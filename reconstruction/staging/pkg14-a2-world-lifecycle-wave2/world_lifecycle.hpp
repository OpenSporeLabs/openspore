#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg14-a2-world-lifecycle-wave2 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg14_a2_world_lifecycle_wave2 {

using TargetWord = std::uint32_t;

#if defined(_MSC_VER)
#define PKG14_A2_THISCALL __thiscall
#else
#define PKG14_A2_THISCALL __attribute__((thiscall))
#endif

struct OpaqueStarRegeneration {
  std::array<std::uint8_t, 0x0c> opaque_00_0b;
  TargetWord generation_minute_0c;
  std::array<std::uint8_t, 0x9c> opaque_10_ab;
  std::uint8_t planet_gate_ac;
  std::array<std::uint8_t, 3> opaque_ad_af;
};

struct OpaqueUninitializedRecordSlot {
  std::uint8_t bytes[8];
};

struct OpaqueCacheEntry {
  std::array<std::uint8_t, 8> key_00;
  TargetWord opaque_08;
  TargetWord opaque_0c;
};

struct OpaqueRecordCache {
  OpaqueCacheEntry* entries_begin;
  OpaqueCacheEntry* entries_end;
  OpaqueCacheEntry* entries_capacity;
  std::array<std::uint8_t, 8> opaque_0c_13;
  std::uint8_t lookup_mode_14;
  std::array<std::uint8_t, 3> opaque_15_17;
};

struct OpaqueStarManager {
  std::array<std::uint8_t, 0xdc> opaque_00_db;
  OpaqueStarRegeneration** vector_begin_dc;
  OpaqueStarRegeneration** vector_end_e0;
  std::array<std::uint8_t, 0x88> opaque_e4_16f;
  OpaqueRecordCache cache_16c;
};

struct OpaqueRecordToPlanetOutput {
  OpaqueCacheEntry* entry;
  std::uint8_t inserted;
  std::array<std::uint8_t, 3> opaque_05_07;
};

struct OpaqueThreeWordKey {
  TargetWord words[3];
};

struct OpaquePlanetRecord {
  std::array<std::uint8_t, 0x188> opaque_00_187;
  OpaqueThreeWordKey key_188;
  std::array<std::uint8_t, 4> opaque_194_197;
};

using ResolveTimingSource =
    TargetWord(PKG14_A2_THISCALL*)(OpaqueStarRegeneration*);
using TimingGate = bool (*)(TargetWord);
using CurrentManager = OpaqueStarManager* (*)();
using ReadClock = std::uint64_t(PKG14_A2_THISCALL*)(OpaqueStarManager*);
using EraseVectorEntry = void (*)(OpaqueStarRegeneration**);
using MakeTemporary = std::int32_t(PKG14_A2_THISCALL*)(OpaqueStarManager*,
                                                       std::uint8_t);
using ApplyTemporary = void(PKG14_A2_THISCALL*)(OpaqueStarRegeneration*,
                                                TargetWord);
using SetRegenerationState = void(PKG14_A2_THISCALL*)(OpaqueStarRegeneration*,
                                                      TargetWord, std::uint8_t);
using RegenerateStar =
    std::int32_t(PKG14_A2_THISCALL*)(OpaqueStarRegeneration*);
using GenerateStar = void(PKG14_A2_THISCALL*)(OpaqueStarManager*,
                                              OpaqueStarRegeneration*,
                                              TargetWord, void*);

struct StarRegenerationPorts {
  ResolveTimingSource resolve_timing_source;
  TimingGate timing_gate;
  CurrentManager current_manager;
  ReadClock read_clock;
  EraseVectorEntry erase_vector_entry;
  MakeTemporary make_temporary;
  ApplyTemporary apply_temporary;
  SetRegenerationState set_state;
  RegenerateStar regenerate;
  GenerateStar generate;
};

using RecordCacheBoundary = OpaqueRecordToPlanetOutput*(
    PKG14_A2_THISCALL*)(OpaqueRecordCache*, OpaqueRecordToPlanetOutput*,
                        OpaqueUninitializedRecordSlot*);
using FindCacheEntry = OpaqueCacheEntry* (*)(OpaqueRecordCache*);
using CacheEntryMatches = bool (*)(const OpaqueCacheEntry*);
using MaterializeCacheEntry = OpaqueCacheEntry* (*)(OpaqueRecordCache*);

struct RecordToPlanetPorts {
  RecordCacheBoundary boundary;
  FindCacheEntry find;
  CacheEntryMatches matches;
  MaterializeCacheEntry materialize;
};

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueStarRegeneration) == 0xb0,
              "opaque star regeneration extent");
static_assert(offsetof(OpaqueStarRegeneration, generation_minute_0c) == 0x0c,
              "opaque star generation-minute offset");
static_assert(offsetof(OpaqueStarRegeneration, planet_gate_ac) == 0xac,
              "opaque star planet-gate offset");
static_assert(sizeof(OpaqueUninitializedRecordSlot) == 8,
              "opaque uninitialized record slot size");
static_assert(sizeof(OpaqueCacheEntry) == 0x10, "opaque cache entry stride");
static_assert(offsetof(OpaqueRecordCache, entries_begin) == 0x00,
              "opaque cache begin offset");
static_assert(offsetof(OpaqueRecordCache, entries_end) == 0x04,
              "opaque cache end offset");
static_assert(offsetof(OpaqueRecordCache, lookup_mode_14) == 0x14,
              "opaque cache mode offset");
static_assert(sizeof(OpaqueRecordCache) == 0x18, "opaque cache extent");
static_assert(offsetof(OpaqueStarManager, vector_begin_dc) == 0xdc,
              "opaque manager vector begin offset");
static_assert(offsetof(OpaqueStarManager, vector_end_e0) == 0xe0,
              "opaque manager vector end offset");
static_assert(offsetof(OpaqueStarManager, cache_16c) == 0x16c,
              "opaque manager cache offset");
static_assert(sizeof(OpaqueRecordToPlanetOutput) == 8,
              "opaque record-to-planet output size");
static_assert(offsetof(OpaqueRecordToPlanetOutput, inserted) == 0x04,
              "opaque record-to-planet output flag offset");
static_assert(offsetof(OpaquePlanetRecord, key_188) == 0x188,
              "opaque planet-record key offset");

StarRegenerationPorts& star_regeneration_ports();
RecordToPlanetPorts& record_to_planet_ports();

OpaqueRecordToPlanetOutput* PKG14_A2_THISCALL record_to_planet_cache_00bb1560(
    OpaqueRecordCache* cache, OpaqueRecordToPlanetOutput* output,
    OpaqueUninitializedRecordSlot* pending_record);

void PKG14_A2_THISCALL star_regenerate_00bb4af0(OpaqueStarManager* manager,
                                                OpaqueStarRegeneration* star,
                                                TargetWord dispatch_word);

OpaqueRecordToPlanetOutput* PKG14_A2_THISCALL
star_manager_record_to_planet_00bb5b50(OpaqueStarManager* manager,
                                       OpaqueRecordToPlanetOutput* output);

void PKG14_A2_THISCALL planet_record_copy_three_word_key_00b8da30(
    OpaquePlanetRecord* record, const OpaqueThreeWordKey* source_key);

#undef PKG14_A2_THISCALL

}
