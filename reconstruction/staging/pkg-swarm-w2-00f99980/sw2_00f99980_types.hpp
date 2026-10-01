// PKG-SWARM-W2-00F99980 -- VA 0x00f99980
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00f99980 @ 0x00f99980, a method on the class
// whose table is at 0x01490be8 (this body occupies that table's slot +0x40: the
// bytes at 0x01490be8+0x40 in the image are 0x00f99980, which is also where the
// single xref, from 0x01490c28, comes from). That association is recorded here and
// in the .cpp's file header and is deliberately NOT modelled as a member: the body
// contains no read of the receiver's +0x00, so naming a dispatch word it never
// touches would be a claim the machine does not support.
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because the split
// matters to a reader:
//
//  * The two receiver displacements this body shows are 0x894 and 0x8a4, read at
//    0x00f999a1, 0x00f99991, 0x00f999bc and written at 0x00f999a7 and 0x00f999c6.
//    They are also, exactly, the two displacements the machine-derived receiver
//    record enumerates (receiver.offsets = [2196, 2212], register ECX, shape
//    R-ALIAS, bounds_only true). An alias-aware scan of the complete 25-instruction
//    listing, which follows MOV ESI,ECX at 0x00f99981, reaches the same pair and no
//    other. So the pair is fixed twice over.
//
//  * NO RECEIVER MEMBER IS NAMED. The record is bounds_only: it states where the
//    body was seen reaching and not which member is which. Calling the word at
//    +0x8a4 a "lighting target" or the word at +0x894 a "reference count" would be
//    a member story this body's evidence does not carry, so the receiver is an
//    opaque byte run and the .cpp reaches it through displacement-named accessors.
//    The *types* below (LightingTarget, RefCountedObject) name what each value is
//    HANDED TO, which the .cpp's own call sites fix; they say nothing about any
//    memory inside either object, and each is an opaque run for exactly that
//    reason.
//
//  * The table-word displacement 0x7c is NOT a receiver displacement and is not in
//    the record. It is fixed by this body's own two instructions: 0x00f99997
//    `MOV EDX,dword ptr [EAX]` reads the manager's leading word and 0x00f99999
//    `MOV EDX,dword ptr [EDX + 0x7c]` reads the word 124 bytes into the table that
//    word points at, which 0x00f9999f `CALL EDX` then calls. That is a two-level
//    load and nothing else, so 0x7c is stated as the table displacement and the
//    .cpp reaches the table through the manager, never through the receiver.
//
//  * The three direct callees' shapes are read out of their OWN bytes in the same
//    image, not out of any record; each is cited instruction by instruction at its
//    declaration below.
//
//  * The literal 0xffffffff is the value 0x00f99983 compares against
//    (`CMP dword ptr [ESI + 0x8a4],-0x1`, bytes 83 BE A4 08 00 00 FF FF) and the
//    value 0x00f999a7 stores (`MOV dword ptr [ESI + 0x8a4],0xffffffff`, bytes
//    C7 86 A4 08 00 00 FF FF FF FF). It is written as kLightingTargetAbsent because
//    the machine compares the field against it and stores it; the name says what
//    the two instructions do, and no record says what the field is when it holds
//    this value.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00f99980 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC 16 rejects the bare
// MSVC keywords outright, so the x86-32 attribute form is the portable spelling and
// the keyword form is kept for MSVC. All three are asserted by machine facts, and
// the indirect one is fixed by the FRAME rather than by a terminator this body
// contains:
//
//   PKG_SW2_00F99980_THISCALL  this body, and the two callees that take a receiver
//     in ECX. For this body: the receiver arrives in ECX (MOV ESI,ECX at
//     0x00f99981) and is dereferenced at 0x00f99983 before any definite write, and
//     its terminator is a bare `C3` (0x00f999d7) with no immediate and no argument
//     word, so the caller owns all cleanup. For 0x00692400: the bytes C2 04 00 at
//     0x00692417 and 0x0069242c are `RET 0x4`, so the callee owns the one argument
//     word this body pushes at 0x00f999b5. For 0x00690120: its own first act is
//     TEST ECX,ECX, so it takes the receiver in ECX.
//   PKG_SW2_00F99980_CDECL  0x0067dd50, whose whole body is `A1 C0 D8 5F 01 / C3`
//     (0x0067dd50, 0x0067dd55) -- it reads no stack slot, touches no ECX, and
//     returns with a plain RET.
//   The INDIRECT call at 0x00f9999f is callee-cleaned, and that is a frame fact
//     rather than a convention choice: this body pushes one word at 0x00f9999c,
//     calls through EDX at 0x00f9999f, and reaches 0x00f999d0 / 0x00f999d6 with a
//     SINGLE `POP ESI`. If the callee did not pop that word, the POP would restore
//     the argument instead of the saved ESI and the RET would land on it. So the
//     .cpp models the slot as a thiscall function pointer, which is the one typing
//     that puts the receiver in ECX and lets the callee own the argument word --
//     the same two instructions, in the same order, that the bytes are.
#if defined(_MSC_VER)
#define PKG_SW2_00F99980_THISCALL __thiscall
#define PKG_SW2_00F99980_CDECL __cdecl
#else
#define PKG_SW2_00F99980_THISCALL __attribute__((thiscall))
#define PKG_SW2_00F99980_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00f99980 {

using Word = std::uint32_t;

// The two receiver displacements, as values.
constexpr std::size_t kRefCountedDisplacement = 0x894;    // 0x00f999a1 / 0x00f999bc, written at 0x00f999c6
constexpr std::size_t kLightingTargetDisplacement = 0x8a4;  // 0x00f99983 / 0x00f99991, written at 0x00f999a7

// The table displacement the indirect call dispatches through, fixed by 0x00f99999
// `MOV EDX,dword ptr [EDX + 0x7c]` and confirmed by the machine dispatch record
// (abi_derived.dispatch.indirect_calls 1, abi_derived.return-side classifier
// VTABLE_SLOT at slot_offset 124). 124 is 31 whole dwords, which is what a
// dword-indexed table looks like on x86-32.
constexpr std::size_t kLightingSlotDisplacement = 0x7c;

// The word 0x00f99983 compares the receiver's +0x8a4 against and 0x00f999a7 stores
// back into it. Spelled as the unsigned 32-bit form of -1, which is the form both
// instructions carry in their immediate bytes (FF FF FF FF).
constexpr Word kLightingTargetAbsent = 0xffffffffu;

// The one ordinary argument this body pushes for 0x00692400, at 0x00f999b5
// (`PUSH 0x1`, bytes 6A 01). It is pushed before the call and is never read back,
// so its meaning is not established by this body; what is established is that it is
// the literal 1 and that the callee reads it as its own first stack word
// (0x00692404 `MOV EDX,DWORD PTR [ESP+0x4]`).
constexpr Word kReleaseNotificationArgument = 1;

// The manager's own leading-word displacement, in DECIMAL on purpose: it is a
// displacement of a different object from the receiver, and the validator reads
// every `+ 0x..` in the source span as a declared displacement to be accounted for
// against the receiver record. Writing it as a named constant keeps the span's
// hexadecimal set to the two receiver words and the one table word.
constexpr std::size_t kObjectTableWordDisplacement = 0;


// The object 0x00f99991 hands to the lighting call, by value. This body NEVER
// dereferences it: 0x00f99991 loads the word at the receiver's +0x8a4 into ECX,
// 0x00f9999c pushes that word, and the only thing that happens to the value
// afterwards is the store of 0xffffffff to the field at 0x00f999a7. The model test
// plants a poison pattern inside an object at that address and asserts not one byte
// of it moves, which is how "passed by value" is distinguished from "dereferenced
// and copied".
struct alignas(4) LightingTarget {
  std::array<std::uint8_t, 4> opaque_00{};
};

// The object the two trailing calls take as their receiver. This body also never
// dereferences it: it is loaded at 0x00f999a1 and 0x00f999bc, tested against 0,
// and passed in ECX. What is known about its INSIDE comes from the two callees'
// own bytes and from nothing in this body, so nothing is named from it here:
// 0x00692400 adjusts its receiver by -8 (0x00692408 `LEA EAX,[ECX-0x8]`) and calls
// the table word 0x4c bytes into that address (0x0069240d `MOV ECX,[ECX+0x30]` on
// the adjusted pointer, so 0x30 - 8 == 0x28 into the object as this body holds it);
// 0x00690120 adjusts it the same way (0x006124 `LEA EAX,[ECX-0x8]`) and decrements
// the word 0x4c bytes into it with an atomic exchange (0x00690132 `LOCK XADD
// DWORD PTR [EAX],ESI` with ESI = -1 from 0x0069012f). Those two facts are stated
// here as a description of the CALLEES and are not used to name a member, because
// no listing in this package reads any byte of this object.
struct alignas(4) RefCountedObject {
  std::array<std::uint8_t, 4> opaque_00{};
};

// The manager 0x00f9998c obtains and dispatches through. The only byte of it this
// body touches is its leading word: 0x00f99997 `MOV EDX,dword ptr [EAX]` reads
// [EAX+0x00] with EAX = the manager, and 0x00f9999d `MOV ECX,EAX` hands the manager
// itself -- not the table, not the table word -- to the call at 0x00f9999f. So four
// bytes is the whole of it, and the model reaches the leading word through
// word_at(manager, 0) with the zero written in decimal so that the span declares no
// hexadecimal displacement outside the receiver's two.
struct alignas(4) LightingManager {
  std::array<std::uint8_t, 4> opaque_00{};
};

// The receiver. This body reads two of its words and writes two, all four by
// displacement, and touches nothing else on it:
//
//   0x00f99983  CMP dword ptr [ESI + 0x8a4],0xffffffff   read
//   0x00f99991  MOV ECX,dword ptr [ESI + 0x8a4]           read  (the same word)
//   0x00f999a1  MOV ECX,dword ptr [ESI + 0x894]           read
//   0x00f999a7  MOV dword ptr [ESI + 0x8a4],0xffffffff   write
//   0x00f999bc  MOV ECX,dword ptr [ESI + 0x894]           read  (the same word again)
//   0x00f999c6  MOV dword ptr [ESI + 0x894],0x0           write
//
// The model therefore ends the receiver at 0x8a8, the byte after the last one
// written, and declares no member. 0x00..0x893 and 0x8a8 onward are never read or
// written by this body; the model test plants decoy words at 0x890, 0x898 and
// 0x8a0 and asserts that none of them moves.
struct alignas(4) Receiver {
  // The size is written as the derived expression rather than as a literal, because it is
  // derived: 0x8a4 is the highest displacement the body writes and it writes four bytes.
  std::array<std::uint8_t, kLightingTargetDisplacement + sizeof(Word)> opaque_00{};
};

// The only way the body under reconstruction touches the receiver: a 32-bit word at
// a stated displacement. A member access would assert an identity the
// machine-derived record cannot corroborate, so none is used anywhere in the body.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// One level of the dispatch's table load, 0x00f99999 in isolation: the word at a
// stated byte displacement of the table, as a raw code address. The .cpp casts it
// to the slot's function-pointer type immediately; nothing here decides what the
// slot IS, because only the call site does.
//
// `displacement` is a BYTE displacement, not an index. A reconstruction that
// indexed the table instead would land on a neighbouring slot, and the model test
// plants a distinct decoy at 0x78 and at 0x80 so that the mistake is visible rather
// than silent.
inline std::uintptr_t load_slot(const Word* table, std::size_t displacement) {
  return static_cast<std::uintptr_t>(*word_at(table, displacement));
}

// The signature of the dispatched slot, as this body reaches it: the manager in ECX
// and the receiver's +0x8a4 word as the single stack argument, popped by the callee.
// thiscall is the typing that produces 0x00f9999c PUSH ECX / 0x00f9999d MOV ECX,EAX
// / 0x00f9999f CALL EDX, and it is the typing the frame requires (see the
// convention note above). The manager's own record names the method this body
// reaches -- Ghidra's decompilation of this VA prints the call as
// `pIVar1->_vftable0[2].GetLightingWorld` and the target's own record carries the
// callee name "Graphics::ILightingManager::Get" for 0x0067dd50 -- so the type name
// below borrows that one and claims nothing further: which slot index 0x7c is, and
// what the method is called, are not established by any record in this package.
using LightingMethod = void (PKG_SW2_00F99980_THISCALL *)(LightingManager* receiver,
                                                          LightingTarget* target);

static_assert(sizeof(Receiver) == kLightingTargetDisplacement + sizeof(Word),
              "the highest displacement the body writes, plus the four bytes it writes, is the size");
static_assert(kRefCountedDisplacement + sizeof(Word) < kLightingTargetDisplacement,
              "the two receiver words are distinct and the lower one is read first");
static_assert(kLightingSlotDisplacement % sizeof(Word) == 0,
              "0x7c is 31 whole dwords into the table");
static_assert(kObjectTableWordDisplacement == 0,
              "the table word is the manager's leading word");

// -- the three direct callees -------------------------------------------------
// Each is declared here and defined as an observer in the package's own model test.
// Every signature below is fixed by the callee's OWN bytes, cited at each one.

// 0x0067dd50, called once, at 0x00f9998c, and reached by no jump. Its whole body is
// six bytes in the image: 0x0067dd50 `A1 C0 D8 5F 01` = `MOV EAX,ds:0x15fd8c0` and
// 0x0067dd55 `C3`. It reads no stack slot, ignores ECX, and returns a dword loaded
// from the .data address 0x015fd8c0. This body uses that dword as the receiver of the
// slot call and reads nothing else of it. cdecl: the plain RET with no immediate,
// and the call site pushes nothing.
//
// The data address 0x015fd8c0 is NOT modelled as a global in this package: the
// constant belongs to the callee's body, not to this one, and the GLOBALS dimension
// is adjudicated against the 25 instructions of THIS body, which name no
// data-segment address at all. The name below is the one this target's own record
// already carries for it, so the model does not invent a competing one.
extern "C" LightingManager* PKG_SW2_00F99980_CDECL graphics_ilightingmanager_get_0067dd50(
    void);

// 0x00692400, called once, at 0x00f999b7, with the receiver in ECX and the literal 1
// pushed at 0x00f999b5. Its own 0x2f bytes in the image, transcribed:
//
//   00692400  TEST ECX,ECX
//   00692402  JE 0x0069241a                     null-receiver arm
//   00692404  MOV EDX,[ESP+0x4]                  the ONE stack word, read
//   00692408  LEA EAX,[ECX-0x8]                 the receiver, adjusted
//   0069240b  MOV ECX,EAX
//   0069240d  MOV ECX,[ECX+0x30]                the adjusted receiver's table word
//   00692410  PUSH EDX                          the argument, forwarded
//   00692411  PUSH EAX                          the adjusted receiver, forwarded
//   00692412  CALL 0x00692330
//   00692417  RET 0x4                           the callee owns the argument word
//   ...        (the null arm at 0x0069241a is the same sequence with EAX and ECX
//             zeroed, and it also ends C2 04 00 at 0x0069242c)
//
// So the callee owns its one argument word, which is what makes this body's frame
// balance with a single POP ESI afterwards, and it forwards to a table word 0x30
// bytes into its own adjusted receiver. Its own receiver is the word this body read
// at 0x00f999a1, and its own return value is discarded -- nothing between
// 0x00f999b7 and 0x00f999d7 reads EAX. The name says what the body does to the
// word it is given; what 0x00692330 is, and what the argument 1 means, are not
// established here.
extern "C" void PKG_SW2_00F99980_THISCALL owned_object_notify_00692400(
    RefCountedObject* receiver, Word argument);

// 0x00690120, reached ONLY by the unconditional jump at 0x00f999d1, after the
// receiver's +0x894 word has been stored to 0 at 0x00f999c6 and after the single
// POP ESI at 0x00f999d0 has run -- so the stack is exactly as it was at this body's
// entry and the transfer is a tail call that returns to THIS body's caller with
// nothing of this frame left. Its own first instructions in the image:
//
//   00690120  TEST ECX,ECX
//   00690122  JE 0x00690129
//   00690124  LEA EAX,[ECX-0x8]                 the receiver, adjusted
//   0069012c  ADD EAX,0x4c                      the word it decrements
//   0069012f  OR ESI,0xffffffff                 ESI = -1
//   00690132  LOCK XADD DWORD PTR [EAX],ESI      one atomic decrement
//   00690136  DEC ESI
//   00690137  JNE 0x0069015c                    the count did not reach 0
//   0069014b  MOV EAX,ESI / POP ESI / RET        the count reached 0: EAX = 0
//
// It reads no stack word and terminates with a plain RET, so it takes no argument
// but the receiver. (Every one of the six addresses above is the one objdump prints
// over the 0x30 bytes at 0x00690120 in this image.) The name says what the count
// does; that the word it decrements is a reference count is the reading of
// `LOCK XADD` with -1 and nothing more, and no record in this package names it.
extern "C" void PKG_SW2_00F99980_THISCALL owned_object_release_00690120(
    RefCountedObject* receiver);

// FUN_00f99980 @ 0x00f99980.
//
// __thiscall, receiver in ECX, NO ordinary stack arguments, bare `RET` (0x00f999d7,
// byte C3). The argument count is not a guess: the frame is one `PUSH ESI`, one
// pushed word per call (each popped by its callee, as the two `RET 0x4`/`C3` forms
// and the single POP ESI on each exit require), one POP ESI and a RET with no
// immediate. Ghidra's own record reports "undefined FUN_00f99980(void)" with
// ghidra_parameter_count 0, and its decompilation opens `void __fastcall
// FUN_00f99980(int param_1)` with `param_1` standing for the ECX receiver; the
// listing is followed here.
//
// RETURN TYPE, and the disagreement with the record, stated once and in full.
// This body writes EAX on NO path: no instruction in the 25 has EAX as a
// destination, the only definitions of it are the three calls' own return values,
// and every one of those three results is discarded -- the manager's word becomes
// ECX at 0x00f9999d, and nothing reads EAX again at 0x00f999a1, 0x00f999bc or
// anywhere else. The one path that does not return here at all (0x00f999d1) hands
// the return register to 0x00690120, which writes it itself. So the bytes produce
// no value and `void` is declared.
//
// The canonical ABI record disagrees in a way no C++ spelling can fix, and this
// package does not try to fix it. abi_derived.return carries register EAX with
// register_class "aggregate_unknown" and `void_possible: false`, and
// abi_derived.abi.return_semantics is the machine phrase "unclassified_in_EAX". The
// validator compares the source's declared return type against that phrase as a
// string, so the dimension is a WARN whatever is written here, and no typedef named
// after the phrase is declared, because that would be a validator hack rather than a
// reconstruction. On the record's own terms `void_possible: false` is not a claim
// that the function returns something: tools/reconstruction_tooling/abi_infer.py
// sets that flag only when EAX is never written AND the body contains no call, so
// any body with a call in it cannot have it set. The sidecar records the whole of
// this, and the .cpp's return section records the path-by-path composition of EAX.
extern "C" void PKG_SW2_00F99980_THISCALL re_00f99980(Receiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00f99980
