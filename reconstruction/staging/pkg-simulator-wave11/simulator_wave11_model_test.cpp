#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

#include "simulator_wave11.hpp"

namespace openspore::reconstruction::pkg_simulator_wave11 {
namespace {

static_assert(std::is_void<decltype(dispatch_key_00628450(
                  static_cast<OpaqueObject00628 *>(nullptr), TargetWord{0},
                  TargetWord{0}, TargetWord{0}))>::value,
              "00628450 returns no value on any path");
static_assert(
    std::is_same<
        decltype(cycle_key_006286a0(static_cast<OpaqueEditor00628 *>(nullptr))),
        TargetWord>::value,
    "006286a0 is a thiscall on the receiver alone, with no stack argument, and "
    "returns a full unsigned word in eax");
static_assert(std::is_same<decltype(forward_key_00628af0(
                               static_cast<OpaqueEditor00628 *>(nullptr),
                               TargetWord{0}, TargetWord{0})),
                           TargetByte>::value,
              "00628af0 returns a single byte in al");
static_assert(
    std::is_same<decltype(route_key_00628d50(
                     static_cast<OpaqueEditor00628 *>(nullptr), TargetWord{0})),
                 TargetByte>::value,
    "00628d50 returns a single byte in al");
static_assert(std::is_void<decltype(release_child_0062c910(
                  static_cast<OpaqueEditor00628 *>(nullptr)))>::value,
              "0062c910 returns no value on any path");

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

enum Step : TargetWord {
  kStepProvider = 1u,
  kStepAcquire,
  kStepSlot04,
  kStepSlot08,
  kStepBlend,
  kStepDebugWord,
  kStepPeer24,
  kStepDirect,
  kStepAssetProbe,
  kStepPeer2c,
  kStepQuery,
  kStepSelect,
  kStepPrepare,
  kStepAssetView,
  kStepResolve,
  kStepRandom,
  kStepSubmit,
  kStepDebugService,
  kStepEmit,
  kStepProbe,
  kStepApply,
  kStepPost,
  kStepSelectEntry,
  kStepInnerRelease,
};

constexpr TargetWord kStepLimit = 64u;
std::array<TargetWord, kStepLimit> g_order{};
TargetWord g_order_count = 0u;

void push_step(TargetWord step) {
  if (g_order_count < kStepLimit) {
    g_order[g_order_count] = step;
  }
  ++g_order_count;
}

template <std::size_t N>
bool order_is(const std::array<TargetWord, N> &expected) {
  if (g_order_count != expected.size()) {
    return false;
  }
  for (std::size_t i = 0u; i < expected.size(); ++i) {
    if (g_order[i] != expected[i]) {
      return false;
    }
  }
  return true;
}

constexpr TargetWord kAssetKey = 0x03f67620u;
constexpr TargetWord kSelectKey0 = 0x04581d50u;
constexpr TargetWord kSelectKey1 = 0x04581d78u;
constexpr TargetWord kSelectKey2 = 0x04581d90u;
constexpr TargetWord kOwnerHandle = 0x0badf00du;

struct StubObject {
  OpaqueObject00628 base;
  OpaqueVtable00628 vtable;
};

OpaqueObject00628 *as_object(StubObject *stub) {
  return &stub->base;
}

TargetWord address(const void *pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

StubObject g_provider{};
StubObject g_acquired{};
StubObject g_manager{};
StubObject g_asset{};
StubObject g_service{};
StubObject g_held_94{};
StubObject g_held_cc{};
StubObject g_held_0c{};
StubObject g_global{};
StubObject g_peers[4] = {};
StubObject g_select_targets[3] = {};
StubObject g_unmatched{};

OpaqueObject00628 *g_query_target = nullptr;
bool g_asset_present = true;
bool g_service_present = true;

TargetWord g_provider_calls = 0u;
TargetWord g_acquire_calls = 0u;
TargetWord g_slot04_calls = 0u;
std::array<const void *, 4> g_slot04_receiver = {};
TargetWord g_slot08_calls = 0u;
TargetWord g_slot08_key[4] = {};
TargetWord g_slot08_arg2[4] = {};
TargetWord g_slot08_arg3[4] = {};
std::array<const void *, 4> g_slot08_receiver = {};
TargetByte g_slot08_result = 0u;

TargetWord g_prepare_calls = 0u;
TargetWord g_asset_view_calls = 0u;
TargetWord g_asset_probe_calls = 0u;
TargetWord g_asset_probe_result = 0u;
TargetWord g_query_calls = 0u;
TargetWord g_query_argument = 0xffffffffu;
TargetWord g_select_calls = 0u;
TargetWord g_select_argument = 0xffffffffu;
std::uintptr_t g_select_target = 0u;

TargetWord g_resolve_calls = 0u;
TargetWord g_resolve_key[8] = {};

TargetWord g_route24_calls = 0u;
TargetWord g_route24_key[4] = {};
TargetWord g_route24_extra[4] = {};
TargetByte g_route24_result[4] = {};
TargetWord g_direct_calls = 0u;
TargetWord g_direct_argument = 0u;
TargetByte g_direct_result = 0u;

TargetWord g_random_calls = 0u;
TargetWord g_random_range = 0u;
TargetWord g_random_script[8] = {};
TargetWord g_random_next = 0u;
TargetWord g_random_count = 0u;

TargetWord g_submit_calls = 0u;
TargetWord g_submit_key = 0xffffffffu;
TargetByte g_submit_result = 0u;
TargetWord g_probe_calls = 0u;
TargetByte g_probe_result[4] = {};
TargetWord g_peer2c_calls = 0u;
TargetByte g_peer2c_result[4] = {};

TargetWord g_debug_service_calls = 0u;
TargetWord g_debug_word_calls = 0u;
TargetWord g_debug_word_value = 0u;
TargetWord g_emit_calls = 0u;
TargetWord g_emit_tag = 0u;
TargetWord g_emit_word = 0u;
TargetWord g_apply_calls = 0u;
TargetByte g_apply_state = 0u;

TargetWord g_blend_calls = 0u;
TargetWord g_blend_args[2][5] = {};
TargetWord g_post_calls = 0u;
TargetWord g_post_event = 0u;
TargetWord g_post_mask = 0u;
TargetFloat g_post_scale = 0.0f;
TargetFloat g_post_offset = 0.0f;
TargetWord g_select_entry_calls = 0u;
TargetWord g_select_entry_value = 0u;
TargetWord g_inner_release_calls = 0u;

void reset_counters() {
  g_order_count = 0u;
  g_provider_calls = 0u;
  g_acquire_calls = 0u;
  g_slot04_calls = 0u;
  g_slot08_calls = 0u;
  g_slot08_result = 0u;
  g_prepare_calls = 0u;
  g_asset_view_calls = 0u;
  g_asset_probe_calls = 0u;
  g_asset_probe_result = 0u;
  g_query_calls = 0u;
  g_query_argument = 0xffffffffu;
  g_select_calls = 0u;
  g_select_argument = 0xffffffffu;
  g_select_target = 0u;
  g_resolve_calls = 0u;
  g_route24_calls = 0u;
  g_direct_calls = 0u;
  g_direct_argument = 0u;
  g_direct_result = 0u;
  g_random_calls = 0u;
  g_random_range = 0u;
  g_random_next = 0u;
  g_random_count = 0u;
  g_submit_calls = 0u;
  g_submit_key = 0xffffffffu;
  g_submit_result = 0u;
  g_probe_calls = 0u;
  g_peer2c_calls = 0u;
  g_debug_service_calls = 0u;
  g_debug_word_calls = 0u;
  g_debug_word_value = 0u;
  g_emit_calls = 0u;
  g_emit_tag = 0u;
  g_emit_word = 0u;
  g_apply_calls = 0u;
  g_apply_state = 0u;
  g_blend_calls = 0u;
  g_post_calls = 0u;
  g_post_event = 0u;
  g_post_mask = 0u;
  g_post_scale = 0.0f;
  g_post_offset = 0.0f;
  g_select_entry_calls = 0u;
  g_select_entry_value = 0u;
  g_inner_release_calls = 0u;
  for (std::size_t i = 0u; i < 4u; ++i) {
    g_route24_result[i] = 0u;
    g_peer2c_result[i] = 0u;
  }
  g_query_target = nullptr;
  g_asset_present = true;
  g_service_present = true;
}

void arm_random(TargetWord first, TargetWord second, TargetWord third) {
  g_random_script[0] = first;
  g_random_script[1] = second;
  g_random_script[2] = third;
  g_random_count = 3u;
  g_random_next = 0u;
}

void arm_probes(TargetByte first, TargetByte second) {
  g_probe_result[0] = first;
  g_probe_result[1] = second;
}

template <typename Fn>
TargetWord as_word(Fn fn) {
  return reinterpret_cast<TargetWord>(fn);
}

void PKG_SIMULATOR_WAVE11_THISCALL stub_destroy_0004(OpaqueObject00628 *self) {
  push_step(kStepSlot04);
  if (g_slot04_calls < 4u) {
    g_slot04_receiver[g_slot04_calls] = self;
  }
  ++g_slot04_calls;
}

void PKG_SIMULATOR_WAVE11_THISCALL stub_release_0008(OpaqueObject00628 *self) {
  push_step(kStepSlot08);
  if (g_slot08_calls < 4u) {
    g_slot08_receiver[g_slot08_calls] = self;
  }
  ++g_slot08_calls;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL stub_dispatch_0008(
    OpaqueObject00628 *self, TargetWord key, TargetWord arg2, TargetWord arg3) {
  push_step(kStepSlot08);
  if (g_slot08_calls < 4u) {
    g_slot08_key[g_slot08_calls] = key;
    g_slot08_arg2[g_slot08_calls] = arg2;
    g_slot08_arg3[g_slot08_calls] = arg3;
    g_slot08_receiver[g_slot08_calls] = self;
  }
  ++g_slot08_calls;
  return g_slot08_result;
}

TargetFloat PKG_SIMULATOR_WAVE11_THISCALL
stub_blend_000c(OpaqueBlend00628 *, TargetWord a1, TargetWord a2, TargetWord a3,
                TargetWord a4, TargetWord a5) {
  push_step(kStepBlend);
  if (g_blend_calls < 2u) {
    g_blend_args[g_blend_calls][0] = a1;
    g_blend_args[g_blend_calls][1] = a2;
    g_blend_args[g_blend_calls][2] = a3;
    g_blend_args[g_blend_calls][3] = a4;
    g_blend_args[g_blend_calls][4] = a5;
  }
  ++g_blend_calls;
  return 0.0f;
}

TargetWord PKG_SIMULATOR_WAVE11_THISCALL stub_word_0020(OpaqueObject00628 *) {
  push_step(kStepDebugWord);
  ++g_debug_word_calls;
  return g_debug_word_value;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL stub_route24_0024(OpaqueObject00628 *,
                                                           TargetWord key,
                                                           TargetWord extra) {
  push_step(kStepPeer24);
  if (g_route24_calls < 4u) {
    g_route24_key[g_route24_calls] = key;
    g_route24_extra[g_route24_calls] = extra;
  }
  const TargetByte result = g_route24_result[g_route24_calls];
  ++g_route24_calls;
  return result;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL stub_direct_0024(OpaqueObject00628 *,
                                                          TargetWord key) {
  push_step(kStepDirect);
  ++g_direct_calls;
  g_direct_argument = key;
  return g_direct_result;
}

TargetWord PKG_SIMULATOR_WAVE11_THISCALL stub_asset_0028(OpaqueObject00628 *) {
  push_step(kStepAssetProbe);
  ++g_asset_probe_calls;
  return g_asset_probe_result;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL stub_route2c_002c(OpaqueObject00628 *,
                                                           TargetWord) {
  push_step(kStepPeer2c);
  const TargetByte result = g_peer2c_result[g_peer2c_calls];
  ++g_peer2c_calls;
  return result;
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_THISCALL
stub_query_0048(OpaqueObject00628 *, TargetWord argument) {
  push_step(kStepQuery);
  ++g_query_calls;
  g_query_argument = argument;
  return g_query_target;
}

void PKG_SIMULATOR_WAVE11_THISCALL stub_select_004c(OpaqueObject00628 *,
                                                    TargetWord argument,
                                                    OpaqueObject00628 *target) {
  push_step(kStepSelect);
  ++g_select_calls;
  g_select_argument = argument;
  g_select_target = reinterpret_cast<std::uintptr_t>(target);
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_THISCALL
stub_acquire_005c(OpaqueObject00628 *) {
  push_step(kStepAcquire);
  ++g_acquire_calls;
  return as_object(&g_acquired);
}

void PKG_SIMULATOR_WAVE11_THISCALL stub_prepare_0084(OpaqueObject00628 *) {
  push_step(kStepPrepare);
  ++g_prepare_calls;
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_CDECL port_provider_0067ddd0() {
  push_step(kStepProvider);
  ++g_provider_calls;
  return as_object(&g_provider);
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_CDECL port_view_manager_0067caa0() {
  return as_object(&g_manager);
}

TargetWord PKG_SIMULATOR_WAVE11_CDECL port_asset_view_00401030() {
  push_step(kStepAssetView);
  ++g_asset_view_calls;
  return 0u;
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_CDECL port_debug_service_00a206f0() {
  push_step(kStepDebugService);
  ++g_debug_service_calls;
  return as_object(&g_service);
}

void PKG_SIMULATOR_WAVE11_CDECL port_emit_debug_00435ed0(TargetWord tag,
                                                         TargetWord word) {
  push_step(kStepEmit);
  ++g_emit_calls;
  g_emit_tag = tag;
  g_emit_word = word;
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_THISCALL
port_resolve_00634e40(OpaqueObject00628 *, TargetWord key) {
  push_step(kStepResolve);
  if (g_resolve_calls < 8u) {
    g_resolve_key[g_resolve_calls] = key;
  }
  ++g_resolve_calls;
  if (key == kAssetKey) {
    return g_asset_present ? as_object(&g_asset) : nullptr;
  }
  if (key == kSelectKey0) {
    return as_object(&g_select_targets[0]);
  }
  if (key == kSelectKey1) {
    return as_object(&g_select_targets[1]);
  }
  if (key == kSelectKey2) {
    return as_object(&g_select_targets[2]);
  }
  return nullptr;
}

TargetWord PKG_SIMULATOR_WAVE11_THISCALL
port_random_00a68fb0(TargetWord *state, TargetWord range) {
  push_step(kStepRandom);
  ++g_random_calls;
  g_random_range = range;
  ++(*state);
  return g_random_next < g_random_count ? g_random_script[g_random_next++] : 0u;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL
port_submit_0062f7f0(OpaqueQueue00628 *, TargetWord key) {
  push_step(kStepSubmit);
  ++g_submit_calls;
  g_submit_key = key;
  return g_submit_result;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL
port_probe_0062f6c0(OpaqueQueue00628 *) {
  push_step(kStepProbe);
  const TargetByte result =
      g_probe_calls < 4u ? g_probe_result[g_probe_calls] : 0u;
  ++g_probe_calls;
  return result;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL
port_release_0062c340(OpaqueEditor00628 *) {
  push_step(kStepInnerRelease);
  ++g_inner_release_calls;
  return 0u;
}

void PKG_SIMULATOR_WAVE11_THISCALL port_apply_00628ca0(OpaqueEditor00628 *,
                                                       TargetByte state) {
  push_step(kStepApply);
  ++g_apply_calls;
  g_apply_state = state;
}

void PKG_SIMULATOR_WAVE11_THISCALL
port_post_event_00574110(OpaqueOwner00628 *, TargetWord event, TargetWord mask,
                         TargetFloat scale, TargetFloat offset) {
  push_step(kStepPost);
  ++g_post_calls;
  g_post_event = event;
  g_post_mask = mask;
  g_post_scale = scale;
  g_post_offset = offset;
}

void PKG_SIMULATOR_WAVE11_THISCALL port_select_005dbbb0(OpaqueOwner00628 *,
                                                        TargetWord value) {
  push_step(kStepSelectEntry);
  ++g_select_entry_calls;
  g_select_entry_value = value;
}

void clear_vtable(OpaqueVtable00628 *vtable) {
  std::memset(vtable, 0, sizeof(*vtable));
}

void setup_acquire(OpaqueVtable00628 *vtable) {
  clear_vtable(vtable);
  vtable->slot_5c = as_word(&stub_acquire_005c);
}

void setup_dispatch(OpaqueVtable00628 *vtable) {
  clear_vtable(vtable);
  vtable->slot_08 = as_word(&stub_dispatch_0008);
}

void setup_release(OpaqueVtable00628 *vtable) {
  clear_vtable(vtable);
  vtable->slot_08 = as_word(&stub_release_0008);
}

void setup_manager(OpaqueVtable00628 *vtable) {
  clear_vtable(vtable);
  vtable->slot_48 = as_word(&stub_query_0048);
  vtable->slot_4c = as_word(&stub_select_004c);
  vtable->slot_84 = as_word(&stub_prepare_0084);
}

void setup_asset(OpaqueVtable00628 *vtable) {
  clear_vtable(vtable);
  vtable->slot_28 = as_word(&stub_asset_0028);
}

void setup_service(OpaqueVtable00628 *vtable) {
  clear_vtable(vtable);
  vtable->slot_20 = as_word(&stub_word_0020);
}

void setup_destroy(OpaqueVtable00628 *vtable) {
  clear_vtable(vtable);
  vtable->slot_04 = as_word(&stub_destroy_0004);
}

void setup_peer(OpaqueVtable00628 *vtable) {
  clear_vtable(vtable);
  vtable->slot_24 = as_word(&stub_route24_0024);
  vtable->slot_2c = as_word(&stub_route2c_002c);
}

void bind_stub(StubObject *stub, void (*setup)(OpaqueVtable00628 *)) {
  setup(&stub->vtable);
  stub->base.vtable = &stub->vtable;
}

struct PortScope {
  SimulatorRuntime00628 saved;
  bool script_random;

  explicit PortScope(bool use_scripted_random)
      : saved(simulator_runtime_00628()), script_random(use_scripted_random) {
    simulator_runtime_00628().provider_0067ddd0 = port_provider_0067ddd0;
    simulator_runtime_00628().view_manager_0067caa0 =
        port_view_manager_0067caa0;
    simulator_runtime_00628().asset_view_00401030 = port_asset_view_00401030;
    simulator_runtime_00628().debug_service_00a206f0 =
        port_debug_service_00a206f0;
    simulator_runtime_00628().emit_debug_00435ed0 = port_emit_debug_00435ed0;
    simulator_runtime_00628().resolve_00634e40 = port_resolve_00634e40;
    if (script_random) {
      simulator_runtime_00628().random_00a68fb0 = port_random_00a68fb0;
    }
    simulator_runtime_00628().submit_0062f7f0 = port_submit_0062f7f0;
    simulator_runtime_00628().probe_0062f6c0 = port_probe_0062f6c0;
    simulator_runtime_00628().release_0062c340 = port_release_0062c340;
    simulator_runtime_00628().apply_00628ca0 = port_apply_00628ca0;
    simulator_runtime_00628().post_event_00574110 = port_post_event_00574110;
    simulator_runtime_00628().select_005dbbb0 = port_select_005dbbb0;
  }

  ~PortScope() {
    simulator_runtime_00628() = saved;
  }
};

struct Fixture {
  PortScope ports;
  OpaqueEditor00628 editor;
  OpaqueOwner00628 owner;
  OpaqueFlag00628 flag;
  OpaqueVtable00628 self_vtable;
  OpaqueVtable00628 blend_vtable;

  explicit Fixture(bool use_scripted_random = true)
      : ports(use_scripted_random) {
    std::memset(&editor, 0, sizeof(editor));
    std::memset(&owner, 0, sizeof(owner));
    std::memset(&flag, 0, sizeof(flag));
    std::memset(&self_vtable, 0, sizeof(self_vtable));
    std::memset(&blend_vtable, 0, sizeof(blend_vtable));
    reset_counters();

    bind_stub(&g_provider, setup_acquire);
    bind_stub(&g_acquired, setup_dispatch);
    bind_stub(&g_manager, setup_manager);
    bind_stub(&g_asset, setup_asset);
    bind_stub(&g_service, setup_service);
    bind_stub(&g_held_94, setup_destroy);
    bind_stub(&g_held_cc, setup_release);
    bind_stub(&g_held_0c, setup_destroy);
    bind_stub(&g_global, setup_release);
    bind_stub(&g_unmatched, setup_release);
    for (std::size_t i = 0u; i < 4u; ++i) {
      bind_stub(&g_peers[i], setup_peer);
    }
    for (std::size_t i = 0u; i < 3u; ++i) {
      bind_stub(&g_select_targets[i], setup_release);
    }

    self_vtable.slot_24 = as_word(&stub_direct_0024);
    blend_vtable.slot_0c = as_word(&stub_blend_000c);
    blend_vtable.slot_08 = as_word(&stub_release_0008);
    editor.vtable = &self_vtable;
    editor.field_3588.vtable = &blend_vtable;
    editor.field_0c = as_object(&g_manager);
    editor.field_cc = as_object(&g_held_cc);
    editor.field_3614 = &owner;
    owner.field_ac = &flag;
    owner.field_364 = kOwnerHandle;
    simulator_runtime_00628().global_015f7cf4 = nullptr;
    simulator_runtime_00628().random_state_01601760 = 0u;
  }

  void attach_peers() {
    editor.field_c8 = as_object(&g_peers[0]);
    editor.field_cc = as_object(&g_peers[1]);
    editor.field_d0 = as_object(&g_peers[2]);
    editor.field_d4 = as_object(&g_peers[3]);
  }
};

void test_dispatch_accepts_once() {
  Fixture fixture;
  g_slot08_result = 1u;
  dispatch_key_00628450(nullptr, 0x11223344u, 0x55667788u, 0x99aabbccu);
  check(g_provider_calls == 1u, "00628450 fetches the provider once");
  check(g_acquire_calls == 1u, "00628450 acquires once through slot 0x5c");
  check(g_slot08_calls == 1u, "00628450 dispatches once when accepted");
  check(g_slot08_key[0] == 0x11223344u, "00628450 forwards the key");
  check(g_slot08_arg2[0] == 0u, "00628450 pushes a zero middle argument");
  check(g_slot08_arg3[0] == 0x99aabbccu, "00628450 forwards the context");
  check(g_slot08_receiver[0] == as_object(&g_acquired),
        "00628450 dispatches on the acquired object");
}

void test_dispatch_falls_back() {
  Fixture fixture;
  g_slot08_result = 0u;
  dispatch_key_00628450(nullptr, 0x11223344u, 0x55667788u, 0x99aabbccu);
  check(g_slot08_calls == 2u, "00628450 dispatches twice when refused");
  check(g_slot08_key[1] == 0xe18d6423u,
        "00628450 replays the fallback key 0xe18d6423");
  check(g_slot08_arg2[1] == 0u,
        "00628450 pushes a zero middle argument on the fallback");
  check(g_slot08_arg3[1] == 0x99aabbccu,
        "00628450 keeps the context on the fallback");
  const std::array<TargetWord, 4> expected = {kStepProvider, kStepAcquire,
                                              kStepSlot08, kStepSlot08};
  check(order_is(expected), "00628450 acquires before it dispatches");
}

void test_dispatch_keeps_supplied_subject() {
  Fixture fixture;
  g_slot08_result = 1u;
  dispatch_key_00628450(as_object(&g_acquired), 0x1u, 0x2u, 0x3u);
  check(g_provider_calls == 0u, "00628450 skips the provider when supplied");
  check(g_acquire_calls == 0u, "00628450 skips the acquire when supplied");
  check(g_slot08_calls == 1u, "00628450 dispatches on the supplied subject");
  check(g_slot08_receiver[0] == as_object(&g_acquired),
        "00628450 keeps the supplied subject as the receiver");
}

void test_cycle_default_lcg() {
  Fixture fixture(false);
  const TargetWord first = cycle_key_006286a0(&fixture.editor);
  check(first == 0x0431df93u, "006286a0 maps the first lcg draw to 0x0431df93");
  check(simulator_runtime_00628().random_state_01601760 == 0x00003039u,
        "006286a0 leaves the lcg state at 0x00003039 after one draw");
  check(fixture.editor.state_36d4 == first,
        "006286a0 stores the accepted candidate at +0x36d4");
  const TargetWord second = cycle_key_006286a0(&fixture.editor);
  check(second == 0x044d7999u,
        "006286a0 redraws past a collision and lands on 0x044d7999");
  check(simulator_runtime_00628().random_state_01601760 == 0xa70427dfu,
        "006286a0 advances the lcg state to 0xa70427df after two draws");
  check(fixture.editor.state_36d4 == second,
        "006286a0 overwrites +0x36d4 with the later candidate");
}

void test_cycle_candidate_table() {
  const TargetWord expected[6] = {0x0431df93u, 0x0431df9au, 0x0431df9fu,
                                  0x0431dfa6u, 0x044d798cu, 0x044d7999u};
  for (TargetWord draw = 0u; draw < 6u; ++draw) {
    Fixture fixture;
    arm_random(draw, 0u, 0u);
    fixture.editor.state_36d4 = 0u;
    const TargetWord got = cycle_key_006286a0(&fixture.editor);
    check(got == expected[draw], "006286a0 maps a draw to its candidate");
    check(g_random_calls == 1u, "006286a0 accepts the first draw");
    check(g_random_range == 6u, "006286a0 draws from a range of six");
  }
}

void test_cycle_out_of_range_keeps_receiver_id() {
  Fixture fixture;
  arm_random(9u, 0u, 0u);
  fixture.editor.state_36d4 = 0u;
  const TargetWord got = cycle_key_006286a0(&fixture.editor);
  check(got == address(&fixture.editor),
        "006286a0 keeps the receiver derived id above the draw range");
  check(g_random_calls == 1u, "006286a0 leaves a distinct receiver id alone");
  check(fixture.editor.state_36d4 == address(&fixture.editor),
        "006286a0 stores the receiver derived id at +0x36d4");
}

void test_cycle_receiver_id_retries() {
  Fixture fixture;
  arm_random(9u, 0u, 0u);
  fixture.editor.state_36d4 = address(&fixture.editor);
  const TargetWord got = cycle_key_006286a0(&fixture.editor);
  check(got == 0x0431df93u,
        "006286a0 redraws while the receiver id collides with the stored one");
  check(g_random_calls == 2u,
        "006286a0 redraws once past the colliding receiver id");
  check(fixture.editor.state_36d4 == 0x0431df93u,
        "006286a0 stores the accepted candidate over the receiver id");
}

void test_cycle_retries_on_collision() {
  Fixture fixture;
  arm_random(0u, 0u, 1u);
  fixture.editor.state_36d4 = 0x0431df93u;
  const TargetWord got = cycle_key_006286a0(&fixture.editor);
  check(got == 0x0431df9au, "006286a0 redraws past a colliding candidate");
  check(g_random_calls == 3u, "006286a0 redraws once per collision");
  check(fixture.editor.state_36d4 == 0x0431df9au,
        "006286a0 overwrites +0x36d4 with the accepted candidate");
}

void test_forward_peer_or() {
  Fixture fixture;
  fixture.attach_peers();
  fixture.editor.field_cc = nullptr;
  g_route24_result[0] = 1u;
  g_route24_result[1] = 2u;
  g_route24_result[2] = 4u;
  const TargetByte got = forward_key_00628af0(&fixture.editor, 0x55u, 0x66u);
  check(got == 7u, "00628af0 ors the peer results into one byte");
  check(g_route24_calls == 3u, "00628af0 skips the empty peer slot");
  check(g_prepare_calls == 1u, "00628af0 prepares the view manager once");
  check(g_asset_view_calls == 1u, "00628af0 touches the asset view once");
  check(g_route24_key[0] == 0x55u && g_route24_extra[0] == 0x66u,
        "00628af0 forwards both peer arguments in order");
  check(g_select_calls == 0u, "00628af0 skips the select chain off key nine");
  check(g_order[0] == kStepPrepare && g_order[1] == kStepAssetView,
        "00628af0 prepares and reads the asset view before the peer walk");
}

void test_forward_direct_shortcut() {
  Fixture fixture;
  fixture.attach_peers();
  g_direct_result = 0xffu;
  const TargetByte got = forward_key_00628af0(&fixture.editor, 0x43u, 0u);
  check(got == 1u, "00628af0 answers one for the direct key");
  check(g_direct_calls == 1u, "00628af0 calls its own slot 0x24 once");
  check(g_direct_argument == 0x03a8ede4u,
        "00628af0 passes 0x03a8ede4 to its own slot 0x24");
  check(g_route24_calls == 0u,
        "00628af0 skips the peer walk on the direct key");
}

void test_forward_direct_needs_zero_extra() {
  Fixture fixture;
  fixture.attach_peers();
  g_route24_result[0] = 1u;
  const TargetByte got = forward_key_00628af0(&fixture.editor, 0x43u, 1u);
  check(got == 1u, "00628af0 accumulates when the extra argument is nonzero");
  check(g_direct_calls == 0u,
        "00628af0 keeps the direct shortcut away from a nonzero extra");
  check(g_route24_calls == 4u, "00628af0 walks every peer in that case");
}

void test_forward_select_rotation() {
  OpaqueObject00628 *const targets[4] = {
      as_object(&g_select_targets[0]), as_object(&g_select_targets[1]),
      as_object(&g_select_targets[2]), as_object(&g_unmatched)};
  const TargetWord probes[4] = {1u, 2u, 3u, 3u};
  const TargetWord action[4] = {kSelectKey1, kSelectKey2, kSelectKey0,
                                kSelectKey0};
  const TargetWord action_target[4] = {1u, 2u, 0u, 0u};
  for (TargetWord branch = 0u; branch < 4u; ++branch) {
    Fixture fixture;
    g_asset_probe_result = 1u;
    g_query_target = targets[branch];
    fixture.attach_peers();
    (void)forward_key_00628af0(&fixture.editor, 0x09u, 0u);
    check(g_asset_probe_calls == 1u, "00628af0 probes the asset once");
    check(g_query_calls == probes[branch],
          "00628af0 stops the select chain at the matching probe");
    check(g_select_calls == 1u,
          "00628af0 selects once when the chain resolves");
    check(g_query_argument == 0u, "00628af0 queries with a zero argument");
    check(g_select_argument == 0u, "00628af0 selects with a zero argument");
    check(g_resolve_key[g_resolve_calls - 1u] == action[branch],
          "00628af0 rotates the action key with the matched probe key");
    check(g_select_target == reinterpret_cast<std::uintptr_t>(as_object(
                                 &g_select_targets[action_target[branch]])),
          "00628af0 resolves the rotated action target");
  }
}

void test_forward_select_without_match() {
  Fixture fixture;
  g_asset_probe_result = 1u;
  g_query_target = as_object(&g_unmatched);
  fixture.attach_peers();
  (void)forward_key_00628af0(&fixture.editor, 0x09u, 0u);
  check(g_query_calls == 3u, "00628af0 exhausts all three select probes");
  check(g_select_calls == 1u, "00628af0 still selects after the last miss");
  check(g_resolve_key[g_resolve_calls - 1u] == kSelectKey0,
        "00628af0 falls back to the first action key");
  check(g_select_target ==
            reinterpret_cast<std::uintptr_t>(as_object(&g_select_targets[0])),
        "00628af0 falls back to the first action target");
}

void test_forward_select_gates() {
  Fixture cleared;
  cleared.attach_peers();
  g_asset_probe_result = 0u;
  g_query_target = as_object(&g_select_targets[0]);
  (void)forward_key_00628af0(&cleared.editor, 0x09u, 0u);
  check(g_query_calls == 0u, "00628af0 stops on a clear asset bit");
  check(g_select_calls == 0u, "00628af0 never selects on a clear asset bit");

  Fixture absent;
  absent.attach_peers();
  g_asset_present = false;
  g_asset_probe_result = 1u;
  g_query_target = as_object(&g_select_targets[0]);
  (void)forward_key_00628af0(&absent.editor, 0x09u, 0u);
  check(g_asset_probe_calls == 0u, "00628af0 never probes an unresolved asset");
  check(g_query_calls == 0u, "00628af0 stops on an unresolved asset");
}

void test_route_peer_fallback() {
  Fixture fixture;
  g_submit_result = 0u;
  fixture.attach_peers();
  g_peer2c_result[0] = 1u;
  g_peer2c_result[1] = 2u;
  g_peer2c_result[2] = 4u;
  g_peer2c_result[3] = 8u;
  const TargetByte got = route_key_00628d50(&fixture.editor, 0x77u);
  check(got == 15u, "00628d50 ors every peer result");
  check(g_peer2c_calls == 4u, "00628d50 crosses all four peers");
  check(g_emit_calls == 0u, "00628d50 skips the debug emit when refused");
  check(g_apply_calls == 0u, "00628d50 skips the apply when refused");
  check(g_submit_key == 0x77u, "00628d50 hands the key to the queue");
}

void test_route_flag_and_emit() {
  Fixture fixture;
  g_submit_result = 1u;
  g_debug_word_value = 0x1234u;
  arm_probes(1u, 1u);
  fixture.flag.field_04 = 0u;
  const TargetByte got = route_key_00628d50(&fixture.editor, 0x0101u);
  check(got == 1u, "00628d50 answers one on the accepted path");
  check(g_emit_calls == 1u, "00628d50 emits the debug tag once");
  check(g_emit_tag == 0x0a03e74b2u, "00628d50 emits tag 0x0a03e74b2");
  check(g_emit_word == 0x1234u, "00628d50 emits the service word");
  check(g_debug_word_calls == 1u, "00628d50 reads the debug word once");
  check(g_probe_calls == 2u, "00628d50 probes the queue twice");
  check(fixture.flag.field_04 == 1u, "00628d50 sets flag bit zero");
  check(g_apply_calls == 1u && g_apply_state == 1u,
        "00628d50 applies the second probe result");
  check(g_blend_calls == 0u, "00628d50 skips the blend off a route key");
  check(g_select_entry_calls == 0u,
        "00628d50 skips the selection off a route key");
}

void test_route_flag_clears() {
  Fixture fixture;
  g_submit_result = 1u;
  arm_probes(0u, 0u);
  fixture.flag.field_04 = 0xffffffffu;
  (void)route_key_00628d50(&fixture.editor, 0x0202u);
  check(fixture.flag.field_04 == 0xfffffffeu,
        "00628d50 clears only flag bit zero");
  check(g_apply_state == 0u, "00628d50 applies a zero probe result");
}

void test_route_null_flag() {
  Fixture fixture;
  g_submit_result = 1u;
  fixture.owner.field_ac = nullptr;
  arm_probes(1u, 1u);
  (void)route_key_00628d50(&fixture.editor, 0x0303u);
  check(g_probe_calls == 1u,
        "00628d50 probes once without a flag, skipping the flag gate");
  check(g_apply_calls == 1u && g_apply_state == 1u,
        "00628d50 still applies without a flag");
}

void test_route_null_service() {
  Fixture fixture;
  g_submit_result = 1u;
  arm_probes(0u, 0u);
  g_service_present = false;
  (void)route_key_00628d50(&fixture.editor, 0x0404u);
  check(g_emit_calls == 1u, "00628d50 still emits without a debug service");
  check(g_emit_word == 0u, "00628d50 emits a zero word without a service");
}

void test_route_blend_and_post() {
  Fixture fixture;
  g_submit_result = 1u;
  arm_probes(1u, 1u);
  arm_random(2u, 0u, 0u);
  fixture.editor.state_36d4 = 0u;
  (void)route_key_00628d50(&fixture.editor, 0x0445b018u);
  check(g_blend_calls == 2u, "00628d50 blends twice for a route key");
  check(g_blend_args[0][0] == kOwnerHandle,
        "00628d50 blends the owner handle first");
  check(g_blend_args[0][1] == 0x0431df9fu,
        "00628d50 blends the accepted cycle candidate second");
  check(g_blend_args[0][2] == 0u && g_blend_args[0][3] == 1u &&
            g_blend_args[0][4] == 0u,
        "00628d50 blends zero, one and zero in the last three slots");
  check(g_blend_args[1][0] == kOwnerHandle,
        "00628d50 keeps the owner handle on the constant blend");
  check(g_blend_args[1][1] == 0x04330667u,
        "00628d50 blends the constant 0x04330667 second");
  check(g_blend_args[1][2] == 1u && g_blend_args[1][3] == 0u &&
            g_blend_args[1][4] == 0u,
        "00628d50 blends one, zero and zero on the constant call");
  check(g_post_calls == 1u, "00628d50 posts one event for a route key");
  check(g_post_event == 0x70842ef6u, "00628d50 posts event 0x70842ef6");
  check(g_post_mask == 0xffffffffu, "00628d50 posts the all-ones mask");
  check(g_post_scale == 1.0f && g_post_offset == 0.0f,
        "00628d50 posts the 1.0 and 0.0 scale pair");
  check(g_select_entry_calls == 1u, "00628d50 selects once for 0x0445b018");
  check(g_select_entry_value == 0u, "00628d50 selects index zero first");
}

void test_route_selection_table() {
  const TargetWord keys[4] = {0x0445b018u, 0x0445b318u, 0x0445b340u,
                              0x0445b388u};
  for (TargetWord index = 0u; index < 4u; ++index) {
    Fixture fixture;
    g_submit_result = 1u;
    arm_probes(0u, 0u);
    arm_random(0u, 0u, 0u);
    fixture.editor.state_36d4 = 0u;
    (void)route_key_00628d50(&fixture.editor, keys[index]);
    check(g_select_entry_calls == 1u, "00628d50 selects once per route key");
    check(g_select_entry_value == index,
          "00628d50 maps each route key to its selection index");
    check(g_blend_calls == 2u, "00628d50 blends twice per route key");
    check(g_post_calls == 1u, "00628d50 posts once per route key");
  }
}

void test_route_seed_reaches_cycle() {
  Fixture fixture;
  g_submit_result = 1u;
  arm_probes(0u, 1u);
  arm_random(9u, 0u, 0u);
  fixture.editor.state_36d4 = 0u;
  (void)route_key_00628d50(&fixture.editor, 0x0445b388u);
  check(g_blend_calls == 2u, "00628d50 still blends for the last route key");
  check(g_blend_args[0][1] == address(&fixture.editor),
        "00628d50 feeds the receiver derived cycle id into the first blend");
  check(g_select_entry_value == 3u, "00628d50 maps 0x0445b388 to index three");
}

void test_release_order() {
  Fixture fixture;
  fixture.editor.field_94 = as_object(&g_held_94);
  fixture.editor.field_0c = as_object(&g_held_0c);
  fixture.editor.field_c8 = as_object(&g_peers[0]);
  simulator_runtime_00628().global_015f7cf4 = as_object(&g_global);
  release_child_0062c910(&fixture.editor);
  const std::array<TargetWord, 6> expected = {kStepSlot04, kStepInnerRelease,
                                              kStepSlot08, kStepSlot08,
                                              kStepSlot08, kStepSlot04};
  check(order_is(expected), "0062c910 releases in the recorded order");
  check(g_slot08_receiver[0] == as_object(&g_held_cc),
        "0062c910 releases the +0xcc holder first");
  check(g_slot08_receiver[1] == &fixture.editor.field_3588,
        "0062c910 releases the +0x3588 blend against its own address");
  check(g_slot08_receiver[2] == as_object(&g_global),
        "0062c910 releases the global holder third");
  check(fixture.editor.field_94 == nullptr, "0062c910 clears the +0x94 slot");
  check(fixture.editor.field_cc == nullptr, "0062c910 clears the +0xcc slot");
  check(fixture.editor.field_0c == nullptr, "0062c910 clears the +0x0c slot");
  check(simulator_runtime_00628().global_015f7cf4 == nullptr,
        "0062c910 clears the global slot");
}

void test_release_unconditional_ports() {
  Fixture fixture;
  fixture.editor.field_0c = nullptr;
  release_child_0062c910(&fixture.editor);
  const std::array<TargetWord, 2> expected = {kStepSlot08, kStepSlot08};
  check(order_is(expected), "0062c910 crosses only the unconditional ports");
  check(g_slot08_receiver[0] == as_object(&g_held_cc),
        "0062c910 keeps the +0xcc port first");
  check(g_slot08_receiver[1] == &fixture.editor.field_3588,
        "0062c910 always releases the +0x3588 blend");
  check(g_inner_release_calls == 0u,
        "0062c910 skips the inner release on an empty +0xc8 slot");
  check(fixture.editor.field_cc == nullptr,
        "0062c910 still clears the +0xcc slot");
  check(fixture.editor.field_0c == nullptr,
        "0062c910 leaves an empty +0x0c slot null");
  check(fixture.editor.field_94 == nullptr,
        "0062c910 leaves an empty +0x94 slot null");
}

}  // namespace

}  // namespace openspore::reconstruction::pkg_simulator_wave11

int main() {
  using namespace openspore::reconstruction::pkg_simulator_wave11;
  test_dispatch_accepts_once();
  test_dispatch_falls_back();
  test_dispatch_keeps_supplied_subject();
  test_cycle_default_lcg();
  test_cycle_candidate_table();
  test_cycle_out_of_range_keeps_receiver_id();
  test_cycle_receiver_id_retries();
  test_cycle_retries_on_collision();
  test_forward_peer_or();
  test_forward_direct_shortcut();
  test_forward_direct_needs_zero_extra();
  test_forward_select_rotation();
  test_forward_select_without_match();
  test_forward_select_gates();
  test_route_peer_fallback();
  test_route_flag_and_emit();
  test_route_flag_clears();
  test_route_null_flag();
  test_route_null_service();
  test_route_blend_and_post();
  test_route_selection_table();
  test_route_seed_reaches_cycle();
  test_release_order();
  test_release_unconditional_ports();

  if (g_failures == 0) {
    std::printf("ok: simulator wave11 model checks passed\n");
  } else {
    std::printf("failed: %d simulator wave11 model checks\n", g_failures);
  }
  return g_failures == 0 ? 0 : 1;
}
