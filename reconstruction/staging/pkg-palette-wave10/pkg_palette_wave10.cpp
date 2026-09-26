#include "pkg_palette_wave10.hpp"

namespace openspore::reconstruction::pkg_palette_wave10 {
namespace {

std::int32_t byte_span(const void* end, const void* begin) {
  return static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(end) -
                                   reinterpret_cast<std::uintptr_t>(begin));
}

PropertyListSlot04 property_slot04(OpaquePropertyList* list) {
  void* const* table = static_cast<void* const*>(list->vtable);
  return reinterpret_cast<PropertyListSlot04>(table[1]);
}

PropertyListSlot24 property_slot24(OpaquePropertyList* list) {
  void* const* table = static_cast<void* const*>(list->vtable);
  return reinterpret_cast<PropertyListSlot24>(table[9]);
}

PropertyListSlot2c property_slot2c(OpaquePropertyList* list) {
  void* const* table = static_cast<void* const*>(list->vtable);
  return reinterpret_cast<PropertyListSlot2c>(table[11]);
}

PageNavSlot7c nav_slot7c(OpaquePageNav* nav) {
  void* const* table = static_cast<void* const*>(nav->vtable);
  return reinterpret_cast<PageNavSlot7c>(table[31]);
}

PageTextSlot80 text_slot80(OpaquePageText* text) {
  void* const* table = static_cast<void* const*>(text->vtable);
  return reinterpret_cast<PageTextSlot80>(table[32]);
}

ElementSlot28 element_slot28(OpaqueElement* element) {
  void* const* table = static_cast<void* const*>(element->vtable);
  return reinterpret_cast<ElementSlot28>(table[10]);
}

ElementSlot38 element_slot38(OpaqueElement* element) {
  void* const* table = static_cast<void* const*>(element->vtable);
  return reinterpret_cast<ElementSlot38>(table[14]);
}

ElementSlot6c element_slot6c(OpaqueElement* element) {
  void* const* table = static_cast<void* const*>(element->vtable);
  return reinterpret_cast<ElementSlot6c>(table[27]);
}

const std::uint16_t g_text_013f7c30_data[] = {0x0025U, 0x0069U, 0x002fU,
                                              0x0025U, 0x0069U, 0x0000U};

}

extern const std::uint16_t* g_text_013f7c30 = g_text_013f7c30_data;
extern std::uint16_t g_text_01667bac[1] = {0U};
extern OpaqueTextBuffer g_text_01667bac_buffer = {
    g_text_01667bac, g_text_01667bac, g_text_01667bac + 1};
extern std::uint32_t g_word_01514dd0 = 0x406b0100U;
extern float g_float_01486110 = 5.0F;
extern OpaqueApp* g_dword_015fd918 = nullptr;

extern "C" void PKG_PALETTE_W10_THISCALL
pkg_palette_w10_005c0a60(OpaquePage* self, std::uint32_t argument) {
  static_cast<void>(argument);
  if (self->field14 == nullptr) {
    return;
  }
  if (self->field18 == nullptr) {
    return;
  }
  OpaquePageCategory* const category = self->field14;
  const std::int32_t slots =
      byte_span(category->field8c, category->field88) >> 3;
  std::int32_t selected = 0;
  std::int32_t total = 0;
  if (slots > 0) {
    for (std::int32_t index = 0; index < slots; ++index) {
      if (unresolved_005c29c0(category, static_cast<std::uint32_t>(index))) {
        if (index == category->fielda0) {
          selected = total;
        }
        ++total;
      }
    }
  }
  if (total >= 2) {
    if (self->field1c != nullptr) {
      nav_slot7c(self->field1c)(self->field1c, 1U, 1U);
    }
    if (self->field20 == selected && self->field24 == total) {
      return;
    }
    OpaqueTextBuffer buffer = g_text_01667bac_buffer;
    unresolved_0041e050(&buffer, g_text_013f7c30,
                        static_cast<std::int32_t>(selected + 1), total);
    text_slot80(self->field18)(self->field18, buffer.begin);
    const std::uint32_t span = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(buffer.end) -
        reinterpret_cast<std::uintptr_t>(buffer.begin));
    self->field20 = selected;
    self->field24 = total;
    if ((span & 0xfffffffeU) <= 2U) {
      return;
    }
    if (buffer.begin == nullptr) {
      return;
    }
    unresolved_00f47380(const_cast<std::uint16_t*>(buffer.begin));
    return;
  }
  if (self->field1c != nullptr) {
    nav_slot7c(self->field1c)(self->field1c, 1U, 0U);
  }
}

extern "C" bool PKG_PALETTE_W10_THISCALL pkg_palette_w10_005c1e20(
    OpaqueEntry* self, const OpaqueResourceKey* key, std::uint32_t argument) {
  static_cast<void>(argument);
  OpaquePropertyList* list = nullptr;
  const std::uint32_t limit = key->word08 != 0U ? key->word08 : g_word_01514dd0;
  OpaquePropertyList* const manager = unresolved_0067de30();
  if (list != nullptr) {
    property_slot04(list)(list);
    list = nullptr;
  }
  list = property_slot2c(manager)(manager, key->word00, limit, &list);
  if (list == nullptr) {
    return false;
  }
  self->field74 = key->word00;
  OpaqueProperty* property = nullptr;
  if (property_slot24(list)(list, 0x337bf31U, &property) &&
      property->field12 == 1U) {
    self->field50 = *unresolved_0041e920(property);
  }
  property = nullptr;
  if (list != nullptr) {
    if (property_slot24(list)(list, 0x88025f5U, &property) &&
        property->field12 == 1U) {
      self->field70 = *unresolved_0041e920(property);
    }
    unresolved_006a12a0(list, 0xd20d4636U, &self->field54);
  }
  property = nullptr;
  if (list != nullptr) {
    if (property_slot24(list)(list, 0x3e0a564U, &property) &&
        property->field12 == 10U) {
      self->field58 = *unresolved_0041ea00(property);
    }
  }
  OpaqueResourceKey group = {0U, 0U, 0U};
  unresolved_006a1250(list, 0xb35d7835U, &group);
  self->field78 = group.word00;
  unresolved_006a1250(list, 0xe6a31466U, &self->field7c);
  std::uint32_t count = 0U;
  unresolved_006a0ae0(list, 0x44f6c09U, &count,
                      reinterpret_cast<OpaqueResourceKey*>(&self->field88));
  property = nullptr;
  if (list != nullptr) {
    if (property_slot24(list)(list, 0x35eeb8b5U, &property) &&
        property->field12 == 10U) {
      self->field4c = *unresolved_0041ea00(property);
    }
  }
  if (group.word08 != 0U) {
    self->field48 = group.word08;
  } else {
    unresolved_006a12a0(list, 0x9a6aaae5U, &self->field48);
  }
  unresolved_006a1360(list, 0x2e1942a8U, &self->field5c);
  if (list != nullptr) {
    property_slot04(list)(list);
  }
  return true;
}

extern "C" void PKG_PALETTE_W10_THISCALL
pkg_palette_w10_005c3000(OpaquePalette* self) {
  const std::uint32_t pages = static_cast<std::uint32_t>(
      byte_span(self->field78, self->field74) & 0xfffffffcU);
  bool stacked = pages >= 4U;
  const std::uint32_t feature =
      reinterpret_cast<std::uintptr_t>(unresolved_008105b0(0x5d3f56bU, 1U));
  OpaquePaletteGroup* const group = self->field6c;
  const std::uint32_t group_bytes = static_cast<std::uint32_t>(
      byte_span(group->field10, group->field0c) & 0xfffffffcU);
  const bool wide = group_bytes > 4U || (group->field70 != 0U);
  OpaqueApp* const app = g_dword_015fd918;
  if (app->field3c->field118 != 0U) {
    if (unresolved_005c2aa0(self) < 1) {
      stacked = false;
    }
  }
  float offset = g_float_01486110;
  if (stacked && self->field20 != nullptr) {
    offset = element_slot38(self->field20)(self->field20)[3] + g_float_01486110;
  }
  OpaqueRectF rect = {0.0F, 0.0F, 0.0F, 0.0F};
  if (feature != 0U && self->field24 != nullptr) {
    const float* const source = element_slot38(self->field24)(self->field24);
    rect.field00 = source[0];
    rect.field08 = source[2];
    rect.field04 = offset;
    rect.field0c = (source[3] - source[1]) + offset;
    element_slot6c(self->field24)(self->field24, &rect);
    offset = rect.field0c + g_float_01486110;
  }
  if (self->field28 == nullptr) {
    return;
  }
  const float* const body = element_slot38(self->field28)(self->field28);
  rect.field00 = body[0];
  rect.field04 = body[1];
  rect.field08 = body[2];
  rect.field0c = body[3];
  rect.field04 = offset;
  if (wide && self->field1c != nullptr) {
    const float* const host = element_slot38(self->field1c)(self->field1c);
    rect.field0c = host[1] - g_float_01486110;
  } else if (self->field2c != nullptr) {
    const float* const tail = element_slot38(self->field2c)(self->field2c);
    rect.field0c = tail[3] - tail[1] - g_float_01486110;
  }
  element_slot6c(self->field28)(self->field28, &rect);
}

extern "C" void PKG_PALETTE_W10_THISCALL
pkg_palette_w10_005c3cb0(OpaquePalette* self, std::uint32_t selection) {
  const std::uint32_t previous = self->fieldac;
  const std::int32_t previous_index = unresolved_005c2a30(previous);
  const std::int32_t next_index = unresolved_005c2a30(selection);
  self->fieldac = selection;
  if (next_index < 0 ||
      next_index >= (byte_span(self->field78, self->field74) >> 2)) {
    return;
  }
  if ((byte_span(self->field78, self->field74) >> 2) != 0) {
    if (previous_index != -1) {
      element_slot28(self->field74[previous_index])(
          self->field74[previous_index], 4U, 0U);
    }
    element_slot28(self->field74[next_index])(self->field74[next_index], 4U,
                                              1U);
  }
  if (previous != self->fieldac) {
    unresolved_005c2590(self, next_index / self->fieldb0);
    unresolved_004a88d0(0x38eb66f8U);
    OpaquePageCategory* const category =
        unresolved_005c2e50(self, self->fielda0);
    if (unresolved_005c8fc0(category) != self->fieldac) {
      unresolved_005c3bd0(self, unresolved_005c29e0(self, self->fieldac));
    }
  }
}

}
