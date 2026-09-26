#include "c37360_global_accessor.hpp"

namespace openspore::reconstruction::wave13_w1_core_b10 {

namespace {

// 0x0168df68. The address is the literal encoded in the MOV at 0x00c37360
// (a1 68 df 68 01), so it is a fixed image-relative global, not a TLS slot.
OpaqueSimulatorSubsystem* const* const kSimulatorSubsystemSlot =
    reinterpret_cast<OpaqueSimulatorSubsystem* const*>(0x0168df68UL);


}  // namespace

OpaqueSimulatorSubsystem* SimulatorSubsystem_GetGlobal_00c37360() {
  return *kSimulatorSubsystemSlot;
}

}  // namespace openspore::reconstruction::wave13_w1_core_b10
