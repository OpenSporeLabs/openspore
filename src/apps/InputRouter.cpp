#include "InputRouter.hpp"

namespace openspore::input {

void InputRouter::setActiveMode(IGameMode* mode) {
  mRegistry = nullptr;
  mMode = mode;
}

void InputRouter::setRegistry(IGameModeRegistry* registry) {
  mRegistry = registry;
  mMode = nullptr;
}

void InputRouter::clear() {
  mRegistry = nullptr;
  mMode = nullptr;
}

IGameMode* InputRouter::activeMode() const {
  return mRegistry == nullptr ? mMode : mRegistry->active();
}

RouteResult InputRouter::route(const InputEvent& event) {
  switch (event.type) {
    case InputEventType::kKeyDown:
    case InputEventType::kKeyUp:
    case InputEventType::kMouseMove:
    case InputEventType::kMouseDown:
    case InputEventType::kMouseUp:
    case InputEventType::kMouseWheel:
      break;
    default:
      return RouteResult::kUnsupportedEvent;
  }

  IGameMode* mode = activeMode();
  if (mode == nullptr) {
    return RouteResult::kNoActiveMode;
  }

  switch (event.type) {
    case InputEventType::kKeyDown:
      mode->onKeyDown(event);
      return RouteResult::kRouted;
    case InputEventType::kKeyUp:
      mode->onKeyUp(event);
      return RouteResult::kRouted;
    case InputEventType::kMouseMove:
      mode->onMouseMove(event);
      return RouteResult::kRouted;
    case InputEventType::kMouseDown:
      mode->onMouseDown(event);
      return RouteResult::kRouted;
    case InputEventType::kMouseUp:
      mode->onMouseUp(event);
      return RouteResult::kRouted;
    case InputEventType::kMouseWheel:
      mode->onMouseWheel(event);
      return RouteResult::kRouted;
  }

  return RouteResult::kUnsupportedEvent;
}

}  // namespace openspore::input
