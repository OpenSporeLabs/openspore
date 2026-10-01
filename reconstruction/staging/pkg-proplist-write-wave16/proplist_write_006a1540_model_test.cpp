// PKG-PROLIST-WRITE-WAVE16 -- focused model test for VA 0x006a1540,
// App::PropertyList::Write.
//
// The test replaces the two port-table members with recorders and asserts the
// exact call sequence, argument surface and verdict the listing mandates. The
// word port also reproduces the observable element order the live
// decompilation of 0x0093aa70 shows for a fourth argument of 0: each 4-byte
// element is byte-swapped and handed to the sink one element at a time, so the
// recorded byte stream pins down the little-endian-to-big-endian conversion as
// well as the field order.

#include <cassert>
#include <cstdint>
#include <vector>

#include "proplist_write_006a1540.hpp"

namespace openspore::reconstruction::pkg_proplist_write_wave16 {

namespace {

#if defined(_MSC_VER)
#define WAVE16_TEST_THISCALL __thiscall
#else
#define WAVE16_TEST_THISCALL __attribute__((thiscall))
#endif

enum EventKind { kWriteWords = 1, kWriteProperty = 2 };

struct Event {
  int kind;
  Word count;     // third argument of the word port
  Word mode;      // fourth argument of the word port / third of the property port
  Word word;      // the single element handed to the word port
  std::uint8_t *payload;  // entry + 0x4, for the property port
  std::vector<std::uint8_t> bytes;  // the sink bytes, for the word port
};

std::vector<Event> trace;
// Per-port call counters, so a "fail the Nth call" switch counts calls to that
// port alone rather than events of the mixed trace.
int word_call_index = 0;
int property_call_index = 0;
int fail_word_call = -1;      // zero-based index of the word call that fails
int fail_property_call = -1;  // zero-based index of the property call that fails

std::uint8_t swap_byte(std::uint8_t value) {
  return value;
}

std::uint32_t swap32(std::uint32_t value) {
  return (value >> 24) | ((value & 0x0000ff00u) << 8) | ((value & 0x00ff0000u) >> 8) |
         (value << 24);
}

void push_be32(std::vector<std::uint8_t> &out, std::uint32_t value) {
  out.push_back(static_cast<std::uint8_t>(value >> 24));
  out.push_back(static_cast<std::uint8_t>(value >> 16));
  out.push_back(static_cast<std::uint8_t>(value >> 8));
  out.push_back(static_cast<std::uint8_t>(value));
  static_cast<void>(swap_byte);
}

// Mirrors the live decompilation of 0x0093aa70 for a fourth argument of 0: the
// elements are byte-swapped one at a time and each is written as 4 bytes.
bool write_words(OpaqueStream *, const Word *values, Word count, Word mode) {
  const int call = word_call_index++;
  Event event{kWriteWords, count, mode, count == 0 ? 0u : values[0], nullptr, {}};
  for (Word index = 0; index < count; ++index) {
    push_be32(event.bytes, swap32(values[index]));
  }
  trace.push_back(event);
  return call != fail_word_call;
}

bool write_property(OpaqueStream *, std::uint8_t *payload, Word mode) {
  const int call = property_call_index++;
  Event event{kWriteProperty, 0, mode, 0, payload, {}};
  trace.push_back(event);
  return call != fail_property_call;
}

void reset(int fail_word, int fail_property) {
  trace.clear();
  word_call_index = 0;
  property_call_index = 0;
  fail_word_call = fail_word;
  fail_property_call = fail_property;
}

std::vector<Word> written_words() {
  std::vector<Word> out;
  for (const Event &event : trace) {
    if (event.kind == kWriteWords) {
      out.push_back(event.word);
    }
  }
  return out;
}

std::vector<std::uint8_t *> written_payloads() {
  std::vector<std::uint8_t *> out;
  for (const Event &event : trace) {
    if (event.kind == kWriteProperty) {
      out.push_back(event.payload);
    }
  }
  return out;
}

std::vector<int> event_kinds() {
  std::vector<int> out;
  for (const Event &event : trace) {
    out.push_back(event.kind);
  }
  return out;
}

std::vector<std::uint8_t> sink_bytes() {
  std::vector<std::uint8_t> out;
  for (const Event &event : trace) {
    if (event.kind == kWriteWords) {
      out.insert(out.end(), event.bytes.begin(), event.bytes.end());
    }
  }
  return out;
}

OpaquePropertyEntry entries[3];
OpaquePropertyList list;
// The body never dereferences the stream, so a single opaque byte stands in for
// the IStream-shaped object the machine takes in ECX-adjacent stack slot
// entry_ESP+0x4. The port signatures take the incomplete type by pointer, which
// is all the model needs.
std::uint8_t stream_storage = 0;

OpaqueStream *stream_ptr() {
  return reinterpret_cast<OpaqueStream *>(&stream_storage);
}

void build(std::int32_t count) {
  for (std::int32_t index = 0; index < 3; ++index) {
    entries[index].word_00 = 0x0A0B0C00u + static_cast<Word>(index);
    for (std::size_t byte = 0; byte < sizeof(entries[index].opaque_04_17); ++byte) {
      entries[index].opaque_04_17[byte] =
          static_cast<std::uint8_t>(0xA0u + static_cast<std::uint8_t>(index));
    }
  }
  for (std::size_t byte = 0; byte < sizeof(list.opaque_00_17); ++byte) {
    list.opaque_00_17[byte] = 0x5Au;
  }
  list.range_begin_018 = entries;
  list.range_end_01c = entries + count;
}

// 0x006a1592 JLE: a zero span skips the loop, and the count word still goes out.
void test_empty_list() {
  reset(-1, -1);
  build(0);
  assert(write_006a1540(&list, stream_ptr()));
  assert(event_kinds() == std::vector<int>{kWriteWords});
  assert(written_words() == std::vector<Word>{0u});
  // The count word is 0, so the only sink bytes are the swapped zero.
  assert(sink_bytes() == std::vector<std::uint8_t>{0, 0, 0, 0});
  assert(written_payloads().empty());
}

// Three entries: the count word first, then id and payload alternating.
void test_three_entries() {
  reset(-1, -1);
  build(3);
  assert(write_006a1540(&list, stream_ptr()));
  assert(event_kinds() ==
         std::vector<int>{kWriteWords, kWriteWords, kWriteProperty, kWriteWords,
                          kWriteProperty, kWriteWords, kWriteProperty});
  assert(written_words() ==
         std::vector<Word>{3u, 0x0A0B0C00u, 0x0A0B0C01u, 0x0A0B0C02u});
  assert(written_payloads() ==
         std::vector<std::uint8_t *>{property_entry_payload(&entries[0]),
                                     property_entry_payload(&entries[1]),
                                     property_entry_payload(&entries[2])});
  // Every word call passes a one-element count and mode 0, per 0x006a155a,
  // 0x006a155e, 0x006a15aa and 0x006a15ac.
  for (const Event &event : trace) {
    if (event.kind == kWriteWords) {
      assert(event.count == 1u);
      assert(event.mode == 0u);
    } else {
      assert(event.mode == 0u);
    }
  }
  // 0x006a15b4 hands the entry word to the callee and 0x0093aa70 swaps each
  // element before writing it, so the id 0x0A0B0C00 reaches the sink as the
  // big-endian dword 0x000C0B0A. The ids differ only in their low byte, which
  // lands first in the sink, so the order is legible byte by byte.
  // The count word is swapped too: 3 leaves this body as the big-endian dword
  // 0x03000000, i.e. 03 00 00 00.
  assert(sink_bytes() ==
         std::vector<std::uint8_t>{0x03, 0, 0, 0, 0, 0x0C, 0x0B, 0x0A, 1, 0x0C,
                                   0x0B, 0x0A, 2, 0x0C, 0x0B, 0x0A});
}

// 0x006a156f fails: the count never reaches the stream and the loop produces no
// traffic at all, because BL is zero on entry to every iteration.
void test_count_write_fails() {
  reset(0, -1);
  build(3);
  assert(!write_006a1540(&list, stream_ptr()));
  assert(event_kinds() == std::vector<int>{kWriteWords});
  assert(written_words() == std::vector<Word>{3u});
}

// 0x006a15b8 fails on the first entry id: the payload write for that entry is
// skipped and the remaining two entries are never touched.
void test_first_id_write_fails() {
  reset(1, -1);
  build(3);
  assert(!write_006a1540(&list, stream_ptr()));
  assert(event_kinds() == std::vector<int>{kWriteWords, kWriteWords});
  assert(written_words() == std::vector<Word>{3u, 0x0A0B0C00u});
}

// 0x006a15d0 fails on the first payload: entry 0 is counted as written, and
// entries 1 and 2 are skipped without being read.
void test_first_payload_write_fails() {
  reset(-1, 0);
  build(3);
  assert(!write_006a1540(&list, stream_ptr()));
  assert(event_kinds() ==
         std::vector<int>{kWriteWords, kWriteWords, kWriteProperty});
  assert(written_words() == std::vector<Word>{3u, 0x0A0B0C00u});
}

// A failure on the LAST entry still returns false: the verdict is the running
// BL, not "was anything written".
void test_last_payload_write_fails() {
  reset(-1, 2);
  build(3);
  assert(!write_006a1540(&list, stream_ptr()));
  assert(event_kinds() ==
         std::vector<int>{kWriteWords, kWriteWords, kWriteProperty, kWriteWords,
                          kWriteProperty, kWriteWords, kWriteProperty});
  assert(written_words() ==
         std::vector<Word>{3u, 0x0A0B0C00u, 0x0A0B0C01u, 0x0A0B0C02u});
}

// 0x006a155a4: the loop bound is re-read from the receiver after the count has
// been written. Widening the range between the two calls is not possible from
// this body, but the test pins the fact that the count word and the loop bound
// are the same quotient on an unmodified receiver.
void test_count_word_matches_iterations() {
  reset(-1, -1);
  build(2);
  assert(write_006a1540(&list, stream_ptr()));
  assert(written_words().size() == 3u);       // count + two ids
  assert(written_words().front() == 2u);      // the count word is the quotient
  assert(written_payloads().size() == 2u);    // and it bounded the loop too
}

// A negative span -- end below begin -- makes the signed quotient negative, so
// the count word carries the negative value and the signed JLE skips the loop.
void test_negative_span() {
  reset(-1, -1);
  build(3);
  list.range_end_01c = entries - 1;
  assert(write_006a1540(&list, stream_ptr()));
  assert(event_kinds() == std::vector<int>{kWriteWords});
  assert(written_words() == std::vector<Word>{0xFFFFFFFFu});
}

} // namespace

} // namespace openspore::reconstruction::pkg_proplist_write_wave16

int main() {
  using namespace openspore::reconstruction::pkg_proplist_write_wave16;
  NativePorts &ports = proplist_write_native_ports();
  ports.write_words_0093aa70 = &write_words;
  ports.write_property_00693390 = &write_property;

  test_empty_list();
  test_three_entries();
  test_count_write_fails();
  test_first_id_write_fails();
  test_first_payload_write_fails();
  test_last_payload_write_fails();
  test_count_word_matches_iterations();
  test_negative_span();
  return 0;
}
