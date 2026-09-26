#include "app_services.hpp"

#if defined(_MSC_VER)
#define PKG_APP_CDECL __cdecl
#define PKG_APP_THISCALL __thiscall
#else
#define PKG_APP_CDECL __attribute__((cdecl))
#define PKG_APP_THISCALL __attribute__((thiscall))
#endif

#if defined(_MSC_VER)
#define PKG_APP_NOINLINE __declspec(noinline)
#else
#define PKG_APP_NOINLINE __attribute__((noinline))
#endif

namespace openspore::reconstruction::pkg_app_services_wave6 {

OpaqueMessageServicePorts* g_message_service_ports = nullptr;
OpaqueCheatServicePorts* g_cheat_service_ports = nullptr;
MouseCameraServicePorts* g_mouse_camera_service_ports = nullptr;

namespace detail {

template <typename Function>
PKG_APP_NOINLINE void call_thiscall_noargs(Function function, void* receiver) {
  __asm__ volatile(
      "movl %0, %%ecx\n\t"
      "call *%1"
      :
      : "r"(receiver), "r"(function)
      : "eax", "ecx", "edx", "cc", "memory");
}

template <typename Function, typename Arg1, typename Arg2>
PKG_APP_NOINLINE void call_thiscall_two(Function function, void* receiver,
                                        Arg1 first, Arg2 second) {
  __asm__ volatile(
      "movl %1, %%eax\n\t"
      "movl %0, %%ecx\n\t"
      "pushl %3\n\t"
      "pushl %2\n\t"
      "call *%%eax"
      :
      : "r"(receiver), "m"(function), "r"(first), "r"(second)
      : "eax", "cc", "ecx", "edx", "memory");
}

}

using namespace detail;

extern "C" OpaqueMessageService* PKG_APP_THISCALL
service_0067dc80(OpaqueMessageService* service, OpaqueWord ownership) {
  OpaqueMessageServicePorts* ports = g_message_service_ports;
  call_thiscall_noargs(ports->dispose_0067db10, service);
  if ((ownership & 1u) != 0u) {
    ports->deallocate_00f47380(service);
  }
  return service;
}

extern "C" OpaqueCheatService* PKG_APP_THISCALL
service_0067e6b0(OpaqueCheatService* service, OpaqueWord ownership) {
  OpaqueCheatServicePorts* ports = g_cheat_service_ports;
  call_thiscall_noargs(ports->dispose_0067e2b0, service);
  if ((ownership & 1u) != 0u) {
    ports->deallocate_00f47380(service);
  }
  return service;
}

extern "C" void PKG_APP_THISCALL service_0067e6f0(OpaqueCheatService* service,
                                                  OpaqueWord event_argument) {
  if (service->gate_064 == 0u) {
    return;
  }
  OpaqueCheatServicePorts& ports = *g_cheat_service_ports;
  OpaqueCheatNode* node = service->first_050;
  while (node != service->sentinel_04c) {
    OpaqueObserver* observer = node->observer;
    call_thiscall_two(observer->vtable->dispatch_1c, observer,
                      static_cast<OpaqueWord>(true), event_argument);
    node = ports.next_00921580(node);
  }
}

extern "C" void PKG_APP_THISCALL service_0067e730(OpaqueCheatService* service,
                                                  OpaqueWord event_argument) {
  OpaqueCheatServicePorts& ports = *g_cheat_service_ports;
  OpaqueCheatNode* node = service->first_050;
  while (node != service->sentinel_04c) {
    OpaqueObserver* observer = node->observer;
    call_thiscall_two(observer->vtable->dispatch_1c, observer,
                      static_cast<OpaqueWord>(false), event_argument);
    node = ports.next_00921580(node);
  }
}

extern "C" void PKG_APP_THISCALL
service_0068f9b0(ContinuationOwner* owner, ContinuationPort* continuation) {
  ContinuationPort* previous = owner->current_008;
  if (continuation == previous) {
    return;
  }
  if (continuation != nullptr) {
    call_thiscall_noargs(continuation->vtable->install_00, continuation);
  }
  owner->current_008 = continuation;
  if (previous != nullptr) {
    call_thiscall_noargs(previous->vtable->remove_04, previous);
  }
}

extern "C" OpaqueMouseCameraBase* PKG_APP_THISCALL
service_007d9410(OpaqueMouseCameraTail* tail, OpaqueWord ownership) {
  auto* base = reinterpret_cast<OpaqueMouseCameraBase*>(
      reinterpret_cast<std::uintptr_t>(tail) - 4u);
  base->vtable_000 = reinterpret_cast<void*>(0x014128a8u);
  base->listener_vtable_004 = reinterpret_cast<void*>(0x01412894u);
  base->virtual_vtable_008 = reinterpret_cast<void*>(0x01412890u);
  if (base->owner_024 != nullptr) {
    OpaqueOwnedObject* owner = base->owner_024;
    call_thiscall_noargs(owner->vtable->remove_04, owner);
  }
  base->virtual_vtable_008 = reinterpret_cast<void*>(0x013ef094u);
  base->listener_vtable_004 = reinterpret_cast<void*>(0x013eb394u);
  base->vtable_000 = reinterpret_cast<void*>(0x013eb938u);
  MouseCameraServicePorts* ports = g_mouse_camera_service_ports;
  if ((ownership & 1u) != 0u) {
    ports->deallocate_00f47380(base);
  }
  return base;
}

}

#undef PKG_APP_CDECL
#undef PKG_APP_THISCALL
#undef PKG_APP_NOINLINE
