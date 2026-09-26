#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-frame-runtime-wave7 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define FRAME_RUNTIME_CDECL __cdecl
#define FRAME_RUNTIME_STDCALL __stdcall
#define FRAME_RUNTIME_THISCALL __thiscall
#else
#define FRAME_RUNTIME_CDECL __attribute__((cdecl))
#define FRAME_RUNTIME_STDCALL __attribute__((stdcall))
#define FRAME_RUNTIME_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_frame_runtime_wave7 {

using OpaqueWord = std::uint32_t;

struct OpaqueCellMode {
  std::uint8_t opaque[0x40]{};
};

struct OpaqueAppSystem;
struct OpaqueFrameStage;
struct OpaquePacingService;

struct OpaquePacingVtable {
  void* slots_00_30[13]{};
  bool(FRAME_RUNTIME_THISCALL* available_34)(OpaquePacingService*,
                                             std::int32_t) = nullptr;
};

struct OpaquePacingService {
  OpaquePacingVtable* vtable = nullptr;
};

struct OpaqueAppSystemVtable {
  void* slots_00_34[14]{};
  void(FRAME_RUNTIME_THISCALL* service_38)(OpaqueAppSystem*) = nullptr;
  void* slots_3c_40[2]{};
  bool(FRAME_RUNTIME_THISCALL* pacing_enabled_44)(OpaqueAppSystem*) = nullptr;
  void* slots_48_74[12]{};
  void(FRAME_RUNTIME_THISCALL* update_78)(OpaqueAppSystem*,
                                          std::int32_t) = nullptr;
  void(FRAME_RUNTIME_THISCALL* post_7c)(OpaqueAppSystem*) = nullptr;
  void(FRAME_RUNTIME_THISCALL* post_80)(OpaqueAppSystem*) = nullptr;
  OpaqueWord(FRAME_RUNTIME_THISCALL* request_pacing_84)(OpaqueAppSystem*,
                                                        OpaqueWord) = nullptr;
};

struct OpaqueAppSystem {
  OpaqueAppSystemVtable* vtable = nullptr;
};

struct OpaqueFrameStageVtable {
  void* slots_00_08[3]{};
  void(FRAME_RUNTIME_THISCALL* update_0c)(OpaqueFrameStage*,
                                          std::int32_t) = nullptr;
  void* slots_10_14[2]{};
  void(FRAME_RUNTIME_THISCALL* update_18)(OpaqueFrameStage*, float) = nullptr;
  void(FRAME_RUNTIME_THISCALL* update_1c)(OpaqueFrameStage*,
                                          std::int32_t) = nullptr;
  void(FRAME_RUNTIME_THISCALL* update_20)(OpaqueFrameStage*,
                                          std::int32_t) = nullptr;
  void* slot_24 = nullptr;
  void(FRAME_RUNTIME_THISCALL* update_28)(OpaqueFrameStage*,
                                          std::int32_t) = nullptr;
};

struct OpaqueFrameStage {
  OpaqueFrameStageVtable* vtable = nullptr;
};

struct OpaqueSporeApp {
  std::uint8_t opaque_00_0b[0x0c]{};
  std::uint8_t active_0c = 0;
  std::uint8_t opaque_0d_0f[3]{};
  std::uint64_t baseline_10 = 0;
  float tick_to_ms_18 = 1.0F;
  float baseline_scale_1c = 1.0F;
  OpaqueAppSystem* app_system_20 = nullptr;
  OpaqueWord opaque_24 = 0;
  void* direct_service_28 = nullptr;
  OpaqueFrameStage* float_stage_2c = nullptr;
  OpaqueFrameStage* last_stage_30 = nullptr;
  OpaqueFrameStage* first_stage_34 = nullptr;
  OpaqueFrameStage* middle_stage_38 = nullptr;
  OpaqueFrameStage* fourth_stage_3c = nullptr;
};

struct FrameRuntimePorts {
  using CellOrchestrator = void(FRAME_RUNTIME_CDECL*)(float, float);
  using QueryCounter = void(FRAME_RUNTIME_CDECL*)(std::uint64_t*);
  using MeasureElapsed = std::int32_t(FRAME_RUNTIME_THISCALL*)(OpaqueSporeApp*);
  using ReadPacingTarget = std::int32_t(FRAME_RUNTIME_CDECL*)();
  using AcquirePacingService = OpaquePacingService*(FRAME_RUNTIME_CDECL*)();
  using WaitMilliseconds = void(FRAME_RUNTIME_CDECL*)(const std::uint32_t*);
  using GetAppSystem = OpaqueAppSystem*(FRAME_RUNTIME_CDECL*)();
  using DirectServiceUpdate = void(FRAME_RUNTIME_THISCALL*)(void*,
                                                            std::int32_t);

  CellOrchestrator cell_orchestrator_00e806b0 = nullptr;
  QueryCounter query_performance_counter = nullptr;
  MeasureElapsed measure_elapsed_00f475b0 = nullptr;
  ReadPacingTarget read_pacing_target = nullptr;
  AcquirePacingService acquire_pacing_0068f4d0 = nullptr;
  WaitMilliseconds wait_milliseconds_00921df0 = nullptr;
  GetAppSystem get_app_system_0067dcc0 = nullptr;
  DirectServiceUpdate direct_service_00812d30 = nullptr;
};

extern FrameRuntimePorts* g_frame_runtime_ports;

static_assert(sizeof(void*) == 4, "x86-32 pointer width");
static_assert(offsetof(OpaquePacingVtable, available_34) == 0x34);
static_assert(offsetof(OpaqueAppSystemVtable, service_38) == 0x38);
static_assert(offsetof(OpaqueAppSystemVtable, pacing_enabled_44) == 0x44);
static_assert(offsetof(OpaqueAppSystemVtable, update_78) == 0x78);
static_assert(offsetof(OpaqueAppSystemVtable, post_7c) == 0x7c);
static_assert(offsetof(OpaqueAppSystemVtable, post_80) == 0x80);
static_assert(offsetof(OpaqueAppSystemVtable, request_pacing_84) == 0x84);
static_assert(offsetof(OpaqueFrameStageVtable, update_0c) == 0x0c);
static_assert(offsetof(OpaqueFrameStageVtable, update_18) == 0x18);
static_assert(offsetof(OpaqueFrameStageVtable, update_1c) == 0x1c);
static_assert(offsetof(OpaqueFrameStageVtable, update_20) == 0x20);
static_assert(offsetof(OpaqueFrameStageVtable, update_28) == 0x28);
static_assert(offsetof(OpaqueSporeApp, active_0c) == 0x0c);
static_assert(offsetof(OpaqueSporeApp, baseline_10) == 0x10);
static_assert(offsetof(OpaqueSporeApp, tick_to_ms_18) == 0x18);
static_assert(offsetof(OpaqueSporeApp, baseline_scale_1c) == 0x1c);
static_assert(offsetof(OpaqueSporeApp, app_system_20) == 0x20);
static_assert(offsetof(OpaqueSporeApp, direct_service_28) == 0x28);
static_assert(offsetof(OpaqueSporeApp, float_stage_2c) == 0x2c);
static_assert(offsetof(OpaqueSporeApp, last_stage_30) == 0x30);
static_assert(offsetof(OpaqueSporeApp, first_stage_34) == 0x34);
static_assert(offsetof(OpaqueSporeApp, middle_stage_38) == 0x38);
static_assert(offsetof(OpaqueSporeApp, fourth_stage_3c) == 0x3c);
static_assert(sizeof(OpaqueSporeApp) == 0x40);

extern "C" void FRAME_RUNTIME_THISCALL
cell_mode_update_00e80980(OpaqueCellMode*, float, float);

extern "C" void FRAME_RUNTIME_THISCALL
app_frame_update_00f47930(OpaqueSporeApp*);

}

#undef FRAME_RUNTIME_CDECL
#undef FRAME_RUNTIME_STDCALL
#undef FRAME_RUNTIME_THISCALL
