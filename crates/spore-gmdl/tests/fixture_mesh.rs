//! Mesh extraction and bounds from the committed fixture.
//!
//! The fixture's vertex payload is deliberately not plausible geometry: it is
//! `byte[i] = (i * 7 + (i % 16) * 3) & 0xFF` (gen_fixtures.py), so every
//! 3-float "position" is an arbitrary bit pattern. They are all finite, which is
//! what the mesh path requires, and they span ~1e38, which is what makes the
//! `f32` radius overflow. Both facts are asserted below rather than smoothed
//! over.

mod common;

use common::mini_gmdl;
use spore_gmdl::{compute_mesh_bounds, mesh_from_gmdl, parse, vertex_stride, Mesh, Topology};

fn fixture_mesh() -> Mesh {
    let data = mini_gmdl();
    let model = parse(&data).expect("mini.gmdl must parse");
    mesh_from_gmdl(&model, 0).expect("mesh 0 must extract")
}

#[test]
fn the_fixture_descriptor_implies_a_sixteen_byte_stride() {
    let data = mini_gmdl();
    let model = parse(&data).expect("parse");
    let descriptor = model.descriptors.first().expect("descriptor 0");
    // FLOAT3 at 0 ends at 12; FLOAT2 at 8 ends at 16. The stride is the maximum
    // end offset, not the sum of sizes (20) and not the gap-free packing (12).
    assert_eq!(vertex_stride(descriptor), Ok(16));
    assert_eq!(model.vertex_stride_of(0), Some(Ok(16)));
    assert_eq!(model.vertex_stride_of(9), None, "no ninth vertex buffer");
    // 50 vertices * 16 bytes is exactly the payload the fixture stores.
    assert_eq!(50 * 16, 800);
}

#[test]
fn mesh_extraction_yields_the_expected_attribute_counts() {
    let mesh = fixture_mesh();
    assert_eq!(mesh.positions.len(), 50);
    assert_eq!(mesh.uvs.len(), 50);
    assert_eq!(mesh.indices.len(), 153);
    assert_eq!(
        mesh.normals.len(),
        0,
        "the fixture descriptor has no NORMAL element, so an empty vector means 'absent', not 'zero'"
    );
    assert_eq!(mesh.topology, Topology::TriangleList);
    assert!(!mesh.is_empty());
}

#[test]
fn every_index_is_inside_the_vertex_range() {
    let mesh = fixture_mesh();
    assert_eq!(mesh.indices.len(), 153);
    let low = mesh.indices.iter().copied().min().expect("non-empty");
    let high = mesh.indices.iter().copied().max().expect("non-empty");
    assert_eq!(low, 0);
    assert_eq!(high, 49);
    for (slot, index) in mesh.indices.iter().enumerate() {
        assert!(*index < 50, "index {slot} = {index} is outside 0..50");
    }
    // The generator's index formula is `(i * 17) % 50`; the first ten entries
    // are asserted directly so a mis-strided read cannot hide behind "all in
    // range".
    let first_ten: Vec<u32> = mesh.indices.iter().copied().take(10).collect();
    assert_eq!(first_ten, vec![0, 17, 34, 1, 18, 35, 2, 19, 36, 3]);
}

#[test]
fn vertex_zero_is_read_from_byte_zero_of_its_own_stride_slot() {
    let mesh = fixture_mesh();
    // Fixture vertex 0 occupies bytes 0..16; POSITION/FLOAT3 reads bytes 0..12,
    // which are byte[i] = 10i (mod 256) for i < 16: 0, 10, 20, 30, 40, 50, 60,
    // 70, 80, 90, 100, 110.
    //
    //   x = f32 from [0, 10, 20, 30]    -> bits 0x1E140A00
    //   y = f32 from [40, 50, 60, 70]   -> bits 0x463C3228  (12044.5390625)
    //   z = f32 from [80, 90, 100, 110] -> bits 0x6E645A50
    //
    // Bit patterns rather than decimals: the values are arbitrary denormal-ish
    // bit patterns, and a decimal round-trip in the test would hide a
    // single-ulp difference.
    let position = mesh.positions.first().copied().expect("vertex 0");
    assert_eq!(position[0].to_bits(), 0x1E14_0A00);
    assert_eq!(position[1].to_bits(), 0x463C_3228);
    assert_eq!(position[2].to_bits(), 0x6E64_5A50);
    // 12044.5390625 is exactly representable (0x463C3228); the shortest
    // spelling clippy accepts is 12_044.539, which is the same f32.
    assert_eq!(position[1], 12_044.539);

    // TEXCOORD/FLOAT2 at byte 8 reads bytes 8..16, which overlap the position's
    // z component: 80..90 and 100..110. The overlap is the fixture's doing, not
    // a decoder bug - the descriptor places the two elements 8 bytes apart while
    // FLOAT3 needs 12.
    let uv = mesh.uvs.first().copied().expect("uv 0");
    assert_eq!(uv[0].to_bits(), 0x6E64_5A50);
    assert_eq!(uv[1].to_bits(), 0x968C_8278);
    assert_eq!(
        uv[0], position[2],
        "the fixture's texcoord overlaps position.z"
    );
}

#[test]
fn computed_bounds_are_the_positions_min_max() {
    let mesh = fixture_mesh();
    // Computed independently from the fixture's vertex bytes with the formula
    // from gen_fixtures.py; see the independent script in this test's history.
    //   min = (-1.6277558584808392e38, -2.4023105399760697e33, -1.6277558584808392e38)
    //   max = ( 8.122099038746153e37,  1.1986100652672641e33,  8.122099038746153e37)
    assert_eq!(mesh.bounds_min[0].to_bits(), 0xFEF4_EAE0);
    assert_eq!(mesh.bounds_min[1].to_bits(), 0xF6EC_E2D8);
    assert_eq!(mesh.bounds_min[2].to_bits(), 0xFEF4_EAE0);
    assert_eq!(mesh.bounds_max[0].to_bits(), 0x7E74_6A60);
    assert_eq!(mesh.bounds_max[1].to_bits(), 0x766C_6258);
    assert_eq!(mesh.bounds_max[2].to_bits(), 0x7E74_6A60);

    // Re-derived from the decoded positions so the bounds cannot be a constant
    // copied out of the record: the record's own box is [1.5, -2.25, 0.125]..
    // [3.5, 0.75, 2.0], and the vertex box is nothing like it.
    let mut low = [f32::INFINITY; 3];
    let mut high = [f32::NEG_INFINITY; 3];
    for position in &mesh.positions {
        for axis in 0..3 {
            let value = position[axis];
            if value < low[axis] {
                low[axis] = value;
            }
            if value > high[axis] {
                high[axis] = value;
            }
        }
    }
    assert_eq!(mesh.bounds_min, low);
    assert_eq!(mesh.bounds_max, high);
}

#[test]
fn the_record_box_and_the_computed_box_are_different_claims() {
    let data = mini_gmdl();
    let model = parse(&data).expect("parse");
    let mesh = fixture_mesh();
    assert_ne!(
        model.bounds_min, mesh.bounds_min,
        "the record's box is not its vertices' box"
    );
    assert_ne!(model.radius, mesh.radius);
    // docs/ASSET-PATH.md grades the record box "VERIFIED" and the derived box
    // "SUPPORTED", and notes the file box is tighter than the LOD/morph range.
    // That gap is recorded as the `file_bounds_coverage` claim.
    assert_eq!(
        spore_gmdl::claim(spore_gmdl::claims::FILE_BOUNDS_COVERAGE).map(|fact| fact.level()),
        Some(spore_core::EvidenceLevel::Inferred)
    );
}

#[test]
fn the_f32_radius_overflows_to_infinity_on_this_fixture() {
    let mesh = fixture_mesh();
    // The reference computes sqrt(dx*dx + dy*dy + dz*dz) in f32. The fixture's
    // coordinates reach 1.6e38, and 1.2e38 squared is ~1.5e76, far past the f32
    // maximum of 3.4e38: every squared term overflows and the radius is +inf.
    //
    // Evaluated in f64 the same computation gives 1.2863269535470269e38 (f32
    // bits 0x7EC18B83). The port keeps the f32 path so it agrees with
    // src/assets/Mesh.cpp on every record, and this test records the difference
    // instead of hiding it.
    assert!(mesh.radius.is_infinite(), "radius {}", mesh.radius);
    assert!(mesh.radius.is_sign_positive());
    assert!(
        mesh.bounds_min[0].is_finite(),
        "the box itself does not overflow"
    );
    assert!(mesh.bounds_max[1].is_finite());
}

#[test]
fn compute_mesh_bounds_is_idempotent() {
    // Extraction already called it; calling it again must not move the box, or
    // the function is not a pure function of the positions.
    let mut mesh = fixture_mesh();
    let before = (mesh.bounds_min, mesh.bounds_max, mesh.radius);
    compute_mesh_bounds(&mut mesh);
    assert_eq!((mesh.bounds_min, mesh.bounds_max, mesh.radius), before);
}

#[test]
fn an_absent_mesh_index_is_an_error_not_an_empty_mesh() {
    let data = mini_gmdl();
    let model = parse(&data).expect("parse");
    assert_eq!(model.meshes.len(), 1);
    assert!(mesh_from_gmdl(&model, 1).is_err());
    assert!(mesh_from_gmdl(&model, u32::MAX).is_err());
}
