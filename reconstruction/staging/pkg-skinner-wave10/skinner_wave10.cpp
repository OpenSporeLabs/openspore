#include "skinner_wave10.hpp"

#include <cstdint>

#if defined(_MSC_VER)
#define PKG_SKINNER_WAVE10_THISCALL __thiscall
#else
#define PKG_SKINNER_WAVE10_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_skinner_wave10 {

SkinnerWave10Ports g_skinner_wave10_ports{};

namespace {

OpaqueTexturePainter* acquire_texture_painter(TargetWord source) {
  OpaqueLayerFactory* factory =
      g_skinner_wave10_ports.acquire_layer_factory_00f473a0(
          kAcquireKey0, kAcquireKey1, 0u, 0u, 0u, 0u);
  if (factory == nullptr) {
    return nullptr;
  }
  return g_skinner_wave10_ports.create_texture_painter_005288f0(factory, source,
                                                                source);
}

}

extern "C" void PKG_SKINNER_WAVE10_THISCALL skin_painter_state_setup_00506590(
    OpaquePainterState* state, TargetWord source) {
  state->texture_painter_010 = acquire_texture_painter(source);
  state->texture_painter_014 = acquire_texture_painter(source);
  state->texture_painter_018 = acquire_texture_painter(source);
  state->source_01c = source;
  state->scale_020 = g_skinner_wave10_ports.read_fixed_float(kScaleSlot020);
  state->scale_024 = g_skinner_wave10_ports.read_fixed_float(kScaleSlot024);
  state->scale_028 = g_skinner_wave10_ports.read_fixed_float(kScaleSlot028);
  state->scale_02c = g_skinner_wave10_ports.read_fixed_float(kScaleSlot02c);
  state->scale_030 = g_skinner_wave10_ports.read_fixed_float(kScaleSlot030);
}

extern "C" void PKG_SKINNER_WAVE10_THISCALL skin_painter_job_run_00517160(
    OpaquePainterJob* job, TargetWord arg_1, TargetWord arg_2, TargetWord arg_3,
    TargetWord arg_4) {
  static_cast<void>(arg_1);
  static_cast<void>(arg_2);
  static_cast<void>(arg_3);
  static_cast<void>(arg_4);

  OpaquePaintSystem* paint_system =
      g_skinner_wave10_ports.get_paint_system_00401080();
  OpaqueSkinPainter* painter = paint_system->painter_00c;
  if (painter == nullptr || painter->texture_010 == nullptr) {
    job->completed_00c = 1u;
    return;
  }

  OpaqueGraphicsProbe* probe =
      g_skinner_wave10_ports.get_graphics_probe_0067dd00();
  const TargetWord slot_count =
      probe->vtable_000->query_044(probe) ? kSlotCountHigh : kSlotCountLow;

  for (TargetWord index = 0; job->completed_00c == 0u && index < slot_count;
       index += 1u) {
    job->completed_00c = job->vtable_000->job_step_014(job);
  }

  if (job->completed_00c != 0u) {
    return;
  }

  OpaqueSubmitState state{};
  static_cast<void>(g_skinner_wave10_ports.reset_submit_state_00517240(&state));
  state.field_000 = kSubmitMode;
  OpaqueLightingManager* manager =
      g_skinner_wave10_ports.get_lighting_manager_0067dd50();
  manager->vtable_000->submit_074(manager, kSubmitZero0, &state, job);
}

extern "C" TargetWord PKG_SKINNER_WAVE10_THISCALL
skin_painter_job_brush_pass_005182f0(OpaquePainterJob* job) {
  OpaqueGraphicsProbe* probe =
      g_skinner_wave10_ports.get_graphics_probe_0067dd00();
  if (probe->vtable_000->query_044(probe)) {
    TargetWord attempt = 0;
    for (;;) {
      if (attempt >= kPassAttemptLimit && job->pass_014 == 0) {
        return kBrushPassFalse;
      }
      if (g_skinner_wave10_ports.advance_painter_job_00517430(job) != 0u) {
        return kBrushPassTrue;
      }
      attempt += 1u;
    }
  }

  if (job->pass_014 == 0 &&
      g_skinner_wave10_ports.advance_painter_job_00517430(job) != 0u) {
    return kBrushPassTrue;
  }
  if (job->pass_014 == 2 &&
      g_skinner_wave10_ports.advance_painter_job_00517430(job) != 0u) {
    return kBrushPassTrue;
  }
  if (job->pass_014 == 3 &&
      g_skinner_wave10_ports.advance_painter_job_00517430(job) != 0u) {
    return kBrushPassTrue;
  }
  return g_skinner_wave10_ports.advance_painter_job_00517430(job);
}

}

#undef PKG_SKINNER_WAVE10_THISCALL
