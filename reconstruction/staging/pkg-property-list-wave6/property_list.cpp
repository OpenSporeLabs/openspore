#include "property_list.hpp"

namespace openspore::reconstruction::pkg_property_list_wave6 {

namespace {

bool default_write_words(Wave6OpaqueStream*, const Wave6Word*, Wave6Word,
                         Wave6Word) {
  return false;
}

bool default_write_property(Wave6OpaqueStream*, Wave6Property*, Wave6Word) {
  return false;
}

std::int32_t signed_entry_count(Wave6PropertyEntry* begin,
                                Wave6PropertyEntry* end) {
  const auto* first = reinterpret_cast<const std::uint8_t*>(begin);
  const auto* last = reinterpret_cast<const std::uint8_t*>(end);
  return static_cast<std::int32_t>(last - first) /
         static_cast<std::int32_t>(sizeof(Wave6PropertyEntry));
}

Wave6PropertyEntry* lower_bound_entries(Wave6PropertyEntry* begin,
                                        Wave6PropertyEntry* end,
                                        const Wave6Word* property_id,
                                        std::uint8_t lookup_mode) {
  static_cast<void>(lookup_mode);
  Wave6PropertyEntry* current = begin;
  std::int32_t count = signed_entry_count(begin, end);
  while (count > 0) {
    const std::int32_t middle = count >> 1;
    if (current[middle].id < *property_id) {
      current += middle + 1;
      count += -1 - middle;
    } else {
      count = middle;
    }
  }
  return current;
}

Wave6PropertyEntry* find_entry(Wave6PropertyList* list, Wave6Word property_id) {
  Wave6PropertyEntry* const end = list->entries_end_1c;
  Wave6PropertyEntry* const candidate = lower_bound_entries(
      list->entries_begin_18, end, &property_id, list->lookup_mode_2c);
  if (candidate == end || property_id < candidate->id) {
    return end;
  }
  const auto address = reinterpret_cast<std::uintptr_t>(candidate);
  if (address == address + sizeof(Wave6PropertyEntry)) {
    return end;
  }
  return candidate;
}

Wave6Property* missing_property() {
  return reinterpret_cast<Wave6Property*>(
      static_cast<std::uintptr_t>(0x016027d0u));
}

}

Wave6NativePorts& wave6_property_list_native_ports() {
  static Wave6NativePorts ports{default_write_words, default_write_property};
  return ports;
}

#if defined(_MSC_VER)
#define WAVE6_PROPERTY_THISCALL __thiscall
#else
#define WAVE6_PROPERTY_THISCALL __attribute__((thiscall))
#endif

void WAVE6_PROPERTY_THISCALL
app_property_list_copy_all_properties_from_006a14d0(Wave6PropertyList* list,
                                                    Wave6PropertyList* other) {
  if (list == other) {
    return;
  }
  Wave6PropertyList* const parent = list->parent_30;
  if (parent != nullptr) {
    list->parent_30 = nullptr;
    parent->vtable->release_04(parent);
  }
  list->vtable->clear_48(list);
  list->vtable->add_all_38(list, other);
}

void WAVE6_PROPERTY_THISCALL app_property_list_add_all_properties_from_006a1510(
    Wave6PropertyList* list, Wave6PropertyList* other) {
  Wave6PropertyList* const parent = other->parent_30;
  if (parent != nullptr) {
    list->vtable->add_all_38(list, parent);
  }
  list->vtable->add_all_30(list, other);
}

bool WAVE6_PROPERTY_THISCALL app_property_list_write_006a1540(
    Wave6PropertyList* list, Wave6OpaqueStream* stream) {
  const std::int32_t count =
      signed_entry_count(list->entries_begin_18, list->entries_end_1c);
  Wave6Word count_word = static_cast<Wave6Word>(count);
  Wave6NativePorts& ports = wave6_property_list_native_ports();
  bool success = ports.write_words_0093aa70(stream, &count_word, 1, 0);
  if (count <= 0) {
    return success;
  }
  for (std::int32_t index = 0; index < count; ++index) {
    if (!success) {
      success = false;
      continue;
    }
    Wave6PropertyEntry& entry = list->entries_begin_18[index];
    Wave6Word id_word = entry.id;
    success = ports.write_words_0093aa70(stream, &id_word, 1, 0);
    if (!success) {
      continue;
    }
    success = ports.write_property_00693390(stream, &entry.property, 0);
  }
  return success;
}

bool WAVE6_PROPERTY_THISCALL app_property_list_get_property_alt_006a1de0(
    Wave6PropertyList* list, Wave6Word property_id, Wave6Property** result) {
  Wave6PropertyEntry* const entry = find_entry(list, property_id);
  if (entry != list->entries_end_1c) {
    *result = &entry->property;
    return true;
  }
  Wave6PropertyList* const parent = list->parent_30;
  if (parent != nullptr) {
    return parent->vtable->parent_get_alt_20(parent, property_id, result);
  }
  return false;
}

bool WAVE6_PROPERTY_THISCALL app_property_list_has_property_006a2470(
    Wave6PropertyList* list, Wave6Word property_id) {
  if (find_entry(list, property_id) != list->entries_end_1c) {
    return true;
  }
  Wave6PropertyList* const parent = list->parent_30;
  if (parent != nullptr) {
    return parent->vtable->parent_has_1c(parent, property_id);
  }
  return false;
}

Wave6Property* WAVE6_PROPERTY_THISCALL
app_property_list_get_property_object_006a24d0(Wave6PropertyList* list,
                                               Wave6Word property_id) {
  Wave6PropertyEntry* const entry = find_entry(list, property_id);
  if (entry != list->entries_end_1c) {
    return &entry->property;
  }
  Wave6PropertyList* const parent = list->parent_30;
  if (parent != nullptr) {
    return parent->vtable->parent_get_object_28(parent, property_id);
  }
  return missing_property();
}

bool WAVE6_PROPERTY_THISCALL app_property_list_get_property_006a2530(
    Wave6PropertyList* list, Wave6Word property_id, Wave6Property** result) {
  Wave6PropertyEntry* const entry = find_entry(list, property_id);
  if (entry != list->entries_end_1c) {
    *result = &entry->property;
    return true;
  }
  Wave6PropertyList* const parent = list->parent_30;
  if (parent != nullptr) {
    return parent->vtable->parent_get_24(parent, property_id, result);
  }
  return false;
}

#undef WAVE6_PROPERTY_THISCALL

}
