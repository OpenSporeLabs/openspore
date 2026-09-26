#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-SKINNER-SAFE-WAVE10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SKINNER_SAFE_WAVE10_THISCALL __thiscall
#define PKG_SKINNER_SAFE_WAVE10_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_SKINNER_SAFE_WAVE10_THISCALL __attribute__((thiscall))
#define PKG_SKINNER_SAFE_WAVE10_CDECL __attribute__((cdecl))
#else
#error "PKG-SKINNER-SAFE-WAVE10 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_skinner_safe_wave10 {

static_assert(sizeof(void *) == 4,
              "PKG-SKINNER-SAFE-WAVE10 requires 32-bit pointers");
static_assert(sizeof(float) == 4,
              "PKG-SKINNER-SAFE-WAVE10 requires 32-bit float");
static_assert(sizeof(std::int32_t) == 4,
              "PKG-SKINNER-SAFE-WAVE10 requires 32-bit int32");

struct OpaqueLayerFactory;
struct OpaqueTexturePainter;

struct alignas(4) OpaqueSkinPainterState {
  std::uint8_t opaque_000[0x0c];
  void *secondary_00c;
  OpaqueTexturePainter *texture_painter_010;
  OpaqueTexturePainter *texture_painter_014;
  OpaqueTexturePainter *texture_painter_018;
  std::uint32_t source_01c;
  float scale_020;
  float scale_024;
  float scale_028;
  float scale_02c;
  float scale_030;
};

struct alignas(4) OpaquePainterJob {
  std::uint8_t opaque_000[0x14];
  std::int32_t pass_014;
  std::uint8_t opaque_018[0x18];
};

using GraphicsQuerySlot =
    std::uint8_t(PKG_SKINNER_SAFE_WAVE10_THISCALL *)(void *);

struct alignas(4) OpaqueGraphicsProbeVTable {
  std::uint8_t opaque_000[0x44];
  GraphicsQuerySlot query_044;
};

struct alignas(4) OpaqueGraphicsProbe {
  OpaqueGraphicsProbeVTable *vtable_000;
};

using AcquireLayerFactory = OpaqueLayerFactory *(
    PKG_SKINNER_SAFE_WAVE10_CDECL *)(std::uint32_t, std::uint32_t,
                                     std::uint32_t, std::uint32_t,
                                     std::uint32_t, std::uint32_t);

using CreateTexturePainter = OpaqueTexturePainter *(
    PKG_SKINNER_SAFE_WAVE10_THISCALL *)(OpaqueLayerFactory *, std::uint32_t,
                                        std::uint32_t);

using GetGraphicsProbe =
    OpaqueGraphicsProbe *(PKG_SKINNER_SAFE_WAVE10_CDECL *)();

using AdvancePainterJob =
    std::uint32_t(PKG_SKINNER_SAFE_WAVE10_THISCALL *)(OpaquePainterJob *);

static_assert(offsetof(OpaqueSkinPainterState, secondary_00c) == 0x0c,
              "painter state secondary offset");
static_assert(offsetof(OpaqueSkinPainterState, texture_painter_010) == 0x10,
              "painter state first painter offset");
static_assert(offsetof(OpaqueSkinPainterState, texture_painter_014) == 0x14,
              "painter state second painter offset");
static_assert(offsetof(OpaqueSkinPainterState, texture_painter_018) == 0x18,
              "painter state third painter offset");
static_assert(offsetof(OpaqueSkinPainterState, source_01c) == 0x1c,
              "painter state source offset");
static_assert(offsetof(OpaqueSkinPainterState, scale_020) == 0x20,
              "painter state first scale offset");
static_assert(offsetof(OpaqueSkinPainterState, scale_024) == 0x24,
              "painter state second scale offset");
static_assert(offsetof(OpaqueSkinPainterState, scale_028) == 0x28,
              "painter state third scale offset");
static_assert(offsetof(OpaqueSkinPainterState, scale_02c) == 0x2c,
              "painter state fourth scale offset");
static_assert(offsetof(OpaqueSkinPainterState, scale_030) == 0x30,
              "painter state fifth scale offset");
static_assert(sizeof(OpaqueSkinPainterState) == 0x34, "painter state size");
static_assert(offsetof(OpaquePainterJob, pass_014) == 0x14,
              "painter job pass offset");
static_assert(sizeof(OpaquePainterJob) == 0x30, "painter job size");
static_assert(offsetof(OpaqueGraphicsProbeVTable, query_044) == 0x44,
              "graphics probe query slot offset");
static_assert(sizeof(OpaqueGraphicsProbeVTable) == 0x48,
              "graphics probe vtable size");
static_assert(offsetof(OpaqueGraphicsProbe, vtable_000) == 0x00,
              "graphics probe vtable offset");
static_assert(sizeof(OpaqueGraphicsProbe) == 0x04, "graphics probe size");
static_assert(sizeof(AcquireLayerFactory) == 4, "port pointer size");
static_assert(sizeof(GraphicsQuerySlot) == 4, "vtable slot pointer size");

inline constexpr std::uint32_t kAcquireTag = 0x00000064u;
inline constexpr std::uint32_t kAcquireName = 0x013f116cu;
inline constexpr std::uint32_t kAcquireZero3 = 0x00000000u;
inline constexpr std::uint32_t kAcquireZero4 = 0x00000000u;
inline constexpr std::uint32_t kAcquireZero5 = 0x00000000u;
inline constexpr std::uint32_t kAcquireZero6 = 0x00000000u;
inline constexpr std::uint32_t kScaleSlot020 = 0x01471064u;
inline constexpr std::uint32_t kScaleSlot024 = 0x01485720u;
inline constexpr std::uint32_t kScaleSlot028 = 0x013eecd8u;
inline constexpr std::uint32_t kScaleSlot02c = 0x01485720u;
inline constexpr std::uint32_t kScaleSlot030 = 0x01485720u;
inline constexpr std::int32_t kAttemptLimit = 12;
inline constexpr std::uint32_t kLowByteMask = 0x000000ffu;
inline constexpr std::uint32_t kBrushPassFalse = 0u;
inline constexpr std::uint32_t kBrushPassTrue = 1u;
inline constexpr std::int32_t kPassZero = 0;
inline constexpr std::int32_t kPassTwo = 2;
inline constexpr std::int32_t kPassThree = 3;
inline constexpr std::size_t kProbeQuerySlotIndex = 0x44u / 4u;

extern float g_float_01471064;
extern float g_float_01485720;
extern float g_float_013eecd8;

extern "C" OpaqueLayerFactory *PKG_SKINNER_SAFE_WAVE10_CDECL
unresolved_00f473a0(std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
                    std::uint32_t, std::uint32_t);

extern "C" OpaqueTexturePainter *PKG_SKINNER_SAFE_WAVE10_THISCALL
unresolved_005288f0(OpaqueLayerFactory *, std::uint32_t, std::uint32_t);

extern "C" OpaqueGraphicsProbe *PKG_SKINNER_SAFE_WAVE10_CDECL
unresolved_0067dd00();

extern "C" std::uint32_t PKG_SKINNER_SAFE_WAVE10_THISCALL
unresolved_00517430(OpaquePainterJob *);

extern "C" void PKG_SKINNER_SAFE_WAVE10_THISCALL
skin_painter_state_setup_00506590(OpaqueSkinPainterState *state,
                                  std::uint32_t source);

extern "C" std::uint32_t PKG_SKINNER_SAFE_WAVE10_THISCALL
skin_painter_job_brush_pass_005182f0(OpaquePainterJob *job);

}

#undef PKG_SKINNER_SAFE_WAVE10_THISCALL
#undef PKG_SKINNER_SAFE_WAVE10_CDECL
