// Candidate reconstruction of the body at VA 0x005c8bc0, 39 bytes, 12
// instructions, transcribed one machine instruction at a time from the listing
// in reconstruction/evidence/005c8bc0/evidence.json (categories.disassembly).
//
// What the machine body actually is: a leaf predicate. It makes no call, names
// no data-segment address, dereferences nothing, writes no memory, and holds no
// frame. The only inputs it consumes are the value the caller leaves in ECX and
// the single four-byte argument it pops off the stack, and the only thing it
// produces is a four-byte value in the return register.
//
// The signature below is deliberately NOT the SDK one. The machine-derived ABI
// record for this target abstains (verdict ABI_UNKNOWN, reason
// ecx_read_without_deref): ECX is read but never dereferenced, so the record
// cannot tell a receiver from a plain register argument and refuses to name a
// convention. This candidate therefore names no receiver, no receiver type, and
// no convention, and the two parameters are positional names for the two
// observed inputs only. Whether the ECX input is in fact the object this method
// is called on is left open in the metadata sidecar, not decided here.
//
// The body does not make the convention obvious either, so nothing is claimed
// about it. RET 0x4 is consistent with a callee that popped one four-byte stack
// word, and the record's own candidate list (__stdcall, __thiscall, confidence
// UNKNOWN) is exactly that ambiguity: under __thiscall the ECX input would be a
// receiver, under __stdcall it would be a leftover register value. The body
// reads no memory at all, so there is no receiver dereference to argue from.
//
// Byte-level confirmation (GhidraMCP /read_memory, 39 bytes, same binary
// sha256 as the evidence pack):
//   8bc1 8b4c2404 81f96e513fee 7416 81f9d09d002f 740e 33d2 81f92bedde72
//   0f95c2 4a 23c2 c20400
// Both JZ displacements land on 0x005c8be4, the shared RET 0x4, so the two
// early exits below are one machine branch target reached twice and not two
// distinct behaviours.
//
// The epilogue is RET 0x4, so the caller pushed exactly one four-byte stack
// argument. Live decompilation reports a six-parameter prototype; that prototype
// would require the callee to pop twenty bytes, so it disagrees with the
// machine epilogue and is not adopted. Only the two inputs the machine body
// actually reads are modelled.
//
// Data flow, instruction by instruction:
//
//   MOV EAX,ECX                     result <- the ECX input
//   MOV ECX,dword ptr [ESP + 0x4]   ECX <- the popped stack argument
//   CMP ECX,0xee3f516e / JZ RET     first guard: leave the ECX input untouched
//   CMP ECX,0x2f009dd0 / JZ RET     second guard: leave the ECX input untouched
//   XOR EDX,EDX / CMP ECX,0x72deed2b / SETNZ DL / DEC EDX
//                                   EDX <- all ones when the argument is not the
//                                   third compared value, zero when it is
//   AND EAX,EDX                     mask the saved ECX input
//   RET 0x4                         pop the one stack argument
//
// The return value is therefore the full 32-bit ECX input, or zero when the
// stack argument equals the third compared value. It is declared unsigned int
// because that is the width the machine returns; the ABI record classifies the
// return as unclassified_in_EAX (aggregate_unknown) and live decompilation
// spells it bool, so no narrower type is claimed and the original's return
// contract stays an open question in the sidecar.

namespace {

// One-word alias for the four-byte value the machine moves in the return
// register. It carries no name from the original: the machine-derived ABI
// record leaves the return unclassified, so the type is stated no further than
// the width the body actually returns.
using LoadWord = unsigned int;

}  // namespace

LoadWord palette_page_load_005c8bc0(LoadWord reg_input_ecx, LoadWord stack_input) {
  LoadWord result = reg_input_ecx;
  if (stack_input == 0xee3f516eU) {
    return result;
  }
  if (stack_input == 0x2f009dd0U) {
    return result;
  }
  const LoadWord keep = (stack_input != 0x72deed2bU) ? ~0U : 0U;
  result &= keep;
  return result;
}
