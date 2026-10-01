#include "vft_preinc_0051e340.hpp"

// Same narrow suppression as the header: the definition is a free function
// spelled __thiscall on purpose (see the header for why).
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

namespace openspore::reconstruction::pkg_vft_preinc_0051e340 {

// 0x0051e340 -- virtual member (vftable slot), receiver in ECX (__thiscall).
//
// Machine, verbatim and complete (20 instructions, 52 bytes):
//   0x0051e340  PUSH EBP
//   0x0051e341  MOV EBP,ESP
//   0x0051e343  SUB ESP,0xc
//   0x0051e346  MOV dword ptr [EBP + -0x8],ECX
//   0x0051e349  MOV EAX,dword ptr [EBP + -0x8]
//   0x0051e34c  ADD EAX,0x4
//   0x0051e34f  MOV dword ptr [EBP + -0x4],EAX
//   0x0051e352  MOV ECX,dword ptr [EBP + -0x4]
//   0x0051e355  MOV EDX,dword ptr [ECX + 0x4]
//   0x0051e358  ADD EDX,0x1
//   0x0051e35b  MOV dword ptr [EBP + -0xc],EDX
//   0x0051e35e  MOV EAX,dword ptr [EBP + -0x4]
//   0x0051e361  MOV ECX,dword ptr [EAX + 0x4]
//   0x0051e364  ADD ECX,0x1
//   0x0051e367  MOV EDX,dword ptr [EBP + -0x4]
//   0x0051e36a  MOV dword ptr [EDX + 0x4],ECX
//   0x0051e36d  MOV EAX,dword ptr [EBP + -0xc]
//   0x0051e370  MOV ESP,EBP
//   0x0051e372  POP EBP
//   0x0051e373  RET
//
// Semantics recovered:
//   * The receiver arrives in ECX (V1-VFT: vftable slot, callee pops nothing,
//     no stack word read as an argument) and is spilled at [EBP-0x8].
//   * The machine forms the byte address receiver+4 (ADD EAX,0x4 at 0x0051e34c),
//     spills it at [EBP-0x4], reloads it into ECX, and reads the dword at
//     [ECX+0x4] -- that is, the dword at receiver+8. ECX is reassigned before
//     the deref, which is why the machine-derived receiver record enumerates
//     no offsets; the field's receiver-relative offset 0x8 is the composition
//     of the two machine displacements, recorded in the header.
//   * The field dword is read twice, both reads before the store: EDX = [ECX+4]
//     + 1 is spilled at [EBP-0xc], then ECX = [EAX+4] + 1 is stored back to
//     [EDX+4]. Both reads see the old value, so the observable semantics are a
//     pre-increment: the field becomes old+1 and old+1 is returned in EAX.
//   * The double read is a -O0 codegen artifact (each subexpression evaluated
//     independently); nothing runs between the reads, so the single-read
//     pre-increment below is observationally identical.
//   * The return is a full 32-bit EAX value (MOV EAX,[EBP-0xc] is a dword
//     load), so the return type is std::uint32_t and not a narrower integer.
//   * No call, no jump, no branch, no data-segment address: the body touches
//     only the receiver's dword at +8 and its own frame.
extern "C" std::uint32_t PKG_VP_THISCALL vft_preinc_0051e340(Receiver* self) {
  std::uint8_t* const base =
      reinterpret_cast<std::uint8_t*>(self) + kBaseDisplacement;
  std::uint32_t* const field =
      reinterpret_cast<std::uint32_t*>(base + kFieldDisplacement);
  const std::uint32_t incremented = *field + 1;
  *field = incremented;
  return incremented;
}

}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
