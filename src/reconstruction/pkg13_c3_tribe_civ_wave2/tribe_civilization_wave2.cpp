#include "tribe_civilization_wave2.hpp"

#include <cstring>
#include <limits>

#if defined(_MSC_VER)
#define PKG13_C3_THISCALL __thiscall
#else
#define PKG13_C3_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg13_c3_tribe_civ_wave2 {

NativePorts g_native_ports{};
std::uint32_t g_dat_01485720 = 0x3f800000u;

namespace {

void* at(void* base, std::size_t offset) {
  return static_cast<std::uint8_t*>(base) + offset;
}

void store_u32(void* base, std::size_t offset, std::uint32_t value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + offset, &value, sizeof(value));
}

void store_u8(void* base, std::size_t offset, std::uint8_t value) {
  *(static_cast<std::uint8_t*>(base) + offset) = value;
}

std::uint32_t pointer_word(const void* pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

BuildingVtable* building_vtable(OpaqueBuilding* building) {
  return *reinterpret_cast<BuildingVtable**>(building->bytes.data());
}

void reset_00bc3170(void* object) {
  store_u32(object, 0x10, 0);
  store_u32(object, 0x14, 0);
  store_u32(object, 0x08, 0);
  store_u32(object, 0x0c, 0);
  store_u8(object, 0x18, 0);
}

void initialize_manager_01062ee0(TribeManager* manager) {
  store_u32(manager, 0x00, 0);
  store_u32(manager, 0x04, std::numeric_limits<std::uint32_t>::max());
}

}

extern "C" Tribe* PKG13_C3_THISCALL tribe_constructor_00c982a0(Tribe* tribe) {
  g_native_ports.initialize_00c011c0(tribe);
  g_native_ports.initialize_00c89630(at(tribe, 0x120));
  g_native_ports.initialize_00ac03d0(at(tribe, 0x1f4));
  g_native_ports.initialize_00cee630(at(tribe, 0x20c));
  g_native_ports.initialize_00b6f280(at(tribe, 0x230));

  store_u32(tribe, 0x1f4, 0x1473d64u);
  store_u32(tribe, 0x120, 0x1473d80u);
  store_u32(tribe, 0x000, 0x1473e58u);
  store_u32(tribe, 0x004, 0x1473e44u);
  store_u32(tribe, 0x034, 0x1469cc0u);
  store_u32(tribe, 0x20c, 0x1473d20u);
  store_u32(tribe, 0x230, 0x1473d00u);
  store_u32(tribe, 0x260, 0);
  store_u8(tribe, 0x264, 0);
  store_u32(tribe, 0x268, 0x41200000u);
  store_u32(tribe, 0x26c, std::numeric_limits<std::uint32_t>::max());

  g_native_ports.initialize_00b63890(at(tribe, 0x270));

  store_u32(tribe, 0x290, 0);
  store_u32(tribe, 0x294, 0);
  store_u32(tribe, 0x298, 0);
  store_u32(tribe, 0x29c, 0);
  store_u32(tribe, 0x2a8, 0);
  store_u32(tribe, 0x2ac, 0);
  store_u32(tribe, 0x2b0, 0);
  store_u32(tribe, 0x2c0, 0);
  store_u32(tribe, 0x2c4, 0);
  store_u32(tribe, 0x2c8, 0);
  store_u32(tribe, 0x2cc, 0);
  store_u32(tribe, 0x2bc, std::numeric_limits<std::uint32_t>::max());
  store_u32(tribe, 0x2d0, 0);
  store_u32(tribe, 0x2d4, 0);
  store_u32(tribe, 0x2d8, 0);
  store_u8(tribe, 0x300, 0);
  store_u8(tribe, 0x301, 0);
  store_u32(tribe, 0x304, 0);
  store_u32(tribe, 0x308, 0);
  store_u32(tribe, 0x30c, 0);
  store_u32(tribe, 0x310, 0);
  store_u32(tribe, 0x314, 0);
  store_u32(tribe, 0x318, 0);
  store_u32(tribe, 0x31c, 0);
  store_u32(tribe, 0x330, g_dat_01485720);
  store_u32(tribe, 0x328, 2);
  store_u8(tribe, 0x334, 0);
  store_u32(tribe, 0x338, 0);
  store_u8(tribe, 0x33c, 0);
  store_u32(tribe, 0x340, 0);
  store_u32(tribe, 0x344, 0);
  store_u32(tribe, 0x348, 0);
  store_u32(tribe, 0x354, 0);
  store_u32(tribe, 0x358, 0);
  store_u32(tribe, 0x35c, 0);
  store_u32(tribe, 0x368, 0);
  store_u32(tribe, 0x36c, 0);
  store_u32(tribe, 0x370, 0);
  store_u32(tribe, 0x374, 0);
  store_u32(tribe, 0x380, 0);
  store_u32(tribe, 0x384, 0);
  store_u32(tribe, 0x388, 0);
  store_u32(tribe, 0x3a4, 0x40000000u);
  store_u32(tribe, 0x3a8, 0x40000000u);
  store_u32(tribe, 0x39c, 1);
  store_u32(tribe, 0x398, 0x154df28u);
  store_u32(tribe, 0x3a0, 0);
  store_u32(tribe, 0x3ac, 0);

  g_native_ports.initialize_00afba10(at(tribe, 0x3b4));

  store_u32(tribe, 0x418, pointer_word(at(tribe, 0x430)));
  store_u32(tribe, 0x41c, pointer_word(at(tribe, 0x430)));
  store_u32(tribe, 0x42c, 0);
  store_u32(tribe, 0x420, pointer_word(at(tribe, 0x4e4)));
  store_u32(tribe, 0x4f4, g_dat_01485720);
  store_u32(tribe, 0x4f8, 0x40000000u);
  store_u32(tribe, 0x4e8, 0x154df28u);
  store_u32(tribe, 0x4ec, 1);
  store_u32(tribe, 0x4f0, 0);
  store_u32(tribe, 0x4fc, 0);

  g_native_ports.initialize_00b63890(at(tribe, 0x510));
  g_native_ports.initialize_00b63890(at(tribe, 0x530));
  g_native_ports.initialize_00cc7e10(at(tribe, 0x558));

  store_u32(tribe, 0x550, 0);
  store_u8(tribe, 0x554, 0);
  store_u8(tribe, 0x555, 0);
  store_u8(tribe, 0x556, 0);
  store_u8(tribe, 0x557, 0);
  store_u32(tribe, 0x1874, std::numeric_limits<std::uint32_t>::max());
  store_u32(tribe, 0x188c, std::numeric_limits<std::uint32_t>::max());
  store_u32(tribe, 0x18a4, std::numeric_limits<std::uint32_t>::max());
  store_u32(tribe, 0x18bc, std::numeric_limits<std::uint32_t>::max());
  store_u32(tribe, 0x1868, 0);
  store_u32(tribe, 0x186c, 0);
  store_u32(tribe, 0x1870, 0);
  store_u8(tribe, 0x1878, 0);
  store_u8(tribe, 0x1879, 0);
  store_u32(tribe, 0x1880, 0);
  store_u32(tribe, 0x1884, 0);
  store_u32(tribe, 0x1888, 0);
  store_u8(tribe, 0x1890, 0);
  store_u8(tribe, 0x1891, 0);
  store_u32(tribe, 0x1898, 0);
  store_u32(tribe, 0x189c, 0);
  store_u32(tribe, 0x18a0, 0);
  store_u8(tribe, 0x18a8, 0);
  store_u8(tribe, 0x18a9, 0);
  store_u32(tribe, 0x18b0, 0);
  store_u32(tribe, 0x18b4, 0);
  store_u32(tribe, 0x18b8, 0);
  store_u8(tribe, 0x18c0, 0);
  store_u8(tribe, 0x18c1, 0);
  store_u32(tribe, 0x18c8, 0);
  store_u32(tribe, 0x18c4, 0);
  store_u32(tribe, 0x18cc, 0);
  store_u32(tribe, 0x18d0, 0);
  store_u32(tribe, 0x18d4, 0);
  store_u32(tribe, 0x18d8, 0);
  store_u32(tribe, 0x1904, pointer_word(at(tribe, 0x191c)));
  store_u32(tribe, 0x1908, pointer_word(at(tribe, 0x191c)));
  store_u32(tribe, 0x1918, 0);
  store_u32(tribe, 0x190c, pointer_word(at(tribe, 0x19c4)));
  store_u32(tribe, 0x19c4, 0);
  store_u32(tribe, 0x19c8, 0);
  store_u32(tribe, 0x19cc, 0);
  store_u32(tribe, 0x19d0, 0);
  store_u32(tribe, 0x19d4, 0);
  store_u32(tribe, 0x19d8, 0);

  std::memset(at(tribe, 0x18cc), 0, 0x38);
  g_native_ports.reserve_004548d0(at(tribe, 0x1904), 14);

  auto* const existing_slot = reinterpret_cast<ExistingObject**>(
      static_cast<std::uint8_t*>(tribe->bytes.data()) + 0x368);
  ExistingObject* const existing = *existing_slot;
  if (existing != nullptr) {
    ExistingObjectVtable* const existing_vtable = existing->vtable;
    *existing_slot = nullptr;
    existing_vtable->release_04(existing);
  }

  reset_00bc3170(at(tribe, 0x530));
  reset_00bc3170(at(tribe, 0x510));

  auto* const manager = static_cast<TribeManager*>(
      g_native_ports.allocate_00f473a0(0x18, "Simulator", 0, 0, 0x013f09b4, 0));
  if (manager != nullptr) {
    initialize_manager_01062ee0(manager);
  }
  store_u32(tribe, 0x18c8, pointer_word(manager));
  return tribe;
}

Tribe* tribe_create_019e0() {
  void* const memory = g_native_ports.allocate_00f473a0(
      Tribe::kSize, "Simulator/cTribe", 0, 0, 0x0145e3bc, 0);
  if (memory == nullptr) {
    return nullptr;
  }
  return tribe_constructor_00c982a0(static_cast<Tribe*>(memory));
}

void PKG13_C3_THISCALL building_vector_insert_00edafd0(
    BuildingVector* vector, OpaqueBuilding** position,
    OpaqueBuilding** source) {
  OpaqueBuilding* const value = *source;
  if (vector->end != vector->capacity) {
    vector->end = position + 1;
    if (position != nullptr) {
      *position = value;
      if (value != nullptr) {
        building_vtable(value)->add_ref(value);
      }
    }
    return;
  }

  const std::intptr_t old_span = reinterpret_cast<std::intptr_t>(vector->end) -
                                 reinterpret_cast<std::intptr_t>(vector->begin);
  std::int32_t new_count = static_cast<std::int32_t>(old_span >> 2);
  if (new_count == 0) {
    new_count = 1;
  } else {
    new_count *= 2;
  }

  auto* const new_storage =
      static_cast<OpaqueBuilding**>(g_native_ports.allocate_00f473a0(
          static_cast<std::size_t>(new_count) * sizeof(OpaqueBuilding*),
          "Simulator", 0, 0, 0x013ebb38, 0xd1));
  OpaqueBuilding** new_end = new_storage;
  const std::size_t prefix_size =
      static_cast<std::size_t>(reinterpret_cast<std::uint8_t*>(position) -
                               reinterpret_cast<std::uint8_t*>(vector->begin));
  if (prefix_size != 0) {
    std::memcpy(new_storage, vector->begin, prefix_size);
    new_end += prefix_size / sizeof(OpaqueBuilding*);
  }
  *new_end = value;
  if (value != nullptr) {
    building_vtable(value)->add_ref(value);
  }
  ++new_end;
  const std::size_t suffix_size =
      static_cast<std::size_t>(reinterpret_cast<std::uint8_t*>(vector->end) -
                               reinterpret_cast<std::uint8_t*>(position));
  if (suffix_size != 0) {
    std::memcpy(new_end, position, suffix_size);
    new_end += suffix_size / sizeof(OpaqueBuilding*);
  }

  OpaqueBuilding* const* const old_storage = vector->begin;
  if (old_storage != nullptr && old_storage != vector->storage_sentinel_10) {
    g_native_ports.free_00f47380(const_cast<OpaqueBuilding**>(old_storage));
  }
  vector->begin = new_storage;
  vector->end = new_end;
  vector->capacity = new_storage + new_count;
}

extern "C" OpaqueBuilding* PKG13_C3_THISCALL
city_add_building_00be1fb0(OpaqueCity* city) {
  OpaqueNounRoot* const root = g_native_ports.current_root_00b3d300();
  BuildingFactory* const factory =
      g_native_ports.create_factory_00b20c60(root, 0x0436f342u);
  if (factory == nullptr) {
    return nullptr;
  }
  OpaqueBuilding* const building =
      factory->vtable->create_building(factory, 0x0436f315u);
  if (building == nullptr) {
    return nullptr;
  }

  building_vtable(building)->add_ref(building);
  auto* const vector =
      reinterpret_cast<BuildingVector*>(city->bytes.data() + 0x354);
  OpaqueBuilding** const position = vector->end;
  OpaqueBuilding* value = building;
  OpaqueBuilding** const source = &value;
  const std::uintptr_t position_word =
      reinterpret_cast<std::uintptr_t>(position);
  const std::uintptr_t capacity_word =
      reinterpret_cast<std::uintptr_t>(vector->capacity);
  if (position_word < capacity_word) {
    vector->end = position + 1;
    if (position != nullptr) {
      *position = building;
      building_vtable(building)->add_ref(building);
    }
  } else {
    building_vector_insert_00edafd0(vector, position, source);
  }
  building_vtable(building)->release(building);
  g_native_ports.initialize_building_00bd2310(building, city);

  auto* const city_owner =
      reinterpret_cast<OpaqueCityOwner*>(city->bytes.data() + 0x120);
  const std::uint32_t owner_value =
      city_owner->vtable->owner_callback_2c(city_owner);
  auto* const building_owner =
      reinterpret_cast<OpaqueBuildingOwner*>(building->bytes.data() + 0x34);
  building_owner->vtable->owner_callback_38(building_owner, owner_value);
  return building;
}

}

#undef PKG13_C3_THISCALL
