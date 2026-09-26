// wave13-w1-core-b08 — declarations of the six reconstructed symbols.
//
// Each symbol name embeds the 8-hex VA of the original function so the tooling
// can locate the body. Signatures below are the observed ABIs.

#ifndef OPENSPORE_WAVE13_W1_CORE_B08_RECONSTRUCTED_HPP
#define OPENSPORE_WAVE13_W1_CORE_B08_RECONSTRUCTED_HPP

#include "wave13_w1_core_b08.hpp"

namespace openspore {
namespace wave13_w1_core_b08 {

// 0x00c0b780 — 19 bytes, 0 callees. __thiscall, receiver in ECX, full-dword
// 0/1 in EAX, bare RET, no stack arguments, no saved registers.
extern "C" std::uint32_t SimCore_00c0b780_sub_object_flag_608(OpaqueC0b780Owner* self);

// 0x00b8dad0 — 7 bytes, 0 callees. __thiscall, receiver in ECX, pointer in
// EAX, bare RET, no stack arguments, no saved registers.
extern "C" ResourceKey3* SimCore_00b8dad0_spice_gen_key_ptr(OpaqueCPlanetRecord* self);

// 0x00c47180 — 51 bytes, 2 callees, 1 virtual call at slot +0xC0.
// __thiscall with one (dead) stack word; RET 0x4 so the callee pops it.
extern "C" void SimCore_00c47180_manager_slot_replace(OpaqueC47180Owner* self, std::uint32_t unused_arg);

// 0x00ba61b0 — 116 bytes, 5 callees, 1 virtual call at slot +0x00. cdecl: the
// body ends in a bare RET after ADD ESP,0xC, so the caller owns cleanup.
extern "C" void SimCore_00ba61b0_make_planet_record(std::uint32_t planet_id, OpaqueCPlanetRecord** out_record);

// 0x00c0ce80 — 204 bytes, 4 callees, 1 virtual call at slot +0x58.
// __thiscall with two stack words; RET 0x8 so the callee pops them. The first
// word is tested as an integer and simultaneously reinterpreted as a float.
extern "C" float SimCore_00c0ce80_tier_value_lookup(OpaqueC0ce80Tiers* self, std::uint32_t tier,
                                         std::uint32_t use_base_offset);

// 0x00ae9f50 — 535 bytes, 23 callees, 1 virtual call at slot +0x20 of a foreign
// object plus 2 through App::IAppSystem slot +0x14. __thiscall, no stack
// arguments, 0x80-byte frame, bare RET.
extern "C" void SimCore_00ae9f50_session_boot_register(OpaqueAe9f50Session* self);

}  // namespace wave13_w1_core_b8
}  // namespace openspore

#endif  // OPENSPORE_WAVE13_W1_CORE_B08_RECONSTRUCTED_HPP
