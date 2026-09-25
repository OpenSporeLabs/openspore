#include <cassert>
#include <cstdint>
#include <vector>

#include "space_player_cache.hpp"

namespace {

using openspore::reconstruction::pkg12_space::Empire;
using openspore::reconstruction::pkg12_space::EmpireLookup;
using openspore::reconstruction::pkg12_space::g_simulator_empire_lookup;
using openspore::reconstruction::pkg12_space::g_simulator_space_player_data;
using openspore::reconstruction::pkg12_space::kInvalidEmpireId;
using openspore::reconstruction::pkg12_space::pkg12_space_01021300;
using openspore::reconstruction::pkg12_space::refresh_player_empire_staged;
using openspore::reconstruction::pkg12_space::SpacePlayerCache;
using openspore::reconstruction::pkg12_space::StagedIdWord;

enum class EventKind : std::uint8_t {
  root,
  find,
  add_ref,
  release,
};

struct Event {
  EventKind kind;
  Empire* empire = nullptr;
  void* root = nullptr;
  std::int32_t empire_id = 0;
};

namespace model {

std::vector<Event> events;
void* root_result = nullptr;
std::int32_t expected_empire_id = 0;
Empire* lookup_result = nullptr;

void reset() {
  events.clear();
  root_result = nullptr;
  expected_empire_id = 0;
  lookup_result = nullptr;
}

}

void* get_root(StagedIdWord staged_id) {
  assert(staged_id.value == model::expected_empire_id);
  model::events.push_back(
      Event{EventKind::root, nullptr, model::root_result, staged_id.value});
  return model::root_result;
}

Empire* __thiscall find_empire(void* root, StagedIdWord staged_id) {
  assert(root == model::root_result);
  assert(staged_id.value == model::expected_empire_id);
  model::events.push_back(
      Event{EventKind::find, model::lookup_result, root, staged_id.value});
  return model::lookup_result;
}

void __thiscall add_ref(Empire* empire) {
  model::events.push_back(Event{EventKind::add_ref, empire, nullptr, 0});
}

void __thiscall release(Empire* empire) {
  model::events.push_back(Event{EventKind::release, empire, nullptr, 0});
}

Empire make_empire(std::int32_t identity) {
  Empire empire{};
  empire.add_ref = add_ref;
  empire.release = release;
  empire.identity = identity;
  return empire;
}

EmpireLookup make_lookup() { return EmpireLookup{get_root, find_empire}; }

void test_invalid_empire_id_preserves_old_cache() {
  Empire old_empire = make_empire(7);
  SpacePlayerCache cache{};
  cache.empire_id = kInvalidEmpireId;
  cache.cached_empire = &old_empire;
  model::reset();
  model::root_result = reinterpret_cast<void*>(0x1000);
  model::expected_empire_id = kInvalidEmpireId;
  model::lookup_result = &old_empire;

  assert(refresh_player_empire_staged(cache, make_lookup()) == nullptr);
  assert(cache.cached_empire == &old_empire);
  assert(model::events.empty());
}

void test_identity_hit_is_borrowed_noop() {
  Empire old_empire = make_empire(42);
  SpacePlayerCache cache{};
  cache.empire_id = 42;
  cache.cached_empire = &old_empire;
  model::reset();
  model::root_result = reinterpret_cast<void*>(0x1000);
  model::expected_empire_id = 42;
  model::lookup_result = nullptr;

  assert(refresh_player_empire_staged(cache, make_lookup()) == &old_empire);
  assert(cache.cached_empire == &old_empire);
  assert(model::events.empty());
}

void test_distinct_refresh_addref_store_release() {
  Empire old_empire = make_empire(1);
  Empire new_empire = make_empire(2);
  SpacePlayerCache cache{};
  cache.empire_id = 2;
  cache.cached_empire = &old_empire;
  model::reset();
  model::root_result = reinterpret_cast<void*>(0x1000);
  model::expected_empire_id = 2;
  model::lookup_result = &new_empire;

  assert(refresh_player_empire_staged(cache, make_lookup()) == &new_empire);
  assert(cache.cached_empire == &new_empire);
  assert(model::events.size() == 4);
  assert(model::events[0].kind == EventKind::root);
  assert(model::events[0].root == model::root_result);
  assert(model::events[0].empire_id == 2);
  assert(model::events[1].kind == EventKind::find);
  assert(model::events[1].root == model::root_result);
  assert(model::events[1].empire_id == 2);
  assert(model::events[1].empire == &new_empire);
  assert(model::events[2].kind == EventKind::add_ref);
  assert(model::events[2].empire == &new_empire);
  assert(model::events[3].kind == EventKind::release);
  assert(model::events[3].empire == &old_empire);
}

void test_equal_pointer_refresh_is_noop() {
  Empire old_empire = make_empire(1);
  SpacePlayerCache cache{};
  cache.empire_id = 2;
  cache.cached_empire = &old_empire;
  model::reset();
  model::root_result = reinterpret_cast<void*>(0x1000);
  model::expected_empire_id = 2;
  model::lookup_result = &old_empire;

  assert(refresh_player_empire_staged(cache, make_lookup()) == &old_empire);
  assert(cache.cached_empire == &old_empire);
  assert(model::events.size() == 2);
  assert(model::events[0].kind == EventKind::root);
  assert(model::events[0].empire_id == 2);
  assert(model::events[1].kind == EventKind::find);
  assert(model::events[1].empire_id == 2);
  assert(model::events[1].empire == &old_empire);
}

void test_null_lookup_releases_old_cache() {
  Empire old_empire = make_empire(1);
  SpacePlayerCache cache{};
  cache.empire_id = 2;
  cache.cached_empire = &old_empire;
  model::reset();
  model::root_result = reinterpret_cast<void*>(0x1000);
  model::expected_empire_id = 2;
  model::lookup_result = nullptr;

  assert(refresh_player_empire_staged(cache, make_lookup()) == nullptr);
  assert(cache.cached_empire == nullptr);
  assert(model::events.size() == 3);
  assert(model::events[0].kind == EventKind::root);
  assert(model::events[0].empire_id == 2);
  assert(model::events[1].kind == EventKind::find);
  assert(model::events[1].empire_id == 2);
  assert(model::events[1].empire == nullptr);
  assert(model::events[2].kind == EventKind::release);
  assert(model::events[2].empire == &old_empire);
}

void test_empty_cache_stores_addrefed_new_empire() {
  Empire new_empire = make_empire(2);
  SpacePlayerCache cache{};
  cache.empire_id = 2;
  model::reset();
  model::root_result = reinterpret_cast<void*>(0x1000);
  model::expected_empire_id = 2;
  model::lookup_result = &new_empire;

  assert(refresh_player_empire_staged(cache, make_lookup()) == &new_empire);
  assert(cache.cached_empire == &new_empire);
  assert(model::events.size() == 3);
  assert(model::events[0].kind == EventKind::root);
  assert(model::events[0].empire_id == 2);
  assert(model::events[1].kind == EventKind::find);
  assert(model::events[1].empire_id == 2);
  assert(model::events[2].kind == EventKind::add_ref);
  assert(model::events[2].empire == &new_empire);
}

void test_empty_cache_null_lookup() {
  SpacePlayerCache cache{};
  cache.empire_id = 2;
  model::reset();
  model::root_result = reinterpret_cast<void*>(0x1000);
  model::expected_empire_id = 2;
  model::lookup_result = nullptr;

  assert(refresh_player_empire_staged(cache, make_lookup()) == nullptr);
  assert(cache.cached_empire == nullptr);
  assert(model::events.size() == 2);
  assert(model::events[0].kind == EventKind::root);
  assert(model::events[0].empire_id == 2);
  assert(model::events[1].kind == EventKind::find);
  assert(model::events[1].empire_id == 2);
}

void test_zero_argument_wrapper_propagates_staged_id() {
  Empire new_empire = make_empire(7);
  SpacePlayerCache cache{};
  cache.empire_id = 7;
  EmpireLookup lookup = make_lookup();
  model::reset();
  model::root_result = reinterpret_cast<void*>(0x1000);
  model::expected_empire_id = 7;
  model::lookup_result = &new_empire;
  g_simulator_space_player_data = &cache;
  g_simulator_empire_lookup = &lookup;

  assert(pkg12_space_01021300() == &new_empire);
  assert(cache.cached_empire == &new_empire);
  assert(model::events.size() == 3);
  assert(model::events[0].kind == EventKind::root);
  assert(model::events[0].empire_id == 7);
  assert(model::events[1].kind == EventKind::find);
  assert(model::events[1].empire_id == 7);
  assert(model::events[1].empire == &new_empire);
  assert(model::events[2].kind == EventKind::add_ref);

  g_simulator_space_player_data = nullptr;
  g_simulator_empire_lookup = nullptr;
}

}

int main() {
  test_invalid_empire_id_preserves_old_cache();
  test_identity_hit_is_borrowed_noop();
  test_distinct_refresh_addref_store_release();
  test_equal_pointer_refresh_is_noop();
  test_null_lookup_releases_old_cache();
  test_empty_cache_stores_addrefed_new_empire();
  test_empty_cache_null_lookup();
  test_zero_argument_wrapper_propagates_staged_id();
}
