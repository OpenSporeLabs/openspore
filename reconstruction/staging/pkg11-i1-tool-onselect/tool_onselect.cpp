#include "tool_onselect.hpp"

namespace openspore::reconstruction::pkg11_i1_tool_onselect {

OnSelectPorts g_pkg11_i1_tool_onselect_ports{};

const Vftable01403934 kVftable01403934Image{0x01053790u, 0x011e06d0u,
                                            0x011e06d0u, 0x011e06d0u,
                                            0x012c6625u, 0x012c6625u};

const Vftable01403934* const kVftable_01403934 = &kVftable01403934Image;

#if defined(_MSC_VER)
#define PKG11I1_THISCALL __thiscall
#else
#define PKG11I1_THISCALL __attribute__((thiscall))
#endif

bool pkg11_i1_on_select_arg_bit0(std::uint32_t arg_word) {
  return (arg_word & 1u) != 0u;
}

bool PKG11I1_THISCALL on_select_01053790(OpaqueBaseSubobject01403934* strategy,
                                         std::uint32_t arg_word) {
  strategy->vftable = kVftable_01403934;

  if (pkg11_i1_on_select_arg_bit0(arg_word)) {
    g_pkg11_i1_tool_onselect_ports.pool_release_00f47380(strategy);
  }

  return strategy != nullptr;
}

#undef PKG11I1_THISCALL

}
