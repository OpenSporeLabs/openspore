// Obj36C — implementation of the clean-room replacement.
// Pure and deterministic: output depends only on (deltaTime, sCellGame, cam,
// plane). No globals, no wall clock, no rand.
#include "Replace.hpp"

#include <cmath>

namespace openspore::replace {
namespace {

// Travel-orientation stand-in for the original's FUN_0069b600(&orient,
// &delta, &N): a yaw quaternion around +Y built from the horizontal travel
// delta, in the sim's heading convention (fwd = (sin h, 0, cos h), so
// h = 0 faces +Z and h increases toward +X). LAYOUT INFERRED (see header).
void travelOrientation(const float delta[3], float orient[4]) {
  const float h = std::atan2f(delta[0], delta[2]);
  orient[0] = 0.0F;
  orient[1] = std::sinf(0.5F * h);
  orient[2] = 0.0F;
  orient[3] = std::cosf(0.5F * h);
}

}  // namespace

void replacement_MovePlayerToMousePosition(float deltaTime, SCellGameView* sCellGame,
                                           const CameraView* cam, const sim::MovementPlane* plane) {
  // Real cdecl arg. The original spends it in the per-frame update
  // (FUN_00e5b2e0(deltaTime)); the ray-plane steering below never reads it.
  static_cast<void>(deltaTime);

  // 1. Lock/paused guard (OBSERVED: sCellGame+0x5158 != 0 -> return).
  if (sCellGame->lockFlag != 0) {
    return;
  }

  // 2. Fetch the player entity (stand-in: the resolved pointer; the real
  //    bytes are the pool index — see header). Null -> return.
  SPlayerView* player = reinterpret_cast<SPlayerView*>(sCellGame->playerRef);
  if (player == nullptr) {
    return;
  }

  // 3. Camera ray ∩ movement plane, with the OBSERVED guards exactly
  //    (denom == 0.0 -> no hit; t < 0.0 -> no hit).
  const float denom = cam->dir[0] * plane->normal[0] + cam->dir[1] * plane->normal[1] +
                      cam->dir[2] * plane->normal[2];
  if (denom == 0.0F) {
    return;
  }
  const float t = ((plane->point[0] - cam->origin[0]) * plane->normal[0] +
                   (plane->point[1] - cam->origin[1]) * plane->normal[1] +
                   (plane->point[2] - cam->origin[2]) * plane->normal[2]) /
                  denom;
  if (t < 0.0F) {
    return;
  }

  // 4. Hit: write the target, set the moving flag, face the travel delta.
  for (int i = 0; i < 3; ++i) {
    player->targetPos[i] = cam->origin[i] + cam->dir[i] * t;
  }
  sCellGame->movingFlag = 1;

  const float delta[3] = {player->currentPos[0] - player->targetPos[0],
                          player->currentPos[1] - player->targetPos[1],
                          player->currentPos[2] - player->targetPos[2]};
  travelOrientation(delta, player->orient);
}

}  // namespace openspore::replace
