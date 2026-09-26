#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "editor wave10 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_EDITOR_WAVE10_THISCALL __thiscall
#else
#define PKG_EDITOR_WAVE10_THISCALL __attribute__((thiscall))
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

namespace openspore::reconstruction::pkg_editor_wave10 {

using Word = std::uint32_t;
using Half = std::uint16_t;
using Byte = std::uint8_t;
using Real = float;

static_assert(sizeof(void*) == 4, "wave10 target pointers are 32-bit");
static_assert(sizeof(float) == 4, "wave10 target floats are 32-bit");
static_assert(sizeof(Word) == 4, "wave10 target words are 32-bit");
static_assert(sizeof(Half) == 2, "wave10 target halfwords are 16-bit");

enum ModelOp : Word {
  kOpQuerySource = 1,
  kOpIndexQuery,
  kOpSingletonLookup,
  kOpSingletonCall2c,
  kOpSlotRelease,
  kOpModeInitialize,
  kOpModeFetch,
  kOpNameQuery,
  kOpRootApplyNamed,
  kOpRootApplyTag,
  kOpChildFinish,
  kOpCountClear,
  kOpStagePrepare,
  kOpStageFinish,
  kOpStagePayload,
  kOpTableAlloc,
  kOpRefAssign,
  kOpTablePayload,
  kOpStagePublish,
  kOpMatrixCompose,
  kOpRangeAppend,
  kOpEntryLookup,
  kOpModeRelease,
};

struct OpaqueRef {
  Word opaque_00 = 0;
  Word refcount_04 = 0;
  Word key_08 = 0;
};

static_assert(offsetof(OpaqueRef, refcount_04) == 0x04, "refcount slot");
static_assert(offsetof(OpaqueRef, key_08) == 0x08, "key slot");
static_assert(sizeof(OpaqueRef) == 0x0c, "ref observed extent");

struct OpaqueVec3Publisher {
  std::uint8_t opaque_00[0x74]{};
  Word row_prev_74 = 0;
  Word row_prev_78 = 0;
  Word row_prev_7c = 0;
  Word row_next_80 = 0;
  Word row_next_84 = 0;
  Word row_next_88 = 0;
};

static_assert(offsetof(OpaqueVec3Publisher, row_prev_74) == 0x74,
              "previous row first word");
static_assert(offsetof(OpaqueVec3Publisher, row_next_80) == 0x80,
              "next row first word");
static_assert(offsetof(OpaqueVec3Publisher, row_next_88) == 0x88,
              "next row third word");
static_assert(sizeof(OpaqueVec3Publisher) == 0x8c, "publisher observed extent");

struct OpaqueChildNode {
  Word opaque_00 = 0;
  Word opaque_04 = 0;
  Word opaque_08 = 0;
  Word opaque_0c = 0;
  Word opaque_10 = 0;
  Word opaque_14 = 0;
  Word opaque_18 = 0;
  Word opaque_1c = 0;
  Word opaque_20 = 0;
  Word opaque_24 = 0;
  Word opaque_28 = 0;
  Word opaque_2c = 0;
  Word opaque_30 = 0;
  Word opaque_34 = 0;
};

static_assert(sizeof(OpaqueChildNode) == 0x38, "child node observed extent");

struct OpaqueModelHost {
  std::uint8_t opaque_00[0x18]{};
  Word* child_base_18 = nullptr;
  Word* child_end_1c = nullptr;
  std::uint8_t opaque_20[0x0c]{};
  Byte accept_flag_2c = 0;
  std::uint8_t opaque_2d[0x03]{};
  OpaqueRef* owner_30 = nullptr;
  std::uint8_t opaque_34[0x04]{};
  Real scalar_38 = 0.0f;
};

static_assert(offsetof(OpaqueModelHost, child_base_18) == 0x18,
              "child array base");
static_assert(offsetof(OpaqueModelHost, child_end_1c) == 0x1c,
              "child array end");
static_assert(offsetof(OpaqueModelHost, accept_flag_2c) == 0x2c, "accept flag");
static_assert(offsetof(OpaqueModelHost, owner_30) == 0x30, "owner slot");
static_assert(offsetof(OpaqueModelHost, scalar_38) == 0x38, "scalar field");

struct OpaqueArena {
  Byte* base_00 = nullptr;
  Word base_offset_04 = 0;
  Word used_08 = 0;
  Word* freelist_0c = nullptr;
  Word flags_10 = 0;
};

static_assert(offsetof(OpaqueArena, base_offset_04) == 0x04,
              "arena base offset");
static_assert(offsetof(OpaqueArena, used_08) == 0x08, "arena used bytes");
static_assert(offsetof(OpaqueArena, freelist_0c) == 0x0c, "arena free head");
static_assert(offsetof(OpaqueArena, flags_10) == 0x10, "arena flags");

struct OpaqueRange {
  Word* begin = nullptr;
  Word* end = nullptr;
  Word* cap = nullptr;
};

static_assert(sizeof(OpaqueRange) == 0x0c, "range descriptor");

struct OpaqueChildInstance {
  Word vtable_00 = 0;
  Word opaque_04 = 0;
  Word opaque_08 = 0;
  Word bound_0c = 0;
  Word bound_10 = 0;
  Word bound_14 = 0;
  std::uint8_t opaque_18[0x04]{};
  Word field_1c = 0;
  Word field_20 = 0;
  std::uint8_t opaque_24[0x04]{};
  void* owner_28 = nullptr;
  std::uint8_t opaque_2c[0x1c]{};
  Word field_48 = 0;
  Word field_4c = 0;
  Word field_50 = 0;
  std::uint8_t opaque_54[0x0c]{};
  Word row_60[9]{};
  std::uint8_t opaque_84[0x24]{};
  Word row_a8[9]{};
  std::uint8_t opaque_cc[0x24]{};
  Word row_f0[9]{};
  std::uint8_t opaque_114[0xb8]{};
  Word field_1cc = 0;
  Word field_1d0 = 0;
  Word field_1d4 = 0;
  Word field_1d8 = 0;
  std::uint8_t opaque_1dc[0x160]{};
  Word* link_33c = nullptr;
  std::uint8_t opaque_340[0x60]{};
  Word row_3a0[6]{};
  std::uint8_t opaque_3b8[0x28]{};
  Word* link_3e0 = nullptr;
  Word* link_3e4 = nullptr;
  std::uint8_t opaque_3e8[0x9e0]{};
  Word bits_dc8 = 0;
  Word bits_dcc = 0;
};

static_assert(offsetof(OpaqueChildInstance, field_1c) == 0x1c, "child 1c");
static_assert(offsetof(OpaqueChildInstance, field_20) == 0x20, "child 20");
static_assert(offsetof(OpaqueChildInstance, owner_28) == 0x28, "child owner");
static_assert(offsetof(OpaqueChildInstance, row_60) == 0x60, "child 60 row");
static_assert(offsetof(OpaqueChildInstance, row_a8) == 0xa8, "child a8 row");
static_assert(offsetof(OpaqueChildInstance, row_f0) == 0xf0, "child f0 row");
static_assert(offsetof(OpaqueChildInstance, field_1cc) == 0x1cc, "child 1cc");
static_assert(offsetof(OpaqueChildInstance, field_1d4) == 0x1d4, "child 1d4");
static_assert(offsetof(OpaqueChildInstance, field_1d8) == 0x1d8, "child 1d8");
static_assert(offsetof(OpaqueChildInstance, link_33c) == 0x33c, "child 33c");
static_assert(offsetof(OpaqueChildInstance, row_3a0) == 0x3a0, "child 3a0");
static_assert(offsetof(OpaqueChildInstance, link_3e0) == 0x3e0, "child 3e0");
static_assert(offsetof(OpaqueChildInstance, link_3e4) == 0x3e4, "child 3e4");
static_assert(offsetof(OpaqueChildInstance, bits_dc8) == 0xdc8,
              "child dc8 bits");
static_assert(offsetof(OpaqueChildInstance, bits_dcc) == 0xdcc,
              "child dcc bits");
static_assert(sizeof(OpaqueChildInstance) == 0xdd0, "child observed extent");

struct OpaqueChildEntryRecord {
  Word key_000 = 0;
  Word value_004 = 0;
  Word parent_index_008 = 0;
  Word alt_index_00c = 0;
  Word field_010 = 0;
  Word field_014 = 0;
  Word field_018 = 0;
  Word field_01c = 0;
  Word field_020 = 0;
  Word field_024 = 0;
  Word field_028 = 0;
  Word field_02c = 0;
  Word field_030 = 0;
  Word field_034 = 0;
  Word block_a[9]{};
  Word block_b[9]{};
  Byte flag_080 = 0;
  Byte flag_081 = 0;
  std::uint8_t opaque_082[0x02]{};
  Word scalar_084 = 0;
  Word scalar_088 = 0;
  Real scalar_08c = 0.0f;
  Word block_offset_090 = 0;
  Word range_a[8]{};
  Word range_b[8]{};
  Word entry_count_0d4 = 0;
  Word entry_keys[8]{};
  Word entry_values[8]{};
  Word entry_vec_a[8][3]{};
  Word entry_vec_b[8][3]{};
};

static_assert(offsetof(OpaqueChildEntryRecord, field_020) == 0x020,
              "record 020");
static_assert(offsetof(OpaqueChildEntryRecord, block_a) == 0x038,
              "record block a");
static_assert(offsetof(OpaqueChildEntryRecord, block_b) == 0x05c,
              "record block b");
static_assert(offsetof(OpaqueChildEntryRecord, flag_080) == 0x080,
              "record flag 080");
static_assert(offsetof(OpaqueChildEntryRecord, flag_081) == 0x081,
              "record flag 081");
static_assert(offsetof(OpaqueChildEntryRecord, scalar_084) == 0x084,
              "record 084");
static_assert(offsetof(OpaqueChildEntryRecord, scalar_08c) == 0x08c,
              "record 08c");
static_assert(offsetof(OpaqueChildEntryRecord, range_a) == 0x094,
              "record range a");
static_assert(offsetof(OpaqueChildEntryRecord, range_b) == 0x0b4,
              "record range b");
static_assert(offsetof(OpaqueChildEntryRecord, entry_count_0d4) == 0x0d4,
              "record entry count");
static_assert(offsetof(OpaqueChildEntryRecord, entry_keys) == 0x0d8,
              "record entry keys");
static_assert(offsetof(OpaqueChildEntryRecord, entry_values) == 0x0f8,
              "record entry values");
static_assert(offsetof(OpaqueChildEntryRecord, entry_vec_a) == 0x118,
              "record entry vec a");
static_assert(offsetof(OpaqueChildEntryRecord, entry_vec_b) == 0x178,
              "record entry vec b");
static_assert(sizeof(OpaqueChildEntryRecord) == 0x1d8,
              "record observed extent");

struct OpaqueModelSource {
  std::uint8_t opaque_00[0x08]{};
  Word manager_08 = 0;
  Word init_arg_0c = 0;
  Word init_arg_10 = 0;
  std::uint8_t opaque_14[0x04]{};
  Word axes_18[17]{};
  std::uint8_t opaque_5c[0x3c]{};
  OpaqueChildEntryRecord* records_98 = nullptr;
  OpaqueChildEntryRecord* records_end_9c = nullptr;
};

static_assert(offsetof(OpaqueModelSource, manager_08) == 0x08, "source 08");
static_assert(offsetof(OpaqueModelSource, init_arg_10) == 0x10, "source 10");
static_assert(offsetof(OpaqueModelSource, axes_18) == 0x18, "source axes");
static_assert(offsetof(OpaqueModelSource, records_98) == 0x98,
              "source records");
static_assert(offsetof(OpaqueModelSource, records_end_9c) == 0x9c,
              "source records end");

struct OpaqueModelRootVtable {
  void (*apply_named_00)(void* arg);
  void (*apply_slot_04)(void* arg);
  void (*apply_tag_08)(Word arg);
};

struct OpaqueModelRoot {
  OpaqueModelRootVtable* vtable_00 = nullptr;
  std::uint8_t opaque_04[0x08]{};
  Word bound_0c = 0;
  Word bound_10 = 0;
  Word bound_14 = 0;
  Word* child_base_18 = nullptr;
  Word* child_end_1c = nullptr;
  std::uint8_t opaque_20[0x34]{};
  Word root_handle_54 = 0;
  Word parent_58 = 0;
  Half select_5c = 0;
  std::uint8_t opaque_5e[0x02]{};
  Word mirror_60 = 0;
  std::uint8_t opaque_64[0x08]{};
  Half select_6c = 0;
  std::uint8_t opaque_6e[0x02]{};
  Word mirror_70 = 0;
  std::uint8_t opaque_74[0x08]{};
  Half select_7c = 0;
  std::uint8_t opaque_7e[0x02]{};
  Word mirror_80 = 0;
  std::uint8_t opaque_84[0x08]{};
  Word group_8c[3]{};
  Word group_98[3]{};
  Word axes_a4[3]{};
  Word axes_b0[3]{};
  Word axes_bc[3]{};
  std::uint8_t opaque_c8[0x14]{};
  Word trailing_dc = 0;
  std::uint8_t opaque_e0[0x120]{};
};

static_assert(offsetof(OpaqueModelRoot, bound_0c) == 0x0c, "root bound 0c");
static_assert(offsetof(OpaqueModelRoot, bound_10) == 0x10, "root bound 10");
static_assert(offsetof(OpaqueModelRoot, bound_14) == 0x14, "root bound 14");
static_assert(offsetof(OpaqueModelRoot, child_base_18) == 0x18,
              "root child base");
static_assert(offsetof(OpaqueModelRoot, child_end_1c) == 0x1c,
              "root child end");
static_assert(offsetof(OpaqueModelRoot, root_handle_54) == 0x54, "root handle");
static_assert(offsetof(OpaqueModelRoot, parent_58) == 0x58, "root parent");
static_assert(offsetof(OpaqueModelRoot, select_5c) == 0x5c, "root select 5c");
static_assert(offsetof(OpaqueModelRoot, mirror_60) == 0x60, "root mirror 60");
static_assert(offsetof(OpaqueModelRoot, select_6c) == 0x6c, "root select 6c");
static_assert(offsetof(OpaqueModelRoot, mirror_70) == 0x70, "root mirror 70");
static_assert(offsetof(OpaqueModelRoot, select_7c) == 0x7c, "root select 7c");
static_assert(offsetof(OpaqueModelRoot, mirror_80) == 0x80, "root mirror 80");
static_assert(offsetof(OpaqueModelRoot, group_8c) == 0x8c, "root group 8c");
static_assert(offsetof(OpaqueModelRoot, group_98) == 0x98, "root group 98");
static_assert(offsetof(OpaqueModelRoot, axes_a4) == 0xa4, "root axes a4");
static_assert(offsetof(OpaqueModelRoot, axes_b0) == 0xb0, "root axes b0");
static_assert(offsetof(OpaqueModelRoot, axes_bc) == 0xbc, "root axes bc");
static_assert(offsetof(OpaqueModelRoot, trailing_dc) == 0xdc,
              "root trailing dc");

struct OpaqueModeManagerInit {
  OpaqueModelRootVtable* vftable_00 = nullptr;
  Word tag_04 = 0;
  Word arg_08 = 0;
  Word opaque_0c = 0;
  Word opaque_10 = 0;
  std::uint8_t opaque_14[0x08]{};
};

struct OpaqueModeManagerHooks {
  void (*initialize_00)(void* mode, OpaqueModeManagerInit* init);
  void (*opaque_04)(void* mode);
  void (*opaque_08)(void* mode);
  void (*opaque_0c)(void* mode);
  void (*opaque_10)(void* mode);
  void (*opaque_14)(void* mode);
  void (*opaque_18)(void* mode);
  void (*opaque_1c)(void* mode);
  void (*opaque_20)(void* mode);
  void (*opaque_24)(void* mode);
  void (*opaque_28)(void* mode);
  void (*call_2c)(void* mode, Word a, Word b, Word c);
  void (*opaque_30)(void* mode);
  void (*opaque_34)(void* mode);
  void (*opaque_38)(void* mode);
  void (*opaque_3c)(void* mode);
  void (*opaque_40)(void* mode);
  void (*opaque_44)(void* mode);
  void (*opaque_48)(void* mode);
  void (*opaque_4c)(void* mode);
  void (*opaque_50)(void* mode);
  void (*opaque_54)(void* mode);
  void (*opaque_58)(void* mode);
};

struct OpaqueModeManager {
  OpaqueModeManagerHooks* vftable_00 = nullptr;
  std::uint8_t opaque_04[0x20]{};
};

struct OpaqueObjectControl {
  void (*opaque_00)(void* object);
  void (*acquire_04)(void* object);
  void (*release_08)(void* object);
  void (*opaque_0c)(void* object);
  void (*opaque_10)(void* object);
  void (*opaque_14)(void* object, Word a, Word b, Word c);
  void (*opaque_18)(void* object);
  void (*opaque_1c)(void* object);
  void (*opaque_20)(void* object);
  void (*opaque_24)(void* object);
  void (*opaque_28)(void* object);
  void (*opaque_2c)(void* object, Word a, Word b, Word c);
  void (*opaque_30)(void* object);
  void (*opaque_34)(void* object);
  void (*opaque_38)(void* object);
  void (*opaque_3c)(void* object);
};

struct OpaqueRefCounted {
  std::uint8_t opaque_00[0x04]{};
  Word refcount_04 = 0;
  Word key_08 = 0;
  std::uint8_t opaque_0c[0x0c]{};
  OpaqueRange entries_18;
  std::uint8_t opaque_24[0x20]{};
  OpaqueObjectControl* control_44 = nullptr;
};

static_assert(offsetof(OpaqueRefCounted, refcount_04) == 0x04,
              "refcounted count");
static_assert(offsetof(OpaqueRefCounted, key_08) == 0x08, "refcounted key");
static_assert(offsetof(OpaqueRefCounted, entries_18) == 0x18,
              "refcounted entries");
static_assert(offsetof(OpaqueRefCounted, control_44) == 0x44,
              "refcounted control");

struct OpaqueWideName {
  Half* text = nullptr;
};

struct OpaqueModelHostHooks {
  Word (*query_key_00)(void* owner);
  Word (*release_04)(void* owner);
  Byte (*apply_child_08)(void* child, Word a, Word b, Real c, Byte d, Byte e);
  void (*register_child_0c)(void* host, void* owner);
};

struct OpaqueArenaHooks {
  Word (*fallback_00)(void* arena, Word need);
  Word (*fallback_04)(void* arena, Word need, Word align);
};

struct OpaqueModelHooks {
  Word trace[512]{};
  Word trace_count = 0;
  void record(Word op) {
    if (trace_count < 512) {
      trace[trace_count] = op;
    }
    ++trace_count;
  }
  void* (*singleton_00)(void* context);
  Word (*singleton_04)(void* context);
  void (*singleton_08)(void* mode, Word a, Word b, Word c);
  void (*slot_lookup_0c)(void** out, Word tag, Word* slot);
  void (*slot_discard_10)(void* object);
  void* (*mode_manager_14)(void);
  bool (*mode_initialize_18)(void* mode, OpaqueModeManagerInit* init);
  void (*mode_release_1c)(void* mode);
  Word (*mode_fetch_20)(void* mode, void** slot);
  OpaqueWideName* (*name_query_24)(void* context);
  Word (*tag_query_28)(void* context);
  std::int32_t (*index_query_2c)(void* context, Word key);
  void (*child_finish_30)(Word* base, Word* end);
  void (*child_bridge_2c)(void** held);
  void (*stage_clear_34)(Word count);
  void (*stage_prepare_38)(void* buffer);
  void (*stage_finish_3c)(void);
  void (*stage_publish_5c)(void);
  void (*stage_payload_40)(Word count, Word mode);
  void* (*child_factory_44)(Word type, const char* name);
  void* (*child_construct_48)(void* handle);
  void (*child_seed_4c)(Word value);
  void (*ref_acquire_50)(void* object);
  void (*ref_assign_54)(void** slot, void* value);
  void (*ref_release_58)(void* object);
  void (*range_append_60)(OpaqueRange* range, const Word* begin,
                          const Word* end);
  void (*matrix_compose_64)(Word* out, const Word* a, const Word* b);
  OpaqueChildNode* (*entry_lookup_68)(void* record, Word index);
  void (*source_query_6c)(void* context, void* owner, void** out);
  const Half* compare_name = nullptr;
};

extern OpaqueModelHostHooks g_model_host_hooks;
extern OpaqueArenaHooks g_arena_hooks;
extern OpaqueModelHooks g_model_hooks;

extern "C" void PKG_EDITOR_WAVE10_THISCALL
editor_row_publish_005a2010(OpaqueVec3Publisher* self, Word row_x, Word row_y,
                            Word row_z, Byte also_previous);

extern "C" Word PKG_EDITOR_WAVE10_THISCALL editor_model_apply_children_004ae260(
    OpaqueModelHost* self, Word context, OpaqueRef* owner, Byte flag_primary,
    Byte flag_secondary);

extern "C" Word PKG_EDITOR_WAVE10_THISCALL arena_release_block_004bfc40(
    OpaqueArena* self, Word payload_size, Word alignment);

extern "C" Byte PKG_EDITOR_WAVE10_THISCALL
editor_model_load_004ae3b0(OpaqueModelRoot* self, void* context);

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

}
