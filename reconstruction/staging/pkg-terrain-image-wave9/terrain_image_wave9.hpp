#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-terrain-image-wave9 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_TERRAIN_IMAGE_WAVE9_THISCALL __thiscall
#define PKG_TERRAIN_IMAGE_WAVE9_NAKED __declspec(naked)
#else
#define PKG_TERRAIN_IMAGE_WAVE9_THISCALL __attribute__((thiscall))
#define PKG_TERRAIN_IMAGE_WAVE9_NAKED __attribute__((naked))
#endif

namespace openspore::reconstruction::pkg_terrain_image_wave9 {

using OpaqueWord = std::uint32_t;

struct alignas(4) OpaqueSimulationTarget {
  std::array<std::uint8_t, 4> bytes_00{};
};

struct OpaqueSimulationProbe;

#if !defined(_MSC_VER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

using OpaqueSimulationSelect = OpaqueSimulationTarget*(
    PKG_TERRAIN_IMAGE_WAVE9_THISCALL*)(OpaqueSimulationProbe*, OpaqueWord);

struct alignas(4) OpaqueSimulationProbeVTable {
  std::array<void*, 22> slots_00{};
  OpaqueSimulationSelect select_58 = nullptr;
};

struct alignas(4) OpaqueSimulationProbe {
  OpaqueSimulationProbeVTable* vtable = nullptr;
  std::array<std::uint8_t, 8> opaque_04{};
};

struct alignas(4) OpaqueSimulationData {
  std::array<OpaqueWord, 2> words_00{};
};

struct alignas(4) OpaquePairDestination {
  OpaqueWord word_00 = 0;
  OpaqueWord word_04 = 0;
  OpaqueWord word_08 = 0;
  OpaqueWord word_0c = 0;
  OpaqueWord word_10 = 0;
  OpaqueWord guard_14 = 0;
};

struct alignas(4) OpaqueImageReceiver {
  OpaqueWord word_00 = 0;
  OpaqueWord word_04 = 0;
  OpaqueWord word_08 = 0;
};

using OpaqueWordPort = OpaqueWord (*)();
using OpaqueWordFirstUsePort = OpaqueWord (*)();

void set_opaque_word_port(OpaqueWordPort port);
void set_opaque_word_first_use_port(OpaqueWordFirstUsePort port);

extern "C" OpaqueWord opaque_word_first_use_011e5870();
extern "C" OpaqueWord opaque_word_port_011e58c0();

extern "C" OpaqueWord PKG_TERRAIN_IMAGE_WAVE9_THISCALL
    PKG_TERRAIN_IMAGE_WAVE9_NAKED
    terrain_probe_00f968b0(OpaqueSimulationData*, OpaqueSimulationProbe*);

extern "C" OpaqueWord PKG_TERRAIN_IMAGE_WAVE9_THISCALL
    PKG_TERRAIN_IMAGE_WAVE9_NAKED
    image_write_pair_00fc7e10(OpaquePairDestination*, OpaqueWord, OpaqueWord);

extern "C" void PKG_TERRAIN_IMAGE_WAVE9_THISCALL PKG_TERRAIN_IMAGE_WAVE9_NAKED
image_write_fields_00fd9460(OpaqueImageReceiver*, OpaqueWord);

#if !defined(_MSC_VER)
#pragma GCC diagnostic pop
#endif

static_assert(sizeof(void*) == 4,
              "pkg-terrain-image-wave9 requires 32-bit pointers");
static_assert(offsetof(OpaqueSimulationProbeVTable, select_58) == 0x58,
              "pkg-terrain-image-wave9 simulation slot");
static_assert(sizeof(OpaqueSimulationProbeVTable) == 0x5c,
              "pkg-terrain-image-wave9 simulation vtable size");
static_assert(sizeof(OpaqueSimulationData) == 8,
              "pkg-terrain-image-wave9 simulation prefix size");
static_assert(offsetof(OpaquePairDestination, word_08) == 0x08,
              "pkg-terrain-image-wave9 first pair word");
static_assert(offsetof(OpaquePairDestination, word_10) == 0x10,
              "pkg-terrain-image-wave9 second pair word");
static_assert(offsetof(OpaquePairDestination, guard_14) == 0x14,
              "pkg-terrain-image-wave9 pair guard");
static_assert(offsetof(OpaqueImageReceiver, word_04) == 0x04,
              "pkg-terrain-image-wave9 input field");
static_assert(offsetof(OpaqueImageReceiver, word_08) == 0x08,
              "pkg-terrain-image-wave9 output field");
static_assert(sizeof(OpaqueImageReceiver) == 0x0c,
              "pkg-terrain-image-wave9 receiver size");

}

#undef PKG_TERRAIN_IMAGE_WAVE9_THISCALL
#undef PKG_TERRAIN_IMAGE_WAVE9_NAKED
