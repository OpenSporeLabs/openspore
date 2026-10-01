#pragma once

#include <cstddef>
#include <cstdint>

// Calling convention. The token `thiscall` is carried once per macro, which
// is what the validator's `_convention_defines` resolves, and the non-MSVC
// arm is the attribute form both clang and gcc accept in a -m32 unit.
#if defined(_MSC_VER)
#define PKG_FA0D50_ATOMIC_INC_THISCALL __thiscall
#else
#define PKG_FA0D50_ATOMIC_INC_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_fa0d50_atomic_inc {

using Word = std::uint32_t;

// 0x00fa0d50 is ADD ECX,0x14: the receiver arrives in ECX and is adjusted
// by 20 bytes before any memory operand names it.
constexpr std::size_t kReceiverAdjust = 0x14;
static_assert(kReceiverAdjust == 0x14, "ADD ECX,0x14 at 0x00fa0d50");

// 0x00fa0d53 is MOV EAX,0x1: the addend every XADD.LOCK exchanges in.
constexpr Word kIncrement = 0x1;
static_assert(kIncrement == 0x1, "MOV EAX,0x1 at 0x00fa0d53");

// 0x00fa0d50: non-static virtual member of some class (vptr-backed vftable
// slot), receiver in ECX, __thiscall, caller cleans, zero ordinary stack
// arguments. The class identity is not inferred.
std::uint32_t PKG_FA0D50_ATOMIC_INC_THISCALL atomic_increment_00fa0d50(std::uint8_t* receiver);

}  // namespace openspore::reconstruction::pkg_fa0d50_atomic_inc
