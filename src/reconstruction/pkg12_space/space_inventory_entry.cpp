#include "space_inventory_entry.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg12_space {

namespace {

bool has_owned_prefix(const void* pointer) {
  if (pointer == nullptr) {
    return false;
  }
  std::uint32_t prefix = 0;
  const auto* bytes = static_cast<const std::uint8_t*>(pointer);
  std::memcpy(&prefix, bytes - 4, sizeof(prefix));
  return prefix != 0;
}

std::size_t descriptor_count(const GameEntryRange& range) {
  if (range.begin == nullptr || range.end == nullptr) {
    return 0;
  }
  const auto begin = reinterpret_cast<std::uintptr_t>(range.begin);
  const auto end = reinterpret_cast<std::uintptr_t>(range.end);
  if (end < begin) {
    return 0;
  }
  return static_cast<std::size_t>(end - begin) / sizeof(GameEntryDescriptor);
}

}

void cSpaceInventoryItem_ctor_00c877f0(InventoryItem* item,
                                       OpaquePropertyList* property_list,
                                       const InventoryItemServices& services) {
  OpaquePropertyList* old_property_list = item->property_list;
  if (property_list != old_property_list) {
    if (property_list != nullptr) {
      property_list->vtable->add_ref(property_list);
    }
    item->property_list = property_list;
    if (old_property_list != nullptr) {
      old_property_list->vtable->release(old_property_list);
    }
  }

  if (property_list == nullptr) {
    return;
  }

  services.get_text(property_list, 0x3068d95dU, &item->description);
  services.get_text(property_list, 0x04cad19bU, &item->detail_description);
  OpaqueProperty* property = nullptr;
  if (property_list->vtable->get_property(property_list, 0x1bfc1deeU,
                                          &property) &&
      property->type == 10) {
    item->item_cost = services.read_value(property);
  }
  item->vtable->notify(item);
}

void pkg12_space_00de9fc0(InventoryEntryContext& context,
                          InventoryEntryServices& services) {
  constexpr struct {
    std::uint32_t key;
    std::uint32_t value;
  } records[] = {
      {0x2dd90afU, 0x366a930dU},
      {0x3cc89b1U, 0x913b23beU},
      {0x54a32960U, 1U},
  };

  PropertyRecord record{};
  PropertyRecordBuffer buffer;
  for (const auto& spec : records) {
    services.property_records.initialize(&services.property_records, &record,
                                         spec.key, spec.value);
    services.property_records.append(&services.property_records, &buffer,
                                     &record);
    services.property_records.cleanup(&services.property_records, buffer.begin,
                                      buffer.end);
    if (has_owned_prefix(buffer.begin)) {
      services.allocation.free(&services.allocation, buffer.begin);
    }
  }

  GameEntryRange range;
  services.galaxy_entries.get_entries(&services.galaxy_entries, &range);
  const std::size_t count = descriptor_count(range);
  for (std::size_t index = 0; index < count; ++index) {
    const GameEntryDescriptor entry = range.begin[index];
    const GameEntryDescriptor* candidate =
        context.index.lower_bound(&context.index, &entry);
    if (candidate == context.index.anchor) {
      services.game_modes.initialize_entry(&services.game_modes, &entry);
    }
  }

  services.behavior.cleanup(&services.behavior);
  if (has_owned_prefix(range.begin)) {
    services.allocation.free(&services.allocation,
                             const_cast<GameEntryDescriptor*>(range.begin));
  }
  services.property_records.cleanup(&services.property_records,
                                    range.records_begin, range.records_end);
  if (has_owned_prefix(range.records_begin)) {
    services.allocation.free(&services.allocation, range.records_begin);
  }
}

}
