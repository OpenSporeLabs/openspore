#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>
#include <vector>

#include "pkg_palette_support_wave10.hpp"

namespace openspore::reconstruction::pkg_palette_support_wave10 {
namespace {

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

struct Arena {
  std::uint8_t data[16384];
  std::size_t used = 0;
  std::uint32_t deny_from = 0xffffffffU;
  std::uint32_t grants = 0;

  void reset() {
    used = 0;
    grants = 0;
    deny_from = 0xffffffffU;
  }

  void *take(std::uint32_t bytes) {
    const std::size_t span = (static_cast<std::size_t>(bytes) + 15U) & ~15U;
    if (used + span > sizeof(data)) {
      return nullptr;
    }
    if (grants >= deny_from) {
      return nullptr;
    }
    grants += 1U;
    void *block = data + used;
    used += span;
    std::memset(block, 0, span);
    return block;
  }
};

struct Trace {
  std::uint32_t resolve_calls;
  std::uint32_t resolve_arg0;
  std::uint32_t resolve_arg1;
  OpaqueProperty *resolve_out;
  OpaqueProperty *resolve_out2;

  std::uint32_t query_calls;
  std::uint32_t query_arg1;
  std::uint32_t query_field00;
  std::uint32_t query_field08;
  bool query_result;

  std::uint32_t group_calls;
  std::uint32_t group_id;
  std::uint32_t group_out;

  std::uint32_t instance_calls;
  std::uint32_t instance_id;
  std::uint32_t instance_out;

  std::uint32_t array_calls;
  std::uint32_t array_id;
  std::int32_t array_count;
  std::uint32_t entry0[3];
  std::uint32_t entry1[3];

  std::uint32_t key_calls;
  std::uint32_t key_id;
  std::uint32_t key_out[3];

  std::uint32_t adopt_calls;
  std::uint32_t adopt_arg[4];
  std::uint32_t adopt_key[4][3];

  std::uint32_t load_calls;
  std::uint32_t load_first_arg0;
  std::uint32_t load_arg0;
  std::uint32_t load_arg1;
  std::uint32_t load_arg2;
  std::uint32_t load_arg3;
  std::uint32_t load_arg4;
  bool load_result;

  std::uint32_t rekey_calls;
  std::uint32_t rekey_first_field20;
  std::uint32_t rekey_first_key[3];
  std::uint32_t rekey_field20;
  std::uint32_t rekey_key[3];
  std::int32_t rekey_arg2;

  std::uint32_t lookup_calls;
  std::uint32_t lookup_key;
  void *lookup_result[4];

  std::uint32_t commit_calls;
  std::uint32_t commit_arg;

  std::uint32_t member_calls;
  std::uint32_t member_arg;
  bool member_result;

  std::uint32_t insert_calls;
  std::uint32_t insert_arg;

  std::uint32_t evict_calls;
  std::uint32_t evict_arg;
  std::uint32_t evict_self;

  std::uint32_t tally_calls;
  std::uint32_t tally_out;
  std::int32_t tally_value;
  std::uint32_t tally_seed;

  std::uint32_t retain_calls;
  std::uint32_t release_calls;
  std::uint32_t release_property;

  std::uint32_t free_calls;
  std::uint32_t free_arg;

  std::uint32_t probe_calls;

  std::uint32_t filter_calls;
  std::uint32_t filter_slot[5];
  std::uint32_t filter_context[3];
  std::uint32_t filter_arg3;
  std::uint32_t filter_block;
  OpaqueResourceEntry *filter_begin;
  OpaqueResourceEntry *filter_end;

  void reset() {
    std::memset(this, 0, sizeof(Trace));
  }
};

Trace g_trace;
Arena g_arena;
std::uint32_t g_probe_storage = 0x00c0ffeeU;
std::uint32_t g_gate_link[128] = {};
std::uint32_t g_gate_page[128] = {};

constexpr std::size_t kGateLinkSlot = 0x3cU / 4U;
constexpr std::size_t kGateFlagSlot = 0x118U / 4U;

void set_gate(std::uint32_t flag) {
  g_gate_link[kGateLinkSlot] = reinterpret_cast<std::uint32_t>(g_gate_page);
  g_gate_page[kGateFlagSlot] = flag;
}

void PKG_PALETTE_SUPPORT_THISCALL node_retain(OpaqueNode *self) {
  (void)self;
  g_trace.retain_calls += 1U;
}

void PKG_PALETTE_SUPPORT_THISCALL node_release(OpaqueNode *self) {
  (void)self;
  g_trace.release_calls += 1U;
}

OpaqueNodeVtable g_node_vtable = {0U, &node_retain, &node_release};

bool PKG_PALETTE_SUPPORT_THISCALL service_resolve(OpaqueService *self,
                                                  std::uint32_t arg0,
                                                  std::uint32_t arg1,
                                                  OpaqueProperty **out) {
  (void)self;
  g_trace.resolve_calls += 1U;
  g_trace.resolve_arg0 = arg0;
  g_trace.resolve_arg1 = arg1;
  *out =
      g_trace.resolve_calls == 1U ? g_trace.resolve_out : g_trace.resolve_out2;
  return true;
}

OpaqueServiceVtable g_service_vtable = {{}, &service_resolve};
OpaqueService g_service = {&g_service_vtable};

void PKG_PALETTE_SUPPORT_THISCALL property_release(OpaqueProperty *self) {
  (void)self;
  g_trace.release_property += 1U;
}

bool PKG_PALETTE_SUPPORT_THISCALL property_query(OpaqueProperty *self,
                                                 OpaqueResourceKey *arg0,
                                                 std::uint32_t arg1) {
  (void)self;
  g_trace.query_calls += 1U;
  g_trace.query_field00 = arg0->field00;
  g_trace.query_field08 = arg0->field08;
  g_trace.query_arg1 = arg1;
  return g_trace.query_result;
}

OpaquePropertyVtable g_property_vtable = {
    {}, &property_release, {}, &property_query};
OpaqueProperty g_property = {&g_property_vtable};
OpaqueProperty g_owner = {&g_property_vtable};

void PKG_PALETTE_SUPPORT_THISCALL registry_filter(OpaqueRegistry *self,
                                                  OpaqueFilterContext *context,
                                                  OpaqueFilterFrame *frame,
                                                  std::uint32_t arg3) {
  (void)self;
  g_trace.filter_calls += 1U;
  g_trace.filter_context[0] = context->field00;
  g_trace.filter_context[1] = context->field04;
  g_trace.filter_context[2] = context->field08;
  g_trace.filter_arg3 = arg3;
  g_trace.filter_slot[0] = frame->slot.field00;
  g_trace.filter_slot[1] = frame->slot.field04;
  g_trace.filter_slot[2] = frame->slot.field08;
  g_trace.filter_slot[3] = frame->slot.field0c;
  g_trace.filter_slot[4] = frame->slot.field10;
  g_trace.filter_block = frame->field10;
  frame->list.field00 = g_trace.filter_end;
  frame->list.field04 = g_trace.filter_begin;
}

OpaqueRegistryVtable g_registry_vtable = {{}, &registry_filter};
OpaqueRegistry g_registry = {&g_registry_vtable};

OpaquePageB *make_page_b() {
  OpaquePageB *page = static_cast<OpaquePageB *>(g_arena.take(0x90));
  if (page != nullptr) {
    page->host.vtable = &g_node_vtable;
  }
  return page;
}

void bind(std::vector<void *> &items, OpaqueSlotVector &vector) {
  vector.begin = reinterpret_cast<std::uint32_t *>(items.data());
  vector.end = vector.begin + items.size();
}

void seed_node(OpaquePageA *page, OpaquePageB *other, OpaqueEntryA *entry,
               OpaqueEntryB *group, OpaqueLeaf *leaf) {
  std::memset(page, 0, sizeof(OpaquePageA));
  std::memset(other, 0, sizeof(OpaquePageB));
  std::memset(entry, 0, sizeof(OpaqueEntryA));
  std::memset(group, 0, sizeof(OpaqueEntryB));
  std::memset(leaf, 0, sizeof(OpaqueLeaf));
  page->host.vtable = &g_node_vtable;
  other->host.vtable = &g_node_vtable;
  entry->vtable = &g_node_vtable;
  group->host.vtable = &g_node_vtable;
  leaf->vtable = &g_node_vtable;
}

using MatchSignature = std::uint32_t(PKG_PALETTE_SUPPORT_THISCALL *)(
    OpaqueSupport *, OpaquePageA *, OpaquePageB *);
using ModuleSignature = void(PKG_PALETTE_SUPPORT_THISCALL *)(
    OpaqueSupport *, OpaqueResourceEntry *);
using PropSignature = bool(PKG_PALETTE_SUPPORT_THISCALL *)(
    OpaqueSupport *, OpaqueResourceKey *, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);

static_assert(
    std::is_same<decltype(&unresolved_005c5cc0), MatchSignature>::value,
    "005c5cc0 is a thiscall with two stack words released by RET 8");
static_assert(
    std::is_same<decltype(&unresolved_005c6010), ModuleSignature>::value,
    "005c6010 is a thiscall with one stack word released by RET 4");
static_assert(
    std::is_same<decltype(&unresolved_005c6340), PropSignature>::value,
    "005c6340 is a thiscall with seven stack words released by RET 1c");
static_assert(
    std::is_same<decltype(unresolved_005c5cc0(nullptr, nullptr, nullptr)),
                 std::uint32_t>::value,
    "005c5cc0 returns a full 32-bit zero or one");
static_assert(std::is_same<decltype(unresolved_005c6340(nullptr, nullptr, 0U,
                                                        0U, 0U, 0U, 0U, 0U)),
                           bool>::value,
              "005c6340 returns a single byte predicate");
static_assert(sizeof(std::uint32_t) == 4, "match result width is one word");
static_assert(sizeof(bool) == 1, "prop result width is one byte");

void test_match_empty() {
  OpaquePageA page{};
  OpaquePageB other{};
  OpaqueSupport support{};
  g_trace.reset();
  check(unresolved_005c5cc0(&support, &page, &other) == 1U,
        "empty vectors compare equal and report one");
  check(g_trace.rekey_calls == 0U, "empty vectors never rekey");
}

void test_match_full() {
  OpaquePageA page{};
  OpaquePageB other{};
  OpaqueSupport support{};
  OpaqueEntryA entries[2]{};
  OpaqueEntryB groups[1]{};
  OpaqueLeaf leaves[2]{};
  std::vector<void *> first{&entries[0], &entries[1]};
  std::vector<void *> second{&groups[0]};
  std::vector<void *> nested{&leaves[0], &leaves[1]};
  seed_node(&page, &other, &entries[0], &groups[0], &leaves[0]);
  for (std::size_t i = 0; i < 2U; ++i) {
    entries[i].vtable = &g_node_vtable;
    leaves[i].vtable = &g_node_vtable;
    entries[i].key.field00 = 0x1000U + i;
    entries[i].key.field04 = 0x2000U;
    entries[i].key.field08 = 0x3000U;
    leaves[i].key = entries[i].key;
    entries[i].field20 = 0x40U + i;
  }
  groups[0].host.field5c = 1U;
  bind(first, page.host.field70);
  bind(second, other.host.field0c);
  bind(nested, groups[0].host.field70);
  g_trace.reset();
  check(unresolved_005c5cc0(&support, &page, &other) == 1U,
        "every entry matched once reports one");
  check(g_trace.rekey_calls == 2U, "each visited entry is rekeyed once");
  check(g_trace.rekey_arg2 == -1, "rekey receives the negative sentinel");
  check(g_trace.rekey_first_field20 == 0x40U,
        "rekey records the entry override");
  check(g_trace.rekey_first_key[0] == 0x1000U, "rekey receives the entry key");
  check(entries[0].field18 == 0x1000U, "rekey copies the key into the entry");
  check(entries[0].field48 == 0xffffffffU, "rekey writes the sentinel state");
  check(entries[1].field48 == 0xffffffffU, "the second entry is stamped too");
}

void test_match_partial() {
  OpaquePageA page{};
  OpaquePageB other{};
  OpaqueSupport support{};
  OpaqueEntryA entries[2]{};
  OpaqueEntryB groups[2]{};
  OpaqueLeaf leaves[2]{};
  std::vector<void *> first{&entries[0], &entries[1], nullptr};
  std::vector<void *> second{&groups[0], &groups[1]};
  std::vector<void *> nested{&leaves[0], &leaves[1]};
  std::vector<void *> holed{nullptr};
  seed_node(&page, &other, &entries[0], &groups[0], &leaves[0]);
  for (std::size_t i = 0; i < 2U; ++i) {
    entries[i].vtable = &g_node_vtable;
    leaves[i].vtable = &g_node_vtable;
    entries[i].key.field00 = 0x1000U + i;
    entries[i].key.field04 = 0x2000U;
    entries[i].key.field08 = 0x3000U;
    leaves[i].key = entries[i].key;
  }
  leaves[1].key.field00 = 0x9999U;
  leaves[1].key.field04 = 0x8888U;
  leaves[1].key.field08 = 0x7777U;
  groups[0].host.vtable = &g_node_vtable;
  groups[1].host.vtable = &g_node_vtable;
  groups[0].host.field5c = 1U;
  groups[1].host.field5c = 1U;
  bind(first, page.host.field70);
  bind(second, other.host.field0c);
  bind(nested, groups[0].host.field70);
  bind(holed, groups[1].host.field70);
  g_trace.reset();
  check(unresolved_005c5cc0(&support, &page, &other) == 0U,
        "a null slot and a mismatched leaf break equality");
  check(g_trace.rekey_calls == 1U, "only the aligned leaf triggers a rekey");
  check(entries[0].field48 == 0xffffffffU, "the aligned entry is stamped");
  check(entries[1].field48 == 0U, "the unaligned entry stays untouched");
}

void test_match_negative_count() {
  OpaquePageA page{};
  OpaquePageB other{};
  OpaqueSupport support{};
  OpaqueEntryA entry{};
  OpaqueEntryB group{};
  OpaqueLeaf leaf{};
  std::vector<void *> first{&entry};
  std::vector<void *> second{&group, nullptr};
  std::vector<void *> nested{&leaf};
  seed_node(&page, &other, &entry, &group, &leaf);
  entry.key.field00 = 0x11U;
  entry.key.field04 = 0x22U;
  entry.key.field08 = 0x33U;
  leaf.key = entry.key;
  group.host.field5c = 1U;
  bind(first, page.host.field70);
  bind(second, other.host.field0c);
  bind(nested, group.host.field70);
  other.host.field0c.end = other.host.field0c.begin - 1;
  g_trace.reset();
  check(unresolved_005c5cc0(&support, &page, &other) == 0U,
        "a negative second count visits the entry and skips the inner loop");
  check(g_trace.rekey_calls == 0U, "no rekey without a scanned group");
  check(entry.field48 == 0U, "the entry is left unstamped");
}

void test_module_no_property() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{0x1234U, 0x5678U, 0x9abcU};
  g_arena.reset();
  g_trace.reset();
  g_trace.resolve_out = nullptr;
  unresolved_005c6010(&support, &source);
  check(g_trace.resolve_calls == 1U, "005c6010 resolves exactly once");
  check(g_trace.resolve_arg0 == 0x1234U, "resolve receives the first word");
  check(g_trace.resolve_arg1 == 0x9abcU, "resolve receives the third word");
  check(g_trace.array_calls == 0U, "a missing property skips the array query");
  check(g_trace.release_property == 0U, "a missing property is never released");
}

void test_module_empty_array() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  g_arena.reset();
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 0;
  unresolved_005c6010(&support, &source);
  check(g_trace.array_calls == 1U, "the array property is queried once");
  check(g_trace.array_id == 0xf21e733cU, "the array property id is stable");
  check(g_trace.load_calls == 0U, "an empty array allocates no page");
  check(g_trace.release_property == 1U, "the property is released once");
}

void test_module_load_failure() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  g_arena.reset();
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 1;
  g_trace.entry0[0] = 0x50U;
  g_trace.load_result = false;
  support.field30 = 0xaaU;
  support.field34 = 0xbbU;
  support.field28 = 0xccU;
  support.field2c = 0xddU;
  unresolved_005c6010(&support, &source);
  check(g_trace.load_calls == 1U, "the loader runs once per array entry");
  check(g_trace.load_arg0 == 0x50U, "the loader receives the entry instance");
  check(g_trace.load_arg1 == 0xaaU, "the loader receives field30 first");
  check(g_trace.load_arg2 == 0xbbU, "the loader receives field34 second");
  check(g_trace.load_arg3 == 0xccU, "the loader receives field28 third");
  check(g_trace.load_arg4 == 0xddU, "the loader receives field2c fourth");
  check(g_trace.retain_calls == 1U, "the loaded page is retained once");
  check(g_trace.release_calls == 1U, "a failed load releases the page once");
  check(g_trace.evict_calls == 0U, "a failed load evicts nothing");
}

void test_module_reuse() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  std::vector<std::uint32_t> span(1, 0U);
  g_arena.reset();
  OpaquePageB *by_key = make_page_b();
  OpaquePageB *by_channel = make_page_b();
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 1;
  g_trace.entry0[0] = 0x50U;
  g_trace.key_out[0] = 0x99U;
  g_trace.load_result = true;
  g_trace.lookup_result[0] = by_key;
  g_trace.lookup_result[1] = by_channel;
  g_trace.member_result = false;
  set_gate(1U);
  by_key->host.field0c.begin = span.data();
  by_key->host.field0c.end = span.data() + 1;
  unresolved_005c6010(&support, &source);
  check(g_trace.lookup_calls == 2U,
        "the key and the channel are both looked up");
  check(g_trace.lookup_key == 0x99U, "the channel lookup uses the key word");
  check(g_trace.adopt_calls == 0U, "reused slots skip adoption");
  check(g_trace.commit_calls == 0U, "reused slots skip registration");
  check(g_trace.member_calls == 1U, "the channel is asked about the key slot");
  check(g_trace.insert_calls == 1U, "a missing member triggers one insert");
  check(g_trace.insert_arg == reinterpret_cast<std::uint32_t>(by_key),
        "the key slot is the inserted member");
  check(g_trace.tally_calls == 1U, "the gate tallies the loaded page");
  check(g_trace.evict_calls == 0U, "a satisfied gate keeps the key slot");
  check(g_trace.retain_calls == 3U, "the page and both slots are retained");
  check(g_trace.release_calls == 3U, "both slots and the page are released");
  check(g_trace.release_property == 1U, "the property is released once");
  set_gate(0U);
}

void test_module_build_channels() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  g_arena.reset();
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 1;
  g_trace.key_out[0] = 0x99U;
  g_trace.key_out[1] = 0x98U;
  g_trace.key_out[2] = 0x97U;
  g_trace.load_result = true;
  g_trace.member_result = true;
  support.field24 = 0x2bU;
  unresolved_005c6010(&support, &source);
  check(g_trace.lookup_calls == 2U, "both lookups run when nothing is cached");
  check(g_trace.adopt_calls == 2U, "two pages are adopted for the two slots");
  check(g_trace.adopt_arg[0] == 0x2bU, "adoption receives the channel word");
  check(g_trace.adopt_key[0][0] == 0x99U,
        "the channel page adopts the key word");
  check(g_trace.adopt_key[0][1] == 0x98U,
        "the channel page adopts the key type");
  check(g_trace.adopt_key[0][2] == 0x97U,
        "the channel page adopts the key group");
  check(g_trace.commit_calls == 1U, "the channel page is registered once");
  check(g_trace.insert_calls == 0U, "a present member blocks the insert");
  check(g_trace.evict_calls == 1U, "an empty span fails the gate");
  check(g_trace.tally_calls == 0U, "a failed span short circuits the tally");
}

void test_module_owner_path() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  g_arena.reset();
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.resolve_out2 = &g_owner;
  g_trace.array_count = 1;
  g_trace.key_out[0] = 0x99U;
  g_trace.key_out[1] = 0x98U;
  g_trace.key_out[2] = 0x97U;
  g_trace.load_result = true;
  g_trace.member_result = false;
  support.field24 = 0x2bU;
  set_gate(0U);
  unresolved_005c6010(&support, &source);
  check(g_trace.key_calls == 1U, "a resolved owner reads the channel key");
  check(g_trace.key_id == 0xb35d7835U, "the channel key id is stable");
  check(g_trace.lookup_calls == 2U, "the owner key drives the channel lookup");
  check(g_trace.adopt_calls == 2U, "both slots are built from scratch");
  check(g_trace.adopt_key[0][0] == 0x99U, "the channel page adopts the key");
  check(g_trace.adopt_key[1][0] == 0U, "the key page adopts the page key");
  check(g_trace.commit_calls == 1U, "only the channel page is registered");
  check(g_trace.member_calls == 1U, "the channel is asked about the key slot");
  check(g_trace.insert_calls == 1U, "a missing member triggers one insert");
  check(g_trace.evict_calls == 1U, "a clear gate flag rejects the key slot");
  check(g_trace.release_calls == 3U, "both slots and the page are released");
  check(g_trace.release_property == 2U, "the owner and the property are freed");
}

void test_module_tally_reject() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  std::vector<std::uint32_t> span(1, 0U);
  g_arena.reset();
  OpaquePageB *by_key = make_page_b();
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 1;
  g_trace.load_result = true;
  g_trace.lookup_result[0] = by_key;
  set_gate(1U);
  by_key->host.field0c.begin = span.data();
  by_key->host.field0c.end = span.data() + 1;
  g_trace.tally_value = 7;
  g_trace.tally_seed = 3;
  unresolved_005c6010(&support, &source);
  check(g_trace.tally_calls == 1U, "a live span reaches the tally");
  check(g_trace.evict_calls == 1U, "a changed tally rejects the slot");
  check(g_trace.evict_self == reinterpret_cast<std::uint32_t>(by_key),
        "the rejected receiver is the key slot");
  check(g_trace.evict_arg != 0U, "the eviction carries the loaded page");
  set_gate(0U);
}

void test_module_span_mask() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  std::vector<std::uint32_t> span(1, 0U);
  g_arena.reset();
  OpaquePageB *by_key = make_page_b();
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 1;
  g_trace.load_result = true;
  g_trace.lookup_result[0] = by_key;
  set_gate(1U);
  by_key->host.field0c.begin = span.data();
  by_key->host.field0c.end = span.data() + 1;
  unresolved_005c6010(&support, &source);
  check(g_trace.tally_calls == 1U, "a four byte span passes the mask");
  check(g_trace.evict_calls == 0U, "an unchanged tally keeps the slot");
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 1;
  g_trace.load_result = true;
  g_trace.lookup_result[0] = by_key;
  set_gate(1U);
  by_key->host.field0c.end = span.data();
  unresolved_005c6010(&support, &source);
  check(g_trace.evict_calls == 1U, "a short span fails the mask");
  check(g_trace.tally_calls == 0U, "a short span short circuits the tally");
  set_gate(0U);
}

void test_module_gate_flag() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  std::vector<std::uint32_t> span(1, 0U);
  g_arena.reset();
  OpaquePageB *by_key = make_page_b();
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 1;
  g_trace.load_result = true;
  g_trace.lookup_result[0] = by_key;
  set_gate(0U);
  by_key->host.field0c.begin = span.data();
  by_key->host.field0c.end = span.data() + 1;
  unresolved_005c6010(&support, &source);
  check(g_trace.evict_calls == 1U, "a clear gate flag rejects the slot");
  check(g_trace.tally_calls == 0U, "a clear flag short circuits the tally");
  set_gate(0U);
}

void test_module_alloc_failure() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  g_arena.reset();
  g_arena.deny_from = 0U;
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 1;
  g_trace.load_result = false;
  unresolved_005c6010(&support, &source);
  check(g_trace.load_calls == 1U, "a denied page still reaches the loader");
  check(g_trace.retain_calls == 0U, "a denied page is never retained");
  check(g_trace.release_calls == 0U, "a denied page is not released");
  check(g_trace.release_property == 1U, "the property is still released");
  g_arena.deny_from = 0xffffffffU;
}

void test_module_two_entries() {
  OpaqueSupport support{};
  OpaqueResourceEntry source{1U, 2U, 3U};
  g_arena.reset();
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.array_count = 2;
  g_trace.entry0[0] = 0x50U;
  g_trace.entry1[0] = 0x51U;
  g_trace.load_result = false;
  unresolved_005c6010(&support, &source);
  check(g_trace.load_calls == 2U, "two array entries drive two page loads");
  check(g_trace.load_first_arg0 == 0x50U, "the first entry is loaded first");
  check(g_trace.release_calls == 2U, "each failed page is released once");
}

void test_prop_missing() {
  OpaqueSupport support{};
  OpaqueResourceKey ref{};
  g_trace.reset();
  g_trace.resolve_out = nullptr;
  const bool result = unresolved_005c6340(&support, &ref, 0x11U, 0x22U, 0x33U,
                                          0x44U, 0x55U, 0x66U);
  check(!result, "a missing property reports the byte sized false");
  check(support.field3c == 0x11U, "the back link is stored before resolving");
  check(g_trace.query_calls == 0U, "a missing property skips the probe");
  check(g_trace.filter_calls == 0U, "a missing property skips the registry");
  check(g_trace.release_property == 0U, "a missing property is not released");
}

void test_prop_state_writes() {
  OpaqueSupport support{};
  OpaqueResourceKey ref{};
  OpaqueResourceEntry items[2]{};
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.query_result = true;
  g_trace.group_out = 0x5a5aU;
  g_trace.filter_begin = items;
  g_trace.filter_end = items + 2;
  ref.field00 = 0x00000041U;
  ref.field08 = 0x77U;
  ref.field12 = 9U;
  items[0].field00 = 0xa0U;
  items[0].field08 = 1U;
  items[1].field00 = 0xa1U;
  items[1].field08 = 0U;
  const bool result = unresolved_005c6340(&support, &ref, 0x11U, 0x22U, 0x33U,
                                          0x44U, 0x55U, 0x66U);
  check(result, "a resolved property reports the byte sized true");
  check(g_trace.query_arg1 == 0x0332b28bU, "the probe id is stable");
  check(g_trace.query_field00 == 0x41U, "the probe receives the word zero");
  check(g_trace.query_field08 == 0x77U, "the probe receives the word two");
  check(support.field38 == 0x00c0ffeeU, "the probe stamp lands in field38");
  check(g_trace.probe_calls == 1U, "the probe slot runs once");
  check(support.field30 == 0x5a5aU, "the group id lands in field30");
  check(g_trace.group_id == 0x02233661U, "the group id is stable");
  check(support.field34 == 0x33U, "the key word zero lands in field34");
  check(support.field20 == 0x44U, "a non zero instance word lands in field20");
  check(g_trace.instance_calls == 0U, "a supplied instance skips the query");
  check(support.field24 == 0x44U, "the instance word also lands in field24");
  check(support.field28 == 0x55U, "the key word one lands in field28");
  check(support.field2c == 0x66U, "the key word two lands in field2c");
  check(g_trace.filter_calls == 1U, "the registry is consulted once");
  check(g_trace.filter_arg3 == 0U, "the registry receives a zero fourth word");
  check(g_trace.filter_context[0] == 0U, "the registry context starts clear");
  check(g_trace.filter_context[1] == 0U, "the context second word is clear");
  check(g_trace.filter_context[2] == 0U, "the context third word is clear");
  check(g_trace.filter_slot[0] == 0x013eb898U, "the slot head token is stable");
  check(g_trace.filter_slot[1] == 0xffffffffU, "the slot head guard is stable");
  check(g_trace.filter_slot[2] == 0x406b6b41U,
        "the slot prefix takes one byte");
  check(g_trace.filter_slot[3] == 0x00b1b104U, "the slot tail token is stable");
  check(g_trace.filter_slot[4] == 0xffffffffU, "the slot tail guard is stable");
  check(g_trace.free_calls == 0U, "a zero sentinel group blocks the release");
}

void test_prop_instance_fallback() {
  OpaqueSupport support{};
  OpaqueResourceKey ref{};
  OpaqueResourceEntry items[1]{};
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.query_result = false;
  g_trace.instance_out = 0x7e7eU;
  g_trace.filter_begin = items;
  g_trace.filter_end = items + 1;
  items[0].field08 = 0x42U;
  const bool result =
      unresolved_005c6340(&support, &ref, 0U, 0U, 0U, 0U, 0U, 0U);
  check(result, "the fallback path still reports true");
  check(g_trace.probe_calls == 0U, "a failed probe skips the stamp");
  check(support.field38 == 0U, "a failed probe leaves field38 clear");
  check(g_trace.instance_calls == 1U, "a zero instance word queries once");
  check(g_trace.instance_id == 0xc46ec042U, "the instance id is stable");
  check(support.field20 == 0x7e7eU, "the queried instance lands in field20");
  check(g_trace.free_calls == 1U,
        "a non zero sentinel group releases the list");
  check(g_trace.free_arg == reinterpret_cast<std::uint32_t>(items + 1),
        "the list end pointer is released");
}

void test_prop_walk() {
  OpaqueSupport support{};
  OpaqueResourceKey ref{};
  OpaqueResourceEntry items[3]{};
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.resolve_out2 = &g_property;
  g_trace.filter_begin = items;
  g_trace.filter_end = items + 3;
  check(unresolved_005c6340(&support, &ref, 0U, 0U, 0U, 0U, 0U, 0U),
        "a three element walk reports true");
  check(g_trace.resolve_calls == 4U, "the walk resolves once per element");
  check(g_trace.array_calls == 3U, "each element drives one array query");
  check(g_trace.release_property == 4U, "each element releases the property");
  check(g_trace.key_calls == 0U, "an empty array never adopts an owner");
  g_trace.reset();
  g_trace.resolve_out = &g_property;
  g_trace.filter_begin = items;
  g_trace.filter_end = items;
  check(unresolved_005c6340(&support, &ref, 0U, 0U, 0U, 0U, 0U, 0U),
        "an empty walk reports true");
  check(g_trace.resolve_calls == 1U, "an empty walk resolves only the head");
  check(g_trace.array_calls == 0U, "an empty walk queries no array");
}

}

extern "C" void *PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c7f00(OpaqueVectorHost *self, std::uint32_t index) {
  std::uint32_t *base = self->field70.begin;
  return reinterpret_cast<void *>(base[index]);
}

extern "C" OpaqueEntryB *PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c1ce0(OpaqueVectorHost *self, std::uint32_t index) {
  const std::int32_t span = static_cast<std::int32_t>(
      reinterpret_cast<const std::uint8_t *>(self->field0c.end) -
      reinterpret_cast<const std::uint8_t *>(self->field0c.begin));
  if (static_cast<std::int32_t>(index) < 0 ||
      static_cast<std::int32_t>(index) >= (span >> 2)) {
    return nullptr;
  }
  return reinterpret_cast<OpaqueEntryB *>(self->field0c.begin[index]);
}

extern "C" bool PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c6810(OpaqueEntryA *self, const OpaqueResourceEntry *key,
                    std::int32_t arg2, std::uint32_t arg3) {
  g_trace.rekey_calls += 1U;
  if (g_trace.rekey_calls == 1U) {
    g_trace.rekey_first_field20 = self->field20;
    g_trace.rekey_first_key[0] = key->field00;
    g_trace.rekey_first_key[1] = key->field04;
    g_trace.rekey_first_key[2] = key->field08;
  }
  g_trace.rekey_key[0] = key->field00;
  g_trace.rekey_key[1] = key->field04;
  g_trace.rekey_key[2] = key->field08;
  g_trace.rekey_arg2 = arg2;
  g_trace.rekey_field20 = self->field20;
  self->key = *key;
  self->field18 = key->field00;
  self->field1c = key->field04;
  self->field48 = static_cast<std::uint32_t>(arg2);
  if (arg3 != 0U) {
    self->field20 = arg3;
  }
  return self->field24 != 0xffffffffU;
}

extern "C" std::int32_t PKG_PALETTE_SUPPORT_THISCALL unresolved_005c5c50(
    OpaqueSupport *self, OpaquePageA *owner, std::uint32_t *out) {
  (void)self;
  (void)owner;
  g_trace.tally_calls += 1U;
  g_trace.tally_out = g_trace.tally_seed;
  *out = g_trace.tally_out;
  return g_trace.tally_value;
}

extern "C" OpaqueEntryB *PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c5df0(OpaqueVectorHost *container, std::uint32_t key) {
  (void)container;
  g_trace.lookup_calls += 1U;
  g_trace.lookup_key = key;
  const std::uint32_t slot = g_trace.lookup_calls - 1U;
  if (slot >= 4U) {
    return nullptr;
  }
  return reinterpret_cast<OpaqueEntryB *>(g_trace.lookup_result[slot]);
}

extern "C" void PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c5f00(OpaqueProperty *self, OpaquePageB *arg) {
  (void)self;
  g_trace.commit_calls += 1U;
  g_trace.commit_arg = reinterpret_cast<std::uint32_t>(arg);
}

extern "C" bool PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c1d40(OpaquePageB *self, OpaquePageB *arg) {
  (void)self;
  g_trace.member_calls += 1U;
  g_trace.member_arg = reinterpret_cast<std::uint32_t>(arg);
  return g_trace.member_result;
}

extern "C" void PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c22b0(OpaquePageB *self, OpaquePageB *arg) {
  (void)self;
  g_trace.insert_calls += 1U;
  g_trace.insert_arg = reinterpret_cast<std::uint32_t>(arg);
}

extern "C" void PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c2390(OpaquePageB *self, OpaqueNode *arg) {
  (void)self;
  g_trace.evict_calls += 1U;
  g_trace.evict_arg = reinterpret_cast<std::uint32_t>(arg);
  g_trace.evict_self = reinterpret_cast<std::uint32_t>(self);
}

extern "C" bool PKG_PALETTE_SUPPORT_THISCALL unresolved_005c8ad0(
    OpaquePageA *self, OpaqueResourceEntry *element, std::uint32_t arg2,
    std::uint32_t arg3, std::uint32_t arg4, std::uint32_t arg5) {
  (void)self;
  g_trace.load_calls += 1U;
  if (g_trace.load_calls == 1U) {
    g_trace.load_first_arg0 = element->field00;
  }
  g_trace.load_arg0 = element->field00;
  g_trace.load_arg1 = arg2;
  g_trace.load_arg2 = arg3;
  g_trace.load_arg3 = arg4;
  g_trace.load_arg4 = arg5;
  return g_trace.load_result;
}

extern "C" OpaquePageA *PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c7f50(OpaquePageA *self) {
  self->host.vtable = &g_node_vtable;
  return self;
}

extern "C" OpaquePageB *PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c2020(OpaquePageB *self) {
  self->host.vtable = &g_node_vtable;
  return self;
}

extern "C" void PKG_PALETTE_SUPPORT_THISCALL unresolved_005c1e20(
    OpaquePageB *self, const OpaqueResourceEntry *key, std::uint32_t arg2) {
  (void)self;
  const std::uint32_t slot = g_trace.adopt_calls;
  g_trace.adopt_calls += 1U;
  if (slot >= 4U) {
    return;
  }
  g_trace.adopt_arg[slot] = arg2;
  g_trace.adopt_key[slot][0] = key->field00;
  g_trace.adopt_key[slot][1] = key->field04;
  g_trace.adopt_key[slot][2] = key->field08;
}

extern "C" OpaqueService *PKG_PALETTE_SUPPORT_CDECL unresolved_0067de30() {
  return &g_service;
}

extern "C" OpaqueRegistry *PKG_PALETTE_SUPPORT_CDECL unresolved_008de1a0() {
  return &g_registry;
}

extern "C" void *PKG_PALETTE_SUPPORT_CDECL unresolved_00f473a0(
    std::uint32_t bytes, std::uint32_t tag, std::uint32_t arg2,
    std::uint32_t arg3, std::uint32_t arg4, std::uint32_t arg5) {
  (void)tag;
  (void)arg2;
  (void)arg3;
  (void)arg4;
  (void)arg5;
  return g_arena.take(bytes);
}

extern "C" void PKG_PALETTE_SUPPORT_CDECL unresolved_00f47380(void *block) {
  g_trace.free_calls += 1U;
  g_trace.free_arg = reinterpret_cast<std::uint32_t>(block);
}

extern "C" const std::uint32_t *PKG_PALETTE_SUPPORT_FASTCALL
unresolved_0041e990(const OpaqueResourceKey *self) {
  (void)self;
  g_trace.probe_calls += 1U;
  return &g_probe_storage;
}

extern "C" bool PKG_PALETTE_SUPPORT_CDECL
unresolved_006a0ae0(OpaqueProperty *self, std::uint32_t id, std::int32_t *count,
                    OpaqueResourceEntry *entries) {
  (void)self;
  g_trace.array_calls += 1U;
  g_trace.array_id = id;
  *count = g_trace.array_count;
  if (g_trace.array_count > 0) {
    entries[0].field00 = g_trace.entry0[0];
    entries[0].field04 = g_trace.entry0[1];
    entries[0].field08 = g_trace.entry0[2];
  }
  if (g_trace.array_count > 1) {
    entries[1].field00 = g_trace.entry1[0];
    entries[1].field04 = g_trace.entry1[1];
    entries[1].field08 = g_trace.entry1[2];
  }
  return true;
}

extern "C" bool PKG_PALETTE_SUPPORT_CDECL unresolved_006a1250(
    OpaqueProperty *self, std::uint32_t id, OpaqueResourceEntry *out) {
  (void)self;
  g_trace.key_calls += 1U;
  g_trace.key_id = id;
  out->field00 = g_trace.key_out[0];
  out->field04 = g_trace.key_out[1];
  out->field08 = g_trace.key_out[2];
  return true;
}

extern "C" bool PKG_PALETTE_SUPPORT_CDECL unresolved_006a12e0(
    OpaqueProperty *self, std::uint32_t id, std::uint32_t *out) {
  (void)self;
  g_trace.group_calls += 1U;
  g_trace.group_id = id;
  *out = g_trace.group_out;
  return true;
}

extern "C" bool PKG_PALETTE_SUPPORT_CDECL unresolved_006a12a0(
    OpaqueProperty *self, std::uint32_t id, std::uint32_t *out) {
  (void)self;
  g_trace.instance_calls += 1U;
  g_trace.instance_id = id;
  *out = g_trace.instance_out;
  return true;
}

}

namespace openspore::reconstruction::pkg_palette_support_wave10 {
namespace {

void run_all() {
  g_table_015fd918 = g_gate_link;
  test_match_empty();
  test_match_full();
  test_match_partial();
  test_match_negative_count();
  test_module_no_property();
  test_module_empty_array();
  test_module_load_failure();
  test_module_reuse();
  test_module_owner_path();
  test_module_build_channels();
  test_module_tally_reject();
  test_module_span_mask();
  test_module_gate_flag();
  test_module_alloc_failure();
  test_module_two_entries();
  test_prop_missing();
  test_prop_state_writes();
  test_prop_instance_fallback();
  test_prop_walk();
}

int report() {
  if (g_failures != 0) {
    std::printf("pkg-palette-support-wave10: %d failure(s)\n", g_failures);
    return 1;
  }
  std::printf("pkg-palette-support-wave10: all checks passed\n");
  return 0;
}

}
}

int main() {
  openspore::reconstruction::pkg_palette_support_wave10::run_all();
  return openspore::reconstruction::pkg_palette_support_wave10::report();
}
