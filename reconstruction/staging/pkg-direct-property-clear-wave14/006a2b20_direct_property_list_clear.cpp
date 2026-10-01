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
// intermediate bytes of the object are not observable from this body.

#include "006a2b20_direct_property_list_clear.hpp"

#include <cstdint>
#include <cstring>

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

// 0x0092cb00: three cdecl words. The body computes dest + count*4 and, while that
// end is above dest, stores the value word repeatedly from dest, then returns
// dest in EAX. So it fills `count` consecutive dwords at dest and hands dest
// back. The three words are removed by the caller, not by this callee.
void* PKG_DIRECT_PROPERTY_CLEAR_WAVE14_CDECL __attribute__((noinline))
helper_0092cb00(void* dest, OpaqueWord value, OpaqueWord count) {
  unsigned char* cursor = static_cast<unsigned char*>(dest);
  for (OpaqueWord index = 0; index < count; ++index) {
    std::memcpy(cursor + index * sizeof(OpaqueWord), &value, sizeof(OpaqueWord));
  }
  return dest;
}

// 0x00612b20: three cdecl words, result in EAX. The body compares its first two
// words and, while they differ, copies one 0x18-byte element from the first to
// the third and advances both cursors by the stride, returning the advanced
// output cursor. When the first two words are equal it skips the walk and
// returns the third word unchanged.
OpaqueDirectPropertyEntry* PKG_DIRECT_PROPERTY_CLEAR_WAVE14_CDECL __attribute__((noinline))
helper_00612b20(OpaqueDirectPropertyEntry* first,
                OpaqueDirectPropertyEntry* last,
                OpaqueDirectPropertyEntry* out) {
  OpaqueDirectPropertyEntry* cursor = out;
  while (first != last) {
    // The per-element copy is the callee's own business; only the stride and the
    // returned output cursor are claimed here.
    cursor = reinterpret_cast<OpaqueDirectPropertyEntry*>(
        reinterpret_cast<unsigned char*>(cursor) + 0x18);
    first = reinterpret_cast<OpaqueDirectPropertyEntry*>(
        reinterpret_cast<unsigned char*>(first) + 0x18);
  }
  return out;
}

// 0x00685a30: receiver in ECX plus two explicit words that its own RET 0x8
// removes. The body walks [first, last) in 0x18 strides and, for each entry
// whose byte at entry+0x14 has its 0x4 bit set, calls a further release helper
// on the sub-object at entry+4. That further release target is out of scope for
// this record, so the port reproduces the traversal and no side effect.
void PKG_DIRECT_PROPERTY_CLEAR_WAVE14_THISCALL __attribute__((noinline))
helper_00685a30(OpaqueDirectPropertySpan* self,
                OpaqueDirectPropertyEntry* first,
                OpaqueDirectPropertyEntry* last) {
  (void)self;
  while (first < last) {
    (void)first;
    first = reinterpret_cast<OpaqueDirectPropertyEntry*>(
        reinterpret_cast<unsigned char*>(first) + 0x18);
  }
}

// --- target ----------------------------------------------------------------

void PKG_DIRECT_PROPERTY_CLEAR_WAVE14_THISCALL app_direct_property_list_clear_006a2b20(void* list) {
  unsigned char* const base = static_cast<unsigned char*>(list);

  // 0x006a2b24: MOV EAX,dword ptr [ESI + 0x38]
  const OpaqueWord fill_count =
      *reinterpret_cast<const OpaqueWord*>(base + 0x38);
  // 0x006a2b27: MOV ECX,dword ptr [ESI + 0x3c]
  void* const fill_dest = *reinterpret_cast<void* const*>(base + 0x3c);

  // 0x006a2b2b..0x006a2b2f: PUSH EAX; PUSH 0x0; PUSH ECX; CALL 0x0092cb00
  // The port fills `fill_count` consecutive dwords at fill_dest with the
  // immediate 0x0 and returns fill_dest, which this body discards: the word in
  // EAX is overwritten by the next load.
  (void)helper_0092cb00(fill_dest, 0, fill_count);

  // 0x006a2b34: MOV EBX,dword ptr [ESI + 0x18]
  OpaqueDirectPropertyEntry* const first =
      *reinterpret_cast<OpaqueDirectPropertyEntry* const*>(base + 0x18);
  // 0x006a2b37: MOV EDI,dword ptr [ESI + 0x1c]
  OpaqueDirectPropertyEntry* const last =
      *reinterpret_cast<OpaqueDirectPropertyEntry* const*>(base + 0x1c);
  // 0x006a2b3a: ADD ESI,0x18 -- ESI stops being the receiver base and is reused
  // as the second call's thiscall receiver and as the base of its [ESI + 0x4]
  // load, so [ESI + 0x4] is receiver+0x1c.
  OpaqueDirectPropertySpan* const span =
      reinterpret_cast<OpaqueDirectPropertySpan*>(base + 0x18);

  // 0x006a2b3d..0x006a2b40: PUSH EBX; PUSH EDI; PUSH EDI; CALL 0x00612b20
  // The pushed range is degenerate, because the first two words are the same
  // register, so the port skips its walk and hands back the third word: the
  // begin cursor.
  OpaqueDirectPropertyEntry* const cursor = helper_00612b20(last, last, first);

  // 0x006a2b45: MOV EDX,dword ptr [ESI + 0x4]  (== receiver+0x1c)
  // The end cursor is re-read from memory after the move rather than taken from
  // the register captured before it.
  OpaqueDirectPropertyEntry* const end_after_move =
      *reinterpret_cast<OpaqueDirectPropertyEntry* const*>(base + 0x1c);

  // 0x006a2b48: ADD ESP,0x18 -- one cleanup removes six words: the three
  // argument words of the fill call and the three of the move call. Both ports
  // are therefore cdecl and the caller owns their stack.
  // 0x006a2b4b..0x006a2b4f: PUSH EDX; PUSH EAX; MOV ECX,ESI; CALL 0x00685a30
  helper_00685a30(span, cursor, end_after_move);

  // 0x006a2b54: SUB EDI,EBX -- a byte subtraction of the two cursors captured
  // before either call, not an element count.
  const std::int32_t span_bytes = static_cast<std::int32_t>(
      reinterpret_cast<const char*>(last) - reinterpret_cast<const char*>(first));

  // 0x006a2b56: MOV EAX,0xd5555555 ; 0x006a2b5b: IMUL EDI -- a signed 32x32
  // product whose high half lands in EDX.
  const std::int64_t product = static_cast<std::int64_t>(span_bytes) *
                               static_cast<std::int32_t>(0xd5555555);
  const std::int32_t high_half = static_cast<std::int32_t>(product >> 32);
  // 0x006a2b5d: SAR EDX,0x2
  const std::int32_t halved = high_half >> 0x2;
  // 0x006a2b60: MOV EAX,EDX ; 0x006a2b62: SHR EAX,0x1f
  const std::int32_t biased =
      static_cast<std::int32_t>(static_cast<std::uint32_t>(halved) >> 0x1f);
  // 0x006a2b65: ADD EAX,EDX
  const std::int32_t groups = biased + halved;
  // 0x006a2b67: LEA EAX,[EAX + EAX*0x2] then 0x006a2b6a, 0x006a2b6c,
  // 0x006a2b6e: ADD EAX,EAX three times -- the corrected quotient scaled by
  // three and then by eight, i.e. multiplied by the 0x18 element stride.
  const std::int32_t rewind = groups * 0x18;

  // 0x006a2b70: ADD dword ptr [ESI + 0x4],EAX  (== receiver+0x1c)
  // The product is added to the end cursor, so for a span that is a whole number
  // of strides the end cursor is rewound onto the begin cursor and the range is
  // emptied; a ragged span lands on the nearest lower stride boundary.
  *reinterpret_cast<OpaqueDirectPropertyEntry**>(base + 0x1c) =
      reinterpret_cast<OpaqueDirectPropertyEntry*>(
          reinterpret_cast<unsigned char*>(last) + rewind);

  // 0x006a2b73..0x006a2b76: POP EDI; POP ESI; POP EBX; RET -- a bare RET with no
  // immediate, and a frame balanced by the single ADD ESP,0x18 above.
}

}  // namespace pkg_direct_property_clear_wave14
}  // namespace reconstruction
}  // namespace openspore
