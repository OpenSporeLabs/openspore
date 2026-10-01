#include "beam_tool_func4ch.hpp"

#if defined(_MSC_VER)
#define PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL __thiscall
#define PKG_SIM_BEAMTOOL_FUNC4CH_CDECL __cdecl
#else
#define PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL __attribute__((thiscall))
#define PKG_SIM_BEAMTOOL_FUNC4CH_CDECL __attribute__((cdecl))
#endif

#define PKG_SIM_BEAMTOOL_FUNC4CH_NAKED __attribute__((naked))

namespace openspore::reconstruction::pkg_sim_beamtool_func4ch {

NativePorts g_beam_tool_func4ch_ports{};
OpaqueRelationshipState* g_relationship_state_0167eb14 = nullptr;

extern "C" void PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL
beam_target_mark_00cb3c70(OpaqueBeamTarget* beam_target) {
  beam_target->state_155 = 1u;
}

extern "C" bool PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL
beam_tool_gate_0104cd50(OpaqueBeamToolState* tool_state) {
  return ((tool_state->gate_174 >> 4U) & 1U) != 0U;
}

extern "C" OpaqueRelationshipState* relationship_get_00b3d3c0() {
  return g_relationship_state_0167eb14;
}

extern "C" void PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL
relationship_state_reset_00b78860(OpaqueRelationshipState* relationship) {
  relationship->state_20 &= kRelationshipStateClearMask;
  relationship->event_55a0 = 0U;
  const RelationshipEventDrain drain =
      g_beam_tool_func4ch_ports.relationship_event_drain_00b77aa0;
  drain(relationship);
}

extern "C" bool PKG_SIM_BEAMTOOL_FUNC4CH_NAKED PKG_SIM_BEAMTOOL_FUNC4CH_CDECL
func4_ch_01053db0(OpaqueBeamToolState* tool_state) {
  __asm__ volatile(
      "pushl %esi\n\t"
      "movl 0x4(%esp), %esi\n\t"
      "movl 0x124(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 2f\n\t"
      "call beam_target_mark_00cb3c70\n\t"
      "movl 0x124(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 2f\n\t"
      "movl $0x0, 0x124(%esi)\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "call *%edx\n\t"
      "2:\n\t"
      "movl %esi, %ecx\n\t"
      "call beam_tool_gate_0104cd50\n\t"
      "popl %esi\n\t"
      "testb %al, %al\n\t"
      "jz 3f\n\t"
      "call relationship_get_00b3d3c0\n\t"
      "movl %eax, %ecx\n\t"
      "call relationship_state_reset_00b78860\n\t"
      "3:\n\t"
      "movb $0x1, %al\n\t"
      "ret $0x4\n\t");
}

bool beam_tool_func4_ch_model(OpaqueBeamToolState* tool_state) {
  OpaqueBeamTarget* beam_target = tool_state->owned_beam_target_124;
  if (beam_target != nullptr) {
    beam_target_mark_00cb3c70(beam_target);
    beam_target = tool_state->owned_beam_target_124;
    if (beam_target != nullptr) {
      tool_state->owned_beam_target_124 = nullptr;
      beam_target->vtable_00->release_04(beam_target);
    }
  }
  if (beam_tool_gate_0104cd50(tool_state)) {
    OpaqueRelationshipState* const relationship = relationship_get_00b3d3c0();
    relationship_state_reset_00b78860(relationship);
  }
  return true;
}

}

#undef PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL
#undef PKG_SIM_BEAMTOOL_FUNC4CH_CDECL
#undef PKG_SIM_BEAMTOOL_FUNC4CH_NAKED
