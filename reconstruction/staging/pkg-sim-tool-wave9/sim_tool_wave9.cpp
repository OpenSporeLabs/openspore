#include "sim_tool_wave9.hpp"

#if defined(_MSC_VER)
#define PKG_SIM_TOOL_WAVE9_THISCALL __thiscall
#define PKG_SIM_TOOL_WAVE9_CDECL __cdecl
#else
#define PKG_SIM_TOOL_WAVE9_THISCALL __attribute__((thiscall))
#define PKG_SIM_TOOL_WAVE9_CDECL __attribute__((cdecl))
#endif

#define PKG_SIM_TOOL_WAVE9_NAKED __attribute__((naked))

namespace openspore::reconstruction::pkg_sim_tool_wave9 {

NativePorts g_sim_tool_wave9_ports{};
OpaquePositionSource* g_position_source_0167eac4 = nullptr;
OpaqueRelationshipState* g_relationship_state_0167eb14 = nullptr;

extern "C" OpaquePositionSource* position_source_get_00b3d240() {
  return g_position_source_0167eac4;
}

extern "C" void PKG_SIM_TOOL_WAVE9_THISCALL
beam_mark_00cb3c70(OpaqueBeamTarget* target) {
  target->state_155 = 1u;
}

extern "C" bool PKG_SIM_TOOL_WAVE9_THISCALL
beam_gate_0104cd50(OpaqueToolState* state) {
  return ((state->state_174 >> 4U) & 1U) != 0U;
}

extern "C" OpaqueRelationshipState* relationship_get_00b3d3c0() {
  return g_relationship_state_0167eb14;
}

extern "C" OpaquePooledObject* pool_root_get_00883860() {
  return g_sim_tool_wave9_ports.pool_root_00883860();
}

extern "C" const TargetWord* delete_identifier_values_get_01465004() {
  return kDeleteIdentifierValues;
}

extern "C" SpecialSelect special_select_port_get_01053980() {
  return g_sim_tool_wave9_ports.special_select_01053980;
}

extern "C" void PKG_SIM_TOOL_WAVE9_NAKED PKG_SIM_TOOL_WAVE9_THISCALL
target_00b72370(OpaqueDeleteOwner* owner) {
  __asm__ volatile(
      "pushl %ebx\n\t"
      "pushl %esi\n\t"
      "pushl %edi\n\t"
      "pushl %ebp\n\t"
      "movl %ecx, %esi\n\t"
      "call pool_root_get_00883860\n\t"
      "movl %eax, %edi\n\t"
      "call delete_identifier_values_get_01465004\n\t"
      "movl %eax, %ebp\n\t"
      "leal -0x4(%esi), %ebx\n\t"
      "movl %edi, 0x20(%esi)\n\t"
      "movl %ebx, 0x24(%esi)\n\t"
      "movl %ebp, 0x28(%esi)\n\t"
      "movl $0x8, 0x2c(%esi)\n\t"
      "movl $0x0, 0x30(%esi)\n\t"
      "testl %edi, %edi\n\t"
      "jz 1f\n\t"
      "testl %ebx, %ebx\n\t"
      "jz 1f\n\t"
      "xorl %esi, %esi\n\t"
      "2:\n\t"
      "movl (%esi,%ebp), %ecx\n\t"
      "movl (%edi), %eax\n\t"
      "movl 0x24(%eax), %edx\n\t"
      "pushl %ecx\n\t"
      "pushl %ebx\n\t"
      "movl %edi, %ecx\n\t"
      "call *%edx\n\t"
      "addl $0x4, %esi\n\t"
      "cmpl $0x20, %esi\n\t"
      "jb 2b\n\t"
      "1:\n\t"
      "popl %ebp\n\t"
      "popl %edi\n\t"
      "popl %esi\n\t"
      "popl %ebx\n\t"
      "ret\n\t");
}

extern "C" void PKG_SIM_TOOL_WAVE9_NAKED PKG_SIM_TOOL_WAVE9_THISCALL
target_01052f90(OpaqueAoEState*, OpaqueVector*) {
  __asm__ volatile(
      "subl $0xc, %esp\n\t"
      "call position_source_get_00b3d240\n\t"
      "movl (%eax), %edx\n\t"
      "movl 0x3c(%edx), %edx\n\t"
      "pushl $0x0\n\t"
      "leal 0x4(%esp), %ecx\n\t"
      "pushl %ecx\n\t"
      "movl %eax, %ecx\n\t"
      "call *%edx\n\t"
      "movl (%eax), %edx\n\t"
      "movl 0x10(%esp), %ecx\n\t"
      "movl %edx, (%ecx)\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "movl %edx, 0x4(%ecx)\n\t"
      "movl 0x8(%eax), %eax\n\t"
      "movl %eax, 0x8(%ecx)\n\t"
      "addl $0xc, %esp\n\t"
      "ret $0x4\n\t");
}

extern "C" OpaqueSelectionState* PKG_SIM_TOOL_WAVE9_THISCALL
target_01053790(OpaqueSelectionState* state, TargetWord flags) {
  state->vtable_00 = reinterpret_cast<const void*>(kSelectionTable);
  if ((flags & 1U) != 0U) {
    const SelectionTransition transition =
        g_sim_tool_wave9_ports.selection_transition_00f47380;
    __asm__ volatile(
        "pushl %1\n\t"
        "call *%0\n\t"
        "addl $0x4, %%esp"
        :
        : "r"(transition), "r"(state)
        : "cc", "memory", "eax", "ebx", "ecx", "edx");
  }
  return state;
}

extern "C" bool PKG_SIM_TOOL_WAVE9_CDECL
target_01053db0(OpaqueToolState* state) {
  OpaqueBeamTarget* target = state->target_124;
  if (target != nullptr) {
    beam_mark_00cb3c70(target);
    target = state->target_124;
    if (target != nullptr) {
      state->target_124 = nullptr;
      target->vtable_00->release_04(target);
    }
  }
  if (beam_gate_0104cd50(state)) {
    OpaqueRelationshipState* const relationship = relationship_get_00b3d3c0();
    relationship->state_20 &= ~TargetWord{4};
    relationship->state_55a0 = 0U;
    g_sim_tool_wave9_ports.event_drain_00b77aa0(relationship);
  }
  return true;
}

extern "C" bool PKG_SIM_TOOL_WAVE9_NAKED PKG_SIM_TOOL_WAVE9_THISCALL
target_01054080(OpaqueSpecialState*, OpaqueSelectionContext*, TargetWord,
                TargetWord) {
  __asm__ volatile(
      "pushl %ebx\n\t"
      "pushl %ebp\n\t"
      "movl %ecx, %ebp\n\t"
      "movl 0xc(%esp), %ebx\n\t"
      "cmpl $0x0, 0x12c(%ebx)\n\t"
      "jne 2f\n\t"
      "call special_select_port_get_01053980\n\t"
      "movl 0x14(%esp), %edx\n\t"
      "pushl %edx\n\t"
      "movl 0x14(%esp), %edx\n\t"
      "pushl %edx\n\t"
      "pushl %ebx\n\t"
      "movl %ebp, %ecx\n\t"
      "call *%eax\n\t"
      "testb %al, %al\n\t"
      "setne %al\n\t"
      "popl %ebp\n\t"
      "popl %ebx\n\t"
      "ret $0xc\n\t"
      "2:\n\t"
      "movb $0x1, %al\n\t"
      "popl %ebp\n\t"
      "popl %ebx\n\t"
      "ret $0xc\n\t");
}

}

#undef PKG_SIM_TOOL_WAVE9_THISCALL
#undef PKG_SIM_TOOL_WAVE9_CDECL
#undef PKG_SIM_TOOL_WAVE9_NAKED
