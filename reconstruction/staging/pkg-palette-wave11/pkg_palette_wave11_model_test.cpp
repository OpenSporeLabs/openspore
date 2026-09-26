#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "pkg_palette_wave11.hpp"

namespace {

using namespace openspore::reconstruction::pkg_palette_wave11;

int g_failures = 0;
int g_checks = 0;

// The model tests assert 219 invariants. assert() compiles away under
// -DNDEBUG, which would leave the two NDEBUG configurations verifying nothing,
// so every assertion goes through this counter and main() reports a real
// failure path instead of returning zero unconditionally.
#define assert(condition)                                                      \
  do {                                                                         \
    ++g_checks;                                                                \
    if (!(condition)) {                                                        \
      ++g_failures;                                                            \
      std::fprintf(stderr, "FAIL %s:%d %s\n", __FILE__, __LINE__, #condition); \
    }                                                                          \
  } while (false)

struct OpaqueProbeContext {
  std::uint32_t word00;
  std::uint32_t word04;
  std::uint32_t word08;
};

std::uint32_t g_call_1 = 0U;
std::uint32_t g_call_2 = 0U;
std::uint32_t g_call_3 = 0U;
std::uint32_t g_call_4 = 0U;
std::uint32_t g_call_5 = 0U;
std::uint32_t g_call_6 = 0U;
std::uint32_t g_call_7 = 0U;
std::uint32_t g_call_8 = 0U;
std::uint32_t g_call_9 = 0U;
std::uint32_t g_call_10 = 0U;
std::uint32_t g_call_11 = 0U;
std::uint32_t g_call_12 = 0U;
std::uint32_t g_call_13 = 0U;
std::uint32_t g_call_14 = 0U;
std::uint32_t g_call_15 = 0U;
std::uint32_t g_call_16 = 0U;
std::uint32_t g_call_17 = 0U;
std::uint32_t g_call_18 = 0U;
std::uint32_t g_call_19 = 0U;
std::uint32_t g_call_20 = 0U;
std::uint32_t g_call_21 = 0U;
std::uint32_t g_call_22 = 0U;

template <typename Slot>
void set_slot_array(Slot* slot, OpaqueNode* const* array) {
  std::memcpy(slot, &array, sizeof(array));
}

struct OpaqueNodeProps {
  OpaqueApp app;
  OpaqueAppProps props;
};

void* g_alloc_block = nullptr;
std::uint32_t* g_fill_columns = nullptr;
std::uint32_t* g_fill_rows = nullptr;
OpaqueNode* g_node_table = nullptr;
OpaqueModel* g_model_table = nullptr;
OpaquePropertyList* g_list_table = nullptr;
OpaqueGameModeManager* g_mode_instance = nullptr;
OpaquePageLead* g_lead_table = nullptr;
OpaqueNode* g_pair_node = nullptr;

std::int32_t g_node_ctor_calls = 0;
std::int32_t g_node_slot01_calls = 0;
std::int32_t g_node_slot02_calls = 0;
std::int32_t g_node_slot04_calls = 0;
std::int32_t g_node_slot13_calls = 0;
std::int32_t g_node_slot24_calls = 0;
std::int32_t g_node_slot31_calls = 0;
std::int32_t g_model_slot14_calls = 0;
std::int32_t g_model_slot31_calls = 0;
std::int32_t g_model_slot48_calls = 0;
std::int32_t g_model_slot49_calls = 0;
std::int32_t g_list_slot01_calls = 0;
std::int32_t g_list_slot09_calls = 0;
std::int32_t g_list_slot11_calls = 0;
std::int32_t g_manager_slot31_calls = 0;
std::int32_t g_lead_slot01_calls = 0;
std::int32_t g_lead_slot66_calls = 0;
void* g_attach_payload = nullptr;
std::uint32_t g_node_slot31_flag = 0xdeadU;
std::uint32_t g_node_slot31_mode = 0xdeadU;
OpaqueNode* g_node_slot31_self = nullptr;
OpaqueNode* g_node_slot31_log[8] = {};
std::uint32_t g_node_slot31_flags[8] = {};
std::uint32_t g_node_slot31_modes[8] = {};
std::int32_t g_node_slot31_log_count = 0;
std::uint32_t g_model_slot31_flag = 0xdeadU;
std::uint32_t g_model_slot31_mode = 0xdeadU;
OpaqueModel* g_model_slot31_self = nullptr;
std::uint32_t g_model_slot31_flags[16] = {};
std::int32_t g_model_slot31_count = 0;

std::int32_t g_link_calls = 0;
OpaqueLink* g_link_script[8] = {};
std::int32_t g_link_at = 0;
OpaqueLink* g_link_result = nullptr;
std::int32_t g_manager_getter_calls = 0;
std::int32_t g_swatch_calls = 0;
void* g_swatch_self = nullptr;
void* g_swatch_arg = nullptr;

std::int32_t g_root_calls = 0;
std::int32_t g_category_calls = 0;
std::int32_t g_entry_calls = 0;
OpaqueCategoryList* g_root_child = nullptr;
OpaquePageList* g_category_child = nullptr;
OpaqueEntryList* g_entry_child = nullptr;

OpaquePropertyList* g_opened_list = nullptr;
std::uint32_t g_open_a = 0U;
std::uint32_t g_open_b = 0U;
OpaquePropertyList** g_open_out = nullptr;
std::uint32_t g_probe_a12a0_calls = 0;
std::uint32_t g_probe_a12a0_key = 0x7fffffffU;
std::uint32_t g_probe_a12a0_value = 0U;
bool g_probe_a12a0_result = true;
std::uint32_t g_probe_a07d0_calls = 0;
std::uint32_t g_probe_a07d0_keys[2] = {0U, 0U};
std::uint32_t g_probe_a07d0_counts[2] = {0U, 0U};
std::uint32_t* g_probe_a07d0_arrays[2] = {nullptr, nullptr};
OpaquePropertyList* g_probe_a07d0_self = nullptr;
std::uint32_t g_probe_a0ae0_calls = 0;
std::uint32_t g_probe_a0ae0_count = 0U;
std::uint32_t g_probe_a0ae0_offset = 0U;
std::uint32_t g_probe_a1160_calls = 0;
OpaqueFloat4 g_probe_a1160_value = {0.0F, 0.0F, 0.0F, 0.0F};
bool g_probe_a1160_result = true;
std::uint32_t g_probe_a1250_calls = 0;
std::uint32_t g_probe_a1250_key = 0U;
std::uint32_t g_probe_a1250_words[3] = {0U, 0U, 0U};
std::uint32_t g_prop_410370_calls = 0;
std::uint32_t g_prop_410370_key = 0U;
std::uint32_t g_prop_410370_value = 0U;

std::int32_t g_report_933960_calls = 0;
std::int32_t g_report_933960_span = 0;
std::int32_t g_free_f47380_calls = 0;
std::int32_t g_free_f47380_span = 0;
bool g_report_rewrites = false;
std::uint16_t g_report_heap[8] = {};

std::int32_t g_new_f473a0_calls = 0;
std::int32_t g_new_f473a0_size = 0;
std::uint32_t g_new_f473a0_tag = 0U;
OpaqueNode* g_node_init_calls = 0;
void* g_node_init_source = nullptr;
std::uint32_t g_node_init_threshold = 0U;
void* g_node_init_extra = nullptr;
bool g_node_init_result = true;
std::int32_t g_assign_calls = 0;
OpaqueNode** g_assign_slot = nullptr;
OpaqueNode* g_assign_value = nullptr;
std::int32_t g_grow_calls = 0;
OpaqueNode* g_grow_value = nullptr;
std::int32_t g_index_calls = 0;
std::int32_t g_index_result = 0;
std::int32_t g_toggle_calls = 0;
OpaqueNode* g_toggle_self = nullptr;
std::uint32_t g_toggle_arg = 0xdeadU;
std::uint32_t g_toggle_result = 0U;

bool g_property_found = true;
std::uint16_t g_property_tag = 0U;
std::uint32_t g_tag_keys[24] = {};
std::uint16_t g_tag_values[24] = {};
std::int32_t g_tag_count = 0;
std::uint8_t g_property_byte = 0U;
std::uint32_t g_property_word = 0U;
float g_property_float = 0.0F;
OpaqueProperty g_property = {};

const float* g_slot13_value = nullptr;
const float* g_slot13_second = nullptr;
const float* g_slot13_pair = nullptr;
const float* g_rect_first = nullptr;
const float* g_rect_second = nullptr;
const float* g_rect_pair = nullptr;
float g_model_box[4] = {0.0F, 0.0F, 0.0F, 0.0F};
float g_blend_box[4] = {0.0F, 0.0F, 0.0F, 0.0F};
float g_shift48_args[2][2] = {{0.0F, 0.0F}, {0.0F, 0.0F}};
std::int32_t g_shift48_count = 0;
float g_shift48_out[2] = {0.0F, 0.0F};
float g_shift48_results[2][2] = {{0.0F, 0.0F}, {0.0F, 0.0F}};
float g_shift49_args[2][2] = {{0.0F, 0.0F}, {0.0F, 0.0F}};
std::int32_t g_shift49_count = 0;
float g_shift49_out[2] = {0.0F, 0.0F};
float g_shift49_results[2] = {0.0F, 0.0F};
float g_apply_rect[4] = {0.0F, 0.0F, 0.0F, 0.0F};

void PKG_PALETTE_W11_THISCALL stub_node_slot01(OpaqueNode* node) {
  static_cast<void>(node);
  ++g_node_slot01_calls;
}

void PKG_PALETTE_W11_THISCALL stub_node_slot02(OpaqueNode* node) {
  static_cast<void>(node);
  ++g_node_slot02_calls;
}

OpaqueModel* PKG_PALETTE_W11_THISCALL stub_node_slot04(OpaqueNode* node) {
  static_cast<void>(node);
  ++g_node_slot04_calls;
  return g_model_table;
}

const float* PKG_PALETTE_W11_THISCALL stub_node_slot13(OpaqueNode* node) {
  ++g_node_slot13_calls;
  if (node == g_pair_node) {
    return g_slot13_pair;
  }
  if (node == g_node_table + 1) {
    return g_slot13_second;
  }
  return g_slot13_value;
}

void PKG_PALETTE_W11_THISCALL stub_node_slot24(OpaqueNode* node,
                                               const float* rect) {
  static_cast<void>(node);
  ++g_node_slot24_calls;
  if (rect != nullptr) {
    std::memcpy(g_apply_rect, rect, sizeof(g_apply_rect));
    if (node == g_node_table) {
      g_rect_first = rect;
    } else if (node == g_node_table + 1) {
      g_rect_second = rect;
    } else {
      g_rect_pair = rect;
    }
  }
}

void PKG_PALETTE_W11_THISCALL stub_node_slot31(OpaqueNode* node,
                                               std::uint32_t flag,
                                               std::uint32_t mode) {
  g_node_slot31_self = node;
  g_node_slot31_flag = flag;
  g_node_slot31_mode = mode;
  if (g_node_slot31_log_count < 8) {
    g_node_slot31_log[g_node_slot31_log_count] = node;
    g_node_slot31_flags[g_node_slot31_log_count] = flag;
    g_node_slot31_modes[g_node_slot31_log_count] = mode;
  }
  ++g_node_slot31_log_count;
  ++g_node_slot31_calls;
}

void PKG_PALETTE_W11_THISCALL stub_model_slot31(OpaqueModel* model,
                                                std::uint32_t flag,
                                                std::uint32_t mode) {
  g_model_slot31_self = model;
  g_model_slot31_flag = flag;
  g_model_slot31_mode = mode;
  if (g_model_slot31_count < 16) {
    g_model_slot31_flags[g_model_slot31_count] = flag;
  }
  ++g_model_slot31_count;
  ++g_model_slot31_calls;
}

const float* PKG_PALETTE_W11_THISCALL stub_model_slot14(OpaqueModel* model) {
  static_cast<void>(model);
  ++g_model_slot14_calls;
  return (g_model_slot14_calls % 2) == 1 ? g_model_box : g_blend_box;
}

void PKG_PALETTE_W11_THISCALL stub_model_slot48(OpaqueModel* model, float a,
                                                float b, float* out) {
  static_cast<void>(model);
  assert(g_shift48_count < 2);
  const std::int32_t slot = g_shift48_count;
  ++g_shift48_count;
  g_shift48_args[slot][0] = a;
  g_shift48_args[slot][1] = b;
  g_shift48_out[0] = a + 0.5F;
  g_shift48_out[1] = b + 1.5F;
  g_shift48_results[slot][0] = g_shift48_out[0];
  g_shift48_results[slot][1] = g_shift48_out[1];
  out[0] = g_shift48_out[0];
  out[1] = g_shift48_out[1];
}

void PKG_PALETTE_W11_THISCALL stub_model_slot49(OpaqueModel* model, float a,
                                                float b, float* out) {
  static_cast<void>(model);
  assert(g_shift49_count < 2);
  const std::int32_t slot = g_shift49_count;
  ++g_shift49_count;
  g_shift49_args[slot][0] = a;
  g_shift49_args[slot][1] = b;
  g_shift49_out[0] = a + 0.25F;
  g_shift49_out[1] = b + 0.75F;
  g_shift49_results[slot] = g_shift49_out[0];
  out[0] = g_shift49_out[0];
  out[1] = g_shift49_out[1];
}

void PKG_PALETTE_W11_THISCALL stub_list_slot01(OpaquePropertyList* list) {
  static_cast<void>(list);
  ++g_list_slot01_calls;
}

bool PKG_PALETTE_W11_THISCALL stub_list_slot09(OpaquePropertyList* list,
                                               std::uint32_t key,
                                               OpaqueProperty** out) {
  static_cast<void>(list);
  static_cast<void>(key);
  ++g_list_slot09_calls;
  g_property.field12 = g_property_tag;
  for (std::int32_t index = 0; index < g_tag_count; ++index) {
    if (g_tag_keys[index] == key) {
      g_property.field12 = g_tag_values[index];
    }
  }
  *out = &g_property;
  return g_property_found;
}

OpaquePropertyList* PKG_PALETTE_W11_THISCALL
stub_list_slot11(OpaquePropertyList* list, std::uint32_t a, std::uint32_t b,
                 OpaquePropertyList** out) {
  static_cast<void>(list);
  ++g_list_slot11_calls;
  g_open_a = a;
  g_open_b = b;
  g_open_out = out;
  if (g_opened_list == nullptr) {
    *out = nullptr;
    return nullptr;
  }
  *out = g_opened_list;
  return g_opened_list;
}

void PKG_PALETTE_W11_THISCALL stub_mode_slot31(OpaqueGameModeManager* manager,
                                               void* context,
                                               OpaqueTextBuffer* buffer) {
  static_cast<void>(manager);
  static_cast<void>(context);
  ++g_manager_slot31_calls;
  if (!g_report_rewrites) {
    return;
  }
  buffer->begin = g_report_heap;
  buffer->cursor = g_report_heap;
  buffer->end = g_report_heap + 4;
}

void PKG_PALETTE_W11_THISCALL stub_lead_slot01(OpaquePageLead* lead) {
  static_cast<void>(lead);
  ++g_lead_slot01_calls;
}

void PKG_PALETTE_W11_THISCALL stub_lead_slot66(OpaquePageLead* lead,
                                               void* payload) {
  static_cast<void>(lead);
  g_attach_payload = payload;
  ++g_lead_slot66_calls;
}

void install_tables() {
  static void* node_table[40];
  static void* model_table[80];
  static void* list_table[16];
  static void* mode_table[40];
  static void* lead_table[80];
  node_table[1] = reinterpret_cast<void*>(&stub_node_slot01);
  node_table[2] = reinterpret_cast<void*>(&stub_node_slot02);
  node_table[4] = reinterpret_cast<void*>(&stub_node_slot04);
  node_table[13] = reinterpret_cast<void*>(&stub_node_slot13);
  node_table[24] = reinterpret_cast<void*>(&stub_node_slot24);
  node_table[31] = reinterpret_cast<void*>(&stub_node_slot31);
  model_table[14] = reinterpret_cast<void*>(&stub_model_slot14);
  model_table[31] = reinterpret_cast<void*>(&stub_model_slot31);
  model_table[48] = reinterpret_cast<void*>(&stub_model_slot48);
  model_table[49] = reinterpret_cast<void*>(&stub_model_slot49);
  list_table[1] = reinterpret_cast<void*>(&stub_list_slot01);
  list_table[9] = reinterpret_cast<void*>(&stub_list_slot09);
  list_table[11] = reinterpret_cast<void*>(&stub_list_slot11);
  mode_table[31] = reinterpret_cast<void*>(&stub_mode_slot31);
  lead_table[1] = reinterpret_cast<void*>(&stub_lead_slot01);
  lead_table[66] = reinterpret_cast<void*>(&stub_lead_slot66);
  g_node_table[0].vtable = node_table;
  g_node_table[1].vtable = node_table;
  g_node_table[2].vtable = node_table;
  g_model_table[0].vtable = model_table;
  g_model_table[1].vtable = model_table;
  g_list_table->vtable = list_table;
  g_mode_instance->vtable = mode_table;
  g_lead_table->vtable = lead_table;
}

void reset_counters() {
  g_node_ctor_calls = 0;
  g_node_slot01_calls = 0;
  g_node_slot02_calls = 0;
  g_node_slot04_calls = 0;
  g_node_slot13_calls = 0;
  g_node_slot24_calls = 0;
  g_node_slot31_calls = 0;
  g_node_slot31_self = nullptr;
  g_node_slot31_flag = 0xdeadU;
  g_node_slot31_mode = 0xdeadU;
  g_node_slot31_log_count = 0;
  for (std::int32_t index = 0; index < 8; ++index) {
    g_node_slot31_log[index] = nullptr;
    g_node_slot31_flags[index] = 0xdeadU;
    g_node_slot31_modes[index] = 0xdeadU;
  }
  g_model_slot14_calls = 0;
  g_model_slot31_calls = 0;
  g_model_slot31_self = nullptr;
  g_model_slot31_flag = 0xdeadU;
  g_model_slot31_mode = 0xdeadU;
  g_model_slot31_count = 0;
  for (std::int32_t index = 0; index < 16; ++index) {
    g_model_slot31_flags[index] = 0xdeadU;
  }
  g_model_slot48_calls = 0;
  g_model_slot49_calls = 0;
  g_list_slot01_calls = 0;
  g_list_slot09_calls = 0;
  g_list_slot11_calls = 0;
  g_manager_slot31_calls = 0;
  g_lead_slot01_calls = 0;
  g_lead_slot66_calls = 0;
  g_attach_payload = nullptr;
  g_link_calls = 0;
  g_manager_getter_calls = 0;
  g_swatch_calls = 0;
  g_swatch_self = nullptr;
  g_swatch_arg = nullptr;
  g_root_calls = 0;
  g_category_calls = 0;
  g_entry_calls = 0;
  g_probe_a12a0_calls = 0;
  g_probe_a12a0_key = 0x7fffffffU;
  g_probe_a12a0_value = 0U;
  g_probe_a07d0_calls = 0;
  g_probe_a07d0_keys[0] = 0U;
  g_probe_a07d0_keys[1] = 0U;
  g_probe_a07d0_self = nullptr;
  g_probe_a0ae0_calls = 0;
  g_probe_a0ae0_count = 0U;
  g_probe_a0ae0_offset = 0U;
  g_probe_a1160_calls = 0;
  g_probe_a1160_result = true;
  g_probe_a1250_calls = 0;
  g_probe_a1250_key = 0U;
  g_prop_410370_calls = 0;
  g_prop_410370_key = 0U;
  g_prop_410370_value = 0U;
  g_report_933960_calls = 0;
  g_report_933960_span = 0;
  g_free_f47380_calls = 0;
  g_free_f47380_span = 0;
  g_report_rewrites = false;
  g_new_f473a0_calls = 0;
  g_new_f473a0_size = 0;
  g_new_f473a0_tag = 0U;
  g_node_init_calls = nullptr;
  g_node_init_source = nullptr;
  g_node_init_threshold = 0U;
  g_node_init_extra = nullptr;
  g_node_init_result = true;
  g_assign_calls = 0;
  g_assign_slot = nullptr;
  g_assign_value = nullptr;
  g_grow_calls = 0;
  g_grow_value = nullptr;
  g_index_calls = 0;
  g_index_result = 0;
  g_toggle_calls = 0;
  g_toggle_self = nullptr;
  g_toggle_arg = 0xdeadU;
  g_toggle_result = 0U;
  g_property_found = true;
  g_property_tag = 0x0dU;
  g_tag_count = 0;
  g_property_byte = 0U;
  g_property_word = 0U;
  g_property_float = 0.0F;
  g_property.field12 = 0x0dU;
  g_slot13_value = nullptr;
  g_slot13_second = nullptr;
  g_slot13_pair = nullptr;
  g_rect_first = nullptr;
  g_rect_second = nullptr;
  g_rect_pair = nullptr;
  g_shift48_count = 0;
  g_shift49_count = 0;
  g_shift48_args[0][0] = 0.0F;
  g_shift48_args[0][1] = 0.0F;
  g_shift48_args[1][0] = 0.0F;
  g_shift48_args[1][1] = 0.0F;
  g_shift49_args[0][0] = 0.0F;
  g_shift49_args[0][1] = 0.0F;
  g_shift49_args[1][0] = 0.0F;
  g_shift49_args[1][1] = 0.0F;
  g_shift48_out[0] = 0.0F;
  g_shift48_out[1] = 0.0F;
  g_shift49_out[0] = 0.0F;
  g_shift49_out[1] = 0.0F;
  g_apply_rect[0] = 0.0F;
  g_apply_rect[1] = 0.0F;
  g_apply_rect[2] = 0.0F;
  g_apply_rect[3] = 0.0F;
  g_model_box[0] = 0.0F;
  g_model_box[1] = 0.0F;
  g_model_box[2] = 0.0F;
  g_model_box[3] = 0.0F;
  g_blend_box[0] = 0.0F;
  g_blend_box[1] = 0.0F;
  g_blend_box[2] = 0.0F;
  g_blend_box[3] = 0.0F;
}

}

namespace openspore::reconstruction::pkg_palette_wave11 {

OpaqueLink* PKG_PALETTE_W11_THISCALL unresolved_005c9830(OpaqueLink* self) {
  static_cast<void>(self);
  ++g_link_calls;
  if (g_link_at < 8) {
    return g_link_script[g_link_at++];
  }
  return g_link_result;
}

void* PKG_PALETTE_W11_CDECL unresolved_00401020() {
  ++g_manager_getter_calls;
  return g_swatch_self;
}

void PKG_PALETTE_W11_THISCALL unresolved_005f0a60(void* self, void* arg) {
  ++g_swatch_calls;
  g_swatch_self = self;
  g_swatch_arg = arg;
}

OpaqueCategoryList* PKG_PALETTE_W11_THISCALL
unresolved_005c5de0(OpaqueRootList* self, std::int32_t index) {
  static_cast<void>(self);
  static_cast<void>(index);
  ++g_root_calls;
  return g_root_child;
}

OpaquePageList* PKG_PALETTE_W11_THISCALL
unresolved_005cae30(OpaqueCategoryList* self, std::int32_t index) {
  static_cast<void>(self);
  static_cast<void>(index);
  ++g_category_calls;
  return g_category_child;
}

OpaqueEntryList* PKG_PALETTE_W11_THISCALL
unresolved_005c1ce0(void* self, std::int32_t index) {
  static_cast<void>(self);
  static_cast<void>(index);
  ++g_entry_calls;
  return g_entry_child;
}

OpaquePropertyList* PKG_PALETTE_W11_CDECL unresolved_0067de30() {
  return g_list_table;
}

OpaqueGameModeManager* PKG_PALETTE_W11_CDECL unresolved_0067dcd0() {
  return g_mode_instance;
}

bool PKG_PALETTE_W11_CDECL unresolved_006a12a0(OpaquePropertyList* list,
                                               std::uint32_t key,
                                               std::uint32_t* out) {
  static_cast<void>(list);
  ++g_probe_a12a0_calls;
  g_probe_a12a0_key = key;
  *out = g_probe_a12a0_value;
  return g_probe_a12a0_result;
}

bool PKG_PALETTE_W11_CDECL unresolved_006a07d0(OpaquePropertyList* list,
                                               std::uint32_t key,
                                               std::uint32_t* count,
                                               std::uint32_t** array) {
  assert(g_probe_a07d0_calls < 2U);
  g_probe_a07d0_self = list;
  g_probe_a07d0_keys[g_probe_a07d0_calls] = key;
  *count = g_probe_a07d0_counts[g_probe_a07d0_calls];
  *array = g_probe_a07d0_arrays[g_probe_a07d0_calls];
  ++g_probe_a07d0_calls;
  return true;
}

bool PKG_PALETTE_W11_CDECL unresolved_006a0ae0(OpaquePropertyList* list,
                                               std::uint32_t key,
                                               std::uint32_t* count,
                                               OpaqueResourceKey* info) {
  static_cast<void>(list);
  static_cast<void>(key);
  ++g_probe_a0ae0_calls;
  *count = g_probe_a0ae0_count;
  info->word00 = g_probe_a0ae0_offset;
  return true;
}

bool PKG_PALETTE_W11_CDECL unresolved_006a1160(OpaquePropertyList* list,
                                               std::uint32_t key,
                                               OpaqueFloat4* out) {
  static_cast<void>(list);
  static_cast<void>(key);
  ++g_probe_a1160_calls;
  if (g_probe_a1160_result) {
    *out = g_probe_a1160_value;
  }
  return g_probe_a1160_result;
}

void PKG_PALETTE_W11_CDECL unresolved_006a1250(OpaquePropertyList* list,
                                               std::uint32_t key,
                                               OpaqueResourceKey* out) {
  static_cast<void>(list);
  ++g_probe_a1250_calls;
  g_probe_a1250_key = key;
  out->word00 = g_probe_a1250_words[0];
  out->word04 = g_probe_a1250_words[1];
  out->word08 = g_probe_a1250_words[2];
}

void PKG_PALETTE_W11_CDECL unresolved_00410370(OpaquePropertyList* list,
                                               std::uint32_t key,
                                               std::uint32_t* out) {
  static_cast<void>(list);
  ++g_prop_410370_calls;
  g_prop_410370_key = key;
  *out = g_prop_410370_value;
}

void PKG_PALETTE_W11_CDECL unresolved_00933960(OpaqueTextBuffer* buffer) {
  g_report_933960_span = static_cast<std::int32_t>(
      (reinterpret_cast<std::uintptr_t>(buffer->end) -
       reinterpret_cast<std::uintptr_t>(buffer->begin)) &
      0xfffffffeU);
  ++g_report_933960_calls;
}

void PKG_PALETTE_W11_CDECL unresolved_00f47380(void* block) {
  ++g_free_f47380_calls;
  g_free_f47380_span = static_cast<std::int32_t>(
      (reinterpret_cast<std::uintptr_t>(g_report_heap + 4) -
       reinterpret_cast<std::uintptr_t>(g_report_heap)) &
      0xfffffffeU);
  static_cast<void>(block);
}

void* PKG_PALETTE_W11_CDECL
unresolved_00f473a0(std::uint32_t size, std::uint32_t tag, std::uint32_t a,
                    std::uint32_t b, std::uint32_t c, std::uint32_t d) {
  ++g_new_f473a0_calls;
  g_new_f473a0_size = static_cast<std::int32_t>(size);
  g_new_f473a0_tag = tag;
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(d);
  if (g_alloc_block == nullptr) {
    return nullptr;
  }
  static_cast<OpaqueNode*>(g_alloc_block)->field48 = 0U;
  return g_alloc_block;
}

OpaqueNode* PKG_PALETTE_W11_THISCALL unresolved_005c66a0(OpaqueNode* self) {
  ++g_node_ctor_calls;
  self->vtable = g_node_table->vtable;
  return self;
}

bool PKG_PALETTE_W11_THISCALL unresolved_005c6810(OpaqueNode* self,
                                                  void* source,
                                                  std::uint32_t threshold,
                                                  void* extra) {
  g_node_init_calls = self;
  g_node_init_source = source;
  g_node_init_threshold = threshold;
  g_node_init_extra = extra;
  if (self != nullptr) {
    self->field48 = 0x1234U;
  }
  return g_node_init_result;
}

void* PKG_PALETTE_W11_THISCALL unresolved_005766e0(void* slot_ptr,
                                                   OpaqueNode* value) {
  ++g_assign_calls;
  g_assign_slot = static_cast<OpaqueNode**>(slot_ptr);
  g_assign_value = value;
  if (g_assign_slot != nullptr) {
    *g_assign_slot = value;
  }
  return slot_ptr;
}

void PKG_PALETTE_W11_THISCALL unresolved_005c8480(OpaqueNode** base,
                                                  OpaqueNode** cursor,
                                                  OpaqueNode** slot) {
  static_cast<void>(base);
  static_cast<void>(cursor);
  ++g_grow_calls;
  g_grow_value = g_node_table;
  if (slot != nullptr) {
    *slot = g_grow_value;
  }
}

std::int32_t PKG_PALETTE_W11_THISCALL
unresolved_005ca9c0(OpaquePageBuild* self) {
  static_cast<void>(self);
  ++g_index_calls;
  return g_index_result;
}

std::uint32_t PKG_PALETTE_W11_THISCALL unresolved_005c2ec0(OpaqueNode* self,
                                                           std::uint32_t flag) {
  ++g_toggle_calls;
  g_toggle_self = self;
  g_toggle_arg = flag;
  return g_toggle_result;
}

const std::uint8_t* PKG_PALETTE_W11_THISCALL
unresolved_0041e920(OpaqueProperty* self) {
  return self == &g_property ? &g_property_byte : nullptr;
}

const std::uint32_t* PKG_PALETTE_W11_THISCALL
unresolved_0041e990(OpaqueProperty* self) {
  return self == &g_property ? &g_property_word : nullptr;
}

const std::uint32_t* PKG_PALETTE_W11_THISCALL
unresolved_0041ea00(OpaqueProperty* self) {
  return self == &g_property ? &g_property_word : nullptr;
}

const float* PKG_PALETTE_W11_THISCALL
unresolved_0041ea70(OpaqueProperty* self) {
  return self == &g_property ? &g_property_float : nullptr;
}

}

namespace {

void test_resolve_link_tail() {
  OpaqueLink first = {};
  OpaqueLink second = {};
  OpaqueLink third = {};
  OpaqueLink dead = {};
  OpaqueLinkInner first_inner = {};
  OpaqueLinkInner second_inner = {};
  OpaqueLinkInner third_inner = {};
  first_inner.field58 = 0x11U;
  second_inner.field58 = 0x22U;
  third_inner.field58 = 0x33U;

  g_call_1 = palette_w11_resolve_link_tail_005c2e00(&first);
  assert(g_call_1 == 0U);

  first.field6c = &first_inner;
  g_link_calls = 0;
  g_link_at = 0;
  g_call_2 = palette_w11_resolve_link_tail_005c2e00(&first);
  assert(g_call_2 == 0x11U);
  assert(g_link_calls == 0);

  first.field9c = &second;
  g_link_script[0] = nullptr;
  g_link_script[1] = nullptr;
  g_link_calls = 0;
  g_link_at = 0;
  g_call_3 = palette_w11_resolve_link_tail_005c2e00(&first);
  assert(g_call_3 == 0x11U);
  assert(g_link_calls == 1);

  g_link_script[0] = &second;
  g_link_script[1] = &second;
  second.field6c = &second_inner;
  g_link_calls = 0;
  g_link_at = 0;
  g_call_4 = palette_w11_resolve_link_tail_005c2e00(&first);
  assert(g_call_4 == 0x22U);
  assert(g_link_calls == 2);

  second.field9c = &third;
  g_link_script[2] = &third;
  g_link_script[3] = &third;
  third.field6c = &third_inner;
  g_link_calls = 0;
  g_link_at = 0;
  g_call_5 = palette_w11_resolve_link_tail_005c2e00(&first);
  assert(g_call_5 == 0x33U);
  assert(g_link_calls == 4);

  third.field9c = &dead;
  g_link_script[4] = &dead;
  g_link_script[5] = &dead;
  g_link_calls = 0;
  g_link_at = 0;
  g_call_6 = palette_w11_resolve_link_tail_005c2e00(&first);
  assert(g_call_6 == 0U);
  assert(g_link_calls == 6);

  g_link_script[0] = nullptr;
  g_link_script[1] = &dead;
  g_link_calls = 0;
  g_link_at = 0;
  g_call_7 = palette_w11_resolve_link_tail_005c2e00(&first);
  assert(g_call_7 == 0x11U);
  assert(g_link_calls == 1);
}

void test_release_page_hold() {
  OpaquePageHost host = {};
  reset_counters();

  host.field18 = g_lead_table;
  palette_w11_release_page_hold_005c7320(&host);
  assert(g_manager_getter_calls == 0);
  assert(g_swatch_calls == 0);
  assert(g_lead_slot66_calls == 1);
  assert(g_attach_payload == &host.field08);

  host.field18 = nullptr;
  host.field14 = g_lead_table;
  palette_w11_release_page_hold_005c7320(&host);
  assert(g_manager_getter_calls == 1);
  assert(g_swatch_calls == 1);
  assert(g_swatch_arg == g_lead_table);
  assert(g_lead_slot01_calls == 1);
  assert(host.field14 == nullptr);
  assert(g_lead_slot66_calls == 1);
}

template <typename T>
T* as_slot(void* address) {
  return reinterpret_cast<T*>(address);
}

void test_walk_has_leaf() {
  static OpaqueCategoryList cats[2];
  static OpaquePageList pages[2];
  static OpaqueEntryList entries[2];
  OpaqueRootList root = {};
  OpaqueWalkIndex walk = {};
  OpaqueCategoryList* cat_span[2] = {&cats[0], &cats[1]};
  OpaqueEntryList* entry_span[2] = {&entries[0], &entries[1]};

  cats[0].field0c = entry_span;
  cats[0].field10 = &entry_span[1];
  cats[0].field34 = cat_span;
  cats[0].field38 = &cat_span[1];
  pages[0].field0c = entry_span;
  pages[0].field10 = &entry_span[1];
  entries[0].field70 = entry_span;
  entries[0].field74 = &entry_span[0];
  root.field0c = as_slot<OpaqueCategoryList>(cat_span);
  root.field10 = as_slot<OpaqueCategoryList>(&cat_span[1]);
  walk.field0c = &root;
  g_root_child = &cats[0];
  g_category_child = &pages[0];
  g_entry_child = &entries[0];

  reset_counters();
  walk.field10 = 0;
  walk.field14 = 0;
  walk.field18 = 0;
  walk.field1c = 0;
  g_call_8 = palette_w11_walk_has_leaf_005c7c10(&walk);
  assert(!g_call_8);
  assert(g_root_calls == 1);
  assert(g_category_calls == 1);
  assert(g_entry_calls == 2);
  assert(walk.field10 == 1);
  assert(walk.field14 == 0);
  assert(walk.field18 == 0);
  assert(walk.field1c == 0);

  reset_counters();
  walk.field10 = 0;
  walk.field14 = 0;
  walk.field18 = 0;
  walk.field1c = 0;
  cats[0].field10 = entry_span;
  g_call_9 = palette_w11_walk_has_leaf_005c7c10(&walk);
  assert(!g_call_9);
  assert(g_root_calls == 1);
  assert(g_category_calls == 1);
  assert(g_entry_calls == 1);
  assert(walk.field10 == 1);

  reset_counters();
  walk.field10 = 0;
  walk.field14 = 0;
  walk.field18 = 0;
  walk.field1c = 0;
  cats[0].field10 = &entry_span[1];
  cats[0].field38 = cat_span;
  entries[0].field74 = &entry_span[1];
  g_call_10 = palette_w11_walk_has_leaf_005c7c10(&walk);
  assert(g_call_10);
  assert(g_root_calls == 1);
  assert(g_category_calls == 0);
  assert(g_entry_calls == 1);
  assert(walk.field1c == 0);
  assert(walk.field10 == 0);
  assert(walk.field14 == 0);
  assert(walk.field18 == 0);

  reset_counters();
  walk.field10 = 0;
  walk.field14 = 0;
  walk.field18 = 0;
  walk.field1c = 0;
  cats[0].field34 = &cat_span[1];
  cats[0].field38 = &cat_span[1];
  cats[0].field10 = &entry_span[1];
  pages[0].field10 = &entry_span[1];
  entries[0].field74 = entry_span;
  g_call_11 = palette_w11_walk_has_leaf_005c7c10(&walk);
  assert(!g_call_11);
  assert(g_root_calls == 1);
  assert(g_category_calls == 0);
  assert(g_entry_calls == 1);
  assert(walk.field10 == 1);
}

void set_tag(std::uint32_t key, std::uint16_t tag) {
  assert(g_tag_count < 24);
  g_tag_keys[g_tag_count] = key;
  g_tag_values[g_tag_count] = tag;
  ++g_tag_count;
}

void arm_tags() {
  g_tag_count = 0;
  set_tag(0x21953e9U, 0x0dU);
  set_tag(0x21953eaU, 0x0dU);
  set_tag(0xb0a1610aU, 0x0dU);
  set_tag(0xb0a16109U, 0x0dU);
  set_tag(0xb0a1610dU, 0x0dU);
  set_tag(0xb0a1610cU, 0x0dU);
  set_tag(0x5adc53bU, 0x01U);
  set_tag(0x5b9a649U, 0x0dU);
  set_tag(0x5adc172U, 0x0dU);
  set_tag(0x5adc18dU, 0x0dU);
  set_tag(0x5b5566eU, 0x01U);
  set_tag(0x5b55d89U, 0x01U);
  set_tag(0x30a95517U, 0x09U);
  set_tag(0x33a8ec2U, 0x09U);
  set_tag(0x9591f67U, 0x0aU);
  set_tag(0x1b8716d6U, 0x09U);
  set_tag(0x52c798eU, 0x01U);
  set_tag(0x56e8657U, 0x01U);
}

void arm_fill() {
  g_opened_list = g_list_table;
  g_probe_a12a0_value = 0x5555U;
  g_probe_a0ae0_count = 2U;
  g_probe_a07d0_counts[0] = 2U;
  g_probe_a07d0_arrays[0] = g_fill_columns;
  g_probe_a07d0_counts[1] = 2U;
  g_probe_a07d0_arrays[1] = g_fill_rows;
  g_prop_410370_value = 0x40U;
}

void test_fill_node_array() {
  OpaquePageBuild build = {};
  OpaqueNodeProps props = {};
  OpaqueNode* grid[4] = {};
  OpaqueNode storage = {};
  OpaqueNode held = {};
  OpaqueProbeContext context = {0x1111U, 0x2222U, 0x3333U};
  std::uint32_t expected = 0x5555U;
  std::uint32_t columns[8] = {1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
  std::uint32_t rows[8] = {0U, 9U, 0U, 0U, 0U, 0U, 0U, 0U};

  install_tables();
  g_fill_columns = columns;
  g_fill_rows = rows;
  held.vtable = g_node_table->vtable;
  storage.vtable = g_node_table->vtable;
  g_dword_015fd918 = &props.app;
  props.app.field3c = &props.props;
  props.props.field118 = 1U;
  g_alloc_block = &storage;

  reset_counters();
  g_opened_list = nullptr;
  palette_w11_fill_node_array_005c7ff0(&build, &expected, &context, nullptr);
  assert(g_list_slot11_calls == 1);
  assert(g_open_a == 0x1111U);
  assert(g_open_b == 0x3333U);
  assert(g_probe_a12a0_calls == 0);
  assert(g_list_slot01_calls == 0);

  reset_counters();
  g_opened_list = g_list_table;
  g_probe_a12a0_value = 0x7777U;
  palette_w11_fill_node_array_005c7ff0(&build, &expected, &context, nullptr);
  assert(g_list_slot01_calls == 1);
  assert(g_probe_a0ae0_calls == 0);
  assert(g_new_f473a0_calls == 0);

  reset_counters();
  arm_fill();
  g_probe_a0ae0_offset = 0x10U;
  g_prop_410370_value = 0x40U;
  build.field50 = 2U;
  build.field54 = 2U;
  build.field70 = grid;
  build.field74 = grid;
  build.field78 = &grid[4];
  palette_w11_fill_node_array_005c7ff0(&build, &expected, &context, nullptr);
  assert(g_probe_a0ae0_calls == 1);
  assert(g_probe_a07d0_calls == 2);
  assert(g_probe_a07d0_keys[0] == 0xf8e99c4fU);
  assert(g_probe_a07d0_keys[1] == 0x22c47931U);
  assert(g_probe_a07d0_self == g_list_table);
  assert(g_prop_410370_calls == 1);
  assert(g_prop_410370_key == 0x5383435U);
  assert(g_new_f473a0_calls == 1);
  assert(g_new_f473a0_size == 0x54);
  assert(g_new_f473a0_tag == 0x13eb430U);
  assert(g_node_ctor_calls == 1);
  assert(g_node_init_calls == &storage);
  assert(g_node_init_source == &columns[4]);
  assert(g_node_init_threshold == 0x40U);
  assert(g_assign_calls == 1);
  assert(g_assign_slot == &grid[1]);
  assert(g_assign_value == &storage);
  assert(g_node_slot02_calls == 1);
  assert(g_list_slot01_calls == 1);

  reset_counters();
  arm_fill();
  rows[1] = 7U;
  palette_w11_fill_node_array_005c7ff0(&build, &expected, &context, nullptr);
  rows[1] = 9U;
  assert(g_new_f473a0_calls == 0);
  assert(g_manager_slot31_calls == 2);
  assert(g_free_f47380_calls == 0);

  reset_counters();
  arm_fill();
  g_report_rewrites = true;
  palette_w11_fill_node_array_005c7ff0(&build, &expected, &context, nullptr);
  rows[1] = 9U;
  assert(g_manager_slot31_calls == 2);
  assert(g_free_f47380_calls == 2);
  assert(g_free_f47380_span == 8);
  g_report_rewrites = false;

  reset_counters();
  arm_fill();
  grid[1] = &held;
  held.field48 = 0x99U;
  palette_w11_fill_node_array_005c7ff0(&build, &expected, &context, nullptr);
  assert(g_new_f473a0_calls == 0);
  assert(g_node_slot01_calls == 1);
  assert(g_node_slot02_calls == 1);
  assert(g_assign_calls == 0);

  reset_counters();
  arm_fill();
  held.field48 = 0x40U;
  palette_w11_fill_node_array_005c7ff0(&build, &expected, &context, nullptr);
  assert(g_new_f473a0_calls == 0);
  assert(g_report_933960_calls == 1);
  assert(g_node_slot02_calls == 1);
  assert(g_assign_calls == 0);

  reset_counters();
  arm_fill();
  held.field48 = 0x01U;
  g_node_init_result = false;
  palette_w11_fill_node_array_005c7ff0(&build, &expected, &context, nullptr);
  assert(g_report_933960_calls == 1);
  assert(g_assign_calls == 0);
  assert(g_node_slot02_calls == 2);
  g_node_init_result = true;
  grid[1] = nullptr;
}

void test_load_page_state() {
  OpaquePageBuild build = {};
  OpaqueNode* grid[64] = {};
  OpaqueProperty* probe_slot = nullptr;
  OpaqueProperty* hold_slot[3] = {nullptr, nullptr, nullptr};
  OpaquePropertyList* follow_list = g_list_table;
  std::uint32_t follow_bits = 0U;

  install_tables();
  build.field70 = grid;
  build.field74 = grid;
  build.field78 = &grid[64];
  std::memcpy(&follow_bits, &follow_list, sizeof(follow_bits));
  std::memcpy(&g_probe_a1160_value.field08, &follow_bits, sizeof(follow_bits));

  reset_counters();
  g_opened_list = g_list_table;
  arm_tags();
  g_property_tag = 0x0dU;
  g_property_byte = 0x5aU;
  g_property_word = 7U;
  g_property_float = 1.5F;
  g_probe_a1160_value.field00 = 1.0F;
  g_probe_a1160_value.field04 = 2.0F;
  g_probe_a1160_value.field0c = 4.0F;
  g_probe_a1250_words[0] = 0xabcU;

  g_call_12 =
      palette_w11_load_page_state_005c85d0(&build, &probe_slot, hold_slot);
  assert(g_call_12);
  assert(g_list_slot11_calls == 1);
  assert(g_open_a == 0U);
  assert(g_open_b == 0U);
  assert(g_list_slot09_calls == 18);
  assert(build.field14.as_float == 1.5F);
  assert(build.field18.as_float == 1.5F);
  assert(build.field28 == 1.5F);
  assert(build.field24 == 1.5F);
  assert(build.field20.as_float == 1.5F);
  assert(build.field1c.as_float == 1.5F);
  assert(build.field38.as_float == 1.0F);
  assert(build.field30 == 2.0F);
  assert(build.field3c != 0.0F);
  assert(build.field34.as_float == 4.0F);
  assert(build.field4c.as_float == 1.5F);
  assert(build.field40 == 1.5F);
  assert(build.field44 == 1.5F);
  assert(build.field48.bytes.byte48 == 0x5aU);
  assert(build.field48.bytes.byte49 == 0x5aU);
  assert(build.field48.bytes.byte4a == 0x5aU);
  assert(build.field2c == 0x5aU);
  assert(build.field2d == 0x5aU);
  assert(g_probe_a1160_calls == 1);
  assert(g_probe_a1250_calls == 1);
  assert(g_probe_a1250_key == 0xc84067f7U);
  assert(build.field64.word00 == 0xabcU);
  assert(build.field58 == 7U);
  assert(build.field5c == 7U);
  assert(build.field50 == 7U);
  assert(build.field54 == 7U);
  assert(build.field0c == reinterpret_cast<std::uint32_t>(hold_slot));
  assert(build.field74 == &grid[49]);
  assert(g_grow_calls == 0);
  assert(g_list_slot01_calls == 1);

  reset_counters();
  g_opened_list = g_list_table;
  arm_tags();
  g_property_tag = 0x0dU;
  g_property_byte = 0U;
  g_property_word = 2U;
  g_property_float = 0.25F;
  build.field70 = grid;
  build.field74 = grid;
  build.field78 = &grid[4];
  g_call_13 =
      palette_w11_load_page_state_005c85d0(&build, &probe_slot, hold_slot);
  assert(g_call_13);
  assert(build.field50 == 2U);
  assert(build.field54 == 2U);
  assert(g_grow_calls == 0);
  assert(build.field74 == &grid[4]);
  assert(grid[0] == nullptr);
  assert(grid[3] == nullptr);

  reset_counters();
  g_opened_list = g_list_table;
  arm_tags();
  g_property_tag = 0x0dU;
  g_property_byte = 0U;
  g_property_word = 3U;
  g_property_float = 0.25F;
  build.field70 = grid;
  build.field74 = &grid[4];
  build.field78 = &grid[4];
  g_call_14 =
      palette_w11_load_page_state_005c85d0(&build, &probe_slot, hold_slot);
  assert(g_call_14);
  assert(build.field50 == 3U);
  assert(build.field54 == 3U);
  assert(g_grow_calls == 9);
  assert(g_node_slot02_calls == 9);
  assert(build.field74 == &grid[4]);

  reset_counters();
  g_opened_list = g_list_table;
  g_tag_count = 0;
  set_tag(0x5adc53bU, 0x01U);
  set_tag(0x5b5566eU, 0x01U);
  set_tag(0x5b55d89U, 0x01U);
  set_tag(0x52c798eU, 0x01U);
  set_tag(0x56e8657U, 0x01U);
  g_property_tag = 0x0dU;
  g_property_byte = 0x5aU;
  g_property_word = 0U;
  g_property_float = 0.0F;
  g_probe_a1160_result = false;
  build.field50 = 0U;
  build.field54 = 0U;
  build.field58 = 0U;
  build.field5c = 0U;
  build.field4c.as_float = 0.0F;
  build.field48.bytes.byte48 = 0x11U;
  g_call_15 =
      palette_w11_load_page_state_005c85d0(&build, &probe_slot, hold_slot);
  assert(g_call_15);
  assert(build.field48.bytes.byte48 == 0x5aU);
  assert(build.field48.bytes.byte49 == 0x5aU);
  assert(build.field48.bytes.byte4a == 0x5aU);
  assert(build.field2c == 0U);
  assert(build.field2d == 0U);
  assert(build.field44 == 0.0F);
  assert(build.field50 == 0U);
  assert(build.field54 == 0U);
  assert(build.field58 == 0U);
  assert(build.field5c == 0U);
  assert(build.field4c.as_float == 0.0F);
  assert(g_grow_calls == 0);
  g_probe_a1160_result = true;

  g_opened_list = nullptr;
  reset_counters();
  g_call_16 =
      palette_w11_load_page_state_005c85d0(&build, &probe_slot, hold_slot);
  assert(!g_call_16);
  assert(g_list_slot01_calls == 0);

  g_opened_list = g_list_table;
  reset_counters();
  arm_tags();
  g_property_tag = 0x0dU;
  g_probe_a1160_value.field00 = 1.0F;
  g_call_17 =
      palette_w11_load_page_state_005c85d0(&build, &probe_slot, hold_slot);
  assert(g_call_17);
  assert(g_probe_a12a0_calls == 0);
  assert(build.field0c == reinterpret_cast<std::uint32_t>(hold_slot));
}

void arm_place(const float* first, const float* second, const float* pair) {
  g_slot13_value = first;
  g_slot13_second = second;
  g_slot13_pair = pair;
  g_model_box[0] = 1.0F;
  g_model_box[2] = 4.0F;
  g_blend_box[0] = 2.0F;
  g_blend_box[2] = 9.0F;
  g_index_result = 2;
  g_toggle_result = 0x5eU;
}

void test_place_page_nodes() {
  OpaquePageBuild build = {};
  OpaqueNode pages[10] = {};
  OpaqueNode pair_holder[2] = {};
  OpaqueNode ids[3] = {};
  OpaqueNode* page_array[10] = {};
  OpaqueNode* id_array[3] = {};
  float first_rect[4] = {0.0F, 1.0F, 2.0F, 3.0F};
  float second_rect[4] = {0.0F, 4.0F, 5.0F, 6.0F};
  float pair_rect[4] = {0.0F, 7.0F, 8.0F, 9.0F};

  install_tables();
  for (std::size_t index = 0; index < 10U; ++index) {
    page_array[index] = &pages[index];
    pages[index].vtable = g_node_table->vtable;
  }
  for (std::size_t index = 0; index < 3U; ++index) {
    id_array[index] = &ids[index];
    ids[index].vtable = g_node_table->vtable;
  }
  pair_holder[1].vtable = g_node_table->vtable;
  g_pair_node = &pair_holder[1];

  reset_counters();
  arm_place(first_rect, second_rect, pair_rect);
  set_slot_array(&build.field48, page_array);
  set_slot_array(&build.field4c, &page_array[10]);
  set_slot_array(&build.field34, id_array);
  set_slot_array(&build.field38, &id_array[3]);
  build.field14.as_node = g_node_table;
  build.field18.as_node = g_node_table + 1;
  build.field1c.as_node = g_node_table + 2;
  build.field20.as_node = pair_holder;
  build.field60 = 0U;
  build.field64.word00 = reinterpret_cast<std::uint32_t>(&ids[2]);

  g_call_18 = palette_w11_place_page_nodes_005ca9f0(&build);
  assert(g_call_18 == 0x5eU);
  assert(g_model_slot31_calls == 10);
  for (std::int32_t index = 0; index < 9; ++index) {
    assert(g_model_slot31_flags[index] == 1U);
  }
  assert(g_model_slot31_flags[9] == 0U);
  assert(g_model_slot31_mode == 1U);
  assert(g_index_calls == 1);
  assert(g_model_slot14_calls == 2);
  assert(g_shift48_args[0][0] == -3.0F);
  assert(g_shift48_args[0][1] == 0.0F);
  assert(g_shift48_results[0][0] == -2.5F);
  assert(g_shift48_results[0][1] == 1.5F);
  assert(g_shift49_args[0][0] == -2.5F);
  assert(g_shift49_args[0][1] == 1.5F);
  assert(g_shift49_results[0] == -2.25F);
  assert(g_shift48_args[1][0] == -2.25F);
  assert(g_shift48_args[1][1] == 0.0F);
  assert(g_shift48_results[1][0] == -1.75F);
  assert(g_shift48_results[1][1] == 1.5F);
  assert(g_shift49_args[1][0] == -1.75F);
  assert(g_shift49_args[1][1] == 1.5F);
  assert(g_shift49_results[1] == -1.5F);
  assert(g_node_slot24_calls == 3);
  assert(g_rect_first != nullptr);
  assert(g_rect_second != nullptr);
  assert(g_rect_pair != nullptr);
  assert(g_node_slot13_calls == 3);
  assert(g_node_slot31_calls == 4);
  assert(g_node_slot31_log[0] == g_node_table + 2);
  assert(g_node_slot31_flags[0] == 0U);
  assert(g_node_slot31_modes[0] == 1U);
  assert(g_node_slot31_log[1] == &pair_holder[1]);
  assert(g_node_slot31_flags[1] == 1U);
  assert(g_node_slot31_log[2] == g_node_table);
  assert(g_node_slot31_flags[2] == 1U);
  assert(g_node_slot31_log[3] == g_node_table + 1);
  assert(g_node_slot31_flags[3] == 1U);
  assert(g_toggle_calls == 1);
  assert(g_toggle_arg == 1U);
  assert(g_toggle_self == reinterpret_cast<OpaqueNode*>(&build.field64));

  reset_counters();
  arm_place(first_rect, second_rect, pair_rect);
  set_slot_array(&build.field48, page_array);
  set_slot_array(&build.field4c, &page_array[10]);
  set_slot_array(&build.field34, id_array);
  set_slot_array(&build.field38, &id_array[3]);
  build.field64.word00 = 0x99U;
  g_call_19 = palette_w11_place_page_nodes_005ca9f0(&build);
  assert(g_call_19 == 0x5eU);
  assert(g_index_calls == 0);
  assert(g_node_slot24_calls == 0);
  assert(g_model_slot31_calls == 10);
  assert(g_toggle_calls == 1);
  assert(g_toggle_arg == 0U);

  reset_counters();
  arm_place(first_rect, second_rect, pair_rect);
  set_slot_array(&build.field48, page_array);
  set_slot_array(&build.field4c, &page_array[10]);
  set_slot_array(&build.field34, id_array);
  set_slot_array(&build.field38, &id_array[3]);
  build.field60 = 1U;
  build.field64.word00 = 0x99U;
  g_call_20 = palette_w11_place_page_nodes_005ca9f0(&build);
  assert(g_call_20 == 0x5eU);
  assert(g_toggle_arg == 0U);
  assert(g_node_slot24_calls == 0);

  reset_counters();
  arm_place(first_rect, second_rect, pair_rect);
  set_slot_array(&build.field48, page_array);
  set_slot_array(&build.field4c, page_array);
  set_slot_array(&build.field34, id_array);
  set_slot_array(&build.field38, &id_array[3]);
  build.field60 = 0U;
  build.field64.word00 = 0x99U;
  g_call_21 = palette_w11_place_page_nodes_005ca9f0(&build);
  assert(g_call_21 == 0x5eU);
  assert(g_model_slot31_calls == 0);
  assert(g_node_slot24_calls == 0);
  assert(g_toggle_calls == 1);

  reset_counters();
  arm_place(first_rect, second_rect, pair_rect);
  set_slot_array(&build.field48, page_array);
  set_slot_array(&build.field4c, &page_array[10]);
  set_slot_array(&build.field34, id_array);
  set_slot_array(&build.field38, &id_array[3]);
  build.field14.as_node = nullptr;
  build.field64.word00 = reinterpret_cast<std::uint32_t>(&ids[1]);
  g_call_22 = palette_w11_place_page_nodes_005ca9f0(&build);
  assert(g_call_22 == 0x5eU);
  assert(g_node_slot31_calls == 1);
  assert(g_node_slot24_calls == 0);
  assert(g_index_calls == 0);
}

}

int main() {
  static OpaqueNode node_table[3];
  static OpaqueModel model_table[2];
  static OpaquePropertyList list_table;
  static OpaqueGameModeManager manager_table;
  static OpaquePageLead lead_table;
  g_node_table = node_table;
  g_model_table = model_table;
  g_list_table = &list_table;
  g_mode_instance = &manager_table;
  g_lead_table = &lead_table;
  install_tables();
  test_resolve_link_tail();
  test_release_page_hold();
  test_walk_has_leaf();
  test_fill_node_array();
  test_load_page_state();
  test_place_page_nodes();
  std::printf("pkg palette wave11 model: checks=%d failures=%d\n", g_checks,
              g_failures);
  return g_failures == 0 ? 0 : 1;
}
