#include "dogfood_0095fa30.hpp"

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-0095fa30 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30 {

TargetPorts g_dogfood_0095fa30_ports{};

// 0x0095fa30 UTFWin::Window::IsAncestorOf, the ModAPI SDK import name.
// Raw bytes 0x0095fa30-0x0095fa3c: 8b 44 24 04 / 89 81 80 00 00 00 / c2 04 00.
// 0x0095fa30 loads the first stack word into EAX, 0x0095fa34 stores it at
// receiver+0x80, and 0x0095fa3a returns with RET 0x4. ECX is the receiver, the
// only argument is one callee-cleaned 4-byte stack word, and the body holds no
// branch, call, flag test, or register save. Nothing is written to EAX after
// the load, so the copied argument word is still in EAX at the RET; no evidence
// claims it as a returned value and the model returns void. The SDK name and
// its bool result are contradicted by the body, which is one unconditional
// pointer store, so no ancestor query is modeled.
extern "C" void PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL
utfwin_window_is_ancestor_of_0095fa30(OpaqueWindowLayout* window,
                                      OpaqueWindow* argument) {
  window->opaque_0080 = argument;
}

}

#undef PKG_ORCHESTRATE_DOGFOOD_0095FA30_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL
