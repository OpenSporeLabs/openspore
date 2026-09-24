#include "EditorSupport.hpp"

#include <algorithm>
#include <iterator>
#include <tuple>
#include <utility>

namespace openspore::editor {
namespace {

bool matches(const PaletteEntry& entry, const PaletteFilter& filter) {
  return (filter.key.empty() || entry.key == filter.key) &&
         (filter.identity.empty() || entry.identity == filter.identity) &&
         (filter.category.empty() || entry.category == filter.category) &&
         (filter.name.empty() || entry.name == filter.name);
}

bool precedes(const PaletteEntry& left, const PaletteEntry& right) {
  return std::tie(left.key.value, left.identity, left.category, left.name) <
         std::tie(right.key.value, right.identity, right.category, right.name);
}

}  // namespace

InMemoryEditorSupportAssets::InMemoryEditorSupportAssets(
    std::vector<EditorSupportAssets> assets)
    : assets_(std::move(assets)) {}

SupportResult<EditorSupportAssets> InMemoryEditorSupportAssets::load(
    const ResourceKey& key) {
  if (key.empty()) {
    return {SupportStatus::invalid_argument,
            SupportEvidence::bounded_inference,
            {}};
  }
  for (const auto& asset : assets_) {
    if (asset.key == key) {
      return {SupportStatus::success, SupportEvidence::bounded_inference,
              asset};
    }
  }
  return {SupportStatus::not_found, SupportEvidence::bounded_inference, {}};
}

PaletteCatalog::PaletteCatalog(std::vector<PaletteEntry> entries)
    : entries_(std::move(entries)) {}

SupportResult<std::vector<PaletteEntry>> PaletteCatalog::query(
    const PaletteFilter& filter) const {
  std::vector<PaletteEntry> result;
  std::copy_if(
      entries_.begin(), entries_.end(), std::back_inserter(result),
      [&filter](const PaletteEntry& entry) { return matches(entry, filter); });
  std::sort(result.begin(), result.end(), precedes);
  return {SupportStatus::success, SupportEvidence::bounded_inference, result};
}

SupportResult<ViewerState> ViewerModel::open(const ResourceKey& key) {
  if (key.empty()) {
    return {SupportStatus::invalid_argument, SupportEvidence::provisional,
            state_};
  }
  if (state_.phase == ViewerPhase::open) {
    return {SupportStatus::already_open, SupportEvidence::provisional, state_};
  }
  state_.phase = ViewerPhase::open;
  state_.key = key;
  return {SupportStatus::success, SupportEvidence::provisional, state_};
}

SupportResult<ViewerState> ViewerModel::close() {
  if (state_.phase == ViewerPhase::closed) {
    return {SupportStatus::not_open, SupportEvidence::provisional, state_};
  }
  state_ = ViewerState{};
  return {SupportStatus::success, SupportEvidence::provisional, state_};
}

ViewerState ViewerModel::state() const { return state_; }

SupportResult<TexturePaintState> TexturePaintSession::begin(
    const PaintRegion& region) {
  if (!region.valid()) {
    return {SupportStatus::invalid_argument, SupportEvidence::provisional,
            state_};
  }
  if (state_.phase != TexturePaintPhase::idle) {
    return {SupportStatus::already_active, SupportEvidence::provisional,
            state_};
  }
  state_.phase = TexturePaintPhase::active;
  state_.region = region;
  state_.hasRegion = true;
  return {SupportStatus::success, SupportEvidence::provisional, state_};
}

SupportResult<TexturePaintState> TexturePaintSession::startRender() {
  if (state_.phase == TexturePaintPhase::idle) {
    return {SupportStatus::not_active, SupportEvidence::provisional, state_};
  }
  if (state_.phase == TexturePaintPhase::rendering) {
    return {SupportStatus::already_rendering, SupportEvidence::provisional,
            state_};
  }
  state_.phase = TexturePaintPhase::rendering;
  return {SupportStatus::success, SupportEvidence::provisional, state_};
}

SupportResult<TexturePaintState> TexturePaintSession::endRender() {
  if (state_.phase != TexturePaintPhase::rendering) {
    return {SupportStatus::not_rendering, SupportEvidence::provisional, state_};
  }
  state_.phase = TexturePaintPhase::active;
  return {SupportStatus::success, SupportEvidence::provisional, state_};
}

SupportResult<TexturePaintState> TexturePaintSession::end() {
  if (state_.phase == TexturePaintPhase::idle) {
    return {SupportStatus::not_active, SupportEvidence::provisional, state_};
  }
  if (state_.phase == TexturePaintPhase::rendering) {
    return {SupportStatus::invalid_state, SupportEvidence::provisional, state_};
  }
  state_ = TexturePaintState{};
  return {SupportStatus::success, SupportEvidence::provisional, state_};
}

TexturePaintState TexturePaintSession::state() const { return state_; }

SupportResult<void> EditorModel::setColor(std::size_t index,
                                          const EditorColor& color) {
  if (index >= colors.size()) {
    return {SupportStatus::invalid_argument,
            SupportEvidence::bounded_inference};
  }
  colors[index] = color;
  return {SupportStatus::success, SupportEvidence::bounded_inference};
}

SupportResult<void> UnsupportedEditorSupportWriter::save(const EditorModel&) {
  return {SupportStatus::unsupported, SupportEvidence::provisional};
}

}  // namespace openspore::editor
