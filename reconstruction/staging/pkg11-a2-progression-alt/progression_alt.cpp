#include "progression_alt.hpp"

#include <cstring>
#include <limits>

namespace openspore::reconstruction::pkg11_a2_progression_alt {
namespace {

MissionManagerOperationPorts g_mission_manager_operation_ports{};
MissionTrackPorts g_mission_track_ports{};
AchievementProgressPorts g_achievement_progress_ports{};

Word read_word(const void* base, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

std::int32_t arithmetic_shift_right_2(std::uint32_t value) {
  const std::uint32_t sign_fill = (value & 0x80000000U) != 0 ? 0xffffffffU : 0U;
  const std::uint32_t shifted = (value >> 2U) | (sign_fill << 30U);
  std::int32_t result = 0;
  std::memcpy(&result, &shifted, sizeof(result));
  return result;
}

}

MissionManagerOperationPorts& mission_manager_operation_ports() {
  return g_mission_manager_operation_ports;
}

void set_mission_manager_operation_ports(
    const MissionManagerOperationPorts* ports) {
  g_mission_manager_operation_ports =
      ports == nullptr ? MissionManagerOperationPorts{} : *ports;
}

void mission_manager_operation_00fee310(MissionManagerWire* manager) {
  const MissionManagerOperationPorts& ports = mission_manager_operation_ports();
  const Opaque simulator_system = ports.get_simulator_system();
  ports.initialize_subsystem(simulator_system, manager);
  ports.populate_manager_state(manager);

  const Opaque initial_registry = ports.get_registry();
  ports.prepare_registry(initial_registry);
  const struct {
    Word key;
    std::size_t field_offset;
  } entries[] = {
      {0x06b5005eU, 0x20},
      {0x994d1f83U, 0x34},
      {0xa07f6fd6U, 0x48},
  };
  for (const auto& entry : entries) {
    void* field = static_cast<void*>(reinterpret_cast<std::uint8_t*>(manager) +
                                     entry.field_offset);
    const Opaque builder = ports.get_registry();
    ports.build_registry_entry(builder, field, entry.key);
  }

  ports.register_fixed_identifiers();
  const Opaque noun_manager = ports.get_noun_manager();
  const MissionProjectionVectorWire* projection =
      ports.project_nouns(noun_manager, 0x00cd7d10U, 0x00d3d420U, 0x00fed010U,
                          0x00b1e520U, 0x02aa5adaU);
  const Opaque* cursor = projection->begin;
  const Opaque* end = projection->end;
  while (cursor != end) {
    const Opaque entry = *cursor;
    if (entry != 0U) {
      ports.dispatch_projection_entry(entry);
    }
    ++cursor;
  }
}

MissionTrackPorts& mission_track_ports() { return g_mission_track_ports; }

void set_mission_track_ports(const MissionTrackPorts* ports) {
  g_mission_track_ports = ports == nullptr ? MissionTrackPorts{} : *ports;
}

bool mission_track_predicate_00febc90(MissionManagerWire* manager,
                                      std::int32_t index, Opaque identity) {
  const MissionTrackPorts& ports = mission_track_ports();
  const std::uint32_t outer_begin = read_word(manager, 0x34);
  const std::uint32_t outer_end = read_word(manager, 0x38);
  const std::int32_t outer_count =
      static_cast<std::int32_t>(outer_end - outer_begin) / 0x38;
  if (index >= outer_count) {
    return false;
  }

  const Opaque record =
      static_cast<Opaque>(static_cast<std::uintptr_t>(outer_begin) +
                          static_cast<std::intptr_t>(index) * 0x38);
  const void* record_pointer = reinterpret_cast<const void*>(record);
  const std::uint32_t inner_begin = read_word(record_pointer, 0x08);
  const std::uint32_t inner_end = read_word(record_pointer, 0x0c);
  const std::int32_t inner_count =
      arithmetic_shift_right_2(inner_end - inner_begin);
  for (std::int32_t item = 0; item < inner_count; ++item) {
    const std::uintptr_t item_address =
        static_cast<std::uintptr_t>(inner_begin) +
        static_cast<std::uintptr_t>(item * 4);
    Word item_identity = 0;
    std::memcpy(&item_identity, reinterpret_cast<const void*>(item_address),
                sizeof(item_identity));
    const Opaque carrier = ports.get_noun_carrier();
    const Opaque command_value = ports.read_command_value(carrier);
    if (!ports.is_command_valid(command_value, item_identity)) {
      return false;
    }
  }

  if (identity == 0U) {
    return true;
  }
  const Opaque current_empire = ports.get_current_empire();
  if (identity == current_empire) {
    return true;
  }
  const std::int32_t score = ports.compute_and_update_score(identity);
  const std::int32_t threshold =
      static_cast<std::int32_t>(read_word(record_pointer, 0x04));
  return score >= threshold;
}

static bool achievement_threshold_reached_006751c0(
    const AchievementRecordWire* record) {
  const Word mode = (record->flags >> 8U) & 0x7U;
  switch (mode) {
    case 0:
      return record->target <= record->progress;
    case 1:
      return record->target < record->progress;
    case 2:
      return record->progress == record->target;
    case 3:
      return record->progress < record->target;
    case 4:
      return record->progress <= record->target;
    case 5:
      return record->progress != record->target;
    default:
      return false;
  }
}

AchievementProgressPorts& achievement_progress_ports() {
  return g_achievement_progress_ports;
}

void set_achievement_progress_ports(const AchievementProgressPorts* ports) {
  g_achievement_progress_ports =
      ports == nullptr ? AchievementProgressPorts{} : *ports;
}

void achievement_progress_update_00676e90(AchievementManagerWire* manager,
                                          Word increment, Word key) {
  const AchievementProgressPorts& ports = achievement_progress_ports();
  if (manager->storage[0x24] != 0U) {
    return;
  }
  AchievementRecordWire* record = ports.lookup_or_create(manager, key);
  record->progress += increment;
  if ((record->flags & 0x1U) == 0U ||
      !achievement_threshold_reached_006751c0(record)) {
    return;
  }
  static_cast<void>(ports.forward_progress_key(manager, key));
}

}
