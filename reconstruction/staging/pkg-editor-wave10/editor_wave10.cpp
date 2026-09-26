#include "editor_wave10.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_editor_wave10 {

namespace {

constexpr Word kSizeMask = 0x3fffffffu;
constexpr Word kTopMask = 0xc0000000u;
constexpr Word kInUseBit = 0x80000000u;
constexpr Word kFooterBit = 0x40000000u;
constexpr Word kBit1000 = 0x00001000u;
constexpr Word kBit2000000 = 0x02000000u;
constexpr Word kOneFloat = 0x3f800000u;
constexpr Word kRecordStride = 0x1d8u;
constexpr Word kCountCap = 512u;

std::uint32_t trunc(std::uintptr_t value) {
  return static_cast<std::uint32_t>(value);
}

std::uint32_t addr(const void* p) {
  return trunc(reinterpret_cast<std::uintptr_t>(p));
}

Word* at(std::uint32_t address) {
  return reinterpret_cast<Word*>(static_cast<std::uintptr_t>(address));
}

Word bit_cast_word(Real value) {
  Word out = 0;
  std::memcpy(&out, &value, sizeof(out));
  return out;
}

std::int32_t sign_compare(Half lhs, Half rhs) {
  if (lhs != rhs) {
    return lhs < rhs ? -1 : 1;
  }
  return 0;
}

std::int32_t wide_compare(const Half* lhs, const Half* rhs) {
  if (rhs == nullptr) {
    return lhs == nullptr ? 0 : 1;
  }
  for (;;) {
    const std::int32_t order = sign_compare(lhs[0], rhs[0]);
    if (order != 0) {
      return order;
    }
    if (lhs[0] == 0) {
      return 0;
    }
    const std::int32_t inner = sign_compare(lhs[1], rhs[1]);
    if (inner != 0) {
      return inner;
    }
    lhs += 2;
    rhs += 2;
  }
}

void copy_words(Word* dst, const Word* src, Word count) {
  for (Word i = 0; i < count; ++i) {
    dst[i] = src[i];
  }
}

void acquire(void* object) {
  if (object != nullptr) {
    g_model_hooks.ref_acquire_50(object);
  }
}

void release(void* object) {
  if (object != nullptr) {
    g_model_hooks.ref_release_58(object);
  }
}

void assign_ref(void** slot, void* value) {
  if (*slot != value) {
    void* const previous = *slot;
    acquire(value);
    *slot = value;
    release(previous);
  }
}

}  // namespace

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

OpaqueModelHostHooks g_model_host_hooks{};
OpaqueArenaHooks g_arena_hooks{};
OpaqueModelHooks g_model_hooks{};

extern "C" void PKG_EDITOR_WAVE10_THISCALL
editor_row_publish_005a2010(OpaqueVec3Publisher* self, Word row_x, Word row_y,
                            Word row_z, Byte also_previous) {
  self->row_next_80 = row_x;
  self->row_next_84 = row_y;
  self->row_next_88 = row_z;
  if (also_previous != 0) {
    self->row_prev_74 = row_x;
    self->row_prev_78 = row_y;
    self->row_prev_7c = row_z;
  }
}

extern "C" Word PKG_EDITOR_WAVE10_THISCALL editor_model_apply_children_004ae260(
    OpaqueModelHost* self, Word context, OpaqueRef* owner, Byte flag_primary,
    Byte flag_secondary) {
  self->accept_flag_2c = 1;
  OpaqueRef** const slot = &self->owner_30;
  if (owner != *slot) {
    OpaqueRef* const previous = *slot;
    if (owner != nullptr) {
      owner->refcount_04 += 1;
    }
    *slot = owner;
    if (previous != nullptr) {
      g_model_host_hooks.release_04(previous);
    }
  }
  Word key = 0;
  if (owner != nullptr) {
    key = g_model_host_hooks.query_key_00(owner);
  }
  const int count = static_cast<int>(
      (addr(self->child_end_1c) - addr(self->child_base_18)) >> 2);
  for (int i = 0; i < count; ++i) {
    void* const child = reinterpret_cast<void*>(self->child_base_18[i]);
    const Byte accepted = g_model_host_hooks.apply_child_08(
        child, context, key, self->scalar_38, flag_primary, flag_secondary);
    const Byte next = (accepted != 0 && self->accept_flag_2c != 0) ? 1 : 0;
    self->accept_flag_2c = next;
  }
  if (self->owner_30 != nullptr) {
    g_model_host_hooks.register_child_0c(self, self->owner_30);
  }
  return 1;
}

extern "C" Word PKG_EDITOR_WAVE10_THISCALL arena_release_block_004bfc40(
    OpaqueArena* self, Word payload_size, Word alignment) {
  const Word flags = self->flags_10;
  Word need = (payload_size + 3u) & 0xfffffffcu;
  need += ((flags & kFooterBit) != 0u) ? 4u : 0u;
  need += 8u;

  if (self->base_00 != nullptr && static_cast<std::int32_t>(self->used_08) >=
                                      static_cast<std::int32_t>(need)) {
    const std::uint32_t arena_end =
        addr(self->base_00) + 0x10u + self->base_offset_04;
    if (static_cast<std::int32_t>(need) < 9) {
      return addr(self->base_00) + 0x18u;
    }
    Word* cursor = self->freelist_0c;
    Word accumulated = 0;
    while (cursor < at(arena_end) &&
           static_cast<std::int32_t>(accumulated + need) <
               static_cast<std::int32_t>(self->used_08)) {
      if (static_cast<std::int32_t>(*cursor) >= 0) {
        Word* const next = at(addr(cursor) + (*cursor & kSizeMask));
        if (next >= at(arena_end) || static_cast<std::int32_t>(*next) < 0) {
          accumulated += *cursor & kSizeMask;
          const std::uint32_t aligned =
              (addr(cursor) + alignment + 7u) & ~(alignment - 1u);
          Word* const header = at(aligned - 8u);
          const std::uint32_t block_end = addr(cursor) + (*cursor & kSizeMask);
          if (aligned - 8u + need < block_end) {
            const std::int32_t lead =
                static_cast<std::int32_t>(addr(header) - addr(cursor));
            if (lead > 0) {
              if ((flags & kFooterBit) != 0u) {
                Word saved = 0;
                if ((cursor[1] & kFooterBit) != 0u) {
                  saved = *at(cursor[1] - 4u + (cursor[1] & kSizeMask));
                }
                header[1] = cursor[1];
                header[0] = (*cursor & kSizeMask) - static_cast<Word>(lead);
                Word* const follower = at(header[1]);
                *follower =
                    (*follower & kTopMask) |
                    (((*follower & kSizeMask) + static_cast<Word>(lead)) &
                     kSizeMask);
                if (static_cast<std::int32_t>(*follower) < 0 ||
                    follower == at(addr(self->base_00) + 0x10u)) {
                  self->used_08 = static_cast<Word>(
                      static_cast<std::int32_t>(self->used_08) - lead);
                }
                *at(addr(follower) - 4u + (*follower & kSizeMask)) = saved;
              } else {
                header[1] = cursor[1];
                header[0] = (*cursor & kSizeMask) - static_cast<Word>(lead);
                Word* const follower = at(header[1]);
                *follower =
                    (*follower & kTopMask) |
                    (((*follower & kSizeMask) + static_cast<Word>(lead)) &
                     kSizeMask);
              }
            }
            const std::int32_t rest =
                static_cast<std::int32_t>(*header & kSizeMask) -
                static_cast<std::int32_t>(need);
            if (rest > 0x27) {
              *header = (*header & kTopMask) | (need & kSizeMask);
              Word* const tail = at(addr(header) + (*header & kSizeMask));
              tail[0] = static_cast<Word>(rest);
              tail[1] = addr(header);
            }
            if (self->freelist_0c == cursor) {
              self->freelist_0c = at(addr(header) + (*header & kSizeMask));
            }
            self->used_08 = static_cast<Word>(
                static_cast<std::int32_t>(self->used_08) -
                static_cast<std::int32_t>(*header & kSizeMask));
            *header |= kInUseBit;
            if ((flags & kFooterBit) == 0u) {
              return static_cast<Word>(aligned);
            }
            *header |= kFooterBit;
            *reinterpret_cast<void**>(aligned - 0x0cu + (*header & kSizeMask)) =
                self;
            return static_cast<Word>(aligned);
          }
        } else {
          Word* const beyond = at(addr(next) + (*next & kSizeMask));
          if (beyond < at(arena_end)) {
            beyond[1] = addr(cursor);
          }
          *cursor = *cursor + *next;
        }
      }
      cursor = at(addr(cursor) + (*cursor & kSizeMask));
    }
  }
  if (alignment < 8u) {
    return g_arena_hooks.fallback_00(self, need);
  }
  return g_arena_hooks.fallback_04(self, need, alignment);
}

extern "C" Byte PKG_EDITOR_WAVE10_THISCALL
editor_model_load_004ae3b0(OpaqueModelRoot* self, void* context) {
  g_model_hooks.trace_count = 0;

  g_model_hooks.record(kOpQuerySource);
  void* source_object = nullptr;
  g_model_hooks.source_query_6c(context, context, &source_object);
  if (source_object == nullptr) {
    return 0;
  }
  OpaqueModelSource* const source =
      static_cast<OpaqueModelSource*>(source_object);
  const Word* const axes = source->axes_18;
  OpaqueChildEntryRecord* const records = source->records_98;
  const Word record_count =
      (addr(source->records_end_9c) - addr(records)) / kRecordStride;

  self->parent_58 = axes[0];
  self->root_handle_54 = 0;

  g_model_hooks.record(kOpIndexQuery);
  if (g_model_hooks.index_query_2c(context, self->parent_58) != -1) {
    g_model_hooks.record(kOpSingletonLookup);
    void* const mode = g_model_hooks.singleton_00(context);
    g_model_hooks.record(kOpSingletonCall2c);
    g_model_hooks.singleton_08(mode, 0x051ce36au, 0x015d68a8u,
                               g_model_hooks.singleton_04(context));
    g_model_hooks.record(kOpSlotRelease);
    void* held = nullptr;
    g_model_hooks.slot_lookup_0c(&held, 0x051ce36au, &self->root_handle_54);
    if (held != nullptr) {
      g_model_hooks.slot_discard_10(held);
    }
  }

  if (self->select_5c != static_cast<Half>(self->mirror_60)) {
    self->select_5c = 0;
    self->mirror_60 = self->select_5c;
  }
  if (self->select_6c != static_cast<Half>(self->mirror_70)) {
    self->select_6c = 0;
    self->mirror_70 = self->select_6c;
  }
  if (self->select_7c != static_cast<Half>(self->mirror_80)) {
    self->select_7c = 0;
    self->mirror_80 = self->select_7c;
  }

  OpaqueModeManagerInit init{};
  init.vftable_00 =
      reinterpret_cast<OpaqueModelRootVtable*>(source->manager_08);
  init.arg_08 = source->init_arg_10;
  init.tag_04 = 0x030bdee3u;

  g_model_hooks.record(kOpModeInitialize);
  void* mode_handle = nullptr;
  void* const manager = g_model_hooks.mode_manager_14();
  if (mode_handle != nullptr) {
    void* const retained = mode_handle;
    mode_handle = nullptr;
    g_model_hooks.mode_release_1c(retained);
  }
  if (g_model_hooks.mode_initialize_18(manager, &init)) {
    g_model_hooks.record(kOpModeFetch);
    if (g_model_hooks.mode_fetch_20(manager, &mode_handle) != 0) {
      g_model_hooks.record(kOpNameQuery);
      OpaqueWideName* const name = g_model_hooks.name_query_24(context);
      const Word tag = g_model_hooks.tag_query_28(context);
      g_model_hooks.record(kOpRootApplyNamed);
      if (name != nullptr &&
          wide_compare(name->text, g_model_hooks.compare_name) != 0) {
        g_model_hooks.record(kOpRootApplyNamed);
        self->vtable_00->apply_named_00(name);
      }
      g_model_hooks.record(kOpRootApplyTag);
      self->vtable_00->apply_tag_08(tag);
    }
  }

  for (Word i = 0; i < 3; ++i) {
    self->group_8c[i] = axes[i + 2];
    self->group_98[i] = axes[i + 5];
  }
  copy_words(self->axes_a4, axes + 8, 3);
  copy_words(self->axes_b0, axes + 11, 3);
  copy_words(self->axes_bc, axes + 14, 3);
  self->trailing_dc = axes[1];

  g_model_hooks.record(kOpChildFinish);
  g_model_hooks.child_finish_30(self->child_base_18, self->child_end_1c);
  g_model_hooks.record(kOpCountClear);
  g_model_hooks.stage_clear_34(record_count);
  g_model_hooks.record(kOpStagePrepare);
  g_model_hooks.stage_prepare_38(nullptr);
  g_model_hooks.record(kOpStageFinish);
  g_model_hooks.stage_finish_3c();
  g_model_hooks.record(kOpStagePayload);
  g_model_hooks.stage_payload_40(record_count, 0);

  Word counts[kCountCap];
  for (Word i = 0; i < kCountCap; ++i) {
    counts[i] = 0;
  }
  for (Word i = 0; i < record_count; ++i) {
    const Word parent =
        reinterpret_cast<const OpaqueChildEntryRecord*>(
            reinterpret_cast<const Byte*>(records) + i * kRecordStride)
            ->parent_index_008;
    if (parent < record_count && parent < kCountCap) {
      counts[parent] += 1;
    }
  }

  for (Word i = 0; i < record_count; ++i) {
    g_model_hooks.record(kOpTableAlloc);
    void* const handle = g_model_hooks.child_factory_44(0x0e08u, "Editor");
    void* const instance = (handle == nullptr)
                               ? nullptr
                               : g_model_hooks.child_construct_48(handle);
    g_model_hooks.record(kOpRefAssign);
    assign_ref(reinterpret_cast<void**>(&self->child_base_18[i]), instance);
    g_model_hooks.record(kOpTablePayload);
    g_model_hooks.child_seed_4c(counts[i]);
  }

  g_model_hooks.record(kOpStagePublish);
  g_model_hooks.stage_publish_5c();

  for (Word i = 0; i < record_count; ++i) {
    OpaqueChildInstance* const child =
        reinterpret_cast<OpaqueChildInstance*>(self->child_base_18[i]);
    OpaqueChildEntryRecord* const record =
        reinterpret_cast<OpaqueChildEntryRecord*>(
            reinterpret_cast<Byte*>(records) + i * kRecordStride);

    child->owner_28 = self;
    const bool marked = record->flag_081 != 0;
    child->bits_dcc = marked ? (child->bits_dcc | kBit2000000)
                             : (child->bits_dcc & ~kBit2000000);

    if (static_cast<std::int32_t>(record->alt_index_00c) != -1) {
      if (marked) {
        if (child->link_3e0 != nullptr) {
          void* const previous = child->link_3e0;
          child->link_3e0 = nullptr;
          release(previous);
        }
      } else {
        assign_ref(reinterpret_cast<void**>(&child->link_3e0),
                   reinterpret_cast<void*>(
                       self->child_base_18[record->alt_index_00c]));
      }
      assign_ref(
          reinterpret_cast<void**>(&child->link_3e4),
          reinterpret_cast<void*>(self->child_base_18[record->alt_index_00c]));
    }

    if (static_cast<std::int32_t>(record->parent_index_008) != -1) {
      assign_ref(reinterpret_cast<void**>(&child->link_33c),
                 reinterpret_cast<void*>(
                     self->child_base_18[record->parent_index_008]));
      void* held = child;
      acquire(held);
      g_model_hooks.child_bridge_2c(&held);
      release(held);
    }

    child->field_20 = record->key_000;
    child->field_1c = record->value_004;
    child->field_1d8 = record->field_010;
    child->field_48 = record->field_014;
    child->field_4c = record->field_018;
    child->field_50 = record->field_01c;
    copy_words(child->row_a8, record->block_a, 9);
    copy_words(child->row_f0, record->block_b, 9);
    g_model_hooks.record(kOpMatrixCompose);
    g_model_hooks.matrix_compose_64(child->row_60, child->row_f0,
                                    child->row_a8);
    child->row_3a0[0] = record->field_020;
    child->row_3a0[1] = record->field_024;
    child->row_3a0[2] = record->field_028;
    child->row_3a0[3] = record->field_02c;
    child->row_3a0[4] = record->field_030;
    child->row_3a0[5] = record->field_034;
    child->field_1cc = record->scalar_084;
    child->field_1d0 = record->scalar_088;
    child->field_1d4 = (record->scalar_08c == 0.0f)
                           ? kOneFloat
                           : bit_cast_word(record->scalar_08c);
    child->bits_dc8 = record->flag_080 != 0 ? (child->bits_dc8 | kBit1000)
                                            : (child->bits_dc8 & ~kBit1000);

    g_model_hooks.record(kOpRangeAppend);
    g_model_hooks.range_append_60(
        reinterpret_cast<OpaqueRange*>(record->range_a), record->range_a,
        record->range_a + record->block_offset_090);
    g_model_hooks.record(kOpRangeAppend);
    g_model_hooks.range_append_60(
        reinterpret_cast<OpaqueRange*>(record->range_b), record->range_b,
        record->range_b + record->block_offset_090);

    const Word entries = record->entry_count_0d4;
    for (Word j = 0; j < entries; ++j) {
      g_model_hooks.record(kOpEntryLookup);
      OpaqueChildNode* const node = g_model_hooks.entry_lookup_68(record, j);
      node->opaque_00 = record->entry_values[j];
      node->opaque_04 = record->entry_vec_a[j][0];
      node->opaque_08 = record->entry_vec_a[j][1];
      node->opaque_0c = record->entry_vec_a[j][2];
      node->opaque_10 = record->entry_vec_b[j][0];
      node->opaque_14 = record->entry_vec_b[j][1];
      node->opaque_18 = record->entry_vec_b[j][2];
    }
  }

  g_model_hooks.record(kOpModeRelease);
  self->bound_0c = source->manager_08;
  self->bound_10 = source->init_arg_0c;
  self->bound_14 = source->init_arg_10;
  if (mode_handle != nullptr) {
    g_model_hooks.slot_discard_10(mode_handle);
  }
  return 1;
}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

}  // namespace openspore::reconstruction::pkg_editor_wave10

#undef PKG_EDITOR_WAVE10_THISCALL
