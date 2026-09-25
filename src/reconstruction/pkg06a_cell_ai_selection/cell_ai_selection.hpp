#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-06A reconstruction requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-06A target pointers are 32-bit");
static_assert(sizeof(std::int32_t) == 4, "PKG-06A target words are 32-bit");

namespace openspore::reconstruction::pkg06a_cell_ai_selection {

struct alignas(4) ObservedCellAiData {
  std::int32_t type;
  std::byte opaque[0xb0];
};

static_assert(offsetof(ObservedCellAiData, type) == 0,
              "Observed AI type is at target offset 0x0");
static_assert(sizeof(ObservedCellAiData) == 0xb4,
              "Observed AI profile stride is 0xb4");

struct alignas(4) ObservedCellCellResource {
  std::byte prefix[0xe0];
  ObservedCellAiData normal;
  ObservedCellAiData ai_hard;
  ObservedCellAiData ai_easy;
};

static_assert(offsetof(ObservedCellCellResource, normal) == 0xe0,
              "Normal AI profile is at target offset 0xe0");
static_assert(offsetof(ObservedCellCellResource, ai_hard) == 0x194,
              "Hard AI profile is at target offset 0x194");
static_assert(offsetof(ObservedCellCellResource, ai_easy) == 0x248,
              "Easy AI profile is at target offset 0x248");
static_assert(offsetof(ObservedCellCellResource, ai_hard) -
                      offsetof(ObservedCellCellResource, normal) ==
                  sizeof(ObservedCellAiData),
              "Observed AI profile stride is 0xb4");
static_assert(offsetof(ObservedCellCellResource, ai_easy) -
                      offsetof(ObservedCellCellResource, ai_hard) ==
                  sizeof(ObservedCellAiData),
              "Observed AI profile stride is 0xb4");

extern std::byte* g_cell_game_016b3c04;

extern "C" ObservedCellAiData* cell_ai_select_profile_00e52910(
    ObservedCellCellResource* resource);

}
