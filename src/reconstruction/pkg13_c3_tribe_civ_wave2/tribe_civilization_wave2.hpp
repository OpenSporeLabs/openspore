#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG13-C3 tribe civilization wave2 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg13_c3_tribe_civ_wave2 {

#if defined(_MSC_VER)
#define PKG13_C3_THISCALL __thiscall
#else
#define PKG13_C3_THISCALL __attribute__((thiscall))
#endif

struct OpaqueBuilding;
struct OpaqueBuildingOwner;
struct OpaqueCity;
struct OpaqueCityOwner;
struct OpaqueNounRoot;
struct BuildingFactory;

using BuildingAddRef = void(PKG13_C3_THISCALL*)(OpaqueBuilding*);
using BuildingRelease = void(PKG13_C3_THISCALL*)(OpaqueBuilding*);
using BuildingCreate = OpaqueBuilding*(PKG13_C3_THISCALL*)(BuildingFactory*,
                                                           std::uint32_t);
using BuildingOwnerCallback = void(PKG13_C3_THISCALL*)(OpaqueBuildingOwner*,
                                                       std::uint32_t);
using CityOwnerCallback = std::uint32_t(PKG13_C3_THISCALL*)(OpaqueCityOwner*);
using ObjectRelease = void(PKG13_C3_THISCALL*)(void*);
using CreateFactory = BuildingFactory*(PKG13_C3_THISCALL*)(OpaqueNounRoot*,
                                                           std::uint32_t);
using InitializeBuilding = void(PKG13_C3_THISCALL*)(OpaqueBuilding*,
                                                    OpaqueCity*);
using InitializePort = void(PKG13_C3_THISCALL*)(void*);
using ReservePort = void(PKG13_C3_THISCALL*)(void*, std::uint32_t);
using CurrentRootPort = OpaqueNounRoot* (*)();
using AllocatePort = void* (*)(std::size_t, const char*, std::uint32_t,
                               std::uint32_t, std::uint32_t, std::uint32_t);
using FreePort = void (*)(void*);

struct alignas(4) Tribe {
  static constexpr std::size_t kSize = 0x19e0;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) TribeManager {
  static constexpr std::size_t kSize = 0x18;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueCity {
  static constexpr std::size_t kSize = 0x368;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueBuilding {
  static constexpr std::size_t kSize = 0x38;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueNounRoot {
  std::array<std::uint8_t, 0x120> bytes;
};

struct BuildingFactoryVtable {
  std::array<void*, 3> opaque_slots;
  BuildingCreate create_building;
};

struct alignas(4) BuildingFactory {
  BuildingFactoryVtable* vtable;
  std::array<std::uint8_t, 0x3c> opaque;
};

struct BuildingVtable {
  BuildingAddRef add_ref;
  BuildingRelease release;
  std::array<void*, 12> opaque_slots;
  BuildingOwnerCallback owner_callback_38;
};

struct alignas(4) OpaqueBuildingOwner {
  BuildingVtable* vtable;
  std::array<std::uint8_t, 4> opaque;
};

struct CityOwnerVtable {
  std::array<void*, 11> opaque_slots;
  CityOwnerCallback owner_callback_2c;
};

struct alignas(4) OpaqueCityOwner {
  CityOwnerVtable* vtable;
  std::array<std::uint8_t, 0x30> opaque;
};

struct ExistingObjectVtable {
  void* opaque_slot_00;
  ObjectRelease release_04;
};

struct alignas(4) ExistingObject {
  ExistingObjectVtable* vtable;
  std::array<std::uint8_t, 4> opaque;
};

struct BuildingVector {
  OpaqueBuilding** begin;
  OpaqueBuilding** end;
  OpaqueBuilding** capacity;
  std::uint32_t opaque_0c;
  OpaqueBuilding** storage_sentinel_10;
};

struct NativePorts {
  InitializePort initialize_00c011c0;
  InitializePort initialize_00c89630;
  InitializePort initialize_00ac03d0;
  InitializePort initialize_00cee630;
  InitializePort initialize_00b6f280;
  InitializePort initialize_00b63890;
  InitializePort initialize_00afba10;
  InitializePort initialize_00cc7e10;
  ReservePort reserve_004548d0;
  CurrentRootPort current_root_00b3d300;
  CreateFactory create_factory_00b20c60;
  InitializeBuilding initialize_building_00bd2310;
  AllocatePort allocate_00f473a0;
  FreePort free_00f47380;
};

extern NativePorts g_native_ports;
extern std::uint32_t g_dat_01485720;

static_assert(sizeof(void*) == 4, "PKG13-C3 pointers are 32-bit");
static_assert(sizeof(Tribe) == 0x19e0, "PKG13-C3 tribe storage size");
static_assert(sizeof(TribeManager) == 0x18, "PKG13-C3 manager storage size");
static_assert(sizeof(OpaqueCity) == 0x368, "PKG13-C3 city storage size");
static_assert(sizeof(BuildingVector) == 0x14, "PKG13-C3 building vector size");
static_assert(offsetof(BuildingFactoryVtable, create_building) == 0x0c,
              "PKG13-C3 factory create slot");
static_assert(offsetof(BuildingVtable, add_ref) == 0x00,
              "PKG13-C3 building AddRef slot");
static_assert(offsetof(BuildingVtable, release) == 0x04,
              "PKG13-C3 building release slot");
static_assert(offsetof(BuildingVtable, owner_callback_38) == 0x38,
              "PKG13-C3 building owner callback slot");
static_assert(offsetof(CityOwnerVtable, owner_callback_2c) == 0x2c,
              "PKG13-C3 city owner callback slot");
static_assert(offsetof(ExistingObjectVtable, release_04) == 0x04,
              "PKG13-C3 existing object release slot");

extern "C" Tribe* PKG13_C3_THISCALL tribe_constructor_00c982a0(Tribe* tribe);
extern "C" OpaqueBuilding* PKG13_C3_THISCALL
city_add_building_00be1fb0(OpaqueCity* city);

Tribe* tribe_create_019e0();
void PKG13_C3_THISCALL building_vector_insert_00edafd0(
    BuildingVector* vector, OpaqueBuilding** position, OpaqueBuilding** source);

}

#undef PKG13_C3_THISCALL
