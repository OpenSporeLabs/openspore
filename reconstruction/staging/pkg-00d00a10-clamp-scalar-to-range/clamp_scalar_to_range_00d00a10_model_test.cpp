#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "clamp_scalar_to_range_00d00a10.hpp"

namespace openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range {
namespace {

// The number of named checks that have run. Reported at the end so the gate can
// see that the mutation build really executed the cases rather than exiting at
// the first failure.
int g_checks = 0;

// The failure path is a counted one, not an immediate exit, so a mutant's blast
// radius is measurable rather than binary. A failing case prints its name and
// keeps going; the process exits non-zero at the end if any case failed.
int g_failures = 0;

void report_case(const char* name, bool passed) {
  ++g_checks;
  if (passed) {
    return;
  }
  ++g_failures;
  std::printf("FAIL %s\n", name);
}

#define CHECK_CASE(name, expression) \
  report_case(name, static_cast<bool>(expression))

float from_bits(std::uint32_t bits) {
  float value = 0.0F;
  std::memcpy(&value, &bits, sizeof(value));
  return value;
}

std::uint32_t to_bits(float value) {
  std::uint32_t bits = 0U;
  std::memcpy(&bits, &value, sizeof(bits));
  return bits;
}

// ---- the evaluator this function forwards to -------------------------------
//
// The body of 0x00d05a20 is 279 instructions and is not reconstructed. What
// the listing at 0x00d00a10 shows about it is its ABI -- receiver in ECX, three
// 4-byte stack words, result in ST0, callee pops 12 -- and that is all this
// stub models. The value it hands back is whatever the case sets, which is what
// lets the clamp itself be measured.
struct ForwardedCall {
  OpaqueReceiver* receiver;
  ForwardedWord first;
  ForwardedWord second;
  ForwardedWord third;
};

ForwardedCall g_last_call{};
float g_next_result = 0.0F;
int g_call_count = 0;

}  // namespace
}  // namespace openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range

// Defined at namespace scope so it carries C linkage and the thiscall
// convention the header declared, exactly as the real callee does.
extern "C" float PKG_00D00A10_THISCALL
openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range::
    evaluate_scalar_00d05a20(OpaqueReceiver* receiver, ForwardedWord first,
                             ForwardedWord second, ForwardedWord third) {
  g_last_call.receiver = receiver;
  g_last_call.first = first;
  g_last_call.second = second;
  g_last_call.third = third;
  ++g_call_count;
  return g_next_result;
}

namespace openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range {
namespace {

// Run the wrapper with the evaluator returning `value`, and return what the
// wrapper returns.
float clamp_with(float value, ForwardedWord first = 0U, ForwardedWord second = 0U,
                 ForwardedWord third = 0U, OpaqueReceiver* receiver = nullptr) {
  g_next_result = value;
  return clamp_scalar_to_range_00d00a10(receiver, first, second, third);
}

// 1. The three words reach the evaluator, in order, each exactly once.
//
// The values are opaque 4-byte words as far as this evidence goes, so the only
// claim available is the mapping: ordinal 1, 2, 3 of the incoming stack arrive
// at the callee's ordinal 1, 2, 3, unswapped and unduplicated. Distinct
// sentinels are what make a swap or a duplicate detectable.
void test_forwards_three_words_in_order() {
  auto* receiver = reinterpret_cast<OpaqueReceiver*>(0x10000U);
  g_call_count = 0;
  (void)clamp_with(1.0F, 0x11111111U, 0x22222222U, 0x33333333U, receiver);

  CHECK_CASE("forwards: calls the evaluator exactly once", g_call_count == 1);
  CHECK_CASE("forwards: receiver is forwarded unchanged",
             g_last_call.receiver == receiver);
  CHECK_CASE("forwards: first word arrives first", g_last_call.first == 0x11111111U);
  CHECK_CASE("forwards: second word arrives second", g_last_call.second == 0x22222222U);
  CHECK_CASE("forwards: third word arrives third", g_last_call.third == 0x33333333U);
}

// 2. A value already inside the range comes back bit-identical.
//
// "Unchanged" is checked on the bit pattern, not on a numeric equality, so a
// reconstruction that returned the range endpoint for an interior value, or that
// perturbed the sign of a zero, cannot pass.
void test_interior_value_passes_through_unchanged() {
  const float samples[] = {
      0.0F,
      -0.0F,
      5.5F,
      -5.5F,
      0.25F,
      -9.999F,
      9.999F,
      1.0e-30F,   // far below resolution but inside the range
      -1.0e-30F,
      9.9999995F,
      -9.9999995F,
      10.0F - 1.0e-6F,
      -(10.0F - 1.0e-6F),
  };
  for (float sample : samples) {
    const std::uint32_t expected = to_bits(sample);
    const std::uint32_t actual = to_bits(clamp_with(sample));
    CHECK_CASE("interior: value is returned bit-identical", actual == expected);
  }
}

// 3. A value below the range becomes exactly the lower bound, and one above
// becomes exactly the upper bound. The endpoints are compared as bit patterns
// so that a bound of -9.999F or a clamp applied in double cannot pass.
void test_out_of_range_values_become_the_bounds() {
  const float lows[] = {-10.0001F, -100.0F, -1.0e30F, -3.4028235e38F};
  for (float sample : lows) {
    const std::uint32_t actual = to_bits(clamp_with(sample));
    CHECK_CASE("below range: becomes exactly the lower bound",
               actual == to_bits(kClampLowerBound));
    CHECK_CASE("below range: is not the upper bound", actual != to_bits(kClampUpperBound));
  }

  const float highs[] = {10.0001F, 100.0F, 1.0e30F, 3.4028235e38F};
  for (float sample : highs) {
    const std::uint32_t actual = to_bits(clamp_with(sample));
    CHECK_CASE("above range: becomes exactly the upper bound",
               actual == to_bits(kClampUpperBound));
    CHECK_CASE("above range: is not the lower bound", actual != to_bits(kClampLowerBound));
  }
}

// 4. The bounds are the ones read out of the binary.
//
// 0x01478d5c holds the four bytes 00 00 20 c1 and 0x01478d60 holds 00 00 20 41
// (GhidraMCP read_memory @ 0x01478d5c length 12). Little-endian, those are the
// two bit patterns below. Checking the endpoints against the raw words rather
// than against the decimal spelling keeps the assertion tied to the bytes.
void test_bounds_are_the_ones_in_the_binary() {
  CHECK_CASE("bound: lower is the word at 0x01478d5c",
             to_bits(kClampLowerBound) == 0xc1200000U);
  CHECK_CASE("bound: upper is the word at 0x01478d60",
             to_bits(kClampUpperBound) == 0x41200000U);
}

// 5. Values sitting exactly ON a bound come back as that bound.
//
// This is where the two comparisons' strictness is observable. `>=` and `<`
// produce the same answer at the boundary for a finite bound, so the boundary
// alone cannot separate them -- which is why this case is stated as a pass
// condition and not as evidence for either comparison's shape.
void test_values_on_the_bounds_are_stable() {
  CHECK_CASE("boundary: exactly the lower bound is returned as-is",
             to_bits(clamp_with(kClampLowerBound)) == to_bits(kClampLowerBound));
  CHECK_CASE("boundary: exactly the upper bound is returned as-is",
             to_bits(clamp_with(kClampUpperBound)) == to_bits(kClampUpperBound));
  CHECK_CASE("boundary: the negative of the lower bound clamps down",
             to_bits(clamp_with(-kClampLowerBound)) == to_bits(kClampUpperBound));
}

// 6. A NaN input leaves through the LOWER bound.
//
// This is the case that fixes the order of the two clamp steps and pins them to
// MAXSS-then-MINSS rather than to fmin/fmax. Both SSE instructions return their
// second source operand when the ordered comparison is unordered, so a NaN meets
// the lower bound first and becomes -10.0F there; it never reaches the upper
// step. A reconstruction that clamped with fmaxf/fminf, that clamped the upper
// bound first, or that propagated the NaN, all fail this one case.
void test_nan_clamps_to_the_lower_bound() {
  const float quiet_nan = from_bits(0x7fc00000U);
  const float negative_nan = from_bits(0xffc00000U);
  const std::uint32_t expected = to_bits(kClampLowerBound);

  CHECK_CASE("nan: a quiet NaN leaves as the lower bound",
             to_bits(clamp_with(quiet_nan)) == expected);
  CHECK_CASE("nan: a negative NaN leaves as the lower bound",
             to_bits(clamp_with(negative_nan)) == expected);
  CHECK_CASE("nan: the result is not the upper bound",
             to_bits(clamp_with(quiet_nan)) != to_bits(kClampUpperBound));
}

// 7. Signed zero is passed through rather than normalised.
//
// The two comparisons are ordered, so -0.0 compares above -10.0 and is returned
// with its sign bit intact. A reconstruction that used a comparison written to
// treat -0.0 as equal to +0.0, or one that rebuilt the value arithmetically,
// would lose the sign here.
void test_signed_zero_is_passed_through() {
  CHECK_CASE("zero: positive zero keeps its sign bit",
             to_bits(clamp_with(0.0F)) == 0x00000000U);
  CHECK_CASE("zero: negative zero keeps its sign bit",
             to_bits(clamp_with(-0.0F)) == 0x80000000U);
}

// 8. The infinities saturate at the bounds rather than passing or wrapping.
void test_infinities_saturate() {
  const float positive_infinity = from_bits(0x7f800000U);
  const float negative_infinity = from_bits(0xff800000U);
  CHECK_CASE("infinity: positive infinity becomes the upper bound",
             to_bits(clamp_with(positive_infinity)) == to_bits(kClampUpperBound));
  CHECK_CASE("infinity: negative infinity becomes the lower bound",
             to_bits(clamp_with(negative_infinity)) == to_bits(kClampLowerBound));
}

// 9. The result is a pure function of the evaluated value.
//
// The body holds no state, so two calls with the same inputs and the same
// evaluator result agree bit for bit, and the same receiver is not required for
// agreement. A wrapper that cached, accumulated, or consulted its own storage
// between calls would break the second pair.
void test_result_is_a_pure_function_of_the_input() {
  const float sample = -3.75F;
  const std::uint32_t first = to_bits(clamp_with(sample));
  const std::uint32_t second = to_bits(clamp_with(sample));
  CHECK_CASE("purity: two identical calls agree", first == second);

  const std::uint32_t with_receiver = to_bits(clamp_with(
      sample, 0U, 0U, 0U, reinterpret_cast<OpaqueReceiver*>(0x20000U)));
  CHECK_CASE("purity: the receiver does not affect the result",
             with_receiver == first);
}

// 10. The wrapper does not dereference the receiver.
//
// 0x00d00a10 forwards the receiver and reads it nowhere. Pointing it at a
// PROT_NONE mapping makes that observable: a reconstruction that read a field
// would fault, and this one returns. The address is never a valid object, so
// nothing here depends on the receiver's type or size.
void test_receiver_is_never_dereferenced() {
  void* mapping =
      mmap(nullptr, 4096U, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  CHECK_CASE("receiver: the mapping was created", mapping != MAP_FAILED);
  if (mapping == MAP_FAILED) {
    return;
  }
  auto* receiver = reinterpret_cast<OpaqueReceiver*>(mapping);
  const std::uint32_t actual = to_bits(clamp_with(7.5F, 1U, 2U, 3U, receiver));
  CHECK_CASE("receiver: an unmapped receiver still yields the clamped value",
             actual == to_bits(7.5F));
  CHECK_CASE("receiver: the unmapped receiver was still forwarded",
             g_last_call.receiver == receiver);
  CHECK_CASE("receiver: the mapping is released", munmap(mapping, 4096U) == 0);
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range

int main() {
  namespace ns = openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range;
  ns::test_forwards_three_words_in_order();
  ns::test_interior_value_passes_through_unchanged();
  ns::test_out_of_range_values_become_the_bounds();
  ns::test_bounds_are_the_ones_in_the_binary();
  ns::test_values_on_the_bounds_are_stable();
  ns::test_nan_clamps_to_the_lower_bound();
  ns::test_signed_zero_is_passed_through();
  ns::test_infinities_saturate();
  ns::test_result_is_a_pure_function_of_the_input();
  ns::test_receiver_is_never_dereferenced();

  std::printf("checks=%d failures=%d\n", ns::g_checks, ns::g_failures);
  return ns::g_failures == 0 ? 0 : 1;
}