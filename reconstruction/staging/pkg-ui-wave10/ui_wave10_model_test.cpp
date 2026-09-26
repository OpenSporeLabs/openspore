#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "ui_wave10.hpp"

namespace openspore::reconstruction::pkg_ui_wave10 {

namespace model {

extern "C" OpaqueService* pkg_ui_wave10_g_provider_015fd8a8;
extern "C" Opaque pkg_ui_wave10_g_allocator_013cc4a8;

enum class Kind : std::uint8_t {
  alloc,
  dealloc,
  service_init,
  service_detach,
  service_attach,
  binding_drop,
  binding_retire,
  service_destroy,
  entity,
  set_property,
  commit,
  lookup,
  service_fetch,
  register_id,
  enable,
  bind,
  registry_fetch,
  registry_resolve,
  produce,
  consume,
  provider_fetch,
  provider_resolve,
  release,
  array_read,
  string_hash,
  string_allocate,
  vector_erase,
  vector_insert,
};

struct Event {
  Kind kind;
  Opaque self;
  Opaque arg0;
  Opaque arg1;
  Opaque arg2;
};

constexpr std::size_t kEventCapacity = 1024;
Event events[kEventCapacity]{};
std::size_t event_count = 0;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

void add(Kind kind, Opaque self, Opaque arg0 = 0, Opaque arg1 = 0,
         Opaque arg2 = 0) {
  check(event_count < kEventCapacity);
  events[event_count] = Event{kind, self, arg0, arg1, arg2};
  event_count += 1;
}

std::size_t index_of(Kind kind, std::size_t from = 0) {
  for (std::size_t i = from; i < event_count; i += 1) {
    if (events[i].kind == kind) {
      return i;
    }
  }
  return event_count;
}

std::size_t nth_of(Kind kind, std::size_t ordinal) {
  std::size_t seen = 0;
  for (std::size_t i = 0; i < event_count; i += 1) {
    if (events[i].kind == kind) {
      if (seen == ordinal) {
        return i;
      }
      seen += 1;
    }
  }
  return event_count;
}

std::size_t count_of(Kind kind) {
  std::size_t total = 0;
  for (std::size_t i = 0; i < event_count; i += 1) {
    if (events[i].kind == kind) {
      total += 1;
    }
  }
  return total;
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

template <typename Function>
Opaque function_word(Function function) {
  static_assert(sizeof(Opaque) == sizeof(Function),
                "UI wave 10 function pointer width mismatch");
  Opaque word{};
  std::memcpy(&word, &function, sizeof(word));
  return word;
}

template <typename Function>
Function function_from(Opaque word) {
  static_assert(sizeof(Opaque) == sizeof(Function),
                "UI wave 10 function pointer width mismatch");
  Function function{};
  std::memcpy(&function, &word, sizeof(function));
  return function;
}

OpaqueSlotVTable slot_vtable{};
OpaqueBindingVTable binding_vtable{};
OpaqueService24VTable service24_vtable{};
OpaqueServiceVTable provider_vtable{};
OpaqueServiceVTable player_vtable{};
OpaqueServiceVTable binder_vtable{};
OpaqueServiceVTable alt_vtable{};
OpaqueCarrierVTable carrier_vtable{};
OpaqueRegistryVTable registry_vtable{};
OpaqueService provider_service{};
OpaqueService player_service{};
OpaqueService binder_service{};
OpaqueService alt_service{};
OpaqueSlot provider_slot{};
OpaqueSlot acquired_slot{};
OpaqueSlot late_slot{};
OpaqueSlot early_slot{};

Opaque* alloc_block = nullptr;
std::uint8_t alloc_storage[8][0x40]{};
std::size_t alloc_index = 0;
bool alloc_fail_next = false;
Opaque alloc_size = 0;
Opaque alloc_tag = 0;

OpaqueSlot* acquired_value = nullptr;
bool release_acquired = true;
OpaqueSlot* resolve_value = nullptr;
Opaque provider_resolve_arg0 = 0;
Opaque provider_resolve_arg1 = 0;
Opaque* provider_resolve_out = nullptr;

bool array_read_result = true;
Opaque array_read_count = 0;
Opaque* array_read_entries = nullptr;
Opaque array_read_id = 0;
Opaque* array_read_count_out = nullptr;
Opaque** array_read_entries_out = nullptr;

Opaque hash_results[16]{};
std::size_t hash_index = 0;
Opaque hash_seed = 0;
int hash_mode = 0;
Opaque hash_text = 0;

Opaque* string_alloc_results[16]{};
std::size_t string_alloc_index = 0;
Opaque string_alloc_source = 0;
Opaque string_alloc_destination = 0;
Opaque string_alloc_size = 0;
Opaque* string_alloc_storage[16]{};
Opaque* make_string_storage(std::size_t index) {
  string_alloc_storage[index] =
      reinterpret_cast<Opaque*>(&alloc_storage[index % 8][0]);
  return string_alloc_storage[index];
}

Opaque PKG_UI_WAVE10_THISCALL release_stub(OpaqueSlot* slot);
Opaque PKG_UI_WAVE10_THISCALL register_stub(OpaqueService* service,
                                            OpaqueNamePanel* subobject,
                                            Opaque id);
Opaque PKG_UI_WAVE10_THISCALL enable_stub(OpaqueService* service, Opaque arg0,
                                          Opaque arg1);
void PKG_UI_WAVE10_THISCALL bind_stub(OpaqueService* service, Opaque value);
OpaqueRegistry* PKG_UI_WAVE10_THISCALL
registry_fetch_stub(OpaqueService* service);
OpaqueCarrier* PKG_UI_WAVE10_THISCALL
registry_resolve_stub(OpaqueRegistry* registry, Opaque key);
Opaque PKG_UI_WAVE10_THISCALL produce_stub(OpaqueCarrier* carrier,
                                           Opaque index);
void PKG_UI_WAVE10_THISCALL consume_stub(OpaqueCarrier* carrier, Opaque index,
                                         Opaque carried);
OpaqueSlot* PKG_UI_WAVE10_THISCALL provider_resolve_stub(OpaqueService* service,
                                                         Opaque arg0,
                                                         Opaque arg1,
                                                         OpaqueSlot** out);
Opaque PKG_UI_WAVE10_THISCALL service_detach_stub(OpaqueService24* service);
Opaque PKG_UI_WAVE10_THISCALL service_attach_stub(OpaqueService24* service);
Opaque PKG_UI_WAVE10_THISCALL binding_drop_stub(OpaqueBinding* binding);
Opaque PKG_UI_WAVE10_THISCALL binding_retire_stub(OpaqueBinding* binding);
Opaque* PKG_UI_WAVE10_CDECL string_allocate_stub(Opaque source,
                                                 Opaque* destination,
                                                 Opaque size);

Opaque lookup_results[16]{};
bool lookup_miss = false;
Opaque lookup_key = 0;
Opaque lookup_flag = 0;
OpaqueService* lookup_services[16]{};
Opaque lookup_keys[16]{};
std::size_t lookup_count = 0;

bool registry_enabled = false;
bool carrier_enabled = false;
OpaqueCarrier carrier_object{};
OpaqueRegistry registry_object{};
Opaque carrier_produce_results[8]{};
Opaque carrier_produce_index = 0;

Opaque triple_words[3]{};
Opaque set_property_count = 0;
Opaque set_property_key = 0;
Opaque commit_value = 0;
Opaque commit_count = 0;
Opaque commit_key = 0;
Opaque entity_value = 0;
OpaqueService24* service_destroy_address[8]{};
std::size_t service_destroy_count = 0;
Opaque* deallocated = nullptr;
Opaque dealloc_count = 0;
Opaque register_ids[8]{};
Opaque register_subobjects[8]{};
std::size_t register_count = 0;
Opaque enable_arg0 = 0;
Opaque enable_arg1 = 0;
Opaque bind_arg0 = 0;
Opaque consume_index[8]{};
Opaque consume_carried[8]{};
std::size_t consume_count = 0;
Opaque produce_index[8]{};
std::size_t produce_count = 0;

void reset() {
  event_count = 0;
  alloc_index = 0;
  alloc_fail_next = false;
  alloc_size = 0;
  alloc_tag = 0;
  alloc_block = nullptr;
  acquired_value = nullptr;
  release_acquired = true;
  resolve_value = nullptr;
  provider_resolve_arg0 = 0;
  provider_resolve_arg1 = 0;
  provider_resolve_out = nullptr;
  array_read_result = true;
  array_read_count = 0;
  array_read_entries = nullptr;
  array_read_id = 0;
  array_read_count_out = nullptr;
  array_read_entries_out = nullptr;
  hash_index = 0;
  hash_seed = 0;
  hash_mode = 0;
  hash_text = 0;
  for (std::size_t i = 0; i < 16; i += 1) {
    hash_results[i] = 0;
    string_alloc_results[i] = nullptr;
    lookup_results[i] = 0;
    lookup_services[i] = nullptr;
  }
  lookup_miss = false;
  lookup_key = 0;
  lookup_flag = 0;
  lookup_count = 0;
  string_alloc_index = 0;
  string_alloc_source = 0;
  string_alloc_destination = 0;
  string_alloc_size = 0;
  carrier_produce_index = 0;
  carrier_produce_results[0] = 0x1111u;
  carrier_produce_results[1] = 0x2222u;
  carrier_produce_results[2] = 0x3333u;
  carrier_produce_results[3] = 0x4444u;
  carrier_produce_results[4] = 0x5555u;
  carrier_produce_results[5] = 0x6666u;
  carrier_produce_results[6] = 0x7777u;
  carrier_produce_results[7] = 0x8888u;
  triple_words[0] = 0;
  triple_words[1] = 0;
  triple_words[2] = 0;
  set_property_count = 0;
  set_property_key = 0;
  commit_value = 0;
  commit_count = 0;
  commit_key = 0;
  entity_value = 0;
  service_destroy_count = 0;
  deallocated = nullptr;
  dealloc_count = 0;
  register_count = 0;
  enable_arg0 = 0;
  enable_arg1 = 0;
  bind_arg0 = 0;
  consume_count = 0;
  produce_count = 0;
  slot_vtable.slots_00[1] = function_word(release_stub);
  binding_vtable.slots_00[0] = function_word(binding_drop_stub);
  binding_vtable.slots_00[1] = function_word(binding_retire_stub);
  pkg_ui_wave10_alloc_tag_013eb430 = 0x013eb430u;
  pkg_ui_wave10_vtable_013eb938 = 0x013eb938u;
  pkg_ui_wave10_vtable_013ec458 = 0x013ec458u;
  pkg_ui_wave10_vtable_013f7b54 = pointer_word(&binding_vtable);
  pkg_ui_wave10_vtable_013fe718 = 0x013fe718u;
  pkg_ui_wave10_vtable_013fe728 = 0x013fe728u;
  pkg_ui_wave10_vtable_0149bad8 = 0x0149bad8u;
  service24_vtable.slots_00[0] = function_word(service_detach_stub);
  service24_vtable.slots_00[1] = function_word(service_detach_stub);
  service24_vtable.slots_00[2] = function_word(service_attach_stub);
  provider_vtable.slot_20 = function_word(register_stub);
  provider_vtable.slot_2c = function_word(provider_resolve_stub);
  player_vtable.slot_7c = function_word(enable_stub);
  player_vtable.slot_a8 = function_word(registry_fetch_stub);
  player_vtable.slot_104 = function_word(bind_stub);
  binder_vtable.slot_104 = function_word(bind_stub);
  alt_vtable.slot_a8 = function_word(registry_fetch_stub);
  alt_vtable.slot_104 = function_word(bind_stub);
  carrier_vtable.slot_10 = function_word(produce_stub);
  carrier_vtable.slot_14 = function_word(consume_stub);
  registry_vtable.slot_0c = function_word(registry_resolve_stub);
  provider_service.vtable_00 = &provider_vtable;
  player_service.vtable_00 = &player_vtable;
  binder_service.vtable_00 = &binder_vtable;
  alt_service.vtable_00 = &alt_vtable;
  provider_slot.vtable_00 = &slot_vtable;
  acquired_slot.vtable_00 = &slot_vtable;
  late_slot.vtable_00 = &slot_vtable;
  early_slot.vtable_00 = &slot_vtable;
  carrier_object.vtable_00 = &carrier_vtable;
  registry_object.vtable_00 = &registry_vtable;
  provider_vtable.slots_00[1] = 0;
  player_vtable.slots_00[1] = 0;
  binder_vtable.slots_00[1] = 0;
  alt_vtable.slots_00[1] = 0;
  registry_enabled = false;
  carrier_enabled = false;
  pkg_ui_wave10_g_provider_015fd8a8 = &provider_service;
  pkg_ui_wave10_g_allocator_013cc4a8 = function_word(string_allocate_stub);
}

Opaque PKG_UI_WAVE10_THISCALL binding_drop_stub(OpaqueBinding* binding) {
  add(Kind::binding_drop, pointer_word(binding));
  return 0;
}

Opaque PKG_UI_WAVE10_THISCALL binding_retire_stub(OpaqueBinding* binding) {
  add(Kind::binding_retire, pointer_word(binding));
  return 0;
}

Opaque PKG_UI_WAVE10_THISCALL service_detach_stub(OpaqueService24* service) {
  add(Kind::service_detach, pointer_word(service));
  return 0;
}

Opaque PKG_UI_WAVE10_THISCALL service_attach_stub(OpaqueService24* service) {
  add(Kind::service_attach, pointer_word(service));
  return 0;
}

Opaque PKG_UI_WAVE10_THISCALL release_stub(OpaqueSlot* slot) {
  add(Kind::release, pointer_word(slot));
  return 0;
}

Opaque PKG_UI_WAVE10_THISCALL register_stub(OpaqueService* service,
                                            OpaqueNamePanel* subobject,
                                            Opaque id) {
  check(register_count < 8);
  register_subobjects[register_count] = pointer_word(subobject);
  register_ids[register_count] = id;
  register_count += 1;
  add(Kind::register_id, pointer_word(service), pointer_word(subobject), id);
  return 0;
}

Opaque PKG_UI_WAVE10_THISCALL enable_stub(OpaqueService* service, Opaque arg0,
                                          Opaque arg1) {
  enable_arg0 = arg0;
  enable_arg1 = arg1;
  add(Kind::enable, pointer_word(service), arg0, arg1);
  return 0;
}

void PKG_UI_WAVE10_THISCALL bind_stub(OpaqueService* service, Opaque value) {
  bind_arg0 = value;
  add(Kind::bind, pointer_word(service), value);
}

OpaqueRegistry* PKG_UI_WAVE10_THISCALL
registry_fetch_stub(OpaqueService* service) {
  add(Kind::registry_fetch, pointer_word(service));
  return registry_enabled ? &registry_object : nullptr;
}

OpaqueCarrier* PKG_UI_WAVE10_THISCALL
registry_resolve_stub(OpaqueRegistry* registry, Opaque key) {
  add(Kind::registry_resolve, pointer_word(registry), key);
  return carrier_enabled ? &carrier_object : nullptr;
}

Opaque PKG_UI_WAVE10_THISCALL produce_stub(OpaqueCarrier* carrier,
                                           Opaque index) {
  check(produce_count < 8);
  produce_index[produce_count] = index;
  produce_count += 1;
  add(Kind::produce, pointer_word(carrier), index,
      carrier_produce_results[index & 7u]);
  return carrier_produce_results[index & 7u];
}

void PKG_UI_WAVE10_THISCALL consume_stub(OpaqueCarrier* carrier, Opaque index,
                                         Opaque carried) {
  check(consume_count < 8);
  consume_index[consume_count] = index;
  consume_carried[consume_count] = carried;
  consume_count += 1;
  add(Kind::consume, pointer_word(carrier), index, carried);
}

OpaqueSlot* PKG_UI_WAVE10_THISCALL provider_resolve_stub(OpaqueService* service,
                                                         Opaque arg0,
                                                         Opaque arg1,
                                                         OpaqueSlot** out) {
  provider_resolve_arg0 = arg0;
  provider_resolve_arg1 = arg1;
  provider_resolve_out = reinterpret_cast<Opaque*>(out);
  add(Kind::provider_resolve, pointer_word(service), arg0, arg1,
      pointer_word(out));
  if (out != nullptr) {
    *out = resolve_value;
  }
  return resolve_value;
}

bool PKG_UI_WAVE10_CDECL array_read_stub(OpaqueSlot* list, Opaque property_id,
                                         Opaque* count, Opaque** entries) {
  array_read_id = property_id;
  array_read_count_out = count;
  array_read_entries_out = reinterpret_cast<Opaque**>(entries);
  add(Kind::array_read, pointer_word(list), property_id,
      count != nullptr ? *count : 0,
      entries != nullptr ? pointer_word(*entries) : 0);
  if (count != nullptr) {
    *count = array_read_count;
  }
  if (entries != nullptr) {
    *entries = array_read_entries;
  }
  return array_read_result;
}

Opaque PKG_UI_WAVE10_CDECL string_hash_stub(const std::uint16_t* text,
                                            Opaque seed, int mode) {
  hash_seed = seed;
  hash_mode = mode;
  hash_text = pointer_word(text);
  const Opaque result = hash_results[hash_index];
  hash_index += 1;
  add(Kind::string_hash, pointer_word(text), seed,
      static_cast<Opaque>(static_cast<std::uint32_t>(mode)), result);
  return result;
}

Opaque* PKG_UI_WAVE10_CDECL string_allocate_stub(Opaque source,
                                                 Opaque* destination,
                                                 Opaque size) {
  string_alloc_source = source;
  string_alloc_destination = pointer_word(destination);
  string_alloc_size = size;
  Opaque* result = string_alloc_results[string_alloc_index];
  string_alloc_index += 1;
  add(Kind::string_allocate, source, pointer_word(destination), size,
      pointer_word(result));
  return result;
}

void PKG_UI_WAVE10_THISCALL vector_erase_stub(OpaqueSettingsVector* vector,
                                              OpaqueSettingsPair* first,
                                              OpaqueSettingsPair* last) {
  add(Kind::vector_erase, pointer_word(vector), pointer_word(first),
      pointer_word(last));
  vector->begin_00 = first;
  vector->end_04 = first;
}

void PKG_UI_WAVE10_THISCALL
vector_insert_stub(OpaqueSettingsVector* vector, OpaqueSettingsPair* position,
                   const OpaqueSettingsPair* value) {
  add(Kind::vector_insert, pointer_word(vector), pointer_word(position),
      pointer_word(value));
  check(position != nullptr);
  *position = *value;
  vector->end_04 = position + 1;
}

}

namespace unresolved_contracts {

extern "C" OpaqueService* pkg_ui_wave10_g_provider_015fd8a8 = nullptr;
extern "C" Opaque pkg_ui_wave10_g_allocator_013cc4a8 = 0;

extern "C" Opaque* PKG_UI_WAVE10_CDECL
pkg_ui_wave10_alloc_00f473a0(Opaque size, Opaque type_tag, Opaque arg_0c,
                             Opaque arg_10, Opaque arg_14, Opaque arg_18) {
  model::check(arg_0c == 0 && arg_10 == 0 && arg_14 == 0 && arg_18 == 0);
  model::alloc_size = size;
  model::alloc_tag = type_tag;
  if (model::alloc_fail_next) {
    model::add(model::Kind::alloc, 0, size, type_tag, 0);
    return nullptr;
  }
  std::uint8_t* block = &model::alloc_storage[model::alloc_index % 8][0];
  std::memset(block, 0, sizeof(model::alloc_storage[0]));
  model::alloc_index += 1;
  model::add(model::Kind::alloc, model::pointer_word(block), size, type_tag, 0);
  return reinterpret_cast<Opaque*>(block);
}

extern "C" void PKG_UI_WAVE10_CDECL
pkg_ui_wave10_free_00f47380(Opaque* pointer) {
  model::dealloc_count += 1;
  model::deallocated = pointer;
  model::add(model::Kind::dealloc, model::pointer_word(pointer));
}

extern "C" void PKG_UI_WAVE10_THISCALL
pkg_ui_wave10_service_init_00810000(OpaqueService24* service) {
  model::add(model::Kind::service_init, model::pointer_word(service));
  service->vtable_00 = &model::service24_vtable;
  service->field_04 = 0;
  service->field_08 = 0;
  service->field_0c = 0;
  service->field_10 = 0;
  service->slot_14 = nullptr;
}

extern "C" void PKG_UI_WAVE10_THISCALL
pkg_ui_wave10_service_destroy_00811fe0(OpaqueService24* service) {
  model::check(model::service_destroy_count < 8);
  model::service_destroy_address[model::service_destroy_count] = service;
  model::service_destroy_count += 1;
  model::add(model::Kind::service_destroy, model::pointer_word(service));
}

extern "C" void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_name_panel_entity_005bfcc0(
    OpaqueNamePanel* object, Opaque entity) {
  model::entity_value = entity;
  object->field_1c = entity;
  model::add(model::Kind::entity, model::pointer_word(object), entity);
}

extern "C" Opaque PKG_UI_WAVE10_THISCALL pkg_ui_wave10_set_property_008120d0(
    OpaqueService24* service, const OpaquePropertyTriple* value, Opaque count,
    Opaque key) {
  model::check(value != nullptr);
  model::triple_words[0] = value->word_00;
  model::triple_words[1] = value->word_04;
  model::triple_words[2] = value->word_08;
  model::set_property_count = count;
  model::set_property_key = key;
  model::add(model::Kind::set_property, model::pointer_word(service), count,
             key, value->word_00);
  return 1;
}

extern "C" Opaque PKG_UI_WAVE10_THISCALL pkg_ui_wave10_commit_008121b0(
    OpaqueService24* service, Opaque value, Opaque count, Opaque key) {
  model::commit_value = value;
  model::commit_count = count;
  model::commit_key = key;
  model::add(model::Kind::commit, model::pointer_word(service), value, count,
             key);
  return 1;
}

extern "C" Opaque PKG_UI_WAVE10_THISCALL pkg_ui_wave10_lookup_008105b0(
    OpaqueService24* service, Opaque key, Opaque flag) {
  model::check(model::lookup_count < 16);
  model::lookup_keys[model::lookup_count] = key;
  model::lookup_count += 1;
  model::lookup_key = key;
  model::lookup_flag = flag;
  const Opaque result =
      model::lookup_miss ? 0u : model::lookup_results[key % 16u];
  model::add(model::Kind::lookup, model::pointer_word(service), key, flag,
             result);
  return result;
}

extern "C" OpaqueService* PKG_UI_WAVE10_CDECL
pkg_ui_wave10_service_fetch_0067dcc0() {
  model::add(model::Kind::service_fetch, 0);
  return &model::provider_service;
}

extern "C" OpaqueService* PKG_UI_WAVE10_CDECL
pkg_ui_wave10_service_provider_0067de30() {
  model::add(model::Kind::provider_fetch, 0,
             model::pointer_word(pkg_ui_wave10_g_provider_015fd8a8));
  return pkg_ui_wave10_g_provider_015fd8a8;
}

extern "C" Opaque PKG_UI_WAVE10_CDECL pkg_ui_wave10_string_hash_00932f30(
    const std::uint16_t* text, Opaque seed, int mode) {
  return model::string_hash_stub(text, seed, mode);
}

extern "C" bool PKG_UI_WAVE10_CDECL pkg_ui_wave10_get_array_006a0bc0(
    OpaqueSlot* list, Opaque property_id, Opaque* count, Opaque** entries) {
  return model::array_read_stub(list, property_id, count, entries);
}

extern "C" void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_vector_erase_00d018d0(
    OpaqueSettingsVector* vector, OpaqueSettingsPair* first,
    OpaqueSettingsPair* last) {
  model::vector_erase_stub(vector, first, last);
}

extern "C" void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_vector_insert_00601b40(
    OpaqueSettingsVector* vector, OpaqueSettingsPair* position,
    const OpaqueSettingsPair* value) {
  model::vector_insert_stub(vector, position, value);
}

}

namespace {

using namespace model;

using NamePanelEntry = void(PKG_UI_WAVE10_THISCALL*)(OpaqueNamePanel*, Opaque,
                                                     Opaque, Opaque, Opaque,
                                                     Opaque);
using SettingsEntry = void(PKG_UI_WAVE10_THISCALL*)(OpaqueSettings*);
using ArchiveEntry =
    OpaqueImageArchive*(PKG_UI_WAVE10_THISCALL*)(OpaqueImageArchive*, Opaque);

NamePanelEntry name_panel_entry() {
  return model::function_from<NamePanelEntry>(
      model::function_word(pkg_ui_wave10_005bfd40));
}

SettingsEntry settings_entry() {
  return model::function_from<SettingsEntry>(
      model::function_word(pkg_ui_wave10_00603650));
}

ArchiveEntry archive_entry() {
  return model::function_from<ArchiveEntry>(
      model::function_word(pkg_ui_wave10_00635700));
}

void prime_settings(OpaqueSettings* object, OpaqueSettingsPair* storage,
                    Opaque capacity) {
  object->vector_40.begin_00 = storage;
  object->vector_40.end_04 = storage;
  object->vector_40.cap_08 = storage + capacity;
  std::memset(storage, 0, sizeof(OpaqueSettingsPair) * 8);
}

OpaqueSettingsPair settings_storage[8]{};

void test_archive_teardown_order() {
  const auto entry = archive_entry();
  OpaqueImageArchive archive{};
  Opaque derived_b = pkg_ui_wave10_vtable_013fe728;
  Opaque derived_a = pkg_ui_wave10_vtable_013fe718;
  archive.vtable_00 = reinterpret_cast<Opaque*>(&derived_b);
  archive.vtable_04 = reinterpret_cast<Opaque*>(&derived_a);
  archive.slot_68 = &late_slot;
  archive.slot_64 = &early_slot;

  reset();
  check(entry(&archive, 0) == &archive);
  check(model::event_count == 4);
  check(model::events[0].kind == model::Kind::release);
  check(model::events[0].self == model::pointer_word(&late_slot));
  check(model::events[1].kind == model::Kind::release);
  check(model::events[1].self == model::pointer_word(&early_slot));
  check(model::events[2].kind == model::Kind::service_destroy);
  check(model::events[2].self == model::pointer_word(&archive) + 0x2c);
  check(model::events[3].kind == model::Kind::service_destroy);
  check(model::events[3].self == model::pointer_word(&archive) + 0x14);
  check(reinterpret_cast<Opaque>(archive.vtable_00) ==
        pkg_ui_wave10_vtable_013eb938);
  check(reinterpret_cast<Opaque>(archive.vtable_04) ==
        pkg_ui_wave10_vtable_013ec458);
  check(model::dealloc_count == 0);

  reset();
  check(entry(&archive, 1) == &archive);
  check(model::event_count == 5);
  check(model::events[4].kind == model::Kind::dealloc);
  check(model::deallocated == reinterpret_cast<Opaque*>(&archive));

  reset();
  check(entry(&archive, 2) == &archive);
  check(model::dealloc_count == 0);

  reset();
  check(entry(&archive, 3) == &archive);
  check(model::dealloc_count == 1);

  reset();
  check(entry(&archive, 0x0100u) == &archive);
  check(model::dealloc_count == 0);
}

void test_archive_base_subobject_thunk() {
  const auto entry = archive_entry();
  OpaqueImageArchive archive{};
  Opaque derived_b = pkg_ui_wave10_vtable_013fe728;
  Opaque derived_a = pkg_ui_wave10_vtable_013fe718;
  archive.vtable_00 = reinterpret_cast<Opaque*>(&derived_b);
  archive.vtable_04 = reinterpret_cast<Opaque*>(&derived_a);
  archive.slot_64 = &early_slot;
  archive.slot_68 = nullptr;

  auto* subobject = reinterpret_cast<OpaqueImageArchive*>(
      reinterpret_cast<std::uintptr_t>(&archive) + 0x04u);
  auto* adjusted = reinterpret_cast<OpaqueImageArchive*>(
      reinterpret_cast<std::uintptr_t>(subobject) - 0x04u);
  reset();
  check(entry(adjusted, 1) == &archive);
  check(model::event_count == 4);
  check(model::events[0].kind == model::Kind::release);
  check(model::events[0].self == model::pointer_word(&early_slot));
  check(model::events[1].kind == model::Kind::service_destroy);
  check(model::events[1].self == model::pointer_word(&archive) + 0x2c);
  check(model::events[2].kind == model::Kind::service_destroy);
  check(model::events[2].self == model::pointer_word(&archive) + 0x14);
  check(model::events[3].kind == model::Kind::dealloc);
  check(model::deallocated == reinterpret_cast<Opaque*>(&archive));
}

void test_settings_handle_gates() {
  const auto entry = settings_entry();
  OpaqueSettings object{};

  reset();
  model::resolve_value = nullptr;
  entry(&object);
  check(model::count_of(model::Kind::provider_resolve) == 1);
  check(model::provider_resolve_arg0 == 0xe280c622u);
  check(model::provider_resolve_arg1 == 0);
  check(model::provider_resolve_out != nullptr);
  check(model::count_of(model::Kind::array_read) == 0);
  check(model::count_of(model::Kind::vector_erase) == 0);
  check(model::count_of(model::Kind::release) == 0);

  reset();
  model::resolve_value = &model::acquired_slot;
  model::array_read_result = false;
  prime_settings(&object, settings_storage, 8);
  entry(&object);
  check(model::array_read_id == 0x9f9c97deu);
  check(model::count_of(model::Kind::vector_erase) == 0);
  check(model::count_of(model::Kind::release) == 1);
  check(model::events[model::event_count - 1].self ==
        model::pointer_word(&model::acquired_slot));

  reset();
  model::resolve_value = &model::acquired_slot;
  model::array_read_result = true;
  model::array_read_count = 0;
  prime_settings(&object, settings_storage, 8);
  entry(&object);
  check(model::count_of(model::Kind::vector_erase) == 0);
  check(model::count_of(model::Kind::release) == 1);

  reset();
  model::resolve_value = &model::acquired_slot;
  model::array_read_count = 0xffffffffu;
  prime_settings(&object, settings_storage, 8);
  entry(&object);
  check(model::count_of(model::Kind::vector_erase) == 0);
  check(model::count_of(model::Kind::release) == 1);
}

void test_settings_fill_loop() {
  const auto entry = settings_entry();
  OpaqueSettings object{};
  Opaque entries[32]{};
  for (std::size_t i = 0; i < 4; i += 1) {
    entries[i * 8] = 0x1000u + static_cast<Opaque>(i);
    entries[i * 8 + 4] = 0x2000u + static_cast<Opaque>(i);
  }

  model::resolve_value = &model::acquired_slot;
  model::array_read_result = true;
  model::array_read_count = 4;
  model::array_read_entries = entries;
  model::hash_results[0] = 0xa1u;
  model::hash_results[1] = 0xb2u;
  model::string_alloc_results[0] = model::make_string_storage(0);
  model::string_alloc_results[1] = model::make_string_storage(1);
  unresolved_contracts::pkg_ui_wave10_g_allocator_013cc4a8 =
      model::function_word(model::string_allocate_stub);

  reset();
  model::resolve_value = &model::acquired_slot;
  model::array_read_count = 4;
  model::array_read_entries = entries;
  model::hash_results[0] = 0xa1u;
  model::hash_results[1] = 0xb2u;
  model::string_alloc_results[0] = model::make_string_storage(0);
  model::string_alloc_results[1] = model::make_string_storage(1);
  prime_settings(&object, settings_storage, 8);
  entry(&object);

  check(model::count_of(model::Kind::vector_erase) == 1);
  const std::size_t erase_index = model::index_of(model::Kind::vector_erase);
  check(model::events[erase_index].self ==
        model::pointer_word(&object.vector_40));
  check(model::events[erase_index].arg0 ==
        model::pointer_word(settings_storage));
  check(model::events[erase_index].arg1 ==
        model::pointer_word(settings_storage));
  check(model::count_of(model::Kind::string_hash) == 2);
  check(model::events[0].kind == model::Kind::provider_fetch);
  check(model::events[1].kind == model::Kind::provider_resolve);
  check(model::events[2].kind == model::Kind::array_read);
  check(model::events[3].kind == model::Kind::vector_erase);
  check(model::events[4].kind == model::Kind::string_hash);
  check(model::events[4].self == model::pointer_word(entries));
  check(model::events[4].arg0 == 0x811c9dc5u);
  check(model::events[4].arg1 == 1);
  check(model::events[5].kind == model::Kind::string_allocate);
  check(model::events[5].self == 0x2000u + 4u);
  check(model::events[5].arg0 == 0);
  check(model::events[5].arg1 == 0x10u);
  check(model::events[6].kind == model::Kind::string_hash);
  check(model::events[6].self == model::pointer_word(entries + 8));
  check(model::events[7].kind == model::Kind::string_allocate);
  check(model::events[7].self == 0x2001u + 4u);
  check(model::events[model::event_count - 1].kind == model::Kind::release);
  check(model::count_of(model::Kind::vector_insert) == 0);

  check(object.vector_40.begin_00 == settings_storage);
  check(object.vector_40.end_04 == settings_storage + 2);
  check(settings_storage[0].hash == 0xa1u);
  check(settings_storage[0].buffer == model::string_alloc_results[0]);
  check(settings_storage[1].hash == 0xb2u);
  check(settings_storage[1].buffer == model::string_alloc_results[1]);

  reset();
  model::resolve_value = &model::acquired_slot;
  model::array_read_count = 4;
  model::array_read_entries = entries;
  model::hash_results[0] = 0xa1u;
  model::hash_results[1] = 0xb2u;
  model::string_alloc_results[0] = model::make_string_storage(2);
  model::string_alloc_results[1] = model::make_string_storage(3);
  prime_settings(&object, settings_storage, 0);
  entry(&object);
  check(model::count_of(model::Kind::vector_insert) == 2);
  check(model::events[model::index_of(model::Kind::vector_insert)].self ==
        model::pointer_word(&object.vector_40));
  check(model::events[model::index_of(model::Kind::vector_insert)].arg0 ==
        model::pointer_word(settings_storage));
  check(object.vector_40.end_04 == settings_storage + 2);
  check(settings_storage[0].hash == 0xa1u);
  check(settings_storage[1].hash == 0xb2u);

  reset();
  model::resolve_value = &model::acquired_slot;
  model::array_read_count = 4;
  model::array_read_entries = entries;
  model::hash_results[0] = 0u;
  model::hash_results[1] = 0xb2u;
  model::string_alloc_results[0] = model::make_string_storage(4);
  model::string_alloc_results[1] = model::make_string_storage(5);
  prime_settings(&object, settings_storage, 8);
  entry(&object);
  check(object.vector_40.end_04 == settings_storage + 1);
  check(settings_storage[0].hash == 0xb2u);

  reset();
  model::resolve_value = &model::acquired_slot;
  model::array_read_count = 4;
  model::array_read_entries = entries;
  model::hash_results[0] = 0xa1u;
  model::hash_results[1] = 0xb2u;
  model::string_alloc_results[0] = nullptr;
  model::string_alloc_results[1] = model::make_string_storage(6);
  prime_settings(&object, settings_storage, 8);
  entry(&object);
  check(object.vector_40.end_04 == settings_storage + 1);
  check(settings_storage[0].hash == 0xb2u);
}

void prime_panel(OpaqueNamePanel* panel) {
  panel->byte_10 = 0xffu;
  panel->byte_11 = 0xffu;
  panel->slot_14 = nullptr;
  panel->slot_18 = nullptr;
  panel->field_1c = 0;
  panel->field_20 = 0xffffffffu;
  panel->field_34 = 0xffffffffu;
}

void test_name_panel_fields_and_registers() {
  const auto entry = name_panel_entry();
  OpaqueNamePanel panel{};
  prime_panel(&panel);

  reset();
  model::lookup_miss = true;
  entry(&panel, 0x11u, 0x22u, 0x33u, 0u, 0x44u);

  check(model::alloc_size == 0x18u);
  check(model::alloc_tag == pkg_ui_wave10_alloc_tag_013eb430);
  check(model::count_of(model::Kind::service_init) == 1);
  check(panel.slot_18 != nullptr);
  check(panel.byte_11 == 0u);
  check(panel.byte_10 == 0u);
  check(panel.field_20 == 0u);
  check(panel.field_34 == 0x22u);
  check(panel.field_1c == 0x11u);
  check(model::entity_value == 0x11u);
  check(model::triple_words[0] == 0x33u);
  check(model::triple_words[1] == 0x510a95bu);
  check(model::triple_words[2] == 0x40464100u);
  check(model::set_property_count == 1);
  check(model::set_property_key == 0x5b598fau);
  check(model::commit_value == 0x22u);
  check(model::commit_count == 1);
  check(model::commit_key == 0x5b598fau);
  check(model::events[model::index_of(model::Kind::set_property)].self ==
        model::pointer_word(panel.slot_18));
  check(model::events[model::index_of(model::Kind::commit)].self ==
        model::pointer_word(panel.slot_18));

  check(model::register_count == 3);
  check(model::register_ids[0] == 0x7aa519dcu);
  check(model::register_ids[1] == 0x14418c3fu);
  check(model::register_ids[2] == 0x01ee1001u);
  for (std::size_t i = 0; i < 3; i += 1) {
    check(model::register_subobjects[i] == model::pointer_word(&panel) + 0x04u);
  }
  check(model::lookup_keys[0] == 0x5415e48u);
  check(model::lookup_flag == 1u);
  check(model::count_of(model::Kind::enable) == 0);
  check(model::count_of(model::Kind::registry_resolve) == 0);
  check(model::count_of(model::Kind::produce) == 0);
  check(model::count_of(model::Kind::consume) == 0);
  check(panel.slot_14 == nullptr);
  check(model::count_of(model::Kind::bind) == 0);

  reset();
  prime_panel(&panel);
  model::lookup_miss = false;
  model::lookup_results[0x5415e48u % 16u] = 0x77u;
  model::lookup_results[0x272eb68eu % 16u] =
      model::pointer_word(&model::player_service);
  model::lookup_results[0x56c1e03u % 16u] =
      model::pointer_word(&model::alt_service);
  model::lookup_results[0xc7ceb1bdu % 16u] =
      model::pointer_word(&model::binder_service);
  model::registry_enabled = true;
  model::carrier_enabled = true;
  entry(&panel, 0x11u, 0x22u, 0x33u, 0u, 0x44u);

  check(model::register_count == 4);
  check(model::register_ids[3] == 0x073127e6u);
  check(model::register_subobjects[3] == model::pointer_word(&panel) + 0x04u);
  check(model::count_of(model::Kind::enable) == 1);
  check(model::enable_arg0 == 1);
  check(model::enable_arg1 == 1);
  check(model::count_of(model::Kind::registry_fetch) == 2);
  check(model::count_of(model::Kind::registry_resolve) == 2);
  check(model::events[model::index_of(model::Kind::registry_resolve)].arg0 ==
        0x103c1908u);
  check(model::events[model::nth_of(model::Kind::registry_resolve, 1)].arg0 ==
        0x103c1908u);
  check(model::produce_count == 8);
  check(model::consume_count == 8);
  for (std::size_t i = 0; i < 8; i += 1) {
    check(model::produce_index[i] == i);
    check(model::consume_index[i] == i);
    check(model::consume_carried[i] == model::carrier_produce_results[i]);
  }
  check(panel.slot_14 != nullptr);
  check(panel.slot_14->field_08 == 0u);
  check(reinterpret_cast<Opaque>(panel.slot_14->vtable_00) ==
        pkg_ui_wave10_vtable_013f7b54);
  check(reinterpret_cast<Opaque>(panel.slot_14->vtable_04) ==
        pkg_ui_wave10_vtable_0149bad8);
  check(model::count_of(model::Kind::alloc) == 2);
  check(model::events[model::nth_of(model::Kind::alloc, 1)].arg0 == 0x0cu);
  check(model::events[model::nth_of(model::Kind::alloc, 1)].arg1 ==
        pkg_ui_wave10_alloc_tag_013eb430);
  check(model::count_of(model::Kind::bind) == 2);
  check(model::events[model::index_of(model::Kind::bind)].arg0 ==
        model::pointer_word(&panel));
  check(model::events[model::nth_of(model::Kind::bind, 1)].arg0 ==
        model::pointer_word(panel.slot_14));
  check(model::nth_of(model::Kind::bind, 1) == model::event_count - 1);
}

void test_name_panel_flag_gates_carrier_copy() {
  const auto entry = name_panel_entry();
  OpaqueNamePanel panel{};

  auto prime = [&panel]() {
    prime_panel(&panel);
    model::reset();
    model::lookup_miss = false;
    model::lookup_results[0x272eb68eu % 16u] =
        model::pointer_word(&model::player_service);
    model::lookup_results[0x56c1e03u % 16u] =
        model::pointer_word(&model::alt_service);
    model::lookup_results[0xc7ceb1bdu % 16u] =
        model::pointer_word(&model::binder_service);
    model::registry_enabled = true;
    model::carrier_enabled = true;
  };

  prime();
  entry(&panel, 1u, 2u, 3u, 1u, 0x44u);
  check(panel.byte_11 == 1u);
  check(panel.field_20 == 0x44u);
  check(model::count_of(model::Kind::produce) == 0);
  check(model::count_of(model::Kind::consume) == 0);
  check(model::register_count == 3);

  prime();
  entry(&panel, 1u, 2u, 3u, 0x0100u, 0x44u);
  check(panel.byte_11 == 0u);
  check(panel.field_20 == 0u);
  check(model::produce_count == 8);

  prime();
  entry(&panel, 1u, 2u, 3u, 0x0200u, 0x44u);
  check(panel.byte_11 == 0u);
  check(panel.field_20 == 0u);
  check(model::produce_count == 8);

  prime();
  entry(&panel, 1u, 2u, 3u, 0x00ffu, 0x44u);
  check(panel.byte_11 == 0xffu);
  check(panel.field_20 == 0x44u);
  check(model::produce_count == 0);
}

void test_name_panel_allocation_failure() {
  const auto entry = name_panel_entry();
  OpaqueNamePanel panel{};
  prime_panel(&panel);
  reset();
  model::lookup_miss = true;
  model::alloc_fail_next = true;
  entry(&panel, 0x11u, 0x22u, 0x33u, 0u, 0x44u);
  check(panel.slot_18 == nullptr);
  check(model::count_of(model::Kind::service_init) == 0);
  check(model::events[model::index_of(model::Kind::set_property)].self == 0);
  check(panel.field_34 == 0x22u);
  check(panel.byte_11 == 0u);
  check(model::register_count == 3);
  check(panel.slot_14 == nullptr);
  check(model::count_of(model::Kind::bind) == 0);

  reset();
  prime_panel(&panel);
  model::lookup_miss = false;
  model::lookup_results[0xc7ceb1bdu % 16u] =
      model::pointer_word(&model::binder_service);
  model::alloc_fail_next = true;
  entry(&panel, 0x11u, 0x22u, 0x33u, 0u, 0x44u);
  check(panel.slot_14 == nullptr);
  check(model::count_of(model::Kind::bind) == 1);
  check(model::events[model::index_of(model::Kind::bind)].arg0 == 0);
}

}

int run_tests() {
  model::reset();
  test_archive_teardown_order();
  test_archive_base_subobject_thunk();
  test_settings_handle_gates();
  test_settings_fill_loop();
  test_name_panel_fields_and_registers();
  test_name_panel_flag_gates_carrier_copy();
  test_name_panel_allocation_failure();
  return 0;
}

}

int main() { return openspore::reconstruction::pkg_ui_wave10::run_tests(); }
