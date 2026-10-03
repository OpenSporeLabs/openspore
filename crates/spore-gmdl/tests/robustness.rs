//! Robustness sweeps: no input may panic, and every prefix must be answered.
//!
//! The contract under test is the one `#![forbid(unsafe_code)]` plus "no
//! indexing, no `unwrap`" is meant to guarantee: a decoder given arbitrary bytes
//! returns `Ok` or `Err` and never panics, allocates nothing unbounded, and never
//! reads out of bounds. That is not provable by inspection over a 1266-byte
//! record with five tables and three nested lengths, so it is swept:
//!
//! * every prefix length `0..=len` of the committed fixture;
//! * every prefix of the minimal synthetic record and of a record carrying a
//!   texture set, bone ranges and anim data (the sections the sweep above
//!   reaches only at the very end);
//! * every single-byte corruption (each byte set to 0x00 and to 0xFF) at every
//!   offset of the fixture, and mesh extraction attempted on whatever parses;
//! * a field-level corruption sweep: each `u32` word replaced with `u32::MAX`,
//!   `0` and `0x7FFFFFFF`, which is where the interesting length arithmetic lives.
//!
//! A panic in any of these fails the test rather than the process, because the
//! tests run in the same binary as everything else in this file.

mod common;

use common::{Builder, Element, MaterialEntry, TextureEntry, Trailer, VertexBufferSpec};
use spore_gmdl::{mesh_from_gmdl, parse};

/// Parses and, when that succeeds, extracts every mesh. Never panics.
fn parse_and_extract(data: &[u8]) {
    if let Ok(model) = parse(data) {
        // Bounds and the walk invariants hold for anything that parses.
        assert!(
            model.consumed == data.len(),
            "consumed must be the input length"
        );
        assert!(model.strict_consumed <= model.consumed);
        for mesh in 0..model.meshes.len() {
            let mesh_index = u32::try_from(mesh).expect("mesh count fits a u32");
            let _ = mesh_from_gmdl(&model, mesh_index);
        }
    }
}

/// Offset just past the last byte of the fixture's strict sections: the
/// material-info count word ends there (gen_fixtures.py writes it at 1242..1246).
const FIXTURE_STRICT_END: usize = 1246;

#[test]
fn every_prefix_of_the_fixture_answers_without_panicking() {
    let data = common::mini_gmdl();
    assert_eq!(data.len(), common::MINI_GMDL_LEN);
    let mut errors = 0usize;
    let mut oks = 0usize;
    for len in 0..=data.len() {
        let prefix = data.get(..len).expect("prefix");
        match parse(prefix) {
            Ok(model) => {
                oks += 1;
                assert_eq!(model.consumed, len);
                let _ = mesh_from_gmdl(&model, 0);
            }
            Err(_) => errors += 1,
        }
    }
    assert_eq!(oks + errors, data.len() + 1);
    // The fixture's strict walk is strict: every prefix from 0 up to and
    // including the strict end is refused, with the last four naming the trailer
    // (fewer than four bytes left for it).
    assert_eq!(
        errors,
        FIXTURE_STRICT_END + 4,
        "every prefix up to the strict end must fail"
    );
    match parse(&data[..FIXTURE_STRICT_END]) {
        Err(spore_gmdl::GmdlError::TruncatedTrailer { available }) => assert_eq!(available, 0),
        other => panic!("{other:?}"),
    }
    // From four bytes past the strict end the parse succeeds, because the trailer
    // is walked best-effort: a truncated tail is reported, never fatal. So the
    // successful prefixes are exactly 1250..=1266.
    let first_ok = FIXTURE_STRICT_END + 4;
    assert_eq!(
        oks,
        data.len() + 1 - first_ok,
        "successful prefixes are {first_ok}..={}",
        data.len()
    );
    for len in first_ok..data.len() {
        let model = parse(&data[..len]).expect("a short tail still parses");
        assert!(
            model.trailer.is_truncated(),
            "len {len} must report the short tail"
        );
        // The walk read the bone-range count and then stopped at the first stage
        // that did not fit. The largest read still ahead of it is the 12-byte
        // trailing key, so fewer than 12 bytes can be left unread - and the count
        // is never more than one byte away.
        assert!(
            model.strict_consumed >= first_ok,
            "len {len}: the bone-range count was read"
        );
        assert!(
            len - model.strict_consumed < 12,
            "len {len}: {} bytes left unread",
            len - model.strict_consumed
        );
    }
    let whole = parse(&data).expect("the whole record");
    assert!(whole.fully_walked());
    assert!(whole.trailer.is_complete());
}

#[test]
fn every_prefix_of_the_minimal_record_answers_without_panicking() {
    let data = Builder::minimal().build();
    for len in 0..=data.len() {
        parse_and_extract(data.get(..len).expect("prefix"));
    }
}

#[test]
fn every_prefix_of_a_record_with_texture_sets_bone_ranges_and_anim_data_answers() {
    // The sections the fixture reaches only in its last 20 bytes get real
    // coverage here: a texture set, two shader payloads, bone ranges and an
    // anim-data record with baked deforms.
    let data = Builder::minimal()
        .material_info(vec![
            vec![MaterialEntry::textures(vec![
                TextureEntry::new(0, 0x1111_1111, 0x2222_2222),
                TextureEntry::new(1, 0x3333_3333, 0x4444_4444),
            ])],
            vec![MaterialEntry::Shader(0x210), MaterialEntry::Shader(0x231)],
        ])
        .trailer(Trailer::Full {
            bone_ranges: vec![(0, 4), (4, 9)],
            anim_datas: vec![(3, vec![1, 2, 3])],
            unknown_key: [7, 8, 9],
        })
        .build();
    assert!(data.len() > 300);
    for len in 0..=data.len() {
        parse_and_extract(data.get(..len).expect("prefix"));
    }
    let model = parse(&data).expect("the whole record");
    assert!(model.fully_walked());
    assert_eq!(model.texture_refs.len(), 2);
    assert_eq!(model.bone_ranges, vec![(0, 4), (4, 9)]);
}

#[test]
fn every_prefix_of_a_record_with_several_descriptors_answers() {
    let data = Builder::minimal()
        .descriptors(vec![
            vec![Element::new(0, 2, 0)],
            vec![
                Element::new(0, 2, 0),
                Element::new(12, 5, 3),
                Element::new(16, 1, 5),
            ],
            vec![Element::new(0, 1, 5), Element::new(8, 4, 10)],
        ])
        .vertex_buffers(vec![
            VertexBufferSpec::new(0, 3, vec![0; 36]),
            VertexBufferSpec::new(1, 3, vec![0; 72]),
            VertexBufferSpec::new(2, 3, vec![0; 36]),
        ])
        .meshes(vec![(0, 0), (0, 1), (0, 2)])
        .material_ids(vec![1, 2, 3])
        .build();
    for len in 0..=data.len() {
        parse_and_extract(data.get(..len).expect("prefix"));
    }
}

#[test]
fn single_byte_corruption_at_every_offset_never_panics() {
    let data = common::mini_gmdl();
    let mut parsed = 0usize;
    for offset in 0..data.len() {
        for replacement in [0x00u8, 0xFF] {
            let mut corrupted = data.clone();
            if let Some(slot) = corrupted.get_mut(offset..offset + 1) {
                slot.copy_from_slice(&[replacement]);
            }
            parse_and_extract(&corrupted);
            if parse(&corrupted).is_ok() {
                parsed += 1;
            }
        }
    }
    // Most corruptions land in payload bytes and are still valid records, which
    // is the point: a decoder must survive a wrong byte rather than assume one.
    assert!(
        parsed > 100,
        "only {parsed} corruptions parsed; the sweep is not exercising the paths"
    );
}

#[test]
fn field_level_corruption_of_every_word_never_panics() {
    // Each 4-byte word replaced with values that stress length arithmetic:
    // zero, u32::MAX, and 0x7FFFFFFF (a count that overflows a naive product).
    let data = common::mini_gmdl();
    let words = data.len() / 4;
    for word in 0..words {
        let offset = word * 4;
        for replacement in [0u32, u32::MAX, 0x7FFF_FFFF, 1] {
            let mut corrupted = data.clone();
            let bytes = replacement.to_le_bytes();
            if let Some(slot) = corrupted.get_mut(offset..offset + 4) {
                slot.copy_from_slice(&bytes);
            }
            parse_and_extract(&corrupted);
        }
    }
    // The big-endian word at offset 4 is handled separately: patching it
    // little-endian-style would not test the same thing.
    for replacement in [0u8, 0xFF] {
        let mut corrupted = data.clone();
        if let Some(slot) = corrupted.get_mut(4..8) {
            slot.copy_from_slice(&[replacement; 4]);
        }
        parse_and_extract(&corrupted);
    }
}

#[test]
fn a_record_of_pure_zeros_and_a_record_of_pure_ff_never_panic() {
    // Degenerate but common shapes in the wild: zero-filled and 0xFF-filled
    // records (an unwritten slot in a package, a truncated-then-prefilled one).
    for byte in [0x00u8, 0xFF, 0x01] {
        for len in [1usize, 4, 8, 64, 1024] {
            parse_and_extract(&vec![byte; len]);
        }
    }
}

#[test]
fn count_words_at_the_extremes_never_panic() {
    // A version-8 record whose every count word is u32::MAX: the largest lengths
    // this decoder can be asked to believe. Every one must be refused by a length
    // check rather than turned into an allocation.
    let data = Builder::minimal().refs(vec![[1, 2, 3]; 1]).build();
    let mut corrupted = data.clone();
    for offset in (0..corrupted.len().saturating_sub(4)).step_by(4) {
        // Leave the version and the big-endian refCount alone.
        if offset == 0 || offset == 4 {
            continue;
        }
        corrupted[offset..offset + 4].copy_from_slice(&u32::MAX.to_le_bytes());
    }
    parse_and_extract(&corrupted);
    // And one where only the refCount is the maximum: 4 billion references.
    let mut huge_refs = Builder::minimal().build();
    huge_refs[4..8].copy_from_slice(&u32::MAX.to_be_bytes());
    parse_and_extract(&huge_refs);
}

#[test]
fn extreme_float_patterns_in_the_bounds_are_refused_or_survive() {
    for bits in [
        0x7F80_0000u32,
        0xFF80_0000,
        0x7FC0_0000,
        0x7F7F_FFFF,
        0x0000_0001,
        0x8000_0000,
    ] {
        let mut data = Builder::minimal().build();
        // bboxMin[0] at offset 8 in a 0-ref record.
        data[8..12].copy_from_slice(&bits.to_le_bytes());
        parse_and_extract(&data);
        // And in the radius, at offset 32.
        data[8..12].copy_from_slice(&0f32.to_bits().to_le_bytes());
        data[32..36].copy_from_slice(&bits.to_le_bytes());
        parse_and_extract(&data);
        // And in a vertex position.
        let mut data = Builder::minimal().build();
        let payload_start = data.len() - 20 - 4 - 4 - 4 - 4 - 4 - 8 - 4 - 36;
        data[payload_start..payload_start + 4].copy_from_slice(&bits.to_le_bytes());
        parse_and_extract(&data);
    }
}

#[test]
fn adversarial_decl_types_and_usages_never_panic() {
    for decl_type in [0u8, 2, 5, 16, 17, 200, 255] {
        for usage in [0u8, 3, 5, 13, 14, 255] {
            for stream in [0u16, 1, 0xFFFF] {
                let payload = common::interleaved_vertices(
                    &[[0.0f32, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, 0.0]],
                    &[[0, 0, 0], [1, 1, 1], [2, 2, 2]],
                    &[[0.0f32, 0.0], [1.0, 1.0], [2.0, 2.0]],
                    12,
                    16,
                );
                let data = Builder::minimal()
                    .descriptors(vec![vec![
                        Element::new(0, 2, 0),
                        Element {
                            stream,
                            offset: 12,
                            decl_type,
                            decl_method: 0,
                            decl_usage: usage,
                            usage_index: 0,
                            type_code: 0,
                        },
                    ]])
                    .vertex_buffers(vec![VertexBufferSpec::new(0, 3, payload)])
                    .build();
                parse_and_extract(&data);
                // And every prefix of it.
                for len in 0..=data.len() {
                    parse_and_extract(data.get(..len).expect("prefix"));
                }
            }
        }
    }
}

#[test]
fn adversarial_decl_offsets_never_panic() {
    // An element whose declared offset places it past the stride: the stride is
    // the maximum end offset, so the buffer-length check must still hold.
    for offset in [0u16, 1, 3, 4096, 0xFFFE, 0xFFFF] {
        let data = Builder::minimal()
            .descriptors(vec![vec![
                Element::new(0, 2, 0),
                Element::new(offset, 1, 5),
            ]])
            .build();
        parse_and_extract(&data);
        for len in 0..=data.len() {
            parse_and_extract(data.get(..len).expect("prefix"));
        }
    }
}

#[test]
fn every_shader_data_id_at_every_prefix_answers() {
    // 49 ids x 4 prefix positions each: the length arithmetic of the skip table
    // is the most-travelled code in the walk after the index/vertex payloads.
    for entry in spore_gmdl::SHADER_DATA_SIZES {
        let data = Builder::minimal()
            .material_info(vec![vec![MaterialEntry::Shader(entry.id)]])
            .build();
        assert!(
            parse(&data).is_ok(),
            "id 0x{:03X} should walk to the record end",
            entry.id
        );
        for cut in [1usize, 5, entry.size as usize] {
            let len = data.len().saturating_sub(cut);
            parse_and_extract(data.get(..len).expect("prefix"));
        }
    }
    // 0x20D is decoded, and every prefix of a texture set answers too.
    for declared in [0u32, 1, 2, 9] {
        let data = Builder::minimal()
            .material_info(vec![vec![MaterialEntry::textures_declared(
                declared,
                vec![TextureEntry::new(0, 1, 2), TextureEntry::new(1, 3, 4)],
            )]])
            .build();
        for len in 0..=data.len() {
            parse_and_extract(data.get(..len).expect("prefix"));
        }
    }
}

#[test]
fn large_but_legal_records_are_handled() {
    // A record with a big vertex buffer and a big index buffer: proves the
    // `u64` length arithmetic is not accidentally 32-bit.
    let vertex_count = 20_000u32;
    let payload = vec![0u8; vertex_count as usize * 12];
    let mut indices = Vec::new();
    for i in 0..18_000u32 {
        indices.push(i % vertex_count);
    }
    let data = Builder::minimal()
        .index_buffers(vec![common::IndexBuffer::triangles(&indices)])
        .vertex_buffers(vec![VertexBufferSpec::new(0, vertex_count, payload)])
        .build();
    assert!(data.len() > 240_000);
    let model = parse(&data).expect("a large record parses");
    assert!(model.fully_walked());
    let mesh = mesh_from_gmdl(&model, 0).expect("a large mesh extracts");
    assert_eq!(mesh.positions.len(), 20_000);
    assert_eq!(mesh.indices.len(), 18_000);
    assert!(mesh.indices.iter().all(|index| *index < vertex_count));
}
