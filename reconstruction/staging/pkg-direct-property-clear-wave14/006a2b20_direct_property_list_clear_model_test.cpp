// PKG-DIRECT-PROPERTY-CLEAR-WAVE14 -- model test for the reconstruction of VA
// 0x006a2b20, App::DirectPropertyList::Clear.
//
// Plain int main(), explicit checks, no framework and no external dependency.
// Everything asserted here is fixed by the 39-instruction listing at
// 0x006a2b20..0x006a2b76:
//
//   1. the fill port (0x0092cb00) is given the word at receiver+0x38 as its
//      count and the word at receiver+0x3c as its destination, and the value it
//      stores is the immediate 0x0 (PUSH EAX / PUSH 0x0 / PUSH ECX at
//      0x006a2b2b..0x006a2b2f). So exactly that many leading dwords at that
//      destination become zero, and the word just past them is not;
//   2. the end cursor is written at receiver+0x1c and the begin cursor at
//      receiver+0x18 is not (ADD dword ptr [ESI+0x4],EAX at 0x006a2b70, with
//      [ESI+0x4] == receiver+0x1c because ESI was advanced by 0x18 at
//      0x006a2b3a);
//   3. the magic-number sequence at 0x006a2b56..0x006a2b6e leaves the end cursor
//      at the greatest multiple-of-0x18 boundary at or below where it started --
//      so a whole number of strides lands it exactly on the begin cursor and a
//      ragged span lands on the lower boundary, not a round-up and not
//      unchanged;
//   4. the fill's destination is read from receiver+0x3c and the count from
//      receiver+0x38, and swapping them is a different body;
//   5. nothing else in the receiver is touched.
//
// The receiver carries no declared layout in the reconstruction, so the test
// builds the smallest object that satisfies the four words the body reads and
// writes, and reads them back through the same displacements so the test cannot
// silently agree with a wrong offset.

#include "006a2b20_direct_property_list_clear.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <initializer_list>

namespace {

using namespace openspore::reconstruction::pkg_direct_property_clear_wave14;

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

constexpr std::uintptr_t kBeginOffset = 0x18;
constexpr std::uintptr_t kEndOffset = 0x1c;
constexpr std::uintptr_t kFillCountOffset = 0x38;
constexpr std::uintptr_t kFillDestOffset = 0x3c;
constexpr std::uintptr_t kElementStride = 0x18;

struct FakeDirectPropertyList {
  std::uint8_t head[0x18];
  void *begin;             // +0x18
  void *end;               // +0x1c
  std::uint8_t mid[0x38 - 0x1c - sizeof(void *)];
  std::uint32_t fill_count;  // +0x38
  void *fill_dest;           // +0x3c
};

template <typename T>
T read_at(void *list, std::uintptr_t offset) {
  return *reinterpret_cast<T *>(reinterpret_cast<std::uint8_t *>(list) + offset);
}

template <typename T>
void write_at(void *list, std::uintptr_t offset, T value) {
  *reinterpret_cast<T *>(reinterpret_cast<std::uint8_t *>(list) + offset) = value;
}

// The property the magic-number sequence has to have: the end cursor is left at
// the greatest multiple-of-stride boundary at or below where it started. This
// rules out rounding up, rounding to nearest, and a zero rewind.
bool rewound_to_floor_boundary(long long span_bytes, long long span_after) {
  if (span_after < 0 || span_after >= static_cast<long long>(kElementStride)) {
    return false;
  }
  return ((span_bytes - span_after) % static_cast<long long>(kElementStride)) == 0;
}

// A distinct destination for the fill port, prefilled with a sentinel so a
// missing store is visible.
struct FillArea {
  static constexpr std::size_t kWords = 8;
  static constexpr std::uint32_t kSentinel = 0xDEADBEEFu;
  std::uint32_t words[kWords];
  FillArea() {
    for (std::size_t i = 0; i < kWords; ++i) {
      words[i] = kSentinel;
    }
  }
};

}  // namespace

int main() {
  static_assert(sizeof(FakeDirectPropertyList) >= kFillDestOffset + sizeof(void *),
                "the fake receiver must cover the +0x3c access");

  // --- 1. The fill port zeroes exactly the count from +0x38 ---------------
  {
    FakeDirectPropertyList list;
    FillArea fill;
    std::memset(&list, 0, sizeof(list));
    std::uint8_t *const base = reinterpret_cast<std::uint8_t *>(&list) + kBeginOffset;
    write_at<void *>(&list, kBeginOffset, base);
    write_at<void *>(&list, kEndOffset, base + 3 * kElementStride);
    write_at<std::uint32_t>(&list, kFillCountOffset, 4u);
    write_at<void *>(&list, kFillDestOffset, fill.words);

    app_direct_property_list_clear_006a2b20(&list);

    for (std::size_t i = 0; i < 4; ++i) {
      check_eq_ll(fill.words[i], 0, "the fill port zeroed the leading dword");
    }
    for (std::size_t i = 4; i < FillArea::kWords; ++i) {
      check_eq_ll(fill.words[i], FillArea::kSentinel,
                  "the fill port stopped at the count from +0x38");
    }
  }

  // --- 2. A zero count writes nothing, and a full count writes all ---------
  {
    FakeDirectPropertyList list;
    FillArea fill;
    std::memset(&list, 0, sizeof(list));
    std::uint8_t *const base = reinterpret_cast<std::uint8_t *>(&list) + kBeginOffset;
    write_at<void *>(&list, kBeginOffset, base);
    write_at<void *>(&list, kEndOffset, base);
    write_at<std::uint32_t>(&list, kFillCountOffset, 0u);
    write_at<void *>(&list, kFillDestOffset, fill.words);

    app_direct_property_list_clear_006a2b20(&list);

    for (std::size_t i = 0; i < FillArea::kWords; ++i) {
      check_eq_ll(fill.words[i], FillArea::kSentinel,
                  "a zero count writes nothing at the fill destination");
    }
  }
  {
    FakeDirectPropertyList list;
    FillArea fill;
    std::memset(&list, 0, sizeof(list));
    std::uint8_t *const base = reinterpret_cast<std::uint8_t *>(&list) + kBeginOffset;
    write_at<void *>(&list, kBeginOffset, base);
    write_at<void *>(&list, kEndOffset, base);
    write_at<std::uint32_t>(&list, kFillCountOffset,
                            static_cast<std::uint32_t>(FillArea::kWords));
    write_at<void *>(&list, kFillDestOffset, fill.words);

    app_direct_property_list_clear_006a2b20(&list);

    for (std::size_t i = 0; i < FillArea::kWords; ++i) {
      check_eq_ll(fill.words[i], 0, "a full count writes every dword");
    }
  }

  // --- 3. Each list fills the area named by its own +0x3c, with its own ----
  // count from its own +0x38. Two lists with different destinations and
  // different counts must each leave the other one's area untouched, so a body
  // that read the two words the other way round, or that reused one list's
  // count for the other, cannot pass.
  {
    FakeDirectPropertyList a;
    FakeDirectPropertyList b;
    FillArea fill_a;
    FillArea fill_b;
    std::memset(&a, 0, sizeof(a));
    std::memset(&b, 0, sizeof(b));
    std::uint8_t *const base_a = reinterpret_cast<std::uint8_t *>(&a) + kBeginOffset;
    std::uint8_t *const base_b = reinterpret_cast<std::uint8_t *>(&b) + kBeginOffset;
    write_at<void *>(&a, kBeginOffset, base_a);
    write_at<void *>(&a, kEndOffset, base_a);
    write_at<std::uint32_t>(&a, kFillCountOffset, 2u);
    write_at<void *>(&a, kFillDestOffset, fill_a.words);
    write_at<void *>(&b, kBeginOffset, base_b);
    write_at<void *>(&b, kEndOffset, base_b);
    write_at<std::uint32_t>(&b, kFillCountOffset, 5u);
    write_at<void *>(&b, kFillDestOffset, fill_b.words);

    app_direct_property_list_clear_006a2b20(&a);
    app_direct_property_list_clear_006a2b20(&b);

    for (std::size_t i = 0; i < 2; ++i) {
      check_eq_ll(fill_a.words[i], 0, "list A zeroed its own first two dwords");
    }
    for (std::size_t i = 2; i < FillArea::kWords; ++i) {
      check_eq_ll(fill_a.words[i], FillArea::kSentinel,
                  "list A wrote no further than its own count of 2");
    }
    for (std::size_t i = 0; i < 5; ++i) {
      check_eq_ll(fill_b.words[i], 0, "list B zeroed its own first five dwords");
    }
    for (std::size_t i = 5; i < FillArea::kWords; ++i) {
      check_eq_ll(fill_b.words[i], FillArea::kSentinel,
                  "list B wrote no further than its own count of 5");
    }
  }


  // --- 4. The rewind is the floor-to-stride of the span ------------------
  {
    const long long kRagged[] = {1, 5, 23, 0x18 + 7};
    for (std::size_t count = 0; count <= 8; ++count) {
      FakeDirectPropertyList list;
      FillArea fill;
      std::memset(&list, 0, sizeof(list));
      std::uint8_t *const base = reinterpret_cast<std::uint8_t *>(&list) + kBeginOffset;
      write_at<void *>(&list, kBeginOffset, base);
      write_at<void *>(&list, kEndOffset, base + count * kElementStride);
      write_at<std::uint32_t>(&list, kFillCountOffset, 0u);
      write_at<void *>(&list, kFillDestOffset, fill.words);

      const long long span = static_cast<long long>(
          reinterpret_cast<const std::uint8_t *>(read_at<void *>(&list, kEndOffset)) -
          reinterpret_cast<const std::uint8_t *>(read_at<void *>(&list, kBeginOffset)));
      check_eq_ll(span, static_cast<long long>(count) *
                             static_cast<long long>(kElementStride),
                  "the span is the distance between the two cursors");

      app_direct_property_list_clear_006a2b20(&list);

      const long long span_after = static_cast<long long>(
          reinterpret_cast<const std::uint8_t *>(read_at<void *>(&list, kEndOffset)) -
          reinterpret_cast<const std::uint8_t *>(read_at<void *>(&list, kBeginOffset)));
      check(rewound_to_floor_boundary(span, span_after),
            "the end cursor lands on the floor-to-stride boundary");
      check(read_at<void *>(&list, kEndOffset) == read_at<void *>(&list, kBeginOffset),
            "a well-formed span leaves the end cursor on the begin cursor");
    }
    for (std::size_t i = 0; i < sizeof(kRagged) / sizeof(kRagged[0]); ++i) {
      FakeDirectPropertyList list;
      FillArea fill;
      std::memset(&list, 0, sizeof(list));
      std::uint8_t *const base = reinterpret_cast<std::uint8_t *>(&list) + kBeginOffset;
      write_at<void *>(&list, kBeginOffset, base);
      write_at<void *>(&list, kEndOffset,
                       reinterpret_cast<std::uint8_t *>(base) + kRagged[i]);
      write_at<std::uint32_t>(&list, kFillCountOffset, 0u);
      write_at<void *>(&list, kFillDestOffset, fill.words);

      app_direct_property_list_clear_006a2b20(&list);

      const long long span_after = static_cast<long long>(
          reinterpret_cast<const std::uint8_t *>(read_at<void *>(&list, kEndOffset)) -
          reinterpret_cast<const std::uint8_t *>(read_at<void *>(&list, kBeginOffset)));
      check(rewound_to_floor_boundary(kRagged[i], span_after),
            "a ragged span lands on the floor-to-stride boundary, not a round-up "
            "or an unchanged cursor");
    }
  }

  // --- 5. Only the words the body names are touched -----------------------
  {
    FakeDirectPropertyList list;
    FillArea fill;
    std::memset(&list, 0xA5, sizeof(list));
    std::uint8_t *const raw = reinterpret_cast<std::uint8_t *>(&list);
    write_at<void *>(&list, kBeginOffset, raw + kBeginOffset);
    write_at<void *>(&list, kEndOffset, raw + kBeginOffset + 2 * kElementStride);
    write_at<std::uint32_t>(&list, kFillCountOffset, 0u);
    write_at<void *>(&list, kFillDestOffset, fill.words);

    app_direct_property_list_clear_006a2b20(&list);

    check(raw[0] == 0xA5, "the head of the receiver is untouched");
    check(raw[8] == 0xA5, "a word in the middle of the receiver is untouched");
    // The bytes just below the begin cursor and below the fill count: neither
    // is written by this body's four words, and the test's own setup does not
    // reach them either.
    check(raw[kBeginOffset - 1] == 0xA5,
          "the byte below the begin cursor is untouched");
    check(raw[kFillCountOffset - 1] == 0xA5,
          "the byte below the fill count is untouched");
    check(read_at<void *>(&list, kBeginOffset) ==
              reinterpret_cast<void *>(raw + kBeginOffset),
          "the begin cursor is not written by this body");
  }

  if (g_failures != 0) {
    std::printf("006a2b20 model test: %d of %d checks failed\n", g_failures, g_checks);
    return 1;
  }
  std::printf("006a2b20 model test: all %d checks passed\n", g_checks);
  return 0;
}
