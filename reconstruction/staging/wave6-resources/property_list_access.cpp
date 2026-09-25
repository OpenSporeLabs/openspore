#include "property_list_access.hpp"

namespace openspore::reconstruction::wave6_resources {

#if defined(_MSC_VER)
#define WAVE6_PROPERTY_THISCALL __thiscall
#else
#define WAVE6_PROPERTY_THISCALL __attribute__((thiscall))
#endif

namespace {

PropertyMapEntry* lower_bound_entries(const PropertyMap& map,
                                      TargetWord property_id) {
  PropertyMapEntry* current = map.entries_begin;
  const PropertyMapEntry* end = map.entries_end;
  std::size_t count = 0;
  if (current != nullptr && end != nullptr && end >= current) {
    count = static_cast<std::size_t>(end - current) /
            sizeof(PropertyMapEntry);
  }
  while (count != 0) {
    const std::size_t half = count / 2;
    PropertyMapEntry* middle = current + half;
    if (middle->key < property_id) {
      current = middle + 1;
      count -= half + 1;
    } else {
      count = half;
    }
  }
  return current;
}

}

bool WAVE6_PROPERTY_THISCALL property_list_get_property_006a2530(
    PropertyList* list, TargetWord property_id, Property** result) {
  PropertyMapEntry* entry = lower_bound_entries(list->properties, property_id);
  if (entry != list->properties.entries_end &&
      property_id >= entry->key) {
    *result = &entry->property;
    return true;
  }
  if (list->parent != nullptr) {
    return list->parent->vftable->get_property_at_24(list->parent, property_id,
                                                      result);
  }
  return false;
}

#undef WAVE6_PROPERTY_THISCALL

}
