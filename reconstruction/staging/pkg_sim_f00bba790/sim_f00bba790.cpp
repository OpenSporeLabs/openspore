#include "sim_f00bba790.hpp"

#if defined(_MSC_VER)
#define PKG_SIM_F00BBA790_THISCALL __thiscall
#else
#define PKG_SIM_F00BBA790_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_sim_f00bba790 {

namespace {

void PKG_SIM_F00BBA790_THISCALL inert_refresh_00bba640(OpaqueSimState*) {}

void PKG_SIM_F00BBA790_THISCALL
inert_reserve_00e25bd0(OpaqueWordVector*, OpaqueSimNode**, OpaqueSimNode**) {}

void PKG_SIM_F00BBA790_THISCALL inert_resize_00d01790(OpaqueWordVector*,
                                                      TargetSignedWord) {}

std::uint8_t PKG_SIM_F00BBA790_THISCALL
inert_keep_pending_00b8d970(OpaqueSimNode*) {
  return 0u;
}

void PKG_SIM_F00BBA790_THISCALL
inert_grow_insert_00aea5d0(OpaqueWordVector*, OpaqueSimNode**,
                           OpaqueSimNode**) {}

SimPorts inert_ports() {
  SimPorts ports;
  ports.refresh_00bba640 = inert_refresh_00bba640;
  ports.reserve_00e25bd0 = inert_reserve_00e25bd0;
  ports.resize_00d01790 = inert_resize_00d01790;
  ports.keep_pending_00b8d970 = inert_keep_pending_00b8d970;
  ports.grow_insert_00aea5d0 = inert_grow_insert_00aea5d0;
  return ports;
}

SimPorts g_ports = inert_ports();

OpaqueSimNode** advance_one_word(OpaqueSimNode** pointer) {
  return reinterpret_cast<OpaqueSimNode**>(
      reinterpret_cast<std::uintptr_t>(pointer) + 4U);
}

TargetSignedWord arithmetic_shift_right_2(TargetSignedWord value) {
  const TargetSignedWord truncated = value / 4;
  if (value < 0 && (value % 4) != 0) {
    return truncated - 1;
  }
  return truncated;
}

}

SimPorts& sim_f00bba790_ports() { return g_ports; }

void sim_f00bba790_set_ports(const SimPorts& ports) { g_ports = ports; }

void sim_f00bba790_reset_ports() { g_ports = inert_ports(); }

OpaqueWordVector* PKG_SIM_F00BBA790_THISCALL
sim_00bba790_flush_pending_and_select_vector(OpaqueSimState* state) {
  const SimPorts& ports = sim_f00bba790_ports();
  ports.refresh_00bba640(state);
  if (((state->state_5c >> 6U) & 1U) == 0U) {
    return &state->pending_84;
  }
  OpaqueWordVector& active = state->active_98;
  ports.reserve_00e25bd0(&active, active.begin, active.end);
  const TargetSignedWord span = static_cast<TargetSignedWord>(
      reinterpret_cast<std::uintptr_t>(state->pending_84.end) -
      reinterpret_cast<std::uintptr_t>(state->pending_84.begin));
  const TargetSignedWord count = arithmetic_shift_right_2(span);
  ports.resize_00d01790(&active, count);
  for (TargetSignedWord index = 0; index < count; ++index) {
    const std::ptrdiff_t step = static_cast<std::ptrdiff_t>(index);
    OpaqueSimNode* const element = state->pending_84.begin[step];
    if (ports.keep_pending_00b8d970(element) != 0u) {
      continue;
    }
    OpaqueSimNode** const slot = state->pending_84.begin + step;
    OpaqueSimNode** const end = active.end;
    if (end >= active.capacity) {
      ports.grow_insert_00aea5d0(&active, end, slot);
      continue;
    }
    active.end = advance_one_word(end);
    if (end == nullptr) {
      continue;
    }
    OpaqueSimNode* const moved = *slot;
    *end = moved;
    if (moved != nullptr) {
      moved->dispatch_table_00->notify_00(moved);
    }
  }
  return &active;
}

}
