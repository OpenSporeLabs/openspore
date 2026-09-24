#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-12 staging requires an x86-32 target and has no 64-bit fallback"
#endif

static_assert(sizeof(void*) == sizeof(std::uint32_t),
              "PKG-12 target pointers and pointer words must both be 32-bit");

#include "space_types.hpp"

namespace openspore::reconstruction::pkg12_space {

void pkg12_space_0102d1b0(Space* space, SpaceContext* context,
                          std::uint32_t value);

void pkg12_space_0102df20(SpaceEvent* event, Space* space,
                          SpaceContext* context);

}  // namespace openspore::reconstruction::pkg12_space
