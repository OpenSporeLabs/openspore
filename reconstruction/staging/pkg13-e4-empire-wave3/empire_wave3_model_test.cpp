#include <cmath>
#include <cstdlib>
#include <initializer_list>
#include <limits>
#include <vector>

#include "empire_wave3.hpp"

namespace openspore::reconstruction::pkg13_e4_empire_wave3 {

struct OpaqueRegistry {
  OpaqueWord marker;
};

struct OpaqueVectorSource {
  OpaqueFloatColor color;
};

struct OpaqueMessageRoot {
  OpaqueWord marker;
};

struct OpaqueMessageState {
  OpaqueWord marker;
};

struct OpaquePersistenceTarget {
  OpaqueWord marker;
};

namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

bool same_color(const OpaqueFloatColor& first, const OpaqueFloatColor& second) {
  return first.value[0] == second.value[0] &&
         first.value[1] == second.value[1] && first.value[2] == second.value[2];
}

enum class ColorCall {
  current,
  registry,
  registry_record,
  resource_type,
  resource_profile,
  current_profile,
  identity,
  active,
  transform,
  write,
  rebuild,
  vector_source,
  collect,
  item_word,
  candidate,
  palette,
  cleanup_first,
  cleanup_second,
  cleanup_third,
  cleanup_fourth,
  cleanup_fifth,
  storage,
};

const EmpireColorPorts kColorDefaults = empire_color_ports();
std::vector<ColorCall> color_trace;
OpaqueRecord current_record{};
OpaqueRecord distinct_record{};
OpaqueRecord candidates[4]{};
OpaqueRegistry registry{};
OpaqueResourceRecord receiver_resource{};
OpaqueResourceRecord candidate_resources[4]{};
OpaqueProfile profiles[2]{};
OpaqueVectorSource receiver_source{};
OpaqueVectorSource candidate_sources[4]{};
OpaqueVectorItemVtable vector_vtable{};
OpaqueVectorItem vector_items[5]{};
OpaqueVectorItem* vector_entries[5]{};
OpaqueWord* vector_storage = nullptr;
OpaqueWord item_identities[5]{};
OpaqueFloatColor palette_colors[12]{};
OpaqueFloatColor current_palette_color{};
OpaqueFloatColor transform_color{{0.1f, 0.2f, 0.3f}};
OpaqueFloatColor transform_result{{0.4f, 0.5f, 0.6f}};
OpaqueRecord* current_result = &distinct_record;
OpaqueRegistry* registry_result = &registry;
OpaqueResourceRecord* receiver_resource_result = &receiver_resource;
OpaqueResourceRecord* candidate_resource_results[4] = {
    &candidate_resources[0], &candidate_resources[1], &candidate_resources[2],
    &candidate_resources[3]};
OpaqueProfile* profile_result = &profiles[0];
OpaqueProfile* current_profile_result = &profiles[0];
OpaqueWord resource_type_result = 5u;
OpaqueWord identity_result = 999u;
OpaqueWord candidate_identities[4] = {101u, 102u, 103u, 104u};
std::uint8_t palette_active[12]{};
bool color_equal_result = true;
float transform_lower = 0.0f;
float transform_upper = 0.0f;
int transform_count = 0;
int write_count = 0;
int rebuild_count = 0;
int cleanup_count = 0;
int storage_cleanup_count = 0;
bool query_valid = false;

OpaqueRecord* PKG13_E4_CDECL model_current_empire() {
  color_trace.push_back(ColorCall::current);
  return current_result;
}

OpaqueRegistry* PKG13_E4_CDECL model_registry() {
  color_trace.push_back(ColorCall::registry);
  return registry_result;
}

OpaqueResourceRecord* PKG13_E4_THISCALL
model_registry_record(OpaqueRegistry* receiver, OpaqueWord handle) {
  check(receiver == registry_result);
  color_trace.push_back(ColorCall::registry_record);
  if (handle == 0x10u) {
    return receiver_resource_result;
  }
  for (int index = 0; index < 4; ++index) {
    if (handle == candidate_identities[index]) {
      return candidate_resource_results[index];
    }
  }
  return nullptr;
}

OpaqueWord PKG13_E4_THISCALL
model_resource_type(OpaqueResourceRecord* receiver) {
  check(receiver == receiver_resource_result ||
        receiver == candidate_resource_results[0] ||
        receiver == candidate_resource_results[1] ||
        receiver == candidate_resource_results[2] ||
        receiver == candidate_resource_results[3]);
  color_trace.push_back(ColorCall::resource_type);
  return resource_type_result;
}

OpaqueProfile* PKG13_E4_THISCALL
model_resource_profile(OpaqueResourceRecord* receiver) {
  check(receiver == receiver_resource_result);
  color_trace.push_back(ColorCall::resource_profile);
  return profile_result;
}

OpaqueProfile* PKG13_E4_THISCALL model_current_profile(OpaqueRecord* receiver) {
  check(receiver == &distinct_record);
  color_trace.push_back(ColorCall::current_profile);
  return current_profile_result;
}

OpaqueWord PKG13_E4_THISCALL model_registry_identity(OpaqueRegistry* receiver) {
  check(receiver == registry_result);
  color_trace.push_back(ColorCall::identity);
  return identity_result;
}

const OpaqueFloatColor* PKG13_E4_CDECL model_palette(OpaqueWord value) {
  color_trace.push_back(ColorCall::palette);
  if (value == 0x53dbcf1u) {
    return &current_palette_color;
  }
  return &palette_colors[value - 0x53dbcf3u];
}

std::uint8_t PKG13_E4_CDECL model_palette_active(OpaqueWord value) {
  color_trace.push_back(ColorCall::active);
  return palette_active[value];
}

bool PKG13_E4_CDECL model_color_equal(const OpaqueFloatColor* first,
                                      const OpaqueFloatColor* second) {
  color_trace.push_back(ColorCall::transform);
  return color_equal_result && same_color(*first, *second);
}

void PKG13_E4_CDECL model_color_transform(const OpaqueFloatColor* source,
                                          OpaqueFloatColor* output, float lower,
                                          float upper) {
  check(source == &profile_result->color_4ec ||
        source == &current_profile_result->color_4ec);
  color_trace.push_back(ColorCall::transform);
  transform_lower = lower;
  transform_upper = upper;
  *output = transform_result;
  ++transform_count;
}

void PKG13_E4_CDECL model_palette_write(float first, float second,
                                        float third) {
  color_trace.push_back(ColorCall::write);
  check(first == transform_result.value[0]);
  check(second == transform_result.value[1]);
  check(third == transform_result.value[2]);
  ++write_count;
}

void PKG13_E4_CDECL model_palette_rebuild() {
  color_trace.push_back(ColorCall::rebuild);
  ++rebuild_count;
}

const OpaqueFloatColor* PKG13_E4_THISCALL
model_vector_source(OpaqueResourceRecord* receiver) {
  color_trace.push_back(ColorCall::vector_source);
  if (receiver == receiver_resource_result) {
    return &receiver_source.color;
  }
  for (int index = 0; index < 4; ++index) {
    if (receiver == candidate_resource_results[index]) {
      return &candidate_sources[index].color;
    }
  }
  return nullptr;
}

void PKG13_E4_THISCALL model_vector_collect(OpaqueRegistry* receiver,
                                            const OpaqueFloatColor* source,
                                            OpaqueVectorQuery* query,
                                            OpaqueVectorItem*** output) {
  check(receiver == registry_result);
  check(source == &receiver_source.color);
  check(output == &query->end);
  check(query->begin == nullptr);
  check(query->field_14 == 0x1fffu);
  check(query->field_18 == 0u);
  check(query->field_1c == 50.0f);
  check(query->field_20 == -1.0f);
  check(query->field_24 == 0u);
  check(query->field_28 == -1.0f);
  check(query->field_2c == 0u);
  color_trace.push_back(ColorCall::collect);
  query->begin = vector_entries;
  *output = vector_entries + 5;
  query_valid = true;
}

OpaqueWord PKG13_E4_THISCALL model_vector_item_word(OpaqueVectorItem* item) {
  color_trace.push_back(ColorCall::item_word);
  for (int index = 0; index < 5; ++index) {
    if (item == &vector_items[index]) {
      return item_identities[index];
    }
  }
  return 0xffffffffu;
}

OpaqueRecord* PKG13_E4_THISCALL
model_registry_candidate(OpaqueRegistry* receiver, OpaqueWord identity) {
  check(receiver == registry_result);
  color_trace.push_back(ColorCall::candidate);
  for (int index = 0; index < 4; ++index) {
    if (identity == candidate_identities[index]) {
      return &candidates[index];
    }
  }
  return nullptr;
}

void PKG13_E4_THISCALL model_vector_cleanup(OpaqueVectorItem* item) {
  for (int index = 0; index < 5; ++index) {
    if (item == &vector_items[index]) {
      color_trace.push_back(static_cast<ColorCall>(
          static_cast<int>(ColorCall::cleanup_first) + index));
      ++cleanup_count;
      return;
    }
  }
  std::abort();
}

void PKG13_E4_CDECL model_vector_storage_cleanup(OpaqueVectorItem** begin) {
  check(begin == vector_entries);
  color_trace.push_back(ColorCall::storage);
  ++storage_cleanup_count;
}

void install_color_ports() {
  EmpireColorPorts& ports = empire_color_ports();
  ports.current_empire = model_current_empire;
  ports.registry = model_registry;
  ports.registry_record = model_registry_record;
  ports.resource_type = model_resource_type;
  ports.resource_profile = model_resource_profile;
  ports.current_profile = model_current_profile;
  ports.registry_identity = model_registry_identity;
  ports.palette = model_palette;
  ports.palette_active = model_palette_active;
  ports.color_equal = model_color_equal;
  ports.color_transform = model_color_transform;
  ports.palette_write = model_palette_write;
  ports.palette_rebuild = model_palette_rebuild;
  ports.vector_source = model_vector_source;
  ports.vector_collect = model_vector_collect;
  ports.vector_item_word = model_vector_item_word;
  ports.registry_candidate = model_registry_candidate;
  ports.vector_storage_cleanup = model_vector_storage_cleanup;
}

void reset_color_model() {
  empire_color_ports() = kColorDefaults;
  delete[] vector_storage;
  vector_storage = new OpaqueWord[7];
  vector_storage[0] = 1u;
  current_record = {};
  distinct_record = {};
  distinct_record.field_10 = 0x53dbcf0u;
  distinct_record.field_84 = 77u;
  distinct_record.field_b0 = 0x10u;
  for (int index = 0; index < 4; ++index) {
    candidates[index] = {};
    candidates[index].field_10 = 0x53dbcf3u + static_cast<OpaqueWord>(index);
    candidates[index].field_b0 = candidate_identities[index];
  }
  candidates[1].field_10 = 0x53dbcf7u;
  candidates[3].field_10 = 0x53dbcf8u;
  registry = {1u};
  receiver_resource = {};
  for (int index = 0; index < 4; ++index) {
    candidate_resources[index] = {};
  }
  profiles[0] = {};
  profiles[1] = {};
  receiver_source = {{0.0f, 0.0f, 0.0f}};
  candidate_sources[0] = {{3.0f, 0.0f, 0.0f}};
  candidate_sources[1] = {{1.0f, 0.0f, 0.0f}};
  candidate_sources[2] = {{1.0f, 0.0f, 0.0f}};
  candidate_sources[3] = {{2.0f, 0.0f, 0.0f}};
  vector_vtable = {};
  vector_vtable.slot_04 = model_vector_cleanup;
  for (int index = 0; index < 5; ++index) {
    vector_items[index] = {&vector_vtable};
  }
  vector_entries[0] = &vector_items[0];
  vector_entries[1] = &vector_items[1];
  vector_entries[2] = &vector_items[2];
  vector_entries[3] = &vector_items[3];
  vector_entries[4] = &vector_items[4];
  item_identities[0] = 101u;
  item_identities[1] = 102u;
  item_identities[2] = 0xffffffffu;
  item_identities[3] = 103u;
  item_identities[4] = 104u;
  for (int index = 0; index < 12; ++index) {
    palette_colors[index] = {
        {0.01f * static_cast<float>(index + 1), 0.0f, 0.0f}};
    palette_active[index] = 0u;
  }
  palette_active[0] = 1u;
  palette_active[4] = 1u;
  palette_active[5] = 1u;
  current_palette_color = {{0.6f, 0.7f, 0.8f}};
  transform_color = {{0.1f, 0.2f, 0.3f}};
  transform_result = {{0.4f, 0.5f, 0.6f}};
  profile_result = &profiles[0];
  profile_result->color_4ec = transform_color;
  current_profile_result = &profiles[1];
  current_profile_result->color_4ec = transform_color;
  current_result = &current_record;
  registry_result = &registry;
  receiver_resource_result = &receiver_resource;
  for (int index = 0; index < 4; ++index) {
    candidate_resource_results[index] = &candidate_resources[index];
  }
  resource_type_result = 5u;
  identity_result = 999u;
  color_equal_result = true;
  transform_lower = 0.0f;
  transform_upper = 0.0f;
  transform_count = 0;
  write_count = 0;
  rebuild_count = 0;
  cleanup_count = 0;
  storage_cleanup_count = 0;
  query_valid = false;
  color_trace.clear();
  install_color_ports();
}

void test_cached_palette_path() {
  reset_color_model();
  OpaqueRecord record{};
  record.field_10 = 0x53dbcf7u;
  OpaqueFloatColor output{};
  check(EmpirePoliticalColor_00c32cd0(&record, &output) == &output);
  check(same_color(output, palette_colors[4]));
  check(color_trace.size() == 1u);
  check(color_trace[0] == ColorCall::palette);
  check(record.field_10 == 0x53dbcf7u);
}

void test_current_transform_writeback_and_cache() {
  reset_color_model();
  current_record.field_10 = 0x53dbcf0u;
  current_record.field_b0 = 0x10u;
  current_result = &current_record;
  OpaqueFloatColor output{};
  check(EmpirePoliticalColor_00c32cd0(&current_record, &output) == &output);
  check(current_record.field_10 == 0x53dbcf1u);
  check(same_color(current_record.color_30, transform_result));
  check(same_color(output, current_palette_color));
  check(transform_lower == 0.5f);
  check(transform_upper == 0.5f);
  check(transform_count == 1);
  check(write_count == 1);
  check(rebuild_count == 1);
  check(color_trace.size() == 8u);
  check(color_trace[0] == ColorCall::current);
  check(color_trace[1] == ColorCall::registry);
  check(color_trace[2] == ColorCall::registry_record);
  check(color_trace[3] == ColorCall::resource_profile);
  check(color_trace[4] == ColorCall::transform);
  check(color_trace[5] == ColorCall::write);
  check(color_trace[6] == ColorCall::rebuild);
  check(color_trace[7] == ColorCall::palette);
}

void test_current_black_cache_writeback() {
  reset_color_model();
  current_record.field_10 = 0x53dbcf1u;
  current_record.color_30 = {{0.0f, 0.0f, 0.0f}};
  current_result = &current_record;
  OpaqueFloatColor output{};
  check(EmpirePoliticalColor_00c32cd0(&current_record, &output) == &output);
  check(same_color(current_record.color_30, current_palette_color));
  check(same_color(output, current_palette_color));
  check(transform_count == 0);
  check(write_count == 0);
  check(rebuild_count == 0);
  check(color_trace.size() == 3u);
  check(color_trace[0] == ColorCall::current);
  check(color_trace[1] == ColorCall::palette);
  check(color_trace[2] == ColorCall::palette);
}

void test_special_black_transform_keeps_local_output() {
  reset_color_model();
  distinct_record.field_10 = 0x53dbcf1u;
  distinct_record.field_50 = 1u << 6;
  distinct_record.field_b0 = 0x10u;
  distinct_record.color_30 = {{0.0f, 0.0f, 0.0f}};
  OpaqueFloatColor output{};
  check(EmpirePoliticalColor_00c32cd0(&distinct_record, &output) == &output);
  check(same_color(output, distinct_record.color_30) == false);
  check(output.value[0] == 0.0f);
  check(output.value[1] == 0.0f);
  check(output.value[2] == 0.0f);
  check(same_color(distinct_record.color_30, transform_result));
  check(transform_count == 1);
  check(write_count == 0);
  check(rebuild_count == 0);
  check(color_trace.size() == 7u);
  check(color_trace[0] == ColorCall::current);
  check(color_trace[1] == ColorCall::registry);
  check(color_trace[2] == ColorCall::registry_record);
  check(color_trace[3] == ColorCall::resource_type);
  check(color_trace[4] == ColorCall::transform);
  check(color_trace[5] == ColorCall::current_profile);
  check(color_trace[6] == ColorCall::transform);
}

void test_special_nonblack_path_has_no_writeback() {
  reset_color_model();
  distinct_record.field_10 = 0x53dbcf1u;
  distinct_record.field_50 = 1u << 6;
  distinct_record.color_30 = {{0.2f, 0.3f, 0.4f}};
  OpaqueFloatColor output{};
  check(EmpirePoliticalColor_00c32cd0(&distinct_record, &output) == &output);
  check(same_color(output, distinct_record.color_30));
  check(transform_count == 0);
  check(color_trace.size() == 5u);
  check(color_trace.back() == ColorCall::transform);
}

void test_identity_shortcut() {
  reset_color_model();
  identity_result = distinct_record.field_84;
  OpaqueFloatColor output{};
  check(EmpirePoliticalColor_00c32cd0(&distinct_record, &output) == &output);
  check(output.value[0] == 0.2f);
  check(output.value[1] == 0.0f);
  check(output.value[2] == 0.25f);
  check(distinct_record.field_10 == 0x53dbcf0u);
  check(color_trace.size() == 3u);
  check(color_trace[0] == ColorCall::current);
  check(color_trace[1] == ColorCall::registry);
  check(color_trace[2] == ColorCall::identity);
}

void test_nearest_of_twelve_and_cleanup_order() {
  reset_color_model();
  for (int index = 0; index < 12; ++index) {
    palette_active[index] = 1u;
  }
  OpaqueFloatColor output{};
  check(EmpirePoliticalColor_00c32cd0(&distinct_record, &output) == &output);
  check(query_valid);
  check(distinct_record.field_10 == 0x53dbcf3u);
  check(same_color(output, palette_colors[0]));
  check(cleanup_count == 5);
  check(storage_cleanup_count == 1);
  check(color_trace[color_trace.size() - 7u] == ColorCall::palette);
  check(color_trace[color_trace.size() - 6u] == ColorCall::cleanup_first);
  check(color_trace[color_trace.size() - 5u] == ColorCall::cleanup_second);
  check(color_trace[color_trace.size() - 4u] == ColorCall::cleanup_third);
  check(color_trace[color_trace.size() - 3u] == ColorCall::cleanup_fourth);
  check(color_trace[color_trace.size() - 2u] == ColorCall::cleanup_fifth);
  check(color_trace.back() == ColorCall::storage);
}

void test_nearest_default_and_null_entries() {
  reset_color_model();
  vector_entries[2] = nullptr;
  item_identities[4] = 0x99999999u;
  for (int index = 0; index < 12; ++index) {
    palette_active[index] = 0u;
  }
  OpaqueFloatColor output{};
  check(EmpirePoliticalColor_00c32cd0(&distinct_record, &output) == &output);
  check(distinct_record.field_10 == 0x53dbcf4u);
  check(cleanup_count == 4);
  check(storage_cleanup_count == 1);
}

void test_distance_association_order() {
  reset_color_model();
  for (int index = 0; index < 12; ++index) {
    palette_active[index] = 1u;
  }
  candidate_sources[0] = {{1.0f, 1.0f, 0.3f}};
  candidate_sources[1] = {{1.0f, 0.3f, 1.0f}};
  item_identities[0] = 101u;
  item_identities[1] = 102u;
  item_identities[2] = 0xffffffffu;
  item_identities[3] = 0x99999999u;
  item_identities[4] = 0x99999999u;
  OpaqueFloatColor output{};
  check(EmpirePoliticalColor_00c32cd0(&distinct_record, &output) == &output);
  check(distinct_record.field_10 == 0x53dbcf3u);
  check(same_color(output, palette_colors[0]));
}

enum class OwnershipCall {
  root_range,
  record_type,
  record_state,
  metric,
  identity,
  current_identity,
  apply,
  current_star,
  current_mode,
  reference,
  count,
  cleanup_root,
  cleanup_word,
  cleanup_list,
  service,
  slot_20,
  slot_38,
  slot_40,
  slot_58,
  message_root,
  message_state,
  contains,
  insert,
  persistence_lookup,
  persistence_append,
};

const PoliticalOwnershipPorts kOwnershipDefaults = political_ownership_ports();
std::vector<OwnershipCall> ownership_trace;
OpaqueRecord ownership_root{};
OpaqueRecord ownership_candidates[7]{};
OpaqueRecord ownership_items[3]{};
OpaqueOwnershipChild ownership_children[3]{};
OpaqueRecord* ownership_roots[7]{};
OpaqueRecordRange ownership_range{};
int ownership_root_count = 7;
OpaqueOwnershipChild* ownership_child_entries[3][2]{};
OpaqueRecord* ownership_item_entries[3][3]{};
OpaqueRecord* rejected_type_record = nullptr;
OpaqueRecord* stateful_record = nullptr;
OpaqueRecord* low_metric_record = nullptr;
OpaqueRecord* nan_metric_record = nullptr;
OpaqueRecord* mismatched_identity_record = nullptr;
OpaqueRecord* current_star = nullptr;
OpaqueWord candidate_type = 5u;
OpaqueWord current_star_type = 5u;
OpaqueWord current_identity = 7u;
OpaqueWord common_identity = 7u;
OpaqueWord current_mode = 0u;
OpaqueWord current_reference = 0u;
std::int32_t current_star_count = 0;
int cleanup_root_index = 0;
OpaqueRecord* cleanup_roots[2]{};
OpaqueWord cleanup_words[2]{41u, 42u};
OpaqueMessageVtable message_vtable{};
OpaqueMessageService message_service{};
OpaqueMessageService* service_result = &message_service;
OpaqueMessageRoot message_root{};
OpaqueMessageState message_state{};
OpaqueMessageState* message_state_result = &message_state;
OpaqueWord message_value = 0x89abcdefu;
std::vector<OpaqueWord> message_slot_38;
std::vector<std::pair<OpaqueWord, OpaqueWord>> message_slot_40;
bool message_contains_result = false;
OpaquePersistenceTarget persistence_target{};
OpaquePersistenceTarget* persistence_result = &persistence_target;

OpaqueRecordRange* PKG13_E4_THISCALL model_root_range(OpaqueRecord* receiver) {
  check(receiver == &ownership_root);
  ownership_trace.push_back(OwnershipCall::root_range);
  ownership_range.begin = ownership_roots;
  ownership_range.end = ownership_roots + ownership_root_count;
  return &ownership_range;
}

OpaqueWord PKG13_E4_THISCALL model_ownership_type(OpaqueRecord* record) {
  ownership_trace.push_back(OwnershipCall::record_type);
  if (record == current_star) {
    return current_star_type;
  }
  if (record == rejected_type_record) {
    return 4u;
  }
  return candidate_type;
}

std::uint8_t PKG13_E4_THISCALL model_ownership_state(OpaqueRecord* record) {
  ownership_trace.push_back(OwnershipCall::record_state);
  return record == stateful_record ? 1u : 0u;
}

float PKG13_E4_THISCALL model_star_metric(OpaqueRecord* record) {
  ownership_trace.push_back(OwnershipCall::metric);
  if (record == low_metric_record) {
    return 99.0f;
  }
  if (record == nan_metric_record) {
    return std::numeric_limits<float>::quiet_NaN();
  }
  return 100.0f;
}

OpaqueWord PKG13_E4_THISCALL model_star_identity(OpaqueRecord* record) {
  ownership_trace.push_back(OwnershipCall::identity);
  return record == mismatched_identity_record ? common_identity + 1u
                                              : common_identity;
}

void PKG13_E4_CDECL model_ownership_apply(OpaqueRecord* record,
                                          std::int32_t identity) {
  check(record == &ownership_root);
  check(static_cast<OpaqueWord>(identity) == common_identity);
  ownership_trace.push_back(OwnershipCall::apply);
}

OpaqueWord PKG13_E4_CDECL model_current_identity() {
  ownership_trace.push_back(OwnershipCall::current_identity);
  return current_identity;
}

OpaqueRecord* PKG13_E4_CDECL model_current_star() {
  ownership_trace.push_back(OwnershipCall::current_star);
  return current_star;
}

OpaqueWord PKG13_E4_CDECL model_current_mode() {
  ownership_trace.push_back(OwnershipCall::current_mode);
  return current_mode;
}

OpaqueWord PKG13_E4_THISCALL model_record_reference(OpaqueRecord* record) {
  check(record == current_star);
  ownership_trace.push_back(OwnershipCall::reference);
  return current_reference;
}

std::int32_t PKG13_E4_CDECL model_current_star_count(OpaqueRecord* record) {
  check(record == current_star);
  ownership_trace.push_back(OwnershipCall::count);
  return current_star_count;
}

OpaqueRecord* PKG13_E4_CDECL model_cleanup_root() {
  ownership_trace.push_back(OwnershipCall::cleanup_root);
  return cleanup_roots[cleanup_root_index++];
}

OpaqueWord PKG13_E4_THISCALL model_cleanup_record_word(OpaqueRecord* record) {
  const int index = record == cleanup_roots[0] ? 0 : 1;
  ownership_trace.push_back(OwnershipCall::cleanup_word);
  return cleanup_words[index];
}

void PKG13_E4_THISCALL model_cleanup_list(OpaqueWord value) {
  check(value == cleanup_words[cleanup_root_index - 1]);
  ownership_trace.push_back(OwnershipCall::cleanup_list);
}

OpaqueWord PKG13_E4_THISCALL
model_message_slot_20(OpaqueMessageService* service) {
  check(service == &message_service);
  ownership_trace.push_back(OwnershipCall::slot_20);
  return message_value;
}

void PKG13_E4_THISCALL model_message_slot_38(OpaqueMessageService* service,
                                             OpaqueWord value) {
  check(service == &message_service);
  ownership_trace.push_back(OwnershipCall::slot_38);
  message_slot_38.push_back(value);
}

void PKG13_E4_THISCALL model_message_slot_40(OpaqueMessageService* service,
                                             OpaqueWord first,
                                             OpaqueWord second) {
  check(service == &message_service);
  ownership_trace.push_back(OwnershipCall::slot_40);
  message_slot_40.emplace_back(first, second);
}

void PKG13_E4_THISCALL model_message_slot_58(OpaqueMessageService* service) {
  check(service == &message_service);
  ownership_trace.push_back(OwnershipCall::slot_58);
}

OpaqueMessageService* PKG13_E4_CDECL model_message_service() {
  ownership_trace.push_back(OwnershipCall::service);
  return service_result;
}

OpaqueMessageRoot* PKG13_E4_CDECL model_message_root() {
  ownership_trace.push_back(OwnershipCall::message_root);
  return &message_root;
}

OpaqueMessageState* PKG13_E4_THISCALL
model_message_state(OpaqueMessageRoot* root) {
  check(root == &message_root);
  ownership_trace.push_back(OwnershipCall::message_state);
  return message_state_result;
}

bool PKG13_E4_THISCALL model_message_contains(OpaqueMessageState* state,
                                              OpaqueWord value) {
  check(state == message_state_result);
  check(value == 0x6627823u);
  ownership_trace.push_back(OwnershipCall::contains);
  return message_contains_result;
}

bool PKG13_E4_THISCALL model_message_insert(OpaqueMessageState* state,
                                            OpaqueWord value) {
  check(state == message_state_result);
  check(value == 0x6627823u);
  ownership_trace.push_back(OwnershipCall::insert);
  return true;
}

OpaquePersistenceTarget* PKG13_E4_CDECL
model_persistence_lookup(OpaqueWord value) {
  check(value == 0xee98e353u);
  ownership_trace.push_back(OwnershipCall::persistence_lookup);
  return persistence_result;
}

void PKG13_E4_THISCALL model_persistence_append(OpaquePersistenceTarget* target,
                                                OpaqueWord value) {
  check(target == persistence_result);
  check(value == 0xee98e353u);
  ownership_trace.push_back(OwnershipCall::persistence_append);
}

void install_ownership_ports() {
  PoliticalOwnershipPorts& ports = political_ownership_ports();
  StarOwnershipPorts& ownership = ports.ownership;
  ownership.root_range = model_root_range;
  ownership.record_type = model_ownership_type;
  ownership.record_state = model_ownership_state;
  ownership.star_metric = model_star_metric;
  ownership.star_identity = model_star_identity;
  ownership.ownership_apply = model_ownership_apply;
  ownership.current_identity = model_current_identity;
  ownership.current_star = model_current_star;
  ownership.current_mode = model_current_mode;
  ownership.record_reference = model_record_reference;
  ownership.current_star_count = model_current_star_count;
  ownership.cleanup_root = model_cleanup_root;
  ownership.cleanup_record_word = model_cleanup_record_word;
  ownership.cleanup_list = model_cleanup_list;
  MessagePorts& messages = ports.messages;
  messages.service = model_message_service;
  messages.root = model_message_root;
  messages.state = model_message_state;
  messages.contains = model_message_contains;
  messages.insert = model_message_insert;
  ports.persistence.lookup = model_persistence_lookup;
  ports.persistence.append = model_persistence_append;
}

void set_chain(OpaqueRecord* candidate, OpaqueOwnershipChild* child,
               OpaqueRecord* first, OpaqueRecord* second) {
  ownership_child_entries[0][0] = child;
  ownership_child_entries[0][1] = nullptr;
  candidate->field_15c = ownership_child_entries[0];
  candidate->field_160 = ownership_child_entries[0] + 1;
  ownership_item_entries[0][0] = first;
  ownership_item_entries[0][1] = second;
  ownership_item_entries[0][2] = nullptr;
  child->begin = ownership_item_entries[0];
  child->end = ownership_item_entries[0] + 2;
}

void reset_ownership_model() {
  political_ownership_ports() = kOwnershipDefaults;
  ownership_root = {};
  ownership_candidates[0] = {};
  ownership_candidates[1] = {};
  ownership_candidates[2] = {};
  ownership_candidates[3] = {};
  ownership_candidates[4] = {};
  ownership_candidates[5] = {};
  ownership_candidates[6] = {};
  ownership_items[0] = {};
  ownership_items[1] = {};
  ownership_items[2] = {};
  ownership_children[0] = {};
  ownership_children[1] = {};
  ownership_children[2] = {};
  ownership_root_count = 7;
  ownership_roots[0] = &ownership_candidates[0];
  ownership_roots[1] = &ownership_candidates[1];
  ownership_roots[2] = &ownership_candidates[2];
  ownership_roots[3] = &ownership_candidates[3];
  ownership_roots[4] = &ownership_candidates[4];
  ownership_roots[5] = &ownership_candidates[5];
  ownership_roots[6] = &ownership_candidates[6];
  rejected_type_record = &ownership_candidates[0];
  stateful_record = &ownership_candidates[1];
  low_metric_record = nullptr;
  nan_metric_record = nullptr;
  mismatched_identity_record = nullptr;
  candidate_type = 5u;
  current_star_type = 5u;
  current_identity = 7u;
  common_identity = 7u;
  current_mode = 0u;
  current_reference = reinterpret_cast<OpaqueWord>(&ownership_root);
  current_star_count = 0;
  current_star = &ownership_candidates[4];
  ownership_candidates[2].field_28 = 0u;
  ownership_candidates[3].field_28 = 1u;
  ownership_candidates[4].field_28 = 0u;
  ownership_candidates[5].field_28 = 2u;
  set_chain(&ownership_candidates[5], &ownership_children[0],
            &ownership_items[0], &ownership_items[1]);
  cleanup_root_index = 0;
  cleanup_roots[0] = &ownership_items[0];
  cleanup_roots[1] = &ownership_items[1];
  cleanup_words[0] = 41u;
  cleanup_words[1] = 42u;
  message_vtable = {};
  message_vtable.slot_20 = model_message_slot_20;
  message_vtable.slot_38 = model_message_slot_38;
  message_vtable.slot_40 = model_message_slot_40;
  message_vtable.slot_58 = model_message_slot_58;
  message_service = {&message_vtable};
  message_root = {};
  message_state = {};
  service_result = &message_service;
  message_state_result = &message_state;
  message_value = 0x89abcdefu;
  message_slot_38.clear();
  message_slot_40.clear();
  message_contains_result = false;
  persistence_target = {};
  persistence_result = &persistence_target;
  ownership_trace.clear();
  install_ownership_ports();
}

std::size_t ownership_index(OwnershipCall call) {
  for (std::size_t index = 0u; index < ownership_trace.size(); ++index) {
    if (ownership_trace[index] == call) {
      return index;
    }
  }
  return ownership_trace.size();
}

void test_candidate_filtering_and_common_identity() {
  reset_ownership_model();
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  bool found_current = false;
  for (OwnershipCall call : ownership_trace) {
    found_current = found_current || call == OwnershipCall::current_identity;
  }
  check(found_current);
  bool found_metric = false;
  for (OwnershipCall call : ownership_trace) {
    found_metric = found_metric || call == OwnershipCall::metric;
  }
  check(found_metric);
}

void test_empty_ranges_return_immediately() {
  reset_ownership_model();
  ownership_candidates[5].field_15c = ownership_child_entries[0];
  ownership_candidates[5].field_160 = ownership_child_entries[0];
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.back() == OwnershipCall::record_state);

  reset_ownership_model();
  ownership_candidates[5].field_15c = ownership_child_entries[0];
  ownership_candidates[5].field_160 = ownership_child_entries[0] + 1;
  ownership_children[0].begin = ownership_item_entries[0];
  ownership_children[0].end = ownership_item_entries[0];
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.back() == OwnershipCall::record_state);
}

void test_threshold_and_common_identity_early_returns() {
  reset_ownership_model();
  low_metric_record = &ownership_items[0];
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.back() == OwnershipCall::metric);

  reset_ownership_model();
  nan_metric_record = &ownership_items[0];
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  bool found_current = false;
  for (OwnershipCall call : ownership_trace) {
    found_current = found_current || call == OwnershipCall::current_identity;
  }
  check(found_current);

  reset_ownership_model();
  mismatched_identity_record = &ownership_items[1];
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.back() == OwnershipCall::identity);
}

void test_no_common_identity_returns() {
  reset_ownership_model();
  ownership_root_count = 0;
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.size() == 1u);
  check(ownership_trace[0] == OwnershipCall::root_range);
}

void test_distinct_current_branch_cleanup_order() {
  reset_ownership_model();
  current_identity = 8u;
  current_star_count = 2;
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.size() >= 27u);
  const std::size_t current = ownership_index(OwnershipCall::current_identity);
  const std::size_t apply = ownership_index(OwnershipCall::apply);
  const std::size_t current_star = ownership_index(OwnershipCall::current_star);
  const std::size_t mode = ownership_index(OwnershipCall::current_mode);
  const std::size_t reference = ownership_index(OwnershipCall::reference);
  const std::size_t count = ownership_index(OwnershipCall::count);
  check(current < apply);
  check(apply < current_star);
  check(current_star < mode);
  check(mode < reference);
  check(reference < count);
  check(ownership_trace.back() == OwnershipCall::cleanup_list);
  check(ownership_trace[ownership_trace.size() - 6u] ==
        OwnershipCall::cleanup_root);
  check(ownership_trace[ownership_trace.size() - 5u] ==
        OwnershipCall::cleanup_word);
  check(ownership_trace[ownership_trace.size() - 4u] ==
        OwnershipCall::cleanup_list);
  check(ownership_trace[ownership_trace.size() - 3u] ==
        OwnershipCall::cleanup_root);
  check(ownership_trace[ownership_trace.size() - 2u] ==
        OwnershipCall::cleanup_word);
}

void test_distinct_branch_short_circuits() {
  reset_ownership_model();
  current_identity = 8u;
  current_mode = 1u;
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.back() == OwnershipCall::current_mode);
}

void test_current_branch_callback_and_persistence_order() {
  reset_ownership_model();
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.size() >= 27u);
  const std::size_t current = ownership_index(OwnershipCall::current_identity);
  const std::size_t current_star = ownership_index(OwnershipCall::current_star);
  const std::size_t first_service = ownership_index(OwnershipCall::service);
  const std::size_t slot_20 = ownership_index(OwnershipCall::slot_20);
  const std::size_t second_service = first_service + 2u;
  const std::size_t slot_38 = ownership_index(OwnershipCall::slot_38);
  const std::size_t slot_40 = ownership_index(OwnershipCall::slot_40);
  const std::size_t slot_40_second = slot_40 + 1u;
  const std::size_t slot_58 = ownership_index(OwnershipCall::slot_58);
  const std::size_t message_root = ownership_index(OwnershipCall::message_root);
  const std::size_t message_state =
      ownership_index(OwnershipCall::message_state);
  const std::size_t contains = ownership_index(OwnershipCall::contains);
  const std::size_t insert = ownership_index(OwnershipCall::insert);
  const std::size_t lookup = ownership_index(OwnershipCall::persistence_lookup);
  const std::size_t append = ownership_index(OwnershipCall::persistence_append);
  check(current < current_star);
  check(current_star < first_service);
  check(first_service < slot_20);
  check(slot_20 + 1u == second_service);
  check(second_service < slot_38);
  check(slot_38 < slot_40);
  check(slot_40_second == slot_40 + 1u);
  check(slot_40_second < slot_58);
  check(slot_58 < message_root);
  check(message_root < message_state);
  check(message_state < contains);
  check(contains < insert);
  check(insert < lookup);
  check(lookup < append);
  check(message_slot_38.size() == 1u);
  check(message_slot_38[0] == 0x03475365u);
  check(message_slot_40.size() == 2u);
  check(message_slot_40[0].first == 0x3475381u);
  check(message_slot_40[0].second == 0xef7f5479u);
  check(message_slot_40[1].first == 0x3475385u);
  check(message_slot_40[1].second == message_value);
}

void test_current_branch_contains_and_null_paths() {
  reset_ownership_model();
  message_contains_result = true;
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.back() == OwnershipCall::contains);

  reset_ownership_model();
  current_star = nullptr;
  PoliticalOwnershipScan_00c8d060(&ownership_root);
  check(ownership_trace.back() == OwnershipCall::current_star);
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg13_e4_empire_wave3;
  test_cached_palette_path();
  test_current_transform_writeback_and_cache();
  test_current_black_cache_writeback();
  test_special_black_transform_keeps_local_output();
  test_special_nonblack_path_has_no_writeback();
  test_identity_shortcut();
  test_nearest_of_twelve_and_cleanup_order();
  test_nearest_default_and_null_entries();
  test_distance_association_order();
  test_candidate_filtering_and_common_identity();
  test_empty_ranges_return_immediately();
  test_threshold_and_common_identity_early_returns();
  test_no_common_identity_returns();
  test_distinct_current_branch_cleanup_order();
  test_distinct_branch_short_circuits();
  test_current_branch_callback_and_persistence_order();
  test_current_branch_contains_and_null_paths();
}
