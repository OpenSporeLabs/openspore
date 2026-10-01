// PKG-W2-00A85840 -- VA 0x00a85840
// FUN_00a85840 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 31 instructions, 0x00a85840..0x00a858b5 inclusive, 118
// bytes. The terminator RET 0x8 at 0x00a858b3 is `c2 08 00`, so it occupies
// 0x00a858b3..0x00a858b5 and the body's last byte is 0x00a858b5, which is what
// ghidra_function.body_end names; body_span_bytes names 118, which is 0x76.
//
// The listing was re-read from the image for this package rather than taken on
// trust. GhidraMCP /read_memory at 0x00a85840 for 118 bytes returns the byte
// string transcribed into kTargetBytes in the header, and
// /disassemble_function at 0x00a85840 returns exactly these thirty-one
// instructions at exactly these addresses:
//
//   00a85840  83 ec 38           SUB ESP,0x38
//   00a85843  8b 44 24 40        MOV EAX,dword ptr [ESP + 0x40]
//   00a85847  f3 0f 10 40 04     MOVSS XMM0,dword ptr [EAX + 0x4]
//   00a8584c  66 8b 50 02        MOV DX,word ptr [EAX + 0x2]
//   00a85850  f3 0f 11 44 24 04  MOVSS dword ptr [ESP + 0x4],XMM0
//   00a85856  f3 0f 10 40 08     MOVSS XMM0,dword ptr [EAX + 0x8]
//   00a8585b  f3 0f 11 44 24 08  MOVSS dword ptr [ESP + 0x8],XMM0
//   00a85861  f3 0f 10 40 0c     MOVSS XMM0,dword ptr [EAX + 0xc]
//   00a85866  56                 PUSH ESI
//   00a85867  8b f1              MOV ESI,ECX
//   00a85869  66 8b 08           MOV CX,word ptr [EAX]
//   00a8586c  f3 0f 11 44 24 10  MOVSS dword ptr [ESP + 0x10],XMM0
//   00a85872  f3 0f 10 40 10     MOVSS XMM0,dword ptr [EAX + 0x10]
//   00a85877  83 c0 14           ADD EAX,0x14
//   00a8587a  66 89 4c 24 04     MOV word ptr [ESP + 0x4],CX
//   00a8587f  50                 PUSH EAX
//   00a85880  8d 4c 24 1c        LEA ECX,[ESP + 0x1c]
//   00a85884  66 89 54 24 0a     MOV word ptr [ESP + 0xa],DX
//   00a85889  f3 0f 11 44 24 18  MOVSS dword ptr [ESP + 0x18],XMM0
//   00a8588f  e8 ac 72 99 ff     CALL 0x0041cb40
//   00a85894  8b 44 24 40        MOV EAX,dword ptr [ESP + 0x40]
//   00a85898  50                 PUSH EAX
//   00a85899  8d 4c 24 08        LEA ECX,[ESP + 0x8]
//   00a8589d  e8 9e 26 ab ff     CALL 0x00537f40
//   00a858a2  8d 4c 24 04        LEA ECX,[ESP + 0x4]
//   00a858a6  51                 PUSH ECX
//   00a858a7  8d 4e 24           LEA ECX,[ESI + 0x24]
//   00a858aa  e8 11 25 ab ff     CALL 0x00537dc0
//   00a858af  5e                 POP ESI
//   00a858b0  83 c4 38           ADD ESP,0x38
//   00a858b3  c2 08 00           RET 0x8
//
// The instruction lengths are 3+4+5+4+6+5+6+5+1+2+3+6+5+3+4+1+4+4+6+5+4+1+4+5+4+1+3+4+5+1+3+3
// = 118, which is ghidra_function.body_span_bytes, and the last instruction's
// three bytes end at 0x00a858b5, which is ghidra_function.body_end. So these
// thirty-one are the whole of the body: abi_derived.parse reports
// {declared_count 31, unparsed 0, degraded false}.
//
// WHY THIS ENTRY IS A NAKED __thiscall TRANSCRIPTION RATHER THAN C++.
//
// The derived ABI record DETERMINES the convention
// (reconstruction/evidence/00a85840/evidence.json, category abi_derived):
//
//   conventions.calling_convention = __thiscall, confidence SUPPORTED,
//   conventions.corroboration = "persisted_agrees",
//   candidate_conventions ["__thiscall"], ambiguities [], verdict ABI_INFERRED;
//   receiver {present true, register ECX, provenance vftable_slot_dispatch,
//   bounds_only true, shape null, distinct_offsets 0, offsets [],
//   written_through 0};
//   cleanup {bytes 8, side callee, evidence "ret 0x8", confidence OBSERVED}.
//
// R1-VFT puts the receiver in ECX: 0x00a85840 is slot 6 of the table the record
// bases at 0x01458024, and the body READS the register such a dispatch delivers
// -- a COM / __stdcall-shaped body takes its receiver from the first popped
// stack word and never reads its incoming ECX, and this one reads it once, at
// 0x00a85867. C6B then names __thiscall from the callee-side cleanup together
// with that register.
//
// So this entry declares __thiscall (the machine's determination, not a choice
// this package made) AND emits the 118 bytes, because those are two separate
// claims and a C++ restatement would only make the first one. The value of the
// second claim is that the model test can hold the reconstruction's own emitted
// code against the binary's own /read_memory output, which is evidence rather
// than a second reading of the same author's mind.
//
// STACK ARITHMETIC, and the one fact a linear ESP walk cannot reach.
//
// Let E be the entry ESP. SUB ESP,0x38 puts the stack pointer at S = E-0x38.
// Then:
//
//   0x00a85843  MOV EAX,[ESP+0x40]   EAX = the word at E+8  (argument 2)
//   0x00a85866  PUSH ESI             S-4;  the only frame push
//   0x00a85867  MOV ESI,ECX          ESI = the receiver, unadjusted
//   0x00a8587f  PUSH EAX             S-8, [S-8] = argument 2 + 0x14
//   0x00a85880  LEA ECX,[ESP+0x1c]  ECX = S-8+0x1c = S+0x14
//   0x00a8588f  CALL 0x0041cb40      and 0x0041cb40 ends in RET 0x4, so the
//                                    push it was given is consumed and the
//                                    stack pointer is back at S-4
//   0x00a85894  MOV EAX,[ESP+0x40]   EAX = the word at S-4+0x40 = E+4
//                                    (argument 1)  <<< the second read
//   0x00a85898  PUSH EAX             S-8, [S-8] = argument 1
//   0x00a85899  LEA ECX,[ESP+0x8]    ECX = S-8+0x8 = S
//   0x00a8589d  CALL 0x00537f40      RET 0x4, back to S-4
//   0x00a858a2  LEA ECX,[ESP+0x4]    ECX = S-4+0x4 = S
//   0x00a858a6  PUSH ECX             S-8, [S-8] = S
//   0x00a858a7  LEA ECX,[ESI+0x24]   ECX = receiver + 0x24
//   0x00a858aa  CALL 0x00537dc0      RET 0x4, back to S-4
//   0x00a858af  POP ESI              S
//   0x00a858b0  ADD ESP,0x38         E
//   0x00a858b3  RET 0x8              the caller resumes at E+8
//
// The three callees' own terminators were read out of the same image to settle
// that: 0x0041cb40 ends 0041cc12 MOV ESP,EBP / 0041cc14 POP EBP / 0041cc15
// RET 0x4; 0x00537f40 ends 00537ff2 MOV ESP,EBP / 00537ff4 POP EBP / 00537ff5
// RET 0x4; 0x00537dc0 ends 00537e91 MOV ESP,EBP / 00537e93 POP EBP / 00537e94
// RET 0x4. Without that, the ADD ESP,0x38 does not land on E and the RET 0x8
// would not land on E+8, so the shape is corroborated by the terminator as well
// as by the callees.
//
// THIS IS WHERE THE MACHINE RECORD IS INCOMPLETE, and the package says so
// rather than papering over it. abi_derived.stack_arguments enumerates ONE slot
// -- entry_ESP+0x8, ordinal 2, observed, sizes [4] -- with gaps 1 and
// total_bytes 8, and its abstained_because reads "flow_not_modelled: the linear
// ESP walk ends at +12, so the listing is not one path". That abstention is about
// a linear walk, which cannot see what a callee does to ESP across a CALL. The
// two facts it missed are the three callee-popped pushes above, which is why the
// body has TWO caller arguments and not one, and the second [ESP+0x40] read,
// which is why the two are different arguments and not the same one twice. The
// record is not edited; the reading is stated here and in the sidecar, with its
// own evidence.
//
// THE THREE CALLS, in listing order, with no branch between any of them.
//
// There is not one conditional branch in the body: the thirty-one instructions
// are straight-line, so all three calls happen on every execution and the only
// ordering statement available is the one the addresses give.
//
//   1. 0x0041cb40, hidden receiver = S+0x14, one word = argument 2 + 0x14.
//      Its own body was read (64 instructions) and it copies nine dwords -- 0x24
//      bytes -- from its word to offsets 0x00..0x20 of its receiver. The window
//      is exactly the tail of this body's frame: S+0x14 + 0x24 = S+0x38, the top
//      of the reservation. Nothing in the body reads it back.
//
//   2. 0x00537f40, hidden receiver = S+0x00, one word = argument 1. The receiver
//      is the address of the six-store head, the same address the third call
//      receives as its word. Unnamed in the image; an observer here.
//
//   3. 0x00537dc0, hidden receiver = receiver + 0x24, one word = S+0x00. This is
//      the ONLY thing the body ever does with the receiver: it forms the address
//      of receiver+0x24 and hands it over. No byte is read and none is written
//      through the receiver, in any register, anywhere in these 118 bytes, which
//      is what the machine receiver record states (bounds_only true, shape null,
//      offsets [], written_through 0) and what this package therefore does not
//      turn into a field or a layout.
//
// ARGUMENT 1 IS NEVER LOOKED THROUGH. It is loaded at 0x00a85894, pushed at
// 0x00a85898 and handed to 0x00537f40; no instruction in the body dereferences
// it. The model test exploits that -- it drives argument 1 over values no fixture
// address can equal, including ones that are not mapped at all, and the run is
// only sound BECAUSE the body never looks. Argument 2 is the opposite: the body
// reads it at six displacements and hands its +0x14 base to the first callee.
//
// CONTROL FLOW. One basic block. No conditional branch, no loop, no second exit,
// and no fall-through off the end of the body: the terminator is reached by
// running the thirty-first instruction. There is exactly one return site.
//
// GLOBALS. None. The thirty-one instructions name no data-segment address; the
// immediates that are addresses are 0x0041cb40, 0x00537f40 and 0x00537dc0, all
// inside .text. The record's globals category is empty and the xref export
// carries no data-reference edge type for this VA.
//
// VIRTUAL DISPATCH. None in the body, and none declared. abi_derived.dispatch
// records indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the
// thirty-one instructions contain no register- or memory-operand transfer: all
// three transfers are CALLs with an immediate operand. The body is itself a slot
// occupant -- GhidraMCP /read_memory at 0x01458018 for 48 bytes puts 0x00a85840
// at 0x0145803c, slot index 6 of the table based at 0x01458024 -- which is the
// opposite of dispatching: it never reads the word at the receiver's +0x00, and
// the receiver's only use is to form an interior address for a callee to take
// as ITS receiver. So no slot boundary is declared and no dispatch pointer is
// modelled as a member.
//
// RETURN. void, and that is a reading of the listing rather than a recovered
// fact. There is no instruction that places a value in a return register at the
// terminator: EAX's last write is the load at 0x00a85894 whose only purpose is
// the PUSH that follows it, and two calls run after that, so EAX at the RET is
// whatever the third callee left there; XMM0's last write is the load at
// 0x00a85872, consumed one instruction later by the store at 0x00a85889. The
// machine record's return_register is XMM0 with return_semantics
// "float_or_x87_in_XMM0", but it carries that at confidence APPROXIMATION under
// rule RT1, whose stated basis is "an x87 or SSE instruction appears in the
// body" -- true of every SSE instruction ever written and not a statement about a
// return. The model test checks the void reading in the only place it is
// observable: the third callee leaves a recognisable word in EAX and the harness
// requires that word back.
//
// NOT MODELLED, and why:
//   * the receiver's size, layout and members. The body never dereferences it.
//   * the receiver's IDENTITY. __thiscall says where it arrives, not what it is;
//     whether the incoming ECX points at the head of the object or at an interior
//     sub-object is invisible from here, because the body neither adds nor
//     subtracts anything of its own and the sole code reference to this address
//     is a table slot, not an adjustor stub.
//   * the class that owns the table 0x01458024. The binary carries no MSVC RTTI
//     and no SDK name is recorded for it.
//   * the meaning of the twenty bytes at S+0x00 and of the 0x24 bytes at S+0x14.
//     Both are located and sized; what they MEAN is not in evidence.
//   * what any of the three callees does beyond the copy 0x0041cb40's own body
//     was read to show. All three are declared in the header and defined by the
//     model test as observers. The body models the calls, their order, their
//     arguments and their stack discipline -- which is all the thirty-one
//     instructions contain.

#include "w2_00a85840_types.hpp"

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00a85840 {

// Placed first in this translation unit on purpose: the validator binds a source
// span to 0x00a85840 by the 8-hex VA token appearing in the function name, and
// it takes the FIRST such definition in the file.
extern "C" void PKG_W2_00A85840_NAKED_THISCALL re_00a85840(Receiver*,
                                                                 Word*,
                                                                 Word*) {
  // The convention is __thiscall: the receiver arrives in ECX and this callee
  // pops its own two stack words itself, in the `retl $8` three lines below.
  //
  // Byte fidelity: 106 of the 118 positions are pinned against the binary's own
  // bytes (kTargetBytes in the header) by the model test. Twelve of the 118
  // cannot be, and each group is pinned differently rather than waved through:
  //
  //   * the three rel32 displacements of the CALLs at 0x00a8588f, 0x00a8589d and
  //     0x00a858aa. They encode addresses in a different image, so the test
  //     RESOLVES each one out of the emitted code and requires it to land on the
  //     callee the xref export names for that callsite -- 0x0041cb40,
  //     0x00537f40 and 0x00537dc0 -- which is a real constraint on the emitted
  //     code rather than a spelling.
  //   * two positions: the encoding of MOV ESI,ECX. The binary writes 8b f1
  //     (the MSVC spelling); the GNU assembler writes 89 ce for the same
  //     operands, and both clang++ and g++ emit 89 ce on this toolchain. Both
  //     spellings are accepted, and each of the remaining 116 positions must
  //     match the binary exactly.
  //
  // A default position-independent g++ build MAY additionally prepend a ten-byte
  // __x86.get_pc_thunk.ax PC anchor to a naked function (g++ -m32 does so at
  // -O0; clang++ emits none at any level). That is a toolchain artifact and not
  // part of the reconstruction. The model test recognises the anchor by its
  // exact opcode pair e8 ?? ?? ?? ?? 05 and requires the 118 target bytes
  // immediately after it; a toolchain that emitted some other form of anchor
  // would fail that test rather than pass it. Byte-identical recompilation is
  // therefore NOT claimed without that allowance; semantic fidelity is, and it is
  // what the executed checks below establish.
  //
  // NOTHING HERE IS RESTATED AS C++. The six stores of argument 2's bytes into
  // the frame are emitted in the listing's own order and at three different
  // stack-pointer values, so the ORDER in which the two bytes at S+0x00 and
  // S+0x01 are written is preserved by construction rather than by a copy. A
  // C++ restatement would have to choose an order, and choosing one is a claim
  // the listing does not make in that form.
  __asm__("subl $0x38, %esp\n\t"             // 00a85840  SUB ESP,0x38
          "movl 0x40(%esp), %eax\n\t"        // 00a85843  MOV EAX,[ESP+0x40]
          "movss 0x4(%eax), %xmm0\n\t"       // 00a85847  MOVSS XMM0,[EAX+0x4]
          "movw 0x2(%eax), %dx\n\t"          // 00a8584c  MOV DX,[EAX+0x2]
          "movss %xmm0, 0x4(%esp)\n\t"      // 00a85850  MOVSS [ESP+0x4],XMM0
          "movss 0x8(%eax), %xmm0\n\t"       // 00a85856  MOVSS XMM0,[EAX+0x8]
          "movss %xmm0, 0x8(%esp)\n\t"      // 00a8585b  MOVSS [ESP+0x8],XMM0
          "movss 0xc(%eax), %xmm0\n\t"       // 00a85861  MOVSS XMM0,[EAX+0xc]
          "pushl %esi\n\t"                   // 00a85866  PUSH ESI
          "movl %ecx, %esi\n\t"              // 00a85867  MOV ESI,ECX
          "movw (%eax), %cx\n\t"             // 00a85869  MOV CX,[EAX]
          "movss %xmm0, 0x10(%esp)\n\t"      // 00a8586c  MOVSS [ESP+0x10],XMM0
          "movss 0x10(%eax), %xmm0\n\t"      // 00a85872  MOVSS XMM0,[EAX+0x10]
          "addl $0x14, %eax\n\t"             // 00a85877  ADD EAX,0x14
          "movw %cx, 0x4(%esp)\n\t"          // 00a8587a  MOV [ESP+0x4],CX
          "pushl %eax\n\t"                   // 00a8587f  PUSH EAX
          "leal 0x1c(%esp), %ecx\n\t"        // 00a85880  LEA ECX,[ESP+0x1c]
          "movw %dx, 0xa(%esp)\n\t"          // 00a85884  MOV [ESP+0xa],DX
          "movss %xmm0, 0x18(%esp)\n\t"      // 00a85889  MOVSS [ESP+0x18],XMM0
          "call callee_0041cb40\n\t"          // 00a8588f  CALL 0x0041cb40
          "movl 0x40(%esp), %eax\n\t"        // 00a85894  MOV EAX,[ESP+0x40]
          "pushl %eax\n\t"                   // 00a85898  PUSH EAX
          "leal 0x8(%esp), %ecx\n\t"         // 00a85899  LEA ECX,[ESP+0x8]
          "call callee_00537f40\n\t"         // 00a8589d  CALL 0x00537f40
          "leal 0x4(%esp), %ecx\n\t"         // 00a858a2  LEA ECX,[ESP+0x4]
          "pushl %ecx\n\t"                   // 00a858a6  PUSH ECX
          "leal 0x24(%esi), %ecx\n\t"        // 00a858a7  LEA ECX,[ESI+0x24]
          "call callee_00537dc0\n\t"         // 00a858aa  CALL 0x00537dc0
          "popl %esi\n\t"                    // 00a858af  POP ESI
          "addl $0x38, %esp\n\t"             // 00a858b0  ADD ESP,0x38
          "retl $0x8\n\t");                  // 00a858b3  RET 0x8
}

}  // namespace pkg_w2_00a85840
}  // namespace reconstruction
}  // namespace openspore
