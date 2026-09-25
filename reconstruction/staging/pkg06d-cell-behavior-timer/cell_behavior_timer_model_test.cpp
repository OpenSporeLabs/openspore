#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>

#include "cell_behavior_timer.hpp"

namespace {

using openspore::reconstruction::pkg06a_cell_ai_selection::g_cell_game_016b3c04;
using openspore::reconstruction::pkg06d_cell_behavior_timer::AdvanceCallContext;
using openspore::reconstruction::pkg06d_cell_behavior_timer::
    cell_behavior_timer_update_00e7e6c0;
using openspore::reconstruction::pkg06d_cell_behavior_timer::ExpireCallContext;
using openspore::reconstruction::pkg06d_cell_behavior_timer::
    FallbackCallContext;
using openspore::reconstruction::pkg06d_cell_behavior_timer::GateCallContext;
using openspore::reconstruction::pkg06d_cell_behavior_timer::NativePorts;
using openspore::reconstruction::pkg06d_cell_behavior_timer::
    OpaqueBehaviorTimerEntryEcx;
using openspore::reconstruction::pkg06d_cell_behavior_timer::
    OpaqueBehaviorTimerRecord;

int failures = 0;
bool gate_result = true;
bool expire_result = true;
bool advance_result = true;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

template <typename Value>
Value load(const void* object, std::size_t offset) {
  Value value{};
  std::memcpy(&value, static_cast<const unsigned char*>(object) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store(void* object, std::size_t offset, Value value) {
  std::memcpy(static_cast<unsigned char*>(object) + offset, &value,
              sizeof(value));
}

bool same_float(float first, float second) {
  return std::memcmp(&first, &second, sizeof(first)) == 0;
}

struct Fixture {
  std::array<std::byte, 0x5200> game{};
  OpaqueBehaviorTimerRecord record{};
  std::byte opaque_entry_ecx_storage{};
  OpaqueBehaviorTimerEntryEcx opaque_entry_ecx = nullptr;
};

enum class EventKind {
  gate,
  expire,
  advance,
  fallback,
};

struct Event {
  EventKind kind = EventKind::gate;
  const OpaqueBehaviorTimerRecord* record = nullptr;
  OpaqueBehaviorTimerEntryEcx opaque_entry_ecx = nullptr;
  float delta = 0.0F;
  std::uint32_t slot = 0;
  std::uint32_t first_zero = 0;
  std::uint32_t second_zero = 0;
  std::uint32_t record_id = 0;
  float record_timer = 0.0F;
  float timers[4]{};
};

std::vector<Event> events;

void add_event(EventKind kind, const OpaqueBehaviorTimerRecord* record,
               OpaqueBehaviorTimerEntryEcx opaque_entry_ecx, float delta,
               std::uint32_t slot, std::uint32_t first_zero,
               std::uint32_t second_zero) {
  Event event{};
  event.kind = kind;
  event.record = record;
  event.opaque_entry_ecx = opaque_entry_ecx;
  event.delta = delta;
  event.slot = slot;
  event.first_zero = first_zero;
  event.second_zero = second_zero;
  event.record_id = load<std::uint32_t>(record, 0);
  event.record_timer = load<float>(record, 0x1c);
  for (std::uint32_t index = 0; index < 4; ++index) {
    event.timers[index] = load<float>(record, 0x0cU + index * sizeof(float));
  }
  events.push_back(event);
}

bool gate(const GateCallContext& context) {
  add_event(EventKind::gate, context.record, context.opaque_entry_ecx,
            context.delta, 0, 0, 0);
  return gate_result;
}

bool expire(const ExpireCallContext& context) {
  add_event(EventKind::expire, context.record, nullptr, context.delta,
            context.slot, 0, 0);
  return expire_result;
}

bool advance(const AdvanceCallContext& context) {
  add_event(EventKind::advance, context.record, nullptr, context.delta, 0, 0,
            0);
  return advance_result;
}

void fallback(const FallbackCallContext& context) {
  add_event(EventKind::fallback, context.record, nullptr, context.delta, 0,
            context.first_zero, context.second_zero);
}

NativePorts make_ports() {
  NativePorts ports{};
  ports.gate_00e59c10 = gate;
  ports.expire_00e7b540 = expire;
  ports.advance_00e7ba30 = advance;
  ports.fallback_00e7e130 = fallback;
  return ports;
}

void initialize(Fixture& fixture, std::uint32_t record_id, float record_timer,
                std::uint32_t selector) {
  g_cell_game_016b3c04 = fixture.game.data();
  fixture.opaque_entry_ecx = &fixture.opaque_entry_ecx_storage;
  store<std::uint32_t>(&fixture.record, 0, record_id);
  store<float>(&fixture.record, 0x1c, record_timer);
  store<std::uint32_t>(fixture.game.data(), 0x5198, selector);
  for (std::uint32_t index = 0; index < 4; ++index) {
    store<float>(&fixture.record, 0x0cU + index * sizeof(float), 0.0F);
  }
  gate_result = true;
  expire_result = true;
  advance_result = true;
  events.clear();
}

void run(Fixture& fixture, float delta) {
  NativePorts ports = make_ports();
  cell_behavior_timer_update_00e7e6c0(&fixture.record, fixture.opaque_entry_ecx,
                                      delta, ports);
}

void check_record(const Fixture& fixture, float record_timer,
                  const std::array<float, 4>& timers) {
  check(same_float(load<float>(&fixture.record, 0x1c), record_timer));
  for (std::uint32_t index = 0; index < 4; ++index) {
    check(
        same_float(load<float>(&fixture.record, 0x0cU + index * sizeof(float)),
                   timers[index]));
  }
}

void check_event(const Event& event, EventKind kind, const Fixture& fixture,
                 float delta, std::uint32_t slot = 0,
                 std::uint32_t first_zero = 0, std::uint32_t second_zero = 0) {
  check(event.kind == kind);
  if (kind == EventKind::gate) {
    check(event.opaque_entry_ecx == fixture.opaque_entry_ecx);
  } else {
    check(event.opaque_entry_ecx == nullptr);
  }
  check(event.record == &fixture.record);
  check(same_float(event.delta, delta));
  check(event.slot == slot);
  check(event.first_zero == first_zero);
  check(event.second_zero == second_zero);
  check(event.record_id == load<std::uint32_t>(&fixture.record, 0));
}

void test_gate_false_fallback() {
  Fixture fixture{};
  initialize(fixture, 0x11U, 10.0F, 0x22U);
  for (std::uint32_t index = 0; index < 4; ++index) {
    store<float>(&fixture.record, 0x0cU + index * sizeof(float),
                 static_cast<float>(index + 1));
  }
  gate_result = false;
  advance_result = true;
  run(fixture, 2.5F);

  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, fixture, 2.5F);
    check(same_float(events[0].record_timer, 7.5F));
    check_event(events[1], EventKind::fallback, fixture, 2.5F);
    check(same_float(events[1].record_timer, 7.5F));
  }
  check_record(fixture, 7.5F, std::array<float, 4>{1.0F, 2.0F, 3.0F, 4.0F});
  check(load<std::uint32_t>(&fixture.record, 0) == 0x11U);
  check(events.size() == 2);
}

void test_all_timers_decrement_and_expire() {
  Fixture fixture{};
  initialize(fixture, 0x33U, 8.0F, 0x44U);
  for (std::uint32_t index = 0; index < 4; ++index) {
    store<float>(&fixture.record, 0x0cU + index * sizeof(float), 0.5F);
  }
  gate_result = true;
  expire_result = true;
  advance_result = true;
  run(fixture, 1.0F);

  check(events.size() == 6);
  if (events.size() == 6) {
    check_event(events[0], EventKind::gate, fixture, 1.0F);
    for (std::uint32_t index = 0; index < 4; ++index) {
      check_event(events[index + 1], EventKind::expire, fixture, 1.0F, index);
      check(same_float(events[index + 1].timers[index], 0.0F));
    }
    check_event(events[5], EventKind::advance, fixture, 1.0F);
    check(same_float(events[5].record_timer, 7.0F));
  }
  check_record(fixture, 7.0F, std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});
}

void test_positive_timer_decrements_without_expiry() {
  Fixture fixture{};
  initialize(fixture, 0x55U, 6.0F, 0x66U);
  for (std::uint32_t index = 0; index < 4; ++index) {
    store<float>(&fixture.record, 0x0cU + index * sizeof(float), 4.0F);
  }
  run(fixture, 1.25F);

  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, fixture, 1.25F);
    check_event(events[1], EventKind::advance, fixture, 1.25F);
  }
  check_record(fixture, 4.75F,
               std::array<float, 4>{2.75F, 2.75F, 2.75F, 2.75F});
}

void test_expire_false_fallback() {
  Fixture fixture{};
  initialize(fixture, 0x77U, 4.0F, 0x88U);
  store<float>(&fixture.record, 0x0c, 0.25F);
  expire_result = false;
  advance_result = true;
  run(fixture, 1.0F);

  check(events.size() == 3);
  if (events.size() == 3) {
    check_event(events[0], EventKind::gate, fixture, 1.0F);
    check_event(events[1], EventKind::expire, fixture, 1.0F, 0);
    check(same_float(events[1].timers[0], 0.0F));
    check_event(events[2], EventKind::fallback, fixture, 1.0F);
  }
  check_record(fixture, 3.0F, std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});
}

void test_main_timer_condition_inputs() {
  Fixture negative{};
  initialize(negative, 0x101U, -2.0F, 0x101U);
  advance_result = true;
  run(negative, 1.0F);
  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, negative, 1.0F);
    check_event(events[1], EventKind::advance, negative, 1.0F);
  }
  check_record(negative, -3.0F, std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});

  Fixture zero{};
  initialize(zero, 0x102U, 1.0F, 0x102U);
  advance_result = true;
  run(zero, 1.0F);
  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, zero, 1.0F);
    check(same_float(events[0].record_timer, 0.0F));
    check_event(events[1], EventKind::advance, zero, 1.0F);
    check(same_float(events[1].record_timer, 0.0F));
  }
  check_record(zero, 0.0F, std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});

  Fixture positive{};
  initialize(positive, 0x103U, 3.0F, 0x999U);
  g_cell_game_016b3c04 = nullptr;
  advance_result = true;
  run(positive, 1.0F);
  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, positive, 1.0F);
    check_event(events[1], EventKind::advance, positive, 1.0F);
  }
  check_record(positive, 2.0F, std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});

  Fixture positive_infinity{};
  initialize(positive_infinity, 0x104U, std::numeric_limits<float>::infinity(),
             0x999U);
  g_cell_game_016b3c04 = nullptr;
  advance_result = true;
  run(positive_infinity, 1.0F);
  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, positive_infinity, 1.0F);
    check_event(events[1], EventKind::advance, positive_infinity, 1.0F);
  }
  check_record(positive_infinity, std::numeric_limits<float>::infinity(),
               std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});

  Fixture negative_infinity{};
  initialize(negative_infinity, 0x105U, -std::numeric_limits<float>::infinity(),
             0x105U);
  advance_result = true;
  run(negative_infinity, 1.0F);
  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, negative_infinity, 1.0F);
    check_event(events[1], EventKind::advance, negative_infinity, 1.0F);
  }
  check_record(negative_infinity, -std::numeric_limits<float>::infinity(),
               std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});

  Fixture unordered{};
  initialize(unordered, 0x106U, std::numeric_limits<float>::quiet_NaN(),
             0x999U);
  g_cell_game_016b3c04 = nullptr;
  advance_result = false;
  run(unordered, 0.0F);
  check(events.size() == 3);
  if (events.size() == 3) {
    check_event(events[0], EventKind::gate, unordered, 0.0F);
    check(std::isnan(events[0].record_timer));
    check_event(events[1], EventKind::advance, unordered, 0.0F);
    check(std::isnan(events[1].record_timer));
    check_event(events[2], EventKind::fallback, unordered, 0.0F);
    check(std::isnan(events[2].record_timer));
  }
  check(std::isnan(load<float>(&unordered.record, 0x1c)));
}

void test_slot_zero_remaining_does_not_expire() {
  Fixture fixture{};
  initialize(fixture, 0x107U, 3.0F, 0x107U);
  store<float>(&fixture.record, 0x0c, 1.0F);
  advance_result = true;
  run(fixture, 1.0F);

  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, fixture, 1.0F);
    check_event(events[1], EventKind::advance, fixture, 1.0F);
  }
  check_record(fixture, 2.0F, std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});
}

void test_slot_nan_remaining_does_not_expire() {
  Fixture fixture{};
  initialize(fixture, 0x108U, 3.0F, 0x108U);
  store<float>(&fixture.record, 0x0c, 3.0F);
  advance_result = true;
  run(fixture, std::numeric_limits<float>::quiet_NaN());

  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, fixture,
                std::numeric_limits<float>::quiet_NaN());
    check(std::isnan(events[0].record_timer));
    check_event(events[1], EventKind::advance, fixture,
                std::numeric_limits<float>::quiet_NaN());
    check(std::isnan(events[1].record_timer));
  }
  check(std::isnan(load<float>(&fixture.record, 0x0c)));
  check(std::isnan(load<float>(&fixture.record, 0x1c)));
}

void test_nonpositive_initial_slots_skip() {
  Fixture fixture{};
  initialize(fixture, 0x109U, 3.0F, 0x109U);
  store<float>(&fixture.record, 0x0c, -1.0F);
  store<float>(&fixture.record, 0x10, std::numeric_limits<float>::quiet_NaN());
  advance_result = true;
  run(fixture, 1.0F);

  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, fixture, 1.0F);
    check_event(events[1], EventKind::advance, fixture, 1.0F);
  }
  check(same_float(load<float>(&fixture.record, 0x0c), -1.0F));
  check(std::isnan(load<float>(&fixture.record, 0x10)));
  check(same_float(load<float>(&fixture.record, 0x1c), 2.0F));
}

void test_negative_main_timer_unequal_selector_zeroes() {
  Fixture fixture{};
  initialize(fixture, 0x10aU, -1.0F, 0x10bU);
  advance_result = true;
  run(fixture, 0.0F);

  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, fixture, 0.0F);
    check(same_float(events[0].record_timer, -1.0F));
    check_event(events[1], EventKind::fallback, fixture, 0.0F);
    check(same_float(events[1].record_timer, 0.0F));
  }
  check_record(fixture, 0.0F, std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});
}

void test_selector_and_advance_branches() {
  Fixture positive_equal{};
  initialize(positive_equal, 0x99U, 3.0F, 0x99U);
  advance_result = true;
  run(positive_equal, 1.0F);
  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, positive_equal, 1.0F);
    check_event(events[1], EventKind::advance, positive_equal, 1.0F);
  }
  check_record(positive_equal, 2.0F,
               std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});

  Fixture zero_equal{};
  initialize(zero_equal, 0xaaU, 2.0F, 0xaaU);
  advance_result = true;
  run(zero_equal, 2.0F);
  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, zero_equal, 2.0F);
    check(same_float(events[0].record_timer, 0.0F));
    check_event(events[1], EventKind::advance, zero_equal, 2.0F);
    check(same_float(events[1].record_timer, 0.0F));
  }
  check_record(zero_equal, 0.0F, std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});

  Fixture negative_equal_false{};
  initialize(negative_equal_false, 0xacU, -1.0F, 0xacU);
  advance_result = false;
  run(negative_equal_false, 0.0F);
  check(events.size() == 3);
  if (events.size() == 3) {
    check_event(events[0], EventKind::gate, negative_equal_false, 0.0F);
    check(same_float(events[0].record_timer, -1.0F));
    check_event(events[1], EventKind::advance, negative_equal_false, 0.0F);
    check(same_float(events[1].record_timer, -1.0F));
    check_event(events[2], EventKind::fallback, negative_equal_false, 0.0F);
    check(same_float(events[2].record_timer, -1.0F));
  }
  check_record(negative_equal_false, -1.0F,
               std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});

  Fixture zero_unequal_false{};
  initialize(zero_unequal_false, 0xbbU, 2.0F, 0xccU);
  advance_result = true;
  run(zero_unequal_false, 2.0F);
  check(events.size() == 2);
  if (events.size() == 2) {
    check_event(events[0], EventKind::gate, zero_unequal_false, 2.0F);
    check(same_float(events[0].record_timer, 0.0F));
    check_event(events[1], EventKind::fallback, zero_unequal_false, 2.0F);
    check(same_float(events[1].record_timer, 0.0F));
  }
  check_record(zero_unequal_false, 0.0F,
               std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});

  Fixture positive_unequal_false{};
  initialize(positive_unequal_false, 0xddU, 5.0F, 0xeeU);
  advance_result = false;
  run(positive_unequal_false, 1.0F);
  check(events.size() == 3);
  if (events.size() == 3) {
    check_event(events[0], EventKind::gate, positive_unequal_false, 1.0F);
    check_event(events[1], EventKind::advance, positive_unequal_false, 1.0F);
    check_event(events[2], EventKind::fallback, positive_unequal_false, 1.0F);
    check(same_float(events[2].record_timer, 4.0F));
  }
  check_record(positive_unequal_false, 4.0F,
               std::array<float, 4>{0.0F, 0.0F, 0.0F, 0.0F});
}

void test_fallback_arguments_and_entry_ecx_boundary() {
  Fixture fixture{};
  initialize(fixture, 0x12345678U, 7.0F, 0x87654321U);
  gate_result = false;
  run(fixture, 0.5F);
  check(events.size() == 2);
  if (events.size() == 2) {
    check(events[0].opaque_entry_ecx == fixture.opaque_entry_ecx);
    check(events[1].opaque_entry_ecx == nullptr);
    check(events[1].first_zero == 0);
    check(events[1].second_zero == 0);
  }
}

}  // namespace

int main() {
  test_gate_false_fallback();
  test_all_timers_decrement_and_expire();
  test_positive_timer_decrements_without_expiry();
  test_main_timer_condition_inputs();
  test_slot_zero_remaining_does_not_expire();
  test_slot_nan_remaining_does_not_expire();
  test_nonpositive_initial_slots_skip();
  test_negative_main_timer_unequal_selector_zeroes();
  test_expire_false_fallback();
  test_selector_and_advance_branches();
  test_fallback_arguments_and_entry_ecx_boundary();
  return failures == 0 ? 0 : 1;
}
