#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-camera-wave8 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_CAMERA_WAVE8_CDECL __cdecl
#define PKG_CAMERA_WAVE8_THISCALL __thiscall
#else
#define PKG_CAMERA_WAVE8_CDECL __attribute__((cdecl))
#define PKG_CAMERA_WAVE8_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_camera_wave8 {

static_assert(sizeof(void *) == 4, "pkg-camera-wave8 requires 32-bit pointers");
static_assert(sizeof(float) == 4, "pkg-camera-wave8 requires 32-bit floats");
static_assert(sizeof(bool) == 1, "pkg-camera-wave8 requires one-byte bools");

using OpaqueWord = std::uint32_t;

struct OpaqueEditorCamera;
struct OpaqueEditorCameraSecondary;
struct OpaqueViewer;
struct OpaquePropertyList;

using EditorCameraOnExit = OpaqueEditorCamera *(
    PKG_CAMERA_WAVE8_THISCALL *)(OpaqueEditorCamera *, OpaqueWord);
using EditorCameraFunc24h = OpaqueEditorCamera *(
    PKG_CAMERA_WAVE8_THISCALL *)(OpaqueEditorCamera *, OpaqueWord);
using EditorCameraFunc54h = OpaqueEditorCamera *(
    PKG_CAMERA_WAVE8_THISCALL *)(OpaqueEditorCameraSecondary *, OpaqueWord);

struct OpaqueEditorCameraOnExitVTable {
  void *slots_00[3]{};
  EditorCameraOnExit on_exit_0c = nullptr;
};

struct OpaqueEditorCameraPrimaryVTable {
  void *slots_00[3]{};
  EditorCameraFunc24h func24h_0c = nullptr;
};

struct OpaqueEditorCameraSecondaryVTable {
  EditorCameraFunc54h deleting_destructor_00 = nullptr;
};

struct OpaqueEditorCameraTertiaryVTable {
  void *slot_00 = nullptr;
};

struct OpaquePropertyListVTable {
  void *complete_destructor_00 = nullptr;
  void(PKG_CAMERA_WAVE8_THISCALL *deleting_destructor_04)(
      OpaquePropertyList *) = nullptr;
};

struct OpaquePropertyList {
  OpaquePropertyListVTable *vtable = nullptr;
};

struct OpaqueVector3 {
  float x = 0.0F;
  float y = 0.0F;
  float z = 0.0F;
};

struct OpaqueEditorCamera {
  OpaqueEditorCameraPrimaryVTable *primary_vtable_000 = nullptr;
  OpaqueEditorCameraSecondaryVTable *secondary_vtable_004 = nullptr;
  OpaqueEditorCameraTertiaryVTable *tertiary_vtable_008 = nullptr;
  std::int32_t reference_count_00c = 0;
  OpaquePropertyList *property_list_010 = nullptr;
  float zoom_scale_014 = 0.0F;
  float translate_scale_018 = 0.0F;
  float rotate_scale_01c = 0.0F;
  float field_020 = 0.0F;
  float field_024 = 0.0F;
  float initial_zoom_028 = 0.0F;
  bool field_02c = false;
  std::uint8_t padding_02d[3]{};
  float initial_heading_030 = 0.0F;
  float initial_pitch_034 = 0.0F;
  float zoom_038 = 0.0F;
  float initial_offset_x_03c = 0.0F;
  float initial_offset_y_040 = 0.0F;
  float heading_044 = 0.0F;
  float pitch_048 = 0.0F;
  float current_zoom_04c = 0.0F;
  float current_offset_x_050 = 0.0F;
  float current_offset_y_054 = 0.0F;
  float minimum_zoom_058 = 0.0F;
  float maximum_zoom_05c = 0.0F;
  float minimum_pitch_060 = 0.0F;
  float maximum_pitch_064 = 0.0F;
  float near_clip_068 = 0.0F;
  float far_clip_06c = 0.0F;
  float initial_fov_070 = 0.0F;
  OpaqueVector3 camera_position_074{};
  OpaqueVector3 alternate_position_080{};
  float position_scale_08c = 0.0F;
  bool turntable_style_090 = false;
  std::uint8_t padding_091[3]{};
  float field_094 = 0.0F;
  float field_098 = 0.0F;
  bool current_fov_09c = false;
  std::uint8_t padding_09d[3]{};
  std::uint8_t input_a0[0x48]{};
  OpaqueViewer *viewer_e8 = nullptr;
};

struct OpaqueEditorCameraSecondary {
  OpaqueEditorCameraSecondaryVTable *vtable = nullptr;
};

struct EditorCameraPorts {
  using DeleteObject = void(PKG_CAMERA_WAVE8_CDECL *)(void *);
  DeleteObject delete_object = nullptr;
};

extern EditorCameraPorts g_editor_camera_ports;

extern "C" OpaqueEditorCamera *PKG_CAMERA_WAVE8_THISCALL
editor_camera_on_exit_00c2e640(OpaqueEditorCamera *camera, OpaqueWord type);

extern "C" OpaqueEditorCamera *PKG_CAMERA_WAVE8_THISCALL
editor_camera_func24h_005a2050(OpaqueEditorCamera *camera, OpaqueWord type);

extern "C" OpaqueEditorCamera *PKG_CAMERA_WAVE8_THISCALL
editor_camera_func54h_005a2320(OpaqueEditorCameraSecondary *secondary,
                               OpaqueWord deleting_destructor_flag);

static_assert(offsetof(OpaqueEditorCameraOnExitVTable, on_exit_0c) == 0x0c,
              "OnExit vtable slot offset");
static_assert(offsetof(OpaqueEditorCameraPrimaryVTable, func24h_0c) == 0x0c,
              "func24h vtable slot offset");
static_assert(offsetof(OpaqueEditorCameraSecondaryVTable,
                       deleting_destructor_00) == 0x00,
              "func54h vtable slot offset");
static_assert(offsetof(OpaqueEditorCamera, primary_vtable_000) == 0x00,
              "primary vtable offset");
static_assert(offsetof(OpaqueEditorCamera, secondary_vtable_004) == 0x04,
              "secondary vtable offset");
static_assert(offsetof(OpaqueEditorCamera, tertiary_vtable_008) == 0x08,
              "tertiary vtable offset");
static_assert(offsetof(OpaqueEditorCamera, reference_count_00c) == 0x0c,
              "reference count offset");
static_assert(offsetof(OpaqueEditorCamera, property_list_010) == 0x10,
              "property list offset");
static_assert(offsetof(OpaqueEditorCamera, camera_position_074) == 0x74,
              "camera position offset");
static_assert(offsetof(OpaqueEditorCamera, alternate_position_080) == 0x80,
              "alternate position offset");
static_assert(offsetof(OpaqueEditorCamera, input_a0) == 0xa0,
              "input snapshot offset");
static_assert(offsetof(OpaqueEditorCamera, viewer_e8) == 0xe8, "viewer offset");
static_assert(sizeof(OpaqueEditorCamera) == 0xec,
              "EditorCamera target object size");

inline constexpr OpaqueWord kOnExitType0 = 0x07406a570u;
inline constexpr OpaqueWord kOnExitType1 = 0x14066ce5u;
inline constexpr OpaqueWord kBaseCameraType = 0x034066a80u;
inline constexpr OpaqueWord kObjectType0 = 0xee3f516eu;
inline constexpr OpaqueWord kObjectType1 = 0x0179c807u;
inline constexpr OpaqueWord kObjectType2 = 0x017f243bu;
inline constexpr OpaqueWord kFunc24hType = 0x029da727u;
inline constexpr OpaqueWord kCompletePrimaryVtable = 0x013f69c8u;
inline constexpr OpaqueWord kCompleteSecondaryVtable = 0x013f69b8u;
inline constexpr OpaqueWord kCompleteTertiaryVtable = 0x013f69b4u;
inline constexpr OpaqueWord kBasePrimaryVtable = 0x013eb938u;
inline constexpr OpaqueWord kBaseSecondaryVtable = 0x013eb394u;
inline constexpr OpaqueWord kBaseTertiaryVtable = 0x013ef094u;
inline constexpr OpaqueWord kOnExitVtable = 0x0146b420u;

}

#undef PKG_CAMERA_WAVE8_CDECL
#undef PKG_CAMERA_WAVE8_THISCALL
