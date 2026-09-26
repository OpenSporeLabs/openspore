#include <cassert>
#include <cstdint>

#include "utfwin_core_wave6.hpp"

using namespace openspore::reconstruction::pkg_utfwin_core_wave6;

namespace {

OpaqueWord allocation_size = 0;
const char* allocation_name = nullptr;
OpaqueWord allocation_trailer[4]{};
int allocation_calls = 0;
int resource_read_calls = 0;
int cursor_dispatch_calls = 0;
int icon_dispatch_calls = 0;
bool cursor_dispatch_result = true;
CursorManager* cursor_dispatch_manager = nullptr;
ResourceFactory* cursor_dispatch_resource = nullptr;
DropIconObject* cursor_dispatch_icon = nullptr;
OpaqueWord cursor_dispatch_value = 0;
OpaqueWord cursor_dispatch_tag = 0;
OpaqueWord resource_words[3]{0x11111111u, 0x22222222u, 0x33333333u};
DropIconObject icon_object{};

void* PKG_UTFWIN_CORE_CDECL allocate_icon(OpaqueWord size, const char* name,
                                          OpaqueWord value0, OpaqueWord value1,
                                          OpaqueWord value2,
                                          OpaqueWord value3) {
  allocation_size = size;
  allocation_name = name;
  allocation_trailer[0] = value0;
  allocation_trailer[1] = value1;
  allocation_trailer[2] = value2;
  allocation_trailer[3] = value3;
  ++allocation_calls;
  return &icon_object;
}

OpaqueWord* PKG_UTFWIN_CORE_THISCALL read_resource(ResourceFactory*) {
  ++resource_read_calls;
  return resource_words;
}

bool PKG_UTFWIN_CORE_THISCALL dispatch_cursor(CursorManager* manager,
                                              ResourceFactory* resource,
                                              DropIconObject* icon,
                                              OpaqueWord value,
                                              OpaqueWord tag) {
  ++cursor_dispatch_calls;
  cursor_dispatch_manager = manager;
  cursor_dispatch_resource = resource;
  cursor_dispatch_icon = icon;
  cursor_dispatch_value = value;
  cursor_dispatch_tag = tag;
  return cursor_dispatch_result;
}

void PKG_UTFWIN_CORE_THISCALL dispatch_icon(DropIconObject*) {
  ++icon_dispatch_calls;
}

int window_destroy_calls = 0;
WindowCore* destroyed_window = nullptr;
OpaqueWord destroyed_window_value = 0;

void PKG_UTFWIN_CORE_THISCALL destroy_window(WindowCore* self,
                                             OpaqueWord value) {
  ++window_destroy_calls;
  destroyed_window = self;
  destroyed_window_value = value;
}

int drawable_add_calls = 0;
int drawable_release_calls = 0;
int drawable_get_calls = 0;
Drawable* added_drawable = nullptr;
Drawable* released_drawable = nullptr;

std::int32_t PKG_UTFWIN_CORE_THISCALL add_drawable(Drawable* self) {
  ++drawable_add_calls;
  added_drawable = self;
  return 1;
}

std::int32_t PKG_UTFWIN_CORE_THISCALL release_drawable(Drawable* self) {
  ++drawable_release_calls;
  released_drawable = self;
  return 1;
}

Drawable* PKG_UTFWIN_CORE_THISCALL get_window_drawable(WindowCore* self) {
  ++drawable_get_calls;
  return self->drawable_1e4;
}

int release_order_count = 0;
RefObject* release_order[3]{};
RefObject* destroyed_reference = nullptr;

void PKG_UTFWIN_CORE_THISCALL release_reference(RefObject* self) {
  release_order[release_order_count++] = self;
}

void PKG_UTFWIN_CORE_THISCALL destroy_reference(RefObject* self) {
  destroyed_reference = self;
}

void* deallocated_tooltip = nullptr;

void PKG_UTFWIN_CORE_CDECL deallocate_tooltip(void* pointer) {
  deallocated_tooltip = pointer;
}

std::uint8_t call_drop_cursor(CursorManager* receiver,
                              ResourceFactory* resource,
                              DropIconObject** output, OpaqueWord value,
                              OpaqueWord compared_word) {
  return re_00801ac0(receiver, resource, output, value, compared_word);
}

void* call_set_serializer(ImageCore* receiver, OpaqueWord type_id) {
  return re_00957510(receiver, type_id);
}

void* call_get_real_area(WindowCore* receiver, OpaqueWord type_id) {
  return re_0095f960(receiver, type_id);
}

void* call_tooltip_teardown(TooltipCore* receiver, OpaqueWord flags) {
  return re_00835380(receiver, flags);
}

Drawable* call_set_drawable(WindowCore* receiver, Drawable* drawable) {
  return re_00960050(receiver, drawable);
}

void test_drop_cursor_gate_reads_fourth_stack_word() {
  ResourceFactoryVTable resource_vtable{};
  resource_vtable.read_10 = read_resource;
  ResourceFactory resource{&resource_vtable};
  DropIconObject* output = nullptr;
  CursorManagerVTable manager_vtable{};
  manager_vtable.dispatch_24 = dispatch_cursor;
  CursorManager manager{&manager_vtable, 0};

  cursor_runtime().allocate = allocate_icon;
  cursor_runtime().icon_dispatch = dispatch_icon;
  allocation_calls = 0;
  resource_read_calls = 0;
  cursor_dispatch_calls = 0;
  icon_dispatch_calls = 0;
  cursor_dispatch_result = true;

  assert(call_drop_cursor(&manager, &resource, &output, 0x02393756u, 0u) == 0u);
  assert(output == nullptr);
  assert(allocation_calls == 0);
  assert(resource_read_calls == 0);
  assert(cursor_dispatch_calls == 0);
  assert(icon_dispatch_calls == 0);

  assert(call_drop_cursor(&manager, &resource, &output, 0u, 0x02393756u) != 0u);
  assert(cursor_dispatch_calls == 1);
}

void test_drop_cursor_accepts_and_writes_output() {
  ResourceFactoryVTable resource_vtable{};
  resource_vtable.read_10 = read_resource;
  ResourceFactory resource{&resource_vtable};
  DropIconObject* output = nullptr;
  CursorManagerVTable manager_vtable{};
  manager_vtable.dispatch_24 = dispatch_cursor;
  CursorManager manager{&manager_vtable, 0};

  cursor_runtime().allocate = allocate_icon;
  cursor_runtime().icon_dispatch = dispatch_icon;
  allocation_calls = 0;
  resource_read_calls = 0;
  cursor_dispatch_calls = 0;
  icon_dispatch_calls = 0;
  cursor_dispatch_result = true;
  icon_object = DropIconObject{};
  icon_object.field_14 = 0x76543210u;

  assert(call_drop_cursor(&manager, &resource, &output, 0xbbbbbbbu,
                          0x02393756u) == 1u);
  assert(output == &icon_object);
  assert(allocation_calls == 1);
  assert(allocation_size == 0x18u);
  assert(reinterpret_cast<std::uintptr_t>(allocation_name) == 0x01416fbcu);
  assert(allocation_trailer[0] == 0u);
  assert(allocation_trailer[1] == 0u);
  assert(allocation_trailer[2] == 0u);
  assert(allocation_trailer[3] == 0u);
  assert(icon_object.vtable_00 ==
         reinterpret_cast<DropIconObjectVTable*>(0x01416fa8u));
  assert(icon_object.field_04 == 0u);
  assert(resource_read_calls == 1);
  assert(icon_object.field_08 == resource_words[0]);
  assert(icon_object.field_0c == resource_words[1]);
  assert(icon_object.field_10 == resource_words[2]);
  assert(icon_object.field_14 == 0x76543210u);
  assert(cursor_dispatch_calls == 1);
  assert(cursor_dispatch_manager == &manager);
  assert(cursor_dispatch_resource == &resource);
  assert(cursor_dispatch_icon == &icon_object);
  assert(cursor_dispatch_value == 0xbbbbbbbu);
  assert(cursor_dispatch_tag == 0x02393756u);
  assert(icon_dispatch_calls == 1);
  assert(resource.vtable_00 == &resource_vtable);
}

void test_drop_cursor_rejected_keeps_output() {
  ResourceFactoryVTable resource_vtable{};
  resource_vtable.read_10 = read_resource;
  ResourceFactory resource{&resource_vtable};
  DropIconObject* output = reinterpret_cast<DropIconObject*>(0x1u);
  CursorManagerVTable manager_vtable{};
  manager_vtable.dispatch_24 = dispatch_cursor;
  CursorManager manager{&manager_vtable, 0};

  cursor_runtime().allocate = allocate_icon;
  cursor_runtime().icon_dispatch = dispatch_icon;
  allocation_calls = 0;
  cursor_dispatch_calls = 0;
  icon_dispatch_calls = 0;
  cursor_dispatch_result = false;
  icon_object = DropIconObject{};

  assert(call_drop_cursor(&manager, &resource, &output, 0xccccccccu,
                          0x02393756u) == 0u);
  assert(output == reinterpret_cast<DropIconObject*>(0x1u));
  assert(allocation_calls == 1);
  assert(cursor_dispatch_calls == 1);
  assert(cursor_dispatch_value == 0xccccccccu);
  assert(cursor_dispatch_tag == 0x02393756u);
  assert(icon_dispatch_calls == 0);
  assert(resource.vtable_00 == &resource_vtable);
}

void test_set_serializer_type_gate() {
  ImageCore image{};
  assert(call_set_serializer(&image, 0x01be8ca6u) == &image);
  assert(call_set_serializer(&image, 0xee3f516eu) == &image);
  assert(call_set_serializer(&image, 0xeeee8218u) == nullptr);
  assert(call_set_serializer(&image, 0xeec58382u) == nullptr);
  assert(call_set_serializer(&image, 0x01be8ca7u) == nullptr);
  assert(call_set_serializer(&image, 0xee3f516fu) == nullptr);
  assert(call_set_serializer(&image, 0u) == nullptr);
  assert(call_set_serializer(&image, 0xffffffffu) == nullptr);
}

void test_get_real_area_type_paths() {
  WindowCore window{};
  auto* real_area = reinterpret_cast<std::uint8_t*>(&window) + 4;
  assert(real_area != reinterpret_cast<std::uint8_t*>(&window));

  assert(call_get_real_area(&window, 0xee3f516eu) == real_area);
  assert(call_get_real_area(&window, 0xeeee8218u) == real_area);
  assert(call_get_real_area(&window, 0xeec58382u) == nullptr);
  assert(call_get_real_area(&window, 0x01be8ca6u) == nullptr);
  assert(call_get_real_area(&window, 0x12345678u) == nullptr);
  assert(call_get_real_area(&window, 0u) == nullptr);

  assert(call_get_real_area(nullptr, 0xee3f516eu) == nullptr);
  assert(call_get_real_area(nullptr, 0xeeee8218u) == nullptr);
  assert(call_get_real_area(nullptr, 0xeec58382u) == nullptr);
  assert(call_get_real_area(nullptr, 0x12345678u) == nullptr);
}

void test_cursor_id_field() {
  WindowCore window{};
  window.cursor_id_a4 = 0xdeadbeefu;
  assert(re_00575ea0(&window) == 0xdeadbeefu);
  assert(window.cursor_id_a4 == 0xdeadbeefu);
}

void test_reference_count_paths() {
  WindowCore window{};
  assert(re_0095f990(&window) == 1);
  assert(window.ref_count_28 == 1);
  assert(re_0095f990(&window) == 2);
  assert(window.ref_count_28 == 2);

  WindowVTable window_vtable{};
  window_vtable.destroy_08 = destroy_window;
  window.vtable_00 = &window_vtable;
  window.ref_count_28 = 2;
  window_destroy_calls = 0;
  assert(re_0095f9a0(&window) == 1);
  assert(window.ref_count_28 == 1);
  assert(window_destroy_calls == 0);
  window.ref_count_28 = 1;
  assert(re_0095f9a0(&window) == 0);
  assert(window.ref_count_28 == 1);
  assert(window_destroy_calls == 1);
  assert(destroyed_window == &window);
  assert(destroyed_window_value == 1u);
}

void test_drawable_replacement() {
  DrawableVTable drawable_vtable{};
  drawable_vtable.add_ref_00 = add_drawable;
  drawable_vtable.release_04 = release_drawable;
  Drawable old_drawable{&drawable_vtable};
  Drawable new_drawable{&drawable_vtable};
  WindowVTable window_vtable{};
  window_vtable.get_drawable_90 = get_window_drawable;
  WindowCore window{};
  window.vtable_00 = &window_vtable;
  window.drawable_1e4 = &old_drawable;
  drawable_add_calls = 0;
  drawable_release_calls = 0;
  drawable_get_calls = 0;

  assert(call_set_drawable(&window, &old_drawable) == &old_drawable);
  assert(drawable_add_calls == 0);
  assert(drawable_release_calls == 0);
  assert(drawable_get_calls == 0);
  assert(window.drawable_1e4 == &old_drawable);

  assert(call_set_drawable(&window, &new_drawable) == &new_drawable);
  assert(drawable_add_calls == 1);
  assert(drawable_release_calls == 1);
  assert(added_drawable == &new_drawable);
  assert(released_drawable == &old_drawable);
  assert(drawable_get_calls == 1);
  assert(window.drawable_1e4 == &new_drawable);

  assert(call_set_drawable(&window, nullptr) == nullptr);
  assert(drawable_add_calls == 1);
  assert(drawable_release_calls == 2);
  assert(drawable_get_calls == 2);
  assert(window.drawable_1e4 == nullptr);
}

void test_tooltip_teardown() {
  RefObjectVTable first_vtable{};
  first_vtable.release_04 = release_reference;
  first_vtable.destroy_08 = destroy_reference;
  RefObjectVTable release_vtable{};
  release_vtable.release_04 = release_reference;
  RefObject first{&first_vtable};
  RefObject second{&release_vtable};
  RefObject third{&release_vtable};
  RefObject fourth{&release_vtable};
  TooltipCore tooltip{};
  tooltip.field_08 = &first;
  tooltip.field_0c = &second;
  tooltip.field_10 = &third;
  tooltip.field_14 = &fourth;
  tooltip_runtime().deallocate = deallocate_tooltip;
  tooltip_sentinel_0164f328 = 0x12345678u;
  release_order_count = 0;
  destroyed_reference = nullptr;
  deallocated_tooltip = nullptr;

  assert(call_tooltip_teardown(&tooltip, 0u) == &tooltip);
  assert(release_order_count == 3);
  assert(release_order[0] == &fourth);
  assert(release_order[1] == &third);
  assert(release_order[2] == &second);
  assert(destroyed_reference == &first);
  assert(tooltip.vtable_00 == reinterpret_cast<TooltipCoreVTable*>(0x013ec458));
  assert(tooltip_sentinel_0164f328 == 0u);
  assert(deallocated_tooltip == nullptr);

  TooltipCore empty{};
  assert(call_tooltip_teardown(&empty, 1u) == &empty);
  assert(deallocated_tooltip == &empty);
}

void test_allocation_stubs_return_null() {
  assert(re_00951220(0x123456abu, 2u, 3u, 4u, 5u) == nullptr);
  assert(re_00951230(0x123456abu, 2u, 3u) == nullptr);
}

}

int main() {
  test_drop_cursor_gate_reads_fourth_stack_word();
  test_drop_cursor_accepts_and_writes_output();
  test_drop_cursor_rejected_keeps_output();
  test_set_serializer_type_gate();
  test_get_real_area_type_paths();
  test_cursor_id_field();
  test_reference_count_paths();
  test_drawable_replacement();
  test_tooltip_teardown();
  test_allocation_stubs_return_null();
  return 0;
}
