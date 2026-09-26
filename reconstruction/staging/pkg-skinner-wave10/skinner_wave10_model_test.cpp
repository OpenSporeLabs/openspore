#include <cstddef>
#include <cstdint>
#include <cstring>

#include "skinner_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_TEST_CDECL __cdecl
#define PKG_TEST_THISCALL __thiscall
#else
#define PKG_TEST_CDECL __attribute__((cdecl))
#define PKG_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::pkg_skinner_wave10;

enum class Step : std::uint8_t {
  kNone,
  kAcquire,
  kCreate,
  kFloatRead,
  kPaintSystem,
  kProbe,
  kQuery,
  kStep,
  kReset,
  kManager,
  kSubmit,
  kAdvance,
};

struct Fixture {
  OpaquePainterState state{};
  OpaquePainterJob job{};
  OpaquePainterJobVTable job_vtable{};
  OpaquePaintSystem paint_system{};
  OpaqueSkinPainter skin_painter{};
  OpaqueGraphicsProbe probe{};
  OpaqueGraphicsProbeVTable probe_vtable{};
  OpaqueLightingManager manager{};
  OpaqueLightingManagerVTable manager_vtable{};

  std::uint8_t factory_storage[3][4]{};
  std::uint8_t painter_storage[3][4]{};
  std::uint8_t texture_storage[4]{};

  std::uint32_t null_factory_mask = 0u;
  TargetWord acquire_keys[3][6]{};
  std::size_t acquire_calls = 0;
  std::size_t create_calls = 0;
  TargetWord create_factory[3]{};
  TargetWord create_source[3][2]{};
  TargetWord float_address[5]{};
  float float_value[5]{};
  std::size_t float_calls = 0;
  bool query_result = false;
  std::size_t query_calls = 0;
  std::uint8_t step_results[8]{};
  std::size_t step_calls = 0;
  std::uint8_t advance_results[40]{};
  std::size_t advance_calls = 0;
  std::size_t reset_calls = 0;
  TargetWord reset_seen_field_000 = 0u;
  OpaqueSubmitState* reset_target = nullptr;
  OpaqueSubmitState submit_state{};
  TargetWord submit_arg_0 = 0xffffffffu;
  OpaqueSubmitState* submit_arg_1 = nullptr;
  OpaquePainterJob* submit_job = nullptr;
  std::size_t submit_calls = 0;
  Step trace[24]{};
  std::size_t trace_count = 0;
};

Fixture* current_fixture = nullptr;
std::size_t failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void append_step(Step step) {
  Fixture& fixture = *current_fixture;
  if (fixture.trace_count < 24) {
    fixture.trace[fixture.trace_count] = step;
  }
  ++fixture.trace_count;
}

OpaqueLayerFactory* PKG_TEST_CDECL
acquire_layer_factory(TargetWord key_0, TargetWord key_1, TargetWord zero_2,
                      TargetWord zero_3, TargetWord zero_4, TargetWord zero_5) {
  Fixture& fixture = *current_fixture;
  const std::size_t slot = fixture.acquire_calls;
  if (slot < 3) {
    fixture.acquire_keys[slot][0] = key_0;
    fixture.acquire_keys[slot][1] = key_1;
    fixture.acquire_keys[slot][2] = zero_2;
    fixture.acquire_keys[slot][3] = zero_3;
    fixture.acquire_keys[slot][4] = zero_4;
    fixture.acquire_keys[slot][5] = zero_5;
  }
  ++fixture.acquire_calls;
  append_step(Step::kAcquire);
  if (slot < 3 && ((fixture.null_factory_mask >> slot) & 1u) != 0u) {
    return nullptr;
  }
  return reinterpret_cast<OpaqueLayerFactory*>(
      &fixture.factory_storage[slot][0]);
}

OpaqueTexturePainter* PKG_TEST_THISCALL create_texture_painter(
    OpaqueLayerFactory* factory, TargetWord source_0, TargetWord source_1) {
  Fixture& fixture = *current_fixture;
  const std::size_t slot = fixture.create_calls;
  if (slot < 3) {
    fixture.create_factory[slot] = reinterpret_cast<TargetWord>(factory);
    fixture.create_source[slot][0] = source_0;
    fixture.create_source[slot][1] = source_1;
  }
  ++fixture.create_calls;
  append_step(Step::kCreate);
  return reinterpret_cast<OpaqueTexturePainter*>(
      &fixture.painter_storage[slot][0]);
}

float read_fixed_float(TargetWord address) {
  Fixture& fixture = *current_fixture;
  const std::size_t slot = fixture.float_calls;
  if (slot < 5) {
    fixture.float_address[slot] = address;
  }
  ++fixture.float_calls;
  append_step(Step::kFloatRead);
  if (slot < 5) {
    return fixture.float_value[slot];
  }
  return 0.0F;
}

OpaquePaintSystem* PKG_TEST_CDECL get_paint_system() {
  append_step(Step::kPaintSystem);
  return &current_fixture->paint_system;
}

OpaqueGraphicsProbe* PKG_TEST_CDECL get_graphics_probe() {
  append_step(Step::kProbe);
  return &current_fixture->probe;
}

OpaqueLightingManager* PKG_TEST_CDECL get_lighting_manager() {
  append_step(Step::kManager);
  return &current_fixture->manager;
}

OpaqueSubmitState* PKG_TEST_THISCALL
reset_submit_state(OpaqueSubmitState* state) {
  Fixture& fixture = *current_fixture;
  ++fixture.reset_calls;
  fixture.reset_seen_field_000 = state->field_000;
  fixture.reset_target = state;
  append_step(Step::kReset);
  state->field_000 = 1u;
  state->field_004 = 0u;
  state->field_008 = 1u;
  state->field_00c = 0u;
  state->field_010 = 0u;
  state->field_014 = 0u;
  state->field_018 = 0u;
  state->field_01c = 0u;
  state->field_020 = 0u;
  state->field_024 = 0u;
  state->field_028 = 0u;
  return state;
}

bool PKG_TEST_THISCALL query_graphics(OpaqueGraphicsProbe*) {
  Fixture& fixture = *current_fixture;
  ++fixture.query_calls;
  append_step(Step::kQuery);
  return fixture.query_result;
}

std::uint8_t PKG_TEST_THISCALL job_step(OpaquePainterJob* job) {
  Fixture& fixture = *current_fixture;
  const std::size_t slot = fixture.step_calls;
  ++fixture.step_calls;
  append_step(Step::kStep);
  check(job == &fixture.job);
  if (slot < 8) {
    return fixture.step_results[slot];
  }
  return 0u;
}

std::uint8_t PKG_TEST_THISCALL advance_job(OpaquePainterJob* job) {
  Fixture& fixture = *current_fixture;
  const std::size_t slot = fixture.advance_calls;
  ++fixture.advance_calls;
  append_step(Step::kAdvance);
  check(job == &fixture.job);
  if (slot < 40) {
    return fixture.advance_results[slot];
  }
  return 0u;
}

void PKG_TEST_THISCALL submit_paint_job(OpaqueLightingManager* manager,
                                        TargetWord zero_0,
                                        OpaqueSubmitState* state_1,
                                        OpaquePainterJob* job_2) {
  Fixture& fixture = *current_fixture;
  ++fixture.submit_calls;
  fixture.submit_arg_0 = zero_0;
  fixture.submit_arg_1 = state_1;
  fixture.submit_state = *state_1;
  fixture.submit_job = job_2;
  append_step(Step::kSubmit);
  check(manager == &fixture.manager);
}

void initialize(Fixture& fixture) {
  fixture = Fixture{};
  current_fixture = &fixture;

  fixture.job_vtable.job_step_014 = job_step;
  fixture.job_vtable.apply_brushes_01c = skin_painter_job_brush_pass_005182f0;
  fixture.probe_vtable.query_044 = query_graphics;
  fixture.manager_vtable.submit_074 = submit_paint_job;

  fixture.job.vtable_000 = &fixture.job_vtable;
  fixture.job.pass_014 = 0;
  fixture.paint_system.painter_00c = &fixture.skin_painter;
  fixture.skin_painter.texture_010 =
      reinterpret_cast<OpaqueSkinTexture*>(&fixture.texture_storage[0]);
  fixture.probe.vtable_000 = &fixture.probe_vtable;
  fixture.manager.vtable_000 = &fixture.manager_vtable;

  for (std::size_t index = 0; index < 5; ++index) {
    fixture.float_value[index] = 0.0F;
  }

  g_skinner_wave10_ports.acquire_layer_factory_00f473a0 = acquire_layer_factory;
  g_skinner_wave10_ports.create_texture_painter_005288f0 =
      create_texture_painter;
  g_skinner_wave10_ports.read_fixed_float = read_fixed_float;
  g_skinner_wave10_ports.get_paint_system_00401080 = get_paint_system;
  g_skinner_wave10_ports.get_graphics_probe_0067dd00 = get_graphics_probe;
  g_skinner_wave10_ports.reset_submit_state_00517240 = reset_submit_state;
  g_skinner_wave10_ports.get_lighting_manager_0067dd50 = get_lighting_manager;
  g_skinner_wave10_ports.advance_painter_job_00517430 = advance_job;
}

void finish() {
  g_skinner_wave10_ports = SkinnerWave10Ports{};
  current_fixture = nullptr;
}

void set_scale_values(Fixture& fixture) {
  fixture.float_value[0] = 0.5F;
  fixture.float_value[1] = 1.0F;
  fixture.float_value[2] = 20.0F;
  fixture.float_value[3] = 1.0F;
  fixture.float_value[4] = 1.0F;
}

OpaqueTexturePainter* expected_painter(const Fixture& fixture,
                                       std::size_t slot) {
  return reinterpret_cast<OpaqueTexturePainter*>(
      const_cast<std::uint8_t*>(&fixture.painter_storage[slot][0]));
}

void test_state_setup_populates_all_slots() {
  Fixture fixture{};
  initialize(fixture);
  set_scale_values(fixture);
  const TargetWord source = 0x0046a1c0u;

  skin_painter_state_setup_00506590(&fixture.state, source);

  check(fixture.acquire_calls == 3);
  check(fixture.create_calls == 3);
  check(fixture.state.texture_painter_010 == expected_painter(fixture, 0));
  check(fixture.state.texture_painter_014 == expected_painter(fixture, 1));
  check(fixture.state.texture_painter_018 == expected_painter(fixture, 2));
  check(fixture.state.source_01c == source);
  check(fixture.create_factory[0] ==
        reinterpret_cast<TargetWord>(&fixture.factory_storage[0][0]));
  check(fixture.create_factory[1] ==
        reinterpret_cast<TargetWord>(&fixture.factory_storage[1][0]));
  check(fixture.create_factory[2] ==
        reinterpret_cast<TargetWord>(&fixture.factory_storage[2][0]));
  for (std::size_t slot = 0; slot < 3; ++slot) {
    check(fixture.create_source[slot][0] == source);
    check(fixture.create_source[slot][1] == source);
  }
  check(fixture.trace_count == 11);
  check(fixture.trace[0] == Step::kAcquire);
  check(fixture.trace[1] == Step::kCreate);
  check(fixture.trace[2] == Step::kAcquire);
  check(fixture.trace[3] == Step::kCreate);
  check(fixture.trace[4] == Step::kAcquire);
  check(fixture.trace[5] == Step::kCreate);
  for (std::size_t index = 6; index < 11; ++index) {
    check(fixture.trace[index] == Step::kFloatRead);
  }
  finish();
}

void test_state_setup_acquire_arguments() {
  Fixture fixture{};
  initialize(fixture);

  skin_painter_state_setup_00506590(&fixture.state, 0u);

  check(fixture.acquire_calls == 3);
  for (std::size_t slot = 0; slot < 3; ++slot) {
    check(fixture.acquire_keys[slot][0] == kAcquireKey0);
    check(fixture.acquire_keys[slot][1] == kAcquireKey1);
    check(fixture.acquire_keys[slot][2] == 0u);
    check(fixture.acquire_keys[slot][3] == 0u);
    check(fixture.acquire_keys[slot][4] == 0u);
    check(fixture.acquire_keys[slot][5] == 0u);
  }
  check(fixture.create_calls == 3);
  check(fixture.state.texture_painter_010 != nullptr);
  check(fixture.state.texture_painter_014 != nullptr);
  check(fixture.state.texture_painter_018 != nullptr);
  finish();
}

void test_state_setup_null_factory_masks() {
  for (std::uint32_t mask = 0; mask < 8u; ++mask) {
    Fixture fixture{};
    initialize(fixture);
    fixture.null_factory_mask = mask;
    set_scale_values(fixture);
    std::size_t null_slots = 0;
    for (std::uint32_t bit = 0; bit < 3u; ++bit) {
      if (((mask >> bit) & 1u) != 0u) {
        null_slots += 1;
      }
    }

    skin_painter_state_setup_00506590(&fixture.state, 0x11223344u);

    check(fixture.acquire_calls == 3);
    check(fixture.create_calls == 3u - null_slots);
    check((fixture.state.texture_painter_010 == nullptr) ==
          (((mask >> 0u) & 1u) != 0u));
    check((fixture.state.texture_painter_014 == nullptr) ==
          (((mask >> 1u) & 1u) != 0u));
    check((fixture.state.texture_painter_018 == nullptr) ==
          (((mask >> 2u) & 1u) != 0u));
    check(fixture.state.source_01c == 0x11223344u);
    check(fixture.state.scale_020 == 0.5F);
    check(fixture.state.scale_024 == 1.0F);
    check(fixture.state.scale_028 == 20.0F);
    check(fixture.state.scale_02c == 1.0F);
    check(fixture.state.scale_030 == 1.0F);
    check(fixture.state.flag_00c == 0u);
    finish();
  }
}

void test_state_setup_float_addresses() {
  Fixture fixture{};
  initialize(fixture);
  set_scale_values(fixture);

  skin_painter_state_setup_00506590(&fixture.state, 0u);

  check(fixture.float_calls == 5);
  check(fixture.float_address[0] == kScaleSlot020);
  check(fixture.float_address[1] == kScaleSlot024);
  check(fixture.float_address[2] == kScaleSlot028);
  check(fixture.float_address[3] == kScaleSlot02c);
  check(fixture.float_address[4] == kScaleSlot030);
  check(fixture.state.scale_020 == 0.5F);
  check(fixture.state.scale_024 == 1.0F);
  check(fixture.state.scale_028 == 20.0F);
  check(fixture.state.scale_02c == 1.0F);
  check(fixture.state.scale_030 == 1.0F);
  finish();
}

void test_state_setup_repeated_call_replaces_slots() {
  Fixture fixture{};
  initialize(fixture);

  skin_painter_state_setup_00506590(&fixture.state, 1u);
  const OpaqueTexturePainter* first = fixture.state.texture_painter_010;
  const OpaqueTexturePainter* second = fixture.state.texture_painter_014;
  const OpaqueTexturePainter* third = fixture.state.texture_painter_018;

  skin_painter_state_setup_00506590(&fixture.state, 2u);

  check(fixture.acquire_calls == 6);
  check(fixture.create_calls == 6);
  check(fixture.state.texture_painter_010 != first);
  check(fixture.state.texture_painter_014 != second);
  check(fixture.state.texture_painter_018 != third);
  check(fixture.state.source_01c == 2u);
  finish();
}

void test_job_run_missing_painter() {
  Fixture fixture{};
  initialize(fixture);
  fixture.paint_system.painter_00c = nullptr;
  const OpaquePainterJob before = fixture.job;

  skin_painter_job_run_00517160(&fixture.job, 1u, 2u, 3u, 4u);

  check(fixture.job.completed_00c == 1u);
  check(fixture.step_calls == 0);
  check(fixture.query_calls == 0);
  check(fixture.submit_calls == 0);
  check(fixture.reset_calls == 0);
  check(fixture.trace_count == 1);
  check(fixture.trace[0] == Step::kPaintSystem);
  check(std::memcmp(&fixture.job.pass_014, &before.pass_014,
                    sizeof(OpaquePainterJob) - 0x14u) == 0);
  finish();
}

void test_job_run_missing_texture() {
  Fixture fixture{};
  initialize(fixture);
  fixture.skin_painter.texture_010 = nullptr;

  skin_painter_job_run_00517160(&fixture.job, 0u, 0u, 0u, 0u);

  check(fixture.job.completed_00c == 1u);
  check(fixture.step_calls == 0);
  check(fixture.query_calls == 0);
  check(fixture.submit_calls == 0);
  check(fixture.trace_count == 1);
  check(fixture.trace[0] == Step::kPaintSystem);
  finish();
}

void test_job_run_probe_low_single_slot() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = false;

  skin_painter_job_run_00517160(&fixture.job, 0u, 0u, 0u, 0u);

  check(fixture.query_calls == 1);
  check(fixture.step_calls == 1);
  check(fixture.job.completed_00c == 0u);
  check(fixture.reset_calls == 1);
  check(fixture.submit_calls == 1);
  check(fixture.trace_count == 7);
  check(fixture.trace[0] == Step::kPaintSystem);
  check(fixture.trace[1] == Step::kProbe);
  check(fixture.trace[2] == Step::kQuery);
  check(fixture.trace[3] == Step::kStep);
  check(fixture.trace[4] == Step::kReset);
  check(fixture.trace[5] == Step::kManager);
  check(fixture.trace[6] == Step::kSubmit);
  finish();
}

void test_job_run_probe_high_four_slots() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = true;

  skin_painter_job_run_00517160(&fixture.job, 0u, 0u, 0u, 0u);

  check(fixture.query_calls == 1);
  check(fixture.step_calls == 4);
  check(fixture.job.completed_00c == 0u);
  check(fixture.reset_calls == 1);
  check(fixture.submit_calls == 1);
  finish();
}

void test_job_run_step_completes_early() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = true;
  fixture.step_results[1] = 1u;

  skin_painter_job_run_00517160(&fixture.job, 0u, 0u, 0u, 0u);

  check(fixture.step_calls == 2);
  check(fixture.job.completed_00c == 1u);
  check(fixture.reset_calls == 0);
  check(fixture.submit_calls == 0);
  finish();
}

void test_job_run_step_stores_raw_byte() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = true;
  fixture.step_results[0] = 0x05u;

  skin_painter_job_run_00517160(&fixture.job, 0u, 0u, 0u, 0u);

  check(fixture.step_calls == 1);
  check(fixture.job.completed_00c == 0x05u);
  check(fixture.submit_calls == 0);
  finish();
}

void test_job_run_preset_completed_flag() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = true;
  fixture.job.completed_00c = 1u;

  skin_painter_job_run_00517160(&fixture.job, 0u, 0u, 0u, 0u);

  check(fixture.step_calls == 0);
  check(fixture.query_calls == 1);
  check(fixture.submit_calls == 0);
  check(fixture.job.completed_00c == 1u);
  finish();
}

void test_job_run_submit_payload() {
  Fixture fixture{};
  initialize(fixture);

  skin_painter_job_run_00517160(&fixture.job, 0u, 0u, 0u, 0u);

  check(fixture.reset_seen_field_000 == 0u);
  check(fixture.reset_calls == 1);
  check(fixture.submit_calls == 1);
  check(fixture.submit_arg_0 == 0u);
  check(fixture.submit_arg_1 == fixture.reset_target);
  check(fixture.submit_job == &fixture.job);
  check(fixture.submit_state.field_000 == kSubmitMode);
  check(fixture.submit_state.field_004 == 0u);
  check(fixture.submit_state.field_008 == 1u);
  check(fixture.submit_state.field_00c == 0u);
  check(fixture.submit_state.field_010 == 0u);
  check(fixture.submit_state.field_014 == 0u);
  check(fixture.submit_state.field_018 == 0u);
  check(fixture.submit_state.field_01c == 0u);
  check(fixture.submit_state.field_020 == 0u);
  check(fixture.submit_state.field_024 == 0u);
  check(fixture.submit_state.field_028 == 0u);
  finish();
}

void test_brush_pass_probe_high_pass_zero_exhausted() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = true;
  fixture.job.pass_014 = 0;

  const TargetWord result = skin_painter_job_brush_pass_005182f0(&fixture.job);

  check(result == kBrushPassFalse);
  check(fixture.query_calls == 1);
  check(fixture.advance_calls == 12);
  check(fixture.job.pass_014 == 0);
  finish();
}

void test_brush_pass_probe_high_pass_zero_limit_is_inclusive() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = true;
  fixture.job.pass_014 = 0;
  fixture.advance_results[12] = 1u;

  const TargetWord result = skin_painter_job_brush_pass_005182f0(&fixture.job);

  check(result == kBrushPassFalse);
  check(fixture.advance_calls == 12);
  finish();
}

void test_brush_pass_probe_high_completes_with_constant() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = true;
  fixture.job.pass_014 = 0;
  fixture.advance_results[4] = 0x03u;

  const TargetWord result = skin_painter_job_brush_pass_005182f0(&fixture.job);

  check(result == kBrushPassTrue);
  check(fixture.advance_calls == 5);
  finish();
}

void test_brush_pass_probe_high_nonzero_pass_is_uncapped() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = true;
  fixture.job.pass_014 = 3;
  fixture.advance_results[19] = 1u;

  const TargetWord result = skin_painter_job_brush_pass_005182f0(&fixture.job);

  check(result == kBrushPassTrue);
  check(fixture.advance_calls == 20);
  check(fixture.job.pass_014 == 3);
  finish();
}

void test_brush_pass_probe_low_pass_matrix() {
  struct PassCase {
    TargetSignedWord pass;
    std::size_t expected_calls;
  };
  const PassCase cases[] = {
      {0, 2}, {1, 1}, {2, 2}, {3, 2}, {4, 1}, {5, 1}, {-1, 1},
  };

  for (const PassCase& item : cases) {
    Fixture fixture{};
    initialize(fixture);
    fixture.query_result = false;
    fixture.job.pass_014 = item.pass;

    const TargetWord result =
        skin_painter_job_brush_pass_005182f0(&fixture.job);

    check(result == kBrushPassFalse);
    check(fixture.advance_calls == item.expected_calls);
    check(fixture.query_calls == 1);
    check(fixture.job.pass_014 == item.pass);
    finish();
  }
}

void test_brush_pass_probe_low_early_return_is_constant() {
  struct PassCase {
    TargetSignedWord pass;
    std::size_t expected_calls;
  };
  const PassCase cases[] = {
      {0, 1},
      {2, 1},
      {3, 1},
  };

  for (const PassCase& item : cases) {
    Fixture fixture{};
    initialize(fixture);
    fixture.query_result = false;
    fixture.job.pass_014 = item.pass;
    fixture.advance_results[0] = 0x07u;

    const TargetWord result =
        skin_painter_job_brush_pass_005182f0(&fixture.job);

    check(result == kBrushPassTrue);
    check(fixture.advance_calls == item.expected_calls);
    finish();
  }
}

void test_brush_pass_probe_low_final_return_passes_raw_value() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = false;
  fixture.job.pass_014 = 4;
  fixture.advance_results[0] = 0x02u;

  const TargetWord result = skin_painter_job_brush_pass_005182f0(&fixture.job);

  check(result == 0x02u);
  check(fixture.advance_calls == 1);
  finish();
}

void test_brush_pass_probe_low_second_stage_completes() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = false;
  fixture.job.pass_014 = 2;
  fixture.advance_results[1] = 0x01u;

  const TargetWord result = skin_painter_job_brush_pass_005182f0(&fixture.job);

  check(result == kBrushPassTrue);
  check(fixture.advance_calls == 2);
  finish();
}

void test_brush_pass_dispatches_through_vtable_slot() {
  Fixture fixture{};
  initialize(fixture);
  fixture.query_result = false;
  fixture.job.pass_014 = 1;

  const TargetWord result = fixture.job_vtable.apply_brushes_01c(&fixture.job);

  check(result == kBrushPassFalse);
  check(fixture.advance_calls == 1);
  finish();
}

void run() {
  test_state_setup_populates_all_slots();
  test_state_setup_acquire_arguments();
  test_state_setup_null_factory_masks();
  test_state_setup_float_addresses();
  test_state_setup_repeated_call_replaces_slots();
  test_job_run_missing_painter();
  test_job_run_missing_texture();
  test_job_run_probe_low_single_slot();
  test_job_run_probe_high_four_slots();
  test_job_run_step_completes_early();
  test_job_run_step_stores_raw_byte();
  test_job_run_preset_completed_flag();
  test_job_run_submit_payload();
  test_brush_pass_probe_high_pass_zero_exhausted();
  test_brush_pass_probe_high_pass_zero_limit_is_inclusive();
  test_brush_pass_probe_high_completes_with_constant();
  test_brush_pass_probe_high_nonzero_pass_is_uncapped();
  test_brush_pass_probe_low_pass_matrix();
  test_brush_pass_probe_low_early_return_is_constant();
  test_brush_pass_probe_low_final_return_passes_raw_value();
  test_brush_pass_probe_low_second_stage_completes();
  test_brush_pass_dispatches_through_vtable_slot();
}

}

int main() {
  run();
  return failures == 0 ? 0 : 1;
}

#undef PKG_TEST_CDECL
#undef PKG_TEST_THISCALL
