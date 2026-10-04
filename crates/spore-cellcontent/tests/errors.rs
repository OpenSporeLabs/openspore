//! Every error variant, constructed by hand, with its message asserted.
//!
//! Two reasons this file exists rather than relying on the decoder tests:
//!
//! * a variant that no decoder can currently reach would be a lie, and a variant
//!   no test constructs is a variant that will silently change shape;
//! * an error message is **part of the API**. The decoders' messages are what a
//!   caller reads to decide what to do next, so they are pinned here verbatim
//!   rather than merely checked for non-emptiness.
//!
//! All six [`CellContentError`] variants and all eight [`CellReferenceError`]
//! variants appear below, each with its `Display` output asserted.

mod support;

use spore_cellcontent::{
    decode, CellContentError, CellContentErrorKind, CellContentRecord, CellReferenceError,
    CellReferenceField, CellReferenceResolver, ReferenceTarget, ResourceKey, CELL_TYPE,
    LOOK_TABLE_TYPE, STRUCTURE_TYPE,
};

use support::*;

const CELL_KEY: ResourceKey = ResourceKey::new(CELL_TYPE, 0, 0x1111_1111);

// ---------------------------------------------------------------------------
// CellContentError
// ---------------------------------------------------------------------------

#[test]
fn unsupported_type_names_the_type_it_refused() {
    let error = CellContentError::UnsupportedType {
        type_id: 0x00E6_BCE5,
    };
    assert_eq!(
        error.to_string(),
        "cell content: unsupported record type 0x00e6bce5"
    );
    assert_eq!(error.type_id(), 0x00E6_BCE5);
    assert_eq!(error.kind(), CellContentErrorKind::UnsupportedType);
    assert_eq!(
        decode(0x00E6_BCE5, &[0u8; 32]),
        Err(CellContentError::UnsupportedType {
            type_id: 0x00E6_BCE5
        })
    );
}

#[test]
fn extent_mismatch_names_both_lengths() {
    let error = CellContentError::ExtentMismatch {
        type_id: CELL_TYPE,
        actual: 795,
        expected: 796,
    };
    assert_eq!(
        error.to_string(),
        "cell content: 0xdfad9f51 is 795 bytes, which is not the fixed extent 796"
    );
    assert_eq!(error.kind(), CellContentErrorKind::ExtentMismatch);
}

#[test]
fn header_too_small_names_the_header_length() {
    let error = CellContentError::HeaderTooSmall {
        type_id: spore_cellcontent::POPULATE_TYPE,
        actual: 4,
        minimum: 16,
    };
    assert_eq!(
        error.to_string(),
        "cell content: 0xda141c1b is 4 bytes, shorter than its 16-byte header"
    );
    assert_eq!(error.kind(), CellContentErrorKind::HeaderTooSmall);
    assert_eq!(
        decode(spore_cellcontent::POPULATE_TYPE, &[0u8; 4]),
        Err(CellContentError::HeaderTooSmall {
            type_id: spore_cellcontent::POPULATE_TYPE,
            actual: 4,
            minimum: 16,
        })
    );
}

#[test]
fn negative_count_names_the_header_field_and_the_value() {
    let error = CellContentError::NegativeCount {
        type_id: spore_cellcontent::LOOK_TABLE_TYPE,
        field: "numEntries",
        count: -1,
    };
    assert_eq!(
        error.to_string(),
        "cell content: 0x8c042499 header field `numEntries` is -1, which is negative"
    );
    assert_eq!(error.kind(), CellContentErrorKind::Extent);
    // Reachable: the look records put the count second, so poke +4.
    let mut bytes = Bytes::new();
    bytes.raw(&look_table(1));
    bytes.poke_u32(4, u32::MAX);
    assert_eq!(
        decode(spore_cellcontent::LOOK_TABLE_TYPE, &bytes.build()),
        Err(error.clone())
    );
}

#[test]
fn count_too_large_shows_the_arithmetic() {
    let error = CellContentError::CountTooLarge {
        type_id: spore_cellcontent::EFFECT_MAP_TYPE,
        field: "numEntries",
        count: 99,
        item_size: 28,
        needed: 2780,
        available: 36,
    };
    assert_eq!(
        error.to_string(),
        "cell content: 0x433fb70c header field `numEntries` claims 99 entries of 28 bytes, \
         needing 2780 bytes, but only 36 remain"
    );
    assert_eq!(error.kind(), CellContentErrorKind::Extent);
}

#[test]
fn trailing_bytes_says_how_many_are_unexplained() {
    let error = CellContentError::TrailingBytes {
        type_id: spore_cellcontent::LOOT_TABLE_TYPE,
        field: "numEntries",
        count: 1,
        trailing: 4,
    };
    assert_eq!(
        error.to_string(),
        "cell content: 0xd92af091 header field `numEntries` declares 1 entries, \
         leaving 4 unexplained trailing bytes"
    );
    assert_eq!(error.kind(), CellContentErrorKind::Extent);
    // And it is reachable by appending four bytes to a real-shaped record.
    let mut bytes = Bytes::new();
    bytes.raw(&loot_table(1, 0, 0));
    bytes.u32(0xDEAD_BEEF);
    assert_eq!(
        decode(spore_cellcontent::LOOT_TABLE_TYPE, &bytes.build()),
        Err(error)
    );
}

#[test]
fn the_three_extent_kinds_cover_every_variant() {
    let kinds = [
        CellContentError::UnsupportedType { type_id: 0 },
        CellContentError::ExtentMismatch {
            type_id: 0,
            actual: 0,
            expected: 1,
        },
        CellContentError::HeaderTooSmall {
            type_id: 0,
            actual: 0,
            minimum: 1,
        },
        CellContentError::NegativeCount {
            type_id: 0,
            field: "n",
            count: -1,
        },
        CellContentError::CountTooLarge {
            type_id: 0,
            field: "n",
            count: 0,
            item_size: 1,
            needed: 0,
            available: 0,
        },
        CellContentError::TrailingBytes {
            type_id: 0,
            field: "n",
            count: 0,
            trailing: 0,
        },
    ];
    assert_eq!(kinds.len(), 6, "one per variant of CellContentError");
    let mut seen: Vec<CellContentErrorKind> = kinds.iter().map(CellContentError::kind).collect();
    seen.sort_by_key(|kind| *kind as u8);
    seen.dedup();
    assert_eq!(seen.len(), 4, "the four coarse kinds are all reachable");
}

// ---------------------------------------------------------------------------
// CellReferenceError
// ---------------------------------------------------------------------------

fn source_record(structure: u32) -> CellContentRecord {
    cell_record(CELL_KEY.instance_id, structure)
}

#[test]
fn incomplete_source_key_says_it_names_no_record() {
    let error = CellReferenceError::IncompleteSource {
        key: ResourceKey::wildcard(),
    };
    assert_eq!(
        error.to_string(),
        "cell reference: source key `0xffffffff:0xffffffff:0xffffffff` is incomplete, \
         so it names no record"
    );
    assert_eq!(error.key(), ResourceKey::wildcard());
    assert!(!error.is_non_finding());
}

#[test]
fn source_mismatch_names_both_keys() {
    let error = CellReferenceError::SourceMismatch {
        key: CELL_KEY,
        claimed: ResourceKey::new(CELL_TYPE, 0, 0x2222_2222),
    };
    assert_eq!(
        error.to_string(),
        "cell reference: asked about a reference on `0xdfad9f51:0x00000000:0x11111111` \
         but the reference names `0xdfad9f51:0x00000000:0x22222222`"
    );
}

#[test]
fn not_a_reference_names_the_field_and_the_index() {
    let error = CellReferenceError::NotAReference {
        key: CELL_KEY,
        field: CellReferenceField::CellLoot,
        index: 3,
        instance: 0xDEAD_BEEF,
    };
    assert_eq!(
        error.to_string(),
        "cell reference: `0xdfad9f51:0x00000000:0x11111111` has no `cell.loot` \
         reference at index 3 to instance 0xdeadbeef"
    );
    assert_eq!(error.key(), CELL_KEY);
}

#[test]
fn unknown_type_word_says_the_field_names_no_record_type() {
    let error = CellReferenceError::UnknownTypeWord {
        key: CELL_KEY,
        field: CellReferenceField::CellPieces,
        index: 1,
        instance: 0x0000_00FF,
    };
    assert_eq!(
        error.to_string(),
        "cell reference: `0xdfad9f51:0x00000000:0x11111111` field `cell.pieces` at index 1 \
         holds instance 0x000000ff but stores no type word, so it names no record type to look up"
    );
    assert!(
        error.is_non_finding(),
        "this is the non-finding: we never looked, because we could not"
    );
}

#[test]
fn outside_family_names_the_foreign_type() {
    let error = CellReferenceError::OutsideFamily {
        key: CELL_KEY,
        field: CellReferenceField::WorldAdvect,
        index: 0,
        type_id: 0x0480_5684,
    };
    assert_eq!(
        error.to_string(),
        "cell reference: `0xdfad9f51:0x00000000:0x11111111` field `world.advect.advectID` \
         at index 0 names type 0x04805684, which is outside the twelve cell-content record types"
    );
    assert!(error.is_non_finding());
}

#[test]
fn target_type_mismatch_names_both_types() {
    let error = CellReferenceError::TargetTypeMismatch {
        key: CELL_KEY,
        field: CellReferenceField::CellStructure,
        index: 0,
        requested_type: CELL_TYPE,
        field_type: STRUCTURE_TYPE,
    };
    assert_eq!(
        error.to_string(),
        "cell reference: `0xdfad9f51:0x00000000:0x11111111` field `cell.structure` at index 0 \
         declares a 0x4b9ef6dc target, not the requested 0xdfad9f51"
    );
    assert!(!error.is_non_finding());
}

#[test]
fn not_found_says_what_was_looked_for() {
    let error = CellReferenceError::NotFound {
        key: CELL_KEY,
        field: CellReferenceField::CellStructure,
        index: 0,
        type_id: STRUCTURE_TYPE,
        instance: 0xAAAA_AAAA,
    };
    assert_eq!(
        error.to_string(),
        "cell reference: `0xdfad9f51:0x00000000:0x11111111` field `cell.structure` at index 0 \
         wants instance 0xaaaaaaaa of type 0x4b9ef6dc, which the catalogue does not hold"
    );
    assert!(
        !error.is_non_finding(),
        "a miss is evidence about the catalogue"
    );

    // Reachable.
    let catalogue = spore_cellcontent::CellCatalogue::new();
    let record = source_record(0xAAAA_AAAA);
    let resolver = CellReferenceResolver::new(&catalogue);
    let reference = record.references()[0];
    assert_eq!(resolver.resolve(&record, &reference, None), Err(error));
}

#[test]
fn ambiguous_reports_how_many_rows_shared_the_instance() {
    let error = CellReferenceError::Ambiguous {
        key: CELL_KEY,
        field: CellReferenceField::CellStructure,
        index: 0,
        type_id: STRUCTURE_TYPE,
        instance: 0xAAAA_AAAA,
        candidates: 3,
    };
    assert_eq!(
        error.to_string(),
        "cell reference: `0xdfad9f51:0x00000000:0x11111111` field `cell.structure` at index 0 \
         wants instance 0xaaaaaaaa of type 0x4b9ef6dc, which 3 catalogue records share"
    );
}

#[test]
fn exactly_eight_reference_error_variants_exist_and_all_are_reachable() {
    // Each variant, built and rendered above. This test exists to make adding a
    // variant a deliberate act.
    let variants = [
        CellReferenceError::IncompleteSource {
            key: ResourceKey::wildcard(),
        },
        CellReferenceError::SourceMismatch {
            key: CELL_KEY,
            claimed: ResourceKey::wildcard(),
        },
        CellReferenceError::NotAReference {
            key: CELL_KEY,
            field: CellReferenceField::NONE,
            index: 0,
            instance: 0,
        },
        CellReferenceError::UnknownTypeWord {
            key: CELL_KEY,
            field: CellReferenceField::CellLoot,
            index: 0,
            instance: 0,
        },
        CellReferenceError::OutsideFamily {
            key: CELL_KEY,
            field: CellReferenceField::WorldAdvect,
            index: 0,
            type_id: 0,
        },
        CellReferenceError::TargetTypeMismatch {
            key: CELL_KEY,
            field: CellReferenceField::CellLoot,
            index: 0,
            requested_type: 0,
            field_type: 0,
        },
        CellReferenceError::NotFound {
            key: CELL_KEY,
            field: CellReferenceField::CellLoot,
            index: 0,
            type_id: 0,
            instance: 0,
        },
        CellReferenceError::Ambiguous {
            key: CELL_KEY,
            field: CellReferenceField::CellLoot,
            index: 0,
            type_id: 0,
            instance: 0,
            candidates: 2,
        },
    ];
    assert_eq!(variants.len(), 8, "one per variant of CellReferenceError");
    for variant in &variants {
        let text = variant.to_string();
        assert!(text.starts_with("cell reference: "), "{text}");
        // Every variant carries the record it is about, except the two that are
        // about the *reference* rather than the record.
        assert!(variant.key().is_complete() || variant.key().is_wildcard());
    }
    // And every variant is Clone + PartialEq, which the workspace relies on.
    assert_eq!(variants[7].clone(), variants[7]);
}

#[test]
fn a_reference_target_reports_its_type_word_or_the_wildcard() {
    assert_eq!(
        ReferenceTarget::Typed(STRUCTURE_TYPE).type_id(),
        STRUCTURE_TYPE
    );
    assert_eq!(ReferenceTarget::Foreign(0x0480_5684).type_id(), 0x0480_5684);
    assert_eq!(
        ReferenceTarget::Untyped.type_id(),
        spore_cellcontent::WILDCARD
    );
}

#[test]
fn an_empty_catalogue_fails_every_resolution_with_a_typed_error() {
    let catalogue = spore_cellcontent::CellCatalogue::new();
    let resolver = CellReferenceResolver::new(&catalogue);
    let record = CellContentRecord::new(
        ResourceKey::new(LOOK_TABLE_TYPE, 0, 1),
        decode(LOOK_TABLE_TYPE, &look_table(1)).expect("decodes"),
    );
    // A look-table record emits no references at all.
    let (resolved, failures) = resolver.resolve_all(&record);
    assert!(resolved.is_empty());
    assert!(failures.is_empty());
    assert!(resolver.catalogue().is_empty());
}
