#include "clamp_scalar_to_range_00d00a10.hpp"

namespace openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range {

// The bounds are written into the body as literals, because the literals are
// what the two MOVSS instructions say. The asserts are what stop the two copies
// from drifting apart, and they are checked at compile time.
static_assert(kClampLowerBound == -10.0F,
              "the lower clamp bound in the body is the documented one");
static_assert(kClampUpperBound == 10.0F,
              "the upper clamp bound in the body is the documented one");

// 0x00d00a10 is a forwarding wrapper. It holds no state, allocates nothing
// beyond the frame the three pushes and the two spills need, and its only
// decision is the pair of comparisons below -- so the entire body is:
//
//   result = evaluate_scalar_00d05a20(receiver, first, second, third);
//   result = (result > lower) ? result : lower;   // MAXSS XMM0, [lo]
//   result = (result < upper) ? result : upper;   // MINSS XMM0, [hi]
//   return result;
//
// The comparison form is deliberate and is not interchangeable with std::fmin /
// std::fmax. MAXSS and MINSS return the SECOND source operand whenever the
// ordered comparison is false, which includes the unordered (NaN) case; the
// ternary above reproduces that exactly, whereas `fminf`/`fmaxf` are specified
// to return the non-NaN operand and do not agree here. The model test measures
// the difference on a NaN input, where this body yields kClampLowerBound.
extern "C" float PKG_00D00A10_THISCALL clamp_scalar_to_range_00d00a10(
    OpaqueReceiver* receiver, ForwardedWord first, ForwardedWord second,
    ForwardedWord third) {
  float result = evaluate_scalar_00d05a20(receiver, first, second, third);
  result = (result > -10.0F) ? result : -10.0F;
  result = (result < 10.0F) ? result : 10.0F;
  return result;
}

}  // namespace openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range