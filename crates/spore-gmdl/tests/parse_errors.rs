//! One negative test per failure mode.
//!
//! Each test builds the *smallest* record that reaches the failure, so the error
//! under test is the reason the record is refused rather than an earlier one. The
//! `Builder`'s `*_count` / `size_word` knobs write exactly one lie per test, so
//! no test has to compute an offset into the middle of a record and hope.
//!
//! Coverage map for the variants that the truncation sweep in
//! `tests/robustness.rs` exercises at every neighbouring length: this file pins
//! the *section* each error names, and the sweep pins the boundary behaviour.

mod common;

use common::{
    f32_at, find_u32, patch_first_u32, u32_at, Builder, Element, IndexBuffer, MaterialEntry,
    TextureEntry, Trailer, VertexBufferSpec,
};
use spore_gmdl::{parse, GmdlError};

/// Asserts the error and that its message names the section under test.
fn expect(error: GmdlError, needle: &str) {
    let text = error.to_string();
    assert!(
        text.contains(needle),
        "message {text:?} does not name {needle:?}"
    );
}

// ---------------------------------------------------------------- header

#[test]
fn empty_input_is_refused() {
    // The C++ reference has an explicit null-pointer check here; a Rust slice
    // cannot be null, so the empty slice is that case.
    assert_eq!(parse(&[]), Err(GmdlError::EmptyInput));
    expect(GmdlError::EmptyInput, "empty input");
}

#[test]
fn a_one_to_three_byte_prefix_is_a_truncated_header() {
    for len in 1..4 {
        let data = vec![0u8; len];
        match parse(&data) {
            Err(GmdlError::TruncatedHeader { got }) => assert_eq!(got, len),
            other => panic!("len {len}: {other:?}"),
        }
    }
    expect(GmdlError::TruncatedHeader { got: 2 }, "truncated header");
}

#[test]
fn version_nine_is_named_and_refused() {
    let data = Builder::minimal().version(9).build();
    let error = parse(&data).expect_err("v9 must be refused");
    assert_eq!(error, GmdlError::UnsupportedVersion { version: 9 });
    let text = error.to_string();
    assert!(text.contains("unsupported version 9"), "{text}");
    assert!(
        text.contains('8'),
        "the message must say what is supported: {text}"
    );
    // Every other version is refused the same way, including versions the format
    // may never have had.
    for version in [0u32, 1, 7, 10, 0xFFFF_FFFF] {
        let data = Builder::minimal().version(version).build();
        assert_eq!(parse(&data), Err(GmdlError::UnsupportedVersion { version }));
    }
}

#[test]
fn a_truncated_refcount_word_is_refused() {
    // Bytes 4..8 missing: version present, refCount absent.
    let data = Builder::minimal().build();
    let cut = data.get(..6).expect("prefix").to_vec();
    assert_eq!(parse(&cut), Err(GmdlError::TruncatedRefCount));
    expect(GmdlError::TruncatedRefCount, "truncated refCount");
}

#[test]
fn a_truncated_reference_table_is_refused() {
    // Two references declared, one supplied.
    let data = Builder::minimal().refs(vec![[1, 2, 3], [4, 5, 6]]).build();
    let cut = data.get(..20).expect("prefix").to_vec();
    match parse(&cut) {
        Err(GmdlError::TruncatedReferencedFiles {
            count,
            needed,
            available,
        }) => {
            assert_eq!((count, needed), (2, 24));
            assert_eq!(available, 12);
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedReferencedFiles {
            count: 2,
            needed: 24,
            available: 12,
        },
        "truncated referenced-file table",
    );
}

// ---------------------------------------------------------------- bounds

#[test]
fn a_truncated_bounds_block_is_refused() {
    // meshCount + six bbox floats + radius is 28 bytes; cut inside it.
    let data = Builder::minimal().build();
    let cut = data.get(..24).expect("prefix").to_vec();
    match parse(&cut) {
        Err(GmdlError::TruncatedBounds { available }) => assert_eq!(available, 16),
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedBounds { available: 16 },
        "truncated bounds",
    );
}

#[test]
fn a_non_finite_bound_is_refused() {
    // With no referenced files the bbox starts at offset 12: version (4),
    // refCount (4), meshCount (4). Asserted rather than assumed.
    let base = Builder::minimal().build();
    assert_eq!(
        common::u32_at(&base, 8),
        Some(1),
        "meshCount is at offset 8"
    );
    assert_eq!(
        f32_at(&base, 12),
        Some(0.0),
        "bboxMin[0] is at offset 12 in a 0-ref record"
    );

    for (component, value) in [
        (0usize, f32::NAN),
        (1, f32::INFINITY),
        (5, f32::NEG_INFINITY),
    ] {
        let mut data = base.clone();
        let offset = 12 + 4 * component;
        let word = value.to_bits();
        let slot = data.get_mut(offset..offset + 4).expect("bbox word");
        slot.copy_from_slice(&word.to_le_bytes());
        match parse(&data) {
            Err(GmdlError::NonFiniteBounds {
                component: named,
                value: seen,
            }) => {
                let expected = if component < 3 { "bboxMin" } else { "bboxMax" };
                assert!(
                    named.starts_with(expected),
                    "{named} should name {expected}"
                );
                assert_eq!(seen.to_bits(), word);
            }
            other => panic!("component {component}: {other:?}"),
        }
    }
    expect(
        GmdlError::NonFiniteBounds {
            component: "bboxMin[0]",
            value: f32::NAN,
        },
        "non-finite bounds",
    );
}

#[test]
fn a_non_finite_radius_is_an_invalid_bounds_error() {
    // The radius is the seventh f32: offset 12 + 6 * 4.
    let mut data = Builder::minimal().build();
    assert_eq!(
        f32_at(&data, 36),
        Some(std::f32::consts::FRAC_1_SQRT_2),
        "radius at offset 36"
    );
    let slot = data.get_mut(36..40).expect("radius word");
    slot.copy_from_slice(&f32::INFINITY.to_bits().to_le_bytes());
    let error = parse(&data).expect_err("an infinite radius is refused");
    assert_eq!(
        error,
        GmdlError::InvalidBounds {
            radius: f32::INFINITY
        }
    );
    expect(error, "invalid bounds");
}

// ---------------------------------------------------------------- index buffers

#[test]
fn a_truncated_index_buffer_table_is_refused() {
    // Claims 11 index-buffer headers; the record has room for one.
    let data = Builder::minimal().index_buffers_count(11).build();
    match parse(&data) {
        Err(GmdlError::TruncatedIndexBufferTable {
            count,
            needed,
            available,
        }) => {
            assert_eq!(count, 11);
            assert_eq!(needed, 176);
            assert!(available < 176, "available {available}");
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedIndexBufferTable {
            count: 11,
            needed: 176,
            available: 0,
        },
        "truncated index-buffer table",
    );
}

#[test]
fn a_truncated_index_buffer_payload_is_refused() {
    // The header claims a 4 GB payload in a 170-byte record.
    let data = Builder::minimal()
        .index_buffers(vec![IndexBuffer::triangles(&[0, 1, 2]).size_word(u32::MAX)])
        .build();
    match parse(&data) {
        Err(GmdlError::TruncatedIndexBuffer { index, size }) => {
            assert_eq!(index, 0);
            assert_eq!(size, u32::MAX);
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedIndexBuffer {
            index: 0,
            size: u32::MAX,
        },
        "truncated index buffer 0",
    );
}

// ---------------------------------------------------------------- descriptors

#[test]
fn a_truncated_vertex_descriptor_table_is_refused() {
    // Claims 30 descriptors; the record holds one.
    let data = Builder::minimal().descriptors_count(30).build();
    match parse(&data) {
        Err(GmdlError::TruncatedVertexDescriptorTable { count, needed, .. }) => {
            assert_eq!(count, 30);
            assert_eq!(needed, 120);
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedVertexDescriptorTable {
            count: 30,
            needed: 120,
            available: 0,
        },
        "truncated vertex-descriptor table",
    );
}

#[test]
fn a_truncated_vertex_descriptor_is_refused() {
    // Claims nine elements where one is written.
    let data = Builder::minimal().elements_count(9).build();
    match parse(&data) {
        Err(GmdlError::TruncatedVertexDescriptor { index, count }) => {
            assert_eq!(index, 0);
            assert_eq!(count, 9);
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedVertexDescriptor { index: 0, count: 9 },
        "truncated vertex descriptor 0",
    );
}

#[test]
fn an_undocumented_decl_type_is_refused_with_code_and_descriptor_index() {
    // Code 17 is the first undocumented D3DDECLTYPE.
    let data = Builder::minimal()
        .descriptors(vec![vec![Element::new(0, 2, 0), Element::new(12, 17, 0)]])
        .build();
    let error = parse(&data).expect_err("an undocumented declType has no stride");
    assert_eq!(
        error,
        GmdlError::UndocumentedDeclType {
            code: 17,
            descriptor_index: Some(0)
        }
    );
    expect(error, "undocumented declType 17 in descriptor Some(0)");

    // A second descriptor names a different index, proving the index is the
    // descriptor's position and not a constant.
    let two = Builder::minimal()
        .descriptors(vec![
            vec![Element::new(0, 2, 0)],
            vec![Element::new(0, 200, 0)],
        ])
        .build();
    assert_eq!(
        parse(&two),
        Err(GmdlError::UndocumentedDeclType {
            code: 200,
            descriptor_index: Some(1)
        })
    );
    // And the message names the code in decimal, because declType is a small byte
    // value everywhere in this repository (unlike shader-data ids, which are
    // hexadecimal).
    assert!(GmdlError::UndocumentedDeclType {
        code: 17,
        descriptor_index: None
    }
    .to_string()
    .contains("declType 17"));
}

// ---------------------------------------------------------------- vertex buffers

#[test]
fn a_truncated_vertex_buffer_table_is_refused() {
    // Claims 12 vertex-buffer headers; the record holds one.
    let data = Builder::minimal().vertex_buffers_count(12).build();
    match parse(&data) {
        Err(GmdlError::TruncatedVertexBufferTable { count, needed, .. }) => {
            assert_eq!(count, 12);
            assert_eq!(needed, 144);
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedVertexBufferTable {
            count: 12,
            needed: 144,
            available: 0,
        },
        "truncated vertex-buffer table",
    );
}

#[test]
fn a_truncated_vertex_buffer_payload_is_refused() {
    let data = Builder::minimal()
        .vertex_buffers(vec![
            VertexBufferSpec::new(0, 3, vec![0; 36]).size_word(4096)
        ])
        .build();
    match parse(&data) {
        Err(GmdlError::TruncatedVertexBuffer { index, size }) => {
            assert_eq!(index, 0);
            assert_eq!(size, 4096);
        }
        other => panic!("{other:?}"),
    }
}

#[test]
fn a_vertex_buffer_naming_a_missing_descriptor_is_refused() {
    let data = Builder::minimal()
        .vertex_buffers(vec![VertexBufferSpec::new(7, 3, vec![0; 36])])
        .build();
    let error = parse(&data).expect_err("descriptor 7 does not exist");
    assert_eq!(
        error,
        GmdlError::BadDescriptorIndex {
            index: 0,
            desc_index: 7,
            desc_count: 1
        }
    );
    expect(error, "names descriptor 7 of 1");
}

// ---------------------------------------------------------------- mesh table

#[test]
fn a_truncated_mesh_table_is_refused() {
    // meshCount 3 with one mesh written.
    let data = Builder::minimal().mesh_count(3).build();
    match parse(&data) {
        Err(GmdlError::TruncatedMeshTable {
            mesh_count, needed, ..
        }) => {
            assert_eq!(mesh_count, 3);
            // 12 per mesh (reference pair + material id), plus the observed zero
            // word and the material-info count word that follows them.
            assert_eq!(needed, 3 * 12 + 8);
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedMeshTable {
            mesh_count: 3,
            needed: 44,
            available: 0,
        },
        "truncated mesh table",
    );
}

#[test]
fn a_mesh_naming_missing_buffers_is_refused() {
    let data = Builder::minimal().meshes(vec![(0, 5)]).build();
    let error = parse(&data).expect_err("vertex buffer 5 does not exist");
    match error {
        GmdlError::MeshReferencesMissingBuffer {
            mesh,
            index_buffer,
            vertex_buffer,
            index_buffers,
            vertex_buffers,
        } => {
            assert_eq!((mesh, index_buffer, vertex_buffer), (0, 0, 5));
            assert_eq!((index_buffers, vertex_buffers), (1, 1));
        }
        other => panic!("{other:?}"),
    }
    // And an out-of-range index buffer.
    let data = Builder::minimal().meshes(vec![(3, 0)]).build();
    assert!(matches!(
        parse(&data),
        Err(GmdlError::MeshReferencesMissingBuffer {
            index_buffer: 3,
            vertex_buffer: 0,
            ..
        })
    ));
    expect(
        GmdlError::MeshReferencesMissingBuffer {
            mesh: 0,
            index_buffer: 3,
            vertex_buffer: 0,
            index_buffers: 1,
            vertex_buffers: 1,
        },
        "mesh 0 references missing buffers",
    );
}

// ---------------------------------------------------------------- material info

#[test]
fn a_truncated_material_info_table_is_refused() {
    // Claims nine material blocks; the record holds none.
    let data = Builder::minimal().material_info_count(9).build();
    match parse(&data) {
        Err(GmdlError::TruncatedMaterialInfoTable { count, needed, .. }) => {
            assert_eq!(count, 9);
            assert_eq!(needed, 36);
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedMaterialInfoTable {
            count: 9,
            needed: 36,
            available: 0,
        },
        "truncated material-info table",
    );
}

#[test]
fn a_truncated_material_info_is_refused() {
    // One block claiming twelve entries: 4 * 12 = 48 bytes are needed and 40 are
    // left (the shader payload plus the trailer).
    let data = Builder::minimal()
        .material_info(vec![vec![MaterialEntry::Shader(0x210)]])
        .material_info_count(1)
        .material_entries_count(12)
        .build();
    match parse(&data) {
        Err(GmdlError::TruncatedMaterialInfo { index, count }) => {
            assert_eq!(index, 0);
            assert_eq!(count, 12);
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedMaterialInfo {
            index: 0,
            count: 12,
        },
        "truncated material info 0",
    );
}

#[test]
fn a_truncated_texture_set_is_refused() {
    let data = Builder::minimal()
        .material_info(vec![vec![MaterialEntry::textures_declared(
            3,
            vec![TextureEntry::new(0, 1, 2)],
        )]])
        .build();
    match parse(&data) {
        Err(GmdlError::TruncatedTextureSet { count, available }) => {
            assert_eq!(count, 3);
            assert!(available < 72, "available {available}");
        }
        other => panic!("{other:?}"),
    }
    expect(
        GmdlError::TruncatedTextureSet {
            count: 3,
            available: 24,
        },
        "truncated texture set",
    );
}

#[test]
fn an_undocumented_shader_data_id_is_refused_by_name() {
    // 0x2FF is not in the table. Guessing a length here would desynchronise every
    // later section, which is strictly worse than stopping.
    let data = Builder::minimal()
        .material_info(vec![vec![MaterialEntry::Shader(0x2FF)]])
        .build();
    let error = parse(&data).expect_err("0x2FF has no documented length");
    assert_eq!(error, GmdlError::UndocumentedShaderDataId { id: 0x2FF });
    expect(error, "undocumented shader-data id 0x2FF");
    // Ids absent from this build's table fail the same way, and 0x20D is not one
    // of them: it is decoded.
    for id in [0x207u32, 0x214, 0x218, 0x257] {
        let data = Builder::minimal()
            .material_info(vec![vec![MaterialEntry::Shader(id)]])
            .build();
        assert_eq!(
            parse(&data),
            Err(GmdlError::UndocumentedShaderDataId { id })
        );
    }
    assert_eq!(spore_gmdl::shader_data_size(0x20D), None);
    assert_eq!(spore_gmdl::shader_data_size(0x210), Some(20));
}

#[test]
fn a_truncated_shader_data_payload_is_refused() {
    // Shader 0x206 needs 256 bytes; only 16 are written.
    let data = Builder::minimal()
        .material_info(vec![vec![MaterialEntry::ShortShader {
            id: 0x206,
            payload_len: 16,
        }]])
        .build();
    match parse(&data) {
        Err(GmdlError::TruncatedShaderData { id, size }) => {
            assert_eq!(id, 0x206);
            assert_eq!(size, 256);
        }
        other => panic!("{other:?}"),
    }
}

#[test]
fn a_record_without_room_for_the_trailer_is_refused() {
    // materialInfoCount = 0 and nothing after it: the walk needs 4 bytes for the
    // trailer's first word.
    let empty = Builder::minimal().trailer(Trailer::None).build();
    match parse(&empty) {
        Err(GmdlError::TruncatedTrailer { available }) => assert_eq!(available, 0),
        other => panic!("{other:?}"),
    }
    // Three filler bytes are one short as well.
    let short = Builder::minimal().trailer(Trailer::Filler(3)).build();
    assert_eq!(
        parse(&short),
        Err(GmdlError::TruncatedTrailer { available: 3 })
    );
    // Four is enough for the walk to read a bone-range count - and that count is
    // 0xA5A5A5A5, which claims 34 billion bone ranges the record does not have.
    // The parse still succeeds, because the tail is best-effort.
    //
    // Note the interaction: `fully_walked()` is true, because every input byte
    // was consumed by a read, while `trailer.is_truncated()` is also true,
    // because the structure that last word described was incomplete. The two
    // answer different questions and both are reported.
    let enough = Builder::minimal().trailer(Trailer::Filler(4)).build();
    let model = parse(&enough).expect("the tail is best-effort");
    assert!(model.fully_walked(), "all four filler bytes were read");
    assert_eq!(
        model.trailer.stopped_at(),
        Some(spore_gmdl::TrailerStage::BoneRanges)
    );
    assert!(
        model.bone_ranges.is_empty(),
        "the claimed array was never read"
    );
}

// ---------------------------------------------------------------- mesh extraction

#[test]
fn a_mesh_with_an_unsupported_primitive_type_is_refused() {
    for prim_type in [1u32, 2, 3, 5, 6, 7, 0] {
        let record = Builder::minimal()
            .index_buffers(vec![IndexBuffer::triangles(&[0, 1, 2]).prim(prim_type)])
            .build();
        let model = parse(&record).expect("the record is valid; the mesh topology is not");
        let error =
            spore_gmdl::mesh_from_gmdl(&model, 0).expect_err("only triangle lists are decoded");
        assert_eq!(error, GmdlError::UnsupportedTopology { prim_type });
    }
    expect(
        GmdlError::UnsupportedTopology { prim_type: 5 },
        "unsupported primitive type 5",
    );
    // Triangle strips and fans have names, and are still refused.
    assert_eq!(
        spore_gmdl::Topology::from_prim_code(5),
        Some(spore_gmdl::Topology::TriangleStrip)
    );
}

#[test]
fn a_mesh_with_32_bit_indices_is_refused() {
    let record = Builder::minimal()
        .index_buffers(vec![IndexBuffer::triangles32(&[0, 1, 2])])
        .build();
    let model = parse(&record).expect("the record parses; the mesh width does not");
    let error = spore_gmdl::mesh_from_gmdl(&model, 0).expect_err("32-bit indices are not decoded");
    assert_eq!(error, GmdlError::UnsupportedIndexWidth { index_bits: 32 });
    expect(error, "unsupported index width 32");
}

#[test]
fn a_mesh_on_a_non_zero_stream_is_refused() {
    let record = Builder::minimal()
        .descriptors(vec![vec![Element::new(0, 2, 0).stream(1)]])
        .build();
    let model = parse(&record).expect("record");
    assert_eq!(
        spore_gmdl::mesh_from_gmdl(&model, 0),
        Err(GmdlError::NonZeroStream { stream: 1 })
    );
}

#[test]
fn a_mesh_with_a_non_default_vertex_method_is_refused() {
    let record = Builder::minimal()
        .descriptors(vec![vec![Element::new(0, 2, 0).method(2)]])
        .build();
    let model = parse(&record).expect("record");
    assert_eq!(
        spore_gmdl::mesh_from_gmdl(&model, 0),
        Err(GmdlError::UnsupportedVertexMethod { method: 2 })
    );
}

#[test]
fn a_descriptor_without_a_position_element_is_refused() {
    let record = Builder::minimal()
        .descriptors(vec![vec![Element::new(0, 1, 5)]])
        .build();
    let model = parse(&record).expect("record");
    assert_eq!(
        spore_gmdl::mesh_from_gmdl(&model, 0),
        Err(GmdlError::MissingPositionElement { descriptor: 0 })
    );
}

#[test]
fn an_index_beyond_the_vertex_count_is_refused_not_clamped() {
    // Three vertices, an index of 3. Clamping would produce a plausible wrong
    // triangle; refusing is the point.
    let record = Builder::minimal()
        .index_buffers(vec![IndexBuffer::triangles(&[0, 1, 3])])
        .build();
    let model = parse(&record).expect("record");
    let error = spore_gmdl::mesh_from_gmdl(&model, 0).expect_err("vertex 3 does not exist");
    assert_eq!(
        error,
        GmdlError::IndexOutOfRange {
            slot: 2,
            index: 3,
            vertex_count: 3
        }
    );
    expect(error, "index 2 is 3");
}

#[test]
fn a_non_finite_position_is_refused() {
    let payload =
        common::positions_payload(&[[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, f32::NAN]]);
    let record = Builder::minimal()
        .descriptors(vec![vec![Element::new(0, 2, 0)]])
        .vertex_buffers(vec![VertexBufferSpec::new(0, 3, payload)])
        .build();
    let model = parse(&record).expect("record");
    let error = spore_gmdl::mesh_from_gmdl(&model, 0).expect_err("a NaN position is refused");
    match error {
        GmdlError::NonFinitePosition {
            vertex,
            component,
            value,
        } => {
            assert_eq!((vertex, component), (2, "z"));
            assert!(value.is_nan());
        }
        other => panic!("{other:?}"),
    }
}

#[test]
fn a_non_finite_texcoord_is_refused() {
    let positions = [[0.0f32, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, 0.0]];
    let uvs = [[0.0f32, 0.0], [f32::INFINITY, 0.5], [1.0, 1.0]];
    let payload = common::interleaved_vertices(&positions, &[], &uvs, 12, 20);
    let record = Builder::minimal()
        .descriptors(vec![vec![Element::new(0, 2, 0), Element::new(20, 1, 5)]])
        .vertex_buffers(vec![VertexBufferSpec::new(0, 3, payload)])
        .build();
    let model = parse(&record).expect("record");
    let error = spore_gmdl::mesh_from_gmdl(&model, 0).expect_err("an infinite texcoord is refused");
    match error {
        GmdlError::NonFiniteTexcoord {
            vertex,
            component,
            value,
        } => {
            assert_eq!((vertex, component), (1, "u"));
            assert!(value.is_infinite());
        }
        other => panic!("{other:?}"),
    }
}

#[test]
fn degenerate_counts_are_refused() {
    // Zero indices.
    let record = Builder::minimal()
        .index_buffers(vec![IndexBuffer::triangles(&[])])
        .build();
    let model = parse(&record).expect("record");
    assert_eq!(
        spore_gmdl::mesh_from_gmdl(&model, 0),
        Err(GmdlError::EmptyIndexBuffer)
    );

    // Zero vertices with three valid-looking indices.
    let record = Builder::minimal()
        .vertex_buffers(vec![VertexBufferSpec::new(0, 0, vec![0; 12])])
        .build();
    let model = parse(&record).expect("record");
    assert_eq!(
        spore_gmdl::mesh_from_gmdl(&model, 0),
        Err(GmdlError::EmptyVertexBuffer)
    );

    // Four indices in a triangle list.
    let record = Builder::minimal()
        .index_buffers(vec![IndexBuffer::triangles(&[0, 1, 2, 0])])
        .build();
    let model = parse(&record).expect("record");
    assert_eq!(
        spore_gmdl::mesh_from_gmdl(&model, 0),
        Err(GmdlError::TriangleListIndexCount { index_count: 4 })
    );
}

#[test]
fn a_declared_count_larger_than_the_payload_is_refused() {
    // Six indices declared, three supplied: the range check fires before any
    // index is read.
    let record = Builder::minimal()
        .index_buffers(vec![IndexBuffer::triangles(&[0, 1, 2]).declared_count(6)])
        .build();
    let model = parse(&record).expect("record");
    match spore_gmdl::mesh_from_gmdl(&model, 0) {
        Err(GmdlError::ShortIndexBuffer { have, index_count }) => {
            assert_eq!((have, index_count), (6, 6));
        }
        other => panic!("{other:?}"),
    }

    // Nine vertices declared, 36 bytes (three) of payload supplied.
    let record = Builder::minimal()
        .vertex_buffers(vec![VertexBufferSpec::new(0, 9, vec![0; 36])])
        .build();
    let model = parse(&record).expect("record");
    match spore_gmdl::mesh_from_gmdl(&model, 0) {
        Err(GmdlError::ShortVertexBuffer {
            have,
            vertex_count,
            stride,
        }) => {
            assert_eq!((have, vertex_count, stride), (36, 9, 12));
        }
        other => panic!("{other:?}"),
    }
}

// ---------------------------------------------------------------- helper guards

#[test]
fn the_byte_patching_helpers_the_tests_rely_on_still_find_words() {
    // If these helpers silently stopped matching, every patching test above would
    // start failing for the wrong reason (or, worse, keep passing on a record it no
    // longer modifies). Guarding them here means a helper regression is reported
    // as a helper regression.
    let mut data = Builder::minimal().build();
    let offset = find_u32(&data, 0x1234_5678).expect("the material id is present");
    assert!(patch_first_u32(&mut data, 0x1234_5678, 0xDEAD_BEEF));
    assert_eq!(u32_at(&data, offset), Some(0xDEAD_BEEF));
    assert!(
        !patch_first_u32(&mut data, 0x1234_5678, 0),
        "a patched-away needle is not found twice"
    );
    let zero_words_before = data
        .windows(4)
        .filter(|window| *window == [0u8; 4].as_slice())
        .count();
    assert_eq!(common::patch_all_u32(&mut data, 0, 7), zero_words_before);
    assert_eq!(
        data.windows(4)
            .filter(|window| *window == [0u8; 4].as_slice())
            .count(),
        0
    );
    // The needle is in memory order, which for a little-endian word is the
    // reverse of the way it is written - the same discipline the format itself
    // punishes anyone who ignores.
    assert!(common::find_bytes(&data, &[0xEF, 0xBE, 0xAD, 0xDE]).is_some());
    assert_eq!(
        common::find_bytes(&data, &[]),
        None,
        "an empty needle is not a position"
    );
}

#[test]
fn an_odd_payload_length_is_handled_without_indexing() {
    // 5 index bytes: `bytes.len() / 2` in the C++ reference is 2, so 3 declared
    // indices fail the length check. The u64 form in this port says the same
    // thing.
    let record = Builder::minimal()
        .index_buffers(vec![IndexBuffer {
            prim_type: 4,
            index_count: 3,
            index_bits: 16,
            bytes: vec![1, 0, 0, 0, 9],
            size_word: None,
        }])
        .build();
    let model = parse(&record).expect("a 5-byte index payload is a record");
    match spore_gmdl::mesh_from_gmdl(&model, 0) {
        Err(GmdlError::ShortIndexBuffer { have, index_count }) => {
            assert_eq!((have, index_count), (5, 3));
        }
        other => panic!("{other:?}"),
    }
}
