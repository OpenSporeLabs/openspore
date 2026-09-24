#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace openspore::gamemode {

enum class InputEventType : std::uint8_t {
  kKeyDown,
  kKeyUp,
  kMouseMove,
  kMouseDown,
  kMouseUp,
  kMouseWheel,
};

enum class InputKey : std::uint16_t {
  kUnknown = 0,
  kW = 2,
  kS = 20,
  kA = 4,
  kD = 32,
  kShift = 42,
  kEscape = 41,
  kLeft = 80,
  kRight = 79,
  kUp = 82,
  kDown = 81,
  kToggleHealth = 1,
};

enum class MouseButton : std::uint8_t {
  kUnknown = 0,
  kLeft,
  kRight,
  kMiddle,
};

struct InputEvent {
  std::uint32_t virtualKey = 0;
  std::uint32_t modifiers = 0;
  float x = 0.0F;
  float y = 0.0F;
  InputEventType type = InputEventType::kKeyDown;
  InputKey key = InputKey::kUnknown;
  MouseButton button = MouseButton::kUnknown;
  float wheel = 0.0F;
};

using NormalizedInput = InputEvent;

class IGameMode {
public:
  virtual ~IGameMode() = default;

  virtual void initialize() = 0;
  virtual void dispose() = 0;
  virtual void onEnter() = 0;
  virtual void onExit() = 0;
  virtual void onKeyDown(const InputEvent &) = 0;
  virtual void onKeyUp(const InputEvent &) {}
  virtual void onMouseMove(const InputEvent &) = 0;
  virtual void onMouseDown(const InputEvent &) = 0;
  virtual void onMouseUp(const InputEvent &) = 0;
  virtual void onMouseWheel(const InputEvent &) = 0;
  virtual void update(float delta) = 0;
};

class IGameModeRegistry {
public:
  virtual ~IGameModeRegistry() = default;

  virtual bool registerMode(IGameMode *mode, std::string name = {}) = 0;
  virtual bool activate(std::uint32_t index) = 0;
  virtual bool activateByName(std::string_view name) = 0;
  virtual bool activate_by_name(std::string_view name) = 0;
  virtual IGameMode *active() const = 0;
};

}
