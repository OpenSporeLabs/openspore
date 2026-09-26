#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg14-a3-world-wave3 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG14_A3_THISCALL __thiscall
#else
#define PKG14_A3_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg14_a3_world_wave3 {

using TargetWord = std::uint32_t;

struct OpaquePlanetType {
  std::array<std::uint8_t, 0x4c> opaque_00_4b;
};

struct OpaqueStar {
  std::array<std::uint8_t, 0x34> opaque_00_33;
  TargetWord primary_type_34;
  TargetWord secondary_type_38;
  std::array<std::uint8_t, 0x0c> opaque_3c_47;
  OpaquePlanetType* type_service_48;
};

struct OpaqueName {
  const char* data_00;
  TargetWord size_04;
};

struct OpaquePlanet {
  std::array<std::uint8_t, 0x2c> opaque_00_2b;
  TargetWord radius_flags_2c;
  std::array<std::uint8_t, 0x08> opaque_30_37;
  std::uint8_t body_kind_38;
  std::array<std::uint8_t, 0x67> opaque_39_9f;
  TargetWord transform_a0;
  TargetWord transform_a4;
  TargetWord transform_a8;
  float angular_scale_ac;
  OpaqueName name_b0;
  std::array<std::uint8_t, 0x10> opaque_b8_c7;
  float radius_c8;
};

struct OpaquePlanetVector {
  OpaquePlanet** begin;
  OpaquePlanet** end;
  OpaquePlanet** capacity;
};

struct OpaqueSolarSystem {
  std::array<std::uint8_t, 0x0c> opaque_00_0b;
  OpaqueStar* owner_star_0c;
  OpaquePlanetVector planet_vector_10;
  std::array<std::uint8_t, 0x08> opaque_1c_23;
  OpaquePlanetVector primary_vector_24;
  std::array<std::uint8_t, 0x08> opaque_30_37;
  OpaquePlanet* primary_38;
};

struct OpaquePlanetManager {
  std::array<std::uint8_t, 0x14> opaque_00_13;
};

struct OpaqueRenderHelper {
  std::array<std::uint8_t, 0x10> opaque_00_0f;
};

using LoadBinaryOrAsteroidSystem = void(PKG14_A3_THISCALL*)(OpaqueSolarSystem*);
using LoadAsteroidBelt = void(PKG14_A3_THISCALL*)(OpaqueSolarSystem*);
using IsBinaryOrAsteroid = bool(PKG14_A3_THISCALL*)(OpaqueStar*);
using IsAsteroidSystem = bool(PKG14_A3_THISCALL*)(OpaqueStar*);
using StarTypeIndex = TargetWord(PKG14_A3_THISCALL*)(OpaqueStar*);
using StarName = OpaqueName*(PKG14_A3_THISCALL*)(OpaqueStar*);
using StarAngularScale = float (*)(TargetWord);
using StarRadius = float (*)(TargetWord);
using StarOrbitScale = float (*)(TargetWord);
using BinaryOrAsteroidRadius = float (*)(TargetWord);
using IsBinaryOrAsteroidType = bool (*)(TargetWord);
using AllocateCelestialBody = void* (*)(TargetWord, const char*, TargetWord,
                                        TargetWord, TargetWord, TargetWord);
using ConstructCelestialBody = OpaquePlanet*(PKG14_A3_THISCALL*)(void*,
                                                                 TargetWord);
using PlanetCall = void(PKG14_A3_THISCALL*)(OpaquePlanet*);
using PlanetRetain = void(PKG14_A3_THISCALL*)(OpaquePlanet*);
using PlanetRelease = void(PKG14_A3_THISCALL*)(OpaquePlanet*);
using CopyName = void(PKG14_A3_THISCALL*)(OpaqueName*, const char*, TargetWord);
using CurrentPlanetManager = OpaquePlanetManager* (*)();
using MaterializePlanet = void(PKG14_A3_THISCALL*)(OpaquePlanetManager*,
                                                   OpaquePlanet*,
                                                   OpaquePlanet**);
using ListPlanets = OpaquePlanetVector* (*)();
using GrowPlanetVector = void(PKG14_A3_THISCALL*)(OpaquePlanetVector*,
                                                  OpaquePlanet**,
                                                  OpaquePlanet**);
using DistanceSample = float (*)(TargetWord);

struct SolarLoadPorts {
  LoadBinaryOrAsteroidSystem load_binary_or_asteroid;
  LoadAsteroidBelt load_asteroid_belt;
  IsBinaryOrAsteroid is_binary_or_asteroid;
  IsAsteroidSystem is_asteroid_system;
  StarTypeIndex star_type;
  StarName star_name;
  StarAngularScale star_angular_scale;
  StarRadius star_radius;
  StarOrbitScale star_orbit_scale;
  BinaryOrAsteroidRadius binary_or_asteroid_radius;
  IsBinaryOrAsteroidType is_binary_or_asteroid_type;
  AllocateCelestialBody allocate_celestial_body;
  ConstructCelestialBody construct_celestial_body;
  PlanetCall planet_call_00;
  PlanetCall planet_call_04;
  PlanetRetain planet_retain_bc;
  PlanetRelease planet_release_c0;
  CopyName copy_name;
  CurrentPlanetManager current_planet_manager;
  MaterializePlanet materialize_planet;
  ListPlanets list_planets;
  GrowPlanetVector grow_primary_vector;
  GrowPlanetVector grow_planet_vector;
  DistanceSample distance_sample;
};

extern TargetWord g_solar_load_transform_01694c10;
extern TargetWord g_solar_load_transform_01694c14;
extern TargetWord g_solar_load_transform_01694c18;
extern std::array<float, 32> g_solar_load_radius_cache_01579d10;

using RenderSample = float(PKG14_A3_THISCALL*)(OpaqueRenderHelper*);

struct SphereDrawPorts {
  RenderSample render_sample;
};

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaquePlanetType) == 0x4c, "planet type extent");
static_assert(offsetof(OpaqueStar, primary_type_34) == 0x34,
              "primary type offset");
static_assert(offsetof(OpaqueStar, secondary_type_38) == 0x38,
              "secondary type offset");
static_assert(offsetof(OpaqueStar, type_service_48) == 0x48,
              "type service offset");
static_assert(sizeof(OpaqueName) == 0x08, "opaque name extent");
static_assert(offsetof(OpaquePlanet, radius_flags_2c) == 0x2c,
              "radius flags offset");
static_assert(offsetof(OpaquePlanet, body_kind_38) == 0x38, "body kind offset");
static_assert(offsetof(OpaquePlanet, transform_a0) == 0xa0,
              "body transform offset");
static_assert(offsetof(OpaquePlanet, angular_scale_ac) == 0xac,
              "angular scale offset");
static_assert(offsetof(OpaquePlanet, name_b0) == 0xb0, "body name offset");
static_assert(offsetof(OpaquePlanet, radius_c8) == 0xc8, "body radius offset");
static_assert(sizeof(OpaquePlanet) == 0xcc, "celestial body extent");
static_assert(sizeof(OpaquePlanetVector) == 0x0c,
              "celestial body vector extent");
static_assert(offsetof(OpaqueSolarSystem, owner_star_0c) == 0x0c,
              "owner star offset");
static_assert(offsetof(OpaqueSolarSystem, planet_vector_10) == 0x10,
              "planet vector offset");
static_assert(offsetof(OpaqueSolarSystem, primary_vector_24) == 0x24,
              "primary vector offset");
static_assert(offsetof(OpaqueSolarSystem, primary_38) == 0x38,
              "primary body offset");
static_assert(sizeof(OpaqueSolarSystem) == 0x3c, "solar system extent");
static_assert(sizeof(std::array<float, 32>) == 0x80,
              "live radius cache extent");

SolarLoadPorts& solar_load_ports();
SphereDrawPorts& sphere_draw_ports();

void PKG14_A3_THISCALL solar_system_load_00c86760(OpaqueSolarSystem* system,
                                                  OpaqueStar* star);
void sphere_draw_direction_00b7e560(float* direction);

}

#undef PKG14_A3_THISCALL
