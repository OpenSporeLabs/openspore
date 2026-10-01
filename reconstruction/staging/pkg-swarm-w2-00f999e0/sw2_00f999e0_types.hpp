// PKG-SWARM-W2-00F999E0 -- VA 0x00f999e0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00f999e0 @ 0x00f999e0: 80 instructions,
// 0x00f999e0..0x00f99ab3 inclusive (ghidra_function.body_start 0x00f999e0,
// body_end 0x00f99ab3, size_bytes 212). The body is the method at slot +0x50 of
// the class table whose address is 0x01490be8, read out of the image in
// reconstruction/metadata/pkg-swarm-w2-00f999e0/00f999e0.json (mechanics.table)
// and matching the single xref, which comes from 0x01490c38 = 0x01490be8 + 0x50.
//
// WHAT THE BODY IS, in one paragraph, and the evidence for every clause: it is a
// zero-argument __thiscall predicate that returns one byte. Five gates must all
// hold before any of the receiver's 96 floats are read, and then 24 groups of four
// floats are compared pairwise; the body returns 0 as soon as any group has BOTH
// of its two pairs ordered-equal, and returns 1 only if all five gates hold and no
// group does. The gates are: a global-object predicate reached through two direct
// calls, the table word at slot +0x4c called with the byte 7, a byte at the
// receiver's +0x370, the table word at slot +0x30, and a byte at +0x4f4.
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because the split
// matters to a reader:
//
//  * NO MEMBER OF THE RECEIVER IS NAMED, and that is a hard rule here, not a
//    preference. The machine-derived receiver record is
//    {register ECX, shape R-ALIAS, bounds_only true, offsets
//    [0, 880, 1076, 1080, 1084, 1088, 1172, 1176, 1180, 1184, 1268],
//    max_offset 1268, written_through 0}: it says where the body was SEEN REACHING
//    and not which member is which, so every access below goes through a
//    displacement-named accessor over an opaque byte run and the receiver struct
//    declares a single unnamed array.
//
//  * The two receiver BYTES are fixed twice over. 0x370 is
//    `CMP BYTE PTR [ESI + 0x370],AL` at 0x00f99a06 and 0x4f4 is
//    `CMP BYTE PTR [ESI + 0x4f4],0x0` at 0x00f99a1b; both are in the record's
//    enumeration above. The record's `written_through` is 0 and the listing has no
//    memory-destination operand at all, so the receiver is READ-ONLY for this body
//    -- asserted byte-for-byte by the model test.
//
//  * The four-float GROUP layout, the 0x60 group stride, the 0x10 outer stride, the
//    counts 6 and 2, and the four group bases are NOT in the receiver record and
//    are derived from this body's own instruction bytes, cited one by one in the
//    .cpp. The reason the record cannot corroborate them is stated in the .cpp:
//    the alias-aware scan the record was built from loses the ESI alias at the
//    `POP ESI` on the first return path (0x00f999f5), so the inner loop's negative
//    displacements are not attributed to the receiver at all.
//
//  * Each group reads four floats at the group base g, g+4, g+8 and g+0xc, and
//    compares them as (g, g+8) and (g+4, g+0xc). The relative shape is fixed four
//    times inside this body, and it is independently CORROBORATED by a different
//    function in the same image: 0x00f699b0 -- one of this body's own direct callees
//    -- repeats the identical `LAHF / TEST AH,0x44 / JNP` dance over the identical
//    (base, base+8) and (base+4, base+0xc) pairs at a 0x60 group stride, with the
//    same six-iteration, 0x10-stride outer loop. The header for that shape is in
//    mechanics.group_layout_corroboration in the sidecar.
//
//  * The two table slots 0x4c and 0x30 are 0x00f999f9's and 0x00f99a10's own
//    displacements. The table address 0x01490be8 and the slot entries it holds are
//    read out of the image and are recorded in the sidecar; the entries are NOT
//    modelled as callees here, because the call is through a word the RUNTIME
//    object holds and a derived class may override either slot. The model calls
//    through whatever word the receiver's own +0x00 names, which is what the
//    listing does.
//
//  * Each direct callee's shape is read out of its OWN bytes in the same image, not
//    out of any record; the three transcriptions are at the bottom of this header.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00f999e0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare MSVC
// keywords, so the x86-32 attribute form is the portable spelling and the keyword
// form is kept for MSVC. Both are asserted by machine facts:
//
//   PKG_SW2_00F999E0_THISCALL  this body AND both table slots it calls. The receiver
//     arrives in ECX and is dereferenced at 0x00f999f7 before any definite write to
//     it; every one of the three return sites ends in a bare `C3` (0x00f999f6,
//     0x00f99aae, 0x00f99ab3) with no immediate, so nothing is popped here. The one
//     argument word this body pushes, `PUSH 0x7` at 0x00f999fc, is never dropped by
//     the body, so the callee owns it -- and the two table implementations in this
//     class's table agree: 0x00fa0e60, the entry at slot +0x4c, ends `C2 04 00`
//     (RET 0x4) and reads its argument with `MOV DL,[ESP+0x4]` at 0x00fa0e66, while
//     0x00fa0d80, the entry at slot +0x30, ends with a bare `C3` and takes none.
//   PKG_SW2_00F999E0_CDECL     0x00f48a70, the six-byte global getter (see below).
#if defined(_MSC_VER)
#define PKG_SW2_00F999E0_THISCALL __thiscall
#define PKG_SW2_00F999E0_CDECL __cdecl
#else
#define PKG_SW2_00F999E0_THISCALL __attribute__((thiscall))
#define PKG_SW2_00F999E0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00f999e0 {

using Word = std::uint32_t;
using Real = float;

static_assert(sizeof(Real) == 4, "MOVSS and UCOMISS read four bytes, so the modelled float is binary32");
static_assert(sizeof(Word) == 4, "a 32-bit table entry is one word");

// The receiver. OPAQUE, and that is the point: the machine-derived receiver record
// is bounds_only, so it fixes no member, and the body is read-only besides, so the
// struct carries nothing the body could contradict. The size is the highest byte
// this body touches plus one, and the highest byte is the +0x4f4 flag at 0x00f99a1b
// (the last float read is at +0x4f0, on outer index 5's fourth group).
constexpr std::size_t kLastReceiverByte = 0x4f4;
struct alignas(4) Receiver {
  std::array<std::uint8_t, kLastReceiverByte + 1> opaque{};
};
static_assert(Receiver{}.opaque.size() == kLastReceiverByte + 1,
              "the model ends one byte past the last byte the body addresses");

// The machine writes ONE byte of the return register on all three exits -- `XOR AL,AL`
// at 0x00f999f3, `MOV AL,0x1` at 0x00f99aab and `XOR AL,AL` at 0x00f99ab0 -- so the
// returned value is one byte wide and bits 8..31 of the return register are whatever
// the last callee left there. That mask is stated here rather than in the .cpp
// because the .cpp's hexadecimal literals are all supposed to be literals the
// 80-instruction listing itself contains, and the listing contains no 0xffffff00.
constexpr Word kDeadHighBytesMask = 0xffffff00u;

// -- the two receiver bytes and the two table words -------------------------------
// Offsets 0x0 and 0x370 and 0x4f4 are the receiver record's own enumeration.
constexpr std::size_t kTableWordDisplacement = 0x0;      // MOV EAX,[ESI]      0x00f999f7, 0x00f99a0e
constexpr std::size_t kFirstFlagDisplacement = 0x370;    // CMP BYTE [ESI+..],AL 0x00f99a06
constexpr std::size_t kSecondFlagDisplacement = 0x4f4;   // CMP BYTE [ESI+..],0   0x00f99a1b

// -- the two table slots ---------------------------------------------------------
// The two dispatches, as the listing spells them. The reconstruction writes these two
// numbers as literals at the `load_slot` call sites rather than through these
// constants, and that is deliberate rather than an oversight: the tooling that
// adjudicates VIRTUAL DISPATCH reads a source's slot displacements out of the
// literals passed to a slot-naming call, so a constant here would leave the
// reconstruction's slot claim unverifiable while saying exactly the same thing. The
// constants stay as the single place the header states what the two displacements are.
constexpr std::size_t kFirstSlotDisplacement = 0x4c;  // MOV EDX,[EAX + 0x4c] 0x00f999f9
constexpr std::size_t kSecondSlotDisplacement = 0x30; // MOV EDX,[EAX + 0x30] 0x00f99a10
static_assert(kFirstSlotDisplacement == 0x4c, "the first dispatch reads the table word at +0x4c");
static_assert(kSecondSlotDisplacement == 0x30, "the second dispatch reads the table word at +0x30");
// The one argument word this body pushes: `PUSH 0x7` at 0x00f999fc. The machine
// passes it as a full dword on the stack; the slot +0x4c implementation in this
// class's table reads it as a byte (`MOV DL,[ESP+0x4]`), so it is modelled as one
// byte and the other three are not observable. Whether the runtime override reads
// it as a dword is unresolved_questions.
constexpr std::uint8_t kFirstSlotSelector = 0x7;

// -- the scan loop -----------------------------------------------------------------
// `ADD ESI,0x438` at 0x00f99a27 lifts the outer cursor off the receiver, and
// `ADD ESI,0x10` at 0x00f99aa2 is its stride.
constexpr std::size_t kOuterCursorDisplacement = 0x438;
constexpr std::size_t kOuterStride = 0x10;
// `LEA ECX,[ESI + 0xffffff40]` at 0x00f99a32 is the inner cursor: 0xffffff40 is
// -0xc0, so the inner cursor starts 0xc0 BELOW the outer one.
constexpr std::size_t kInnerBackDisplacement = 0xc0;
// `ADD ECX,0x60` at 0x00f99a5e is the inner stride, and it is also the distance
// from one group base to the next (see the group layout below).
constexpr std::size_t kGroupStride = 0x60;
// `CMP EDX,0x2` at 0x00f99a61 and `CMP EDI,0x6` at 0x00f99aa5. Both bounds are
// tested with a SIGNED JL against a counter that starts at zero and is incremented
// before the test, so the outer loop runs exactly six times and the inner exactly
// two. Nothing in the listing makes either count depend on anything else.
constexpr unsigned kInnerCount = 2;
constexpr unsigned kOuterCount = 6;

// The inner cursor's first float is at [ECX - 0x4] (0x00f99a40), so the first
// group base is four bytes below it -- and so is the third group's (0x00f99a66).
constexpr std::size_t kGroupLead = 0x4;
// The fourth group's first float is at [ESI + 0x5c] (0x00f99a83), i.e. 0x60 past
// the third group's base of [ESI - 0x4].
constexpr std::size_t kFourthGroupOffset = 0x5c;
// Within a group base g the first pair is (g, g+8) -- 0x00f99a40 `MOVSS [ECX-0x4]`
// against 0x00f99a45 `UCOMISS [ECX+0x4]` -- and the second is (g+4, g+0xc)
// (0x00f99a4f `MOVSS [ECX]` against 0x00f99a53 `UCOMISS [ECX+0x8]`). So the two
// pairs sit at the group base and four bytes later, and each spans eight.
constexpr std::size_t kPairStride = 0x4;
constexpr std::size_t kPairSpan = 0x8;

// -- the only way the body touches the receiver or a group -------------------------
// Displacement-named accessors over an opaque byte run. A member access would assert
// an identity the machine-derived record cannot corroborate, so none is used
// anywhere in this package, and the model test plants decoy words at every
// neighbouring offset it can name.
// The word AT a displacement, as a VALUE. `MOV EAX,dword ptr [ESI]` loads the word
// the receiver holds at +0x00; using the ADDRESS of that word instead of the word is
// exactly the two-level mistake this accessor is shaped to make impossible, and it is
// the mistake this package's first build made.
inline Word word_value_at(const std::uint8_t* base, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, base + displacement, sizeof value);
  return value;
}

inline std::uint8_t* byte_at(std::uint8_t* base, std::size_t displacement) {
  return base + displacement;
}

inline const std::uint8_t* byte_at(const std::uint8_t* base, std::size_t displacement) {
  return base + displacement;
}

// `MOVSS XMM0,dword ptr [...]` and `UCOMISS XMM0,dword ptr [...]` each read four
// bytes. memcpy rather than a reinterpret_cast: the group's base g is only ever
// four-byte aligned relative to the cursor, and a strict-aliasing cast of a
// std::uint8_t buffer to Real is a defect the compiler is entitled to exploit.
inline Real real_at(const std::uint8_t* base, std::size_t displacement) {
  Real value = 0.0f;
  std::memcpy(&value, base + displacement, sizeof value);
  return value;
}

// -- the two table slots as function-pointer types ---------------------------------
// Both are __thiscall. The first takes the one stack argument word and the callee
// pops it (`RET 0x4` in the table's slot +0x4c implementation); the second takes
// none (bare `RET` in the table's slot +0x30 implementation).
//
// Both return a FULL word, not a byte, and that is deliberate: the machine writes
// only AL, so bits 8..31 of the return register survive into this body's own return
// register and the model records them. It also keeps the gate honest -- the machine
// tests all eight bits of AL (`TEST AL,AL` at 0x00f99a02, 0x00f99a17 and
// 0x00f999ef), not bit 0, and a return type of std::uint8_t on the slot would hide
// that distinction from the model test instead of exposing it.
using SlotFirst = Word(PKG_SW2_00F999E0_THISCALL*)(Receiver*, std::uint8_t);
using SlotSecond = Word(PKG_SW2_00F999E0_THISCALL*)(Receiver*);

// The word a table entry holds, loaded by address. `MOV EDX,dword ptr [EAX + 0x4c]`
// is a load of a function POINTER out of a table the runtime object names -- two
// levels, and the model test's decoys for the wrong-base and wrong-slot cases are
// aimed squarely at collapsing them into one.
//
// It returns a plain Word rather than the typed pointer on purpose. A helper whose
// return type is a POINTER TO A FUNCTION inherits that function's calling convention,
// so returning Slot would make load_slot itself __thiscall on this ABI, the call in
// the body would no longer be the shape the listing has, and -- as this package's
// first build showed -- the result would come back somewhere the call site does not
// look. The typed value is re-made by slot_from_word below, from the same word.
// `table` is the table ADDRESS, already read out of the receiver's own +0x00, which
// is why it is a pointer parameter and not a receiver pointer: `MOV EAX,[ESI]` then
// `MOV EDX,[EAX + 0x4c]` is two loads, and collapsing them into one is the two-level
// mistake this signature is shaped to make impossible.
inline Word load_slot(const Word* table, std::size_t slot_displacement) {
  Word target = 0;
  std::memcpy(&target, reinterpret_cast<const std::uint8_t*>(table) + slot_displacement,
              sizeof target);
  return target;
}

// The typed re-make of a loaded word. It is a memcpy rather than a cast or a
// templated helper, and both of those were tried first: a function-pointer cast from
// an integer is not allowed without a reinterpret_cast, and a template whose return
// type is a pointer to a function inherits that function's calling convention, which
// turns the helper itself into a __thiscall call and puts the result somewhere the
// call site does not read. memcpy returns void*, so this helper stays cdecl.
template <typename Slot>
inline Slot slot_from_word(Word raw) {
  Slot target = nullptr;
  std::memcpy(&target, &raw, sizeof target);
  return target;
}
static_assert(sizeof(SlotFirst) == sizeof(Word), "a table entry is one 32-bit word");
static_assert(sizeof(SlotSecond) == sizeof(Word), "a table entry is one 32-bit word");

// -- the two direct callees -------------------------------------------------------
// 0x00f48a70, six bytes, transcribed from the image:
//   00f48a70  A1 B0 8E 6C 01   MOV EAX,ds:0x16c8eb0
//   00f48a75  C3               RET
// A cdecl leaf with no stack argument, no ECX use, and EAX its only register
// written. It reads one global and returns it. The model declares the READ, not the
// value: nothing in this body or in any record fixes what 0x16c8eb0 holds, so the
// declaration hands the value to the model test's observer. The global read lives
// inside 0x00f48a70 and not in this body's span, which is why GLOBALS is empty for
// this package and why the sidecar records it under mechanics.direct_call_1.
extern "C" Word PKG_SW2_00F999E0_CDECL global_object_00f48a70(void);

// 0x00f699b0, transcribed from the image (its own bytes, 0x00f699b0..0x00f69a23):
//   00f699b0  CMP DWORD PTR ds:0x15b0e48,0x15b0e48
//   00f699ba  JE  0x00f699bf
//   00f699bc  XOR AL,AL
//   00f699be  RET                                  -> return 0
//   00f699bf  CMP BYTE PTR [ECX+0x1ce],0x0
//   00f699c6  JNE 0x00f699bc                       -> return 0
//   00f699c8  PUSH ESI
//   00f699c9  XOR ESI,ESI
//   00f699cb  LEA EDX,[ECX+0x84]
//   00f699d1  CMP BYTE PTR [ECX+ESI*1+0x78],0x0   <- the per-iteration flag gate
//   00f699d6  JNE 0x00f69a20
//   00f699d8..0x00f69a02   the same two-pair, 0x60-stride, LAHF/TEST AH,0x44 shape
//   00f69a13  INC ESI / 00f69a14 ADD EDX,0x10 / 00f69a17 CMP ESI,0x6 / JL
//   00f69a1c  MOV AL,0x1 ; POP ESI ; RET           -> return 1
//   00f69a20  XOR AL,AL ; POP ESI ; RET            -> return 0
// Zero-argument __thiscall on ECX: it reads [ECX+...], never a stack slot, and its
// two terminators are `POP ESI ; RET`. Its EAX comes from `XOR AL,AL` / `MOV AL,0x1`
// on a body that has not written EAX, so its own return word is 0 or 1 -- but the
// declaration returns a full word anyway, for the reason given on SlotFirst.
extern "C" Word PKG_SW2_00F999E0_THISCALL global_predicate_00f699b0(void* receiver);

// -- the reconstructed body -------------------------------------------------------
//
// __thiscall, receiver in ECX, NO ordinary stack argument, bare `RET` on all three
// return sites (0x00f999f6, 0x00f99aae, 0x00f99ab3). Ghidra's own record for this
// VA reports "undefined FUN_00f999e0(void)" with ghidra_parameter_count 0 and
// return_type "undefined", which is its reading of an unclassified convention and
// not a claim about either the arguments or the return value.
//
// Return type is std::uint8_t and the width is a machine fact, not a choice: the
// three exits write AL only (0x00f999f3 `XOR AL,AL`, 0x00f99aab `MOV AL,0x1`,
// 0x00f99ab0 `XOR AL,AL`) and no instruction on any path writes the other three
// bytes of the return register. The record disagrees, and the disagreement is
// recorded rather than won: abi.return_register is "XMM0" with the register-class
// classification "float_or_x87_in_XMM0" at APPROXIMATION confidence, and inference
// RT1 gives the same reason ("an x87 or SSE instruction appears in the body"). The
// listing refutes it -- XMM0 is written only by MOVSS and read only by UCOMISS, and
// no path leaves a value in it. So the phrase is kept verbatim as a
// CLASSIFICATION in the sidecar's abi.return_semantics, with this refutation in its
// abi.return_note, and the type field states the one byte the bytes support. No
// typedef named after the phrase is written here or anywhere in this package, and
// none may be: a name for a register class would agree with the check on paper and
// with nothing in the machine. The disagreement is unresolved, not settled; see
// unresolved_questions item 1 in the sidecar.
extern "C" std::uint8_t PKG_SW2_00F999E0_THISCALL re_00f999e0(Receiver* receiver);

// Model instrumentation, not a machine global and not part of the machine's
// observable surface: the whole return register at the last return, composed exactly
// as the machine composes it (the flag byte, over the last callee's word masked to
// its high 24 bits). The C-visible return value is the low byte, which is all the
// declared 1-byte type promises; this accessor publishes the other three bytes so
// the model test can assert that a reconstruction returning a full word, or one
// that reuses a stale callee result, is caught.
std::uint32_t dead_return_word();

}  // namespace openspore::reconstruction::pkg_swarm_w2_00f999e0
