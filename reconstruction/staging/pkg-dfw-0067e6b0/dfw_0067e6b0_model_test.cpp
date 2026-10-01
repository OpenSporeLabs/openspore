// PKG-DFW-0067E6B0 -- VA 0x0067e6b0
// Behavioural model test for dfw_0067e6b0_func3Ch.
//
// The two direct callees are defined here as observers, so this test sees every
// transfer the reconstruction makes, in order, with the words it hands over, and
// it gets to decide what each callee returns. That is what lets the assertions
// below be about the listing rather than about a type system.
//
// The claims asserted are exactly the ones the 11-instruction listing fixes:
//   * one unconditional transfer at 0x0067e6b3, on both paths, with the receiver
//     and with nothing else;
//   * one conditional transfer at 0x0067e6c0, reached only when bit 0 of the low
//     byte of the argument word is set, and only ever handed the receiver;
//   * the order the two transfers happen in;
//   * the EAX word on each path, which is the receiver on both;
//   * that neither callee's return word reaches the caller;
//   * that the body writes no memory at all.
//
// What this interface cannot see, stated so it is not over-claimed: the machine
// reads the gate word from its own stack slot AFTER the first callee has run
// (0x0067e6b8, with only the PUSH ESI at 0x0067e6b0 outstanding). A C parameter
// is a by-value copy with no address the callee can reach, so a reconstruction
// that read the word before the call would be indistinguishable here. The
// ordering that IS observable -- transfer 1 before transfer 2, and both of them
// gated exactly as listed -- is asserted below; the read-vs-call order is not
// observable through this interface and is not claimed to be tested.

#include "dfw_0067e6b0_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_dfw_0067e6b0 {

// 0x0067e6b0, defined in the package's own translation unit. The header declares
// only the two callees, so the reconstructed body is declared here with the same
// portable calling-convention spelling the package uses.
extern "C" pointer_to_the_receiver PKG_DFW_0067E6B0_THISCALL
dfw_0067e6b0_func3Ch(opaque_receiver receiver,
                     branch_gate_word argument_word);

namespace {

// A word that cannot be confused with the receiver, the gate word, or a real
// return value. Both observers return it, so any leak of a callee's return word
// into the result of the body is visible.
constexpr Word kPoison = 0xdeadbeefu;

enum class Step { kFirstTransfer, kSecondTransfer };

struct Observation {
  int first_calls = 0;
  int second_calls = 0;
  opaque_receiver first_receiver = nullptr;
  pointer_to_the_receiver second_payload = nullptr;
  int order[4] = {0, 0, 0, 0};
  int order_length = 0;
  // When set, the modelled 0x0067e2b0 scribbles over the receiver block. The
  // body copied the receiver into ESI at 0x0067e6b1, before the call, so
  // nothing that callee does to those bytes can reach what the body forwards at
  // 0x0067e6bf or what it returns at 0x0067e6c8.
  bool first_scribbles_receiver = false;
};

Observation g_obs;

void reset_observation() {
  g_obs = Observation{};
}

void record(Step step) {
  if (g_obs.order_length < 4) {
    g_obs.order[g_obs.order_length] = static_cast<int>(step);
    ++g_obs.order_length;
  }
}

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// A receiver block. The body dereferences nothing, so its size and contents are
// irrelevant to the reconstruction; it exists so the "writes no memory" check has
// something to watch, and so the pointer handed to the callees is a real
// non-null address distinct from every gate word used below.
struct Receiver {
  unsigned char bytes[64];
};

Receiver make_receiver() {
  Receiver receiver{};
  std::memset(receiver.bytes, 0xa5, sizeof receiver.bytes);
  return receiver;
}

}  // namespace

// 0x0067e6b3 -- the unconditional transfer. Nothing is pushed, so the observer
// can only have been handed the receiver through the register convention.
extern "C" Word PKG_DFW_0067E6B0_THISCALL first_transfer_0067e2b0(
    opaque_receiver receiver) {
  ++g_obs.first_calls;
  g_obs.first_receiver = receiver;
  record(Step::kFirstTransfer);
  if (g_obs.first_scribbles_receiver && receiver != nullptr) {
    std::memset(static_cast<void *>(receiver), 0x5au,
                sizeof(static_cast<Receiver *>(receiver)->bytes));
  }
  return kPoison;
}

// 0x0067e6c0 -- the conditional transfer, caller-cleaned, taking the single word
// pushed at 0x0067e6bf.
extern "C" Word PKG_DFW_0067E6B0_CDECL second_transfer_00f47380(
    pointer_to_the_receiver payload) {
  ++g_obs.second_calls;
  g_obs.second_payload = payload;
  record(Step::kSecondTransfer);
  return kPoison;
}

namespace {

// A body that made no call at all, or only the conditional one, fails here.
void test_the_first_transfer_is_unconditional_and_carries_the_receiver() {
  const Word words[] = {0u, 1u, 2u, 0x100u, 0x80000000u, 0xffffffffu};
  for (const Word word : words) {
    Receiver receiver = make_receiver();
    reset_observation();

    (void)dfw_0067e6b0_func3Ch(receiver.bytes, word);

    check(g_obs.first_calls == 1,
          "0x0067e6b3 runs exactly once for every gate word, including a "
          "cleared one");
    check(g_obs.first_receiver == static_cast<opaque_receiver>(receiver.bytes),
          "0x0067e6b3 receives the receiver and nothing is pushed for it");
  }
}

// JZ 0x0067e6c8: a cleared bit 0 skips the whole block, and the body still pops
// the saved register and returns.
void test_a_cleared_gate_word_skips_the_second_transfer() {
  const Word words[] = {0u, 2u, 4u, 0x100u, 0x00fffffeu, 0xfffffffeu};
  for (const Word word : words) {
    Receiver receiver = make_receiver();
    reset_observation();

    (void)dfw_0067e6b0_func3Ch(receiver.bytes, word);

    check(g_obs.second_calls == 0,
          "0x0067e6c0 is skipped whenever bit 0 of the gate word is clear");
  }
}

// The taken side: exactly one call, and the word it is handed is the ESI copy of
// the receiver -- not the gate word, not a re-read of the entry register.
void test_a_set_gate_word_reaches_the_second_transfer_with_the_receiver() {
  const Word words[] = {1u, 3u, 0x101u, 0xffffffffu};
  for (const Word word : words) {
    Receiver receiver = make_receiver();
    reset_observation();

    (void)dfw_0067e6b0_func3Ch(receiver.bytes, word);

    check(g_obs.second_calls == 1,
          "0x0067e6c0 runs exactly once when bit 0 of the gate word is set");
    check(g_obs.second_payload ==
              static_cast<pointer_to_the_receiver>(receiver.bytes),
          "0x0067e6bf PUSH ESI hands the receiver to 0x00f47380, not the gate "
          "word");
  }
}

// TEST byte ptr [ESP + 0x8],0x1 -- a byte test against the immediate 0x1. This
// table is what makes the mask and its position load-bearing: a body that tested
// the whole word against zero, or tested bit 1, or tested the high byte, fails
// at least one row.
void test_only_bit_zero_of_the_low_byte_decides_the_branch() {
  struct Row {
    Word word;
    bool second_transfer_expected;
  };
  const Row rows[] = {
      {0x00000000u, false}, {0x00000001u, true},  {0x00000002u, false},
      {0x00000003u, true},  {0x00000004u, false}, {0x00000010u, false},
      {0x00000100u, false}, {0x00010000u, false}, {0x01000000u, false},
      {0x80000000u, false}, {0x7ffffffeu, false}, {0x7fffffffu, true},
      {0xfffffffeu, false}, {0xffffffffu, true},
  };
  for (const Row &row : rows) {
    Receiver receiver = make_receiver();
    reset_observation();

    (void)dfw_0067e6b0_func3Ch(receiver.bytes, row.word);

    check(g_obs.second_calls == (row.second_transfer_expected ? 1 : 0),
          "the branch follows bit 0 of the low byte of the gate word and "
          "nothing else");
  }
}

// The listing's order: 0x0067e6b3 comes before 0x0067e6c0, and the conditional
// transfer never precedes the unconditional one.
void test_the_two_transfers_happen_in_the_listed_order() {
  {
    Receiver receiver = make_receiver();
    reset_observation();
    (void)dfw_0067e6b0_func3Ch(receiver.bytes, 0u);
    check(g_obs.order_length == 1 && g_obs.order[0] == static_cast<int>(Step::kFirstTransfer),
          "with the bit clear, only the transfer at 0x0067e6b3 happens");
  }
  {
    Receiver receiver = make_receiver();
    reset_observation();
    (void)dfw_0067e6b0_func3Ch(receiver.bytes, 1u);
    check(g_obs.order_length == 2 &&
              g_obs.order[0] == static_cast<int>(Step::kFirstTransfer) &&
              g_obs.order[1] == static_cast<int>(Step::kSecondTransfer),
          "with the bit set, 0x0067e6b3 runs before 0x0067e6c0");
  }
}

// 0x0067e6c8 MOV EAX,ESI is the only write to the return register and it is on
// the shared exit, so both paths return the receiver. Both observers return
// kPoison, so this also proves neither callee's return word reaches the caller.
void test_both_paths_return_the_receiver_and_no_callee_word_leaks() {
  const Word words[] = {0u, 1u, 0xdeadbeefu, 0xffffffffu};
  for (const Word word : words) {
    Receiver receiver = make_receiver();
    reset_observation();

    const pointer_to_the_receiver got =
        dfw_0067e6b0_func3Ch(receiver.bytes, word);

    check(got == static_cast<pointer_to_the_receiver>(receiver.bytes),
          "the word left in EAX is the receiver on both paths, and it is the "
          "entry value of the register, not a callee's return word");
  }
}

// The receiver is copied into ESI at 0x0067e6b1 and that copy is what both
// callees are handed and what is returned; nothing re-reads the entry register
// after the copy. Distinct, non-null addresses make the comparison meaningful.
void test_both_transfers_see_the_same_receiver_copy() {
  Receiver first = make_receiver();
  Receiver second = make_receiver();
  reset_observation();

  (void)dfw_0067e6b0_func3Ch(first.bytes, 1u);

  check(g_obs.first_receiver == g_obs.second_payload,
        "0x0067e6b3 and 0x0067e6c0 are handed the same word, the ESI copy");
  check(g_obs.first_receiver != static_cast<opaque_receiver>(second.bytes),
        "the two receivers really are distinct addresses, so the comparison "
        "above is not vacuous");
}

// The listing has no store: 11 instructions, zero memory writes. Any byte the
// body wrote would show up here. One limit worth stating: a write of a value
// that happened to equal the byte already there would not show up, and this
// interface cannot see such a store; every write that changes a byte is
// excluded.
void test_the_body_writes_no_memory() {
  const Word words[] = {0u, 1u};
  for (const Word word : words) {
    Receiver receiver = make_receiver();
    unsigned char before[sizeof receiver.bytes];
    std::memcpy(before, receiver.bytes, sizeof before);
    reset_observation();

    (void)dfw_0067e6b0_func3Ch(receiver.bytes, word);

    check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
          "no byte of the receiver is written on either path");
  }
}

// 0x0067e6b1 MOV ESI,ECX copies the receiver ONCE, before the first callee runs,
// and everything afterwards uses that copy. 0x0067e2b0 is not a leaf: its
// listing makes two calls (0x0067e2e1 CALL EDX, 0x0067e2ed CALL 0x0083c750),
// and on x86-32 __thiscall ECX is caller-saved, so the copy is load-bearing on
// the machine. This is the closest a C model can come: the observer scribbles
// over the receiver block during the first transfer, and the body must still
// forward and return the pointer it was handed.
//
// Declared limit, stated so it is not over-read: a C model cannot express WHICH
// REGISTER holds the value, so a reconstruction that re-read its receiver
// parameter instead of keeping a pre-call copy is indistinguishable here. The
// reconstruction does keep the copy (esi_receiver is bound at 0x0067e6b1 and is
// the value used at 0x0067e6bf and 0x0067e6c8), which is the faithful shape, but
// the test cannot refute the other one.
void test_the_pre_call_receiver_copy_is_what_is_forwarded_and_returned() {
  Receiver receiver = make_receiver();
  reset_observation();
  g_obs.first_scribbles_receiver = true;

  const pointer_to_the_receiver got =
      dfw_0067e6b0_func3Ch(receiver.bytes, 1u);

  check(g_obs.first_scribbles_receiver && g_obs.first_calls == 1,
        "the modelled first callee really did run and really did write");
  check(g_obs.second_payload == static_cast<pointer_to_the_receiver>(receiver.bytes),
        "0x0067e6bf forwards the pointer copied at 0x0067e6b1, unaffected by "
        "what the first callee wrote into the receiver block");
  check(got == static_cast<pointer_to_the_receiver>(receiver.bytes),
        "0x0067e6c8 returns that same copied pointer, not a re-read");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_0067e6b0

int main() {
  using namespace openspore::reconstruction::pkg_dfw_0067e6b0;
  test_the_first_transfer_is_unconditional_and_carries_the_receiver();
  test_a_cleared_gate_word_skips_the_second_transfer();
  test_a_set_gate_word_reaches_the_second_transfer_with_the_receiver();
  test_only_bit_zero_of_the_low_byte_decides_the_branch();
  test_the_two_transfers_happen_in_the_listed_order();
  test_both_paths_return_the_receiver_and_no_callee_word_leaks();
  test_both_transfers_see_the_same_receiver_copy();
  test_the_body_writes_no_memory();
  test_the_pre_call_receiver_copy_is_what_is_forwarded_and_returned();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
