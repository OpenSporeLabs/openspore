#include <cstdlib>
#include <initializer_list>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "diplomacy_alt.hpp"

namespace openspore::reconstruction::pkg13_e2_diplomacy_alt {

struct OpaqueRelationshipPolicy {};

namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::vector<std::string> trace;
std::vector<OpaqueWord> relationship_state;
std::vector<std::string> domain_events;
OpaqueRelationshipPolicy policy;
OpaqueRelationshipPolicy* policy_result = &policy;
OpaqueWord policy_source = 0u;
OpaqueWord policy_target = 0u;
OpaqueWord policy_mode = 0u;
OpaqueWord stage_result = 0u;
OpaqueRelationshipPolicy* stage_receiver = nullptr;
OpaqueWord stage_source = 0u;
OpaqueWord stage_target = 0u;
OpaqueWord stage_mode = 0u;
OpaqueWord first_identity = 0u;
OpaqueWord second_identity = 0u;
OpaqueWord first_identity_calls = 0u;
OpaqueWord second_identity_calls = 0u;
float raw_score_result = 0.0f;
OpaqueRelationshipPolicy* raw_score_receiver = nullptr;
OpaqueWord raw_score_source = 0u;
OpaqueWord raw_score_target = 0u;
OpaqueWord raw_score_mode = 0u;
OpaqueIdentityVtable first_vtable{};
OpaqueIdentityVtable second_vtable{};
OpaqueIdentityObject first{&first_vtable};
OpaqueIdentityObject second{&second_vtable};

OpaqueRelationshipPolicy* PKG13_E2_CDECL
model_policy_resolver(OpaqueWord source, OpaqueWord target, OpaqueWord mode) {
  trace.emplace_back("policy");
  policy_source = source;
  policy_target = target;
  policy_mode = mode;
  return policy_result;
}

OpaqueWord PKG13_E2_THISCALL
model_relationship_stage(OpaqueRelationshipPolicy* receiver, OpaqueWord source,
                         OpaqueWord target, OpaqueWord mode) {
  trace.emplace_back("stage");
  stage_receiver = receiver;
  stage_source = source;
  stage_target = target;
  stage_mode = mode;
  return stage_result;
}

float PKG13_E2_THISCALL model_raw_relationship_score(
    OpaqueRelationshipPolicy* receiver, OpaqueWord source, OpaqueWord target,
    OpaqueWord mode) {
  trace.emplace_back("score");
  raw_score_receiver = receiver;
  raw_score_source = source;
  raw_score_target = target;
  raw_score_mode = mode;
  return raw_score_result;
}

OpaqueWord PKG13_E2_THISCALL
model_first_identity(OpaqueIdentityObject* object) {
  check(object == &first);
  ++first_identity_calls;
  trace.emplace_back("first-identity");
  return first_identity;
}

OpaqueWord PKG13_E2_THISCALL
model_second_identity(OpaqueIdentityObject* object) {
  check(object == &second);
  ++second_identity_calls;
  trace.emplace_back("second-identity");
  return second_identity;
}

void reset_model() {
  trace.clear();
  relationship_state = {4u, 7u, 11u};
  domain_events.clear();
  policy_result = &policy;
  policy_source = 0u;
  policy_target = 0u;
  policy_mode = 0u;
  stage_result = 0u;
  stage_receiver = nullptr;
  stage_source = 0u;
  stage_target = 0u;
  stage_mode = 0u;
  first_identity = 0u;
  second_identity = 0u;
  first_identity_calls = 0u;
  second_identity_calls = 0u;
  raw_score_result = 0.0f;
  raw_score_receiver = nullptr;
  raw_score_source = 0u;
  raw_score_target = 0u;
  raw_score_mode = 0u;
  first_vtable.slots.fill(nullptr);
  second_vtable.slots.fill(nullptr);
  first_vtable.slots[19] = model_first_identity;
  second_vtable.slots[19] = model_second_identity;
}

void install_ports() {
  DiplomacyAltPorts& ports = diplomacy_alt_ports();
  ports.policy_resolver = model_policy_resolver;
  ports.relationship_stage = model_relationship_stage;
  ports.raw_relationship_score = model_raw_relationship_score;
}

void expect_trace(std::initializer_list<const char*> expected) {
  check(trace.size() == expected.size());
  std::size_t index = 0;
  for (const char* value : expected) {
    check(trace[index] == value);
    ++index;
  }
}

void test_directed_id_bands_and_policy_order() {
  const std::vector<std::pair<OpaqueWord, float>> cases{
      {0u, 10.0f},
      {1u, 30.0f},
      {2u, 50.0f},
      {3u, 80.0f},
      {4u, 100.0f},
      {5u, 100.0f},
      {std::numeric_limits<OpaqueWord>::max(), 100.0f}};

  for (const auto& item : cases) {
    reset_model();
    install_ports();
    stage_result = item.first;

    check(RelationshipScoreBand_00d00d00(10u, 20u) == item.second);
    check(policy_source == 10u);
    check(policy_target == 20u);
    check(policy_mode == 1u);
    check(stage_receiver == &policy);
    check(stage_source == 10u);
    check(stage_target == 20u);
    check(stage_mode == 1u);
    expect_trace({"policy", "stage"});

    check(RelationshipScoreBand_00d00d00(20u, 10u) == item.second);
    check(policy_source == 20u);
    check(policy_target == 10u);
    check(stage_source == 20u);
    check(stage_target == 10u);
  }

  check(relationship_state == std::vector<OpaqueWord>({4u, 7u, 11u}));
  check(domain_events.empty());
}

void test_sentinel_ids_and_null_policy_reach_classifier() {
  struct Case {
    OpaqueWord source;
    OpaqueWord target;
  };
  const std::vector<Case> cases{{std::numeric_limits<OpaqueWord>::max(), 0u},
                                {0u, std::numeric_limits<OpaqueWord>::max()}};

  for (const auto& item : cases) {
    reset_model();
    install_ports();
    stage_result = 3u;

    check(RelationshipScoreBand_00d00d00(item.source, item.target) == 80.0f);
    check(policy_source == item.source);
    check(policy_target == item.target);
    check(stage_source == item.source);
    check(stage_target == item.target);
  }

  reset_model();
  install_ports();
  policy_result = nullptr;
  stage_result = 4u;
  check(RelationshipScoreBand_00d00d00(1u, 2u) == 100.0f);
  check(stage_receiver == nullptr);
  expect_trace({"policy", "stage"});

  check(relationship_state == std::vector<OpaqueWord>({4u, 7u, 11u}));
  check(domain_events.empty());
}

void test_object_null_paths_skip_virtual_dispatch() {
  reset_model();
  install_ports();
  raw_score_result = 9.0f;

  check(RelationshipScoreObjects_00d00d60(&policy, nullptr, &second, 1u) ==
        0.0f);
  check(RelationshipScoreObjects_00d00d60(&policy, &first, nullptr, 1u) ==
        0.0f);
  check(RelationshipScoreObjects_00d00d60(&policy, nullptr, nullptr, 1u) ==
        0.0f);
  check(trace.empty());
  check(first_identity_calls == 0u);
  check(second_identity_calls == 0u);
  check(relationship_state == std::vector<OpaqueWord>({4u, 7u, 11u}));
  check(domain_events.empty());
}

void test_object_virtual_identity_direction_and_score_order() {
  reset_model();
  install_ports();
  first_identity = 10u;
  second_identity = 20u;
  raw_score_result = -7.5f;

  check(RelationshipScoreObjects_00d00d60(&policy, &first, &second, 1u) ==
        -7.5f);
  expect_trace({"first-identity", "second-identity", "score"});
  check(first_identity_calls == 1u);
  check(second_identity_calls == 1u);
  check(raw_score_receiver == &policy);
  check(raw_score_source == 10u);
  check(raw_score_target == 20u);
  check(raw_score_mode == 1u);

  check(RelationshipScoreObjects_00d00d60(&policy, &second, &first, 2u) ==
        -7.5f);
  check(raw_score_source == 20u);
  check(raw_score_target == 10u);
  check(raw_score_mode == 2u);

  check(RelationshipScoreObjects_00d00d60(&policy, &first, &first, 3u) ==
        -7.5f);
  check(first_identity_calls == 4u);
  check(raw_score_source == 10u);
  check(raw_score_target == 10u);
  check(raw_score_mode == 3u);

  check(relationship_state == std::vector<OpaqueWord>({4u, 7u, 11u}));
  check(domain_events.empty());
}

void test_object_invalid_ids_are_not_rejected() {
  reset_model();
  install_ports();
  first_identity = std::numeric_limits<OpaqueWord>::max();
  second_identity = 0u;
  raw_score_result = 4.25f;

  check(RelationshipScoreObjects_00d00d60(&policy, &first, &second, 1u) ==
        4.25f);
  check(raw_score_source == std::numeric_limits<OpaqueWord>::max());
  check(raw_score_target == 0u);
  expect_trace({"first-identity", "second-identity", "score"});

  check(RelationshipScoreObjects_00d00d60(&policy, &second, &first, 1u) ==
        4.25f);
  check(raw_score_source == 0u);
  check(raw_score_target == std::numeric_limits<OpaqueWord>::max());

  check(relationship_state == std::vector<OpaqueWord>({4u, 7u, 11u}));
  check(domain_events.empty());
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg13_e2_diplomacy_alt;
  test_directed_id_bands_and_policy_order();
  test_sentinel_ids_and_null_policy_reach_classifier();
  test_object_null_paths_skip_virtual_dispatch();
  test_object_virtual_identity_direction_and_score_order();
  test_object_invalid_ids_are_not_rejected();
}
