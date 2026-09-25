#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "zoom_boundary_00834fa0.hpp"

namespace openspore::reconstruction::pkg18_ui_space {
namespace {

using Object = ZoomObject;
using Owner = ZoomOwner;
using Vtable = ZoomVtable;
using Word = Opaque;

std::vector<std::string> events;
std::array<Object, 32> objects{};
alignas(Object) std::array<unsigned char, 0x560> factory_root{};
Vtable vtable{};
std::size_t object_index;
bool factory_available;
bool probe_result;
bool lookup_result;
bool recover_null_target;
Object* recovered_target;
Object* service_object;
Word probed_key[3];
Word registered_key[3];
Opaque probe_installed;
Opaque probe_requested;
Opaque error_lookup_receiver;
Opaque error_lookup_id;
Opaque slot_d8_receiver;
Opaque slot_d8_argument;
Opaque resource_apply_target;
Opaque resource_receiver;
Opaque resource_id;
std::vector<Opaque> final_service_arguments;
std::vector<Opaque> slot_104_arguments;

Word load_word(const void* base, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, static_cast<const unsigned char*>(base) + offset,
              sizeof(value));
  return value;
}

void store_word(void* base, std::size_t offset, Word value) {
  std::memcpy(static_cast<unsigned char*>(base) + offset, &value,
              sizeof(value));
}

Word object_word(const void* object) { return reinterpret_cast<Word>(object); }

Object* object_from(Word value) { return reinterpret_cast<Object*>(value); }

Word result_word(Object* object) { return load_word(object->opaque.data(), 4); }

Opaque PKG18_VTABLECALL slot_acquire(Object*) {
  events.emplace_back("acquire");
  return 0;
}

Opaque PKG18_VTABLECALL slot_release(Object*) {
  events.emplace_back("release");
  return 0;
}

Opaque PKG18_VTABLECALL slot_owner(Object* object) {
  events.emplace_back("owner");
  return result_word(object);
}

Opaque PKG18_VTABLECALL slot_value30(Object* object) {
  events.emplace_back("value30");
  return result_word(object);
}

Opaque PKG18_VTABLECALL slot_7c(Object* object, Opaque first, Opaque second) {
  events.emplace_back("slot7c");
  if (object == service_object && first == 1 && second == 0) {
    final_service_arguments.clear();
    final_service_arguments.push_back(first);
    final_service_arguments.push_back(second);
  }
  return 0;
}

Opaque PKG18_VTABLECALL slot_d8(Object* object, Opaque argument) {
  events.emplace_back("slotd8");
  slot_d8_receiver = object_word(object);
  slot_d8_argument = argument;
  return 0;
}

Opaque PKG18_VTABLECALL slot_104(Object*, Opaque argument) {
  events.emplace_back("slot104");
  slot_104_arguments.push_back(argument);
  return 0;
}

Opaque PKG18_VTABLECALL slot_108(Object*, Opaque argument) {
  events.emplace_back("slot108");
  slot_104_arguments.push_back(argument);
  return 0;
}

void initialize_vtable() {
  vtable.slots.fill(0);
  vtable.slots[0x00 / sizeof(Word)] = reinterpret_cast<Word>(slot_acquire);
  vtable.slots[0x04 / sizeof(Word)] = reinterpret_cast<Word>(slot_release);
  vtable.slots[0x10 / sizeof(Word)] = reinterpret_cast<Word>(slot_owner);
  vtable.slots[0x30 / sizeof(Word)] = reinterpret_cast<Word>(slot_value30);
  vtable.slots[0x7c / sizeof(Word)] = reinterpret_cast<Word>(slot_7c);
  vtable.slots[0xd8 / sizeof(Word)] = reinterpret_cast<Word>(slot_d8);
  vtable.slots[0x104 / sizeof(Word)] = reinterpret_cast<Word>(slot_104);
  vtable.slots[0x108 / sizeof(Word)] = reinterpret_cast<Word>(slot_108);
}

Object* new_object(Word result = 0) {
  assert(object_index < objects.size());
  Object* object = &objects[object_index++];
  object->vtable = &vtable;
  object->opaque.fill(0);
  store_word(object->opaque.data(), 4, result);
  return object;
}

Object* source_chain() {
  Object* selected = new_object(5);
  Object* parent = new_object(object_word(selected));
  return new_object(object_word(parent));
}

Object* factory_child() {
  Object* child = reinterpret_cast<Object*>(factory_root.data() + 0x20c);
  child->vtable = &vtable;
  child->opaque.fill(0);
  store_word(child->opaque.data(), 4, object_word(new_object()));
  return child;
}

void reset() {
  events.clear();
  object_index = 0;
  std::memset(objects.data(), 0, sizeof(objects));
  factory_root.fill(0);
  initialize_vtable();
  factory_available = true;
  probe_result = true;
  lookup_result = true;
  recover_null_target = false;
  recovered_target = nullptr;
  service_object = nullptr;
  for (Word& value : probed_key) {
    value = 0;
  }
  for (Word& value : registered_key) {
    value = 0;
  }
  probe_installed = 0;
  probe_requested = 0;
  error_lookup_receiver = 0;
  error_lookup_id = 0;
  slot_d8_receiver = 0;
  slot_d8_argument = 0;
  resource_apply_target = 0;
  resource_receiver = 0;
  resource_id = 0;
  final_service_arguments.clear();
  slot_104_arguments.clear();
}

bool has_event(const char* value) {
  for (const std::string& event : events) {
    if (event == value) {
      return true;
    }
  }
  return false;
}

void store_owner_object(Owner& owner, std::size_t offset, Object* object) {
  store_word(owner.bytes.data(), offset, object_word(object));
}

Object* load_owner_object(const Owner& owner, std::size_t offset) {
  return object_from(load_word(owner.bytes.data(), offset));
}

void prepare_zoom(Object* zoom, Object* view) {
  store_word(zoom->opaque.data(), 4, object_word(view));
}

}

}

extern "C" std::uint8_t __cdecl pkg18_re_004eb930(
    const openspore::reconstruction::pkg18_ui_space::Opaque* installed,
    const openspore::reconstruction::pkg18_ui_space::Opaque* requested) {
  using namespace openspore::reconstruction::pkg18_ui_space;
  probe_installed = object_word(installed);
  probe_requested = object_word(requested);
  for (std::size_t index = 0; index < 3; ++index) {
    probed_key[index] = requested[index];
  }
  events.emplace_back("resource-probe");
  return probe_result ? 1u : 0u;
}

extern "C" void __fastcall pkg18_re_00834e30(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  using namespace openspore::reconstruction::pkg18_ui_space;
  events.emplace_back("zoom-prepare");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_009512c0() {
  using namespace openspore::reconstruction::pkg18_ui_space;
  events.emplace_back("factory-context");
  return 0x7000u;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __cdecl
pkg18_re_009512d0(openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque) {
  using namespace openspore::reconstruction::pkg18_ui_space;
  events.emplace_back("factory-create");
  return factory_available ? object_word(factory_root.data()) : 0u;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __fastcall
pkg18_re_00989000(openspore::reconstruction::pkg18_ui_space::Opaque owner) {
  using namespace openspore::reconstruction::pkg18_ui_space;
  events.emplace_back("factory-object");
  return owner;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_0080fee0() {
  using namespace openspore::reconstruction::pkg18_ui_space;
  events.emplace_back("error-lookup");
  return 0x7100u;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __fastcall
pkg18_re_00810620(openspore::reconstruction::pkg18_ui_space::Opaque receiver,
                  openspore::reconstruction::pkg18_ui_space::Opaque id) {
  using namespace openspore::reconstruction::pkg18_ui_space;
  error_lookup_receiver = receiver;
  error_lookup_id = id;
  events.emplace_back("error-object");
  return 0x7200u;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __fastcall
pkg18_re_00b5f950(openspore::reconstruction::pkg18_ui_space::Opaque field,
                  openspore::reconstruction::pkg18_ui_space::Opaque object) {
  using namespace openspore::reconstruction::pkg18_ui_space;
  if (recover_null_target && recovered_target != nullptr) {
    store_word(reinterpret_cast<void*>(field), 0,
               object_word(recovered_target));
  } else {
    store_word(reinterpret_cast<void*>(field), 0, object);
  }
  events.emplace_back("null-target-recovery");
  return field;
}

extern "C" std::uint8_t __fastcall pkg18_re_008120d0(
    openspore::reconstruction::pkg18_ui_space::Opaque owner,
    openspore::reconstruction::pkg18_ui_space::Opaque resource,
    openspore::reconstruction::pkg18_ui_space::Opaque one,
    openspore::reconstruction::pkg18_ui_space::Opaque id) {
  using namespace openspore::reconstruction::pkg18_ui_space;
  (void)owner;
  (void)one;
  (void)id;
  const auto* keys = reinterpret_cast<const Opaque*>(resource);
  for (std::size_t index = 0; index < 3; ++index) {
    registered_key[index] = keys[index];
  }
  events.emplace_back("resource-register");
  return lookup_result ? 1u : 0u;
}

extern "C" void __fastcall pkg18_re_008121b0(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque target,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  using namespace openspore::reconstruction::pkg18_ui_space;
  resource_apply_target = target;
  events.emplace_back("resource-apply");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __fastcall
pkg18_re_008105b0(openspore::reconstruction::pkg18_ui_space::Opaque owner,
                  openspore::reconstruction::pkg18_ui_space::Opaque id,
                  openspore::reconstruction::pkg18_ui_space::Opaque) {
  using namespace openspore::reconstruction::pkg18_ui_space;
  resource_receiver = owner;
  resource_id = id;
  events.emplace_back("resource-object");
  return service_object == nullptr ? 0u : object_word(service_object);
}

namespace {

using namespace openspore::reconstruction::pkg18_ui_space;

void test_fast_noop() {
  reset();
  Owner owner{};
  Object* source = source_chain();
  Object* target = new_object();
  store_owner_object(owner, 0x68, source);
  store_owner_object(owner, 0x6c, target);
  store_word(owner.bytes.data(), 0x48, 0x11111111u);
  store_word(owner.bytes.data(), 0x4c, 0x22222222u);
  store_word(owner.bytes.data(), 0x50, 0x33333333u);

  assert(
      pkg18_text_zoom_rebind_00834fa0(&owner, source, target, 0, 0, 1, 2, 3));
  assert(events.size() == 4);
  assert(events[0] == "owner");
  assert(events[1] == "owner");
  assert(events[2] == "value30");
  assert(events[3] == "resource-probe");
  assert(probed_key[0] == 1);
  assert(probed_key[1] == 2);
  assert(probed_key[2] == 3);
  assert(!has_event("zoom-prepare"));
  assert(!has_event("factory-context"));
  assert(!has_event("resource-object"));
}

void test_rebind_order() {
  reset();
  Owner owner{};
  Object* source = source_chain();
  Object* old_source = new_object();
  Object* old_zoom = new_object();
  Object* old_target = new_object();
  Object* old_mode = new_object();
  Object* target = new_object();
  Object* mode = new_object();
  store_owner_object(owner, 0x68, old_source);
  store_owner_object(owner, 0x64, old_zoom);
  store_owner_object(owner, 0x6c, old_target);
  store_owner_object(owner, 0x70, old_mode);
  store_word(owner.bytes.data(), 0x0c, 0xc0deu);
  service_object = new_object();
  factory_child();

  assert(pkg18_text_zoom_rebind_00834fa0(
      &owner, source, target, object_word(mode), 0x1234u, 1u, 2u, 3u));
  assert(load_word(owner.bytes.data(), 0x54) == 0x1234u);
  assert(load_owner_object(owner, 0x68) == source);
  assert(load_owner_object(owner, 0x6c) == target);
  assert(load_owner_object(owner, 0x70) == mode);
  assert(slot_d8_receiver == object_word(target));
  assert(slot_d8_argument != 0);
  assert(resource_apply_target == object_word(target));
  assert(resource_receiver == object_word(owner.bytes.data() + 0x30));
  assert(resource_id == 0x0626e3b8u);
  assert(has_event("zoom-prepare"));
  assert(has_event("slot108"));
  assert(has_event("slot104"));
  assert(has_event("resource-register"));
  assert(has_event("resource-apply"));
  std::size_t acquire_count = 0;
  std::size_t release_count = 0;
  for (const std::string& event : events) {
    acquire_count += event == "acquire" ? 1u : 0u;
    release_count += event == "release" ? 1u : 0u;
  }
  assert(acquire_count == 4);
  assert(release_count == 4);
  assert(final_service_arguments == std::vector<Opaque>({1u, 0u}));
}

void test_resource_key_fallback() {
  reset();
  Owner owner{};
  Object* source = source_chain();
  Object* zoom = new_object();
  Object* target = new_object();
  Object* mode = new_object();
  Object* zoom_view = new_object();
  prepare_zoom(zoom, zoom_view);
  store_owner_object(owner, 0x64, zoom);
  Object* created = factory_child();
  lookup_result = true;

  assert(pkg18_text_zoom_rebind_00834fa0(&owner, source, target,
                                         object_word(mode), 0, 0x0164f240u,
                                         0x0164f244u, 0x0164f248u));
  assert(has_event("factory-object"));
  assert(load_owner_object(owner, 0x64) == created);
  assert(registered_key[0] == 0x0164f234u);
  assert(registered_key[1] == 0x0164f238u);
  assert(registered_key[2] == 0x0164f23cu);
  assert(load_word(owner.bytes.data(), 0x48) == 0x0164f234u);
  assert(load_word(owner.bytes.data(), 0x4c) == 0x0164f238u);
  assert(load_word(owner.bytes.data(), 0x50) == 0x0164f23cu);
}

void test_null_target_recovery() {
  reset();
  Owner owner{};
  Object* source = source_chain();
  Object* zoom = new_object();
  Object* zoom_view = new_object();
  Object* mode = new_object();
  prepare_zoom(zoom, zoom_view);
  store_owner_object(owner, 0x64, zoom);
  factory_child();
  recovered_target = new_object();
  recover_null_target = true;

  assert(pkg18_text_zoom_rebind_00834fa0(&owner, source, nullptr,
                                         object_word(mode), 0, 1u, 2u, 3u));
  assert(load_owner_object(owner, 0x6c) == recovered_target);
  assert(slot_d8_receiver == object_word(recovered_target));
  assert(resource_apply_target == object_word(recovered_target));
  assert(error_lookup_id == 0x05b598f6u);
  assert(has_event("null-target-recovery"));
}

void test_service_result() {
  reset();
  Owner owner{};
  Object* source = source_chain();
  Object* target = new_object();
  Object* mode = new_object();
  Object* zoom = new_object();
  Object* zoom_view = new_object();
  prepare_zoom(zoom, zoom_view);
  store_owner_object(owner, 0x64, zoom);
  factory_child();
  service_object = new_object();

  assert(pkg18_text_zoom_rebind_00834fa0(&owner, source, target,
                                         object_word(mode), 0, 1u, 2u, 3u));
  assert(final_service_arguments == std::vector<Opaque>({1u, 0u}));
  assert(resource_receiver == object_word(owner.bytes.data() + 0x30));
  assert(resource_id == 0x0626e3b8u);
}

void test_null_source() {
  reset();
  Owner owner{};
  assert(!pkg18_text_zoom_rebind_00834fa0(&owner, nullptr, nullptr, 0, 0, 1, 2,
                                          3));
  assert(events.empty());
}

}

int main() {
  test_fast_noop();
  test_rebind_order();
  test_resource_key_fallback();
  test_null_target_recovery();
  test_service_result();
  test_null_source();
}
