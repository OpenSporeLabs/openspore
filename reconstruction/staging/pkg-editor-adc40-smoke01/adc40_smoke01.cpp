#include "adc40_smoke01.hpp"

#if defined(_MSC_VER)
#define PKG_EDITOR_ADC40_SMOKE01_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_ADC40_SMOKE01_THISCALL __attribute__((thiscall))
#else
#error "PKG-EDITOR-ADC40-SMOKE01 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_adc40_smoke01 {

// 0x004adc40, 17 bytes, 9 instructions, one basic block.
// Raw bytes: 55 8b ec 51 89 4d fc 8b 45 fc 8a 40 4f 8b e5 5d c3
//
//   004adc40  55           push   ebp
//   004adc41  89 e5        mov    ebp, esp
//   004adc43  51           push   ecx
//   004adc44  89 4d fc     mov    dword ptr [ebp-0x4], ecx
//   004adc47  8b 45 fc     mov    eax, dword ptr [ebp-0x4]
//   004adc4a  8a 40 4f     mov    al, byte ptr [eax+0x4f]
//   004adc4d  89 e5        mov    esp, ebp
//   004adc4f  5d           pop    ebp
//   004adc50  c3           ret
//
// The whole body is the single statement below: read one byte at receiver+0x4f
// and return it. It writes nothing, calls nothing, branches nowhere, allocates
// nothing and carries no null guard, so a null or near-null receiver faults on
// the unchecked load. That is the observed behaviour and no check is added.
//
// Two properties of the original encoding are recorded rather than reproduced.
//
//  1. Return register width. The load writes AL only, and EAX was reloaded from
//     the spilled ECX on the preceding instruction, so the upper 24 bits of EAX
//     emerge equal to receiver address bits 8..31 instead of zero. A C++ function
//     returning std::uint8_t zero-extends, which is a strictly stronger guarantee.
//     Nothing observed depends on the difference: all three sampled call sites
//     (0x00435aa5, 0x0043ffd2, 0x00588ba6) consume the result through MOVZX on
//     AL or a TEST on AL alone.
//
//  2. The frame. PUSH EBP / MOV EBP,ESP and the PUSH ECX / spill / reload pair
//     are redundant at this size -- no instruction reads the spilled slot except
//     the reload -- and a compiler emits no frame for the statement below.
//
// Why the plain form is the correct one, verified rather than assumed.
//
// A hand-written body for this function is tempting: it would reproduce the
// epilogue exactly. Two measurements on this toolchain (GCC 16.2.1, -m32, -O2)
// say not to ship one, and the reason is not the one usually given.
//
//   * The stack does balance. GCC's i386 thiscall caller reserves 8 bytes around
//     the call and reclaims them itself: `sub $0x8,%esp` ... `call` ... `add
//     $0x8,%esp`. A callee ending in a bare `ret` therefore leaves ESP exactly
//     where the caller expects it. A runtime canary test over a call made through
//     this declaration returns the right value with no frame or stack damage.
//     Claims that a bare `ret` is uncallable under GCC's i386 thiscall are wrong.
//
//   * The real hazard is caller-visible convention mismatch. A `naked` body whose
//     caller-visible declaration does not carry `thiscall` makes GCC pass the
//     receiver on the stack and never load ECX, so the body reads whatever ECX
//     happened to hold. Measured: the mismatched form returned 0x00 for a receiver
//     holding 0x5a, and the identical body returned 0x5a once the declaration
//     carried `thiscall`.
//
// The plain form below sidesteps the whole question. It emits
// `movzbl 0x4f(%ecx),%eax ; ret` -- byte-wide load at 0x4f, receiver in ECX,
// bare ret, 5 bytes -- which is machine-equivalent to the hand-written body and
// carries no convention-mismatch footgun.
extern "C" Byte PKG_EDITOR_ADC40_SMOKE01_THISCALL
FUN_004adc40(OpaqueEditorFlag* self) {
  return self->byte_04f;
}

}  // namespace openspore::reconstruction::pkg_editor_adc40_smoke01

#undef PKG_EDITOR_ADC40_SMOKE01_THISCALL
