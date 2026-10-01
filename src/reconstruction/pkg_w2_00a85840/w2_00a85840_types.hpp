// PKG-W2-00A85840 -- VA 0x00a85840
// Boundary types and machine facts for the 31-instruction body at
// 0x00a85840..0x00a858b5 inclusive (118 bytes, SPORE/SporeBin/SporeApp.exe 3.1.0.22).
//
// Everything named here is named from the disassembly listing, from the
// machine-derived ABI record in reconstruction/evidence/00a85840/evidence.json
// (category abi_derived), or from bytes read back out of the image through the
// GhidraMCP bridge. Where the evidence abstains, this file says so instead of
// filling the gap; the gaps are listed at the bottom of the model test and each
// one is a real open question, not a placeholder.
//
// THE CALLING CONVENTION IS DETERMINED BY THE MACHINE, NOT CHOSEN HERE.
//
// reconstruction/evidence/00a85840/evidence.json, category abi_derived, states
// field for field:
//
//   conventions.calling_convention    : __thiscall
//   conventions.confidence            : SUPPORTED
//   conventions.corroboration          : "persisted_agrees"
//   conventions.candidate_conventions : ["__thiscall"]
//   conventions.ambiguities           : []
//   verdict                           : ABI_INFERRED
//   cross_validation.agreement         : true
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
//   cleanup.bytes    : 8     cleanup.side : callee
//   cleanup.evidence : "ret 0x8"            confidence OBSERVED
//
// in the two steps the record itself separates:
//
//   R1-VFT  (INFERRED) "ECX carries the receiver".
//     value: {receiver_register ECX, receiver_provenance vftable_slot_dispatch,
//             table 0x01458024, slot_index 6, incoming_ecx_reads 1,
//             membership_count 1, cleanup_side callee}
//     0x00a85840 is slot 6 of the table the record bases at 0x01458024 -- the
//     twenty-fourth byte above it, which is 6 four-byte slots -- and the body
//     READS the register such a dispatch delivers, which is the shape R1-VFT
//     discriminates from a COM / __stdcall body: a __stdcall-shaped body takes
//     its receiver from the first popped stack word and never reads its
//     incoming ECX. The body reads ECX exactly once, at 0x00a85867
//     (MOV ESI,ECX, obs-0013), and writes ECX once as well, at 0x00a85869
//     (MOV CX,[EAX], obs-0015), which is a partial write of the register and
//     happens AFTER the copy into ESI, so the copy sees the entry value.
//
//   C6B     (INFERRED) "the calling convention is __thiscall". The callee pops
//           its own stack arguments, which rules out cdecl and fastcall, and
//           the receiver arrives in ECX.
//
// SUPPORTED, and the record says what the support is: conventions.confidence is
// SUPPORTED, conventions.corroboration is "persisted_agrees" and
// cross_validation.agreement is true, i.e. the derived record and the persisted
// ABI layer name the same convention. The RECEIVER rule underneath is still
// INFERRED (R1-VFT), and nothing in this repository has watched a caller
// dispatch through the table at 0x01458024, and the record says so.
//
// WHAT THE CONVENTION DOES NOT SETTLE. A convention is not an identity.
// __thiscall says the receiver arrives in ECX. It does not say what the receiver
// IS, and this package does not guess. The body forms ONE address from it --
// LEA ECX,[ESI+0x24] at 0x00a858a7 -- and hands that address to a callee as its
// hidden receiver. It never loads a byte and never stores a byte through the
// receiver: there is no MOV or MOVSS with a receiver-relative memory operand
// anywhere in the thirty-one instructions. So:
//
//   * no owning class, and no vtable identity. R1-VFT names ONE table address
//     and a slot index; a slot is not a class, and this binary carries no MSVC
//     RTTI (Ghidra reports ghidra_has_calling_convention false and
//     ghidra_calling_convention_signal "no_information" for this target).
//   * no receiver type, no pointee, no object size, no vtable-pointer offset and
//     no field. Receiver is declared and deliberately left UNDEFINED
//     (struct Receiver;), which is a statement that none was observed and not a
//     statement that there are no members.
//
// THE DISPLACEMENT 0x24 IS A DISPLACEMENT AND NOT A FIELD. 0x00a858a7 computes
// receiver+0x24 and passes it; nothing ever reads or writes there, so the
// listing proves the arithmetic and proves nothing whatever about what lives at
// that offset. It is carried here as kReceiverInteriorDisplacement, an immediate
// taken from the instruction, and no field name or layout is attached to it in
// either direction.
//
// THE STACK ARGUMENT SURFACE, AND WHERE THE MACHINE RECORD IS INCOMPLETE.
//
// The record's own note on its stack_arguments is
// "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not
// one path", and the slot it enumerates is one: entry_ESP+0x8, ordinal 2,
// observed true, read false, sizes [4], with gaps 1 and total_bytes 8. That is
// a partial read, and the incompleteness is a property of a LINEAR ESP walk, not
// of the body: the walk cannot see what a callee does to ESP across a CALL.
//
// The body reads [ESP+0x40] twice -- at 0x00a85843 and at 0x00a85894 -- and the
// two reads name DIFFERENT caller arguments, which is exactly the fact the
// linear walk cannot see. Both callees it calls have been read out of the same
// image to settle it, and both end in a RET that carries an immediate:
//
//   0x0041cb40  ... 0041cc12 MOV ESP,EBP / 0041cc14 POP EBP / 0041cc15 RET 0x4
//   0x00537f40  ... 00537ff2 MOV ESP,EBP / 00537ff4 POP EBP / 00537ff5 RET 0x4
//   0x00537dc0  ... 00537e91 MOV ESP,EBP / 00537e93 POP EBP / 00537e94 RET 0x4
//
// All three are callee-popped with a four-byte immediate, so each of the three
// PUSHes in this body is consumed by its own callee and the body itself pushes
// and pops nothing across a call. That is what makes the second [ESP+0x40] read
// resolve to entry_ESP+0x4 and not to entry_ESP+0x8, and it is corroborated
// independently by the terminator: RET 0x8 drops two four-byte words, and the
// ADD ESP,0x38 that precedes it is balanced only if all three pushes were
// consumed. The stack shape this package models is therefore:
//
//   E+0x00  the return address                       (not touched by the body)
//   E+0x04  argument 1: a 4-byte slot, READ at 0x00a85894, PUSHed at
//           0x00a85898 and handed to 0x00537f40. Never dereferenced by the body.
//   E+0x08  argument 2: a 4-byte slot, READ at 0x00a85843 and then read through
//           by 0x00a85847, 0x00a8584c, 0x00a85856, 0x00a85861, 0x00a85869 and
//           0x00a85872, and PUSHed at 0x00a8587f as the base of the 0x24-byte
//           window handed to 0x0041cb40.
//   E+0x0c  the callee-popped cleanup of the two slots above; a caller that
//           pushed more sees those words again after the RET 0x8.
//
// NEITHER ARGUMENT IS NAMED FOR WHAT IT IS. Argument 1 is read and pushed and
// handed on without being dereferenced anywhere in these 118 bytes, so this
// package does not call it a struct pointer or anything else: the model test
// drives it over values no fixture address can equal, which is only sound
// BECAUSE the body never looks through it. Argument 2 is dereferenced, and the
// displacements the body reaches on it (0x00, 0x02, 0x04, 0x08, 0x0c, 0x10) plus
// the 0x14 base it adds before pushing (so 0x14..0x37) are all facts of the
// listing; what those bytes MEAN is not in evidence and is not claimed.
//
// THE FRAME. SUB ESP,0x38 at 0x00a85840 is the only frame instruction: no
// PUSH EBP, no MOV EBP,ESP, no SEH or cookie frame (parse.frame push_ebp false,
// mov_ebp_esp false, sub 56, local_extent 0). The 0x38 bytes below the entry
// stack pointer are named by nine stores and three LEAs, and the model test
// pins each of them. With S = the stack pointer immediately after the SUB:
//
//   S+0x00  word   the 2 bytes at argument 2 + 0x00   (MOV word [ESP+4],CX @00a8587a)
//   S+0x02  word   the 2 bytes at argument 2 + 0x02   (MOV word [ESP+0xa],DX @00a85884)
//   S+0x04  dword  the 4 bytes at argument 2 + 0x04   (MOVSS [ESP+4],XMM0   @00a85850)
//   S+0x08  dword  the 4 bytes at argument 2 + 0x08   (MOVSS [ESP+8],XMM0   @00a8585b)
//   S+0x0c  dword  the 4 bytes at argument 2 + 0x0c   (MOVSS [ESP+0x10],XMM0 @00a8586c)
//   S+0x10  dword  the 4 bytes at argument 2 + 0x10   (MOVSS [ESP+0x18],XMM0 @00a85889)
//   S+0x14  0x24 bytes handed to 0x0041cb40 as its hidden receiver (LEA ECX,[ESP+0x1c]
//           at 00a85880 with the stack pointer at S-8)
//
// The six stores are at three different stack-pointer values, which is why the
// listing spells them as it does: the MOVSS at 0x00a8586c runs with one word
// pushed (PUSH ESI at 0x00a85866) and so lands at S+0x0c, not at S+0x10, and
// the word and dword stores at 0x00a8587a / 0x00a85884 / 0x00a85889 run with
// two words pushed and land at S+0x00 / S+0x02 / S+0x10. The order in which the
// two overlapping S+0x00..S+0x03 bytes are written is a machine fact and the
// model preserves it by construction, because the reconstruction emits the
// stores in the listing's order rather than restating them as a copy.
//
// The consequence worth stating plainly: the twenty bytes at S+0x00 are a
// byte-for-byte copy of the first twenty bytes of argument 2, reassembled from
// two word loads and four dword loads in ascending address order. That is a
// property of the listing and the model test checks it as one, against the
// argument's own bytes.
//
// THE THIRTY-SIX BYTES AT S+0x14 ARE NOT DESCRIBED HERE. 0x0041cb40's own body
// was read (GhidraMCP /disassemble_function at 0x0041cb40, 64 instructions) and
// it copies nine dwords from its stack argument at offsets 0x00, 0x04, 0x08,
// 0x0c, 0x10, 0x14, 0x18, 0x1c and 0x20 -- that is, 0x24 bytes -- to offsets
// 0x00..0x20 of its hidden receiver. This package models that copy because the
// callee's behaviour is the only thing that makes the 0x24-byte window
// observable, and it claims nothing else about 0x0041cb40. The window's SIZE
// and the fact that it is 0x24 bytes are therefore facts about 0x0041cb40, not
// about 0x00a85840, and they are recorded as such.

#ifndef RECONSTRUCTION_STAGING_PKG_W2_00A85840_SW2_00A85840_TYPES_HPP_
#define RECONSTRUCTION_STAGING_PKG_W2_00A85840_SW2_00A85840_TYPES_HPP_

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-w2-00a85840 requires an x86-32 target"
#endif

// The convention is spelled once, here, and the reconstructed entry names the
// macro.
//
//   PKG_W2_00A85840_THISCALL        the convention on an ordinary
//                                         declarable function. It is what the
//                                         model test gives the three callees,
//                                         each of which the image shows being
//                                         entered with a hidden receiver in ECX
//                                         and a four-byte RET immediate.
//   PKG_W2_00A85840_NAKED_THISCALL  the same convention on the naked,
//                                         byte-faithful transcription of the
//                                         target's own 118 bytes.
//
// GCC rejects the bare MSVC keyword in the attribute position on some versions,
// so the attribute form is the portable spelling and the keyword form is kept
// for MSVC. Either way the token `thiscall` is carried once per macro, which is
// what the validator's convention resolution follows.
#if defined(_MSC_VER)
#define PKG_W2_00A85840_THISCALL __thiscall
#define PKG_W2_00A85840_NAKED_THISCALL __declspec(naked) __thiscall
#else
#define PKG_W2_00A85840_THISCALL __attribute__((thiscall))
#define PKG_W2_00A85840_NAKED_THISCALL __attribute__((naked, thiscall))
#endif

// The word this model moves around. A 32-bit slot is a machine fact at every
// place it is used; the C spelling is this package's choice.
using Word = std::uint32_t;

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00a85840 {

// -- identity ----------------------------------------------------------------

// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind the source span to 0x00a85840.
inline constexpr std::uint32_t kTargetVa = 0x00a85840u;
inline constexpr std::uint32_t kBodyFirstByte = 0x00a85840u;
// The terminator RET 0x8 at 0x00a858b3 is c2 08 00 and occupies
// 0x00a858b3..0x00a858b5, so the LAST byte of the body is 0x00a858b5 and the
// exclusive end is 0x00a858b6. ghidra_function.body_end names 0x00a858b5 and
// body_span_bytes names 118, which is 0x76.
inline constexpr std::uint32_t kBodyLastByte = 0x00a858b5u;
inline constexpr std::uint32_t kBodyEndExclusive = 0x00a858b6u;

// -- the receiver ------------------------------------------------------------

// The receiver. Declared and left UNDEFINED on purpose: the body never
// dereferences it -- it forms one interior address and hands it to a callee --
// so its size, layout, members and object identity are all unproven, and an
// empty definition here would be a claim that there are no members rather than
// a statement that none was observed.
struct Receiver;

// The one displacement the body forms from the receiver, LEA ECX,[ESI+0x24] at
// 0x00a858a7. This is the ADDRESS of receiver+0x24, passed as the third callee's
// hidden receiver. It is an immediate out of the instruction and nothing is read
// or written there, so no field and no layout is claimed in either direction.
inline constexpr std::size_t kReceiverInteriorDisplacement = 0x24u;

// How many times the body reads the receiver register itself: once, at
// 0x00a85867. The machine receiver record agrees at incoming_ecx_reads 1.
inline constexpr int kReceiverRegisterReads = 1;
// How many times the body loads or stores THROUGH the receiver: never.
inline constexpr int kReceiverDereferenceCount = 0;

// -- the frame ---------------------------------------------------------------

// SUB ESP,0x38 at 0x00a85840. The only frame instruction in the body.
inline constexpr std::size_t kFrameBytes = 0x38u;
inline constexpr int kFrameInstructions = 1;

// The six stores of argument 2's bytes into the frame, as offsets from the stack
// pointer immediately after the SUB. Each is an immediate out of the instruction
// named beside it; none of them is a field of anything.
inline constexpr std::size_t kLocalWord0Offset = 0x00u;   // MOV word [ESP+0x4],CX  @00a8587a
inline constexpr std::size_t kLocalWord2Offset = 0x02u;   // MOV word [ESP+0xa],DX  @00a85884
inline constexpr std::size_t kLocalFloat4Offset = 0x04u;  // MOVSS [ESP+0x4],XMM0   @00a85850
inline constexpr std::size_t kLocalFloat8Offset = 0x08u;  // MOVSS [ESP+0x8],XMM0   @00a8585b
inline constexpr std::size_t kLocalFloatCOffset = 0x0cu;  // MOVSS [ESP+0x10],XMM0  @00a8586c
inline constexpr std::size_t kLocalFloat10Offset = 0x10u; // MOVSS [ESP+0x18],XMM0  @00a85889

// The six-byte head of that block: two words and four dwords, laid end to end.
inline constexpr std::size_t kLocalHeadBytes = 0x14u;
// The window the first callee is given as its hidden receiver, starting where
// the head ends. Its SIZE is a fact about 0x0041cb40's own body (nine dword
// copies) and about nothing in this body.
inline constexpr std::size_t kLocalBlockOffset = 0x14u;
inline constexpr std::size_t kLocalBlockBytes = 0x24u;

// -- the two stack arguments -------------------------------------------------
//
// Two callee-popped words. The second is the one the machine record enumerates
// (entry_ESP+0x8, ordinal 2); the first is what the second [ESP+0x40] read
// resolves to once the first callee's own RET 0x4 is taken into account. See
// the note at the top of this file for why the linear walk could not see it.
inline constexpr int kStackArgumentSlots = 2;
inline constexpr std::size_t kArg1EntryOffset = 0x4u;
inline constexpr std::size_t kArg2EntryOffset = 0x8u;
inline constexpr std::size_t kArg1ReadFrom = 0x00a85894u;
inline constexpr std::size_t kArg2ReadFrom = 0x00a85843u;
// Argument 1 is read, pushed and handed on; it is never dereferenced.
inline constexpr bool kArg1Dereferenced = false;
// Argument 2 is read, and read through, at the six displacements below.
inline constexpr bool kArg2Dereferenced = true;
inline constexpr std::size_t kArg2Offsets[] = {0x00u, 0x02u, 0x04u, 0x08u, 0x0cu, 0x10u};
inline constexpr std::size_t kArg2OffsetCount = 6u;
// The base the body adds to argument 2 before pushing it, so the window handed
// to the first callee is argument 2 + 0x14 .. argument 2 + 0x37.
inline constexpr std::size_t kArg2PushedBase = 0x14u;
// The word telling the model test's harness to push NO extra dword. Any other
// value is pushed first, so it lands ABOVE both arguments and survives the
// terminator's RET 0x8. Zero is deliberately not the sentinel: the decoy cases
// pass 0 and 1 as real decoy words.
inline constexpr Word kNoDecoyWord = 0xffffffffu;

// -- extent, restated from the thirty-one instructions -----------------------

inline constexpr int kInstructionCount = 31;
inline constexpr std::size_t kBodySpanBytes = 118;
inline constexpr int kBasicBlockCount = 1;   // no branch of any kind in the body
inline constexpr int kConditionalBranches = 0;
inline constexpr int kDirectCalleeCount = 3;
inline constexpr int kIndirectTransfers = 0;
inline constexpr int kGlobalReferences = 0;
// Exactly one register is saved: ESI, PUSHed at 0x00a85866 and POPped at
// 0x00a858af, a save/restore pair that brackets everything between them -- all
// three calls included. The machine record agrees (abi.derived
// saved_registers ["ESI"], obs-0012 REG_READ and obs-0027 REG_RESTORE).
inline constexpr int kSavedRegisterCount = 1;

// -- the table slot the receiver rule rests on --------------------------------
//
// Machine facts, read out of the image and named by the record's R1-VFT rule.
// GhidraMCP /read_memory at 0x0145800c for 48 bytes puts, from 0x01458024:
// 0x00a85070, 0x004ae250, 0x00a850d0, 0x00a85790, 0x00a858c0, 0x007edc60 and
// 0x00a85840 at 0x0145803c -- the seventh dword, which is slot index 6 and the
// single incoming code reference ghidra_function.xrefs records for this VA.
// Every one of the seven is a .text address. A table of code pointers is what
// R1-VFT reasons about; this package names no class for it and no field of it,
// because this binary carries no MSVC RTTI and no SDK name is recorded for it.
inline constexpr std::uint32_t kTableBase = 0x01458024u;
inline constexpr std::uint32_t kOwnSlotAddress = 0x0145803cu;
inline constexpr int kOwnSlotIndex = 6;
inline constexpr std::size_t kOwnSlotDisplacement = 0x18u;
// The six other words of the same table, so a reader can see that the base is a
// table of code addresses rather than a single entry. Not a layout claim: these
// are the bytes at 0x01458024..0x0145803f and nothing is inferred from them.
inline constexpr std::uint32_t kTableWords[] = {
    0x00a85070u, 0x004ae250u, 0x00a850d0u,
    0x00a85790u, 0x00a858c0u, 0x007edc60u, 0x00a85840u};
inline constexpr std::size_t kTableWordCount = 7u;

// -- the 118 bytes, transcribed from the image -------------------------------
//
// GhidraMCP /read_memory at 0x00a85840 for 118 bytes returns the byte string
// below, and /disassemble_function at 0x00a85840 returns exactly the
// thirty-one instructions in the model test's header comment, at exactly these
// addresses, consuming all 118 bytes with nothing left over. Every displacement
// was checked against that byte string: the CALL rel32 at 0x00a8588f is
// e8 ac 72 99 ff, next-instruction 0x00a85894 plus signed -0x668d54 lands on
// 0x0041cb40; the one at 0x00a8589d is e8 9e 26 ab ff, next 0x00a858a2 plus
// signed -0x54d962 lands on 0x00537f40; the one at 0x00a858aa is e8 11 25 ab
// ff, next 0x00a858af plus signed -0x54daef lands on 0x00537dc0.
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x83u, 0xecu, 0x38u,                                // 00a85840  SUB ESP,0x38
    0x8bu, 0x44u, 0x24u, 0x40u,                         // 00a85843  MOV EAX,[ESP+0x40]
    0xf3u, 0x0fu, 0x10u, 0x40u, 0x04u,                 // 00a85847  MOVSS XMM0,[EAX+0x4]
    0x66u, 0x8bu, 0x50u, 0x02u,                         // 00a8584c  MOV DX,[EAX+0x2]
    0xf3u, 0x0fu, 0x11u, 0x44u, 0x24u, 0x04u,           // 00a85850  MOVSS [ESP+0x4],XMM0
    0xf3u, 0x0fu, 0x10u, 0x40u, 0x08u,                 // 00a85856  MOVSS XMM0,[EAX+0x8]
    0xf3u, 0x0fu, 0x11u, 0x44u, 0x24u, 0x08u,           // 00a8585b  MOVSS [ESP+0x8],XMM0
    0xf3u, 0x0fu, 0x10u, 0x40u, 0x0cu,                 // 00a85861  MOVSS XMM0,[EAX+0xc]
    0x56u,                                              // 00a85866  PUSH ESI
    0x8bu, 0xf1u,                                       // 00a85867  MOV ESI,ECX
    0x66u, 0x8bu, 0x08u,                                // 00a85869  MOV CX,[EAX]
    0xf3u, 0x0fu, 0x11u, 0x44u, 0x24u, 0x10u,           // 00a8586c  MOVSS [ESP+0x10],XMM0
    0xf3u, 0x0fu, 0x10u, 0x40u, 0x10u,                 // 00a85872  MOVSS XMM0,[EAX+0x10]
    0x83u, 0xc0u, 0x14u,                                // 00a85877  ADD EAX,0x14
    0x66u, 0x89u, 0x4cu, 0x24u, 0x04u,                 // 00a8587a  MOV [ESP+0x4],CX
    0x50u,                                              // 00a8587f  PUSH EAX
    0x8du, 0x4cu, 0x24u, 0x1cu,                         // 00a85880  LEA ECX,[ESP+0x1c]
    0x66u, 0x89u, 0x54u, 0x24u, 0x0au,                 // 00a85884  MOV [ESP+0xa],DX
    0xf3u, 0x0fu, 0x11u, 0x44u, 0x24u, 0x18u,           // 00a85889  MOVSS [ESP+0x18],XMM0
    0xe8u,                                              // 00a8588f  CALL 0x0041cb40 (opcode)
    0xacu, 0x72u, 0x99u, 0xffu,                         //           rel32, resolved by the test
    0x8bu, 0x44u, 0x24u, 0x40u,                         // 00a85894  MOV EAX,[ESP+0x40]
    0x50u,                                              // 00a85898  PUSH EAX
    0x8du, 0x4cu, 0x24u, 0x08u,                         // 00a85899  LEA ECX,[ESP+0x8]
    0xe8u,                                              // 00a8589d  CALL 0x00537f40 (opcode)
    0x9eu, 0x26u, 0xabu, 0xffu,                         //           rel32, resolved by the test
    0x8du, 0x4cu, 0x24u, 0x04u,                         // 00a858a2  LEA ECX,[ESP+0x4]
    0x51u,                                              // 00a858a6  PUSH ECX
    0x8du, 0x4eu, 0x24u,                                // 00a858a7  LEA ECX,[ESI+0x24]
    0xe8u,                                              // 00a858aa  CALL 0x00537dc0 (opcode)
    0x11u, 0x25u, 0xabu, 0xffu,                         //           rel32, resolved by the test
    0x5eu,                                              // 00a858af  POP ESI
    0x83u, 0xc4u, 0x38u,                                // 00a858b0  ADD ESP,0x38
    0xc2u, 0x08u, 0x00u,                                // 00a858b3  RET 0x8
};

// The three rel32 displacements, as offsets into kTargetBytes counting from the
// byte after the E8 opcode, and the fact that each CALL is a five-byte E8 form.
// Those twelve bytes cannot be compared against the binary's numerically -- they
// encode addresses in a different image -- so the model test resolves each one
// out of the emitted code and requires it to land on the callee the xref export
// names for that callsite.
inline constexpr std::size_t kCallRel32FirstOffset = 0x50u;   // after the E8 at 0x4f
inline constexpr std::size_t kCallRel32SecondOffset = 0x5eu;  // after the E8 at 0x5d
inline constexpr std::size_t kCallRel32ThirdOffset = 0x6bu;   // after the E8 at 0x6a

// The one instruction whose encoding the assembler is free to spell two ways:
// the binary writes MOV ESI,ECX as 8b f1 and the GNU assembler writes 89 ce for
// the same operands. Both spellings are accepted by the model test and every
// other one of the 118 positions is compared literally. Measured on this
// toolchain: clang++ emits 89 ce, and g++ emits 89 ce at every -O level; the
// binary's 8b f1 is the MSVC spelling.
inline constexpr std::size_t kEcxToEsiFirstByte = 0x27u;
inline constexpr std::size_t kEcxToEsiSecondByte = 0x28u;

// The 10-byte PC anchor a position-independent g++ build may prepend to a naked
// function, recognised by its exact opcode pair e8 ?? ?? ?? ?? 05. It is a
// toolchain artifact and is not part of the reconstruction; the model test
// requires the 118 target bytes immediately after it, so a toolchain that
// emitted some other form of anchor fails the byte comparison rather than
// passing it.
inline constexpr std::size_t kPcAnchorBytes = 10u;

// -- the machine-derived ABI, carried as DATA --------------------------------
//
// Every value below is transcribed from the evidence pack's `abi_derived`
// category and from nothing else. They are data rather than prose so that
// changing one is a change the model test can catch, and so a package that
// quietly reverted to the old abstention -- "no convention, no receiver" --
// fails the model test instead of passing.

// The convention the derived record names: __thiscall, with no other candidate.
enum class ConventionVerdict00a85840 : int { kThiscall = 0 };

// INFERRED, not OBSERVED and not UNKNOWN. The determination is an inference
// from the vftable-slot rule and the cleanup side; nothing here observed a
// caller dispatching through the table.
enum class ConventionConfidence : int {
  kUnknown = 0,
  kInferred = 1,
  kSupported = 2,
  kObserved = 3
};

// What the record says the SUPPORTED confidence rests on: its own
// conventions.corroboration field, and cross_validation.agreement.
enum class Corroboration00a85840 : int { kPersistedAgrees = 0 };

// The register the receiver arrives in.
enum class ReceiverRegister00a85840 : int { kEcx = 0 };

// Why the derived record believes a receiver is there at all.
enum class ReceiverProvenance00a85840 : int { kVftableSlotDispatch = 0 };

// Which side of the stack arguments this callee pops.
enum class CleanupSide00a85840 : int { kCallee = 0 };

inline constexpr ConventionVerdict00a85840 kDerivedConventionVerdict =
    ConventionVerdict00a85840::kThiscall;
inline constexpr ConventionConfidence kDerivedConventionConfidence =
    ConventionConfidence::kSupported;
inline constexpr Corroboration00a85840 kConventionsCorroboration =
    Corroboration00a85840::kPersistedAgrees;
inline constexpr bool kCrossValidationAgreement = true;
inline constexpr int kCandidateConventionCount = 1;

inline constexpr ReceiverRegister00a85840 kDerivedReceiverRegister =
    ReceiverRegister00a85840::kEcx;
inline constexpr ReceiverProvenance00a85840 kReceiverProvenance =
    ReceiverProvenance00a85840::kVftableSlotDispatch;
inline constexpr bool kReceiverPresent = true;
inline constexpr bool kReceiverAbsent = false;
inline constexpr bool kReceiverBoundsOnly = true;
inline constexpr bool kReceiverHasShape = false;
// 0, because the thirty-one instructions contain no load and no store through
// the receiver in any register: the only receiver-relative operand in the whole
// body is a LEA, which forms an address and touches nothing.
inline constexpr int kReceiverDistinctOffsets = 0;
inline constexpr int kReceiverBytesLoaded = 0;
inline constexpr int kReceiverBytesStored = 0;

// Separately OBSERVED, and independent of the convention: the terminator's own
// form is RET 0x8.
inline constexpr CleanupSide00a85840 kObservedCleanupSide =
    CleanupSide00a85840::kCallee;
inline constexpr std::size_t kRetImmediateBytes = 8;
inline constexpr std::size_t kStackCleanupBytes = 8;
// The terminator's immediate, seen from the bytes rather than from the record.
inline constexpr std::uint8_t kRetImmediateLowByte = 0x08u;
inline constexpr std::uint8_t kRetImmediateHighByte = 0x00u;
// What a CALL pushes on top of the terminator's immediate: the return address.
// The model test needs it because a post-call stack sample sits FOUR bytes above
// entry_ESP + kRetImmediateBytes, not on it -- `ret imm16` pops the return address
// first and only then adds its immediate -- and a harness that forgets this reads
// the body's frame four bytes high.
inline constexpr std::uint32_t kReturnAddressBytes = 4u;
// The two stack arguments are READ and never WRITTEN.
inline constexpr bool kStackArgumentRead = true;
inline constexpr bool kStackArgumentWritten = false;
// The two arguments are DATA. Neither is a receiver, and neither ever becomes
// one: the receiver arrives in ECX, is copied into ESI, and only its +0x24
// address is ever formed.
inline constexpr bool kStackArgumentIsReceiver = false;

// The three callees' own terminators, read out of the same image. This is what
// turns three callee-popped pushes into a balanced frame, and it is the evidence
// the second [ESP+0x40] read needs in order to name entry_ESP+0x4.
inline constexpr std::uint32_t kCalleeReturnAddresses[3] = {
    0x0041cc15u, 0x00537ff5u, 0x00537e94u};
inline constexpr std::size_t kCalleeRetImmediateBytes = 4;
inline constexpr int kCalleeCount = 3;

// -- the three direct callees, declared as the model's own out-of-line calls ----
//
// Their addresses are in their names, which is the convention the validator
// reads to compare a source's call set against the xref export. All three are
// entered exactly the way the listing enters them: a hidden receiver in ECX and
// one four-byte word on the stack, consumed by the callee (RET 0x4 each, read
// from the image). None of them is a C++ class member and no receiver type is
// named for any of them; the first parameter's declared type is the same opaque
// Receiver the body itself takes.
//
//   0x0041cb40  hidden receiver = the 0x24-byte window at S+0x14, one word =
//               argument 2 + 0x14. Unnamed in the image. Its own body was read
//               and it copies 0x24 bytes from its word to its receiver; this
//               package models that copy and claims nothing else about it.
//   0x00537f40  hidden receiver = the 0x14-byte head at S+0x00, one word =
//               argument 1. Unnamed in the image; an observer here.
//   0x00537dc0  hidden receiver = receiver + 0x24, one word = the address of the
//               0x14-byte head at S+0x00. Unnamed in the image; an observer here.
extern "C" void PKG_W2_00A85840_THISCALL callee_0041cb40(Receiver* block,
                                                              Word* source);
extern "C" void PKG_W2_00A85840_THISCALL callee_00537f40(Receiver* head,
                                                              Word* argument1);
extern "C" Word PKG_W2_00A85840_THISCALL callee_00537dc0(Receiver* interior,
                                                              Word* head_address);

// -- the reconstruction ------------------------------------------------------

// FUN_00a85840 @ 0x00a85840, reconstructed.
//
// A naked __thiscall transcription of the target's own 118 bytes. __thiscall is
// what puts the receiver in ECX; the callee-side cleanup of the two stack words
// is carried by this entry's own `retl $8`, which is the machine instruction
// 0x00a858b3 itself rather than a statement about it.
//
// The return type is void, and that is a source-side reading of the listing
// rather than a recovered fact: the thirty-one instructions contain no
// instruction that places a value in a return register at the terminator. EAX's
// last write is 0x00a85894, which loads argument 1 so that the very next
// instruction can push it, and two calls run after it, so whatever they leave in
// EAX is what reaches the caller. XMM0's last write is 0x00a85872, a load whose
// only consumer is the store at 0x00a85889.
//
// WHAT THAT EAX IS, from a SECOND listing rather than from this body. 0x00537dc0's
// own 80-instruction listing ends on both of its arms -- the overwrite arm entered at
// 0x00537e33 and the skip arm reached by 0x00537e14 / 0x00537e2f -- with the same
// instruction, 0x00537e8c `MOV EAX,[EBP + -0x4]`, i.e. its own hidden receiver. So the
// word the caller receives is the address this body built at 0x00a858a7, receiver +
// 0x24. That is stated here as a fact about the CALLEE, and it is why the declared
// type is the weaker claim: this body neither computes nor stores that address for a
// caller, it only happens to be the register the callee left behind, and a C++
// `return f(...)` and a C++ void body are byte-identical in these 118 bytes. The
// model test pins the mechanics either way -- case F drives a sentinel through the
// last callee and requires it handed straight back.
//
// The machine record's own
// return_register is XMM0 with return_semantics "float_or_x87_in_XMM0", but it
// carries that at confidence APPROXIMATION under rule RT1, whose stated basis is
// "an x87 or SSE instruction appears in the body" -- a property of every SSE
// instruction ever written, not of a return. That heuristic claim is recorded in
// the sidecar and is not adopted here.
//
// The parameters are left unnamed on purpose: this function is naked, so it has
// no C++ body to read them in, and a named parameter in a naked definition is an
// unused-parameter diagnostic under -Wextra on every compiler. The declared types
// describe the shape the machine enters this with -- a receiver pointer in ECX
// and one 32-bit word at each of entry_ESP+0x4 and entry_ESP+0x8 -- and the
// model test drives it through a call site that builds exactly that shape.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
extern "C" void PKG_W2_00A85840_NAKED_THISCALL re_00a85840(Receiver*,
                                                                 Word*,
                                                                 Word*);

}  // namespace pkg_w2_00a85840
}  // namespace reconstruction
}  // namespace openspore

#endif  // RECONSTRUCTION_STAGING_PKG_W2_00A85840_SW2_00A85840_TYPES_HPP_
