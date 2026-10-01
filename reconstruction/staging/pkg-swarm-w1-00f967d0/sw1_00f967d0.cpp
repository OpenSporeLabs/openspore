// PKG-SWARM-W1-00F967D0 -- VA 0x00f967d0
// FUN_00f967d0 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 27 instructions, 0x00f967d0..0x00f96832 inclusive
// (ghidra_function.body_start 0x00f967d0, body_end 0x00f96832, span_bytes 99).
// Every line of the model below is annotated with the instruction it comes from.
//
//   00f967d0  SUB ESP,0x10
//   00f967d3  PUSH ESI
//   00f967d4  MOV ESI,ECX
//   00f967d6  MOV ECX,dword ptr [ESI + 0x20c]
//   00f967dc  CALL 0x0097ef00
//   00f967e1  FMUL float ptr [0x0140f334]
//   00f967e7  FSTP float ptr [ESP + 0x4]
//   00f967eb  MOVSS XMM0,dword ptr [ESP + 0x4]
//   00f967f1  CVTSS2SI EAX,XMM0
//   00f967f5  CVTSI2SS XMM1,EAX
//   00f967f9  MOV ECX,EAX
//   00f967fb  SUB ECX,0x1
//   00f967fe  UCOMISS XMM0,XMM1
//   00f96801  CMOVC EAX,ECX
//   00f96804  MOV ECX,dword ptr [ESP + 0x18]
//   00f96808  MOV dword ptr [ECX],EAX
//   00f9680a  MOV ECX,dword ptr [ESI + 0x20c]
//   00f96810  CALL 0x00fb7bb0
//   00f96815  MOV EDX,dword ptr [ESP + 0x1c]
//   00f96819  MOV dword ptr [EDX],EAX
//   00f9681b  MOV ECX,dword ptr [ESI + 0x20c]
//   00f96821  CALL 0x00fb7bc0
//   00f96826  MOV ECX,dword ptr [ESP + 0x20]
//   00f9682a  MOV dword ptr [ECX],EAX
//   00f9682c  POP ESI
//   00f9682d  ADD ESP,0x10
//   00f96830  RET 0xc
//
// FRAME, resolved once against the entry ESP E. `SUB ESP,0x10` then `PUSH ESI`
// puts ESP at E-0x14 for every displacement in the middle of the body, and the
// epilogue's `POP ESI` + `ADD ESP,0x10` lands back on E exactly, so the walk is
// right. The three argument displacements then check out on their own:
//
//   E-0x14  [ESP+0x00]  ESI, pushed at 0x00f967d3 and popped at 0x00f9682c
//   E-0x10  [ESP+0x04]  the frame's leading dword: the only frame slot the body
//                        writes, and only 0x00f967e7 writes it (FSTP, 4 bytes)
//   E+0x04  [ESP+0x18]  the first ordinary argument
//   E+0x08  [ESP+0x1c]  the second ordinary argument
//   E+0x0c  [ESP+0x20]  the third ordinary argument
//
//   E-0x14 + 0x18 = E+0x04, E-0x14 + 0x1c = E+0x08, E-0x14 + 0x20 = E+0x0c
//
// So the three argument slots are contiguous and in ascending order, and
// `RET 0xc` consumes the return address plus all three. The body's own frame
// never touches any of them: the only ESP-relative writes in the 27 instructions
// are the FSTP at 0x00f967e7 (to E-0x10, above the argument block) and the three
// stores at 0x00f96808 / 0x00f96819 / 0x00f9682a, which are stores THROUGH the
// loaded argument pointers, not stores to the frame.
//
// CONTROL FLOW: one block. There is no branch instruction anywhere in the body.
// The only conditional instruction is the CMOVC at 0x00f96801, and it is modelled
// as the `if` it is, with both of its inputs annotated. The Ghidra
// decompilation's `ROUND(...)` and its `if (x < iVar1) iVar1 = iVar1 - 1` are that
// same CMOVC written as source, and the decompiler's `float10` for the FLD result
// is the x87 register view of it -- the value is rounded to a single by the FSTP
// at 0x00f967e7 before anything else looks at it, which is what the MOVSS at
// 0x00f967eb then reloads.
//
// VIRTUAL DISPATCH: none in the body, and none declared. abi_derived.dispatch
// records indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and all
// three transfers are direct CALLs to immediate targets. The body IS reached
// virtually -- ghidra_function.xrefs carries one reference, DATA from 0x01490c60,
// which is 0x01490be8 + 0x78, so this body is slot index 30 of the table at
// 0x01490be8; the table's own words were read and index 30 is 0x00f967d0 -- but
// the body never reads a dispatch word, so no slot is modelled on the receiver
// and nothing at +0x00 is named. The table's owner class was not established by
// any record available here, so none is asserted.
//
// GLOBALS: exactly one. 0x00f967e1's `FMUL float ptr [0x0140f334]` is the only
// data-segment operand in the body. The four bytes at 0x0140f334 in this image
// are 00 00 80 42, which is binary32 64.0f, and the model READS that word rather
// than embedding the value, because the instruction is a memory operand.

#include "sw1_00f967d0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00f967d0 {
namespace {

// The modelled word at 0x0140f334. It lives at namespace scope because the body
// reads it by address and the test has to be able to change it; see the header
// for why it is a reference and not a constant. The initialiser is the image's
// own four bytes, little-endian: 00 00 80 42.
float g_scale_word = 64.0f;

// Model instrumentation, not machine state: the three call-site stack samples. See
// the header for why they exist and why they are not sampled inside the callees.
std::uint32_t g_call_site_esp[3] = {0u, 0u, 0u};

std::uint32_t sample_current_esp() {
  std::uint32_t value = 0;
  __asm__ __volatile__("movl %%esp, %0" : "=r"(value));
  return value;
}

// 0x00f967f1  CVTSS2SI EAX,XMM0
//
// The x86 single-to-signed-int32 conversion: truncation TOWARD ZERO, and the
// "integer indefinite" result 0x80000000 for a NaN source and for any value
// outside [-2^31, 2^31). 2^31 itself is out of range, and -2^31 is in range,
// which is why the upper test is strict and the lower one is not.
//
// Written as negated ordered comparisons on purpose: every ordered comparison
// against NaN is false, so a NaN source falls into the same arm as an
// out-of-range one, which is what CVTSS2SI does with it.
constexpr std::int32_t kIntegerIndefinite = static_cast<std::int32_t>(0x80000000u);

std::int32_t cvtss2si_00f967f1(float value) {
  if (!(value >= -2147483648.0f)) {  // NaN, or below -2^31
    return kIntegerIndefinite;
  }
  if (!(value < 2147483648.0f)) {   // NaN, 2^31 or above, or +infinity
    return kIntegerIndefinite;
  }
  return static_cast<std::int32_t>(value);
}

// 0x00f967fe  UCOMISS XMM0,XMM1   with   0x00f96801  CMOVC EAX,ECX
//
// UCOMISS raises CF for the ordered case a < b, and it raises CF ALSO in the
// unordered case, which is whenever either operand is a NaN (unordered sets
// ZF, PF and CF together). CMOVC then moves on CF alone, so the decrement fires
// when the scaled value is below its own truncation, and it fires again when the
// scaled value is a NaN. A C++ `<` would not fire on the NaN, which is why the
// NaN test is written out rather than left to the comparison.
//
// The second operand cannot be a NaN: 0x00f967f5 built it by CVTSI2SS from a
// 32-bit integer, so only the first operand is tested for it.
bool carry_is_set_00f967fe(float scaled, float truncated_as_float) {
  return (scaled != scaled) || (scaled < truncated_as_float);
}

// 0x00f967f9  MOV ECX,EAX / 0x00f967fb  SUB ECX,0x1 / 0x00f96801  CMOVC EAX,ECX
//
// The decrement happens in a 32-bit register, so 0x80000000 - 1 wraps to
// 0x7fffffff rather than trapping. Routed through the unsigned type so the wrap
// is defined behaviour in the model instead of signed overflow.
std::int32_t decrement_00f96801(std::int32_t value) {
  return static_cast<std::int32_t>(static_cast<std::uint32_t>(value) - 1u);
}

}  // namespace

float& scale_word_0140f334() { return g_scale_word; }

std::uint32_t call_site_esp_00f967d0(int call_ordinal) {
  if (call_ordinal < 0 || call_ordinal > 2) {
    return 0u;
  }
  return g_call_site_esp[call_ordinal];
}

extern "C" void PKG_SW1_00F967D0_THISCALL re_00f967d0(OpaqueReceiver* receiver,
                                                     std::int32_t* out_scaled,
                                                     Word* out_word_5c0,
                                                     Word* out_word_5c4) {
  // 00f967d0  SUB ESP,0x10
  // 00f967d3  PUSH ESI
  // 00f967d4  MOV ESI,ECX
  //
  // The prologue: a sixteen-byte frame and one saved register. ESI becomes the
  // receiver alias and every receiver access in the body goes through it; ECX is
  // then free to be the argument register. The frame has one used dword
  // ([ESP+0x4], the FSTP scratch below) and twelve unused bytes
  // ([ESP+0x8]..[ESP+0x13]), which is why the frame is not modelled as state:
  // nothing reads it back and nothing outside the body can see it.
  //
  // The receiver is taken as a byte run and reached by DISPLACEMENT. The single
  // displacement is 0x20c and it is read three times; nothing else on the
  // receiver is touched, and the body never writes to the receiver at all.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00f967d6  MOV ECX,dword ptr [ESI + 0x20c]
  //
  // The first of THREE identical reads of the same word. Each one is immediately
  // consumed as the next call's hidden receiver, and the body never keeps the
  // value in a register across a call -- which is observable and which the model
  // test measures by having the first callee change the word: see the reload at
  // 0x00f9680a below.
  OpaquePointee* const first =
      *reinterpret_cast<OpaquePointee* const*>(self + kReceiverPointeeDisplacement);

  // 00f967dc  CALL 0x0097ef00
  //
  // ECX is the pointee, not the receiver. 0x0097ef00's own first instruction is
  // `FLD float ptr [ECX + 0x8]`, so the float comes from the pointee's +0x08 and
  // not from the receiver's. The result arrives in ST0. The callee ends in a
  // bare RET, so it owns no stack cleanup and the body pushed no argument for it.
  g_call_site_esp[0] = sample_current_esp();
  const float sampled = record_get_float_0097ef00(first);

  // 00f967e1  FMUL float ptr [0x0140f334]
  //
  // The only data-segment operand in the whole body. It is a memory operand, so
  // the value is READ, and the model reads its own word at that address rather
  // than embedding the 64.0f the image happens to hold there.
  //
  // 00f967e7  FSTP float ptr [ESP + 0x4]
  //
  // The pop, and it is what rounds the product to a single: the x87 multiply ran
  // at extended precision and the store commits binary32. The model's `float`
  // return type from the helper above forces the same single rounding, because
  // the value has to survive being passed as a float parameter.
  const float scaled = sampled * scale_word_0140f334();

  // 00f967eb  MOVSS XMM0,dword ptr [ESP + 0x4]
  //
  // The reload of what the FSTP just wrote. Round-tripping through the frame is
  // not an observable of its own here -- the store and the load are the same four
  // bytes -- but it is why the model keeps `scaled` a `float` and not a double.
  //
  // 00f967f1  CVTSS2SI EAX,XMM0
  //
  // Truncation toward zero, NOT floor. For a negative scaled value this leaves
  // the result one too high until the CMOVC below fixes it.
  std::int32_t truncated = cvtss2si_00f967f1(scaled);

  // 00f967f5  CVTSI2SS XMM1,EAX
  //
  // The truncation result, back to a single, for the comparison. CVTSI2SS rounds
  // to nearest, and that is irrelevant here: the value came out of a float, so
  // for |x| >= 2^23 the round trip is exact and for |x| < 2^23 both operands are
  // small integers. Either way XMM1 is the truncation and no more.
  const float truncated_as_float = static_cast<float>(truncated);

  // 00f967f9  MOV ECX,EAX
  // 00f967fb  SUB ECX,0x1
  //
  // The candidate is computed unconditionally and then selected, so the -1 is
  // always formed and discarded when the carry is clear.
  //
  // 00f967fe  UCOMISS XMM0,XMM1
  // 00f96801  CMOVC EAX,ECX
  //
  // The body's only decision. CF is XMM0 < XMM1 ordered, plus the unordered case
  // for a NaN XMM0. Since XMM1 is the truncation of XMM0, "XMM0 below its own
  // truncation" is exactly "XMM0 has a fractional part AND is negative", so for
  // every finite in-range XMM0 the pair of these two instructions is floor().
  // That is a DERIVED property of the sequence, not an instruction: the model
  // runs the sequence, because the sequence is also what defines the out-of-range
  // and NaN results, and floor() would not produce those.
  if (carry_is_set_00f967fe(scaled, truncated_as_float)) {
    truncated = decrement_00f96801(truncated);
  }

  // 00f96804  MOV ECX,dword ptr [ESP + 0x18]
  // 00f96808  MOV dword ptr [ECX],EAX
  //
  // The first out parameter, entry ESP+0x04. A POINTER: the body loads the
  // argument word into ECX and stores EAX through ECX, so the store lands in the
  // caller's buffer and not in this frame. It is the only 4-byte write the body
  // makes, and it happens BEFORE the pointee is re-read for the next call.
  *out_scaled = truncated;

  // 00f9680a  MOV ECX,dword ptr [ESI + 0x20c]
  //
  // The second read of the receiver's word -- a fresh load, not the value the
  // first call was given. Anything that changed the word since 0x00f967d6 is
  // visible here, and the model deliberately re-loads rather than reusing `first`
  // so that the test can see the difference.
  OpaquePointee* const second =
      *reinterpret_cast<OpaquePointee* const*>(self + kReceiverPointeeDisplacement);

  // 00f96810  CALL 0x00fb7bb0
  //
  // `MOV EAX,dword ptr [ECX + 0x5c0]` / `RET`: the word at the pointee's +0x5c0,
  // in EAX, with no stack argument and a bare RET terminator.
  g_call_site_esp[1] = sample_current_esp();
  const Word word_5c0 = record_get_word_00fb7bb0(second);

  // 00f96815  MOV EDX,dword ptr [ESP + 0x1c]
  // 00f96819  MOV dword ptr [EDX],EAX
  //
  // The second out parameter, entry ESP+0x08. Also a pointer, and it is loaded
  // into EDX rather than ECX here -- the register choice differs from the other
  // two stores and is fixed by the listing, not by a convention.
  *out_word_5c0 = word_5c0;

  // 00f9681b  MOV ECX,dword ptr [ESI + 0x20c]
  //
  // The third read of the same word, again fresh.
  OpaquePointee* const third =
      *reinterpret_cast<OpaquePointee* const*>(self + kReceiverPointeeDisplacement);

  // 00f96821  CALL 0x00fb7bc0
  //
  // `MOV EAX,dword ptr [ECX + 0x5c4]` / `RET`: the word at the pointee's +0x5c4.
  // Note that this is a different displacement from 0x00fb7bb0's, one dword
  // higher, and the two results go to two different out parameters in
  // argument order. The body does not compute either word itself.
  g_call_site_esp[2] = sample_current_esp();
  const Word word_5c4 = record_get_word_00fb7bc0(third);

  // 00f96826  MOV ECX,dword ptr [ESP + 0x20]
  // 00f9682a  MOV dword ptr [ECX],EAX
  //
  // The third out parameter, entry ESP+0x0c, and the last store in the body.
  *out_word_5c4 = word_5c4;

  // 00f9682c  POP ESI
  // 00f9682d  ADD ESP,0x10
  // 00f96830  RET 0xc
  //
  // The epilogue, unmodelled: the frame comes off and the callee returns past
  // three argument words, which is what `C2 0C 00` means and why the declared
  // convention drops its own arguments. Nothing is produced: ST0 has been empty
  // since 0x00f967e8 and EAX's last writer is the store two instructions above,
  // so the return type is void.
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00f967d0
