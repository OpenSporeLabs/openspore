#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "CellGfx.hpp"
#include "CellPresentation.hpp"
#include "CellUI.hpp"
#include "assets/ModelStore.hpp"
#include "assets/TextureStore.hpp"

namespace openspore::apps {

enum class PresentationResourceKind {
  model,
  texture,
  effect,
  creature,
  animation,
};

struct PresentationPreloadRequest {
  PresentationResourceKind kind = PresentationResourceKind::model;
  assets::ResourceKey key;
  PresentationEvidence evidence = PresentationEvidence::unknown;
};

struct PresentationResourceHandle {
  std::uint64_t value = 0;

  bool valid() const { return value != 0; }
  bool operator==(const PresentationResourceHandle& other) const {
    return value == other.value;
  }
  bool operator!=(const PresentationResourceHandle& other) const {
    return !(*this == other);
  }
};

struct PreloadedPresentationResource {
  PresentationResourceHandle handle;
  PresentationResourceKind kind = PresentationResourceKind::model;
  assets::ResourceKey key;
  PresentationEvidence evidence = PresentationEvidence::unknown;
  PresentationStatus poseStatus = PresentationStatus::unsupported;
};

struct PresentationPreloadSummary {
  std::vector<PreloadedPresentationResource> resources;
};

enum class SceneStageState {
  uninitialized,
  initialized,
  preloaded,
  displayed,
  stopped,
  shutdown,
};

class ISceneStage {
 public:
  virtual ~ISceneStage() = default;
  virtual PresentationResult<void> initialize() = 0;
  virtual PresentationResult<PresentationPreloadSummary> preload(
      const std::vector<PresentationPreloadRequest>& requests) = 0;
  virtual PresentationResult<void> display() = 0;
  virtual PresentationResult<void> stop() = 0;
  virtual PresentationResult<void> shutdown() = 0;
};

class CellSceneStage final : public ISceneStage {
 public:
  CellSceneStage(cellgfx::CellGfx& gfx, cellui::CellUI& ui,
                 assets::IModelStore& models, assets::ITextureStore& textures,
                 IRenderQueue& queue, IEffectPresenter* effects = nullptr);
  ~CellSceneStage() override;

  PresentationResult<void> initialize() override;
  PresentationResult<PresentationPreloadSummary> preload(
      const std::vector<PresentationPreloadRequest>& requests) override;
  PresentationResult<void> display() override;
  PresentationResult<void> stop() override;
  PresentationResult<void> shutdown() override;

  PresentationResult<EffectHandle> spawnEffect(const EffectRequest& request);
  PresentationResult<void> submit(const std::vector<RenderCommand>& commands);
  PresentationResult<PreloadedPresentationResource> findResource(
      PresentationResourceKind kind, assets::ResourceKey key) const;
  PresentationResult<std::shared_ptr<const assets::ModelRecord>> borrowModel(
      PresentationResourceHandle handle) const;
  PresentationResult<assets::TextureHandle> borrowTextureHandle(
      PresentationResourceHandle handle) const;

  SceneStageState state() const { return state_; }
  bool ready() const { return state_ == SceneStageState::preloaded; }
  EntityPresentationRegistry& presentations() { return presentations_; }
  const EntityPresentationRegistry& presentations() const {
    return presentations_;
  }
  const std::vector<PreloadedPresentationResource>& resources() const {
    return resources_;
  }

 private:
  struct ModelResource {
    PresentationResourceHandle handle;
    PresentationEvidence evidence = PresentationEvidence::unknown;
    PresentationStatus poseStatus = PresentationStatus::unsupported;
    std::shared_ptr<const assets::ModelRecord> record;
  };

  struct TextureResource {
    PresentationResourceHandle handle;
    PresentationEvidence evidence = PresentationEvidence::unknown;
    assets::TextureHandle gfx = assets::kInvalidTextureHandle;
  };

  PresentationResult<void> releaseEffects();
  void releaseTextures();
  void clearPreloadState();
  void clearState();

  cellgfx::CellGfx* gfx_ = nullptr;
  cellui::CellUI* ui_ = nullptr;
  assets::IModelStore* modelPort_ = nullptr;
  assets::ITextureStore* texturePort_ = nullptr;
  IRenderQueue* queue_ = nullptr;
  IEffectPresenter* effects_ = nullptr;
  EntityPresentationRegistry presentations_;
  std::vector<ModelResource> modelResources_;
  std::vector<TextureResource> textureResources_;
  std::vector<PreloadedPresentationResource> resources_;
  std::vector<EffectHandle> activeEffects_;
  SceneStageState state_ = SceneStageState::uninitialized;
  std::uint64_t nextResource_ = 1;
};

}  // namespace openspore::apps
