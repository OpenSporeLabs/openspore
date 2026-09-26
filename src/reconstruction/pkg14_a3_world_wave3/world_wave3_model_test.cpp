#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "world_wave3.hpp"

namespace openspore::reconstruction::pkg14_a3_world_wave3 {

#if defined(_MSC_VER)
#define PKG14_A3_TEST_THISCALL __thiscall
#else
#define PKG14_A3_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

void check_near(float actual, float expected) {
  check(std::fabs(actual - expected) < 0.00001F);
}

struct Fixture {
  OpaqueSolarSystem system{};
  OpaqueStar star{};
  OpaquePlanetType star_type_service{};
  OpaqueName name{"star", 4};
  OpaquePlanet created{};
  OpaquePlanet materialized{};
  OpaquePlanet source{};
  OpaquePlanetManager manager{};
  OpaquePlanet* primary_slots[2]{};
  OpaquePlanet* planet_slots[2]{};
  OpaquePlanet* list_slots[1]{};
  OpaquePlanetVector list{};
  TargetWord type_index = 1;
  float distance = 100.0F;
  bool binary = false;
  bool asteroid = false;
  bool binary_type = false;
  std::size_t allocation_count = 0;
  std::size_t construction_count = 0;
  std::size_t binary_load_count = 0;
  std::size_t asteroid_load_count = 0;
  std::size_t star_type_count = 0;
  std::size_t angular_scale_count = 0;
  std::size_t orbit_scale_count = 0;
  std::size_t copy_name_count = 0;
  std::size_t star_radius_count = 0;
  std::size_t binary_radius_count = 0;
  std::size_t name_count = 0;
  std::size_t call_00_count = 0;
  std::size_t call_04_count = 0;
  std::size_t retain_count = 0;
  std::size_t release_count = 0;
  std::size_t materialize_count = 0;
  std::size_t grow_primary_count = 0;
  std::size_t grow_planet_count = 0;
  std::size_t distance_count = 0;
};

Fixture* expected_fixture = nullptr;

void PKG14_A3_TEST_THISCALL load_binary_or_asteroid(OpaqueSolarSystem* system) {
  check(system == &expected_fixture->system);
  ++expected_fixture->binary_load_count;
}

void PKG14_A3_TEST_THISCALL load_asteroid_belt(OpaqueSolarSystem* system) {
  check(system == &expected_fixture->system);
  ++expected_fixture->asteroid_load_count;
}

bool PKG14_A3_TEST_THISCALL is_binary_or_asteroid(OpaqueStar* star) {
  check(star == &expected_fixture->star);
  return expected_fixture->binary;
}

bool PKG14_A3_TEST_THISCALL is_asteroid_system(OpaqueStar* star) {
  check(star == &expected_fixture->star);
  return expected_fixture->asteroid;
}

TargetWord PKG14_A3_TEST_THISCALL star_type(OpaqueStar* star) {
  check(star == &expected_fixture->star);
  ++expected_fixture->star_type_count;
  return expected_fixture->type_index;
}

OpaqueName* PKG14_A3_TEST_THISCALL star_name(OpaqueStar* star) {
  check(star == &expected_fixture->star);
  ++expected_fixture->name_count;
  return &expected_fixture->name;
}

float star_angular_scale(TargetWord type) {
  check(type == expected_fixture->type_index);
  ++expected_fixture->angular_scale_count;
  return 0.5F;
}

float star_radius(TargetWord type) {
  check(type == expected_fixture->type_index);
  ++expected_fixture->star_radius_count;
  return 10.0F;
}

float star_orbit_scale(TargetWord type) {
  check(type == expected_fixture->type_index);
  ++expected_fixture->orbit_scale_count;
  return 2.0F;
}

float binary_or_asteroid_radius(TargetWord type) {
  check(type == expected_fixture->type_index);
  ++expected_fixture->binary_radius_count;
  return 20.0F;
}

bool is_binary_or_asteroid_type(TargetWord type) {
  check(type == expected_fixture->type_index);
  return expected_fixture->binary_type;
}

void* allocate_celestial_body(TargetWord size, const char* type,
                              TargetWord first, TargetWord second,
                              TargetWord third, TargetWord fourth) {
  check(expected_fixture != nullptr);
  check(size == 0xcc);
  check(std::strcmp(type, "Simulator/cCelestialBody") == 0);
  check(first == 0);
  check(second == 0);
  check(third == 0);
  check(fourth == 0);
  ++expected_fixture->allocation_count;
  return &expected_fixture->created;
}

OpaquePlanet* PKG14_A3_TEST_THISCALL construct_celestial_body(void* allocation,
                                                              TargetWord mode) {
  check(allocation == &expected_fixture->created);
  check(mode == 0);
  ++expected_fixture->construction_count;
  return &expected_fixture->created;
}

void PKG14_A3_TEST_THISCALL planet_call_00(OpaquePlanet* planet) {
  check(planet == &expected_fixture->created ||
        planet == &expected_fixture->materialized);
  ++expected_fixture->call_00_count;
}

void PKG14_A3_TEST_THISCALL planet_call_04(OpaquePlanet* planet) {
  check(planet == &expected_fixture->created ||
        planet == &expected_fixture->materialized);
  ++expected_fixture->call_04_count;
}

void PKG14_A3_TEST_THISCALL planet_retain(OpaquePlanet* planet) {
  check(planet == &expected_fixture->created ||
        planet == &expected_fixture->materialized);
  ++expected_fixture->retain_count;
}

void PKG14_A3_TEST_THISCALL planet_release(OpaquePlanet* planet) {
  check(planet == &expected_fixture->created ||
        planet == &expected_fixture->materialized);
  ++expected_fixture->release_count;
}

void PKG14_A3_TEST_THISCALL copy_name(OpaqueName* destination, const char* data,
                                      TargetWord size) {
  check(destination == &expected_fixture->created.name_b0);
  check(data == expected_fixture->name.data_00);
  check(size == expected_fixture->name.size_04);
  ++expected_fixture->copy_name_count;
  destination->data_00 = data;
  destination->size_04 = size;
}

OpaquePlanetManager* current_planet_manager() {
  return &expected_fixture->manager;
}

void PKG14_A3_TEST_THISCALL materialize_planet(OpaquePlanetManager* manager,
                                               OpaquePlanet* source,
                                               OpaquePlanet** output) {
  check(manager == &expected_fixture->manager);
  check(source == &expected_fixture->source);
  check(output != nullptr);
  *output = &expected_fixture->materialized;
  ++expected_fixture->materialize_count;
}

OpaquePlanetVector* list_planets() { return &expected_fixture->list; }

void PKG14_A3_TEST_THISCALL grow_primary_vector(OpaquePlanetVector* vector,
                                                OpaquePlanet** end,
                                                OpaquePlanet** value) {
  check(vector == &expected_fixture->system.primary_vector_24);
  check(end == vector->end);
  check(value == &expected_fixture->system.primary_38);
  ++expected_fixture->grow_primary_count;
  vector->capacity = vector->begin + 1;
  *vector->begin = *value;
  end = vector->begin + 1;
  vector->end = end;
  ++expected_fixture->call_00_count;
}

void PKG14_A3_TEST_THISCALL grow_planet_vector(OpaquePlanetVector* vector,
                                               OpaquePlanet** end,
                                               OpaquePlanet** value) {
  check(vector == &expected_fixture->system.planet_vector_10);
  check(end == vector->end);
  check(value != nullptr);
  ++expected_fixture->grow_planet_count;
  vector->capacity = vector->begin + 1;
  *vector->begin = *value;
  end = vector->begin + 1;
  vector->end = end;
  ++expected_fixture->retain_count;
}

float distance_sample(TargetWord selector) {
  check(selector == 1);
  ++expected_fixture->distance_count;
  return expected_fixture->distance;
}

void install_ports() {
  auto& ports = solar_load_ports();
  ports.load_binary_or_asteroid = &load_binary_or_asteroid;
  ports.load_asteroid_belt = &load_asteroid_belt;
  ports.is_binary_or_asteroid = &is_binary_or_asteroid;
  ports.is_asteroid_system = &is_asteroid_system;
  ports.star_type = &star_type;
  ports.star_name = &star_name;
  ports.star_angular_scale = &star_angular_scale;
  ports.star_radius = &star_radius;
  ports.star_orbit_scale = &star_orbit_scale;
  ports.binary_or_asteroid_radius = &binary_or_asteroid_radius;
  ports.is_binary_or_asteroid_type = &is_binary_or_asteroid_type;
  ports.allocate_celestial_body = &allocate_celestial_body;
  ports.construct_celestial_body = &construct_celestial_body;
  ports.planet_call_00 = &planet_call_00;
  ports.planet_call_04 = &planet_call_04;
  ports.planet_retain_bc = &planet_retain;
  ports.planet_release_c0 = &planet_release;
  ports.copy_name = &copy_name;
  ports.current_planet_manager = &current_planet_manager;
  ports.materialize_planet = &materialize_planet;
  ports.list_planets = &list_planets;
  ports.grow_primary_vector = &grow_primary_vector;
  ports.grow_planet_vector = &grow_planet_vector;
  ports.distance_sample = &distance_sample;
}

void reset_fixture(Fixture& fixture) {
  fixture = Fixture{};
  fixture.star.type_service_48 = &fixture.star_type_service;
  fixture.name.data_00 = "star";
  fixture.name.size_04 = 4;
  fixture.system.primary_vector_24 = {
      fixture.primary_slots, fixture.primary_slots, fixture.primary_slots + 2};
  fixture.system.planet_vector_10 = {fixture.planet_slots, fixture.planet_slots,
                                     fixture.planet_slots + 2};
  fixture.list_slots[0] = &fixture.source;
  fixture.list = {fixture.list_slots, fixture.list_slots + 1,
                  fixture.list_slots + 1};
  g_solar_load_transform_01694c10 = 0;
  g_solar_load_transform_01694c14 = 0;
  g_solar_load_transform_01694c18 = 0;
  g_solar_load_radius_cache_01579d10 = {};
  g_solar_load_transform_01694c10 = 0x11111111u;
  g_solar_load_transform_01694c14 = 0x22222222u;
  g_solar_load_transform_01694c18 = 0x33333333u;
  g_solar_load_radius_cache_01579d10[1] = -1.0F;
  expected_fixture = &fixture;
  install_ports();
}

void test_regular_create_materialize_and_reference_order() {
  Fixture fixture;
  reset_fixture(fixture);
  fixture.source.radius_flags_2c = 0;

  solar_system_load_00c86760(&fixture.system, &fixture.star);

  check(fixture.system.owner_star_0c == &fixture.star);
  check(fixture.system.primary_38 == &fixture.created);
  check(fixture.system.primary_vector_24.end ==
        fixture.system.primary_vector_24.begin + 1);
  check(*fixture.system.primary_vector_24.begin == &fixture.created);
  check(fixture.system.planet_vector_10.end ==
        fixture.system.planet_vector_10.begin + 1);
  check(*fixture.system.planet_vector_10.begin == &fixture.materialized);
  check(fixture.created.body_kind_38 == 1);
  check(fixture.created.transform_a0 == 0x11111111u);
  check(fixture.created.transform_a4 == 0x22222222u);
  check(fixture.created.transform_a8 == 0x33333333u);
  check(fixture.created.angular_scale_ac == 0.5F);
  check(fixture.created.radius_c8 == 10.0F);
  check(fixture.created.name_b0.data_00 == fixture.name.data_00);
  check(fixture.created.name_b0.size_04 == fixture.name.size_04);
  check(g_solar_load_radius_cache_01579d10[1] == 10.0F);
  check(fixture.source.radius_flags_2c == 0x1000u);
  check(fixture.allocation_count == 1);
  check(fixture.construction_count == 1);
  check(fixture.star_type_count == 4);
  check(fixture.angular_scale_count == 1);
  check(fixture.orbit_scale_count == 2);
  check(fixture.copy_name_count == 1);
  check(fixture.star_radius_count == 2);
  check(fixture.binary_radius_count == 0);
  check(fixture.materialize_count == 1);
  check(fixture.retain_count == 2);
  check(fixture.release_count == 2);
  check(fixture.call_00_count == 2);
  check(fixture.call_04_count == 0);
  check(fixture.distance_count == 1);
}

void test_existing_primary_is_reused() {
  Fixture fixture;
  reset_fixture(fixture);
  fixture.system.primary_38 = &fixture.created;
  fixture.system.primary_vector_24 = {fixture.primary_slots,
                                      fixture.primary_slots + 1,
                                      fixture.primary_slots + 2};
  fixture.list = {fixture.list_slots, fixture.list_slots, fixture.list_slots};

  solar_system_load_00c86760(&fixture.system, &fixture.star);

  check(fixture.allocation_count == 0);
  check(fixture.construction_count == 0);
  check(fixture.call_00_count == 0);
  check(fixture.materialize_count == 0);
  check(fixture.system.owner_star_0c == &fixture.star);
  check(fixture.system.primary_38 == &fixture.created);
}

void test_binary_and_asteroid_branches_are_separate() {
  Fixture fixture;
  reset_fixture(fixture);
  fixture.binary = true;
  fixture.asteroid = true;
  fixture.binary_type = true;
  fixture.type_index = 7;
  g_solar_load_radius_cache_01579d10[7] = -1.0F;
  fixture.created.body_kind_38 = 0x5a;
  fixture.created.transform_a0 = 0x11111111u;
  fixture.created.transform_a4 = 0x22222222u;
  fixture.created.transform_a8 = 0x33333333u;
  fixture.created.angular_scale_ac = 0.5F;
  fixture.created.radius_c8 = 10.0F;
  fixture.source.radius_flags_2c = 0x54u;
  fixture.list = {fixture.list_slots, fixture.list_slots + 1,
                  fixture.list_slots + 1};

  solar_system_load_00c86760(&fixture.system, &fixture.star);

  check(fixture.binary_load_count == 1);
  check(fixture.asteroid_load_count == 1);
  check(fixture.system.primary_38 == nullptr);
  check(fixture.system.planet_vector_10.end ==
        fixture.system.planet_vector_10.begin + 1);
  check(*fixture.system.planet_vector_10.begin == &fixture.materialized);
  check(fixture.allocation_count == 0);
  check(fixture.construction_count == 0);
  check(fixture.star_type_count == 2);
  check(fixture.angular_scale_count == 0);
  check(fixture.orbit_scale_count == 2);
  check(fixture.copy_name_count == 0);
  check(fixture.star_radius_count == 0);
  check(fixture.binary_radius_count == 1);
  check(fixture.name_count == 0);
  check(fixture.materialize_count == 1);
  check(fixture.distance_count == 1);
  check(fixture.call_00_count == 0);
  check(fixture.call_04_count == 0);
  check(fixture.retain_count == 2);
  check(fixture.release_count == 2);
  check(fixture.created.body_kind_38 == 0x5a);
  check(fixture.created.transform_a0 == 0x11111111u);
  check(fixture.created.transform_a4 == 0x22222222u);
  check(fixture.created.transform_a8 == 0x33333333u);
  check(fixture.created.angular_scale_ac == 0.5F);
  check(fixture.created.radius_c8 == 10.0F);
  check(fixture.source.radius_flags_2c == 0x1054u);
  check(g_solar_load_radius_cache_01579d10[7] == 20.0F);
}

void test_radius_flags_and_bit_zero_gate() {
  Fixture fixture;
  reset_fixture(fixture);
  fixture.distance = 500.0F;

  solar_system_load_00c86760(&fixture.system, &fixture.star);
  check(fixture.source.radius_flags_2c == 0x2000u);

  fixture.source.radius_flags_2c = 0;
  fixture.distance = 0.0F;
  solar_system_load_00c86760(&fixture.system, &fixture.star);
  check(fixture.source.radius_flags_2c == 0x1000u);

  fixture.source.radius_flags_2c = 1u;
  fixture.distance = 0.0F;
  solar_system_load_00c86760(&fixture.system, &fixture.star);
  check(fixture.source.radius_flags_2c == 1u);
}

void test_full_primary_and_planet_vectors_use_growth_ports() {
  Fixture fixture;
  reset_fixture(fixture);
  fixture.system.primary_vector_24 = {
      fixture.primary_slots, fixture.primary_slots, fixture.primary_slots};
  fixture.system.planet_vector_10 = {fixture.planet_slots, fixture.planet_slots,
                                     fixture.planet_slots};

  solar_system_load_00c86760(&fixture.system, &fixture.star);

  check(fixture.grow_primary_count == 1);
  check(fixture.grow_planet_count == 1);
  check(fixture.call_00_count == 2);
  check(fixture.retain_count == 2);
  check(fixture.release_count == 2);
  check(*fixture.system.primary_vector_24.begin == &fixture.created);
  check(*fixture.system.planet_vector_10.begin == &fixture.materialized);
}

std::vector<float> render_samples;
std::size_t render_sample_index = 0;

float PKG14_A3_TEST_THISCALL render_sample(OpaqueRenderHelper* helper) {
  check(helper == reinterpret_cast<OpaqueRenderHelper*>(UINT32_C(0x1601760)));
  check(render_sample_index < render_samples.size());
  return render_samples[render_sample_index++];
}

void install_render_samples(std::vector<float> samples) {
  render_samples = std::move(samples);
  render_sample_index = 0;
  sphere_draw_ports().render_sample = &render_sample;
}

void test_sphere_retry_clamp_and_boundary_normalization() {
  install_render_samples({1.0F, 1.0F, 1.0F, 2.0F, 0.5F, 0.5F});
  float output[3]{};

  sphere_draw_direction_00b7e560(output);

  check(render_sample_index == 6);
  check_near(output[0], 1.0F);
  check_near(output[1], 0.0F);
  check_near(output[2], 0.0F);
}

void test_sphere_clamps_lower_sample() {
  install_render_samples({0.5F, 0.5F, 0.5F, 0.5F, 0.0F, 0.5F});
  float output[3]{};

  sphere_draw_direction_00b7e560(output);

  check(render_sample_index == 6);
  check_near(output[0], 0.0F);
  check_near(output[1], -1.0F);
  check_near(output[2], 0.0F);
}

void test_sphere_rejects_zero_length_and_normalizes_components() {
  install_render_samples({0.5F, 0.5F, 0.5F, 0.75F, 0.5F, 0.25F});
  float output[3]{};

  sphere_draw_direction_00b7e560(output);

  check(render_sample_index == 6);
  check_near(output[0], 0.70710678F);
  check_near(output[1], 0.0F);
  check_near(output[2], -0.70710678F);
}

void run() {
  test_regular_create_materialize_and_reference_order();
  test_existing_primary_is_reused();
  test_binary_and_asteroid_branches_are_separate();
  test_radius_flags_and_bit_zero_gate();
  test_full_primary_and_planet_vectors_use_growth_ports();
  test_sphere_retry_clamp_and_boundary_normalization();
  test_sphere_clamps_lower_sample();
  test_sphere_rejects_zero_length_and_normalizes_components();
}

}

}

#undef PKG14_A3_TEST_THISCALL

int main() { openspore::reconstruction::pkg14_a3_world_wave3::run(); }
