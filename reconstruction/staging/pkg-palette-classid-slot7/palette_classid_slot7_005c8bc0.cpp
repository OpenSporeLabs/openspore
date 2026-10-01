// Bounded x86-32 reconstruction of the body at VA 0x005c8bc0.
//
// What the machine body is, and is not
// ------------------------------------
//
// 39 bytes, 12 instructions, no frame, no memory write, no dereference, no
// call, no data-segment access. It is a leaf predicate over two inputs: the
// value the caller leaves in ECX, and the one four-byte argument it pops off
// the stack at entry_ESP+0x4.
//
// The SDK symbol table names 0x005c8bc0 `Palettes::PalettePage::Load` and the
// SDK header declares that method thiscall with six parameters. A six-parameter
// thiscall ends in RET 0x14. This body ends in RET 0x4, so the caller pushed
// exactly one four-byte word. The SDK name and prototype are therefore not
// adopted, and this file reconstructs the body the binary actually ships rather
// than the header it was labelled with. The name mismatch is recorded in the
// metadata sidecar, not resolved here.
//
// The function is nonetheless a real virtual method, which is why the receiver
// is spelled as a thiscall receiver here. Its only xref is the data word at
// 0x013f8318, which is word 7 of the function-pointer table at 0x013f82fc.
// That table is a vtable, not a plain array: words 0 and 6 of it hold
//   0x005c9060: 83 e9 04           SUB ECX,0x4
//                e9 08 00 00 00    JMP  0x005c9070
// which is the MSVC this-adjusting thunk emitted for a multiple-inheritance
// class, where one of the slot pointers has to shift the receiver back to the
// primary base before dispatching. A table that mixes adjusting thunks with
// ordinary implementations is a vtable. Both thunks were read at those two
// addresses in this binary; neither is a guess.
//
// Data flow, one machine instruction at a time
// -------------------------------------------
//
//   MOV EAX,ECX                     result <- the ECX input
//   MOV ECX,[ESP+0x4]               ECX <- the popped stack argument
//   CMP ECX,0xee3f516e / JZ RET     equal: return the saved ECX input
//   CMP ECX,0x2f009dd0 / JZ RET     equal: return the saved ECX input
//   XOR EDX,EDX                     EDX <- 0
//   CMP ECX,0x72deed2b
//   SETNZ DL                        DL <- 1 when the argument is NOT the third
//                                  class id, 0 when it is
//   DEC EDX                         EDX <- 0xfffffffe+1 == 0, or 0xffffffff
//   AND EAX,EDX                     mask the saved ECX input
//   RET 0x4                         pop the one four-byte argument
//
// The mask therefore keeps the saved input when the argument DOES equal
// 0x72deed2b and clears it in every other case, exactly like the two JZ guards
// above it. All three compared values behave alike: the body returns the saved
// ECX input for each of them, and zero for everything else. The three guards
// are one membership test, not three different behaviours.
//
// What the argument is
// --------------------
//
// All three compared constants are Spore class tokens, carried by the SDK
// symbol table's ENUM_ENTRY list:
//   0xee3f516e  Object                    (line 51581)
//   0x2f009dd0  UTFWin::IWinProc          (line 51651)
//   0x72deed2b  Palettes::PalettePageUI   (line 51714)
// so the single stack argument is a 32-bit class id being asked about. The body
// answers by handing the receiver back when the queried id is one of the three
// it recognises, and a null pointer when it is not.
//
// Note what that does and does not license. The three tokens are named Object,
// UTFWin::IWinProc and Palettes::PalettePageUI, and they are unrelated to one
// another -- a base type, a windowing interface and a palette UI. This body
// does not therefore read as a coherent domain predicate, and no such reading
// is asserted here. What is asserted is the arithmetic: a three-way membership
// test over three class ids, returning the receiver or null. Any wider story
// about why one vtable slot tests exactly those three is left open in the
// sidecar.
//
// Correction against a sibling candidate
// -------------------------------------
//
// reconstruction/staging/pkg-palette-wave6/pkg_palette_wave6.cpp already
// reconstructs this body as `key == 0xee3f516e || key == 0x2f009dd0 ||
// key == 0x72deed2b ? self : nullptr`, which agrees instruction for instruction
// with the reading above.
//
// reconstruction/staging/pkg-palette-wave12/005c8bc0_palette_page_load.cpp does
// not: it writes the third guard as `(stack_input != 0x72deed2bU) ? ~0U : 0U`,
// which keeps the input when the argument is NOT the third class id, and its
// sidecar's result_function string repeats the same inversion. The machine
// goes the other way. 0x0f95c2 is SETNZ DL and 0x33d2 zeroed EDX just before it,
// so the SETNZ defines the whole of EDX: the argument equal to 0x72deed2b sets
// DL to 0, DEC EDX then produces all ones, and AND EAX,EDX keeps the saved ECX
// input. That candidate is left untouched on disk; the disagreement is recorded,
// not resolved by editing another package.

#include "palette_classid_slot7_005c8bc0.hpp"

namespace openspore::reconstruction::pkg_palette_classid_slot7 {

OpaqueSlot7Receiver* PKG_PCS7_THISCALL palette_classid_slot7_005c8bc0(
    OpaqueSlot7Receiver* receiver, std::uint32_t class_id) {
  // 005c8bc0  MOV EAX,ECX -- the result register takes the receiver unchanged.
  // The receiver is never dereferenced anywhere in the body, so it is only ever
  // carried, and a null receiver is as legal an input as any other.
  auto result = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(receiver));

  // 005c8bc6  CMP ECX,0xee3f516e / 005c8bcc  JZ 0x005c8be4
  if (class_id == kClassIdObject) {
    return receiver;
  }

  // 005c8bce  CMP ECX,0x2f009dd0 / 005c8bd4  JZ 0x005c8be4
  if (class_id == kClassIdUTFWinIWinProc) {
    return receiver;
  }

  // 005c8bd6  XOR EDX,EDX / 005c8bd8  CMP ECX,0x72deed2b
  // 005c8bde  SETNZ DL / 005c8be1  DEC EDX
  // SETNZ writes DL against an EDX that XOR just cleared, so the pair yields
  // 0xffffffff when class_id EQUALS kClassIdPalettePageUI and 0 when it does
  // not -- the third guard behaves like the two JZ guards above it.
  const std::uint32_t keep =
      (class_id == kClassIdPalettePageUI) ? ~0U : 0U;

  // 005c8be2  AND EAX,EDX
  result &= keep;

  // 005c8be4  RET 0x4 -- the callee pops the one four-byte stack argument.
  return reinterpret_cast<OpaqueSlot7Receiver*>(
      static_cast<std::uintptr_t>(result));
}

}  // namespace openspore::reconstruction::pkg_palette_classid_slot7
