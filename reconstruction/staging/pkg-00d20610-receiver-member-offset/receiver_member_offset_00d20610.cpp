#include "receiver_member_offset_00d20610.hpp"

namespace openspore::reconstruction::pkg_00d20610_receiver_member_offset {

// The body below writes the displacement as a literal rather than through the
// named constant, because the literal is what the machine instruction says. The
// assert is what keeps the two from drifting: it is checked at compile time, so
// the duplicated literal cannot become a second unverified number.
static_assert(kMemberDisplacement == 0x1c8,
              "the LEA displacement in the body is the documented one");

// This reads no memory. `self` is only the base of an address computation, which
// is what `LEA` is, so a receiver pointing at unmapped memory is in range for
// this function exactly as it is for the original -- the model test asserts that
// on a PROT_NONE mapping rather than assuming it.
extern "C" OpaqueMember* PKG_00D20610_THISCALL receiver_member_offset_00d20610(
    OpaqueReceiver* self) {
  return reinterpret_cast<OpaqueMember*>(reinterpret_cast<char*>(self) + 0x1c8);
}

}  // namespace openspore::reconstruction::pkg_00d20610_receiver_member_offset