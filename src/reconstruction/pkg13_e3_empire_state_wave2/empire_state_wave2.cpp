#include "empire_state_wave2.hpp"

namespace openspore::reconstruction::pkg13_e3_empire_state_wave2 {

namespace {

constexpr OpaqueWord kDefaultRelationshipId = 0x4e5855b9u;
constexpr OpaqueWord kRelationshipMatrix[19][3] = {
    {0xacb9635du, 0x4fede4a6u, 0xed2bbcc8u},
    {0x04a83b77u, 0x250f78b4u, 0x12486202u},
    {0x5d054a25u, 0x076b1a6eu, 0x8aa5a470u},
    {0xdf83b46du, 0xb308c5d6u, 0x21d2a5b8u},
    {0x59878688u, 0xacd3a4cfu, 0xf9b2cbadu},
    {0xb8196164u, 0x62166b9bu, 0x01100719u},
    {0xe80abf05u, 0x901a654eu, 0x18271550u},
    {0x401c6160u, 0x86a04027u, 0x3001d0a5u},
    {0x25885eafu, 0x7e56d6ccu, 0x87d7829au},
    {0xacb9635du, 0x4fede4a6u, 0xed2bbcc8u},
    {0x04a83b77u, 0x250f78b4u, 0x12486202u},
    {0x5d054a25u, 0x076b1a6eu, 0x8aa5a470u},
    {0xdf83b46du, 0xb308c5d6u, 0x21d2a5b8u},
    {0x59878688u, 0xacd3a4cfu, 0xf9b2cbadu},
    {0xb8196164u, 0x62166b9bu, 0x01100719u},
    {0xe80abf05u, 0x901a654eu, 0x18271550u},
    {0x401c6160u, 0x86a04027u, 0x3001d0a5u},
    {0xe80abf05u, 0x901a654eu, 0x18271550u},
    {0xacb9635du, 0x4fede4a6u, 0xed2bbcc8u}};

constexpr OpaqueWord kLocalFirst = 0x01667bacu;
constexpr OpaqueWord kLocalSecond = 0x01667bacu;
constexpr OpaqueWord kLocalThird = 0x01667baeu;

OpaqueCurrentEmpire* PKG13_E3_CDECL default_current_empire() { return nullptr; }

OpaqueMetricValue* PKG13_E3_THISCALL
default_metric_source(OpaqueEmpireMetricState*) {
  return nullptr;
}

OpaqueMetricContext* PKG13_E3_CDECL default_metric_context() { return nullptr; }

float PKG13_E3_THISCALL default_metric_value(OpaqueMetricContext*,
                                             OpaqueMetricValue*) {
  return 0.0f;
}

void PKG13_E3_THISCALL default_profile_prepare(OpaqueProfile*, OpaqueWord*) {}

OpaqueStarManager* PKG13_E3_CDECL default_star_manager() { return nullptr; }

void PKG13_E3_THISCALL default_record_to_planet(OpaqueStarManager*,
                                                OpaqueLocalRecord*) {}

void PKG13_E3_THISCALL default_profile_apply(OpaqueSpeciesProfile*,
                                             OpaqueLocalRecord*) {}

void PKG13_E3_THISCALL default_vector_color(OpaqueVectorElement*, OpaqueWord*) {
}

void PKG13_E3_THISCALL default_name_state(OpaqueProfileNameState*,
                                          OpaqueLocalRecord*) {}

void PKG13_E3_THISCALL default_name_assign(OpaqueText*, OpaqueTextWord*,
                                           OpaqueTextWord*) {}

void PKG13_E3_CDECL default_record_cleanup(OpaqueLocalRecord*) {}

void cleanup_if_needed(OpaqueLocalRecord* record,
                       const RecordCleanupPort& cleanup) {
  const OpaqueWord distance = record->third - record->first;
  if ((distance & 0xfffffffeu) > 2u && record->first != 0u) {
    cleanup(record);
  }
}

}

EmpireStatePorts& empire_state_ports() {
  static EmpireStatePorts ports{
      default_current_empire,   default_metric_source,
      default_metric_context,   default_metric_value,
      default_profile_prepare,  default_star_manager,
      default_record_to_planet, default_profile_apply,
      default_vector_color,     default_name_state,
      default_name_assign,      default_record_cleanup};
  return ports;
}

extern "C" OpaqueWord PKG13_E3_CDECL
SpeciesProfileSelector_00c30cc0(OpaqueWord archetype, OpaqueWord difficulty) {
  OpaqueWord default_result = kDefaultRelationshipId;
  if (archetype > 18u) {
    return default_result;
  }
  if (archetype == 8u) {
    __asm__ volatile(
        "pushl %[difficulty]\n\t"
        "pushl %[archetype]\n\t"
        "movl %[default_result], %%eax\n\t"
        "call ArchetypeRelationshipsID_00c30e20\n\t"
        "addl $8, %%esp"
        : "=a"(default_result)
        : [archetype] "r"(archetype), [difficulty] "r"(difficulty),
          [default_result] "i"(kDefaultRelationshipId)
        : "cc", "ecx", "memory");
    return default_result;
  }
  if (difficulty > 2u) {
    return default_result;
  }
  return kRelationshipMatrix[archetype][difficulty];
}

extern "C" float PKG13_E3_THISCALL
HomeWorldMetricLazy_00c31890(OpaqueEmpireMetricState* state) {
  const float cached = state->home_world_metric;
  if (cached > 0.0f || cached != cached) {
    return cached;
  }
  EmpireStatePorts& ports = empire_state_ports();
  OpaqueMetricValue* source = ports.metric_source(state);
  OpaqueMetricContext* context = ports.metric_context();
  const float result = ports.metric_value(context, source);
  state->home_world_metric = result;
  return result;
}

extern "C" void PKG13_E3_THISCALL
ProfileSetter_00c33690(OpaqueSpeciesProfile* species, OpaqueProfile* profile) {
  EmpireStatePorts& ports = empire_state_ports();
  const bool is_current = ports.current_empire() ==
                          reinterpret_cast<const OpaqueCurrentEmpire*>(species);
  OpaqueLocalRecord first_record;

  if (is_current && profile != nullptr) {
    first_record = OpaqueLocalRecord{kLocalFirst, kLocalSecond, kLocalThird};
    ports.profile_prepare(profile,
                          reinterpret_cast<OpaqueWord*>(&first_record));
    OpaqueStarManager* manager = ports.star_manager();
    ports.record_to_planet(manager, &first_record);
    cleanup_if_needed(&first_record, ports.record_cleanup);
  }

  OpaqueWord color[3]{};
  if (profile != nullptr) {
    color[0] = profile->color[0];
    color[1] = profile->color[1];
    color[2] = profile->color[2];
  }

  const std::uintptr_t begin_address =
      reinterpret_cast<std::uintptr_t>(species->vector_begin);
  const std::uintptr_t end_address =
      reinterpret_cast<std::uintptr_t>(species->vector_end);
  const std::uint32_t byte_difference =
      static_cast<std::uint32_t>(end_address - begin_address);
  std::int32_t count = static_cast<std::int32_t>(byte_difference);
  count >>= 2;
  for (std::int32_t index = 0; index < count; ++index) {
    OpaqueVectorElement* element = species->vector_begin[index];
    ports.vector_color(element, color);
  }

  if (profile != nullptr) {
    ports.profile_apply(species, &first_record);
    OpaqueLocalRecord second_record{kLocalFirst, kLocalSecond, kLocalThird};
    ports.profile_prepare(profile,
                          reinterpret_cast<OpaqueWord*>(&second_record));
    ports.name_state(&species->name_state, &second_record);

    OpaqueNameNode* node = species->name_state.leaf;
    OpaqueNameNode* root = species->name_state.root;
    OpaqueNameNode* selected = root;
    while (node != nullptr) {
      if (node->rank < 2u) {
        node = node->left;
      } else {
        selected = node;
        node = node->right;
      }
    }
    if (selected == root || selected->rank <= 2u) {
      selected = root;
    }
    OpaqueTextWord* start = selected->name;
    OpaqueTextWord* cursor = start;
    while (*cursor != 0u) {
      ++cursor;
    }
    const std::ptrdiff_t length = cursor - start;
    ports.name_assign(&species->name, start, start + length);
    cleanup_if_needed(&second_record, ports.record_cleanup);
  }
}

}
