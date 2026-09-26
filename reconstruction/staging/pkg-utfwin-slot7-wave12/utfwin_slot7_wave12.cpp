#include "utfwin_slot7_wave12.hpp"

namespace openspore::reconstruction::pkg_utfwin_slot7_wave12 {

// 0x00fc7e10, 17 bytes, 5 instructions, leaf.
//
// Observed body, in order:
//   MOV EAX, dword ptr [ESP + 0x4]   ; first incoming stack word
//   MOV EDX, dword ptr [ESP + 0x8]   ; second incoming stack word
//   MOV dword ptr [ECX + 0x8],  EAX  ; publish the first word at +0x08
//   MOV dword ptr [ECX + 0x10], EDX  ; publish the second word at +0x10
//   RET 0x8                          ; callee pops both stack words
//
// Proven by the body, and therefore relied on by this reconstruction:
//   - receiver in ECX, dereferenced only as a store base;
//   - exactly two 4-byte incoming stack words, consumed by this frame;
//   - exactly two dword stores, at receiver +0x08 and receiver +0x10;
//   - no branch, so the CFG is a single block;
//   - no CALL and no absolute address, so no callee and no global;
//   - no word other than +0x08 and +0x10 is written.
//
// No transformation is applied to either word: there is no comparison, mask,
// widening or range check, so both are stored exactly as received. The
// functions that later consume the two offsets are the reason the words are
// opaque here rather than typed:
//
//   - 0x00fc7ec0 (slot +0x48 of vtable 0x01493990) loads the word at +0x08
//     into ECX and calls it, pushing the word at +0x10 as the third of three
//     stack arguments before "CALL ECX" and "ADD ESP, 0xc" after it. So the
//     first argument is installed where the class later treats it as a code
//     address, and the second argument is installed where the class later
//     passes it to that code.
//   - 0x0093b6c0 (slot +0x20) returns the word at +0x08 unchanged in EAX.
//
// Neither reader is a caller of this target, and both are virtual slots, so
// this is a statement about how the stored words are used, not about who calls
// this function. No caller of this target exists in the binary.
//
// EAX is returned to reproduce the observed exit register state. The original
// body contains no instruction that produces a result in EAX, so the source
// level return type is not established by the evidence; see the metadata
// record for the open question and for the SDK prototype mismatch.
extern "C" OpaqueWord PKG_UTFWIN_SLOT7_THISCALL
re_00fc7e10_UTFWin_ImageDrawable_GetTiling(OpaqueSlot7ReceiverWire *self,
                                           OpaqueWord first_word,
                                           OpaqueWord second_word) {
  // Observed convention: __thiscall. The receiver arrives in ECX and the body
  // ends with RET 0x8, so this callee pops its own two 4-byte stack words.
  // That cleanup rules out cdecl and fastcall, and the receiver register rules
  // out stdcall. The two words below are therefore the only arguments, they
  // are stored exactly as received, and no caller-side cleanup is expected.
  self->word_08 = first_word;
  self->word_10 = second_word;

  // EAX is returned to reproduce the observed exit register state; the original
  // never loads a produced result into EAX, so see the metadata record for why
  // the source level return type stays unresolved.
  return first_word;
}

}
