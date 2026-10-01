#include "beam_tool_func5_01053e00.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG_SIM_BEAMTOOL_FUNC5_THISCALL __thiscall
#define PKG_SIM_BEAMTOOL_FUNC5_CDECL __cdecl
#else
#define PKG_SIM_BEAMTOOL_FUNC5_THISCALL __attribute__((thiscall))
#define PKG_SIM_BEAMTOOL_FUNC5_CDECL __attribute__((cdecl))
#endif

#define PKG_SIM_BEAMTOOL_FUNC5_NAKED __attribute__((naked))

namespace openspore::reconstruction::pkg_sim_beamtool_func5 {

const std::uint32_t kPositionServiceTable_013f94d4[8] = {};

extern "C" void PKG_SIM_BEAMTOOL_FUNC5_THISCALL anchor_position_commit_00cb5930(
    OpaqueBeamTarget* target, const OpaqueBeamToolState* fallback) {
  const OpaqueVec3* position = nullptr;
  OpaqueAnchor* const anchor = target->anchor_134;
  if (anchor != nullptr) {
    OpaqueAnchorProvider* const provider =
        anchor->vtable_00->provider_118(anchor);
    if (provider != nullptr) {
      position = provider->vtable_00->position_2c(provider);
    }
  }
  if (position == nullptr) {
    OpaqueVec3 fallback_copy{};
    std::memcpy(&fallback_copy, fallback, sizeof(fallback_copy));
    position = &fallback_copy;
  }
  target->anchor_position_13c.x = position->x;
  target->anchor_position_13c.y = position->y;
  target->anchor_position_13c.z = position->z;
}

extern "C" bool PKG_SIM_BEAMTOOL_FUNC5_NAKED PKG_SIM_BEAMTOOL_FUNC5_CDECL
func_01053e00(OpaqueBeamToolState* tool_state, void* update_context) {
  __asm__ volatile(
      "subl $0x18, %esp\n\t"
      "pushl %esi\n\t"
      "movl 0x20(%esp), %esi\n\t"
      "movl 0x124(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 2f\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x2c(%eax), %edx\n\t"
      "call *%edx\n\t"
      "testb %al, %al\n\t"
      "jz 2f\n\t"
      "movl 0x124(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 2f\n\t"
      "movl $0x0, 0x124(%esi)\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "call *%edx\n\t"
      "2:\n\t"
      "cmpl $0x0, 0x124(%esi)\n\t"
      "jz 4f\n\t"
      "movl 0x114(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 3f\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0xb8(%eax), %edx\n\t"
      "pushl $0x13f94d4\n\t"
      "call *%edx\n\t"
      "testl %eax, %eax\n\t"
      "jz 3f\n\t"
      "movl (%eax), %edx\n\t"
      "movl 0x30(%edx), %edx\n\t"
      "leal 0x10(%esp), %ecx\n\t"
      "pushl %ecx\n\t"
      "movl %eax, %ecx\n\t"
      "call *%edx\n\t"
      "jmp 5f\n\t"
      "3:\n\t"
      "movl 0x114(%esi), %ecx\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x2c(%eax), %edx\n\t"
      "call *%edx\n\t"
      "5:\n\t"
      "movss 0x0(%eax), %xmm0\n\t"
      "movss %xmm0, 0x4(%esp)\n\t"
      "movss 0x4(%eax), %xmm0\n\t"
      "movss %xmm0, 0x8(%esp)\n\t"
      "movss 0x8(%eax), %xmm0\n\t"
      "movl 0x124(%esi), %eax\n\t"
      "leal 0x34(%eax), %ecx\n\t"
      "movss %xmm0, 0xc(%esp)\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x38(%eax), %eax\n\t"
      "leal 0x4(%esp), %edx\n\t"
      "pushl %edx\n\t"
      "call *%eax\n\t"
      "movl 0x24(%esp), %ecx\n\t"
      "pushl %ecx\n\t"
      "movl 0x124(%esi), %ecx\n\t"
      "call anchor_position_commit_00cb5930\n\t"
      "movb $0x1, %al\n\t"
      "popl %esi\n\t"
      "addl $0x18, %esp\n\t"
      "ret $0x8\n\t"
      "4:\n\t"
      "xorb %al, %al\n\t"
      "popl %esi\n\t"
      "addl $0x18, %esp\n\t"
      "ret $0x8\n\t");
}

bool beam_tool_func5_01053e00_model(OpaqueBeamToolState* tool_state,
                                    void* update_context) {
  (void)update_context;
  OpaqueBeamTarget* owned = tool_state->owned_beam_target_124;
  if (owned != nullptr) {
    if (owned->vtable_00->completion_query_2c(owned)) {
      owned = tool_state->owned_beam_target_124;
      if (owned != nullptr) {
        tool_state->owned_beam_target_124 = nullptr;
        owned->vtable_00->release_04(owned);
      }
    }
  }
  owned = tool_state->owned_beam_target_124;
  if (owned == nullptr) {
    return false;
  }
  OpaquePositionSource* const source = tool_state->position_source_114;
  OpaqueFoundPosition* found = nullptr;
  if (source != nullptr) {
    found = source->vtable_00->lookup_by_table_b8(
        source, kPositionServiceTable_013f94d4);
  }
  OpaqueVec3 out_of_band{};
  const OpaqueVec3* position = nullptr;
  if (found != nullptr) {
    position = found->vtable_00->position_out_30(found, &out_of_band);
  } else {
    position = source->vtable_00->position_pointer_2c(source);
  }
  const OpaqueVec3 resolved = *position;
  OpaqueBeamEmitter* const emitter = owned->emitter_34;
  emitter->vtable_00->set_position_38(emitter, &resolved);
  anchor_position_commit_00cb5930(owned, tool_state);
  return true;
}

}

#undef PKG_SIM_BEAMTOOL_FUNC5_THISCALL
#undef PKG_SIM_BEAMTOOL_FUNC5_CDECL
#undef PKG_SIM_BEAMTOOL_FUNC5_NAKED
