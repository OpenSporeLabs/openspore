//! The reference layer: 26 typed fields, a catalogue, and three outcomes.

mod support;

use spore_cellcontent::{
    decode, CellCatalogue, CellContent, CellContentRecord, CellInstanceIndex, CellReference,
    CellReferenceError, CellReferenceField, CellReferenceResolver, ReferenceTarget, ResourceKey,
    CELL_TYPE, LOOK_ALGORITHM_TYPE, LOOK_TABLE_TYPE, LOOT_TABLE_TYPE, POPULATE_TYPE, POWERS_TYPE,
    RANDOM_CREATURE_TYPE, STRUCTURE_TYPE, WORLD_TYPE,
};

use support::*;

#[test]
fn there_are_exactly_twenty_six_reference_fields_plus_the_sentinel() {
    assert_eq!(CellReferenceField::ALL.len(), 26);
    let mut unique: Vec<CellReferenceField> = CellReferenceField::ALL.to_vec();
    unique.sort();
    unique.dedup();
    assert_eq!(unique.len(), 26, "a field is listed twice");
    assert!(!CellReferenceField::ALL.contains(&CellReferenceField::NONE));
    // Every field has a distinct spelling, so an error message cannot be
    // ambiguous about which field it is about.
    let mut names: Vec<&str> = CellReferenceField::ALL.iter().map(|f| f.as_str()).collect();
    names.sort_unstable();
    let before = names.len();
    names.dedup();
    assert_eq!(names.len(), before, "two fields share a spelling");
    assert_eq!(CellReferenceField::NONE.as_str(), "none");
}

#[test]
fn ten_of_the_twenty_six_fields_store_no_type_word() {
    // A field either names a type in this family, names a type in another
    // subsystem, or names nothing at all. The third case is the one that turns
    // resolution into a non-finding.
    let untyped: Vec<CellReferenceField> = CellReferenceField::ALL
        .iter()
        .copied()
        .filter(|field| !field.declares_type())
        .collect();
    assert_eq!(
        untyped,
        vec![
            CellReferenceField::CellBreak,
            CellReferenceField::CellPieces,
            CellReferenceField::CellLeak,
            CellReferenceField::CellExpel,
            CellReferenceField::CellExplosionTable,
            CellReferenceField::CellPoison,
            CellReferenceField::CellAiSpawnOutput,
            CellReferenceField::CellAiDigestionOutput,
            CellReferenceField::StructureHeaderEffect,
            CellReferenceField::StructureAttachmentEffect,
        ],
        "the untyped set changed; the crate documentation counts them"
    );
    // `world.advect` DOES declare a type word -- just not one in this family --
    // which is why it is a separate outcome rather than an eleventh untyped one.
    assert!(CellReferenceField::WorldAdvect.declares_type());
}

// ---------------------------------------------------------------------------
// catalogue + resolution
// ---------------------------------------------------------------------------

fn catalogue_with_two_cells() -> (CellCatalogue, CellContentRecord) {
    let first = cell_record(0x1111_1111, 0xAAAA_AAAA);
    let second = cell_record(0x2222_2222, 0xBBBB_BBBB);
    let structure = structure_record(0xAAAA_AAAA);
    let catalogue = CellCatalogue::from_records([first.clone(), second, structure]);
    (catalogue, first)
}

#[test]
fn a_structure_reference_resolves_to_the_record_it_names() {
    let (catalogue, record) = catalogue_with_two_cells();
    let resolver = CellReferenceResolver::new(&catalogue);
    let references = record.references();
    let structure_reference = references
        .iter()
        .find(|reference| reference.field == CellReferenceField::CellStructure)
        .expect("a non-null structure emits a reference");
    assert_eq!(structure_reference.instance, 0xAAAA_AAAA);
    assert_eq!(
        structure_reference.target,
        ReferenceTarget::Typed(STRUCTURE_TYPE)
    );
    let resolved = resolver
        .resolve(&record, structure_reference, None)
        .expect("the reference resolves");
    assert_eq!(resolved.key.instance_id, 0xAAAA_AAAA);
    assert_eq!(resolved.key.type_id, STRUCTURE_TYPE);
}

#[test]
fn a_reference_to_a_missing_instance_is_a_typed_error_naming_the_key_and_the_field() {
    let catalogue = CellCatalogue::from_records([structure_record(0x0000_0001)]);
    let record = cell_record(0x1111_1111, 0xDEAD_BEEF);
    let resolver = CellReferenceResolver::new(&catalogue);
    let reference = record
        .references()
        .into_iter()
        .find(|r| r.field == CellReferenceField::CellStructure)
        .expect("emitted");
    let error = resolver
        .resolve(&record, &reference, None)
        .expect_err("0xdeadbeef is not in the catalogue");
    assert_eq!(
        error,
        CellReferenceError::NotFound {
            key: record.key,
            field: CellReferenceField::CellStructure,
            index: 0,
            type_id: STRUCTURE_TYPE,
            instance: 0xDEAD_BEEF,
        }
    );
    let text = error.to_string();
    assert!(text.contains("0xdfad9f51:0x00000000:0x11111111"), "{text}");
    assert!(text.contains("cell.structure"), "{text}");
    assert!(text.contains("0xdeadbeef"), "{text}");
    assert!(
        !error.is_non_finding(),
        "a miss is a fact about the catalogue"
    );
    assert_eq!(error.key(), record.key);
}

#[test]
fn a_field_with_no_type_word_is_a_non_finding_not_a_missing_record() {
    let catalogue = CellCatalogue::new(); // empty on purpose
    let record = cell_record(0x1111_1111, 0);
    // Give `break` a value, which is the untyped field under test.
    let record = CellContentRecord::new(
        record.key,
        CellContent::Cell({
            let mut value = match &record.value {
                CellContent::Cell(decoded) => decoded.clone(),
                other => panic!("{other:?}"),
            };
            value.break_ = 0xABCD_EF01;
            value
        }),
    );

    let resolver = CellReferenceResolver::new(&catalogue);
    let reference = record
        .references()
        .into_iter()
        .find(|r| r.field == CellReferenceField::CellBreak)
        .expect("emitted");
    assert_eq!(reference.target, ReferenceTarget::Untyped);
    assert_eq!(reference.target.type_id(), spore_cellcontent::WILDCARD);
    assert_eq!(reference.target_key(), None);

    let error = resolver
        .resolve(&record, &reference, None)
        .expect_err("cannot be resolved");
    assert_eq!(
        error,
        CellReferenceError::UnknownTypeWord {
            key: record.key,
            field: CellReferenceField::CellBreak,
            index: 0,
            instance: 0xABCD_EF01,
        }
    );
    assert!(
        error.is_non_finding(),
        "an untyped field is a non-finding: we never looked, because we could not"
    );
    assert!(error.to_string().contains("no type word"));
}

#[test]
fn an_advect_id_points_outside_the_family_and_says_so() {
    let catalogue = CellCatalogue::new();
    let record = CellContentRecord::new(
        key(WORLD_TYPE, 0, 1),
        decode(WORLD_TYPE, &world(0, 0, 1)).expect("decodes"),
    );
    let resolver = CellReferenceResolver::new(&catalogue);
    let reference = record
        .references()
        .into_iter()
        .find(|r| r.field == CellReferenceField::WorldAdvect)
        .expect("a non-null advectID emits a reference");
    assert_eq!(reference.target, ReferenceTarget::Foreign(0x0480_5684));
    let error = resolver
        .resolve(&record, &reference, None)
        .expect_err("never resolvable against this family");
    assert_eq!(
        error,
        CellReferenceError::OutsideFamily {
            key: record.key,
            field: CellReferenceField::WorldAdvect,
            index: 0,
            type_id: 0x0480_5684,
        }
    );
    assert!(error.is_non_finding());
    assert!(error.to_string().contains("0x04805684"));
}

#[test]
fn a_hand_built_reference_the_record_does_not_emit_is_refused() {
    let (catalogue, record) = catalogue_with_two_cells();
    let resolver = CellReferenceResolver::new(&catalogue);
    let forged = CellReference {
        source: record.key,
        target: ReferenceTarget::Typed(STRUCTURE_TYPE),
        instance: 0xAAAA_AAAA,
        field: CellReferenceField::CellLoot, // this field holds zero in the record
        index: 0,
    };
    assert_eq!(
        resolver.resolve(&record, &forged, None),
        Err(CellReferenceError::NotAReference {
            key: record.key,
            field: CellReferenceField::CellLoot,
            index: 0,
            instance: 0xAAAA_AAAA,
        })
    );
}

#[test]
fn a_reference_naming_the_wrong_target_type_is_refused() {
    let (catalogue, record) = catalogue_with_two_cells();
    let resolver = CellReferenceResolver::new(&catalogue);
    let reference = record
        .references()
        .into_iter()
        .find(|r| r.field == CellReferenceField::CellStructure)
        .expect("emitted");
    assert_eq!(
        resolver.resolve(&record, &reference, Some(CELL_TYPE)),
        Err(CellReferenceError::TargetTypeMismatch {
            key: record.key,
            field: CellReferenceField::CellStructure,
            index: 0,
            requested_type: CELL_TYPE,
            field_type: STRUCTURE_TYPE,
        })
    );
    // The declared type itself resolves.
    assert!(resolver
        .resolve(&record, &reference, Some(STRUCTURE_TYPE))
        .is_ok());
}

#[test]
fn a_source_mismatch_is_refused() {
    let (catalogue, record) = catalogue_with_two_cells();
    let resolver = CellReferenceResolver::new(&catalogue);
    let mut reference = record.references()[0];
    reference.source = key(CELL_TYPE, 0, 0x9999_9999);
    assert_eq!(
        resolver.resolve(&record, &reference, None),
        Err(CellReferenceError::SourceMismatch {
            key: record.key,
            claimed: key(CELL_TYPE, 0, 0x9999_9999),
        })
    );
}

#[test]
fn two_catalogue_rows_sharing_an_instance_are_ambiguous_not_picked_from() {
    let mut catalogue = CellCatalogue::new();
    catalogue.add(structure_record(0xAAAA_AAAA));
    // A second row of the same type and instance but a different group: exactly
    // the patch-overlay case, and exactly the case a reference cannot disambiguate
    // because references carry no group.
    catalogue.add(CellContentRecord::new(
        key(STRUCTURE_TYPE, 7, 0xAAAA_AAAA),
        CellContent::Structure(
            spore_cellcontent::structure::decode(&structure(1, 0)).expect("synthetic"),
        ),
    ));
    let record = cell_record(0x1111_1111, 0xAAAA_AAAA);
    let resolver = CellReferenceResolver::new(&catalogue);
    let reference = record.references()[0];
    assert_eq!(
        resolver.resolve(&record, &reference, None),
        Err(CellReferenceError::Ambiguous {
            key: record.key,
            field: CellReferenceField::CellStructure,
            index: 0,
            type_id: STRUCTURE_TYPE,
            instance: 0xAAAA_AAAA,
            candidates: 2,
        })
    );
    assert!(catalogue.holds_instance(STRUCTURE_TYPE, 0xAAAA_AAAA));
}

#[test]
fn a_zero_field_emits_no_reference_at_all() {
    // 0 means "no target". Collapsing it into a reference to instance 0 would
    // mean a catalogue lookup for a record that cannot exist.
    let record = cell_record(0x1111_1111, 0);
    assert!(record.references().is_empty(), "{:?}", record.references());
    let empty = CellCatalogue::new();
    let resolver = CellReferenceResolver::new(&empty);
    let (resolved, failures) = resolver.resolve_all(&record);
    assert!(resolved.is_empty());
    assert!(failures.is_empty());
}

#[test]
fn every_record_type_enumerates_only_the_fields_it_declares() {
    // `(type id, payload, expected reference count)`, with every non-null
    // reference slot in the synthetic payload filled in so the counts are
    // non-trivial.
    let cases: [(u32, Vec<u8>, usize); 12] = [
        (spore_cellcontent::GLOBALS_TYPE, globals_with_refs(), 17),
        (spore_cellcontent::EFFECT_MAP_TYPE, effect_map(1), 0),
        (spore_cellcontent::BACKGROUND_MAP_TYPE, background_map(1), 0),
        // onDeath + one attachment effectID.
        (STRUCTURE_TYPE, structure(1, 0), 2),
        // one level entry's populate + one advect entry's advectID.
        (WORLD_TYPE, world(1, 0x7777, 1), 2),
        (RANDOM_CREATURE_TYPE, random_creature(1), 0),
        (POWERS_TYPE, powers(), 0),
        (LOOK_TABLE_TYPE, look_table(1), 0),
        (LOOK_ALGORITHM_TYPE, look_algorithm(1, [0, 0, 0]), 0),
        (LOOT_TABLE_TYPE, loot_table(1, 0, 0), 0),
        // two markers, each with two cell references.
        (POPULATE_TYPE, populate(2, 0xC0DE, 0xF00D), 4),
        (CELL_TYPE, cell(0, "x", 0, 0), 0),
    ];
    for (type_id, bytes, expected) in cases {
        let record = CellContentRecord::new(
            key(type_id, 0, 1),
            decode(type_id, &bytes).expect("decodes"),
        );
        assert_eq!(
            record.references().len(),
            expected,
            "0x{type_id:08x}: {:?}",
            record.references()
        );
        // Every emitted reference names its own record.
        assert!(record.references().iter().all(|r| r.source == record.key));
    }
}

#[test]
fn a_globals_record_emits_all_seventeen_reference_slots() {
    let record = CellContentRecord::new(
        key(spore_cellcontent::GLOBALS_TYPE, 0, 1),
        decode(spore_cellcontent::GLOBALS_TYPE, &globals_with_refs()).expect("decodes"),
    );
    let references = record.references();
    assert_eq!(references.len(), 17);
    let worlds = references
        .iter()
        .filter(|r| r.field == CellReferenceField::GlobalsWorld)
        .count();
    assert_eq!(worlds, 12, "five world + five background + two random");
    // `startCell` and `startingCellKey` share one field and are told apart by
    // index -- and only the first declares the cell type. The corpus value at
    // +56 names a `prop`, so treating it as a cell reference would be a lookup
    // that must fail.
    let start_cell: Vec<_> = references
        .iter()
        .filter(|r| r.field == CellReferenceField::GlobalsCell)
        .collect();
    assert_eq!(start_cell.len(), 2, "startCell and startingCellKey");
    assert_eq!(start_cell[0].index, 0);
    assert_eq!(start_cell[0].target, ReferenceTarget::Typed(CELL_TYPE));
    assert!(start_cell[0].declares_type());
    assert_eq!(start_cell[1].index, 1);
    assert_eq!(start_cell[1].target, ReferenceTarget::Untyped);
    assert!(
        !start_cell[1].declares_type(),
        "the corpus value at +56 names a prop, not a cell"
    );

    let typed = references.iter().filter(|r| r.declares_type()).count();
    assert_eq!(
        typed, 16,
        "sixteen of the seventeen globals slots name a type"
    );
    for reference in &references {
        assert_ne!(reference.instance, 0);
    }
}

#[test]
fn the_look_algorithm_indexes_its_three_tables_per_entry() {
    let record = CellContentRecord::new(
        key(LOOK_ALGORITHM_TYPE, 0, 1),
        decode(LOOK_ALGORITHM_TYPE, &look_algorithm(3, [0xAA, 0xBB, 0xCC])).expect("decodes"),
    );
    let references = record.references();
    assert_eq!(references.len(), 9);
    for (entry, chunk) in references.chunks(3).enumerate() {
        assert_eq!(chunk[0].index, entry * 3);
        assert_eq!(chunk[0].instance, 0xAA, "player");
        assert_eq!(chunk[1].index, entry * 3 + 1);
        assert_eq!(chunk[1].instance, 0xBB, "npc");
        assert_eq!(chunk[2].index, entry * 3 + 2);
        assert_eq!(chunk[2].instance, 0xCC, "epic");
        for reference in chunk {
            assert_eq!(reference.field, CellReferenceField::LookTable);
            assert_eq!(reference.target, ReferenceTarget::Typed(LOOK_TABLE_TYPE));
        }
    }
}

#[test]
fn a_negative_effect_id_is_not_treated_as_a_reference() {
    let mut bytes = structure(1, 0);
    // effectID is the fifth i32 of the attachment: 28 + 16 = 44.
    bytes[44..48].copy_from_slice(&(-1i32).to_le_bytes());
    let record = CellContentRecord::new(
        key(STRUCTURE_TYPE, 0, 1),
        decode(STRUCTURE_TYPE, &bytes).expect("decodes"),
    );
    assert!(
        !record
            .references()
            .iter()
            .any(|r| r.field == CellReferenceField::StructureAttachmentEffect),
        "a negative effect id must not become instance 0xFFFFFFFF"
    );
    // And the signed value survives intact, which is what makes the difference
    // observable rather than hidden.
    let CellContent::Structure(value) = &record.value else {
        panic!("wrong variant");
    };
    assert_eq!(value.attachments[0].effect_id, -1);
}

#[test]
fn a_creature_id_is_never_enumerated_as_a_reference() {
    let record = CellContentRecord::new(
        key(RANDOM_CREATURE_TYPE, 0, 1),
        decode(RANDOM_CREATURE_TYPE, &random_creature(4)).expect("decodes"),
    );
    assert!(
        record.references().is_empty(),
        "creatureID is a soft id with no registry: {:?}",
        record.references()
    );
}

#[test]
fn resolve_all_keeps_the_non_findings_and_the_misses_in_one_place() {
    let catalogue = CellCatalogue::from_records([structure_record(0x0000_0001)]);
    let record = cell_record(0x1111_1111, 0xAAAA_AAAA);
    let resolver = CellReferenceResolver::new(&catalogue);
    let (resolved, failures) = resolver.resolve_all(&record);
    assert!(resolved.is_empty(), "0xaaaaaaaa is not present");
    assert_eq!(failures.len(), 1);
    assert!(!failures[0].1.is_non_finding());
}

#[test]
fn an_identity_index_records_an_undecoded_record_without_inventing_one() {
    // The Python oracles work from `set()` of instance ids, never from decoded
    // records. That has to be expressible here without fabricating a record.
    let mut index = CellInstanceIndex::new();
    assert!(index.is_empty());
    index.insert(key(CELL_TYPE, 0, 0x1111));
    index.insert(key(CELL_TYPE, 0, 0x1111)); // a duplicate identity
    assert_eq!(index.len(), 1, "the same identity twice is one identity");
    assert!(index.holds(CELL_TYPE, 0x1111));
    assert!(!index.holds(STRUCTURE_TYPE, 0x1111));

    let mut catalogue = CellCatalogue::new();
    catalogue.add_identity(key(CELL_TYPE, 0, 0x1111));
    assert_eq!(catalogue.record_count(), 0, "nothing has been decoded");
    assert_eq!(catalogue.identity_count(), 1);
    assert!(!catalogue.is_empty());
    assert!(catalogue.sorted().is_empty());
}

#[test]
fn a_catalogue_built_from_keys_still_answers_domain_checkers() {
    let mut catalogue = CellCatalogue::new();
    catalogue.add_identity(key(CELL_TYPE, 0, 0x2222));
    catalogue.add_identity(key(STRUCTURE_TYPE, 0, 0x1111));
    let CellContent::Cell(value) = decode(CELL_TYPE, &cell(0x1111, "x", 0, 0)).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(
        spore_cellcontent::cell_issues(&value, &catalogue).is_empty(),
        "0x1111 is in the STRUCTURE identity index, so the reference resolves"
    );
    // Move the identity to a different type and the same issue appears: the
    // check is about the (type, instance) pair, not the instance alone.
    let mut wrong_type = CellCatalogue::new();
    wrong_type.add_identity(key(CELL_TYPE, 0, 0x1111));
    let issues = spore_cellcontent::cell_issues(&value, &wrong_type);
    assert_eq!(issues.len(), 1, "{issues:?}");
    assert_eq!(issues[0].field, "structure");
}

#[test]
fn an_incomplete_source_key_is_refused() {
    let record = CellContentRecord::new(
        ResourceKey::wildcard(),
        decode(POWERS_TYPE, &powers()).expect("decodes"),
    );
    let empty = CellCatalogue::new();
    let resolver = CellReferenceResolver::new(&empty);
    let forged = CellReference {
        source: ResourceKey::wildcard(),
        target: ReferenceTarget::Typed(POWERS_TYPE),
        instance: 1,
        field: CellReferenceField::CellLoot,
        index: 0,
    };
    assert_eq!(
        resolver.resolve(&record, &forged, None),
        Err(CellReferenceError::IncompleteSource {
            key: ResourceKey::wildcard()
        })
    );
}

#[test]
fn the_populate_and_loot_reference_fields_resolve_against_a_catalogue() {
    // Every field the corpus resolves, exercised end to end.
    let mut catalogue = CellCatalogue::new();
    catalogue.add(cell_record(0x0000_C0DE, 0));
    catalogue.add(cell_record(0x0000_F00D, 0));
    catalogue.add(CellContentRecord::new(
        key(LOOK_TABLE_TYPE, 0, 0x0000_01EA),
        decode(LOOK_TABLE_TYPE, &look_table(1)).expect("decodes"),
    ));
    catalogue.add(CellContentRecord::new(
        key(LOOK_ALGORITHM_TYPE, 0, 0x0000_0A16),
        decode(
            LOOK_ALGORITHM_TYPE,
            &look_algorithm(1, [0x1EA, 0x1EA, 0x1EA]),
        )
        .expect("decodes"),
    ));

    let populate = CellContentRecord::new(
        key(POPULATE_TYPE, 0, 1),
        decode(POPULATE_TYPE, &populate(1, 0xC0DE, 0xF00D)).expect("decodes"),
    );
    let resolver = CellReferenceResolver::new(&catalogue);
    let (resolved, failures) = resolver.resolve_all(&populate);
    assert_eq!(resolved.len(), 2, "{failures:?}");
    assert!(failures.is_empty());
    assert_eq!(
        resolved[0].0.field,
        CellReferenceField::PopulateDistributeCell
    );
    assert_eq!(resolved[0].1.key.instance_id, 0xC0DE);
    assert_eq!(resolved[1].0.field, CellReferenceField::PopulateClusterCell);
    assert_eq!(resolved[1].1.key.instance_id, 0xF00D);

    let loot = CellContentRecord::new(
        key(LOOT_TABLE_TYPE, 0, 1),
        decode(LOOT_TABLE_TYPE, &loot_table(1, 0xC0DE, 0xC0DE)).expect("decodes"),
    );
    let (resolved, failures) = resolver.resolve_all(&loot);
    assert_eq!(resolved.len(), 1, "{failures:?}");
    assert_eq!(resolved[0].0.field, CellReferenceField::LootCell);

    let algorithm = CellContentRecord::new(
        key(LOOK_ALGORITHM_TYPE, 0, 1),
        decode(
            LOOK_ALGORITHM_TYPE,
            &look_algorithm(1, [0x1EA, 0x1EA, 0x1EA]),
        )
        .expect("decodes"),
    );
    let (resolved, failures) = resolver.resolve_all(&algorithm);
    assert_eq!(resolved.len(), 3, "{failures:?}");
    assert!(resolved
        .iter()
        .all(|(_, target)| target.key.instance_id == 0x1EA));
}

#[test]
fn an_ai_output_reference_is_reported_per_tier() {
    let mut bytes = cell(0, "x", 0, 0);
    // spawnOutput sits at cAIData + 80: tier 0 at 224+80 = 304, tier 1 at 404+80,
    // tier 2 at 584+80.
    for offset in [304usize, 404 + 80, 584 + 80] {
        bytes[offset..offset + 4].copy_from_slice(&0x0000_00FEu32.to_le_bytes());
    }
    let record = CellContentRecord::new(
        key(CELL_TYPE, 0, 1),
        decode(CELL_TYPE, &bytes).expect("decodes"),
    );
    let spawn: Vec<_> = record
        .references()
        .into_iter()
        .filter(|r| r.field == CellReferenceField::CellAiSpawnOutput)
        .collect();
    assert_eq!(spawn.len(), 3);
    assert_eq!(
        spawn.iter().map(|r| r.index).collect::<Vec<_>>(),
        vec![0usize, 1, 2],
        "the index is the AI tier"
    );
    let empty = CellCatalogue::new();
    let resolver = CellReferenceResolver::new(&empty);
    for reference in &spawn {
        let error = resolver
            .resolve(&record, reference, None)
            .expect_err("untyped");
        assert_eq!(
            error,
            CellReferenceError::UnknownTypeWord {
                key: record.key,
                field: CellReferenceField::CellAiSpawnOutput,
                index: reference.index,
                instance: 0xFE,
            }
        );
    }
}

#[test]
fn every_structure_header_effect_slot_is_reported_with_its_own_index() {
    let mut bytes = Bytes::new();
    for value in [11u32, 22, 33, 44, 55] {
        bytes.u32(value);
    }
    bytes.u32(0); // dead pointer slot
    bytes.u32(0); // numAttachments
    let record = CellContentRecord::new(
        key(STRUCTURE_TYPE, 0, 1),
        decode(STRUCTURE_TYPE, &bytes.build()).expect("decodes"),
    );
    let effects: Vec<_> = record
        .references()
        .into_iter()
        .filter(|r| r.field == CellReferenceField::StructureHeaderEffect)
        .collect();
    assert_eq!(effects.len(), 5);
    assert_eq!(
        effects
            .iter()
            .map(|r| (r.index, r.instance))
            .collect::<Vec<_>>(),
        vec![(0, 11), (1, 22), (2, 33), (3, 44), (4, 55)]
    );
}
