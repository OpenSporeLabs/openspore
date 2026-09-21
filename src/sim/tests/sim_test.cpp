// CTest unit checks for the deterministic cell simulation (Obj17 part A).
// Pure C++: no SPORE/ package, no GPU — CI-safe.
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>

#include "Sim.hpp"

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
  check(std::fabs(p.pos[0]) < 0.5F,
        "sim: forward thrust -> no sideways drift");
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

void testScriptedInput() {
  const char *path = "/tmp/opencode/sim_test_input.jsonl";
  std::ofstream f(path, std::ios::trunc);
  f << "{\"frame\": 0, \"keys\": [\"forward\"], \"yaw\": 0.6, "
        "\"pitch\": 0.2, \"zoom\": 0.8}\n";
  f << "{\"frame\": 1, \"keys\": [\"right\", \"boost\"]}\n";
  f << "\n";
  f << "{\"keys\": [\"back\"]}\n";
  f.close();
  ScriptedInputSource src(path);
  check(src.ok(), "sim: scripted input parses");
  if (!src.ok()) {
    std::printf("  (%s)\n", src.error().c_str());
    return;
  }
  check(src.frameCount() == 3, "sim: 3 input frames parsed");
  const InputFrame f0 = src.frame(0);
  check(f0.thrustForward && f0.hasCamera &&
            std::fabs(f0.cameraYaw - 0.6F) < 1e-5F &&
            std::fabs(f0.cameraZoom - 0.8F) < 1e-5F,
        "sim: frame 0 keys + camera fields");
  const InputFrame f1 = src.frame(1);
  check(f1.thrustRight && f1.boost && !f1.hasCamera,
        "sim: frame 1 keys, camera untouched");
  const InputFrame f2 = src.frame(2);
  check(f2.thrustBack, "sim: frameless line lands on the next frame");
  const InputFrame f9 = src.frame(99);
  check(f9.thrustBack, "sim: frames past the end replay the last line");
  ScriptedInputSource bad("/tmp/opencode/definitely_absent_xyz.jsonl");
  check(!bad.ok(), "sim: missing input file reports an error");
}

} // namespace

int main() {
  testZeroInput();
  testForwardThrust();
  testDeterminism();
  testEat();
  testFlee();
  testScriptedInput();
  if (g_failures == 0) {
    std::printf("sim_test: ALL PASS\n");
    return 0;
  }
  std::printf("sim_test: %d FAILURES\n", g_failures);
  return 1;
}
