#pragma once

#include "IGameMode.hpp"

namespace openspore::input {

using openspore::gamemode::IGameMode;
using openspore::gamemode::IGameModeRegistry;
using openspore::gamemode::InputEvent;
using openspore::gamemode::InputEventType;

enum class RouteResult {
  kRouted,
  kNoActiveMode,
  kUnsupportedEvent,
};

class IInputRouter {
 public:
  virtual ~IInputRouter() = default;
  virtual void setActiveMode(IGameMode* mode) = 0;
  virtual void setRegistry(IGameModeRegistry* registry) = 0;
  virtual void clear() = 0;
  virtual IGameMode* activeMode() const = 0;
  virtual RouteResult route(const InputEvent& event) = 0;
};

class InputRouter final : public IInputRouter {
 public:
  void setActiveMode(IGameMode* mode) override;
  void setRegistry(IGameModeRegistry* registry) override;
  void clear() override;
  IGameMode* activeMode() const override;
  RouteResult route(const InputEvent& event) override;

 private:
  IGameModeRegistry* mRegistry = nullptr;
  IGameMode* mMode = nullptr;
};

}  // namespace openspore::input

namespace openspore::gamemode {
using input::IInputRouter;
using input::InputRouter;
using input::RouteResult;
}  // namespace openspore::gamemode
