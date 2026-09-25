#include <cassert>
#include <cstdint>
#include <cstring>
#include <vector>

#include "space_inventory_entry.hpp"

namespace {

using openspore::reconstruction::pkg12_space::AllocationService;
using openspore::reconstruction::pkg12_space::BehaviorCleanupService;
using openspore::reconstruction::pkg12_space::cSpaceInventoryItem_ctor_00c877f0;
using openspore::reconstruction::pkg12_space::EntryIndex;
using openspore::reconstruction::pkg12_space::GalaxyGameEntryService;
using openspore::reconstruction::pkg12_space::GameEntryDescriptor;
using openspore::reconstruction::pkg12_space::GameEntryRange;
using openspore::reconstruction::pkg12_space::GameModeService;
using openspore::reconstruction::pkg12_space::InventoryEntryContext;
using openspore::reconstruction::pkg12_space::InventoryEntryServices;
using openspore::reconstruction::pkg12_space::InventoryItem;
using openspore::reconstruction::pkg12_space::InventoryItemServices;
using openspore::reconstruction::pkg12_space::InventoryItemVtable;
using openspore::reconstruction::pkg12_space::OpaqueLocalizedString;
using openspore::reconstruction::pkg12_space::OpaqueProperty;
using openspore::reconstruction::pkg12_space::OpaquePropertyList;
using openspore::reconstruction::pkg12_space::pkg12_space_00de9fc0;
using openspore::reconstruction::pkg12_space::PropertyListVtable;
using openspore::reconstruction::pkg12_space::PropertyRecord;
using openspore::reconstruction::pkg12_space::PropertyRecordBuffer;
using openspore::reconstruction::pkg12_space::PropertyRecordService;

enum class EventKind : std::uint8_t {
  add_ref,
  release,
  get_text,
  get_property,
  read_value,
  notify,
  record_init,
  append,
  record_cleanup,
  free,
  entries,
  mode_init,
  behavior_cleanup,
};

struct Event {
  EventKind kind;
  std::uintptr_t first = 0;
  std::uintptr_t second = 0;
};

struct RecordStorage {
  std::uint32_t prefix;
  PropertyRecord record;
};

std::vector<Event> events;
std::uint32_t text_value = 0xa1a1a1a1U;
std::uint32_t detail_value = 0xb2b2b2b2U;
std::uint32_t property_value = 0x12345678U;
bool property_found = true;
std::uint16_t property_type = 10;
PropertyRecordBuffer scratch_buffer;
RecordStorage scratch_storage{};
GameEntryRange supplied_range;
const GameEntryDescriptor* search_result = nullptr;
const GameEntryDescriptor* mode_entry = nullptr;

Event make_event(EventKind kind, std::uintptr_t first = 0,
                 std::uintptr_t second = 0) {
  return Event{kind, first, second};
}

void clear_events() { events.clear(); }

void __thiscall add_ref(OpaquePropertyList* list) {
  events.push_back(
      make_event(EventKind::add_ref, reinterpret_cast<std::uintptr_t>(list)));
}

void __thiscall release(OpaquePropertyList* list) {
  events.push_back(
      make_event(EventKind::release, reinterpret_cast<std::uintptr_t>(list)));
}

bool __thiscall get_property(OpaquePropertyList* list, std::uint32_t key,
                             OpaqueProperty** result) {
  events.push_back(make_event(EventKind::get_property,
                              reinterpret_cast<std::uintptr_t>(list), key));
  if (key == 0x1bfc1deeU && property_found) {
    static OpaqueProperty property{};
    property.first = property_value;
    property.flags = 0;
    property.type = property_type;
    *result = &property;
    return true;
  }
  *result = nullptr;
  return false;
}

bool get_text(OpaquePropertyList* list, std::uint32_t key,
              OpaqueLocalizedString* destination) {
  events.push_back(make_event(EventKind::get_text,
                              reinterpret_cast<std::uintptr_t>(list), key));
  const std::uint32_t value = key == 0x3068d95dU ? text_value : detail_value;
  for (std::size_t index = 0; index < sizeof(destination->bytes); ++index) {
    destination->bytes[index] =
        static_cast<std::uint8_t>(value >> ((index % 4) * 8));
  }
  return true;
}

std::uint32_t read_value(const OpaqueProperty* property) {
  events.push_back(make_event(EventKind::read_value,
                              reinterpret_cast<std::uintptr_t>(property)));
  return property->first;
}

void __thiscall notify(InventoryItem* item) {
  events.push_back(
      make_event(EventKind::notify, reinterpret_cast<std::uintptr_t>(item)));
}

void initialize_record(PropertyRecordService*, PropertyRecord* record,
                       std::uint32_t key, std::uint32_t value) {
  record->key = key;
  record->tag = 0x2e1a75dU;
  record->value = value;
  record->value_end = value + 1U;
  record->opaque[0] = 0;
  record->opaque[1] = 0;
  record->opaque[2] = 0;
  record->opaque[3] = 0;
  record->opaque[4] = 0;
  events.push_back(make_event(EventKind::record_init, key, value));
}

void append_record(PropertyRecordService*, PropertyRecordBuffer* buffer,
                   const PropertyRecord* record) {
  if (buffer->begin == nullptr) {
    scratch_storage.prefix = 1;
    buffer->begin = &scratch_storage.record;
  }
  *buffer->begin = *record;
  buffer->end = buffer->begin + 1;
  buffer->capacity = buffer->end;
  events.push_back(
      make_event(EventKind::append, reinterpret_cast<std::uintptr_t>(record)));
}

void cleanup_records(PropertyRecordService*, PropertyRecord* begin,
                     PropertyRecord* end) {
  events.push_back(make_event(EventKind::record_cleanup,
                              reinterpret_cast<std::uintptr_t>(begin),
                              reinterpret_cast<std::uintptr_t>(end)));
}

void free_memory(AllocationService*, void* pointer) {
  events.push_back(
      make_event(EventKind::free, reinterpret_cast<std::uintptr_t>(pointer)));
  if (pointer == &scratch_storage.record) {
    scratch_buffer.begin = nullptr;
    scratch_buffer.end = nullptr;
    scratch_buffer.capacity = nullptr;
  }
}

void get_entries(GalaxyGameEntryService*, GameEntryRange* range) {
  *range = supplied_range;
  events.push_back(make_event(EventKind::entries));
}

const GameEntryDescriptor* lower_bound(const EntryIndex*,
                                       const GameEntryDescriptor* entry) {
  assert(search_result != nullptr);
  (void)entry;
  return search_result;
}

void initialize_mode(GameModeService*, const GameEntryDescriptor* entry) {
  mode_entry = entry;
  events.push_back(make_event(EventKind::mode_init,
                              reinterpret_cast<std::uintptr_t>(entry),
                              entry->word1));
}

void cleanup_behavior(BehaviorCleanupService*) {
  events.push_back(make_event(EventKind::behavior_cleanup));
}

PropertyListVtable make_property_vtable() {
  PropertyListVtable vtable{};
  vtable.add_ref = add_ref;
  vtable.release = release;
  vtable.get_property = get_property;
  return vtable;
}

InventoryItemServices make_item_services() {
  return InventoryItemServices{get_text, read_value};
}

PropertyRecordService make_record_service() {
  return PropertyRecordService{initialize_record, append_record,
                               cleanup_records};
}

InventoryEntryServices make_entry_services() {
  InventoryEntryServices services{};
  services.property_records = make_record_service();
  services.galaxy_entries = GalaxyGameEntryService{get_entries};
  services.game_modes = GameModeService{initialize_mode};
  services.behavior = BehaviorCleanupService{cleanup_behavior};
  services.allocation = AllocationService{free_memory};
  return services;
}

void test_property_application_and_ref_order() {
  clear_events();
  property_found = true;
  property_type = 10;
  text_value = 0xa1a1a1a1U;
  detail_value = 0xb2b2b2b2U;
  property_value = 0x12345678U;
  PropertyListVtable vtable = make_property_vtable();
  OpaquePropertyList old_list{&vtable};
  OpaquePropertyList new_list{&vtable};
  InventoryItemVtable item_vtable{};
  item_vtable.notify = notify;
  InventoryItem item{};
  item.vtable = &item_vtable;
  item.property_list = &old_list;
  const InventoryItemServices services = make_item_services();

  cSpaceInventoryItem_ctor_00c877f0(&item, &new_list, services);

  assert(item.property_list == &new_list);
  assert(item.item_cost == property_value);
  assert(events.size() == 7);
  assert(events[0].kind == EventKind::add_ref);
  assert(events[0].first == reinterpret_cast<std::uintptr_t>(&new_list));
  assert(events[1].kind == EventKind::release);
  assert(events[1].first == reinterpret_cast<std::uintptr_t>(&old_list));
  assert(events[2].kind == EventKind::get_text);
  assert(events[2].second == 0x3068d95dU);
  assert(events[3].kind == EventKind::get_text);
  assert(events[3].second == 0x04cad19bU);
  assert(events[4].kind == EventKind::get_property);
  assert(events[4].second == 0x1bfc1deeU);
  assert(events[5].kind == EventKind::read_value);
  assert(events[6].kind == EventKind::notify);
  for (std::size_t index = 0; index < sizeof(item.description.bytes); ++index) {
    assert(item.description.bytes[index] ==
           static_cast<std::uint8_t>(text_value >> ((index % 4) * 8)));
    assert(item.detail_description.bytes[index] ==
           static_cast<std::uint8_t>(detail_value >> ((index % 4) * 8)));
  }
}

void test_property_same_pointer_and_null_paths() {
  clear_events();
  property_found = false;
  PropertyListVtable vtable = make_property_vtable();
  OpaquePropertyList list{&vtable};
  InventoryItemVtable item_vtable{};
  item_vtable.notify = notify;
  InventoryItem item{};
  item.vtable = &item_vtable;
  item.property_list = &list;
  const InventoryItemServices services = make_item_services();

  cSpaceInventoryItem_ctor_00c877f0(&item, &list, services);
  assert(events.size() == 4);
  assert(events[0].kind == EventKind::get_text);
  assert(events[1].kind == EventKind::get_text);
  assert(events[2].kind == EventKind::get_property);
  assert(events[3].kind == EventKind::notify);

  clear_events();
  cSpaceInventoryItem_ctor_00c877f0(&item, nullptr, services);
  assert(item.property_list == nullptr);
  assert(events.size() == 1);
  assert(events[0].kind == EventKind::release);
  assert(events[0].first == reinterpret_cast<std::uintptr_t>(&list));
}

void test_property_type_filter() {
  clear_events();
  property_found = false;
  PropertyListVtable vtable = make_property_vtable();
  OpaquePropertyList list{&vtable};
  InventoryItemVtable item_vtable{};
  item_vtable.notify = notify;
  InventoryItem item{};
  item.vtable = &item_vtable;
  item.item_cost = 77U;
  const InventoryItemServices services = make_item_services();

  cSpaceInventoryItem_ctor_00c877f0(&item, &list, services);
  assert(item.item_cost == 77U);
  assert(events.size() == 5);
  assert(events[0].kind == EventKind::add_ref);
  assert(events[1].kind == EventKind::get_text);
  assert(events[2].kind == EventKind::get_text);
  assert(events[3].kind == EventKind::get_property);
  assert(events[4].kind == EventKind::notify);

  clear_events();
  property_found = true;
  property_type = 9;
  cSpaceInventoryItem_ctor_00c877f0(&item, &list, services);
  assert(item.item_cost == 77U);
  assert(events.size() == 4);
  assert(events[2].kind == EventKind::get_property);
  assert(events[3].kind == EventKind::notify);
}

void test_entry_initialization_and_cleanup_order() {
  clear_events();
  scratch_buffer = PropertyRecordBuffer{};
  supplied_range = GameEntryRange{};
  struct EntryBlock {
    std::uint32_t prefix;
    GameEntryDescriptor entries[2];
  } entry_block{};
  struct RecordBlock {
    std::uint32_t prefix;
    PropertyRecord record;
  } record_block{};
  entry_block.prefix = 1;
  record_block.prefix = 1;
  entry_block.entries[0] = GameEntryDescriptor{11U, 22U, 33U};
  entry_block.entries[1] = GameEntryDescriptor{44U, 55U, 66U};
  supplied_range.begin = &entry_block.entries[0];
  supplied_range.end = &entry_block.entries[2];
  supplied_range.records_begin = &record_block.record;
  supplied_range.records_end = &record_block.record + 1;
  const GameEntryDescriptor anchor{99U, 99U, 99U};
  search_result = &anchor;
  mode_entry = nullptr;
  InventoryEntryContext context{};
  context.index.anchor = &anchor;
  context.index.lower_bound = lower_bound;
  InventoryEntryServices services = make_entry_services();

  pkg12_space_00de9fc0(context, services);

  assert(events.size() == 19);
  assert(events[0].kind == EventKind::record_init);
  assert(events[0].first == 0x2dd90afU);
  assert(events[0].second == 0x366a930dU);
  assert(events[1].kind == EventKind::append);
  assert(events[2].kind == EventKind::record_cleanup);
  assert(events[3].kind == EventKind::free);
  assert(events[4].kind == EventKind::record_init);
  assert(events[4].first == 0x3cc89b1U);
  assert(events[4].second == 0x913b23beU);
  assert(events[5].kind == EventKind::append);
  assert(events[6].kind == EventKind::record_cleanup);
  assert(events[7].kind == EventKind::free);
  assert(events[8].kind == EventKind::record_init);
  assert(events[8].first == 0x54a32960U);
  assert(events[8].second == 1U);
  assert(events[9].kind == EventKind::append);
  assert(events[10].kind == EventKind::record_cleanup);
  assert(events[11].kind == EventKind::free);
  assert(events[12].kind == EventKind::entries);
  assert(events[13].kind == EventKind::mode_init);
  assert(events[14].kind == EventKind::mode_init);
  assert(events[15].kind == EventKind::behavior_cleanup);
  assert(events[16].kind == EventKind::free);
  assert(events[17].kind == EventKind::record_cleanup);
  assert(events[18].kind == EventKind::free);
  assert(mode_entry != nullptr);
  assert(scratch_storage.record.key == 0x54a32960U);
  assert(scratch_storage.record.value == 1U);

  clear_events();
  search_result = reinterpret_cast<const GameEntryDescriptor*>(0x2000U);
  mode_entry = nullptr;
  assert(search_result != context.index.anchor);
  pkg12_space_00de9fc0(context, services);
  assert(mode_entry == nullptr);
  assert(events.size() == 17);
  assert(events[12].kind == EventKind::entries);
  assert(events[13].kind == EventKind::behavior_cleanup);
  assert(events[14].kind == EventKind::free);
  assert(events[15].kind == EventKind::record_cleanup);
  assert(events[16].kind == EventKind::free);
}

void test_empty_and_invalid_ranges_cleanup() {
  clear_events();
  supplied_range = GameEntryRange{};
  const GameEntryDescriptor anchor{};
  search_result = &anchor;
  InventoryEntryContext context{};
  context.index.anchor = &anchor;
  context.index.lower_bound = lower_bound;
  InventoryEntryServices services = make_entry_services();

  pkg12_space_00de9fc0(context, services);
  assert(events.size() == 15);
  assert(events[0].kind == EventKind::record_init);
  assert(events[1].kind == EventKind::append);
  assert(events[2].kind == EventKind::record_cleanup);
  assert(events[3].kind == EventKind::free);
  assert(events[12].kind == EventKind::entries);
  assert(events[13].kind == EventKind::behavior_cleanup);
  assert(events[14].kind == EventKind::record_cleanup);

  clear_events();
  supplied_range.begin = nullptr;
  supplied_range.end = nullptr;
  pkg12_space_00de9fc0(context, services);
  assert(events.size() == 15);
  assert(events[12].kind == EventKind::entries);
  assert(events[13].kind == EventKind::behavior_cleanup);
  assert(events[14].kind == EventKind::record_cleanup);
}

}

int main() {
  test_property_application_and_ref_order();
  test_property_same_pointer_and_null_paths();
  test_property_type_filter();
  test_entry_initialization_and_cleanup_order();
  test_empty_and_invalid_ranges_cleanup();
}
