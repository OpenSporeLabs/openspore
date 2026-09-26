#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-resource-state-safe-wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_RSS_CDECL __cdecl
#define PKG_RSS_THISCALL __thiscall
#else
#define PKG_RSS_CDECL __attribute__((cdecl))
#define PKG_RSS_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_resource_state_safe_wave10 {

using Word = std::uint32_t;

struct OpaqueRecordWrite;

using ReleaseFlag = std::uint8_t;

constexpr ReleaseFlag kReleaseFlagMask = 0x01;
constexpr ReleaseFlag kReleaseFlagBitLow = 0x00;

using DestroyPort = void(PKG_RSS_THISCALL*)(OpaqueRecordWrite*);
using UntrackPort = void(PKG_RSS_CDECL*)(void*);

struct ResourceStateSafePorts {
  DestroyPort destroy_00e30f90 = nullptr;
  UntrackPort untrack_00f47380 = nullptr;
};

static_assert(sizeof(void*) == 4, "x86-32 pointers are four bytes");
static_assert(sizeof(Word) == 4, "target words are four bytes");
static_assert(sizeof(ReleaseFlag) == 1, "the release flag is one byte wide");
static_assert(kReleaseFlagMask == 0x01u, "the observed test mask is one");
static_assert(kReleaseFlagBitLow == 0x00u,
              "the observed flag bit is the low bit");

void resource_state_safe_set_ports(ResourceStateSafePorts new_ports);
void resource_state_safe_reset_ports();

OpaqueRecordWrite* PKG_RSS_THISCALL record_write_get_state_00e310c0(
    OpaqueRecordWrite* receiver, ReleaseFlag state_release_flag);

}

#undef PKG_RSS_CDECL
#undef PKG_RSS_THISCALL
