#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "sporepedia_wave10.hpp"

namespace openspore::reconstruction::pkg_sporepedia_wave10 {
namespace {

#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_WAVE10_TEST_THISCALL __thiscall
#else
#define PKG_SPOREPEDIA_WAVE10_TEST_THISCALL __attribute__((thiscall))
#endif

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

enum EventKind {
  kEventRetain = 1,
  kEventRelease = 2,
  kEventFree = 3,
  kEventBaseDestroy = 4,
  kEventLookup = 5,
  kEventTagKey = 6,
  kEventMaskTest = 7,
  kEventKeyCollect = 8,
  kEventReserve = 9,
  kEventInsert = 10,
  kEventRange = 11,
  kEventLookupGate = 12,
  kEventLookupEntry = 13,
  kEventApplyProperty = 14
};

struct Event {
  int kind;
  const void* pointer;
  OpaqueWord word;
  OpaqueWord second;
};

std::array<Event, 128> g_events{};
std::size_t g_event_count = 0;

void record(int kind, const void* pointer, OpaqueWord word, OpaqueWord second) {
  check(g_event_count < g_events.size());
  g_events[g_event_count] = Event{kind, pointer, word, second};
  ++g_event_count;
}

std::size_t count_events(int kind) {
  std::size_t total = 0;
  for (std::size_t scan = 0; scan < g_event_count; ++scan) {
    if (g_events[scan].kind == kind) {
      ++total;
    }
  }
  return total;
}

const Event& event_at(int kind, std::size_t occurrence) {
  std::size_t seen = 0;
  for (std::size_t scan = 0; scan < g_event_count; ++scan) {
    if (g_events[scan].kind != kind) {
      continue;
    }
    if (seen == occurrence) {
      return g_events[scan];
    }
    ++seen;
  }
  std::abort();
}

struct RefFixture {
  OpaqueAssetRefVtable vtable{};
  OpaqueAssetRef ref{};
};

struct Observation {
  const void* object;
  unsigned retains;
  unsigned releases;
};

std::array<Observation, 8> g_observations{};
std::size_t g_observation_count = 0;

Observation* observe(const void* object) {
  for (std::size_t index = 0; index < g_observation_count; ++index) {
    if (g_observations[index].object == object) {
      return &g_observations[index];
    }
  }
  check(g_observation_count < g_observations.size());
  g_observations[g_observation_count] = Observation{object, 0u, 0u};
  return &g_observations[g_observation_count++];
}

unsigned retains_of(const void* object) {
  const Observation* const entry = observe(object);
  return entry->retains;
}

unsigned releases_of(const void* object) {
  const Observation* const entry = observe(object);
  return entry->releases;
}

void PKG_SPOREPEDIA_WAVE10_TEST_THISCALL retain_hook(OpaqueAssetRef* ref) {
  record(kEventRetain, ref, 0u, 0u);
  ++observe(ref)->retains;
}

void PKG_SPOREPEDIA_WAVE10_TEST_THISCALL release_hook(OpaqueAssetRef* ref) {
  record(kEventRelease, ref, 0u, 0u);
  ++observe(ref)->releases;
}

struct PortScript {
  OpaqueWord key_pattern[4] = {0x11111111u, 0x22222222u, 0x33333333u,
                               0x44444444u};
  bool fill_key = true;
  OpaqueKey16 mask_left[8] = {};
  OpaqueKey16 mask_right[8] = {};
  std::size_t mask_calls = 0;
  std::uint8_t mask_results[3] = {0u, 0u, 0u};
  OpaqueWordVector collected{};
  bool collect_result = false;
  bool collect_writes = true;
  OpaqueWord reserve_count = 0xffffffffu;
  unsigned reserve_calls = 0;
  std::size_t entry_calls = 0;
  std::size_t gate_calls = 0;
  const OpaqueLookupEntry* entry_results[8] = {};
  bool prologue_verified = false;
};

RefFixture g_author;
RefFixture g_slot_ref;
RefFixture g_first;
RefFixture g_second;
RefFixture g_third;
PortScript g_script;
OpaqueKeyedSet g_keyed_set{};
OpaqueAssetRefVtable g_keyed_vtable{};
OpaqueLookupSource g_source{};
OpaqueLookupSourceVtable g_source_vtable{};
OpaqueAssetVtable g_asset_vtable{};
OpaqueSporepediaAsset g_asset{};
bool g_author_enabled = false;
bool g_keyed_enabled = false;
OpaqueLookup* g_lookup = nullptr;
bool g_gate_enabled = false;
OpaqueGlobalRecordRange g_range{0u, 0u};
OpaqueGlobalRecord g_range_records[4] = {};
OpaqueWord g_range_storage[12] = {};
OpaqueLookupEntry g_entries[4] = {};

OpaqueWord to_word(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

OpaqueWord* inline_storage() { return g_asset.inline_58.data(); }

OpaqueWord* sentinel_storage() {
  static OpaqueWord storage[2] = {0u, 0u};
  return storage;
}

OpaqueAssetRef* PKG_SPOREPEDIA_WAVE10_TEST_THISCALL
lookup_hook(OpaqueLookupSource* source, OpaqueWord id) {
  record(kEventLookup, source, id, 0u);
  check(source == &g_source);
  if (id == 0x0670da17u) {
    return g_author_enabled ? &g_author.ref : nullptr;
  }
  if (id == 0x03c609f8u) {
    return g_keyed_enabled ? reinterpret_cast<OpaqueAssetRef*>(&g_keyed_set)
                           : nullptr;
  }
  return nullptr;
}

void PKG_SPOREPEDIA_WAVE10_TEST_THISCALL apply_property_hook(
    OpaqueSporepediaAsset* asset, const OpaqueGlobalRecord* entry) {
  record(kEventApplyProperty, entry, 0u, 0u);
  check(asset == &g_asset);
}

OpaqueKey16* PKG_SPOREPEDIA_WAVE10_TEST_THISCALL
key_fill_hook(OpaqueKeyedSet* tags, OpaqueKey16* out, OpaqueWord one) {
  record(kEventTagKey, out, one, 0u);
  check(tags == &g_keyed_set);
  if (g_script.fill_key) {
    for (std::size_t index = 0; index < out->words.size(); ++index) {
      out->words[index] = g_script.key_pattern[index];
    }
  }
  return out;
}

std::uint8_t mask_test_hook(OpaqueKey16 left, OpaqueKey16 right) {
  check(g_script.mask_calls < 8u);
  g_script.mask_left[g_script.mask_calls] = left;
  g_script.mask_right[g_script.mask_calls] = right;
  record(kEventMaskTest, nullptr, static_cast<OpaqueWord>(g_script.mask_calls),
         0u);
  return g_script.mask_results[g_script.mask_calls++];
}

bool key_collect_hook(OpaqueKeyedSet* tags, OpaqueWordVector* out) {
  record(kEventKeyCollect, out, g_script.collect_result ? 1u : 0u, 0u);
  check(tags == &g_keyed_set);
  if (g_script.collect_writes) {
    *out = g_script.collected;
  }
  return g_script.collect_result;
}

void PKG_SPOREPEDIA_WAVE10_TEST_THISCALL
reserve_hook(OpaqueInlineWordVector* vector, OpaqueWord count) {
  record(kEventReserve, vector, count, 0u);
  check(vector == &g_asset.entries_40);
  ++g_script.reserve_calls;
  g_script.reserve_count = count;
}

void PKG_SPOREPEDIA_WAVE10_TEST_THISCALL
insert_hook(OpaqueInlineWordVector* vector, OpaqueWord* position,
            const OpaqueWord* value) {
  record(kEventInsert, vector, to_word(position), *value);
  check(vector == &g_asset.entries_40);
  check(position == vector->last);
  *position = *value;
  vector->last += 1;
}

const OpaqueGlobalRecordRange* range_hook() {
  record(kEventRange, &g_range, g_asset.word_2c,
         g_asset.entries_40.last == g_asset.entries_40.first ? 1u : 0u);
  return &g_range;
}

OpaqueLookup* gate_lookup_hook() {
  record(kEventLookupGate, g_lookup, 0u, 0u);
  ++g_script.gate_calls;
  return g_gate_enabled ? g_lookup : nullptr;
}

const OpaqueLookupEntry* PKG_SPOREPEDIA_WAVE10_TEST_THISCALL
entry_lookup_hook(OpaqueLookup* lookup, OpaqueWord element) {
  record(kEventLookupEntry, lookup, element, 0u);
  check(lookup == g_lookup);
  check(g_script.entry_calls < 8u);
  return g_script.entry_results[g_script.entry_calls++];
}

void free_hook(OpaqueWord address) {
  record(kEventFree,
         reinterpret_cast<const void*>(static_cast<std::uintptr_t>(address)),
         address, 0u);
}

void PKG_SPOREPEDIA_WAVE10_TEST_THISCALL
base_destroy_hook(OpaqueSporepediaAsset* asset) {
  record(kEventBaseDestroy, asset, 0u, 0u);
}

void install_ports() {
  SporepediaRuntime& runtime = sporepedia_runtime();
  runtime.free_00f47380 = free_hook;
  runtime.base_destroy_006412a0 = base_destroy_hook;
  runtime.key_fill_004babe0 = key_fill_hook;
  runtime.mask_test_004f3d60 = mask_test_hook;
  runtime.key_collect_004f5720 = key_collect_hook;
  runtime.word_vector_reserve_00642070 = reserve_hook;
  runtime.word_vector_insert_0060a600 = insert_hook;
  runtime.global_record_range_005507a0 = range_hook;
  runtime.gate_lookup_0067dea0 = gate_lookup_hook;
  runtime.entry_lookup_007db5e0 = entry_lookup_hook;
}

void arm_ref(RefFixture& fixture) {
  fixture.vtable.retain_00 = retain_hook;
  fixture.vtable.release_04 = release_hook;
  fixture.ref.vtable = &fixture.vtable;
}

void arm_source(bool author, bool keyed) {
  g_author_enabled = author;
  g_keyed_enabled = keyed;
  arm_ref(g_author);
  g_keyed_set = OpaqueKeyedSet{};
  g_keyed_vtable.retain_00 = retain_hook;
  g_keyed_vtable.release_04 = release_hook;
  g_keyed_set.vtable = &g_keyed_vtable;
  g_keyed_set.word_18 = 0x1234abcdu;
  if (author) {
    *observe(&g_author.ref) = Observation{&g_author.ref, 0u, 0u};
  }
  if (keyed) {
    *observe(&g_keyed_set) = Observation{&g_keyed_set, 0u, 0u};
  }
}

void reset_fixture() {
  std::memset(&g_asset, 0x5a, sizeof(g_asset));
  g_asset.vtable = &g_asset_vtable;
  g_asset.entries_40.first = inline_storage();
  g_asset.entries_40.last = inline_storage();
  g_asset.entries_40.end_of_storage =
      inline_storage() + g_asset.inline_58.size();
  g_asset.entries_40.inline_first = to_word(inline_storage());
  g_asset.secondary_10 = 0x11111111u;
  g_asset.secondary_14 = 0x22222222u;
  g_asset.access_1c = nullptr;
  g_asset.access_20 = nullptr;
  g_asset.access_3c = nullptr;
  g_asset.access_70 = nullptr;
  g_asset.access_74 = nullptr;
  g_asset.flag_24 = 0x11u;
  g_asset.flag_25 = 0x22u;
  g_asset.flag_26 = 0x33u;
  g_asset.opaque_27 = 0x44u;
  g_asset.word_28 = 0x55555555u;
  g_asset.word_2c = 0x66666666u;
  g_asset.max_6c = 0x77777777u;

  g_source.vtable = &g_source_vtable;
  g_source_vtable.lookup_0c = lookup_hook;

  g_first = RefFixture{};
  g_second = RefFixture{};
  g_third = RefFixture{};
  arm_ref(g_author);
  arm_ref(g_slot_ref);
  g_author_enabled = false;
  g_keyed_enabled = false;
  g_keyed_set = OpaqueKeyedSet{};
  g_keyed_vtable = OpaqueAssetRefVtable{};
  g_observations = std::array<Observation, 8>{};
  g_observation_count = 0;

  g_lookup = reinterpret_cast<OpaqueLookup*>(&g_entries[0]);
  g_gate_enabled = false;
  g_range = OpaqueGlobalRecordRange{0u, 0u};
  std::memset(g_range_records, 0, sizeof(g_range_records));
  std::memset(g_range_storage, 0, sizeof(g_range_storage));
  std::memset(g_entries, 0, sizeof(g_entries));
  g_key_015da8e0.words = {{0x0a0a0a0au, 0x0b0b0b0bu, 0x0c0c0c0cu, 0x0d0d0d0du}};
  g_key_015dab18.words = {{0x1a1a1a1au, 0x1b1b1b1bu, 0x1c1c1c1cu, 0x1d1d1d1du}};
  g_key_015da80c.words = {{0x2a2a2a2au, 0x2b2b2b2bu, 0x2c2c2c2cu, 0x2d2d2d2du}};
  g_event_count = 0;
  g_script = PortScript{};
}

void arm_range(std::size_t records) {
  for (std::size_t index = 0; index < records; ++index) {
    g_range_records[index].words = {{index + 1u, index + 11u, index + 21u}};
  }
  std::memcpy(g_range_storage, g_range_records, sizeof(g_range_records));
  g_range.first = to_word(g_range_storage);
  g_range.last = to_word(g_range_storage + records * 3u);
}

void arm_inline_key_set(std::size_t count) {
  for (std::size_t index = 0; index < count; ++index) {
    g_asset.inline_58[index] = 0xa000u + static_cast<OpaqueWord>(index);
  }
  g_script.collected.first = inline_storage();
  g_script.collected.last = inline_storage() + count;
  g_script.collected.end_of_storage =
      inline_storage() + g_asset.inline_58.size();
  g_script.collect_result = true;
}

std::array<std::uint8_t, 0x78> snapshot_asset() {
  std::array<std::uint8_t, 0x78> bytes{};
  std::memcpy(bytes.data(), &g_asset, bytes.size());
  return bytes;
}

void test_destroy_releases_in_reverse_order() {
  reset_fixture();
  arm_ref(g_first);
  arm_ref(g_second);
  arm_ref(g_third);
  g_asset.access_1c = &g_author.ref;
  g_asset.access_20 = &g_second.ref;
  g_asset.access_3c = &g_third.ref;
  g_asset.access_70 = &g_first.ref;
  arm_ref(g_slot_ref);
  g_asset.access_74 = &g_slot_ref.ref;

  sporepedia_asset_destroy_00642190(&g_asset);

  check(to_word(g_asset.vtable) == 0x013ff648u);
  check(g_asset.secondary_10 == 0x01462748u);
  check(g_asset.secondary_14 == 0x01462738u);
  check(count_events(kEventFree) == 0u);
  check(g_event_count == 6u);
  check(g_events[0].kind == kEventRelease);
  check(g_events[0].pointer == &g_slot_ref.ref);
  check(g_events[1].kind == kEventRelease);
  check(g_events[1].pointer == &g_first.ref);
  check(g_events[2].kind == kEventRelease);
  check(g_events[2].pointer == &g_third.ref);
  check(g_events[3].kind == kEventRelease);
  check(g_events[3].pointer == &g_second.ref);
  check(g_events[4].kind == kEventRelease);
  check(g_events[4].pointer == &g_author.ref);
  check(g_events[5].kind == kEventBaseDestroy);
  check(g_events[5].pointer == &g_asset);
  check(releases_of(&g_slot_ref.ref) == 1u);
  check(releases_of(&g_first.ref) == 1u);
  check(releases_of(&g_third.ref) == 1u);
  check(releases_of(&g_second.ref) == 1u);
  check(releases_of(&g_author.ref) == 1u);
  check(retains_of(&g_slot_ref.ref) == 0u);
}

void test_destroy_frees_heap_entries() {
  reset_fixture();
  std::array<OpaqueWord, 4> heap{};
  g_asset.entries_40.first = heap.data();
  g_asset.entries_40.last = heap.data() + 2;
  g_asset.entries_40.end_of_storage = heap.data() + heap.size();
  g_asset.entries_40.inline_first = 0x00c00000u;
  sporepedia_asset_destroy_00642190(&g_asset);
  check(count_events(kEventFree) == 1u);
  check(g_events[0].kind == kEventFree);
  check(g_events[0].word == to_word(heap.data()));
  check(g_asset.entries_40.first == heap.data());
  check(g_asset.entries_40.last == heap.data() + 2);
  check(g_asset.entries_40.inline_first == 0x00c00000u);
  check(g_event_count == 2u);
  check(g_events[1].kind == kEventBaseDestroy);
}

void test_destroy_null_entry_pointer_skips_free() {
  reset_fixture();
  g_asset.entries_40.first = nullptr;
  g_asset.entries_40.last = sentinel_storage() + 1;
  g_asset.entries_40.inline_first = 0x00c00000u;
  sporepedia_asset_destroy_00642190(&g_asset);
  check(count_events(kEventFree) == 0u);
  check(count_events(kEventRelease) == 0u);
  check(count_events(kEventBaseDestroy) == 1u);
  check(to_word(g_asset.vtable) == 0x013ff648u);
}

void test_destroy_preserves_other_words() {
  reset_fixture();
  arm_ref(g_author);
  arm_ref(g_slot_ref);
  g_asset.access_1c = &g_author.ref;
  g_asset.access_20 = &g_slot_ref.ref;
  g_asset.access_3c = &g_slot_ref.ref;
  g_asset.access_70 = &g_slot_ref.ref;
  g_asset.access_74 = &g_slot_ref.ref;
  const std::array<std::uint8_t, 0x78> before = snapshot_asset();
  sporepedia_asset_destroy_00642190(&g_asset);
  const std::array<std::uint8_t, 0x78> after = snapshot_asset();
  check(std::memcmp(after.data(), before.data(), 0x04) != 0);
  check(std::memcmp(before.data() + 0x04, after.data() + 0x04, 0x0c) == 0);
  check(std::memcmp(before.data() + 0x18, after.data() + 0x18, 0x60) == 0);
  check(before[0x10] == 0x11u && before[0x11] == 0x11u);
  check(before[0x14] == 0x22u && before[0x15] == 0x22u);
  check(g_asset.secondary_10 == 0x01462748u);
  check(g_asset.secondary_14 == 0x01462738u);
  check(static_cast<const void*>(g_asset.vtable) !=
        static_cast<const void*>(before.data()));
  check(g_asset.access_1c == &g_author.ref);
  check(g_asset.access_74 == &g_slot_ref.ref);
  check(g_asset.entries_40.first == inline_storage());
}

void test_destroy_null_receivers_only_tail() {
  reset_fixture();
  g_asset.access_1c = nullptr;
  g_asset.access_20 = nullptr;
  g_asset.access_3c = nullptr;
  g_asset.access_70 = nullptr;
  g_asset.access_74 = nullptr;
  sporepedia_asset_destroy_00642190(&g_asset);
  check(g_event_count == 1u);
  check(g_events[0].kind == kEventBaseDestroy);
  check(g_events[0].pointer == &g_asset);
  check(to_word(g_asset.vtable) == 0x013ff648u);
  check(g_asset.secondary_10 == 0x01462748u);
  check(g_asset.secondary_14 == 0x01462738u);
  check(g_asset.word_2c == 0x66666666u);
  check(g_asset.max_6c == 0x77777777u);
}

void test_load_null_source() {
  reset_fixture();
  g_asset.entries_40.last = inline_storage() + 3;
  g_asset.max_6c = 0xdeadbeefu;
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(g_asset.word_2c == 2u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
  check(g_asset.max_6c == 0u);
  check(g_asset.word_28 == 0x55555555u);
  check(g_asset.flag_24 == 0x11u);
  check(g_asset.flag_25 == 0x22u);
  check(g_asset.flag_26 == 0x33u);
  check(count_events(kEventLookup) == 0u);
  check(count_events(kEventRetain) == 0u);
  check(count_events(kEventRelease) == 0u);
  check(count_events(kEventFree) == 0u);
  check(count_events(kEventRange) == 0u);
  check(count_events(kEventTagKey) == 0u);
  check(g_script.gate_calls == 1u);
}

void test_load_source_without_refs() {
  reset_fixture();
  arm_source(false, false);
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventLookup) == 2u);
  check(event_at(kEventLookup, 0).word == 0x0670da17u);
  check(event_at(kEventLookup, 1).word == 0x03c609f8u);
  check(event_at(kEventLookup, 0).pointer == &g_source);
  check(event_at(kEventLookup, 1).pointer == &g_source);
  check(count_events(kEventRetain) == 0u);
  check(count_events(kEventRelease) == 0u);
  check(count_events(kEventRange) == 0u);
  check(count_events(kEventTagKey) == 0u);
  check(g_script.gate_calls == 1u);
  check(g_asset.word_2c == 2u);
  check(g_asset.max_6c == 0u);
  check(g_asset.word_28 == 0x55555555u);
}

void test_load_primary_ref_walks_global_range() {
  reset_fixture();
  arm_source(true, false);
  arm_range(3u);
  g_asset.entries_40.last = inline_storage() + 2;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventRange) == 1u);
  check(event_at(kEventRange, 0).word == 2u);
  check(event_at(kEventRange, 0).second == 1u);
  check(count_events(kEventApplyProperty) == 3u);
  for (std::size_t index = 0; index < 3u; ++index) {
    const auto* const seen = static_cast<const OpaqueGlobalRecord*>(
        event_at(kEventApplyProperty, index).pointer);
    check(seen == reinterpret_cast<const OpaqueGlobalRecord*>(g_range_storage +
                                                              index * 3u));
    check(seen->words[0] == index + 1u);
    check(seen->words[1] == index + 11u);
    check(seen->words[2] == index + 21u);
  }
  check(count_events(kEventTagKey) == 0u);
  check(count_events(kEventKeyCollect) == 0u);
  check(g_script.reserve_calls == 0u);
  check(g_asset.word_28 == 0x55555555u);
  check(g_asset.flag_24 == 0x11u);
  check(g_asset.flag_25 == 0x22u);
  check(g_script.reserve_count == 0xffffffffu);
  check(retains_of(&g_author.ref) == 1u);
  check(retains_of(&g_keyed_set) == 0u);
  check(count_events(kEventRelease) == 1u);
  check(g_events[g_event_count - 1u].pointer == &g_author.ref);
  check(g_asset.max_6c == 0u);
  check(g_asset.word_2c == 2u);
}

void test_load_both_refs_walk_range_only() {
  reset_fixture();
  arm_source(true, true);
  arm_range(1u);
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventApplyProperty) == 1u);
  check(count_events(kEventTagKey) == 0u);
  check(count_events(kEventKeyCollect) == 0u);
  check(retains_of(&g_author.ref) == 1u);
  check(retains_of(&g_keyed_set) == 1u);
  check(count_events(kEventRelease) == 2u);
  check(g_events[g_event_count - 2u].pointer == &g_keyed_set);
  check(g_events[g_event_count - 1u].pointer == &g_author.ref);
  check(g_asset.word_28 == 0x55555555u);
  check(g_asset.flag_24 == 0x11u);
  check(g_asset.word_2c == 2u);
  check(g_asset.max_6c == 0u);
}

void test_load_empty_range_walks_nothing() {
  reset_fixture();
  arm_source(true, false);
  arm_range(0u);
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventRange) == 1u);
  check(count_events(kEventApplyProperty) == 0u);
  check(count_events(kEventRelease) == 1u);
  check(releases_of(&g_author.ref) == 1u);
}

void test_load_secondary_ref_extracts_key() {
  reset_fixture();
  arm_source(false, true);
  arm_inline_key_set(3u);
  g_script.mask_results[0] = 0x02u;
  g_script.mask_results[1] = 0x04u;
  g_script.mask_results[2] = 0x08u;
  g_asset.opaque_54 = 0u;
  g_asset.entries_40.last = inline_storage() + 1;
  sporepedia_asset_load_00642230(&g_asset, &g_source);

  check(g_asset.word_28 == 0x1234abcdu);
  check(count_events(kEventTagKey) == 1u);
  check(event_at(kEventTagKey, 0).word == 1u);
  check(event_at(kEventTagKey, 0).pointer != nullptr);
  check(g_script.mask_calls == 3u);
  check(g_asset.flag_25 == 0x02u);
  check(g_asset.flag_24 == 0x04u);
  check(g_asset.flag_26 == 0x08u);
  check(g_asset.opaque_27 == 0x44u);
  check(count_events(kEventKeyCollect) == 1u);
  check(g_script.reserve_calls == 1u);
  check(g_script.reserve_count == 3u);
  check(g_asset.entries_40.last == g_asset.entries_40.first + 3u);
  for (std::size_t index = 0; index < 3u; ++index) {
    check(g_asset.entries_40.first[index] == 0xa000u + index);
  }
  check(count_events(kEventInsert) == 0u);
  check(count_events(kEventFree) == 0u);
  check(count_events(kEventRange) == 0u);
  check(count_events(kEventApplyProperty) == 0u);
  check(retains_of(&g_keyed_set) == 1u);
  check(count_events(kEventRelease) == 1u);
  check(g_events[g_event_count - 1u].pointer == &g_keyed_set);
  check(g_asset.max_6c == 0u);
}

void test_load_secondary_ref_key_order() {
  reset_fixture();
  arm_source(false, true);
  arm_inline_key_set(0u);
  g_script.fill_key = false;
  g_script.mask_results[0] = 0xf0u;
  g_script.mask_results[1] = 0x0fu;
  g_script.mask_results[2] = 0xa5u;
  g_asset.opaque_54 = 1u;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.mask_calls == 3u);
  for (std::size_t call = 0; call < 3u; ++call) {
    for (std::size_t word = 0; word < 4u; ++word) {
      check(g_script.mask_left[call].words[word] == 0u);
    }
    const OpaqueKey16& expected = call == 0u   ? g_key_015da8e0
                                  : call == 1u ? g_key_015dab18
                                               : g_key_015da80c;
    for (std::size_t word = 0; word < 4u; ++word) {
      check(g_script.mask_right[call].words[word] == expected.words[word]);
    }
  }
  check(g_asset.flag_25 == 0xf0u);
  check(g_asset.flag_24 == 0x0fu);
  check(g_asset.flag_26 == 0xa5u);
  check(g_script.reserve_calls == 1u);
  check(g_script.reserve_count == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
  check(count_events(kEventFree) == 1u);
  check(g_asset.max_6c == 0u);
}

void test_load_secondary_ref_insert_slow_path() {
  reset_fixture();
  arm_source(false, true);
  arm_inline_key_set(4u);
  g_asset.entries_40.end_of_storage = g_asset.entries_40.first;
  g_asset.opaque_54 = 7u;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.reserve_count == 4u);
  check(count_events(kEventInsert) == 4u);
  for (std::size_t index = 0; index < 4u; ++index) {
    check(event_at(kEventInsert, index).pointer == &g_asset.entries_40);
    check(event_at(kEventInsert, index).word ==
          to_word(inline_storage() + index));
    check(event_at(kEventInsert, index).second ==
          0xa000u + static_cast<OpaqueWord>(index));
  }
  check(g_asset.entries_40.last == g_asset.entries_40.first + 4u);
  for (std::size_t index = 0; index < 4u; ++index) {
    check(g_asset.entries_40.first[index] == 0xa000u + index);
  }
  check(count_events(kEventFree) == 1u);
  check(event_at(kEventFree, 0).word == to_word(inline_storage()));
}

void test_load_secondary_ref_collect_rejected() {
  reset_fixture();
  arm_source(false, true);
  arm_inline_key_set(3u);
  g_script.collect_result = false;
  g_asset.opaque_54 = 9u;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.mask_calls == 3u);
  check(g_script.reserve_calls == 0u);
  check(g_script.reserve_count == 0xffffffffu);
  check(count_events(kEventInsert) == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
  check(count_events(kEventFree) == 1u);
  check(count_events(kEventRelease) == 1u);
  check(releases_of(&g_keyed_set) == 1u);
}

void test_load_secondary_ref_collect_keeps_destination() {
  reset_fixture();
  arm_source(false, true);
  arm_inline_key_set(2u);
  g_script.collect_writes = false;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.collect_result);
  check(g_script.reserve_calls == 1u);
  check(g_script.reserve_count == 0u);
  check(count_events(kEventInsert) == 0u);
  check(count_events(kEventFree) == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
  check(releases_of(&g_keyed_set) == 1u);
}

void test_load_maximum_reduction() {
  reset_fixture();
  arm_source(false, true);
  arm_inline_key_set(4u);
  g_gate_enabled = true;
  g_entries[0] = OpaqueLookupEntry{0u, 5u};
  g_entries[1] = OpaqueLookupEntry{0u, 0u};
  g_entries[2] = OpaqueLookupEntry{0u, 0xffffffffu};
  g_script.entry_results[0] = &g_entries[0];
  g_script.entry_results[1] = nullptr;
  g_script.entry_results[2] = &g_entries[1];
  g_script.entry_results[3] = &g_entries[2];
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.entry_calls == 4u);
  check(g_script.gate_calls == 5u);
  check(count_events(kEventLookupEntry) == 4u);
  check(event_at(kEventLookupEntry, 0).word == 0xa000u);
  check(event_at(kEventLookupEntry, 3).word == 0xa003u);
  check(event_at(kEventLookupEntry, 0).pointer == g_lookup);
  check(g_asset.max_6c == 0xffffffffu);
  check(g_asset.entries_40.last == g_asset.entries_40.first + 4u);
}

void test_load_maximum_stays_zero_without_entries() {
  reset_fixture();
  arm_source(false, true);
  arm_inline_key_set(0u);
  g_gate_enabled = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.gate_calls == 1u);
  check(g_script.entry_calls == 0u);
  check(count_events(kEventLookupEntry) == 0u);
  check(g_asset.max_6c == 0u);
}

void test_load_gate_disabled_skips_lookup() {
  reset_fixture();
  arm_source(false, true);
  arm_inline_key_set(3u);
  g_gate_enabled = false;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.gate_calls == 1u);
  check(g_script.entry_calls == 0u);
  check(count_events(kEventLookupEntry) == 0u);
  check(g_asset.max_6c == 0u);
}

void test_load_prologue_precedes_ports() {
  reset_fixture();
  arm_source(true, false);
  arm_range(0u);
  g_asset.entries_40.last = inline_storage() + 4;
  g_asset.word_2c = 0x99999999u;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(event_at(kEventRange, 0).word == 2u);
  check(event_at(kEventRange, 0).second == 1u);
  check(g_asset.word_2c == 2u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
}

void test_load_stack_cleanup() {
  reset_fixture();
  arm_source(false, false);
  std::uintptr_t before = 0;
  std::uintptr_t after = 0;
  __asm__ volatile(
      "movl %%esp, %[before]\n\t"
      "pushl %[source]\n\t"
      "movl %[asset], %%ecx\n\t"
      "call sporepedia_asset_load_00642230\n\t"
      "movl %%esp, %[after]\n\t"
      : [before] "=m"(before), [after] "=m"(after)
      : [asset] "r"(&g_asset), [source] "r"(&g_source)
      : "ecx", "memory");
  check(before == after);
  check(g_asset.word_2c == 2u);
  check(g_asset.max_6c == 0u);
  check(count_events(kEventLookup) == 2u);
}

}

int run_tests() {
  install_ports();
  g_asset_vtable.apply_property_b4 = apply_property_hook;
  test_destroy_releases_in_reverse_order();
  test_destroy_frees_heap_entries();
  test_destroy_null_entry_pointer_skips_free();
  test_destroy_preserves_other_words();
  test_destroy_null_receivers_only_tail();
  test_load_null_source();
  test_load_source_without_refs();
  test_load_primary_ref_walks_global_range();
  test_load_both_refs_walk_range_only();
  test_load_empty_range_walks_nothing();
  test_load_secondary_ref_extracts_key();
  test_load_secondary_ref_key_order();
  test_load_secondary_ref_insert_slow_path();
  test_load_secondary_ref_collect_rejected();
  test_load_secondary_ref_collect_keeps_destination();
  test_load_maximum_reduction();
  test_load_maximum_stays_zero_without_entries();
  test_load_gate_disabled_skips_lookup();
  test_load_prologue_precedes_ports();
  test_load_stack_cleanup();
  return 0;
}

}

#undef PKG_SPOREPEDIA_WAVE10_TEST_THISCALL

int main() {
  return openspore::reconstruction::pkg_sporepedia_wave10::run_tests();
}
