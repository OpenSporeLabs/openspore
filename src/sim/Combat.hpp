// Cell combat rules (clean-room):
//   GetScaleDifferenceWithPlayer @ 00e57340
//   GetDamageAmount              @ 00e58980
//   ShouldNotAttack              @ 00e57460
//
// All three reduce to pure functions over scale buckets + a few resource flags,
// so they are testable table-driven from the decompiled constants.
#pragma once

#include <cstdint>

namespace openspore::sim {

// ScaleDifference (SDK enum): how a cell compares to the player.
enum class ScaleDifference : int32_t {
  MuchSmaller = 0,
  Smaller = 1,
  Equal = 2,
  Larger = 3,
  MuchLarger = 4,
};

// GetScaleDifferenceWithPlayer: the other cell's bucket key minus the player's,
// centered so Equal == 2, clamped to [MuchSmaller, MuchLarger].
inline ScaleDifference getScaleDifferenceWithPlayer(int32_t otherScale,
                                                    int32_t playerScale) {
  int32_t d = otherScale - playerScale + 2;
  if (d < 0) {
    d = 0;
  }
  if (d > 4) {
    d = 4;
  }
  return static_cast<ScaleDifference>(d);
}

// The 5x5 damage matrix for two non-player cells (local_64, VERIFIED from the
// decompilation): row = attacker difference, col = victim difference.
inline constexpr int32_t kDamageMatrix[25] = {
    0, 0, 0, 0, 0,  // attacker MuchSmaller
    6, 2, 1, 0, 0,  // attacker Smaller
    6, 6, 2, 0, 0,  // attacker Equal
    6, 6, 6, 2, 0,  // attacker Larger
    6, 6, 6, 6, 2,  // attacker MuchLarger
};

struct AttackInputs {
  bool attackerIsPlayer = false;
  bool victimIsPlayer = false;
  int32_t attackerScale = 0;  // attacker bucket key (1..10)
  int32_t victimScale = 0;    // victim bucket key
  int32_t playerScale = 0;    // player bucket key
  int32_t playerFlag = 0;     // sCellGame[0x5190]+0x7c (2 vs not)
};

// GetDamageAmount: damage dealt by `attacker` to `victim` (0..6).
inline int32_t getDamageAmount(const AttackInputs &in) {
  if (in.attackerIsPlayer) {
    switch (getScaleDifferenceWithPlayer(in.victimScale, in.playerScale)) {
      case ScaleDifference::MuchSmaller:
      case ScaleDifference::Smaller:
        return 6;  // the player crushes anything smaller
      case ScaleDifference::Equal:
        return (in.playerFlag != 2) + 2;  // 2 or 3
      case ScaleDifference::Larger:
      case ScaleDifference::MuchLarger:
        return 1;  // the player barely dents anything bigger
    }
    return 0;
  }
  if (!in.victimIsPlayer) {
    auto a = getScaleDifferenceWithPlayer(in.attackerScale, in.playerScale);
    auto v = getScaleDifferenceWithPlayer(in.victimScale, in.playerScale);
    return kDamageMatrix[static_cast<int32_t>(a) * 5 + static_cast<int32_t>(v)];
  }
  // A non-player attacks the player.
  switch (getScaleDifferenceWithPlayer(in.attackerScale, in.playerScale)) {
    case ScaleDifference::MuchSmaller:
    case ScaleDifference::Smaller:
      return 1;
    case ScaleDifference::Equal:
      return 2;
    case ScaleDifference::Larger:
      return 3;
    case ScaleDifference::MuchLarger:
      return 6;
  }
  return 0;
}

struct AttackGate {
  bool sameResource = false;     // cell1->mCellResource == cell2->mCellResource
  bool cell1Bypass = false;      // cell1 field_112 (bool, after mIsInvulnerable)
  bool cell2Bypass = false;      // cell2 field_112
  bool targetIsPlayer = false;   // cell2 is the player
  bool resFlag301 = false;       // attacker resource byte 0x301
  bool resFlag300 = false;       // attacker resource byte 0x300
  int32_t cell1Territory = 0;    // attacker resource int 0x2fc
  int32_t cell2Territory = 0;    // target resource int 0x2fc
  int32_t cell1Scale = 0;        // attacker bucket key
  int32_t playerScale = 0;       // player bucket key
};

// ShouldNotAttack: true when the attack should be skipped.
inline bool shouldNotAttack(const AttackGate &g) {
  if (g.sameResource) {
    return true;
  }
  if (g.cell1Bypass || g.cell2Bypass) {
    return false;
  }
  if (g.targetIsPlayer) {
    if (g.resFlag300) {
      return true;
    }
    if (g.resFlag301 &&
        getScaleDifferenceWithPlayer(g.cell1Scale, g.playerScale) ==
            ScaleDifference::Smaller) {
      return true;
    }
  }
  if (g.cell1Territory != 0 && g.cell1Territory == g.cell2Territory) {
    return true;
  }
  return false;
}

} // namespace openspore::sim
