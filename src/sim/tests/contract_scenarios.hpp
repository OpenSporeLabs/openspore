// Shared contract scenarios for the Cell simulation (Obj35,
// docs/CELL-CONTRACT.md). The same Scenario list drives BOTH the fixture
// emitter (sim_test --emit-fixtures) and the contract test
// (sim_contract_test), so the frozen fixtures and the replay use identical
// inputs by construction.
//
// Contract version is pinned by kContractVersion; the frozen fixtures record
// that string and the contract test asserts it. Bumping the version requires
// a deliberate semantics change + fixture regeneration.
#pragma once

#include <string>
#include <vector>

#include "Sim.hpp"

namespace openspore::sim {

// Pinned contract version. The frozen fixture file
// tests/fixtures/cell/fixtures.json records this exact string.
// /2 (2026-09-23, CS-01): MovementPlane defaults pinned to the values read
// from the original binary (normal {0,0,1}, point {0,0,0}) — the mouse-
// steering fixture values changed accordingly.
constexpr const char *kContractVersion = "cell-sim-contract/2";

// One named, fully-specified replay: entities + initial camera + movement
// plane + ordered input frames. MovementParams are the struct defaults
// (pinned by the contract document; changing them breaks the fixtures).
struct Scenario {
  std::string name;
  std::string description;
  std::vector<Entity> entities;
  CameraState camera; // camera before frame 0 (initial)
  MovementPlane plane;
  std::vector<InputFrame> frames;
};

// The sim state captured AFTER each update() call — the per-frame oracle.
// Events are this frame's only (returned by update); alive is the entity
// vector's alive flags in entity order.
struct FrameSnapshot {
  float pos[3] = {0.0F, 0.0F, 0.0F};
  float heading = 0.0F;
  float vel[3] = {0.0F, 0.0F, 0.0F};
  int growMeter = 0;
  std::vector<std::string> eventTypes;    // "eat" | "flee"
  std::vector<std::string> eventEntities; // parallel to eventTypes
  std::vector<bool> alive;
};

// Fresh sim for a scenario: default params, scenario plane + entities,
// default player (origin, heading 0, growMeter 0), scenario initial camera.
inline CellSim makeSim(const Scenario &s) {
  CellSim sim(std::vector<Entity>(s.entities), MovementParams{}, s.plane);
  sim.camera().yaw = s.camera.yaw;
  sim.camera().pitch = s.camera.pitch;
  sim.camera().zoom = s.camera.zoom;
  sim.camera().baseDist = s.camera.baseDist;
  sim.camera().fov = s.camera.fov;
  sim.camera().target[0] = s.camera.target[0];
  sim.camera().target[1] = s.camera.target[1];
  sim.camera().target[2] = s.camera.target[2];
  return sim;
}

// Replays the scenario from scratch; returns one FrameSnapshot per frame,
// in frame order. Deterministic: two calls return identical snapshots.
inline std::vector<FrameSnapshot> replay(const Scenario &s) {
  CellSim sim = makeSim(s);
  std::vector<FrameSnapshot> out;
  out.reserve(s.frames.size());
  for (const InputFrame &fr : s.frames) {
    const std::vector<SimEvent> ev = sim.update(fr);
    FrameSnapshot sn;
    const PlayerState &p = sim.player();
    for (int i = 0; i < 3; ++i) {
      sn.pos[i] = p.pos[i];
      sn.vel[i] = p.vel[i];
    }
    sn.heading = p.heading;
    sn.growMeter = p.growMeter;
    for (const SimEvent &e : ev) {
      sn.eventTypes.push_back(e.type != nullptr ? e.type : "");
      sn.eventEntities.push_back(e.entity);
    }
    for (const Entity &e : sim.entities()) {
      sn.alive.push_back(e.alive);
    }
    out.push_back(std::move(sn));
  }
  return out;
}

namespace contract_detail {

// The cell-stage entity layout (docs/analysis/dossiers/cell-movement.md
// resource refs; positions APPROXIMATION, parsed from cell_stage.cpp).
inline std::vector<Entity> stageEntities() {
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

inline InputFrame mouseFrame(float mx, float my, float camPitch) {
  InputFrame f;
  f.hasCamera = true;
  f.cameraYaw = 0.0F;
  f.cameraPitch = camPitch;
  f.cameraZoom = 1.0F;
  f.hasMouse = true;
  f.mouseX = mx;
  f.mouseY = my;
  return f;
}

} // namespace contract_detail

// The canonical scenario set (order is part of the fixture file).
inline const std::vector<Scenario> &scenarios() {
  static const std::vector<Scenario> all = [] {
    std::vector<Scenario> v;

    {
      // (a) No mouse, no keys -> the player is stationary.
      Scenario s;
      s.name = "zero_input_stationary";
      s.description = "30 empty frames, stage entities: player never moves, "
                      "no eat/flee events, growMeter stays 0";
      s.entities = contract_detail::stageEntities();
      for (int i = 0; i < 30; ++i) {
        s.frames.push_back(InputFrame{});
      }
      v.push_back(s);
    }

    {
      // (b) Mouse offset -> camera ray hits the movement plane, player swims
      // to the target point (Obj33 steering).
      Scenario s;
      s.name = "mouse_swim_toward_target";
      s.description = "camera pitch -0.3; 15 frames mouse at NDC center "
                      "(stationary), then 45 frames at NDC (0.5, 0): the "
                      "ray-plane target lands on +X, the player swims +X on "
                      "the swim plane";
      CameraState c;
      c.pitch = -0.3F;
      s.camera = c;
      for (int i = 0; i < 15; ++i) {
        s.frames.push_back(contract_detail::mouseFrame(0.0F, 0.0F, -0.3F));
      }
      for (int i = 0; i < 45; ++i) {
        s.frames.push_back(contract_detail::mouseFrame(0.5F, 0.0F, -0.3F));
      }
      v.push_back(s);
    }

    {
      // (c) Eat trigger: keyboard turns toward food_a, then thrusts into it.
      Scenario s;
      s.name = "eat_food_keyboard";
      s.description = "20 frames thrust-right (turn toward food_a), then 100 "
                      "frames thrust-forward: the player swims into food_a, "
                      "an eat event fires, growMeter becomes 1, food_a is "
                      "culled; prey_c untouched";
      s.entities = contract_detail::stageEntities();
      for (int i = 0; i < 20; ++i) {
        InputFrame f;
        f.thrustRight = true;
        s.frames.push_back(f);
      }
      for (int i = 0; i < 100; ++i) {
        InputFrame f;
        f.thrustForward = true;
        s.frames.push_back(f);
      }
      v.push_back(s);
    }

    {
      // (d) Flee trigger: prey inside fleeRadius at the start.
      Scenario s;
      s.name = "flee_from_prey";
      s.description = "prey_test at (0, 0, -3), inside fleeRadius 4.0 of the "
                      "origin; 40 empty frames: flee events while the player "
                      "is within fleeRadius, the player is pushed +Z (faces "
                      "away, boosted); flee stops once it escapes the radius";
      Entity prey;
      prey.role = "prey_test";
      prey.pos[0] = 0.0F;
      prey.pos[1] = 0.0F;
      prey.pos[2] = -3.0F;
      s.entities.push_back(prey);
      for (int i = 0; i < 40; ++i) {
        s.frames.push_back(InputFrame{});
      }
      v.push_back(s);
    }

    {
      // (e) Keyboard-only fallback: boost forward, then back, no mouse.
      Scenario s;
      s.name = "keyboard_only_fallback";
      s.description = "stage entities; 30 frames thrust-forward+boost (swims "
                      "+Z), then 30 frames thrust-back (retreats): final "
                      "position is short of the origin, no events (food_a and "
                      "prey_c stay out of range)";
      s.entities = contract_detail::stageEntities();
      for (int i = 0; i < 30; ++i) {
        InputFrame f;
        f.thrustForward = true;
        f.boost = true;
        s.frames.push_back(f);
      }
      for (int i = 0; i < 30; ++i) {
        InputFrame f;
        f.thrustBack = true;
        s.frames.push_back(f);
      }
      v.push_back(s);
    }

    return v;
  }();
  return all;
}

} // namespace openspore::sim
