// PKG-DFW-007D9410 -- VA 0x007d9410
// Behavioural model test for the body at 0x007d9410.
//
// The one address this body reaches, 0x007d9bb0, is not part of this package, so
// it is defined here as an observer. That is what lets this test see the transfer
// the reconstruction makes, and it is also what lets the test choose what the
// transfer returns -- which is the only way to show that this body forwards that
// word rather than reinterpreting it.
//
// The assertions are the four claims the two-instruction listing makes and nothing
// more:
//
//   007d9410  SUB ECX,0x4    -> the entry register's value reaches the target four
//                              bytes lower, for every entry value, with no test
//                              of any kind in between
//   007d9413  JMP 0x007d9bb0  -> exactly one transfer, direct, unconditional, and
//                              the last instruction: the stack is not touched, so
//                              the caller's one argument word crosses the transfer
//                              unchanged, and the word the target leaves behind is
//                              the word this body returns
//
// Nothing here asserts what 0x007d9bb0 does internally, what the argument word
// means, or what the entry register points at -- no record in this pack settles
// any of the three.

#include "dfw_007d9410_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_dfw_007d9410 {
namespace {

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// What the observer at 0x007d9bb0 saw, and what it hands back.
struct Observation {
  int calls = 0;
  OpaqueReceiver *receiver = nullptr;
  Word argument_word = 0u;
  unclassified_in_EAX result = 0u;
};

Observation g_obs;

void arm(unclassified_in_EAX result) {
  g_obs = Observation{};
  g_obs.result = result;
}

// The four subtracted at 0x007d9410, in decimal, applied the way the machine
// applies SUB to a 32-bit register: modulo 2^32, with no test.
std::uintptr_t rewind(std::uintptr_t entered) {
  return (entered - 4u) & 0xffffffffu;
}

OpaqueEnteredReceiver *enter_at(std::uintptr_t raw) {
  return reinterpret_cast<OpaqueEnteredReceiver *>(raw);
}

std::uintptr_t raw_of(const OpaqueReceiver *receiver) {
  return reinterpret_cast<std::uintptr_t>(receiver);
}

}  // namespace

// 0x007d9413 -- the one direct transfer, reached by a jump rather than a call. The
// contract is the one the jump fixes: the adjusted entry register arrives as the
// hidden first argument, and the caller's one stack word arrives behind it,
// untouched, because the body pushed nothing before the jump.
extern "C" unclassified_in_EAX PKG_DFW_007D9410_THISCALL
tail_transfer_target_007d9bb0(OpaqueReceiver *receiver, Word argument_word) {
  ++g_obs.calls;
  g_obs.receiver = receiver;
  g_obs.argument_word = argument_word;
  return g_obs.result;
}

namespace {

// A block big enough that entering at several offsets inside it is meaningful and
// nothing in this test ever writes through any of those pointers.
struct Block {
  unsigned char bytes[64] = {};
};

// 007d9410 -- entering four bytes into a block, the value the target receives is
// the block itself. This is the shape the persisted ABI record describes when it
// calls the entry value a subobject pointer the body rewinds to the object start.
void test_entering_four_bytes_in_hands_over_the_block() {
  Block block;
  arm(0u);

  mouse_camera_on_key_down_007d9410(enter_at(raw_of(reinterpret_cast<OpaqueReceiver *>(block.bytes)) + 4u), 0x11u);

  check(g_obs.calls == 1, "0x007d9413 transfers exactly once");
  check(raw_of(g_obs.receiver) ==
            raw_of(reinterpret_cast<OpaqueReceiver *>(block.bytes)),
        "entering at block+4 hands the target block, i.e. the entry value less four");
}

// 007d9410 -- the rewind is exactly four bytes, and it is four for every entry
// value. A displacement of eight, or an addition, or a subtraction applied to
// something other than the entry value, fails here.
void test_the_rewind_is_four_bytes_for_any_entry_value() {
  const std::uintptr_t kEntries[] = {
      0x00401000u, 0x00401001u, 0x00401003u, 0x00401004u, 0x00401010u,
      0x7fffffffu, 0xfffffff0u,
  };
  for (const std::uintptr_t entry : kEntries) {
    arm(0u);
    mouse_camera_on_key_down_007d9410(enter_at(entry), 0x22u);
    check(g_obs.calls == 1, "0x007d9413 transfers exactly once for every entry value");
    check(raw_of(g_obs.receiver) == rewind(entry),
            "the target receives the entry value less four, for every entry value");
  }
}

// 007d9410 -- there is no test in the body. A null entry register is rewound like
// any other value and the transfer still happens, with the machine's wraparound
// in the result. A reconstruction that guards the null case returns early and
// fails both checks here; one that wraps in a wider type hands over 0x00000000
// or 0xFFFFFFFFfffffffe and fails the second.
void test_the_transfer_is_unconditional_on_a_null_entry_register() {
  arm(0u);

  const unclassified_in_EAX got = mouse_camera_on_key_down_007d9410(enter_at(0u), 0x33u);

  check(g_obs.calls == 1, "a null entry register still reaches 0x007d9bb0");
  check(raw_of(g_obs.receiver) == 0xfffffffcu,
        "0x00000000 less four is 0xfffffffc on 32 bits, and that is what arrives");
  check(g_obs.argument_word == 0x33u,
        "the argument word is forwarded on the null path too, not dropped");
  check(got == 0u, "the null path returns the target's word like every other path");
}

// 007d9410 -- the same unconditional rewind, one word above zero, where the
// subtraction borrows across the whole register. This is the case a
// wider-than-32-bit intermediate would get wrong.
void test_the_rewind_wraps_at_zero() {
  arm(0u);

  mouse_camera_on_key_down_007d9410(enter_at(2u), 0x44u);

  check(g_obs.calls == 1, "an entry value of 0x00000002 still reaches 0x007d9bb0");
  check(raw_of(g_obs.receiver) == 0xfffffffeu,
        "0x00000002 less four is 0xfffffffe, not a value above 2^32");
}

// 007d9413 -- the body touches no stack word, so the caller's one argument
// crosses the transfer exactly as it was pushed: same value, same single slot,
// no re-push and no drop in between. Any transformation of the argument, and any
// argument count other than one, fails here.
void test_the_argument_word_crosses_untouched() {
  const Word kWords[] = {0u, 1u, 2u, 0x7fffffffu, 0x80000000u, 0xdeadbeefu, 0xffffffffu};
  for (const Word word : kWords) {
    Block block;
    arm(0u);
    mouse_camera_on_key_down_007d9410(
        enter_at(raw_of(reinterpret_cast<OpaqueReceiver *>(block.bytes))), word);
    check(g_obs.calls == 1, "exactly one transfer for every argument word");
    check(g_obs.argument_word == word, "the argument word arrives unchanged");
  }
}

// 007d9413 -- the jump is the last instruction, so the word the target leaves
// behind is the word this body returns. Values that are neither 0 nor 1 are the
// load-bearing part: the body executes no comparison and no normalisation, so a
// reconstruction that returns a bool, a zero, or a re-derived pointer fails here
// even though every one of those is indistinguishable on 0 and 1.
void test_the_target_s_word_is_returned_verbatim() {
  const unclassified_in_EAX kResults[] = {0u, 1u, 2u, 0x7fffffffu, 0x80000000u,
                                          0xdeadbeefu, 0xffffffffu};
  Block block;
  for (const unclassified_in_EAX result : kResults) {
    arm(result);
    const unclassified_in_EAX got = mouse_camera_on_key_down_007d9410(
        enter_at(raw_of(reinterpret_cast<OpaqueReceiver *>(block.bytes))), 0x55u);
    check(got == result, "the target's return word is returned unchanged, 0xdeadbeef included");
  }
}

// The listing holds no memory operand of any kind, so the body addresses no
// object and writes nothing. Every byte of a block reached through several entry
// offsets inside it must be exactly as it was. This is the check that would catch
// a displacement applied as a store.
//
// One honest limit, the same one the reference package states: a store that wrote
// back the value it had just read would leave the bytes identical and so pass.
// That store is not observable through this interface and is not claimed to be
// excluded; every store that changes a byte is excluded.
void test_the_body_writes_no_byte_of_the_receiver() {
  const std::size_t kOffsets[] = {0u, 1u, 3u, 4u, 8u, 16u};
  for (const std::size_t offset : kOffsets) {
    Block block;
    for (std::size_t index = 0u; index < sizeof block.bytes; ++index) {
      block.bytes[index] = static_cast<unsigned char>(index + 1u);
    }
    unsigned char before[sizeof block.bytes];
    std::memcpy(before, block.bytes, sizeof before);

    arm(0xdeadbeefu);
    mouse_camera_on_key_down_007d9410(
        enter_at(raw_of(reinterpret_cast<OpaqueReceiver *>(block.bytes)) + offset), 0x66u);

    check(std::memcmp(before, block.bytes, sizeof before) == 0,
          "no byte of the receiver is written, for any entry offset");
  }
}

// The body makes one transfer and no other, so the observer's call count tracks
// the number of invocations exactly: no second transfer, and none skipped.
void test_one_transfer_per_invocation() {
  arm(0u);
  Block block;
  const std::uintptr_t base = raw_of(reinterpret_cast<OpaqueReceiver *>(block.bytes));
  const int kInvocations = 16;
  for (int index = 0; index < kInvocations; ++index) {
    mouse_camera_on_key_down_007d9410(enter_at(base + static_cast<std::uintptr_t>(index)), 0x77u);
  }
  check(g_obs.calls == kInvocations,
        "each invocation makes exactly one transfer, with none skipped or doubled");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_007d9410

int main() {
  using namespace openspore::reconstruction::pkg_dfw_007d9410;
  test_entering_four_bytes_in_hands_over_the_block();
  test_the_rewind_is_four_bytes_for_any_entry_value();
  test_the_transfer_is_unconditional_on_a_null_entry_register();
  test_the_rewind_wraps_at_zero();
  test_the_argument_word_crosses_untouched();
  test_the_target_s_word_is_returned_verbatim();
  test_the_body_writes_no_byte_of_the_receiver();
  test_one_transfer_per_invocation();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
