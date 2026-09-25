#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg14-a1 world-state staging requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define WORLD_THISCALL __thiscall
#else
#define WORLD_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg14_a1_world_state {

struct OpaqueWorldViewer {
  std::byte padding_000[0x140];
  std::uint32_t background_140[4];
  std::uint32_t render_type_150;
  std::uint8_t state_154;
  std::byte padding_155[3];
  void* state_158;
  std::byte padding_15c[0x10];
  std::uint8_t state_16c;
  std::byte padding_16d[3];
  void* camera_170;
};

struct WorldState {
  std::uint32_t active_object;
  std::uint32_t flags_8a38;
  std::uint32_t flags_9110;
};

using ReleasePort = void (*)(void*);
using RenderStatePort = std::uint8_t (*)(void*, const std::uint32_t*,
                                         std::uint8_t);

struct WorldReleasePorts {
  ReleasePort release_field;
  ReleasePort release_camera;
};

static_assert(sizeof(void*) == 4, "world-state target pointers are 32-bit");
static_assert(sizeof(OpaqueWorldViewer) == 0x174, "world viewer extent");
static_assert(offsetof(OpaqueWorldViewer, background_140) == 0x140,
              "background field offset");
static_assert(offsetof(OpaqueWorldViewer, state_158) == 0x158,
              "state field offset");
static_assert(offsetof(OpaqueWorldViewer, camera_170) == 0x170,
              "camera field offset");

extern WorldState g_world_state;
extern WorldReleasePorts g_world_release_ports;
extern RenderStatePort g_render_state_port;

void set_world_release_ports(ReleasePort release_field,
                             ReleasePort release_camera);
void set_render_state_port(RenderStatePort render_state);

extern "C" std::uint8_t WORLD_THISCALL
world_viewer_clear_007c3ba0(OpaqueWorldViewer* viewer);
extern "C" void WORLD_THISCALL world_viewer_set_background_007c3c20(
    OpaqueWorldViewer* viewer, const std::uint32_t* source);
extern "C" std::uint8_t WORLD_THISCALL world_viewer_apply_flags_007c3c50(
    OpaqueWorldViewer* viewer, std::uint8_t flags);

}

#undef WORLD_THISCALL
