#include "0043eed0_editor_part_blend_getter.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

extern "C" float __attribute__((thiscall)) FUN_0043eed0_get_blend_value(
    const EditorPart_0043eed0* self) {
    // 0x0043eeda: FLD dword ptr [EAX+0x1D4]. One operand, no store, no
    // arithmetic, so the value is returned in ST(0) and the x87 stack is
    // balanced on exit.
    return self->blend_value;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
