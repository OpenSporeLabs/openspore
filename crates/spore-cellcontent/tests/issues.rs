//! The domain invariants: in-domain records report nothing, out-of-domain records
//! report exactly what is wrong.
//!
//! The synthetic builders write in-domain values, so the first half of every
//! test here is "no issues" — which is the half that proves the checkers do not
//! manufacture findings. The second half pokes exactly one field out of domain
//! and asserts exactly one issue names it.

mod support;

use spore_cellcontent::{
    background_map_issues, cell_issues, decode, effect_map_issues, globals_issues, issue,
    look_algorithm_issues, look_table_issues, loot_table_issues, populate_issues, powers_issues,
    random_creature_issues, structure_issues, validate_catalogue, world_issues, CellCatalogue,
    CellContent, CellContentRecord, IssueConfidence, IssueKind, IssueValue, Scalar, CELL_TYPE,
    RECORD_LEVEL, STRUCTURE_TYPE,
};

use support::*;

fn empty_catalogue() -> CellCatalogue {
    CellCatalogue::new()
}

/// Asserts that exactly one issue names `field`, and returns its description.
fn only_issue(issues: &[spore_cellcontent::CellIssue], field: &str) -> String {
    assert_eq!(
        issues.len(),
        1,
        "expected one issue for {field}, got {:#?}",
        issues
            .iter()
            .map(spore_cellcontent::CellIssue::describe)
            .collect::<Vec<_>>()
    );
    let issue = &issues[0];
    assert_eq!(issue.field, field, "{:?}", issue.describe());
    issue.describe()
}

fn fields(issues: &[spore_cellcontent::CellIssue]) -> Vec<&'static str> {
    issues.iter().map(|issue| issue.field).collect()
}

/// Decodes, poking one `u32` at `offset` first.
fn poked_cell(offset: usize, word: u32) -> Vec<u8> {
    let mut bytes = Bytes::new();
    bytes.raw(&cell(0, "x", 0, 0));
    bytes.poke_u32(offset, word);
    bytes.build()
}

/// Decodes a cell record with one `u8` poked at `offset`.
fn poked_cell_u8(offset: usize, value: u8) -> Vec<u8> {
    let mut bytes = Bytes::new();
    bytes.raw(&cell(0, "x", 0, 0));
    bytes.poke_u8(offset, value);
    bytes.build()
}

// ---------------------------------------------------------------------------
// the base case: the builders are in domain
// ---------------------------------------------------------------------------

#[test]
fn every_synthetic_record_is_in_domain() {
    // This is the load-bearing negative: if a checker fires on an in-domain
    // record, every other assertion in this file is measuring noise.
    let cases: [(u32, Vec<u8>); 12] = [
        (spore_cellcontent::GLOBALS_TYPE, globals_zeroed()),
        (spore_cellcontent::EFFECT_MAP_TYPE, effect_map(3)),
        (spore_cellcontent::BACKGROUND_MAP_TYPE, background_map(4)),
        (STRUCTURE_TYPE, structure(2, 0)),
        (spore_cellcontent::WORLD_TYPE, world(2, 0, 2)),
        (spore_cellcontent::RANDOM_CREATURE_TYPE, random_creature(3)),
        (spore_cellcontent::POWERS_TYPE, powers()),
        (spore_cellcontent::LOOK_TABLE_TYPE, look_table(4)),
        (
            spore_cellcontent::LOOK_ALGORITHM_TYPE,
            look_algorithm(2, [0, 0, 0]),
        ),
        (spore_cellcontent::LOOT_TABLE_TYPE, loot_table(3, 0, 0)),
        (spore_cellcontent::POPULATE_TYPE, populate(3, 0, 0)),
        (CELL_TYPE, cell(0, "x", 0, 0)),
    ];
    let catalogue = empty_catalogue();
    for (type_id, bytes) in cases {
        let content = decode(type_id, &bytes).expect("decodes");
        let issues = content.issues(&catalogue);
        assert!(
            issues.is_empty(),
            "0x{type_id:08x} reported {:?}",
            issues
                .iter()
                .map(spore_cellcontent::CellIssue::describe)
                .collect::<Vec<_>>()
        );
    }
}

// ---------------------------------------------------------------------------
// cell
// ---------------------------------------------------------------------------

#[test]
fn a_cell_record_reports_its_enumerated_domains() {
    // cellType @180, unlockType @184, density @188, hp @168.
    let cases: [(usize, u32, &str); 4] = [
        (180, 8, "cellType"),
        (184, 3, "unlockType"),
        (188, 2, "density"),
        (168, 9, "hp"),
    ];
    for (offset, word, field) in cases {
        let CellContent::Cell(value) =
            decode(CELL_TYPE, &poked_cell(offset, word)).expect("decodes")
        else {
            panic!("wrong variant");
        };
        let issues = cell_issues(&value, &empty_catalogue());
        let description = only_issue(&issues, field);
        assert!(description.contains(field), "{description}");
    }
}

#[test]
fn a_cell_flag_byte_must_be_zero_or_one() {
    // The Python oracle requires this; the C++ stores a `bool` and cannot see
    // it. fixedOrientation is at +172.
    let CellContent::Cell(value) = decode(CELL_TYPE, &poked_cell_u8(172, 2)).expect("decodes")
    else {
        panic!("wrong variant");
    };
    let issues = cell_issues(&value, &empty_catalogue());
    assert_eq!(
        only_issue(&issues, "fixedOrientation"),
        "cell fixedOrientation: not a boolean = 2, want 0 or 1"
    );
}

#[test]
fn a_cell_size_out_of_range_is_reported_and_an_inverted_pair_too() {
    let CellContent::Cell(value) =
        decode(CELL_TYPE, &poked_cell(772, (-1.0f32).to_bits())).expect("decodes")
    else {
        panic!("wrong variant");
    };
    let issues = cell_issues(&value, &empty_catalogue());
    assert_eq!(issues.len(), 1);
    assert_eq!(issues[0].field, "sizeMin");
    assert_eq!(issues[0].kind, IssueKind::NotFinite);

    let mut bytes = Bytes::new();
    bytes.raw(&cell(0, "x", 0, 0));
    bytes.poke_u32(772, 9.0f32.to_bits());
    bytes.poke_u32(776, 2.0f32.to_bits());
    let CellContent::Cell(value) = decode(CELL_TYPE, &bytes.build()).expect("decodes") else {
        panic!("wrong variant");
    };
    let issues = cell_issues(&value, &empty_catalogue());
    assert_eq!(
        only_issue(&issues, "sizeMin"),
        "cell sizeMin: inverted range = f0x41100000, want sizeMin <= sizeMax"
    );
}

#[test]
fn a_nan_size_is_reported_even_though_the_cpp_accepts_it() {
    // The disagreement, pinned as a test: the C++ form
    // `sizeMin < 0 || sizeMin > 10 || sizeMin > sizeMax` is false for NaN, so a
    // NaN passes it. The Python form `0.0 <= sizeMin <= 10.0` is false for NaN,
    // so it does not. This crate follows Python.
    let CellContent::Cell(value) =
        decode(CELL_TYPE, &poked_cell(772, f32::NAN.to_bits())).expect("decodes")
    else {
        panic!("wrong variant");
    };
    let issues = cell_issues(&value, &empty_catalogue());
    assert_eq!(issues.len(), 1, "{issues:?}");
    assert_eq!(issues[0].field, "sizeMin");
    assert!(
        issues[0].describe().contains("NaN fails"),
        "{}",
        issues[0].describe()
    );
}

#[test]
fn the_three_ai_tiers_are_checked_independently_and_named_by_their_index() {
    // movementStyle is at cAIData + 16: tier 0 @240, tier 1 @420, tier 2 @600.
    for (tier, offset) in [(0usize, 240usize), (1, 420), (2, 600)] {
        let CellContent::Cell(value) =
            decode(CELL_TYPE, &poked_cell(offset, 0xFFFF_FFFF)).expect("decodes")
        else {
            panic!("wrong variant");
        };
        let issues = cell_issues(&value, &empty_catalogue());
        let description = only_issue(&issues, "ai.movementStyle");
        assert!(
            description.contains(&format!("ai.movementStyle#{tier}")),
            "{description}"
        );
    }
}

#[test]
fn an_ai_kind_outside_the_observed_bands_is_reported() {
    // `type` is at cAIData + 0: tier 0 @224.
    let CellContent::Cell(value) = decode(CELL_TYPE, &poked_cell(224, 0x1234)).expect("decodes")
    else {
        panic!("wrong variant");
    };
    let issues = cell_issues(&value, &empty_catalogue());
    assert!(only_issue(&issues, "ai.type").contains("0x00001234"));
}

#[test]
fn an_ai_food_outside_the_observed_set_is_reported_as_an_enum_member() {
    // `food` is at cAIData + 104: tier 0 @328.
    let CellContent::Cell(value) = decode(CELL_TYPE, &poked_cell(328, 7)).expect("decodes") else {
        panic!("wrong variant");
    };
    let issues = cell_issues(&value, &empty_catalogue());
    assert_eq!(issues.len(), 1);
    assert_eq!(issues[0].kind, IssueKind::NotAnEnumMember);
    assert!(only_issue(&issues, "ai.food").contains("0 or 3"));
}

#[test]
fn a_non_finite_ai_float_names_its_own_field() {
    // `speed` is at cAIData + 24: tier 0 @248.
    let CellContent::Cell(value) =
        decode(CELL_TYPE, &poked_cell(248, f32::INFINITY.to_bits())).expect("decodes")
    else {
        panic!("wrong variant");
    };
    let issues = cell_issues(&value, &empty_catalogue());
    assert!(
        only_issue(&issues, "speed").starts_with("cell speed#0: non-finite float"),
        "the float's own name, not the tier's"
    );
    assert_eq!(
        issues[0].observed,
        IssueValue::Scalar(Scalar::F32(f32::INFINITY))
    );
    assert!(issues[0].describe().contains("f0x7f800000"));
}

#[test]
fn an_unresolved_structure_reference_is_reported_on_the_cell() {
    let CellContent::Cell(value) =
        decode(CELL_TYPE, &cell(0xAAAA_AAAA, "x", 0, 0)).expect("decodes")
    else {
        panic!("wrong variant");
    };
    let issues = cell_issues(&value, &empty_catalogue());
    assert_eq!(
        only_issue(&issues, "structure"),
        "cell structure: unresolved reference = 0xaaaaaaaa, want an instance the catalogue holds"
    );
    assert_eq!(issues[0].confidence, IssueConfidence::Resolution);
    assert_eq!(
        issues[0].level(),
        spore_cellcontent::EvidenceLevel::Verified
    );

    // Add the structure and the issue goes away.
    let mut catalogue = empty_catalogue();
    catalogue.add_identity(key(STRUCTURE_TYPE, 0, 0xAAAA_AAAA));
    assert!(cell_issues(&value, &catalogue).is_empty());
}

#[test]
fn a_negative_eat_value_is_reported() {
    // eatFoodValue @780, eatHpValue @784.
    for (offset, field) in [(780usize, "eatFoodValue"), (784, "eatHpValue")] {
        let CellContent::Cell(value) =
            decode(CELL_TYPE, &poked_cell(offset, (-1i32) as u32)).expect("decodes")
        else {
            panic!("wrong variant");
        };
        let issues = cell_issues(&value, &empty_catalogue());
        assert!(only_issue(&issues, field).contains(">= 0"));
    }
}

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------

fn globals_with(offset: usize, word: u32) -> spore_cellcontent::CellGlobals {
    let mut bytes = Bytes::new();
    bytes.raw(&globals_zeroed());
    bytes.poke_u32(offset, word);
    match decode(spore_cellcontent::GLOBALS_TYPE, &bytes.build()).expect("decodes") {
        CellContent::Globals(value) => value,
        other => panic!("wrong variant: {other:?}"),
    }
}

#[test]
fn globals_enum_and_count_bounds_are_enforced_per_field() {
    // gameMode @0, numHighLOD_FG @192.
    for (offset, word, field) in [(0usize, 9u32, "gameMode"), (192, 2000, "numHighLOD_FG")] {
        let issues = globals_issues(&globals_with(offset, word), &empty_catalogue());
        assert!(only_issue(&issues, field).contains(field));
    }
}

#[test]
fn a_globals_float_out_of_range_is_reported() {
    // flowMultiplier @68.
    let issues = globals_issues(&globals_with(68, 2.0e6f32.to_bits()), &empty_catalogue());
    assert!(only_issue(&issues, "flowMultiplier").contains("1e6"));
}

#[test]
fn globals_reference_slots_are_resolved_and_null_slots_are_not() {
    // startCell @52 pointing at a cell instance the catalogue does not hold.
    let issues = globals_issues(&globals_with(52, 0x1111), &empty_catalogue());
    let description = only_issue(&issues, "startCell");
    assert!(
        description.contains("unresolved reference"),
        "{description}"
    );

    // A null slot is not a finding.
    assert!(globals_issues(&globals_zeroed_value(), &empty_catalogue()).is_empty());
}

fn globals_zeroed_value() -> spore_cellcontent::CellGlobals {
    match decode(spore_cellcontent::GLOBALS_TYPE, &globals_zeroed()).expect("decodes") {
        CellContent::Globals(value) => value,
        other => panic!("wrong variant: {other:?}"),
    }
}

// ---------------------------------------------------------------------------
// world / populate / structure / loot / look / spawn / maps
// ---------------------------------------------------------------------------

#[test]
fn a_world_start_tile_and_player_size_are_checked() {
    // level[0]: populate @16, startTile @20, playerSize @24.
    let mut bytes = Bytes::new();
    bytes.raw(&world(1, 0, 0));
    bytes.poke_u8(20, 2);
    let CellContent::World(value) =
        decode(spore_cellcontent::WORLD_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(only_issue(&world_issues(&value), "level.startTile").contains("0 or 1"));

    let mut bytes = Bytes::new();
    bytes.raw(&world(1, 0, 0));
    bytes.poke_u32(24, 0);
    let CellContent::World(value) =
        decode(spore_cellcontent::WORLD_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(only_issue(&world_issues(&value), "level.playerSize").contains("0xFFFFFFFF"));

    // The "any" sentinel is not a finding.
    let mut bytes = Bytes::new();
    bytes.raw(&world(1, 0, 0));
    bytes.poke_u32(24, 0xFFFF_FFFF);
    let CellContent::World(value) =
        decode(spore_cellcontent::WORLD_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(world_issues(&value).is_empty());
}

#[test]
fn an_advect_float_out_of_range_is_reported_by_its_own_name() {
    // advect[0] strength @24: 16-byte header, then stageScale, playerSize.
    let mut bytes = Bytes::new();
    bytes.raw(&world(0, 0, 1));
    bytes.poke_u32(24, 100.0f32.to_bits());
    let CellContent::World(value) =
        decode(spore_cellcontent::WORLD_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(only_issue(&world_issues(&value), "advect.strength").contains("advect.strength#0"));
}

#[test]
fn a_populate_scale_outside_the_observed_set_is_reported() {
    // The disagreement, pinned: the C++ allows `scale <= 10`; the Python oracle
    // requires one of {0,1,2,3,4}. Five satisfies the C++ and fails Python.
    // This crate follows Python, so 5 is an issue and 4 is not.
    let mut bytes = Bytes::new();
    bytes.raw(&populate(0, 0, 0));
    bytes.poke_u32(0, 5);
    let CellContent::Populate(value) =
        decode(spore_cellcontent::POPULATE_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert_eq!(
        only_issue(&populate_issues(&value, &empty_catalogue()), "scale"),
        "populate scale: not an observed value = 0x00000005, want 0, 1, 2, 3 or 4"
    );
    let mut bytes = Bytes::new();
    bytes.raw(&populate(0, 0, 0));
    bytes.poke_u32(0, 4);
    let CellContent::Populate(value) =
        decode(spore_cellcontent::POPULATE_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(populate_issues(&value, &empty_catalogue()).is_empty());
}

#[test]
fn a_dead_marker_field_that_becomes_non_zero_is_reported() {
    // field_0 is the first u32 of marker 0: +16.
    let mut bytes = Bytes::new();
    bytes.raw(&populate(1, 0, 0));
    bytes.poke_u32(16, 1);
    let CellContent::Populate(value) =
        decode(spore_cellcontent::POPULATE_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    let issues = populate_issues(&value, &empty_catalogue());
    assert_eq!(only_issue(&issues, "field_0"), "populate field_0#0: dead field is non-zero = 0x00000001, want 0 on all 387 observed markers");
    assert_eq!(issues[0].kind, IssueKind::DeadFieldNonZero);
}

#[test]
fn a_populate_cell_reference_that_does_not_resolve_is_reported() {
    let CellContent::Populate(value) =
        decode(spore_cellcontent::POPULATE_TYPE, &populate(2, 0xC0DE, 0)).expect("decodes")
    else {
        panic!("wrong variant");
    };
    let issues = populate_issues(&value, &empty_catalogue());
    assert_eq!(fields(&issues), vec!["distributeCell", "distributeCell"]);
    assert_eq!(issues[0].index, 0);
    assert_eq!(issues[1].index, 1);
    // And a null clusterCell emits nothing.
    assert!(!fields(&issues).contains(&"clusterCell"));
}

#[test]
fn a_structure_attachment_domain_is_checked() {
    // attachment[0]: bone +28, type +32, structure +36, randomCreature +40,
    // effectID +44, levelMin +48, levelMax +52, color +56.
    let cases: [(usize, u32, &str); 4] = [
        (28, 2, "bone"),
        (36, 1, "attachment.structure"),
        (48, 5, "levelMin"),
        (52, 11, "levelMax"),
    ];
    for (offset, word, field) in cases {
        let mut bytes = Bytes::new();
        bytes.raw(&structure(1, 0));
        bytes.poke_u32(offset, word);
        let CellContent::Structure(value) =
            decode(STRUCTURE_TYPE, &bytes.build()).expect("decodes")
        else {
            panic!("wrong variant");
        };
        let issues = structure_issues(&value, &empty_catalogue());
        assert!(
            issues.iter().any(|issue| issue.field == field),
            "{field} not reported: {:?}",
            issues
                .iter()
                .map(spore_cellcontent::CellIssue::describe)
                .collect::<Vec<_>>()
        );
    }
}

#[test]
fn a_negative_effect_id_is_not_an_issue_but_an_unresolved_creature_is() {
    // The corpus settles this: 108 real attachments carry a negative effectID and
    // `CellResource.hpp` documents the field as "128 distinct, negative ok", so a
    // checker that flagged the sign would manufacture 108 findings out of correct
    // data. The hazard is the unsigned cast, and the reference layer handles it.
    let mut bytes = Bytes::new();
    bytes.raw(&structure(1, 0xDEAD_BEEF));
    bytes.poke_u32(44, (-7i32) as u32);
    let CellContent::Structure(value) = decode(STRUCTURE_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    let issues = structure_issues(&value, &empty_catalogue());
    assert_eq!(
        fields(&issues),
        vec!["randomCreature"],
        "the sign of an effect id is not a domain violation"
    );
    // And the negative value survives intact, so the reference layer can see it.
    assert_eq!(value.attachments[0].effect_id, -7);
    assert!(!value
        .attachments
        .iter()
        .any(|a| a.effect_id >= 0 && a.structure == 0 && a.random_creature == 0));
}

#[test]
fn a_loot_header_float_outside_its_observed_range_is_reported() {
    // minRadius @8; the C++ bound is 0..=1000 and 50 passes it.
    let mut bytes = Bytes::new();
    bytes.raw(&loot_table(0, 0, 0));
    bytes.poke_u32(8, 50.0f32.to_bits());
    let CellContent::LootTable(value) =
        decode(spore_cellcontent::LOOT_TABLE_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert_eq!(
        only_issue(&loot_table_issues(&value, &empty_catalogue()), "minRadius"),
        "lootTable minRadius: out of range = f0x42480000, want a finite float within the observed range"
    );
}

#[test]
fn a_loot_entry_reference_that_does_not_resolve_is_reported_per_entry() {
    let CellContent::LootTable(value) = decode(
        spore_cellcontent::LOOT_TABLE_TYPE,
        &loot_table(2, 0xC0DE, 0xBEEF),
    )
    .expect("decodes") else {
        panic!("wrong variant");
    };
    let issues = loot_table_issues(&value, &empty_catalogue());
    // Reported per entry, in entry order, cell before table within an entry.
    assert_eq!(
        fields(&issues),
        vec!["entry.cell", "entry.table", "entry.cell", "entry.table"]
    );
    assert_eq!(
        issues.iter().map(|issue| issue.index).collect::<Vec<_>>(),
        vec![0usize, 0, 1, 1]
    );
}

#[test]
fn a_look_action_outside_the_plausible_set_is_reported() {
    let mut bytes = Bytes::new();
    bytes.raw(&look_algorithm(1, [0, 0, 0]));
    // entry[0].action is at +12.
    bytes.poke_u32(12, 100);
    let CellContent::LookAlgorithm(value) =
        decode(spore_cellcontent::LOOK_ALGORITHM_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(only_issue(
        &look_algorithm_issues(&value, &empty_catalogue()),
        "entry.action"
    )
    .contains("0x00000064"));
    // The unset sentinel is not a finding, and neither is 60.
    // Both references agree here, and the agreement is worth pinning: the C++
    // writes `action > 60 && action != 0xFFFFFFFF` and the Python writes
    // `action not in (0, 18..22, 0xFFFFFFFF) and action > 60`. The Python form
    // additionally exempts 0 and 18..22, but none of those exceeds 60, so the
    // exemption never fires and both reduce to "only 61..=0xFFFFFFFE offend".
    for action in [0u32, 1, 17, 18, 22, 23, 60, 0xFFFF_FFFF] {
        assert!(
            spore_cellcontent::CellLookAlgorithmEntry::is_action_plausible(action),
            "{action} is plausible"
        );
    }
    for action in [61u32, 100, 0x0100_0000, 0xFFFF_FFFE] {
        assert!(
            !spore_cellcontent::CellLookAlgorithmEntry::is_action_plausible(action),
            "{action} is not plausible"
        );
    }
}

#[test]
fn a_look_algorithm_table_reference_is_reported_per_slot() {
    let CellContent::LookAlgorithm(value) = decode(
        spore_cellcontent::LOOK_ALGORITHM_TYPE,
        &look_algorithm(1, [1, 2, 3]),
    )
    .expect("decodes") else {
        panic!("wrong variant");
    };
    let issues = look_algorithm_issues(&value, &empty_catalogue());
    assert_eq!(
        fields(&issues),
        vec!["entry.player", "entry.npc", "entry.epic"]
    );
    assert!(issues.iter().all(|issue| issue.index == 0));
}

#[test]
fn a_look_table_entry_domain_is_checked() {
    let mut bytes = Bytes::new();
    bytes.raw(&look_table(1));
    bytes.poke_u32(8, 99);
    let CellContent::LookTable(value) =
        decode(spore_cellcontent::LOOK_TABLE_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(only_issue(&look_table_issues(&value), "entry.type").contains("0..=31"));
}

#[test]
fn a_random_creature_inverted_range_is_reported() {
    let mut bytes = Bytes::new();
    bytes.raw(&random_creature(1));
    // speedMin @8+12 = 20, speedMax @24.
    bytes.poke_u32(20, 9);
    let CellContent::RandomCreature(value) =
        decode(spore_cellcontent::RANDOM_CREATURE_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(only_issue(&random_creature_issues(&value), "speedMin").contains("inverted range"));
    // A `-1` on either side means "any" and exempts the ordering.
    let mut bytes = Bytes::new();
    bytes.raw(&random_creature(1));
    bytes.poke_u32(20, 9);
    bytes.poke_u32(24, (-1i32) as u32);
    let CellContent::RandomCreature(value) =
        decode(spore_cellcontent::RANDOM_CREATURE_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(random_creature_issues(&value).is_empty());
}

#[test]
fn a_powers_field_out_of_range_is_reported() {
    let mut bytes = Bytes::new();
    bytes.raw(&powers());
    bytes.poke_u32(0, (-1i32) as u32);
    let CellContent::Powers(value) =
        decode(spore_cellcontent::POWERS_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(only_issue(&powers_issues(&value), "teleportCost").contains("0..=10000"));
}

#[test]
fn an_effect_map_field_outside_its_range_or_sentinel_is_reported() {
    // field_8 is the third u32 of entry 0: 8 + 8 = 16.
    let mut bytes = Bytes::new();
    bytes.raw(&effect_map(1));
    bytes.poke_u32(16, (-200.0f32).to_bits());
    let CellContent::EffectMap(value) =
        decode(spore_cellcontent::EFFECT_MAP_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(only_issue(&effect_map_issues(&value), "field_8").contains("-1.0 sentinel"));
    // The sentinel itself is accepted.
    let mut bytes = Bytes::new();
    bytes.raw(&effect_map(1));
    bytes.poke_u32(16, (-1.0f32).to_bits());
    let CellContent::EffectMap(value) =
        decode(spore_cellcontent::EFFECT_MAP_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(effect_map_issues(&value).is_empty());
}

#[test]
fn a_background_map_channel_outside_zero_to_one_is_reported() {
    let mut bytes = Bytes::new();
    bytes.raw(&background_map(1));
    bytes.poke_u32(8, 1.5f32.to_bits());
    let CellContent::BackgroundMap(value) =
        decode(spore_cellcontent::BACKGROUND_MAP_TYPE, &bytes.build()).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert!(only_issue(&background_map_issues(&value), "r").contains("0.0..=1.0"));
}

#[test]
fn the_background_ramp_sampler_and_envelope_are_total() {
    let ramp = match decode(spore_cellcontent::BACKGROUND_MAP_TYPE, &background_map(6)) {
        Ok(CellContent::BackgroundMap(value)) => value,
        _ => panic!("wrong variant"),
    };
    assert!(spore_cellcontent::sample_background_color(&ramp, 1.0).is_some());
    // Clamping at both ends.
    let below = spore_cellcontent::sample_background_color(&ramp, -100.0).unwrap();
    let above = spore_cellcontent::sample_background_color(&ramp, 1.0e9).unwrap();
    assert_eq!(below, ramp.entries[0].rgb());
    assert_eq!(above, ramp.entries[5].rgb());
    let envelope = spore_cellcontent::background_color_envelope(&ramp).expect("non-empty");
    assert!(envelope[0] <= envelope[3] && envelope[1] <= envelope[4] && envelope[2] <= envelope[5]);

    // An empty ramp is a NON-FINDING, not black.
    let empty = match decode(spore_cellcontent::BACKGROUND_MAP_TYPE, &background_map(0)) {
        Ok(CellContent::BackgroundMap(value)) => value,
        _ => panic!("wrong variant"),
    };
    assert_eq!(
        spore_cellcontent::sample_background_color(&empty, 1.0),
        None,
        "no entries means nothing to sample, which is not (0,0,0)"
    );
    assert_eq!(spore_cellcontent::background_color_envelope(&empty), None);
}

// ---------------------------------------------------------------------------
// whole-catalogue validation
// ---------------------------------------------------------------------------

#[test]
fn catalogue_validation_is_sorted_and_omits_clean_records() {
    let mut catalogue = CellCatalogue::new();
    catalogue.add(cell_record(0x2222, 0xAAAA_AAAA)); // unresolved structure
    catalogue.add(cell_record(0x1111, 0));
    let clean = cell_record(0x3333, 0);
    let rows = validate_catalogue(&catalogue, catalogue.sorted());
    assert_eq!(rows.len(), 1, "only the record with an issue is reported");
    assert_eq!(rows[0].key.instance_id, 0x2222);
    assert_eq!(rows[0].issues.len(), 1);

    // Sorted output is stable regardless of insertion order.
    let mut forward = CellCatalogue::new();
    forward.add(cell_record(0x1111, 0));
    forward.add(clean.clone());
    forward.add(cell_record(0x2222, 0xAAAA_AAAA));
    let again = validate_catalogue(&forward, forward.sorted());
    assert_eq!(rows, again);
}

#[test]
fn a_record_level_issue_uses_the_sentinel_index() {
    let CellContent::Cell(value) = decode(CELL_TYPE, &poked_cell(180, 99)).expect("decodes") else {
        panic!("wrong variant");
    };
    let issues = cell_issues(&value, &empty_catalogue());
    assert_eq!(issues[0].index, RECORD_LEVEL);
    assert_eq!(issues[0].type_id(), CELL_TYPE);
    assert_eq!(
        issues[0].level(),
        spore_cellcontent::EvidenceLevel::Observed,
        "a corpus bound is an observation, not a proof"
    );
    assert_eq!(issue::RECORD_LEVEL, usize::MAX);
    assert!(
        spore_cellcontent::IssueValue::Bytes(vec![1, 2, 3])
            .scalar()
            .is_none(),
        "raw bytes are not a scalar"
    );
}

#[test]
fn every_issue_kind_is_reachable() {
    // A guard against a checker arm that has silently become dead.
    let mut seen: Vec<IssueKind> = Vec::new();
    let collect = |issues: &[spore_cellcontent::CellIssue], seen: &mut Vec<IssueKind>| {
        for issue in issues {
            if !seen.contains(&issue.kind) {
                seen.push(issue.kind);
            }
        }
    };

    let CellContent::Cell(value) =
        decode(CELL_TYPE, &poked_cell(772, f32::NAN.to_bits())).expect("d")
    else {
        panic!();
    };
    collect(&cell_issues(&value, &empty_catalogue()), &mut seen);
    let CellContent::Cell(value) = decode(CELL_TYPE, &poked_cell(328, 7)).expect("d") else {
        panic!();
    };
    collect(&cell_issues(&value, &empty_catalogue()), &mut seen);
    let CellContent::Cell(value) = decode(CELL_TYPE, &poked_cell_u8(172, 2)).expect("d") else {
        panic!();
    };
    collect(&cell_issues(&value, &empty_catalogue()), &mut seen);
    let mut bytes = Bytes::new();
    bytes.raw(&populate(1, 0, 0));
    bytes.poke_u32(16, 1);
    let CellContent::Populate(value) =
        decode(spore_cellcontent::POPULATE_TYPE, &bytes.build()).expect("d")
    else {
        panic!();
    };
    collect(&populate_issues(&value, &empty_catalogue()), &mut seen);
    let CellContent::Cell(value) = decode(CELL_TYPE, &cell(0xAAAA, "x", 0, 0)).expect("d") else {
        panic!();
    };
    collect(&cell_issues(&value, &empty_catalogue()), &mut seen);
    let CellContent::LootTable(value) =
        decode(spore_cellcontent::LOOT_TABLE_TYPE, &loot_table(1, 0xC0, 0)).expect("d")
    else {
        panic!()
    };
    collect(&loot_table_issues(&value, &empty_catalogue()), &mut seen);
    let mut bytes = Bytes::new();
    bytes.raw(&loot_table(0, 0, 0));
    bytes.poke_u8(29, 1);
    let CellContent::LootTable(value) =
        decode(spore_cellcontent::LOOT_TABLE_TYPE, &bytes.build()).expect("d")
    else {
        panic!()
    };
    collect(&loot_table_issues(&value, &empty_catalogue()), &mut seen);
    let mut bytes = Bytes::new();
    bytes.raw(&random_creature(1));
    bytes.poke_u32(20, 9);
    let CellContent::RandomCreature(value) =
        decode(spore_cellcontent::RANDOM_CREATURE_TYPE, &bytes.build()).expect("d")
    else {
        panic!();
    };
    collect(&random_creature_issues(&value), &mut seen);
    // OutOfRange: the globals enum bound.
    collect(
        &globals_issues(&globals_with(0, 9), &empty_catalogue()),
        &mut seen,
    );

    for kind in [
        IssueKind::NotFinite,
        IssueKind::OutOfRange,
        IssueKind::NotAnEnumMember,
        IssueKind::NotABoolean,
        IssueKind::DeadFieldNonZero,
        IssueKind::PaddingNonZero,
        IssueKind::UnresolvedReference,
        IssueKind::InvertedRange,
    ] {
        assert!(
            seen.contains(&kind),
            "{kind:?} is never produced by any checker"
        );
    }
}

#[test]
fn a_cell_content_record_dispatches_its_own_issues() {
    let record = CellContentRecord::new(
        key(CELL_TYPE, 0, 1),
        CellContent::Cell(match decode(CELL_TYPE, &cell(0xAAAA, "x", 0, 0)) {
            Ok(CellContent::Cell(value)) => value,
            _ => panic!(),
        }),
    );
    let catalogue = empty_catalogue();
    assert_eq!(record.value.issues(&catalogue).len(), 1);
    assert_eq!(
        record.value.issues(&catalogue)[0].field,
        "structure",
        "the same answer through the enum and through the free function"
    );
}
