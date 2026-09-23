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

const Action *Table::lookup(Key key) {
  for (std::size_t i = 0; i < count; ++i) {
    if (entries[i].key == key) {
      return &entries[i].action;
    }
  }
  return nullptr;
}

void CellInput::press(Key key) {
  mDown.insert(static_cast<std::uint16_t>(key));
  if (key == Key::kToggleHealth) {
    mToggleHealthPending = true;
  }
}

void CellInput::release(Key key) {
  mDown.erase(static_cast<std::uint16_t>(key));
}

bool CellInput::isDown(Key key) const {
  return mDown.count(static_cast<std::uint16_t>(key)) != 0;
}

void CellInput::clear() {
  mDown.clear();
}

Frame CellInput::frame() const {
  Frame f;
  for (const std::uint16_t k : mDown) {
    const Action *a = Table::lookup(static_cast<Key>(k));
    if (a == nullptr) {
      continue;
    }
    switch (*a) {
      case Action::kThrustForward:
        f.thrustForward = true;
        break;
      case Action::kThrustBack:
        f.thrustBack = true;
        break;
      case Action::kThrustLeft:
        f.thrustLeft = true;
        break;
      case Action::kThrustRight:
        f.thrustRight = true;
        break;
      case Action::kBoost:
        f.boost = true;
        break;
      default:
        break;
    }
  }
  return f;
}

CameraDirs CellInput::camera() const {
  CameraDirs c;
  c.left = isDown(Key::kLeft);
  c.right = isDown(Key::kRight);
  c.up = isDown(Key::kUp);
  c.down = isDown(Key::kDown);
  return c;
}

bool CellInput::wantsQuit() const {
  return isDown(Key::kEscape);
}

bool CellInput::takeToggleHealth() {
  const bool p = mToggleHealthPending;
  mToggleHealthPending = false;
  return p;
}

} // namespace openspore::cellinput
