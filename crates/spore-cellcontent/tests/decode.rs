//! Decoder tests: every record, every field, and every extent rule.
//!
//! The load-bearing idea is that each test **reads the synthetic bytes back a
//! second, independent way**. Where a builder writes a value from a formula, the
//! test recomputes that formula from the index rather than comparing against a
//! hand-written constant list, so a decoder that is consistently wrong in the
//! same direction as the builder cannot pass by construction.

mod support;

use spore_cellcontent::{
    cell, decode, globals, issue, CellContent, CellLookAlgorithmEntry, GlobalsFieldSpec, Scalar,
    SpanRule, BACKGROUND_MAP_TYPE, CELL_TYPE, EFFECT_MAP_TYPE, GLOBALS_FIELD_COUNT, GLOBALS_SIZE,
    GLOBALS_TYPE, LOOK_ALGORITHM_TYPE, LOOK_TABLE_TYPE, LOOT_TABLE_TYPE, POPULATE_TYPE,
    POWERS_TYPE, RANDOM_CREATURE_TYPE, STRUCTURE_TYPE, SUPPORTED_TYPES, WORLD_TYPE,
};

use support::*;

// ---------------------------------------------------------------------------
// extent tables
// ---------------------------------------------------------------------------

/// `(type id, span rule)` for all twelve records, as published.
const SPAN_RULES: [(u32, SpanRule); 12] = [
    (GLOBALS_TYPE, globals::SPAN_RULE),
    (EFFECT_MAP_TYPE, spore_cellcontent::maps::SPAN_RULE),
    (BACKGROUND_MAP_TYPE, spore_cellcontent::maps::SPAN_RULE),
    (STRUCTURE_TYPE, spore_cellcontent::structure::SPAN_RULE),
    (WORLD_TYPE, spore_cellcontent::world::SPAN_RULE),
    (
        RANDOM_CREATURE_TYPE,
        spore_cellcontent::spawn::RANDOM_CREATURE_SPAN_RULE,
    ),
    (POWERS_TYPE, spore_cellcontent::spawn::POWERS_SPAN_RULE),
    (LOOK_TABLE_TYPE, spore_cellcontent::look::SPAN_RULE),
    (LOOK_ALGORITHM_TYPE, spore_cellcontent::look::SPAN_RULE),
    (LOOT_TABLE_TYPE, spore_cellcontent::loot::SPAN_RULE),
    (POPULATE_TYPE, spore_cellcontent::populate::SPAN_RULE),
    (CELL_TYPE, cell::SPAN_RULE),
];

#[test]
fn every_record_publishes_its_span_rule() {
    assert_eq!(SPAN_RULES.len(), SUPPORTED_TYPES.len());
    for (type_id, rule) in SPAN_RULES {
        assert!(spore_cellcontent::is_supported(type_id));
        assert_eq!(rule, SpanRule::ExactFit, "0x{type_id:08x}");
    }
}

#[test]
fn all_twelve_counted_records_are_exact_fit_and_none_is_fits_only() {
    // The finding: the premise that only two records demand an exact fit is not
    // borne out by either reference. Every counted record in this family uses
    // exact-fit, so `FitsOnly` is defined but unrepresented.
    assert!(
        SPAN_RULES
            .iter()
            .all(|(_, rule)| *rule == SpanRule::ExactFit),
        "a FitsOnly record appeared; its decoder must tolerate a remainder"
    );
    assert_eq!(SpanRule::ExactFit.as_str(), "exact-fit");
    assert_eq!(SpanRule::FitsOnly.as_str(), "fits-only");
}

#[test]
fn the_five_record_layout_matches_the_table() {
    // count -> (header, stride) for the nine counted records plus world's two.
    let table: [(u32, usize, usize); 10] = [
        (EFFECT_MAP_TYPE, 8, 28),
        (BACKGROUND_MAP_TYPE, 8, 16),
        (STRUCTURE_TYPE, 28, 40),
        (RANDOM_CREATURE_TYPE, 8, 28),
        (LOOK_TABLE_TYPE, 8, 8),
        (LOOK_ALGORITHM_TYPE, 8, 20),
        (LOOT_TABLE_TYPE, 36, 28),
        (POPULATE_TYPE, 16, 76),
        (CELL_TYPE, cell::AI_OFFSET, cell::AI_BLOCK_SIZE),
        (WORLD_TYPE, 16, 12),
    ];
    assert_eq!(table[0], (EFFECT_MAP_TYPE, 8, 28));
    assert_eq!(table.len(), 10);
    // Every one of these is quoted from the C++ header and the Python oracle, and
    // the decode tests below build records to exactly these sizes.
    for (type_id, header, stride) in table {
        assert!(spore_cellcontent::is_supported(type_id));
        assert_eq!(stride % 4, 0, "0x{type_id:08x}: {stride}");
        assert_eq!(header % 4, 0, "0x{type_id:08x}: {header}");
    }
}

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------

/// The exhaustive name-to-field match that keeps [`GLOBALS_LAYOUT`] and
/// [`CellGlobals`] from drifting.
///
/// Written by hand from the field names so that adding a name to the layout
/// table without adding a struct field, or vice versa, is a **compile error**
/// here rather than a runtime surprise.
fn globals_field(globals: &globals::CellGlobals, name: &str) -> Scalar {
    match name {
        "gameMode" => Scalar::U32(globals.game_mode),
        "world_1" => Scalar::U32(globals.world_1),
        "world_2" => Scalar::U32(globals.world_2),
        "world_3" => Scalar::U32(globals.world_3),
        "world_4" => Scalar::U32(globals.world_4),
        "world_5" => Scalar::U32(globals.world_5),
        "worldBackground_1" => Scalar::U32(globals.world_background_1),
        "worldBackground_2" => Scalar::U32(globals.world_background_2),
        "worldBackground_3" => Scalar::U32(globals.world_background_3),
        "worldBackground_4" => Scalar::U32(globals.world_background_4),
        "worldBackground_5" => Scalar::U32(globals.world_background_5),
        "worldRandom" => Scalar::U32(globals.world_random),
        "worldRandomBg" => Scalar::U32(globals.world_random_bg),
        "startCell" => Scalar::U32(globals.start_cell),
        "startingCellKey" => Scalar::U32(globals.starting_cell_key),
        "effectMapEntry" => Scalar::U32(globals.effect_map_entry),
        "backgroundMapEntry" => Scalar::U32(globals.background_map_entry),
        "flowMultiplier" => Scalar::F32(globals.flow_multiplier),
        "npcSpeedMultiplier" => Scalar::F32(globals.npc_speed_multiplier),
        "npcTurnSpeedMultiplier_Jet" => Scalar::F32(globals.npc_turn_speed_multiplier_jet),
        "npcTurnSpeedMultiplier_Flagella" => {
            Scalar::F32(globals.npc_turn_speed_multiplier_flagella)
        }
        "npcTurnSpeedMultiplier_Cilia" => Scalar::F32(globals.npc_turn_speed_multiplier_cilia),
        "densityRock" => Scalar::F32(globals.density_rock),
        "densitySolid" => Scalar::F32(globals.density_solid),
        "densityLiquid" => Scalar::F32(globals.density_liquid),
        "densityAir" => Scalar::F32(globals.density_air),
        "backgroundDistance" => Scalar::F32(globals.background_distance),
        "minDragCollisionSpeed" => Scalar::F32(globals.min_drag_collision_speed),
        "minImpactCollisionSpeed" => Scalar::F32(globals.min_impact_collision_speed),
        "ciliaSpeedAsJet" => Scalar::F32(globals.cilia_speed_as_jet),
        "flagellaSpeedAsJet" => Scalar::F32(globals.flagella_speed_as_jet),
        "flagellaSpeedAsCilia" => Scalar::F32(globals.flagella_speed_as_cilia),
        "ciliaSpeedAsFlagella" => Scalar::F32(globals.cilia_speed_as_flagella),
        "keyLookAlgorithm" => Scalar::U32(globals.key_look_algorithm),
        "beachDistance" => Scalar::F32(globals.beach_distance),
        "finishLineDistance" => Scalar::F32(globals.finish_line_distance),
        "noPartSpeed" => Scalar::F32(globals.no_part_speed),
        "flagellaRampMinFactor" => Scalar::F32(globals.flagella_ramp_min_factor),
        "flagellaRampTime" => Scalar::F32(globals.flagella_ramp_time),
        "flagellaRampResetAngle" => Scalar::F32(globals.flagella_ramp_reset_angle),
        "flagellaTurnSpeedRampStart" => Scalar::F32(globals.flagella_turn_speed_ramp_start),
        "flagellaTurnSpeedRampEnd" => Scalar::F32(globals.flagella_turn_speed_ramp_end),
        "flagellaTurnSpeedMin" => Scalar::F32(globals.flagella_turn_speed_min),
        "flagellaTurnSpeedMax" => Scalar::F32(globals.flagella_turn_speed_max),
        "ciliaTurnSpeed" => Scalar::F32(globals.cilia_turn_speed),
        "jetTurnSpeed" => Scalar::F32(globals.jet_turn_speed),
        "startLevelNoCreatureRadius" => Scalar::F32(globals.start_level_no_creature_radius),
        "startLevelNoAnythingRadius" => Scalar::F32(globals.start_level_no_anything_radius),
        "numHighLOD_FG" => Scalar::U32(globals.num_high_lod_fg),
        "numHighLOD_BG" => Scalar::U32(globals.num_high_lod_bg),
        "percentAnimalFood" => Scalar::F32(globals.percent_animal_food),
        "percentPlantFood" => Scalar::F32(globals.percent_plant_food),
        "field_208" => Scalar::U32(globals.field_208),
        "controlMethod" => Scalar::U32(globals.control_method),
        "editorMethod" => Scalar::U32(globals.editor_method),
        "tutorialMethod" => Scalar::U32(globals.tutorial_method),
        "endingMethod" => Scalar::U32(globals.ending_method),
        "eyeMethod" => Scalar::U32(globals.eye_method),
        "timeToGoldyCinematic" => Scalar::F32(globals.time_to_goldy_cinematic),
        "missionTime" => Scalar::F32(globals.mission_time),
        "missionResetTime" => Scalar::F32(globals.mission_reset_time),
        "escapeMinDistance" => Scalar::F32(globals.escape_min_distance),
        "escapeMaxDistance" => Scalar::F32(globals.escape_max_distance),
        "escapeDelayMedium" => Scalar::F32(globals.escape_delay_medium),
        "escapeTimerHard" => Scalar::F32(globals.escape_timer_hard),
        "nonAnimatingCiliaMovementFactor" => {
            Scalar::F32(globals.non_animating_cilia_movement_factor)
        }
        "nonAnimatingJetMovementFactor" => Scalar::F32(globals.non_animating_jet_movement_factor),
        "mateTriggerDistance" => Scalar::F32(globals.mate_trigger_distance),
        "mateSpawnDistance" => Scalar::F32(globals.mate_spawn_distance),
        other => panic!("the layout table names a field the struct does not have: {other}"),
    }
}

fn read_u32_at(bytes: &[u8], offset: usize) -> u32 {
    u32::from_le_bytes([
        bytes[offset],
        bytes[offset + 1],
        bytes[offset + 2],
        bytes[offset + 3],
    ])
}

#[test]
fn every_globals_field_reads_back_through_both_paths() {
    let bytes = globals_distinct();
    let decoded = globals::decode(&bytes).expect("276 bytes decode");
    assert_eq!(globals::GLOBALS_LAYOUT.len(), GLOBALS_FIELD_COUNT);
    for (index, spec) in globals::GLOBALS_LAYOUT.iter().enumerate() {
        let word = read_u32_at(&bytes, spec.offset);
        // Path 1: straight out of the buffer at the table's offset.
        let expected = if globals_is_float(index) {
            Scalar::F32(f32::from_bits(word))
        } else {
            Scalar::U32(word)
        };
        // Path 2: through the struct, matched by the record's own name.
        assert_eq!(
            globals_field(&decoded, spec.name),
            expected,
            "{}",
            spec.name
        );
        // Path 3: through the record's own accessor.
        assert_eq!(decoded.lookup(spec.name), Some(expected), "{}", spec.name);
    }
    assert_eq!(decoded.entries().len(), GLOBALS_FIELD_COUNT);
    assert_eq!(decoded.reference_slots().len(), 17);
}

#[test]
fn the_globals_layout_is_69_fields_of_four_bytes_ending_at_276() {
    assert_eq!(GLOBALS_SIZE, 276);
    assert_eq!(GLOBALS_FIELD_COUNT, 69);
    assert_eq!(GLOBALS_FIELD_COUNT * 4, GLOBALS_SIZE);
    for (index, spec) in globals::GLOBALS_LAYOUT.iter().enumerate() {
        assert_eq!(spec.offset, index * 4, "{}", spec.name);
    }
    let last: GlobalsFieldSpec = globals::GLOBALS_LAYOUT[GLOBALS_FIELD_COUNT - 1];
    assert_eq!(last.name, "mateSpawnDistance");
    assert_eq!(last.offset, 272);
}

#[test]
fn a_globals_record_is_refused_one_byte_short_and_one_byte_long() {
    for actual in [GLOBALS_SIZE - 1, GLOBALS_SIZE + 1] {
        let bytes = Bytes::zeroed(actual).build();
        assert_eq!(
            globals::decode(&bytes),
            Err(spore_cellcontent::CellContentError::ExtentMismatch {
                type_id: GLOBALS_TYPE,
                actual,
                expected: GLOBALS_SIZE,
            }),
            "{actual} bytes"
        );
    }
}

#[test]
fn a_zeroed_globals_record_decodes_and_is_in_domain() {
    let decoded = globals::decode(&globals_zeroed()).expect("zeroed globals decode");
    assert_eq!(decoded.game_mode, 0);
    assert_eq!(decoded.mate_spawn_distance, 0.0);
    assert_eq!(decoded.lookup("field_208"), Some(Scalar::U32(0)));
    let catalogue = spore_cellcontent::CellCatalogue::new();
    assert_eq!(
        issue::globals_issues(&decoded, &catalogue),
        Vec::new(),
        "an all-zero globals record is inside every observed bound"
    );
}

// ---------------------------------------------------------------------------
// cell
// ---------------------------------------------------------------------------

#[test]
fn a_cell_record_reads_back_every_field() {
    let bytes = cell(0x00AA_BBCC, "PLACEHOLDER_Tester", 0x0012_3456, 0x0BAD_F00D);
    assert_eq!(bytes.len(), cell::CELL_SIZE);
    let decoded = cell::decode(&bytes).expect("796 bytes decode");

    assert_eq!(decoded.structure, 0x00AA_BBCC);
    assert_eq!(decoded.name, "PLACEHOLDER_Tester");
    assert_eq!(decoded.locale_instance_id, 0x1234_5678);
    assert_eq!(decoded.hp, 3);
    assert_eq!(decoded.fixed_orientation, 0);
    assert_eq!(decoded.flags, 0x0F0F_0F0F);
    assert_eq!(decoded.cell_type, 4);
    assert_eq!(decoded.unlock_type, 8);
    assert_eq!(decoded.density, 3);
    assert_eq!(decoded.sound, 0x00AB_CDEF);
    assert_eq!(decoded.break_, 0x0BAD_F00D);
    assert_eq!(decoded.pieces, 0);
    assert_eq!(decoded.loot, 0x0012_3456);
    assert_eq!(decoded.friend_group, -2);
    assert_eq!(decoded.wont_attack_player, 0);
    assert_eq!(decoded.wont_attack_player_when_small, 1);
    assert_eq!(decoded.size_min, 1.0);
    assert_eq!(decoded.size_max, 4.0);
    assert_eq!(decoded.eat.food_value, 7);
    assert_eq!(decoded.eat.hp_value, 2);
    assert_eq!(decoded.eat.bomb, 0);
    assert_eq!(decoded.eat.poison_nova, 1);
    assert_eq!(decoded.triggers_escape_mission, 1);
}

#[test]
fn the_three_ai_blocks_land_at_224_404_and_584_and_are_180_bytes_each() {
    let bytes = cell(0, "x", 0, 0);
    let decoded = cell::decode(&bytes).expect("decodes");
    assert_eq!(cell::AI_BLOCK_SIZE, 180);
    for (offset, expected_kind, block) in [
        (cell::AI_OFFSET, 0x1000u32, &decoded.ai),
        (cell::AI_HARD_OFFSET, 0x1001, &decoded.ai_hard),
        (cell::AI_EASY_OFFSET, 0x1002, &decoded.ai_easy),
    ] {
        assert_eq!(offset, 224 + (offset - 224) / 180 * 180, "offset {offset}");
        // Path 1: the block's `kind` read straight out of the buffer at the
        // published offset.
        assert_eq!(read_u32_at(&bytes, offset), expected_kind, "@{offset}");
        // Path 2: the decoded struct.
        assert_eq!(block.kind, expected_kind, "@{offset}");
        // Every byte of the block is claimed: the next offset is exactly 180 on.
        assert_eq!(
            offset + cell::AI_BLOCK_SIZE,
            match offset {
                224 => cell::AI_HARD_OFFSET,
                404 => cell::AI_EASY_OFFSET,
                _ => 764,
            },
            "@{offset} does not abut the next block"
        );
    }
    assert_eq!(cell::AI_HARD_OFFSET, cell::AI_OFFSET + 180);
    assert_eq!(cell::AI_EASY_OFFSET, cell::AI_HARD_OFFSET + 180);
    assert_eq!(cell::AI_EASY_OFFSET + 180, 764, "friendGroup starts at 764");
    assert_eq!(read_u32_at(&bytes, 764), (-2i32) as u32, "friendGroup @764");
}

#[test]
fn every_ai_field_reads_back() {
    let bytes = cell(0, "x", 0, 0);
    let decoded = cell::decode(&bytes).expect("decodes");
    let tiers = decoded.ai_tiers();
    for (index, tier) in tiers.iter().enumerate() {
        assert_eq!(tier.kind, 0x1000 + index as u32);
        assert_eq!(tier.awareness_radius, 10.0 + index as f32);
        assert_eq!(tier.movement_style, 0b0111);
        assert_eq!(tier.flocking, 1);
        assert_eq!(tier.axial_movement, 1);
        assert_eq!(tier.num_arcs, index as i32);
        assert_eq!(tier.food, 3);
        assert_eq!(tier.grow_count, index as i32);
        assert_eq!(tier.digestion_count, index as i32 + 1);
        assert_eq!(tier.grow_amount, index as i32);
        assert_eq!(tier.flags().len(), 9);
        assert!(tier.flags().iter().all(|(_, flag)| *flag == 1));
        assert_eq!(tier.floats().len(), 30);
        assert_eq!(tier.floats()[0], 10.0 + index as f32);
        assert!(!tier.is_empty());
    }
    // The zeroed "no AI" sentinel is recognised, not silently accepted as data.
    let mut blank = cell(0, "x", 0, 0);
    blank[cell::AI_OFFSET..cell::AI_OFFSET + 4].copy_from_slice(&0xFFFF_FFFFu32.to_le_bytes());
    let decoded = cell::decode(&blank).expect("decodes");
    assert!(decoded.ai.is_empty());
    assert!(!decoded.ai_hard.is_empty());
}

#[test]
fn a_cell_record_is_refused_one_byte_short_and_one_byte_long() {
    for actual in [cell::CELL_SIZE - 1, cell::CELL_SIZE + 1] {
        let bytes = Bytes::zeroed(actual).build();
        assert_eq!(
            cell::decode(&bytes),
            Err(spore_cellcontent::CellContentError::ExtentMismatch {
                type_id: CELL_TYPE,
                actual,
                expected: cell::CELL_SIZE,
            }),
            "{actual} bytes"
        );
    }
    assert_eq!(cell::CELL_SIZE, 796);
}

// ---------------------------------------------------------------------------
// the counted records: 0, 1 and several entries
// ---------------------------------------------------------------------------

#[test]
fn an_effect_map_decodes_with_zero_one_and_several_entries() {
    for count in [0usize, 1, 7] {
        let bytes = effect_map(count);
        let CellContent::EffectMap(map) = decode(EFFECT_MAP_TYPE, &bytes).expect("decodes") else {
            panic!("wrong variant for {count} entries");
        };
        assert_eq!(map.num_entries, count as u32);
        assert_eq!(map.entries.len(), count);
        assert_eq!(bytes.len(), 8 + 28 * count);
        for (index, entry) in map.entries.iter().enumerate() {
            assert_eq!(entry.effect_id, 0x1000 + index as u32);
            assert_eq!(entry.entry_type, (index % 6) as u32 + 2);
            assert_eq!(entry.field_8, 42.0 + index as f32);
            assert_eq!(entry.field_18, (index % 12) as i32);
        }
    }
}

#[test]
fn a_background_map_decodes_with_zero_one_and_several_entries() {
    for count in [0usize, 1, 12] {
        let bytes = background_map(count);
        let CellContent::BackgroundMap(map) = decode(BACKGROUND_MAP_TYPE, &bytes).expect("decodes")
        else {
            panic!("wrong variant for {count} entries");
        };
        assert_eq!(map.entries.len(), count);
        assert_eq!(bytes.len(), 8 + 16 * count);
        if count > 0 {
            let colour = map.entries[count - 1].rgb();
            assert!(colour.iter().all(|channel| (0.0..=1.0).contains(channel)));
        }
    }
}

#[test]
fn a_random_creature_record_decodes_with_zero_one_and_several_entries() {
    for count in [0usize, 1, 4] {
        let bytes = random_creature(count);
        let CellContent::RandomCreature(table) =
            decode(RANDOM_CREATURE_TYPE, &bytes).expect("decodes")
        else {
            panic!("wrong variant for {count} entries");
        };
        assert_eq!(table.num_entries, count as u32);
        assert_eq!(table.entries.len(), count);
        assert_eq!(bytes.len(), 8 + 28 * count);
        for (index, entry) in table.entries.iter().enumerate() {
            assert_eq!(entry.entry_type, (index % 2) as u32);
            assert_eq!(entry.creature_id, 0x9000_0000 + index as u32);
            assert_eq!(entry.weight, 1.0);
            assert_eq!(entry.stats().len(), 4);
        }
    }
}

#[test]
fn a_look_table_decodes_with_zero_one_and_several_entries() {
    for count in [0usize, 1, 11] {
        let bytes = look_table(count);
        let CellContent::LookTable(table) = decode(LOOK_TABLE_TYPE, &bytes).expect("decodes")
        else {
            panic!("wrong variant for {count} entries");
        };
        assert_eq!(table.num_entries, count as u32);
        assert_eq!(table.entries.len(), count);
        assert_eq!(bytes.len(), 8 + 8 * count);
        for (index, entry) in table.entries.iter().enumerate() {
            assert_eq!(entry.entry_type, (index % 12) as i32);
        }
    }
}

#[test]
fn a_look_algorithm_decodes_with_zero_one_and_several_entries() {
    for count in [0usize, 1, 6] {
        let bytes = look_algorithm(count, [0xAA, 0xBB, 0xCC]);
        let CellContent::LookAlgorithm(algorithm) =
            decode(LOOK_ALGORITHM_TYPE, &bytes).expect("decodes")
        else {
            panic!("wrong variant for {count} entries");
        };
        assert_eq!(algorithm.num_entries, count as u32);
        assert_eq!(algorithm.entries.len(), count);
        assert_eq!(bytes.len(), 8 + 20 * count);
        for entry in &algorithm.entries {
            assert_eq!(entry.look_tables(), [0xAA, 0xBB, 0xCC]);
            assert!(CellLookAlgorithmEntry::is_action_plausible(entry.action));
        }
    }
}

#[test]
fn a_loot_table_decodes_with_zero_one_and_several_entries() {
    for count in [0usize, 1, 9] {
        let bytes = loot_table(count, 0x1111_1111, 0x2222_2222);
        let CellContent::LootTable(table) = decode(LOOT_TABLE_TYPE, &bytes).expect("decodes")
        else {
            panic!("wrong variant for {count} entries");
        };
        assert_eq!(table.num_entries, count as u32);
        assert_eq!(table.entries.len(), count);
        assert_eq!(bytes.len(), 36 + 28 * count);
        assert_eq!(table.header_padding, [0, 0, 0]);
        assert_eq!(table.must_have_part, 1);
        assert_eq!(table.initial_alpha, 1.0);
        for (index, entry) in table.entries.iter().enumerate() {
            assert_eq!(entry.cell, 0x1111_1111);
            assert_eq!(entry.table, 0x2222_2222);
            assert_eq!(entry.weight, 25.0 + index as f32);
        }
    }
}

#[test]
fn the_loot_table_reads_its_three_header_pad_bytes_rather_than_skipping_them() {
    let mut bytes = Bytes::zeroed(36);
    bytes.poke_u8(29, 0xAA);
    bytes.poke_u8(30, 0xBB);
    bytes.poke_u8(31, 0xCC);
    let CellContent::LootTable(table) = decode(LOOT_TABLE_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert_eq!(table.header_padding, [0xAA, 0xBB, 0xCC]);
    // And it is observable as an issue rather than silently dropped.
    let issues = issue::loot_table_issues(&table, &spore_cellcontent::CellCatalogue::new());
    let padding: Vec<_> = issues
        .iter()
        .filter(|issue| issue.kind == spore_cellcontent::IssueKind::PaddingNonZero)
        .collect();
    assert_eq!(padding.len(), 1, "{issues:?}");
    assert!(padding[0].describe().contains("headerPadding"));
}

#[test]
fn a_populate_record_decodes_with_zero_one_and_several_entries() {
    for count in [0usize, 1, 4] {
        let bytes = populate(count, 0x3333_3333, 0x4444_4444);
        let CellContent::Populate(record) = decode(POPULATE_TYPE, &bytes).expect("decodes") else {
            panic!("wrong variant for {count} markers");
        };
        assert_eq!(record.num_markers, count as u32);
        assert_eq!(record.markers.len(), count);
        assert_eq!(bytes.len(), 16 + 76 * count);
        assert_eq!(record.scale, 4);
        for (index, marker) in record.markers.iter().enumerate() {
            assert_eq!(marker.distribute_cell, 0x3333_3333);
            assert_eq!(marker.cluster_cell, 0x4444_4444);
            assert_eq!(marker.z_offset, index as f32);
            assert_eq!(marker.counts().len(), 4);
            assert!(marker.dead_fields().iter().all(|(_, v)| *v == 0));
        }
    }
}

#[test]
fn a_structure_record_decodes_with_zero_one_and_several_entries() {
    for count in [0usize, 1, 3] {
        let bytes = structure(count, 0x5555_5555);
        let CellContent::Structure(record) = decode(STRUCTURE_TYPE, &bytes).expect("decodes")
        else {
            panic!("wrong variant for {count} attachments");
        };
        assert_eq!(record.num_attachments, count as u32);
        assert_eq!(record.attachments.len(), count);
        assert_eq!(bytes.len(), 28 + 40 * count);
        assert_eq!(record.on_death, 101);
        assert_eq!(record.header_effects().len(), 5);
        for (index, attachment) in record.attachments.iter().enumerate() {
            assert_eq!(attachment.bone, [0, 3, -1][index % 3]);
            assert_eq!(attachment.random_creature, 0x5555_5555);
            assert_eq!(attachment.effect_id, 100 + index as i32);
            assert_eq!(attachment.color, [1.0, 0.5, 0.25]);
        }
    }
}

#[test]
fn a_world_record_decodes_with_zero_one_and_several_level_and_advect_entries() {
    for populates in [0usize, 1, 3] {
        for advects in [0usize, 1, 2] {
            let bytes = world(populates, 0x6666_6666, advects);
            let CellContent::World(record) = decode(WORLD_TYPE, &bytes).expect("decodes") else {
                panic!("wrong variant for {populates}/{advects}");
            };
            assert_eq!(record.populate.len(), populates);
            assert_eq!(record.advect.len(), advects);
            assert_eq!(bytes.len(), 16 + 12 * populates + 24 * advects);
            for entry in &record.populate {
                assert_eq!(entry.populate, 0x6666_6666);
                assert!((1..=10).contains(&entry.player_size));
            }
            for (index, entry) in record.advect.iter().enumerate() {
                assert_eq!(entry.stage_scale, index as u32 + 1);
                assert_eq!(entry.player_size, -1);
                assert_eq!(entry.floats(), [1.5, 0.0, 1.0]);
                assert_eq!(entry.advect_id, 0x1234_5678);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// the "exact fit" refusals
// ---------------------------------------------------------------------------

#[test]
fn every_counted_record_refuses_trailing_bytes() {
    // Because every counted record is exact-fit, a record with four trailing
    // bytes must be refused by every one of them. This is the assertion that
    // would fail if any record silently took the fits-only rule.
    for (type_id, _, _, field) in COUNTED {
        let mut long = Bytes::new();
        long.raw(&counted_payload(type_id));
        long.u32(0xDEAD_BEEF);
        assert_eq!(
            decode(type_id, &long.build()),
            Err(spore_cellcontent::CellContentError::TrailingBytes {
                type_id,
                field,
                count: 1,
                trailing: 4,
            }),
            "0x{type_id:08x}"
        );
    }
    // And `world`, whose two counts share one span.
    let mut long = Bytes::new();
    long.raw(&world(2, 0, 1));
    long.u32(0xDEAD_BEEF);
    assert_eq!(
        decode(WORLD_TYPE, &long.build()),
        Err(spore_cellcontent::CellContentError::TrailingBytes {
            type_id: WORLD_TYPE,
            field: "numPopulate+numAdvect",
            count: 3,
            trailing: 4,
        })
    );
}

/// The header length of each single-count record, from the published table.
fn header_of(type_id: u32) -> usize {
    match type_id {
        EFFECT_MAP_TYPE | BACKGROUND_MAP_TYPE | RANDOM_CREATURE_TYPE | LOOK_TABLE_TYPE
        | LOOK_ALGORITHM_TYPE => 8,
        STRUCTURE_TYPE => 28,
        LOOT_TABLE_TYPE => 36,
        POPULATE_TYPE => 16,
        other => panic!("0x{other:08x} is not a single-count record"),
    }
}

#[test]
fn every_counted_record_refuses_more_entries_than_it_holds() {
    for (type_id, count_offset, stride, field) in COUNTED {
        let payload = counted_payload(type_id);
        let mut bytes = Bytes::new();
        bytes.raw(&payload);
        bytes.poke_u32(count_offset, 99);
        let error = decode(type_id, &bytes.build())
            .expect_err("0x{type_id:08x} must refuse an over-long count");
        // `needed` and `available` are both measured against the WHOLE record,
        // which is what the error message says it computed.
        assert_eq!(
            error,
            spore_cellcontent::CellContentError::CountTooLarge {
                type_id,
                field,
                count: 99,
                item_size: stride,
                needed: header_of(type_id) + 99 * stride,
                available: payload.len(),
            },
            "0x{type_id:08x}"
        );
        assert_eq!(error.type_id(), type_id);
        assert_eq!(
            error.kind(),
            spore_cellcontent::CellContentErrorKind::Extent
        );
    }
}

#[test]
fn a_negative_count_is_refused_by_name() {
    // 0xFFFF_FFFF read as i32 is -1. Reinterpreting it as an unsigned length is
    // how a corrupt count turns into a four-gigabyte span request.
    for (type_id, count_offset, _, field) in COUNTED {
        let mut bytes = Bytes::new();
        bytes.raw(&counted_payload(type_id));
        bytes.poke_u32(count_offset, u32::MAX);
        let error = decode(type_id, &bytes.build()).expect_err("negative count refused");
        assert_eq!(
            error,
            spore_cellcontent::CellContentError::NegativeCount {
                type_id,
                field,
                count: -1,
            },
            "0x{type_id:08x}"
        );
    }
    // And `world` refuses either of its two counts by name.
    for (offset, field) in [(0usize, "numPopulate"), (8, "numAdvect")] {
        let mut bytes = Bytes::new();
        bytes.raw(&world(1, 0, 1));
        bytes.poke_u32(offset, u32::MAX);
        assert_eq!(
            decode(WORLD_TYPE, &bytes.build()),
            Err(spore_cellcontent::CellContentError::NegativeCount {
                type_id: WORLD_TYPE,
                field,
                count: -1,
            }),
            "{field}"
        );
    }
}

#[test]
fn a_record_shorter_than_its_own_header_says_so() {
    for type_id in SUPPORTED_TYPES {
        if type_id == GLOBALS_TYPE || type_id == POWERS_TYPE || type_id == CELL_TYPE {
            continue; // fixed extents, checked above
        }
        let error = decode(type_id, &[]).expect_err("0x{type_id:08x} refuses an empty buffer");
        assert!(
            matches!(
                error,
                spore_cellcontent::CellContentError::HeaderTooSmall { .. }
            ),
            "0x{type_id:08x}: {error}"
        );
    }
}

#[test]
fn an_unsupported_type_is_refused_by_name() {
    for type_id in [0x00E6_BCE5u32, 0x2F4E_681C, 0xDEAD_BEEF, 0] {
        assert!(!spore_cellcontent::is_supported(type_id));
        assert_eq!(
            decode(type_id, &[0u8; 64]),
            Err(spore_cellcontent::CellContentError::UnsupportedType { type_id })
        );
    }
    for type_id in SUPPORTED_TYPES {
        assert!(spore_cellcontent::is_supported(type_id));
    }
}

#[test]
fn a_powers_record_is_refused_one_byte_short_and_one_byte_long() {
    for actual in [7usize, 9] {
        assert_eq!(
            decode(POWERS_TYPE, &Bytes::zeroed(actual).build()),
            Err(spore_cellcontent::CellContentError::ExtentMismatch {
                type_id: POWERS_TYPE,
                actual,
                expected: 8,
            })
        );
    }
    let CellContent::Powers(powers) = decode(POWERS_TYPE, &powers()).expect("decodes") else {
        panic!("wrong variant");
    };
    assert_eq!(powers.teleport_cost, 10);
    assert_eq!(powers.teleport_range, 10.0);
}

// ---------------------------------------------------------------------------
// the UTF-16 name
// ---------------------------------------------------------------------------

/// A cell record whose `name` buffer is exactly `units` and whose every other
/// field comes from [`cell`].
fn cell_with_units(units: [u16; cell::NAME_UNITS]) -> Vec<u8> {
    let template = cell(0, "x", 0, 0);
    let mut bytes = Bytes::new();
    bytes.raw(&template[..4]); // structure
    bytes.raw(&units.map(|unit| unit.to_le_bytes()).concat()); // 80 code units
    bytes.raw(&template[4 + cell::NAME_UNITS * 2..]); // localeInstanceID onwards
    let built = bytes.build();
    assert_eq!(built.len(), cell::CELL_SIZE);
    built
}

#[test]
fn the_name_decodes_as_utf16_including_a_non_ascii_character() {
    // `Cell_é` is 7 UTF-16 code units but 8 UTF-8 bytes, so it fails if the
    // decoder reads the field as bytes.
    let bytes = cell(0, "Cell_é", 0, 0);
    let decoded = cell::decode(&bytes).expect("decodes");
    assert_eq!(decoded.name, "Cell_é");
    assert_eq!(decoded.name.chars().count(), 6);
    assert_eq!(decoded.name.len(), 7, "6 chars + a 2-byte é");

    // And a character above the BMP, which is a surrogate PAIR in UTF-16 and
    // two code units in the buffer.
    let astral = "Cell\u{1F9EC}";
    let units: Vec<u16> = astral.encode_utf16().collect();
    assert_eq!(
        units.len(),
        6,
        "the astral character is two code units, not one"
    );
    assert_eq!(astral.chars().count(), 5, "but one scalar value");
    let decoded = cell::decode(&cell_with_units(name_buffer(astral))).expect("decodes");
    assert_eq!(
        decoded.name, astral,
        "a well-formed surrogate pair must decode to one scalar"
    );
    assert_eq!(decoded.name.chars().count(), 5);
}

#[test]
fn a_name_of_exactly_79_characters_decodes_in_full_and_is_not_truncated() {
    // 79 characters into an 80-unit buffer: the terminator is unit[79], which is
    // exactly what `size - 1` bytes of text leaves. Neither oracle reserves a
    // "the last unit must be zero" rule, so nothing is dropped.
    let text = "z".repeat(79);
    let units = name_buffer(&text);
    assert_eq!(units[78], u16::from(b'z'));
    assert_eq!(units[79], 0, "the 80th unit is the terminator");
    let decoded = cell::decode(&cell_with_units(units)).expect("decodes");
    assert_eq!(decoded.name.len(), 79);
    assert_eq!(decoded.name.chars().count(), 79);
    assert_eq!(decoded.name, text);

    // The decision, stated: **do not truncate at 79.** Both oracles read up to
    // the first zero unit and read all 80 otherwise, and dropping the 80th unit
    // would be a silent loss of a byte the record stores.
    let full = name_buffer_full();
    assert!(full.iter().all(|unit| *unit != 0), "no terminator at all");
    let decoded = cell::decode(&cell_with_units(full)).expect("decodes");
    assert_eq!(
        decoded.name.chars().count(),
        80,
        "an unterminated buffer yields all 80 code units"
    );
}

#[test]
fn a_lone_surrogate_decodes_to_the_replacement_character_rather_than_panicking() {
    // The buffer can hold a lone surrogate (mutated data, or a truncated astral
    // character). `from_utf16_lossy` turns it into U+FFFD; a hand-rolled encoder
    // that emitted three raw bytes here would produce invalid UTF-8.
    let mut units = name_buffer("ok");
    units[2] = 0xD83D; // high surrogate with no low surrogate after it
    let decoded = cell::decode(&cell_with_units(units)).expect("decodes");
    assert!(decoded.name.starts_with("ok\u{FFFD}"), "{:?}", decoded.name);
    assert!(decoded.name.is_char_boundary(0));
}

#[test]
fn an_empty_name_is_an_empty_string_not_a_missing_one() {
    let decoded = cell::decode(&cell_with_units([0u16; cell::NAME_UNITS])).expect("decodes");
    assert_eq!(decoded.name, "");
    assert!(decoded.name.is_empty());
}

#[test]
fn the_name_field_is_164_bytes_so_hp_sits_at_168() {
    assert_eq!(cell::NAME_UNITS, 80);
    assert_eq!(cell::NAME_FIELD_SIZE, 164);
    assert_eq!(cell::NAME_FIELD_SIZE, 160 + 4);
    let bytes = cell(0, "x", 0, 0);
    assert_eq!(
        read_u32_at(&bytes, 164),
        0x1234_5678,
        "localeInstanceID @164"
    );
    assert_eq!(read_u32_at(&bytes, 168), 3, "hp @168");
    assert_eq!(spore_cellcontent::cell::NAME_UNITS * 2 + 4, 164);
}

// ---------------------------------------------------------------------------
// every type decodes
// ---------------------------------------------------------------------------

#[test]
fn all_twelve_record_types_decode_from_a_synthetic_payload() {
    for (type_id, bytes) in one_of_each() {
        assert!(spore_cellcontent::is_supported(type_id));
        let decoded =
            decode(type_id, &bytes).unwrap_or_else(|error| panic!("0x{type_id:08x}: {error}"));
        assert_eq!(decoded.type_id(), type_id, "type_id must round-trip");
    }
    assert_eq!(one_of_each().len(), 12);
}

#[test]
fn decoding_is_deterministic_and_reports_its_type_name() {
    for (type_id, bytes) in one_of_each() {
        let first = decode(type_id, &bytes).expect("decodes");
        let second = decode(type_id, &bytes).expect("decodes");
        assert_eq!(first, second, "0x{type_id:08x} must decode identically");
        // Two of the twelve ids are absent from spore-core's transcribed
        // `typenames.json`; `None` there is a non-finding, not a hex guess.
        match decoded_name(first.type_id()) {
            Some(name) => assert_eq!(first.type_name(), Some(name)),
            None => assert!(first.type_name().is_none()),
        }
    }
}

fn decoded_name(type_id: u32) -> Option<&'static str> {
    spore_core::record::RecordType::new(type_id).name()
}

#[test]
fn decode_record_pairs_an_identity_with_its_value() {
    let record = spore_cellcontent::decode_record(key(POWERS_TYPE, 0, 0xA426_730B), &powers())
        .expect("decodes");
    assert_eq!(record.key, key(POWERS_TYPE, 0, 0xA426_730B));
    assert_eq!(record.type_id(), POWERS_TYPE);
    assert!(matches!(record.value, CellContent::Powers(_)));
}

#[test]
fn every_record_type_issues_dispatch_without_panicking() {
    for (type_id, bytes) in one_of_each() {
        let content = decode(type_id, &bytes).expect("decodes");
        let catalogue = spore_cellcontent::CellCatalogue::new();
        let issues = content.issues(&catalogue);
        let _ = issues.len();
    }
}
