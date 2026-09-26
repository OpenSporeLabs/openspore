#include "004ad450_related_pointer_getter.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

extern "C" void* __attribute__((thiscall)) FUN_004ad450_get_related(
    const RelatedPointerOwner_004ad450* self) {
    // 0x004ad45c: MOV ECX,[EAX+0x30], round-tripped through [EBP-4] and read
    // back at 0x004ad462. The round trip is a register-allocation artefact and
    // has no effect: the single load is the whole contract. No null check, so
    // a receiver whose field is null yields null rather than faulting here -
    // the callers at 0x004a6c3f and 0x004a6c5b pass the result straight on
    // without testing it.
    return self->related;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
