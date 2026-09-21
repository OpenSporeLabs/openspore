// Obj36D — EVIDENCE-NOT-TRUTH reference implementation.
//
// Line-by-line transcription of the DECOMPILED body (Ghidra 12.1.2 capture,
// tools/re/data/decompiled/MovePlayerToMousePosition.c). The decompiler's
// cast types are guesses; the behavior is "what the decompiler tells us",
// not a traced runtime. The transcription boundary (what is deliberately
// omitted, and why none of it touches a compared field):
//   - FUN_00e5b2e0(deltaTime) / FUN_00743b50(): per-frame environment
//     updates (lighting world tick etc.). Omitted: environment side effects;
//     deltaTime is the only real arg and is unused by the steering math.
//   - FUN_00e4ce40 +0xd4 camera-mode read, FUN_00e82130(), and the sCellUI
//     +0x24/+0x26 selection gating: UI/environment state. Omitted: they gate
//     the ray cast in the original; every differential case here feeds an
//     already-resolved camera ray (the post-gate state).
//   - The sCellGame+0x411c pool lookup FUN_00b721d0(index) is condensed to
//     reading those 4 bytes as the resolved entity pointer (32-bit stand-in,
//     documented in Replace.hpp).
//
// A live-runtime differential against the original is NOT possible headless:
// cell mode is unreachable. See docs/REPLACEMENT-DIFF.md.
#include <cmath>

#include "Replace.hpp"

namespace openspore::replace {
namespace {

// FUN_0069b600(&orient, &delta, &N) stand-in (INFERRED layout, 4 floats at
// player+0x14..0x20): yaw quaternion around +Y from the horizontal travel
// delta, sim heading convention (fwd = (sin h, 0, cos h)).
void referenceTravelOrientation(const float delta[3], float orient[4]) {
  const float h = std::atan2f(delta[0], delta[2]);
  orient[0] = 0.0F;
  orient[1] = std::sinf(0.5F * h);
  orient[2] = 0.0F;
  orient[3] = std::cosf(0.5F * h);
}

}  // namespace

void reference_MovePlayerToMousePosition(float deltaTime, SCellGameView* sCellGame,
                                         const CameraView* cam, const sim::MovementPlane* plane) {
  // if (*(int *)(sCellGame + 0x5158) != 0) return;
  static_cast<void>(deltaTime);  // consumed only by the omitted FUN_00e5b2e0
  if (sCellGame->lockFlag != 0) {
    return;
  }

  // iVar2 = FUN_00b721d0(*(undefined4 *)(sCellGame + 0x411c)); if (!iVar2) return;
  SPlayerView* player = reinterpret_cast<SPlayerView*>(sCellGame->playerRef);
  if (player == nullptr) {
    return;
  }

  // FUN_007c4900(&origin, &dir);  (camera origin + view ray)
  const float origin[3] = {cam->origin[0], cam->origin[1], cam->origin[2]};
  const float dir[3] = {cam->dir[0], cam->dir[1], cam->dir[2]};

  // plane normal DAT_015a7c40/44/48, point DAT_016b3c28/2c/30 (values
  // APPROXIMATION — never read at runtime)
  const float N[3] = {plane->normal[0], plane->normal[1], plane->normal[2]};
  const float P[3] = {plane->point[0], plane->point[1], plane->point[2]};

  // denom = dir·N  (decomp: fStack_30); if (denom != 0.0)
  const float denom = dir[0] * N[0] + dir[1] * N[1] + dir[2] * N[2];
  if (denom == 0.0F) {
    return;
  }

  // t = -(origin·N + offset) / denom,  offset = -P·N  (plane N·x + d = 0)
  const float planeOffset = -(P[0] * N[0] + P[1] * N[1] + P[2] * N[2]);
  const float t = -((origin[0] * N[0] + origin[1] * N[1] + origin[2] * N[2]) + planeOffset) / denom;
  if (t < 0.0F) {
    return;
  }

  // *(player+0x08/0c/10) = origin + dir·t   (target position)
  player->targetPos[0] = origin[0] + dir[0] * t;
  player->targetPos[1] = origin[1] + dir[1] * t;
  player->targetPos[2] = origin[2] + dir[2] * t;

  // *(sCellGame + 0x5190 + 0xe0) = 1   ("moving" flag)
  sCellGame->movingFlag = 1;

  // delta = -(target - current);  current at player+0x4c/0x50/0x54
  const float delta[3] = {-(player->targetPos[0] - player->currentPos[0]),
                          -(player->targetPos[1] - player->currentPos[1]),
                          -(player->targetPos[2] - player->currentPos[2])};

  // FUN_0069b600(&orient, &delta, &N);  *(player+0x14..0x20) = orient
  referenceTravelOrientation(delta, player->orient);
}

}  // namespace openspore::replace
