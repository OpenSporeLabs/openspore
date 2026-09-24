#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "assets/ResourceKey.hpp"
#include "renderer/Renderer.hpp"

namespace openspore::apps {

enum class PresentationStatus {
  success,
  unsupported,
  invalid_argument,
  invalid_state,
  missing_resource,
  not_found,
  failure,
};

template <typename T>
struct PresentationResult {
  PresentationStatus status = PresentationStatus::failure;
  T value{};
  std::string detail;

  explicit operator bool() const {
    return status == PresentationStatus::success;
  }

  static PresentationResult successResult(T value) {
    return {PresentationStatus::success, std::move(value), {}};
  }

  static PresentationResult failureResult(PresentationStatus status,
                                          std::string detail) {
    return {status, {}, std::move(detail)};
  }
};

template <>
struct PresentationResult<void> {
  PresentationStatus status = PresentationStatus::failure;
  std::string detail;

  explicit operator bool() const {
    return status == PresentationStatus::success;
  }

  static PresentationResult successResult() {
    return {PresentationStatus::success, {}};
  }

  static PresentationResult failureResult(PresentationStatus status,
                                          std::string detail) {
    return {status, std::move(detail)};
  }
};

enum class PresentationEvidence {
  unknown,
  verified,
  inferred,
  approximation,
  supported,
  observed,
  confirmed,
};

PresentationEvidence presentationEvidenceFromLabel(std::string_view label);
const char* presentationEvidenceLabel(PresentationEvidence evidence);

struct EntityId {
  std::uint64_t value = 0;

  bool valid() const { return value != 0; }
  bool operator==(const EntityId& other) const { return value == other.value; }
  bool operator!=(const EntityId& other) const { return !(*this == other); }
};

struct PresentationHandle {
  std::uint64_t value = 0;

  bool valid() const { return value != 0; }
  bool operator==(const PresentationHandle& other) const {
    return value == other.value;
  }
  bool operator!=(const PresentationHandle& other) const {
    return !(*this == other);
  }
};

struct EffectHandle {
  std::uint64_t value = 0;

  bool valid() const { return value != 0; }
  bool operator==(const EffectHandle& other) const {
    return value == other.value;
  }
  bool operator!=(const EffectHandle& other) const { return !(*this == other); }
};

struct PresentationTransform {
  float position[3] = {0.0F, 0.0F, 0.0F};
  float rotation[4] = {0.0F, 0.0F, 0.0F, 1.0F};
  float scale[3] = {1.0F, 1.0F, 1.0F};
};

bool validPresentationTransform(const PresentationTransform& transform);

class IEntityView {
 public:
  virtual ~IEntityView() = default;
  virtual PresentationResult<void> set_transform(
      const PresentationTransform& transform) = 0;
  virtual PresentationResult<void> set_visibility(bool visible) = 0;
};

class SnapshotEntityView final : public IEntityView {
 public:
  PresentationResult<void> set_transform(
      const PresentationTransform& transform) override;
  PresentationResult<void> set_visibility(bool visible) override;

  const PresentationTransform& transform() const { return transform_; }
  bool visible() const { return visible_; }

 private:
  PresentationTransform transform_;
  bool visible_ = true;
};

class UnsupportedEntityView final : public IEntityView {
 public:
  PresentationResult<void> set_transform(
      const PresentationTransform& transform) override;
  PresentationResult<void> set_visibility(bool visible) override;
};

struct EntityPresentationBinding {
  EntityId entity;
  PresentationHandle presentation;
  PresentationEvidence evidence = PresentationEvidence::unknown;
  std::shared_ptr<IEntityView> view;
};

class IEntityPresentationRegistry {
 public:
  virtual ~IEntityPresentationRegistry() = default;
  virtual PresentationResult<PresentationHandle> attach(
      EntityId entity, PresentationEvidence evidence,
      std::shared_ptr<IEntityView> view) = 0;
  virtual PresentationResult<void> detach(PresentationHandle presentation) = 0;
  virtual PresentationResult<void> rebuild(
      PresentationHandle presentation, PresentationEvidence evidence,
      std::shared_ptr<IEntityView> view) = 0;
};

class EntityPresentationRegistry final : public IEntityPresentationRegistry {
 public:
  PresentationResult<PresentationHandle> attach(
      EntityId entity, PresentationEvidence evidence,
      std::shared_ptr<IEntityView> view) override;
  PresentationResult<void> detach(PresentationHandle presentation) override;
  PresentationResult<void> rebuild(PresentationHandle presentation,
                                   PresentationEvidence evidence,
                                   std::shared_ptr<IEntityView> view) override;

  PresentationResult<EntityPresentationBinding> find(
      PresentationHandle presentation) const;
  PresentationResult<EntityPresentationBinding> find(EntityId entity) const;
  void detachAll();
  std::size_t size() const { return bindings_.size(); }

 private:
  std::vector<EntityPresentationBinding> bindings_;
  std::uint64_t nextPresentation_ = 1;
};

struct EffectRequest {
  assets::ResourceKey definition;
  EntityId owner;
  PresentationTransform transform;
  std::uint32_t layer = 0;
};

class IEffectPresenter {
 public:
  virtual ~IEffectPresenter() = default;
  virtual PresentationResult<EffectHandle> spawn(
      const EffectRequest& request) = 0;
  virtual PresentationResult<void> release(EffectHandle effect) = 0;
};

class CellEffectPresenter final : public IEffectPresenter {
 public:
  struct ActiveEffect {
    EffectHandle handle;
    EffectRequest request;
  };

  void setAvailable(bool available);
  PresentationResult<void> define(assets::ResourceKey definition,
                                  PresentationEvidence evidence);
  PresentationResult<EffectHandle> spawn(const EffectRequest& request) override;
  PresentationResult<void> release(EffectHandle effect) override;
  std::size_t activeCount() const { return effects_.size(); }
  const std::vector<ActiveEffect>& activeEffects() const { return effects_; }

 private:
  struct Definition {
    assets::ResourceKey key;
    PresentationEvidence evidence = PresentationEvidence::unknown;
  };

  bool available_ = false;
  std::vector<Definition> definitions_;
  std::vector<ActiveEffect> effects_;
  std::uint64_t nextEffect_ = 1;
};

enum class RenderPass {
  opaque,
  transparent,
  overlay,
};

struct RenderCommand {
  EntityId entity;
  PresentationHandle presentation;
  assets::ResourceKey model;
  assets::ResourceKey effect;
  MeshHandle mesh = kInvalidMesh;
  TextureHandle texture = kInvalidTexture;
  std::uint32_t materialId = 0;
  PresentationTransform transform;
  bool visible = true;
  std::uint32_t layer = 0;
  RenderPass pass = RenderPass::opaque;
  std::uint64_t drawOrder = 0;
};

class IRenderQueue {
 public:
  virtual ~IRenderQueue() = default;
  virtual PresentationResult<void> submit(
      const std::vector<RenderCommand>& commands) = 0;
};

class RecordingRenderQueue final : public IRenderQueue {
 public:
  explicit RecordingRenderQueue(bool supported = true)
      : supported_(supported) {}
  PresentationResult<void> submit(
      const std::vector<RenderCommand>& commands) override;
  const std::vector<std::vector<RenderCommand>>& batches() const {
    return batches_;
  }

 private:
  bool supported_ = true;
  std::vector<std::vector<RenderCommand>> batches_;
};

}  // namespace openspore::apps
