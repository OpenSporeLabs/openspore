//! The three code tables of the gmdl format: `D3DDECLTYPE`, `D3DDECLUSAGE` and
//! RenderWare `ShaderData` payload sizes, plus the `PRIM` primitive-type codes.
//!
//! Every constant here is transcribed, and the transcription is checked against
//! two independent implementations rather than against itself:
//!
//! * `src/assets/Gmdl.cpp` (`kDeclTypeSizes`, `kShaderSizes`) — the C++
//!   reference decoder this crate ports;
//! * `tools/spore/gmdl/gmdl.py` (`DECLTYPE_SIZE`, `DECLUSAGE`, `SHADER_DATA_SIZE`)
//!   — the stdlib-only Python oracle, an independent decode of the same layout.
//!
//! Where a table has a **gap**, the gap is data, not an oversight: an id this
//! build has never seen has no known payload length, and a length is the only
//! thing that makes an entry skippable. So `shader_data_size` returns `None`
//! for an undocumented id and the walk stops, rather than skipping a guess that
//! would desynchronise every later section.

use crate::error::GmdlError;
use crate::parse::GmdlVertexElement;

/// The `D3DDECLTYPE` a vertex element declares.
///
/// Codes 0..=16 are the documented Direct3D 9 declaration types, and the code
/// *is* the index into the size table — which is why [`DeclType::from_code`] and
/// [`DeclType::as_code`] are exact inverses.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum DeclType {
    /// Code 0: one 32-bit float.
    Float1,
    /// Code 1: two 32-bit floats.
    Float2,
    /// Code 2: three 32-bit floats. The `POSITION` encoding on this path.
    Float3,
    /// Code 3: four 32-bit floats.
    Float4,
    /// Code 4: four normalised 8-bit components (`D3DCOLOR`).
    D3dColor,
    /// Code 5: four unnormalised 8-bit components. The `NORMAL` encoding on
    /// this path — see [`crate::mesh_from_gmdl`] for why that is not a
    /// decoding but a reproduction.
    UByte4,
    /// Code 6: two 16-bit signed integers.
    Short2,
    /// Code 7: four 16-bit signed integers.
    Short4,
    /// Code 8: four normalised 8-bit components.
    UByte4N,
    /// Code 9: two normalised 16-bit signed integers.
    Short2N,
    /// Code 10: four normalised 16-bit signed integers.
    Short4N,
    /// Code 11: two normalised 16-bit unsigned integers.
    UShort2N,
    /// Code 12: four normalised 16-bit unsigned integers.
    UShort4N,
    /// Code 13: three packed unsigned normalised 10-bit integers in a word.
    UDec3,
    /// Code 14: three packed signed normalised 10-bit integers in a word.
    Dec3N,
    /// Code 15: two half-precision floats.
    Float16x2,
    /// Code 16: four half-precision floats.
    Float16x4,
}

impl DeclType {
    /// Every documented declaration type, indexed by its code.
    ///
    /// The array is the single place that states "codes 0..=16 are
    /// contiguous"; the tests use it to prove [`DeclType::from_code`] and
    /// [`DeclType::as_code`] agree with it.
    pub const ALL: [DeclType; 17] = [
        DeclType::Float1,
        DeclType::Float2,
        DeclType::Float3,
        DeclType::Float4,
        DeclType::D3dColor,
        DeclType::UByte4,
        DeclType::Short2,
        DeclType::Short4,
        DeclType::UByte4N,
        DeclType::Short2N,
        DeclType::Short4N,
        DeclType::UShort2N,
        DeclType::UShort4N,
        DeclType::UDec3,
        DeclType::Dec3N,
        DeclType::Float16x2,
        DeclType::Float16x4,
    ];

    /// The `declType` byte this variant came from.
    pub const fn as_code(self) -> u8 {
        match self {
            DeclType::Float1 => 0,
            DeclType::Float2 => 1,
            DeclType::Float3 => 2,
            DeclType::Float4 => 3,
            DeclType::D3dColor => 4,
            DeclType::UByte4 => 5,
            DeclType::Short2 => 6,
            DeclType::Short4 => 7,
            DeclType::UByte4N => 8,
            DeclType::Short2N => 9,
            DeclType::Short4N => 10,
            DeclType::UShort2N => 11,
            DeclType::UShort4N => 12,
            DeclType::UDec3 => 13,
            DeclType::Dec3N => 14,
            DeclType::Float16x2 => 15,
            DeclType::Float16x4 => 16,
        }
    }

    /// Decodes a `declType` byte, or `None` when the byte is not documented.
    ///
    /// `None` is a hard error everywhere it can appear, never a default width:
    /// the size of an unknown declaration type is exactly the thing this table
    /// exists to supply, and a wrong guess misaligns every vertex after the
    /// first.
    pub const fn from_code(code: u8) -> Option<Self> {
        Some(match code {
            0 => DeclType::Float1,
            1 => DeclType::Float2,
            2 => DeclType::Float3,
            3 => DeclType::Float4,
            4 => DeclType::D3dColor,
            5 => DeclType::UByte4,
            6 => DeclType::Short2,
            7 => DeclType::Short4,
            8 => DeclType::UByte4N,
            9 => DeclType::Short2N,
            10 => DeclType::Short4N,
            11 => DeclType::UShort2N,
            12 => DeclType::UShort4N,
            13 => DeclType::UDec3,
            14 => DeclType::Dec3N,
            15 => DeclType::Float16x2,
            16 => DeclType::Float16x4,
            _ => return None,
        })
    }

    /// The on-disk size of one element of this type, in bytes.
    ///
    /// Transcribed from `src/assets/Gmdl.cpp:kDeclTypeSizes`, which the Python
    /// oracle's `DECLTYPE_SIZE` reproduces value for value.
    pub const fn byte_size(self) -> u32 {
        match self {
            DeclType::Float1 => 4,
            DeclType::Float2 => 8,
            DeclType::Float3 => 12,
            DeclType::Float4 => 16,
            DeclType::D3dColor => 4,
            DeclType::UByte4 => 4,
            DeclType::Short2 => 4,
            DeclType::Short4 => 8,
            DeclType::UByte4N => 4,
            DeclType::Short2N => 4,
            DeclType::Short4N => 8,
            DeclType::UShort2N => 4,
            DeclType::UShort4N => 8,
            DeclType::UDec3 => 4,
            DeclType::Dec3N => 4,
            DeclType::Float16x2 => 4,
            DeclType::Float16x4 => 8,
        }
    }

    /// The canonical name used in every table and document of this repository.
    pub const fn as_str(self) -> &'static str {
        match self {
            DeclType::Float1 => "FLOAT1",
            DeclType::Float2 => "FLOAT2",
            DeclType::Float3 => "FLOAT3",
            DeclType::Float4 => "FLOAT4",
            DeclType::D3dColor => "D3DCOLOR",
            DeclType::UByte4 => "UBYTE4",
            DeclType::Short2 => "SHORT2",
            DeclType::Short4 => "SHORT4",
            DeclType::UByte4N => "UBYTE4N",
            DeclType::Short2N => "SHORT2N",
            DeclType::Short4N => "SHORT4N",
            DeclType::UShort2N => "USHORT2N",
            DeclType::UShort4N => "USHORT4N",
            DeclType::UDec3 => "UDEC3",
            DeclType::Dec3N => "DEC3N",
            DeclType::Float16x2 => "FLOAT16_2",
            DeclType::Float16x4 => "FLOAT16_4",
        }
    }
}

/// The `D3DDECLUSAGE` a vertex element declares: what the element *is*, as
/// opposed to [`DeclType`], which is how it is *stored*.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum DeclUsage {
    /// Code 0: vertex position.
    Position,
    /// Code 1: skinning weight.
    BlendWeight,
    /// Code 2: skinning bone index.
    BlendIndices,
    /// Code 3: vertex normal.
    Normal,
    /// Code 4: point size.
    PSize,
    /// Code 5: texture coordinate.
    TexCoord,
    /// Code 6: tangent.
    Tangent,
    /// Code 7: binormal.
    Binormal,
    /// Code 8: tessellation factor.
    TessFactor,
    /// Code 9: homogeneous position.
    PositionT,
    /// Code 10: vertex colour.
    Color,
    /// Code 11: fog blend factor.
    Fog,
    /// Code 12: depth.
    Depth,
    /// Code 13: displacement-map sample coordinate.
    Sample,
}

impl DeclUsage {
    /// Every documented usage, indexed by its code.
    pub const ALL: [DeclUsage; 14] = [
        DeclUsage::Position,
        DeclUsage::BlendWeight,
        DeclUsage::BlendIndices,
        DeclUsage::Normal,
        DeclUsage::PSize,
        DeclUsage::TexCoord,
        DeclUsage::Tangent,
        DeclUsage::Binormal,
        DeclUsage::TessFactor,
        DeclUsage::PositionT,
        DeclUsage::Color,
        DeclUsage::Fog,
        DeclUsage::Depth,
        DeclUsage::Sample,
    ];

    /// The `declUsage` byte this variant came from.
    pub const fn as_code(self) -> u8 {
        match self {
            DeclUsage::Position => 0,
            DeclUsage::BlendWeight => 1,
            DeclUsage::BlendIndices => 2,
            DeclUsage::Normal => 3,
            DeclUsage::PSize => 4,
            DeclUsage::TexCoord => 5,
            DeclUsage::Tangent => 6,
            DeclUsage::Binormal => 7,
            DeclUsage::TessFactor => 8,
            DeclUsage::PositionT => 9,
            DeclUsage::Color => 10,
            DeclUsage::Fog => 11,
            DeclUsage::Depth => 12,
            DeclUsage::Sample => 13,
        }
    }

    /// Decodes a `declUsage` byte, or `None` when it is not documented.
    ///
    /// An unrecognised usage is *not* fatal on the walk: an element this path
    /// does not consume is ignored, exactly as the C++ reference ignores
    /// `COLOR`, `MATID`, `TANGENT` and extra `TEXCOORD`s. Its size is still
    /// validated through [`vertex_stride`].
    pub const fn from_code(code: u8) -> Option<Self> {
        Some(match code {
            0 => DeclUsage::Position,
            1 => DeclUsage::BlendWeight,
            2 => DeclUsage::BlendIndices,
            3 => DeclUsage::Normal,
            4 => DeclUsage::PSize,
            5 => DeclUsage::TexCoord,
            6 => DeclUsage::Tangent,
            7 => DeclUsage::Binormal,
            8 => DeclUsage::TessFactor,
            9 => DeclUsage::PositionT,
            10 => DeclUsage::Color,
            11 => DeclUsage::Fog,
            12 => DeclUsage::Depth,
            13 => DeclUsage::Sample,
            _ => return None,
        })
    }

    /// The canonical name used in every table and document of this repository.
    pub const fn as_str(self) -> &'static str {
        match self {
            DeclUsage::Position => "POSITION",
            DeclUsage::BlendWeight => "BLENDWEIGHT",
            DeclUsage::BlendIndices => "BLENDINDICES",
            DeclUsage::Normal => "NORMAL",
            DeclUsage::PSize => "PSIZE",
            DeclUsage::TexCoord => "TEXCOORD",
            DeclUsage::Tangent => "TANGENT",
            DeclUsage::Binormal => "BINORMAL",
            DeclUsage::TessFactor => "TESSFACTOR",
            DeclUsage::PositionT => "POSITIONT",
            DeclUsage::Color => "COLOR",
            DeclUsage::Fog => "FOG",
            DeclUsage::Depth => "DEPTH",
            DeclUsage::Sample => "SAMPLE",
        }
    }
}

/// The RenderWare shader-data entry id whose payload is a **texture set**
/// rather than a skippable blob.
///
/// `0x20D` is decoded, not skipped, so it is deliberately absent from
/// [`SHADER_DATA_SIZES`]. The Python oracle also carries a
/// `SHADER_DATA_0x20D = 100` constant that is never read; copying that number
/// into the skip table would be worse than useless, because it would make a
/// texture set silently skippable and lose every texture reference in the
/// record.
pub const TEXTURE_SET_ID: u32 = 0x20D;

/// One entry of the RenderWare `ShaderData` size table: id plus on-disk size.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct ShaderDataSize {
    /// The `ShaderData` entry id as it appears in the material-info table.
    pub id: u32,
    /// On-disk payload length in bytes.
    pub size: u32,
}

/// The RenderWare `ShaderData` id to byte-size table, ascending by id.
///
/// Transcribed from `src/assets/Gmdl.cpp:kShaderSizes`; the Python oracle's
/// `SHADER_DATA_SIZE` holds the same 49 pairs. `0x20D` is intentionally absent
/// (see [`TEXTURE_SET_ID`]).
///
/// The gaps are real: ids such as `0x207`, `0x214`, `0x215` and `0x218` are
/// not in this build's table because no record decoded by this build used them.
pub const SHADER_DATA_SIZES: [ShaderDataSize; 49] = [
    ShaderDataSize { id: 0x201, size: 8 },
    ShaderDataSize {
        id: 0x202,
        size: 20,
    },
    ShaderDataSize { id: 0x203, size: 8 },
    ShaderDataSize {
        id: 0x204,
        size: 16,
    },
    ShaderDataSize {
        id: 0x205,
        size: 20,
    },
    ShaderDataSize {
        id: 0x206,
        size: 256,
    },
    ShaderDataSize { id: 0x208, size: 8 },
    ShaderDataSize { id: 0x209, size: 4 },
    ShaderDataSize {
        id: 0x20A,
        size: 64,
    },
    ShaderDataSize {
        id: 0x20B,
        size: 64,
    },
    ShaderDataSize {
        id: 0x20C,
        size: 16,
    },
    ShaderDataSize { id: 0x20E, size: 8 },
    ShaderDataSize { id: 0x20F, size: 8 },
    ShaderDataSize {
        id: 0x210,
        size: 20,
    },
    ShaderDataSize {
        id: 0x211,
        size: 20,
    },
    ShaderDataSize {
        id: 0x212,
        size: 32,
    },
    ShaderDataSize {
        id: 0x213,
        size: 48,
    },
    ShaderDataSize { id: 0x216, size: 1 },
    ShaderDataSize { id: 0x217, size: 1 },
    ShaderDataSize {
        id: 0x21C,
        size: 32,
    },
    ShaderDataSize {
        id: 0x21E,
        size: 16,
    },
    ShaderDataSize {
        id: 0x220,
        size: 16,
    },
    ShaderDataSize {
        id: 0x223,
        size: 164,
    },
    ShaderDataSize {
        id: 0x224,
        size: 152,
    },
    ShaderDataSize {
        id: 0x226,
        size: 16,
    },
    ShaderDataSize {
        id: 0x22D,
        size: 16,
    },
    ShaderDataSize {
        id: 0x22E,
        size: 16,
    },
    ShaderDataSize {
        id: 0x22F,
        size: 16428,
    },
    ShaderDataSize { id: 0x230, size: 4 },
    ShaderDataSize {
        id: 0x231,
        size: 12,
    },
    ShaderDataSize { id: 0x232, size: 1 },
    ShaderDataSize { id: 0x233, size: 4 },
    ShaderDataSize { id: 0x235, size: 4 },
    ShaderDataSize { id: 0x236, size: 4 },
    ShaderDataSize { id: 0x237, size: 1 },
    ShaderDataSize { id: 0x238, size: 1 },
    ShaderDataSize {
        id: 0x23B,
        size: 96,
    },
    ShaderDataSize {
        id: 0x23C,
        size: 48,
    },
    ShaderDataSize {
        id: 0x241,
        size: 64,
    },
    ShaderDataSize {
        id: 0x242,
        size: 64,
    },
    ShaderDataSize {
        id: 0x243,
        size: 144,
    },
    ShaderDataSize { id: 0x244, size: 1 },
    ShaderDataSize {
        id: 0x245,
        size: 12,
    },
    ShaderDataSize {
        id: 0x246,
        size: 20,
    },
    ShaderDataSize {
        id: 0x247,
        size: 16,
    },
    ShaderDataSize {
        id: 0x248,
        size: 16,
    },
    ShaderDataSize {
        id: 0x24A,
        size: 48,
    },
    ShaderDataSize {
        id: 0x255,
        size: 32,
    },
    ShaderDataSize {
        id: 0x256,
        size: 16,
    },
];

/// On-disk size of a RenderWare shader-data payload, or `None` for an id this
/// build does not document.
///
/// A 49-entry linear scan is used rather than a binary search: the table is
/// small enough to sit in cache, and `None` for an unknown id must stay the
/// cheap, obvious path because it is the error case the walk turns into a
/// refusal.
pub fn shader_data_size(id: u32) -> Option<u32> {
    SHADER_DATA_SIZES
        .iter()
        .find(|entry| entry.id == id)
        .map(|entry| entry.size)
}

/// The RenderWare `PRIM` primitive-type code for a triangle list.
///
/// This is the only code the mesh path accepts (see
/// [`crate::mesh_from_gmdl`]); the other five are named by
/// [`crate::Topology::from_prim_code`] so a record that uses one is reported by
/// name rather than as a bare number.
pub const PRIM_TRIANGLE_LIST: u32 = 4;

/// Interleaved vertex stride implied by one descriptor: the largest
/// `offset + size` over its elements.
///
/// The stride is *derived*, never stored: the record does not record it, and
/// deriving it is the only way to know where element *k* of vertex *v* starts.
/// An undocumented `declType` has no size and therefore no stride, so it is an
/// error rather than a zero — a zero stride would make every vertex alias
/// vertex 0 and produce a mesh that looks decodable and is not.
pub fn vertex_stride(desc: &[GmdlVertexElement]) -> Result<u32, GmdlError> {
    let mut stride: u32 = 0;
    for element in desc {
        let size = DeclType::from_code(element.decl_type)
            .map(DeclType::byte_size)
            .ok_or(GmdlError::UndocumentedDeclType {
                code: element.decl_type,
                descriptor_index: None,
            })?;
        let end = u32::from(element.offset)
            .checked_add(size)
            .ok_or(GmdlError::StrideOverflow {
                offset: element.offset,
                size,
            })?;
        if end > stride {
            stride = end;
        }
    }
    Ok(stride)
}

#[cfg(test)]
mod tests {
    use super::*;

    /// The expected `(code, size)` pairs, written out independently of the
    /// implementation from the D3D9 declaration types and from the two
    /// reference tables in this repository.
    const EXPECTED_DECL_TYPES: [(u8, u32, &str); 17] = [
        (0, 4, "FLOAT1"),
        (1, 8, "FLOAT2"),
        (2, 12, "FLOAT3"),
        (3, 16, "FLOAT4"),
        (4, 4, "D3DCOLOR"),
        (5, 4, "UBYTE4"),
        (6, 4, "SHORT2"),
        (7, 8, "SHORT4"),
        (8, 4, "UBYTE4N"),
        (9, 4, "SHORT2N"),
        (10, 8, "SHORT4N"),
        (11, 4, "USHORT2N"),
        (12, 8, "USHORT4N"),
        (13, 4, "UDEC3"),
        (14, 4, "DEC3N"),
        (15, 4, "FLOAT16_2"),
        (16, 8, "FLOAT16_4"),
    ];

    #[test]
    fn decl_type_codes_and_sizes_match_the_reference_tables() {
        for (code, size, name) in EXPECTED_DECL_TYPES {
            let decl = DeclType::from_code(code).unwrap_or_else(|| panic!("code {code} missing"));
            assert_eq!(decl.as_code(), code, "code round-trip");
            assert_eq!(decl.byte_size(), size, "code {code} ({name}) size");
            assert_eq!(decl.as_str(), name, "code {code} name");
        }
    }

    #[test]
    fn decl_type_table_is_complete_and_contiguous() {
        assert_eq!(DeclType::ALL.len(), EXPECTED_DECL_TYPES.len());
        for (index, decl) in DeclType::ALL.iter().enumerate() {
            assert_eq!(decl.as_code(), index as u8, "ALL must be indexed by code");
            assert_eq!(
                DeclType::from_code(index as u8),
                Some(*decl),
                "from_code must agree"
            );
        }
        // Code 17 is the first undocumented code; the test that feeds it to
        // `vertex_stride` lives in tests/parse_errors.rs.
        assert_eq!(DeclType::from_code(17), None);
        assert_eq!(DeclType::from_code(255), None);
    }

    #[test]
    fn decl_usage_codes_match_the_reference_tables() {
        const EXPECTED: [(u8, &str); 14] = [
            (0, "POSITION"),
            (1, "BLENDWEIGHT"),
            (2, "BLENDINDICES"),
            (3, "NORMAL"),
            (4, "PSIZE"),
            (5, "TEXCOORD"),
            (6, "TANGENT"),
            (7, "BINORMAL"),
            (8, "TESSFACTOR"),
            (9, "POSITIONT"),
            (10, "COLOR"),
            (11, "FOG"),
            (12, "DEPTH"),
            (13, "SAMPLE"),
        ];
        assert_eq!(DeclUsage::ALL.len(), EXPECTED.len());
        for (code, name) in EXPECTED {
            let usage =
                DeclUsage::from_code(code).unwrap_or_else(|| panic!("usage {code} missing"));
            assert_eq!(usage.as_code(), code);
            assert_eq!(usage.as_str(), name);
        }
        assert_eq!(DeclUsage::from_code(14), None);
    }

    /// The expected `ShaderData` pairs, transcribed a third time from
    /// `tools/spore/gmdl/gmdl.py:SHADER_DATA_SIZE` so a divergence between the
    /// table above and either reference implementation fails here rather than
    /// silently skipping a wrong number of bytes on a real record.
    const EXPECTED_SHADER_SIZES: [(u32, u32); 49] = [
        (0x201, 8),
        (0x202, 20),
        (0x203, 8),
        (0x204, 16),
        (0x205, 20),
        (0x206, 256),
        (0x208, 8),
        (0x209, 4),
        (0x20A, 64),
        (0x20B, 64),
        (0x20C, 16),
        (0x20E, 8),
        (0x20F, 8),
        (0x210, 20),
        (0x211, 20),
        (0x212, 32),
        (0x213, 48),
        (0x216, 1),
        (0x217, 1),
        (0x21C, 32),
        (0x21E, 16),
        (0x220, 16),
        (0x223, 164),
        (0x224, 152),
        (0x226, 16),
        (0x22D, 16),
        (0x22E, 16),
        (0x22F, 16428),
        (0x230, 4),
        (0x231, 12),
        (0x232, 1),
        (0x233, 4),
        (0x235, 4),
        (0x236, 4),
        (0x237, 1),
        (0x238, 1),
        (0x23B, 96),
        (0x23C, 48),
        (0x241, 64),
        (0x242, 64),
        (0x243, 144),
        (0x244, 1),
        (0x245, 12),
        (0x246, 20),
        (0x247, 16),
        (0x248, 16),
        (0x24A, 48),
        (0x255, 32),
        (0x256, 16),
    ];

    #[test]
    fn shader_data_table_is_sorted_duplicate_free_and_complete() {
        assert_eq!(SHADER_DATA_SIZES.len(), EXPECTED_SHADER_SIZES.len());
        for pair in SHADER_DATA_SIZES.windows(2) {
            let (first, second) = (pair.first().copied(), pair.get(1).copied());
            let (Some(first), Some(second)) = (first, second) else {
                panic!("window of 2 yielded a short window");
            };
            assert!(
                first.id < second.id,
                "shader-data ids must be strictly ascending"
            );
            assert!(second.id > 0, "ids are 3-hex-digit RenderWare codes");
        }
        for (id, size) in EXPECTED_SHADER_SIZES {
            assert_eq!(shader_data_size(id), Some(size), "id 0x{id:03X} size");
        }
    }

    #[test]
    fn the_texture_set_id_is_absent_from_the_skip_table() {
        // The Python oracle declares `SHADER_DATA_0x20D = 100` but never reads
        // it. Copying that number here would make a texture set silently
        // skippable and lose every texture reference in the record, so the
        // decoder path must keep it non-skippable.
        assert_eq!(shader_data_size(TEXTURE_SET_ID), None);
        assert_eq!(TEXTURE_SET_ID, 0x20D);
        assert!(
            !SHADER_DATA_SIZES
                .iter()
                .any(|entry| entry.id == TEXTURE_SET_ID),
            "0x20D is decoded, not skipped"
        );
    }

    #[test]
    fn an_undocumented_shader_data_id_is_absent_rather_than_zero() {
        // Every id in the gap 0x207/0x207..0x20D and around the table's end has
        // no known length, so it must report absence. Zero would be a claim
        // that the entry has no payload, which is a different statement.
        for id in [
            0x000,
            0x200,
            0x207,
            0x214,
            0x215,
            0x218,
            0x219,
            0x257,
            0x2FF,
            u32::MAX,
        ] {
            assert_eq!(
                shader_data_size(id),
                None,
                "id 0x{id:03X} must be undocumented"
            );
        }
    }

    #[test]
    fn vertex_stride_is_the_largest_end_offset() {
        let element = |offset: u16, decl_type: u8| GmdlVertexElement {
            stream: 0,
            offset,
            decl_type,
            decl_method: 0,
            decl_usage: 0,
            usage_index: 0,
            type_code: 0,
        };
        // POSITION/FLOAT3 at 0 then TEXCOORD/FLOAT2 at 8 -> 16, the fixture's
        // stride.
        assert_eq!(vertex_stride(&[element(0, 2), element(8, 1)]), Ok(16));
        // Order does not matter: it is a maximum, not a running offset.
        assert_eq!(vertex_stride(&[element(8, 1), element(0, 2)]), Ok(16));
        // A gap is honoured, not closed up.
        assert_eq!(vertex_stride(&[element(0, 2), element(32, 1)]), Ok(40));
        // Overlap is honoured too: the stride is the max end, never a sum.
        assert_eq!(vertex_stride(&[element(0, 3), element(0, 3)]), Ok(16));
        // Empty -> zero, which callers must treat as an error.
        assert_eq!(vertex_stride(&[]), Ok(0));
    }

    #[test]
    fn vertex_stride_refuses_an_undocumented_decl_type() {
        let bad = GmdlVertexElement {
            stream: 0,
            offset: 0,
            decl_type: 17,
            decl_method: 0,
            decl_usage: 0,
            usage_index: 0,
            type_code: 0,
        };
        assert_eq!(
            vertex_stride(&[bad]),
            Err(GmdlError::UndocumentedDeclType {
                code: 17,
                descriptor_index: None
            })
        );
        // A documented element after the bad one does not rescue it: the
        // maximum is never reached, because the walk stops at the first hole.
        let good = GmdlVertexElement {
            decl_type: 2,
            ..bad
        };
        assert!(vertex_stride(&[bad, good]).is_err());
        assert_eq!(vertex_stride(&[good]), Ok(12));
    }
}
