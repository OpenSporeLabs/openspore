// Model test for the four bodies of pkg_property_safe_wave9: 0x006a1600,
// 0x006a1e50, 0x006a2a40 and 0x006a3070.
//
// The test is written to falsify, not to exercise. Every check names the
// reconstruction mistake it would catch, and the load-bearing ones are pairs: a
// receiver slot and its neighbour, a table and a decoy at the same
// displacement, the receiver's span and the destination vector, a word and the
// byte beside it. A test that only walked the happy path would pass on a body
// that read the wrong slot, dispatched one level too few, indexed where it
// should displace, or conflated two objects' fields -- which is exactly the
// class of mistake this package's evidence cannot rule out from the outside.
//
// Nothing here reaches into a reconstructed object through a named member,
// because the package declares none: the fixtures are byte arrays and every
// access in the test is a displacement, the same vocabulary the bodies use. A
// test that reached into a struct would be asserting the very layout the header
// refuses to claim.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include "property_safe_wave9.hpp"

namespace openspore::reconstruction::pkg_property_safe_wave9 {
namespace {

#if defined(_MSC_VER)
#define PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL __thiscall
#else
#define PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL __attribute__((thiscall))
#endif

// --- reporting --------------------------------------------------------------

std::size_t g_checks = 0;
std::size_t g_failures = 0;

// Failures go to stderr, which is unbuffered: a later check may abort the
// process (a mutation that makes a copy loop unbounded will), and a named
// failure must survive that instead of being lost in a full stdout buffer.
void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL: %s\n", what);
  }
}

void check_word(TargetWord got, TargetWord want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::fprintf(stderr, "FAIL: %s (got 0x%x, want 0x%x)\n", what, got, want);
  }
}

// --- signatures -------------------------------------------------------------
//
// These assert the shape this reconstruction declares for itself, not a
// convention proved by the body. What the bodies do prove is that each explicit
// argument is one 32-bit word and that the immediate in each RET says the callee
// removed it; that is checked below by observing the port calls, one word per
// argument and no other.

using AddFromSignature = void(PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL*)(
    OpaquePropertyList*, OpaquePropertyList*);
using GetAltSignature = bool(PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL*)(
    OpaquePropertyList*, TargetWord, OpaqueProperty**);
using CopyFromSignature = void(PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL*)(
    OpaquePropertyList*, OpaquePropertyList*);
using GetIdsSignature = void(PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL*)(
    OpaquePropertyList*, OpaqueWordVector*);

static_assert(
    std::is_same<decltype(&direct_property_list_add_properties_from_006a1600),
                 AddFromSignature>::value,
    "006a1600 takes a receiver and one explicit word (RET 0x4)");
static_assert(
    std::is_same<decltype(&direct_property_list_get_property_alt_006a1e50),
                 GetAltSignature>::value,
    "006a1e50 takes a receiver and two explicit words (RET 0x8)");
static_assert(std::is_same<decltype(&property_list_copy_from_006a2a40),
                           CopyFromSignature>::value,
              "006a2a40 takes a receiver and one explicit word (RET 0x4)");
static_assert(std::is_same<decltype(&property_list_get_property_ids_006a3070),
                           GetIdsSignature>::value,
              "006a3070 takes a receiver and one explicit word (RET 0x4)");

// --- the displacement vocabulary, pinned by value ---------------------------
//
// Compared against the value the listing prints, not against a spelling: a test
// that compared text would pass a wrong constant written the same way.

static_assert(kReceiverTableDisplacement == 0x00,
              "006a1617/006a1e59 read the table word at displacement 0");
static_assert(kAddFromCounterDisplacement == 0x34,
              "006a162e is INC dword ptr [EDI + 0x34]");
static_assert(kGetAltLimitDisplacement == 0x38,
              "006a1e54 is CMP EAX,dword ptr [ECX + 0x38]");
static_assert(kCopyFromParentDisplacement == 0x30,
              "006a2a61 is MOV EAX,dword ptr [ESI + 0x30]");
static_assert(kSpanFirstDisplacement == 0x18,
              "006a1610/006a3097 read the first cursor at +0x18");
static_assert(kSpanLastDisplacement == 0x1c,
              "006a160c/006a3073 read the last cursor at +0x1c");
static_assert(kEntrySecondWordDisplacement == 0x04,
              "006a161e is LEA ECX,[ESI + 0x4]");
static_assert(kRegionByteDisplacement == 0x14,
              "006a2a5b/006a2a5e move one byte at +0x14 inside the region");
static_assert(kEntryStride == 0x18,
              "006a1627/006a30a9 advance the cursor by 0x18");
static_assert(kSetSlotDisplacement == 0x14,
              "006a161b is MOV EAX,dword ptr [EAX + 0x14]");
static_assert(kGetObjectSlotDisplacement == 0x28,
              "006a1e5c is MOV EAX,dword ptr [EDX + 0x28]");
static_assert(sizeof(TargetWord) == 4, "a word on the target is 32-bit");

// --- fixtures ---------------------------------------------------------------

// A receiver as raw bytes. The size is the test's own choice: the machine bounds
// what a body *reaches*, not how large the object is, so this is only required
// to cover the highest displacement any of the four bodies touches (0x38 plus
// its four bytes) with room for the composed +0x2c byte and the canaries.
constexpr std::size_t kReceiverBytes = 0x80;
constexpr std::uint8_t kCanary = 0xa5;
constexpr TargetWord kCanaryWord = static_cast<TargetWord>(kCanary) * 0x01010101u;

struct FakeList {
  alignas(TargetWord) std::array<std::uint8_t, kReceiverBytes> bytes{};

  std::uint8_t* raw() { return bytes.data(); }
  const std::uint8_t* raw() const { return bytes.data(); }
  OpaquePropertyList* as_list() {
    return reinterpret_cast<OpaquePropertyList*>(raw());
  }
  OpaquePropertyMap* region() {
    return reinterpret_cast<OpaquePropertyMap*>(raw() + kSpanFirstDisplacement);
  }

  void poison() { bytes.fill(kCanary); }
  TargetWord word(TargetWord displacement) const {
    return load_word(raw() + displacement);
  }
  void put_word(TargetWord displacement, TargetWord value) {
    store_word(raw() + displacement, value);
  }
};

// A table: the words a two-level load reads out of. Every slot this package
// could reach is left at the canary except the ones a test fills, so a body that
// read the wrong slot has nothing plausible to call.
constexpr std::size_t kTableWords = 16;

struct FakeTable {
  alignas(TargetWord) std::array<std::uint8_t, kTableWords * 4> bytes{};

  std::uint8_t* raw() { return bytes.data(); }
  void poison() { bytes.fill(kCanary); }
  void put_slot(TargetWord displacement, TargetWord address) {
    store_word(raw() + displacement, address);
  }
};

// A function pointer as the word a table slot holds.
template <typename Fn>
TargetWord slot_address(Fn fn) {
  TargetWord value = 0;
  static_assert(sizeof(Fn) == sizeof(TargetWord), "a slot is one word");
  std::memcpy(&value, &fn, sizeof value);
  return value;
}

// An entry span: `count` entries of kEntryStride bytes, each first word set to a
// distinct key so a wrong stride cannot produce the right sequence. The bytes
// between keys are canary, so a stride that is not 0x18 reads poison.
constexpr std::size_t kEntrySlots = 8;

struct FakeEntries {
  alignas(TargetWord) std::array<std::uint8_t, kEntrySlots * kEntryStride> bytes{};

  std::uint8_t* raw() { return bytes.data(); }
  std::uint8_t* at(std::size_t index) { return raw() + index * kEntryStride; }
  void put_key(std::size_t index, TargetWord key) { store_word(at(index), key); }
  // The second word of an entry, which 0x006a1600 hands to the slot. It is
  // filled with a pattern the first word never holds, so "the address is the
  // entry's second word" and "the address is the entry" are distinguishable.
  void put_second(std::size_t index, TargetWord value) {
    store_word(at(index) + kEntrySecondWordDisplacement, value);
  }
};

// --- observed ports ---------------------------------------------------------

std::vector<std::string> events;

struct SetRecord {
  OpaquePropertyList* receiver = nullptr;
  TargetWord id = 0;
  OpaqueProperty* value = nullptr;
};
std::vector<SetRecord> set_calls;
std::size_t decoy_set_calls = 0;

std::size_t fetch_calls = 0;
std::size_t decoy_fetch_calls = 0;
OpaqueProperty* fetch_result = nullptr;
TargetWord fetch_id = 0;

struct MapCopyRecord {
  OpaquePropertyMap* destination = nullptr;
  OpaquePropertyMap* source = nullptr;
};
std::vector<MapCopyRecord> map_copy_calls;

std::size_t set_parent_calls = 0;
OpaquePropertyList* set_parent_receiver = nullptr;
OpaquePropertyList* set_parent_argument = nullptr;

struct ResizeRecord {
  OpaqueWordVector* vector = nullptr;
  TargetWord count = 0;
};
std::vector<ResizeRecord> resize_calls;

std::size_t base_calls = 0;
OpaquePropertyList* base_receiver = nullptr;
TargetWord base_id = 0;
OpaqueProperty** base_result = nullptr;
bool base_answer = false;
OpaqueProperty* base_value = nullptr;

// What the parent chain's +0x20 slot saw, when the default base port defers to
// it. See `defer_hook` for why it needs its own shape.
std::size_t defer_calls = 0;
OpaquePropertyList* defer_receiver = nullptr;
TargetWord defer_id = 0;
OpaqueProperty** defer_result = nullptr;
bool defer_answer = false;
OpaqueProperty* defer_value = nullptr;

// A property object the ports hand back. No body in this package dereferences
// it and neither does the test: only its address is ever compared.
alignas(TargetWord) std::array<std::uint8_t, 32> property_object{};

OpaqueProperty* the_property() {
  return reinterpret_cast<OpaqueProperty*>(property_object.data());
}

// What the map-copy hook under test rewrites before returning, so the body's
// read of the +0x30 word *after* the call is observable.
OpaquePropertyList* rewrite_target = nullptr;
TargetWord rewrite_value = 0;

// The buffer a replacing resize port re-points the destination vector at, and
// the receiver a collapsing resize port empties. Both are the two load-ordering
// probes of 0x006a3070; see the hooks below.
std::array<TargetWord, 8>* resize_target = nullptr;
OpaquePropertyList* collapsing_target = nullptr;

void reset_counters() {
  events.clear();
  set_calls.clear();
  decoy_set_calls = 0;
  fetch_calls = 0;
  decoy_fetch_calls = 0;
  fetch_result = nullptr;
  fetch_id = 0;
  map_copy_calls.clear();
  set_parent_calls = 0;
  set_parent_receiver = nullptr;
  set_parent_argument = nullptr;
  resize_calls.clear();
  base_calls = 0;
  base_receiver = nullptr;
  base_id = 0;
  base_result = nullptr;
  base_answer = false;
  base_value = nullptr;
  defer_calls = 0;
  defer_receiver = nullptr;
  defer_id = 0;
  defer_result = nullptr;
  defer_answer = false;
  defer_value = nullptr;
  rewrite_target = nullptr;
  rewrite_value = 0;
  resize_target = nullptr;
  collapsing_target = nullptr;
}

void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL set_hook(OpaquePropertyList* list,
                                                    TargetWord id,
                                                    OpaqueProperty* value) {
  events.push_back("set");
  set_calls.push_back(SetRecord{list, id, value});
}

// A decoy with the *same* shape as the real slot, so a body that dispatched the
// wrong one reports a clean failure instead of jumping through a mismatched
// pointer.
void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL decoy_set_hook(OpaquePropertyList*,
                                                           TargetWord,
                                                           OpaqueProperty*) {
  ++decoy_set_calls;
}

OpaqueProperty* PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL fetch_hook(
    OpaquePropertyList*, TargetWord id) {
  events.push_back("fetch");
  ++fetch_calls;
  fetch_id = id;
  return fetch_result;
}

OpaqueProperty* PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL decoy_fetch_hook(
    OpaquePropertyList*, TargetWord) {
  ++decoy_fetch_calls;
  return nullptr;
}

void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL map_copy_hook(
    OpaquePropertyMap* destination, OpaquePropertyMap* source) {
  events.push_back("map_copy");
  map_copy_calls.push_back(MapCopyRecord{destination, source});
}

void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL map_copy_rewrite_hook(
    OpaquePropertyMap*, OpaquePropertyMap*) {
  events.push_back("map_copy");
  map_copy_calls.push_back(MapCopyRecord{nullptr, nullptr});
  if (rewrite_target != nullptr) {
    store_word(byte_view(rewrite_target) + kCopyFromParentDisplacement,
               rewrite_value);
  }
}

void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL set_parent_hook(
    OpaquePropertyList* list, OpaquePropertyList* parent) {
  events.push_back("set_parent");
  ++set_parent_calls;
  set_parent_receiver = list;
  set_parent_argument = parent;
}

void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL resize_hook(OpaqueWordVector* vector,
                                                       TargetWord count) {
  events.push_back("resize");
  resize_calls.push_back(ResizeRecord{vector, count});
}

// A resize port that re-points the vector's first word at a second buffer, so a
// body that read that word before calling the port is distinguishable from one
// that reads it after -- which is the order 0x006a3070's listing shows.
void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL replacing_resize_hook(
    OpaqueWordVector* vector, TargetWord count) {
  events.push_back("resize");
  resize_calls.push_back(ResizeRecord{vector, count});
  if (resize_target != nullptr) {
    store_word(byte_view(vector),
               static_cast<TargetWord>(
                   reinterpret_cast<std::uintptr_t>(resize_target->data())));
    store_word(byte_view(vector) + sizeof(TargetWord),
               count * sizeof(TargetWord));
  }
}

// A resize port that empties the receiver's span, which 0x006a3070 re-reads
// *after* the call (MOV EAX,[ESI + 0x18] / CMP EAX,[ESI + 0x1c]). It is how a
// reversed span -- whose quotient is negative and whose copy loop would never
// terminate on the machine either -- can be exercised without running that loop,
// and it doubles as a check that the span words are read after the port returns.
void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL collapsing_resize_hook(
    OpaqueWordVector* vector, TargetWord count) {
  events.push_back("resize");
  resize_calls.push_back(ResizeRecord{vector, count});
  if (collapsing_target != nullptr) {
    const TargetWord empty = load_word(byte_view(collapsing_target) +
                                       kSpanFirstDisplacement);
    store_word(byte_view(collapsing_target) + kSpanLastDisplacement, empty);
  }
}

bool PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL base_hook(OpaquePropertyList* list,
                                                     TargetWord id,
                                                     OpaqueProperty** result) {
  events.push_back("base");
  ++base_calls;
  base_receiver = list;
  base_id = id;
  base_result = result;
  if (base_answer) {
    *result = base_value;
  }
  return base_answer;
}

// A hook with the *base-lookup* shape, for the parent chain's +0x20 slot. It has
// to match that slot's declared type exactly: a thiscall callee removes its own
// stack words, so calling a one-word callee through a two-word slot pointer
// would unbalance the stack rather than fail a check.
bool PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL defer_hook(OpaquePropertyList* list,
                                                     TargetWord id,
                                                     OpaqueProperty** result) {
  events.push_back("defer");
  ++defer_calls;
  defer_receiver = list;
  defer_id = id;
  defer_result = result;
  if (defer_answer) {
    *result = defer_value;
  }
  return defer_answer;
}

PropertySafePorts observed_ports() {
  PropertySafePorts ports = property_safe_ports();
  ports.map_copy = map_copy_hook;
  ports.set_parent = set_parent_hook;
  ports.resize_words = resize_hook;
  ports.get_property_alt_base = base_hook;
  return ports;
}

// --- fixture builders -------------------------------------------------------

// Point a receiver's two span words at entries[0 .. count).
void arm_span(FakeList& list, FakeEntries& entries, std::size_t count) {
  list.put_word(
      kSpanFirstDisplacement,
      static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(entries.raw())));
  list.put_word(kSpanLastDisplacement,
                static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(
                    entries.raw() + count * kEntryStride)));
}

// Point a receiver's table word (displacement 0) at a table.
void arm_table(FakeList& list, FakeTable& table) {
  list.put_word(kReceiverTableDisplacement,
                static_cast<TargetWord>(
                    reinterpret_cast<std::uintptr_t>(table.raw())));
}

void arm_limit(FakeList& list, TargetWord limit) {
  list.put_word(kGetAltLimitDisplacement, limit);
}

void arm_parent(FakeList& list, OpaquePropertyList* parent) {
  list.put_word(kCopyFromParentDisplacement,
                static_cast<TargetWord>(
                    reinterpret_cast<std::uintptr_t>(parent)));
}

// Point a word vector's first word at a buffer, as 0x006a3070 expects to find.
void arm_vector(OpaqueWordVector& vector, TargetWord* buffer) {
  store_word(reinterpret_cast<std::uint8_t*>(&vector),
             static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(buffer)));
}

void arm_vector_end(OpaqueWordVector& vector, std::size_t words) {
  store_word(reinterpret_cast<std::uint8_t*>(&vector) + sizeof(TargetWord),
             static_cast<TargetWord>(words * sizeof(TargetWord)));
}

// ===========================================================================
// 0x006a1600 -- AddPropertiesFrom
// ===========================================================================

void test_006a1600_self_copy_touches_nothing() {
  FakeList list;
  FakeEntries entries;
  FakeTable table;
  list.poison();
  entries.bytes.fill(kCanary);
  table.poison();
  arm_span(list, entries, 3);
  arm_table(list, table);
  table.put_slot(kSetSlotDisplacement, slot_address(set_hook));
  list.put_word(kAddFromCounterDisplacement, 0x5a5a5a5au);
  list.put_word(0x30u, 0x11111111u);
  reset_counters();
  property_safe_set_ports(observed_ports());

  direct_property_list_add_properties_from_006a1600(list.as_list(),
                                                    list.as_list());

  check(set_calls.empty(),
        "006a1600: receiver == argument dispatches nothing (CMP EDI,EAX / JZ)");
  check_word(list.word(kAddFromCounterDisplacement), 0x5a5a5a5au,
             "006a1600: the early return leaves the +0x34 word alone");
  check_word(list.word(0x30u), 0x11111111u,
             "006a1600: the early return leaves the +0x30 word alone");
}

void test_006a1600_empty_span_still_increments() {
  FakeList list;
  FakeEntries entries;
  FakeList other;
  FakeTable table;
  list.poison();
  other.poison();
  entries.bytes.fill(kCanary);
  table.poison();
  arm_span(other, entries, 0);
  arm_table(list, table);
  table.put_slot(kSetSlotDisplacement, slot_address(set_hook));
  list.put_word(kAddFromCounterDisplacement, 41u);
  reset_counters();
  property_safe_set_ports(observed_ports());

  direct_property_list_add_properties_from_006a1600(list.as_list(),
                                                    other.as_list());

  check(set_calls.empty(),
        "006a1600: an empty argument span skips the loop (CMP ESI,EBX / JZ)");
  check_word(list.word(kAddFromCounterDisplacement), 42u,
             "006a1600: the +0x34 increment is reached on the empty-span path");
  check_word(other.word(kAddFromCounterDisplacement), kCanaryWord,
             "006a1600: the increment lands on the receiver, not the argument");
}

void test_006a1600_one_call_per_entry_in_order() {
  FakeList list;
  FakeEntries entries;
  FakeList other;
  FakeTable table;
  list.poison();
  other.poison();
  entries.bytes.fill(0);
  table.poison();
  arm_span(other, entries, 3);
  arm_table(list, table);
  table.put_slot(kSetSlotDisplacement, slot_address(set_hook));
  for (std::size_t index = 0; index < 3; ++index) {
    entries.put_key(index, 100u + static_cast<TargetWord>(index));
    entries.put_second(index, 0x80000000u + static_cast<TargetWord>(index));
  }
  list.put_word(kAddFromCounterDisplacement, 0u);
  reset_counters();
  property_safe_set_ports(observed_ports());

  direct_property_list_add_properties_from_006a1600(list.as_list(),
                                                    other.as_list());

  check(set_calls.size() == 3u,
        "006a1600: one slot call per entry in the argument's span");
  for (std::size_t index = 0; index < set_calls.size(); ++index) {
    check(set_calls[index].receiver == list.as_list(),
          "006a1600: ECX is the receiver, not the argument");
    // The id is the pointee's first word: the fixture gives the first and the
    // second word of every entry different values, so reading either of the
    // others, or the cursor, produces a different id.
    check_word(set_calls[index].id, 100u + static_cast<TargetWord>(index),
               "006a1600: the id is the first word of the entry (MOV EDX,[ESI])");
    // The pushed address is entry+0x04, not entry and not entry+0x18.
    check(set_calls[index].value ==
              reinterpret_cast<OpaqueProperty*>(entries.at(index) +
                                               kEntrySecondWordDisplacement),
          "006a1600: the pushed address is entry+0x04 (LEA ECX,[ESI + 0x4])");
  }
  check_word(list.word(kAddFromCounterDisplacement), 1u,
             "006a1600: the +0x34 word is incremented once per call, not per entry");
}

void test_006a1600_stride_is_a_displacement_not_an_index() {
  // A stride of 0x1c, of 0x14, or an element index would read keys the fixture
  // never wrote: the bytes between the keys are poisoned.
  FakeList list;
  FakeEntries entries;
  FakeList other;
  FakeTable table;
  list.poison();
  other.poison();
  entries.bytes.fill(kCanary);
  table.poison();
  arm_span(other, entries, 4);
  arm_table(list, table);
  table.put_slot(kSetSlotDisplacement, slot_address(set_hook));
  for (std::size_t index = 0; index < 4; ++index) {
    entries.put_key(index, 0x11110000u + static_cast<TargetWord>(index));
  }
  reset_counters();
  property_safe_set_ports(observed_ports());

  direct_property_list_add_properties_from_006a1600(list.as_list(),
                                                    other.as_list());

  check(set_calls.size() == 4u, "006a1600: four entries, four calls");
  for (std::size_t index = 0; index < set_calls.size(); ++index) {
    check_word(set_calls[index].id,
               0x11110000u + static_cast<TargetWord>(index),
               "006a1600: the entry stride is 0x18 bytes (ADD ESI,0x18)");
  }
}

void test_006a1600_slot_is_two_levels_deep_at_0x14() {
  // Two tables, one decoy per neighbouring slot, and a decoy word inside the
  // receiver at +0x14. A body that read the receiver's own +0x14 (one level)
  // would call the in-receiver decoy on both calls; a body that read the wrong
  // table slot would call a table decoy; a body that never followed the table
  // word would not call at all. Only the two-level load the listing shows
  // survives all three.
  FakeList list;
  FakeEntries entries;
  FakeList other;
  FakeTable first_table;
  FakeTable second_table;
  list.poison();
  other.poison();
  entries.bytes.fill(kCanary);
  first_table.poison();
  second_table.poison();
  arm_span(other, entries, 1);
  entries.put_key(0, 7u);
  first_table.put_slot(kSetSlotDisplacement, slot_address(set_hook));
  first_table.put_slot(0x10u, slot_address(decoy_set_hook));
  first_table.put_slot(0x18u, slot_address(decoy_set_hook));
  second_table.put_slot(kSetSlotDisplacement, slot_address(decoy_set_hook));
  list.put_word(0x14u, slot_address(decoy_set_hook));
  reset_counters();
  property_safe_set_ports(observed_ports());

  arm_table(list, first_table);
  direct_property_list_add_properties_from_006a1600(list.as_list(),
                                                    other.as_list());
  check(set_calls.size() == 1u,
        "006a1600: the first table's +0x14 slot is the one dispatched");
  check(decoy_set_calls == 0u,
        "006a1600: neither the neighbouring table slots nor the receiver's own "
        "+0x14 word is dispatched");
  check_word(list.word(0x14u), slot_address(decoy_set_hook),
             "006a1600: the decoy word inside the receiver is left alone");

  reset_counters();
  arm_table(list, second_table);
  direct_property_list_add_properties_from_006a1600(list.as_list(),
                                                    other.as_list());
  check(decoy_set_calls == 1u && set_calls.empty(),
        "006a1600: re-pointing the receiver's table word re-points the "
        "dispatch, so the slot is read out of the table");
}

void test_006a1600_counter_displacement_is_exact() {
  // Canary words on both sides of the real one, and a value that wraps: a
  // counter read or written at the wrong displacement moves two words, and a
  // counter updated by anything other than one produces a different value.
  FakeList list;
  FakeEntries entries;
  FakeList other;
  FakeTable table;
  list.poison();
  other.poison();
  entries.bytes.fill(kCanary);
  table.poison();
  arm_span(other, entries, 0);
  arm_table(list, table);
  table.put_slot(kSetSlotDisplacement, slot_address(set_hook));
  list.put_word(kAddFromCounterDisplacement, 0xffffffffu);
  reset_counters();
  property_safe_set_ports(observed_ports());

  direct_property_list_add_properties_from_006a1600(list.as_list(),
                                                    other.as_list());

  check_word(list.word(kAddFromCounterDisplacement), 0u,
             "006a1600: the +0x34 word wraps, so the update is a 32-bit INC");
  check_word(list.word(0x30u), kCanaryWord,
             "006a1600: the word below the counter is not the counter");
  check_word(list.word(0x38u), kCanaryWord,
             "006a1600: the word above the counter is not the counter");
}

void test_006a1600_writes_no_other_receiver_word() {
  FakeList list;
  FakeEntries entries;
  FakeList other;
  FakeTable table;
  list.poison();
  other.poison();
  entries.bytes.fill(kCanary);
  table.poison();
  arm_span(other, entries, 2);
  arm_table(list, table);
  table.put_slot(kSetSlotDisplacement, slot_address(set_hook));
  entries.put_key(0, 1u);
  entries.put_key(1, 2u);
  // The table word is arm_table's write and the counter starts at zero, so the
  // snapshot below differs from the final receiver in the counter alone.
  list.put_word(kAddFromCounterDisplacement, 0u);
  const std::array<std::uint8_t, kReceiverBytes> before = list.bytes;
  reset_counters();
  property_safe_set_ports(observed_ports());

  direct_property_list_add_properties_from_006a1600(list.as_list(),
                                                    other.as_list());

  // Not "four bytes changed": an increment from zero moves one byte. The claim
  // is that every byte that did move lies inside the +0x34 word, and that the
  // word's value is the increment.
  std::size_t moved = 0;
  bool all_inside_counter = true;
  for (std::size_t offset = 0; offset < kReceiverBytes; ++offset) {
    if (list.bytes[offset] != before[offset]) {
      ++moved;
      if (offset < kAddFromCounterDisplacement ||
          offset >= kAddFromCounterDisplacement + sizeof(TargetWord)) {
        all_inside_counter = false;
      }
    }
  }
  check(moved >= 1u, "006a1600: the counter word did change");
  check(all_inside_counter,
        "006a1600: every changed byte lies inside the +0x34 word, so no other "
        "receiver word is written");
  check_word(list.word(kAddFromCounterDisplacement), 1u,
             "006a1600: the +0x34 word is the one that moved, by one");
}

// ===========================================================================
// 0x006a1e50 -- GetPropertyAlt
// ===========================================================================

void test_006a1e50_limit_is_compared_unsigned() {
  // JNC is an unsigned compare. With the limit at 0x80000000 the id 0x80000000
  // must take the base path; a signed compare would read it as negative, find
  // it below the limit, and take the fast path.
  FakeList list;
  FakeTable table;
  list.poison();
  table.poison();
  arm_table(list, table);
  table.put_slot(kGetObjectSlotDisplacement, slot_address(fetch_hook));
  arm_limit(list, 0x80000000u);
  reset_counters();
  fetch_result = the_property();
  property_safe_set_ports(observed_ports());

  OpaqueProperty* result = nullptr;
  const bool found = direct_property_list_get_property_alt_006a1e50(
      list.as_list(), 0x80000000u, &result);

  check(!found, "006a1e50: an id equal to the limit takes the base path");
  check(fetch_calls == 0u,
        "006a1e50: a signed reading of the limit would have dispatched here");
  check(base_calls == 1u && base_id == 0x80000000u,
        "006a1e50: the base port receives the id unchanged");

  reset_counters();
  const bool below = direct_property_list_get_property_alt_006a1e50(
      list.as_list(), 0x7fffffffu, &result);
  check(below && fetch_calls == 1u,
        "006a1e50: the id just below the limit takes the fast path");
  check_word(fetch_id, 0x7fffffffu, "006a1e50: the id is pushed unchanged");
}

void test_006a1e50_zero_limit_always_uses_the_base() {
  FakeList list;
  FakeTable table;
  list.poison();
  table.poison();
  arm_table(list, table);
  table.put_slot(kGetObjectSlotDisplacement, slot_address(fetch_hook));
  arm_limit(list, 0u);
  reset_counters();
  property_safe_set_ports(observed_ports());

  OpaqueProperty* result = the_property();
  const bool found = direct_property_list_get_property_alt_006a1e50(
      list.as_list(), 0u, &result);
  check(!found && base_calls == 1u && fetch_calls == 0u,
        "006a1e50: with a zero limit no id is below it, so every id defers");
}

void test_006a1e50_fast_path_stores_the_pointee_it_was_given() {
  FakeList list;
  FakeTable table;
  FakeEntries entries;
  list.poison();
  table.poison();
  entries.bytes.fill(kCanary);
  arm_table(list, table);
  table.put_slot(kGetObjectSlotDisplacement, slot_address(fetch_hook));
  // A decoy in every neighbouring slot, and at displacement 0.
  table.put_slot(0x00u, slot_address(decoy_fetch_hook));
  table.put_slot(0x24u, slot_address(decoy_fetch_hook));
  table.put_slot(0x2cu, slot_address(decoy_fetch_hook));
  arm_limit(list, 4u);
  reset_counters();
  fetch_result = reinterpret_cast<OpaqueProperty*>(entries.at(2));
  property_safe_set_ports(observed_ports());

  OpaqueProperty* result = reinterpret_cast<OpaqueProperty*>(entries.raw());
  const bool found = direct_property_list_get_property_alt_006a1e50(
      list.as_list(), 2u, &result);

  check(found, "006a1e50: the fast path returns true (MOV AL,0x1)");
  check(fetch_calls == 1u, "006a1e50: exactly one slot call");
  check(decoy_fetch_calls == 0u,
        "006a1e50: the dispatched slot is the +0x28 one and no neighbour");
  check(base_calls == 0u, "006a1e50: the fast path never reaches the base port");
  check(result == fetch_result,
        "006a1e50: the out pointer receives the address the slot returned, not "
        "the receiver and not a copy of the property");
  check(result == reinterpret_cast<OpaqueProperty*>(entries.at(2)),
        "006a1e50: the stored address is the one the slot handed back");
  check_word(list.word(kAddFromCounterDisplacement), kCanaryWord,
             "006a1e50: this body writes no receiver word");
}

void test_006a1e50_slot_is_two_levels_deep_at_0x28() {
  FakeList list;
  FakeTable first_table;
  FakeTable second_table;
  list.poison();
  first_table.poison();
  second_table.poison();
  first_table.put_slot(kGetObjectSlotDisplacement, slot_address(fetch_hook));
  second_table.put_slot(kGetObjectSlotDisplacement,
                        slot_address(decoy_fetch_hook));
  // A decoy at the same displacement inside the receiver itself.
  list.put_word(0x28u, slot_address(decoy_fetch_hook));
  arm_limit(list, 4u);
  reset_counters();
  fetch_result = the_property();
  property_safe_set_ports(observed_ports());

  arm_table(list, first_table);
  OpaqueProperty* result = nullptr;
  direct_property_list_get_property_alt_006a1e50(list.as_list(), 1u, &result);
  check(fetch_calls == 1u && decoy_fetch_calls == 0u,
        "006a1e50: the first table's +0x28 slot is dispatched, and the "
        "receiver's own +0x28 word is not");

  reset_counters();
  arm_table(list, second_table);
  direct_property_list_get_property_alt_006a1e50(list.as_list(), 1u, &result);
  check(decoy_fetch_calls == 1u && fetch_calls == 0u,
        "006a1e50: the dispatch follows the receiver's table word, so re-"
        "pointing it re-points the slot");
}

void test_006a1e50_base_path_forwards_and_answers() {
  FakeList list;
  FakeTable table;
  list.poison();
  table.poison();
  arm_table(list, table);
  table.put_slot(kGetObjectSlotDisplacement, slot_address(fetch_hook));
  arm_limit(list, 2u);
  reset_counters();
  base_answer = true;
  base_value = the_property();
  property_safe_set_ports(observed_ports());

  OpaqueProperty* result = nullptr;
  const bool found = direct_property_list_get_property_alt_006a1e50(
      list.as_list(), 9u, &result);

  check(found,
        "006a1e50: the base path returns whatever the base routine returns");
  check(base_receiver == list.as_list(),
        "006a1e50: the tail-jump keeps the receiver in ECX");
  check(base_id == 9u, "006a1e50: the base port receives the id");
  check(base_result == &result, "006a1e50: the out pointer is forwarded, not copied");
  check(result == the_property(),
        "006a1e50: a base answer reaches the out pointer");
  check(fetch_calls == 0u, "006a1e50: the fast slot is not reached");
}

void test_006a1e50_base_miss_leaves_the_out_pointer_alone() {
  // MOV dword ptr [ECX],EAX sits on the fast path only. A body that stored
  // through the out pointer on the base path too would be claiming a write the
  // listing does not show.
  FakeList list;
  FakeTable table;
  list.poison();
  table.poison();
  arm_table(list, table);
  table.put_slot(kGetObjectSlotDisplacement, slot_address(fetch_hook));
  arm_limit(list, 1u);
  reset_counters();
  base_answer = false;
  property_safe_set_ports(observed_ports());

  OpaqueProperty* result = the_property();
  const bool found = direct_property_list_get_property_alt_006a1e50(
      list.as_list(), 1u, &result);

  check(!found, "006a1e50: the base path returns the base routine's false");
  check(result == the_property(),
        "006a1e50: a base miss does not write through the out pointer");
  check(fetch_calls == 0u, "006a1e50: a base miss does not dispatch the fast slot");
}

void test_006a1e50_limit_displacement_is_exact() {
  // A decoy limit planted one word below the real one. If the body read the
  // decoy, the boundary would move and the id 4 would take the fast path.
  FakeList list;
  FakeTable table;
  list.poison();
  table.poison();
  arm_table(list, table);
  table.put_slot(kGetObjectSlotDisplacement, slot_address(fetch_hook));
  list.put_word(kGetAltLimitDisplacement - 4u, 1u);
  arm_limit(list, 4u);
  reset_counters();
  fetch_result = the_property();
  property_safe_set_ports(observed_ports());

  OpaqueProperty* result = nullptr;
  direct_property_list_get_property_alt_006a1e50(list.as_list(), 3u, &result);
  check(fetch_calls == 1u, "006a1e50: the id 3 is below the +0x38 limit of 4");
  reset_counters();
  direct_property_list_get_property_alt_006a1e50(list.as_list(), 4u, &result);
  check(fetch_calls == 0u && base_calls == 1u,
        "006a1e50: the id 4 is not below it, so the boundary is the +0x38 word");
  check_word(list.word(kGetAltLimitDisplacement - 4u), 1u,
             "006a1e50: the decoy word below the limit is never read or written");
}

// ===========================================================================
// 0x006a2a40 -- CopyFrom
// ===========================================================================

void test_006a2a40_self_copy_touches_nothing() {
  FakeList list;
  list.poison();
  list.put_word(kSpanFirstDisplacement, 0x11111111u);
  list.put_word(kCopyFromParentDisplacement, 0x22222222u);
  list.raw()[0x2c] = 0x77u;
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_copy_from_006a2a40(list.as_list(), list.as_list());

  check(map_copy_calls.empty() && set_parent_calls == 0u,
        "006a2a40: receiver == argument reaches neither port (CMP ESI,EAX / JZ)");
  check(list.raw()[0x2c] == 0x77u,
        "006a2a40: the early return copies no byte");
}

void test_006a2a40_delegates_to_both_ports_in_order() {
  FakeList list;
  FakeList other;
  FakeList parent;
  list.poison();
  other.poison();
  parent.poison();
  arm_parent(list, parent.as_list());
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_copy_from_006a2a40(list.as_list(), other.as_list());

  check(map_copy_calls.size() == 1u, "006a2a40: one map-copy call");
  check(map_copy_calls[0].destination ==
            reinterpret_cast<OpaquePropertyMap*>(list.raw() + 0x18),
        "006a2a40: the destination is the receiver's own +0x18 (LEA EBX,[ESI + "
        "0x18])");
  check(map_copy_calls[0].source ==
            reinterpret_cast<OpaquePropertyMap*>(other.raw() + 0x18),
        "006a2a40: the source is the argument's own +0x18 (LEA EDI,[EAX + "
        "0x18]), not the argument");
  check(map_copy_calls[0].destination == list.region() &&
            map_copy_calls[0].source == other.region(),
        "006a2a40: both are the same +0x18 displacement on their own receiver");
  check(map_copy_calls[0].destination != other.region(),
        "006a2a40: the two regions are two different objects");
  check(set_parent_calls == 1u, "006a2a40: one SetParent call");
  check(set_parent_receiver == list.as_list(),
        "006a2a40: ECX is the receiver for SetParent");
  check(set_parent_argument == parent.as_list(),
        "006a2a40: the word at +0x30 is passed back, not the source list");
  check(events.size() == 2u && events[0] == "map_copy" &&
            events[1] == "set_parent",
        "006a2a40: the byte copy sits between the two calls, so the order is "
        "map-copy, byte copy, SetParent");
}

void test_006a2a40_moves_one_byte_and_only_one() {
  FakeList list;
  FakeList other;
  list.poison();
  other.poison();
  // The byte is at +0x14 inside a region that begins at +0x18, so on the receiver
  // it is at +0x2c. The source's neighbours carry values that are *not* the
  // canary and are all different from the moved byte: a canary on both sides
  // would be invisible to a word-wide move, because the bytes it dragged along
  // would be canary in the destination either way.
  static const std::uint8_t kSource[5] = {0x7b, 0xa7, 0x5c, 0x5d, 0x5e};
  for (std::size_t index = 0; index < 5; ++index) {
    other.raw()[0x2b + index] = kSource[index];
  }
  list.raw()[0x2c] = 0x5au;
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_copy_from_006a2a40(list.as_list(), other.as_list());

  check(list.raw()[0x2c] == 0xa7u,
        "006a2a40: the argument's byte lands on the receiver's +0x2c");
  check(other.raw()[0x2c] == 0xa7u, "006a2a40: the argument's byte is unchanged");
  check(list.raw()[0x2b] == kCanary && list.raw()[0x2d] == kCanary &&
            list.raw()[0x2e] == kCanary && list.raw()[0x2f] == kCanary,
        "006a2a40: the move is one byte wide, so the four bytes around it stay "
        "at their canary although the argument's differ from it");
  for (std::size_t index = 0; index < 5; ++index) {
    if (other.raw()[0x2b + index] != kSource[index]) {
      check(false, "006a2a40: a byte of the argument's region was written");
      break;
    }
  }
  check(true, "006a2a40: no byte of the argument's region is written");
  check(list.raw()[0x28] == kCanary && list.raw()[0x24] == kCanary,
        "006a2a40: the words around the moved byte are untouched");
}

void test_006a2a40_reads_the_parent_word_after_the_map_copy() {
  // MOV EAX,[ESI + 0x30] follows CALL 0x006a1e80. A hook that rewrites the word
  // is the discriminator: a body that read +0x30 before delegating would hand
  // SetParent the stale value.
  FakeList list;
  FakeList other;
  FakeList first_parent;
  FakeList second_parent;
  list.poison();
  other.poison();
  first_parent.poison();
  second_parent.poison();
  arm_parent(list, first_parent.as_list());
  reset_counters();
  PropertySafePorts ports = observed_ports();
  ports.map_copy = map_copy_rewrite_hook;
  property_safe_set_ports(ports);
  rewrite_target = list.as_list();
  rewrite_value = static_cast<TargetWord>(
      reinterpret_cast<std::uintptr_t>(second_parent.as_list()));

  property_list_copy_from_006a2a40(list.as_list(), other.as_list());

  check(map_copy_calls.size() == 1u, "006a2a40: the rewriting hook ran");
  check_word(list.word(kCopyFromParentDisplacement), rewrite_value,
             "006a2a40: the map-copy port's write to +0x30 is visible afterwards");
  check(set_parent_argument == second_parent.as_list(),
        "006a2a40: the +0x30 word is read after the map-copy port returns, so "
        "SetParent sees the value the port left behind");
}

void test_006a2a40_parent_displacement_is_exact() {
  FakeList list;
  FakeList other;
  FakeList parent;
  list.poison();
  other.poison();
  parent.poison();
  arm_parent(list, parent.as_list());
  // A decoy word one displacement above the real one, holding a different
  // address: a body that read +0x34 would hand SetParent the argument instead.
  list.put_word(kCopyFromParentDisplacement + 4u,
                static_cast<TargetWord>(
                    reinterpret_cast<std::uintptr_t>(other.as_list())));
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_copy_from_006a2a40(list.as_list(), other.as_list());

  check(set_parent_argument == parent.as_list(),
        "006a2a40: the word at +0x30 is the one handed to SetParent, not the "
        "neighbouring word");
}

void test_006a2a40_writes_no_other_receiver_byte() {
  FakeList list;
  FakeList other;
  list.poison();
  other.poison();
  const std::array<std::uint8_t, kReceiverBytes> before = list.bytes;
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_copy_from_006a2a40(list.as_list(), other.as_list());

  std::size_t moved = 0;
  for (std::size_t offset = 0; offset < kReceiverBytes; ++offset) {
    if (list.bytes[offset] != before[offset]) {
      ++moved;
    }
  }
  check(moved == 0u || (moved == 1u && list.bytes[0x2c] != before[0x2c]),
        "006a2a40: the only receiver byte this body can write is +0x2c");
  check(list.raw()[0x2c] == kCanary,
        "006a2a40: with a canary on both sides the copied byte is the canary "
        "itself, so exactly one byte moved");
}

// ===========================================================================
// 0x006a3070 -- GetPropertyIDs
// ===========================================================================

void test_006a3070_count_is_the_signed_span_quotient() {
  FakeList list;
  FakeEntries entries;
  OpaqueWordVector destination{};
  std::array<TargetWord, 8> words{};
  list.poison();
  entries.bytes.fill(kCanary);
  words.fill(0xccccccccu);
  arm_span(list, entries, 3);
  arm_vector(destination, words.data());
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_get_property_ids_006a3070(list.as_list(), &destination);

  check(resize_calls.size() == 1u, "006a3070: one resize call");
  check(resize_calls[0].vector == &destination,
        "006a3070: ECX is the destination vector");
  check_word(resize_calls[0].count, 3u,
             "006a3070: the quotient is the span in bytes over 24, not over 4 "
             "and not over 28");
  check_word(words[0], kCanaryWord,
             "006a3070: the port is inert here, so nothing is stored");
}

void test_006a3070_forwards_a_negative_quotient_unclamped() {
  // The magic-number sequence truncates toward zero and the result is pushed as
  // it stands: a last cursor before the first yields -1, which reaches the port
  // as 0xffffffff. A body that clamped, or that divided unsigned, hands over
  // something else. The port then empties the receiver's span, which the body
  // re-reads after the call -- and which is also what keeps a reversed span's
  // copy loop (which on the machine never terminates) from being entered.
  FakeList list;
  FakeEntries entries;
  OpaqueWordVector destination{};
  std::array<TargetWord, 8> words{};
  list.poison();
  entries.bytes.fill(kCanary);
  words.fill(0xccccccccu);
  list.put_word(kSpanFirstDisplacement,
                static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(
                    entries.raw() + kEntryStride)));
  list.put_word(kSpanLastDisplacement,
                static_cast<TargetWord>(
                    reinterpret_cast<std::uintptr_t>(entries.raw())));
  arm_vector(destination, words.data());
  reset_counters();
  PropertySafePorts ports = observed_ports();
  ports.resize_words = collapsing_resize_hook;
  property_safe_set_ports(ports);
  collapsing_target = list.as_list();

  property_list_get_property_ids_006a3070(list.as_list(), &destination);

  check(resize_calls.size() == 1u, "006a3070: the port is still called");
  check_word(resize_calls[0].count, 0xffffffffu,
             "006a3070: a reversed span reaches the port as -1, unclamped");
  check(events.size() == 1u,
        "006a3070: the span is re-read after the port returns, so the port's "
        "rewrite of it ends the copy loop");
  check_word(words[0], 0xccccccccu, "006a3070: no word is stored");
}

void test_006a3070_span_is_re_read_after_the_resize() {
  // MOV EAX,[ESI + 0x18] / CMP EAX,[ESI + 0x1c] sit *after* CALL 0x004cd3c0, so
  // the copy loop runs on cursors read after the port returns. A body that kept
  // the cursors it read for the count would ignore the port's rewrite and walk
  // a span the port had already emptied.
  FakeList list;
  FakeEntries entries;
  OpaqueWordVector destination{};
  std::array<TargetWord, 8> words{};
  list.poison();
  entries.bytes.fill(kCanary);
  words.fill(0xccccccccu);
  arm_span(list, entries, 2);
  entries.put_key(0, 0x51u);
  entries.put_key(1, 0x52u);
  arm_vector(destination, words.data());
  reset_counters();
  PropertySafePorts ports = observed_ports();
  ports.resize_words = collapsing_resize_hook;
  property_safe_set_ports(ports);
  collapsing_target = list.as_list();

  property_list_get_property_ids_006a3070(list.as_list(), &destination);

  check_word(resize_calls[0].count, 2u,
             "006a3070: the port is asked for the count the first read gives");
  check_word(words[0], 0xccccccccu,
             "006a3070: the span is re-read after the port returns, so the port's "
             "rewrite of it ends the copy loop");
  check_word(words[1], 0xccccccccu, "006a3070: nothing is stored");
}

void test_006a3070_empty_span_resizes_to_zero_and_stores_nothing() {
  FakeList list;
  FakeEntries entries;
  OpaqueWordVector destination{};
  std::array<TargetWord, 8> words{};
  words.fill(0xccccccccu);
  list.poison();
  entries.bytes.fill(kCanary);
  arm_span(list, entries, 0);
  arm_vector(destination, words.data());
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_get_property_ids_006a3070(list.as_list(), &destination);

  check_word(resize_calls[0].count, 0u,
             "006a3070: an empty span asks the port for zero words");
  check(events.size() == 1u,
        "006a3070: the copy loop is skipped when the two cursors are equal");
  check_word(words[0], 0xccccccccu, "006a3070: no word is stored");
}

void test_006a3070_stores_each_entry_key_after_the_resize() {
  // The hook re-points the vector's first word at a second buffer, which is only
  // observable if the body reads that word *after* the port call -- the order
  // the listing shows (CALL 0x004cd3c0, then MOV EDX,dword ptr [EDI]).
  FakeList list;
  FakeEntries entries;
  OpaqueWordVector destination{};
  std::array<TargetWord, 8> before{};
  std::array<TargetWord, 8> after{};
  list.poison();
  entries.bytes.fill(kCanary);
  before.fill(0xccccccccu);
  after.fill(0xccccccccu);
  arm_span(list, entries, 3);
  for (std::size_t index = 0; index < 3; ++index) {
    entries.put_key(index, 4u + static_cast<TargetWord>(index) * 4u);
  }
  arm_vector(destination, before.data());
  reset_counters();
  PropertySafePorts ports = observed_ports();
  ports.resize_words = replacing_resize_hook;
  property_safe_set_ports(ports);
  resize_target = &after;

  property_list_get_property_ids_006a3070(list.as_list(), &destination);

  resize_target = nullptr;
  bool untouched = true;
  for (std::size_t index = 0; index < before.size(); ++index) {
    if (before[index] != 0xccccccccu) {
      untouched = false;
    }
  }
  check(untouched,
        "006a3070: nothing is written into the buffer the vector held before "
        "the resize, so the base word is read after the port returns");
  check_word(after[0], 4u, "006a3070: the first key is stored at word 0");
  check_word(after[1], 8u, "006a3070: the second key is stored at word 1");
  check_word(after[2], 12u, "006a3070: the third key is stored at word 2");
  check_word(after[3], 0xccccccccu,
             "006a3070: the destination cursor advances one word per entry, so "
             "word 3 is untouched");
  check_word(resize_calls[0].count, 3u, "006a3070: the port was asked for 3");
}

void test_006a3070_loop_bound_is_the_receiver_span() {
  // The destination's second word says one word is live; the receiver's span
  // says three. The listing's loop compares against [ESI + 0x1c] and nothing
  // else, so all three keys are stored. A body that respected the destination's
  // end word would stop after one, and a body that trusted the resize port's
  // count instead of the span would too.
  FakeList list;
  FakeEntries entries;
  OpaqueWordVector destination{};
  std::array<TargetWord, 8> words{};
  list.poison();
  entries.bytes.fill(kCanary);
  words.fill(0xccccccccu);
  arm_span(list, entries, 3);
  for (std::size_t index = 0; index < 3; ++index) {
    entries.put_key(index, 0x2000u + static_cast<TargetWord>(index));
  }
  arm_vector(destination, words.data());
  arm_vector_end(destination, 1u);
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_get_property_ids_006a3070(list.as_list(), &destination);

  check_word(words[0], 0x2000u, "006a3070: the first key is stored");
  check_word(words[1], 0x2001u,
             "006a3070: the loop bound is the receiver's span, so the second "
             "key is stored past the destination's end word");
  check_word(words[2], 0x2002u, "006a3070: the third key is stored too");
  check_word(words[3], 0xccccccccu, "006a3070: the fourth word is never touched");
}

void test_006a3070_span_displacements_are_exact() {
  // A decoy cursor planted one word below and one word above the real pair. If
  // the body read either, the count and the stored keys would change.
  FakeList list;
  FakeEntries entries;
  OpaqueWordVector destination{};
  std::array<TargetWord, 8> words{};
  list.poison();
  entries.bytes.fill(kCanary);
  words.fill(0xccccccccu);
  arm_span(list, entries, 2);
  for (std::size_t index = 0; index < 2; ++index) {
    entries.put_key(index, 0x30u + static_cast<TargetWord>(index));
  }
  list.put_word(kSpanFirstDisplacement - 4u,
                static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(
                    entries.raw() + 4u)));
  list.put_word(kSpanLastDisplacement + 4u,
                static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(
                    entries.raw() + 6u * kEntryStride)));
  arm_vector(destination, words.data());
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_get_property_ids_006a3070(list.as_list(), &destination);

  check_word(resize_calls[0].count, 2u,
             "006a3070: the count comes from the +0x18/+0x1c pair, not from "
             "the decoy pair one word out on each side");
  check_word(words[0], 0x30u, "006a3070: the first stored word is the entry key");
  check_word(words[1], 0x31u,
             "006a3070: the second stored word is the next entry's key");
  check_word(words[2], 0xccccccccu, "006a3070: no third word is stored");
}

void test_006a3070_writes_no_receiver_byte() {
  FakeList list;
  FakeEntries entries;
  OpaqueWordVector destination{};
  std::array<TargetWord, 8> words{};
  list.poison();
  entries.bytes.fill(kCanary);
  words.fill(0xccccccccu);
  arm_span(list, entries, 2);
  entries.put_key(0, 1u);
  entries.put_key(1, 2u);
  arm_vector(destination, words.data());
  const std::array<std::uint8_t, kReceiverBytes> before = list.bytes;
  reset_counters();
  property_safe_set_ports(observed_ports());

  property_list_get_property_ids_006a3070(list.as_list(), &destination);

  bool clean = true;
  for (std::size_t offset = 0; offset < kReceiverBytes; ++offset) {
    if (list.bytes[offset] != before[offset]) {
      clean = false;
    }
  }
  check(clean, "006a3070: this body reads the receiver's span words and writes "
               "none of them");
  check_word(words[0], 1u, "006a3070: the keys are still stored");
  check_word(words[1], 2u, "006a3070: both keys are stored");
}

// ===========================================================================
// the port defaults, and the four bodies together
// ===========================================================================

void test_default_map_copy_port_is_a_bounded_model() {
  property_safe_reset_ports();
  reset_counters();
  FakeList list;
  FakeList other;
  FakeEntries source_entries;
  FakeEntries destination_entries;
  list.poison();
  other.poison();
  source_entries.bytes.fill(0x11u);
  destination_entries.bytes.fill(kCanary);
  // The region is rooted at +0x18, so the region's own two cursor words are the
  // receiver's +0x18 and +0x1c -- which is how the default bounds its copy.
  arm_span(other, source_entries, 3);
  arm_span(list, destination_entries, 2);
  store_word(source_entries.raw(), 0xa1a1a1a1u);
  reset_counters();

  property_list_copy_from_006a2a40(list.as_list(), other.as_list());

  check_word(load_word(destination_entries.raw()), 0xa1a1a1a1u,
             "the map-copy default copies the source's span bytes into the "
             "destination's own buffer");
  check_word(load_word(destination_entries.raw() + kEntryStride), 0x11111111u,
             "the map-copy default copies every entry of the source span");
  check_word(load_word(destination_entries.raw() + 2u * kEntryStride),
             kCanaryWord,
             "the map-copy default stops at the destination's own bound, so the "
             "third entry is not copied");
}

void test_default_resize_port_never_allocates_and_moves_the_end_word() {
  property_safe_reset_ports();
  std::array<TargetWord, 4> storage{};
  OpaqueWordVector vector{};
  arm_vector(vector, storage.data());
  const std::uint8_t* const base = byte_view(&vector);
  property_safe_ports().resize_words(&vector, 3u);
  // The end word holds an address, so the check is on the distance from the
  // base, not on the raw word: comparing the word with a count would pass for
  // any base whose address happened to be small.
  check_word(load_word(base + sizeof(TargetWord)) -
                 static_cast<TargetWord>(
                     reinterpret_cast<std::uintptr_t>(storage.data())),
             static_cast<TargetWord>(3u * sizeof(TargetWord)),
             "the resize default moves the end word to base + count words");
  property_safe_ports().resize_words(&vector, 1u);
  check_word(load_word(base + sizeof(TargetWord)) -
                 static_cast<TargetWord>(
                     reinterpret_cast<std::uintptr_t>(storage.data())),
             static_cast<TargetWord>(sizeof(TargetWord)),
             "the resize default accepts a shrink and keeps the same base");
  check_word(storage[0], 0u, "the resize default writes no element");
  check_word(load_word(base), static_cast<TargetWord>(
                                   reinterpret_cast<std::uintptr_t>(
                                       storage.data())),
             "the resize default does not move the base");
}

void test_default_set_parent_port_is_inert() {
  property_safe_reset_ports();
  FakeList list;
  list.poison();
  arm_parent(list, list.as_list());
  property_safe_ports().set_parent(
      list.as_list(), list_at(list.word(kCopyFromParentDisplacement)));
  check_word(list.word(kCopyFromParentDisplacement),
             static_cast<TargetWord>(
                 reinterpret_cast<std::uintptr_t>(list.as_list())),
             "the SetParent default is inert, because its side effects are "
             "unresolved in this package's evidence");
  check(set_parent_calls == 0u,
        "the default does not route through the test hook");
}

void test_default_base_lookup_follows_006a1de0() {
  // The default base port is a transcription of 0x006a1de0's own listing, so
  // these checks are about that transcription: a lower-bound walk over the
  // span, entry+0x04 on a hit, the +0x30 word as the parent, and the parent's
  // +0x20 slot on a miss.
  property_safe_reset_ports();
  FakeList list;
  FakeEntries entries;
  FakeList parent;
  FakeTable parent_table;
  list.poison();
  entries.bytes.fill(kCanary);
  parent.poison();
  parent_table.poison();
  arm_span(list, entries, 3);
  // No parent yet: the canary a poisoned receiver carries at +0x30 is a non-null
  // pointer, and a miss would be deferred into it.
  list.put_word(kCopyFromParentDisplacement, 0u);
  for (std::size_t index = 0; index < 3; ++index) {
    entries.put_key(index, 2u + static_cast<TargetWord>(index) * 2u);
    entries.put_second(index, 0x40000000u + static_cast<TargetWord>(index));
  }
  reset_counters();

  OpaqueProperty* result = nullptr;
  bool found = property_safe_ports().get_property_alt_base(list.as_list(), 4u,
                                                           &result);
  check(found, "006a1e50's default base port finds a key in the span");
  check(result == reinterpret_cast<OpaqueProperty*>(entries.at(1) +
                                                   kEntrySecondWordDisplacement),
        "006a1e50's default base port hands back entry+0x04 on a hit");

  result = the_property();
  found =
      property_safe_ports().get_property_alt_base(list.as_list(), 5u, &result);
  check(!found, "006a1e50's default base port misses between two keys");
  check(result == the_property(),
        "006a1e50's default base port writes nothing through the out pointer on "
        "a miss");

  result = the_property();
  list.put_word(kCopyFromParentDisplacement, 0u);
  found =
      property_safe_ports().get_property_alt_base(list.as_list(), 9u, &result);
  check(!found, "006a1e50's default base port ends the chain on a null +0x30");

  // The parent's +0x20 slot: a neighbour slot carries a decoy so that a body
  // reading the wrong displacement of the parent's table would report it.
  parent_table.put_slot(0x20u, slot_address(defer_hook));
  parent_table.put_slot(0x1cu, slot_address(defer_hook));
  parent_table.put_slot(0x24u, slot_address(defer_hook));
  reset_counters();
  defer_answer = true;
  defer_value = the_property();
  arm_table(parent, parent_table);
  arm_parent(list, parent.as_list());
  found =
      property_safe_ports().get_property_alt_base(list.as_list(), 9u, &result);
  check(found && defer_calls == 1u && defer_id == 9u,
        "006a1e50's default base port defers to the parent's +0x20 slot on a "
        "miss with a non-null +0x30 word");
  check(defer_receiver == parent.as_list(),
        "006a1e50's default base port passes the parent, not the receiver");
  check(defer_result == &result,
        "006a1e50's default base port forwards the out pointer to the parent");
  check(result == the_property(),
        "the deferred slot's answer reaches the out pointer");
}

void test_four_bodies_together() {
  FakeList list;
  FakeList other;
  FakeList parent;
  FakeEntries entries;
  FakeTable table;
  OpaqueWordVector destination{};
  std::array<TargetWord, 8> words{};
  list.poison();
  other.poison();
  parent.poison();
  entries.bytes.fill(kCanary);
  table.poison();
  words.fill(0xccccccccu);
  arm_span(list, entries, 2);
  arm_span(other, entries, 2);
  arm_table(list, table);
  arm_table(other, table);
  table.put_slot(kSetSlotDisplacement, slot_address(set_hook));
  table.put_slot(kGetObjectSlotDisplacement, slot_address(fetch_hook));
  arm_limit(list, 2u);
  for (std::size_t index = 0; index < 2; ++index) {
    entries.put_key(index, 6u + static_cast<TargetWord>(index));
  }
  other.raw()[0x2c] = 0x12u;
  list.put_word(kAddFromCounterDisplacement, 0u);
  arm_parent(list, parent.as_list());
  arm_vector(destination, words.data());
  reset_counters();
  property_safe_set_ports(observed_ports());
  fetch_result = the_property();

  OpaqueProperty* result = nullptr;
  direct_property_list_add_properties_from_006a1600(list.as_list(),
                                                    other.as_list());
  direct_property_list_get_property_alt_006a1e50(list.as_list(), 1u, &result);
  direct_property_list_get_property_alt_006a1e50(list.as_list(), 40u, &result);
  property_list_copy_from_006a2a40(list.as_list(), other.as_list());
  property_list_get_property_ids_006a3070(list.as_list(), &destination);

  check(set_calls.size() == 2u, "006a1600 dispatched twice");
  check(fetch_calls == 1u, "006a1e50 dispatched the fast slot once");
  check(base_calls == 1u, "006a1e50 deferred once");
  check(map_copy_calls.size() == 1u, "006a2a40 delegated once");
  check(set_parent_calls == 1u, "006a2a40 called SetParent once");
  check(resize_calls.size() == 1u, "006a3070 resized once");
  check_word(list.word(kAddFromCounterDisplacement), 1u,
             "006a1600 counted its one call");
  check_word(words[0], 6u, "006a3070 stored the first key");
  check_word(words[1], 7u, "006a3070 stored the second key");
  check(list.raw()[0x2c] == 0x12u, "006a2a40 moved its one byte");
  check(result == the_property(),
        "006a1e50's base answer reached the out pointer");
  check_word(list.word(kGetAltLimitDisplacement), 2u,
             "006a1e50 read its limit and did not write it");
  check_word(list.word(kCopyFromParentDisplacement),
             static_cast<TargetWord>(
                 reinterpret_cast<std::uintptr_t>(parent.as_list())),
             "006a2a40 read its +0x30 word and did not write it");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_property_safe_wave9

int main() {
  using namespace openspore::reconstruction::pkg_property_safe_wave9;

  test_006a1600_self_copy_touches_nothing();
  test_006a1600_empty_span_still_increments();
  test_006a1600_one_call_per_entry_in_order();
  test_006a1600_stride_is_a_displacement_not_an_index();
  test_006a1600_slot_is_two_levels_deep_at_0x14();
  test_006a1600_counter_displacement_is_exact();
  test_006a1600_writes_no_other_receiver_word();

  test_006a1e50_limit_is_compared_unsigned();
  test_006a1e50_zero_limit_always_uses_the_base();
  test_006a1e50_fast_path_stores_the_pointee_it_was_given();
  test_006a1e50_slot_is_two_levels_deep_at_0x28();
  test_006a1e50_base_path_forwards_and_answers();
  test_006a1e50_base_miss_leaves_the_out_pointer_alone();
  test_006a1e50_limit_displacement_is_exact();

  test_006a2a40_self_copy_touches_nothing();
  test_006a2a40_delegates_to_both_ports_in_order();
  test_006a2a40_moves_one_byte_and_only_one();
  test_006a2a40_reads_the_parent_word_after_the_map_copy();
  test_006a2a40_parent_displacement_is_exact();
  test_006a2a40_writes_no_other_receiver_byte();

  test_006a3070_count_is_the_signed_span_quotient();
  test_006a3070_span_is_re_read_after_the_resize();
  test_006a3070_forwards_a_negative_quotient_unclamped();
  test_006a3070_empty_span_resizes_to_zero_and_stores_nothing();
  test_006a3070_stores_each_entry_key_after_the_resize();
  test_006a3070_loop_bound_is_the_receiver_span();
  test_006a3070_span_displacements_are_exact();
  test_006a3070_writes_no_receiver_byte();

  test_default_map_copy_port_is_a_bounded_model();
  test_default_resize_port_never_allocates_and_moves_the_end_word();
  test_default_set_parent_port_is_inert();
  test_default_base_lookup_follows_006a1de0();
  test_four_bodies_together();

  if (g_failures != 0) {
    std::printf("pkg_property_safe_wave9: %d of %zu checks FAILED\n", g_failures,
                g_checks);
    return 1;
  }
  std::printf("pkg_property_safe_wave9: all %zu checks passed\n", g_checks);
  return 0;
}

#undef PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL
