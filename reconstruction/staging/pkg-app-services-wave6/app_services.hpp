#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "app services wave6 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_APP_CDECL __cdecl
#define PKG_APP_THISCALL __thiscall
#else
#define PKG_APP_CDECL __attribute__((cdecl))
#define PKG_APP_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_app_services_wave6 {

static_assert(sizeof(void*) == 4, "app services wave6 pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "app services wave6 words are 32-bit");

using OpaqueWord = std::uint32_t;

struct OpaqueOwnedService {
  std::uint32_t opaque[4]{};
};

struct OpaqueMessageService {
  OpaqueWord opaque[12]{};
};

struct OpaqueMessageServicePorts {
  using Dispose = void(PKG_APP_THISCALL*)(OpaqueMessageService*);
  using Deallocate = void(PKG_APP_CDECL*)(OpaqueMessageService*);

  Dispose dispose_0067db10 = nullptr;
  Deallocate deallocate_00f47380 = nullptr;
};

extern OpaqueMessageServicePorts* g_message_service_ports;

extern "C" OpaqueMessageService* PKG_APP_THISCALL
service_0067dc80(OpaqueMessageService* service, OpaqueWord ownership);

struct OpaqueObserver;

struct OpaqueObserverVTable {
  void* slots_00[7]{};
  void(PKG_APP_THISCALL* dispatch_1c)(OpaqueObserver*, bool,
                                      OpaqueWord) = nullptr;
};

struct OpaqueObserver {
  OpaqueObserverVTable* vtable = nullptr;
  std::uint32_t opaque[3]{};
};

struct OpaqueCheatNode {
  std::uint32_t opaque[4]{};
  OpaqueObserver* observer = nullptr;
};

struct OpaqueCheatService {
  std::uint32_t opaque_000[19]{};
  OpaqueCheatNode* sentinel_04c = nullptr;
  OpaqueCheatNode* first_050 = nullptr;
  std::uint32_t opaque_054[4]{};
  std::uint8_t gate_064 = 0;
};

static_assert(offsetof(OpaqueObserverVTable, dispatch_1c) == 0x1c,
              "observer dispatch slot");
static_assert(offsetof(OpaqueCheatNode, observer) == 0x10,
              "cheat node observer offset");
static_assert(offsetof(OpaqueCheatService, sentinel_04c) == 0x4c,
              "cheat sentinel offset");
static_assert(offsetof(OpaqueCheatService, first_050) == 0x50,
              "cheat first node offset");
static_assert(offsetof(OpaqueCheatService, gate_064) == 0x64,
              "cheat dispatch gate offset");

struct OpaqueCheatServicePorts {
  using Dispose = void(PKG_APP_THISCALL*)(OpaqueCheatService*);
  using Deallocate = void(PKG_APP_CDECL*)(OpaqueCheatService*);
  using NextNode = OpaqueCheatNode*(PKG_APP_CDECL*)(OpaqueCheatNode*);

  Dispose dispose_0067e2b0 = nullptr;
  Deallocate deallocate_00f47380 = nullptr;
  NextNode next_00921580 = nullptr;
};

extern OpaqueCheatServicePorts* g_cheat_service_ports;

extern "C" OpaqueCheatService* PKG_APP_THISCALL
service_0067e6b0(OpaqueCheatService* service, OpaqueWord ownership);

extern "C" void PKG_APP_THISCALL service_0067e6f0(OpaqueCheatService* service,
                                                  OpaqueWord event_argument);

extern "C" void PKG_APP_THISCALL service_0067e730(OpaqueCheatService* service,
                                                  OpaqueWord event_argument);

struct ContinuationPort;

struct ContinuationVTable {
  void(PKG_APP_THISCALL* install_00)(ContinuationPort*) = nullptr;
  void(PKG_APP_THISCALL* remove_04)(ContinuationPort*) = nullptr;
};

struct ContinuationPort {
  ContinuationVTable* vtable = nullptr;
};

struct ContinuationOwner {
  std::uint32_t opaque_000[2]{};
  ContinuationPort* current_008 = nullptr;
};

static_assert(offsetof(ContinuationOwner, current_008) == 0x8,
              "continuation current slot");
static_assert(sizeof(ContinuationVTable) == 8,
              "continuation observed virtual prefix");

extern "C" void PKG_APP_THISCALL
service_0068f9b0(ContinuationOwner* owner, ContinuationPort* continuation);

struct OpaqueOwnedObject;

struct OpaqueObjectVTable {
  void* slots_00[1]{};
  void(PKG_APP_THISCALL* remove_04)(OpaqueOwnedObject*) = nullptr;
};

struct OpaqueOwnedObject {
  OpaqueObjectVTable* vtable = nullptr;
  std::uint32_t opaque[8]{};
};

struct OpaqueMouseCameraBase {
  void* vtable_000 = nullptr;
  void* listener_vtable_004 = nullptr;
  void* virtual_vtable_008 = nullptr;
  OpaqueWord reference_count_00c = 0;
  OpaqueOwnedObject* owner_024 = nullptr;
  std::uint32_t opaque_028 = 0;
};

struct OpaqueMouseCameraTail {
  std::uint32_t opaque = 0;
};

struct MouseCameraServicePorts {
  using Deallocate = void(PKG_APP_CDECL*)(OpaqueMouseCameraBase*);

  Deallocate deallocate_00f47380 = nullptr;
};

extern MouseCameraServicePorts* g_mouse_camera_service_ports;

extern "C" OpaqueMouseCameraBase* PKG_APP_THISCALL
service_007d9410(OpaqueMouseCameraTail* tail, OpaqueWord ownership);

}

#undef PKG_APP_CDECL
#undef PKG_APP_THISCALL
