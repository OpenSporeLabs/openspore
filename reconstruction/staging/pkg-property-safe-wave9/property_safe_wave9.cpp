#include "property_safe_wave9.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_property_safe_wave9 {
namespace {

#if defined(_MSC_VER)
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __thiscall
#else
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __attribute__((thiscall))
#endif

void default_cleanup_port(TargetWord, OpaqueProperty*, TargetWord, TargetWord,
                          TargetWord, TargetWord) {}

void PKG_PROPERTY_SAFE_WAVE9_THISCALL
default_convert_port(OpaqueProperty*, TargetWord, std::uint16_t, const void*,
                     TargetWord, TargetWord) {}

void PKG_PROPERTY_SAFE_WAVE9_THISCALL
default_set_parent_port(OpaquePropertyList*, OpaquePropertyList*) {}

TargetSignedWord signed_map_count(const OpaquePropertyMap& map) {
  const auto begin = reinterpret_cast<std::uintptr_t>(map.begin);
  const auto end = reinterpret_cast<std::uintptr_t>(map.end);
  return static_cast<TargetSignedWord>(end - begin) /
         static_cast<TargetSignedWord>(sizeof(OpaquePropertyEntry));
}

TargetSignedWord signed_word_count(const OpaqueWordVector& vector) {
  const auto begin = reinterpret_cast<std::uintptr_t>(vector.begin);
  const auto end = reinterpret_cast<std::uintptr_t>(vector.end);
  return static_cast<TargetSignedWord>(end - begin) /
         static_cast<TargetSignedWord>(sizeof(TargetWord));
}

TargetSignedWord signed_word_capacity(const OpaqueWordVector& vector) {
  const auto begin = reinterpret_cast<std::uintptr_t>(vector.begin);
  const auto capacity = reinterpret_cast<std::uintptr_t>(vector.capacity);
  return static_cast<TargetSignedWord>(capacity - begin) /
         static_cast<TargetSignedWord>(sizeof(TargetWord));
}

OpaquePropertyEntry* lower_bound_entry(const OpaquePropertyMap& map,
                                       TargetWord property_id) {
  static_cast<void>(map.lookup_mode);
  auto current = map.begin;
  TargetSignedWord count = signed_map_count(map);
  while (count > 0) {
    const TargetSignedWord middle = count >> 1;
    if (current[middle].id < property_id) {
      current += middle + 1;
      count += -1 - middle;
    } else {
      count = middle;
    }
  }
  return current;
}

OpaquePropertyEntry* find_entry(const OpaquePropertyMap& map,
                                TargetWord property_id) {
  OpaquePropertyEntry* const candidate = lower_bound_entry(map, property_id);
  if (candidate == map.end || property_id < candidate->id) {
    return map.end;
  }
  return candidate;
}

OpaquePropertyMap* PKG_PROPERTY_SAFE_WAVE9_THISCALL default_map_copy_port(
    OpaquePropertyMap* destination, const OpaquePropertyMap* source) {
  if (destination == source || destination == nullptr || source == nullptr) {
    return destination;
  }
  const auto source_count = signed_map_count(*source);
  if (source_count <= 0 || destination->begin == nullptr) {
    return destination;
  }
  const auto available =
      static_cast<TargetWord>(destination->capacity - destination->begin);
  const auto wanted = static_cast<TargetWord>(source_count);
  const auto copyable = wanted < available ? wanted : available;
  for (TargetWord index = 0; index < copyable; ++index) {
    destination->begin[index].id = source->begin[index].id;
    std::memcpy(destination->begin[index].property.value.data(),
                source->begin[index].property.value.data(),
                sizeof(destination->begin[index].property.value));
    destination->begin[index].property.type =
        source->begin[index].property.type;
    destination->begin[index].property.flags =
        source->begin[index].property.flags;
  }
  return destination;
}

void PKG_PROPERTY_SAFE_WAVE9_THISCALL
default_resize_words_port(OpaqueWordVector* vector, TargetWord count) {
  if (vector == nullptr) {
    return;
  }
  if (count == 0 && vector->begin == nullptr) {
    vector->end = nullptr;
    return;
  }
  const auto old_count =
      signed_word_count(*vector) > 0
          ? static_cast<TargetWord>(signed_word_count(*vector))
          : 0u;
  if (signed_word_capacity(*vector) < static_cast<TargetSignedWord>(count)) {
    auto* replacement = new TargetWord[count];
    for (TargetWord index = 0; index < old_count; ++index) {
      replacement[index] = vector->begin[index];
    }
    delete[] vector->begin;
    vector->begin = replacement;
    vector->capacity = replacement + count;
  }
  const auto resized_end = vector->begin + count;
  if (resized_end > vector->end && vector->end != nullptr) {
    std::memset(vector->end, 0,
                static_cast<std::size_t>(resized_end - vector->end) *
                    sizeof(TargetWord));
  }
  vector->end = resized_end;
}

bool PKG_PROPERTY_SAFE_WAVE9_THISCALL default_get_property_alt_base_port(
    OpaquePropertyList* list, TargetWord property_id, OpaqueProperty** result) {
  OpaquePropertyEntry* const entry = find_entry(list->properties, property_id);
  if (entry != list->properties.end) {
    *result = &entry->property;
    return true;
  }
  if (list->parent != nullptr) {
    return list->parent->vtable->get_property_alt_20(list->parent, property_id,
                                                     result);
  }
  return false;
}

#undef PKG_PROPERTY_SAFE_WAVE9_THISCALL

}

PropertySafePorts& property_safe_ports() {
  static PropertySafePorts ports{
      default_cleanup_port,      default_convert_port,
      default_map_copy_port,     default_set_parent_port,
      default_resize_words_port, default_get_property_alt_base_port};
  return ports;
}

void property_safe_set_ports(const PropertySafePorts& ports) {
  property_safe_ports() = ports;
}

void property_safe_reset_ports() {
  property_safe_ports() = PropertySafePorts{
      default_cleanup_port,      default_convert_port,
      default_map_copy_port,     default_set_parent_port,
      default_resize_words_port, default_get_property_alt_base_port};
}

#if defined(_MSC_VER)
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __thiscall
#else
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __attribute__((thiscall))
#endif

void PKG_PROPERTY_SAFE_WAVE9_THISCALL
direct_property_list_add_properties_from_006a1600(OpaquePropertyList* list,
                                                  OpaquePropertyList* other) {
  if (list == other) {
    return;
  }
  OpaquePropertyEntry* entry = other->properties.begin;
  while (entry != other->properties.end) {
    list->vtable->set_property_14(list, entry->id, &entry->property);
    entry += 1;
  }
  ++list->operations_done;
}

bool PKG_PROPERTY_SAFE_WAVE9_THISCALL
direct_property_list_get_property_alt_006a1e50(OpaquePropertyList* list,
                                               TargetWord property_id,
                                               OpaqueProperty** result) {
  if (property_id < list->fast_count) {
    *result = list->vtable->get_property_object_28(list, property_id);
    return true;
  }
  return property_safe_ports().get_property_alt_base(list, property_id, result);
}

void PKG_PROPERTY_SAFE_WAVE9_THISCALL property_list_copy_from_006a2a40(
    OpaquePropertyList* list, OpaquePropertyList* other) {
  if (list == other) {
    return;
  }
  property_safe_ports().map_copy(&list->properties, &other->properties);
  list->properties.lookup_mode = other->properties.lookup_mode;
  property_safe_ports().set_parent(list, list->parent);
}

void PKG_PROPERTY_SAFE_WAVE9_THISCALL property_list_get_property_ids_006a3070(
    OpaquePropertyList* list, OpaqueWordVector* destination) {
  const auto count = signed_map_count(list->properties);
  property_safe_ports().resize_words(destination,
                                     static_cast<TargetWord>(count));
  OpaquePropertyEntry* entry = list->properties.begin;
  TargetWord* slot = destination->begin;
  while (entry != list->properties.end) {
    *slot = entry->id;
    ++entry;
    ++slot;
  }
}

#undef PKG_PROPERTY_SAFE_WAVE9_THISCALL

}
