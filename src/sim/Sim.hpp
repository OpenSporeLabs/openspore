// Clean-room deterministic cell simulation (Obj17 part A).
//
// Fixed-dt (1/60 s) update of a player cell among food/prey entities.
// No time(), no rand(): the same entity table + input sequence always
// produces the same state (differential-testable).
//
// Evidence labels (docs/CELLSTAGE-RECON section 5,
// docs/analysis/dossiers/cell-movement.md):
//   - movement: the player is steered by a CAMERA-RAY / MOVEMENT-PLANE
//     intersection (MovePlayerToMousePosition, OBSERVED in decompilation).
//     The mouse sets the movement TARGET; OnKeyDown thrust keys are
//     SECONDARY. Keyboard-only input is kept as the fallback for frames
//     without a mouse position.
//   - movement plane normal/point: the original reads them from constants at
//     DAT_015a7c40/44/48 and DAT_016b3c28/2c/30 — addresses OBSERVED. Values
//     READ from the static binary (CS-01, 2026-09-23): the normal is
//     VERIFIED = {0,0,1} (section .data, file offset 0x11a6640: 0.0f, 0.0f,
//     1.0f); the point's addresses sit in BSS (zero in the image, written at
//     runtime — per-world), so its load-time value is {0,0,0}. The
//     MovementPlane defaults below are the read values.
//   - camera: INFERRED orbit/follow/zoom from cCameraManager::SetViewer;
//   - eat/flee rules: INFERRED from anim states Cell_eat_* / Cell_mov_*.
#pragma once

#include <cmath>
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
  float fov = 60.0F * 3.14159265358979F / 180.0F; // vertical, APPROXIMATION

  float dist() const { return baseDist * zoom; }

  // Camera eye position (same orbit formula the cell stage renders with).
  void eyePos(float out[3]) const {
    out[0] = target[0] + dist() * std::sinf(yaw) * std::cosf(pitch);
    out[1] = target[1] + dist() * std::sinf(pitch);
    out[2] = target[2] + dist() * std::cosf(yaw) * std::cosf(pitch);
  }

  // View ray for an NDC mouse position (x right, y up, -1..1). Fills origin
  // (the eye) and a normalized dir; the basis mirrors the stage's lookAt.
  void viewRay(float mouseX, float mouseY, float origin[3],
               float dir[3]) const {
    eyePos(origin);
    const float cp = std::cosf(pitch);
    const float f[3] = {-std::sinf(yaw) * cp, -std::sinf(pitch),
                        -std::cosf(yaw) * cp};
    const float r[3] = {std::cosf(yaw), 0.0F, -std::sinf(yaw)};
    const float u[3] = {r[1] * f[2] - r[2] * f[1],
                        r[2] * f[0] - r[0] * f[2],
                        r[0] * f[1] - r[1] * f[0]};
    const float th = std::tanf(fov * 0.5F);
    dir[0] = f[0] + r[0] * mouseX * th + u[0] * mouseY * th;
    dir[1] = f[1] + r[1] * mouseX * th + u[1] * mouseY * th;
    dir[2] = f[2] + r[2] * mouseX * th + u[2] * mouseY * th;
    const float l = std::sqrtf(dir[0] * dir[0] + dir[1] * dir[1] +
                                dir[2] * dir[2]);
    for (int i = 0; i < 3; ++i) {
      dir[i] /= l;
    }
  }
};

// The movement plane the camera ray is intersected with
// (docs/analysis/dossiers/cell-movement.md). The original reads the normal
// from DAT_015a7c40/44/48 and the point from DAT_016b3c28/2c/30.
// CS-01 (2026-09-23) read the static binary (SporeApp.exe 3.1.0.22, PE .data
// section, file offset 0x11a6640): normal = {0,0,1} — VERIFIED. The point's
// addresses are BSS (zero in the image; written at runtime, per-world):
// load-time {0,0,0}. The swim plane is therefore the horizontal z=0 plane.
struct MovementPlane {
  float normal[3] = {0.0F, 0.0F, 1.0F}; // VERIFIED (binary read, .data)
  float point[3] = {0.0F, 0.0F, 0.0F};  // BSS: zero at load, runtime-written
};

// Intersect a ray with a plane (the decompiled t = dot(n, p-o)/dot(n, d)
// with the observed t >= 0 guard). Returns false when the ray is parallel
// to the plane or the hit is behind the origin.
inline bool rayPlaneHit(const float origin[3], const float dir[3],
                        const MovementPlane &plane, float hit[3]) {
  const float denom = dir[0] * plane.normal[0] + dir[1] * plane.normal[1] +
                      dir[2] * plane.normal[2];
  if (std::fabsf(denom) < 1e-6F) {
    return false;
  }
  const float t = ((plane.point[0] - origin[0]) * plane.normal[0] +
                   (plane.point[1] - origin[1]) * plane.normal[1] +
                   (plane.point[2] - origin[2]) * plane.normal[2]) /
                  denom;
  if (t < 0.0F) {
    return false;
  }
  for (int i = 0; i < 3; ++i) {
    hit[i] = origin[i] + dir[i] * t;
  }
  return true;
}

// One frame of input. The mouse position (OnMouseMove, VERIFIED SDK name)
// sets the movement TARGET via the camera ray; the thrust keys (OnKeyDown,
// VERIFIED SDK name) are SECONDARY — they bias the steered velocity but do
// not set the target. hasMouse=false (no mouse position recorded) falls back
// to the keyboard-only thrust path.
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
  // Mouse in NDC (x right, y up, -1..1).
  bool hasMouse = false;
  float mouseX = 0.0F;
  float mouseY = 0.0F;
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
  // Mouse steering (the ray-plane target); values APPROXIMATION (no traced
  // numbers exist for any of these).
  float steerSpeed = 4.0F;           // max units/s toward the ray-plane target
  float steerStopRadius = 0.2F;      // stop once this close to the target
  float keyboardSecondaryMul = 0.25F; // keyboard thrust weight while the mouse
                                      // target is active (keys are secondary)
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
  // plane: the movement plane for mouse steering (defaults are the values
  // read from the original binary — see MovementPlane).
  CellSim(std::vector<Entity> entities, MovementParams params = {},
          MovementPlane plane = {});

  const PlayerState &player() const { return player_; }
  CameraState &camera() { return cam_; }
  const CameraState &camera() const { return cam_; }
  const std::vector<Entity> &entities() const { return entities_; }
  const std::vector<SimEvent> &events() const { return events_; }
  int frame() const { return frame_; }
  const MovementPlane &plane() const { return plane_; }

  // Advances one frame (fixed kDt) and returns this frame's events.
  // Movement (Obj33): when the frame carries a mouse position, the camera
  // ray is intersected with the movement plane and the player steers to
  // the hit point (oriented to face the travel direction); the thrust keys
  // add a secondary bias. Without a mouse, the keyboard thrust path applies
  // (forward along heading + strafe, scaled by boost). Vel damps toward the
  // target; pos integrates. EAT: live food within eatRadius is culled and
  // growMeter += 1. FLEE: live prey within fleeRadius makes the player face
  // away, thrust forward, and boost for this frame.
  std::vector<SimEvent> update(const InputFrame &input);

  // Deterministic text dump of the full state (tests compare two runs).
  std::string stateString() const;

private:
  PlayerState player_;
  CameraState cam_;
  MovementParams params_;
  MovementPlane plane_;
  std::vector<Entity> entities_;
  std::vector<SimEvent> events_;
  int frame_ = 0;
};

// Replays a JSON-lines input file: one object per line,
//   {"frame": 12, "keys": ["forward","right","boost"],
//    "yaw": 0.6, "pitch": 0.2, "zoom": 0.8, "mouse": [0.4, -0.1]}
// "keys" items: left, right, forward, back, boost. "mouse" is the NDC mouse
// position [x, y] (x right, y up, -1..1); its presence enables mouse
// steering for that frame. Missing keys default; unknown keys are ignored;
// a line without "frame" takes the frame after the previous line (0 for the
// first). Hand-rolled for this fixed shape; no dependencies.
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
