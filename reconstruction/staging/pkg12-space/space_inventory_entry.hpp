#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-12 inventory staging requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-12 target pointers are 32-bit");
static_assert(sizeof(std::int32_t) == 4, "PKG-12 target words are 32-bit");

namespace openspore::reconstruction::pkg12_space {

struct OpaquePropertyList;

using PropertyListAddRef = void(__thiscall*)(OpaquePropertyList*);
using PropertyListRelease = void(__thiscall*)(OpaquePropertyList*);
using PropertyListGetProperty = bool(__thiscall*)(OpaquePropertyList*,
                                                  std::uint32_t,
                                                  struct OpaqueProperty**);

struct OpaqueProperty {
  std::uint32_t first;
  std::uint8_t middle[0x0c];
  std::uint16_t flags;
  std::uint16_t type;
};

static_assert(offsetof(OpaqueProperty, flags) == 0x10,
              "property flags are at target offset 0x10");
static_assert(offsetof(OpaqueProperty, type) == 0x12,
              "property type is at target offset 0x12");

struct OpaqueLocalizedString {
  std::uint8_t bytes[20];
};

struct PropertyListVtable {
  PropertyListAddRef add_ref;
  PropertyListRelease release;
  void* slots[7];
  PropertyListGetProperty get_property;
};

static_assert(offsetof(PropertyListVtable, get_property) == 0x24,
              "PropertyList GetProperty is at vtable offset 0x24");

struct OpaquePropertyList {
  PropertyListVtable* vtable;
};

using InventoryItemNotify = void(__thiscall*)(struct InventoryItem*);

struct InventoryItemVtable {
  void* slots[19];
  InventoryItemNotify notify;
};

static_assert(offsetof(InventoryItemVtable, notify) == 0x4c,
              "inventory item notification is at vtable offset 0x4c");

struct InventoryItem {
  InventoryItemVtable* vtable;
  std::uint8_t prefix[0x20];
  std::uint32_t item_cost;
  std::uint8_t middle[0x08];
  OpaquePropertyList* property_list;
  OpaqueLocalizedString description;
  OpaqueLocalizedString detail_description;
};

static_assert(offsetof(InventoryItem, item_cost) == 0x24,
              "inventory item cost is at target offset 0x24");
static_assert(offsetof(InventoryItem, property_list) == 0x30,
              "inventory item property list is at target offset 0x30");
static_assert(offsetof(InventoryItem, description) == 0x34,
              "inventory item description is at target offset 0x34");
static_assert(offsetof(InventoryItem, detail_description) == 0x48,
              "inventory detail description is at target offset 0x48");

struct InventoryItemServices {
  using GetText = bool (*)(OpaquePropertyList*, std::uint32_t,
                           OpaqueLocalizedString*);
  using ReadValue = std::uint32_t (*)(const OpaqueProperty*);
  GetText get_text = nullptr;
  ReadValue read_value = nullptr;
};

void cSpaceInventoryItem_ctor_00c877f0(InventoryItem* item,
                                       OpaquePropertyList* property_list,
                                       const InventoryItemServices& services);

struct PropertyRecord {
  std::uint32_t key;
  std::uint32_t tag;
  std::uint32_t value;
  std::uint32_t value_end;
  std::uint32_t opaque[5];
};

static_assert(sizeof(PropertyRecord) == 0x24,
              "property records occupy one 0x24-byte target record");

struct PropertyRecordBuffer {
  PropertyRecord* begin = nullptr;
  PropertyRecord* end = nullptr;
  PropertyRecord* capacity = nullptr;
};

struct PropertyRecordService {
  using Initialize = void (*)(PropertyRecordService*, PropertyRecord*,
                              std::uint32_t, std::uint32_t);
  using Append = void (*)(PropertyRecordService*, PropertyRecordBuffer*,
                          const PropertyRecord*);
  using Cleanup = void (*)(PropertyRecordService*, PropertyRecord*,
                           PropertyRecord*);
  Initialize initialize = nullptr;
  Append append = nullptr;
  Cleanup cleanup = nullptr;
};

struct GameEntryDescriptor {
  std::uint32_t word0;
  std::uint32_t word1;
  std::uint32_t word2;
};

static_assert(sizeof(GameEntryDescriptor) == 0x0c,
              "game-entry descriptors occupy one 0x0c-byte target record");

struct GameEntryRange {
  const GameEntryDescriptor* begin = nullptr;
  const GameEntryDescriptor* end = nullptr;
  PropertyRecord* records_begin = nullptr;
  PropertyRecord* records_end = nullptr;
};

struct GalaxyGameEntryService {
  using GetEntries = void (*)(GalaxyGameEntryService*, GameEntryRange*);
  GetEntries get_entries = nullptr;
};

struct EntryIndex {
  using LowerBound = const GameEntryDescriptor* (*)(const EntryIndex*,
                                                    const GameEntryDescriptor*);
  const GameEntryDescriptor* anchor = nullptr;
  LowerBound lower_bound = nullptr;
};

struct GameModeService {
  using InitializeEntry = void (*)(GameModeService*,
                                   const GameEntryDescriptor*);
  InitializeEntry initialize_entry = nullptr;
};

struct BehaviorCleanupService {
  using Cleanup = void (*)(BehaviorCleanupService*);
  Cleanup cleanup = nullptr;
};

struct AllocationService {
  using Free = void (*)(AllocationService*, void*);
  Free free = nullptr;
};

struct InventoryEntryContext {
  EntryIndex index;
};

struct InventoryEntryServices {
  PropertyRecordService property_records;
  GalaxyGameEntryService galaxy_entries;
  GameModeService game_modes;
  BehaviorCleanupService behavior;
  AllocationService allocation;
};

void pkg12_space_00de9fc0(InventoryEntryContext& context,
                          InventoryEntryServices& services);

}
