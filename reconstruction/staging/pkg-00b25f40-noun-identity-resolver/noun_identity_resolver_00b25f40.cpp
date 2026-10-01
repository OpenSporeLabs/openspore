#include "noun_identity_resolver_00b25f40.hpp"

// The header undefines its own convention macro, so the definition re-spells
// it. The spelling must agree with the declaration in the header: it is the
// same callee-cleans contract stated by `c2 04 00` RET 0x4 at 0x00b25f95 and
// 0x00b25f9e, and a definition that disagreed would be a different stack
// contract rather than a different spelling.
#if defined(_MSC_VER) || defined(__clang__)
#define PKG_00B25F40_THISCALL __thiscall
#else
#define PKG_00B25F40_THISCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_00b25f40 {

namespace {

// The five words the body pushes before calling 0x00b21340, in push order:
// `68 6a 81 8c 01` PUSH 0x18c816a at 0x00b25f44, `68 00 e5 b1 00` PUSH
// 0xb1e500 at 0x00b25f49, `68 c0 36 b2 00` PUSH 0xb236c0 at 0x00b25f4e,
// `68 20 d4 d3 00` PUSH 0xd3d420 at 0x00b25f53, and `68 80 10 b2 00` PUSH
// 0xb21080 at 0x00b25f58. Because the stack grows down, the last push is the
// callee's first stack argument, so the callee reads them in the reverse of
// push order -- which is the order the call below passes them in. Only the word
// values are claimed; what any of them means is not.
constexpr std::uint32_t kPushedFifth = 0x018c816aU;
constexpr std::uint32_t kPushedFourth = 0x00b1e500U;
constexpr std::uint32_t kPushedThird = 0x00b236c0U;
constexpr std::uint32_t kPushedSecond = 0x00d3d420U;
constexpr std::uint32_t kPushedFirst = 0x00b21080U;

// The element count is `(end - begin) >> 2`, computed with an arithmetic shift
// (`c1 fe 02` SAR ESI,0x2 at 0x00b25f6d), so a negative byte span yields a
// negative count and `85 f6` TEST ESI,ESI / `7e 19` JLE at
// 0x00b25f72..0x00b25f74 skips the loop entirely rather than iterating.
constexpr std::int32_t kElementShiftBits = 2;
constexpr std::intptr_t kElementStrideBytes = static_cast<std::intptr_t>(1)
                                              << kElementShiftBits;

}

// The body pushes the address 0x018c816a and never dereferences it, so this
// word carries the address value and nothing is claimed about what lives there.
std::uint32_t g_018c816a = kPushedFifth;

NativePorts g_native_ports{nullptr};

extern "C" NounObject* PKG_00B25F40_THISCALL noun_identity_resolver_00b25f40(
    NounProjection* receiver, std::uint32_t identity) {
  NounProjectionVector* const vector =
      g_native_ports.noun_projection_lookup_00b21340(
          receiver, kPushedFirst, kPushedSecond, kPushedThird, kPushedFourth,
          g_018c816a);

  const std::intptr_t byte_span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count =
      static_cast<std::int32_t>(byte_span >> kElementShiftBits);
  static_assert(kElementStrideBytes == 4,
                "SAR ESI,0x2 over a byte span divides by four");

  // container_begin is re-read inside the loop, not hoisted: the listing's loop
  // head is `8b 07` MOV EAX,[EDI] at 0x00b25f76, INSIDE the loop, so the +0x04
  // word is loaded again on every iteration. The count above is computed once,
  // before the loop, and is not recomputed. A body that froze the begin pointer
  // on the first read would walk the original array after any probe repointed
  // it.
  for (std::int32_t index = 0; index < count; ++index) {
    NounObject* const candidate = container_begin(vector)[index];
    const std::uint32_t observed =
        candidate_table(candidate)->slot_4c(candidate);
    if (observed == identity) {
      return candidate;
    }
  }
  return nullptr;
}

}

#undef PKG_00B25F40_THISCALL
