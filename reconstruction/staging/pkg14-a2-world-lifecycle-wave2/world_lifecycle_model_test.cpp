#include <array>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "world_lifecycle.hpp"

namespace openspore::reconstruction::pkg14_a2_world_lifecycle_wave2 {

#if defined(_MSC_VER)
#define PKG14_A2_TEST_THISCALL __thiscall
#else
#define PKG14_A2_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::vector<std::string> trace;
OpaqueStarRegeneration* expected_star = nullptr;
OpaqueStarManager* expected_manager = nullptr;
std::int32_t expected_temporary = 0;
OpaqueStarRegeneration** expected_entries = nullptr;
OpaqueRecordCache* expected_cache = nullptr;
OpaqueRecordToPlanetOutput* expected_output = nullptr;
OpaqueCacheEntry* found_entry = nullptr;
OpaqueCacheEntry* materialized_entry = nullptr;
OpaqueRecordToPlanetOutput* boundary_result = nullptr;
bool match_result = false;
TargetWord timing_source_result = 0;
std::size_t generation_count = 0;
std::size_t materialize_count = 0;
std::size_t boundary_count = 0;

TargetWord PKG14_A2_TEST_THISCALL
resolve_timing_source(OpaqueStarRegeneration* star) {
  check(star == expected_star);
  trace.emplace_back("source");
  return timing_source_result;
}

bool timing_gate(TargetWord source) {
  check(source == timing_source_result);
  trace.emplace_back("timing");
  return true;
}

OpaqueStarManager* current_manager() {
  trace.emplace_back("manager");
  return expected_manager;
}

std::uint64_t PKG14_A2_TEST_THISCALL read_clock(OpaqueStarManager* manager) {
  check(manager == expected_manager);
  trace.emplace_back("clock");
  return UINT64_C(0x100000000) + UINT64_C(150000);
}

void erase_vector_entry(OpaqueStarRegeneration** entry) {
  check(entry >= expected_entries);
  trace.emplace_back("erase:" + std::to_string(static_cast<std::size_t>(
                                    entry - expected_entries)));
}

std::int32_t PKG14_A2_TEST_THISCALL make_temporary(OpaqueStarManager* manager,
                                                   std::uint8_t word) {
  check(manager == expected_manager);
  check(word == 0);
  trace.emplace_back("temporary");
  return expected_temporary;
}

void PKG14_A2_TEST_THISCALL apply_temporary(OpaqueStarRegeneration* star,
                                            TargetWord temporary) {
  check(star == expected_star);
  check(temporary == static_cast<TargetWord>(expected_temporary));
  trace.emplace_back("apply");
}

void PKG14_A2_TEST_THISCALL set_state(OpaqueStarRegeneration* star,
                                      TargetWord first, std::uint8_t second) {
  check(star == expected_star);
  check(first == 1);
  check(second == 0);
  trace.emplace_back("set");
}

std::int32_t PKG14_A2_TEST_THISCALL regenerate(OpaqueStarRegeneration* star) {
  check(star == expected_star);
  trace.emplace_back("regenerate");
  return 0;
}

void PKG14_A2_TEST_THISCALL generate(OpaqueStarManager* manager,
                                     OpaqueStarRegeneration* star,
                                     TargetWord dispatch_word,
                                     void* last_word) {
  check(manager == expected_manager);
  check(star == expected_star);
  check(dispatch_word == UINT32_C(0xa1b2c3d4));
  check(last_word == nullptr);
  ++generation_count;
  trace.emplace_back("generate");
}

void install_star_ports() {
  auto& ports = star_regeneration_ports();
  ports.resolve_timing_source = &resolve_timing_source;
  ports.timing_gate = &timing_gate;
  ports.current_manager = &current_manager;
  ports.read_clock = &read_clock;
  ports.erase_vector_entry = &erase_vector_entry;
  ports.make_temporary = &make_temporary;
  ports.apply_temporary = &apply_temporary;
  ports.set_state = &set_state;
  ports.regenerate = &regenerate;
  ports.generate = &generate;
}

void test_planet_gate_stops_before_timing() {
  trace.clear();
  generation_count = 0;
  OpaqueStarManager manager{};
  OpaqueStarRegeneration star{};
  star.planet_gate_ac = 1;
  star.generation_minute_0c = UINT32_C(0x76543210);
  expected_star = &star;
  expected_manager = &manager;
  install_star_ports();

  star_regenerate_00bb4af0(&manager, &star, UINT32_C(0xa1b2c3d4));

  check(trace.empty());
  check(generation_count == 0);
  check(star.generation_minute_0c == UINT32_C(0x76543210));
}

void test_timing_gate_stops_after_source() {
  trace.clear();
  generation_count = 0;
  OpaqueStarManager manager{};
  OpaqueStarRegeneration star{};
  expected_star = &star;
  expected_manager = &manager;
  timing_source_result = UINT32_C(0x89abcdef);
  auto& ports = star_regeneration_ports();
  install_star_ports();
  ports.timing_gate = [](TargetWord source) {
    check(source == UINT32_C(0x89abcdef));
    trace.emplace_back("timing");
    return false;
  };

  star_regenerate_00bb4af0(&manager, &star, UINT32_C(0xa1b2c3d4));

  check(trace == std::vector<std::string>({"source", "timing"}));
  check(generation_count == 0);
  check(star.generation_minute_0c == 0);
}

void test_found_star_reset_and_generation_order() {
  trace.clear();
  generation_count = 0;
  OpaqueStarManager manager{};
  OpaqueStarRegeneration other{};
  OpaqueStarRegeneration star{};
  OpaqueStarRegeneration last{};
  OpaqueStarRegeneration* entries[] = {&other, &star, &last};
  manager.vector_begin_dc = entries;
  manager.vector_end_e0 = entries + 3;
  expected_star = &star;
  expected_manager = &manager;
  expected_temporary = INT32_C(0x12345678);
  expected_entries = entries;
  timing_source_result = UINT32_C(0x10203040);
  install_star_ports();

  star_regenerate_00bb4af0(&manager, &star, UINT32_C(0xa1b2c3d4));

  check(star.generation_minute_0c ==
        static_cast<TargetWord>((UINT64_C(0x100000000) + UINT64_C(150000)) /
                                UINT64_C(60000)));
  check(trace == std::vector<std::string>(
                     {"source", "timing", "manager", "clock", "erase:1",
                      "temporary", "apply", "set", "regenerate", "generate"}));
  check(generation_count == 1);
}

void test_missing_vector_entry_preserves_reset_order() {
  trace.clear();
  generation_count = 0;
  OpaqueStarManager manager{};
  OpaqueStarRegeneration first{};
  OpaqueStarRegeneration second{};
  OpaqueStarRegeneration star{};
  OpaqueStarRegeneration* entries[] = {&first, &second};
  manager.vector_begin_dc = entries;
  manager.vector_end_e0 = entries + 2;
  expected_star = &star;
  expected_manager = &manager;
  expected_entries = entries;
  timing_source_result = 0;
  install_star_ports();

  star_regenerate_00bb4af0(&manager, &star, UINT32_C(0xa1b2c3d4));

  check(trace ==
        std::vector<std::string>({"source", "timing", "manager", "clock", "set",
                                  "regenerate", "generate"}));
  check(generation_count == 1);
}

OpaqueCacheEntry* find_entry(OpaqueRecordCache* cache) {
  check(cache == expected_cache);
  return found_entry;
}

bool entry_matches(const OpaqueCacheEntry* entry) {
  check(entry == found_entry);
  return match_result;
}

OpaqueCacheEntry* materialize_entry(OpaqueRecordCache* cache) {
  check(cache == expected_cache);
  ++materialize_count;
  return materialized_entry;
}

void test_cache_hit_output_and_flag_without_key_read() {
  OpaqueCacheEntry entries[2]{};
  OpaqueRecordCache cache{};
  cache.entries_begin = entries;
  cache.entries_end = entries + 2;
  OpaqueRecordToPlanetOutput output{};
  OpaqueUninitializedRecordSlot slot;
  expected_cache = &cache;
  found_entry = &entries[0];
  match_result = true;
  materialize_count = 0;
  auto& ports = record_to_planet_ports();
  ports.find = &find_entry;
  ports.matches = &entry_matches;
  ports.materialize = &materialize_entry;

  OpaqueRecordToPlanetOutput* const result =
      record_to_planet_cache_00bb1560(&cache, &output, &slot);

  check(result == &output);
  check(output.entry == &entries[0]);
  check(output.inserted == 0);
  check(materialize_count == 0);
}

void test_cache_miss_materializer_output_and_flag_without_key_read() {
  OpaqueCacheEntry entries[2]{};
  OpaqueCacheEntry materialized{};
  OpaqueRecordCache cache{};
  cache.entries_begin = entries;
  cache.entries_end = entries + 2;
  OpaqueRecordToPlanetOutput output{};
  OpaqueUninitializedRecordSlot slot;
  expected_cache = &cache;
  found_entry = &entries[1];
  match_result = false;
  materialized_entry = &materialized;
  materialize_count = 0;
  auto& ports = record_to_planet_ports();
  ports.find = &find_entry;
  ports.matches = &entry_matches;
  ports.materialize = &materialize_entry;

  OpaqueRecordToPlanetOutput* const result =
      record_to_planet_cache_00bb1560(&cache, &output, &slot);

  check(result == &output);
  check(output.entry == &materialized);
  check(output.inserted == 1);
  check(materialize_count == 1);
}

OpaqueRecordToPlanetOutput* PKG14_A2_TEST_THISCALL
boundary(OpaqueRecordCache* cache, OpaqueRecordToPlanetOutput* output,
         OpaqueUninitializedRecordSlot* pending) {
  ++boundary_count;
  check(cache == expected_cache);
  check(output == expected_output);
  check(reinterpret_cast<std::uintptr_t>(pending) !=
        reinterpret_cast<std::uintptr_t>(output));
  check(reinterpret_cast<std::uintptr_t>(pending) <
            reinterpret_cast<std::uintptr_t>(expected_output) ||
        reinterpret_cast<std::uintptr_t>(pending) >=
            reinterpret_cast<std::uintptr_t>(expected_output) +
                sizeof(*output));
  output->entry = materialized_entry;
  output->inserted = 1;
  return boundary_result;
}

void test_record_to_planet_forwards_uninitialized_slot() {
  OpaqueStarManager manager{};
  OpaqueRecordToPlanetOutput output{};
  OpaqueRecordToPlanetOutput returned_output{};
  OpaqueCacheEntry materialized{};
  expected_cache = &manager.cache_16c;
  expected_output = &output;
  output.entry = reinterpret_cast<OpaqueCacheEntry*>(
      static_cast<std::uintptr_t>(UINT32_C(0x80000000)));
  output.inserted = 0x5a;
  output.opaque_05_07 = {0x11, 0x22, 0x33};
  materialized_entry = &materialized;
  boundary_result = &returned_output;
  boundary_count = 0;
  auto& ports = record_to_planet_ports();
  ports.boundary = &boundary;

  OpaqueRecordToPlanetOutput* const result =
      star_manager_record_to_planet_00bb5b50(&manager, &output);

  check(result == &returned_output);
  check(boundary_count == 1);
  check(output.entry == &materialized);
  check(output.inserted == 1);
  check(returned_output.entry == nullptr);
}

void test_three_word_key_copy_and_neighbors() {
  OpaquePlanetRecord record{};
  record.opaque_00_187.fill(0xa5);
  record.opaque_194_197.fill(0x5a);
  record.opaque_00_187.back() = 0x6b;
  record.key_188.words[0] = 0x11111111u;
  record.key_188.words[1] = 0x22222222u;
  record.key_188.words[2] = 0x33333333u;
  OpaqueThreeWordKey source{
      {UINT32_C(0x80000000), UINT32_C(0xdeadbeef), UINT32_C(0x7fffffff)}};

  planet_record_copy_three_word_key_00b8da30(&record, &source);

  check(record.key_188.words[0] == UINT32_C(0x80000000));
  check(record.key_188.words[1] == UINT32_C(0xdeadbeef));
  check(record.key_188.words[2] == UINT32_C(0x7fffffff));
  check(source.words[0] == UINT32_C(0x80000000));
  check(source.words[1] == UINT32_C(0xdeadbeef));
  check(source.words[2] == UINT32_C(0x7fffffff));
  check(record.opaque_00_187.back() == 0x6b);
  for (std::size_t index = 0; index + 1 < record.opaque_00_187.size();
       ++index) {
    check(record.opaque_00_187[index] == 0xa5);
  }
  for (const std::uint8_t value : record.opaque_194_197) {
    check(value == 0x5a);
  }
}

void run() {
  test_planet_gate_stops_before_timing();
  test_timing_gate_stops_after_source();
  test_found_star_reset_and_generation_order();
  test_missing_vector_entry_preserves_reset_order();
  test_cache_hit_output_and_flag_without_key_read();
  test_cache_miss_materializer_output_and_flag_without_key_read();
  test_record_to_planet_forwards_uninitialized_slot();
  test_three_word_key_copy_and_neighbors();
}

}

}

#undef PKG14_A2_TEST_THISCALL

int main() { openspore::reconstruction::pkg14_a2_world_lifecycle_wave2::run(); }
