#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-frame-runtime-wave8 requires an x86-32 target"
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

namespace openspore::reconstruction::pkg_frame_runtime_wave8 {

using OpaqueWord = std::uint32_t;

struct OpaquePlayer {
  std::uint8_t opaque_00_1b[0x1c]{};
  OpaqueWord word_1c = 0;
  OpaqueWord word_20 = 0;
  OpaqueWord word_24 = 0;
  OpaqueWord word_28 = 0;
  std::uint8_t opaque_2c_73[0x48]{};
  std::int32_t word_74 = 0;
};

struct OpaqueCellGame {
  std::uint8_t opaque_0000_410b[0x410c]{};
  std::uint8_t source_410c = 0;
  std::uint8_t opaque_410d_410f[3]{};
  OpaqueWord source_4110 = 0;
  std::uint8_t opaque_4114_515b[0x515c - 0x4114]{};
  std::int32_t gate_515c = 0;
  std::int32_t counter_5160 = 0;
  std::uint8_t opaque_5164_518f[0x5190 - 0x5164]{};
  OpaquePlayer *player_5190 = nullptr;
  std::uint8_t opaque_5194_51d7[0x51d8 - 0x5194]{};
  std::uint8_t reload_51d8 = 0;
  std::uint8_t reload_51d9 = 0;
  std::uint8_t opaque_51da_51df[0x51e0 - 0x51da]{};
  std::int32_t state_51e0 = 0;
};

struct OpaqueSpaceTrading;
struct OpaqueCellService;
struct OpaqueTextureManager;
struct OpaqueIdGenerator;
struct OpaqueRenderer;
struct OpaqueFrustum;
struct OpaqueTimingService;
struct OpaqueTimingRoot;
struct OpaqueTimingRuntime;
struct OpaqueTimingContext;
struct OpaqueLayerBuffer;
struct OpaqueLayerResult;
struct OpaqueTimingVector;
struct OpaqueTimingVector3;
struct OpaqueTimingConfig;
struct OpaqueTimingMatrix;

struct OpaqueSpaceTradingVtable {
  void *slots_00_34[14]{};
  void(FRAME_RUNTIME_THISCALL *update_38)(OpaqueSpaceTrading *, std::int32_t,
                                          std::int32_t) = nullptr;
};

struct OpaqueSpaceTrading {
  std::uint8_t opaque_00_03[4]{};
  OpaqueSpaceTradingVtable *vtable_04 = nullptr;
};

struct OpaqueCellServiceVtable {
  void *slots_00_34[14]{};
  void(FRAME_RUNTIME_THISCALL *update_38)(OpaqueCellService *, std::int32_t,
                                          std::int32_t) = nullptr;
};

struct OpaqueCellService {
  std::uint8_t opaque_00_03[4]{};
  OpaqueCellServiceVtable *vtable_04 = nullptr;
};

struct OpaqueTextureManagerVtable {
  void *slots_00_3c[16]{};
  void(FRAME_RUNTIME_THISCALL *tail_texture_40)(OpaqueTextureManager *) =
      nullptr;
};

struct OpaqueTextureManager {
  OpaqueTextureManagerVtable *vtable = nullptr;
};

struct OpaqueIdGeneratorVtable {
  void *slots_00_1c[8]{};
  void(FRAME_RUNTIME_THISCALL *generate_20)(OpaqueIdGenerator *,
                                            OpaqueWord) = nullptr;
};

struct OpaqueIdGenerator {
  OpaqueIdGeneratorVtable *vtable = nullptr;
};

struct OpaqueRendererVtable {
  void *slots_00_54[22]{};
  OpaqueLayerResult *(FRAME_RUNTIME_THISCALL *layer_58)(
      OpaqueRenderer *, OpaqueTimingMatrix *) = nullptr;
};

struct OpaqueRenderer {
  OpaqueRendererVtable *vtable = nullptr;
};

struct OpaqueTimingOwner {
  std::uint8_t opaque_00_03[4]{};
  OpaqueTimingService *service_04 = nullptr;
};

struct OpaqueTimingContext {
  std::uint8_t opaque[0x20]{};
};

struct OpaqueLayerBuffer {
  std::uint8_t opaque[0x20]{};
};

struct OpaqueLayerResult {
  std::uint8_t opaque[0x20]{};
};

struct OpaqueTimingVector {
  float word_00 = 0.0F;
  float word_04 = 0.0F;
};

struct OpaqueTimingVector3 {
  OpaqueWord word_00 = 0;
  OpaqueWord word_04 = 0;
  OpaqueWord word_08 = 0;
};

struct OpaqueTimingConfig {
  std::uint8_t opaque_00_23[0x24]{};
  float word_24 = 1.0F;
};

struct OpaqueTimingMatrix {
  float word_00 = 0.0F;
  float word_04 = 0.0F;
  float word_08 = 0.0F;
  float word_0c = 0.0F;
  float word_10 = 0.0F;
  float word_14 = 0.0F;
  float word_18 = 0.0F;
  float word_1c = 0.0F;
  float word_20 = 0.0F;
};

struct OpaqueTimingRoot {
  std::uint8_t opaque_00_53[0x54]{};
  OpaqueTimingRuntime *runtime_54 = nullptr;
};

struct OpaqueTimingRuntimeVtable {
  void *slots_00_28[11]{};
  OpaqueTimingVector3 *(FRAME_RUNTIME_THISCALL *vector_2c)(
      OpaqueTimingRuntimeVtable *) = nullptr;
};

struct OpaqueTimingRuntime {
  std::uint8_t opaque_00_bf[0xc0]{};
  OpaqueTimingRuntimeVtable *vtable_c0 = nullptr;
};

struct OpaqueTimingServiceVtable {
  void *slots_00_97[38]{};
  float(FRAME_RUNTIME_THISCALL *speed_98)(OpaqueTimingService *,
                                          OpaqueWord) = nullptr;
  void *slots_9c_a0[2]{};
  OpaqueTimingVector *(FRAME_RUNTIME_THISCALL *layer_a4)(OpaqueTimingService *,
                                                         OpaqueLayerBuffer *,
                                                         OpaqueWord) = nullptr;
};

struct OpaqueTimingService {
  OpaqueTimingServiceVtable *vtable = nullptr;
};

struct OpaqueCellRuntimePorts {
  using Prepare = void(FRAME_RUNTIME_CDECL *)();
  using SetWords = void(FRAME_RUNTIME_CDECL *)(std::int32_t, std::int32_t);
  using GetSpaceTrading = OpaqueSpaceTrading *(FRAME_RUNTIME_CDECL *)();
  using GetCellService = OpaqueCellService *(FRAME_RUNTIME_CDECL *)();
  using Ready = bool(FRAME_RUNTIME_CDECL *)();
  using GetTextureManager = OpaqueTextureManager *(FRAME_RUNTIME_CDECL *)();
  using GetIdGenerator = OpaqueIdGenerator *(FRAME_RUNTIME_CDECL *)();
  using MovePlayer = void(FRAME_RUNTIME_CDECL *)(float);
  using UpdateWord = void(FRAME_RUNTIME_CDECL *)(float);
  using UpdateWordFlag = void(FRAME_RUNTIME_CDECL *)(float, std::uint8_t);
  using UpdateNoWords = void(FRAME_RUNTIME_CDECL *)();
  using ReturnByte = std::uint8_t(FRAME_RUNTIME_CDECL *)();
  using DispatchReload = void(FRAME_RUNTIME_CDECL *)(OpaqueWord, OpaqueWord,
                                                     OpaqueWord, OpaqueWord,
                                                     std::uint8_t, OpaqueWord,
                                                     OpaqueWord);
  using BuildFrustum = void(FRAME_RUNTIME_THISCALL *)(OpaqueFrustum *,
                                                      OpaqueWord);

  Prepare prepare_00e84bf0 = nullptr;
  SetWords set_words_00e82de0 = nullptr;
  GetSpaceTrading get_space_trading_00b3d4d0 = nullptr;
  GetCellService get_cell_service_00b3d3f0 = nullptr;
  Ready ready_00e82c70 = nullptr;
  GetTextureManager get_texture_manager_0067dd20 = nullptr;
  GetIdGenerator get_id_generator_0067de20 = nullptr;
  MovePlayer move_player_00e5b790 = nullptr;
  UpdateWord update_word_00e7f3a0 = nullptr;
  ReturnByte update_return_00e7f550 = nullptr;
  DispatchReload dispatch_reload_00e7fd00 = nullptr;
  UpdateNoWords update_no_words_00e73f60 = nullptr;
  UpdateWord update_word_00e53b00 = nullptr;
  UpdateWordFlag update_word_flag_00e600a0 = nullptr;
  UpdateWord update_word_00e6c9f0 = nullptr;
  BuildFrustum build_frustum_006ffe00 = nullptr;
};

struct FrameRuntimePorts {
  OpaqueCellGame *cell_game = nullptr;
  OpaqueCellRuntimePorts cell{};
  using TimingLookup = const OpaqueWord *(
      FRAME_RUNTIME_THISCALL *)(OpaqueTimingContext *, OpaqueTimingContext **,
                                OpaqueWord, OpaqueWord);
  using TimingBegin = OpaqueTimingConfig *(FRAME_RUNTIME_CDECL *)();
  using TimingRootGet = OpaqueTimingRoot *(FRAME_RUNTIME_CDECL *)();
  using TimingRuntimeGet =
      OpaqueTimingRuntime *(FRAME_RUNTIME_THISCALL *)(OpaqueTimingRoot *);
  using TimingGetRenderer = OpaqueRenderer *(FRAME_RUNTIME_CDECL *)();
  using TimingInitFallback = void(FRAME_RUNTIME_THISCALL *)(
      OpaqueTimingMatrix *, const OpaqueTimingMatrix *);
  using TimingRelease = void(FRAME_RUNTIME_THISCALL *)(OpaqueLayerResult *);
  using TimingEnabled = bool(FRAME_RUNTIME_CDECL *)();
  using TimingApplyVectorFinish = void(FRAME_RUNTIME_THISCALL *)(
      OpaqueTimingConfig *, float, OpaqueTimingVector3 *);
  using TimingSpeedLookup =
      const OpaqueWord *(FRAME_RUNTIME_STDCALL *)(const char *, OpaqueWord);
  using TimingApplySpeedFinish =
      void(FRAME_RUNTIME_THISCALL *)(OpaqueTimingConfig *, float);

  TimingLookup timing_lookup_00838020 = nullptr;
  TimingBegin timing_begin_00bc30b0 = nullptr;
  TimingRootGet timing_root_00b3d300 = nullptr;
  TimingRuntimeGet timing_runtime_00b1fdb0 = nullptr;
  TimingGetRenderer timing_renderer_0067dd10 = nullptr;
  TimingInitFallback timing_init_0041cb40 = nullptr;
  TimingRelease timing_release_007c40f0 = nullptr;
  TimingEnabled timing_enabled_01021260 = nullptr;
  TimingApplyVectorFinish timing_bc2f00 = nullptr;
  TimingSpeedLookup timing_speed_lookup_00838330 = nullptr;
  TimingApplySpeedFinish timing_bc28c0 = nullptr;
  const OpaqueTimingMatrix *timing_matrix_0167e8e0 = nullptr;
};

extern FrameRuntimePorts *g_frame_runtime_wave8_ports;

static_assert(sizeof(void *) == 4, "x86-32 pointer width");
static_assert(offsetof(OpaquePlayer, word_74) == 0x74, "player word offset");
static_assert(offsetof(OpaqueCellGame, source_410c) == 0x410c,
              "cell source offset");
static_assert(offsetof(OpaqueCellGame, source_4110) == 0x4110,
              "cell source word offset");
static_assert(offsetof(OpaqueCellGame, reload_51d8) == 0x51d8,
              "cell reload gate offset");
static_assert(offsetof(OpaqueCellGame, reload_51d9) == 0x51d9,
              "cell reload secondary offset");
static_assert(offsetof(OpaqueCellGame, state_51e0) == 0x51e0,
              "cell state offset");
static_assert(offsetof(OpaqueCellGame, gate_515c) == 0x515c,
              "cell frame gate offset");
static_assert(offsetof(OpaqueCellGame, counter_5160) == 0x5160,
              "cell counter offset");
static_assert(offsetof(OpaqueCellGame, player_5190) == 0x5190,
              "cell player offset");
static_assert(offsetof(OpaqueSpaceTrading, vtable_04) == 0x04,
              "space vtable receiver offset");
static_assert(offsetof(OpaqueCellService, vtable_04) == 0x04,
              "cell service vtable receiver offset");
static_assert(offsetof(OpaqueSpaceTradingVtable, update_38) == 0x38,
              "space update slot");
static_assert(offsetof(OpaqueCellServiceVtable, update_38) == 0x38,
              "cell service update slot");
static_assert(offsetof(OpaqueTextureManagerVtable, tail_texture_40) == 0x40,
              "texture tail slot");
static_assert(offsetof(OpaqueIdGeneratorVtable, generate_20) == 0x20,
              "identifier generate slot");
static_assert(offsetof(OpaqueRendererVtable, layer_58) == 0x58,
              "renderer layer slot");
static_assert(offsetof(OpaqueTimingServiceVtable, speed_98) == 0x98,
              "timing speed slot");
static_assert(offsetof(OpaqueTimingServiceVtable, layer_a4) == 0xa4,
              "timing layer slot");
static_assert(offsetof(OpaqueTimingRoot, runtime_54) == 0x54,
              "timing root runtime offset");
static_assert(offsetof(OpaqueTimingRuntime, vtable_c0) == 0xc0,
              "timing embedded vtable offset");
static_assert(offsetof(OpaqueTimingOwner, service_04) == 0x04,
              "timing owner service offset");
static_assert(sizeof(OpaqueCellGame) == 0x51e4, "cell state size");

extern "C" void FRAME_RUNTIME_CDECL
cell_update_body_00e806b0(float first_stack_word, float second_stack_word);

extern "C" void FRAME_RUNTIME_THISCALL timing_update_body_00b31cc0(
    OpaqueTimingOwner *receiver, OpaqueTimingContext *first_stack_word);

static_assert(std::is_same<decltype(&cell_update_body_00e806b0),
                           void(FRAME_RUNTIME_CDECL *)(float, float)>::value,
              "cell body cdecl stack signature");
static_assert(
    std::is_same<decltype(&timing_update_body_00b31cc0),
                 void(FRAME_RUNTIME_THISCALL *)(OpaqueTimingOwner *,
                                                OpaqueTimingContext *)>::value,
    "timing body thiscall signature");

}

#undef FRAME_RUNTIME_CDECL
#undef FRAME_RUNTIME_STDCALL
#undef FRAME_RUNTIME_THISCALL
