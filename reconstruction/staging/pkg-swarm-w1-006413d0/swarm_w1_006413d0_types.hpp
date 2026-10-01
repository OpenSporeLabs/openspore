// PKG-SWARM-W1-006413D0 -- VA 0x006413d0
// FUN_006413d0 (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000,
// sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for the 43-byte, three-transfer wrapper at
// 0x006413d0. Target subsystem Sporepedia (cluster sporepedia-online).
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because for this
// body the split is unusually clean:
//
//  * The three dispatch displacements 0xa4, 0xa8 and 0xac are read directly out
//    of the body's own instruction bytes: 0x006413d5 `8B 90 A4 00 00 00`,
//    0x006413e1 `8B 90 A8 00 00 00`, 0x006413ed `8B 90 AC 00 00 00`. They are
//    dword displacements of the form [EAX + imm32] on the value just loaded from
//    the receiver, so they index a 4-byte-stride table. Nothing else in the body
//    names an offset.
//
//  * The receiver displacement 0x00 is likewise the body's own: 0x006413d3
//    `8B 06` (MOV EAX,[ESI]) with ESI = ECX from 0x006413d1. The
//    machine-derived receiver record for this VA carries offsets=[0], register
//    ECX, shape R-ALIAS, written_through 0, present false for a slot-0 write --
//    it agrees that the only receiver word reached is the leading one and that
//    the body never writes through it.
//
//  * The minimum table size 0xb0 is arithmetic on the largest displacement, not a
//    measurement of a table: 0xac + 4. It is the only bound this body puts on the
//    table's extent, and it is a bound and not a size.
//
//  * No slot is NAMED. sdk_name is null, the pack's types list for this VA is
//    empty, and the eight vtable records the target carries
//    (0x013ff648, 0x01462764, 0x0147c9e8, 0x0147ca30, 0x0147caf8, 0x0147cbbc,
//    0x01489090, 0x014893b0) place this body at five DIFFERENT slot displacements
//    within their tables (+0x50, +0x44, +0x60, +0xe0, +0x108), so there is no
//    single index and therefore no way to read an SDK method ordinal off it. The
//    three callees are addressed by the displacements the body uses and by
//    nothing else.
//
//  * The receiver's total size is NOT fixed by this body. It reads exactly one
//    word, at +0x00. The struct below is 0x10 bytes so the model test has room to
//    plant decoys at +0x04..+0x0f; the 0x10 is a model choice with a hard LOWER
//    bound of 0x04 and no upper bound, and the bytes past the dispatch word are
//    declared opaque precisely because nothing here reads or writes them.
//
//  * The per-class target addresses are NOT constants of this body. Reading the
//    table at 0x013ff648 gives 0x00641cd0 / 0x00641e10 / 0x00641e40 at +0xa4 /
//    +0xa8 / +0xac; the other seven recorded tables give nine further different
//    values (0x00642230, 0x00642530, 0x00b5d860, 0x00641890, 0x00b7e380,
//    0x00641fd0, 0x00e31100, 0x00dd0a00, 0x00dd0ac0, 0x004535b0, 0x00c6a960,
//    0x007b86e0, 0x00ec3bc0, 0x00ecc550, 0x00dd0550). So the model dispatches
//    through the receiver's own table and never through a fixed address, and the
//    three externs at the bottom are seams the package's own model test fills,
//    not the callees of a real object.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-006413d0 requires an x86-32 target"
#endif

// The three transfers in this body are register-indirect (`FF D2`, CALL EDX) and
// each of them hands the receiver back in ECX, so all three are __thiscall. Two of
// them are additionally handed exactly one stack word and one is handed none.
//
// The conventions are fixed twice over. First by this body's own bytes: PUSH 0x0
// precedes the CALL at 0x006413dd and the CALL at 0x006413f7 and nothing is pushed
// before the CALL at 0x006413e9, and the body never adjusts ESP except the PUSH
// ESI / POP ESI pair, so the callees must consume their own argument words or the
// POP ESI at 0x006413f9 would pop a zero instead of ESI. Second, independently, by
// the terminators of the three concrete targets in the table at 0x013ff648:
// 0x00641cd0 ends `83 C4 10 / C2 04 00` (ADD ESP,0x10; RET 4) -- one word, callee
// cleaned; 0x00641e10 ends `FF 83 C4 08 / 5F 5E C3` (POP EDI; POP ESI; RET) -- no
// word at all; 0x00641e40 ends `5B 83 C4 14 / C2 04 00` (POP EBX; ADD ESP,0x14;
// RET 4) -- one word, callee cleaned. The three terminators agree with the three
// call sites one for one, and the middle one is the only one of the three that
// does not pop.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_006413D0_THISCALL __thiscall
#define PKG_SWARM_W1_006413D0_CDECL __cdecl
#else
#define PKG_SWARM_W1_006413D0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_006413D0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_006413d0 {

using Word = std::uint32_t;

// The tag keyword is `struct` here, at the definition below and at every use,
// because the definition is an `alignas(4)` aggregate like its sibling
// SporepediaReceiver. A `class` forward declaration against a `struct` definition
// is legal C++ but -Wmismatched-tags promotes it to an error inside -Werror, and
// under the Microsoft C++ ABI it changes linkage. One keyword, one meaning: the
// leading dispatch word's 4-byte-stride table of 0xb0 bytes.
struct DispatchTable;

// The receiver. One named member, at the one displacement the body reads; the
// rest is an opaque run. See the honesty note at the head of this file for why the
// size is a model choice and not a measurement.
struct alignas(4) SporepediaReceiver {
  DispatchTable* field_00;                             // 0x00, read three times
  std::array<std::uint8_t, 0x0c> opaque_04_0f{};      // 0x04..0x0f, untouched
};
static_assert(sizeof(SporepediaReceiver) == 0x10,
              "0x00 is the only receiver displacement this body reaches");

// The object the leading word points at: a 4-byte-stride table of code addresses.
// Only three of its words are ever read by this body, and which three is fixed by
// the displacements below. 0xb0 bytes is the minimum that can hold them.
struct alignas(4) DispatchTable {
  std::array<Word, 0xb0 / 4> slot;  // 0x00..0xaf; 0xa4/0xa8/0xac are the read ones
};
static_assert(sizeof(DispatchTable) == 0xb0,
              "0xac + 4 is the smallest table that can hold the third target");

// The three displacements, as values. 0xa4, 0xa8 and 0xac are the imm32 of the
// three `MOV EDX,[EAX+imm32]` instructions at 0x006413d5, 0x006413e1 and
// 0x006413ed; the fourth is arithmetic on the largest of them.
constexpr std::size_t kDispatchWordDisplacement = 0x00;  // 0x006413d3 `8B 06`
constexpr std::size_t kSlotFirstDisplacement = 0xa4;     // 0x006413d5
constexpr std::size_t kSlotSecondDisplacement = 0xa8;    // 0x006413e1
constexpr std::size_t kSlotThirdDisplacement = 0xac;     // 0x006413ed
constexpr std::size_t kMinimumTableBytes = 0xb0;         // 0xac + 4

// The three target signatures. The first and the third take one stack word (the
// literal 0 the body pushes) and the second takes none; see the macro block above
// for the terminators that fix this. All three return a 32-bit word, which is a
// MODEL CHOICE and not a claim: the body reads the return of the third one (it is
// what EAX holds at the RET) and discards the other two, so the return types of the
// first and the second are unobservable here and the third one's is only observable
// as "a dword reaches EAX". A void return on any of the three would be
// indistinguishable at this call site for the first two; for the third it would
// only mean the EAX the body leaves behind is dead. See unresolved_questions in the
// package sidecar.
using SlotTargetFirst =
    Word(PKG_SWARM_W1_006413D0_THISCALL*)(SporepediaReceiver*, Word);
using SlotTargetSecond = Word(PKG_SWARM_W1_006413D0_THISCALL*)(SporepediaReceiver*);
using SlotTargetThird =
    Word(PKG_SWARM_W1_006413D0_THISCALL*)(SporepediaReceiver*, Word);

// The single accessor the model uses to take a word out of a table. A member access
// would assert an identity the machine record does not carry; a displacement is
// what the instruction is.
inline Word* word_at(DispatchTable* table, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uint8_t*>(table) +
                                 displacement);
}
inline const Word* word_at(const DispatchTable* table, std::size_t displacement) {
  return reinterpret_cast<const Word*>(
      reinterpret_cast<const std::uint8_t*>(table) + displacement);
}

// A fresh read of the receiver's leading word. Called once per transfer, at the
// address of the body's own `8B 06`, because the body RE-READS it: 0x006413d3,
// 0x006413df and 0x006413eb are three separate loads of the same word. A model that
// cached the table pointer in a local would be a different machine, and the package
// model test drives a first-transfer callee that overwrites the receiver's leading
// word to prove the second and third transfers follow the new value.
inline DispatchTable* load_dispatch_table(SporepediaReceiver* receiver) {
  return receiver->field_00;
}

// Turning a table word back into a callable. The machine does this by loading the
// word into EDX and executing `FF D2`; the model copies the 4 bytes into a function
// pointer rather than casting, because a reinterpret_cast between two different
// function pointer types is diagnosed by -Wextra and because a byte copy is what
// the instruction does.
template <typename Target>
inline Target target_from_word(Word word) {
  static_assert(sizeof(Target) == sizeof(Word),
                "x86-32 function pointers are 4 bytes, like the table word");
  Target target;
  std::memcpy(&target, &word, sizeof target);
  return target;
}

static_assert(kSlotFirstDisplacement + 4 <= sizeof(DispatchTable),
              "the first target word is inside the modelled table");
static_assert(kSlotSecondDisplacement + 4 <= sizeof(DispatchTable),
              "the second target word is inside the modelled table");
static_assert(kSlotThirdDisplacement + 4 == sizeof(DispatchTable),
              "the third target word is the last word of the modelled table");
static_assert(kDispatchWordDisplacement == 0u,
              "the receiver's dispatch word is the leading word");

// -- the three indirect call sites -------------------------------------------
// There is NO direct callee in this body: all three transfers are `FF D2`, the
// register-indirect CALL through EDX, and the machine record agrees
// (dispatch.indirect_calls 3, call_offsets [], vtable_shaped_loads 0 -- the last
// because the word it walks through is a plain dword load, with no stride the
// record could recognise). The three declarations below are therefore NOT callees
// of a real object: they are the seams the package's own model test fills, one per
// call site, so that the test can see every transfer with its arguments and can
// choose the table the transfers go through. None of them is defined in the .cpp.

extern "C" Word PKG_SWARM_W1_006413D0_THISCALL
sporepedia_virtual_slot_a4_006413d0(SporepediaReceiver* receiver, Word argument);

extern "C" Word PKG_SWARM_W1_006413D0_THISCALL
sporepedia_virtual_slot_a8_006413d0(SporepediaReceiver* receiver);

extern "C" Word PKG_SWARM_W1_006413D0_THISCALL
sporepedia_virtual_slot_ac_006413d0(SporepediaReceiver* receiver, Word argument);

// FUN_006413d0 @ 0x006413d0.
//
// __thiscall, receiver in ECX, NO ordinary stack arguments, bare RET (0x006413fa
// is `C3`, one byte, no immediate). So the caller owns the cleanup of an argument
// area that is empty, which is the same thing the machine record reports
// (stack_cleanup_bytes 0, side "caller", termination "RET"). The prologue is
// `PUSH ESI` / `MOV ESI,ECX` and the epilogue is `POP ESI` / `RET`: one saved
// register, no frame, no locals, and ESP balanced on entry and exit.
//
// Return type is Word. The bare RET rules out a hidden return pointer -- a function
// returning a non-trivial class by value would have to `RET 4` to drop it -- so
// whatever this function hands back travels in EAX. EAX is written exactly once
// after the last transfer, by the CALL at 0x006413f7, and nothing between that
// instruction and the RET touches it (0x006413f9 is POP ESI). The value the caller
// therefore receives is the return word of the transfer at slot 0xac, and the
// returns of the transfers at 0xa4 and 0xa8 are dead: they are never moved and
// never read.
extern "C" Word PKG_SWARM_W1_006413D0_THISCALL re_006413d0(
    SporepediaReceiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_006413d0
