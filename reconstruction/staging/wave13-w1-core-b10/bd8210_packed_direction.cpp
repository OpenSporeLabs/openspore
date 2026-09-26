#include "bd8210_packed_direction.hpp"

#include <cstring>

namespace openspore::reconstruction::wave13_w1_core_b10 {

std::uint16_t DirectionCarrier_GetPackedDirection_00bd8210(
    OpaqueDirectionCarrier* carrier) {
  // 0x00b88590 reads three consecutive floats from the argument pointer:
  // 0x00b885a9 FLD float ptr [ECX], 0x00b885b5 FLD [ECX + 0x4],
  // 0x00b885c2 FLD [ECX + 0x8].
  //
  // 0x00bd821c is CALL EAX with ECX still holding the receiver that 0x00bd8210
  // received and with &local as the single pushed word, so slot +0x58 is a
  // thiscall of the form receiver -> (Vector3* out). clang has no
  // well-defined thiscall for a free-function pointer, so the receiver is
  // spelled as the first ordinary parameter here; the observed ECX convention
  // is recorded in the metadata sidecar.
  float local[3];
  using Slot58 = float* (*)(OpaqueDirectionCarrier*, float*);

  // 0x00bd8210 MOV EAX,[ECX] then 0x00bd8212 MOV EAX,[EAX + 0x58]: the slot is
  // addressed through the loaded vtable pointer, not through the object.
  // The load is spelled with memcpy so the reconstruction always performs the
  // memory read that 0x00bd8212 performs, instead of letting the compiler fold
  // the vtable access.
  Slot58 slot_58;
  std::memcpy(&slot_58,
              reinterpret_cast<const std::uint8_t*>(carrier->vtable) + 0x58,
              sizeof(slot_58));
  float* direction = slot_58(carrier, local);

  OpaqueGameInputManager* manager = Port_00b3d350_GetGameInputManager();
  return Port_00b88590_QuantiseDirection(manager, direction);
}

}  // namespace openspore::reconstruction::wave13_w1_core_b10
