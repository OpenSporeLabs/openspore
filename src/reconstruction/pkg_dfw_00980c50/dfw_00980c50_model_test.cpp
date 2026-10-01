// PKG-DFW-00980C50 -- VA 0x00980c50
// Behavioural model test for UTFWin::RotateEffect::func88h.
//
// The body under test is two instructions -- MOV EAX,0xcf2b2ad5 and a bare
// RET -- so it makes no transfer, calls nothing and has no extern callee. The
// convention of defining each unowned callee here as an argument-recording
// observer therefore has nothing to bind to in this package, and the test says
// so rather than manufacturing a callee. What stands in for the callee side is
// a CALLER: `probe_sdk_caller_shape` below reproduces the caller the persisted
// ABI record describes (three words pushed, receiver in ECX, the call, then
// the caller removing whatever is left) and reports back what the
// reconstruction left in EAX and how much of the stack the callee consumed.
// Every assertion below is about what that probe observes.
//
// The observable claims the listing fixes, and which this test checks:
//
//   1. the returned word is exactly 0xcf2b2ad5, the immediate at 0x00980c50;
//   2. that word does not depend on the receiver, on any of the three stack
//      words, or on whether the receiver is null -- the body reads no operand
//      of any kind, so there is no input that selects a path;
//   3. the frame pops nothing, so the caller still has to remove all twelve
//      bytes of arguments after the call (bare RET at 0x00980c55);
//   4. no byte of the receiver and no byte of the argument area is written;
//   5. the caller's own frame is left balanced across repeated calls, which is
//      what makes claim 3 an assertion about the ABI and not about one call.
//
// What this test deliberately does NOT claim, stated here so the silence is
// not mistaken for coverage:
//
//   * It does not compare the emitted machine code against the six bytes at
//     0x00980c50. This is a C++ reimplementation, not a copy of the opcodes,
//     and no such comparison would be honest.
//   * A write to a slot the compiler allocates for itself inside the callee's
//     own frame is invisible through this interface and is not claimed to be
//     excluded. Every write that touches the receiver, the argument area or
//     the caller's frame is excluded, and check 4 and check 5 are what exclude
//     them.
//   * It does not claim the void return type wrong or right. It asserts the
//     word the MOV leaves in EAX, which is the part the instructions fix; the
//     SDK/Ghidra void spelling is recorded as an open question in the
//     sidecar, not settled here.
//   * It does not observe ECX inside the callee. The record's claim that the
//     receiver is never read is a property of a prototype with no receiver
//     parameter, so it is asserted by the prototype rather than measured; the
//     measurement the test can make is that the receiver's value does not reach
//     the result, which is check 2.
//
// Teeth, verified by mutation rather than asserted. The package was copied to
// a scratch directory and broken five ways; each was expected to fail and did:
//
//   m1  the immediate changed from 0xcf2b2ad5 to 0xcf2b2ad6
//       -> 5 named checks fail, exit 1.
//   m2  a discriminator invented that the listing has none of: the return made
//       conditional on the receiver being non-null
//       -> 2 named checks fail, exit 1.
//   m3  the stack-cleanup side flipped: the model declared callee-cleaned for
//       three stack words (__attribute__((stdcall)) with three Word parameters),
//       which is the reading the bare RET at 0x00980c55 refutes
//       -> 2 named checks fail, exit 1. The probe's measure-then-rebalance
//          design is what turns this into a reported number instead of a
//          stack-corrupted crash.
//   m4  a store the listing does not have, written through the receiver, but
//       guarded to a real stack-addressed block so the sweep does not fault
//       first
//       -> the receiver canary check fails, exit 1.
//   m5  the same store with no guard, i.e. any dereference of ECX at all
//       -> SIGSEGV, exit 139. This one is caught as a crash rather than as a
//          named check, and that is reported as such: the input sweep
//          deliberately feeds receiver values that are not addresses (0, 1,
//          0x7fffffff, 0x80000000, 0xffffffff, 0xdeadbeef), so a body that
//          reads ECX cannot survive the sweep whether or not any assertion
//          about it exists.
//
// The m3 result is re-verified after the rebalance moved inside the assembly
// block, because that move is what makes m3 reachable at all: a probe that
// repaired ESP from the caller crashed before it could report the flipped
// cleanup side, so the old result was a "rejected" rather than a "reported".
// The mutation now reports 2 named failures under both g++ 16.2.1 and
// clang 22.1.8, which is the property the redesign was for.

#include "dfw_00980c50_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <initializer_list>

namespace openspore::reconstruction::pkg_dfw_00980c50 {
namespace {

// The total number of argument bytes the SDK method header's three words
// occupy. 0x00980c55 is a bare RET, so a caller that pushed them must remove
// all twelve itself; that is the number the stack checks below measure.
constexpr Word kSdkArgumentBytes = 12u;

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// What one probe observed. `result` is the word the reconstruction left in EAX
// when it returned. `esp_delta` is how many bytes of the argument area were
// still there when control came back: 12 means the frame popped nothing,
// which is what a bare RET does and what any callee-cleaned reading of the
// three SDK words would not.
struct Probe {
  Word result;
  Word esp_delta;
};

// The three words the probe samples, written directly by its assembly.
struct ProbeFrame {
  Word esp_before;  // ESP immediately before the three argument pushes
  Word esp_delta;   // ESP immediately after the RET, minus esp_before: the
                    // argument bytes the callee left for the caller to remove
  Word result;      // EAX at that same instant
};

// The receiver block the tests hand in. It is larger than any plausible object
// and is filled from a pattern rather than left zeroed, so a store into it
// would change a byte the test can see.
struct Receiver {
  unsigned char bytes[256];
};

// A pattern that is not a plausible word value, so a read of untouched memory
// cannot be mistaken for the constant the body returns.
constexpr unsigned char kPattern = 0xa5u;

void fill(Receiver &receiver) {
  std::memset(receiver.bytes, kPattern, sizeof receiver.bytes);
}

}  // namespace

// The caller. It pushes the three stack words the SDK method header declares,
// puts the receiver in ECX, calls the reconstruction, and samples ESP the
// instant control returns together with the word in EAX.
//
// The rebalancing happens INSIDE the assembly block, immediately after the
// sample, and that placement is load-bearing rather than cosmetic. The
// quantity to remove is not knowable until the call has returned -- a
// callee-cleaned reading of the same three words would leave nothing -- so the
// value can only be computed after the RET. Leaving the block unbalanced and
// repairing ESP in the C++ caller, which is what an earlier revision of this
// file did, makes the function's own epilogue read a stack it no longer owns:
// GCC (-O0, x86-32) happens to emit `leave` there and so restores ESP from
// EBP, which masks the imbalance, while clang 22 (-O0, x86-32) emits the
// ESP-relative `add $0x34, %esp; pop %ebx; pop %ebp; ret %4`, which is only
// correct while ESP is exactly where the prologue left it. Under clang that
// variant returned through a corrupted return address and the promotion gate
// reported SIGSEGV for a reconstruction whose own body is a bare `ret`. The
// defect is the harness's, not the model's, and the fix is to make the frame
// well-formed rather than to weaken any check: ESP is restored before the
// assembly block ends, `probe_sdk_caller_shape` returns balanced under every
// cleanup side, and the measured delta is still reported as a number.
//
// The assembly is written out longhand for the same reason the listing is: the
// sampling has to happen between the RET and the caller's own stack
// adjustment, which is the only place the two cleanup sides differ. EAX is the
// only scratch register used after the call, because EAX already carries the
// returned word and the compiler is free to place either operand in any
// register it likes; borrowing a second one would risk aliasing an input
// operand and the block declares no register constraint that prevents it.
extern "C" void probe_sdk_caller_shape(const Word *in, ProbeFrame *frame) {
  __asm__ volatile(
      "movl %%esp, 0(%[f])\n\t"
      "movl 16(%[in]), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 12(%[in]), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 8(%[in]), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0(%[in]), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "call dfw_00980c50_func88h\n\t"
      // EAX holds the returned word and ESP is the value the RET left behind.
      // Both are stored before EAX is reused, so the returned word is the one
      // the body produced and not the difference computed two instructions
      // later.
      "movl %%eax, 8(%[f])\n\t"
      "movl %%esp, 4(%[f])\n\t"
      "movl 0(%[f]), %%eax\n\t"
      "subl 4(%[f]), %%eax\n\t"
      // ESP_delta = esp_before - esp_after: 12 for the bare RET the listing
      // fixes, 0 for a callee that popped its own three words.
      "addl %%eax, %%esp\n\t"
      "movl %%eax, 4(%[f])\n\t"
      : : [in] "r"(in), [f] "r"(frame)
      : "eax", "ecx", "memory", "cc");
}

namespace {

// Runs one probe over an explicit four-word argument array and reads back what
// the probe measured.
//
// There is no `add $12, %esp` here and deliberately so. The rebalancing is the
// probe's own job, inside its assembly block, because only the probe knows how
// much the callee left behind. Repairing ESP from out here instead would make
// this function's epilogue run against a stack it does not own, which GCC's
// `leave` hides and clang's ESP-relative epilogue does not.
Probe call_with_words(const Word *in) {
  ProbeFrame frame = {};
  probe_sdk_caller_shape(in, &frame);

  Probe probe;
  probe.result = frame.result;
  // 0x00980c55 is a bare RET, so this is twelve for the reconstruction as the
  // listing fixes it. A callee that popped its own three words would make it
  // zero, and the stack checks below would say so by name.
  probe.esp_delta = frame.esp_delta;
  return probe;
}

// Runs one probe with the given receiver and three stack words.
Probe call_with(Word receiver, Word second, Word third, Word fourth) {
  const Word in[4] = {receiver, second, third, fourth};
  return call_with_words(in);
}

// 0x00980c50 MOV EAX,0xcf2b2ad5 -- the immediate is the whole result.
void test_the_returned_word_is_the_listing_immediate() {
  Receiver receiver;
  fill(receiver);

  const Probe probe = call_with(reinterpret_cast<Word>(&receiver), 0u, 0u, 0u);

  check(probe.result == 0xcf2b2ad5u,
        "0x00980c50 returns exactly the immediate 0xcf2b2ad5");
  check(probe.result == kReturnedWord,
        "the word the body returns is the word the header publishes");
}

// The body has no operand at all, so no input can change what it returns. A
// reconstruction that branched on, read a field of, or otherwise consumed any
// of these would produce a different word for at least one of them, so this is
// the check with teeth for the record's "no discriminator" claim.
void test_no_input_can_change_the_result() {
  Receiver receiver;
  fill(receiver);

  const Word receivers[] = {0u,
                            1u,
                            0x7fffffffu,
                            0x80000000u,
                            0xffffffffu,
                            0xdeadbeefu,
                            reinterpret_cast<Word>(&receiver)};
  const Word words[] = {0u,           1u,           0x7fffffffu, 0x80000000u,
                        0xffffffffu,  0xcf2b2ad5u,  0xcf2b2ad4u, 0x12345678u};

  bool all_constant = true;
  for (const Word receiver_value : receivers) {
    for (const Word first : words) {
      for (const Word second : words) {
        for (const Word third : words) {
          if (call_with(receiver_value, first, second, third).result !=
              0xcf2b2ad5u) {
            all_constant = false;
          }
        }
      }
    }
  }

  check(all_constant,
        "0x00980c50 returns 0xcf2b2ad5 for every receiver and every stack word "
        "combination: the body reads no operand, so it has no discriminator");
}

// 0x00980c55 is a bare RET (opcode C3, no immediate), so the frame removes no
// argument byte. A reconstruction declared callee-cleaned for the SDK's three
// words would report esp_delta 0 here.
void test_the_frame_pops_nothing() {
  Receiver receiver;
  fill(receiver);

  bool all_untouched = true;
  for (const Word value : {0u, 0x12345678u, 0xffffffffu}) {
    if (call_with(reinterpret_cast<Word>(&receiver), value, value, value)
            .esp_delta != kSdkArgumentBytes) {
      all_untouched = false;
    }
  }

  check(all_untouched,
        "the bare RET at 0x00980c55 pops nothing: the caller still owns all "
        "twelve bytes of the SDK argument area after the call");
}

// A null receiver is not a special case, because the frame never reads ECX.
// Stated separately from the sweep above so that a reconstruction which grew a
// null check on the receiver is caught by a named check rather than by an
// anonymous loop iteration.
void test_a_null_receiver_is_not_special() {
  const Probe probe = call_with(0u, 0u, 0u, 0u);

  check(probe.result == 0xcf2b2ad5u,
        "a null receiver still yields 0xcf2b2ad5: no null check exists");
  check(probe.esp_delta == kSdkArgumentBytes,
        "a null receiver still leaves the caller's twelve bytes alone");
}

// The listing has no memory operand, so nothing is written. The receiver block
// and the words pushed as arguments are the two regions a store would land in.
void test_no_byte_of_the_receiver_or_the_arguments_is_written() {
  Receiver receiver;
  fill(receiver);
  unsigned char receiver_before[sizeof receiver.bytes];
  std::memcpy(receiver_before, receiver.bytes, sizeof receiver_before);

  // The four words are the ones the reconstruction is handed: the receiver and
  // the three words the caller pushes. A store through either would change a
  // byte one of the two comparisons below sees.
  const Word in[4] = {reinterpret_cast<Word>(&receiver), 0x11223344u, 0x55667788u,
                      0x99aabbccu};
  Word arguments_before[4];
  std::memcpy(arguments_before, in, sizeof arguments_before);

  call_with_words(in);

  check(std::memcmp(receiver_before, receiver.bytes, sizeof receiver.bytes) == 0,
        "0x00980c50 writes no byte of the receiver");
  check(std::memcmp(arguments_before, in, sizeof arguments_before) == 0,
        "0x00980c50 writes none of the three words the caller pushed");
}

// The caller's own frame survives its own stack rebalancing after every call.
// This is what makes the stack check above an ABI assertion rather than a
// one-shot observation, and it is also the check that keeps the probe itself
// honest: if the rebalancing arithmetic were wrong, the canary would be
// overwritten long before the loop ended.
void test_the_caller_frame_stays_balanced_across_many_calls() {
  unsigned char canary[64];
  unsigned char expected[64];
  std::memset(canary, 0x5au, sizeof canary);
  std::memcpy(expected, canary, sizeof expected);

  Receiver receiver;
  fill(receiver);

  bool all_constant = true;
  for (int index = 0; index < 64; ++index) {
    if (call_with(reinterpret_cast<Word>(&receiver), static_cast<Word>(index),
                  static_cast<Word>(index * 3), 0u)
            .result != 0xcf2b2ad5u) {
      all_constant = false;
      break;
    }
  }

  check(all_constant, "every one of the 64 repeated calls returns 0xcf2b2ad5");
  check(std::memcmp(expected, canary, sizeof expected) == 0,
        "the caller's own frame is intact after 64 calls: the caller removed "
        "exactly the bytes the callee left behind");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_00980c50

int main() {
  using namespace openspore::reconstruction::pkg_dfw_00980c50;
  test_the_returned_word_is_the_listing_immediate();
  test_no_input_can_change_the_result();
  test_the_frame_pops_nothing();
  test_a_null_receiver_is_not_special();
  test_no_byte_of_the_receiver_or_the_arguments_is_written();
  test_the_caller_frame_stays_balanced_across_many_calls();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
