#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#include "game_mode_wave8.hpp"

#if defined(_MSC_VER)
#define PKG_GAME_MODE_WAVE8_THISCALL __thiscall
#define PKG_GAME_MODE_WAVE8_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_GAME_MODE_WAVE8_THISCALL __attribute__((thiscall))
#define PKG_GAME_MODE_WAVE8_CDECL __attribute__((cdecl))
#else
#error "PKG-GAME-MODE-WAVE8 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_game_mode_wave8 {
namespace {

struct PairService4 {
  std::uint8_t prefix[4]{};
  OpaquePairServiceVtable* vtable = nullptr;
};

struct PairService8 {
  std::uint8_t prefix[8]{};
  OpaquePairServiceVtable* vtable = nullptr;
};

struct PairServiceC {
  std::uint8_t prefix[12]{};
  OpaquePairServiceVtable* vtable = nullptr;
};

static_assert(offsetof(PairService4, vtable) == 4, "service +4 layout");
static_assert(offsetof(PairService8, vtable) == 8, "service +8 layout");
static_assert(offsetof(PairServiceC, vtable) == 12, "service +12 layout");

struct Fixture {
  std::vector<const char*> trace;
  std::vector<TextRange> appended;
  std::vector<const char*> freed;
  OpaqueModeTransition transition{};
  OpaqueModeTransitionVtable transition_vtable{};
  std::array<OpaqueParticipant, 2> participants{};
  std::array<OpaqueParticipant*, 2> participant_ptrs{};
  std::array<OpaqueParticipantVtable, 2> participant_vtables{};
  OpaqueSimulationState state{};
  std::uint8_t context = 0U;
  OpaquePairServiceVtable pair_vtable{};
  PairService4 service_cf{};
  PairService8 service_d388{};
  PairService8 service_fd{};
  PairService8 service_d1{};
  PairServiceC service_cd{};
  OpaqueReturnService return_service{};
  OpaqueReturnServiceVtable return_vtable{};
  OpaqueService tail{};
  OpaqueService48 service_0067ddd0{};
  OpaqueService48Vtable service_0067ddd0_vtable{};
  OpaqueAppSystem app_system{};
  OpaqueAppSystemVtable app_vtable{};
  OpaqueRenderer renderer{};
  OpaqueRendererVtable renderer_vtable{};
  OpaqueRenderer viewer{};
  OpaqueSpeciesManager species_manager{};
  OpaqueRenderer* viewer_result = nullptr;
  bool renderer_query_result = true;
  std::size_t renderer_text_span = 0U;
  ModeWord strategy_mode = 0U;
  ModeWord telemetry_value = 0U;
  std::uint32_t tail_finalize_value = 0x12345678U;
  TextVector* transform_output = nullptr;
  const TextVector* transform_source = nullptr;
  TextVector* build_output = nullptr;
  const TextVector* build_source = nullptr;
  bool build_returns_labels = false;
};

Fixture* current_fixture = nullptr;
int failures = 0;

void check(bool condition) {
  if (!condition) {
    std::fprintf(stderr, "check failed at %s:%d\n", __FILE__, __LINE__);
    ++failures;
  }
}

bool trace_is(const char* actual, const char* expected) {
  return std::strcmp(actual, expected) == 0;
}

bool trace_contains(const char* expected) {
  for (const char* value : current_fixture->trace) {
    if (trace_is(value, expected)) {
      return true;
    }
  }
  return false;
}

void state_root() { current_fixture->trace.push_back("state-root"); }
OpaqueSimulationState* state_root_port() {
  state_root();
  return &current_fixture->state;
}

void* state_followup() {
  current_fixture->trace.push_back("state-followup");
  return &current_fixture->state;
}

void PKG_GAME_MODE_WAVE8_THISCALL state_followup_call(void* value) {
  static_cast<void>(value);
  current_fixture->trace.push_back("state-followup-call");
  check(value == &current_fixture->state);
}

void clear_transition() { current_fixture->trace.push_back("clear"); }

void PKG_GAME_MODE_WAVE8_THISCALL
strategy_transition(OpaqueModeTransition* receiver, ModeWord mode) {
  check(receiver == &current_fixture->transition);
  current_fixture->strategy_mode = mode;
  current_fixture->trace.push_back("strategy");
}

void* context_get() {
  current_fixture->trace.push_back("context-get");
  return &current_fixture->context;
}

bool PKG_GAME_MODE_WAVE8_THISCALL context_query(void* receiver, ModeWord key) {
  static_cast<void>(receiver);
  static_cast<void>(key);
  check(receiver == &current_fixture->context);
  check(key == 0x05b598f6U);
  current_fixture->trace.push_back("context-query");
  return false;
}

void PKG_GAME_MODE_WAVE8_THISCALL context_set(void* receiver, ModeWord key,
                                              std::uint8_t value) {
  static_cast<void>(receiver);
  static_cast<void>(key);
  static_cast<void>(value);
  check(receiver == &current_fixture->context);
  check(key == 0x05b598f6U);
  check(value == 1U);
  current_fixture->trace.push_back("context-set");
}

void pair_dispatch_33970(ModeWord first, ModeWord second) {
  check(first == kModeGalaxy || first == kModeCell);
  check(second == kModeCell || second == kModeGalaxy ||
        second == kModeEditorTarget || second == kNoMode);
  current_fixture->trace.push_back("pair-dispatch-33970");
}

void pair_dispatch_335d0(ModeWord first, ModeWord second) {
  check(first == kModeGalaxy || first == kModeCell);
  check(second == kModeCell || second == kModeCreature ||
        second == kModeTribe || second == kModeCivilisation ||
        second == kModeSpace || second == kModeScenario ||
        second == kModeGalaxy || second == kModeEditorTarget ||
        second == 0x01654c06U);
  current_fixture->trace.push_back("pair-dispatch-335d0");
}

OpaqueReturnService* return_service_get() {
  current_fixture->trace.push_back("return-get");
  return &current_fixture->return_service;
}

void* PKG_GAME_MODE_WAVE8_THISCALL
return_service_slot(OpaqueService* receiver) {
  static_cast<void>(receiver);
  check(receiver ==
        reinterpret_cast<OpaqueService*>(&current_fixture->return_service));
  current_fixture->trace.push_back("return-slot");
  return reinterpret_cast<void*>(0x100U);
}

void PKG_GAME_MODE_WAVE8_THISCALL context_reset(void* value) {
  static_cast<void>(value);
  check(value == reinterpret_cast<void*>(0xfcU));
  current_fixture->trace.push_back("context-reset");
}

void PKG_GAME_MODE_WAVE8_THISCALL context_finalize(void* value,
                                                   ModeWord argument) {
  static_cast<void>(value);
  static_cast<void>(argument);
  check(value == reinterpret_cast<void*>(0xfcU));
  check(argument == 0U);
  current_fixture->trace.push_back("context-finalize");
}

OpaqueService* service_cf_get() {
  current_fixture->trace.push_back("service-cf-get");
  return reinterpret_cast<OpaqueService*>(&current_fixture->service_cf);
}

OpaqueService* service_d388_get() {
  current_fixture->trace.push_back("service-d388-get");
  return reinterpret_cast<OpaqueService*>(&current_fixture->service_d388);
}

OpaqueService* service_cd_get() {
  current_fixture->trace.push_back("service-cd-get");
  return reinterpret_cast<OpaqueService*>(&current_fixture->service_cd);
}

OpaqueService* service_fd_get() {
  current_fixture->trace.push_back("service-fd-get");
  return reinterpret_cast<OpaqueService*>(&current_fixture->service_fd);
}

OpaqueService* service_d1_get() {
  current_fixture->trace.push_back("service-d1-get");
  return reinterpret_cast<OpaqueService*>(&current_fixture->service_d1);
}

void PKG_GAME_MODE_WAVE8_THISCALL service_pair_14(OpaqueService* receiver,
                                                  ModeWord first,
                                                  ModeWord second) {
  check(receiver != nullptr);
  check(first == kModeGalaxy || first == kModeCell);
  check(second == kModeCell || second == kNoMode);
  current_fixture->trace.push_back("service-pair-14");
}

void PKG_GAME_MODE_WAVE8_THISCALL service_pair_18(OpaqueService* receiver,
                                                  ModeWord first,
                                                  ModeWord second) {
  check(receiver != nullptr);
  check(first == kModeGalaxy || first == kModeCell);
  check(second == kModeCell || second == kModeCreature ||
        second == kModeTribe || second == kModeCivilisation ||
        second == kModeSpace || second == kModeScenario ||
        second == kModeGalaxy || second == kModeEditorTarget ||
        second == 0x01654c06U);
  current_fixture->trace.push_back("service-pair-18");
}

OpaqueService* tail_get() {
  current_fixture->trace.push_back("tail-get");
  return &current_fixture->tail;
}

bool PKG_GAME_MODE_WAVE8_THISCALL tail_configure(OpaqueService* receiver,
                                                 ModeWord value) {
  static_cast<void>(receiver);
  static_cast<void>(value);
  check(receiver == &current_fixture->tail);
  check(value == 0x1002U);
  current_fixture->trace.push_back("tail-configure");
  return true;
}

std::uint32_t PKG_GAME_MODE_WAVE8_THISCALL
tail_finalize(OpaqueService* receiver, ModeWord value) {
  static_cast<void>(receiver);
  static_cast<void>(value);
  check(receiver == &current_fixture->tail);
  check(value == 0U);
  current_fixture->trace.push_back("tail-finalize");
  return current_fixture->tail_finalize_value;
}

OpaqueService48* service_0067ddd0_get() {
  current_fixture->trace.push_back("service-0067ddd0");
  return &current_fixture->service_0067ddd0;
}

void PKG_GAME_MODE_WAVE8_THISCALL
service_0067ddd0_slot(OpaqueService* receiver) {
  static_cast<void>(receiver);
  check(receiver ==
        reinterpret_cast<OpaqueService*>(&current_fixture->service_0067ddd0));
  current_fixture->trace.push_back("service-0067ddd0-slot");
}

OpaqueAppSystem* app_system_get() {
  current_fixture->trace.push_back("app-system-get");
  return &current_fixture->app_system;
}

void PKG_GAME_MODE_WAVE8_THISCALL app_initialize(OpaqueAppSystem* receiver,
                                                 ModeWord first,
                                                 ModeWord second,
                                                 ModeWord third) {
  static_cast<void>(receiver);
  static_cast<void>(first);
  static_cast<void>(second);
  static_cast<void>(third);
  check(receiver == &current_fixture->app_system);
  check(first == 0x685f4afU);
  check(second == 0U);
  check(third == 0U);
  current_fixture->trace.push_back("app-initialize");
}

OpaqueService* telemetry_get() {
  current_fixture->trace.push_back("telemetry-get");
  return &current_fixture->tail;
}

void PKG_GAME_MODE_WAVE8_THISCALL telemetry_reset(OpaqueService* receiver,
                                                  ModeWord value) {
  check(receiver == &current_fixture->tail);
  current_fixture->telemetry_value = value;
  current_fixture->trace.push_back("telemetry-reset");
}

OpaqueRenderer* renderer_get() {
  current_fixture->trace.push_back("renderer-get");
  return &current_fixture->renderer;
}

OpaqueRenderer* PKG_GAME_MODE_WAVE8_THISCALL
renderer_set(OpaqueRenderer* receiver) {
  check(receiver == &current_fixture->renderer);
  current_fixture->trace.push_back("renderer-set");
  return current_fixture->viewer_result;
}

bool PKG_GAME_MODE_WAVE8_THISCALL renderer_query(OpaqueRenderer* receiver,
                                                 TextVector* value) {
  check(receiver == &current_fixture->viewer);
  check(value != nullptr);
  if (current_fixture->renderer_text_span != 0U) {
    value->end = value->begin + current_fixture->renderer_text_span;
  }
  current_fixture->trace.push_back("renderer-query");
  return current_fixture->renderer_query_result;
}

OpaqueSpeciesManager* species_get() {
  current_fixture->trace.push_back("species-get");
  return &current_fixture->species_manager;
}

void PKG_GAME_MODE_WAVE8_THISCALL
species_initialize(OpaqueSpeciesManager* receiver, TextVector* value) {
  static_cast<void>(receiver);
  static_cast<void>(value);
  check(receiver == &current_fixture->species_manager);
  check(value != nullptr);
  current_fixture->trace.push_back("species-initialize");
}

void PKG_GAME_MODE_WAVE8_THISCALL append_text(TextVector* vector,
                                              const char* begin,
                                              const char* end) {
  current_fixture->trace.push_back("append-text");
  current_fixture->appended.push_back({begin, end});
  if (begin != nullptr) {
    vector->begin = begin;
    vector->end = end;
    vector->capacity = end + 1;
  }
}

TextVector* transform_text(TextVector* output, const TextVector* input) {
  current_fixture->transform_output = output;
  current_fixture->transform_source = input;
  current_fixture->trace.push_back("transform-text");
  output->begin = input->begin;
  output->end = input->end;
  output->capacity = input->capacity;
  return output;
}

TextVector* build_text(TextVector* output, const TextVector* input,
                       const char* suffix) {
  current_fixture->build_output = output;
  current_fixture->build_source = input;
  static_cast<void>(suffix);
  static const char editor[] = "Editor";
  current_fixture->trace.push_back("build-text");
  output->begin = editor;
  output->end = editor + 6;
  output->capacity = output->end;
  return current_fixture->build_returns_labels ? const_cast<TextVector*>(input)
                                               : output;
}

void PKG_GAME_MODE_WAVE8_CDECL free_text(const char* value) {
  current_fixture->trace.push_back("free-text");
  current_fixture->freed.push_back(value);
}

void check_participant(OpaqueParticipant* receiver) {
  check(receiver == &current_fixture->participants[0] ||
        receiver == &current_fixture->participants[1]);
}

void PKG_GAME_MODE_WAVE8_THISCALL participant_transition_14(
    OpaqueParticipant* receiver, ModeWord first, ModeWord second) {
  check_participant(receiver);
  check(first == kModeGalaxy || first == kModeCell);
  check(second == kModeCell || second == kNoMode);
  current_fixture->trace.push_back("participant-14");
}

void PKG_GAME_MODE_WAVE8_THISCALL participant_transition_18(
    OpaqueParticipant* receiver, ModeWord first, ModeWord second) {
  check_participant(receiver);
  check(first == kModeGalaxy || first == kModeCell);
  check(second == kModeCell || second == kModeCreature ||
        second == kModeTribe || second == kModeCivilisation ||
        second == kModeSpace || second == kModeScenario ||
        second == kModeGalaxy || second == kModeEditorTarget ||
        second == 0x01654c06U);
  current_fixture->trace.push_back("participant-18");
}

void PKG_GAME_MODE_WAVE8_THISCALL
transition_44(OpaqueModeTransition* receiver) {
  static_cast<void>(receiver);
  check(receiver == &current_fixture->transition);
  current_fixture->trace.push_back("transition-44");
}

void PKG_GAME_MODE_WAVE8_THISCALL
transition_58(OpaqueModeTransition* receiver) {
  static_cast<void>(receiver);
  check(receiver == &current_fixture->transition);
  current_fixture->trace.push_back("transition-58");
}

void initialize(Fixture& fixture) {
  current_fixture = &fixture;
  fixture.trace.clear();
  fixture.appended.clear();
  fixture.freed.clear();
  fixture.transition = OpaqueModeTransition{};
  fixture.transition_vtable = OpaqueModeTransitionVtable{};
  fixture.participants = {};
  fixture.participant_ptrs = {};
  fixture.participant_vtables = {};
  for (std::size_t index = 0; index < fixture.participant_vtables.size();
       ++index) {
    fixture.participant_vtables[index].slot_14 = &participant_transition_14;
    fixture.participant_vtables[index].slot_18 = &participant_transition_18;
    fixture.participants[index].vtable = &fixture.participant_vtables[index];
    fixture.participant_ptrs[index] = &fixture.participants[index];
  }
  fixture.transition.vtable = &fixture.transition_vtable;
  fixture.transition.participants_begin =
      reinterpret_cast<std::uint8_t*>(fixture.participant_ptrs.data());
  fixture.transition.participants_end = reinterpret_cast<std::uint8_t*>(
      fixture.participant_ptrs.data() + fixture.participant_ptrs.size());
  fixture.transition.transition_flag_0c = 0xa5U;
  fixture.state = OpaqueSimulationState{};
  fixture.context = 0U;
  fixture.pair_vtable = OpaquePairServiceVtable{};
  fixture.pair_vtable.slot_04 = &service_pair_18;
  fixture.pair_vtable.slot_08 = &service_pair_18;
  fixture.pair_vtable.slot_0c = &service_pair_18;
  fixture.pair_vtable.slot_14 = &service_pair_14;
  fixture.pair_vtable.slot_18 = &service_pair_18;
  fixture.service_cf = PairService4{};
  fixture.service_cf.vtable = &fixture.pair_vtable;
  fixture.service_d388 = PairService8{};
  fixture.service_d388.vtable = &fixture.pair_vtable;
  fixture.service_fd = PairService8{};
  fixture.service_fd.vtable = &fixture.pair_vtable;
  fixture.service_d1 = PairService8{};
  fixture.service_d1.vtable = &fixture.pair_vtable;
  fixture.service_cd = PairServiceC{};
  fixture.service_cd.vtable = &fixture.pair_vtable;
  fixture.return_service = OpaqueReturnService{};
  fixture.return_vtable = OpaqueReturnServiceVtable{};
  fixture.return_vtable.slot_04 = &return_service_slot;
  fixture.return_service.vtable = &fixture.return_vtable;
  fixture.tail = OpaqueService{};
  fixture.service_0067ddd0 = OpaqueService48{};
  fixture.service_0067ddd0_vtable = OpaqueService48Vtable{};
  fixture.service_0067ddd0_vtable.slot_48 = &service_0067ddd0_slot;
  fixture.service_0067ddd0.vtable = &fixture.service_0067ddd0_vtable;
  fixture.app_system = OpaqueAppSystem{};
  fixture.app_vtable = OpaqueAppSystemVtable{};
  fixture.app_vtable.slot_14 = &app_initialize;
  fixture.app_system.vtable = &fixture.app_vtable;
  fixture.renderer = OpaqueRenderer{};
  fixture.renderer_vtable = OpaqueRendererVtable{};
  fixture.renderer_vtable.slot_2c = &renderer_set;
  fixture.renderer.vtable = &fixture.renderer_vtable;
  fixture.viewer = OpaqueRenderer{};
  fixture.species_manager = OpaqueSpeciesManager{};
  fixture.viewer_result = &fixture.viewer;
  fixture.renderer_query_result = true;
  fixture.renderer_text_span = 0U;
  fixture.strategy_mode = 0U;
  fixture.telemetry_value = 0U;
  fixture.tail_finalize_value = 0x12345678U;
  fixture.transform_output = nullptr;
  fixture.transform_source = nullptr;
  fixture.build_output = nullptr;
  fixture.build_source = nullptr;
  fixture.build_returns_labels = false;
  fixture.transition_vtable.slot_44 = &transition_44;
  fixture.transition_vtable.slot_58 = &transition_58;
  g_game_mode_wave8_globals = SimulatorGlobals{};
  g_game_mode_wave8_ports = TransitionPorts{};
  TransitionPorts& ports = g_game_mode_wave8_ports;
  ports.state_root_00b3d320 = &state_root_port;
  ports.state_followup_00b3d380 = &state_followup;
  ports.state_followup_call_00b31a90 = &state_followup_call;
  ports.clear_00b2fbe0 = &clear_transition;
  ports.strategy_00b5e3f0 = &strategy_transition;
  ports.context_get_00805070 = &context_get;
  ports.context_query_00810760 = &context_query;
  ports.context_set_00810660 = &context_set;
  ports.pair_dispatch_00b33970 = &pair_dispatch_33970;
  ports.pair_dispatch_00b335d0 = &pair_dispatch_335d0;
  ports.return_service_get_0067caa0 = &return_service_get;
  ports.context_reset_008153e0 = &context_reset;
  ports.context_finalize_00812d60 = &context_finalize;
  ports.pair_service_get_00d38840 = &service_d388_get;
  ports.pair_service_get_00cd40b0 = &service_cd_get;
  ports.pair_service_get_00cf74c0 = &service_cf_get;
  ports.pair_service_get_00fd9c60 = &service_fd_get;
  ports.pair_service_get_00d1bf00 = &service_d1_get;
  ports.tail_service_get_0067cab0 = &tail_get;
  ports.tail_configure_00801bb0 = &tail_configure;
  ports.tail_finalize_008017f0 = &tail_finalize;
  ports.service_get_0067ddd0 = &service_0067ddd0_get;
  ports.app_system_get_0067dcc0 = &app_system_get;
  ports.telemetry_service_get_0067de90 = &telemetry_get;
  ports.telemetry_reset_007ebce0 = &telemetry_reset;
  ports.renderer_get_0067dd10 = &renderer_get;
  ports.renderer_set_viewer_slot_2c = &renderer_set;
  ports.renderer_query_005805e0 = &renderer_query;
  ports.species_manager_get_00401090 = &species_get;
  ports.species_initialize_004df310 = &species_initialize;
  ports.append_text_00454cb0 = &append_text;
  ports.transform_text_0093c570 = &transform_text;
  ports.build_text_0091ba90 = &build_text;
  ports.free_text_00f47380 = &free_text;
}

void test_strategy_transition_order_and_writes() {
  Fixture fixture{};
  initialize(fixture);
  simulator_strategy_transition_00b5f040(&fixture.transition, kModeGalaxy,
                                         kModeCell);
  check(fixture.state.first_mode == kModeGalaxy);
  check(fixture.state.shared_state == kModeCell);
  check(fixture.state.transition_flag_28 == 0U);
  check(g_game_mode_wave8_globals.flag_01686af0 == 0U);
  check(fixture.transition.transition_flag_0c == 1U);
  check(fixture.strategy_mode == kModeCell);
  check(fixture.trace == (std::vector<const char*>{
                             "state-root",          "state-followup",
                             "state-followup-call", "strategy",
                             "context-get",         "context-query",
                             "context-set",         "pair-dispatch-33970",
                             "return-get",          "return-slot",
                             "context-reset",       "context-finalize",
                             "participant-14",      "participant-14",
                             "service-d388-get",    "service-pair-14",
                             "service-cd-get",      "service-pair-14",
                             "service-cf-get",      "service-pair-14",
                             "service-fd-get",      "service-pair-14",
                             "service-d1-get",      "service-pair-14",
                             "transition-44",       "tail-get",
                             "tail-finalize",
                         }));
}

void test_strategy_sentinel_clear() {
  Fixture fixture{};
  initialize(fixture);
  simulator_strategy_transition_00b5f040(&fixture.transition, kModeCell,
                                         kNoMode);
  check(fixture.state.first_mode == kModeCell);
  check(fixture.state.shared_state == kNoMode);
  check(fixture.transition.transition_flag_0c == 0xa5U);
  check(fixture.trace.size() > 3U);
  check(trace_is(fixture.trace[3], "clear"));
  check(trace_contains("pair-dispatch-33970"));
}

void test_mode_transition_order_and_reset() {
  Fixture fixture{};
  initialize(fixture);
  simulator_strategy_transition_00b5dbb0(&fixture.transition, kModeCell,
                                         kModeGalaxy);
  check(fixture.telemetry_value == kNoMode);
  check(fixture.trace ==
        (std::vector<const char*>{
            "service-0067ddd0",   "service-0067ddd0-slot", "app-system-get",
            "app-initialize",     "telemetry-get",         "telemetry-reset",
            "tail-get",           "tail-configure",        "tail-finalize",
            "service-d388-get",   "service-pair-18",       "service-cd-get",
            "service-pair-18",    "service-cf-get",        "service-pair-18",
            "service-fd-get",     "service-pair-18",       "service-d1-get",
            "service-pair-18",    "pair-dispatch-335d0",   "participant-18",
            "participant-18",     "append-text",           "species-get",
            "species-initialize", "transition-58",         "free-text",
        }));
  check(fixture.appended.size() == 1U);
  check(fixture.appended[0].begin ==
        reinterpret_cast<const char*>(0x0146288cU));
  check(fixture.appended[0].end == reinterpret_cast<const char*>(0x0146289bU));
}

void test_mode_transition_galaxy_source_does_not_reset() {
  Fixture fixture{};
  initialize(fixture);
  simulator_strategy_transition_00b5dbb0(&fixture.transition, kModeGalaxy,
                                         kModeCell);
  check(fixture.telemetry_value == 0U);
  check(fixture.appended.size() == 1U);
  check(fixture.appended[0].begin ==
        reinterpret_cast<const char*>(0x0145d940U));
  check(fixture.appended[0].end == reinterpret_cast<const char*>(0x0145d948U));
  check(trace_is(fixture.trace[fixture.trace.size() - 2U], "transition-58"));
  check(trace_is(fixture.trace.back(), "free-text"));
}

void test_mode_transition_editor_effect_is_separate() {
  Fixture fixture{};
  initialize(fixture);
  fixture.renderer_text_span = 4U;
  simulator_strategy_transition_00b5dbb0(&fixture.transition, kModeCell,
                                         kModeEditorTarget);
  check(fixture.trace == (std::vector<const char*>{
                             "service-0067ddd0", "service-0067ddd0-slot",
                             "app-system-get",   "app-initialize",
                             "tail-get",         "tail-configure",
                             "tail-finalize",    "service-d388-get",
                             "service-pair-18",  "service-cd-get",
                             "service-pair-18",  "service-cf-get",
                             "service-pair-18",  "service-fd-get",
                             "service-pair-18",  "service-d1-get",
                             "service-pair-18",  "pair-dispatch-335d0",
                             "participant-18",   "participant-18",
                             "renderer-get",     "renderer-set",
                             "renderer-query",   "transform-text",
                             "append-text",      "free-text",
                             "build-text",       "append-text",
                             "free-text",        "transition-58",
                             "free-text",
                         }));
  check(fixture.trace.size() == 31U);
  check(fixture.appended.size() == 2U);
  check(fixture.freed.size() == 3U);
  check(fixture.transform_output == fixture.build_output);
  check(fixture.transform_source != fixture.build_source);
}

void test_mode_transition_transform_guards_labels() {
  Fixture fixture{};
  initialize(fixture);
  fixture.build_returns_labels = true;
  simulator_strategy_transition_00b5dbb0(&fixture.transition, kModeCell,
                                         kModeEditorTarget);
  check(fixture.appended.size() == 1U);
  check(fixture.transform_output == fixture.build_output);
  check(fixture.transform_source != fixture.build_source);
  check(fixture.build_source != fixture.transform_output);
}

void test_mode_transition_label_end_addresses() {
  struct Expectation {
    ModeWord mode;
    const char* end;
  };
  const std::array<Expectation, 6> expectations{{
      {kModeCell, reinterpret_cast<const char*>(0x0145d948U)},
      {kModeCreature, reinterpret_cast<const char*>(0x0145d93cU)},
      {kModeTribe, reinterpret_cast<const char*>(0x0145d92dU)},
      {kModeCivilisation, reinterpret_cast<const char*>(0x0145d920U)},
      {kModeSpace, reinterpret_cast<const char*>(0x0145d90dU)},
      {kModeScenario, reinterpret_cast<const char*>(0x014628a8U)},
  }};
  for (const Expectation& expectation : expectations) {
    Fixture fixture{};
    initialize(fixture);
    simulator_strategy_transition_00b5dbb0(&fixture.transition, kModeGalaxy,
                                           expectation.mode);
    check(fixture.appended.size() == 1U);
    check(fixture.appended[0].end == expectation.end);
  }
}

void test_mode_transition_selector_six_has_no_effect() {
  Fixture fixture{};
  initialize(fixture);
  simulator_strategy_transition_00b5dbb0(&fixture.transition, kModeGalaxy,
                                         0x01654c06U);
  check(!trace_contains("append-text"));
  check(!trace_contains("free-text"));
  check(fixture.appended.empty());
  check(fixture.freed.empty());
}

int run_tests() {
  test_strategy_transition_order_and_writes();
  test_strategy_sentinel_clear();
  test_mode_transition_order_and_reset();
  test_mode_transition_galaxy_source_does_not_reset();
  test_mode_transition_editor_effect_is_separate();
  test_mode_transition_transform_guards_labels();
  test_mode_transition_label_end_addresses();
  test_mode_transition_selector_six_has_no_effect();
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_game_mode_wave8::run_tests();
}

#undef PKG_GAME_MODE_WAVE8_THISCALL
#undef PKG_GAME_MODE_WAVE8_CDECL
