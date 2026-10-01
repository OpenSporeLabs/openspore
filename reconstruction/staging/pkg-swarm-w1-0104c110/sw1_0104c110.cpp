// PKG-SWARM-W1-0104C110 -- VA 0x0104c110
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// The body, reproduced instruction for instruction. The header carries the full
// evidence trail; this file is the reconstruction, and its code is deliberately
// as small as the two-instruction original is. Nothing is added that the
// machine does not show: no null check on the receiver (the body has none), no
// branch, no default, no normalisation, no cache, no callee.
//
// What the original does, in the order it does it:
//
//   0x0104c110   8B 81 10 02 00 00   MOV EAX, dword ptr [ECX + 0x210]
//   0x0104c116   C3                  RET
//
// The three things a reader of this file has to be told, because each is a way
// to be wrong here:
//
//  * THE RECEIVER IS READ, NOT WRITTEN, AND NOT TESTED. ECX is dereferenced at
//    0x0104c110 with no preceding compare and no conditional branch, and the
//    machine receiver record carries written_through = 0. So there is no null
//    guard to model: one was not in the machine, and adding one would invent a
//    branch the two-instruction listing cannot contain. A null receiver faults
//    in the original, and it faults here.
//
//  * THE READ IS ONE LEVEL DEEP AND IT IS THE RECEIVER'S OWN MEMORY. The
//    original reads [ECX + 0x210]: the receiver pointer is the base, and the
//    4 bytes at 0x210 are the value. It does not load a pointer out of
//    0x210 and dereference that, and it does not treat ECX as a pointer to a
//    separate header. word_at() below performs exactly the one dereference the
//    original performs, in the same direction.
//
//  * THE VALUE IS RETURNED UNMODIFIED AND BIT-EXACT. 32 bits out, 32 bits
//    back: no sign extension, no zero-extension, no truncation to 16 or 8 bits,
//    no byte swap. EAX's only definition is the load, and the RET immediately
//    follows, so there is no opportunity in the body for anything to happen to
//    the value in between.

#include "sw1_0104c110_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_0104c110 {

// FUN_0104c110 @ 0x0104c110 -- the single-field accessor at receiver + 0x210.
//
//   0x0104c110   8B 81 10 02 00 00   MOV EAX, dword ptr [ECX + 0x210]
//   0x0104c116   C3                  RET
//
// The only executable statement is the load. It is written with the displacement
// as a literal rather than through the header's kReceiverFieldDisplacement
// constant so that the constant this body implements is visible at the point of
// use and the two can be compared by eye; the header's static_assert already
// pins the constant to the receiver's size, and the model test asserts the
// literal against a planted value at that exact displacement.
extern "C" FieldWord PKG_SW1_0104C110_THISCALL re_0104c110(
    OpaqueVtableOwner* receiver) {
  return *word_at(receiver, 0x210);
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_0104c110
