#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-007c3c50 flag-mask-dispatch requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define FLAGMASK_THISCALL __thiscall
#else
#define FLAGMASK_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_007c3c50_flag_mask_dispatch {

// Opaque receiver for VA 0x007c3c50.
//
// Only two field offsets are machine-derived for this target:
//   [ECX+0x140] is loaded as an address (LEA) and handed to the callee;
//   [ECX+0x170] is dereferenced and moved into ECX, becoming the callee's
//   implicit `this`. Everything between them is not touched by this target,
// so the interior is modelled as opaque padding.
struct OpaqueWorldViewer {
  std::byte padding_000[0x140];
  std::uint32_t background_140[4];
  std::byte padding_150[0x20];
  void* camera_170;
};

// Argument 3 of the callee 0x011f3d40 is read with "MOV DL,[ESP+8]", i.e. one
// byte, after the two PUSHes made by the target itself.
using FlagMaskDispatch = std::uint8_t(FLAGMASK_THISCALL*)(
    void* /*camera*/, const std::uint32_t* /*background*/,
    std::uint8_t /*flags*/);

// Default port stands in for callee 0x011f3d40, whose own semantics are not
// established by the target bytes.
extern FlagMaskDispatch g_dispatch_port;

void set_dispatch_port(FlagMaskDispatch port);

extern "C" std::uint8_t FLAGMASK_THISCALL world_viewer_apply_flags_007c3c50(
    OpaqueWorldViewer* viewer, std::uint8_t flags);

}

#undef FLAGMASK_THISCALL