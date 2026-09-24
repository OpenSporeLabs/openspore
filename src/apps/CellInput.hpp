#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_set>

#include "IGameMode.hpp"

namespace openspore::cellinput {

using Key = openspore::gamemode::InputKey;

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

struct KeyAction {
  Key key;
  Action action;
};

struct Table {
  static const KeyAction entries[];
  static const std::size_t count;
  static const Action* lookup(Key key);
};

struct Frame {
  bool thrustLeft = false;
  bool thrustRight = false;
  bool thrustForward = false;
  bool thrustBack = false;
  bool boost = false;
};

struct CameraDirs {
  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;
  bool any() const { return left || right || up || down; }
};

class CellInput {
 public:
  void press(Key key);
  void release(Key key);
  bool isDown(Key key) const;
  void clear();
  void reset();

  Frame frame() const;
  CameraDirs camera() const;
  bool wantsQuit() const;
  bool takeToggleHealth();

  openspore::gamemode::InputEvent keyDown(Key key) const;
  openspore::gamemode::InputEvent keyUp(Key key) const;
  openspore::gamemode::InputEvent mouseMove(float x, float y) const;
  openspore::gamemode::InputEvent mouseDown(
      float x, float y, openspore::gamemode::MouseButton button) const;
  openspore::gamemode::InputEvent mouseUp(
      float x, float y, openspore::gamemode::MouseButton button) const;
  openspore::gamemode::InputEvent mouseWheel(float x, float y,
                                             float wheel) const;

 private:
  std::unordered_set<Key> mDown;
  bool mToggleHealthPending = false;
};

}  // namespace openspore::cellinput
