#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "camera services wave6 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_CAM_CDECL __cdecl
#define PKG_CAM_THISCALL __thiscall
#else
#define PKG_CAM_CDECL __attribute__((cdecl))
#define PKG_CAM_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_app_services_wave6 {

using OpaqueWord = std::uint32_t;
using OpaqueWide = std::uint16_t;

struct OpaqueCamera {
  std::uint32_t opaque[4]{};
};

struct OpaqueCameraManagerVTable {
  void* slots_00[21]{};
  bool(PKG_CAM_THISCALL* set_active_by_id_54)(void*, OpaqueWord) = nullptr;
};

struct OpaqueMessageNode {
  OpaqueWord key = 0;
  OpaqueWord value = 0;
  OpaqueMessageNode* next = nullptr;
};

struct OpaqueMessageRegistry {
  OpaqueWord opaque_000 = 0;
  OpaqueMessageNode** buckets_004 = nullptr;
  OpaqueWord bucket_count_008 = 0;
  OpaqueWord opaque_00c[5]{};
};

struct OpaqueMessageRecord {
  OpaqueWord key = 0;
  OpaqueWord value = 0;
};

struct OpaqueCameraManager {
  OpaqueCameraManagerVTable* vtable_000 = nullptr;
  OpaqueWord opaque_004[23]{};
  OpaqueMessageRegistry messages_060{};
  OpaqueCamera** cameras_080 = nullptr;
  OpaqueCamera** camera_end_084 = nullptr;
  OpaqueCamera** camera_capacity_088 = nullptr;
  OpaqueWord opaque_08c[2]{};
  OpaqueWide** names_094 = nullptr;
  OpaqueWide** name_end_098 = nullptr;
  OpaqueWide** name_capacity_09c = nullptr;
  OpaqueWord opaque_0a0[2]{};
  int active_index_0a8 = 0;
  OpaqueWord opaque_0ac = 0;
};

static_assert(offsetof(OpaqueCameraManagerVTable, set_active_by_id_54) == 0x54,
              "camera manager active-by-id slot");
static_assert(offsetof(OpaqueCameraManager, messages_060) == 0x60,
              "camera message registry offset");
static_assert(offsetof(OpaqueCameraManager, cameras_080) == 0x80,
              "camera array offset");
static_assert(offsetof(OpaqueCameraManager, active_index_0a8) == 0xa8,
              "active camera index offset");

extern "C" OpaqueCamera* PKG_CAM_THISCALL service_007c61a0(
    OpaqueCameraManager* manager);

extern "C" bool PKG_CAM_THISCALL service_007c66b0(
    OpaqueCameraManager* manager, OpaqueMessageRecord* message);

struct OpaqueCommandEntry {
  void* first = nullptr;
  void* second = nullptr;
  OpaqueWord opaque_008 = 0;
  OpaqueWord opaque_00c = 0;
};

struct OpaqueCommandCameraVTable {
  void* slots_00[19]{};
  void*(PKG_CAM_THISCALL* get_property_list_4c)(void*) = nullptr;
};

struct OpaqueCommandCamera {
  OpaqueCommandCameraVTable* vtable = nullptr;
  std::uint32_t opaque[4]{};
};

struct OpaquePropertyListVTable {
  void* slots_00[7]{};
  bool(PKG_CAM_THISCALL* has_1c)(void*, OpaqueWord) = nullptr;
  void*(PKG_CAM_THISCALL* get_28)(void*, OpaqueWord) = nullptr;
};

struct OpaquePropertyList {
  OpaquePropertyListVTable* vtable = nullptr;
  std::uint32_t opaque[4]{};
};

struct OpaquePropertyValue {
  void* payload = nullptr;
  std::uint8_t opaque_004[12]{};
  std::uint8_t flags_010 = 0;
  std::uint8_t opaque_011 = 0;
  std::uint16_t type_012 = 0;
  std::uint8_t opaque_014[2]{};
};

struct OpaqueCommandCollectionVTable {
  void* slots_00[13]{};
  void(PKG_CAM_THISCALL* activate_34)(void*, OpaqueWord) = nullptr;
  void* slots_38[4]{};
  int(PKG_CAM_THISCALL* count_48)(void*) = nullptr;
  OpaqueCommandCamera*(PKG_CAM_THISCALL* camera_at_4c)(void*, int) = nullptr;
  OpaqueWord(PKG_CAM_THISCALL* describe_50)(void*, int, OpaqueWord,
                                            OpaqueWord) = nullptr;
  void(PKG_CAM_THISCALL* set_active_54)(void*, int) = nullptr;
  int(PKG_CAM_THISCALL* active_58)(void*) = nullptr;
};

struct OpaqueCommandCollection {
  OpaqueCommandCollectionVTable* vtable = nullptr;
  std::uint8_t opaque_004[0x90]{};
  OpaqueCommandEntry* entries_094 = nullptr;
  OpaqueCommandEntry* entries_098 = nullptr;
};

struct OpaqueRect {
  float values[4]{};
};

struct OpaqueViewer {
  std::uint32_t opaque[4]{};
};

struct OpaqueRenderer;

struct OpaqueRendererLayer {
  using OneArgument = OpaqueViewer*(PKG_CAM_THISCALL*)(OpaqueRenderer*,
                                                       const void*);
  using TwoArguments = OpaqueViewer*(PKG_CAM_THISCALL*)(OpaqueRenderer*,
                                                        OpaqueViewer*,
                                                        OpaqueWord);
  union {
    OneArgument one = nullptr;
    TwoArguments two;
  };
};

struct OpaqueRendererVTable {
  OpaqueRendererLayer layer_00{};
};

struct OpaqueRenderer {
  OpaqueRendererVTable* vtable = nullptr;
  std::uint32_t opaque[4]{};
};

struct OpaqueCommandSecondaryVTable {
  void* slots_00[13]{};
  void* slot_34 = nullptr;
  void* slots_38[25]{};
  OpaqueViewer*(PKG_CAM_THISCALL* resolve_render_type_9c)(void*,
                                                          OpaqueWord) = nullptr;
  OpaqueWord(PKG_CAM_THISCALL* resolve_digit_a0)(void*, const char*) = nullptr;
  void* slots_a4[4]{};
  const OpaqueRect*(PKG_CAM_THISCALL* resolve_target_b4)(void*, OpaqueRect*,
                                                          OpaqueWord) = nullptr;
};

struct OpaqueCommandSecondary {
  OpaqueCommandSecondaryVTable* vtable = nullptr;
  std::uint32_t opaque[4]{};
};

struct OpaqueCameraCommandOwner {
  void* vtable_000 = nullptr;
  OpaqueCommandSecondary* secondary_004 = nullptr;
  OpaqueCommandCollection* collection_010 = nullptr;
};

static_assert(offsetof(OpaqueCommandCollectionVTable, count_48) == 0x48,
              "command collection count slot");
static_assert(offsetof(OpaqueCommandCollectionVTable, set_active_54) == 0x54,
              "command collection set-active slot");
static_assert(offsetof(OpaqueCommandCollection, entries_094) == 0x94,
              "command collection entries offset");
static_assert(offsetof(OpaqueCommandSecondaryVTable, resolve_render_type_9c) ==
                  0x9c,
              "render-type resolver slot");
static_assert(offsetof(OpaqueCommandSecondaryVTable, resolve_target_b4) == 0xb4,
              "target resolver slot");

struct OpaqueWideRange {
  OpaqueWide* begin = nullptr;
  OpaqueWide* end = nullptr;
};

struct CameraCommandPorts {
  using ParseMode = int(PKG_CAM_CDECL*)(OpaqueWord);
  using LogCurrent = bool(PKG_CAM_CDECL*)(OpaqueCommandSecondary*, void*);
  using ParseDefault = const char**(PKG_CAM_CDECL*)(OpaqueWord, OpaqueWord*,
                                                    OpaqueWord);
  using LookupSwitch = const char**(PKG_CAM_THISCALL*)(OpaqueWord, OpaqueWord);
  using IsDigit = int(PKG_CAM_CDECL*)(unsigned char);
  using Widen = void(PKG_CAM_CDECL*)(const char*, int, OpaqueWideRange*);
  using WideCompare = int(PKG_CAM_CDECL*)(const OpaqueWide*, const OpaqueWide*);
  using FreeValue = bool(PKG_CAM_CDECL*)(void*);
  using ListEnabled = bool(PKG_CAM_THISCALL*)(OpaqueWord);
  using LogList = void(PKG_CAM_CDECL*)(OpaqueCommandSecondary*, int, OpaqueWord,
                                       OpaqueWord, OpaqueWord);
  using LookupTarget = const char**(PKG_CAM_THISCALL*)(OpaqueWord);
  using LookupRenderType = const char**(PKG_CAM_THISCALL*)(OpaqueWord);
  using RendererGet = OpaqueRenderer*(PKG_CAM_CDECL*)();
  using ViewerUpdate = void(PKG_CAM_CDECL*)(OpaqueWord);
  using DefaultCategory = const OpaqueWide*(PKG_CAM_CDECL*)();
  using ActiveCategory = const OpaqueWide*(PKG_CAM_CDECL*)();
  using InactiveCategory = const OpaqueWide*(PKG_CAM_CDECL*)();
  using EndUpdate = bool(PKG_CAM_THISCALL*)(OpaqueViewer*);

  ParseMode parse_mode_00837f30 = nullptr;
  LogCurrent log_current_00841000 = nullptr;
  ParseDefault parse_default_00838020 = nullptr;
  LookupSwitch lookup_switch_00838330 = nullptr;
  IsDigit is_digit = nullptr;
  Widen widen_0093c5a0 = nullptr;
  WideCompare wide_compare = nullptr;
  FreeValue free_00f47380 = nullptr;
  ListEnabled list_enabled_008380b0 = nullptr;
  LogList log_list_00841000 = nullptr;
  LookupTarget lookup_target_00838330 = nullptr;
  LookupRenderType lookup_render_type_00838330 = nullptr;
  RendererGet renderer_get_0067dd10 = nullptr;
  ViewerUpdate viewer_update_007c3c20 = nullptr;
  DefaultCategory default_category_007c65a0 = nullptr;
  ActiveCategory active_category_013ec468 = nullptr;
  InactiveCategory inactive_category_013ed024 = nullptr;
  EndUpdate end_update_007c3ce0 = nullptr;
};

extern CameraCommandPorts* g_camera_command_ports;

struct OpaqueCameraCommandError {};

extern "C" bool PKG_CAM_THISCALL service_007c6750(
    OpaqueCameraCommandOwner* owner, OpaqueWord argument);

}

#undef PKG_CAM_CDECL
#undef PKG_CAM_THISCALL
