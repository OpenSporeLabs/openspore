#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg11-h5-update-gate-0105a050 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG11H5_THISCALL __thiscall
#define PKG11H5_CDECL __cdecl
#else
#define PKG11H5_THISCALL __attribute__((thiscall))
#define PKG11H5_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg11_h5_update_gate_0105a050 {

using TargetWord = std::uint32_t;

inline constexpr TargetWord kTargetVa = 0x0105a050u;
inline constexpr TargetWord kOwnedSubjectOffset = 0x124u;
inline constexpr TargetWord kSubjectFlagFrontOffset = 0x16cu;
inline constexpr TargetWord kSubjectFlagBackOffset = 0x16du;
inline constexpr TargetWord kToolGateWordOffset = 0x174u;
inline constexpr TargetWord kToolActiveTimeOffset = 0x1acu;
inline constexpr TargetWord kSubjectStateWordOffset = 0x1e0u;
inline constexpr TargetWord kFrameBytes = 0x18u;
inline constexpr TargetWord kStackCleanupBytes = 0x10u;
inline constexpr TargetWord kForwardedImmediate = 0u;
inline constexpr std::size_t kFloat3Bytes = 12u;

struct alignas(4) OpaqueToolSubject {
  std::uint8_t opaque_000[0x16c];
  std::uint8_t flag_16c;
  std::uint8_t flag_16d;
  std::uint8_t opaque_16e[0x72];
  TargetWord state_word_1e0;
};

struct alignas(4) OpaqueToolState {
  std::uint8_t opaque_000[0x124];
  OpaqueToolSubject* owned_subject_124;
  std::uint8_t opaque_128[0x4c];
  TargetWord gate_word_174;
  std::uint8_t opaque_178[0x34];
  float active_time_1ac;
};

struct Float3 {
  float x;
  float y;
  float z;
};

struct TrailEnds {
  Float3 first;
  Float3 last;
};

struct OpaqueAxisSnapRoot;

using ModeUpdate010593e0 = bool(PKG11H5_CDECL*)(OpaqueToolState*, TargetWord,
                                                 TargetWord, TargetWord);
using ActiveTime0104bdb0 = float(PKG11H5_THISCALL*)(OpaqueToolState*);
using SubjectLive00cb5ba0 = bool(PKG11H5_THISCALL*)(OpaqueToolSubject*);
using ToolGate0104cd40 = bool(PKG11H5_THISCALL*)(OpaqueToolState*);
using SubjectTrailEnds00cb8ba0 =
    void(PKG11H5_THISCALL*)(OpaqueToolSubject*, Float3*, Float3*);
using RootAccessor00b3d430 = OpaqueAxisSnapRoot*(PKG11H5_CDECL*)();
using AxisSnap00bbec40 =
    void(PKG11H5_THISCALL*)(OpaqueAxisSnapRoot*, Float3*, float);

struct NativePorts {
  ModeUpdate010593e0 mode_update_010593e0 = nullptr;
  ActiveTime0104bdb0 active_time_0104bdb0 = nullptr;
  SubjectLive00cb5ba0 subject_live_00cb5ba0 = nullptr;
  ToolGate0104cd40 tool_gate_0104cd40 = nullptr;
  SubjectTrailEnds00cb8ba0 subject_trail_ends_00cb8ba0 = nullptr;
  RootAccessor00b3d430 root_accessor_00b3d430 = nullptr;
  AxisSnap00bbec40 axis_snap_00bbec40 = nullptr;
};

extern "C" bool PKG11H5_THISCALL func_0105a050(OpaqueToolState* tool_state,
                                               TargetWord mode_word,
                                               TargetWord selector,
                                               TargetWord unused_slot);

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(bool) == 1, "the machine return is written through AL");
static_assert(sizeof(Float3) == kFloat3Bytes, "trail point extent");
static_assert(offsetof(OpaqueToolSubject, flag_16c) ==
                  kSubjectFlagFrontOffset,
              "subject front flag offset");
static_assert(offsetof(OpaqueToolSubject, flag_16d) ==
                  kSubjectFlagBackOffset,
              "subject back flag offset");
static_assert(offsetof(OpaqueToolSubject, state_word_1e0) ==
                  kSubjectStateWordOffset,
              "subject state word offset");
static_assert(sizeof(OpaqueToolSubject) == 0x1e4, "subject extent");
static_assert(offsetof(OpaqueToolState, owned_subject_124) ==
                  kOwnedSubjectOffset,
              "owned subject pointer offset");
static_assert(offsetof(OpaqueToolState, gate_word_174) == kToolGateWordOffset,
              "tool gate word offset");
static_assert(offsetof(OpaqueToolState, active_time_1ac) ==
                  kToolActiveTimeOffset,
              "tool active time offset");
static_assert(sizeof(OpaqueToolState) == 0x1b0, "tool state extent");
static_assert(sizeof(ModeUpdate010593e0) == 4, "mode update port width");
static_assert(sizeof(SubjectTrailEnds00cb8ba0) == 4, "trail port width");
static_assert(std::is_same_v<decltype(&func_0105a050),
                             bool(PKG11H5_THISCALL*)(OpaqueToolState*,
                                                      TargetWord, TargetWord,
                                                      TargetWord)>,
              "entry ABI: hidden ECX receiver and four callee-popped slots");

extern NativePorts g_tool_update_gate_0105a050_ports;

bool tool_update_gate_0105a050_model(OpaqueToolState* tool_state,
                                     TargetWord mode_word, TargetWord selector,
                                     TargetWord unused_slot);

}

#undef PKG11H5_THISCALL
#undef PKG11H5_CDECL
