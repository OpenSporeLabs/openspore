//! Every claim this crate records, with the grade it is recorded at.
//!
//! # The distinction this module is built around
//!
//! For a gameplay-configuration record the interesting questions are rarely
//! "how many bytes is this field". They are:
//!
//! * *where is it and how wide is it* — an **observation**, `OBSERVED`, because
//!   the bytes are there and were read;
//! * *what does it mean* — often a **non-finding**, `Fact::unavailable`, because
//!   the corpus constrains a field's values without naming it.
//!
//! Those are two different statements and both belong in the crate. Collapsing
//! them is how a decoder ends up reporting "this record says 0" when what it
//! actually knows is "this build has never established what this field is".
//! [`ClaimKind`] keeps the two apart and [`ALL_CLAIMS`] states, per subject,
//! which one a subject is and why.
//!
//! [`ALL_CLAIMS`] is the single table of (subject, grade, basis). `tests/honesty.rs`
//! asserts that every graded claim's `Fact` level equals [`grade_of`] for its
//! subject and that every non-finding is `UNKNOWN` + `MISSING` + provenance-free,
//! so the grade a caller reads and the grade this module documents cannot drift
//! apart.
//!
//! # What is *not* here
//!
//! No prose about how the Cell stage plays. The reference implementation's
//! semantics were never fully recovered — `docs/CELLSTAGE-RECON.md` §5 grades
//! cell movement `APPROXIMATION` and the eat/flee rules `INFERRED` — and this
//! crate reads records. It does not simulate them.

use spore_core::evidence::{EvidenceLevel, EvidenceState, Fact, Provenance};

// ---------------------------------------------------------------------------
// Subjects: layout and encoding
// ---------------------------------------------------------------------------

/// There is no `CellSerializer` envelope in front of any of the twelve records.
pub const SERIALIZER_ENVELOPE_ABSENT: &str = "serializer_envelope_absent";

/// The `globals` layout: 69 four-byte fields ending exactly at byte 276.
pub const GLOBALS_LAYOUT: &str = "globals_layout";

/// The `globals` field names come from the SDK struct, not from this crate.
pub const GLOBALS_FIELD_NAMES: &str = "globals_field_names";

/// The `cell` layout: 796 bytes with `cAIData` at 224/404/584.
pub const CELL_LAYOUT: &str = "cell_layout";

/// The `cell` `name` field is `wchar16[80]` + `u32 localeInstanceID`.
pub const CELL_NAME_ENCODING: &str = "cell_name_encoding";

/// How UTF-16 surrogate pairs in a cell name are handled.
pub const AI_SURROGATE_PAIRING: &str = "cell_name_surrogate_pairing";

/// The `world` layout: 16-byte header then 12- and 24-byte rows.
pub const WORLD_LAYOUT: &str = "world_layout";

/// `world` advect `strength`/`variance`/`period` are stored as `f32` although the
/// SDK types them `int`.
pub const ADVECT_FLOAT_OVERRIDES_SDK_INT: &str = "advect_stored_as_float_overrides_sdk_int";

/// The record type an advect entry's `advectID` names.
pub const ADVERT_FLOW_FIELD_TYPE: &str = "advect_id_type";

/// The `populate` layout: 16-byte header then 76-byte `cMarker` rows.
pub const POPULATE_LAYOUT: &str = "populate_layout";

/// The `structure` layout: 28-byte header then 40-byte `cSPAttachment` rows.
pub const STRUCTURE_LAYOUT: &str = "structure_layout";

/// The `lootTable` layout: 36-byte header (with three pad bytes) then 28-byte rows.
pub const LOOT_LAYOUT: &str = "loot_table_layout";

/// What the three pad bytes at +29..+32 of the loot-table header are.
pub const LOOT_HEADER_PADDING: &str = "loot_table_header_padding_meaning";

/// The `look_table` / `look_algorithm` layouts.
pub const LOOK_LAYOUT: &str = "look_layout";

/// The `randomCreature` layout: 8-byte header then 28-byte rows.
pub const RANDOM_CREATURE_LAYOUT: &str = "random_creature_layout";

/// The `powers` layout: exactly eight bytes.
pub const POWERS_LAYOUT: &str = "powers_layout";

/// The `effectMap` layout: 8-byte header then 28-byte rows.
pub const EFFECT_MAP_LAYOUT: &str = "effect_map_layout";

/// The `backgroundMap` layout: 8-byte header then 16-byte rows.
pub const BACKGROUND_MAP_LAYOUT: &str = "background_map_layout";

/// Every counted record in this family is exact-fit.
pub const SPAN_RULE_ALL_EXACT_FIT: &str = "every_counted_record_is_exact_fit";

/// The globals record exists in two revisions in one stock install.
pub const GLOBALS_HAS_TWO_REVISIONS: &str = "globals_has_two_revisions";

// ---------------------------------------------------------------------------
// Subjects: what a field means, or does not
// ---------------------------------------------------------------------------

/// What `globals.field_208` means.
pub const GLOBALS_FIELD_208_MEANING: &str = "globals_field_208_meaning";

/// Whether `globals.startingCellKey` names a cell record.
pub const GLOBALS_STARTING_CELL_KEY_IS_A_REFERENCE: &str =
    "globals_starting_cell_key_is_a_reference";

/// What the `cAIData.movementStyle` bitfield's bits mean.
pub const AI_MOVEMENT_STYLE_MEANING: &str = "ai_movement_style_meaning";

/// What the `cAIData.food` value means.
pub const AI_FOOD_MEANING: &str = "ai_food_meaning";

/// What the four dead `cMarker` fields are.
pub const DEAD_MARKER_FIELD: &str = "populate_marker_dead_field";

/// What an attachment's `structure` slot would name.
pub const ATTACHMENT_STRUCTURE_FIELD: &str = "attachment_structure_field";

/// What a soft effect id names.
pub const EFFECT_ID_REGISTRY: &str = "effect_id_registry";

/// A negative `effectID` is not a reference, however it is cast.
pub const NEGATIVE_EFFECT_ID_IS_NOT_A_REFERENCE: &str = "negative_effect_id_is_not_a_reference";

/// What a random-creature entry's `creatureID` names.
pub const CREATURE_ID_REGISTRY: &str = "creature_id_registry";

/// What the five positional fields of a `cEffectMapEntry` mean.
pub const EFFECT_MAP_FIELD_MEANING: &str = "effect_map_positional_field_meaning";

/// A `cBackgroundMapEntry`'s RGB triple is a background colour ramp.
pub const BACKGROUND_RAMP_IS_RGB: &str = "background_map_entry_is_rgb";

/// A background-map row's `field_c` values form a geometric ladder.
pub const BACKGROUND_LADDER_IS_GEOMETRIC: &str = "background_map_field_c_is_geometric";

/// A reference field that stores an instance id with no type word.
pub const REFERENCE_TYPE_WORD_ABSENT: &str = "reference_field_has_no_type_word";

/// `world.populate[i].populate` is a hard reference that no oracle measured.
pub const WORLD_POPULATE_RESOLUTION_UNMEASURED: &str =
    "world_populate_reference_resolution_unmeasured";

// ---------------------------------------------------------------------------
// Reason codes — the closed vocabulary of `Fact::unavailable`
// ---------------------------------------------------------------------------

/// A field whose value has been observed but whose *meaning* nobody
/// established. A value being constant is not evidence about what it is.
pub const MEANING_NOT_ESTABLISHED: &str = "meaning_not_established";

/// The field reads as zero on every observed record and is not decoded.
pub const DEAD_FIELD_OBSERVED_ZERO: &str = "dead_field_observed_zero";

/// The bytes are alignment padding that this build does not interpret.
pub const PADDING_NOT_INTERPRETED: &str = "padding_not_interpreted";

/// No registry maps a soft creature id to a creature.
pub const NO_CREATURE_REGISTRY: &str = "no_creature_registry";

/// No registry maps a soft effect id to an effect.
pub const NO_EFFECT_REGISTRY: &str = "no_effect_registry";

/// The record stores an instance id and no type word, so the reference names no
/// record type to look up.
pub const NO_TYPE_WORD_IN_RECORD: &str = "no_type_word_in_record";

// ---------------------------------------------------------------------------
// Provenance references
// ---------------------------------------------------------------------------

/// The stdlib-only oracle for the globals record.
pub const PROV_CELLRES_ORACLE: &str = "tools/spore/cellres/cellres.py";
/// The stdlib-only oracle for the cell record and its AI blocks.
pub const PROV_CELL_ORACLE: &str = "tools/spore/cellres/cell.py";
/// The stdlib-only oracle for the world record.
pub const PROV_CELLWORLD_ORACLE: &str = "tools/spore/cellres/cellworld.py";
/// The stdlib-only oracle for the populate record.
pub const PROV_CELLPOP_ORACLE: &str = "tools/spore/cellres/cellpop.py";
/// The stdlib-only oracle for the structure record.
pub const PROV_CELLSTRUCT_ORACLE: &str = "tools/spore/cellres/cellstruct.py";
/// The stdlib-only oracle for the loot-table record.
pub const PROV_CELLLOOT_ORACLE: &str = "tools/spore/cellres/cellloot.py";
/// The stdlib-only oracle for both look records.
pub const PROV_CELLLOOK_ORACLE: &str = "tools/spore/cellres/celllook.py";
/// The stdlib-only oracle for the random-creature and powers records.
pub const PROV_RANDCREATURE_ORACLE: &str = "tools/spore/cellres/randcreature.py";
/// The stdlib-only oracle for the effect-map and background-map records.
pub const PROV_CELLEFFECTMAP_ORACLE: &str = "tools/spore/cellres/celleffectmap.py";

/// The C++ record decoder: layouts and the dead pointer slots.
pub const PROV_CELLRESOURCE_CPP: &str = "src/assets/CellResource.cpp";
/// The C++ record catalogue and the twenty-six reference fields.
pub const PROV_CELLCONTENT_CPP: &str = "src/assets/CellContent.cpp";
/// The SDK struct the globals field names come from.
pub const PROV_SDK_STRUCT_61843: &str =
    "Spore-ModAPI SDK Simulator::Cell::cCellGlobalsResource (Ghidra struct family 61843)";
/// The SDK struct the `cAIData` field names come from.
pub const PROV_SDK_STRUCT_61866: &str =
    "Spore-ModAPI SDK Simulator::Cell::cAIData (Ghidra struct family 61866)";
/// The SDK struct the `cCellCellResource` field names come from.
pub const PROV_SDK_STRUCT_61869: &str =
    "Spore-ModAPI SDK Simulator::Cell::cCellCellResource (Ghidra struct family 61869)";
/// The stage reconnaissance that lists the eleven SDK resource class names.
pub const PROV_CELLSTAGE_RECON: &str = "docs/CELLSTAGE-RECON.md";

/// What a recorded claim is: a value with a grade, or a non-finding.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ClaimKind {
    /// A value that was established, with its grade.
    Graded(EvidenceLevel),
    /// "We looked and found nothing", with the closed reason code that says so.
    NonFinding(&'static str),
}

impl ClaimKind {
    /// The grade this claim is recorded at.
    pub const fn level(self) -> EvidenceLevel {
        match self {
            Self::Graded(level) => level,
            Self::NonFinding(_) => EvidenceLevel::Unknown,
        }
    }

    /// The reason code, when this claim can be a non-finding.
    pub const fn reason(self) -> Option<&'static str> {
        match self {
            Self::Graded(_) => None,
            Self::NonFinding(reason) => Some(reason),
        }
    }

    /// Whether this claim may carry a value.
    pub const fn can_carry_value(self) -> bool {
        !matches!(self, Self::NonFinding(_))
    }
}

/// One claim this crate can record: its subject, its grade, and why.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct ClaimSpec {
    /// The stable subject string.
    pub subject: &'static str,
    /// Graded value, or non-finding.
    pub kind: ClaimKind,
    /// Why the grade is what it is. Part of the contract, not a comment.
    pub basis: &'static str,
}

/// Every claim this crate can record, in declaration order.
pub const ALL_CLAIMS: &[ClaimSpec] = &[
    ClaimSpec {
        subject: SERIALIZER_ENVELOPE_ABSENT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "the C++ reference names a CellSerializer in its comments and then reads \
                gameMode at offset 0; all 69 fields decode to plausible values at \
                consecutive 4-byte offsets on the one real record, and an envelope would \
                shift every one of them.",
    },
    ClaimSpec {
        subject: GLOBALS_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "69 four-byte fields, the last (mateSpawnDistance) ending at byte 276, and \
                276 is the record length in Spore_EP1_Data.package. cellres.py asserts \
                exactly this (`field span %d != size %d`).",
    },
    ClaimSpec {
        subject: GLOBALS_FIELD_NAMES,
        kind: ClaimKind::Graded(EvidenceLevel::Confirmed),
        basis: "transcribed from the SDK struct Simulator::Cell::cCellGlobalsResource \
                (Ghidra struct family 61843) and corroborated by the matching layout: \
                69 named fields, 69 slots, 276 bytes. The names themselves are not in \
                the record; the corroboration is the size-and-order match.",
    },
    ClaimSpec {
        subject: GLOBALS_FIELD_208_MEANING,
        kind: ClaimKind::NonFinding(MEANING_NOT_ESTABLISHED),
        basis: "cellres.py checks it only as a small enum (<= 8), which is a bound and not \
                a name. Nothing in the corpus or the oracles says what it selects.",
    },
    ClaimSpec {
        subject: GLOBALS_STARTING_CELL_KEY_IS_A_REFERENCE,
        kind: ClaimKind::NonFinding(NO_TYPE_WORD_IN_RECORD),
        basis: "NO TYPE WORD, and the corpus says the C++ reading is wrong. \
                src/assets/CellContent.cpp groups `startingCellKey` with `startCell` and \
                emits it as a cCellCellResource instance; cellres.py calls it a \
                ResourceKey reference but declines to bound-check it and never resolves \
                it. Measured on the one real globals record: `startCell` at +52 is \
                0xCBcd1287, a cell instance present in all three packages, while \
                `startingCellKey` at +56 is 0xA1C46DF2, which the DBPF index of all three \
                packages holds as a `prop` (0x00B1B104) and NOT as a cell. So the field \
                names a record of a different subsystem, this crate cannot say which from \
                the record alone, and the reference resolves to a non-finding rather than \
                to a lookup that must fail.",
    },
    ClaimSpec {
        subject: CELL_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "all 489 cell records in the install are exactly 796 bytes; the three \
                180-byte cAIData blocks at 224/404/584 leave 764 for friendGroup, and \
                every field after them decodes to a plausible value on every record.",
    },
    ClaimSpec {
        subject: CELL_NAME_ENCODING,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "wchar16[80] at +4 followed by u32 localeInstanceID at +164; the 164-byte \
                width is what puts hp at 168, where every record carries a value in 1..4.",
    },
    ClaimSpec {
        subject: AI_SURROGATE_PAIRING,
        kind: ClaimKind::Graded(EvidenceLevel::Inferred),
        basis: "decoding follows the UTF-16 standard, which neither the C++ reference \
                (one code point per unit, CESU-8 output) nor cell.py (chr() per unit) \
                does. NO real record exercises it: all 70 observed names are ASCII. The \
                grade is INFERRED, not OBSERVED, precisely because it is untested by data.",
    },
    ClaimSpec {
        subject: AI_MOVEMENT_STYLE_MEANING,
        kind: ClaimKind::NonFinding(MEANING_NOT_ESTABLISHED),
        basis: "the bit assignments (1=Jet, 2=Flagella, 4=Cilia) come from a C++ comment. \
                The corpus constrains the value to four low bits and no more, which is a \
                bound and not a mapping.",
    },
    ClaimSpec {
        subject: AI_FOOD_MEANING,
        kind: ClaimKind::NonFinding(MEANING_NOT_ESTABLISHED),
        basis: "food takes only 0 and 3 across every observed record. Two values cannot \
                name two things, and no food-type table exists in this build.",
    },
    ClaimSpec {
        subject: WORLD_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "cellworld.py computes 16 + 12*nPop + 24*nAdv and compares it to the length \
                with !=; all 13 unique records satisfy it exactly.",
    },
    ClaimSpec {
        subject: ADVECT_FLOAT_OVERRIDES_SDK_INT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "documented drift: the SDK types strength/variance/period as int and the \
                file stores f32. Reading them as <f yields clean 0.5..3.5 / 0.0 / 1.0 on \
                every advect entry; reading them as <i yields implausible bit patterns. \
                The file wins over the header.",
    },
    ClaimSpec {
        subject: ADVERT_FLOW_FIELD_TYPE,
        kind: ClaimKind::NonFinding(NO_TYPE_WORD_IN_RECORD),
        basis: "the type 0x04805684 comes from the C++ reference's own annotation. No \
                oracle in tools/spore/cellres/ resolves advectID at all, and the field \
                stores no type word of its own, so this crate reports it as pointing \
                outside the family rather than resolving it.",
    },
    ClaimSpec {
        subject: WORLD_POPULATE_RESOLUTION_UNMEASURED,
        kind: ClaimKind::Graded(EvidenceLevel::Inferred),
        basis: "the C++ reference emits world.populate.populate as a hard reference to a \
                0xDA141C1B. No oracle measures whether those resolve, so this crate \
                resolves them through the reference layer but does NOT assert them in the \
                domain checker, where an unmeasured invariant would be a guess.",
    },
    ClaimSpec {
        subject: POPULATE_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "cellpop.py computes 16 + 76*nMarkers and compares with !=; all 21 unique \
                records and all 387 markers satisfy it.",
    },
    ClaimSpec {
        subject: DEAD_MARKER_FIELD,
        kind: ClaimKind::NonFinding(DEAD_FIELD_OBSERVED_ZERO),
        basis: "cMarker.field_0/4/8/14 read as zero on all 387 markers of all 21 records. \
                A constant is not evidence about what a field is, so the bytes are read \
                and reported but nothing is claimed about them.",
    },
    ClaimSpec {
        subject: STRUCTURE_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "cellstruct.py computes 28 + 40*nAttachments and compares with !=; all 149 \
                unique records satisfy it, and every non-null cell.structure reference \
                (165 of them) resolves to a real instance.",
    },
    ClaimSpec {
        subject: ATTACHMENT_STRUCTURE_FIELD,
        kind: ClaimKind::NonFinding(DEAD_FIELD_OBSERVED_ZERO),
        basis: "cSPAttachment.structure is zero on every attachment of every record. The \
                slot exists and is read; what it would name is not established.",
    },
    ClaimSpec {
        subject: EFFECT_ID_REGISTRY,
        kind: ClaimKind::NonFinding(NO_EFFECT_REGISTRY),
        basis: "128 distinct effect ids occur and none has a name in this build. The C++ \
                reference keeps its effect registry populated from outside, so the mapping \
                is not in the game data this crate can read. Inventing a name from the id \
                would be a fabrication.",
    },
    ClaimSpec {
        subject: NEGATIVE_EFFECT_ID_IS_NOT_A_REFERENCE,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "effectID is a SIGNED field and negative values are legitimate, not \
                violations: CellResource.hpp documents '128 distinct, negative ok' and 108 \
                of the real attachments carry a negative value, so a checker that flagged \
                them would manufacture 108 findings out of correct data. The hazard is the \
                unsigned CAST: the C++ reference emits the value as a reference via \
                static_cast<uint32_t>, which turns -1 into 0xFFFFFFFF -- the same word it \
                uses for 'unset'. This crate keeps the signed value and emits the \
                reference only for non-negative values.",
    },
    ClaimSpec {
        subject: LOOT_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "cellloot.py computes 36 + 28*n and compares with !=; all 45 unique records \
                satisfy it, and every non-null entry cell/table reference resolves.",
    },
    ClaimSpec {
        subject: LOOT_HEADER_PADDING,
        kind: ClaimKind::NonFinding(PADDING_NOT_INTERPRETED),
        basis: "the three bytes at +29..+32 are zero on all 45 records. They are read into \
                header_padding rather than skipped, so a non-zero byte is an observable \
                issue, but nothing says what they are for.",
    },
    ClaimSpec {
        subject: LOOK_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "celllook.py computes 8 + 8*n and 8 + 20*n and compares both with !=; all 9 \
                unique tables and the 1 algorithm satisfy them, and every non-null \
                player/npc/epic resolves to one of the 10 look-table instance ids.",
    },
    ClaimSpec {
        subject: RANDOM_CREATURE_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "randcreature.py computes 8 + 28*n and compares with !=; all 10 unique records \
                satisfy it.",
    },
    ClaimSpec {
        subject: CREATURE_ID_REGISTRY,
        kind: ClaimKind::NonFinding(NO_CREATURE_REGISTRY),
        basis: "randcreature.py states it explicitly: creatureID is a soft id, NOT a \
                cell-record reference, and one of the observed ids is absent from every \
                package. Resolving it would be inventing a target.",
    },
    ClaimSpec {
        subject: POWERS_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "randcreature.py reads exactly two fields and does not bound the length, but \
                the one observed powers record is 8 bytes and the C++ reference requires \
                exactly 8. This crate requires 8 as well; that is stricter than the \
                oracle, not looser.",
    },
    ClaimSpec {
        subject: EFFECT_MAP_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "celleffectmap.py computes 8 + 28*n and compares with !=; the one record \
                (24 entries) satisfies it.",
    },
    ClaimSpec {
        subject: BACKGROUND_MAP_LAYOUT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "celleffectmap.py computes 8 + 16*n and compares with !=; the one record \
                (12 entries) satisfies it.",
    },
    ClaimSpec {
        subject: EFFECT_MAP_FIELD_MEANING,
        kind: ClaimKind::NonFinding(MEANING_NOT_ESTABLISHED),
        basis: "cEffectMapEntry.field_8/C/10/14 are named by OFFSET only. The corpus bounds \
                them (-1.0 sentinel, then 0.42..5700 etc.) which is a range, not a name.",
    },
    ClaimSpec {
        subject: BACKGROUND_RAMP_IS_RGB,
        kind: ClaimKind::Graded(EvidenceLevel::Confirmed),
        basis: "the SDK names the fields r, g and b and every value lies in 0..=1 across \
                all 12 stops, which is the corroboration the grade asks for.",
    },
    ClaimSpec {
        subject: BACKGROUND_LADDER_IS_GEOMETRIC,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "the 12 observed field_c values are 0, 0.5, 1.5, 5, 15, 50, 150, 500, \
                1500, 5000, 15000, 100000. The interior steps alternate a factor of \
                exactly 3.0 and 10/3, which is what log-space interpolation between \
                stops is based on. Two of the twelve are NOT ladder steps and are \
                excluded from that regularity: the first is 0.0, where log2 is \
                undefined, and the last is 100000, a clamp whose ratio to the \
                previous stop is 6.67.",
    },
    ClaimSpec {
        subject: SPAN_RULE_ALL_EXACT_FIT,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "measured over every counted record in three packages: no record has \
                trailing bytes and none has entries that overflow its length. Both the C++ \
                binding checks and every Python oracle use exact span arithmetic, so \
                SpanRule::FitsOnly is unrepresented in this family.",
    },
    ClaimSpec {
        subject: GLOBALS_HAS_TWO_REVISIONS,
        kind: ClaimKind::Graded(EvidenceLevel::Observed),
        basis: "0x2A3CE5B7:0x00000000:0xA426730B exists in three packages with two \
                byte-distinct revisions: Spore_Game holds 264 bytes, PatchData and \
                Spore_EP1_Data hold a byte-identical 276. A word alignment shows the \
                short copy is the same record with exactly three fields absent -- \
                gameMode (@0), startingCellKey (@56) and controlMethod (@212) -- so \
                the struct grew by three fields after the base game and this is a \
                format fact, not a truncation. The short revision is refused with \
                ExtentMismatch rather than padded: padding would fabricate three \
                fields. NOTE this is not recorded by the C++ reference or by \
                cellres.py, which only ever loads the EP1 copy.",
    },
    ClaimSpec {
        subject: REFERENCE_TYPE_WORD_ABSENT,
        kind: ClaimKind::NonFinding(NO_TYPE_WORD_IN_RECORD),
        basis: "eleven of the twenty-six reference fields store a bare instance id: the C++ \
                reference gives them ResourceKey::kWildcard as the type word, which is an \
                explicit statement that the record does not say what it points at. They \
                resolve to a non-finding, never to a missing record.",
    },
];

/// The specification for `subject`, or `None` when this build records no such
/// claim. Absence is not `UNKNOWN`: it means "this build does not say".
pub fn spec_of(subject: &str) -> Option<&'static ClaimSpec> {
    ALL_CLAIMS.iter().find(|spec| spec.subject == subject)
}

/// The grade `subject` is recorded at, or [`EvidenceLevel::Unknown`] when this
/// build records nothing for it.
pub fn grade_of(subject: &str) -> EvidenceLevel {
    spec_of(subject).map_or(EvidenceLevel::Unknown, |spec| spec.kind.level())
}

/// Builds the non-finding for `subject`.
///
/// The reason code comes from the subject's own specification, so a claim can
/// never be recorded with a reason that disagrees with its documented grade.
///
/// # Panics
///
/// If `subject` is not declared in [`ALL_CLAIMS`]. Silently answering
/// `meaning_not_established` for a subject nobody declared would report a
/// non-finding about a claim this build does not make — the exact confusion this
/// module exists to prevent — so the mistake surfaces at the construction site
/// instead. Every caller in this crate passes a declared literal.
pub fn non_finding(subject: &'static str) -> Fact<&'static str> {
    let reason = spec_of(subject)
        .and_then(|spec| spec.kind.reason())
        .unwrap_or_else(|| panic!("`{subject}` is not a declared claim subject"));
    Fact::unavailable(reason)
}

/// Builds the graded value for `subject`, sourced from `basis`.
///
/// # Panics
///
/// If `subject` is not declared in [`ALL_CLAIMS`], or is declared a
/// non-finding. A non-finding carrying a value, or an undeclared subject quietly
/// graded, are the two failures this crate exists to prevent.
pub fn graded(
    subject: &'static str,
    basis: &'static str,
    value: &'static str,
) -> Fact<&'static str> {
    let level = grade_of(subject);
    assert_ne!(
        level,
        EvidenceLevel::Unknown,
        "`{subject}` is not a declared graded claim subject"
    );
    Fact::new(
        level,
        EvidenceState::Derived,
        vec![Provenance::derived(basis)],
        value,
    )
}
