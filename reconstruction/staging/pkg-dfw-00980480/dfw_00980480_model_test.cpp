// PKG-DFW-00980480 -- VA 0x00980480
// Behavioural model test for the two-instruction body at 0x00980480.
//
//   00980480  SUB ECX, 0x4
//   00980483  JMP 0x00980330
//
// 0x00980330 is not this package's target and is not reconstructed here, so its
// contract is satisfied below by an observer: it records the arguments it was
// handed and returns a value this test chooses. That is what lets the test
// observe the two things the listing actually fixes -- the receiver adjustment
// applied before the transfer, and the single stack word passed through without
// being touched -- and the two things it then hands back: the callee's result
// word, forwarded verbatim, and the fact that the transfer happens exactly once.
//
// The assertions are claims the machine listing makes and nothing more. There is
// no claim here about what the forwarded word means, what the returned word
// points at, which class this belongs to, or which virtual reaches it. The
// forwarded word is checked for bit-identity only; the returned word is checked
// for bit-identity only.
//
// One limit is stated rather than papered over: this is a C++ model of a body
// that has no epilogue, so the absence of a PUSH and the absence of a CALL
// before the transfer are stated in the reconstruction's comments but are not
// observable through this interface. A model that pushed a return address would
// still pass every check below. What is observable -- and is asserted -- is that
// the transfer happens once, that its arguments are the adjusted receiver and
// the caller's own word, and that nothing about the receiver is disturbed.

#include "dfw_00980480_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_dfw_00980480 {

namespace {

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// The receiver's adjustment, restated as a machine displacement so the expected
// value in the assertions below is the instruction's 0x4 and not this test's
// name for it. The sibling adjustor thunk at 0x00980470 subtracts a different
// amount; 0x0c is used in one assertion purely as a value the model must NOT
// produce, to catch a copy of that sibling.
constexpr std::uintptr_t kExpectedAdjustment = 0x04u;
constexpr std::uintptr_t kSiblingAdjustment = 0x0cu;

// The one immediate the tail callee's own listing compares the forwarded word
// against, at 0x00980334. It belongs to the callee, not to this body; it is
// named here only because it is the single most interesting word this body can
// be asked to forward, and forwarding it bit-for-bit is a real check.
constexpr MessageWord kCalleeImmediate = 0xef865d7eu;

struct Observation {
  int calls = 0;
  Opaque *received_receiver = nullptr;
  MessageWord received_word = 0u;
  // What the observer hands back. Preset by each test.
  Opaque *result = nullptr;
};

Observation g_obs;

// A receiver the body is allowed to do anything with. 64 bytes, zero-filled, so
// a word nobody writes reads as zero and any store into the block shows up in
// the byte-for-byte comparison.
struct Receiver {
  unsigned char bytes[64];
};

Receiver make_receiver() {
  Receiver receiver;
  std::memset(receiver.bytes, 0, sizeof receiver.bytes);
  return receiver;
}

// The address the model is expected to hand the tail callee for a given entry
// address: the entry address moved down by 0x4, in uintptr_t arithmetic so the
// null case wraps the way ECX does rather than becoming undefined.
Opaque *expected_adjusted(const void *entered) {
  return reinterpret_cast<Opaque *>(
      reinterpret_cast<std::uintptr_t>(entered) - kExpectedAdjustment);
}

}  // namespace

// 0x00980483 -- the body transfers control here and this is the receiving end.
// Nothing is pushed, so the receiver arrives in ECX and the word arrives in the
// one stack slot above the return address, exactly as the callee's own listing
// reads it at 0x00980330.
extern "C" Opaque* PKG_DFW_00980480_THISCALL
tail_00980330(Opaque *adjusted_receiver, MessageWord forwarded_word) {
  ++g_obs.calls;
  g_obs.received_receiver = adjusted_receiver;
  g_obs.received_word = forwarded_word;
  return g_obs.result;
}

namespace {

// 0x00980480 -- the adjustment happens before the transfer, so the callee must
// see the entry address moved down by exactly four bytes. Both negatives are
// asserted too, because "the callee got something near the receiver" is not the
// claim: the claim is the exact address.
void test_receiver_is_adjusted_down_by_exactly_four() {
  Receiver receiver = make_receiver();
  g_obs = Observation{};

  handle_message_00980480(receiver.bytes, kCalleeImmediate);

  check(g_obs.received_receiver == expected_adjusted(receiver.bytes),
        "0x00980480 hands the callee the entry address minus exactly 0x4");
  check(g_obs.received_receiver != receiver.bytes,
        "the transfer is not made with the unadjusted receiver");
  check(g_obs.received_receiver !=
            reinterpret_cast<Opaque *>(
                reinterpret_cast<std::uintptr_t>(receiver.bytes) -
                kSiblingAdjustment),
        "the adjustment is 0x4, not the 0x0c the sibling thunk at 0x00980470 uses");
}

// The listing holds one transfer and nothing else, so the callee runs once.
void test_the_transfer_happens_exactly_once() {
  Receiver receiver = make_receiver();
  g_obs = Observation{};

  handle_message_00980480(receiver.bytes, kCalleeImmediate);

  check(g_obs.calls == 1, "0x00980483 transfers control exactly once");
}

// The body contains no PUSH and no store, so the caller's own word reaches the
// callee unchanged. Checked over values chosen to catch a truncation, a sign
// extension, a byte swap and a null test: any of those would pass on a single
// convenient value.
void test_the_stack_word_is_forwarded_bit_for_bit() {
  const MessageWord words[] = {
      0x00000000u,  // the word the callee's own JZ would treat as "not matched"
      0x00000001u,  // all bits but the lowest
      0x0000ffffu,  // the low half only
      0xffff0000u,  // the high half only
      0x80000000u,  // the sign bit alone
      0xef865d7eu,  // the immediate the callee compares against at 0x00980334
      0xffffffffu,
  };

  for (const MessageWord word : words) {
    Receiver receiver = make_receiver();
    g_obs = Observation{};

    handle_message_00980480(receiver.bytes, word);

    check(g_obs.calls == 1, "exactly one transfer per forwarded word");
    check(g_obs.received_word == word,
          "the caller's stack word reaches the callee bit-identical, for every "
          "word tested");
  }
}

// 0x00980483 is a tail transfer, so the word the callee leaves in EAX is this
// body's result. The preset results are chosen so that a normalised result
// cannot pass: the SDK and Ghidra name this symbol `bool`, and a model that
// returned "non-null ? 1 : 0" would collapse every one of these to 1.
void test_the_result_word_is_forwarded_verbatim() {
  const Opaque *const results[] = {
      nullptr,
      reinterpret_cast<const Opaque *>(static_cast<std::uintptr_t>(0x00000001u)),
      reinterpret_cast<const Opaque *>(static_cast<std::uintptr_t>(0x0000abcdu)),
      reinterpret_cast<const Opaque *>(static_cast<std::uintptr_t>(0xdeadbeefu)),
  };

  Receiver receiver = make_receiver();
  for (const Opaque *const preset : results) {
    g_obs = Observation{};
    g_obs.result = const_cast<Opaque *>(preset);

    const Opaque *const got =
        handle_message_00980480(receiver.bytes, kCalleeImmediate);

    check(got == preset,
          "the callee's word is returned verbatim, not normalised to a byte");
    check(got != receiver.bytes,
          "the returned word is the callee's, not the entry receiver");
    check(got != expected_adjusted(receiver.bytes),
          "the returned word is the callee's, not the adjusted receiver");
  }
}

// 0x00980480 is a bare SUB with no TEST and no branch, so a null receiver is not
// special: 0 - 4 wraps to 0xfffffffc and the transfer still happens. A model
// that added a null guard would be claiming a branch the listing does not have.
void test_a_null_receiver_wraps_rather_than_being_guarded() {
  g_obs = Observation{};
  g_obs.result = reinterpret_cast<Opaque *>(
      static_cast<std::uintptr_t>(0xcafebabeu));

  const Opaque *const got = handle_message_00980480(nullptr, kCalleeImmediate);

  check(g_obs.calls == 1, "a null receiver still transfers control once");
  check(g_obs.received_receiver ==
            reinterpret_cast<Opaque *>(0xfffffffcu),
        "a null receiver wraps to 0xfffffffc: the SUB is unconditional");
  check(g_obs.received_word == kCalleeImmediate,
        "a null receiver does not change the forwarded word");
  check(got == g_obs.result,
        "a null receiver still returns the callee's word");
}

// The complete listing holds no memory operand at all, so the body writes no
// byte of the receiver. The adjustment is register arithmetic, not a store.
void test_the_receiver_block_is_not_written() {
  Receiver receiver = make_receiver();
  unsigned char before[sizeof receiver.bytes];

  // A non-zero pattern, so a store of the same value the block already held
  // cannot be mistaken for an absence of stores.
  for (std::size_t i = 0; i < sizeof receiver.bytes; ++i) {
    receiver.bytes[i] = static_cast<unsigned char>(0x10u + i);
  }
  std::memcpy(before, receiver.bytes, sizeof before);

  g_obs = Observation{};
  handle_message_00980480(receiver.bytes, kCalleeImmediate);

  check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
        "no byte of the receiver is written: the body has no memory operand");

  // And on the path where the callee answers zero, so a model that stored a
  // result somewhere in the receiver would be caught on this path too.
  Receiver second = make_receiver();
  std::memcpy(second.bytes, receiver.bytes, sizeof second.bytes);
  std::memcpy(before, second.bytes, sizeof before);

  g_obs = Observation{};
  g_obs.result = nullptr;
  handle_message_00980480(second.bytes, kCalleeImmediate);

  check(std::memcmp(before, second.bytes, sizeof before) == 0,
        "no byte of the receiver is written when the callee answers zero");
}

// The listing holds no conditional branch, so the adjustment does not depend on
// anything. Same entry address, different forwarded words, identical adjusted
// address every time: a model that branched on the word -- for instance to send
// a second value to the callee -- would diverge here.
void test_the_adjustment_does_not_depend_on_the_forwarded_word() {
  const MessageWord words[] = {0x00000000u, 0xef865d7eu, 0xffffffffu, 0x0000ffffu};

  Receiver receiver = make_receiver();
  for (const MessageWord word : words) {
    g_obs = Observation{};
    handle_message_00980480(receiver.bytes, word);
    check(g_obs.received_receiver == expected_adjusted(receiver.bytes),
          "the same entry address is adjusted the same way for every forwarded "
          "word: the body has no branch");
  }
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_00980480

int main() {
  using namespace openspore::reconstruction::pkg_dfw_00980480;
  test_receiver_is_adjusted_down_by_exactly_four();
  test_the_transfer_happens_exactly_once();
  test_the_stack_word_is_forwarded_bit_for_bit();
  test_the_result_word_is_forwarded_verbatim();
  test_a_null_receiver_wraps_rather_than_being_guarded();
  test_the_receiver_block_is_not_written();
  test_the_adjustment_does_not_depend_on_the_forwarded_word();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
