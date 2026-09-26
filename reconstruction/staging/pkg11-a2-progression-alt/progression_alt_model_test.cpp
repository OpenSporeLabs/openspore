#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "progression_alt.hpp"

#if defined(_MSC_VER)
#define PKG11_A2_TEST_THISCALL __thiscall
#else
#define PKG11_A2_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::pkg11_a2_progression_alt;

int failures = 0;

void expect(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void write_word(void* base, std::size_t offset, Word value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + offset, &value, sizeof(value));
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

enum class MissionCallKind : std::uint8_t {
  get_simulator_system,
  initialize_subsystem,
  populate_manager_state,
  get_registry,
  prepare_registry,
  build_registry_entry,
  register_fixed_identifiers,
  get_noun_manager,
  project_nouns,
  dispatch_projection_entry,
};

struct MissionCall {
  MissionCallKind kind;
  Opaque receiver = 0;
  Opaque value = 0;
  Word key = 0;
  std::size_t offset = 0;
  Opaque word0 = 0;
  Opaque word1 = 0;
  Opaque word2 = 0;
  Opaque word3 = 0;
  Opaque word4 = 0;
  Opaque manager = 0;

  bool operator==(const MissionCall& other) const {
    return kind == other.kind && receiver == other.receiver &&
           value == other.value && key == other.key && offset == other.offset &&
           word0 == other.word0 && word1 == other.word1 &&
           word2 == other.word2 && word3 == other.word3 &&
           word4 == other.word4 && manager == other.manager;
  }
};

std::vector<MissionCall> mission_calls;
std::vector<Opaque> registry_values;
std::size_t registry_index = 0;
MissionManagerWire g_mission_manager{};
Opaque simulator_system_word = 0x1000;
Opaque noun_manager_word = 0x3000;
Opaque projection_entries[3]{};
MissionProjectionVectorWire projection_result{};

Opaque get_simulator_system() {
  mission_calls.push_back({MissionCallKind::get_simulator_system});
  return simulator_system_word;
}

void PKG11_A2_TEST_THISCALL initialize_subsystem(Opaque system,
                                                 MissionManagerWire* manager) {
  mission_calls.push_back({MissionCallKind::initialize_subsystem, 0, system, 0,
                           0, 0, 0, 0, 0, 0, pointer_word(manager)});
}

void PKG11_A2_TEST_THISCALL
populate_manager_state(MissionManagerWire* manager) {
  mission_calls.push_back({MissionCallKind::populate_manager_state, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, pointer_word(manager)});
}

Opaque get_registry() {
  const Opaque value = registry_index < registry_values.size()
                           ? registry_values[registry_index]
                           : 0;
  ++registry_index;
  mission_calls.push_back({MissionCallKind::get_registry, 0, value});
  return value;
}

void PKG11_A2_TEST_THISCALL prepare_registry(Opaque registry) {
  mission_calls.push_back({MissionCallKind::prepare_registry, registry});
}

void PKG11_A2_TEST_THISCALL build_registry_entry(Opaque builder, void* field,
                                                 Word key) {
  auto* manager_bytes = reinterpret_cast<std::uint8_t*>(&g_mission_manager);
  auto* field_bytes = static_cast<std::uint8_t*>(field);
  mission_calls.push_back(
      {MissionCallKind::build_registry_entry, builder, 0, key,
       static_cast<std::size_t>(field_bytes - manager_bytes)});
}

void register_fixed_identifiers() {
  mission_calls.push_back({MissionCallKind::register_fixed_identifiers});
}

Opaque get_noun_manager() {
  mission_calls.push_back({MissionCallKind::get_noun_manager});
  return noun_manager_word;
}

const MissionProjectionVectorWire* PKG11_A2_TEST_THISCALL project_nouns(
    Opaque noun_manager, Opaque create_callback, Opaque clear_callback,
    Opaque add_callback, Opaque filter_callback, Word noun_id) {
  mission_calls.push_back({MissionCallKind::project_nouns, noun_manager, 0,
                           noun_id, 0, create_callback, clear_callback,
                           add_callback, filter_callback, noun_id});
  return &projection_result;
}

void PKG11_A2_TEST_THISCALL dispatch_projection_entry(Opaque entry) {
  mission_calls.push_back({MissionCallKind::dispatch_projection_entry, entry});
}

void test_mission_manager_operation_order_and_identity() {
  mission_calls.clear();
  registry_values = {0x2000, 0x2100, 0x2200, 0x2300};
  registry_index = 0;
  projection_entries[0] = 0xaaaa0001U;
  projection_entries[1] = 0U;
  projection_entries[2] = 0xaaaa0002U;
  projection_result = {
      0U, {0, 0, 0}, projection_entries, projection_entries + 3};
  const MissionManagerOperationPorts ports{
      get_simulator_system,
      initialize_subsystem,
      populate_manager_state,
      get_registry,
      prepare_registry,
      build_registry_entry,
      register_fixed_identifiers,
      get_noun_manager,
      project_nouns,
      dispatch_projection_entry,
  };
  set_mission_manager_operation_ports(&ports);

  mission_manager_operation_00fee310(&g_mission_manager);

  const std::vector<MissionCall> expected = {
      {MissionCallKind::get_simulator_system},
      {MissionCallKind::initialize_subsystem, 0, simulator_system_word, 0, 0, 0,
       0, 0, 0, 0, pointer_word(&g_mission_manager)},
      {MissionCallKind::populate_manager_state, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       pointer_word(&g_mission_manager)},
      {MissionCallKind::get_registry, 0, 0x2000U},
      {MissionCallKind::prepare_registry, 0x2000U},
      {MissionCallKind::get_registry, 0, 0x2100U},
      {MissionCallKind::build_registry_entry, 0x2100U, 0, 0x06b5005eU, 0x20},
      {MissionCallKind::get_registry, 0, 0x2200U},
      {MissionCallKind::build_registry_entry, 0x2200U, 0, 0x994d1f83U, 0x34},
      {MissionCallKind::get_registry, 0, 0x2300U},
      {MissionCallKind::build_registry_entry, 0x2300U, 0, 0xa07f6fd6U, 0x48},
      {MissionCallKind::register_fixed_identifiers},
      {MissionCallKind::get_noun_manager},
      {MissionCallKind::project_nouns, noun_manager_word, 0, 0x02aa5adaU, 0,
       0x00cd7d10U, 0x00d3d420U, 0x00fed010U, 0x00b1e520U, 0x02aa5adaU},
      {MissionCallKind::dispatch_projection_entry, 0xaaaa0001U},
      {MissionCallKind::dispatch_projection_entry, 0xaaaa0002U},
  };
  expect(mission_calls == expected);
  set_mission_manager_operation_ports(nullptr);
}

enum class TrackCallKind : std::uint8_t {
  get_noun_carrier,
  read_command_value,
  validate_command,
  get_current_empire,
  compute_and_update_score,
};

struct TrackCall {
  TrackCallKind kind;
  Opaque value = 0;
  Word identity = 0;

  bool operator==(const TrackCall& other) const {
    return kind == other.kind && value == other.value &&
           identity == other.identity;
  }
};

struct ScoreTarget {
  std::int32_t score;
  Word updates;
};

std::vector<TrackCall> track_calls;
std::vector<std::uint8_t> command_valid_results;
std::size_t command_result_index = 0;
Opaque current_empire_word = 0;

Opaque get_noun_carrier() {
  track_calls.push_back({TrackCallKind::get_noun_carrier});
  return 0x5000U;
}

Opaque PKG11_A2_TEST_THISCALL read_command_value(Opaque carrier) {
  track_calls.push_back({TrackCallKind::read_command_value, carrier});
  return 0x6000U;
}

bool PKG11_A2_TEST_THISCALL is_command_valid(Opaque command_value,
                                             Word identity) {
  track_calls.push_back(
      {TrackCallKind::validate_command, command_value, identity});
  const std::uint8_t result =
      command_result_index < command_valid_results.size()
          ? command_valid_results[command_result_index]
          : 0U;
  ++command_result_index;
  return result != 0U;
}

Opaque get_current_empire() {
  track_calls.push_back(
      {TrackCallKind::get_current_empire, current_empire_word});
  return current_empire_word;
}

std::int32_t PKG11_A2_TEST_THISCALL compute_and_update_score(Opaque target) {
  auto* score_target = reinterpret_cast<ScoreTarget*>(target);
  ++score_target->updates;
  track_calls.push_back({TrackCallKind::compute_and_update_score, target});
  return score_target->score;
}

MissionTrackPorts g_track_ports{get_noun_carrier, read_command_value,
                                is_command_valid, get_current_empire,
                                compute_and_update_score};

void initialize_track_fixture(MissionManagerWire& manager,
                              MissionTrackRecordStorage* entries,
                              std::size_t count, std::size_t first_index) {
  write_word(&manager, 0x34, pointer_word(entries + first_index));
  write_word(&manager, 0x38, pointer_word(entries + first_index + count));
}

void initialize_entry(MissionTrackRecordStorage& entry, Word* identities,
                      std::size_t count, Word threshold) {
  write_word(&entry, 0x04, threshold);
  write_word(&entry, 0x08, pointer_word(identities));
  write_word(
      &entry, 0x0c,
      pointer_word(identities == nullptr ? nullptr : identities + count));
}

void test_mission_track_record_one_fields_and_target_update() {
  MissionManagerWire manager{};
  MissionTrackRecordStorage entries[2]{};
  Word first[] = {0x10, 0x11};
  Word second[] = {0x21, 0x22, 0x23};
  initialize_entry(entries[0], first, 2, 99);
  initialize_entry(entries[1], second, 3, 5);
  initialize_track_fixture(manager, entries, 2, 0);
  ScoreTarget score_target{4, 0};
  const Opaque identity = pointer_word(&score_target);
  command_valid_results = {1, 1, 1};
  command_result_index = 0;
  current_empire_word = 0x7000U;
  track_calls.clear();
  set_mission_track_ports(&g_track_ports);

  expect(!mission_track_predicate_00febc90(&manager, 1, identity));
  expect(command_result_index == 3);
  expect(score_target.updates == 1);
  expect(track_calls == (std::vector<TrackCall>{
                            {TrackCallKind::get_noun_carrier},
                            {TrackCallKind::read_command_value, 0x5000U},
                            {TrackCallKind::validate_command, 0x6000U, 0x21},
                            {TrackCallKind::get_noun_carrier},
                            {TrackCallKind::read_command_value, 0x5000U},
                            {TrackCallKind::validate_command, 0x6000U, 0x22},
                            {TrackCallKind::get_noun_carrier},
                            {TrackCallKind::read_command_value, 0x5000U},
                            {TrackCallKind::validate_command, 0x6000U, 0x23},
                            {TrackCallKind::get_current_empire, 0x7000U},
                            {TrackCallKind::compute_and_update_score, identity},
                        }));

  score_target.score = 5;
  command_result_index = 0;
  track_calls.clear();
  expect(mission_track_predicate_00febc90(&manager, 1, identity));
  expect(score_target.updates == 2);
  set_mission_track_ports(nullptr);
}

void test_mission_track_rejects_invalid_record_identity() {
  MissionManagerWire manager{};
  MissionTrackRecordStorage entries[1]{};
  Word identities[] = {0x31, 0x32, 0x33};
  initialize_entry(entries[0], identities, 3, 0);
  initialize_track_fixture(manager, entries, 1, 0);
  ScoreTarget score_target{0, 0};
  command_valid_results = {1, 0, 1};
  command_result_index = 0;
  current_empire_word = 0x7000U;
  track_calls.clear();
  set_mission_track_ports(&g_track_ports);

  expect(!mission_track_predicate_00febc90(&manager, 0,
                                           pointer_word(&score_target)));
  expect(command_result_index == 2);
  expect(track_calls.size() == 6);
  expect(score_target.updates == 0);
  set_mission_track_ports(nullptr);
}

void test_mission_track_null_and_current_identity() {
  MissionManagerWire manager{};
  MissionTrackRecordStorage entries[1]{};
  Word identities[] = {0x41, 0x42};
  initialize_entry(entries[0], identities, 2, 0);
  initialize_track_fixture(manager, entries, 1, 0);
  command_valid_results = {1, 1};
  command_result_index = 0;
  current_empire_word = 0;
  track_calls.clear();
  set_mission_track_ports(&g_track_ports);

  expect(mission_track_predicate_00febc90(&manager, 0, 0));
  expect(track_calls.size() == 6);
  expect(command_result_index == 2);

  ScoreTarget score_target{0, 0};
  const Opaque identity = pointer_word(&score_target);
  current_empire_word = identity;
  command_result_index = 0;
  track_calls.clear();
  expect(mission_track_predicate_00febc90(&manager, 0, identity));
  expect(track_calls.size() == 7);
  expect(score_target.updates == 0);
  set_mission_track_ports(nullptr);
}

void test_mission_track_index_boundaries() {
  MissionManagerWire manager{};
  MissionTrackRecordStorage entries[4]{};
  Word identities[] = {0x51};
  for (MissionTrackRecordStorage& entry : entries) {
    initialize_entry(entry, identities, 1, 0);
  }
  initialize_track_fixture(manager, entries + 1, 3, 0);
  ScoreTarget score_target{0, 0};
  command_valid_results = {1};
  command_result_index = 0;
  current_empire_word = 0x7000U;
  set_mission_track_ports(&g_track_ports);

  track_calls.clear();
  expect(!mission_track_predicate_00febc90(&manager, 3, 0x8000U));
  expect(track_calls.empty());
  command_result_index = 0;
  expect(mission_track_predicate_00febc90(&manager, -1,
                                          pointer_word(&score_target)));
  expect(command_result_index == 1);
  set_mission_track_ports(nullptr);
}

enum class AchievementCallKind : std::uint8_t {
  lookup_or_create,
  forward_progress_key,
};

struct AchievementCall {
  AchievementCallKind kind;
  Word key = 0;
  Opaque manager = 0;

  bool operator==(const AchievementCall& other) const {
    return kind == other.kind && key == other.key && manager == other.manager;
  }
};

std::vector<AchievementCall> achievement_calls;
AchievementManagerWire g_achievement_manager{};
AchievementRecordWire g_achievement_record{};
Word lookup_key = 0;
bool forward_result = true;

AchievementRecordWire* PKG11_A2_TEST_THISCALL
lookup_or_create(AchievementManagerWire* manager, Word key) {
  achievement_calls.push_back(
      {AchievementCallKind::lookup_or_create, key, pointer_word(manager)});
  lookup_key = key;
  return &g_achievement_record;
}

bool PKG11_A2_TEST_THISCALL
forward_progress_key(AchievementManagerWire* manager, Word key) {
  achievement_calls.push_back(
      {AchievementCallKind::forward_progress_key, key, pointer_word(manager)});
  return forward_result;
}

AchievementProgressPorts g_achievement_ports{lookup_or_create,
                                             forward_progress_key};

AchievementRecordWire record_with(Word flags, Word progress, Word target) {
  return AchievementRecordWire{flags, progress, target};
}

void test_achievement_threshold_modes_and_boundaries() {
  const std::vector<AchievementRecordWire> records = {
      {0x001U, 4, 5}, {0x001U, 5, 5}, {0x001U, 6, 5}, {0x101U, 5, 5},
      {0x101U, 6, 5}, {0x201U, 5, 5}, {0x301U, 4, 5}, {0x401U, 5, 5},
      {0x501U, 5, 6}, {0x601U, 5, 5}, {0x701U, 5, 5},
  };
  const std::vector<std::uint8_t> expected = {
      0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0,
  };
  set_achievement_progress_ports(&g_achievement_ports);
  for (std::size_t index = 0; index < records.size(); ++index) {
    g_achievement_manager = AchievementManagerWire{};
    g_achievement_record = records[index];
    achievement_calls.clear();
    achievement_progress_update_00676e90(&g_achievement_manager, 0, index);
    expect(achievement_calls.size() == (expected[index] != 0U ? 2U : 1U));
  }
  set_achievement_progress_ports(nullptr);
}

void test_achievement_update_gate_order_and_identity() {
  g_achievement_manager = AchievementManagerWire{};
  g_achievement_record = record_with(0x101U, 5, 5);
  achievement_calls.clear();
  lookup_key = 0;
  set_achievement_progress_ports(&g_achievement_ports);

  g_achievement_manager.storage[0x24] = 1;
  achievement_progress_update_00676e90(&g_achievement_manager, 7, 0x1234U);
  expect(achievement_calls.empty());
  expect(g_achievement_record.progress == 5);

  g_achievement_manager.storage[0x24] = 0;
  achievement_progress_update_00676e90(&g_achievement_manager, 7, 0x1234U);
  expect(lookup_key == 0x1234U);
  expect(g_achievement_record.progress == 12);
  expect(achievement_calls ==
         (std::vector<AchievementCall>{
             {AchievementCallKind::lookup_or_create, 0x1234U,
              pointer_word(&g_achievement_manager)},
             {AchievementCallKind::forward_progress_key, 0x1234U,
              pointer_word(&g_achievement_manager)},
         }));

  achievement_calls.clear();
  g_achievement_record = record_with(0x100U, 12, 5);
  achievement_progress_update_00676e90(&g_achievement_manager, 1, 0x5678U);
  expect(g_achievement_record.progress == 13);
  expect(achievement_calls.size() == 1);
  expect(achievement_calls.front().kind ==
         AchievementCallKind::lookup_or_create);
  set_achievement_progress_ports(nullptr);
}

void test_achievement_increment_boundaries_and_forward_result() {
  g_achievement_manager = AchievementManagerWire{};
  g_achievement_record = record_with(0x101U, 1, 0);
  achievement_calls.clear();
  forward_result = false;
  set_achievement_progress_ports(&g_achievement_ports);

  achievement_progress_update_00676e90(&g_achievement_manager, 0xffffffffU, 0U);
  expect(g_achievement_record.progress == 0U);
  expect(achievement_calls.size() == 2);
  expect(achievement_calls.back().key == 0U);

  achievement_calls.clear();
  g_achievement_record = record_with(0x601U, 0, 0);
  achievement_progress_update_00676e90(&g_achievement_manager, 0, 0xffffffffU);
  expect(achievement_calls.size() == 1);
  set_achievement_progress_ports(nullptr);
  forward_result = true;
}

}

int main() {
  test_mission_manager_operation_order_and_identity();
  test_mission_track_record_one_fields_and_target_update();
  test_mission_track_rejects_invalid_record_identity();
  test_mission_track_null_and_current_identity();
  test_mission_track_index_boundaries();
  test_achievement_threshold_modes_and_boundaries();
  test_achievement_update_gate_order_and_identity();
  test_achievement_increment_boundaries_and_forward_result();
  return failures == 0 ? 0 : 1;
}

#undef PKG11_A2_TEST_THISCALL
