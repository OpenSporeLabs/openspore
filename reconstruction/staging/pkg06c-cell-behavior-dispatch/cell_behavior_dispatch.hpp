#pragma once

#include <cstddef>
#include <cstdint>

#include "../../../src/reconstruction/pkg06a_cell_ai_selection/cell_ai_selection.hpp"

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-06C reconstruction requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-06C target pointers are 32-bit");
static_assert(sizeof(std::int32_t) == 4, "PKG-06C target words are 32-bit");
static_assert(sizeof(float) == 4, "PKG-06C target floats are 32-bit");

namespace openspore::reconstruction::pkg06c_cell_behavior_dispatch {

using openspore::reconstruction::pkg06a_cell_ai_selection::
    cell_ai_select_profile_00e52910;
using openspore::reconstruction::pkg06a_cell_ai_selection::g_cell_game_016b3c04;
using openspore::reconstruction::pkg06a_cell_ai_selection::ObservedCellAiData;
using openspore::reconstruction::pkg06a_cell_ai_selection::
    ObservedCellCellResource;

struct alignas(4) ObservedCellObjectData {
  std::byte opaque[0x398];
};

static_assert(sizeof(ObservedCellObjectData) == 0x398,
              "Observed Cell object view must retain its 0x398 extent");

inline constexpr std::size_t kGameSerializableOffset = 0x5190;
inline constexpr std::size_t kGameDifficultyOffset = 0x7c;
inline constexpr std::size_t kObjectIdOffset = 0x000;
inline constexpr std::size_t kObjectStopOffset = 0x112;
inline constexpr std::size_t kObjectReturnOffset = 0x16c;
inline constexpr std::size_t kObjectStateOffset = 0x18c;
inline constexpr std::size_t kGamePlayerOffset = 0x411c;
inline constexpr std::size_t kGameSpecialObjectOffset = 0x51b0;
inline constexpr std::size_t kGameSpecialModeOffset = 0x51b4;
inline constexpr std::size_t kGamePriorityObjectOffset = 0x51d4;
inline constexpr std::size_t kGameSuppressionOffset = 0x51db;

struct NativeCallContext {
  ObservedCellObjectData* object = nullptr;
  ObservedCellCellResource* resource = nullptr;
  std::byte* game = nullptr;
  float delta = 0.0F;
};

using PreDispatch00e76a80 = void (*)(const NativeCallContext&);
using Value00e67c40 = std::uint32_t (*)(const NativeCallContext&, std::uint32_t,
                                        std::uint32_t);
using Raw00e6f800 = void (*)(const NativeCallContext&, std::uint32_t, float,
                             float, std::uint32_t, std::uint32_t,
                             std::uint32_t);
using Priority00e71c00 = void (*)(const NativeCallContext&);
using Player00e6f5b0 = void (*)(const NativeCallContext&);
using Dispatch1001_00e71300 = void (*)(const NativeCallContext&);
using Dispatch1003_00e70650 = void (*)(const NativeCallContext&);
using Dispatch1004_00e704b0 = void (*)(const NativeCallContext&);
using Dispatch1005_00e702d0 = void (*)(const NativeCallContext&);
using Dispatch1006_00e7a0a0 = void (*)(const NativeCallContext&);
using Dispatch1007_00e6f990 = void (*)(const NativeCallContext&);
using Dispatch1008_00e78fc0 = void (*)(const NativeCallContext&);
using Dispatch1009_00e707d0 = void (*)(const NativeCallContext&);
using Dispatch100b_00e6fbb0 = void (*)(const NativeCallContext&);
using Dispatch100c_00e6fd70 = void (*)(const NativeCallContext&);
using Dispatch100d_00e6fce0 = void (*)(const NativeCallContext&);
using Dispatch100e_00e7a0d0 = void (*)(const NativeCallContext&);

struct NativePorts {
  static constexpr char boundary_metadata[] = "unresolved direct native calls";

  PreDispatch00e76a80 pre_dispatch_00e76a80 = nullptr;
  Value00e67c40 value_00e67c40 = nullptr;
  Raw00e6f800 raw_00e6f800 = nullptr;
  Priority00e71c00 priority_00e71c00 = nullptr;
  Player00e6f5b0 player_00e6f5b0 = nullptr;
  Dispatch1001_00e71300 dispatch_1001_00e71300 = nullptr;
  Dispatch1003_00e70650 dispatch_1003_00e70650 = nullptr;
  Dispatch1004_00e704b0 dispatch_1004_00e704b0 = nullptr;
  Dispatch1005_00e702d0 dispatch_1005_00e702d0 = nullptr;
  Dispatch1006_00e7a0a0 dispatch_1006_00e7a0a0 = nullptr;
  Dispatch1007_00e6f990 dispatch_1007_00e6f990 = nullptr;
  Dispatch1008_00e78fc0 dispatch_1008_00e78fc0 = nullptr;
  Dispatch1009_00e707d0 dispatch_1009_00e707d0 = nullptr;
  Dispatch100b_00e6fbb0 dispatch_100b_00e6fbb0 = nullptr;
  Dispatch100c_00e6fd70 dispatch_100c_00e6fd70 = nullptr;
  Dispatch100d_00e6fce0 dispatch_100d_00e6fce0 = nullptr;
  Dispatch100e_00e7a0d0 dispatch_100e_00e7a0d0 = nullptr;
};

void cell_behavior_dispatch_00e7a190(ObservedCellCellResource* resource,
                                     ObservedCellObjectData* object,
                                     float delta, NativePorts& ports);

}  // namespace openspore::reconstruction::pkg06c_cell_behavior_dispatch
