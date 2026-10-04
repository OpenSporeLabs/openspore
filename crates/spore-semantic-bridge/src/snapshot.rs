//! The snapshot: a streaming reader over the JSON Lines file.
//!
//! # How the 98 MB file is read
//!
//! The file (93.5 MiB — 98 080 685 bytes) is **never** loaded into memory.
//! [`Snapshot::open`] reads it once, from line 2 onwards, and keeps only:
//!
//! * a [`Vec<Entry>`] of 24-byte records — `{va, size, offset, len, line}` —
//!   giving a compact `u32 -> byte offset` index and, because the file is sorted
//!   ascending by `identity.canonical_va` **by contract**, the sorted entry table
//!   the canonical-identity rule bisects on. 58 757 entries is 1.35 MiB;
//! * a `HashMap` from lowercased name to the VAs carrying it, de-duplicated
//!   case-insensitively, for name lookups. 59 779 names;
//! * the parsed metadata line (line 1, 1_028_861 bytes with its 685 input
//!   digests).
//!
//! Measured on this checkout: `open` takes ~0.85 s and grows RSS by ~10.9 MiB,
//! about 12% of the file, most of which is the name map. `tests/streaming_cost.rs`
//! prints the numbers and bounds them.
//!
//! Every record line is **fully parsed and validated** during `open` — that is
//! what makes an unknown field a refusal rather than a silent absorption — and
//! then dropped. The peak cost is therefore one parsed record, whose largest
//! instance on the current snapshot is the 86 339-byte promotion-supersession
//! blob.
//!
//! Nothing is cached afterwards. `lookup` and every query open their own
//! read-only handle and seek to the byte offset the index recorded, so a
//! long-lived `Snapshot` costs its index and nothing else, and two threads can
//! query one snapshot concurrently without a lock.
//!
//! # Why `lookup` returns an owned `Passport`
//!
//! `fn lookup(&self, va: u32) -> Result<&Passport, _>` cannot coexist with
//! streaming. Returning a borrow tied to `&self` means the `Passport` must live
//! inside the `Snapshot`, which means holding all 58 757 parsed records — the
//! whole 98 MB re-materialised as a syntax tree, several times the file. An
//! interior-mutability cache does not help: the returned reference would be
//! borrowed from the cache and could not outlive the call. So the answer is
//! owned, it is one line's parse, and it costs a few microseconds.
//!
//! # Sortedness is an invariant, not an assumption
//!
//! The interior-resolution rule bisects on entry starts, which is only sound if
//! the index is sorted. `open` therefore **requires** strictly ascending
//! `identity.canonical_va` and refuses anything else as corruption. The Go
//! loader tolerates an unsorted file and leaves the diagnosis to `validate`; this
//! crate cannot, because its index would be wrong, so it fails closed at open.

use crate::address::Va;
use crate::error::BridgeError;
use crate::json::Parser;
use crate::metadata::Metadata;
use crate::passport::{AddressResolution, Canonicalization, Passport};
use crate::schema::metadata_spec;
use crate::sha256::Sha256;
use std::collections::HashMap;
use std::fmt;
use std::fs::File;
use std::io::{BufRead, BufReader, Seek, SeekFrom};
use std::path::{Path, PathBuf};

/// The buffer used for every line read. 1 MiB: the largest record on the
/// current snapshot is 86 kB, and the Go loader allows 16 MiB.
const READ_BUFFER: usize = 1 << 20;

/// The longest record line this crate will read, matching the Go loader's cap.
const MAX_LINE_BYTES: usize = 16 * 1024 * 1024;

/// The default location, relative to a repository root.
const DEFAULT_RELATIVE_PATH: &str = "knowledge/semantic/function-passport-v1.jsonl";

/// The ceiling on what `metadata.counts.functions` is allowed to preallocate.
///
/// The counter is data, and a capacity derived from untrusted data is how a
/// reader turns a header into an allocation attack. Twice the current artifact's
/// 58 757 records, so the hint is generous and the ceiling never binds.
const MAX_PREALLOCATED_ENTRIES: usize = 1 << 20;

/// One indexed record: where it is and what the resolution rule needs.
///
/// The size is asserted in the unit tests so the memory claim in the module docs
/// cannot drift away from the layout.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
struct Entry {
    va: u32,
    size: u32,
    /// Byte offset of the record's line within the file.
    offset: u64,
    /// The line's length without its terminator, checked on re-read so a file
    /// swapped under a long-running process cannot be mis-served.
    len: u32,
    /// The 1-based line number, for errors.
    line: u32,
}

/// The snapshot's binary identity and header facts.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct BinaryIdentity {
    /// The join key: 64 lowercase hex characters.
    pub sha256: String,
    /// The PE image base, as a number.
    pub image_base: u32,
    /// The architecture string, e.g. `x86:LE:32`.
    pub architecture: String,
    /// The analysed program, e.g. `SporeApp.exe`.
    pub program: String,
    /// The program version, e.g. `3.1.0.22`.
    pub version: String,
}

/// What [`Snapshot::verify`] recomputed.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Verification {
    /// `metadata.content_sha256`, verbatim.
    pub declared_content_sha256: String,
    /// The digest this crate computed over the record lines only. The metadata
    /// line is excluded, which is what keeps the field from being
    /// self-referential.
    pub computed_content_sha256: String,
    /// `metadata.counts.functions`.
    pub declared_record_count: usize,
    /// How many record lines were hashed.
    pub computed_record_count: usize,
    /// How many bytes the record lines occupied.
    pub record_bytes: u64,
}

/// A read-only view of one committed passport snapshot.
///
/// Opening one is **optional**: the engine builds and runs without it, and
/// [`Snapshot::open_committed`] returns [`BridgeError::SnapshotUnavailable`]
/// rather than failing to build.
///
/// # Examples
///
/// ```no_run
/// use spore_semantic_bridge::Snapshot;
///
/// # fn main() -> Result<(), spore_semantic_bridge::BridgeError> {
/// // Every fact group is graded, so a look is a match, never a guess.
/// let snapshot = Snapshot::open_committed()?;
/// let passport = snapshot.lookup(0x0040_ccb0)?;
/// println!("{} {:?}", passport.canonical_va_text(), passport.subsystem());
/// # Ok(())
/// # }
/// ```
#[derive(Debug)]
pub struct Snapshot {
    path: PathBuf,
    metadata: Metadata,
    binary: BinaryIdentity,
    entries: Vec<Entry>,
    symbols: HashMap<Box<str>, Vec<u32>>,
    /// True when at least one record states a size, which is what makes interior
    /// resolution possible at all.
    has_sizes: bool,
}

impl Snapshot {
    /// Opens a snapshot and validates every record line in it.
    ///
    /// Eager: the metadata line is parsed in full, and every record line is
    /// parsed in full so that an unknown field is a refusal at open time rather
    /// than a surprise at the first lookup. Cheap in memory: see the module
    /// docs.
    pub fn open(path: &Path) -> Result<Self, BridgeError> {
        let file = File::open(path).map_err(|source| match source.kind() {
            std::io::ErrorKind::NotFound => BridgeError::SnapshotUnavailable {
                path: path.to_path_buf(),
            },
            _ => BridgeError::io(path, source),
        })?;
        let mut reader = LineReader::new(file)?;

        let (line_no, header) = reader.next_line(path, false)?.ok_or_else(|| {
            BridgeError::corrupt(path, 0, "the file is empty: there is no metadata line")
        })?;
        let metadata = parse_metadata(path, line_no, &header)?;
        let binary = metadata.binary.clone();

        // Preallocation is a hint taken from the header, and the header is data:
        // a `counts.functions` of 2^63 must not become a capacity request. One
        // million entries is twice the current artifact, so the hint is generous
        // and the ceiling never binds on real input.
        let hint = metadata.counts.functions.max(0) as usize;
        let mut entries: Vec<Entry> = Vec::with_capacity(hint.min(MAX_PREALLOCATED_ENTRIES));
        let mut symbols: HashMap<Box<str>, Vec<u32>> =
            HashMap::with_capacity(hint.min(MAX_PREALLOCATED_ENTRIES));
        let mut has_sizes = false;
        let mut previous: Option<u32> = None;

        while let Some((line_no, line)) = reader.next_line(path, false)? {
            let passport = parse_passport(path, line_no, &line.text)?;
            let (va, size, size_known, names) = passport.index_fields();
            if let Some(previous) = previous {
                if va == previous {
                    return Err(BridgeError::corrupt(
                        path,
                        line_no,
                        format!(
                            "duplicate canonical VA {}; two records for one address is a file \
                             that can disagree with itself",
                            Va::new(va).canonical()
                        ),
                    ));
                }
                if va < previous {
                    return Err(BridgeError::corrupt(
                        path,
                        line_no,
                        format!(
                            "records are not strictly ascending by identity.canonical_va ({} after \
                             {}); the interior-resolution rule bisects on entry starts, so an \
                             unsorted index would answer a different question",
                            Va::new(va).canonical(),
                            Va::new(previous).canonical()
                        ),
                    ));
                }
            }
            previous = Some(va);
            has_sizes |= size_known;
            // De-duplicate one record's names case-insensitively before
            // indexing. For most functions `normalized_symbol` and
            // `ghidra_name` are the same string, and indexing it twice would
            // make every such lookup report a spurious ambiguity.
            let mut indexed: Vec<String> = Vec::with_capacity(3);
            for name in names.into_iter().flatten().filter(|name| !name.is_empty()) {
                let key = name.to_lowercase();
                if !indexed.contains(&key) {
                    indexed.push(key.clone());
                    symbols.entry(key.into_boxed_str()).or_default().push(va);
                }
            }
            entries.push(Entry {
                va,
                size,
                offset: line.offset,
                len: line.len,
                line: line_no as u32,
            });
        }

        if entries.is_empty() {
            return Err(BridgeError::corrupt(
                path,
                0,
                "metadata present but no function records",
            ));
        }

        Ok(Self {
            path: path.to_path_buf(),
            metadata,
            binary,
            entries,
            symbols,
            has_sizes,
        })
    }

    /// Opens the repository's committed snapshot.
    ///
    /// Resolution order:
    ///
    /// 1. `$OPENSPORE_SEMANTIC_SNAPSHOT` — an explicit file path.
    /// 2. `$OPENSPORE_ROOT`, then each ancestor of the working directory,
    ///    looking for `knowledge/semantic/function-passport-v1.jsonl`.
    ///
    /// With none of those present the answer is
    /// [`BridgeError::SnapshotUnavailable`], which is the artifact's
    /// optionality expressed as a type rather than as a failure to build.
    pub fn open_committed() -> Result<Self, BridgeError> {
        let candidate = locate_committed_snapshot()?;
        Self::open(&candidate)
    }

    /// The file this snapshot was read from.
    pub fn path(&self) -> &Path {
        &self.path
    }

    /// The join key's first half: the SHA-256 of the analysed binary.
    pub fn binary_sha256(&self) -> &str {
        &self.binary.sha256
    }

    /// The analysed binary's image base.
    pub fn image_base(&self) -> u32 {
        self.binary.image_base
    }

    /// The analysed binary's identity.
    pub fn binary(&self) -> &BinaryIdentity {
        &self.binary
    }

    /// How many function records the file holds.
    pub fn function_count(&self) -> usize {
        self.entries.len()
    }

    /// The schema id this build implements, for a caller recording what it read.
    pub fn schema(&self) -> &'static str {
        crate::passport::SNAPSHOT_SCHEMA
    }

    /// The header's declared content digest, without recomputing anything.
    pub fn declared_content_sha256(&self) -> &str {
        &self.metadata.content_sha256
    }

    /// The header, including every input digest the export read.
    pub fn metadata(&self) -> &Metadata {
        &self.metadata
    }

    /// Refuses a snapshot that describes another binary.
    ///
    /// The join key is `binary_sha256 + canonical VA`, so a mismatched snapshot
    /// answers a different question than the caller asked. Call this before
    /// trusting any fact from a snapshot you did not produce.
    pub fn require_binary(&self, sha256: &str) -> Result<(), BridgeError> {
        if self.binary.sha256 == sha256 {
            Ok(())
        } else {
            Err(BridgeError::BinaryMismatch {
                snapshot: self.binary.sha256.clone(),
                required: sha256.to_owned(),
            })
        }
    }

    /// Looks up the passport whose canonical entry is exactly `va`.
    ///
    /// The returned `Passport` is parsed from that one line; see the module docs
    /// for why it is owned.
    ///
    /// # Errors
    ///
    /// [`BridgeError::UnknownFunction`] when no entry sits at `va`. For an
    /// address *inside* a body use [`Snapshot::lookup_interior`], which reports
    /// the containing entry instead of failing.
    pub fn lookup(&self, va: u32) -> Result<Passport, BridgeError> {
        let Some(entry) = self.entry_at(va).copied() else {
            return Err(self.unknown(va));
        };
        self.read(entry)
    }

    /// Whether an entry sits at exactly `va`.
    pub fn contains_entry(&self, va: u32) -> bool {
        self.entry_at(va).is_some()
    }

    /// Places `va` in the function universe.
    ///
    /// # The rule
    ///
    /// This is the **third transcription** of `canonical_identity` in
    /// `tools/reconstruction_knowledge.py`. The second is
    /// `tools/spore-semantic/internal/openspore/identity.go`, whose own comment
    /// says it transcribes the Python rather than inventing a second mapping
    /// rule. A third mapping algorithm would be a third source of truth for
    /// identity, so the algorithm is transcribed and not improved:
    ///
    /// 1. An address that is already an entry is [`Canonicalization::FunctionEntry`].
    /// 2. Otherwise bisect on entry starts for the greatest start `s <= va`.
    /// 3. Require `s <= va < s + size`. A hit is
    ///    [`Canonicalization::ContainingFunctionEntry`] with `offset = va - s`.
    /// 4. A miss is [`Canonicalization::NonFunctionEntity`].
    ///
    /// Step 4 is the conservative direction the repository already chose:
    /// padding between two bodies — real padding, or the tail of a body whose
    /// size stops short — resolves to **nothing**.
    ///
    /// # `0x00925050`
    ///
    /// The live case, and the reason step 4 refuses instead of guessing. It lies
    /// between `FUN_00925000` (ending `0x0092504a`) and `FUN_009250c0`, so the
    /// rule returns `NonFunctionEntity`. `spore-recomp` reached it through a real
    /// vtable indirect call; that discrepancy is the deliverable, and mapping
    /// padding to a function would destroy it.
    ///
    /// # Note on the return type
    ///
    /// The specified shape was `{canonical: u32, offset: u32}`. A non-function
    /// entity has neither, and `0x00000000` is a real address that means something
    /// else, so both are [`Option`]. See [`AddressResolution`].
    pub fn lookup_interior(&self, va: u32) -> Result<AddressResolution, BridgeError> {
        Ok(self.resolve(va))
    }

    /// The canonical-identity rule, non-failing.
    ///
    /// Every answer is a resolution, including "nothing", so this cannot fail and
    /// `lookup_interior` exists for callers who prefer a `Result` at the call
    /// site.
    pub fn resolve(&self, va: u32) -> AddressResolution {
        if let Some(entry) = self.entry_at(va) {
            return AddressResolution {
                requested: va,
                canonical: Some(entry.va),
                rule: Canonicalization::FunctionEntry,
                offset: Some(0),
                end: None,
            };
        }
        if !self.has_sizes {
            return AddressResolution {
                requested: va,
                canonical: None,
                rule: Canonicalization::NonFunctionEntity,
                offset: None,
                end: None,
            };
        }
        // The greatest entry start at or below `va`. `entries` is sorted and
        // strictly ascending, which `open` has already proved.
        let position = self.entries.partition_point(|entry| entry.va <= va);
        let Some(entry) = position.checked_sub(1).map(|i| &self.entries[i]) else {
            return AddressResolution {
                requested: va,
                canonical: None,
                rule: Canonicalization::NonFunctionEntity,
                offset: None,
                end: None,
            };
        };
        if entry.size == 0 {
            return AddressResolution {
                requested: va,
                canonical: None,
                rule: Canonicalization::NonFunctionEntity,
                offset: None,
                end: None,
            };
        }
        // x86-32 addresses cannot overflow here in practice, but the addition is
        // done in 64 bits so a nonsense size cannot wrap a real address into a
        // range test that passes.
        let end = u64::from(entry.va) + u64::from(entry.size);
        if u64::from(va) >= u64::from(entry.va) && u64::from(va) < end {
            AddressResolution {
                requested: va,
                canonical: Some(entry.va),
                rule: Canonicalization::ContainingFunctionEntry,
                offset: Some(va - entry.va),
                end: u32::try_from(end).ok(),
            }
        } else {
            AddressResolution {
                requested: va,
                canonical: None,
                rule: Canonicalization::NonFunctionEntity,
                offset: None,
                end: None,
            }
        }
    }

    /// Every canonical VA carrying `name`, ascending.
    ///
    /// Searches `names.normalized_symbol`, `names.sdk_name` and
    /// `names.ghidra_name`, case-insensitively, de-duplicated — so a record whose
    /// normalized symbol equals its Ghidra name is not reported twice.
    ///
    /// Ambiguity is preserved, not resolved: a name shared by several functions
    /// yields several VAs. The triage export's own notes record 92 duplicate
    /// normalized-name groups across 190 rows, which is why address identity
    /// stays authoritative and [`Snapshot::resolve_symbol`] is the explicit
    /// single-answer form.
    ///
    /// # Why VAs and not `&[&Passport]`
    ///
    /// The specified shape returns borrowed passports. A borrowed `Passport`
    /// would have to live inside the `Snapshot`, which is the same
    /// materialise-everything problem [`Snapshot::lookup`] documents — 98 MB
    /// re-parsed as a syntax tree, and one borrowed record per name. Returning
    /// the *addresses* is also the better answer: names are a convenience index
    /// and the address is the key, so a caller picks by address and re-reads
    /// only what it wants. [`Snapshot::lookup_symbol_passports`] is the
    /// convenience that parses the matches for you.
    ///
    /// # Errors
    ///
    /// [`BridgeError::UnknownSymbol`] when nothing carries the name.
    pub fn lookup_symbol(&self, name: &str) -> Result<Vec<u32>, BridgeError> {
        let key = name.trim().to_lowercase();
        self.symbols
            .get(key.as_str())
            .map(|list| list.to_vec())
            .ok_or_else(|| BridgeError::UnknownSymbol {
                name: name.to_owned(),
            })
    }

    /// Every passport carrying `name`, ascending by canonical VA.
    ///
    /// Parses only the matching records, so a common name costs one parse per
    /// match rather than a whole scan.
    pub fn lookup_symbol_passports(&self, name: &str) -> Result<Vec<Passport>, BridgeError> {
        self.lookup_symbol(name)?
            .into_iter()
            .map(|va| self.lookup(va))
            .collect()
    }

    /// The one canonical VA carrying `name`.
    ///
    /// # Errors
    ///
    /// [`BridgeError::UnknownSymbol`] for no match,
    /// [`BridgeError::AmbiguousSymbol`] for more than one — reported, never
    /// silently resolved to the first.
    pub fn resolve_symbol(&self, name: &str) -> Result<u32, BridgeError> {
        let matches = self.lookup_symbol(name)?;
        match matches.as_slice() {
            [] => Err(BridgeError::UnknownSymbol {
                name: name.to_owned(),
            }),
            [only] => Ok(*only),
            many => Err(BridgeError::AmbiguousSymbol {
                name: name.to_owned(),
                matches: many.len(),
            }),
        }
    }

    /// How many distinct names the snapshot indexes.
    pub fn symbol_count(&self) -> usize {
        self.symbols.len()
    }

    /// How many indexed names map to more than one function.
    ///
    /// A property of the identity model, not a defect: names are a convenience
    /// index and addresses are the key.
    pub fn ambiguous_name_count(&self) -> usize {
        self.symbols.values().filter(|list| list.len() > 1).count()
    }

    /// The entry immediately below `va` in the index, with its body size.
    ///
    /// The entry the canonical-identity rule bisected onto for `va`, with its
    /// body size.
    ///
    /// Exposed so a caller can see *why* an address resolved to nothing: the
    /// candidate it landed on and the byte it fell past.
    pub fn preceding_entry(&self, va: u32) -> Option<(u32, u32)> {
        let position = self.entries.partition_point(|entry| entry.va <= va);
        position
            .checked_sub(1)
            .map(|i| (self.entries[i].va, self.entries[i].size))
    }

    /// Recomputes `metadata.content_sha256` over the record lines and checks the
    /// header's own counters.
    ///
    /// The digest covers the **record lines only**, each including its
    /// terminator. Line 1 is excluded, which is what keeps the field from being
    /// self-referential and lets a consumer check binary identity before parsing
    /// 59k records.
    ///
    /// This is a second, independent pass over the file: `open` already read
    /// every byte to validate it, but it deliberately does not hash, so that
    /// integrity checking stays something a caller opts into and can re-run
    /// against a file that may have changed.
    pub fn verify(&self) -> Result<Verification, BridgeError> {
        let mut hasher = Sha256::new();
        let mut count = 0usize;
        let mut bytes = 0u64;
        let file = File::open(&self.path).map_err(|source| BridgeError::io(&self.path, source))?;
        let mut reader = LineReader::new(file)?;
        let Some((_, _)) = reader.next_line(&self.path, false)? else {
            return Err(BridgeError::corrupt(&self.path, 0, "the file is empty"));
        };
        while let Some((_, line)) = reader.next_line(&self.path, true)? {
            hasher.update(&line.raw);
            count += 1;
            bytes += line.raw.len() as u64;
        }
        let computed = hasher.hex();
        let declared = self.metadata.content_sha256.clone();
        if declared != computed {
            return Err(BridgeError::ContentDigestMismatch {
                path: self.path.clone(),
                declared,
                computed,
            });
        }
        let declared_count = self.metadata.counts.functions.max(0) as usize;
        if declared_count != count {
            return Err(BridgeError::RecordCountMismatch {
                path: self.path.clone(),
                declared: declared_count,
                computed: count,
            });
        }
        Ok(Verification {
            declared_content_sha256: declared,
            computed_content_sha256: computed,
            declared_record_count: declared_count,
            computed_record_count: count,
            record_bytes: bytes,
        })
    }

    /// A reader over every record, in canonical-VA order.
    ///
    /// Lazily: one record is parsed at a time and dropped before the next is
    /// read, so an engine can walk all 58 757 without ever holding more than one
    /// of them.
    pub fn passports(&self) -> PassportCursor<'_> {
        PassportCursor::new(self, self.entries.as_slice())
    }

    /// A reader over the records whose triage subsystem is exactly `subsystem`.
    ///
    /// Routing key caveat: 49 340 of the 58 757 subsystem values are the literal
    /// string `"Unknown"`, so filtering on that value returns 49 340 records. Use
    /// [`crate::Classification::has_named_subsystem`] when you want real names.
    pub fn passports_in_subsystem(&self, subsystem: &str) -> PassportCursor<'_> {
        let wanted = subsystem.to_owned();
        PassportCursor::filtered(self, self.entries.as_slice(), move |passport| {
            passport.classification().subsystem.as_deref() == Some(wanted.as_str())
        })
    }

    /// A reader over the records whose SDK name lies in `namespace`.
    ///
    /// `namespace` is matched case-sensitively against the text before the first
    /// `::`, because that is how the SDK spells it: `Graphics`, `UTFWin`, `App`,
    /// `Simulator`, `GameInput`, `Resource`.
    pub fn passports_with_sdk_namespace(&self, namespace: &str) -> PassportCursor<'_> {
        let wanted = namespace.to_owned();
        PassportCursor::filtered(self, self.entries.as_slice(), move |passport| {
            passport.sdk_namespace() == Some(wanted.as_str())
        })
    }

    /// A reader over the records a promotion marker exists for.
    pub fn promoted_passports(&self) -> PassportCursor<'_> {
        PassportCursor::filtered(self, self.entries.as_slice(), |passport| {
            passport.promoted().value() == Some(&true)
        })
    }

    /// A reader over the records whose reconstruction group is present.
    pub fn reconstructed_passports(&self) -> PassportCursor<'_> {
        PassportCursor::filtered(self, self.entries.as_slice(), |passport| {
            passport.reconstruction().is_available()
        })
    }

    /// Runs `visit` over every record without allocating a cursor.
    ///
    /// The primitive the cursors are built from; use it when a caller wants one
    /// pass over the file with no per-item `Result` to thread.
    pub fn for_each_passport(
        &self,
        mut visit: impl FnMut(&Passport) -> Result<(), BridgeError>,
    ) -> Result<(), BridgeError> {
        for entry in &self.entries {
            let passport = self.read(*entry)?;
            visit(&passport)?;
        }
        Ok(())
    }

    /// The subsystem histogram, most frequent first and alphabetically within a
    /// tie.
    ///
    /// Streams the file and counts, so it holds one record plus the distinct
    /// subsystem names (122 on the current snapshot) rather than the corpus.
    pub fn subsystem_histogram(&self) -> Result<Vec<(String, usize)>, BridgeError> {
        self.histogram(|passport| {
            passport
                .classification()
                .subsystem
                .clone()
                .unwrap_or_else(|| "<unavailable>".to_owned())
        })
    }

    /// The SDK-namespace histogram. Records without an SDK name fall under
    /// `<none>` rather than being dropped, so the counts still sum to
    /// [`Snapshot::function_count`].
    pub fn sdk_namespace_histogram(&self) -> Result<Vec<(String, usize)>, BridgeError> {
        self.histogram(|passport| passport.sdk_namespace().unwrap_or("<none>").to_owned())
    }

    fn histogram(
        &self,
        key: impl Fn(&Passport) -> String,
    ) -> Result<Vec<(String, usize)>, BridgeError> {
        let mut counts: HashMap<String, usize> = HashMap::new();
        self.for_each_passport(|passport| {
            *counts.entry(key(passport)).or_default() += 1;
            Ok(())
        })?;
        let mut out: Vec<(String, usize)> = counts.into_iter().collect();
        out.sort_by(|a, b| b.1.cmp(&a.1).then_with(|| a.0.cmp(&b.0)));
        Ok(out)
    }

    fn entry_at(&self, va: u32) -> Option<&Entry> {
        let position = self.entries.partition_point(|entry| entry.va < va);
        self.entries.get(position).filter(|entry| entry.va == va)
    }

    fn unknown(&self, va: u32) -> BridgeError {
        BridgeError::UnknownFunction {
            requested: va,
            image_base: self.binary.image_base,
            indexed: self.entries.len(),
        }
    }

    /// Reads one indexed record and checks it against the index.
    ///
    /// The index holds the VA, the body size and the line's length, so a file
    /// replaced underneath a long-lived engine is reported at the record that
    /// noticed rather than served from a stale offset.
    fn read(&self, entry: Entry) -> Result<Passport, BridgeError> {
        let passport = self.read_raw(entry)?;
        if passport.canonical_va() != entry.va {
            return Err(BridgeError::corrupt(
                &self.path,
                entry.line as usize,
                format!(
                    "the line at this offset now holds {} but the index recorded {}; the file \
                     changed after it was opened",
                    passport.canonical_va_text(),
                    Va::new(entry.va).canonical()
                ),
            ));
        }
        if passport.size() != Some(entry.size) {
            return Err(BridgeError::corrupt(
                &self.path,
                entry.line as usize,
                format!(
                    "{} now states a body size of {:?} but the index recorded {}; the file changed \
                     after it was opened",
                    passport.canonical_va_text(),
                    passport.size(),
                    entry.size
                ),
            ));
        }
        Ok(passport)
    }

    /// Reads and parses exactly one indexed record.
    fn read_raw(&self, entry: Entry) -> Result<Passport, BridgeError> {
        let file = File::open(&self.path).map_err(|source| BridgeError::io(&self.path, source))?;
        let mut reader = LineReader::new(file)?;
        reader.seek_to(entry.offset, &self.path)?;
        let line = reader
            .next_line(&self.path, false)?
            .map(|(_, line)| line)
            .ok_or_else(|| BridgeError::corrupt(&self.path, entry.line as usize, "line is gone"))?;
        if line.len != entry.len {
            return Err(BridgeError::corrupt(
                &self.path,
                entry.line as usize,
                format!(
                    "the line at this offset is {} bytes but the index recorded {}; the file \
                     changed after it was opened",
                    line.len, entry.len
                ),
            ));
        }
        parse_passport(&self.path, entry.line as usize, &line.text)
    }
}

/// The filter a narrowed [`PassportCursor`] applies.
type Predicate<'s> = Box<dyn Fn(&Passport) -> bool + 's>;

/// A lazily-parsed run over the snapshot's records.
///
/// Yields one [`Result`] per item rather than panicking, so a file that changed
/// underneath is reported at the item that noticed.
pub struct PassportCursor<'s> {
    snapshot: &'s Snapshot,
    entries: &'s [Entry],
    position: usize,
    predicate: Option<Predicate<'s>>,
}

impl fmt::Debug for PassportCursor<'_> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("PassportCursor")
            .field("path", &self.snapshot.path)
            .field("remaining", &self.remaining())
            .field("filtered", &self.predicate.is_some())
            .finish()
    }
}

impl<'s> PassportCursor<'s> {
    fn new(snapshot: &'s Snapshot, entries: &'s [Entry]) -> Self {
        Self {
            snapshot,
            entries,
            position: 0,
            predicate: None,
        }
    }

    fn filtered(
        snapshot: &'s Snapshot,
        entries: &'s [Entry],
        predicate: impl Fn(&Passport) -> bool + 's,
    ) -> Self {
        Self {
            snapshot,
            entries,
            position: 0,
            predicate: Some(Box::new(predicate)),
        }
    }

    /// How many records this cursor may still yield.
    pub fn remaining(&self) -> usize {
        self.entries.len().saturating_sub(self.position)
    }
}

impl Iterator for PassportCursor<'_> {
    type Item = Result<Passport, BridgeError>;

    fn next(&mut self) -> Option<Self::Item> {
        while self.position < self.entries.len() {
            let entry = self.entries[self.position];
            self.position += 1;
            let passport = match self.snapshot.read(entry) {
                Ok(passport) => passport,
                Err(error) => return Some(Err(error)),
            };
            let keep = match &self.predicate {
                None => true,
                Some(predicate) => predicate(&passport),
            };
            if keep {
                return Some(Ok(passport));
            }
        }
        None
    }
}

// ---------------------------------------------------------------------------
// Line reading
// ---------------------------------------------------------------------------

/// One record line: its text without the terminator, and its bytes with.
#[derive(Debug)]
struct Line {
    text: String,
    /// The exact bytes read, terminator included. Only populated when the caller
    /// asked for it, because only the integrity pass needs them.
    raw: Vec<u8>,
    offset: u64,
    len: u32,
}

/// What one `fill_buf` step found.
enum Step {
    /// The line terminator is at this offset.
    Line(usize),
    /// No terminator in the buffered bytes; take all of them and continue.
    Need(usize),
    /// End of input.
    Eof,
}

/// A `BufReader` wrapper that tracks byte offsets and refuses oversized lines.
///
/// Lines are assembled by hand rather than with `read_until` so that a file with
/// no newline at all is refused at 16 MiB instead of being read into memory in
/// one piece. That is the only unbounded allocation a corrupt file could provoke,
/// so it is bounded.
#[derive(Debug)]
struct LineReader {
    reader: BufReader<File>,
    buffer: Vec<u8>,
    offset: u64,
    line_number: usize,
}

impl LineReader {
    fn new(file: File) -> Result<Self, BridgeError> {
        Ok(Self {
            reader: BufReader::with_capacity(READ_BUFFER, file),
            buffer: Vec::with_capacity(8 * 1024),
            offset: 0,
            line_number: 1,
        })
    }

    fn seek_to(&mut self, offset: u64, path: &Path) -> Result<(), BridgeError> {
        self.reader
            .seek(SeekFrom::Start(offset))
            .map_err(|source| BridgeError::io(path, source))?;
        self.offset = offset;
        Ok(())
    }

    /// Reads the next line, or `None` at end of input.
    ///
    /// A line that is empty or pure whitespace is refused. The Go loader skips
    /// such lines silently; this crate does not, because a blank line in a file
    /// whose content digest covers every record line means the file is not the
    /// file it claims to be, and a silent skip would hide that.
    fn next_line(
        &mut self,
        path: &Path,
        keep_raw: bool,
    ) -> Result<Option<(usize, Line)>, BridgeError> {
        self.buffer.clear();
        loop {
            let step = {
                let available = self
                    .reader
                    .fill_buf()
                    .map_err(|source| BridgeError::io(path, source))?;
                if available.is_empty() {
                    Step::Eof
                } else {
                    match available.iter().position(|byte| *byte == b'\n') {
                        Some(index) => Step::Line(index),
                        None => Step::Need(available.len()),
                    }
                }
            };
            match step {
                Step::Eof => {
                    // A final line with no terminator is still a line; an empty
                    // buffer at end of input is not.
                    if self.buffer.is_empty() {
                        return Ok(None);
                    }
                    break;
                }
                Step::Line(index) => {
                    self.take(index + 1);
                    break;
                }
                Step::Need(count) => self.take(count),
            }
            if self.buffer.len() > MAX_LINE_BYTES {
                return Err(BridgeError::corrupt(
                    path,
                    self.line_number,
                    format!("line exceeds the {MAX_LINE_BYTES}-byte record limit"),
                ));
            }
        }

        let line_number = self.line_number;
        self.line_number += 1;
        let offset = self.offset;
        self.offset += self.buffer.len() as u64;

        let length = self
            .buffer
            .iter()
            .rposition(|byte| *byte != b'\n' && *byte != b'\r')
            .map_or(0, |index| index + 1);
        let text = core::str::from_utf8(&self.buffer[..length]).map_err(|_| {
            BridgeError::corrupt(path, line_number, "record line is not valid UTF-8")
        })?;
        if text.trim().is_empty() {
            return Err(BridgeError::corrupt(
                path,
                line_number,
                "blank or whitespace-only line; every line after the metadata is a record",
            ));
        }
        let text = text.to_owned();
        let raw = if keep_raw {
            self.buffer.clone()
        } else {
            Vec::new()
        };
        self.buffer.clear();
        Ok(Some((
            line_number,
            Line {
                text,
                raw,
                offset,
                len: length as u32,
            },
        )))
    }

    /// Appends `count` buffered bytes to the line under construction.
    fn take(&mut self, count: usize) {
        let chunk = self
            .reader
            .fill_buf()
            .map(|available| available[..count.min(available.len())].to_vec())
            .unwrap_or_default();
        let taken = chunk.len();
        self.reader.consume(taken);
        self.buffer.extend_from_slice(&chunk);
    }
}

fn parse_metadata(path: &Path, line_number: usize, line: &Line) -> Result<Metadata, BridgeError> {
    let obj = Parser::new(&line.text)
        .parse_one(metadata_spec())
        .map_err(|error| BridgeError::from_json(path, line_number, error))?;
    Metadata::parse(path, line_number, &obj)
}

fn parse_passport(path: &Path, line: usize, text: &str) -> Result<Passport, BridgeError> {
    Passport::parse(text).map_err(|error| BridgeError::from_json(path, line, error))
}

/// Where the committed snapshot lives, or the first place that was looked for.
fn locate_committed_snapshot() -> Result<PathBuf, BridgeError> {
    if let Some(path) = std::env::var_os("OPENSPORE_SEMANTIC_SNAPSHOT") {
        let path = PathBuf::from(path);
        if !path.is_absolute() {
            let mut absolute = std::env::current_dir().unwrap_or_else(|_| PathBuf::from("."));
            absolute.push(path);
            return Ok(absolute);
        }
        return Ok(path);
    }
    let mut roots: Vec<PathBuf> = Vec::new();
    if let Some(root) = std::env::var_os("OPENSPORE_ROOT") {
        roots.push(PathBuf::from(root));
    }
    let mut cursor = std::env::current_dir().ok();
    while let Some(dir) = cursor {
        roots.push(dir.clone());
        cursor = dir.parent().map(Path::to_path_buf);
    }
    for root in roots {
        let candidate = root.join(DEFAULT_RELATIVE_PATH);
        if candidate.is_file() {
            return Ok(candidate);
        }
    }
    // The path named in the error is the location searched for, not a path built
    // by joining the default directory to the file name — those differ, and the
    // second would point at nothing.
    Err(BridgeError::SnapshotUnavailable {
        path: PathBuf::from(DEFAULT_RELATIVE_PATH),
    })
}

/// Locates the committed snapshot, exposed for callers that want to report the
/// path without opening it.
pub fn committed_snapshot_path() -> Result<PathBuf, BridgeError> {
    locate_committed_snapshot()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_index_entry_is_small_enough_for_the_memory_claim_to_hold() {
        // The module docs state the layout and the per-record cost; this keeps
        // them honest if a field is ever added.
        assert_eq!(core::mem::size_of::<Entry>(), 24);
        assert_eq!(
            58_757 * core::mem::size_of::<Entry>(),
            1_410_168,
            "the entry table for the current artifact is about 1.35 MiB"
        );
    }
}
