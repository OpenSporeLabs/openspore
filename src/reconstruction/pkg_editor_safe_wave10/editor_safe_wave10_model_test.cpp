#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "editor_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_EDITOR_SAFE_TEST_CDECL __cdecl
#define PKG_EDITOR_SAFE_TEST_THISCALL __thiscall
#else
#define PKG_EDITOR_SAFE_TEST_CDECL __attribute__((cdecl))
#define PKG_EDITOR_SAFE_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_safe_wave10 {
namespace {

using PublishSignature = void(PKG_EDITOR_SAFE_TEST_THISCALL*)(
    OpaqueRowPublisher*, Real, Real, Real, Word);

static_assert(std::is_same<decltype(&editor_row_publish_005a2010),
                           PublishSignature>::value,
              "005a2010 takes the receiver plus four stack words popped by"
              " RET 0x10");
static_assert(std::is_same<decltype(std::declval<PublishSignature>()(
                               std::declval<OpaqueRowPublisher*>(),
                               std::declval<Real>(), std::declval<Real>(),
                               std::declval<Real>(), std::declval<Word>())),
                           void>::value,
              "005a2010 returns nothing");
static_assert(sizeof(OpaqueRowPublisher) == 0x8c &&
                  offsetof(OpaqueRowPublisher, row_prev_74) == 0x74 &&
                  offsetof(OpaqueRowPublisher, row_next_80) == 0x80 &&
                  offsetof(OpaqueRowPublisher, row_next_88) == 0x88,
              "the receiver keeps the mirrored row at +0x74 and the primary"
              " row at +0x80");
static_assert(sizeof(Real) == 4 && sizeof(Word) == 4,
              "each row component and the gate word occupy one stack word");

void check(bool condition, const char* what) {
  if (condition) {
    return;
  }
  std::fprintf(stderr, "check failed: %s\n", what);
  std::abort();
}

Word bits_of(Real value) {
  Word raw = 0;
  std::memcpy(&raw, &value, sizeof(raw));
  return raw;
}

Real value_of(Word raw) {
  Real value = 0.0f;
  std::memcpy(&value, &raw, sizeof(value));
  return value;
}

Word word_at(const OpaqueRowPublisher* publisher, std::size_t offset) {
  Word raw = 0;
  std::memcpy(&raw, reinterpret_cast<const std::uint8_t*>(publisher) + offset,
              sizeof(raw));
  return raw;
}

void seed_sentinel(OpaqueRowPublisher* publisher) {
  std::memset(publisher, 0xcd, sizeof(*publisher));
  publisher->row_prev_74 = -1.0f;
  publisher->row_prev_78 = -2.0f;
  publisher->row_prev_7c = -3.0f;
  publisher->row_next_80 = -4.0f;
  publisher->row_next_84 = -5.0f;
  publisher->row_next_88 = -6.0f;
}

std::uint32_t stack_probe_result = 0;
std::uint8_t stack_probe_rows[sizeof(OpaqueRowPublisher)] = {};

void PKG_EDITOR_SAFE_TEST_CDECL publish_stack_probe(
    OpaqueRowPublisher* self, Real row_x, Real row_y, Real row_z,
    Word also_previous, Word fifth_word, Word guard_low, Word guard_high) {
  std::uint32_t* const canary =
      static_cast<std::uint32_t*>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  static_cast<void>(fifth_word);
  const PublishSignature publish = &editor_row_publish_005a2010;
  publish(self, row_x, row_y, row_z, also_previous);
  check(canary[0] == 0xc0dec0deu, "stack canary below the argument block held");
  check(canary[1] == 0xfeedfaceu, "second stack canary word held");
  check(guard_low == 0x11223344u, "the word after the fourth argument held");
  check(guard_high == 0x55667788u, "the word after the fifth argument held");
  stack_probe_result = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
  std::memcpy(stack_probe_rows, self, sizeof(*self));
}

void test_row_publish_writes_primary_row_only() {
  OpaqueRowPublisher publisher{};
  seed_sentinel(&publisher);
  editor_row_publish_005a2010(&publisher, 1.0f, 2.0f, 3.0f, 0u);
  check(publisher.row_next_80 == 1.0f, "+0x80 took the first component");
  check(publisher.row_next_84 == 2.0f, "+0x84 took the second component");
  check(publisher.row_next_88 == 3.0f, "+0x88 took the third component");
  check(publisher.row_prev_74 == -1.0f, "+0x74 was left untouched");
  check(publisher.row_prev_78 == -2.0f, "+0x78 was left untouched");
  check(publisher.row_prev_7c == -3.0f, "+0x7c was left untouched");
}

void test_row_publish_mirrors_row_on_nonzero_gate() {
  OpaqueRowPublisher publisher{};
  seed_sentinel(&publisher);
  editor_row_publish_005a2010(&publisher, -4.5f, 6.25f, 1.0e20f, 1u);
  check(publisher.row_next_80 == -4.5f, "+0x80 took the first component");
  check(publisher.row_next_84 == 6.25f, "+0x84 took the second component");
  check(publisher.row_next_88 == 1.0e20f, "+0x88 took the third component");
  check(publisher.row_prev_74 == -4.5f, "+0x74 mirrored the first component");
  check(publisher.row_prev_78 == 6.25f, "+0x78 mirrored the second component");
  check(publisher.row_prev_7c == 1.0e20f, "+0x7c mirrored the third component");
}

void test_row_publish_gate_reads_only_low_byte() {
  OpaqueRowPublisher upper_only{};
  OpaqueRowPublisher upper_and_low{};
  seed_sentinel(&upper_only);
  seed_sentinel(&upper_and_low);
  editor_row_publish_005a2010(&upper_only, 8.0f, 9.0f, 10.0f, 0x00000100u);
  editor_row_publish_005a2010(&upper_and_low, 8.0f, 9.0f, 10.0f, 0x00000101u);
  check(upper_only.row_next_80 == 8.0f, "+0x80 still written for 0x100");
  check(upper_only.row_next_84 == 9.0f, "+0x84 still written for 0x100");
  check(upper_only.row_next_88 == 10.0f, "+0x88 still written for 0x100");
  check(upper_only.row_prev_74 == -1.0f, "0x100 has a zero low byte");
  check(upper_only.row_prev_78 == -2.0f, "0x100 leaves +0x78 untouched");
  check(upper_only.row_prev_7c == -3.0f, "0x100 leaves +0x7c untouched");
  check(upper_and_low.row_prev_74 == 8.0f, "0x101 has a nonzero low byte");
  check(upper_and_low.row_prev_78 == 9.0f, "0x101 mirrors +0x78");
  check(upper_and_low.row_prev_7c == 10.0f, "0x101 mirrors +0x7c");

  OpaqueRowPublisher top_byte_only{};
  seed_sentinel(&top_byte_only);
  editor_row_publish_005a2010(&top_byte_only, 1.0f, 2.0f, 3.0f, 0xff000000u);
  check(top_byte_only.row_prev_74 == -1.0f,
        "0xff000000 has a zero low byte and skips the mirror");
  check(top_byte_only.row_next_80 == 1.0f, "0xff000000 still writes +0x80");
}

void test_row_publish_binds_components_in_declared_order() {
  OpaqueRowPublisher publisher{};
  seed_sentinel(&publisher);
  editor_row_publish_005a2010(&publisher, 0.25f, 0.5f, 0.75f, 0xabcu);
  check(word_at(&publisher, 0x80) == 0x3e800000u, "+0x80 holds the first word");
  check(word_at(&publisher, 0x84) == 0x3f000000u,
        "+0x84 holds the second word");
  check(word_at(&publisher, 0x88) == 0x3f400000u, "+0x88 holds the third word");
  check(word_at(&publisher, 0x74) == 0x3e800000u, "+0x74 mirrors the first");
  check(word_at(&publisher, 0x78) == 0x3f000000u, "+0x78 mirrors the second");
  check(word_at(&publisher, 0x7c) == 0x3f400000u, "+0x7c mirrors the third");
  check(word_at(&publisher, 0x8c - 4) == 0x3f400000u,
        "the primary row ends at +0x8b");
}

void test_row_publish_preserves_exact_bit_patterns() {
  const Real negative_zero = value_of(0x80000000u);
  const Real subnormal = value_of(0x00000001u);
  const Real one_and_a_half = value_of(0x3fc00000u);
  OpaqueRowPublisher publisher{};
  seed_sentinel(&publisher);
  editor_row_publish_005a2010(&publisher, negative_zero, subnormal,
                              one_and_a_half, 0x000000ffu);
  check(bits_of(publisher.row_next_80) == 0x80000000u,
        "the negative zero sign bit survives the +0x80 move");
  check(bits_of(publisher.row_next_84) == 0x00000001u,
        "the subnormal payload survives the +0x84 move");
  check(bits_of(publisher.row_next_88) == 0x3fc00000u,
        "+0x88 keeps the third component unchanged");
  check(bits_of(publisher.row_prev_74) == 0x80000000u,
        "the mirrored negative zero keeps its sign bit");
  check(bits_of(publisher.row_prev_78) == 0x00000001u,
        "the mirrored subnormal keeps its payload");
  check(bits_of(publisher.row_prev_7c) == 0x3fc00000u,
        "the mirrored third component is unchanged");
}

void test_row_publish_leaves_opaque_prefix_untouched() {
  OpaqueRowPublisher publisher{};
  seed_sentinel(&publisher);
  for (std::size_t index = 0; index < sizeof(publisher.opaque_00_73); ++index) {
    publisher.opaque_00_73[index] = static_cast<std::uint8_t>(0x10 + index);
  }
  std::uint8_t prefix[sizeof(publisher.opaque_00_73)];
  std::memcpy(prefix, publisher.opaque_00_73, sizeof(prefix));
  std::uint8_t whole[sizeof(OpaqueRowPublisher)];
  std::memcpy(whole, &publisher, sizeof(whole));
  editor_row_publish_005a2010(&publisher, 1.0f, 2.0f, 3.0f, 0xffu);
  check(std::memcmp(prefix, publisher.opaque_00_73, sizeof(prefix)) == 0,
        "the opaque +0x00..+0x73 prefix is never written");
  check(std::memcmp(whole,
                    reinterpret_cast<const std::uint8_t*>(&publisher) + 0x74,
                    sizeof(OpaqueRowPublisher) - 0x74) != 0,
        "the six row words are the only storage the call touches");
}

void test_row_publish_overwrites_existing_row_contents() {
  OpaqueRowPublisher publisher{};
  seed_sentinel(&publisher);
  editor_row_publish_005a2010(&publisher, 5.0f, 6.0f, 7.0f, 0xffffffffu);
  check(publisher.row_next_80 == 5.0f, "the old +0x80 word is fully replaced");
  check(publisher.row_next_84 == 6.0f, "the old +0x84 word is fully replaced");
  check(publisher.row_next_88 == 7.0f, "the old +0x88 word is fully replaced");
  check(publisher.row_prev_74 == 5.0f, "the old +0x74 word is fully replaced");
  check(publisher.row_prev_78 == 6.0f, "the old +0x78 word is fully replaced");
  check(publisher.row_prev_7c == 7.0f, "the old +0x7c word is fully replaced");
}

void test_row_publish_never_reads_a_fifth_stack_word() {
  OpaqueRowPublisher first{};
  OpaqueRowPublisher second{};
  seed_sentinel(&first);
  seed_sentinel(&second);
  publish_stack_probe(&first, 1.0f, 2.0f, 3.0f, 0u, 0x00000000u, 0x11223344u,
                      0x55667788u);
  std::uint8_t with_zero_fifth[sizeof(OpaqueRowPublisher)];
  std::memcpy(with_zero_fifth, stack_probe_rows, sizeof(with_zero_fifth));
  publish_stack_probe(&second, 1.0f, 2.0f, 3.0f, 0u, 0xffffffffu, 0x11223344u,
                      0x55667788u);
  check(std::memcmp(with_zero_fifth, stack_probe_rows,
                    sizeof(with_zero_fifth)) == 0,
        "the fifth stack word never influences the observed effect");
  check(value_of(word_at(&first, 0x80)) == 1.0f, "the probe wrote +0x80");
  check(word_at(&first, 0x74) == bits_of(-1.0f),
        "the probe left the mirror row alone for a zero gate");
}

void test_row_publish_stack_discipline() {
  OpaqueRowPublisher publisher{};
  seed_sentinel(&publisher);
  publish_stack_probe(&publisher, 1.0f, 2.0f, 3.0f, 0u, 0u, 0x11223344u,
                      0x55667788u);
  check(stack_probe_result ==
            (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u),
        "the callee released exactly the four words it was given");
  check(sizeof(stack_probe_rows) == 0x8c,
        "the probe snapshots the whole observed receiver extent");
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_editor_safe_wave10;
  test_row_publish_writes_primary_row_only();
  test_row_publish_mirrors_row_on_nonzero_gate();
  test_row_publish_gate_reads_only_low_byte();
  test_row_publish_binds_components_in_declared_order();
  test_row_publish_preserves_exact_bit_patterns();
  test_row_publish_leaves_opaque_prefix_untouched();
  test_row_publish_overwrites_existing_row_contents();
  test_row_publish_never_reads_a_fifth_stack_word();
  test_row_publish_stack_discipline();
  return 0;
}

#undef PKG_EDITOR_SAFE_TEST_CDECL
#undef PKG_EDITOR_SAFE_TEST_THISCALL
