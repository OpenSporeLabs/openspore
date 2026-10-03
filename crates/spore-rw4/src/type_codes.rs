//! The two **incompatible** RW4 section-type-code tables.
//!
//! # The two references disagree, and that disagreement is data
//!
//! | Source | Membership rule | Names |
//! |---|---|---|
//! | `src/assets/Rw4.cpp` `inKnownSet` | the C++ set | SporeModder-FX / SMFX names |
//! | `tools/spore/rw4/rw4.py` `TYPES` | the Python map | SMFX names, different ids |
//!
//! They are **not** two encodings of one table. Measured:
//!
//! * C++ set: 22 ids. Python map: 29 ids. Intersection: 9.
//! * 13 ids are C++-only (`0x20007`, `0x20009`, `0x70002`, `0xff0000`, ...).
//! * 20 ids are Python-only (`0x20001`, `0x40001`, `0x30001`, `0xc0001`, ...).
//! * Two ids carry the **same id with different names**: `0x70001` is
//!   `KeyframeAnim` in C++ and `SkinsInK` in Python; `0x80003` is
//!   `TriangleKDTreeProcedural` in C++ and `BBox` in Python.
//! * Sixteen names exist in both tables under **different ids** (`Mesh` is
//!   `0x20009` in C++ and `0x40001` in Python; `AnimationSkin` is `0x70003` in
//!   C++ and `0x30001` in Python; ...).
//!
//! Forcing them into agreement would fabricate a third table that describes
//! neither reference, so both are reproduced verbatim and the divergence is
//! pinned by tests. **Membership follows the C++ set** ([`known_type_code`]),
//! because that is the table the reference walker actually uses; the Python map
//! is exposed read-only as vocabulary ([`python_type_name`]).
//!
//! A third, smaller view exists in `docs/RENDERWARE-RESEARCH.md` §7.5, which
//! lists `0x20004`/`0x20005` (VertexDescription/VertexBuffer) — codes present
//! in the Python map but absent from the C++ set. That document is a research
//! note, not a parser, so it is not transcribed here.
//!
//! Spore also emits `0x7000c` and `0x7000f`, which appear in **neither**
//! table (591 sections each across the 1,131 real records). They are exactly
//! why an unknown type code is not a parse error.

/// True when `tc` is in the C++ `inKnownSet` table.
///
/// This is the membership rule the reference walker uses and the one
/// [`crate::Rw4::unknown_type_codes`] counts against. `0x7000c` / `0x7000f`
/// are **not** in it.
pub fn known_type_code(tc: u32) -> bool {
    matches!(
        tc,
        // 0x100xx — container-level sections
        0x10004 | 0x10005 | 0x10006 | 0x10007 | 0x10008 | 0x10030
        // 0x200xx — renderable resources
        | 0x20003 | 0x20007 | 0x20008 | 0x20009 | 0x2000b | 0x2001a | 0x200af
        // 0x700xx — animation
        | 0x70001 | 0x70002 | 0x70003 | 0x7000b
        // 0x800xx — spatial acceleration
        | 0x80003 | 0x80005
        // 0xff00xx — blend shapes
        | 0xff0000 | 0xff0001 | 0xff0002
    )
}

/// The C++ set's name for `tc`, or `None`.
///
/// `None` covers **two** distinct situations that must not be conflated:
/// * `tc` is not in the C++ set at all — test with [`known_type_code`];
/// * `tc` **is** in the set but has no documented name: `0x2000b` and
///   `0x7000b` are recorded as "Spore-specific, unmapped" by the C++ comment.
///   No name is invented for them here.
pub fn cpp_type_name(tc: u32) -> Option<&'static str> {
    match tc {
        0x10004 => Some("SectionManifest"),
        0x10005 => Some("SectionTypes"),
        0x10006 => Some("SectionExternalArenas"),
        0x10007 => Some("SectionSubReferences"),
        0x10008 => Some("SectionAtoms"),
        0x10030 => Some("BaseResource"),
        0x20003 => Some("Raster"),
        0x20007 => Some("IndexBuffer"),
        0x20008 => Some("TextureOverride"),
        0x20009 => Some("Mesh"),
        // 0x2000b: in the C++ set, deliberately unnamed (see module docs).
        0x2001a => Some("MeshCompiledStateLink"),
        0x200af => Some("BlendShapeBuffer"),
        0x70001 => Some("KeyframeAnim"),
        0x70002 => Some("Skeleton"),
        0x70003 => Some("AnimationSkin"),
        // 0x7000b: in the C++ set, deliberately unnamed (see module docs).
        0x80003 => Some("TriangleKDTreeProcedural"),
        0x80005 => Some("BBox"),
        0xff0000 => Some("MorphHandle"),
        0xff0001 => Some("Animations"),
        0xff0002 => Some("BlendShape"),
        _ => None,
    }
}

/// The Python oracle's name for `tc`, or `None` when `tc` is not a key of
/// `rw4.py::TYPES`.
///
/// **This map does not agree with [`cpp_type_name`]** — see the module docs for
/// the measurement. Three of its keys carry the literal placeholder `"?"`,
/// because the oracle never resolved them; that is reproduced verbatim rather
/// than replaced with a guess, so a caller can tell "the oracle has an entry
/// but no name for it" apart from "the oracle has no entry".
///
/// Use this as *vocabulary* when reading oracle output. Do not use it to decide
/// membership — that is [`known_type_code`]'s job.
pub fn python_type_name(tc: u32) -> Option<&'static str> {
    match tc {
        0x10010 => Some("?"),
        0x10004 => Some("SectionManifest"),
        0x10005 => Some("SectionTypes"),
        0x10006 => Some("SectionExternalArenas"),
        0x10007 => Some("SectionSubReferences"),
        0x10008 => Some("SectionAtoms"),
        0x10030 => Some("BaseResource"),
        0x10031 => Some("?"),
        0x10032 => Some("?"),
        0x20001 => Some("VertexDescription"),
        0x20002 => Some("VertexBuffer"),
        0x20003 => Some("Raster"),
        0x20004 => Some("IndexBuffer"),
        0x20005 => Some("SkinMatrixBuffer"),
        0x30001 => Some("AnimationSkin"),
        0x40001 => Some("Mesh"),
        0x50001 => Some("MeshCompiledStateLink"),
        0x60001 => Some("CompiledState"),
        0x70001 => Some("SkinsInK"),
        0x80001 => Some("SkeletonsInK"),
        0x80002 => Some("Skeleton"),
        0x80003 => Some("BBox"),
        0x90001 => Some("MorphHandle"),
        0x90002 => Some("TriangleKDTreeProcedural"),
        0xA0001 => Some("Animations"),
        0xA0002 => Some("KeyframeAnim"),
        0xB0001 => Some("BlendShape"),
        0xB0002 => Some("BlendShapeBuffer"),
        0xC0001 => Some("TextureOverride"),
        _ => None,
    }
}

/// Every id in the C++ set, ascending. Exposed for tests and for callers that
/// want to print the table.
pub const CPP_TYPE_CODES: &[u32] = &[
    0x10004, 0x10005, 0x10006, 0x10007, 0x10008, 0x10030, 0x20003, 0x20007, 0x20008, 0x20009,
    0x2000b, 0x2001a, 0x200af, 0x70001, 0x70002, 0x70003, 0x7000b, 0x80003, 0x80005, 0xff0000,
    0xff0001, 0xff0002,
];

/// Every id in the Python oracle's map, ascending. Exposed for tests and for
/// callers that want to print the table.
pub const PYTHON_TYPE_CODES: &[u32] = &[
    0x10004, 0x10005, 0x10006, 0x10007, 0x10008, 0x10010, 0x10030, 0x10031, 0x10032, 0x20001,
    0x20002, 0x20003, 0x20004, 0x20005, 0x30001, 0x40001, 0x50001, 0x60001, 0x70001, 0x80001,
    0x80002, 0x80003, 0x90001, 0x90002, 0xA0001, 0xA0002, 0xB0001, 0xB0002, 0xC0001,
];

/// Codes in the C++ set that the C++ comment records as Spore-specific and
/// deliberately unmapped. [`cpp_type_name`] returns `None` for these even
/// though [`known_type_code`] accepts them.
pub const CPP_UNNAMED_TYPE_CODES: &[u32] = &[0x2000b, 0x7000b];

/// Codes Spore emits that are in **neither** reference table. Measured over the
/// 1,131 real records: 591 sections each.
pub const SPORE_ONLY_TYPE_CODES: &[u32] = &[0x7000c, 0x7000f];
