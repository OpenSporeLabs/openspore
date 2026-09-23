// CS-31: cell animation blend state machine + event->effect mapping test.
//
// Pure C++ + stdlib; no GPU, no SPORE/ package. Checks the PlayAnimation blend
// special cases, the LoadEffectMap 3-slot selection, the contract
// event->effect ID mapping, and the InstanceEffectOnCell param-record build
// (swim-plane-point override + 1.0f sentinel + placement). Every check is
// deterministic (two calls -> identical results).
#include <cmath>
#include <cstdio>

#include "CellAnim.hpp"

namespace {

using openspore::apps::AnimBlend;
using openspore::apps::CellAnim;
using openspore::apps::EffectInstance;
using openspore::apps::animBlend;
using openspore::apps::effectIDForEvent;
using openspore::apps::instanceEffect;
using openspore::apps::selectEffectMapSlot;

int g_failures = 0;

void check(bool cond, const char *label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

} // namespace

int main() {
  using A = CellAnim;

  // ---- PlayAnimation blend state machine (00e6d200) ------------------------
  {
    AnimBlend b = animBlend(A::kIdle, A::kSwimForward, 1.0F);
    check(b.in == 0.2F && b.out == 0.2F,
          "blend: base idle->swim, scale 1.0 -> in=out=0.2");
  }
  {
    AnimBlend b = animBlend(A::kIdleBig, A::kSwimForward, 1.0F);
    check(b.in == 0.2F && b.out == 0.1F,
          "blend: current IdleBig -> out=0.1");
  }
  {
    AnimBlend b = animBlend(A::kIdleBlink1Big, A::kSwimForward, 1.0F);
    check(b.in == 0.2F && b.out == 0.1F,
          "blend: current IdleBlink1Big -> out=0.1");
  }
  {
    AnimBlend b = animBlend(A::kEatProbRetractTrgt, A::kIdle, 1.0F);
    check(b.in == 0.2F && b.out == 0.0F,
          "blend: current EatProbRetractTrgt -> out=0.0");
  }
  {
    AnimBlend b = animBlend(A::kTakeDmgElecNpc, A::kIdle, 1.0F);
    check(b.in == 0.2F && b.out == 0.0F,
          "blend: current TakeDmgElecNpc -> out=0.0");
  }
  {
    AnimBlend b = animBlend(A::kTakeDmgPoisonNpc, A::kIdle, 1.0F);
    check(b.in == 0.2F && b.out == 0.0F,
          "blend: current TakeDmgPoisonNpc -> out=0.0");
  }
  {
    AnimBlend b = animBlend(A::kIdle, A::kEatProbRetractTrgt, 1.0F);
    check(b.in == 0.0F && b.out == 0.2F,
          "blend: target EatProbRetractTrgt -> in=0.0");
  }
  {
    AnimBlend b = animBlend(A::kIdleBig, A::kEatProbRetractTrgt, 1.0F);
    check(b.in == 0.0F && b.out == 0.1F,
          "blend: current IdleBig + target Retract -> in=0.0, out=0.1");
  }
  {
    AnimBlend b = animBlend(A::kIdle, A::kSwimForward, 0.5F);
    check(b.in == 0.1F && b.out == 0.1F,
          "blend: scale 0.5 halves both times");
  }
  {
    AnimBlend a = animBlend(A::kIdleBig, A::kEatProbRetractTrgt, 1.0F);
    AnimBlend c = animBlend(A::kIdleBig, A::kEatProbRetractTrgt, 1.0F);
    check(a.in == c.in && a.out == c.out, "blend: two runs -> identical");
  }

  // ---- LoadEffectMap 3-slot selection (00e63560 switch) -------------------
  {
    check(selectEffectMapSlot(0) == 0, "slot: type 0 -> slot 0");
    check(selectEffectMapSlot(2) == 0, "slot: type 2 -> slot 0");
    check(selectEffectMapSlot(1) == 1, "slot: type 1 -> slot 1");
    check(selectEffectMapSlot(3) == 1, "slot: type 3 -> slot 1");
    check(selectEffectMapSlot(4) == 2, "slot: type 4 -> slot 2");
    check(selectEffectMapSlot(7) == -1, "slot: type 7 -> no slot");
  }

  // ---- contract event -> effect ID ----------------------------------------
  {
    check(effectIDForEvent("eat") == 1, "event: eat -> effect 1");
    check(effectIDForEvent("flee") == 2, "event: flee -> effect 2");
    check(effectIDForEvent("death") == 2, "event: death -> effect 2");
    check(effectIDForEvent("swim") == 0, "event: swim -> no effect");
    check(effectIDForEvent(nullptr) == 0, "event: null -> no effect");
  }

  // ---- InstanceEffectOnCell param-record build (00e66840) ------------------
  {
    const float mapParams[9] = {10.0F, 20.0F, 30.0F, 40.0F, 50.0F, 60.0F,
                                70.0F, 80.0F, 90.0F};
    const float planePoint[3] = {0.0F, 0.0F, 0.0F}; // CS-01: z=0 swim plane
    const float cellPos[3] = {1.5F, -2.0F, 3.0F};
    EffectInstance inst =
        instanceEffect(1, mapParams, planePoint, cellPos);
    check(inst.effectID == 1, "effect: effectID passed through");
    check(inst.params[0] == 0.0F && inst.params[1] == 0.0F &&
              inst.params[2] == 0.0F,
          "effect: plane point overrides record words 0..2");
    check(inst.params[3] == 1.0F, "effect: word 3 = 1.0f sentinel");
    check(inst.params[4] == 50.0F && inst.params[5] == 60.0F &&
              inst.params[8] == 90.0F,
          "effect: remaining record words copied verbatim");
    check(inst.pos[0] == 1.5F && inst.pos[1] == -2.0F && inst.pos[2] == 3.0F,
          "effect: placed at the cell transform");
    check(inst.active, "effect: active flag set");

    EffectInstance again = instanceEffect(1, mapParams, planePoint, cellPos);
    bool same = again.effectID == inst.effectID && again.pos[0] == inst.pos[0] &&
                again.pos[1] == inst.pos[1] && again.pos[2] == inst.pos[2];
    for (int i = 0; i < 9 && same; ++i) {
      same = again.params[i] == inst.params[i];
    }
    check(same, "effect: two runs -> identical instance");

    // A non-origin plane point (per-world, CS-30) lands in words 0..2.
    const float planeB[3] = {0.0F, 0.0F, -50.0F};
    EffectInstance instB = instanceEffect(2, mapParams, planeB, cellPos);
    check(instB.params[2] == -50.0F,
          "effect: non-origin plane point lands in word 2");
  }

  if (g_failures == 0) {
    std::printf("cellanim_test: ALL PASS\n");
    return 0;
  }
  std::printf("cellanim_test: %d FAILURES\n", g_failures);
  return 1;
}
