#include "mission_progression.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

using namespace openspore::reconstruction::pkg11_a1_mission_progression;

int failures = 0;

void check(bool condition, int line) {
  if (!condition) {
    ++failures;
    std::cerr << "check failed at line " << line << "\n";
  }
}

#define expect(condition) check((condition), __LINE__)

std::vector<Word> badge_trace;
std::vector<MissionProjectionEntry> projection;
std::vector<Word> run_trace;
bool run_ready = true;

void badge_base(BadgeManagerModel* model) {
  badge_trace.push_back(1);
  model->wire.vtable0 = 0x00146155cU;
  model->wire.refcount = 0;
  model->wire.vtable1 = 0x001461538U;
  model->wire.base_flags[0] = 0;
  model->wire.base_flags[1] = 0;
  model->wire.base_flags[2] = 0;
  model->wire.base_flags[3] = 0;
}

void badge_register_points(BadgeManagerModel*) {
  badge_trace.push_back(2);
}

void badge_register_property(BadgeManagerModel*) {
  badge_trace.push_back(3);
}

void badge_release(BadgeManagerModel*, BadgeSource* source) {
  badge_trace.push_back(10U + source->key);
}

void badge_remove(BadgeManagerModel*, BadgeSource* source) {
  badge_trace.push_back(20U + source->key);
}

void badge_property(BadgeManagerModel*, const BadgeSource* source,
                    bool* has_instance, Word* instance_id, Word* property_type,
                    std::uint8_t* property_flags, std::uint8_t* property_value) {
  *has_instance = source->has_property && source->has_instance;
  *instance_id = source->instance_id;
  *property_type = source->property_type;
  *property_flags = source->property_flags;
  *property_value = source->property_value;
  badge_trace.push_back(30U + source->key);
}

void badge_event_create(BadgeManagerModel*, const BadgeSource* source,
                        Word, std::uint8_t* state) {
  *state = source->has_instance ? 1U : *state;
  badge_trace.push_back(40U + source->event_id);
}

void badge_event_lookup(BadgeManagerModel*, Word key) {
  badge_trace.push_back(50U + key);
}

void badge_event_advance(BadgeManagerModel*) {
  badge_trace.push_back(60);
}

void load_projection(MissionManagerWire*,
                     std::vector<MissionProjectionEntry>& output) {
  output = projection;
}

bool projection_matches(MissionManagerWire*, const MissionProjectionEntry& entry,
                        Word planet_id) {
  return entry.active && entry.planet_id == planet_id;
}

Word resolve_entry(MissionManagerWire*, const MissionProjectionEntry& entry,
                   bool* valid) {
  *valid = entry.valid;
  return entry.mission_id;
}

Word planet_from_mission(MissionManagerWire*, Word mission, bool* has_planet) {
  for (const MissionProjectionEntry& entry : projection) {
    if (entry.mission_id == mission) {
      *has_planet = entry.active;
      return entry.planet_id;
    }
  }
  *has_planet = false;
  return 0;
}

bool candidate_allowed(MissionManagerWire*, Word key) {
  return key != 30U && key != 0xffffffffU;
}

void run_enter(MissionManagerWire*, const MissionRunSeed* seed, Word, Word) {
  expect(seed != nullptr);
  expect(seed->value == 0x1234U);
  run_trace.push_back(1);
}

bool run_ready_check(MissionManagerWire*) {
  run_trace.push_back(2);
  return run_ready;
}

void run_initialize_1(MissionRunState*) {
  run_trace.push_back(3);
}

void run_initialize_2(MissionRunState*) {
  run_trace.push_back(5);
}

void run_collect(MissionManagerWire*, MissionRunState* state) {
  run_trace.push_back(4);
  state->source_ids.push_back(1);
  state->source_ids.push_back(2);
}

void run_build(MissionManagerWire*, MissionRunState* state) {
  run_trace.push_back(6);
  state->ordered_ids.clear();
  state->ordered_ids.push_back(11);
  state->ordered_ids.push_back(22);
}

Word run_resolve(MissionManagerWire*, Word id) {
  return id + 1000U;
}

bool run_set_state(MissionManagerWire*, Word value) {
  return value == 1U;
}

Word run_current(MissionManagerWire*) {
  return 1011U;
}

bool run_should_dispatch(MissionManagerWire*, Word, Word event_word) {
  expect(event_word == 0xabcdef01U);
  return true;
}

void run_dispatch(MissionRunState*, Word, Word) {}

void run_cleanup(MissionManagerWire*) {
  run_trace.push_back(7);
}

void test_badge_lifecycle_and_event_order() {
  badge_trace.clear();
  BadgeManagerModel model;
  model.sources = {
      BadgeSource{1U, 0U, false, true, 1U, 0U, 1U, 100U},
      BadgeSource{2U, 7U, true, true, 1U, 0x30U, 0U, 200U},
      BadgeSource{3U, 0U, false, false, 0U, 0U, 0U, 300U},
      BadgeSource{4U, 0U, false, true, 1U, 0U, 1U, 100U},
  };
  BadgeManagerPorts ports;
  ports.base_00b5b6c0 = badge_base;
  ports.register_00932e80 = badge_register_points;
  ports.register_006b5770 = badge_register_property;
  ports.release_00dd85c0 = badge_release;
  ports.remove_source = badge_remove;
  ports.property_lookup = badge_property;
  ports.event_create_00badea0 = badge_event_create;
  ports.event_lookup_00fe4300 = badge_event_lookup;
  ports.event_advance_00921580 = badge_event_advance;

  BadgeManagerWire* result = badge_manager_construct_00fe4fa0(model, ports);
  expect(result == &model.wire);
  expect(model.wire.vtable0 == 0x00149429cU);
  expect(model.wire.vtable1 == 0x001494278U);
  expect(model.wire.m_badges.anchor_left ==
         reinterpret_cast<Word>(&model.wire.m_badges.anchor_left));
  expect(model.wire.m_badge_map.anchor_left ==
         reinterpret_cast<Word>(&model.wire.m_badge_map.anchor_left));
  expect(model.wire.m_stage_map.anchor_left ==
         reinterpret_cast<Word>(&model.wire.m_stage_map.anchor_left));
  expect(model.wire.m_event_counts.anchor_left ==
         reinterpret_cast<Word>(&model.wire.m_event_counts.anchor_left));
  expect(model.wire.current_badge_card == 0U);
  expect(model.events.size() == 3U);
  expect(model.events[0].key == 100U);
  expect(model.events[0].state == 3U);
  expect(model.events[1].key == 200U);
  expect(model.events[1].state == 1U);
  expect(model.events[2].key == 300U);
  expect(model.events[2].state == 2U);
  expect(model.wire.m_event_counts.size == 3U);
  expect(model.source_release_order == std::vector<Word>({1U, 2U, 3U, 4U}));
  expect(badge_trace[0] == 1U);
  expect(badge_trace[1] == 2U);
  expect(badge_trace[2] == 3U);
  expect(std::find(badge_trace.begin(), badge_trace.end(), 11U) !=
         badge_trace.end());
  expect(std::find(badge_trace.begin(), badge_trace.end(), 21U) !=
         badge_trace.end());
  expect(std::find(badge_trace.begin(), badge_trace.end(), 31U) !=
         badge_trace.end());
  expect(std::find(badge_trace.begin(), badge_trace.end(), 50U + 100U) !=
         badge_trace.end());
  expect(std::find(badge_trace.begin(), badge_trace.end(), 40U + 100U) !=
         badge_trace.end());
  expect(std::find(badge_trace.begin(), badge_trace.end(), 40U + 200U) !=
         badge_trace.end());
  expect(std::find(badge_trace.begin(), badge_trace.end(), 40U + 300U) !=
         badge_trace.end());
}

void test_mission_metric_identity_and_invalid_projection() {
  projection = {
      MissionProjectionEntry{10U, 7U, true, true},
      MissionProjectionEntry{11U, 8U, true, true},
  };
  MissionProjectionPorts ports;
  ports.load_projection = load_projection;
  ports.entry_matches = projection_matches;
  const std::vector<PlanetMissionRef> recent = {
      PlanetMissionRef{4U, 40U},
      PlanetMissionRef{9U, 90U},
  };
  MissionManagerWire manager;
  const float indexed = mission_event_metric_00fedfe0(
      &manager, recent, 9U, ports);
  expect(std::fabs(indexed - 0.101F) < 0.00001F);
  const float projected = mission_event_metric_00fedfe0(
      &manager, recent, 0xffffffffU, ports);
  expect(std::fabs(projected - 1.0F) < 0.00001F);
  projection[0].active = false;
  projection[1].active = false;
  const float missing = mission_event_metric_00fedfe0(
      &manager, recent, 0xffffffffU, ports);
  expect(std::fabs(missing - 1.0F) < 0.00001F);
}

void test_mission_lookup_identity_gate() {
  projection = {
      MissionProjectionEntry{100U, 5U, true, true},
      MissionProjectionEntry{200U, 6U, true, true},
  };
  MissionLookupPorts ports;
  ports.resolve_entry = resolve_entry;
  ports.planet_from_mission = planet_from_mission;
  ports.projection = projection;
  MissionManagerWire manager;
  expect(mission_lookup_00fee220(&manager, 5U, ports) == 100U);
  expect(mission_lookup_00fee220(&manager, 6U, ports) == 200U);
  expect(mission_lookup_00fee220(&manager, 0xffffffffU, ports) == 0U);
  write_mission_manager_byte(&manager, 0x15, 1);
  expect(mission_lookup_00fee220(&manager, 0xffffffffU, ports) == 100U);
  ports.projection[0].valid = false;
  projection[0].valid = false;
  write_mission_manager_byte(&manager, 0x15, 0);
  expect(mission_lookup_00fee220(&manager, 5U, ports) == 0U);
}

void test_mission_selection_boundaries() {
  MissionManagerWire manager;
  MissionSelectionState state;
  MissionSelectionPorts ports;
  ports.candidate_allowed_00fee930 = candidate_allowed;
  expect(!mission_choose_00feebb0(&manager, state, ports));
  state.candidates = {10U, 20U, 30U, 0xffffffffU};
  state.status_nodes = {{10U, 1U}, {20U, 2U}};
  expect(mission_choose_00feebb0(&manager, state, ports));
  state.status_nodes = {{20U, 2U}};
  expect(mission_choose_00feebb0(&manager, state, ports));
  state.status_nodes = {{20U, 1U}, {30U, 1U}, {0xffffffffU, 1U}};
  expect(!mission_choose_00feebb0(&manager, state, ports));
}

void test_mission_manager_operation_order_and_propagation() {
  run_trace.clear();
  MissionManagerWire manager;
  MissionRunState state;
  MissionRunPorts ports;
  ports.enter_007c50b0 = run_enter;
  ports.ready_007c4fd0 = run_ready_check;
  ports.initialize_013ca260 = run_initialize_1;
  ports.initialize_013ca240 = run_initialize_2;
  ports.collect_00ffbe50 = run_collect;
  ports.build_order = run_build;
  ports.resolve_empire_00ba9370 = run_resolve;
  ports.set_state_01046fc0 = run_set_state;
  ports.current_empire_01021300 = run_current;
  ports.should_dispatch_00e18c70 = run_should_dispatch;
  ports.dispatch_00feb510 = run_dispatch;
  ports.cleanup_007c3c10 = run_cleanup;
  MissionRunSeed seed{0x1234U, 0x17U, 0x55U};

  mission_manager_operation_00feb770(&manager, 0x16U, &seed, 0xabcdef01U,
                                      state, ports);
  expect(run_trace.empty());
  run_ready = false;
  mission_manager_operation_00feb770(&manager, 0x17U, &seed, 0xabcdef01U,
                                      state, ports);
  expect(run_trace == std::vector<Word>({1U, 2U}));
  run_ready = true;
  run_trace.clear();
  mission_manager_operation_00feb770(&manager, 0x17U, &seed, 0xabcdef01U,
                                      state, ports);
  expect(run_trace == std::vector<Word>({1U, 2U, 3U, 4U, 5U, 6U, 7U}));
  expect(state.visited_ids == std::vector<Word>({11U, 22U}));
  expect(state.emitted_ids == std::vector<Word>({11U, 22U}));
  expect(state.initialization_flags == 3U);
  run_trace.clear();
  mission_manager_operation_00feb770(&manager, 0x17U, &seed, 0xabcdef01U,
                                      state, ports);
  expect(run_trace == std::vector<Word>({1U, 2U, 4U, 6U, 7U}));
}

}

int main() {
  test_badge_lifecycle_and_event_order();
  test_mission_metric_identity_and_invalid_projection();
  test_mission_lookup_identity_gate();
  test_mission_selection_boundaries();
  test_mission_manager_operation_order_and_propagation();
  if (failures != 0) {
    std::cerr << failures << " mission progression model checks failed\n";
    return 1;
  }
  std::cout << "mission progression model: PASS\n";
  return 0;
}
