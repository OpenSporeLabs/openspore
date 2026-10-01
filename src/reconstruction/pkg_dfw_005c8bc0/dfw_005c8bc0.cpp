// PKG-DFW-005C8BC0 -- VA 0x005c8bc0
// Editor-support cluster, Palettes subsystem
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Machine listing, 12 instructions, body 0x005c8bc0..0x005c8be4 inclusive
// (39 bytes, Ghidra body_end 0x005c8be6, parse.declared_count 12, unparsed 0,
// degraded false, flow_complete true). Verified byte for byte against the live
// bridge (GhidraMCP /read_memory at 0x005c8bc0) and against the committed pack
// reconstruction/evidence/005c8bc0/evidence.json, category disassembly. The
// thirty-nine bytes are:
//
//   8b c1 8b 4c 24 04 81 f9 6e 51 3f ee 74 16 81 f9 d0 9d 00 2f 74 0e
//   33 d2 81 f9 2b ed de 72 0f 95 c2 4a 23 c2 c2 04 00
//
// and they decode instruction for instruction to:
//
//   0x005c8bc0  8B C1           MOV EAX,ECX
//   0x005c8bc2  8B 4C 24 04     MOV ECX,dword ptr [ESP + 0x4]
//   0x005c8bc6  81 F9 6E 51 3F EE   CMP ECX,0xee3f516e
//   0x005c8bcc  74 16           JZ  0x005c8be4      (0x005c8bce + 0x16)
//   0x005c8bce  81 F9 D0 9D 00 2F   CMP ECX,0x2f009dd0
//   0x005c8bd4  74 0E           JZ  0x005c8be4      (0x005c8bd6 + 0x0e)
//   0x005c8bd6  33 D2           XOR EDX,EDX
//   0x005c8bd8  81 F9 2B ED DE 72   CMP ECX,0x72deed2b
//   0x005c8bde  0F 95 C2        SETNZ DL
//   0x005c8be1  4A              DEC EDX
//   0x005c8be2  23 C2           AND EAX,EDX
//   0x005c8be4  C2 04 00        RET 0x4
//
// What the body is
// -----------------
//
// A leaf over two inputs and no memory of its own: no frame, no store, no call,
// no indirect transfer, no data-segment access. It reads the word the caller left
// in ECX, reads the one word the caller pushed, and returns one of the two.
//
// Data flow, one machine instruction at a time
// -------------------------------------------
//
//   0x005c8bc0  MOV EAX,ECX      the result register takes the ECX input
//   0x005c8bc2  MOV ECX,[ESP+0x4] ECX is overwritten with the stack argument
//   0x005c8bc6  CMP ECX,0xee3f516e
//   0x005c8bcc  JZ  0x005c8be4    equal: return the saved ECX input untouched
//   0x005c8bce  CMP ECX,0x2f009dd0
//   0x005c8bd4  JZ  0x005c8be4    equal: return the saved ECX input untouched
//   0x005c8bd6  XOR EDX,EDX      EDX <- 0
//   0x005c8bd8  CMP ECX,0x72deed2b
//   0x005c8bde  SETNZ DL         DL  <- 1 when the argument is NOT that value
//   0x005c8be1  DEC EDX          EDX <- 0xffffffff when it IS, 0 when it is not
//   0x005c8be2  AND EAX,EDX      mask the saved ECX input
//   0x005c8be4  RET 0x4          the callee drops the one stack argument
//
// The two values are rigorously separate, and this is the one substantive ABI
// error available here. The receiver is the word in ECX on entry. The stack word
// is a 32-bit integral value that the body compares against three immediates and
// nothing else: it is never dereferenced, never written, never aliased into a
// register that survives, and never becomes the value in EAX. It is not a
// pointer, not a receiver, not a field, and not an identifier this pack can name.
//
// The third guard, read exactly as the machine computes it
// -------------------------------------------------------
//
// SETNZ at 0x005c8bde writes DL and nothing else, against the EDX that XOR at
// 0x005c8bd6 has just cleared. So the pair (SETNZ, DEC) yields:
//
//   argument == 0x72deed2b  ->  DL = 0  ->  EDX = 0 - 1 = 0xffffffff  ->  keep
//   argument != 0x72deed2b  ->  DL = 1  ->  EDX = 1 - 1 = 0x00000000  ->  clear
//
// which is the same verdict the two JZ guards above it give. All three compared
// values therefore behave alike: the body returns the saved ECX input for each of
// them and zero for every other input. The third guard is not an exception and not
// an inversion; the mask keeps the input exactly when the argument EQUALS the
// third value. (A sibling candidate, pkg-palette-wave12, inverts this; the machine
// does not, and that candidate is left untouched on disk with the disagreement
// recorded in the sidecar rather than resolved by editing another package.)
//
// Return word
// -----------
//
// Four bytes, in EAX, on every path. On the two JZ paths it is the ECX input bit
// for bit -- MOV EAX,ECX at 0x005c8bc0 is the last write to EAX before either
// RET, and neither JZ touches it. On the fall-through path it is that word AND
// the mask, so it is either the same word or zero. The machine therefore returns
// the input word or zero; it does not return a one-bit flag. The live decompiler
// spells the return `bool` and tests only the low byte of ECX, which is a
// narrowing the listing does not support; the disagreement is open, not settled,
// and the width asserted here is the machine's.
//
// Other record-level disagreements, all left open in the sidecar: the SDK symbol
// table's `Palettes::PalettePage::Load` and its six-parameter prototype (a
// six-parameter thiscall ends in RET 0x14, this body ends in RET 0x4); the
// zero-callers fan-in, so the argument surface modelled above is what the body
// reads, not what any known caller passes; and the three compared values, whose
// identity and role nothing in this pack states.

#include "dfw_005c8bc0_types.hpp"

namespace openspore::reconstruction::pkg_dfw_005c8bc0 {

// Placed first in this translation unit on purpose: the validator binds a source
// span to 0x005c8bc0 by the 8-hex VA token appearing in the function name, and it
// takes the FIRST such definition in the file.
//
// THE CONVENTION IS __thiscall. That is the machine's determination, not a choice
// this package made: the derived ABI record names __thiscall with confidence
// INFERRED and no other candidate, puts the receiver in ECX with provenance
// vftable_slot_dispatch (rule R1-VFT, on this address being slot 7 of the vptr-
// backed vftable at 0x013f82fc), and observes the cleanup as callee-side with
// four bytes (rule C6B). The entry spells the convention token __thiscall through
// the package macro PKG_DFW_005C8BC0_THISCALL, which is the attribute form on
// GCC and clang and the keyword form on MSVC; the token is what the validator
// reads out of this span.
//
// The name carries the VA and the record's own last name component
// ("Palettes::PalettePage::Load" -> "Load") so the reconstruction is bound to this
// target by address and name rather than by an address alone.
extern "C" unclassified_in_EAX PKG_DFW_005C8BC0_THISCALL
dfw_005c8bc0_load(Word receiver_word, Word queried_value) {
  // 0x005c8bc0  MOV EAX,ECX
  //
  // The result register takes the ECX input, all 32 bits of it, before anything
  // else happens. ECX is then overwritten at 0x005c8bc2, so this is the only
  // place the incoming register is captured.
  unclassified_in_EAX result = receiver_word;

  // 0x005c8bc2  MOV ECX,dword ptr [ESP + 0x4]
  //
  // The one and only memory operand in the body: the caller's single pushed word,
  // read over ESP with no frame of this function's own (the body pushes nothing
  // and subtracts nothing, so entry_ESP+0x4 is the argument slot itself). It
  // lands in ECX, so every comparison below is against the stack word and never
  // against the register input. Nothing dereferences it.

  // 0x005c8bc6  CMP ECX,0xee3f516e
  // 0x005c8bcc  JZ  0x005c8be4
  //
  // Taken: the branch lands on the shared terminator, skipping the block below.
  // EAX still holds the word MOV EAX,ECX put there, and neither the compare nor
  // the jump writes to it, so the value returned is the ECX input unchanged.
  if (queried_value == kFirstComparedValue) {
    return result;
  }

  // 0x005c8bce  CMP ECX,0x2f009dd0
  // 0x005c8bd4  JZ  0x005c8be4
  //
  // The second of the same two-instruction guard, to the same terminator and with
  // the same consequence for EAX.
  if (queried_value == kSecondComparedValue) {
    return result;
  }

  // 0x005c8bd6  XOR EDX,EDX
  Word edx = 0u;

  // 0x005c8bd8  CMP ECX,0x72deed2b
  // 0x005c8bde  SETNZ DL
  //
  // SETNZ writes the low byte of EDX and leaves the other three as XOR left them,
  // so this instruction is the whole of DL's value: 1 when the argument is NOT
  // the third compared value, 0 when it is.
  if (queried_value != kThirdComparedValue) {
    edx = 1u;
  }

  // 0x005c8be1  DEC EDX
  //
  // 0 - 1 and 1 - 1 in unsigned arithmetic: 0xffffffff in the equality case, 0 in
  // every other case. Unsigned wraparound is defined, so this is the machine's own
  // operation, not an approximation of it.
  edx = edx - 1u;

  // 0x005c8be2  AND EAX,EDX
  //
  // A full-word AND (23 C2: mod=11, reg=EAX, r/m=EDX), not a test and not a byte
  // operation: an all-ones mask returns the saved ECX input bit for bit and a zero
  // mask returns zero, with no width and no sign involved on either side.
  result &= edx;

  // 0x005c8be4  RET 0x4
  //
  // The shared terminator all three paths reach, and the immediate 4 is the callee
  // dropping the one word it read at 0x005c8bc2. That is what fixes the argument
  // count at one and the stack ownership with the callee.
  return result;
}

}  // namespace openspore::reconstruction::pkg_dfw_005c8bc0
