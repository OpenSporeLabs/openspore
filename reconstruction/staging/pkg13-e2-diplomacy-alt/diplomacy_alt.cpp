#include "diplomacy_alt.hpp"

namespace openspore::reconstruction::pkg13_e2_diplomacy_alt {

namespace {

OpaqueRelationshipPolicy* PKG13_E2_CDECL default_policy_resolver(OpaqueWord,
                                                                 OpaqueWord,
                                                                 OpaqueWord) {
  return nullptr;
}

OpaqueWord PKG13_E2_THISCALL default_relationship_stage(
    OpaqueRelationshipPolicy*, OpaqueWord, OpaqueWord, OpaqueWord) {
  return 0u;
}

float PKG13_E2_THISCALL default_raw_relationship_score(
    OpaqueRelationshipPolicy*, OpaqueWord, OpaqueWord, OpaqueWord) {
  return 0.0f;
}

}

DiplomacyAltPorts& diplomacy_alt_ports() {
  static DiplomacyAltPorts ports{default_policy_resolver,
                                 default_relationship_stage,
                                 default_raw_relationship_score};
  return ports;
}

extern "C" float PKG13_E2_CDECL
RelationshipScoreBand_00d00d00(OpaqueWord source, OpaqueWord target) {
  DiplomacyAltPorts& ports = diplomacy_alt_ports();
  OpaqueRelationshipPolicy* policy = ports.policy_resolver(source, target, 1u);
  OpaqueWord stage = ports.relationship_stage(policy, source, target, 1u);
  switch (stage) {
    case 0u:
      return 10.0f;
    case 1u:
      return 30.0f;
    case 2u:
      return 50.0f;
    case 3u:
      return 80.0f;
    case 4u:
    default:
      return 100.0f;
  }
}

extern "C" float PKG13_E2_THISCALL RelationshipScoreObjects_00d00d60(
    OpaqueRelationshipPolicy* policy, OpaqueIdentityObject* first,
    OpaqueIdentityObject* second, OpaqueWord mode) {
  if (first == nullptr || second == nullptr) {
    return 0.0f;
  }
  DiplomacyAltPorts& ports = diplomacy_alt_ports();
  OpaqueWord source = first->vtable->slots[19](first);
  OpaqueWord target = second->vtable->slots[19](second);
  return ports.raw_relationship_score(policy, source, target, mode);
}

}
