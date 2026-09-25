#include "cell_behavior_timer.hpp"

#include <cmath>
#include <cstring>

namespace openspore::reconstruction::pkg06d_cell_behavior_timer {

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

float load_float(const void* object, std::size_t offset) {
  return load_field<float>(object, offset);
}

std::uint32_t load_u32(const void* object, std::size_t offset) {
  return load_field<std::uint32_t>(object, offset);
}

void store_float(void* object, std::size_t offset, float value) {
  store_field(object, offset, value);
}

}  // namespace

void cell_behavior_timer_update_00e7e6c0(
    OpaqueBehaviorTimerRecord* record,
    OpaqueBehaviorTimerEntryEcx opaque_entry_ecx, float delta,
    NativePorts& ports) {
  const float record_timer = load_float(record, 0x1c);
  store_float(record, 0x1c, record_timer - delta);

  if (!ports.gate_00e59c10({record, opaque_entry_ecx, delta})) {
    ports.fallback_00e7e130({record, delta, 0, 0});
    return;
  }

  for (std::uint32_t slot = 0; slot < 4; ++slot) {
    const std::size_t timer_offset = 0x0cU + slot * sizeof(float);
    const float timer = load_float(record, timer_offset);
    if (0.0F < timer) {
      const float remaining = timer - delta;
      store_float(record, timer_offset, remaining);
      if (remaining < 0.0F) {
        store_float(record, timer_offset, 0.0F);
        if (!ports.expire_00e7b540({record, delta, slot})) {
          ports.fallback_00e7e130({record, delta, 0, 0});
          return;
        }
      }
    }
  }

  const float current_record_timer = load_float(record, 0x1c);
  if (0.0F < current_record_timer || std::isnan(current_record_timer)) {
    if (ports.advance_00e7ba30({record, delta})) {
      return;
    }
  } else {
    const std::byte* game = g_cell_game_016b3c04;
    const std::uint32_t selector = load_u32(game, 0x5198);
    const std::uint32_t record_id = load_u32(record, 0x000);
    if (selector == record_id) {
      if (ports.advance_00e7ba30({record, delta})) {
        return;
      }
    } else {
      store_float(record, 0x1c, 0.0F);
    }
  }

  ports.fallback_00e7e130({record, delta, 0, 0});
}

}  // namespace openspore::reconstruction::pkg06d_cell_behavior_timer
