#include "wave13_pilot_core_b01_types.hpp"

// 0x00bbaa60 — 8 instructions, 25 bytes, body span 0x00bbaa60..0x00bbaa78,
// INT3 pad 0x00bbaa79..0x00bbaa7f.
//
//   00bbaa60  PUSH ESI
//   00bbaa61  MOV  ESI,ECX
//   00bbaa63  CALL 0x00bba640               thiscall, no stack argument
//   00bbaa68  MOV  EAX,[ESI+0x84]           vector begin, re-read AFTER the sync
//   00bbaa6e  MOV  ECX,[ESP+0x8]            the index, full 32 bits
//   00bbaa72  MOV  EAX,[EAX+ECX*0x4]        no bounds check
//   00bbaa75  POP  ESI
//   00bbaa76  RET  0x4                      callee pops the one stack word
//
// The sync port's return value is discarded, and the vector base is re-read
// after it, so the sync may reallocate. The index is used as a raw 32-bit
// scale-of-4 offset with no comparison against the vector's end pointer.

namespace openspore::reconstruction::wave13_pilot_core_b01 {

void* StarRecord_00bbaa60_getPlanetRecordByIndex(OpaqueStarRecord* self,
                                                 std::uint32_t index) {
    port_00bba640_sync_planet_vector(self);

    const auto begin = static_cast<void**>(self->field_084.begin);
    return begin[index];
}

}  // namespace openspore::reconstruction::wave13_pilot_core_b01
