#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "app canvas wave6 staging requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define APP_CANVAS_THISCALL __thiscall
#define APP_CANVAS_STDCALL __stdcall
#else
#define APP_CANVAS_THISCALL __attribute__((thiscall))
#define APP_CANVAS_STDCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_app_canvas_wave6 {

using OpaqueWord = std::uint32_t;
using OpaqueHandle = void*;

struct OpaqueCanvas;
struct OpaqueDispatchRecord;
struct OpaqueMessageManager;
struct OpaqueOwnerManager;

using MessageDispatch = void(APP_CANVAS_THISCALL*)(OpaqueMessageManager*,
                                                   OpaqueWord,
                                                   OpaqueDispatchRecord*,
                                                   OpaqueWord);
using OwnerDispatch = void(APP_CANVAS_THISCALL*)(OpaqueOwnerManager*,
                                                 OpaqueWord);
using DispatchFallback = void (*)(OpaqueDispatchRecord*, void*);

struct OpaqueMessageManagerVtable {
  void* slots[5];
  MessageDispatch dispatch;
};

struct OpaqueOwnerManagerVtable {
  void* slots[12];
  OwnerDispatch dispatch;
};

struct OpaqueMessageManager {
  OpaqueMessageManagerVtable* vtable;
};

struct OpaqueOwnerManager {
  OpaqueOwnerManagerVtable* vtable;
};

struct OpaqueDispatchRecord {
  OpaqueWord code;
  OpaqueCanvas* canvas;
  OpaqueWord zero;
};

struct OpaqueCanvas {
  void* vtable;
  OpaqueWord field_4;
  OpaqueWord field_8;
  std::uint8_t field_c[0x28];
  OpaqueWord field_34;
  OpaqueWord field_38;
  std::uint8_t field_3c[0x11];
  std::uint8_t field_4d;
  std::uint8_t field_4e;
  std::uint8_t field_4f;
  OpaqueWord field_50;
  OpaqueWord field_54;
  OpaqueWord field_58;
  OpaqueMessageManager* field_5c;
  OpaqueOwnerManager* field_60;
  DispatchFallback field_64;
  void* field_68;
  std::uint8_t field_6c[3];
  std::uint16_t field_70;
  OpaqueHandle field_74;
  OpaqueWord field_78;
  OpaqueHandle field_7c;
  OpaqueHandle field_80;
  OpaqueWord field_84;
  OpaqueWord field_88;
  OpaqueWord field_8c;
  OpaqueWord field_90;
  OpaqueWord field_94;
};

struct OpaqueGlobalState {
  std::uint8_t opaque[0x10];
  OpaqueWord field_10;
};

struct OpaqueCanvasExtent {
  OpaqueWord first;
  OpaqueWord second;
};

using SetThreadState = OpaqueWord(APP_CANVAS_STDCALL*)(OpaqueWord);
using SetActiveHandle = OpaqueHandle(APP_CANVAS_STDCALL*)(OpaqueHandle);
using GetAncestorHandle = OpaqueHandle(APP_CANVAS_STDCALL*)(OpaqueHandle,
                                                            OpaqueWord);
using QueryZoomed = OpaqueWord(APP_CANVAS_STDCALL*)(OpaqueHandle);
using KillObjectTimer = OpaqueWord(APP_CANVAS_STDCALL*)(OpaqueHandle,
                                                        OpaqueWord);
using DestroyHandle = OpaqueWord(APP_CANVAS_STDCALL*)(OpaqueHandle);
using GetModuleHandle = OpaqueHandle(APP_CANVAS_STDCALL*)(const char*);
using UnregisterClassHandle = OpaqueWord(APP_CANVAS_STDCALL*)(const char*,
                                                              OpaqueHandle);
using DeleteObjectHandle = OpaqueWord(APP_CANVAS_STDCALL*)(OpaqueHandle);
using QuerySystemParameters = OpaqueWord(APP_CANVAS_STDCALL*)(OpaqueWord,
                                                              OpaqueWord, void*,
                                                              OpaqueWord);

struct OpaqueCanvasSystems {
  SetThreadState set_thread_state;
  SetActiveHandle set_active_handle;
  GetAncestorHandle get_ancestor_handle;
  QueryZoomed query_zoomed;
  KillObjectTimer kill_object_timer;
  DestroyHandle destroy_handle;
  GetModuleHandle get_module_handle;
  UnregisterClassHandle unregister_class_handle;
  DeleteObjectHandle delete_object_handle;
  QuerySystemParameters query_system_parameters;
  OpaqueGlobalState* global_state;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueDispatchRecord) == 0x0c);
static_assert(offsetof(OpaqueDispatchRecord, code) == 0x00);
static_assert(offsetof(OpaqueDispatchRecord, canvas) == 0x04);
static_assert(offsetof(OpaqueDispatchRecord, zero) == 0x08);
static_assert(offsetof(OpaqueMessageManagerVtable, dispatch) == 0x14);
static_assert(offsetof(OpaqueOwnerManagerVtable, dispatch) == 0x30);
static_assert(sizeof(OpaqueCanvas) == 0x98);
static_assert(offsetof(OpaqueCanvas, field_8) == 0x08);
static_assert(offsetof(OpaqueCanvas, field_34) == 0x34);
static_assert(offsetof(OpaqueCanvas, field_38) == 0x38);
static_assert(offsetof(OpaqueCanvas, field_4d) == 0x4d);
static_assert(offsetof(OpaqueCanvas, field_4e) == 0x4e);
static_assert(offsetof(OpaqueCanvas, field_4f) == 0x4f);
static_assert(offsetof(OpaqueCanvas, field_5c) == 0x5c);
static_assert(offsetof(OpaqueCanvas, field_60) == 0x60);
static_assert(offsetof(OpaqueCanvas, field_64) == 0x64);
static_assert(offsetof(OpaqueCanvas, field_68) == 0x68);
static_assert(offsetof(OpaqueCanvas, field_70) == 0x70);
static_assert(offsetof(OpaqueCanvas, field_74) == 0x74);
static_assert(offsetof(OpaqueCanvas, field_80) == 0x80);
static_assert(offsetof(OpaqueCanvas, field_8c) == 0x8c);
static_assert(offsetof(OpaqueCanvas, field_90) == 0x90);
static_assert(offsetof(OpaqueCanvas, field_94) == 0x94);
static_assert(offsetof(OpaqueGlobalState, field_10) == 0x10);
static_assert(sizeof(OpaqueCanvasExtent) == 0x08);

extern "C" OpaqueWord APP_CANVAS_THISCALL app_canvas_00847a40(OpaqueCanvas*,
                                                              OpaqueWord);
extern "C" OpaqueHandle APP_CANVAS_THISCALL app_canvas_00847a90(OpaqueCanvas*,
                                                                std::uint8_t);
extern "C" bool APP_CANVAS_THISCALL app_canvas_00847b10(OpaqueCanvas*);
extern "C" std::uint16_t APP_CANVAS_THISCALL app_canvas_00847b40(OpaqueCanvas*);
extern "C" bool APP_CANVAS_THISCALL app_canvas_00848020(OpaqueCanvas*);
extern "C" void APP_CANVAS_THISCALL app_canvas_00848100(OpaqueCanvas*,
                                                        OpaqueCanvasExtent*);

void app_canvas_wave6_set_systems(OpaqueCanvasSystems*);

}

#undef APP_CANVAS_THISCALL
#undef APP_CANVAS_STDCALL
