#include "cell_behavior_dispatch.hpp"

#include <cmath>
#include <cstring>

namespace openspore::reconstruction::pkg06c_cell_behavior_dispatch {

namespace {

template <typename Value>
Value load_field(const void* object, std::size_t offset) {
  Value value{};
  std::memcpy(&value, static_cast<const unsigned char*>(object) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store_field(void* object, std::size_t offset, Value value) {
  std::memcpy(static_cast<unsigned char*>(object) + offset, &value,
              sizeof(value));
}

std::uint8_t load_u8(const void* object, std::size_t offset) {
  return load_field<std::uint8_t>(object, offset);
}

std::int32_t load_i32(const void* object, std::size_t offset) {
  return load_field<std::int32_t>(object, offset);
}

std::uint32_t load_u32(const void* object, std::size_t offset) {
  return load_field<std::uint32_t>(object, offset);
}

float load_float(const void* object, std::size_t offset) {
  return load_field<float>(object, offset);
}

}  // namespace

void cell_behavior_dispatch_00e7a190(ObservedCellCellResource* resource,
                                     ObservedCellObjectData* object,
                                     float delta, NativePorts& ports) {
  const std::uint32_t serializable_address =
      load_u32(g_cell_game_016b3c04, kGameSerializableOffset);
  const auto serializable = reinterpret_cast<const std::byte*>(
      static_cast<std::uintptr_t>(serializable_address));
  const std::int32_t difficulty = load_i32(serializable, kGameDifficultyOffset);
  ObservedCellAiData* activity_profile = &resource->normal;
  if (difficulty == 0) {
    activity_profile = &resource->ai_easy;
    if (load_i32(activity_profile, 0) == -1) {
      activity_profile = &resource->normal;
    }
  } else if (difficulty == 2) {
    activity_profile = &resource->ai_hard;
    if (load_i32(activity_profile, 0) == -1) {
      activity_profile = &resource->normal;
    }
  }

  const NativeCallContext pre_context{object, resource, g_cell_game_016b3c04,
                                      delta};
  const std::uint32_t activity_object_id = load_u32(object, kObjectIdOffset);
  if (load_i32(activity_profile, 0) == 0 &&
      activity_object_id != load_u32(pre_context.game, kGamePlayerOffset)) {
    return;
  }

  ports.pre_dispatch_00e76a80(pre_context);
  const std::uint32_t object_id = load_u32(object, kObjectIdOffset);

  if (load_u8(object, kObjectStopOffset) != 0 &&
      load_i32(object, kObjectStateOffset) != 8) {
    store_field<std::int32_t>(object, kObjectStateOffset, 10);
    return;
  }

  if (load_u8(object, kObjectReturnOffset) != 0) {
    return;
  }

  std::byte* game_after = g_cell_game_016b3c04;
  const NativeCallContext context{object, resource, game_after, delta};
  if (load_u8(context.game, kGameSuppressionOffset) == 1 &&
      object_id == load_u32(context.game, kGamePlayerOffset)) {
    return;
  }

  if (object_id == load_u32(context.game, kGameSpecialObjectOffset)) {
    ObservedCellAiData* special_profile =
        cell_ai_select_profile_00e52910(resource);
    float special_value = load_float(special_profile, 0x1c);
    if (special_value == 0.0F) {
      special_value = load_float(special_profile, 0x18);
    }

    if (load_i32(context.game, kGameSpecialModeOffset) == 3) {
      ObservedCellAiData* byte_profile =
          cell_ai_select_profile_00e52910(resource);
      const std::uint32_t profile_byte =
          static_cast<std::uint32_t>(load_u8(byte_profile, 0x44));
      const std::uint32_t value =
          ports.value_00e67c40(context, 1U, profile_byte);
      ObservedCellAiData* value_profile =
          cell_ai_select_profile_00e52910(resource);
      std::byte* game_after_value = g_cell_game_016b3c04;
      const NativeCallContext raw_context{object, resource, game_after_value,
                                          delta};
      ports.raw_00e6f800(raw_context,
                         load_u32(raw_context.game, kGamePlayerOffset),
                         special_value, load_float(value_profile, 0x40), value,
                         1U, profile_byte);
      return;
    }
  }

  if (object_id == load_u32(context.game, kGamePriorityObjectOffset)) {
    ports.priority_00e71c00(context);
    return;
  }

  if (object_id == load_u32(context.game, kGamePlayerOffset)) {
    ports.player_00e6f5b0(context);
    return;
  }

  ObservedCellAiData* dispatch_profile =
      cell_ai_select_profile_00e52910(resource);
  switch (load_i32(dispatch_profile, 0)) {
    case 0x1001:
      ports.dispatch_1001_00e71300(context);
      break;
    case 0x1003:
      ports.dispatch_1003_00e70650(context);
      break;
    case 0x1004:
      ports.dispatch_1004_00e704b0(context);
      break;
    case 0x1005:
      ports.dispatch_1005_00e702d0(context);
      break;
    case 0x1006:
      ports.dispatch_1006_00e7a0a0(context);
      break;
    case 0x1007:
      ports.dispatch_1007_00e6f990(context);
      break;
    case 0x1008:
      ports.dispatch_1008_00e78fc0(context);
      break;
    case 0x1009:
      ports.dispatch_1009_00e707d0(context);
      break;
    case 0x100a:
      break;
    case 0x100b:
      ports.dispatch_100b_00e6fbb0(context);
      break;
    case 0x100c:
      ports.dispatch_100c_00e6fd70(context);
      break;
    case 0x100d:
      ports.dispatch_100d_00e6fce0(context);
      break;
    case 0x100e:
      ports.dispatch_100e_00e7a0d0(context);
      break;
    default:
      break;
  }
}

}  // namespace openspore::reconstruction::pkg06c_cell_behavior_dispatch
