// CS-21: cell combat rules — table-driven from the decompiled constants.
#include "Combat.hpp"

#include <cmath>
#include <cstdio>

namespace {

int g_failures = 0;

void check(bool cond, const char* label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

using openspore::sim::CombatStatus;
using openspore::sim::evaluateAttack;
using openspore::sim::getDamageAmount;
using openspore::sim::getScaleDifferenceWithPlayer;
using openspore::sim::ScaleDifference;
using openspore::sim::shouldFlee;
using openspore::sim::shouldNotAttack;

void testScaleDifference() {
  check(getScaleDifferenceWithPlayer(5, 5) == ScaleDifference::Equal,
        "diff: equal -> Equal");
  check(getScaleDifferenceWithPlayer(6, 5) == ScaleDifference::Larger,
        "diff: +1 -> Larger");
  check(getScaleDifferenceWithPlayer(7, 5) == ScaleDifference::MuchLarger,
        "diff: +2 -> MuchLarger");
  check(getScaleDifferenceWithPlayer(10, 5) == ScaleDifference::MuchLarger,
        "diff: +5 clamps -> MuchLarger");
  check(getScaleDifferenceWithPlayer(4, 5) == ScaleDifference::Smaller,
        "diff: -1 -> Smaller");
  check(getScaleDifferenceWithPlayer(3, 5) == ScaleDifference::MuchSmaller,
        "diff: -2 -> MuchSmaller");
  check(getScaleDifferenceWithPlayer(1, 5) == ScaleDifference::MuchSmaller,
        "diff: -4 clamps -> MuchSmaller");
}

void testDamagePlayerAttacks() {
  openspore::sim::AttackInputs in;
  in.attackerIsPlayer = true;
  in.playerScale = 5;
  in.victimScale = 3;  // Smaller
  check(getDamageAmount(in) == 6, "dmg: player vs smaller -> 6");
  in.victimScale = 5;  // Equal
  in.playerFlag = 2;
  check(getDamageAmount(in) == 2, "dmg: player vs equal (flag 2) -> 2");
  in.playerFlag = 1;
  check(getDamageAmount(in) == 3, "dmg: player vs equal (flag 1) -> 3");
  in.victimScale = 6;  // Larger
  check(getDamageAmount(in) == 1, "dmg: player vs larger -> 1");
}

void testDamageMatrix() {
  // Two non-player cells: damage = kDamageMatrix[attackerDiff*5 + victimDiff].
  openspore::sim::AttackInputs in;
  in.playerScale = 5;
  in.attackerScale = 5;
  in.victimScale = 5;  // both Equal (diff 2,2) -> matrix[12] = 2
  check(getDamageAmount(in) == 2, "dmg matrix: equal vs equal -> 2");
  in.attackerScale = 6;  // Larger (3)
  in.victimScale = 4;    // Smaller (1) -> matrix[3*5+1]=16 = 6
  check(getDamageAmount(in) == 6, "dmg matrix: larger vs smaller -> 6");
  in.attackerScale = 4;  // Smaller (1)
  in.victimScale = 6;    // Larger (3) -> matrix[1*5+3]=8 = 0
  check(getDamageAmount(in) == 0, "dmg matrix: smaller vs larger -> 0");
}

void testDamageVsPlayer() {
  openspore::sim::AttackInputs in;
  in.victimIsPlayer = true;
  in.playerScale = 5;
  in.attackerScale = 7;  // MuchLarger
  check(getDamageAmount(in) == 6, "dmg: much-larger vs player -> 6");
  in.attackerScale = 6;  // Larger
  check(getDamageAmount(in) == 3, "dmg: larger vs player -> 3");
  in.attackerScale = 5;  // Equal
  check(getDamageAmount(in) == 2, "dmg: equal vs player -> 2");
  in.attackerScale = 4;  // Smaller
  check(getDamageAmount(in) == 1, "dmg: smaller vs player -> 1");
}

void testHealthAndFlee() {
  openspore::sim::HealthState health{15, 10};
  auto damaged = openspore::sim::applyDamage(health, 20);
  check(damaged.status == CombatStatus::success && damaged.health == 0,
        "health: damage clamps at zero");
  auto healed = openspore::sim::clampHealth(30, 10);
  check(healed.status == CombatStatus::success && healed.health == 10,
        "health: values clamp at maximum");
  check(openspore::sim::applyDamage(health, -1).status == CombatStatus::failure,
        "health: negative damage fails explicitly");

  openspore::sim::FleeInputs flee;
  flee.threatPresent = true;
  flee.distance = 3;
  flee.radius = 4;
  check(shouldFlee(flee).flee, "flee: nearby threat triggers escape");
  flee.distance = 5;
  check(!shouldFlee(flee).flee, "flee: distant threat does not trigger escape");
  flee.distance = 3;
  flee.health = 0;
  check(!shouldFlee(flee).flee, "flee: dead cell does not flee");
}

void testAttackResult() {
  openspore::sim::AttackInputs inputs;
  inputs.attackerIsPlayer = true;
  inputs.playerScale = 5;
  inputs.victimScale = 4;
  openspore::sim::AttackGate gate;
  gate.playerScale = 5;
  gate.cell1Scale = 5;
  auto allowed = evaluateAttack(inputs, gate);
  check(allowed.status == CombatStatus::success && allowed.allowed &&
            allowed.damage == 6,
        "attack: permitted attack reports damage");
  gate.sameResource = true;
  auto blocked = evaluateAttack(inputs, gate);
  check(blocked.status == CombatStatus::success && !blocked.allowed &&
            blocked.damage == 0,
        "attack: same-resource gate blocks damage");
  gate.sameResource = false;
  gate.attackerHealth = 0;
  check(!evaluateAttack(inputs, gate).allowed,
        "attack: dead attacker is gated");
}

void testShouldNotAttack() {
  openspore::sim::AttackGate g;
  g.playerScale = 5;

  openspore::sim::AttackGate s = g;
  s.sameResource = true;
  check(shouldNotAttack(s), "gate: same resource -> skip");

  s = g;
  s.cell1Bypass = true;
  check(!shouldNotAttack(s), "gate: field_112 set -> allow");

  s = g;
  s.targetIsPlayer = true;
  s.resFlag300 = true;
  check(shouldNotAttack(s), "gate: passive flag vs player -> skip");

  s = g;
  s.targetIsPlayer = true;
  s.resFlag301 = true;
  s.cell1Scale = 4;
  check(shouldNotAttack(s), "gate: smaller-than-player (flag 301) -> skip");

  s = g;
  s.targetIsPlayer = true;
  s.resFlag301 = true;
  s.cell1Scale = 6;
  check(!shouldNotAttack(s), "gate: larger-than-player (flag 301) -> allow");

  s = g;
  s.cell1Territory = 7;
  s.cell2Territory = 7;
  check(shouldNotAttack(s), "gate: same non-zero territory -> skip");

  s = g;
  check(!shouldNotAttack(s), "gate: default -> allow");
}

}  // namespace

int main() {
  testScaleDifference();
  testDamagePlayerAttacks();
  testDamageMatrix();
  testDamageVsPlayer();
  testHealthAndFlee();
  testAttackResult();
  testShouldNotAttack();
  if (g_failures == 0) {
    std::printf("combat_test: ALL PASS\n");
    return 0;
  }
  std::printf("combat_test: %d FAILURES\n", g_failures);
  return 1;
}
