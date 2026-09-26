#include "frame_runtime_wave7.hpp"

#include <cmath>
#include <cstdint>
#include <limits>

#if defined(_MSC_VER)
#define FRAME_SOURCE_THISCALL __thiscall
#else
#define FRAME_SOURCE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_frame_runtime_wave7 {
namespace {

std::int32_t wrap_add(std::int32_t left, std::int32_t right) {
  return static_cast<std::int32_t>(static_cast<std::uint32_t>(left) +
                                   static_cast<std::uint32_t>(right));
}

std::int32_t wrap_sub(std::int32_t left, std::int32_t right) {
  return static_cast<std::int32_t>(static_cast<std::uint32_t>(left) -
                                   static_cast<std::uint32_t>(right));
}

std::int32_t truncate_to_i32(float value) {
  if (std::isnan(value) || value >= 0x1p31F || value < -0x1p31F) {
    return std::numeric_limits<std::int32_t>::min();
  }
  return static_cast<std::int32_t>(value);
}

std::int64_t round_x87_to_i64(float value) {
  if (std::isnan(value) || value >= 0x1p63F || value < -0x1p63F) {
    return std::numeric_limits<std::int64_t>::min();
  }
  return static_cast<std::int64_t>(std::llrint(value));
}

std::int32_t normalize_pacing_target(std::int32_t target, bool enabled) {
  if (!enabled || target >= 45) {
    return target;
  }
  if (target < 0) {
    return target == std::numeric_limits<std::int32_t>::min() ? target
                                                              : -target;
  }
  return 45;
}

std::int64_t elapsed_ticks(std::uint64_t now, std::uint64_t baseline) {
  return static_cast<std::int64_t>(now - baseline);
}

std::int32_t pace_frame(OpaqueSporeApp* owner, OpaqueAppSystem* app_system,
                        std::int32_t target, std::int32_t delta,
                        FrameRuntimePorts& ports) {
  if (target <= 0) {
    return delta;
  }

  OpaquePacingService* pacing = ports.acquire_pacing_0068f4d0();
  if (pacing->vtable->available_34(pacing, -1)) {
    if (wrap_sub(target, delta) < 3) {
      target = wrap_add(delta, 3);
    }
    if (delta < wrap_sub(target, 1)) {
      OpaqueWord request =
          static_cast<OpaqueWord>(wrap_sub(wrap_sub(target, delta), 1));
      app_system->vtable->request_pacing_84(app_system, request);
      delta = ports.measure_elapsed_00f475b0(owner);
    }
  }

  std::int32_t remaining = wrap_sub(target, delta);
  if (remaining > 0) {
    std::uint32_t wait_word = static_cast<std::uint32_t>(remaining);
    ports.wait_milliseconds_00921df0(&wait_word);
    delta = ports.measure_elapsed_00f475b0(owner);
  }
  return delta;
}

void publish_baseline(OpaqueSporeApp* owner, std::int32_t delta) {
  float scaled = static_cast<float>(delta) * owner->baseline_scale_1c;
  std::int64_t increment = round_x87_to_i64(scaled);
  owner->baseline_10 += static_cast<std::uint64_t>(increment);
}

}

FrameRuntimePorts* g_frame_runtime_ports = nullptr;

extern "C" void FRAME_SOURCE_THISCALL cell_mode_update_00e80980(
    OpaqueCellMode* receiver, float first_word, float second_word) {
  static_cast<void>(receiver);
  g_frame_runtime_ports->cell_orchestrator_00e806b0(first_word, second_word);
}

extern "C" void FRAME_SOURCE_THISCALL
app_frame_update_00f47930(OpaqueSporeApp* owner) {
  if (owner->active_0c == 0) {
    return;
  }

  FrameRuntimePorts& ports = *g_frame_runtime_ports;
  std::uint64_t now = 0;
  ports.query_performance_counter(&now);
  float elapsed_ms =
      static_cast<float>(elapsed_ticks(now, owner->baseline_10)) *
      owner->tick_to_ms_18;
  std::int32_t delta = truncate_to_i32(elapsed_ms);

  OpaqueAppSystem* app_system = owner->app_system_20;
  std::int32_t pacing_target = ports.read_pacing_target();
  if (app_system->vtable->pacing_enabled_44(app_system)) {
    pacing_target = normalize_pacing_target(pacing_target, true);
  }
  delta = pace_frame(owner, app_system, pacing_target, delta, ports);

  publish_baseline(owner, delta);

  OpaqueAppSystem* service = ports.get_app_system_0067dcc0();
  service->vtable->service_38(service);
  if (owner->direct_service_28 != nullptr) {
    ports.direct_service_00812d30(owner->direct_service_28, delta);
  }
  if (owner->first_stage_34 != nullptr) {
    owner->first_stage_34->vtable->update_20(owner->first_stage_34, delta);
  }
  if (owner->middle_stage_38 != nullptr) {
    owner->middle_stage_38->vtable->update_1c(owner->middle_stage_38, delta);
  }
  if (owner->fourth_stage_3c != nullptr) {
    owner->fourth_stage_3c->vtable->update_28(owner->fourth_stage_3c, delta);
  }
  if (owner->last_stage_30 != nullptr) {
    owner->last_stage_30->vtable->update_0c(owner->last_stage_30, delta);
  }
  owner->app_system_20->vtable->update_78(owner->app_system_20, delta);
  if (owner->float_stage_2c != nullptr) {
    owner->float_stage_2c->vtable->update_18(
        owner->float_stage_2c, static_cast<float>(delta) * 0.001F);
  }
  owner->app_system_20->vtable->post_7c(owner->app_system_20);
}

}

#undef FRAME_SOURCE_THISCALL
