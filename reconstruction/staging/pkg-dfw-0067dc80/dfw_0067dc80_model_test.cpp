// PKG-DFW-0067DC80 -- VA 0x0067dc80
// Behavioural model test for the body at 0x0067dc80.
//
// The two direct callees the model calls -- 0x0067db10 from 0x0067dc83 and
// 0x00f47380 from 0x0067dc90 -- are not owned by this package, so they are
// defined here as observers. Each records the argument it was handed, in the
// order it was called, and returns nothing, which is what both of their own
// recorded prototypes say. The observers exist so the test can see the transfer
// set and the transfer order the listing fixes, and so nothing about either
// callee's internals leaks into a claim about this body.
//
// The assertions are exactly the claims the machine listing makes:
//
//   * one unconditional direct transfer to 0x0067db10, and it is the FIRST one;
//   * the flag argument is examined at bit 0 only -- not "zero or nonzero";
//   * a clear bit 0 skips 0x00f47380 entirely and nothing else;
//   * a set bit 0 calls 0x00f47380 exactly once, with the receiver itself, and
//     that call comes after the 0x0067db10 call;
//   * the receiver is returned unchanged on both paths, including the path on
//     which it was just released;
//   * the receiver is not null-checked by this body;
//   * not one byte of the receiver is read or written by this body.
//
// What is deliberately NOT asserted, and why:
//
//   * That the flag is read AFTER 0x0067db10. The flag is an ordinary by-value
//     argument: the body reads its own stack slot, and there is no interface
//     through which the first callee could change what is in it. The listing
//     puts the CALL at 0x0067dc83 before the TEST at 0x0067dc88, and the
//     unconditional call is asserted, but the relative position of the two reads
//     is not separable through this model and is not claimed to be tested.
//   * That the epilogue pops 4 bytes. `__attribute__((thiscall))` on x86-32
//     implies callee-pops and the body ends in `RET 0x4`; whether the compiler
//     emits the matching `ret 4` cannot be observed from a C++ caller, so this
//     test says nothing about it and the claim lives in the sidecar instead.
//   * That ESI is restored. Not observable from portable C++, not asserted.
//   * Anything about what either callee does internally, or what the receiver
//     points at. The body never dereferences the receiver and this test keeps
//     it that way.

#include "dfw_0067dc80_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_dfw_0067dc80 {

// 0x0067dc80, defined in the package's own translation unit. The header declares
// only the two callees, so the reconstructed body is declared here with the same
// portable calling-convention spelling the package uses.
extern "C" void* PKG_DFW_0067DC80_THISCALL
App_IMessageManager_Get_0067dc80(OpaqueMessageManagerBlock *receiver,
                                 Word deletingDestructorFlag);

namespace {

// The two callee addresses as the machine spells them, kept as numbers so a
// failure message can name the transfer rather than the observer's local name.
constexpr unsigned long kCompleteDtorVa = 0x0067db10ul;
constexpr unsigned long kGlobalReleaseVa = 0x00f47380ul;

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// A transfer, in the order the model made it.
struct Transfer {
  unsigned long va;
  const void *argument;
  bool operator==(const Transfer &other) const {
    return va == other.va && argument == other.argument;
  }
};

struct Observation {
  Transfer trace[4];
  int trace_count = 0;
  int complete_dtor_calls = 0;
  int global_release_calls = 0;
  const void *complete_dtor_argument = nullptr;
  const void *global_release_argument = nullptr;
};

Observation g_obs;

void record(unsigned long va, const void *argument) {
  if (g_obs.trace_count < 4) {
    g_obs.trace[static_cast<std::size_t>(g_obs.trace_count)] = Transfer{va, argument};
  }
  ++g_obs.trace_count;
}

// A receiver block. The body must never touch it, so the pattern here is
// deliberately not all-zero: an all-zero block would let a body that wrote only
// zeros pass the "unchanged" check below.
struct Receiver {
  unsigned char bytes[64];
};

void fill_pattern(Receiver &receiver) {
  for (std::size_t index = 0; index < sizeof receiver.bytes; ++index) {
    receiver.bytes[index] = static_cast<unsigned char>(0xa5u ^ (index * 7u));
  }
}

void report_flag(Word flag, bool ok, const char *what) {
  if (ok) {
    return;
  }
  std::fprintf(stderr, "FAILED: %s (flag = 0x%08lx)\n", what,
               static_cast<unsigned long>(flag));
  ++g_failures;
}

}  // namespace

// 0x0067db10, the unconditional first callee. Nothing is pushed by the body
// before this call, so the observer takes the receiver alone and records it.
extern "C" void PKG_DFW_0067DC80_THISCALL
imessage_manager_complete_dtor_0067db10(OpaqueMessageManagerBlock *receiver) {
  ++g_obs.complete_dtor_calls;
  g_obs.complete_dtor_argument = receiver;
  record(kCompleteDtorVa, receiver);
}

// 0x00f47380, the conditional release. The body pushes one word and drops it
// with ADD ESP,0x4, so the observer takes one argument and the caller cleans.
extern "C" void PKG_DFW_0067DC80_CDECL
imessage_manager_global_release_00f47380(OpaqueMessageManagerBlock *block) {
  ++g_obs.global_release_calls;
  g_obs.global_release_argument = block;
  record(kGlobalReleaseVa, block);
}

namespace {

// 0067dc83 is unconditional: the listing places the call above the TEST, so it
// runs for a clear bit 0 too, exactly once, and it is the first transfer made.
void test_the_dtor_runs_first_and_unconditionally() {
  static const Word kFlags[] = {0u, 1u, 2u, 3u, 0x80000000u, 0xffffffffu};
  for (std::size_t index = 0; index < sizeof kFlags / sizeof kFlags[0]; ++index) {
    const Word flag = kFlags[index];
    Receiver receiver;
    fill_pattern(receiver);
    g_obs = Observation{};

    App_IMessageManager_Get_0067dc80(receiver.bytes, flag);

    report_flag(flag, g_obs.complete_dtor_calls == 1,
                "0067dc83 runs exactly once for every flag value");
    report_flag(flag, g_obs.trace_count >= 1 &&
                          g_obs.trace[0] == Transfer{kCompleteDtorVa, receiver.bytes},
                "0067dc83 is the first transfer, and it is handed the receiver");
  }
}

// 0067dc88 is `TEST byte ptr [ESP + 0x8],0x1`: a bit-0 test. Flags whose low bit
// is clear must not reach 0x00f47380 whatever their other 31 bits say, and flags
// whose low bit is set must reach it exactly once. This is the assertion that
// separates a bit test from a zero-or-nonzero test, which is a difference the
// encoding fixes and a whole-word test would lose.
void test_only_bit_zero_of_the_flag_is_examined() {
  static const Word kBitZeroClear[] = {0x00000000u, 0x00000002u, 0x00000004u,
                                       0x00000100u, 0x80000000u, 0xfffffffeu};
  for (std::size_t index = 0; index < sizeof kBitZeroClear / sizeof kBitZeroClear[0];
       ++index) {
    const Word flag = kBitZeroClear[index];
    Receiver receiver;
    fill_pattern(receiver);
    g_obs = Observation{};

    App_IMessageManager_Get_0067dc80(receiver.bytes, flag);

    report_flag(flag, g_obs.global_release_calls == 0,
                "0067dc8d takes the JZ: a clear bit 0 skips 0x00f47380 entirely");
  }

  static const Word kBitZeroSet[] = {0x00000001u, 0x00000003u, 0x00000005u,
                                     0x00000101u, 0x80000001u, 0xffffffffu};
  for (std::size_t index = 0; index < sizeof kBitZeroSet / sizeof kBitZeroSet[0];
       ++index) {
    const Word flag = kBitZeroSet[index];
    Receiver receiver;
    fill_pattern(receiver);
    g_obs = Observation{};

    App_IMessageManager_Get_0067dc80(receiver.bytes, flag);

    report_flag(flag, g_obs.global_release_calls == 1,
                "a set bit 0 calls 0x00f47380 exactly once");
  }
}

// The two transfers happen in the listing's order and only when the branch is
// not taken: 0067dc83 then 0067dc90. A body that ran them the other way round,
// or that ran the release on the JZ path, produces a different trace.
void test_the_release_comes_after_the_dtor_and_only_when_the_branch_falls_through() {
  Receiver receiver;
  fill_pattern(receiver);
  g_obs = Observation{};

  App_IMessageManager_Get_0067dc80(receiver.bytes, 1u);

  check(g_obs.trace_count == 2,
        "a set bit 0 makes exactly the two transfers the listing shows");
  if (g_obs.trace_count == 2) {
    check(g_obs.trace[0] == Transfer{kCompleteDtorVa, receiver.bytes},
          "trace[0] is 0x0067db10 with the receiver");
    check(g_obs.trace[1] == Transfer{kGlobalReleaseVa, receiver.bytes},
          "trace[1] is 0x00f47380 with the receiver");
  }

  // And the clear path stops at the first transfer.
  Receiver quiet;
  fill_pattern(quiet);
  g_obs = Observation{};
  App_IMessageManager_Get_0067dc80(quiet.bytes, 0u);
  check(g_obs.trace_count == 1,
        "a clear bit 0 makes the 0x0067db10 transfer and nothing after it");
}

// 0067dc8f is `PUSH ESI`, so the release is handed the receiver itself. A body
// that formed an address first -- the address of its own local, the base of the
// enclosing object, or receiver plus a displacement -- would hand the callee a
// different pointer. The receiver is deliberately passed as an interior address
// here (bytes + 8) so that all three of those alternatives are distinguishable
// from the correct one; the body has no LEA, no ADD and no SUB on any pointer
// operand anywhere in its 11 instructions, so it has no instruction that could
// form one.
void test_the_release_is_handed_the_receiver_and_not_an_address_formed_from_it() {
  Receiver block;
  fill_pattern(block);
  auto *const interior = static_cast<OpaqueMessageManagerBlock *>(block.bytes + 8);
  g_obs = Observation{};

  App_IMessageManager_Get_0067dc80(interior, 1u);

  check(g_obs.global_release_argument == static_cast<const void *>(interior),
        "0067dc8f pushes the receiver value itself");
  check(g_obs.global_release_argument != static_cast<const void *>(block.bytes),
        "0067dc8f does not push the base of the enclosing block");
  check(g_obs.global_release_argument != static_cast<const void *>(&block),
        "0067dc8f does not push the address of the model's own local");
  check(g_obs.complete_dtor_argument == static_cast<const void *>(interior),
        "0067dc83 is handed the same receiver value the release is");
}

// 0067dc98 is `MOV EAX,ESI` and it is reached from both arms, so the receiver
// comes back on both paths -- including the path that has just released it,
// which is what makes this a deleting shape rather than a plain destructor.
void test_the_receiver_is_returned_on_both_paths() {
  Receiver released;
  fill_pattern(released);
  g_obs = Observation{};

  void *const after_release =
      App_IMessageManager_Get_0067dc80(released.bytes, 1u);

  check(after_release == static_cast<void *>(released.bytes),
        "0067dc98 returns the receiver on the path that released it");

  Receiver kept;
  fill_pattern(kept);
  g_obs = Observation{};

  void *const without_release =
      App_IMessageManager_Get_0067dc80(kept.bytes, 0u);

  check(without_release == static_cast<void *>(kept.bytes),
        "0067dc98 returns the receiver on the JZ path too");
}

// The listing has no null check: there is no TEST or CMP against the receiver
// anywhere in the 11 instructions, and 0x00f47380's own guard lives inside that
// callee, not here. So a null receiver is passed straight through to both
// callees and comes straight back.
void test_the_receiver_is_not_null_checked() {
  g_obs = Observation{};
  void *const got = App_IMessageManager_Get_0067dc80(nullptr, 1u);

  check(g_obs.complete_dtor_calls == 1 && g_obs.complete_dtor_argument == nullptr,
        "0067dc83 receives a null receiver without a guard in this body");
  check(g_obs.global_release_calls == 1 && g_obs.global_release_argument == nullptr,
        "0067dc90 receives a null receiver without a guard in this body");
  check(got == nullptr, "0067dc98 returns the null receiver unchanged");
}

// The body has no memory operand other than its own argument slot, so it reads
// and writes no byte of the object. A non-zero, non-uniform pattern is used
// because an all-zero block would not catch a store of zero.
//
// The honest limit: a store that wrote back the value it had just read would
// leave the bytes identical and would pass here. No store is claimed to be
// excluded on that ground; every store that changes a byte is excluded, and the
// body is not claimed to store at all.
void test_no_byte_of_the_receiver_is_read_or_written() {
  Receiver receiver;
  unsigned char before[sizeof receiver.bytes];
  fill_pattern(receiver);
  std::memcpy(before, receiver.bytes, sizeof before);

  g_obs = Observation{};
  App_IMessageManager_Get_0067dc80(receiver.bytes, 0xffffffffu);

  check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
        "the release path leaves every byte of the receiver alone");

  // And the bytes the model would have had to write to record anything: the
  // whole block is still the pattern, not merely equal to itself.
  bool all_pattern = true;
  for (std::size_t index = 0; index < sizeof receiver.bytes; ++index) {
    if (receiver.bytes[index] != static_cast<unsigned char>(0xa5u ^ (index * 7u))) {
      all_pattern = false;
    }
  }
  check(all_pattern, "no byte of the receiver became zero or anything else");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_0067dc80

int main() {
  using namespace openspore::reconstruction::pkg_dfw_0067dc80;
  test_the_dtor_runs_first_and_unconditionally();
  test_only_bit_zero_of_the_flag_is_examined();
  test_the_release_comes_after_the_dtor_and_only_when_the_branch_falls_through();
  test_the_release_is_handed_the_receiver_and_not_an_address_formed_from_it();
  test_the_receiver_is_returned_on_both_paths();
  test_the_receiver_is_not_null_checked();
  test_no_byte_of_the_receiver_is_read_or_written();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
