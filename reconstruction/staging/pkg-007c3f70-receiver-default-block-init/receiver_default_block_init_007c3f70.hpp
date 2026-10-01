#pragma once

// Reconstruction of FUN_007c3f70 @ 0x007c3f70 (SporeApp.exe 3.1.0.22,
// image base 0x400000, x86-32).
//
// Evidence basis, all from the live Ghidra bridge on SporeApp.exe and collected
// into reconstruction/evidence/007c3f70/:
//   * complete 21-instruction listing, body_start 0x007c3f70, body_end
//     0x007c3ffb, body_span_bytes 140; parse record declared_count 21,
//     unparsed 0, degraded false, flow_complete true, local_extent 0,
//     esp_unresolved false, and no frame instruction at all (push_ebp false,
//     sub null, mov_ebp_esp false, fp false):
//       0x007c3f70  F3 0F 10 05 B8 5D 63 01   MOVSS XMM0,dword ptr [0x01635db8]
//       0x007c3f78  8B C1                     MOV EAX,ECX
//       0x007c3f7a  F3 0F 11 84 04 01 00 00   MOVSS dword ptr [EAX+0x140],XMM0
//       0x007c3f82  F3 0F 10 05 BC 5D 63 01   MOVSS XMM0,dword ptr [0x01635dbc]
//       0x007c3f8a  F3 0F 11 84 44 01 00 00   MOVSS dword ptr [EAX+0x144],XMM0
//       0x007c3f92  F3 0F 10 05 C0 5D 63 01   MOVSS XMM0,dword ptr [0x01635dc0]
//       0x007c3f9a  F3 0F 11 84 48 01 00 00   MOVSS dword ptr [EAX+0x148],XMM0
//       0x007c3fa2  F3 0F 10 05 C4 5D 63 01   MOVSS XMM0,dword ptr [0x01635dc4]
//       0x007c3faa  F3 0F 11 84 4C 01 00 00   MOVSS dword ptr [EAX+0x14c],XMM0
//       0x007c3fb2  F3 0F 10 05 20 06 3F 01   MOVSS XMM0,dword ptr [0x013f0620]
//       0x007c3fba  33 C9                     XOR ECX,ECX
//       0x007c3fbc  89 88 50 01 00 00         MOV dword ptr [EAX+0x150],ECX
//       0x007c3fc2  89 88 54 01 00 00         MOV dword ptr [EAX+0x154],ECX
//       0x007c3fc8  89 88 58 01 00 00         MOV dword ptr [EAX+0x158],ECX
//       0x007c3fce  F3 0F 11 84 5C 01 00 00   MOVSS dword ptr [EAX+0x15c],XMM0
//       0x007c3fd6  F3 0F 11 84 60 01 00 00   MOVSS dword ptr [EAX+0x160],XMM0
//       0x007c3fde  F3 0F 11 84 64 01 00 00   MOVSS dword ptr [EAX+0x164],XMM0
//       0x007c3fe6  F3 0F 11 84 68 01 00 00   MOVSS dword ptr [EAX+0x168],XMM0
//       0x007c3fee  C6 80 6C 01 00 00 01     MOV byte ptr [EAX+0x16c],0x1
//       0x007c3ff5  89 88 70 01 00 00         MOV dword ptr [EAX+0x170],ECX
//       0x007c3ffb  C3                        RET
//   * /read_memory at 0x007c3f70 returns exactly those 140 bytes and nothing
//     outside 0x007c3f70..0x007c3ffb is read by this package.
//   * derived ABI (categories abi and abi_derived, verdict ABI_INFERRED,
//     conflicts empty, completeness CORE_RESOLVED): calling_convention
//     __thiscall, candidate_conventions ["__thiscall","__fastcall"], cleanup 0
//     bytes owned by the caller ("ret with no immediate, no stack reads"),
//     receiver register ECX, receiver present, bounds_only, distinct_offsets 13,
//     max_offset 368, written_through 13, dispatch {call_offsets: [],
//     indirect_calls: 0, vtable_shaped_loads: 0}, variadic false, tail_call
//     false, sret false, stack_arguments [], seh_or_cookie_frame false.
//   * ghidra_function (live): classification "leaf", callees [], parameter_count
//     0, locals [], body_span_bytes 140, xref_count 65, 32 distinct caller
//     functions, rva 0x3c3f70.
//   * the five absolute data addresses the listing names are recorded as FIVE
//     data-reference rows, ALL OF THEM access_mode `read`, in
//     knowledgegraph/triage/datarefs-2540f2ca.tsv:
//         007c3f70 -> 0x01635db8  read  .data -wr  callsite 0x007c3f70
//         007c3f70 -> 0x01635dbc  read  .data -wr  callsite 0x007c3f82
//         007c3f70 -> 0x01635dc0  read  .data -wr  callsite 0x007c3f92
//         007c3f70 -> 0x01635dc4  read  .data -wr  callsite 0x007c3fa2
//         007c3f70 -> 0x013f0620  read  .rdata --r callsite 0x007c3fb2
//     NO ROW IN THAT ARTIFACT RECORDS A WRITE MODE FOR THIS BODY, so no write
//     to any of those five addresses is claimed, and this reconstruction
//     performs none: the only way the package touches them is a `const` read.
//
// WHAT THE BODY IS, AS A TRANSCRIPTION AND NOTHING MORE.
//
//     void receiver_default_block_init_007c3f70(Receiver* self) {
//         const float a = g_01635db8;   // MOVSS loads, one word each
//         const float b = g_01635dbc;
//         const float c = g_01635dc0;
//         const float d = g_01635dc4;
//         const float shared = g_013f0620;   // ONE load
//         self->f_140 = a;
//         self->f_144 = b;
//         self->f_148 = c;
//         self->f_14c = d;
//         self->w_150 = 0;               // three zeroed words
//         self->w_154 = 0;
//         self->w_158 = 0;
//         self->f_15c = shared;          // the SAME register, four stores
//         self->f_160 = shared;
//         self->f_164 = shared;
//         self->f_168 = shared;
//         self->b_16c = 1;               // one byte, immediate 0x1
//         self->w_170 = 0;               // one more zeroed word
//     }
//
// Thirteen receiver writes and five global reads, straight-line, no branch, no
// call, no stack slot, no register save. Three facts about ORDER are
// load-bearing and are preserved exactly as the listing has them:
//
//   1. `MOV EAX,ECX` sits at 0x007c3f78, AFTER the first `MOVSS` load
//      (0x007c3f70) and BEFORE every store. EAX, not ECX, is the base register
//      for all thirteen stores, and the receiver is read from ECX exactly once.
//   2. `XOR ECX,ECX` sits at 0x007c3fba: it destroys the receiver register, and
//      it happens AFTER EAX has taken the receiver and AFTER the fifth global
//      load. ECX=0 is then the immediate source of the three zeroed words at
//      0x150, 0x154 and 0x158 AND of the zeroed word at 0x170, written eleven
//      instructions later. Nothing after 0x007c3fba re-reads ECX as a pointer.
//   3. The word loaded from 0x013f0620 at 0x007c3fb2 is stored FOUR times
//      (0x15c, 0x160, 0x164, 0x168) and loaded ONCE. A reconstruction that
//      re-read the global between those stores would be a different machine
//      body, and the model test's coverage is built to kill exactly that.
//
// WHY THE ENTRY TAKES ONLY THE RECEIVER, WITH NO SECOND ARGUMENT.
//
// The five loads name fixed absolute addresses, which a reconstruction cannot
// reproduce literally, so the storage they name is supplied by the host as one
// namespace-scope object (`g_global_source`) and the address of each
// word is kept as a constant. It is deliberately NOT an entry parameter: the
// derived record reports stack_arguments [] and parameter_count 0, and the body
// never reads a stack slot (esp_unresolved false, local_extent 0), so adding
// one would invent an argument the machine does not take.
//
// CALLER-SIDE CORROBORATION, AND IT IS STRONG.
//
// Four call sites read off the image put this entry immediately after an
// allocation of the same size the body's write extent implies:
//
//   0x0076adf2  PUSH 0x174              ; 372 = 0x170 + 4
//   0x0076adf7  CALL 0x00f473a0         ; the allocating helper
//   0x0076adff  MOV dword ptr [ESP+0x10],EAX
//   0x0076ae0b  TEST EAX,EAX
//   0x0076ae0d  JZ  0x0076ae18
//   0x0076ae0f  MOV ECX,EAX             ; the fresh block becomes `this`
//   0x0076ae11  CALL 0x007c3f70         ; <- this entry
//
// The same shape (PUSH 0x174 / CALL 0x00f473a0 / MOV ECX,EAX / CALL 0x007c3f70)
// appears at 0x0076ae45/0x0076ae5f, 0x0076aeb2/0x0076aec8 and
// 0x007b2cfb/0x007b2d1a. The pushed size equals the end of the highest word this
// body writes, to the byte, so the allocation size and the write extent agree.
// That is the receipt for the SHAPE -- a value initializer over a freshly
// allocated block -- and it is not a claim about any class: this binary carries
// no MSVC RTTI, so nothing here names one. A fifth site, 0x00431264/0x0043126a,
// calls the entry on a stack object (`LEA ECX,[EBP-0x178]` at 0x00431264, right
// before the call), so the initializer is not exclusive to fresh allocations.
//
// RETURN: declared `void`.
//
//   * ghidra_function reports return_type "undefined", return_type_resolved
//     false, signature "undefined FUN_007c3f70(void)", parameter_count 0, and
//     classifies the function as a leaf.
//   * The body leaves no result for a caller to consume. Every one of its four
//     XMM0-consuming stores sinks the register into the receiver; the final
//     `MOV` before the `RET` writes the zeroed word at 0x170, and the final
//     instruction that defines any register at all is the byte immediate at
//     0x007c3fee.
//   * The derived record's `return` block is `register XMM0`, `register_class
//     float_or_x87`, `type null`, confidence APPROXIMATION, and it names its own
//     basis as inference RT1, whose claim is verbatim "the return value is
//     carried in XMM0: an x87 or SSE instruction appears in the body". That is a
//     statement about a register class the record could classify, not a
//     measurement that a value is returned, and the same record carries
//     `void_possible: false`, so it does not exclude void either. `float` is NOT
//     claimed: no instruction computes a value the caller could read.
//   * The observable consequence is documented rather than asserted: XMM0 still
//     holds the word loaded from 0x013f0620 when the `RET` executes, because
//     nothing writes XMM0 after 0x007c3fb2. Whether any of the 65 call sites
//     reads it was NOT established, so the residual is an open question rather
//     than a modelled result.
//
// WHAT IS DELIBERATELY NOT CLAIMED:
//
//   * NO MEMBER NAME. The derived receiver record is `bounds_only`, so it fixes
//     only how far the body reached (13 displacements, 0x140..0x170) and never
//     which member of any type is which. Every displacement is a `constexpr`
//     value plus a displacement-named accessor over an opaque byte run, and
//     `receiver->member` appears nowhere in this package.
//   * NO RECEIVER TYPE, SHAPE, SIZE, VTABLE OR BASE CLASS. The receiver is an
//     opaque byte run, aligned 4, sized only to the end of the last word the
//     body reaches. That extent is a MODELLING BOUND, corroborated as an
//     allocation size by the four allocation sites above; nothing wider is
//     asserted, and this body never touches the bytes below the first
//     displacement, so the package does not say who initialises them.
//   * NO GLOBAL IDENTITY. The five absolute addresses are recorded as addresses
//     and as read-only source storage; what they hold is not claimed.
//     /read_memory shows 0x01635db8.. as zero bytes in the static image, but
//     those four words sit in a WRITABLE segment (`.data -wr`), so a zero in the
//     file is not a claim about the running program and none is made. 0x013f0620
//     sits in a read-only segment (`.rdata --r`) and reads as 0x461c4000, i.e.
//     10000.0f in IEEE-754 binary32; that is recorded as an observed image value
//     and is deliberately NOT baked into the source, because the body reads that
//     word at run time and a patched or relocated image would change it.
//   * NO WRITE TO ANY GLOBAL. The sidecar records five rows and every one has
//     access_mode `read`. A reconstruction that stored to one of them would be
//     claiming a write mode the artifact does not record.
//   * NO SDK NAME, NO CLASS, NO METHOD NAME. The function is `FUN_007c3f70`, the
//     subsystem tag is "Terrain", and neither is evidence of an identity.
//   * NOT __fastcall. The record keeps both conventions open and this package
//     does not close that; see UNRESOLVED in the model test header comment.
//
// NAMING: `receiver_default_block_init_007c3f70` describes the SHAPE the listing
// fixes -- a block initializer writing defaults into a receiver -- and asserts
// nothing about what the thirteen words MEAN. "default" is what a body that
// stores constants plus four externally-read words is; no field identity is
// implied. The name carries the 8-hex target VA so the validator can bind this
// span to 0x007c3f70, and it is the only symbol in the package that does.

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_007c3f70 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_007C3F70_THISCALL __thiscall
#else
#define PKG_007C3F70_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_007c3f70_receiver_default_block_init {

// The width of one `MOVSS` access: every float operand in the body is a dword
// (`F3 0F 10` / `F3 0F 11`), so four bytes, and a `MOVSS` transfers exactly
// those four and leaves the rest of the destination register alone.
using Float = float;

// The width of the three zeroed words and of the trailing zeroed word: `89 88`
// with a disp32 is a 32-bit `MOV`.
using Word = std::uint32_t;

// The width of the one byte store: `C6 80` with a disp32 is a single byte.
using Byte = std::uint8_t;

// ---------------------------------------------------------------------------
// The five absolute addresses the listing loads from, in the body's load order.
//
// The first four are named for their ADDRESS and not for any role, because the
// artifact records them only as read-mode data references into a writable
// segment: nothing says what they hold or which code fills them. The fifth is
// named for the one property the artifact does record about it -- that it lies
// in a read-only segment -- and for nothing else.
// ---------------------------------------------------------------------------
constexpr std::uint32_t kGlobalFirstWordAddress = 0x01635db8;   // MOVSS @ 0x007c3f70
constexpr std::uint32_t kGlobalSecondWordAddress = 0x01635dbc;  // MOVSS @ 0x007c3f82
constexpr std::uint32_t kGlobalThirdWordAddress = 0x01635dc0;   // MOVSS @ 0x007c3f92
constexpr std::uint32_t kGlobalFourthWordAddress = 0x01635dc4;  // MOVSS @ 0x007c3fa2
constexpr std::uint32_t kGlobalSharedReadOnlyAddress = 0x013f0620;  // MOVSS @ 0x007c3fb2

// The five load sites, in the order the body performs them. Slot 4 is the one
// load whose value is stored four times; it is also the load that happens after
// `XOR ECX,ECX` has been reached but before the zero stores consume ECX.
enum GlobalSlot : std::size_t {
  kSlotFirstWord = 0,
  kSlotSecondWord = 1,
  kSlotThirdWord = 2,
  kSlotFourthWord = 3,
  kSlotSharedReadOnly = 4,
  kSlotCount = 5,
};

// The address slot N stands for, as the machine's disp32 states it.
std::uint32_t global_slot_address(std::size_t slot);

// ---------------------------------------------------------------------------
// The thirteen receiver displacements, in listing order.
//
// Grouped only by the INSTRUCTION that writes them, never by meaning:
//   * four words each storing its own freshly loaded global (0x140..0x14c)
//   * three words each storing zero (0x150, 0x154, 0x158)
//   * four words each storing the SAME already-loaded register (0x15c..0x168)
//   * one byte storing the immediate 0x1 (0x16c)
//   * one word storing zero (0x170)
// ---------------------------------------------------------------------------
constexpr std::size_t kFieldFirstLoadedFloat = 0x140;
constexpr std::size_t kFieldSecondLoadedFloat = 0x144;
constexpr std::size_t kFieldThirdLoadedFloat = 0x148;
constexpr std::size_t kFieldFourthLoadedFloat = 0x14c;

constexpr std::size_t kFieldFirstZeroWord = 0x150;
constexpr std::size_t kFieldSecondZeroWord = 0x154;
constexpr std::size_t kFieldThirdZeroWord = 0x158;

constexpr std::size_t kFieldFirstSharedFloat = 0x15c;
constexpr std::size_t kFieldSecondSharedFloat = 0x160;
constexpr std::size_t kFieldThirdSharedFloat = 0x164;
constexpr std::size_t kFieldFourthSharedFloat = 0x168;

constexpr std::size_t kFieldFlagByte = 0x16c;
constexpr std::size_t kFieldTrailingZeroWord = 0x170;

// The immediate the byte store writes. `C6 80 6C 01 00 00 01` states 0x1.
constexpr std::uint8_t kFlagByteImmediate = 0x1;

// The highest word the body writes, and the byte extent that implies. This is a
// MODELLING BOUND; it is corroborated as an allocation size at the four call
// sites that push this same value immediately before allocating, but nothing
// wider is claimed, because this body never reaches below the first
// displacement.
constexpr std::size_t kReceiverModelledExtent =
    kFieldTrailingZeroWord + sizeof(Word);

// The receiver, opaque, 4-byte aligned, sized only to the end of the last word
// the body writes. No member is declared: the receiver record is `bounds_only`,
// so none of the displacements above is corroborated as a member of a named
// type, and naming one would be a layout claim with nothing behind it.
struct alignas(Word) OpaqueReceiver {
  std::uint8_t opaque_bytes[kReceiverModelledExtent] = {};
};

// ---------------------------------------------------------------------------
// The read-only source storage the five `MOVSS` loads name.
//
// The machine reads five fixed absolute addresses. A reconstruction cannot
// allocate at those, so the STORAGE is supplied by the host as one
// namespace-scope object while each word's address stays a constant. It exists
// to give the loads a base to be spelled against; it asserts nothing about what
// the real words hold or which code fills them, and it is the only way this
// package touches them. Every read below is `const`, because all five
// data-reference rows are access_mode `read` and no write mode is recorded.
// ---------------------------------------------------------------------------
struct alignas(Float) OpaqueGlobalSource {
  Float words[kSlotCount] = {};
};

extern OpaqueGlobalSource g_global_source;

// The one and only way this package reads a global.
Float read_global_float(std::size_t slot);

// ---------------------------------------------------------------------------
// The only three ways this package touches the receiver: a 4-byte float word, a
// 4-byte plain word, and a single byte, each at a stated displacement.
// ---------------------------------------------------------------------------
inline void store_float(OpaqueReceiver* receiver, std::size_t displacement, Float value) {
  *reinterpret_cast<Float*>(reinterpret_cast<std::uintptr_t>(receiver) + displacement) = value;
}

inline void store_word(OpaqueReceiver* receiver, std::size_t displacement, Word value) {
  *reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(receiver) + displacement) = value;
}

inline void store_byte(OpaqueReceiver* receiver, std::size_t displacement, Byte value) {
  *reinterpret_cast<Byte*>(reinterpret_cast<std::uintptr_t>(receiver) + displacement) = value;
}

// x86-32 thiscall: the receiver arrives in ECX, there is no ordinary stack
// argument at all, the terminator is a bare `RET` with no immediate so the
// callee pops nothing and the caller owns the stack, and no value is returned.
using AbiReceiverDefaultBlockInit007c3f70 = void(PKG_007C3F70_THISCALL*)(OpaqueReceiver*);

static_assert(sizeof(void*) == 4, "pointers are 32-bit");
static_assert(sizeof(Float) == 4, "MOVSS moves a 4-byte operand");
static_assert(sizeof(Word) == 4, "the zeroed words are 32-bit");
static_assert(sizeof(Byte) == 1, "the flag store is a single byte");
static_assert(sizeof(OpaqueGlobalSource) == sizeof(Float) * kSlotCount,
              "five 4-byte global words back to back");
static_assert(kSlotCount == 5, "the listing names five data addresses");

static_assert(kFieldFirstLoadedFloat == 0x140, "the first MOVSS store displacement");
static_assert(kFieldSecondLoadedFloat == 0x144, "the second MOVSS store displacement");
static_assert(kFieldThirdLoadedFloat == 0x148, "the third MOVSS store displacement");
static_assert(kFieldFourthLoadedFloat == 0x14c, "the fourth MOVSS store displacement");
static_assert(kFieldFirstZeroWord == 0x150, "the first zeroed word displacement");
static_assert(kFieldSecondZeroWord == 0x154, "the second zeroed word displacement");
static_assert(kFieldThirdZeroWord == 0x158, "the third zeroed word displacement");
static_assert(kFieldFirstSharedFloat == 0x15c, "the first shared store displacement");
static_assert(kFieldSecondSharedFloat == 0x160, "the second shared store displacement");
static_assert(kFieldThirdSharedFloat == 0x164, "the third shared store displacement");
static_assert(kFieldFourthSharedFloat == 0x168, "the fourth shared store displacement");
static_assert(kFieldFlagByte == 0x16c, "the byte store displacement");
static_assert(kFieldTrailingZeroWord == 0x170, "the trailing zeroed word displacement");
static_assert(kFlagByteImmediate == 0x1, "the byte store's immediate");

static_assert(kGlobalFirstWordAddress == 0x01635db8, "the first MOVSS load address");
static_assert(kGlobalSecondWordAddress == 0x01635dbc, "the second MOVSS load address");
static_assert(kGlobalThirdWordAddress == 0x01635dc0, "the third MOVSS load address");
static_assert(kGlobalFourthWordAddress == 0x01635dc4, "the fourth MOVSS load address");
static_assert(kGlobalSharedReadOnlyAddress == 0x013f0620, "the shared MOVSS load address");

// The first four load addresses are consecutive, which is what lets the model
// test derive each load's address from the encoded disp32 rather than restate
// it. The shared load is a different segment and is NOT consecutive with them.
static_assert(kGlobalSecondWordAddress - kGlobalFirstWordAddress == sizeof(Float),
              "the first four loads are consecutive words");
static_assert(kGlobalThirdWordAddress - kGlobalSecondWordAddress == sizeof(Float),
              "the first four loads are consecutive words");
static_assert(kGlobalFourthWordAddress - kGlobalThirdWordAddress == sizeof(Float),
              "the first four loads are consecutive words");
static_assert(kGlobalSharedReadOnlyAddress < kGlobalFirstWordAddress,
              "the shared load lies in a lower segment than the other four");

// The receiver's write extent is one past the last displacement, and the four
// allocation sites agree with it to the byte. Stated arithmetically, because the
// pushed size belongs to the CALLER's listing and is not a displacement this
// body states.
static_assert(kReceiverModelledExtent == kFieldTrailingZeroWord + 4,
              "the modelled extent is one word past the last displacement");
static_assert(kReceiverModelledExtent == sizeof(OpaqueReceiver),
              "the modelled extent is the struct size");
static_assert(kFieldTrailingZeroWord + sizeof(Word) == kReceiverModelledExtent,
              "the last word ends exactly at the modelled extent");
static_assert(kFieldFirstLoadedFloat < kFieldSecondLoadedFloat,
              "the four loaded floats ascend");
static_assert(kFieldFourthLoadedFloat + sizeof(Float) == kFieldFirstZeroWord,
              "the loaded floats are contiguous and end where the zero words begin");
static_assert(kFieldThirdZeroWord + sizeof(Word) == kFieldFirstSharedFloat,
              "the three zero words are contiguous and end where the shared stores begin");
static_assert(kFieldFourthSharedFloat + sizeof(Float) == kFieldFlagByte,
              "the four shared stores are contiguous and end where the byte store begins");
static_assert(kFieldFlagByte + 4 == kFieldTrailingZeroWord,
              "the byte store is followed by three untouched bytes, then the last word");
static_assert(std::is_same<AbiReceiverDefaultBlockInit007c3f70,
                           void(PKG_007C3F70_THISCALL*)(OpaqueReceiver*)>::value,
              "modelled entry carries the ECX receiver and returns nothing");

// Entry point under reconstruction. The name carries the 8-hex target VA so the
// validator can bind this span to 0x007c3f70, and it is the package's only
// symbol that does.
void PKG_007C3F70_THISCALL receiver_default_block_init_007c3f70(OpaqueReceiver* receiver);

}

#undef PKG_007C3F70_THISCALL