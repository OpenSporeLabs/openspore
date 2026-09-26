#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <string>
#include <type_traits>
#include <vector>

#include "resource_state_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_RSS_TEST_CDECL __cdecl
#define PKG_RSS_TEST_THISCALL __thiscall
#else
#define PKG_RSS_TEST_CDECL __attribute__((cdecl))
#define PKG_RSS_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_resource_state_safe_wave10 {
namespace {

using GetStateSignature =
    OpaqueRecordWrite*(PKG_RSS_TEST_THISCALL*)(OpaqueRecordWrite*, ReleaseFlag);
using DestroySignature = void(PKG_RSS_TEST_THISCALL*)(OpaqueRecordWrite*);
using UntrackSignature = void(PKG_RSS_TEST_CDECL*)(void*);

static_assert(std::is_same<decltype(&record_write_get_state_00e310c0),
                           GetStateSignature>::value,
              "00e310c0 takes this plus one stack word popped by RET 4");
static_assert(
    std::is_same<decltype(ResourceStateSafePorts::destroy_00e30f90),
                 DestroySignature>::value,
    "00e30f90 is a dependency port taking this and releasing nothing");
static_assert(
    std::is_same<decltype(ResourceStateSafePorts::untrack_00f47380),
                 UntrackSignature>::value,
    "00f47380 is a dependency port that releases nothing and takes the "
    "receiver on the stack");
static_assert(sizeof(ReleaseFlag) == 1 && kReleaseFlagMask == 0x01,
              "the release flag is a single byte narrowed by the low bit");
static_assert(sizeof(void*) == 4, "x86-32 pointers are four bytes");

std::vector<std::string> events;

void check(bool condition) {
  if (condition) {
    return;
  }
  std::fputs("check failed", stderr);
  for (const std::string& event : events) {
    std::fprintf(stderr, " %s", event.c_str());
  }
  std::fputc('\n', stderr);
  std::abort();
}

void expect(std::initializer_list<const char*> expected) {
  check(events.size() == expected.size());
  std::size_t index = 0;
  for (const char* value : expected) {
    check(events[index] == value);
    ++index;
  }
}

constexpr std::size_t kReceiverBytes = 32;

std::uint8_t receiver_storage[kReceiverBytes];

OpaqueRecordWrite* receiver() {
  return reinterpret_cast<OpaqueRecordWrite*>(receiver_storage);
}

struct PortState {
  Word destroy_calls = 0;
  Word untrack_calls = 0;
  const void* last_destroy_receiver = nullptr;
  const void* last_untrack_target = nullptr;
};

PortState state;

void PKG_RSS_TEST_THISCALL destroy_port(OpaqueRecordWrite* target) {
  events.emplace_back("destroy");
  ++state.destroy_calls;
  state.last_destroy_receiver = target;
}

void PKG_RSS_TEST_CDECL untrack_port(void* target) {
  events.emplace_back("untrack");
  ++state.untrack_calls;
  state.last_untrack_target = target;
}

void install_ports() {
  state = PortState{};
  events.clear();
  ResourceStateSafePorts injected{};
  injected.destroy_00e30f90 = &destroy_port;
  injected.untrack_00f47380 = &untrack_port;
  resource_state_safe_set_ports(injected);
  events.clear();
}

void seed_receiver() {
  for (std::size_t index = 0; index < kReceiverBytes; ++index) {
    receiver_storage[index] = static_cast<std::uint8_t>(0x30 + index);
  }
}

void test_release_flag_zero_skips_untrack() {
  install_ports();
  seed_receiver();
  check(record_write_get_state_00e310c0(receiver(), 0x00) == receiver());
  expect({"destroy"});
  check(state.destroy_calls == 1);
  check(state.untrack_calls == 0);
}

void test_release_flag_low_bit_releases() {
  install_ports();
  seed_receiver();
  check(record_write_get_state_00e310c0(receiver(), 0x01) == receiver());
  expect({"destroy", "untrack"});
  check(state.destroy_calls == 1);
  check(state.untrack_calls == 1);
}

void test_release_flag_high_bits_are_ignored() {
  install_ports();
  const ReleaseFlag cases[] = {0x02, 0x04, 0x40, 0x80, 0x7e, 0xfc, 0xfe, 0xaa};
  for (const ReleaseFlag flag : cases) {
    seed_receiver();
    events.clear();
    check(record_write_get_state_00e310c0(receiver(), flag) == receiver());
    expect({"destroy"});
    check(state.untrack_calls == 0);
  }
}

void test_release_flag_low_bit_with_high_bits_releases() {
  install_ports();
  const ReleaseFlag cases[] = {0x81, 0xff, 0x03, 0xf1};
  for (const ReleaseFlag flag : cases) {
    seed_receiver();
    events.clear();
    check(record_write_get_state_00e310c0(receiver(), flag) == receiver());
    expect({"destroy", "untrack"});
  }
}

void test_destroy_precedes_untrack() {
  install_ports();
  seed_receiver();
  check(record_write_get_state_00e310c0(receiver(), 0x01) == receiver());
  expect({"destroy", "untrack"});
  check(state.destroy_calls == 1);
  check(state.untrack_calls == 1);
}

void test_receiver_returned_unchanged() {
  install_ports();
  seed_receiver();
  OpaqueRecordWrite* const expected = receiver();
  OpaqueRecordWrite* const returned =
      record_write_get_state_00e310c0(expected, 0x00);
  check(returned == expected);
  check(static_cast<const void*>(returned) == receiver_storage);
  events.clear();
  check(record_write_get_state_00e310c0(expected, 0x01) == expected);
  check(state.destroy_calls == 2);
  check(state.untrack_calls == 1);
}

void test_ports_receive_receiver_pointer() {
  install_ports();
  seed_receiver();
  check(record_write_get_state_00e310c0(receiver(), 0x01) == receiver());
  expect({"destroy", "untrack"});
  check(state.last_destroy_receiver == receiver());
  check(state.last_untrack_target == receiver());
}

void test_receiver_storage_untouched() {
  install_ports();
  seed_receiver();
  std::uint8_t before[kReceiverBytes];
  std::memcpy(before, receiver_storage, sizeof(before));
  check(record_write_get_state_00e310c0(receiver(), 0x00) == receiver());
  check(std::memcmp(receiver_storage, before, sizeof(before)) == 0);
  check(record_write_get_state_00e310c0(receiver(), 0x01) == receiver());
  check(std::memcmp(receiver_storage, before, sizeof(before)) == 0);
  expect({"destroy", "destroy", "untrack"});
}

std::uint32_t stack_probe_result = 0;

void PKG_RSS_TEST_CDECL get_state_stack_probe(OpaqueRecordWrite* target,
                                              ReleaseFlag flag, Word guard_low,
                                              Word guard_high) {
  std::uint32_t* const canary =
      static_cast<std::uint32_t*>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  const GetStateSignature get_state = &record_write_get_state_00e310c0;
  check(get_state(target, flag) == target);
  check(canary[0] == 0xc0dec0deu);
  check(canary[1] == 0xfeedfaceu);
  check(guard_low == 0x11223344u);
  check(guard_high == 0x55667788u);
  stack_probe_result = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
}

void test_stack_discipline() {
  install_ports();
  seed_receiver();
  get_state_stack_probe(receiver(), 0x01, 0x11223344u, 0x55667788u);
  check(stack_probe_result ==
        (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u));
  expect({"destroy", "untrack"});
  get_state_stack_probe(receiver(), 0x00, 0x11223344u, 0x55667788u);
  expect({"destroy", "untrack", "destroy"});
  check(state.destroy_calls == 2);
  check(state.untrack_calls == 1);
}

void test_null_ports_fall_back_to_inert() {
  ResourceStateSafePorts empty{};
  check(empty.destroy_00e30f90 == nullptr);
  check(empty.untrack_00f47380 == nullptr);
  state = PortState{};
  resource_state_safe_set_ports(empty);
  events.clear();
  seed_receiver();
  check(record_write_get_state_00e310c0(receiver(), 0x01) == receiver());
  check(state.destroy_calls == 0);
  check(state.untrack_calls == 0);
  expect({});
}

void test_reset_ports_restores_inert() {
  install_ports();
  seed_receiver();
  check(record_write_get_state_00e310c0(receiver(), 0x01) == receiver());
  expect({"destroy", "untrack"});
  state = PortState{};
  resource_state_safe_reset_ports();
  events.clear();
  check(record_write_get_state_00e310c0(receiver(), 0x01) == receiver());
  check(state.destroy_calls == 0);
  check(state.untrack_calls == 0);
  expect({});
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_resource_state_safe_wave10;
  test_release_flag_zero_skips_untrack();
  test_release_flag_low_bit_releases();
  test_release_flag_high_bits_are_ignored();
  test_release_flag_low_bit_with_high_bits_releases();
  test_destroy_precedes_untrack();
  test_receiver_returned_unchanged();
  test_ports_receive_receiver_pointer();
  test_receiver_storage_untouched();
  test_stack_discipline();
  test_null_ports_fall_back_to_inert();
  test_reset_ports_restores_inert();
  return 0;
}

#undef PKG_RSS_TEST_CDECL
#undef PKG_RSS_TEST_THISCALL
