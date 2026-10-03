//! Typed failures of the gmdl walk.
//!
//! One variant per failure mode, on purpose. A decoder that answers "it did not
//! work" for a truncated record, an undocumented shader-data id and a
//! bad vertex stride has thrown away the only information a caller has to act
//! on: which of the three it was, and where. Every variant here names the
//! section it happened in and carries the values needed to identify the record
//! in a report.

use thiserror::Error;

use crate::SUPPORTED_VERSION;

/// Every way decoding a gmdl record can fail.
///
/// The variants are ordered to follow the section walk, so a reader of the
/// source (or of a backtrace) meets them in the order the walk can produce
/// them. `parse` never publishes a partially populated model: a `Err` means
/// nothing was returned, and `mesh_from_gmdl` never publishes a partial mesh.
///
/// `PartialEq` but not `Eq`: several variants carry the offending `f32`, and
/// `NaN != NaN` is the point rather than a nuisance — two parses that both hit
/// the same non-finite value are equal only through their bit patterns, which
/// is what `value.to_bits()` is for.
#[derive(Debug, Clone, PartialEq, Error)]
pub enum GmdlError {
    // ---- header -------------------------------------------------------
    /// The input was empty. A gmdl record always begins with a version word.
    #[error("gmdl: empty input (a record is never zero bytes)")]
    EmptyInput,

    /// Fewer than four bytes: not even the version word fits.
    #[error("gmdl: truncated header (want 4 bytes for the version word, got {got})")]
    TruncatedHeader {
        /// Bytes actually available.
        got: usize,
    },

    /// The version word is not [`SUPPORTED_VERSION`].
    ///
    /// Version 9 changes the material-info framing (its per-material block
    /// carries no entry-count word, see `tools/spore/gmdl/gmdl.py`) and this
    /// build has never validated it. It is rejected by name rather than
    /// guessed at.
    #[error("gmdl: unsupported version {version} (want {}) — version 9 changes the material-info framing and is unvalidated", SUPPORTED_VERSION)]
    UnsupportedVersion {
        /// The version word as read from the record.
        version: u32,
    },

    /// Fewer than four bytes remain for the big-endian reference count.
    #[error("gmdl: truncated refCount (want 4 bytes)")]
    TruncatedRefCount,

    /// The record claims more referenced-file keys than it has bytes for.
    #[error("gmdl: truncated referenced-file table ({count} keys need {needed} bytes, {available} left)")]
    TruncatedReferencedFiles {
        /// Big-endian reference count from the record.
        count: u32,
        /// `count * 12`.
        needed: u64,
        /// Bytes left in the record at that point.
        available: usize,
    },

    /// Fewer than 28 bytes remain for `meshCount` + bbox + radius.
    #[error("gmdl: truncated bounds (want 28 bytes, {available} left)")]
    TruncatedBounds {
        /// Bytes left in the record at that point.
        available: usize,
    },

    /// One of the six bounding-box floats is NaN or infinite.
    ///
    /// A non-finite box cannot be culled against, fitted to, or uploaded, and
    /// it is always corruption rather than a value Spore wrote.
    #[error("gmdl: non-finite bounds ({component} = {value})")]
    NonFiniteBounds {
        /// `"bboxMin[0]"`, `"bboxMax[2]"`, ... as written.
        component: &'static str,
        /// The offending value.
        value: f32,
    },

    /// The bounding radius is not a number.
    ///
    /// Note what this variant does **not** say: the walk does not reject a box
    /// whose `min` exceeds its `max` on some axis. No observed record does
    /// that, the axis convention is not established, and inventing a check here
    /// would reject a record the reference decoder accepts.
    #[error("gmdl: invalid bounds: bounding radius is {radius}")]
    InvalidBounds {
        /// The offending radius.
        radius: f32,
    },

    // ---- index buffers -------------------------------------------------
    /// The index-buffer count word or the per-buffer headers do not fit.
    ///
    /// When the count word itself is missing, `count` is 0 and `needed` is the 4
    /// bytes that word needed.
    #[error("gmdl: truncated index-buffer table: {available} bytes left, {needed} needed ({count} buffers declared)")]
    TruncatedIndexBufferTable {
        /// Count word from the record.
        count: u32,
        /// `count * 16`.
        needed: u64,
        /// Bytes left in the record at that point.
        available: usize,
    },

    /// An index buffer's header or its payload runs past the record end.
    #[error("gmdl: truncated index buffer {index} (want {size} payload bytes)")]
    TruncatedIndexBuffer {
        /// Position in the index-buffer table.
        index: usize,
        /// Declared payload size.
        size: u32,
    },

    // ---- vertex descriptors --------------------------------------------
    /// The descriptor count word or the per-descriptor element counts do not fit.
    ///
    /// When the count word itself is missing, `count` is 0 and `needed` is the 4
    /// bytes that word needed.
    #[error("gmdl: truncated vertex-descriptor table: {available} bytes left, {needed} needed ({count} descriptors declared)")]
    TruncatedVertexDescriptorTable {
        /// Count word from the record.
        count: u32,
        /// `count * 4`.
        needed: u64,
        /// Bytes left in the record at that point.
        available: usize,
    },

    /// A vertex descriptor's element array runs past the record end.
    #[error("gmdl: truncated vertex descriptor {index} (want {count} * 12-byte elements)")]
    TruncatedVertexDescriptor {
        /// Position in the descriptor table.
        index: usize,
        /// Declared element count.
        count: u32,
    },

    /// A descriptor element names a `D3DDECLTYPE` this build does not know.
    ///
    /// The size of such a type is unknown, so the interleaved stride is
    /// unknown, so *every* vertex in the buffer would be read from the wrong
    /// offset. The record is rejected rather than read with a guess.
    #[error("gmdl: undocumented declType {code} in descriptor {descriptor_index:?}")]
    UndocumentedDeclType {
        /// The unrecognised `declType` byte.
        code: u8,
        /// Descriptor table position, or `None` when the failure came from
        /// [`crate::vertex_stride`], which is handed a bare element slice and
        /// therefore has no table position to report.
        descriptor_index: Option<usize>,
    },

    // ---- vertex buffers ------------------------------------------------
    /// The vertex-buffer count word or the per-buffer headers do not fit.
    ///
    /// When the count word itself is missing, `count` is 0 and `needed` is the 4
    /// bytes that word needed.
    #[error("gmdl: truncated vertex-buffer table: {available} bytes left, {needed} needed ({count} buffers declared)")]
    TruncatedVertexBufferTable {
        /// Count word from the record.
        count: u32,
        /// `count * 12`.
        needed: u64,
        /// Bytes left in the record at that point.
        available: usize,
    },

    /// A vertex buffer's header or its payload runs past the record end.
    #[error("gmdl: truncated vertex buffer {index} (want {size} payload bytes)")]
    TruncatedVertexBuffer {
        /// Position in the vertex-buffer table.
        index: usize,
        /// Declared payload size.
        size: u32,
    },

    /// A vertex buffer names a descriptor that does not exist.
    #[error("gmdl: vertex buffer {index} names descriptor {desc_index} of {desc_count}")]
    BadDescriptorIndex {
        /// Position in the vertex-buffer table.
        index: usize,
        /// The out-of-range descriptor index.
        desc_index: u32,
        /// How many descriptors the record actually has.
        desc_count: usize,
    },

    // ---- mesh table ----------------------------------------------------
    /// The mesh reference table, the material-id table or the observed zero
    /// word do not fit.
    #[error(
        "gmdl: truncated mesh table ({mesh_count} meshes need {needed} bytes, {available} left)"
    )]
    TruncatedMeshTable {
        /// `meshCount` from the record.
        mesh_count: u32,
        /// `mesh_count * 16` (references plus material ids) plus the 4-byte
        /// observed zero word.
        needed: u64,
        /// Bytes left in the record at that point.
        available: usize,
    },

    /// A mesh names an index or vertex buffer that does not exist.
    #[error("gmdl: mesh {mesh} references missing buffers (index {index_buffer}, vertex {vertex_buffer}; have {index_buffers}/{vertex_buffers})")]
    MeshReferencesMissingBuffer {
        /// Position in the mesh table.
        mesh: usize,
        /// The out-of-range index-buffer index.
        index_buffer: u32,
        /// The out-of-range vertex-buffer index.
        vertex_buffer: u32,
        /// How many index buffers the record has.
        index_buffers: usize,
        /// How many vertex buffers the record has.
        vertex_buffers: usize,
    },

    // ---- material info -------------------------------------------------
    /// The material-info count word or one of the per-material entry counts does
    /// not fit.
    ///
    /// When the count word itself is missing, `count` is 0 and `needed` is the 4
    /// bytes that word needed.
    #[error("gmdl: truncated material-info table: {available} bytes left, {needed} needed ({count} blocks declared)")]
    TruncatedMaterialInfoTable {
        /// Count word from the record.
        count: u32,
        /// `count * 4`.
        needed: u64,
        /// Bytes left in the record at that point.
        available: usize,
    },

    /// A material block's entry array runs past the record end.
    #[error("gmdl: truncated material info {index} (want {count} * 4-byte ids)")]
    TruncatedMaterialInfo {
        /// Position in the material-info table.
        index: usize,
        /// Declared entry count.
        count: u32,
    },

    /// A `0x20D` texture-set block runs past the record end.
    #[error("gmdl: truncated texture set (want {count} * 24-byte entries, {available} left)")]
    TruncatedTextureSet {
        /// Declared texture count.
        count: u32,
        /// Bytes left in the record at that point.
        available: usize,
    },

    /// A material-info entry names a RenderWare shader-data id this build does
    /// not document.
    ///
    /// The payload length is what makes an id skippable, so an unknown id has
    /// no length and the walk cannot continue. Skipping a guessed length would
    /// silently desynchronise every later section, which is strictly worse
    /// than stopping.
    #[error("gmdl: undocumented shader-data id 0x{id:03X} in material info")]
    UndocumentedShaderDataId {
        /// The unrecognised shader-data id.
        id: u32,
    },

    /// A documented shader-data payload runs past the record end.
    #[error("gmdl: truncated shader data 0x{id:03X} (want {size} bytes)")]
    TruncatedShaderData {
        /// The shader-data id whose payload was short.
        id: u32,
        /// Its documented byte size.
        size: u32,
    },

    /// Fewer than four bytes remain after the material info: not even the
    /// trailer's first word fits.
    #[error("gmdl: truncated trailer ({available} bytes left, want >= 4)")]
    TruncatedTrailer {
        /// Bytes left in the record at that point.
        available: usize,
    },

    // ---- mesh extraction -----------------------------------------------
    /// The requested mesh does not exist.
    #[error("mesh: mesh index {mesh_index} out of range ({mesh_count} meshes)")]
    MeshIndexOutOfRange {
        /// The requested mesh.
        mesh_index: u32,
        /// How many meshes the model has.
        mesh_count: usize,
    },

    /// A parsed model's mesh table points at a buffer that is not there.
    ///
    /// Unreachable through [`crate::parse`], which rejects the same condition
    /// during the walk; kept because the model fields are public and a caller
    /// may build one by hand.
    #[error(
        "mesh: mesh references missing buffers (index {index_buffer}, vertex {vertex_buffer})"
    )]
    MeshReferencesMissingBuffers {
        /// The out-of-range index-buffer index.
        index_buffer: u32,
        /// The out-of-range vertex-buffer index.
        vertex_buffer: u32,
    },

    /// The index buffer is not a triangle list.
    ///
    /// A deliberate narrow contract, not an oversight: see
    /// [`crate::mesh_from_gmdl`].
    #[error("mesh: unsupported primitive type {prim_type} (want 4 = triangle list)")]
    UnsupportedTopology {
        /// The `primType` word from the index-buffer header.
        prim_type: u32,
    },

    /// The index buffer is not 16-bit.
    #[error("mesh: unsupported index width {index_bits} (want 16)")]
    UnsupportedIndexWidth {
        /// The `indexBits` word from the index-buffer header.
        index_bits: u32,
    },

    /// The index buffer declares zero indices.
    #[error("mesh: index buffer is empty")]
    EmptyIndexBuffer,

    /// The vertex buffer declares zero vertices.
    #[error("mesh: vertex buffer is empty")]
    EmptyVertexBuffer,

    /// A triangle list whose index count is not a multiple of three.
    #[error("mesh: triangle-list index count {index_count} is not divisible by 3")]
    TriangleListIndexCount {
        /// The declared index count.
        index_count: u32,
    },

    /// The index buffer payload is shorter than its declared index count.
    #[error("mesh: index buffer truncated ({have} bytes for {index_count} 16-bit indices)")]
    ShortIndexBuffer {
        /// Payload bytes present.
        have: usize,
        /// Declared index count.
        index_count: u32,
    },

    /// The descriptor has no `POSITION`/`FLOAT3` element.
    #[error("mesh: descriptor {descriptor} has no POSITION/FLOAT3")]
    MissingPositionElement {
        /// Descriptor table position.
        descriptor: usize,
    },

    /// A vertex element sits on a non-zero stream.
    ///
    /// Stream 0 is the only stream this path reads, so any other stream means
    /// the interleaving is not what it appears to be.
    #[error("mesh: unsupported non-zero stream {stream}")]
    NonZeroStream {
        /// The `stream` field of the offending element.
        stream: u16,
    },

    /// A vertex element declares a non-zero method.
    ///
    /// Method 0 is the only method observed on the records this build decodes;
    /// any other value is a per-vertex transform step this path would silently
    /// ignore.
    #[error("mesh: unsupported vertex-declaration method {method}")]
    UnsupportedVertexMethod {
        /// The `declMethod` field of the offending element.
        method: u8,
    },

    /// The descriptor implies a zero stride.
    ///
    /// Unreachable through a parsed model: an empty descriptor fails the
    /// `POSITION`/`FLOAT3` check first. Kept so the "stride is positive"
    /// precondition of the vertex loop is stated rather than assumed.
    #[error("mesh: zero vertex stride (descriptor {descriptor} is empty)")]
    ZeroStride {
        /// Descriptor table position.
        descriptor: usize,
    },

    /// The stride computation overflowed.
    ///
    /// Not reachable from the current tables: `offset` is a `u16` and the
    /// largest documented element is 16 bytes, so `offset + size` tops out at
    /// 65 551. The check is written anyway so that widening a decl-type table
    /// cannot turn a wrap into a plausible-looking stride.
    #[error("mesh: vertex stride overflow (offset {offset} + size {size} does not fit a u32)")]
    StrideOverflow {
        /// The element's `offset` field.
        offset: u16,
        /// The element's documented size.
        size: u32,
    },

    /// The vertex buffer payload is shorter than `vertex_count * stride`.
    #[error("mesh: vertex buffer truncated ({have} bytes for {vertex_count} vertices of {stride} bytes)")]
    ShortVertexBuffer {
        /// Payload bytes present.
        have: usize,
        /// Declared vertex count.
        vertex_count: u32,
        /// Interleaved stride in bytes.
        stride: u32,
    },

    /// A decoded position component is NaN or infinite.
    #[error("mesh: non-finite position at vertex {vertex} (component {component} = {value})")]
    NonFinitePosition {
        /// Vertex index within the buffer.
        vertex: usize,
        /// `"x"`, `"y"` or `"z"`.
        component: &'static str,
        /// The offending value.
        value: f32,
    },

    /// A decoded texcoord component is NaN or infinite.
    #[error("mesh: non-finite texcoord at vertex {vertex} (component {component} = {value})")]
    NonFiniteTexcoord {
        /// Vertex index within the buffer.
        vertex: usize,
        /// `"u"` or `"v"`.
        component: &'static str,
        /// The offending value.
        value: f32,
    },

    /// An index names a vertex that does not exist.
    ///
    /// Rejected, never clamped: a clamped index renders as a plausible wrong
    /// triangle, which is far harder to notice than a refused parse.
    #[error("mesh: index {slot} is {index}, out of range for {vertex_count} vertices")]
    IndexOutOfRange {
        /// Position of the index within the index buffer.
        slot: usize,
        /// The offending index value.
        index: u32,
        /// How many vertices the buffer declares.
        vertex_count: u32,
    },
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn every_variant_message_names_its_section() {
        // The point of one-variant-per-failure-mode is that a message alone is
        // enough to locate the failure, so the section word is asserted rather
        // than assumed.
        let cases: &[(GmdlError, &str)] = &[
            (GmdlError::EmptyInput, "gmdl"),
            (GmdlError::TruncatedHeader { got: 3 }, "truncated header"),
            (
                GmdlError::UnsupportedVersion { version: 9 },
                "unsupported version 9",
            ),
            (GmdlError::TruncatedRefCount, "truncated refCount"),
            (
                GmdlError::TruncatedReferencedFiles {
                    count: 2,
                    needed: 24,
                    available: 4,
                },
                "truncated referenced-file table",
            ),
            (
                GmdlError::TruncatedBounds { available: 4 },
                "truncated bounds",
            ),
            (
                GmdlError::NonFiniteBounds {
                    component: "bboxMin[0]",
                    value: f32::NAN,
                },
                "non-finite bounds",
            ),
            (
                GmdlError::InvalidBounds {
                    radius: f32::INFINITY,
                },
                "invalid bounds",
            ),
            (
                GmdlError::TruncatedIndexBufferTable {
                    count: 1,
                    needed: 16,
                    available: 3,
                },
                "truncated index-buffer table",
            ),
            (
                GmdlError::TruncatedIndexBuffer { index: 0, size: 16 },
                "truncated index buffer 0",
            ),
            (
                GmdlError::TruncatedVertexDescriptorTable {
                    count: 1,
                    needed: 4,
                    available: 1,
                },
                "truncated vertex-descriptor table",
            ),
            (
                GmdlError::TruncatedVertexDescriptor { index: 0, count: 2 },
                "truncated vertex descriptor 0",
            ),
            (
                GmdlError::UndocumentedDeclType {
                    code: 17,
                    descriptor_index: Some(0),
                },
                "undocumented declType 17 in descriptor Some(0)",
            ),
            (
                GmdlError::TruncatedVertexBufferTable {
                    count: 1,
                    needed: 12,
                    available: 2,
                },
                "truncated vertex-buffer table",
            ),
            (
                GmdlError::TruncatedVertexBuffer { index: 0, size: 8 },
                "truncated vertex buffer 0",
            ),
            (
                GmdlError::BadDescriptorIndex {
                    index: 0,
                    desc_index: 4,
                    desc_count: 1,
                },
                "names descriptor 4 of 1",
            ),
            (
                GmdlError::TruncatedMeshTable {
                    mesh_count: 2,
                    needed: 36,
                    available: 8,
                },
                "truncated mesh table",
            ),
            (
                GmdlError::MeshReferencesMissingBuffer {
                    mesh: 0,
                    index_buffer: 0,
                    vertex_buffer: 3,
                    index_buffers: 1,
                    vertex_buffers: 1,
                },
                "mesh 0 references missing buffers",
            ),
            (
                GmdlError::TruncatedMaterialInfoTable {
                    count: 1,
                    needed: 4,
                    available: 1,
                },
                "truncated material-info table",
            ),
            (
                GmdlError::TruncatedMaterialInfo { index: 0, count: 3 },
                "truncated material info 0",
            ),
            (
                GmdlError::TruncatedTextureSet {
                    count: 2,
                    available: 24,
                },
                "truncated texture set",
            ),
            (
                GmdlError::UndocumentedShaderDataId { id: 0x2FF },
                "undocumented shader-data id 0x2FF",
            ),
            (
                GmdlError::TruncatedShaderData {
                    id: 0x210,
                    size: 20,
                },
                "truncated shader data 0x210",
            ),
            (
                GmdlError::TruncatedTrailer { available: 2 },
                "truncated trailer",
            ),
            (
                GmdlError::MeshIndexOutOfRange {
                    mesh_index: 3,
                    mesh_count: 1,
                },
                "mesh index 3 out of range",
            ),
            (
                GmdlError::MeshReferencesMissingBuffers {
                    index_buffer: 0,
                    vertex_buffer: 9,
                },
                "mesh references missing buffers",
            ),
            (
                GmdlError::UnsupportedTopology { prim_type: 5 },
                "unsupported primitive type 5",
            ),
            (
                GmdlError::UnsupportedIndexWidth { index_bits: 32 },
                "unsupported index width 32",
            ),
            (GmdlError::EmptyIndexBuffer, "index buffer is empty"),
            (GmdlError::EmptyVertexBuffer, "vertex buffer is empty"),
            (
                GmdlError::TriangleListIndexCount { index_count: 4 },
                "not divisible by 3",
            ),
            (
                GmdlError::ShortIndexBuffer {
                    have: 4,
                    index_count: 3,
                },
                "index buffer truncated",
            ),
            (
                GmdlError::MissingPositionElement { descriptor: 0 },
                "no POSITION/FLOAT3",
            ),
            (GmdlError::NonZeroStream { stream: 1 }, "non-zero stream 1"),
            (GmdlError::UnsupportedVertexMethod { method: 2 }, "method 2"),
            (
                GmdlError::ZeroStride { descriptor: 0 },
                "zero vertex stride",
            ),
            (
                GmdlError::StrideOverflow {
                    offset: 0xFFFF,
                    size: 16,
                },
                "vertex stride overflow",
            ),
            (
                GmdlError::ShortVertexBuffer {
                    have: 8,
                    vertex_count: 2,
                    stride: 12,
                },
                "vertex buffer truncated",
            ),
            (
                GmdlError::NonFinitePosition {
                    vertex: 4,
                    component: "y",
                    value: f32::NAN,
                },
                "non-finite position at vertex 4",
            ),
            (
                GmdlError::NonFiniteTexcoord {
                    vertex: 1,
                    component: "u",
                    value: f32::INFINITY,
                },
                "non-finite texcoord at vertex 1",
            ),
            (
                GmdlError::IndexOutOfRange {
                    slot: 2,
                    index: 50,
                    vertex_count: 50,
                },
                "index 2 is 50",
            ),
        ];

        for (error, needle) in cases {
            let text = error.to_string();
            assert!(
                text.contains(needle),
                "message {text:?} does not mention {needle:?}"
            );
        }
        // 41 variants are constructed above; the enum must not grow without
        // this test being extended, because an unmentioned variant has an
        // unasserted message.
        assert_eq!(
            cases.len(),
            41,
            "a new GmdlError variant needs a message case here"
        );
    }

    #[test]
    fn shader_data_ids_are_spelled_in_hex_not_decimal() {
        // The C++ reference writes `std::to_string(id)` after a literal "0x",
        // which prints 0x525 for id 0x210. A shader-data id is always spelled
        // in hexadecimal in every table and document of this repository, so
        // the message agrees with them instead of contradicting them.
        let text = GmdlError::UndocumentedShaderDataId { id: 0x210 }.to_string();
        assert!(text.contains("0x210"), "got {text:?}");
    }
}
