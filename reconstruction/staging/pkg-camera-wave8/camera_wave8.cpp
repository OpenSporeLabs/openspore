#include "camera_wave8.hpp"

#include <cstdint>

#if defined(_MSC_VER)
#define PKG_CAMERA_WAVE8_CDECL __cdecl
#define PKG_CAMERA_WAVE8_THISCALL __thiscall
#else
#define PKG_CAMERA_WAVE8_CDECL __attribute__((cdecl))
#define PKG_CAMERA_WAVE8_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_camera_wave8 {

EditorCameraPorts g_editor_camera_ports{};

namespace {

OpaqueEditorCamera *cast_object_00b18460(OpaqueEditorCamera *camera,
                                         OpaqueWord type) {
  if (type == kObjectType0 || type == kObjectType1 || type == kObjectType2) {
    return camera;
  }
  return nullptr;
}

OpaqueEditorCamera *cast_base_camera_00c44990(OpaqueEditorCamera *camera,
                                              OpaqueWord type) {
  if (type == kBaseCameraType) {
    return camera;
  }
  return cast_object_00b18460(camera, type);
}

OpaqueEditorCamera *
destroy_primary_005a2ed0(OpaqueEditorCamera *camera,
                         OpaqueWord deleting_destructor_flag) {
  camera->primary_vtable_000 =
      reinterpret_cast<OpaqueEditorCameraPrimaryVTable *>(
          kCompletePrimaryVtable);
  camera->secondary_vtable_004 =
      reinterpret_cast<OpaqueEditorCameraSecondaryVTable *>(
          kCompleteSecondaryVtable);
  camera->tertiary_vtable_008 =
      reinterpret_cast<OpaqueEditorCameraTertiaryVTable *>(
          kCompleteTertiaryVtable);

  if (camera->property_list_010 != nullptr) {
    camera->property_list_010->vtable->deleting_destructor_04(
        camera->property_list_010);
  }

  camera->tertiary_vtable_008 =
      reinterpret_cast<OpaqueEditorCameraTertiaryVTable *>(kBaseTertiaryVtable);
  camera->secondary_vtable_004 =
      reinterpret_cast<OpaqueEditorCameraSecondaryVTable *>(
          kBaseSecondaryVtable);
  camera->primary_vtable_000 =
      reinterpret_cast<OpaqueEditorCameraPrimaryVTable *>(kBasePrimaryVtable);

  if ((deleting_destructor_flag & 1u) != 0u) {
    g_editor_camera_ports.delete_object(camera);
  }
  return camera;
}

}

extern "C" OpaqueEditorCamera *PKG_CAMERA_WAVE8_THISCALL
editor_camera_on_exit_00c2e640(OpaqueEditorCamera *camera, OpaqueWord type) {
  if (type == kOnExitType0 || type == kOnExitType1) {
    return camera;
  }
  return cast_base_camera_00c44990(camera, type);
}

extern "C" OpaqueEditorCamera *PKG_CAMERA_WAVE8_THISCALL
editor_camera_func24h_005a2050(OpaqueEditorCamera *camera, OpaqueWord type) {
  return type == kFunc24hType ? camera : nullptr;
}

extern "C" OpaqueEditorCamera *PKG_CAMERA_WAVE8_THISCALL
editor_camera_func54h_005a2320(OpaqueEditorCameraSecondary *secondary,
                               OpaqueWord deleting_destructor_flag) {
  auto *camera = reinterpret_cast<OpaqueEditorCamera *>(
      reinterpret_cast<std::uint8_t *>(secondary) - 4u);
  return destroy_primary_005a2ed0(camera, deleting_destructor_flag);
}

}

#undef PKG_CAMERA_WAVE8_CDECL
#undef PKG_CAMERA_WAVE8_THISCALL
