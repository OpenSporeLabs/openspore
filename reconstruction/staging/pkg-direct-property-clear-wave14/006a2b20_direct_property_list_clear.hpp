// Clean-room reconstruction of SporeApp.exe 0x006a2b20
// Original symbol (SDK label): App::DirectPropertyList::Clear
// Binary sha256: 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// Evidence: the complete 39-instruction disassembly of 0x006a2b20
// (0x006a2b20..0x006a2b76) persisted in
// reconstruction/evidence/006a2b20/evidence.json under categories.disassembly,
// the persisted SDK decompilation at
// .spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__Clear.c,
// and live reads of the three direct callee bodies, which establish each call's
// argument order and stack-cleanup ownership.
//
// The receiver arrives in ECX, is copied to ESI by the third instruction, and the
// body ends in a bare RET, so the calling convention is __thiscall with no
// explicit stack arguments and no callee-side stack cleanup. No value reaches the
// caller: the last EAX write is the rewind byte count, and the body stores it
// through the receiver before the epilogue, so the return type is void.
//
// The receiver is addressed only by its machine displacement. The ABI envelope's
// receiver record is bounds_only and enumerates displacements, not members, so
// naming a member would be an identity claim no machine record grounds. The
// intermediate bytes of the object are not observable from this body, which is
// why this header declares no member of any receiver: the offsets live in the
// .cpp as the constants the listing fixes.

#ifndef OPENSPORE_RECONSTRUCTION_PKG_DIRECT_PROPERTY_CLEAR_WAVE14_006A2B20_HPP
#define OPENSPORE_RECONSTRUCTION_PKG_DIRECT_PROPERTY_CLEAR_WAVE14_006A2B20_HPP

#include <cstdint>

#if defined(_MSC_VER)
#define PKG_DIRECT_PROPERTY_CLEAR_WAVE14_CDECL __cdecl
#else
#define PKG_DIRECT_PROPERTY_CLEAR_WAVE14_CDECL __attribute__((cdecl))
#endif

#if defined(_MSC_VER)
#define PKG_DIRECT_PROPERTY_CLEAR_WAVE14_THISCALL __thiscall
#else
#define PKG_DIRECT_PROPERTY_CLEAR_WAVE14_THISCALL __attribute__((thiscall))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_direct_property_clear_wave14 {

// Element of the range whose begin and end cursors live at receiver+0x18 and
// receiver+0x1c. Declared incomplete and with no members: this body only moves
// cursors and never dereferences an element, so no element layout is claimed.
struct OpaqueDirectPropertyEntry;

// Address handed to the release helper as its thiscall receiver. It is the
// receiver displacement 0x18 itself, is never dereferenced by this body, and no
// layout is claimed for it.
struct OpaqueDirectPropertySpan;

// A bare 32-bit word as the machine reads and writes it. The two words at
// receiver+0x38 and receiver+0x3c are only ever loaded and pushed, never
// interpreted here.
typedef std::uint32_t OpaqueWord;

// --- ports -----------------------------------------------------------------
//
// Each direct callee is modelled as a package-local port named with its VA. No
// callee body is promoted to a record in this package; only the call shape
// observed at its call site is claimed.

// 0x0092cb00: three cdecl words. The body computes dest + count*4 and, while that
// end is above dest, stores the value word repeatedly from dest, then returns
// dest in EAX. So it fills `count` consecutive dwords at dest and hands dest
// back. The three words are removed by the caller, not by this callee.
void* PKG_DIRECT_PROPERTY_CLEAR_WAVE14_CDECL __attribute__((noinline))
helper_0092cb00(void* dest, OpaqueWord value, OpaqueWord count);

// 0x00612b20: three cdecl words, result in EAX. The body compares its first two
// words and, while they differ, copies one 0x18-byte element from the first to
// the third and advances both cursors by the stride, returning the advanced
// output cursor. When the first two words are equal it skips the walk and
// returns the third word unchanged.
OpaqueDirectPropertyEntry* PKG_DIRECT_PROPERTY_CLEAR_WAVE14_CDECL __attribute__((noinline))
helper_00612b20(OpaqueDirectPropertyEntry* first,
                OpaqueDirectPropertyEntry* last,
                OpaqueDirectPropertyEntry* out);

// 0x00685a30: receiver in ECX plus two explicit words that its own RET 0x8
// removes. The body walks [first, last) in 0x18 strides and, for each entry
// whose byte at entry+0x14 has its 0x4 bit set, calls a further release helper
// on the sub-object at entry+4. That further release target is out of scope for
// this record, so the port reproduces the traversal and no side effect.
void PKG_DIRECT_PROPERTY_CLEAR_WAVE14_THISCALL __attribute__((noinline))
helper_00685a30(OpaqueDirectPropertySpan* self,
                OpaqueDirectPropertyEntry* first,
                OpaqueDirectPropertyEntry* last);

// --- target ----------------------------------------------------------------

// App::DirectPropertyList::Clear @ 0x006a2b20.
//
// __thiscall, receiver in ECX, no stack arguments, bare RET, so the callee pops
// nothing. No value reaches the caller, so the return type is void.
void PKG_DIRECT_PROPERTY_CLEAR_WAVE14_THISCALL app_direct_property_list_clear_006a2b20(void* list);

}  // namespace pkg_direct_property_clear_wave14
}  // namespace reconstruction
}  // namespace openspore

#endif  // OPENSPORE_RECONSTRUCTION_PKG_DIRECT_PROPERTY_CLEAR_WAVE14_006A2B20_HPP
