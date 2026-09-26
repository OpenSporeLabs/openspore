#include "frame_runtime_wave8.hpp"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>

#if defined(_MSC_VER)
#define FRAME_RUNTIME_CDECL __cdecl
#define FRAME_RUNTIME_STDCALL __stdcall
#define FRAME_RUNTIME_THISCALL __thiscall
#else
#define FRAME_RUNTIME_CDECL __attribute__((cdecl))
#define FRAME_RUNTIME_STDCALL __attribute__((stdcall))
#define FRAME_RUNTIME_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_frame_runtime_wave8 {
namespace {

OpaqueWord raw_dword(float value) {
  OpaqueWord raw = 0;
  std::memcpy(&raw, &value, sizeof(raw));
  return raw;
}

std::int32_t scale_to_integer(float word) {
  const float scaled = word * 1000.0F;
  if (std::isnan(scaled) || scaled >= 0x1p31F || scaled < -0x1p31F) {
    return std::numeric_limits<std::int32_t>::min();
  }
  const long rounded = std::lrint(scaled);
  if (rounded < std::numeric_limits<std::int32_t>::min() ||
      rounded > std::numeric_limits<std::int32_t>::max()) {
    return std::numeric_limits<std::int32_t>::min();
  }
  return static_cast<std::int32_t>(rounded);
}

}

FrameRuntimePorts* g_frame_runtime_wave8_ports = nullptr;

extern "C" void FRAME_RUNTIME_CDECL
cell_update_body_00e806b0(float first_stack_word, float second_stack_word) {
  FrameRuntimePorts& frame = *g_frame_runtime_wave8_ports;
  OpaqueCellRuntimePorts& ports = frame.cell;
  OpaqueCellGame& game = *frame.cell_game;
  ports.prepare_00e84bf0();

  if (game.state_51e0 == 0) {
    if (game.gate_515c == 0) {
      if (first_stack_word != 0.0F) {
        ++game.counter_5160;
        const std::int32_t first_word = scale_to_integer(first_stack_word);
        const std::int32_t second_word = scale_to_integer(second_stack_word);
        ports.set_words_00e82de0(second_word, first_word);

        OpaqueSpaceTrading* space = ports.get_space_trading_00b3d4d0();
        space->vtable_04->update_38(
            reinterpret_cast<OpaqueSpaceTrading*>(&space->vtable_04),
            second_word, first_word);

        OpaqueCellService* cell = ports.get_cell_service_00b3d3f0();
        cell->vtable_04->update_38(
            reinterpret_cast<OpaqueCellService*>(&cell->vtable_04), second_word,
            first_word);

        OpaquePlayer* player = game.player_5190;
        player->word_74 += first_word;
        ports.move_player_00e5b790(second_stack_word);
        ports.update_word_00e7f3a0(second_stack_word);

        if (game.reload_51d8 == 1) {
          ports.dispatch_reload_00e7fd00(player->word_1c, player->word_20,
                                         player->word_24, player->word_28,
                                         game.source_410c, game.source_4110, 0);
          if (game.reload_51d9 == 1) {
            ports.update_return_00e7f550();
          }
          ports.update_word_00e7f3a0(second_stack_word);
        }

        ports.update_no_words_00e73f60();
        ports.update_word_00e53b00(second_stack_word);
        ports.update_word_flag_00e600a0(second_stack_word, 0);
        ports.update_word_00e6c9f0(second_stack_word);
        return;
      }
    }

    OpaqueSpaceTrading* space = ports.get_space_trading_00b3d4d0();
    const std::int32_t second_word = scale_to_integer(second_stack_word);
    space->vtable_04->update_38(
        reinterpret_cast<OpaqueSpaceTrading*>(&space->vtable_04), second_word,
        0);

    OpaqueCellService* cell = ports.get_cell_service_00b3d3f0();
    cell->vtable_04->update_38(
        reinterpret_cast<OpaqueCellService*>(&cell->vtable_04), second_word, 0);

    ports.build_frustum_006ffe00(reinterpret_cast<OpaqueFrustum*>(0x016b3cb8U),
                                 0x016b4378U);
    ports.update_word_flag_00e600a0(second_stack_word, 1);
    ports.update_word_00e6c9f0(second_stack_word);
    return;
  }

  if (first_stack_word == 0.0F) {
    return;
  }
  if (game.state_51e0 == 1) {
    if (ports.ready_00e82c70()) {
      OpaqueTextureManager* manager = ports.get_texture_manager_0067dd20();
      manager->vtable->tail_texture_40(manager);
    }
    return;
  }
  if (game.state_51e0 == 2) {
    if (ports.ready_00e82c70()) {
      OpaqueIdGenerator* generator = ports.get_id_generator_0067de20();
      generator->vtable->generate_20(generator, 0x014137f8U);
    }
  }
}

extern "C" void FRAME_RUNTIME_THISCALL timing_update_body_00b31cc0(
    OpaqueTimingOwner* receiver, OpaqueTimingContext* first_stack_word) {
  FrameRuntimePorts& ports = *g_frame_runtime_wave8_ports;
  OpaqueTimingContext* context = first_stack_word;
  const OpaqueWord* values =
      ports.timing_lookup_00838020(context, &context, 0, 1);
  ports.timing_begin_00bc30b0();

  const std::int32_t context_value =
      static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(context));
  if (context_value > 0) {
    const OpaqueWord item = values[0];
    OpaqueLayerBuffer layer{};
    OpaqueTimingVector* vector = receiver->service_04->vtable->layer_a4(
        receiver->service_04, &layer, item);
    float blend =
        vector->word_04 * 0.00069444446F + vector->word_00 * 0.041666668F;
    if (!(blend > 0.0F)) {
      blend = 0.0F;
    }
    if (blend > 1.0F) {
      blend = 1.0F;
    }

    OpaqueTimingRoot* root = ports.timing_root_00b3d300();
    OpaqueTimingRuntime* runtime = ports.timing_runtime_00b1fdb0(root);
    OpaqueTimingVector3 result{};
    if (runtime != nullptr) {
      result = *runtime->vtable_c0->vector_2c(
          reinterpret_cast<OpaqueTimingRuntimeVtable*>(&runtime->vtable_c0));
    } else {
      std::uint8_t initialized_storage[0x60]{};
      OpaqueTimingMatrix* initialized =
          reinterpret_cast<OpaqueTimingMatrix*>(initialized_storage);
      OpaqueTimingMatrix* init_receiver = reinterpret_cast<OpaqueTimingMatrix*>(
          reinterpret_cast<std::uintptr_t>(initialized) + 0x14);
      ports.timing_init_0041cb40(init_receiver, ports.timing_matrix_0167e8e0);
      OpaqueRenderer* renderer = ports.timing_renderer_0067dd10();
      OpaqueLayerResult* layer_result =
          renderer->vtable->layer_58(renderer, initialized);
      ports.timing_release_007c40f0(layer_result);
      OpaqueTimingMatrix read_after_mutate = *initialized;
      result.word_00 = raw_dword(read_after_mutate.word_04);
      result.word_04 = raw_dword(read_after_mutate.word_08);
      result.word_08 = raw_dword(read_after_mutate.word_0c);
    }

    if (!ports.timing_enabled_01021260()) {
      return;
    }
    OpaqueTimingConfig* config = ports.timing_begin_00bc30b0();
    const float scaled_word = blend * config->word_24;
    ports.timing_bc2f00(ports.timing_begin_00bc30b0(), scaled_word, &result);
  }

  const OpaqueWord* speed = ports.timing_speed_lookup_00838330("speed", 1);
  if (speed != nullptr) {
    float speed_word =
        receiver->service_04->vtable->speed_98(receiver->service_04, *speed);
    if (!(speed_word > 1.5258789e-05F)) {
      speed_word = 1.5258789e-05F;
    }
    OpaqueTimingConfig* speed_config = ports.timing_begin_00bc30b0();
    ports.timing_bc28c0(speed_config, speed_word);
  }
}

}

#undef FRAME_RUNTIME_CDECL
#undef FRAME_RUNTIME_STDCALL
#undef FRAME_RUNTIME_THISCALL
