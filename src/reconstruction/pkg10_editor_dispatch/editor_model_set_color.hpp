#pragma once

namespace openspore::reconstruction::pkg10_editor_dispatch {

struct OpaqueEditorModel;

struct EditorModelColor {
  float red;
  float green;
  float blue;
};

using EditorModelSetColorTargetAbi = void(__thiscall*)(OpaqueEditorModel*, int,
                                                       EditorModelColor);

static_assert(sizeof(int) == 4, "the formal target index is 32-bit");
static_assert(sizeof(EditorModelColor) == 12,
              "the formal target color is three consecutive floats");
static_assert(sizeof(EditorModelSetColorTargetAbi) == 4,
              "the target ABI stores one 32-bit function pointer");

void __thiscall editor_model_set_color_raw(OpaqueEditorModel*);
void __thiscall editor_model_set_color(OpaqueEditorModel*, int,
                                       EditorModelColor);

}
