#include "skinner_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_SKINNER_SAFE_WAVE10_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_SKINNER_SAFE_WAVE10_THISCALL __attribute__((thiscall))
#else
#error "PKG-SKINNER-SAFE-WAVE10 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_skinner_safe_wave10 {

float g_float_01471064 = 0.5F;
float g_float_01485720 = 1.0F;
float g_float_013eecd8 = 20.0F;

namespace {

OpaqueTexturePainter *acquire_texture_painter(std::uint32_t source) {
  OpaqueLayerFactory *factory =
      unresolved_00f473a0(kAcquireTag, kAcquireName, kAcquireZero3,
                          kAcquireZero4, kAcquireZero5, kAcquireZero6);
  if (factory == nullptr) {
    return nullptr;
  }
  return unresolved_005288f0(factory, source, source);
}

std::uint8_t step_is_done(std::uint32_t step) {
  return static_cast<std::uint8_t>(step & kLowByteMask);
}

}

extern "C" void PKG_SKINNER_SAFE_WAVE10_THISCALL
skin_painter_state_setup_00506590(OpaqueSkinPainterState *state,
                                  std::uint32_t source) {
  state->texture_painter_010 = acquire_texture_painter(source);
  state->texture_painter_014 = acquire_texture_painter(source);
  state->texture_painter_018 = acquire_texture_painter(source);
  state->source_01c = source;
  state->scale_020 = g_float_01471064;
  state->scale_024 = g_float_01485720;
  state->scale_028 = g_float_013eecd8;
  state->scale_02c = g_float_01485720;
  state->scale_030 = g_float_01485720;
}

extern "C" std::uint32_t PKG_SKINNER_SAFE_WAVE10_THISCALL
skin_painter_job_brush_pass_005182f0(OpaquePainterJob *job) {
  OpaqueGraphicsProbe *probe = unresolved_0067dd00();
  const std::uint8_t query = probe->vtable_000->query_044(probe);
  if (query != 0u) {
    std::int32_t attempt = 0;
    for (;;) {
      if (attempt >= kAttemptLimit && job->pass_014 == kPassZero) {
        return kBrushPassFalse;
      }
      if (step_is_done(unresolved_00517430(job)) != 0u) {
        return kBrushPassTrue;
      }
      attempt += 1;
    }
  }

  if (job->pass_014 == kPassZero &&
      step_is_done(unresolved_00517430(job)) != 0u) {
    return kBrushPassTrue;
  }
  if (job->pass_014 == kPassTwo &&
      step_is_done(unresolved_00517430(job)) != 0u) {
    return kBrushPassTrue;
  }
  if (job->pass_014 == kPassThree &&
      step_is_done(unresolved_00517430(job)) != 0u) {
    return kBrushPassTrue;
  }
  return unresolved_00517430(job);
}

}

#undef PKG_SKINNER_SAFE_WAVE10_THISCALL
