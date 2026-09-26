#include "dogfood_005c5ee0.hpp"

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-005c5ee0 requires MSVC or GCC CCs"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0 {

GetCategoryPorts g_dogfood_005c5ee0_ports{};

// 0x005c5ee0, eleven instructions, 0x005c5ee0 through 0x005c5efb.
// 0x005c5ee0-0x005c5ee1 push ESI and copy the ECX receiver into ESI, so the
// receiver word is preserved across both calls.
// 0x005c5ee3 calls 0x005c5e90 with ECX still holding the receiver and pushes
// nothing, so the teardown port takes the receiver and no stack word. Its EAX
// result is discarded: 0x005c5ef8 overwrites EAX with the saved receiver.
// 0x005c5ee8 tests bit 0 of the byte at ESP+0x8. With the pushed ESI that
// displacement is the low byte of the first ordinary stack word, and 0x005c5efb
// is `RET 0x4`, so the callee reclaims exactly that one four-byte word.
// 0x005c5eed skips the release when bit 0 is clear.
// 0x005c5eef-0x005c5ef5 push the receiver, call 0x00f47380 and add 4 back to
// the stack, so the release is cdecl with the receiver as its only argument.
// 0x005c5ef8-0x005c5efb return the receiver word in EAX on both paths, restore
// the saved ESI and reclaim the stack word.
// The body writes no memory: the receiver is never dereferenced, so the model
// reproduces no receiver store.
extern "C" OpaquePaletteMain* PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL
palettes_palette_main_get_category_005c5ee0(OpaquePaletteMain* main,
                                            OpaqueWord stack_word) {
  GetCategoryPorts& ports = g_dogfood_005c5ee0_ports;

  ports.teardown_005c5e90(main);

  if ((stack_word & 0x1u) != 0u) {
    ports.release_00f47380(static_cast<void*>(main));
  }

  return main;
}

}

#undef PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL
