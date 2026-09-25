#include "direct_property_list.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg20_property_adapter {

using OpaqueCleanupPort = void (*)(TargetWord, Property*, TargetWord,
                                   TargetWord, TargetWord, TargetWord);

namespace {

void default_opaque_cleanup(TargetWord, Property*, TargetWord, TargetWord,
                            TargetWord, TargetWord) {}

OpaqueCleanupPort opaque_cleanup_port = default_opaque_cleanup;

void materialize_fallback(Property& destination, const Property& source) {
  std::memcpy(destination.opaque_prefix.data(), source.opaque_prefix.data(),
              destination.opaque_prefix.size());
  destination.flags = source.flags;
  destination.opaque_0x11 = source.opaque_0x11;
  destination.type = source.type;
}

void materialize_property(Property& destination, const Property& source) {
  destination.flags = 2;
  destination.opaque_0x11 = 0;
  destination.type = 1;
  if ((source.flags & 0x08) != 0 ||
      ((destination.flags & 0x02) != 0 && destination.type != source.type)) {
    materialize_fallback(destination, source);
    return;
  }
  std::memcpy(destination.opaque_prefix.data(), source.opaque_prefix.data(),
              destination.opaque_prefix.size());
  destination.opaque_0x11 = source.opaque_0x11;
  destination.type = source.type;
  destination.flags = static_cast<std::uint8_t>((source.flags & ~0x02u) |
                                                (destination.flags & 0x02u));
}

void cleanup_property(Property& property, TargetWord argument) {
  if ((property.flags & 0x04u) != 0) {
    opaque_cleanup_port(1, &property, 0, 0, 0, 0);
  }
  if (argument != 0 && (property.flags & 0x02u) == 0) {
    property.type = 0;
    property.opaque_0x11 = 0;
    property.flags = 0;
  }
}

PropertyMapEntry* lower_bound_entries(const PropertyMap& map,
                                      TargetWord property_id,
                                      std::uint8_t lookup_mode) {
  (void)lookup_mode;
  PropertyMapEntry* current = map.entries_begin;
  PropertyMapEntry* const end = map.entries_end;
  while (current != end) {
    if (current->key < property_id) {
      ++current;
    } else {
      break;
    }
  }
  return current;
}

TargetWord load_value_word(const Property& property) {
  TargetWord value = 0;
  std::memcpy(&value, property.opaque_prefix.data(), sizeof(value));
  return value;
}

bool normalize_property(const Property& property) {
  if (property.type != 1 && property.type != 0x10) {
    return false;
  }
  if ((property.flags & 0x30u) != 0) {
    const auto* value = reinterpret_cast<const std::uint8_t*>(
        static_cast<std::uintptr_t>(load_value_word(property)));
    return *value != 0;
  }
  return property.opaque_prefix[0] != 0;
}

}

PropertyAdapterServices& property_adapter_services() {
  static PropertyAdapterServices services{materialize_property,
                                          cleanup_property};
  return services;
}

void set_opaque_cleanup_port(OpaqueCleanupPort port) {
  opaque_cleanup_port = port == nullptr ? default_opaque_cleanup : port;
}

#if defined(_MSC_VER)
#define PKG20_PROPERTY_THISCALL __thiscall
#else
#define PKG20_PROPERTY_THISCALL __attribute__((thiscall))
#endif

bool PKG20_PROPERTY_THISCALL app_direct_property_list_get_direct_bool_006a25a0(
    DirectPropertyList* list, TargetWord property_id) {
  if (property_id < list->fast_access_count) {
    return list->values[property_id] != 0;
  }

  PropertyMapEntry* entry = lower_bound_entries(list->properties, property_id,
                                                list->properties.lookup_mode);
  if (entry == list->properties.entries_end || property_id < entry->key) {
    return false;
  }

  Property temporary_property{};
  auto& services = property_adapter_services();
  services.materialize(temporary_property, entry->property);
  const bool result = normalize_property(temporary_property);
  if ((temporary_property.flags & 0x04u) != 0) {
    services.cleanup(temporary_property, 0);
  }
  return result;
}

#undef PKG20_PROPERTY_THISCALL

}
