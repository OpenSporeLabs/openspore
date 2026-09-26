#include "property_list_variants.hpp"

namespace openspore::reconstruction::wave6_resources {

#if defined(_MSC_VER)
#define WAVE6_VARIANT_THISCALL __thiscall
#else
#define WAVE6_VARIANT_THISCALL __attribute__((thiscall))
#endif

namespace {

PropertyMapEntry* lower_bound_entries(const PropertyMap& map,
                                      TargetWord property_id) {
  PropertyMapEntry* current = map.entries_begin;
  std::size_t count = 0;
  const auto begin_address =
      reinterpret_cast<std::uintptr_t>(map.entries_begin);
  const auto end_address = reinterpret_cast<std::uintptr_t>(map.entries_end);
  if (begin_address != 0 && end_address >= begin_address) {
    count = static_cast<std::size_t>((end_address - begin_address) / 0x18u);
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

bool has_parent_property(PropertyList* parent, TargetWord property_id) {
  const auto* vtable =
      reinterpret_cast<const HasParentVtable*>(parent->vftable);
  return vtable->get_at_1c(parent, property_id);
}

Property* get_parent_property_object(PropertyList* parent,
                                     TargetWord property_id) {
  const auto* vtable =
      reinterpret_cast<const ObjectParentVtable*>(parent->vftable);
  return vtable->get_at_28(parent, property_id);
}

}

bool WAVE6_VARIANT_THISCALL property_list_has_property_006a2470(
    PropertyList* list, TargetWord property_id) {
  PropertyMapEntry* entry = lower_bound_entries(list->properties, property_id);
  if (entry != list->properties.entries_end && property_id >= entry->key) {
    return true;
  }
  if (list->parent != nullptr) {
    return has_parent_property(list->parent, property_id);
  }
  return false;
}

Property* WAVE6_VARIANT_THISCALL property_list_get_property_object_006a24d0(
    PropertyList* list, TargetWord property_id) {
  PropertyMapEntry* entry = lower_bound_entries(list->properties, property_id);
  if (entry != list->properties.entries_end && property_id >= entry->key) {
    return &entry->property;
  }
  if (list->parent != nullptr) {
    return get_parent_property_object(list->parent, property_id);
  }
  return reinterpret_cast<Property*>(static_cast<std::uintptr_t>(0x016027d0u));
}

#undef WAVE6_VARIANT_THISCALL

}
