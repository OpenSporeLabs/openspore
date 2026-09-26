#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <initializer_list>
#include <vector>

#include "frame_runtime_wave7.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_STDCALL __stdcall
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_STDCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_frame_runtime_wave7 {
namespace {

enum class Kind : std::uint8_t {
  cell_update,
  query_counter,
  read_target,
  pacing_gate,
  acquire_pacing,
  pacing_available,
  request_pacing,
  measure_elapsed,
  wait,
  get_app_system,
  service_38,
  direct_service,
  stage_20,
  stage_1c,
  stage_28,
  stage_0c,
  app_update_78,
  stage_18,
  app_post_7c,
  app_post_80,
};

struct Event {
  Kind kind = Kind::query_counter;
  const void* receiver = nullptr;
  OpaqueWord word = 0;
  std::int32_t signed_word = 0;
  float first_scalar = 0.0F;
  float second_scalar = 0.0F;
};

struct Fixture {
  OpaqueCellMode cell_mode{};
  OpaqueAppSystemVtable app_vtable{};
  OpaqueAppSystem app_system{};
  OpaquePacingVtable pacing_vtable{};
  OpaquePacingService pacing{};
  OpaqueFrameStageVtable stage_vtable_20{};
  OpaqueFrameStageVtable stage_vtable_1c{};
  OpaqueFrameStageVtable stage_vtable_28{};
  OpaqueFrameStageVtable stage_vtable_0c{};
  OpaqueFrameStageVtable stage_vtable_18{};
  OpaqueFrameStage stage_20{};
  OpaqueFrameStage stage_1c{};
  OpaqueFrameStage stage_28{};
  OpaqueFrameStage stage_0c{};
  OpaqueFrameStage stage_18{};
  OpaqueSporeApp owner{};
  FrameRuntimePorts ports{};
  std::vector<Event> events{};
  std::vector<std::int32_t> measure_values{};
  std::size_t measure_index = 0;
  std::uint64_t now = 0;
  std::int32_t pacing_target = 0;
  bool pacing_gate_enabled = false;
  bool pacing_service_available = false;
  OpaqueWord request_result = 0;
  std::int32_t direct_service_object = 0;
};

Fixture fixture;

void check(bool condition, const char* message) {
  static_cast<void>(message);
  if (!condition) {
    std::abort();
  }
}

Event& record(Kind kind) {
  fixture.events.push_back(Event{});
  Event& event = fixture.events.back();
  event.kind = kind;
  return event;
}

void cell_update(float first_word, float second_word) {
  Event& event = record(Kind::cell_update);
  event.first_scalar = first_word;
  event.second_scalar = second_word;
}

void query_counter(std::uint64_t* output) {
  Event& event = record(Kind::query_counter);
  event.receiver = output;
  *output = fixture.now;
}

std::int32_t TEST_THISCALL measure_elapsed(OpaqueSporeApp* owner) {
  Event& event = record(Kind::measure_elapsed);
  event.receiver = owner;
  std::int32_t result = 0;
  if (fixture.measure_index < fixture.measure_values.size()) {
    result = fixture.measure_values[fixture.measure_index];
    ++fixture.measure_index;
  }
  event.signed_word = result;
  return result;
}

std::int32_t read_pacing_target() {
  Event& event = record(Kind::read_target);
  event.signed_word = fixture.pacing_target;
  return fixture.pacing_target;
}

OpaquePacingService* acquire_pacing() {
  record(Kind::acquire_pacing);
  return &fixture.pacing;
}

bool TEST_THISCALL pacing_available(OpaquePacingService* service,
                                    std::int32_t selector) {
  Event& event = record(Kind::pacing_available);
  event.receiver = service;
  event.signed_word = selector;
  return fixture.pacing_service_available;
}

OpaqueWord TEST_THISCALL request_pacing(OpaqueAppSystem* service,
                                        OpaqueWord amount) {
  Event& event = record(Kind::request_pacing);
  event.receiver = service;
  event.word = amount;
  event.signed_word = static_cast<std::int32_t>(amount);
  return fixture.request_result;
}

void wait_milliseconds(const std::uint32_t* amount) {
  Event& event = record(Kind::wait);
  event.word = *amount;
  event.first_scalar = static_cast<float>(*amount);
}

OpaqueAppSystem* get_app_system() {
  record(Kind::get_app_system);
  return &fixture.app_system;
}

void TEST_THISCALL direct_service(void* receiver, std::int32_t delta) {
  Event& event = record(Kind::direct_service);
  event.receiver = receiver;
  event.signed_word = delta;
}

void TEST_THISCALL service_38(OpaqueAppSystem* service) {
  Event& event = record(Kind::service_38);
  event.receiver = service;
}

bool TEST_THISCALL pacing_gate(OpaqueAppSystem* service) {
  Event& event = record(Kind::pacing_gate);
  event.receiver = service;
  return fixture.pacing_gate_enabled;
}

void TEST_THISCALL app_update_78(OpaqueAppSystem* service, std::int32_t delta) {
  Event& event = record(Kind::app_update_78);
  event.receiver = service;
  event.signed_word = delta;
}

void TEST_THISCALL app_post_7c(OpaqueAppSystem* service) {
  Event& event = record(Kind::app_post_7c);
  event.receiver = service;
}

void TEST_THISCALL app_post_80(OpaqueAppSystem* service) {
  Event& event = record(Kind::app_post_80);
  event.receiver = service;
}

void TEST_THISCALL stage_20(OpaqueFrameStage* stage, std::int32_t delta) {
  Event& event = record(Kind::stage_20);
  event.receiver = stage;
  event.signed_word = delta;
}

void TEST_THISCALL stage_1c(OpaqueFrameStage* stage, std::int32_t delta) {
  Event& event = record(Kind::stage_1c);
  event.receiver = stage;
  event.signed_word = delta;
}

void TEST_THISCALL stage_28(OpaqueFrameStage* stage, std::int32_t delta) {
  Event& event = record(Kind::stage_28);
  event.receiver = stage;
  event.signed_word = delta;
}

void TEST_THISCALL stage_0c(OpaqueFrameStage* stage, std::int32_t delta) {
  Event& event = record(Kind::stage_0c);
  event.receiver = stage;
  event.signed_word = delta;
}

void TEST_THISCALL stage_18(OpaqueFrameStage* stage, float seconds) {
  Event& event = record(Kind::stage_18);
  event.receiver = stage;
  event.first_scalar = seconds;
}

void initialize() {
  fixture = Fixture{};
  fixture.app_vtable.service_38 = &service_38;
  fixture.app_vtable.pacing_enabled_44 = &pacing_gate;
  fixture.app_vtable.update_78 = &app_update_78;
  fixture.app_vtable.post_7c = &app_post_7c;
  fixture.app_vtable.post_80 = &app_post_80;
  fixture.app_vtable.request_pacing_84 = &request_pacing;
  fixture.app_system.vtable = &fixture.app_vtable;
  fixture.pacing_vtable.available_34 = &pacing_available;
  fixture.pacing.vtable = &fixture.pacing_vtable;
  fixture.stage_vtable_20.update_20 = &stage_20;
  fixture.stage_vtable_1c.update_1c = &stage_1c;
  fixture.stage_vtable_28.update_28 = &stage_28;
  fixture.stage_vtable_0c.update_0c = &stage_0c;
  fixture.stage_vtable_18.update_18 = &stage_18;
  fixture.stage_20.vtable = &fixture.stage_vtable_20;
  fixture.stage_1c.vtable = &fixture.stage_vtable_1c;
  fixture.stage_28.vtable = &fixture.stage_vtable_28;
  fixture.stage_0c.vtable = &fixture.stage_vtable_0c;
  fixture.stage_18.vtable = &fixture.stage_vtable_18;
  fixture.owner.active_0c = 1;
  fixture.owner.baseline_10 = 1000;
  fixture.owner.tick_to_ms_18 = 1.0F;
  fixture.owner.baseline_scale_1c = 1.0F;
  fixture.owner.app_system_20 = &fixture.app_system;
  fixture.owner.direct_service_28 = &fixture.direct_service_object;
  fixture.owner.float_stage_2c = &fixture.stage_18;
  fixture.owner.last_stage_30 = &fixture.stage_0c;
  fixture.owner.first_stage_34 = &fixture.stage_20;
  fixture.owner.middle_stage_38 = &fixture.stage_1c;
  fixture.owner.fourth_stage_3c = &fixture.stage_28;
  fixture.ports.cell_orchestrator_00e806b0 = &cell_update;
  fixture.ports.query_performance_counter = &query_counter;
  fixture.ports.measure_elapsed_00f475b0 = &measure_elapsed;
  fixture.ports.read_pacing_target = &read_pacing_target;
  fixture.ports.acquire_pacing_0068f4d0 = &acquire_pacing;
  fixture.ports.wait_milliseconds_00921df0 = &wait_milliseconds;
  fixture.ports.get_app_system_0067dcc0 = &get_app_system;
  fixture.ports.direct_service_00812d30 = &direct_service;
  g_frame_runtime_ports = &fixture.ports;
}

void expect_kinds(std::initializer_list<Kind> expected) {
  check(fixture.events.size() == expected.size(), "event count");
  std::size_t index = 0;
  for (Kind kind : expected) {
    check(fixture.events[index].kind == kind, "event order");
    ++index;
  }
}

const Event& event(Kind kind) {
  for (const Event& entry : fixture.events) {
    if (entry.kind == kind) {
      return entry;
    }
  }
  std::abort();
}

std::size_t count(Kind kind) {
  std::size_t result = 0;
  for (const Event& entry : fixture.events) {
    if (entry.kind == kind) {
      ++result;
    }
  }
  return result;
}

void test_inactive_frame() {
  initialize();
  fixture.owner.active_0c = 0;
  fixture.owner.baseline_10 = 0x123456789abcdef0ULL;
  app_frame_update_00f47930(&fixture.owner);
  check(fixture.events.empty(), "inactive frame has no events");
  check(fixture.owner.baseline_10 == 0x123456789abcdef0ULL,
        "inactive frame publication");
}

void test_callback_order_and_publication() {
  initialize();
  fixture.now = 1100;
  app_frame_update_00f47930(&fixture.owner);
  expect_kinds({Kind::query_counter, Kind::read_target, Kind::pacing_gate,
                Kind::get_app_system, Kind::service_38, Kind::direct_service,
                Kind::stage_20, Kind::stage_1c, Kind::stage_28, Kind::stage_0c,
                Kind::app_update_78, Kind::stage_18, Kind::app_post_7c});
  check(fixture.owner.baseline_10 == 1100, "baseline publication");
  check(event(Kind::query_counter).receiver != nullptr, "QPC output pointer");
  check(event(Kind::direct_service).receiver == fixture.owner.direct_service_28,
        "direct receiver");
  check(event(Kind::direct_service).signed_word == 100, "direct delta");
  check(event(Kind::stage_20).signed_word == 100, "stage 20 delta");
  check(event(Kind::stage_1c).signed_word == 100, "stage 1c delta");
  check(event(Kind::stage_28).signed_word == 100, "stage 28 delta");
  check(event(Kind::stage_0c).signed_word == 100, "stage 0c delta");
  check(event(Kind::app_update_78).signed_word == 100, "app update delta");
  check(std::fabs(event(Kind::stage_18).first_scalar - 0.1F) < 0.000001F,
        "seconds callback");
  check(count(Kind::app_update_78) == 1, "single update callback");
  check(count(Kind::app_post_80) == 0, "post update remains caller-owned");
}

void test_pacing_order() {
  initialize();
  fixture.now = 1100;
  fixture.owner.baseline_10 = 1090;
  fixture.pacing_target = 1;
  fixture.pacing_gate_enabled = true;
  fixture.pacing_service_available = true;
  fixture.measure_values = {20, 30};
  app_frame_update_00f47930(&fixture.owner);
  expect_kinds({Kind::query_counter, Kind::read_target, Kind::pacing_gate,
                Kind::acquire_pacing, Kind::pacing_available,
                Kind::request_pacing, Kind::measure_elapsed, Kind::wait,
                Kind::measure_elapsed, Kind::get_app_system, Kind::service_38,
                Kind::direct_service, Kind::stage_20, Kind::stage_1c,
                Kind::stage_28, Kind::stage_0c, Kind::app_update_78,
                Kind::stage_18, Kind::app_post_7c});
  check(event(Kind::pacing_available).signed_word == -1,
        "pacing availability selector");
  check(event(Kind::request_pacing).word == 34, "pacing request amount");
  check(event(Kind::wait).word == 25, "pacing wait DWORD");
  check(event(Kind::wait).first_scalar == 25.0F, "pacing wait amount");
  check(event(Kind::app_update_78).signed_word == 30, "paced update delta");
  check(fixture.owner.baseline_10 == 1120, "paced baseline publication");
}

void test_pacing_floor() {
  initialize();
  fixture.now = 1100;
  fixture.owner.baseline_10 = 1056;
  fixture.pacing_target = 1;
  fixture.pacing_gate_enabled = true;
  fixture.pacing_service_available = true;
  fixture.measure_values = {45, 47};
  app_frame_update_00f47930(&fixture.owner);
  check(event(Kind::request_pacing).word == 2, "three millisecond floor");
  check(event(Kind::wait).word == 2, "post-floor wait DWORD");
  check(event(Kind::wait).first_scalar == 2.0F, "post-floor wait");
  check(event(Kind::app_update_78).signed_word == 47, "floor final delta");
  check(fixture.owner.baseline_10 == 1103, "floor final publication");
}

void test_pacing_service_unavailable() {
  initialize();
  fixture.now = 1100;
  fixture.owner.baseline_10 = 1090;
  fixture.pacing_target = 20;
  fixture.pacing_gate_enabled = true;
  fixture.pacing_service_available = false;
  fixture.measure_values = {30};
  app_frame_update_00f47930(&fixture.owner);
  check(count(Kind::request_pacing) == 0, "unavailable service request count");
  check(event(Kind::wait).word == 35, "unavailable service wait DWORD");
  check(event(Kind::wait).first_scalar == 35.0F,
        "unavailable service common wait");
  check(event(Kind::app_update_78).signed_word == 30,
        "unavailable service final delta");
}

void test_x87_rounding_publication() {
  initialize();
  fixture.now = 1003;
  fixture.owner.baseline_scale_1c = 0.5F;
  app_frame_update_00f47930(&fixture.owner);
  check(fixture.owner.baseline_10 == 1002, "x87 nearest publication");
  check(event(Kind::app_update_78).signed_word == 3,
        "unrounded callback delta");
}

void test_optional_callback_nulls() {
  initialize();
  fixture.now = 1010;
  fixture.owner.direct_service_28 = nullptr;
  fixture.owner.float_stage_2c = nullptr;
  fixture.owner.last_stage_30 = nullptr;
  fixture.owner.first_stage_34 = nullptr;
  fixture.owner.middle_stage_38 = nullptr;
  fixture.owner.fourth_stage_3c = nullptr;
  app_frame_update_00f47930(&fixture.owner);
  expect_kinds({Kind::query_counter, Kind::read_target, Kind::pacing_gate,
                Kind::get_app_system, Kind::service_38, Kind::app_update_78,
                Kind::app_post_7c});
}

void test_cell_update_forwarding() {
  initialize();
  cell_mode_update_00e80980(&fixture.cell_mode, 1.25F, -0.0F);
  expect_kinds({Kind::cell_update});
  const Event& forwarded = fixture.events.front();
  check(forwarded.receiver == nullptr, "cell port has no receiver parameter");
  check(forwarded.first_scalar == 1.25F, "cell first word");
  check(std::signbit(forwarded.second_scalar), "cell second word sign");
}

void run() {
  test_inactive_frame();
  test_callback_order_and_publication();
  test_pacing_order();
  test_pacing_floor();
  test_pacing_service_unavailable();
  test_x87_rounding_publication();
  test_optional_callback_nulls();
  test_cell_update_forwarding();
}

}

}

int main() {
  openspore::reconstruction::pkg_frame_runtime_wave7::run();
  return 0;
}

#undef TEST_THISCALL
#undef TEST_STDCALL
