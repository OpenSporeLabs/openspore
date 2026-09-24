#include "editor_model_set_color.hpp"

namespace openspore::reconstruction::pkg10_editor_dispatch {

struct TestEditorModel {
  unsigned char bytes[0xe0];
};

static_assert(sizeof(TestEditorModel) == 0xe0);
static_assert(__builtin_offsetof(EditorModelColor, red) == 0);
static_assert(__builtin_offsetof(EditorModelColor, green) == 4);
static_assert(__builtin_offsetof(EditorModelColor, blue) == 8);

bool unchanged(OpaqueEditorModel *model) {
  unsigned char before[0xe0];
  unsigned char after[0xe0];
  auto *bytes = reinterpret_cast<unsigned char *>(model);
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    before[offset] = bytes[offset];
  }
  editor_model_set_color(model);
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
  editor_model_set_color(nullptr);
  auto *near_null = reinterpret_cast<OpaqueEditorModel *>(1u);
  editor_model_set_color(near_null);

  TestEditorModel model;
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    model.bytes[offset] = static_cast<unsigned char>(offset * 37u + 11u);
  }
  model.bytes[0xa4] = 0x21;
  model.bytes[0xa5] = 0x43;
  model.bytes[0xa6] = 0x65;
  model.bytes[0xa7] = 0x87;
  return unchanged(reinterpret_cast<OpaqueEditorModel *>(&model));
}

}

int main() {
  return openspore::reconstruction::pkg10_editor_dispatch::run() ? 0 : 1;
}
