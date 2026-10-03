//! Converting decoded Spore meshes into Bevy meshes.
//!
//! This module is deliberately free of windowing, rendering and asset
//! lifetimes so it can be tested with no GPU. It does exactly three things:
//!
//! 1. lift a [`spore_gmdl::Mesh`] into plain vertex buffers,
//! 2. decide what to do about the normals, which is a *semantic* question and
//!    therefore stated rather than buried,
//! 3. pack those buffers into a [`Mesh`].
//!
//! # The normals problem, stated honestly
//!
//! GMDL vertex buffers in the records decoded so far carry normals as
//! `UBYTE4`, and the container stores them as raw bytes. The reference decoder
//! divides by 255 and hands back `[0,1]` triples. **That encoding is not
//! understood.** `docs/ASSET-PATH.md` grades it INFERRED and asks the open
//! question outright: "signed? scaled?" A raw unsigned byte cannot be a signed
//! normal, so feeding `/255` straight into a PBR shader produces a surface lit
//! as though every normal pointed into the positive octant.
//!
//! There are three honest options and this build takes the second by default:
//!
//! | Option | Fidelity | Result |
//! |---|---|---|
//! | Feed `/255` through | faithful to the reference | shading is wrong |
//! | **Recompute from the triangles** | a *stated derivation* | shading is right |
//! | Decode as biased signed (`2x-1`) | an **invention** | plausible, unproven |
//!
//! So [`NormalMode::Computed`] is the default and the raw bytes are still
//! carried on [`MeshBuffers::raw_normal_bytes`] -- nothing is discarded, and
//! nothing is claimed that was not measured. See
//! `spore_gmdl::claims::vertex_normal_encoding`.

use bevy::asset::RenderAssetUsages;
use bevy::mesh::{Indices, PrimitiveTopology};
use bevy::prelude::Mesh;
use bevy::render::mesh::VertexAttributeValues;

/// What to do with a mesh's normals.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum NormalMode {
    /// Recompute smooth normals from the triangle geometry.
    ///
    /// A derivation, not a recovery: the engine is computing what the original
    /// *presumably* intended rather than reading what it stored.
    #[default]
    Computed,
    /// Use the record's raw `UBYTE4` bytes divided by 255, as the C++ did.
    ///
    /// Faithful, and demonstrably wrong-looking, which is why it is not the
    /// default. Kept so the two can be compared.
    RawUnorm,
    /// Carry no normal attribute and let the material shade unlit.
    None,
}

/// Vertex buffers lifted out of a decoded Spore mesh.
#[derive(Debug, Clone, PartialEq)]
pub struct MeshBuffers {
    /// Vertex positions, `f32` triples.
    pub positions: Vec<[f32; 3]>,
    /// Texture coordinates, when the descriptor had a TEXCOORD element.
    pub uvs: Option<Vec<[f32; 2]>>,
    /// Indices, already widened to `u32` and range-checked by the decoder.
    pub indices: Vec<u32>,
    /// Topology as decoded.
    pub topology: Topology,
    /// The record's raw normal bytes, undecoded, when it had a NORMAL element.
    ///
    /// Four components wide to match the on-disk `UBYTE4` element; the fourth
    /// is the unused byte and is left at zero rather than invented.
    ///
    /// Retained so that understanding the encoding later costs nothing.
    pub raw_normal_bytes: Option<Vec<[u8; 4]>>,
}

/// The subset of topologies Bevy and Spore share.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Topology {
    /// Independent points.
    Points,
    /// Independent line segments.
    Lines,
    /// A connected line strip.
    LineStrip,
    /// Independent triangles -- the only topology observed in decoded records.
    TriangleList,
    /// A connected triangle strip.
    TriangleStrip,
    /// A triangle fan.
    TriangleFan,
}

impl Topology {
    /// The Bevy/wgpu topology this maps to.
    ///
    /// # A triangle fan has no native representation
    ///
    /// GMDL's `primType` 6 is a triangle fan, and neither wgpu nor Bevy has a
    /// fan topology: `PrimitiveTopology` offers exactly `PointList`,
    /// `LineList`, `LineStrip`, `TriangleList` and `TriangleStrip`. So a fan
    /// maps to `TriangleList` **and its index buffer must be expanded** by
    /// [`expand_fan`] -- returning `TriangleList` without doing so would draw
    /// every consecutive triple as an unrelated triangle, which looks like a
    /// geometry bug rather than the missing-topology situation it is.
    ///
    /// The expansion is exact and standard, not a reinterpretation: fan
    /// vertex 0 is fixed and each subsequent vertex closes a triangle.
    pub fn to_primitive(self) -> PrimitiveTopology {
        match self {
            Self::Points => PrimitiveTopology::PointList,
            Self::Lines => PrimitiveTopology::LineList,
            Self::LineStrip => PrimitiveTopology::LineStrip,
            Self::TriangleList => PrimitiveTopology::TriangleList,
            Self::TriangleStrip => PrimitiveTopology::TriangleStrip,
            Self::TriangleFan => PrimitiveTopology::TriangleList,
        }
    }

    /// Whether [`Self::to_primitive`] needs the index buffer rewritten first.
    pub const fn needs_index_expansion(self) -> bool {
        matches!(self, Self::TriangleFan)
    }
}

/// Expands a triangle-fan index buffer into a triangle list.
///
/// `[v0, v1, v2, v3]` becomes `[v0, v1, v2, v0, v2, v3]`: the first vertex is
/// fixed and every consecutive pair after it closes a triangle. A fan of `n`
/// indices is therefore always complete for `n >= 3`; when `n` is even there is
/// one trailing vertex with no partner, and it is dropped rather than paired
/// with anything, because a half triangle has no meaning.
pub fn expand_fan(indices: &[u32]) -> Vec<u32> {
    let Some((&first, rest)) = indices.split_first() else {
        return Vec::new();
    };
    let mut out = Vec::with_capacity(rest.len().saturating_sub(1).saturating_mul(3));
    for pair in rest.windows(2) {
        out.extend_from_slice(&[first, pair[0], pair[1]]);
    }
    out
}

impl From<spore_gmdl::Topology> for Topology {
    fn from(value: spore_gmdl::Topology) -> Self {
        match value {
            spore_gmdl::Topology::Points => Self::Points,
            spore_gmdl::Topology::Lines => Self::Lines,
            spore_gmdl::Topology::LineStrip => Self::LineStrip,
            spore_gmdl::Topology::TriangleList => Self::TriangleList,
            spore_gmdl::Topology::TriangleStrip => Self::TriangleStrip,
            spore_gmdl::Topology::TriangleFan => Self::TriangleFan,
        }
    }
}

/// Lifts a decoded mesh into plain buffers. No Bevy types, no GPU.
pub fn to_buffers(mesh: &spore_gmdl::Mesh) -> MeshBuffers {
    // The decoder already normalised UBYTE4 to f32 in [0,1] and multiplied by
    // 255 to recover the byte. That round trip is only exact for 0 and 255, so
    // the raw bytes are recovered by rounding rather than claimed to be the
    // original values. They are retained for a future decode, not for shading.
    let raw_normal_bytes = if mesh.normals.is_empty() {
        None
    } else {
        Some(
            mesh.normals
                .iter()
                .map(|n| {
                    [
                        (n[0] * 255.0).round().clamp(0.0, 255.0) as u8,
                        (n[1] * 255.0).round().clamp(0.0, 255.0) as u8,
                        (n[2] * 255.0).round().clamp(0.0, 255.0) as u8,
                        0,
                    ]
                })
                .collect(),
        )
    };
    MeshBuffers {
        positions: mesh.positions.clone(),
        uvs: if mesh.uvs.is_empty() {
            None
        } else {
            Some(mesh.uvs.clone())
        },
        // A fan has no wgpu topology, so its indices are rewritten here rather
        // than in `to_bevy_mesh`: `MeshBuffers` is the engine-neutral form, and
        // an engine-neutral form that still needs a caller-side fixup is a
        // buffer that some future caller will forget to fix up.
        indices: match Topology::from(mesh.topology) {
            Topology::TriangleFan => expand_fan(&mesh.indices),
            _ => mesh.indices.clone(),
        },
        topology: mesh.topology.into(),
        raw_normal_bytes,
    }
}

/// Packs buffers into a Bevy mesh.
///
/// `compute_normals` is applied by the caller through [`with_normals`] so the
/// choice stays explicit at the call site rather than implied by this function.
pub fn to_bevy_mesh(buffers: &MeshBuffers, mode: NormalMode) -> Mesh {
    let mut mesh = Mesh::new(
        buffers.topology.to_primitive(),
        RenderAssetUsages::default(),
    );
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, buffers.positions.clone());
    if let Some(uvs) = &buffers.uvs {
        mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uvs.clone());
    }
    if !buffers.indices.is_empty() {
        mesh.insert_indices(Indices::U32(buffers.indices.clone()));
    }
    apply_normals(&mut mesh, buffers, mode);
    mesh
}

fn apply_normals(mesh: &mut Mesh, buffers: &MeshBuffers, mode: NormalMode) {
    match mode {
        NormalMode::None => {}
        NormalMode::RawUnorm => {
            if !buffers.positions.is_empty() {
                // Reproduce the reference decoder exactly: N/255 in [0,1].
                let raw: Vec<[f32; 3]> = buffers
                    .raw_normal_bytes
                    .as_ref()
                    .map(|bytes| {
                        bytes
                            .iter()
                            .map(|b| {
                                [
                                    b[0] as f32 / 255.0,
                                    b[1] as f32 / 255.0,
                                    b[2] as f32 / 255.0,
                                ]
                            })
                            .collect()
                    })
                    .unwrap_or_else(|| vec![[0.0; 3]; buffers.positions.len()]);
                if raw.len() == buffers.positions.len() {
                    mesh.insert_attribute(Mesh::ATTRIBUTE_NORMAL, raw);
                }
            }
        }
        NormalMode::Computed => {
            if !buffers.positions.is_empty() {
                mesh.compute_normals();
            }
        }
    }
}

/// Ensures the mesh carries normals under `mode`, computing them if needed.
///
/// Separated from [`to_bevy_mesh`] so a caller that has already packed a mesh
/// can normalise it, and so a test can assert the attribute's presence without
/// constructing a whole mesh twice.
pub fn with_normals(mesh: Mesh, buffers: &MeshBuffers, mode: NormalMode) -> Mesh {
    let mut mesh = mesh;
    apply_normals(&mut mesh, buffers, mode);
    mesh
}

/// Reads back the position attribute, for tests and diagnostics.
pub fn positions_of(mesh: &Mesh) -> Option<Vec<[f32; 3]>> {
    match mesh.attribute(Mesh::ATTRIBUTE_POSITION) {
        Some(VertexAttributeValues::Float32x3(values)) => Some(values.clone()),
        _ => None,
    }
}

/// Reads back the normal attribute, for tests and diagnostics.
pub fn normals_of(mesh: &Mesh) -> Option<Vec<[f32; 3]>> {
    match mesh.attribute(Mesh::ATTRIBUTE_NORMAL) {
        Some(VertexAttributeValues::Float32x3(values)) => Some(values.clone()),
        _ => None,
    }
}

/// Reads back the UV attribute, for tests and diagnostics.
pub fn uvs_of(mesh: &Mesh) -> Option<Vec<[f32; 2]>> {
    match mesh.attribute(Mesh::ATTRIBUTE_UV_0) {
        Some(VertexAttributeValues::Float32x2(values)) => Some(values.clone()),
        _ => None,
    }
}

/// The index buffer as `u32`, for tests and diagnostics.
pub fn indices_of(mesh: &Mesh) -> Option<Vec<u32>> {
    mesh.indices().map(|i| match i {
        Indices::U16(v) => v.iter().map(|x| *x as u32).collect(),
        Indices::U32(v) => v.clone(),
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use spore_gmdl::Mesh as SporeMesh;

    fn triangle() -> SporeMesh {
        SporeMesh {
            positions: vec![[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.0, 1.0, 0.0]],
            normals: vec![[1.0, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 0.0, 0.0]],
            uvs: vec![[0.0, 0.0], [1.0, 0.0], [0.0, 1.0]],
            indices: vec![0, 1, 2],
            topology: spore_gmdl::Topology::TriangleList,
            bounds_min: [0.0, 0.0, 0.0],
            bounds_max: [1.0, 1.0, 0.0],
            radius: 1.0,
        }
    }

    #[test]
    fn buffers_carry_positions_uvs_indices_and_the_raw_normal_bytes() {
        let buffers = to_buffers(&triangle());
        assert_eq!(buffers.positions.len(), 3);
        assert_eq!(buffers.uvs.as_ref().unwrap().len(), 3);
        assert_eq!(buffers.indices, vec![0, 1, 2]);
        assert_eq!(buffers.topology, Topology::TriangleList);
        // The record's normals came in as 1.0; the byte recovery must land on
        // 255, not on some intermediate value from the round trip.
        assert_eq!(
            buffers.raw_normal_bytes.as_ref().unwrap()[0],
            [255, 0, 0, 0]
        );
    }

    #[test]
    fn computed_normals_are_produced_and_unit_length() {
        let buffers = to_buffers(&triangle());
        let mesh = to_bevy_mesh(&buffers, NormalMode::Computed);
        let normals = normals_of(&mesh).expect("computed mode must attach normals");
        assert_eq!(normals.len(), 3);
        for n in &normals {
            let length = (n[0] * n[0] + n[1] * n[1] + n[2] * n[2]).sqrt();
            assert!(
                (length - 1.0).abs() < 1e-5,
                "normal {n:?} is not unit length"
            );
        }
    }

    #[test]
    fn raw_unorm_reproduces_the_reference_decode_and_is_not_the_default() {
        let buffers = to_buffers(&triangle());
        assert_eq!(
            NormalMode::default(),
            NormalMode::Computed,
            "the faithful-but-wrong mode must not be the default"
        );
        let mesh = to_bevy_mesh(&buffers, NormalMode::RawUnorm);
        let normals = normals_of(&mesh).unwrap();
        assert_eq!(normals[0], [1.0, 0.0, 0.0]);
        // And it is visibly not a normal: every component is in [0,1].
        for n in &normals {
            for c in n {
                assert!(
                    (0.0..=1.0).contains(c),
                    "raw unorm decode produced {c} outside [0,1]"
                );
            }
        }
    }

    #[test]
    fn none_mode_attaches_no_normals() {
        let buffers = to_buffers(&triangle());
        let mesh = to_bevy_mesh(&buffers, NormalMode::None);
        assert!(normals_of(&mesh).is_none());
    }

    #[test]
    fn a_mesh_without_uvs_gets_no_uv_attribute() {
        let mut bare = triangle();
        bare.uvs.clear();
        let buffers = to_buffers(&bare);
        let mesh = to_bevy_mesh(&buffers, NormalMode::Computed);
        assert!(uvs_of(&mesh).is_none());
        assert!(positions_of(&mesh).is_some());
    }

    #[test]
    fn indices_survive_the_round_trip_as_u32() {
        let buffers = to_buffers(&triangle());
        let mesh = to_bevy_mesh(&buffers, NormalMode::None);
        assert_eq!(indices_of(&mesh).unwrap(), vec![0, 1, 2]);
    }

    #[test]
    fn every_topology_maps_to_the_primitive_it_can_actually_express() {
        let pairs = [
            (Topology::Points, PrimitiveTopology::PointList),
            (Topology::Lines, PrimitiveTopology::LineList),
            (Topology::LineStrip, PrimitiveTopology::LineStrip),
            (Topology::TriangleList, PrimitiveTopology::TriangleList),
            (Topology::TriangleStrip, PrimitiveTopology::TriangleStrip),
            // A fan becomes a LIST, which is only correct because the index
            // buffer is expanded alongside it.
            (Topology::TriangleFan, PrimitiveTopology::TriangleList),
        ];
        for (ours, theirs) in pairs {
            assert_eq!(ours.to_primitive(), theirs);
        }
    }

    #[test]
    fn only_the_fan_needs_its_indices_expanded() {
        assert!(Topology::TriangleFan.needs_index_expansion());
        for topology in [
            Topology::Points,
            Topology::Lines,
            Topology::LineStrip,
            Topology::TriangleList,
            Topology::TriangleStrip,
        ] {
            assert!(
                !topology.needs_index_expansion(),
                "{topology:?} must pass indices through"
            );
        }
    }

    #[test]
    fn fan_expansion_fixes_the_first_vertex_and_is_exact() {
        // [v0 v1 v2 v3] -> two triangles sharing v0.
        assert_eq!(expand_fan(&[0, 1, 2, 3]), vec![0, 1, 2, 0, 2, 3]);
        // Three indices is already exactly one triangle.
        assert_eq!(expand_fan(&[7, 8, 9]), vec![7, 8, 9]);
        // Fewer than three indices cannot describe a fan at all.
        assert_eq!(expand_fan(&[0, 1]), Vec::<u32>::new());
        assert_eq!(expand_fan(&[]), Vec::<u32>::new());
        // Five indices is a complete three-triangle fan, not a partial one:
        // the odd trailing vertex is what makes the count odd, not a defect.
        assert_eq!(
            expand_fan(&[0, 1, 2, 3, 4]),
            vec![0, 1, 2, 0, 2, 3, 0, 3, 4]
        );
        assert_eq!(expand_fan(&[0, 1, 2, 3, 4, 5]).len(), 12);
        // Every expansion is a whole number of triangles, always.
        for n in 0..12usize {
            assert_eq!(
                expand_fan(&vec![0u32; n]).len() % 3,
                0,
                "n={n} produced a partial triangle"
            );
        }
    }

    #[test]
    fn a_fan_mesh_comes_out_the_other_side_as_a_valid_triangle_list() {
        let mut fan = triangle();
        fan.topology = spore_gmdl::Topology::TriangleFan;
        // A quad as a fan: 0,1,2,3 -> two triangles.
        fan.indices = vec![0, 1, 2, 3];
        fan.positions.push([1.0, 1.0, 0.0]);
        fan.normals.push([1.0, 0.0, 0.0]);
        fan.uvs.push([1.0, 1.0]);

        let buffers = to_buffers(&fan);
        assert_eq!(buffers.topology, Topology::TriangleFan);
        assert_eq!(
            buffers.indices,
            vec![0, 1, 2, 0, 2, 3],
            "the fan must be expanded, not passed through"
        );
        assert_eq!(buffers.indices.len() % 3, 0);

        let mesh = to_bevy_mesh(&buffers, NormalMode::Computed);
        assert_eq!(mesh.primitive_topology(), PrimitiveTopology::TriangleList);
        assert_eq!(indices_of(&mesh).unwrap().len(), 6);
    }
}
