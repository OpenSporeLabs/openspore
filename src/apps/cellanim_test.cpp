// CS-31: cell animation blend state machine + event->effect mapping test.
//
// Pure C++ + stdlib; no GPU, no SPORE/ package. Checks the PlayAnimation blend
// special cases, the LoadEffectMap 3-slot selection, the contract
// event->effect ID mapping, and the InstanceEffectOnCell param-record build
// (swim-plane-point override + 1.0f sentinel + placement). Every check is
// deterministic (two calls -> identical results).
#include "CellAnim.hpp"

#include <cmath>
#include <cstdio>
#include <limits>

namespace {

using openspore::apps::AnimBlend;
using openspore::apps::animBlend;
using openspore::apps::CellAnim;
using openspore::apps::effectIDForEvent;
using openspore::apps::EffectInstance;
using openspore::apps::instanceEffect;
using openspore::apps::selectEffectMapSlot;

int g_failures = 0;

void check(bool cond, const char* label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

}  // namespace

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
    check(b.in == 0.2F && b.out == 0.1F, "blend: current IdleBig -> out=0.1");
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
    check(b.in == 0.1F && b.out == 0.1F, "blend: scale 0.5 halves both times");
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
    const float mapParams[9] = {10.0F, 20.0F, 30.0F, 40.0F, 50.0F,
                                60.0F, 70.0F, 80.0F, 90.0F};
    const float planePoint[3] = {0.0F, 0.0F, 0.0F};  // CS-01: z=0 swim plane
    const float cellPos[3] = {1.5F, -2.0F, 3.0F};
    EffectInstance inst = instanceEffect(1, mapParams, planePoint, cellPos);
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
    bool same = again.effectID == inst.effectID &&
                again.pos[0] == inst.pos[0] && again.pos[1] == inst.pos[1] &&
                again.pos[2] == inst.pos[2];
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

  {
    using openspore::apps::AnimationEffectHandle;
    using openspore::apps::AnimationEntityId;
    using openspore::apps::AnimationRequest;
    using openspore::apps::AnimationResultStatus;
    using openspore::apps::CellAnimationEffectBinder;
    using openspore::apps::CellAnimationWorld;
    using openspore::apps::PoseSnapshot;
    using openspore::apps::SnapshotPoseEvaluator;
    using openspore::apps::UnsupportedAnimationEffectPresenter;
    using openspore::apps::UnsupportedPoseEvaluator;

    CellAnimationWorld world;
    AnimationRequest invalid;
    invalid.blend = -1.0F;
    check(world.request(invalid).status ==
              AnimationResultStatus::invalid_argument,
          "animation request rejects negative blend");
    invalid.blend = 0.2F;
    invalid.time_scale = std::numeric_limits<float>::quiet_NaN();
    check(world.request(invalid).status ==
              AnimationResultStatus::invalid_argument,
          "animation request rejects non-finite time scale");
    invalid.time_scale = 1.0F;
    invalid.clip = static_cast<CellAnim>(99);
    check(world.request(invalid).status ==
              AnimationResultStatus::invalid_argument,
          "animation request rejects unknown clip");

    AnimationRequest request;
    request.clip = CellAnim::kSwimForward;
    request.blend = 0.2F;
    request.time_scale = 2.0F;
    check(world.request(request).status == AnimationResultStatus::success,
          "animation request accepts a valid target");
    auto state = world.current_and_target();
    check(state && state.value.current.clip == CellAnim::kIdle &&
              state.value.target.clip == CellAnim::kSwimForward &&
              state.value.blend.active && state.value.blend.phase == 0.0F,
          "animation request publishes current and target clips");
    check(world.tick(0.1F).status == AnimationResultStatus::success,
          "animation tick accepts a positive delta");
    state = world.current_and_target();
    check(
        state && state.value.blend.active && state.value.blend.phase == 0.5F &&
            state.value.current.time == 0.1F && state.value.target.time == 0.2F,
        "animation tick advances both clocks and blend phase");
    check(world.tick(0.1F).status == AnimationResultStatus::success,
          "animation tick accepts the blend boundary delta");
    state = world.current_and_target();
    check(state && !state.value.blend.active &&
              state.value.blend.phase == 1.0F &&
              state.value.current.clip == CellAnim::kSwimForward &&
              state.value.target.clip == CellAnim::kSwimForward,
          "animation blend boundary deterministically completes");

    CellAnimationWorld repeat;
    check(repeat.request(request) && repeat.tick(0.1F) && repeat.tick(0.1F),
          "animation state is deterministic across identical requests");
    auto repeated = repeat.current_and_target();
    check(repeated && repeated.value.current.time == state.value.current.time &&
              repeated.value.blend.phase == state.value.blend.phase,
          "identical animation requests produce identical state");

    request.blend = 0.0F;
    check(world.request(request).status == AnimationResultStatus::success,
          "animation request accepts an immediate transition");
    state = world.current_and_target();
    check(state && !state.value.blend.active &&
              state.value.current.clip == CellAnim::kSwimForward &&
              state.value.target.clip == CellAnim::kSwimForward,
          "zero blend switches current and target without an active blend");

    check(world.tick(-0.1F).status == AnimationResultStatus::invalid_argument &&
              world.tick(std::numeric_limits<float>::quiet_NaN()).status ==
                  AnimationResultStatus::invalid_argument,
          "animation tick rejects invalid delta values");

    UnsupportedPoseEvaluator unsupportedPose;
    PoseSnapshot invalidPose;
    invalidPose.animation = world.snapshot();
    check(unsupportedPose.evaluate(invalidPose).status ==
              AnimationResultStatus::unsupported,
          "unsupported pose evaluator reports unsupported");
    SnapshotPoseEvaluator pose;
    check(pose.evaluate(invalidPose).status ==
              AnimationResultStatus::invalid_argument,
          "pose seam rejects an invalid owner");
    invalidPose.owner = AnimationEntityId{17};
    check(pose.evaluate(invalidPose).status ==
                  AnimationResultStatus::provisional &&
              pose.evaluationCount() == 1,
          "pose seam records snapshots without claiming backend evaluation");

    CellAnimationEffectBinder binder;
    AnimationEffectHandle effect{42};
    auto bound = binder.bind(AnimationEntityId{17}, effect);
    check(bound && bound.value == effect && binder.bindingCount() == 1,
          "effect binding records entity ownership");
    check(binder.bind(AnimationEntityId{17}, effect).status ==
              AnimationResultStatus::invalid_state,
          "effect binding rejects a duplicate entity binding");
    check(binder.unbind(AnimationEntityId{17}, effect).status ==
                  AnimationResultStatus::success &&
              binder.bindingCount() == 0,
          "effect unbinding clears the requested binding");
    check(
        binder.unbind(effect).status == AnimationResultStatus::invalid_argument,
        "unbinding an absent effect is explicit");
    check(binder.bind(AnimationEntityId{}, effect).status ==
                  AnimationResultStatus::invalid_argument &&
              binder.bind(AnimationEntityId{18}, {}).status ==
                  AnimationResultStatus::invalid_argument,
          "effect binding validates entity and effect identities");
    UnsupportedAnimationEffectPresenter unsupportedEffects;
    check(unsupportedEffects.bind(AnimationEntityId{18}, effect).status ==
              AnimationResultStatus::unsupported,
          "unsupported effect binding is explicit");
  }

  if (g_failures == 0) {
    std::printf("cellanim_test: ALL PASS\n");
    return 0;
  }
  std::printf("cellanim_test: %d FAILURES\n", g_failures);
  return 1;
}
