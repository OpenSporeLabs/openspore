#include "game_mode_wave8.hpp"

#if defined(_MSC_VER)
#define PKG_GAME_MODE_WAVE8_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_GAME_MODE_WAVE8_THISCALL __attribute__((thiscall))
#else
#error "PKG-GAME-MODE-WAVE8 requires an MSVC or GCC thiscall convention"
#endif

#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::pkg_game_mode_wave8 {

TransitionPorts g_game_mode_wave8_ports{};
SimulatorGlobals g_game_mode_wave8_globals{};

namespace {

const char* text_address(std::uintptr_t value) {
  return reinterpret_cast<const char*>(value);
}

OpaquePairService* pair_service_at(void* raw, std::size_t object_offset) {
  return reinterpret_cast<OpaquePairService*>(static_cast<std::uint8_t*>(raw) +
                                              object_offset);
}

void call_pair_slot(void* raw, std::size_t object_offset,
                    std::size_t vtable_offset, ModeWord first,
                    ModeWord second) {
  OpaquePairService* service = pair_service_at(raw, object_offset);
  if (vtable_offset == 0x04) {
    service->vtable->slot_04(reinterpret_cast<OpaqueService*>(service), first,
                             second);
  } else if (vtable_offset == 0x08) {
    service->vtable->slot_08(reinterpret_cast<OpaqueService*>(service), first,
                             second);
  } else if (vtable_offset == 0x0c) {
    service->vtable->slot_0c(reinterpret_cast<OpaqueService*>(service), first,
                             second);
  } else if (vtable_offset == 0x14) {
    service->vtable->slot_14(reinterpret_cast<OpaqueService*>(service), first,
                             second);
  } else {
    service->vtable->slot_18(reinterpret_cast<OpaqueService*>(service), first,
                             second);
  }
}

void call_participants(OpaqueModeTransition* transition, ModeWord first,
                       ModeWord second, std::size_t vtable_offset) {
  std::uint32_t index = 0U;
  while (true) {
    const std::ptrdiff_t span =
        transition->participants_end - transition->participants_begin;
    const std::int32_t count = static_cast<std::int32_t>(span >> 2);
    if (count <= 0 || index >= static_cast<std::uint32_t>(count)) {
      break;
    }
    auto** entries =
        reinterpret_cast<OpaqueParticipant**>(transition->participants_begin);
    OpaqueParticipant* participant = entries[index];
    if (vtable_offset == 0x14) {
      participant->vtable->slot_14(participant, first, second);
    } else {
      participant->vtable->slot_18(participant, first, second);
    }
    ++index;
  }
}

bool should_reset_telemetry(ModeWord first, ModeWord second) {
  if (second == kModeGalaxy) {
    return first == kModeEditorTarget || first == kModeCell ||
           first == kModeCreature || first == kModeTribe ||
           first == kModeCivilisation || first == kModeSpace;
  }
  if (second == kModeCreature || second == kModeTribe ||
      second == kModeCivilisation || second == kModeSpace) {
    return first == kModeCell || first == kModeCreature ||
           first == kModeTribe || first == kModeCivilisation;
  }
  return false;
}

TextRange mode_name_range(std::uint8_t selector) {
  if (selector == 0U) {
    return {text_address(0x0145d940U), text_address(0x0145d948U)};
  }
  if (selector == 1U) {
    return {text_address(0x0145d930U), text_address(0x0145d93cU)};
  }
  if (selector == 2U) {
    return {text_address(0x0145d924U), text_address(0x0145d92dU)};
  }
  if (selector == 3U) {
    return {text_address(0x0145d910U), text_address(0x0145d920U)};
  }
  if (selector == 4U) {
    return {text_address(0x0145d904U), text_address(0x0145d90dU)};
  }
  if (selector == 5U) {
    return {text_address(0x0146289cU), text_address(0x014628a8U)};
  }
  return {nullptr, nullptr};
}

void append_mode_name(const TransitionPorts& ports, TextVector* labels,
                      std::uint8_t selector) {
  if (selector == 6U) {
    return;
  }
  const TextRange range = mode_name_range(selector);
  ports.append_text_00454cb0(labels, range.begin, range.end);
}

void append_mode_index(const TransitionPorts& ports, TextVector* labels,
                       ModeWord mode) {
  static constexpr std::uint8_t indices[17] = {
      0U, 1U, 2U, 6U, 3U, 4U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 5U,
  };
  const ModeWord index = mode + 0xfe9ab400U;
  if (index > 0x10U) {
    return;
  }
  append_mode_name(ports, labels, indices[index]);
}

void release_text(const TransitionPorts& ports, TextVector* vector) {
  const std::uintptr_t begin = reinterpret_cast<std::uintptr_t>(vector->begin);
  const std::uintptr_t capacity =
      reinterpret_cast<std::uintptr_t>(vector->capacity);
  if (capacity > begin && capacity - begin > 1U && begin != 0U) {
    ports.free_text_00f47380(vector->begin);
  }
}

void release_text_even_masked(const TransitionPorts& ports,
                              TextVector* vector) {
  const std::uintptr_t begin = reinterpret_cast<std::uintptr_t>(vector->begin);
  const std::uintptr_t capacity =
      reinterpret_cast<std::uintptr_t>(vector->capacity);
  const std::uintptr_t masked_span = (capacity - begin) & ~std::uintptr_t{1};
  if (masked_span > 2U && begin != 0U) {
    ports.free_text_00f47380(vector->begin);
  }
}

}

extern "C" void PKG_GAME_MODE_WAVE8_THISCALL
simulator_strategy_transition_00b5f040(OpaqueModeTransition* transition,
                                       ModeWord first, ModeWord second) {
  TransitionPorts& ports = g_game_mode_wave8_ports;
  OpaqueSimulationState* state = ports.state_root_00b3d320();
  state->first_mode = first;
  state->shared_state = second;
  state->transition_flag_28 = 0U;
  g_game_mode_wave8_globals.flag_01686af0 = 0U;
  if (first == kModeGalaxy) {
    transition->transition_flag_0c =
        static_cast<std::uint8_t>(second != kModeEditorTarget);
  }
  void* state_followup = ports.state_followup_00b3d380();
  ports.state_followup_call_00b31a90(state_followup);
  if (second == kModeGalaxy || second == kNoMode || second == kModeEditor) {
    ports.clear_00b2fbe0();
  }
  ports.strategy_00b5e3f0(transition, second);
  void* context = ports.context_get_00805070();
  if (!ports.context_query_00810760(context, 0x05b598f6U)) {
    ports.context_set_00810660(context, 0x05b598f6U, 1U);
  }
  ports.pair_dispatch_00b33970(first, second);
  OpaqueReturnService* return_service = ports.return_service_get_0067caa0();
  void* returned = return_service->vtable->slot_04(
      reinterpret_cast<OpaqueService*>(return_service));
  void* context_value =
      returned == nullptr ? nullptr : static_cast<std::uint8_t*>(returned) - 4U;
  ports.context_reset_008153e0(context_value);
  ports.context_finalize_00812d60(context_value, 0U);
  call_participants(transition, first, second, 0x14U);
  call_pair_slot(ports.pair_service_get_00d38840(), 0x08U, 0x14U, first,
                 second);
  call_pair_slot(ports.pair_service_get_00cd40b0(), 0x0cU, 0x14U, first,
                 second);
  call_pair_slot(ports.pair_service_get_00cf74c0(), 0x04U, 0x14U, first,
                 second);
  call_pair_slot(ports.pair_service_get_00fd9c60(), 0x08U, 0x14U, first,
                 second);
  call_pair_slot(ports.pair_service_get_00d1bf00(), 0x08U, 0x14U, first,
                 second);
  transition->vtable->slot_44(transition);
  OpaqueService* tail = ports.tail_service_get_0067cab0();
  static_cast<void>(ports.tail_finalize_008017f0(tail, 0U));
}

extern "C" void PKG_GAME_MODE_WAVE8_THISCALL
simulator_strategy_transition_00b5dbb0(OpaqueModeTransition* transition,
                                       ModeWord first, ModeWord second) {
  TransitionPorts& ports = g_game_mode_wave8_ports;
  OpaqueService48* service = ports.service_get_0067ddd0();
  service->vtable->slot_48(reinterpret_cast<OpaqueService*>(service));
  OpaqueAppSystem* app_system = ports.app_system_get_0067dcc0();
  app_system->vtable->slot_14(app_system, 0x685f4afU, 0U, 0U);
  if (should_reset_telemetry(first, second)) {
    OpaqueService* telemetry = ports.telemetry_service_get_0067de90();
    ports.telemetry_reset_007ebce0(telemetry, kNoMode);
  }
  OpaqueService* tail = ports.tail_service_get_0067cab0();
  static_cast<void>(ports.tail_configure_00801bb0(tail, 0x1002U));
  static_cast<void>(ports.tail_finalize_008017f0(tail, 0U));
  call_pair_slot(ports.pair_service_get_00d38840(), 0x08U, 0x18U, first,
                 second);
  call_pair_slot(ports.pair_service_get_00cd40b0(), 0x0cU, 0x18U, first,
                 second);
  call_pair_slot(ports.pair_service_get_00cf74c0(), 0x04U, 0x18U, first,
                 second);
  call_pair_slot(ports.pair_service_get_00fd9c60(), 0x08U, 0x18U, first,
                 second);
  call_pair_slot(ports.pair_service_get_00d1bf00(), 0x08U, 0x18U, first,
                 second);
  ports.pair_dispatch_00b335d0(first, second);
  call_participants(transition, first, second, 0x18U);
  TextVector labels{text_address(0x01667bacU), text_address(0x01667bacU),
                    text_address(0x01667badU)};
  if (first == kModeGalaxy || first == kModeEditorTarget) {
    append_mode_index(ports, &labels, second);
  }
  if (second == kModeGalaxy) {
    ports.append_text_00454cb0(&labels, text_address(0x0146288cU),
                               text_address(0x0146289bU));
    OpaqueSpeciesManager* species_manager =
        ports.species_manager_get_00401090();
    TextVector command{};
    ports.species_initialize_004df310(species_manager, &command);
  } else if (second == kModeEditorTarget) {
    OpaqueRenderer* renderer = ports.renderer_get_0067dd10();
    OpaqueRenderer* viewer = ports.renderer_set_viewer_slot_2c(renderer);
    if (viewer != nullptr) {
      TextVector text{text_address(0x01667bacU), text_address(0x01667bacU),
                      text_address(0x01667baeU)};
      if (ports.renderer_query_005805e0(viewer, &text)) {
        TextVector temp{};
        TextVector* result = ports.transform_text_0093c570(&temp, &text);
        if (result != &labels) {
          ports.append_text_00454cb0(&labels, result->begin, result->end);
        }
        release_text(ports, &temp);
        TextVector* editor_result = ports.build_text_0091ba90(
            &temp, &labels, text_address(0x013eb430U));
        if (editor_result != &labels) {
          ports.append_text_00454cb0(&labels, editor_result->begin,
                                     editor_result->end);
        }
        release_text(ports, &temp);
      }
      release_text_even_masked(ports, &text);
    }
  }
  transition->vtable->slot_58(transition);
  release_text(ports, &labels);
}

}

#undef PKG_GAME_MODE_WAVE8_THISCALL
