#include "cheat_wave9.hpp"

#if defined(_MSC_VER)
#define PKG_CHEAT_WAVE9_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_CHEAT_WAVE9_THISCALL __attribute__((thiscall))
#else
#error "pkg-cheat-wave9 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_cheat_wave9 {

OpaquePorts g_cheat_wave9_ports{};

extern "C" bool PKG_CHEAT_WAVE9_THISCALL
opaque_service_forward_00abf790(OpaqueManager* manager, OpaqueWord first,
                                OpaqueWord second, OpaqueWord third) {
  OpaqueService* const service = g_cheat_wave9_ports.service_get_00b3d260();
  return service->vtable->operation_24(service, first, manager, second, third);
}

}

#undef PKG_CHEAT_WAVE9_THISCALL
