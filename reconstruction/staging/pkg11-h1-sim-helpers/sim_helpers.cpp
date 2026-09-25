#include "sim_helpers.hpp"

namespace openspore::reconstruction::pkg11_h1_sim_helpers {

extern "C" __attribute__((naked)) SharedGateValue
pkg11_sim_helpers_00b5b800() {
  __asm__(
      "call manager_root_00b3d320\n\t"
      "testl %eax, %eax\n\t"
      "jz 1f\n\t"
      "movl %eax, %ecx\n\t"
      "jmp read_shared_gate_00a42730\n\t"
      "1:\n\t"
      "orl $-1, %eax\n\t"
      "ret\n\t");
}

extern "C" void __attribute__((thiscall))
pkg11_sim_helpers_00b5b6c0(OpaqueProgressionBadgeBase*) {
  __asm__(
      "movl %ecx, %eax\n\t"
      "xorl %ecx, %ecx\n\t"
      "movl %ecx, 0x4(%eax)\n\t"
      "movl $0x01444434, 0x8(%eax)\n\t"
      "movl $0x0146155c, (%eax)\n\t"
      "movl $0x01461538, 0x8(%eax)\n\t"
      "movb %cl, 0xc(%eax)\n\t"
      "movb %cl, 0xd(%eax)\n\t"
      "movb %cl, 0xe(%eax)\n\t"
      "ret\n\t");
}

extern "C" OpaqueRelationshipManager* g_relationship_manager_0167eb14 =
    nullptr;

extern "C" __attribute__((naked)) OpaqueRelationshipManager*
pkg11_sim_helpers_00b3d3c0() {
  __asm__(
      "movl g_relationship_manager_0167eb14, %eax\n\t"
      "ret\n\t");
}

}
