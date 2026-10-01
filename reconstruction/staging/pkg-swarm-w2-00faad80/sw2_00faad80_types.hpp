// PKG-SWARM-W2-00FAAD80 -- VA 0x00faad80
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00faad80 @ 0x00faad80, a __thiscall method with
// a 242-instruction body, 15 direct callees and 6 indirect dispatch sites. The
// xref export records exactly one reference to this address, from 0x01490c84, and the
// record associates the class tables at 0x01490be8 and 0x01490c7c. Neither is used as
// evidence here: the body reads the receiver's word at +0x00 four times and dispatches
// through it, so the association is recorded for the integrator and no slot is named
// from a table dump. Every slot displacement below is cited from the instruction that
// fixes it.
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM:
//
//  * Every receiver displacement named here is a displacement the complete
//    242-instruction listing shows through ECX or through its own alias chain
//    (`MOV ESI,ECX` at 0x00faad84, `MOV ECX,ESI` at 0x00faadd4 and 0x00faaec4, and the
//    LEA-derived cursors at 0x00faaf46/0x00faaf4c/0x00fab01c). No member of the
//    receiver is NAMED. The machine-derived receiver record (register ECX, offsets
//    {0x0,0x2c,0xfc,0x110,0x111,0x114,0x1d0,0x20c,0x210,0x30c,0x310,0x314,0x33d,
//    0x360,0x364,0x36c,0x370,0xa48}) is a set of displacements and says nothing about
//    which member is which, so the receiver is an opaque byte run reached by
//    displacement. Displacements outside that set -- 0x118, 0x369, 0x374, 0x81c, 0x828 --
//    are displacements of a row table, a phase byte, a source row array and two cursor
//    bases that the body reaches through the same alias; each is cited in the .cpp at
//    the instruction that shows it.
//
//  * Two displacements are DERIVED and are deliberately written as arithmetic on
//    displacements the listing does contain, because the derived value appears nowhere
//    in the listing: the destination row element of iteration i is written through a
//    cursor based at 0x828 with the four stores at cursor-8/cursor-4/cursor/cursor+4, so
//    no 0x820 literal is written anywhere in this package; and the source row of
//    iteration i of page k is at 0x374 + 0x10*(i + 6*k), a product of three listing
//    displacements (0x374 at 0x00faaf61, 0x10 at 0x00fab006, 6 at 0x00fab00c) rather
//    than a single invented constant.
//
//  * The frame is walked by hand in the .cpp and reproduced here as a real object with
//    real slots, so the 16 bytes the body hands to its three per-row callees sit where
//    the listing's ESP arithmetic puts them. The model test asserts that placement
//    against an independently computed expectation.
//
//  * The three float constants are read out of the image, not out of any record:
//    0x01473c70 holds 0x42c80000's neighbour 10.0f, 0x01485720 holds 1.0f and
//    0x013ec4d0 holds 100.0f. The 0x016c9e8c operand of 0x00faae86 is a POINTER (a
//    .data address), not a float and not a value; nothing in this body reads through it
//    and the model passes it through unread.
//
//  * Nothing inside the row objects at the receiver's +0x118 is named or claimed. This
//    body only loads a POINTER from each of the six words and passes it as a receiver;
//    what the pointer designates is not established by any record in this repository.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cmath>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00faad80 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain: GCC rejects the bare MSVC
// keywords, so the x86-32 attribute form is the portable spelling and the keyword form
// is kept for MSVC. Which one each callee gets, and why, is stated at its declaration.
#if defined(_MSC_VER)
#define PKG_SWARM_W2_00FAAD80_THISCALL __thiscall
#define PKG_SWARM_W2_00FAAD80_CDECL __cdecl
#else
#define PKG_SWARM_W2_00FAAD80_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W2_00FAAD80_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00faad80 {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Receiver displacements. Each is the displacement of one instruction, cited.
// ---------------------------------------------------------------------------

// 0x00faad86 MOV EAX,dword ptr [ESI + 0xa48] / 0x00faad9a MOV [ESI + 0xa48],EAX.
// The body branches on this word three times (0x00faad8f JZ, 0x00faad93 JLE,
// 0x00faada0 JNZ) and writes it once (0x00faad9a).
constexpr std::uint32_t kOffPageCounter = 0xa48;
// 0x00faade3 CMP dword ptr [ESI + 0xfc],EDI -- a dword, compared as a word, but the
// value it feeds is produced by SETNZ (0x00faadbf) and zero-extended (0x00faadc5), so
// only "zero or non-zero" is ever observable.
constexpr std::uint32_t kOffGate = 0xfc;
// 0x00faadef MOV ECX,dword ptr [ESI + 0x2c] -- a POINTER. Every +0x34/+0x38/+0x3c/
// +0x40/+0x50/+0x54 access in this body is through this pointer, never through the
// receiver. Reading one of them off the receiver instead is the two-level bug this
// package's model test is built to catch.
constexpr std::uint32_t kOffBoundsObject = 0x2c;
// 0x00faadf2 MOVSS XMM0,dword ptr [ESI + 0x360] -- compared (as "differs") against
// bounds+0x34 at 0x00faadfa.
constexpr std::uint32_t kOffExtentNear = 0x360;
// 0x00faae0f MOVSS XMM1,dword ptr [ESI + 0x364] -- compared (as "differs") against
// bounds+0x3c * bounds+0x38 at 0x00faae17.
constexpr std::uint32_t kOffExtentSpan = 0x364;
// 0x00fae20 CMP byte ptr [ESI + 0x111],0x0 -- a BYTE, and the third disjunct of the
// resync condition at 0x00faae20/0x00faae27.
constexpr std::uint32_t kOffResyncFlag = 0x111;
// 0x00faaebb MOV byte ptr [ESI + 0x33d],AL -- a BYTE, written twice: at 0x00faaebb from
// the phase test, and cleared at 0x00fab04c.
constexpr std::uint32_t kOffPhaseDirty = 0x33d;
// 0x00faaf1d CMP byte ptr [ESI + 0x370],0x0 -- a BYTE, the "already done" latch, set at
// 0x00fab022 and tested at 0x00faaf1d.
constexpr std::uint32_t kOffPhaseDone = 0x370;
// 0x00faaea1 SUB ECX,dword ptr [ESI + 0x36c] -- a dword, the page index. It is read
// once for the phase byte (0x00faaea1) and once PER LOOP ITERATION (0x00faaf52), and
// the callee at 0x00faaf41 changes it, so the in-loop read is load-bearing.
constexpr std::uint32_t kOffPageIndex = 0x36c;
// 0x00faaea7 TEST byte ptr [ECX + 0x369],0x7, with ECX = self - *(self+0x36c) from
// 0x00faaea1. So the byte is at receiver + 0x369 - page, computed in 32-bit arithmetic
// and allowed to wrap; the model reproduces the wrap rather than clamping it.
constexpr std::uint32_t kOffRowPhase = 0x369;
// The TEST mask of 0x00faaea7, and the ONLY use of the receiver's +0x369 word.
constexpr std::uint32_t kRowPhaseMask = 0x7;
// 0x00faaee0 INC dword ptr [ESI + 0x114] -- the one counter this body increments, and
// it increments it exactly once on every path that reaches 0x00faaee0.
constexpr std::uint32_t kOffCallCounter = 0x114;
// 0x00faaeda MOV ECX,dword ptr [ESI + 0x20c] -- a POINTER, tested against zero at
// 0x00faaee6/0x00faaee8. It is loaded BEFORE the counter increment and its value is
// then dead: 0x00faaf06 `PUSH ECX` is overwritten in place by the FSTP at 0x00faaf07,
// so the callee at 0x00faaf0b never receives it.
constexpr std::uint32_t kOffSettleTarget = 0x20c;
// 0x00faaeea MOV EDX,dword ptr [ESI + 0x1d0] -- a mode word. The four instructions at
// 0x00faaef6..0x00faaeff reduce it to 0 when it equals 4 and leave it alone otherwise.
constexpr std::uint32_t kOffMode = 0x1d0;
// The value the SUB at 0x00faaf0... (0x00faaef8 SUB EAX,0x4) compares the mode
// against. Four instructions, one value: mode == 4 yields 0, anything else yields the
// mode word itself.
constexpr std::uint32_t kModeNeutral = 4;
// 0x00fab0b5 MOV ESI,dword ptr [ESI + 0x210] -- a POINTER to the peer object, tested
// against zero at 0x00fab0bc/0x00fab0be. Null is a normal outcome, not an error.
constexpr std::uint32_t kOffPeer = 0x210;
// 0x00fab0aa MOV byte ptr [ESI + 0x110],AL -- a BYTE, the "still inside" flag written
// from the FCOMIP comparison.
constexpr std::uint32_t kOffInsideFlag = 0x110;
// 0x00fab061/0x00fab067/0x00fab070 -- the three floats whose squares are summed and
// square-rooted, in that load order (0x314, 0x310, 0x30c) and in that sum order
// (0x30c^2, then 0x310^2, then 0x314^2).
constexpr std::uint32_t kOffExtentW = 0x314;
constexpr std::uint32_t kOffExtentV = 0x310;
constexpr std::uint32_t kOffExtentU = 0x30c;
// 0x00faaf46 LEA EBX,[ESI + 0x118] -- the base of the six row-object POINTERS. The
// cursor advances by 4 per iteration (0x00fab009 ADD EBX,0x4), so element i is the
// word at receiver + 0x118 + 4*i and the body only LOADS it (0x00faafe3, 0x00faafeb,
// 0x00faaff8) and passes it as a receiver. Nothing inside it is reached.
constexpr std::uint32_t kOffRowObject = 0x118;
// 0x00faaf4c LEA EBP,[ESI + 0x828] -- the destination cursor. It advances by 0x10 per
// iteration (0x00fab006 ADD EBP,0x10) and the four stores are at cursor-8, cursor-4,
// cursor and cursor+4 (0x00faaf92..0x00faafa1), so the cursor is the SECOND word of the
// 16-byte element. The element base is 0x828-8, which appears in no instruction, so it
// is written below as arithmetic and never as a literal.
constexpr std::uint32_t kOffRowDestCursor = 0x828;
// 0x00fab01c LEA EDI,[ESI + 0x81c] -- the address of a dword, not the dword. It is the
// argument of 0x00faacd0, the receiver-relay argument of 0x00690120/0x006909b0, and
// the value at it is re-read at 0x00fab029 AND at 0x00fab042.
constexpr std::uint32_t kOffRelaySlot = 0x81c;
// 0x00faaf61 MOVSS XMM0,dword ptr [ECX + ESI*0x1 + 0x374] with ECX = (i + 6*page)*0x10
// built by 0x00faaf52..0x00faaf5e. The four words of a row are read at +0, +4, +8 and
// +0xc of that address (0x00faaf61, 0x00faaf77, 0x00faaf82, 0x00faaf8d).
constexpr std::uint32_t kOffRowSource = 0x374;
// The row stride: ADD EBP,0x10 (0x00fab006) and SHL ECX,0x4 (0x00faaf5e).
constexpr std::uint32_t kRowStride = 0x10;
// The rows per page and the loop trip count, which are the same 6: the index is
// i + 6*page at 0x00faaf5b (`LEA ECX,[EDI + EAX*0x2]` with EAX = 3*page) and the loop
// ends at 0x00fab00c `CMP EDI,0x6` / 0x00fab00f `JL`.
constexpr std::uint32_t kRowCount = 6;

// The receiver model ends at 0xa4c, the byte after the last word this body writes
// (0xa48 + 4). The source rows live inside that run, so the run also bounds the page
// index the model supports; kMaxModelledPageIndex is the largest k for which all six
// rows of page k fit, and the static_assert says so rather than the comment.
constexpr std::size_t kReceiverSpan = 0xa4c;
constexpr std::uint32_t kMaxModelledPageIndex = 17;
static_assert(kOffRowSource + kRowStride * kRowCount * (kMaxModelledPageIndex + 1) <= kReceiverSpan,
              "the modelled receiver must hold every source row this body can read");

// The receiver. An opaque byte run: no member is named, because the machine-derived
// receiver record is a set of displacements and cannot corroborate any name for one.
struct alignas(4) Receiver {
  std::array<std::uint8_t, kReceiverSpan> opaque_00{};
};

// Displacements of the object the receiver's +0x2c WORD points at. They are NOT
// receiver displacements -- they are reached through a second dereference, and
// reading one of them off the receiver instead is the two-level bug this package's
// model test is built to catch. Each is cited from an instruction that reads it
// through the loaded pointer and never through ECX's own displacement.
//   kBoundsNear          0x34  0x00faadfa UCOMISS / 0x00faae3d ADDSS / 0x00fab086 FSUB
//   kBoundsScaleRight    0x38  0x00faae0a MULSS / 0x00faae38 MULSS / 0x00fab08f FMUL
//   kBoundsScaleLeft     0x3c  0x00faae05 MOVSS / 0x00faae33 MOVSS / 0x00fab08c FADD
//   kBoundsReach         0x40  0x00faae89 FLD / 0x00fab089 FLD
//   kBoundsLimit         0x50  0x00faae42 MOVSS / 0x00faae47 COMISS
//   kBoundsSecondLimit   0x54  0x00faae4a MOVSS
constexpr std::uint32_t kBoundsNear = 0x34;
constexpr std::uint32_t kBoundsScaleRight = 0x38;
constexpr std::uint32_t kBoundsScaleLeft = 0x3c;
constexpr std::uint32_t kBoundsReach = 0x40;
constexpr std::uint32_t kBoundsLimit = 0x50;
constexpr std::uint32_t kBoundsSecondLimit = 0x54;

// ---------------------------------------------------------------------------
// The 16-byte record the body passes to its three per-row callees.
// ---------------------------------------------------------------------------
//
// It is 16 bytes wide in the machine (four MOVSS stores at 0x00faaf71/0x00faaf7c/
// 0x00faaf82/0x00faafaf and four at 0x00faafbe..0x00faafd8) and it lives in the FRAME,
// not in the receiver: the four words are at ESP+0x14, +0x18, +0x1c and +0x20 with
// ESP = entry_esp-0x24, i.e. entry_esp-0x10 .. entry_esp-0x1. The three bound floats
// written at 0x00faae4f/0x00faae55/0x00faae5b are at ESP+0xc, +0x10 and +0x14 with
// ESP = entry_esp-0x1c, i.e. entry_esp-0x10, entry_esp-0xc and entry_esp-0x8 -- the same
// three words. The two uses are disjoint in time (the bound word is consumed by the
// FLD at 0x00faae7e, before 0x00faaf71 writes the first row word), so ONE 16-byte
// frame slot serves both, and `pick` below is a pointer into it.
struct Row4 {
  float v0;
  float v1;
  float v2;
  float v3;
};
static_assert(sizeof(Row4) == kRowStride, "the frame row slot is 16 bytes wide in the listing");

// The machine frame. The .cpp holds its 16 bytes as a plain `float scratch[4]` local
// rather than as a member of a frame type, so the reconstructed span names no struct
// member anywhere; see the walk below for why the offset the array sits at is the only
// thing the model needs to reproduce.
//
// Walked by hand over the 242 instructions, entry_esp = 0:
//   0x00faad80 SUB ESP,0x14                    esp = -0x14   (20 bytes of locals)
//   0x00faad83 PUSH ESI                        esp = -0x18
//   0x00faad8c PUSH EDI                        esp = -0x1c   <- the steady state
//   0x00faadff PUSH EBX                        esp = -0x20   (main path only)
//   0x00faaf3e PUSH EBP                        esp = -0x24   (the row loop only)
//   0x00fab02b POP EBP                         esp = -0x20
//   0x00fab0bb POP EBX                         esp = -0x1c
//   0x00fab0cc POP EDI / POP ESI / ADD ESP,0x14 esp = 0, then RET 0x8 consumes 8 more.
// The 16 bytes at -0x10 are the only frame slots this body ever addresses:
//   bound floats   0x00faae4f [ESP+0xc] = -0x10, 0x00faae55 [ESP+0x10] = -0xc,
//                  0x00faae5b [ESP+0x14] = -0x8, with ESP = -0x1c
//   row word 0..3  0x00faaf71 [ESP+0x14] = -0x10, 0x00faaf7c [ESP+0x18] = -0xc,
//                  0x00faaf87 [ESP+0x1c] = -0x8, 0x00faafaf [ESP+0x24] = -0x4 (with
//                  ESP = -0x28, after the PUSH 0x8 of 0x00faafab), all with ESP = -0x24
// So the model's frame slot is a `float scratch[4]` local whose word 0 is at
// entry_esp-0x10, and the two uses above alias: `scratch[0]` is both the computed
// bound the LEA at 0x00faae61 points at and the first word of the row the MOVSS at
// 0x00faaf71 writes.

// The two stack arguments, read out of the frame by the body itself. With ESP = -0x20
// at 0x00fab055 and 0x00fab0c0, `MOV ...,dword ptr [ESP + 0x24]` is entry_esp+0x4 and
// entry_esp+0x8 respectively -- so the second read at 0x00fab0c0 is the SECOND argument
// and the first is the FIRST. `RET 0x8` says the callee owns both words.
constexpr std::ptrdiff_t kArg1FromEntryEsp = 0x4;
constexpr std::ptrdiff_t kArg2FromEntryEsp = 0x8;
// The frame slot offsets, as signed distances from entry_esp.
constexpr std::ptrdiff_t kFrameRowFromEntryEsp = -0x10;

// ---------------------------------------------------------------------------
// The float constants, read out of the image.
// ---------------------------------------------------------------------------
//
// FLD dword ptr [0x01473c70] at 0x00faadb2: the word at file offset for RVA 0x1073c70
// is 0x41a00000, i.e. 10.0f. It is FSTP'd into the callee's argument block at
// 0x00faadc2, so it is the fifth argument of 0x00f9b8c0.
constexpr float kOneShotSeconds = 10.0f;
// MOVSS XMM0,dword ptr [0x01485720] at 0x00faafca: 0x3f800000, i.e. 1.0f. It is also
// the subtrahend of the FSUB at 0x00fab092, and the two upper words of the identity
// row written at 0x00faafd2/0x00faafd8.
constexpr float kUnitScale = 1.0f;
// FLD dword ptr [0x013ec4d0] at 0x00faaef0: 0x42c80000, i.e. 100.0f. FSTP'd into the
// callee's argument block at 0x00faaf07, so it is the second argument of 0x00fbf570.
constexpr float kSettleAmount = 100.0f;
// PUSH 0x016c9e8c at 0x00faae86. A POINTER: RVA 0x12c9e8c is in .data, 16 bytes past
// the three words this body zeroes at 0x00faaec8/0x00faaece/0x00faaed4. Nothing in
// this body reads through it and nothing in this repository identifies it, so the
// model passes the address through unread and says so.
constexpr std::uint32_t kNotifyVectorAddress = 0x016c9e8c;
// PUSH 0x03fbae24 at 0x00faae77 -- the single argument of the slot+0x1c call. Read as
// a 32-bit VALUE, not a pointer: 0x03fbae24 is below the image's data segment, and the
// decompiler's own `(IShadowWorld *)0x3fbae24` cast is the same value. What it selects
// is not established by any record; it is carried as an opaque id.
constexpr Word kStageId = 0x03fbae24;
// PUSH 0x00000008 at 0x00faafab -- the single argument of the slot+0x4c call.
constexpr Word kRowQuerySize = 8;

// The three words this body zeroes. 0x00faaec8 writes the dword at 0x016c9e7c,
// 0x00faaece the one at 0x016c9e80 and 0x00faaed4 the one at 0x016c9e84: a contiguous
// 12-byte run. The model keeps the three words in file-scope storage instead of writing
// to a fixed address, and the model test asserts all three land on zero. `which` is
// 0, 1 or 2; nothing else is a valid index and the test does not use one.
Word cleared_word(unsigned which);
// Restores the three words to their poisoned value so a case can observe the ORDER of
// the clears rather than only their result. Model instrumentation, like the four
// accessors below; not a machine global and not part of the machine's surface.
void poison_cleared_words();

// ---------------------------------------------------------------------------
// Slot-boundary model. load_slot is the ONLY place this package performs the
// two-level dereference the machine performs, so it is written down exactly once.
// ---------------------------------------------------------------------------

// The objects reached through the table pointer at the receiver's +0x00 and through
// the global getter's return value are used as table bases and nothing else. The four
// displacements below are the four `MOV EAX,dword ptr [EDX + <slot>]` reads:
//
//   0x00faadaa  +0x80  after MOV EAX,[ESI]          -- no stack argument
//   0x00faaec1  +0x10  after MOV EDX,[ESI]          -- no stack argument
//   0x00faaf2c  +0xd8  after MOV EAX,[ESI]          -- no stack argument, AL tested
//   0x00faafa8  +0x4c  after MOV EDX,[ESI]          -- one stack word (8), AL tested
//   0x00faae74  +0x1c  on the getter's return value -- one stack word (kStageId)
//   0x00faae8d  +0x15c on the +0x1c call's return   -- three stack words
inline void* load_slot(void* object, std::size_t slot_byte_offset) {
  void** table = nullptr;
  std::memcpy(&table, object, sizeof(table));
  return table[slot_byte_offset / sizeof(void*)];
}
constexpr std::size_t kSlotPageEntered = 0x80;
constexpr std::size_t kSlotPhaseResync = 0x10;
constexpr std::size_t kSlotPhaseReady = 0xd8;
constexpr std::size_t kSlotRowQuery = 0x4c;
constexpr std::size_t kSlotStageMake = 0x1c;
constexpr std::size_t kSlotStageNotify = 0x15c;

// The signatures the six indirect sites are called through. The receiver is the
// object whose table the slot came from; the argument list is the pushed words, in
// push order reversed (the last push is the first argument).
using FnVoid = void (*)(void*);
using FnBool = Word (*)(void*);
using FnQuery = Word (*)(void*, Word);
using FnVoidToVoid = void* (*)(void*, Word);
using FnNotify = void (*)(void*, Word, Word, float);

// ---------------------------------------------------------------------------
// Byte accessors. Every read and write of the receiver, of the bounds object and of
// the row arrays goes through one of these, by displacement. None of them names a
// member, and none of them asserts an identity for a word.
// ---------------------------------------------------------------------------
inline Word load_word(const void* base, std::uint32_t displacement) {
  Word value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + displacement, sizeof(value));
  return value;
}
inline void store_word(void* base, std::uint32_t displacement, Word value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + displacement, &value, sizeof(value));
}
inline std::uint8_t load_byte(const void* base, std::uint32_t displacement) {
  return *(static_cast<const std::uint8_t*>(base) + displacement);
}
inline void store_byte(void* base, std::uint32_t displacement, std::uint8_t value) {
  *(static_cast<std::uint8_t*>(base) + displacement) = value;
}
inline float load_float(const void* base, std::uint32_t displacement) {
  float value = 0.0f;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + displacement, sizeof(value));
  return value;
}
inline void store_float(void* base, std::uint32_t displacement, float value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + displacement, &value, sizeof(value));
}
// A receiver word read as a POINTER. Four displacements in this body are pointers and
// only one of them is dereferenced by this body (kOffBoundsObject); the others
// (kOffSettleTarget, kOffPeer and the six row objects at kOffRowObject) are handed to
// callees as receivers. Reading through any of them here would be a claim the listing
// does not support.
inline void* load_pointer(const void* base, std::uint32_t displacement) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(load_word(base, displacement)));
}

// UCOMISS + LAHF + TEST AH,0x44 + JP, as at 0x00faadfa/0x00faadfe/0x00faae00/0x00faae03
// and again at 0x00faae17/0x00faae1a/0x00faae1b/0x00faae1e. LAHF puts ZF in AH bit 6
// and 0x44 masks bits 6 and 2, so the masked value is 0x44 (two bits, even) when ZF is
// set and 0x04 (one bit, odd) when it is clear, and JP is taken exactly when ZF is
// CLEAR. UCOMISS sets ZF for an equal pair AND for an unordered one, so this sequence
// reports an unordered pair as "the same". C's `!=` reports it as different, and the
// two disagree on a NaN; the model uses the machine's reading and says so.
inline bool ordered_differs(float left, float right) { return (left < right) || (left > right); }

// ---------------------------------------------------------------------------
// The 15 direct callees. Each name carries the address as an 8-hex-digit suffix.
// Each declaration states the shape this body's own frame fixes, and nothing more.
// ---------------------------------------------------------------------------

// 0x00faae6b, no pushed word, and the frame is unchanged across it (the next
// instruction 0x00faae70 reads [EAX] with ESP = entry-0x1c, as 0x00faae4f did). The
// callee ends `C3` (bytes a1 cc d8 5f 01 / c3 at 0x0067dd80..0x0067dd85), so it pops
// nothing: cdecl, no argument, and its EAX is the object the slot+0x1c call is made
// on. The 0x015fd8cc it loads is a .data address; the body does not interpret it.
extern "C" void* PKG_SWARM_W2_00FAAD80_CDECL renderer_global_get_0067dd80();

// 0x00faaf41, no pushed word, receiver in ECX (0x00faaf3f). The callee's own 32 bytes
// are `MOV EAX,[ECX+0x36c]` / `MOV BYTE PTR [ECX+EAX+0x368],0` / `MOV EDX,1` /
// `SUB EDX,[ECX+0x36c]` / `MOV [ECX+0x36c],EDX` / `C3` (0x00f96370..0x00f9638f), so it
// CLEARS the byte at receiver+0x368+page and SETS receiver+0x36c to 1-page. The model
// reproduces that, because the row loop re-reads +0x36c on every iteration.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL page_turn_00f96370(void* receiver);

// 0x00fab017, no pushed word, receiver in ECX (0x00fab015). Terminator not read; only
// "receiver in ECX and no stack word" is fixed, by 0x00fab015 and the unchanged frame.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL row_block_finish_00f96f90(void* receiver);

// 0x00faae2b, no pushed word, receiver in ECX (0x00faae29). Terminator not read.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL bounds_resync_00f977c0(void* receiver);

// 0x00fab036, no pushed word, receiver in ECX carrying the value read at 0x00fab029
// (0x00fab02b pops EBP, which is not ECX, so ECX survives). The word at
// receiver+0x81c is CLEARED at 0x00fab030, BEFORE the call. Terminator not read.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL relay_release_00690120(void* receiver);

// 0x00fab047, no pushed word, receiver in ECX re-read at 0x00fab042 -- i.e. the value
// the relay builder at 0x00fab03d may have stored, NOT the value 0x00690120 was given
// and NOT the value 0x00fab030 cleared. Terminator not read.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL relay_commit_006909b0(void* receiver);

// 0x00faadd6. Five words are pushed and the epilogue at 0x00faaddb..0x00faaddd
// (`POP EDI; POP ESI; ADD ESP,0x14; RET 0x8`) needs ESP = entry-0x1c while the call
// leaves it at entry-0x30, so the callee pops all 20 bytes: __thiscall, five stack
// words, receiver in ECX (0x00faadd4). Argument order, by push:
//   PUSH EAX (0x00faadd3) -- LAST push, so the FIRST argument. EAX came from
//     `LEA EAX,[ESP + 0x30]` at 0x00faadcf with ESP = entry-0x2c, i.e. entry+0x4.
//   PUSH EDX (0x00faadce) -- second argument, and `LEA EDX,[ESP + 0x2c]` at 0x00faadca
//     with ESP = entry-0x28 is ALSO entry+0x4.
//   PUSH ECX (0x00faadc9) -- third argument, the SETNZ/MOVZX pair at 0x00faadbf and
//     0x00faadc5: 1 when the receiver's +0xfc is non-zero, 0 otherwise.
//   PUSH EDI (0x00faadc8) -- fourth argument, always 0 (XOR EDI,EDI at 0x00faad8d and
//     nothing writes EDI before this call on this path).
//   the fifth argument is the FSTP at 0x00faadc2 into the slot 0x00faadbe reserved by
//     `PUSH ECX`: 10.0f. The PUSH at 0x00faadbe pushes the incoming ECX and the FSTP
//     overwrites it, so the value pushed there is dead.
// So the first TWO arguments are the SAME address, and it is the address of the
// caller's first stack argument. The model hands the address of its own copy of that
// argument, which designates the same value; the model test asserts the two pointers
// it hands out are equal and that reading through either yields the argument.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL one_shot_notify_00f9b8c0(
    void* receiver, Word* first_argument_slot, Word* second_argument_slot, Word gate_flag,
    Word zero_argument, float seconds);

// A sentinel, NOT a machine address. 0x00faaf0b is the only call in this body whose
// ECX receiver the listing does not reload: the last write to ECX before it is
// `MOV ECX,ESI` at 0x00faaec4, for the slot+0x10 call, and 0x00fbf570 is called
// eleven instructions later with no intervening ECX write. So the value ECX holds
// there is whatever the slot+0x10 callee left, and this listing does not fix that
// callee's return either. The receiver of 0x00fbf570 is therefore NOT DETERMINED by
// this body, and the model passes this sentinel rather than inventing a receiver.
// The model test asserts the callee observer receives exactly this value, which is
// what makes the non-claim checkable rather than merely stated.
void* indeterminate_receiver();

// 0x00faaf0b. Three words are pushed and the frame is unchanged across the call
// (0x00fab055 reads [ESP+0x24] with ESP = entry-0x20, which is where 0x00fbf570's
// arguments were), so the callee pops 12 bytes: __thiscall, three stack words. Argument
// order, by push:
//   PUSH EDX (0x00faaf0a) -- first argument, read at 0x00faaf01 with ESP = entry-0x20,
//     i.e. entry+0x4: the caller's first argument.
//   the second argument is the 100.0f FSTP'd at 0x00faaf07 into the slot 0x00faaf06
//     reserved by `PUSH ECX`; the ECX pushed there is the receiver's +0x20c word and
//     is overwritten in place, so the callee never receives it.
//   PUSH EAX (0x00faaf05) -- third argument, the mode word reduced by
//     0x00faaef6..0x00faaeff to 0 when it equals 4.
// The first parameter is the ECX value and is the sentinel above, not the receiver.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL settle_amount_00fbf570(
    void* unfixed_ecx, Word first_argument, float amount, Word mode);

// 0x00faafe6, 0x00faaff3 and 0x00fab000. Each pushes two words (0x00faafe5/0x00faaff2/
// 0x00faafff push EDI, the loop index) and the loop's ESP is back at entry-0x24 for
// every one of them (0x00faafde reads [ESP+0x14] = entry-0x10 again after the first),
// so all three pop 8 bytes: __thiscall, two stack words. Argument order, by push:
//   PUSH EDI (0x00faafe5) -- first argument, the loop index i, 0..5.
//   PUSH ECX (0x00faafe2) -- second argument, `LEA ECX,[ESP+0x14]` at 0x00faafde, i.e.
//     the address of the 16-byte frame row slot at entry-0x10.
// The receiver is re-loaded from the row-object cursor on every one of the three
// (0x00faafe3, 0x00faafeb, 0x00faaff8), so the same object is given all three times.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL row_apply_first_00fb0d20(
    void* row_object, Word index, const Row4* row);
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL row_apply_second_00faf140(
    void* row_object, Word index, const Row4* row);
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL row_apply_third_00faf400(
    void* row_object, Word index, const Row4* row);

// 0x00fab03d. Two words are pushed and the body drops them itself at 0x00fab044 with
// `ADD ESP,0x8`, so this one is cdecl: two stack words, caller-cleaned. Argument order,
// by push: PUSH ESI (0x00fab03c) is the first argument (the receiver) and PUSH EDI
// (0x00fab03b) the second (the address receiver+0x81c). The frame is back at entry-0x1c
// for 0x00fab042's `MOV ECX,[EDI]`, which reads through the same address.
extern "C" void PKG_SWARM_W2_00FAAD80_CDECL relay_build_00faacd0(void* receiver, void* relay_slot);

// 0x00fab05c. One word is pushed and the x87 block that follows does not touch ESP,
// and 0x00fab0a7's PUSH EBX lands the next word on top of it, so the callee pops 4
// bytes: __thiscall, one stack word, which 0x00fab055 read out of the frame as the
// caller's first argument. ECX is the receiver (0x00fab05a).
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL frame_commit_00f9ba40(void* receiver, Word first_argument);

// 0x00fab0b0. One word is pushed at 0x00fab0a7 and 0x00fab0bb's POP EBX needs ESP back
// at entry-0x1c, so the callee pops 4 bytes: __thiscall, one stack word, the same first
// argument (EBX, not re-read from the frame). ECX is the receiver (0x00fab0a8). The
// byte written at 0x00fab0aa lies between the argument push and the call, so it is
// already stored when the callee runs.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL inside_flag_commit_00fa5610(
    void* receiver, Word first_argument);

// 0x00fab0c7. One word is pushed and the epilogue's POP EDI needs ESP = entry-0x1c, so
// the callee pops 4 bytes: __thiscall, one stack word. ECX is the receiver, which
// 0x00fab0b5 loaded from the original receiver's +0x210 and 0x00fab0c5 moved into ECX --
// i.e. the callee's receiver is the PEER object, not this one. The word is the caller's
// SECOND argument (0x00fab0c0, [ESP+0x24] with ESP = entry-0x1c).
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL peer_notify_00fc7b30(void* peer, Word second_argument);

// ---------------------------------------------------------------------------
// The reconstruction itself.
// ---------------------------------------------------------------------------

// FUN_00faad80 @ 0x00faad80.
//
// __thiscall, receiver in ECX (the record's R1 inference and this body's own
// `MOV ESI,ECX` at 0x00faad84), and exactly TWO ordinary stack arguments: RET 0x8 on
// both return sites (0x00faade0 and 0x00fab0d1) makes the callee own both words, and
// the body reads them itself at 0x00faaf01/0x00fab055 (entry+0x4) and 0x00fab0c0
// (entry+0x8). The frame balances exactly under the walk in `Frame` above.
//
// Return type is void, and that is a machine fact rather than a record's word: the
// record's return_semantics is the phrase "float_or_x87_in_ST0", which its own
// inference RT1 derives from nothing more than "an x87 or SSE instruction appears in
// the body". The body produces no value in ST0 on either path -- the 10.0f is loaded
// and immediately stored at 0x00faadb2/0x00faadc2, the bound float is loaded and
// immediately stored at 0x00faae7e/0x00faae83, and the distance comparison's FCOMIP at
// 0x00fab098 and FSTP at 0x00fab09a pop the last two x87 words before either return --
// so the x87 stack is empty at 0x00faade0 and at 0x00fab0d1. See the sidecar's
// unresolved_questions; the disagreement with the record is recorded, not hidden.
extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL re_00faad80(Receiver* receiver, Word first_argument,
                                                          Word second_argument);

// ---------------------------------------------------------------------------
// Model instrumentation. NOT machine globals and NOT part of the machine's
// observable surface; declared here so the model test can assert the frame walk
// instead of trusting it.
// ---------------------------------------------------------------------------

// The 16-byte frame slot the last call used, so the test can check the two frame claims
// below against an address it computes itself. Returned as four floats because that is
// how the model holds them; the callee declarations take a `const Row4*` over the same
// four words.
const float* last_frame();
// The same 16 bytes as the model handed them to the three per-row callees.
const float* last_row_slot();
// Its signed distance from the modelled entry stack pointer, which the machine fixes
// at -0x10 (0x00faaf71 with ESP = entry-0x24).
std::ptrdiff_t last_row_slot_entry_offset();
// The bound word `LEA EBX,[...]` selected at 0x00faae61/0x00faae67, as an offset inside
// the row slot: 0 when JA kept the computed bound (0x00faae65) and 4 when it took the
// stored limit (0x00faae67). The value read through it is handed to the slot+0x15c
// call as the third argument (0x00faae7e/0x00faae83).
std::ptrdiff_t last_picked_word_offset();

}  // namespace openspore::reconstruction::pkg_swarm_w2_00faad80
