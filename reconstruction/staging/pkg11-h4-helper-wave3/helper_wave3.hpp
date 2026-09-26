#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-11-H4 helper wave 3 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg11_h4_helper_wave3 {

struct alignas(4) OpaqueAddressWindow {
  std::array<std::uint8_t, 0x3c> opaque;
};

using OpaqueContextWord = std::uint32_t;

struct alignas(4) OpaqueContext {
  std::array<std::uint8_t, 0x184> opaque_prefix;
  OpaqueContextWord context_word;
};

using AddressWindowOffsetAbi =
    OpaqueAddressWindow*(__attribute__((fastcall)) *)(OpaqueAddressWindow*);
using ContextWordReadAbi =
    OpaqueContextWord(__attribute__((fastcall)) *)(OpaqueContext*);

extern "C" OpaqueAddressWindow* __attribute__((fastcall))
address_window_offset_005c65e0(OpaqueAddressWindow*);
extern "C" OpaqueContextWord __attribute__((fastcall))
context_word_read_00ce6950(OpaqueContext*);

static_assert(sizeof(void*) == 4, "PKG-11-H4 target pointers are 32-bit");
static_assert(sizeof(OpaqueAddressWindow) == 0x3c,
              "opaque address-window extent");
static_assert(sizeof(OpaqueContextWord) == 4,
              "opaque context words are 32-bit");
static_assert(offsetof(OpaqueContext, context_word) == 0x184,
              "opaque context-word offset");
static_assert(sizeof(OpaqueContext) == 0x188,
              "opaque context access-window extent");
static_assert(std::is_same_v<decltype(&address_window_offset_005c65e0),
                             AddressWindowOffsetAbi>,
              "address-window offset ABI");
static_assert(
    std::is_same_v<decltype(&context_word_read_00ce6950), ContextWordReadAbi>,
    "context-word read ABI");

}
