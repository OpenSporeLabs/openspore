#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "erase_range_shift_down_00d018d0.hpp"

namespace openspore::reconstruction::pkg_00d018d0_erase_range_shift_down {
namespace {

// The receiver as this package models it: the machine reaches displacement 0x4
// and nothing else, so the word at 0x4 is the tail and the words on either side
// are guards. A reconstruction that wrote a receiver word other than the tail,
// or read one it should not, moves a guard.
struct ReceiverFixture {
  std::uint32_t guard_before;
  OpaqueElement* tail;
  std::uint32_t guard_after;
};

static_assert(sizeof(ReceiverFixture) == 12,
              "the receiver fixture is exactly guard, tail word, guard");

constexpr std::size_t kWordsPerElement = 2U;  // two 32-bit words per element
constexpr std::size_t kBytesPerElement = 8U;
constexpr std::size_t kStorageWords = 64U;
constexpr std::size_t kMaxLiveElements = kStorageWords / kWordsPerElement;

int g_checks = 0;
int g_failures = 0;

void check(bool condition, const char* expression, const char* file, int line) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL %s:%d  %s\n", file, line, expression);
  }
}

#define CHECK(expression) \
  check(static_cast<bool>(expression), #expression, __FILE__, __LINE__)

// A word's fill is a distinct function of its index, so a copy that moves the
// wrong words, the wrong direction or the wrong count shows up as a byte
// difference rather than as a coincidence.
std::uint32_t pattern(std::size_t word_index) {
  return static_cast<std::uint32_t>(word_index * 2654435761U + 0x9e3779b9U) ^
         0xa5a5f00dU;
}

struct Workspace {
  alignas(8) std::uint32_t words[kStorageWords];
  ReceiverFixture receiver;
};

OpaqueReceiver* receiver_of(Workspace& space) {
  return reinterpret_cast<OpaqueReceiver*>(&space.receiver);
}

std::uint8_t* base_of(Workspace& space) {
  return reinterpret_cast<std::uint8_t*>(space.words);
}

// The element at `index`. Every address in this file is built as base + a byte
// offset rather than by arithmetic on OpaqueElement*, because OpaqueElement is
// deliberately an INCOMPLETE type here -- the body never interprets the 8 bytes
// it moves, and completing the type in the test would quietly assert a size the
// header refuses to claim.
OpaqueElement* element_at(Workspace& space, std::size_t index) {
  return reinterpret_cast<OpaqueElement*>(base_of(space) +
                                          index * kBytesPerElement);
}

OpaqueElement* shift(OpaqueElement* element, std::ptrdiff_t bytes) {
  return reinterpret_cast<OpaqueElement*>(reinterpret_cast<std::uint8_t*>(element) +
                                          bytes);
}

void reset(Workspace& space, std::size_t live_elements) {
  for (std::size_t index = 0; index < kStorageWords; ++index) {
    space.words[index] = pattern(index);
  }
  space.receiver.guard_before = 0x11111111U;
  space.receiver.tail = element_at(space, live_elements);
  space.receiver.guard_after = 0x22222222U;
}

// 1. The whole behavioural claim in one case: erasing a middle range moves the
// tail down over it and pulls the tail word back by the range's byte length,
// and the elements after the erased range survive in order.
void test_erase_middle_range_shifts_tail_down() {
  Workspace space{};
  reset(space, 8U);

  OpaqueElement* const returned = erase_range_shift_down_00d018d0(
      receiver_of(space), element_at(space, 2U), element_at(space, 5U));

  CHECK(returned == element_at(space, 2U));
  CHECK(space.receiver.tail == shift(element_at(space, 8U), -24));
  // Three iterations: elements 5,6,7 land at 2,3,4. So words 4..9 carry the old
  // words 10..15. Elements 0 and 1 are untouched, and everything from the old
  // tail word onward is not written at all.
  for (std::size_t index = 0; index < 2U * kWordsPerElement; ++index) {
    CHECK(space.words[index] == pattern(index));
  }
  for (std::size_t index = 0; index < 3U * kWordsPerElement; ++index) {
    const std::size_t destination = 2U * kWordsPerElement + index;
    const std::size_t source = 5U * kWordsPerElement + index;
    CHECK(space.words[destination] == pattern(source));
  }
  for (std::size_t index = 8U * kWordsPerElement; index < kStorageWords; ++index) {
    CHECK(space.words[index] == pattern(index));
  }
}

// 2. Erasing at the tail copies nothing and still moves the tail word back by
// the range's byte length. This is the path the body's JZ skips the loop for, so
// it is the case that separates "loop skipped" from "loop ran zero times".
void test_erase_at_tail_runs_no_copy() {
  Workspace space{};
  reset(space, 6U);
  const Workspace pristine = space;

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 4U),
                                        element_at(space, 6U));

  CHECK(std::memcmp(space.words, pristine.words, sizeof(space.words)) == 0);
  CHECK(space.receiver.tail == shift(element_at(space, 6U), -16));
}

// 3. An empty range at the tail changes nothing at all: no copy, and no movement
// of the tail word, because the removal it computes is zero bytes.
void test_empty_range_at_tail_changes_nothing() {
  Workspace space{};
  reset(space, 5U);
  const Workspace pristine = space;

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 5U),
                                        element_at(space, 5U));

  CHECK(std::memcmp(&space, &pristine, sizeof(space)) == 0);
}

// 4. A one-element range in the middle: the smallest non-empty removal, but
// note the trip count is NOT one -- the loop runs from `last` to the TAIL, so it
// copies three of the five elements down over the one that was erased. A
// reconstruction that ran the loop once would leave elements 3 and 4 in place
// and the tail word in the wrong place, which is exactly what this asserts.
void test_single_element_range() {
  Workspace space{};
  reset(space, 5U);

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 1U),
                                        element_at(space, 2U));

  CHECK(space.words[0] == pattern(0));
  CHECK(space.words[1] == pattern(1));
  for (std::size_t index = 0; index < 3U * kWordsPerElement; ++index) {
    const std::size_t destination = 1U * kWordsPerElement + index;
    const std::size_t source = 2U * kWordsPerElement + index;
    CHECK(space.words[destination] == pattern(source));
  }
  for (std::size_t index = 4U * kWordsPerElement; index < kStorageWords; ++index) {
    CHECK(space.words[index] == pattern(index));
  }
  CHECK(space.receiver.tail == shift(element_at(space, 5U), -8));
}

// 5. Erasing the entire live range empties the sequence: the tail word comes
// back to the base address and no word of the storage is written, because the
// read cursor starts already at the tail.
void test_erase_whole_range_empties_sequence() {
  Workspace space{};
  reset(space, 4U);
  const Workspace pristine = space;

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 0U),
                                        element_at(space, 4U));

  CHECK(space.receiver.tail == element_at(space, 0U));
  CHECK(std::memcmp(space.words, pristine.words, sizeof(space.words)) == 0);
}

// 6. The tail word is the ONLY receiver word touched. Both guards are compared
// explicitly, so a body that wrote the receiver at a neighbouring displacement
// -- 0x0 or 0x8 -- is caught here and not merely by a value mismatch elsewhere.
void test_only_the_tail_word_is_written() {
  for (std::size_t live = 2U; live <= 6U; ++live) {
    Workspace space{};
    reset(space, live);
    const std::uint32_t before_low = space.receiver.guard_before;
    const std::uint32_t before_high = space.receiver.guard_after;

    (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 0U),
                                          element_at(space, live));

    CHECK(space.receiver.guard_before == before_low);
    CHECK(space.receiver.guard_after == before_high);
  }
}

// 7. The tail word tracks the erased range exactly, across every well-formed
// shape: every (live, first, last) triple with first <= last <= live. This is
// the exhaustive check on the removal arithmetic.
void test_tail_moves_by_the_element_aligned_byte_length() {
  for (std::size_t live = 1U; live <= 8U; ++live) {
    for (std::size_t first = 0U; first <= live; ++first) {
      for (std::size_t last = first; last <= live; ++last) {
        Workspace space{};
        reset(space, live);

        (void)erase_range_shift_down_00d018d0(
            receiver_of(space), element_at(space, first), element_at(space, last));

        CHECK(space.receiver.tail ==
              shift(element_at(space, live), -static_cast<std::ptrdiff_t>(
                                                 (last - first) * kBytesPerElement)));
      }
    }
  }
}

// 8. The loop's trip count is set by the TAIL, not by `first`. A body that
// compared its read cursor against `first` instead would stop early; one that
// compared the WRITE cursor against the tail would run a different number of
// times. This asserts the exact resulting words for a one-element range at the
// very end of a nine-element sequence, where those readings diverge.
void test_trip_count_is_governed_by_the_tail() {
  Workspace space{};
  reset(space, 9U);

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 7U),
                                        element_at(space, 8U));

  // One iteration: element 8 lands at 7. Reading the trip count off `first`
  // instead would have stopped immediately and copied nothing.
  CHECK(space.words[14] == pattern(16));
  CHECK(space.words[15] == pattern(17));
  for (std::size_t index = 16U; index < kStorageWords; ++index) {
    CHECK(space.words[index] == pattern(index));
  }
  CHECK(space.receiver.tail == shift(element_at(space, 9U), -8));
}

// 9. A LONG range: the removal spans eight elements, so the tail word has to
// move sixty-four bytes, and the loop still runs from `last` (element 9) to the
// tail -- three iterations, not eight. A body that ran one iteration per erased
// element, or whose removal were the element count rather than a byte count,
// lands on a different tail word and moves different words.
void test_long_range_moves_the_tail_by_the_whole_range() {
  Workspace space{};
  reset(space, 12U);

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 1U),
                                        element_at(space, 9U));

  CHECK(space.receiver.tail == shift(element_at(space, 12U), -64));
  for (std::size_t index = 0; index < 3U * kWordsPerElement; ++index) {
    const std::size_t destination = 1U * kWordsPerElement + index;
    const std::size_t source = 9U * kWordsPerElement + index;
    CHECK(space.words[destination] == pattern(source));
  }
  for (std::size_t index = 12U * kWordsPerElement; index < kStorageWords; ++index) {
    CHECK(space.words[index] == pattern(index));
  }
}

// 10. Nothing outside [first, old_tail) is written. The words past the tail
// carry a pattern the body has no reason to produce, so any write beyond the
// live range -- the loop running one iteration too many, or the tail word being
// used as the write cursor -- is caught.
void test_nothing_beyond_the_live_range_is_written() {
  constexpr std::size_t kLive = 4U;
  Workspace space{};
  reset(space, kLive);
  constexpr std::size_t kPast = kStorageWords - kLive * kWordsPerElement;

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 1U),
                                        element_at(space, 3U));

  for (std::size_t index = 0; index < kPast; ++index) {
    CHECK(space.words[kLive * kWordsPerElement + index] ==
          pattern(kLive * kWordsPerElement + index));
  }
}

// 11. The loop copies BOTH words of each element, in order. The two words of an
// element carry distinct pattern values, so a body that copied only the first
// word, or copied the pair the other way round, is caught on every element
// rather than only at a boundary.
void test_both_words_of_each_element_are_copied() {
  Workspace space{};
  reset(space, 6U);

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 2U),
                                        element_at(space, 4U));

  // Two iterations: elements 4 and 5 land at 2 and 3.
  for (std::size_t index = 0; index < 2U * kWordsPerElement; ++index) {
    const std::size_t destination = 2U * kWordsPerElement + index;
    const std::size_t source = 4U * kWordsPerElement + index;
    CHECK(space.words[destination] == pattern(source));
  }
  CHECK(space.words[4] != pattern(6));
  CHECK(space.words[5] != pattern(7));
}

// 12. The shift is DOWNWARD: the read cursor walks up from `last` while the
// write cursor walks up from `first`, and `first` is below `last`, so the
// surviving elements land at LOWER addresses than they came from. A body that
// had the cursors the other way round would write the block below `first` and
// leave the tail elements where they were.
void test_the_shift_is_downward_not_upward() {
  Workspace space{};
  reset(space, 6U);

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 0U),
                                        element_at(space, 2U));

  // Four iterations: elements 2,3,4,5 land at 0,1,2,3.
  for (std::size_t index = 0; index < 4U * kWordsPerElement; ++index) {
    const std::size_t destination = index;
    const std::size_t source = 2U * kWordsPerElement + index;
    CHECK(space.words[destination] == pattern(source));
  }
  CHECK(space.words[0] != pattern(0));
  CHECK(space.words[1] != pattern(1));
  CHECK(space.receiver.tail == shift(element_at(space, 6U), -16));
}

// 13. The value the terminator hands back is arg1 verbatim. The body writes EAX
// once, at its first instruction, from the first stack word, and never writes it
// again -- so the return is `first`, and not the tail, not the new tail, and not
// any value the body computed.
void test_return_is_the_first_argument_verbatim() {
  Workspace space{};
  reset(space, 7U);
  OpaqueElement* const first = element_at(space, 3U);
  OpaqueElement* const last = element_at(space, 5U);
  OpaqueElement* const tail_before = space.receiver.tail;

  OpaqueElement* const returned =
      erase_range_shift_down_00d018d0(receiver_of(space), first, last);

  CHECK(returned == first);
  CHECK(returned != last);
  CHECK(returned != tail_before);
  CHECK(returned != space.receiver.tail);
}

// 14. The return tracks the argument, not the receiver. Receivers with different
// live lengths each return their own `first` argument, which rules out any value
// derived from the receiver or from the storage.
void test_return_tracks_the_argument_not_the_receiver() {
  Workspace space{};
  for (std::size_t live = 1U; live <= 6U; ++live) {
    for (std::size_t first = 0U; first < live; ++first) {
      reset(space, live);
      OpaqueElement* const expected = element_at(space, first);
      OpaqueElement* const returned = erase_range_shift_down_00d018d0(
          receiver_of(space), expected, element_at(space, live));
      CHECK(returned == expected);
    }
  }
}

// 15. The removal is the byte length of the range, not the byte length of the
// whole live sequence and not the element count left behind. The exhaustive
// sweep in case 7 covers every well-formed shape at small sizes; this repeats
// the widest one at the edge of the storage, where an off-by-one stride would
// still land inside mapped memory and go unnoticed at smaller sizes.
void test_widest_range_at_the_storage_edge() {
  Workspace space{};
  reset(space, kMaxLiveElements);

  (void)erase_range_shift_down_00d018d0(receiver_of(space), element_at(space, 0U),
                                        element_at(space, kMaxLiveElements));

  CHECK(space.receiver.tail == element_at(space, 0U));
  CHECK(space.words[0] == pattern(0));
  CHECK(space.words[1] == pattern(1));
}

void report() {
  std::printf("checks=%d failures=%d\n", g_checks, g_failures);
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_00d018d0_erase_range_shift_down

int main() {
  namespace ns = openspore::reconstruction::pkg_00d018d0_erase_range_shift_down;
  ns::test_erase_middle_range_shifts_tail_down();
  ns::test_erase_at_tail_runs_no_copy();
  ns::test_empty_range_at_tail_changes_nothing();
  ns::test_single_element_range();
  ns::test_erase_whole_range_empties_sequence();
  ns::test_only_the_tail_word_is_written();
  ns::test_tail_moves_by_the_element_aligned_byte_length();
  ns::test_trip_count_is_governed_by_the_tail();
  ns::test_long_range_moves_the_tail_by_the_whole_range();
  ns::test_nothing_beyond_the_live_range_is_written();
  ns::test_both_words_of_each_element_are_copied();
  ns::test_the_shift_is_downward_not_upward();
  ns::test_return_is_the_first_argument_verbatim();
  ns::test_return_tracks_the_argument_not_the_receiver();
  ns::test_widest_range_at_the_storage_edge();
  ns::report();
  return ns::g_failures == 0 ? 0 : 1;
}