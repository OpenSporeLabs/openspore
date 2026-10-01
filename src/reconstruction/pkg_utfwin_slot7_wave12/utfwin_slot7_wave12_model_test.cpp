// Model test for 0x00fc7e10, UTFWin::ImageDrawable::GetTiling.
//
// What the machine listing fixes, and what each test below therefore attacks:
//
//   00fc7e10  MOV EAX,dword ptr [ESP + 0x4]    first incoming stack word
//   00fc7e14  MOV EDX,dword ptr [ESP + 0x8]    second incoming stack word
//   00fc7e18  MOV dword ptr [ECX + 0x8], EAX   store #1, at displacement 0x08
//   00fc7e1b  MOV dword ptr [ECX + 0x10], EDX  store #2, at displacement 0x10
//   00fc7e1e  RET 0x8                          the callee pops both words
//
// so: both stores are 4-byte and verbatim, at displacements 0x08 and 0x10 of the
// receiver; the receiver is never read before the two stores; the callee owns
// the cleanup of both stack words; and EAX is left holding the first stack word,
// which is what the entry point returns.
//
// Not asserted, on purpose:
//
//   * That the original source returned the word deliberately. The body has no
//     instruction producing a result; EAX merely still holds the first stack
//     word at the RET because the register was loaded for the store at +0x08
//     and never reused. The reconstruction returns it to reproduce the observed
//     exit state, and the metadata record carries that as an open question. The
//     test pins the value the reconstruction claims and nothing about intent.
//   * Any C type for either stored word beyond its 32-bit width. 0x00fc7ec0
//     loads the word at +0x08 into ECX and calls it, and pushes the word at
//     +0x10 as an argument to that call; "used as a code address" and "used as
//     a context word" are observed uses, not proven declared types.
//
// Build (x86-32):
/*
 * clang++ -m32 -std=c++17 -Wall -Wextra -Werror -O2 \
 * -I. utfwin_slot7_wave12.cpp utfwin_slot7_wave12_model_test.cpp
 * ./utfwin_slot7_wave12_model_test && echo PASS
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "utfwin_slot7_wave12.hpp"

namespace openspore::reconstruction::pkg_utfwin_slot7_wave12 {
namespace {

int g_failures = 0;

void check(bool condition, const char *what) {
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s\n", what);
  }
}

// The declared contract, pinned. The body ends in RET 0x8, so the callee owns
// the cleanup of exactly two 4-byte stack words, and the receiver arrives in a
// register rather than on the stack; __thiscall with two stack words is the
// reading this package takes. Every call in this test goes through a pointer of
// exactly this type, so the body is only ever exercised through the convention
// it claims, and any change to the parameter list or to the convention stops
// the file from compiling.
//
// A runtime stack-drift measurement was tried and deliberately dropped: on
// i386-ELF the compiler reserves the outgoing argument area itself, so the
// caller's ESP is unchanged whether the callee pops the words or not, and no
// probe of the caller's stack can separate the two conventions.
using EntryPoint = OpaqueWord(PKG_UTFWIN_SLOT7_THISCALL *)(
    OpaqueSlot7ReceiverWire *, OpaqueWord, OpaqueWord);
static_assert(std::is_same<EntryPoint, decltype(&re_00fc7e10_UTFWin_ImageDrawable_GetTiling)>::value,
              "the entry point takes the receiver in ECX and exactly two "
              "4-byte callee-popped stack words");

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

// Records what a call through the word stored at +0x08 actually reached, so the
// round trip can be checked by invoking it rather than by comparing numbers.
int g_callback_calls = 0;
int g_callback_first = -1;
OpaqueWord g_callback_context = 0u;

int callback_stub(int first, int second, OpaqueWord context) {
  ++g_callback_calls;
  g_callback_first = first + second;
  g_callback_context = context;
  return 0;
}

// Both stack words are written, to the two proven offsets, and nothing else in
// the receiver changes.
void test_stores_both_words_to_proven_offsets() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();
  const OpaqueSlot7ReceiverWire before = receiver;

  const OpaqueWord result = re_00fc7e10_UTFWin_ImageDrawable_GetTiling(
      &receiver, 0xdeadbeefu, 0x0badf00du);

  check(receiver.word_08 == 0xdeadbeefu, "+0x08 must hold the first word");
  check(receiver.word_10 == 0x0badf00du, "+0x10 must hold the second word");
  check(receiver.dispatch_00 == before.dispatch_00, "+0x00 must not change");
  check(receiver.unproven_04 == before.unproven_04, "+0x04 must not change");
  check(receiver.word_0c == before.word_0c, "+0x0c must not change");
  check(receiver.word_14 == before.word_14, "+0x14 must not change");
  check(receiver.word_18 == before.word_18, "+0x18 must not change");
  check(receiver.word_1c == before.word_1c, "+0x1c must not change");
  check(result == 0xdeadbeefu, "EAX is left holding the first stack word");
}

// The two stores must not alias: swapping the arguments swaps the two words.
void test_argument_order_is_not_swapped() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0xaaaaaaaau,
                                             0xbbbbbbbbu);

  check(receiver.word_08 == 0xaaaaaaaau, "+0x08 is the FIRST word");
  check(receiver.word_10 == 0xbbbbbbbbu, "+0x10 is the SECOND word");
  check(receiver.word_08 != receiver.word_10, "the two stores must not alias");
  // The word between the two published displacements, +0x0c, is written by a
  // sibling slot (0x00fc7e30) and by nothing in this body. A reconstruction
  // that treated 0x10 as an offset from 0x0c, or that stored a 0x10-byte run
  // from 0x08, would land here.
  check(receiver.word_0c == 0x33333333u,
        "the word between +0x08 and +0x10 must be untouched");
}

// Displacement, not index, and not a run. 0x08 and 0x10 are byte
// displacements. Read as word indices they would be byte offsets 0x20 and
// 0x40, and read as a 0x10-byte run from 0x08 they would cover 0x08..0x17. An
// arena with a distinct byte at each of those places separates all three
// readings from the one the listing shows.
void test_displacements_are_byte_offsets_not_word_indices_or_runs() {
  std::uint8_t arena[0x50];
  for (std::size_t index = 0; index < sizeof(arena); ++index) {
    arena[index] = static_cast<std::uint8_t>(0x20u + index);
  }
  auto *const receiver = reinterpret_cast<OpaqueSlot7ReceiverWire *>(arena);
  std::uint8_t before[sizeof(arena)] = {};
  std::memcpy(before, arena, sizeof(arena));

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(receiver, 0xdeadbeefu, 0x0badf00du);

  check(receiver->word_08 == 0xdeadbeefu, "+0x08 is the first word");
  check(receiver->word_10 == 0x0badf00du, "+0x10 is the second word");

  // Exactly the two 4-byte windows 0x08..0x0b and 0x10..0x13 may differ. 0x14
  // (the run reading), 0x20 and 0x40 (the word-index reading) and 0x0c are
  // among the bytes that must not.
  for (std::size_t index = 0; index < sizeof(arena); ++index) {
    const bool written = (index >= 0x08 && index < 0x0c) ||
                         (index >= 0x10 && index < 0x14);
    if (written) {
      continue;
    }
    if (arena[index] != before[index]) {
      std::fprintf(stderr, "FAIL byte 0x%02zx moved: 0x%02x -> 0x%02x\n", index,
                   before[index], arena[index]);
      ++g_failures;
      break;
    }
  }
}

// Pointer vs pointee, and pointer vs pointer-to-pointer. The word published at
// +0x08 is used by 0x00fc7ec0 as a code address (MOV ECX,[ESI+0x8] ... CALL ECX)
// and returned unchanged by 0x0093b6c0. So the reconstruction must publish the
// ADDRESS itself: not the callee at that address, not a pointer to the slot that
// holds the address, and not the argument it was handed. Invoking the published
// word is what separates all four.
void test_first_word_is_published_as_a_callable_address() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();
  const OpaqueWord callable_address =
      reinterpret_cast<OpaqueWord>(&callback_stub);
  const OpaqueWord context = 0x0badc0deu;
  g_callback_calls = 0;
  g_callback_first = -1;
  g_callback_context = 0u;

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, callable_address,
                                             context);

  check(receiver.word_08 == callable_address,
        "+0x08 must hold the address, verbatim");
  check(receiver.word_10 == context, "+0x10 must hold the context word");
  check(receiver.word_08 != context,
        "the two words must not be exchanged");
  check(receiver.word_10 != callable_address,
        "+0x10 must not hold the address");

  // Reading the published word back out of the receiver's storage and calling
  // it is the pointer-vs-pointee test: a reconstruction that had stored
  // &slot (the address of the word) instead of the word's value would hand the
  // stub's caller a data address and never reach the stub.
  OpaqueSlot7ReceiverWire reloaded{};
  std::memcpy(&reloaded, &receiver, sizeof(reloaded));
  check(reloaded.word_08 == callable_address,
        "the published address survives a reload of the receiver");
  const auto invoked = reinterpret_cast<int (*)(int, int, OpaqueWord)>(
      reloaded.word_08);
  invoked(20, 22, reloaded.word_10);
  check(g_callback_calls == 1, "the published word must be a callable address");
  check(g_callback_first == 42, "the call must reach the published callee");
  check(g_callback_context == context,
        "the word at +0x10 must be usable as that call's context argument");
}

// The receiver is never read before the two stores, so a stale value at either
// displacement must not survive, and an argument equal to the stale value must
// be indistinguishable from a fresh one.
void test_stores_overwrite_stale_state_without_reading_it() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();
  check(receiver.word_08 == 0x22222222u, "precondition: +0x08 is stale");
  check(receiver.word_10 == 0x44444444u, "precondition: +0x10 is stale");

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0x22222222u,
                                             0x44444444u);
  check(receiver.word_08 == 0x22222222u,
        "an argument equal to the stale word is stored either way");
  check(receiver.word_10 == 0x44444444u,
        "an argument equal to the stale word is stored either way");

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0xcafebabeu,
                                             0xfeedfaceu);
  check(receiver.word_08 == 0xcafebabeu, "+0x08 is overwritten, not merged");
  check(receiver.word_10 == 0xfeedfaceu, "+0x10 is overwritten, not merged");
}

// Repeated invocation is idempotent for equal arguments and overwrites stale
// state for different ones; neither call may disturb the sibling words.
void test_repeated_invocation_overwrites_stale_words() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0x00000001u,
                                             0x00000002u);
  check(receiver.word_08 == 0x00000001u, "+0x08 after the first call");
  check(receiver.word_10 == 0x00000002u, "+0x10 after the first call");

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0x00000001u,
                                             0x00000002u);
  check(receiver.word_08 == 0x00000001u, "+0x08 is idempotent for equal input");
  check(receiver.word_10 == 0x00000002u, "+0x10 is idempotent for equal input");
  check(receiver.word_0c == 0x33333333u, "sibling +0x0c survives");
  check(receiver.word_14 == 0x55555555u, "sibling +0x14 survives");

  re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0xcafebabeu,
                                             0xfeedfaceu);
  check(receiver.word_08 == 0xcafebabeu, "+0x08 after the third call");
  check(receiver.word_10 == 0xfeedfaceu, "+0x10 after the third call");
}

// Zero is an ordinary payload value, not a skip.
void test_zero_words_are_written() {
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();

  const OpaqueWord result =
      re_00fc7e10_UTFWin_ImageDrawable_GetTiling(&receiver, 0u, 0u);

  check(receiver.word_08 == 0u, "a zero first word is stored, not skipped");
  check(receiver.word_10 == 0u, "a zero second word is stored, not skipped");
  check(result == 0u, "EAX is left holding the first word, zero here");
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

    check(receiver.word_08 == first, "+0x08 tracks the first word");
    check(receiver.word_10 == second, "+0x10 tracks the second word");

    OpaqueSlot7ReceiverWire diff = receiver;
    diff.word_08 = previous.word_08;
    diff.word_10 = previous.word_10;
    check(std::memcmp(&diff, &previous, sizeof(diff)) == 0,
          "no byte outside +0x08 and +0x10 may change");

    previous = receiver;
  }
}

// The declared callee-cleanup contract, exercised rather than described: the
// call is made through a pointer of the modelled type, so the receiver travels
// in ECX and both words travel on the stack. A cdecl-flavoured body would have
// taken the receiver from the stack and stored through that pointer instead, so
// which object receives the two words is also a measurement of the receiver's
// register.
void test_call_goes_through_the_modelled_convention() {
  const EntryPoint target = &re_00fc7e10_UTFWin_ImageDrawable_GetTiling;
  OpaqueSlot7ReceiverWire receiver = seeded_receiver();

  const OpaqueWord result = target(&receiver, 0x0badf00du, 0x00c0ffeeu);

  check(receiver.word_08 == 0x0badf00du,
        "the first stack word reached the body and landed at +0x08");
  check(receiver.word_10 == 0x00c0ffeeu,
        "the second stack word reached the body and landed at +0x10");
  check(receiver.dispatch_00 == 0x01491730u,
        "the receiver the body wrote through is the caller's object");
  check(result == 0x0badf00du, "EAX is left holding the first stack word");
}

} // namespace

int run_tests() {
  test_stores_both_words_to_proven_offsets();
  test_argument_order_is_not_swapped();
  test_displacements_are_byte_offsets_not_word_indices_or_runs();
  test_first_word_is_published_as_a_callable_address();
  test_stores_overwrite_stale_state_without_reading_it();
  test_repeated_invocation_overwrites_stale_words();
  test_zero_words_are_written();
  test_only_the_two_published_offsets_change();
  test_call_goes_through_the_modelled_convention();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}

} // namespace openspore::reconstruction::pkg_utfwin_slot7_wave12

int main() {
  return openspore::reconstruction::pkg_utfwin_slot7_wave12::run_tests();
}
