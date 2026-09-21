// Clean-room deterministic cell simulation (Obj17 part A).
//
// Fixed-dt (1/60 s) update of a player cell among food/prey entities.
// No time(), no rand(): the same entity table + input sequence always
// produces the same state (differential-testable).
//
// Evidence labels (docs/CELLSTAGE-RECON section 5):
//   - movement constants: APPROXIMATION (never traced; cCellModeStrategy
//     OnKeyDown confirms thrust-style input exists, no values observed);
//   - camera: INFERRED orbit/follow/zoom from cCameraManager::SetViewer;
//   - eat/flee rules: INFERRED from anim states Cell_eat_* / Cell_mov_*.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace openspore::sim {

// Fixed simulation step; 60 updates per second.
constexpr float kDt = 1.0F / 60.0F;

// A scene entity. role/group/inst identify the record; pos is world space;
// targetSpan scales the mesh bbox max span. alive flips to false when the
// entity is eaten (or culled); the stage skips dead entities.
struct Entity {
  std::string role;
  uint32_t group = 0;
  uint32_t inst = 0;
  float pos[3] = {0.0F, 0.0F, 0.0F};
  float targetSpan = 1.0F;
  bool alive = true;

  bool isFood() const { return role.compare(0, 5, "food_") == 0; }
  bool isPrey() const { return role.compare(0, 5, "prey_") == 0; }
};

// Player state. heading is yaw in radians; forward = (sin h, 0, cos h),
// so h=0 faces +Z and increasing h turns toward +X.
struct PlayerState {
  float pos[3] = {0.0F, 0.0F, 0.0F};
  float heading = 0.0F;
  float vel[3] = {0.0F, 0.0F, 0.0F};
  int growMeter = 0;
};

// Orbit camera following the player (INFERRED from cCameraManager::SetViewer).
// eye = target + dist * (sin yaw * cos pitch, sin pitch, cos yaw * cos pitch).
struct CameraState {
  float yaw = 0.0F;
  float pitch = 0.0F;
  float zoom = 1.0F;
  float baseDist = 16.0F;
  float target[3] = {0.0F, 0.0F, 0.0F};

  float dist() const { return baseDist * zoom; }
};

// One frame of input. Thrust keys map to the cCellModeStrategy OnKeyDown
// handlers (names CONFIRMED; behavior APPROXIMATED below).
struct InputFrame {
  bool thrustLeft = false;
  bool thrustRight = false;
  bool thrustForward = false;
  bool thrustBack = false;
  bool boost = false;
  // Camera; hasCamera=false leaves the camera untouched this frame.
  bool hasCamera = false;
  float cameraYaw = 0.0F;
  float cameraPitch = 0.0F;
  float cameraZoom = 1.0F;
};

// Named so every number is replaceable without touching the update code.
// Speeds/damping/turn rate: APPROXIMATION (no traced values, recon section 5).
// Radii: INFERRED (eat smaller / flee bigger; no observed numbers).
struct MovementParams {
  float forwardSpeed = 4.0F; // units/s, APPROXIMATION
  float strafeSpeed = 2.0F;  // units/s, APPROXIMATION
  float boostMul = 2.0F;     // speed multiplier while boosting, APPROXIMATION
  float turnRate = 1.5F;     // radians/s, APPROXIMATION
  float damping = 6.0F;      // vel approaches target vel (exponential), APPROXIMATION
  float eatRadius = 3.5F;    // dist(player, food) below this eats, INFERRED
  float fleeRadius = 4.0F;   // dist(player, prey) below this flees, INFERRED
};

struct SimEvent {
  int frame = 0;
  const char *type = nullptr; // "eat" | "flee"
  std::string entity;

  bool operator==(const SimEvent &o) const {
    return frame == o.frame &&
           (type == o.type ||
            (type != nullptr && o.type != nullptr &&
             std::strcmp(type, o.type) == 0)) &&
           entity == o.entity;
  }
};

// Deterministic fixed-dt simulation of the player cell.
class CellSim {
public:
  CellSim(std::vector<Entity> entities, MovementParams params = {});

  const PlayerState &player() const { return player_; }
  CameraState &camera() { return cam_; }
  const CameraState &camera() const { return cam_; }
  const std::vector<Entity> &entities() const { return entities_; }
  const std::vector<SimEvent> &events() const { return events_; }
  int frame() const { return frame_; }

  // Advances one frame (fixed kDt) and returns this frame's events.
  // Movement: heading turns with left/right; target velocity from thrust
  // (forward along heading + strafe), scaled by boost; vel damps toward
  // the target; pos integrates. EAT: live food within eatRadius is culled
  // and growMeter += 1. FLEE: live prey within fleeRadius makes the player
  // face away, thrust forward, and boost for this frame.
  std::vector<SimEvent> update(const InputFrame &input);

  // Deterministic text dump of the full state (tests compare two runs).
  std::string stateString() const;

private:
  PlayerState player_;
  CameraState cam_;
  MovementParams params_;
  std::vector<Entity> entities_;
  std::vector<SimEvent> events_;
  int frame_ = 0;
};

// Replays a JSON-lines input file: one object per line,
//   {"frame": 12, "keys": ["forward","right","boost"],
//    "yaw": 0.6, "pitch": 0.2, "zoom": 0.8}
// "keys" items: left, right, forward, back, boost. Missing keys default;
// unknown keys are ignored; a line without "frame" takes the frame after
// the previous line (0 for the first). Hand-rolled for this fixed shape;
// no dependencies.
class ScriptedInputSource {
public:
  explicit ScriptedInputSource(const std::string &path);

  bool ok() const { return error_.empty(); }
  const std::string &error() const { return error_; }
  std::size_t frameCount() const { return frames_.size(); }

  // Input for frame f; frames past the last line replay the last line.
  InputFrame frame(int f) const;

private:
  std::vector<InputFrame> frames_;
  std::string error_;
};

} // namespace openspore::sim
