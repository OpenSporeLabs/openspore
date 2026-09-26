#include "game_input_wave8.hpp"

#if defined(_MSC_VER)
#define PKG_GAME_INPUT_WAVE8_THISCALL __thiscall
#else
#define PKG_GAME_INPUT_WAVE8_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_game_input_wave8 {

OpaqueCellGame* g_cell_game_016b3c04 = nullptr;
OpaqueCellInputState* g_cell_input_state_016b3c0c = nullptr;
TargetWord g_object_sentinel_016b3c14 = 0;
NativePorts g_game_input_wave8_ports{};

extern "C" bool PKG_GAME_INPUT_WAVE8_THISCALL
cell_mode_strategy_on_mouse_down_00e6c860(OpaqueCellModeStrategy* strategy,
                                          MouseButton mouse_button,
                                          float mouse_x, float mouse_y,
                                          MouseState mouse_state) {
  static_cast<void>(strategy);
  auto* const ports = &g_game_input_wave8_ports;
  OpaqueMouseDownLocals locals{};

  ports->mouse_down_00697ab0(&g_cell_input_state_016b3c0c->input, mouse_button,
                             mouse_x, mouse_y, mouse_state);

  if ((mouse_state_low_byte(mouse_state) & kMouseStateDownRaycastMask) != 0u) {
    OpaqueLayer* const layer =
        ports->renderer_layer_slot_58(ports->renderer_get_0067dd10());
    ports->layer_unproject_007c4730(layer, mouse_x, mouse_y,
                                    &locals.raycast_in_0, &locals.raycast_in_1);
    const std::int32_t hits = ports->raycast_00e87200(
        g_cell_game_016b3c04->scene_object_40fc, &locals.raycast_in_0,
        &locals.raycast_in_1, locals.out_buffer, kRaycastCapacity,
        float_from_bits(kRaycastMaxDistanceBits));
    if (hits != 0) {
      TargetWord first_hit = 0;
      std::memcpy(&first_hit, &locals.out_buffer[0], sizeof(first_hit));
      g_cell_input_state_016b3c0c->pick_result_00c0 = first_hit;
    }
    return true;
  }

  OpaqueCellObject* const picked = ports->pick_object_00e6c780();
  if (mouse_button == kMouseButtonLeft && picked != nullptr) {
    ports->on_object_clicked_00e643e0(picked);
  }

  ports->handle_reset_00743b50(&locals.handle);
  OpaqueCellSubObject* const subject =
      ports->resolve_sub_object_00e4ce40(&locals.handle);
  const std::int32_t mode = subject->mode_00d4;
  ports->handle_release_00e82130(&locals.handle);

  const bool has_pick = picked != nullptr;
  if (mode == kSubObjectModeOne) {
    if (has_pick && (mouse_button == kMouseButtonLeft ||
                     mouse_button == kMouseButtonRight)) {
      g_cell_input_state_016b3c0c->selected_object_00c4 =
          reinterpret_cast<TargetWord>(picked);
      return true;
    }
  } else if (mode == kSubObjectModeTwo) {
    if (has_pick && mouse_button == kMouseButtonLeft) {
      g_cell_input_state_016b3c0c->selected_object_00c4 =
          reinterpret_cast<TargetWord>(picked);
      return true;
    }
  }

  g_cell_input_state_016b3c0c->selected_object_00c4 = 0;
  return false;
}

extern "C" bool PKG_GAME_INPUT_WAVE8_THISCALL
cell_mode_strategy_on_mouse_up_00e5c0f0(OpaqueCellModeStrategy* strategy,
                                        MouseButton mouse_button, float mouse_x,
                                        float mouse_y, MouseState mouse_state) {
  static_cast<void>(strategy);
  auto* const ports = &g_game_input_wave8_ports;
  OpaqueMouseUpLocals locals{};

  ports->mouse_up_00697af0(&g_cell_input_state_016b3c0c->input, mouse_button,
                           mouse_x, mouse_y, mouse_state);

  OpaqueLayer* const layer =
      ports->renderer_layer_slot_58(ports->renderer_get_0067dd10());
  ports->layer_unproject_int_007c4900(layer, &locals.raycast_in_0,
                                      &locals.raycast_in_1);
  const std::int32_t hits = ports->raycast_00e87200(
      g_cell_game_016b3c04->scene_object_40fc, &locals.raycast_in_0,
      &locals.raycast_in_1, g_cell_input_state_016b3c0c->unproject_out_0100,
      kRaycastCapacity, float_from_bits(kRaycastMaxDistanceBits));

  g_cell_input_state_016b3c0c->health_0900 = hits;
  g_cell_input_state_016b3c0c->health_phase_0904 = 0.0F;
  return true;
}

extern "C" bool PKG_GAME_INPUT_WAVE8_THISCALL
cell_mode_strategy_on_mouse_wheel_00e7d660(OpaqueCellModeStrategy* strategy,
                                           WheelDelta wheel_delta,
                                           float mouse_x, float mouse_y,
                                           MouseState mouse_state) {
  static_cast<void>(strategy);
  auto* const ports = &g_game_input_wave8_ports;
  const std::uint8_t state = mouse_state_low_byte(mouse_state);

  ports->mouse_wheel_00697b40(&g_cell_input_state_016b3c0c->input, wheel_delta,
                              mouse_x, mouse_y, mouse_state);

  if ((state & kMouseStateWheelZoomMask) != 0u &&
      !ports->wheel_gate_00b1fbf0()) {
    ports->zoom_out_00e50f60(wheel_step_quotient(wheel_delta));
    return true;
  }

  if ((state & kMouseStateWheelHealthMask) != 0u &&
      !ports->wheel_gate_00b1fbf0()) {
    const TargetWord found = ports->local_object_lookup_00b721d0(
        &g_cell_game_016b3c04->object_index_01c,
        g_cell_game_016b3c04->local_object_411c);
    if (found == 0) {
      return false;
    }
    if (wheel_delta < 0) {
      call_health_tick_raw_00e7d070(ports->health_tick_00e7d070,
                                    kHealthTickDeadReceiver, kHealthTickMode,
                                    0.0F, g_object_sentinel_016b3c14, nullptr);
    }
    return true;
  }

  ports->zoom_in_00e51060(wheel_delta);
  return true;
}

}
