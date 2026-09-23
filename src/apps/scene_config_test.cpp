// CS-23: declarative scene config test. Loads src/apps/scene.json and asserts:
//   - it parses and has the expected entity set;
//   - every entity round-trips to the known record key + transform values;
//   - every entity carries identity + position provenance labels in
//     {VERIFIED, INFERRED} (the whole point of CS-23: provenance, not silence);
//   - the player-cell identity is INFERRED (the one non-record-confirmed id);
//   - a malformed scene (bad pos array) is rejected.
// Usage: scene_config_test <path-to-scene.json>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "SceneConfig.hpp"

namespace {

int g_failures = 0;
void check(bool cond, const char *label) {
  std::printf("%s: %s\n", cond ? "ok" : "FAIL", label);
  if (!cond) {
    ++g_failures;
  }
}

bool validProvenance(const std::string &s) {
  return s == "VERIFIED" || s == "INFERRED";
}

struct Expect {
  const char *role;
  uint32_t group;
  uint32_t inst;
  float pos[3];
  float targetSpan;
  size_t expectVerts;
  bool textured;
  const char *identity;  // expected identity provenance label
};

// The known Cell Stage scene (mirrors scene.json; the single source of truth
// for the test's expectations). CS-24: food/prey are real cell-family gmdl
// (group 0x40616201), replacing the rejected building stand-in 0x40637E03.
const Expect kExpected[] = {
    {"backdrop_a", 0x40666202, 0xD1B4BB56, {-8.0F, -6.0F, 2.0F}, 16.0F,
     1059, true, "VERIFIED"},
    {"backdrop_b", 0x40666203, 0xD1B4BB56, {8.0F, -6.0F, 5.0F}, 16.0F,
     750, true, "VERIFIED"},
    {"player_cell", 0x40616201, 0x0C7963FB, {0.0F, 0.0F, 0.0F}, 4.0F,
     668, false, "INFERRED"},
    {"food_a", 0x40616201, 0xB0B9BAFF, {3.5F, -1.5F, 2.5F}, 2.0F, 613, false,
     "INFERRED"},
    {"food_b", 0x40616201, 0xD9007204, {-4.5F, -2.0F, 3.5F}, 3.0F, 631, false,
     "INFERRED"},
    {"prey_c", 0x40616201, 0x0D64F036, {1.5F, -0.5F, -5.0F}, 2.5F, 1250,
     false, "INFERRED"},
};
constexpr int kCount = sizeof(kExpected) / sizeof(kExpected[0]);

} // namespace

int main(int argc, char **argv) {
  if (argc < 2) {
    std::printf("usage: scene_config_test <scene.json>\n");
    return 1;
  }

  openspore::apps::SceneConfig cfg;
  std::string err;
  const bool ok = openspore::apps::loadSceneConfig(argv[1], cfg, err);
  check(ok, "scene.json parses");
  if (!ok) {
    std::printf("  parse error: %s\n", err.c_str());
    return 1;
  }

  check(cfg.entities.size() == static_cast<size_t>(kCount),
        "scene has the expected entity count");
  check(cfg.schema == "cellstage.scene/1", "scene declares its schema");
  check(!cfg.provenanceNote.empty(), "scene carries a provenance note");

  for (int i = 0; i < kCount && i < static_cast<int>(cfg.entities.size());
       ++i) {
    const auto &e = cfg.entities[static_cast<size_t>(i)];
    const Expect &x = kExpected[i];

    char label[128];
    std::snprintf(label, sizeof(label), "role[%d] == %s", i, x.role);
    check(e.role == x.role, label);

    std::snprintf(label, sizeof(label), "group[%d] == 0x%08X", i, x.group);
    check(e.group == x.group, label);

    std::snprintf(label, sizeof(label), "inst[%d] == 0x%08X", i, x.inst);
    check(e.inst == x.inst, label);

    bool posEq = true;
    for (int c = 0; c < 3; ++c) {
      if (e.pos[c] != x.pos[c]) {
        posEq = false;
      }
    }
    std::snprintf(label, sizeof(label), "pos[%d] == [%.3f %.3f %.3f]", i,
                  x.pos[0], x.pos[1], x.pos[2]);
    check(posEq, label);

    std::snprintf(label, sizeof(label), "targetSpan[%d] == %.3f", i,
                  x.targetSpan);
    check(e.targetSpan == x.targetSpan, label);

    std::snprintf(label, sizeof(label), "expectVerts[%d] == %zu", i,
                  x.expectVerts);
    check(e.expectVerts == x.expectVerts, label);

    std::snprintf(label, sizeof(label), "textured[%d] == %d", i,
                  static_cast<int>(x.textured));
    check(e.textured == x.textured, label);

    // Provenance: every value must carry a label in {VERIFIED, INFERRED}.
    std::snprintf(label, sizeof(label), "identity[%d] labeled (%s)", i,
                  e.identity.c_str());
    check(validProvenance(e.identity), label);

    std::snprintf(label, sizeof(label), "pos_provenance[%d] labeled (%s)", i,
                  e.posProvenance.c_str());
    check(validProvenance(e.posProvenance), label);

    // Position provenance is INFERRED for every entity (no record stores a
    // per-entity position — the procedural-placement finding).
    std::snprintf(label, sizeof(label), "pos[%d] is INFERRED (procedural)", i);
    check(e.posProvenance == "INFERRED", label);

    // Identity provenance: the exact label per role (backdrops VERIFIED; the
    // cell-family identities are INFERRED — real cell gmdl, role by size).
    std::snprintf(label, sizeof(label), "identity[%d] == %s", i, x.identity);
    check(e.identity == x.identity, label);
  }

  // Negative: a malformed scene (pos not [x,y,z]) must be rejected.
  {
    const char *bad = "/tmp/opencode/bad_scene.json";
    {
      std::ofstream out(bad);
      out << "{ \"schema\": \"cellstage.scene/1\", \"entities\": ["
          << "{ \"role\": \"x\", \"group\": \"0x1\", \"inst\": \"0x2\","
          << " \"pos\": [1.0, 2.0], \"textured\": false } ] }";
    }
    openspore::apps::SceneConfig badCfg;
    std::string badErr;
    const bool badOk =
        openspore::apps::loadSceneConfig(bad, badCfg, badErr);
    check(!badOk, "malformed scene (pos [x,y]) is rejected");
  }

  if (g_failures > 0) {
    std::printf("scene_config_test: %d FAIL\n", g_failures);
    return 1;
  }
  std::printf("scene_config_test: all pass\n");
  return 0;
}
