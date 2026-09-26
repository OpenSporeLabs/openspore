#include "004adc20_set_flag4f.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// 0x004adc20: 55 8b ec 51 89 4d fc 8b 45 fc 8a 4d 08 88 48 4f 8b e5 5d
//             c2 04 00
//
// 0x004adc2a narrows the incoming dword to CL and 0x004adc2d stores exactly
// that one byte. Bits 8..31 of the caller's stack word are discarded, so a
// caller passing 0x00000101 writes 0x01, not 0x00 and not 0x101.
extern "C" __attribute__((thiscall)) void FUN_004adc20_SetFlag4F(OpaqueEditorBlockSettings* self,
                                       std::uint8_t value) {
    self->flag_04f = value;
}

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
