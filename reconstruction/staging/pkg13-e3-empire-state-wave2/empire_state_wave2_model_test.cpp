#include <cmath>
#include <cstdlib>
#include <initializer_list>
#include <limits>
#include <vector>

#include "empire_state_wave2.hpp"

namespace openspore::reconstruction::pkg13_e3_empire_state_wave2 {
namespace {

extern "C" OpaqueWord PKG13_E3_CDECL ArchetypeRelationshipsIDIncoming_00c30e20(
    OpaqueWord archetype, OpaqueWord difficulty, OpaqueWord incoming_eax);

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

constexpr OpaqueWord kDefaultRelationshipId = 0x4e5855b9u;
constexpr OpaqueWord kExpectedMatrix[19][3] = {
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

void expect_selector_matrix() {
  for (OpaqueWord archetype = 0u; archetype < 19u; ++archetype) {
    for (OpaqueWord difficulty = 0u; difficulty < 3u; ++difficulty) {
      check(SpeciesProfileSelector_00c30cc0(archetype, difficulty) ==
            kExpectedMatrix[archetype][difficulty]);
    }
  }
  for (OpaqueWord archetype = 0u; archetype < 19u; ++archetype) {
    for (OpaqueWord difficulty :
         {3u, 4u, 0x80000000u, std::numeric_limits<OpaqueWord>::max()}) {
      check(SpeciesProfileSelector_00c30cc0(archetype, difficulty) ==
            kDefaultRelationshipId);
    }
  }
  for (OpaqueWord archetype :
       {19u, 20u, 0x80000000u, std::numeric_limits<OpaqueWord>::max()}) {
    for (OpaqueWord difficulty = 0u; difficulty < 3u; ++difficulty) {
      check(SpeciesProfileSelector_00c30cc0(archetype, difficulty) ==
            kDefaultRelationshipId);
    }
  }
  for (OpaqueWord archetype :
       {0u, 8u, 18u, 19u, std::numeric_limits<OpaqueWord>::max()}) {
    check(ArchetypeRelationshipsID_00c30e20(archetype, 0u) == 0x25885eafu);
    check(ArchetypeRelationshipsID_00c30e20(archetype, 1u) == 0x7e56d6ccu);
    check(ArchetypeRelationshipsID_00c30e20(archetype, 2u) == 0x87d7829au);
    check(ArchetypeRelationshipsIDIncoming_00c30e20(
              archetype, 0u, 0x12345678u) == 0x25885eafu);
    check(ArchetypeRelationshipsIDIncoming_00c30e20(
              archetype, 1u, 0x12345678u) == 0x7e56d6ccu);
    check(ArchetypeRelationshipsIDIncoming_00c30e20(
              archetype, 2u, 0x12345678u) == 0x87d7829au);
    check(ArchetypeRelationshipsIDIncoming_00c30e20(
              archetype, 3u, 0x12345678u) == 0x12345678u);
  }
}

void test_selector_archetype_eight_invalid_difficulty() {
  check(SpeciesProfileSelector_00c30cc0(8u, 3u) == kDefaultRelationshipId);
}

enum class MetricCall {
  source,
  context,
  value,
};

const EmpireStatePorts kDefaultPorts = empire_state_ports();
std::vector<MetricCall> metric_trace;
OpaqueEmpireMetricState metric_state{};
OpaqueMetricValue* metric_source_result = nullptr;
OpaqueMetricContext* metric_context_result = nullptr;
float metric_value_result = 0.0f;

OpaqueMetricValue* PKG13_E3_THISCALL
model_metric_source(OpaqueEmpireMetricState* state) {
  check(state == &metric_state);
  metric_trace.push_back(MetricCall::source);
  return metric_source_result;
}

OpaqueMetricContext* PKG13_E3_CDECL model_metric_context() {
  metric_trace.push_back(MetricCall::context);
  return metric_context_result;
}

float PKG13_E3_THISCALL model_metric_value(OpaqueMetricContext* context,
                                           OpaqueMetricValue* source) {
  check(context == metric_context_result);
  check(source == metric_source_result);
  metric_trace.push_back(MetricCall::value);
  return metric_value_result;
}

void install_metric_ports() {
  EmpireStatePorts& ports = empire_state_ports();
  ports.metric_source = model_metric_source;
  ports.metric_context = model_metric_context;
  ports.metric_value = model_metric_value;
}

void reset_metric_model() {
  empire_state_ports() = kDefaultPorts;
  metric_trace.clear();
  metric_state = {};
  metric_source_result = reinterpret_cast<OpaqueMetricValue*>(1);
  metric_context_result = reinterpret_cast<OpaqueMetricContext*>(2);
  metric_value_result = 0.0f;
  install_metric_ports();
}

void expect_metric_trace(std::initializer_list<MetricCall> expected) {
  check(metric_trace.size() == expected.size());
  std::size_t index = 0u;
  for (MetricCall call : expected) {
    check(metric_trace[index] == call);
    ++index;
  }
}

void test_metric_cache_gate_and_helper_order() {
  reset_metric_model();
  metric_state.home_world_metric = 7.5f;
  metric_value_result = 9.0f;
  check(HomeWorldMetricLazy_00c31890(&metric_state) == 7.5f);
  check(metric_state.home_world_metric == 7.5f);
  check(metric_trace.empty());

  reset_metric_model();
  metric_state.home_world_metric = 0.0f;
  metric_value_result = 9.0f;
  check(HomeWorldMetricLazy_00c31890(&metric_state) == 9.0f);
  check(metric_state.home_world_metric == 9.0f);
  expect_metric_trace(
      {MetricCall::source, MetricCall::context, MetricCall::value});

  reset_metric_model();
  metric_state.home_world_metric = -2.0f;
  metric_value_result = -3.5f;
  check(HomeWorldMetricLazy_00c31890(&metric_state) == -3.5f);
  check(metric_state.home_world_metric == -3.5f);
  expect_metric_trace(
      {MetricCall::source, MetricCall::context, MetricCall::value});

  reset_metric_model();
  metric_state.home_world_metric = std::numeric_limits<float>::quiet_NaN();
  metric_value_result = 11.0f;
  const float nan_result = HomeWorldMetricLazy_00c31890(&metric_state);
  check(std::isnan(nan_result));
  check(std::isnan(metric_state.home_world_metric));
  check(metric_trace.empty());
}

enum class ProfileCall {
  current,
  prepare_first,
  manager,
  record_to_planet,
  vector_zero,
  vector_one,
  apply,
  prepare_second,
  name_state,
  name_assign,
  cleanup,
};

OpaqueSpeciesProfile species{};
OpaqueSpeciesProfile distinct_species{};
OpaqueProfile profile{};
OpaqueCurrentEmpire* current_result = nullptr;
OpaqueStarManager* manager_result = nullptr;
OpaqueVectorElement vector_elements[2]{};
OpaqueVectorElement* vector_storage[2]{};
OpaqueNameNode root_node{};
OpaqueNameNode leaf_node{};
OpaqueTextWord root_name[] = {'r', 'o', 'o', 't', 0};
OpaqueTextWord leaf_name[] = {'l', 'e', 'a', 'f', 0};
std::vector<ProfileCall> profile_trace;
std::vector<OpaqueWord*> prepare_arguments;
std::size_t prepare_index = 0u;
bool current_profile_branch = true;
OpaqueLocalRecord* prepared_first_record = nullptr;
OpaqueLocalRecord* applied_record = nullptr;
OpaqueLocalRecord* state_record = nullptr;
OpaqueTextWord assigned_name[8]{};
std::size_t assigned_length = 0u;
std::size_t cleanup_count = 0u;
std::vector<OpaqueWord> vector_colors[2];

OpaqueCurrentEmpire* PKG13_E3_CDECL model_current_empire() {
  profile_trace.push_back(ProfileCall::current);
  return current_result;
}

void PKG13_E3_THISCALL model_profile_prepare(OpaqueProfile* receiver,
                                             OpaqueWord* argument) {
  check(receiver == &profile);
  prepare_arguments.push_back(argument);
  const OpaqueLocalRecord* record =
      reinterpret_cast<const OpaqueLocalRecord*>(argument);
  if (prepare_index == 0u && current_profile_branch) {
    profile_trace.push_back(ProfileCall::prepare_first);
    check(argument != reinterpret_cast<OpaqueWord*>(&species));
    check(record->first == 0x01667bacu);
    check(record->second == 0x01667bacu);
    check(record->third == 0x01667baeu);
    prepared_first_record = const_cast<OpaqueLocalRecord*>(record);
  } else {
    profile_trace.push_back(ProfileCall::prepare_second);
    check(record->first == 0x01667bacu);
    check(record->second == 0x01667bacu);
    check(record->third == 0x01667baeu);
  }
  ++prepare_index;
}

OpaqueStarManager* PKG13_E3_CDECL model_star_manager() {
  profile_trace.push_back(ProfileCall::manager);
  return manager_result;
}

void PKG13_E3_THISCALL model_record_to_planet(OpaqueStarManager* manager,
                                              OpaqueLocalRecord* record) {
  check(manager == manager_result);
  check(record == prepared_first_record);
  check(record->first == 0x01667bacu);
  check(record->second == 0x01667bacu);
  check(record->third == 0x01667baeu);
  profile_trace.push_back(ProfileCall::record_to_planet);
}

void PKG13_E3_THISCALL model_profile_apply(OpaqueSpeciesProfile* receiver,
                                           OpaqueLocalRecord* record) {
  check(receiver == &species);
  applied_record = record;
  profile_trace.push_back(ProfileCall::apply);
}

void PKG13_E3_THISCALL model_vector_color(OpaqueVectorElement* element,
                                          OpaqueWord* color) {
  check(element == &vector_elements[0] || element == &vector_elements[1]);
  const std::size_t index = element == &vector_elements[0] ? 0u : 1u;
  profile_trace.push_back(index == 0u ? ProfileCall::vector_zero
                                      : ProfileCall::vector_one);
  vector_colors[index].assign(color, color + 3);
  for (std::size_t word = 0u; word < 3u; ++word) {
    element->words[word] = color[word];
  }
}

void PKG13_E3_THISCALL model_name_state(OpaqueProfileNameState* receiver,
                                        OpaqueLocalRecord* record) {
  check(receiver == &species.name_state);
  state_record = record;
  check(record->first == 0x01667bacu);
  check(record->second == 0x01667bacu);
  check(record->third == 0x01667baeu);
  profile_trace.push_back(ProfileCall::name_state);
}

void PKG13_E3_THISCALL model_name_assign(OpaqueText* receiver,
                                         OpaqueTextWord* begin,
                                         OpaqueTextWord* end) {
  check(receiver == &species.name);
  check(end >= begin);
  assigned_length = static_cast<std::size_t>(end - begin);
  check(assigned_length < sizeof(assigned_name) / sizeof(assigned_name[0]));
  for (std::size_t index = 0u; index < assigned_length; ++index) {
    assigned_name[index] = begin[index];
  }
  profile_trace.push_back(ProfileCall::name_assign);
}

void PKG13_E3_CDECL model_record_cleanup(OpaqueLocalRecord* record) {
  check(record != nullptr);
  ++cleanup_count;
  profile_trace.push_back(ProfileCall::cleanup);
}

void install_profile_ports() {
  EmpireStatePorts& ports = empire_state_ports();
  ports.current_empire = model_current_empire;
  ports.profile_prepare = model_profile_prepare;
  ports.star_manager = model_star_manager;
  ports.record_to_planet = model_record_to_planet;
  ports.profile_apply = model_profile_apply;
  ports.vector_color = model_vector_color;
  ports.name_state = model_name_state;
  ports.name_assign = model_name_assign;
  ports.record_cleanup = model_record_cleanup;
}

void reset_profile_model() {
  empire_state_ports() = kDefaultPorts;
  species = {};
  distinct_species = {};
  profile = {};
  profile.color[0] = 0x11u;
  profile.color[1] = 0x22u;
  profile.color[2] = 0x33u;
  current_result = reinterpret_cast<OpaqueCurrentEmpire*>(&species);
  manager_result = reinterpret_cast<OpaqueStarManager*>(4);
  vector_elements[0] = {};
  vector_elements[1] = {};
  vector_storage[0] = &vector_elements[0];
  vector_storage[1] = &vector_elements[1];
  species.vector_begin = vector_storage;
  species.vector_end = vector_storage + 2;
  species.vector_capacity = vector_storage + 2;
  root_node = {};
  leaf_node = {};
  root_node.rank = 1u;
  root_node.right = &leaf_node;
  root_node.name = root_name;
  leaf_node.rank = 3u;
  leaf_node.name = leaf_name;
  species.name_state.root = &root_node;
  species.name_state.leaf = &leaf_node;
  profile_trace.clear();
  prepare_arguments.clear();
  prepare_index = 0u;
  current_profile_branch = true;
  prepared_first_record = nullptr;
  applied_record = nullptr;
  state_record = nullptr;
  assigned_length = 0u;
  cleanup_count = 0u;
  vector_colors[0].clear();
  vector_colors[1].clear();
  install_profile_ports();
}

void expect_profile_trace(std::initializer_list<ProfileCall> expected) {
  check(profile_trace.size() == expected.size());
  std::size_t index = 0u;
  for (ProfileCall call : expected) {
    check(profile_trace[index] == call);
    ++index;
  }
}

void test_profile_current_path_color_vector_name_and_cleanup() {
  reset_profile_model();
  ProfileSetter_00c33690(&species, &profile);
  expect_profile_trace({ProfileCall::current, ProfileCall::prepare_first,
                        ProfileCall::manager, ProfileCall::record_to_planet,
                        ProfileCall::vector_zero, ProfileCall::vector_one,
                        ProfileCall::apply, ProfileCall::prepare_second,
                        ProfileCall::name_state, ProfileCall::name_assign});
  check(prepare_index == 2u);
  check(prepared_first_record != nullptr);
  check(prepared_first_record ==
        reinterpret_cast<OpaqueLocalRecord*>(prepare_arguments[0]));
  check(applied_record != nullptr);
  check(applied_record == prepared_first_record);
  check(state_record != nullptr);
  check(vector_colors[0] == std::vector<OpaqueWord>({0x11u, 0x22u, 0x33u}));
  check(vector_colors[1] == std::vector<OpaqueWord>({0x11u, 0x22u, 0x33u}));
  check(assigned_length == 4u);
  check(assigned_name[0] == u'l');
  check(assigned_name[1] == u'e');
  check(assigned_name[2] == u'a');
  check(assigned_name[3] == u'f');
  check(cleanup_count == 0u);
}

void test_profile_distinct_path_forwards_uninitialized_first_record() {
  reset_profile_model();
  current_result = reinterpret_cast<OpaqueCurrentEmpire*>(&distinct_species);
  current_profile_branch = false;
  ProfileSetter_00c33690(&species, &profile);
  expect_profile_trace({ProfileCall::current, ProfileCall::vector_zero,
                        ProfileCall::vector_one, ProfileCall::apply,
                        ProfileCall::prepare_second, ProfileCall::name_state,
                        ProfileCall::name_assign});
  check(prepare_index == 1u);
  check(applied_record != nullptr);
  check(applied_record != state_record);
  check(cleanup_count == 0u);
}

void test_profile_null_path_uses_zero_color_and_skips_name() {
  reset_profile_model();
  ProfileSetter_00c33690(&species, nullptr);
  expect_profile_trace({ProfileCall::current, ProfileCall::vector_zero,
                        ProfileCall::vector_one});
  check(prepare_index == 0u);
  check(applied_record == nullptr);
  check(state_record == nullptr);
  check(assigned_length == 0u);
  check(vector_colors[0] == std::vector<OpaqueWord>({0u, 0u, 0u}));
  check(vector_colors[1] == std::vector<OpaqueWord>({0u, 0u, 0u}));
  check(cleanup_count == 0u);
}

void test_profile_empty_vector_keeps_final_profile_order() {
  reset_profile_model();
  species.vector_end = species.vector_begin;
  current_result = reinterpret_cast<OpaqueCurrentEmpire*>(&distinct_species);
  current_profile_branch = false;
  ProfileSetter_00c33690(&species, &profile);
  expect_profile_trace({ProfileCall::current, ProfileCall::apply,
                        ProfileCall::prepare_second, ProfileCall::name_state,
                        ProfileCall::name_assign});
  check(vector_colors[0].empty());
  check(vector_colors[1].empty());
  check(cleanup_count == 0u);
}

void test_profile_state_and_cleanup_remain_separate() {
  reset_profile_model();
  const OpaqueWord original_profile_color[3] = {0x11u, 0x22u, 0x33u};
  const OpaqueTextWord* original_name = species.name.begin;
  ProfileSetter_00c33690(&species, &profile);
  check(profile.color[0] == original_profile_color[0]);
  check(profile.color[1] == original_profile_color[1]);
  check(profile.color[2] == original_profile_color[2]);
  check(species.name.begin == original_name);
  check(cleanup_count == 0u);
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg13_e3_empire_state_wave2;
  expect_selector_matrix();
  test_selector_archetype_eight_invalid_difficulty();
  test_metric_cache_gate_and_helper_order();
  test_profile_current_path_color_vector_name_and_cleanup();
  test_profile_distinct_path_forwards_uninitialized_first_record();
  test_profile_null_path_uses_zero_color_and_skips_name();
  test_profile_empty_vector_keeps_final_profile_order();
  test_profile_state_and_cleanup_remain_separate();
}
