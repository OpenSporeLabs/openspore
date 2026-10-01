
#if defined(_MSC_VER)
#define PKG_PROPERTY_CLEAR_WAVE13_CDECL __cdecl
#else
#define PKG_PROPERTY_CLEAR_WAVE13_CDECL __attribute__((cdecl))
#endif

#if defined(_MSC_VER)
#define PKG_PROPERTY_CLEAR_WAVE13_THISCALL __thiscall
#else
#define PKG_PROPERTY_CLEAR_WAVE13_THISCALL __attribute__((thiscall))
#endif
// Clean-room reconstruction of SporeApp.exe 0x006a2a80
// Original symbol (SDK label): App::PropertyList::Clear
// Binary sha256: 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// Evidence: live Ghidra MCP disassembly of 0x006a2a80 (36 instructions,
// 0x006a2a80..0x006a2acc) plus the persisted SDK decompilation at
// .spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Clear.c
//
// The receiver is taken from ECX into EBX by the third instruction and the body
// returns with a bare RET, so the calling convention is __thiscall with no
// explicit stack arguments and no stack cleanup. EAX is never populated on any
// path, so the return type is void.
//
// Only three words of the receiver are touched, and they are addressed as raw
// displacements rather than as declared fields, because the intermediate bytes
// of the object are not observable from this body. This header therefore
// declares no field of any receiver: the offsets live in the .cpp as the
// constants the listing fixes.

#ifndef OPENSPORE_RECONSTRUCTION_PKG_PROPERTY_CLEAR_WAVE13_006A2A80_HPP
#define OPENSPORE_RECONSTRUCTION_PKG_PROPERTY_CLEAR_WAVE13_006A2A80_HPP

namespace openspore {
namespace reconstruction {
namespace pkg_property_clear_wave13 {

// Element type is opaque: this body only ever manipulates cursors over the
// element array and never dereferences an element.
struct OpaquePropertyEntry;

// Sub-object rooted at receiver+0x18. It is handed to the release helper as the
// `this` of a thiscall, and is never dereferenced here.
struct OpaquePropertySpan;

// --- ports -----------------------------------------------------------------
//
// Both callees are modelled as package-local ports. Neither port body is
// promoted to a record in this package; only the call shape observed at
// 0x006a2a92 and 0x006a2aa1 is claimed here.

typedef OpaquePropertyEntry* (*MoveRangeFn)(OpaquePropertyEntry* first,
                                            OpaquePropertyEntry* last,
                                            OpaquePropertyEntry* out);
typedef void (PKG_PROPERTY_CLEAR_WAVE13_THISCALL *ReleaseRangeFn)(OpaquePropertySpan* self,
                                          OpaquePropertyEntry* first,
                                          OpaquePropertyEntry* last);

// 0x00612b20: three cdecl words pushed by the caller and cleaned by the ADD
// ESP,0xc that follows the call; result in EAX.
OpaquePropertyEntry* PKG_PROPERTY_CLEAR_WAVE13_CDECL __attribute__((noinline))
helper_00612b20(OpaquePropertyEntry* first, OpaquePropertyEntry* last,
                OpaquePropertyEntry* out);

// 0x00685a30: two explicit words popped by the callee (RET 0x8), receiver in
// ECX.
void PKG_PROPERTY_CLEAR_WAVE13_THISCALL __attribute__((noinline))
helper_00685a30(OpaquePropertySpan* self, OpaquePropertyEntry* first,
                OpaquePropertyEntry* last);

// --- target ----------------------------------------------------------------

// App::PropertyList::Clear @ 0x006a2a80.
//
// __thiscall, receiver in ECX, no stack arguments, bare RET, so the callee
// pops nothing. EAX is never written on any path: the return type is void.
void PKG_PROPERTY_CLEAR_WAVE13_THISCALL App_PropertyList_Clear_006a2a80(void* list);

}  // namespace pkg_property_clear_wave13
}  // namespace reconstruction
}  // namespace openspore

#endif  // OPENSPORE_RECONSTRUCTION_PKG_PROPERTY_CLEAR_WAVE13_006A2A80_HPP
