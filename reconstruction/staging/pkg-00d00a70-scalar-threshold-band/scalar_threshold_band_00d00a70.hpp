#pragma once

// Reconstruction of FUN_00d00a70 @ 0x00d00a70 (SporeApp.exe 3.1.0.22).
//
// Evidence basis -- all of it read out of this target's own bytes:
//   * complete 58-instruction listing, body 0x00d00a70..0x00d00b35 inclusive,
//     every one of the 7 conditional branch targets inside that span:
//       00d00a70  83 ec 10                SUB ESP,0x10
//       00d00a73  8b 44 24 1c            MOV EAX,dword ptr [ESP+0x1c]
//       00d00a77  8b 54 24 14            MOV EDX,dword ptr [ESP+0x14]
//       00d00a7b  56                     PUSH ESI
//       00d00a7c  89 ce                  MOV ESI,ECX
//       00d00a7e  8b 4c 24 1c            MOV ECX,dword ptr [ESP+0x1c]
//       00d00a82  50                     PUSH EAX
//       00d00a83  51                     PUSH ECX
//       00d00a84  52                     PUSH EDX
//       00d00a85  89 f1                  MOV ECX,ESI
//       00d00a87  e8 94 4f ff ff         CALL 0x00d05a20
//       00d00a8c  d9 5c 24 04            FSTP dword ptr [ESP+0x4]
//       00d00a90 .. 00d00abe             clamp: MAXSS against 0x01478d5c,
//                                        then MINSS against 0x01478d60,
//                                        result stored back to [ESP+0x4]
//       00d00ac4..00d00b35               four MOVSS reads of the receiver at
//                                        +0x10,+0x14,+0x18,+0x1c and five
//                                        COMISS/branch tests, returning
//                                        immediates 2,3,4,1,0 in EAX
//   * `GhidraMCP read_memory` at 0x01478d5c length 8 returns
//     `00 00 20 c1 00 00 20 41`, i.e. the two IEEE-754 binary32 words
//     0xc1200000 = -10.0f and 0x41200000 = +10.0f. Those are the clamp bounds.
//   * caller-side corroboration of the return register: at 0x00ae2e33 and
//     0x00bef633 the two instructions after the CALL are `CMP EAX,0x1` /
//     `CMP EAX,0x4` feeding SETLE / SETGE, so the result is read out of EAX as
//     a small integer.
//
// A CONTRADICTION with the derived ABI record, resolved against it here:
// `abi_derived` reports `return_register: "ST0"` and
// `return_semantics: "float_or_x87_in_ST0"`. The listing refutes that. Every
// one of the five exits materialises an integer immediate into EAX
// (`MOV EAX,0x2`, `MOV EAX,0x3`, `MOV EAX,0x4`, `MOV EAX,0x1`, `XOR EAX,EAX`),
// and the x87 register ST0 is consumed and dead by 0x00d00a8c (`FSTP`). The
// record's own inference RT1 says it only looked for "an x87 or SSE instruction
// in the body" and rated itself APPROXIMATION; that heuristic fired on the FSTP
// and on the clamp, neither of which returns. This package therefore declares
// EAX, and says so in `conflicts` in the metadata sidecar.
//
// WHAT THE BODY IS, AS A TRANSCRIPTION AND NOTHING MORE:
//
//   v = evaluate_scalar_00d05a20(receiver, w1, w2, w3);       // 0x00d00a87
//   v = maxss(v, kClampLowerBound);                          // 0x00d00ab2
//   v = minss(v, kClampUpperBound);                          // 0x00d00ab8
//   // then, in THIS order, first match wins:
//   if (f14 <  v && v <  f18) return 2;                       // 0x00d00ad2..0x00d00ade
//   if (f18 <= v && v <  f1c) return 3;                       // 0x00d00aee..0x00d00afa
//   if (f1c <= v)           return 4;                         // 0x00d00b0a..0x00d00b0c
//   if (v <= f14 && f10 <  v) return 1;                       // 0x00d00b1b..0x00d00b23
//   return 0;                                                 // 0x00d00b2f
//
// WITH ASCENDING THRESHOLDS (f10 <= f14 <= f18 <= f1c) that partitions as
// (-inf,f10] -> 0, (f10,f14] -> 1, (f14,f18) -> 2, [f18,f1c) -> 3,
// [f1c,+inf) -> 4 -- note band 2 is open at BOTH ends and band 1 is closed at
// its top, which is what the listing does and not what a tidy interval search
// would do. Ascending order is NOT asserted by this package: the body never
// compares two receiver floats to each other, so the ascending case is a
// statement about the fixtures, not a claim about the receiver.
//
// The comparisons are modelled through the exact CF/ZF that COMISS produces,
// NOT through C++ `<`/`<=`, because the two differ on an unordered compare.
// `COMISS` sets CF=ZF=PF=1 when either operand is NaN, so `JBE` is TAKEN and
// `JC` is TAKEN. C++ `a <= b` is FALSE in that case. Any of the four receiver
// floats can carry a NaN and the listing's answers then differ from the
// arithmetic reading; `comiss_jbe` / `comiss_jc` below reproduce the machine.
//
// What is NOT claimed: the receiver's class, what the four floats mean, whether
// they are ascending, what the three forwarded words are, what the callee at
// 0x00d05a20 computes, and anything about the original process. See `not_claimed`
// in the metadata sidecar.

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-00D00A70 scalar threshold band requires an x86-32 target"
#endif

// `RET 0xc` at 0x00d00b03 and 0x00d00b15 and 0x00d00b2c and 0x00d00b35: the
// callee pops its own three 4-byte arguments. The receiver arrives in ECX
// (`MOV ESI,ECX` at 0x00d00a7c, then every field read is through ESI), so the
// convention is __thiscall with callee cleanup. ESI is saved and restored
// (`PUSH ESI` at 0x00d00a7b, `POP ESI` on all five exits).
#if defined(_MSC_VER)
#define PKG_00D00A70_THISCALL __thiscall
#else
#define PKG_00D00A70_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00d00a70_scalar_threshold_band {

// Not constexpr: `__builtin_memcpy` is not a constant expression in C++17 and
// the pattern is only ever needed at run time. The two clamp bounds are pinned
// at run time by the model test, which reads the same two global words back
// out of memory.
inline std::uint32_t float_bits(float value) {
  std::uint32_t bits = 0;
  __builtin_memcpy(&bits, &value, sizeof(bits));
  return bits;
}

// NaN detection written as `v != v` rather than std::isnan so the model does
// not depend on <cmath> and cannot be folded away by a fast-math build.
constexpr bool unordered_self(float value) { return value != value; }

// The exact flag pair COMISS a,b leaves, restricted to CF and ZF, which are
// the only flags either branch of this body reads. `isnan` is spelled `v != v`
// so the answer is the unordered predicate the instruction actually computes.
struct ComissFlags {
  bool cf;  // a < b, or unordered
  bool zf;  // a == b, or unordered
};

constexpr ComissFlags comiss_flags(float a, float b) {
  return unordered_self(a) || unordered_self(b) ? ComissFlags{true, true}
                                                : ComissFlags{a < b, a == b};
}

// `JBE` after `COMISS a,b`: taken when CF or ZF is set.
constexpr bool comiss_jbe(float a, float b) {
  const ComissFlags flags = comiss_flags(a, b);
  return flags.cf || flags.zf;
}

// `JC` after `COMISS a,b`: taken when CF is set.
constexpr bool comiss_jc(float a, float b) { return comiss_flags(a, b).cf; }

// `MAXSS dst,src`: on an unordered operand pair the destination takes the
// SECOND source, which here is the memory operand -- the lower bound.
constexpr float maxss(float dst, float src) {
  return (unordered_self(dst) || unordered_self(src)) ? src
                                                      : (dst > src ? dst : src);
}

// `MINSS dst,src`: same rule, the second source is the upper bound. The value
// reaching this call is never NaN (the MAXSS above already folded it onto the
// lower bound), so the unordered arm is unreachable from the reconstruction and
// is spelled anyway rather than left to chance.
constexpr float minss(float dst, float src) {
  return (unordered_self(dst) || unordered_self(src)) ? src
                                                      : (dst < src ? dst : src);
}

// The receiver. Modelled at exactly the width the body reaches: the last
// displacement it reads is +0x1c and the access there is 4 bytes, so the
// modelled extent is 0x20. Bytes 0x00..0x0f are never read or written by this
// body. The four floats are named for the ROLE the listing gives them -- a
// compared edge, at a stated displacement -- and nothing else: no evidence here
// says what they measure or what order they are in.
struct alignas(4) OpaqueReceiver {
  std::uint8_t opaque_prefix[0x10]{};  // 0x00..0x0f, never touched
  float band_edge_10{};                // +0x10, read at 0x00d00b1d
  float band_edge_14{};                // +0x14, read at 0x00d00ac4
  float band_edge_18{};                // +0x18, read at 0x00d00ad4
  float band_edge_1c{};                // +0x1c, read at 0x00d00af0
};

// The receiver's float reads, addressed by displacement. Spelled as an
// accessor rather than as `receiver->field` at the call sites below so that a
// mutation can move a displacement without moving a member name with it.
inline float band_edge(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const float*>(reinterpret_cast<std::uintptr_t>(receiver) +
                                         displacement);
}

// The four displacements the listing reads. Each is the machine's own 8-bit
// displacement byte, nothing else.
inline constexpr std::size_t kEdgeDisplacement10 = 0x10;
inline constexpr std::size_t kEdgeDisplacement14 = 0x14;
inline constexpr std::size_t kEdgeDisplacement18 = 0x18;
inline constexpr std::size_t kEdgeDisplacement1c = 0x1c;

// The three 4-byte words read off the incoming stack at entry_ESP+0x4,
// +0x8 and +0xc and forwarded, unmodified and in that order, to the callee.
// The derived ABI record types them `undefined4`: 4-byte words of unstated
// interpretation, so they are modelled as uint32 and no signedness is claimed.
using ForwardedWord = std::uint32_t;

// The clamp bounds, read from the two data addresses the body names.
// `read_memory` at 0x01478d5c length 8 gives `00 00 20 c1 00 00 20 41`, which
// little-endian is 0xc1200000 followed by 0x41200000. As IEEE-754 binary32
// those are exactly -10.0 and +10.0, and the static_asserts below pin the bit
// patterns so a transcription of the wrong word cannot slip through.
inline constexpr float kClampLowerBound = -10.0F;  // [0x01478d5c] @ 0x00d00ab2
inline constexpr float kClampUpperBound = 10.0F;   // [0x01478d60] @ 0x00d00ab8

// The scalar evaluation. Its body at 0x00d05a20 is 279 instructions and is NOT
// reconstructed here; this is a declaration of the ABI the listing at
// 0x00d00a70 shows that callee having -- receiver in ECX, three 4-byte stack
// arguments pushed at 0x00d00a82..0x00d00a84, float result in ST0 consumed by
// the `FSTP` at 0x00d00a8c, callee pops 12 -- and nothing more. The model test
// links its own definition, so the value that comes back is under test control.
//
// The name carries the CALLEE's VA and not the reconstructed target's, which is
// what keeps exactly one symbol in this package embedding 00d00a70.
extern "C" float PKG_00D00A70_THISCALL evaluate_scalar_00d05a20(
    OpaqueReceiver* receiver, ForwardedWord first, ForwardedWord second,
    ForwardedWord third);

// x86-32 thiscall: receiver in ECX, three callee-cleaned 4-byte arguments, and
// a 32-bit integer result in EAX.
using AbiScalarThresholdBand00d00a70 =
    std::int32_t(PKG_00D00A70_THISCALL*)(OpaqueReceiver*, ForwardedWord,
                                         ForwardedWord, ForwardedWord);

static_assert(sizeof(void*) == 4, "pointers are 32-bit");
static_assert(sizeof(float) == 4, "every float access in the body is 4 bytes wide");
static_assert(sizeof(ForwardedWord) == 4, "the forwarded stack slots are 4 bytes");
// The two bounds are pinned by their IEEE-754 binary32 PATTERNS, which
// `read_memory` gave verbatim: 0x01478d5c is `00 00 20 c1` and 0x01478d60 is
// `00 00 20 41`. A constant-expression float-to-bits conversion is C++20, so
// the pattern comparison is a run-time assert in the model test rather than a
// static_assert here; what is asserted at compile time is that the two bounds
// are ordered and straddle zero, which the MAXSS/MINSS pair requires of them.
static_assert(kClampLowerBound < 0.0F, "MAXSS lowers against a negative bound");
static_assert(kClampUpperBound > 0.0F, "MINSS raises against a positive bound");
static_assert(kClampLowerBound < kClampUpperBound,
              "the clamp is only a clamp if the lower bound is below the upper one");
static_assert(kEdgeDisplacement10 == 0x10, "MOVSS at 0x00d00b1d reads [ESI+0x10]");
static_assert(kEdgeDisplacement14 == 0x14, "MOVSS at 0x00d00ac4 reads [ESI+0x14]");
static_assert(kEdgeDisplacement18 == 0x18, "MOVSS at 0x00d00ad4 reads [ESI+0x18]");
static_assert(kEdgeDisplacement1c == 0x1c, "MOVSS at 0x00d00af0 reads [ESI+0x1c]");
static_assert(offsetof(OpaqueReceiver, band_edge_10) == 0x10, "+0x10");
static_assert(offsetof(OpaqueReceiver, band_edge_14) == 0x14, "+0x14");
static_assert(offsetof(OpaqueReceiver, band_edge_18) == 0x18, "+0x18");
static_assert(offsetof(OpaqueReceiver, band_edge_1c) == 0x1c, "+0x1c");
static_assert(sizeof(OpaqueReceiver) == 0x20,
              "the last displacement the body reaches ends the modelled extent");
static_assert(std::is_same<AbiScalarThresholdBand00d00a70,
                           std::int32_t(PKG_00D00A70_THISCALL*)(
                               OpaqueReceiver*, ForwardedWord, ForwardedWord,
                               ForwardedWord)>::value,
              "the modeled entry carries the ECX receiver and returns a 32-bit EAX value");

// Entry point under reconstruction. The name carries the 8-hex target VA so the
// validator can bind this span to 0x00d00a70, and it is this package's only
// definition that does.
std::int32_t PKG_00D00A70_THISCALL scalar_threshold_band_00d00a70(
    OpaqueReceiver* receiver, ForwardedWord first, ForwardedWord second,
    ForwardedWord third);

}  // namespace openspore::reconstruction::pkg_00d00a70_scalar_threshold_band

#undef PKG_00D00A70_THISCALL
