#include <cstddef>
#include <cstdint>

#include "world_state.hpp"

namespace {

using openspore::reconstruction::pkg14_a1_world_state::g_world_state;
using openspore::reconstruction::pkg14_a1_world_state::OpaqueWorldViewer;
using openspore::reconstruction::pkg14_a1_world_state::set_render_state_port;
using openspore::reconstruction::pkg14_a1_world_state::set_world_release_ports;
using openspore::reconstruction::pkg14_a1_world_state::
    world_viewer_apply_flags_007c3c50;
using openspore::reconstruction::pkg14_a1_world_state::
    world_viewer_clear_007c3ba0;
using openspore::reconstruction::pkg14_a1_world_state::
    world_viewer_set_background_007c3c20;
using openspore::reconstruction::pkg14_a1_world_state::WorldState;

int failures = 0;

void check(bool value) {
  if (!value) {
    ++failures;
  }
}

struct ReleaseCall {
  const char* slot;
  void* value;
};

ReleaseCall release_calls[8];
std::size_t release_count = 0;

struct RenderCall {
  void* camera;
  const std::uint32_t* background;
  std::uint8_t flags;
  std::uint8_t result;
};

RenderCall render_calls[8];
std::size_t render_count = 0;

void record_field_release(void* value) {
  release_calls[release_count++] = {"field", value};
}

void record_camera_release(void* value) {
  release_calls[release_count++] = {"camera", value};
}

std::uint8_t record_render(void* camera, const std::uint32_t* background,
                           std::uint8_t flags) {
  render_calls[render_count++] = {camera, background, flags, 0x5a};
  return 0x5a;
}

void reset_fixture() {
  g_world_state = {};
  release_count = 0;
  render_count = 0;
  set_world_release_ports(record_field_release, record_camera_release);
  set_render_state_port(record_render);
}

void test_clear_active_state_order_and_reset() {
  reset_fixture();
  OpaqueWorldViewer viewer{};
  viewer.state_158 = reinterpret_cast<void*>(0x1000u);
  viewer.camera_170 = reinterpret_cast<void*>(0x2000u);
  g_world_state.active_object = 0x1000u;
  g_world_state.flags_8a38 = 0x40u;
  g_world_state.flags_9110 = 0x10u;

  check(world_viewer_clear_007c3ba0(&viewer) == 1);
  check(release_count == 2);
  check(release_calls[0].slot[0] == 'f');
  check(release_calls[0].value == reinterpret_cast<void*>(0x1000u));
  check(release_calls[1].slot[0] == 'c');
  check(release_calls[1].value == reinterpret_cast<void*>(0x2000u));
  check(viewer.state_158 == nullptr);
  check(viewer.camera_170 == nullptr);
  check(g_world_state.active_object == 0);
  check(g_world_state.flags_8a38 == 0x42u);
  check(g_world_state.flags_9110 == 0x18u);
}

void test_clear_inactive_state_still_releases() {
  reset_fixture();
  OpaqueWorldViewer viewer{};
  viewer.state_158 = reinterpret_cast<void*>(0x3000u);
  viewer.camera_170 = reinterpret_cast<void*>(0x4000u);
  g_world_state.active_object = 0x9999u;
  g_world_state.flags_8a38 = 0x40u;
  g_world_state.flags_9110 = 0x10u;

  check(world_viewer_clear_007c3ba0(&viewer) == 1);
  check(release_count == 2);
  check(g_world_state.active_object == 0x9999u);
  check(g_world_state.flags_8a38 == 0x40u);
  check(g_world_state.flags_9110 == 0x10u);
}

void test_clear_null_fields_returns_without_releases() {
  reset_fixture();
  OpaqueWorldViewer viewer{};
  g_world_state.active_object = 0x1234u;
  g_world_state.flags_8a38 = 0x44u;
  g_world_state.flags_9110 = 0x88u;

  check(world_viewer_clear_007c3ba0(&viewer) == 0);
  check(release_count == 0);
  check(g_world_state.active_object == 0x1234u);
  check(g_world_state.flags_8a38 == 0x44u);
  check(g_world_state.flags_9110 == 0x88u);
}

void test_background_copy_preserves_all_words() {
  reset_fixture();
  OpaqueWorldViewer viewer{};
  const std::uint32_t source[4] = {0x01020304u, 0x11121314u, 0x21222324u,
                                   0x31323334u};
  viewer.background_140[0] = 0;
  viewer.background_140[1] = 0;
  viewer.background_140[2] = 0;
  viewer.background_140[3] = 0;

  world_viewer_set_background_007c3c20(&viewer, source);
  check(viewer.background_140[0] == source[0]);
  check(viewer.background_140[1] == source[1]);
  check(viewer.background_140[2] == source[2]);
  check(viewer.background_140[3] == source[3]);
  check(render_count == 0);
  check(release_count == 0);
}

void test_render_flag_mask_and_identity() {
  reset_fixture();
  OpaqueWorldViewer viewer{};
  const std::uint32_t source[4] = {1u, 2u, 3u, 4u};
  world_viewer_set_background_007c3c20(&viewer, source);
  viewer.camera_170 = reinterpret_cast<void*>(0x5000u);

  check(world_viewer_apply_flags_007c3c50(&viewer, 0xffu) == 0x5au);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x80u) == 0x5au);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x05u) == 0x5au);
  check(render_count == 3);
  check(render_calls[0].camera == viewer.camera_170);
  check(render_calls[0].background == viewer.background_140);
  check(render_calls[0].flags == 0x07u);
  check(render_calls[1].flags == 0x00u);
  check(render_calls[2].flags == 0x05u);
}

void test_render_forwards_null_and_sentinel_without_normalizing() {
  reset_fixture();
  OpaqueWorldViewer viewer{};
  viewer.camera_170 = nullptr;
  check(world_viewer_apply_flags_007c3c50(&viewer, 0xf8u) == 0x5au);
  check(render_count == 1);
  check(render_calls[0].camera == nullptr);
  check(render_calls[0].flags == 0);

  viewer.camera_170 = reinterpret_cast<void*>(0x1u);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x82u) == 0x5au);
  check(render_count == 2);
  check(render_calls[1].camera == reinterpret_cast<void*>(0x1u));
  check(render_calls[1].flags == 0x02u);
}

void test_world_state_write_has_no_container_or_event_mutation() {
  reset_fixture();
  OpaqueWorldViewer viewer{};
  const WorldState before{0xabcdu, 0x11u, 0x22u};
  g_world_state = before;
  const std::uint32_t source[4] = {5u, 6u, 7u, 8u};
  world_viewer_set_background_007c3c20(&viewer, source);
  check(g_world_state.active_object == before.active_object);
  check(g_world_state.flags_8a38 == before.flags_8a38);
  check(g_world_state.flags_9110 == before.flags_9110);
  check(release_count == 0);
  check(render_count == 0);
}

}

int main() {
  test_clear_active_state_order_and_reset();
  test_clear_inactive_state_still_releases();
  test_clear_null_fields_returns_without_releases();
  test_background_copy_preserves_all_words();
  test_render_flag_mask_and_identity();
  test_render_forwards_null_and_sentinel_without_normalizing();
  test_world_state_write_has_no_container_or_event_mutation();
  return failures == 0 ? 0 : 1;
}
