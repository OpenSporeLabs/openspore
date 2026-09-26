#include "editor_wave10.hpp"

namespace openspore::reconstruction::pkg_editor_wave10 {
namespace {

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

struct CallLog {
  int query_key = 0;
  int release = 0;
  int apply = 0;
  int register_child = 0;
  int last_context = 0;
  int last_key = -1;
  Real last_scalar = 0.0f;
  int last_flag_primary = -1;
  int last_flag_secondary = -1;
  int last_child = 0;
  int released_child = 0;
  int registered_child = 0;
  int registered_host = 0;
  int queried_key = -1;
  int accept_result = 1;
  int clear_after_call = 0;
};

CallLog g_log{};

Word stub_query_key(void* owner) {
  ++g_log.query_key;
  g_log.queried_key = static_cast<int>(reinterpret_cast<std::uintptr_t>(owner));
  return static_cast<OpaqueRef*>(owner)->key_08;
}

Word stub_release(void* owner) {
  ++g_log.release;
  g_log.released_child =
      static_cast<int>(reinterpret_cast<std::uintptr_t>(owner));
  return 0;
}

Byte stub_apply_child(void* child, Word context, Word key, Real scalar,
                      Byte flag_primary, Byte flag_secondary) {
  ++g_log.apply;
  g_log.last_context = static_cast<int>(context);
  g_log.last_key = static_cast<int>(key);
  g_log.last_scalar = scalar;
  g_log.last_flag_primary = flag_primary;
  g_log.last_flag_secondary = flag_secondary;
  g_log.last_child = static_cast<int>(reinterpret_cast<std::uintptr_t>(child));
  if (g_log.clear_after_call != 0) {
    return 0;
  }
  return static_cast<Byte>(g_log.accept_result);
}

void stub_register_child(void* host, void* owner) {
  ++g_log.register_child;
  g_log.registered_child =
      static_cast<int>(reinterpret_cast<std::uintptr_t>(owner));
  g_log.registered_host =
      static_cast<int>(reinterpret_cast<std::uintptr_t>(host));
}

void install_host_hooks() {
  g_model_host_hooks.query_key_00 = stub_query_key;
  g_model_host_hooks.release_04 = stub_release;
  g_model_host_hooks.apply_child_08 = stub_apply_child;
  g_model_host_hooks.register_child_0c = stub_register_child;
}

void test_row_publish_writes_next_only() {
  OpaqueVec3Publisher publisher{};
  publisher.row_prev_74 = 1;
  publisher.row_prev_78 = 2;
  publisher.row_prev_7c = 3;
  editor_row_publish_005a2010(&publisher, 0x11111111u, 0x22222222u, 0x33333333u,
                              0);
  check(publisher.row_next_80 == 0x11111111u);
  check(publisher.row_next_84 == 0x22222222u);
  check(publisher.row_next_88 == 0x33333333u);
  check(publisher.row_prev_74 == 1);
  check(publisher.row_prev_78 == 2);
  check(publisher.row_prev_7c == 3);
}

void test_row_publish_writes_both_rows() {
  OpaqueVec3Publisher publisher{};
  editor_row_publish_005a2010(&publisher, 7u, 8u, 9u, 1);
  check(publisher.row_next_80 == 7u);
  check(publisher.row_next_84 == 8u);
  check(publisher.row_next_88 == 9u);
  check(publisher.row_prev_74 == 7u);
  check(publisher.row_prev_78 == 8u);
  check(publisher.row_prev_7c == 9u);
}

void test_apply_children_ownership_swap_order() {
  install_host_hooks();
  g_log = CallLog{};

  OpaqueRef previous{};
  previous.key_08 = 0xaaaa;
  OpaqueRef next{};
  next.key_08 = 0xbbbb;

  OpaqueModelHost host{};
  host.owner_30 = &previous;

  Word slots[2] = {1, 2};
  host.child_base_18 = slots;
  host.child_end_1c = slots + 2;
  host.scalar_38 = 2.5f;

  const Word result =
      editor_model_apply_children_004ae260(&host, 0x1234u, &next, 1, 1);

  check(result == 1u);
  check(host.owner_30 == &next);
  check(next.refcount_04 == 1u);
  check(previous.refcount_04 == 0u);
  check(g_log.release == 1);
  check(g_log.released_child ==
        static_cast<int>(reinterpret_cast<std::uintptr_t>(&previous)));
  check(g_log.query_key == 1);
  check(g_log.apply == 2);
  check(g_log.last_context == 0x1234);
  check(g_log.last_key == 0xbbbb);
  check(g_log.queried_key ==
        static_cast<int>(reinterpret_cast<std::uintptr_t>(&next)));
  check(g_log.last_scalar == 2.5f);
  check(g_log.last_flag_primary == 1);
  check(g_log.last_flag_secondary == 1);
  check(g_log.last_child == 2);
  check(g_log.register_child == 1);
  check(g_log.registered_child ==
        static_cast<int>(reinterpret_cast<std::uintptr_t>(&next)));
  check(g_log.registered_host ==
        static_cast<int>(reinterpret_cast<std::uintptr_t>(&host)));
}

void test_apply_children_no_release_when_owner_unchanged() {
  install_host_hooks();
  g_log = CallLog{};

  OpaqueRef owner{};
  owner.refcount_04 = 4;
  OpaqueModelHost host{};
  host.owner_30 = &owner;

  const Word result =
      editor_model_apply_children_004ae260(&host, 0u, &owner, 0, 0);
  check(result == 1u);
  check(owner.refcount_04 == 4u);
  check(g_log.release == 0);
  check(g_log.apply == 0);
  check(g_log.register_child == 1);
}

void test_apply_children_null_owner_skips_key_and_register() {
  install_host_hooks();
  g_log = CallLog{};

  OpaqueModelHost host{};
  Word slots[3] = {11, 12, 13};
  host.child_base_18 = slots;
  host.child_end_1c = slots + 3;

  const Word result =
      editor_model_apply_children_004ae260(&host, 5u, nullptr, 0, 0);
  check(result == 1u);
  check(host.owner_30 == nullptr);
  check(g_log.query_key == 0);
  check(g_log.register_child == 0);
  check(g_log.apply == 3);
  check(g_log.last_key == 0);
  check(g_log.last_context == 5);
  check(g_log.last_child == 13);
}

void test_apply_children_flag_accumulates_and_uses_and_semantics() {
  install_host_hooks();
  g_log = CallLog{};

  OpaqueModelHost host{};
  Word slots[3] = {1, 2, 3};
  host.child_base_18 = slots;
  host.child_end_1c = slots + 3;
  host.accept_flag_2c = 0;

  g_log.accept_result = 1;
  const Word result =
      editor_model_apply_children_004ae260(&host, 0u, nullptr, 0, 0);
  check(result == 1u);
  check(host.accept_flag_2c == 1);

  host.accept_flag_2c = 0;
  g_log.accept_result = 0;
  editor_model_apply_children_004ae260(&host, 0u, nullptr, 0, 0);
  check(host.accept_flag_2c == 0);
}

void test_apply_children_flag_read_after_call() {
  install_host_hooks();
  g_log = CallLog{};

  OpaqueModelHost host{};
  Word slots[1] = {1};
  host.child_base_18 = slots;
  host.child_end_1c = slots + 1;

  g_log.accept_result = 1;
  g_log.clear_after_call = 0;
  editor_model_apply_children_004ae260(&host, 0u, nullptr, 0, 0);
  check(host.accept_flag_2c == 1);

  g_log.clear_after_call = 1;
  editor_model_apply_children_004ae260(&host, 0u, nullptr, 0, 0);
  check(host.accept_flag_2c == 0);
}

struct ArenaFixture {
  std::uint8_t storage[0x200];
  OpaqueArena arena;
  Word* base;
  Word* sentinel;
  Word* end;
};

void arena_init(ArenaFixture& fixture, Word flags) {
  fixture.base = reinterpret_cast<Word*>(fixture.storage);
  fixture.sentinel = fixture.base + 6;
  fixture.end = fixture.base + 0x40;
  for (std::size_t i = 0; i < sizeof(fixture.storage) / 4; ++i) {
    fixture.base[i] = 0;
  }
  fixture.arena = OpaqueArena{};
  fixture.arena.base_00 = reinterpret_cast<std::uint8_t*>(fixture.base);
  fixture.arena.base_offset_04 = 0x100u;
  fixture.arena.used_08 = 0u;
  fixture.arena.freelist_0c = fixture.sentinel;
  fixture.arena.flags_10 = flags;
  fixture.sentinel[0] = 0u;
  fixture.base[0x3f] = 0u;
}

Word fallback_small_calls = 0;
Word fallback_large_calls = 0;
Word fallback_last_need = 0;
Word fallback_last_align = 0;

Word stub_fallback_00(void*, Word need) {
  ++fallback_small_calls;
  fallback_last_need = need;
  fallback_last_align = 0;
  return 0xdeadbeefu;
}

Word stub_fallback_04(void*, Word need, Word align) {
  ++fallback_large_calls;
  fallback_last_need = need;
  fallback_last_align = align;
  return 0xcafebabeu;
}

void install_arena_hooks() {
  g_arena_hooks.fallback_00 = stub_fallback_00;
  g_arena_hooks.fallback_04 = stub_fallback_04;
}

void test_arena_small_request_returns_sentinel() {
  install_arena_hooks();
  fallback_small_calls = 0;
  fallback_large_calls = 0;

  ArenaFixture fixture{};
  arena_init(fixture, 0u);
  fixture.arena.used_08 = 0x20u;
  const Word result = arena_release_block_004bfc40(&fixture.arena, 0u, 4u);
  check(result == reinterpret_cast<std::uintptr_t>(fixture.sentinel));
  check(fallback_small_calls == 0);
  check(fallback_large_calls == 0);
}

void test_arena_out_of_arena_falls_back_by_alignment() {
  install_arena_hooks();
  fallback_small_calls = 0;
  fallback_large_calls = 0;

  ArenaFixture fixture{};
  arena_init(fixture, 0u);
  fixture.arena.used_08 = 0u;

  const Word small = arena_release_block_004bfc40(&fixture.arena, 64u, 4u);
  check(small == 0xdeadbeefu);
  check(fallback_small_calls == 1);
  check(fallback_last_need == 72u);
  check(fallback_last_align == 0);

  const Word large = arena_release_block_004bfc40(&fixture.arena, 64u, 16u);
  check(large == 0xcafebabeu);
  check(fallback_large_calls == 1);
  check(fallback_last_need == 72u);
  check(fallback_last_align == 16u);

  ArenaFixture none{};
  arena_init(none, 0u);
  none.arena.base_00 = nullptr;
  const Word detached = arena_release_block_004bfc40(&none.arena, 64u, 4u);
  check(detached == 0xdeadbeefu);
  check(fallback_small_calls == 2);
}

void test_arena_footer_alignment_adds_four() {
  install_arena_hooks();
  fallback_small_calls = 0;

  ArenaFixture plain{};
  arena_init(plain, 0u);
  plain.arena.used_08 = 0u;
  arena_release_block_004bfc40(&plain.arena, 64u, 4u);
  check(fallback_last_need == 72u);

  ArenaFixture footed{};
  arena_init(footed, 0x40000000u);
  footed.arena.used_08 = 0u;
  arena_release_block_004bfc40(&footed.arena, 64u, 4u);
  check(fallback_last_need == 76u);
}

void test_arena_split_marks_in_use_and_updates_used() {
  install_arena_hooks();
  fallback_small_calls = 0;
  fallback_large_calls = 0;

  ArenaFixture fixture{};
  arena_init(fixture, 0u);

  Word* const block = fixture.sentinel;
  block[0] = 0x200u;
  fixture.arena.used_08 = 0x200u;
  fixture.arena.freelist_0c = block;

  const Word payload = arena_release_block_004bfc40(&fixture.arena, 0x40u, 4u);
  check(fallback_small_calls == 0);
  check(payload != 0u);

  Word* const header =
      reinterpret_cast<Word*>(static_cast<std::uintptr_t>(payload) - 8u);
  check((header[0] & 0x80000000u) != 0u);
  check((header[0] & 0x3fffffffu) == 0x48u);
  check((header[0] & 0xc0000000u) == 0x80000000u);
  check(fixture.arena.used_08 == 0x1b8u);
  check(fixture.arena.freelist_0c ==
        reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(header) +
                                0x48u));
  check(fixture.sentinel[0] == 0x80000048u);
  check(reinterpret_cast<Word*>(
            reinterpret_cast<std::uintptr_t>(fixture.sentinel) + 0x48u)[0] ==
        0x1b8u);
}

void test_arena_no_split_when_remainder_too_small() {
  install_arena_hooks();
  fallback_small_calls = 0;

  ArenaFixture fixture{};
  arena_init(fixture, 0u);

  Word* const block = fixture.sentinel;
  block[0] = 0x60u;
  fixture.arena.used_08 = 0x60u;
  fixture.arena.base_offset_04 = 0x68u;
  fixture.arena.freelist_0c = block;

  const Word payload = arena_release_block_004bfc40(&fixture.arena, 0x40u, 4u);
  check(fallback_small_calls == 0);
  check(payload != 0u);
  Word* const header =
      reinterpret_cast<Word*>(static_cast<std::uintptr_t>(payload) - 8u);
  check((header[0] & 0x3fffffffu) == 0x60u);
  check((header[0] & 0x80000000u) != 0u);
}

void test_arena_footer_mode_stores_owner_and_flags() {
  install_arena_hooks();
  fallback_small_calls = 0;

  ArenaFixture fixture{};
  arena_init(fixture, 0x40000000u);

  Word* const block = fixture.sentinel;
  block[0] = 0x200u;
  fixture.arena.used_08 = 0x200u;
  fixture.arena.freelist_0c = block;

  const Word payload = arena_release_block_004bfc40(&fixture.arena, 0x40u, 4u);
  check(fallback_small_calls == 0);
  check(payload != 0u);
  Word* const header =
      reinterpret_cast<Word*>(static_cast<std::uintptr_t>(payload) - 8u);
  check((header[0] & 0xc0000000u) == 0xc0000000u);
  void** const owner_slot = reinterpret_cast<void**>(
      static_cast<std::uintptr_t>(payload) - 0x0cu + (header[0] & 0x3fffffffu));
  check(*owner_slot == static_cast<void*>(&fixture.arena));
}

void test_arena_scans_past_in_use_blocks() {
  install_arena_hooks();
  fallback_small_calls = 0;

  ArenaFixture fixture{};
  arena_init(fixture, 0u);

  Word* const used = fixture.sentinel;
  Word* const free_block =
      reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(used) + 0x10u);
  used[0] = 0x80000010u;
  used[1] = 0u;
  free_block[0] = 0x100u;
  free_block[1] = 0u;
  fixture.arena.used_08 = 0x110u;
  fixture.arena.freelist_0c = used;

  const Word payload = arena_release_block_004bfc40(&fixture.arena, 0x40u, 4u);
  check(fallback_small_calls == 0);
  check(payload != 0u);
  Word* const header =
      reinterpret_cast<Word*>(static_cast<std::uintptr_t>(payload) - 8u);
  check((header[0] & 0x3fffffffu) == 0x48u);
  check(fixture.arena.used_08 == 0xc8u);
  check(used[0] == 0x80000010u);
}

struct ModelLog {
  int source_queries = 0;
  int index_queries = 0;
  int singleton_lookups = 0;
  int singleton_calls = 0;
  int slot_lookups = 0;
  int slot_discards = 0;
  int mode_initializes = 0;
  int mode_releases = 0;
  int mode_fetches = 0;
  int name_queries = 0;
  int child_finishes = 0;
  int bridges = 0;
  int clears = 0;
  int prepares = 0;
  int finishes = 0;
  int publishes = 0;
  int payloads = 0;
  int factories = 0;
  int seeds = 0;
  Word seed_values[8]{};
  int composes = 0;
  int range_appends = 0;
  int acquires = 0;
  int releases = 0;
  Word init_tag = 0;
  Word init_arg = 0;
  Word fetch_result = 1;
  Word tag_value = 0x777u;
  Word range_a_count = 0;
  Word range_b_count = 0;
  Word last_seed = 0;
};

ModelLog g_mlog{};
OpaqueModelSource g_source{};
OpaqueModelRootVtable g_root_vtable{};
int g_named_applies = 0;
int g_tag_applies = 0;
Word g_tag_arg = 0;
OpaqueChildInstance g_instances[4];
OpaqueChildNode g_nodes[8];
std::int32_t g_index_result = -1;
Half g_name_text[4] = {0x0041, 0x0000, 0x0000, 0x0000};

void stub_root_named(void*) { ++g_named_applies; }

void stub_root_slot(void*) {}

void stub_root_tag(Word arg) {
  ++g_tag_applies;
  g_tag_arg = arg;
}

void stub_source_query(void*, void*, void** out) {
  ++g_mlog.source_queries;
  *out = g_mlog.source_queries == 0 ? nullptr : &g_source;
}

std::int32_t stub_index_query(void*, Word) {
  ++g_mlog.index_queries;
  return g_index_result;
}

void* stub_singleton_00(void*) {
  ++g_mlog.singleton_lookups;
  return reinterpret_cast<void*>(0x1000u);
}

Word stub_singleton_04(void*) { return 0x2000u; }

void stub_singleton_08(void*, Word, Word, Word) { ++g_mlog.singleton_calls; }

void stub_slot_lookup(void** out, Word, Word* slot) {
  ++g_mlog.slot_lookups;
  *out = nullptr;
  *slot = 0xabcdu;
}

void stub_slot_discard(void*) { ++g_mlog.slot_discards; }

void* stub_mode_manager(void) { return reinterpret_cast<void*>(0x3000u); }

bool stub_mode_initialize(void*, OpaqueModeManagerInit* init) {
  ++g_mlog.mode_initializes;
  g_mlog.init_tag = init->tag_04;
  g_mlog.init_arg = init->arg_08;
  return true;
}

void stub_mode_release(void*) { ++g_mlog.mode_releases; }

Word stub_mode_fetch(void*, void** slot) {
  ++g_mlog.mode_fetches;
  *slot = reinterpret_cast<void*>(0x4000u);
  return g_mlog.fetch_result;
}

OpaqueWideName* stub_name_query(void*) {
  ++g_mlog.name_queries;
  static OpaqueWideName name{};
  name.text = g_name_text;
  return &name;
}

Word stub_tag_query(void*) { return g_mlog.tag_value; }

void stub_child_finish(Word*, Word*) { ++g_mlog.child_finishes; }

void stub_bridge(void**) { ++g_mlog.bridges; }

void stub_clear(Word) { ++g_mlog.clears; }

void stub_prepare(void*) { ++g_mlog.prepares; }

void stub_finish(void) { ++g_mlog.finishes; }

void stub_publish(void) { ++g_mlog.publishes; }

void stub_payload(Word, Word) { ++g_mlog.payloads; }

int g_factory_next = 0;

void* stub_factory(Word, const char*) {
  ++g_mlog.factories;
  void* p = static_cast<void*>(&g_instances[g_factory_next]);
  g_factory_next = (g_factory_next + 1) % 4;
  return p;
}

void* stub_construct(void* handle) { return handle; }

void stub_seed(Word value) {
  if (g_mlog.seeds < 8) {
    g_mlog.seed_values[g_mlog.seeds] = value;
  }
  ++g_mlog.seeds;
  g_mlog.last_seed = value;
}

void stub_acquire(void*) { ++g_mlog.acquires; }

void stub_release_ref(void*) { ++g_mlog.releases; }

void stub_range_append(OpaqueRange* range, const Word*, const Word*) {
  ++g_mlog.range_appends;
  if (range == reinterpret_cast<OpaqueRange*>(g_source.records_98->range_a)) {
    ++g_mlog.range_a_count;
  } else {
    ++g_mlog.range_b_count;
  }
}

void stub_compose(Word* out, const Word* a, const Word* b) {
  ++g_mlog.composes;
  for (Word i = 0; i < 9; ++i) {
    out[i] = a[i] + b[i];
  }
}

OpaqueChildNode* stub_entry_lookup(void*, Word index) {
  return &g_nodes[index];
}

void install_model_hooks() {
  g_model_hooks.source_query_6c = stub_source_query;
  g_model_hooks.index_query_2c = stub_index_query;
  g_model_hooks.singleton_00 = stub_singleton_00;
  g_model_hooks.singleton_04 = stub_singleton_04;
  g_model_hooks.singleton_08 = stub_singleton_08;
  g_model_hooks.slot_lookup_0c = stub_slot_lookup;
  g_model_hooks.slot_discard_10 = stub_slot_discard;
  g_model_hooks.mode_manager_14 = stub_mode_manager;
  g_model_hooks.mode_initialize_18 = stub_mode_initialize;
  g_model_hooks.mode_release_1c = stub_mode_release;
  g_model_hooks.mode_fetch_20 = stub_mode_fetch;
  g_model_hooks.name_query_24 = stub_name_query;
  g_model_hooks.tag_query_28 = stub_tag_query;
  g_model_hooks.child_finish_30 = stub_child_finish;
  g_model_hooks.child_bridge_2c = stub_bridge;
  g_model_hooks.stage_clear_34 = stub_clear;
  g_model_hooks.stage_prepare_38 = stub_prepare;
  g_model_hooks.stage_finish_3c = stub_finish;
  g_model_hooks.stage_publish_5c = stub_publish;
  g_model_hooks.stage_payload_40 = stub_payload;
  g_model_hooks.child_factory_44 = stub_factory;
  g_model_hooks.child_construct_48 = stub_construct;
  g_model_hooks.child_seed_4c = stub_seed;
  g_model_hooks.ref_acquire_50 = stub_acquire;
  g_model_hooks.ref_release_58 = stub_release_ref;
  g_model_hooks.range_append_60 = stub_range_append;
  g_model_hooks.matrix_compose_64 = stub_compose;
  g_model_hooks.entry_lookup_68 = stub_entry_lookup;
  g_model_hooks.compare_name = g_name_text;
}

void model_setup(Word record_count) {
  install_model_hooks();
  g_mlog = ModelLog{};
  g_named_applies = 0;
  g_tag_applies = 0;
  g_tag_arg = 0;
  g_index_result = -1;
  g_mlog.fetch_result = 1;
  g_factory_next = 0;
  g_root_vtable = OpaqueModelRootVtable{};
  g_root_vtable.apply_named_00 = stub_root_named;
  g_root_vtable.apply_slot_04 = stub_root_slot;
  g_root_vtable.apply_tag_08 = stub_root_tag;

  static OpaqueChildEntryRecord records[4];
  for (std::size_t i = 0; i < sizeof(records) / sizeof(records[0]); ++i) {
    records[i] = OpaqueChildEntryRecord{};
  }
  g_source = OpaqueModelSource{};
  g_source.manager_08 = 0x6000u;
  g_source.init_arg_0c = 0x7000u;
  g_source.init_arg_10 = 0x8000u;
  for (Word i = 0; i < 17; ++i) {
    g_source.axes_18[i] = 0x100u + i;
  }
  g_source.records_98 = records;
  g_source.records_end_9c = records + record_count;

  for (std::size_t i = 0; i < 4; ++i) {
    g_instances[i] = OpaqueChildInstance{};
  }
  for (std::size_t i = 0; i < 8; ++i) {
    g_nodes[i] = OpaqueChildNode{};
  }
}

OpaqueModelRoot* make_root() {
  static OpaqueModelRoot root;
  root = OpaqueModelRoot{};
  root.vtable_00 = &g_root_vtable;
  static std::uintptr_t slots[4];
  for (std::size_t i = 0; i < 4; ++i) {
    slots[i] = 0;
  }
  root.child_base_18 = slots;
  root.child_end_1c = slots + 4;
  return &root;
}

void test_model_null_source_returns_zero() {
  model_setup(1);
  g_mlog.source_queries = -1;
  OpaqueModelRoot* root = make_root();
  const Byte result = editor_model_load_004ae3b0(root, nullptr);
  check(result == 0);
  check(root->root_handle_54 == 0);
  check(g_mlog.index_queries == 0);
  check(g_mlog.mode_initializes == 0);
  g_mlog.source_queries = 0;
}

void test_model_axes_and_bounds_publication() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  const Byte result = editor_model_load_004ae3b0(root, nullptr);
  check(result == 1);
  check(root->parent_58 == 0x100u);
  check(root->trailing_dc == 0x101u);
  check(root->group_8c[0] == 0x102u);
  check(root->group_8c[1] == 0x103u);
  check(root->group_8c[2] == 0x104u);
  check(root->group_98[0] == 0x105u);
  check(root->group_98[1] == 0x106u);
  check(root->group_98[2] == 0x107u);
  check(root->axes_a4[0] == 0x108u);
  check(root->axes_a4[1] == 0x109u);
  check(root->axes_a4[2] == 0x10au);
  check(root->axes_b0[0] == 0x10bu);
  check(root->axes_bc[0] == 0x10eu);
  check(root->bound_0c == 0x6000u);
  check(root->bound_10 == 0x7000u);
  check(root->bound_14 == 0x8000u);
  check(g_mlog.init_tag == 0x030bdee3u);
  check(g_mlog.init_arg == 0x8000u);
  check(g_mlog.mode_initializes == 1);
}

void test_model_select_mirror_normalization() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  root->select_5c = 3;
  root->mirror_60 = 9;
  root->select_6c = 4;
  root->mirror_70 = 4;
  root->select_7c = 5;
  root->mirror_80 = 6;
  editor_model_load_004ae3b0(root, nullptr);
  check(root->select_5c == 0);
  check(root->mirror_60 == 0);
  check(root->select_6c == 4);
  check(root->mirror_70 == 4);
  check(root->select_7c == 0);
  check(root->mirror_80 == 0);
}

void test_model_index_branch_order() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  g_index_result = 5;
  editor_model_load_004ae3b0(root, nullptr);
  check(g_mlog.index_queries == 1);
  check(g_mlog.singleton_lookups == 1);
  check(g_mlog.singleton_calls == 1);
  check(g_mlog.slot_lookups == 1);
  check(root->root_handle_54 == 0xabcdu);

  model_setup(1);
  root = make_root();
  g_index_result = -1;
  editor_model_load_004ae3b0(root, nullptr);
  check(g_mlog.index_queries == 1);
  check(g_mlog.singleton_lookups == 0);
  check(g_mlog.slot_lookups == 0);
}

void test_model_name_compare_gates_named_apply() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  static Half other[4] = {0x0042, 0x0000, 0x0000, 0x0000};
  g_model_hooks.compare_name = other;
  editor_model_load_004ae3b0(root, nullptr);
  check(g_named_applies == 1);
  check(g_tag_applies == 1);
  check(g_tag_arg == 0x777u);

  model_setup(1);
  root = make_root();
  g_model_hooks.compare_name = g_name_text;
  editor_model_load_004ae3b0(root, nullptr);
  check(g_named_applies == 0);
  check(g_tag_applies == 1);
}

void test_model_mode_fetch_zero_skips_name_queries() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  g_mlog.fetch_result = 0;
  editor_model_load_004ae3b0(root, nullptr);
  check(g_mlog.mode_fetches == 1);
  check(g_mlog.name_queries == 0);
  check(g_tag_applies == 0);
  check(g_mlog.slot_discards == 1);
}

void test_model_phase_call_order() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  editor_model_load_004ae3b0(root, nullptr);
  const Word expected[] = {
      kOpQuerySource,   kOpIndexQuery,     kOpModeInitialize, kOpModeFetch,
      kOpNameQuery,     kOpRootApplyNamed, kOpRootApplyTag,   kOpChildFinish,
      kOpCountClear,    kOpStagePrepare,   kOpStageFinish,    kOpStagePayload,
      kOpTableAlloc,    kOpRefAssign,      kOpTablePayload,   kOpStagePublish,
      kOpMatrixCompose, kOpRangeAppend,    kOpRangeAppend,    kOpModeRelease};
  const Word count = sizeof(expected) / sizeof(expected[0]);
  check(g_model_hooks.trace_count == count);
  for (Word i = 0; i < count && i < g_model_hooks.trace_count; ++i) {
    check(g_model_hooks.trace[i] == expected[i]);
  }
  check(g_mlog.clears == 1);
  check(g_mlog.prepares == 1);
  check(g_mlog.finishes == 1);
  check(g_mlog.payloads == 1);
  check(g_mlog.publishes == 1);
  check(g_mlog.child_finishes == 1);
  check(g_mlog.factories == 1);
}

void test_model_child_field_mutation() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  OpaqueChildEntryRecord* record = g_source.records_98;
  record->key_000 = 0x11u;
  record->value_004 = 0x22u;
  record->parent_index_008 = 0xffffffffu;
  record->alt_index_00c = 0xffffffffu;
  record->field_010 = 0x33u;
  record->field_014 = 0x44u;
  record->field_018 = 0x55u;
  record->field_01c = 0x66u;
  for (Word i = 0; i < 9; ++i) {
    record->block_a[i] = 0xa0u + i;
    record->block_b[i] = 0xb0u + i;
  }
  record->scalar_084 = 0x77u;
  record->scalar_088 = 0x88u;
  record->scalar_08c = 0.0f;
  record->flag_080 = 1;
  record->flag_081 = 0;

  g_model_hooks.child_factory_44 = [](Word, const char*) -> void* {
    return static_cast<void*>(&g_instances[0]);
  };

  editor_model_load_004ae3b0(root, nullptr);
  OpaqueChildInstance& child = g_instances[0];
  check(child.field_20 == 0x11u);
  check(child.field_1c == 0x22u);
  check(child.field_1d8 == 0x33u);
  check(child.field_48 == 0x44u);
  check(child.field_4c == 0x55u);
  check(child.field_50 == 0x66u);
  check(child.row_a8[0] == 0xa0u);
  check(child.row_a8[8] == 0xa8u);
  check(child.row_f0[0] == 0xb0u);
  check(child.row_f0[8] == 0xb8u);
  check(child.row_60[0] == 0xb0u + 0xa0u);
  check(child.row_3a0[0] == record->field_020);
  check(child.row_3a0[5] == record->field_034);
  check(child.field_1cc == 0x77u);
  check(child.field_1d0 == 0x88u);
  check(child.field_1d4 == 0x3f800000u);
  check((child.bits_dc8 & 0x1000u) != 0u);
  check((child.bits_dcc & 0x02000000u) == 0u);
  check(child.owner_28 == static_cast<void*>(root));
  check(g_mlog.composes == 1);
  check(g_mlog.range_a_count == 1);
  check(g_mlog.range_b_count == 1);
  check(g_mlog.bridges == 0);
}

void test_model_scalar_nonzero_preserved() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  g_source.records_98->parent_index_008 = 0xffffffffu;
  g_source.records_98->alt_index_00c = 0xffffffffu;
  g_source.records_98->scalar_08c = 2.5f;
  g_model_hooks.child_factory_44 = [](Word, const char*) -> void* {
    return static_cast<void*>(&g_instances[1]);
  };
  editor_model_load_004ae3b0(root, nullptr);
  Word expected = 0;
  float value = 2.5f;
  __builtin_memcpy(&expected, &value, sizeof(expected));
  check(g_instances[1].field_1d4 == expected);
}

void test_model_flag_bits() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  g_source.records_98->parent_index_008 = 0xffffffffu;
  g_source.records_98->alt_index_00c = 0xffffffffu;
  g_source.records_98->flag_080 = 0;
  g_source.records_98->flag_081 = 1;
  g_instances[2].bits_dc8 = 0x1000u;
  g_instances[2].bits_dcc = 0x02000000u;
  g_model_hooks.child_factory_44 = [](Word, const char*) -> void* {
    return static_cast<void*>(&g_instances[2]);
  };
  editor_model_load_004ae3b0(root, nullptr);
  check((g_instances[2].bits_dc8 & 0x1000u) == 0u);
  check((g_instances[2].bits_dcc & 0x02000000u) != 0u);
}

void test_model_parent_counts_and_links() {
  model_setup(2);
  OpaqueModelRoot* root = make_root();
  g_source.records_98[0].parent_index_008 = 0u;
  g_source.records_98[1].parent_index_008 = 0u;
  g_source.records_98[0].alt_index_00c = 0xffffffffu;
  g_source.records_98[1].alt_index_00c = 0xffffffffu;

  g_model_hooks.child_factory_44 = [](Word, const char*) -> void* {
    static int next = 0;
    void* p = static_cast<void*>(&g_instances[next]);
    next = (next + 1) % 4;
    return p;
  };
  editor_model_load_004ae3b0(root, nullptr);
  check(g_mlog.seeds == 2);
  check(g_mlog.seed_values[0] == 2u);
  check(g_mlog.seed_values[1] == 0u);
  check(g_mlog.bridges == 2);
  check(g_mlog.acquires >= 2);
  check(g_mlog.releases >= 2);
}

void test_model_entry_emission() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  g_source.records_98->parent_index_008 = 0xffffffffu;
  g_source.records_98->alt_index_00c = 0xffffffffu;
  g_source.records_98->entry_count_0d4 = 2;
  g_source.records_98->entry_values[0] = 0xa0u;
  g_source.records_98->entry_values[1] = 0xa1u;
  g_source.records_98->entry_vec_a[1][2] = 0xc2u;
  g_source.records_98->entry_vec_b[0][1] = 0xd1u;
  g_model_hooks.child_factory_44 = [](Word, const char*) -> void* {
    return static_cast<void*>(&g_instances[3]);
  };
  editor_model_load_004ae3b0(root, nullptr);
  check(g_nodes[0].opaque_00 == 0xa0u);
  check(g_nodes[1].opaque_00 == 0xa1u);
  check(g_nodes[1].opaque_0c == 0xc2u);
  check(g_nodes[0].opaque_14 == 0xd1u);
  check(g_nodes[0].opaque_18 == 0u);
}

void test_model_alt_index_marks_clears_link() {
  model_setup(1);
  OpaqueModelRoot* root = make_root();
  g_source.records_98->parent_index_008 = 0xffffffffu;
  g_source.records_98->alt_index_00c = 0u;
  g_source.records_98->flag_081 = 1;
  g_instances[0].link_3e0 = reinterpret_cast<Word*>(0xdeadu);
  g_model_hooks.child_factory_44 = [](Word, const char*) -> void* {
    return static_cast<void*>(&g_instances[0]);
  };
  editor_model_load_004ae3b0(root, nullptr);
  check(g_instances[0].link_3e0 == nullptr);
  check(g_mlog.releases >= 1);
}

}  // namespace

int run_editor_wave10_model_tests() {
  test_row_publish_writes_next_only();
  test_row_publish_writes_both_rows();
  test_apply_children_ownership_swap_order();
  test_apply_children_no_release_when_owner_unchanged();
  test_apply_children_null_owner_skips_key_and_register();
  test_apply_children_flag_accumulates_and_uses_and_semantics();
  test_apply_children_flag_read_after_call();
  test_arena_small_request_returns_sentinel();
  test_arena_out_of_arena_falls_back_by_alignment();
  test_arena_footer_alignment_adds_four();
  test_arena_split_marks_in_use_and_updates_used();
  test_arena_no_split_when_remainder_too_small();
  test_arena_footer_mode_stores_owner_and_flags();
  test_arena_scans_past_in_use_blocks();
  test_model_null_source_returns_zero();
  test_model_axes_and_bounds_publication();
  test_model_select_mirror_normalization();
  test_model_index_branch_order();
  test_model_name_compare_gates_named_apply();
  test_model_mode_fetch_zero_skips_name_queries();
  test_model_phase_call_order();
  test_model_child_field_mutation();
  test_model_scalar_nonzero_preserved();
  test_model_flag_bits();
  test_model_parent_counts_and_links();
  test_model_entry_emission();
  test_model_alt_index_marks_clears_link();
  return failures;
}

}  // namespace openspore::reconstruction::pkg_editor_wave10
