#include "scalar_threshold_band_00d00a70.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00D00A70_THISCALL __thiscall
#else
#define PKG_00D00A70_THISCALL __attribute__((thiscall))
#endif

// 0x00d00a70 FUN_00d00a70 - a five-way band index over one clamped scalar.
//
// The body is 58 instructions, 0x00d00a70..0x00d00b35, seven conditional
// branches all landing inside that span, one direct call, no indirect transfer,
// one direct callee. It forwards three stack words to 0x00d05a20, clamps what
// comes back into [-10.0, +10.0], and returns an immediate from {0,1,2,3,4}
// chosen by four comparison tests against four floats on the receiver.
//
// Nothing here is inferred from the decompiler. Where the decompiler's
// rendering of 0x00d00a70 disagrees with the listing -- and it does, on the
// unordered compare -- the listing wins and the disagreement is recorded in
// `conflicts` in the metadata sidecar.
//
// Two machine details are carried deliberately, because both are observable and
// a tidier transcription would lose them:
//
//   * MAXSS then MINSS, in that order, with the memory operand SECOND on each.
//     On an unordered pair `MAXSS` writes the second source, so a NaN coming
//     back from the callee leaves through the LOWER bound and not the upper
//     one. Reversing the two operations sends the same NaN out the other end.
//   * Every comparison goes through the CF/ZF pair COMISS really produces. On
//     an unordered pair it sets CF=ZF=1, so BOTH `JBE` and `JC` are taken,
//     while C++ `a <= b` and `a < b` are false. Any of the four receiver floats
//     may hold a NaN, and when one does the band's answer is not the one the
//     arithmetic reading gives.

namespace openspore::reconstruction::pkg_00d00a70_scalar_threshold_band {

std::int32_t PKG_00D00A70_THISCALL scalar_threshold_band_00d00a70(
    OpaqueReceiver* receiver, ForwardedWord first, ForwardedWord second,
    ForwardedWord third) {
  // 00d00a70 SUB ESP,0x10
  // 00d00a73 MOV EAX,dword ptr [ESP+0x1c]   third incoming word  (entry+0xc)
  // 00d00a77 MOV EDX,dword ptr [ESP+0x14]   first incoming word   (entry+0x4)
  // 00d00a7b PUSH ESI
  // 00d00a7c MOV ESI,ECX                    the receiver, kept in ESI because
  //                                         the callee will clobber ECX
  // 00d00a7e MOV ECX,dword ptr [ESP+0x1c]   second incoming word  (entry+0x8)
  //
  // The three words are read off their own incoming slots before anything is
  // pushed, which is why they can be forwarded in the order the listing reads
  // them and not in a single load-and-push run. Second, not first, is read last.
  //
  // 00d00a82 PUSH EAX / 00d00a83 PUSH ECX / 00d00a84 PUSH EDX -- pushed in
  // reverse so the callee sees them in argument order; then
  // 00d00a85 MOV ECX,ESI restores the receiver into ECX, which is the register
  // the callee's `MOV EDI,ECX` at 0x00d05a26 reads.
  //
  // 00d00a87 CALL 0x00d05a20 -- not reconstructed here; see the header. The
  // result arrives in ST0.
  const float value = evaluate_scalar_00d05a20(receiver, first, second, third);

  // 00d00a8c FSTP dword ptr [ESP+0x4]
  //   The x87 result is stored through FSTP as a 32-bit binary32 value, so the
  //   stack slot and every later MOVSS/COMISS in this body is single
  //   precision. Not a double round trip.
  //
  // 00d00a90..00d00aa6
  //   The two bounds are loaded from their global addresses and spilled to
  //   stack slots before use. Both are 4-byte reads of the same two words the
  //   sibling package at 0x00d00a10 clamps with.
  //
  // 00d00ab2 MAXSS XMM0,dword ptr [ESP+0x1c]   value = max(value, LOWER)
  // 00d00ab8 MINSS XMM0,dword ptr [ESP+0x20]   value = min(value, UPPER)
  // 00d00abe MOVSS dword ptr [ESP+0x4],XMM0    the clamped value is what the
  //                                              four band tests below read.
  const float clamped = minss(maxss(value, kClampLowerBound), kClampUpperBound);

  // 00d00ac4 MOVSS XMM1,dword ptr [ESI+0x14]  -- f14, loaded ONCE and kept in
  //                                                 XMM1 for the whole body,
  //                                                 which is why the last test
  //                                                 at 0x00d00b18 compares
  //                                                 against XMM1 and does not
  //                                                 reload it.
  const float edge14 = band_edge(receiver, kEdgeDisplacement14);

  // 00d00ac4..00d00ade  band 2
  //   COMISS XMM0,XMM1 / JBE  -> not(v <= f14) i.e. v >  f14
  //   COMISS XMM2,XMM0 / JBE  -> not(f18 <= v)  i.e. v <  f18
  // Strictly between the first and second edge. Both ends open -- the listing
  // has no equality case here and neither does this.
  if (!comiss_jbe(clamped, edge14) && !comiss_jbe(band_edge(receiver, kEdgeDisplacement18), clamped)) {
    // 00d00ade MOV EAX,0x2
    return 2;
  }

  // 00d00aea..00d00afa  band 3
  //   COMISS XMM0,[ESI+0x18] / JC -> not(v <  f18) i.e. v >= f18
  //   COMISS XMM2,XMM0     / JBE -> not(f1c <= v) i.e. v <  f1c
  // Lower end INCLUSIVE, upper end open.
  if (!comiss_jc(clamped, band_edge(receiver, kEdgeDisplacement18)) &&
      !comiss_jbe(band_edge(receiver, kEdgeDisplacement1c), clamped)) {
    // 00d00afa MOV EAX,0x3
    return 3;
  }

  // 00d00b06..00d00b0c  band 4
  //   COMISS XMM0,[ESI+0x1c] / JC -> not(v < f1c) i.e. v >= f1c
  // No upper test: nothing above this band.
  if (!comiss_jc(clamped, band_edge(receiver, kEdgeDisplacement1c))) {
    // 00d00b0c MOV EAX,0x4
    return 4;
  }

  // 00d00b18..00d00b23  band 1
  //   COMISS XMM1,XMM0 / JC     -> not(f14 < v) i.e. v <= f14  (XMM1 still f14)
  //   COMISS XMM0,[ESI+0x10]/JBE -> not(v <= f10) i.e. v >  f10
  // Upper end INCLUSIVE of f14, lower end open above f10. Checked LAST, after
  // bands 2, 3 and 4 have all declined: the listing is a fall-through chain
  // and not a binary search over an ordered key.
  if (!comiss_jc(edge14, clamped) &&
      !comiss_jbe(clamped, band_edge(receiver, kEdgeDisplacement10))) {
    // 00d00b23 MOV EAX,0x1
    return 1;
  }

  // 00d00b2f XOR EAX,EAX -- the fall-through case. Reached when the value is at
  // or below the +0x10 edge, and also by any path where an unordered compare
  // routed here. Not a default the compiler invented: it is a spelled `XOR`.
  return 0;
}

}  // namespace openspore::reconstruction::pkg_00d00a70_scalar_threshold_band

#undef PKG_00D00A70_THISCALL
