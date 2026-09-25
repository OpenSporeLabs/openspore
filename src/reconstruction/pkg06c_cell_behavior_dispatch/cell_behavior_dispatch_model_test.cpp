#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>

#include "cell_behavior_dispatch.hpp"

namespace {

using openspore::reconstruction::pkg06c_cell_behavior_dispatch::
    cell_behavior_dispatch_00e7a190;
using openspore::reconstruction::pkg06c_cell_behavior_dispatch::
    NativeCallContext;
using openspore::reconstruction::pkg06c_cell_behavior_dispatch::NativePorts;
using openspore::reconstruction::pkg06c_cell_behavior_dispatch::
    ObservedCellCellResource;
using openspore::reconstruction::pkg06c_cell_behavior_dispatch::
    ObservedCellObjectData;

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

template <typename T>
T load(const void* object, std::size_t offset) {
  T value{};
  std::memcpy(&value, static_cast<const unsigned char*>(object) + offset,
              sizeof(value));
  return value;
}

template <typename T>
void store(void* object, std::size_t offset, T value) {
  std::memcpy(static_cast<unsigned char*>(object) + offset, &value,
              sizeof(value));
}

std::int32_t load_i32(const void* object, std::size_t offset) {
  return load<std::int32_t>(object, offset);
}

void store_u8(void* object, std::size_t offset, std::uint8_t value) {
  store<std::uint8_t>(object, offset, value);
}

void store_i32(void* object, std::size_t offset, std::int32_t value) {
  store<std::int32_t>(object, offset, value);
}

void store_u32(void* object, std::size_t offset, std::uint32_t value) {
  store<std::uint32_t>(object, offset, value);
}

void store_float(void* object, std::size_t offset, float value) {
  store<float>(object, offset, value);
}

bool same_float(float first, float second) {
  return std::memcmp(&first, &second, sizeof(first)) == 0;
}

enum class PortKind {
  pre_dispatch,
  value,
  raw_00e6f800,
  priority,
  player,
  dispatch_1001,
  dispatch_1003,
  dispatch_1004,
  dispatch_1005,
  dispatch_1006,
  dispatch_1007,
  dispatch_1008,
  dispatch_1009,
  dispatch_100b,
  dispatch_100c,
  dispatch_100d,
  dispatch_100e,
};

struct Event {
  PortKind kind = PortKind::pre_dispatch;
  NativeCallContext context{};
  std::uint32_t player_index = 0;
  float value0 = 0.0F;
  float value1 = 0.0F;
  std::uint32_t word0 = 0;
  std::uint32_t word1 = 0;
  std::uint32_t word2 = 0;
};

std::vector<Event> events;
std::uint32_t helper_result = 0x12345678U;
bool pre_mutates_object_id = false;
std::uint32_t pre_mutation_id = 0;
std::byte* pre_swap_game = nullptr;
std::byte* value_swap_game = nullptr;

void add_event(PortKind kind, const NativeCallContext& context,
               std::uint32_t player_index, float value0, float value1,
               std::uint32_t word0, std::uint32_t word1, std::uint32_t word2) {
  Event event{};
  event.kind = kind;
  event.context = context;
  event.player_index = player_index;
  event.value0 = value0;
  event.value1 = value1;
  event.word0 = word0;
  event.word1 = word1;
  event.word2 = word2;
  events.push_back(event);
}

void pre_dispatch(const NativeCallContext& context) {
  add_event(PortKind::pre_dispatch, context, 0, 0.0F, 0.0F, 0, 0, 0);
  if (pre_mutates_object_id) {
    store_u32(context.object, 0, pre_mutation_id);
  }
  if (pre_swap_game != nullptr) {
    openspore::reconstruction::pkg06a_cell_ai_selection::g_cell_game_016b3c04 =
        pre_swap_game;
  }
}

std::uint32_t value(const NativeCallContext& context, std::uint32_t one,
                    std::uint32_t profile_byte) {
  add_event(PortKind::value, context, 0, 0.0F, 0.0F, one, profile_byte, 0);
  if (value_swap_game != nullptr) {
    openspore::reconstruction::pkg06a_cell_ai_selection::g_cell_game_016b3c04 =
        value_swap_game;
  }
  return helper_result;
}

void raw_00e6f800(const NativeCallContext& context, std::uint32_t player_index,
                  float value0, float value1, std::uint32_t word0,
                  std::uint32_t word1, std::uint32_t word2) {
  add_event(PortKind::raw_00e6f800, context, player_index, value0, value1,
            word0, word1, word2);
}

void priority(const NativeCallContext& context) {
  add_event(PortKind::priority, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void player(const NativeCallContext& context) {
  add_event(PortKind::player, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_1001(const NativeCallContext& context) {
  add_event(PortKind::dispatch_1001, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_1003(const NativeCallContext& context) {
  add_event(PortKind::dispatch_1003, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_1004(const NativeCallContext& context) {
  add_event(PortKind::dispatch_1004, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_1005(const NativeCallContext& context) {
  add_event(PortKind::dispatch_1005, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_1006(const NativeCallContext& context) {
  add_event(PortKind::dispatch_1006, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_1007(const NativeCallContext& context) {
  add_event(PortKind::dispatch_1007, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_1008(const NativeCallContext& context) {
  add_event(PortKind::dispatch_1008, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_1009(const NativeCallContext& context) {
  add_event(PortKind::dispatch_1009, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_100b(const NativeCallContext& context) {
  add_event(PortKind::dispatch_100b, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_100c(const NativeCallContext& context) {
  add_event(PortKind::dispatch_100c, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_100d(const NativeCallContext& context) {
  add_event(PortKind::dispatch_100d, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

void dispatch_100e(const NativeCallContext& context) {
  add_event(PortKind::dispatch_100e, context, 0, 0.0F, 0.0F, 0, 0, 0);
}

NativePorts make_ports() {
  NativePorts ports{};
  ports.pre_dispatch_00e76a80 = pre_dispatch;
  ports.value_00e67c40 = value;
  ports.raw_00e6f800 = raw_00e6f800;
  ports.priority_00e71c00 = priority;
  ports.player_00e6f5b0 = player;
  ports.dispatch_1001_00e71300 = dispatch_1001;
  ports.dispatch_1003_00e70650 = dispatch_1003;
  ports.dispatch_1004_00e704b0 = dispatch_1004;
  ports.dispatch_1005_00e702d0 = dispatch_1005;
  ports.dispatch_1006_00e7a0a0 = dispatch_1006;
  ports.dispatch_1007_00e6f990 = dispatch_1007;
  ports.dispatch_1008_00e78fc0 = dispatch_1008;
  ports.dispatch_1009_00e707d0 = dispatch_1009;
  ports.dispatch_100b_00e6fbb0 = dispatch_100b;
  ports.dispatch_100c_00e6fd70 = dispatch_100c;
  ports.dispatch_100d_00e6fce0 = dispatch_100d;
  ports.dispatch_100e_00e7a0d0 = dispatch_100e;
  return ports;
}

struct Fixture {
  std::array<std::byte, 0x5280> game{};
  ObservedCellCellResource resource{};
  ObservedCellObjectData object{};
};

void configure_game(std::array<std::byte, 0x5280>& game,
                    std::int32_t difficulty, std::uint32_t player_index,
                    std::uint32_t special_index, std::int32_t special_mode,
                    std::uint32_t priority_index, std::uint8_t suppression) {
  std::byte* serializable = game.data() + 0x100;
  store_u32(game.data(), 0x5190,
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(serializable)));
  store_i32(serializable, 0x7c, difficulty);
  store_u32(game.data(), 0x411c, player_index);
  store_u32(game.data(), 0x51b0, special_index);
  store_i32(game.data(), 0x51b4, special_mode);
  store_u32(game.data(), 0x51d4, priority_index);
  store_u8(game.data(), 0x51db, suppression);
}

void initialize(Fixture& fixture) {
  openspore::reconstruction::pkg06a_cell_ai_selection::g_cell_game_016b3c04 =
      fixture.game.data();
  std::byte* serializable = fixture.game.data() + 0x100;
  store_u32(fixture.game.data(), 0x5190,
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(serializable)));
  store_i32(serializable, 0x7c, 1);
  store_u32(fixture.game.data(), 0x411c, 0x77U);
  store_u32(fixture.game.data(), 0x51b0, 0x30U);
  store_i32(fixture.game.data(), 0x51b4, 2);
  store_u32(fixture.game.data(), 0x51d4, 0x40U);
  store_u8(fixture.game.data(), 0x51db, 0);
  store_u32(&fixture.object, 0x000, 0x20U);
  store_u32(&fixture.object, 0x18c, 0);
  fixture.resource.normal.type = 0x1001;
  fixture.resource.ai_hard.type = 0x1002;
  fixture.resource.ai_easy.type = 0x1003;
}

template <typename T>
std::array<std::byte, sizeof(T)> snapshot(const T& value) {
  std::array<std::byte, sizeof(T)> result{};
  std::memcpy(result.data(), &value, sizeof(T));
  return result;
}

template <typename T>
bool unchanged(const T& value, const std::array<std::byte, sizeof(T)>& before) {
  return std::memcmp(&value, before.data(), sizeof(T)) == 0;
}

void run_and_check_mutation(Fixture& fixture, NativePorts& ports, float delta,
                            bool expect_state_ten) {
  const auto game_before = snapshot(fixture.game);
  const auto resource_before = snapshot(fixture.resource);
  ObservedCellObjectData object_before = fixture.object;
  if (expect_state_ten) {
    store_i32(&object_before, 0x18c, 10);
  }

  cell_behavior_dispatch_00e7a190(&fixture.resource, &fixture.object, delta,
                                  ports);

  check(unchanged(fixture.game, game_before));
  check(unchanged(fixture.resource, resource_before));
  check(std::memcmp(&fixture.object, &object_before, sizeof(fixture.object)) ==
        0);
}

void check_context(const NativeCallContext& context, const Fixture& fixture,
                   float delta) {
  check(context.object == &fixture.object);
  check(context.resource == &fixture.resource);
  check(context.game == fixture.game.data());
  check(same_float(context.delta, delta));
}

void check_pre(const Fixture& fixture, float delta) {
  check(!events.empty());
  if (events.empty()) {
    return;
  }
  check(events[0].kind == PortKind::pre_dispatch);
  check_context(events[0].context, fixture, delta);
}

void test_activity_gates() {
  NativePorts ports = make_ports();

  Fixture inactive{};
  initialize(inactive);
  inactive.resource.normal.type = 0;
  events.clear();
  run_and_check_mutation(inactive, ports, 1.0F, false);
  check(events.empty());

  Fixture player_zero{};
  initialize(player_zero);
  store_u32(&player_zero.object, 0, 0x77U);
  player_zero.resource.normal.type = 0;
  events.clear();
  run_and_check_mutation(player_zero, ports, 2.0F, false);
  check(events.size() == 2);
  check_pre(player_zero, 2.0F);
  if (events.size() == 2) {
    check(events[1].kind == PortKind::player);
    check_context(events[1].context, player_zero, 2.0F);
  }

  Fixture active_negative{};
  initialize(active_negative);
  active_negative.resource.normal.type = -1;
  events.clear();
  run_and_check_mutation(active_negative, ports, 3.0F, false);
  check(events.size() == 1);
  check_pre(active_negative, 3.0F);

  Fixture easy_fallback{};
  initialize(easy_fallback);
  store_i32(easy_fallback.game.data() + 0x100, 0x7c, 0);
  easy_fallback.resource.ai_easy.type = -1;
  easy_fallback.resource.normal.type = 0;
  events.clear();
  run_and_check_mutation(easy_fallback, ports, 4.0F, false);
  check(events.empty());

  Fixture hard_fallback{};
  initialize(hard_fallback);
  store_i32(hard_fallback.game.data() + 0x100, 0x7c, 2);
  hard_fallback.resource.ai_hard.type = -1;
  hard_fallback.resource.normal.type = 0;
  events.clear();
  run_and_check_mutation(hard_fallback, ports, 5.0F, false);
  check(events.empty());

  Fixture normal_other{};
  initialize(normal_other);
  store_i32(normal_other.game.data() + 0x100, 0x7c, 3);
  normal_other.resource.normal.type = 0;
  normal_other.resource.ai_hard.type = 0;
  normal_other.resource.ai_easy.type = 0;
  events.clear();
  run_and_check_mutation(normal_other, ports, 6.0F, false);
  check(events.empty());

  Fixture easy_positive{};
  initialize(easy_positive);
  store_i32(easy_positive.game.data() + 0x100, 0x7c, 0);
  easy_positive.resource.normal.type = 0;
  easy_positive.resource.ai_easy.type = 0x1001;
  events.clear();
  run_and_check_mutation(easy_positive, ports, 7.0F, false);
  check(events.size() == 2);
  check_pre(easy_positive, 7.0F);
  if (events.size() == 2) {
    check(events[1].kind == PortKind::dispatch_1001);
    check_context(events[1].context, easy_positive, 7.0F);
  }

  Fixture hard_positive{};
  initialize(hard_positive);
  store_i32(hard_positive.game.data() + 0x100, 0x7c, 2);
  hard_positive.resource.normal.type = 0;
  hard_positive.resource.ai_hard.type = 0x1001;
  events.clear();
  run_and_check_mutation(hard_positive, ports, 8.0F, false);
  check(events.size() == 2);
  check_pre(hard_positive, 8.0F);
  if (events.size() == 2) {
    check(events[1].kind == PortKind::dispatch_1001);
    check_context(events[1].context, hard_positive, 8.0F);
  }
}

void test_later_selector() {
  NativePorts ports = make_ports();

  Fixture easy{};
  initialize(easy);
  store_i32(easy.game.data() + 0x100, 0x7c, 0);
  easy.resource.ai_easy.type = 0x1004;
  events.clear();
  run_and_check_mutation(easy, ports, 9.0F, false);
  check(events.size() == 2);
  check_pre(easy, 9.0F);
  if (events.size() == 2) {
    check(events[1].kind == PortKind::dispatch_1004);
    check_context(events[1].context, easy, 9.0F);
  }

  Fixture hard{};
  initialize(hard);
  store_i32(hard.game.data() + 0x100, 0x7c, 2);
  hard.resource.ai_hard.type = 0x1005;
  events.clear();
  run_and_check_mutation(hard, ports, 10.0F, false);
  check(events.size() == 2);
  check_pre(hard, 10.0F);
  if (events.size() == 2) {
    check(events[1].kind == PortKind::dispatch_1005);
    check_context(events[1].context, hard, 10.0F);
  }
}

void test_early_gates() {
  NativePorts ports = make_ports();

  Fixture write_state{};
  initialize(write_state);
  store_u8(&write_state.object, 0x112, 1);
  store_i32(&write_state.object, 0x18c, 4);
  events.clear();
  run_and_check_mutation(write_state, ports, 7.0F, true);
  check(events.size() == 1);
  check_pre(write_state, 7.0F);
  check(load_i32(&write_state.object, 0x18c) == 10);

  Fixture state_eight{};
  initialize(state_eight);
  store_u8(&state_eight.object, 0x112, 1);
  store_i32(&state_eight.object, 0x18c, 8);
  events.clear();
  run_and_check_mutation(state_eight, ports, 8.0F, false);
  check(events.size() == 2);
  check_pre(state_eight, 8.0F);
  if (events.size() == 2) {
    check(events[1].kind == PortKind::dispatch_1001);
  }

  Fixture return_gate{};
  initialize(return_gate);
  store_u8(&return_gate.object, 0x16c, 1);
  events.clear();
  run_and_check_mutation(return_gate, ports, 9.0F, false);
  check(events.size() == 1);
  check_pre(return_gate, 9.0F);

  Fixture suppressed{};
  initialize(suppressed);
  store_u32(&suppressed.object, 0, 0x77U);
  store_u8(suppressed.game.data(), 0x51db, 1);
  events.clear();
  run_and_check_mutation(suppressed, ports, 10.0F, false);
  check(events.size() == 1);
  check_pre(suppressed, 10.0F);
}

void test_special(float first_value, float fallback_value, std::int32_t mode,
                  float expected_value, bool mode_three) {
  NativePorts ports = make_ports();
  Fixture fixture{};
  initialize(fixture);
  store_u32(&fixture.object, 0, 0x30U);
  store_i32(fixture.game.data(), 0x51b4, mode);
  store_float(&fixture.resource.normal, 0x1c, first_value);
  store_float(&fixture.resource.normal, 0x18, fallback_value);
  store_float(&fixture.resource.normal, 0x40, 4.5F);
  store_u8(&fixture.resource.normal, 0x44, 0x5a);
  events.clear();
  run_and_check_mutation(fixture, ports, 11.0F, false);

  check_pre(fixture, 11.0F);
  if (mode_three) {
    check(events.size() == 3);
    if (events.size() == 3) {
      check(events[1].kind == PortKind::value);
      check_context(events[1].context, fixture, 11.0F);
      check(events[1].word0 == 1);
      check(events[1].word1 == 0x5a);
      check(events[2].kind == PortKind::raw_00e6f800);
      check_context(events[2].context, fixture, 11.0F);
      check(events[2].player_index == 0x77U);
      check(same_float(events[2].value0, expected_value));
      check(same_float(events[2].value1, 4.5F));
      check(events[2].word0 == helper_result);
      check(events[2].word1 == 1);
      check(events[2].word2 == 0x5a);
    }
  } else {
    check(events.size() == 2);
    if (events.size() == 2) {
      check(events[1].kind == PortKind::dispatch_1001);
      check_context(events[1].context, fixture, 11.0F);
    }
  }
}

void test_special_paths() {
  test_special(0.0F, 8.0F, 3, 8.0F, true);
  test_special(std::numeric_limits<float>::quiet_NaN(), 9.0F, 3,
               std::numeric_limits<float>::quiet_NaN(), true);
  test_special(3.25F, 10.0F, 3, 3.25F, true);
  test_special(4.5F, 10.0F, 2, 10.0F, false);
}

void test_priority_and_player() {
  NativePorts ports = make_ports();

  Fixture priority{};
  initialize(priority);
  store_u32(&priority.object, 0, 0x40U);
  events.clear();
  run_and_check_mutation(priority, ports, 12.0F, false);
  check(events.size() == 2);
  check_pre(priority, 12.0F);
  if (events.size() == 2) {
    check(events[1].kind == PortKind::priority);
    check_context(events[1].context, priority, 12.0F);
  }

  Fixture player_fixture{};
  initialize(player_fixture);
  store_u32(&player_fixture.object, 0, 0x77U);
  events.clear();
  run_and_check_mutation(player_fixture, ports, 13.0F, false);
  check(events.size() == 2);
  check_pre(player_fixture, 13.0F);
  if (events.size() == 2) {
    check(events[1].kind == PortKind::player);
    check_context(events[1].context, player_fixture, 13.0F);
  }
}

void test_dispatch_value(std::int32_t type, PortKind kind) {
  NativePorts ports = make_ports();
  Fixture fixture{};
  initialize(fixture);
  fixture.resource.normal.type = type;
  events.clear();
  run_and_check_mutation(fixture, ports, 14.0F, false);
  check(events.size() == 2);
  check_pre(fixture, 14.0F);
  if (events.size() == 2) {
    check(events[1].kind == kind);
    check_context(events[1].context, fixture, 14.0F);
  }
}

void test_dispatch_values() {
  test_dispatch_value(0x1001, PortKind::dispatch_1001);
  test_dispatch_value(0x1003, PortKind::dispatch_1003);
  test_dispatch_value(0x1004, PortKind::dispatch_1004);
  test_dispatch_value(0x1005, PortKind::dispatch_1005);
  test_dispatch_value(0x1006, PortKind::dispatch_1006);
  test_dispatch_value(0x1007, PortKind::dispatch_1007);
  test_dispatch_value(0x1008, PortKind::dispatch_1008);
  test_dispatch_value(0x1009, PortKind::dispatch_1009);
  test_dispatch_value(0x100b, PortKind::dispatch_100b);
  test_dispatch_value(0x100c, PortKind::dispatch_100c);
  test_dispatch_value(0x100d, PortKind::dispatch_100d);
  test_dispatch_value(0x100e, PortKind::dispatch_100e);
}

void test_default_values() {
  const std::int32_t values[] = {0x1002, 0x100a, 0x100f, 0x2000, -2};
  for (const std::int32_t type : values) {
    NativePorts ports = make_ports();
    Fixture fixture{};
    initialize(fixture);
    fixture.resource.normal.type = type;
    events.clear();
    run_and_check_mutation(fixture, ports, 15.0F, false);
    check(events.size() == 1);
    check_pre(fixture, 15.0F);
  }
}

void test_pre_dispatch_reload() {
  NativePorts ports = make_ports();

  Fixture suppression{};
  initialize(suppression);
  store_u8(suppression.game.data(), 0x51db, 1);
  pre_mutates_object_id = true;
  pre_mutation_id = 0x77U;
  events.clear();
  cell_behavior_dispatch_00e7a190(&suppression.resource, &suppression.object,
                                  16.0F, ports);
  check(events.size() == 1);
  check_pre(suppression, 16.0F);
  check(load<std::uint32_t>(&suppression.object, 0) == 0x77U);

  Fixture special{};
  initialize(special);
  store_i32(special.game.data(), 0x51b4, 3);
  pre_mutates_object_id = true;
  pre_mutation_id = 0x30U;
  events.clear();
  cell_behavior_dispatch_00e7a190(&special.resource, &special.object, 17.0F,
                                  ports);
  check(events.size() == 3);
  check_pre(special, 17.0F);
  if (events.size() == 3) {
    check(events[1].kind == PortKind::value);
    check(events[2].kind == PortKind::raw_00e6f800);
  }

  Fixture dispatch{};
  initialize(dispatch);
  store_u32(&dispatch.object, 0, 0x30U);
  pre_mutates_object_id = true;
  pre_mutation_id = 0x20U;
  events.clear();
  cell_behavior_dispatch_00e7a190(&dispatch.resource, &dispatch.object, 18.0F,
                                  ports);
  check(events.size() == 2);
  check_pre(dispatch, 18.0F);
  if (events.size() == 2) {
    check(events[1].kind == PortKind::dispatch_1001);
  }

  pre_mutates_object_id = false;
}

void test_game_reload() {
  NativePorts ports = make_ports();
  std::array<std::byte, 0x5280> second_game{};

  Fixture suppression{};
  initialize(suppression);
  configure_game(second_game, 1, 0x77U, 0x30U, 2, 0x40U, 1);
  store_u32(&suppression.object, 0, 0x77U);
  pre_swap_game = second_game.data();
  events.clear();
  cell_behavior_dispatch_00e7a190(&suppression.resource, &suppression.object,
                                  19.0F, ports);
  check(events.size() == 1);
  check_pre(suppression, 19.0F);
  if (events.size() == 1) {
    check(events[0].context.game == suppression.game.data());
  }

  Fixture special{};
  initialize(special);
  configure_game(second_game, 1, 0x88U, 0x30U, 3, 0x40U, 0);
  store_u32(&special.object, 0, 0x30U);
  pre_swap_game = second_game.data();
  events.clear();
  cell_behavior_dispatch_00e7a190(&special.resource, &special.object, 20.0F,
                                  ports);
  check(events.size() == 3);
  if (events.size() == 3) {
    check(events[0].context.game == special.game.data());
    check(events[1].kind == PortKind::value);
    check(events[1].context.game == second_game.data());
    check(events[2].kind == PortKind::raw_00e6f800);
    check(events[2].context.game == second_game.data());
    check(events[2].context.object == &special.object);
    check(events[2].context.resource == &special.resource);
    check(events[2].player_index == 0x88U);
  }

  pre_swap_game = nullptr;
  Fixture value_swap{};
  initialize(value_swap);
  store_i32(value_swap.game.data(), 0x51b4, 3);
  configure_game(second_game, 1, 0x88U, 0x30U, 3, 0x40U, 0);
  store_u32(&value_swap.object, 0, 0x30U);
  value_swap_game = second_game.data();
  events.clear();
  cell_behavior_dispatch_00e7a190(&value_swap.resource, &value_swap.object,
                                  21.0F, ports);
  check(events.size() == 3);
  if (events.size() == 3) {
    check(events[1].kind == PortKind::value);
    check(events[1].context.game == value_swap.game.data());
    check(events[2].kind == PortKind::raw_00e6f800);
    check(events[2].context.game == second_game.data());
    check(events[2].player_index == 0x88U);
  }
  value_swap_game = nullptr;
}

}  // namespace

int main() {
  test_activity_gates();
  test_later_selector();
  test_early_gates();
  test_special_paths();
  test_priority_and_player();
  test_dispatch_values();
  test_default_values();
  test_pre_dispatch_reload();
  test_game_reload();
  return failures == 0 ? 0 : 1;
}
