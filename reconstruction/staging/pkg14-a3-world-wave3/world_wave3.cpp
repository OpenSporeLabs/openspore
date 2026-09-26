#include "world_wave3.hpp"

#include <cmath>

namespace openspore::reconstruction::pkg14_a3_world_wave3 {

#if defined(_MSC_VER)
#define PKG14_A3_THISCALL __thiscall
#else
#define PKG14_A3_THISCALL __attribute__((thiscall))
#endif

namespace {

void PKG14_A3_THISCALL default_load_binary_or_asteroid(OpaqueSolarSystem*) {}

void PKG14_A3_THISCALL default_load_asteroid_belt(OpaqueSolarSystem*) {}

bool PKG14_A3_THISCALL default_is_binary_or_asteroid(OpaqueStar*) {
  return false;
}

bool PKG14_A3_THISCALL default_is_asteroid_system(OpaqueStar*) { return false; }

TargetWord PKG14_A3_THISCALL default_star_type(OpaqueStar*) { return 0; }

OpaqueName* PKG14_A3_THISCALL default_star_name(OpaqueStar*) { return nullptr; }

float default_star_angular_scale(TargetWord) { return 1.0F; }

float default_star_radius(TargetWord) { return 0.0F; }

float default_star_orbit_scale(TargetWord) { return 1.0F; }

float default_binary_or_asteroid_radius(TargetWord) { return 0.0F; }

bool default_is_binary_or_asteroid_type(TargetWord) { return false; }

void* default_allocate_celestial_body(TargetWord, const char*, TargetWord,
                                      TargetWord, TargetWord, TargetWord) {
  return nullptr;
}

OpaquePlanet* PKG14_A3_THISCALL
default_construct_celestial_body(void* allocation, TargetWord) {
  return static_cast<OpaquePlanet*>(allocation);
}

void PKG14_A3_THISCALL default_planet_call_00(OpaquePlanet*) {}

void PKG14_A3_THISCALL default_planet_call_04(OpaquePlanet*) {}

void PKG14_A3_THISCALL default_planet_retain_bc(OpaquePlanet*) {}

void PKG14_A3_THISCALL default_planet_release_c0(OpaquePlanet*) {}

void PKG14_A3_THISCALL default_copy_name(OpaqueName* destination,
                                         const char* data, TargetWord size) {
  destination->data_00 = data;
  destination->size_04 = size;
}

OpaquePlanetManager* default_current_planet_manager() { return nullptr; }

void PKG14_A3_THISCALL default_materialize_planet(OpaquePlanetManager*,
                                                  OpaquePlanet*,
                                                  OpaquePlanet** output) {
  *output = nullptr;
}

OpaquePlanetVector* default_list_planets() {
  static OpaquePlanetVector empty{};
  return &empty;
}

void PKG14_A3_THISCALL default_grow_primary_vector(OpaquePlanetVector*,
                                                   OpaquePlanet**,
                                                   OpaquePlanet**) {}

void PKG14_A3_THISCALL default_grow_planet_vector(OpaquePlanetVector*,
                                                  OpaquePlanet**,
                                                  OpaquePlanet**) {}

float default_distance_sample(TargetWord) { return 0.0F; }

float clamp_unit_sample(float sample) {
  float value = sample + sample - 1.0F;
  if (value < 1.0F) {
    if (value < -1.0F) {
      value = -1.0F;
    }
    return value;
  }
  return 1.0F;
}

float PKG14_A3_THISCALL default_render_sample(OpaqueRenderHelper*) {
  return 0.0F;
}

void append_primary_planet(OpaqueSolarSystem* system) {
  auto& ports = solar_load_ports();
  auto& vector = system->primary_vector_24;
  if (vector.end < vector.capacity) {
    OpaquePlanet** const cursor = vector.end;
    vector.end = cursor + 1;
    if (cursor != nullptr) {
      *cursor = system->primary_38;
      if (system->primary_38 != nullptr) {
        ports.planet_call_00(system->primary_38);
      }
    }
    return;
  }
  ports.grow_primary_vector(&vector, vector.end, &system->primary_38);
}

OpaquePlanet* append_materialized_planet(OpaqueSolarSystem* system,
                                         OpaquePlanet* planet) {
  auto& ports = solar_load_ports();
  auto& vector = system->planet_vector_10;
  if (vector.end < vector.capacity) {
    OpaquePlanet** const cursor = vector.end;
    vector.end = cursor + 1;
    if (cursor != nullptr) {
      *cursor = planet;
      if (planet != nullptr) {
        ports.planet_retain_bc(planet);
      }
    }
    return planet;
  }
  OpaquePlanet* value = planet;
  ports.grow_planet_vector(&vector, vector.end, &value);
  return value;
}

float load_cached_radius(TargetWord type) {
  auto& ports = solar_load_ports();
  float& cached = g_solar_load_radius_cache_01579d10[type];
  if (cached <= 0.0F && cached != 0.0F) {
    cached = ports.is_binary_or_asteroid_type(type)
                 ? ports.binary_or_asteroid_radius(type)
                 : ports.star_radius(type);
  }
  return cached;
}

}

TargetWord g_solar_load_transform_01694c10{};
TargetWord g_solar_load_transform_01694c14{};
TargetWord g_solar_load_transform_01694c18{};
std::array<float, 32> g_solar_load_radius_cache_01579d10{};

SolarLoadPorts& solar_load_ports() {
  static SolarLoadPorts ports{default_load_binary_or_asteroid,
                              default_load_asteroid_belt,
                              default_is_binary_or_asteroid,
                              default_is_asteroid_system,
                              default_star_type,
                              default_star_name,
                              default_star_angular_scale,
                              default_star_radius,
                              default_star_orbit_scale,
                              default_binary_or_asteroid_radius,
                              default_is_binary_or_asteroid_type,
                              default_allocate_celestial_body,
                              default_construct_celestial_body,
                              default_planet_call_00,
                              default_planet_call_04,
                              default_planet_retain_bc,
                              default_planet_release_c0,
                              default_copy_name,
                              default_current_planet_manager,
                              default_materialize_planet,
                              default_list_planets,
                              default_grow_primary_vector,
                              default_grow_planet_vector,
                              default_distance_sample};
  return ports;
}

SphereDrawPorts& sphere_draw_ports() {
  static SphereDrawPorts ports{default_render_sample};
  return ports;
}

void PKG14_A3_THISCALL solar_system_load_00c86760(OpaqueSolarSystem* system,
                                                  OpaqueStar* star) {
  auto& ports = solar_load_ports();
  system->owner_star_0c = star;

  const bool binary_or_asteroid = ports.is_binary_or_asteroid(star);
  if (binary_or_asteroid) {
    ports.load_binary_or_asteroid(system);
  } else {
    if (system->primary_38 == nullptr) {
      void* const allocation = ports.allocate_celestial_body(
          0xcc, "Simulator/cCelestialBody", 0, 0, 0, 0);
      OpaquePlanet* const created =
          allocation == nullptr ? nullptr
                                : ports.construct_celestial_body(allocation, 0);
      OpaquePlanet* const previous = system->primary_38;
      if (created != previous) {
        if (created != nullptr) {
          ports.planet_call_00(created);
        }
        system->primary_38 = created;
        if (previous != nullptr) {
          ports.planet_call_04(previous);
        }
      }
      append_primary_planet(system);
    }

    OpaquePlanet* const primary = system->primary_38;
    primary->body_kind_38 = 1;
    primary->transform_a0 = g_solar_load_transform_01694c10;
    primary->transform_a4 = g_solar_load_transform_01694c14;
    primary->transform_a8 = g_solar_load_transform_01694c18;
    const TargetWord angular_type = ports.star_type(system->owner_star_0c);
    primary->angular_scale_ac = ports.star_angular_scale(angular_type);

    OpaqueName* const current_name = ports.star_name(system->owner_star_0c);
    if (current_name != &primary->name_b0) {
      ports.copy_name(&primary->name_b0, current_name->data_00,
                      current_name->size_04);
    }
    const TargetWord radius_type = ports.star_type(system->owner_star_0c);
    primary->radius_c8 = ports.star_radius(radius_type);
  }

  if (ports.is_asteroid_system(star)) {
    ports.load_asteroid_belt(system);
  }

  const TargetWord lower_type = ports.star_type(system->owner_star_0c);
  const float radius = load_cached_radius(lower_type);
  const float lower = ports.star_orbit_scale(lower_type) * 85.0F + radius;
  const TargetWord upper_type = ports.star_type(system->owner_star_0c);
  const float upper_radius = load_cached_radius(upper_type);
  const float upper =
      ports.star_orbit_scale(upper_type) * 195.0F + upper_radius;

  OpaquePlanetVector* const vector = ports.list_planets();
  for (OpaquePlanet** cursor = vector->begin; cursor != vector->end; ++cursor) {
    OpaquePlanet* const source = *cursor;
    OpaquePlanet* materialized = nullptr;
    OpaquePlanetManager* const manager = ports.current_planet_manager();
    ports.materialize_planet(manager, source, &materialized);
    if (materialized != nullptr) {
      ports.planet_retain_bc(materialized);
      OpaquePlanet* const appended =
          append_materialized_planet(system, materialized);
      ports.planet_release_c0(appended);
    }

    const float distance = ports.distance_sample(1);
    if (distance < lower && (source->radius_flags_2c & 1u) == 0u) {
      source->radius_flags_2c |= 0x1000u;
    }
    if (upper < distance && (source->radius_flags_2c & 1u) == 0u) {
      source->radius_flags_2c |= 0x2000u;
    }

    if (materialized != nullptr) {
      ports.planet_release_c0(materialized);
    }
  }
}

void sphere_draw_direction_00b7e560(float* direction) {
  auto* const render_helper =
      reinterpret_cast<OpaqueRenderHelper*>(UINT32_C(0x1601760));
  float x;
  float y;
  float z;
  float norm;
  do {
    x = clamp_unit_sample(sphere_draw_ports().render_sample(render_helper));
    y = clamp_unit_sample(sphere_draw_ports().render_sample(render_helper));
    z = clamp_unit_sample(sphere_draw_ports().render_sample(render_helper));
    norm = z * z + x * x + y * y;
  } while (norm > 1.0F || norm < 0.0001F);

  const float inverse_norm = 1.0F / std::sqrt(norm);
  direction[0] = inverse_norm * x;
  direction[1] = inverse_norm * y;
  direction[2] = inverse_norm * z;
}

}

#undef PKG14_A3_THISCALL
