#include "flag_mask_dispatch.hpp"

#if defined(_MSC_VER)
#define FLAGMASK_THISCALL __thiscall
#else
#define FLAGMASK_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_007c3c50_flag_mask_dispatch {

namespace {

std::uint8_t FLAGMASK_THISCALL default_dispatch(void*, const std::uint32_t*,
                                                std::uint8_t) {
  return 0;
}

}

// Callee 0x011f3d40 terminates with "RET 8", so it consumes both arguments the
// target pushes. Its own body is not reconstructed here.
FlagMaskDispatch g_dispatch_port = default_dispatch;

void set_dispatch_port(FlagMaskDispatch port) {
  g_dispatch_port = port == nullptr ? default_dispatch : port;
}

// VA 0x007c3c50 .. 0x007c3c85.
//
// Ghidra splits this span at 0x007c3c70 ("App::cViewer::Dispose"). That is a
// false boundary: the bytes there are the continuation of the flag-OR chain
// followed by the argument setup and the call, so the real span runs to the
// "RET 4" at 0x007c3c83.
extern "C" std::uint8_t FLAGMASK_THISCALL world_viewer_apply_flags_007c3c50(
    OpaqueWorldViewer* viewer, std::uint8_t flags) {
  std::uint8_t masked = 0;
  if ((flags & 0x1u) != 0) {
    masked = static_cast<std::uint8_t>(0x1u);
  }
  if ((flags & 0x2u) != 0) {
    masked = static_cast<std::uint8_t>(masked | 0x2u);
  }
  if ((flags & 0x4u) != 0) {
    masked = static_cast<std::uint8_t>(masked | 0x4u);
  }

  return g_dispatch_port(viewer->camera_170, viewer->background_140, masked);
}

}