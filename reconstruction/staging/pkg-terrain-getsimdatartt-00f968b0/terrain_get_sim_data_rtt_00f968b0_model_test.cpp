// Focused semantic test for get_sim_data_rtt_00f968b0.
//
// It drives the reconstruction through a synthetic provider whose +0x58 slot is
// replaced by a recorder, and asserts exactly the four behaviours the machine at
// 0x00f968b0..0x00f968ff can produce:
//
//   1. both queries return &receiver->anchor_04  -> EAX = 1
//   2. the first query does not                  -> EAX = 0, the second query
//                                                   is never issued
//   3. the first matches and the second does not -> EAX = 0
//   4. the receiver is NULL, so the anchor is 0  -> both queries must answer
//                                                   NULL for EAX = 1
//
// plus the call-order / call-count facts: ids 0x8 then 0x7, one call each, and
// the receiver handed to the slot is the provider, not the terrain sphere.
//
// Build (x86-32, matching the target):
//   g++ -m32 -std=c++17 -Wall -Wextra -Werror -I<staging dir>
//       terrain_get_sim_data_rtt_00f968b0.cpp
//       terrain_get_sim_data_rtt_00f968b0_model_test.cpp -o rtt_test

#include "terrain_get_sim_data_rtt_00f968b0.hpp"

#include <cstdio>
#include <cstdlib>
#include <vector>

namespace gsdr = openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0;

namespace {

struct CallRecord {
  std::uint32_t selector_id;
  gsdr::OpaqueRttData* anchor;
  gsdr::OpaqueSelectorProvider* receiver;
};

// Scripted answers for the +0x58 slot: one per call, in order.
struct ProviderScript {
  std::vector<CallRecord> calls;
  std::vector<gsdr::OpaqueRttData*> answers;
  std::size_t next = 0;
};

ProviderScript* g_script = nullptr;

void* PKG_GSDR_THISCALL recording_selector(gsdr::OpaqueSelectorProvider* receiver,
                                          std::uint32_t selector_id) {
  CallRecord record{selector_id, nullptr, receiver};
  g_script->calls.push_back(record);
  if (g_script->next >= g_script->answers.size()) {
    std::fprintf(stderr, "unexpected selector call #%zu (id 0x%x)\n",
                 g_script->next + 1, selector_id);
    std::exit(2);
  }
  return g_script->answers[g_script->next++];
}

int failures = 0;

void expect(bool condition, const char* what) {
  if (!condition) {
    std::fprintf(stderr, "FAIL: %s\n", what);
    ++failures;
  }
}

void expect_equal(std::size_t actual, std::size_t expected, const char* what) {
  if (actual != expected) {
    std::fprintf(stderr, "FAIL: %s (expected %zu, got %zu)\n", what, expected,
                 actual);
    ++failures;
  }
}

// A provider wired to the recorder, plus a receiver whose anchor is the address
// the script has to echo back.
struct Fixture {
  gsdr::OpaqueSelectorProviderVTable vtable{};
  gsdr::OpaqueSelectorProvider provider{};
  gsdr::OpaqueTerrainSphere sphere{};

  Fixture() {
    vtable.select_58 = &recording_selector;
    provider.vtable = &vtable;
  }
};

}  // namespace

int main() {
  // --- case 1: both queries answer the anchor -> true -----------------------
  {
    Fixture f;
    ProviderScript script;
    script.answers = std::vector<gsdr::OpaqueRttData*>{&f.sphere.anchor_04, &f.sphere.anchor_04};
    g_script = &script;

    const bool result =
        gsdr::get_sim_data_rtt_00f968b0(&f.sphere, &f.provider);

    expect(result, "both queries matching the anchor returns true");
    expect_equal(script.calls.size(), 2, "two selector calls");
    if (script.calls.size() == 2) {
      expect_equal(script.calls[0].selector_id, gsdr::kSelectorIdFirst,
                   "first query uses selector id 0x8");
      expect_equal(script.calls[1].selector_id, gsdr::kSelectorIdSecond,
                   "second query uses selector id 0x7");
      expect(script.calls[0].receiver == &f.provider,
             "the provider, not the sphere, is the slot receiver");
      expect(script.calls[1].receiver == &f.provider,
             "the provider, not the sphere, is the slot receiver");
    }
  }

  // --- case 2: the first query misses -> false, and 0x7 is never issued -----
  {
    Fixture f;
    gsdr::OpaqueRttData decoy{};  // a different address, so the compare misses
    ProviderScript script;
    script.answers = std::vector<gsdr::OpaqueRttData*>{&decoy, &f.sphere.anchor_04};
    g_script = &script;

    const bool result =
        gsdr::get_sim_data_rtt_00f968b0(&f.sphere, &f.provider);

    expect(!result, "a first-query mismatch returns false");
    expect_equal(script.calls.size(), 1, "the second query is short-circuited");
  }

  // --- case 3: first matches, second misses -> false, both queries issued ---
  {
    Fixture f;
    gsdr::OpaqueRttData decoy{};
    ProviderScript script;
    script.answers = std::vector<gsdr::OpaqueRttData*>{&f.sphere.anchor_04, &decoy};
    g_script = &script;

    const bool result =
        gsdr::get_sim_data_rtt_00f968b0(&f.sphere, &f.provider);

    expect(!result, "a second-query mismatch returns false");
    expect_equal(script.calls.size(), 2, "both queries are issued");
  }

  // --- case 4: NULL receiver -> the anchor is NULL, not &sphere.anchor_04 ---
  {
    Fixture f;
    ProviderScript script;
    script.answers = std::vector<gsdr::OpaqueRttData*>{nullptr, nullptr};
    g_script = &script;

    const bool result =
        gsdr::get_sim_data_rtt_00f968b0(nullptr, &f.provider);

    expect(result, "a NULL receiver succeeds only when both queries answer NULL");
    expect_equal(script.calls.size(), 2, "two selector calls");
  }

  // --- case 5: NULL receiver, a non-NULL answer -> false -------------------
  {
    Fixture f;
    ProviderScript script;
    script.answers = std::vector<gsdr::OpaqueRttData*>{&f.sphere.anchor_04, &f.sphere.anchor_04};
    g_script = &script;

    const bool result =
        gsdr::get_sim_data_rtt_00f968b0(nullptr, &f.provider);

    expect(!result, "a NULL receiver does not match a non-NULL answer");
  }

  g_script = nullptr;
  if (failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", failures);
    return 1;
  }
  std::printf("get_sim_data_rtt_00f968b0: all checks passed\n");
  return 0;
}
