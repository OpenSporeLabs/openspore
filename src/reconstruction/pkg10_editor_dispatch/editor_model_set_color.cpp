#include "editor_model_set_color.hpp"

namespace openspore::reconstruction::pkg10_editor_dispatch {

#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__))
__attribute__((naked)) void __thiscall editor_model_set_color_raw(
    OpaqueEditorModel*) {
  __asm__(
      "pushl %ebp\n\t"
      "movl %esp, %ebp\n\t"
      "pushl %ecx\n\t"
      "movl %ecx, -4(%ebp)\n\t"
      "movl %ebp, %esp\n\t"
      "popl %ebp\n\t"
      "ret\n\t");
}
#else
void __thiscall editor_model_set_color_raw(OpaqueEditorModel*) {}
#endif

void __thiscall editor_model_set_color(OpaqueEditorModel* model, int,
                                       EditorModelColor) {
  editor_model_set_color_raw(model);
}

}
