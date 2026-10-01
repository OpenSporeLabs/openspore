// PKG-SWARM-W1-010537B0 -- VA 0x010537b0
// FUN_010537b0 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 12 instructions, 0x010537b0..0x010537d3 inclusive
// (ghidra_function.body_start 0x010537b0, body_end 0x010537d5, size_bytes 38).
// Every line of the model below is annotated with the instruction it came from.
//
// The listing was re-derived from the image bytes for this package rather than taken
// on trust. The body's 38 bytes sit at file offset 0x00c53bb0 (.text has VMA 0x401000
// at file offset 0x400, so the offset is 0x010537b0 - 0x401000 + 0x400) and are:
//
//   010537b0  f6 44 24 04 01           TEST byte ptr [ESP + 0x4],0x1
//   010537b5  56                       PUSH ESI
//   010537b6  8b f1                    MOV ESI,ECX
//   010537b8  c7 46 04 58 c4 3e 01     MOV dword ptr [ESI + 0x4],0x13ec458
//   010537bf  c7 06 38 b9 3e 01        MOV dword ptr [ESI],0x13eb938
//   010537c5  74 09                    JZ 0x010537d0
//   010537c7  56                       PUSH ESI
//   010537c8  e8 b3 3b ef ff           CALL 0x00f47380
//   010537cd  83 c4 04                 ADD ESP,0x4
//   010537d0  8b c6                    MOV EAX,ESI
//   010537d2  5e                       POP ESI
//   010537d3  c2 04 00                 RET 0x4
//
// which is the committed 12-instruction listing instruction for instruction, and
// abi_derived.parse agrees it is whole: {declared_count 12, unparsed 0, degraded
// false, flow_complete true, layout json_instruction_list}.
//
// FRAME, resolved once against the entry ESP so every displacement below is a fact.
// Entry ESP is 0 in the walk. `RET 0x4` pops the return address and one 4-byte stack
// word, so control returns with ESP at +8 and the frame balances; the walk is also
// fixed by 0x010537b5/0x010537d2 (`PUSH ESI` ... `POP ESI`, one push and one pop) and
// by 0x010537c7/0x010537cd (one push, and an `ADD ESP,0x4` that the callee did not do,
// because 0x00f47380 returns with a bare `C3`).
//
//   entry+0    the return address
//   entry+4    the one ordinary stack argument. 0x010537b0 reads its LOW BYTE, taken
//              with ESP still at its entry value, which is the only moment in the body
//              at which the argument slot is at entry+4; the machine-derived record
//              agrees (ordinary_stack_arguments[0].entry_offset "entry_ESP+0x4",
//              sizes [1], observed true, read false)
//   entry-4    the saved ESI, pushed at 0x010537b5 and popped at 0x010537d2
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the 12 instructions
// contain no register- or memory-operand transfer -- the single CALL, 0x010537c8, is
// direct to 0x00f47380.
//
// The body is REFERENCED BY tables (the target's export carries 39 xrefs, 20 of them
// data references from .rdata, and the pack's vtables category lists 16
// `vtable:0x...` ids), which is a statement about the address, not about this body:
// the listing never reads a dispatch word. This xref is recorded in the sidecar and
// nothing in the model depends on it. In particular the two constants the body STORES
// are table heads, and storing a pointer to a table is a different act from
// dereferencing one; no slot boundary is declared here and no dispatch word is named.
//
// GLOBALS: two. The immediates 0x013eb938 (0x010537bf) and 0x013ec458 (0x010537b8)
// both lie in .rdata (VMA 0x013cc000, size 0x0013f5ae). The target's own xref export
// carries no data-reference edge type at all, so there is no second machine side to
// corroborate a mode for them; both are WRITES, read off the two MOV instructions'
// own operands, and nothing here reads either word back.

#include "sw1_010537b0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_010537b0 {

extern "C" TableWordPair* PKG_SWARM_W1_010537B0_THISCALL re_010537b0(
    TableWordPair* receiver, std::uint8_t deleting_destructor_flag) {
  // 010537b0  TEST byte ptr [ESP + 0x4],0x1
  //
  // The body's first instruction, executed BEFORE the prologue push, so ESP is still
  // at its entry value and [ESP + 0x4] is the first ordinary stack argument. The
  // width is one BYTE, not a dword: the operand is `byte ptr`, so only the low eight
  // bits of the argument word participate, and only bit 0 of those is tested. The
  // machine-derived record states the same width independently
  // (ordinary_stack_arguments[0].sizes [1]).
  //
  // TEST sets flags without writing anywhere, so the flag survives the two stores
  // that follow and is still the flag the JZ at 0x010537c5 reads. Nothing between
  // here and that branch touches the flags: the two MOVs store to memory and take no
  // flags, and 0x010537b6 is a register move. The branch therefore tests THIS
  // instruction's TEST and nothing else.
  //
  // Polarity: JZ jumps when the result is ZERO, so bit 0 of the argument's low byte
  // being CLEAR skips the release and being SET runs it. A reconstruction that had
  // the polarity inverted would free exactly the objects it should have left alone,
  // which is why the model test drives the flag from both sides and at the boundary.
  const bool release_memory = (deleting_destructor_flag & 0x1u) != 0u;

  // 010537b5  PUSH ESI
  //
  // The callee-saved register, saved before it is written and restored at
  // 0x010537d2. It is not a frame slot the model needs to carry: the model's locals
  // live in the compiler's frame, and the only thing a test can observe about this
  // push is that ESI arrives at the caller unchanged, which the test measures in a
  // trampoline rather than asserting as a convention.
  //
  // 010537b6  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and BOTH stores below go through it. ECX is dead
  // from here on, which is why the machine-derived receiver record reports register
  // ECX with shape R-ALIAS: the record's register is where the receiver ARRIVED, and
  // the listing addresses it through the copy. That alias is also why a scan of the
  // listing for ECX's own operands finds no displacement at all.
  //
  // The copy is a copy: ECX is not adjusted. 0x01053780, the adjustor thunk eight
  // bytes below this body, is `sub ecx,4 / jmp 0x010537b0`, so a caller that holds a
  // sub-object at +0x04 tail-jumps here with a receiver already biased down to the
  // object base. Applying that bias a second time here would be wrong, and the model
  // test drives the sub-object case with a decoy word planted below the passed
  // pointer to catch exactly that.
  //
  // The receiver is taken as a byte run and every access below is a DISPLACEMENT into
  // it. The record enumerates offsets [0, 4] and is bounds_only: it says where the
  // body was seen reaching and not which word is which, so no member is written for
  // either. Nothing at +0x08 or beyond is touched, by this body or by any path of it.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 010537b8  MOV dword ptr [ESI + 0x4],0x13ec458
  //
  // The FIRST store, and it is first: the +0x04 word is written before the +0x00 word
  // is. Four bytes, a displacement of four, and the immediate 0x013ec458 -- read out of
  // the instruction's own bytes (c7 46 04 58 c4 3e 01, little-endian immediate
  // 58 c4 3e 01 = 0x013ec458). The word is not read before the store and not read
  // after it: no instruction in the body loads [ESI] or [ESI+0x4], so whatever was
  // there is destroyed, not consumed. Both the header's kTableHeadAtFour and this
  // literal state the same value, and the model test checks the two against each
  // other rather than trusting either alone.
  *reinterpret_cast<Word*>(self + 0x4) = 0x013ec458u;

  // 010537bf  MOV dword ptr [ESI],0x13eb938
  //
  // The SECOND store, to the object's displacement zero, of the immediate 0x013eb938
  // (bytes c7 06 38 b9 3e 01: no displacement byte at all, so the operand is bare
  // [ESI], and the little-endian immediate 38 b9 3e 01 = 0x013eb938). The absence of
  // a displacement byte in the encoding is why the model adds no offset to the
  // pointer here, rather than writing a zero offset and letting it add: the machine
  // stores at displacement zero by omitting the displacement, and the same opcode
  // with a disp8 form is the instruction above, one byte earlier, so both encodings
  // are present in these 38 bytes. Adding a literal zero would also assert a
  // constant the listing does not contain -- the listing text for this instruction
  // has no offset token at all, and only the store above contributes 0x4.
  //
  // The write ORDER is the machine's and is reproduced: +0x04 first, then +0x00. Both
  // stores precede the conditional call, on both arms, and neither is conditional.
  *reinterpret_cast<Word*>(self) = 0x013eb938u;

  // 010537c5  JZ 0x010537d0
  //
  // The one and only branch. Its target 0x010537d0 is the `MOV EAX,ESI` shared by both
  // arms, and it is inside this body, so the branch graph closes here: there is no
  // loop, no second exit, and no path that leaves the function other than the single
  // RET 0x4. The flags it reads are the ones 0x010537b0 set, three instructions and
  // two stores earlier.
  if (release_memory) {
    // 010537c7  PUSH ESI
    //
    // The receiver, not a derivation of it: ESI holds ECX's entry value unchanged, so
    // the pointer handed over is the object address the caller passed, at whatever
    // bias the caller chose. It is not the +0x04 sub-object, not the value just
    // stored into the object, and not a pointer to either of those.
    //
    // 010537c8  CALL 0x00f47380
    //
    // The one direct transfer out of the body. cdecl, one dword argument: the callee's
    // own body loads [esp+0x4] into EAX, null-checks it, and returns with a bare C3
    // that leaves ESP alone, so the argument comes off here.
    //
    // 010537cd  ADD ESP,0x4
    //
    // The caller-side cleanup the callee's bare RET did not do, which is the other
    // half of the cdecl pairing and the reason the stack is balanced at 0x010537d0.
    heap_release_00f47380(receiver);

    // 010537d0 is reached by falling out of here as well as by the JZ, so both arms
    // converge on the same return.
  }
  // 010537cd falls through to 0x010537d0 as well; the jump above is the only other
  // edge into it.

  // 010537d0  MOV EAX,ESI
  //
  // The return value, and it is the receiver: ESI was never written after 0x010537b6,
  // so EAX holds the object address unchanged on both arms. The release call does not
  // clobber the model's read of it because the model returns the parameter, which is
  // the same value -- and the trampoline in the model test samples EAX itself, at the
  // instruction boundary, so the return really is a register fact and not a C-level
  // convention. (On a real call the callee may leave EAX holding anything; the point
  // established here is what THIS body writes into it, which the listing fixes.)
  //
  // 010537d2  POP ESI
  //
  // The callee-saved register restored, balancing 0x010537b5. Nothing in the body
  // depends on it.
  //
  // 010537d3  RET 0x4
  //
  // One return, and the callee pops four bytes: the argument word at entry+4. The
  // terminator's immediate is the machine's statement that this is a thiscall-shaped
  // function of one stack argument and not a cdecl one, and the model test measures
  // the resulting ESP balance instead of taking the token's word for it.
  return receiver;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_010537b0
