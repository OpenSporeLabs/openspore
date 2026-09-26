#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG skinner wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SKINNER_WAVE10_CDECL __cdecl
#define PKG_SKINNER_WAVE10_THISCALL __thiscall
#else
#define PKG_SKINNER_WAVE10_CDECL __attribute__((cdecl))
#define PKG_SKINNER_WAVE10_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_skinner_wave10 {

static_assert(sizeof(void*) == 4,
              "pkg-skinner-wave10 requires 32-bit pointers");
static_assert(sizeof(float) == 4, "pkg-skinner-wave10 requires 32-bit floats");
static_assert(sizeof(bool) == 1, "pkg-skinner-wave10 requires one-byte bools");

using TargetWord = std::uint32_t;
using TargetSignedWord = std::int32_t;

struct OpaqueLayerFactory;
struct OpaqueTexturePainter;
struct OpaqueSkinTexture;
struct OpaqueSkinPainter;
struct OpaquePaintSystem;
struct OpaqueGraphicsProbe;
struct OpaqueLightingManager;
struct OpaqueSubmitState;
struct OpaquePainterState;
struct OpaquePainterJob;

using AcquireLayerFactory = OpaqueLayerFactory*(
    PKG_SKINNER_WAVE10_CDECL*)(TargetWord key_0, TargetWord key_1,
                               TargetWord zero_2, TargetWord zero_3,
                               TargetWord zero_4, TargetWord zero_5);

using CreateTexturePainter = OpaqueTexturePainter*(
    PKG_SKINNER_WAVE10_THISCALL*)(OpaqueLayerFactory*, TargetWord source_0,
                                  TargetWord source_1);

using ReadFixedFloat = float (*)(TargetWord address);

using GetPaintSystem = OpaquePaintSystem*(PKG_SKINNER_WAVE10_CDECL*)();
using GetGraphicsProbe = OpaqueGraphicsProbe*(PKG_SKINNER_WAVE10_CDECL*)();
using GetLightingManager = OpaqueLightingManager*(PKG_SKINNER_WAVE10_CDECL*)();

using ResetSubmitState =
    OpaqueSubmitState*(PKG_SKINNER_WAVE10_THISCALL*)(OpaqueSubmitState * state);

using PainterJobStep =
    std::uint8_t(PKG_SKINNER_WAVE10_THISCALL*)(OpaquePainterJob* job);

using PainterJobBrushPass =
    TargetWord(PKG_SKINNER_WAVE10_THISCALL*)(OpaquePainterJob* job);

using GraphicsQuery = bool(PKG_SKINNER_WAVE10_THISCALL*)(OpaqueGraphicsProbe*);

using SubmitPaintJob = void(PKG_SKINNER_WAVE10_THISCALL*)(
    OpaqueLightingManager* manager, TargetWord zero_0,
    OpaqueSubmitState* state_1, OpaquePainterJob* job_2);

struct OpaquePainterJobVTable {
  void* slots_000[5]{};
  PainterJobStep job_step_014 = nullptr;
  void* slot_018 = nullptr;
  PainterJobBrushPass apply_brushes_01c = nullptr;
};

struct OpaquePainterJob {
  OpaquePainterJobVTable* vtable_000 = nullptr;
  TargetWord field_004 = 0;
  TargetWord field_008 = 0;
  std::uint8_t completed_00c = 0;
  std::uint8_t padding_00d[3]{};
  void* records_010 = nullptr;
  TargetSignedWord pass_014 = 0;
  std::uint8_t opaque_018[0x18]{};
};

struct OpaquePainterState {
  void* vtable_000 = nullptr;
  TargetWord field_004 = 0;
  TargetWord field_008 = 0;
  std::uint8_t flag_00c = 0;
  std::uint8_t padding_00d[3]{};
  OpaqueTexturePainter* texture_painter_010 = nullptr;
  OpaqueTexturePainter* texture_painter_014 = nullptr;
  OpaqueTexturePainter* texture_painter_018 = nullptr;
  TargetWord source_01c = 0;
  float scale_020 = 0.0F;
  float scale_024 = 0.0F;
  float scale_028 = 0.0F;
  float scale_02c = 0.0F;
  float scale_030 = 0.0F;
};

struct OpaqueSubmitState {
  TargetWord field_000 = 0;
  TargetWord field_004 = 0;
  std::uint8_t field_008 = 0;
  std::uint8_t padding_009[3]{};
  TargetWord field_00c = 0;
  TargetWord field_010 = 0;
  TargetWord field_014 = 0;
  TargetWord field_018 = 0;
  TargetWord field_01c = 0;
  TargetWord field_020 = 0;
  TargetWord field_024 = 0;
  TargetWord field_028 = 0;
};

struct OpaqueSkinPainter {
  void* fields_000[4]{};
  OpaqueSkinTexture* texture_010 = nullptr;
};

struct OpaquePaintSystem {
  void* fields_000[3]{};
  OpaqueSkinPainter* painter_00c = nullptr;
};

struct OpaqueGraphicsProbeVTable {
  void* slots_000[17]{};
  GraphicsQuery query_044 = nullptr;
};

struct OpaqueGraphicsProbe {
  OpaqueGraphicsProbeVTable* vtable_000 = nullptr;
};

struct OpaqueLightingManagerVTable {
  void* slots_000[29]{};
  SubmitPaintJob submit_074 = nullptr;
};

struct OpaqueLightingManager {
  OpaqueLightingManagerVTable* vtable_000 = nullptr;
};

struct SkinnerWave10Ports {
  AcquireLayerFactory acquire_layer_factory_00f473a0 = nullptr;
  CreateTexturePainter create_texture_painter_005288f0 = nullptr;
  ReadFixedFloat read_fixed_float = nullptr;
  GetPaintSystem get_paint_system_00401080 = nullptr;
  GetGraphicsProbe get_graphics_probe_0067dd00 = nullptr;
  ResetSubmitState reset_submit_state_00517240 = nullptr;
  GetLightingManager get_lighting_manager_0067dd50 = nullptr;
  PainterJobStep advance_painter_job_00517430 = nullptr;
};

extern SkinnerWave10Ports g_skinner_wave10_ports;

static_assert(offsetof(OpaquePainterJobVTable, job_step_014) == 0x14,
              "painter job step slot offset");
static_assert(offsetof(OpaquePainterJobVTable, apply_brushes_01c) == 0x1c,
              "painter job brush pass slot offset");
static_assert(offsetof(OpaquePainterJob, vtable_000) == 0x00,
              "painter job vtable offset");
static_assert(offsetof(OpaquePainterJob, completed_00c) == 0x0c,
              "painter job completed flag offset");
static_assert(offsetof(OpaquePainterJob, pass_014) == 0x14,
              "painter job pass offset");
static_assert(sizeof(OpaquePainterJob) == 0x30, "painter job size");
static_assert(offsetof(OpaquePainterState, flag_00c) == 0x0c,
              "painter state flag offset");
static_assert(offsetof(OpaquePainterState, texture_painter_010) == 0x10,
              "painter state first painter offset");
static_assert(offsetof(OpaquePainterState, texture_painter_014) == 0x14,
              "painter state second painter offset");
static_assert(offsetof(OpaquePainterState, texture_painter_018) == 0x18,
              "painter state third painter offset");
static_assert(offsetof(OpaquePainterState, source_01c) == 0x1c,
              "painter state source offset");
static_assert(offsetof(OpaquePainterState, scale_020) == 0x20,
              "painter state first scale offset");
static_assert(offsetof(OpaquePainterState, scale_024) == 0x24,
              "painter state second scale offset");
static_assert(offsetof(OpaquePainterState, scale_028) == 0x28,
              "painter state third scale offset");
static_assert(offsetof(OpaquePainterState, scale_02c) == 0x2c,
              "painter state fourth scale offset");
static_assert(offsetof(OpaquePainterState, scale_030) == 0x30,
              "painter state fifth scale offset");
static_assert(sizeof(OpaquePainterState) == 0x34, "painter state size");
static_assert(sizeof(OpaqueSubmitState) == 0x2c, "submit state size");
static_assert(offsetof(OpaqueSkinPainter, texture_010) == 0x10,
              "skin painter texture offset");
static_assert(offsetof(OpaquePaintSystem, painter_00c) == 0x0c,
              "paint system painter offset");
static_assert(offsetof(OpaqueGraphicsProbeVTable, query_044) == 0x44,
              "graphics probe query slot offset");
static_assert(offsetof(OpaqueLightingManagerVTable, submit_074) == 0x74,
              "lighting manager submit slot offset");

inline constexpr TargetWord kAcquireKey0 = 0x00000064u;
inline constexpr TargetWord kAcquireKey1 = 0x013f116cu;
inline constexpr TargetWord kScaleSlot020 = 0x01471064u;
inline constexpr TargetWord kScaleSlot024 = 0x01485720u;
inline constexpr TargetWord kScaleSlot028 = 0x013eecd8u;
inline constexpr TargetWord kScaleSlot02c = 0x01485720u;
inline constexpr TargetWord kScaleSlot030 = 0x01485720u;
inline constexpr TargetWord kSubmitMode = 0x0000000au;
inline constexpr TargetWord kSubmitZero0 = 0x00000000u;
inline constexpr TargetWord kSlotCountLow = 1u;
inline constexpr TargetWord kSlotCountHigh = 4u;
inline constexpr TargetWord kPassAttemptLimit = 12u;
inline constexpr TargetWord kBrushPassTrue = 1u;
inline constexpr TargetWord kBrushPassFalse = 0u;

extern "C" void PKG_SKINNER_WAVE10_THISCALL
skin_painter_state_setup_00506590(OpaquePainterState* state, TargetWord source);

extern "C" void PKG_SKINNER_WAVE10_THISCALL skin_painter_job_run_00517160(
    OpaquePainterJob* job, TargetWord arg_1, TargetWord arg_2, TargetWord arg_3,
    TargetWord arg_4);

extern "C" TargetWord PKG_SKINNER_WAVE10_THISCALL
skin_painter_job_brush_pass_005182f0(OpaquePainterJob* job);

}

#undef PKG_SKINNER_WAVE10_CDECL
#undef PKG_SKINNER_WAVE10_THISCALL
