#include "resource_state_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_RSS_CDECL __cdecl
#define PKG_RSS_THISCALL __thiscall
#else
#define PKG_RSS_CDECL __attribute__((cdecl))
#define PKG_RSS_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_resource_state_safe_wave10 {
namespace {

void PKG_RSS_THISCALL inert_destroy_port(OpaqueRecordWrite*) {}

void PKG_RSS_CDECL inert_untrack_port(void*) {}

ResourceStateSafePorts make_default_ports() {
  ResourceStateSafePorts defaults{};
  defaults.destroy_00e30f90 = &inert_destroy_port;
  defaults.untrack_00f47380 = &inert_untrack_port;
  return defaults;
}

ResourceStateSafePorts ports = make_default_ports();

}

void resource_state_safe_set_ports(ResourceStateSafePorts new_ports) {
  if (new_ports.destroy_00e30f90 == nullptr) {
    new_ports.destroy_00e30f90 = &inert_destroy_port;
  }
  if (new_ports.untrack_00f47380 == nullptr) {
    new_ports.untrack_00f47380 = &inert_untrack_port;
  }
  ports = new_ports;
}

void resource_state_safe_reset_ports() { ports = make_default_ports(); }

OpaqueRecordWrite* PKG_RSS_THISCALL record_write_get_state_00e310c0(
    OpaqueRecordWrite* receiver, ReleaseFlag state_release_flag) {
  ports.destroy_00e30f90(receiver);
  if ((state_release_flag & kReleaseFlagMask) != 0) {
    ports.untrack_00f47380(receiver);
  }
  return receiver;
}

}

#undef PKG_RSS_CDECL
#undef PKG_RSS_THISCALL
