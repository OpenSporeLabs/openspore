//! `types`: the canonical type/group tables and a per-package census.
//!
//! A Rust port of `tools/spore/typescan.py` for the histogram, and of the
//! transcribed `typenames.json` / `groupnames.json` tables for the listing.
//!
//! # The prop-directory scrape, reproduced exactly
//!
//! `typescan.py` does not get its names from `typenames.json` alone. It merges a
//! **second, per-package source**: the record whose group *and* instance are both
//! `0x1C7AC81`, whose bytes are printable latin-1 that spell out
//! `0x<8 hex digits><name>` pairs, and whose names win over the canonical table.
//!
//! Two details of the oracle's scrape are load-bearing and are reproduced rather
//! than "cleaned up":
//!
//! * The blob is filtered to `isprintable() or ch == ' '` before the regex runs.
//!   Python's `str.isprintable()` is a Unicode property, so the filtered text is
//!   *not* the ASCII subset -- high latin-1 characters such as `é` and `ñ` are
//!   printable and survive. Filtering to ASCII here would drop them and shift
//!   every match after the first non-ASCII byte.
//! * The regex is `0x([0-9a-f]{8})([A-Za-z0-9_]+?)(?=0x|$)`: lowercase `0x` and
//!   lowercase hex only, and the name must run **immediately** up to the next
//!   `0x` or the end of the text. A blob entry followed by anything else simply
//!   does not match, and a failed match does not consume the position, so the
//!   scan retries one byte later and can find an *inner* `0x`.
//!
//! # Measured on the real corpus
//!
//! `Spore_Content.package` (17 119 records) carries a `0x01C7AC81:0x01C7AC81`
//! prop directory, and the scrape finds names for its types. The histogram it
//! produces agrees with `verify`'s census on every count, which is the check that
//! matters: two independent code paths over the same index reach the same numbers.
//!
//! One name is worth flagging. The canonical table calls `0x2F4E681B` `rw4`, and
//! so does the prop directory. All 1 131 RW4 records in the package decode through
//! `spore-rw4`, while `png`-typed records (1 642 of them in this package, and
//! 10 487 across the whole installed data set) begin with the **PNG magic**
//! `89 50 4e 47 0d 0a 1a 0a` and are stored uncompressed -- they are raw PNG, not
//! RW4 containers as three crate docs in this workspace state. See
//! `docs/RENDERWARE-RESEARCH.md`; the discrepancy is reported rather than resolved
//! here, because resolving it means changing a claim in another crate.
//!
//! # The `0x1C7AC81` record is NOT an instance string table
//!
//! The instance component is `0x1C7AC81` — the same word as the group. That
//! coincidence is exactly why it is worth saying plainly: this record maps **type
//! ids to type names**. It says nothing about what any instance id means, and
//! nothing in DBPF does. `list --names` deliberately does *not* merge it, because
//! a per-package type name displayed as if it were a canonical one is how a
//! package-local convention becomes an unexamined global assumption.

use std::collections::HashMap;
use std::io::Write;

use spore_assets::ContentStore;
use spore_core::record::{GROUP_NAMES, TYPE_NAMES};

use crate::{ToolError, TypesRequest};

/// The group id of the prop-directory record.
pub const PROP_DIRECTORY_GROUP: u32 = 0x01C7_AC81;

/// The instance id of the prop-directory record.
///
/// Equal to [`PROP_DIRECTORY_GROUP`]. See the module docs: this record names
/// *types*, not instances.
pub const PROP_DIRECTORY_INSTANCE: u32 = 0x01C7_AC81;

/// How many histogram rows `typescan.py` prints.
///
/// 60, not 20: the oracle's `Counter.most_common(60)` is the behaviour being
/// ported, and a census that silently shows a different number of rows than its
/// reference is not a port.
pub const TYPESCAN_TOP_N: usize = 60;

/// `types`: the type table, optionally the group table and a package census.
pub fn run(request: &TypesRequest, out: &mut dyn Write) -> Result<(), ToolError> {
    write_type_table(out)?;
    if request.group {
        write_group_table(out)?;
    }
    if let Some(path) = &request.package {
        let store = super::single_package_store(path)?;
        write_histogram(out, &store)?;
    }
    Ok(())
}

/// The canonical type table, ascending by id.
fn write_type_table(out: &mut dyn Write) -> Result<(), ToolError> {
    writeln!(out, "canonical type table ({} entries)", TYPE_NAMES.len())?;
    writeln!(out, "     type_id  name")?;
    for (id, name) in TYPE_NAMES {
        writeln!(out, "  0x{id:08x}  {name}")?;
    }
    Ok(())
}

/// The canonical group table, ascending by id.
fn write_group_table(out: &mut dyn Write) -> Result<(), ToolError> {
    writeln!(out)?;
    writeln!(out, "canonical group table ({} entries)", GROUP_NAMES.len())?;
    writeln!(out, "     group_id  name")?;
    for (id, name) in GROUP_NAMES {
        writeln!(out, "  0x{id:08x}  {name}")?;
    }
    Ok(())
}

/// The per-package census: count by type id, with the prop directory's names
/// merged over the canonical ones.
fn write_histogram(out: &mut dyn Write, store: &ContentStore) -> Result<(), ToolError> {
    let package = &store.packages()[0];
    let names = merged_names(store);
    let ranked = rank_types(package.index().entries().iter().map(|e| e.type_id));

    writeln!(out)?;
    writeln!(out, "### {}", package.name())?;
    writeln!(
        out,
        "per-package type histogram ({} record(s)); names merge the canonical table with this",
        package.record_count()
    )?;
    writeln!(
        out,
        "package's own 0x01C7AC81:0x01C7AC81 prop directory, which maps TYPE IDS TO NAMES"
    )?;
    writeln!(out, "and says nothing about instance ids.")?;
    writeln!(out, "{:>7}  typeID      name", "count")?;
    for (type_id, count) in ranked.iter().take(TYPESCAN_TOP_N) {
        writeln!(
            out,
            "{count:7}  0x{type_id:08x}  {}",
            names.get(type_id).map_or("?", String::as_str)
        )?;
    }
    if ranked.len() > TYPESCAN_TOP_N {
        writeln!(
            out,
            "({} further type(s) not shown; typescan.py caps at {TYPESCAN_TOP_N})",
            ranked.len() - TYPESCAN_TOP_N
        )?;
    }
    Ok(())
}

/// Counts by type id, ranked most frequent first.
///
/// The tie-break reproduces `Counter.most_common`'s: `Counter` records first
/// appearance in index order, and `sorted(..., reverse=True)` is stable, so
/// equal counts keep that order. Sorting on `(Reverse(count), first_seen)` is
/// the same rule stated explicitly — a plain `sort_by(|a, b| b.1.cmp(&a.1))` on a
/// `HashMap` would be a different, unreproducible ranking.
pub fn rank_types(type_ids: impl Iterator<Item = u32>) -> Vec<(u32, usize)> {
    let mut first_seen: HashMap<u32, usize> = HashMap::new();
    let mut counts: HashMap<u32, usize> = HashMap::new();
    for (position, type_id) in type_ids.enumerate() {
        first_seen.entry(type_id).or_insert(position);
        *counts.entry(type_id).or_insert(0) += 1;
    }
    let mut ranked: Vec<(u32, usize)> = counts.into_iter().collect();
    ranked.sort_by(|left, right| {
        right
            .1
            .cmp(&left.1)
            .then_with(|| first_seen.get(&left.0).cmp(&first_seen.get(&right.0)))
    });
    ranked
}

/// The name for every type id a package implies: the canonical table, overlaid
/// with the package's own prop-directory names.
///
/// The prop names win, exactly as in `typescan.py`, where `names` starts as a
/// copy of the canonical table and each regex hit overwrites it.
pub fn merged_names(store: &ContentStore) -> HashMap<u32, String> {
    let mut names: HashMap<u32, String> = TYPE_NAMES
        .iter()
        .map(|(id, name)| (*id, (*name).to_owned()))
        .collect();
    for (type_id, name) in prop_directory_names(store) {
        names.insert(type_id, name);
    }
    names
}

/// Scrapes `0x<8 lowercase hex><name>` pairs out of the prop-directory record.
///
/// Returns an empty vector when the package has no such record, when its payload
/// cannot be extracted, or when the text contains no match. Those are three
/// different states that all mean "no name is available from here", and none of
/// them is an error: a package without a prop directory is normal.
pub fn prop_directory_names(store: &ContentStore) -> Vec<(u32, String)> {
    for (index, package) in store.packages().iter().enumerate() {
        // Located by group and instance only, exactly as `typescan.py` does
        // (`it['group'] == 0x1C7AC81 and it['inst'] == 0x1C7AC81`). The record's
        // type id is deliberately *not* a matching condition, because the oracle
        // does not constrain it and a name table whose lookup depended on an
        // unobserved third field would be a second, wrong guess.
        let Some(entry) = package.index().entries().iter().find(|entry| {
            entry.group_id == PROP_DIRECTORY_GROUP && entry.instance_id == PROP_DIRECTORY_INSTANCE
        }) else {
            continue;
        };
        let Ok(bytes) = store.read_from(index, &entry.key) else {
            continue;
        };
        let text = printable_latin1(&bytes);
        return scrape_pairs(&text);
    }
    Vec::new()
}

/// Decodes bytes as latin-1 and keeps the characters Python's
/// `str.isprintable()` would keep.
///
/// Python decodes with `errors="replace"` and `latin1` never fails, so the
/// "replacement" never actually appears; the filter is what does the work.
/// Two subtleties, both reproduced:
///
/// * `isprintable()` is a Unicode predicate, so `é`, `ñ` and `é` **survive**
///   while a control byte or a combining mark does not.
/// * Space is added back explicitly, because `isprintable()` is false for it.
///
/// The one thing that cannot be reproduced is Python's exact Unicode `isprintable`
/// table. This implementation uses the Unicode categories that table is defined
/// in terms of: it keeps letters, marks, numbers, punctuation, symbols and
/// separators other than the non-breaking space, and drops control, unassigned,
/// format, surrogate and private-use characters. A prop directory is ASCII in
/// every package this repository has looked at, so the difference is invisible
/// there — and it is still a difference, so it is named rather than glossed.
pub fn printable_latin1(bytes: &[u8]) -> String {
    bytes
        .iter()
        .map(|&byte| char::from_u32(u32::from(byte)).unwrap_or('\u{fffd}'))
        .filter(|&c| c == ' ' || is_python_printable(c))
        .collect()
}

/// The categories Python's `str.isprintable()` accepts.
///
/// `Other`/`Separator` are the interesting case: Python keeps the space characters
/// and drops the line/paragraph separators, which is why `c == ' '` has to be
/// re-added by the caller.
fn is_python_printable(c: char) -> bool {
    // `char::is_control` covers Cc plus the format characters Python treats as
    // non-printable (Cf), and `is_whitespace` covers the separators Python
    // excludes.
    !(c.is_control() || c.is_whitespace())
}

/// Scans for `0x([0-9a-f]{8})([A-Za-z0-9_]+?)(?=0x|$)` and returns the pairs.
///
/// A hand-rolled equivalent of Python's `re.finditer` over that pattern. The
/// three behaviours that a naive rewrite gets wrong, and which are each visible
/// in the tests below:
///
/// * **The lazy quantifier is checked at every character position**, not only at
///   a class boundary. `0` and `x` are both in `[A-Za-z0-9_]`, so the name
///   `"gmdl"` in `0x00e6bce5gmdl0x2f4e681brw4` ends where the *next* `0x` begins —
///   it does not run on into `gmdl0x2f4e681brw4`. The lookahead is therefore
///   tested after each character is taken, including characters that are
///   themselves name-class.
/// * **A failed match consumes nothing.** Python resumes at the next byte, so a
///   junk `0x` in front of a real entry does not hide it.
/// * **The lookahead position is not consumed.** `finditer` resumes *at* the
///   `0x` that ended a name, which is the next entry's prefix — so a run of
///   entries with no separator parses correctly.
///
/// A name also has to be non-empty (`+?`, not `*?`), and `$` means the very end
/// of the text: a trailing space — which the printable filter *keeps* — is
/// neither `0x` nor end-of-text, and therefore defeats the final entry. That is a
/// quirk of the oracle's pattern, reproduced rather than repaired: a "fixed"
/// version would find names in blobs the reference does not.
pub fn scrape_pairs(text: &str) -> Vec<(u32, String)> {
    let bytes = text.as_bytes();
    let mut found = Vec::new();
    let mut at = 0usize;
    while at + 10 <= bytes.len() {
        if &bytes[at..at + 2] != b"0x" {
            at += 1;
            continue;
        }
        // `[0-9a-f]{8}` exactly: uppercase hex does not match, and nine or more
        // digits are consumed as eight digits plus a name that starts with a
        // digit.
        let Some(digits) = bytes.get(at + 2..at + 10).filter(|window| {
            window
                .iter()
                .all(|byte| byte.is_ascii_digit() || matches!(byte, b'a'..=b'f'))
        }) else {
            at += 1;
            continue;
        };
        let Ok(digits) = std::str::from_utf8(digits) else {
            at += 1;
            continue;
        };
        let Ok(type_id) = u32::from_str_radix(digits, 16) else {
            at += 1;
            continue;
        };

        let Some(name_end) = lazy_name_end(bytes, at + 10) else {
            at += 1;
            continue;
        };
        let name = text
            .get(at + 10..name_end)
            .filter(|name| !name.is_empty())
            .unwrap_or_default();
        found.push((type_id, name.to_owned()));
        // Resume *at* the lookahead: the `0x` there is the next entry's prefix.
        at = name_end;
    }
    found
}

/// The end of a lazy `[A-Za-z0-9_]+?` that is followed by `0x` or end-of-text.
///
/// Takes one name character at a time and tests the lookahead after each, which
/// is exactly what a backtracking engine does. `None` when no split satisfies
/// both conditions.
fn lazy_name_end(bytes: &[u8], from: usize) -> Option<usize> {
    let mut pos = from;
    while pos < bytes.len() {
        let byte = bytes[pos];
        if !(byte.is_ascii_alphanumeric() || byte == b'_') {
            // The group cannot take this byte, and the lookahead does not match
            // here either (it is not `0x`, and it is not the end).
            return None;
        }
        pos += 1;
        if pos == bytes.len() {
            return Some(pos); // `$`
        }
        if bytes[pos] == b'0' && bytes.get(pos + 1) == Some(&b'x') {
            return Some(pos); // `0x`
        }
    }
    // Ran out of input before the group was even one character long.
    None
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_prop_directory_key_is_group_and_instance_with_the_shared_word() {
        assert_eq!(PROP_DIRECTORY_GROUP, PROP_DIRECTORY_INSTANCE);
        assert_eq!(PROP_DIRECTORY_GROUP, 0x01c7_ac81);
    }

    #[test]
    fn the_scrape_finds_consecutive_entries() {
        // The oracle's lookahead means the `0x` that ends one name starts the
        // next, so a run of entries parses without a separator.
        assert_eq!(
            scrape_pairs("0x00e6bce5gmdl0x2f4e681brw40x2f4e681craster"),
            vec![
                (0x00e6_bce5, "gmdl".to_owned()),
                (0x2f4e_681b, "rw4".to_owned()),
                (0x2f4e_681c, "raster".to_owned()),
            ]
        );
    }

    #[test]
    fn a_name_that_is_not_followed_by_0x_or_the_end_does_not_match() {
        // The lazy name has to reach the next `0x` or the very end of the text.
        // A space ends the run and is neither, so nothing matches.
        assert!(scrape_pairs("0x00e6bce5gmdl and more text").is_empty());
        assert!(scrape_pairs("0x00e6bce5gmdl:rw4").is_empty());
    }

    #[test]
    fn a_trailing_space_defeats_the_final_entry_because_the_filter_keeps_it() {
        // `isprintable()` is false for a space, so `typescan.py` re-adds it --
        // and then `$` no longer matches the end of the filtered text. The
        // oracle therefore finds NOTHING in a blob whose last entry is followed
        // by a space. Reproduced rather than "fixed": a repaired version would
        // find names in blobs the reference does not.
        assert_eq!(printable_latin1(b"0x00e6bce5gmdl "), "0x00e6bce5gmdl ");
        assert!(scrape_pairs(&printable_latin1(b"0x00e6bce5gmdl ")).is_empty());
        // The same blob without the trailing space does parse.
        assert_eq!(
            scrape_pairs(&printable_latin1(b"0x00e6bce5gmdl")),
            vec![(0x00e6_bce5, "gmdl".to_owned())]
        );
    }

    #[test]
    fn a_one_character_name_at_the_very_end_is_a_match() {
        // `+?` is one-or-more, and `$` is the end of the text.
        assert_eq!(
            scrape_pairs("0x00e6bce5g"),
            vec![(0x00e6_bce5, "g".to_owned())]
        );
    }

    /// The oracle's own answers, taken from running `tools/spore/typescan.py`'s
    /// filter-and-regex pair under Python 3.
    ///
    /// This is the test that would catch a rewrite of [`scrape_pairs`] quietly
    /// diverging from the tool being ported, which no amount of self-consistent
    /// reasoning about the regex can do.
    #[test]
    fn the_scrape_matches_the_python_oracle_case_for_case() {
        /// One blob and the pairs the oracle's regex finds in it.
        type Case = (&'static [u8], &'static [(u32, &'static str)]);
        let cases: &[Case] = &[
            (
                b"0x00e6bce5gmdl0x2f4e681brw40x2f4e681craster",
                &[
                    (0x00e6_bce5, "gmdl"),
                    (0x2f4e_681b, "rw4"),
                    (0x2f4e_681c, "raster"),
                ],
            ),
            (b"0x00e6bce5gmdl and more text", &[]),
            (b"0x00e6bce5gmdl ", &[]),
            (b"0x00E6BCE5gmdl", &[]),
            (b"0X00e6bce5gmdl", &[]),
            (b"0x00e6bcegmdl", &[]),
            (b"0x00e6bce5g", &[(0x00e6_bce5, "g")]),
            (b"0xzz0x00e6bce5gmdl", &[(0x00e6_bce5, "gmdl")]),
            (
                b"0x00e6bce5gmdl_v80x2f4e681brw4",
                &[(0x00e6_bce5, "gmdl_v8"), (0x2f4e_681b, "rw4")],
            ),
        ];
        for (blob, expected) in cases {
            let text = printable_latin1(blob);
            let got: Vec<(u32, String)> = scrape_pairs(&text);
            let want: Vec<(u32, String)> = expected
                .iter()
                .map(|(id, name)| (*id, (*name).to_owned()))
                .collect();
            assert_eq!(got, want, "blob {:?}", String::from_utf8_lossy(blob));
        }
    }

    #[test]
    fn an_uppercase_or_short_hex_run_is_not_a_match() {
        // The oracle's class is `[0-9a-f]`: lowercase only, exactly eight.
        assert!(scrape_pairs("0x00E6BCE5gmdl").is_empty(), "uppercase hex");
        assert!(
            scrape_pairs("0X00e6bce5gmdl").is_empty(),
            "uppercase prefix"
        );
        assert!(scrape_pairs("0x00e6bcegmdl").is_empty(), "seven digits");
    }

    #[test]
    fn a_failed_match_does_not_consume_the_scan_so_an_inner_prefix_is_found() {
        // "0xzz0x00e6bce5gmdl": the first `0x` is followed by `zz`, which is not
        // eight hex digits, so it does not match -- and the scan must not skip
        // past it, or the real entry behind it would be lost.
        assert_eq!(
            scrape_pairs("0xzz0x00e6bce5gmdl"),
            vec![(0x00e6_bce5, "gmdl".to_owned())]
        );
    }

    #[test]
    fn digits_in_the_name_class_are_part_of_the_name() {
        assert_eq!(
            scrape_pairs("0x00e6bce5gmdl_v80x2f4e681brw4"),
            vec![
                (0x00e6_bce5, "gmdl_v8".to_owned()),
                (0x2f4e_681b, "rw4".to_owned()),
            ]
        );
    }

    #[test]
    fn an_empty_blob_yields_no_names_rather_than_a_panic() {
        assert!(scrape_pairs("").is_empty());
        assert!(scrape_pairs("0x").is_empty());
        assert!(scrape_pairs("0x00e6bce").is_empty());
    }

    #[test]
    fn the_printable_filter_drops_control_bytes_and_keeps_high_latin1() {
        // 0xc3 0xa9 is the *UTF-8* encoding of `\u{e9}`. Decoded as latin-1 --
        // which is what the oracle does -- it is two characters, `\u{c3}` and
        // `\u{a9}`. Getting this wrong is a real trap: a UTF-8-aware filter
        // would emit one character where the reference emits two.
        let text = printable_latin1(b"a\x01b\x1fc d\xc3\xa9");
        assert!(!text.contains('\u{1}'), "control byte must be dropped");
        assert!(!text.contains('\u{1f}'), "unit separator must be dropped");
        assert!(text.contains('a') && text.contains('b'));
        assert!(text.contains(' '), "space is re-added explicitly");
        assert_eq!(text, "abc d\u{c3}\u{a9}");
        // Python's `str.isprintable()` is a Unicode predicate, so high latin-1
        // letters survive the filter even though they are not ASCII.
        assert!(is_python_printable('\u{c3}') && is_python_printable('\u{a9}'));
    }

    #[test]
    fn ranking_is_by_count_then_by_first_appearance() {
        let ranked = rank_types([7, 7, 7, 3, 9, 3, 9].into_iter());
        assert_eq!(ranked[0], (7, 3), "the most frequent leads");
        // 3 and 9 both have count 2; 3 was first seen at position 3, 9 at 4.
        assert_eq!(ranked[1], (3, 2));
        assert_eq!(ranked[2], (9, 2));
    }

    #[test]
    fn ranking_a_stable_counter_matches_python_most_common_order() {
        // `collections.Counter` + `most_common` on this input: 1 first (count 3),
        // then the equal-count pair in first-appearance order.
        let ranked = rank_types([1, 2, 1, 3, 1, 2].into_iter());
        assert_eq!(ranked, vec![(1, 3), (2, 2), (3, 1)]);
    }
}
