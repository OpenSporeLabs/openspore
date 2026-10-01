#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-00D20610 receiver member offset requires an x86-32 target"
#endif

// 0x00d20610 is `8d 81 c8 01 00 00 c3`: LEA EAX,[ECX+0x1c8] then a bare RET.
//
// Three facts about those seven bytes fix the convention, and none of them needs
// a callee-side stack read to establish:
//
//   * the only register read is ECX, and it is the base of the LEA's memory
//     operand. Every one of the 95 call sites in the binary loads a pointer into
//     ECX immediately before the call (measured: 92 of 95 within the preceding
//     12 instructions), and no call site pushes an argument for this callee;
//   * the RET carries no immediate, so the callee pops nothing and every caller
//     pops for itself;
//   * the function reads no stack word at all, so it consumes no stack argument
//     whether or not one is pushed.
//
// __cdecl and __stdcall are both excluded by the receiver in ECX, and __fastcall
// is not distinguishable from __thiscall on a one-ECX-argument body: for a
// single-pointer argument both place it in ECX. The receiver framing is the one
// the call sites support, so it is the one declared here; see
// `observed_original_abi.calling_convention_alternatives` in the metadata
// sidecar, which keeps the fastcall reading rather than discarding it.
#if defined(_MSC_VER)
#define PKG_00D20610_THISCALL __thiscall
#else
#define PKG_00D20610_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00d20610_receiver_member_offset {

// The receiver. The observed body never dereferences it -- LEA computes an
// address, it does not read memory -- so nothing here knows what the receiver is
// or how large it is, and this type carries no fields and asserts no size.
struct OpaqueReceiver;

// The object the returned address is computed for. Every one of the 95 call
// sites consumes the result as a POINTER (measured: 71 of 95 dereference EAX or
// copy it into another register within the following 8 instructions, and the
// sampled remainder push it as an argument), so the return is an address and
// not a value. Which member of the receiver it names is NOT known here; see
// `not_claimed` in the metadata sidecar.
struct OpaqueMember;

// The displacement of the single LEA at 0x00d20610. This is the machine's
// constant, read out of the instruction stream, not a field offset asserted
// about any layout: nothing in the observed evidence says a member exists at
// this displacement, only that this address is what the function computes.
inline constexpr std::ptrdiff_t kMemberDisplacement = 0x1c8;

// 0x00d20610, 7 bytes, body 0x00d20610..0x00d20616 inclusive: two instructions,
// no branches, no calls, no globals, no memory access.
//
// It returns `self + kMemberDisplacement` and nothing else. Every other
// behaviour is absent from the listing rather than merely unobserved.
extern "C" OpaqueMember* PKG_00D20610_THISCALL
receiver_member_offset_00d20610(OpaqueReceiver* self);

}  // namespace openspore::reconstruction::pkg_00d20610_receiver_member_offset