// PKG-W2-00F96840 -- VA 0x00f96840
// FUN_00f96840 (SPORE/SporeBin/SporeApp.exe 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// The complete body: 15 instructions, 0x00f96840..0x00f96869 inclusive, 42 bytes.
// Every line of the transcription below is annotated with the instruction it is.
//
// The listing was re-read from the image for this package rather than taken on
// trust. GhidraMCP /read_memory at 0x00f96840 for 42 bytes returns
//
//   56 8b f1 8b 06 8b 50 70 ff d2 8b 06 8b 50 60 8b ce ff d2 8b 06
//   8b 90 84 00 00 00 c7 86 14 08 00 00 00 00 00 00 8b ce 5e ff e2
//
// and /disassemble_function returns these fifteen instructions at these
// addresses:
//
//   00f96840  56              PUSH ESI
//   00f96841  8b f1           MOV ESI,ECX
//   00f96843  8b 06           MOV EAX,dword ptr [ESI]
//   00f96845  8b 50 70        MOV EDX,dword ptr [EAX + 0x70]
//   00f96848  ff d2           CALL EDX
//   00f9684a  8b 06           MOV EAX,dword ptr [ESI]
//   00f9684c  8b 50 60        MOV EDX,dword ptr [EAX + 0x60]
//   00f9684f  8b ce           MOV ECX,ESI
//   00f96851  ff d2           CALL EDX
//   00f96853  8b 06           MOV EAX,dword ptr [ESI]
//   00f96855  8b 90 84 00 00 00  MOV EDX,dword ptr [EAX + 0x84]
//   00f9685b  c7 86 14 08 00 00 00 00 00 00   MOV dword ptr [ESI + 0x814],0x0
//   00f96865  8b ce           MOV ECX,ESI
//   00f96867  5e              POP ESI
//   00f96868  ff e2           JMP EDX
//
// The instruction lengths are 1+2+2+3+2 +2+3+2+2 +2+6+10+2+1+2 = 42, which is
// ghidra_function.body_span_bytes; the last instruction's two bytes end at
// 0x00f96869, which is ghidra_function.body_end; and abi_derived.parse reports
// {declared_count 15, unparsed 0, degraded false, flow_complete true}. So these
// fifteen are the whole of the body.
//
// WHY THIS ENTRY IS A NAKED TRANSCRIPTION THAT DECLARES NO CONVENTION.
//
// This is the part of the target the machine record explicitly refuses to settle,
// and the refusal is the finding. reconstruction/evidence/00f96840/evidence.json,
// category abi_derived, states:
//
//   verdict                           : ABI_UNKNOWN
//   conventions.calling_convention    : null
//   conventions.confidence            : UNKNOWN
//   conventions.candidate_conventions : ["__cdecl","__stdcall","__thiscall",
//                                       "__fastcall"]
//   conventions.ambiguities           : []
//   abstained_because                 : ["no_terminal_ret: function has no RET
//                                       instruction"]
//   cleanup.bytes / cleanup.side      : null / null, confidence UNKNOWN
//
// The reason is in the listing above and nowhere else: the last instruction is
// JMP EDX. There is no RET, so the terminator that a convention is derived from
// does not exist, and the record says so instead of guessing. So this package
// declares no convention at all -- not __thiscall, not __cdecl, not even a
// "harmless" default. Four candidate conventions are named by the record and this
// entry deliberately satisfies none of them as a claim.
//
// WHAT IS NOT ABSTAINED IS THE RECEIVER, and it is a real derivation rather than
// an inference from the convention. The record states receiver {present true,
// register ECX, confidence INFERRED, shape R-ALIAS, bounds_only true,
// distinct_offsets 2, offsets [0, 2068], max_offset 2068, written_through 1} on
// inference R1, "ECX carries a receiver and is dereferenced before any definite
// write to it". The listing corroborates that reading step for step: 0x00f96841
// copies ECX into ESI, and ECX is not written again until 0x00f9684f, so the
// three reads of [ESI] at 0x00f96843, 0x00f9684a and 0x00f96853 and the single
// write of 0 to [ESI+0x814] at 0x00f9685b are all reached through the alias the
// record describes. The two displacements the record enumerates are exactly the
// two this body touches through the object: 0x0 and 0x814. Neither is named, no
// size is claimed, no layout is claimed and no class is claimed.
//
// WHY A RECEIVER IN ECX IS NOT A CONVENTION, stated here because it is the
// temptation this target invites. A COM/__stdcall object also presents itself in
// the first popped stack word, and nothing in these 42 bytes shows a caller, a
// stack argument, or a terminator that would tell the two apart. The record
// names this address as a slot OF vtable 0x01490be8, which is a fact about how
// the address is REACHED (it is referenced by that table at 0x01490c70) and not
// a statement that the body dispatches or that the table has an owning class.
// This binary carries no MSVC RTTI and no SDK name is recorded for the table, so
// no class, no vtable identity and no receiver type is asserted anywhere here.
//
// FRAME. There is no prologue beyond PUSH ESI, no SUB ESP, no PUSH EBP, no EBP
// frame and no spill: parse.frame reads push_ebp false, mov_ebp_esp false, sub
// null, local_extent 0, seh_or_cookie_frame false. One register is saved, ESI,
// at 0x00f96840 and restored at 0x00f96867 -- and restored BEFORE the transfer
// out, so the routine at table slot 0x84 is entered with the caller's stack
// exactly as it stood at the call, and with ECX holding the receiver.
//
// CONTROL FLOW. Straight-line. There is no conditional branch, no unconditional
// branch inside the span and no second exit: the single transfer out of the body
// is the JMP EDX at 0x00f96868. abi_derived.parse reports flow_complete true over
// all 15 instructions, and the two CALLs at 0x00f96848 and 0x00f96851 both return
// before the tail.
//
// STACK ARITHMETIC. Let E be the ESP at entry. PUSH ESI makes it E-4; nothing
// else in the body touches the stack -- no argument is ever pushed, no argument
// is ever read, and no cleanup is performed, because there is no RET to carry
// one. Both CALLs are entered with ESP = E-4 and return to the same E-4. POP ESI
// at 0x00f96867 restores E, and the JMP at 0x00f96868 leaves it at E. So the
// routine at slot 0x84 is entered with the caller's stack untouched, and the
// body pops exactly what it pushed. Nothing is left behind and nothing is taken.
//
// THE THREE TRANSFERS. All three are register-indirect, and all three are
// two-level: a displacement is read through the word at the receiver's +0x00,
// which the body re-reads before each one, and the result is transferred to.
// abi_derived.dispatch records indirect_calls 3, call_offsets [] and
// vtable_shaped_loads 0, and the model's own reading agrees on the count and on
// the three displacements 0x70, 0x60 and 0x84. No slot is named, no slot's
// occupant is described, and nothing is claimed about what the three routines do:
// all three are outside this body and are modelled by the test as observers.
//
// THE SINGLE WRITE. 0x00f9685b is the body's only store, `MOV dword ptr
// [ESI + 0x814], 0x0`, a ten-byte immediate form that the byte string above
// confirms in full (c7 86 14 08 00 00 00 00 00 00). The displacement 0x814 is
// the largest the record enumerates, and it is the only place this body writes
// anything at all. It is written AFTER both calls and BEFORE the transfer out, so
// the routine at slot 0x84 observes the zeroed word; the model test reads that
// word back at the moment the tail is taken, which is the only place the ordering
// is observable at all.
//
// RETURN. There is none of its own. The value in EAX when the body leaves is the
// word at the receiver's +0x00, written at 0x00f96853 and untouched since; what
// the caller eventually receives in EAX is whatever the routine at slot 0x84
// leaves there, and that routine is outside this body. The machine record names
// EAX as the return register with register_class pointer_like at INFERRED
// confidence and type null, and says void_possible false; no C type is claimed
// here, and `void` on the declaration below is a statement about this entry
// having no terminator, not a claim about the register's contents.
//
// NOT MODELLED, and why:
//   * the calling convention. The record determines none and this package claims
//     none; see the top of this file.
//   * the cleanup side and size. There is no terminator, so the record read
//     neither (cleanup.side null, cleanup.bytes null) and neither is guessed.
//   * the return type. Undetermined: the only exit belongs to a routine outside
//     the body.
//   * the receiver's size, layout, members and identity. bounds_only true and no
//     shape; the two enumerated displacements are carried and nothing is named.
//   * the owning class of vtable 0x01490be8, and of the table read at the
//     receiver's +0x00. No MSVC RTTI, no SDK name, and a slot is not a class.
//   * what the routines at the three slots do, and why the order is 0x70, 0x60,
//     0x84. The order is transcribed; the reason is not observable from here.
//   * the meaning of the word the body loads at 0x00f96843 besides "it is the
//     base of the next displacement".
//   * whether the routine at slot 0x84 returns to this body's caller or does
//     something else entirely. The body hands it control; that is all it shows.

#include "w2_00f96840_types.hpp"

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00f96840 {

// Placed first in this translation unit on purpose: the validator binds a source
// span to 0x00f96840 by the 8-hex VA token appearing in the function name, and
// it takes the FIRST such definition in the file.
//
// The declaration carries the package's NAKED macro and NO calling-convention
// token. That is the machine's answer, not an oversight: the derived record's
// verdict is ABI_UNKNOWN, its confidence is UNKNOWN, its candidate list still
// holds all four conventions, and its abstained_because is "no_terminal_ret:
// function has no RET instruction". There is nothing here for a convention to be
// derived from, and the receiver the record does establish (ECX, R-ALIAS,
// INFERRED) is present under all four of them.
//
// Byte fidelity: thirty-eight of the forty-two positions are pinned against the
// binary's own bytes (kTargetBytes in the header) by the model test, and the four
// that cannot be are the two register moves the assembler spells either way --
// `MOV ESI,ECX` and both occurrences of `MOV ECX,ESI`, written 8b f1 / 8b ce in
// the binary and 89 ce / 89 f1 by the GNU assembler. Both spellings are accepted
// and each of the remaining thirty-eight must match the binary exactly. Unlike a
// body with direct calls, nothing here is a rel32 displacement: all three
// transfers are register-indirect, so no byte in the window encodes an address
// and every one of them is a literal comparison.
//
// A default position-independent build MAY additionally prepend a ten-byte
// __x86.get_pc_thunk.ax PC anchor (g++ -m32 -fPIE prepends one to some naked
// functions; clang++ -m32 emits none here). That is a toolchain artifact and not
// part of the reconstruction. The model test recognises the anchor by its exact
// opcode pair e8 ?? ?? ?? ?? 05 and requires the forty-two target bytes
// immediately after it; a toolchain that emitted some other form of anchor would
// fail that test rather than pass it.
extern "C" void PKG_W2_00F96840_NAKED re_00f96840(void) {
  // The addresses in the annotations below are written WITHOUT an 0x prefix, so
  // that the only 0x literals in this source span are the three slot
  // displacements and the receiver's 0x814 -- which is what the machine listing
  // actually contains, and nothing else.
  __asm__("pushl %esi\n\t"                  // 00f96840  PUSH ESI
          "movl %ecx, %esi\n\t"             // 00f96841  MOV ESI,ECX
          "movl (%esi), %eax\n\t"           // 00f96843  MOV EAX,dword ptr [ESI]
          "movl 0x70(%eax), %edx\n\t"       // 00f96845  MOV EDX,dword ptr [EAX + 0x70]
          "call *%edx\n\t"                  // 00f96848  CALL EDX
          "movl (%esi), %eax\n\t"           // 00f9684a  MOV EAX,dword ptr [ESI]
          "movl 0x60(%eax), %edx\n\t"       // 00f9684c  MOV EDX,dword ptr [EAX + 0x60]
          "movl %esi, %ecx\n\t"             // 00f9684f  MOV ECX,ESI
          "call *%edx\n\t"                  // 00f96851  CALL EDX
          "movl (%esi), %eax\n\t"           // 00f96853  MOV EAX,dword ptr [ESI]
          "movl 0x84(%eax), %edx\n\t"       // 00f96855  MOV EDX,dword ptr [EAX + 0x84]
          "movl $0x0, 0x814(%esi)\n\t"      // 00f9685b  MOV dword ptr [ESI + 0x814],0x0
          "movl %esi, %ecx\n\t"             // 00f96865  MOV ECX,ESI
          "popl %esi\n\t"                   // 00f96867  POP ESI
          "jmp *%edx\n\t");                 // 00f96868  JMP EDX
}

}  // namespace pkg_w2_00f96840
}  // namespace reconstruction
}  // namespace openspore
