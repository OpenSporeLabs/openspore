#include "empire_wave3.hpp"

#include <algorithm>
#include <limits>

namespace openspore::reconstruction::pkg13_e4_empire_wave3 {

namespace {

constexpr OpaqueWord kPaletteBase = 0x53dbcf3u;
constexpr OpaqueWord kCurrentColor = 0x53dbcf1u;
constexpr float kMaximumDistance = std::numeric_limits<float>::max();
constexpr float kBlack[3] = {0.0f, 0.0f, 0.0f};
constexpr OpaqueFloatColor kIdentityColor{{0.2f, 0.0f, 0.25f}};

OpaqueRecord* PKG13_E4_CDECL default_current_empire() { return nullptr; }

OpaqueRegistry* PKG13_E4_CDECL default_registry() { return nullptr; }

OpaqueResourceRecord* PKG13_E4_THISCALL default_registry_record(OpaqueRegistry*,
                                                                OpaqueWord) {
  return nullptr;
}

OpaqueWord PKG13_E4_THISCALL default_resource_type(OpaqueResourceRecord*) {
  return 0u;
}

OpaqueProfile* PKG13_E4_THISCALL
default_resource_profile(OpaqueResourceRecord*) {
  return nullptr;
}

OpaqueProfile* PKG13_E4_THISCALL default_current_profile(OpaqueRecord*) {
  return nullptr;
}

OpaqueWord PKG13_E4_THISCALL default_registry_identity(OpaqueRegistry*) {
  return 0u;
}

const OpaqueFloatColor* PKG13_E4_CDECL default_palette(OpaqueWord) {
  return nullptr;
}

std::uint8_t PKG13_E4_CDECL default_palette_active(OpaqueWord) { return 0u; }

bool PKG13_E4_CDECL default_color_equal(const OpaqueFloatColor*,
                                        const OpaqueFloatColor*) {
  return false;
}

void PKG13_E4_CDECL default_color_transform(const OpaqueFloatColor*,
                                            OpaqueFloatColor*, float, float) {}

void PKG13_E4_CDECL default_palette_write(float, float, float) {}

void PKG13_E4_CDECL default_palette_rebuild() {}

const OpaqueFloatColor* PKG13_E4_THISCALL
default_vector_source(OpaqueResourceRecord*) {
  return nullptr;
}

void PKG13_E4_THISCALL default_vector_collect(OpaqueRegistry*,
                                              const OpaqueFloatColor*,
                                              OpaqueVectorQuery*,
                                              OpaqueVectorItem***) {}

OpaqueWord PKG13_E4_THISCALL default_vector_item_word(OpaqueVectorItem*) {
  return 0u;
}

OpaqueRecord* PKG13_E4_THISCALL default_registry_candidate(OpaqueRegistry*,
                                                           OpaqueWord) {
  return nullptr;
}

void PKG13_E4_CDECL default_vector_storage_cleanup(OpaqueVectorItem**) {}

OpaqueRecordRange* PKG13_E4_THISCALL default_root_range(OpaqueRecord*) {
  return nullptr;
}

OpaqueWord PKG13_E4_THISCALL default_record_type(OpaqueRecord*) { return 0u; }

std::uint8_t PKG13_E4_THISCALL default_record_state(OpaqueRecord*) {
  return 0u;
}

float PKG13_E4_THISCALL default_star_metric(OpaqueRecord*) { return 0.0f; }

OpaqueWord PKG13_E4_THISCALL default_star_identity(OpaqueRecord*) { return 0u; }

void PKG13_E4_CDECL default_ownership_apply(OpaqueRecord*, std::int32_t) {}

OpaqueWord PKG13_E4_CDECL default_current_identity() { return 0u; }

OpaqueRecord* PKG13_E4_CDECL default_current_star() { return nullptr; }

OpaqueWord PKG13_E4_CDECL default_current_mode() { return 0u; }

OpaqueWord PKG13_E4_THISCALL default_record_reference(OpaqueRecord*) {
  return 0u;
}

std::int32_t PKG13_E4_CDECL default_current_star_count(OpaqueRecord*) {
  return 0;
}

OpaqueRecord* PKG13_E4_CDECL default_cleanup_root() { return nullptr; }

OpaqueWord PKG13_E4_THISCALL default_cleanup_record_word(OpaqueRecord*) {
  return 0u;
}

void PKG13_E4_THISCALL default_cleanup_list(OpaqueWord) {}

OpaqueMessageService* PKG13_E4_CDECL default_message_service() {
  return nullptr;
}

OpaqueMessageRoot* PKG13_E4_CDECL default_message_root() { return nullptr; }

OpaqueMessageState* PKG13_E4_THISCALL
default_message_state(OpaqueMessageRoot*) {
  return nullptr;
}

bool PKG13_E4_THISCALL default_message_contains(OpaqueMessageState*,
                                                OpaqueWord) {
  return false;
}

bool PKG13_E4_THISCALL default_message_insert(OpaqueMessageState*, OpaqueWord) {
  return false;
}

OpaquePersistenceTarget* PKG13_E4_CDECL default_persistence_lookup(OpaqueWord) {
  return nullptr;
}

void PKG13_E4_THISCALL default_persistence_append(OpaquePersistenceTarget*,
                                                  OpaqueWord) {}

bool is_palette_index(OpaqueWord value) { return value - kPaletteBase <= 11u; }

void copy_color(const OpaqueFloatColor* source, OpaqueFloatColor* output) {
  output->value[0] = source->value[0];
  output->value[1] = source->value[1];
  output->value[2] = source->value[2];
}

OpaqueResourceRecord* resolve_record(EmpireColorPorts& ports,
                                     OpaqueRecord* record) {
  const OpaqueWord handle = record->field_b0;
  if (handle == 0xffffffffu) {
    return nullptr;
  }
  return ports.registry_record(ports.registry(), handle);
}

OpaqueFloatColor* copy_palette(EmpireColorPorts& ports, OpaqueWord value,
                               OpaqueFloatColor* output) {
  copy_color(ports.palette(value), output);
  return output;
}

}

EmpireColorPorts& empire_color_ports() {
  static EmpireColorPorts ports{
      default_current_empire,     default_registry,
      default_registry_record,    default_resource_type,
      default_resource_profile,   default_current_profile,
      default_registry_identity,  default_palette,
      default_palette_active,     default_color_equal,
      default_color_transform,    default_palette_write,
      default_palette_rebuild,    default_vector_source,
      default_vector_collect,     default_vector_item_word,
      default_registry_candidate, default_vector_storage_cleanup};
  return ports;
}

extern "C" OpaqueFloatColor* PKG13_E4_THISCALL
EmpirePoliticalColor_00c32cd0(OpaqueRecord* record, OpaqueFloatColor* output) {
  EmpireColorPorts& ports = empire_color_ports();
  const OpaqueWord value = record->field_10;
  if (is_palette_index(value)) {
    return copy_palette(ports, value, output);
  }

  OpaqueRecord* const current = ports.current_empire();
  if (record == current) {
    if (value != kCurrentColor) {
      OpaqueResourceRecord* const resource = resolve_record(ports, record);
      OpaqueProfile* const profile =
          resource == nullptr ? nullptr : ports.resource_profile(resource);
      ports.color_transform(&profile->color_4ec, output, 0.5f, 0.5f);
      ports.palette_write(output->value[0], output->value[1], output->value[2]);
      ports.palette_rebuild();
      record->color_30 = *output;
      record->field_10 = kCurrentColor;
    }
    if (record->color_30.value[0] == kBlack[0] &&
        record->color_30.value[1] == kBlack[1] &&
        record->color_30.value[2] == kBlack[2]) {
      copy_palette(ports, record->field_10, &record->color_30);
    }
    return copy_palette(ports, record->field_10, output);
  }

  if ((record->field_50 >> 6 & 1u) != 0u) {
    OpaqueResourceRecord* const resource = resolve_record(ports, record);
    if (ports.resource_type(resource) == 5u && value == kCurrentColor) {
      OpaqueFloatColor local = record->color_30;
      if (ports.color_equal(
              &local, reinterpret_cast<const OpaqueFloatColor*>(kBlack))) {
        OpaqueProfile* const profile = ports.current_profile(record);
        OpaqueFloatColor transformed{};
        ports.color_transform(&profile->color_4ec, &transformed, 0.5f, 0.5f);
        record->color_30 = transformed;
      }
      *output = local;
      return output;
    }
  }

  OpaqueRegistry* const registry = ports.registry();
  if (ports.registry_identity(registry) == record->field_84) {
    *output = kIdentityColor;
    return output;
  }

  float distances[12];
  for (OpaqueWord index = 0u; index < 12u; ++index) {
    distances[index] =
        ports.palette_active(index) == 0u ? kMaximumDistance : 0.0f;
  }

  OpaqueVectorQuery query;
  query.begin = nullptr;
  query.end = nullptr;
  query.capacity = nullptr;
  query.field_14 = 0x1fffu;
  query.field_18 = 0u;
  query.field_1c = 50.0f;
  query.field_20 = -1.0f;
  query.field_24 = 0u;
  query.field_28 = -1.0f;
  query.field_2c = 0u;
  OpaqueResourceRecord* const current_resource = resolve_record(ports, record);
  const OpaqueFloatColor* const current_source =
      ports.vector_source(current_resource);
  OpaqueRegistry* const vector_registry = ports.registry();
  ports.vector_collect(vector_registry, current_source, &query, &query.end);

  OpaqueVectorItem** item = query.begin;
  while (item != query.end) {
    OpaqueVectorItem* const entry = *item;
    if (entry != nullptr) {
      const OpaqueWord identity = ports.vector_item_word(entry);
      if (identity != 0xffffffffu) {
        OpaqueRegistry* const candidate_registry = ports.registry();
        OpaqueRecord* const candidate =
            ports.registry_candidate(candidate_registry, identity);
        if (candidate != nullptr && is_palette_index(candidate->field_10)) {
          OpaqueResourceRecord* const candidate_resource =
              resolve_record(ports, candidate);
          OpaqueResourceRecord* const receiver_resource =
              resolve_record(ports, record);
          const OpaqueFloatColor* const candidate_source =
              ports.vector_source(candidate_resource);
          const OpaqueFloatColor* const receiver_source =
              ports.vector_source(receiver_resource);
          const float first =
              candidate_source->value[0] - receiver_source->value[0];
          const float second =
              candidate_source->value[1] - receiver_source->value[1];
          const float third =
              candidate_source->value[2] - receiver_source->value[2];
          const float distance =
              (first * first + third * third) + second * second;
          const OpaqueWord offset = candidate->field_10 - kPaletteBase;
          if (!(distance > distances[offset])) {
            distances[offset] = distance;
          }
        }
      }
    }
    ++item;
  }

  OpaqueWord selected = 0u;
  float selected_distance = 0.0f;
  for (OpaqueWord index = 0u; index < 12u; ++index) {
    if (selected_distance < distances[index]) {
      selected = index;
      selected_distance = distances[index];
    }
  }
  const OpaqueWord next =
      selected < 12u ? kPaletteBase + selected : kPaletteBase;
  record->field_10 = next;
  copy_palette(ports, next, output);

  for (item = query.begin; item != query.end; ++item) {
    OpaqueVectorItem* const entry = *item;
    if (entry != nullptr) {
      entry->vtable->slot_04(entry);
    }
  }
  if (query.begin != nullptr && query.begin[-1] != 0) {
    ports.vector_storage_cleanup(query.begin);
  }
  return output;
}

PoliticalOwnershipPorts& political_ownership_ports() {
  static PoliticalOwnershipPorts ports{
      {default_root_range, default_record_type, default_record_state,
       default_star_metric, default_star_identity, default_ownership_apply,
       default_current_identity, default_current_star, default_current_mode,
       default_record_reference, default_current_star_count,
       default_cleanup_root, default_cleanup_record_word, default_cleanup_list},
      {default_message_service, default_message_root, default_message_state,
       default_message_contains, default_message_insert},
      {default_persistence_lookup, default_persistence_append}};
  return ports;
}

extern "C" void PKG13_E4_CDECL
PoliticalOwnershipScan_00c8d060(OpaqueRecord* record) {
  PoliticalOwnershipPorts& ports = political_ownership_ports();
  StarOwnershipPorts& ownership = ports.ownership;
  OpaqueRecordRange* const roots = ownership.root_range(record);
  if (roots == nullptr) {
    return;
  }
  const std::int32_t root_count = static_cast<std::int32_t>(
      (reinterpret_cast<std::uintptr_t>(roots->end) -
       reinterpret_cast<std::uintptr_t>(roots->begin)) >>
      2);
  std::int32_t common_identity = -1;

  for (std::int32_t root_index = 0; root_index < root_count; ++root_index) {
    OpaqueRecord* const candidate = roots->begin[root_index];
    if (ownership.record_type(candidate) != 5u || candidate->field_28 == 1u ||
        candidate->field_28 == 0u || ownership.record_state(candidate) != 0u) {
      continue;
    }
    const std::int32_t candidate_count = static_cast<std::int32_t>(
        (reinterpret_cast<std::uintptr_t>(candidate->field_160) -
         reinterpret_cast<std::uintptr_t>(candidate->field_15c)) >>
        2);
    if (candidate_count == 0) {
      return;
    }
    for (std::int32_t child_index = 0; child_index < candidate_count;
         ++child_index) {
      OpaqueOwnershipChild* const child = candidate->field_15c[child_index];
      const std::int32_t child_count = static_cast<std::int32_t>(
          (reinterpret_cast<std::uintptr_t>(child->end) -
           reinterpret_cast<std::uintptr_t>(child->begin)) >>
          2);
      if (child_count == 0) {
        return;
      }
      for (std::int32_t item_index = 0; item_index < child_count;
           ++item_index) {
        OpaqueRecord* const item = child->begin[item_index];
        if (ownership.star_metric(item) < 100.0f) {
          return;
        }
        if (common_identity == -1) {
          common_identity =
              static_cast<std::int32_t>(ownership.star_identity(item));
        }
        if (static_cast<std::int32_t>(ownership.star_identity(item)) !=
            common_identity) {
          return;
        }
      }
    }
  }

  if (common_identity == -1) {
    return;
  }

  const OpaqueWord current_identity = ownership.current_identity();
  if (static_cast<std::int32_t>(current_identity) != common_identity) {
    ownership.ownership_apply(record, common_identity);
    OpaqueRecord* const current_star = ownership.current_star();
    if (ownership.current_mode() != 0u ||
        ownership.record_type(current_star) != 5u ||
        ownership.record_reference(current_star) !=
            reinterpret_cast<OpaqueWord>(record)) {
      return;
    }
    const std::int32_t count = ownership.current_star_count(current_star);
    if (count <= 0) {
      return;
    }
    for (std::int32_t index = 0; index < count; ++index) {
      OpaqueRecord* const root = ownership.cleanup_root();
      const OpaqueWord value = ownership.cleanup_record_word(root);
      ownership.cleanup_list(value);
    }
    return;
  }

  OpaqueRecord* const current_star = ownership.current_star();
  if (current_star == nullptr) {
    return;
  }
  MessagePorts& messages = ports.messages;
  OpaqueMessageService* service = messages.service();
  OpaqueWord value = 0u;
  if (service != nullptr) {
    value = service->vtable->slot_20(service);
  }
  service = messages.service();
  if (service != nullptr) {
    service->vtable->slot_38(service, 0x03475365u);
    service->vtable->slot_40(service, 0x3475381u, 0xef7f5479u);
    service->vtable->slot_40(service, 0x3475385u, value);
    service->vtable->slot_58(service);
  }
  OpaqueMessageRoot* const message_root = messages.root();
  OpaqueMessageState* const state = messages.state(message_root);
  if (state == nullptr || messages.contains(state, 0x6627823u)) {
    return;
  }
  messages.insert(state, 0x6627823u);
  OpaquePersistenceTarget* const persistence =
      ports.persistence.lookup(0xee98e353u);
  ports.persistence.append(persistence, 0xee98e353u);
}

}
