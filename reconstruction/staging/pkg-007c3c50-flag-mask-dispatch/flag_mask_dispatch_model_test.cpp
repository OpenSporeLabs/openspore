#include <cstddef>
#include <cstdint>

#include "flag_mask_dispatch.hpp"

namespace {

#if defined(_MSC_VER)
#define FLAGMASK_THISCALL __thiscall
#else
#define FLAGMASK_THISCALL __attribute__((thiscall))
#endif

using openspore::reconstruction::pkg_007c3c50_flag_mask_dispatch::
    OpaqueWorldViewer;
using openspore::reconstruction::pkg_007c3c50_flag_mask_dispatch::
    set_dispatch_port;
using openspore::reconstruction::pkg_007c3c50_flag_mask_dispatch::
    world_viewer_apply_flags_007c3c50;

int failures = 0;

void check(bool value) {
  if (!value) {
    ++failures;
  }
}

constexpr std::uint32_t kBackgroundWords[4] = {0x01020304u, 0x11121314u,
                                               0x21222324u, 0x31323334u};
constexpr std::uint8_t kPortResult = 0x5au;

void* kCamera() {
  return reinterpret_cast<void*>(0x00c0ffeeu);
}

struct DispatchCall {
  void* camera;
  const std::uint32_t* background;
  std::uint8_t flags;
};

DispatchCall calls[512];
std::size_t call_count = 0;

std::uint8_t FLAGMASK_THISCALL recording_dispatch(void* camera,
                                                  const std::uint32_t* background,
                                                  std::uint8_t flags) {
  if (call_count < 512) {
    calls[call_count++] = DispatchCall{camera, background, flags};
  }
  return kPortResult;
}

void reset_fixture() {
  call_count = 0;
  set_dispatch_port(recording_dispatch);
}

OpaqueWorldViewer make_viewer() {
  OpaqueWorldViewer viewer{};
  for (std::size_t i = 0; i < 4; ++i) {
    viewer.background_140[i] = kBackgroundWords[i];
  }
  viewer.camera_170 = kCamera();
  return viewer;
}

// The three TEST immediates are 1, 2 and 4, so exactly flags & 0x07 survive.
// Bits 0x08 and above are tested by nothing and must be dropped.
void test_exhaustive_mask_is_and_0x07() {
  reset_fixture();
  OpaqueWorldViewer viewer = make_viewer();

  for (unsigned flags = 0; flags <= 0xffu; ++flags) {
    check(world_viewer_apply_flags_007c3c50(&viewer,
                                            static_cast<std::uint8_t>(flags)) ==
          kPortResult);
  }

  check(call_count == 256);
  for (unsigned flags = 0; flags <= 0xffu; ++flags) {
    check(calls[flags].flags == static_cast<std::uint8_t>(flags & 0x07u));
  }
}

void test_each_bit_maps_to_itself() {
  reset_fixture();
  OpaqueWorldViewer viewer = make_viewer();

  check(world_viewer_apply_flags_007c3c50(&viewer, 0x00u) == kPortResult);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x01u) == kPortResult);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x02u) == kPortResult);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x04u) == kPortResult);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x03u) == kPortResult);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x06u) == kPortResult);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x07u) == kPortResult);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x05u) == kPortResult);

  check(call_count == 8);
  const std::uint8_t expected[8] = {0x00u, 0x01u, 0x02u, 0x04u,
                                    0x03u, 0x06u, 0x07u, 0x05u};
  for (std::size_t i = 0; i < 8; ++i) {
    check(calls[i].flags == expected[i]);
  }
}

// [ECX+0x170] moves to ECX and [ECX+0x140] is passed as the second argument,
// on every one of the 256 inputs and independent of the mask value.
void test_receiver_fields_forwarded_unconditionally() {
  reset_fixture();
  OpaqueWorldViewer viewer = make_viewer();

  for (unsigned flags = 0; flags <= 0xffu; ++flags) {
    check(world_viewer_apply_flags_007c3c50(&viewer,
                                            static_cast<std::uint8_t>(flags)) ==
          kPortResult);
  }

  for (std::size_t i = 0; i < call_count; ++i) {
    check(calls[i].camera == kCamera());
    check(calls[i].background == viewer.background_140);
  }
}

// The call site is not guarded, so a null camera is forwarded rather than
// checked. The target performs no read of its own through the field.
void test_null_camera_is_forwarded_not_checked() {
  reset_fixture();
  OpaqueWorldViewer viewer = make_viewer();
  viewer.camera_170 = nullptr;

  check(world_viewer_apply_flags_007c3c50(&viewer, 0xf8u) == kPortResult);
  check(call_count == 1);
  check(calls[0].camera == nullptr);
  check(calls[0].flags == 0x00u);
}

// "MOV EAX,1" on the bit-0 path rather than an OR: a fresh accumulator, so
// the high bits of EAX can never leak into the argument.
void test_accumulator_starts_clean() {
  reset_fixture();
  OpaqueWorldViewer viewer = make_viewer();

  check(world_viewer_apply_flags_007c3c50(&viewer, 0x04u) == kPortResult);
  check(calls[0].flags == 0x04u);
  check(world_viewer_apply_flags_007c3c50(&viewer, 0xfcu) == kPortResult);
  check(calls[1].flags == 0x04u);
}

// The target's own bytes touch no global and write nothing through the
// receiver; the background block handed to the port is unchanged afterwards.
void test_no_side_effects_on_receiver_or_background() {
  reset_fixture();
  OpaqueWorldViewer viewer = make_viewer();
  const OpaqueWorldViewer before = viewer;

  check(world_viewer_apply_flags_007c3c50(&viewer, 0xffu) == kPortResult);

  check(viewer.camera_170 == before.camera_170);
  for (std::size_t i = 0; i < 4; ++i) {
    check(viewer.background_140[i] == before.background_140[i]);
  }
}

// A null port must not be dereferenced: the seam falls back to a stub.
void test_null_port_falls_back_to_stub() {
  set_dispatch_port(nullptr);
  OpaqueWorldViewer viewer = make_viewer();
  check(world_viewer_apply_flags_007c3c50(&viewer, 0x03u) == 0);
  reset_fixture();
}

}

int main() {
  test_exhaustive_mask_is_and_0x07();
  test_each_bit_maps_to_itself();
  test_receiver_fields_forwarded_unconditionally();
  test_null_camera_is_forwarded_not_checked();
  test_accumulator_starts_clean();
  test_no_side_effects_on_receiver_or_background();
  test_null_port_falls_back_to_stub();
  return failures == 0 ? 0 : 1;
}