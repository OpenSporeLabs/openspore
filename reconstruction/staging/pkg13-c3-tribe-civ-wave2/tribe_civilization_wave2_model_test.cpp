#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <string>
#include <vector>

#include "tribe_civilization_wave2.hpp"

#if defined(_MSC_VER)
#define PKG13_C3_TEST_THISCALL __thiscall
#else
#define PKG13_C3_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::pkg13_c3_tribe_civ_wave2;

BuildingFactoryVtable factory_building_vtable{};

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::vector<std::string> trace;
bool fail_tribe_allocation = false;
bool fail_manager_allocation = false;
bool reserve_injects_existing = false;
bool observed_tribe_allocation = false;
bool observed_manager_allocation = false;
bool observed_tribe_source = false;
bool observed_manager_source = false;
const std::uint8_t* active_tribe_bytes = nullptr;
OpaqueNounRoot root;
BuildingFactory factory;
OpaqueBuilding* factory_building_result = nullptr;
OpaqueBuilding* factory_building_next = nullptr;
BuildingFactory* factory_result = &factory;
std::uint32_t city_owner_value = 0x12345678u;
OpaqueCityOwner city_owner;
CityOwnerVtable city_owner_vtable{};
OpaqueBuildingOwner building_owner;
BuildingVtable building_vtable_value{};
ExistingObject existing_object;
ExistingObjectVtable existing_vtable{};
OpaqueBuilding* expected_initialize_building = nullptr;
OpaqueCity* expected_initialize_city = nullptr;
OpaqueCityOwner* expected_city_owner = nullptr;
OpaqueBuildingOwner* expected_building_owner = nullptr;

std::uint32_t load_u32(const void* base, std::size_t offset) {
  std::uint32_t value = 0;
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

void store_pointer(void* base, std::size_t offset, const void* pointer) {
  const auto value =
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
  store_u32(base, offset, value);
}

void expect_trace(std::initializer_list<const char*> expected) {
  check(trace.size() == expected.size());
  std::size_t index = 0;
  for (const char* value : expected) {
    check(trace[index] == value);
    ++index;
  }
}

void PKG13_C3_TEST_THISCALL initialize_00c011c0(void* object) {
  check(object != nullptr);
  trace.emplace_back("initialize-00c011c0");
}

void PKG13_C3_TEST_THISCALL initialize_00c89630(void* object) {
  check(object != nullptr);
  trace.emplace_back("initialize-00c89630:120");
}

void PKG13_C3_TEST_THISCALL initialize_00ac03d0(void* object) {
  check(object != nullptr);
  trace.emplace_back("initialize-00ac03d0:1f4");
}

void PKG13_C3_TEST_THISCALL initialize_00cee630(void* object) {
  check(object != nullptr);
  trace.emplace_back("initialize-00cee630:20c");
}

void PKG13_C3_TEST_THISCALL initialize_00b6f280(void* object) {
  check(object != nullptr);
  trace.emplace_back("initialize-00b6f280:230");
}

void PKG13_C3_TEST_THISCALL initialize_00b63890(void* object) {
  check(active_tribe_bytes != nullptr);
  const auto offset = static_cast<std::size_t>(
      static_cast<std::uint8_t*>(object) - active_tribe_bytes);
  if (offset == 0x270u) {
    trace.emplace_back("initialize-00b63890:270");
  } else if (offset == 0x510u) {
    trace.emplace_back("initialize-00b63890:510");
  } else {
    check(offset == 0x530u);
    trace.emplace_back("initialize-00b63890:530");
  }
}

void PKG13_C3_TEST_THISCALL initialize_00afba10(void* object) {
  check(object != nullptr);
  trace.emplace_back("initialize-00afba10:3b4");
}

void PKG13_C3_TEST_THISCALL initialize_00cc7e10(void* object) {
  check(object != nullptr);
  trace.emplace_back("initialize-00cc7e10:558");
}

void PKG13_C3_TEST_THISCALL reserve_004548d0(void* object,
                                             std::uint32_t count) {
  check(active_tribe_bytes != nullptr);
  check(object == active_tribe_bytes + 0x1904);
  check(count == 14);
  if (reserve_injects_existing) {
    store_pointer(const_cast<std::uint8_t*>(active_tribe_bytes), 0x368,
                  &existing_object);
  }
  trace.emplace_back("reserve-004548d0:1904:14");
}

OpaqueNounRoot* current_root_00b3d300() {
  trace.emplace_back("current-root-00b3d300");
  return &root;
}

BuildingFactory* PKG13_C3_TEST_THISCALL
create_factory_00b20c60(OpaqueNounRoot* receiver, std::uint32_t key) {
  check(receiver == &root);
  check(key == 0x0436f342u);
  trace.emplace_back("create-factory-00b20c60:436f342");
  return factory_result;
}

OpaqueBuilding* PKG13_C3_TEST_THISCALL
create_building_00c(BuildingFactory* receiver, std::uint32_t key) {
  check(receiver == &factory);
  check(key == 0x0436f315u);
  trace.emplace_back("create-building:436f315");
  return factory_building_result;
}

void PKG13_C3_TEST_THISCALL building_add_ref(OpaqueBuilding* building) {
  check(building == factory_building_result);
  trace.emplace_back("building-add-ref");
}

void PKG13_C3_TEST_THISCALL building_release(OpaqueBuilding* building) {
  check(building == factory_building_result);
  trace.emplace_back("building-release");
}

std::uint32_t PKG13_C3_TEST_THISCALL
city_owner_callback(OpaqueCityOwner* owner) {
  check(owner == expected_city_owner);
  trace.emplace_back("city-owner-callback:2c");
  return city_owner_value;
}

void PKG13_C3_TEST_THISCALL building_owner_callback(OpaqueBuildingOwner* owner,
                                                    std::uint32_t value) {
  check(owner == expected_building_owner);
  char entry[80];
  std::snprintf(entry, sizeof(entry), "building-owner-callback:38:%08x", value);
  trace.emplace_back(entry);
}

void PKG13_C3_TEST_THISCALL
initialize_building_00bd2310(OpaqueBuilding* building, OpaqueCity* city) {
  check(building == expected_initialize_building);
  check(city == expected_initialize_city);
  trace.emplace_back("initialize-building-00bd2310");
}

void PKG13_C3_TEST_THISCALL release_existing(void* object) {
  check(object == &existing_object);
  trace.emplace_back("release-existing:04");
}

void* allocate_00f473a0(std::size_t size, const char* domain,
                        std::uint32_t value0, std::uint32_t value1,
                        std::uint32_t source, std::uint32_t line) {
  check(domain != nullptr);
  check(value0 == 0);
  check(value1 == 0);
  if (size == Tribe::kSize) {
    observed_tribe_allocation = true;
    observed_tribe_source = source == 0x0145e3bcu && line == 0;
    trace.emplace_back("allocate-00f473a0:tribe");
    if (fail_tribe_allocation) {
      return nullptr;
    }
  } else if (size == TribeManager::kSize) {
    observed_manager_allocation = true;
    observed_manager_source = source == 0x013f09b4u && line == 0;
    trace.emplace_back("allocate-00f473a0:manager");
    if (fail_manager_allocation) {
      return nullptr;
    }
  } else {
    check(source == 0x013ebb38u);
    check(line == 0xd1u);
    char entry[80];
    std::snprintf(entry, sizeof(entry), "allocate-00f473a0:vector:%zu", size);
    trace.emplace_back(entry);
  }
  void* const memory = std::malloc(size);
  check(memory != nullptr);
  std::memset(memory, 0xa5, size);
  if (size == Tribe::kSize) {
    active_tribe_bytes = static_cast<std::uint8_t*>(memory);
  }
  return memory;
}

void free_00f47380(void* pointer) {
  check(pointer != nullptr);
  trace.emplace_back("free-00f47380");
  std::free(pointer);
}

void install_constructor_ports() {
  g_native_ports = {};
  g_native_ports.initialize_00c011c0 = initialize_00c011c0;
  g_native_ports.initialize_00c89630 = initialize_00c89630;
  g_native_ports.initialize_00ac03d0 = initialize_00ac03d0;
  g_native_ports.initialize_00cee630 = initialize_00cee630;
  g_native_ports.initialize_00b6f280 = initialize_00b6f280;
  g_native_ports.initialize_00b63890 = initialize_00b63890;
  g_native_ports.initialize_00afba10 = initialize_00afba10;
  g_native_ports.initialize_00cc7e10 = initialize_00cc7e10;
  g_native_ports.reserve_004548d0 = reserve_004548d0;
  g_native_ports.allocate_00f473a0 = allocate_00f473a0;
  g_native_ports.free_00f47380 = free_00f47380;
}

void install_add_building_ports() {
  g_native_ports = {};
  g_native_ports.current_root_00b3d300 = current_root_00b3d300;
  g_native_ports.create_factory_00b20c60 = create_factory_00b20c60;
  g_native_ports.initialize_building_00bd2310 = initialize_building_00bd2310;
  g_native_ports.allocate_00f473a0 = allocate_00f473a0;
  g_native_ports.free_00f47380 = free_00f47380;
}

void reset_constructor_fixture() {
  trace.clear();
  fail_tribe_allocation = false;
  fail_manager_allocation = false;
  reserve_injects_existing = false;
  observed_tribe_allocation = false;
  observed_manager_allocation = false;
  observed_tribe_source = false;
  observed_manager_source = false;
  active_tribe_bytes = nullptr;
  existing_object = {};
  existing_object.vtable = &existing_vtable;
  existing_vtable.opaque_slot_00 = nullptr;
  existing_vtable.release_04 = release_existing;
  install_constructor_ports();
}

void reset_add_building_fixture() {
  trace.clear();
  fail_tribe_allocation = false;
  fail_manager_allocation = false;
  reserve_injects_existing = false;
  factory_result = &factory;
  factory_building_result = nullptr;
  factory_building_next = nullptr;
  expected_initialize_building = nullptr;
  expected_initialize_city = nullptr;
  expected_city_owner = nullptr;
  expected_building_owner = nullptr;
  city_owner_value = 0x12345678u;
  city_owner = {};
  city_owner.vtable = &city_owner_vtable;
  city_owner_vtable = {};
  city_owner_vtable.owner_callback_2c = city_owner_callback;
  building_owner = {};
  building_owner.vtable = &building_vtable_value;
  building_vtable_value = {};
  building_vtable_value.add_ref = building_add_ref;
  building_vtable_value.release = building_release;
  building_vtable_value.owner_callback_38 = building_owner_callback;
  factory = {};
  factory.vtable = nullptr;
  install_add_building_ports();
}

void configure_building(OpaqueBuilding* building) {
  building->bytes.fill(0);
  store_pointer(building->bytes.data(), 0x00, &building_vtable_value);
  store_pointer(building->bytes.data(), 0x34, &building_vtable_value);
  expected_building_owner =
      reinterpret_cast<OpaqueBuildingOwner*>(building->bytes.data() + 0x34);
}

struct WordExpectation {
  std::size_t offset;
  std::uint32_t value;
};

void verify_constructor_fields(const Tribe& tribe, std::uint32_t manager_word) {
  check(g_dat_01485720 == 0x3f800000u);
  const std::uint32_t max = std::numeric_limits<std::uint32_t>::max();
  const auto pointer = reinterpret_cast<std::uintptr_t>(&tribe);
  const WordExpectation words[] = {
      {0x000, 0x1473e58u},
      {0x004, 0x1473e44u},
      {0x034, 0x1469cc0u},
      {0x120, 0x1473d80u},
      {0x1f4, 0x1473d64u},
      {0x20c, 0x1473d20u},
      {0x230, 0x1473d00u},
      {0x260, 0},
      {0x268, 0x41200000u},
      {0x26c, max},
      {0x290, 0},
      {0x294, 0},
      {0x298, 0},
      {0x29c, 0},
      {0x2a8, 0},
      {0x2ac, 0},
      {0x2b0, 0},
      {0x2bc, max},
      {0x2c0, 0},
      {0x2c4, 0},
      {0x2c8, 0},
      {0x2cc, 0},
      {0x2d0, 0},
      {0x2d4, 0},
      {0x2d8, 0},
      {0x304, 0},
      {0x308, 0},
      {0x30c, 0},
      {0x310, 0},
      {0x314, 0},
      {0x318, 0},
      {0x31c, 0},
      {0x328, 2},
      {0x330, 0x3f800000u},
      {0x338, 0},
      {0x340, 0},
      {0x344, 0},
      {0x348, 0},
      {0x354, 0},
      {0x358, 0},
      {0x35c, 0},
      {0x368, 0},
      {0x36c, 0},
      {0x370, 0},
      {0x374, 0},
      {0x380, 0},
      {0x384, 0},
      {0x388, 0},
      {0x398, 0x154df28u},
      {0x39c, 1},
      {0x3a0, 0},
      {0x3ac, 0},
      {0x3a4, 0x40000000u},
      {0x3a8, 0x40000000u},
      {0x418, pointer + 0x430u},
      {0x41c, pointer + 0x430u},
      {0x420, pointer + 0x4e4u},
      {0x42c, 0},
      {0x4e8, 0x154df28u},
      {0x4ec, 1},
      {0x4f0, 0},
      {0x4f4, 0x3f800000u},
      {0x4f8, 0x40000000u},
      {0x4fc, 0},
      {0x518, 0},
      {0x51c, 0},
      {0x520, 0},
      {0x524, 0},
      {0x538, 0},
      {0x53c, 0},
      {0x540, 0},
      {0x544, 0},
      {0x550, 0},
      {0x1868, 0},
      {0x186c, 0},
      {0x1870, 0},
      {0x1874, max},
      {0x1880, 0},
      {0x1884, 0},
      {0x1888, 0},
      {0x188c, max},
      {0x1898, 0},
      {0x189c, 0},
      {0x18a0, 0},
      {0x18a4, max},
      {0x18b0, 0},
      {0x18b4, 0},
      {0x18b8, 0},
      {0x18bc, max},
      {0x18c4, 0},
      {0x18c8, manager_word},
      {0x18cc, 0},
      {0x18d0, 0},
      {0x18d4, 0},
      {0x18d8, 0},
      {0x1904, pointer + 0x191c},
      {0x1908, pointer + 0x191c},
      {0x190c, pointer + 0x19c4},
      {0x1918, 0},
      {0x19c4, 0},
      {0x19c8, 0},
      {0x19cc, 0},
      {0x19d0, 0},
      {0x19d4, 0},
      {0x19d8, 0},
  };
  for (const WordExpectation& expected : words) {
    const std::uint32_t actual = load_u32(tribe.bytes.data(), expected.offset);
    if (actual != expected.value) {
      std::fprintf(stderr, "offset=%#x expected=%#x actual=%#x\n",
                   static_cast<unsigned>(expected.offset), expected.value,
                   actual);
    }
    check(actual == expected.value);
  }
  const std::size_t bytes[] = {0x264,  0x300,  0x301,  0x334,  0x33c,
                               0x528,  0x548,  0x554,  0x555,  0x556,
                               0x557,  0x1878, 0x1879, 0x1890, 0x1891,
                               0x18a8, 0x18a9, 0x18c0, 0x18c1};
  for (const std::size_t offset : bytes) {
    check(load_u8(tribe.bytes.data(), offset) == 0);
  }
  for (std::size_t offset = 0x18cc; offset < 0x1904; ++offset) {
    check(load_u8(tribe.bytes.data(), offset) == 0);
  }
  check(load_u8(tribe.bytes.data(), 0x548) == 0);
  check(load_u8(tribe.bytes.data(), 0x008) == 0xa5);
}

void verify_manager(const std::uint32_t word) {
  if (word == 0) {
    return;
  }
  auto* const manager = reinterpret_cast<TribeManager*>(word);
  check(load_u32(manager->bytes.data(), 0x00) == 0);
  check(load_u32(manager->bytes.data(), 0x04) ==
        std::numeric_limits<std::uint32_t>::max());
  check(load_u8(manager->bytes.data(), 0x08) == 0xa5);
}

void test_constructor_success_and_outer_allocation() {
  reset_constructor_fixture();
  Tribe* const tribe = tribe_create_019e0();
  check(tribe != nullptr);
  check(observed_tribe_allocation);
  check(observed_manager_allocation);
  check(observed_tribe_source);
  check(observed_manager_source);
  const std::uint32_t manager_word = load_u32(tribe->bytes.data(), 0x18c8);
  verify_constructor_fields(*tribe, manager_word);
  verify_manager(manager_word);
  expect_trace({"allocate-00f473a0:tribe", "initialize-00c011c0",
                "initialize-00c89630:120", "initialize-00ac03d0:1f4",
                "initialize-00cee630:20c", "initialize-00b6f280:230",
                "initialize-00b63890:270", "initialize-00afba10:3b4",
                "initialize-00b63890:510", "initialize-00b63890:530",
                "initialize-00cc7e10:558", "reserve-004548d0:1904:14",
                "allocate-00f473a0:manager"});
  free_00f47380(
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(manager_word)));
  std::free(tribe);
}

void test_outer_allocation_failure() {
  reset_constructor_fixture();
  fail_tribe_allocation = true;
  check(tribe_create_019e0() == nullptr);
  expect_trace({"allocate-00f473a0:tribe"});
  check(!observed_manager_allocation);
}

void test_manager_allocation_failure_preserves_tribe() {
  reset_constructor_fixture();
  fail_manager_allocation = true;
  Tribe tribe;
  tribe.bytes.fill(0xa5);
  active_tribe_bytes = tribe.bytes.data();
  check(tribe_constructor_00c982a0(&tribe) == &tribe);
  check(observed_manager_allocation);
  check(observed_manager_source);
  verify_constructor_fields(tribe, 0);
}

void test_constructor_existing_release_branch() {
  reset_constructor_fixture();
  reserve_injects_existing = true;
  Tribe tribe;
  tribe.bytes.fill(0xa5);
  active_tribe_bytes = tribe.bytes.data();
  check(tribe_constructor_00c982a0(&tribe) == &tribe);
  const std::uint32_t manager_word = load_u32(tribe.bytes.data(), 0x18c8);
  verify_constructor_fields(tribe, manager_word);
  verify_manager(manager_word);
  check(trace.size() == 13);
  check(trace[10] == "reserve-004548d0:1904:14");
  check(trace[11] == "release-existing:04");
  check(trace[12] == "allocate-00f473a0:manager");
  free_00f47380(
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(manager_word)));
}

void configure_city(OpaqueCity& city, OpaqueBuilding** entries,
                    OpaqueBuilding** begin, OpaqueBuilding** end,
                    OpaqueBuilding** capacity) {
  city.bytes.fill(0);
  store_pointer(city.bytes.data(), 0x120, &city_owner_vtable);
  expected_city_owner =
      reinterpret_cast<OpaqueCityOwner*>(city.bytes.data() + 0x120);
  auto* const vector =
      reinterpret_cast<BuildingVector*>(city.bytes.data() + 0x354);
  vector->begin = begin;
  vector->end = end;
  vector->capacity = capacity;
  vector->opaque_0c = 0;
  vector->storage_sentinel_10 = nullptr;
  (void)entries;
}

void test_add_building_empty_vector_and_return_identity() {
  reset_add_building_fixture();
  OpaqueBuilding building;
  configure_building(&building);
  factory_building_result = &building;
  factory.vtable =
      reinterpret_cast<BuildingFactoryVtable*>(&factory_building_vtable);
  OpaqueCity city;
  OpaqueBuilding* entries[4]{};
  configure_city(city, entries, entries, entries, entries + 4);
  expected_initialize_building = &building;
  expected_initialize_city = &city;
  Tribe tribe;
  tribe.bytes.fill(0x5a);
  std::uint32_t population_state = 0x10203040u;
  std::uint32_t persistence_state = 0x50607080u;

  check(city_add_building_00be1fb0(&city) == &building);
  auto* const vector =
      reinterpret_cast<BuildingVector*>(city.bytes.data() + 0x354);
  check(vector->begin == entries);
  check(vector->end == entries + 1);
  check(vector->capacity == entries + 4);
  check(entries[0] == &building);
  check(population_state == 0x10203040u);
  check(persistence_state == 0x50607080u);
  for (const std::uint8_t byte : tribe.bytes) {
    check(byte == 0x5a);
  }
  expect_trace({"current-root-00b3d300", "create-factory-00b20c60:436f342",
                "create-building:436f315", "building-add-ref",
                "building-add-ref", "building-release",
                "initialize-building-00bd2310", "city-owner-callback:2c",
                "building-owner-callback:38:12345678"});
}

void test_add_building_existing_capacity_preserves_order() {
  reset_add_building_fixture();
  OpaqueBuilding first;
  OpaqueBuilding second;
  configure_building(&first);
  configure_building(&second);
  factory_building_result = &second;
  factory.vtable =
      reinterpret_cast<BuildingFactoryVtable*>(&factory_building_vtable);
  OpaqueCity city;
  OpaqueBuilding* entries[4]{&first, nullptr, nullptr, nullptr};
  configure_city(city, entries, entries, entries + 1, entries + 4);
  expected_initialize_building = &second;
  expected_initialize_city = &city;

  check(city_add_building_00be1fb0(&city) == &second);
  auto* const vector =
      reinterpret_cast<BuildingVector*>(city.bytes.data() + 0x354);
  check(vector->begin[0] == &first);
  check(vector->begin[1] == &second);
  check(vector->end == entries + 2);
  expect_trace({"current-root-00b3d300", "create-factory-00b20c60:436f342",
                "create-building:436f315", "building-add-ref",
                "building-add-ref", "building-release",
                "initialize-building-00bd2310", "city-owner-callback:2c",
                "building-owner-callback:38:12345678"});
}

void test_add_building_vector_growth() {
  reset_add_building_fixture();
  OpaqueBuilding first;
  OpaqueBuilding second;
  configure_building(&first);
  configure_building(&second);
  factory_building_result = &second;
  factory.vtable =
      reinterpret_cast<BuildingFactoryVtable*>(&factory_building_vtable);
  OpaqueCity city;
  auto* const entries =
      static_cast<OpaqueBuilding**>(std::malloc(sizeof(OpaqueBuilding*)));
  check(entries != nullptr);
  entries[0] = &first;
  configure_city(city, entries, entries, entries + 1, entries + 1);
  expected_initialize_building = &second;
  expected_initialize_city = &city;

  check(city_add_building_00be1fb0(&city) == &second);
  auto* const vector =
      reinterpret_cast<BuildingVector*>(city.bytes.data() + 0x354);
  check(vector->begin != entries);
  check(vector->capacity == vector->begin + 2);
  check(vector->end == vector->begin + 2);
  check(vector->begin[0] == &first);
  check(vector->begin[1] == &second);
  expect_trace({"current-root-00b3d300", "create-factory-00b20c60:436f342",
                "create-building:436f315", "building-add-ref",
                "allocate-00f473a0:vector:8", "building-add-ref",
                "free-00f47380", "building-release",
                "initialize-building-00bd2310", "city-owner-callback:2c",
                "building-owner-callback:38:12345678"});
  free_00f47380(vector->begin);
}

void test_add_building_growth_from_empty_null_storage() {
  reset_add_building_fixture();
  OpaqueBuilding building;
  configure_building(&building);
  factory_building_result = &building;
  factory.vtable =
      reinterpret_cast<BuildingFactoryVtable*>(&factory_building_vtable);
  OpaqueCity city;
  configure_city(city, nullptr, nullptr, nullptr, nullptr);
  expected_initialize_building = &building;
  expected_initialize_city = &city;

  check(city_add_building_00be1fb0(&city) == &building);
  auto* const vector =
      reinterpret_cast<BuildingVector*>(city.bytes.data() + 0x354);
  check(vector->begin != nullptr);
  check(vector->capacity == vector->begin + 1);
  check(vector->end == vector->begin + 1);
  check(vector->begin[0] == &building);
  expect_trace({"current-root-00b3d300", "create-factory-00b20c60:436f342",
                "create-building:436f315", "building-add-ref",
                "allocate-00f473a0:vector:4", "building-add-ref",
                "building-release", "initialize-building-00bd2310",
                "city-owner-callback:2c",
                "building-owner-callback:38:12345678"});
  free_00f47380(vector->begin);
}

void test_factory_failures_leave_city_unchanged() {
  reset_add_building_fixture();
  OpaqueCity city;
  OpaqueBuilding* entries[2]{};
  configure_city(city, entries, entries, entries, entries + 2);
  const auto before = city.bytes;

  factory_result = nullptr;
  check(city_add_building_00be1fb0(&city) == nullptr);
  expect_trace({"current-root-00b3d300", "create-factory-00b20c60:436f342"});

  trace.clear();
  factory_result = &factory;
  factory.vtable =
      reinterpret_cast<BuildingFactoryVtable*>(&factory_building_vtable);
  factory_building_result = nullptr;
  check(city_add_building_00be1fb0(&city) == nullptr);
  expect_trace({"current-root-00b3d300", "create-factory-00b20c60:436f342",
                "create-building:436f315"});
  check(city.bytes == before);
}

}

int main() {
  factory_building_vtable.create_building = create_building_00c;
  test_constructor_success_and_outer_allocation();
  test_outer_allocation_failure();
  test_manager_allocation_failure_preserves_tribe();
  test_constructor_existing_release_branch();
  test_add_building_empty_vector_and_return_identity();
  test_add_building_existing_capacity_preserves_order();
  test_add_building_vector_growth();
  test_add_building_growth_from_empty_null_storage();
  test_factory_failures_leave_city_unchanged();
}

#undef PKG13_C3_TEST_THISCALL
