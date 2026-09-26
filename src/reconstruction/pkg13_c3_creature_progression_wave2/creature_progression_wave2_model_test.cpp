#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>

#include "creature_progression_wave2.hpp"

#if defined(_MSC_VER)
#define PKG13_C3_TEST_THISCALL __thiscall
#else
#define PKG13_C3_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg13_c3_creature_progression_wave2 {
struct OpaqueAvatar {
  std::uint32_t opaque_word = 0;
};
}

namespace {

using namespace openspore::reconstruction::pkg13_c3_creature_progression_wave2;

enum class CallKind : std::uint8_t {
  kGetNounManager,
  kGetProgressionPlayer,
  kGetEventGate,
  kGetActionStrategy,
  kTransitionAvatar,
  kGetAvatar,
  kExecuteAction,
};

struct TraceEntry {
  CallKind kind;
  const void* receiver = nullptr;
  std::uint32_t action_id = 0;
  float points = 0.0F;
  const OpaqueActionPayload* payload = nullptr;
};

int failures = 0;
OpaqueNounManager manager{};
OpaqueNounManager* manager_result = &manager;
OpaqueNounManager* second_manager_result = &manager;
ProgressionPlayerAccessWindow player{};
ProgressionPlayerAccessWindow* player_result = &player;
OpaqueActionStrategy strategy{};
OpaqueActionStrategy* strategy_result = &strategy;
OpaqueAvatar avatar{};
const void* event_gate_result = reinterpret_cast<const void*>(0x2000U);
std::vector<TraceEntry> trace;
OpaqueActionPayload last_payload{};
const OpaqueActionPayload* last_payload_address = nullptr;
OpaqueActionStrategy* last_action_strategy = nullptr;
std::uint32_t last_action_id = 0;

void Expect(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void Trace(CallKind kind, const void* receiver = nullptr,
           std::uint32_t action_id = 0, float points = 0.0F,
           const OpaqueActionPayload* payload = nullptr) {
  trace.push_back({kind, receiver, action_id, points, payload});
}

bool SameFloatBits(float left, float right) {
  std::uint32_t left_bits = 0;
  std::uint32_t right_bits = 0;
  std::memcpy(&left_bits, &left, sizeof(left_bits));
  std::memcpy(&right_bits, &right, sizeof(right_bits));
  return left_bits == right_bits;
}

OpaqueNounManager* GetNounManager() {
  Trace(CallKind::kGetNounManager, manager_result);
  return manager_result;
}

ProgressionPlayerAccessWindow* PKG13_C3_TEST_THISCALL
GetProgressionPlayer(OpaqueNounManager* receiver) {
  Trace(CallKind::kGetProgressionPlayer, receiver);
  Expect(receiver == manager_result);
  return player_result;
}

const void* GetEventGate() {
  Trace(CallKind::kGetEventGate);
  return event_gate_result;
}

OpaqueActionStrategy* GetActionStrategy() {
  Trace(CallKind::kGetActionStrategy);
  return strategy_result;
}

void PKG13_C3_TEST_THISCALL TransitionAvatar(OpaqueAvatar* receiver,
                                             float points) {
  Trace(CallKind::kTransitionAvatar, receiver, 0, points);
  Expect(receiver == strategy.transition_receiver);
}

OpaqueAvatar* PKG13_C3_TEST_THISCALL GetAvatar(OpaqueNounManager* receiver) {
  Trace(CallKind::kGetAvatar, receiver);
  Expect(receiver == second_manager_result);
  return &avatar;
}

void PKG13_C3_TEST_THISCALL ExecuteAction(OpaqueActionStrategy* receiver,
                                          std::uint32_t action_id,
                                          const OpaqueActionPayload* payload) {
  Trace(CallKind::kExecuteAction, receiver, action_id, payload->points,
        payload);
  last_action_strategy = receiver;
  last_action_id = action_id;
  last_payload_address = payload;
  last_payload = *payload;
  Expect(payload->avatar == &avatar);
  Expect(payload->action_word == 0U);
}

void InstallPorts() {
  g_native_ports =
      NativePorts{GetNounManager,    GetProgressionPlayer, GetEventGate,
                  GetActionStrategy, TransitionAvatar,     GetAvatar,
                  ExecuteAction};
}

void ResetFixture() {
  manager_result = &manager;
  second_manager_result = &manager;
  player_result = &player;
  strategy_result = &strategy;
  strategy.transition_receiver = &avatar;
  event_gate_result = reinterpret_cast<const void*>(0x2000U);
  trace.clear();
  last_payload_address = nullptr;
  last_action_strategy = nullptr;
  last_action_id = 0;
  last_payload = OpaqueActionPayload{};
}

void SetGlobal(float value) { DAT_0169e398 = value; }

void SetPlayer(float value) {
  std::memcpy(player.bytes.data() + 0x10f0U, &value, sizeof(value));
}

float GetPlayer() {
  float value = 0.0F;
  std::memcpy(&value, player.bytes.data() + 0x10f0U, sizeof(value));
  return value;
}

void ExpectKinds(const CallKind* expected, std::size_t count) {
  Expect(trace.size() == count);
  const std::size_t checked = trace.size() < count ? trace.size() : count;
  for (std::size_t index = 0; index < checked; ++index) {
    Expect(trace[index].kind == expected[index]);
  }
}

void TestZeroBypass() {
  for (const float value : {0.0F, -0.0F}) {
    ResetFixture();
    SetGlobal(12.5F);
    SetPlayer(-7.25F);
    Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0(value);
    Expect(SameFloatBits(DAT_0169e398, 12.5F));
    Expect(SameFloatBits(GetPlayer(), -7.25F));
    Expect(trace.empty());
  }
}

void TestNaNPath() {
  ResetFixture();
  SetGlobal(1.0F);
  SetPlayer(2.0F);
  const float nan_value = std::numeric_limits<float>::quiet_NaN();
  Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0(nan_value);
  Expect(std::isnan(DAT_0169e398));
  Expect(std::isnan(GetPlayer()));
  const CallKind expected[] = {
      CallKind::kGetNounManager,   CallKind::kGetProgressionPlayer,
      CallKind::kGetEventGate,     CallKind::kGetActionStrategy,
      CallKind::kTransitionAvatar, CallKind::kGetNounManager,
      CallKind::kGetAvatar,        CallKind::kExecuteAction,
  };
  ExpectKinds(expected, sizeof(expected) / sizeof(expected[0]));
  Expect(std::isnan(last_payload.points));
}

void TestNegativeAndCapBoundary() {
  ResetFixture();
  Expect(SameFloatBits(DAT_01582e54, 10000.0F));
  SetGlobal(9999.0F);
  SetPlayer(-100.0F);
  Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0(2.0F);
  Expect(SameFloatBits(DAT_0169e398, 10000.0F));
  Expect(SameFloatBits(GetPlayer(), -98.0F));
  Expect(last_action_id == kAddEvolutionPointsActionId);

  ResetFixture();
  SetGlobal(10000.0F);
  SetPlayer(5.0F);
  Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0(-1.0F);
  Expect(SameFloatBits(DAT_0169e398, 9999.0F));
  Expect(SameFloatBits(GetPlayer(), 4.0F));
}

void TestEventGatingAndPayload() {
  ResetFixture();
  event_gate_result = event_gate_sentinel();
  SetGlobal(3.0F);
  SetPlayer(4.0F);
  Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0(2.0F);
  const CallKind gated[] = {CallKind::kGetNounManager,
                            CallKind::kGetProgressionPlayer,
                            CallKind::kGetEventGate};
  ExpectKinds(gated, sizeof(gated) / sizeof(gated[0]));
  Expect(last_payload_address == nullptr);

  ResetFixture();
  strategy_result = nullptr;
  SetGlobal(3.0F);
  SetPlayer(4.0F);
  Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0(2.0F);
  const CallKind no_strategy[] = {
      CallKind::kGetNounManager, CallKind::kGetProgressionPlayer,
      CallKind::kGetEventGate, CallKind::kGetActionStrategy};
  ExpectKinds(no_strategy, sizeof(no_strategy) / sizeof(no_strategy[0]));
  Expect(last_payload_address == nullptr);

  ResetFixture();
  SetGlobal(3.0F);
  SetPlayer(4.0F);
  Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0(2.0F);
  const CallKind active[] = {
      CallKind::kGetNounManager,   CallKind::kGetProgressionPlayer,
      CallKind::kGetEventGate,     CallKind::kGetActionStrategy,
      CallKind::kTransitionAvatar, CallKind::kGetNounManager,
      CallKind::kGetAvatar,        CallKind::kExecuteAction};
  ExpectKinds(active, sizeof(active) / sizeof(active[0]));
  Expect(last_action_strategy == &strategy);
  Expect(last_action_id == kAddEvolutionPointsActionId);
  Expect(trace[0].receiver == trace[5].receiver);
  Expect(last_payload_address != nullptr);
  Expect(last_payload.avatar == &avatar);
  Expect(last_payload.action_word == 0U);
  Expect(SameFloatBits(last_payload.points, 2.0F));
  Expect(trace[1].receiver == &manager);
  Expect(trace[4].receiver == &avatar);
  Expect(trace[6].receiver == &manager);
}

void TestAccessorIdentityAndLifetime() {
  g_native_ports = NativePorts{};
  trace.clear();
  OpaqueCreatureGameData* first = Simulator_cCreatureGameData_Get_00d2e340();
  OpaqueCreatureGameData* second = Simulator_cCreatureGameData_Get_00d2e340();
  Expect(first == second);
  Expect(trace.empty());
  {
    OpaqueCreatureGameData* local = Simulator_cCreatureGameData_Get_00d2e340();
    Expect(local == first);
  }
  Expect(Simulator_cCreatureGameData_Get_00d2e340() == first);
}

}

int main() {
  InstallPorts();
  TestZeroBypass();
  TestNaNPath();
  TestNegativeAndCapBoundary();
  TestEventGatingAndPayload();
  TestAccessorIdentityAndLifetime();
  return failures == 0 ? 0 : 1;
}
