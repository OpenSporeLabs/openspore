#include "dogfood_004df420_a1.hpp"

// The header undefines its convention macro at the end, so the implementation
// restates the same convention before it declares the entry.
#if defined(_MSC_VER)
#define PKG_DF420_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_DF420_THISCALL __attribute__((thiscall))
#else
#error "PKG-DOGFOOD-004DF420-A1 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_dogfood_004df420_a1 {

// 0x004df420, 28 bytes, 12 instructions.
//
// Raw bytes read from SporeApp.exe 3.1.0.22 at 0x004df420 this attempt:
//   55 8b ec 51 89 4d fc 8b 45 fc 05 a4 00 00 00 50 8b 4d fc e8 18 01 00 00
//   8b e5 5d c3
//
// What the body proves, and what this reconstruction relies on:
//
//   - One receiver, in ECX. It is spilled to [EBP-0x4] and reloaded twice: once
//     into EAX as a pointer base for the +0xa4 address, once into ECX to be
//     forwarded.
//   - Zero ordinary stack arguments. [EBP+0x8] is never read. The single PUSH
//     is the outgoing argument of 0x004df550, and that callee pops it.
//   - One callee, 0x004df550, entered by direct relative CALL with operands
//     e8 18 01 00 00. No register or memory operand appears, so there is no
//     indirect call and no vtable slot anywhere in this body.
//   - One physical offset, +0xa4, formed by ADD EAX,0xa4 at 0x004df42a.
//   - No global reference: the body names no absolute address.
//   - No branch: a single block, twelve instructions, no conditional and no
//     unconditional jump inside the span.
//   - EBP is the only saved register pushed or written.
//   - The receiver is never dereferenced and no word of it is written.
//
// Return semantics, read from the machine and not from the decompilation: the
// body has no instruction that produces a value in EAX after the CALL, so the
// dword 0x004df550 returns in EAX leaves the frame untouched. The callee's
// epilogue at 0x004df6bc/0x004df6c2 is MOV EAX,[EBP-0x4] / MOV ESP,EBP /
// POP EBP / RET 0x4, so the callee really does produce that dword. Across the
// 58 direct call sites in the xref export the value is consumed by the
// immediately following instruction at 50 of them and within the following
// instructions at 7 more; at 0x00d5d074 no use of EAX follows on the traced
// path. Two sites dereference it, 0x00c02734 reading [EAX+0x5b0] and
// 0x00aec396 reading [EAX+0x51c], each behind a TEST EAX,EAX null guard, which
// is consistent with a pointer but does not prove a declared type.
//
// The Ghidra decompilation of this body is
//   void __fastcall FUN_004df420(int param_1) { FUN_004df550(param_1 + 0xa4); }
// Three defects in it are corrected here and recorded in the sidecar:
//
//   1. The return is not void. The instruction stream forwards a
//   callee-produced
//      dword, and the call sites above consume it. A void model would silently
//      discard the resolved value everywhere.
//   2. The convention is not fastcall. EDX is never read and never forwarded,
//   so
//      no call site sets EDX for this target.
//   3. "param_1" is a receiver, not an argument. Ghidra types it int and places
//      it at register:00000004:4, which is the decompiler reading the ECX spill
//      as a stack parameter. The same value is reloaded into ECX and handed to
//      a callee that dereferences ECX as `this`, and [EBP+0x8] is never read.
//
// What this body does NOT do, and this reconstruction therefore does not model:
// it does not inspect the key, does not test the receiver, does not allocate,
// does not construct and does not store. All of that belongs to 0x004df550,
// which is a different owned VA. The callee's contract is documented in the
// header; its body is not reimplemented here.
extern "C" OpaqueWord PKG_DF420_THISCALL
dogfood_species_key_resolve_fun_004df420(OpaqueSpeciesReceiver *self) {
  // Observed convention: __thiscall. The receiver arrives in ECX, the body
  // reads no entry stack slot, and the bare RET at 0x004df43b releases zero
  // bytes, so the caller performs no callee-side cleanup.
  //
  // The single argument is exactly the value EAX holds after "MOV
  // EAX,[EBP-0x4]" and "ADD EAX,0xa4" at 0x004df427/0x004df42a. No
  // transformation is applied to the receiver: no mask, no widening, no range
  // check, no null test and no comparison appear anywhere in the body, which is
  // why an all-zero key block still reaches the port.
  return unresolved_004df550(self, &self->key_0a4);
}

}  // namespace openspore::reconstruction::pkg_dogfood_004df420_a1
