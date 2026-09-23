// CTest unit checks for the deterministic cell simulation (Obj17 part A).
// Pure C++: no SPORE/ package, no GPU — CI-safe.
//
// Obj35 fixture emitter: `sim_test --emit-fixtures <out.json>` freezes the
// contract fixture file (tests/fixtures/cell/fixtures.json). The "expected"
// values are exactly what the CURRENT CellSim produces — the provenance of
// every expected number is this binary (docs/CELL-CONTRACT.md).
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>

#include "Sim.hpp"
#include "contract_scenarios.hpp"

namespace {

int g_failures = 0;

void check(bool cond, const char *label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

using openspore::sim::CellSim;
using openspore::sim::Entity;
using openspore::sim::InputFrame;
using openspore::sim::ScriptedInputSource;

std::vector<Entity> makeEntities() {
  std::vector<Entity> v;
  Entity food;
  food.role = "food_a";
  food.pos[0] = 3.5F;
  food.pos[1] = -1.5F;
  food.pos[2] = 2.5F;
  v.push_back(food);
  Entity prey;
  prey.role = "prey_c";
  prey.pos[0] = 1.5F;
  prey.pos[1] = -0.5F;
  prey.pos[2] = -5.0F;
  v.push_back(prey);
  return v;
}

void testZeroInput() {
  CellSim sim(makeEntities());
  InputFrame zero;
  for (int i = 0; i < 30; ++i) {
    sim.update(zero);
  }
  const auto &p = sim.player();
  check(std::fabs(p.pos[0]) < 1e-6F && std::fabs(p.pos[1]) < 1e-6F &&
            std::fabs(p.pos[2]) < 1e-6F,
        "sim: zero input -> no movement");
  check(p.growMeter == 0, "sim: zero input -> no eat");
  check(sim.events().empty(), "sim: zero input -> no events");
}

void testForwardThrust() {
  CellSim sim(makeEntities());
  InputFrame in;
  in.thrustForward = true;
  for (int i = 0; i < 60; ++i) {
    sim.update(in);
  }
  const auto &p = sim.player();
  check(p.pos[2] > 1.0F, "sim: forward thrust -> moves along +Z (heading 0)");
  check(std::fabs(p.pos[0]) < 0.5F, "sim: forward thrust -> no sideways drift");
  check(p.pos[1] == 0.0F, "sim: forward thrust -> stays on the swim plane");
  check(p.growMeter == 0, "sim: straight +Z path misses food_a");
}

void testDeterminism() {
  CellSim a(makeEntities());
  CellSim b(makeEntities());
  InputFrame in;
  in.thrustForward = true;
  for (int i = 0; i < 120; ++i) {
    if (i % 20 == 0) {
      in.thrustRight = true;
      in.boost = true;
    }
    in.thrustForward = i % 2 == 0;
    a.update(in);
    b.update(in);
  }
  check(a.stateString() == b.stateString(),
        "sim: two runs of the same input -> identical state");
  check(a.events() == b.events(), "sim: events identical across runs");
}

void testEat() {
  Entity food;
  food.role = "food_test";
  food.pos[0] = 0.0F;
  food.pos[1] = 0.0F;
  food.pos[2] = 2.0F; // inside eatRadius 3.5 of the origin
  std::vector<Entity> v{food};
  CellSim sim(std::move(v));
  auto ev = sim.update(InputFrame{});
  check(!sim.entities()[0].alive, "sim: food in range is culled");
  check(sim.player().growMeter == 1, "sim: eating increments growMeter");
  check(ev.size() == 1 && std::string(ev[0].type) == "eat" &&
            ev[0].entity == "food_test",
        "sim: eat event recorded with entity role");
  auto ev2 = sim.update(InputFrame{});
  check(ev2.empty(), "sim: eaten food cannot be eaten twice");
}

void testFlee() {
  Entity prey;
  prey.role = "prey_test";
  prey.pos[0] = 0.0F;
  prey.pos[1] = 0.0F;
  prey.pos[2] = -3.0F; // inside fleeRadius 4.0 of the origin
  std::vector<Entity> v{prey};
  CellSim sim(std::move(v));
  auto ev = sim.update(InputFrame{});
  check(ev.size() == 1 && std::string(ev[0].type) == "flee",
        "sim: close prey emits a flee event");
  check(std::fabs(sim.player().heading) < 1e-3F,
        "sim: flee turns the player to face away (+Z)");
  check(sim.player().vel[2] > 0.0F, "sim: flee boosts the player away");
}

void testRayPlaneHit() {
  using openspore::sim::MovementPlane;
  using openspore::sim::rayPlaneHit;
  MovementPlane plane; // pinned (CS-01): z=0 plane, normal (0,0,1), point origin
  float hit[3];
  // Perpendicular ray from above the plane -> hits at the origin.
  const float o1[3] = {0.0F, 0.0F, 5.0F};
  const float d1[3] = {0.0F, 0.0F, -1.0F};
  check(rayPlaneHit(o1, d1, plane, hit) && std::fabs(hit[0]) < 1e-5F &&
            std::fabs(hit[1]) < 1e-5F && std::fabs(hit[2]) < 1e-5F,
        "sim: rayPlaneHit perpendicular ray -> origin");
  // Parallel ray (in the plane's direction) -> no hit.
  const float o2[3] = {0.0F, 5.0F, 0.0F};
  const float d2[3] = {1.0F, 0.0F, 0.0F};
  check(!rayPlaneHit(o2, d2, plane, hit),
        "sim: rayPlaneHit parallel ray -> none");
  // Ray pointing away from the plane (t < 0) -> no hit.
  const float o3[3] = {0.0F, 0.0F, -5.0F};
  const float d3[3] = {0.0F, 0.0F, -1.0F};
  check(!rayPlaneHit(o3, d3, plane, hit),
        "sim: rayPlaneHit ray behind plane -> none");
}

// Mouse steering (Obj33): with the camera pitched down, the view ray hits the
// z=0 swim plane (pinned from the binary, CS-01). NDC (0,0) targets the
// player's own position -> no movement; NDC (0.5,0) targets a point ahead on
// +X -> the player swims toward +X.
void testMouseSteer() {
  CellSim sim(std::vector<Entity>{});
  InputFrame in;
  in.hasCamera = true;
  in.cameraYaw = 0.0F;
  in.cameraPitch = -0.3F;
  in.cameraZoom = 1.0F;
  // Mouse dead-center: the ray-plane target is the player's own position.
  in.hasMouse = true;
  in.mouseX = 0.0F;
  in.mouseY = 0.0F;
  for (int i = 0; i < 30; ++i) {
    sim.update(in);
  }
  const auto &c = sim.player();
  check(std::fabs(c.pos[0]) < 1e-3F && std::fabs(c.pos[1]) < 1e-3F &&
            std::fabs(c.pos[2]) < 1e-3F,
        "sim: mouse at screen center -> no movement");

  // Offset the mouse right: the target lands on +X, the player swims +X.
  in.mouseX = 0.5F;
  for (int i = 0; i < 60; ++i) {
    sim.update(in);
  }
  const auto &p = sim.player();
  check(p.pos[0] > 1.0F, "sim: mouse right of center -> swims toward +X");
  check(std::fabs(p.pos[2]) < 0.5F,
        "sim: mouse steering stays on the swim plane (no z drift)");
  check(std::fabs(p.pos[1]) < 0.5F,
        "sim: mouse steering stays on the swim plane (no y drift)");
}

void testScriptedInput() {
  const char *path = "/tmp/opencode/sim_test_input.jsonl";
  std::ofstream f(path, std::ios::trunc);
  f << "{\"frame\": 0, \"keys\": [\"forward\"], \"yaw\": 0.6, "
       "\"pitch\": 0.2, \"zoom\": 0.8}\n";
  f << "{\"frame\": 1, \"keys\": [\"right\", \"boost\"]}\n";
  f << "{\"frame\": 2, \"mouse\": [0.5, 0.0], \"yaw\": 0.0, "
       "\"pitch\": -0.3}\n";
  f << "\n";
  f << "{\"keys\": [\"back\"]}\n";
  f.close();
  ScriptedInputSource src(path);
  check(src.ok(), "sim: scripted input parses");
  if (!src.ok()) {
    std::printf("  (%s)\n", src.error().c_str());
    return;
  }
  check(src.frameCount() == 4, "sim: 4 input frames parsed");
  const InputFrame f0 = src.frame(0);
  check(f0.thrustForward && f0.hasCamera &&
            std::fabs(f0.cameraYaw - 0.6F) < 1e-5F &&
            std::fabs(f0.cameraZoom - 0.8F) < 1e-5F,
        "sim: frame 0 keys + camera fields");
  const InputFrame f1 = src.frame(1);
  check(f1.thrustRight && f1.boost && !f1.hasCamera,
        "sim: frame 1 keys, camera untouched");
  const InputFrame f2 = src.frame(2);
  check(f2.hasMouse && std::fabs(f2.mouseX - 0.5F) < 1e-5F &&
            std::fabs(f2.mouseY) < 1e-5F && f2.hasCamera &&
            std::fabs(f2.cameraPitch - (-0.3F)) < 1e-5F && !f2.thrustBack,
        "sim: frame 2 mouse NDC + camera parsed");
  const InputFrame f3 = src.frame(3);
  check(f3.thrustBack, "sim: frameless line lands on the next frame");
  const InputFrame f9 = src.frame(99);
  check(f9.thrustBack, "sim: frames past the end replay the last line");
  ScriptedInputSource bad("/tmp/opencode/definitely_absent_xyz.jsonl");
  check(!bad.ok(), "sim: missing input file reports an error");
}

// ---- Obj35: contract fixture emitter --------------------------------------
// Emits the frozen fixture JSON. Floats are printed as %.9g — 9 significant
// decimal digits round-trip binary32 exactly, so the contract test's strtof
// parse recovers the emitted bits.

std::string fnum(float v) {
  char b[32];
  std::snprintf(b, sizeof(b), "%.9g", v);
  return b;
}

std::string fvec(const float v[3]) {
  return "[" + fnum(v[0]) + ", " + fnum(v[1]) + ", " + fnum(v[2]) + "]";
}

void emitFixtures(const char *path, bool &ok) {
  ok = false;
  std::ofstream f(path, std::ios::trunc);
  if (!f) {
    std::printf("emit-fixtures: cannot open %s for writing\n", path);
    return;
  }
  using openspore::sim::FrameSnapshot;
  using openspore::sim::replay;
  using openspore::sim::Scenario;
  using openspore::sim::scenarios;
  f << "{\n";
  f << "  \"contract\": \"" << openspore::sim::kContractVersion << "\",\n";
  f << "  \"dt\": " << fnum(openspore::sim::kDt) << ",\n";
  f << "  \"floats\": \"binary32; %.9g decimal round-trips exactly\",\n";
  f << "  \"params\": \"MovementParams struct defaults (pinned by "
       "docs/CELL-CONTRACT.md)\",\n";
  f << "  \"scenarios\": [\n";
  const std::vector<Scenario> &all = scenarios();
  for (std::size_t si = 0; si < all.size(); ++si) {
    const Scenario &s = all[si];
    f << "    {\n";
    f << "      \"name\": \"" << s.name << "\",\n";
    f << "      \"description\": \"" << s.description << "\",\n";
    f << "      \"entities\": [";
    for (size_t i = 0; i < s.entities.size(); ++i) {
      const openspore::sim::Entity &e = s.entities[i];
      if (i != 0) {
        f << ", ";
      }
      f << "{\"role\": \"" << e.role << "\", \"pos\": " << fvec(e.pos) << "}";
    }
    f << "],\n";
    f << "      \"camera\": {\"yaw\": " << fnum(s.camera.yaw)
      << ", \"pitch\": " << fnum(s.camera.pitch)
      << ", \"zoom\": " << fnum(s.camera.zoom)
      << ", \"baseDist\": " << fnum(s.camera.baseDist)
      << ", \"fov\": " << fnum(s.camera.fov) << "},\n";
    f << "      \"plane\": {\"normal\": " << fvec(s.plane.normal)
      << ", \"point\": " << fvec(s.plane.point) << "},\n";
    f << "      \"frames\": [";
    for (size_t i = 0; i < s.frames.size(); ++i) {
      const openspore::sim::InputFrame &fr = s.frames[i];
      if (i != 0) {
        f << ", ";
      }
      std::vector<const char *> keys;
      if (fr.thrustLeft) {
        keys.push_back("left");
      }
      if (fr.thrustRight) {
        keys.push_back("right");
      }
      if (fr.thrustForward) {
        keys.push_back("forward");
      }
      if (fr.thrustBack) {
        keys.push_back("back");
      }
      if (fr.boost) {
        keys.push_back("boost");
      }
      f << "{\"keys\": [";
      for (size_t k = 0; k < keys.size(); ++k) {
        if (k != 0) {
          f << ", ";
        }
        f << "\"" << keys[k] << "\"";
      }
      f << "]";
      if (fr.hasCamera) {
        f << ", \"camera\": {\"yaw\": " << fnum(fr.cameraYaw)
          << ", \"pitch\": " << fnum(fr.cameraPitch)
          << ", \"zoom\": " << fnum(fr.cameraZoom) << "}";
      }
      if (fr.hasMouse) {
        f << ", \"mouse\": [" << fnum(fr.mouseX) << ", " << fnum(fr.mouseY)
          << "]";
      }
      f << "}";
    }
    f << "],\n";
    const std::vector<FrameSnapshot> snaps = replay(s);
    f << "      \"expected\": {\"frames\": [";
    for (size_t i = 0; i < snaps.size(); ++i) {
      const FrameSnapshot &sn = snaps[i];
      if (i != 0) {
        f << ", ";
      }
      f << "{\"pos\": " << fvec(sn.pos) << ", \"heading\": " << fnum(sn.heading)
        << ", \"vel\": " << fvec(sn.vel) << ", \"growMeter\": " << sn.growMeter
        << ", \"events\": [";
      for (size_t e = 0; e < sn.eventTypes.size(); ++e) {
        if (e != 0) {
          f << ", ";
        }
        f << "[\"" << sn.eventTypes[e] << "\", \"" << sn.eventEntities[e]
          << "\"]";
      }
      f << "], \"alive\": [";
      for (size_t a = 0; a < sn.alive.size(); ++a) {
        if (a != 0) {
          f << ", ";
        }
        f << (sn.alive[a] ? "true" : "false");
      }
      f << "]}";
    }
    f << "]}";
    f << "\n    }" << (si + 1 < all.size() ? "," : "") << "\n";
  }
  f << "  ]\n";
  f << "}\n";
  f.close();
  if (!f) {
    std::printf("emit-fixtures: write to %s failed\n", path);
    return;
  }
  ok = true;
  std::printf("emit-fixtures: wrote %zu scenarios to %s (%s)\n", all.size(),
              path, openspore::sim::kContractVersion);
}

} // namespace

int main(int argc, char **argv) {
  if (argc >= 3 && std::string(argv[1]) == "--emit-fixtures") {
    bool ok = false;
    emitFixtures(argv[2], ok);
    return ok ? 0 : 1;
  }
  testZeroInput();
  testForwardThrust();
  testDeterminism();
  testEat();
  testFlee();
  testRayPlaneHit();
  testMouseSteer();
  testScriptedInput();
  if (g_failures == 0) {
    std::printf("sim_test: ALL PASS\n");
    return 0;
  }
  std::printf("sim_test: %d FAILURES\n", g_failures);
  return 1;
}
