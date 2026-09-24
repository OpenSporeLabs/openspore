#include "CellInput.hpp"

namespace openspore::cellinput {

const KeyAction Table::entries[] = {
    {Key::kW, Action::kThrustForward},
    {Key::kS, Action::kThrustBack},
    {Key::kA, Action::kThrustLeft},
    {Key::kD, Action::kThrustRight},
    {Key::kShift, Action::kBoost},
    {Key::kEscape, Action::kQuit},
    {Key::kLeft, Action::kCamLeft},
    {Key::kRight, Action::kCamRight},
    {Key::kUp, Action::kCamUp},
    {Key::kDown, Action::kCamDown},
    {Key::kToggleHealth, Action::kToggleHealthDisplay},
};
const std::size_t Table::count = sizeof(entries) / sizeof(entries[0]);

const Action* Table::lookup(Key key) {
  for (std::size_t i = 0; i < count; ++i) {
    if (entries[i].key == key) {
      return &entries[i].action;
    }
  }
  return nullptr;
}

void CellInput::press(Key key) {
  if (mDown.insert(key).second && key == Key::kToggleHealth) {
    mToggleHealthPending = true;
  }
}

void CellInput::release(Key key) { mDown.erase(key); }

bool CellInput::isDown(Key key) const { return mDown.count(key) != 0; }

void CellInput::clear() {
  mDown.clear();
  mToggleHealthPending = false;
}

void CellInput::reset() { clear(); }

Frame CellInput::frame() const {
  Frame frame;
  for (const Key key : mDown) {
    const Action* action = Table::lookup(key);
    if (action == nullptr) {
      continue;
    }
    switch (*action) {
      case Action::kThrustForward:
        frame.thrustForward = true;
        break;
      case Action::kThrustBack:
        frame.thrustBack = true;
        break;
      case Action::kThrustLeft:
        frame.thrustLeft = true;
        break;
      case Action::kThrustRight:
        frame.thrustRight = true;
        break;
      case Action::kBoost:
        frame.boost = true;
        break;
      default:
        break;
    }
  }
  return frame;
}

CameraDirs CellInput::camera() const {
  CameraDirs dirs;
  dirs.left = isDown(Key::kLeft);
  dirs.right = isDown(Key::kRight);
  dirs.up = isDown(Key::kUp);
  dirs.down = isDown(Key::kDown);
  return dirs;
}

bool CellInput::wantsQuit() const { return isDown(Key::kEscape); }

bool CellInput::takeToggleHealth() {
  const bool pending = mToggleHealthPending;
  mToggleHealthPending = false;
  return pending;
}

openspore::gamemode::InputEvent CellInput::keyDown(Key key) const {
  openspore::gamemode::InputEvent event;
  event.type = openspore::gamemode::InputEventType::kKeyDown;
  event.virtualKey = static_cast<std::uint32_t>(key);
  event.key = key;
  return event;
}

openspore::gamemode::InputEvent CellInput::keyUp(Key key) const {
  openspore::gamemode::InputEvent event;
  event.type = openspore::gamemode::InputEventType::kKeyUp;
  event.virtualKey = static_cast<std::uint32_t>(key);
  event.key = key;
  return event;
}

openspore::gamemode::InputEvent CellInput::mouseMove(float x, float y) const {
  openspore::gamemode::InputEvent event;
  event.type = openspore::gamemode::InputEventType::kMouseMove;
  event.x = x;
  event.y = y;
  return event;
}

openspore::gamemode::InputEvent CellInput::mouseDown(
    float x, float y, openspore::gamemode::MouseButton button) const {
  openspore::gamemode::InputEvent event;
  event.type = openspore::gamemode::InputEventType::kMouseDown;
  event.x = x;
  event.y = y;
  event.button = button;
  return event;
}

openspore::gamemode::InputEvent CellInput::mouseUp(
    float x, float y, openspore::gamemode::MouseButton button) const {
  openspore::gamemode::InputEvent event;
  event.type = openspore::gamemode::InputEventType::kMouseUp;
  event.x = x;
  event.y = y;
  event.button = button;
  return event;
}

openspore::gamemode::InputEvent CellInput::mouseWheel(float x, float y,
                                                      float wheel) const {
  openspore::gamemode::InputEvent event;
  event.type = openspore::gamemode::InputEventType::kMouseWheel;
  event.x = x;
  event.y = y;
  event.wheel = wheel;
  return event;
}

}  // namespace openspore::cellinput
