#include "world_state.hpp"

#if defined(_MSC_VER)
#define WORLD_THISCALL __thiscall
#else
#define WORLD_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg14_a1_world_state {

namespace {

void default_release(void*) {}

std::uint8_t default_render_state(void*, const std::uint32_t*, std::uint8_t) {
  return 0;
}

}

WorldState g_world_state{};
WorldReleasePorts g_world_release_ports{default_release, default_release};
RenderStatePort g_render_state_port = default_render_state;

void set_world_release_ports(ReleasePort release_field,
                             ReleasePort release_camera) {
  g_world_release_ports.release_field =
      release_field == nullptr ? default_release : release_field;
  g_world_release_ports.release_camera =
      release_camera == nullptr ? default_release : release_camera;
}

void set_render_state_port(RenderStatePort render_state) {
  g_render_state_port =
      render_state == nullptr ? default_render_state : render_state;
}

extern "C" std::uint8_t WORLD_THISCALL
world_viewer_clear_007c3ba0(OpaqueWorldViewer* viewer) {
  void* field = viewer->state_158;
  if (field != nullptr) {
    const std::uint32_t field_word =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(field));
    if (g_world_state.active_object == field_word) {
      g_world_state.flags_8a38 |= 0x2u;
      g_world_state.flags_9110 |= 0x8u;
      g_world_state.active_object = 0;
    }
    g_world_release_ports.release_field(field);
    viewer->state_158 = nullptr;
  }

  void* camera = viewer->camera_170;
  if (camera != nullptr) {
    g_world_release_ports.release_camera(camera);
    viewer->camera_170 = nullptr;
    return 1;
  }
  return 0;
}

extern "C" void WORLD_THISCALL world_viewer_set_background_007c3c20(
    OpaqueWorldViewer* viewer, const std::uint32_t* source) {
  viewer->background_140[0] = source[0];
  viewer->background_140[1] = source[1];
  viewer->background_140[2] = source[2];
  viewer->background_140[3] = source[3];
}

extern "C" std::uint8_t WORLD_THISCALL world_viewer_apply_flags_007c3c50(
    OpaqueWorldViewer* viewer, std::uint8_t flags) {
  std::uint8_t normalized = 0;
  if ((flags & 0x1u) != 0) {
    normalized = static_cast<std::uint8_t>(normalized | 0x1u);
  }
  if ((flags & 0x2u) != 0) {
    normalized = static_cast<std::uint8_t>(normalized | 0x2u);
  }
  if ((flags & 0x4u) != 0) {
    normalized = static_cast<std::uint8_t>(normalized | 0x4u);
  }

  const std::uint32_t* background = viewer->background_140;
  void* camera = viewer->camera_170;
  return g_render_state_port(camera, background, normalized);
}

}
