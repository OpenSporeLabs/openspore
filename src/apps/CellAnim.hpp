#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace openspore::apps {

enum class CellAnim : int {
  kIdle = 0,
  kSwimForward,
  kEat,
  kIdleBig,
  kIdleBlink1Big,
  kEatProbRetractTrgt,
  kTakeDmgElecNpc,
  kTakeDmgPoisonNpc,
};

struct AnimBlend {
  float in = 0.2F;
  float out = 0.2F;
};

struct EffectInstance {
  uint32_t effectID = 0;
  float params[9] = {0.0F};
  float pos[3] = {0.0F};
  bool active = true;
};

enum class AnimationResultStatus {
  success,
  unsupported,
  invalid_argument,
  invalid_state,
  missing_resource,
  not_found,
  failure,
  provisional,
};

template <typename T>
struct AnimationResult {
  AnimationResultStatus status = AnimationResultStatus::failure;
  T value{};
  std::string detail;

  explicit operator bool() const {
    return status == AnimationResultStatus::success;
  }

  static AnimationResult successResult(T value) {
    return {AnimationResultStatus::success, std::move(value), {}};
  }

  static AnimationResult failureResult(AnimationResultStatus status,
                                       std::string detail) {
    return {status, {}, std::move(detail)};
  }

  static AnimationResult provisionalResult(std::string detail) {
    return {AnimationResultStatus::provisional, {}, std::move(detail)};
  }
};

template <>
struct AnimationResult<void> {
  AnimationResultStatus status = AnimationResultStatus::failure;
  std::string detail;

  explicit operator bool() const {
    return status == AnimationResultStatus::success;
  }

  static AnimationResult successResult() {
    return {AnimationResultStatus::success, {}};
  }

  static AnimationResult failureResult(AnimationResultStatus status,
                                       std::string detail) {
    return {status, std::move(detail)};
  }

  static AnimationResult provisionalResult(std::string detail) {
    return {AnimationResultStatus::provisional, std::move(detail)};
  }
};

struct AnimationRequest {
  CellAnim clip = CellAnim::kIdle;
  float blend = 0.2F;
  bool loop = true;
  float time_scale = 1.0F;
};

struct AnimationClipState {
  CellAnim clip = CellAnim::kIdle;
  float time = 0.0F;
  bool loop = true;
  float time_scale = 1.0F;
};

struct AnimationBlendState {
  float duration = 0.0F;
  float elapsed = 0.0F;
  float phase = 0.0F;
  bool active = false;
};

struct AnimationSnapshot {
  AnimationClipState current;
  AnimationClipState target;
  AnimationBlendState blend;
};

class IAnimationController {
 public:
  virtual ~IAnimationController() = default;
  virtual AnimationResult<void> request(const AnimationRequest& request) = 0;
};

class IAnimationWorld {
 public:
  virtual ~IAnimationWorld() = default;
  virtual AnimationResult<void> tick(float delta) = 0;
  virtual AnimationResult<AnimationSnapshot> current_and_target() const = 0;
};

class CellAnimationWorld final : public IAnimationController,
                                 public IAnimationWorld {
 public:
  AnimationResult<void> request(const AnimationRequest& request) override;
  AnimationResult<void> tick(float delta) override;
  AnimationResult<AnimationSnapshot> current_and_target() const override;

  AnimationSnapshot snapshot() const { return snapshot_; }

 private:
  AnimationSnapshot snapshot_;
  bool initialized_ = false;
};

struct AnimationEntityId {
  std::uint64_t value = 0;

  bool valid() const { return value != 0; }
  bool operator==(const AnimationEntityId& other) const {
    return value == other.value;
  }
};

struct AnimationEffectHandle {
  std::uint64_t value = 0;

  bool valid() const { return value != 0; }
  bool operator==(const AnimationEffectHandle& other) const {
    return value == other.value;
  }
};

struct PoseSnapshot {
  AnimationEntityId owner;
  AnimationSnapshot animation;
};

class IPoseEvaluator {
 public:
  virtual ~IPoseEvaluator() = default;
  virtual AnimationResult<void> evaluate(const PoseSnapshot& snapshot) = 0;
};

class UnsupportedPoseEvaluator final : public IPoseEvaluator {
 public:
  AnimationResult<void> evaluate(const PoseSnapshot& snapshot) override;
};

class SnapshotPoseEvaluator final : public IPoseEvaluator {
 public:
  AnimationResult<void> evaluate(const PoseSnapshot& snapshot) override;

  std::size_t evaluationCount() const { return snapshots_.size(); }
  const std::vector<PoseSnapshot>& snapshots() const { return snapshots_; }

 private:
  std::vector<PoseSnapshot> snapshots_;
};

class IAnimationEffectPresenter {
 public:
  virtual ~IAnimationEffectPresenter() = default;
  virtual AnimationResult<AnimationEffectHandle> bind(
      AnimationEntityId entity, AnimationEffectHandle effect) = 0;
  virtual AnimationResult<void> unbind(AnimationEntityId entity,
                                       AnimationEffectHandle effect) = 0;
};

class UnsupportedAnimationEffectPresenter final
    : public IAnimationEffectPresenter {
 public:
  AnimationResult<AnimationEffectHandle> bind(
      AnimationEntityId entity, AnimationEffectHandle effect) override;
  AnimationResult<void> unbind(AnimationEntityId entity,
                               AnimationEffectHandle effect) override;
};

struct AnimationEffectBinding {
  AnimationEntityId entity;
  AnimationEffectHandle effect;
};

class CellAnimationEffectBinder final : public IAnimationEffectPresenter {
 public:
  AnimationResult<AnimationEffectHandle> bind(
      AnimationEntityId entity, AnimationEffectHandle effect) override;
  AnimationResult<void> unbind(AnimationEntityId entity,
                               AnimationEffectHandle effect) override;
  AnimationResult<void> unbind(AnimationEffectHandle effect);

  AnimationResult<AnimationEffectBinding> find(AnimationEntityId entity) const;
  std::size_t bindingCount() const { return bindings_.size(); }

 private:
  std::vector<AnimationEffectBinding> bindings_;
};

AnimBlend animBlend(CellAnim current, CellAnim target, float scale);

int selectEffectMapSlot(int recordType);
uint32_t effectIDForEvent(const char* event);

EffectInstance instanceEffect(uint32_t effectID, const float* mapParams,
                              const float* planePoint, const float* cellPos);

}  // namespace openspore::apps
