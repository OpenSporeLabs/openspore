#include "CellAnim.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

namespace openspore::apps {
namespace {

bool validCellAnim(CellAnim clip) {
  switch (clip) {
    case CellAnim::kIdle:
    case CellAnim::kSwimForward:
    case CellAnim::kEat:
    case CellAnim::kIdleBig:
    case CellAnim::kIdleBlink1Big:
    case CellAnim::kEatProbRetractTrgt:
    case CellAnim::kTakeDmgElecNpc:
    case CellAnim::kTakeDmgPoisonNpc:
      return true;
  }
  return false;
}

}  // namespace

AnimationResult<void> CellAnimationWorld::request(
    const AnimationRequest& request) {
  if (!validCellAnim(request.clip)) {
    return AnimationResult<void>::failureResult(
        AnimationResultStatus::invalid_argument,
        "animation request contains an unknown clip");
  }
  if (!std::isfinite(request.blend) || request.blend < 0.0F) {
    return AnimationResult<void>::failureResult(
        AnimationResultStatus::invalid_argument,
        "animation request blend must be finite and non-negative");
  }
  if (!std::isfinite(request.time_scale) || request.time_scale < 0.0F) {
    return AnimationResult<void>::failureResult(
        AnimationResultStatus::invalid_argument,
        "animation request time scale must be finite and non-negative");
  }

  AnimationClipState nextTarget{request.clip, 0.0F, request.loop,
                                request.time_scale};
  if (initialized_ && snapshot_.current.clip == nextTarget.clip &&
      snapshot_.target.clip == nextTarget.clip) {
    snapshot_.current = nextTarget;
    snapshot_.target = nextTarget;
    snapshot_.blend = {request.blend, 0.0F, 0.0F, false};
  } else if (request.blend == 0.0F) {
    snapshot_.current = nextTarget;
    snapshot_.target = nextTarget;
    snapshot_.blend = {0.0F, 0.0F, 0.0F, false};
  } else {
    snapshot_.target = nextTarget;
    snapshot_.blend = {request.blend, 0.0F, 0.0F, true};
  }
  initialized_ = true;
  return AnimationResult<void>::successResult();
}

AnimationResult<void> CellAnimationWorld::tick(float delta) {
  if (!std::isfinite(delta) || delta < 0.0F) {
    return AnimationResult<void>::failureResult(
        AnimationResultStatus::invalid_argument,
        "animation tick delta must be finite and non-negative");
  }
  if (!initialized_ || delta == 0.0F) {
    return AnimationResult<void>::successResult();
  }

  snapshot_.current.time += delta * snapshot_.current.time_scale;
  snapshot_.target.time += delta * snapshot_.target.time_scale;
  if (!snapshot_.blend.active) {
    return AnimationResult<void>::successResult();
  }

  const float remaining = snapshot_.blend.duration - snapshot_.blend.elapsed;
  if (delta >= remaining) {
    snapshot_.blend.elapsed = snapshot_.blend.duration;
    snapshot_.blend.phase = 1.0F;
    snapshot_.blend.active = false;
    snapshot_.current = snapshot_.target;
  } else {
    snapshot_.blend.elapsed += delta;
    snapshot_.blend.phase = snapshot_.blend.elapsed / snapshot_.blend.duration;
  }
  return AnimationResult<void>::successResult();
}

AnimationResult<AnimationSnapshot> CellAnimationWorld::current_and_target()
    const {
  return AnimationResult<AnimationSnapshot>::successResult(snapshot_);
}

AnimationResult<void> UnsupportedPoseEvaluator::evaluate(
    const PoseSnapshot& snapshot) {
  (void)snapshot;
  return AnimationResult<void>::failureResult(
      AnimationResultStatus::unsupported,
      "pose evaluation backend is unsupported");
}

AnimationResult<void> SnapshotPoseEvaluator::evaluate(
    const PoseSnapshot& snapshot) {
  if (!snapshot.owner.valid()) {
    return AnimationResult<void>::failureResult(
        AnimationResultStatus::invalid_argument,
        "pose snapshot requires a valid owner");
  }
  snapshots_.push_back(snapshot);
  return AnimationResult<void>::provisionalResult(
      "pose snapshot recorded without skeleton evaluation or upload");
}

AnimationResult<AnimationEffectHandle>
UnsupportedAnimationEffectPresenter::bind(AnimationEntityId entity,
                                          AnimationEffectHandle effect) {
  (void)entity;
  (void)effect;
  return AnimationResult<AnimationEffectHandle>::failureResult(
      AnimationResultStatus::unsupported,
      "animation effect binding backend is unsupported");
}

AnimationResult<void> UnsupportedAnimationEffectPresenter::unbind(
    AnimationEntityId entity, AnimationEffectHandle effect) {
  (void)entity;
  (void)effect;
  return AnimationResult<void>::failureResult(
      AnimationResultStatus::unsupported,
      "animation effect unbinding backend is unsupported");
}

AnimationResult<AnimationEffectHandle> CellAnimationEffectBinder::bind(
    AnimationEntityId entity, AnimationEffectHandle effect) {
  if (!entity.valid()) {
    return AnimationResult<AnimationEffectHandle>::failureResult(
        AnimationResultStatus::invalid_argument,
        "animation effect binding requires a valid entity");
  }
  if (!effect.valid()) {
    return AnimationResult<AnimationEffectHandle>::failureResult(
        AnimationResultStatus::invalid_argument,
        "animation effect binding requires a valid effect handle");
  }
  for (const AnimationEffectBinding& binding : bindings_) {
    if (binding.entity == entity) {
      return AnimationResult<AnimationEffectHandle>::failureResult(
          AnimationResultStatus::invalid_state,
          "animation entity already owns an effect binding");
    }
    if (binding.effect == effect) {
      return AnimationResult<AnimationEffectHandle>::failureResult(
          AnimationResultStatus::invalid_state,
          "animation effect is already bound");
    }
  }
  bindings_.push_back({entity, effect});
  return AnimationResult<AnimationEffectHandle>::successResult(effect);
}

AnimationResult<void> CellAnimationEffectBinder::unbind(
    AnimationEntityId entity, AnimationEffectHandle effect) {
  if (!entity.valid()) {
    return AnimationResult<void>::failureResult(
        AnimationResultStatus::invalid_argument,
        "animation effect unbinding requires a valid entity");
  }
  if (!effect.valid()) {
    return AnimationResult<void>::failureResult(
        AnimationResultStatus::invalid_argument,
        "animation effect unbinding requires a valid effect handle");
  }
  for (auto it = bindings_.begin(); it != bindings_.end(); ++it) {
    if (it->entity == entity && it->effect == effect) {
      bindings_.erase(it);
      return AnimationResult<void>::successResult();
    }
  }
  return AnimationResult<void>::failureResult(
      AnimationResultStatus::not_found,
      "animation effect binding was not found");
}

AnimationResult<void> CellAnimationEffectBinder::unbind(
    AnimationEffectHandle effect) {
  for (const AnimationEffectBinding& binding : bindings_) {
    if (binding.effect == effect) {
      return unbind(binding.entity, effect);
    }
  }
  return AnimationResult<void>::failureResult(
      AnimationResultStatus::invalid_argument,
      "animation effect unbinding requires a bound effect handle");
}

AnimationResult<AnimationEffectBinding> CellAnimationEffectBinder::find(
    AnimationEntityId entity) const {
  if (!entity.valid()) {
    return AnimationResult<AnimationEffectBinding>::failureResult(
        AnimationResultStatus::invalid_argument,
        "animation effect lookup requires a valid entity");
  }
  for (const AnimationEffectBinding& binding : bindings_) {
    if (binding.entity == entity) {
      return AnimationResult<AnimationEffectBinding>::successResult(binding);
    }
  }
  return AnimationResult<AnimationEffectBinding>::failureResult(
      AnimationResultStatus::not_found,
      "animation effect binding was not found");
}

AnimBlend animBlend(CellAnim current, CellAnim target, float scale) {
  AnimBlend blend;
  if (current == CellAnim::kIdleBig || current == CellAnim::kIdleBlink1Big) {
    blend.out = 0.1F;
  }
  if (current == CellAnim::kEatProbRetractTrgt ||
      current == CellAnim::kTakeDmgElecNpc ||
      current == CellAnim::kTakeDmgPoisonNpc) {
    blend.out = 0.0F;
  }
  if (target == CellAnim::kEatProbRetractTrgt) {
    blend.in = 0.0F;
  }
  blend.in *= scale;
  blend.out *= scale;
  return blend;
}

int selectEffectMapSlot(int recordType) {
  switch (recordType) {
    case 0:
    case 2:
      return 0;
    case 1:
    case 3:
      return 1;
    case 4:
      return 2;
    default:
      return -1;
  }
}

uint32_t effectIDForEvent(const char* event) {
  if (event == nullptr) {
    return 0;
  }
  if (std::strcmp(event, "eat") == 0) {
    return 1;
  }
  if (std::strcmp(event, "flee") == 0 || std::strcmp(event, "death") == 0) {
    return 2;
  }
  return 0;
}

EffectInstance instanceEffect(uint32_t effectID, const float* mapParams,
                              const float* planePoint, const float* cellPos) {
  EffectInstance instance;
  if (mapParams == nullptr || planePoint == nullptr || cellPos == nullptr) {
    instance.active = false;
    return instance;
  }
  instance.effectID = effectID;
  for (int i = 0; i < 9; ++i) {
    instance.params[i] = mapParams[i];
  }
  instance.params[0] = planePoint[0];
  instance.params[1] = planePoint[1];
  instance.params[2] = planePoint[2];
  instance.params[3] = 1.0F;
  for (int i = 0; i < 3; ++i) {
    instance.pos[i] = cellPos[i];
  }
  instance.active = true;
  return instance;
}

}  // namespace openspore::apps
