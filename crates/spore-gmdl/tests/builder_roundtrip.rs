//! The synthetic builder, round-tripped through the parser.
//!
//! `tests/fixture_parse.rs` proves this decoder reads bytes it did not write.
//! This file proves the opposite direction: that a record written from a forward
//! description of the format - the section list in `src/assets/Gmdl.hpp`, the
//! `cargo` reference tables and `docs/ASSET-PATH.md` §3 - comes back out of the
//! parser with the values it was given. A fixture cannot do this, because both
//! sides of it could be wrong in the same way.
//!
//! The minimal record built here is deliberately the same shape as the one
//! `src/assets/tests/assets_test.cpp:buildGmdl` writes: three positions in the
//! z = 0 plane, indices 0/1/2, a POSITION-only descriptor, and the bounds the
//! C++ test asserts (`bboxMin (0,0,0)`, `bboxMax (1,1,0)`, `radius sqrt(0.5)`).

mod common;

use common::{
    interleaved_vertices, Builder, Element, IndexBuffer, MaterialEntry, TextureEntry, Trailer,
    VertexBufferSpec,
};
use spore_gmdl::{
    compute_mesh_bounds, mesh_from_gmdl, parse, vertex_stride, DeclType, DeclUsage, GmdlError,
    Topology,
};

#[test]
fn the_minimal_record_round_trips() {
    let data = Builder::minimal().build();
    let model = parse(&data).expect("the minimal record is valid");

    assert_eq!(model.version, 8);
    assert!(model.referenced_files.is_empty());
    assert_eq!(model.mesh_count, 1);
    assert_eq!(model.bounds_min, [0.0, 0.0, 0.0]);
    assert_eq!(model.bounds_max, [1.0, 1.0, 0.0]);
    assert_eq!(model.radius, std::f32::consts::FRAC_1_SQRT_2);
    assert_eq!(model.index_buffers.len(), 1);
    assert_eq!(model.descriptors.len(), 1);
    assert_eq!(model.vertex_buffers.len(), 1);
    assert_eq!(model.meshes.len(), 1);
    assert_eq!(model.material_ids, vec![0x1234_5678]);
    assert!(model.texture_refs.is_empty());
    assert_eq!(model.bone_ranges, Vec::new());
    assert_eq!(model.unknown_key, [0, 0, 0]);
    assert_eq!(model.consumed, data.len());
    assert_eq!(model.strict_consumed, data.len());
    assert!(model.fully_walked());

    // Section offsets, forward: version (4) + refCount (4) + meshCount (4).
    assert_eq!(common::u32_at(&data, 0), Some(8));
    assert_eq!(
        common::u32_at(&data, 4),
        Some(0),
        "the refCount word, big-endian zero"
    );
    assert_eq!(common::u32_at(&data, 8), Some(1));
}

#[test]
fn the_minimal_mesh_yields_exactly_the_three_written_vertices() {
    let data = Builder::minimal().build();
    let model = parse(&data).expect("parse");
    let mesh = mesh_from_gmdl(&model, 0).expect("mesh");

    assert_eq!(mesh.positions.len(), 3);
    assert_eq!(
        mesh.positions,
        vec![[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, 0.0]]
    );
    assert_eq!(mesh.indices, vec![0, 1, 2]);
    assert_eq!(mesh.topology, Topology::TriangleList);
    assert!(mesh.normals.is_empty(), "POSITION-only descriptor");
    assert!(mesh.uvs.is_empty(), "POSITION-only descriptor");

    // The same bounds src/assets/tests/assets_test.cpp asserts.
    assert_eq!(mesh.bounds_min, [0.0, 0.0, 0.0]);
    assert_eq!(mesh.bounds_max, [1.0, 1.0, 0.0]);
    let half_diagonal = std::f32::consts::FRAC_1_SQRT_2;
    assert!(
        (mesh.radius - half_diagonal).abs() < 1e-6,
        "radius {}",
        mesh.radius
    );

    // And the stride the descriptor implies.
    let descriptor = model.descriptors.first().expect("descriptor");
    assert_eq!(vertex_stride(descriptor), Ok(12));
}

#[test]
fn a_position_normal_uv_descriptor_round_trips() {
    // The real-record layout from docs/ASSET-PATH.md: POSITION/FLOAT3 at 0,
    // NORMAL/UBYTE4 at 12, TEXCOORD/FLOAT2 at 16 -> stride 24.
    let positions = [[0.0f32, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, 0.0]];
    let normals = [[230u8, 107, 59], [0, 0, 255], [255, 255, 255]];
    let uvs = [[0.0f32, 0.0], [0.5, 0.25], [1.0, 1.0]];
    let payload = interleaved_vertices(&positions, &normals, &uvs, 12, 16);
    let record = Builder::minimal()
        .descriptors(vec![vec![
            Element::new(0, 2, 0),
            Element::new(12, 5, 3),
            Element::new(16, 1, 5),
        ]])
        .vertex_buffers(vec![VertexBufferSpec::new(0, 3, payload)])
        .build();

    let model = parse(&record).expect("parse");
    let descriptor = model.descriptors.first().expect("descriptor");
    assert_eq!(vertex_stride(descriptor), Ok(24));
    assert_eq!(descriptor.len(), 3);
    // Every element field survives the walk.
    assert_eq!(
        descriptor
            .first()
            .map(|e| (e.stream, e.offset, e.decl_type, e.decl_usage)),
        Some((0, 0, 2, 0))
    );
    assert_eq!(
        descriptor
            .get(1)
            .map(|e| (e.offset, e.decl_type, e.decl_usage)),
        Some((12, 5, 3))
    );
    assert_eq!(
        descriptor
            .get(2)
            .map(|e| (e.offset, e.decl_type, e.decl_usage)),
        Some((16, 1, 5))
    );
    assert_eq!(
        descriptor
            .first()
            .and_then(|e| DeclType::from_code(e.decl_type)),
        Some(DeclType::Float3)
    );
    assert_eq!(
        descriptor
            .get(1)
            .and_then(|e| DeclUsage::from_code(e.decl_usage)),
        Some(DeclUsage::Normal)
    );

    let mesh = mesh_from_gmdl(&model, 0).expect("mesh");
    assert_eq!(mesh.positions.len(), 3);
    assert_eq!(mesh.normals.len(), 3);
    assert_eq!(mesh.uvs.len(), 3);
    assert_eq!(mesh.positions, positions.to_vec());
    assert_eq!(mesh.uvs, uvs.to_vec());
    // The `/255` reproduction, exactly as docs/ASSET-PATH.md reports it for the
    // real record's first vertex: (230, 107, 59) -> (0.902, 0.420, 0.231).
    let first_normal = mesh.normals.first().copied().expect("normal 0");
    assert_eq!(first_normal[0].to_bits(), (230.0f32 / 255.0).to_bits());
    assert_eq!(first_normal[1].to_bits(), (107.0f32 / 255.0).to_bits());
    assert_eq!(first_normal[2].to_bits(), (59.0f32 / 255.0).to_bits());
    assert!((first_normal[0] - 0.902).abs() < 1e-3);
    assert!((first_normal[1] - 0.420).abs() < 1e-3);
    assert!((first_normal[2] - 0.231).abs() < 1e-3);
    // A normal byte of 255 is 1.0 and 0 is 0.0: the mapping is unsigned, which is
    // exactly why it cannot be the signed/bias-corrected decode it might be.
    assert_eq!(mesh.normals.get(1).copied(), Some([0.0, 0.0, 1.0]));
    assert_eq!(mesh.normals.get(2).copied(), Some([1.0, 1.0, 1.0]));
}

#[test]
fn ignored_elements_still_count_towards_the_stride() {
    // A COLOR element this path does not consume must still occupy its bytes, or
    // the texcoord would be read from the wrong offset.
    let positions = [[0.0f32, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, 0.0]];
    let uvs = [[0.25f32, 0.75], [0.5, 0.5], [0.0, 1.0]];
    // POSITION (0..12), COLOR/D3DCOLOR (12..16), TEXCOORD (16..24) -> stride 24.
    let mut payload = Vec::new();
    for index in 0..3 {
        for value in positions[index] {
            payload.extend_from_slice(&value.to_le_bytes());
        }
        payload.extend_from_slice(&[0x11, 0x22, 0x33, 0x44]);
        payload.extend_from_slice(&uvs[index][0].to_le_bytes());
        payload.extend_from_slice(&uvs[index][1].to_le_bytes());
    }
    let record = Builder::minimal()
        .descriptors(vec![vec![
            Element::new(0, 2, 0),
            Element::new(12, 4, 10),
            Element::new(16, 1, 5),
        ]])
        .vertex_buffers(vec![VertexBufferSpec::new(0, 3, payload)])
        .build();
    let model = parse(&record).expect("parse");
    assert_eq!(
        vertex_stride(model.descriptors.first().expect("descriptor")),
        Ok(24)
    );
    let mesh = mesh_from_gmdl(&model, 0).expect("mesh");
    assert_eq!(
        mesh.uvs,
        uvs.to_vec(),
        "the texcoord is read past the ignored colour"
    );
    assert!(mesh.normals.is_empty());
}

#[test]
fn a_texture_set_round_trips_in_order_of_appearance() {
    let record = Builder::minimal()
        .material_info(vec![
            vec![MaterialEntry::textures(vec![
                TextureEntry::new(0, 0xAAAA_AAAA, 0xBBBB_BBBB),
                TextureEntry::new(1, 0xCCCC_CCCC, 0xDDDD_DDDD),
            ])],
            vec![MaterialEntry::Shader(0x210)],
            vec![MaterialEntry::textures(vec![TextureEntry::new(
                2,
                0xEEEE_EEEE,
                0xFFFF_FFFF,
            )
            .opaque([0xA5; 12])])],
        ])
        .build();
    let model = parse(&record).expect("parse");
    assert_eq!(
        model.texture_refs.len(),
        3,
        "two blocks, three textures, order preserved"
    );
    assert_eq!(
        model
            .texture_refs
            .first()
            .map(|t| (t.instance_id, t.group_id)),
        Some((0xAAAA_AAAA, 0xBBBB_BBBB))
    );
    assert_eq!(
        model
            .texture_refs
            .get(1)
            .map(|t| (t.instance_id, t.group_id)),
        Some((0xCCCC_CCCC, 0xDDDD_DDDD))
    );
    assert_eq!(
        model
            .texture_refs
            .get(2)
            .map(|t| (t.instance_id, t.group_id)),
        Some((0xEEEE_EEEE, 0xFFFF_FFFF))
    );
    // A group of 0xFFFFFFFF is the wildcard, and is preserved as such rather than
    // being normalised away.
    assert!(!model.texture_refs.get(2).expect("third").group_id == 0);
    assert!(
        model.fully_walked(),
        "three material blocks walked to the exact end"
    );
}

#[test]
fn every_documented_shader_id_can_be_skipped() {
    // All 49 ids in one material block: if any length were wrong the walk would
    // not land on the record end, which `fully_walked` then asserts.
    let ids: Vec<MaterialEntry> = spore_gmdl::SHADER_DATA_SIZES
        .iter()
        .map(|entry| MaterialEntry::Shader(entry.id))
        .collect();
    let record = Builder::minimal().material_info(vec![ids]).build();
    let model = parse(&record).expect("every documented shader id");
    assert!(model.texture_refs.is_empty());
    assert!(model.fully_walked());
    assert_eq!(spore_gmdl::SHADER_DATA_SIZES.len(), 49);
}

#[test]
fn bone_ranges_round_trip() {
    let record = Builder::minimal()
        .trailer(Trailer::Full {
            bone_ranges: vec![(0, 4), (4, 12), (16, 0)],
            anim_datas: Vec::new(),
            unknown_key: [1, 2, 3],
        })
        .build();
    let model = parse(&record).expect("parse");
    assert_eq!(model.bone_ranges, vec![(0, 4), (4, 12), (16, 0)]);
    assert_eq!(model.unknown_key, [1, 2, 3]);
    assert!(model.fully_walked());
}

#[test]
fn anim_data_with_baked_deforms_round_trips() {
    // One anim-data record with two baked deforms: 144 bytes of fixed prefix plus
    // the count word plus 8 payload bytes.
    let record = Builder::minimal()
        .trailer(Trailer::Full {
            bone_ranges: vec![(3, 7)],
            anim_datas: vec![(2, vec![0xAAAA_AAAA, 0])],
            unknown_key: [0, 0xFFFF_FFFF, 0],
        })
        .build();
    let model = parse(&record).expect("parse");
    assert_eq!(model.bone_ranges, vec![(3, 7)]);
    assert_eq!(model.unknown_key, [0, 0xFFFF_FFFF, 0]);
    assert!(model.fully_walked());
    // The walked length is the whole record.
    assert_eq!(model.strict_consumed, record.len());
    assert_eq!(model.consumed, record.len());
}

#[test]
fn strict_and_best_effort_tails_differ_only_when_the_tail_is_short() {
    // A record whose trailer overruns the record end: the C++ reference accepts
    // it because the tail is best-effort, and the opaque remainder becomes part of
    // the record. That is the documented behaviour, and it is the only case where
    // `strict_consumed` and `consumed` differ.
    let record = Builder::minimal().trailer(Trailer::Filler(24)).build();
    let model = parse(&record).expect("a short tail does not fail the parse");
    assert_eq!(model.consumed, record.len());
    assert_eq!(
        model.strict_consumed,
        record.len() - 20,
        "the walk read 4 bytes of the filler"
    );
    assert!(!model.fully_walked());
    assert!(model.trailer.is_truncated());
    assert!(
        model.bone_ranges.is_empty(),
        "no bone ranges were read - and the trailer says so"
    );

    // A record whose trailer claims more bone ranges than the record can hold:
    // the count word is read, the array is not, and the empty `bone_ranges` means
    // "not read", not "none".
    let mut record = Builder::minimal().build();
    // The bone-range count word is 20 bytes from the end (4 bone-count + 4
    // anim-count + 12 key).
    let bone_count_offset = record.len() - 20;
    record[bone_count_offset..bone_count_offset + 4].copy_from_slice(&9u32.to_le_bytes());
    let model = parse(&record).expect("a short tail does not fail the parse");
    assert_eq!(model.bone_ranges, Vec::<(u32, u32)>::new());
    assert_eq!(
        model.trailer.stopped_at(),
        Some(spore_gmdl::TrailerStage::BoneRanges)
    );
    assert!(model.strict_consumed < model.consumed);
    // The count word says nine and the bytes are not there: nothing was read.
    assert!(!model.fully_walked());
}

#[test]
fn a_record_with_no_mesh_data_still_parses() {
    // The real record captured in tests/expected/real_gmdl_1006.json is exactly
    // this shape: meshCount 0 and no buffers at all.
    let record = Builder::empty_mesh()
        .bounds(
            [0.1676, 0.4499, -0.6402],
            [0.1798, 0.4499, 16.4433],
            16.4503,
        )
        .trailer(Trailer::Full {
            bone_ranges: Vec::new(),
            anim_datas: Vec::new(),
            unknown_key: [0, 0xFFFF_FFFF, 0],
        })
        .build();

    let model = parse(&record).expect("an empty-mesh gmdl is a valid gmdl");
    assert_eq!(model.mesh_count, 0);
    assert!(model.meshes.is_empty());
    assert!(model.index_buffers.is_empty());
    assert!(model.descriptors.is_empty());
    assert!(model.vertex_buffers.is_empty());
    assert!(model.material_ids.is_empty());
    assert!(model.texture_refs.is_empty());
    assert_eq!(model.unknown_key, [0, 0xFFFF_FFFF, 0]);
    assert!(model.fully_walked());
    // Its geometry is its bounding box.
    assert_eq!(model.bounds_min[0], 0.1676);
    assert_eq!(model.bounds_max[2], 16.4433);
    assert!((model.radius - 16.4503).abs() < 1e-4);
    // And there is no mesh to extract, which is an error rather than an empty mesh.
    assert_eq!(
        mesh_from_gmdl(&model, 0),
        Err(GmdlError::MeshIndexOutOfRange {
            mesh_index: 0,
            mesh_count: 0
        })
    );
    // The record is 80 bytes, exactly the size of the real record this mirrors:
    // 40 bytes of header and bounds, three buffer-count words, the zero word, the
    // material-info count, two trailer counts and the 12-byte key.
    assert_eq!(record.len(), 80);
    assert_eq!(common::u32_at(&record, 8), Some(0), "meshCount 0");
    assert_eq!(
        common::u32_at(&record, 80 - 20),
        Some(0),
        "boneRangeCount 0"
    );
    assert_eq!(common::u32_at(&record, 80 - 16), Some(0), "animDataCount 0");
}

#[test]
fn a_second_mesh_reads_its_own_buffers() {
    // Two meshes over two buffer pairs, so the mesh table is not accidentally
    // always read as mesh 0.
    // POSITION-only descriptors, so the payload is 12 bytes per vertex with no
    // padding (a padded row would make the descriptor's stride a lie).
    let first = common::positions_payload(&[[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.0, 1.0, 0.0]]);
    let second = common::positions_payload(&[[5.0, 5.0, 5.0], [6.0, 5.0, 5.0], [5.0, 6.0, 5.0]]);
    let record = Builder::minimal()
        .index_buffers(vec![
            IndexBuffer::triangles(&[0, 1, 2]),
            IndexBuffer::triangles(&[0, 2, 1]),
        ])
        .vertex_buffers(vec![
            VertexBufferSpec::new(0, 3, first),
            VertexBufferSpec::new(0, 3, second),
        ])
        .meshes(vec![(0, 0), (1, 1)])
        .material_ids(vec![0x1111, 0x2222])
        .build();
    let model = parse(&record).expect("parse");
    assert_eq!(model.mesh_count, 2);
    assert_eq!(model.meshes.len(), 2);
    assert_eq!(model.material_ids, vec![0x1111, 0x2222]);

    let mesh0 = mesh_from_gmdl(&model, 0).expect("mesh 0");
    let mesh1 = mesh_from_gmdl(&model, 1).expect("mesh 1");
    assert_eq!(mesh0.positions[0], [0.0, 0.0, 0.0]);
    assert_eq!(mesh1.positions[0], [5.0, 5.0, 5.0]);
    assert_eq!(mesh0.indices, vec![0, 1, 2]);
    assert_eq!(
        mesh1.indices,
        vec![0, 2, 1],
        "the second buffer's own order"
    );
    assert_eq!(mesh1.bounds_min, [5.0, 5.0, 5.0]);
    assert_eq!(mesh1.bounds_max, [6.0, 6.0, 5.0]);

    // Bounds are recomputed per mesh, not shared across the model.
    let mut copy = mesh1.clone();
    copy.positions[0] = [0.0, 0.0, 0.0];
    compute_mesh_bounds(&mut copy);
    assert_eq!(copy.bounds_min, [0.0, 0.0, 0.0]);
}

#[test]
fn referenced_files_round_trip_in_order() {
    let record = Builder::minimal()
        .refs(vec![
            [0x0000_0001, 0x4061_6201, 0x00E6_BCE5],
            [0x0000_0002, 0x4062_7100, 0x2F4E_681C],
            [0x0000_0003, 0x4061_6201, 0x2F4E_681B],
        ])
        .build();
    let model = parse(&record).expect("parse");
    assert_eq!(model.referenced_files.len(), 3);
    assert_eq!(
        model.referenced_files[0].to_tgi(),
        "0x00e6bce5:0x40616201:0x00000001"
    );
    assert_eq!(
        model.referenced_files[1].to_tgi(),
        "0x2f4e681c:0x40627100:0x00000002"
    );
    assert_eq!(
        model.referenced_files[2].to_tgi(),
        "0x2f4e681b:0x40616201:0x00000003"
    );
    // The group bytes are structured, and that structure survives the reorder.
    let group = model.referenced_files[0].group_id;
    assert_eq!((group >> 8) & 0xFF, 0x62, "stage byte");
    assert_eq!((group >> 16) & 0xFF, 0x61, "category byte");
    assert!(model.fully_walked());
}

#[test]
fn a_three_mesh_record_is_not_refused_by_the_mesh_table_threshold() {
    // Three meshes is where a transcribed `meshCount * 16` threshold stops
    // agreeing with `12 * meshCount + 8`: for three meshes the transcribed one
    // demands 52 bytes where 44 suffice. A record that is complete must not be
    // refused by a threshold that is merely conservative, so this test builds the
    // smallest complete three-mesh record there is and requires it to parse.
    let payload = common::positions_payload(&[[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.0, 1.0, 0.0]]);
    let record = Builder::minimal()
        .index_buffers(vec![
            IndexBuffer::triangles(&[0, 1, 2]),
            IndexBuffer::triangles(&[0, 1, 2]),
            IndexBuffer::triangles(&[0, 1, 2]),
        ])
        .vertex_buffers(vec![
            VertexBufferSpec::new(0, 3, payload.clone()),
            VertexBufferSpec::new(0, 3, payload.clone()),
            VertexBufferSpec::new(0, 3, payload),
        ])
        .meshes(vec![(0, 0), (1, 1), (2, 2)])
        .material_ids(vec![1, 2, 3])
        .build();

    let model = parse(&record).expect("a complete three-mesh record must parse");
    assert_eq!(model.mesh_count, 3);
    assert_eq!(model.meshes.len(), 3);
    assert_eq!(model.material_ids, vec![1, 2, 3]);
    assert!(model.fully_walked());
    for index in 0..3u32 {
        let mesh = mesh_from_gmdl(&model, index).expect("each mesh extracts");
        assert_eq!(mesh.indices, vec![0, 1, 2]);
    }

    // The negative side of this threshold cannot be reached by truncating this
    // record: the buffer tables come first, so a short prefix fails there (and
    // `tests/robustness.rs` sweeps that exhaustively). What matters here is the
    // positive side - a complete three-mesh record must parse - because a
    // threshold that is merely conservative still refuses valid records.
    let mesh_table_start = 12usize;
    let point = common::u32_at(&record, 8);
    assert_eq!(
        point,
        Some(3),
        "meshCount sits at offset 8 in a 0-reference record"
    );
    assert!(
        record.len() > mesh_table_start + 3 * 12 + 8,
        "the record has room for its mesh table"
    );
}
