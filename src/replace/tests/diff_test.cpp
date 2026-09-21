// Obj36D — differential driver: decompilation-derived reference vs the
// clean-room replacement.
//
// IMPORTANT EVIDENCE BOUNDARY: there is NO live cell-mode runtime available
// headless, so this differential is against a DECOMPILED REFERENCE
// (Reference.cpp, EVIDENCE-NOT-TRUTH), not against the running original.
// A green run proves the replacement reproduces the decompilation reference;
// it is NOT a live-runtime verification. See docs/REPLACEMENT-DIFF.md.
//
// Deterministic input cases (a few camera rays × planes × mouse offsets,
// plus lock-set, ray-parallel-to-plane, ray-behind-origin, and null-player
// cases). Every output field is compared with an explicit tolerance:
// position x/y/z (float, tol 1e-6), orientation quaternion q0..q3 (float,
// tol 1e-6), moving flag (int, exact). Exit code 0 iff ALL match.
#include <sys/mman.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../Replace.hpp"

namespace {

using openspore::replace::CameraView;
using openspore::replace::SCellGameView;
using openspore::replace::SPlayerView;

constexpr float kFloatTol = 1e-6F;

// The real 32-bit process stores the player pointer in the 4-byte playerRef
// field (Obj36C stand-in). On the 64-bit test host we must therefore keep
// the test buffers inside the low 4 GiB so the 32-bit address stands in
// faithfully: MAP_32BIT guarantees that.
void* alloc32(size_t bytes) {
  void* p =
      mmap(nullptr, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
  if (p == MAP_FAILED) {
    std::printf("MAP_32BIT failed\n");
    std::exit(1);
  }
  return p;
}

struct Case {
  const char* name;
  CameraView cam;
  openspore::sim::MovementPlane plane;
  float currentPos[3];
  float initOrient[4];
  int32_t lock = 0;
  bool nullPlayer = false;
};

float norm3(const float v[3]) { return std::sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); }

void normalize3(float v[3]) {
  const float l = norm3(v);
  v[0] /= l;
  v[1] /= l;
  v[2] /= l;
}

// Fresh, identically-initialized state buffers for one case.
void initState(const Case& c, SCellGameView* game, SPlayerView* player, uint32_t* playerAddrOut) {
  std::memset(game, 0, sizeof(*game));
  std::memset(player, 0, sizeof(*player));
  for (int i = 0; i < 3; ++i) {
    player->currentPos[i] = c.currentPos[i];
  }
  for (int i = 0; i < 4; ++i) {
    player->orient[i] = c.initOrient[i];
  }
  game->lockFlag = c.lock;
  if (c.nullPlayer) {
    game->playerRef = 0;
    *playerAddrOut = 0;
  } else {
    const uintptr_t up = reinterpret_cast<uintptr_t>(player);
    if (up >> 32 != 0) {
      std::printf("player buffer escaped the low 4 GiB (%#llx)\n",
                  static_cast<unsigned long long>(up));
      std::exit(1);
    }
    *playerAddrOut = static_cast<uint32_t>(up);
    game->playerRef = *playerAddrOut;
  }
}

struct FieldResult {
  const char* field;
  float refV, repV;
  int refI, repI;
  bool isInt;
  bool match;
};

}  // namespace

int main() {
  Case cases[] = {
      // 1. Straight-down ray at the origin: t = 12, target = (0,0,0).
      {"normal_hit_center",
       {{0.0F, 12.0F, 0.0F}, {0.0F, -1.0F, 0.0F}},
       {{0.0F, 1.0F, 0.0F}, {0.0F, 0.0F, 0.0F}},
       {3.0F, 0.0F, -4.0F},
       {0.0F, 0.0F, 0.0F, 1.0F},
       0,
       false},
      // 2. Mouse offset toward +X (ray slants from an off-center eye).
      {"hit_offset_plus_x",
       {{10.0F, 8.0F, -14.0F}, {-0.6F, -0.55F, 0.55F}},
       {{0.0F, 1.0F, 0.0F}, {0.0F, 0.0F, 0.0F}},
       {-2.0F, 0.0F, 1.0F},
       {0.0F, 0.0F, 0.0F, 1.0F},
       0,
       false},
      // 3. Mirror: mouse offset toward -X.
      {"hit_offset_minus_x",
       {{-10.0F, 8.0F, -14.0F}, {0.6F, -0.55F, 0.55F}},
       {{0.0F, 1.0F, 0.0F}, {0.0F, 0.0F, 0.0F}},
       {2.0F, 0.0F, 1.0F},
       {0.0F, 0.0F, 0.0F, 1.0F},
       0,
       false},
      // 4. Non-default plane: the z = 2 wall, oblique ray.
      {"hit_nontrivial_plane",
       {{1.0F, 5.0F, -3.0F}, {0.0F, -0.6F, 0.8F}},
       {{0.0F, 0.0F, 1.0F}, {0.0F, 0.0F, 2.0F}},
       {0.0F, 0.0F, 0.0F},
       {0.0F, 0.0F, 0.0F, 1.0F},
       0,
       false},
      // 5. Ray parallel to the plane (denom == 0): no hit, no writes.
      {"ray_parallel_to_plane",
       {{5.0F, 7.0F, 0.0F}, {1.0F, 0.0F, 0.0F}},
       {{0.0F, 1.0F, 0.0F}, {0.0F, 0.0F, 0.0F}},
       {3.0F, 0.0F, -4.0F},
       {0.0F, 0.0F, 0.0F, 1.0F},
       0,
       false},
      // 6. Ray pointing away from the plane (t < 0): no hit, no writes.
      {"ray_behind_origin",
       {{0.0F, -5.0F, 2.0F}, {0.0F, -1.0F, 0.0F}},
       {{0.0F, 1.0F, 0.0F}, {0.0F, 0.0F, 0.0F}},
       {3.0F, 0.0F, -4.0F},
       {0.0F, 0.0F, 0.0F, 1.0F},
       0,
       false},
      // 7. Lock/paused flag set: early return, nothing written.
      {"lock_set",
       {{0.0F, 12.0F, 0.0F}, {0.0F, -1.0F, 0.0F}},
       {{0.0F, 1.0F, 0.0F}, {0.0F, 0.0F, 0.0F}},
       {3.0F, 0.0F, -4.0F},
       {0.0F, 0.0F, 0.0F, 1.0F},
       1,
       false},
      // 8. Player pool lookup returned null: early return, nothing written.
      {"player_null",
       {{0.0F, 12.0F, 0.0F}, {0.0F, -1.0F, 0.0F}},
       {{0.0F, 1.0F, 0.0F}, {0.0F, 0.0F, 0.0F}},
       {3.0F, 0.0F, -4.0F},
       {0.0F, 0.0F, 0.0F, 1.0F},
       0,
       true},
  };

  int totalFields = 0;
  int mismatches = 0;
  for (const Case& c : cases) {
    // Normalize the case rays once, identically for both sides.
    CameraView cam = c.cam;
    normalize3(cam.dir);

    // Low-4GiB buffers so the 32-bit playerRef stand-in is a valid address.
    SCellGameView* gameRef = static_cast<SCellGameView*>(alloc32(sizeof(*gameRef)));
    SCellGameView* gameRep = static_cast<SCellGameView*>(alloc32(sizeof(*gameRep)));
    SPlayerView* playerRef = static_cast<SPlayerView*>(alloc32(sizeof(*playerRef)));
    SPlayerView* playerRep = static_cast<SPlayerView*>(alloc32(sizeof(*playerRep)));
    uint32_t playerAddrRef, playerAddrRep;
    initState(c, gameRef, playerRef, &playerAddrRef);
    initState(c, gameRep, playerRep, &playerAddrRep);

    openspore::replace::reference_MovePlayerToMousePosition(0.0166667F, gameRef, &cam, &c.plane);
    openspore::replace::replacement_MovePlayerToMousePosition(0.0166667F, gameRep, &cam, &c.plane);

    FieldResult fields[] = {
        {"pos_x", playerRef->targetPos[0], playerRep->targetPos[0], 0, 0, false,
         std::fabsf(playerRef->targetPos[0] - playerRep->targetPos[0]) <= kFloatTol},
        {"pos_y", playerRef->targetPos[1], playerRep->targetPos[1], 0, 0, false,
         std::fabsf(playerRef->targetPos[1] - playerRep->targetPos[1]) <= kFloatTol},
        {"pos_z", playerRef->targetPos[2], playerRep->targetPos[2], 0, 0, false,
         std::fabsf(playerRef->targetPos[2] - playerRep->targetPos[2]) <= kFloatTol},
        {"orient_qx", playerRef->orient[0], playerRep->orient[0], 0, 0, false,
         std::fabsf(playerRef->orient[0] - playerRep->orient[0]) <= kFloatTol},
        {"orient_qy", playerRef->orient[1], playerRep->orient[1], 0, 0, false,
         std::fabsf(playerRef->orient[1] - playerRep->orient[1]) <= kFloatTol},
        {"orient_qz", playerRef->orient[2], playerRep->orient[2], 0, 0, false,
         std::fabsf(playerRef->orient[2] - playerRep->orient[2]) <= kFloatTol},
        {"orient_qw", playerRef->orient[3], playerRep->orient[3], 0, 0, false,
         std::fabsf(playerRef->orient[3] - playerRep->orient[3]) <= kFloatTol},
        {"moving", 0, 0, gameRef->movingFlag, gameRep->movingFlag, true,
         gameRef->movingFlag == gameRep->movingFlag},
    };

    std::printf("| %s", c.name);
    for (const FieldResult& f : fields) {
      std::printf(" | %s", f.field);
    }
    std::printf(" |\n");
    for (const FieldResult& f : fields) {
      ++totalFields;
      if (!f.match) {
        ++mismatches;
      }
      if (f.isInt) {
        std::printf("| (all) | %s | %d | %d | %s | (exact) |\n", f.field, f.refI, f.repI,
                    f.match ? "MATCH" : "MISMATCH");
      } else {
        std::printf("| (all) | %s | %.9g | %.9g | %s | 1e-6 |\n", f.field, f.refV, f.repV,
                    f.match ? "MATCH" : "MISMATCH");
      }
    }
  }

  std::printf(
      "VERDICT: %d cases x 8 fields = %d field comparisons; %d mismatch(es). "
      "Differential is vs the DECOMPILED reference (EVIDENCE-NOT-TRUTH); "
      "no live cell-mode runtime exists headless — this is NOT a "
      "live-runtime verification.\n",
      static_cast<int>(sizeof(cases) / sizeof(cases[0])), totalFields, mismatches);
  return mismatches == 0 ? 0 : 1;
}
