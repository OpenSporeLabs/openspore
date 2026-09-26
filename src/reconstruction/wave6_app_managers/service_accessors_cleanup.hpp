#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6 app-manager infrastructure requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "wave6 app-manager pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "wave6 app-manager words are 32-bit");

#if defined(_MSC_VER)
#define PKG06_WAVE6_CDECL __cdecl
#define PKG06_WAVE6_THISCALL __thiscall
#else
#define PKG06_WAVE6_CDECL __attribute__((cdecl))
#define PKG06_WAVE6_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::wave6_app_managers {

struct OpaqueStateManager;
struct OpaquePropManager;

struct Wave6ServiceRoots {
  std::uint32_t state_manager_015fd898 = 0;
  std::uint32_t prop_manager_015fd8f0 = 0;
};

extern Wave6ServiceRoots g_wave6_service_roots;

struct OpaqueMessageCleanupWindow {
  void* root_storage_00 = nullptr;
  std::uint32_t opaque_04 = 0;
  std::uint8_t* cursor_08 = nullptr;
  std::uint32_t opaque_0c = 0;
  std::uint8_t* limit_10 = nullptr;
  std::uint8_t* link_14 = nullptr;
  std::uint8_t* end_18 = nullptr;
  std::uint32_t opaque_1c = 0;
  std::uint32_t opaque_20 = 0;
  std::uint8_t* array_end_24 = nullptr;
  std::uint32_t opaque_28 = 0;
  void PKG06_WAVE6_THISCALL cleanup_storage_walker()
#if !defined(_MSC_VER)
      asm("MessageManagerCleanupStorageWalker_008841f0")
#endif
          ;
};

struct OpaqueMessageManager {
  std::uint32_t opaque_00 = 0;
  std::uint32_t opaque_04 = 0;
  OpaqueMessageCleanupWindow cleanup_08;
};

struct OpaqueMessageCleanupPorts {
  using Release = void (*)(void*);
  Release release_00f47380 = nullptr;
};

OpaqueMessageCleanupPorts& message_cleanup_ports();

static_assert(offsetof(OpaqueMessageCleanupWindow, root_storage_00) == 0x00,
              "wave6 message root storage offset");
static_assert(offsetof(OpaqueMessageCleanupWindow, cursor_08) == 0x08,
              "wave6 message cursor offset");
static_assert(offsetof(OpaqueMessageCleanupWindow, limit_10) == 0x10,
              "wave6 message limit offset");
static_assert(offsetof(OpaqueMessageCleanupWindow, link_14) == 0x14,
              "wave6 message link offset");
static_assert(offsetof(OpaqueMessageCleanupWindow, end_18) == 0x18,
              "wave6 message end offset");
static_assert(offsetof(OpaqueMessageCleanupWindow, array_end_24) == 0x24,
              "wave6 message array end offset");
static_assert(sizeof(OpaqueMessageCleanupWindow) == 0x2c,
              "wave6 message cleanup window size");
static_assert(offsetof(OpaqueMessageManager, cleanup_08) == 0x08,
              "wave6 message cleanup receiver offset");

extern "C" OpaqueStateManager* PKG06_WAVE6_CDECL
App_IStateManager_Get_0067dce0();

extern "C" OpaquePropManager* PKG06_WAVE6_CDECL App_IPropManager_Get_0067ddf0();

}

#undef PKG06_WAVE6_CDECL
#undef PKG06_WAVE6_THISCALL
