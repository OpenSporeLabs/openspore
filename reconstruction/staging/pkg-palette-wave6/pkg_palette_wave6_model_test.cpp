#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "pkg_palette_wave6.hpp"

struct OpaqueSwatchManager {
  std::uint32_t value;
};

struct OpaqueSwatchState {
  std::uint32_t value;
};

struct OpaqueGraphicsRoot {
  void* vtable;
};

struct OpaqueGraphicsContext {
  void* vtable;
};

struct OpaqueRenderTarget {
  std::uint32_t value;
};

struct OpaqueAppSystem {
  void* vtable;
};

namespace {

using namespace openspore::reconstruction::pkg_palette_wave6;

template <typename Function>
void* function_data(Function function) {
  return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(function));
}

void set_vtable(OpaqueViewerObject* object, void* table) {
  std::memcpy(object, &table, sizeof(table));
}

void set_vtable(OpaqueAdvancedItemViewer* object, void* table) {
  object->vtable = table;
}

void set_vtable(OpaqueGraphicsRoot* object, void* table) {
  object->vtable = table;
}

void set_vtable(OpaqueGraphicsContext* object, void* table) {
  object->vtable = table;
}

void set_vtable(OpaqueAppSystem* object, void* table) {
  object->vtable = table;
}

int prepare_calls;
OpaquePaletteMain* prepared_object;
int release_prepare_calls;
OpaquePaletteMain* released_object;

int swatch_manager_calls;
int swatch_state_calls;
OpaqueSwatchManager* selected_swatch_manager;
OpaqueSwatchState* selected_swatch_state;
OpaqueSwatchManager swatch_manager{1U};
OpaqueSwatchState swatch_state{2U};
bool swatch_enabled;

int allocation_calls;
std::uint32_t allocation_arguments[6];
OpaqueViewerObject* allocation_result;

int constructor_calls;
OpaqueViewerObject* constructor_receiver;
std::uint32_t constructor_arguments[7];
OpaqueViewerObject* constructor_result;
bool constructor_returns_receiver;

int addref_calls;
int release_calls;
OpaqueViewerObject* addref_object;
OpaqueViewerObject* release_object;

int producer_calls;
OpaqueViewerObject* producer_receiver;
OpaqueViewerItem* producer_item;
void* producer_key;
OpaqueViewerObject* producer_resource;

int manager_set_calls;
OpaqueSwatchManager* manager_set_receiver;
OpaqueViewerObject* manager_set_resource;
OpaqueViewerItem* manager_set_item;
OpaqueViewerObject* manager_set_constructed;
std::uint32_t manager_set_flag;

int manager_detail_calls;
OpaqueSwatchManager* manager_detail_receiver;
std::uint32_t manager_detail_argument;

int graphics_root_calls;
int graphics_context_calls;
int graphics_rect_calls;
OpaqueGraphicsRoot graphics_root{};
OpaqueGraphicsContext graphics_context{};
OpaqueRect rect{1.0F, 2.0F, 10.0F, 14.0F};

int layout_calls;
OpaqueSwatchManager* layout_receiver;
float layout_x;
float layout_y;
float layout_width;
float layout_height;

int viewer_slot_calls;
OpaqueAdvancedItemViewer* viewer_slot_receiver;
std::uint32_t viewer_slot_a;
std::uint32_t viewer_slot_b;
OpaqueRenderTarget render_target{3U};
OpaqueRenderTarget secondary_target{4U};
int render_target_calls;
OpaqueRenderTarget* render_target_argument;
int post_calls;
OpaqueRenderTarget* post_target;
std::uint32_t post_a;
std::uint8_t post_b;
int app_calls;
OpaqueAppSystem* app_receiver;
std::uint32_t app_a;
OpaqueCommandLine* app_command_line;
std::uint32_t app_b;
OpaqueAppSystem app_system{};

int item_slot_calls;
OpaqueViewerObject* item_slot_receiver;
void* item_slot_argument;
std::uint8_t item_slot_result;

int viewer_addref_calls;
int viewer_release_calls;

std::uint8_t PKG_PALETTE_THISCALL
item_slot_callback(OpaqueViewerObject* receiver, void* argument) {
  ++item_slot_calls;
  item_slot_receiver = receiver;
  item_slot_argument = argument;
  return item_slot_result;
}

void PKG_PALETTE_THISCALL addref_callback(OpaqueViewerObject* receiver) {
  ++addref_calls;
  addref_object = receiver;
}

void PKG_PALETTE_THISCALL release_callback(OpaqueViewerObject* receiver) {
  ++release_calls;
  release_object = receiver;
}

void PKG_PALETTE_THISCALL producer_callback(OpaqueViewerObject* receiver,
                                            OpaqueViewerObject* resource,
                                            void* key, OpaqueViewerItem* item) {
  ++producer_calls;
  producer_receiver = receiver;
  producer_item = item;
  producer_key = key;
  producer_resource = resource;
}

OpaqueRenderTarget* PKG_PALETTE_THISCALL viewer_slot_callback(
    OpaqueAdvancedItemViewer* receiver, std::uint32_t a, std::uint32_t b) {
  ++viewer_slot_calls;
  viewer_slot_receiver = receiver;
  viewer_slot_a = a;
  viewer_slot_b = b;
  return &render_target;
}

OpaqueGraphicsContext* PKG_PALETTE_THISCALL
graphics_root_callback(OpaqueGraphicsRoot* receiver) {
  ++graphics_context_calls;
  assert(receiver == &graphics_root);
  return &graphics_context;
}

OpaqueRect* PKG_PALETTE_THISCALL
graphics_rect_callback(OpaqueGraphicsContext* receiver) {
  ++graphics_rect_calls;
  assert(receiver == &graphics_context);
  return &rect;
}

void PKG_PALETTE_THISCALL app_callback(OpaqueAppSystem* receiver,
                                       std::uint32_t a,
                                       OpaqueCommandLine* command_line,
                                       std::uint32_t b) {
  ++app_calls;
  app_receiver = receiver;
  app_a = a;
  app_command_line = command_line;
  app_b = b;
}

void reset_observations() {
  prepare_calls = 0;
  prepared_object = nullptr;
  release_prepare_calls = 0;
  released_object = nullptr;
  swatch_manager_calls = 0;
  swatch_state_calls = 0;
  selected_swatch_manager = nullptr;
  selected_swatch_state = nullptr;
  swatch_enabled = false;
  allocation_calls = 0;
  allocation_arguments[0] = 0U;
  allocation_arguments[1] = 0U;
  allocation_arguments[2] = 0U;
  allocation_arguments[3] = 0U;
  allocation_arguments[4] = 0U;
  allocation_arguments[5] = 0U;
  allocation_result = nullptr;
  constructor_calls = 0;
  constructor_receiver = nullptr;
  for (std::uint32_t& value : constructor_arguments) {
    value = 0U;
  }
  constructor_result = nullptr;
  constructor_returns_receiver = true;
  addref_calls = 0;
  release_calls = 0;
  addref_object = nullptr;
  release_object = nullptr;
  producer_calls = 0;
  producer_receiver = nullptr;
  producer_item = nullptr;
  producer_key = nullptr;
  producer_resource = nullptr;
  manager_set_calls = 0;
  manager_set_receiver = nullptr;
  manager_set_resource = nullptr;
  manager_set_item = nullptr;
  manager_set_constructed = nullptr;
  manager_set_flag = 0U;
  manager_detail_calls = 0;
  manager_detail_receiver = nullptr;
  manager_detail_argument = 0U;
  graphics_root_calls = 0;
  graphics_context_calls = 0;
  graphics_rect_calls = 0;
  layout_calls = 0;
  layout_receiver = nullptr;
  layout_x = 0.0F;
  layout_y = 0.0F;
  layout_width = 0.0F;
  layout_height = 0.0F;
  g_palette_width_multiplier = 0.05F;
  g_palette_height_multiplier = 0.0F;
  viewer_slot_calls = 0;
  viewer_slot_receiver = nullptr;
  viewer_slot_a = 0U;
  viewer_slot_b = 0U;
  render_target_calls = 0;
  render_target_argument = nullptr;
  post_calls = 0;
  post_target = nullptr;
  post_a = 0U;
  post_b = 0U;
  app_calls = 0;
  app_receiver = nullptr;
  app_a = 0U;
  app_command_line = nullptr;
  app_b = 0U;
  item_slot_calls = 0;
  item_slot_receiver = nullptr;
  item_slot_argument = nullptr;
  item_slot_result = 1U;
  viewer_addref_calls = 0;
  viewer_release_calls = 0;
}

void set_item_callback_vtable(OpaqueViewerObject* object) {
  static void* table[3] = {nullptr, nullptr, function_data(item_slot_callback)};
  set_vtable(object, table);
}

void set_allocated_vtable(OpaqueViewerObject* object) {
  static void* table[3] = {nullptr, function_data(addref_callback),
                           function_data(release_callback)};
  set_vtable(object, table);
}

void set_producer_vtable(OpaqueViewerObject* object) {
  static void* table[11] = {};
  table[10] = function_data(producer_callback);
  set_vtable(object, table);
}

void set_viewer_vtable(OpaqueAdvancedItemViewer* object) {
  static void* table[14] = {};
  table[13] = function_data(viewer_slot_callback);
  set_vtable(object, table);
}

void set_graphics_vtables() {
  static void* root_table[2] = {nullptr, function_data(graphics_root_callback)};
  static void* context_table[14] = {};
  context_table[13] = function_data(graphics_rect_callback);
  set_vtable(&graphics_root, root_table);
  set_vtable(&graphics_context, context_table);
}

void set_app_vtable() {
  static void* table[6] = {};
  table[5] = function_data(app_callback);
  set_vtable(&app_system, table);
}

void reset_viewer(OpaqueAdvancedItemViewer& viewer, OpaqueViewerItem& item,
                  OpaqueViewerObject& callback, OpaqueViewerObject& producer,
                  OpaqueViewerObject& resource) {
  reset_observations();
  viewer = OpaqueAdvancedItemViewer{};
  item = OpaqueViewerItem{};
  callback = OpaqueViewerObject{};
  producer = OpaqueViewerObject{};
  resource = OpaqueViewerObject{};
  set_viewer_vtable(&viewer);
  set_item_callback_vtable(&callback);
  set_producer_vtable(&producer);
  set_graphics_vtables();
  set_app_vtable();
  viewer.field100 = 0x71fa7d3fU;
  viewer.field198 = 1U;
  viewer.field188 = 10.0F;
  viewer.field84 = 20.0F;
  viewer.field88 = 30.0F;
  viewer.field17c = &item;
  viewer.field180 = &resource;
  item.field08 = &callback;
  item.field14 = &producer;
  item.field2c = 0x12345678U;
  item.field31 = 1U;
}

}

namespace openspore::reconstruction::pkg_palette_wave6 {

extern "C" void PKG_PALETTE_THISCALL
unresolved_005c5e90(OpaquePaletteMain* self) {
  ++prepare_calls;
  prepared_object = self;
}

extern "C" void PKG_PALETTE_CDECL unresolved_00f47380(OpaquePaletteMain* self) {
  ++release_prepare_calls;
  released_object = self;
}

extern "C" OpaqueSwatchManager* PKG_PALETTE_CDECL unresolved_00401020() {
  ++swatch_manager_calls;
  return &swatch_manager;
}

extern "C" OpaqueSwatchState* PKG_PALETTE_THISCALL
unresolved_0113ae10(OpaqueSwatchManager* receiver) {
  ++swatch_state_calls;
  selected_swatch_manager = receiver;
  selected_swatch_state = swatch_enabled ? &swatch_state : nullptr;
  return selected_swatch_state;
}

extern "C" OpaqueViewerObject* PKG_PALETTE_CDECL
unresolved_00f473a0(std::uint32_t a, std::uint32_t b, std::uint32_t c,
                    std::uint32_t d, std::uint32_t e, std::uint32_t f) {
  ++allocation_calls;
  allocation_arguments[0] = a;
  allocation_arguments[1] = b;
  allocation_arguments[2] = c;
  allocation_arguments[3] = d;
  allocation_arguments[4] = e;
  allocation_arguments[5] = f;
  return allocation_result;
}

extern "C" OpaqueViewerObject* PKG_PALETTE_THISCALL
unresolved_0059f030(OpaqueViewerObject* receiver, std::uint32_t a,
                    std::uint32_t b, std::uint32_t c, std::uint32_t d,
                    std::uint32_t e, std::uint32_t f, std::uint32_t g) {
  ++constructor_calls;
  constructor_receiver = receiver;
  constructor_arguments[0] = a;
  constructor_arguments[1] = b;
  constructor_arguments[2] = c;
  constructor_arguments[3] = d;
  constructor_arguments[4] = e;
  constructor_arguments[5] = f;
  constructor_arguments[6] = g;
  return constructor_returns_receiver ? receiver : constructor_result;
}

extern "C" void PKG_PALETTE_THISCALL
unresolved_005ed320(OpaqueSwatchManager* receiver, std::uint32_t argument) {
  ++manager_detail_calls;
  manager_detail_receiver = receiver;
  manager_detail_argument = argument;
}

extern "C" void PKG_PALETTE_THISCALL
unresolved_005ee480(OpaqueSwatchManager* receiver, OpaqueViewerObject* resource,
                    OpaqueViewerItem* item, OpaqueViewerObject* constructed,
                    std::uint32_t flag) {
  ++manager_set_calls;
  manager_set_receiver = receiver;
  manager_set_resource = resource;
  manager_set_item = item;
  manager_set_constructed = constructed;
  manager_set_flag = flag;
}

extern "C" OpaqueGraphicsRoot* PKG_PALETTE_CDECL unresolved_0067caa0() {
  ++graphics_root_calls;
  return &graphics_root;
}

extern "C" OpaqueRenderTarget* PKG_PALETTE_CDECL
unresolved_0067cad0(OpaqueRenderTarget* target) {
  ++render_target_calls;
  render_target_argument = target;
  return target;
}

extern "C" void PKG_PALETTE_STDCALL unresolved_0080d710(
    OpaqueRenderTarget* target, std::uint32_t a, std::uint8_t b) {
  ++post_calls;
  post_target = target;
  post_a = a;
  post_b = b;
}

extern "C" void PKG_PALETTE_THISCALL
unresolved_008283a0(OpaqueSwatchManager* receiver, float x, float y,
                    float width, float height) {
  ++layout_calls;
  layout_receiver = receiver;
  layout_x = x;
  layout_y = y;
  layout_width = width;
  layout_height = height;
}

extern "C" OpaqueAppSystem* PKG_PALETTE_CDECL unresolved_0067dcc0() {
  return &app_system;
}

}

namespace {

using namespace openspore::reconstruction::pkg_palette_wave6;

void test_category_helper_and_page_return() {
  OpaquePaletteMain main_object{};
  reset_observations();
  OpaquePaletteMain* result = pkg_palette_005c5ee0(&main_object, 2U);
  assert(result == &main_object);
  assert(prepare_calls == 1);
  assert(released_object == nullptr);
  result = pkg_palette_005c5ee0(&main_object, 3U);
  assert(result == &main_object);
  assert(prepare_calls == 2);
  assert(release_prepare_calls == 1);
  assert(released_object == &main_object);

  OpaquePalettePage page{};
  assert(pkg_palette_005c8bc0(&page, 0xee3f516eU) == &page);
  assert(pkg_palette_005c8bc0(&page, 0x2f009dd0U) == &page);
  assert(pkg_palette_005c8bc0(&page, 0x72deed2bU) == &page);
  assert(pkg_palette_005c8bc0(&page, 0U) == nullptr);
  assert(pkg_palette_005c8bc0(&page, 0x72deed2cU) == nullptr);
}

void test_viewer_state_without_tooltip() {
  OpaqueAdvancedItemViewer viewer{};
  OpaqueViewerItem item{};
  OpaqueViewerObject callback{};
  OpaqueViewerObject producer{};
  OpaqueViewerObject resource{};
  reset_viewer(viewer, item, callback, producer, resource);
  swatch_enabled = false;
  pkg_palette_005f4750(&viewer);
  assert(viewer.field16a == 1U);
  assert(viewer.field94 == 10.0F);
  assert(viewer.field169 == 1U);
  assert(item_slot_calls == 1);
  assert(item_slot_argument ==
         reinterpret_cast<std::uint8_t*>(&viewer) + 0x4cU);
  assert(viewer_slot_calls == 1);
  assert(viewer_slot_a == 1U && viewer_slot_b == 1U);
  assert(render_target_calls == 1);
  assert(render_target_argument == &render_target);
  assert(post_calls == 1);
  assert(post_target == &render_target);
  assert(app_calls == 1);
  assert(app_receiver == &app_system);
  assert(app_a == 0U && app_b == 0x0522f9cdU);
  assert(app_command_line != nullptr);
  assert(app_command_line->field00 ==
         static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&viewer)));
  assert(app_command_line->field08 == 0x0522f9cdU);
  assert(graphics_root_calls == 0);
  assert(allocation_calls == 0);
}

void test_viewer_unavailable_and_scale() {
  OpaqueAdvancedItemViewer viewer{};
  OpaqueViewerItem item{};
  OpaqueViewerObject callback{};
  OpaqueViewerObject producer{};
  OpaqueViewerObject resource{};
  reset_viewer(viewer, item, callback, producer, resource);
  item_slot_result = 0U;
  viewer.field198 = 0U;
  pkg_palette_005f4750(&viewer);
  assert(viewer.field16a == 0U);
  assert(viewer.field94 == 7.5F);
  assert(viewer.field169 == 0U);
  assert(item_slot_calls == 1);

  reset_viewer(viewer, item, callback, producer, resource);
  item_slot_result = 1U;
  viewer.field184 = 1U;
  viewer.field16b = 1U;
  swatch_enabled = true;
  pkg_palette_005f4750(&viewer);
  assert(viewer.field94 == 10.0F);
  assert(viewer.field169 == 0U);
  assert(producer_calls == 1);
  assert(producer_receiver == &producer);
  assert(producer_item == &item);
  assert(producer_key == reinterpret_cast<std::uint8_t*>(&viewer) + 0x4cU);
  assert(producer_resource == &resource);
  assert(manager_detail_calls == 1);
  assert(manager_detail_argument == 2U);
  assert(graphics_root_calls == 1);
  assert(graphics_context_calls == 1);
  assert(graphics_rect_calls == 1);
  assert(layout_calls == 1);
  assert(layout_receiver == &swatch_manager);
  assert(layout_x == 20.0F);
  assert(layout_y == 30.0F);
  assert(layout_width > 0.44F && layout_width < 0.46F);
  assert(layout_height == 0.0F);
}

void test_viewer_allocation_and_ownership() {
  OpaqueAdvancedItemViewer viewer{};
  OpaqueViewerItem item{};
  OpaqueViewerObject callback{};
  OpaqueViewerObject producer{};
  OpaqueViewerObject resource{};
  OpaqueViewerObject allocated{};
  reset_viewer(viewer, item, callback, producer, resource);
  viewer.field16b = 1U;
  swatch_enabled = true;
  item.field14 = nullptr;
  item.field31 = 0U;
  allocation_result = &allocated;
  set_allocated_vtable(&allocated);
  resource.opaque[0] = 0;
  resource.opaque[1] = 0;
  resource.opaque[2] = 0;
  std::memcpy(resource.opaque + 0x0c, "\xef\xbc\xad\xde", 4);
  std::memcpy(resource.opaque + 0x10, "\x34\x12\x00\x00", 4);
  std::memcpy(resource.opaque + 0x14, "\x78\x56\x00\x00", 4);
  viewer.field194 = &secondary_target;
  pkg_palette_005f4750(&viewer);
  assert(allocation_calls == 1);
  assert(allocation_arguments[0] == 100U);
  assert(allocation_arguments[1] == 0x13eb430U);
  assert(constructor_calls == 1);
  assert(constructor_receiver == &allocated);
  assert(constructor_arguments[0] == 0xdeadbcefU);
  assert(constructor_arguments[1] == 0x1234U);
  assert(constructor_arguments[2] == 0x5678U);
  assert(constructor_arguments[3] == 0x12345678U);
  assert(constructor_arguments[4] == 0x14880158U);
  assert(constructor_arguments[5] == 0U);
  assert(constructor_arguments[6] == 1U);
  assert(addref_calls == 1 && addref_object == &allocated);
  assert(manager_set_calls == 1);
  assert(manager_set_constructed == &allocated);
  assert(manager_set_flag == 1U);
  assert(release_calls == 1 && release_object == &allocated);
  assert(render_target_calls == 2);
  assert(render_target_argument == &secondary_target);
  assert(post_calls == 2);
  assert(post_target == &secondary_target);
  assert(app_calls == 1);
}

void test_viewer_allocation_failure_paths() {
  OpaqueAdvancedItemViewer viewer{};
  OpaqueViewerItem item{};
  OpaqueViewerObject callback{};
  OpaqueViewerObject producer{};
  OpaqueViewerObject resource{};
  reset_viewer(viewer, item, callback, producer, resource);
  viewer.field16b = 1U;
  swatch_enabled = true;
  item.field14 = nullptr;
  item.field31 = 0U;
  allocation_result = nullptr;
  pkg_palette_005f4750(&viewer);
  assert(allocation_calls == 1);
  assert(constructor_calls == 0);
  assert(addref_calls == 0 && release_calls == 0);
  assert(manager_set_calls == 1);
  assert(manager_set_constructed == nullptr);

  reset_viewer(viewer, item, callback, producer, resource);
  viewer.field16b = 1U;
  swatch_enabled = true;
  item.field14 = nullptr;
  item.field31 = 0U;
  allocation_result = &resource;
  constructor_returns_receiver = false;
  constructor_result = nullptr;
  pkg_palette_005f4750(&viewer);
  assert(constructor_calls == 1);
  assert(addref_calls == 0 && release_calls == 0);
  assert(manager_set_constructed == nullptr);
}

}

int main() {
  test_category_helper_and_page_return();
  test_viewer_state_without_tooltip();
  test_viewer_unavailable_and_scale();
  test_viewer_allocation_and_ownership();
  test_viewer_allocation_failure_paths();
}
