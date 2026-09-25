#include "app_services.hpp"

#if defined(_MSC_VER)
#define PKG_APP_THISCALL __thiscall
#else
#define PKG_APP_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_app_services_wave6 {

OpaqueMessageServicePorts* g_message_service_ports = nullptr;
OpaqueCheatServicePorts* g_cheat_service_ports = nullptr;
MouseCameraServicePorts* g_mouse_camera_service_ports = nullptr;

namespace {

void dispatch_observer(OpaqueCheatNode* node, OpaqueWord event_argument,
                       bool enabled) {
  OpaqueObserver* observer = node->observer;
  OpaqueObserverVTable* vtable = observer->vtable;
  vtable->dispatch_1c(observer, event_argument, enabled);
}

}

extern "C" OpaqueMessageService* PKG_APP_THISCALL service_0067dc80(
    OpaqueMessageService* service, OpaqueWord ownership) {
  OpaqueMessageServicePorts& ports = *g_message_service_ports;
  ports.dispose_0067db10(service);
  if ((ownership & 1u) != 0u) {
    ports.deallocate_00f47380(service);
  }
  return service;
}

extern "C" OpaqueCheatService* PKG_APP_THISCALL service_0067e6b0(
    OpaqueCheatService* service, OpaqueWord ownership) {
  OpaqueCheatServicePorts& ports = *g_cheat_service_ports;
  ports.dispose_0067e2b0(service);
  if ((ownership & 1u) != 0u) {
    ports.deallocate_00f47380(service);
  }
  return service;
}

extern "C" void PKG_APP_THISCALL service_0067e6f0(
    OpaqueCheatService* service, OpaqueWord event_argument) {
  if (service->gate_064 == 0u) {
    return;
  }
  OpaqueCheatServicePorts& ports = *g_cheat_service_ports;
  OpaqueCheatNode* node = service->first_050;
  while (node != service->sentinel_04c) {
    dispatch_observer(node, event_argument, true);
    node = ports.next_00921580(node);
  }
}

extern "C" void PKG_APP_THISCALL service_0067e730(
    OpaqueCheatService* service, OpaqueWord event_argument) {
  OpaqueCheatServicePorts& ports = *g_cheat_service_ports;
  OpaqueCheatNode* node = service->first_050;
  while (node != service->sentinel_04c) {
    dispatch_observer(node, event_argument, false);
    node = ports.next_00921580(node);
  }
}

extern "C" void PKG_APP_THISCALL service_0068f9b0(
    ContinuationOwner* owner, ContinuationPort* continuation) {
  ContinuationPort* previous = owner->current_008;
  if (continuation == previous) {
    return;
  }
  if (continuation != nullptr) {
    continuation->vtable->install_00(continuation);
  }
  owner->current_008 = continuation;
  if (previous != nullptr) {
    previous->vtable->remove_04(previous);
  }
}

extern "C" OpaqueMouseCameraBase* PKG_APP_THISCALL service_007d9410(
    OpaqueMouseCameraTail* tail, OpaqueWord ownership) {
  auto* base = reinterpret_cast<OpaqueMouseCameraBase*>(
      reinterpret_cast<std::uintptr_t>(tail) - 4u);
  base->vtable_000 = reinterpret_cast<void*>(0x014128a8u);
  base->listener_vtable_004 = reinterpret_cast<void*>(0x01412894u);
  base->virtual_vtable_008 = reinterpret_cast<void*>(0x01412890u);
  if (base->owner_024 != nullptr) {
    OpaqueOwnedObject* owner = base->owner_024;
    owner->vtable->remove_04(owner);
  }
  base->virtual_vtable_008 = reinterpret_cast<void*>(0x013ef094u);
  base->listener_vtable_004 = reinterpret_cast<void*>(0x013eb394u);
  base->vtable_000 = reinterpret_cast<void*>(0x013eb938u);
  if ((ownership & 1u) != 0u) {
    g_mouse_camera_service_ports->deallocate_00f47380(base);
  }
  return base;
}

}

#undef PKG_APP_THISCALL
