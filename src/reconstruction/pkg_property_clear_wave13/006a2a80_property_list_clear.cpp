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
// of the object are not observable from this body.

#include "006a2a80_property_list_clear.hpp"

#include <cstdint>

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

namespace openspore {
namespace reconstruction {
namespace pkg_property_clear_wave13 {

// 0x00612b20: three cdecl words pushed by the caller, cleaned by the ADD ESP,
// 0xc, that follows the call; result in EAX.
OpaquePropertyEntry* PKG_PROPERTY_CLEAR_WAVE13_CDECL __attribute__((noinline))
helper_00612b20(OpaquePropertyEntry* first, OpaquePropertyEntry* last,
                OpaquePropertyEntry* out) {
  // The observed body (27 instructions, 0x00612b20..0x00612b59) compares its
  // first two words with CMP ESI,EBX / JZ and, when they are equal, falls
  // straight to `MOV EAX,dword ptr [ESP + 0x14]` and returns the third word
  // unchanged. The non-degenerate arm is a 0x18-stride walk that moves each
  // element into `out` and returns the advanced output cursor; per element it
  // writes the dword at +0x00 inline and then thiscall-calls 0x00542b80 with
  // ECX = out_element+0x4 and the source's +0x4 pushed, so the move is a
  // four-dword block plus two flag words, not a single 8-byte copy.
  //
  // This call site always passes first == last, so the walk is never entered and
  // the third word is returned unchanged. That degenerate contract is all this
  // port claims.
  (void)first;
  (void)last;
  return out;
}

// 0x00685a30: two explicit words popped by the callee (RET 0x8), receiver in ECX.
void PKG_PROPERTY_CLEAR_WAVE13_THISCALL __attribute__((noinline))
helper_00685a30(OpaquePropertySpan* self, OpaquePropertyEntry* first,
                OpaquePropertyEntry* last) {
  // The observed body (18 instructions, 0x00685a30..0x00685a59) bounds the walk
  // with an unsigned compare (JNC on the pretest, JC on the back edge) and
  // advances by the 0x18 element stride. For each entry it applies
  // `TEST byte ptr [ESI + 0x14],0x4`; when that mask is set it pushes 0x0, forms
  // ECX = entry+0x4 and calls 0x0093db80, whose own first act is to test
  // `byte ptr [ESI + 0x10],0x4` on the address it is given. The release is out
  // of scope for this record, so the port reproduces the unsigned 0x18-stride
  // traversal and no side effect.
  (void)self;
  std::uintptr_t cursor = reinterpret_cast<std::uintptr_t>(first);
  const std::uintptr_t end = reinterpret_cast<std::uintptr_t>(last);
  while (cursor < end) {
    cursor += 0x18;
  }
}

// --- target ----------------------------------------------------------------

void PKG_PROPERTY_CLEAR_WAVE13_THISCALL App_PropertyList_Clear_006a2a80(void* list) {
  unsigned char* const base = reinterpret_cast<unsigned char*>(list);

  // 0x006a2a83: MOV EBX,ECX
  // 0x006a2a85: MOV EBP,dword ptr [EBX + 0x18]
  OpaquePropertyEntry* const first =
      *reinterpret_cast<OpaquePropertyEntry* const*>(base + 0x18);
  // 0x006a2a89: MOV EDI,dword ptr [EBX + 0x1c]
  OpaquePropertyEntry* const last =
      *reinterpret_cast<OpaquePropertyEntry* const*>(base + 0x1c);
  // 0x006a2a8c: LEA ESI,[EBX + 0x18]
  OpaquePropertySpan* const span =
      reinterpret_cast<OpaquePropertySpan*>(base + 0x18);

  // 0x006a2a8f..0x006a2a92: PUSH EBP; PUSH EDI; PUSH EDI; CALL 0x00612b20
  // The pushed range is degenerate (its first two words are the same register),
  // so the helper's compare is equal, its loop pretest is never taken, and it
  // hands back its third word -- the begin cursor it was given.
  OpaquePropertyEntry* const cursor = helper_00612b20(last, last, first);

  // 0x006a2a97: MOV ECX,dword ptr [ESI + 0x4]   (ESI + 0x4 == base + 0x1c)
  // 0x006a2a9a: ADD ESP,0xc - the caller, not the callee, removes the three words
  // of the first call.
  // 0x006a2a9d..0x006a2aa1: PUSH ECX; PUSH EAX; MOV ECX,ESI; CALL 0x00685a30
  helper_00685a30(span, cursor,
                  *reinterpret_cast<OpaquePropertyEntry* const*>(base + 0x1c));

  // 0x006a2aa6..0x006a2ac1, transcribed operation for operation. The span is a
  // byte subtraction of the two cursors, not an element count.
  const std::int32_t span_bytes = static_cast<std::int32_t>(
      reinterpret_cast<const char*>(last) - reinterpret_cast<const char*>(first));

  // 0x006a2aa8: MOV EAX,0xd5555555
  // 0x006a2aad: IMUL EDI          -> the 32x32 signed product occupies EDX:EAX,
  // so the high half is selected by shifting the widened product down.
  const std::int64_t product = static_cast<std::int64_t>(span_bytes) *
                               static_cast<std::int32_t>(0xd5555555);
  const std::int32_t high_half = static_cast<std::int32_t>(product >> 32);
  // 0x006a2aaf: SAR EDX,0x2
  const std::int32_t halved = high_half >> 0x2;
  // 0x006a2ab2: MOV EAX,EDX
  // 0x006a2ab4: SHR EAX,0x1f
  const std::int32_t biased =
      static_cast<std::int32_t>(static_cast<std::uint32_t>(halved) >> 0x1f);
  // 0x006a2ab7: ADD EAX,EDX
  const std::int32_t groups = biased + halved;
  // 0x006a2ab9..0x006a2ac1: LEA EDX,[EAX + EAX*0x2]; ADD EDX,EDX (three times)
  const std::int32_t rewind = groups * 0x18;

  // 0x006a2ac3: ADD dword ptr [ESI + 0x4],EDX   (ESI + 0x4 == base + 0x1c)
  // The accumulated product is the negated span rounded down to a multiple of
  // the element stride, so for any well-formed span this rewinds the end cursor
  // back onto the begin cursor and empties the range. The machine adds to
  // whatever the word holds at this instruction, so the word is read again here
  // rather than reusing the copy taken into EDI before either call: the claim
  // must not depend on the release helper having left it untouched.
  *reinterpret_cast<OpaquePropertyEntry**>(base + 0x1c) =
      reinterpret_cast<OpaquePropertyEntry*>(
          reinterpret_cast<unsigned char*>(
              *reinterpret_cast<OpaquePropertyEntry* const*>(base + 0x1c)) +
          rewind);

  // 0x006a2ac6: INC dword ptr [EBX + 0x34]
  ++(*reinterpret_cast<std::int32_t*>(base + 0x34));

  // 0x006a2ac9..0x006a2acc: POP ESI; POP EBP; POP EBX; RET
}

}  // namespace pkg_property_clear_wave13
}  // namespace reconstruction
}  // namespace openspore
