#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include "beam_tool_func5_01053e00.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_CDECL __cdecl
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_sim_beamtool_func5 {
namespace {

using ExpectedEntryAbi = bool(TEST_CDECL*)(OpaqueBeamToolState*, void*);
using ExpectedCommitAbi = void(TEST_THISCALL*)(OpaqueBeamTarget*,
                                               const OpaqueBeamToolState*);

static_assert(std::is_same<decltype(&func_01053e00), ExpectedEntryAbi>::value,
              "func_01053e00 takes the receiver plus one further stack word");
static_assert(std::is_same<decltype(&anchor_position_commit_00cb5930),
                           ExpectedCommitAbi>::value,
              "commit helper ABI");
static_assert(kEntryStackCleanupBytes == 8u, "entry pops two stack words");

int failures = 0;
std::vector<std::string> events;

TargetWord release_count = 0;
TargetWord set_position_count = 0;
TargetWord lookup_count = 0;
bool completion_query_result = false;
OpaqueFoundPosition* lookup_result = nullptr;
OpaqueAnchorProvider* provider_result = nullptr;
OpaqueVec3 emitter_seen{};
OpaqueVec3 provider_position{};
OpaqueVec3 fallback_position{};
OpaqueVec3 out_buffer_seen{};
OpaqueBeamTarget* released_target = nullptr;

OpaquePositionSourceVTable source_vtable{};
OpaqueAnchorProviderVTable provider_vtable{};
OpaqueFoundPositionVTable found_vtable{};
OpaqueFoundPosition found_object{};
OpaqueBeamTargetVTable target_vtable{};
OpaqueBeamEmitterVTable emitter_vtable{};
OpaqueAnchorVTable anchor_vtable{};

OpaquePositionSource source_object{};
OpaqueAnchorProvider provider_object{};
OpaqueBeamEmitter emitter_object{};
OpaqueAnchor anchor_object{};
OpaqueBeamTarget target_object{};
OpaqueBeamToolState tool_state{};
OpaqueVec3 found_position{};

const OpaqueVec3* TEST_THISCALL
source_position_pointer_2c(const OpaquePositionSource*) {
  events.push_back("source_position_2c");
  return &fallback_position;
}

const OpaqueVec3* TEST_THISCALL found_position_out_30(OpaqueFoundPosition*,
                                                      OpaqueVec3* out) {
  events.push_back("found_position_30");
  *out = out_buffer_seen;
  return &found_position;
}

const OpaqueVec3* TEST_THISCALL
provider_position_pointer_2c(OpaqueAnchorProvider* provider) {
  events.push_back("provider_position_2c");
  return provider == &provider_object ? &provider_position : &found_position;
}

OpaqueAnchorProvider* TEST_THISCALL anchor_provider_118(OpaqueAnchor*) {
  events.push_back("anchor_provider_118");
  return provider_result;
}

OpaqueFoundPosition* TEST_THISCALL source_lookup_b8(OpaquePositionSource*,
                                                    const std::uint32_t* key) {
  events.push_back("lookup_b8");
  ++lookup_count;
  if (key != kPositionServiceTable_013f94d4) {
    return nullptr;
  }
  return lookup_result;
}

void TEST_THISCALL target_release_04(OpaqueBeamTarget* target) {
  events.push_back("release_04");
  ++release_count;
  released_target = target;
}

bool TEST_THISCALL target_completion_query_2c(const OpaqueBeamTarget*) {
  events.push_back("completion_query_2c");
  return completion_query_result;
}

void TEST_THISCALL emitter_set_position_38(OpaqueBeamEmitter* emitter,
                                           const OpaqueVec3* position) {
  events.push_back("set_position_38");
  ++set_position_count;
  if (emitter == &emitter_object) {
    emitter_seen = *position;
  }
}

void reset_world() {
  std::memset(&tool_state, 0, sizeof(tool_state));
  std::memset(&target_object, 0, sizeof(target_object));
  std::memset(&emitter_object, 0, sizeof(emitter_object));
  std::memset(&anchor_object, 0, sizeof(anchor_object));
  std::memset(&provider_object, 0, sizeof(provider_object));
  std::memset(&found_object, 0, sizeof(found_object));
  std::memset(&source_object, 0, sizeof(source_object));
  std::memset(&emitter_seen, 0, sizeof(emitter_seen));
  std::memset(&found_position, 0, sizeof(found_position));
  std::memset(&provider_position, 0, sizeof(provider_position));
  std::memset(&fallback_position, 0, sizeof(fallback_position));
  std::memset(&out_buffer_seen, 0, sizeof(out_buffer_seen));

  emitter_vtable.set_position_38 = &emitter_set_position_38;
  anchor_vtable.provider_118 = &anchor_provider_118;
  provider_vtable.position_2c = &provider_position_pointer_2c;
  found_vtable.position_out_30 = &found_position_out_30;
  source_vtable.position_pointer_2c = &source_position_pointer_2c;
  source_vtable.lookup_by_table_b8 = &source_lookup_b8;
  target_vtable.release_04 = &target_release_04;
  target_vtable.completion_query_2c = &target_completion_query_2c;

  emitter_object.vtable_00 = &emitter_vtable;
  anchor_object.vtable_00 = &anchor_vtable;
  provider_object.vtable_00 = &provider_vtable;
  found_object.vtable_00 = &found_vtable;
  source_object.vtable_00 = &source_vtable;
  target_object.vtable_00 = &target_vtable;
  target_object.emitter_34 = &emitter_object;

  tool_state.position_source_114 = &source_object;
  tool_state.owned_beam_target_124 = &target_object;
  tool_state.gate_174 = 0x10u;

  completion_query_result = false;
  lookup_result = nullptr;
  provider_result = nullptr;
  release_count = 0u;
  set_position_count = 0u;
  lookup_count = 0u;
  released_target = nullptr;
  events.clear();
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
  {
    reset_world();
    tool_state.owned_beam_target_124 = nullptr;

    const bool result = beam_tool_func5_01053e00_model(&tool_state, nullptr);

    check(!result, "absent owned target returns false");
    check(events.empty(), "absent owned target performs no call at all");
  }

  {
    reset_world();
    completion_query_result = true;

    const bool result = beam_tool_func5_01053e00_model(&tool_state, nullptr);

    check(!result, "completed owned target returns false");
    check(release_count == 1u, "completed owned target is released once");
    check(released_target == &target_object,
          "release receives the owned target");
    check(tool_state.owned_beam_target_124 == nullptr,
          "owned target slot is nulled before the release");
    check(events.size() == 2u && events[0] == "completion_query_2c" &&
              events[1] == "release_04",
          "completed path stops at the release and never resolves a position");
    check(set_position_count == 0u, "completed path never touches the emitter");
  }

  {
    reset_world();
    completion_query_result = false;
    lookup_result = nullptr;
    fallback_position.x = 1.0f;
    fallback_position.y = 2.0f;
    fallback_position.z = 3.0f;

    const bool result = beam_tool_func5_01053e00_model(&tool_state, nullptr);

    check(result, "incomplete owned target returns true");
    check(lookup_count == 1u, "position source is queried once");
    check(events.size() == 4u && events[0] == "completion_query_2c" &&
              events[1] == "lookup_b8" && events[2] == "source_position_2c" &&
              events[3] == "set_position_38",
          "fallback order is query, lookup, source position, emit");
    check(emitter_seen.x == 1.0f && emitter_seen.y == 2.0f &&
              emitter_seen.z == 3.0f,
          "emitter receives the fallback position floats");
  }

  {
    reset_world();
    completion_query_result = false;
    lookup_result = &found_object;
    found_position.x = 7.0f;
    found_position.y = 8.0f;
    found_position.z = 9.0f;
    fallback_position.x = 100.0f;
    fallback_position.y = 200.0f;
    fallback_position.z = 300.0f;
    out_buffer_seen.x = -1.0f;
    out_buffer_seen.y = -2.0f;
    out_buffer_seen.z = -3.0f;

    const bool result = beam_tool_func5_01053e00_model(&tool_state, nullptr);

    check(result, "found provider path returns true");
    check(emitter_seen.x == 7.0f && emitter_seen.y == 8.0f &&
              emitter_seen.z == 9.0f,
          "the returned pointer wins over the out buffer and the fallback");
    check(events.size() == 4u && events[1] == "lookup_b8" &&
              events[2] == "found_position_30" &&
              events[3] == "set_position_38",
          "found path skips the source position fallback slot");
  }

  {
    reset_world();
    lookup_result = &found_object;
    found_position.x = 4.0f;
    found_position.y = 5.0f;
    found_position.z = 6.0f;
    tool_state.owned_beam_target_124 = &target_object;
    target_object.anchor_134 = &anchor_object;
    provider_result = &provider_object;
    provider_position.x = 40.0f;
    provider_position.y = 50.0f;
    provider_position.z = 60.0f;

    beam_tool_func5_01053e00_model(&tool_state, nullptr);

    check(target_object.anchor_position_13c.x == 40.0f &&
              target_object.anchor_position_13c.y == 50.0f &&
              target_object.anchor_position_13c.z == 60.0f,
          "commit writes the anchor provider position into the target");
    check(emitter_seen.x == 4.0f,
          "emitter position and anchor position are resolved separately");
  }

  {
    reset_world();
    lookup_result = &found_object;
    found_position.x = 11.0f;
    found_position.y = 12.0f;
    found_position.z = 13.0f;
    target_object.anchor_134 = &anchor_object;
    provider_result = nullptr;
    const OpaqueVec3 passed{11.0f, 12.0f, 13.0f};
    std::memcpy(&tool_state, &passed, sizeof(passed));
    tool_state.position_source_114 = &source_object;
    tool_state.owned_beam_target_124 = &target_object;

    beam_tool_func5_01053e00_model(&tool_state, nullptr);

    check(target_object.anchor_position_13c.x == 11.0f &&
              target_object.anchor_position_13c.y == 12.0f &&
              target_object.anchor_position_13c.z == 13.0f,
          "a null anchor provider makes the commit copy the passed pointer");
  }

  {
    reset_world();
    lookup_result = &found_object;
    found_position.x = 21.0f;
    found_position.y = 22.0f;
    found_position.z = 23.0f;
    target_object.anchor_134 = nullptr;
    const OpaqueVec3 passed{21.0f, 22.0f, 23.0f};
    std::memcpy(&tool_state, &passed, sizeof(passed));
    tool_state.position_source_114 = &source_object;
    tool_state.owned_beam_target_124 = &target_object;

    beam_tool_func5_01053e00_model(&tool_state, nullptr);

    check(target_object.anchor_position_13c.x == 21.0f &&
              target_object.anchor_position_13c.y == 22.0f &&
              target_object.anchor_position_13c.z == 23.0f,
          "a null anchor skips the resolver and copies the passed pointer");
    check(events.size() == 4u, "a null anchor performs no resolver call");
  }

  {
    reset_world();
    lookup_result = &found_object;
    found_position.x = 31.0f;
    found_position.y = 32.0f;
    found_position.z = 33.0f;
    beam_tool_func5_01053e00_model(&tool_state, nullptr);
    found_position.x = -5.0f;

    check(emitter_seen.x == 31.0f,
          "the emitter argument is a copy taken before the commit call");
  }

  {
    reset_world();
    lookup_result = &found_object;
    found_position.x = 41.0f;
    out_buffer_seen.x = 0.0f;
    out_buffer_seen.y = 0.0f;
    out_buffer_seen.z = 0.0f;

    beam_tool_func5_01053e00_model(&tool_state, nullptr);

    check(emitter_seen.x == 41.0f,
          "a zeroed out buffer does not influence the consumed position");
  }

  if (failures != 0) {
    std::printf("%d failure(s)\n", failures);
    return 1;
  }
  std::printf("all func_01053e00 model checks passed\n");
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_sim_beamtool_func5::run_tests();
}

#undef TEST_THISCALL
#undef TEST_CDECL
