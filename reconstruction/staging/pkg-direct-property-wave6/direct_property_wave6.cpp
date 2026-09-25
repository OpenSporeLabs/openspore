#include "direct_property_wave6.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_direct_property_wave6 {
namespace {

OpaquePropertyService* opaque_property_service = nullptr;
OpaqueList* opaque_fast_list = nullptr;
OpaqueBaseInsert opaque_base_insert = nullptr;
OpaqueErrorPort opaque_error_port = nullptr;
OpaqueTypeConversion opaque_type_conversion = nullptr;
OpaqueProperty opaque_default_property{};

void no_error_port(TargetWord) {}

void no_type_conversion(TargetWord, TargetWord, const void*, TargetWord,
                        TargetWord) {}

OpaqueMapEntry* lower_bound_entries(const OpaqueMap& map, TargetWord key) {
  auto begin = reinterpret_cast<std::uintptr_t>(map.field_00);
  const auto end = reinterpret_cast<std::uintptr_t>(map.field_04);
  auto count = static_cast<std::ptrdiff_t>(
      (end - begin) / static_cast<std::uintptr_t>(sizeof(OpaqueMapEntry)));
  while (count > 0) {
    const auto middle = static_cast<std::size_t>(count >> 1);
    auto* candidate = reinterpret_cast<OpaqueMapEntry*>(
        begin + middle * sizeof(OpaqueMapEntry));
    if (candidate->field_00 < key) {
      begin = reinterpret_cast<std::uintptr_t>(candidate) +
              sizeof(OpaqueMapEntry);
      count = count - static_cast<std::ptrdiff_t>(middle) - 1;
    } else {
      count = static_cast<std::ptrdiff_t>(middle);
    }
  }
  return reinterpret_cast<OpaqueMapEntry*>(begin);
}

OpaqueMapEntry* find_entry(const OpaqueMap& map, TargetWord key) {
  OpaqueMapEntry* candidate = lower_bound_entries(map, key);
  if (candidate == map.field_04 || key < candidate->field_00) {
    return map.field_04;
  }
  return candidate;
}

void copy_property(OpaqueProperty& destination,
                   const OpaqueProperty& source) {
  if ((destination.field_10 & 0x0004u) != 0) {
    opaque_error_port(1u);
  }
  if ((source.field_10 & 0x0008u) == 0 &&
      ((destination.field_10 & 0x0002u) == 0 ||
       destination.field_12 == source.field_12)) {
    std::memcpy(destination.field_00_0f.data(), source.field_00_0f.data(),
                destination.field_00_0f.size());
    destination.field_12 = source.field_12;
    destination.field_10 = static_cast<std::uint16_t>(
        (source.field_10 & 0xfffdu) | (destination.field_10 & 0x0002u));
    return;
  }

  if ((source.field_10 & 0x0030u) == 0) {
    opaque_type_conversion(source.field_12, source.field_10, &source, 0x10u,
                           1u);
  } else {
    TargetWord pointer_word = 0;
    std::memcpy(&pointer_word, source.field_00_0f.data(),
                sizeof(pointer_word));
    TargetWord size_word = 0;
    TargetWord mode_word = 0;
    std::memcpy(&size_word, source.field_00_0f.data() + sizeof(TargetWord),
                sizeof(size_word));
    std::memcpy(&mode_word, source.field_00_0f.data() + sizeof(TargetWord) * 2u,
                sizeof(mode_word));
    opaque_type_conversion(source.field_12, source.field_10,
                           reinterpret_cast<const void*>(
                               static_cast<std::uintptr_t>(pointer_word)),
                           size_word, mode_word);
  }
}

const std::uint8_t* property_value_pointer(const OpaqueProperty* property) {
  if ((property->field_10 & 0x0030u) != 0) {
    TargetWord pointer_word = 0;
    std::memcpy(&pointer_word, property->field_00_0f.data(),
                sizeof(pointer_word));
    return reinterpret_cast<const std::uint8_t*>(
        static_cast<std::uintptr_t>(pointer_word));
  }
  if (property->field_12 != 0) {
    return property->field_00_0f.data();
  }
  return nullptr;
}

bool load_property_bool(const OpaqueProperty* property) {
  const auto* value = property_value_pointer(property);
  return *value != 0;
}

TargetWord load_property_word(const OpaqueProperty* property) {
  const auto* value = property_value_pointer(property);
  TargetWord result = 0;
  std::memcpy(&result, value, sizeof(result));
  return result;
}

float load_property_float(const OpaqueProperty* property) {
  const auto* value = property_value_pointer(property);
  float result = 0.0f;
  std::memcpy(&result, value, sizeof(result));
  return result;
}

void set_property_bool(OpaqueProperty& destination, bool value) {
  if ((destination.field_10 & 0x0004u) != 0) {
    opaque_error_port(1u);
  }
  if ((destination.field_10 & 0x0002u) == 0 || destination.field_12 == 1u) {
    destination.field_00_0f[0] = static_cast<std::uint8_t>(value);
    destination.field_12 = 1u;
    destination.field_10 &= 0x0002u;
    return;
  }
  opaque_type_conversion(1u, 0u, &value, 1u, 1u);
}

void set_property_word(OpaqueProperty& destination, TargetWord value,
                       std::uint16_t type) {
  if ((destination.field_10 & 0x0004u) != 0) {
    opaque_error_port(1u);
  }
  if ((destination.field_10 & 0x0002u) == 0 ||
      destination.field_12 == type) {
    std::memcpy(destination.field_00_0f.data(), &value, sizeof(value));
    destination.field_12 = type;
    destination.field_10 &= 0x0002u;
    return;
  }
  opaque_type_conversion(type, 0u, &value, sizeof(value), 1u);
}

void set_property_float(OpaqueProperty& destination, float value) {
  if ((destination.field_10 & 0x0004u) != 0) {
    opaque_error_port(1u);
  }
  if ((destination.field_10 & 0x0002u) == 0 ||
      destination.field_12 == 0x0du) {
    std::memcpy(destination.field_00_0f.data(), &value, sizeof(value));
    destination.field_12 = 0x0du;
    destination.field_10 &= 0x0002u;
    return;
  }
  opaque_type_conversion(0x0du, 0u, &value, sizeof(value), 1u);
}

bool base_has_property(OpaqueList* list, TargetWord property_id) {
  const OpaqueMapEntry* entry = find_entry(list->field_18, property_id);
  if (entry != list->field_18.field_04) {
    return true;
  }
  if (list->field_30 != nullptr) {
    return list->field_30->field_00->field_1c(list->field_30, property_id);
  }
  return false;
}

OpaqueProperty* base_get_property_object(OpaqueList* list,
                                         TargetWord property_id) {
  OpaqueMapEntry* entry = find_entry(list->field_18, property_id);
  if (entry != list->field_18.field_04) {
    return &entry->field_04;
  }
  if (list->field_30 != nullptr) {
    return list->field_30->field_00->field_28(list->field_30, property_id);
  }
  return &opaque_default_property;
}

bool base_get_property(OpaqueList* list, TargetWord property_id,
                       OpaqueProperty** result) {
  OpaqueMapEntry* entry = find_entry(list->field_18, property_id);
  if (entry != list->field_18.field_04) {
    *result = &entry->field_04;
    return true;
  }
  if (list->field_30 != nullptr) {
    return list->field_30->field_00->field_24(list->field_30, property_id,
                                               result);
  }
  return false;
}

void base_set_property(OpaqueList* list, TargetWord property_id,
                       OpaqueProperty* value) {
  OpaqueMapEntry* entry = find_entry(list->field_18, property_id);
  if (entry != list->field_18.field_04) {
    copy_property(entry->field_04, *value);
  } else {
    opaque_base_insert(list, property_id, value);
  }
  ++list->field_34;
}

void set_fast_bool(OpaqueList* list, TargetWord property_id, bool value) {
  if (property_id < list->field_38) {
    list->field_3c[property_id] = static_cast<std::uint8_t>(value);
    return;
  }
  OpaqueProperty temporary{};
  temporary.field_10 = 2u;
  temporary.field_12 = 1u;
  set_property_bool(temporary, value);
  list->field_00->field_14(list, property_id, &temporary);
}

void set_fast_word(OpaqueList* list, TargetWord property_id, TargetWord value) {
  if (property_id < list->field_38) {
    list->field_3c[property_id] = value;
    return;
  }
  OpaqueProperty temporary{};
  temporary.field_10 = 2u;
  temporary.field_12 = 9u;
  set_property_word(temporary, value, 9u);
  list->field_00->field_14(list, property_id, &temporary);
}

void set_fast_float(OpaqueList* list, TargetWord property_id, float value) {
  if (property_id < list->field_38) {
    std::memcpy(&list->field_3c[property_id], &value, sizeof(value));
    return;
  }
  OpaqueProperty temporary{};
  temporary.field_10 = 2u;
  temporary.field_12 = 0x0du;
  set_property_float(temporary, value);
  list->field_00->field_14(list, property_id, &temporary);
}

void vector_grow(OpaqueWordVector& vector, std::size_t capacity) {
  auto* replacement = new TargetWord[capacity];
  const auto count = static_cast<std::size_t>(
      (reinterpret_cast<std::uintptr_t>(vector.field_04) -
       reinterpret_cast<std::uintptr_t>(vector.field_00)) /
      sizeof(TargetWord));
  if (count != 0) {
    std::memcpy(replacement, vector.field_00, count * sizeof(TargetWord));
  }
  delete[] vector.field_00;
  vector.field_00 = replacement;
  vector.field_04 = replacement + count;
  vector.field_08 = replacement + capacity;
}

void vector_append(OpaqueWordVector& vector, TargetWord value) {
  if (vector.field_04 == vector.field_08) {
    const auto count = static_cast<std::size_t>(
        (reinterpret_cast<std::uintptr_t>(vector.field_04) -
         reinterpret_cast<std::uintptr_t>(vector.field_00)) /
        sizeof(TargetWord));
    vector_grow(vector, count == 0 ? 1u : count * 2u);
  }
  if (vector.field_04 != nullptr) {
    *vector.field_04 = value;
  }
  ++vector.field_04;
}

void vector_insert_zero(OpaqueWordVector& vector, std::size_t count) {
  if (count == 0) {
    return;
  }
  const auto current = static_cast<std::size_t>(
      (reinterpret_cast<std::uintptr_t>(vector.field_04) -
       reinterpret_cast<std::uintptr_t>(vector.field_00)) /
      sizeof(TargetWord));
  const auto capacity = static_cast<std::size_t>(
      (reinterpret_cast<std::uintptr_t>(vector.field_08) -
       reinterpret_cast<std::uintptr_t>(vector.field_00)) /
      sizeof(TargetWord));
  if (capacity - current < count) {
    const auto doubled = current == 0 ? 1u : current * 2u;
    const auto required = current + count;
    vector_grow(vector, doubled < required ? required : doubled);
  }
  if (vector.field_04 != nullptr) {
    std::memset(vector.field_04, 0, count * sizeof(TargetWord));
  }
  vector.field_04 += count;
}

}

void set_opaque_property_service(OpaquePropertyService* service) {
  opaque_property_service = service;
}

void set_opaque_fast_list(OpaqueList* list) { opaque_fast_list = list; }

void set_opaque_base_insert(OpaqueBaseInsert insert) {
  opaque_base_insert = insert;
}

void set_opaque_error_port(OpaqueErrorPort port) {
  opaque_error_port = port == nullptr ? no_error_port : port;
}

void set_opaque_type_conversion(OpaqueTypeConversion conversion) {
  opaque_type_conversion =
      conversion == nullptr ? no_type_conversion : conversion;
}

#if defined(_MSC_VER)
#define PKG20_WAVE6_THISCALL __thiscall
#else
#define PKG20_WAVE6_THISCALL __attribute__((thiscall))
#endif

bool PKG20_WAVE6_THISCALL opaque_list_has_property_006a27d0(
    OpaqueList* list, TargetWord property_id) {
  if (property_id == 0 || list->field_38 <= property_id) {
    return base_has_property(list, property_id);
  }
  return true;
}

OpaqueProperty* PKG20_WAVE6_THISCALL opaque_list_get_property_object_006a2800(
    OpaqueList* list, TargetWord property_id) {
  if (list->field_38 <= property_id) {
    return base_get_property_object(list, property_id);
  }

  OpaqueProperty* source = opaque_property_service->field_00->field_50(
      opaque_property_service, property_id);
  copy_property(list->field_40, *source);
  if ((list->field_40.field_10 & 0x0010u) == 0) {
    if (list->field_40.field_12 == 1u) {
      set_property_bool(list->field_40, list->field_3c[property_id] != 0);
    } else if (list->field_40.field_12 == 9u) {
      set_property_word(list->field_40, list->field_3c[property_id], 9u);
    } else if (list->field_40.field_12 == 0x0du) {
      float value = 0.0f;
      std::memcpy(&value, &list->field_3c[property_id], sizeof(value));
      set_property_float(list->field_40, value);
    }
  }
  return &list->field_40;
}

bool PKG20_WAVE6_THISCALL opaque_list_get_property_006a28c0(
    OpaqueList* list, TargetWord property_id, OpaqueProperty** result) {
  if (list->field_38 > property_id) {
    *result = list->field_00->field_28(list, property_id);
    return true;
  }
  return base_get_property(list, property_id, result);
}

void PKG20_WAVE6_THISCALL opaque_list_set_property_006a30c0(
    OpaqueList* list, TargetWord property_id, OpaqueProperty* value) {
  if (list->field_38 <= property_id) {
    base_set_property(list, property_id, value);
    return;
  }

  OpaqueProperty* source = opaque_property_service->field_00->field_50(
      opaque_property_service, property_id);
  const std::uint16_t type = source->field_12;
  if (type == 1u && (source->field_10 & 0x0010u) == 0) {
    set_fast_bool(opaque_fast_list, property_id,
                  load_property_bool(source));
    return;
  }
  if (type == 9u && (source->field_10 & 0x0010u) == 0) {
    set_fast_word(opaque_fast_list, property_id, load_property_word(source));
    return;
  }
  if (type == 0x0du && (source->field_10 & 0x0010u) == 0) {
    set_fast_float(opaque_fast_list, property_id, load_property_float(source));
  }
}

void PKG20_WAVE6_THISCALL opaque_list_get_property_ids_006a3180(
    OpaqueList* list, OpaqueWordVector* destination) {
  destination->field_04 = destination->field_00;

  std::size_t direct_count = 0;
  if (list->field_38 > 1) {
    for (TargetWord property_id = 1; property_id < list->field_38;
         ++property_id) {
      OpaqueProperty* property = opaque_property_service->field_00->field_50(
          opaque_property_service, property_id);
      if (property->field_12 != 0) {
        vector_append(*destination, property_id);
        ++direct_count;
      }
    }
  }

  const auto map_count = static_cast<std::size_t>(
      (reinterpret_cast<std::uintptr_t>(list->field_18.field_04) -
       reinterpret_cast<std::uintptr_t>(list->field_18.field_00)) /
      sizeof(OpaqueMapEntry));
  vector_insert_zero(*destination, map_count);

  const auto entry_begin = reinterpret_cast<std::uintptr_t>(
      list->field_18.field_00);
  for (std::size_t index = 0; index < map_count; ++index) {
    const auto* entry = reinterpret_cast<const OpaqueMapEntry*>(
        entry_begin + index * sizeof(OpaqueMapEntry));
    destination->field_00[direct_count + index] = entry->field_00;
  }
}

#undef PKG20_WAVE6_THISCALL

}
