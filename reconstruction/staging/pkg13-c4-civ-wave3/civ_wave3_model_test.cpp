#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "civ_wave3.hpp"

#if defined(_MSC_VER)
#define PKG13_C4_TEST_THISCALL __thiscall
#else
#define PKG13_C4_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::pkg13_c4_civ_wave3;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::uint32_t load_u32(const void* base, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

std::int32_t load_i32(const void* base, std::size_t offset) {
  std::int32_t value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

std::uint8_t load_u8(const void* base, std::size_t offset) {
  return *(static_cast<const std::uint8_t*>(base) + offset);
}

void store_u32(void* base, std::size_t offset, std::uint32_t value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + offset, &value, sizeof(value));
}

void store_i32(void* base, std::size_t offset, std::int32_t value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + offset, &value, sizeof(value));
}

void store_u8(void* base, std::size_t offset, std::uint8_t value) {
  *(static_cast<std::uint8_t*>(base) + offset) = value;
}

void store_pointer(void* base, std::size_t offset, const void* pointer) {
  store_u32(
      base, offset,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer)));
}

OpaqueCultureCandidate* load_culture(void* base, std::size_t offset) {
  return reinterpret_cast<OpaqueCultureCandidate*>(
      static_cast<std::uintptr_t>(load_u32(base, offset)));
}

void* load_pointer(const void* base, std::size_t offset) {
  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(load_u32(base, offset)));
}

std::uint32_t word_of(const void* pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

std::vector<std::string> trace;
OpaqueCity city;
OpaqueCityRoot city_root;
OpaqueCityBuilding city_buildings[kSlotCount];
OpaqueCityData city_data[kSlotCount];
OpaqueLiveStateContext live_context;
OpaqueLiveState live_states[kSlotCount];
OpaqueCity* expected_city = nullptr;
OpaqueCityRoot* city_root_result = nullptr;
bool city_building_present[kSlotCount]{};
bool city_data_filter_value[kSlotCount]{};
std::int32_t city_data_state[kSlotCount]{};
std::uint32_t city_data_id[kSlotCount]{};
std::uint8_t city_adjacency[kSlotCount * kSlotCount]{};
std::uint8_t city_data_marked[kSlotCount]{};
bool live_present[kSlotCount]{};
std::uint32_t live_type[kSlotCount]{};
std::uint32_t live_slot[kSlotCount]{};
std::uint8_t live_adjacency[kSlotCount * kSlotCount]{};
int city_commit_count = 0;
int city_mark_count = 0;
float notified_effectiveness = 0.0f;
std::uint32_t notified_update_word = 0;
OpaqueLiveStateContext* notified_context = nullptr;

std::size_t city_data_index(const OpaqueCityData* data) {
  for (std::size_t index = 0; index < kSlotCount; ++index) {
    if (data == &city_data[index]) {
      return index;
    }
  }
  return kSlotCount;
}

OpaqueCity* city_lookup_receiver() {
  return reinterpret_cast<OpaqueCity*>(city.bytes.data() + 0x3ec);
}

OpaqueCityData* city_data_receiver(OpaqueCityData* data) {
  return reinterpret_cast<OpaqueCityData*>(data->bytes.data() + 0x120);
}

OpaqueCityData* city_data_from_receiver(OpaqueCityData* receiver) {
  for (std::size_t index = 0; index < kSlotCount; ++index) {
    if (receiver == city_data_receiver(&city_data[index])) {
      return &city_data[index];
    }
  }
  return nullptr;
}

OpaqueCityRoot* PKG13_C4_TEST_THISCALL get_city_root(OpaqueCity* receiver) {
  check(receiver == expected_city);
  return city_root_result;
}

OpaqueCityBuilding* PKG13_C4_TEST_THISCALL
get_city_building(OpaqueCity* receiver, std::uint32_t slot) {
  check(receiver == city_lookup_receiver());
  check(slot < kSlotCount);
  return city_building_present[slot] ? &city_buildings[slot] : nullptr;
}

OpaqueCityData* PKG13_C4_TEST_THISCALL
get_city_data(OpaqueCityBuilding* building) {
  for (std::size_t index = 0; index < kSlotCount; ++index) {
    if (building == &city_buildings[index] && city_building_present[index]) {
      return &city_data[index];
    }
  }
  return nullptr;
}

std::int32_t PKG13_C4_TEST_THISCALL get_city_data_state(OpaqueCityData* data) {
  OpaqueCityData* const original = city_data_from_receiver(data);
  check(original != nullptr);
  return city_data_state[city_data_index(original)];
}

bool PKG13_C4_TEST_THISCALL city_data_filter(OpaqueCityData* data) {
  OpaqueCityData* const original = city_data_from_receiver(data);
  check(original != nullptr);
  return city_data_filter_value[city_data_index(original)];
}

std::uint32_t PKG13_C4_TEST_THISCALL
get_city_building_id(OpaqueCityData* data) {
  return city_data_id[city_data_index(data)];
}

std::uint8_t PKG13_C4_TEST_THISCALL get_city_adjacency(OpaqueCityRoot* root,
                                                       std::uint32_t slot,
                                                       std::uint32_t neighbor) {
  check(root == &city_root);
  return city_adjacency[slot * kSlotCount + neighbor];
}

OpaqueLiveState* PKG13_C4_TEST_THISCALL
get_live_state(OpaqueLiveStateContext* receiver, std::uint32_t index) {
  check(receiver == &live_context);
  return live_present[index] ? &live_states[index] : nullptr;
}

std::uint8_t PKG13_C4_TEST_THISCALL
get_live_adjacency(OpaqueLiveStateContext* receiver, std::uint32_t slot,
                   std::uint32_t neighbor) {
  check(receiver == &live_context);
  return live_adjacency[slot * kSlotCount + neighbor];
}

void PKG13_C4_TEST_THISCALL mark_city_data(OpaqueCityData* data,
                                           std::uint8_t value) {
  const std::size_t index = city_data_index(data);
  check(index < kSlotCount);
  city_data_marked[index] = value;
  ++city_mark_count;
}

void PKG13_C4_TEST_THISCALL commit_city(OpaqueCity* receiver) {
  check(receiver == &city);
  ++city_commit_count;
}

void PKG13_C4_TEST_THISCALL notify_live_state(OpaqueLiveStateContext* receiver,
                                              float effectiveness,
                                              std::uint32_t update_word) {
  check(receiver == &live_context);
  notified_context = receiver;
  notified_effectiveness = effectiveness;
  notified_update_word = update_word;
}

void install_city_ports() {
  g_city_update_ports = {};
  g_city_update_ports.get_city_root = get_city_root;
  g_city_update_ports.get_city_building = get_city_building;
  g_city_update_ports.get_city_data = get_city_data;
  g_city_update_ports.get_city_data_state = get_city_data_state;
  g_city_update_ports.city_data_filter = city_data_filter;
  g_city_update_ports.get_city_building_id = get_city_building_id;
  g_city_update_ports.get_city_adjacency = get_city_adjacency;
  g_city_update_ports.get_live_state = get_live_state;
  g_city_update_ports.get_live_adjacency = get_live_adjacency;
  g_city_update_ports.mark_city_data = mark_city_data;
  g_city_update_ports.commit_city = commit_city;
  g_city_update_ports.notify_live_state = notify_live_state;
}

void reset_city_fixture() {
  city.bytes.fill(0);
  city_root.bytes.fill(0);
  live_context.bytes.fill(0);
  expected_city = &city;
  city_root_result = &city_root;
  for (std::size_t index = 0; index < kSlotCount; ++index) {
    city_buildings[index].bytes.fill(0);
    city_data[index].bytes.fill(0);
    live_states[index].bytes.fill(0);
    city_building_present[index] = false;
    city_data_filter_value[index] = false;
    city_data_state[index] = 0;
    city_data_id[index] = 0;
    city_data_marked[index] = 0;
    live_present[index] = false;
    live_type[index] = 0;
    live_slot[index] = static_cast<std::uint32_t>(index);
  }
  std::memset(city_adjacency, 0, sizeof(city_adjacency));
  std::memset(live_adjacency, 0, sizeof(live_adjacency));
  city_commit_count = 0;
  city_mark_count = 0;
  notified_effectiveness = 0.0f;
  notified_update_word = 0;
  notified_context = nullptr;
  install_city_ports();
}

void configure_city_slot(std::size_t slot, std::uint32_t id) {
  check(slot < kSlotCount);
  city_building_present[slot] = true;
  city_data_id[slot] = id;
  store_i32(&city_data[slot], 0x290, 0);
}

void configure_live_slot(std::size_t index, std::size_t slot,
                         std::uint32_t id) {
  check(index < kSlotCount && slot < kSlotCount);
  live_present[index] = true;
  live_type[index] = id;
  live_slot[index] = static_cast<std::uint32_t>(slot);
  store_i32(&live_states[index], 0x20, 0);
  store_i32(&live_states[index], 0x2c, 1);
  store_u32(&live_states[index], 0x30, static_cast<std::uint32_t>(slot));
  store_u32(&live_states[index], 0x34, id);
}

void test_city_root_guard() {
  reset_city_fixture();
  city_root_result = nullptr;
  city_building_economy_update_00be2440(&city, nullptr, 7);
  check(city_commit_count == 0);
  check(city_mark_count == 0);
}

void test_live_adjacency_effectiveness_and_live_writes() {
  reset_city_fixture();
  configure_live_slot(0, 0, 0x018ea1ebu);
  configure_live_slot(1, 1, 0x01a56abau);
  configure_live_slot(2, 2, 0x018ea2ccu);
  live_adjacency[1 * kSlotCount + 0] = 1;
  live_adjacency[2 * kSlotCount + 0] = 1;

  city_building_economy_update_00be2440(nullptr, &live_context, 0x1234u);

  check(load_u8(&live_states[0], 0x24) == 1);
  check(load_u8(&live_states[1], 0x24) == 1);
  check(load_u8(&live_states[2], 0x24) == 1);
  check(load_u32(&live_states[1], 0x28) == 0);
  check(load_u32(&live_states[2], 0x28) == 0);
  check(load_i32(&live_context, 0x2c) == 400);
  check(notified_context == &live_context);
  check(notified_update_word == 0x1234u);
  check(notified_effectiveness == 60.0f);
  check(city_mark_count == 0);
  check(city_commit_count == 0);
}

void test_city_data_and_city_totals() {
  reset_city_fixture();
  configure_city_slot(0, 0x018ea1ebu);
  configure_city_slot(1, 0x01a56abau);
  configure_city_slot(2, 0x018ea2ccu);
  city_adjacency[1 * kSlotCount + 0] = 1;
  city_adjacency[2 * kSlotCount + 0] = 1;

  city_building_economy_update_00be2440(&city, nullptr, 0x55u);

  check(city_data_marked[0] == 1);
  check(city_data_marked[1] == 1);
  check(city_data_marked[2] == 1);
  check(load_u32(&city_data[0], 0x28c) == 0);
  check(load_u32(&city_data[1], 0x28c) == 0);
  check(load_u32(&city_data[1], 0x294) == 0);
  check(load_u32(&city_data[1], 0x298) == 2);
  check(load_u32(&city_data[1], 0x29c) == 0);
  check(load_u32(&city_data[2], 0x294) == 400);
  check(load_u32(&city_data[2], 0x298) == 0);
  check(load_u32(&city_data[2], 0x29c) == 1);
  check(load_u32(&city, 0x664) == 400);
  check(load_u32(&city, 0x668) == 2);
  check(load_u32(&city, 0x66c) == 1);
  check(load_u32(&city, 0x678) == 400);
  check(notified_context == nullptr);
  check(city_commit_count == 1);
}

void test_effectiveness_upper_and_lower_clamp() {
  reset_city_fixture();
  configure_live_slot(0, 0, 0x018ea1ebu);
  for (std::size_t slot = 1; slot <= 5; ++slot) {
    configure_live_slot(slot, slot, 0x01a56abau);
    live_adjacency[slot * kSlotCount] = 1;
  }
  city_building_economy_update_00be2440(nullptr, &live_context, 0);
  check(notified_effectiveness == 100.0f);

  reset_city_fixture();
  configure_live_slot(0, 0, 0x018ea1ebu);
  for (std::size_t slot = 1; slot <= 6; ++slot) {
    configure_live_slot(slot, slot, 0x018ea2ccu);
    live_adjacency[slot * kSlotCount] = 1;
  }
  city_building_economy_update_00be2440(nullptr, &live_context, 0);
  check(notified_effectiveness == 0.0f);
}

OpaqueCultureSelection culture;
OpaqueCulturePlayer culture_player;

OpaqueCultureSelection* culture_context() {
  return reinterpret_cast<OpaqueCultureSelection*>(culture.bytes.data() +
                                                   0x1c8);
}
OpaqueCultureCandidate candidates[2];
OpaqueCultureCity culture_cities[3];
CultureCandidateVtable candidate_vtables[2];
CultureCandidateRangeStorage candidate_range_storage{};
CultureCityRangeStorage city_range_storage{};
OpaqueCultureCandidate* candidate_scan[2];
std::size_t candidate_scan_count = 0;
OpaqueCultureCity* city_scan[3];
std::size_t city_scan_count = 0;
OpaqueCultureCity* selection_city_scan[1];
std::size_t selection_city_scan_count = 1;
OpaqueCulturePlayer* player_result = nullptr;
OpaqueCultureCandidate* expected_add_ref = nullptr;
OpaqueCultureCandidate* expected_release = nullptr;
OpaqueCultureCandidate* expected_old_pointer = nullptr;
OpaqueCultureCandidate* expected_new_pointer = nullptr;
OpaqueCultureCity* current_match_city = nullptr;
OpaqueCultureCandidate* current_match_culture = nullptr;
OpaqueCultureCity* position_match_city = nullptr;
OpaqueCultureCandidate* position_match_culture = nullptr;
std::int32_t phase_value = 1;
std::int32_t current_score_value = 0;
std::int32_t selection_score_value = 0;
bool candidate_available_value = false;
std::uint64_t wait_value = 0x2711u;
bool primary_value = true;
bool secondary_value = true;
float candidate_a_score = 5.0f;
float candidate_b_score = 10.0f;
CultureVectorResult candidate_result_vectors[2] = {
    CultureVectorResult{0x111, 0.0f, 0.0f},
    CultureVectorResult{0x112, 0.0f, 0.0f},
};
CultureVectorResult* expected_commit_candidate_result = nullptr;
std::int32_t expected_commit_mode = 0;
OpaqueCultureCity* expected_commit_city = nullptr;
float city_score_value = 3.0f;
int root_call_count = 0;
int input_manager_call_count = 0;
int vector_result_call_count = 0;
int candidate_result_call_count = 0;
int city_context_call_count = 0;
int finish_count = 0;
int city_match_call_count = 0;
int try_commit_count = 0;
std::int32_t try_commit_mode = -1;

int candidate_index_from_receiver(OpaqueCultureCandidate* receiver) {
  for (std::size_t index = 0; index < 2; ++index) {
    OpaqueCultureCandidate* const owner =
        reinterpret_cast<OpaqueCultureCandidate*>(
            candidates[index].bytes.data() + 0x34);
    if (receiver == owner) {
      return static_cast<int>(index);
    }
  }
  return -1;
}

void PKG13_C4_TEST_THISCALL
candidate_add_ref(OpaqueCultureCandidate* candidate) {
  check(candidate == expected_add_ref);
  check(load_culture(&culture, 0x468) == expected_old_pointer);
  trace.emplace_back("culture-add-ref");
}

void PKG13_C4_TEST_THISCALL
candidate_release(OpaqueCultureCandidate* candidate) {
  check(candidate == expected_release);
  check(load_culture(&culture, 0x468) == expected_new_pointer);
  trace.emplace_back("culture-release");
}

void* current_root() {
  ++root_call_count;
  return &culture_player;
}

OpaqueCulturePlayer* PKG13_C4_TEST_THISCALL current_player(void* root) {
  check(root == &culture_player);
  return player_result;
}

void* PKG13_C4_TEST_THISCALL phase_source(void* root) {
  check(root == &culture_player);
  return root;
}

std::int32_t PKG13_C4_TEST_THISCALL phase_score(void* owner) {
  check(owner == &culture_player);
  return phase_value;
}

std::int32_t PKG13_C4_TEST_THISCALL current_score(OpaqueCulturePlayer* player) {
  check(player == player_result);
  return current_score_value;
}

std::int32_t PKG13_C4_TEST_THISCALL
selection_score(OpaqueCultureSelection* selection) {
  check(selection == &culture);
  return selection_score_value;
}

bool PKG13_C4_TEST_THISCALL
candidate_available(OpaqueCultureCandidate* candidate) {
  check(candidate == &candidates[0] || candidate == &candidates[1]);
  return candidate_available_value;
}

const CultureVectorResult* candidate_result(OpaqueCultureCandidate* receiver,
                                            std::uint32_t filter_argument,
                                            std::uint32_t switch_mode,
                                            bool include_switch_mode) {
  const int index = candidate_index_from_receiver(receiver);
  check(index == 0 || index == 1);
  if (include_switch_mode) {
    check(filter_argument == 0u);
    check(switch_mode == 0u || switch_mode == 1u);
  } else {
    check(filter_argument == 0xffffffffu);
    check(switch_mode == 0u);
  }
  ++candidate_result_call_count;
  return &candidate_result_vectors[index];
}

void* input_manager() {
  ++input_manager_call_count;
  return &culture_player;
}

std::uint16_t PKG13_C4_TEST_THISCALL
vector_result(void* input, const CultureVectorResult* result) {
  check(input == &culture_player);
  check(result == &candidate_result_vectors[0] ||
        result == &candidate_result_vectors[1]);
  ++vector_result_call_count;
  return static_cast<std::uint16_t>(result->x);
}

std::uint32_t PKG13_C4_TEST_THISCALL
city_context(OpaqueCultureCity* city_pointer) {
  check(city_pointer == expected_commit_city);
  ++city_context_call_count;
  return word_of(city_pointer);
}

std::uint64_t PKG13_C4_TEST_THISCALL
selection_wait(OpaqueCultureSelection* selection) {
  check(selection == culture_context());
  return wait_value;
}

CultureCandidateRangeStorage* PKG13_C4_TEST_THISCALL enumerate_candidates(
    void* root, std::uint32_t arg1, std::uint32_t arg2, std::uint32_t arg3,
    std::uint32_t arg4, std::uint32_t arg5) {
  check(root == &culture_player);
  check(arg1 == 0x00cd7d10u);
  check(arg2 == 0x00d3d420u);
  check(arg3 == 0x00ae5ea0u);
  check(arg4 == 0x00b1e500u);
  check(arg5 == 0x0403df5cu);
  candidate_range_storage.opaque_0 = 0;
  candidate_range_storage.begin = candidate_scan;
  candidate_range_storage.end = candidate_scan + candidate_scan_count;
  return &candidate_range_storage;
}

bool PKG13_C4_TEST_THISCALL candidate_primary(
    OpaqueCultureSelection* selection, const CultureVectorResult* candidate,
    std::uint16_t argument) {
  check(selection == &culture);
  check(candidate == &candidate_result_vectors[0] ||
        candidate == &candidate_result_vectors[1]);
  check(argument == static_cast<std::uint16_t>(candidate->x));
  return primary_value;
}

bool PKG13_C4_TEST_THISCALL candidate_secondary(
    OpaqueCultureSelection* selection, const CultureVectorResult* candidate,
    std::uint32_t argument) {
  check(selection == &culture);
  check(candidate == &candidate_result_vectors[0] ||
        candidate == &candidate_result_vectors[1]);
  check(argument == 0xffffffffu);
  return secondary_value;
}

CultureCityRangeStorage* PKG13_C4_TEST_THISCALL enumerate_cities(void* root) {
  check(root == &culture_player);
  city_range_storage.begin = city_scan;
  city_range_storage.end = city_scan + city_scan_count;
  return &city_range_storage;
}

bool city_is_self(OpaqueCultureCity* city_pointer,
                  OpaqueCultureSelection* selection) {
  check(selection == &culture);
  return city_pointer == nullptr;
}

float candidate_score(OpaqueCultureSelection* selection,
                      OpaqueCultureCity* reference,
                      OpaqueCultureCandidate* candidate,
                      std::uint32_t multiplier, std::uint32_t matching_cities) {
  check(selection == &culture);
  check(reference == &culture_cities[0]);
  check(candidate == &candidates[0] || candidate == &candidates[1]);
  check(multiplier == 100u || multiplier == 200u);
  check(matching_cities < 3u);
  return candidate == &candidates[0] ? candidate_a_score : candidate_b_score;
}

bool city_matches_current(OpaqueCultureSelection* selection,
                          OpaqueCultureCity* city_pointer,
                          OpaqueCultureCandidate* candidate) {
  ++city_match_call_count;
  check(selection == &culture);
  return city_pointer == current_match_city &&
         candidate == current_match_culture;
}

bool city_matches_position(OpaqueCultureSelection* selection,
                           OpaqueCultureCity* city_pointer,
                           OpaqueCultureCandidate* candidate) {
  ++city_match_call_count;
  check(selection == &culture);
  return city_pointer == position_match_city &&
         candidate == position_match_culture;
}

float city_score(OpaqueCultureSelection* selection,
                 OpaqueCultureCity* city_pointer,
                 OpaqueCultureCandidate* candidate) {
  check(selection == &culture);
  check(city_pointer != nullptr);
  check(candidate != nullptr);
  return city_score_value;
}

bool PKG13_C4_TEST_THISCALL try_commit(OpaqueCultureSelection* selection,
                                       std::uint32_t first,
                                       const CultureVectorResult* candidate,
                                       std::uint16_t normalized,
                                       std::uint32_t city_result) {
  check(selection == &culture);
  check(first == 0u);
  check(candidate == expected_commit_candidate_result);
  check(normalized == static_cast<std::uint16_t>(candidate->x));
  check(city_result == word_of(expected_commit_city));
  try_commit_count++;
  try_commit_mode = expected_commit_mode;
  trace.emplace_back("culture-try-commit");
  return true;
}

void PKG13_C4_TEST_THISCALL finish(OpaqueCultureSelection* selection) {
  check(selection == culture_context());
  ++finish_count;
  trace.emplace_back("culture-finish");
}

void install_culture_ports() {
  g_culture_wave3_ports = {};
  g_culture_wave3_ports.current_root = current_root;
  g_culture_wave3_ports.current_player = current_player;
  g_culture_wave3_ports.phase_source = phase_source;
  g_culture_wave3_ports.phase_score = phase_score;
  g_culture_wave3_ports.current_score = current_score;
  g_culture_wave3_ports.selection_score = selection_score;
  g_culture_wave3_ports.candidate_available = candidate_available;
  g_culture_wave3_ports.candidate_result = candidate_result;
  g_culture_wave3_ports.input_manager = input_manager;
  g_culture_wave3_ports.vector_result = vector_result;
  g_culture_wave3_ports.city_context = city_context;
  g_culture_wave3_ports.selection_wait = selection_wait;
  g_culture_wave3_ports.enumerate_candidates = enumerate_candidates;
  g_culture_wave3_ports.candidate_primary = candidate_primary;
  g_culture_wave3_ports.candidate_secondary = candidate_secondary;
  g_culture_wave3_ports.enumerate_cities = enumerate_cities;
  g_culture_wave3_ports.city_is_self = city_is_self;
  g_culture_wave3_ports.candidate_score = candidate_score;
  g_culture_wave3_ports.city_matches_current = city_matches_current;
  g_culture_wave3_ports.city_matches_position = city_matches_position;
  g_culture_wave3_ports.city_score = city_score;
  g_culture_wave3_ports.try_commit = try_commit;
  g_culture_wave3_ports.finish = finish;
}

void reset_culture_fixture() {
  trace.clear();
  culture.bytes.fill(0);
  culture_player.bytes.fill(0);
  for (std::size_t index = 0; index < 2; ++index) {
    candidates[index].bytes.fill(0);
    candidate_vtables[index].add_ref = candidate_add_ref;
    candidate_vtables[index].release = candidate_release;
    store_pointer(&candidates[index], 0, &candidate_vtables[index]);
  }
  for (OpaqueCultureCity& city_value : culture_cities) {
    city_value.bytes.fill(0);
  }
  candidate_scan[0] = &candidates[0];
  candidate_scan[1] = &candidates[1];
  candidate_scan_count = 2;
  city_scan_count = 0;
  selection_city_scan[0] = &culture_cities[0];
  selection_city_scan_count = 1;
  store_pointer(&culture, 0x9c, selection_city_scan);
  store_pointer(&culture, 0xa0,
                selection_city_scan + selection_city_scan_count);
  store_i32(&culture, 0x298, 1);
  store_u8(&culture, 0x93, 0);
  player_result = nullptr;
  expected_add_ref = nullptr;
  expected_release = nullptr;
  expected_old_pointer = nullptr;
  expected_new_pointer = nullptr;
  current_match_city = nullptr;
  current_match_culture = nullptr;
  position_match_city = nullptr;
  position_match_culture = nullptr;
  phase_value = 1;
  current_score_value = 0;
  selection_score_value = 0;
  candidate_available_value = false;
  wait_value = 0x2711u;
  primary_value = true;
  secondary_value = true;
  candidate_a_score = 5.0f;
  candidate_b_score = 10.0f;
  candidate_result_vectors[0] = CultureVectorResult{0x111, 0.0f, 0.0f};
  candidate_result_vectors[1] = CultureVectorResult{0x112, 0.0f, 0.0f};
  expected_commit_candidate_result = nullptr;
  expected_commit_mode = 0;
  expected_commit_city = nullptr;
  city_score_value = 3.0f;
  root_call_count = 0;
  input_manager_call_count = 0;
  vector_result_call_count = 0;
  candidate_result_call_count = 0;
  city_context_call_count = 0;
  finish_count = 0;
  city_match_call_count = 0;
  try_commit_count = 0;
  try_commit_mode = -1;
  install_culture_ports();
}

void test_culture_empty_guard() {
  reset_culture_fixture();
  store_pointer(&culture, 0xa0, load_pointer(&culture, 0x9c));
  culture_selection_00bf9820(&culture);
  check(root_call_count == 0);
  check(finish_count == 0);
}

void test_culture_null_element_guard() {
  reset_culture_fixture();
  selection_city_scan[0] = nullptr;
  culture_selection_00bf9820(&culture);
  check(root_call_count == 0);
  check(finish_count == 0);
}

void test_culture_score_guard_releases_old() {
  reset_culture_fixture();
  store_pointer(&culture, 0x468, &candidates[0]);
  player_result = &culture_player;
  phase_value = 0;
  current_score_value = 1;
  selection_score_value = 2;
  expected_release = &candidates[0];
  expected_new_pointer = nullptr;
  culture_selection_00bf9820(&culture);
  check(load_culture(&culture, 0x468) == nullptr);
  check(trace.size() == 2);
  check(trace[0] == "culture-release");
  check(trace[1] == "culture-finish");
}

void test_culture_wait_guard() {
  reset_culture_fixture();
  wait_value = 0x2710u;
  culture_selection_00bf9820(&culture);
  check(root_call_count == 1);
  check(finish_count == 0);
  check(candidate_scan_count == 2);
}

void test_culture_null_selection_skips_city_loop() {
  reset_culture_fixture();
  primary_value = false;
  secondary_value = false;
  culture_selection_00bf9820(&culture);
  check(city_match_call_count == 0);
  check(try_commit_count == 0);
  check(finish_count == 1);
}

void test_culture_secondary_filter_is_direct() {
  reset_culture_fixture();
  store_i32(&culture, 0x298, 2);
  primary_value = false;
  secondary_value = true;
  current_match_city = &culture_cities[0];
  current_match_culture = &candidates[1];
  expected_add_ref = &candidates[1];
  expected_old_pointer = nullptr;
  expected_new_pointer = &candidates[1];
  expected_commit_candidate_result = &candidate_result_vectors[1];
  expected_commit_mode = 0;
  expected_commit_city = &culture_cities[0];
  culture_selection_00bf9820(&culture);
  check(load_culture(&culture, 0x468) == &candidates[1]);
  check(candidate_result_call_count == 5);
  check(input_manager_call_count == 3);
  check(vector_result_call_count == 3);
  check(try_commit_count == 1);
}

void test_culture_candidate_score_and_commit() {
  reset_culture_fixture();
  city_scan[0] = &culture_cities[0];
  city_scan_count = 1;
  store_pointer(&culture_cities[0], 0x468, &candidates[0]);
  store_u8(&culture_cities[0], 0x8a, 1);
  current_match_city = &culture_cities[0];
  current_match_culture = &candidates[1];
  expected_add_ref = &candidates[1];
  expected_old_pointer = nullptr;
  expected_new_pointer = &candidates[1];
  expected_commit_candidate_result = &candidate_result_vectors[1];
  expected_commit_mode = 0;
  expected_commit_city = &culture_cities[0];
  culture_selection_00bf9820(&culture);
  check(load_culture(&culture, 0x468) == &candidates[1]);
  check(try_commit_count == 1);
  check(try_commit_mode == 0);
  check(candidate_result_call_count == 3);
  check(input_manager_call_count == 3);
  check(city_context_call_count == 1);
  check(trace.size() == 3);
  check(trace[0] == "culture-try-commit");
  check(trace[1] == "culture-add-ref");
  check(trace[2] == "culture-finish");
}

void test_culture_tie_keeps_first_candidate() {
  reset_culture_fixture();
  candidate_b_score = 5.0f;
  current_match_city = &culture_cities[0];
  current_match_culture = &candidates[0];
  expected_add_ref = &candidates[0];
  expected_old_pointer = nullptr;
  expected_new_pointer = &candidates[0];
  expected_commit_candidate_result = &candidate_result_vectors[0];
  expected_commit_mode = 0;
  expected_commit_city = &culture_cities[0];
  culture_selection_00bf9820(&culture);
  check(load_culture(&culture, 0x468) == &candidates[0]);
  check(try_commit_count == 1);
}

void test_culture_replacement_order() {
  reset_culture_fixture();
  store_pointer(&culture, 0x468, &candidates[0]);
  city_scan[0] = &culture_cities[0];
  city_scan_count = 1;
  store_pointer(&culture_cities[0], 0x468, &candidates[1]);
  store_u8(&culture_cities[0], 0x8a, 1);
  current_match_city = &culture_cities[0];
  current_match_culture = &candidates[1];
  expected_add_ref = &candidates[1];
  expected_release = &candidates[0];
  expected_old_pointer = &candidates[0];
  expected_new_pointer = &candidates[1];
  expected_commit_candidate_result = &candidate_result_vectors[1];
  expected_commit_mode = 0;
  expected_commit_city = &culture_cities[0];
  culture_selection_00bf9820(&culture);
  check(load_culture(&culture, 0x468) == &candidates[1]);
  check(trace.size() == 4);
  check(trace[0] == "culture-try-commit");
  check(trace[1] == "culture-add-ref");
  check(trace[2] == "culture-release");
  check(trace[3] == "culture-finish");
}

void test_culture_same_candidate_has_no_refcalls() {
  reset_culture_fixture();
  candidate_b_score = 5.0f;
  store_pointer(&culture, 0x468, &candidates[0]);
  current_match_city = &culture_cities[0];
  current_match_culture = &candidates[0];
  expected_commit_candidate_result = &candidate_result_vectors[0];
  expected_commit_mode = 0;
  expected_commit_city = &culture_cities[0];
  culture_selection_00bf9820(&culture);
  check(load_culture(&culture, 0x468) == &candidates[0]);
  check(trace.size() == 2);
  check(trace[0] == "culture-try-commit");
  check(trace[1] == "culture-finish");
}

}

int main() {
  test_city_root_guard();
  test_live_adjacency_effectiveness_and_live_writes();
  test_city_data_and_city_totals();
  test_effectiveness_upper_and_lower_clamp();
  test_culture_empty_guard();
  test_culture_null_element_guard();
  test_culture_score_guard_releases_old();
  test_culture_wait_guard();
  test_culture_null_selection_skips_city_loop();
  test_culture_secondary_filter_is_direct();
  test_culture_candidate_score_and_commit();
  test_culture_tie_keeps_first_candidate();
  test_culture_replacement_order();
  test_culture_same_candidate_has_no_refcalls();
}

#undef PKG13_C4_TEST_THISCALL
