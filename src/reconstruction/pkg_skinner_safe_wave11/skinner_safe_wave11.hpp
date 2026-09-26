#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG skinner wave11 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SKINNER_SAFE_WAVE11_CDECL __cdecl
#define PKG_SKINNER_SAFE_WAVE11_THISCALL __thiscall
#else
#define PKG_SKINNER_SAFE_WAVE11_CDECL __attribute__((cdecl))
#define PKG_SKINNER_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_skinner_safe_wave11 {

static_assert(sizeof(void*) == 4,
              "pkg-skinner-safe-wave11 requires 32-bit pointers");
static_assert(sizeof(float) == 4,
              "pkg-skinner-safe-wave11 requires 32-bit floats");
static_assert(sizeof(bool) == 1,
              "pkg-skinner-safe-wave11 requires one-byte bools");
static_assert(sizeof(short) == 2,
              "pkg-skinner-safe-wave11 requires 16-bit rigblock flags");

using TargetWord = std::uint32_t;
using TargetSignedWord = std::int32_t;
using TargetByte = std::uint8_t;
using TargetHalf = std::uint16_t;

struct OpaqueVec2 {
  float a;
  float b;
};

struct OpaqueVec3f {
  float a;
  float b;
  float c;
};

struct OpaqueVec3w {
  TargetWord a;
  TargetWord b;
  TargetWord c;
};

struct OpaqueVec4f {
  float a;
  float b;
  float c;
  float d;
};

struct OpaqueKeyBlock {
  TargetWord w0;
  TargetWord w1;
  TargetWord w2;
};

struct OpaqueTexturePainter;
struct OpaqueHandle;
struct OpaqueSkinPainter;
struct OpaquePaintSystem;
struct OpaqueMesh;
struct OpaqueGraphicsProbe;
struct OpaqueRenderTargetManager;
struct OpaqueRefObject;
struct OpaqueSkinJob;
struct OpaqueSkinJobState;

struct OpaqueTexturePainter {
  OpaqueRefObject* vtable_000;
  TargetWord field_004;
  TargetWord field_008;
  OpaqueVec4f params_00c;
  OpaqueVec4f params_01c;
  OpaqueVec4f params_02c;
  OpaqueHandle* rasters_03c;
  OpaqueHandle* rasters_040;
  TargetSignedWord count_044;
  TargetSignedWord count_048;
  TargetWord field_04c;
  TargetWord field_050;
  TargetWord field_054;
  TargetWord field_058;
  TargetWord field_05c;
  OpaqueHandle* field_060;
  TargetWord field_064;
};

struct OpaqueSkinPainter {
  TargetWord field_000;
  TargetWord field_004;
  TargetWord field_008;
  TargetWord field_00c;
  OpaqueTexturePainter* textures_010[3];
  TargetWord field_01c;
  TargetWord field_020;
  TargetWord field_024;
  TargetWord field_028;
  float scale_02c;
  float scale_030;
  TargetWord field_034;
  TargetWord field_038;
  TargetWord field_03c;
  TargetWord field_040;
  TargetSignedWord count_044;
  TargetWord field_048;
  TargetWord field_04c;
  TargetWord field_050;
  TargetWord field_054;
  TargetWord field_058;
  TargetWord field_05c;
  TargetWord field_060;
  TargetWord field_064;
  TargetWord field_068;
  TargetWord field_06c;
  TargetWord field_070;
  TargetWord field_074;
  TargetWord field_078;
  TargetWord field_07c;
  TargetWord field_080;
  TargetWord field_084;
  TargetWord field_088;
  TargetWord field_08c;
  OpaqueVec4f* slots_090;
  TargetWord field_094;
  TargetWord field_098;
};

struct OpaqueBatchSlot {
  std::uint8_t opaque_000[0x58];
  float field_058;
  float field_05c;
  float field_060;
  float field_064;
  std::uint8_t opaque_068[0x7c];
};

struct OpaqueBatch {
  TargetWord field_000;
  std::uint8_t opaque_004[0x2c];
  TargetWord* vertices_030;
  std::uint8_t opaque_034[0x24];
  TargetWord* parts_begin_058;
  TargetWord* parts_end_05c;
  std::uint8_t opaque_060[0x20];
  TargetWord* index_080;
  std::uint8_t opaque_084[0x60];
  OpaqueBatchSlot** slots_begin_0e4;
  OpaqueBatchSlot** slots_end_0e8;
};

struct OpaqueRigblock;

struct OpaqueMeshBlock {
  TargetWord field_000;
  TargetWord field_004;
  TargetWord* field_008;
  TargetWord* field_00c;
  TargetWord field_010;
  TargetWord field_014;
  TargetWord field_018;
  TargetWord field_01c;
  std::uint8_t opaque_020[0x78];
  OpaqueRigblock* rigblocks_098;
  OpaqueRigblock* rigblocks_09c;
};

struct OpaqueMesh {
  TargetWord field_000;
  TargetWord field_004;
  OpaqueMeshBlock* field_008;
  TargetWord* ids_00c;
  std::uint8_t opaque_010[0x80];
  OpaqueVec4f* slots_090;
  OpaqueRigblock* rigblocks_098;
  OpaqueRigblock* rigblocks_09c;
};

struct OpaqueRigblock {
  std::uint8_t opaque_000[8];
  TargetHalf flags_008;
  std::uint8_t opaque_00a[0x82];
};

struct OpaquePaintSystem {
  TargetWord field_000;
  TargetWord field_004;
  TargetWord field_008;
  OpaqueSkinPainter* painter_00c;
  OpaqueBatch* batch_010;
  TargetWord field_014;
  TargetWord field_018;
  TargetWord field_01c;
  OpaqueMesh* mesh_020;
  std::uint8_t opaque_024[0x58];
  TargetByte byte_07c;
  std::uint8_t opaque_07d;
  TargetByte byte_07e;
};

struct OpaqueGraphicsProbeVTable {
  void* slots_000[17];
  TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL* query_044)(OpaqueGraphicsProbe*);
};

struct OpaqueGraphicsProbe {
  OpaqueGraphicsProbeVTable* vtable_000;
};

using GraphicsQuery =
    TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueGraphicsProbe*);

using CreateFromBlock = OpaqueRefObject*(
    PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueRenderTargetManager*,
                                       OpaqueKeyBlock block, TargetWord tag);

using CreateRaw = OpaqueRefObject*(
    PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueRenderTargetManager*,
                                       TargetWord arg_0, TargetWord arg_1,
                                       TargetWord arg_2);

using CanCreate = TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(
    OpaqueRenderTargetManager*, OpaqueKeyBlock block);

using Prepare = TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(
    OpaqueRenderTargetManager*, OpaqueRefObject*);

struct OpaqueRenderTargetManagerVTable {
  void* slots_000[7];
  CreateFromBlock create_01c;
  CreateRaw create_020;
  CanCreate can_create_024;
  void* slots_028[3];
  Prepare prepare_034;
};

struct OpaqueRenderTargetManager {
  OpaqueRenderTargetManagerVTable* vtable_000;
};

using RefAddRef =
    TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueRefObject*);
using RefRelease =
    TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueRefObject*);
using RefStep = TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueRefObject*);

struct OpaqueRefVTable {
  RefAddRef add_000;
  RefRelease release_004;
  void* slots_008[2];
  RefStep step_010;
};

struct OpaqueRefObject {
  OpaqueRefVTable* vtable_000;
  TargetWord field_004;
  TargetWord refcount_008;
  TargetByte flag_00c;
  std::uint8_t opaque_00d[3];
  TargetWord field_010;
  TargetWord field_014;
  TargetWord field_018;
  TargetWord field_01c;
  TargetWord field_020;
  TargetWord field_024;
  TargetWord field_028;
  TargetWord field_02c;
  std::uint8_t opaque_030[0x10];
  TargetWord field_040;
  TargetWord field_044;
  TargetWord field_048;
  TargetWord field_04c;
  TargetWord field_050;
  TargetWord field_054;
  TargetWord field_058;
  TargetWord field_05c;
  TargetWord field_060;
  TargetWord field_064;
};

using RenderDispatch = TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(
    OpaqueRefObject*, TargetWord material, TargetWord colour, TargetWord tail);

struct OpaqueRenderObjectVTable {
  void* slots_000[11];
  RenderDispatch dispatch_02c;
};

struct OpaqueVector {
  TargetWord field_000;
  TargetWord field_004;
  TargetWord field_008;
};

struct OpaqueSkinJobState {
  TargetWord field_000;
  TargetWord field_004;
  TargetWord field_008;
  TargetWord field_00c;
  TargetSignedWord field_010;
  TargetSignedWord field_014;
  TargetSignedWord field_018;
};

struct OpaqueSkinJob {
  OpaqueRefObject* vtable_000;
  TargetWord field_004;
  TargetWord* array_008;
  TargetWord* array_00c;
  std::uint8_t opaque_010[0x310];
  TargetWord field_320;
  TargetWord field_324;
  TargetWord field_328;
  TargetWord field_32c;
  OpaqueRefObject* handle_330;
  TargetWord field_334;
  TargetWord field_338;
  TargetWord state_33c;
  TargetWord cursor_340;
  TargetWord calls_344;
  TargetByte flag_348;
  TargetByte flag_349;
  TargetByte flag_34a;
  TargetByte flag_34b;
  TargetByte flag_34c;
  TargetByte flag_34d;
  TargetByte flag_34e;
};

using GetPaintSystem = OpaquePaintSystem*(PKG_SKINNER_SAFE_WAVE11_CDECL*)();
using GetGraphicsProbe = OpaqueGraphicsProbe*(PKG_SKINNER_SAFE_WAVE11_CDECL*)();
using GetRenderTargetManager =
    OpaqueRenderTargetManager*(PKG_SKINNER_SAFE_WAVE11_CDECL*)();
using GetRenderObject = OpaqueRefObject*(PKG_SKINNER_SAFE_WAVE11_CDECL*)();
using GetScale = float(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueRefObject*,
                                                          TargetWord key);
using Classify = TargetWord(PKG_SKINNER_SAFE_WAVE11_CDECL*)(TargetWord id);
using GetFloat = bool(PKG_SKINNER_SAFE_WAVE11_CDECL*)(TargetWord object,
                                                      TargetWord key,
                                                      float* out);
using GetKey = bool(PKG_SKINNER_SAFE_WAVE11_CDECL*)(TargetWord id,
                                                    TargetWord key,
                                                    OpaqueKeyBlock* out);

using StartRender =
    void(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueTexturePainter*);
using SetColorWrite = void(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(
    OpaqueTexturePainter*, TargetWord a0, TargetWord a1, TargetWord a2,
    TargetWord a3);
using PaintRegion = void(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(
    OpaqueTexturePainter*, const OpaqueVec2* a0, const OpaqueVec2* a1,
    TargetWord a2);
using EndRender =
    void(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueTexturePainter*);
using EmitVertex = void(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(
    OpaqueTexturePainter*, const OpaqueVec2* pos, const OpaqueVec2* uv,
    const OpaqueVec3w* nrm, TargetWord colour);
using SetVertexLimit = TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(
    OpaqueTexturePainter*, TargetWord requested);
using FlushBatch =
    void(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueTexturePainter*);
using GetRaster =
    OpaqueRefObject*(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaquePaintSystem*);
using Truncate = void(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueVector*,
                                                         OpaqueRefObject* begin,
                                                         OpaqueRefObject* end);
using LazyReset =
    TargetWord(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueRefObject**);
using SwapPairs = void(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(void*, void*);
using ResolveRefVTable =
    OpaqueRefVTable*(PKG_SKINNER_SAFE_WAVE11_CDECL*)(TargetWord address);

// 0x0051ab50 is defective in this tranche, so the call 0x0051a9a0 makes to it
// at 0x0051aa95 is kept as an opaque port. That call is a plain call followed
// by the complete epilogue at 0x0051aa9a, 0x0051aa9c and 0x0051aa9d, so it is
// not a tail call, and its one stack argument is the low byte of the caller's
// stack word one widened to a word.
using CollectJob = void(PKG_SKINNER_SAFE_WAVE11_THISCALL*)(OpaqueSkinJob*,
                                                           TargetWord);

struct SkinnerSafeWave11Ports {
  CollectJob collect_job_0051ab50;
  GetPaintSystem get_paint_system_00401080;
  StartRender start_render_00528e90;
  SetColorWrite set_color_write_00529280;
  PaintRegion paint_region_005296b0;
  EndRender end_render_00529bf0;
  EmitVertex emit_005295b0;
  SetVertexLimit set_vertex_limit_00529520;
  FlushBatch flush_00529690;
  SwapPairs swap_00518b00;
  GetGraphicsProbe get_graphics_probe_0067dd00;
  GetRenderTargetManager get_render_target_manager_0067dd60;
  GetRenderObject get_render_object_0067de30;
  GetScale get_scale_006a2710;
  Classify classify_004bb860;
  GetFloat get_float_0040cf10;
  GetKey get_key_006a1250;
  GetRaster get_raster_00525aa0;
  Truncate truncate_004259e0;
  LazyReset lazy_reset_0041d870;
  ResolveRefVTable resolve_ref_vtable;
};

extern SkinnerSafeWave11Ports g_skinner_safe_wave11_ports;

extern OpaqueRefObject* g_skinner_safe_wave11_scale_source;

static_assert(sizeof(OpaqueVec2) == 8, "opaque vec2 size");
static_assert(sizeof(OpaqueVec3f) == 12, "opaque vec3f size");
static_assert(sizeof(OpaqueVec3w) == 12, "opaque vec3w size");
static_assert(sizeof(OpaqueVec4f) == 16, "opaque vec4f size");
static_assert(sizeof(OpaqueKeyBlock) == 12, "opaque key block size");
static_assert(sizeof(OpaqueTexturePainter) == 0x68, "texture painter size");
static_assert(offsetof(OpaqueTexturePainter, field_004) == 0x04,
              "texture painter material offset");
static_assert(offsetof(OpaqueTexturePainter, params_00c) == 0x0c,
              "texture painter first param offset");
static_assert(offsetof(OpaqueTexturePainter, params_01c) == 0x1c,
              "texture painter second param offset");
static_assert(offsetof(OpaqueTexturePainter, params_02c) == 0x2c,
              "texture painter third param offset");
static_assert(offsetof(OpaqueTexturePainter, rasters_03c) == 0x3c,
              "texture painter first raster offset");
static_assert(offsetof(OpaqueTexturePainter, rasters_040) == 0x40,
              "texture painter second raster offset");
static_assert(offsetof(OpaqueTexturePainter, count_044) == 0x44,
              "texture painter param count offset");
static_assert(offsetof(OpaqueTexturePainter, count_048) == 0x48,
              "texture painter raster count offset");
static_assert(offsetof(OpaqueTexturePainter, field_058) == 0x58,
              "texture painter width offset");
static_assert(offsetof(OpaqueTexturePainter, field_05c) == 0x5c,
              "texture painter height offset");
static_assert(offsetof(OpaqueTexturePainter, field_060) == 0x60,
              "texture painter raster offset");
static_assert(offsetof(OpaqueSkinPainter, textures_010) == 0x10,
              "skin painter first texture offset");
static_assert(offsetof(OpaqueSkinPainter, scale_02c) == 0x2c,
              "skin painter second scale offset");
static_assert(offsetof(OpaqueSkinPainter, scale_030) == 0x30,
              "skin painter scale offset");
static_assert(offsetof(OpaqueSkinPainter, field_03c) == 0x3c,
              "skin painter slot base offset");
static_assert(offsetof(OpaqueSkinPainter, field_040) == 0x40,
              "skin painter slot owner offset");
static_assert(offsetof(OpaqueSkinPainter, count_044) == 0x44,
              "skin painter slot count offset");
static_assert(offsetof(OpaqueSkinPainter, slots_090) == 0x90,
              "skin painter slot array offset");
static_assert(sizeof(OpaqueBatchSlot) == 0xe4, "batch slot size");
static_assert(offsetof(OpaqueBatchSlot, field_058) == 0x58,
              "batch slot first field offset");
static_assert(offsetof(OpaqueBatchSlot, field_064) == 0x64,
              "batch slot last field offset");
static_assert(sizeof(OpaqueBatch) == 0xec, "batch size");
static_assert(offsetof(OpaqueBatch, vertices_030) == 0x30,
              "batch vertex base offset");
static_assert(offsetof(OpaqueBatch, parts_begin_058) == 0x58,
              "batch parts begin offset");
static_assert(offsetof(OpaqueBatch, parts_end_05c) == 0x5c,
              "batch parts end offset");
static_assert(offsetof(OpaqueBatch, index_080) == 0x80,
              "batch index array offset");
static_assert(offsetof(OpaqueBatch, slots_begin_0e4) == 0xe4,
              "batch slot begin offset");
static_assert(sizeof(OpaqueMeshBlock) == 0xa0, "mesh block size");
static_assert(offsetof(OpaqueMeshBlock, rigblocks_098) == 0x98,
              "mesh block rigblock array offset");
static_assert(offsetof(OpaqueMeshBlock, rigblocks_09c) == 0x9c,
              "mesh block rigblock end offset");
static_assert(offsetof(OpaqueMesh, field_008) == 0x08,
              "mesh block pointer offset");
static_assert(offsetof(OpaqueMesh, ids_00c) == 0x0c, "mesh id array offset");
static_assert(offsetof(OpaqueMesh, slots_090) == 0x90,
              "mesh slot array offset");
static_assert(sizeof(OpaqueRigblock) == 0x8c, "rigblock stride");
static_assert(offsetof(OpaqueRigblock, flags_008) == 0x08,
              "rigblock flag offset");
static_assert(offsetof(OpaquePaintSystem, painter_00c) == 0x0c,
              "paint system painter offset");
static_assert(offsetof(OpaquePaintSystem, batch_010) == 0x10,
              "paint system batch offset");
static_assert(offsetof(OpaquePaintSystem, mesh_020) == 0x20,
              "paint system mesh offset");
static_assert(offsetof(OpaquePaintSystem, byte_07c) == 0x7c,
              "paint system flag 7c offset");
static_assert(offsetof(OpaquePaintSystem, byte_07e) == 0x7e,
              "paint system flag 7e offset");
static_assert(offsetof(OpaqueGraphicsProbeVTable, query_044) == 0x44,
              "graphics probe query slot offset");
static_assert(offsetof(OpaqueRenderTargetManagerVTable, create_01c) == 0x1c,
              "render target create slot offset");
static_assert(offsetof(OpaqueRenderTargetManagerVTable, create_020) == 0x20,
              "render target raw create slot offset");
static_assert(offsetof(OpaqueRenderTargetManagerVTable, can_create_024) == 0x24,
              "render target can-create slot offset");
static_assert(offsetof(OpaqueRenderTargetManagerVTable, prepare_034) == 0x34,
              "render target prepare slot offset");
static_assert(offsetof(OpaqueRefVTable, add_000) == 0x00,
              "ref add slot offset");
static_assert(offsetof(OpaqueRefVTable, release_004) == 0x04,
              "ref release slot offset");
static_assert(offsetof(OpaqueRefVTable, step_010) == 0x10,
              "ref step slot offset");
static_assert(offsetof(OpaqueRefObject, refcount_008) == 0x08,
              "ref object refcount offset");
static_assert(offsetof(OpaqueRefObject, flag_00c) == 0x0c,
              "ref object done flag offset");
static_assert(sizeof(OpaqueVector) == 12, "vector size");
static_assert(offsetof(OpaqueRenderObjectVTable, dispatch_02c) == 0x2c,
              "render object dispatch slot offset");
static_assert(offsetof(OpaqueSkinJobState, field_010) == 0x10,
              "job state first cursor offset");
static_assert(offsetof(OpaqueSkinJobState, field_014) == 0x14,
              "job state second cursor offset");
static_assert(offsetof(OpaqueSkinJobState, field_018) == 0x18,
              "job state third cursor offset");
static_assert(offsetof(OpaqueSkinJob, array_008) == 0x08,
              "skin job array base offset");
static_assert(offsetof(OpaqueSkinJob, array_00c) == 0x0c,
              "skin job array cursor offset");
static_assert(offsetof(OpaqueSkinJob, field_320) == 0x320,
              "skin job first argument offset");
static_assert(offsetof(OpaqueSkinJob, handle_330) == 0x330,
              "skin job handle offset");
static_assert(offsetof(OpaqueSkinJob, state_33c) == 0x33c,
              "skin job state offset");
static_assert(offsetof(OpaqueSkinJob, cursor_340) == 0x340,
              "skin job cursor offset");
static_assert(offsetof(OpaqueSkinJob, calls_344) == 0x344,
              "skin job call counter offset");
static_assert(offsetof(OpaqueSkinJob, flag_348) == 0x348,
              "skin job flag 348 offset");
static_assert(offsetof(OpaqueSkinJob, flag_34e) == 0x34e,
              "skin job flag 34e offset");
static_assert(sizeof(OpaqueSkinJob) == 0x350, "skin job size");

inline constexpr float kScaleUnit = 1.0F;
inline constexpr float kScaleZero = 0.0F;
inline constexpr float kScaleFallback = 5.0F;
inline constexpr float kScaleThird = 3.0F;
inline constexpr float kByteScale = 255.0F;

// 0x0041d870 always writes zero through the slot pointer it is handed, so the
// value 0x0051916a and 0x00519187 push for the two GetFloat receivers is zero.
inline constexpr TargetWord kLazySlotValue = 0u;

inline constexpr TargetWord kPassSlot = 2u;
inline constexpr TargetWord kPassNormal = 8u;
inline constexpr TargetWord kPassSmall = 2u;
inline constexpr TargetWord kEmitQuad = 6u;
inline constexpr TargetWord kRigStride = 0x8cu;
inline constexpr TargetSignedWord kRigPassLimit = 10;
inline constexpr TargetSignedWord kRigStatePass = 4;
inline constexpr TargetSignedWord kRigStateSkip = 1;
inline constexpr TargetWord kColourOpaque = 0xff000000u;
inline constexpr TargetWord kAcquireKey = 0x013f116cu;
inline constexpr TargetWord kAcquireSizeEmpty = 0x0cu;
inline constexpr TargetWord kAcquireSizeRaw = 0x10u;
inline constexpr TargetWord kAcquireSizeMid = 0x14u;
inline constexpr TargetWord kAcquireSizeJob = 0x18u;
inline constexpr TargetWord kAcquireSizeJobWide = 0x1cu;
inline constexpr TargetWord kAcquireSizeStage = 0x30u;
inline constexpr TargetWord kAcquireSizeWide = 0x48u;
inline constexpr TargetWord kCreateRawKey = 0xbd77bb98u;
inline constexpr TargetWord kCreateBlockTags = 6u;
inline constexpr TargetWord kClassifyKey = 0x438f6347u;
inline constexpr TargetWord kMaterialHit = 0xf01f7f52u;
inline constexpr TargetWord kMaterialMiss = 0xf1cf8a9du;
inline constexpr TargetWord kMaterialPassSetup = 0x00f8b396u;
inline constexpr TargetWord kMaterialPassLoop = 0xfa2f3df4u;
inline constexpr TargetWord kMaterialPassDead = 0xa0468560u;
inline constexpr TargetWord kMaterialTex0Full = 0x58653eacu;
inline constexpr TargetWord kMaterialTex2Uv = 0x9e74d163u;
inline constexpr TargetWord kMaterialRigBlock = 0xbc487ecbu;
inline constexpr TargetWord kMaterialBase = 0xd9ec39bcu;
inline constexpr TargetWord kMaterialOverlay = 0xa91b6551u;
inline constexpr TargetWord kMaterialRim = 0x03815422u;
inline constexpr TargetWord kMaterialScale = 0x968e3fffu;
inline constexpr TargetWord kKeySlotA = 0x02424655u;
inline constexpr TargetWord kKeySlotB = 0x02424657u;
inline constexpr TargetWord kKeySlotC = 0x02424656u;
inline constexpr TargetWord kKeyTuneA = 0x026cabbfu;
inline constexpr TargetWord kKeyTuneB = 0x026dc91eu;
inline constexpr TargetWord kKeyTone = 0x0d669e3c7u;
inline constexpr TargetWord kKeyScale = 0x1c76d9b5u;
inline constexpr TargetWord kKeyTuneQuery = 0x0c19db33u;
inline constexpr TargetWord kHandleTypeWide = 0x20u;
inline constexpr TargetWord kHandleTypeNarrow = 0x10u;
inline constexpr TargetWord kColourMask = 0x40200100u;
inline constexpr TargetWord kStateTerminal = 0xffffffffu;
inline constexpr TargetWord kStateCount = 14u;
inline constexpr TargetWord kJobAuxVTable = 0x013f1b3cu;
inline constexpr TargetWord kJobVTableA = 0x013f1b40u;
inline constexpr TargetWord kJobVTableB = 0x013f1b24u;
inline constexpr TargetWord kJobVTableC = 0x013f1b0cu;
inline constexpr TargetWord kJobVTableD = 0x013f1af4u;
inline constexpr TargetWord kJobVTableE = 0x013f1adcu;
inline constexpr TargetWord kJobVTableF = 0x013f1ac4u;
inline constexpr TargetWord kJobVTableWideC = 0x013f1b40u;
inline constexpr TargetSignedWord kJobField14Eight = 8;
inline constexpr TargetSignedWord kJobField18Zero = 0;

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_paint_slot_pass_005183c0(OpaqueSkinJobState* job);

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_tex0_full_region_00518bf0(OpaqueTexturePainter* job);

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_tex2_uv_region_00518cf0(OpaqueRefObject* job);

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_rig_block_draw_00518f10(OpaqueTexturePainter* job);

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_rig_index_pass_0051a350(OpaqueSkinJobState* job);

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL skin_job_setup_0051a9a0(
    OpaqueSkinJob* job, TargetWord arg_1, TargetByte arg_2, TargetByte arg_3,
    TargetWord arg_4, TargetWord arg_5, TargetWord arg_6, TargetWord arg_7,
    TargetByte arg_8, TargetByte arg_9, TargetByte arg_10);

// 0x00519640, 0x0051ab50 and 0x0051afd0 are excluded from this tranche for
// unresolved reconstruction defects, so their bodies and every port that only
// they called are not promoted: the element block resolve slots 0x1c and 0x28,
// the block descriptors 0x00446ff0 and 0x006bb640, the object factory
// 0x00f473a0, the vector copy 0x004098a0, the painter slot acquire 0x00552750,
// the vector collect, rewind and release trio 0x0051d1e0, 0x0051d140 and
// 0x00402420, the job build trio 0x00517310, 0x005173a0 and 0x0051c470, and the
// nine dword scale block that 0x00519656 copies from. The collector 0x0051ab50
// survives only as the opaque port above. The vtable images keep every observed
// slot so their layout assertions stay valid; the slots the promoted bodies do
// not use are simply never installed by the model test.
}  // namespace openspore::reconstruction::pkg_skinner_safe_wave11

#undef PKG_SKINNER_SAFE_WAVE11_CDECL
#undef PKG_SKINNER_SAFE_WAVE11_THISCALL
