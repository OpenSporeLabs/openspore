#pragma once

// Reconstruction of App::cCameraManager::SetViewer @ 0x007c61a0
// (SporeApp.exe 3.1.0.22).
//
// Evidence basis, re-read for this package:
//   * disassembly 0x007c61a0..0x007c61b7 - exactly eight instructions:
//       0x007c61a0  8b 81 a8 00 00 00   MOV  EAX,dword ptr [ECX + 0xa8]
//       0x007c61a6  85 c0               TEST EAX,EAX
//       0x007c61a8  7c 0a               JL   0x007c61b4
//       0x007c61aa  8b 89 80 00 00 00   MOV  ECX,dword ptr [ECX + 0x80]
//       0x007c61b0  8b 04 81            MOV  EAX,dword ptr [ECX + EAX*0x4]
//       0x007c61b3  c3                  RET
//       0x007c61b4  33 c0               XOR  EAX,EAX
//       0x007c61b6  c3                  RET
//   * receiver record: register=ECX, offsets=[0x80, 0xa8], bounds_only.
//   * vtable image vtable:0x014106a4. The sixteen words read at
//     0x014106a4 are 0x007c75d0, 0x007c76e0, 0x007c6610, 0x00c6a960,
//     0x007b86e0, 0x007c70b0, 0x007c6db0, 0x007c6100, 0x00a21120,
//     0x007c6e90, 0x007c7270, 0x007c6b80, 0x007c63a0, 0x007c6110,
//     0x007c66b0, 0x007c61a0, 0x007c6150 - so word 15, at displacement
//     0x3c from the table base, is this entry. The body itself never reads
//     [ECX+0x00]; the vtable pointer on the receiver is a fact of the
//     dispatch record, not of these eight instructions.
//
// WHAT THE RECEIVER EVIDENCE CARRIES AND WHAT IT DOES NOT. The machine proves
// this body reads exactly two words of the receiver: a signed 32-bit value at
// +0xa8 and a pointer at +0x80, and the receiver record corroborates precisely
// those two displacements. It proves nothing about which member of any type
// occupies either word - a camera array's base, an active index, a count, a
// generation number would all read the same - and it says nothing at all about
// the bytes in between or beyond. So no member is declared on OpaqueCameraManager
// below: it is an opaque run of bytes, and the reconstruction reaches it only
// through the word_at displacement accessor. Naming `active_index_0a8` or
// `cameras_080` would be importing a member story from the SDK header that this
// body's own evidence does not carry.

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-app-camera-active-007c61a0 reconstruction requires an x86-32 target"
#endif

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

static_assert(sizeof(void*) == 4,
              "pkg-app-camera-active-007c61a0 requires 32-bit pointers");
static_assert(sizeof(std::int32_t) == 4, "int32 must be 4 bytes");

struct OpaqueCamera;
struct OpaqueCameraManager;

// The element type of the array the +0x80 word is dereferenced as. The body
// only ever hands the loaded 4-byte word back to the caller, so the camera is
// modelled as a never-dereferenced object of a plausible shape and nothing is
// claimed about its own layout.
struct OpaqueCameraVTable {
  void* slots_00[5]{};
};

struct OpaqueCamera {
  OpaqueCameraVTable* vtable_000 = nullptr;
  std::uint32_t opaque_004 = 0;
};

using SetViewer007c61a0 =
    OpaqueCamera*(PKG_CAM_ACTIVE_THISCALL*)(OpaqueCameraManager*);

// The dispatch table image, kept apart from the receiver because the body
// never reads a vtable word off the receiver. `slots_00` holds the sixteen
// words read at 0x014106a4; word 15 (displacement 0x3c) is this entry.
struct OpaqueCameraManagerVTable {
  void* slots_00[15]{};
  SetViewer007c61a0 get_active_camera_3c = nullptr;
};

static_assert(offsetof(OpaqueCameraManagerVTable, get_active_camera_3c) == 0x3c,
              "vtable slot 15 of table 0x014106a4 offset");

// The two receiver displacements 0x007c61a0 was observed reaching, as values
// rather than as members: 0xa8 from `MOV EAX,dword ptr [ECX + 0xa8]` and 0x80
// from `MOV ECX,dword ptr [ECX + 0x80]`. The scale of the element index is the
// third constant the body names, 0x4 from `MOV EAX,dword ptr
// [ECX + EAX*0x4]`.
constexpr std::size_t kIndexDisplacement = 0xa8;
constexpr std::size_t kBaseDisplacement = 0x80;
constexpr std::size_t kElementStride = 0x4;

// Receiver of 0x007c61a0, modelled as far as the machine reached and no
// further: 0xac bytes, 4-byte aligned, the prefix through the last word the
// body reads. +0x00 is the dispatch word the vtable record names; +0x04..+0xab
// is opaque and is never read or written by this body. The extent is a
// modelling bound, not a recovered allocation size.
struct alignas(4) OpaqueCameraManager {
  OpaqueCameraManagerVTable* vtable_000 = nullptr;  // +0x00, dispatch record
  std::array<std::uint8_t, 0xa8> opaque_004{};     // +0x04..+0xab
};

// The only way this package touches the receiver: a 4-byte word at a stated
// displacement. A member access would assert an identity the receiver record
// (a set of displacements, bounds_only) cannot confirm.
inline std::uint32_t* word_at(OpaqueCameraManager* manager,
                              std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(manager) + displacement);
}

inline const std::uint32_t* word_at(const OpaqueCameraManager* manager,
                                    std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(manager) + displacement);
}

// The 4-byte word at a displacement, read as the address it holds. 0x007c61aa
// loads the +0x80 word into ECX and 0x007c61b0 dereferences it, so the value
// stored there is an address, not a datum. Which object it is the base of is
// not something this body establishes.
inline const std::uint8_t* address_at(const OpaqueCameraManager* manager,
                                      std::size_t displacement) {
  return reinterpret_cast<const std::uint8_t*>(
      static_cast<std::uintptr_t>(*word_at(manager, displacement)));
}

static_assert(sizeof(OpaqueCameraManager) == 0xac,
              "modeled receiver extent through the last word the body reads");
static_assert(offsetof(OpaqueCameraManager, opaque_004) == 0x04,
              "the opaque prefix starts right after the dispatch word");
static_assert(kIndexDisplacement + sizeof(std::uint32_t) ==
                  sizeof(OpaqueCameraManager),
              "the index word ends the modeled receiver extent");
static_assert(kBaseDisplacement + sizeof(std::uint32_t) <= kIndexDisplacement,
              "the base word and the index word are distinct, non-overlapping");
static_assert(sizeof(OpaqueCamera*) == kElementStride,
              "the element stride 0x4 of [ECX + EAX*0x4] is a 32-bit pointer");

extern "C" OpaqueCamera* PKG_CAM_ACTIVE_THISCALL set_viewer_007c61a0(
    OpaqueCameraManager* manager);

}

#undef PKG_CAM_ACTIVE_CDECL
#undef PKG_CAM_ACTIVE_THISCALL
#undef PKG_CAM_ACTIVE_FASTCALL
