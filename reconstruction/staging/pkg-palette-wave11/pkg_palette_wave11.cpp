#include "pkg_palette_wave11.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_palette_wave11 {
namespace {

std::int32_t word_span(const void* end, const void* begin) {
  return static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(end) -
                                   reinterpret_cast<std::uintptr_t>(begin)) >>
         2;
}

std::uint32_t byte_span(const void* end, const void* begin) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(end) -
                                    reinterpret_cast<std::uintptr_t>(begin));
}

std::uint32_t ninth_of(std::uint32_t value) {
  const std::uint64_t wide = static_cast<std::uint64_t>(value) * 0x38e38e39ULL;
  return static_cast<std::uint32_t>(static_cast<std::uint32_t>(wide >> 32) >>
                                    1);
}

std::int32_t guard_span(const OpaqueTextBuffer* buffer) {
  return static_cast<std::int32_t>(
      (reinterpret_cast<std::uintptr_t>(buffer->end) -
       reinterpret_cast<std::uintptr_t>(buffer->begin)) &
      0xfffffffeU);
}

ReleaseSlot01 node_release_slot(OpaqueNode* node) {
  void* const* table = static_cast<void* const*>(node->vtable);
  return reinterpret_cast<ReleaseSlot01>(table[1]);
}

DropSlot02 node_drop_slot(OpaqueNode* node) {
  void* const* table = static_cast<void* const*>(node->vtable);
  return reinterpret_cast<DropSlot02>(table[2]);
}

ModelSlot04 node_model_slot(OpaqueNode* node) {
  void* const* table = static_cast<void* const*>(node->vtable);
  return reinterpret_cast<ModelSlot04>(table[4]);
}

NodeSlot13 node_rect_slot(OpaqueNode* node) {
  void* const* table = static_cast<void* const*>(node->vtable);
  return reinterpret_cast<NodeSlot13>(table[13]);
}

NodeSlot24 node_apply_slot(OpaqueNode* node) {
  void* const* table = static_cast<void* const*>(node->vtable);
  return reinterpret_cast<NodeSlot24>(table[24]);
}

NodeSlot31 node_layer_slot(OpaqueNode* node) {
  void* const* table = static_cast<void* const*>(node->vtable);
  return reinterpret_cast<NodeSlot31>(table[31]);
}

ModelSlot31 model_layer_slot(OpaqueModel* model) {
  void* const* table = static_cast<void* const*>(model->vtable);
  return reinterpret_cast<ModelSlot31>(table[31]);
}

ModelSlot14 model_bounds_slot(OpaqueModel* model) {
  void* const* table = static_cast<void* const*>(model->vtable);
  return reinterpret_cast<ModelSlot14>(table[14]);
}

ModelSlot48 model_shift_slot(OpaqueModel* model) {
  void* const* table = static_cast<void* const*>(model->vtable);
  return reinterpret_cast<ModelSlot48>(table[48]);
}

ModelSlot49 model_blend_slot(OpaqueModel* model) {
  void* const* table = static_cast<void* const*>(model->vtable);
  return reinterpret_cast<ModelSlot49>(table[49]);
}

ListSlot04 list_release_slot(OpaquePropertyList* list) {
  void* const* table = static_cast<void* const*>(list->vtable);
  return reinterpret_cast<ListSlot04>(table[1]);
}

ListSlot24 list_probe_slot(OpaquePropertyList* list) {
  void* const* table = static_cast<void* const*>(list->vtable);
  return reinterpret_cast<ListSlot24>(table[9]);
}

ListSlot2c list_open_slot(OpaquePropertyList* list) {
  void* const* table = static_cast<void* const*>(list->vtable);
  return reinterpret_cast<ListSlot2c>(table[11]);
}

PageSlot108 page_attach_slot(OpaquePageLead* host) {
  void* const* table = static_cast<void* const*>(host->vtable);
  return reinterpret_cast<PageSlot108>(table[66]);
}

ModeSlot7c mode_report_slot(OpaqueGameModeManager* manager) {
  void* const* table = static_cast<void* const*>(manager->vtable);
  return reinterpret_cast<ModeSlot7c>(table[31]);
}

OpaqueTextBuffer report_buffer() {
  OpaqueTextBuffer buffer = {g_text_01667bac, g_text_01667bac, g_text_01667bae};
  return buffer;
}

void release_report(OpaqueTextBuffer* buffer) {
  if (guard_span(buffer) <= 2) {
    return;
  }
  if (buffer->begin == nullptr) {
    return;
  }
  unresolved_00f47380(const_cast<std::uint16_t*>(buffer->begin));
}

void emit_report(void* context, OpaqueTextBuffer* buffer) {
  OpaqueGameModeManager* const mode = unresolved_0067dcd0();
  mode_report_slot(mode)(mode, context, buffer);
}

void emit_and_release(void* context) {
  OpaqueTextBuffer buffer = report_buffer();
  emit_report(context, &buffer);
  release_report(&buffer);
}

void emit_and_discard(void* context) {
  OpaqueTextBuffer buffer = report_buffer();
  emit_report(context, &buffer);
  unresolved_00933960(&buffer);
}

bool probe_property(OpaquePropertyList* list, std::uint32_t key,
                    std::uint16_t tag, OpaqueProperty** slot) {
  *slot = nullptr;
  if (list == nullptr) {
    return false;
  }
  if (!list_probe_slot(list)(list, key, slot)) {
    return false;
  }
  if ((*slot)->field12 != tag) {
    return false;
  }
  return true;
}

bool read_float_property(OpaquePropertyList* list, std::uint32_t key,
                         OpaqueProperty** slot, float* out) {
  if (!probe_property(list, key, 0x0dU, slot)) {
    return false;
  }
  *out = *unresolved_0041ea70(*slot);
  return true;
}

bool read_byte_property(OpaquePropertyList* list, std::uint32_t key,
                        OpaqueProperty** slot, std::uint8_t* out) {
  if (!probe_property(list, key, 0x01U, slot)) {
    return false;
  }
  *out = *unresolved_0041e920(*slot);
  return true;
}

bool read_index_property(OpaquePropertyList* list, std::uint32_t key,
                         OpaqueProperty** slot, std::uint32_t* out) {
  if (!probe_property(list, key, 0x09U, slot)) {
    return false;
  }
  *out = *unresolved_0041e990(*slot);
  return true;
}

bool read_count_property(OpaquePropertyList* list, std::uint32_t key,
                         OpaqueProperty** slot, std::uint32_t* out) {
  if (!probe_property(list, key, 0x0aU, slot)) {
    return false;
  }
  *out = *unresolved_0041ea00(*slot);
  return true;
}

}

extern std::uint16_t g_text_01667bac[1] = {0U};
extern std::uint16_t g_text_01667bae[1] = {0U};
extern float g_float_013eb95c = 3.0F;
extern float g_float_014854c4 = -3.0F;
extern float g_float_01485720 = 1.0F;
extern OpaqueApp* g_dword_015fd918 = nullptr;

extern "C" std::uint32_t PKG_PALETTE_W11_THISCALL
palette_w11_resolve_link_tail_005c2e00(OpaqueLink* self) {
  if (self->field6c == nullptr) {
    return 0U;
  }
  OpaqueLink* node = self;
  for (;;) {
    OpaqueLinkInner* const inner = static_cast<OpaqueLinkInner*>(node->field6c);
    if (node->field9c == nullptr) {
      return inner->field58;
    }
    OpaqueLink* const next = static_cast<OpaqueLink*>(node->field9c);
    if (unresolved_005c9830(next) == nullptr) {
      return inner->field58;
    }
    node = unresolved_005c9830(next);
    if (node->field6c == nullptr) {
      return 0U;
    }
  }
}

extern "C" void PKG_PALETTE_W11_THISCALL
palette_w11_release_page_hold_005c7320(OpaquePageHost* self) {
  if (self->field14 != nullptr) {
    void* const manager = unresolved_00401020();
    unresolved_005f0a60(manager, self->field14);
    if (self->field14 != nullptr) {
      OpaquePageLead* const held = self->field14;
      self->field14 = nullptr;
      void* const* const table = static_cast<void* const*>(held->vtable);
      reinterpret_cast<ReleaseSlot01>(table[1])(held);
    }
  }
  if (self->field18 != nullptr) {
    page_attach_slot(self->field18)(self->field18, &self->field08);
  }
}

extern "C" bool PKG_PALETTE_W11_THISCALL
palette_w11_walk_has_leaf_005c7c10(OpaqueWalkIndex* self) {
  OpaqueRootList* const root = self->field0c;
  if (self->field10 >= word_span(root->field10, root->field0c)) {
    return false;
  }
  for (;;) {
    OpaqueCategoryList* const category =
        unresolved_005c5de0(root, self->field10);
    if (self->field14 >= word_span(category->field38, category->field34)) {
      goto after_middle;
    }
    for (;;) {
      OpaquePageList* const page = unresolved_005cae30(category, self->field14);
      if (self->field18 >= word_span(page->field10, page->field0c)) {
        break;
      }
      for (;;) {
        OpaqueEntryList* const entry = unresolved_005c1ce0(page, self->field18);
        if (self->field1c < word_span(entry->field74, entry->field70)) {
          return true;
        }
        ++self->field18;
        self->field1c = 0;
        if (self->field18 >= word_span(page->field10, page->field0c)) {
          break;
        }
      }
      ++self->field14;
      self->field18 = 0;
      if (self->field14 >= word_span(category->field38, category->field34)) {
        break;
      }
    }
  after_middle:
    self->field14 = 0;
    if (self->field18 >= word_span(category->field10, category->field0c)) {
      goto advance;
    }
    for (;;) {
      OpaqueEntryList* const entry =
          unresolved_005c1ce0(category, self->field18);
      if (self->field1c < word_span(entry->field74, entry->field70)) {
        return true;
      }
      ++self->field18;
      self->field1c = 0;
      if (self->field18 >= word_span(category->field10, category->field0c)) {
        break;
      }
    }
  advance:
    ++self->field10;
    self->field18 = 0;
    if (self->field10 >= word_span(root->field10, root->field0c)) {
      break;
    }
  }
  return false;
}

extern "C" void PKG_PALETTE_W11_THISCALL palette_w11_fill_node_array_005c7ff0(
    OpaquePageBuild* self, const std::uint32_t* expected, void* context,
    void* extra) {
  OpaquePropertyList* list = nullptr;
  OpaquePropertyList* const manager = unresolved_0067de30();
  if (list != nullptr) {
    list_release_slot(list)(list);
    list = nullptr;
  }
  const std::uint32_t* const seed = static_cast<const std::uint32_t*>(context);
  list = list_open_slot(manager)(manager, seed[0], seed[2], &list);
  if (list == nullptr) {
    return;
  }

  std::uint32_t probe_id = 0U;
  if (!unresolved_006a12a0(list, 0x1f7d3cf3U, &probe_id)) {
    emit_and_release(context);
  }

  if (probe_id != *expected) {
    list_release_slot(list)(list);
    return;
  }

  std::uint32_t limit = 0U;
  std::uint32_t offset = 0U;
  std::uint32_t* grid = nullptr;
  std::uint32_t rows = 0U;
  std::uint32_t* columns = nullptr;
  std::uint32_t lines = 0U;
  std::uint32_t* indices = nullptr;
  std::uint32_t threshold = 0U;
  const OpaqueApp* const app = g_dword_015fd918;
  unresolved_006a0ae0(list, 0xeeead734U, &limit,
                      reinterpret_cast<OpaqueResourceKey*>(&offset));
  unresolved_006a07d0(reinterpret_cast<OpaquePropertyList*>(self), 0xf8e99c4fU,
                      &rows, &columns);
  unresolved_006a07d0(list, 0x22c47931U, &lines, &indices);
  if (app->field3c->field118 != 0U) {
    unresolved_00410370(list, 0x5383435U, &threshold);
  }
  if (limit == rows) {
    emit_and_release(context);
  }
  if (limit != lines) {
    if (lines < limit) {
      limit = lines;
    }
    emit_and_release(context);
  }
  grid = columns;

  for (std::uint32_t index = 0U; index < limit; ++index) {
    const std::int32_t column = static_cast<std::int32_t>(columns[index]);
    const std::int32_t row = static_cast<std::int32_t>(indices[index]);
    if (column < 0 || column >= static_cast<std::int32_t>(self->field50)) {
      emit_and_release(context);
      continue;
    }
    if (row < 0 || row >= static_cast<std::int32_t>(self->field54)) {
      emit_and_release(context);
      continue;
    }
    const std::uint32_t flat = static_cast<std::uint32_t>(column) +
                               static_cast<std::uint32_t>(row) * self->field50;
    OpaqueNode* const held = self->field70[flat];
    if (held != nullptr) {
      node_release_slot(held)(held);
      if (held->field48 >= threshold) {
        if (held->field48 > threshold) {
          node_drop_slot(held)(held);
        } else {
          emit_and_discard(context);
          node_drop_slot(held)(held);
        }
        continue;
      }
    }
    void* const raw = unresolved_00f473a0(0x54U, 0x13eb430U, 0U, 0U, 0U, 0U);
    OpaqueNode* created = nullptr;
    if (raw != nullptr) {
      created = unresolved_005c66a0(static_cast<OpaqueNode*>(raw));
    }
    if (created != nullptr) {
      node_release_slot(created)(created);
    }
    if (!unresolved_005c6810(created,
                             reinterpret_cast<std::uint8_t*>(grid) + offset,
                             threshold, extra)) {
      emit_and_discard(context);
    } else {
      unresolved_005766e0(self->field70 + flat, created);
    }
    node_drop_slot(created)(created);
    if (held != nullptr) {
      node_drop_slot(held)(held);
    }
  }

  list_release_slot(list)(list);
}

extern "C" bool PKG_PALETTE_W11_THISCALL palette_w11_load_page_state_005c85d0(
    OpaquePageBuild* self, OpaqueProperty** probe_slot,
    OpaqueProperty** hold_slot) {
  OpaquePropertyList* list = nullptr;
  OpaquePropertyList* const manager = unresolved_0067de30();
  if (list != nullptr) {
    list_release_slot(list)(list);
    list = nullptr;
  }
  list = list_open_slot(manager)(
      manager,
      reinterpret_cast<std::uint32_t>(
          reinterpret_cast<std::uintptr_t>(hold_slot[0])),
      reinterpret_cast<std::uint32_t>(
          reinterpret_cast<std::uintptr_t>(hold_slot[2])),
      &list);
  if (list == nullptr) {
    return false;
  }

  OpaquePropertyList* follow = nullptr;

  read_float_property(list, 0x21953e9U, probe_slot, &self->field14.as_float);
  read_float_property(list, 0x21953eaU, probe_slot, &self->field18.as_float);
  read_float_property(list, 0xb0a1610aU, probe_slot, &self->field28);
  read_float_property(list, 0xb0a16109U, probe_slot, &self->field24);
  read_float_property(list, 0xb0a1610dU, probe_slot, &self->field20.as_float);
  read_float_property(list, 0xb0a1610cU, probe_slot, &self->field1c.as_float);

  self->field48.bytes.byte48 = 0U;
  read_byte_property(list, 0x5adc53bU, probe_slot, &self->field48.bytes.byte48);

  OpaqueFloat4 extents = {0.0F, 0.0F, 0.0F, 0.0F};
  if (unresolved_006a1160(list, 0x5adc149U, &extents)) {
    self->field38.as_float = extents.field00;
    self->field30 = extents.field04;
    self->field3c = extents.field08;
    self->field34.as_float = extents.field0c;
    std::uint32_t follow_bits = 0U;
    std::memcpy(&follow_bits, &self->field3c, sizeof(follow_bits));
    follow = reinterpret_cast<OpaquePropertyList*>(
        static_cast<std::uintptr_t>(follow_bits));
  }

  read_float_property(follow, 0x5b9a649U, probe_slot, &self->field4c.as_float);
  read_float_property(follow, 0x5adc172U, probe_slot, &self->field40);

  self->field44 = g_float_01485720;
  read_float_property(list, 0x5adc18dU, probe_slot, &self->field44);
  read_byte_property(list, 0x5b5566eU, probe_slot, &self->field48.bytes.byte49);
  read_byte_property(list, 0x5b55d89U, probe_slot, &self->field48.bytes.byte4a);
  read_index_property(list, 0x30a95517U, probe_slot, &self->field50);
  read_index_property(list, 0x33a8ec2U, probe_slot, &self->field54);

  unresolved_006a1250(list, 0xc84067f7U, &self->field64);

  read_count_property(follow, 0x9591f67U, probe_slot, &self->field58);
  read_index_property(follow, 0x1b8716d6U, probe_slot, &self->field5c);

  if (hold_slot != nullptr) {
    self->field0c = reinterpret_cast<std::uint32_t>(hold_slot);
  } else {
    unresolved_006a12a0(list, 0x35b12c24U, &self->field0c);
  }
  read_byte_property(follow, 0x52c798eU, probe_slot, &self->field2c);
  read_byte_property(follow, 0x56e8657U, probe_slot, &self->field2d);

  const std::int32_t cells =
      static_cast<std::int32_t>(self->field54 * self->field50);
  std::int32_t filled = 0;
  if (cells > 0) {
    do {
      OpaqueNode** const cursor = self->field74;
      OpaqueNode* grown = nullptr;
      if (cursor < self->field78) {
        self->field74 = cursor + 1;
        if (cursor != nullptr) {
          *cursor = nullptr;
        }
      } else {
        unresolved_005c8480(self->field70, cursor, &grown);
        if (grown != nullptr) {
          node_drop_slot(grown)(grown);
        }
      }
      ++filled;
    } while (filled < static_cast<std::int32_t>(self->field54 * self->field50));
  }
  static_cast<void>(cells);

  if (list != nullptr) {
    list_release_slot(list)(list);
  }
  return true;
}

extern "C" std::uint32_t PKG_PALETTE_W11_THISCALL
palette_w11_place_page_nodes_005ca9f0(OpaquePageBuild* self) {
  OpaqueNode* const* const pages =
      reinterpret_cast<OpaqueNode* const* const>(self->field48.as_node);
  OpaqueNode* const* const page_limit =
      reinterpret_cast<OpaqueNode* const* const>(self->field4c.as_node);
  OpaqueNode* const* const id_list =
      reinterpret_cast<OpaqueNode* const* const>(self->field34.as_node);
  OpaqueNode* const* const id_limit =
      reinterpret_cast<OpaqueNode* const* const>(self->field38.as_node);

  if ((byte_span(page_limit, pages) & 0xfffffffcU) != 0U) {
    const std::uint32_t count = byte_span(page_limit, pages) >> 2;
    std::uint32_t index = 0U;
    if (count != 0U) {
      do {
        const std::uint32_t active = ninth_of(index) == self->field60 ? 1U : 0U;
        OpaqueModel* const model = node_model_slot(pages[index])(pages[index]);
        model_layer_slot(model)(model, active, 1U);
        ++index;
      } while (index < count);
    }
  }

  std::int32_t slot = -1;
  const std::int32_t slots = word_span(id_limit, id_list);
  if (slots > 0) {
    std::int32_t scan = 0;
    while (scan < slots) {
      if (reinterpret_cast<std::uint32_t>(id_list[scan]) ==
          self->field64.word00) {
        slot = scan;
        break;
      }
      ++scan;
    }
  }

  const bool active =
      ninth_of(static_cast<std::uint32_t>(slot)) == self->field60;
  const bool usable = self->field14.as_node != nullptr &&
                      self->field18.as_node != nullptr &&
                      self->field20.as_node != nullptr;
  OpaqueNode* const pair = self->field20.as_node + 1;

  if (active) {
    if (self->field1c.as_node != nullptr) {
      node_layer_slot(self->field1c.as_node)(self->field1c.as_node, 0U, 1U);
    }
    if (usable) {
      node_layer_slot(pair)(pair, 1U, 1U);
      node_layer_slot(self->field14.as_node)(self->field14.as_node, 1U, 1U);
      node_layer_slot(self->field18.as_node)(self->field18.as_node, 1U, 1U);

      const std::int32_t page = unresolved_005ca9c0(self);
      OpaqueModel* const model = node_model_slot(pages[page])(pages[page]);
      OpaqueModel* const blend =
          node_model_slot(self->field14.as_node)(self->field14.as_node);
      const float* const model_box = model_bounds_slot(model)(model);
      const float* const blend_box = model_bounds_slot(blend)(blend);
      float pad = (model_box[2] - model_box[0]) + g_float_013eb95c;

      float shifted[2] = {0.0F, 0.0F};
      model_shift_slot(model)(model, g_float_014854c4, 0.0F, shifted);
      model_blend_slot(blend)(blend, shifted[0], shifted[1], &pad);

      float staged[2] = {0.0F, 0.0F};
      model_shift_slot(model)(model, pad, 0.0F, staged);
      model_blend_slot(blend)(blend, staged[0], staged[1], &pad);

      const float* const first =
          node_rect_slot(self->field14.as_node)(self->field14.as_node);
      const float first_rect[4] = {0.0F, first[1], 0.0F, first[3]};
      node_apply_slot(self->field14.as_node)(self->field14.as_node, first_rect);

      const float* const second =
          node_rect_slot(self->field18.as_node)(self->field18.as_node);
      const float second_rect[4] = {pad, second[1], blend_box[2] - blend_box[0],
                                    second[3]};
      node_apply_slot(self->field18.as_node)(self->field18.as_node,
                                             second_rect);

      const float* const third = node_rect_slot(pair)(pair);
      const float third_rect[4] = {pad, third[1], pad, third[3]};
      node_apply_slot(pair)(pair, third_rect);
    }
  } else {
    if (self->field1c.as_node != nullptr) {
      node_layer_slot(self->field1c.as_node)(self->field1c.as_node, 1U, 1U);
    }
    if (self->field14.as_node != nullptr) {
      node_layer_slot(self->field14.as_node)(self->field14.as_node, 0U, 1U);
    }
    if (self->field18.as_node != nullptr) {
      node_layer_slot(self->field18.as_node)(self->field18.as_node, 0U, 1U);
    }
    if (self->field20.as_node != nullptr) {
      node_layer_slot(pair)(pair, 0U, 1U);
    }
  }

  std::uint32_t result = 0U;
  if (self->field64.word00 != 0U) {
    OpaqueNode* const anchor = reinterpret_cast<OpaqueNode*>(
        reinterpret_cast<std::uintptr_t>(&self->field64));
    result = unresolved_005c2ec0(anchor, active ? 1U : 0U);
  }
  return result;
}

}
