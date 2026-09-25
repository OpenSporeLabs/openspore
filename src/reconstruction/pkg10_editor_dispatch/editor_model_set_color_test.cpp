#include "editor_model_set_color.hpp"

namespace openspore::reconstruction::pkg10_editor_dispatch {

struct TestEditorModel {
  unsigned char bytes[0xe0];
};

static_assert(sizeof(TestEditorModel) == 0xe0);
static_assert(__builtin_offsetof(EditorModelColor, red) == 0);
static_assert(__builtin_offsetof(EditorModelColor, green) == 4);
static_assert(__builtin_offsetof(EditorModelColor, blue) == 8);

bool same_bytes(const unsigned char* left, const unsigned char* right) {
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    if (left[offset] != right[offset]) {
      return false;
    }
  }
  return true;
}

bool raw_unchanged(OpaqueEditorModel* model) {
  unsigned char before[0xe0];
  unsigned char after[0xe0];
  auto* bytes = reinterpret_cast<unsigned char*>(model);
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    before[offset] = bytes[offset];
  }
  editor_model_set_color_raw(model);
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    after[offset] = bytes[offset];
  }
  return same_bytes(before, after);
}

bool formal_unchanged(EditorModelSetColorTargetAbi target,
                      OpaqueEditorModel* model, int index,
                      EditorModelColor color) {
  unsigned char before[0xe0];
  unsigned char after[0xe0];
  auto* bytes = reinterpret_cast<unsigned char*>(model);
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    before[offset] = bytes[offset];
  }
  target(model, index, color);
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    after[offset] = bytes[offset];
  }
  return same_bytes(before, after);
}

bool run() {
  const EditorModelColor color{-1.0f, 0.5f, 1.0f};
  const EditorModelSetColorTargetAbi formal_target = editor_model_set_color;

  editor_model_set_color_raw(nullptr);
  editor_model_set_color_raw(reinterpret_cast<OpaqueEditorModel*>(1u));
  formal_target(nullptr, 0, color);
  formal_target(reinterpret_cast<OpaqueEditorModel*>(1u), -1, color);

  TestEditorModel model;
  for (unsigned int offset = 0; offset < 0xe0; ++offset) {
    model.bytes[offset] = static_cast<unsigned char>(offset * 37u + 11u);
  }
  model.bytes[0xa4] = 0x21;
  model.bytes[0xa5] = 0x43;
  model.bytes[0xa6] = 0x65;
  model.bytes[0xa7] = 0x87;

  auto* raw = reinterpret_cast<OpaqueEditorModel*>(&model);
  auto* formal = reinterpret_cast<OpaqueEditorModel*>(&model);
  if (!raw_unchanged(raw)) {
    return false;
  }
  if (!formal_unchanged(formal_target, formal, -1, color)) {
    return false;
  }
  if (!formal_unchanged(formal_target, formal, 0, color)) {
    return false;
  }
  if (!formal_unchanged(formal_target, formal, 2, color)) {
    return false;
  }
  if (!formal_unchanged(formal_target, formal, 3, color)) {
    return false;
  }
  if (!formal_unchanged(formal_target, formal, -2147483647 - 1, color)) {
    return false;
  }
  return formal_unchanged(formal_target, formal, 2147483647, color);
}

}

__asm__(".globl __fltused\n__fltused: .long 0");

int main() {
  return openspore::reconstruction::pkg10_editor_dispatch::run() ? 0 : 1;
}
