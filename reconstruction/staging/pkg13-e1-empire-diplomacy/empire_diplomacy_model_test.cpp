#include "empire_diplomacy.hpp"

#include <cassert>
#include <cmath>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_FASTCALL __fastcall
#define TEST_STDCALL __stdcall
#define TEST_CDECL __cdecl
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_FASTCALL __attribute__((fastcall))
#define TEST_STDCALL __attribute__((stdcall))
#define TEST_CDECL __attribute__((cdecl))
#endif

namespace {

using namespace openspore::reconstruction::pkg13_e1_empire_diplomacy;

const EmpireDiplomacyPorts kDefaults = empire_diplomacy_ports();

std::vector<std::string> trace;
OpaqueRelationshipPolicy policy{};
OpaqueDirectedEmpire first{};
OpaqueDirectedEmpire second{};
OpaqueDirectedEmpire current{};
OpaqueRelationshipManager manager{};
OpaqueRelationshipPairMap relationship_map{};
OpaqueRelationshipEntry entry{};
OpaqueRelationshipEventNode existing_node{};
OpaqueRelationshipEventNode inserted_node{};
OpaqueRelationshipPairNode pair_left{};
OpaqueRelationshipPairNode pair_root{};
OpaqueRelationshipPairNode pair_right{};
OpaquePropertyValue property_object{};
OpaqueFloatProperty properties[4]{};
float property_numbers[4]{};
std::size_t property_number_index = 0;
OpaqueWord property_result_mask = 0xfu;
float score_result = 0.0f;
OpaqueWord score_result_source = 0;
OpaqueWord score_result_target = 0;
OpaqueWord score_result_mode = 0;
std::int32_t stage_result = 0;
std::vector<std::int32_t> root_stage_results;
std::size_t root_stage_index = 0;
OpaqueWord current_identity = 0;
OpaqueWord first_identity = 0;
OpaqueWord second_identity = 0;
OpaqueWord classifier_results[2]{};
std::size_t classifier_index = 0;
Opaque* service_result = nullptr;
OpaquePropertyValue* property_object_result = &property_object;
bool property_object_success = true;
OpaqueRelationshipEntry* lookup_result = &entry;
OpaqueWord runtime_mode = 0;
OpaqueStarManager* selected_star = nullptr;
OpaqueStar* star_result = reinterpret_cast<OpaqueStar*>(1);
OpaqueWord star_key_result = 0;
OpaqueEventProfile profile{};
OpaqueEventProfile* profile_result = &profile;
bool use_existing_event = true;
float relationship_values[2]{};
std::size_t relationship_value_index = 0;
OpaqueWord current_player_result = 0;
OpaqueWord lookup_source = 0;
OpaqueWord lookup_target = 0;
OpaqueWord lookup_modifier = 0;
OpaqueWord profile_base = 0;
std::int32_t empire_kind_result = 0;
OpaqueMetric* metric_result = reinterpret_cast<OpaqueMetric*>(1);
float metric_result_value = 0.0f;
OpaqueDirectedEmpire* object_result = reinterpret_cast<OpaqueDirectedEmpire*>(1);
OpaqueAppSystem* app_result = reinterpret_cast<OpaqueAppSystem*>(1);
std::size_t remove_count = 0;
std::size_t reset_count = 0;
std::size_t aggregate_count = 0;
std::size_t dispatch_count = 0;

void reset_model() {
  empire_diplomacy_ports() = kDefaults;
  trace.clear();
  policy = {};
  first = {};
  second = {};
  current = {};
  manager = {};
  relationship_map = {};
  entry = {};
  existing_node = {};
  inserted_node = {};
  property_object = {};
  properties[0] = {};
  properties[1] = {};
  properties[2] = {};
  properties[3] = {};
  property_numbers[0] = 1.0f;
  property_numbers[1] = 2.0f;
  property_numbers[2] = 3.0f;
  property_numbers[3] = 4.0f;
  property_number_index = 0;
  property_result_mask = 0xfu;
  score_result = 0.0f;
  score_result_source = 0;
  score_result_target = 0;
  score_result_mode = 0;
  stage_result = 0;
  root_stage_results.clear();
  root_stage_index = 0;
  current_identity = 0;
  first_identity = 0;
  second_identity = 0;
  classifier_results[0] = 0;
  classifier_results[1] = 0;
  classifier_index = 0;
  service_result = nullptr;
  property_object_result = &property_object;
  property_object_success = true;
  lookup_result = &entry;
  runtime_mode = 0;
  selected_star = nullptr;
  star_result = reinterpret_cast<OpaqueStar*>(1);
  star_key_result = 0;
  profile_result = &profile;
  use_existing_event = true;
  relationship_values[0] = 0.0f;
  relationship_values[1] = 0.0f;
  relationship_value_index = 0;
  current_player_result = 0;
  lookup_source = 0;
  lookup_target = 0;
  lookup_modifier = 0;
  profile_base = 0;
  empire_kind_result = 0;
  metric_result = reinterpret_cast<OpaqueMetric*>(1);
  metric_result_value = 0.0f;
  object_result = reinterpret_cast<OpaqueDirectedEmpire*>(1);
  app_result = reinterpret_cast<OpaqueAppSystem*>(1);
  remove_count = 0;
  reset_count = 0;
  aggregate_count = 0;
  dispatch_count = 0;
  policy.first = -8.0f;
  policy.second = -2.0f;
  policy.third = 2.0f;
  policy.fourth = 8.0f;
  entry.events.anchor = reinterpret_cast<OpaqueRelationshipEventNode*>(
      reinterpret_cast<unsigned char*>(&entry.events) + 0x04u);
}

void assert_trace(std::initializer_list<const char*> expected) {
  assert(trace.size() == expected.size());
  std::size_t index = 0;
  for (const char* value : expected) {
    assert(trace[index] == value);
    ++index;
  }
}

float TEST_THISCALL model_relationship_score(OpaqueRelationshipPolicy* receiver,
                                             OpaqueWord source, OpaqueWord target,
                                             OpaqueWord mode) {
  assert(receiver == &policy);
  trace.emplace_back("score");
  assert(source == score_result_source);
  assert(target == score_result_target);
  assert(mode == score_result_mode);
  return score_result;
}

std::int32_t TEST_FASTCALL model_relationship_stage(
    OpaqueDirectedEmpire* receiver) {
  trace.emplace_back("stage");
  assert(receiver == &second);
  return stage_result;
}

OpaqueRoot* TEST_CDECL model_noun_root() {
  trace.emplace_back("root");
  return reinterpret_cast<OpaqueRoot*>(1);
}

OpaqueRoot* TEST_THISCALL model_root_followup(OpaqueRoot* receiver) {
  trace.emplace_back("followup");
  assert(receiver == reinterpret_cast<OpaqueRoot*>(1));
  return reinterpret_cast<OpaqueRoot*>(2);
}

std::int32_t TEST_FASTCALL model_root_stage(OpaqueRoot* receiver) {
  assert(receiver == reinterpret_cast<OpaqueRoot*>(2));
  trace.emplace_back("root-stage");
  return root_stage_results[root_stage_index++];
}

OpaqueDirectedEmpire* TEST_CDECL model_resolve_current_empire(
    OpaqueRoot* fallback) {
  trace.emplace_back("resolve-current");
  assert(fallback == reinterpret_cast<OpaqueRoot*>(1));
  return &current;
}

OpaqueWord TEST_THISCALL model_directed_identity(
    OpaqueDirectedEmpire* receiver) {
  trace.emplace_back(receiver == &current ? "identity-current"
                                          : receiver == &first ? "identity-first"
                                                               : "identity-second");
  if (receiver == &current) {
    return current_identity;
  }
  if (receiver == &first) {
    return first_identity;
  }
  assert(receiver == &second);
  return second_identity;
}

OpaqueWord TEST_THISCALL model_relationship_classifier(
    OpaqueRelationshipPolicy* receiver, OpaqueWord source, OpaqueWord target,
    OpaqueWord mode) {
  trace.emplace_back("classify");
  assert(receiver == reinterpret_cast<OpaqueRelationshipPolicy*>(&first));
  assert(source == current_identity);
  assert(mode == 1u);
  if (classifier_index == 0) {
    assert(target == first_identity);
  } else {
    assert(target == second_identity);
  }
  return classifier_results[classifier_index++];
}

Opaque* TEST_CDECL model_property_service() {
  trace.emplace_back("property-service");
  return service_result;
}

std::uint8_t TEST_THISCALL model_property_object(
    Opaque* receiver, OpaqueWord id, OpaquePropertyValue** output) {
  assert(receiver == service_result);
  assert(id == 0x5c770db7u);
  *output = property_object_result;
  trace.emplace_back(property_object_success ? "property-object" : "property-none");
  return property_object_success ? 1u : 0u;
}

OpaqueWord kPropertyId(std::size_t index) {
  static constexpr OpaqueWord ids[4] = {0x01d379fau, 0x01d37be0u,
                                        0x01d37a06u, 0x01d37a0cu};
  return ids[index];
}

std::uint8_t TEST_THISCALL model_property_read(
    OpaquePropertyValue* receiver, OpaqueWord id,
    OpaqueFloatProperty** output) {
  assert(receiver == &property_object);
  trace.emplace_back("property-read-" + std::to_string(id));
  std::size_t index = 0;
  while (index < 4 && kPropertyId(index) != id) {
    ++index;
  }
  assert(index < 4);
  *output = &properties[index];
  return (property_result_mask & (1u << index)) != 0u ? 1u : 0u;
}

const float* TEST_CDECL model_property_number() {
  trace.emplace_back("property-number");
  return &property_numbers[property_number_index++];
}

void TEST_THISCALL model_property_release(OpaquePropertyValue* receiver) {
  assert(receiver == &property_object);
  trace.emplace_back("property-release");
}

OpaqueRelationshipEntry* TEST_STDCALL model_relationship_lookup(
    OpaqueRelationshipPairMap* receiver, OpaqueWord source, OpaqueWord target) {
  assert(receiver == &relationship_map);
  trace.emplace_back("lookup");
  assert(source == lookup_source);
  assert(target == lookup_target);
  return lookup_result;
}

OpaqueRelationshipEntry* TEST_THISCALL model_relationship_ensure(
    OpaqueRelationshipManager* receiver, OpaqueRelationshipPairMap* map,
    OpaqueWord source, OpaqueWord target) {
  assert(receiver == &manager);
  assert(map == &relationship_map);
  trace.emplace_back("ensure");
  assert(source == lookup_source);
  assert(target == lookup_target);
  return &entry;
}

OpaqueWord TEST_CDECL model_runtime_mode() {
  trace.emplace_back("mode");
  return runtime_mode;
}

OpaqueStarManager* TEST_CDECL model_star_manager() {
  trace.emplace_back("star-manager");
  return selected_star;
}

OpaqueStar* TEST_CDECL model_star_lookup(OpaqueStarManager* receiver,
                                         OpaqueWord source) {
  assert(receiver == selected_star);
  trace.emplace_back("star-lookup");
  assert(source == lookup_source);
  return star_result;
}

OpaqueWord TEST_CDECL model_star_key(OpaqueStarManager* receiver) {
  assert(receiver == selected_star);
  trace.emplace_back("star-key");
  return star_key_result;
}

OpaqueEventProfile* TEST_THISCALL model_event_profile(
    OpaqueRelationshipManager* receiver, OpaqueEventKey* key) {
  assert(receiver == &manager);
  trace.emplace_back("profile");
  assert(key->modifier == lookup_modifier);
  profile_base = key->base;
  return profile_result;
}

OpaqueRelationshipEventNode* TEST_CDECL model_event_lower_bound(
    OpaqueRelationshipEventMap* map, OpaqueWord key) {
  assert(map == &entry.events);
  assert(key == lookup_modifier);
  trace.emplace_back("event-lower-bound");
  return use_existing_event ? &existing_node : entry.events.anchor;
}

OpaqueRelationshipEventNode* TEST_THISCALL model_event_insert(
    OpaqueRelationshipEventMap* map, OpaqueWord key) {
  assert(map == &entry.events);
  assert(key == lookup_modifier);
  trace.emplace_back("event-insert");
  inserted_node.key = key;
  return &inserted_node;
}

void TEST_THISCALL model_event_remove(
    OpaqueRelationshipEventMap* map, OpaqueRelationshipEventNode* node) {
  assert(map == &entry.events);
  assert(node == &existing_node);
  ++remove_count;
  trace.emplace_back("event-remove");
}

float TEST_THISCALL model_relationship_value(
    OpaqueRelationshipManager* receiver, OpaqueRelationshipPairMap* map,
    OpaqueWord source, OpaqueWord target, OpaqueWord modifier,
    OpaqueEventProfile* selected_profile) {
  assert(receiver == &manager);
  assert(map == &relationship_map);
  assert(source == lookup_source);
  assert(target == lookup_target);
  assert(modifier == lookup_modifier);
  assert(selected_profile == profile_result);
  trace.emplace_back(relationship_value_index == 0 ? "value-before"
                                                    : "value-after");
  return relationship_values[relationship_value_index++];
}

void TEST_THISCALL model_reset_relationship(OpaqueWord source) {
  assert(source == lookup_source);
  ++reset_count;
  trace.emplace_back("reset");
}

void TEST_THISCALL model_aggregate_relationship(
    OpaqueRelationshipManager* receiver, OpaqueWord source, OpaqueWord target,
    OpaqueWord mode) {
  assert(receiver == &manager);
  assert(source == lookup_source);
  assert(target == lookup_target);
  assert(mode == 0u);
  ++aggregate_count;
  trace.emplace_back("aggregate");
}

OpaqueAppSystem* TEST_CDECL model_app_system() {
  trace.emplace_back("app-system");
  return app_result;
}

void TEST_THISCALL model_event_dispatch(OpaqueAppSystem* receiver,
                                        OpaqueWord event_id, OpaqueWord first,
                                        OpaqueWord second) {
  assert(receiver == app_result);
  assert(event_id == 0x05fa2448u);
  assert(first == 0u);
  assert(second == 0u);
  ++dispatch_count;
  trace.emplace_back("event");
}

OpaqueWord TEST_CDECL model_current_player_id() {
  trace.emplace_back("current-player");
  return current_player_result;
}

OpaqueDirectedEmpire* TEST_CDECL model_directed_empire_object(OpaqueWord source) {
  trace.emplace_back(source == lookup_source ? "object-source" : "object-target");
  return object_result;
}

std::int32_t TEST_CDECL model_directed_empire_kind(OpaqueWord source) {
  assert(source == lookup_source);
  trace.emplace_back("empire-kind");
  return empire_kind_result;
}

OpaqueMetric* TEST_CDECL model_metric_owner() {
  trace.emplace_back("metric-owner");
  return metric_result;
}

float TEST_THISCALL model_metric_value(OpaqueMetric* receiver) {
  assert(receiver == metric_result);
  trace.emplace_back("metric-value");
  return metric_result_value;
}

void install_relationship_ports() {
  EmpireDiplomacyPorts& ports = empire_diplomacy_ports();
  ports.relationship_score = model_relationship_score;
  ports.relationship_stage = model_relationship_stage;
  ports.noun_root = model_noun_root;
  ports.root_followup = model_root_followup;
  ports.root_stage = model_root_stage;
  ports.resolve_current_empire = model_resolve_current_empire;
  ports.directed_identity = model_directed_identity;
  ports.relationship_classifier = model_relationship_classifier;
}

void install_threshold_ports() {
  EmpireDiplomacyPorts& ports = empire_diplomacy_ports();
  ports.property_service = model_property_service;
  ports.property_object = model_property_object;
  ports.property_read = model_property_read;
  ports.property_number = model_property_number;
  ports.property_release = model_property_release;
}

void install_apply_ports() {
  EmpireDiplomacyPorts& ports = empire_diplomacy_ports();
  ports.relationship_lookup = model_relationship_lookup;
  ports.relationship_ensure = model_relationship_ensure;
  ports.runtime_mode = model_runtime_mode;
  ports.star_manager = model_star_manager;
  ports.star_lookup = model_star_lookup;
  ports.star_key = model_star_key;
  ports.event_profile = model_event_profile;
  ports.event_lower_bound = model_event_lower_bound;
  ports.event_insert = model_event_insert;
  ports.event_remove = model_event_remove;
  ports.relationship_value = model_relationship_value;
  ports.reset_relationship = model_reset_relationship;
  ports.aggregate_relationship = model_aggregate_relationship;
  ports.app_system = model_app_system;
  ports.event_dispatch = model_event_dispatch;
  ports.current_player_id = model_current_player_id;
  ports.directed_empire_object = model_directed_empire_object;
  ports.directed_empire_kind = model_directed_empire_kind;
  ports.metric_owner = model_metric_owner;
  ports.metric_value = model_metric_value;
}

void test_classifier_directed_scores_boundaries_and_sentinels() {
  reset_model();
  install_relationship_ports();
  score_result_source = 10u;
  score_result_target = 20u;
  score_result_mode = 1u;
  const std::pair<float, OpaqueWord> cases[] = {
      {-std::numeric_limits<float>::infinity(), 0u},
      {-10.0f, 0u},
      {-8.0f, 0u},
      {-7.0f, 1u},
      {-2.0f, 1u},
      {-1.9f, 2u},
      {2.0f, 3u},
      {7.9f, 3u},
      {8.0f, 4u},
      {std::numeric_limits<float>::infinity(), 4u},
      {std::numeric_limits<float>::max(), 4u},
      {std::numeric_limits<float>::quiet_NaN(), 0u}};
  for (const auto& item : cases) {
    reset_model();
    install_relationship_ports();
    score_result_source = 10u;
    score_result_target = 20u;
    score_result_mode = 1u;
    score_result = item.first;
    assert(RelationshipClassify_00d00a70(&policy, 10u, 20u, 1u) ==
           item.second);
  }
  reset_model();
  install_relationship_ports();
  score_result_source = 20u;
  score_result_target = 10u;
  score_result = -7.0f;
  assert(RelationshipClassify_00d00a70(&policy, 20u, 10u, 1u) == 1u);
}

void test_owner_adjustment_identity_and_stage_order() {
  reset_model();
  install_relationship_ports();
  second.relationship_owner_id = 7u;
  second.relationship_gate = 0u;
  stage_result = 0;
  assert(RelationshipOwnerAdjustment_00d00b40(7u, &second) == -4.0f);
  stage_result = 1;
  assert(RelationshipOwnerAdjustment_00d00b40(7u, &second) == -2.0f);
  stage_result = 2;
  assert(RelationshipOwnerAdjustment_00d00b40(7u, &second) == -3.0f);
  stage_result = -1;
  assert(RelationshipOwnerAdjustment_00d00b40(7u, &second) == 0.0f);
  assert(RelationshipOwnerAdjustment_00d00b40(8u, &second) == 0.0f);

  second.relationship_gate = 1u;
  root_stage_results = {2};
  root_stage_index = 0;
  stage_result = 0;
  assert(RelationshipOwnerAdjustment_00d00b40(7u, &second) == -8.0f);
  assert(root_stage_index == 1);
  assert_trace({"stage", "root", "followup", "root-stage"});

  root_stage_results = {0, 1};
  root_stage_index = 0;
  stage_result = 1;
  assert(RelationshipOwnerAdjustment_00d00b40(7u, &second) == -3.0f);
  assert(root_stage_index == 2);

  root_stage_results = {0, 0};
  root_stage_index = 0;
  assert(RelationshipOwnerAdjustment_00d00b40(8u, &second) == 0.0f);
  assert(root_stage_index == 2);
}

void test_threshold_load_order_type_filter_and_null_paths() {
  reset_model();
  install_threshold_ports();
  service_result = reinterpret_cast<Opaque*>(1);
  for (std::size_t index = 0; index < 4; ++index) {
    properties[index].type = 13u;
  }
  RelationshipLoadThresholds_00d00db0(&manager);
  assert(manager.thresholds[0] == 1.0f);
  assert(manager.thresholds[1] == 2.0f);
  assert(manager.thresholds[2] == 3.0f);
  assert(manager.thresholds[3] == 4.0f);
  assert_trace({"property-service", "property-object", "property-read-30770810",
                "property-number", "property-read-30770800", "property-number",
                "property-read-30770726", "property-number",
                "property-read-30770732", "property-number", "property-release"});

  reset_model();
  install_threshold_ports();
  service_result = reinterpret_cast<Opaque*>(1);
  properties[0].type = 12u;
  properties[1].type = 13u;
  properties[2].type = 13u;
  properties[3].type = 13u;
  RelationshipLoadThresholds_00d00db0(&manager);
  assert(manager.thresholds[0] == 0.0f);
  assert(manager.thresholds[1] == 2.0f);

  reset_model();
  install_threshold_ports();
  service_result = reinterpret_cast<Opaque*>(1);
  property_result_mask = 0x3u;
  RelationshipLoadThresholds_00d00db0(&manager);
  assert(manager.thresholds[2] == 0.0f);
  assert(manager.thresholds[3] == 0.0f);
  assert(trace.back() == "property-release");

  reset_model();
  install_threshold_ports();
  service_result = reinterpret_cast<Opaque*>(1);
  property_object_success = false;
  RelationshipLoadThresholds_00d00db0(&manager);
  assert_trace({"property-service", "property-none", "property-release"});

  reset_model();
  install_threshold_ports();
  service_result = reinterpret_cast<Opaque*>(1);
  property_object_result = nullptr;
  RelationshipLoadThresholds_00d00db0(&manager);
  assert_trace({"property-service", "property-object"});
}

void test_directed_penalty_identity_propagation_and_short_circuit() {
  reset_model();
  install_relationship_ports();
  current_identity = 30u;
  first_identity = 10u;
  second_identity = 20u;
  classifier_results[0] = 4u;
  classifier_results[1] = 1u;
  assert(DirectedEmpirePenalty_00d00ee0(&first, &second) == -10.0f);
  assert_trace({"root", "resolve-current", "identity-current", "identity-first",
                "classify", "identity-second", "classify"});

  reset_model();
  install_relationship_ports();
  current_identity = 30u;
  first_identity = 10u;
  second_identity = 20u;
  classifier_results[0] = 3u;
  assert(DirectedEmpirePenalty_00d00ee0(&first, &second) == 0.0f);
  assert(classifier_index == 1);

  reset_model();
  install_relationship_ports();
  current_identity = 30u;
  first_identity = 10u;
  second_identity = 20u;
  classifier_results[0] = 4u;
  classifier_results[1] = 2u;
  assert(DirectedEmpirePenalty_00d00ee0(&first, &second) == 0.0f);

  reset_model();
  install_relationship_ports();
  first.relationship_gate = 1u;
  assert(DirectedEmpirePenalty_00d00ee0(&first, &second) == 0.0f);
  assert(trace.empty());
}

void initialize_pair_map() {
  relationship_map.anchor = reinterpret_cast<OpaqueRelationshipPairNode*>(
      reinterpret_cast<unsigned char*>(&relationship_map) + 0x04u);
  pair_left.left = nullptr;
  pair_left.right = nullptr;
  pair_left.key_a = 5u;
  pair_left.key_b = 9u;
  pair_root.left = &pair_left;
  pair_root.right = &pair_right;
  pair_root.key_a = 10u;
  pair_root.key_b = 5u;
  pair_right.left = nullptr;
  pair_right.right = nullptr;
  pair_right.key_a = 20u;
  pair_right.key_b = 1u;
  relationship_map.root = &pair_root;
}

OpaqueRelationshipPairNode* lower_bound(OpaqueWord first, OpaqueWord second) {
  static OpaqueRelationshipPairNode key{};
  key.key_a = first;
  key.key_b = second;
  OpaqueRelationshipPairNode* result = nullptr;
  RelationshipMapLowerBound_00d00f80(&relationship_map, &result, &key);
  return result;
}

void test_pair_map_lower_bound_sentinel_and_invalid_keys() {
  reset_model();
  initialize_pair_map();
  assert(lower_bound(10u, 5u) == relationship_map.root);
  assert(lower_bound(10u, 4u) == relationship_map.root->left);
  assert(lower_bound(10u, 6u) == relationship_map.root->right);
  assert(lower_bound(11u, 0u) == relationship_map.root->right);
  assert(lower_bound(9u, 99u) == relationship_map.root->left);
  assert(lower_bound(4u, 0u) == relationship_map.anchor);
  assert(lower_bound(std::numeric_limits<OpaqueWord>::max(),
                      std::numeric_limits<OpaqueWord>::max()) ==
         relationship_map.anchor);
  assert(lower_bound(0u, 0u) == relationship_map.anchor);
  assert(relationship_map.root->left == &pair_left);
  assert(relationship_map.root->right == &pair_right);
}

void test_apply_create_event_order_and_directed_identity() {
  reset_model();
  install_apply_ports();
  lookup_source = 10u;
  lookup_target = 20u;
  lookup_modifier = 0x05adb0aau;
  lookup_result = nullptr;
  runtime_mode = 0x01654c05u;
  selected_star = reinterpret_cast<OpaqueStarManager*>(1);
  star_key_result = 77u;
  profile_base = 0u;
  use_existing_event = false;
  relationship_values[0] = 1.25f;
  relationship_values[1] = 2.5f;
  current_player_result = 20u;
  empire_kind_result = 5;
  metric_result_value = 1.0f;
  const float result =
      RelationshipApply_00d05d90(&manager, &relationship_map, 10u, 20u,
                                 lookup_modifier, 0.75f);
  assert(result == 1.25f);
  assert(inserted_node.key == lookup_modifier);
  assert(inserted_node.value == 0.75f);
  assert(profile_base == 77u);
  assert(dispatch_count == 1);
  assert(aggregate_count == 1);
  assert(remove_count == 0);
  assert_trace({"lookup", "ensure", "mode", "star-manager", "star-lookup",
                "star-key", "profile", "value-before", "event-lower-bound",
                "event-insert", "value-after", "current-player", "empire-kind",
                "metric-owner", "metric-value", "app-system", "event",
                "object-source", "object-target", "aggregate"});
}

void test_apply_existing_near_zero_removal_and_unknown_id() {
  reset_model();
  install_apply_ports();
  lookup_source = 10u;
  lookup_target = 20u;
  lookup_modifier = 0x12345678u;
  runtime_mode = 0u;
  use_existing_event = true;
  existing_node.value = 0.005f;
  relationship_values[0] = 3.0f;
  relationship_values[1] = 3.25f;
  current_player_result = 99u;
  const float result =
      RelationshipApply_00d05d90(&manager, &relationship_map, 10u, 20u,
                                 lookup_modifier, -0.004f);
  assert(result == 0.25f);
  assert(existing_node.value == 0.001f);
  assert(remove_count == 1);
  assert(dispatch_count == 0);
  assert(aggregate_count == 0);
  assert(profile_base == 0x4e5855b9u);
}

void test_apply_zero_app_reset_and_reverse_direction() {
  reset_model();
  install_apply_ports();
  lookup_source = 10u;
  lookup_target = 20u;
  lookup_modifier = 0x12345678u;
  runtime_mode = 0x01654c02u;
  selected_star = nullptr;
  use_existing_event = true;
  relationship_values[0] = 4.0f;
  relationship_values[1] = 4.5f;
  current_player_result = 10u;
  object_result = reinterpret_cast<OpaqueDirectedEmpire*>(1);
  RelationshipApply_00d05d90(&manager, &relationship_map, 10u, 20u,
                            lookup_modifier, 0.0f);
  assert(trace.empty());
  assert(reset_count == 0);

  trace.clear();
  entry.value = 9.0f;
  RelationshipApply_00d05d90(&manager, &relationship_map, 10u, 20u,
                            lookup_modifier, 0.5f);
  assert(entry.value == std::numeric_limits<float>::max());
  assert(reset_count == 1);
  assert(aggregate_count == 1);
  assert(trace.front() == "lookup");
  assert(trace[1] == "mode");
  assert(trace[2] == "reset");

  reset_model();
  install_apply_ports();
  lookup_source = 20u;
  lookup_target = 10u;
  lookup_modifier = 0x12345678u;
  runtime_mode = 0u;
  use_existing_event = true;
  relationship_values[0] = 0.0f;
  relationship_values[1] = 0.5f;
  const float reverse =
      RelationshipApply_00d05d90(&manager, &relationship_map, 20u, 10u,
                                 lookup_modifier, 0.5f);
  assert(reverse == 0.5f);
  assert(profile_base == 0x4e5855b9u);
  assert(existing_node.value == 0.5f);
}

}

int main() {
  test_classifier_directed_scores_boundaries_and_sentinels();
  test_owner_adjustment_identity_and_stage_order();
  test_threshold_load_order_type_filter_and_null_paths();
  test_directed_penalty_identity_propagation_and_short_circuit();
  test_pair_map_lower_bound_sentinel_and_invalid_keys();
  test_apply_create_event_order_and_directed_identity();
  test_apply_existing_near_zero_removal_and_unknown_id();
  test_apply_zero_app_reset_and_reverse_direction();
}
