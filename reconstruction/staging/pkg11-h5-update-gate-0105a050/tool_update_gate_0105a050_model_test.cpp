#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "tool_update_gate_0105a050.hpp"

#if defined(_MSC_VER)
#define PKG11H5_THISCALL __thiscall
#define PKG11H5_CDECL __cdecl
#else
#define PKG11H5_THISCALL __attribute__((thiscall))
#define PKG11H5_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg11_h5_update_gate_0105a050 {
namespace {

struct alignas(4) RootSentinel {
  std::uint32_t word;
};

struct Counters {
  int mode_update;
  int active_time;
  int subject_live;
  int tool_gate;
  int trail_ends;
  int root_accessor;
  int axis_snap;
};

struct Recorder {
  Counters calls{};
  OpaqueToolState* mode_receiver = nullptr;
  TargetWord mode_arg1 = 0xffffffffu;
  TargetWord mode_arg2 = 0xffffffffu;
  TargetWord mode_arg3 = 0xffffffffu;
  OpaqueToolSubject* trail_subject = nullptr;
  Float3* trail_first = nullptr;
  Float3* trail_last = nullptr;
  OpaqueAxisSnapRoot* snapped_root = nullptr;
  Float3* snapped = nullptr;
  float snapped_value = 0.0f;
  bool mode_result = true;
  bool subject_live_result = true;
  bool tool_gate_result = true;
  float active_time_value = 1.0f;
};

Recorder g_recorder;
RootSentinel g_root{0x13572468u};

void check(bool condition) {
  if (!condition) {
    std::_Exit(1);
  }
}

#define CHECK(expression)                 \
  do {                                    \
    check(static_cast<bool>(expression)); \
  } while (false)

bool PKG11H5_CDECL stub_mode_update_010593e0(OpaqueToolState* tool_state,
                                            TargetWord mode_word,
                                            TargetWord selector,
                                            TargetWord unused_slot) {
  g_recorder.calls.mode_update += 1;
  g_recorder.mode_receiver = tool_state;
  g_recorder.mode_arg1 = mode_word;
  g_recorder.mode_arg2 = selector;
  g_recorder.mode_arg3 = unused_slot;
  return g_recorder.mode_result;
}

float PKG11H5_THISCALL stub_active_time_0104bdb0(OpaqueToolState*) {
  g_recorder.calls.active_time += 1;
  return g_recorder.active_time_value;
}

bool PKG11H5_THISCALL stub_subject_live_00cb5ba0(OpaqueToolSubject*) {
  g_recorder.calls.subject_live += 1;
  return g_recorder.subject_live_result;
}

bool PKG11H5_THISCALL stub_tool_gate_0104cd40(OpaqueToolState*) {
  g_recorder.calls.tool_gate += 1;
  return g_recorder.tool_gate_result;
}

void PKG11H5_THISCALL stub_subject_trail_ends_00cb8ba0(
    OpaqueToolSubject* subject, Float3* first, Float3* last) {
  g_recorder.calls.trail_ends += 1;
  g_recorder.trail_subject = subject;
  g_recorder.trail_first = first;
  g_recorder.trail_last = last;
  first->x = 1.0f;
  first->y = 2.0f;
  first->z = 3.0f;
  last->x = 4.0f;
  last->y = 5.0f;
  last->z = 6.0f;
}

OpaqueAxisSnapRoot* PKG11H5_CDECL stub_root_accessor_00b3d430() {
  g_recorder.calls.root_accessor += 1;
  return reinterpret_cast<OpaqueAxisSnapRoot*>(&g_root);
}

void PKG11H5_THISCALL stub_axis_snap_00bbec40(OpaqueAxisSnapRoot* root,
                                              Float3* direction, float reach) {
  g_recorder.calls.axis_snap += 1;
  g_recorder.snapped_root = root;
  g_recorder.snapped = direction;
  g_recorder.snapped_value = reach;
}

void install_ports() {
  g_tool_update_gate_0105a050_ports.mode_update_010593e0 =
      stub_mode_update_010593e0;
  g_tool_update_gate_0105a050_ports.active_time_0104bdb0 =
      stub_active_time_0104bdb0;
  g_tool_update_gate_0105a050_ports.subject_live_00cb5ba0 =
      stub_subject_live_00cb5ba0;
  g_tool_update_gate_0105a050_ports.tool_gate_0104cd40 = stub_tool_gate_0104cd40;
  g_tool_update_gate_0105a050_ports.subject_trail_ends_00cb8ba0 =
      stub_subject_trail_ends_00cb8ba0;
  g_tool_update_gate_0105a050_ports.root_accessor_00b3d430 =
      stub_root_accessor_00b3d430;
  g_tool_update_gate_0105a050_ports.axis_snap_00bbec40 = stub_axis_snap_00bbec40;
  g_recorder = Recorder{};
}

struct alignas(4) SubjectFixture {
  std::uint32_t prefix;
  OpaqueToolSubject subject;
  std::uint32_t suffix;
};

struct alignas(4) ToolFixture {
  std::uint32_t prefix;
  OpaqueToolState state;
  SubjectFixture owned;
  std::uint32_t suffix;
};

void fill_subject(SubjectFixture& fixture) {
  fixture.prefix = 0xa5a5a5a5u;
  fixture.suffix = 0x5a5a5a5au;
  for (std::size_t index = 0; index < sizeof(fixture.subject.opaque_000);
       ++index) {
    fixture.subject.opaque_000[index] = static_cast<std::uint8_t>(index * 7u);
  }
  fixture.subject.flag_16c = 0u;
  fixture.subject.flag_16d = 0u;
  for (std::size_t index = 0; index < sizeof(fixture.subject.opaque_16e);
       ++index) {
    fixture.subject.opaque_16e[index] =
        static_cast<std::uint8_t>(index * 11u + 3u);
  }
  fixture.subject.state_word_1e0 = 0u;
}

void fill_tool(ToolFixture& fixture) {
  fixture.prefix = 0x12345678u;
  fixture.suffix = 0x87654321u;
  for (std::size_t index = 0; index < sizeof(fixture.state.opaque_000);
       ++index) {
    fixture.state.opaque_000[index] = static_cast<std::uint8_t>(index * 5u + 1u);
  }
  for (std::size_t index = 0; index < sizeof(fixture.state.opaque_128);
       ++index) {
    fixture.state.opaque_128[index] = static_cast<std::uint8_t>(index * 3u + 2u);
  }
  for (std::size_t index = 0; index < sizeof(fixture.state.opaque_178);
       ++index) {
    fixture.state.opaque_178[index] = static_cast<std::uint8_t>(index * 13u);
  }
  fixture.state.gate_word_174 = 0xffffffffu;
  fixture.state.active_time_1ac = 1.0f;
  fill_subject(fixture.owned);
  fixture.state.owned_subject_124 = &fixture.owned.subject;
}

bool run_gate(ToolFixture& fixture) {
  return func_0105a050(&fixture.state, 0x11u, 0x22u, 0x33u);
}

void test_false_mode_update_short_circuits() {
  ToolFixture fixture{};
  fill_tool(fixture);
  install_ports();
  g_recorder.mode_result = false;
  const ToolFixture before = fixture;

  CHECK(run_gate(fixture) == false);

  CHECK(g_recorder.calls.mode_update == 1);
  CHECK(g_recorder.calls.active_time == 0);
  CHECK(g_recorder.calls.subject_live == 0);
  CHECK(g_recorder.calls.tool_gate == 0);
  CHECK(g_recorder.calls.trail_ends == 0);
  CHECK(g_recorder.calls.root_accessor == 0);
  CHECK(g_recorder.calls.axis_snap == 0);
  CHECK(g_recorder.mode_receiver == &fixture.state);
  CHECK(g_recorder.mode_arg1 == 0x11u);
  CHECK(g_recorder.mode_arg2 == 0x22u);
  CHECK(g_recorder.mode_arg3 == 0u);
  CHECK(std::memcmp(&fixture, &before, sizeof(fixture)) == 0);
}

void test_non_positive_active_time_stops_after_time_read() {
  const float values[] = {0.0f, -0.0f, -1.0f};
  for (float value : values) {
    ToolFixture fixture{};
    fill_tool(fixture);
    install_ports();
    g_recorder.active_time_value = value;
    const ToolFixture before = fixture;

    CHECK(run_gate(fixture) == true);

    CHECK(g_recorder.calls.mode_update == 1);
    CHECK(g_recorder.calls.active_time == 1);
    CHECK(g_recorder.calls.subject_live == 0);
    CHECK(g_recorder.calls.tool_gate == 0);
    CHECK(g_recorder.calls.trail_ends == 0);
    CHECK(g_recorder.calls.axis_snap == 0);
    CHECK(std::memcmp(&fixture, &before, sizeof(fixture)) == 0);
  }
}

void test_null_subject_stops_before_subject_live() {
  ToolFixture fixture{};
  fill_tool(fixture);
  install_ports();
  fixture.state.owned_subject_124 = nullptr;

  CHECK(run_gate(fixture) == true);

  CHECK(g_recorder.calls.active_time == 1);
  CHECK(g_recorder.calls.subject_live == 0);
  CHECK(g_recorder.calls.tool_gate == 0);
  CHECK(g_recorder.calls.trail_ends == 0);
  CHECK(g_recorder.calls.axis_snap == 0);
}

void test_quiet_subject_stops_before_gate() {
  ToolFixture fixture{};
  fill_tool(fixture);
  install_ports();
  g_recorder.subject_live_result = false;

  CHECK(run_gate(fixture) == true);

  CHECK(g_recorder.calls.subject_live == 1);
  CHECK(g_recorder.calls.tool_gate == 0);
  CHECK(g_recorder.calls.trail_ends == 0);
  CHECK(g_recorder.calls.axis_snap == 0);
}

void test_each_subject_flag_alone_opens_the_gate() {
  for (int flag = 0; flag < 2; ++flag) {
    ToolFixture fixture{};
    fill_tool(fixture);
    install_ports();
    g_recorder.subject_live_result = false;
    g_recorder.tool_gate_result = false;
    if (flag == 0) {
      fixture.owned.subject.flag_16c = 1u;
    } else {
      fixture.owned.subject.flag_16d = 1u;
    }

    CHECK(run_gate(fixture) == true);

    CHECK(g_recorder.calls.subject_live == 1);
    CHECK(g_recorder.calls.tool_gate == 1);
    CHECK(g_recorder.calls.trail_ends == 0);
    CHECK(g_recorder.calls.axis_snap == 0);
  }
}

void test_closed_tool_gate_stops_before_trail() {
  ToolFixture fixture{};
  fill_tool(fixture);
  install_ports();
  g_recorder.tool_gate_result = false;

  CHECK(run_gate(fixture) == true);

  CHECK(g_recorder.calls.tool_gate == 1);
  CHECK(g_recorder.calls.trail_ends == 0);
  CHECK(g_recorder.calls.root_accessor == 0);
  CHECK(g_recorder.calls.axis_snap == 0);
}

void test_open_gate_forwards_last_trail_point_and_reach() {
  ToolFixture fixture{};
  fill_tool(fixture);
  install_ports();
  g_recorder.active_time_value = 2.5f;
  const ToolFixture before = fixture;

  CHECK(run_gate(fixture) == true);

  CHECK(g_recorder.calls.mode_update == 1);
  CHECK(g_recorder.calls.active_time == 2);
  CHECK(g_recorder.calls.subject_live == 1);
  CHECK(g_recorder.calls.tool_gate == 1);
  CHECK(g_recorder.calls.trail_ends == 1);
  CHECK(g_recorder.calls.root_accessor == 1);
  CHECK(g_recorder.calls.axis_snap == 1);
  CHECK(g_recorder.snapped_root ==
        reinterpret_cast<OpaqueAxisSnapRoot*>(&g_root));
  CHECK(g_recorder.trail_subject == &fixture.owned.subject);
  CHECK(g_recorder.trail_first != g_recorder.trail_last);
  CHECK(g_recorder.snapped == g_recorder.trail_last);
  CHECK(g_recorder.snapped != g_recorder.trail_first);
  CHECK(g_recorder.snapped->x == 4.0f);
  CHECK(g_recorder.snapped->y == 5.0f);
  CHECK(g_recorder.snapped->z == 6.0f);
  CHECK(g_recorder.snapped_value == 2.5f);
  CHECK(std::memcmp(&fixture, &before, sizeof(fixture)) == 0);
}

void test_null_receiver_is_not_special_cased() {
  install_ports();
  g_recorder.mode_result = false;

  CHECK(func_0105a050(nullptr, 1u, 2u, 3u) == false);
  CHECK(g_recorder.mode_receiver == nullptr);
  CHECK(g_recorder.calls.mode_update == 1);
  CHECK(g_recorder.calls.active_time == 0);
}

void test_model_wrapper_matches_entry() {
  ToolFixture fixture{};
  fill_tool(fixture);
  install_ports();
  g_recorder.tool_gate_result = false;

  CHECK(tool_update_gate_0105a050_model(&fixture.state, 4u, 5u, 6u) == true);
  CHECK(g_recorder.mode_arg1 == 4u);
  CHECK(g_recorder.mode_arg2 == 5u);
  CHECK(g_recorder.mode_arg3 == 0u);
  CHECK(g_recorder.calls.mode_update == 1);
}

}

}

int main() {
  namespace ns = openspore::reconstruction::pkg11_h5_update_gate_0105a050;
  ns::test_false_mode_update_short_circuits();
  ns::test_non_positive_active_time_stops_after_time_read();
  ns::test_null_subject_stops_before_subject_live();
  ns::test_quiet_subject_stops_before_gate();
  ns::test_each_subject_flag_alone_opens_the_gate();
  ns::test_closed_tool_gate_stops_before_trail();
  ns::test_open_gate_forwards_last_trail_point_and_reach();
  ns::test_null_receiver_is_not_special_cased();
  ns::test_model_wrapper_matches_entry();
}
