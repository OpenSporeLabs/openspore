#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "pkg_palette_wave10.hpp"

namespace {

const std::size_t kSlots = 40;

void* g_function_table[kSlots];

template <typename Function>
void* function_data(Function function) {
  return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(function));
}

struct OpaqueCategorySlot {
  OpaqueElement* first;
  std::uint32_t second;
};

}

namespace openspore::reconstruction::pkg_palette_wave10 {

namespace {

int category_probe_calls;
std::uint32_t category_probe_index;
std::uint8_t category_probe_result[8];

int format_calls;
std::uint32_t format_first;
std::int32_t format_second;
std::int32_t format_third;
std::uint16_t format_store[16];
std::size_t format_width;

int release_text_calls;
const std::uint16_t* release_text_pointer;

int nav_calls;
OpaquePageNav* nav_receiver;
std::uint32_t nav_first;
std::uint32_t nav_second;

int text_calls;
OpaquePageText* text_receiver;
const std::uint16_t* text_pointer;

int list_release_calls;
OpaquePropertyList* list_release_receiver;

int property_get_calls;
std::uint32_t property_get_key;
std::uint16_t property_get_tag;

int value8_calls;
int value32_calls;
std::uint8_t value8_payload;
std::uint32_t value32_payload;

int key_instance_calls;
std::uint32_t key_instance_key;
std::uint32_t* key_instance_out;
std::uint32_t key_instance_payload;

int group_key_calls;
std::uint32_t group_key_key;
OpaqueResourceKey* group_key_out;
std::uint32_t group_key_word00;
std::uint32_t group_key_word04;
std::uint32_t group_key_word08;

int array_key_calls;
std::uint32_t array_key_key;
std::uint32_t* array_key_count;
OpaqueResourceKey* array_key_out;

int text_key_calls;
std::uint32_t text_key_key;

int feature_calls;
std::uint32_t feature_first;
std::uint32_t feature_second;
OpaqueToggle* feature_result;

int dedupe_calls;
int dedupe_result;

int index_lookup_calls;
std::uint32_t index_lookup_value;
int index_lookup_result[2];
int index_lookup_step;

int row_calls;
OpaquePalette* row_receiver;
std::int32_t row_value;

int event_calls;
std::uint32_t event_value;

OpaquePageCategory* category_at_result;

std::uint32_t category_id_result;
int category_id_calls;
OpaquePageCategory* category_id_receiver;

int index_of_calls;
OpaquePalette* index_of_receiver;
std::uint32_t index_of_value;
int index_of_result;

int commit_calls;
OpaquePalette* commit_receiver;
std::int32_t commit_value;

int element_rect_calls;
OpaqueElement* element_rect_receiver;
OpaqueRectF element_rect_value;
int element_place_calls;
OpaqueElement* element_place_receiver;
OpaqueRectF element_place_value;
OpaqueElement* element_place_history[8];
OpaqueRectF element_place_history_value[8];
int element_mark_calls;
OpaqueElement* element_mark_receiver;
std::uint32_t element_mark_first;
std::uint32_t element_mark_second;
OpaqueElement* element_mark_history[4];
std::uint32_t element_mark_history_first[4];
std::uint32_t element_mark_history_second[4];

OpaquePropertyList* sublist_result;
std::uint32_t sublist_key;
std::uint32_t sublist_limit;

OpaquePropertyList property_list;
OpaquePropertyList property_manager;
OpaqueProperty property_object;
OpaquePageText page_text;
OpaquePageNav page_nav;
OpaqueElement lead_element;
OpaqueElement title_element;
OpaqueElement body_element;
OpaqueElement tail_element;
OpaqueElement host_element;
OpaquePageCategory page_category;
OpaquePaletteGroup palette_group;
OpaqueAppProps app_props;
OpaqueApp app_object;

}

extern "C" bool PKG_PALETTE_W10_THISCALL
unresolved_005c29c0(OpaquePageCategory* receiver, std::uint32_t index) {
  static_cast<void>(receiver);
  ++category_probe_calls;
  category_probe_index = index;
  return index < 8U ? category_probe_result[index] != 0U : false;
}

extern "C" OpaqueTextBuffer* PKG_PALETTE_W10_CDECL
unresolved_0041e050(OpaqueTextBuffer* buffer, const std::uint16_t* format,
                    std::int32_t first, std::int32_t second) {
  static_cast<void>(format);
  ++format_calls;
  format_first = static_cast<std::uint32_t>(first);
  format_second = second;
  format_third = first;
  buffer->begin = format_store;
  buffer->cursor = format_store + format_width;
  buffer->end = format_store + format_width;
  return buffer;
}

extern "C" void PKG_PALETTE_W10_CDECL unresolved_00f47380(void* pointer) {
  ++release_text_calls;
  release_text_pointer = static_cast<const std::uint16_t*>(pointer);
}

extern "C" OpaquePropertyList* PKG_PALETTE_W10_CDECL unresolved_0067de30() {
  return &property_manager;
}

extern "C" const std::uint8_t* PKG_PALETTE_W10_THISCALL
unresolved_0041e920(OpaqueProperty* receiver) {
  static_cast<void>(receiver);
  ++value8_calls;
  return &value8_payload;
}

extern "C" const std::uint32_t* PKG_PALETTE_W10_THISCALL
unresolved_0041ea00(OpaqueProperty* receiver) {
  static_cast<void>(receiver);
  ++value32_calls;
  return &value32_payload;
}

extern "C" void PKG_PALETTE_W10_CDECL unresolved_006a12a0(
    OpaquePropertyList* list, std::uint32_t key, std::uint32_t* out) {
  static_cast<void>(list);
  ++key_instance_calls;
  key_instance_key = key;
  key_instance_out = out;
  *out = key_instance_payload;
}

extern "C" void PKG_PALETTE_W10_CDECL unresolved_006a1250(
    OpaquePropertyList* list, std::uint32_t key, OpaqueResourceKey* out) {
  static_cast<void>(list);
  ++group_key_calls;
  group_key_key = key;
  group_key_out = out;
  out->word00 = group_key_word00;
  out->word04 = group_key_word04;
  out->word08 = group_key_word08;
}

extern "C" void PKG_PALETTE_W10_CDECL
unresolved_006a0ae0(OpaquePropertyList* list, std::uint32_t key,
                    std::uint32_t* count, OpaqueResourceKey* out) {
  static_cast<void>(list);
  ++array_key_calls;
  array_key_key = key;
  array_key_count = count;
  array_key_out = out;
}

extern "C" void PKG_PALETTE_W10_CDECL unresolved_006a1360(
    OpaquePropertyList* list, std::uint32_t key, OpaqueLocalizedText* out) {
  static_cast<void>(list);
  static_cast<void>(out);
  ++text_key_calls;
  text_key_key = key;
}

extern "C" OpaqueToggle* PKG_PALETTE_W10_THISCALL
unresolved_008105b0(std::uint32_t first, std::uint32_t second) {
  ++feature_calls;
  feature_first = first;
  feature_second = second;
  return feature_result;
}

extern "C" int PKG_PALETTE_W10_THISCALL
unresolved_005c2aa0(OpaquePalette* receiver) {
  static_cast<void>(receiver);
  ++dedupe_calls;
  return dedupe_result;
}

extern "C" int PKG_PALETTE_W10_STDCALL
unresolved_005c2a30(std::uint32_t value) {
  const int step = index_lookup_step < 2 ? index_lookup_step : 1;
  ++index_lookup_step;
  ++index_lookup_calls;
  index_lookup_value = value;
  return index_lookup_result[step];
}

extern "C" void PKG_PALETTE_W10_THISCALL
unresolved_005c2590(OpaquePalette* receiver, std::int32_t value) {
  ++row_calls;
  row_receiver = receiver;
  row_value = value;
}

extern "C" void PKG_PALETTE_W10_CDECL unresolved_004a88d0(std::uint32_t value) {
  ++event_calls;
  event_value = value;
}

extern "C" OpaquePageCategory* PKG_PALETTE_W10_THISCALL
unresolved_005c2e50(OpaquePalette* receiver, std::int32_t value) {
  static_cast<void>(receiver);
  static_cast<void>(value);
  return category_at_result;
}

extern "C" std::uint32_t PKG_PALETTE_W10_THISCALL
unresolved_005c8fc0(OpaquePageCategory* receiver) {
  ++category_id_calls;
  category_id_receiver = receiver;
  return category_id_result;
}

extern "C" int PKG_PALETTE_W10_THISCALL
unresolved_005c29e0(OpaquePalette* receiver, std::uint32_t value) {
  ++index_of_calls;
  index_of_receiver = receiver;
  index_of_value = value;
  return index_of_result;
}

extern "C" bool PKG_PALETTE_W10_THISCALL
unresolved_005c3bd0(OpaquePalette* receiver, std::int32_t value) {
  ++commit_calls;
  commit_receiver = receiver;
  commit_value = value;
  return true;
}

namespace {

void list_release_stub(OpaquePropertyList* receiver) {
  ++list_release_calls;
  list_release_receiver = receiver;
}

bool property_get_stub(OpaquePropertyList* receiver, std::uint32_t key,
                       OpaqueProperty** out) {
  static_cast<void>(receiver);
  ++property_get_calls;
  property_get_key = key;
  *out = &property_object;
  property_object.field12 = property_get_tag;
  return true;
}

OpaquePropertyList* property_sublist_stub(OpaquePropertyList* receiver,
                                          std::uint32_t key,
                                          std::uint32_t limit,
                                          OpaquePropertyList** out) {
  static_cast<void>(receiver);
  sublist_key = key;
  sublist_limit = limit;
  *out = sublist_result;
  return sublist_result;
}

void nav_stub(OpaquePageNav* receiver, std::uint32_t first,
              std::uint32_t second) {
  ++nav_calls;
  nav_receiver = receiver;
  nav_first = first;
  nav_second = second;
}

void text_stub(OpaquePageText* receiver, const std::uint16_t* pointer) {
  ++text_calls;
  text_receiver = receiver;
  text_pointer = pointer;
}

void mark_stub(OpaqueElement* receiver, std::uint32_t first,
               std::uint32_t second) {
  ++element_mark_calls;
  element_mark_receiver = receiver;
  element_mark_first = first;
  element_mark_second = second;
  if (element_mark_calls <= 4) {
    element_mark_history[element_mark_calls - 1] = receiver;
    element_mark_history_first[element_mark_calls - 1] = first;
    element_mark_history_second[element_mark_calls - 1] = second;
  }
}

const float* rect_stub(OpaqueElement* receiver) {
  ++element_rect_calls;
  element_rect_receiver = receiver;
  return &element_rect_value.field00;
}

void place_stub(OpaqueElement* receiver, const OpaqueRectF* rect) {
  ++element_place_calls;
  element_place_receiver = receiver;
  element_place_value = *rect;
  if (element_place_calls <= 8) {
    element_place_history[element_place_calls - 1] = receiver;
    element_place_history_value[element_place_calls - 1] = *rect;
  }
}

void install_list_table(void** table) {
  std::memset(table, 0, sizeof(void*) * kSlots);
  table[1] = function_data(list_release_stub);
  table[9] = function_data(property_get_stub);
  table[11] = function_data(property_sublist_stub);
}

void install_element_table(void** table) {
  std::memset(table, 0, sizeof(void*) * kSlots);
  table[10] = function_data(mark_stub);
  table[14] = function_data(rect_stub);
  table[27] = function_data(place_stub);
}

void install_page_table(void** table) {
  std::memset(table, 0, sizeof(void*) * kSlots);
  table[31] = function_data(nav_stub);
  table[32] = function_data(text_stub);
}

void reset_ports() {
  category_probe_calls = 0;
  category_probe_index = 0U;
  format_calls = 0;
  format_first = 0U;
  format_second = 0;
  format_third = 0;
  format_width = 0U;
  release_text_calls = 0;
  release_text_pointer = nullptr;
  nav_calls = 0;
  nav_receiver = nullptr;
  nav_first = 0U;
  nav_second = 0U;
  text_calls = 0;
  text_receiver = nullptr;
  text_pointer = nullptr;
  list_release_calls = 0;
  list_release_receiver = nullptr;
  property_get_calls = 0;
  property_get_key = 0U;
  property_get_tag = 0U;
  value8_calls = 0;
  value32_calls = 0;
  key_instance_calls = 0;
  key_instance_key = 0U;
  key_instance_out = nullptr;
  key_instance_payload = 0U;
  group_key_calls = 0;
  group_key_key = 0U;
  group_key_out = nullptr;
  group_key_word00 = 0U;
  group_key_word04 = 0U;
  group_key_word08 = 0U;
  array_key_calls = 0;
  array_key_key = 0U;
  array_key_count = nullptr;
  array_key_out = nullptr;
  text_key_calls = 0;
  text_key_key = 0U;
  feature_calls = 0;
  feature_first = 0U;
  feature_second = 0U;
  feature_result = nullptr;
  dedupe_calls = 0;
  dedupe_result = 0;
  index_lookup_calls = 0;
  index_lookup_value = 0U;
  index_lookup_result[0] = 0;
  index_lookup_result[1] = 0;
  index_lookup_step = 0;
  row_calls = 0;
  row_receiver = nullptr;
  row_value = 0;
  event_calls = 0;
  event_value = 0U;
  category_at_result = nullptr;
  category_id_result = 0U;
  category_id_calls = 0;
  category_id_receiver = nullptr;
  index_of_calls = 0;
  index_of_receiver = nullptr;
  index_of_value = 0U;
  index_of_result = 0;
  commit_calls = 0;
  commit_receiver = nullptr;
  commit_value = 0;
  element_rect_calls = 0;
  element_rect_receiver = nullptr;
  element_rect_value = OpaqueRectF{0.0F, 0.0F, 0.0F, 0.0F};
  element_place_calls = 0;
  element_place_receiver = nullptr;
  element_place_value = OpaqueRectF{0.0F, 0.0F, 0.0F, 0.0F};
  for (std::size_t index = 0; index < 8; ++index) {
    element_place_history[index] = nullptr;
    element_place_history_value[index] = OpaqueRectF{0.0F, 0.0F, 0.0F, 0.0F};
  }
  element_mark_calls = 0;
  element_mark_receiver = nullptr;
  element_mark_first = 0U;
  element_mark_second = 0U;
  for (std::size_t index = 0; index < 4; ++index) {
    element_mark_history[index] = nullptr;
    element_mark_history_first[index] = 0U;
    element_mark_history_second[index] = 0U;
  }
  value8_payload = 0U;
  value32_payload = 0U;
  for (std::size_t index = 0; index < 8; ++index) {
    category_probe_result[index] = 0U;
  }
  g_word_01514dd0 = 0x406b0100U;
  g_float_01486110 = 5.0F;
}

void setup_page(OpaquePage* page, OpaqueCategorySlot* slots,
                std::size_t count) {
  std::memset(page, 0, sizeof(*page));
  std::memset(&page_category, 0, sizeof(page_category));
  std::memset(&page_text, 0, sizeof(page_text));
  std::memset(&page_nav, 0, sizeof(page_nav));
  install_page_table(g_function_table);
  page_text.vtable = g_function_table;
  page_nav.vtable = g_function_table;
  page_category.field88 = reinterpret_cast<OpaqueElement**>(slots);
  page_category.field8c = reinterpret_cast<OpaqueElement**>(slots) + count * 2;
  page->field14 = &page_category;
  page->field18 = &page_text;
  page->field1c = &page_nav;
}

void test_page_005c0a60_guards() {
  OpaquePage page{};
  OpaqueCategorySlot slots[4]{};
  setup_page(&page, slots, 4U);
  reset_ports();
  page.field14 = nullptr;
  pkg_palette_w10_005c0a60(&page, 0U);
  assert(nav_calls == 0 && category_probe_calls == 0 && format_calls == 0);

  setup_page(&page, slots, 4U);
  reset_ports();
  page.field18 = nullptr;
  pkg_palette_w10_005c0a60(&page, 0U);
  assert(nav_calls == 0 && category_probe_calls == 0 && format_calls == 0);
}

void test_page_005c0a60_few_pages() {
  OpaquePage page{};
  OpaqueCategorySlot slots[8]{};
  setup_page(&page, slots, 0U);
  reset_ports();
  pkg_palette_w10_005c0a60(&page, 7U);
  assert(category_probe_calls == 0);
  assert(nav_calls == 1);
  assert(nav_receiver == &page_nav);
  assert(nav_first == 1U && nav_second == 0U);
  assert(format_calls == 0 && text_calls == 0);

  setup_page(&page, slots, 4U);
  reset_ports();
  category_probe_result[0] = 1U;
  pkg_palette_w10_005c0a60(&page, 0U);
  assert(category_probe_calls == 4);
  assert(nav_calls == 1 && nav_second == 0U);
  assert(format_calls == 0);
  assert(page.field20 == 0 && page.field24 == 0);
}

void test_page_005c0a60_paged_text() {
  OpaquePage page{};
  OpaqueCategorySlot slots[8]{};
  setup_page(&page, slots, 3U);
  reset_ports();
  category_probe_result[0] = 1U;
  category_probe_result[2] = 1U;
  page_category.fielda0 = 2;
  format_width = 1U;
  pkg_palette_w10_005c0a60(&page, 0U);
  assert(category_probe_calls == 3);
  assert(category_probe_index == 2U);
  assert(nav_calls == 1 && nav_first == 1U && nav_second == 1U);
  assert(format_calls == 1);
  assert(format_first == 2U);
  assert(format_second == 2);
  assert(format_third == 2);
  assert(text_calls == 1);
  assert(text_receiver == &page_text);
  assert(text_pointer == format_store);
  assert(page.field20 == 1);
  assert(page.field24 == 2);
  assert(release_text_calls == 0);

  setup_page(&page, slots, 3U);
  reset_ports();
  category_probe_result[0] = 1U;
  category_probe_result[2] = 1U;
  page_category.fielda0 = 2;
  page.field20 = 1;
  page.field24 = 2;
  format_width = 1U;
  pkg_palette_w10_005c0a60(&page, 0U);
  assert(nav_calls == 1 && nav_second == 1U);
  assert(format_calls == 0 && text_calls == 0);
}

void test_page_005c0a60_span_and_release() {
  OpaquePage page{};
  OpaqueCategorySlot slots[8]{};
  setup_page(&page, slots, 2U);
  reset_ports();
  category_probe_result[0] = 1U;
  category_probe_result[1] = 1U;
  format_width = 1U;
  pkg_palette_w10_005c0a60(&page, 0U);
  assert(page.field20 == 0 && page.field24 == 2);
  assert(release_text_calls == 0);

  setup_page(&page, slots, 2U);
  reset_ports();
  category_probe_result[0] = 1U;
  category_probe_result[1] = 1U;
  format_width = 4U;
  pkg_palette_w10_005c0a60(&page, 0U);
  assert(page.field20 == 0 && page.field24 == 2);
  assert(release_text_calls == 1);
  assert(release_text_pointer == format_store);

  setup_page(&page, slots, 2U);
  reset_ports();
  category_probe_result[0] = 1U;
  category_probe_result[1] = 1U;
  format_width = 4U;
  page.field1c = nullptr;
  pkg_palette_w10_005c0a60(&page, 0U);
  assert(nav_calls == 0);
  assert(format_calls == 1 && text_calls == 1);
  assert(release_text_calls == 1);
}

void setup_entry(OpaqueEntry* entry) {
  std::memset(entry, 0, sizeof(*entry));
  std::memset(&property_list, 0, sizeof(property_list));
  std::memset(&property_manager, 0, sizeof(property_manager));
  std::memset(&property_object, 0, sizeof(property_object));
  install_list_table(g_function_table);
  property_list.vtable = g_function_table;
  property_manager.vtable = g_function_table;
  sublist_result = &property_list;
  sublist_key = 0U;
  sublist_limit = 0U;
}

void test_entry_005c1e20_missing_list() {
  OpaqueEntry entry{};
  setup_entry(&entry);
  reset_ports();
  OpaqueResourceKey key{0x11111111U, 0x22222222U, 3U};
  static_cast<void>(key);
  sublist_result = nullptr;
  assert(pkg_palette_w10_005c1e20(&entry, &key, 5U) == false);
  assert(sublist_key == 0x11111111U);
  assert(sublist_limit == 3U);
  assert(entry.field74 == 0U);
  assert(property_get_calls == 0);
  assert(group_key_calls == 0 && array_key_calls == 0 && text_key_calls == 0);
  assert(list_release_calls == 0);
}

void test_entry_005c1e20_full_load() {
  OpaqueEntry entry{};
  setup_entry(&entry);
  reset_ports();
  value8_payload = 0x7fU;
  value32_payload = 0x11223344U;
  key_instance_payload = 0x55667788U;
  property_get_tag = 1U;
  group_key_word00 = 0x0000abcdU;
  group_key_word08 = 0x0000beefU;
  OpaqueResourceKey key{0x11111111U, 0x22222222U, 0U};
  static_cast<void>(key);
  assert(pkg_palette_w10_005c1e20(&entry, &key, 5U) == true);
  assert(sublist_limit == 0x406b0100U);
  assert(entry.field74 == 0x11111111U);
  assert(entry.field50 == 0x7fU);
  assert(entry.field70 == 0x7fU);
  assert(entry.field54 == 0x55667788U);
  assert(entry.field78 == 0x0000abcdU);
  assert(entry.field7c.word00 == 0x0000abcdU);
  assert(entry.field7c.word04 == 0U);
  assert(entry.field7c.word08 == 0x0000beefU);
  assert(entry.field48 == 0x0000beefU);
  assert(property_get_calls == 4);
  assert(property_get_key == 0x35eeb8b5U);
  assert(value8_calls == 2);
  assert(value32_calls == 0);
  assert(entry.field58 == 0U);
  assert(entry.field4c == 0U);
  assert(key_instance_calls == 1);
  assert(key_instance_key == 0xd20d4636U);
  assert(key_instance_out == &entry.field54);
  assert(group_key_calls == 2);
  assert(array_key_calls == 1);
  assert(array_key_key == 0x44f6c09U);
  assert(array_key_out == reinterpret_cast<OpaqueResourceKey*>(&entry.field88));
  assert(text_key_calls == 1);
  assert(text_key_key == 0x2e1942a8U);
  assert(list_release_calls == 1);
  assert(list_release_receiver == &property_list);
}

void test_entry_005c1e20_tag_gates() {
  OpaqueEntry entry{};
  setup_entry(&entry);
  reset_ports();
  value8_payload = 0x21U;
  value32_payload = 0xdeadbeefU;
  key_instance_payload = 0xabcdef01U;
  property_get_tag = 10U;
  group_key_word08 = 0U;
  OpaqueResourceKey key{0x00000005U, 0U, 9U};
  static_cast<void>(key);
  assert(pkg_palette_w10_005c1e20(&entry, &key, 0U) == true);
  assert(sublist_limit == 9U);
  assert(entry.field50 == 0U);
  assert(entry.field70 == 0U);
  assert(entry.field58 == 0xdeadbeefU);
  assert(entry.field4c == 0xdeadbeefU);
  assert(value8_calls == 0);
  assert(value32_calls == 2);
  assert(property_get_calls == 4);
  assert(key_instance_calls == 2);
  assert(key_instance_key == 0x9a6aaae5U);
  assert(key_instance_out == &entry.field48);
  assert(entry.field48 == 0xabcdef01U);
  entry.field48 = 0xabcdef01U;
}

void setup_palette(OpaquePalette* palette, OpaqueElement** pages,
                   std::size_t page_count) {
  std::memset(palette, 0, sizeof(*palette));
  std::memset(&palette_group, 0, sizeof(palette_group));
  std::memset(&app_props, 0, sizeof(app_props));
  std::memset(&app_object, 0, sizeof(app_object));
  std::memset(&lead_element, 0, sizeof(lead_element));
  std::memset(&title_element, 0, sizeof(title_element));
  std::memset(&body_element, 0, sizeof(body_element));
  std::memset(&tail_element, 0, sizeof(tail_element));
  std::memset(&host_element, 0, sizeof(host_element));
  install_element_table(g_function_table);
  lead_element.vtable = g_function_table;
  title_element.vtable = g_function_table;
  body_element.vtable = g_function_table;
  tail_element.vtable = g_function_table;
  host_element.vtable = g_function_table;
  palette_group.field0c = pages;
  palette_group.field10 = pages + page_count;
  palette->field6c = &palette_group;
  palette->field74 = pages;
  palette->field78 = pages + page_count;
  palette->field28 = &body_element;
  palette->fieldb0 = 3;
  app_props.field118 = 0U;
  app_object.field3c = &app_props;
  g_dword_015fd918 = &app_object;
}

void test_palette_005c3000_plain_body() {
  OpaquePalette palette{};
  OpaqueElement* pages[1]{};
  setup_palette(&palette, pages, 0U);
  reset_ports();
  element_rect_value = OpaqueRectF{1.0F, 2.0F, 3.0F, 40.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(feature_calls == 1);
  assert(feature_first == 0x5d3f56bU && feature_second == 1U);
  assert(dedupe_calls == 0);
  assert(element_place_calls == 1);
  assert(element_place_receiver == &body_element);
  assert(element_place_value.field00 == 1.0F);
  assert(element_place_value.field04 == 5.0F);
  assert(element_place_value.field08 == 3.0F);
  assert(element_place_value.field0c == 40.0F);
}

void test_palette_005c3000_stacked_lead() {
  OpaquePalette palette{};
  OpaqueElement* pages[2]{};
  setup_palette(&palette, pages, 2U);
  reset_ports();
  palette.field20 = &lead_element;
  element_rect_value = OpaqueRectF{0.0F, 0.0F, 10.0F, 60.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(element_place_value.field04 == 65.0F);
  assert(element_place_value.field0c == 60.0F);
}

void test_palette_005c3000_title_feature() {
  OpaquePalette palette{};
  OpaqueElement* pages[1]{};
  setup_palette(&palette, pages, 1U);
  reset_ports();
  OpaqueToggle toggle{};
  feature_result = &toggle;
  palette.field24 = &title_element;
  palette.field20 = &lead_element;
  element_rect_value = OpaqueRectF{0.0F, 0.0F, 4.0F, 12.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(element_place_calls == 2);
  assert(element_place_history[0] == &title_element);
  assert(element_place_history_value[0].field00 == 0.0F);
  assert(element_place_history_value[0].field04 == 17.0F);
  assert(element_place_history_value[0].field08 == 4.0F);
  assert(element_place_history_value[0].field0c == 29.0F);
  assert(element_place_history[1] == &body_element);
  assert(element_place_history_value[1].field00 == 0.0F);
  assert(element_place_history_value[1].field04 == 34.0F);
  assert(element_place_history_value[1].field08 == 4.0F);
  assert(element_place_history_value[1].field0c == 12.0F);
}

void test_palette_005c3000_dedupe_gate() {
  OpaquePalette palette{};
  OpaqueElement* pages[2]{};
  setup_palette(&palette, pages, 2U);
  reset_ports();
  palette.field20 = &lead_element;
  app_props.field118 = 1U;
  dedupe_result = 0;
  element_rect_value = OpaqueRectF{0.0F, 0.0F, 0.0F, 30.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(dedupe_calls == 1);
  assert(element_place_value.field04 == 5.0F);

  setup_palette(&palette, pages, 2U);
  reset_ports();
  palette.field20 = &lead_element;
  app_props.field118 = 1U;
  dedupe_result = 1;
  element_rect_value = OpaqueRectF{0.0F, 0.0F, 0.0F, 30.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(dedupe_calls == 1);
  assert(element_place_value.field04 == 35.0F);
}

void test_palette_005c3000_wide_and_tail() {
  OpaquePalette palette{};
  OpaqueElement* pages[1]{};
  setup_palette(&palette, pages, 1U);
  reset_ports();
  palette.field1c = &host_element;
  palette_group.field70 = 1U;
  element_rect_value = OpaqueRectF{0.0F, 20.0F, 0.0F, 50.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(element_place_value.field0c == 15.0F);

  setup_palette(&palette, pages, 1U);
  reset_ports();
  palette.field2c = &tail_element;
  palette_group.field70 = 1U;
  element_rect_value = OpaqueRectF{0.0F, 20.0F, 0.0F, 50.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(element_place_value.field0c == 25.0F);

  setup_palette(&palette, pages, 1U);
  reset_ports();
  palette.field2c = &tail_element;
  palette_group.field70 = 0U;
  element_rect_value = OpaqueRectF{0.0F, 20.0F, 0.0F, 50.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(element_place_value.field0c == 25.0F);

  setup_palette(&palette, pages, 1U);
  reset_ports();
  palette_group.field70 = 1U;
  element_rect_value = OpaqueRectF{0.0F, 20.0F, 0.0F, 50.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(element_place_value.field0c == 50.0F);
}

void test_palette_005c3000_missing_body() {
  OpaquePalette palette{};
  OpaqueElement* pages[1]{};
  setup_palette(&palette, pages, 1U);
  reset_ports();
  palette.field28 = nullptr;
  element_rect_value = OpaqueRectF{0.0F, 20.0F, 0.0F, 50.0F};
  pkg_palette_w10_005c3000(&palette);
  assert(element_place_calls == 0);
}

void test_palette_005c3cb0_out_of_range() {
  OpaquePalette palette{};
  OpaqueElement* pages[3]{};
  setup_palette(&palette, pages, 3U);
  reset_ports();
  palette.fieldac = 0x11U;
  index_lookup_result[0] = 9;
  index_lookup_result[1] = 9;
  pkg_palette_w10_005c3cb0(&palette, 0x22U);
  assert(palette.fieldac == 0x22U);
  assert(index_lookup_calls == 2);
  assert(element_mark_calls == 0);
  assert(row_calls == 0 && event_calls == 0);

  setup_palette(&palette, pages, 3U);
  reset_ports();
  index_lookup_result[0] = -1;
  index_lookup_result[1] = -1;
  pkg_palette_w10_005c3cb0(&palette, 0x22U);
  assert(palette.fieldac == 0x22U);
  assert(element_mark_calls == 0);
  assert(row_calls == 0 && event_calls == 0);
}

void test_palette_005c3cb0_empty_pages() {
  OpaquePalette palette{};
  OpaqueElement* pages[1]{};
  setup_palette(&palette, pages, 0U);
  reset_ports();
  index_lookup_result[0] = 0;
  index_lookup_result[1] = 0;
  pkg_palette_w10_005c3cb0(&palette, 0x22U);
  assert(palette.fieldac == 0x22U);
  assert(element_mark_calls == 0);
  assert(row_calls == 0);
  assert(event_calls == 0);
  assert(category_id_calls == 0);
  assert(index_of_calls == 0);
  assert(commit_calls == 0);
}

void test_palette_005c3cb0_no_previous() {
  OpaquePalette palette{};
  OpaqueElement* pages[2]{&lead_element, &title_element};
  setup_palette(&palette, pages, 2U);
  reset_ports();
  palette.fieldac = 0x11U;
  index_lookup_result[0] = -1;
  index_lookup_result[1] = 0;
  pkg_palette_w10_005c3cb0(&palette, 0x22U);
  assert(palette.fieldac == 0x22U);
  assert(element_mark_calls == 1);
  assert(element_mark_receiver == &lead_element);
  assert(element_mark_first == 4U && element_mark_second == 1U);
  assert(row_calls == 1);
  assert(category_id_calls == 1);
  assert(commit_calls == 1);
  assert(commit_value == index_of_result);
}

void test_palette_005c3cb0_marked_pages() {
  OpaquePalette palette{};
  OpaqueElement* pages[3]{&lead_element, &title_element, &body_element};
  setup_palette(&palette, pages, 3U);
  reset_ports();
  palette.fieldac = 0x11U;
  index_lookup_result[0] = 0;
  index_lookup_result[1] = 0;
  pkg_palette_w10_005c3cb0(&palette, 0x22U);
  assert(element_mark_calls == 2);
  assert(element_mark_history[0] == &lead_element);
  assert(element_mark_history_first[0] == 4U);
  assert(element_mark_history_second[0] == 0U);
  assert(element_mark_history[1] == &lead_element);
  assert(element_mark_history_first[1] == 4U);
  assert(element_mark_history_second[1] == 1U);
  assert(row_calls == 1);
  assert(row_value == 0);

  setup_palette(&palette, pages, 3U);
  reset_ports();
  palette.fieldac = 0x11U;
  index_lookup_result[0] = 1;
  index_lookup_result[1] = 1;
  category_id_result = 0x22U;
  pkg_palette_w10_005c3cb0(&palette, 0x22U);
  assert(element_mark_calls == 2);
  assert(element_mark_history[0] == &title_element);
  assert(element_mark_history_second[0] == 0U);
  assert(element_mark_history[1] == &title_element);
  assert(element_mark_history_second[1] == 1U);
  assert(row_calls == 1);
  assert(category_id_calls == 1);
  assert(index_of_calls == 0);
  assert(commit_calls == 0);
}

void test_palette_005c3cb0_unchanged_selection() {
  OpaquePalette palette{};
  OpaqueElement* pages[2]{&lead_element, &title_element};
  setup_palette(&palette, pages, 2U);
  reset_ports();
  palette.fieldac = 0x11U;
  index_lookup_result[0] = 0;
  index_lookup_result[1] = 0;
  pkg_palette_w10_005c3cb0(&palette, 0x11U);
  assert(palette.fieldac == 0x11U);
  assert(element_mark_calls == 2);
  assert(row_calls == 0 && event_calls == 0);
  assert(category_id_calls == 0 && commit_calls == 0);
}

void test_palette_005c3cb0_row_division() {
  OpaquePalette palette{};
  OpaqueElement* pages[4]{&lead_element, &title_element, &body_element,
                          &tail_element};
  setup_palette(&palette, pages, 4U);
  reset_ports();
  palette.fieldac = 0x11U;
  palette.fieldb0 = 2;
  index_lookup_result[0] = 3;
  index_lookup_result[1] = 3;
  palette.fielda0 = 5;
  category_at_result = &page_category;
  pkg_palette_w10_005c3cb0(&palette, 0x22U);
  assert(row_value == 1);
  assert(category_id_receiver == &page_category);
  assert(index_of_value == 0x22U);
  assert(commit_receiver == &palette);
  assert(commit_value == index_of_result);
}

}

}

using namespace openspore::reconstruction::pkg_palette_wave10;

int main() {
  test_page_005c0a60_guards();
  test_page_005c0a60_few_pages();
  test_page_005c0a60_paged_text();
  test_page_005c0a60_span_and_release();
  test_entry_005c1e20_missing_list();
  test_entry_005c1e20_full_load();
  test_entry_005c1e20_tag_gates();
  test_palette_005c3000_plain_body();
  test_palette_005c3000_stacked_lead();
  test_palette_005c3000_title_feature();
  test_palette_005c3000_dedupe_gate();
  test_palette_005c3000_wide_and_tail();
  test_palette_005c3000_missing_body();
  test_palette_005c3cb0_out_of_range();
  test_palette_005c3cb0_empty_pages();
  test_palette_005c3cb0_no_previous();
  test_palette_005c3cb0_marked_pages();
  test_palette_005c3cb0_unchanged_selection();
  test_palette_005c3cb0_row_division();
}
