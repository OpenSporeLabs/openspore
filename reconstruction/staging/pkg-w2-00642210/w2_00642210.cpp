// PKG-W2-00642210 -- VA 0x00642210
// FUN_00642210 (SPORE/SporeBin/SporeApp.exe 3.1.0.22)
//
// The complete body: 11 instructions, 0x00642210..0x0064222d inclusive, 30 bytes.
// Every line of the model below is annotated with the instruction it comes from.
//
// The listing was re-read from the image for this package rather than taken on
// trust. GhidraMCP /read_memory at 0x00642210 for 30 bytes returns
//
//   56 8b f1 e8 78 ff ff ff f6 44 24 08 01 74 09 56 e8 5b 51 90 00 83 c4 04
//   8b c6 5e c2 04 00
//
// and /disassemble_function returns these eleven instructions at these addresses:
//
//   00642210  56              PUSH ESI
//   00642211  8b f1           MOV ESI,ECX
//   00642213  e8 78 ff ff ff  CALL 0x00642190
//   00642218  f6 44 24 08 01  TEST byte ptr [ESP + 0x8],0x1
//   0064221d  74 09           JZ 0x00642228
//   0064221f  56              PUSH ESI
//   00642220  e8 5b 51 90 00  CALL 0x00f47380
//   00642225  83 c4 04        ADD ESP,0x4
//   00642228  8b c6           MOV EAX,ESI
//   0064222a  5e              POP ESI
//   0064222b  c2 04 00        RET 0x4
//
// The instruction lengths are 1+2+5+5+2+1+5+3+2+1+3 = 30, which is
// ghidra_function.body_span_bytes; the last instruction's three bytes end at
// 0x0064222d, which is ghidra_function.body_end; and abi_derived.parse reports
// {declared_count 11, unparsed 0, degraded false, flow_complete true}. So these
// eleven are the whole of the body.
//
// WHY THIS ENTRY IS A NAKED __thiscall TRANSCRIPTION RATHER THAN C++.
//
// The derived ABI record for this target DETERMINES the convention
// (reconstruction/evidence/00642210/evidence.json, category abi_derived):
//
//   conventions.calling_convention = __thiscall
//   conventions.confidence         = INFERRED
//   conventions.candidate_conventions = ["__thiscall"]
//   conventions.ambiguities        = []
//
//   receiver.present   = true    receiver.register = ECX
//   receiver.provenance = vftable_slot_dispatch
//   receiver.bounds_only = true   receiver.shape = null
//   receiver.offsets   = []       receiver.written_through = 0
//
//   cleanup.bytes = 4  cleanup.side = callee  cleanup.evidence = "ret 0x4"
//   confidence     = OBSERVED
//
// in two steps the record states separately. R1-VFT puts the receiver in ECX
// because this address is a slot of the vftable based at 0x013ff648 (this body is
// its slot 0) and because the body reads the register that dispatch delivered --
// a COM/__stdcall-shaped body takes its receiver from the first popped stack word
// and never reads its incoming ECX. C6B then names __thiscall from the
// callee-side cleanup together with that receiver register. The caller side
// corroborates it independently and the machine never sees it: the only two code
// references to 0x00642210 in the whole image are the JMPs of two
// two-instruction this-adjusting stubs, SUB ECX,0x10 followed by JMP at
// 0x00642170/0x00642173 and SUB ECX,0x14 followed by JMP at 0x00642180/0x00642183.
// A first argument that a caller-side stub reduces by a constant before the
// transfer is a receiver; a by-value parameter is not adjusted. There is no direct
// CALL into this address at all, which is why the stubs are the only code entries
// there are.
//
// So this entry declares __thiscall (the machine's determination, not a choice
// this package made) AND emits the thirty bytes, because those are two separate
// claims and a C++ restatement would only make the first one.
//
// FRAME. There is no prologue, no SUB ESP, no PUSH EBP and no EBP frame. Exactly
// one register is saved: ESI, pushed at 0x00642210 and popped at 0x0064222a, a
// save/restore pair that brackets the whole body. Nothing is allocated on the
// stack and nothing is spilled: the body's entire local state is that one
// register.
//
// WHY ESI IS SAVED, WHICH IS WHY THE RETURN VALUE IS THE RECEIVER AND NOT
// WHATEVER THE CALLEE LEFT BEHIND. The call at 0x00642213 is a full call whose
// return value lands in EAX. If the receiver were left in ECX it would be lost at
// the first call. ESI exists to carry it across both calls, and the
// `MOV EAX,ESI` at 0x00642228 -- which runs on BOTH paths, because the JZ target
// at 0x0064221d is 0x00642228, the instruction immediately after the dispose block
// -- is what makes the returned value the receiver.
//
// STACK ARITHMETIC. Let E be the entry ESP. PUSH ESI makes it E-4. The callee at
// 0x00642190 consumes no stack argument and is handed nothing to drop, so the
// call returns with ESP = E-4. `TEST byte ptr [ESP + 0x8]` therefore reads the
// byte at E+4, which is the low byte of the caller's first ordinary stack
// argument -- the return address occupies E..E+3. That is the only argument this
// body reads, and the only thing the JZ decides. Afterwards PUSH ESI / CALL /
// ADD ESP,0x4 leave ESP back at E-4, POP ESI restores E, and RET 0x4 leaves the
// caller at E+4: the callee pops four bytes of stack argument, exactly as
// abi_derived.abi records (stack_cleanup_bytes 4, stack_cleanup_owner "callee",
// evidence "ret 0x4"). ONE callee-popped stack word, and no more.
//
// THE OPTION WORD IS DATA, NOT A RECEIVER. The word at entry_ESP+0x4 is read for
// bit 0 and bit 0 only, and it is never handed to either callee and never becomes
// the value in EAX. The receiver is a different value entirely: it arrives in
// ECX, is aliased into ESI at 0x00642211, is passed to 0x00642190 in ECX and to
// 0x00f47380 on the stack, and is what the tail puts in EAX. Conflating the two
// would be the one substantive ABI error available here, so the model test keeps
// them apart: it drives the option word over the whole byte range and the
// receiver over five interior positions, and it feeds the body a receiver that is
// null, an interior pointer and a value no fixture address can equal.
//
// CONTROL FLOW. One conditional branch, `JZ 0x00642228`, and its target is the
// third of the four instructions after it -- the tail of the body. So the branch
// skips exactly one five-byte call and one three-byte stack adjustment and lands
// on the common return. There is no loop, no second exit, no fall-through off the
// end of the body, and no path on which the epilogue is not reached: both paths
// converge on 0x00642228.
//
// GLOBALS. None. The eleven instructions name no data-segment address; the two
// immediates that are addresses are 0x00642190 and 0x00f47380, both call targets
// inside .text. The record's globals category is empty and the xref export
// carries no data-reference edge type for this VA. (0x00642190 does name absolute
// addresses, but that is the callee's business and none of it is imported into
// this body.)
//
// VIRTUAL DISPATCH. None in the body, and none declared. abi_derived.dispatch
// records indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the
// eleven instructions contain no register- or memory-operand transfer: both
// transfers are CALLs with an immediate operand. The body is itself a table slot
// occupant -- GhidraMCP /read_memory at 0x013ff648 puts 0x00642210 in that word,
// the first slot of the table the record bases there -- which is the opposite of
// dispatching: it never reads the word at the receiver's +0x00. So no slot
// boundary is declared and no dispatch pointer is modelled as a member.
//
// RETURN. EAX carries the value, 32 bits wide, and evidence_returns.classify
// reads the state as WIDTH_4_IN_EAX off the complete listing: EAX is written
// once, at 0x00642228, by a register-to-register MOV, on every path to the
// single reachable RET. The C type of that width is a source-side choice, and
// `Receiver *` is the one the machine points at: the value written is the
// receiver. The machine record's own return_semantics is
// "unclassified_in_EAX" (RT2 register_class "aggregate_unknown"), which is a
// statement about the record and not a licence to declare void or an aggregate.
//
// NOT MODELLED, and why:
//   * the receiver's size, layout and members. This body never dereferences it.
//   * the receiver's IDENTITY. Whether the incoming ECX points at the head of the
//     object or at an interior sub-object is invisible from here: the two entry
//     stubs adjust ECX by 0x10 and 0x14 before arriving, so the body is reached at
//     two different displacements, and it neither adds nor subtracts anything.
//   * the class that owns the table 0x013ff648. The binary carries no MSVC RTTI
//     and no SDK name is recorded for it.
//   * the meaning of the 31 argument bits this body never tests. Only bit 0 is
//     read; the rest are copied by nobody and examined by nobody.
//   * what either callee does. Both are declared in the header and defined by the
//     model test as observers. The body models the calls, their order, their
//     arguments and their stack discipline -- which is all the eleven instructions
//     contain -- and nothing about either callee's internals.

#include "w2_00642210_types.hpp"

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00642210 {

// Placed first in this translation unit on purpose: the validator binds a source
// span to 0x00642210 by the 8-hex VA token appearing in the function name, and
// it takes the FIRST such definition in the file.
extern "C" Receiver* PKG_W2_00642210_NAKED_THISCALL re_00642210(Receiver*,
                                                                 OptionWord) {
  // The convention is __thiscall: the receiver arrives in ECX and this callee
  // pops its one stack word itself, in the `retl $4` two lines below.
  //
  // Byte fidelity: twenty-eight of the thirty bytes are pinned against the
  // binary's own bytes (kTargetBytes in the header) by the model test. Two of the
  // thirty cannot be, and each is pinned differently rather than waved through:
  //
  //   * the two rel32 displacements of the CALLs at 0x00642213 and 0x00642220.
  //     They encode addresses in a different image, so the test RESOLVES each one
  //     and requires it to land on the callee the xref export names for that
  //     callsite -- 0x00642190 and 0x00f47380 respectively -- which is a real
  //     constraint on the emitted code rather than a spelling.
  //   * two register moves. The binary encodes 0x00642211 as 8b f1 (MOV ESI,ECX)
  //     and 0x00642228 as 8b c6 (MOV EAX,ESI); the GNU assembler writes 89 ce
  //     and 89 f0 for the same operands. Both spellings are accepted, and each of
  //     the remaining twenty-eight positions must match the binary exactly.
  //     clang++ emits the binary's 8b f1 / 8b c6; g++ emits 89 ce / 89 f0.
  //
  // A default position-independent build MAY additionally prepend a ten-byte
  // __x86.get_pc_thunk.ax PC anchor (g++ -m32 -fPIC prepends one to some naked
  // functions; clang++ -m32 emits none here). That is a toolchain artifact and
  // not part of the reconstruction. The model test recognises the anchor by its
  // exact opcode pair e8 ?? ?? ?? ?? 05 and requires the thirty target bytes
  // immediately after it; a toolchain that emitted some other form of anchor
  // would fail that test rather than pass it. Byte-identical recompilation is
  // therefore NOT claimed without that allowance; semantic fidelity is, and it is
  // what the executed checks below establish.
  __asm__("pushl %esi\n\t"              // 00642210  PUSH ESI
          "movl %ecx, %esi\n\t"         // 00642211  MOV ESI,ECX
          "call teardown_00642190\n\t"  // 00642213  CALL 0x00642190
          "testb $0x1, 8(%esp)\n\t"     // 00642218  TEST byte ptr [ESP + 0x8],0x1
          "jz 1f\n\t"                   // 0064221d  JZ 0x00642228
          "pushl %esi\n\t"              // 0064221f  PUSH ESI
          "call dispose_00f47380\n\t"   // 00642220  CALL 0x00f47380
          "addl $0x4, %esp\n\t"         // 00642225  ADD ESP,0x4
          "1:\n\t"                      // 00642228  the JZ target
          "movl %esi, %eax\n\t"         // 00642228  MOV EAX,ESI
          "popl %esi\n\t"               // 0064222a  POP ESI
          "retl $4\n\t");               // 0064222b  RET 0x4
}

}  // namespace pkg_w2_00642210
}  // namespace reconstruction
}  // namespace openspore
