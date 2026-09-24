#include "CellPresentation.hpp"

#include <cmath>
#include <utility>

namespace openspore::apps {

PresentationEvidence presentationEvidenceFromLabel(std::string_view label) {
  if (label == "VERIFIED") {
    return PresentationEvidence::verified;
  }
  if (label == "INFERRED") {
    return PresentationEvidence::inferred;
  }
  if (label == "APPROXIMATION") {
    return PresentationEvidence::approximation;
  }
  if (label == "SUPPORTED") {
    return PresentationEvidence::supported;
  }
  if (label == "OBSERVED") {
    return PresentationEvidence::observed;
  }
  if (label == "CONFIRMED") {
    return PresentationEvidence::confirmed;
  }
  return PresentationEvidence::unknown;
}

const char* presentationEvidenceLabel(PresentationEvidence evidence) {
  switch (evidence) {
    case PresentationEvidence::verified:
      return "VERIFIED";
    case PresentationEvidence::inferred:
      return "INFERRED";
    case PresentationEvidence::approximation:
      return "APPROXIMATION";
    case PresentationEvidence::supported:
      return "SUPPORTED";
    case PresentationEvidence::observed:
      return "OBSERVED";
    case PresentationEvidence::confirmed:
      return "CONFIRMED";
    case PresentationEvidence::unknown:
      return "UNKNOWN";
  }
  return "UNKNOWN";
}

bool validPresentationTransform(const PresentationTransform& transform) {
  for (float value : transform.position) {
    if (!std::isfinite(value)) {
      return false;
    }
  }
  for (float value : transform.rotation) {
    if (!std::isfinite(value)) {
      return false;
    }
  }
  for (float value : transform.scale) {
    if (!std::isfinite(value) || value == 0.0F) {
      return false;
    }
  }
  return true;
}

PresentationResult<void> SnapshotEntityView::set_transform(
    const PresentationTransform& transform) {
  if (!validPresentationTransform(transform)) {
    return PresentationResult<void>::failureResult(
        PresentationStatus::invalid_argument,
        "entity view transform contains a non-finite or zero scale value");
  }
  transform_ = transform;
  return PresentationResult<void>::successResult();
}

PresentationResult<void> SnapshotEntityView::set_visibility(bool visible) {
  visible_ = visible;
  return PresentationResult<void>::successResult();
}

PresentationResult<void> UnsupportedEntityView::set_transform(
    const PresentationTransform& transform) {
  (void)transform;
  return PresentationResult<void>::failureResult(
      PresentationStatus::unsupported,
      "entity view transform propagation is unsupported");
}

PresentationResult<void> UnsupportedEntityView::set_visibility(bool visible) {
  (void)visible;
  return PresentationResult<void>::failureResult(
      PresentationStatus::unsupported,
      "entity view visibility propagation is unsupported");
}

PresentationResult<PresentationHandle> EntityPresentationRegistry::attach(
    EntityId entity, PresentationEvidence evidence,
    std::shared_ptr<IEntityView> view) {
  if (!entity.valid()) {
    return PresentationResult<PresentationHandle>::failureResult(
        PresentationStatus::invalid_argument,
        "presentation attach requires a valid entity identity");
  }
  if (!view) {
    return PresentationResult<PresentationHandle>::failureResult(
        PresentationStatus::missing_resource,
        "presentation attach requires an entity view");
  }
  if (find(entity)) {
    return PresentationResult<PresentationHandle>::failureResult(
        PresentationStatus::invalid_state,
        "entity already owns a presentation association");
  }
  const PresentationHandle handle{nextPresentation_++};
  bindings_.push_back({entity, handle, evidence, std::move(view)});
  return PresentationResult<PresentationHandle>::successResult(handle);
}

PresentationResult<void> EntityPresentationRegistry::detach(
    PresentationHandle presentation) {
  if (!presentation.valid()) {
    return PresentationResult<void>::failureResult(
        PresentationStatus::invalid_argument,
        "presentation detach requires a valid handle");
  }
  for (auto it = bindings_.begin(); it != bindings_.end(); ++it) {
    if (it->presentation == presentation) {
      bindings_.erase(it);
      return PresentationResult<void>::successResult();
    }
  }
  return PresentationResult<void>::successResult();
}

PresentationResult<void> EntityPresentationRegistry::rebuild(
    PresentationHandle presentation, PresentationEvidence evidence,
    std::shared_ptr<IEntityView> view) {
  if (!presentation.valid()) {
    return PresentationResult<void>::failureResult(
        PresentationStatus::invalid_argument,
        "presentation rebuild requires a valid handle");
  }
  if (!view) {
    return PresentationResult<void>::failureResult(
        PresentationStatus::missing_resource,
        "presentation rebuild requires an entity view");
  }
  for (EntityPresentationBinding& binding : bindings_) {
    if (binding.presentation == presentation) {
      std::shared_ptr<IEntityView> previous = std::move(binding.view);
      binding.evidence = evidence;
      binding.view = std::move(view);
      previous.reset();
      return PresentationResult<void>::successResult();
    }
  }
  return PresentationResult<void>::failureResult(
      PresentationStatus::not_found, "presentation handle is not attached");
}

PresentationResult<EntityPresentationBinding> EntityPresentationRegistry::find(
    PresentationHandle presentation) const {
  if (!presentation.valid()) {
    return PresentationResult<EntityPresentationBinding>::failureResult(
        PresentationStatus::invalid_argument,
        "presentation lookup requires a valid handle");
  }
  for (const EntityPresentationBinding& binding : bindings_) {
    if (binding.presentation == presentation) {
      return PresentationResult<EntityPresentationBinding>::successResult(
          binding);
    }
  }
  return PresentationResult<EntityPresentationBinding>::failureResult(
      PresentationStatus::not_found, "presentation handle is not attached");
}

PresentationResult<EntityPresentationBinding> EntityPresentationRegistry::find(
    EntityId entity) const {
  if (!entity.valid()) {
    return PresentationResult<EntityPresentationBinding>::failureResult(
        PresentationStatus::invalid_argument,
        "presentation lookup requires a valid entity identity");
  }
  for (const EntityPresentationBinding& binding : bindings_) {
    if (binding.entity == entity) {
      return PresentationResult<EntityPresentationBinding>::successResult(
          binding);
    }
  }
  return PresentationResult<EntityPresentationBinding>::failureResult(
      PresentationStatus::not_found, "entity has no presentation association");
}

void EntityPresentationRegistry::detachAll() { bindings_.clear(); }

void CellEffectPresenter::setAvailable(bool available) {
  available_ = available;
}

PresentationResult<void> CellEffectPresenter::define(
    assets::ResourceKey definition, PresentationEvidence evidence) {
  if (!definition.isComplete()) {
    return PresentationResult<void>::failureResult(
        PresentationStatus::invalid_argument,
        "effect definition requires a complete resource key");
  }
  for (const Definition& existing : definitions_) {
    if (existing.key == definition) {
      if (existing.evidence == evidence) {
        return PresentationResult<void>::successResult();
      }
      return PresentationResult<void>::failureResult(
          PresentationStatus::invalid_state,
          "effect definition evidence cannot change while retained");
    }
  }
  definitions_.push_back({definition, evidence});
  return PresentationResult<void>::successResult();
}

PresentationResult<EffectHandle> CellEffectPresenter::spawn(
    const EffectRequest& request) {
  if (!request.definition.isComplete()) {
    return PresentationResult<EffectHandle>::failureResult(
        PresentationStatus::invalid_argument,
        "effect spawn requires a complete definition key");
  }
  if (!request.owner.valid()) {
    return PresentationResult<EffectHandle>::failureResult(
        PresentationStatus::invalid_argument,
        "effect spawn requires a valid owner entity");
  }
  if (!validPresentationTransform(request.transform)) {
    return PresentationResult<EffectHandle>::failureResult(
        PresentationStatus::invalid_argument,
        "effect spawn transform is invalid");
  }
  bool defined = false;
  for (const Definition& definition : definitions_) {
    if (definition.key == request.definition) {
      defined = true;
      break;
    }
  }
  if (!defined) {
    return PresentationResult<EffectHandle>::failureResult(
        PresentationStatus::missing_resource,
        "effect definition was not preloaded");
  }
  if (!available_) {
    return PresentationResult<EffectHandle>::failureResult(
        PresentationStatus::unsupported,
        "effect presenter backend is unavailable");
  }
  const EffectHandle handle{nextEffect_++};
  effects_.push_back({handle, request});
  return PresentationResult<EffectHandle>::successResult(handle);
}

PresentationResult<void> CellEffectPresenter::release(EffectHandle effect) {
  if (!effect.valid()) {
    return PresentationResult<void>::failureResult(
        PresentationStatus::invalid_argument,
        "effect release requires a valid handle");
  }
  for (auto it = effects_.begin(); it != effects_.end(); ++it) {
    if (it->handle == effect) {
      effects_.erase(it);
      return PresentationResult<void>::successResult();
    }
  }
  return PresentationResult<void>::successResult();
}

PresentationResult<void> RecordingRenderQueue::submit(
    const std::vector<RenderCommand>& commands) {
  if (!supported_) {
    return PresentationResult<void>::failureResult(
        PresentationStatus::unsupported, "render queue backend is unavailable");
  }
  if (!commands.empty()) {
    batches_.push_back(commands);
  }
  return PresentationResult<void>::successResult();
}

}  // namespace openspore::apps
