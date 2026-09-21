// Implementation of the deterministic cell simulation (see Sim.hpp for the
// evidence labels of every behavior).
#include "Sim.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>

namespace openspore::sim {
namespace {

float dist2(const float a[3], const float b[3]) {
  const float dx = a[0] - b[0];
  const float dy = a[1] - b[1];
  const float dz = a[2] - b[2];
  return dx * dx + dy * dy + dz * dz;
}

// ---- tiny JSON-line parser (fixed shape only, no dependencies) -----------

// Returns the text of the value for "key" inside `line`, up to the matching
// delimiter (',' / '}' / ']'), trimmed; empty when the key is absent.
std::string jsonValue(const std::string &line, const char *key) {
  const std::string k = std::string("\"") + key + "\"";
  std::size_t p = line.find(k);
  if (p == std::string::npos) {
    return {};
  }
  p = line.find(':', p + k.size());
  if (p == std::string::npos) {
    return {};
  }
  ++p;
  while (p < line.size() && (line[p] == ' ' || line[p] == '\t')) {
    ++p;
  }
  std::size_t end = p;
  char open = 0;
  if (end < line.size() && (line[end] == '[' || line[end] == '{')) {
    open = line[end];
    const char close = open == '[' ? ']' : '}';
    ++end;
    while (end < line.size() && line[end] != close) {
      ++end;
    }
  } else {
    while (end < line.size() && line[end] != ',' && line[end] != '}' &&
           line[end] != ']') {
      ++end;
    }
  }
  std::string v = line.substr(p, end - p);
  while (!v.empty() && (v.back() == ' ' || v.back() == '\t')) {
    v.pop_back();
  }
  return v;
}

float jsonFloat(const std::string &line, const char *key, float def) {
  const std::string v = jsonValue(line, key);
  return v.empty() ? def : std::strtof(v.c_str(), nullptr);
}

int jsonInt(const std::string &line, const char *key, int def) {
  const std::string v = jsonValue(line, key);
  return v.empty() ? def : static_cast<int>(std::strtol(v.c_str(), nullptr, 10));
}

void parseKeys(const std::string &line, InputFrame &f) {
  const std::string v = jsonValue(line, "keys");
  if (v.empty()) {
    return;
  }
  std::size_t p = v.find('"');
  while (p != std::string::npos) {
    std::size_t q = v.find('"', p + 1);
    if (q == std::string::npos) {
      break;
    }
    const std::string k = v.substr(p + 1, q - p - 1);
    if (k == "left") {
      f.thrustLeft = true;
    } else if (k == "right") {
      f.thrustRight = true;
    } else if (k == "forward") {
      f.thrustForward = true;
    } else if (k == "back") {
      f.thrustBack = true;
    } else if (k == "boost") {
      f.boost = true;
    }
    p = v.find('"', q + 1);
  }
}

} // namespace

CellSim::CellSim(std::vector<Entity> entities, MovementParams params,
                 MovementPlane plane)
    : params_(params), plane_(plane), entities_(std::move(entities)) {}

std::vector<SimEvent> CellSim::update(const InputFrame &input) {
  std::vector<SimEvent> ev;
  if (input.hasCamera) {
    cam_.yaw = input.cameraYaw;
    cam_.pitch = input.cameraPitch;
    cam_.zoom = input.cameraZoom;
  }

  if (input.thrustLeft) {
    player_.heading -= params_.turnRate * kDt;
  }
  if (input.thrustRight) {
    player_.heading += params_.turnRate * kDt;
  }

  // Steering target (Obj33, docs/analysis/dossiers/cell-movement.md): the
  // camera ray (from the recorded mouse position) is intersected with the
  // movement plane; the hit point becomes the player's target and the
  // orientation-to-travel. The ray origin/dir come from the camera; the
  // plane normal/point are named parameters (APPROXIMATION defaults — the
  // original's constant values were never read, no runtime trace exists).
  bool steer = false;
  float target[3] = {0.0F, 0.0F, 0.0F};
  if (input.hasMouse) {
    float origin[3], dir[3];
    cam_.viewRay(input.mouseX, input.mouseY, origin, dir);
    if (rayPlaneHit(origin, dir, plane_, target)) {
      steer = true;
      const float dx = target[0] - player_.pos[0];
      const float dy = target[1] - player_.pos[1];
      const float dz = target[2] - player_.pos[2];
      const float d = std::sqrtf(dx * dx + dy * dy + dz * dz);
      if (d > params_.steerStopRadius && dx * dx + dz * dz > 1e-12F) {
        player_.heading = std::atan2f(dx, dz); // face the travel direction
      }
    }
  }

  // FLEE (INFERRED): prey within fleeRadius -> face away, implicit forward
  // thrust (the "scared" swim states), boosted, for this frame.
  bool boost = input.boost;
  bool fleeing = false;
  for (const Entity &e : entities_) {
    if (!e.alive || !e.isPrey()) {
      continue;
    }
    if (dist2(player_.pos, e.pos) < params_.fleeRadius * params_.fleeRadius) {
      const float dx = player_.pos[0] - e.pos[0];
      const float dz = player_.pos[2] - e.pos[2];
      if (dx * dx + dz * dz > 1e-12F) {
        player_.heading = std::atan2f(dx, dz); // face directly away
      }
      boost = true;
      fleeing = true;
      SimEvent e2;
      e2.frame = frame_;
      e2.type = "flee";
      e2.entity = e.role;
      ev.push_back(e2);
    }
  }

  const float fwd = params_.forwardSpeed * (boost ? params_.boostMul : 1.0F);
  const float str = params_.strafeSpeed * (boost ? params_.boostMul : 1.0F);
  const float sspd = params_.steerSpeed * (boost ? params_.boostMul : 1.0F);
  const float fx = std::sinf(player_.heading);
  const float fz = std::cosf(player_.heading);
  const float rx = fz;   // right = (fz, 0, -fx)
  const float rz = -fx;
  float tvx = 0.0F, tvy = 0.0F, tvz = 0.0F;
  if (steer) {
    // Mouse-driven target is primary: full steer velocity toward the hit.
    const float dx = target[0] - player_.pos[0];
    const float dy = target[1] - player_.pos[1];
    const float dz = target[2] - player_.pos[2];
    const float d = std::sqrtf(dx * dx + dy * dy + dz * dz);
    if (d > params_.steerStopRadius) {
      tvx = dx / d * sspd;
      tvy = dy / d * sspd;
      tvz = dz / d * sspd;
      // Keyboard is SECONDARY (OnKeyDown): a reduced thrust bias on top of
      // the mouse target; it never sets the target.
      const float km = params_.keyboardSecondaryMul;
      if (input.thrustForward) {
        tvx += fx * fwd * km;
        tvz += fz * fwd * km;
      }
      if (input.thrustBack) {
        tvx -= fx * fwd * km;
        tvz -= fz * fwd * km;
      }
      if (input.thrustLeft) {
        tvx -= rx * str * km;
        tvz -= rz * str * km;
      }
      if (input.thrustRight) {
        tvx += rx * str * km;
        tvz += rz * str * km;
      }
    }
  } else {
    // No mouse position this frame: keyboard-only thrust path.
    if (input.thrustForward) {
      tvx += fx * fwd;
      tvz += fz * fwd;
    }
    if (input.thrustBack) {
      tvx -= fx * fwd;
      tvz -= fz * fwd;
    }
    if (input.thrustLeft) {
      tvx -= rx * str;
      tvz -= rz * str;
    }
    if (input.thrustRight) {
      tvx += rx * str;
      tvz += rz * str;
    }
  }
  if (fleeing) {
    // Flee overrides: straight ahead, boosted.
    tvx = fx * fwd;
    tvy = 0.0F;
    tvz = fz * fwd;
  }

  const float k = std::min(1.0F, params_.damping * kDt);
  player_.vel[0] += (tvx - player_.vel[0]) * k;
  player_.vel[1] += (tvy - player_.vel[1]) * k;
  player_.vel[2] += (tvz - player_.vel[2]) * k;
  player_.pos[0] += player_.vel[0] * kDt;
  player_.pos[1] += player_.vel[1] * kDt;
  player_.pos[2] += player_.vel[2] * kDt;

  // EAT (INFERRED): food within eatRadius is consumed.
  for (Entity &e : entities_) {
    if (!e.alive || !e.isFood()) {
      continue;
    }
    if (dist2(player_.pos, e.pos) < params_.eatRadius * params_.eatRadius) {
      e.alive = false;
      ++player_.growMeter;
      SimEvent e2;
      e2.frame = frame_;
      e2.type = "eat";
      e2.entity = e.role;
      ev.push_back(e2);
    }
  }

  cam_.target[0] = player_.pos[0];
  cam_.target[1] = player_.pos[1];
  cam_.target[2] = player_.pos[2];
  ++frame_;
  for (const SimEvent &e2 : ev) {
    events_.push_back(e2);
  }
  return ev;
}

std::string CellSim::stateString() const {
  char buf[256];
  std::string s;
  std::snprintf(buf, sizeof(buf),
                "player pos=%.6f %.6f %.6f heading=%.6f vel=%.6f %.6f %.6f "
                "growMeter=%d\n",
                player_.pos[0], player_.pos[1], player_.pos[2],
                player_.heading, player_.vel[0], player_.vel[1],
                player_.vel[2], player_.growMeter);
  s += buf;
  s += "entities:\n";
  for (const Entity &e : entities_) {
    std::snprintf(buf, sizeof(buf), "  %s pos=%.6f %.6f %.6f alive=%d\n",
                  e.role.c_str(), e.pos[0], e.pos[1], e.pos[2], e.alive);
    s += buf;
  }
  return s;
}

ScriptedInputSource::ScriptedInputSource(const std::string &path) {
  std::ifstream f(path);
  if (!f) {
    error_ = "cannot open input file: " + path;
    return;
  }
  std::string line;
  int lastFrame = -1;
  while (std::getline(f, line)) {
    std::size_t b = line.find_first_not_of(" \t\r\n");
    if (b == std::string::npos || line.find('{', b) == std::string::npos) {
      continue; // blank line
    }
    InputFrame fr;
    const int frame = jsonInt(line, "frame", lastFrame + 1);
    if (frame < 0) {
      error_ = "negative frame number in: " + line;
      frames_.clear();
      return;
    }
    parseKeys(line, fr);
    const std::string m = jsonValue(line, "mouse");
    if (!m.empty()) {
      // "mouse": [x, y] — jsonValue returns the bracketed array text; skip
      // the leading '[', parse the first float, skip to the second, parse it.
      fr.hasMouse = true;
      const char *p1 = m.c_str();
      while (*p1 && (*p1 == '[' || *p1 == ' ' || *p1 == '\t')) {
        ++p1;
      }
      char *end1 = nullptr;
      fr.mouseX = std::strtof(p1, &end1);
      if (end1 != p1) {
        const char *p2 = end1;
        while (*p2 && (*p2 == ',' || *p2 == ' ' || *p2 == '\t' || *p2 == ']')) {
          ++p2;
        }
        char *end2 = nullptr;
        fr.mouseY = std::strtof(p2, &end2);
      }
    }
    const std::string y = jsonValue(line, "yaw");
    const std::string p = jsonValue(line, "pitch");
    const std::string z = jsonValue(line, "zoom");
    if (!y.empty() || !p.empty() || !z.empty()) {
      fr.hasCamera = true;
      fr.cameraYaw = jsonFloat(line, "yaw", fr.cameraYaw);
      fr.cameraPitch = jsonFloat(line, "pitch", fr.cameraPitch);
      fr.cameraZoom = jsonFloat(line, "zoom", fr.cameraZoom);
    }
    if (static_cast<std::size_t>(frame) >= frames_.size()) {
      frames_.resize(static_cast<std::size_t>(frame) + 1);
    }
    frames_[static_cast<std::size_t>(frame)] = fr;
    lastFrame = std::max(lastFrame, frame);
  }
  if (frames_.empty()) {
    error_ = "no input frames in: " + path;
  }
}

InputFrame ScriptedInputSource::frame(int f) const {
  if (frames_.empty()) {
    return {};
  }
  if (f < 0) {
    return frames_[0];
  }
  if (static_cast<std::size_t>(f) >= frames_.size()) {
    return frames_.back();
  }
  return frames_[static_cast<std::size_t>(f)];
}

} // namespace openspore::sim
