#pragma once

#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-11-H2 root accessors require an x86-32 target"
#endif

namespace openspore::reconstruction::pkg11_h2_root_accessors {

using RootWord = std::uint32_t;
using RootAccessor = RootWord (*)();

static_assert(sizeof(RootWord) == 4, "root words are 32-bit");
static_assert(sizeof(void*) == 4, "absolute slots require 32-bit pointers");

extern "C" {
RootWord root_accessor_00b3d3b0();
RootWord root_accessor_00b3d3e0();
RootWord root_accessor_00b3d3f0();
RootWord root_accessor_00b3d430();
}

}
