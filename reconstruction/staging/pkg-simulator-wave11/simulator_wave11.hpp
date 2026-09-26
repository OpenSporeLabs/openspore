#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG simulator wave11 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SIMULATOR_WAVE11_CDECL __cdecl
#define PKG_SIMULATOR_WAVE11_THISCALL __thiscall
#define PKG_SIMULATOR_WAVE11_FASTCALL __fastcall
#else
#define PKG_SIMULATOR_WAVE11_CDECL __attribute__((cdecl))
#define PKG_SIMULATOR_WAVE11_THISCALL __attribute__((thiscall))
#define PKG_SIMULATOR_WAVE11_FASTCALL __attribute__((fastcall))
#endif

namespace openspore::reconstruction::pkg_simulator_wave11 {

using TargetWord = std::uint32_t;
using TargetHalf = std::uint16_t;
using TargetByte = std::uint8_t;
using TargetFloat = float;

struct OpaqueVtable00628 {
  TargetWord opaque_00;
  TargetWord slot_04;
  TargetWord slot_08;
  TargetWord slot_0c;
  std::array<TargetWord, 4> opaque_10_1f;
  TargetWord slot_20;
  TargetWord slot_24;
  TargetWord slot_28;
  TargetWord slot_2c;
  std::array<TargetWord, 6> opaque_30_47;
  TargetWord slot_48;
  TargetWord slot_4c;
  std::array<TargetWord, 3> opaque_50_5b;
  TargetWord slot_5c;
  std::array<TargetWord, 9> opaque_60_83;
  TargetWord slot_84;
  std::array<TargetWord, 1> opaque_88_8b;
};

struct OpaqueObject00628 {
  OpaqueVtable00628 *vtable;
};

struct OpaqueFlag00628 {
  TargetWord opaque_00;
  TargetWord field_04;
};

struct OpaqueOwner00628 {
  std::array<TargetByte, 0xac> opaque_00_ab;
  OpaqueFlag00628 *field_ac;
  std::array<TargetByte, 0x2b4> opaque_b0_363;
  TargetWord field_364;
};

struct OpaqueQueue00628 {
  std::array<TargetByte, 0x40> opaque_00_3f;
};

struct OpaqueBlend00628 {
  OpaqueVtable00628 *vtable;
};

struct OpaqueEditor00628 {
  OpaqueVtable00628 *vtable;
  std::array<TargetByte, 0x08> opaque_04_0b;
  OpaqueObject00628 *field_0c;
  std::array<TargetByte, 0x64> opaque_10_73;
  OpaqueObject00628 *field_74;
  OpaqueObject00628 *field_78;
  std::array<TargetByte, 0x18> opaque_7c_93;
  OpaqueObject00628 *field_94;
  std::array<TargetByte, 0x30> opaque_98_c7;
  OpaqueObject00628 *field_c8;
  OpaqueObject00628 *field_cc;
  OpaqueObject00628 *field_d0;
  OpaqueObject00628 *field_d4;
  std::array<TargetByte, 0x34b0> opaque_d8_3587;
  OpaqueBlend00628 field_3588;
  std::array<TargetByte, 0x88> opaque_358c_3613;
  OpaqueOwner00628 *field_3614;
  OpaqueQueue00628 field_3618;
  std::array<TargetByte, 0x7c> opaque_3658_36d3;
  TargetWord state_36d4;
};

using Slot000400628 =
    void(PKG_SIMULATOR_WAVE11_THISCALL *)(OpaqueObject00628 *);
using Slot000800628n0 =
    void(PKG_SIMULATOR_WAVE11_THISCALL *)(OpaqueObject00628 *);
using Slot000800628 = TargetByte(PKG_SIMULATOR_WAVE11_THISCALL *)(
    OpaqueObject00628 *, TargetWord, TargetWord, TargetWord);
using Slot000c00628 = TargetFloat(PKG_SIMULATOR_WAVE11_THISCALL *)(
    OpaqueBlend00628 *, TargetWord, TargetWord, TargetWord, TargetWord,
    TargetWord);
using Slot002000628 =
    TargetWord(PKG_SIMULATOR_WAVE11_THISCALL *)(OpaqueObject00628 *);
using Slot002400628 = TargetByte(PKG_SIMULATOR_WAVE11_THISCALL *)(
    OpaqueObject00628 *, TargetWord, TargetWord);
using Slot002400628n1 = TargetByte(PKG_SIMULATOR_WAVE11_THISCALL *)(
    OpaqueObject00628 *, TargetWord);
using Slot002800628 =
    TargetWord(PKG_SIMULATOR_WAVE11_THISCALL *)(OpaqueObject00628 *);
using Slot002c00628 = TargetByte(PKG_SIMULATOR_WAVE11_THISCALL *)(
    OpaqueObject00628 *, TargetWord);
using Slot004800628 = OpaqueObject00628 *(
    PKG_SIMULATOR_WAVE11_THISCALL *)(OpaqueObject00628 *, TargetWord);
using Slot004c00628 = void(PKG_SIMULATOR_WAVE11_THISCALL *)(
    OpaqueObject00628 *, TargetWord, OpaqueObject00628 *);
using Slot005c00628 =
    OpaqueObject00628 *(PKG_SIMULATOR_WAVE11_THISCALL *)(OpaqueObject00628 *);
using Slot008400628 =
    void(PKG_SIMULATOR_WAVE11_THISCALL *)(OpaqueObject00628 *);

struct SimulatorRuntime00628 {
  OpaqueObject00628 *(PKG_SIMULATOR_WAVE11_CDECL *provider_0067ddd0)();
  OpaqueObject00628 *(PKG_SIMULATOR_WAVE11_CDECL *view_manager_0067caa0)();
  TargetWord(PKG_SIMULATOR_WAVE11_CDECL *asset_view_00401030)();
  OpaqueObject00628 *(PKG_SIMULATOR_WAVE11_CDECL *debug_service_00a206f0)();
  void(PKG_SIMULATOR_WAVE11_CDECL *emit_debug_00435ed0)(TargetWord, TargetWord);
  OpaqueObject00628 *(PKG_SIMULATOR_WAVE11_THISCALL *resolve_00634e40)(
      OpaqueObject00628 *, TargetWord);
  TargetWord(PKG_SIMULATOR_WAVE11_THISCALL *random_00a68fb0)(TargetWord *,
                                                             TargetWord);
  TargetByte(PKG_SIMULATOR_WAVE11_THISCALL *submit_0062f7f0)(OpaqueQueue00628 *,
                                                             TargetWord);
  TargetByte(PKG_SIMULATOR_WAVE11_THISCALL *probe_0062f6c0)(OpaqueQueue00628 *);
  TargetByte(PKG_SIMULATOR_WAVE11_THISCALL *release_0062c340)(
      OpaqueEditor00628 *);
  void(PKG_SIMULATOR_WAVE11_THISCALL *apply_00628ca0)(OpaqueEditor00628 *,
                                                      TargetByte);
  void(PKG_SIMULATOR_WAVE11_THISCALL *post_event_00574110)(
      OpaqueOwner00628 *, TargetWord, TargetWord, TargetFloat, TargetFloat);
  void(PKG_SIMULATOR_WAVE11_THISCALL *select_005dbbb0)(OpaqueOwner00628 *,
                                                       TargetWord);
  OpaqueObject00628 *global_015f7cf4;
  TargetWord random_state_01601760;
};

SimulatorRuntime00628 &simulator_runtime_00628();

extern "C" void PKG_SIMULATOR_WAVE11_CDECL
dispatch_key_00628450(OpaqueObject00628 *subject, TargetWord key,
                      TargetWord reserved, TargetWord context);

extern "C" TargetWord PKG_SIMULATOR_WAVE11_THISCALL
cycle_key_006286a0(OpaqueEditor00628 *subject);

extern "C" TargetByte PKG_SIMULATOR_WAVE11_THISCALL forward_key_00628af0(
    OpaqueEditor00628 *subject, TargetWord key, TargetWord extra);

extern "C" TargetByte PKG_SIMULATOR_WAVE11_THISCALL
route_key_00628d50(OpaqueEditor00628 *subject, TargetWord key);

extern "C" void PKG_SIMULATOR_WAVE11_THISCALL
release_child_0062c910(OpaqueEditor00628 *subject);

static_assert(sizeof(void *) == 4,
              "pkg-simulator-wave11 needs 32-bit pointers");
static_assert(sizeof(TargetFloat) == 4,
              "pkg-simulator-wave11 needs 32-bit floats");
static_assert(offsetof(OpaqueVtable00628, slot_04) == 0x04,
              "vtable slot 0x04 offset");
static_assert(offsetof(OpaqueVtable00628, slot_08) == 0x08,
              "vtable slot 0x08 offset");
static_assert(offsetof(OpaqueVtable00628, slot_0c) == 0x0c,
              "vtable slot 0x0c offset");
static_assert(offsetof(OpaqueVtable00628, slot_20) == 0x20,
              "vtable slot 0x20 offset");
static_assert(offsetof(OpaqueVtable00628, slot_24) == 0x24,
              "vtable slot 0x24 offset");
static_assert(offsetof(OpaqueVtable00628, slot_28) == 0x28,
              "vtable slot 0x28 offset");
static_assert(offsetof(OpaqueVtable00628, slot_2c) == 0x2c,
              "vtable slot 0x2c offset");
static_assert(offsetof(OpaqueVtable00628, slot_48) == 0x48,
              "vtable slot 0x48 offset");
static_assert(offsetof(OpaqueVtable00628, slot_4c) == 0x4c,
              "vtable slot 0x4c offset");
static_assert(offsetof(OpaqueVtable00628, slot_5c) == 0x5c,
              "vtable slot 0x5c offset");
static_assert(offsetof(OpaqueVtable00628, slot_84) == 0x84,
              "vtable slot 0x84 offset");
static_assert(sizeof(OpaqueVtable00628) == 0x8c, "opaque vtable size");
static_assert(sizeof(OpaqueObject00628) == 0x04, "opaque object size");
static_assert(offsetof(OpaqueFlag00628, field_04) == 0x04,
              "opaque flag field offset");
static_assert(offsetof(OpaqueOwner00628, field_ac) == 0xac,
              "opaque owner flag pointer offset");
static_assert(offsetof(OpaqueOwner00628, field_364) == 0x364,
              "opaque owner handle offset");
static_assert(offsetof(OpaqueEditor00628, field_0c) == 0x0c,
              "editor field_0c offset");
static_assert(offsetof(OpaqueEditor00628, field_94) == 0x94,
              "editor field_94 offset");
static_assert(offsetof(OpaqueEditor00628, field_c8) == 0xc8,
              "editor field_c8 offset");
static_assert(offsetof(OpaqueEditor00628, field_cc) == 0xcc,
              "editor field_cc offset");
static_assert(offsetof(OpaqueEditor00628, field_d0) == 0xd0,
              "editor field_d0 offset");
static_assert(offsetof(OpaqueEditor00628, field_d4) == 0xd4,
              "editor field_d4 offset");
static_assert(offsetof(OpaqueEditor00628, field_3588) == 0x3588,
              "editor field_3588 offset");
static_assert(offsetof(OpaqueEditor00628, field_3614) == 0x3614,
              "editor field_3614 offset");
static_assert(offsetof(OpaqueEditor00628, field_3618) == 0x3618,
              "editor field_3618 offset");
static_assert(offsetof(OpaqueEditor00628, state_36d4) == 0x36d4,
              "editor state_36d4 offset");
static_assert(sizeof(OpaqueEditor00628) == 0x36d8, "opaque editor size");

}  // namespace openspore::reconstruction::pkg_simulator_wave11
