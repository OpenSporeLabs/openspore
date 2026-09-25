#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <vector>

#include "creature_progression.hpp"

namespace {

using ::DAT_0169e398;
using openspore::reconstruction::pkg13_c1_creature_progression::NativePorts;
using openspore::reconstruction::pkg13_c1_creature_progression::
    OpaqueNounManager;
using openspore::reconstruction::pkg13_c1_creature_progression::
    pkg13_progression_brain_level_00d2e830;
using openspore::reconstruction::pkg13_c1_creature_progression::
    ProgressionPlayerAccessWindow;
using openspore::reconstruction::pkg13_c1_creature_progression::
    Simulator_cCreatureGameData_SetEvolutionPoints_raw_00d2e480;

using openspore::reconstruction::pkg13_c1_creature_progression::g_native_ports;

enum class TraceKind : std::uint8_t {
  kNounManager,
  kProgressionPlayer,
  kLevelRequirement,
  kEvent,
};

struct TraceEntry {
  TraceKind kind;
  std::int32_t level;
};

OpaqueNounManager noun_manager{};
ProgressionPlayerAccessWindow player{};
std::array<float, 4> requirements{10.0F, 20.0F, 30.0F, 40.0F};
std::vector<TraceEntry> trace;
int event_count = 0;

OpaqueNounManager* GetNounManager() {
  trace.push_back({TraceKind::kNounManager, -1});
  return &noun_manager;
}

ProgressionPlayerAccessWindow* GetProgressionPlayer(
    OpaqueNounManager* receiver) {
  assert(receiver == &noun_manager);
  trace.push_back({TraceKind::kProgressionPlayer, -1});
  return &player;
}

float GetLevelRequirement(std::int32_t level) {
  assert(level >= 0 && level < static_cast<std::int32_t>(requirements.size()));
  trace.push_back({TraceKind::kLevelRequirement, level});
  return requirements[static_cast<std::size_t>(level)];
}

void InstallPorts() {
  g_native_ports = {GetNounManager, GetProgressionPlayer, GetLevelRequirement};
}

void SetPlayerPoints(float points) {
  std::memcpy(player.bytes.data() + 0x10f0U, &points, sizeof(points));
}

bool SameFloatBits(float left, float right) {
  std::uint32_t left_bits;
  std::uint32_t right_bits;
  std::memcpy(&left_bits, &left, sizeof(left_bits));
  std::memcpy(&right_bits, &right, sizeof(right_bits));
  return left_bits == right_bits;
}

void ExpectTrace(std::initializer_list<TraceKind> expected_kinds,
                 std::initializer_list<std::int32_t> expected_levels) {
  assert(trace.size() == expected_kinds.size());
  std::size_t index = 0;
  for (const TraceKind expected_kind : expected_kinds) {
    assert(trace[index].kind == expected_kind);
    ++index;
  }
  index = 0;
  for (const std::int32_t expected_level : expected_levels) {
    assert(trace[index].level == expected_level);
    ++index;
  }
}

void TestSetterExactFloatStateTransitions() {
  const float values[] = {
      0.0F,
      -0.0F,
      -1234.5F,
      10000.0F,
      std::numeric_limits<float>::infinity(),
      -std::numeric_limits<float>::infinity(),
      std::numeric_limits<float>::quiet_NaN(),
  };

  for (const float value : values) {
    trace.clear();
    event_count = 0;
    Simulator_cCreatureGameData_SetEvolutionPoints_raw_00d2e480(value);
    assert(SameFloatBits(DAT_0169e398, value));
    assert(trace.empty());
    assert(event_count == 0);
  }
}

void TestStrictCumulativeBoundaries() {
  requirements = {10.0F, 20.0F, 30.0F, 40.0F};
  struct Case {
    float points;
    std::int32_t expected_level;
  };
  const Case cases[] = {
      {-std::numeric_limits<float>::infinity(), 0},
      {std::nextafter(10.0F, -std::numeric_limits<float>::infinity()), 0},
      {10.0F, 1},
      {std::nextafter(10.0F, std::numeric_limits<float>::infinity()), 1},
      {30.0F, 2},
      {std::nextafter(30.0F, std::numeric_limits<float>::infinity()), 2},
      {60.0F, 3},
      {std::nextafter(60.0F, std::numeric_limits<float>::infinity()), 3},
      {100.0F, 4},
      {std::nextafter(100.0F, std::numeric_limits<float>::infinity()), 4},
      {std::numeric_limits<float>::infinity(), 4},
  };

  for (const Case& test_case : cases) {
    SetPlayerPoints(test_case.points);
    trace.clear();
    event_count = 0;
    const std::int32_t actual = pkg13_progression_brain_level_00d2e830();
    assert(actual == test_case.expected_level);
    assert(event_count == 0);

    const std::size_t threshold_calls =
        test_case.expected_level == 4
            ? 4U
            : static_cast<std::size_t>(test_case.expected_level + 1);
    assert(trace.size() == threshold_calls + 2U);
    assert(trace[0].kind == TraceKind::kNounManager);
    assert(trace[1].kind == TraceKind::kProgressionPlayer);
    for (std::size_t index = 0; index < threshold_calls; ++index) {
      assert(trace[index + 2U].kind == TraceKind::kLevelRequirement);
      assert(trace[index + 2U].level == static_cast<std::int32_t>(index));
    }
  }
}

void TestNaNAndNoMutationEventBoundary() {
  requirements = {10.0F, 20.0F, 30.0F, 40.0F};
  SetPlayerPoints(std::numeric_limits<float>::quiet_NaN());
  trace.clear();
  event_count = 0;
  assert(pkg13_progression_brain_level_00d2e830() == 4);
  ExpectTrace({TraceKind::kNounManager, TraceKind::kProgressionPlayer,
               TraceKind::kLevelRequirement, TraceKind::kLevelRequirement,
               TraceKind::kLevelRequirement, TraceKind::kLevelRequirement},
              {-1, -1, 0, 1, 2, 3});
  assert(event_count == 0);

  requirements = {10.0F, 20.0F, std::numeric_limits<float>::quiet_NaN(), 40.0F};
  SetPlayerPoints(35.0F);
  const std::array<std::uint8_t, 0x10f4> before = player.bytes;
  trace.clear();
  assert(pkg13_progression_brain_level_00d2e830() == 4);
  assert(player.bytes == before);
  ExpectTrace({TraceKind::kNounManager, TraceKind::kProgressionPlayer,
               TraceKind::kLevelRequirement, TraceKind::kLevelRequirement,
               TraceKind::kLevelRequirement, TraceKind::kLevelRequirement},
              {-1, -1, 0, 1, 2, 3});
  assert(event_count == 0);
}

void TestExactCallAndEventOrder() {
  requirements = {10.0F, 10.0F, 10.0F, 10.0F};
  SetPlayerPoints(41.0F);
  trace.clear();
  event_count = 0;
  assert(pkg13_progression_brain_level_00d2e830() == 4);
  ExpectTrace({TraceKind::kNounManager, TraceKind::kProgressionPlayer,
               TraceKind::kLevelRequirement, TraceKind::kLevelRequirement,
               TraceKind::kLevelRequirement, TraceKind::kLevelRequirement},
              {-1, -1, 0, 1, 2, 3});
  assert(event_count == 0);
}

}

int main() {
  InstallPorts();
  TestSetterExactFloatStateTransitions();
  TestStrictCumulativeBoundaries();
  TestNaNAndNoMutationEventBoundary();
  TestExactCallAndEventOrder();
}
