#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "sporepedia_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_SAFE_WAVE10_TEST_CDECL __cdecl
#define PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL __thiscall
#else
#define PKG_SPOREPEDIA_SAFE_WAVE10_TEST_CDECL __attribute__((cdecl))
#define PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_sporepedia_safe_wave10 {
namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Word word_of(const void *pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

void *pointer_of(Word word) {
  return reinterpret_cast<void *>(static_cast<std::uintptr_t>(word));
}

Word *shifted(Word *base, std::intptr_t bytes) {
  return reinterpret_cast<Word *>(reinterpret_cast<std::uint8_t *>(base) +
                                  bytes);
}

std::intptr_t byte_distance(Word *high, Word *low) {
  return reinterpret_cast<std::uint8_t *>(high) -
         reinterpret_cast<std::uint8_t *>(low);
}

enum EventKind {
  kEventLookup = 1,
  kEventRetain = 2,
  kEventRelease = 3,
  kEventFree = 4,
  kEventBaseDestroy = 5,
  kEventKeyFill = 6,
  kEventMask = 7,
  kEventKeyCollect = 8,
  kEventReserve = 9,
  kEventInsert = 10,
  kEventRange = 11,
  kEventGate = 12,
  kEventEntry = 13,
  kEventApply = 14,
  kEventClear = 15
};

struct Event {
  int kind;
  const void *pointer;
  Word first;
  Word second;
};

std::array<Event, 512> g_events{};
std::size_t g_event_count = 0;

void record(int kind, const void *pointer, Word first, Word second) {
  check(g_event_count < g_events.size());
  g_events[g_event_count] = Event{kind, pointer, first, second};
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

std::size_t event_index(int kind, std::size_t occurrence) {
  std::size_t seen = 0;
  for (std::size_t scan = 0; scan < g_event_count; ++scan) {
    if (g_events[scan].kind != kind) {
      continue;
    }
    if (seen == occurrence) {
      return scan;
    }
    ++seen;
  }
  std::abort();
}

const Event &event_at(int kind, std::size_t occurrence) {
  return g_events[event_index(kind, occurrence)];
}

Word event_word(int kind, std::size_t occurrence) {
  return event_at(kind, occurrence).first;
}

Word event_second(int kind, std::size_t occurrence) {
  return event_at(kind, occurrence).second;
}

const void *event_pointer(int kind, std::size_t occurrence) {
  return event_at(kind, occurrence).pointer;
}

struct RefFixture {
  OpaqueAssetRefVtable vtable{};
  OpaqueAssetRef ref{};
};

struct PrimaryFixture {
  OpaqueAssetRefVtable vtable{};
  OpaqueAssetRef ref{};
  Word padding[5]{};
  OpaqueGlobalRecordRange range{};
};

static_assert(offsetof(PrimaryFixture, range) - offsetof(PrimaryFixture, ref) ==
                  kGlobalRecordRangeOffset,
              "default range port resolves to the primary reference plus "
              "0x18");

struct Script {
  bool primary_enabled = false;
  bool primary_range_enabled = false;
  bool secondary_enabled = false;
  std::size_t clear_calls = 0;
  Word *clear_field_last = nullptr;
  bool clear_field_untouched = true;
  bool fill_tag = true;
  std::uint8_t mask_results[3] = {0u, 0u, 0u};
  std::size_t mask_calls = 0;
  OpaqueKey16 mask_left[4] = {};
  OpaqueKey16 mask_right[4] = {};
  bool collect_result = false;
  bool collect_writes = true;
  OpaqueWordVector collected{};
  std::size_t reserve_calls = 0;
  Word reserve_count = 0u;
  std::size_t range_calls = 0;
  OpaqueGlobalRecordRange range_first_call{0u, 0u};
  OpaqueGlobalRecordRange range_second_call{0u, 0u};
  OpaqueLookup *gate = nullptr;
  std::size_t entry_calls = 0;
  Word entry_elements[16] = {};
  const OpaqueLookupEntry *entry_results[16] = {};
  std::size_t insert_calls = 0;
  SignedWord inline_span_words_after_entry = -1;
};

RefFixture g_access_1c;
RefFixture g_access_20;
RefFixture g_access_3c;
RefFixture g_access_70;
RefFixture g_access_74;
RefFixture g_primary;
PrimaryFixture g_primary_range{};
OpaqueKeyedSet g_keyed{};
OpaqueAssetRefVtable g_keyed_vtable{};
OpaqueLookupSourceVtable g_source_vtable{};
OpaqueLookupSource g_source{};
OpaqueAssetVtable g_asset_vtable{};
OpaqueSporepediaAsset g_asset{};
OpaqueKey16 g_tag_015da8e0 = {
    {0xa1a1a1a1u, 0xa1a1a1a2u, 0xa1a1a1a3u, 0xa1a1a1a4u}};
OpaqueKey16 g_tag_015dab18 = {
    {0xb2b2b2b1u, 0xb2b2b2b2u, 0xb2b2b2b3u, 0xb2b2b2b4u}};
OpaqueKey16 g_tag_015da80c = {
    {0xc3c3c3c1u, 0xc3c3c3c2u, 0xc3c3c3c3u, 0xc3c3c3c4u}};
Script g_script;
OpaqueSporepediaAsset *g_base_destroy_receiver = nullptr;
Word g_inline_storage[8] = {};
Word g_heap_storage[8] = {};
Word g_collect_buffer[10] = {};

Word *collect_first() {
  return g_collect_buffer + 1;
}

using LoadThunk = void(PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL *)(
    OpaqueSporepediaAsset *, OpaqueLookupSource *);

LoadThunk g_load_thunk = &sporepedia_asset_load_00642230;
OpaqueSporepediaAsset *g_asset_pointer = &g_asset;
OpaqueLookupSource *g_source_pointer = &g_source;

void PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL retain_hook(OpaqueAssetRef *ref) {
  record(kEventRetain, ref, 0u, 0u);
}

void PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL
release_hook(OpaqueAssetRef *ref) {
  record(kEventRelease, ref, 0u, 0u);
}

OpaqueAssetRef *PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL
lookup_hook(OpaqueLookupSource *source, Word id) {
  record(kEventLookup, source, id, 0u);
  check(source == &g_source);
  if (id == 0x0670da17u) {
    if (g_script.primary_range_enabled) {
      return &g_primary_range.ref;
    }
    return g_script.primary_enabled ? &g_primary.ref : nullptr;
  }
  if (id == 0x03c609f8u) {
    return g_script.secondary_enabled
               ? reinterpret_cast<OpaqueAssetRef *>(&g_keyed)
               : nullptr;
  }
  return nullptr;
}

void PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL
apply_hook(OpaqueSporepediaAsset *asset, const OpaqueGlobalRecord *entry) {
  record(kEventApply, entry, 0u, 0u);
  check(asset == &g_asset);
}

OpaqueKey16 *PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL
key_fill_hook(OpaqueKeyedSet *tags, OpaqueKey16 *out, Word selector) {
  record(kEventKeyFill, out, selector, 0u);
  check(tags == &g_keyed);
  if (g_script.fill_tag) {
    for (std::size_t index = 0; index < 4u; ++index) {
      out->words[index] = 0x5a5a0000u + static_cast<Word>(index);
    }
  }
  return out;
}

std::uint8_t PKG_SPOREPEDIA_SAFE_WAVE10_TEST_CDECL
mask_hook(OpaqueKey16 left, OpaqueKey16 right) {
  check(g_script.mask_calls < 4u);
  g_script.mask_left[g_script.mask_calls] = left;
  g_script.mask_right[g_script.mask_calls] = right;
  const std::uint8_t result = g_script.mask_results[g_script.mask_calls];
  ++g_script.mask_calls;
  record(kEventMask, nullptr, static_cast<Word>(g_script.mask_calls - 1u),
         result);
  return result;
}

bool PKG_SPOREPEDIA_SAFE_WAVE10_TEST_CDECL
key_collect_hook(OpaqueKeyedSet *tags, OpaqueWordVector *out) {
  record(kEventKeyCollect, out, g_script.collect_result ? 1u : 0u, 0u);
  check(tags == &g_keyed);
  if (g_script.collect_writes) {
    *out = g_script.collected;
  }
  return g_script.collect_result;
}

void PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL
reserve_hook(OpaqueInlineWordVector *vector, Word count) {
  record(kEventReserve, vector, count, 0u);
  check(vector == &g_asset.entries_40);
  ++g_script.reserve_calls;
  g_script.reserve_count = count;
}

void PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL
insert_hook(OpaqueInlineWordVector *vector, Word *slot, const Word *value) {
  record(kEventInsert, slot, value == nullptr ? 0u : *value, 0u);
  check(vector == &g_asset.entries_40);
  ++g_script.insert_calls;
  if (slot != nullptr) {
    *slot = *value;
  }
}

const OpaqueGlobalRecordRange *PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL
range_hook(OpaqueAssetRef *primary) {
  ++g_script.range_calls;
  record(kEventRange, primary, static_cast<Word>(g_script.range_calls), 0u);
  return g_script.range_calls == 1u ? &g_script.range_first_call
                                    : &g_script.range_second_call;
}

OpaqueLookup *PKG_SPOREPEDIA_SAFE_WAVE10_TEST_CDECL gate_hook() {
  record(kEventGate, g_script.gate, 0u, 0u);
  return g_script.gate;
}

const OpaqueLookupEntry *PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL
entry_hook(OpaqueLookup *gate, Word element) {
  record(kEventEntry, gate, element, 0u);
  check(g_script.entry_calls < 16u);
  g_script.entry_elements[g_script.entry_calls] = element;
  const OpaqueLookupEntry *const result =
      g_script.entry_results[g_script.entry_calls];
  ++g_script.entry_calls;
  if (g_script.inline_span_words_after_entry >= 0) {
    g_asset.entries_40.last =
        g_asset.entries_40.first +
        static_cast<Word>(g_script.inline_span_words_after_entry);
  }
  return result;
}

void PKG_SPOREPEDIA_SAFE_WAVE10_TEST_CDECL free_hook(Word address) {
  record(kEventFree, pointer_of(address), 0u, 0u);
}

void PKG_SPOREPEDIA_SAFE_WAVE10_TEST_CDECL clear_hook(void *first,
                                                      const void *last,
                                                      std::size_t count) {
  record(kEventClear, first, word_of(last), static_cast<Word>(count));
  ++g_script.clear_calls;
  g_script.clear_field_last = g_asset.entries_40.last;
  g_script.clear_field_untouched =
      g_script.clear_field_untouched && g_asset.entries_40.last == last;
}

void PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL
base_destroy_hook(OpaqueSporepediaAsset *asset) {
  record(kEventBaseDestroy, asset, 0u, 0u);
  g_base_destroy_receiver = asset;
}

void install_bindings() {
  sporepedia_safe_reset_bindings();
  SporepediaSafeBindings &bindings = sporepedia_safe_bindings();
  bindings.tag_015da8e0 = &g_tag_015da8e0;
  bindings.tag_015dab18 = &g_tag_015dab18;
  bindings.tag_015da80c = &g_tag_015da80c;
  bindings.free_00f47380 = free_hook;
  bindings.clear_011e0744 = clear_hook;
  bindings.base_destroy_006412a0 = base_destroy_hook;
  bindings.key_fill_004babe0 = key_fill_hook;
  bindings.mask_test_004f3d60 = mask_hook;
  bindings.key_collect_004f5720 = key_collect_hook;
  bindings.inline_reserve_00642070 = reserve_hook;
  bindings.inline_insert_0060a600 = insert_hook;
  bindings.global_record_range_005507a0 = range_hook;
  bindings.gate_lookup_0067dea0 = gate_hook;
  bindings.entry_lookup_007db5e0 = entry_hook;
}

void reset_fixture() {
  g_event_count = 0;
  g_script = Script{};
  g_base_destroy_receiver = nullptr;

  g_access_1c.vtable.retain_00 = retain_hook;
  g_access_1c.vtable.release_04 = release_hook;
  g_access_1c.ref.vtable = &g_access_1c.vtable;
  g_access_20.vtable.retain_00 = retain_hook;
  g_access_20.vtable.release_04 = release_hook;
  g_access_20.ref.vtable = &g_access_20.vtable;
  g_access_3c.vtable.retain_00 = retain_hook;
  g_access_3c.vtable.release_04 = release_hook;
  g_access_3c.ref.vtable = &g_access_3c.vtable;
  g_access_70.vtable.retain_00 = retain_hook;
  g_access_70.vtable.release_04 = release_hook;
  g_access_70.ref.vtable = &g_access_70.vtable;
  g_access_74.vtable.retain_00 = retain_hook;
  g_access_74.vtable.release_04 = release_hook;
  g_access_74.ref.vtable = &g_access_74.vtable;
  g_primary.vtable.retain_00 = retain_hook;
  g_primary.vtable.release_04 = release_hook;
  g_primary.ref.vtable = &g_primary.vtable;
  g_primary_range.vtable.retain_00 = retain_hook;
  g_primary_range.vtable.release_04 = release_hook;
  g_primary_range.ref.vtable = &g_primary_range.vtable;
  g_primary_range.range = OpaqueGlobalRecordRange{0u, 0u};
  g_keyed_vtable.retain_00 = retain_hook;
  g_keyed_vtable.release_04 = release_hook;
  g_keyed = OpaqueKeyedSet{};
  g_keyed.vtable = &g_keyed_vtable;
  g_keyed.word_18 = 0u;

  g_source_vtable.lookup_0c = lookup_hook;
  g_source.vtable = &g_source_vtable;

  g_asset_vtable.apply_property_b4 = apply_hook;
  g_asset = OpaqueSporepediaAsset{};
  g_asset.vtable_00 = &g_asset_vtable;
  g_asset.access_1c = &g_access_1c.ref;
  g_asset.access_20 = &g_access_20.ref;
  g_asset.access_3c = &g_access_3c.ref;
  g_asset.access_70 = &g_access_70.ref;
  g_asset.access_74 = &g_access_74.ref;
  g_asset.entries_40.first = g_inline_storage;
  g_asset.entries_40.last = g_inline_storage;
  g_asset.entries_40.capacity = g_inline_storage + 8;
  g_asset.entries_40.filler_0c = 0u;
  g_asset.entries_40.inline_marker_10 = word_of(g_inline_storage);

  install_bindings();
}

void arm_collected(Word count) {
  for (std::size_t index = 0; index < 10u; ++index) {
    g_collect_buffer[index] = 0x9000u + static_cast<Word>(index);
  }
  g_collect_buffer[0] = 1u;
  g_script.collected.first = collect_first();
  g_script.collected.last = collect_first() + count;
  g_script.collected.capacity = g_collect_buffer + 10;
}

void arm_inline_entries(Word count) {
  g_asset.entries_40.first = g_inline_storage;
  g_asset.entries_40.last = g_inline_storage + count;
  for (Word index = 0; index < count; ++index) {
    g_inline_storage[index] = 0xa000u + index;
  }
}

int run_destroy() {
  sporepedia_asset_destroy_00642190(&g_asset);
  return 0;
}

void test_abi_type_shapes() {
  check(sizeof(decltype(&sporepedia_asset_destroy_00642190)) ==
        sizeof(void (*)()));
  check(sizeof(decltype(&sporepedia_asset_load_00642230)) ==
        sizeof(void (*)()));
  static_assert(sizeof(OpaqueSporepediaAsset) == 0x78, "asset size");
  static_assert(offsetof(OpaqueSporepediaAsset, access_74) == 0x74,
                "asset fifth accessor offset");
  static_assert(offsetof(OpaqueSporepediaAsset, entries_40) == 0x40,
                "asset inline entry vector offset");
  static_assert(offsetof(OpaqueSporepediaAsset, max_6c) == 0x6c,
                "asset maximum word offset");
  static_assert(offsetof(OpaqueAssetVtable, apply_property_b4) == 0xb4,
                "asset apply property slot offset");
  static_assert(offsetof(OpaqueLookupSourceVtable, lookup_0c) == 0x0c,
                "source lookup slot offset");
  static_assert(offsetof(OpaqueAssetRefVtable, release_04) == 0x04,
                "reference release slot offset");
  static_assert(std::is_same<BaseDestroyPort,
                             void(PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL *)(
                                 OpaqueSporepediaAsset *)>::value,
                "base destroy port returns void");
  static_assert(
      std::is_same<ClearPort, void(PKG_SPOREPEDIA_SAFE_WAVE10_TEST_CDECL *)(
                                  void *, const void *, std::size_t)>::value,
      "clear port takes three cdecl words");
}

void test_bindings_round_trip() {
  reset_fixture();
  SporepediaSafeBindings published = sporepedia_safe_bindings();
  check(published.vtable_words.primary_00 == 0x013ff648u);
  check(published.vtable_words.secondary_10 == 0x01462748u);
  check(published.vtable_words.tertiary_14 == 0x01462738u);
  check(published.tag_015da8e0 == &g_tag_015da8e0);
  check(published.tag_015dab18 == &g_tag_015dab18);
  check(published.tag_015da80c == &g_tag_015da80c);
  sporepedia_safe_reset_bindings();
  const SporepediaSafeBindings &defaults = sporepedia_safe_bindings();
  check(defaults.vtable_words.primary_00 == 0x013ff648u);
  check(defaults.vtable_words.secondary_10 == 0x01462748u);
  check(defaults.vtable_words.tertiary_14 == 0x01462738u);
  check(defaults.tag_015da8e0 != nullptr);
  check(defaults.tag_015dab18 != nullptr);
  check(defaults.tag_015da80c != nullptr);
  install_bindings();
}

void test_destroy_writes_three_vtable_words_in_order() {
  reset_fixture();
  run_destroy();
  check(g_asset.vtable_00 == pointer_of(0x013ff648u));
  check(word_of(g_asset.vtable_10) == 0x01462748u);
  check(word_of(g_asset.vtable_14) == 0x01462738u);
  check(g_event_count >= 6u);
  check(g_events[0].kind == kEventRelease);
  check(event_index(kEventBaseDestroy, 0u) == g_event_count - 1u);
}

void test_destroy_releases_five_refs_in_field_order() {
  reset_fixture();
  run_destroy();
  check(count_events(kEventRelease) == 5u);
  check(event_pointer(kEventRelease, 0u) == &g_access_74.ref);
  check(event_pointer(kEventRelease, 1u) == &g_access_70.ref);
  check(event_pointer(kEventRelease, 2u) == &g_access_3c.ref);
  check(event_pointer(kEventRelease, 3u) == &g_access_20.ref);
  check(event_pointer(kEventRelease, 4u) == &g_access_1c.ref);
  check(count_events(kEventRetain) == 0u);
  check(g_base_destroy_receiver == &g_asset);
}

void test_destroy_free_sits_between_second_and_third_release() {
  reset_fixture();
  g_asset.entries_40.first = g_heap_storage;
  g_asset.entries_40.last = g_heap_storage + 2;
  run_destroy();
  check(count_events(kEventFree) == 1u);
  check(event_pointer(kEventFree, 0u) == g_heap_storage);
  check(event_index(kEventFree, 0u) == 2u);
  check(g_events[0].kind == kEventRelease);
  check(g_events[1].kind == kEventRelease);
  check(g_events[3].kind == kEventRelease);
}

void test_destroy_skips_free_when_pointer_matches_inline_marker() {
  reset_fixture();
  g_asset.entries_40.first = g_inline_storage;
  g_asset.entries_40.last = g_inline_storage + 3;
  g_asset.entries_40.inline_marker_10 = word_of(g_inline_storage);
  run_destroy();
  check(count_events(kEventFree) == 0u);
  check(count_events(kEventRelease) == 5u);
}

void test_destroy_skips_free_when_pointer_is_null() {
  reset_fixture();
  g_asset.entries_40.first = nullptr;
  g_asset.entries_40.last = nullptr;
  run_destroy();
  check(count_events(kEventFree) == 0u);
  check(count_events(kEventRelease) == 5u);
}

void test_destroy_frees_unmarked_heap_pointer() {
  reset_fixture();
  g_asset.entries_40.first = g_heap_storage;
  g_asset.entries_40.inline_marker_10 = 0xdeadbeefu;
  run_destroy();
  check(count_events(kEventFree) == 1u);
  check(event_pointer(kEventFree, 0u) == g_heap_storage);
}

void test_destroy_skips_null_receivers() {
  reset_fixture();
  g_asset.access_74 = nullptr;
  g_asset.access_70 = nullptr;
  g_asset.access_3c = nullptr;
  g_asset.access_20 = nullptr;
  g_asset.access_1c = nullptr;
  g_asset.entries_40.first = nullptr;
  run_destroy();
  check(count_events(kEventRelease) == 0u);
  check(count_events(kEventFree) == 0u);
  check(count_events(kEventBaseDestroy) == 1u);
}

void test_destroy_returns_to_its_call_site() {
  reset_fixture();
  Word sentinel = 0u;
  run_destroy();
  sentinel = 1u;
  check(sentinel == 1u);
  check(count_events(kEventBaseDestroy) == 1u);
  check(count_events(kEventRelease) == 5u);
  check(g_base_destroy_receiver == &g_asset);
}

void test_observed_vtable_words_come_from_the_default_bindings() {
  reset_fixture();
  sporepedia_safe_reset_bindings();
  sporepedia_safe_bindings().base_destroy_006412a0 = base_destroy_hook;
  g_asset = OpaqueSporepediaAsset{};
  g_asset.entries_40.first = g_inline_storage;
  g_asset.entries_40.inline_marker_10 = word_of(g_inline_storage);
  g_asset.access_1c = &g_access_1c.ref;
  g_asset.access_20 = &g_access_20.ref;
  g_asset.access_3c = &g_access_3c.ref;
  g_asset.access_70 = &g_access_70.ref;
  g_asset.access_74 = &g_access_74.ref;
  sporepedia_asset_destroy_00642190(&g_asset);
  check(g_asset.vtable_00 == pointer_of(0x013ff648u));
  check(word_of(g_asset.vtable_10) == 0x01462748u);
  check(word_of(g_asset.vtable_14) == 0x01462738u);
  check(g_asset.vtable_00 != pointer_of(0x01403758u));
  check(word_of(g_asset.vtable_10) != 0x013eb938u);
  check(word_of(g_asset.vtable_14) != 0x013ec458u);
  install_bindings();
}

void test_default_destroy_writes_observed_words_before_the_base_tail() {
  reset_fixture();
  sporepedia_safe_reset_bindings();
  g_asset = OpaqueSporepediaAsset{};
  g_asset.entries_40.first = g_inline_storage;
  g_asset.entries_40.inline_marker_10 = word_of(g_inline_storage);
  g_asset.access_1c = &g_access_1c.ref;
  g_asset.access_20 = &g_access_20.ref;
  g_asset.access_3c = &g_access_3c.ref;
  g_asset.access_70 = &g_access_70.ref;
  g_asset.access_74 = &g_access_74.ref;
  sporepedia_asset_destroy_00642190(&g_asset);
  check(g_asset.vtable_00 == pointer_of(0x01403758u));
  check(word_of(g_asset.vtable_10) == 0x013eb938u);
  check(word_of(g_asset.vtable_14) == 0x013ec458u);
  install_bindings();
}

void test_default_base_destroy_resets_three_vtable_words() {
  reset_fixture();
  sporepedia_safe_reset_bindings();
  g_asset = OpaqueSporepediaAsset{};
  g_asset.state_2c = 0x77777777u;
  g_asset.max_6c = 0x88888888u;
  const BaseDestroyPort port = sporepedia_safe_bindings().base_destroy_006412a0;
  port(&g_asset);
  check(g_asset.vtable_00 == pointer_of(0x01403758u));
  check(word_of(g_asset.vtable_10) == 0x013eb938u);
  check(word_of(g_asset.vtable_14) == 0x013ec458u);
  check(g_asset.state_2c == 0x77777777u);
  check(g_asset.max_6c == 0x88888888u);
  install_bindings();
}

void test_destroy_after_default_base_destroy_stays_callable() {
  reset_fixture();
  sporepedia_safe_reset_bindings();
  g_asset = OpaqueSporepediaAsset{};
  g_asset.entries_40.first = g_inline_storage;
  g_asset.entries_40.last = g_inline_storage;
  g_asset.entries_40.capacity = g_inline_storage + 8;
  g_asset.entries_40.inline_marker_10 = word_of(g_inline_storage);
  g_asset.access_1c = &g_access_1c.ref;
  g_asset.access_20 = &g_access_20.ref;
  g_asset.access_3c = &g_access_3c.ref;
  g_asset.access_70 = &g_access_70.ref;
  g_asset.access_74 = &g_access_74.ref;
  sporepedia_asset_destroy_00642190(&g_asset);
  check(g_asset.vtable_00 == pointer_of(0x01403758u));
  check(word_of(g_asset.vtable_10) == 0x013eb938u);
  check(word_of(g_asset.vtable_14) == 0x013ec458u);
  install_bindings();
}

void test_destroy_tail_precedes_every_other_port() {
  reset_fixture();
  run_destroy();
  check(event_index(kEventBaseDestroy, 0u) == g_event_count - 1u);
  for (std::size_t scan = 0; scan < g_event_count; ++scan) {
    check(g_events[scan].kind != kEventBaseDestroy ||
          scan == g_event_count - 1u);
  }
}

void test_load_prologue_sets_state_2c_and_clears_entries() {
  reset_fixture();
  g_asset.state_2c = 0x99999999u;
  arm_inline_entries(4u);
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(g_asset.state_2c == 2u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
}

void test_load_prologue_clears_by_byte_span_arithmetic() {
  reset_fixture();
  g_asset.entries_40.last = shifted(g_asset.entries_40.first, 6);
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(byte_distance(g_asset.entries_40.last, g_asset.entries_40.first) == 2);
}

void test_load_prologue_clears_whole_element_spans() {
  reset_fixture();
  g_asset.entries_40.last = shifted(g_asset.entries_40.first, 16);
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
}

void test_load_prologue_clears_backwards_byte_span() {
  reset_fixture();
  g_asset.entries_40.last = shifted(g_asset.entries_40.first, -6);
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(byte_distance(g_asset.entries_40.last, g_asset.entries_40.first) == 2);
}

void test_load_prologue_clears_through_three_argument_port() {
  reset_fixture();
  arm_inline_entries(4u);
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(count_events(kEventClear) == 1u);
  check(event_pointer(kEventClear, 0u) == g_inline_storage);
  check(event_word(kEventClear, 0u) == word_of(g_inline_storage + 4));
  check(event_second(kEventClear, 0u) == 0u);
  check(event_index(kEventClear, 0u) == 0u);
}

void test_load_clear_port_precedes_the_signed_end_adjustment() {
  reset_fixture();
  arm_inline_entries(4u);
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(g_script.clear_calls == 1u);
  check(g_script.clear_field_untouched);
  check(g_script.clear_field_last == g_inline_storage + 4);
  check(g_asset.entries_40.last == g_inline_storage);
}

void test_load_clear_port_receives_a_misaligned_end() {
  reset_fixture();
  Word *const armed_last = shifted(g_asset.entries_40.first, 6);
  g_asset.entries_40.last = armed_last;
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(count_events(kEventClear) == 1u);
  check(event_word(kEventClear, 0u) == word_of(armed_last));
  check(event_second(kEventClear, 0u) == 0u);
  check(byte_distance(g_asset.entries_40.last, g_asset.entries_40.first) == 2);
}

void test_load_null_source_still_clears_through_the_port() {
  reset_fixture();
  arm_inline_entries(2u);
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(count_events(kEventClear) == 1u);
  check(event_pointer(kEventClear, 0u) == g_inline_storage);
  check(event_word(kEventClear, 0u) == word_of(g_inline_storage + 2));
  check(g_asset.entries_40.last == g_inline_storage);
}

void test_load_null_source_skips_every_source_port() {
  reset_fixture();
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(g_asset.state_2c == 2u);
  check(g_asset.max_6c == 0u);
  check(count_events(kEventLookup) == 0u);
  check(count_events(kEventRetain) == 0u);
  check(count_events(kEventRelease) == 0u);
  check(count_events(kEventKeyFill) == 0u);
  check(count_events(kEventMask) == 0u);
  check(count_events(kEventKeyCollect) == 0u);
  check(count_events(kEventReserve) == 0u);
  check(count_events(kEventRange) == 0u);
  check(count_events(kEventGate) == 1u);
}

void test_load_uses_the_two_observed_lookup_ids_in_order() {
  reset_fixture();
  g_script.primary_enabled = true;
  g_script.range_first_call = OpaqueGlobalRecordRange{0u, 0u};
  g_script.range_second_call = OpaqueGlobalRecordRange{0u, 0u};
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventLookup) == 2u);
  check(event_word(kEventLookup, 0u) == 0x0670da17u);
  check(event_word(kEventLookup, 1u) == 0x03c609f8u);
  check(event_pointer(kEventLookup, 0u) == &g_source);
  check(event_pointer(kEventLookup, 1u) == &g_source);
}

void test_load_retains_each_resolved_ref_immediately() {
  reset_fixture();
  g_script.primary_enabled = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventRetain) == 1u);
  check(event_pointer(kEventRetain, 0u) == &g_primary.ref);
  check(event_index(kEventRetain, 0u) == 2u);

  reset_fixture();
  g_script.secondary_enabled = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventRetain) == 1u);
  check(event_pointer(kEventRetain, 0u) == &g_keyed);
  check(event_index(kEventRetain, 0u) == 3u);
}

void test_load_primary_branch_walks_range_with_stride_0c() {
  reset_fixture();
  g_script.primary_enabled = true;
  static std::array<Word, 12> records = {
      {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}};
  g_script.range_first_call =
      OpaqueGlobalRecordRange{word_of(records.data()), 0u};
  g_script.range_second_call =
      OpaqueGlobalRecordRange{0u, word_of(records.data() + 9)};
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventApply) == 3u);
  check(event_pointer(kEventApply, 0u) == records.data());
  check(event_pointer(kEventApply, 1u) == records.data() + 3);
  check(event_pointer(kEventApply, 2u) == records.data() + 6);
  check(count_events(kEventKeyFill) == 0u);
  check(count_events(kEventKeyCollect) == 0u);
}

void test_load_range_uses_two_separate_port_calls() {
  reset_fixture();
  g_script.primary_enabled = true;
  static std::array<Word, 3> records = {{0u, 0u, 0u}};
  g_script.range_first_call =
      OpaqueGlobalRecordRange{word_of(records.data()), 0xdeadbeefu};
  g_script.range_second_call =
      OpaqueGlobalRecordRange{0xfeedfaceu, word_of(records.data() + 3)};
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.range_calls == 2u);
  check(event_word(kEventRange, 0u) == 1u);
  check(event_word(kEventRange, 1u) == 2u);
  check(count_events(kEventApply) == 1u);
  check(event_pointer(kEventApply, 0u) == records.data());
}

void test_load_range_port_receives_the_primary_ref_as_this() {
  reset_fixture();
  g_script.primary_enabled = true;
  g_script.range_first_call = OpaqueGlobalRecordRange{0u, 0u};
  g_script.range_second_call = OpaqueGlobalRecordRange{0u, 0u};
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.range_calls == 2u);
  check(event_pointer(kEventRange, 0u) == &g_primary.ref);
  check(event_pointer(kEventRange, 1u) == &g_primary.ref);
}

void test_load_range_port_is_skipped_without_a_primary() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_script.collect_result = false;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.range_calls == 0u);
  check(count_events(kEventRange) == 0u);
}

void test_default_range_port_returns_the_primary_plus_0x18() {
  sporepedia_safe_reset_bindings();
  const GlobalRecordRangePort port =
      sporepedia_safe_bindings().global_record_range_005507a0;
  g_primary_range.ref.vtable = &g_primary_range.vtable;
  g_primary_range.range = OpaqueGlobalRecordRange{0x11223344u, 0x55667788u};
  const OpaqueGlobalRecordRange *const resolved = port(&g_primary_range.ref);
  check(resolved == &g_primary_range.range);
  check(reinterpret_cast<std::uintptr_t>(resolved) ==
        reinterpret_cast<std::uintptr_t>(&g_primary_range.ref) +
            kGlobalRecordRangeOffset);
  check(resolved->first == 0x11223344u);
  check(resolved->last == 0x55667788u);
  g_primary_range.range = OpaqueGlobalRecordRange{0u, 0u};
  install_bindings();
}

void test_default_range_port_feeds_the_record_walk_through_thiscall() {
  reset_fixture();
  sporepedia_safe_reset_bindings();
  g_script.primary_range_enabled = true;
  static std::array<Word, 9> records = {{0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}};
  g_primary_range.range = OpaqueGlobalRecordRange{word_of(records.data()),
                                                  word_of(records.data() + 6)};
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventApply) == 2u);
  check(event_pointer(kEventApply, 0u) == records.data());
  check(event_pointer(kEventApply, 1u) == records.data() + 3);
  check(count_events(kEventRelease) == 1u);
  check(event_pointer(kEventRelease, 0u) == &g_primary_range.ref);
  check(g_asset.state_2c == 2u);
  check(g_asset.max_6c == 0u);
  g_primary_range.range = OpaqueGlobalRecordRange{0u, 0u};
  install_bindings();
}

void test_load_empty_range_walks_nothing() {
  reset_fixture();
  g_script.primary_enabled = true;
  g_script.range_first_call = OpaqueGlobalRecordRange{0x33333333u, 0x33333333u};
  g_script.range_second_call =
      OpaqueGlobalRecordRange{0x33333333u, 0x33333333u};
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.range_calls == 2u);
  check(count_events(kEventApply) == 0u);
}

void test_load_branch_is_exclusive_on_primary() {
  reset_fixture();
  g_script.primary_enabled = true;
  g_script.secondary_enabled = true;
  g_keyed.word_18 = 0x77u;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventLookup) == 2u);
  check(count_events(kEventApply) >= 0u);
  check(count_events(kEventKeyFill) == 0u);
  check(count_events(kEventMask) == 0u);
  check(count_events(kEventKeyCollect) == 0u);
  check(g_asset.source_word_28 == 0u);
  check(g_asset.flag_24 == 0u);
  check(g_asset.flag_25 == 0u);
  check(g_asset.flag_26 == 0u);
}

void test_load_branch_is_exclusive_on_secondary() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_script.collect_result = false;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.range_calls == 0u);
  check(count_events(kEventApply) == 0u);
  check(count_events(kEventKeyFill) == 1u);
  check(g_script.mask_calls == 3u);
}

void test_load_no_refs_skips_both_branches() {
  reset_fixture();
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.range_calls == 0u);
  check(count_events(kEventApply) == 0u);
  check(count_events(kEventKeyFill) == 0u);
  check(g_script.mask_calls == 0u);
  check(count_events(kEventKeyCollect) == 0u);
  check(count_events(kEventRelease) == 0u);
}

void test_load_keyed_branch_copies_word_18_before_key_fill() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_keyed.word_18 = 0x5eed1234u;
  g_script.collect_result = false;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_asset.source_word_28 == 0x5eed1234u);
  check(count_events(kEventKeyFill) == 1u);
  check(event_word(kEventKeyFill, 0u) == 1u);
  check(event_index(kEventKeyFill, 0u) > 2u);
}

void test_load_mask_order_and_keys_are_exact() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_script.collect_result = false;
  g_script.mask_results[0] = 11u;
  g_script.mask_results[1] = 22u;
  g_script.mask_results[2] = 33u;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.mask_calls == 3u);
  check(g_script.mask_left[0].words[0] == 0x5a5a0000u);
  check(g_script.mask_left[1].words[0] == 0x5a5a0000u);
  check(g_script.mask_left[2].words[0] == 0x5a5a0000u);
  check(g_script.mask_left[0].words[3] == 0x5a5a0003u);
  check(g_script.mask_left[2].words[3] == 0x5a5a0003u);
  check(g_script.mask_right[0].words[0] == 0xa1a1a1a1u);
  check(g_script.mask_right[1].words[0] == 0xb2b2b2b1u);
  check(g_script.mask_right[2].words[0] == 0xc3c3c3c1u);
  check(g_script.mask_right[0].words[3] == 0xa1a1a1a4u);
  check(g_script.mask_right[1].words[3] == 0xb2b2b2b4u);
  check(g_script.mask_right[2].words[3] == 0xc3c3c3c4u);
  check(g_asset.flag_25 == 11u);
  check(g_asset.flag_24 == 22u);
  check(g_asset.flag_26 == 33u);
}

void test_load_mask_skips_untouched_key_words() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_script.collect_result = false;
  g_script.fill_tag = false;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.mask_calls == 3u);
  check(g_script.mask_left[0].words[0] == 0u);
  check(g_script.mask_left[1].words[0] == 0u);
  check(g_script.mask_left[2].words[0] == 0u);
  check(g_script.mask_right[0].words[0] == 0xa1a1a1a1u);
  check(g_asset.flag_24 == 0u);
  check(g_asset.flag_25 == 0u);
  check(g_asset.flag_26 == 0u);
}

void test_load_collect_false_skips_reserve_and_append() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(3u);
  g_script.collect_result = false;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventKeyCollect) == 1u);
  check(g_script.reserve_calls == 0u);
  check(count_events(kEventInsert) == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
  check(count_events(kEventFree) == 1u);
}

void test_load_collect_true_reserves_even_when_empty() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(0u);
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.reserve_calls == 1u);
  check(g_script.reserve_count == 0u);
  check(count_events(kEventInsert) == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
}

void test_load_reserve_receives_signed_word_quotient() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(3u);
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.reserve_calls == 1u);
  check(g_script.reserve_count == 3u);
}

void test_load_reserve_receives_a_negative_signed_quotient() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(0u);
  g_script.collected.first = collect_first() + 3u;
  g_script.collected.last = collect_first();
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.reserve_calls == 1u);
  check(g_script.reserve_count == static_cast<Word>(-3));
  check(count_events(kEventInsert) == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
  check(count_events(kEventFree) == 1u);
}

void test_load_append_uses_in_place_fast_path() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(3u);
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.insert_calls == 0u);
  check(count_events(kEventInsert) == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first + 3);
  check(g_inline_storage[0] == 0x9001u);
  check(g_inline_storage[1] == 0x9002u);
  check(g_inline_storage[2] == 0x9003u);
}

void test_load_append_uses_insert_port_at_capacity() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_asset.entries_40.capacity = g_asset.entries_40.first;
  arm_collected(3u);
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.insert_calls == 3u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
}

void test_load_append_switches_path_at_capacity() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_asset.entries_40.capacity = g_inline_storage + 1;
  arm_collected(3u);
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.insert_calls == 2u);
  check(g_asset.entries_40.last == g_asset.entries_40.first + 1);
  check(g_inline_storage[0] == 0x9001u);
}

void test_load_append_walks_collection_in_order() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_asset.entries_40.capacity = g_asset.entries_40.first;
  arm_collected(4u);
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.insert_calls == 4u);
  check(count_events(kEventInsert) == 4u);
  check(event_word(kEventInsert, 0u) == 0x9001u);
  check(event_word(kEventInsert, 1u) == 0x9002u);
  check(event_word(kEventInsert, 2u) == 0x9003u);
  check(event_word(kEventInsert, 3u) == 0x9004u);
}

void test_load_free_guard_reads_the_word_before_first() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(2u);
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventFree) == 1u);
  check(event_pointer(kEventFree, 0u) == collect_first());
  check(event_index(kEventFree, 0u) > 0u);
}

void test_load_free_skips_when_preceding_word_is_zero() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(2u);
  g_script.collected.first[-1] = 0u;
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventFree) == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first + 2);
}

void test_load_free_skips_when_collection_pointer_is_null() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_script.collect_result = true;
  g_script.collect_writes = false;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.reserve_calls == 1u);
  check(g_script.reserve_count == 0u);
  check(count_events(kEventFree) == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
}

void test_load_maximum_is_zeroed_before_the_gate() {
  reset_fixture();
  g_asset.max_6c = 0xffffffffu;
  sporepedia_asset_load_00642230(&g_asset, nullptr);
  check(g_asset.max_6c == 0u);
  check(count_events(kEventGate) == 1u);
  check(count_events(kEventEntry) == 0u);
}

void test_load_gate_guard_call_precedes_every_entry_lookup() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(2u);
  g_script.collect_result = true;
  g_script.gate = reinterpret_cast<OpaqueLookup *>(&g_primary.ref);
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventGate) == 3u);
  check(count_events(kEventEntry) == 2u);
  check(event_word(kEventEntry, 0u) == 0x9001u);
  check(event_word(kEventEntry, 1u) == 0x9002u);
  check(event_pointer(kEventEntry, 0u) == g_script.gate);
  check(event_pointer(kEventEntry, 1u) == g_script.gate);
  check(g_script.entry_calls == 2u);
}

void test_load_maximum_reduction_is_signed() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(4u);
  g_script.collect_result = true;
  g_script.gate = reinterpret_cast<OpaqueLookup *>(&g_primary.ref);
  static std::array<OpaqueLookupEntry, 4> entries = {{
      {0u, 5u},
      {0u, 0u},
      {0u, 0xffffffffu},
      {0u, 9u},
  }};
  g_script.entry_results[0] = &entries[0];
  g_script.entry_results[1] = &entries[1];
  g_script.entry_results[2] = &entries[2];
  g_script.entry_results[3] = &entries[3];
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.entry_calls == 4u);
  check(g_asset.max_6c == 9u);
}

void test_load_maximum_ignores_negative_candidates() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(3u);
  g_script.collect_result = true;
  g_script.gate = reinterpret_cast<OpaqueLookup *>(&g_primary.ref);
  static std::array<OpaqueLookupEntry, 3> entries = {{
      {0u, 0x7fffffffu},
      {0u, 0x80000000u},
      {0u, 0xffffffffu},
  }};
  g_script.entry_results[0] = &entries[0];
  g_script.entry_results[1] = &entries[1];
  g_script.entry_results[2] = &entries[2];
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.entry_calls == 3u);
  check(g_asset.max_6c == 0x7fffffffu);
}

void test_load_maximum_keeps_equal_candidate() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(2u);
  g_script.collect_result = true;
  g_script.gate = reinterpret_cast<OpaqueLookup *>(&g_primary.ref);
  static std::array<OpaqueLookupEntry, 2> entries = {{
      {0u, 7u},
      {0u, 7u},
  }};
  g_script.entry_results[0] = &entries[0];
  g_script.entry_results[1] = &entries[1];
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_asset.max_6c == 7u);
}

void test_load_maximum_keeps_zero_for_all_negative_values() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(2u);
  g_script.collect_result = true;
  g_script.gate = reinterpret_cast<OpaqueLookup *>(&g_primary.ref);
  static std::array<OpaqueLookupEntry, 2> entries = {{
      {0u, 0xffffffffu},
      {0u, 0xfffffffeu},
  }};
  g_script.entry_results[0] = &entries[0];
  g_script.entry_results[1] = &entries[1];
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_asset.max_6c == 0u);
}

void test_load_maximum_skipped_when_gate_is_null() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(3u);
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_asset.entries_40.last == g_asset.entries_40.first + 3);
  check(count_events(kEventGate) == 1u);
  check(g_script.entry_calls == 0u);
  check(g_asset.max_6c == 0u);
}

void test_load_gate_bound_is_recomputed_each_iteration() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(4u);
  g_script.collect_result = true;
  g_script.gate = reinterpret_cast<OpaqueLookup *>(&g_primary.ref);
  g_script.inline_span_words_after_entry = 0;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.entry_calls == 1u);
  check(count_events(kEventEntry) == 1u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
}

void test_load_gate_bound_follows_a_grown_span() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(4u);
  g_script.collect_result = true;
  g_script.gate = reinterpret_cast<OpaqueLookup *>(&g_primary.ref);
  g_script.inline_span_words_after_entry = 6;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_script.entry_calls == 6u);
  check(count_events(kEventEntry) == 6u);
  check(event_word(kEventEntry, 0u) == 0x9001u);
  check(event_word(kEventEntry, 3u) == 0x9004u);
  check(event_word(kEventEntry, 4u) == 0u);
}

void test_load_gate_bound_skips_non_positive_span() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_script.gate = reinterpret_cast<OpaqueLookup *>(&g_primary.ref);
  g_asset.entries_40.last = g_asset.entries_40.first;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventGate) == 1u);
  check(g_script.entry_calls == 0u);
  check(g_asset.max_6c == 0u);
}

void test_load_gate_bound_skips_a_backwards_inline_span() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_script.gate = reinterpret_cast<OpaqueLookup *>(&g_primary.ref);
  g_asset.entries_40.last = g_asset.entries_40.first - 3;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventGate) == 1u);
  check(g_script.entry_calls == 0u);
  check(g_asset.max_6c == 0u);
}

void test_load_collect_guard_skips_a_backwards_span() {
  reset_fixture();
  g_script.secondary_enabled = true;
  arm_collected(0u);
  g_script.collected.first = collect_first() + 3u;
  g_script.collected.last = collect_first();
  g_script.collect_result = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventKeyCollect) == 1u);
  check(count_events(kEventInsert) == 0u);
  check(g_script.entry_calls == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
}

void test_load_releases_secondary_before_primary() {
  reset_fixture();
  g_script.primary_enabled = true;
  g_script.secondary_enabled = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventRelease) == 2u);
  check(event_pointer(kEventRelease, 0u) == &g_keyed);
  check(event_pointer(kEventRelease, 1u) == &g_primary.ref);
  check(event_index(kEventRelease, 1u) == g_event_count - 1u);
}

void test_load_releases_secondary_only_when_primary_absent() {
  reset_fixture();
  g_script.secondary_enabled = true;
  g_script.collect_result = false;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventRelease) == 1u);
  check(event_pointer(kEventRelease, 0u) == &g_keyed);
}

void test_load_releases_primary_only_when_secondary_absent() {
  reset_fixture();
  g_script.primary_enabled = true;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(count_events(kEventRelease) == 1u);
  check(event_pointer(kEventRelease, 0u) == &g_primary.ref);
}

void test_load_stack_cleanup_matches_ret_4() {
  reset_fixture();
  std::uintptr_t before = 0u;
  std::uintptr_t after = 0u;
  __asm__ volatile(
      "movl %%esp, %[before]\n\t"
      "pushl %[source]\n\t"
      "movl %[asset], %%ecx\n\t"
      "movl %[loader], %%edx\n\t"
      "call *%%edx\n\t"
      "movl %%esp, %[after]\n\t"
      : [before] "=m"(before), [after] "=m"(after)
      : [asset] "m"(g_asset_pointer), [source] "m"(g_source_pointer),
        [loader] "m"(g_load_thunk)
      : "ecx", "edx", "memory");
  check(before == after);
  check(g_asset.state_2c == 2u);
  check(g_asset.max_6c == 0u);
  check(count_events(kEventLookup) == 2u);
}

void test_defaults_are_inert_and_shape_preserving() {
  reset_fixture();
  sporepedia_safe_reset_bindings();
  g_asset = OpaqueSporepediaAsset{};
  g_asset.entries_40.first = g_inline_storage;
  g_asset.entries_40.last = g_inline_storage + 2;
  g_asset.entries_40.capacity = g_inline_storage + 8;
  g_asset.entries_40.inline_marker_10 = word_of(g_inline_storage);
  g_asset.vtable_00 = &g_asset_vtable;
  g_inline_storage[0] = 0x5a5a0000u;
  g_inline_storage[1] = 0x5a5a0001u;
  sporepedia_asset_load_00642230(&g_asset, &g_source);
  check(g_asset.state_2c == 2u);
  check(g_asset.max_6c == 0u);
  check(g_asset.entries_40.last == g_asset.entries_40.first);
  check(g_inline_storage[0] == 0x5a5a0000u);
  check(g_inline_storage[1] == 0x5a5a0001u);
  check(count_events(kEventClear) == 0u);
  check(count_events(kEventLookup) == 2u);
  check(count_events(kEventKeyFill) == 0u);
  check(count_events(kEventKeyCollect) == 0u);
  check(g_asset.vtable_00 == &g_asset_vtable);
  install_bindings();
}

}

int run_tests() {
  test_abi_type_shapes();
  test_bindings_round_trip();
  test_destroy_writes_three_vtable_words_in_order();
  test_destroy_releases_five_refs_in_field_order();
  test_destroy_free_sits_between_second_and_third_release();
  test_destroy_skips_free_when_pointer_matches_inline_marker();
  test_destroy_skips_free_when_pointer_is_null();
  test_destroy_frees_unmarked_heap_pointer();
  test_destroy_skips_null_receivers();
  test_destroy_returns_to_its_call_site();
  test_observed_vtable_words_come_from_the_default_bindings();
  test_default_destroy_writes_observed_words_before_the_base_tail();
  test_default_base_destroy_resets_three_vtable_words();
  test_destroy_after_default_base_destroy_stays_callable();
  test_destroy_tail_precedes_every_other_port();
  test_load_prologue_sets_state_2c_and_clears_entries();
  test_load_prologue_clears_through_three_argument_port();
  test_load_clear_port_precedes_the_signed_end_adjustment();
  test_load_clear_port_receives_a_misaligned_end();
  test_load_null_source_still_clears_through_the_port();
  test_load_prologue_clears_by_byte_span_arithmetic();
  test_load_prologue_clears_whole_element_spans();
  test_load_prologue_clears_backwards_byte_span();
  test_load_null_source_skips_every_source_port();
  test_load_uses_the_two_observed_lookup_ids_in_order();
  test_load_retains_each_resolved_ref_immediately();
  test_load_primary_branch_walks_range_with_stride_0c();
  test_load_range_uses_two_separate_port_calls();
  test_load_range_port_receives_the_primary_ref_as_this();
  test_load_range_port_is_skipped_without_a_primary();
  test_default_range_port_returns_the_primary_plus_0x18();
  test_default_range_port_feeds_the_record_walk_through_thiscall();
  test_load_empty_range_walks_nothing();
  test_load_branch_is_exclusive_on_primary();
  test_load_branch_is_exclusive_on_secondary();
  test_load_no_refs_skips_both_branches();
  test_load_keyed_branch_copies_word_18_before_key_fill();
  test_load_mask_order_and_keys_are_exact();
  test_load_mask_skips_untouched_key_words();
  test_load_collect_false_skips_reserve_and_append();
  test_load_collect_true_reserves_even_when_empty();
  test_load_reserve_receives_signed_word_quotient();
  test_load_reserve_receives_a_negative_signed_quotient();
  test_load_append_uses_in_place_fast_path();
  test_load_append_uses_insert_port_at_capacity();
  test_load_append_switches_path_at_capacity();
  test_load_append_walks_collection_in_order();
  test_load_free_guard_reads_the_word_before_first();
  test_load_free_skips_when_preceding_word_is_zero();
  test_load_free_skips_when_collection_pointer_is_null();
  test_load_maximum_is_zeroed_before_the_gate();
  test_load_gate_guard_call_precedes_every_entry_lookup();
  test_load_maximum_reduction_is_signed();
  test_load_maximum_ignores_negative_candidates();
  test_load_maximum_keeps_equal_candidate();
  test_load_maximum_keeps_zero_for_all_negative_values();
  test_load_maximum_skipped_when_gate_is_null();
  test_load_gate_bound_is_recomputed_each_iteration();
  test_load_gate_bound_follows_a_grown_span();
  test_load_gate_bound_skips_non_positive_span();
  test_load_gate_bound_skips_a_backwards_inline_span();
  test_load_collect_guard_skips_a_backwards_span();
  test_load_releases_secondary_before_primary();
  test_load_releases_secondary_only_when_primary_absent();
  test_load_releases_primary_only_when_secondary_absent();
  test_load_stack_cleanup_matches_ret_4();
  test_defaults_are_inert_and_shape_preserving();
  return 0;
}

}

#undef PKG_SPOREPEDIA_SAFE_WAVE10_TEST_CDECL
#undef PKG_SPOREPEDIA_SAFE_WAVE10_TEST_THISCALL

int main() {
  return openspore::reconstruction::pkg_sporepedia_safe_wave10::run_tests();
}
