#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "terrain_image_wave9.hpp"

#if defined(_MSC_VER)
#define PKG_TEST_NAKED __declspec(naked)
#define PKG_TEST_THISCALL __thiscall
#else
#define PKG_TEST_NAKED __attribute__((naked))
#define PKG_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_terrain_image_wave9 {
namespace {

struct Fixture;

Fixture* current_fixture = nullptr;

struct Fixture {
  OpaqueSimulationProbeVTable probe_vtable{};
  OpaqueSimulationProbe probe{};
  OpaqueSimulationData simulation{};
  OpaqueSimulationTarget first_target{};
  OpaqueSimulationTarget second_target{};
  OpaqueSimulationTarget* first_result = nullptr;
  OpaqueSimulationTarget* second_result = nullptr;
  OpaqueWord arguments[2]{};
  std::size_t call_count = 0;
  OpaqueImageReceiver receiver{};
  OpaqueWord pending_value = 0;
  OpaqueWord prior_word_08 = 0;
  OpaqueWord port_result = 0;
  std::size_t port_call_count = 0;
};

#if !defined(_MSC_VER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

OpaqueSimulationTarget* PKG_TEST_THISCALL
simulation_select(OpaqueSimulationProbe* probe, OpaqueWord argument) {
  static_cast<void>(probe);
  Fixture& fixture = *current_fixture;
  assert(probe == &fixture.probe);
  assert(probe->vtable == &fixture.probe_vtable);
  assert(fixture.call_count < 2);
  fixture.arguments[fixture.call_count] = argument;
  OpaqueSimulationTarget* result =
      fixture.call_count == 0 ? fixture.first_result : fixture.second_result;
  ++fixture.call_count;
  return result;
}

#if !defined(_MSC_VER)
#pragma GCC diagnostic pop
#endif

OpaqueWord opaque_word_port() {
  Fixture& fixture = *current_fixture;
  assert(fixture.receiver.word_04 == fixture.pending_value);
  assert(fixture.receiver.word_08 == fixture.prior_word_08);
  ++fixture.port_call_count;
  return fixture.port_result;
}

std::size_t first_use_call_count = 0;

OpaqueWord opaque_word_first_use_port() {
  ++first_use_call_count;
  return 0u;
}

void test_default_opaque_word_port() {
  first_use_call_count = 0;
  set_opaque_word_port(nullptr);
  set_opaque_word_first_use_port(opaque_word_first_use_port);
  assert(opaque_word_port_011e58c0() == 0u);
  assert(opaque_word_port_011e58c0() == 0u);
  assert(first_use_call_count == 1);
  static_assert(std::is_same<decltype(&opaque_word_port_011e58c0),
                             OpaqueWord (*)()>::value,
                "direct word port ABI");
}

PKG_TEST_NAKED OpaqueWord probe_stack_check(OpaqueSimulationData*,
                                            OpaqueSimulationProbe*,
                                            std::uintptr_t*, std::uintptr_t*,
                                            OpaqueWord*) {
  __asm__ volatile(
      "movl 0xc(%esp), %edx\n\t"
      "movl %esp, (%edx)\n\t"
      "movl 0x4(%esp), %ecx\n\t"
      "movl 0x8(%esp), %eax\n\t"
      "pushl %eax\n\t"
      "call terrain_probe_00f968b0\n\t"
      "movl 0x14(%esp), %edx\n\t"
      "movl %eax, (%edx)\n\t"
      "movl 0x10(%esp), %edx\n\t"
      "movl %esp, (%edx)\n\t"
      "ret\n\t");
}

PKG_TEST_NAKED OpaqueWord pair_stack_check(OpaquePairDestination*, OpaqueWord,
                                           OpaqueWord, std::uintptr_t*,
                                           std::uintptr_t*) {
  __asm__ volatile(
      "movl 0x10(%esp), %edx\n\t"
      "movl %esp, (%edx)\n\t"
      "movl 0x4(%esp), %ecx\n\t"
      "movl 0xc(%esp), %eax\n\t"
      "pushl %eax\n\t"
      "pushl 0xc(%esp)\n\t"
      "call image_write_pair_00fc7e10\n\t"
      "movl 0x14(%esp), %edx\n\t"
      "movl %esp, (%edx)\n\t"
      "ret\n\t");
}

PKG_TEST_NAKED void field_stack_check(OpaqueImageReceiver*, OpaqueWord,
                                      std::uintptr_t*, std::uintptr_t*) {
  __asm__ volatile(
      "movl 0xc(%esp), %edx\n\t"
      "movl %esp, (%edx)\n\t"
      "movl 0x4(%esp), %ecx\n\t"
      "movl 0x8(%esp), %eax\n\t"
      "pushl %eax\n\t"
      "call image_write_fields_00fd9460\n\t"
      "movl 0x10(%esp), %eax\n\t"
      "movl %esp, (%eax)\n\t"
      "ret\n\t");
}

OpaqueSimulationTarget* simulation_expected(const OpaqueSimulationData* data) {
  return reinterpret_cast<OpaqueSimulationTarget*>(
      reinterpret_cast<std::uintptr_t>(data) + 4u);
}

void initialize_probe(Fixture& fixture) {
  fixture.probe_vtable.select_58 = simulation_select;
  fixture.probe.vtable = &fixture.probe_vtable;
  current_fixture = &fixture;
}

OpaqueWord run_probe(Fixture& fixture, OpaqueSimulationData* data) {
  std::uintptr_t before = 0;
  std::uintptr_t after = 0;
  OpaqueWord result = 0;
  probe_stack_check(data, &fixture.probe, &before, &after, &result);
  assert(before == after);
  return result;
}

void test_terrain_non_null_match() {
  Fixture fixture{};
  initialize_probe(fixture);
  OpaqueSimulationTarget* expected = simulation_expected(&fixture.simulation);
  fixture.first_result = expected;
  fixture.second_result = expected;

  const OpaqueWord result = run_probe(fixture, &fixture.simulation);
  static_cast<void>(result);
  assert(result == 1u);
  assert(fixture.call_count == 2);
  assert(fixture.arguments[0] == 8u);
  assert(fixture.arguments[1] == 7u);
}

void test_terrain_null_sentinel() {
  Fixture fixture{};
  initialize_probe(fixture);
  fixture.first_result = nullptr;
  fixture.second_result = nullptr;

  const OpaqueWord result = run_probe(fixture, nullptr);
  static_cast<void>(result);
  assert(result == 1u);
  assert(fixture.call_count == 2);
  assert(fixture.arguments[0] == 8u);
  assert(fixture.arguments[1] == 7u);
}

void test_terrain_first_mismatch_short_circuits() {
  Fixture fixture{};
  initialize_probe(fixture);
  OpaqueSimulationTarget* expected = simulation_expected(&fixture.simulation);
  fixture.first_result = nullptr;
  fixture.second_result = expected;

  const OpaqueWord result = run_probe(fixture, &fixture.simulation);
  static_cast<void>(result);
  assert(result == 0u);
  assert(fixture.call_count == 1);
  assert(fixture.arguments[0] == 8u);
}

void test_terrain_second_mismatch() {
  Fixture fixture{};
  initialize_probe(fixture);
  OpaqueSimulationTarget* expected = simulation_expected(&fixture.simulation);
  fixture.first_result = expected;
  fixture.second_result = &fixture.second_target;

  const OpaqueWord result = run_probe(fixture, &fixture.simulation);
  static_cast<void>(result);
  assert(result == 0u);
  assert(fixture.call_count == 2);
  assert(fixture.arguments[0] == 8u);
  assert(fixture.arguments[1] == 7u);
}

void test_pair_write_and_stack_cleanup() {
  Fixture fixture{};
  current_fixture = &fixture;
  OpaquePairDestination destination{};
  destination.word_00 = 0x11111111u;
  destination.word_04 = 0x22222222u;
  destination.word_0c = 0x33333333u;
  destination.guard_14 = 0x44444444u;

  std::uintptr_t before = 0;
  std::uintptr_t after = 0;
  const OpaqueWord result =
      pair_stack_check(&destination, 0x89abcdefu, 0xfedcba98u, &before, &after);
  static_cast<void>(result);

  assert(before == after);
  assert(result == 0x89abcdefu);
  assert(destination.word_00 == 0x11111111u);
  assert(destination.word_04 == 0x22222222u);
  assert(destination.word_08 == 0x89abcdefu);
  assert(destination.word_0c == 0x33333333u);
  assert(destination.word_10 == 0xfedcba98u);
  assert(destination.guard_14 == 0x44444444u);
}

void test_field_write_order_and_result() {
  Fixture fixture{};
  fixture.receiver.word_00 = 0x11111111u;
  fixture.receiver.word_04 = 0x22222222u;
  fixture.receiver.word_08 = 0x33333333u;
  fixture.pending_value = 0x89abcdefu;
  fixture.prior_word_08 = fixture.receiver.word_08;
  fixture.port_result = 0xfedcba98u;
  current_fixture = &fixture;
  set_opaque_word_port(opaque_word_port);

  std::uintptr_t before = 0;
  std::uintptr_t after = 0;
  field_stack_check(&fixture.receiver, fixture.pending_value, &before, &after);

  assert(before == after);
  assert(fixture.receiver.word_00 == 0x11111111u);
  assert(fixture.receiver.word_04 == 0x89abcdefu);
  assert(fixture.receiver.word_08 == 0xfedcba98u);
  assert(fixture.port_call_count == 1);
}

void test_field_write_zero_result() {
  Fixture fixture{};
  fixture.receiver.word_08 = 0xffffffffu;
  fixture.pending_value = 0x76543210u;
  fixture.prior_word_08 = fixture.receiver.word_08;
  fixture.port_result = 0;
  current_fixture = &fixture;
  set_opaque_word_port(opaque_word_port);

  image_write_fields_00fd9460(&fixture.receiver, fixture.pending_value);

  assert(fixture.receiver.word_04 == 0x76543210u);
  assert(fixture.receiver.word_08 == 0u);
  assert(fixture.port_call_count == 1);
}

}

int run_all() {
  test_default_opaque_word_port();
  test_terrain_non_null_match();
  test_terrain_null_sentinel();
  test_terrain_first_mismatch_short_circuits();
  test_terrain_second_mismatch();
  test_pair_write_and_stack_cleanup();
  test_field_write_order_and_result();
  test_field_write_zero_result();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_terrain_image_wave9::run_all();
}

#undef PKG_TEST_NAKED
#undef PKG_TEST_THISCALL
