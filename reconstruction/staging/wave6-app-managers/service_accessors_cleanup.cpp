#include "service_accessors_cleanup.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG06_WAVE6_CDECL __cdecl
#define PKG06_WAVE6_THISCALL __thiscall
#else
#define PKG06_WAVE6_CDECL __attribute__((cdecl))
#define PKG06_WAVE6_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::wave6_app_managers {

Wave6ServiceRoots g_wave6_service_roots{};

namespace {

void default_release(void*) {}

std::uintptr_t load_word(const void* address) {
  std::uintptr_t value = 0;
  std::memcpy(&value, address, sizeof(value));
  return value;
}

std::uint8_t* load_pointer(const void* address) {
  return reinterpret_cast<std::uint8_t*>(load_word(address));
}

}

OpaqueMessageCleanupPorts& message_cleanup_ports() {
  static OpaqueMessageCleanupPorts ports{&default_release};
  if (ports.release_00f47380 == nullptr) {
    ports.release_00f47380 = &default_release;
  }
  return ports;
}

extern "C" OpaqueStateManager* PKG06_WAVE6_CDECL
App_IStateManager_Get_0067dce0() {
  return reinterpret_cast<OpaqueStateManager*>(static_cast<std::uintptr_t>(
      g_wave6_service_roots.state_manager_015fd898));
}

extern "C" OpaquePropManager* PKG06_WAVE6_CDECL
App_IPropManager_Get_0067ddf0() {
  return reinterpret_cast<OpaquePropManager*>(
      static_cast<std::uintptr_t>(g_wave6_service_roots.prop_manager_015fd8f0));
}

void PKG06_WAVE6_THISCALL OpaqueMessageCleanupWindow::cleanup_storage_walker() {
  std::uint8_t* cursor = this->cursor_08;
  std::uint8_t* limit = this->limit_10;
  std::uint8_t* link = this->link_14;
  const std::uint8_t* end = this->end_18;
  while (cursor != end) {
    cursor = reinterpret_cast<std::uint8_t*>(cursor) + 0x18;
    if (cursor == limit) {
      const std::uintptr_t next = load_word(link + 4);
      link += 4;
      cursor = reinterpret_cast<std::uint8_t*>(next);
      limit = reinterpret_cast<std::uint8_t*>(next + 0xc0u);
    }
  }

  if (this->root_storage_00 == nullptr) {
    return;
  }
  std::uint8_t* item = load_pointer(&this->link_14);
  std::uint8_t* item_end = load_pointer(&this->array_end_24) + 4;
  for (; item < item_end; item += 4) {
    void* value = reinterpret_cast<void*>(load_word(item));
    if (value != nullptr) {
      message_cleanup_ports().release_00f47380(value);
    }
  }
  void* root_storage =
      reinterpret_cast<void*>(load_word(&this->root_storage_00));
  if (root_storage != nullptr) {
    message_cleanup_ports().release_00f47380(root_storage);
  }
}

}

#undef PKG06_WAVE6_CDECL
#undef PKG06_WAVE6_THISCALL
