#include "tool_strategy_01059f20.hpp"

#if defined(_MSC_VER)
#define PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL __thiscall
#define PKG_SIM_TOOLSTRATEGY_01059F20_CDECL __cdecl
#define PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL __stdcall
#define PKG_SIM_TOOLSTRATEGY_01059F20_NAKED __declspec(naked)
#else
#define PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL __attribute__((thiscall))
#define PKG_SIM_TOOLSTRATEGY_01059F20_CDECL __attribute__((cdecl))
#define PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL __attribute__((stdcall))
#define PKG_SIM_TOOLSTRATEGY_01059F20_NAKED __attribute__((naked))
#endif

namespace openspore::reconstruction::pkg_sim_toolstrategy_01059f20 {

NativePorts g_tool_strategy_01059f20_ports = {
    nullptr, nullptr, nullptr, nullptr, nullptr,
};

namespace {

const OpaqueTypeEntry* tool_owner_cast_type_entry() {
  return reinterpret_cast<const OpaqueTypeEntry*>(
      static_cast<std::uintptr_t>(kToolOwnerCastTypeEntryVa));
}

}

extern "C" bool PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL tool_precheck_010568b0(
    cSpaceToolData* pTool, const Vector3* aimPoint, int param_4) {
  return g_tool_strategy_01059f20_ports.tool_precheck_010568b0(pTool, aimPoint,
                                                               param_4);
}

extern "C" bool PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
tool_flags_picks_flora_0104cd50(cSpaceToolData* pTool) {
  return g_tool_strategy_01059f20_ports.tool_flags_picks_flora_0104cd50(pTool);
}

extern "C" cRelationshipManager* PKG_SIM_TOOLSTRATEGY_01059F20_CDECL
relationship_manager_get_00b3d3c0() {
  return g_tool_strategy_01059f20_ports.relationship_manager_get_00b3d3c0();
}

extern "C" void PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
relationship_set_event_00b7c160(cRelationshipManager* manager,
                                TargetWord value) {
  g_tool_strategy_01059f20_ports.relationship_set_event_00b7c160(manager,
                                                                 value);
}

extern "C" void PKG_SIM_TOOLSTRATEGY_01059F20_CDECL
tool_position_update_01059170(cSpaceToolData* pTool, float x, float y,
                              float z) {
  g_tool_strategy_01059f20_ports.tool_position_update_01059170(pTool, x, y, z);
}

extern "C" bool PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
func_01059f20(OpaqueToolStrategy* strategy, cSpaceToolData* pTool,
              const Vector3* aimPoint, int param_4) {
  if (!g_tool_strategy_01059f20_ports.tool_precheck_010568b0(pTool, aimPoint,
                                                             param_4)) {
    return true;
  }
  void* owner_view = nullptr;
  if (pTool->mpToolOwner != nullptr) {
    owner_view = pTool->mpToolOwner->vtable_00->cast_b8(
        pTool->mpToolOwner, tool_owner_cast_type_entry());
  }
  if (owner_view == nullptr) {
    return true;
  }
  const Vector3 aim = *aimPoint;
  cDefaultBeamProjectile* held = pTool->mpBeam;
  if (held != nullptr) {
    held->vtable_00->add_ref_00(held);
    if (held->vtable_00->predicate_2c(held)) {
      strategy->vtable_00->bridge_48(strategy, pTool, &aim);
      cDefaultBeamProjectile* const current = pTool->mpBeam;
      if (current != held) {
        if (current != nullptr) {
          current->vtable_00->add_ref_00(current);
        }
        cDefaultBeamProjectile* const previous = held;
        held = current;
        if (previous != nullptr) {
          previous->vtable_00->release_04(previous);
        }
      }
      if (g_tool_strategy_01059f20_ports.tool_flags_picks_flora_0104cd50(
              pTool)) {
        cRelationshipManager* const manager =
            g_tool_strategy_01059f20_ports.relationship_manager_get_00b3d3c0();
        g_tool_strategy_01059f20_ports.relationship_set_event_00b7c160(
            manager, kRelationshipSetterArgument);
      }
    }
  } else {
    strategy->vtable_00->bridge_48(strategy, pTool, &aim);
  }
  if (held != nullptr) {
    held->field_154 = 1;
  }
  g_tool_strategy_01059f20_ports.tool_position_update_01059170(pTool, aim.x,
                                                               aim.y, aim.z);
  if (held != nullptr) {
    held->vtable_00->release_04(held);
  }
  return true;
}

}

namespace ts = openspore::reconstruction::pkg_sim_toolstrategy_01059f20;

extern "C" bool PKG_SIM_TOOLSTRATEGY_01059F20_NAKED
    PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
    ts::naked_body_01059f20(ts::OpaqueToolStrategy*, ts::cSpaceToolData*,
                            const ts::Vector3*, int) {
  __asm__ __volatile__(
      "subl $0x10, %esp\n\t"
      "movl 0x1c(%esp), %eax\n\t"
      "pushl %ebx\n\t"
      "movl 0x1c(%esp), %ebx\n\t"
      "pushl %ebp\n\t"
      "movl 0x1c(%esp), %ebp\n\t"
      "pushl %esi\n\t"
      "pushl %edi\n\t"
      "pushl %eax\n\t"
      "pushl %ebx\n\t"
      "pushl %ebp\n\t"
      "movl %ecx, 0x1c(%esp)\n\t"
      "call tool_precheck_010568b0\n\t"
      "testb %al, %al\n\t"
      "jz 9f\n\t"
      "movl 0x114(%ebp), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 8f\n\t"
      "movl (%ecx), %edx\n\t"
      "movl 0xb8(%edx), %eax\n\t"
      "pushl $0x013f94d4\n\t"
      "call *%eax\n\t"
      "jmp 7f\n\t"
      "8:\n\t"
      "xorl %eax, %eax\n\t"
      "7:\n\t"
      "xorl %esi, %esi\n\t"
      "testl %eax, %eax\n\t"
      "jz 9f\n\t"
      "movss (%ebx), %xmm0\n\t"
      "movl 0x124(%ebp), %edi\n\t"
      "movss %xmm0, 0x14(%esp)\n\t"
      "movss 0x4(%ebx), %xmm0\n\t"
      "movss %xmm0, 0x18(%esp)\n\t"
      "movss 0x8(%ebx), %xmm0\n\t"
      "movss %xmm0, 0x1c(%esp)\n\t"
      "testl %edi, %edi\n\t"
      "jz 6f\n\t"
      "movl (%edi), %edx\n\t"
      "movl (%edx), %eax\n\t"
      "movl %edi, %ecx\n\t"
      "call *%eax\n\t"
      "movl (%edi), %edx\n\t"
      "movl 0x2c(%edx), %eax\n\t"
      "movl %edi, %ecx\n\t"
      "movl %edi, %esi\n\t"
      "call *%eax\n\t"
      "testb %al, %al\n\t"
      "jz 5f\n\t"
      "6:\n\t"
      "movl 0x10(%esp), %ecx\n\t"
      "movl (%ecx), %edx\n\t"
      "movl 0x48(%edx), %edx\n\t"
      "leal 0x14(%esp), %eax\n\t"
      "pushl %eax\n\t"
      "pushl %ebp\n\t"
      "call *%edx\n\t"
      "movl 0x124(%ebp), %edi\n\t"
      "cmpl %edi, %esi\n\t"
      "jz 3f\n\t"
      "movl %esi, 0x2c(%esp)\n\t"
      "testl %edi, %edi\n\t"
      "jz 2f\n\t"
      "movl (%edi), %eax\n\t"
      "movl (%eax), %edx\n\t"
      "movl %edi, %ecx\n\t"
      "call *%edx\n\t"
      "2:\n\t"
      "movl 0x2c(%esp), %ecx\n\t"
      "movl %edi, %esi\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 3f\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "call *%edx\n\t"
      "3:\n\t"
      "movl %ebp, %ecx\n\t"
      "call tool_flags_picks_flora_0104cd50\n\t"
      "testb %al, %al\n\t"
      "jz 5f\n\t"
      "pushl $7\n\t"
      "call relationship_manager_get_00b3d3c0\n\t"
      "movl %eax, %ecx\n\t"
      "call relationship_set_event_00b7c160\n\t"
      "5:\n\t"
      "testl %esi, %esi\n\t"
      "jz 4f\n\t"
      "movb $1, 0x154(%esi)\n\t"
      "4:\n\t"
      "flds (%ebx)\n\t"
      "subl $0xc, %esp\n\t"
      "movl %esp, %eax\n\t"
      "fstps (%eax)\n\t"
      "pushl %ebp\n\t"
      "flds 0x4(%ebx)\n\t"
      "fstps 0x4(%eax)\n\t"
      "flds 0x8(%ebx)\n\t"
      "fstps 0x8(%eax)\n\t"
      "call tool_position_update_01059170\n\t"
      "addl $0x10, %esp\n\t"
      "testl %esi, %esi\n\t"
      "jz 9f\n\t"
      "movl (%esi), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "movl %esi, %ecx\n\t"
      "call *%edx\n\t"
      "9:\n\t"
      "popl %edi\n\t"
      "popl %esi\n\t"
      "popl %ebp\n\t"
      "movb $1, %al\n\t"
      "popl %ebx\n\t"
      "addl $0x10, %esp\n\t"
      "ret $0xc\n\t");
}
