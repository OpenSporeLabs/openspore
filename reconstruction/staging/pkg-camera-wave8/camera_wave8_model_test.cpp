#include <cstddef>
#include <cstdint>
#include <cstring>

#include "camera_wave8.hpp"

#if defined(_MSC_VER)
#define PKG_TEST_CDECL __cdecl
#define PKG_TEST_THISCALL __thiscall
#else
#define PKG_TEST_CDECL __attribute__((cdecl))
#define PKG_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::pkg_camera_wave8;

enum class Step : std::uint8_t {
  kNone,
  kPropertyDestroy,
  kDeleteObject,
};

struct ManagerState {
  OpaqueEditorCamera *active_camera = nullptr;
  OpaqueEditorCamera *pending_camera = nullptr;
  OpaqueViewer *viewer = nullptr;
  std::int32_t active_index = 0;
  OpaqueWord transition_generation = 0;
};

struct Fixture {
  OpaqueEditorCamera camera{};
  OpaqueEditorCameraPrimaryVTable primary_vtable{};
  OpaqueEditorCameraSecondaryVTable secondary_vtable{};
  OpaqueEditorCameraTertiaryVTable tertiary_vtable{};
  OpaqueEditorCameraOnExitVTable on_exit_vtable{};
  OpaquePropertyList property_list{};
  OpaquePropertyListVTable property_vtable{};
  std::uint8_t viewer_storage[4]{};
  ManagerState manager{};
  Step trace[2]{Step::kNone, Step::kNone};
  std::size_t trace_count = 0;
  std::size_t property_destroy_calls = 0;
  std::size_t delete_calls = 0;
};

Fixture *current_fixture = nullptr;
std::size_t failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void append_step(Step step) {
  Fixture &fixture = *current_fixture;
  if (fixture.trace_count < 2) {
    fixture.trace[fixture.trace_count] = step;
  }
  ++fixture.trace_count;
}

void PKG_TEST_THISCALL destroy_property_list(OpaquePropertyList *property) {
  Fixture &fixture = *current_fixture;
  check(property == &fixture.property_list);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.primary_vtable_000) ==
        kCompletePrimaryVtable);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.secondary_vtable_004) ==
        kCompleteSecondaryVtable);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.tertiary_vtable_008) ==
        kCompleteTertiaryVtable);
  ++fixture.property_destroy_calls;
  append_step(Step::kPropertyDestroy);
}

void PKG_TEST_CDECL delete_object(void *object) {
  Fixture &fixture = *current_fixture;
  check(object == &fixture.camera);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.primary_vtable_000) ==
        kBasePrimaryVtable);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.secondary_vtable_004) ==
        kBaseSecondaryVtable);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.tertiary_vtable_008) ==
        kBaseTertiaryVtable);
  ++fixture.delete_calls;
  append_step(Step::kDeleteObject);
}

void initialize(Fixture &fixture) {
  fixture = Fixture{};
  current_fixture = &fixture;

  fixture.primary_vtable.func24h_0c = editor_camera_func24h_005a2050;
  fixture.secondary_vtable.deleting_destructor_00 =
      editor_camera_func54h_005a2320;
  fixture.on_exit_vtable.on_exit_0c = editor_camera_on_exit_00c2e640;
  fixture.property_vtable.deleting_destructor_04 = destroy_property_list;

  fixture.camera.primary_vtable_000 = &fixture.primary_vtable;
  fixture.camera.secondary_vtable_004 = &fixture.secondary_vtable;
  fixture.camera.tertiary_vtable_008 = &fixture.tertiary_vtable;
  fixture.camera.reference_count_00c = 7;
  fixture.camera.property_list_010 = &fixture.property_list;
  fixture.camera.zoom_scale_014 = 1.25F;
  fixture.camera.translate_scale_018 = 2.5F;
  fixture.camera.rotate_scale_01c = 3.75F;
  fixture.camera.heading_044 = 4.5F;
  fixture.camera.pitch_048 = 5.25F;
  fixture.camera.current_zoom_04c = 6.5F;
  fixture.camera.camera_position_074 = OpaqueVector3{7.5F, 8.25F, 9.75F};
  fixture.camera.alternate_position_080 = OpaqueVector3{10.5F, 11.25F, 12.75F};
  fixture.camera.input_a0[0] = 13u;
  fixture.camera.input_a0[0x47] = 14u;
  fixture.camera.viewer_e8 =
      reinterpret_cast<OpaqueViewer *>(fixture.viewer_storage);

  fixture.property_list.vtable = &fixture.property_vtable;
  fixture.manager.active_camera = &fixture.camera;
  fixture.manager.pending_camera = &fixture.camera;
  fixture.manager.viewer =
      reinterpret_cast<OpaqueViewer *>(fixture.viewer_storage);
  fixture.manager.active_index = 3;
  fixture.manager.transition_generation = 19u;

  g_editor_camera_ports.delete_object = delete_object;
}

void finish() {
  g_editor_camera_ports = EditorCameraPorts{};
  current_fixture = nullptr;
}

void check_manager_unchanged(const Fixture &fixture,
                             const ManagerState &before) {
  check(fixture.manager.active_camera == before.active_camera);
  check(fixture.manager.pending_camera == before.pending_camera);
  check(fixture.manager.viewer == before.viewer);
  check(fixture.manager.active_index == before.active_index);
  check(fixture.manager.transition_generation == before.transition_generation);
}

void check_camera_unchanged(const OpaqueEditorCamera &actual,
                            const OpaqueEditorCamera &before) {
  check(std::memcmp(&actual, &before, sizeof(OpaqueEditorCamera)) == 0);
}

void check_camera_state_unchanged(const OpaqueEditorCamera &actual,
                                  const OpaqueEditorCamera &before) {
  check(actual.reference_count_00c == before.reference_count_00c);
  check(actual.property_list_010 == before.property_list_010);
  check(std::memcmp(&actual.reference_count_00c, &before.reference_count_00c,
                    sizeof(OpaqueEditorCamera) - 0x0c) == 0);
}

void test_on_exit_type_chain() {
  struct TypeCase {
    OpaqueWord type;
    bool accepted;
  };
  const TypeCase cases[] = {
      {kOnExitType0, true},  {kOnExitType1, true}, {kBaseCameraType, true},
      {kObjectType0, true},  {kObjectType1, true}, {kObjectType2, true},
      {kFunc24hType, false}, {0u, false},          {0xffffffffu, false},
  };

  for (const TypeCase &item : cases) {
    Fixture fixture{};
    initialize(fixture);
    const OpaqueEditorCamera before = fixture.camera;
    const ManagerState manager_before = fixture.manager;
    OpaqueEditorCamera *result =
        fixture.on_exit_vtable.on_exit_0c(&fixture.camera, item.type);
    check(result == (item.accepted ? &fixture.camera : nullptr));
    check_camera_unchanged(fixture.camera, before);
    check_manager_unchanged(fixture, manager_before);
    check(fixture.trace_count == 0);
    finish();
  }
}

void test_func24h_return_gate() {
  struct TypeCase {
    OpaqueWord type;
    bool accepted;
  };
  const TypeCase cases[] = {
      {kFunc24hType, true},
      {0u, false},
      {0xffffffffu, false},
      {kOnExitType0, false},
  };

  for (const TypeCase &item : cases) {
    Fixture fixture{};
    initialize(fixture);
    const OpaqueEditorCamera before = fixture.camera;
    const ManagerState manager_before = fixture.manager;
    OpaqueEditorCamera *result =
        fixture.primary_vtable.func24h_0c(&fixture.camera, item.type);
    check(result == (item.accepted ? &fixture.camera : nullptr));
    check_camera_unchanged(fixture.camera, before);
    check_manager_unchanged(fixture, manager_before);
    check(fixture.trace_count == 0);
    finish();
  }
}

OpaqueEditorCameraSecondary *secondary_base(OpaqueEditorCamera &camera) {
  return reinterpret_cast<OpaqueEditorCameraSecondary *>(
      &camera.secondary_vtable_004);
}

void test_func54h_teardown_order() {
  Fixture fixture{};
  initialize(fixture);
  const OpaqueEditorCamera before = fixture.camera;
  const ManagerState manager_before = fixture.manager;

  OpaqueEditorCamera *result = fixture.secondary_vtable.deleting_destructor_00(
      secondary_base(fixture.camera), 0u);

  check(result == &fixture.camera);
  check(fixture.property_destroy_calls == 1);
  check(fixture.delete_calls == 0);
  check(fixture.trace_count == 1);
  check(fixture.trace[0] == Step::kPropertyDestroy);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.primary_vtable_000) ==
        kBasePrimaryVtable);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.secondary_vtable_004) ==
        kBaseSecondaryVtable);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.tertiary_vtable_008) ==
        kBaseTertiaryVtable);
  check_camera_state_unchanged(fixture.camera, before);
  check_manager_unchanged(fixture, manager_before);
  finish();
}

void test_func54h_deleting_flag() {
  Fixture fixture{};
  initialize(fixture);
  const OpaqueEditorCamera before = fixture.camera;
  const ManagerState manager_before = fixture.manager;

  OpaqueEditorCamera *result = fixture.secondary_vtable.deleting_destructor_00(
      secondary_base(fixture.camera), 1u);

  check(result == &fixture.camera);
  check(fixture.property_destroy_calls == 1);
  check(fixture.delete_calls == 1);
  check(fixture.trace_count == 2);
  check(fixture.trace[0] == Step::kPropertyDestroy);
  check(fixture.trace[1] == Step::kDeleteObject);
  check_camera_state_unchanged(fixture.camera, before);
  check_manager_unchanged(fixture, manager_before);
  finish();
}

void test_func54h_null_property_and_even_flag() {
  Fixture fixture{};
  initialize(fixture);
  fixture.camera.property_list_010 = nullptr;
  const OpaqueEditorCamera before = fixture.camera;
  const ManagerState manager_before = fixture.manager;

  OpaqueEditorCamera *result = fixture.secondary_vtable.deleting_destructor_00(
      secondary_base(fixture.camera), 2u);

  check(result == &fixture.camera);
  check(fixture.property_destroy_calls == 0);
  check(fixture.delete_calls == 0);
  check(fixture.trace_count == 0);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.primary_vtable_000) ==
        kBasePrimaryVtable);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.secondary_vtable_004) ==
        kBaseSecondaryVtable);
  check(reinterpret_cast<OpaqueWord>(fixture.camera.tertiary_vtable_008) ==
        kBaseTertiaryVtable);
  check_camera_state_unchanged(fixture.camera, before);
  check_manager_unchanged(fixture, manager_before);
  finish();
}

void run() {
  test_on_exit_type_chain();
  test_func24h_return_gate();
  test_func54h_teardown_order();
  test_func54h_deleting_flag();
  test_func54h_null_property_and_even_flag();
}

}

int main() {
  run();
  return failures == 0 ? 0 : 1;
}

#undef PKG_TEST_CDECL
#undef PKG_TEST_THISCALL
