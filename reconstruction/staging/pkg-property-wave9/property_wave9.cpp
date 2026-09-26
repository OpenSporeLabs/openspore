#include "property_wave9.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_property_wave9 {
namespace {

#if defined(_MSC_VER)
#define PKG_PROPERTY_WAVE9_THISCALL __thiscall
#else
#define PKG_PROPERTY_WAVE9_THISCALL __attribute__((thiscall))
#endif

void PKG_PROPERTY_WAVE9_THISCALL default_conversion(OpaqueProperty*, TargetWord,
                                                    std::uint16_t, const void*,
                                                    TargetWord, TargetWord) {}

void default_error_port(TargetWord, OpaqueProperty*, TargetWord, TargetWord,
                        TargetWord, TargetWord) {}

void cleanup_property(OpaqueProperty& property, TargetWord argument) {
  if ((property.flags & 0x0004u) != 0) {
    property_list_runtime().error(1u, &property, 0u, 0u, 0u, 0u);
  }
  if (argument != 0 && (property.flags & 0x0002u) == 0) {
    property.type = 0;
    property.flags = 0;
  }
}

void assign_property(OpaqueProperty& destination,
                     const OpaqueProperty& source) {
  if ((destination.flags & 0x0004u) != 0) {
    cleanup_property(destination, 1u);
  }
  if ((source.flags & 0x0008u) == 0 &&
      ((destination.flags & 0x0002u) == 0 || destination.type == source.type)) {
    std::memcpy(destination.value.data(), source.value.data(),
                destination.value.size());
    destination.type = source.type;
    destination.flags = static_cast<std::uint16_t>(
        (source.flags & 0xfffdu) | (destination.flags & 0x0002u));
    return;
  }
  if ((source.flags & 0x0030u) == 0) {
    property_list_runtime().conversion(&destination, source.type, source.flags,
                                       &source, 0x10u, 1u);
    return;
  }
  TargetWord pointer_word = 0;
  TargetWord size_word = 0;
  TargetWord count_word = 0;
  std::memcpy(&pointer_word, source.value.data(), sizeof(pointer_word));
  std::memcpy(&size_word, source.value.data() + sizeof(TargetWord),
              sizeof(size_word));
  std::memcpy(&count_word, source.value.data() + sizeof(TargetWord) * 2u,
              sizeof(count_word));
  property_list_runtime().conversion(
      &destination, source.type, source.flags,
      reinterpret_cast<const void*>(static_cast<std::uintptr_t>(pointer_word)),
      size_word, count_word);
}

TargetSignedWord signed_map_count(const OpaquePropertyMap& map) {
  const auto begin = reinterpret_cast<std::uintptr_t>(map.begin);
  const auto end = reinterpret_cast<std::uintptr_t>(map.end);
  return static_cast<TargetSignedWord>(end - begin) /
         static_cast<TargetSignedWord>(sizeof(OpaquePropertyEntry));
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

void destroy_entries(OpaquePropertyEntry* begin, OpaquePropertyEntry* end) {
  while (begin != end) {
    if ((begin->property.flags & 0x0004u) != 0) {
      cleanup_property(begin->property, 0u);
    }
    ++begin;
  }
}

void ensure_map_capacity(OpaquePropertyMap& map, TargetWord capacity) {
  if (capacity <=
      static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(map.capacity) -
                              reinterpret_cast<std::uintptr_t>(map.begin)) /
          sizeof(OpaquePropertyEntry)) {
    return;
  }
  const auto old_count = signed_map_count(map) > 0
                             ? static_cast<std::size_t>(signed_map_count(map))
                             : 0u;
  auto* replacement = new OpaquePropertyEntry[capacity];
  for (std::size_t index = 0; index < old_count; ++index) {
    replacement[index].id = map.begin[index].id;
    assign_property(replacement[index].property, map.begin[index].property);
  }
  destroy_entries(map.begin, map.end);
  delete[] map.begin;
  map.begin = replacement;
  map.end = replacement + old_count;
  map.capacity = replacement + capacity;
}

void resize_map(OpaquePropertyMap& map, TargetWord count) {
  if (count == 0 && map.begin == nullptr) {
    map.end = nullptr;
    return;
  }
  ensure_map_capacity(map, count);
  auto* const resized_end = map.begin + count;
  if (resized_end < map.end) {
    destroy_entries(resized_end, map.end);
  } else if (resized_end > map.end && map.end != nullptr) {
    std::memset(map.end, 0,
                static_cast<std::size_t>(resized_end - map.end) *
                    sizeof(OpaquePropertyEntry));
  }
  map.end = resized_end;
}

OpaquePropertyEntry* insert_entry(OpaquePropertyMap& map,
                                  TargetWord property_id,
                                  const OpaqueProperty& property) {
  OpaquePropertyEntry* position = lower_bound_entry(map, property_id);
  if (map.end != map.begin && map.end != map.capacity) {
    if (map.end != nullptr) {
      map.end->id = map.end[-1].id;
      map.end->property = OpaqueProperty{};
      assign_property(map.end->property, map.end[-1].property);
    }
    for (OpaquePropertyEntry* source = map.end - 1; source >= position;
         --source) {
      source[1].id = source->id;
      assign_property(source[1].property, source->property);
    }
    position->id = property_id;
    assign_property(position->property, property);
    ++map.end;
    return position;
  }
  if (map.end == map.capacity) {
    const auto count = signed_map_count(map);
    const auto growth =
        count > 0 ? static_cast<TargetWord>(count * 2) : TargetWord{1};
    const auto position_index = static_cast<std::size_t>(position - map.begin);
    ensure_map_capacity(map, growth);
    position = map.begin + position_index;
  }
  if (map.end != nullptr) {
    map.end->id = property_id;
    map.end->property = OpaqueProperty{};
    assign_property(map.end->property, property);
  }
  ++map.end;
  return map.end - 1;
}

OpaquePropertyEntry* obtain_property_entry(OpaquePropertyMap& map,
                                           TargetWord property_id) {
  OpaquePropertyEntry* const existing = find_entry(map, property_id);
  if (existing != map.end) {
    return existing;
  }
  OpaqueProperty property{};
  return insert_entry(map, property_id, property);
}

OpaquePropertyMap* PKG_PROPERTY_WAVE9_THISCALL default_map_copy(
    OpaquePropertyMap* destination, const OpaquePropertyMap* source) {
  if (destination == source) {
    return destination;
  }
  const auto source_count =
      source == nullptr ? TargetSignedWord{0} : signed_map_count(*source);
  const auto count =
      source_count > 0 ? static_cast<TargetWord>(source_count) : 0u;
  resize_map(*destination, count);
  for (TargetWord index = 0; index < count; ++index) {
    destination->begin[index].id = source->begin[index].id;
    assign_property(destination->begin[index].property,
                    source->begin[index].property);
  }
  return destination;
}

void PKG_PROPERTY_WAVE9_THISCALL default_set_parent(OpaquePropertyList*,
                                                    OpaquePropertyList*) {}

bool default_read_words(OpaqueStream*, TargetWord*, TargetWord, TargetWord) {
  return false;
}

bool default_read_property(OpaqueStream*, OpaqueProperty*, TargetWord) {
  return false;
}

OpaquePropertyListFactory* default_get_factory() { return nullptr; }

void PKG_PROPERTY_WAVE9_THISCALL default_resize_words(OpaqueWordVector* vector,
                                                      TargetWord count) {
  if (count == 0 && vector->begin == nullptr) {
    vector->end = nullptr;
    return;
  }
  const auto old_count = static_cast<TargetWord>(
      (reinterpret_cast<std::uintptr_t>(vector->end) -
       reinterpret_cast<std::uintptr_t>(vector->begin)) /
      sizeof(TargetWord));
  const auto old_capacity = static_cast<TargetWord>(
      (reinterpret_cast<std::uintptr_t>(vector->capacity) -
       reinterpret_cast<std::uintptr_t>(vector->begin)) /
      sizeof(TargetWord));
  if (count > old_capacity) {
    auto* replacement = new TargetWord[count];
    for (TargetWord index = 0; index < old_count; ++index) {
      replacement[index] = vector->begin[index];
    }
    delete[] vector->begin;
    vector->begin = replacement;
    vector->end = replacement + old_count;
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

#undef PKG_PROPERTY_WAVE9_THISCALL

}

PropertyListRuntime& property_list_runtime() {
  static PropertyListRuntime runtime{default_conversion,  default_error_port,
                                     default_map_copy,    default_set_parent,
                                     default_read_words,  default_read_property,
                                     default_get_factory, default_resize_words};
  return runtime;
}

#if defined(_MSC_VER)
#define PKG_PROPERTY_WAVE9_THISCALL __thiscall
#else
#define PKG_PROPERTY_WAVE9_THISCALL __attribute__((thiscall))
#endif

void PKG_PROPERTY_WAVE9_THISCALL
direct_property_list_add_properties_from_006a1600(OpaquePropertyList* list,
                                                  OpaquePropertyList* other) {
  if (list == other) {
    return;
  }
  for (OpaquePropertyEntry* entry = other->properties.begin;
       entry != other->properties.end; ++entry) {
    list->vtable->set_property_14(list, entry->id, &entry->property);
  }
  ++list->operations_done;
}

bool PKG_PROPERTY_WAVE9_THISCALL direct_property_list_get_property_alt_006a1e50(
    OpaquePropertyList* list, TargetWord property_id, OpaqueProperty** result) {
  if (property_id < list->fast_count) {
    *result = list->vtable->get_property_object_28(list, property_id);
    return true;
  }
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

void PKG_PROPERTY_WAVE9_THISCALL property_list_copy_from_006a2a40(
    OpaquePropertyList* list, OpaquePropertyList* other) {
  if (list == other) {
    return;
  }
  property_list_runtime().map_copy(&list->properties, &other->properties);
  list->properties.lookup_mode = other->properties.lookup_mode;
  property_list_runtime().set_parent(list, list->parent);
}

void PKG_PROPERTY_WAVE9_THISCALL
property_list_clear_006a2a80(OpaquePropertyList* list) {
  destroy_entries(list->properties.begin, list->properties.end);
  list->properties.end = list->properties.begin;
  ++list->operations_done;
}

void PKG_PROPERTY_WAVE9_THISCALL direct_property_list_copy_from_006a2ad0(
    OpaquePropertyList* list, OpaquePropertyList* other) {
  if (list == other) {
    return;
  }
  destroy_entries(list->properties.begin, list->properties.end);
  list->properties.end = list->properties.begin;
  for (OpaquePropertyEntry* entry = other->properties.begin;
       entry != other->properties.end; ++entry) {
    list->vtable->set_property_14(list, entry->id, &entry->property);
  }
  property_list_runtime().set_parent(list, list->parent);
}

void PKG_PROPERTY_WAVE9_THISCALL
direct_property_list_clear_006a2b20(OpaquePropertyList* list) {
  if (list->fast_count != 0) {
    std::memset(list->fast_values, 0,
                static_cast<std::size_t>(list->fast_count));
  }
  destroy_entries(list->properties.begin, list->properties.end);
  list->properties.end = list->properties.begin;
}

void PKG_PROPERTY_WAVE9_THISCALL property_list_set_property_006a2e20(
    OpaquePropertyList* list, TargetWord property_id, OpaqueProperty* value) {
  OpaquePropertyEntry* const entry = find_entry(list->properties, property_id);
  if (entry != list->properties.end) {
    assign_property(entry->property, *value);
    ++list->operations_done;
    return;
  }

  OpaquePropertyEntry temporary{};
  temporary.id = property_id;
  assign_property(temporary.property, *value);
  insert_entry(list->properties, property_id, temporary.property);
  if ((temporary.property.flags & 0x0004u) != 0) {
    cleanup_property(temporary.property, 0u);
  }
  ++list->operations_done;
}

TargetSignedWord PKG_PROPERTY_WAVE9_THISCALL
property_list_remove_property_006a2ef0(OpaquePropertyList* list,
                                       TargetWord property_id) {
  OpaquePropertyEntry* entry = find_entry(list->properties, property_id);
  if (entry == list->properties.end) {
    ++list->operations_done;
    return 0;
  }
  for (OpaquePropertyEntry* source = entry + 1; source != list->properties.end;
       ++source) {
    entry->id = source->id;
    assign_property(entry->property, source->property);
    if (source + 1 != list->properties.end) {
      ++entry;
    }
  }
  --list->properties.end;
  if ((list->properties.end->property.flags & 0x0004u) != 0) {
    cleanup_property(list->properties.end->property, 0u);
  }
  ++list->operations_done;
  return 1;
}

void PKG_PROPERTY_WAVE9_THISCALL property_list_add_properties_from_006a2f10(
    OpaquePropertyList* list, OpaquePropertyList* other) {
  if (list == other) {
    return;
  }
  for (OpaquePropertyEntry* source = other->properties.begin;
       source != other->properties.end; ++source) {
    OpaquePropertyEntry* const destination =
        obtain_property_entry(list->properties, source->id);
    assign_property(destination->property, source->property);
  }
  ++list->operations_done;
}

bool PKG_PROPERTY_WAVE9_THISCALL
property_list_read_006a2f60(OpaquePropertyList* list, OpaqueStream* stream) {
  PropertyListRuntime& runtime = property_list_runtime();
  TargetWord count = 0;
  bool success = runtime.read_words(stream, &count, 1u, 0u);
  if (success && (count & 0x80000000u) != 0) {
    std::array<TargetWord, 3> key{};
    success = runtime.read_words(stream, key.data(), 3u, 0u);
    OpaquePropertyListFactory* const factory = runtime.get_factory();
    OpaquePropertyList* const previous_parent = list->parent;
    if (previous_parent != nullptr) {
      list->parent = nullptr;
      previous_parent->vtable->release_04(previous_parent);
    }
    factory->vtable->create_from_key_2c(factory, key[0], key[2], &list->parent);
  }

  const TargetWord entry_count = count & 0x7fffffffu;
  resize_map(list->properties, entry_count);
  OpaquePropertyEntry* entry = list->properties.begin;
  while (entry != list->properties.end) {
    if (!success) {
      success = false;
    } else {
      success = runtime.read_words(stream, &entry->id, 1u, 0u);
      if (success) {
        success = runtime.read_property(stream, &entry->property, 0u);
      }
    }
    ++entry;
  }
  return success;
}

void PKG_PROPERTY_WAVE9_THISCALL property_list_get_property_ids_006a3070(
    OpaquePropertyList* list, OpaqueWordVector* destination) {
  const auto count = signed_map_count(list->properties);
  const auto unsigned_count = count > 0 ? static_cast<TargetWord>(count) : 0u;
  property_list_runtime().resize_words(destination, unsigned_count);
  OpaquePropertyEntry* entry = list->properties.begin;
  TargetWord index = 0;
  while (entry != list->properties.end) {
    destination->begin[index] = entry->id;
    ++entry;
    ++index;
  }
}

#undef PKG_PROPERTY_WAVE9_THISCALL

}
