// PKG-SWARM-W1-005BA0D0 -- VA 0x005ba0d0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_005ba0d0 @ 0x005ba0d0.
//
// HONESTY NOTE ON WHERE EVERY OFFSET IN THIS HEADER COMES FROM, because the split
// matters to a reader:
//
//  * Two receiver displacements, and only two, are reached by the body itself:
//    0x18 and 0x14. They are 0x18 (the dword the body reads, decrements, and
//    conditionally restores to 1) and 0x14 (the word the body loads and then
//    dereferences, and the address it hands to the callee as its receiver).
//    Both are re-read from the image bytes for this package:
//
//      0x005ba0d0  8b 41 18              mov eax,DWORD PTR [ecx+0x18]
//      0x005ba0d3  83 c1 14              add ecx,0x14
//      0x005ba0d6  83 c0 ff              add eax,0xffffffff
//      0x005ba0d9  89 41 04              mov DWORD PTR [ecx+4],eax     -> +0x18
//      0x005ba0dc  75 11                 jne 0x5ba0ef
//      0x005ba0de  c7 41 04 01 00 00 00  mov DWORD PTR [ecx+4],0x1    -> +0x18
//      0x005ba0e5  8b 01                 mov eax,DWORD PTR [ecx]      -> +0x14
//      0x005ba0e7  8b 10                 mov edx,DWORD PTR [eax]
//      0x005ba0e9  6a 01                 push 0x1
//      0x005ba0eb  ff d2                 call edx
//      0x005ba0ed  33 c0                 xor eax,eax
//      0x005ba0ef  c3                    ret
//
//  * The machine-derived receiver record for this VA enumerates offsets [24] and
//    register ECX, i.e. 0x18 only, and states written_through 0. The listing
//    plainly also reaches 0x14, so the record is INCOMPLETE here rather than
//    contradictory: the record itself abstained with "flow_not_modelled: the
//    linear ESP walk ends at +4, so the listing is not one path", and 0x14 only
//    becomes a displacement once 0x005ba0d3 has rewritten ECX. The listing wins.
//    The disagreement is recorded in the sidecar, not smoothed over.
//
//  * 0x14 being a VTABLE POINTER rather than a pointer to a polymorphic object
//    is not a choice: it is the only reading the two instructions at 0x005ba0e5
//    and 0x005ba0e7 leave open, and it is corroborated from outside this body by
//    the constructor at 0x005ac980, which installs two pointer words on a fresh
//    object -- 0x013f718c at +0x00 (0x005ac996) and 0x013f76c4 at +0x14
//    (0x005ac99c) -- and zeroes +0x18 (`mov DWORD PTR [esi+0x18],0x0` at
//    0x005ac98f). The body reads the word at +0x14 as a vtable pointer, calls
//    its slot 0 with +0x14 as the receiver, and writes the word at +0x18 twice.
//    Both words this body touches are words that constructor also writes, at the
//    same offsets.
//
//  * No member is named beyond those two offsets. The receiver's +0x00 and
//    +0x01..+0x13 are never read or written by this body, so no member name is
//    declared for them: calling +0x18 a "timer", a "cooldown", a "counter" or a
//    "reference count" is a story this body's twelve instructions do not carry.
//    The two words are named field_14 and field_18 for where they live; their
//    types say what the machine does to them and nothing more.
//
//  * 0x14 heads an embedded subobject and 0x18 is the dword at that subobject's
//    own +0x04 -- the two are adjacent, not nested, and the overlap is asserted
//    below so a reader cannot mistake one for the other. Nothing shows the
//    subobject's extent, so it is modelled as exactly the two words this body can
//    see and no padding is invented past +0x1b.
//
//  * No name is claimed for the callee. The function called at 0x005ba0eb is
//    reached as slot 0 of a vtable word, and SporeApp.exe carries no MSVC RTTI
//    (AGENTS.md, "SporeApp.exe has no MSVC RTTI"), so the class that vtable
//    belongs to is not recoverable from anything in this image. The extern below
//    is named after the CALL SITE, not after a guess.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-005ba0d0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC 16 rejects the
// bare MSVC keywords outright, so the x86-32 attribute form is the portable
// spelling and the keyword form is kept for MSVC.
//
//   PKG_SWARM_W1_005BA0D0_THISCALL  the body under reconstruction, and the
//     indirect callee it reaches. Both are fixed by machine facts, not chosen:
//
//     * the body: ECX is dereferenced at 0x005ba0d0 before any write, three
//       receiver reads follow at 0x005ba0d0 and 0x005ba0e5, and the three
//       receiver-adjustor thunks that reach it (see the thunk note below) all
//       rewrite ECX and tail-jump, which is only meaningful for a
//       this-pointer-in-ECX convention. Its terminator is a bare `C3` with no
//       immediate and it reads no stack slot, so it takes no ordinary argument
//       and cleans nothing.
//     * the indirect callee: the body pushes one word (`6a 01` at 0x005ba0e9),
//       calls, and then executes only `XOR EAX,EAX` and `RET`. There is no POP
//       and no ADD ESP anywhere in the twelve instructions, so a caller-cleaned
//       callee would leak four bytes on every call and the RET at 0x005ba0ef
//       would pop that leaked word as if it were a return address. The callee
//       therefore owns the four bytes, which is the callee-cleaned half of
//       __thiscall / __stdcall. Which of the two it is cannot be settled from
//       here: the callee is reached through a vtable word and its own bytes are
//       not available to this package.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_005BA0D0_THISCALL __thiscall
#else
#define PKG_SWARM_W1_005BA0D0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_005ba0d0 {

using Word = std::uint32_t;

// The receiver displacements this body was seen reaching, and the immediates and
// displacements its own encodings carry, stated as values BEFORE the types so the
// layout assertions below can be written against them.
//
//   kReceiverSubobjectDisplacement  0x005ba0d3 is `83 c1 14` -- ADD ECX,0x14.
//                                   From then on ECX is receiver+0x14, so this is
//                                   both where the load at 0x005ba0e5 reads and
//                                   what the callee at 0x005ba0eb receives as its
//                                   receiver.
//   kReceiverCounterDisplacement    0x005ba0d0 is `8b 41 18` and 0x005ba0d9 is
//                                   `89 41 04` with ECX already at receiver+0x14,
//                                   so 0x18 is read and written. It is the same
//                                   word twice: 0x14 + 4 == 0x18.
//   kDecrementImmediate             0x005ba0d6 is `83 c0 ff` -- a sign extended
//                                   one byte add, so the immediate is 0xffffffff
//                                   and the arithmetic wraps on a 32-bit
//                                   register. It is written as an add of
//                                   0xffffffff rather than as a subtraction so
//                                   the model's expression carries the same
//                                   immediate the instruction does.
//   kRestoreValue                   0x005ba0de is `c7 41 04 01 00 00 00` -- MOV
//                                   DWORD PTR [ECX+4],0x1. The stored value is
//                                   the literal 1, not the saved pre-decrement
//                                   value and not zero.
//   kDispatchArgument               0x005ba0e9 is `6a 01` -- PUSH 0x1, a sign
//                                   extended one byte immediate, so the argument
//                                   is 1.
//   kDispatchSlot                   0x005ba0e7 is `8b 10` -- MOV EDX,[EAX], i.e.
//                                   offset 0x00 of the table. Slot 0 is the only
//                                   slot this body can name.
constexpr std::size_t kReceiverSubobjectDisplacement = 0x14;
constexpr std::size_t kReceiverCounterDisplacement = 0x18;
constexpr std::size_t kSubobjectShift = 0x14;
constexpr Word kDecrementImmediate = 0xffffffffu;
constexpr Word kRestoreValue = 0x1u;
constexpr Word kDispatchArgument = 0x1u;
constexpr std::size_t kDispatchSlot = 0x00;

// The embedded polymorphic subobject at receiver+0x14. Declared before the
// receiver because the receiver embeds it by value.
struct alignas(4) DispatchSubobject {
  // +0x00 == receiver+0x14. Loaded at 0x005ba0e5 (`8b 01`) and dereferenced once
  // more at 0x005ba0e7 (`8b 10`), so the CALL at 0x005ba0eb is a TWO-LEVEL
  // dispatch: read the vtable word, then read slot 0 of the table it points at.
  // The constructor at 0x005ac99c writes 0x013f76c4 here, which is what
  // corroborates that the word is a vtable pointer and not a pointer to an
  // object. A model that stops at one level, or that reads a neighbour
  // displacement, is refuted by cases N5, N6 and N7 in the package's own model
  // test.
  void** vtable;

  // +0x04 == receiver+0x18. The SAME word as the receiver's +0x18 -- this is one
  // 4-byte word at one address with two names for its offset, and it is
  // deliberately NOT declared twice: a second member at the receiver's +0x18
  // would either nest wrongly or silently alias, and both would misdescribe the
  // twelve instructions. The body reads it at 0x005ba0d0, decrements it at
  // 0x005ba0d9 and restores it to 1 at 0x005ba0de. It is WRITTEN TO, never
  // written through, so the receiver record's written_through 0 holds for it.
  //
  // A word, not a named counter: the listing says only "a 32-bit word that is
  // decremented, and set back to 1 when the decrement reaches zero". Timer,
  // cooldown, refcount and depth counter are all stories this body does not tell.
  Word word_04;
};
static_assert(sizeof(DispatchSubobject) == 8,
              "0x14 + 8 == 0x1c: the two words this body can see end the subobject");
static_assert(offsetof(DispatchSubobject, vtable) == 0x00,
              "the vtable word is the subobject's own +0x00");
static_assert(offsetof(DispatchSubobject, word_04) == 0x04,
              "the rewritten word is the subobject's own +0x04");
static_assert(kReceiverSubobjectDisplacement + offsetof(DispatchSubobject, word_04) ==
                  kReceiverCounterDisplacement,
              "the subobject's +0x04 word IS the receiver's +0x18 word");

// Slot 0 of the subobject's vtable: receiver in ECX, one stack word, callee
// cleans four bytes. `void` because the caller zeroes EAX immediately after the
// call (0x005ba0ed) and never reads what came back -- that is a statement about
// this body, not about the callee, which is not this package's to describe.
using DispatchSlot0 = void(PKG_SWARM_W1_005BA0D0_THISCALL*)(DispatchSubobject*,
                                                             Word);

// The receiver. Two words are named because two words are reached, and the
// opaque head is 0x14 bytes because the first displacement this body touches is
// at 0x14. Nothing in the twelve instructions reads or writes +0x00, so no
// dispatch word is named there even though the constructor at 0x005ac996 writes
// one: a member this body never touches is a claim the body does not support.
struct alignas(4) Swarm005ba0d0Receiver {
  std::uint8_t opaque_00_13[0x14];  // 0x00..0x13, untouched by this body
  DispatchSubobject field_14;       // 0x14..0x1b, the embedded subobject
};
static_assert(offsetof(Swarm005ba0d0Receiver, field_14) == 0x14,
              "the subobject word is the receiver's +0x14");
static_assert(sizeof(Swarm005ba0d0Receiver) == 0x1c,
              "0x18 + 4 is the last byte this body writes on the receiver");
static_assert(kReceiverCounterDisplacement + sizeof(Word) ==
                  sizeof(Swarm005ba0d0Receiver),
              "the rewritten word ends the modelled receiver");
static_assert(sizeof(void**) == 4, "the vtable word is 32-bit");
static_assert(sizeof(DispatchSlot0) == 4, "the slot-0 pointer is 32-bit");

// The only way the body under reconstruction touches the receiver: two
// displacements into a byte run. A member access would assert an identity the
// twelve instructions do not carry, so word_at() is what the model uses.
inline std::uint32_t* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                         displacement);
}

inline const std::uint32_t* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// -- the indirect callee ------------------------------------------------------
// Declared here and NOT defined here: the package's own model test defines it as
// an observer. The machine reaches it as the vtable word at receiver+0x14 and
// then its slot 0, so the test installs the address of this function in a vtable
// of its own and the model calls through the pointer, exactly as `ff d2` does.
//
// The name carries the CALL SITE, not a class and not a role. Nothing in this
// image names it: SporeApp.exe has no MSVC RTTI, the callee is only ever reached
// through a vtable word, and the class of the object at receiver+0x14 is not
// established by anything in this package.
extern "C" void PKG_SWARM_W1_005BA0D0_THISCALL dispatch_slot0_005ba0eb(
    DispatchSubobject* subobject, Word argument);

// -- model instrumentation ---------------------------------------------------
// The two 4-byte STORES the body makes to the same address, in the order it makes
// them. Both encodings are visible in the listing -- `89 41 04` at 0x005ba0d9 and
// `c7 41 04 01 00 00 00` at 0x005ba0de -- and they are two separate instructions
// writing two separate values, so a reconstruction that writes only one, or
// writes them the other way round, is a different machine. But the FIRST of the
// two is invisible to every observer: the window between 0x005ba0d9 and 0x005ba0de
// contains no call, no branch target and no exit, so nothing outside the body can
// sample the transient 0.
//
// Rather than pretend otherwise, the model records the two stores in a
// file-scope log so the test can assert the count, the values and their order.
// This is instrumentation, NOT a machine global: nothing in the twelve
// instructions names a global address (abi_derived.globals is empty and the
// body has no absolute operand outside itself), and this log is declared in the
// header only so the test can reach it.
struct ReceiverWriteLog {
  std::uint32_t count;   // 1 on the early-out path, 2 when the body dispatches
  std::uint32_t first;   // the value of the `mov DWORD PTR [ecx+4],eax` store
  std::uint32_t second;  // the value of the `mov DWORD PTR [ecx+4],0x1` store
};
ReceiverWriteLog receiver_write_log();

// FUN_005ba0d0 @ 0x005ba0d0.
//
// __thiscall, receiver in ECX, NO ordinary stack arguments, bare `RET`. The
// argument count is not a guess: the twelve instructions contain no `[esp+...]`
// operand at all, so the body reads no argument slot, and the terminator is
// `c3` with no immediate, so it pops nothing but the return address. Ghidra's own
// record agrees on the count (ghidra_function.parameter_count 0, signature
// "undefined FUN_005ba0d0(void)") and reports no calling convention, which is
// why the convention here is INFERRED from the ECX reads and the thunks rather
// than taken from the prototype.
//
// Return type is a 32-bit word, and the two paths leave two different words in
// EAX:
//
//   * early-out (0x005ba0dc JNZ taken, 0x005ba0ef RET): EAX is the decremented
//     value, i.e. the receiver's +0x18 as it now stands. The JNZ has already
//     proved it is non-zero.
//   * dispatch (0x005ba0de..0x005ba0ed): EAX is zeroed by `33 c0`, and it is
//     zeroed AFTER the call, so the callee's return value is discarded and 0 is
//     returned even though the receiver's +0x18 now holds 1. The returned 0 is
//     NOT the field's value.
//
// Nothing in this image shows a caller consuming EAX -- the three non-vtable
// references are thunks, not call sites -- so whether EAX is an intended result
// or a dead register is unresolved. What the listing fixes is the value on each
// path, and that is what is declared and modelled.
extern "C" Word PKG_SWARM_W1_005BA0D0_THISCALL re_005ba0d0(
    Swarm005ba0d0Receiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_005ba0d0
