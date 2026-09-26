#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "achievement_mission_wave2.hpp"

#if defined(_MSC_VER)
#define PKG11_A3_TEST_THISCALL __thiscall
#else
#define PKG11_A3_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::pkg11_a3_achievement_mission_wave2;

int failures = 0;

void expect(bool condition) {
  if (!condition) {
    ++failures;
  }
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

bool live_comparator_mode(const AchievementDefinitionWire* record) {
  const Word mode = (record->flags >> 8U) & 0x7U;
  const Word progress = record->progress_flags;
  const Word target = record->target;
  switch (mode) {
    case 0:
      return progress >= target;
    case 1:
      return target < progress;
    case 2:
      return progress == target;
    case 3:
      return progress < target;
    case 4:
      return progress <= target;
    case 5:
      return progress != target;
    default:
      return false;
  }
}

enum class CompletionCallKind : std::uint8_t {
  search_sorted_set,
  lookup_or_create,
  acquire_notifier,
  notify_completion,
  acquire_event_queue,
  construct_event_argument,
  post_completion_event,
  release_event_argument,
  persist_achievements,
};

struct CompletionCall {
  CompletionCallKind kind;
  Word key = 0;
  Word word0 = 0;
  Word word1 = 0;
  Word word2 = 0;
  Opaque receiver = 0;
  std::uint8_t tag = 0;

  bool operator==(const CompletionCall& other) const {
    return kind == other.kind && key == other.key && word0 == other.word0 &&
           word1 == other.word1 && word2 == other.word2 &&
           receiver == other.receiver && tag == other.tag;
  }
};

std::vector<CompletionCall> completion_calls;
AchievementManagerWire g_manager{};
AchievementSerializerWire g_serializer{};
Word sorted_set[4] = {0x10U, 0x20U, 0x30U, 0x40U};
Opaque search_result = 0;
Opaque notifier_object = 0;
Opaque queue_object = 0;
Opaque notifier_acquire_count = 0;
std::uint8_t inserted_status = 1U;
std::uint8_t constructed_flags = 0U;
std::int16_t constructed_type = 1;
std::uint16_t constructed_reserved = 1;
Word constructed_key = 0;
Opaque post_result = 0;
Opaque persist_count = 0;
Opaque release_count = 0;

Opaque search_sorted_set(Opaque begin, Opaque end, const Word* key,
                         std::uint8_t tag) {
  completion_calls.push_back(
      {CompletionCallKind::search_sorted_set, *key, begin, end, 0, 0, tag});
  return search_result;
}

const AchievementLookupResultWire* PKG11_A3_TEST_THISCALL lookup_or_create(
    Opaque container, AchievementLookupResultWire* out, const Word* key) {
  completion_calls.push_back({CompletionCallKind::lookup_or_create, *key,
                              container, pointer_word(out), 0, 0, 0});
  out->position = pointer_word(sorted_set);
  out->inserted = inserted_status;
  return out;
}

Opaque acquire_notifier() {
  ++notifier_acquire_count;
  completion_calls.push_back({CompletionCallKind::acquire_notifier});
  return notifier_object;
}

void PKG11_A3_TEST_THISCALL notify_completion(Opaque notifier, Word event,
                                              const Word* key, Opaque tail) {
  completion_calls.push_back({CompletionCallKind::notify_completion, *key,
                              event, tail, 0, notifier, 0});
}

Opaque acquire_event_queue() {
  completion_calls.push_back({CompletionCallKind::acquire_event_queue});
  return queue_object;
}

AchievementEventArgumentWire* PKG11_A3_TEST_THISCALL construct_event_argument(
    AchievementEventArgumentWire* destination, const Word* key) {
  completion_calls.push_back({CompletionCallKind::construct_event_argument,
                              *key, pointer_word(destination), 0, 0, 0, 0});
  constructed_key = *key;
  constructed_type = destination->type_id;
  constructed_reserved = destination->reserved;
  destination->flags = constructed_flags;
  return destination;
}

Opaque PKG11_A3_TEST_THISCALL
post_completion_event(Opaque queue, Opaque type_descriptor,
                      const AchievementEventArgumentWire* arguments) {
  completion_calls.push_back({CompletionCallKind::post_completion_event, 0, 0,
                              type_descriptor, arguments->flags, queue, 0});
  return post_result;
}

void PKG11_A3_TEST_THISCALL
release_event_argument(AchievementEventArgumentWire* arguments, Opaque tail) {
  ++release_count;
  completion_calls.push_back({CompletionCallKind::release_event_argument, 0,
                              tail, pointer_word(arguments), arguments->flags,
                              0, 0});
}

Opaque PKG11_A3_TEST_THISCALL
persist_achievements(AchievementManagerWire* manager) {
  ++persist_count;
  completion_calls.push_back({CompletionCallKind::persist_achievements, 0, 0, 0,
                              0, pointer_word(manager)});
  return 0U;
}

const AchievementCompletionPorts g_completion_ports{
    search_sorted_set,     lookup_or_create,       acquire_notifier,
    notify_completion,     acquire_event_queue,    construct_event_argument,
    post_completion_event, release_event_argument, persist_achievements,
};

void reset_completion_fixture() {
  g_manager = AchievementManagerWire{};
  g_serializer = AchievementSerializerWire{};
  g_serializer.achievement_set.begin = pointer_word(sorted_set);
  g_serializer.achievement_set.end =
      pointer_word(sorted_set + (sizeof(sorted_set) / sizeof(sorted_set[0])));
  g_serializer.achievement_set.tag = 0x5aU;
  g_manager.serializer = pointer_word(&g_serializer);
  g_manager.gate = 0U;
  search_result = pointer_word(sorted_set + 2);
  notifier_object = 0x9000U;
  queue_object = 0xa000U;
  notifier_acquire_count = 0;
  inserted_status = 1U;
  constructed_flags = 0U;
  constructed_type = 1;
  constructed_reserved = 1;
  constructed_key = 0U;
  post_result = 0U;
  persist_count = 0;
  release_count = 0;
  completion_calls.clear();
}

std::vector<CompletionCallKind> completion_kinds() {
  std::vector<CompletionCallKind> kinds;
  for (const CompletionCall& call : completion_calls) {
    kinds.push_back(call.kind);
  }
  return kinds;
}

void test_completion_missing_definition_notifies_and_forwards() {
  reset_completion_fixture();
  set_achievement_completion_ports(&g_completion_ports);
  const bool result =
      achievement_completion_boundary_00676710(&g_manager, 0x20U);

  expect(result);
  expect(completion_calls.size() == 8U);
  expect(completion_calls[0].kind == CompletionCallKind::search_sorted_set);
  expect(completion_calls[0].key == 0x20U);
  expect(completion_calls[0].word0 == pointer_word(sorted_set));
  expect(
      completion_calls[0].word1 ==
      pointer_word(sorted_set + (sizeof(sorted_set) / sizeof(sorted_set[0]))));
  expect(completion_calls[0].tag == 0x5aU);
  expect(completion_calls[1].kind == CompletionCallKind::lookup_or_create);
  expect(completion_calls[1].key == 0x20U);
  expect(completion_calls[1].word0 ==
         pointer_word(&g_serializer.achievement_set));
  expect(completion_calls[2].kind == CompletionCallKind::acquire_notifier);
  expect(completion_calls[3].kind == CompletionCallKind::notify_completion);
  expect(completion_calls[3].key == 0x20U);
  expect(completion_calls[3].word0 == kCompletionNotifyEvent);
  expect(completion_calls[3].word1 == kCompletionForwardedTail);
  expect(completion_calls[3].receiver == 0x9000U);
  expect(completion_calls[4].kind == CompletionCallKind::acquire_event_queue);
  expect(completion_calls[5].kind ==
         CompletionCallKind::construct_event_argument);
  expect(constructed_key == 0x20U);
  expect(constructed_type == 0);
  expect(constructed_reserved == 0U);
  expect(completion_calls[6].kind == CompletionCallKind::post_completion_event);
  expect(completion_calls[6].receiver == 0xa000U);
  expect(completion_calls[6].word1 == kCompletionPostType);
  expect(completion_calls[7].kind == CompletionCallKind::persist_achievements);
  expect(completion_calls[7].receiver == pointer_word(&g_manager));
  expect(persist_count == 1U);
  expect(release_count == 0U);
  set_achievement_completion_ports(nullptr);
}

void test_completion_present_definition_suppresses_everything() {
  reset_completion_fixture();
  inserted_status = 0U;
  set_achievement_completion_ports(&g_completion_ports);
  const bool result =
      achievement_completion_boundary_00676710(&g_manager, 0x20U);

  expect(!result);
  expect(completion_kinds() == (std::vector<CompletionCallKind>{
                                   CompletionCallKind::search_sorted_set,
                                   CompletionCallKind::lookup_or_create,
                               }));
  expect(notifier_acquire_count == 0);
  expect(persist_count == 0);
  expect(release_count == 0);
  set_achievement_completion_ports(nullptr);
}

void test_completion_search_hit_suppresses_notify() {
  reset_completion_fixture();
  search_result = pointer_word(sorted_set + 1);
  set_achievement_completion_ports(&g_completion_ports);
  const bool result =
      achievement_completion_boundary_00676710(&g_manager, 0x20U);

  expect(result);
  expect(completion_kinds() == (std::vector<CompletionCallKind>{
                                   CompletionCallKind::search_sorted_set,
                                   CompletionCallKind::lookup_or_create,
                                   CompletionCallKind::acquire_event_queue,
                                   CompletionCallKind::construct_event_argument,
                                   CompletionCallKind::post_completion_event,
                                   CompletionCallKind::persist_achievements,
                               }));
  expect(notifier_acquire_count == 0);
  set_achievement_completion_ports(nullptr);
}

void test_completion_search_slot_above_key_counts_as_missing() {
  reset_completion_fixture();
  search_result = pointer_word(sorted_set);
  set_achievement_completion_ports(&g_completion_ports);
  const bool result =
      achievement_completion_boundary_00676710(&g_manager, 0x05U);

  expect(result);
  expect(completion_kinds() == (std::vector<CompletionCallKind>{
                                   CompletionCallKind::search_sorted_set,
                                   CompletionCallKind::lookup_or_create,
                                   CompletionCallKind::acquire_notifier,
                                   CompletionCallKind::notify_completion,
                                   CompletionCallKind::acquire_event_queue,
                                   CompletionCallKind::construct_event_argument,
                                   CompletionCallKind::post_completion_event,
                                   CompletionCallKind::persist_achievements,
                               }));
  set_achievement_completion_ports(nullptr);
}

void test_completion_manager_gate_runs_after_search() {
  reset_completion_fixture();
  g_manager.gate = 1U;
  set_achievement_completion_ports(&g_completion_ports);
  const bool result =
      achievement_completion_boundary_00676710(&g_manager, 0x20U);

  expect(!result);
  expect(completion_kinds() == (std::vector<CompletionCallKind>{
                                   CompletionCallKind::search_sorted_set}));
  expect(notifier_acquire_count == 0);
  expect(persist_count == 0);
  set_achievement_completion_ports(nullptr);
}

void test_completion_status_boundaries() {
  const std::vector<std::uint8_t> statuses = {0x00U, 0x01U, 0x02U, 0x80U};
  const std::vector<bool> expected = {false, true, true, true};
  for (std::size_t index = 0; index < statuses.size(); ++index) {
    reset_completion_fixture();
    inserted_status = statuses[index];
    set_achievement_completion_ports(&g_completion_ports);
    const bool result =
        achievement_completion_boundary_00676710(&g_manager, 0x20U);
    expect(result == expected[index]);
    expect((persist_count == 1U) == expected[index]);
    expect((completion_calls.size() == 8U) == expected[index]);
  }
  set_achievement_completion_ports(nullptr);
}

void test_completion_null_notifier_and_queue_paths() {
  reset_completion_fixture();
  notifier_object = 0U;
  set_achievement_completion_ports(&g_completion_ports);
  expect(achievement_completion_boundary_00676710(&g_manager, 0x20U));
  expect(notifier_acquire_count == 1U);
  expect(completion_kinds() == (std::vector<CompletionCallKind>{
                                   CompletionCallKind::search_sorted_set,
                                   CompletionCallKind::lookup_or_create,
                                   CompletionCallKind::acquire_notifier,
                                   CompletionCallKind::acquire_event_queue,
                                   CompletionCallKind::construct_event_argument,
                                   CompletionCallKind::post_completion_event,
                                   CompletionCallKind::persist_achievements,
                               }));

  reset_completion_fixture();
  queue_object = 0U;
  set_achievement_completion_ports(&g_completion_ports);
  expect(achievement_completion_boundary_00676710(&g_manager, 0x20U));
  expect(completion_kinds() == (std::vector<CompletionCallKind>{
                                   CompletionCallKind::search_sorted_set,
                                   CompletionCallKind::lookup_or_create,
                                   CompletionCallKind::acquire_notifier,
                                   CompletionCallKind::notify_completion,
                                   CompletionCallKind::acquire_event_queue,
                                   CompletionCallKind::persist_achievements,
                               }));
  expect(release_count == 0);
  expect(persist_count == 1U);
  set_achievement_completion_ports(nullptr);
}

void test_completion_release_flag_and_post_failure() {
  reset_completion_fixture();
  constructed_flags = kCompletionEventReleaseFlag;
  set_achievement_completion_ports(&g_completion_ports);
  expect(achievement_completion_boundary_00676710(&g_manager, 0x20U));
  expect(release_count == 1U);
  expect(completion_kinds().back() == CompletionCallKind::persist_achievements);

  reset_completion_fixture();
  constructed_flags = 0x02U;
  set_achievement_completion_ports(&g_completion_ports);
  expect(achievement_completion_boundary_00676710(&g_manager, 0x20U));
  expect(release_count == 0U);

  reset_completion_fixture();
  constructed_flags = kCompletionEventReleaseFlag;
  post_result = 0U;
  set_achievement_completion_ports(&g_completion_ports);
  expect(achievement_completion_boundary_00676710(&g_manager, 0x20U));
  expect(release_count == 1U);
  expect(persist_count == 1U);
  set_achievement_completion_ports(nullptr);
}

enum class TransitionCallKind : std::uint8_t {
  lookup_or_create,
  compare_threshold,
  forward_completion,
};

struct TransitionCall {
  TransitionCallKind kind;
  Word key = 0;
  Word flags = 0;
  Word progress_flags = 0;
  Word target = 0;
  Opaque receiver = 0;
  bool result = false;

  bool operator==(const TransitionCall& other) const {
    return kind == other.kind && key == other.key && flags == other.flags &&
           progress_flags == other.progress_flags && target == other.target &&
           receiver == other.receiver && result == other.result;
  }
};

std::vector<TransitionCall> transition_calls;
AchievementDefinitionWire g_definition{};
Word lookup_key = 0;
bool forward_result = true;

AchievementDefinitionWire* PKG11_A3_TEST_THISCALL
transition_lookup_or_create(AchievementManagerWire* manager, Word key) {
  transition_calls.push_back({TransitionCallKind::lookup_or_create, key,
                              g_definition.flags, g_definition.progress_flags,
                              g_definition.target, pointer_word(manager),
                              false});
  lookup_key = key;
  return &g_definition;
}

bool compare_threshold(const AchievementDefinitionWire* record) {
  transition_calls.push_back({TransitionCallKind::compare_threshold, 0,
                              record->flags, record->progress_flags,
                              record->target, pointer_word(record),
                              live_comparator_mode(record)});
  return live_comparator_mode(record);
}

bool PKG11_A3_TEST_THISCALL forward_completion(AchievementManagerWire* manager,
                                               Word key) {
  transition_calls.push_back({TransitionCallKind::forward_completion, key, 0, 0,
                              0, pointer_word(manager), forward_result});
  return forward_result;
}

const AchievementFlagTransitionPorts g_transition_ports{
    transition_lookup_or_create,
    compare_threshold,
    forward_completion,
};

void reset_transition_fixture() {
  g_manager = AchievementManagerWire{};
  g_definition = AchievementDefinitionWire{0x001U, 0U, 0U};
  lookup_key = 0;
  forward_result = true;
  transition_calls.clear();
}

void test_transition_set_and_clear_mask() {
  reset_transition_fixture();
  set_achievement_flag_transition_ports(&g_transition_ports);
  g_definition.progress_flags = 0x0f0f0f0fU;
  achievement_progress_flag_transition_00676ed0(&g_manager, 0x1234U,
                                                0x00ff00ffU, 1U);
  expect(lookup_key == 0x1234U);
  expect(g_definition.progress_flags == (0x0f0f0f0fU | 0x00ff00ffU));
  expect(transition_calls.size() == 3U);
  expect(transition_calls[1].progress_flags == (0x0f0f0f0fU | 0x00ff00ffU));
  expect(transition_calls[2].key == 0x1234U);
  expect(transition_calls[2].receiver == pointer_word(&g_manager));

  transition_calls.clear();
  achievement_progress_flag_transition_00676ed0(&g_manager, 0x1234U,
                                                0x00ff00ffU, 0U);
  expect(g_definition.progress_flags == 0x0f000f00U);
  expect(transition_calls.size() == 3U);
  expect(transition_calls[1].progress_flags == 0x0f000f00U);
  set_achievement_flag_transition_ports(nullptr);
}

void test_transition_mask_boundaries() {
  reset_transition_fixture();
  set_achievement_flag_transition_ports(&g_transition_ports);

  g_definition.progress_flags = 0xdeadbeefU;
  achievement_progress_flag_transition_00676ed0(&g_manager, 1U, 0U, 1U);
  expect(g_definition.progress_flags == 0xdeadbeefU);

  achievement_progress_flag_transition_00676ed0(&g_manager, 1U, 0xffffffffU,
                                                1U);
  expect(g_definition.progress_flags == 0xffffffffU);

  achievement_progress_flag_transition_00676ed0(&g_manager, 1U, 0xffffffffU,
                                                0U);
  expect(g_definition.progress_flags == 0U);

  g_definition.progress_flags = 0x80000000U;
  achievement_progress_flag_transition_00676ed0(&g_manager, 1U, 0x80000000U,
                                                0U);
  expect(g_definition.progress_flags == 0U);

  g_definition.progress_flags = 0x80000000U;
  achievement_progress_flag_transition_00676ed0(&g_manager, 1U, 0x80000000U,
                                                2U);
  expect(g_definition.progress_flags == 0x80000000U);
  set_achievement_flag_transition_ports(nullptr);
}

void test_transition_manager_gate_and_flag_bit() {
  reset_transition_fixture();
  set_achievement_flag_transition_ports(&g_transition_ports);
  g_manager.gate = 1U;
  achievement_progress_flag_transition_00676ed0(&g_manager, 7U, 0x10U, 1U);
  expect(transition_calls.empty());
  expect(g_definition.progress_flags == 0U);

  g_manager.gate = 0U;
  g_definition.flags = 0x100U;
  achievement_progress_flag_transition_00676ed0(&g_manager, 7U, 0x10U, 1U);
  expect(g_definition.progress_flags == 0x10U);
  expect(transition_calls.size() == 1U);
  expect(transition_calls[0].kind == TransitionCallKind::lookup_or_create);
  set_achievement_flag_transition_ports(nullptr);
}

void test_transition_comparator_modes() {
  struct ModeCase {
    Word flags;
    Word progress;
    Word target;
    bool forwards;
  };
  const std::vector<ModeCase> cases = {
      {0x001U, 4U, 5U, false}, {0x001U, 5U, 5U, true},  {0x001U, 6U, 5U, true},
      {0x101U, 5U, 5U, false}, {0x101U, 6U, 5U, true},  {0x201U, 5U, 5U, true},
      {0x201U, 4U, 5U, false}, {0x301U, 4U, 5U, true},  {0x301U, 5U, 5U, false},
      {0x401U, 5U, 5U, true},  {0x401U, 6U, 5U, false}, {0x501U, 5U, 5U, false},
      {0x501U, 5U, 6U, true},  {0x601U, 5U, 5U, false}, {0x701U, 5U, 5U, false},
  };
  set_achievement_flag_transition_ports(&g_transition_ports);
  for (const ModeCase& entry : cases) {
    reset_transition_fixture();
    g_definition.flags = entry.flags;
    g_definition.progress_flags = entry.progress;
    g_definition.target = entry.target;
    achievement_progress_flag_transition_00676ed0(&g_manager, 0x55U, 0U, 0U);
    const bool forwarded = transition_calls.size() == 3U;
    expect(forwarded == entry.forwards);
    expect(g_definition.progress_flags == entry.progress);
    if (forwarded) {
      expect(transition_calls[1].kind == TransitionCallKind::compare_threshold);
      expect(transition_calls[1].flags == entry.flags);
      expect(transition_calls[1].target == entry.target);
      expect(transition_calls[2].kind ==
             TransitionCallKind::forward_completion);
    } else {
      expect(transition_calls[1].kind == TransitionCallKind::compare_threshold);
    }
  }
  set_achievement_flag_transition_ports(nullptr);
}

void test_transition_forward_result_ignored() {
  reset_transition_fixture();
  set_achievement_flag_transition_ports(&g_transition_ports);
  forward_result = false;
  achievement_progress_flag_transition_00676ed0(&g_manager, 3U, 0x4U, 1U);
  expect(transition_calls.size() == 3U);
  expect(transition_calls[2].result == false);
  expect(g_definition.progress_flags == 0x4U);
  forward_result = true;
  set_achievement_flag_transition_ports(nullptr);
}

enum class RecordCallKind : std::uint8_t {
  acquire_manager_target,
  acquire_write_stream,
  write_record_word,
  write_record_byte,
};

struct RecordCall {
  RecordCallKind kind;
  Word value = 0;
  Word count = 0;
  Word mode = 0;
  Opaque receiver = 0;
  Opaque stream = 0;

  bool operator==(const RecordCall& other) const {
    return kind == other.kind && value == other.value && count == other.count &&
           mode == other.mode && receiver == other.receiver &&
           stream == other.stream;
  }
};

std::vector<RecordCall> record_calls;
MissionManagerWire g_mission_manager{};
Opaque manager_target = 0;
Opaque write_stream = 0;
std::uint8_t record_flag = 0;

Opaque PKG11_A3_TEST_THISCALL
acquire_manager_target(MissionManagerWire* manager) {
  record_calls.push_back({RecordCallKind::acquire_manager_target, 0, 0, 0,
                          pointer_word(manager), 0});
  return manager_target;
}

Opaque PKG11_A3_TEST_THISCALL acquire_write_stream(Opaque target) {
  record_calls.push_back(
      {RecordCallKind::acquire_write_stream, 0, 0, 0, target, 0});
  return write_stream;
}

Opaque PKG11_A3_TEST_THISCALL write_record_word(Opaque stream,
                                                const Word* payload,
                                                std::int32_t count, Word mode) {
  record_calls.push_back({RecordCallKind::write_record_word, *payload,
                          static_cast<Word>(count), mode, 0, stream});
  return 0U;
}

Word PKG11_A3_TEST_THISCALL write_record_byte(Opaque stream,
                                              const std::uint8_t* payload,
                                              Word size) {
  record_calls.push_back(
      {RecordCallKind::write_record_byte, payload[0], size, 0, 0, stream});
  return 0U;
}

const MissionRecordInitPorts g_record_ports{
    acquire_manager_target,
    acquire_write_stream,
    write_record_word,
    write_record_byte,
};

std::vector<Opaque> staged_targets;
std::vector<Opaque> staged_streams;
std::size_t staged_index = 0;

Opaque PKG11_A3_TEST_THISCALL
staged_manager_target(MissionManagerWire* manager) {
  record_calls.push_back({RecordCallKind::acquire_manager_target, 0, 0, 0,
                          pointer_word(manager), 0});
  const Opaque value = staged_targets[staged_index];
  ++staged_index;
  return value;
}

Opaque PKG11_A3_TEST_THISCALL staged_write_stream(Opaque target) {
  record_calls.push_back(
      {RecordCallKind::acquire_write_stream, 0, 0, 0, target, 0});
  return staged_streams[staged_index - 1U];
}

const MissionRecordInitPorts g_staged_ports{
    staged_manager_target, staged_write_stream, write_record_word,
    write_record_byte};

void test_record_init_write_order_and_flag_propagation() {
  record_calls.clear();
  g_mission_manager = MissionManagerWire{nullptr};
  manager_target = 0x7000U;
  write_stream = 0x7100U;
  record_flag = 0x01U;
  set_mission_record_init_ports(&g_record_ports);

  const MissionManagerWire* const returned =
      mission_manager_record_init_00fec3c0(&g_mission_manager, &record_flag);
  expect(returned == &g_mission_manager);
  expect(record_calls ==
         (std::vector<RecordCall>{
             {RecordCallKind::acquire_manager_target, 0, 0, 0,
              pointer_word(&g_mission_manager), 0},
             {RecordCallKind::acquire_write_stream, 0, 0, 0, 0x7000U, 0},
             {RecordCallKind::write_record_word, 1U, 1U, 0U, 0, 0x7100U},
             {RecordCallKind::acquire_manager_target, 0, 0, 0,
              pointer_word(&g_mission_manager), 0},
             {RecordCallKind::acquire_write_stream, 0, 0, 0, 0x7000U, 0},
             {RecordCallKind::write_record_byte, 1U, 1U, 0U, 0, 0x7100U},
         }));
  set_mission_record_init_ports(nullptr);
}

void test_record_init_flag_bit_masking() {
  const std::vector<std::uint8_t> flags = {0x00U, 0x01U, 0x02U,
                                           0x03U, 0x80U, 0xffU};
  const std::vector<Word> expected = {0U, 1U, 0U, 1U, 0U, 1U};
  set_mission_record_init_ports(&g_record_ports);
  for (std::size_t index = 0; index < flags.size(); ++index) {
    record_calls.clear();
    g_mission_manager = MissionManagerWire{nullptr};
    record_flag = flags[index];
    mission_manager_record_init_00fec3c0(&g_mission_manager, &record_flag);
    expect(record_calls.size() == 6U);
    expect(record_calls[2].kind == RecordCallKind::write_record_word);
    expect(record_calls[2].value == 1U);
    expect(record_calls[2].count == 1U);
    expect(record_calls[2].mode == 0U);
    expect(record_calls[5].kind == RecordCallKind::write_record_byte);
    expect(record_calls[5].value == expected[index]);
    expect(record_calls[5].count == 1U);
  }
  set_mission_record_init_ports(nullptr);
}

void test_record_init_reacquires_target_per_write() {
  staged_targets = {0x1000U, 0x2000U};
  staged_streams = {0x1100U, 0x2200U};
  staged_index = 0;
  record_calls.clear();
  g_mission_manager = MissionManagerWire{nullptr};
  record_flag = 0x01U;
  set_mission_record_init_ports(&g_staged_ports);
  expect(mission_manager_record_init_00fec3c0(
             &g_mission_manager, &record_flag) == &g_mission_manager);
  expect(staged_index == 2U);
  expect(record_calls[2].stream == 0x1100U);
  expect(record_calls[5].stream == 0x2200U);
  expect(record_calls[1].receiver == 0x1000U);
  expect(record_calls[4].receiver == 0x2000U);
  set_mission_record_init_ports(nullptr);
}

}

int main() {
  test_completion_missing_definition_notifies_and_forwards();
  test_completion_present_definition_suppresses_everything();
  test_completion_search_hit_suppresses_notify();
  test_completion_search_slot_above_key_counts_as_missing();
  test_completion_manager_gate_runs_after_search();
  test_completion_status_boundaries();
  test_completion_null_notifier_and_queue_paths();
  test_completion_release_flag_and_post_failure();
  test_transition_set_and_clear_mask();
  test_transition_mask_boundaries();
  test_transition_manager_gate_and_flag_bit();
  test_transition_comparator_modes();
  test_transition_forward_result_ignored();
  test_record_init_write_order_and_flag_propagation();
  test_record_init_flag_bit_masking();
  test_record_init_reacquires_target_per_write();
  return failures == 0 ? 0 : 1;
}

#undef PKG11_A3_TEST_THISCALL
