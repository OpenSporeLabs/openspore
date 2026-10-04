//! No input produces a panic.
//!
//! Three sweeps, all of which must return `Ok` or `Err` and never unwind:
//!
//! 1. **every prefix length** of every record type, from 0 to the full record
//!    plus a generous margin;
//! 2. **byte mutations** at several offsets of every record type, with a value
//!    that maximises the chance of a hostile read (`0xFF`, `0x80`, `0x7F`,
//!    `0x00`);
//! 3. **random garbage**, deterministic (a fixed LCG seed) so a failure is
//!    reproducible.
//!
//! A prefix shorter than a counted record's header is refused by
//! `HeaderTooSmall`; a prefix that happens to satisfy the extent arithmetic but
//! is not the intended record decodes to *something*, which is fine — the
//! contract is "typed answer or typed error", never a panic.

mod support;

use spore_cellcontent::{
    decode, CellCatalogue, CellContent, CellReferenceResolver, SUPPORTED_TYPES,
};

use support::*;

#[test]
fn no_prefix_of_any_record_panics() {
    for (type_id, bytes) in one_of_each() {
        // A generous margin past the record's own length: a decoder that only
        // guards its own extent should still answer.
        for length in 0..=(bytes.len() + 64) {
            let prefix = &bytes[..length.min(bytes.len())];
            match decode(type_id, prefix) {
                Ok(content) => assert_eq!(content.type_id(), type_id, "0x{type_id:08x}@{length}"),
                Err(error) => {
                    assert_eq!(
                        error.type_id(),
                        type_id,
                        "0x{type_id:08x}@{length}: {error}"
                    );
                    let _ = error.to_string();
                    let _ = error.kind();
                }
            }
        }
    }
}

#[test]
fn an_over_long_buffer_is_also_answered() {
    // A record plus trailing bytes, at several margins, for every type. The
    // fixed-extent records must refuse and the counted ones must too (they are
    // exact-fit), but the point here is only that both are *typed*.
    for (type_id, bytes) in one_of_each() {
        for extra in [1usize, 4, 8, 76, 1024] {
            let mut longer = Bytes::new();
            longer.raw(&bytes);
            for _ in 0..extra {
                longer.u8(0xA5);
            }
            match decode(type_id, &longer.build()) {
                Ok(content) => assert_eq!(content.type_id(), type_id, "0x{type_id:08x}+{extra}"),
                Err(error) => {
                    assert_eq!(error.type_id(), type_id, "0x{type_id:08x}+{extra}");
                    let _ = error.to_string();
                }
            }
        }
    }
}

#[test]
fn no_byte_mutation_panics() {
    const VALUES: [u8; 6] = [0x00, 0x01, 0x7F, 0x80, 0xFE, 0xFF];
    for (type_id, bytes) in one_of_each() {
        // A spread of offsets: the header, each structural boundary, and the
        // last few bytes, rather than every byte of a 796-byte record.
        let mut offsets: Vec<usize> = vec![0, 1, 3, 4, 7, 8, 11, 12];
        let mut cursor = 24;
        while cursor < bytes.len() {
            offsets.push(cursor);
            cursor += 37;
        }
        offsets.push(bytes.len().saturating_sub(4));
        offsets.push(bytes.len().saturating_sub(1));
        for offset in offsets {
            if offset >= bytes.len() {
                continue;
            }
            for value in VALUES {
                let mut mutated = Bytes::new();
                mutated.raw(&bytes);
                mutated.poke_u8(offset, value);
                let mutated = mutated.build();
                let result = decode(type_id, &mutated);
                match result {
                    Ok(content) => {
                        assert_eq!(content.type_id(), type_id, "0x{type_id:08x}@{offset}")
                    }
                    Err(error) => {
                        assert_eq!(error.type_id(), type_id);
                        let _ = error.to_string();
                    }
                }
            }
        }
    }
}

#[test]
fn no_word_mutation_panics() {
    for (type_id, bytes) in one_of_each() {
        let mut offset = 0;
        while offset + 4 <= bytes.len() {
            for word in [0u32, 1, 0x7FFF_FFFF, 0x8000_0000, 0xFFFF_FFFF] {
                let mut mutated = Bytes::new();
                mutated.raw(&bytes);
                mutated.poke_u32(offset, word);
                let _ = decode(type_id, &mutated.build());
            }
            offset += 12;
        }
    }
}

#[test]
fn no_counted_record_panics_on_an_absurd_count() {
    // The classic overflow trap: a count whose product with the stride would
    // wrap a 32-bit computation.
    for (type_id, count_offset, _, _) in COUNTED {
        for count in [
            0x7FFF_FFFFu32,
            0x8000_0000,
            0xFFFF_FFFF,
            0xFFFF_FFFE,
            0x7FFF_FFFF / 28,
            0x7FFF_FFFF / 8,
        ] {
            let mut bytes = Bytes::new();
            bytes.raw(&counted_payload(type_id));
            bytes.poke_u32(count_offset, count);
            let result = decode(type_id, &bytes.build());
            if let Err(error) = result {
                assert_eq!(error.type_id(), type_id);
            }
        }
    }
    // And `world`, whose two counts are combined in 64-bit arithmetic.
    for (a, b) in [
        (0x7FFF_FFFFu32, 0u32),
        (0u32, 0x7FFF_FFFF),
        (0x7FFF_FFFF, 0x7FFF_FFFF),
        (0xFFFF_FFFF, 0xFFFF_FFFF),
    ] {
        let mut bytes = Bytes::new();
        bytes.raw(&world(0, 0, 0));
        bytes.poke_u32(0, a);
        bytes.poke_u32(8, b);
        let _ = decode(spore_cellcontent::WORLD_TYPE, &bytes.build());
    }
}

#[test]
fn a_counted_record_with_a_two_gigabyte_count_does_not_allocate() {
    // The property that matters is not only "no panic" but "no attempt": a count
    // of 2^31 with a 76-byte stride must be refused before any `Vec` of that
    // length is built. The decoder reserves capacity from the count, so the
    // refusal has to happen first -- which the extent check does.
    let mut bytes = Bytes::new();
    bytes.raw(&counted_payload(spore_cellcontent::POPULATE_TYPE));
    bytes.poke_u32(8, 0x0FFF_FFFF);
    assert!(
        decode(spore_cellcontent::POPULATE_TYPE, &bytes.build()).is_err(),
        "a 268-million-marker record must be refused, not allocated"
    );
}

#[test]
fn deterministic_garbage_never_panics() {
    // A fixed LCG, so a failure here is reproducible from the seed alone.
    let mut state: u64 = 0x2545_F491_4F6C_DD1D;
    let mut next = move || {
        state = state
            .wrapping_mul(6_364_136_223_846_793_005)
            .wrapping_add(1_442_695_040_888_963_407);
        (state >> 33) as u32
    };
    for type_id in SUPPORTED_TYPES {
        for len in [
            0usize, 1, 3, 7, 8, 15, 16, 27, 28, 35, 36, 75, 76, 275, 276, 795, 796, 4096,
        ] {
            let garbage: Vec<u8> = (0..len).map(|_| next() as u8).collect();
            match decode(type_id, &garbage) {
                Ok(content) => assert_eq!(content.type_id(), type_id),
                Err(error) => {
                    assert_eq!(error.type_id(), type_id);
                    let _ = error.to_string();
                }
            }
        }
    }
}

#[test]
fn a_decoded_record_survives_the_whole_issue_and_reference_pipeline() {
    // Whatever garbage happens to decode must also survive enumeration,
    // resolution and the domain checkers without panicking.
    let mut state: u64 = 0x9E37_79B9_7F4A_7C15;
    let mut next = move || {
        state = state
            .wrapping_mul(6_364_136_223_846_793_005)
            .wrapping_add(1_442_695_040_888_963_407);
        (state >> 33) as u32
    };
    for type_id in SUPPORTED_TYPES {
        let mut catalogue = CellCatalogue::new();
        for len in [8usize, 16, 28, 36, 64, 128] {
            let garbage: Vec<u8> = (0..len).map(|_| next() as u8).collect();
            let Ok(content) = decode(type_id, &garbage) else {
                continue;
            };
            catalogue.add_identity(spore_cellcontent::ResourceKey::new(type_id, 0, next()));
            let record = spore_cellcontent::CellContentRecord::new(
                spore_cellcontent::ResourceKey::new(type_id, 0, next()),
                content,
            );
            let _ = record.references();
            let _ = record.value.issues(&catalogue);
            let resolver = CellReferenceResolver::new(&catalogue);
            let _ = resolver.resolve_all(&record);
            let _ = record.claim(spore_cellcontent::claims::SERIALIZER_ENVELOPE_ABSENT);
        }
    }
}

#[test]
fn an_all_zero_record_of_every_type_decodes_and_survives_the_pipeline() {
    // Zero is the byte most likely to be "the field is absent" in real data, so
    // it is worth a dedicated pass: no field may be indexed by a count that a
    // zero byte can make inconsistent with the record length.
    for type_id in SUPPORTED_TYPES {
        for len in [
            0usize, 1, 4, 8, 12, 16, 20, 24, 28, 36, 76, 180, 276, 796, 1024,
        ] {
            let zeros = vec![0u8; len];
            match decode(type_id, &zeros) {
                Ok(content) => {
                    assert_eq!(content.type_id(), type_id);
                    let catalogue = CellCatalogue::new();
                    let issues = content.issues(&catalogue);
                    let record = spore_cellcontent::CellContentRecord::new(
                        spore_cellcontent::ResourceKey::new(type_id, 0, 1),
                        content,
                    );
                    let _ = record.references();
                    let _ = issues;
                }
                Err(error) => assert_eq!(error.type_id(), type_id),
            }
        }
    }
}

#[test]
fn the_variant_accessors_never_panic_on_a_zeroed_record() {
    // Every accessor the crate exposes over a decoded value, on the input most
    // likely to be degenerate.
    let cases = [
        spore_cellcontent::GLOBALS_TYPE,
        spore_cellcontent::EFFECT_MAP_TYPE,
        spore_cellcontent::BACKGROUND_MAP_TYPE,
        spore_cellcontent::STRUCTURE_TYPE,
        spore_cellcontent::WORLD_TYPE,
        spore_cellcontent::RANDOM_CREATURE_TYPE,
        spore_cellcontent::POWERS_TYPE,
        spore_cellcontent::LOOK_TABLE_TYPE,
        spore_cellcontent::LOOK_ALGORITHM_TYPE,
        spore_cellcontent::LOOT_TABLE_TYPE,
        spore_cellcontent::POPULATE_TYPE,
        spore_cellcontent::CELL_TYPE,
    ];
    for type_id in cases {
        // A zero buffer of the exact right length for the three fixed records,
        // and a header-only buffer for the counted ones.
        for len in [0usize, 8, 16, 28, 36] {
            let zeros = vec![0u8; len];
            let Ok(content) = decode(type_id, &zeros) else {
                continue;
            };
            match content {
                CellContent::Globals(value) => {
                    let _ = value.entries();
                    let _ = value.reference_slots();
                    let _ = value.lookup("gameMode");
                    let _ = value.lookup("nope");
                }
                CellContent::BackgroundMap(value) => {
                    let _ = spore_cellcontent::sample_background_color(&value, 1.0);
                    let _ = spore_cellcontent::sample_background_color(&value, f32::NAN);
                    let _ = spore_cellcontent::background_color_envelope(&value);
                }
                CellContent::Cell(value) => {
                    let _ = value.scalars();
                    let _ = value.flags();
                    let _ = value.ai_tiers();
                    for ai in value.ai_tiers() {
                        let _ = ai.floats();
                        let _ = ai.flags();
                        let _ = ai.is_empty();
                        let _ = ai.movement_style_meaning();
                        let _ = ai.food_meaning();
                    }
                }
                CellContent::Structure(value) => {
                    let _ = value.header_effects();
                    for attachment in &value.attachments {
                        let _ = attachment.structure_meaning();
                        let _ = attachment.effect_id_meaning();
                    }
                }
                CellContent::RandomCreature(value) => {
                    for entry in &value.entries {
                        let _ = entry.stats();
                        let _ = entry.creature_id_meaning();
                    }
                }
                CellContent::LookAlgorithm(value) => {
                    for entry in &value.entries {
                        let _ = entry.look_tables();
                    }
                }
                _ => {}
            }
        }
    }
}

#[test]
fn an_empty_slice_never_panics_for_any_type() {
    for type_id in SUPPORTED_TYPES {
        let error =
            decode(type_id, &[]).expect_err("an empty buffer decodes to nothing for every type");
        assert!(!error.to_string().is_empty());
    }
}
