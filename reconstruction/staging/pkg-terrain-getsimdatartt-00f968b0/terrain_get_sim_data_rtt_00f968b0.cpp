#include "terrain_get_sim_data_rtt_00f968b0.hpp"

// Reconstruction of the body at 0x00f968b0..0x00f968ff, statement for
// statement. The machine is:
//
//   00f968b0  PUSH EBX / PUSH ESI / PUSH EDI          prologue, 3 callee-saved
//   00f968b2  MOV ESI,ECX                             receiver into ESI
//   00f968b5  TEST ESI,ESI / JZ +0x5                  null-receiver guard
//   00f968b9  LEA EDI,[ESI + 0x4]                     anchor, first compare
//   00f968be  XOR EDI,EDI                             null receiver -> 0 anchor
//   00f968c0  MOV EBX,dword ptr [ESP + 0x10]          the stack argument
//   00f968c4  MOV EAX,dword ptr [EBX]                 provider vtable
//   00f968c6  MOV EDX,dword ptr [EAX + 0x58]          slot +0x58
//   00f968c9  PUSH 0x8 / MOV ECX,EBX / CALL EDX       query with 0x8
//   00f968cf  CMP EAX,EDI / JNZ -> return 0           first compare
//   00f968d3  TEST ESI,ESI / JZ +0x7                  the guard is REPEATED
//   00f968d7  ADD ESI,0x4                             anchor, second compare
//   00f968dc  XOR ESI,ESI                             null receiver -> 0 anchor
//   00f968de  MOV EAX,dword ptr [EBX]                 vtable reloaded
//   00f968e0  MOV EDX,dword ptr [EAX + 0x58]          slot reloaded
//   00f968e3  PUSH 0x7 / MOV ECX,EBX / CALL EDX       query with 0x7
//   00f968e9  CMP EAX,ESI / JNZ -> return 0           second compare
//   00f968ed  POP EDI / POP ESI / MOV EAX,0x1         success
//   00f968f5  RET 0x4
//   00f968f8  POP EDI / POP ESI / XOR EAX,EAX         failure
//   00f968fd  RET 0x4
//
// The BOTH-queries-must-return-the-anchor shape is the observation, not a
// reconstruction convenience: the second compare uses the same
// &receiver->anchor_04 address as the first, and both compares gate the same
// JNZ to the zero-return block. Whether the original source really asked the
// same object twice, or whether the compiler duplicated an anchor load, is not
// decidable from this body; see unresolved_questions in the sidecar.

namespace openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0 {

extern "C" bool PKG_GSDR_THISCALL get_sim_data_rtt_00f968b0(
    OpaqueTerrainSphere* self, OpaqueSelectorProvider* provider) {
  // 0x00f968b5..0x00f968be. The guard is not defensive source code: the machine
  // materialises a NULL anchor for a NULL receiver and keeps going.
  OpaqueRttData* const anchor_first =
      self != nullptr ? &self->anchor_04 : nullptr;

  // 0x00f968c0..0x00f968d1. The provider is dereferenced unconditionally
  // (MOV EAX,dword ptr [EBX]), so a NULL provider faults exactly as it does in
  // the original; there is no guard to reproduce.
  if (provider->vtable->select_58(provider, kSelectorIdFirst) != anchor_first) {
    return false;  // 0x00f968f8..0x00f968fd: XOR EAX,EAX / POP EBX / RET 0x4
  }

  // 0x00f968d3..0x00f968dc. Emitted again by the compiler even though the first
  // guard already established the same value; kept because it is observable.
  OpaqueRttData* const anchor_second =
      self != nullptr ? &self->anchor_04 : nullptr;

  // 0x00f968de..0x00f968eb. The vtable word and the +0x58 slot are re-read from
  // memory rather than reused, so a provider that mutates itself between the two
  // queries is observed by the second compare.
  return provider->vtable->select_58(provider, kSelectorIdSecond) ==
         anchor_second;  // 0x00f968ed..0x00f968f5: MOV EAX,0x1 / POP EBX / RET 0x4
}

}  // namespace openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0
