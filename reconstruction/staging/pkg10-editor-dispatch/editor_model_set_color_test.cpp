#include "editor_model_set_color.hpp"

namespace openspore::reconstruction::pkg10_editor_dispatch {

struct TestEditorModel {
  unsigned char bytes[0xe0]{};
};

static_assert(__builtin_offsetof(EditorModelColor, red) == 0);
static_assert(__builtin_offsetof(EditorModelColor, green) == 4);
static_assert(__builtin_offsetof(EditorModelColor, blue) == 8);

bool unchanged(OpaqueEditorModel *model, int index, EditorModelColor color) {
  unsigned char before[0xe0]{};
  unsigned char after[0xe0]{};
  auto *bytes = reinterpret_cast<unsigned char *>(model);
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    before[offset] = bytes[offset];
  }
  editor_model_set_color(model, index, color);
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    after[offset] = bytes[offset];
  }
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    if (before[offset] != after[offset]) {
      return false;
    }
  }
  return true;
}

bool run() {
  const EditorModelColor color{-1.0f, 0.5f, 1.0f};
  editor_model_set_color(nullptr, 0, color);

  TestEditorModel model;
  for (unsigned int index = 0; index < 0xe0; ++index) {
    model.bytes[index] = static_cast<unsigned char>(index * 37u + 11u);
  }

  auto *opaque = reinterpret_cast<OpaqueEditorModel *>(&model);
  return unchanged(opaque, -1, color) && unchanged(opaque, 0, color) &&
         unchanged(opaque, 2, color) && unchanged(opaque, 3, color) &&
         unchanged(opaque, -2147483647 - 1, color) &&
         unchanged(opaque, 2147483647, color);
}

} // namespace openspore::reconstruction::pkg10_editor_dispatch

int main() {
  return openspore::reconstruction::pkg10_editor_dispatch::run() ? 0 : 1;
}
