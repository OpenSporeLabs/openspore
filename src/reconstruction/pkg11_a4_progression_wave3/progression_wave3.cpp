#include "progression_wave3.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg11_a4_progression_wave3 {
namespace {

ProgressionPorts g_progression_ports{};

Opaque container_address(ProgressionManagerWire* manager, std::size_t offset) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(
      reinterpret_cast<std::uint8_t*>(manager) + offset));
}

Word read_points(const ProgressionManagerWire* manager) {
  Word points = 0;
  std::memcpy(&points, manager->storage + kPointsOffset, sizeof(points));
  return points;
}

void write_points(ProgressionManagerWire* manager, Word points) {
  std::memcpy(manager->storage + kPointsOffset, &points, sizeof(points));
}

bool progression_entry_eligible(ProgressionManagerWire* manager,
                                Word instance_id, Word group_id) {
  const ProgressionPorts& ports = progression_ports();
  const OpaqueKey key{instance_id, group_id};
  std::uint8_t status = 0;
  if (ports.find_status(container_address(manager, kStatusContainerOffset),
                        &key, &status)) {
    return (status & kUnlockedMask) == 0U;
  }
  if (ports.find_configured(
          container_address(manager, kConfiguredContainerOffset), &key)) {
    return true;
  }
  return manager->storage[kDefaultEligibilityOffset] == 0U;
}

}

ProgressionPorts& progression_ports() { return g_progression_ports; }

void set_progression_ports(const ProgressionPorts* ports) {
  g_progression_ports = ports == nullptr ? ProgressionPorts{} : *ports;
}

bool collectable_unlock_00596da0(ProgressionManagerWire* manager,
                                 Word instance_id, Word group_id,
                                 std::int32_t cost) {
  const ProgressionPorts& ports = progression_ports();
  if (!progression_entry_eligible(manager, instance_id, group_id)) {
    return false;
  }

  const Word remaining = read_points(manager) - static_cast<Word>(cost);
  if (cost != 0 && (remaining & 0x80000000U) != 0U) {
    return false;
  }

  write_points(manager, remaining);
  const OpaqueKey key{instance_id, group_id};
  std::uint8_t* const status = ports.status_operator_bracket(
      container_address(manager, kStatusContainerOffset), &key);
  *status = static_cast<std::uint8_t>(*status | kUnlockStateMask);
  ports.append_unlocked(container_address(manager, kUnlockedListOffset), &key);
  return true;
}

bool collectable_lock_00596e10(ProgressionManagerWire* manager,
                               Word instance_id, Word group_id) {
  const ProgressionPorts& ports = progression_ports();
  const OpaqueKey key{instance_id, group_id};
  std::uint8_t* const status = ports.status_operator_bracket(
      container_address(manager, kStatusContainerOffset), &key);
  *status = static_cast<std::uint8_t>(*status & kUnlockStateClearMask);
  ports.remove_unlocked(container_address(manager, kUnlockedListOffset), &key);
  return true;
}

}
