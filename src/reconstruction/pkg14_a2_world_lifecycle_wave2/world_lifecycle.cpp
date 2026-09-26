#include "world_lifecycle.hpp"

namespace openspore::reconstruction::pkg14_a2_world_lifecycle_wave2 {

#if defined(_MSC_VER)
#define PKG14_A2_THISCALL __thiscall
#else
#define PKG14_A2_THISCALL __attribute__((thiscall))
#endif

namespace {

TargetWord PKG14_A2_THISCALL
default_resolve_timing_source(OpaqueStarRegeneration*) {
  return 0;
}

bool default_timing_gate(TargetWord) { return false; }

OpaqueStarManager* default_current_manager() { return nullptr; }

std::uint64_t PKG14_A2_THISCALL default_read_clock(OpaqueStarManager*) {
  return 0;
}

void default_erase_vector_entry(OpaqueStarRegeneration**) {}

std::int32_t PKG14_A2_THISCALL default_make_temporary(OpaqueStarManager*,
                                                      std::uint8_t) {
  return 0;
}

void PKG14_A2_THISCALL default_apply_temporary(OpaqueStarRegeneration*,
                                               TargetWord) {}

void PKG14_A2_THISCALL default_set_state(OpaqueStarRegeneration*, TargetWord,
                                         std::uint8_t) {}

std::int32_t PKG14_A2_THISCALL default_regenerate(OpaqueStarRegeneration*) {
  return 0;
}

void PKG14_A2_THISCALL default_generate(OpaqueStarManager*,
                                        OpaqueStarRegeneration*, TargetWord,
                                        void*) {}

OpaqueCacheEntry* default_find(OpaqueRecordCache* cache) {
  return cache->entries_end;
}

bool default_matches(const OpaqueCacheEntry*) { return false; }

OpaqueCacheEntry* default_materialize(OpaqueRecordCache*) { return nullptr; }

}

OpaqueRecordToPlanetOutput* PKG14_A2_THISCALL record_to_planet_cache_00bb1560(
    OpaqueRecordCache* cache, OpaqueRecordToPlanetOutput* output,
    OpaqueUninitializedRecordSlot* pending_record) {
  auto& ports = record_to_planet_ports();
  (void)pending_record;
  OpaqueCacheEntry* const candidate = ports.find(cache);
  if (candidate != cache->entries_end && ports.matches(candidate)) {
    output->entry = candidate;
    output->inserted = 0;
    return output;
  }

  output->entry = ports.materialize(cache);
  output->inserted = 1;
  return output;
}

StarRegenerationPorts& star_regeneration_ports() {
  static StarRegenerationPorts ports{default_resolve_timing_source,
                                     default_timing_gate,
                                     default_current_manager,
                                     default_read_clock,
                                     default_erase_vector_entry,
                                     default_make_temporary,
                                     default_apply_temporary,
                                     default_set_state,
                                     default_regenerate,
                                     default_generate};
  return ports;
}

RecordToPlanetPorts& record_to_planet_ports() {
  static RecordToPlanetPorts ports{&record_to_planet_cache_00bb1560,
                                   default_find, default_matches,
                                   default_materialize};
  return ports;
}

void PKG14_A2_THISCALL star_regenerate_00bb4af0(OpaqueStarManager* manager,
                                                OpaqueStarRegeneration* star,
                                                TargetWord dispatch_word) {
  auto& ports = star_regeneration_ports();
  if (star->planet_gate_ac != 0) {
    return;
  }

  const TargetWord timing_source = ports.resolve_timing_source(star);
  if (!ports.timing_gate(timing_source)) {
    return;
  }

  OpaqueStarManager* const clock_owner = ports.current_manager();
  const std::uint64_t clock = ports.read_clock(clock_owner);
  star->generation_minute_0c = static_cast<TargetWord>(clock / UINT64_C(60000));

  OpaqueStarRegeneration** entry = manager->vector_begin_dc;
  if (entry != manager->vector_end_e0) {
    do {
      if (*entry == star) {
        ports.erase_vector_entry(entry);
        const TargetWord temporary =
            static_cast<TargetWord>(ports.make_temporary(manager, 0));
        ports.apply_temporary(star, temporary);
        break;
      }
      ++entry;
    } while (entry != manager->vector_end_e0);
  }

  ports.set_state(star, 1, 0);
  ports.regenerate(star);
  ports.generate(manager, star, dispatch_word, 0);
}

OpaqueRecordToPlanetOutput* PKG14_A2_THISCALL
star_manager_record_to_planet_00bb5b50(OpaqueStarManager* manager,
                                       OpaqueRecordToPlanetOutput* output) {
  OpaqueUninitializedRecordSlot temporary;
  return record_to_planet_ports().boundary(&manager->cache_16c, output,
                                           &temporary);
}

void PKG14_A2_THISCALL planet_record_copy_three_word_key_00b8da30(
    OpaquePlanetRecord* record, const OpaqueThreeWordKey* source_key) {
  record->key_188.words[0] = source_key->words[0];
  record->key_188.words[1] = source_key->words[1];
  record->key_188.words[2] = source_key->words[2];
}

#undef PKG14_A2_THISCALL

}
