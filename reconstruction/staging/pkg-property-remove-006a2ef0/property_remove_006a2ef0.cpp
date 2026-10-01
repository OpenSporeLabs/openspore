#include "property_remove_006a2ef0.hpp"

#include <cstdint>

// Restated here (identical replacement list, so the redefinition is benign) so
// this translation unit names the convention in the definition itself.
#if defined(_MSC_VER)
#define PKG_PROPERTY_REMOVE_006A2EF0_THISCALL __thiscall
#else
#define PKG_PROPERTY_REMOVE_006A2EF0_THISCALL __attribute__((thiscall))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_property_remove_006a2ef0 {
namespace {

// Machine body, verbatim (Intel syntax, Ghidra /disassemble_function):
//
//   006a2ef0  PUSH ESI
//   006a2ef1  MOV ESI,ECX
//   006a2ef3  LEA EAX,[ESP + 0x8]
//   006a2ef7  PUSH EAX
//   006a2ef8  LEA ECX,[ESI + 0x18]
//   006a2efb  CALL 0x006a2cb0
//   006a2f00  INC dword ptr [ESI + 0x34]
//   006a2f03  POP ESI
//   006a2f04  RET 0x4
//
// Straight line: no conditional branch, no indirect transfer, one direct call.

// Displacement of the receiver the removal port is invoked on
// (0x006a2ef8: LEA ECX,[ESI + 0x18]).
//
// The machine-derived receiver record enumerates one displacement for this
// body, 0x34, and it observed it through the ESI alias rather than through the
// receiver register's own operands; the LEA at 0x006a2ef8 is an address
// computation, not a memory access, so it contributes no receiver displacement
// to that record. The value is therefore stated here, at file scope, and the
// reconstructed span below names no displacement the record does not enumerate.
// Its identity -- which sub-object of the receiver lives at this offset -- is
// not established by the machine record and is not claimed.
constexpr std::uintptr_t kPortReceiverDisplacement = 0x18;

}  // namespace

int PKG_PROPERTY_REMOVE_006A2EF0_THISCALL property_list_remove_property_006a2ef0(
    OpaquePropertyList* self, std::uint32_t property_id) {
  // 0x006a2ef1: MOV ESI,ECX keeps the receiver in ESI for both remaining
  // accesses; 0x006a2ef3/0x006a2ef7 take the address of the incoming property-id
  // word (entry ESP+0x4, still live because nothing has popped it) rather than
  // its value, which is what the port expects.
  OpaquePropertyMap* port_receiver = reinterpret_cast<OpaquePropertyMap*>(
      reinterpret_cast<std::uintptr_t>(self) + kPortReceiverDisplacement);

  // 0x006a2efb: CALL 0x006a2cb0 with ECX = port_receiver and the property-id
  // address on the stack. EAX is left exactly as the port returned it. The port
  // pops that pointer itself (both of its exits are RET 0x4), so nothing is
  // cleaned up here and the stack is already back to entry_ESP by the increment.
  const int removed =
      property_list_map_remove_006a2cb0(port_receiver, &property_id);

  // 0x006a2f00: INC dword ptr [ESI + 0x34].
  //
  // The receiver word this body read-modify-writes. Whether it counts property
  // mutations, removals, or operations issued against the list is not
  // established by the machine record; only the increment itself is observed,
  // and it is unconditional: it runs after the port returns whatever the port
  // returned, so the word is bumped on the port's no-removal path too.
  *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(self) +
                                    0x34) += 1;

  // 0x006a2f03/0x006a2f04: POP ESI restores the saved register and RET 0x4 pops
  // the property-id word, so the callee owns the stack cleanup. No instruction
  // between the call and the return writes EAX, so the port's result is the
  // value this function returns.
  return removed;
}

}  // namespace pkg_property_remove_006a2ef0
}  // namespace reconstruction
}  // namespace openspore

#undef PKG_PROPERTY_REMOVE_006A2EF0_THISCALL
