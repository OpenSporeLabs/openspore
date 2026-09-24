#include "CellSceneStage.hpp"

#include <algorithm>
#include <utility>

namespace openspore::apps {
namespace {

PresentationStatus modelStatus(assets::ModelLoadCode code) {
  switch (code) {
    case assets::ModelLoadCode::ok:
      return PresentationStatus::success;
    case assets::ModelLoadCode::invalid_key:
      return PresentationStatus::invalid_argument;
    case assets::ModelLoadCode::not_found:
      return PresentationStatus::missing_resource;
    case assets::ModelLoadCode::unsupported_type:
    case assets::ModelLoadCode::unsupported_version:
    case assets::ModelLoadCode::unsupported_format:
    case assets::ModelLoadCode::unsupported_material:
    case assets::ModelLoadCode::unsupported_animation:
      return PresentationStatus::unsupported;
    case assets::ModelLoadCode::provider_failure:
    case assets::ModelLoadCode::source_failure:
    case assets::ModelLoadCode::malformed_record:
      return PresentationStatus::failure;
  }
  return PresentationStatus::failure;
}

PresentationStatus textureStatus(assets::TextureCode code) {
  switch (code) {
    case assets::TextureCode::ok:
      return PresentationStatus::success;
    case assets::TextureCode::invalid_key:
    case assets::TextureCode::invalid_image:
      return PresentationStatus::invalid_argument;
    case assets::TextureCode::not_found:
      return PresentationStatus::missing_resource;
    case assets::TextureCode::unsupported_type:
    case assets::TextureCode::unsupported_format:
      return PresentationStatus::unsupported;
    case assets::TextureCode::provider_failure:
    case assets::TextureCode::source_failure:
    case assets::TextureCode::malformed_record:
    case assets::TextureCode::upload_failed:
      return PresentationStatus::failure;
  }
  return PresentationStatus::failure;
}

template <typename T>
PresentationResult<T> invalidState(const char* operation) {
  return PresentationResult<T>::failureResult(
      PresentationStatus::invalid_state,
      std::string("scene stage ") + operation + " is out of order");
}

}  // namespace
CellSceneStage::CellSceneStage(cellgfx::CellGfx& gfx, cellui::CellUI& ui,
                               assets::IModelStore& models,
                               assets::ITextureStore& textures,
                               IRenderQueue& queue, IEffectPresenter* effects)
    : gfx_(&gfx),
      ui_(&ui),
      modelPort_(&models),
      texturePort_(&textures),
      queue_(&queue),
      effects_(effects) {}

CellSceneStage::~CellSceneStage() { (void)shutdown(); }

PresentationResult<void> CellSceneStage::initialize() {
  if (state_ != SceneStageState::uninitialized) {
    return invalidState<void>("initialize");
  }
  clearState();
  gfx_->initialize();
  ui_->load();
  state_ = SceneStageState::initialized;
  return PresentationResult<void>::successResult();
}

PresentationResult<PresentationPreloadSummary> CellSceneStage::preload(
    const std::vector<PresentationPreloadRequest>& requests) {
  if (state_ != SceneStageState::initialized) {
    return invalidState<PresentationPreloadSummary>("preload");
  }
  PresentationPreloadSummary summary;
  for (const PresentationPreloadRequest& request : requests) {
    if (!request.key.isComplete()) {
      clearPreloadState();
      state_ = SceneStageState::initialized;
      return PresentationResult<PresentationPreloadSummary>::failureResult(
          PresentationStatus::invalid_argument,
          "scene preload requires complete resource keys");
    }
    const bool duplicate = std::any_of(
        resources_.begin(), resources_.end(),
        [&request](const PreloadedPresentationResource& resource) {
          return resource.kind == request.kind && resource.key == request.key;
        });
    if (duplicate) {
      summary.resources.push_back(
          findResource(request.kind, request.key).value);
      continue;
    }
    if (request.kind == PresentationResourceKind::model) {
      assets::ModelLoadResult loaded = modelPort_->load(request.key);
      if (!loaded) {
        const PresentationStatus status = modelStatus(loaded.code);
        clearPreloadState();
        state_ = SceneStageState::initialized;
        return PresentationResult<PresentationPreloadSummary>::failureResult(
            status, "scene model preload failed: " + loaded.error);
      }
      const PresentationResourceHandle handle{nextResource_++};
      const PresentationStatus poseStatus = PresentationStatus::unsupported;
      modelResources_.push_back({handle, request.evidence, poseStatus,
                                 std::make_shared<const assets::ModelRecord>(
                                     std::move(loaded.record))});
      resources_.push_back(
          {handle, request.kind, request.key, request.evidence, poseStatus});
      summary.resources.push_back(resources_.back());
      continue;
    }
    if (request.kind == PresentationResourceKind::texture) {
      assets::TextureLoadResult loaded = texturePort_->load(request.key);
      if (!loaded) {
        const PresentationStatus status = textureStatus(loaded.code);
        clearPreloadState();
        state_ = SceneStageState::initialized;
        return PresentationResult<PresentationPreloadSummary>::failureResult(
            status, "scene texture preload failed: " + loaded.error);
      }
      assets::TextureUploadResult uploaded =
          texturePort_->upload(loaded.record);
      if (!uploaded) {
        const PresentationStatus status = textureStatus(uploaded.code);
        clearPreloadState();
        state_ = SceneStageState::initialized;
        return PresentationResult<PresentationPreloadSummary>::failureResult(
            status, "scene texture upload failed: " + uploaded.error);
      }
      if (uploaded.handle == assets::kInvalidTextureHandle) {
        clearPreloadState();
        state_ = SceneStageState::initialized;
        return PresentationResult<PresentationPreloadSummary>::failureResult(
            PresentationStatus::missing_resource,
            "scene texture upload returned an invalid graphics handle");
      }
      const PresentationResourceHandle handle{nextResource_++};
      textureResources_.push_back({handle, request.evidence, uploaded.handle});
      resources_.push_back({handle, request.kind, request.key, request.evidence,
                            PresentationStatus::success});
      summary.resources.push_back(resources_.back());
      continue;
    }
    clearPreloadState();
    state_ = SceneStageState::initialized;
    return PresentationResult<PresentationPreloadSummary>::failureResult(
        PresentationStatus::unsupported,
        "scene preload resource kind is not supported by the current host");
  }
  state_ = SceneStageState::preloaded;
  return PresentationResult<PresentationPreloadSummary>::successResult(
      std::move(summary));
}

PresentationResult<void> CellSceneStage::display() {
  if (state_ != SceneStageState::preloaded) {
    return invalidState<void>("display");
  }
  gfx_->startDisplay();
  state_ = SceneStageState::displayed;
  return PresentationResult<void>::successResult();
}

PresentationResult<void> CellSceneStage::stop() {
  if (state_ == SceneStageState::stopped) {
    return PresentationResult<void>::successResult();
  }
  if (state_ != SceneStageState::displayed) {
    return invalidState<void>("stop");
  }
  PresentationResult<void> release = releaseEffects();
  gfx_->displayActive = false;
  state_ = SceneStageState::stopped;
  return release;
}

PresentationResult<void> CellSceneStage::shutdown() {
  if (state_ == SceneStageState::shutdown) {
    return PresentationResult<void>::successResult();
  }
  PresentationResult<void> result = PresentationResult<void>::successResult();
  if (state_ == SceneStageState::displayed) {
    const PresentationResult<void> stopped = stop();
    if (!stopped) {
      result = stopped;
    }
  }
  gfx_->displayActive = false;
  presentations_.detachAll();
  releaseTextures();
  clearState();
  state_ = SceneStageState::shutdown;
  return result;
}

PresentationResult<std::shared_ptr<const assets::ModelRecord>>
CellSceneStage::borrowModel(PresentationResourceHandle handle) const {
  for (const ModelResource& model : modelResources_) {
    if (model.handle == handle) {
      return PresentationResult<std::shared_ptr<const assets::ModelRecord>>::
          successResult(model.record);
    }
  }
  return PresentationResult<std::shared_ptr<const assets::ModelRecord>>::
      failureResult(PresentationStatus::not_found,
                    "scene stage has no matching model resource");
}

PresentationResult<assets::TextureHandle> CellSceneStage::borrowTextureHandle(
    PresentationResourceHandle handle) const {
  for (const TextureResource& texture : textureResources_) {
    if (texture.handle == handle) {
      return PresentationResult<assets::TextureHandle>::successResult(
          texture.gfx);
    }
  }
  return PresentationResult<assets::TextureHandle>::failureResult(
      PresentationStatus::not_found,
      "scene stage has no matching texture resource");
}

PresentationResult<EffectHandle> CellSceneStage::spawnEffect(
    const EffectRequest& request) {
  if (state_ != SceneStageState::displayed) {
    return invalidState<EffectHandle>("effect spawn");
  }
  if (effects_ == nullptr) {
    return PresentationResult<EffectHandle>::failureResult(
        PresentationStatus::unsupported,
        "scene stage has no effect presenter port");
  }
  if (!presentations_.find(request.owner)) {
    return PresentationResult<EffectHandle>::failureResult(
        PresentationStatus::not_found,
        "effect owner has no presentation association");
  }
  PresentationResult<EffectHandle> spawned = effects_->spawn(request);
  if (spawned) {
    activeEffects_.push_back(spawned.value);
  }
  return spawned;
}

PresentationResult<void> CellSceneStage::submit(
    const std::vector<RenderCommand>& commands) {
  if (state_ != SceneStageState::displayed) {
    return invalidState<void>("render submission");
  }
  for (const RenderCommand& command : commands) {
    if (!command.entity.valid() || !command.presentation.valid()) {
      return PresentationResult<void>::failureResult(
          PresentationStatus::invalid_argument,
          "render command requires stable entity and presentation identities");
    }
    if (!validPresentationTransform(command.transform)) {
      return PresentationResult<void>::failureResult(
          PresentationStatus::invalid_argument,
          "render command transform is invalid");
    }
    const bool hasModel = command.model.isComplete();
    const bool hasEffect = command.effect.isComplete();
    if (!hasModel && !hasEffect) {
      return PresentationResult<void>::failureResult(
          PresentationStatus::invalid_argument,
          "render command requires a model or effect identity");
    }
    if (hasModel && command.mesh == kInvalidMesh) {
      return PresentationResult<void>::failureResult(
          PresentationStatus::missing_resource,
          "render model command has no mesh handle");
    }
    const PresentationResult<EntityPresentationBinding> binding =
        presentations_.find(command.entity);
    if (!binding || binding.value.presentation != command.presentation) {
      return PresentationResult<void>::failureResult(
          PresentationStatus::not_found,
          "render command has no matching presentation association");
    }
  }
  return queue_->submit(commands);
}

PresentationResult<PreloadedPresentationResource> CellSceneStage::findResource(
    PresentationResourceKind kind, assets::ResourceKey key) const {
  for (const PreloadedPresentationResource& resource : resources_) {
    if (resource.kind == kind && resource.key == key) {
      return PresentationResult<PreloadedPresentationResource>::successResult(
          resource);
    }
  }
  return PresentationResult<PreloadedPresentationResource>::failureResult(
      PresentationStatus::not_found,
      "scene stage has no matching preloaded resource");
}

PresentationResult<void> CellSceneStage::releaseEffects() {
  PresentationResult<void> result = PresentationResult<void>::successResult();
  if (effects_ == nullptr) {
    activeEffects_.clear();
    return result;
  }
  for (EffectHandle effect : activeEffects_) {
    const PresentationResult<void> released = effects_->release(effect);
    if (!released && result) {
      result = released;
    }
  }
  activeEffects_.clear();
  return result;
}

void CellSceneStage::releaseTextures() {
  for (const TextureResource& texture : textureResources_) {
    if (texture.gfx != assets::kInvalidTextureHandle) {
      texturePort_->release(texture.gfx);
    }
  }
  textureResources_.clear();
}

void CellSceneStage::clearPreloadState() {
  releaseTextures();
  modelResources_.clear();
  resources_.clear();
  nextResource_ = 1;
}

void CellSceneStage::clearState() {
  releaseTextures();
  modelResources_.clear();
  resources_.clear();
  activeEffects_.clear();
  nextResource_ = 1;
  if (gfx_ != nullptr) {
    gfx_->displayActive = false;
    gfx_->slots.clear();
    gfx_->preloadedModels.clear();
    gfx_->preloadedPopulates.clear();
  }
  if (ui_ != nullptr) {
    ui_->loaded = false;
    ui_->rollovers.clear();
  }
}

}  // namespace openspore::apps
