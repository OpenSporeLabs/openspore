#include "editor_species_default_wave12.hpp"

// The header undefines its convention macro at the end, so the implementation
// restates the same convention before it declares the entry.
#if defined(_MSC_VER)
#define PKG_ESD12_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ESD12_THISCALL __attribute__((thiscall))
#else
#error \
    "PKG-EDITOR-SPECIES-DEFAULT-WAVE12 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_species_default_wave12 {

// 0x004df420, 28 bytes, 12 instructions.
//
// Raw bytes read from SporeApp.exe 3.1.0.22 at 0x004df420:
//   55              PUSH EBP
//   8b ec           MOV EBP,ESP
//   51              PUSH ECX
//   89 4d fc        MOV dword ptr [EBP + -0x4],ECX
//   8b 45 fc        MOV EAX,dword ptr [EBP + -0x4]
//   05 a4 00 00 00  ADD EAX,0xa4
//   50              PUSH EAX
//   8b 4d fc        MOV ECX,dword ptr [EBP + -0x4]
//   e8 18 01 00 00  CALL 0x004df550
//   8b e5           MOV ESP,EBP
//   5d              POP EBP
//   c3              RET
//
// Observed body, in order:
//   PUSH EBP                              ; 0x004df420
//   MOV EBP,ESP                           ; 0x004df421
//   PUSH ECX                              ; 0x004df423, reserve one local slot
//   MOV dword ptr [EBP - 0x4],ECX         ; 0x004df424, spill the receiver
//   MOV EAX,dword ptr [EBP - 0x4]         ; 0x004df427
//   ADD EAX,0xa4                          ; 0x004df42a, receiver + 0xa4
//   PUSH EAX                              ; 0x004df42f, the one stack argument
//   MOV ECX,dword ptr [EBP - 0x4]         ; 0x004df430, reload the receiver
//   CALL 0x004df550                       ; 0x004df433
//   MOV ESP,EBP                           ; 0x004df438
//   POP EBP                               ; 0x004df43a
//   RET                                   ; 0x004df43b, bare, zero bytes popped
//
// What the body proves, and what this reconstruction relies on:
//
//   - One receiver, in ECX. It is spilled to a local and then used twice, once
//     as a pointer base for the +0xa4 address and once forwarded in ECX.
//   - Zero ordinary stack arguments. [EBP + 0x8] is never read. The single
//     PUSH is the outgoing argument of the callee, and the callee pops it.
//   - One callee, 0x004df550, entered by direct relative CALL. The body
//   contains
//     no CALL through a register or memory operand and no jump table, so there
//     is no virtual dispatch and no indirect call site.
//   - One physical offset, +0xa4 on the receiver, formed by ADD EAX,0xa4 and
//     consumed by the callee.
//   - No global reference: the body contains no absolute address.
//   - No branch: the CFG is a single block, 12 instructions, no conditional and
//     no unconditional jump inside the span.
//   - EBP is the only saved register. Nothing else is pushed and no other
//     callee-saved register is written, so the frame is EBP only.
//   - The receiver is never dereferenced by this body. Pointer arithmetic on a
//     forwarded pointer is not a load, and no word of the receiver is written.
//
// Return semantics, read from the machine rather than from the decompilation:
// the body has no instruction that produces a result in EAX after the CALL, so
// the dword 0x004df550 returns in EAX leaves the frame untouched and reaches
// the caller in EAX. Six observed call sites consume that EAX immediately:
//   0x004d2239 -> 0x004d2241 "MOV dword ptr [ECX], EAX" stores it;
//   0x004d2366 -> 0x004d236b "MOV dword ptr [EBP - 0x30], EAX" stores it;
//   0x00aec385 -> 0x00aec38a stores it, 0x00aec38e "TEST EAX,EAX" null-tests
//   it; 0x00c0272b -> 0x00c02730 "TEST EAX,EAX" null-tests it, then 0x00c02734
//                 "MOVSS XMM2, dword ptr [EAX + 0x5b0]" dereferences it;
//   0x00c04060 -> 0x00c04065 "CMP EDI, EAX" compares it against a cached word;
//   0x00b28f57 -> 0x00b28f5c "MOV ESI, EAX" keeps it in a callee-saved
//   register.
//
// The Ghidra decompilation of this body is
//   void __fastcall FUN_004df420(int param_1) { FUN_004df550(param_1 + 0xa4); }
// which is wrong about the return: it types the function void, while the
// instruction stream leaves a callee-produced dword in EAX and the call sites
// above consume it. The __fastcall attribution is also wrong: EDX is never
// read. Both defects are corrected here and recorded in the metadata sidecar.
//
// The Ghidra local "param_1" is typed int and is reported as living at
// register:00000004:4. That is the decompiler's reading of the ECX spill at
// [EBP - 0x4] as a stack parameter. It is a receiver, not an argument: the same
// value is reloaded into ECX and handed to a callee that dereferences ECX as
// `this`, and no call site pushes anything for this frame.
//
// Not modelled, and not invented:
//
//   - No field name or declared type for the twelve bytes at +0xa4. They are
//     addressed by offset because the offset is observed.
//   - No name for the C++ class. SporeApp.exe carries no MSVC RTTI. The
//   observed
//     receiver producer is the SDK-named singleton accessor 0x00401090, which
//     Ghidra reports as Editors::cSpeciesManager::Get returning the global
//     DAT_015d0c24; every call site sampled feeds its result straight into ECX.
//     That is evidence of the receiver's role, not a proof of the owning class.
//   - No return type beyond "a dword in EAX". The pointer-like dereferences at
//     +0x51c and +0x5b0 are recorded as an open question.
extern "C" OpaqueWord PKG_ESD12_THISCALL
editor_species_resolve_fun_004df420(OpaqueSpeciesLinkRoot *self) {
  // Observed convention: __thiscall. The receiver arrives in ECX, the body
  // reads no entry stack slot, and the bare RET at 0x004df43b releases zero
  // bytes, so the caller performs no callee-side cleanup and the callee owns
  // the one dword it pushed at 0x004df42f, which 0x004df550 pops with its own
  // RET 0x4.
  //
  // The single argument is `self + 0xa4`, exactly the value EAX holds after
  // "MOV EAX,[EBP-0x4]" and "ADD EAX,0xa4" at 0x004df427/0x004df42a. No
  // transformation is applied to the receiver: no mask, no widening, no range
  // check, no null test and no comparison appear anywhere in the body.
  return unresolved_004df550(self, &self->key_0a4);
}

}  // namespace openspore::reconstruction::pkg_editor_species_default_wave12
