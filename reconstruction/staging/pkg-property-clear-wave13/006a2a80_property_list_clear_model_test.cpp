// PKG-PROPERTY-CLEAR-WAVE13 -- model test for the reconstruction of VA
// 0x006a2a80, App::PropertyList::Clear.
//
// Plain int main(), explicit checks, no framework and no external dependency.
// The two ports this body calls are package-local in the reconstruction, so
// this test checks what the body observably does to the receiver rather than
// what it hands the ports. Everything asserted here is fixed by the 36-
// instruction listing at 0x006a2a80..0x006a2acc:
//
//   1. the two cursors are read from receiver+0x18 and receiver+0x1c, and the
//      span sub-object is formed at receiver+0x18 (LEA ESI,[EBX+0x18]);
//   2. the magic-number sequence at 0x006a2aa8..0x006a2ac1 computes the
//      negated span rounded DOWN to a multiple of the 0x18 element stride, for
//      spans of every size -- not merely for the well-formed multiples;
//   3. the end cursor is then advanced by that rewind (ADD [ESI+4],EDX), which
//      for a well-formed span lands it exactly on the begin cursor;
//   4. the word at receiver+0x34 is incremented exactly once, on every path
//      (INC dword ptr [EBX+0x34] at 0x006a2ac6, with no branch around it);
//   5. an empty range (begin == end) is still counted, because the increment is
//      unconditional and the body has no conditional branch at all.
//
// The receiver carries no declared layout in the reconstruction, so the test
// builds the smallest object that satisfies the three words the body reads and
// writes, and reads the cursors back the way the body does -- through the same
// displacements -- so the test cannot silently agree with a wrong offset.

#include "006a2a80_property_list_clear.hpp"

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace {

using namespace openspore::reconstruction::pkg_property_clear_wave13;

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char *what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL: %s\n", what);
  }
}

void check_eq_ll(long long got, long long want, const char *what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL: %s (got %lld, want %lld)\n", what, got, want);
  }
}

constexpr std::uintptr_t kFirstOffset = 0x18;
constexpr std::uintptr_t kEndOffset = 0x1c;
constexpr std::uintptr_t kCounterOffset = 0x34;
constexpr std::uintptr_t kElementStride = 0x18;

// The receiver: enough room for the counter, and the two cursor slots where
// the body reads them.
struct FakePropertyList {
  std::uint8_t filler[0x18];
  void *begin;        // +0x18
  void *end;          // +0x1c
  std::uint8_t mid[0x34 - 0x1c - sizeof(void *)];
  std::int32_t counter;  // +0x34
};

void *read_cursor(void *list, std::uintptr_t offset) {
  return *reinterpret_cast<void *const *>(reinterpret_cast<std::uint8_t *>(list) + offset);
}

void write_cursor(void *list, std::uintptr_t offset, void *value) {
  *reinterpret_cast<void **>(reinterpret_cast<std::uint8_t *>(list) + offset) = value;
}

std::int32_t read_counter(void *list) {
  return *reinterpret_cast<std::int32_t *>(
      reinterpret_cast<std::uint8_t *>(list) + kCounterOffset);
}

void set_up(FakePropertyList *list, std::size_t element_count) {
  std::memset(list, 0, sizeof(*list));
  std::uint8_t *const base = reinterpret_cast<std::uint8_t *>(list) + kFirstOffset;
  write_cursor(list, kFirstOffset, base);
  write_cursor(list, kEndOffset, base + element_count * kElementStride);
}

// The property the magic-number sequence has to have, stated as a property
// rather than as a re-derivation of 0xd5555555: the end cursor is left at the
// greatest multiple-of-stride boundary at or below where it started. That rules
// out rounding up, rounding to nearest, and truncating the rewind to zero, and
// it forces the end cursor exactly onto the begin cursor for a well-formed
// (stride-multiple) span.
bool rewound_to_floor_boundary(long long span_bytes, long long span_after) {
  if (span_after < 0 || span_after >= static_cast<long long>(kElementStride)) {
    return false;
  }
  return ((span_bytes - span_after) % static_cast<long long>(kElementStride)) == 0;
}

}  // namespace

int main() {
  static_assert(sizeof(FakePropertyList) >= kCounterOffset + 4,
                "the fake receiver must cover the +0x34 access");

  // --- 1. A well-formed span empties the range and counts once -----------
  {
    FakePropertyList list;
    set_up(&list, 4);
    const void *const begin = read_cursor(&list, kFirstOffset);
    const void *const end = read_cursor(&list, kEndOffset);
    check_eq_ll(reinterpret_cast<const std::uint8_t *>(end) -
                    reinterpret_cast<const std::uint8_t *>(begin),
                4 * static_cast<long long>(kElementStride),
                "the test set up a 4-element span");

    App_PropertyList_Clear_006a2a80(&list);

    check(read_cursor(&list, kEndOffset) == begin,
          "a well-formed span rewinds the end cursor onto the begin cursor");
    check_eq_ll(read_counter(&list), 1, "the counter is incremented exactly once");
  }

  // --- 2. An empty range is still counted ---------------------------------
  {
    FakePropertyList list;
    set_up(&list, 0);
    App_PropertyList_Clear_006a2a80(&list);
    check(read_cursor(&list, kEndOffset) == read_cursor(&list, kFirstOffset),
          "an empty range stays empty");
    check_eq_ll(read_counter(&list), 1,
                "the increment is unconditional, so an empty range counts too");
  }

  // --- 3. Counts accumulate, one per call ---------------------------------
  {
    FakePropertyList list;
    set_up(&list, 2);
    App_PropertyList_Clear_006a2a80(&list);
    App_PropertyList_Clear_006a2a80(&list);
    check_eq_ll(read_counter(&list), 2, "two calls increment the counter twice");
    check(read_cursor(&list, kEndOffset) == read_cursor(&list, kFirstOffset),
          "clearing an already-clear range is idempotent for the cursors");
  }

  // --- 4. The rewind is the floor-to-stride of the span -------------------
  // Driven for every element count 0..8 plus four deliberately ragged spans, so
  // a wrong stride, a rounding-up magic constant, and a truncating division
  // all show up. The ragged cases are the load-bearing ones: for them the
  // floor-to-stride rewind, a round-up rewind and a zero rewind are three
  // different answers, so a test that only used stride multiples would pass on
  // a body that rounds the wrong way.
  {
    const long long kRagged[] = {1, 5, 23, 0x18 + 7};
    for (std::size_t count = 0; count <= 8; ++count) {
      FakePropertyList list;
      set_up(&list, count);
      const long long span = static_cast<long long>(
          reinterpret_cast<const std::uint8_t *>(read_cursor(&list, kEndOffset)) -
          reinterpret_cast<const std::uint8_t *>(read_cursor(&list, kFirstOffset)));
      check_eq_ll(span, static_cast<long long>(count) *
                             static_cast<long long>(kElementStride),
                  "the span is the distance between the two cursors");

      App_PropertyList_Clear_006a2a80(&list);

      const long long span_after = static_cast<long long>(
          reinterpret_cast<const std::uint8_t *>(read_cursor(&list, kEndOffset)) -
          reinterpret_cast<const std::uint8_t *>(read_cursor(&list, kFirstOffset)));
      check(rewound_to_floor_boundary(span, span_after),
            "the end cursor lands on the floor-to-stride boundary");
      // For a well-formed span that boundary IS the begin cursor.
      check(read_cursor(&list, kEndOffset) == read_cursor(&list, kFirstOffset),
            "a well-formed span leaves the end cursor on the begin cursor");
      check_eq_ll(read_counter(&list), 1, "each call counts once");
    }
    for (std::size_t i = 0; i < sizeof(kRagged) / sizeof(kRagged[0]); ++i) {
      FakePropertyList list;
      set_up(&list, 1);
      // Force a ragged span by moving the end cursor off the stride.
      write_cursor(&list, kEndOffset,
                   reinterpret_cast<std::uint8_t *>(
                       read_cursor(&list, kFirstOffset)) + kRagged[i]);
      App_PropertyList_Clear_006a2a80(&list);
      const long long span_after = static_cast<long long>(
          reinterpret_cast<const std::uint8_t *>(read_cursor(&list, kEndOffset)) -
          reinterpret_cast<const std::uint8_t *>(read_cursor(&list, kFirstOffset)));
      check(rewound_to_floor_boundary(kRagged[i], span_after),
            "a ragged span lands on the floor-to-stride boundary, not a round-up "
            "or an unchanged cursor");
      check_eq_ll(read_counter(&list), 1, "a ragged span still counts once");
    }
  }

  // --- 5. Only the three words the body names are touched -----------------
  {
    FakePropertyList list;
    std::memset(&list, 0xA5, sizeof(list));
    set_up(&list, 3);
    // Re-apply the sentinel over the gaps, keeping only the two cursors.
    std::uint8_t *const raw = reinterpret_cast<std::uint8_t *>(&list);
    std::memset(raw, 0xA5, sizeof(list));
    write_cursor(&list, kFirstOffset, raw + kFirstOffset);
    write_cursor(&list, kEndOffset,
                 raw + kFirstOffset + 3 * kElementStride);
    std::memset(raw + kCounterOffset, 0, 4);

    App_PropertyList_Clear_006a2a80(&list);

    check(raw[kCounterOffset - 1] == 0xA5,
          "the byte below the counter is untouched");
    check(raw[kFirstOffset - 1] == 0xA5, "the byte below the begin cursor is untouched");
    check(raw[0] == 0xA5, "the head of the receiver is untouched");
    check(raw[4] == 0xA5, "a word in the middle of the receiver is untouched");
  }

  if (g_failures != 0) {
    std::printf("006a2a80 model test: %d of %d checks failed\n", g_failures, g_checks);
    return 1;
  }
  std::printf("006a2a80 model test: all %d checks passed\n", g_checks);
  return 0;
}
