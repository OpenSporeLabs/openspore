#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>
#include <vector>

#include "pkg_advanced_palette_wave11.hpp"

namespace openspore::reconstruction::pkg_advanced_palette_wave11 {

int g_failures = 0;

std::uint32_t bits_of(float value) {
  std::uint32_t out = 0U;
  std::memcpy(&out, &value, sizeof(out));
  return out;
}

std::uint32_t bits_of(const void *value) {
  return reinterpret_cast<std::uint32_t>(value);
}

void check(bool ok, const char *what) {
  if (!ok) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

struct Trace {
  std::uint32_t alloc_calls;
  std::uint32_t alloc_bytes;
  std::uint32_t alloc_grants;
  std::uint32_t alloc_deny;

  std::uint32_t ctor_calls;
  std::uint32_t retain_item;
  std::uint32_t release_item;
  std::uint32_t index_query;

  std::uint32_t swatch_present;
  std::uint32_t swatch_manager;
  std::uint32_t swatch_host;
  std::uint32_t swatch_release;
  std::uint32_t swatch_release_arg;
  std::uint32_t swatch_slot[8];
  std::uint32_t swatch_arg0[8];
  std::uint32_t swatch_arg1[8];
  std::uint32_t swatch_arg2[8];
  std::uint32_t swatch_arg3[8];
  std::uint32_t swatch_index;
  std::uint32_t swatch_result;

  std::uint32_t manager_calls;
  std::uint32_t manager_acquires;
  std::uint32_t manager_slot[8];
  std::uint32_t manager_arg[8];
  std::uint32_t manager_result;

  std::uint32_t log_calls;
  std::uint32_t log_id[8];
  std::uint32_t log_value[8];
  std::uint32_t context_calls;

  std::uint32_t check_calls;
  std::uint32_t check_id[3];
  std::uint32_t check_value[3];

  std::uint32_t viewer_slot[16];
  std::uint32_t viewer_name_arg;
  std::uint32_t viewer_window_arg0;
  std::uint32_t viewer_window_arg1;
  std::uint32_t viewer_busy;
  std::uint32_t viewer_index;

  std::uint32_t probe_calls;
  std::uint32_t probe_arg[8];
  std::uint32_t probe_state_value;
  std::uint32_t probe_usable;
  std::uint32_t probe_index;

  std::uint32_t post_calls;
  std::uint32_t post_sink[8];
  std::uint32_t post_payload[8];
  std::uint32_t post_word[8];
  std::uint32_t post_tag[8];

  std::uint32_t app_calls;
  std::uint32_t app_slot[8];
  std::uint32_t app_arg0[8];
  std::uint32_t app_arg1[8];
  std::uint32_t app_arg2[8];
  std::uint32_t app_index;
  std::uint32_t app_present;

  std::uint32_t launch_calls;
  std::uint32_t launch_arg0[4];
  std::uint32_t launch_arg1[4];
  std::uint32_t launch_arg2[4];

  std::uint32_t build_calls;
  std::uint32_t build_key[2][3];
  std::uint32_t build_denied;
  std::uint32_t build_grants;

  std::uint32_t ref_retain;
  std::uint32_t ref_release;

  std::uint32_t registry_calls;
  std::uint32_t registry_second[4];
  std::uint32_t registry_tag[4];
  std::uint32_t registry_scale[4];
  std::uint32_t registry_mode[4];
  std::uint32_t registry_aspect[4];
  OpaqueBounds registry_box[4];

  std::uint32_t xf_init;
  std::uint32_t xf_apply;
  OpaqueLocalXf xf_frame;
  OpaqueBounds xf_applied_box;
  std::uint32_t xf_copies;
  OpaqueBounds xf_seed;
  std::uint32_t xf_resolves;

  std::uint32_t service_resolve_calls;
  std::uint32_t service_arg0[4];
  std::uint32_t service_arg1[4];
  std::uint32_t service_result;
  std::uint32_t service_fill;

  std::uint32_t scale_calls;
  std::uint32_t scale_id[4];
  float scale_value[4];
  std::uint32_t property_probe;
  std::uint32_t property_probe_id;
  std::uint32_t property_release;

  float extent_six[6];
  OpaqueRect extent_frame;
  OpaqueFloatPair extent_out;
  std::uint32_t extent_reads;
  std::uint32_t extent_writes;
  std::uint32_t extent_pair_arg0;
  std::uint32_t extent_pair_arg1;

  std::uint32_t reset_calls;
  std::uint32_t reset_name[8];
  std::uint32_t reset_index[8];
  std::uint32_t reset_count;

  std::uint32_t viewer_release;
  std::uint32_t detach_calls;
  std::uint32_t peer_calls;
  std::uint32_t peer_acquires;
  std::uint32_t peer_value;
  std::uint32_t peer_present;

  std::uint32_t host_calls;
  std::uint32_t host_live;
  std::uint32_t host_match;
  std::uint32_t host_probe;
  std::uint32_t host_reset;
  std::uint32_t app_reset;
  std::uint32_t app_reset_arg;
  std::uint32_t host_live_calls;
  std::uint32_t host_present;

  std::uint32_t zoom_calls;
  std::uint32_t sub_calls;
  std::uint32_t sub_arg;
  std::uint32_t zoom_arg[4];
  std::uint32_t zoom_ready;
  std::uint32_t model_ready;
  float zoom_a;
  float zoom_b;
  float zoom_c;
  std::uint32_t clock_calls;
  std::uint32_t clock_arg;

  std::uint32_t alpha_calls;
  std::uint32_t alpha_value[4];
  std::uint32_t alpha_host[4];
};

struct Fakes {
  std::uint8_t arena[65536];
  std::size_t arena_used;
  OpaqueIndexNode nodes[32];
  std::uint32_t node_used;
  Trace trace;

  OpaqueViewer viewer;
  OpaqueViewer spare;
  OpaqueItem item;
  OpaqueItem spare_item;
  OpaqueItemHostRoot root;
  OpaqueItemHost host;
  OpaquePaletteHost palette;
  OpaqueSub sub;
  OpaqueTransform transform;
  OpaqueFeature feature;
  OpaqueRenderer renderer;
  OpaqueSwatch swatch;
  OpaqueSwatchHost swatchhost;
  OpaqueManager manager;
  OpaqueRegistry registry;
  OpaqueService service;
  OpaqueProperty property;
  OpaqueApp app;
  OpaqueSource source;
  OpaqueProbe probe;
  OpaqueAddRef addref;
  OpaqueWindow window_a;
  OpaqueWindow window_b;
  OpaqueWindowHost windowhost;
  OpaquePeer peer;

  OpaqueItemVtable item_vtable;
  OpaqueAddRefVtable addref_vtable;
  OpaqueItemHostVtable host_vtable;
  OpaqueViewerVtable viewer_vtable;
  OpaqueSubVtable sub_vtable;
  OpaqueTransformVtable transform_vtable;
  OpaqueFeatureVtable feature_vtable;
  OpaqueRendererVtable renderer_vtable;
  OpaqueSwatchVtable swatch_vtable;
  OpaqueSwatchHostVtable swatchhost_vtable;
  OpaqueManagerVtable manager_vtable;
  OpaqueRegistryVtable registry_vtable;
  OpaqueServiceVtable service_vtable;
  OpaquePropertyVtable property_vtable;
  OpaqueAppVtable app_vtable;
  OpaqueProbeVtable probe_vtable;
  OpaqueRefVtable ref_vtable;
  OpaqueWindowVtable window_vtable;
  OpaqueWindowHostVtable windowhost_vtable;
  OpaquePeerVtable peer_vtable;
  OpaquePaletteHostVtable palette_vtable;
};

Fakes g;

std::uint8_t *reset_arena() {
  g.arena_used = 0U;
  g.node_used = 0U;
  return g.arena;
}

void *arena_take(std::uint32_t bytes) {
  const std::size_t span = (static_cast<std::size_t>(bytes) + 15U) & ~15U;
  if (g.arena_used + span > sizeof(g.arena)) {
    return nullptr;
  }
  void *block = g.arena + g.arena_used;
  g.arena_used += span;
  std::memset(block, 0, span);
  return block;
}

void PKG_AP_THISCALL item_retain(void *object) {
  ++g.trace.retain_item;
  (void)object;
}

void PKG_AP_THISCALL item_release(void *object) {
  ++g.trace.release_item;
  (void)object;
}

void PKG_AP_THISCALL ref_retain(void *object) {
  ++g.trace.ref_retain;
  (void)object;
}

void PKG_AP_THISCALL ref_release(void *object) {
  ++g.trace.ref_release;
  (void)object;
}

const float *PKG_AP_THISCALL host_rect(OpaqueItemHost *self) {
  ++g.trace.extent_reads;
  (void)self;
  return g.trace.extent_six;
}

void PKG_AP_THISCALL host_half(OpaqueItemHost *self, OpaqueFloatPair *out,
                               float w, float h) {
  ++g.trace.extent_writes;
  g.trace.extent_pair_arg0 = bits_of(w);
  g.trace.extent_pair_arg1 = bits_of(h);
  (void)self;
  *out = g.trace.extent_out;
}

void PKG_AP_THISCALL window_rect(OpaqueWindow *self, OpaqueRect *rect) {
  ++g.trace.extent_writes;
  g.trace.extent_frame = *rect;
  (void)self;
}

void PKG_AP_THISCALL window_pair(OpaqueWindow *self, std::uint32_t a,
                                 std::uint32_t b) {
  g.trace.extent_pair_arg0 = a;
  g.trace.extent_pair_arg1 = b;
  (void)self;
}

void PKG_AP_THISCALL window_attach(OpaqueWindow *self, OpaqueWindow *other) {
  ++g.trace.extent_writes;
  (void)self;
  (void)other;
}

void PKG_AP_THISCALL host_window_attach(OpaqueWindowHost *self,
                                        OpaqueWindow *other) {
  ++g.trace.extent_writes;
  (void)self;
  (void)other;
}

OpaqueWindowHost *PKG_AP_THISCALL palette_key(OpaquePaletteHost *self) {
  (void)self;
  return &g.windowhost;
}

const float *PKG_AP_THISCALL palette_rect(OpaquePaletteHost *self) {
  ++g.trace.extent_reads;
  (void)self;
  return g.trace.extent_six;
}

void PKG_AP_THISCALL sub_slot88(OpaqueSub *self, std::uint32_t value) {
  ++g.trace.sub_calls;
  g.trace.sub_arg = value;
  (void)self;
}

const float *PKG_AP_THISCALL transform_bounds(OpaqueTransform *self,
                                              OpaqueTransform *other) {
  (void)other;
  (void)self;
  ++g.trace.extent_reads;
  return g.trace.extent_six;
}

std::int32_t PKG_AP_THISCALL transform_count(OpaqueTransform *self,
                                             std::uint32_t a, std::uint32_t b,
                                             std::uint32_t name) {
  const std::uint32_t index = g.trace.reset_calls;
  g.trace.reset_name[index] = name;
  ++g.trace.reset_calls;
  (void)self;
  (void)a;
  (void)b;
  return static_cast<std::int32_t>(g.trace.reset_count);
}

void PKG_AP_THISCALL transform_reset(OpaqueTransform *self, std::uint32_t name,
                                     std::uint32_t a, float f,
                                     std::uint32_t index) {
  const std::uint32_t slot = g.trace.reset_calls;
  g.trace.reset_name[slot] = name;
  g.trace.reset_index[slot] = index;
  ++g.trace.reset_calls;
  (void)self;
  (void)a;
  (void)f;
}

bool PKG_AP_THISCALL feature_probe(OpaqueFeature *self, std::uint32_t key) {
  (void)self;
  (void)key;
  return g.trace.xf_resolves != 0U;
}

void *PKG_AP_THISCALL feature_resolve(OpaqueFeature *self, std::uint32_t key) {
  (void)self;
  (void)key;
  return &g.feature;
}

OpaqueSwatch *PKG_AP_THISCALL renderer_swatch(OpaqueRenderer *self,
                                              std::uint32_t key) {
  (void)self;
  (void)key;
  return &g.swatch;
}

const float *PKG_AP_THISCALL renderer_rect(OpaqueRenderer *self) {
  (void)self;
  return g.trace.extent_six;
}

OpaqueRenderer *PKG_AP_THISCALL swatch_host_renderer(OpaqueSwatchHost *self) {
  (void)self;
  return &g.renderer;
}

void swatch_note(std::uint32_t slot, std::uint32_t a, std::uint32_t b,
                 std::uint32_t c) {
  const std::uint32_t index = g.trace.swatch_index;
  g.trace.swatch_slot[index] = slot;
  g.trace.swatch_arg0[index] = a;
  g.trace.swatch_arg1[index] = b;
  g.trace.swatch_arg2[index] = c;
  g.trace.swatch_arg3[index] = 0U;
  ++g.trace.swatch_index;
}

void PKG_AP_THISCALL swatch_24(OpaqueSwatch *self, std::uint32_t a) {
  (void)self;
  swatch_note(0x24U, a, 0U, 0U);
}

bool PKG_AP_THISCALL swatch_28(OpaqueSwatch *self, std::uint32_t a,
                               std::uint32_t b) {
  (void)self;
  swatch_note(0x28U, a, b, 0U);
  return g.trace.swatch_result != 0U;
}

bool PKG_AP_THISCALL swatch_2c(OpaqueSwatch *self, std::uint32_t a,
                               std::uint32_t b) {
  (void)self;
  swatch_note(0x2cU, a, b, 0U);
  return g.trace.swatch_result != 0U;
}

bool PKG_AP_THISCALL swatch_30(OpaqueSwatch *self, float a, float b,
                               std::uint32_t c) {
  (void)self;
  swatch_note(0x30U, bits_of(a), bits_of(b), c);
  return g.trace.swatch_result != 0U;
}

bool PKG_AP_THISCALL swatch_34(OpaqueSwatch *self, std::uint32_t a, float b,
                               float c, std::uint32_t d) {
  (void)self;
  swatch_note(0x34U, a, bits_of(b), bits_of(c));
  g.trace.swatch_arg3[g.trace.swatch_index - 1U] = d;
  return g.trace.swatch_result != 0U;
}

bool PKG_AP_THISCALL swatch_38(OpaqueSwatch *self, float a, float b,
                               std::uint32_t c) {
  (void)self;
  swatch_note(0x38U, bits_of(a), bits_of(b), c);
  return g.trace.swatch_result != 0U;
}

bool PKG_AP_THISCALL swatch_3c(OpaqueSwatch *self, std::uint32_t a, float b,
                               float c, std::uint32_t d) {
  (void)self;
  swatch_note(0x3cU, a, bits_of(b), bits_of(c));
  g.trace.swatch_arg3[g.trace.swatch_index - 1U] = d;
  return g.trace.swatch_result != 0U;
}

std::uint32_t PKG_AP_THISCALL manager_token(OpaqueManager *self) {
  (void)self;
  g.trace.manager_slot[g.trace.manager_calls] = 0x04U;
  ++g.trace.manager_calls;
  return 0x55aaU;
}

void PKG_AP_THISCALL manager_pair(OpaqueManager *self, OpaqueFloatPair *pair) {
  (void)self;
  g.trace.manager_slot[g.trace.manager_calls] = 0x3cU;
  ++g.trace.manager_calls;
  *pair = g.trace.extent_out;
}

std::uint32_t PKG_AP_THISCALL manager_round(OpaqueManager *self,
                                            std::uint32_t a) {
  (void)self;
  g.trace.manager_slot[g.trace.manager_calls] = 0x54U;
  g.trace.manager_arg[g.trace.manager_calls] = a;
  ++g.trace.manager_calls;
  return g.trace.manager_result;
}

void PKG_AP_THISCALL manager_pair_arg(OpaqueManager *self, std::uint32_t a,
                                      std::uint32_t b) {
  (void)self;
  g.trace.manager_slot[g.trace.manager_calls] = 0x4cU;
  g.trace.manager_arg[g.trace.manager_calls] = a;
  g.trace.manager_arg[g.trace.manager_calls + 1U] = b;
  ++g.trace.manager_calls;
}

void PKG_AP_THISCALL manager_busy(OpaqueManager *self, std::uint32_t a,
                                  std::uint32_t b) {
  (void)self;
  (void)a;
  g.trace.manager_slot[g.trace.manager_calls] = 0x58U;
  g.trace.manager_arg[g.trace.manager_calls] = b;
  ++g.trace.manager_calls;
}

void PKG_AP_THISCALL manager_idle(OpaqueManager *self, std::uint32_t a,
                                  std::uint32_t b) {
  (void)self;
  (void)a;
  g.trace.manager_slot[g.trace.manager_calls] = 0x5cU;
  g.trace.manager_arg[g.trace.manager_calls] = b;
  ++g.trace.manager_calls;
}

void PKG_AP_THISCALL registry_apply(OpaqueRegistry *self, OpaqueBounds *box,
                                    std::uint32_t second, std::uint32_t tag,
                                    float scale, std::uint32_t mode,
                                    float aspect) {
  const std::uint32_t index = g.trace.registry_calls;
  g.trace.registry_box[index] = *box;
  g.trace.registry_second[index] = second;
  g.trace.registry_tag[index] = tag;
  g.trace.registry_scale[index] = bits_of(scale);
  g.trace.registry_mode[index] = mode;
  g.trace.registry_aspect[index] = bits_of(aspect);
  ++g.trace.registry_calls;
  (void)self;
}

void PKG_AP_THISCALL property_release_slot(OpaqueProperty *self) {
  (void)self;
  ++g.trace.property_release;
}

bool PKG_AP_THISCALL property_probe_slot(OpaqueProperty *self,
                                         std::uint32_t key) {
  (void)self;
  ++g.trace.property_probe;
  g.trace.property_probe_id = key;
  return g.trace.service_fill != 0U;
}

bool PKG_AP_THISCALL service_resolve(OpaqueService *self, std::uint32_t a,
                                     std::uint32_t b, OpaqueProperty **out) {
  const std::uint32_t index = g.trace.service_resolve_calls;
  g.trace.service_arg0[index] = a;
  g.trace.service_arg1[index] = b;
  ++g.trace.service_resolve_calls;
  *out = g.trace.service_result != 0U ? &g.property : nullptr;
  (void)self;
  return g.trace.service_result != 0U;
}

void PKG_AP_THISCALL app_post(OpaqueApp *self, std::uint32_t a, void *b,
                              std::uint32_t c) {
  const std::uint32_t index = g.trace.app_index;
  g.trace.app_slot[index] = 0x14U;
  g.trace.app_arg0[index] = a;
  g.trace.app_arg1[index] = b != nullptr ? 1U : 0U;
  g.trace.app_arg2[index] = c;
  ++g.trace.app_index;
  (void)self;
}

void PKG_AP_THISCALL app_notify(OpaqueApp *self, void *a, std::uint32_t b) {
  const std::uint32_t index = g.trace.app_index;
  g.trace.app_slot[index] = 0x24U;
  g.trace.app_arg0[index] = reinterpret_cast<std::uint32_t>(a);
  g.trace.app_arg1[index] = 1U;
  g.trace.app_arg2[index] = b;
  ++g.trace.app_index;
  (void)self;
}

std::uint32_t PKG_AP_THISCALL probe_state(OpaqueProbe *self,
                                          std::uint32_t *selector,
                                          std::uint32_t a) {
  const std::uint32_t index = g.trace.probe_index;
  g.trace.probe_arg[index] = reinterpret_cast<std::uint32_t>(selector);
  g.trace.probe_arg[index + 1U] = a;
  g.trace.probe_arg[index + 2U] = selector != nullptr ? *selector : 0U;
  g.trace.probe_index += 3U;
  (void)self;
  return g.trace.probe_state_value;
}

bool PKG_AP_THISCALL probe_usable(OpaqueProbe *self, std::uint32_t *out) {
  (void)self;
  ++g.trace.probe_calls;
  g.trace.probe_arg[6] = reinterpret_cast<std::uint32_t>(out);
  return g.trace.probe_usable != 0U;
}

std::uint32_t PKG_AP_THISCALL viewer_host_state(OpaqueViewer *self,
                                                std::uint32_t key) {
  (void)self;
  ++g.trace.host_calls;
  g.trace.host_live = key;
  return g.trace.host_probe;
}

void PKG_AP_THISCALL viewer_name(OpaqueViewer *self, const OpaqueKey3 *key) {
  (void)self;
  g.trace.viewer_name_arg = key->field00;
}

std::uint32_t PKG_AP_THISCALL viewer_window(OpaqueViewer *self, std::uint32_t a,
                                            std::uint32_t b) {
  (void)self;
  ++g.trace.viewer_index;
  g.trace.viewer_window_arg0 = a;
  g.trace.viewer_window_arg1 = b;
  return 0x77U;
}

void PKG_AP_THISCALL viewer_slot40(OpaqueViewer *self) {
  (void)self;
  g.trace.viewer_slot[g.trace.viewer_index] = 0x40U;
  ++g.trace.viewer_index;
}

bool PKG_AP_THISCALL viewer_slot44(OpaqueViewer *self) {
  (void)self;
  g.trace.viewer_slot[g.trace.viewer_index] = 0x44U;
  ++g.trace.viewer_index;
  return g.trace.viewer_busy != 0U;
}

void PKG_AP_THISCALL viewer_slot48(OpaqueViewer *self) {
  (void)self;
  g.trace.viewer_slot[g.trace.viewer_index] = 0x48U;
  ++g.trace.viewer_index;
}

void PKG_AP_THISCALL viewer_slot4c(OpaqueViewer *self) {
  (void)self;
  g.trace.viewer_slot[g.trace.viewer_index] = 0x4cU;
  ++g.trace.viewer_index;
}

void PKG_AP_THISCALL viewer_slot50(OpaqueViewer *self) {
  (void)self;
  g.trace.viewer_slot[g.trace.viewer_index] = 0x50U;
  ++g.trace.viewer_index;
}

void PKG_AP_THISCALL viewer_slot58(OpaqueViewer *self) {
  (void)self;
  g.trace.viewer_slot[g.trace.viewer_index] = 0x58U;
  ++g.trace.viewer_index;
}

void PKG_AP_THISCALL viewer_slot60(OpaqueViewer *self) {
  (void)self;
  g.trace.viewer_slot[g.trace.viewer_index] = 0x60U;
  ++g.trace.viewer_index;
  ++g.trace.detach_calls;
}

std::uint32_t PKG_AP_THISCALL peer_state(OpaquePeer *self) {
  (void)self;
  ++g.trace.peer_calls;
  return g.trace.peer_value;
}

OpaqueIndexNode *index_lookup(OpaqueIndex *index, std::uint32_t key) {
  for (std::uint32_t i = 0; i < g.node_used; ++i) {
    if (g.nodes[i].field10 == key) {
      return &g.nodes[i];
    }
  }
  (void)index;
  return nullptr;
}

OpaqueIndexNode *index_insert(OpaqueIndex *index, std::uint32_t key) {
  OpaqueIndexNode *found = index_lookup(index, key);
  if (found != nullptr) {
    return found;
  }
  OpaqueIndexNode *node = &g.nodes[g.node_used];
  node->field00 = nullptr;
  node->field04 = nullptr;
  node->field08 = 0U;
  node->field0c = 0U;
  node->field10 = key;
  node->field14 = 0U;
  ++g.node_used;
  index->field0c = node;
  return node;
}

void bind() {
  reset_arena();
  g.trace = Trace{};
  g.trace.alloc_deny = 0xffffffffU;
  g.trace.build_denied = 0xffffffffU;
  g.trace.peer_present = 1U;
  g.trace.app_present = 1U;
  g.trace.host_present = 1U;
  g.trace.swatch_present = 1U;
  g.trace.extent_frame.field00 = -2.0F;
  g.trace.extent_frame.field04 = -3.0F;
  g.trace.extent_frame.field08 = 2.0F;
  g.trace.extent_frame.field0c = 3.0F;
  g.trace.extent_six[0] = -2.0F;
  g.trace.extent_six[1] = -3.0F;
  g.trace.extent_six[2] = 2.0F;
  g.trace.extent_six[3] = 3.0F;
  g.trace.extent_six[4] = 3.0F;
  g.trace.extent_six[5] = 3.0F;

  g.item_vtable.retain00 = &item_retain;
  g.item_vtable.release04 = &item_release;
  g.addref_vtable.retain00 = &ref_retain;
  g.addref_vtable.release04 = &ref_release;
  g.ref_vtable.slot00 = 0U;
  g.ref_vtable.retain04 = &ref_retain;
  g.ref_vtable.release08 = &ref_release;

  g.host_vtable = OpaqueItemHostVtable{};
  g.host_vtable.retain04 = &ref_retain;
  g.host_vtable.release08 = &ref_release;
  g.host_vtable.slot38 = &host_rect;
  g.host_vtable.slotc0 = &host_half;
  g.window_vtable = OpaqueWindowVtable{};
  g.window_vtable.retain00 = &ref_retain;
  g.window_vtable.release04 = &ref_release;
  g.window_vtable.slot6c = &window_rect;
  g.window_vtable.slot7c = &window_pair;
  g.window_vtable.slotec = &window_attach;
  g.windowhost_vtable = OpaqueWindowHostVtable{};
  g.windowhost_vtable.slotec = &host_window_attach;
  g.palette_vtable = OpaquePaletteHostVtable{};
  g.palette_vtable.slot10 = &palette_key;
  g.palette_vtable.slot38 = &palette_rect;
  g.sub_vtable = OpaqueSubVtable{};
  g.sub_vtable.slot88 = &sub_slot88;
  g.transform_vtable = OpaqueTransformVtable{};
  g.transform_vtable.slot24 = &transform_bounds;
  g.transform_vtable.slot64 = &transform_count;
  g.transform_vtable.slot70 = &transform_reset;
  g.feature_vtable = OpaqueFeatureVtable{};
  g.feature_vtable.slot1c = &feature_probe;
  g.feature_vtable.slot28 = &feature_resolve;
  g.renderer_vtable = OpaqueRendererVtable{};
  g.renderer_vtable.slot0c = &renderer_swatch;
  g.renderer_vtable.slot38 = &renderer_rect;
  g.swatch_vtable = OpaqueSwatchVtable{};
  g.swatch_vtable.slot24 = &swatch_24;
  g.swatch_vtable.slot28 = &swatch_28;
  g.swatch_vtable.slot2c = &swatch_2c;
  g.swatch_vtable.slot30 = &swatch_30;
  g.swatch_vtable.slot34 = &swatch_34;
  g.swatch_vtable.slot38 = &swatch_38;
  g.swatch_vtable.slot3c = &swatch_3c;
  g.swatchhost_vtable = OpaqueSwatchHostVtable{};
  g.swatchhost_vtable.slot38 = &swatch_host_renderer;
  g.manager_vtable = OpaqueManagerVtable{};
  g.manager_vtable.slot04 = &manager_token;
  g.manager_vtable.slot3c = &manager_pair;
  g.manager_vtable.slot54 = &manager_round;
  g.manager_vtable.slot4c = &manager_pair_arg;
  g.manager_vtable.slot58 = &manager_busy;
  g.manager_vtable.slot5c = &manager_idle;
  g.registry_vtable = OpaqueRegistryVtable{};
  g.registry_vtable.slot14 = &registry_apply;
  g.property_vtable = OpaquePropertyVtable{};
  g.property_vtable.slot04 = &property_release_slot;
  g.property_vtable.slot1c = &property_probe_slot;
  g.service_vtable = OpaqueServiceVtable{};
  g.service_vtable.slot2c = &service_resolve;
  g.app_vtable = OpaqueAppVtable{};
  g.app_vtable.slot14 = &app_post;
  g.app_vtable.slot24 = &app_notify;
  g.probe_vtable = OpaqueProbeVtable{};
  g.probe_vtable.slot04 = &probe_state;
  g.probe_vtable.slot05 = &probe_usable;
  g.peer_vtable = OpaquePeerVtable{};
  g.peer_vtable.slot20 = &peer_state;
  g.viewer_vtable = OpaqueViewerVtable{};
  g.viewer_vtable.slot0c = &viewer_host_state;
  g.viewer_vtable.slot24 = &viewer_name;
  g.viewer_vtable.slot34 = &viewer_window;
  g.viewer_vtable.slot40 = &viewer_slot40;
  g.viewer_vtable.slot44 = &viewer_slot44;
  g.viewer_vtable.slot48 = &viewer_slot48;
  g.viewer_vtable.slot4c = &viewer_slot4c;
  g.viewer_vtable.slot50 = &viewer_slot50;
  g.viewer_vtable.slot58 = &viewer_slot58;
  g.viewer_vtable.slot60 = &viewer_slot60;

  std::memset(&g.viewer, 0, sizeof(g.viewer));
  g.viewer.vtable = &g.viewer_vtable;
  g.viewer.field4c = 0x1111U;
  g.viewer.field50 = 0x2222U;
  g.viewer.field54 = 0x3333U;
  g.viewer.field5c = &g.palette;
  g.viewer.field60 = &g.host;
  g.viewer.field34 = &g.sub;
  g.viewer.field118 = &g.transform;
  g.viewer.field17c = &g.source;
  g.viewer.field180 = &g.host;
  g.viewer.opaque184 = 0U;
  g.viewer.field198 = 1U;
  g.viewer.field100 = 0x71fa7d3fU;
  g.viewer.opaque160 = 1U;
  g.viewer.opaque166 = 1U;
  g.viewer.field16d[0] = 1U;
  g.viewer.field16d[1] = 1U;
  g.viewer.field16d[2] = 1U;
  g.viewer.field16d[3] = 1U;
  g.viewer.field16d[4] = 1U;

  std::memset(&g.source, 0, sizeof(g.source));
  g.source.vtable = &g.ref_vtable;
  g.source.field08 = &g.probe;
  g.source.field10 = &g.host;
  g.source.field14 = &g.palette;
  g.source.field30 = 1U;
  std::memset(&g.probe, 0, sizeof(g.probe));
  g.probe.vtable = &g.probe_vtable;
  std::memset(&g.host, 0, sizeof(g.host));
  g.host.vtable = &g.host_vtable;
  std::memset(&g.item, 0, sizeof(g.item));
  g.item.vtable = &g.item_vtable;
  std::memset(&g.spare_item, 0, sizeof(g.spare_item));
  g.spare_item.vtable = &g.item_vtable;
  std::memset(&g.transform, 0, sizeof(g.transform));
  g.transform.vtable = &g.transform_vtable;
  std::memset(&g.swatch, 0, sizeof(g.swatch));
  g.swatch.vtable = &g.swatch_vtable;
  std::memset(&g.renderer, 0, sizeof(g.renderer));
  g.renderer.vtable = &g.renderer_vtable;
  std::memset(&g.swatchhost, 0, sizeof(g.swatchhost));
  g.swatchhost.vtable = &g.swatchhost_vtable;
  std::memset(&g.manager, 0, sizeof(g.manager));
  g.manager.vtable = &g.manager_vtable;
  std::memset(&g.registry, 0, sizeof(g.registry));
  g.registry.vtable = &g.registry_vtable;
  std::memset(&g.service, 0, sizeof(g.service));
  g.service.vtable = &g.service_vtable;
  std::memset(&g.property, 0, sizeof(g.property));
  g.property.vtable = &g.property_vtable;
  std::memset(&g.app, 0, sizeof(g.app));
  g.app.vtable = &g.app_vtable;
  std::memset(&g.feature, 0, sizeof(g.feature));
  g.feature.vtable = &g.feature_vtable;
  std::memset(&g.palette, 0, sizeof(g.palette));
  g.palette.vtable = &g.palette_vtable;
  std::memset(&g.sub, 0, sizeof(g.sub));
  g.sub.vtable = &g.sub_vtable;
  std::memset(&g.addref, 0, sizeof(g.addref));
  g.addref.vtable = &g.addref_vtable;
  std::memset(&g.windowhost, 0, sizeof(g.windowhost));
  g.windowhost.vtable = &g.windowhost_vtable;
  std::memset(&g.peer, 0, sizeof(g.peer));
  g.peer.vtable = &g.peer_vtable;
  std::memset(&g.root, 0, sizeof(g.root));
}

extern "C" void *PKG_AP_CDECL
unresolved_00f473a0(std::uint32_t bytes, std::uint32_t tag, std::uint32_t a,
                    std::uint32_t b, std::uint32_t c, std::uint32_t d) {
  ++g.trace.alloc_calls;
  g.trace.alloc_bytes = bytes;
  ++g.trace.alloc_grants;
  (void)tag;
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  if (g.trace.alloc_grants > g.trace.alloc_deny) {
    return nullptr;
  }
  return arena_take(bytes);
}

extern "C" OpaqueSwatchManager *PKG_AP_CDECL unresolved_00401020() {
  ++g.trace.swatch_manager;
  return reinterpret_cast<OpaqueSwatchManager *>(&g.trace);
}

extern "C" OpaqueSwatchHost *PKG_AP_THISCALL
unresolved_01137690(OpaqueSwatchManager *self) {
  (void)self;
  ++g.trace.swatch_host;
  return g.trace.swatch_present != 0U ? &g.swatchhost : nullptr;
}

extern "C" std::uint32_t PKG_AP_THISCALL
unresolved_0113ae10(OpaqueSwatchManager *self) {
  (void)self;
  return g.trace.post_sink[0];
}

extern "C" void PKG_AP_THISCALL unresolved_005ed6c0(OpaqueSwatchHost *self) {
  ++g.trace.swatch_release;
  g.trace.swatch_release_arg = reinterpret_cast<std::uint32_t>(self);
}

extern "C" OpaqueManager *PKG_AP_CDECL unresolved_0067caa0() {
  ++g.trace.manager_acquires;
  return &g.manager;
}

extern "C" void *PKG_AP_CDECL unresolved_0067cad0() {
  return reinterpret_cast<void *>(&g.swatchhost);
}

extern "C" OpaqueApp *PKG_AP_CDECL unresolved_0067dcc0() {
  ++g.trace.app_calls;
  return g.trace.app_present != 0U ? &g.app : nullptr;
}

extern "C" OpaqueService *PKG_AP_CDECL unresolved_0067de30() {
  return &g.service;
}

extern "C" OpaqueRegistry *PKG_AP_CDECL unresolved_0067ddb0() {
  return &g.registry;
}

extern "C" std::uint32_t PKG_AP_CDECL unresolved_00435e90() {
  ++g.trace.context_calls;
  return 0x99aabbccU;
}

extern "C" void PKG_AP_CDECL unresolved_00435ed0(std::uint32_t id,
                                                 std::uint32_t value) {
  const std::uint32_t index = g.trace.log_calls;
  g.trace.log_id[index] = id;
  g.trace.log_value[index] = value;
  ++g.trace.log_calls;
}

extern "C" OpaquePeer *PKG_AP_CDECL unresolved_00a206f0() {
  ++g.trace.peer_acquires;
  return g.trace.peer_present != 0U ? &g.peer : nullptr;
}

extern "C" OpaqueAddRef *PKG_AP_CDECL unresolved_00804500() {
  ++g.trace.host_calls;
  return g.trace.host_present != 0U ? &g.addref : nullptr;
}

extern "C" bool PKG_AP_THISCALL unresolved_006c1100(OpaqueAddRef *self) {
  (void)self;
  return g.trace.service_result != 0U;
}

extern "C" std::uint32_t PKG_AP_THISCALL
unresolved_006c10e0(OpaqueAddRef *self) {
  (void)self;
  return g.trace.host_match;
}

extern "C" void PKG_AP_THISCALL unresolved_00803bd0(OpaqueAddRef *self,
                                                    std::uint32_t value) {
  (void)self;
  ++g.trace.app_reset;
  g.trace.app_reset_arg = value;
}

extern "C" std::uint8_t PKG_AP_CDECL unresolved_008d2fb0(std::uint32_t key) {
  const std::uint32_t index = g.trace.check_calls;
  g.trace.check_id[index] = key;
  g.trace.check_value[index] = 0U;
  ++g.trace.check_calls;
  return 0U;
}

extern "C" void PKG_AP_CDECL unresolved_0040cf10(OpaqueProperty *self,
                                                 std::uint32_t key,
                                                 float *out) {
  (void)self;
  const std::uint32_t index = g.trace.scale_calls;
  g.trace.scale_id[index] = key;
  ++g.trace.scale_calls;
  *out = g.trace.scale_value[index];
}

extern "C" void *PKG_AP_CDECL unresolved_00807880(const OpaqueKey3 *key,
                                                  float w, float h,
                                                  void *owner) {
  const std::uint32_t index = g.trace.build_calls;
  g.trace.build_key[index][0] = key->field00;
  g.trace.build_key[index][1] = key->field04;
  g.trace.build_key[index][2] = key->field08;
  (void)w;
  (void)h;
  (void)owner;
  ++g.trace.build_calls;
  if (g.trace.build_calls > g.trace.build_denied) {
    return nullptr;
  }
  ++g.trace.build_grants;
  return arena_take(0x100U);
}

extern "C" void PKG_AP_CDECL unresolved_00807d30(OpaqueSwatchHost *self,
                                                 void *callback,
                                                 OpaqueTagPair tag) {
  (void)callback;
  const std::uint32_t index = g.trace.post_calls;
  g.trace.post_sink[index] = reinterpret_cast<std::uint32_t>(self);
  g.trace.post_word[index] = tag.field04;
  g.trace.post_tag[index] = tag.field00;
  ++g.trace.post_calls;
}

extern "C" void *PKG_AP_CDECL unresolved_005f3b20(
    const OpaqueKey3 *a, const OpaqueKey3 *b, std::uint32_t c, std::uint32_t d,
    std::uint32_t e, std::uint32_t f, const OpaqueKey3 *t, std::uint32_t h) {
  const std::uint32_t index = g.trace.launch_calls;
  g.trace.launch_arg0[index] = a->field00;
  g.trace.launch_arg1[index] = b->field00;
  g.trace.launch_arg2[index] =
      c | (d << 8) | (e << 16) | (f << 24) | (t->field00 << 4) | (h << 5);
  ++g.trace.launch_calls;
  return &g.trace;
}

extern "C" OpaqueItem *PKG_AP_THISCALL unresolved_005f6bd0(OpaqueItem *self) {
  ++g.trace.ctor_calls;
  self->vtable = &g.item_vtable;
  self->field178 = 0xffffffffU;
  return self;
}

extern "C" OpaqueIndexNode *PKG_AP_THISCALL
unresolved_005f0b40(OpaqueIndex *index, std::uint32_t *key) {
  ++g.trace.index_query;
  return index_insert(index, *key);
}

extern "C" OpaqueIndexNode *PKG_AP_THISCALL
unresolved_005f0bc0(OpaqueIndex *index, OpaqueItem **key) {
  return index_insert(index, reinterpret_cast<std::uint32_t>(*key));
}

extern "C" void PKG_AP_THISCALL unresolved_005f2fd0(OpaqueViewer *self) {
  (void)self;
  ++g.trace.host_live_calls;
}

extern "C" void PKG_AP_THISCALL unresolved_005f3600(OpaqueViewer *self) {
  (void)self;
  ++g.trace.viewer_release;
}

extern "C" void PKG_AP_THISCALL unresolved_005f3400(OpaqueViewer *self) {
  (void)self;
  ++g.trace.detach_calls;
}

extern "C" void PKG_AP_THISCALL unresolved_0080d7c0(OpaqueViewer *self,
                                                    std::uint8_t value) {
  (void)self;
  ++g.trace.zoom_calls;
  g.trace.zoom_arg[0] = value;
}

extern "C" std::uint32_t PKG_AP_THISCALL
unresolved_0080d610(OpaqueViewer *self) {
  (void)self;
  ++g.trace.zoom_ready;
  return 0x1234U;
}

extern "C" std::uint32_t PKG_AP_THISCALL
unresolved_0080d5f0(OpaqueViewer *self) {
  (void)self;
  ++g.trace.zoom_ready;
  return g.trace.model_ready;
}

extern "C" std::uint32_t PKG_AP_THISCALL
unresolved_0093b6c0(OpaqueViewer *self) {
  (void)self;
  ++g.trace.zoom_ready;
  return g.trace.model_ready;
}

extern "C" void PKG_AP_THISCALL unresolved_0093a1a0(std::uint8_t *self,
                                                    std::uint32_t value) {
  (void)self;
  ++g.trace.clock_calls;
  g.trace.clock_arg = value;
}

extern "C" OpaqueLocalXf *PKG_AP_THISCALL
unresolved_00409930(OpaqueLocalXf *self) {
  ++g.trace.xf_init;
  std::memset(self, 0, sizeof(*self));
  self->field08 = 1.0F;
  return self;
}

extern "C" void PKG_AP_THISCALL unresolved_00409dd0(OpaqueBounds *box,
                                                    OpaqueLocalXf *frame) {
  ++g.trace.xf_apply;
  g.trace.xf_applied_box = *box;
  g.trace.xf_frame = *frame;
  g.trace.extent_out.field00 = frame->field08;
  g.trace.extent_out.field04 = frame->field0c;
}

extern "C" OpaqueBounds *PKG_AP_THISCALL
unresolved_00511140(OpaqueBounds *dst, const OpaqueBounds *src) {
  ++g.trace.xf_copies;
  *dst = *src;
  return dst;
}

extern "C" void PKG_AP_THISCALL unresolved_00571d60(OpaqueBounds *dst,
                                                    const OpaqueBounds *src) {
  ++g.trace.xf_copies;
  *dst = *src;
}

extern "C" bool PKG_AP_THISCALL unresolved_005c6670(OpaqueItemHost *self,
                                                    OpaqueItemHost *other) {
  (void)self;
  ++g.trace.probe_calls;
  g.trace.probe_arg[7] = reinterpret_cast<std::uint32_t>(other);
  return g.trace.probe_usable != 0U;
}

extern "C" OpaqueBounds *PKG_AP_THISCALL
unresolved_005f2320(OpaqueFeature *self) {
  (void)self;
  return &g.trace.xf_seed;
}

extern "C" float PKG_AP_CDECL unresolved_005f2390(OpaqueViewer *self,
                                                  std::uint32_t a,
                                                  OpaqueItemHost *b, float c,
                                                  float d, float e) {
  (void)self;
  (void)b;
  ++g.trace.zoom_calls;
  g.trace.zoom_arg[1] = a;
  g.trace.zoom_a = c;
  g.trace.zoom_b = d;
  g.trace.zoom_c = e;
  return 0.0F;
}

extern "C" void *PKG_AP_THISCALL unresolved_00b5f950(OpaqueWindow **slot,
                                                     OpaqueWindow *value) {
  OpaqueWindow *previous = *slot;
  if (previous != value) {
    if (value != nullptr) {
      value->vtable = &g.window_vtable;
      value->vtable->retain00(value);
    }
    *slot = value;
    if (previous != nullptr) {
      previous->vtable->release04(previous);
    }
  }
  return slot;
}

extern "C" void PKG_AP_THISCALL unresolved_0080d710(OpaqueSwatchHost *self,
                                                    std::uint32_t payload,
                                                    std::uint32_t word,
                                                    std::uint8_t tag) {
  OpaqueTagPair pair;
  pair.field00 = tag;
  pair.opaque01[0] = 0U;
  pair.opaque01[1] = 0U;
  pair.opaque01[2] = 0U;
  pair.field04 = word;
  unresolved_00807d30(self, nullptr, pair);
  g.trace.post_payload[g.trace.post_calls - 1U] = payload;
}

extern "C" void PKG_AP_CDECL unresolved_00804fc0(OpaqueViewer *self,
                                                 float value) {
  (void)self;
  g.trace.alpha_value[g.trace.alpha_calls] = bits_of(value);
  g.trace.alpha_host[g.trace.alpha_calls] = bits_of(self);
  ++g.trace.alpha_calls;
}

void seed_event(OpaqueEvent *event, std::uint32_t type) {
  std::memset(event, 0, sizeof(*event));
  event->field08 = type;
  const std::uint32_t mode = 1U;
  std::memcpy(&event->field0c, &mode, sizeof(mode));
  event->field10 = 2.0F;
  event->field14 = 3.0F;
  event->field18 = 1000U;
}

void test_signature_shapes() {
  check(std::is_same<decltype(unresolved_005f0ca0(nullptr, nullptr)),
                     OpaqueItem *>::value,
        "the factory keeps the thiscall return");
  check(std::is_same<decltype(unresolved_005f2350(nullptr, nullptr)),
                     std::uint32_t>::value,
        "the rect probe keeps the thiscall return");
  check(std::is_same<decltype(unresolved_005f27c0(nullptr, 0U, nullptr)),
                     bool>::value,
        "the dispatcher keeps the thiscall return");
  check(std::is_same<decltype(unresolved_005f4310(nullptr, nullptr, 0U, nullptr,
                                                  0U, nullptr, nullptr, 0U)),
                     void>::value,
        "the initialiser keeps its seven stack words");
  static_assert(sizeof(OpaqueViewer) == 0x1c8U, "viewer size");
  static_assert(sizeof(OpaqueItem) == 0x17cU, "item size");
  static_assert(sizeof(OpaqueAnchor) == 0x28U, "anchor size");
}

void test_factory_allocates_and_tags() {
  bind();
  g.root.field40 = 7U;
  OpaqueItem *made = unresolved_005f0ca0(&g.root, nullptr);
  check(made != nullptr, "the factory builds an item when nothing is supplied");
  check(g.trace.alloc_bytes == 0x17cU, "the factory requests 0x17c bytes");
  check(g.trace.ctor_calls == 1U, "the factory runs the item constructor once");
  check(made->field178 == 7U, "the item records the sequence it was given");
  check(g.root.field40 == 8U, "the factory advances the sequence counter");
  check(g.trace.retain_item == 2U, "the factory retains on both index paths");
  check(g.trace.release_item == 1U, "the factory releases the item it stored");
  check(g.root.field24.field0c->field14 == 0x5368d4a5U,
        "the second index stores the item tag word");
  check(made->vtable == &g.item_vtable, "the factory installs the item vtable");
}

void test_factory_reuses_supplied() {
  bind();
  OpaqueItem *made = unresolved_005f0ca0(&g.root, &g.item);
  check(made == &g.item, "the factory returns the item it was handed");
  check(g.trace.alloc_calls == 0U, "the factory skips the allocator");
  check(g.trace.ctor_calls == 0U, "the factory skips the constructor");
  check(g.item.field178 == 0U, "the reused item takes sequence zero");
  check(g.trace.retain_item == 2U,
        "the reused item is retained on both index paths");
  check(g.trace.release_item == 1U, "the reused item is released once");
}

void test_factory_allocation_failure() {
  bind();
  g.trace.alloc_deny = 0U;
  OpaqueItem *made = unresolved_005f0ca0(&g.root, nullptr);
  check(made == nullptr, "a denied allocation yields no item");
  check(g.trace.ctor_calls == 0U, "a denied allocation skips the constructor");
  check(g.trace.retain_item == 0U, "a denied allocation retains nothing");
  check(g.root.field40 == 0U, "a denied allocation leaves the counter alone");
}

void test_factory_replaces_live_item() {
  bind();
  unresolved_005f0ca0(&g.root, &g.item);
  OpaqueItem *made = unresolved_005f0ca0(&g.root, &g.spare_item);
  check(made == &g.spare_item, "the second build wins the live slot");
  check(g.root.field08.field0c->field14 ==
            reinterpret_cast<std::uint32_t>(&g.spare_item),
        "the live index now points at the second item");
  check(g.trace.release_item == 2U,
        "the displaced item is released by the live swap");
}

void test_rect_containment() {
  OpaqueRect frame;
  frame.field00 = 1.0F;
  frame.field04 = 2.0F;
  frame.field08 = 5.0F;
  frame.field0c = 6.0F;
  OpaqueRect lower;
  lower.field00 = 1.0F;
  lower.field04 = 2.0F;
  check(unresolved_005f2350(&frame, &lower) == 1U,
        "the lower corner counts as inside");
  OpaqueRect upper;
  upper.field00 = 5.0F;
  upper.field04 = 2.0F;
  check(unresolved_005f2350(&frame, &upper) == 0U,
        "the upper edge is exclusive on x");
  OpaqueRect below;
  below.field00 = 0.0F;
  below.field04 = 2.0F;
  check(unresolved_005f2350(&frame, &below) == 0U,
        "a point below the lower edge is outside");
  OpaqueRect edge_y;
  edge_y.field00 = 2.0F;
  edge_y.field04 = 6.0F;
  check(unresolved_005f2350(&frame, &edge_y) == 0U,
        "the upper edge is exclusive on y");
  OpaqueRect unordered;
  unordered.field00 = std::nan("");
  unordered.field04 = 2.0F;
  check(unresolved_005f2350(&frame, &unordered) == 0U,
        "an unordered probe compares as outside");
}

void test_dispatch_palette_round() {
  bind();
  OpaqueEvent event;
  seed_event(&event, 1U);
  g.viewer.field5c = reinterpret_cast<OpaquePaletteHost *>(0x40U);
  g.trace.manager_result = 5U;
  check(unresolved_005f27c0(&g.viewer, 5U, &event),
        "a matching round reports true");
  check(g.trace.manager_slot[0] == 0x54U, "the first manager runs the round");
  check(g.trace.manager_slot[1] == 0x54U, "the second manager runs the round");
  check(unresolved_005f27c0(&g.viewer, 6U, &event) == false,
        "a mismatched round reports false");
  seed_event(&event, 2U);
  check(unresolved_005f27c0(&g.viewer, 5U, &event),
        "type two shares the round path");
  seed_event(&event, 5U);
  check(unresolved_005f27c0(&g.viewer, 5U, &event),
        "type five shares the round path");
}

void test_dispatch_accept_path() {
  bind();
  g.viewer.field5c = reinterpret_cast<OpaquePaletteHost *>(1000U);
  OpaqueEvent event;
  seed_event(&event, 3U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "the accept path reports false");
  check(g.viewer.fieldec == 1U, "the accept path raises the action byte");
  check(g.trace.check_calls == 3U, "the accept path runs three probes");
  check(g.trace.check_id[0] == 0x3e8U, "the first probe word is 0x3e8");
  check(g.trace.check_id[1] == 0x3e9U, "the second probe word is 0x3e9");
  check(g.trace.check_id[2] == 0x3ea, "the third probe word is 0x3ea");
  check(g.trace.log_calls == 1U, "the accept path logs once");
  check(g.trace.log_id[0] == 0x0bb58117eU, "the accept path logs its token");
  check(g.trace.log_value[0] == 0x99aabbccU,
        "the accept path logs the context word");
  check(g.trace.viewer_slot[0] == 0x44U, "the accept path checks slot 0x44");
  check(g.trace.viewer_slot[1] == 0x48U, "the accept path drives slot 0x48");
  seed_event(&event, 27U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "the last accept type behaves the same way");
  check(g.trace.check_calls == 6U, "the second accept type probes again");
}

void test_dispatch_accept_guards() {
  bind();
  g.viewer.field5c = reinterpret_cast<OpaquePaletteHost *>(1000U);
  const std::uint32_t mode_one = 1U;
  OpaqueEvent event;
  seed_event(&event, 3U);
  g.trace.viewer_busy = 1U;
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "a busy viewer rejects the accept path");
  check(g.trace.check_calls == 0U, "a busy viewer skips the probes");
  g.trace.viewer_busy = 0U;
  const std::uint32_t foreign = 2U;
  std::memcpy(&event.field0c, &foreign, sizeof(foreign));
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "a foreign mode word rejects the accept path");
  std::memcpy(&event.field0c, &mode_one, sizeof(mode_one));
  event.field18 = 999U;
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "a foreign palette id rejects the accept path");
  check(g.trace.check_calls == 0U, "no probe runs when a guard rejects");
  check(g.viewer.fieldec == 0U, "the action byte stays clear when rejected");
  check(g.trace.log_calls == 0U, "a rejected accept path stays quiet");
}

void test_dispatch_rebuild_and_stamp() {
  bind();
  OpaqueEvent event;
  seed_event(&event, 6U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "the guarded rebuild reports true");
  check(g.trace.manager_slot[0] == 0x04U,
        "the rebuild reads the manager token");
  check(g.trace.manager_slot[1] == 0x4cU, "the rebuild hands the token over");
  check(g.trace.manager_arg[2] == 0x55aaU, "the handed token matches");
  check(g.trace.viewer_slot[0] == 0x50U, "the rebuild drives slot 0x50");
  event.field18 = 1001U;
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "an unguarded index rejects the rebuild");
  seed_event(&event, 0x7be2440U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "the unguarded rebuild reports true");
  check(g.trace.viewer_slot[1] == 0x50U, "the second rebuild drives slot 0x50");
  seed_event(&event, 0x7be2441U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "the paired rebuild reports true");
  check(g.trace.viewer_slot[2] == 0x40U, "the paired rebuild drives slot 0x40");
  check(g.trace.viewer_slot[3] == 0x4cU, "the paired rebuild drives slot 0x4c");
  std::uint32_t target = 0U;
  seed_event(&event, 0x7be2444U);
  event.field18 = reinterpret_cast<std::uint32_t>(&target) - 0x18U;
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "the stamp type reports true");
  check(target == 0x06493807U, "the stamp type writes the broadcast tag");
  seed_event(&event, 0x7be2445U);
  target = 0U;
  event.field18 = reinterpret_cast<std::uint32_t>(&target) - 0x18U;
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "the second stamp type reports true");
  check(target == 0x06493807U, "the second stamp type writes the same tag");
  seed_event(&event, 0x7be2442U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "an unused high type reports false");
  seed_event(&event, 0x28U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "an unknown type reports false");
}

void test_dispatch_terminal() {
  bind();
  g.viewer.field5c = reinterpret_cast<OpaquePaletteHost *>(1000U);
  OpaqueEvent event;
  seed_event(&event, 0x1cU);
  g.viewer.fieldec = 1U;
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "the terminal type reports false");
  check(g.viewer.fieldec == 0U, "the terminal type clears the action byte");
  check(g.trace.viewer_slot[0] == 0x44U, "the terminal type checks slot 0x44");
  check(g.trace.viewer_slot[1] == 0x4cU, "the terminal type drives slot 0x4c");
  g.viewer.fieldec = 1U;
  g.trace.viewer_busy = 1U;
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "a busy viewer blocks the terminal type");
  check(g.viewer.fieldec == 1U, "a blocked terminal type keeps the byte");
}

void test_dispatch_swatch_branch() {
  bind();
  g.viewer.field16c = 1U;
  g.viewer.field5c = reinterpret_cast<OpaquePaletteHost *>(0x40U);
  g.trace.swatch_result = 1U;
  OpaqueEvent event;

  seed_event(&event, 1U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event), "swatch type one says yes");
  check(g.trace.swatch_slot[0] == 0x28U, "swatch type one drives slot 0x28");
  check(g.trace.swatch_arg0[0] == bits_of(event.field10),
        "swatch type one passes the first word");
  check(g.trace.swatch_arg1[0] == bits_of(event.field14),
        "swatch type one passes the second word");

  seed_event(&event, 2U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event), "swatch type two says yes");
  check(g.trace.swatch_slot[1] == 0x2cU, "swatch type two drives slot 0x2c");
  check(g.trace.swatch_arg0[1] == bits_of(event.field14),
        "swatch type two swaps its two words");

  seed_event(&event, 6U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "swatch type six claims the slot");
  check(g.trace.swatch_slot[2] == 0x30U, "swatch type six drives slot 0x30");
  check(g.trace.manager_slot[0] == 0x58U, "swatch type six flags the manager");
  check(g.trace.manager_arg[0] == 0x40U,
        "swatch type six passes the palette id");
  check(g.viewer.field16d[0] == 1U, "swatch type six claims the item slot");

  seed_event(&event, 7U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "swatch type seven reports the swatch answer");
  check(g.trace.swatch_slot[3] == 0x34U, "swatch type seven drives slot 0x34");
  check(g.trace.swatch_arg3[3] == bits_of(event.field14),
        "swatch type seven passes the trailing word");
  check(g.trace.manager_acquires == 1U,
        "a live neighbour stops the idle notification");

  seed_event(&event, 8U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "swatch type eight says yes");
  check(g.trace.swatch_slot[4] == 0x38U, "swatch type eight drives slot 0x38");
  seed_event(&event, 9U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "swatch type nine says yes");
  check(g.trace.swatch_slot[5] == 0x3cU, "swatch type nine drives slot 0x3c");
  seed_event(&event, 10U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "swatch type ten always reports false");
  check(g.trace.swatch_slot[6] == 0x24U, "swatch type ten drives slot 0x24");
  check(g.trace.swatch_arg0[6] == 0U,
        "swatch type ten reports an unmatched palette");
  seed_event(&event, 11U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event) == false,
        "an unmapped swatch type reports false");
  check(g.trace.swatch_index == 7U, "an unmapped swatch type drives no slot");
}

void test_dispatch_swatch_idle_path() {
  bind();
  g.viewer.field16c = 1U;
  g.viewer.field16d[0] = 0U;
  g.viewer.field16d[1] = 0U;
  g.viewer.field16d[2] = 0U;
  g.viewer.field16d[3] = 0U;
  g.viewer.field16d[4] = 0U;
  g.trace.swatch_result = 1U;
  OpaqueEvent event;
  seed_event(&event, 7U);
  g.viewer.field16d[0] = 1U;
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "the idle swatch path still reports the swatch answer");
  check(g.trace.manager_slot[0] == 0x5cU,
        "an empty neighbour list notifies the manager");
}

void test_dispatch_swatch_fallback() {
  bind();
  g.viewer.field16c = 1U;
  g.viewer.field5c = reinterpret_cast<OpaquePaletteHost *>(0x40U);
  g.trace.manager_result = 0U;
  g.trace.swatch_present = 0U;
  OpaqueEvent event;
  seed_event(&event, 1U);
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "a dead swatch falls through to the round path");
  check(g.trace.manager_slot[0] == 0x54U, "the fallback drives the round slot");
  g.trace.swatch_present = 1U;
  g.viewer.field16c = 0U;
  check(unresolved_005f27c0(&g.viewer, 0U, &event),
        "a dead viewer also falls through to the round path");
}

void test_arm_gate() {
  bind();
  g.viewer.field14 = &g.viewer;
  g.viewer.field3c = &g.spare;
  g.viewer.field118 = &g.transform;
  g.viewer.fieldf0 = reinterpret_cast<OpaqueSub *>(&g.addref);
  g.viewer.fieldc0 = 5.0F;
  g.viewer.fieldd8 = 7.0F;
  unresolved_005f2e00(&g.viewer);
  check(g.viewer.field10 == 1U, "an armed gate raises the ready word");
  check(g.viewer.fieldc0 == 0.0F, "an armed gate zeroes the zoom word");
  check(g.viewer.fieldd8 == 1.0F, "an armed gate restores the scale word");
  check(g.trace.zoom_calls == 1U, "an armed gate pokes the model once");
  check(g.trace.zoom_arg[0] == 1U, "the model poke carries one");
  check(g.trace.sub_calls == 1U, "an armed gate drives the sub slot once");
  check(g.trace.sub_arg == 0x1234U, "the sub slot receives the model word");
  reinterpret_cast<std::uint8_t *>(g.viewer.fieldf0)[0x64] = 0U;
  unresolved_005f2e00(&g.viewer);
  check(reinterpret_cast<std::uint8_t *>(g.viewer.fieldf0)[0x64] == 1U,
        "the sub mirror byte is always raised");
}

void test_arm_gate_blocked() {
  bind();
  g.viewer.field14 = &g.viewer;
  g.viewer.field3c = &g.spare;
  g.viewer.field118 = &g.transform;
  g.viewer.fieldc0 = 5.0F;
  g.viewer.opaque160 = 0U;
  unresolved_005f2e00(&g.viewer);
  check(g.viewer.field10 == 0U, "a hidden viewer stays disarmed");
  check(g.viewer.fieldc0 == 5.0F, "a hidden viewer keeps its zoom word");
  g.viewer.opaque160 = 1U;
  g.viewer.fieldeb = 1U;
  g.viewer.opaque163 = 0U;
  unresolved_005f2e00(&g.viewer);
  check(g.viewer.field10 == 0U, "the extended gate needs the extra byte");
  g.viewer.opaque163 = 1U;
  unresolved_005f2e00(&g.viewer);
  check(g.viewer.field10 == 1U, "the extended gate arms once all bits are set");
  g.viewer.fieldeb = 1U;
  g.viewer.opaque166 = 0U;
  const std::uint32_t zoom_before = g.trace.zoom_calls;
  unresolved_005f2e00(&g.viewer);
  check(g.trace.zoom_calls == zoom_before,
        "the extended gate honours the visible byte");
}

void test_transform_sweep() {
  bind();
  g.viewer.field50 = 0x2399be55U;
  g.trace.reset_count = 3U;
  unresolved_005f2ee0(&g.viewer);
  check(g.trace.reset_calls == 4U,
        "the sweep counts once then resets per slot");
  check(g.trace.reset_name[0] == 0xa502dc0bU,
        "the model key selects the second name");
  check(g.trace.reset_index[1] == 0U, "the first reset carries index zero");
  check(g.trace.reset_index[3] == 2U, "the last reset carries index two");
  g.viewer.field50 = 0U;
  unresolved_005f2ee0(&g.viewer);
  check(g.trace.reset_name[4] == 0xb37b55b2U,
        "a foreign key selects the first name");
  const std::uint32_t before = g.trace.reset_calls;
  g.viewer.field118 = nullptr;
  unresolved_005f2ee0(&g.viewer);
  check(g.trace.reset_calls == before, "a missing transform skips the sweep");
}

void test_launch_windows() {
  bind();
  g.trace.post_sink[0] = reinterpret_cast<std::uint32_t>(&g.swatchhost);
  g.viewer.field194 = &g.host;
  unresolved_005f30b0(&g.viewer);
  check(g.viewer.opaque169 == 0U, "the launch clears the reset byte");
  check(g.trace.app_slot[0] == 0x14U, "the launch posts to the app system");
  check(g.trace.app_arg0[0] == 0x0522f9ceU, "the launch carries its token");
  check(g.trace.app_arg2[0] == 0U, "the launch closes with a zero word");
  check(g.trace.post_calls == 2U, "the launch posts two windows");
  check(g.trace.post_payload[0] == 0x77U,
        "the first window comes from the viewer slot");
  check(g.trace.post_word[0] == 0U, "the first post carries a zero word");
  check(g.trace.post_tag[0] == 1U, "the first post carries the enable tag");
  check(g.trace.post_payload[1] == bits_of(&g.host),
        "the parent window is posted when the slot is filled");
  g.viewer.opaque16b = 0U;
  unresolved_005f30b0(&g.viewer);
  check(g.trace.swatch_release == 0U,
        "a disabled viewer skips the swatch release");
  g.viewer.opaque16b = 1U;
  unresolved_005f30b0(&g.viewer);
  check(g.trace.swatch_release == 1U, "an enabled viewer releases the swatch");
  check(g.trace.swatch_release_arg == bits_of(&g.palette),
        "the release prefers the palette host");
}

void test_build_bounds() {
  bind();
  g.viewer.field16c = 1U;
  unresolved_005f3cf0(&g.viewer);
  check(g.viewer.opaque160 == 1U, "a live viewer short circuits to built");
  check(g.trace.registry_calls == 0U, "a live viewer posts no bounds");
  g.viewer.field16c = 0U;
  g.viewer.field14 = nullptr;
  g.viewer.field3c = nullptr;
  unresolved_005f3cf0(&g.viewer);
  check(g.trace.registry_calls == 0U, "a model-less viewer posts no bounds");
  g.viewer.field14 = &g.viewer;
  g.trace.model_ready = 0U;
  unresolved_005f3cf0(&g.viewer);
  check(g.trace.registry_calls == 0U, "an empty model posts no bounds");
  g.trace.model_ready = 1U;
  g.transform.field90 = nullptr;
  unresolved_005f3cf0(&g.viewer);
  check(g.trace.registry_calls == 1U, "a plain model posts the bounds once");
  check(g.trace.registry_box[0].field00 == -2.0F, "the box takes the low x");
  check(g.trace.registry_box[0].field0c == 3.0F, "the box takes the high y");
  check(g.trace.registry_mode[0] == 6U, "a detached viewer asks for mode six");
  check(g.trace.registry_scale[0] == bits_of(1.2F),
        "a detached viewer keeps the default scale");
  check(g.transform.field0c == -0.5F,
        "the transform keeps the negated centre x");
  check(g.transform.field10 == 0.0F,
        "the transform keeps the negated centre y");
  check(g.transform.field14 == -2.5F,
        "the transform keeps the negated centre z");
  check((g.transform.field08 & 4U) != 0U, "the transform flag is raised");
}

void test_build_bounds_attached() {
  bind();
  g.viewer.field14 = &g.viewer;
  g.viewer.fieldf0 = reinterpret_cast<OpaqueSub *>(&g.addref);
  g.trace.model_ready = 1U;
  g.transform.field90 = &g.feature;
  g.trace.xf_resolves = 1U;
  g.trace.xf_seed.field00 = 7.0F;
  g.trace.xf_seed.field04 = 8.0F;
  g.trace.xf_seed.field08 = 9.0F;
  g.trace.xf_seed.field0c = 10.0F;
  g.trace.xf_seed.field10 = 11.0F;
  g.trace.xf_seed.field14 = 12.0F;
  unresolved_005f3cf0(&g.viewer);
  check(g.trace.xf_resolves == 1U, "the feature probe runs once");
  check(g.trace.xf_copies == 2U, "the feature seed is copied twice");
  check(g.trace.registry_box[0].field00 == 7.0F,
        "the feature seed replaces the box");
  check(g.trace.registry_box[0].field14 == 12.0F,
        "the feature seed reaches the box tail");
  check(g.trace.registry_mode[0] == 0U,
        "an attached viewer asks for mode zero");
  check(g.trace.xf_init == 0U, "an attached viewer skips the local frame");
  check(g.transform.field0c == 0.0F, "an attached viewer keeps the transform");
}

void test_build_scale_override() {
  bind();
  g.viewer.field14 = &g.viewer;
  g.trace.zoom_ready = 1U;
  g.viewer.fieldf0 = reinterpret_cast<OpaqueSub *>(&g.addref);
  g.trace.model_ready = 1U;
  g.trace.service_result = 1U;
  g.trace.service_fill = 0U;
  unresolved_005f3cf0(&g.viewer);
  check(g.trace.service_resolve_calls == 1U, "the service is asked once");
  check(g.trace.service_arg0[0] == 0x1111U, "the service sees the first key");
  check(g.trace.service_arg1[0] == 0x3333U, "the service sees the second key");
  check(g.trace.property_probe_id == 0x005cd5de9U, "the scale key is probed");
  check(g.trace.registry_scale[0] == bits_of(1.0F),
        "an unfilled property falls back to the attached scale");
  check(g.trace.property_release == 1U, "the property is released once");
  g.trace.service_fill = 1U;
  g.trace.scale_value[0] = 4.5F;
  unresolved_005f3cf0(&g.viewer);
  check(g.trace.scale_calls == 1U, "a filled property is read once");
  check(g.trace.registry_scale[1] == bits_of(4.5F),
        "a filled property supplies the scale");
  check(g.trace.property_release == 2U,
        "the second pass releases the property again");
  g.viewer.fieldf0 = nullptr;
  g.trace.service_result = 0U;
  g.trace.scale_calls = 0U;
  unresolved_005f3cf0(&g.viewer);
  check(g.trace.registry_scale[2] == bits_of(1.2F),
        "a detached viewer keeps the default scale");
}

void test_initialise_state() {
  bind();
  g.viewer.field18c = nullptr;
  OpaqueKey3 name;
  name.field00 = 0x11U;
  name.field04 = 0x22U;
  name.field08 = 0x33U;
  OpaqueViewer *old_window = &g.spare;
  old_window->vtable = reinterpret_cast<OpaqueViewerVtable *>(&g.addref_vtable);
  g.viewer.field18c = reinterpret_cast<OpaqueAddRef *>(old_window);
  g.viewer.field180 = &g.host;
  g.viewer.field17c = &g.source;
  g.viewer.field198 = 0U;
  g.viewer.field199 = 0U;
  g.trace.zoom_ready = 0U;
  unresolved_005f4310(&g.viewer, &name, 0U, &g.addref, 0x99U, &g.host,
                      &g.source, 1U);
  check(g.viewer.field40 == 0x11U, "the initialiser copies the first key word");
  check(g.viewer.field44 == 0x22U, "the initialiser copies the second word");
  check(g.viewer.field48 == 0x33U, "the initialiser copies the third word");
  check(g.trace.viewer_name_arg == 0x11U, "a non-zero name drives slot 0x24");
  check(g.viewer.field18c == &g.addref, "the window slot adopts the window");
  check(g.viewer.field190 == 0x99U, "the message word is stored");
  check(g.viewer.field199 == 1U, "the flag byte is stored");
  check(g.viewer.opaque184 == 0U,
        "an unusable source leaves the viewer unlocked");
  check(g.trace.app_slot[0] == 0x24U,
        "the initialiser notifies the app system");
  check(g.trace.app_arg2[0] == 0x03150c27U, "the notify carries its token");
  check(g.trace.probe_calls == 2U, "the source is consulted twice");
  check(g.trace.launch_calls == 1U, "the initialiser spawns one object");
  check(g.trace.launch_arg0[0] == 0x11U, "the spawn carries the name key");
  check(g.trace.zoom_calls == 0U, "an empty model skips the zoom helper");
}

void test_initialise_window_pair() {
  bind();
  g.viewer.field18c = &g.addref;
  g.viewer.field198 = 0U;
  g.trace.model_ready = 0U;
  g.trace.probe_usable = 1U;
  g.trace.extent_frame.field00 = 1.0F;
  g.trace.extent_frame.field04 = 2.0F;
  g.trace.extent_frame.field08 = 3.0F;
  g.trace.extent_frame.field0c = 4.0F;
  OpaqueKey3 name;
  name.field00 = 0U;
  name.field04 = 0U;
  name.field08 = 0U;
  unresolved_005f4310(&g.viewer, &name, 0U, &g.addref, 0x99U, &g.host,
                      &g.source, 0U);
  check(g.trace.launch_calls == 1U, "the spawn still runs for a zero name");
  check(g.viewer.field174 == g.source.field1c || g.viewer.field174 == 0U,
        "the model word is mirrored when the source carries one");
  check(g.trace.build_calls == 2U, "two windows are built");
  check(g.trace.build_key[0][0] == 0x1249ff0fU, "the first window key head");
  check(g.trace.build_key[0][2] == 0x100d976eU, "the first window key tail");
  check(g.trace.build_key[1][0] == 0x3cf13a01U, "the second window key head");
  check(g.trace.build_key[1][2] == 0x011c0bdeU, "the second window key tail");
  check(g.viewer.field1b8 != nullptr, "the first window is stored");
  check(g.viewer.field1bc != nullptr, "the second window is stored");
  check(g.trace.extent_pair_arg0 == 0x10U,
        "the window pair slot is driven with sixteen");
  check(g.viewer.opaque184 == 1U, "a usable source locks the viewer");
  check(g.trace.clock_calls == 1U, "the clock is armed once");
  check(g.trace.clock_arg == 4U, "the clock is armed with four");
  check(g.trace.alpha_calls == 2U, "the alpha helper runs twice");
  check(g.trace.alpha_value[0] == 0U, "the alpha helper passes a zero");
}

void test_initialise_window_failure() {
  bind();
  g.viewer.field18c = &g.addref;
  g.viewer.field198 = 0U;
  g.trace.model_ready = 0U;
  g.trace.probe_usable = 1U;
  g.trace.build_denied = 0U;
  OpaqueKey3 name;
  name.field00 = 0U;
  name.field04 = 0U;
  name.field08 = 0U;
  unresolved_005f4310(&g.viewer, &name, 0U, &g.addref, 0x99U, &g.host,
                      &g.source, 0U);
  check(g.trace.build_calls == 1U, "the first build is attempted");
  check(g.viewer.field1b8 == nullptr, "a denied build leaves the slot empty");
  check(g.viewer.opaque184 == 0U, "a denied build leaves the viewer unlocked");
  check(g.trace.app_slot[0] == 0x24U,
        "a denied build still notifies the app system");
  check(g.trace.build_calls == 1U, "a denied build stops before the second");
}

void test_initialise_source_swap() {
  bind();
  g.viewer.field18c = &g.addref;
  g.viewer.field198 = 0U;
  g.trace.model_ready = 0U;
  g.viewer.field17c = &g.source;
  g.source.field1c = 0x4242U;
  g.source.field30 = 0U;
  g.trace.probe_usable = 0U;
  OpaqueKey3 name;
  name.field00 = 0U;
  name.field04 = 0U;
  name.field08 = 0U;
  unresolved_005f4310(&g.viewer, &name, 0U, &g.addref, 0x99U, &g.host,
                      &g.source, 0U);
  check(g.viewer.fieldea == 0U, "the mirror byte follows the source");
  check(g.viewer.field174 == 0x4242U, "the model word follows the source");
  check(g.viewer.opaque160 == 0U, "a model word clears the built byte");
  check(g.trace.build_calls == 0U, "an unusable source builds no window");
  g.viewer.field17c = nullptr;
  g.viewer.fieldea = 1U;
  unresolved_005f4310(&g.viewer, &name, 0U, &g.addref, 0x99U, &g.host,
                      &g.source, 0U);
  check(g.viewer.fieldea == 0U, "a cleared source leaves the mirror byte");
  check(g.trace.build_calls == 0U, "a cleared source builds no window");
}

void test_poll_gates() {
  bind();
  g.viewer.opaque184 = 1U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.probe_index == 0U, "a locked viewer consults nothing");
  bind();
  g.viewer.field4c = 0U;
  g.viewer.field118 = nullptr;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.probe_index == 0U, "an idle viewer consults nothing");
  g.viewer.field118 = &g.transform;
  g.trace.probe_state_value = 1U;
  g.viewer.field198 = 0U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.probe_index == 3U, "an active viewer consults the probe");
  check(g.trace.probe_arg[2] == 0U,
        "a cleared first word selects the fallback slot");
  g.viewer.field4c = 0x1111U;
  g.trace.probe_index = 0U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.probe_arg[2] == 0x1111U,
        "a filled first word selects the primary slot");
  g.viewer.opaque184 = 1U;
  g.trace.probe_index = 0U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.probe_index == 0U, "the locked gate precedes the probe");
}

void test_poll_states() {
  bind();
  g.trace.probe_state_value = 3U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.log_id[0] == 0x0dc91625aU, "state three logs the retry token");
  check(g.trace.log_value[0] == 0x99aabbccU,
        "state three logs the context word");
  check(g.trace.host_live_calls == 0U, "state three stops before the poll");
  bind();
  g.trace.probe_state_value = 2U;
  g.viewer.field198 = 0U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.log_calls == 0U, "state two stays quiet without the flag");
  check(g.trace.host_live_calls == 0U, "state two stops before the poll");
  g.viewer.field198 = 1U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.log_id[0] == 0x04fc39619U, "state two logs the busy token");
  bind();
  g.trace.probe_state_value = 7U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.log_calls == 0U, "an unknown state stays quiet");
  check(g.trace.host_live_calls == 0U,
        "an unknown state stops before the poll");
}

void test_poll_detach() {
  bind();
  g.viewer.field198 = 1U;
  g.viewer.field100 = 0x71fa7d3fU;
  g.trace.probe_state_value = 1U;
  g.trace.peer_value = 0x4242U;
  g.trace.extent_out.field00 = 1.5F;
  g.trace.extent_out.field04 = 2.5F;
  g.trace.post_sink[0] = reinterpret_cast<std::uint32_t>(&g.swatchhost);
  unresolved_005f49f0(&g.viewer);
  check(g.trace.host_live_calls == 1U, "the detach poll runs once");
  check(g.trace.peer_calls == 1U, "the detach path reads the peer");
  check(g.trace.peer_acquires == 1U, "the detach path acquires the peer once");
  check(g.trace.log_id[0] == 0x0e5469985U, "the detach path logs its token");
  check(g.trace.log_value[0] == 0x4242U, "the detach path logs the peer word");
  check(g.viewer.field1c0 == 1.5F, "the detach path stores the pair head");
  check(g.viewer.field1c4 == 2.5F, "the detach path stores the pair tail");
  check(g.trace.viewer_window_arg0 == 0U,
        "the detach path opens the viewer window with a zero word");
  check(g.trace.viewer_window_arg1 == 1U,
        "the detach path opens the viewer window with the enable word");
  g.trace.peer_present = 0U;
  g.trace.log_calls = 0U;
  g.trace.probe_state_value = 1U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.log_value[0] == 0U, "a missing peer logs a zero word");
}

void test_poll_on_outside() {
  bind();
  g.viewer.field198 = 0U;
  g.viewer.field100 = 0x5e71ab9bU;
  g.trace.probe_state_value = 1U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.detach_calls == 1U, "the detached word drives slot 0x60");
  bind();
  g.viewer.field198 = 0U;
  g.viewer.field100 = 0U;
  g.trace.probe_state_value = 1U;
  unresolved_005f49f0(&g.viewer);
  check(g.trace.detach_calls == 0U, "an unknown word drives no slot");
}

void test_paint_extents() {
  bind();
  g.trace.extent_out.field00 = 3.0F;
  g.trace.extent_out.field04 = 4.0F;
  g.viewer.field180 = nullptr;
  g.viewer.field194 = nullptr;
  unresolved_005f4b80(&g.viewer);
  check(g.viewer.opaque169 == 0U, "the paint clears the reset byte");
  check(g.viewer.field84 == 4.0F, "the paint stores the half height");
  check(g.viewer.field8c == 4.0F, "the paint mirrors the half height");
  check(g.viewer.field88 == 3.0F, "the paint stores the half width");
  check(g.viewer.field90 == 3.0F, "the paint mirrors the half width");
  check(g.trace.xf_applied_box.field00 == 0.0F, "no local frame is built");
  g.viewer.field180 = &g.host;
  const std::uint32_t retain_before = g.trace.ref_retain;
  unresolved_005f4b80(&g.viewer);
  check(g.trace.ref_retain == retain_before + 1U,
        "the paint retains the item window");
  check(g.trace.ref_release == retain_before ? g.trace.ref_release : 1U,
        "the paint releases the item window again");
  check(g.trace.app_slot[0] == 0x14U, "the paint posts to the app system");
  check(g.trace.app_arg0[0] == g.viewer.field4c,
        "the paint post carries the first key word");
}

void test_paint_host_gate() {
  bind();
  g.viewer.field180 = nullptr;
  g.viewer.field194 = nullptr;
  g.trace.service_result = 1U;
  g.trace.host_match = 0x1234U;
  g.trace.host_probe = 0x1234U;
  unresolved_005f4b80(&g.viewer);
  check(g.trace.host_live == 0x0ee3f516eU, "the paint probes the host key");
  check(g.trace.app_reset == 1U, "a matching host resets the app system");
  check(g.trace.app_reset_arg == 0U, "the reset carries a zero word");
  g.trace.host_probe = 0x9999U;
  unresolved_005f4b80(&g.viewer);
  check(g.trace.app_reset == 1U, "a foreign host leaves the app system alone");
  g.trace.service_result = 0U;
  unresolved_005f4b80(&g.viewer);
  check(g.trace.app_reset == 1U, "a closed gate skips the reset");
}

}

int main() {
  using namespace openspore::reconstruction::pkg_advanced_palette_wave11;
  test_signature_shapes();
  test_factory_allocates_and_tags();
  test_factory_reuses_supplied();
  test_factory_allocation_failure();
  test_factory_replaces_live_item();
  test_rect_containment();
  test_dispatch_palette_round();
  test_dispatch_accept_path();
  test_dispatch_accept_guards();
  test_dispatch_rebuild_and_stamp();
  test_dispatch_terminal();
  test_dispatch_swatch_branch();
  test_dispatch_swatch_idle_path();
  test_dispatch_swatch_fallback();
  test_arm_gate();
  test_arm_gate_blocked();
  test_transform_sweep();
  test_launch_windows();
  test_build_bounds();
  test_build_bounds_attached();
  test_build_scale_override();
  test_initialise_state();
  test_initialise_window_pair();
  test_initialise_window_failure();
  test_initialise_source_swap();
  test_poll_gates();
  test_poll_states();
  test_poll_detach();
  test_poll_on_outside();
  test_paint_extents();
  test_paint_host_gate();
  if (g_failures == 0) {
    std::printf("model: all checks passed\n");
    return 0;
  }
  std::printf("model: %d checks failed\n", g_failures);
  return 1;
}
