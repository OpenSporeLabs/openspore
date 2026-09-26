// 0x00b8dad0 — SimCore_00b8dad0_spice_gen_key_ptr
//
// Body read live, 2 instructions, 7 bytes, no callees:
//
//   00b8dad0  8D 81 98 01 00 00  LEA EAX,[ECX + 0x198]
//   00b8dad6  C3                 RET
//
// The address is formed, not loaded, so the block at +0x198 is a member of the
// receiver and not a pointer the receiver owns. Sibling evidence in the same
// accessor cluster bounds the block at three dwords:
//   0x00b8dae0  *(this+0x198)=arg[0]; *(this+0x19C)=arg[1]; *(this+0x1A0)=arg[2]
// and 0x00ba61b0 allocates 0x1B0 bytes for the object and passes the literal
// "Simulator/cPlanetRecord" to the allocator. Spore-ModAPI declares
// Simulator::cPlanetRecord::mSpiceGen as a ResourceKey at +0x198 and
// ResourceKey as three uint32 (Spore ModAPI/Spore/ResourceKey.h), and declares
// +0x184 mKey, +0x188 field_188, +0x194 mTechLevel, +0x1A4 mGeneratedTerrainKey
// around it (Spore ModAPI/Spore/Simulator/cPlanetRecord.h). Six consecutive
// offsets in that one header agree with offsets this binary reads.
//
// The SDK name for this accessor is a CANDIDATE. The header declares
// GetGeneratedTerrainKey() for the +0x1A4 sibling and declares mSpiceGen at
// +0x198 with no accessor, so no SDK method name is claimed for this address.

#include "wave13_w1_core_b08.hpp"

namespace openspore {
namespace wave13_w1_core_b08 {

extern "C" ResourceKey3* SimCore_00b8dad0_spice_gen_key_ptr(OpaqueCPlanetRecord* self);

extern "C" ResourceKey3* SimCore_00b8dad0_spice_gen_key_ptr(OpaqueCPlanetRecord* self) {
    // LEA EAX,[ECX + 0x198] ; RET
    return reinterpret_cast<ResourceKey3*>(reinterpret_cast<std::uint8_t*>(self) + 0x198);
}

}  // namespace wave13_w1_core_b08
}  // namespace openspore
