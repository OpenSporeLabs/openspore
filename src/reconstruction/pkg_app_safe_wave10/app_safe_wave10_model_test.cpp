#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

#include "app_safe_wave10.hpp"

namespace openspore::reconstruction::pkg_app_safe_wave10 {
namespace {

static_assert(
    std::is_void<decltype(cursor_buffer_emit_0041e8b0(
        static_cast<OpaqueCursorBuffer*>(nullptr), TargetWord{0}))>::value,
    "0041e8b0 returns no value on any path");
static_assert(
    std::is_void<std::invoke_result_t<GrowAndEmit_00424010, OpaqueCursorBuffer*,
                                      TargetWord, TargetWord>>::value,
    "00424010 returns no value for 0041e8b0 to forward");

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

struct Trace {
  std::uint32_t copy_calls;
  std::uintptr_t copy_destination;
  std::uintptr_t copy_source;
  std::uint32_t copy_perform;

  std::uint32_t grow_calls;
  std::uintptr_t grow_buffer;
  TargetWord grow_cursor;
  TargetWord grow_argument;
};

Trace g_trace;

void reset_trace() { std::memset(&g_trace, 0, sizeof(g_trace)); }

OpaqueCursorElement* PKG_APP_SAFE_WAVE10_THISCALL trace_copy_element_00511140(
    OpaqueCursorElement* destination, const OpaqueCursorElement* source) {
  ++g_trace.copy_calls;
  g_trace.copy_destination = reinterpret_cast<std::uintptr_t>(destination);
  g_trace.copy_source = reinterpret_cast<std::uintptr_t>(source);
  if (g_trace.copy_perform != 0u) {
    std::memcpy(destination, source, sizeof(OpaqueCursorElement));
  }
  return destination;
}

void PKG_APP_SAFE_WAVE10_THISCALL trace_grow_and_emit_00424010(
    OpaqueCursorBuffer* buffer, TargetWord cursor, TargetWord argument) {
  ++g_trace.grow_calls;
  g_trace.grow_buffer = reinterpret_cast<std::uintptr_t>(buffer);
  g_trace.grow_cursor = cursor;
  g_trace.grow_argument = argument;
}

struct PortScope {
  CopyElement_00511140 saved_copy;
  GrowAndEmit_00424010 saved_grow;

  PortScope()
      : saved_copy(cursor_runtime().copy_element_00511140),
        saved_grow(cursor_runtime().grow_and_emit_00424010) {
    cursor_runtime().copy_element_00511140 = trace_copy_element_00511140;
    cursor_runtime().grow_and_emit_00424010 = trace_grow_and_emit_00424010;
    reset_trace();
  }

  ~PortScope() {
    cursor_runtime().copy_element_00511140 = saved_copy;
    cursor_runtime().grow_and_emit_00424010 = saved_grow;
    reset_trace();
  }

  PortScope(const PortScope&) = delete;
  PortScope& operator=(const PortScope&) = delete;
};

TargetWord bits_of(TargetFloat value) {
  TargetWord bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  return bits;
}

TargetFloat float_of(TargetWord bits) {
  TargetFloat value = 0.0f;
  std::memcpy(&value, &bits, sizeof(value));
  return value;
}

std::array<TargetByte, 0x18> g_element_storage;
std::array<TargetByte, 0x18> g_source_storage;
std::array<TargetByte, 0x18> g_slot_storage;

OpaqueCursorElement* element_storage() {
  return reinterpret_cast<OpaqueCursorElement*>(g_element_storage.data());
}

const OpaqueCursorElement* source_storage() {
  return reinterpret_cast<const OpaqueCursorElement*>(g_source_storage.data());
}

OpaquePropertySlot* slot_storage() {
  return reinterpret_cast<OpaquePropertySlot*>(g_slot_storage.data());
}

void fill_slot(TargetWord stored, TargetHalf flags, TargetHalf kind) {
  std::memset(g_slot_storage.data(), 0, g_slot_storage.size());
  std::memcpy(&g_slot_storage[0x00], &stored, sizeof(stored));
  std::memcpy(&g_slot_storage[0x10], &flags, sizeof(flags));
  std::memcpy(&g_slot_storage[0x12], &kind, sizeof(kind));
}

void test_vector3_add_returns_destination() {
  OpaqueVector3 destination{0.0f, 0.0f, 0.0f};
  const OpaqueVector3 left{1.0f, 2.0f, 3.0f};
  const OpaqueVector3 right{10.0f, 20.0f, 30.0f};
  OpaqueVector3* const returned =
      vector3_add_0041dc10(&destination, &left, &right);
  check(returned == &destination, "0041dc10 returns the destination pointer");
  check(destination.x == 11.0f, "0041dc10 sums the first component");
  check(destination.y == 22.0f, "0041dc10 sums the second component");
  check(destination.z == 33.0f, "0041dc10 sums the third component");
}

void test_vector3_add_exact_alias() {
  OpaqueVector3 accumulator{1.0f, 2.0f, 3.0f};
  const OpaqueVector3 addend{0.5f, 0.25f, 0.125f};
  vector3_add_0041dc10(&accumulator, &accumulator, &addend);
  check(accumulator.x == 1.5f, "0041dc10 adds in place on the left operand");
  check(accumulator.y == 2.25f, "0041dc10 adds in place on the left y");
  check(accumulator.z == 3.125f, "0041dc10 adds in place on the left z");

  OpaqueVector3 left{4.0f, 5.0f, 6.0f};
  const OpaqueVector3 right{-4.0f, -5.0f, -6.0f};
  vector3_add_0041dc10(&left, &left, &right);
  check(left.x == 0.0f, "0041dc10 cancels on the aliased right operand");
  check(bits_of(left.x) == 0u, "0041dc10 cancellation is positive zero");
  check(left.y == 0.0f, "0041dc10 cancels the aliased right y");
  check(left.z == 0.0f, "0041dc10 cancels the aliased right z");
}

void test_vector3_add_partial_overlap() {
  TargetFloat slots[6] = {1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f};
  const TargetFloat expect_one = slots[0] + slots[3];
  const TargetFloat expect_two = slots[1] + slots[4];
  const TargetFloat expect_three = slots[2] + slots[5];
  auto* const left = reinterpret_cast<const OpaqueVector3*>(&slots[0]);
  auto* const right = reinterpret_cast<const OpaqueVector3*>(&slots[3]);
  auto* const destination = reinterpret_cast<OpaqueVector3*>(&slots[1]);
  OpaqueVector3* const returned =
      vector3_add_0041dc10(destination, left, right);
  check(returned == destination,
        "0041dc10 returns the overlapping destination");
  check(slots[0] == 1.0f, "0041dc10 leaves the leading operand word alone");
  check(slots[1] == expect_one, "0041dc10 reads every operand before storing");
  check(slots[2] == expect_two, "0041dc10 overlap survives the second store");
  check(slots[3] == expect_three, "0041dc10 overlap survives the third store");
  check(slots[4] == 16.0f, "0041dc10 leaves the trailing operand word alone");
  check(slots[5] == 32.0f, "0041dc10 leaves the last operand word alone");
}

void test_vector3_add_ieee_edges() {
  const TargetFloat negative_zero = -0.0f;
  const TargetFloat positive_zero = 0.0f;
  OpaqueVector3 destination{0.0f, 0.0f, 0.0f};
  const OpaqueVector3 zero{positive_zero, positive_zero, positive_zero};
  const OpaqueVector3 negative{negative_zero, negative_zero, negative_zero};
  vector3_add_0041dc10(&destination, &zero, &negative);
  check(bits_of(destination.x) == 0x00000000u,
        "0041dc10 turns negative zero plus positive zero into positive zero");

  const TargetFloat infinity = float_of(0x7f800000u);
  const TargetFloat negative_infinity = float_of(0xff800000u);
  OpaqueVector3 span{0.0f, 0.0f, 0.0f};
  const OpaqueVector3 big{infinity, infinity, negative_infinity};
  const OpaqueVector3 small{1.0f, -1.0f, 1.0f};
  vector3_add_0041dc10(&span, &big, &small);
  check(bits_of(span.x) == 0x7f800000u, "0041dc10 keeps positive infinity");
  check(bits_of(span.y) == 0x7f800000u, "0041dc10 keeps infinity on minus one");
  check(bits_of(span.z) == 0xff800000u, "0041dc10 keeps negative infinity");

  OpaqueVector3 clash{0.0f, 0.0f, 0.0f};
  const OpaqueVector3 upward{infinity, infinity, negative_infinity};
  const OpaqueVector3 downward{negative_infinity, 1.0f, infinity};
  vector3_add_0041dc10(&clash, &upward, &downward);
  const TargetWord produced = bits_of(clash.x);
  const TargetWord reversed = bits_of(clash.z);
  check((produced & 0x7f800000u) == 0x7f800000u,
        "0041dc10 produces a NaN from an infinity clash");
  check((produced & 0x007fffffu) != 0u,
        "0041dc10 NaN keeps a payload mantissa");
  check(bits_of(clash.y) == 0x7f800000u,
        "0041dc10 keeps a finite infinity pair per lane");
  check((reversed & 0x7f800000u) == 0x7f800000u,
        "0041dc10 clashes every lane independently");
  check((reversed & 0x007fffffu) != 0u,
        "0041dc10 keeps a payload on the reversed lane");

  const TargetFloat denormal = float_of(0x00000001u);
  OpaqueVector3 tiny{0.0f, 0.0f, 0.0f};
  const OpaqueVector3 tiny_left{denormal, denormal, denormal};
  const OpaqueVector3 tiny_right{0.0f, 0.0f, 0.0f};
  vector3_add_0041dc10(&tiny, &tiny_left, &tiny_right);
  check(bits_of(tiny.x) == 0x00000001u, "0041dc10 keeps subnormal precision");
  check(bits_of(tiny.z) == 0x00000001u, "0041dc10 keeps subnormals per lane");

  OpaqueVector3 subnormal_sum{0.0f, 0.0f, 0.0f};
  const OpaqueVector3 min_subnormal{denormal, denormal, denormal};
  const OpaqueVector3 second_min{denormal, denormal, denormal};
  vector3_add_0041dc10(&subnormal_sum, &min_subnormal, &second_min);
  check(bits_of(subnormal_sum.x) == 0x00000002u,
        "0041dc10 adds subnormals without underflow to zero");
  check(bits_of(subnormal_sum.z) == 0x00000002u,
        "0041dc10 sums subnormal lanes the same way");

  OpaqueVector3 exact{0.0f, 0.0f, 0.0f};
  const OpaqueVector3 one_ulp{float_of(0x3f800001u), float_of(0x3f800001u),
                              float_of(0x3f800001u)};
  const OpaqueVector3 second_ulp{float_of(0x3f800001u), float_of(0x3f800001u),
                                 float_of(0x3f800001u)};
  vector3_add_0041dc10(&exact, &one_ulp, &second_ulp);
  check(bits_of(exact.x) == 0x40000001u,
        "0041dc10 keeps the 24-bit mantissa sum exact");
  check(bits_of(exact.z) == 0x40000001u,
        "0041dc10 keeps the mantissa sum exact per lane");
}

void test_cursor_gate_is_unsigned() {
  PortScope scope;
  OpaqueCursorBuffer buffer{0u, 0xffffffffu, 1u};
  cursor_buffer_emit_0041e8b0(&buffer, 0u);
  check(g_trace.grow_calls == 1u,
        "0041e8b0 grows when an unsigned cursor exceeds the limit");
  check(g_trace.copy_calls == 0u, "0041e8b0 skips the copy on the grow path");
  check(g_trace.grow_cursor == 0xffffffffu,
        "0041e8b0 hands the raw cursor over");
  check(g_trace.grow_buffer == reinterpret_cast<std::uintptr_t>(&buffer),
        "0041e8b0 hands the buffer receiver to the grow port");
  check(buffer.cursor == 0xffffffffu,
        "0041e8b0 leaves the cursor to the grow port");
}

void test_cursor_gate_equal_limit() {
  PortScope scope;
  OpaqueCursorBuffer buffer{0u, 0x1000u, 0x1000u};
  cursor_buffer_emit_0041e8b0(&buffer, 0u);
  check(g_trace.grow_calls == 1u,
        "0041e8b0 grows when the cursor equals the limit");
  check(g_trace.copy_calls == 0u, "0041e8b0 does not copy at the limit");
}

void test_cursor_fast_path_copies() {
  PortScope scope;
  g_trace.copy_perform = 1u;
  std::memset(g_source_storage.data(), 0x5a, g_source_storage.size());
  std::memset(g_element_storage.data(), 0x00, g_element_storage.size());
  OpaqueCursorElement* const element = element_storage();
  OpaqueCursorBuffer buffer{0u, reinterpret_cast<std::uintptr_t>(element),
                            reinterpret_cast<std::uintptr_t>(element) + 0x18u};
  const TargetWord source_address = static_cast<TargetWord>(
      reinterpret_cast<std::uintptr_t>(source_storage()));
  cursor_buffer_emit_0041e8b0(&buffer, source_address);
  check(g_trace.copy_calls == 1u, "0041e8b0 copies once below the limit");
  check(g_trace.grow_calls == 0u, "0041e8b0 does not grow below the limit");
  check(g_trace.copy_destination == reinterpret_cast<std::uintptr_t>(element),
        "0041e8b0 passes the pre-advance cursor to the copy port");
  check(g_trace.copy_source == source_address,
        "0041e8b0 passes the argument word as the copy source");
  check(buffer.cursor == reinterpret_cast<std::uintptr_t>(element) + 0x18u,
        "0041e8b0 advances the cursor by one element stride");
  check(std::memcmp(g_element_storage.data(), g_source_storage.data(),
                    g_element_storage.size()) == 0,
        "0041e8b0 lets the copy port fill the element");
}

void test_cursor_fast_path_null_cursor() {
  PortScope scope;
  OpaqueCursorBuffer buffer{0u, 0u, 0x40u};
  cursor_buffer_emit_0041e8b0(&buffer, 0u);
  check(g_trace.copy_calls == 0u, "0041e8b0 skips a null cursor copy");
  check(g_trace.grow_calls == 0u, "0041e8b0 treats a null cursor as in range");
  check(buffer.cursor == 0x18u, "0041e8b0 still advances past a null cursor");
}

void test_cursor_fast_path_wraps() {
  PortScope scope;
  OpaqueCursorBuffer buffer{0u, 0xfffffffcu, 0xffffffffu};
  cursor_buffer_emit_0041e8b0(&buffer, 0x1234u);
  check(g_trace.copy_calls == 1u, "0041e8b0 copies through a wrapping cursor");
  check(g_trace.copy_destination == 0xfffffffcu,
        "0041e8b0 keeps the pre-wrap cursor for the copy port");
  check(g_trace.copy_source == 0x1234u,
        "0041e8b0 keeps the argument word through a wrapping cursor");
  check(buffer.cursor == 0x14u, "0041e8b0 wraps the cursor by the stride");
}

void test_cursor_last_free_slot() {
  PortScope scope;
  g_trace.copy_perform = 1u;
  std::memset(g_source_storage.data(), 0x11, g_source_storage.size());
  OpaqueCursorElement* const element = element_storage();
  const std::uintptr_t last = reinterpret_cast<std::uintptr_t>(element) + 0x18u;
  OpaqueCursorBuffer buffer{0u, last - 0x18u, last};
  const TargetWord source_address = static_cast<TargetWord>(
      reinterpret_cast<std::uintptr_t>(source_storage()));
  cursor_buffer_emit_0041e8b0(&buffer, source_address);
  check(g_trace.copy_calls == 1u, "0041e8b0 accepts the last in-range cursor");
  check(buffer.cursor == last, "0041e8b0 reaches the limit after one emit");

  g_trace.copy_perform = 0u;
  OpaqueCursorBuffer full{0u, last, last};
  cursor_buffer_emit_0041e8b0(&full, 0u);
  check(g_trace.copy_calls == 1u,
        "0041e8b0 does not copy once the limit is hit");
  check(g_trace.grow_calls == 1u, "0041e8b0 grows after the last free slot");
}

void test_property_resolve_stored_values() {
  fill_slot(0x00c0ffeeu, 0x0030u, 0x0001u);
  check(reinterpret_cast<std::uintptr_t>(
            property_value_resolve_0041e920(slot_storage())) == 0x00c0ffeeu,
        "0041e920 returns the stored word for a bool with storage bits");
  fill_slot(0x00badd00du, 0x0010u, 0x0010u);
  check(reinterpret_cast<std::uintptr_t>(
            property_value_resolve_0041e920(slot_storage())) == 0x00badd00du,
        "0041e920 returns the stored word for a void with storage bits");
  fill_slot(0x00000001u, 0x0020u, 0x0001u);
  check(reinterpret_cast<std::uintptr_t>(
            property_value_resolve_0041e920(slot_storage())) == 1u,
        "0041e920 returns a stored word of one unchanged");
}

void test_property_resolve_mask_edges() {
  const TargetHalf stored_kinds[3] = {0x0010u, 0x0020u, 0x0030u};
  for (std::size_t index = 0; index < 3u; ++index) {
    fill_slot(0x00abcdefu, stored_kinds[index], 0x0001u);
    check(reinterpret_cast<std::uintptr_t>(
              property_value_resolve_0041e920(slot_storage())) == 0x00abcdefu,
          "0041e920 honours each storage mask bit alone");
  }
  const TargetHalf self_kinds[3] = {0x0000u, 0x000fu, 0x0040u};
  for (std::size_t index = 0; index < 3u; ++index) {
    fill_slot(0x00abcdefu, self_kinds[index], 0x0010u);
    check(property_value_resolve_0041e920(slot_storage()) ==
              reinterpret_cast<const TargetByte*>(slot_storage()),
          "0041e920 falls back to the slot without storage bits");
  }
}

void test_property_resolve_self_and_sentinel() {
  fill_slot(0x00abcdefu, 0x0000u, 0x0001u);
  check(property_value_resolve_0041e920(slot_storage()) ==
            reinterpret_cast<const TargetByte*>(slot_storage()),
        "0041e920 returns the slot pointer for a bool without storage bits");
  fill_slot(0x00abcdefu, 0x0000u, 0x0010u);
  check(property_value_resolve_0041e920(slot_storage()) ==
            reinterpret_cast<const TargetByte*>(slot_storage()),
        "0041e920 returns the slot pointer for a void without storage bits");

  const TargetWord sentinel_address = 0x015d115du;
  const TargetHalf rejected[6] = {0x0000u, 0x0002u, 0x000fu,
                                  0x0011u, 0x0020u, 0x0100u};
  for (std::size_t index = 0; index < 6u; ++index) {
    fill_slot(0x00abcdefu, 0x0030u, rejected[index]);
    check(reinterpret_cast<std::uintptr_t>(property_value_resolve_0041e920(
              slot_storage())) == sentinel_address,
          "0041e920 returns the sentinel for an unsupported kind");
  }
  fill_slot(0x00abcdefu, 0x0000u, 0x0000u);
  check(reinterpret_cast<std::uintptr_t>(property_value_resolve_0041e920(
            slot_storage())) == sentinel_address,
        "0041e920 never reaches the null branch for a zero kind");
}

void test_property_resolve_reads_a_half_word() {
  const TargetWord stored = 0x0055aa55u;
  const auto* const self = reinterpret_cast<const TargetByte*>(slot_storage());

  std::memset(g_slot_storage.data(), 0, g_slot_storage.size());
  std::memcpy(&g_slot_storage[0x00], &stored, sizeof(stored));
  const TargetWord kind_and_tail = 0x11000001u;
  std::memcpy(&g_slot_storage[0x12], &kind_and_tail, sizeof(kind_and_tail));
  check(property_value_resolve_0041e920(slot_storage()) == self,
        "0041e920 compares the kind as a 16-bit word");

  std::memset(g_slot_storage.data(), 0, g_slot_storage.size());
  std::memcpy(&g_slot_storage[0x00], &stored, sizeof(stored));
  const TargetWord void_kind_and_tail = 0x22000010u;
  std::memcpy(&g_slot_storage[0x12], &void_kind_and_tail,
              sizeof(void_kind_and_tail));
  check(property_value_resolve_0041e920(slot_storage()) == self,
        "0041e920 accepts the void kind as a 16-bit word");

  std::memset(g_slot_storage.data(), 0, g_slot_storage.size());
  std::memcpy(&g_slot_storage[0x00], &stored, sizeof(stored));
  const TargetWord storage_with_kind = 0x00010030u;
  std::memcpy(&g_slot_storage[0x10], &storage_with_kind,
              sizeof(storage_with_kind));
  check(reinterpret_cast<std::uintptr_t>(property_value_resolve_0041e920(
            slot_storage())) == static_cast<std::uintptr_t>(stored),
        "0041e920 accepts the full storage mask through a half word");
}

void test_property_sentinel_address() {
  check(reinterpret_cast<std::uintptr_t>(property_sentinel_015d115d()) ==
            0x015d115du,
        "the 0041e920 sentinel is the address 0x015d115d");
}

void run_all() {
  test_vector3_add_returns_destination();
  test_vector3_add_exact_alias();
  test_vector3_add_partial_overlap();
  test_vector3_add_ieee_edges();
  test_cursor_gate_is_unsigned();
  test_cursor_gate_equal_limit();
  test_cursor_fast_path_copies();
  test_cursor_fast_path_null_cursor();
  test_cursor_fast_path_wraps();
  test_cursor_last_free_slot();
  test_property_resolve_stored_values();
  test_property_resolve_mask_edges();
  test_property_resolve_self_and_sentinel();
  test_property_resolve_reads_a_half_word();
  test_property_sentinel_address();
}

int report() {
  if (g_failures != 0) {
    std::printf("pkg-app-safe-wave10: %d failure(s)\n", g_failures);
    return 1;
  }
  std::printf("pkg-app-safe-wave10: all checks passed\n");
  return 0;
}

}

}

int main() {
  openspore::reconstruction::pkg_app_safe_wave10::run_all();
  return openspore::reconstruction::pkg_app_safe_wave10::report();
}
