// PKG-SWARM-W1-005C0DD0 -- VA 0x005c0dd0
// FUN_005c0dd0, subsystem Sporepedia (SPORE/SporeBin/SporeApp.exe 3.1.0.22,
// image base 0x400000, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// THE COMPLETE BODY: 2 instructions, 0x005c0dd0..0x005c0dd3 inclusive, 4 bytes.
//
//   005c0dd0  8A 41 24    MOV AL, byte ptr [ECX + 0x24]
//   005c0dd3  C3          RET
//
// The listing this was written against was re-derived from the image bytes for
// this package rather than taken on trust, because at four bytes long there is
// nothing else to cross-check it against. GhidraMCP /read_memory at 0x005c0dd0
// returns `8A 41 24 C3 CC CC CC CC` (decimal 138 65 36 195 204 204 204 204),
// and /disassemble_bytes over 0x005c0da0..0x005c0def gives the same two
// instructions at the same addresses with a twelve-byte 0xCC run from 0x005c0dd4
// to 0x005c0ddf, preceded by `RET 0x8` at 0x005c0dc1 and its own padding from
// 0x005c0dc4. So the span really is four bytes and the stub really is isolated.
//
// WHAT IS FIXED, AND BY WHAT
//
//  * THE RECEIVER IS READ, NOT WRITTEN. The one memory operand is based on ECX
//    and is a load (8A = MOV r8, r/m8). There is no store instruction in the
//    body and no other register is written at all. The machine-derived receiver
//    record agrees in its own terms: {register ECX, shape R-DIRECT, written_through
//    0, offsets [36], max_offset 36, distinct_offsets 1, bounds_only true}. The
//    model therefore takes the receiver and returns a value; the test diffs the
//    whole receiver before and after and requires it byte-identical.
//
//  * THE RECEIVER IS ECX AND ONLY ECX. ECX is read by the load and is never
//    written first, so there is no shadowing the way there would be in a body
//    that copied its receiver into a scratch register. Nothing else in the
//    listing is even a register operand, so the field is reachable through no
//    other register and through no pointer stored in memory.
//
//  * THE VALUE IS ONE BYTE, READ AT DISPLACEMENT 0x24. The destination operand
//    of 8A is AL, so the machine's return width is one byte -- read off the
//    operand, not inferred from the fact that accessors like this one return
//    flags. The displacement is the instruction's own disp8 (the third byte of
//    the encoding) and it is the same 0x24 the receiver record enumerates as
//    offset 36. The model reads it as a BYTE, and the test drives a four-byte
//    pattern across 0x24..0x27 so that a word-sized or dword-sized read would
//    return a different number.
//
//  * THIS IS NOT A DISPATCH, AND NOT A CONSTANT STUB. dispatch records
//    indirect_calls 0, call_offsets [] and vtable_shaped_loads 0. The load is
//    through a base REGISTER, which is what a field read looks like, and there
//    is no second dereference anywhere, so a one-level-vs-two-level dispatch
//    question does not arise: there is no dispatch. Conversely the value is
//    not a constant: it comes out of the receiver, and the test drives the
//    receiver's byte through 0x00, 0x01, 0x7f, 0x80, 0xfe and 0xff and requires
//    the result to track it in every case, which a "return true" or "return 1"
//    stub cannot do.
//
//  * ZERO ORDINARY STACK ARGUMENTS, ZERO CALLEE CLEANUP. The terminator is a
//    bare `RET` -- one byte, 0xC3, with no immediate -- and the body contains no
//    read of ESP or of any [EBP+k] frame slot, so there is no argument slot to
//    account for. stack_arguments records observed_slots 0, derived_slots 0,
//    total_bytes 0, gaps 0; cleanup records bytes 0 on the caller's side, with
//    the evidence string "ret with no immediate, no stack reads". The model
//    takes the receiver and nothing else, and the test MEASURES the shape rather
//    than asserting the convention: it pushes a decoy word, calls, and samples
//    ESP after the return. The residual is required to be exactly four bytes,
//    which is what a zero-byte callee cleanup looks like and what a `RET 4`
//    reconstruction would not produce.
//
//  * THE TERMINATOR FORM IS `RET`, NOT `RET imm16`. Read off the byte at
//    0x005c0dd3 (0xC3) against kBodyBytes in the header. A body of four bytes
//    cannot carry `C2 nn nn`, and the image byte settles it rather than a
//    length argument.
//
// RETURN SEMANTICS -- WHAT IS CLAIMED AND WHAT IS NOT
//
// The declared type is std::uint8_t. What the machine fixes is the WIDTH: one
// byte, in AL, from receiver+0x24. What it does not fix is the C++ spelling --
// `bool`, `unsigned char` and `std::uint8_t` all compile to these three bytes --
// so the widest claim available from the width alone is a one-byte unsigned
// value, and that is what is declared. `bool` is specifically NOT claimed,
// because a `bool` return would assert the value is {0, 1} and nothing in these
// two instructions masks anything: the byte at 0x24 is returned verbatim, and a
// reconstruction that normalised it would be inventing a domain. `int` is not
// claimed either, because the machine writes AL and not EAX, so a four-byte
// return would assert four bytes the body does not produce.
//
// Bits 8..31 of EAX: NOT ASSERTED, and deliberately so. 8A 41 24 is a partial
// register write -- it is not 0F B6 41 24 (MOVZX EAX, byte ptr [ECX+0x24],
// four bytes) -- so the body leaves the upper three bytes of EAX exactly as the
// caller left them. Asserting a zero-extension here would assert an instruction
// the image does not contain. What settles it as UNOBSERVABLE is the two direct
// callers, both of which consume AL alone:
//   0x00adfeaa CALL 0x005c0dd0 -- 0x00adfeb2 `MOV byte ptr [ESI + 0x170], AL`:
//     the low byte is stored into a byte field, and the upper three bytes are
//     never read.
//   0x00de5273 CALL 0x005c0dd0 -- 0x00de5278 `TEST AL, AL` / 0x00de527a `JNZ`:
//     a zero test on the low byte alone.
// The model test samples the full EAX at the return and asserts only bits 0..7,
// and says so at the check. A one-byte return has unspecified upper bits in the
// i386 convention too, so the model and the machine agree that the upper three
// bytes carry no information; the test just refuses to pretend to check them.
//
// A CONTRADICTION IN THE MACHINE RECORD, RESOLVED AGAINST THE RECORD. The
// persisted ABI envelope and the derived return sub-record both classify this
// value as `pointer_like_in_EAX` / register_class "pointer_like", and there is no
// `return_type` at all. That classification is a machine artifact of the shape
// of the memory operand -- a base-register operand read out of a pointer -- and
// the listing refutes it: the last and only definition of EAX is a ONE-BYTE load
// from the receiver, which is not a pointer load and has pointer width nowhere
// in it. The record is reported as contradicted rather than adopted, because a
// `pointer_like` return would make the reconstruction claim a pointer the body
// does not return. The validator's own width oracle (WIDTH_1_IN_EAX, from the AL
// destination operand) is the one that agrees with the bytes.
//
// GLOBALS: none. Neither instruction names an absolute operand, and the source
// span below names none. Note that the file header above is deliberately outside
// the function span, and the twelve data-segment table addresses live in the
// package header for exactly that reason: a data address written inside the
// function's own comment would read as a global reference this body does not
// have.
//
// NO CALLEE IS DECLARED AND NONE IS CALLED. Two instructions, neither of them a
// transfer. `callees` is empty, the xref export records no outgoing edge, and
// the model test has no callee observer because there is nothing to observe.

#include "swarm_w1_005c0dd0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_005c0dd0 {

extern "C" std::uint8_t PKG_SWARM_W1_005C0DD0_THISCALL re_005c0dd0(
    SporepediaByteRecord* receiver) {
  // 005c0dd0  MOV AL, byte ptr [ECX + 0x24]      ; 8A 41 24
  //
  // ECX is the receiver and stays in ECX: there is no prologue and no
  // MOV EDI,ECX-style alias, so the base register of the load is the receiver
  // register itself. The operand is a BYTE read at the instruction's own
  // displacement, from the receiver itself and not from anything the receiver
  // points at -- there is no second dereference in the body, so the receiver is
  // the object and not a holder for one.
  const std::uint8_t* const self =
      reinterpret_cast<const std::uint8_t*>(receiver);

  // 0x24 is the disp8 of the encoding (the third byte of 8A 41 24) and the same
  // displacement the machine-derived receiver record enumerates as offset 36.
  // One byte, exactly: the three bytes after the displacement in the instruction
  // stream are the next instruction, not a wider operand.
  const std::uint8_t value = self[0x24];

  // The return width is one byte because the destination operand of 8A is AL.
  // Bits 8..31 of EAX are not this body's to set and are not modelled; see the
  // return-semantics section of the file header for the two call sites that
  // establish they are unobservable.
  return value;

  // 005c0dd3  RET                              ; C3
  //
  // A bare RET with no immediate, so the callee pops nothing: there are no
  // ordinary stack arguments, and the receiver arrived in ECX. Nothing is left
  // to do at the return -- no spill, no tail call, no stack restore -- because
  // the body never touched ESP and saved no register.
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_005c0dd0
