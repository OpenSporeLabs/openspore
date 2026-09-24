#include <cstdio>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "CellSceneStage.hpp"

namespace {

int failures = 0;

void check(bool condition, const char* label) {
  std::printf("%s: %s\n", condition ? "ok" : "FAIL", label);
  if (!condition) {
    ++failures;
  }
}

class FakeModelStore final : public openspore::assets::IModelStore {
 public:
  openspore::assets::ModelLoadResult result;

  openspore::assets::ModelLoadResult load(
      const openspore::assets::ResourceKey& key) const override {
    ++loads;
    loaded = key;
    return result;
  }

  openspore::assets::ModelAnimationResult loadAnimation(
      const openspore::assets::ResourceKey&) const override {
    return {openspore::assets::ModelLoadCode::unsupported_animation, {}};
  }

  mutable int loads = 0;
  mutable openspore::assets::ResourceKey loaded;
};

class FakeTextureStore final : public openspore::assets::ITextureStore {
 public:
  openspore::assets::TextureLoadResult loadResult;
  openspore::assets::TextureUploadResult uploadResult;
  std::vector<openspore::assets::TextureHandle> released;
  std::size_t failUploadAt = 0;

  openspore::assets::TextureLoadResult load(
      const openspore::assets::ResourceKey& key) const override {
    ++loads;
    loaded = key;
    return loadResult;
  }

  openspore::assets::TextureUploadResult upload(
      const openspore::assets::ImageRecord&) override {
    ++uploads;
    if (failUploadAt != 0 &&
        static_cast<std::size_t>(uploads) == failUploadAt) {
      return {openspore::assets::TextureCode::upload_failed,
              openspore::assets::kInvalidTextureHandle, 0u, "upload failed"};
    }
    return uploadResult;
  }

  void release(openspore::assets::TextureHandle handle) override {
    released.push_back(handle);
  }

  mutable int loads = 0;
  mutable openspore::assets::ResourceKey loaded;
  int uploads = 0;
};

openspore::assets::ModelLoadResult modelSuccess(
    const openspore::assets::ResourceKey& key) {
  openspore::assets::ModelRecord record;
  record.key = key;
  record.hasGmdl = true;
  record.animation = openspore::assets::AnimationStatus::opaque_trailer;
  return {openspore::assets::ModelLoadCode::ok, std::move(record), {}};
}

openspore::assets::TextureLoadResult textureSuccess(
    const openspore::assets::ResourceKey& key) {
  openspore::assets::ImageRecord record;
  record.key = key;
  return {openspore::assets::TextureCode::ok, std::move(record), {}};
}

bool sameTransform(const openspore::apps::PresentationTransform& left,
                   const openspore::apps::PresentationTransform& right) {
  for (std::size_t i = 0; i < 3; ++i) {
    if (left.position[i] != right.position[i] ||
        left.scale[i] != right.scale[i]) {
      return false;
    }
  }
  for (std::size_t i = 0; i < 4; ++i) {
    if (left.rotation[i] != right.rotation[i]) {
      return false;
    }
  }
  return true;
}

}  // namespace

int main() {
  using namespace openspore;
  using namespace openspore::apps;

  check(presentationEvidenceFromLabel("VERIFIED") ==
                PresentationEvidence::verified &&
            presentationEvidenceFromLabel("INFERRED") ==
                PresentationEvidence::inferred &&
            presentationEvidenceFromLabel("UNRECOGNIZED") ==
                PresentationEvidence::unknown,
        "provenance labels retain verified and inferred distinctions");
  check(std::string(presentationEvidenceLabel(
            PresentationEvidence::approximation)) == "APPROXIMATION",
        "bounded approximations remain explicitly labeled");

  UnsupportedEntityView unsupported;
  const PresentationTransform invalidTransform = [] {
    PresentationTransform transform;
    transform.scale[1] = 0.0F;
    return transform;
  }();
  check(unsupported.set_transform(invalidTransform).status ==
                PresentationStatus::unsupported &&
            unsupported.set_visibility(false).status ==
                PresentationStatus::unsupported,
        "unsupported entity view reports unsupported operations");

  EntityPresentationRegistry registry;
  const EntityId entity{41};
  auto firstView = std::make_shared<SnapshotEntityView>();
  std::weak_ptr<SnapshotEntityView> firstLifetime = firstView;
  const PresentationResult<PresentationHandle> attached =
      registry.attach(entity, PresentationEvidence::inferred, firstView);
  check(static_cast<bool>(attached), "entity presentation attaches");
  firstView.reset();
  check(!firstLifetime.expired(), "attached view remains owned by registry");
  const PresentationHandle stable = attached.value;
  check(registry.attach(entity, PresentationEvidence::verified,
                        std::make_shared<SnapshotEntityView>())
                .status == PresentationStatus::invalid_state,
        "duplicate entity association is rejected");

  auto replacement = std::make_shared<SnapshotEntityView>();
  std::weak_ptr<SnapshotEntityView> replacementLifetime = replacement;
  PresentationTransform moved;
  moved.position[0] = 7.0F;
  moved.position[2] = -2.0F;
  check(static_cast<bool>(replacement->set_transform(moved)) &&
            static_cast<bool>(replacement->set_visibility(false)),
        "entity view accepts transform and visibility snapshots");
  check(static_cast<bool>(registry.rebuild(
            stable, PresentationEvidence::verified, replacement)),
        "entity presentation rebuild succeeds");
  replacement.reset();
  check(firstLifetime.expired() && !replacementLifetime.expired(),
        "rebuild releases the old view and retains the replacement");
  const auto rebuilt = registry.find(stable);
  check(static_cast<bool>(rebuilt) && rebuilt.value.entity == entity &&
            rebuilt.value.presentation == stable &&
            rebuilt.value.evidence == PresentationEvidence::verified,
        "rebuild preserves stable entity presentation identity");
  const auto replacementView =
      std::dynamic_pointer_cast<SnapshotEntityView>(rebuilt.value.view);
  check(replacementView && sameTransform(replacementView->transform(), moved) &&
            !replacementView->visible(),
        "rebuilt view retains its presentation state");
  check(
      registry.attach(EntityId{}, PresentationEvidence::unknown,
                      std::make_shared<SnapshotEntityView>())
                  .status == PresentationStatus::invalid_argument &&
          registry.attach(EntityId{42}, PresentationEvidence::unknown, nullptr)
                  .status == PresentationStatus::missing_resource,
      "missing and invalid views are explicit");
  check(registry.find(PresentationHandle{999}).status ==
            PresentationStatus::not_found,
        "missing presentation lookup is explicit");

  CellEffectPresenter effects;
  const assets::ResourceKey effectKey{0xEA5118B0u, 0x40212000u, 0x1234u};
  EffectRequest effectRequest;
  effectRequest.definition = effectKey;
  effectRequest.owner = entity;
  check(effects.spawn(effectRequest).status ==
            PresentationStatus::missing_resource,
        "missing effect definition is explicit");
  check(static_cast<bool>(
            effects.define(effectKey, PresentationEvidence::supported)) &&
            effects.spawn(effectRequest).status ==
                PresentationStatus::unsupported,
        "unavailable effect backend reports unsupported");
  effects.setAvailable(true);
  const auto firstEffect = effects.spawn(effectRequest);
  EffectRequest secondRequest = effectRequest;
  secondRequest.transform.position[1] = 3.0F;
  const auto secondEffect = effects.spawn(secondRequest);
  check(static_cast<bool>(firstEffect) && static_cast<bool>(secondEffect) &&
            effects.activeCount() == 2,
        "effect instances have independent lifetimes");
  check(static_cast<bool>(effects.release(secondEffect.value)) &&
            effects.activeCount() == 1 &&
            effects.activeEffects().front().handle == firstEffect.value,
        "effect release removes the requested instance only");

  const assets::ResourceKey modelKey{assets::kGmdlType, 0x40616201u,
                                     0xABCDEF01u};
  const assets::ResourceKey textureKey{assets::kRasterType, 0x40662900u,
                                       0xD1B4BB56u};
  FakeModelStore models;
  models.result = modelSuccess(modelKey);
  FakeTextureStore textures;
  textures.loadResult = textureSuccess(textureKey);
  textures.uploadResult = {assets::TextureCode::ok, 77u, 1u, {}};
  RecordingRenderQueue queue;
  cellgfx::CellGfx gfx;
  cellui::CellUI ui;
  CellSceneStage stage(gfx, ui, models, textures, queue, &effects);

  check(stage.display().status == PresentationStatus::invalid_state,
        "display before preload is rejected");
  check(stage.preload({}).status == PresentationStatus::invalid_state &&
            stage.stop().status == PresentationStatus::invalid_state,
        "preload and stop preserve stage ordering");
  check(static_cast<bool>(stage.initialize()) && gfx.modelWorld() != nullptr &&
            ui.loaded &&
            stage.submit({}).status == PresentationStatus::invalid_state,
        "stage initialization builds gfx and HUD while blocking submission");
  const PresentationResult<PresentationPreloadSummary> preloaded =
      stage.preload(std::vector<PresentationPreloadRequest>{
          {PresentationResourceKind::model, modelKey,
           PresentationEvidence::verified},
          {PresentationResourceKind::texture, textureKey,
           PresentationEvidence::inferred},
      });
  check(static_cast<bool>(preloaded) && preloaded.value.resources.size() == 2,
        "stage preloads model content and texture graphics resource");
  const auto modelResource =
      stage.findResource(PresentationResourceKind::model, modelKey);
  const auto textureResource =
      stage.findResource(PresentationResourceKind::texture, textureKey);
  const auto borrowedModel = stage.borrowModel(modelResource.value.handle);
  const auto borrowedTexture =
      stage.borrowTextureHandle(textureResource.value.handle);
  check(static_cast<bool>(modelResource) &&
            modelResource.value.evidence == PresentationEvidence::verified &&
            modelResource.value.poseStatus == PresentationStatus::unsupported &&
            static_cast<bool>(textureResource) &&
            textureResource.value.handle.value == 2u &&
            modelResource.value.handle.value !=
                textureResource.value.handle.value,
        "preload identity, evidence, pose support, and gfx ownership stay "
        "separate");
  check(static_cast<bool>(borrowedModel) && borrowedModel.value &&
            borrowedModel.value->key == modelKey &&
            static_cast<bool>(borrowedTexture) && borrowedTexture.value == 77u,
        "content records and borrowed gfx handles are separate host ports");
  check(static_cast<bool>(stage.display()) && gfx.displayActive,
        "display activates only after preload readiness");
  check(static_cast<bool>(stage.submit({})),
        "empty render submission is a deterministic no-op");

  const PresentationResult<PresentationHandle> stageAttached =
      stage.presentations().attach(EntityId{73}, PresentationEvidence::observed,
                                   std::make_shared<SnapshotEntityView>());
  check(static_cast<bool>(stageAttached),
        "stage exposes presentation registry");
  const PresentationResult<PresentationHandle> secondAttached =
      stage.presentations().attach(EntityId{74}, PresentationEvidence::inferred,
                                   std::make_shared<SnapshotEntityView>());
  check(static_cast<bool>(secondAttached),
        "second renderable presentation attaches independently");
  RenderCommand first;
  first.entity = EntityId{73};
  first.presentation = stageAttached.value;
  first.model = modelKey;
  first.mesh = 9u;
  first.texture = 77u;
  first.materialId = 12u;
  first.layer = 2u;
  first.pass = RenderPass::transparent;
  first.drawOrder = 5u;
  RenderCommand second = first;
  second.entity = EntityId{74};
  second.presentation = secondAttached.value;
  second.drawOrder = 4u;
  RenderCommand orphan = second;
  orphan.entity = EntityId{999};
  check(stage.submit({orphan}).status == PresentationStatus::not_found,
        "render command with a missing view is rejected");
  const PresentationResult<void> submitted = stage.submit({first, second});
  check(static_cast<bool>(submitted) && queue.batches().size() == 1u &&
            queue.batches().front().size() == 2u &&
            queue.batches().front()[0].model == modelKey &&
            queue.batches().front()[0].mesh == 9u &&
            queue.batches().front()[0].texture == 77u &&
            queue.batches().front()[0].materialId == 12u &&
            queue.batches().front()[0].drawOrder == 5u,
        "render queue receives ordered identity and gfx command data");

  check(
      stage.spawnEffect(effectRequest).status == PresentationStatus::not_found,
      "effect owner without a presentation association is rejected");
  EffectRequest stageEffectRequest = effectRequest;
  stageEffectRequest.owner = EntityId{73};
  const auto spawned = stage.spawnEffect(stageEffectRequest);
  check(static_cast<bool>(spawned) && effects.activeCount() == 2,
        "displayed stage spawns through the effect presenter port");
  check(static_cast<bool>(stage.stop()) && !gfx.displayActive &&
            effects.activeCount() == 1,
        "stop releases stage effects before deactivating display");
  check(static_cast<bool>(stage.stop()) &&
            stage.submit({first}).status == PresentationStatus::invalid_state,
        "stop is idempotent and blocks later render submission");
  check(static_cast<bool>(stage.shutdown()) &&
            stage.state() == SceneStageState::shutdown &&
            textures.released.size() == 1u &&
            textures.released.front() == 77u && gfx.slots.empty() &&
            !gfx.displayActive && !ui.loaded,
        "shutdown releases views, graphics handles, worlds, and HUD state");
  check(static_cast<bool>(stage.shutdown()), "shutdown is idempotent");

  FakeModelStore rollbackModels;
  rollbackModels.result = modelSuccess(modelKey);
  FakeTextureStore rollbackTextures;
  rollbackTextures.loadResult = textureSuccess(textureKey);
  rollbackTextures.uploadResult = {assets::TextureCode::ok, 88u, 1u, {}};
  rollbackTextures.failUploadAt = 2u;
  RecordingRenderQueue rollbackQueue;
  cellgfx::CellGfx rollbackGfx;
  cellui::CellUI rollbackUi;
  CellSceneStage rollbackStage(rollbackGfx, rollbackUi, rollbackModels,
                               rollbackTextures, rollbackQueue);
  const assets::ResourceKey secondTextureKey{assets::kRasterType, 0x40662900u,
                                             0xD1B4BB57u};
  check(static_cast<bool>(rollbackStage.initialize()) &&
            rollbackStage
                    .preload(std::vector<PresentationPreloadRequest>{
                        {PresentationResourceKind::model, modelKey,
                         PresentationEvidence::supported},
                        {PresentationResourceKind::texture, textureKey,
                         PresentationEvidence::supported},
                        {PresentationResourceKind::texture, secondTextureKey,
                         PresentationEvidence::supported}})
                    .status == PresentationStatus::failure &&
            rollbackTextures.released.size() == 1u &&
            rollbackTextures.released.front() == 88u,
        "failed preload releases previously acquired graphics handles");
  check(rollbackStage.display().status == PresentationStatus::invalid_state &&
            rollbackStage.resources().empty(),
        "failed preload does not publish readiness");
  (void)rollbackStage.shutdown();

  FakeModelStore missingModels;
  missingModels.result = {assets::ModelLoadCode::not_found, {}, "missing"};
  FakeTextureStore unusedTextures;
  unusedTextures.loadResult = {assets::TextureCode::ok, {}, {}};
  unusedTextures.uploadResult = {
      assets::TextureCode::ok, assets::kInvalidTextureHandle, 0u, {}};
  RecordingRenderQueue unusedQueue;
  cellgfx::CellGfx missingGfx;
  cellui::CellUI missingUi;
  CellSceneStage missingStage(missingGfx, missingUi, missingModels,
                              unusedTextures, unusedQueue);
  check(
      static_cast<bool>(missingStage.initialize()) &&
          missingStage
                  .preload(std::vector<PresentationPreloadRequest>{
                      {PresentationResourceKind::model, modelKey,
                       PresentationEvidence::inferred}})
                  .status == PresentationStatus::missing_resource &&
          missingStage.display().status == PresentationStatus::invalid_state,
      "missing model resource blocks display without changing gameplay state");
  check(static_cast<bool>(missingStage.shutdown()) &&
            missingGfx.modelWorld() == nullptr,
        "failed preload can be torn down without display activation");

  FakeModelStore effectModels;
  effectModels.result = modelSuccess(modelKey);
  FakeTextureStore effectTextures;
  effectTextures.loadResult = {assets::TextureCode::ok, {}, {}};
  effectTextures.uploadResult = {
      assets::TextureCode::ok, assets::kInvalidTextureHandle, 0u, {}};
  RecordingRenderQueue effectQueue;
  cellgfx::CellGfx unsupportedGfx;
  cellui::CellUI unsupportedUi;
  CellSceneStage unsupportedStage(unsupportedGfx, unsupportedUi, effectModels,
                                  effectTextures, effectQueue);
  check(static_cast<bool>(unsupportedStage.initialize()) &&
            unsupportedStage
                    .preload(std::vector<PresentationPreloadRequest>{
                        {PresentationResourceKind::effect, effectKey,
                         PresentationEvidence::supported}})
                    .status == PresentationStatus::unsupported,
        "unsupported preload resource is explicit and blocks display");
  (void)unsupportedStage.shutdown();

  RecordingRenderQueue unavailableQueue(false);
  check(unavailableQueue.submit({first}).status ==
            PresentationStatus::unsupported,
        "unavailable render queue reports unsupported submission");

  std::printf("cell_presentation_test: %s\n",
              failures == 0 ? "ALL PASS" : "FAIL");
  return failures == 0 ? 0 : 1;
}
