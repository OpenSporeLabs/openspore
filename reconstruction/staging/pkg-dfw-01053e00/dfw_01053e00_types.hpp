// PKG-DFW-01053E00 -- VA 0x01053e00
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Opaque boundary types for the reconstruction of FUN_01053e00.
//
// Naming discipline for this file, and the reason it is worth stating: no record
// in reconstruction/evidence/01053e00/ names a member, a slot target or a
// dispatch table for this target, and the knowledge record's own
// unresolved_questions says so ("The semantic role of each dispatched slot is
// inferred from shape only"). So every name below is either
//   (a) one of the three type names the knowledge record itself carries --
//       OpaqueBeamTarget, OpaqueBeamToolState, bool -- or
//   (b) a name built out of the machine displacement that fixes it, and
//       nothing else.
// There is no name here that asserts what a word means. `word_124` is the word
// at displacement 0x124 because the listing reads displacement 0x124, not
// because any record says what sits there.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-01053e00 requires an x86-32 target"
#endif

// Calling conventions, spelled per toolchain. GCC and clang reject the MSVC
// keywords outright and only accept the __attribute__ form, so both spellings
// are kept. Which one the reconstructed entry point uses is argued in the .cpp
// and repeated in the sidecar; the short version is that the two terminators at
// 0x01053eca and 0x01053ed3 are `RET 0x8`, so the callee owns eight bytes of
// stack, and that is the stdcall shape on x86-32.
#if defined(_MSC_VER)
#define PKG_DFW_01053E00_THISCALL __thiscall
#define PKG_DFW_01053E00_STDCALL __stdcall
#define PKG_DFW_01053E00_CDECL __cdecl
#else
#define PKG_DFW_01053E00_THISCALL __attribute__((thiscall))
#define PKG_DFW_01053E00_STDCALL __attribute__((stdcall))
#define PKG_DFW_01053E00_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_dfw_01053e00 {

using Word = std::uint32_t;

// The three consecutive single-precision words this body copies about. The
// spelling is the instruction's: 0x01053e7f/0x01053e89/0x01053e94 are MOVSS, so
// each of offsets 0, 4 and 8 of the pointer EAX holds is one 32-bit
// single-precision value, and the body parks them at [ESP+0x4], [ESP+0x8] and
// [ESP+0xc]. No record says the three words are a coordinate triple; they are
// three words.
struct alignas(4) OpaqueSinglePrecisionTriple {
  float word_00;
  float word_04;
  float word_08;
};

// Objects this body reaches. The first two names are the knowledge record's own
// (`types: ["OpaqueBeamTarget", "OpaqueBeamToolState", "bool"]`); the rest are
// named for the displacement that reaches them and assert nothing further.
struct OpaqueWordAt34;
struct OpaqueWordAt114;
struct OpaqueFoundAt_b8;
struct OpaqueBeamTarget;

// Slot types, one per dispatch site, each carrying the displacement the listing
// reads the slot word at. The receiver is ECX at every one of the six sites and
// the machine pushes at most one stack word, so thiscall is the shape for all of
// them: first parameter in ECX, at most one callee-popped stack word.
//
// The three that return a pointer or a byte are typed that way only because the
// body consumes their return word: `TEST AL,AL` at 0x01053e19 and the three
// `MOV EAX`/`TEST EAX,EAX` pairs after the calls at 0x01053e5c, 0x01053e6e and
// 0x01053e7d. The return widths are the instruction widths, not a claim about
// what the callees mean.

// 0x01053e17  MOV EAX,[ECX] / MOV EDX,[EAX+0x2c] / CALL EDX, then TEST AL,AL.
using BeamTargetSlot2cFn = bool(PKG_DFW_01053E00_THISCALL*)(OpaqueBeamTarget*);

// 0x01053e36, from MOV EAX,[ECX] / MOV EDX,[EAX+0x4] / CALL EDX. Its return is
// never read: the next write to EAX is the LOAD of the gate compare at
// 0x01053e38, and the return paths at 0x01053eca/0x01053ed3 set AL explicitly.
using BeamTargetSlot04Fn = void(PKG_DFW_01053E00_THISCALL*)(OpaqueBeamTarget*);

// 0x01053e7d, from MOV EAX,[ECX] / MOV EDX,[EAX+0x2c] / CALL EDX on the object
// the receiver's word at 0x114 holds. EAX is consumed at 0x01053e7f.
using WordAt114Slot2cFn =
    const OpaqueSinglePrecisionTriple*(PKG_DFW_01053E00_THISCALL*)(OpaqueWordAt114*);

// 0x01053e5c, from MOV EAX,[ECX] / MOV EDX,[EAX+0xb8] / PUSH 0x13f94d4 /
// CALL EDX. EAX is tested against zero at 0x01053e5e.
using WordAt114Slotb8Fn =
    OpaqueFoundAt_b8*(PKG_DFW_01053E00_THISCALL*)(OpaqueWordAt114*, const Word*);

// 0x01053e6e, from MOV EDX,[EAX] / MOV EDX,[EDX+0x30] / LEA ECX,[ESP+0x10] /
// PUSH ECX / MOV ECX,EAX / CALL EDX. EAX is consumed at 0x01053e7f.
using FoundAtB8Slot30Fn = const OpaqueSinglePrecisionTriple*(
    PKG_DFW_01053E00_THISCALL*)(OpaqueFoundAt_b8*, OpaqueSinglePrecisionTriple*);

// 0x01053eb2, from LEA ECX,[EAX+0x34] / MOV EAX,[ECX] / MOV EAX,[EAX+0x38] /
// LEA EDX,[ESP+0x4] / PUSH EDX / CALL EAX. Its return is never read.
using WordAt34Slot38Fn =
    void(PKG_DFW_01053E00_THISCALL*)(OpaqueWordAt34*, const OpaqueSinglePrecisionTriple*);

// -- the tables ------------------------------------------------------------
//
// Every dispatch site is a two-level load: MOV EAX,[object] then
// MOV EDX,[EAX+disp]. So each object this body dispatches through begins with a
// table pointer at displacement 0, and the slot word sits at the displacement the
// listing names. The padding words are declared, not omitted, so the layout is
// pinned by static_assert rather than by arithmetic nobody can check.

struct alignas(4) OpaqueBeamTargetTable {
  Word word_00;                   // displacement 0x00
  BeamTargetSlot04Fn slot_04;     // displacement 0x04
  Word word_08;                   // displacement 0x08
  Word word_0c;                   // displacement 0x0c
  Word word_10;                   // displacement 0x10
  Word word_14;                   // displacement 0x14
  Word word_18;                   // displacement 0x18
  Word word_1c;                   // displacement 0x1c
  Word word_20;                   // displacement 0x20
  Word word_24;                   // displacement 0x24
  Word word_28;                   // displacement 0x28
  BeamTargetSlot2cFn slot_2c;     // displacement 0x2c
};

struct alignas(4) OpaqueWordAt114Table {
  Word word_00;  // displacement 0x00
  Word word_04;  // displacement 0x04
  Word word_08;  // displacement 0x08
  Word word_0c;  // displacement 0x0c
  Word word_10;  // displacement 0x10
  Word word_14;  // displacement 0x14
  Word word_18;  // displacement 0x18
  Word word_1c;  // displacement 0x1c
  Word word_20;  // displacement 0x20
  Word word_24;  // displacement 0x24
  Word word_28;  // displacement 0x28
  WordAt114Slot2cFn slot_2c;                 // displacement 0x2c
  Word slot_30[34];                          // displacements 0x30 .. 0xb4
  WordAt114Slotb8Fn slot_b8;                 // displacement 0xb8
};

struct alignas(4) OpaqueFoundAtB8Table {
  Word word_00;  // displacement 0x00
  Word word_04;  // displacement 0x04
  Word word_08;  // displacement 0x08
  Word word_0c;  // displacement 0x0c
  Word word_10;  // displacement 0x10
  Word word_14;  // displacement 0x14
  Word word_18;  // displacement 0x18
  Word word_1c;  // displacement 0x1c
  Word word_20;  // displacement 0x20
  Word word_24;  // displacement 0x24
  Word word_28;  // displacement 0x28
  Word word_2c;  // displacement 0x2c
  FoundAtB8Slot30Fn slot_30;  // displacement 0x30
};

struct alignas(4) OpaqueWordAt34Table {
  Word word_00;  // displacement 0x00
  Word word_04;  // displacement 0x04
  Word word_08;  // displacement 0x08
  Word word_0c;  // displacement 0x0c
  Word word_10;  // displacement 0x10
  Word word_14;  // displacement 0x14
  Word word_18;  // displacement 0x18
  Word word_1c;  // displacement 0x1c
  Word word_20;  // displacement 0x20
  Word word_24;  // displacement 0x24
  Word word_28;  // displacement 0x28
  Word word_2c;  // displacement 0x2c
  Word word_30;  // displacement 0x30
  Word word_34;  // displacement 0x34
  WordAt34Slot38Fn slot_38;  // displacement 0x38
};

// -- the objects ------------------------------------------------------------

// The object the receiver's word at displacement 0x124 holds. The body reaches
// exactly one word of it beyond the table pointer: the pointer at displacement
// 0x34, loaded at 0x01053e9f with LEA rather than read, and dereferenced at
// 0x01053ea8.
struct alignas(4) OpaqueBeamTarget {
  const OpaqueBeamTargetTable* table_00;  // displacement 0x00
  std::uint8_t opaque_004[0x34u - 0x04u];
  OpaqueWordAt34* word_34;  // displacement 0x34
};

// The object the receiver's word at displacement 0x114 holds. Reached at
// 0x01053e45 and dispatched through at 0x01053e5c and 0x01053e7d.
struct alignas(4) OpaqueWordAt114 {
  const OpaqueWordAt114Table* table_00;  // displacement 0x00
};

// The object the +0xb8 slot returns. Reached at 0x01053e62 and dispatched
// through at 0x01053e6e. What it is, is not established by any record.
struct alignas(4) OpaqueFoundAt_b8 {
  const OpaqueFoundAtB8Table* table_00;  // displacement 0x00
};

// The object the owned target's word at displacement 0x34 holds. Reached at
// 0x01053ea8 and dispatched through at 0x01053eb2.
struct alignas(4) OpaqueWordAt34 {
  const OpaqueWordAt34Table* table_00;  // displacement 0x00
};

// The receiver. This is the knowledge record's own type name, attached to the
// object the body reads its two words out of: 0x114 (0x01053e45, 0x01053e72) and
// 0x124 (0x01053e08, 0x01053e1d, 0x01053e27, 0x01053e38, 0x01053e99,
// 0x01053eb9). The model addresses it through raw displacements rather than
// through these members -- see the .cpp -- so the two spellings cannot drift
// apart silently; the static_asserts below pin the members to the same
// displacements the model writes as literals.
struct alignas(4) OpaqueBeamToolState {
  std::uint8_t opaque_000[0x114u];
  OpaqueWordAt114* word_114;  // displacement 0x114
  std::uint8_t opaque_118[0x124u - 0x118u];
  OpaqueBeamTarget* word_124;  // displacement 0x124
};

// 0x00cb5930, the body's one direct callee, at 0x01053ebf. The live
// decompilation of that address is `void __thiscall FUN_00cb5930(int param_1,
// undefined4 *param_2)`, and this body sets it up exactly that way: ECX is
// loaded from the receiver's word at 0x124 at 0x01053eb9 and the one stack word
// is pushed at 0x01053eb8 from [ESP+0x24]. What the callee does with the stack
// word is its own business and is not modelled here; that callee reads three
// words from it, and that is recorded in the sidecar rather than asserted here.
extern "C" void PKG_DFW_01053E00_THISCALL
dfw_commit_00cb5930(OpaqueBeamTarget* word_124_at_01053eb9, void* second_stack_word);

static_assert(sizeof(void*) == 4, "the target is x86-32 and its pointers are 4 bytes");
static_assert(sizeof(Word) == 4, "a machine word is 4 bytes");
static_assert(sizeof(float) == 4, "a MOVSS operand is a 32-bit single-precision word");
static_assert(sizeof(OpaqueSinglePrecisionTriple) == 0x10u - 0x04u,
              "three consecutive words, as [ESP+0x4]..[ESP+0xf] holds them");
static_assert(offsetof(OpaqueSinglePrecisionTriple, word_00) == 0x0u, "triple offset 0");
static_assert(offsetof(OpaqueSinglePrecisionTriple, word_04) == 0x4u, "triple offset 4");
static_assert(offsetof(OpaqueSinglePrecisionTriple, word_08) == 0x8u, "triple offset 8");

static_assert(offsetof(OpaqueBeamTargetTable, slot_04) == 0x04u,
              "the +0x04 slot the body dispatches at 0x01053e36");
static_assert(offsetof(OpaqueBeamTargetTable, slot_2c) == 0x2cu,
              "the +0x2c slot the body dispatches at 0x01053e17");
static_assert(offsetof(OpaqueWordAt114Table, slot_2c) == 0x2cu,
              "the +0x2c slot the body dispatches at 0x01053e7d");
static_assert(offsetof(OpaqueWordAt114Table, slot_b8) == 0xb8u,
              "the +0xb8 slot the body dispatches at 0x01053e5c");
static_assert(offsetof(OpaqueFoundAtB8Table, slot_30) == 0x30u,
              "the +0x30 slot the body dispatches at 0x01053e6e");
static_assert(offsetof(OpaqueWordAt34Table, slot_38) == 0x38u,
              "the +0x38 slot the body dispatches at 0x01053eb2");

static_assert(offsetof(OpaqueBeamTarget, word_34) == 0x34u,
              "the owned target's word at 0x34, reached by LEA at 0x01053e9f");
static_assert(offsetof(OpaqueBeamToolState, word_114) == 0x114u,
              "the receiver's word at 0x114, read at 0x01053e45 and 0x01053e72");
static_assert(offsetof(OpaqueBeamToolState, word_124) == 0x124u,
              "the receiver's word at 0x124, read and written seven times");

}  // namespace openspore::reconstruction::pkg_dfw_01053e00
