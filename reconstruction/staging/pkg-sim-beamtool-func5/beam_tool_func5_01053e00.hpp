#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-sim-beamtool-func5 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SIM_BEAMTOOL_FUNC5_THISCALL __thiscall
#define PKG_SIM_BEAMTOOL_FUNC5_STDCALL __stdcall
#define PKG_SIM_BEAMTOOL_FUNC5_CDECL __cdecl
#define PKG_SIM_BEAMTOOL_FUNC5_NAKED __declspec(naked)
#else
#define PKG_SIM_BEAMTOOL_FUNC5_THISCALL __attribute__((thiscall))
#define PKG_SIM_BEAMTOOL_FUNC5_STDCALL __attribute__((stdcall))
#define PKG_SIM_BEAMTOOL_FUNC5_CDECL __attribute__((cdecl))
#define PKG_SIM_BEAMTOOL_FUNC5_NAKED __attribute__((naked))
#endif

namespace openspore::reconstruction::pkg_sim_beamtool_func5 {

using TargetWord = std::uint32_t;

inline constexpr TargetWord kTargetVa = 0x01053e00u;

inline constexpr TargetWord kReceiverPositionSourceOffset = 276u;
inline constexpr TargetWord kReceiverOwnedTargetOffset = 292u;
inline constexpr TargetWord kReceiverGateOffset = 372u;
inline constexpr TargetWord kReceiverExtent = 376u;

inline constexpr TargetWord kTargetEmitterOffset = 52u;
inline constexpr TargetWord kTargetAnchorOffset = 308u;
inline constexpr TargetWord kTargetAnchorPositionOffset = 316u;
inline constexpr TargetWord kTargetExtent = 328u;

inline constexpr TargetWord kSlotRelease = 4u;
inline constexpr TargetWord kSlotCompletionQuery = 44u;
inline constexpr TargetWord kSlotPositionPointer = 44u;
inline constexpr TargetWord kSlotPositionOut = 48u;
inline constexpr TargetWord kSlotProviderResolver = 280u;
inline constexpr TargetWord kSlotLookupByTable = 184u;
inline constexpr TargetWord kSlotSetPosition = 56u;

inline constexpr TargetWord kEntryStackCleanupBytes = 8u;

struct alignas(4) OpaqueVec3 {
  float x;
  float y;
  float z;
};

struct OpaquePositionSource;
struct OpaqueFoundPosition;
struct OpaqueAnchorProvider;
struct OpaqueBeamTarget;
struct OpaqueBeamEmitter;
struct OpaqueAnchor;

using PositionPointerFn = const OpaqueVec3*(
    PKG_SIM_BEAMTOOL_FUNC5_THISCALL*)(const OpaquePositionSource*);
using PositionOutFn = const OpaqueVec3*(
    PKG_SIM_BEAMTOOL_FUNC5_THISCALL*)(OpaquePositionSource*, OpaqueVec3*);
using LookupByTableFn = OpaqueFoundPosition*(
    PKG_SIM_BEAMTOOL_FUNC5_THISCALL*)(OpaquePositionSource*,
                                      const std::uint32_t*);

struct OpaquePositionSourceVTable {
  void* slots_00[11];
  PositionPointerFn position_pointer_2c;
  PositionOutFn position_out_30;
  void* slots_34[33];
  LookupByTableFn lookup_by_table_b8;
};

using ReleaseFn = void(PKG_SIM_BEAMTOOL_FUNC5_THISCALL*)(OpaqueBeamTarget*);
using CompletionQueryFn =
    bool(PKG_SIM_BEAMTOOL_FUNC5_THISCALL*)(const OpaqueBeamTarget*);

struct OpaqueBeamTargetVTable {
  void* slots_00[1];
  ReleaseFn release_04;
  void* slots_08[9];
  CompletionQueryFn completion_query_2c;
};

using SetPositionFn = void(PKG_SIM_BEAMTOOL_FUNC5_THISCALL*)(OpaqueBeamEmitter*,
                                                             const OpaqueVec3*);

struct OpaqueBeamEmitterVTable {
  void* slots_00[14];
  SetPositionFn set_position_38;
};

using FoundPositionOutFn = const OpaqueVec3*(
    PKG_SIM_BEAMTOOL_FUNC5_THISCALL*)(OpaqueFoundPosition*, OpaqueVec3*);

struct OpaqueFoundPositionVTable {
  void* slots_00[12];
  FoundPositionOutFn position_out_30;
};

using AnchorProviderFn =
    OpaqueAnchorProvider*(PKG_SIM_BEAMTOOL_FUNC5_THISCALL*)(OpaqueAnchor*);

struct OpaqueAnchorVTable {
  void* slots_00[70];
  AnchorProviderFn provider_118;
};

using ProviderPositionFn =
    const OpaqueVec3*(PKG_SIM_BEAMTOOL_FUNC5_THISCALL*)(OpaqueAnchorProvider*);

struct OpaqueAnchorProviderVTable {
  void* slots_00[11];
  ProviderPositionFn position_2c;
};

struct alignas(4) OpaquePositionSource {
  const OpaquePositionSourceVTable* vtable_00;
};

struct alignas(4) OpaqueFoundPosition {
  const OpaqueFoundPositionVTable* vtable_00;
};

struct alignas(4) OpaqueAnchorProvider {
  const OpaqueAnchorProviderVTable* vtable_00;
};

struct alignas(4) OpaqueBeamEmitter {
  const OpaqueBeamEmitterVTable* vtable_00;
};

struct alignas(4) OpaqueAnchor {
  const OpaqueAnchorVTable* vtable_00;
};

struct alignas(4) OpaqueBeamTarget {
  const OpaqueBeamTargetVTable* vtable_00;
  std::uint8_t opaque_004[kTargetEmitterOffset - 4u];
  OpaqueBeamEmitter* emitter_34;
  std::uint8_t opaque_038[kTargetAnchorOffset - kTargetEmitterOffset - 4u];
  OpaqueAnchor* anchor_134;
  std::uint8_t
      opaque_138[kTargetAnchorPositionOffset - kTargetAnchorOffset - 4u];
  OpaqueVec3 anchor_position_13c;
};

struct alignas(4) OpaqueBeamToolState {
  std::uint8_t opaque_000[kReceiverPositionSourceOffset];
  OpaquePositionSource* position_source_114;
  std::uint8_t opaque_118[kReceiverOwnedTargetOffset -
                          kReceiverPositionSourceOffset - 4u];
  OpaqueBeamTarget* owned_beam_target_124;
  std::uint8_t
      opaque_128[kReceiverGateOffset - kReceiverOwnedTargetOffset - 4u];
  TargetWord gate_174;
};

extern const std::uint32_t kPositionServiceTable_013f94d4[8];

extern "C" void PKG_SIM_BEAMTOOL_FUNC5_THISCALL anchor_position_commit_00cb5930(
    OpaqueBeamTarget* target, const OpaqueBeamToolState* fallback);

extern "C" bool PKG_SIM_BEAMTOOL_FUNC5_CDECL
func_01053e00(OpaqueBeamToolState* tool_state, void* update_context);

bool beam_tool_func5_01053e00_model(OpaqueBeamToolState* tool_state,
                                    void* update_context);

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(OpaqueVec3) == 12, "vector extent");
static_assert(offsetof(OpaquePositionSourceVTable, position_pointer_2c) ==
                  kSlotPositionPointer,
              "position source slot 2c offset");
static_assert(offsetof(OpaquePositionSourceVTable, position_out_30) ==
                  kSlotPositionOut,
              "position source slot 30 offset");
static_assert(offsetof(OpaquePositionSourceVTable, lookup_by_table_b8) ==
                  kSlotLookupByTable,
              "position source slot b8 offset");
static_assert(offsetof(OpaqueBeamTargetVTable, release_04) == kSlotRelease,
              "beam target release slot offset");
static_assert(offsetof(OpaqueBeamTargetVTable, completion_query_2c) ==
                  kSlotCompletionQuery,
              "beam target completion query slot offset");
static_assert(offsetof(OpaqueBeamEmitterVTable, set_position_38) ==
                  kSlotSetPosition,
              "beam emitter set position slot offset");
static_assert(offsetof(OpaqueFoundPositionVTable, position_out_30) ==
                  kSlotPositionOut,
              "found position slot 30 offset");
static_assert(offsetof(OpaqueAnchorVTable, provider_118) ==
                  kSlotProviderResolver,
              "anchor provider resolver slot offset");
static_assert(offsetof(OpaqueAnchorProviderVTable, position_2c) ==
                  kSlotPositionPointer,
              "anchor provider position slot offset");
static_assert(offsetof(OpaqueBeamTarget, emitter_34) == kTargetEmitterOffset,
              "owned target emitter pointer offset");
static_assert(offsetof(OpaqueBeamTarget, anchor_134) == kTargetAnchorOffset,
              "owned target anchor pointer offset");
static_assert(offsetof(OpaqueBeamTarget, anchor_position_13c) ==
                  kTargetAnchorPositionOffset,
              "owned target anchor position offset");
static_assert(sizeof(OpaqueBeamTarget) == kTargetExtent, "owned target extent");
static_assert(offsetof(OpaqueBeamToolState, position_source_114) ==
                  kReceiverPositionSourceOffset,
              "receiver position source offset");
static_assert(offsetof(OpaqueBeamToolState, owned_beam_target_124) ==
                  kReceiverOwnedTargetOffset,
              "receiver owned target offset");
static_assert(offsetof(OpaqueBeamToolState, gate_174) == kReceiverGateOffset,
              "receiver gate word offset");
static_assert(sizeof(OpaqueBeamToolState) == kReceiverExtent,
              "receiver extent");

}

#undef PKG_SIM_BEAMTOOL_FUNC5_THISCALL
#undef PKG_SIM_BEAMTOOL_FUNC5_STDCALL
#undef PKG_SIM_BEAMTOOL_FUNC5_CDECL
#undef PKG_SIM_BEAMTOOL_FUNC5_NAKED
