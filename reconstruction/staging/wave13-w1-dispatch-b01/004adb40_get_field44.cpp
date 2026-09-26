#include "004adb40_get_field44.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// 0x004adb40: 55 8b ec 51 89 4d fc 8b 45 fc d9 40 44 8b e5 5d c3
//
// The single FLD at 0x004adb4a is the whole observable body. It is a 4-byte
// memory load, so the returned value is exactly the stored bit pattern widened
// to float; no conversion, no mask, no default for a null receiver.
extern "C" __attribute__((thiscall)) float FUN_004adb40_GetField44(OpaqueEditorBlockSettings* self) {
    return self->field_044;
}

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
