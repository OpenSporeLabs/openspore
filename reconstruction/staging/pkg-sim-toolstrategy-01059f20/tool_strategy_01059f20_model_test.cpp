#include <cstdio>

#include "tool_strategy_01059f20.hpp"

#if defined(_MSC_VER)
#define PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL __thiscall
#define PKG_SIM_TOOLSTRATEGY_01059F20_CDECL __cdecl
#define PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL __stdcall
#else
#define PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL __attribute__((thiscall))
#define PKG_SIM_TOOLSTRATEGY_01059F20_CDECL __attribute__((cdecl))
#define PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_sim_toolstrategy_01059f20 {
namespace {

int g_checks = 0;
int g_failures = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

struct Trace {
  int precheck = 0;
  int casts = 0;
  int bridges = 0;
  int beam_add_refs = 0;
  int beam_releases = 0;
  int predicate_queries = 0;
  int gates = 0;
  int manager_gets = 0;
  int manager_sets = 0;
  int position_updates = 0;
  TargetWord manager_argument = 0;
  float updated[3] = {0.0f, 0.0f, 0.0f};
  void* cast_result = nullptr;
  bool cast_returns_null = false;
  bool precheck_result = true;
  bool gate_result = true;
  bool beam_predicate = true;
  bool bridge_clears_beam = false;
  cDefaultBeamProjectile* bridge_installs = nullptr;
  int last_precheck_param = 0;
};

Trace g_trace;

void PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
stub_add_ref_00(cDefaultBeamProjectile*) {
  ++g_trace.beam_add_refs;
}

void PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
stub_release_04(cDefaultBeamProjectile*) {
  ++g_trace.beam_releases;
}

bool PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
stub_predicate_2c(cDefaultBeamProjectile*) {
  ++g_trace.predicate_queries;
  return g_trace.beam_predicate;
}

bool PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL
stub_precheck_010568b0(cSpaceToolData*, const Vector3*, int param_4) {
  ++g_trace.precheck;
  g_trace.last_precheck_param = param_4;
  return g_trace.precheck_result;
}

bool PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
stub_gate_0104cd50(cSpaceToolData*) {
  ++g_trace.gates;
  return g_trace.gate_result;
}

cRelationshipManager g_manager;

cRelationshipManager* PKG_SIM_TOOLSTRATEGY_01059F20_CDECL
stub_manager_get_00b3d3c0() {
  ++g_trace.manager_gets;
  return &g_manager;
}

void PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
stub_manager_set_00b7c160(cRelationshipManager* manager, TargetWord value) {
  ++g_trace.manager_sets;
  check(manager == &g_manager, "relationship setter receives the singleton");
  g_trace.manager_argument = value;
}

void PKG_SIM_TOOLSTRATEGY_01059F20_CDECL
stub_position_update_01059170(cSpaceToolData*, float x, float y, float z) {
  ++g_trace.position_updates;
  g_trace.updated[0] = x;
  g_trace.updated[1] = y;
  g_trace.updated[2] = z;
}

void* PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
stub_cast_b8(cSpatialObject*, const OpaqueTypeEntry* entry) {
  ++g_trace.casts;
  check(entry == reinterpret_cast<const OpaqueTypeEntry*>(
                     static_cast<std::uintptr_t>(kToolOwnerCastTypeEntryVa)),
        "Cast receives the observed type entry");
  return g_trace.cast_returns_null ? nullptr : g_trace.cast_result;
}

bool PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
stub_bridge_48(OpaqueToolStrategy*, cSpaceToolData* pTool, const Vector3* aim) {
  ++g_trace.bridges;
  check(aim != nullptr, "bridge receives the copied aim point");
  check(aim->x == 1.5f && aim->y == -2.25f && aim->z == 3.0f,
        "bridge receives a copy of the the caller vector components");
  if (g_trace.bridge_clears_beam && pTool != nullptr) {
    pTool->mpBeam = nullptr;
  } else if (g_trace.bridge_installs != nullptr && pTool != nullptr) {
    pTool->mpBeam = g_trace.bridge_installs;
  }
  return true;
}

OpaqueBeamProjectileVTable g_beam_vtable = {
    stub_add_ref_00,
    stub_release_04,
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
     nullptr},
    stub_predicate_2c,
};

OpaqueSpatialObjectVTable g_owner_vtable = {
    {nullptr},
    stub_cast_b8,
};

OpaqueToolStrategyVTable g_strategy_vtable = {
    {nullptr},
    stub_bridge_48,
};

alignas(4) cSpatialObject g_owner = {&g_owner_vtable, {0}};
alignas(4) cDefaultBeamProjectile g_beam_a = {&g_beam_vtable, {}, 0, {0}};
alignas(4) cDefaultBeamProjectile g_beam_b = {&g_beam_vtable, {}, 0, {0}};
alignas(4) OpaqueToolStrategy g_strategy = {&g_strategy_vtable, {0}};

alignas(4) cSpaceToolData g_tool = {};

const Vector3 kAim = {1.5f, -2.25f, 3.0f};

void install_ports() {
  g_tool_strategy_01059f20_ports.tool_precheck_010568b0 =
      stub_precheck_010568b0;
  g_tool_strategy_01059f20_ports.tool_flags_picks_flora_0104cd50 =
      stub_gate_0104cd50;
  g_tool_strategy_01059f20_ports.relationship_manager_get_00b3d3c0 =
      stub_manager_get_00b3d3c0;
  g_tool_strategy_01059f20_ports.relationship_set_event_00b7c160 =
      stub_manager_set_00b7c160;
  g_tool_strategy_01059f20_ports.tool_position_update_01059170 =
      stub_position_update_01059170;
}

void reset() {
  g_trace = Trace();
  g_beam_a.field_154 = 0;
  g_beam_b.field_154 = 0;
  g_tool.mpToolOwner = &g_owner;
  g_tool.mpBeam = nullptr;
  g_tool.mFlags = 0;
  g_trace.cast_result = &g_manager;
}

bool run_model() { return func_01059f20(&g_strategy, &g_tool, &kAim, 9); }

bool run_naked() { return naked_body_01059f20(&g_strategy, &g_tool, &kAim, 9); }

void test_precheck_rejection() {
  reset();
  g_trace.precheck_result = false;
  check(run_model() == true, "a rejecting precheck still returns true");
  check(g_trace.casts == 0, "a rejecting precheck skips the Cast query");
  check(g_trace.position_updates == 0,
        "a rejecting precheck skips the position update");
  check(g_trace.last_precheck_param == 9,
        "the fourth argument is forwarded to the precheck unchanged");
}

void test_null_cast_result() {
  reset();
  g_trace.cast_returns_null = true;
  check(run_model() == true, "a null Cast result still returns true");
  check(g_trace.casts == 1, "the Cast query runs once");
  check(g_trace.bridges == 0, "a null Cast result skips the strategy bridge");
  check(g_trace.position_updates == 0,
        "a null Cast result skips the position update");
}

void test_null_tool_owner() {
  reset();
  g_tool.mpToolOwner = nullptr;
  g_tool.mpBeam = &g_beam_a;
  check(run_model() == true, "a null tool owner still returns true");
  check(g_trace.casts == 0, "a null tool owner issues no Cast query");
  check(g_trace.beam_add_refs == 0, "a null tool owner never touches the beam");
  check(g_trace.position_updates == 0,
        "a null tool owner skips the position update");
}

void test_no_beam_bridges_and_updates() {
  reset();
  check(run_model() == true, "the beam-free path returns true");
  check(g_trace.beam_add_refs == 0, "no beam is acquired when mpBeam is null");
  check(g_trace.bridges == 1, "the strategy bridge runs on the beam-free path");
  check(g_trace.gates == 0, "the flora gate is not reached without a beam");
  check(g_trace.position_updates == 1, "the position update still runs");
  check(g_trace.updated[0] == 1.5f && g_trace.updated[1] == -2.25f &&
            g_trace.updated[2] == 3.0f,
        "the position update receives the caller three components");
}

void test_live_beam_full_path() {
  reset();
  g_tool.mpBeam = &g_beam_a;
  check(run_model() == true, "the live-beam path returns true");
  check(g_trace.beam_add_refs == 1, "the beam is acquired once");
  check(g_trace.beam_releases == 1, "the beam is released once");
  check(g_trace.predicate_queries == 1, "vtable word 0x2c is queried once");
  check(g_trace.bridges == 1, "the strategy bridge runs once");
  check(g_trace.gates == 1, "the flora gate is evaluated once");
  check(g_trace.manager_gets == 1,
        "the relationship singleton is fetched once");
  check(g_trace.manager_sets == 1, "the relationship setter runs once");
  check(g_trace.manager_argument == kRelationshipSetterArgument,
        "the relationship setter receives the observed constant argument");
  check(g_beam_a.field_154 == 1,
        "the beam flagged field is set before release");
  check(g_trace.position_updates == 1, "the position update runs once");
}

void test_zero_word_2c_skips_middle() {
  reset();
  g_tool.mpBeam = &g_beam_a;
  g_trace.beam_predicate = false;
  check(run_model() == true, "the clear-word-0x2c path returns true");
  check(g_trace.beam_add_refs == 1, "the beam is still acquired");
  check(g_trace.predicate_queries == 1, "vtable word 0x2c is queried once");
  check(g_trace.bridges == 0, "a clear word 0x2c skips the strategy bridge");
  check(g_trace.gates == 0, "a clear word 0x2c skips the flora gate");
  check(g_trace.manager_sets == 0,
        "a clear word 0x2c skips the relationship setter");
  check(g_beam_a.field_154 == 1, "the tail still sets the beam flagged field");
  check(g_trace.position_updates == 1,
        "the tail still runs the position update");
  check(g_trace.beam_releases == 1, "the beam is still released");
}

void test_set_word_2c_takes_bridge_path() {
  reset();
  g_tool.mpBeam = &g_beam_a;
  g_trace.beam_predicate = true;
  check(run_model() == true, "the set-word-0x2c path returns true");
  check(g_trace.beam_add_refs == 1, "the beam is acquired");
  check(g_trace.bridges == 1,
        "a set word 0x2c is exactly what selects the bridge path");
  check(g_trace.gates == 1, "the flora gate is evaluated once");
}

void test_clear_gate_skips_relationship() {
  reset();
  g_tool.mpBeam = &g_beam_a;
  g_trace.gate_result = false;
  check(run_model() == true, "a clear flora gate still returns true");
  check(g_trace.gates == 1, "the flora gate is evaluated once");
  check(g_trace.manager_gets == 0,
        "a clear flora gate never fetches the relationship singleton");
  check(g_trace.manager_sets == 0,
        "a clear flora gate never runs the relationship setter");
  check(g_beam_a.field_154 == 1,
        "a clear flora gate still sets the beam field");
}

void test_bridge_installs_another_beam() {
  reset();
  g_tool.mpBeam = &g_beam_a;
  g_trace.bridge_installs = &g_beam_b;
  check(run_model() == true, "the beam-swap path returns true");
  check(g_trace.beam_add_refs == 2,
        "the bridge-installed beam is acquired after the original");
  check(g_trace.beam_releases == 2,
        "the original beam is released on the swap, the installed one at the "
        "tail");
  check(g_beam_b.field_154 == 1,
        "the flagged field lands on the beam installed by the bridge");
  check(g_beam_a.field_154 == 0,
        "the flagged field does not land on the released beam");
  check(g_trace.position_updates == 1, "the position update still runs once");
}

void test_bridge_clears_the_beam() {
  reset();
  g_tool.mpBeam = &g_beam_a;
  g_trace.bridge_clears_beam = true;
  check(run_model() == true, "the beam-clear path returns true");
  check(g_trace.beam_add_refs == 1, "the original beam is acquired once");
  check(g_trace.beam_releases == 1, "the original beam is released once");
  check(g_beam_a.field_154 == 0,
        "no beam is held at the tail, so nothing is flagged");
  check(g_trace.position_updates == 1, "the position update still runs once");
}

void test_stable_beam_is_not_reswapped() {
  reset();
  g_tool.mpBeam = &g_beam_a;
  check(run_model() == true, "the stable-beam path returns true");
  check(g_trace.beam_add_refs == 1,
        "an unchanged beam is not acquired a second time");
  check(g_trace.beam_releases == 1,
        "an unchanged beam is released exactly once, at the tail");
}

void test_naked_body_matches_model() {
  reset();
  g_tool.mpBeam = &g_beam_a;
  g_trace.bridge_installs = &g_beam_b;
  const Trace model_trace = [&] {
    const bool result = run_model();
    check(result == true, "the model path returns true");
    return g_trace;
  }();
  const int model_add_refs = model_trace.beam_add_refs;
  const int model_releases = model_trace.beam_releases;
  const int model_bridges = model_trace.bridges;
  const int model_gates = model_trace.gates;
  const int model_sets = model_trace.manager_sets;
  const int model_updates = model_trace.position_updates;
  const TargetWord model_argument = model_trace.manager_argument;
  const std::uint8_t model_field = g_beam_b.field_154;

  reset();
  g_tool.mpBeam = &g_beam_a;
  g_trace.bridge_installs = &g_beam_b;
  check(run_naked() == true, "the staged naked body returns true");
  check(g_trace.beam_add_refs == model_add_refs,
        "naked body and model agree on the acquire count");
  check(g_trace.beam_releases == model_releases,
        "naked body and model agree on the release count");
  check(g_trace.bridges == model_bridges,
        "naked body and model agree on the bridge count");
  check(g_trace.gates == model_gates,
        "naked body and model agree on the gate count");
  check(g_trace.manager_sets == model_sets,
        "naked body and model agree on the relationship setter count");
  check(g_trace.position_updates == model_updates,
        "naked body and model agree on the position update count");
  check(g_trace.manager_argument == model_argument,
        "naked body and model agree on the relationship setter argument");
  check(g_beam_b.field_154 == model_field,
        "naked body and model agree on the flagged beam field");
}

void test_abi_surface() {
  static_assert(sizeof(Vector3) == 12, "Vector3 is three floats");
  static_assert(kStackCleanupBytes == 12, "the callee pops three stack words");
  static_assert(offsetof(cSpaceToolData, mpBeam) == 0x124, "mpBeam offset");
  static_assert(offsetof(cDefaultBeamProjectile, field_154) == 0x154,
                "flagged beam field offset");
  static_assert(offsetof(OpaqueToolStrategyVTable, bridge_48) == 0x48,
                "strategy bridge slot offset");
  static_assert(offsetof(OpaqueBeamProjectileVTable, predicate_2c) == 0x2c,
                "beam word 0x2c offset");
  static_assert(offsetof(OpaqueSpatialObjectVTable, cast_b8) == 0xb8,
                "spatial object Cast slot offset");
  check(true, "the static assertions hold");
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_sim_toolstrategy_01059f20;
  install_ports();
  test_precheck_rejection();
  test_null_cast_result();
  test_null_tool_owner();
  test_no_beam_bridges_and_updates();
  test_live_beam_full_path();
  test_zero_word_2c_skips_middle();
  test_set_word_2c_takes_bridge_path();
  test_clear_gate_skips_relationship();
  test_bridge_installs_another_beam();
  test_bridge_clears_the_beam();
  test_stable_beam_is_not_reswapped();
  test_naked_body_matches_model();
  test_abi_surface();
  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
