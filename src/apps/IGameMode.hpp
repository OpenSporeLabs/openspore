// IGameMode (CS-28, clean-room).
//
// The original cCellModeStrategy (Simulator::Cell) sits behind a 27-slot
// virtual table at 0x01485550. Ten of those slots resolve to the game-mode
// lifecycle + input surface that the cGameModeManager drives; the rest are
// unexported in the SDK. The resolved slots, in vtable order:
//   [6]  Initialize   [7] Dispose       [8] OnEnter
//   [9]  OnExit       [11] OnKeyDown   [12] OnMouseMove
//   [13] OnMouseDown  [14] OnMouseUp   [16] OnMouseWheel
//   [17] Update
// This is the abstract base the mode strategy implements; the manager calls
// exactly these slots to enter / update / leave / tear down a mode.
#pragma once

#include <cstdint>

namespace openspore::gamemode {

// One routed input event: the virtual-key code + modifier flags OnKeyDown
// takes, plus the mouse position / wheel delta the mouse slots take.
struct InputEvent {
  std::uint32_t virtualKey = 0;
  std::uint32_t modifiers = 0;
  float x = 0.0F;
  float y = 0.0F;
};

class IGameMode {
 public:
  virtual ~IGameMode() = default;

  // vtable [6] Initialize: allocate + reset the mode's owned resources.
  virtual void initialize() = 0;
  // vtable [7] Dispose: tear down + free.
  virtual void dispose() = 0;
  // vtable [8] OnEnter: enter the mode (start the display, enable input).
  virtual void onEnter() = 0;
  // vtable [9] OnExit: leave the mode (reset globals, disable input).
  virtual void onExit() = 0;
  // vtable [11]
  virtual void onKeyDown(const InputEvent &) = 0;
  // vtable [12]
  virtual void onMouseMove(const InputEvent &) = 0;
  // vtable [13]
  virtual void onMouseDown(const InputEvent &) = 0;
  // vtable [14]
  virtual void onMouseUp(const InputEvent &) = 0;
  // vtable [16]
  virtual void onMouseWheel(const InputEvent &) = 0;
  // vtable [17] Update: the per-frame tick.
  virtual void update(float delta) = 0;
};

} // namespace openspore::gamemode
