// Focused model test for reconstruction/staging/pkg-00d00a70-scalar-threshold-band.
//
// A static model of the 58-instruction listing at 0x00d00a70..0x00d00b35. No
// original-process observation exists in this repository for this target, so
// nothing here is a differential claim; see `runtime_validation_status` in the
// metadata sidecar.
//
// The test's own definition of evaluate_scalar_00d05a20 is the only definition
// of that symbol in the link, so the value the reconstruction clamps is chosen by
// the test and every case states which value it chose.

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>

#include "scalar_threshold_band_00d00a70.hpp"

namespace openspore::reconstruction::pkg_00d00a70_scalar_threshold_band {
namespace {

int g_checks = 0;
int g_failures = 0;

void record(bool condition, const char* expression, int line) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    if (g_failures <= 20) {
      std::printf("FAIL line %d: %s\n", line, expression);
    }
  }
}

#define CHECK(expression) record(static_cast<bool>(expression), #expression, __LINE__)

float g_next_value = 0.0F;
unsigned g_next_first = 0U;
unsigned g_next_second = 0U;
unsigned g_next_third = 0U;
int g_call_count = 0;

OpaqueReceiver make_receiver(float edge10, float edge14, float edge18, float edge1c) {
  OpaqueReceiver receiver{};
  std::memset(&receiver.opaque_prefix, 0, sizeof(receiver.opaque_prefix));
  receiver.band_edge_10 = edge10;
  receiver.band_edge_14 = edge14;
  receiver.band_edge_18 = edge18;
  receiver.band_edge_1c = edge1c;
  return receiver;
}

std::int32_t run(const OpaqueReceiver& receiver, float value) {
  g_next_value = value;
  return scalar_threshold_band_00d00a70(const_cast<OpaqueReceiver*>(&receiver), 0U, 0U, 0U);
}

float quiet_nan() { return std::numeric_limits<float>::quiet_NaN(); }

// Ascending edges, used wherever the case is about the arithmetic rather than
// about an unordered compare.
constexpr float kE10 = 1.0F;
constexpr float kE14 = 2.0F;
constexpr float kE18 = 4.0F;
constexpr float kE1c = 8.0F;

// 1. The band partition, on the ascending fixture, boundary by boundary. Every
// edge value is probed AT ITSELF, because the four bands have different
// closure: band 0 closed below, band 1 closed above, band 2 open at both ends,
// band 3 closed below, band 4 closed below. A test that only probes interiors
// cannot tell any of those apart.
void test_band_partition_and_edge_inclusivity() {
  const OpaqueReceiver receiver = make_receiver(kE10, kE14, kE18, kE1c);

  // Band 0: at or below the +0x10 edge. Its upper end is INCLUSIVE of f10.
  CHECK(run(receiver, 1.0F) == 0);  // exactly f10 -> 0
  CHECK(run(receiver, 0.999F) == 0);
  CHECK(run(receiver, 0.0F) == 0);
  CHECK(run(receiver, -5.0F) == 0);

  // Band 1: strictly above f10, up to and INCLUDING f14.
  CHECK(run(receiver, 1.001F) == 1);
  CHECK(run(receiver, 1.5F) == 1);
  CHECK(run(receiver, 2.0F) == 1);  // exactly f14 -> 1, the inclusive end

  // Band 2: strictly above f14 and strictly below f18. BOTH ends open, so
  // neither edge belongs here.
  CHECK(run(receiver, 2.001F) == 2);
  CHECK(run(receiver, 3.0F) == 2);
  CHECK(run(receiver, 3.999F) == 2);

  // Band 3: at or above f18, strictly below f1c.
  CHECK(run(receiver, 4.0F) == 3);  // exactly f18 -> 3, the inclusive end
  CHECK(run(receiver, 6.0F) == 3);
  CHECK(run(receiver, 7.999F) == 3);

  // Band 4: at or above f1c, with no upper test at all.
  CHECK(run(receiver, 8.0F) == 4);  // exactly f1c -> 4
  CHECK(run(receiver, 100.0F) == 4);
}

// 2. The band number is not offset. A transcription that returns band+1, or
// that renumbers the chain, has to produce one of these wrong.
void test_band_numbers_are_not_shifted() {
  const OpaqueReceiver receiver = make_receiver(kE10, kE14, kE18, kE1c);
  CHECK(run(receiver, 0.0F) == 0);
  CHECK(run(receiver, 1.5F) == 1);
  CHECK(run(receiver, 3.0F) == 2);
  CHECK(run(receiver, 6.0F) == 3);
  CHECK(run(receiver, 100.0F) == 4);
}

// 3. The clamp happens, and it happens BEFORE the band tests. A value far
// outside the bounds must answer like the bound it folded onto, not like
// itself.
void test_clamp_folds_before_the_band_tests() {
  const OpaqueReceiver receiver = make_receiver(kE10, kE14, kE18, kE1c);

  // -1000.0 folds onto the lower bound, which on this fixture is band 0.
  CHECK(run(receiver, -1000.0F) == run(receiver, -10.0F));
  CHECK(run(receiver, -1000.0F) == 0);
  // +1000.0 folds onto the upper bound, which on this fixture is band 4.
  CHECK(run(receiver, 1000.0F) == run(receiver, 10.0F));
  CHECK(run(receiver, 1000.0F) == 4);
  // Inside the bounds the value reaches the band tests untouched.
  CHECK(run(receiver, 3.0F) == 2);

  // Exactly on a bound is not moved by the clamp: MAXSS and MINSS both write the
  // second source on an equality, and that source IS the bound. So a value
  // sitting on the bound must answer like its immediate neighbour on the far
  // side of it, not like a value beyond it.
  CHECK(run(receiver, kClampLowerBound) == run(receiver, -10.0001F));
  CHECK(run(receiver, kClampUpperBound) == run(receiver, 10.0001F));
}

// 4. The clamp bounds are MEASURED, not assumed. One receiver slot at a time is
// swept across the whole binary32 space as an INTEGER bit pattern, while the
// probe value sits far outside any bound, so the reconstruction's clamp folds
// it onto a single value and the band's answer flips exactly where that folded
// value stops clearing the swept edge. The transition bit pattern is then read
// back out and asserted, which pins 0xc1200000 and 0x41200000 FROM THE
// BEHAVIOUR -- the same two words the header states, reached by a different
// route.
//
// The search is an integer bisection over the pattern, not a bisection over the
// float. A float midpoint rounds, and it rounds straight past the answer: the
// interval collapses onto a float a whole ULP away from the bound and the
// measurement silently reads as "close enough". Bit patterns order exactly and
// the neighbour on either side is the adjacent float.
//
// The sweep ranges are restricted to NEGATIVE patterns for the lower bound and
// POSITIVE patterns for the upper one, because only there does the single
// predicate "folded value clears the swept edge" have one transition. Let a
// pattern of either sign into the other half and the predicate flips a second
// time near zero.
void test_clamp_bounds_are_measurable_and_exact() {
  // Lower bound. Only the +0x10 slot moves. The other three edges are parked
  // above the fold so bands 2, 3 and 4 all decline and band 1 is the only
  // answer that can flip. Band 1 requires (folded > f10), and with a negative
  // sweep a LARGER pattern is a MORE NEGATIVE float, so the predicate is true
  // on the high side of the transition. -1.0e30f folds onto the lower bound.
  {
    unsigned low = 0x81200000U;   // ~-1e-38 : below the fold, predicate false
    unsigned high = 0xd0000000U;  // ~-1e9   : above the fold, predicate true
    CHECK(run(make_receiver(-1.0e-38F, 1000.0F, 2000.0F, 3000.0F), -1.0e30F) == 0);
    CHECK(run(make_receiver(-1.0e9F, 1000.0F, 2000.0F, 3000.0F), -1.0e30F) == 1);
    while (high - low > 1U) {
      unsigned mid = low + (high - low) / 2U;
      float probe = 0.0F;
      std::memcpy(&probe, &mid, sizeof(probe));
      const OpaqueReceiver fixture = make_receiver(probe, 1000.0F, 2000.0F, 3000.0F);
      if (run(fixture, -1.0e30F) == 1) {
        high = mid;
      } else {
        low = mid;
      }
    }
    // `low` is the last pattern that did NOT clear, i.e. the fold's own value.
    CHECK(low == 0xc1200000U);
    // And the neighbour one pattern above it DOES clear, so the bracket is a
    // single float wide and not a loose interval.
    {
      unsigned above = low + 1U;
      float probe = 0.0F;
      std::memcpy(&probe, &above, sizeof(probe));
      CHECK(run(make_receiver(probe, 1000.0F, 2000.0F, 3000.0F), -1.0e30F) == 1);
    }
  }

  // Upper bound, mirror image. Only the +0x1c slot moves and the probe is
  // +1.0e30f, which folds onto the upper bound. Band 4 requires (folded >=
  // f1c) and, over positive patterns, a LARGER pattern is a LARGER float, so
  // the predicate is true on the LOW side and the answer is the largest true
  // pattern.
  //
  // The other three edges are parked so that bands 2 and 3 decline for a reason
  // that is NOT the swept comparison: f14 and f18 sit above the fold, so band 2
  // declines on its first half (folded > f14 is false) and band 3 on its first
  // half (folded >= f18 is false). Otherwise band 2 or band 3 would answer
  // first and the sweep would measure the wrong edge's position.
  {
    unsigned low = 0x01200000U;   // ~1e-38  : predicate true
    unsigned high = 0x4e6e6b28U; // +1e9    : predicate false
    CHECK(run(make_receiver(100.0F, 200.0F, 300.0F, 1.0e-38F), 1.0e30F) == 4);
    CHECK(run(make_receiver(100.0F, 200.0F, 300.0F, 1.0e9F), 1.0e30F) == 0);
    while (high - low > 1U) {
      unsigned mid = low + (high - low) / 2U;
      float probe = 0.0F;
      std::memcpy(&probe, &mid, sizeof(probe));
      const OpaqueReceiver fixture = make_receiver(100.0F, 200.0F, 300.0F, probe);
      if (run(fixture, 1.0e30F) == 4) {
        low = mid;
      } else {
        high = mid;
      }
    }
    CHECK(low == 0x41200000U);
    {
      unsigned above = low + 1U;
      float probe = 0.0F;
      std::memcpy(&probe, &above, sizeof(probe));
      CHECK(run(make_receiver(100.0F, 200.0F, 300.0F, probe), 1.0e30F) == 0);
    }
  }

  // The fold happened, rather than the raw probe reaching the bands. With the
  // probe edge at exactly -1000.0 the folded -10.0 is ABOVE it and answers 1,
  // while the raw -1000.0 would be at the edge and answer 0 -- and the raw value
  // and the folded value sit on opposite sides of the same comparison, so no
  // band answer can be right unless the clamp ran first.
  {
    const OpaqueReceiver r = make_receiver(-1000.0F, 1000.0F, 2000.0F, 3000.0F);
    CHECK(run(r, -1000.0F) == 1);
    CHECK(run(r, -1001.0F) == 1);  // also folds
    CHECK(run(r, -999.0F) == 1);   // inside the bounds already
    // Just outside the lower bound and just inside it agree, because both fold
    // onto the bound:
    CHECK(run(r, -10.5F) == 1);
    CHECK(run(r, -9.5F) == 1);
    // And a probe between the raw value and the bound answers 0 only when it is
    // above the edge and below the bound, which is band 0's own region.
    // The same fold seen from the other side: with f10 at -9.0 the folded -10.0
    // is BELOW it and answers 0, while any value above -9.0 answers 1. A
    // reconstruction that skipped the clamp would hand -1000.0 straight to the
    // bands and get 0 here, and one that clamped to the wrong bound would get 0
    // at -8.5 instead of 1.
    const OpaqueReceiver q = make_receiver(-9.0F, 1000.0F, 2000.0F, 3000.0F);
    CHECK(run(q, -1000.0F) == 0);
    CHECK(run(q, -10.0F) == 0);
    CHECK(run(q, -8.5F) == 1);
  }
}

// 5. The clamp's OPERATION ORDER is observable, because a NaN out of the callee
// leaves through whichever bound runs first. MAXSS runs against the LOWER bound
// and MINSS against the UPPER bound, so the NaN becomes -10.0f. Swap the two
// operations and the same NaN becomes +10.0f and lands in band 4 on a fixture
// chosen so -10.0f is band 1.
void test_clamp_order_sends_nan_out_the_lower_bound() {
  const OpaqueReceiver receiver = make_receiver(-20.0F, -5.0F, 0.0F, 5.0F);

  // -10.0f is band 1 here; +10.0f would be band 4.
  CHECK(run(receiver, -10.0F) == 1);
  CHECK(run(receiver, 10.0F) == 4);

  // The NaN answer is the -10.0f answer, byte for byte.
  CHECK(run(receiver, quiet_nan()) == 1);
  CHECK(run(receiver, quiet_nan()) == run(receiver, kClampLowerBound));

  // And it is not simply "the NaN compares false everywhere and lands in band
  // 0": with the fixture above a NaN answers 1, not 0.
  CHECK(run(receiver, quiet_nan()) != 0);
}

// 6. Each of the four displacements is load-bearing. Every edge is probed at
// itself, so an offset that moved onto a neighbouring slot -- or a permutation
// of the four -- changes at least one of these.
void test_each_edge_displacement_is_load_bearing() {
  // +0x10 owns the lower boundary of band 1 and the upper boundary of band 0.
  {
    const OpaqueReceiver r = make_receiver(kE10, kE14, kE18, kE1c);
    CHECK(run(r, kE10) == 0);
    CHECK(run(r, kE10 + 0.001F) == 1);
  }
  // +0x14 owns band 2's lower edge and band 1's upper edge.
  {
    const OpaqueReceiver r = make_receiver(kE10, kE14, kE18, kE1c);
    CHECK(run(r, kE14) == 1);
    CHECK(run(r, kE14 + 0.001F) == 2);
  }
  // +0x18 owns band 2's upper edge and band 3's lower edge.
  {
    const OpaqueReceiver r = make_receiver(kE10, kE14, kE18, kE1c);
    CHECK(run(r, kE18) == 3);
    CHECK(run(r, kE18 - 0.001F) == 2);
  }
  // +0x1c owns band 3's upper edge and band 4's lower edge.
  {
    const OpaqueReceiver r = make_receiver(kE10, kE14, kE18, kE1c);
    CHECK(run(r, kE1c) == 4);
    CHECK(run(r, kE1c - 0.001F) == 3);
  }
  // A receiver whose edges are deliberately out of order, with f14 above f18:
  // band 2 is unreachable and the answers are 0, 1, 3, 4, 4. A reconstruction
  // that sorted, deduplicated or assumed ascending would answer differently.
  {
    const OpaqueReceiver r = make_receiver(1.0F, 8.0F, 2.0F, 6.0F);
    CHECK(run(r, 0.0F) == 0);
    CHECK(run(r, 1.5F) == 1);
    CHECK(run(r, 2.5F) == 3);
    CHECK(run(r, 7.0F) == 4);
    CHECK(run(r, 8.5F) == 4);
  }
  // Four distinct values at 1/2/4/8 with a naive "search the array" rewrite
  // would give the same answers; this fixture pins that the four slots are read
  // as four separate words rather than as a range over a counted array.
  {
    const OpaqueReceiver r = make_receiver(7.0F, 1.0F, 9.0F, 3.0F);
    CHECK(run(r, 0.0F) == 0);
    CHECK(run(r, 1.5F) == 2);
    CHECK(run(r, 2.0F) == 2);
    CHECK(run(r, 5.0F) == 2);
    CHECK(run(r, 9.5F) == 4);
  }
}

// 7. The band chain is a fall-through list in a specific order -- 2, then 3, then
// 4, then 1, then 0 -- and that order is observable on unsorted fixtures. A
// reconstruction that tested band 1 first, or that searched for the band,
// answers differently here.
void test_band_tests_run_in_listing_order() {
  // f14=1, f18=9, f1c=3, v=2.0: band 2's halves hold (1 < 2 < 9) AND band 4's
  // half holds (2 >= 3 is false, so actually band 4 declines). Band 2 answers 2.
  {
    const OpaqueReceiver r = make_receiver(-100.0F, 1.0F, 9.0F, 3.0F);
    CHECK(run(r, 2.0F) == 2);
  }
  // f14=1, f18=3, f1c=9, v=5.0: band 2 declines on its upper half, band 3's
  // halves hold -> 3, not 4.
  {
    const OpaqueReceiver r = make_receiver(-100.0F, 1.0F, 3.0F, 9.0F);
    CHECK(run(r, 5.0F) == 3);
  }
  // f14=9, f18=1, f1c=3, v=5.0: band 2 declines (v <= f14), band 3 declines
  // (v < f1c fails), band 4 answers 4 -- and specifically NOT band 1, which
  // would need v <= f14.
  {
    const OpaqueReceiver r = make_receiver(-100.0F, 9.0F, 1.0F, 3.0F);
    CHECK(run(r, 5.0F) == 4);
  }
  // f14=9, f18=20, f1c=30, v=1.5: bands 2, 3 and 4 all decline (1.5 is below
  // every one of those edges) and band 1's halves hold (1.5 <= 9, 1.5 > -100) -> 1.
  // Band 1 is reachable only because the listing tests it LAST, so a rewrite
  // that reached it earlier would not change this answer -- which is exactly
  // why the pair of cases above it matter.
  {
    const OpaqueReceiver r = make_receiver(-100.0F, 9.0F, 20.0F, 30.0F);
    CHECK(run(r, 1.5F) == 1);
    CHECK(run(r, 9.0F) == 1);
    CHECK(run(r, 9.5F) == 2);
  }
}

// 8. An unordered receiver float. COMISS sets CF=ZF=1 on an unordered pair, so
// both `JBE` and `JC` are TAKEN. Every guard in this body is a NEGATED branch
// (`JBE` -> `if (taken) leave`, `JC` -> `if (taken) leave`), which is why
// `!comiss_jbe(a,b)` is exactly `a > b` and `!comiss_jc(a,b)` is exactly
// `a >= b` INCLUDING the unordered case -- a negated branch through COMISS and
// the matching C++ operator agree, and this test pins that agreement so the
// helpers cannot drift into something else. The band answers below are traced
// from the listing with that fact applied.
void test_unordered_receiver_float_behaves_as_the_negated_comiss_says() {
  const float nan = quiet_nan();

  // The two identities, checked directly on the helpers.
  CHECK(comiss_jbe(nan, 1.0F));
  CHECK(comiss_jc(1.0F, nan));
  CHECK(!comiss_jbe(2.0F, 1.0F));
  CHECK(!comiss_jbe(nan, nan) == false);
  CHECK((!comiss_jbe(1.0F, nan)) == (1.0F > nan));
  CHECK((!comiss_jc(nan, 1.0F)) == (nan >= 1.0F));
  CHECK((!comiss_jc(1.0F, 1.0F)) == (1.0F >= 1.0F));

  // +0x18 unordered, v=2.0, others 1/2/8: band 2 declines on the unordered
  // compare, band 3 declines, band 4 declines, band 1 answers 1.
  {
    const OpaqueReceiver r = make_receiver(1.0F, 2.0F, nan, 8.0F);
    CHECK(run(r, 2.0F) == 1);
  }
  // +0x14 unordered, v=6.0, f18=4, f1c=8: band 2 declines, band 3 answers 3.
  {
    const OpaqueReceiver r = make_receiver(1.0F, nan, 4.0F, 8.0F);
    CHECK(run(r, 6.0F) == 3);
  }
  // +0x1c unordered, v=6.0, f10=1, f14=2, f18=4: band 2 needs v < f18 (false),
  // band 3 needs v < f1c (unordered -> declines), band 4 needs v >= f1c
  // (unordered -> declines), band 1 needs v <= f14 (false). All four decline
  // and the spelled `XOR EAX,EAX` answers 0.
  {
    const OpaqueReceiver r = make_receiver(1.0F, 2.0F, 4.0F, nan);
    CHECK(run(r, 6.0F) == 0);
  }
  // +0x10 unordered, v=6.0, f14=2, f18=4, f1c=8: bands 2..4 answer 3 and band
  // 1 is never reached, so the NaN at +0x10 changes nothing here.
  {
    const OpaqueReceiver r = make_receiver(nan, 2.0F, 4.0F, 8.0F);
    CHECK(run(r, 6.0F) == 3);
  }
  // Two unordered edges (f14 and f1c), v=5.0, f18=4, f10=1. Band 2's first
  // compare is against the unordered f14 and declines; band 3's second is
  // against the unordered f1c and declines; band 4's single compare is against
  // it and declines; band 1's first compare is against it and declines. All
  // four guards fall through to the spelled `XOR EAX,EAX` -> 0.
  {
    const OpaqueReceiver r = make_receiver(1.0F, nan, 4.0F, nan);
    CHECK(run(r, 5.0F) == 0);
  }
  // Three unordered edges, nothing to compare against: every guard declines
  // and the spelled fall-through answers 0.
  {
    const OpaqueReceiver r = make_receiver(nan, nan, 4.0F, nan);
    CHECK(run(r, 5.0F) == 0);
  }
}

// 9. The result is an integer in EAX, in {0,1,2,3,4}, and nothing else. No
// input in this sweep escapes the set -- including both infinities, NaN and a
// denormal, which the clamp and the negated compares both have to absorb.
void test_result_is_always_a_small_integer() {
  const OpaqueReceiver r = make_receiver(kE10, kE14, kE18, kE1c);
  const float probes[] = {
      -1e30F,  -1000.0F, -10.0F,     -1.0F,      0.0F,      1.0F,
      2.0F,    4.0F,     8.0F,       1000.0F,    1e30F,     3.4028235e38F,
      -3.4028235e38F,       std::numeric_limits<float>::infinity(),
      -std::numeric_limits<float>::infinity(),  quiet_nan(),
      std::numeric_limits<float>::denorm_min(),
  };
  for (float probe : probes) {
    const std::int32_t band = run(r, probe);
    CHECK(band >= 0);
    CHECK(band <= 4);
  }
  CHECK(run(r, -0.0F) == 0);
  CHECK(run(r, std::numeric_limits<float>::denorm_min()) == 0);
  // Both infinities reach the clamp: -inf folds onto the lower bound, +inf onto
  // the upper one, so they must answer like those bounds do.
  CHECK(run(r, -std::numeric_limits<float>::infinity()) == run(r, -10.0F));
  CHECK(run(r, std::numeric_limits<float>::infinity()) == run(r, 10.0F));
}

// 10. The three stack words are forwarded, unmodified and in the order the
// listing reads them (entry+0x4 first, then +0x8, then +0xc), and the receiver
// reaches the callee. This is the one case that pins the forwarding identity
// rather than the arithmetic.
void test_three_words_are_forwarded_verbatim_in_order() {
  OpaqueReceiver receiver = make_receiver(kE10, kE14, kE18, kE1c);

  g_next_value = 3.0F;
  g_call_count = 0;
  const std::int32_t band =
      scalar_threshold_band_00d00a70(&receiver, 0x11111111U, 0x22222222U, 0x33333333U);

  CHECK(g_call_count == 1);
  CHECK(g_next_first == 0x11111111U);
  CHECK(g_next_second == 0x22222222U);
  CHECK(g_next_third == 0x33333333U);
  CHECK(band == 2);

  // Distinct words per slot, so a swap of two of them is caught.
  g_call_count = 0;
  static_cast<void>(scalar_threshold_band_00d00a70(&receiver, 1U, 2U, 3U));
  CHECK(g_call_count == 1);
  CHECK(g_next_first == 1U);
  CHECK(g_next_second == 2U);
  CHECK(g_next_third == 3U);

  // Zero words are forwarded as zero rather than defaulted or dropped.
  g_call_count = 0;
  static_cast<void>(scalar_threshold_band_00d00a70(&receiver, 0U, 0U, 0U));
  CHECK(g_call_count == 1);
  CHECK(g_next_first == 0U && g_next_second == 0U && g_next_third == 0U);

  // High-bit-set words (which would be negative if they were read as signed)
  // are forwarded bit-for-bit, so no signedness is smuggled in.
  g_call_count = 0;
  static_cast<void>(
      scalar_threshold_band_00d00a70(&receiver, 0x80000000U, 0xffffffffU, 0x7fffffffU));
  CHECK(g_next_first == 0x80000000U);
  CHECK(g_next_second == 0xffffffffU);
  CHECK(g_next_third == 0x7fffffffU);
}

// 11. The receiver is only ever READ. The body performs no store through it, so
// the fixture is compared byte for byte around a sweep of calls and a
// reconstruction that wrote through the receiver, or through one of the four
// floats, is caught rather than silently tolerated.
void test_receiver_is_never_written() {
  OpaqueReceiver receiver = make_receiver(kE10, kE14, kE18, kE1c);
  std::uint8_t before[sizeof(OpaqueReceiver)];
  std::memcpy(before, &receiver, sizeof(before));

  const float probes[] = {-1000.0F, -10.0F, 0.0F,   1.0F,     2.0F,
                          4.0F,     8.0F,    1000.0F, quiet_nan()};
  for (float probe : probes) {
    g_next_value = probe;
    static_cast<void>(scalar_threshold_band_00d00a70(&receiver, 7U, 8U, 9U));
  }

  CHECK(std::memcmp(before, &receiver, sizeof(before)) == 0);
}

// 12. The edge accessor reads exactly the displacement it is handed, and a NaN
// payload survives into the band test instead of being laundered into a zero.
void test_edge_accessor_reads_the_stated_displacement() {
  OpaqueReceiver receiver = make_receiver(0.0F, 0.0F, 0.0F, 8.0F);

  const std::uint32_t nan_bits = 0x7fc00000U;  // quiet NaN
  std::memcpy(&receiver.band_edge_18, &nan_bits, sizeof(nan_bits));

  const float read10 = band_edge(&receiver, kEdgeDisplacement10);
  const float read14 = band_edge(&receiver, kEdgeDisplacement14);
  const float read18 = band_edge(&receiver, kEdgeDisplacement18);
  const float read1c = band_edge(&receiver, kEdgeDisplacement1c);
  CHECK(float_bits(read10) == float_bits(receiver.band_edge_10));
  CHECK(float_bits(read14) == float_bits(receiver.band_edge_14));
  CHECK(float_bits(read18) == float_bits(receiver.band_edge_18));
  CHECK(float_bits(read1c) == float_bits(receiver.band_edge_1c));

  // The NaN is still a NaN by the time the band test sees it.
  CHECK(read18 != read18);
  // f10=0, f14=0, f18=NaN, f1c=8; v=0.5. Band 2 and band 3 decline on the NaN,
  // band 4 needs 0.5 >= 8 (false), band 1 needs 0.5 <= 0 (false) -> 0.
  CHECK(run(receiver, 0.5F) == 0);
}

// 13. The stated ABI shape: the entry is a thiscall taking the receiver and
// three 4-byte words and returning a 32-bit integer. Called through the
// declared function-pointer type so a changed signature cannot compile.
void test_entry_matches_the_declared_abi() {
  AbiScalarThresholdBand00d00a70 entry = &scalar_threshold_band_00d00a70;
  OpaqueReceiver receiver = make_receiver(kE10, kE14, kE18, kE1c);
  g_next_value = 3.0F;
  CHECK(entry(&receiver, 0U, 0U, 0U) == 2);
  CHECK(sizeof(std::int32_t) == 4);
  CHECK(static_cast<int>(sizeof(ForwardedWord)) == 4);
  CHECK(static_cast<int>(sizeof(OpaqueReceiver)) == 0x20);
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_00d00a70_scalar_threshold_band

// The callee the reconstruction calls at 0x00d00a87, defined here at namespace
// scope so the `extern "C"` linkage the header declares is the linkage it gets.
// Not reconstructed: this is the harness's control over the value that reaches
// the clamp at 0x00d00ab2.
extern "C" float __attribute__((thiscall))
openspore::reconstruction::pkg_00d00a70_scalar_threshold_band::evaluate_scalar_00d05a20(
    openspore::reconstruction::pkg_00d00a70_scalar_threshold_band::OpaqueReceiver*,
    openspore::reconstruction::pkg_00d00a70_scalar_threshold_band::ForwardedWord first,
    openspore::reconstruction::pkg_00d00a70_scalar_threshold_band::ForwardedWord second,
    openspore::reconstruction::pkg_00d00a70_scalar_threshold_band::ForwardedWord third) {
  using namespace openspore::reconstruction::pkg_00d00a70_scalar_threshold_band;
  ++g_call_count;
  g_next_first = first;
  g_next_second = second;
  g_next_third = third;
  return g_next_value;
}

int main() {
  using namespace openspore::reconstruction::pkg_00d00a70_scalar_threshold_band;

  test_band_partition_and_edge_inclusivity();
  test_band_numbers_are_not_shifted();
  test_clamp_folds_before_the_band_tests();
  test_clamp_bounds_are_measurable_and_exact();
  test_clamp_order_sends_nan_out_the_lower_bound();
  test_each_edge_displacement_is_load_bearing();
  test_band_tests_run_in_listing_order();
  test_unordered_receiver_float_behaves_as_the_negated_comiss_says();
  test_result_is_always_a_small_integer();
  test_three_words_are_forwarded_verbatim_in_order();
  test_receiver_is_never_written();
  test_edge_accessor_reads_the_stated_displacement();
  test_entry_matches_the_declared_abi();

  std::printf("checks=%d failures=%d\n", g_checks, g_failures);
  // `std::exit`, not `std::_Exit`: _Exit skips the stdio flush, and on a
  // failing run the failure list is the only output there is.
  std::fflush(stdout);
  if (g_failures != 0) {
    std::exit(1);
  }
  std::printf("OK\n");
  return 0;
}
