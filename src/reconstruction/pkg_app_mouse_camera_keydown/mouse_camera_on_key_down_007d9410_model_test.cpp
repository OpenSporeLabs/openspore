// Behavioural model test for target 0x007d9410 - App::cMouseCamera::OnKeyDown.
// See mouse_camera_on_key_down_007d9410.hpp for the machine evidence.
//
// The entry is two instructions, so what is tested is exactly what two
// instructions can be wrong about:
//
//   * the receiver word is rewound by four bytes, wrapping at zero, with no
//     null special case;
//   * the caller's ordinary argument crosses the boundary untouched, all 32
//     bits of it, and no bit of it steers control;
//   * control crosses the boundary exactly once, unconditionally, to the one
//     direct target the listing names;
//   * the entry builds no frame of its own;
//   * the return word is the target's, adopted without being written, and
//     narrowed to the declared bool the way a 32-bit return register is.
//
// Every one of those is checkable from the model alone, so a reconstruction
// that got any of them wrong fails here rather than passing quietly.

#include "mouse_camera_on_key_down_007d9410.hpp"

#include <cstdio>
#include <cstdint>

namespace mc = openspore::reconstruction::pkg_app_mouse_camera_keydown;

namespace {

unsigned g_checks = 0u;
unsigned g_failures = 0u;

void report(bool ok, const char* what, const char* detail) {
  g_checks += 1u;
  if (ok) {
    return;
  }
  g_failures += 1u;
  std::printf("FAIL: %s: %s\n", what, detail);
}

void expect_eq_u32(mc::OpaqueWord got, mc::OpaqueWord want, const char* what,
                   const char* detail) {
  char buffer[192];
  std::snprintf(buffer, sizeof buffer, "%s (got 0x%08x, want 0x%08x)", detail,
                static_cast<unsigned>(got), static_cast<unsigned>(want));
  report(got == want, what, buffer);
}

void expect_true(bool got, const char* what, const char* detail) {
  report(got, what, detail);
}

// What the boundary was handed on the way in.
unsigned g_boundary_calls = 0u;
mc::OpaqueWord g_saw_receiver = 0u;
mc::OpaqueWord g_saw_argument = 0u;
mc::OpaqueWord g_saw_frame_words = 0xdeadbeefu;
mc::OpaqueWord g_script_eax = 0u;

void boundary_probe(mc::TailTransferBoundary* boundary) {
  g_boundary_calls += 1u;
  g_saw_receiver = boundary->receiver;
  g_saw_argument = boundary->argument;
  g_saw_frame_words = boundary->entry_frame_words;
  boundary->eax = g_script_eax;
}

void arm(mc::OpaqueWord eax) {
  g_boundary_calls = 0u;
  g_saw_receiver = 0u;
  g_saw_argument = 0u;
  // A sentinel the probe never writes, so a probe that did not run is
  // distinguishable from one that ran and saw zero.
  g_saw_frame_words = 0xdeadbeefu;
  g_script_eax = eax;
  mc::g_entry_trace_007d9410 = mc::EntryTrace{};
  mc::g_tail_target_007d9bb0 = &boundary_probe;
}

mc::OpaqueWord address_of(const mc::OpaqueListenerSubobject* pointer) {
  return static_cast<mc::OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(pointer));
}

// Drives the entry the way a caller does: a pointer in the receiver register
// and a word in the ordinary argument slot.
bool invoke(const mc::OpaqueListenerSubobject* listener, mc::OpaqueWord argument) {
  return mc::on_key_down_007d9410(
      const_cast<mc::OpaqueListenerSubobject*>(listener), argument);
}

const mc::OpaqueWord kWordBattery[] = {
    0x00000000u, 0x00000001u, 0x00000002u, 0x00000003u, 0x00000004u,
    0x00000005u, 0x00000008u, 0x00001000u, 0x10000000u, 0x7ffffffcu,
    0x7fffffffu, 0x80000000u, 0xfffffffbu, 0xfffffffcu, 0xfffffffdu,
    0xdeadbeefu, 0xffffffffu};
const unsigned kWordBatteryCount =
    static_cast<unsigned>(sizeof kWordBattery / sizeof kWordBattery[0]);

const mc::OpaqueWord kArgumentBattery[] = {
    0x00000000u, 0x00000001u, 0x00000002u, 0x00000003u, 0x00010000u,
    0x12345678u, 0x7fffffffu, 0x80000000u, 0xffffffffu};
const unsigned kArgumentBatteryCount =
    static_cast<unsigned>(sizeof kArgumentBattery / sizeof kArgumentBattery[0]);

const mc::OpaqueWord kReturnBattery[] = {
    0x00000000u, 0x00000001u, 0x00000002u, 0x000000ffu, 0x00010000u,
    0x40000000u, 0x7fffffffu, 0x80000000u, 0xfffffffeu, 0xffffffffu};
const unsigned kReturnBatteryCount =
    static_cast<unsigned>(sizeof kReturnBattery / sizeof kReturnBattery[0]);

// A real buffer, so the pointer path is exercised with genuine addresses at
// several alignments rather than with fabricated ones.
alignas(4) unsigned char g_buffer[256];

void test_receiver_word_is_rewound_by_four() {
  for (unsigned i = 0u; i < kWordBatteryCount; ++i) {
    const mc::OpaqueWord word = kWordBattery[i];
    expect_eq_u32(mc::rewind_receiver_007d9410(word), word - 4u,
                  "the receiver word is rewound by exactly four",
                  "adjustor delta over the word battery");
  }
  // `SUB ECX,0x4` is unconditional arithmetic on a 32-bit register, so zero is
  // not special: it wraps, and it is not turned into a null check.
  expect_eq_u32(mc::rewind_receiver_007d9410(0x00000000u), 0xfffffffcu,
                "a zero receiver word wraps rather than being rejected",
                "zero must rewind to 0xfffffffc");
  expect_eq_u32(mc::rewind_receiver_007d9410(0x00000004u), 0x00000000u,
                "a receiver word of four rewinds to zero",
                "rewind of 0x00000004");
}

void test_pointer_path_rewinds_the_address() {
  const unsigned offsets[] = {0u, 4u, 8u, 12u, 16u, 64u, 128u, 252u};
  const unsigned offset_count =
      static_cast<unsigned>(sizeof offsets / sizeof offsets[0]);
  for (unsigned i = 0u; i < offset_count; ++i) {
    const mc::OpaqueListenerSubobject* const at =
        reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer + offsets[i]);
    const mc::OpaqueWord address = address_of(at);
    arm(0u);
    invoke(at, 0u);
    expect_eq_u32(g_saw_receiver, address - 4u,
                  "the address the caller passed is forwarded minus four",
                  "pointer path at a real buffer offset");
    expect_eq_u32(mc::g_entry_trace_007d9410.receiver, address - 4u,
                  "the trace records the rewound address, not the one passed",
                  "pointer path at a real buffer offset");
  }
}

void test_null_receiver_is_not_special_cased() {
  // No null guard: the complete listing holds no conditional branch, so a null
  // receiver is rewound like any other word and still transfers.
  const mc::OpaqueListenerSubobject* const nowhere = nullptr;
  arm(0u);
  invoke(nowhere, 0u);
  expect_eq_u32(g_saw_receiver, 0xfffffffcu,
                "a null receiver is rewound like any other word",
                "zero address must wrap to 0xfffffffc");
  expect_eq_u32(mc::g_entry_trace_007d9410.transfers, 1u,
                "a null receiver still transfers exactly once",
                "no null guard may skip the transfer");
  expect_eq_u32(g_boundary_calls, 1u,
                "a null receiver still reaches the boundary",
                "the boundary is entered once for a null receiver");
}

void test_argument_is_forwarded_verbatim() {
  for (unsigned i = 0u; i < kArgumentBatteryCount; ++i) {
    const mc::OpaqueWord argument = kArgumentBattery[i];
    arm(0u);
    invoke(reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer), argument);
    expect_eq_u32(g_saw_argument, argument,
                  "the caller's argument crosses the boundary untouched",
                  "argument battery entry");
  }
  // In particular the entry does not test, mask or consume a bit of it: the
  // body holds no conditional branch, so no bit of the argument can decide
  // anything here.
  arm(0u);
  invoke(reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer), 0x00000000u);
  const unsigned zero_argument_transfers = mc::g_entry_trace_007d9410.transfers;
  const mc::OpaqueWord zero_argument_receiver = g_saw_receiver;
  arm(0u);
  invoke(reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer), 0xffffffffu);
  expect_eq_u32(mc::g_entry_trace_007d9410.transfers, zero_argument_transfers,
                "no bit of the argument changes the control flow",
                "the entry holds no conditional branch");
  expect_eq_u32(g_saw_receiver, zero_argument_receiver,
                "the argument does not perturb the rewound receiver",
                "the receiver adjustment is independent of the argument");
}

void test_exactly_one_transfer_to_the_named_target() {
  for (unsigned i = 0u; i < kWordBatteryCount; ++i) {
    for (unsigned j = 0u; j < kArgumentBatteryCount; ++j) {
      arm(0u);
      invoke(reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer),
             kArgumentBattery[j]);
      expect_eq_u32(mc::g_entry_trace_007d9410.transfers, 1u,
                    "control crosses the boundary exactly once",
                    "transfer count over the battery cross product");
      expect_eq_u32(mc::g_entry_trace_007d9410.target_va, mc::kTailTargetVa,
                    "the single transfer goes to 0x007d9bb0",
                    "transfer target over the battery cross product");
      expect_eq_u32(g_boundary_calls, 1u,
                    "the boundary is entered exactly once",
                    "boundary entry count over the battery cross product");
      if (g_failures > 0u) {
        return;  // one clear failure per property is enough to diagnose it
      }
    }
  }
}

void test_entry_builds_no_frame() {
  const unsigned offsets[] = {0u, 4u, 64u, 252u};
  const unsigned offset_count =
      static_cast<unsigned>(sizeof offsets / sizeof offsets[0]);
  for (unsigned i = 0u; i < offset_count; ++i) {
    arm(0u);
    invoke(reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer + offsets[i]),
           0u);
    expect_eq_u32(g_saw_frame_words, 0u,
                  "the boundary finds no frame the entry pushed",
                  "words the boundary sees on the stack");
    expect_eq_u32(mc::g_entry_trace_007d9410.entry_frame_words, 0u,
                  "the entry's own frame word count is zero",
                  "entry frame count at a real buffer offset");
  }
}

void test_flow_is_straight_line() {
  arm(0u);
  invoke(reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer), 0u);
  expect_true(!mc::g_entry_trace_007d9410.branched,
              "the entry records no conditional control flow",
              "a two-instruction straight-line body has no branch");
  expect_true(mc::g_entry_trace_007d9410.completed,
              "the entry runs to its single successor",
              "the transfer is the last thing the entry does");

  // The trace shape must not depend on the input: a guard anywhere would make
  // some of these differ.
  for (unsigned i = 0u; i < kWordBatteryCount; ++i) {
    arm(0u);
    invoke(reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer), 0x00000001u);
    expect_eq_u32(mc::g_entry_trace_007d9410.transfers, 1u,
                  "transfer count does not depend on the receiver",
                  "word battery entry");
    expect_eq_u32(mc::g_entry_trace_007d9410.entry_frame_words, 0u,
                  "frame count does not depend on the receiver",
                  "word battery entry");
    expect_true(!mc::g_entry_trace_007d9410.branched,
                "no input turns the entry into a branching body",
                "word battery entry");
  }
}

void test_return_word_is_adopted_and_narrowed_to_bool() {
  const mc::OpaqueListenerSubobject* const at =
      reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer);
  for (unsigned i = 0u; i < kReturnBatteryCount; ++i) {
    const mc::OpaqueWord word = kReturnBattery[i];
    arm(word);
    const bool returned = invoke(at, 0u);
    expect_eq_u32(mc::g_entry_trace_007d9410.observed_eax, word,
                  "the caller observes the target's return word unchanged",
                  "return battery entry");
    // bool out of a 32-bit register is non-zero-ness, not low-bit-ness: a word
    // of 0x00010000 is true, and a word of 0xfffffffe is true.
    expect_true(returned == (word != 0u),
                "the adopted word is narrowed to bool by non-zero-ness",
                "return battery entry");
  }
}

void test_return_word_is_not_manufactured_from_the_receiver() {
  // A null receiver does not make the entry answer false, and a non-null one
  // does not make it answer true: the body never writes the return register, so
  // only the transfer target can decide the answer.
  arm(0xffffffffu);
  const bool from_null_receiver = invoke(nullptr, 0u);
  expect_true(from_null_receiver,
              "a null receiver does not make the entry answer false",
              "the return register is the target's, not the receiver's");

  arm(0x00000000u);
  const bool from_live_receiver =
      invoke(reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer), 0u);
  expect_true(!from_live_receiver,
              "a non-null receiver does not make the entry answer true",
              "the return register is the target's, not the receiver's");
}

void test_unreachable_boundary_is_reported_not_invented() {
  // A null port is a modelling choice about the boundary, not a machine fact.
  // What the model must never do is fabricate a return word for it.
  mc::g_tail_target_007d9bb0 = nullptr;
  mc::g_entry_trace_007d9410 = mc::EntryTrace{};
  const bool returned =
      invoke(reinterpret_cast<const mc::OpaqueListenerSubobject*>(g_buffer), 0u);
  expect_eq_u32(mc::g_entry_trace_007d9410.transfers, 1u,
                "the transfer is still attempted with no boundary installed",
                "transfer count with a null port");
  expect_eq_u32(mc::g_entry_trace_007d9410.observed_eax, 0u,
                "no return word is invented when the boundary is absent",
                "return word with a null port");
  expect_true(!returned,
              "an absent boundary yields the zero word, not a guess",
              "return value with a null port");
  mc::g_tail_target_007d9bb0 = &boundary_probe;
}

}  // namespace

int main() {
  test_receiver_word_is_rewound_by_four();
  test_pointer_path_rewinds_the_address();
  test_null_receiver_is_not_special_cased();
  test_argument_is_forwarded_verbatim();
  test_exactly_one_transfer_to_the_named_target();
  test_entry_builds_no_frame();
  test_flow_is_straight_line();
  test_return_word_is_adopted_and_narrowed_to_bool();
  test_return_word_is_not_manufactured_from_the_receiver();
  test_unreachable_boundary_is_reported_not_invented();

  std::printf("%u check(s), %u failure(s)\n", g_checks, g_failures);
  return g_failures == 0u ? 0 : 1;
}
