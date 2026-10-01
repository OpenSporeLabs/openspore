#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-11-I1 tool OnSelect staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg11_i1_tool_onselect {

struct Vftable01403934;

struct OpaqueBaseSubobject01403934 {
  const Vftable01403934* vftable;
};

struct Vftable01403934 {
  std::uint32_t slot0_va;
  std::uint32_t slot1_va;
  std::uint32_t slot2_va;
  std::uint32_t slot3_va;
  std::uint32_t slot4_va;
  std::uint32_t slot5_va;
};

struct OnSelectPorts {
  void (*pool_release_00f47380)(void* block);
};

static_assert(sizeof(void*) == 4, "PKG-11-I1 target pointers are 32-bit");
static_assert(offsetof(OpaqueBaseSubobject01403934, vftable) == 0x00,
              "vptr is the first word of the base subobject");
static_assert(sizeof(Vftable01403934) == 24, "six observed vftable slots");

extern OnSelectPorts g_pkg11_i1_tool_onselect_ports;
extern const Vftable01403934* const kVftable_01403934;

#if defined(_MSC_VER)
#define PKG11I1_THISCALL __thiscall
#else
#define PKG11I1_THISCALL __attribute__((thiscall))
#endif

bool PKG11I1_THISCALL on_select_01053790(OpaqueBaseSubobject01403934* strategy,
                                         std::uint32_t arg_word);

bool pkg11_i1_on_select_arg_bit0(std::uint32_t arg_word);

#undef PKG11I1_THISCALL

}
