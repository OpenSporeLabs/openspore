// Focused semantic test for the 0x0067e6b0 reconstruction.
//
// What is testable, and what is not. The observable behaviour of this body is
// exactly three things -- the teardown call always happens, the submit call
// happens if and only if bit 0 of the argument word is set, and the receiver
// comes back in the return register. Those are what this file checks. What it
// cannot check is the meaning of the word, the meaning of 0x0067e2b0, and
// whether any consumer of the vtable slot reads the returned pointer: the
// listing fixes none of them, and the test asserts none of them.

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "cheat_func3ch_0067e6b0.hpp"

#if defined(_MSC_VER)
#define TEST3_THISCALL __thiscall
#define TEST3_CDECL __cdecl
#else
#define TEST3_THISCALL __attribute__((thiscall))
#define TEST3_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_cheat_func3ch_0067e6b0 {
namespace {

std::vector<std::string>* events = nullptr;
std::vector<std::string> last_log;
CheatManager* teardown_receiver = nullptr;
CheatManager* submit_argument = nullptr;
int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void record(const char* name) { events->push_back(name); }

void TEST3_THISCALL teardown_stub(CheatManager* manager) {
  teardown_receiver = manager;
  record("teardown_0067e2b0");
}

void TEST3_CDECL submit_stub(CheatManager* manager) {
  submit_argument = manager;
  record("submit_00f47380");
}

Ports make_ports() {
  Ports ports;
  ports.teardown_0067e2b0 = &teardown_stub;
  ports.submit_00f47380 = &submit_stub;
  return ports;
}

using Entry = CheatManager* (TEST3_THISCALL*)(CheatManager*, OpaqueWord);

Entry entry() { return &func3_ch_0067e6b0; }

// One run of the entry with a fresh event log.
CheatManager* run(OpaqueWord gate_word, CheatManager* manager) {
  std::vector<std::string> log;
  events = &log;
  teardown_receiver = nullptr;
  submit_argument = nullptr;

  Ports ports = make_ports();
  g_cheat_func3ch_ports = &ports;
  CheatManager* returned = entry()(manager, gate_word);
  g_cheat_func3ch_ports = nullptr;

  events = nullptr;
  last_log = log;
  return returned;
}

// 0x0067e6b3 runs unconditionally: no gate word suppresses the teardown.
void test_teardown_is_unconditional() {
  for (std::uint32_t word = 0; word < 4; ++word) {
    CheatManager manager;
    run(static_cast<OpaqueWord>(word), &manager);
    check(last_log.size() >= 1u);
    check(last_log[0] == "teardown_0067e2b0");
    check(teardown_receiver == &manager);
  }
}

// 0x0067e6b8 tests bit 0 of the low byte: these words must all take the branch
// and these must all skip it. Bit 1 alone must NOT open the gate, which is the
// only way to show the test is on bit 0 and not on "non-zero".
void test_gate_is_bit_zero_only() {
  const std::uint32_t closed[] = {0x00000000u, 0x00000002u, 0x00000004u,
                                  0x000000feu, 0xfffffffeu, 0x00010000u};
  for (std::uint32_t word : closed) {
    CheatManager manager;
    run(word, &manager);
    check(last_log.size() == 1u);
    if (last_log.size() == 1u) {
      check(last_log[0] == "teardown_0067e2b0");
    }
    check(submit_argument == nullptr);
  }

  const std::uint32_t open[] = {0x00000001u, 0x00000003u, 0x00000101u,
                                0xffffffffu, 0x80000001u};
  for (std::uint32_t word : open) {
    CheatManager manager;
    run(word, &manager);
    check(last_log.size() == 2u);
    if (last_log.size() == 2u) {
      check(last_log[0] == "teardown_0067e2b0");
      check(last_log[1] == "submit_00f47380");
    }
    check(submit_argument == &manager);
  }
}

// 0x0067e6bf/0x0067e6c0: the argument pushed for 0x00f47380 is the receiver,
// not the gate word and not a copy of anything else.
void test_submit_carries_the_receiver() {
  CheatManager manager;
  run(0x00000001u, &manager);
  check(submit_argument == &manager);
  check(submit_argument != reinterpret_cast<CheatManager*>(&manager.gate_064));
}

// The submit call is after the teardown call and never before it.
void test_call_order() {
  CheatManager manager;
  run(0x00000001u, &manager);
  check(last_log.size() == 2u);
  if (last_log.size() == 2u) {
    check(last_log[0] == "teardown_0067e2b0");
    check(last_log[1] == "submit_00f47380");
  }
}

// 0x0067e6c8 writes the receiver into EAX on the single exit path, so both
// branches hand the same pointer back. The SDK signature says void; this
// records the machine's behaviour, and is the one place the reconstruction
// knowingly departs from the declared type.
void test_receiver_is_returned_on_both_paths() {
  CheatManager manager;
  check(run(0x00000000u, &manager) == &manager);
  check(run(0x00000001u, &manager) == &manager);
}

// The gate word is read once and only after the first call
// (0x0067e6b3 precedes 0x0067e6b8), so the teardown always runs first and the
// decision to submit is taken on the word as it stands afterwards. What the
// callees do to that slot is not observable from here, so the test pins only
// the order that the listing fixes.
void test_gate_is_read_after_the_teardown() {
  CheatManager manager;
  run(0x00000000u, &manager);
  check(last_log.size() == 1u);
  if (!last_log.empty()) {
    check(last_log[0] == "teardown_0067e2b0");
  }
}

// Layout pins, restated at run time so a header edit that keeps the source
// compiling still fails the test.
void test_offsets() {
  check(offsetof(CheatManager, subobject_014) == 0x14);
  check(offsetof(CheatManager, owner_024) == 0x24);
  check(offsetof(CheatManager, gate_064) == 0x64);
  check(offsetof(SubObjectVTable, entry_10) == 0x10);
  check(offsetof(AllocatorSingleton, lock_04e4) == 0x4e4);
  check(kGateMask == 0x1u);
}

int run_tests() {
  test_offsets();
  test_teardown_is_unconditional();
  test_gate_is_bit_zero_only();
  test_submit_carries_the_receiver();
  test_call_order();
  test_receiver_is_returned_on_both_paths();
  test_gate_is_read_after_the_teardown();
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_cheat_func3ch_0067e6b0::run_tests();
}

#undef TEST3_CDECL
#undef TEST3_THISCALL
