#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-13 creature accessor requires an x86-32 target"
#endif

struct OpaqueNounManager;

namespace openspore::reconstruction::pkg13_creature_accessor {

using OpaqueNounManagerField = std::uint32_t;

extern "C" __thiscall __attribute__((naked)) OpaqueNounManagerField
pkg13_creature_accessor_00b1fdb0(OpaqueNounManager* receiver);

}
