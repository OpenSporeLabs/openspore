// PKG-W2-00F9FEF0 -- VA 0x00f9fef0
// Boundary types and machine facts for the 112-instruction body at
// 0x00f9fef0..0x00fa0008 inclusive (281 bytes, SPORE/SporeBin/SporeApp.exe
// 3.1.0.22, image base 0x400000).
//
// Everything named here is named from the disassembly listing, from the
// machine-derived ABI record in reconstruction/evidence/00f9fef0/evidence.json
// (category abi_derived), or from bytes read back out of the image through the
// GhidraMCP bridge. Where the evidence abstains, this file says so instead of
// filling the gap; the gaps are listed at the bottom of the model test and each
// one is a real open question, not a placeholder.
//
// THE CALLING CONVENTION IS DETERMINED BY THE MACHINE, NOT CHOSEN HERE.
//
// reconstruction/evidence/00f9fef0/evidence.json, category abi_derived, states
// field for field:
//
//   conventions.calling_convention    : __thiscall
//   conventions.confidence            : INFERRED
//   conventions.candidate_conventions : ["__thiscall"]
//   conventions.ambiguities           : []
//   conventions.corroboration         : not_available
//
//   receiver.present         : true
//   receiver.register        : ECX
//   receiver.provenance      : vftable_slot_dispatch
//   receiver.confidence      : INFERRED
//   receiver.bounds_only     : true
//   receiver.shape           : null
//   receiver.distinct_offsets : 0
//   receiver.offsets         : []
//   receiver.written_through  : 0
//
//   cleanup.bytes    : 4     cleanup.side : callee
//   cleanup.evidence : "ret 0x4"            confidence OBSERVED
//
//   return.register      : EAX
//   return.register_class: pointer_like
//   return.confidence    : INFERRED
//   return.type          : null      return.void_possible: false
//
//   dispatch.indirect_calls      : 10
//   parse.declared_count         : 112     parse.unparsed : 0
//   parse.degraded               : false
//
// and the rules it cites, transcribed by id: C3, A1, R1-VFT, C6B, S2, RT1, RT2.
// The record's own note on its stack argument is
//
//   abstained_because: ["flow_not_modelled: the linear ESP walk ends at +60, so
//   the listing is not one path"]
//
// WHICH IS THIS PACKAGE'S MOST IMPORTANT SINGLE FACT, because the linear walk is
// exactly what gets the first stack slot wrong. See "THE FIRST POPPED STACK
// WORD" below.
//
// INFERRED, not OBSERVED: nothing in this repository has watched a caller
// dispatch through a table, and the record says so.
//
// THE RECEIVER, AND THE FIRST POPPED STACK WORD, ARE DIFFERENT VALUES. THIS
// PACKAGE KEEPS THEM APART AND THE MODEL TEST DRIVES THEM APART.
//
//   * The RECEIVER arrives in ECX. The witness is the strongest in this
//     campaign: 0x00f9fef3 `MOV EDI,ECX` copies the incoming register into EDI
//     before anything else touches it, 0x00f9fef5/0x00f9fef7 `TEST EDI,EDI` /
//     `JZ 0x00f9fefe` NULL-TEST it, and 0x00f9fef9 `LEA EBX,[EDI + 0x4]` forms
//     an interior address from it. ECX is therefore the register the vtable
//     dispatch that reaches slot 35 needed as its vtable base, which is what the
//     record's R1-VFT reasons from.
//
//   * The FIRST CALLEE-POPPED STACK WORD, at entry_ESP+0x4, is ALSO an object
//     pointer, and it is ALSO used as a vtable holder -- 0x00f9ff00
//     `MOV ESI,dword ptr [ESP + 0x10]` reads it (with the stack pointer at
//     entry_ESP-12, so [ESP+0x10] is entry_ESP+0x4), 0x00f9ff04 `MOV EAX,[ESI]`
//     loads its first word, and 0x00f9ff0b `MOV ECX,ESI` hands it in ECX to the
//     virtual call at 0x00f9ff0d. It is loaded from again at 0x00f9ff5f,
//     0x00f9ff78, 0x00f9ff91 and 0x00f9ffb2, and it is written at 0x00f9fff4.
//
//   IT IS STILL AN EXPLICIT ARGUMENT AND NOT THE RECEIVER, and the difference
//   is not a matter of taste:
//
//     - it is a STACK slot. The receiver is a REGISTER. A __thiscall receiver
//       is never on the stack, and this body's terminator pops exactly this one
//       word and no more (RET 0x4 at 0x00fa0006, bytes c2 04 00, OBSERVED), so
//       the popped area is one word wide and the receiver is not in it.
//     - the body NEVER DEREFERENCES THE RECEIVER. Every one of the eleven
//       instructions that touch EDI reads it as a register -- MOV, TEST, LEA,
//       MOV -- and not one has EDI as a memory base. The four LEA instructions
//       (0x00f9fef9, 0x00f9ff58, 0x00f9ff71, 0x00f9ff8a) form receiver+0x4 and
//       touch nothing. That is why the record reads bounds_only true with an
//       empty offsets list, and it is why no field offset is claimed in either
//       direction below.
//     - the stack word, by contrast, is dereferenced five times.
//
//   Conflating them would be the one substantive ABI error available in this
//   body, so the model test drives the two over twelve different address pairs
//   (case C), plants marker words inside BOTH objects (case B), and shows that
//   changing the popped word while holding the receiver fixed changes the answer
//   while the reverse does not (case D).
//
// THE DISPLACEMENT 0x4 IS A DISPLACEMENT AND NOT A FIELD. The four LEAs form
// receiver+0x4 and the result is only ever PUSHed as an argument (0x00f9ff65,
// 0x00f9ff7e, 0x00f9ff97) and CMPared against a callee's return value
// (0x00f9ff0f). Nothing in these 281 bytes reads or writes the byte at that
// address. It is carried here as kReceiverInteriorDisplacement, an immediate out
// of the instruction, and NO FIELD NAME AND NO LAYOUT IS ATTACHED TO IT IN
// EITHER DIRECTION: this package asserts neither a member at some offset nor
// the receiver's being flat, empty or of any size.
//
// THE FIRST POPPED STACK WORD, WHERE THE MACHINE RECORD AND THE LISTING
// DISAGREE, AND WHERE THIS PACKAGE SIDES WITH THE LISTING.
//
// The record enumerates one ordinary stack argument, entry_ESP+0x4, ordinal 1,
// observed true, sizes [4], and marks it `read: false, written: false`. The
// listing says otherwise on BOTH counts:
//
//   0x00f9ff00  8b 74 24 10   MOV ESI,dword ptr [ESP + 0x10]
//       with the stack pointer at entry_ESP-12 (three PUSHes and nothing else),
//       so [ESP+0x10] is entry_ESP+0x4. That is a READ of the slot.
//
//   0x00f9fff4  c7 44 24 04 00 00 00 00   MOV dword ptr [ESP + 0x4],0x0
//       with the stack pointer at entry_ESP (the three POPs at 0x00f9fff1,
//       0x00f9fff2 and 0x00f9fff3 have just restored it), so [ESP+0x4] is
//       entry_ESP+0x4 again. That is a WRITE of the slot, of the constant 0,
//       and it is the last thing the main path does before it tail-transfers.
//
// The record's own abstention explains the divergence exactly. A linear ESP walk
// cannot see what a branch does to the stack pointer, so it walked the body
// straight through, ended at +60, and reported the slot's state from the
// terminal immediate alone. The record is not corrected here -- this package
// does not own that file and did not touch it -- and the divergence is recorded
// as an unresolved question instead. What the LISTING supports is carried as
// kFirstStackArgumentRead / kFirstStackArgumentWritten below, and the model test
// checks both against literals written independently in the test (case J) and
// then MEASURES them (case K: the caller's pushed word is read back by the
// reconstruction's own dispatch, and the zero the body writes there is observed
// by the tail callee).
//
// THE STACK DISCIPLINE, AND EXACTLY HOW MUCH OF IT THE EVIDENCE SETTLES.
//
// This section replaces an earlier draft of this header that claimed the frame
// balance "admits exactly one assignment" for the ten indirect transfers' callees
// and published the whole table. THAT CLAIM WAS WRONG and is withdrawn: an
// exhaustive search over releases that are multiples of four finds 156
// assignments that close BOTH epilogues and the tail transfer. What follows is
// only what survives that search, and the rest is named as undetermined.
//
// THREE THINGS FIX THE MODEL. None of them is a modelling choice.
//
//   1. Entry_ESP is the stack pointer on entry. The prologue is three PUSHes
//      (0x00f9fef0 EBX, 0x00f9fef1 ESI, 0x00f9fef2 EDI) and nothing else, so
//      the pointer is entry_ESP-12 at 0x00f9ff00, which is what makes that
//      instruction's [ESP+0x10] equal to entry_ESP+0x4.
//
//   2. BOTH epilogues are the same three words. 0x00f9fff1..0x00f9fff3 and
//      0x00fa0003..0x00fa0005 are both POP EDI / POP ESI / POP EBX, restoring
//      the prologue's three pushes in reverse order, so the stack pointer must
//      read entry_ESP-12 at both. After those three POPs it reads entry_ESP, and
//      at 0x00f9fff4 the body writes [ESP+0x4] -- entry_ESP+0x4, the first
//      popped word -- and at 0x00fa0001 it JMPs with the stack pointer at
//      entry_ESP, which is exactly the shape a tail call needs: the callee's
//      return address is this body's own return address, and its first stack
//      argument is the zero just written. The early-out then RETs 0x4 with the
//      stack pointer at entry_ESP, which pops the return address and the same
//      word, leaving the caller at entry_ESP+4.
//
//   3. The five DIRECT callees' own terminators were read out of the image:
//
//        0x006a25a0  006a2652 C2 04 00   RET 0x4          releases  4
//        0x00f96b40  00f96b40 SUB ESP,0x8 / 00f96b43 PUSH ESI
//                    ... 00f96c4e POP ESI / 00f96c4f ADD ESP,0x8
//                        00f96c52 C3                        releases  0
//        0x00f9e3a0  00f9e3a0 PUSH EBX/ESI/EDI
//                    ... 00f9e4c1 POP EDI/ESI/EBX
//                        00f9e4c4 C3                        releases  0
//        0x0067dd80  0067dd80 A1 CC D8 5F 01 / 0067dd85 C3 releases  0
//        0x0067ddd0  0067ddd0 A1 94 D8 5F 01 / 0067ddd5 C3 releases  0
//
//      `release` is the NET number of bytes a callee hands back to its caller
//      beyond the return address it pops, so an ordinary callee that cleans one
//      pushed word releases 4 and a cdecl one releases 0. 0x00f96b40's `SUB
//      ESP,0x8` and `ADD ESP,0x8` cancel around its own frame, which is why it
//      releases 0 and not 12 -- reading its ADD ESP,0x8 as a pop of this body's
//      would be a mistake, and this package made it once before checking.
//
// WHAT THE BALANCE FORCES. The early-out epilogue leaves exactly one transfer
// between it and the prologue: the slot-0x58 call at 0x00f9ff0d, handed one
// pushed word. Requiring the stack pointer to read entry_ESP-12 at 0x00fa0003
// therefore pins its release at 4 bytes, and that one figure is the same in all
// 156 closing assignments. It is the only virtual callee's release the evidence
// determines.
//
// WHAT THE BALANCE ALSO FORCES, AND THIS IS THE SHARPEST FACT IN THE PACKAGE.
// The spill at 0x00f9ff38 and the test at 0x00f9ff46 name THE SAME BYTE, and
// that byte is entry_ESP+0x4 -- the first callee-popped stack word:
//
//   0x00f9ff38  88 44 24 14   MOV byte ptr [ESP + 0x14],AL   with ESP = entry_ESP-16
//   0x00f9ff46  80 7c 24 10 00 CMP byte ptr [ESP + 0x10],0   with ESP = entry_ESP-12
//
// entry_ESP-16 + 0x14 is entry_ESP+4 and entry_ESP-12 + 0x10 is entry_ESP+4, and
// the second of those two stack-pointer values
// depends only on releases this package has read out of the image (the two
// 0x006a25a0 words and 0x00f96b40's own frame), so the coincidence is not an
// artefact of an unknown. So the body SPILLS the low byte of the second
// 0x006a25a0 answer into its own first stack argument slot and then BRANCHES ON
// IT to decide whether 0x00f9e3a0 is reached. That is a byte-level consequence of
// two instructions and it is what the model test measures in case F.
//
// WHAT THE BALANCE DOES NOT DETERMINE. The releases of the other six virtual
// callees. A callee resolved through a table slot at run time has no terminator
// in this image at this address, and the six figures are constrained only by
// their SUM -- the 156 closing assignments differ in six numbers at a time. This
// package therefore publishes no table for them. The model test's stubs pop what
// the table below says, that table is a MODELLING CHOICE about seven functions
// this body does not own, and the model test says so where it is defined. A
// reader who prefers a different assignment changes seven numbers in one place
// and nothing else.
//
//   slot 0x58   stub releases  4   (the one figure the balance forces)
//   slot 0x4c   stub releases  8   -- given three words three times and one once
//   slot 0x1c   stub releases  4
//   slot 0x13c  stub releases  8
//   slot 0x134  stub releases  4
//   slot 0x54   stub releases 12   -- carries the correction the 0x4c stub's
//                                      three-word cases leave behind
//   slot 0xc    stub releases  4   -- the TAIL callee; see the note below
//
// The tail callee's release is not determined by this body either. This body hands
// it a stack pointer at entry_ESP and one zeroed word, and whether it consumes
// that word is its own business; `ret $4` is the model's choice and nothing in
// the reconstruction depends on it.
//
// One more reading the balance supports and the listing shows directly: the
// fourth slot-0x4c call, at 0x00f9ffcc, is handed ONE word where the other three
// are handed three. The model test reports what its stub actually received rather
// than asserting a value the listing does not determine.

// THE TEN INDIRECT TRANSFERS AND THE SEVEN SLOTS THEY REACH. Each is
// `MOV EAX/EDX,[EDX+slot]` (or `[EAX+slot]`) followed by `MOV ECX,<object>` and
// `CALL EAX/EDX`, except the last, which is `JMP EAX`. The slot displacements
// are immediates out of those instructions and nothing more: no class, no slot
// boundary, no vtable identity and no member name is claimed for any of them,
// and the binary carries no MSVC RTTI for this target (ghidra_function reports
// ghidra_has_calling_convention false and ghidra_calling_convention_signal
// "no_information"). The record's own vtable projection names one table for
// this address; the model test records that fact and dispatches only through
// tables it builds itself.
//
// THE ONE DATA ADDRESS. 0x00f9ff18 `MOV EBP,dword ptr [0x015fd918]` is the only
// data-segment operand in the 281 bytes. It is a four-byte LOAD: the word is
// used as the ECX of both 0x006a25a0 calls and is never written. What the word
// holds, and whether it is a pointer, is not established here.
//
// THE RETURN. There are two exits and they are not the same shape, and the
// record's single `return_register: EAX` describes only the first:
//
//   * The EARLY-OUT at 0x00fa0003 returns. EAX is compared against EBX at
//     0x00f9ff0f and the branch is TAKEN only when they are equal, so on that
//     path EAX IS the interior pointer: receiver+0x4 when the receiver is
//     non-null, and 0 when it is null. That is a byte-level consequence of
//     CMP-then-JZ and the model test checks it (case A) with the receiver both
//     non-null and null.
//
//   * The MAIN path does not return at all. It ends in a TAIL TRANSFER: the
//     0x00fa0001 JMP EAX is not a call, so EAX becomes the tail callee's
//     register-carried receiver and whatever the tail callee returns is what
//     this body's caller receives. No value is returned "by" this body on that
//     path, and the model test proves the transfer happened by handing the tail
//     slot a distinguishable stub (case G).
//
// The declared return type is `Word *`. That is a source-side spelling of a
// four-byte pointer-shaped value, chosen because the early-out's value is an
// interior address; the machine fixes the register, the width and the
// pointer-shaped class (return.register EAX, return.register_class pointer_like,
// confidence INFERRED under RT1 and RT2) and not the spelling.

#ifndef RECONSTRUCTION_STAGING_PKG_W2_00F9FEF0_W2_00F9FEF0_TYPES_HPP_
#define RECONSTRUCTION_STAGING_PKG_W2_00F9FEF0_W2_00F9FEF0_TYPES_HPP_

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-w2-00f9fef0 requires an x86-32 target"
#endif

// The convention is spelled once, here, and the reconstructed entry names the
// macro.
//
//   PKG_W2_00F9FEF0_THISCALL        the convention on an ordinary declarable
//                                   function. It is what the model test gives
//                                   the five direct callees, each entered
//                                   exactly as the image enters it.
//   PKG_W2_00F9FEF0_NAKED_THISCALL  the same convention on the naked,
//                                   byte-faithful transcription of the target's
//                                   own 281 bytes.
//
// GCC rejects the bare MSVC keyword in the attribute position on some versions,
// so the attribute form is the portable spelling and the keyword form is kept
// for MSVC. Either way the token `thiscall` is carried once per macro, which is
// what the validator's convention resolution follows.
#if defined(_MSC_VER)
#define PKG_W2_00F9FEF0_THISCALL __thiscall
#define PKG_W2_00F9FEF0_NAKED_THISCALL __declspec(naked) __thiscall
#else
#define PKG_W2_00F9FEF0_THISCALL __attribute__((thiscall))
#define PKG_W2_00F9FEF0_NAKED_THISCALL __attribute__((naked, thiscall))
#endif

// The word this model moves around. A 32-bit slot is a machine fact at every
// place it is used; the C spelling is this package's choice.
using Word = std::uint32_t;

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00f9fef0 {

// -- identity ----------------------------------------------------------------

// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind the source span to 0x00f9fef0.
inline constexpr std::uint32_t kTargetVa = 0x00f9fef0u;
inline constexpr std::uint32_t kBodyFirstByte = 0x00f9fef0u;
// The terminator RET 0x4 at 0x00fa0006 is c2 04 00 and occupies
// 0x00fa0006..0x00fa0008, so the LAST byte of the body is 0x00fa0008 and the
// exclusive end is 0x00fa0009. ghidra_function.body_end names 0x00fa0008 and
// body_span_bytes names 281, which is 0x119.
inline constexpr std::uint32_t kBodyLastByte = 0x00fa0008u;
inline constexpr std::uint32_t kBodyEndExclusive = 0x00fa0009u;
// The live read at 0x00f9fef0 shows 0xCC inter-function padding behind the body.
inline constexpr std::uint8_t kInterFunctionPad = 0xCCu;

// -- the two carriers, and only these two ------------------------------------

// The RECEIVER. Declared and left UNDEFINED on purpose: the body never
// dereferences it -- it copies it, null-tests it, forms receiver+0x4 four times
// and hands that address to callees -- so its size, layout, members, vtable
// pointer offset and object identity are all unproven, and an empty definition
// here would be a claim that there are no members rather than a statement that
// none was observed.
struct Receiver;

// The FIRST CALLEE-POPPED STACK WORD. Also declared and left UNDEFINED: the
// body reads its first dword and reloads it five times, so it is an object
// pointer, but nothing here establishes its type, size or identity either.
struct Argument;

// The one displacement the body forms from the receiver, LEA with +0x4 at
// 0x00f9fef9, 0x00f9ff58, 0x00f9ff71 and 0x00f9ff8a. It is an immediate out of
// those instructions and nothing is ever read or written there, so no field and
// no layout is claimed in either direction.
inline constexpr std::size_t kReceiverInteriorDisplacement = 0x4u;
inline constexpr int kReceiverInteriorLeaCount = 4;

// How many times the body reads the receiver register itself: eleven
// instructions, at 0x00f9fef3, 0x00f9fef5, 0x00f9fef7 (its flag), 0x00f9fef9,
// 0x00f9ff4d, 0x00f9ff54, 0x00f9ff56, 0x00f9ff6d, 0x00f9ff71, 0x00f9ff86 and
// 0x00f9ff8a. Every one of them uses EDI as a register; not one uses it as a
// memory base.
inline constexpr int kReceiverRegisterReads = 11;
// How many times the body loads or stores THROUGH the receiver: never.
inline constexpr int kReceiverDereferenceCount = 0;
// The honest form of the two facts above: the body shows no offset, so this
// package claims none -- neither a field at some offset nor the receiver's being
// flat. `false` here means "not claimed", NOT "there is no field".
inline constexpr bool kReceiverFieldOffsetClaimed = false;

// The first popped stack word, at entry_ESP+0x4. Read at 0x00f9ff00 and written
// at 0x00f9fff4; the machine record says read false and written false, and the
// note at the top of this file says why, and reports the divergence rather than
// resolving it.
inline constexpr std::size_t kFirstStackArgumentEntryOffset = 0x4u;
inline constexpr std::uint32_t kFirstStackArgumentReadFrom = 0x00f9ff00u;
inline constexpr std::uint32_t kFirstStackArgumentWrittenFrom = 0x00f9fff4u;
inline constexpr std::size_t kFirstStackArgumentBytes = 4;
inline constexpr int kStackArgumentSlots = 1;
inline constexpr bool kFirstStackArgumentRead = true;
inline constexpr bool kFirstStackArgumentWritten = true;
// How many times the body dereferences it: five, at 0x00f9ff04, 0x00f9ff5f,
// 0x00f9ff78, 0x00f9ff91 and 0x00f9ffb2. This is the asymmetry the whole
// receiver/argument separation rests on: eleven register reads of the receiver
// and no dereference, against five dereferences of this.
inline constexpr int kFirstStackArgumentDereferenceCount = 5;
// The record's own, contradicted-on-both-counts reading, kept so the divergence
// is pinned by a check rather than only by prose.
inline constexpr bool kRecordSaysFirstStackArgumentRead = false;
inline constexpr bool kRecordSaysFirstStackArgumentWritten = false;
// The stack pointer is 12 bytes below the entry value at 0x00f9ff00, which is
// what makes that instruction's [ESP+0x10] equal to entry_ESP+0x4.
inline constexpr std::size_t kPrologueBytes = 12;
inline constexpr std::size_t kSavedRegisterCount = 3;
inline constexpr std::size_t kSavedRegisterEbx = 0x00f9fef0u;
inline constexpr std::size_t kSavedRegisterEsi = 0x00f9fef1u;
inline constexpr std::size_t kSavedRegisterEdi = 0x00f9fef2u;
inline constexpr std::size_t kSavedRegisterEbp = 0x00f9ff17u;
inline constexpr std::size_t kSavedRegisterCountTotal = 4;

// -- the ten indirect transfers, and the seven slots they reach -------------

inline constexpr int kIndirectTransferCount = 10;
inline constexpr int kIndirectCallCount = 9;
inline constexpr int kTailTransferCount = 1;
// The slot displacements, in the order the body reaches them. Each is the
// immediate of a `MOV reg,[reg+slot]`.
inline constexpr std::size_t kSlotDisplacements[] = {0x58u, 0x4cu, 0x1cu, 0x13cu,
                                                     0x134u, 0x54u, 0x0cu};
inline constexpr std::size_t kSlotDisplacementCount = 7u;
// How many transfers reach each of them: 0x58 once, 0x4c four times, and each
// of the other five once. 1 + 4 + 5 = 10.
inline constexpr int kSlotReachCounts[] = {1, 4, 1, 1, 1, 1, 1};
// The body itself records the agreement: the machine dispatch record counts ten
// indirect transfers and the listing has ten, so the two machine sources are
// not describing a slice.
inline constexpr int kMachineDispatchIndirectCalls = 10;

// -- the stack discipline: what is observed, what is forced, what is not -----
//
// The five direct callees' net releases, read out of the image. `pop_read` is
// true for all five and false for nothing in this table, because nothing in it is
// derived.
struct DirectCallee {
  std::uint32_t address;
  std::size_t release_bytes;
  const char* terminator;
};
inline constexpr DirectCallee kDirectCallees[] = {
    {0x006a25a0u, 4u, "006a2652  C2 04 00   RET 0x4"},
    {0x00f96b40u, 0u, "00f96b40  SUB ESP,0x8 / PUSH ESI ... POP ESI / ADD ESP,0x8 / C3"},
    {0x00f9e3a0u, 0u, "00f9e3a0  PUSH EBX/ESI/EDI ... POP EDI/ESI/EBX / C3"},
    {0x0067dd80u, 0u, "0067dd80  A1 CC D8 5F 01 / C3"},
    {0x0067ddd0u, 0u, "0067ddd0  A1 94 D8 5F 01 / C3"},
};
inline constexpr std::size_t kDirectCalleeCount = 5u;
inline constexpr int kDirectCallSiteCount = 6;
inline constexpr std::size_t kDirectReleasesTotal = 8u;  // 4 + 4, the two 0x006a25a0 calls

// The ONE virtual release the frame balance forces: the early-out epilogue
// leaves only the slot-0x58 call between it and the prologue, and it requires
// the stack pointer to read entry_ESP-12 at 0x00fa0003.
inline constexpr std::size_t kSlot58ForcedRelease = 4u;
inline constexpr std::uint32_t kSlot58CallSite = 0x00f9ff0du;
inline constexpr std::size_t kSlot58PushedBytes = 4u;

// The other six virtual releases, and the tail's. NOT DETERMINED by the evidence.
// `is_modelling_choice` is true for every row, without exception, and the model
// test says the same in the comment above each stub.
inline constexpr std::size_t kModelStubRelease[] = {4u, 8u, 4u, 8u, 4u, 12u, 4u};
inline constexpr std::size_t kModelStubReleaseCount = 7u;
inline constexpr std::size_t kClosingAssignmentsFound = 156u;
inline constexpr std::size_t kUndeterminedVirtualReleases = 6u;

// The spill and the test that read the same byte of the first popped stack word.
inline constexpr std::size_t kSpillDisplacement = 0x14u;   // 0x00f9ff38
inline constexpr std::size_t kTestDisplacement = 0x10u;    // 0x00f9ff46
inline constexpr std::size_t kSpillEspFromEntry = 0x10u;   // 16 bytes below
inline constexpr std::size_t kTestEspFromEntry = 0x0cu;    // 12 bytes below
inline constexpr std::uint32_t kSpillAt = 0x00f9ff38u;
inline constexpr std::uint32_t kTestAt = 0x00f9ff46u;
inline constexpr std::size_t kSpillAndTestAddress = 4u;    // entry_ESP + 4, both
inline constexpr int kBranchGovernedByTheSpill = 1;       // 0x00f9ff4b JZ 0x00f9ff54

// The immediates the body pushes, as an immediate is an immediate. Each is out
// of the named instruction and is checked against a literal written separately
// in the model test.
inline constexpr Word kPushedWordSlot58 = 0x8u;      // 0x00f9ff09
inline constexpr Word kPushedKeyFirst = 0x201a4e50u;  // 0x00f9ff1e
inline constexpr Word kPushedKeySecond = 0xe13ce337u; // 0x00f9ff2a
inline constexpr Word kPushedSecondCall7 = 0x7u;      // 0x00f9ff63
inline constexpr Word kPushedSecondCall8 = 0x8u;      // 0x00f9ff7c
inline constexpr Word kPushedSecondCall21 = 0x21u;    // 0x00f9ff95
inline constexpr Word kPushedSlot1c = 0x3fbae24u;     // 0x00f9ffab
inline constexpr Word kPushedSlot13c10 = 0xau;       // 0x00f9ffc0
inline constexpr Word kPushedSlot134 = 0x1u;         // 0x00f9ffd6
inline constexpr Word kPushedSlot54 = 0x3fbae24u;     // 0x00f9ffe8
inline constexpr Word kWrittenStackSlotValue = 0x0u;   // 0x00f9fff4
inline constexpr std::size_t kPushedZeroCount = 4u;    // 0x00f9ff61,7a,93,be

// -- extent, restated from the 112 instructions -----------------------------

inline constexpr int kInstructionCount = 112;
inline constexpr std::size_t kBodySpanBytes = 281;
// Both epilogues are POP EDI / POP ESI / POP EBX, so the body has exactly two.
inline constexpr int kEpilogueBlockCount = 2;
inline constexpr int kConditionalBranches = 7;
inline constexpr int kUnconditionalIntraBodyJumps = 4;
inline constexpr int kGlobalReferences = 1;
inline constexpr std::uint32_t kGlobalAddress = 0x015fd918u;
inline constexpr std::uint32_t kGlobalReadFrom = 0x00f9ff18u;

// -- the machine-derived ABI, carried as DATA -------------------------------
//
// Every value below is transcribed from the evidence pack's `abi_derived`
// category and from nothing else. They are data rather than prose so that
// changing one is a change the model test can catch, and so a package that
// quietly reverted to the old abstention -- "no convention, no receiver" --
// fails the model test instead of passing it.

enum class ConventionVerdict00f9fef0 : int { kThiscall = 0 };

enum class ConventionConfidence : int {
  kUnknown = 0,
  kInferred = 1,
  kObserved = 2
};

enum class ReceiverRegister00f9fef0 : int { kEcx = 0 };

enum class ReceiverProvenance00f9fef0 : int { kVftableSlotDispatch = 0 };

enum class CleanupSide00f9fef0 : int { kCallee = 0 };

enum class ReturnRegisterClass00f9fef0 : int { kPointerLike = 0 };

inline constexpr ConventionVerdict00f9fef0 kDerivedConventionVerdict =
    ConventionVerdict00f9fef0::kThiscall;
inline constexpr ConventionConfidence kDerivedConventionConfidence =
    ConventionConfidence::kInferred;
inline constexpr int kCandidateConventionCount = 1;
inline constexpr int kConventionAmbiguityCount = 0;

inline constexpr ReceiverRegister00f9fef0 kDerivedReceiverRegister =
    ReceiverRegister00f9fef0::kEcx;
inline constexpr ReceiverProvenance00f9fef0 kReceiverProvenance =
    ReceiverProvenance00f9fef0::kVftableSlotDispatch;
inline constexpr bool kReceiverPresent = true;
inline constexpr bool kReceiverBoundsOnly = true;
inline constexpr bool kReceiverHasShape = false;
inline constexpr int kReceiverRecordDistinctOffsets = 0;
inline constexpr int kReceiverRecordWrittenThrough = 0;

// Separately OBSERVED, and independent of the convention: the terminator's own
// form is RET 0x4.
inline constexpr CleanupSide00f9fef0 kObservedCleanupSide =
    CleanupSide00f9fef0::kCallee;
inline constexpr std::size_t kRetImmediateBytes = 4;
inline constexpr std::size_t kStackCleanupBytes = 4;
inline constexpr std::uint8_t kRetImmediateLowByte = 0x04u;
inline constexpr std::uint8_t kRetImmediateHighByte = 0x00u;
inline constexpr std::uint32_t kRetImmediateAt = 0x00fa0006u;
// What a CALL pushes on top of the terminator's immediate: the return address.
// The model test needs it because a post-call stack sample sits FOUR bytes above
// entry_ESP + kRetImmediateBytes, not on it -- `ret imm16` pops the return
// address first and only then adds its immediate -- and a harness that forgets
// this reads the body's frame four bytes high.
inline constexpr std::uint32_t kReturnAddressBytes = 4u;
inline constexpr std::size_t kEspImmediatelyAfterTheCall = 4u;

inline constexpr int kReturnRegisterId = 0;  // ModRM reg field: 0 is EAX
inline constexpr ReturnRegisterClass00f9fef0 kReturnRegisterClass =
    ReturnRegisterClass00f9fef0::kPointerLike;
inline constexpr ConventionConfidence kReturnConfidence =
    ConventionConfidence::kInferred;
inline constexpr std::size_t kReturnWidthBytes = 4;
inline constexpr bool kVoidPossible = false;

// The parse record, and the integrity figure the model test checks.
inline constexpr int kMachineParseDeclaredCount = 112;
inline constexpr int kMachineParseUnparsed = 0;
inline constexpr bool kMachineParseDegraded = false;
inline constexpr bool kMachineParseFlowComplete = false;

// The abstention the record itself carries, kept as data because it is the
// reason this package and the record disagree about the first stack slot.
inline constexpr const char* kAbstainedBecause =
    "flow_not_modelled: the linear ESP walk ends at +60, so the listing is not "
    "one path";

// -- the five direct callees, declared as the model's own out-of-line calls ----
//
// Their addresses are in their names, which is the convention the validator
// reads to compare a source's call set against the xref export. Each is entered
// exactly the way the listing enters it, and each one's stack effect was read
// back out of the same image:
//
//   0x006a25a0  ECX = the word read from 0x015fd918; one pushed word
//               (0x201a4e50 then 0xe13ce337); RET 0x4. Returns a value whose
//               low byte AL is taken twice: into BL at 0x00f9ff31, and into the
//               scratch byte at 0x00f9ff38.
//   0x00f96b40  no register is set before the call and nothing is pushed; plain
//               RET, so it costs its caller nothing. Its return value is not
//               used.
//   0x00f9e3a0  ECX = the receiver copy in EDI; nothing is pushed; plain RET.
//               Its return value is not used.
//   0x0067dd80  nothing is set and nothing is pushed; plain RET; returns a
//               pointer in EAX, which 0x00f9ffa4 immediately dereferences.
//   0x0067ddd0  the same shape as 0x0067dd80, one call later.
//
// The declared types describe the shape the image enters them with. They are
// NOT claims about those functions' real signatures: the return values of
// 0x00f96b40 and 0x00f9e3a0 are discarded by this body, so nothing here says
// they return void.
extern "C" Word PKG_W2_00F9FEF0_THISCALL callee_006a25a0(Word* self, Word key);
extern "C" void callee_00f96b40();
extern "C" void PKG_W2_00F9FEF0_THISCALL callee_00f9e3a0(Receiver* receiver);
extern "C" Word* callee_0067dd80();
extern "C" Word* callee_0067ddd0();

// The one data address the body reads. Declared here and DEFINED BY THE MODEL
// TEST, which is what supplies the word the body loads; the reconstruction does
// not own the value and says nothing about what it holds.
extern "C" Word g_015fd918;

// -- the 281 bytes, transcribed from the image --------------------------------
//
// GhidraMCP /read_memory at 0x00f9fef0 for 288 bytes returns the byte string
// this table is transcribed from (the first 281, then eight 0xCC padding
// bytes), and /disassemble_function at 0x00f9fef0 returns exactly the 112
// instructions at exactly the addresses in the trailing comments, consuming all
// 281 bytes with nothing left over. Every displacement was checked against that
// byte string: the CALL rel32 at 0x00f9ff25 is e8 76 26 70 ff, next-instruction
// 0x00f9ff2a plus signed -0x8fda8a lands on 0x006a25a0; the one at 0x00f9ff33
// is e8 68 26 70 ff, next 0x00f9ff38 plus signed -0x8fd998 lands on 0x006a25a0;
// the one at 0x00f9ff41 is e8 fa 6b ff ff, next 0x00f9ff46 plus signed -0x9406
// lands on 0x00f96b40; the one at 0x00f9ff4f is e8 4c e4 ff ff, next 0x00f9ff54
// plus signed -0x1bb4 lands on 0x00f9e3a0; the one at 0x00f9ff9f is e8 dc dd
// 6d ff, next 0x00f9ffa4 plus signed -0x92224 lands on 0x0067dd80; the one at
// 0x00f9ffdc is e8 ef dd 6d ff, next 0x00f9ffe1 plus signed -0x92211 lands on
// 0x0067ddd0. The absolute data displacement at 0x00f9ff18 is 18 d9 5f 01,
// which is 0x015fd918.
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x53,                          // 00f9fef0  PUSH EBX
    0x56,                          // 00f9fef1  PUSH ESI
    0x57,                          // 00f9fef2  PUSH EDI
    0x8b, 0xf9,                    // 00f9fef3  MOV EDI,ECX
    0x85, 0xff,                    // 00f9fef5  TEST EDI,EDI
    0x74, 0x05,                    // 00f9fef7  JZ 0x00f9fefe
    0x8d, 0x5f, 0x04,              // 00f9fef9  LEA EBX,[EDI+0x4]
    0xeb, 0x02,                    // 00f9fefc  JMP 0x00f9ff00
    0x33, 0xdb,                    // 00f9fefe  XOR EBX,EBX
    0x8b, 0x74, 0x24, 0x10,        // 00f9ff00  MOV ESI,[ESP+0x10]
    0x8b, 0x06,                    // 00f9ff04  MOV EAX,[ESI]
    0x8b, 0x50, 0x58,              // 00f9ff06  MOV EDX,[EAX+0x58]
    0x6a, 0x08,                    // 00f9ff09  PUSH 0x8
    0x8b, 0xce,                    // 00f9ff0b  MOV ECX,ESI
    0xff, 0xd2,                    // 00f9ff0d  CALL EDX
    0x3b, 0xc3,                    // 00f9ff0f  CMP EAX,EBX
    0x0f, 0x84, 0xec, 0x00, 0x00, 0x00, // 00f9ff11  JZ 0x00fa0003
    0x55,                          // 00f9ff17  PUSH EBP
    0x8b, 0x2d, 0x18, 0xd9, 0x5f, 0x01, // 00f9ff18  MOV EBP,[0x015fd918]
    0x68, 0x50, 0x4e, 0x1a, 0x20,  // 00f9ff1e  PUSH 0x201a4e50
    0x8b, 0xcd,                    // 00f9ff23  MOV ECX,EBP
    0xe8, 0x76, 0x26, 0x70, 0xff,  // 00f9ff25  CALL 0x006a25a0
    0x68, 0x37, 0xe3, 0x3c, 0xe1,  // 00f9ff2a  PUSH 0xe13ce337
    0x8b, 0xcd,                    // 00f9ff2f  MOV ECX,EBP
    0x8a, 0xd8,                    // 00f9ff31  MOV BL,AL
    0xe8, 0x68, 0x26, 0x70, 0xff,  // 00f9ff33  CALL 0x006a25a0
    0x88, 0x44, 0x24, 0x14,        // 00f9ff38  MOV [ESP+0x14],AL
    0x5d,                          // 00f9ff3c  POP EBP
    0x84, 0xdb,                    // 00f9ff3d  TEST BL,BL
    0x74, 0x13,                    // 00f9ff3f  JZ 0x00f9ff54
    0xe8, 0xfa, 0x6b, 0xff, 0xff,  // 00f9ff41  CALL 0x00f96b40
    0x80, 0x7c, 0x24, 0x10, 0x00,  // 00f9ff46  CMP [ESP+0x10],0
    0x74, 0x07,                    // 00f9ff4b  JZ 0x00f9ff54
    0x8b, 0xcf,                    // 00f9ff4d  MOV ECX,EDI
    0xe8, 0x4c, 0xe4, 0xff, 0xff,  // 00f9ff4f  CALL 0x00f9e3a0
    0x85, 0xff,                    // 00f9ff54  TEST EDI,EDI
    0x74, 0x05,                    // 00f9ff56  JZ 0x00f9ff5d
    0x8d, 0x47, 0x04,              // 00f9ff58  LEA EAX,[EDI+0x4]
    0xeb, 0x02,                    // 00f9ff5b  JMP 0x00f9ff5f
    0x33, 0xc0,                    // 00f9ff5d  XOR EAX,EAX
    0x8b, 0x16,                    // 00f9ff5f  MOV EDX,[ESI]
    0x6a, 0x00,                    // 00f9ff61  PUSH 0x0
    0x6a, 0x07,                    // 00f9ff63  PUSH 0x7
    0x50,                          // 00f9ff65  PUSH EAX
    0x8b, 0x42, 0x4c,              // 00f9ff66  MOV EAX,[EDX+0x4c]
    0x8b, 0xce,                    // 00f9ff69  MOV ECX,ESI
    0xff, 0xd0,                    // 00f9ff6b  CALL EAX
    0x85, 0xff,                    // 00f9ff6d  TEST EDI,EDI
    0x74, 0x05,                    // 00f9ff6f  JZ 0x00f9ff76
    0x8d, 0x47, 0x04,              // 00f9ff71  LEA EAX,[EDI+0x4]
    0xeb, 0x02,                    // 00f9ff74  JMP 0x00f9ff78
    0x33, 0xc0,                    // 00f9ff76  XOR EAX,EAX
    0x8b, 0x16,                    // 00f9ff78  MOV EDX,[ESI]
    0x6a, 0x00,                    // 00f9ff7a  PUSH 0x0
    0x6a, 0x08,                    // 00f9ff7c  PUSH 0x8
    0x50,                          // 00f9ff7e  PUSH EAX
    0x8b, 0x42, 0x4c,              // 00f9ff7f  MOV EAX,[EDX+0x4c]
    0x8b, 0xce,                    // 00f9ff82  MOV ECX,ESI
    0xff, 0xd0,                    // 00f9ff84  CALL EAX
    0x85, 0xff,                    // 00f9ff86  TEST EDI,EDI
    0x74, 0x05,                    // 00f9ff88  JZ 0x00f9ff8f
    0x8d, 0x47, 0x04,              // 00f9ff8a  LEA EAX,[EDI+0x4]
    0xeb, 0x02,                    // 00f9ff8d  JMP 0x00f9ff91
    0x33, 0xc0,                    // 00f9ff8f  XOR EAX,EAX
    0x8b, 0x16,                    // 00f9ff91  MOV EDX,[ESI]
    0x6a, 0x00,                    // 00f9ff93  PUSH 0x0
    0x6a, 0x21,                    // 00f9ff95  PUSH 0x21
    0x50,                          // 00f9ff97  PUSH EAX
    0x8b, 0x42, 0x4c,              // 00f9ff98  MOV EAX,[EDX+0x4c]
    0x8b, 0xce,                    // 00f9ff9b  MOV ECX,ESI
    0xff, 0xd0,                    // 00f9ff9d  CALL EAX
    0xe8, 0xdc, 0xdd, 0x6d, 0xff,  // 00f9ff9f  CALL 0x0067dd80
    0x8b, 0x10,                    // 00f9ffa4  MOV EDX,[EAX]
    0x8b, 0xc8,                    // 00f9ffa6  MOV ECX,EAX
    0x8b, 0x42, 0x1c,              // 00f9ffa8  MOV EAX,[EDX+0x1c]
    0x68, 0x24, 0xae, 0xfb, 0x03,  // 00f9ffab  PUSH 0x3fbae24
    0xff, 0xd0,                    // 00f9ffb0  CALL EAX
    0x8b, 0x1e,                    // 00f9ffb2  MOV EBX,[ESI]
    0x8b, 0xf8,                    // 00f9ffb4  MOV EDI,EAX
    0x8b, 0x17,                    // 00f9ffb6  MOV EDX,[EDI]
    0x8b, 0x82, 0x3c, 0x01, 0x00, 0x00, // 00f9ffb8  MOV EAX,[EDX+0x13c]
    0x6a, 0x00,                    // 00f9ffbe  PUSH 0x0
    0x6a, 0x0a,                    // 00f9ffc0  PUSH 0xa
    0x8b, 0xcf,                    // 00f9ffc2  MOV ECX,EDI
    0xff, 0xd0,                    // 00f9ffc4  CALL EAX
    0x8b, 0x53, 0x4c,              // 00f9ffc6  MOV EDX,[EBX+0x4c]
    0x50,                          // 00f9ffc9  PUSH EAX
    0x8b, 0xce,                    // 00f9ffca  MOV ECX,ESI
    0xff, 0xd2,                    // 00f9ffcc  CALL EDX
    0x8b, 0x07,                    // 00f9ffce  MOV EAX,[EDI]
    0x8b, 0x90, 0x34, 0x01, 0x00, 0x00, // 00f9ffd0  MOV EDX,[EAX+0x134]
    0x6a, 0x01,                    // 00f9ffd6  PUSH 0x1
    0x8b, 0xcf,                    // 00f9ffd8  MOV ECX,EDI
    0xff, 0xd2,                    // 00f9ffda  CALL EDX
    0xe8, 0xef, 0xdd, 0x6d, 0xff,  // 00f9ffdc  CALL 0x0067ddd0
    0x8b, 0x10,                    // 00f9ffe1  MOV EDX,[EAX]
    0x8b, 0xc8,                    // 00f9ffe3  MOV ECX,EAX
    0x8b, 0x42, 0x54,              // 00f9ffe5  MOV EAX,[EDX+0x54]
    0x68, 0x24, 0xae, 0xfb, 0x03,  // 00f9ffe8  PUSH 0x3fbae24
    0xff, 0xd0,                    // 00f9ffed  CALL EAX
    0x8b, 0x10,                    // 00f9ffef  MOV EDX,[EAX]
    0x5f,                          // 00f9fff1  POP EDI
    0x5e,                          // 00f9fff2  POP ESI
    0x5b,                          // 00f9fff3  POP EBX
    0xc7, 0x44, 0x24, 0x04, 0x00, 0x00, 0x00, 0x00, // 00f9fff4  MOV [ESP+0x4],0
    0x8b, 0xc8,                    // 00f9fffc  MOV ECX,EAX
    0x8b, 0x42, 0x0c,              // 00f9fffe  MOV EAX,[EDX+0xc]
    0xff, 0xe0,                    // 00fa0001  JMP EAX
    0x5f,                          // 00fa0003  POP EDI
    0x5e,                          // 00fa0004  POP ESI
    0x5b,                          // 00fa0005  POP EBX
    0xc2, 0x04, 0x00,              // 00fa0006  RET 0x4
};

// The 28 bytes of that table which cannot be compared against the binary
// numerically, because they encode addresses in a different image: the four
// bytes of the absolute data displacement at offset 41, and the twenty-four
// bytes of the six CALL rel32 displacements. Each entry is the offset into
// kTargetBytes of the FIRST displacement byte.
//
// A SECOND class of byte cannot be compared either, and is not listed here
// because it needs no list: twenty-one register-only two-byte instructions are
// spelled two ways by x86 (MOV 8B/89, XOR 33/31, CMP 3B/39, and the byte forms
// 8A/88), and the GNU assembler picks the other one from the one the image has.
// The model test computes the mirror from the image's own bytes -- opcode minus
// two, ModRM reg and r/m exchanged, mod field required to be 11 -- and accepts a
// position only when the emitted bytes ARE that computed mirror, so nothing is
// excused by a stored alternative. Byte-identical recompilation is therefore
// NOT claimed for those 42 bytes without that allowance; semantic fidelity is,
// and it is what the executed cases establish.
inline constexpr std::size_t kRelocatableOffset0 = 42u;  // after 0x00f9ff18 8B 2D
inline constexpr std::size_t kRelocatableCallOffset[] = {54u, 68u, 82u, 96u, 176u, 237u};
inline constexpr std::size_t kRelocatableCallCount = 6u;
inline constexpr std::size_t kRelocatableBytes = 28u;
// The 10-byte PC anchor a position-independent g++ build MAY prepend to a naked
// function, recognised by its exact opcode pair e8 ?? ?? ?? ?? 05. It is a
// toolchain artifact and is not part of the reconstruction; the model test
// requires the 281 target bytes immediately after it, so a toolchain that
// emitted some other form of anchor fails the byte comparison rather than
// passing it. Measured on this toolchain: g++ emits it at -O0 and at no other
// level, and clang++ emits none at any level.
inline constexpr std::size_t kPcAnchorBytes = 10u;

// -- the reconstruction ------------------------------------------------------

// FUN_00f9fef0 @ 0x00f9fef0, reconstructed.
//
// A naked __thiscall transcription of the target's own 281 bytes. __thiscall is
// what puts the receiver in ECX; the callee-side cleanup of the one stack word is
// carried by this entry's own `retl $0x4`, which is the machine instruction
// 0x00fa0006 itself rather than a statement about it.
//
// The return type is `Word *`. See the note at the top of this file: the early
// out returns the interior pointer and the main path tail-transfers, so the
// declared type describes the early out's four-byte pointer-shaped value and
// nothing is claimed about the tail callee's return.
//
// The parameters are left unnamed on purpose: this function is naked, so it has
// no C++ body to read them in, and a named parameter in a naked definition is an
// unused-parameter diagnostic under -Wextra on every compiler. The declared types
// describe the shape the machine enters this with -- a receiver pointer in ECX
// and one 32-bit word at entry_ESP+0x4 -- and the model test drives it through
// its own declaration, which builds exactly that shape.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
extern "C" Word* PKG_W2_00F9FEF0_NAKED_THISCALL re_00f9fef0(Receiver*,
                                                             Argument*);

}  // namespace pkg_w2_00f9fef0
}  // namespace reconstruction
}  // namespace openspore

#endif  // RECONSTRUCTION_STAGING_PKG_W2_00F9FEF0_W2_00F9FEF0_TYPES_HPP_
