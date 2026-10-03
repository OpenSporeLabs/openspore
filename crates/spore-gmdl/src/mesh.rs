//! Mesh extraction: a decoded gmdl mesh as an engine-neutral, GPU-ready mesh.
//!
//! The output type is deliberately **not** a Bevy type. `spore-assets` owns the
//! adaptation to whatever renderer is in use; this crate knows about bytes,
//! layouts and bounds, and nothing about a GPU, a window or an engine.
//!
//! # This is a deliberately narrow contract
//!
//! [`mesh_from_gmdl`] accepts exactly one path:
//!
//! * primitive type 4 (triangle list) and 16-bit indices;
//! * stream 0 only;
//! * method 0 (the default) only;
//! * `POSITION`/`FLOAT3` required, `NORMAL`/`UBYTE4` and `TEXCOORD`/`FLOAT2`
//!   consumed when present, everything else ignored.
//!
//! Every other shape is a typed error rather than a best-effort decode. That is
//! a design decision, not an oversight. A mesh that "mostly" decodes is worse
//! than one that refuses: a mis-read stride, an unhandled primitive or a
//! dropped index buffer all render as plausible geometry, and plausible wrong
//! geometry is the hardest class of bug to notice downstream. What has been
//! observed in every record decoded so far stays inside this path (all
//! version-8 records use `primType` 4 and `u16` indices, per
//! `docs/CELLSTAGE-RECON.md` §2), and the day that stops being true the answer
//! is a new variant with its own evidence, not a silent widening.
//!
//! # The `UBYTE4` normal encoding is NOT understood
//!
//! The bytes of a `NORMAL`/`UBYTE4` element are copied out as `byte / 255.0`,
//! which reproduces the C++ reference and the Python oracle exactly. It is not a
//! decoding: whether Spore stores a signed normal, a biased normal, a scaled
//! normal or something else in those four bytes is **not known**, and
//! `docs/ASSET-PATH.md` grades the mapping `INFERRED` with the note "true normal
//! decode (signed? scaled?) unknown".
//!
//! So this is a reproduction, deliberately un-"fixed". Rewriting it as a
//! `value * 2 - 1` bias-corrected signed decode would produce nicer-looking
//! normals and would be an invention, not a port. A consumer that wants a real
//! normal direction must decide for itself what those bytes mean, on evidence
//! this crate does not have. See the `vertex_normal_encoding` claim in
//! [`crate::claims`].

use crate::error::GmdlError;
use crate::parse::{GmdlModel, GmdlVertexElement};
use crate::tables::{vertex_stride, DeclType, DeclUsage, PRIM_TRIANGLE_LIST};

/// `D3DDECLUSAGE_POSITION`.
const USAGE_POSITION: u8 = 0;
/// `D3DDECLUSAGE_NORMAL`.
const USAGE_NORMAL: u8 = 3;
/// `D3DDECLUSAGE_TEXCOORD`.
const USAGE_TEXCOORD: u8 = 5;

/// How a mesh's indices are to be assembled into primitives.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum Topology {
    /// `PRIM` 1: one point per index.
    Points,
    /// `PRIM` 2: one line per index pair.
    Lines,
    /// `PRIM` 3: a connected run of lines.
    LineStrip,
    /// `PRIM` 4: one triangle per index triple. The only topology
    /// [`mesh_from_gmdl`] produces.
    TriangleList,
    /// `PRIM` 5: a connected run of triangles.
    TriangleStrip,
    /// `PRIM` 6: triangles around a first vertex.
    TriangleFan,
}

impl Topology {
    /// Every `PRIM` code this build names, indexed by code - 1.
    pub const ALL: [Topology; 6] = [
        Topology::Points,
        Topology::Lines,
        Topology::LineStrip,
        Topology::TriangleList,
        Topology::TriangleStrip,
        Topology::TriangleFan,
    ];

    /// Decodes a RenderWare `PRIM` code, or `None` when the code is not one of
    /// the six documented ones.
    pub const fn from_prim_code(code: u32) -> Option<Self> {
        Some(match code {
            1 => Topology::Points,
            2 => Topology::Lines,
            3 => Topology::LineStrip,
            4 => Topology::TriangleList,
            5 => Topology::TriangleStrip,
            6 => Topology::TriangleFan,
            _ => return None,
        })
    }

    /// The `PRIM` code for this topology.
    pub const fn prim_code(self) -> u32 {
        match self {
            Topology::Points => 1,
            Topology::Lines => 2,
            Topology::LineStrip => 3,
            Topology::TriangleList => 4,
            Topology::TriangleStrip => 5,
            Topology::TriangleFan => 6,
        }
    }

    /// The canonical name used by every table in this repository.
    pub const fn as_str(self) -> &'static str {
        match self {
            Topology::Points => "POINTLIST",
            Topology::Lines => "LINELIST",
            Topology::LineStrip => "LINESTRIP",
            Topology::TriangleList => "TRIANGLELIST",
            Topology::TriangleStrip => "TRIANGLESTRIP",
            Topology::TriangleFan => "TRIANGLEFAN",
        }
    }
}

/// A GPU-ready mesh: parallel attribute arrays plus indices.
///
/// Attribute arrays are parallel and may be shorter than the vertex count needs:
/// a descriptor with no `NORMAL` element yields an empty [`Mesh::normals`],
/// which is "the record does not carry normals", not "all normals are zero". A
/// consumer decides the fallback (the C++ renderer defaults to `+Z`).
#[derive(Debug, Clone, PartialEq)]
pub struct Mesh {
    /// Decoded vertex positions.
    pub positions: Vec<[f32; 3]>,
    /// Per-vertex normals in `[0, 1]`, from `NORMAL`/`UBYTE4` bytes divided by
    /// 255. Empty when the descriptor has no such element. See the module docs:
    /// this is a reproduction, not a decoding.
    pub normals: Vec<[f32; 3]>,
    /// Per-vertex texture coordinates. Empty when the descriptor has no
    /// `TEXCOORD`/`FLOAT2` element.
    pub uvs: Vec<[f32; 2]>,
    /// Indices, widened from the record's 16-bit values and range-checked
    /// against the vertex count.
    pub indices: Vec<u32>,
    /// How to assemble `indices` into primitives.
    pub topology: Topology,
    /// Lower corner of the mesh's own bounding box.
    pub bounds_min: [f32; 3],
    /// Upper corner of the mesh's own bounding box.
    pub bounds_max: [f32; 3],
    /// Maximum distance from the box centre to any vertex.
    pub radius: f32,
}

impl Mesh {
    /// True when the mesh has no positions or no indices: nothing to draw.
    pub fn is_empty(&self) -> bool {
        self.positions.is_empty() || self.indices.is_empty()
    }
}

/// Extracts one mesh from a decoded model.
///
/// Bounds are computed as part of the extraction, so a returned mesh always has
/// consistent [`Mesh::bounds_min`], [`Mesh::bounds_max`] and [`Mesh::radius`].
/// See the module docs for the exact (narrow) set of accepted layouts.
pub fn mesh_from_gmdl(model: &GmdlModel, mesh_index: u32) -> Result<Mesh, GmdlError> {
    let mesh_count = model.meshes.len();
    let reference =
        *model
            .meshes
            .get(mesh_index as usize)
            .ok_or(GmdlError::MeshIndexOutOfRange {
                mesh_index,
                mesh_count,
            })?;
    let missing = || GmdlError::MeshReferencesMissingBuffers {
        index_buffer: reference.index_buffer,
        vertex_buffer: reference.vertex_buffer,
    };
    let index_buffer = model
        .index_buffers
        .get(reference.index_buffer as usize)
        .ok_or_else(missing)?;
    let vertex_buffer = model
        .vertex_buffers
        .get(reference.vertex_buffer as usize)
        .ok_or_else(missing)?;

    if index_buffer.prim_type != PRIM_TRIANGLE_LIST {
        return Err(GmdlError::UnsupportedTopology {
            prim_type: index_buffer.prim_type,
        });
    }
    if index_buffer.index_bits != 16 {
        return Err(GmdlError::UnsupportedIndexWidth {
            index_bits: index_buffer.index_bits,
        });
    }
    if index_buffer.index_count == 0 {
        return Err(GmdlError::EmptyIndexBuffer);
    }
    if vertex_buffer.vertex_count == 0 {
        return Err(GmdlError::EmptyVertexBuffer);
    }
    if index_buffer.index_count % 3 != 0 {
        return Err(GmdlError::TriangleListIndexCount {
            index_count: index_buffer.index_count,
        });
    }
    // `u64` arithmetic rather than `index_count * 2` in `usize`: the count is a
    // `u32` read from the record, so the product can exceed `usize` on a 32-bit
    // target. The C++ reference guards for that with `count > SIZE_MAX / 2`,
    // which compares a `u32` against `SIZE_MAX / 2` and is therefore
    // tautologically false there - clang's -Wtautological-constant-out-of-range
    // rejects it - so the reference had to drop the guard instead.
    let needed_index_bytes = u64::from(index_buffer.index_count) * 2;
    if needed_index_bytes > index_buffer.bytes.len() as u64 {
        return Err(GmdlError::ShortIndexBuffer {
            have: index_buffer.bytes.len(),
            index_count: index_buffer.index_count,
        });
    }

    let desc_index = vertex_buffer.desc_index as usize;
    let descriptor = model
        .descriptors
        .get(desc_index)
        .ok_or(GmdlError::BadDescriptorIndex {
            index: reference.vertex_buffer as usize,
            desc_index: vertex_buffer.desc_index,
            desc_count: model.descriptors.len(),
        })?;

    let mut position_element: Option<&GmdlVertexElement> = None;
    let mut normal_element: Option<&GmdlVertexElement> = None;
    let mut uv_element: Option<&GmdlVertexElement> = None;
    for element in descriptor {
        if element.stream != 0 {
            return Err(GmdlError::NonZeroStream {
                stream: element.stream,
            });
        }
        if element.decl_method != 0 {
            return Err(GmdlError::UnsupportedVertexMethod {
                method: element.decl_method,
            });
        }
        // First match wins for each role, exactly as in the C++ reference's
        // if/else-if chain: a second `POSITION` element with a different
        // declaration type falls through and is ignored rather than displacing
        // the first.
        if position_element.is_none()
            && element.decl_usage == USAGE_POSITION
            && element.decl_type == DeclType::Float3.as_code()
        {
            position_element = Some(element);
        } else if normal_element.is_none()
            && element.decl_usage == USAGE_NORMAL
            && element.decl_type == DeclType::UByte4.as_code()
        {
            normal_element = Some(element);
        } else if uv_element.is_none()
            && element.decl_usage == USAGE_TEXCOORD
            && element.decl_type == DeclType::Float2.as_code()
        {
            uv_element = Some(element);
        }
        // Any other element (COLOR, TANGENT, extra TEXCOORDs, ...) is not
        // consumed here and is ignored. Its size still counts towards the
        // stride below, where an undocumented declType fails.
    }
    let position_element = position_element.ok_or(GmdlError::MissingPositionElement {
        descriptor: desc_index,
    })?;

    let stride = vertex_stride(descriptor)?;
    if stride == 0 {
        return Err(GmdlError::ZeroStride {
            descriptor: desc_index,
        });
    }
    // `u64` again, for the same reason as the index arithmetic above.
    let needed_vertex_bytes = u64::from(vertex_buffer.vertex_count) * u64::from(stride);
    if needed_vertex_bytes > vertex_buffer.bytes.len() as u64 {
        return Err(GmdlError::ShortVertexBuffer {
            have: vertex_buffer.bytes.len(),
            vertex_count: vertex_buffer.vertex_count,
            stride,
        });
    }

    let vertex_count = vertex_buffer.vertex_count as usize;
    let short = || GmdlError::ShortVertexBuffer {
        have: vertex_buffer.bytes.len(),
        vertex_count: vertex_buffer.vertex_count,
        stride,
    };
    let mut positions = Vec::with_capacity(vertex_count);
    let mut normals = Vec::with_capacity(usize::from(normal_element.is_some()) * vertex_count);
    let mut uvs = Vec::with_capacity(usize::from(uv_element.is_some()) * vertex_count);
    for vertex in 0..vertex_count {
        let row_start = vertex * stride as usize;
        let row = vertex_buffer
            .bytes
            .get(row_start..row_start + stride as usize)
            .ok_or_else(short)?;

        let base = position_element.offset as usize;
        let position = [
            f32_at(row, base).ok_or_else(short)?,
            f32_at(row, base + 4).ok_or_else(short)?,
            f32_at(row, base + 8).ok_or_else(short)?,
        ];
        for (component, value) in position.iter().enumerate() {
            if !value.is_finite() {
                return Err(GmdlError::NonFinitePosition {
                    vertex,
                    component: axis_name(component),
                    value: *value,
                });
            }
        }
        positions.push(position);

        if let Some(element) = normal_element {
            // The `/255` reproduction; see the module docs before "fixing" it.
            let [x, y, z] = bytes_at(row, element.offset as usize).ok_or_else(short)?;
            normals.push([x as f32 / 255.0, y as f32 / 255.0, z as f32 / 255.0]);
        }
        if let Some(element) = uv_element {
            let base = element.offset as usize;
            let uv = [
                f32_at(row, base).ok_or_else(short)?,
                f32_at(row, base + 4).ok_or_else(short)?,
            ];
            for (component, value) in uv.iter().enumerate() {
                if !value.is_finite() {
                    return Err(GmdlError::NonFiniteTexcoord {
                        vertex,
                        component: if component == 0 { "u" } else { "v" },
                        value: *value,
                    });
                }
            }
            uvs.push(uv);
        }
    }

    let mut indices = Vec::with_capacity(index_buffer.index_count as usize);
    for slot in 0..index_buffer.index_count as usize {
        let index =
            u16_at(index_buffer.bytes.as_slice(), slot * 2).ok_or(GmdlError::ShortIndexBuffer {
                have: index_buffer.bytes.len(),
                index_count: index_buffer.index_count,
            })? as u32;
        // Range-checked, never clamped: a clamped index renders as a plausible
        // wrong triangle, which is far harder to notice than a refused mesh.
        if index >= vertex_buffer.vertex_count {
            return Err(GmdlError::IndexOutOfRange {
                slot,
                index,
                vertex_count: vertex_buffer.vertex_count,
            });
        }
        indices.push(index);
    }

    let mut mesh = Mesh {
        positions,
        normals,
        uvs,
        indices,
        topology: Topology::TriangleList,
        bounds_min: [0.0; 3],
        bounds_max: [0.0; 3],
        radius: 0.0,
    };
    compute_mesh_bounds(&mut mesh);
    Ok(mesh)
}

/// Recomputes [`Mesh::bounds_min`], [`Mesh::bounds_max`] and [`Mesh::radius`]
/// from the positions.
///
/// The radius is the greatest distance from the **bounding-box centre** to any
/// vertex - not the greatest distance from the origin, and not the box's
/// diagonal half-length. Those three differ, and the C++ reference, this port
/// and every derived test agree on the centre-distance definition, so it is
/// reproduced exactly - including in `f32`, which means a mesh with enormous
/// coordinates can overflow the squared terms and report an infinite radius.
/// `tests/fixture_mesh.rs` pins that behaviour instead of papering over it with
/// an `f64` intermediate the reference does not use.
///
/// An empty mesh gets an all-zero box and a zero radius: a zero box is the only
/// honest answer for "no vertices", and it is a different claim from "a
/// degenerate point at the origin".
pub fn compute_mesh_bounds(mesh: &mut Mesh) {
    let Some(first) = mesh.positions.first().copied() else {
        mesh.bounds_min = [0.0; 3];
        mesh.bounds_max = [0.0; 3];
        mesh.radius = 0.0;
        return;
    };
    let mut low = first;
    let mut high = first;
    for position in &mesh.positions {
        for component in 0..3 {
            let value = component_of(position, component);
            if value < component_of(&low, component) {
                set_component(&mut low, component, value);
            }
            if value > component_of(&high, component) {
                set_component(&mut high, component, value);
            }
        }
    }
    mesh.bounds_min = low;
    mesh.bounds_max = high;

    // Components are read through `component_of` rather than subscripted, so
    // there is no indexing anywhere in this crate outside tests.
    let center = [
        (component_of(&low, 0) + component_of(&high, 0)) * 0.5,
        (component_of(&low, 1) + component_of(&high, 1)) * 0.5,
        (component_of(&low, 2) + component_of(&high, 2)) * 0.5,
    ];
    let mut radius: f32 = 0.0;
    for position in &mesh.positions {
        let dx = component_of(position, 0) - component_of(&center, 0);
        let dy = component_of(position, 1) - component_of(&center, 1);
        let dz = component_of(position, 2) - component_of(&center, 2);
        let distance = (dx * dx + dy * dy + dz * dz).sqrt();
        if distance > radius {
            radius = distance;
        }
    }
    mesh.radius = radius;
}

/// Names an axis for an error message.
fn axis_name(component: usize) -> &'static str {
    match component {
        0 => "x",
        1 => "y",
        _ => "z",
    }
}

/// Borrows `len` bytes at `offset`, or `None`. Overflow-safe.
fn window(row: &[u8], offset: usize, len: usize) -> Option<&[u8]> {
    let end = offset.checked_add(len)?;
    row.get(offset..end)
}

/// Reads `len` bytes at `offset` as an array.
fn bytes_at<const N: usize>(row: &[u8], offset: usize) -> Option<[u8; N]> {
    window(row, offset, N)?.try_into().ok()
}

/// Reads a little-endian `f32` at `offset`.
fn f32_at(row: &[u8], offset: usize) -> Option<f32> {
    Some(f32::from_le_bytes(bytes_at(row, offset)?))
}

/// Reads a little-endian `u16` at `offset`.
fn u16_at(row: &[u8], offset: usize) -> Option<u16> {
    Some(u16::from_le_bytes(bytes_at(row, offset)?))
}

/// Reads one component of a 3-vector.
fn component_of(vector: &[f32; 3], component: usize) -> f32 {
    vector.get(component).copied().unwrap_or(0.0)
}

/// Writes one component of a 3-vector.
fn set_component(target: &mut [f32; 3], component: usize, value: f32) {
    if let Some(slot) = target.get_mut(component) {
        *slot = value;
    }
}

/// Compile-time proof that the byte constants this module matches on are the
/// ones the transcribed tables assign. If a `D3DDECLUSAGE` code ever moves, this
/// stops compiling instead of silently reinterpreting every record's vertices.
const _: () = {
    assert!(USAGE_POSITION == DeclUsage::Position.as_code());
    assert!(USAGE_NORMAL == DeclUsage::Normal.as_code());
    assert!(USAGE_TEXCOORD == DeclUsage::TexCoord.as_code());
    assert!(PRIM_TRIANGLE_LIST == Topology::TriangleList.prim_code());
    assert!(DeclType::Float3.byte_size() == 12);
    assert!(DeclType::UByte4.byte_size() == 4);
    assert!(DeclType::Float2.byte_size() == 8);
};

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn prim_codes_round_trip() {
        const EXPECTED: [(u32, &str); 6] = [
            (1, "POINTLIST"),
            (2, "LINELIST"),
            (3, "LINESTRIP"),
            (4, "TRIANGLELIST"),
            (5, "TRIANGLESTRIP"),
            (6, "TRIANGLEFAN"),
        ];
        assert_eq!(Topology::ALL.len(), EXPECTED.len());
        for (code, name) in EXPECTED {
            let topology =
                Topology::from_prim_code(code).unwrap_or_else(|| panic!("PRIM {code} missing"));
            assert_eq!(topology.prim_code(), code);
            assert_eq!(topology.as_str(), name);
        }
        for code in [0u32, 7, 8, 0xFFFF_FFFF] {
            assert_eq!(
                Topology::from_prim_code(code),
                None,
                "PRIM {code} must be unnamed"
            );
        }
    }

    #[test]
    fn an_empty_mesh_bounds_to_zero_rather_than_to_a_degenerate_point() {
        let mut mesh = Mesh {
            positions: Vec::new(),
            normals: Vec::new(),
            uvs: Vec::new(),
            indices: Vec::new(),
            topology: Topology::TriangleList,
            bounds_min: [9.0; 3],
            bounds_max: [9.0; 3],
            radius: 9.0,
        };
        compute_mesh_bounds(&mut mesh);
        assert_eq!(mesh.bounds_min, [0.0; 3]);
        assert_eq!(mesh.bounds_max, [0.0; 3]);
        assert_eq!(mesh.radius, 0.0);
        assert!(mesh.is_empty());
    }

    #[test]
    fn bounds_come_from_positions_and_radius_from_the_box_centre() {
        // A unit triangle in the z = 0 plane: box (0,0,0)..(1,1,0), centre
        // (0.5, 0.5, 0), so the farthest vertex is sqrt(0.5) away. The same
        // assertion src/assets/tests/assets_test.cpp makes, and the definition
        // src/assets/Mesh.cpp implements.
        let mut mesh = Mesh {
            positions: vec![[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [1.0, 1.0, 0.0]],
            normals: Vec::new(),
            uvs: Vec::new(),
            indices: vec![0, 1, 2],
            topology: Topology::TriangleList,
            bounds_min: [0.0; 3],
            bounds_max: [0.0; 3],
            radius: 0.0,
        };
        compute_mesh_bounds(&mut mesh);
        assert_eq!(mesh.bounds_min, [0.0, 0.0, 0.0]);
        assert_eq!(mesh.bounds_max, [1.0, 1.0, 0.0]);
        let half_diagonal = std::f32::consts::FRAC_1_SQRT_2;
        assert!(
            (mesh.radius - half_diagonal).abs() < 1e-6,
            "radius {}",
            mesh.radius
        );
        assert!(!mesh.is_empty());
    }

    #[test]
    fn a_single_vertex_has_a_zero_radius() {
        let mut mesh = Mesh {
            positions: vec![[3.0, -4.0, 5.0]],
            normals: Vec::new(),
            uvs: Vec::new(),
            indices: vec![0, 0, 0],
            topology: Topology::TriangleList,
            bounds_min: [0.0; 3],
            bounds_max: [0.0; 3],
            radius: 0.0,
        };
        compute_mesh_bounds(&mut mesh);
        assert_eq!(mesh.bounds_min, [3.0, -4.0, 5.0]);
        assert_eq!(mesh.bounds_max, [3.0, -4.0, 5.0]);
        assert_eq!(mesh.radius, 0.0);
    }

    #[test]
    fn enormous_coordinates_overflow_the_f32_radius_to_infinity() {
        // The reference computes the squared distance in `f32`, so a vertex at
        // ~1e38 makes every squared term overflow. Reproduced rather than
        // widened: switching to `f64` here would silently disagree with
        // src/assets/Mesh.cpp on every such record.
        let mut mesh = Mesh {
            positions: vec![[1.0e38, 0.0, 0.0], [-1.0e38, 0.0, 0.0]],
            normals: Vec::new(),
            uvs: Vec::new(),
            indices: vec![0, 1, 0],
            topology: Topology::TriangleList,
            bounds_min: [0.0; 3],
            bounds_max: [0.0; 3],
            radius: 0.0,
        };
        compute_mesh_bounds(&mut mesh);
        assert_eq!(mesh.bounds_min, [-1.0e38, 0.0, 0.0]);
        assert_eq!(mesh.bounds_max, [1.0e38, 0.0, 0.0]);
        assert!(
            mesh.radius.is_infinite(),
            "f32 squaring overflows, as in Mesh.cpp"
        );
    }
}
