// PKG-SWARM-W1-005B2490 -- VA 0x005b2490
// FUN_005b2490 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 4 instructions, 0x005b2490..0x005b2497 inclusive, 8 bytes.
// Every line of the model below is annotated with the instruction it comes from.
//
// The listing was re-read from the image for this package rather than taken on
// trust, because a body this short has no room for a boundary error to hide in
// and because the byte count is one of the four things this package was asked to
// pin down. GhidraMCP /read_memory at 0x005b2490 for 8 bytes returns
// 8b 41 18 40 89 41 18 c3, and /disassemble_function at 0x005b2490 returns these
// four instructions at these four addresses:
//
//   005b2490  8B 41 18   MOV EAX,dword ptr [ECX + 0x18]
//   005b2493  40         INC EAX
//   005b2494  89 41 18   MOV dword ptr [ECX + 0x18],EAX
//   005b2497  C3         RET
//
// The instruction lengths are 3 + 1 + 3 + 1, which is 8, which is
// ghidra_function.size_bytes and body_span_bytes, and which agrees with the
// 0x005b2497 terminator address. There is no fifth instruction, no padding, no
// tail: 0x005b2498 is not part of this body and abi_derived.parse reports
// {declared_count 4, unparsed 0, degraded false, flow_complete true}, so the four
// above are the whole of it and not a slice of something longer.
//
// FRAME: none. There is no prologue, no SUB ESP, no PUSH, no POP, no saved
// register and no EBP frame -- the four instructions touch exactly two registers,
// EAX and ECX, and both are volatile on x86-32. Nothing is allocated, nothing is
// spilled, and the stack pointer is the same on entry and on exit.
//
// TERMINATOR: 0x005b2497 is C3, RET with no immediate. Two consequences, both
// machine facts rather than conventions:
//   * the callee pops nothing, so stack_cleanup_bytes is 0 and the cleanup is the
//     caller's. With no immediate there is also no ordinary stack argument being
//     consumed: a `RET imm16` is the only thing in this ABI that eats arguments,
//     and this one eats none.
//   * the body reads no stack slot anywhere -- none of the four instructions has
//     an ESP-relative operand -- so it cannot be reading an argument it does not
//     consume. Zero arguments is read out of the listing, not inferred from the
//     terminator alone.
//
// ABI: __thiscall, receiver in ECX. The abi_derived receiver record says
// {register ECX, shape R-DIRECT, offsets [24], bounds_only true, written_through
// 1}, the abi envelope says {calling_convention __thiscall, hidden_this true,
// hidden_this_register ECX, receiver true, receiver_register ECX, ret_form RET,
// return_register EAX, stack_cleanup_bytes 0, stack_cleanup_owner caller}, and
// the envelope records its own confidence as INFERRED with corroboration
// "not_available" and candidate_conventions [__thiscall, __fastcall].
//
// That missing corroboration is supplied here, from the entry points, and it is
// what upgrades the convention from a record's guess to a fact this body is
// reached only in one way. The three code references to 0x005b2490 are not call
// sites; each is the JMP at the end of a two-instruction adjustor:
//
//   0x0057a5d0  83 E9 04      SUB ECX,0x4    ; E9 B8 7E 03 00  JMP 0x005b2490
//   0x0057a5f0  83 E9 10      SUB ECX,0x10   ; E9 98 7E 03 00  JMP 0x005b2490
//   0x005b8550  83 E9 14      SUB ECX,0x14   ; E9 38 9F FF FF  JMP 0x005b2490
//
// A first argument that a caller-side stub reduces by a constant before the
// transfer, and which is then never consumed, is a `this` pointer; a cdecl
// parameter is passed by value and is not adjusted. The convention's remaining
// candidate, __fastcall, is excluded outright because the body reads no register
// other than ECX, so there is no EDX argument to find. The stub adjusts ECX in
// its own two instructions and this body never writes ECX, so the body itself is
// not an adjustor: obs-0002 records the only definite register writes as EAX (at
// 0x005b2490 and 0x005b2493), and EAX is the return register.
//
// REACHABILITY: there is no direct caller. All eighteen xrefs to 0x005b2490 are
// either data references into virtual-slot tables or the JMP of one of the three
// adjustors above, and the adjustors themselves are referenced only from data.
// So the body is a leaf that is entered only through its slot, never called by
// name in this image. That is a statement about the entry paths, not a claim that
// nothing calls it: an indirect call through a table slot has no static edge.
//
// VIRTUAL DISPATCH: none in the body, and none declared. abi_derived.dispatch
// records indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the
// four instructions contain no register- or memory-operand transfer, no CALL and
// no JMP. The body is a table's slot occupant, which is the opposite of doing
// dispatch: it never reads the word at the receiver's +0x00, so no slot boundary
// is declared anywhere in this model and no dispatch pointer is modelled as a
// member. The slot facts the data segment does fix -- this address at slot +0x00
// of the table at 0x013f57f8, and at slot +0x10 of the table at 0x013f7028 -- are
// recorded in the header for the integrator and are not used to name the slot.
//
// CONTROL FLOW: none. Zero conditional branches, one basic block, no loop, no
// selection, no early exit. Every path through this body is the same four
// instructions; there is no arm to get wrong and no state the caller can steer.
//
// GLOBALS: none. No instruction names a data-segment address; the only absolute
// values in the body are the two 0x18 displacements, which are displacements and
// not addresses. The record's globals category is empty and the xref export
// carries no data-reference edge for this VA.
//
// RETURN: EAX carries the value. The load at 0x005b2490 puts the receiver's word
// in EAX, the INC at 0x005b2493 makes it one larger, and the store at 0x005b2494
// puts that same register back -- so the value returned and the value stored are
// the same one, which is a fact a test can check and not merely a reading. The
// width is 32 bits: a dword is read, all 32 bits of EAX are incremented, and a
// dword is stored. The SIGN is not fixed. `INC EAX` is bit-identical for a signed
// and an unsigned word, no instruction here tests bit 31, and the record's own
// return_semantics is "unclassified_in_EAX" (RT2 register_class
// "aggregate_unknown"), so the reconstruction models an unsigned 32-bit word --
// whose 0xffffffff -> 0x00000000 transition is the machine's own, not a C++
// invention -- and leaves the signedness open in the sidecar. What the word at
// +0x18 IS is not fixed by anything here: this body only ever adds one to it.
//
// DECLARED SPELLING. The signature above declares `std::uint32_t` rather than this
// package's `Word` alias for one reason, and it is a reason about readers rather
// than about the machine: `Word` is a name this package invented, so the width of
// the declared return cannot be computed from the declaration itself, and a
// 4-byte machine return then has nothing to compare against. `std::uint32_t` is
// four bytes on this target and is what 8B / 40 / 89 read, increment and write, so
// it states the machine fact in a form that can be read. The two names are the
// same type, the body below is unchanged by the spelling, and `Word` is still used
// for the receiver's own word, where an alias asks no reader to verify anything.
//
// NOT MODELLED, and why:
//   * the value of EAX on entry. The body overwrites it at 0x005b2490 before
//     reading it, so its incoming value is unobservable and no test can pin it.
//     obs-0002 marks that write definite, and S2 records the same as
//     "entry slot 0 is not written through a pointer" (APPROXIMATION).
//   * the identity of the receiver. The body never stores ECX anywhere, so
//     whether ECX points at the head of the object or at an interior sub-object
//     is invisible from here; the three adjustors are evidence that the
//     +0x18 word lives at more than one displacement in a class hierarchy, and
//     that is as far as this package takes it.
//   * the sign, the width beyond 32, and the meaning of the word. See above.

#include "sw1_005b2490_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_005b2490 {

extern "C" std::uint32_t PKG_SW1_005B2490_THISCALL re_005b2490(Receiver* receiver) {
  // 005b2490  8B 41 18   MOV EAX,dword ptr [ECX + 0x18]
  //
  // The body's first act, and the whole of its read side: one dword at the
  // receiver's displacement 0x18, loaded into EAX. ECX is the receiver and ECX is
  // never copied into another register -- there is no `MOV EDI,ECX` here, which
  // is why the machine-derived receiver record reports shape R-DIRECT rather than
  // the R-ALIAS a body that aliased would carry.
  //
  // One level of indirection and one only: 8B 41 18 is a load of the dword AT
  // ECX+0x18, not a load through a pointer stored there. The model therefore takes
  // the address of the receiver's own +0x18 and reads the word in place; it never
  // follows the word it finds, which is the mistake the model test plants decoys
  // for.
  //
  // The receiver is taken as a byte run and the word is reached by displacement.
  // The record enumerates exactly this one displacement (offsets [24],
  // bounds_only true) and says nothing about which member it is, so the word is
  // unnamed: `opaque` in the struct, "the word at +0x18" in prose.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);
  Word* const word = reinterpret_cast<Word*>(self + 0x18);
  Word value = *word;

  // 005b2493  40         INC EAX
  //
  // One, on all 32 bits, in the register rather than in memory: the machine does
  // not re-read the word to increment it, so the value it adds to is exactly the
  // one just loaded and the model keeps it in a local for the same reason. The
  // opcode 40 is INC r32 and carries no flag operand and no immediate, so there is
  // no hidden constant here: the only constant in the entire body is 0x18.
  //
  // Wraparound is the machine's: 0xffffffff increments to 0x00000000 and 0x80000000
  // to 0x80000001, both as EAX's 32 bits behave. Adding 1u to a std::uint32_t is
  // defined to do exactly that, which is why the arithmetic is unsigned here and
  // why the model's test drives those two values. Nothing signs or tests the word,
  // so no signed-overflow question arises in the model -- the SIGN of the word is
  // unresolved, and this line is where that question lives.
  value = static_cast<Word>(value + 1u);

  // 005b2494  89 41 18   MOV dword ptr [ECX + 0x18],EAX
  //
  // The store, at the same displacement the load used and to the same address:
  // 8B 41 18 and 89 41 18 differ only in direction, so this is a read-modify-write
  // of one dword and not a read of one word and a write of another. The value
  // stored is EAX, i.e. the value the previous instruction produced, i.e. the same
  // value the RET is about to return -- which is why the model returns the local
  // rather than re-reading memory after the store.
  //
  // This is the body's only memory write (receiver.written_through 1) and it is a
  // dword write: four bytes, at 0x18..0x1b, and nothing outside them. The model
  // test asserts that by comparing the receiver byte for byte before and after.
  *word = value;

  // 005b2497  C3         RET
  //
  // The terminator, and the whole of the epilogue: one byte, no immediate, no
  // stack adjustment, no register restore -- consistent with there being no frame
  // and nothing to restore. EAX is returned unaltered from the store above, which
  // is the last thing that touched it. No ordinary stack argument is consumed and
  // no bytes of cleanup are owed, so the caller's stack pointer is the same before
  // and after the call.
  return value;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_005b2490
