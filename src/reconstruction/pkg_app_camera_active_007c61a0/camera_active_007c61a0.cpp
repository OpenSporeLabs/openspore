#include "camera_active_007c61a0.hpp"

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_CAM_ACTIVE_CDECL __cdecl
#define PKG_CAM_ACTIVE_THISCALL __thiscall
#define PKG_CAM_ACTIVE_FASTCALL __fastcall
#else
#define PKG_CAM_ACTIVE_CDECL __attribute__((cdecl))
#define PKG_CAM_ACTIVE_THISCALL __attribute__((thiscall))
#define PKG_CAM_ACTIVE_FASTCALL __attribute__((fastcall))
#endif

namespace openspore::reconstruction::pkg_app_camera_active_007c61a0 {

extern "C" OpaqueCamera* PKG_CAM_ACTIVE_THISCALL set_viewer_007c61a0(
    OpaqueCameraManager* manager) {
  // 0x007c61a0  MOV EAX,dword ptr [ECX + 0xa8]
  // 0x007c61a6  TEST EAX,EAX
  // 0x007c61a8  JL 0x007c61b4
  // 0x007c61aa  MOV ECX,dword ptr [ECX + 0x80]
  // 0x007c61b0  MOV EAX,dword ptr [ECX + EAX*0x4]
  // 0x007c61b3  RET
  // 0x007c61b4  XOR EAX,EAX
  // 0x007c61b6  RET
  //
  // Two receiver words and nothing else, each transcribed as the address
  // arithmetic the instruction performs: the word at receiver+0xa8 is loaded
  // first and is the only thing the JL inspects; the word at receiver+0x80 is
  // then loaded as a base address and scaled-indexed by 0x4. Neither is written
  // as a member access, because the machine names no member and the receiver
  // record enumerates displacements (0x80, 0xa8) without saying which member is
  // which. The header spells the same two displacements as kBaseDisplacement
  // and kIndexDisplacement, and its static_asserts pin the extents.
  const std::int32_t index = static_cast<std::int32_t>(
      *reinterpret_cast<const std::uint32_t*>(
          reinterpret_cast<std::uintptr_t>(manager) + 0xa8));
  if (index < 0) {
    // 0x007c61b4 XOR EAX,EAX / 0x007c61b6 RET. TEST EAX,EAX clears the flags
    // the JL then reads and nothing touches them afterwards, and JL is a signed
    // jump, so the rejection is signed and exact: every negative word is
    // refused and no other value is.
    return nullptr;
  }
  // 0x007c61aa MOV ECX,[ECX+0x80] loads an address; 0x007c61b0 reads
  // [ECX + EAX*0x4] and hands that word back verbatim. The scale is a 32-bit
  // unsigned scale, so the byte offset is (std::uint32_t)index * 0x4, not a
  // sign-extended one - which is only reachable because the JL above has
  // already excluded every negative word.
  const std::uint8_t* base = reinterpret_cast<const std::uint8_t*>(
      static_cast<std::uintptr_t>(*reinterpret_cast<const std::uint32_t*>(
          reinterpret_cast<std::uintptr_t>(manager) + 0x80)));
  return *reinterpret_cast<OpaqueCamera* const*>(
      base + static_cast<std::uint32_t>(index) * 0x4u);
}

}
