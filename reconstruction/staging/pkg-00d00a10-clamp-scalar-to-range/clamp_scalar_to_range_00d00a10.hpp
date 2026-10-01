#pragma once

#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-00D00A10 clamp scalar to range requires an x86-32 target"
#endif

// The terminator is `RET 0xc` at 0x00d00a62, so the callee removes its own
// three 4-byte stack arguments and the caller removes none of them. That is the
// stdcall cleanup rule, and nothing else in the body contradicts it.
//
// This is declared separately from the receiver convention on purpose. The
// __thiscall below is NOT established by this function's own bytes: ECX is
// never read or written in the 20 instructions of the body, so the callee-side
// evidence cannot tell a thiscall from a stdcall. It is established by what the
// function FORWARDS -- see the note on the receiver parameter below.
#if defined(_MSC_VER)
#define PKG_00D00A10_THISCALL __thiscall
#else
#define PKG_00D00A10_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range {

// The receiver forwarded to the evaluator. The body of 0x00d00a10 never
// dereferences it -- it is passed straight through -- so nothing here knows what
// it is or how large it is. Incomplete type, no fields, no asserted size.
struct OpaqueReceiver;

// The three 32-bit values the function forwards, in the order the body reads
// them. The evidence types them `undefined4`: they are 4-byte words whose
// interpretation the listing does not settle, so they are modelled as uint32
// and no signedness is claimed. See `not_claimed` in the metadata sidecar.
using ForwardedWord = std::uint32_t;

// The two clamp bounds, at their image addresses 0x01478d5c and 0x01478d60.
//
// The values are read out of the binary, not chosen. `GhidraMCP read_memory`
// at 0x01478d5c length 12 returns
//   hex 000020c1 00002041 00010200
// whose first four bytes, little-endian, are 0xc1200000 and whose next four are
// 0x41200000. As IEEE-754 binary32 those are -10.0 and +10.0.
//
// The word `GLOBALS` is derived from those same two data references and reads
// them as the only globals this body touches; the body reads each exactly once
// and writes neither.
inline constexpr float kClampLowerBound = -10.0F;
inline constexpr float kClampUpperBound = 10.0F;

// The scalar evaluation this function forwards to and clamps.
//
// Its body is 279 instructions and is NOT reconstructed here. This is a
// declaration of the ABI the listing at 0x00d00a10 shows the callee having --
// receiver in ECX (`MOV EDI,ECX` at 0x00d05a26), three 4-byte stack arguments,
// result in ST0 (`FLD float ptr [0x01478d60]` at 0x00d05a53 through
// `RET 0xc`), callee pops 12 -- and nothing more. The model test links its own
// definition, so it controls the value that comes back.
//
// The name carries this callee's VA and not the reconstructed target's, which
// is what keeps exactly one symbol in the package embedding 00d00a10.
extern "C" float PKG_00D00A10_THISCALL evaluate_scalar_00d05a20(
    OpaqueReceiver* receiver, ForwardedWord first, ForwardedWord second,
    ForwardedWord third);

// 0x00d00a10, 85 bytes, body 0x00d00a10..0x00d00a62 inclusive: 20 instructions,
// one direct call, no branch, no indirect transfer, no stack write outside its
// own frame, and no write to memory it did not allocate.
//
// It is a wrapper, and the wrapper is the whole of it:
//
//   1. read three words off the incoming stack and push them in reverse, which
//      is the ordinary stdcall outgoing-argument sequence for a callee that pops
//      its own arguments;
//   2. call 0x00d05a20 with the receiver forwarded in ECX untouched;
//   3. clamp the returned float into [kClampLowerBound, kClampUpperBound];
//   4. return it in ST0, having never branched.
//
// The clamp is `MAXSS` against the lower bound then `MINSS` against the upper
// bound, in that order and with those operands. That order is observable and is
// what the model test pins: a NaN input leaves through the LOWER bound, not the
// upper one, because MAXSS against a non-NaN bound returns the bound.
//
// The receiver is declared here because the call sites establish it, not the
// callee. See `observed_original_abi.receiver_evidence` in the sidecar.
extern "C" float PKG_00D00A10_THISCALL clamp_scalar_to_range_00d00a10(
    OpaqueReceiver* receiver, ForwardedWord first, ForwardedWord second,
    ForwardedWord third);

}  // namespace openspore::reconstruction::pkg_00d00a10_clamp_scalar_to_range