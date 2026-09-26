#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <vector>

#include "frame_runtime_wave8.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_STDCALL __stdcall
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_STDCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_frame_runtime_wave8 {
namespace {

enum class Kind : std::uint8_t {
  cell_prepare,
  cell_set_words,
  cell_get_space,
  cell_space_update,
  cell_get_service,
  cell_service_update,
  cell_move,
  cell_update_second,
  cell_reload,
  cell_reload_secondary,
  cell_no_words,
  cell_followup,
  cell_flag,
  cell_final,
  cell_frustum,
  cell_ready,
  cell_get_texture,
  cell_tail_texture,
  cell_get_generator,
  cell_generator,
  timing_lookup,
  timing_begin,
  timing_layer,
  timing_root,
  timing_runtime,
  timing_vector,
  timing_init_fallback,
  timing_renderer,
  timing_renderer_layer,
  timing_release,
  timing_enabled,
  timing_finish_vector,
  timing_speed_lookup,
  timing_speed,
  timing_finish_speed,
};

struct Event {
  Kind kind = Kind::cell_prepare;
  const void *receiver = nullptr;
  const void *source = nullptr;
  OpaqueWord word = 0;
  OpaqueWord second_word = 0;
  std::uint8_t byte_word = 0;
  std::int32_t signed_word = 0;
  float first_scalar = 0.0F;
  float second_scalar = 0.0F;
};

struct Fixture {
  OpaqueCellGame game{};
  OpaquePlayer player{};
  OpaqueSpaceTradingVtable space_vtable{};
  OpaqueSpaceTrading space{};
  OpaqueCellServiceVtable cell_service_vtable{};
  OpaqueCellService cell_service{};
  OpaqueTextureManagerVtable texture_vtable{};
  OpaqueTextureManager texture{};
  OpaqueIdGeneratorVtable generator_vtable{};
  OpaqueIdGenerator generator{};
  OpaqueRendererVtable renderer_vtable{};
  OpaqueRenderer renderer{};
  OpaqueLayerResult layer_result{};
  OpaqueTimingOwner timing_owner{};
  OpaqueTimingContext timing_context{};
  OpaqueTimingServiceVtable timing_service_vtable{};
  OpaqueTimingService timing_service{};
  OpaqueTimingRoot timing_root{};
  OpaqueTimingRuntime timing_runtime{};
  OpaqueTimingRuntimeVtable timing_runtime_vtable{};
  OpaqueTimingConfig timing_config{};
  OpaqueTimingMatrix timing_matrix{};
  OpaqueTimingVector timing_layer_result{};
  OpaqueTimingVector3 timing_vector_result{};
  std::vector<OpaqueWord> timing_values{};
  std::vector<OpaqueWord> timing_speeds{};
  FrameRuntimePorts ports{};
  std::vector<Event> events{};
  bool ready = false;
  bool runtime_enabled = true;
  bool runtime_available = true;
  bool speed_available = true;
  float speed_value = 0.2F;
};

Fixture fixture;
std::size_t failure_count = 0;

bool same_float_bits(float left, float right) {
  return std::memcmp(&left, &right, sizeof(left)) == 0;
}

OpaqueWord raw_float(float value) {
  OpaqueWord raw = 0;
  std::memcpy(&raw, &value, sizeof(raw));
  return raw;
}

void check(bool condition, const char *message) {
  static_cast<void>(message);
  if (!condition) {
    std::fputs(message, stderr);
    std::fputc('\n', stderr);
    ++failure_count;
  }
}

Event &record(Kind kind) {
  fixture.events.push_back(Event{});
  Event &event = fixture.events.back();
  event.kind = kind;
  return event;
}

void cell_prepare() { record(Kind::cell_prepare); }

void cell_set_words(std::int32_t first_word, std::int32_t second_word) {
  Event &event = record(Kind::cell_set_words);
  event.signed_word = first_word;
  event.word = static_cast<OpaqueWord>(second_word);
}

OpaqueSpaceTrading *get_space() {
  record(Kind::cell_get_space);
  return &fixture.space;
}

void TEST_THISCALL space_update(OpaqueSpaceTrading *receiver,
                                std::int32_t first_word,
                                std::int32_t second_word) {
  Event &event = record(Kind::cell_space_update);
  event.receiver = receiver;
  event.signed_word = first_word;
  event.word = static_cast<OpaqueWord>(second_word);
}

OpaqueCellService *get_cell_service() {
  record(Kind::cell_get_service);
  return &fixture.cell_service;
}

void TEST_THISCALL cell_service_update(OpaqueCellService *receiver,
                                       std::int32_t first_word,
                                       std::int32_t second_word) {
  Event &event = record(Kind::cell_service_update);
  event.receiver = receiver;
  event.signed_word = first_word;
  event.word = static_cast<OpaqueWord>(second_word);
}

bool cell_ready() {
  record(Kind::cell_ready);
  return fixture.ready;
}

OpaqueTextureManager *get_texture() {
  record(Kind::cell_get_texture);
  return &fixture.texture;
}

void TEST_THISCALL tail_texture(OpaqueTextureManager *receiver) {
  Event &event = record(Kind::cell_tail_texture);
  event.receiver = receiver;
}

OpaqueIdGenerator *get_generator() {
  record(Kind::cell_get_generator);
  return &fixture.generator;
}

void TEST_THISCALL generate_id(OpaqueIdGenerator *receiver, OpaqueWord word) {
  Event &event = record(Kind::cell_generator);
  event.receiver = receiver;
  event.word = word;
}

void move_player(float word) {
  Event &event = record(Kind::cell_move);
  event.first_scalar = word;
}

void update_second(float word) {
  Event &event = record(Kind::cell_update_second);
  event.first_scalar = word;
}

void reload(OpaqueWord first_word, OpaqueWord second_word,
            OpaqueWord third_word, OpaqueWord fourth_word,
            std::uint8_t source_byte, OpaqueWord source_word,
            OpaqueWord trailing_word) {
  Event &event = record(Kind::cell_reload);
  event.signed_word = static_cast<std::int32_t>(first_word);
  event.second_word = second_word;
  event.byte_word = source_byte;
  event.first_scalar = static_cast<float>(third_word);
  event.second_scalar = static_cast<float>(fourth_word);
  event.word = trailing_word;
  static_cast<void>(source_word);
}

std::uint8_t reload_secondary() {
  record(Kind::cell_reload_secondary);
  return 1;
}

void no_words() { record(Kind::cell_no_words); }

void followup(float word) {
  Event &event = record(Kind::cell_followup);
  event.first_scalar = word;
}

void cell_flag(float word, std::uint8_t flag) {
  Event &event = record(Kind::cell_flag);
  event.first_scalar = word;
  event.word = flag;
}

void cell_final(float word) {
  Event &event = record(Kind::cell_final);
  event.first_scalar = word;
}

void TEST_THISCALL build_frustum(OpaqueFrustum *receiver, OpaqueWord word) {
  Event &event = record(Kind::cell_frustum);
  event.receiver = receiver;
  event.word = word;
}

const OpaqueWord *TEST_THISCALL timing_lookup(OpaqueTimingContext *context,
                                              OpaqueTimingContext **source,
                                              OpaqueWord selector,
                                              OpaqueWord mode) {
  Event &event = record(Kind::timing_lookup);
  event.receiver = context;
  event.source = source;
  event.word = selector;
  event.signed_word = static_cast<std::int32_t>(mode);
  return fixture.timing_values.data();
}

OpaqueTimingConfig *timing_begin() {
  record(Kind::timing_begin);
  return &fixture.timing_config;
}

OpaqueTimingVector *TEST_THISCALL timing_layer(OpaqueTimingService *service,
                                               OpaqueLayerBuffer *layer,
                                               OpaqueWord item) {
  Event &event = record(Kind::timing_layer);
  event.receiver = service;
  event.source = layer;
  event.word = item;
  return &fixture.timing_layer_result;
}

OpaqueTimingRoot *timing_root() {
  Event &event = record(Kind::timing_root);
  event.receiver = &fixture.timing_root;
  return &fixture.timing_root;
}

OpaqueTimingRuntime *TEST_THISCALL timing_runtime(OpaqueTimingRoot *root) {
  Event &event = record(Kind::timing_runtime);
  event.receiver = root;
  return fixture.runtime_available ? root->runtime_54 : nullptr;
}

OpaqueTimingVector3 *TEST_THISCALL
timing_vector(OpaqueTimingRuntimeVtable *receiver) {
  Event &event = record(Kind::timing_vector);
  event.receiver = receiver;
  return &fixture.timing_vector_result;
}

void TEST_THISCALL timing_init_fallback(OpaqueTimingMatrix *destination,
                                        const OpaqueTimingMatrix *source) {
  Event &event = record(Kind::timing_init_fallback);
  event.receiver = destination;
  event.source = source;
  *destination = *source;
}

OpaqueRenderer *timing_renderer() {
  record(Kind::timing_renderer);
  return &fixture.renderer;
}

OpaqueLayerResult *TEST_THISCALL renderer_layer(OpaqueRenderer *renderer,
                                                OpaqueTimingMatrix *matrix) {
  Event &event = record(Kind::timing_renderer_layer);
  event.receiver = renderer;
  event.source = matrix;
  matrix->word_04 = 2.5F;
  matrix->word_08 = 3.75F;
  matrix->word_0c = 4.5F;
  return &fixture.layer_result;
}

void TEST_THISCALL timing_release(OpaqueLayerResult *receiver) {
  Event &event = record(Kind::timing_release);
  event.receiver = receiver;
}

bool timing_enabled() {
  record(Kind::timing_enabled);
  return fixture.runtime_enabled;
}

void TEST_THISCALL finish_vector(OpaqueTimingConfig *receiver,
                                 float scaled_word,
                                 OpaqueTimingVector3 *source) {
  Event &event = record(Kind::timing_finish_vector);
  event.receiver = receiver;
  event.first_scalar = scaled_word;
  event.source = source;
  event.word = source->word_00;
  event.second_word = source->word_04;
  event.signed_word = static_cast<std::int32_t>(source->word_08);
}

const OpaqueWord *TEST_STDCALL speed_lookup(const char *name,
                                            OpaqueWord selector) {
  Event &event = record(Kind::timing_speed_lookup);
  event.source = name;
  event.word = selector;
  return fixture.speed_available ? fixture.timing_speeds.data() : nullptr;
}

float TEST_THISCALL speed_from_service(OpaqueTimingService *service,
                                       OpaqueWord word) {
  Event &event = record(Kind::timing_speed);
  event.receiver = service;
  event.word = word;
  return fixture.speed_value;
}

void TEST_THISCALL finish_speed(OpaqueTimingConfig *receiver,
                                float speed_word) {
  Event &event = record(Kind::timing_finish_speed);
  event.receiver = receiver;
  event.first_scalar = speed_word;
}

void initialize() {
  fixture = Fixture{};
  fixture.game.player_5190 = &fixture.player;
  fixture.game.source_410c = 0x7b;
  fixture.game.source_4110 = 0x12345678U;
  fixture.game.reload_51d8 = 1;
  fixture.game.reload_51d9 = 1;
  fixture.space_vtable.update_38 = &space_update;
  fixture.space.vtable_04 = &fixture.space_vtable;
  fixture.cell_service_vtable.update_38 = &cell_service_update;
  fixture.cell_service.vtable_04 = &fixture.cell_service_vtable;
  fixture.texture_vtable.tail_texture_40 = &tail_texture;
  fixture.texture.vtable = &fixture.texture_vtable;
  fixture.generator_vtable.generate_20 = &generate_id;
  fixture.generator.vtable = &fixture.generator_vtable;
  fixture.renderer_vtable.layer_58 = &renderer_layer;
  fixture.renderer.vtable = &fixture.renderer_vtable;
  fixture.timing_service_vtable.speed_98 = &speed_from_service;
  fixture.timing_service_vtable.layer_a4 = &timing_layer;
  fixture.timing_service.vtable = &fixture.timing_service_vtable;
  fixture.timing_owner.service_04 = &fixture.timing_service;
  fixture.timing_root.runtime_54 = &fixture.timing_runtime;
  fixture.timing_runtime.vtable_c0 = &fixture.timing_runtime_vtable;
  fixture.timing_runtime_vtable.vector_2c = &timing_vector;
  fixture.timing_values = {7U};
  fixture.timing_speeds = {11U};
  fixture.timing_config.word_24 = 2.0F;
  fixture.timing_matrix.word_00 = 9.0F;
  fixture.timing_matrix.word_04 = 8.0F;
  fixture.timing_matrix.word_08 = 7.0F;
  fixture.timing_layer_result.word_00 = 2.0F;
  fixture.timing_layer_result.word_04 = 3.0F;
  fixture.timing_vector_result.word_00 = 0xaaaaaaaaU;
  fixture.timing_vector_result.word_04 = 0xbbbbbbbbU;
  fixture.timing_vector_result.word_08 = 0xccccccccU;
  fixture.ports.cell_game = &fixture.game;
  fixture.ports.cell.prepare_00e84bf0 = &cell_prepare;
  fixture.ports.cell.set_words_00e82de0 = &cell_set_words;
  fixture.ports.cell.get_space_trading_00b3d4d0 = &get_space;
  fixture.ports.cell.get_cell_service_00b3d3f0 = &get_cell_service;
  fixture.ports.cell.ready_00e82c70 = &cell_ready;
  fixture.ports.cell.get_texture_manager_0067dd20 = &get_texture;
  fixture.ports.cell.get_id_generator_0067de20 = &get_generator;
  fixture.ports.cell.move_player_00e5b790 = &move_player;
  fixture.ports.cell.update_word_00e7f3a0 = &update_second;
  fixture.ports.cell.update_return_00e7f550 = &reload_secondary;
  fixture.ports.cell.dispatch_reload_00e7fd00 = &reload;
  fixture.ports.cell.update_no_words_00e73f60 = &no_words;
  fixture.ports.cell.update_word_00e53b00 = &followup;
  fixture.ports.cell.update_word_flag_00e600a0 = &cell_flag;
  fixture.ports.cell.update_word_00e6c9f0 = &cell_final;
  fixture.ports.cell.build_frustum_006ffe00 = &build_frustum;
  fixture.ports.timing_lookup_00838020 = &timing_lookup;
  fixture.ports.timing_begin_00bc30b0 = &timing_begin;
  fixture.ports.timing_root_00b3d300 = &timing_root;
  fixture.ports.timing_runtime_00b1fdb0 = &timing_runtime;
  fixture.ports.timing_renderer_0067dd10 = &timing_renderer;
  fixture.ports.timing_init_0041cb40 = &timing_init_fallback;
  fixture.ports.timing_release_007c40f0 = &timing_release;
  fixture.ports.timing_enabled_01021260 = &timing_enabled;
  fixture.ports.timing_bc2f00 = &finish_vector;
  fixture.ports.timing_speed_lookup_00838330 = &speed_lookup;
  fixture.ports.timing_bc28c0 = &finish_speed;
  fixture.ports.timing_matrix_0167e8e0 = &fixture.timing_matrix;
  g_frame_runtime_wave8_ports = &fixture.ports;
}

void expect_kinds(std::initializer_list<Kind> expected) {
  check(fixture.events.size() == expected.size(), "event count");
  if (fixture.events.size() != expected.size()) {
    return;
  }
  std::size_t index = 0;
  for (Kind kind : expected) {
    check(fixture.events[index].kind == kind, "event order");
    ++index;
  }
}

const Event &event(Kind kind) {
  for (const Event &entry : fixture.events) {
    if (entry.kind == kind) {
      return entry;
    }
  }
  static const Event missing{};
  return missing;
}

void test_cell_rounding_nearest_even() {
  initialize();
  cell_update_body_00e806b0(0.0005F, 0.0015F);
  check(event(Kind::cell_set_words).signed_word == 2,
        "nearest-even rounds 1.5 to 2");
  check(event(Kind::cell_set_words).word == 0U, "nearest-even rounds 0.5 to 0");
  check(same_float_bits(event(Kind::cell_move).first_scalar, 0.0015F),
        "player movement uses unrounded second word");
}

void test_cell_active_order() {
  initialize();
  cell_update_body_00e806b0(1.25F, -0.5F);
  expect_kinds({Kind::cell_prepare, Kind::cell_set_words, Kind::cell_get_space,
                Kind::cell_space_update, Kind::cell_get_service,
                Kind::cell_service_update, Kind::cell_move,
                Kind::cell_update_second, Kind::cell_reload,
                Kind::cell_reload_secondary, Kind::cell_update_second,
                Kind::cell_no_words, Kind::cell_followup, Kind::cell_flag,
                Kind::cell_final});
  check(fixture.game.counter_5160 == 1, "cell counter write");
  check(fixture.player.word_74 == 1250, "cell player state write");
  check(event(Kind::cell_set_words).signed_word == -500,
        "cell first callback word is second stack word");
  check(event(Kind::cell_set_words).word == 1250U,
        "cell second callback word is first stack word");
  check(event(Kind::cell_space_update).receiver == &fixture.space.vtable_04,
        "space object+4 receiver");
  check(event(Kind::cell_service_update).receiver ==
            &fixture.cell_service.vtable_04,
        "cell service object+4 receiver");
  check(same_float_bits(event(Kind::cell_move).first_scalar, -0.5F),
        "e5b790 uses second word");
  check(same_float_bits(event(Kind::cell_update_second).first_scalar, -0.5F),
        "e7f3a0 uses second word");
  check(same_float_bits(event(Kind::cell_followup).first_scalar, -0.5F),
        "e53b00 uses second word");
  check(same_float_bits(event(Kind::cell_flag).first_scalar, -0.5F),
        "e600a0 uses second word and zero");
  check(event(Kind::cell_flag).word == 0U, "active e600a0 uses zero flag");
  check(same_float_bits(event(Kind::cell_final).first_scalar, -0.5F),
        "active e6c9f0 uses second word");
}

void test_cell_frame_gate_fallback() {
  initialize();
  fixture.game.gate_515c = 1;
  cell_update_body_00e806b0(1.25F, 3.0F);
  expect_kinds({Kind::cell_prepare, Kind::cell_get_space,
                Kind::cell_space_update, Kind::cell_get_service,
                Kind::cell_service_update, Kind::cell_frustum, Kind::cell_flag,
                Kind::cell_final});
  check(fixture.game.counter_5160 == 0, "gated cell counter unchanged");
  check(fixture.player.word_74 == 0, "gated cell state unchanged");
  check(event(Kind::cell_space_update).signed_word == 3000,
        "inactive scaled second callback word");
  check(event(Kind::cell_space_update).word == 0,
        "inactive zero callback word");
  check(same_float_bits(event(Kind::cell_flag).first_scalar, 3.0F),
        "inactive e600a0 uses second word");
  check(event(Kind::cell_flag).word == 1U, "inactive e600a0 uses one flag");
  check(event(Kind::cell_frustum).receiver ==
            reinterpret_cast<const void *>(0x016b3cb8U),
        "frustum thiscall receiver");
  check(event(Kind::cell_frustum).word == 0x016b4378U,
        "frustum raw stack dword");
  check(same_float_bits(event(Kind::cell_final).first_scalar, 3.0F),
        "inactive e6c9f0 uses second word");
}

void test_cell_gate_states() {
  initialize();
  cell_update_body_00e806b0(0.0F, 3.0F);
  expect_kinds({Kind::cell_prepare, Kind::cell_get_space,
                Kind::cell_space_update, Kind::cell_get_service,
                Kind::cell_service_update, Kind::cell_frustum, Kind::cell_flag,
                Kind::cell_final});

  initialize();
  cell_update_body_00e806b0(-0.0F, 3.0F);
  expect_kinds({Kind::cell_prepare, Kind::cell_get_space,
                Kind::cell_space_update, Kind::cell_get_service,
                Kind::cell_service_update, Kind::cell_frustum, Kind::cell_flag,
                Kind::cell_final});

  initialize();
  cell_update_body_00e806b0(std::numeric_limits<float>::quiet_NaN(), 3.0F);
  expect_kinds({Kind::cell_prepare, Kind::cell_set_words, Kind::cell_get_space,
                Kind::cell_space_update, Kind::cell_get_service,
                Kind::cell_service_update, Kind::cell_move,
                Kind::cell_update_second, Kind::cell_reload,
                Kind::cell_reload_secondary, Kind::cell_update_second,
                Kind::cell_no_words, Kind::cell_followup, Kind::cell_flag,
                Kind::cell_final});
  check(event(Kind::cell_set_words).word ==
            static_cast<OpaqueWord>(std::numeric_limits<std::int32_t>::min()),
        "NaN conversion retains invalid sentinel");
  check(event(Kind::cell_set_words).signed_word == 3000,
        "NaN gate keeps ordered second word");

  initialize();
  cell_update_body_00e806b0(-1.25F, -2.5F);
  expect_kinds({Kind::cell_prepare, Kind::cell_set_words, Kind::cell_get_space,
                Kind::cell_space_update, Kind::cell_get_service,
                Kind::cell_service_update, Kind::cell_move,
                Kind::cell_update_second, Kind::cell_reload,
                Kind::cell_reload_secondary, Kind::cell_update_second,
                Kind::cell_no_words, Kind::cell_followup, Kind::cell_flag,
                Kind::cell_final});
  check(event(Kind::cell_set_words).signed_word == -2500,
        "negative second word reaches reversed first callback slot");
  check(same_float_bits(event(Kind::cell_final).first_scalar, -2.5F),
        "active e6c9f0 keeps negative second word");

  initialize();
  fixture.game.gate_515c = 1;
  cell_update_body_00e806b0(0.0F, 3.0F);
  expect_kinds({Kind::cell_prepare, Kind::cell_get_space,
                Kind::cell_space_update, Kind::cell_get_service,
                Kind::cell_service_update, Kind::cell_frustum, Kind::cell_flag,
                Kind::cell_final});
  check(same_float_bits(event(Kind::cell_final).first_scalar, 3.0F),
        "gated inactive e6c9f0 uses second word");

  initialize();
  fixture.game.state_51e0 = 1;
  fixture.ready = true;
  cell_update_body_00e806b0(0.0F, 3.0F);
  expect_kinds({Kind::cell_prepare});

  initialize();
  fixture.game.state_51e0 = 1;
  fixture.ready = true;
  cell_update_body_00e806b0(1.25F, 3.0F);
  expect_kinds({Kind::cell_prepare, Kind::cell_ready, Kind::cell_get_texture,
                Kind::cell_tail_texture});

  initialize();
  fixture.game.state_51e0 = 2;
  fixture.ready = true;
  cell_update_body_00e806b0(0.0F, 3.0F);
  expect_kinds({Kind::cell_prepare});

  initialize();
  fixture.game.state_51e0 = 2;
  fixture.ready = true;
  cell_update_body_00e806b0(1.25F, 3.0F);
  expect_kinds({Kind::cell_prepare, Kind::cell_ready, Kind::cell_get_generator,
                Kind::cell_generator});
  check(event(Kind::cell_generator).word == 0x014137f8U,
        "generator slot 20 key");
}

void test_timing_active_order() {
  initialize();
  timing_update_body_00b31cc0(&fixture.timing_owner, &fixture.timing_context);
  expect_kinds({Kind::timing_lookup, Kind::timing_begin, Kind::timing_layer,
                Kind::timing_root, Kind::timing_runtime, Kind::timing_vector,
                Kind::timing_enabled, Kind::timing_begin, Kind::timing_begin,
                Kind::timing_finish_vector, Kind::timing_speed_lookup,
                Kind::timing_speed, Kind::timing_begin,
                Kind::timing_finish_speed});
  check(event(Kind::timing_finish_vector).receiver == &fixture.timing_config,
        "bc2f00 thiscall receiver");
  const float blend = 3.0F * 0.00069444446F + 2.0F * 0.041666668F;
  check(same_float_bits(event(Kind::timing_finish_vector).first_scalar,
                        blend * 2.0F),
        "bc2f00 scaled stack argument");
  check(event(Kind::timing_lookup).word == 0U, "lookup minimum stack word");
  check(event(Kind::timing_lookup).signed_word == 1,
        "lookup maximum stack word");
  check(event(Kind::timing_root).receiver == &fixture.timing_root,
        "timing root callback");
  check(event(Kind::timing_runtime).receiver == &fixture.timing_root,
        "runtime root receiver");
  check(event(Kind::timing_vector).receiver ==
            &fixture.timing_runtime.vtable_c0,
        "embedded runtime+0xc0 receiver");
  check(event(Kind::timing_finish_vector).source != nullptr,
        "bc2f00 result pointer stack argument");
  check(event(Kind::timing_finish_vector).word == 0xaaaaaaaaU,
        "bc2f00 runtime result word zero");
  check(event(Kind::timing_finish_vector).second_word == 0xbbbbbbbbU,
        "bc2f00 runtime result word one");
  check(event(Kind::timing_finish_vector).signed_word ==
            static_cast<std::int32_t>(0xccccccccU),
        "bc2f00 runtime result word two");
  check(event(Kind::timing_speed_lookup).word == 1U, "speed selector");
  check(event(Kind::timing_speed).word == 11U, "timing speed word");
  check(same_float_bits(event(Kind::timing_finish_speed).first_scalar, 0.2F),
        "bc28c0 speed stack argument");
}

void test_timing_early_return_and_fallback() {
  initialize();
  fixture.runtime_enabled = false;
  timing_update_body_00b31cc0(&fixture.timing_owner, &fixture.timing_context);
  expect_kinds({Kind::timing_lookup, Kind::timing_begin, Kind::timing_layer,
                Kind::timing_root, Kind::timing_runtime, Kind::timing_vector,
                Kind::timing_enabled});

  initialize();
  fixture.runtime_available = false;
  timing_update_body_00b31cc0(&fixture.timing_owner, &fixture.timing_context);
  expect_kinds(
      {Kind::timing_lookup, Kind::timing_begin, Kind::timing_layer,
       Kind::timing_root, Kind::timing_runtime, Kind::timing_init_fallback,
       Kind::timing_renderer, Kind::timing_renderer_layer, Kind::timing_release,
       Kind::timing_enabled, Kind::timing_begin, Kind::timing_begin,
       Kind::timing_finish_vector, Kind::timing_speed_lookup,
       Kind::timing_speed, Kind::timing_begin, Kind::timing_finish_speed});
  check(event(Kind::timing_renderer_layer).source != nullptr,
        "fallback initialized matrix reaches layer");
  check(reinterpret_cast<std::uintptr_t>(
            event(Kind::timing_init_fallback).receiver) ==
            reinterpret_cast<std::uintptr_t>(
                event(Kind::timing_renderer_layer).source) +
                0x14U,
        "0041cb40 receiver is initialized base+0x14");
  check(event(Kind::timing_release).receiver == &fixture.layer_result,
        "fallback release layer receiver");
  check(event(Kind::timing_finish_vector).receiver == &fixture.timing_config,
        "fallback bc2f00 thiscall receiver");
  check(event(Kind::timing_finish_vector).word == raw_float(2.5F),
        "fallback result reads base+0x04");
  check(event(Kind::timing_finish_vector).second_word == raw_float(3.75F),
        "fallback result reads base+0x08");
  check(static_cast<OpaqueWord>(
            event(Kind::timing_finish_vector).signed_word) == raw_float(4.5F),
        "fallback result reads base+0x0c");
}

void test_timing_negative_context_still_queries_speed() {
  initialize();
  auto context = reinterpret_cast<OpaqueTimingContext *>(
      static_cast<std::uintptr_t>(0x80000000U));
  timing_update_body_00b31cc0(&fixture.timing_owner, context);
  expect_kinds({Kind::timing_lookup, Kind::timing_begin,
                Kind::timing_speed_lookup, Kind::timing_speed,
                Kind::timing_begin, Kind::timing_finish_speed});
  check(event(Kind::timing_lookup).receiver == context,
        "negative context lookup");
}

void test_timing_null_context_still_queries_speed() {
  initialize();
  timing_update_body_00b31cc0(&fixture.timing_owner, nullptr);
  expect_kinds({Kind::timing_lookup, Kind::timing_begin,
                Kind::timing_speed_lookup, Kind::timing_speed,
                Kind::timing_begin, Kind::timing_finish_speed});
  check(event(Kind::timing_lookup).receiver == nullptr, "null context lookup");
}

int run() {
  test_cell_rounding_nearest_even();
  test_cell_active_order();
  test_cell_frame_gate_fallback();
  test_cell_gate_states();
  test_timing_active_order();
  test_timing_early_return_and_fallback();
  test_timing_negative_context_still_queries_speed();
  test_timing_null_context_still_queries_speed();
  return static_cast<int>(failure_count);
}

}

}

int main() { return openspore::reconstruction::pkg_frame_runtime_wave8::run(); }

#undef TEST_THISCALL
#undef TEST_STDCALL
