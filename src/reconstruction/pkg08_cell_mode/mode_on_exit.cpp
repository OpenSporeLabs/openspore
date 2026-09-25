#include "mode_on_exit.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg08_cell_mode {

OpaqueGlobalViews g_mode_on_exit_globals{};
NativePorts g_mode_on_exit_ports{};

namespace {

template <typename Value>
Value load(const void* address) {
  Value value{};
  std::memcpy(&value, address, sizeof(value));
  return value;
}

template <typename Value>
void store(void* address, Value value) {
  std::memcpy(address, &value, sizeof(value));
}

OpaqueMode* iterator_owner() {
  return reinterpret_cast<OpaqueMode*>(
      g_mode_on_exit_globals.cell_game_016b3c04 + 0x54U);
}

}

extern "C" void __thiscall cell_mode_on_exit_00e7fc00(OpaqueMode* mode) {
  static_cast<void>(mode);
  g_mode_on_exit_ports.helper_00e53580();

  store(g_mode_on_exit_globals.destination_01550adc,
        load<float>(g_mode_on_exit_globals.source_016b3bf0));
  store(g_mode_on_exit_globals.destination_01550af0,
        load<float>(g_mode_on_exit_globals.source_016b3bec));
  store(g_mode_on_exit_globals.destination_01550a84,
        load<std::uint32_t>(g_mode_on_exit_globals.source_016b3bf8));
  store(g_mode_on_exit_globals.destination_01550aec,
        load<float>(g_mode_on_exit_globals.source_016b3be8));
  store(g_mode_on_exit_globals.destination_01550ae0,
        load<float>(g_mode_on_exit_globals.source_016b3be4));
  store(g_mode_on_exit_globals.destination_0166c004,
        load<std::uint32_t>(g_mode_on_exit_globals.source_016b3bfc));
  store(g_mode_on_exit_globals.destination_01550ad8,
        load<std::uint32_t>(g_mode_on_exit_globals.source_016b3bf4));
  store(g_mode_on_exit_globals.destination_01550ae4,
        load<float>(g_mode_on_exit_globals.source_016b3be0));

  OpaqueIterator iterator = g_mode_on_exit_ports.iterator_begin_00e31100();
  OpaqueRecord* record = g_mode_on_exit_ports.iterator_access_00b72230(
      iterator_owner(), &iterator);
  while (record != nullptr) {
    g_mode_on_exit_ports.record_00e7e130(iterator_owner(), record, 0.0F, 0, 1);
    record = g_mode_on_exit_ports.iterator_access_00b72230(iterator_owner(),
                                                           &iterator);
  }

  g_mode_on_exit_ports.iterator_cleanup_00b72110(iterator_owner());
  OpaqueService* service = g_mode_on_exit_ports.service_acquire_0067ddd0();
  g_mode_on_exit_ports.service_vtable_0098(service, 7, 0);
  g_mode_on_exit_ports.helper_00e64a00();
  g_mode_on_exit_ports.helper_00e82d40();
}

}
