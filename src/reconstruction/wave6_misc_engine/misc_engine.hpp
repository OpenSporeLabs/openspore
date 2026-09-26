#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave6-misc-engine requires an x86-32 target"
#endif

namespace openspore::reconstruction::wave6_misc_engine {

using TargetWord = std::uint32_t;

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");

#if defined(_MSC_VER)
#define WAVE6_CDECL __cdecl
#define WAVE6_THISCALL __thiscall
#else
#define WAVE6_CDECL __attribute__((cdecl))
#define WAVE6_THISCALL __attribute__((thiscall))
#endif

struct OpaqueIAppSystem;
struct OpaqueGameTimeManager;
struct OpaqueAppSystem;
struct OpaqueMessageService;
struct OpaqueMessageManager;
struct OpaqueDestructibleVtable;

struct OpaqueIAppSystem {
  std::array<std::byte, 0x10> opaque;
};

struct OpaqueGameTimeManager {
  std::array<std::byte, 0x10> opaque;
};

struct OpaqueAppSystem {
  std::array<std::byte, 0x173> opaque;
};

struct OpaqueMessageService {
  std::array<std::byte, 0x10> opaque;
};

struct OpaqueMessageManager {
  std::array<std::byte, 0xbc> opaque;
};

struct OpaqueDestructible {
  OpaqueDestructibleVtable* vtable;
  std::array<std::byte, 0x20> opaque;
};

struct MessageQueuePorts {
  using Prepare = void(WAVE6_THISCALL*)(OpaqueMessageService*, TargetWord,
                                        TargetWord);
  using Query = TargetWord(WAVE6_THISCALL*)(OpaqueMessageService*);

  Prepare prepare_7c = nullptr;
  Query query_90 = nullptr;
};

struct DeletingDestructorPorts {
  using BaseDestroy = void(WAVE6_THISCALL*)(OpaqueDestructible*);
  using GlobalDelete = void(WAVE6_CDECL*)(OpaqueDestructible*);

  BaseDestroy base_destroy_005725a0 = nullptr;
  GlobalDelete global_delete_00f47380 = nullptr;
};

extern TargetWord g_game_time_manager_0167eb3c;
extern MessageQueuePorts g_message_queue_ports;
extern DeletingDestructorPorts g_deleting_destructor_ports;

OpaqueGameTimeManager* WAVE6_CDECL game_time_manager_get_00b3d480();
TargetWord WAVE6_THISCALL message_manager_get_queue_0098f4d0(
    OpaqueMessageManager* manager, TargetWord queue_index, void* queue);
OpaqueDestructible* WAVE6_THISCALL destructible_lifecycle_thunk_00b63980(
    OpaqueDestructible* receiver, TargetWord deleting_flag);

}
