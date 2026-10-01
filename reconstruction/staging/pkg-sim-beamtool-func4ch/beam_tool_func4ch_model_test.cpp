#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include "beam_tool_func4ch.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_CDECL __cdecl
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_sim_beamtool_func4ch {
namespace {

using ExpectedFunc4ChAbi = bool(TEST_CDECL*)(OpaqueBeamToolState*);
using ExpectedReleaseAbi = void(TEST_THISCALL*)(OpaqueBeamTarget*);
using ExpectedDrainAbi = void(TEST_THISCALL*)(OpaqueRelationshipState*);

static_assert(
    std::is_same<decltype(&func4_ch_01053db0), ExpectedFunc4ChAbi>::value,
    "func4Ch receives this as its single callee-popped stack argument");
static_assert(std::is_same<decltype(OpaqueBeamTargetVTable::release_04),
                           ExpectedReleaseAbi>::value,
              "beam target release slot ABI");
static_assert(sizeof(decltype(&func4_ch_01053db0)) == 4,
              "func4Ch pointer width");
static_assert(sizeof(decltype(&OpaqueBeamTargetVTable::release_04)) == 4,
              "beam target release pointer width");

int failures = 0;
std::vector<std::string> events;
TargetWord release_count = 0;

void TEST_THISCALL record_release(OpaqueBeamTarget*) {
  ++release_count;
  events.push_back("release");
}

void TEST_THISCALL record_drain(OpaqueRelationshipState*) {
  events.push_back("drain");
}

OpaqueBeamTargetVTable beam_vtable{};
OpaqueRelationshipState relationship{};

OpaqueBeamToolState make_tool_state(OpaqueBeamTarget* beam_target,
                                    TargetWord gate) {
  OpaqueBeamToolState state{};
  std::memset(&state, 0, sizeof(state));
  state.owned_beam_target_124 = beam_target;
  state.gate_174 = gate;
  return state;
}

OpaqueBeamTarget make_beam_target() {
  OpaqueBeamTarget target{};
  std::memset(&target, 0, sizeof(target));
  return target;
}

void reset_relationship() {
  std::memset(&relationship, 0, sizeof(relationship));
  relationship.state_20 = 0xffffffffu;
  relationship.event_55a0 = 0x1234u;
}

void check(bool condition, const std::string& label) {
  if (!condition) {
    ++failures;
    std::printf("FAIL %s\n", label.c_str());
  } else {
    std::printf("ok   %s\n", label.c_str());
  }
}

}

int run_tests() {
  beam_vtable.slots_00[0] = nullptr;
  beam_vtable.release_04 = &record_release;
  g_beam_tool_func4ch_ports.relationship_event_drain_00b77aa0 = &record_drain;
  g_relationship_state_0167eb14 = &relationship;

  {
    OpaqueBeamTarget target = make_beam_target();
    target.vtable_00 = &beam_vtable;
    OpaqueBeamToolState state = make_tool_state(&target, 0u);
    reset_relationship();
    events.clear();
    release_count = 0u;

    const bool result = beam_tool_func4_ch_model(&state);

    check(result, "absent-gate path still returns true");
    check(state.owned_beam_target_124 == nullptr,
          "owned beam target slot is nulled before release");
    check(release_count == 1u, "virtual release slot 0x04 is invoked once");
    check(target.state_155 == 1u, "beam target state byte 0x155 is set to 1");
    check(events.size() == 1u && events[0] == "release",
          "gate clear performs only the release call");
    check(relationship.state_20 == 0xffffffffu,
          "gate clear leaves relationship word 0x20 untouched");
    check(relationship.event_55a0 == 0x1234u,
          "gate clear leaves relationship word 0x55a0 untouched");
  }

  {
    OpaqueBeamTarget target = make_beam_target();
    target.vtable_00 = &beam_vtable;
    OpaqueBeamToolState state = make_tool_state(&target, 0x10u);
    reset_relationship();
    events.clear();
    release_count = 0u;

    const bool result = beam_tool_func4_ch_model(&state);

    check(result, "gate set path returns true");
    check(events.size() == 2u && events[0] == "release" && events[1] == "drain",
          "gate set emits release then the relationship drain");
    check(relationship.state_20 == 0xfffffffbu,
          "gate set clears bit 2 of relationship word 0x20");
    check(relationship.event_55a0 == 0u,
          "gate set zeroes relationship word 0x55a0");
  }

  {
    OpaqueBeamTarget target = make_beam_target();
    target.vtable_00 = &beam_vtable;
    OpaqueBeamToolState state = make_tool_state(&target, 0x01u);
    reset_relationship();
    events.clear();
    release_count = 0u;

    beam_tool_func4_ch_model(&state);

    check(release_count == 1u, "gate mask ignores bit 0 of the gate word");
    check(relationship.state_20 == 0xffffffffu,
          "gate mask rejects a word with only bit 0 set");
  }

  {
    OpaqueBeamTarget target = make_beam_target();
    target.vtable_00 = &beam_vtable;
    OpaqueBeamToolState state = make_tool_state(&target, 0x100u);
    reset_relationship();
    events.clear();
    release_count = 0u;

    beam_tool_func4_ch_model(&state);

    check(release_count == 1u, "gate mask ignores bit 8 of the gate word");
    check(relationship.state_20 == 0xffffffffu,
          "gate mask rejects a word with only bit 8 set");
  }

  {
    OpaqueBeamToolState state = make_tool_state(nullptr, 0x10u);
    reset_relationship();
    events.clear();
    release_count = 0u;

    const bool result = beam_tool_func4_ch_model(&state);

    check(result, "null owned beam target still returns true");
    check(release_count == 0u,
          "null owned beam target suppresses mark and release");
    check(events.size() == 1u && events[0] == "drain",
          "null beam target still runs the gate-set relationship drain");
    check(relationship.state_20 == 0xfffffffbu,
          "null beam target still clears relationship bit 2");
  }

  {
    OpaqueBeamToolState state = make_tool_state(nullptr, 0u);
    reset_relationship();
    events.clear();
    release_count = 0u;

    const bool result = beam_tool_func4_ch_model(&state);

    check(result, "fully inert path returns true");
    check(release_count == 0u, "fully inert path performs no release");
    check(events.empty(), "fully inert path performs no drain");
    check(relationship.state_20 == 0xffffffffu,
          "fully inert path leaves relationship word 0x20 untouched");
  }

  {
    OpaqueBeamToolState gate_clear = make_tool_state(nullptr, 0x20u);
    OpaqueBeamToolState gate_set = make_tool_state(nullptr, 0x1f0u);
    check(!beam_tool_gate_0104cd50(&gate_clear),
          "gate probes only bit 4 of the word at 0x174");
    check(beam_tool_gate_0104cd50(&gate_set),
          "gate accepts bit 4 regardless of the other bits");
  }

  if (failures != 0) {
    std::printf("%d failure(s)\n", failures);
    return 1;
  }
  std::printf("all func4_ch_01053db0 model checks passed\n");
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_sim_beamtool_func4ch::run_tests();
}

#undef TEST_THISCALL
#undef TEST_CDECL
