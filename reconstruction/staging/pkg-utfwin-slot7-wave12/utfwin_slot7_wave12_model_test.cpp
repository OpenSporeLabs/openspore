#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "utfwin_slot7_wave12.hpp"

namespace openspore::reconstruction::pkg_utfwin_slot7_wave12 {
namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

OpaqueSlot7ReceiverWire seeded_receiver() {
  OpaqueSlot7ReceiverWire receiver{};
  receiver.dispatch_00 = 0x01491730u;
  receiver.unproven_04 = 0x11111111u;
  receiver.word_08 = 0x22222222u;
  receiver.word_0c = 0x33333333u;
  receiver.word_10 = 0x44444444u;
  receiver.word_14 = 0x55555555u;
  receiver.word_18 = 0x66666666u;
  receiver.word_1c = 0x77777777u;
  return receiver;
}

// Stand-in for the code address that 0x00fc7ec0 finds at receiver +0x08 and
// calls. It is never invoked here; the test only needs a stable code address
// to prove the model installs the caller's word verbatim.
int callback_stub(int, int, OpaqueWord) {
  return 0;
}

// Both stack words are written, to the two proven offsets, and nothing else in
// the receiver changes.
void test_stores_both_words_to_proven_offsets() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();
  const OpaqueSlot7ReceiverWire before = receiver;

  const OpaqueWord result = re_00fc7e10_UTFWin_ImageDrawable_GetTiling(
      &receiver, 0xdeadbeefu, 0x0badf00du);

  check(receiver.word_08 == 0xdeadbeefu);
  check(receiver.word_10 == 0x0badf00du);
  check(receiver.dispatch_00 == before.dispatch_00);
  check(receiver.unproven_04 == before.unproven_04);
  check(receiver.word_0c == before.word_0c);
  check(receiver.word_14 == before.word_14);
  check(receiver.word_18 == before.word_18);
  check(receiver.word_1c == before.word_1c);
  check(result == 0xdeadbeefu);
}

// The two stores must not alias: swapping the arguments swaps the two words.
void test_argument_order_is_not_swapped() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0xaaaaaaaau,
                                             0xbbbbbbbbu);

  check(receiver.word_08 == 0xaaaaaaaau);
  check(receiver.word_10 == 0xbbbbbbbbu);
  check(receiver.word_08 != receiver.word_10);
}

// Repeated invocation is idempotent for equal arguments and overwrites stale
// state for different ones; neither call may disturb the sibling words.
void test_repeated_invocation_overwrites_stale_words() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0x00000001u,
                                             0x00000002u);
  check(receiver.word_08 == 0x00000001u);
  check(receiver.word_10 == 0x00000002u);

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0x00000001u,
                                             0x00000002u);
  check(receiver.word_08 == 0x00000001u);
  check(receiver.word_10 == 0x00000002u);
  check(receiver.word_0c == 0x33333333u);
  check(receiver.word_14 == 0x55555555u);

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0xcafebabeu,
                                             0xfeedfaceu);
  check(receiver.word_08 == 0xcafebabeu);
  check(receiver.word_10 == 0xfeedfaceu);
}

// Zero is an ordinary payload value, not a skip.
void test_zero_words_are_written() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();

  const OpaqueWord result =
      re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0u, 0u);

  check(receiver.word_08 == 0u);
  check(receiver.word_10 == 0u);
  check(result == 0u);
}

// The first word must survive as a usable code address, because 0x00fc7ec0
// loads receiver +0x08 into ECX and calls it, and 0x0093b6c0 returns it. The
// second word must survive as the context that 0x00fc7ec0 pushes alongside
// that call. Both are checked as exact 32-bit round trips, never invoked.
void test_first_word_round_trips_as_a_callable_address() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();
  const OpaqueWord callable_address =
      reinterpret_cast<OpaqueWord>(&callback_stub);
  const OpaqueWord context = 0x0badc0deu;

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, callable_address,
                                             context);

  check(receiver.word_08 == callable_address);
  check(receiver.word_08 == reinterpret_cast<OpaqueWord>(&callback_stub));
  check(receiver.word_10 == context);

  OpaqueSlot7ReceiverWire reloaded{};
  std::memcpy(&reloaded, &receiver, sizeof(reloaded));
  check(reloaded.word_08 == callable_address);
  check(reloaded.word_10 == context);
}

// The observed instruction stream is byte for byte independent of the values
// passed, so the only memory the body may touch is the two proven offsets.
void test_only_the_two_published_offsets_change() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();
  OpaqueSlot7ReceiverWire previous = receiver;

  for (OpaqueWord seed = 0; seed < 64u; ++seed) {
    const OpaqueWord first = 0x9e3779b9u * (seed + 1u);
    const OpaqueWord second = 0x85ebca6bu * (seed + 1u);
    re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, first, second);

    check(receiver.word_08 == first);
    check(receiver.word_10 == second);

    OpaqueSlot7ReceiverWire diff = receiver;
    diff.word_08 = previous.word_08;
    diff.word_10 = previous.word_10;
    check(std::memcmp(&diff, &previous, sizeof(diff)) == 0);

    previous = receiver;
  }
}

}

int run_tests() {
  test_stores_both_words_to_proven_offsets();
  test_argument_order_is_not_swapped();
  test_repeated_invocation_overwrites_stale_words();
  test_zero_words_are_written();
  test_first_word_round_trips_as_a_callable_address();
  test_only_the_two_published_offsets_change();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_utfwin_slot7_wave12::run_tests();
}
