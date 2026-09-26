#include "004c49e0_pick.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// 0x004c49e0: 55 8b ec 83 ec 10 89 4d f4 8b 45 08 89 45 f0 83 7d f0 00
//             74 08 83 7d f0 01 74 12 eb 1e 8b 4d f4 8b 51 18 89 55 fc
//             8b 45 fc eb 12 eb 0e 8b 45 f4 8b 48 1c 89 4d f8 8b 45 f8
//             eb 02 33 c0 8b e5 5d c2 04 00
//
// The original spills `this` and the index into EBP-relative slots, compares the
// index against 0 and 1 in that order, and returns the selected pointer. The
// three JZ/JMP edges give exactly: index==0 -> load +0x18; index==1 -> load
// +0x1c; otherwise fall into the XOR EAX,EAX that yields 0. The reconstruction
// keeps the comparison order and the polarity and drops the redundant spills.
extern "C" __attribute__((thiscall)) void* FUN_004c49e0_SelectSlotByIndex(OpaqueTwoSlotOwner* self,
                                               std::uint32_t index) {
    if (index == 0u) {
        return self->slot_018;
    }
    if (index == 1u) {
        return self->slot_01c;
    }
    return nullptr;
}

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
