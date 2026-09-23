// CellInput (CS-29, clean-room): the cell_stage key->action table.
//
// The original cCellModeStrategy::OnKeyDown (00e818f0) calls FUN_00e82900
// (the key->action lookup, 30 B) and, when it returns 0, special-cases
// virtualKey==2 to toggle the sCellUI health display (sCellUI+0x937), then
// forwards to GameInput::OnKeyDown. The thrust actions are the sim's
// (Sim.hpp InputFrame: thrustLeft/Right/Forward/Back + boost). This is the
// clean-room, layout-stable scancode->action table the app drives — the same
// mapping the SDL interactive path uses, made table-driven and testable
// (SDL-free; the app maps SDL scancodes onto the Key enum below).
#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_set>

namespace openspore::cellinput {

// Layout-stable key identifiers (the SDL scancodes the app uses, abstracted).
enum class Key : std::uint16_t {
  kW = 2,          // SDL_SCANCODE_W
  kS = 20,         // SDL_SCANCODE_S
  kA = 4,          // SDL_SCANCODE_A
  kD = 32,         // SDL_SCANCODE_D
  kShift = 42,     // SDL_SCANCODE_LSHIFT / RSHIFT
  kEscape = 41,    // SDL_SCANCODE_ESCAPE
  kLeft = 80,      // SDL_SCANCODE_LEFT
  kRight = 79,     // SDL_SCANCODE_RIGHT
  kUp = 82,        // SDL_SCANCODE_UP
  kDown = 81,      // SDL_SCANCODE_DOWN
  kToggleHealth = 0, // the original's virtualKey==2 special case
};

// The actions the cell-stage keys drive.
enum class Action : std::uint16_t {
  kNone = 0,
  kThrustForward,
  kThrustBack,
  kThrustLeft,
  kThrustRight,
  kBoost,
  kQuit,
  kCamLeft,
  kCamRight,
  kCamUp,
  kCamDown,
  kToggleHealthDisplay,
};

// One row of the key->action table.
struct KeyAction {
  Key key;
  Action action;
};

// The app's mapping (the SDL interactive path's table).
struct Table {
  static const KeyAction entries[];
  static const std::size_t count;
  // The action for a key, or nullptr if the key is unbound.
  static const Action *lookup(Key key);
};

// The thrust/boost portion of a frame (the sim's InputFrame thrust fields).
struct Frame {
  bool thrustLeft = false;
  bool thrustRight = false;
  bool thrustForward = false;
  bool thrustBack = false;
  bool boost = false;
};

// The arrow-key camera directions held this frame. The table owns WHICH
// direction; the app applies its own step magnitudes + pitch clamps.
struct CameraDirs {
  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;
  bool any() const {
    return left || right || up || down;
  }
};

class CellInput {
 public:
  void press(Key key);
  void release(Key key);
  bool isDown(Key key) const;
  void clear();

  // The thrust/boost actions held this frame.
  Frame frame() const;

  // The arrow-key camera directions held this frame.
  CameraDirs camera() const;

  // True while the quit key is down.
  bool wantsQuit() const;

  // Edge-triggered health-display toggle (the original's virtualKey==2).
  // Consumes the event on read.
  bool takeToggleHealth();

 private:
  std::unordered_set<std::uint16_t> mDown;
  bool mToggleHealthPending = false;
};

} // namespace openspore::cellinput
