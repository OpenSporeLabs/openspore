//! # spore-cellcontent — the Cell stage's gameplay configuration records
//!
//! Twelve record types that decide **what exists in the Cell stage and how it
//! behaves**: which cell species there are, what a level looks like, what spawns
//! where, what a cell eats when it is eaten, and how its appearance is chosen.
//! They are configuration, not geometry, and nothing here touches a mesh.
//!
//! ```text
//!   spore-dbpf / spore-assets   record bytes, by (type, group, instance)
//!        |
//!  spore-cellcontent   <-- THIS CRATE: flat decoders, 26 typed reference
//!        |               fields, a catalogue, and the domain invariants
//!        v
//!   spore-engine       (not yet: no consumer is wired up)
//! ```
//!
//! The library takes **bytes**, not packages. It has no container knowledge, no
//! Bevy dependency and no game-install requirement, so every decoder in it is
//! testable with a synthetic buffer. `spore-assets` supplies the bytes; the
//! `#[ignore]`d real-corpus tests in `tests/real_corpus.rs` are the only place a
//! package is opened, and they are dev-dependencies only.
//!
//! # All twelve records are flat, and that is measured, not assumed
//!
//! There is **no `CellSerializer` envelope**. The C++ reference names a
//! `CellSerializer` in its comments and then reads `gameMode` at offset 0; the
//! Python oracles read the same offsets. If an envelope existed, every field of
//! every record would be shifted by its size and none would decode to a plausible
//! value. All of them do.
//!
//! | record | type id | extent |
//! |---|---|---|
//! | [`globals`](globals) | `0x2A3CE5B7` | **fixed** 276 B, 69 fields |
//! | [`effectMap`](maps) | `0x433FB70C` | 8 B header + n × 28 |
//! | [`backgroundMap`](maps) | `0x612B3191` | 8 B header + n × 16 |
//! | [`structure`](structure) | `0x4B9EF6DC` | 28 B header + n × 40 |
//! | [`world`](world) | `0x9B8E862F` | 16 B header + nPop × 12 + nAdv × 24 |
//! | [`randomCreature`](spawn) | `0xF9C3D770` | 8 B header + n × 28 |
//! | [`powers`](spawn) | `0x754BE343` | **fixed** 8 B |
//! | [`look_table`](look) | `0x8C042499` | 8 B header + n × 8 |
//! | [`look_algorithm`](look) | `0xDBA35AE2` | 8 B header + n × 20 |
//! | [`lootTable`](loot) | `0xD92AF091` | 36 B header (3 pad bytes) + n × 28 |
//! | [`populate`](populate) | `0xDA141C1B` | 16 B header + n × 76 |
//! | [`cell`](cell) | `0xDFAD9F51` | **fixed** 796 B, `cAIData` at 224/404/584 |
//!
//! The `globals` extent is the 276-byte revision. See "Two findings" below.
//!
//! ## Every counted record is exact-fit
//!
//! **The premise that only two of them require the count to fill the record is
//! not borne out by either reference.** Measured over `Spore_Game`,
//! `Spore_EP1_Data` and `PatchData`:
//!
//! * every Python oracle that decodes a counted record writes
//!   `if len(blob) != header + n * stride: raise` — exact;
//! * the C++ reference's *binding* check is `spanMatches` (exact) for every
//!   record it decodes. `countFits` (fits-only) appears twice and is **redundant
//!   in both places**: `lootTable`'s early `countFits` at offset 8 is implied by
//!   its later `spanMatches` at offset 36, and `world`'s `countFits` on
//!   `numPopulate` is followed by an equality check on the total.
//!
//! So [`SpanRule::FitsOnly`] is defined and published per record but **no record
//! in this family takes it**. It exists so the question has one answer per record
//! and so that a future record which genuinely tolerates a remainder is a
//! deliberate, visible choice rather than an accident. Each record type exports
//! its own `SPAN_RULE`, and `tests/decode.rs` pins all twelve.
//!
//! # Where the two references disagree
//!
//! Five disagreements were found between `src/assets/CellResource.{hpp,cpp}` and
//! `tools/spore/cellres/*.py`. None changes a decode outcome; all five are
//! domain bounds, where the Python oracle holds the corpus-derived bound and the
//! C++ holds a looser envelope around it. This crate follows **Python** every
//! time, because the repository's rule is that the corpus outranks the port.
//!
//! | # | field | C++ | Python | followed | why |
//! |---|---|---|---|---|---|
//! | 1 | `populate.scale` | `scale > 10` | `scale not in (0,1,2,3,4)` | Python | closed observed set vs. an interval no record reaches |
//! | 2 | `lootTable` header floats | all five in `0..=1000` | `minRadius`/`maxRadius`/`delay` in `0..=10`, `initialAlpha` in `0..=2`, `expelForce` in `0..=100` | Python | per-field observed ranges |
//! | 3 | `cell` one-byte flags | stored as `bool`, so the raw byte is destroyed | required to be `0` or `1` | Python | this crate keeps the bytes as `u8`, which is what makes the invariant expressible at all |
//! | 4 | `cell` `sizeMin`/`sizeMax` | `sizeMin < 0 or sizeMin > 10 or sizeMin > sizeMax`, which **accepts NaN** | `0.0 <= sizeMin <= 10.0`, which rejects it | Python | an accepted NaN is a value no rule in either reference can then constrain |
//! | 5 | `globals` domains | **none at all** — `parseCellGlobals` has no `issues` counterpart | `cellres.py::validate` bounds 7 enums at `<= 8`, 2 counts at `<= 1024`, and every float at `abs(v) <= 1e6` | Python | the C++ simply has no checker here |
//! | 6 | `globals.startingCellKey` | grouped with `startCell` and emitted as a `0xDFAD9F51` | called a `ResourceKey` reference in a comment, but never resolved | **neither** | the corpus says the C++ is wrong: see below |
//!
//! # Two findings that are not disagreements but gaps
//!
//! Both were measured on a stock install on 2026-10-04 and both are pinned by
//! `#[ignore]`d tests in `tests/real_corpus.rs`.
//!
//! ## 1. The globals record has **two revisions** in one install
//!
//! `0x2A3CE5B7:0x00000000:0xA426730B` exists in three packages:
//!
//! | package | length |
//! |---|---|
//! | `Spore/Data/Spore_Game.package` | **264** bytes |
//! | `SPORE/Data/PatchData.package` | 276 bytes |
//! | `SPORE/DataEP1/Spore_EP1_Data.package` | 276 bytes (byte-identical to `PatchData`) |
//!
//! A word-level alignment shows the short copy is **not** a truncation and **not**
//! a shift: it is the same record with exactly **three fields absent** —
//! `gameMode` (@0), `startingCellKey` (@56) and `controlMethod` (@212) — and every
//! other word is byte-identical. So `cCellGlobalsResource` grew by three fields
//! between the base game and the expansion pack, and the three it gained are all
//! "which mode / which cell / which control scheme" selectors.
//!
//! Neither reference records this. `src/assets/CellResource.hpp` says the record
//! "lives in `SPORE/DataEP1/Spore_EP1_Data.package`", which is true of that package
//! and silent about the other two, and `tools/spore/cellres/cellres.py` only ever
//! loads the EP1 copy so its `size=276 fields=69 violations=0` line never sees the
//! base revision.
//!
//! **Operational consequence.** `spore_assets::ContentStore` resolves first match
//! wins, so a caller that loads base content before its patches resolves this
//! record to the **264-byte** copy and gets a typed
//! [`CellContentError::ExtentMismatch`]. That is the right answer — padding 264 to
//! 276 would fabricate three fields — and the fix is the package order, not the
//! decoder. [`globals::decode`] never guesses.
//!
//! ## 2. `globals.startingCellKey` does **not** name a cell record
//!
//! The C++ reference emits it as a `cCellCellResource` instance. Measured:
//! `startCell` at +52 is `0xCBcd1287`, a real cell instance present in all three
//! packages; `startingCellKey` at +56 is `0xA1C46DF2`, which the DBPF index holds
//! as a **`prop`** (`0x00B1B104`) and not as a cell at all.
//!
//! So this crate models it as a bare instance id with **no type word** — the same
//! treatment as `cell.break` — which makes it a reference non-finding rather than a
//! lookup that must fail. It shares [`CellReferenceField::GlobalsCell`] with
//! `startCell` and is told apart by index (0 and 1), so the field count stays at
//! **26**. See [`globals::GLOBALS_REFERENCE_FIELDS`].
//!
//! # Honesty: an observation and a meaning are two claims
//!
//! For this family that distinction is not decoration. A gameplay record is full
//! of fields the corpus constrains but nobody has named, and the temptation is to
//! report "field 208 = 0" when what is actually known is "nobody knows what field
//! 208 selects".
//!
//! * A field whose **position and width** are verified is `OBSERVED` — we read the
//!   value.
//! * A field whose **meaning** is not established is
//!   [`spore_core::Fact::unavailable`], with a closed reason code. It is never a
//!   zero, an empty string or a default.
//!
//! [`claims`] holds the whole table with a grade and a written basis per subject,
//! and `tests/honesty.rs` asserts the recorded grade equals the documented one.
//! The three cases this crate was built around:
//!
//! * [`claims::DEAD_MARKER_FIELD`] — four `cMarker` fields read zero on all 387
//!   markers. Observed; meaning not established.
//! * [`claims::ATTACHMENT_STRUCTURE_FIELD`] — `cSPAttachment.structure` is zero
//!   everywhere. Observed; meaning not established.
//! * [`claims::LOOT_HEADER_PADDING`] — three bytes at +29..+32. Read into
//!   [`loot::CellLootTable::header_padding`] rather than skipped, so a non-zero
//!   byte is an observable [`issue::IssueKind::PaddingNonZero`], and still named
//!   as not interpreted.
//!
//! # A reference that resolves to nothing is a non-finding
//!
//! [`CellReferenceField`] enumerates the **26** reference fields. They are typed,
//! because the type of the target is part of the claim, and they resolve into
//! three outcomes rather than two:
//!
//! * **resolved** — a catalogue record has that `(type, instance)`;
//! * **unresolved** — the field says what it wants and the catalogue lacks it,
//!   reported as [`CellReferenceError::NotFound`];
//! * **non-finding** — the field does not say what it wants. Eleven of the 26 store
//!   a bare instance id with **no type word** ([`ReferenceTarget::Untyped`]), and
//!   one (`world.advect.advectID`) names type `0x04805684`, outside this family.
//!   Both are reported through
//!   [`CellReferenceError::is_non_finding`] rather than as a missing record,
//!   because asserting "we looked and it is not there" about a field that never
//!   said what to look for is a fabricated negative.
//!
//! Measured on a stock install (2026-10-04), the twelve records emit **1135**
//! references: **821 resolved**, **1 unresolved**
//! (`globals.startCell` -> a cell instance the three packages do not hold), and
//! **313 non-findings** — 296 untyped fields and 17 advect flow fields.
//!
//! [`CellRandomCreatureEntry::creature_id`] is deliberately **not** a reference:
//! `tools/spore/cellres/randcreature.py` states it is a soft id that is absent from
//! every package, and resolving it would be inventing a target.
//!
//! # Example
//!
//! ```
//! use spore_cellcontent::{decode, is_supported, CellContentRecord, CellReferenceField};
//! use spore_core::ResourceKey;
//!
//! # fn main() -> Result<(), Box<dyn std::error::Error>> {
//! // 796 zero bytes are a syntactically valid `cell` record: every field is a
//! // zero, which is in domain for most of them but not for all (see
//! // `spore_cellcontent::issue::cell_issues`).
//! let bytes = vec![0u8; 796];
//! assert!(is_supported(0xDFAD9F51));
//! let content = decode(0xDFAD9F51, &bytes)?;
//! assert!(matches!(content, spore_cellcontent::CellContent::Cell(_)));
//!
//! // A record holding zero references emits none: 0 means "no target", which is
//! // not the same as a reference to instance 0.
//! let record = CellContentRecord::new(ResourceKey::new(0xDFAD9F51, 0, 1), content);
//! assert!(record.references().iter().all(|r| r.instance != 0));
//! assert!(CellReferenceField::CellLoot.declares_type());
//! # Ok(())
//! # }
//! ```

#![forbid(unsafe_code)]
#![warn(missing_debug_implementations)]

pub mod cell;
pub mod claims;
pub mod error;
pub mod globals;
pub mod issue;
pub mod look;
pub mod loot;
pub mod maps;
pub mod populate;
pub mod reader;
pub mod reference;
pub mod scalar;
pub mod spawn;
pub mod structure;
pub mod world;

/// The record type id of a cell record, re-exported from [`cell`].
pub use cell::CELL_TYPE;
pub use cell::{CellAi, CellCell, CellEatData};
pub use error::{CellContentError, CellContentErrorKind, CellReferenceError};
pub use globals::{CellGlobals, GlobalsFieldSpec, GLOBALS_FIELD_COUNT, GLOBALS_SIZE, GLOBALS_TYPE};
pub use issue::{
    background_map_issues, cell_issues, effect_map_issues, globals_issues, look_algorithm_issues,
    look_table_issues, loot_table_issues, populate_issues, powers_issues, random_creature_issues,
    structure_issues, validate_catalogue, world_issues, CatalogueIssue, CellIssue, IssueConfidence,
    IssueKind, IssueValue, RECORD_LEVEL,
};
pub use look::{
    CellLookAlgorithm, CellLookAlgorithmEntry, CellLookEntry, CellLookTable, LOOK_ALGORITHM_TYPE,
    LOOK_TABLE_TYPE,
};
pub use loot::{CellLootEntry, CellLootTable, LOOT_TABLE_TYPE};
pub use maps::{
    background_color_envelope, sample_background_color, CellBackgroundMap, CellBackgroundMapEntry,
    CellEffectMap, CellEffectMapEntry,
};
pub use maps::{BACKGROUND_MAP_TYPE, EFFECT_MAP_TYPE};
pub use populate::{CellMarker, CellPopulate, POPULATE_TYPE};
pub use reader::SpanRule;
pub use reference::{
    CellCatalogue, CellContentRecord, CellInstanceIndex, CellReference, CellReferenceField,
    CellReferenceResolver, ReferenceTarget,
};
pub use scalar::{FieldKind, Scalar};
pub use spawn::{
    CellPowers, CellRandomCreature, CellRandomCreatureEntry, POWERS_TYPE, RANDOM_CREATURE_TYPE,
};
/// Re-exported so a consumer needs only this crate to name a record identity,
/// a wildcard or an evidence grade.
pub use spore_core::{EvidenceLevel, EvidenceState, Fact, Provenance, ResourceKey, WILDCARD};
pub use structure::{CellStructure, CellStructureAttachment, STRUCTURE_TYPE};
pub use world::{CellAdvectEntry, CellLevelEntry, CellWorld, WORLD_TYPE};

/// Every record type in this family, in the order [`CellContent`] declares its
/// variants. 12 entries.
pub const SUPPORTED_TYPES: [u32; 12] = [
    GLOBALS_TYPE,
    maps::EFFECT_MAP_TYPE,
    maps::BACKGROUND_MAP_TYPE,
    structure::STRUCTURE_TYPE,
    world::WORLD_TYPE,
    spawn::RANDOM_CREATURE_TYPE,
    spawn::POWERS_TYPE,
    look::LOOK_TABLE_TYPE,
    look::LOOK_ALGORITHM_TYPE,
    loot::LOOT_TABLE_TYPE,
    populate::POPULATE_TYPE,
    cell::CELL_TYPE,
];

/// One decoded cell-stage gameplay record.
///
/// The variant order is the C++ reference's
/// `openspore::assets::CellContentValue`, and it is load-bearing: the reference
/// layer and the manifest both key off it, so reordering would silently change
/// which type an index corresponds to.
///
/// # Why the variants are not boxed
///
/// The largest, `Cell`, is 640 bytes — three inline 180-byte `cAIData` blocks —
/// while most others are one `Vec` behind a header. Clippy's
/// `large_enum_variant` fires on that gap and is deliberately allowed here.
/// Boxing would replace one move of 640 bytes with one heap allocation per
/// decoded record, and these records are built once, stored in a
/// [`CellContentRecord`] and thereafter read **by reference** by the catalogue,
/// the resolver and the checkers. The enum is moved twice in its whole life
/// (out of `decode`, into `CellContentRecord::new`) and never copied on a hot
/// path, so the allocation would be a permanent cost against a saving that never
/// materialises.
#[allow(clippy::large_enum_variant)]
#[derive(Debug, Clone, PartialEq)]
pub enum CellContent {
    /// `cCellGlobalsResource`.
    Globals(CellGlobals),
    /// `cCellEffectMapResource`.
    EffectMap(CellEffectMap),
    /// `cCellBackgroundMapResource`.
    BackgroundMap(CellBackgroundMap),
    /// `cCellStructureResource`.
    Structure(CellStructure),
    /// `cCellWorldResource`.
    World(CellWorld),
    /// `cCellRandomCreatureResource`.
    RandomCreature(CellRandomCreature),
    /// `cCellPowersResource`.
    Powers(CellPowers),
    /// `cCellLookTableResource`.
    LookTable(CellLookTable),
    /// `cCellLookAlgorithmResource`.
    LookAlgorithm(CellLookAlgorithm),
    /// `cCellLootTableResource`.
    LootTable(CellLootTable),
    /// `cCellPopulateResource`.
    Populate(CellPopulate),
    /// `cCellCellResource`.
    Cell(CellCell),
}

/// Whether `type_id` is one of the twelve records this crate decodes.
///
/// The single authority. A `gmdl` or a `raster` is a real record that is not a
/// cell-content record, and conflating the two is exactly what
/// [`CellContentError::UnsupportedType`] exists to prevent.
pub const fn is_supported(type_id: u32) -> bool {
    matches!(
        type_id,
        GLOBALS_TYPE
            | maps::EFFECT_MAP_TYPE
            | maps::BACKGROUND_MAP_TYPE
            | structure::STRUCTURE_TYPE
            | world::WORLD_TYPE
            | spawn::RANDOM_CREATURE_TYPE
            | spawn::POWERS_TYPE
            | look::LOOK_TABLE_TYPE
            | look::LOOK_ALGORITHM_TYPE
            | loot::LOOT_TABLE_TYPE
            | populate::POPULATE_TYPE
            | cell::CELL_TYPE
    )
}

/// Decodes one cell-content record from its bytes.
///
/// `type_id` must be one of [`SUPPORTED_TYPES`]. The bytes are the
/// **decompressed** record payload, which is what `spore-dbpf` produces; this
/// crate knows nothing about compression.
///
/// A `global_issues`-style domain check is a separate step, deliberately: a
/// record that decodes and a record that is *sane* are different questions, and
/// [`CellContent::issues`] asks the second one.
pub fn decode(type_id: u32, bytes: &[u8]) -> Result<CellContent, CellContentError> {
    Ok(match type_id {
        GLOBALS_TYPE => CellContent::Globals(globals::decode(bytes)?),
        maps::EFFECT_MAP_TYPE => CellContent::EffectMap(maps::decode_effect_map(bytes)?),
        maps::BACKGROUND_MAP_TYPE => {
            CellContent::BackgroundMap(maps::decode_background_map(bytes)?)
        }
        structure::STRUCTURE_TYPE => CellContent::Structure(structure::decode(bytes)?),
        world::WORLD_TYPE => CellContent::World(world::decode(bytes)?),
        spawn::RANDOM_CREATURE_TYPE => {
            CellContent::RandomCreature(spawn::decode_random_creature(bytes)?)
        }
        spawn::POWERS_TYPE => CellContent::Powers(spawn::decode_powers(bytes)?),
        look::LOOK_TABLE_TYPE => CellContent::LookTable(look::decode_table(bytes)?),
        look::LOOK_ALGORITHM_TYPE => CellContent::LookAlgorithm(look::decode_algorithm(bytes)?),
        loot::LOOT_TABLE_TYPE => CellContent::LootTable(loot::decode(bytes)?),
        populate::POPULATE_TYPE => CellContent::Populate(populate::decode(bytes)?),
        cell::CELL_TYPE => CellContent::Cell(cell::decode(bytes)?),
        _ => return Err(CellContentError::UnsupportedType { type_id }),
    })
}

/// Decodes a record and pairs it with its identity in one step.
pub fn decode_record(
    key: spore_core::ResourceKey,
    bytes: &[u8],
) -> Result<CellContentRecord, CellContentError> {
    let value = decode(key.type_id, bytes)?;
    Ok(CellContentRecord::new(key, value))
}

impl CellContent {
    /// This record's type word.
    pub const fn type_id(&self) -> u32 {
        match self {
            Self::Globals(_) => GLOBALS_TYPE,
            Self::EffectMap(_) => maps::EFFECT_MAP_TYPE,
            Self::BackgroundMap(_) => maps::BACKGROUND_MAP_TYPE,
            Self::Structure(_) => structure::STRUCTURE_TYPE,
            Self::World(_) => world::WORLD_TYPE,
            Self::RandomCreature(_) => spawn::RANDOM_CREATURE_TYPE,
            Self::Powers(_) => spawn::POWERS_TYPE,
            Self::LookTable(_) => look::LOOK_TABLE_TYPE,
            Self::LookAlgorithm(_) => look::LOOK_ALGORITHM_TYPE,
            Self::LootTable(_) => loot::LOOT_TABLE_TYPE,
            Self::Populate(_) => populate::POPULATE_TYPE,
            Self::Cell(_) => cell::CELL_TYPE,
        }
    }

    /// The canonical name `spore-core` has for this type, or `None`.
    ///
    /// `None` is a non-finding: two of the twelve ids (`globals` `0x2A3CE5B7` and
    /// `effectMap` `0x433FB70C`) are **not** in the transcribed `typenames.json`
    /// table, and nothing is invented for them. See `spore_core::record::TYPE_NAMES`.
    pub fn type_name(&self) -> Option<&'static str> {
        spore_core::record::RecordType::new(self.type_id()).name()
    }

    /// Every graded claim that applies to this record's type.
    ///
    /// `None` means *this record type does not carry that subject*, which is a
    /// third state distinct from [`spore_core::Fact::unavailable`] ("this record
    /// type carries it, and we looked and found nothing").
    pub fn claim(&self, subject: &'static str) -> Option<spore_core::Fact<&'static str>> {
        use CellContent as C;
        match self {
            C::Globals(globals) => globals.claim(subject),
            C::Cell(cell) => cell.claim(subject),
            C::Structure(structure) => structure_claim(structure, subject),
            C::RandomCreature(random_creature) => random_creature_claim(random_creature, subject),
            _ => generic_claim(self.type_id(), subject),
        }
    }
}

fn structure_claim(
    structure: &CellStructure,
    subject: &'static str,
) -> Option<spore_core::Fact<&'static str>> {
    match subject {
        claims::STRUCTURE_LAYOUT => Some(claims::graded(
            claims::STRUCTURE_LAYOUT,
            claims::PROV_CELLSTRUCT_ORACLE,
            "28-byte header then 40-byte cSPAttachment rows",
        )),
        claims::EFFECT_ID_REGISTRY => Some(structure.attachments.first().map_or_else(
            || claims::non_finding(claims::EFFECT_ID_REGISTRY),
            |attachment| attachment.effect_id_meaning(),
        )),
        claims::ATTACHMENT_STRUCTURE_FIELD => Some(structure.attachments.first().map_or_else(
            || claims::non_finding(claims::ATTACHMENT_STRUCTURE_FIELD),
            |attachment| attachment.structure_meaning(),
        )),
        _ => None,
    }
}

fn random_creature_claim(
    random_creature: &CellRandomCreature,
    subject: &'static str,
) -> Option<spore_core::Fact<&'static str>> {
    match subject {
        claims::RANDOM_CREATURE_LAYOUT => Some(claims::graded(
            claims::RANDOM_CREATURE_LAYOUT,
            claims::PROV_RANDCREATURE_ORACLE,
            "8-byte header then 28-byte rows",
        )),
        claims::CREATURE_ID_REGISTRY => Some(random_creature.entries.first().map_or_else(
            || claims::non_finding(claims::CREATURE_ID_REGISTRY),
            |entry| entry.creature_id_meaning(),
        )),
        _ => None,
    }
}

/// The claims that depend only on the record's type, not on its contents.
fn generic_claim(type_id: u32, subject: &'static str) -> Option<spore_core::Fact<&'static str>> {
    let (subject, basis, value) = match (type_id, subject) {
        (_, claims::SERIALIZER_ENVELOPE_ABSENT) => (
            claims::SERIALIZER_ENVELOPE_ABSENT,
            claims::PROV_CELLRES_ORACLE,
            "no name/id envelope precedes the fields",
        ),
        (_, claims::SPAN_RULE_ALL_EXACT_FIT) => (
            claims::SPAN_RULE_ALL_EXACT_FIT,
            claims::PROV_CELLRESOURCE_CPP,
            "every counted record uses SpanRule::ExactFit",
        ),
        (maps::EFFECT_MAP_TYPE, claims::EFFECT_MAP_LAYOUT) => (
            claims::EFFECT_MAP_LAYOUT,
            claims::PROV_CELLEFFECTMAP_ORACLE,
            "8-byte header then 28-byte rows",
        ),
        (maps::EFFECT_MAP_TYPE, claims::EFFECT_MAP_FIELD_MEANING) => {
            return Some(claims::non_finding(claims::EFFECT_MAP_FIELD_MEANING))
        }
        (maps::BACKGROUND_MAP_TYPE, claims::BACKGROUND_MAP_LAYOUT) => (
            claims::BACKGROUND_MAP_LAYOUT,
            claims::PROV_CELLEFFECTMAP_ORACLE,
            "8-byte header then 16-byte rows",
        ),
        (maps::BACKGROUND_MAP_TYPE, claims::BACKGROUND_RAMP_IS_RGB) => (
            claims::BACKGROUND_RAMP_IS_RGB,
            claims::PROV_CELLLOOK_ORACLE,
            "r/g/b in 0..=1 across all 12 stops",
        ),
        (maps::BACKGROUND_MAP_TYPE, claims::BACKGROUND_LADDER_IS_GEOMETRIC) => (
            claims::BACKGROUND_LADDER_IS_GEOMETRIC,
            claims::PROV_CELLEFFECTMAP_ORACLE,
            "12 stops at a factor of about 3.33",
        ),
        (world::WORLD_TYPE, claims::WORLD_LAYOUT) => (
            claims::WORLD_LAYOUT,
            claims::PROV_CELLWORLD_ORACLE,
            "16-byte header then 12- and 24-byte rows",
        ),
        (world::WORLD_TYPE, claims::ADVECT_FLOAT_OVERRIDES_SDK_INT) => (
            claims::ADVECT_FLOAT_OVERRIDES_SDK_INT,
            claims::PROV_CELLWORLD_ORACLE,
            "strength/variance/period read as <f, not <i",
        ),
        (world::WORLD_TYPE, claims::ADVERT_FLOW_FIELD_TYPE) => {
            return Some(claims::non_finding(claims::ADVERT_FLOW_FIELD_TYPE))
        }
        (world::WORLD_TYPE, claims::WORLD_POPULATE_RESOLUTION_UNMEASURED) => (
            claims::WORLD_POPULATE_RESOLUTION_UNMEASURED,
            claims::PROV_CELLCONTENT_CPP,
            "resolved by the reference layer, not asserted by world_issues",
        ),
        (populate::POPULATE_TYPE, claims::POPULATE_LAYOUT) => (
            claims::POPULATE_LAYOUT,
            claims::PROV_CELLPOP_ORACLE,
            "16-byte header then 76-byte cMarker rows",
        ),
        (loot::LOOT_TABLE_TYPE, claims::LOOT_LAYOUT) => (
            claims::LOOT_LAYOUT,
            claims::PROV_CELLLOOT_ORACLE,
            "36-byte header then 28-byte rows",
        ),
        (loot::LOOT_TABLE_TYPE, claims::LOOT_HEADER_PADDING) => {
            return Some(claims::non_finding(claims::LOOT_HEADER_PADDING))
        }
        (look::LOOK_TABLE_TYPE | look::LOOK_ALGORITHM_TYPE, claims::LOOK_LAYOUT) => (
            claims::LOOK_LAYOUT,
            claims::PROV_CELLLOOK_ORACLE,
            "8-byte header then 8- or 20-byte rows",
        ),
        (spawn::POWERS_TYPE, claims::POWERS_LAYOUT) => (
            claims::POWERS_LAYOUT,
            claims::PROV_RANDCREATURE_ORACLE,
            "exactly 8 bytes: i32 teleportCost + f32 teleportRange",
        ),
        _ => return None,
    };
    Some(claims::graded(subject, basis, value))
}
