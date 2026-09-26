#include "achievement_mission_wave2.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg11_a3_achievement_mission_wave2 {
namespace {

AchievementCompletionPorts g_achievement_completion_ports{};
AchievementFlagTransitionPorts g_achievement_flag_transition_ports{};
MissionRecordInitPorts g_mission_record_init_ports{};

Word read_word(const void* base, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

}

AchievementCompletionPorts& achievement_completion_ports() {
  return g_achievement_completion_ports;
}

void set_achievement_completion_ports(const AchievementCompletionPorts* ports) {
  g_achievement_completion_ports =
      ports == nullptr ? AchievementCompletionPorts{} : *ports;
}

bool achievement_completion_boundary_00676710(AchievementManagerWire* manager,
                                              Word key) {
  const AchievementCompletionPorts& ports = achievement_completion_ports();
  AchievementSerializerWire* const serializer =
      reinterpret_cast<AchievementSerializerWire*>(
          static_cast<std::uintptr_t>(manager->serializer));

  Word search_key = key;
  const Opaque position = ports.search_sorted_set(
      serializer->achievement_set.begin, serializer->achievement_set.end,
      &search_key, serializer->achievement_set.tag);

  const Opaque set_end = serializer->achievement_set.end;
  bool present = position != set_end;
  if (present && key < read_word(reinterpret_cast<const void*>(
                                     static_cast<std::uintptr_t>(position)),
                                 0)) {
    present = false;
  }
  const Opaque clamped = present ? position : set_end;

  if (manager->gate != 0U) {
    return false;
  }

  AchievementLookupResultWire result{};
  const AchievementLookupResultWire* const outcome = ports.lookup_or_create(
      static_cast<Opaque>(
          reinterpret_cast<std::uintptr_t>(&serializer->achievement_set)),
      &result, &key);
  const std::uint8_t inserted = outcome->inserted;
  if (inserted == 0U) {
    return false;
  }

  if (clamped == set_end) {
    const Opaque notifier = ports.acquire_notifier();
    if (notifier != 0U) {
      ports.notify_completion(notifier, kCompletionNotifyEvent, &key,
                              kCompletionForwardedTail);
    }
  }

  const Opaque queue = ports.acquire_event_queue();
  if (queue != 0U) {
    AchievementEventArgumentWire arguments{};
    arguments.type_id = 0;
    arguments.reserved = 0;
    ports.construct_event_argument(&arguments, &key);
    static_cast<void>(
        ports.post_completion_event(queue, kCompletionPostType, &arguments));
    if ((arguments.flags & kCompletionEventReleaseFlag) != 0U) {
      ports.release_event_argument(&arguments, 0U);
    }
  }

  static_cast<void>(ports.persist_achievements(manager));
  return inserted != 0U;
}

AchievementFlagTransitionPorts& achievement_flag_transition_ports() {
  return g_achievement_flag_transition_ports;
}

void set_achievement_flag_transition_ports(
    const AchievementFlagTransitionPorts* ports) {
  g_achievement_flag_transition_ports =
      ports == nullptr ? AchievementFlagTransitionPorts{} : *ports;
}

void achievement_progress_flag_transition_00676ed0(
    AchievementManagerWire* manager, Word key, Word mask, std::uint8_t set) {
  if (manager->gate != 0U) {
    return;
  }
  const AchievementFlagTransitionPorts& ports =
      achievement_flag_transition_ports();
  AchievementDefinitionWire* const record =
      ports.lookup_or_create(manager, key);
  if (set != 0U) {
    record->progress_flags |= mask;
  } else {
    record->progress_flags &= ~mask;
  }
  if ((record->flags & 0x1U) == 0U) {
    return;
  }
  if (!ports.compare_threshold(record)) {
    return;
  }
  static_cast<void>(ports.forward_completion(manager, key));
}

MissionRecordInitPorts& mission_record_init_ports() {
  return g_mission_record_init_ports;
}

void set_mission_record_init_ports(const MissionRecordInitPorts* ports) {
  g_mission_record_init_ports =
      ports == nullptr ? MissionRecordInitPorts{} : *ports;
}

MissionManagerWire* mission_manager_record_init_00fec3c0(
    MissionManagerWire* manager, const std::uint8_t* flag) {
  const MissionRecordInitPorts& ports = mission_record_init_ports();

  const Opaque first_target = ports.acquire_manager_target(manager);
  const Opaque first_stream = ports.acquire_write_stream(first_target);

  Word payload = 1U;
  static_cast<void>(ports.write_record_word(first_stream, &payload, 1, 0U));

  const std::uint8_t observed = *flag;
  const Opaque second_target = ports.acquire_manager_target(manager);
  const Opaque second_stream = ports.acquire_write_stream(second_target);

  payload = (observed & 0x1U) != 0U ? 1U : 0U;
  static_cast<void>(ports.write_record_byte(
      second_stream, reinterpret_cast<const std::uint8_t*>(&payload), 1U));
  return manager;
}

}
