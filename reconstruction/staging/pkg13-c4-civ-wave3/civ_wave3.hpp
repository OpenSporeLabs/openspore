#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG13-C4 civ wave3 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg13_c4_civ_wave3 {

constexpr std::size_t kSlotCount = 14;

#if defined(_MSC_VER)
#define PKG13_C4_THISCALL __thiscall
#else
#define PKG13_C4_THISCALL __attribute__((thiscall))
#endif

struct OpaqueCity;
struct OpaqueCityRoot;
struct OpaqueCityBuilding;
struct OpaqueCityData;
struct OpaqueLiveStateContext;
struct OpaqueLiveState;
struct OpaqueCulturePlayer;
struct OpaqueCultureCandidate;
struct OpaqueCultureCity;

struct alignas(4) OpaqueCity {
  static constexpr std::size_t kSize = 0x6a0;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueCityRoot {
  static constexpr std::size_t kSize = 0x300;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueCityBuilding {
  static constexpr std::size_t kSize = 0x38;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueCityData {
  static constexpr std::size_t kSize = 0x2a0;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueLiveStateContext {
  static constexpr std::size_t kSize = 0x30;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueLiveState {
  static constexpr std::size_t kSize = 0x38;
  std::array<std::uint8_t, kSize> bytes;
};

using CultureAddRef = void(PKG13_C4_THISCALL*)(OpaqueCultureCandidate*);
using CultureRelease = void(PKG13_C4_THISCALL*)(OpaqueCultureCandidate*);

struct CultureCandidateVtable {
  CultureAddRef add_ref;
  CultureRelease release;
};

struct alignas(4) OpaqueCultureCandidate {
  static constexpr std::size_t kSize = 0x38;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueCultureCity {
  static constexpr std::size_t kSize = 0x4c0;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) OpaqueCulturePlayer {
  static constexpr std::size_t kSize = 0x40;
  std::array<std::uint8_t, kSize> bytes;
};

struct alignas(4) CultureVectorResult {
  float x;
  float y;
  float z;
};

struct alignas(4) OpaqueCultureSelection {
  static constexpr std::size_t kSize = 0x4b4;
  std::array<std::uint8_t, kSize> bytes;
};

struct CultureIntrusivePtr {
  OpaqueCultureCandidate* ptr;
};

struct alignas(4) CultureCandidateRangeStorage {
  std::uint32_t opaque_0;
  OpaqueCultureCandidate** begin;
  OpaqueCultureCandidate** end;
};

struct alignas(4) CultureCityRangeStorage {
  OpaqueCultureCity** begin;
  OpaqueCultureCity** end;
};

using CityRootPort = OpaqueCityRoot*(PKG13_C4_THISCALL*)(OpaqueCity*);
using CityBuildingPort = OpaqueCityBuilding*(PKG13_C4_THISCALL*)(OpaqueCity*,
                                                                 std::uint32_t);
using CityDataPort = OpaqueCityData*(PKG13_C4_THISCALL*)(OpaqueCityBuilding*);
using CityDataStatePort = std::int32_t(PKG13_C4_THISCALL*)(OpaqueCityData*);
using CityDataFilterPort = bool(PKG13_C4_THISCALL*)(OpaqueCityData*);
using CityBuildingIdPort = std::uint32_t(PKG13_C4_THISCALL*)(OpaqueCityData*);
using CityAdjacencyPort = std::uint8_t(PKG13_C4_THISCALL*)(OpaqueCityRoot*,
                                                           std::uint32_t,
                                                           std::uint32_t);
using LiveStatePort = OpaqueLiveState*(
    PKG13_C4_THISCALL*)(OpaqueLiveStateContext*, std::uint32_t);
using LiveAdjacencyPort = std::uint8_t(PKG13_C4_THISCALL*)(
    OpaqueLiveStateContext*, std::uint32_t, std::uint32_t);
using CityDataMarkPort = void(PKG13_C4_THISCALL*)(OpaqueCityData*,
                                                  std::uint8_t);
using CityCommitPort = void(PKG13_C4_THISCALL*)(OpaqueCity*);
using LiveNotifyPort = void(PKG13_C4_THISCALL*)(OpaqueLiveStateContext*, float,
                                                std::uint32_t);

struct CityBuildingUpdatePorts {
  CityRootPort get_city_root;
  CityBuildingPort get_city_building;
  CityDataPort get_city_data;
  CityDataStatePort get_city_data_state;
  CityDataFilterPort city_data_filter;
  CityBuildingIdPort get_city_building_id;
  CityAdjacencyPort get_city_adjacency;
  LiveStatePort get_live_state;
  LiveAdjacencyPort get_live_adjacency;
  CityDataMarkPort mark_city_data;
  CityCommitPort commit_city;
  LiveNotifyPort notify_live_state;
};

using CultureRootPort = void* (*)();
using CulturePlayerPort = OpaqueCulturePlayer*(PKG13_C4_THISCALL*)(void*);
using CulturePhaseSourcePort = void*(PKG13_C4_THISCALL*)(void*);
using CulturePhaseScorePort = std::int32_t(PKG13_C4_THISCALL*)(void*);
using CultureCurrentScorePort =
    std::int32_t(PKG13_C4_THISCALL*)(OpaqueCulturePlayer*);
using CultureSelectionScorePort =
    std::int32_t(PKG13_C4_THISCALL*)(OpaqueCultureSelection*);
using CultureCandidateAvailablePort =
    bool(PKG13_C4_THISCALL*)(OpaqueCultureCandidate*);
using CultureCandidateResultAdapterPort =
    const CultureVectorResult* (*)(OpaqueCultureCandidate*,
                                   std::uint32_t filter_argument,
                                   std::uint32_t switch_mode,
                                   bool include_switch_mode);
using CultureInputManagerPort = void* (*)();
using CultureVectorResultPort =
    std::uint16_t(PKG13_C4_THISCALL*)(void*, const CultureVectorResult*);
using CultureCityContextPort =
    std::uint32_t(PKG13_C4_THISCALL*)(OpaqueCultureCity*);
using CultureWaitPort =
    std::uint64_t(PKG13_C4_THISCALL*)(OpaqueCultureSelection*);
using CultureCandidateQueryPort = CultureCandidateRangeStorage*(
    PKG13_C4_THISCALL*)(void*, std::uint32_t, std::uint32_t, std::uint32_t,
                        std::uint32_t, std::uint32_t);
using CultureFilterPort = bool(PKG13_C4_THISCALL*)(OpaqueCultureSelection*,
                                                   const CultureVectorResult*,
                                                   std::uint16_t);
using CultureSecondaryFilterPort = bool(PKG13_C4_THISCALL*)(
    OpaqueCultureSelection*, const CultureVectorResult*, std::uint32_t);
using CultureCityQueryPort =
    CultureCityRangeStorage*(PKG13_C4_THISCALL*)(void*);
using CultureSelfPort = bool (*)(OpaqueCultureCity*, OpaqueCultureSelection*);
using CultureCandidateScorePort = float (*)(OpaqueCultureSelection*,
                                            OpaqueCultureCity*,
                                            OpaqueCultureCandidate*,
                                            std::uint32_t, std::uint32_t);
using CultureCityMatchPort = bool (*)(OpaqueCultureSelection*,
                                      OpaqueCultureCity*,
                                      OpaqueCultureCandidate*);
using CultureCityScorePort = float (*)(OpaqueCultureSelection*,
                                       OpaqueCultureCity*,
                                       OpaqueCultureCandidate*);
using CultureTryCommitPort = bool(PKG13_C4_THISCALL*)(
    OpaqueCultureSelection*, std::uint32_t, const CultureVectorResult*,
    std::uint16_t, std::uint32_t);
using CultureFinishPort = void(PKG13_C4_THISCALL*)(OpaqueCultureSelection*);

struct CultureWave3Ports {
  CultureRootPort current_root;
  CulturePlayerPort current_player;
  CulturePhaseSourcePort phase_source;
  CulturePhaseScorePort phase_score;
  CultureCurrentScorePort current_score;
  CultureSelectionScorePort selection_score;
  CultureCandidateAvailablePort candidate_available;
  CultureCandidateResultAdapterPort candidate_result;
  CultureInputManagerPort input_manager;
  CultureVectorResultPort vector_result;
  CultureCityContextPort city_context;
  CultureWaitPort selection_wait;
  CultureCandidateQueryPort enumerate_candidates;
  CultureFilterPort candidate_primary;
  CultureSecondaryFilterPort candidate_secondary;
  CultureCityQueryPort enumerate_cities;
  CultureSelfPort city_is_self;
  CultureCandidateScorePort candidate_score;
  CultureCityMatchPort city_matches_current;
  CultureCityMatchPort city_matches_position;
  CultureCityScorePort city_score;
  CultureTryCommitPort try_commit;
  CultureFinishPort finish;
};

extern CityBuildingUpdatePorts g_city_update_ports;
extern CultureWave3Ports g_culture_wave3_ports;

static_assert(sizeof(void*) == 4, "PKG13-C4 pointers are 32-bit");
static_assert(sizeof(OpaqueCity) == 0x6a0, "PKG13-C4 city size");
static_assert(sizeof(OpaqueCityBuilding) == 0x38,
              "PKG13-C4 city building size");
static_assert(sizeof(OpaqueCityData) == 0x2a0, "PKG13-C4 city data size");
static_assert(sizeof(OpaqueLiveStateContext) == 0x30,
              "PKG13-C4 live context size");
static_assert(sizeof(OpaqueLiveState) == 0x38, "PKG13-C4 live state size");
static_assert(sizeof(OpaqueCultureCandidate) == 0x38,
              "PKG13-C4 culture candidate size");
static_assert(sizeof(CultureVectorResult) == 0x0c,
              "PKG13-C4 culture vector result size");
static_assert(sizeof(OpaqueCultureCity) == 0x4c0, "PKG13-C4 culture city size");
static_assert(sizeof(OpaqueCultureSelection) == 0x4b4,
              "PKG13-C4 culture selection size");
static_assert(sizeof(CultureIntrusivePtr) == 4,
              "PKG13-C4 culture intrusive pointer size");
static_assert(sizeof(CultureCandidateRangeStorage) == 0x0c,
              "PKG13-C4 candidate range storage size");
static_assert(offsetof(CultureCandidateRangeStorage, begin) == 0x04,
              "PKG13-C4 candidate range begin offset");
static_assert(offsetof(CultureCandidateRangeStorage, end) == 0x08,
              "PKG13-C4 candidate range end offset");
static_assert(sizeof(CultureCityRangeStorage) == 0x08,
              "PKG13-C4 city range storage size");
static_assert(offsetof(CultureCityRangeStorage, begin) == 0x00,
              "PKG13-C4 city range begin offset");
static_assert(offsetof(CultureCityRangeStorage, end) == 0x04,
              "PKG13-C4 city range end offset");
static_assert(offsetof(CultureCandidateVtable, add_ref) == 0x00,
              "PKG13-C4 culture AddRef slot");
static_assert(offsetof(CultureCandidateVtable, release) == 0x04,
              "PKG13-C4 culture release slot");

extern "C" void city_building_economy_update_00be2440(OpaqueCity*,
                                                      OpaqueLiveStateContext*,
                                                      std::uint32_t);
extern "C" void PKG13_C4_THISCALL
culture_selection_00bf9820(OpaqueCultureSelection*);

}

#undef PKG13_C4_THISCALL
