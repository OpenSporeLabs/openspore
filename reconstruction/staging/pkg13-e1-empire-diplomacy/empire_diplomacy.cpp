#include "empire_diplomacy.hpp"

#include <cmath>
#include <limits>

namespace openspore::reconstruction::pkg13_e1_empire_diplomacy {
namespace {

constexpr OpaqueWord kRuntimeModeApp = 0x01654c02u;
constexpr OpaqueWord kRuntimeModeLocal = 0x01654c05u;
constexpr OpaqueWord kDefaultEventBase = 0x4e5855b9u;
constexpr OpaqueWord kPropertyObjectId = 0x5c770db7u;
constexpr OpaqueWord kPropertyIds[4] = {0x01d379fau, 0x01d37be0u,
                                       0x01d37a06u, 0x01d37a0cu};
constexpr std::uint16_t kFloatPropertyType = 13u;
constexpr OpaqueWord kRelationshipChangeEvent = 0x05fa2448u;
constexpr float kMinimumRetainedModifier = 0.01f;

float PKG13_E1_THISCALL default_relationship_score(
    OpaqueRelationshipPolicy*, OpaqueWord, OpaqueWord, OpaqueWord) {
  return 0.0f;
}

std::int32_t PKG13_E1_FASTCALL default_relationship_stage(
    OpaqueDirectedEmpire*) {
  return 0;
}

OpaqueRoot* default_noun_root() { return nullptr; }

OpaqueRoot* PKG13_E1_THISCALL default_root_followup(OpaqueRoot*) {
  return nullptr;
}

std::int32_t PKG13_E1_FASTCALL default_root_stage(OpaqueRoot*) { return 0; }

OpaqueDirectedEmpire* PKG13_E1_CDECL default_resolve_current_empire(
    OpaqueRoot* fallback) {
  return reinterpret_cast<OpaqueDirectedEmpire*>(fallback);
}

OpaqueWord PKG13_E1_THISCALL default_directed_identity(
    OpaqueDirectedEmpire*) {
  return 0u;
}

OpaqueWord PKG13_E1_THISCALL default_relationship_classifier(
    OpaqueRelationshipPolicy* policy, OpaqueWord source, OpaqueWord target,
    OpaqueWord mode) {
  return RelationshipClassify_00d00a70(policy, source, target, mode);
}

Opaque* PKG13_E1_CDECL default_property_service() { return nullptr; }

std::uint8_t PKG13_E1_THISCALL default_property_object(
    Opaque*, OpaqueWord, OpaquePropertyValue**) {
  return 0u;
}

std::uint8_t PKG13_E1_THISCALL default_property_read(
    OpaquePropertyValue*, OpaqueWord, OpaqueFloatProperty**) {
  return 0u;
}

const float* PKG13_E1_CDECL default_property_number() { return nullptr; }

void PKG13_E1_THISCALL default_property_release(OpaquePropertyValue*) {}

OpaqueRelationshipEntry* PKG13_E1_STDCALL default_relationship_lookup(
    OpaqueRelationshipPairMap*, OpaqueWord, OpaqueWord) {
  return nullptr;
}

OpaqueRelationshipEntry* PKG13_E1_THISCALL default_relationship_ensure(
    OpaqueRelationshipManager*, OpaqueRelationshipPairMap*, OpaqueWord,
    OpaqueWord) {
  static OpaqueRelationshipEntry entry{};
  return &entry;
}

OpaqueWord PKG13_E1_CDECL default_runtime_mode() { return 0u; }

OpaqueStarManager* PKG13_E1_CDECL default_star_manager() { return nullptr; }

OpaqueStar* PKG13_E1_CDECL default_star_lookup(OpaqueStarManager*, OpaqueWord) {
  return nullptr;
}

OpaqueWord PKG13_E1_CDECL default_star_key(OpaqueStarManager*) { return 0u; }

OpaqueEventProfile* PKG13_E1_THISCALL default_event_profile(
    OpaqueRelationshipManager*, OpaqueEventKey*) {
  return nullptr;
}

OpaqueRelationshipEventNode* PKG13_E1_CDECL default_event_lower_bound(
    OpaqueRelationshipEventMap* map, OpaqueWord key) {
  OpaqueRelationshipEventNode* candidate = map->anchor;
  OpaqueRelationshipEventNode* node = map->root;
  while (node != nullptr) {
    if (node->key < key) {
      node = node->left;
    } else {
      candidate = node;
      node = node->right;
    }
  }
  return candidate;
}

OpaqueRelationshipEventNode* PKG13_E1_THISCALL default_event_insert(
    OpaqueRelationshipEventMap*, OpaqueWord) {
  static OpaqueRelationshipEventNode node{};
  return &node;
}

void PKG13_E1_THISCALL default_event_remove(OpaqueRelationshipEventMap*,
                                            OpaqueRelationshipEventNode*) {}

float PKG13_E1_THISCALL default_relationship_value(
    OpaqueRelationshipManager*, OpaqueRelationshipPairMap*, OpaqueWord,
    OpaqueWord, OpaqueWord, OpaqueEventProfile*) {
  return 0.0f;
}

void PKG13_E1_THISCALL default_reset_relationship(OpaqueWord) {}

void PKG13_E1_THISCALL default_aggregate_relationship(
    OpaqueRelationshipManager*, OpaqueWord, OpaqueWord, OpaqueWord) {}

OpaqueAppSystem* PKG13_E1_CDECL default_app_system() { return nullptr; }

void PKG13_E1_THISCALL default_event_dispatch(OpaqueAppSystem*, OpaqueWord,
                                              OpaqueWord, OpaqueWord) {}

OpaqueWord PKG13_E1_CDECL default_current_player_id() {
  return std::numeric_limits<OpaqueWord>::max();
}

OpaqueDirectedEmpire* PKG13_E1_CDECL default_directed_empire_object(
    OpaqueWord) {
  return nullptr;
}

std::int32_t PKG13_E1_CDECL default_directed_empire_kind(OpaqueWord) {
  return 0;
}

OpaqueMetric* PKG13_E1_CDECL default_metric_owner() { return nullptr; }

float PKG13_E1_THISCALL default_metric_value(OpaqueMetric*) { return 0.0f; }

bool is_relationship_change_modifier(OpaqueWord modifier) {
  switch (modifier) {
    case 0x0526e4e5u:
    case 0x0526e4f2u:
    case 0x0526e4f5u:
    case 0x0526e4f8u:
    case 0x0526e4feu:
    case 0x0526e50au:
    case 0x0526e50eu:
    case 0x0526e512u:
    case 0x05adb0aau:
      return true;
    default:
      return false;
  }
}

}

EmpireDiplomacyPorts& empire_diplomacy_ports() {
  static EmpireDiplomacyPorts ports{default_relationship_score,
                                    default_relationship_stage,
                                    default_noun_root,
                                    default_root_followup,
                                    default_root_stage,
                                    default_resolve_current_empire,
                                    default_directed_identity,
                                    default_relationship_classifier,
                                    default_property_service,
                                    default_property_object,
                                    default_property_read,
                                    default_property_number,
                                    default_property_release,
                                    default_relationship_lookup,
                                    default_relationship_ensure,
                                    default_runtime_mode,
                                    default_star_manager,
                                    default_star_lookup,
                                    default_star_key,
                                    default_event_profile,
                                    default_event_lower_bound,
                                    default_event_insert,
                                    default_event_remove,
                                    default_relationship_value,
                                    default_reset_relationship,
                                    default_aggregate_relationship,
                                    default_app_system,
                                    default_event_dispatch,
                                    default_current_player_id,
                                    default_directed_empire_object,
                                    default_directed_empire_kind,
                                    default_metric_owner,
                                    default_metric_value};
  return ports;
}

extern "C" OpaqueWord PKG13_E1_THISCALL RelationshipClassify_00d00a70(
    OpaqueRelationshipPolicy* policy, OpaqueWord source, OpaqueWord target,
    OpaqueWord mode) {
  float value = empire_diplomacy_ports().relationship_score(
      policy, source, target, mode);
  if (!(value >= -10.0f)) {
    value = -10.0f;
  }
  if (value >= 10.0f) {
    value = 10.0f;
  }
  if (policy->second < value && value < policy->third) {
    return 2u;
  }
  if (policy->third <= value && value < policy->fourth) {
    return 3u;
  }
  if (policy->fourth <= value) {
    return 4u;
  }
  if (value <= policy->second && policy->first <= value &&
      value != policy->first) {
    return 1u;
  }
  return 0u;
}

extern "C" float PKG13_E1_STDCALL RelationshipOwnerAdjustment_00d00b40(
    OpaqueWord source, OpaqueDirectedEmpire* target) {
  EmpireDiplomacyPorts& ports = empire_diplomacy_ports();
  float value = 0.0f;
  if (target->relationship_owner_id == source) {
    switch (ports.relationship_stage(target)) {
      case 0:
        value = -4.0f;
        break;
      case 1:
        value = -2.0f;
        break;
      case 2:
        value = -3.0f;
        break;
      default:
        break;
    }
  }
  if (target->relationship_gate != 0u) {
    OpaqueRoot* root = ports.noun_root();
    int stage = ports.root_stage(ports.root_followup(root));
    if (stage >= 2) {
      value *= 2.0f;
    } else {
      stage = ports.root_stage(ports.root_followup(root));
      if (stage >= 1) {
        value *= 1.5f;
      }
    }
  }
  return value;
}

extern "C" void PKG13_E1_FASTCALL RelationshipLoadThresholds_00d00db0(
    OpaqueRelationshipManager* manager) {
  EmpireDiplomacyPorts& ports = empire_diplomacy_ports();
  OpaquePropertyValue* object = nullptr;
  if (ports.property_object(ports.property_service(), kPropertyObjectId,
                            &object) == 0u ||
      object == nullptr) {
    if (object != nullptr) {
      ports.property_release(object);
    }
    return;
  }
  for (std::size_t index = 0; index < 4; ++index) {
    OpaqueFloatProperty* property = nullptr;
    if (ports.property_read(object, kPropertyIds[index], &property) != 0u) {
      if (property->type == kFloatPropertyType) {
        manager->thresholds[index] = *ports.property_number();
      }
    }
  }
  ports.property_release(object);
}

extern "C" float PKG13_E1_THISCALL DirectedEmpirePenalty_00d00ee0(
    OpaqueDirectedEmpire* first, OpaqueDirectedEmpire* second) {
  if (first->relationship_gate != 0u || second->relationship_gate != 0u) {
    return 0.0f;
  }
  EmpireDiplomacyPorts& ports = empire_diplomacy_ports();
  OpaqueDirectedEmpire* current =
      ports.resolve_current_empire(ports.noun_root());
  if (current == nullptr) {
    return 0.0f;
  }
  OpaqueWord current_identity = ports.directed_identity(current);
  OpaqueWord first_identity = ports.directed_identity(first);
  if (ports.relationship_classifier(
          reinterpret_cast<OpaqueRelationshipPolicy*>(first), current_identity,
          first_identity, 1u) < 4u) {
    return 0.0f;
  }
  OpaqueWord second_identity = ports.directed_identity(second);
  if (ports.relationship_classifier(
          reinterpret_cast<OpaqueRelationshipPolicy*>(first), current_identity,
          second_identity, 1u) <= 1u) {
    return -10.0f;
  }
  return 0.0f;
}

extern "C" void PKG13_E1_THISCALL RelationshipMapLowerBound_00d00f80(
    OpaqueRelationshipPairMap* map, OpaqueRelationshipPairNode** output,
    OpaqueRelationshipPairNode* key) {
  OpaqueRelationshipPairNode* candidate = map->anchor;
  OpaqueRelationshipPairNode* node = map->root;
  while (node != nullptr) {
    const bool key_before =
        key->key_a < node->key_a ||
        (key->key_a == node->key_a && key->key_b < node->key_b);
    if (key_before) {
      candidate = node;
      node = node->right;
    } else {
      node = node->left;
    }
  }
  const bool found = candidate != map->anchor &&
                     (candidate->key_a < key->key_a ||
                      (candidate->key_a == key->key_a &&
                       candidate->key_b <= key->key_b));
  *output = found ? candidate : map->anchor;
}

extern "C" float PKG13_E1_THISCALL RelationshipApply_00d05d90(
    OpaqueRelationshipManager* manager, OpaqueRelationshipPairMap* map,
    OpaqueWord source, OpaqueWord target, OpaqueWord modifier, float delta) {
  if (delta == 0.0f) {
    return 0.0f;
  }
  EmpireDiplomacyPorts& ports = empire_diplomacy_ports();
  OpaqueRelationshipEntry* entry =
      ports.relationship_lookup(map, source, target);
  if (entry == nullptr) {
    entry = ports.relationship_ensure(manager, map, source, target);
  }
  OpaqueWord mode = ports.runtime_mode();
  OpaqueWord event_base = kDefaultEventBase;
  if (mode == kRuntimeModeLocal) {
    OpaqueStarManager* star_manager = ports.star_manager();
    if (ports.star_lookup(star_manager, source) != nullptr) {
      event_base = ports.star_key(star_manager);
    }
  }
  if (mode == kRuntimeModeApp) {
    entry->value = std::numeric_limits<float>::max();
    ports.reset_relationship(source);
  }
  OpaqueEventKey event_key{event_base, modifier};
  OpaqueEventProfile* profile = ports.event_profile(manager, &event_key);
  const float before = ports.relationship_value(manager, map, source, target,
                                                modifier, profile);
  OpaqueRelationshipEventNode* node =
      ports.event_lower_bound(&entry->events, modifier);
  if (node == entry->events.anchor) {
    node = ports.event_insert(&entry->events, modifier);
    node->value = delta;
  } else {
    node->value += delta;
    if (std::fabs(node->value) < kMinimumRetainedModifier) {
      ports.event_remove(&entry->events, node);
    }
  }
  const float after = ports.relationship_value(manager, map, source, target,
                                               modifier, profile);
  if (mode == kRuntimeModeLocal && source != target &&
      target == ports.current_player_id() &&
      ports.directed_empire_kind(source) == 5) {
    OpaqueMetric* metric = ports.metric_owner();
    if (ports.metric_value(metric) >= 1.0f) {
      OpaqueAppSystem* service = ports.app_system();
      ports.event_dispatch(service, kRelationshipChangeEvent, 0u, 0u);
    }
  }
  if (is_relationship_change_modifier(modifier)) {
    OpaqueDirectedEmpire* source_object =
        ports.directed_empire_object(source);
    OpaqueDirectedEmpire* target_object =
        ports.directed_empire_object(target);
    if (source_object != nullptr && target_object != nullptr) {
      ports.aggregate_relationship(manager, source, target, 0u);
    }
  }
  if (mode == kRuntimeModeApp) {
    ports.aggregate_relationship(manager, source, target, 0u);
  }
  return after - before;
}

}
