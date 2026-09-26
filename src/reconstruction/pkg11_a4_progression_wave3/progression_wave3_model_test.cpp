#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <limits>
#include <vector>

#include "progression_wave3.hpp"

#if defined(_MSC_VER)
#define PKG11_A4_TEST_THISCALL __thiscall
#else
#define PKG11_A4_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::pkg11_a4_progression_wave3;

int failures = 0;

enum class CallKind : std::uint8_t {
  find_status,
  find_configured,
  status_operator_bracket,
  append_unlocked,
  remove_unlocked,
};

struct Call {
  CallKind kind;
  Opaque container;
  OpaqueKey key;

  bool operator==(const Call& other) const {
    return kind == other.kind && container == other.container &&
           key.instance_id == other.key.instance_id &&
           key.group_id == other.key.group_id;
  }
};

struct StatusEntry {
  OpaqueKey key;
  std::uint8_t flags;
};

struct Fixture {
  ProgressionManagerWire manager{};
  std::deque<StatusEntry> statuses;
  std::vector<OpaqueKey> configured;
  std::vector<OpaqueKey> unlocked;
  std::vector<Call> calls;
};

Fixture fixture;

void expect(bool condition) {
  if (!condition) {
    ++failures;
  }
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

Opaque status_container() {
  return pointer_word(fixture.manager.storage + kStatusContainerOffset);
}

Opaque configured_container() {
  return pointer_word(fixture.manager.storage + kConfiguredContainerOffset);
}

Opaque unlocked_container() {
  return pointer_word(fixture.manager.storage + kUnlockedListOffset);
}

bool same_key(const OpaqueKey& lhs, const OpaqueKey& rhs) {
  return lhs.instance_id == rhs.instance_id && lhs.group_id == rhs.group_id;
}

bool same_keys(const std::vector<OpaqueKey>& lhs,
               const std::vector<OpaqueKey>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (std::size_t index = 0; index < lhs.size(); ++index) {
    if (!same_key(lhs[index], rhs[index])) {
      return false;
    }
  }
  return true;
}

void reset_fixture() {
  fixture.manager = ProgressionManagerWire{};
  fixture.statuses.clear();
  fixture.configured.clear();
  fixture.unlocked.clear();
  fixture.calls.clear();
}

Word points() {
  Word value = 0;
  std::memcpy(&value, fixture.manager.storage + kPointsOffset, sizeof(value));
  return value;
}

void set_points(Word value) {
  std::memcpy(fixture.manager.storage + kPointsOffset, &value, sizeof(value));
}

StatusEntry* find_status(const OpaqueKey& key) {
  for (StatusEntry& entry : fixture.statuses) {
    if (same_key(entry.key, key)) {
      return &entry;
    }
  }
  return nullptr;
}

bool PKG11_A4_TEST_THISCALL find_status_port(Opaque container,
                                             const OpaqueKey* key,
                                             std::uint8_t* status) {
  fixture.calls.push_back({CallKind::find_status, container, *key});
  const StatusEntry* const entry = find_status(*key);
  if (entry == nullptr) {
    return false;
  }
  *status = entry->flags;
  return true;
}

bool PKG11_A4_TEST_THISCALL find_configured_port(Opaque container,
                                                 const OpaqueKey* key) {
  fixture.calls.push_back({CallKind::find_configured, container, *key});
  return std::any_of(
      fixture.configured.begin(), fixture.configured.end(),
      [key](const OpaqueKey& entry) { return same_key(entry, *key); });
}

std::uint8_t* PKG11_A4_TEST_THISCALL
status_operator_bracket_port(Opaque container, const OpaqueKey* key) {
  fixture.calls.push_back({CallKind::status_operator_bracket, container, *key});
  StatusEntry* entry = find_status(*key);
  if (entry == nullptr) {
    fixture.statuses.push_back({*key, 0});
    entry = &fixture.statuses.back();
  }
  return &entry->flags;
}

void PKG11_A4_TEST_THISCALL append_unlocked_port(Opaque container,
                                                 const OpaqueKey* key) {
  fixture.calls.push_back({CallKind::append_unlocked, container, *key});
  fixture.unlocked.push_back(*key);
}

void PKG11_A4_TEST_THISCALL remove_unlocked_port(Opaque container,
                                                 const OpaqueKey* key) {
  fixture.calls.push_back({CallKind::remove_unlocked, container, *key});
  fixture.unlocked.erase(
      std::remove_if(
          fixture.unlocked.begin(), fixture.unlocked.end(),
          [key](const OpaqueKey& entry) { return same_key(entry, *key); }),
      fixture.unlocked.end());
}

const ProgressionPorts g_ports{find_status_port, find_configured_port,
                               status_operator_bracket_port,
                               append_unlocked_port, remove_unlocked_port};

void test_status_and_configured_guards() {
  const OpaqueKey key{0x1111U, 0x2222U};
  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  fixture.statuses.push_back({key, kUnlockedMask});
  set_points(20U);
  set_progression_ports(&g_ports);

  expect(!collectable_unlock_00596da0(&fixture.manager, key.instance_id,
                                      key.group_id, 4));
  expect(points() == 20U);
  expect(fixture.calls ==
         (std::vector<Call>{{CallKind::find_status, status_container(), key}}));

  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  fixture.statuses.push_back({key, kNotUnlockableMask});
  expect(collectable_unlock_00596da0(&fixture.manager, key.instance_id,
                                     key.group_id, 0));
  expect(fixture.statuses.front().flags ==
         (kNotUnlockableMask | kUnlockStateMask));

  reset_fixture();
  fixture.configured.push_back(key);
  expect(collectable_unlock_00596da0(&fixture.manager, key.instance_id,
                                     key.group_id, 0));
  expect(fixture.calls ==
         (std::vector<Call>{
             {CallKind::find_status, status_container(), key},
             {CallKind::find_configured, configured_container(), key},
             {CallKind::status_operator_bracket, status_container(), key},
             {CallKind::append_unlocked, unlocked_container(), key},
         }));
  expect(fixture.statuses.size() == 1U);

  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 1U;
  expect(!collectable_unlock_00596da0(&fixture.manager, key.instance_id,
                                      key.group_id, 0));
  expect(fixture.calls ==
         (std::vector<Call>{
             {CallKind::find_status, status_container(), key},
             {CallKind::find_configured, configured_container(), key},
         }));
  expect(fixture.statuses.empty());
  set_progression_ports(nullptr);
}

void test_default_eligibility_and_missing_entry_creation() {
  const OpaqueKey key{0x3333U, 0x4444U};
  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  set_points(5U);
  set_progression_ports(&g_ports);

  expect(collectable_unlock_00596da0(&fixture.manager, key.instance_id,
                                     key.group_id, 2));
  expect(points() == 3U);
  expect(fixture.statuses.size() == 1U);
  expect(fixture.statuses.front().flags == kUnlockStateMask);
  expect(same_keys(fixture.unlocked, std::vector<OpaqueKey>{key}));
  expect(fixture.calls ==
         (std::vector<Call>{
             {CallKind::find_status, status_container(), key},
             {CallKind::find_configured, configured_container(), key},
             {CallKind::status_operator_bracket, status_container(), key},
             {CallKind::append_unlocked, unlocked_container(), key},
         }));
  set_progression_ports(nullptr);
}

void test_status_preservation_and_repeat() {
  const OpaqueKey first{0x5555U, 0x6666U};
  const OpaqueKey second{0x7777U, 0x8888U};
  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  fixture.statuses.push_back({first, 0xa4U});
  set_points(7U);
  set_progression_ports(&g_ports);

  expect(collectable_unlock_00596da0(&fixture.manager, first.instance_id,
                                     first.group_id, 3));
  expect(points() == 4U);
  expect(fixture.statuses.front().flags == 0xa7U);
  expect(same_keys(fixture.unlocked, std::vector<OpaqueKey>{first}));

  fixture.calls.clear();
  expect(!collectable_unlock_00596da0(&fixture.manager, first.instance_id,
                                      first.group_id, 2));
  expect(points() == 4U);
  expect(fixture.statuses.front().flags == 0xa7U);
  expect(same_keys(fixture.unlocked, std::vector<OpaqueKey>{first}));
  expect(fixture.calls == (std::vector<Call>{{CallKind::find_status,
                                              status_container(), first}}));

  fixture.statuses.push_back({second, 0x04U});
  fixture.calls.clear();
  expect(collectable_unlock_00596da0(&fixture.manager, second.instance_id,
                                     second.group_id, 1));
  expect(fixture.statuses.back().flags == 0x07U);
  expect(same_keys(fixture.unlocked, std::vector<OpaqueKey>{first, second}));
  set_progression_ports(nullptr);
}

void test_wrapping_subtraction_and_cost_edges() {
  const OpaqueKey key{0x9999U, 0xaaaaU};
  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  set_points(0x80000000U);
  set_progression_ports(&g_ports);
  expect(collectable_unlock_00596da0(&fixture.manager, key.instance_id,
                                     key.group_id, 1));
  expect(points() == 0x7fffffffU);
  expect(fixture.statuses.size() == 1U);

  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  set_points(5U);
  expect(collectable_unlock_00596da0(&fixture.manager, key.instance_id,
                                     key.group_id, -1));
  expect(points() == 6U);
  expect(fixture.statuses.size() == 1U);

  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  set_points(5U);
  expect(!collectable_unlock_00596da0(&fixture.manager, key.instance_id,
                                      key.group_id, 6));
  expect(points() == 5U);
  expect(fixture.statuses.empty());
  expect(fixture.unlocked.empty());

  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  set_points(0xffffffffU);
  expect(collectable_unlock_00596da0(&fixture.manager, key.instance_id,
                                     key.group_id, 0));
  expect(points() == 0xffffffffU);
  expect(fixture.statuses.size() == 1U);

  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  set_points(0U);
  expect(!collectable_unlock_00596da0(
      &fixture.manager, key.instance_id, key.group_id,
      std::numeric_limits<std::int32_t>::min()));
  expect(points() == 0U);
  expect(fixture.statuses.empty());
  expect(fixture.unlocked.empty());
  set_progression_ports(nullptr);
}

void test_lock_clears_only_unlock_bits_and_removes_every_match() {
  const OpaqueKey key{0xbbbbU, 0xccccU};
  const OpaqueKey other{0xddddU, 0xeeeeU};
  reset_fixture();
  fixture.statuses.push_back({key, 0xa7U});
  fixture.statuses.push_back({other, 0x03U});
  fixture.unlocked = {key, other, key};
  set_points(41U);
  set_progression_ports(&g_ports);

  expect(collectable_lock_00596e10(&fixture.manager, key.instance_id,
                                   key.group_id));
  expect(points() == 41U);
  expect(fixture.statuses.front().flags == 0xa4U);
  expect(same_keys(fixture.unlocked, std::vector<OpaqueKey>{other}));
  expect(fixture.calls ==
         (std::vector<Call>{
             {CallKind::status_operator_bracket, status_container(), key},
             {CallKind::remove_unlocked, unlocked_container(), key},
         }));

  const OpaqueKey missing{0xffffU, 0x1000U};
  reset_fixture();
  fixture.unlocked = {missing, missing};
  set_points(9U);
  expect(collectable_lock_00596e10(&fixture.manager, missing.instance_id,
                                   missing.group_id));
  expect(points() == 9U);
  expect(fixture.statuses.size() == 1U);
  expect(fixture.statuses.front().flags == 0U);
  expect(fixture.unlocked.empty());
  expect(collectable_lock_00596e10(&fixture.manager, missing.instance_id,
                                   missing.group_id));
  expect(points() == 9U);
  expect(fixture.statuses.front().flags == 0U);
  expect(fixture.unlocked.empty());
  expect(fixture.calls ==
         (std::vector<Call>{
             {CallKind::status_operator_bracket, status_container(), missing},
             {CallKind::remove_unlocked, unlocked_container(), missing},
             {CallKind::status_operator_bracket, status_container(), missing},
             {CallKind::remove_unlocked, unlocked_container(), missing},
         }));
  set_progression_ports(nullptr);
}

void test_unlock_keeps_points_status_and_list_separate() {
  const OpaqueKey first{0x1212U, 0x3434U};
  const OpaqueKey second{0x5656U, 0x7878U};
  reset_fixture();
  fixture.manager.storage[kDefaultEligibilityOffset] = 0U;
  set_points(100U);
  set_progression_ports(&g_ports);

  expect(collectable_unlock_00596da0(&fixture.manager, first.instance_id,
                                     first.group_id, 25));
  expect(points() == 75U);
  expect(fixture.statuses.size() == 1U);
  expect(same_keys(fixture.unlocked, std::vector<OpaqueKey>{first}));

  expect(collectable_unlock_00596da0(&fixture.manager, second.instance_id,
                                     second.group_id, 0));
  expect(points() == 75U);
  expect(fixture.statuses.size() == 2U);
  expect(fixture.statuses.front().flags == 0x03U);
  expect(fixture.statuses.back().flags == 0x03U);
  expect(same_keys(fixture.unlocked, std::vector<OpaqueKey>{first, second}));

  expect(collectable_lock_00596e10(&fixture.manager, first.instance_id,
                                   first.group_id));
  expect(points() == 75U);
  expect(fixture.statuses.front().flags == 0U);
  expect(same_keys(fixture.unlocked, std::vector<OpaqueKey>{second}));
  set_progression_ports(nullptr);
}

}

int main() {
  test_status_and_configured_guards();
  test_default_eligibility_and_missing_entry_creation();
  test_status_preservation_and_repeat();
  test_wrapping_subtraction_and_cost_edges();
  test_lock_clears_only_unlock_bits_and_removes_every_match();
  test_unlock_keeps_points_status_and_list_separate();
  return failures == 0 ? 0 : 1;
}

#undef PKG11_A4_TEST_THISCALL
