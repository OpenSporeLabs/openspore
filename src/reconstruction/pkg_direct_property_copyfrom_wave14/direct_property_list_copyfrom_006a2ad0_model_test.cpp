// PKG-DIRECT-PROPERTY-COPYFROM-WAVE14 -- VA 0x006a2ad0
// Behavioural model test for App::DirectPropertyList::CopyFrom.
//
// The two direct callees the reconstructed body calls -- 0x006a28f0 at
// 0x006a2ae0 and 0x006a1710 at 0x006a2b0d -- are defined here as observer
// stubs, because neither is owned by this package. The slot target at
// displacement 0x14 is UNRESOLVED, so it is not stubbed by declaration: the
// test supplies its own function pointers in the receiver's table word and
// watches which of them the body dispatches through.
//
// The assertions are the claims the 33-instruction machine listing fixes and
// nothing more: the self-copy guard, the resize call's single occurrence and
// its receiver-only shape, the ordering of the resize relative to the two
// source-range loads, the element stride, the empty-range path, one dispatch
// per element with all three arguments, the per-element re-read of the
// two-level table load, the single tail call and its argument, and the fact
// that the body writes nothing at all.
//
// What is deliberately NOT asserted, because no record in this package fixes
// it: what the element's first word means, what the receiver's word at
// displacement 0x30 means, what 0x006a28f0 does with the range beyond the
// ordering this body fixes, whether the receiver's word 0 is a vtable pointer,
// which slot index displacement 0x14 corresponds to, the element's internal
// layout, and anything about 0x006a1710 other than the receiver and the one
// pushed word it is given. The fixtures below are therefore opaque byte blocks:
// the only field names are the listing's own reading of the two words the body
// touches, and no field is named after a type or a meaning.

#include "direct_property_list_copyfrom_006a2ad0.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

// The package header #undefs its own convention macros at the end of the file,
// so this translation unit spells the convention again for the definitions it
// supplies. It is the same spelling the header used; a divergence here would be
// a compile error rather than a silent ABI split.
#if defined(_MSC_VER)
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_THISCALL __thiscall
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_CDECL __cdecl
#else
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_THISCALL __attribute__((thiscall))
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_direct_property_copyfrom_wave14 {

namespace {

// ---------------------------------------------------------------------------
// Assertions
// ---------------------------------------------------------------------------
int g_failures = 0;
int g_checks = 0;

void check(bool ok, const char *what) {
  ++g_checks;
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// The same, tagged with the path under test, for the checks that run once per
// scenario in a loop.
void check_path(bool ok, const char *path, const char *what) {
  ++g_checks;
  if (!ok) {
    std::fprintf(stderr, "FAILED: [%s] %s\n", path, what);
    ++g_failures;
  }
}

// ---------------------------------------------------------------------------
// Observer state
// ---------------------------------------------------------------------------
constexpr int kMaxSlotCalls = 16;
constexpr int kMaxTraceEvents = 32;

// One slot dispatch, as the test sees it through the stub the body reached.
struct SlotCall {
  int event_index = 0;
  const void *receiver = nullptr;
  TargetWord first_word = 0u;
  const void *second_argument = nullptr;
  const char *via = nullptr;
};

struct Observation {
  // 0x006a28f0
  int resize_calls = 0;
  int resize_event = 0;
  const void *resize_argument = nullptr;
  // When set, the stub writes the planted range into the argument object's
  // +0x18 / +0x1c words. That is what lets the test tell a source range read
  // that happens AFTER 0x006a2ae0 from one that does not.
  bool resize_plants_range = false;
  const void *plant_target = nullptr;
  const void *plant_begin = nullptr;
  const void *plant_end = nullptr;

  // 0x006a1710
  int set_parent_calls = 0;
  int set_parent_event = 0;
  const void *set_parent_receiver = nullptr;
  const void *set_parent_argument = nullptr;

  // The slot transfers.
  int slot_call_count = 0;
  SlotCall slot_calls[kMaxSlotCalls];
  int decoy_calls = 0;

  // When set, the first slot stub overwrites the receiver's table word with
  // replacement_table, which is how the test tells a per-iteration re-read of
  // the table from a hoist before the loop.
  bool slot_swaps_table_on_first_call = false;
  const void *replacement_table = nullptr;
};

// A single-character trace of the observers' entries, in order: 'R' is
// 0x006a28f0, 'P' is 0x006a1710, '1' and '2' are the two slot stubs (the table
// word the body reached), and 'X' is the decoy that would fire if the body read
// a table displacement other than 0x14. The slot markers are digits rather than
// case variants so a trace literal is unambiguous to read.
struct Trace {
  char events[kMaxTraceEvents] = {};
  int count = 0;

  void push(char what) {
    if (count < kMaxTraceEvents) {
      events[count] = what;
      ++count;
    }
  }

  std::string str() const {
    return std::string(events, static_cast<std::size_t>(count));
  }
};

Observation g_obs;
Trace g_trace;
int g_event = 0;

void reset_observation() {
  g_obs = Observation{};
  g_trace = Trace{};
  g_event = 0;
}

// ---------------------------------------------------------------------------
// Fixtures
// ---------------------------------------------------------------------------
// A 0x18-stride element. ONLY the two words the body touches are given a
// meaning, and both names are the listing's: the first word is pushed as a
// value (0x006a2afb PUSH EDX) and the second field is handed over as an
// address (0x006a2af7 LEA ECX,[ESI + 0x4]). No record establishes the element
// type or the bytes between and after them, so the rest is opaque padding whose
// contents are checked to survive the call untouched.
//
// The first member is a uint32_t and the struct's alignment is therefore 4,
// because the body reads element + 0x0 with a uint32_t load and forms
// element + 0x4: the fixture must be the aligned block the listing assumes.
struct Element {
  TargetWord first_word;
  TargetWord second_field;
  unsigned char opaque[kElementStride - 2u * sizeof(TargetWord)];
};

static_assert(sizeof(Element) == kElementStride,
              "an element is exactly one 0x18 stride");
static_assert(offsetof(Element, first_word) == kElementFirstWordOffset,
              "the first word is at element + 0x0");
static_assert(offsetof(Element, second_field) == kElementSecondFieldOffset,
              "the second field is at element + 0x4");
static_assert(alignof(Element) >= alignof(TargetWord),
              "the body's uint32_t load of element + 0x0 needs a 4-byte aligned block");

// The walk is bounded by the range end word, and a step that is not exactly
// 0x18 is caught two ways. A step that still LANDS on the end word is caught
// cleanly, by the dispatch count, the first-word order and the requirement
// that every dispatch's second argument lie inside the real element array --
// that last check is what pins 0x006a2b00 ADD ESI,0x18 as the exact step
// rather than merely a step that eventually reached the end.
//
// A step that never lands on the end word does not terminate: the walk runs off
// the real elements, and in the original it would run off its own buffer too.
// The block below carries poisoned padding so the run is over a known poisoned
// region rather than over live objects, and the process then dies on unmapped
// memory. That is a non-zero exit and a detected failure, not a false pass, but
// it carries no diagnostic, and no amount of padding changes that: the walk
// never comes back to be checked.
constexpr int kMaxElements = 3;
constexpr int kSlopSlots = 128;

struct ElementBlock {
  Element elements[kMaxElements];
  unsigned char padding[kSlopSlots * kElementStride];
};

// The receiver. Its only three significant words are the ones the listing shows
// it addressing: the table word at 0x0, the address it forms at 0x18, and the
// word it pushes at 0x30. The gaps are poisoned and are included in the
// before/after comparison, so a store into a gap would be caught even though no
// record says what lives there.
//
// No field is named after a meaning: the layout is a set of displacements, and
// the receiver's actual type is not established by any record in this package.
struct Receiver {
  TargetWord table_word;                                // 0x00
  unsigned word_gap[kReceiverRangeSubObjectOffset / sizeof(TargetWord) - 1u];
  unsigned char range_sub_object[kReceiverParentWordOffset -
                                 kReceiverRangeSubObjectOffset];  // 0x18 .. 0x2f
  TargetWord parent_word;                               // 0x30
  unsigned char tail[64];
};

static_assert(offsetof(Receiver, table_word) == kReceiverTableWordOffset,
              "the table word is at receiver + 0x0");
static_assert(offsetof(Receiver, range_sub_object) == kReceiverRangeSubObjectOffset,
              "the resize sub-object address is receiver + 0x18");
static_assert(offsetof(Receiver, parent_word) == kReceiverParentWordOffset,
              "the pushed word is at receiver + 0x30");

// The argument object, holding the source range the body reads at 0x006a2ae5
// and 0x006a2ae8.
struct Argument {
  unsigned char head[kSourceRangeBeginOffset];  // 0x00 .. 0x17
  void *range_begin;                            // 0x18
  void *range_end;                              // 0x1c
  unsigned char tail[64];
};

static_assert(offsetof(Argument, range_begin) == kSourceRangeBeginOffset,
              "the range begin word is at argument + 0x18");
static_assert(offsetof(Argument, range_end) == kSourceRangeEndOffset,
              "the range end word is at argument + 0x1c");

// A dispatch table in which EVERY word except the one at 0x14 holds the decoy.
// If the body reached the table at any displacement other than 0x14 the decoy
// would fire and record an 'X' in the trace, so this pins 0x006a2af4
// MOV EAX,[EAX + 0x14] and not merely "somewhere in this table".
struct ProbeTable {
  SlotTarget_006a2ad0 word_0x00;
  SlotTarget_006a2ad0 word_0x04;
  SlotTarget_006a2ad0 word_0x08;
  SlotTarget_006a2ad0 word_0x0c;
  SlotTarget_006a2ad0 word_0x10;
  SlotTarget_006a2ad0 entry;  // 0x14 -- the only word the body may read
  SlotTarget_006a2ad0 word_0x18;
  SlotTarget_006a2ad0 word_0x1c;
  SlotTarget_006a2ad0 word_0x20;
  SlotTarget_006a2ad0 word_0x24;
  SlotTarget_006a2ad0 word_0x28;
  SlotTarget_006a2ad0 word_0x2c;
};

static_assert(offsetof(ProbeTable, entry) == kTableEntryOffset,
              "the transferred function pointer is at table + 0x14");

// A word that is plainly not an address, so a body that pushed the ADDRESS
// receiver + 0x30 instead of the word stored there would be caught.
constexpr TargetWord kParentWord = 0x5a5a1234u;

// Fill every byte of a fixture with a pattern, so an untouched gap is provably
// untouched and an uninitialised read cannot leak a stray pointer into a
// comparison.
template <typename Fixture>
void poison(Fixture &fixture) {
  std::memset(&fixture, 0xa5, sizeof fixture);
}

void plant_table_word(Receiver &receiver, const ProbeTable *table) {
  receiver.table_word = reinterpret_cast<TargetWord>(table);
}

void plant_range(Argument &argument, const Element *begin, const Element *end) {
  argument.range_begin = const_cast<Element *>(begin);
  argument.range_end = const_cast<Element *>(end);
}

}  // namespace

// ---------------------------------------------------------------------------
// 0x006a28f0 -- receiver-only direct call, declared by the header, defined here
// because it lives outside this package.
// ---------------------------------------------------------------------------
// 0x006a2add LEA ECX,[EDI + 0x18] / 0x006a2ae0 CALL 0x006a28f0. Nothing is
// pushed, so this is a one-word __thiscall and the pointer it is handed is the
// whole of what can be observed.
extern "C" void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_THISCALL
App_unmodelled_element_range_resize_006a28f0(void *element_range) {
  ++g_obs.resize_calls;
  g_obs.resize_event = ++g_event;
  g_obs.resize_argument = element_range;
  g_trace.push('R');
  if (g_obs.resize_plants_range) {
    unsigned char *const target =
        static_cast<unsigned char *>(const_cast<void *>(g_obs.plant_target));
    std::memcpy(target + kSourceRangeBeginOffset, &g_obs.plant_begin,
                sizeof g_obs.plant_begin);
    std::memcpy(target + kSourceRangeEndOffset, &g_obs.plant_end,
                sizeof g_obs.plant_end);
  }
}

// ---------------------------------------------------------------------------
// 0x006a1710 -- the tail call, declared by the header, defined here because it
// lives outside this package.
// ---------------------------------------------------------------------------
// 0x006a2b07 MOV ECX,[EDI + 0x30] / 0x006a2b0a PUSH ECX / 0x006a2b0b
// MOV ECX,EDI / 0x006a2b0d CALL 0x006a1710. The receiver is the hidden ECX
// argument and the one ordinary argument is the VALUE of the word at receiver
// + 0x30.
extern "C" void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_THISCALL
App_PropertyList_SetParent_006a1710(void *receiver, void *parent_word) {
  ++g_obs.set_parent_calls;
  g_obs.set_parent_event = ++g_event;
  g_obs.set_parent_receiver = receiver;
  g_obs.set_parent_argument = parent_word;
  g_trace.push('P');
}

namespace {

// ---------------------------------------------------------------------------
// The two slot stubs, plus the decoy
// ---------------------------------------------------------------------------
// 0x006a2afe CALL EAX, with the receiver in ECX and two words pushed. Which stub
// fires is decided entirely by the body: it chooses the table entry it reads,
// and this test only reports what it was handed.
void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_THISCALL
slot_table_a_entry(void *receiver, TargetWord first_word, void *second_argument) {
  if (g_obs.slot_call_count < kMaxSlotCalls) {
    SlotCall &call = g_obs.slot_calls[g_obs.slot_call_count];
    call.event_index = ++g_event;
    call.receiver = receiver;
    call.first_word = first_word;
    call.second_argument = second_argument;
    call.via = "table_a";
    ++g_obs.slot_call_count;
  }
  g_trace.push('1');
  if (g_obs.slot_swaps_table_on_first_call && g_obs.slot_call_count == 1) {
    std::memcpy(receiver, &g_obs.replacement_table,
                sizeof g_obs.replacement_table);
  }
}

// The same shape, reached only if the body re-reads the receiver's table word.
void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_THISCALL
slot_table_b_entry(void *receiver, TargetWord first_word, void *second_argument) {
  if (g_obs.slot_call_count < kMaxSlotCalls) {
    SlotCall &call = g_obs.slot_calls[g_obs.slot_call_count];
    call.event_index = ++g_event;
    call.receiver = receiver;
    call.first_word = first_word;
    call.second_argument = second_argument;
    call.via = "table_b";
    ++g_obs.slot_call_count;
  }
  g_trace.push('2');
}

// Every table word other than the one at displacement 0x14. If this ever fires,
// the body read a table displacement the listing does not contain.
void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_THISCALL
slot_wrong_displacement(void *receiver, TargetWord first_word,
                        void *second_argument) {
  (void)receiver;
  (void)first_word;
  (void)second_argument;
  ++g_obs.decoy_calls;
  g_trace.push('X');
}

ProbeTable make_probe_table(SlotTarget_006a2ad0 entry) {
  ProbeTable table;
  table.word_0x00 = &slot_wrong_displacement;
  table.word_0x04 = &slot_wrong_displacement;
  table.word_0x08 = &slot_wrong_displacement;
  table.word_0x0c = &slot_wrong_displacement;
  table.word_0x10 = &slot_wrong_displacement;
  table.entry = entry;
  table.word_0x18 = &slot_wrong_displacement;
  table.word_0x1c = &slot_wrong_displacement;
  table.word_0x20 = &slot_wrong_displacement;
  table.word_0x24 = &slot_wrong_displacement;
  table.word_0x28 = &slot_wrong_displacement;
  table.word_0x2c = &slot_wrong_displacement;
  return table;
}

ProbeTable make_table_a() { return make_probe_table(&slot_table_a_entry); }

ProbeTable make_table_b() { return make_probe_table(&slot_table_b_entry); }

void fill_elements(Element *elements, int count, const TargetWord *first_words) {
  for (int i = 0; i < count; ++i) {
    poison(elements[i]);
    elements[i].first_word = first_words[i];
    elements[i].second_field = 0x11110000u + static_cast<TargetWord>(i);
  }
}

const void *second_argument_for(const Element &element) {
  return reinterpret_cast<const unsigned char *>(&element) +
         kElementSecondFieldOffset;
}

// True when the address is inside the real element array and nowhere else.
bool within_elements(const void *address, const Element *first, int count) {
  const unsigned char *const low =
      reinterpret_cast<const unsigned char *>(first);
  const unsigned char *const high =
      low + static_cast<std::size_t>(count) * kElementStride;
  const unsigned char *const probe = static_cast<const unsigned char *>(address);
  return probe >= low && probe < high;
}

// ---------------------------------------------------------------------------
// 1. The self-copy guard
// ---------------------------------------------------------------------------
// 0x006a2ad8 CMP EDI,EBX / 0x006a2ada JZ 0x006a2b13. The receiver and the
// argument are the same object, so the body reaches the epilogue with no
// transfer at all: no resize, no dispatch, no tail call.
void test_self_copy_skips_the_entire_body() {
  Receiver receiver;
  const ProbeTable table = make_table_a();
  poison(receiver);
  plant_table_word(receiver, &table);
  receiver.parent_word = kParentWord;
  reset_observation();

  App_DirectPropertyList_CopyFrom_006a2ad0(&receiver, &receiver);

  check(g_obs.resize_calls == 0,
        "self-copy: 0x006a28f0 is not called when the receiver is the argument");
  check(g_obs.slot_call_count == 0, "self-copy: no slot transfer is dispatched");
  check(g_obs.set_parent_calls == 0,
        "self-copy: the 0x006a1710 tail call is not reached");
  check(g_trace.str().empty(), "self-copy: the body makes no transfer at all");
}

// ---------------------------------------------------------------------------
// 2. The resize call's shape and position
// ---------------------------------------------------------------------------
// 0x006a2add LEA ECX,[EDI + 0x18] / 0x006a2ae0 CALL 0x006a28f0. The callee is
// receiver-only, so the pointer it receives is the whole contract: exactly
// receiver + 0x18, and it is the FIRST thing that happens.
void test_resize_runs_once_with_the_receiver_sub_object() {
  Receiver receiver;
  Argument argument;
  const ProbeTable table = make_table_a();
  ElementBlock block;
  const TargetWord first_words[1] = {0x11u};
  poison(receiver);
  poison(argument);
  poison(block);
  fill_elements(block.elements, 1, first_words);
  plant_table_word(receiver, &table);
  receiver.parent_word = kParentWord;
  // Empty range: only the resize runs.
  plant_range(argument, block.elements, block.elements);
  reset_observation();

  App_DirectPropertyList_CopyFrom_006a2ad0(&receiver, &argument);

  check(g_obs.resize_calls == 1, "0x006a28f0 runs exactly once");
  check(g_obs.resize_argument == reinterpret_cast<const unsigned char *>(&receiver) +
                                       kReceiverRangeSubObjectOffset,
        "0x006a28f0 receives the address receiver + 0x18 from LEA ECX,[EDI+0x18]");
  check(g_trace.count >= 1 && g_trace.events[0] == 'R',
        "the resize is the first transfer in the body");
  check(g_trace.str() == "RP",
        "with an empty source range the resize is followed straight by the tail call");
  check(g_obs.decoy_calls == 0, "the table entry read is the one at 0x14");
}

// ---------------------------------------------------------------------------
// 3. The source range is read AFTER the resize
// ---------------------------------------------------------------------------
// 0x006a2ae0 CALL 0x006a28f0 precedes 0x006a2ae5 and 0x006a2ae8. The argument
// object is loaded with a one-element decoy range and the resize stub overwrites
// it with a two-element range, so a body that read the range first would walk
// the decoy: one dispatch, carrying the decoy's first word.
void test_the_source_range_is_read_after_the_resize() {
  Receiver receiver;
  Argument argument;
  const ProbeTable table = make_table_a();
  ElementBlock decoy;
  ElementBlock planted;
  const TargetWord decoy_words[1] = {0xd0ec0001u};
  const TargetWord planted_words[2] = {0x1111u, 0x2222u};
  poison(receiver);
  poison(argument);
  poison(decoy);
  poison(planted);
  fill_elements(decoy.elements, 1, decoy_words);
  fill_elements(planted.elements, 2, planted_words);
  plant_table_word(receiver, &table);
  receiver.parent_word = kParentWord;
  plant_range(argument, decoy.elements, decoy.elements + 1);
  reset_observation();
  g_obs.resize_plants_range = true;
  g_obs.plant_target = &argument;
  g_obs.plant_begin = planted.elements;
  g_obs.plant_end = planted.elements + 2;

  App_DirectPropertyList_CopyFrom_006a2ad0(&receiver, &argument);

  check(g_obs.resize_calls == 1, "the resize still runs exactly once");
  check(argument.range_begin == planted.elements &&
            argument.range_end == planted.elements + 2,
        "the resize stub did overwrite the argument's +0x18 / +0x1c words");
  check(g_obs.slot_call_count == 2,
        "the walk uses the range the resize planted, not the one already in the argument");
  check(g_obs.slot_call_count >= 1 && g_obs.slot_calls[0].first_word == 0x1111u,
        "the first dispatch carries the first planted element's word");
  check(g_obs.slot_call_count >= 2 && g_obs.slot_calls[1].first_word == 0x2222u,
        "the second dispatch carries the second planted element's word");
  bool saw_decoy = false;
  for (int i = 0; i < g_obs.slot_call_count; ++i) {
    saw_decoy = saw_decoy || g_obs.slot_calls[i].first_word == decoy_words[0];
  }
  check(!saw_decoy, "no dispatch carries the decoy element's word");
  check(g_trace.str() == "R11P", "the trace is resize, two dispatches, tail call");
}

// ---------------------------------------------------------------------------
// 4. The empty source range
// ---------------------------------------------------------------------------
// 0x006a2aeb CMP ESI,EBX / 0x006a2aed JZ 0x006a2b07. begin == end skips the
// loop body entirely, and the tail block at 0x006a2b07 is still reached, so the
// 0x006a1710 call happens exactly once with nothing dispatched.
void test_empty_source_range_skips_the_loop_but_reaches_the_tail() {
  Receiver receiver;
  Argument argument;
  const ProbeTable table = make_table_a();
  ElementBlock block;
  const TargetWord first_words[2] = {0xaaaa0001u, 0xaaaa0002u};
  poison(receiver);
  poison(argument);
  poison(block);
  fill_elements(block.elements, 2, first_words);
  plant_table_word(receiver, &table);
  receiver.parent_word = kParentWord;
  // begin == end, and both non-null.
  plant_range(argument, block.elements, block.elements);
  reset_observation();

  App_DirectPropertyList_CopyFrom_006a2ad0(&receiver, &argument);

  check(g_obs.resize_calls == 1, "the empty range does not skip the resize");
  check(g_obs.slot_call_count == 0,
        "begin == end skips the loop body: no slot transfer is dispatched");
  check(g_obs.set_parent_calls == 1,
        "the empty-range path still reaches 0x006a1710 exactly once");
  check(g_trace.str() == "RP", "the empty-range trace is resize then tail call");
  check(g_obs.set_parent_receiver == &receiver,
        "the tail call's receiver is the same self");
  check(g_obs.set_parent_argument ==
            reinterpret_cast<const void *>(
                static_cast<std::uintptr_t>(kParentWord)),
        "the tail call's argument is the word stored at receiver + 0x30");
}

// ---------------------------------------------------------------------------
// 5. One dispatch per element, in order, with all three arguments
// ---------------------------------------------------------------------------
// 0x006a2af0..0x006a2b00: the cursor walks 0x18 at a time and the block
// 0x006a2af0..0x006a2afe runs once per element. Three elements with distinct
// first words pin the order, the stride and both ordinary arguments.
void test_n_elements_dispatch_n_times_in_order() {
  Receiver receiver;
  Argument argument;
  const ProbeTable table = make_table_a();
  ElementBlock block;
  const TargetWord first_words[3] = {0x00000011u, 0x0000b22fu, 0x7fabcde3u};
  poison(receiver);
  poison(argument);
  poison(block);
  fill_elements(block.elements, 3, first_words);
  plant_table_word(receiver, &table);
  receiver.parent_word = kParentWord;
  plant_range(argument, block.elements, block.elements + 3);
  reset_observation();

  App_DirectPropertyList_CopyFrom_006a2ad0(&receiver, &argument);

  check(g_obs.slot_call_count == 3,
        "three elements produce exactly three slot transfers");
  bool every_dispatch_stayed_in_range = true;
  for (int i = 0; i < 3 && i < g_obs.slot_call_count; ++i) {
    check(g_obs.slot_calls[i].first_word == first_words[i],
          "the slot's first argument is the element's first word, in order");
    check(g_obs.slot_calls[i].receiver == &receiver,
          "the slot's hidden receiver is the same self on every dispatch");
    check(g_obs.slot_calls[i].second_argument ==
              second_argument_for(block.elements[i]),
          "the slot's second argument is the ADDRESS element + 0x4, not its value");
    every_dispatch_stayed_in_range =
        every_dispatch_stayed_in_range &&
        within_elements(g_obs.slot_calls[i].second_argument, block.elements, 3);
  }
  check(every_dispatch_stayed_in_range,
        "every dispatch addresses a real element: the cursor stepped by exactly 0x18");
  check(g_trace.str() == "R111P",
        "the trace is one resize, three dispatches, tail call");
  check(g_obs.decoy_calls == 0,
        "no table word other than the one at 0x14 is ever read");
}

// ---------------------------------------------------------------------------
// 6. The table load is inside the loop
// ---------------------------------------------------------------------------
// 0x006a2af0 MOV EAX,[EDI] and 0x006a2af4 MOV EAX,[EAX + 0x14] are inside the
// loop body, not hoisted before it. The first stub overwrites the receiver's
// table word with a second table, so the second element can only dispatch
// through the second table's entry if the word is re-read per iteration.
//
// The receiver and both tables are byte-compared around the call, so the only
// word that changes anywhere is the one the stub itself wrote.
void test_the_slot_is_re_read_for_every_element() {
  Receiver receiver;
  Argument argument;
  const ProbeTable table_a = make_table_a();
  const ProbeTable table_b = make_table_b();
  ElementBlock block;
  const TargetWord first_words[2] = {0x0badf00du, 0x0badf00eu};
  unsigned char receiver_before[sizeof(Receiver)];
  unsigned char table_a_before[sizeof(ProbeTable)];
  unsigned char table_b_before[sizeof(ProbeTable)];
  poison(receiver);
  poison(argument);
  poison(block);
  fill_elements(block.elements, 2, first_words);
  plant_table_word(receiver, &table_a);
  receiver.parent_word = kParentWord;
  plant_range(argument, block.elements, block.elements + 2);
  std::memcpy(receiver_before, &receiver, sizeof receiver_before);
  std::memcpy(table_a_before, &table_a, sizeof table_a_before);
  std::memcpy(table_b_before, &table_b, sizeof table_b_before);
  reset_observation();
  g_obs.slot_swaps_table_on_first_call = true;
  g_obs.replacement_table = &table_b;

  App_DirectPropertyList_CopyFrom_006a2ad0(&receiver, &argument);

  check(g_obs.slot_call_count == 2, "both elements are dispatched");
  check(g_obs.slot_call_count >= 1 && g_obs.slot_calls[0].via != nullptr &&
            std::strcmp(g_obs.slot_calls[0].via, "table_a") == 0,
        "the first element dispatches through the first table's entry at 0x14");
  check(g_obs.slot_call_count >= 2 && g_obs.slot_calls[1].via != nullptr &&
            std::strcmp(g_obs.slot_calls[1].via, "table_b") == 0,
        "the second element dispatches through the SECOND table's entry at 0x14");
  check(g_trace.str() == "R12P",
        "the trace shows the two dispatches reaching different tables");
  check(word_at(&receiver, kReceiverTableWordOffset) ==
            reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table_b)),
        "the receiver's table word at 0x0 is the second table after the swap");
  check(std::memcmp(table_a_before, &table_a, sizeof table_a_before) == 0,
        "the first table is not written");
  check(std::memcmp(table_b_before, &table_b, sizeof table_b_before) == 0,
        "the second table is not written");
  check(g_obs.decoy_calls == 0,
        "only the entry at table + 0x14 is read; no other table word fires");
  check(receiver.parent_word == kParentWord,
        "the word at receiver + 0x30 survives both dispatches");
  // The one word the stub itself wrote is masked out; every other byte of the
  // receiver must be exactly as it was.
  unsigned char receiver_masked[sizeof(Receiver)];
  std::memcpy(receiver_masked, &receiver, sizeof receiver_masked);
  std::memcpy(receiver_masked + kReceiverTableWordOffset,
              receiver_before + kReceiverTableWordOffset, sizeof(TargetWord));
  check(std::memcmp(receiver_masked, receiver_before, sizeof receiver_before) == 0,
        "the body writes no receiver byte outside the one the stub itself wrote");
}

// ---------------------------------------------------------------------------
// 7. The tail call runs once, after the loop
// ---------------------------------------------------------------------------
// 0x006a2b07..0x006a2b0d is reached from both the empty-range path and the
// loop-exit path. The last dispatch records a marker and the tail call's marker
// must come after it, on the non-empty path too.
void test_set_parent_runs_once_after_the_loop() {
  Receiver receiver;
  Argument argument;
  const ProbeTable table = make_table_a();
  ElementBlock block;
  const TargetWord first_words[2] = {0x00000021u, 0x00000022u};
  poison(receiver);
  poison(argument);
  poison(block);
  fill_elements(block.elements, 2, first_words);
  plant_table_word(receiver, &table);
  receiver.parent_word = kParentWord;
  plant_range(argument, block.elements, block.elements + 2);
  reset_observation();

  App_DirectPropertyList_CopyFrom_006a2ad0(&receiver, &argument);

  check(g_obs.set_parent_calls == 1,
        "0x006a1710 runs exactly once on the non-empty path too");
  check(g_obs.slot_call_count == 2 &&
            g_obs.set_parent_event > g_obs.slot_calls[1].event_index,
        "the tail call's marker comes after the last dispatch's marker");
  check(g_obs.set_parent_event > g_obs.resize_event,
        "the tail call comes after the resize");
  check(g_obs.set_parent_receiver == &receiver,
        "the tail call's receiver is self, from MOV ECX,EDI at 0x006a2b0b");
  check(g_obs.set_parent_argument ==
            reinterpret_cast<const void *>(
                static_cast<std::uintptr_t>(kParentWord)),
        "the tail call's argument is the VALUE at receiver + 0x30, not its address");
  check(g_trace.str() == "R11P",
        "the tail call is the last transfer in the body");
}

// ---------------------------------------------------------------------------
// 8. The body writes nothing
// ---------------------------------------------------------------------------
// The listing contains no store to the receiver, to the argument object or to
// any element: every access it makes is a load or a LEA. All three paths are
// byte-compared with read-only observers, so nothing else can be blamed for a
// change.
//
// One limit stated plainly: a store that wrote back the value it had just read
// would leave the bytes identical and would pass here. That store is not
// observable through this interface and is not claimed to be excluded; every
// store that changes a byte is.
void test_the_body_writes_nothing() {
  struct Path {
    const char *name;
    bool self_copy;
    int element_count;
  };
  const Path paths[3] = {
      {"self-copy", true, 0},
      {"empty-range", false, 0},
      {"three-elements", false, 3},
  };
  const TargetWord first_words[3] = {0x30000001u, 0x30000002u, 0x30000003u};

  for (const Path &path : paths) {
    Receiver receiver;
    Argument argument;
    const ProbeTable table = make_table_a();
    ElementBlock block;
    unsigned char receiver_before[sizeof(Receiver)];
    unsigned char argument_before[sizeof(Argument)];
    unsigned char table_before[sizeof(ProbeTable)];
    unsigned char element_before[sizeof(block.elements)];
    poison(receiver);
    poison(argument);
    poison(block);
    fill_elements(block.elements, 3, first_words);
    plant_table_word(receiver, &table);
    receiver.parent_word = kParentWord;
    plant_range(argument, block.elements,
                block.elements + path.element_count);
    std::memcpy(receiver_before, &receiver, sizeof receiver_before);
    std::memcpy(argument_before, &argument, sizeof argument_before);
    std::memcpy(table_before, &table, sizeof table_before);
    std::memcpy(element_before, block.elements, sizeof element_before);
    reset_observation();

    if (path.self_copy) {
      App_DirectPropertyList_CopyFrom_006a2ad0(&receiver, &receiver);
    } else {
      App_DirectPropertyList_CopyFrom_006a2ad0(&receiver, &argument);
    }

    check_path(std::memcmp(receiver_before, &receiver, sizeof receiver_before) == 0,
               path.name, "no byte of the receiver is written");
    check_path(std::memcmp(argument_before, &argument, sizeof argument_before) == 0,
               path.name, "no byte of the argument object is written");
    check_path(std::memcmp(table_before, &table, sizeof table_before) == 0, path.name,
               "no byte of the receiver's table is written");
    check_path(
        std::memcmp(element_before, block.elements, sizeof element_before) == 0,
        path.name, "no byte of any element is written");
    check_path(g_obs.decoy_calls == 0, path.name,
               "no table word other than 0x14 is read");
  }
}

// ---------------------------------------------------------------------------
// 9. The displacement pins, restated at run time
// ---------------------------------------------------------------------------
// Every one of these is a displacement the 33-instruction listing shows
// verbatim. They are restated here so the header's constants are checked
// against the literals the listing carries, and so the element fixture's layout
// is proved to be the one the body's 0x18-stride walk and its uint32_t load of
// element + 0x0 actually require.
void test_the_displacement_pins() {
  check(kReceiverTableWordOffset == 0x00u,
        "receiver + 0x0: MOV EAX,[EDI] at 0x006a2af0");
  check(kReceiverRangeSubObjectOffset == 0x18u,
        "receiver + 0x18: LEA ECX,[EDI+0x18] at 0x006a2add");
  check(kReceiverParentWordOffset == 0x30u,
        "receiver + 0x30: MOV ECX,[EDI+0x30] at 0x006a2b07");
  check(kSourceRangeBeginOffset == 0x18u,
        "argument + 0x18: MOV ESI,[EBX+0x18] at 0x006a2ae5");
  check(kSourceRangeEndOffset == 0x1cu,
        "argument + 0x1c: MOV EBX,[EBX+0x1c] at 0x006a2ae8");
  check(kElementFirstWordOffset == 0x00u,
        "element + 0x0: MOV EDX,[ESI] at 0x006a2af2");
  check(kElementSecondFieldOffset == 0x04u,
        "element + 0x4: LEA ECX,[ESI+0x4] at 0x006a2af7");
  check(kElementStride == 0x18u, "element stride: ADD ESI,0x18 at 0x006a2b00");
  check(kTableEntryOffset == 0x14u,
        "table + 0x14: MOV EAX,[EAX+0x14] at 0x006a2af4");
  check(sizeof(void *) == 4u, "a pointer is one 32-bit word");
  check(sizeof(Element) == 0x18u, "the element fixture is exactly one stride");
  check(offsetof(Element, first_word) == 0x00u,
        "the element's first word sits at element + 0x0");
  check(offsetof(Element, second_field) == 0x04u,
        "the element's second field sits at element + 0x4");
  check(offsetof(Receiver, table_word) == 0x00u,
        "the fixture's table word sits at receiver + 0x0");
  check(offsetof(Receiver, range_sub_object) == 0x18u,
        "the fixture's resize sub-object sits at receiver + 0x18");
  check(offsetof(Receiver, parent_word) == 0x30u,
        "the fixture's tail word sits at receiver + 0x30");
  check(offsetof(Argument, range_begin) == 0x18u,
        "the fixture's range begin sits at argument + 0x18");
  check(offsetof(Argument, range_end) == 0x1cu,
        "the fixture's range end sits at argument + 0x1c");
  check(offsetof(ProbeTable, entry) == 0x14u,
        "the transferred entry sits at table + 0x14");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_direct_property_copyfrom_wave14

int main() {
  using namespace openspore::reconstruction::pkg_direct_property_copyfrom_wave14;
  test_self_copy_skips_the_entire_body();
  test_resize_runs_once_with_the_receiver_sub_object();
  test_the_source_range_is_read_after_the_resize();
  test_empty_source_range_skips_the_loop_but_reaches_the_tail();
  test_n_elements_dispatch_n_times_in_order();
  test_the_slot_is_re_read_for_every_element();
  test_set_parent_runs_once_after_the_loop();
  test_the_body_writes_nothing();
  test_the_displacement_pins();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d of %d check(s) failed\n", g_failures, g_checks);
    return 1;
  }
  std::fprintf(stderr, "all %d checks passed\n", g_checks);
  return 0;
}

#undef PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_CDECL
#undef PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_TEST_THISCALL
