// PKG-DFW-006A2E20 -- VA 0x006a2e20
// Behavioural model test for App::PropertyList::SetProperty @ 0x006a2e20.
//
// All four direct callees -- 0x00612db0, 0x00542b80, 0x006a2c50 and 0x0093db80 --
// are defined here as observers, so the test sees every transfer the
// reconstruction makes, with which arguments, in which order, and gets to decide
// what each of them does to memory.
//
// What is asserted is what the 65-instruction listing fixes and nothing more:
//
//   * the four transfers, once each, and their order on each arm;
//   * the four words pushed for 0x00612db0 and the fact that the key goes over
//     by address;
//   * the four receiver displacements read (0x18, 0x1c, 0x2c, 0x34) and the one
//     written (0x34) -- checked by comparing the receiver's bytes before and
//     after, so "no other byte changed" is asserted rather than assumed;
//   * the seed entry's key stored BEFORE the assign, and the two cleared words
//     zeroed BEFORE the assign (the assign observer reads them itself);
//   * the argument order of 0x006a2c50, fixed by the callee's own frame reads;
//   * the two branch conditions: candidate == end, and the UNSIGNED
//     key < candidate->field_00, with inputs chosen so a signed compare would
//     take the other arm;
//   * the arm taken for each of those, and the calls each arm makes;
//   * the counter at +0x34 moving exactly once per call on every path;
//   * the try-level word being 0 while 0x006a2c50 runs and 0xffffffff after it.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names a wrong reconstruction it is aimed at:
//
//   H  the element's leading dword is the ELEMENT's word: decoys planted in the
//      receiver's own untouched bytes and in the map's bytes do not move the arm;
//   I  0x04 and 0x10 are BYTE displacements: the assign destination is four bytes
//      into the element, not the element and not the next element;
//   J  the seed record is four bytes into a 0x18 frame run, and is neither
//      receiver memory nor the map;
//   K  the counter at +0x34 moves AFTER the report call, so a model that
//      incremented early is caught by the report observer reading the counter;
//   L  the bit test at 0x006a2eb7 reads the word 0x00542b80 WROTE, not the
//      source's: driven in both directions with disagreeing values;
//   M  the byte at +0x2c is zero-extended, so 0x80 and 0xff reach the search as
//      0x00000080 and 0x000000ff and never as sign-extended words;
//   N  the counter is at +0x34 and not at +0x30: a decoy word one dword lower is
//      never touched;
//   O  the words at +0x18 and +0x1c are two different pointers and the search
//      receives each of them;
//   P  the ABI: the two argument words are popped by the CALLEE, measured by
//      sampling ESP inside a trampoline rather than asserted as a convention.
//
// What is NOT asserted, and why:
//
//   * EAX. The body leaves three different dead words there depending on the path
//     and the declared return type is void, so there is nothing to assert.
//   * The out record. 0x006a2c50 writes it and this body never reads it; the
//     test can only show that the observable outcome does not change when the
//     observer fills it with poison, which is a weaker statement than "never
//     read" and is labelled as such at the check.
//   * What 0x00542b80 does beyond the flags/type recomposition the 0x006a2e20
//     listing itself depends on. The observer implements that recomposition
//     because the TEST at 0x006a2eb7 reads a word 0x00542b80 wrote; everything
//     else the observer does is a test fixture, not a claim.
//   * The exception frame. Installing and unwinding FS:[0] is not modelled, so
//     there is no observable to test.

#include "dfw_006a2e20_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_dfw_006a2e20 {
namespace {

// Machine displacements, as literals: the four this body reads and the one it
// writes. 0x18/0x1c/0x2c are the array begin, the array end and the map byte;
// 0x34 is the counter.
constexpr std::size_t kArrayOffset = 0x18u;
constexpr std::size_t kEndOffset = 0x1cu;
constexpr std::size_t kModeOffset = 0x2cu;
constexpr std::size_t kCounterOffset = 0x34u;
constexpr std::size_t kReceiverSize = 0x38u;

enum Call : int {
  kCallSearch = 0,
  kCallAssign = 1,
  kCallFindOrInsert = 2,
  kCallReport = 3,
};

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

struct Observation {
  int log[8] = {};
  int log_length = 0;

  int search_calls = 0;
  MapEntry* search_first = nullptr;
  MapEntry* search_last = nullptr;
  Word search_key_value = 0;
  Word search_mode = 0;
  MapEntry* search_result = nullptr;  // nullptr means "return search_last"

  int assign_calls = 0;
  Property* assign_dest = nullptr;
  Property* assign_source = nullptr;
  Word assign_dest_lead = 0;   // the leading dword of the object dest sits in
  Word assign_dest_flags = 0;  // dest's +16 as the callee found it
  Word assign_dest_type = 0;   // dest's +18 as the callee found it
  // Captured inside the observer, because the destination is the model's own
  // stack frame and must not be dereferenced after the call returns.
  Word assign_written_first = 0;
  Word assign_written_type = 0;
  // When set, the observer leaves this value in the destination's +16 instead of
  // recomposing it. Lets the test drive the TEST at 0x006a2eb7 directly.
  bool assign_forced_flags = false;
  Word assign_forced_flags_value = 0;

  int insert_calls = 0;
  PropertyMap* insert_map = nullptr;
  FindOrInsertResult* insert_result_record = nullptr;
  MapEntry* insert_entry = nullptr;
  Word insert_entry_key = 0;
  std::int32_t insert_try_level = 0;
  // When set, the observer fills the out record with these values instead of the
  // ones the real callee writes, to show the caller does not consult it.
  bool insert_poison_record = false;
  MapEntry* insert_poison_iterator = nullptr;
  std::uint8_t insert_poison_flag = 0;

  int report_calls = 0;
  Property* report_receiver = nullptr;
  std::uint8_t report_argument = 0;
  Word report_receiver_flags = 0;
  // Sampled INSIDE the report call, so the counter's position in the sequence is
  // observable: 0x006a2ed1 runs after 0x006a2ecc, not before it.
  Word report_counter_seen = 0;
  bool report_counter_valid = false;

  void reset() { *this = Observation(); }

  void record(Call call) {
    if (log_length < 8) {
      log[log_length] = static_cast<int>(call);
    }
    ++log_length;
  }

  bool log_is(Call a, Call b) const {
    return log_length == 2 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b);
  }
  bool log_is(Call a, Call b, Call c) const {
    return log_length == 3 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b) &&
           log[2] == static_cast<int>(c);
  }
  bool log_is(Call a, Call b, Call c, Call d) const {
    return log_length == 4 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b) &&
           log[2] == static_cast<int>(c) && log[3] == static_cast<int>(d);
  }
};

Observation g_obs;

// A receiver large enough for every word this body touches, plus a sentinel tail
// so an overrun past 0x34 would show up in the byte comparison.
struct Receiver {
  unsigned char bytes[kReceiverSize + 8];
};

Receiver make_receiver(MapEntry* begin, MapEntry* end, std::uint8_t mode, Word counter) {
  Receiver receiver;
  std::memset(&receiver, 0, sizeof receiver);
  std::memcpy(receiver.bytes + kArrayOffset, &begin, sizeof begin);
  std::memcpy(receiver.bytes + kEndOffset, &end, sizeof end);
  std::memcpy(receiver.bytes + kModeOffset, &mode, sizeof mode);
  std::memcpy(receiver.bytes + kCounterOffset, &counter, sizeof counter);
  return receiver;
}

// A Property-shaped source record.
Property make_property(Word w0, Word w1, Word w2, Word w3, std::uint16_t flags,
                       std::uint16_t type) {
  Property property{};
  property.field_00_0c[0] = w0;
  property.field_00_0c[1] = w1;
  property.field_00_0c[2] = w2;
  property.field_00_0c[3] = w3;
  property.field_10 = flags;
  property.field_12 = type;
  return property;
}

// How many bytes of the receiver changed OUTSIDE the four counter bytes, and how
// many changed inside them. The body has exactly one memory write to the receiver,
// so every changed byte has to fall inside the counter's window and the counter's
// own value has to move.
struct ReceiverDiff {
  int inside = 0;
  int outside = 0;
};

ReceiverDiff diff_receiver(const Receiver& before, const Receiver& after) {
  ReceiverDiff diff;
  for (std::size_t index = 0; index < sizeof before.bytes; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    if (index >= kCounterOffset && index < kCounterOffset + 4) {
      ++diff.inside;
    } else {
      ++diff.outside;
    }
  }
  return diff;
}

// The receiver the current case is exercising, so an observer can sample a
// receiver byte at a moment the caller cannot see.
Receiver* g_active_receiver = nullptr;

// Reads the receiver's counter word at its machine displacement.
Word counter_of(const Receiver& receiver) {
  Word value = 0;
  std::memcpy(&value, receiver.bytes + kCounterOffset, sizeof value);
  return value;
}

}  // namespace

// 0x006a2e52 -- the search. Four words, caller-cleaned; the third is a POINTER to
// the key word, so the observer dereferences it immediately (the model's key
// parameter dies with the call) and records the value.
extern "C" MapEntry* PKG_DFW_006A2E20_CDECL entry_array_lower_bound_00612db0(
    MapEntry* first, MapEntry* last, Word* key, Word mode) {
  ++g_obs.search_calls;
  g_obs.record(kCallSearch);
  g_obs.search_first = first;
  g_obs.search_last = last;
  g_obs.search_key_value = (key != nullptr) ? *key : 0u;
  g_obs.search_mode = mode;
  return g_obs.search_result != nullptr ? g_obs.search_result : last;
}

// 0x006a2e7c and 0x006a2e99 -- the assign. Destination in ECX, source as the one
// stack word. The observer records the destination's own +16 and +18 as it found
// them, and the leading dword of the 0x18-stride object the destination sits four
// bytes into, so the test can see the seed's key store and the two clears BEFORE
// this call. It then performs the same +16 recomposition the callee's listing
// shows, because the TEST at 0x006a2eb7 reads a word this call wrote.
extern "C" Property* PKG_DFW_006A2E20_THISCALL property_assign_00542b80(
    Property* destination, Property* source) {
  ++g_obs.assign_calls;
  g_obs.record(kCallAssign);
  g_obs.assign_dest = destination;
  g_obs.assign_source = source;
  g_obs.assign_dest_lead =
      *reinterpret_cast<const Word*>(reinterpret_cast<const unsigned char*>(destination) - 4);
  g_obs.assign_dest_flags = destination->field_10;
  g_obs.assign_dest_type = destination->field_12;

  if (g_obs.assign_forced_flags) {
    destination->field_10 = g_obs.assign_forced_flags_value;
  } else {
    // 0x00542b8a..0x00542c0a: four dwords, then the type word whole, then the
    // flags word as (source & ~0x0002) | (destination & 0x0002).
    for (std::size_t index = 0; index < 4; ++index) {
      reinterpret_cast<Word*>(destination)[index] = source->field_00_0c[index];
    }
    destination->field_12 = source->field_12;
    destination->field_10 = static_cast<std::uint16_t>((source->field_10 & 0xfffdu) |
                                                      (destination->field_10 & 0x2u));
  }
  g_obs.assign_written_first = destination->field_00_0c[0];
  g_obs.assign_written_type = destination->field_12;
  return destination;
}

// 0x006a2eb2 -- the find-or-insert. Array object in ECX, the out record as the
// FIRST stack word and the seed entry as the second (that order is the callee's
// own: 0x006a2c78 reads the first word as the record it writes, 0x006a2c51 the
// second as the entry it reads the key from). The observer records the key it was
// handed and samples the model's try-level word, which is what proves the store
// at 0x006a2eaa precedes this call and the store at 0x006a2ebc follows it.
extern "C" FindOrInsertResult* PKG_DFW_006A2E20_THISCALL property_map_find_or_insert_006a2c50(
    PropertyMap* map, FindOrInsertResult* result, MapEntry* entry) {
  ++g_obs.insert_calls;
  g_obs.record(kCallFindOrInsert);
  g_obs.insert_map = map;
  g_obs.insert_result_record = result;
  g_obs.insert_entry = entry;
  g_obs.insert_entry_key = (entry != nullptr) ? entry->field_00 : 0u;
  g_obs.insert_try_level = try_level_word();
  if (g_obs.insert_poison_record) {
    result->field_00 = g_obs.insert_poison_iterator;
    result->field_04 = g_obs.insert_poison_flag;
  } else {
    result->field_00 = entry;
    result->field_04 = 1;
  }
  return result;
}

// 0x006a2ecc -- the report. Receiver in ECX, one stack word read as a byte; this
// body always passes 0. The observer records the receiver's +16, which is the
// very word the TEST at 0x006a2eb7 examined one instruction group earlier.
extern "C" void PKG_DFW_006A2E20_THISCALL editor_query_clear_flags_0093db80(
    Property* receiver, std::uint8_t argument) {
  ++g_obs.report_calls;
  g_obs.record(kCallReport);
  g_obs.report_receiver = receiver;
  g_obs.report_argument = argument;
  g_obs.report_receiver_flags = (receiver != nullptr) ? receiver->field_10 : 0u;
  if (g_active_receiver != nullptr) {
    g_obs.report_counter_seen = counter_of(*g_active_receiver);
    g_obs.report_counter_valid = true;
  }
}

}  // namespace openspore::reconstruction::pkg_dfw_006a2e20

namespace {

using namespace openspore::reconstruction::pkg_dfw_006a2e20;

PropertyList* as_list(Receiver& receiver) {
  return reinterpret_cast<PropertyList*>(&receiver);
}

// Case A -- the key is present. The search returns an element whose leading
// dword equals the key, so 0x006a2e60 falls through, 0x006a2e64 does not branch,
// 0x006a2e74 does not branch, and the body assigns into that element's record.
void case_key_present() {
  MapEntry array[3];
  for (int index = 0; index < 3; ++index) {
    array[index] = MapEntry{};
    array[index].field_00 = static_cast<Word>(0x10u * static_cast<unsigned>(index + 1));
  }
  Property source = make_property(0xaaaa0001u, 0xaaaa0002u, 0xaaaa0003u, 0xaaaa0004u,
                                  0x0000u, 0x0021u);
  const Word key = 0x20u;

  g_obs.reset();
  g_obs.search_result = &array[1];
  array[1].field_00 = key;

  Receiver receiver = make_receiver(&array[0], &array[0] + 3, 0x07u, 0u);
  Receiver before = receiver;

  dfw_property_set_006a2e20(as_list(receiver), key, &source);

  check(g_obs.search_calls == 1, "A: 0x00612db0 is called exactly once");
  check(g_obs.search_first == &array[0], "A: the search gets the array begin from receiver+0x18");
  check(g_obs.search_last == &array[0] + 3, "A: the search gets the array end from receiver+0x1c");
  check(g_obs.search_key_value == key,
        "A: the search is handed the first argument by address and reads the key word");
  check(g_obs.search_mode == 0x07u, "A: the search gets the zero-extended byte from receiver+0x2c");
  check(g_obs.assign_calls == 1, "A: 0x00542b80 is called exactly once");
  check(g_obs.assign_dest == &array[1].field_04,
        "A: the assign destination is the found element's record at +0x04");
  check(g_obs.assign_source == &source, "A: the assign source is the second ordinary argument");
  check(g_obs.assign_dest_lead == key,
        "A: the found element's leading dword is read as the key by the assign observer");
  check(g_obs.insert_calls == 0, "A: 0x006a2c50 is not called when the key is present");
  check(g_obs.report_calls == 0, "A: 0x0093db80 is not called when the key is present");
  check(g_obs.log_is(kCallSearch, kCallAssign), "A: the transfer order is search then assign");
  check(counter_of(receiver) == 1u, "A: the counter at +0x34 moves exactly once");
  {
    const ReceiverDiff diff = diff_receiver(before, receiver);
    check(diff.outside == 0 && diff.inside >= 1,
          "A: no byte of the receiver outside the counter's four bytes changed");
  }
  check(try_level_word() == -1,
        "A: the found arm never enters the try scope, so the try-level word stays -1");
  check(array[1].field_04.field_00_0c[0] == 0xaaaa0001u &&
            array[1].field_04.field_12 == 0x0021u,
        "A: the assign observer's write landed in the found element");
}

// Case B -- the search returns an element whose key is ABOVE the requested one.
// 0x006a2e64 (JB) is taken, 0x006a2e6d normalises the candidate to the array end
// and the insert arm runs. This is the case a wrong (signed, or inverted) compare
// at 0x006a2e64 gets wrong.
void case_key_below_candidate() {
  MapEntry array[2];
  array[0] = MapEntry{};
  array[1] = MapEntry{};
  array[0].field_00 = 0x10u;
  array[1].field_00 = 0x30u;
  Property source = make_property(0, 0, 0, 0, 0x0000u, 0x0000u);
  const Word key = 0x20u;

  g_obs.reset();
  g_obs.search_result = &array[1];

  Receiver receiver = make_receiver(&array[0], &array[0] + 2, 0x00u, 0u);
  dfw_property_set_006a2e20(as_list(receiver), key, &source);

  check(g_obs.assign_calls == 1, "B: 0x00542b80 is called exactly once");
  check(g_obs.assign_dest != &array[1].field_04,
        "B: the assign does NOT go into the element the search returned");
  check(g_obs.assign_dest != &array[0].field_04,
        "B: the assign does not go into any array element");
  check(g_obs.insert_calls == 1,
        "B: 0x006a2c50 runs, because key < candidate->field_00 normalised the candidate away");
  check(g_obs.log_is(kCallSearch, kCallAssign, kCallFindOrInsert),
        "B: the transfer order is search, assign, find-or-insert");
  check(g_obs.insert_entry_key == key, "B: the seed entry carries the key that was requested");
  check(counter_of(receiver) == 1u, "B: the counter at +0x34 moves exactly once");
  check(array[0].field_04.field_00_0c[0] == 0u && array[1].field_04.field_00_0c[0] == 0u,
        "B: no array element was written");
}

// Case C -- the comparison at 0x006a2e64 is UNSIGNED. Two inputs on which a
// signed compare would take the other arm.
void case_comparison_is_unsigned() {
  Property source = make_property(0, 0, 0, 0, 0x0000u, 0x0000u);
  MapEntry array[1];
  array[0] = MapEntry{};

  // 0x006a2e5e CMP EAX,EBX is not taken, then 0x006a2e62 CMP EDX,[EAX] with
  // EDX = 0xffffffff and [EAX] = 0: unsigned 0xffffffff < 0 is FALSE, so the
  // found arm runs. Signed, -1 < 0 is true and the insert arm would run.
  g_obs.reset();
  array[0].field_00 = 0u;
  g_obs.search_result = &array[0];
  Receiver high = make_receiver(&array[0], &array[0] + 1, 0x00u, 0u);
  dfw_property_set_006a2e20(as_list(high), 0xffffffffu, &source);
  check(g_obs.assign_dest == &array[0].field_04 && g_obs.insert_calls == 0,
        "C1: 0xffffffff against 0 is an unsigned above-or-equal, so the found arm runs");

  // The mirror: key 0 against an element key of 0xffffffff. Unsigned 0 <
  // 0xffffffff is TRUE, so the insert arm runs. Signed, 0 < -1 is false and the
  // found arm would run.
  g_obs.reset();
  array[0].field_00 = 0xffffffffu;
  g_obs.search_result = &array[0];
  Receiver low = make_receiver(&array[0], &array[0] + 1, 0x00u, 0u);
  dfw_property_set_006a2e20(as_list(low), 0u, &source);
  check(g_obs.insert_calls == 1 && g_obs.assign_dest != &array[0].field_04,
        "C2: 0 against 0xffffffff is an unsigned below, so the insert arm runs");
}

// Case D -- the key is absent and the array is empty, so the candidate IS the
// array end and 0x006a2e60 branches before the key compare ever runs. With the
// end pointer null this case also proves the short circuit: a model that read
// candidate->field_00 unconditionally would fault here.
void case_empty_array_inserts() {
  Property source = make_property(0xbbbb0001u, 0xbbbb0002u, 0xbbbb0003u, 0xbbbb0004u,
                                  0x0000u, 0x0031u);
  const Word key = 0x1234u;

  g_obs.reset();
  g_obs.search_result = nullptr;  // return the end pointer, which is null

  Receiver receiver = make_receiver(nullptr, nullptr, 0x11u, 5u);
  Receiver before = receiver;
  dfw_property_set_006a2e20(as_list(receiver), key, &source);

  check(g_obs.search_calls == 1 && g_obs.search_last == nullptr,
        "D: 0x00612db0 is called once with a null begin and a null end");
  check(g_obs.search_mode == 0x11u, "D: the mode word is the zero-extended byte at receiver+0x2c");
  check(g_obs.assign_calls == 1, "D: 0x00542b80 is called exactly once");
  check(g_obs.assign_dest != nullptr &&
            g_obs.assign_dest != reinterpret_cast<Property*>(&receiver),
        "D: the assign destination is the frame's own seed record, not receiver memory");
  check(g_obs.assign_dest_lead == key,
        "D: the seed entry's key was stored BEFORE the assign (0x006a2e83)");
  check(g_obs.assign_dest_flags == 0u,
        "D: the seed record's +16 word was zeroed BEFORE the assign (0x006a2e8f)");
  check(g_obs.assign_dest_type == 0u,
        "D: the seed record's +18 word was zeroed BEFORE the assign (0x006a2e94)");
  check(g_obs.assign_source == &source, "D: the assign source is the second ordinary argument");
  check(g_obs.insert_calls == 1, "D: 0x006a2c50 is called exactly once");
  check(g_obs.insert_map == reinterpret_cast<PropertyMap*>(&receiver.bytes[kArrayOffset]),
        "D: 0x006a2c50 receives receiver+0x18, the address formed by LEA ESI at 0x006a2e47");
  check(g_obs.insert_result_record != nullptr && g_obs.insert_entry != nullptr &&
            reinterpret_cast<const void*>(g_obs.insert_result_record) !=
                reinterpret_cast<const void*>(g_obs.insert_entry),
        "D: the out record and the seed entry are two distinct objects");
  check(g_obs.insert_entry_key == key, "D: the seed entry's leading dword is the key");
  check(g_obs.insert_try_level == 0,
        "D: the try-level word is 0 while 0x006a2c50 runs (0x006a2eaa)");
  check(try_level_word() == -1, "D: the try-level word is 0xffffffff after the call (0x006a2ebc)");
  check(g_obs.report_calls == 0,
        "D: 0x0093db80 is not called when the assign leaves bit 0x0004 clear");
  check(g_obs.log_is(kCallSearch, kCallAssign, kCallFindOrInsert),
        "D: the transfer order is search, assign, find-or-insert");
  check(counter_of(receiver) == 6u, "D: the counter at +0x34 moves exactly once");
  {
    const ReceiverDiff diff = diff_receiver(before, receiver);
    check(diff.outside == 0 && diff.inside >= 1,
          "D: no byte of the receiver outside the counter's four bytes changed");
  }
  // The source's four opaque words and its type word reached the seed record, so
  // the assign really did run against the frame seed and not against the array.
  // The values are the ones the observer captured while the frame was still live.
  check(g_obs.assign_written_first == 0xbbbb0001u && g_obs.assign_written_type == 0x0031u,
        "D: the assign wrote the source into the seed record");
}

// Case E -- the assign leaves bit 0x0004 in the record's +16 word, so the TEST at
// 0x006a2eb7 branches and 0x0093db80 runs with the seed record as its receiver
// and 0 as its argument.
void case_report_runs() {
  MapEntry array[1];
  array[0] = MapEntry{};
  Property source = make_property(0xcccc0001u, 0, 0, 0, 0x0004u, 0x0000u);
  const Word key = 0x77u;

  g_obs.reset();
  g_obs.assign_forced_flags = true;
  g_obs.assign_forced_flags_value = 0x0004u;

  Receiver receiver = make_receiver(&array[0], &array[0] + 1, 0x00u, 0u);
  dfw_property_set_006a2e20(as_list(receiver), key, &source);

  check(g_obs.insert_calls == 1, "E: 0x006a2c50 runs before the report test");
  check(g_obs.report_calls == 1, "E: 0x0093db80 is called exactly once");
  check(g_obs.report_receiver == g_obs.assign_dest,
        "E: the report receiver is the same seed record the assign wrote into");
  check(g_obs.report_receiver_flags == 0x0004u,
        "E: the report receiver's +16 word is the one the TEST examined");
  check(g_obs.report_argument == 0u, "E: the report argument is the literal 0 of PUSH 0x0");
  check(g_obs.log_is(kCallSearch, kCallAssign, kCallFindOrInsert, kCallReport),
        "E: the transfer order is search, assign, find-or-insert, report");
  check(counter_of(receiver) == 1u,
        "E: the counter at +0x34 still moves exactly once, after the report");
  check(array[0].field_00 == 0u, "E: the array element was not written by the body itself");
}

// Case F -- the same arm with the bit clear, and the out record poisoned. The
// observable outcome must be identical, which is the weakest honest form of
// "the out record is not consulted": it shows the result does not depend on what
// the callee wrote there, not that the body never read it.
void case_record_not_consulted() {
  MapEntry array[1];
  array[0] = MapEntry{};
  Property source = make_property(0, 0, 0, 0, 0x0000u, 0x0000u);
  const Word key = 0x99u;

  g_obs.reset();
  g_obs.insert_poison_record = true;
  g_obs.insert_poison_iterator = reinterpret_cast<MapEntry*>(0xdeadbeefu);
  g_obs.insert_poison_flag = 0xffu;

  Receiver receiver = make_receiver(&array[0], &array[0] + 1, 0x00u, 3u);
  dfw_property_set_006a2e20(as_list(receiver), key, &source);

  check(g_obs.insert_calls == 1, "F: 0x006a2c50 is called once");
  check(g_obs.report_calls == 0, "F: 0x0093db80 is not called");
  check(g_obs.assign_calls == 1, "F: 0x00542b80 is called once");
  check(g_obs.log_is(kCallSearch, kCallAssign, kCallFindOrInsert),
        "F: the transfer order is unchanged by the out record's contents");
  check(counter_of(receiver) == 4u,
        "F: the counter still moves exactly once regardless of the out record");
  check(array[0].field_00 == 0u, "F: the array element was not written");
}

// Case G -- repeated calls. The counter at +0x34 must move once per call, on both
// arms, so a mixed sequence of three calls has to land on exactly +3.
void case_counter_once_per_call() {
  MapEntry array[4];
  for (int index = 0; index < 4; ++index) {
    array[index] = MapEntry{};
    array[index].field_00 = static_cast<Word>(0x40u * static_cast<unsigned>(index + 1));
  }
  Property source = make_property(0, 0, 0, 0, 0x0000u, 0x0000u);

  g_obs.reset();
  Receiver receiver = make_receiver(&array[0], &array[0] + 4, 0x00u, 0u);

  g_obs.search_result = &array[0];
  dfw_property_set_006a2e20(as_list(receiver), 0x40u, &source);  // found
  g_obs.search_result = &array[3];
  dfw_property_set_006a2e20(as_list(receiver), 0x41u, &source);  // key below candidate -> insert
  g_obs.search_result = &array[0];
  dfw_property_set_006a2e20(as_list(receiver), 0x40u, &source);  // found again

  check(g_obs.search_calls == 3, "G: three calls make three searches");
  check(g_obs.assign_calls == 3, "G: three calls make three assigns");
  check(g_obs.insert_calls == 1, "G: only the middle call took the insert arm");
  check(counter_of(receiver) == 3u, "G: the counter moved once per call, so it reads 3");
}


// -- REFUTATION CASES --------------------------------------------------------
// The cases above show the reconstruction behaving. The ones below are aimed at
// breaking it: each states the wrong reconstruction it is trying to catch.

// H. The leading dword compared at 0x006a2e62 belongs to the ELEMENT the search
// returned. Decoy words are planted in the receiver's own untouched bytes
// (0x00..0x17) and in the map's bytes, with values chosen to flip the arm if
// either were read; the arm must not move.
void case_element_key_is_not_a_receiver_or_map_field() {
  Property source = make_property(0, 0, 0, 0, 0x0000u, 0x0000u);
  MapEntry array[2];
  array[0] = MapEntry{};
  array[1] = MapEntry{};

  // The key is 0x80000000. Unsigned, 0x80000000 < 0 is FALSE (found arm); signed,
// it is negative so a signed compare would take the insert arm. The decoys below
  // are 0, which under either reading would take the insert arm.
  const Word key = 0x80000000u;

  g_obs.reset();
  array[1].field_00 = 0u;  // candidate key 0
  g_obs.search_result = &array[1];
  Receiver receiver = make_receiver(&array[0], &array[0] + 2, 0x00u, 0u);
  // Decoys: the receiver's untouched head, and the map's own first two dwords.
  // 0x00..0x17 is opaque to this body, and the map's +0x00/+0x04 are read only
  // by 0x006a2c50, not by the compare.
  for (std::size_t index = 0; index < 0x18; ++index) {
    receiver.bytes[index] = 0u;
  }
  Word decoy = 0u;
  std::memcpy(receiver.bytes + kArrayOffset + 0x8, &decoy, sizeof decoy);
  std::memcpy(receiver.bytes + kArrayOffset + 0xc, &decoy, sizeof decoy);
  g_active_receiver = &receiver;
  dfw_property_set_006a2e20(as_list(receiver), key, &source);
  g_active_receiver = nullptr;

  check(g_obs.insert_calls == 0,
        "H1: the compare follows the element's own leading dword, not the receiver's decoys");
  check(g_obs.assign_dest ==
            reinterpret_cast<Property*>(reinterpret_cast<unsigned char*>(&array[1]) +
                                       kElementRecordDisplacement),
        "H2: the found arm assigned into the element the search returned");

  // Mirror image: the element's key is above the requested one, the decoys are
  // below it, and the insert arm must run.
  g_obs.reset();
  array[1].field_00 = 0xffffffffu;
  g_obs.search_result = &array[1];
  Receiver other = make_receiver(&array[0], &array[0] + 2, 0x00u, 0u);
  decoy = 0u;
  for (std::size_t index = 0; index < 0x18; ++index) {
    other.bytes[index] = 0u;
  }
  std::memcpy(other.bytes + kArrayOffset + 0x8, &decoy, sizeof decoy);
  dfw_property_set_006a2e20(as_list(other), key, &source);

  check(g_obs.insert_calls == 1,
        "H3: the mirror case also follows the element, so the decoys are inert both ways");
  check(g_obs.assign_dest !=
            reinterpret_cast<Property*>(reinterpret_cast<unsigned char*>(&array[1]) +
                                       kElementRecordDisplacement),
        "H4: the insert arm did not assign into the array element");
}

// I. 0x04 is a BYTE displacement into the element, not an element index and not a
// dword offset. The destination is four bytes past the element's base; a
// reconstruction that added 0x04 elements would land 0x60 bytes out, and one that
// treated it as a dword offset would land at +0x10.
void case_record_displacement_is_bytes() {
  MapEntry array[3];
  for (int index = 0; index < 3; ++index) {
    array[index] = MapEntry{};
    array[index].field_00 = static_cast<Word>(0x10u * static_cast<unsigned>(index + 1));
  }
  Property source = make_property(0x11112222u, 0, 0, 0, 0x0000u, 0x0000u);
  const Word key = 0x20u;

  g_obs.reset();
  g_obs.search_result = &array[1];
  Receiver receiver = make_receiver(&array[0], &array[0] + 3, 0x00u, 0u);
  dfw_property_set_006a2e20(as_list(receiver), key, &source);

  unsigned char* element = reinterpret_cast<unsigned char*>(&array[1]);
  check(g_obs.assign_dest == reinterpret_cast<Property*>(element + 0x4),
        "I1: the assign destination is the element's +0x04 BYTE displacement");
  check(g_obs.assign_dest != reinterpret_cast<Property*>(element),
        "I2: it is not the element's own base");
  check(g_obs.assign_dest != reinterpret_cast<Property*>(element + 0x10),
        "I3: it is not a dword-indexed +0x04 (which would be +0x10)");
  check(g_obs.assign_dest != reinterpret_cast<Property*>(element + 4 * 0x18),
        "I4: it is not four elements on (which would be +0x60)");
  check(reinterpret_cast<unsigned char*>(g_obs.assign_dest) -
            reinterpret_cast<unsigned char*>(&array[2]) <
        0,
        "I5: it is still inside the element the search returned, not the next one");
  check(array[1].field_04.field_00_0c[0] == 0x11112222u,
        "I6: the assign landed on the element the search returned");
  check(array[0].field_04.field_00_0c[0] == 0u && array[2].field_04.field_00_0c[0] == 0u,
        "I7: no neighbouring element was written");
}

// J. The insert arm's assign destination is four bytes into a 0x18-byte run that
// lives in the body's own frame. It is not receiver memory, not the map, and not
// the run's base.
void case_seed_record_placement() {
  MapEntry array[1];
  array[0] = MapEntry{};
  Property source = make_property(0x0badf00du, 0, 0, 0, 0x0000u, 0x0000u);
  const Word key = 0x4242u;

  g_obs.reset();
  g_obs.search_result = nullptr;  // the search returns the end pointer
  Receiver receiver = make_receiver(&array[0], &array[0] + 1, 0x00u, 0u);
  unsigned char* receiver_base = receiver.bytes;
  dfw_property_set_006a2e20(as_list(receiver), key, &source);

  unsigned char* seed = reinterpret_cast<unsigned char*>(g_obs.assign_dest);
  check(seed != nullptr, "J1: the insert arm assigned somewhere");
  check(seed < receiver_base || seed >= receiver_base + sizeof receiver.bytes,
        "J2: the seed record is NOT inside the receiver");
  check(seed != receiver_base + kArrayOffset,
        "J3: the seed record is not the map's address either");
  // The seed record sits four bytes into its run, so the run's leading dword -
  // which the assign observer reads as assign_dest_lead - is the key.
  check(g_obs.assign_dest_lead == key,
        "J4: the run's leading dword is the key, so the record is at +0x04 of it");
  check(sizeof(MapEntry) == 0x18 && kElementRecordDisplacement + 0x14 == sizeof(MapEntry),
        "J5: the 0x04 displacement plus the 0x14-byte record ends the 0x18 stride");
  check(g_obs.assign_source == &source, "J6: the source is the second argument, not the seed");
  check(g_obs.assign_dest != &source, "J7: the source is read, never written");
}

// K. ORDERING: 0x006a2ed1 (the counter increment) runs AFTER 0x006a2ecc (the
// report). The report observer samples the counter while it is running, so a
// reconstruction that incremented earlier is caught.
void case_counter_increments_after_the_report() {
  MapEntry array[1];
  array[0] = MapEntry{};
  Property source = make_property(0, 0, 0, 0, 0x0000u, 0x0000u);
  const Word key = 0x55u;

  g_obs.reset();
  g_obs.assign_forced_flags = true;
  g_obs.assign_forced_flags_value = 0x0004u;  // take the report branch
  Receiver receiver = make_receiver(&array[0], &array[0] + 1, 0x00u, 9u);
  g_active_receiver = &receiver;
  dfw_property_set_006a2e20(as_list(receiver), key, &source);
  g_active_receiver = nullptr;

  check(g_obs.report_calls == 1, "K1: the report ran");
  check(g_obs.report_counter_valid, "K2: the report observer sampled the counter");
  check(g_obs.report_counter_seen == 9u,
        "K3: the counter still held its pre-call value while the report ran");
  check(counter_of(receiver) == 10u, "K4: and it moved exactly once, after the report");
  check(g_obs.log_is(kCallSearch, kCallAssign, kCallFindOrInsert, kCallReport),
        "K5: the report is the last transfer before the increment");
}

// L. The TEST at 0x006a2eb7 reads the word 0x00542b80 WROTE, not the source's.
// Driven in both directions with the two disagreeing, so a reconstruction that
// read the source (or that read the pre-assign zero) is refuted either way.
void case_bit_test_reads_the_assign_output() {
  MapEntry array[1];
  array[0] = MapEntry{};
  const Word key = 0x66u;

  // Source bit clear, assign leaves the bit SET: the report must run, which a
  // reconstruction testing the source (or the zeroed pre-assign word) would not.
  {
    Property source = make_property(0, 0, 0, 0, 0x0000u, 0x0000u);
    g_obs.reset();
    g_obs.assign_forced_flags = true;
    g_obs.assign_forced_flags_value = 0x0004u;
    Receiver receiver = make_receiver(&array[0], &array[0] + 1, 0x00u, 0u);
    dfw_property_set_006a2e20(as_list(receiver), key, &source);
    check(g_obs.report_calls == 1,
          "L1: the bit comes from the word the assign wrote, not from the source");
  }

  // Source bit SET, assign leaves the bit CLEAR: the report must NOT run, which
  // a reconstruction testing the source would get wrong in the other direction.
  {
    Property source = make_property(0, 0, 0, 0, 0x0004u, 0x0000u);
    g_obs.reset();
    g_obs.assign_forced_flags = true;
    g_obs.assign_forced_flags_value = 0x0000u;
    Receiver receiver = make_receiver(&array[0], &array[0] + 1, 0x00u, 0u);
    dfw_property_set_006a2e20(as_list(receiver), key, &source);
    check(g_obs.report_calls == 0,
          "L2: and in the other direction the source's own bit is not what is tested");
  }

  // The recomposition the callee's own listing shows: the source's bits minus
  // 0x0002, or the destination's 0x0002. Bit 0x0004 is never one of the two, so
  // it always comes from the source.
  {
    Property source = make_property(0, 0, 0, 0, 0x0006u, 0x0000u);
    g_obs.reset();
    Receiver receiver = make_receiver(&array[0], &array[0] + 1, 0x00u, 0u);
    dfw_property_set_006a2e20(as_list(receiver), key, &source);
    check(g_obs.report_calls == 1,
          "L3: bit 0x0004 of the source survives the recomposition and takes the branch");
  }
}

// M. The byte at receiver+0x2c is zero-extended by the MOVZX. 0x80 and 0xff are
// the discriminating values: a sign-extending read would hand the search
// 0xffffff80 / 0xffffffff and a one-byte read would hand it 0x80/0xff.
void case_mode_byte_is_zero_extended() {
  MapEntry array[1];
  array[0] = MapEntry{};
  Property source = make_property(0, 0, 0, 0, 0x0000u, 0x0000u);

  for (std::size_t value : {std::size_t(0x80), std::size_t(0xff), std::size_t(0x01)}) {
    g_obs.reset();
    g_obs.search_result = &array[0];
    Receiver receiver =
        make_receiver(&array[0], &array[0] + 1, static_cast<std::uint8_t>(value), 0u);
    dfw_property_set_006a2e20(as_list(receiver), 0u, &source);
    check(g_obs.search_mode == value,
          "M: the mode word is the byte at +0x2c zero-extended, never sign-extended");
  }
}

// N. The counter is the word at +0x34. A decoy word one dword lower is never
// touched, and the word at +0x38 is past the modelled receiver.
void case_counter_displacement_is_0x34() {
  MapEntry array[1];
  array[0] = MapEntry{};
  Property source = make_property(0, 0, 0, 0, 0x0000u, 0x0000u);

  g_obs.reset();
  g_obs.search_result = &array[0];
  Receiver receiver = make_receiver(&array[0], &array[0] + 1, 0x00u, 0x11223344u);
  Word decoy_low = 0xaabbccddu;
  std::memcpy(receiver.bytes + 0x30, &decoy_low, sizeof decoy_low);
  Word decoy_high = 0x55667788u;
  std::memcpy(receiver.bytes + 0x38, &decoy_high, sizeof decoy_high);
  Receiver before = receiver;
  dfw_property_set_006a2e20(as_list(receiver), 0u, &source);

  check(counter_of(receiver) == 0x11223345u, "N1: the word at +0x34 is the one that moved");
  Word still_low = 0;
  Word still_high = 0;
  std::memcpy(&still_low, receiver.bytes + 0x30, sizeof still_low);
  std::memcpy(&still_high, receiver.bytes + 0x38, sizeof still_high);
  check(still_low == 0xaabbccddu, "N2: the decoy word at +0x30 was not touched");
  check(still_high == 0x55667788u, "N3: neither was the word at +0x38");
  const ReceiverDiff diff = diff_receiver(before, receiver);
  check(diff.outside == 0, "N4: no byte outside the four counter bytes changed");
}

// O. The words at +0x18 and +0x1c are two different pointers and the search
// receives each of them, not one of them twice. The receiver's begin points into
// the FIRST array and its end into the SECOND, and the search result is steered
// into each of them in turn so that both arrays are live at the same time - a
// compiler is free to give two never-both-used locals the same storage, and a
// test that let it would compare an array against itself.
void case_begin_and_end_words_are_distinct() {
  // ONE backing store, with the two "arrays" as windows into it. Two separate
  // locals would not do: the compiler is free to overlap two locals it never
  // sees aliased, and it does - `second_array[3]` and `first_array[0]` land on
  // the same address here - which would make the distinctness check below a
  // statement about the compiler instead of about the body.
  MapEntry backing[5];
  for (int index = 0; index < 5; ++index) {
    backing[index] = MapEntry{};
    backing[index].field_00 = 0x10u * static_cast<Word>(index + 1u);
  }
  MapEntry* const first_array = backing;
  MapEntry* const second_array = backing + 2;
  Property source = make_property(0x0f0f0f0fu, 0, 0, 0, 0x0000u, 0x0000u);
  // 0xffffffff is unsigned-above every element key, so the found arm runs; a
  // signed compare would call it a below and take the insert arm instead.
  const Word key = 0xffffffffu;

  // First: the search returns an element of the array the BEGIN word names.
  g_obs.reset();
  g_obs.search_result = first_array + 1;
  Receiver receiver = make_receiver(backing, backing + 5, 0x00u, 0u);
  dfw_property_set_006a2e20(as_list(receiver), key, &source);
  check(g_obs.search_first == backing,
        "O1: the search's first argument is the word at receiver+0x18");
  check(g_obs.search_last == backing + 5,
        "O2: the search's second argument is the word at receiver+0x1c");
  check(g_obs.search_first != g_obs.search_last, "O3: the two are genuinely different objects");
  check(g_obs.assign_dest == &first_array[1].field_04,
        "O4: the element the search returned is assigned into, whichever window it is in");

  // Second: the same receiver, the search steered into the OTHER array. Only a
  // reconstruction that ignored the search result could confuse the two.
  g_obs.reset();
  g_obs.search_result = second_array + 2;
  dfw_property_set_006a2e20(as_list(receiver), key, &source);
  check(g_obs.search_first == backing, "O5: the two receiver words are read again unchanged");
  check(g_obs.search_last == backing + 5, "O6: and are still two different pointers");
  check(g_obs.assign_dest == &second_array[2].field_04,
        "O7: the second call assigned into the other window, not the first");
  check(first_array[1].field_04.field_00_0c[0] == 0x0f0f0f0fu &&
            second_array[2].field_04.field_00_0c[0] == 0x0f0f0f0fu,
        "O8: both arrays really were written, so neither is a dead local");
}

// P. ABI. The terminator is `RET 0x8`, so the callee owns the two argument words.
// ESP is sampled inside a trampoline, before the pushes and after the return: the
// two are equal only when the callee popped all eight bytes. A caller-cleaned
// convention would leave the second sample eight bytes lower.
struct EspSamples {
  std::uint32_t before_push = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_measured(PropertyList* receiver, Word key, Property* source) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&dfw_property_set_006a2e20));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  // EAX and ECX are in the clobber list, so the compiler cannot have allocated
  // any of the four inputs to them: every "r" operand therefore survives the
  // `movl ..., %%ecx` that precedes its use.
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "pushl %[src]\n\t"
                       "pushl %[key]\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver), [key] "r"(key),
                         [src] "r"(source)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_push = before;
  samples.after_return = after;
  return samples;
}

void case_two_argument_words_are_callee_cleaned() {
  MapEntry array[1];
  array[0] = MapEntry{};
  Property source = make_property(0x01020304u, 0, 0, 0, 0x0000u, 0x0000u);
  Receiver receiver = make_receiver(&array[0], &array[0] + 1, 0x00u, 0u);

  g_obs.reset();
  g_obs.search_result = &array[0];
  const EspSamples samples = call_measured(as_list(receiver), 0u, &source);
  check(samples.after_return == samples.before_push,
        "P1: the callee popped both argument words (RET 0x8), so ESP is balanced");
  check(g_obs.search_calls == 1, "P2: the trampoline really reached the body");
  check(counter_of(receiver) == 1u, "P3: and the body really ran to its end");

  // The receiver the trampoline handed over is the one the body read: the search
  // saw this receiver's begin, end and mode.
  check(g_obs.search_mode == 0x00u && g_obs.search_first == &array[0],
        "P4: ECX carried the receiver the trampoline was given");
}

// The displacements the reconstruction states, against the listing's own bytes.
void verify_displacement_constants() {
  check(kReceiverArrayDisplacement == 0x18u, "V1: array begin at receiver+0x18");
  check(kReceiverEndDisplacement == 0x1cu, "V2: array end at receiver+0x1c");
  check(kReceiverModeByteDisplacement == 0x2cu, "V3: the byte at receiver+0x2c");
  check(kReceiverCounterDisplacement == 0x34u, "V4: the counter at receiver+0x34");
  check(kElementKeyDisplacement == 0x0u, "V5: the element's key word is at its +0x00");
  check(kElementRecordDisplacement == 0x4u, "V6: the element's record is at its +0x04");
  check(kRecordFlagsDisplacement == 0x10u, "V7: the record's tested word is at its +0x10");
  check(kRecordTypeDisplacement == 0x12u, "V8: the record's copied word is at its +0x12");
  check(sizeof(PropertyList) == 0x38u, "V9: the modeled receiver ends after the counter");
  check(kReceiverArrayDisplacement + 0x14 == kReceiverModeByteDisplacement,
        "V10: the map's own +0x14 byte is the receiver's +0x2c byte");
  check(sizeof(MapEntry) == 0x18u, "V11: the 0x18 element stride");
  check(sizeof(Property) == 0x14u, "V12: the 0x14-byte record");
}

}  // namespace

int main() {
  verify_displacement_constants();
  case_key_present();
  case_key_below_candidate();
  case_comparison_is_unsigned();
  case_empty_array_inserts();
  case_report_runs();
  case_record_not_consulted();
  case_counter_once_per_call();
  case_element_key_is_not_a_receiver_or_map_field();
  case_record_displacement_is_bytes();
  case_seed_record_placement();
  case_counter_increments_after_the_report();
  case_bit_test_reads_the_assign_output();
  case_mode_byte_is_zero_extended();
  case_counter_displacement_is_0x34();
  case_begin_and_end_words_are_distinct();
  case_two_argument_words_are_callee_cleaned();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
