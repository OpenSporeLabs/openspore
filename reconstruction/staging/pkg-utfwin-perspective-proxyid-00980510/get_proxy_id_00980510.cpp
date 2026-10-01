#include "get_proxy_id_00980510.hpp"

// Same narrow suppression as the header: the definition is a free function
// spelled __thiscall on purpose (see the header for why).
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

namespace openspore::reconstruction::pkg_utfwin_perspective_proxyid_00980510 {

// 0x00980510 -- UTFWin::PerspectiveEffect::GetProxyID
//
// Machine, verbatim and complete (2 instructions, 6 bytes):
//   0x00980510  MOV EAX,0x202
//   0x00980515  RET
//
// Semantics recovered:
//   * The whole body is one immediate store into EAX followed by a bare RET.
//     There is no branch, no call, no tail call, no stack read, no stack write
//     and no second instruction beyond the RET.
//   * The immediate is a full 32-bit write, so the returned value is exactly
//     0x00000202 and the upper three bytes of EAX are defined rather than
//     residual. That is why the return type is std::uint32_t and not bool or
//     a narrower integer.
//   * The body never reads ECX, so the receiver is unobservable inside the
//     body: the result is a constant function of nothing. The ECX receiver is
//     inferred from placement, not observed (see the sidecar's
//     unresolved_questions): the only reference to this address in the program
//     is the vtable slot word at 0x014440e4 = 0x014440d0 + 0x14.
//   * Zero stack words, therefore zero callee stack cleanup. A bare RET is
//     consistent with a __thiscall virtual member of no declared parameters.
//
// 0x202 is a per-class interned proxy identifier, not an address and not a
// mask: it is below any plausible code or data address in this image and the
// body performs no arithmetic on it. Sibling GetProxyID implementations in
// this binary (0x0096fec0 UTFWin::GlideEffect::GetProxyID, 0x0097e7d0
// UTFWin::ProportionalLayout::GetProxyID) return values obtained from a
// runtime registry instead, which is why this class can answer with a literal.
// What 0x202 denotes inside the ID space is not recoverable from this body.
extern "C" OpaqueWord PKG_PP_THISCALL get_proxy_id_00980510(
    PerspectiveEffect* self) {
  (void)self;
  return kPerspectiveEffectProxyId;
}

}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
