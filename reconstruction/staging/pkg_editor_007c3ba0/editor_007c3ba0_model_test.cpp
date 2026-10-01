#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "editor_007c3ba0.hpp"

namespace openspore::reconstruction::pkg_editor_007c3ba0 {
namespace {

#if defined(_MSC_VER)
#define PKG_EDITOR_007C3BA0_TEST_THISCALL __thiscall
#else
#define PKG_EDITOR_007C3BA0_TEST_THISCALL __attribute__((thiscall))
#endif

using TeardownSignature = std::uint8_t(PKG_EDITOR_007C3BA0_TEST_THISCALL*)(
    OpaqueEditorTeardown*);

static_assert(
    std::is_same<decltype(&editor_teardown_007c3ba0), TeardownSignature>::value,
    "007c3ba0 is a zero-argument thiscall with the receiver in ECX");
static_assert(
    std::is_same<decltype(editor_teardown_007c3ba0(
                     static_cast<OpaqueEditorTeardown*>(nullptr))),
                 std::uint8_t>::value,
    "007c3ba0 returns a single byte in AL");
static_assert(std::is_same<decltype(g_editor_slot_007c3ba0_0),
                           TargetWord>::value,
              "0x016f6dac is observed as a 32-bit word");
static_assert(std::is_same<decltype(g_editor_slot_007c3ba0_1),
                           TargetWord>::value,
              "0x016f8a38 is observed as a 32-bit word");
static_assert(std::is_same<decltype(g_editor_slot_007c3ba0_2),
                           TargetWord>::value,
              "0x016f9110 is observed as a 32-bit word");
static_assert(std::is_same<decltype(EditorTeardownPorts::release_field_158),
                           ReleaseWordPort>::value,
              "0x00f47380 is a cdecl port taking one 32-bit word");
static_assert(std::is_same<decltype(EditorTeardownPorts::release_field_170),
                           ReleaseWordPort>::value,
              "0x00f47410 is a cdecl port taking one 32-bit word");

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

struct FixtureReceiver {
  std::uint8_t opaque_000[0x158];
  TargetWord field_158;
  std::uint8_t opaque_15c[0x14];
  TargetWord field_170;
};

static_assert(sizeof(FixtureReceiver) == 0x174,
              "the model fixture mirrors the observed receiver extent");
static_assert(offsetof(FixtureReceiver, field_158) == 0x158,
              "the model fixture keeps the +0x158 word in place");
static_assert(offsetof(FixtureReceiver, field_170) == 0x170,
              "the model fixture keeps the +0x170 word in place");

OpaqueEditorTeardown* as_receiver(FixtureReceiver& fixture) {
  return reinterpret_cast<OpaqueEditorTeardown*>(&fixture);
}

std::size_t release_158_calls = 0;
TargetWord release_158_argument = 0;
std::size_t release_170_calls = 0;
TargetWord release_170_argument = 0;
TargetWord call_order[4]{};
std::size_t call_order_count = 0;

void release_field_158_hook(TargetWord value) {
  ++release_158_calls;
  release_158_argument = value;
  check(call_order_count < 4u);
  call_order[call_order_count] = 0x158u;
  ++call_order_count;
}

void release_field_170_hook(TargetWord value) {
  ++release_170_calls;
  release_170_argument = value;
  check(call_order_count < 4u);
  call_order[call_order_count] = 0x170u;
  ++call_order_count;
}

void install_hooks() {
  EditorTeardownPorts ports;
  ports.release_field_158 = release_field_158_hook;
  ports.release_field_170 = release_field_170_hook;
  editor_teardown_set_ports(ports);
}

void reset_state() {
  release_158_calls = 0;
  release_158_argument = 0;
  release_170_calls = 0;
  release_170_argument = 0;
  call_order_count = 0;
  std::memset(call_order, 0, sizeof(call_order));
  g_editor_slot_007c3ba0_0 = 0;
  g_editor_slot_007c3ba0_1 = 0;
  g_editor_slot_007c3ba0_2 = 0;
  install_hooks();
}

FixtureReceiver make_fixture(TargetWord field_158, TargetWord field_170) {
  FixtureReceiver fixture;
  std::memset(&fixture, 0, sizeof(fixture));
  fixture.field_158 = field_158;
  fixture.field_170 = field_170;
  return fixture;
}

void test_both_words_null_return_zero() {
  reset_state();
  FixtureReceiver fixture = make_fixture(0u, 0u);

  const std::uint8_t result =
      editor_teardown_007c3ba0(as_receiver(fixture));

  check(result == 0u);
  check(release_158_calls == 0u);
  check(release_170_calls == 0u);
  check(call_order_count == 0u);
  check(fixture.field_158 == 0u);
  check(fixture.field_170 == 0u);
  check(g_editor_slot_007c3ba0_0 == 0u);
  check(g_editor_slot_007c3ba0_1 == 0u);
  check(g_editor_slot_007c3ba0_2 == 0u);
}

void test_field_170_present_returns_one() {
  reset_state();
  FixtureReceiver fixture = make_fixture(0u, 0x00c0ffeeu);

  const std::uint8_t result =
      editor_teardown_007c3ba0(as_receiver(fixture));

  check(result == 1u);
  check(release_158_calls == 0u);
  check(release_170_calls == 1u);
  check(release_170_argument == 0x00c0ffeeu);
  check(call_order_count == 1u);
  check(call_order[0] == 0x170u);
  check(fixture.field_170 == 0u);
  check(fixture.field_158 == 0u);
  check(g_editor_slot_007c3ba0_0 == 0u);
  check(g_editor_slot_007c3ba0_1 == 0u);
  check(g_editor_slot_007c3ba0_2 == 0u);
}

void test_field_158_present_without_match_leaves_globals_alone() {
  reset_state();
  g_editor_slot_007c3ba0_0 = 0x11111111u;
  g_editor_slot_007c3ba0_1 = 0x00000004u;
  g_editor_slot_007c3ba0_2 = 0x00000001u;
  FixtureReceiver fixture = make_fixture(0x22222222u, 0u);

  const std::uint8_t result =
      editor_teardown_007c3ba0(as_receiver(fixture));

  check(result == 0u);
  check(release_158_calls == 1u);
  check(release_158_argument == 0x22222222u);
  check(release_170_calls == 0u);
  check(call_order_count == 1u);
  check(call_order[0] == 0x158u);
  check(fixture.field_158 == 0u);
  check(g_editor_slot_007c3ba0_0 == 0x11111111u);
  check(g_editor_slot_007c3ba0_1 == 0x00000004u);
  check(g_editor_slot_007c3ba0_2 == 0x00000001u);
}

void test_matching_field_158_sets_both_flag_bits() {
  reset_state();
  g_editor_slot_007c3ba0_0 = 0x33333333u;
  g_editor_slot_007c3ba0_1 = 0x00000004u;
  g_editor_slot_007c3ba0_2 = 0x00000001u;
  FixtureReceiver fixture = make_fixture(0x33333333u, 0u);

  const std::uint8_t result =
      editor_teardown_007c3ba0(as_receiver(fixture));

  check(result == 0u);
  check(release_158_calls == 1u);
  check(release_158_argument == 0x33333333u);
  check(fixture.field_158 == 0u);
  check(g_editor_slot_007c3ba0_0 == 0u);
  check(g_editor_slot_007c3ba0_1 == 0x00000006u);
  check(g_editor_slot_007c3ba0_2 == 0x00000009u);
}

void test_both_words_present_release_order_and_return_one() {
  reset_state();
  g_editor_slot_007c3ba0_0 = 0x44444444u;
  FixtureReceiver fixture = make_fixture(0x44444444u, 0x55555555u);

  const std::uint8_t result =
      editor_teardown_007c3ba0(as_receiver(fixture));

  check(result == 1u);
  check(release_158_calls == 1u);
  check(release_158_argument == 0x44444444u);
  check(release_170_calls == 1u);
  check(release_170_argument == 0x55555555u);
  check(call_order_count == 2u);
  check(call_order[0] == 0x158u);
  check(call_order[1] == 0x170u);
  check(fixture.field_158 == 0u);
  check(fixture.field_170 == 0u);
  check(g_editor_slot_007c3ba0_0 == 0u);
  check(g_editor_slot_007c3ba0_1 == 0x00000002u);
  check(g_editor_slot_007c3ba0_2 == 0x00000008u);
}

void test_repeat_call_is_idempotent_on_cleared_fields() {
  reset_state();
  g_editor_slot_007c3ba0_0 = 0x66666666u;
  FixtureReceiver fixture = make_fixture(0x66666666u, 0x77777777u);

  check(editor_teardown_007c3ba0(as_receiver(fixture)) == 1u);
  check(editor_teardown_007c3ba0(as_receiver(fixture)) == 0u);
  check(editor_teardown_007c3ba0(as_receiver(fixture)) == 0u);

  check(release_158_calls == 1u);
  check(release_170_calls == 1u);
  check(fixture.field_158 == 0u);
  check(fixture.field_170 == 0u);
  check(g_editor_slot_007c3ba0_0 == 0u);
  check(g_editor_slot_007c3ba0_1 == 0x00000002u);
  check(g_editor_slot_007c3ba0_2 == 0x00000008u);
}

void test_default_ports_are_inert_and_still_clear_fields() {
  editor_teardown_reset_ports();
  release_158_calls = 0;
  release_170_calls = 0;
  g_editor_slot_007c3ba0_0 = 0x88888888u;
  FixtureReceiver fixture = make_fixture(0x88888888u, 0x99999999u);

  check(editor_teardown_007c3ba0(as_receiver(fixture)) == 1u);

  check(release_158_calls == 0u);
  check(release_170_calls == 0u);
  check(fixture.field_158 == 0u);
  check(fixture.field_170 == 0u);
  check(g_editor_slot_007c3ba0_0 == 0u);
  check(g_editor_slot_007c3ba0_1 == 0x00000002u);
  check(g_editor_slot_007c3ba0_2 == 0x00000008u);
}

void test_null_ports_fall_back_to_inert_defaults() {
  editor_teardown_set_ports(EditorTeardownPorts{nullptr, nullptr});
  check(editor_teardown_ports().release_field_158 != nullptr);
  check(editor_teardown_ports().release_field_170 != nullptr);
  release_158_calls = 0;
  release_170_calls = 0;
  FixtureReceiver fixture = make_fixture(0xaaaaaaaau, 0xbbbbbbbbu);

  check(editor_teardown_007c3ba0(as_receiver(fixture)) == 1u);

  check(release_158_calls == 0u);
  check(release_170_calls == 0u);
  check(fixture.field_158 == 0u);
  check(fixture.field_170 == 0u);
}

void test_signature_round_trips_through_function_pointer() {
  reset_state();
  TeardownSignature entry = editor_teardown_007c3ba0;
  FixtureReceiver fixture = make_fixture(0u, 0xccccccccu);

  check(entry(as_receiver(fixture)) == 1u);

  check(release_170_calls == 1u);
  check(release_170_argument == 0xccccccccu);
  check(fixture.field_170 == 0u);
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_editor_007c3ba0;
  test_both_words_null_return_zero();
  test_field_170_present_returns_one();
  test_field_158_present_without_match_leaves_globals_alone();
  test_matching_field_158_sets_both_flag_bits();
  test_both_words_present_release_order_and_return_one();
  test_repeat_call_is_idempotent_on_cleared_fields();
  test_default_ports_are_inert_and_still_clear_fields();
  test_null_ports_fall_back_to_inert_defaults();
  test_signature_round_trips_through_function_pointer();
  return 0;
}

#undef PKG_EDITOR_007C3BA0_TEST_THISCALL
