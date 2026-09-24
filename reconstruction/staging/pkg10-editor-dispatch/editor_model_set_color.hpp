#pragma once

namespace openspore::reconstruction::pkg10_editor_dispatch {

struct OpaqueEditorModel;

struct EditorModelColor {
  float red;
  float green;
  float blue;
};

static_assert(sizeof(int) == 4, "the target index is a signed 32-bit word");
static_assert(sizeof(EditorModelColor) == 12,
              "the target color is three consecutive 32-bit floats");

void __thiscall editor_model_set_color(OpaqueEditorModel *, int,
                                       EditorModelColor);

} // namespace openspore::reconstruction::pkg10_editor_dispatch
