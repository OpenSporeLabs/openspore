#include <iostream>
#include <string>
#include <vector>

#include "../EditorSupport.hpp"

namespace {

using openspore::editor::EditorModel;
using openspore::editor::EditorSupportAssets;
using openspore::editor::InMemoryEditorSupportAssets;
using openspore::editor::PaintRegion;
using openspore::editor::PaletteCatalog;
using openspore::editor::PaletteEntry;
using openspore::editor::PaletteFilter;
using openspore::editor::ResourceKey;
using openspore::editor::SupportEvidence;
using openspore::editor::SupportStatus;
using openspore::editor::TexturePaintPhase;
using openspore::editor::TexturePaintSession;
using openspore::editor::UnsupportedEditorSupportWriter;
using openspore::editor::ViewerModel;
using openspore::editor::ViewerPhase;

struct GameplayState {
  int score = 0;
};

bool sameEntry(const PaletteEntry& left, const PaletteEntry& right) {
  return left.key == right.key && left.identity == right.identity &&
         left.category == right.category && left.name == right.name;
}

bool runPaletteAndLoadChecks() {
  const EditorSupportAssets support{
      {"asset-b"},
      {{"entry-b", "page-b", "group-b", "name-b"},
       {"entry-a", "page-a", "group-a", "name-a"},
       {"entry-c", "page-c", "group-a", "name-c"}}};
  InMemoryEditorSupportAssets assets({support});
  bool passed = true;
  const auto loaded = assets.load(ResourceKey{"asset-b"});
  passed = passed && loaded.status == SupportStatus::success;
  passed = passed && loaded.evidence == SupportEvidence::bounded_inference;
  passed = passed && loaded.value.palette.size() == 3;
  passed = passed &&
           assets.load(ResourceKey{}).status == SupportStatus::invalid_argument;
  passed = passed && assets.load(ResourceKey{"missing"}).status ==
                         SupportStatus::not_found;

  PaletteCatalog catalog(
      {support.palette[0], support.palette[2], support.palette[1]});
  PaletteFilter filter;
  filter.category = "group-a";
  const auto first = catalog.query(filter);
  const auto second = catalog.query(filter);
  passed = passed && first.status == SupportStatus::success;
  passed = passed && second.status == SupportStatus::success;
  passed = passed && first.value.size() == 2;
  passed = passed && second.value.size() == first.value.size();
  passed = passed && sameEntry(first.value[0], second.value[0]);
  passed = passed && sameEntry(first.value[1], second.value[1]);
  passed = passed && first.value[0].key.value == "entry-a";
  passed = passed && first.value[1].key.value == "entry-c";

  const auto all = catalog.query(PaletteFilter{});
  passed = passed && all.status == SupportStatus::success;
  passed = passed && all.value.size() == 3;
  passed = passed && all.value[0].key.value == "entry-a";
  passed = passed && all.value[1].key.value == "entry-b";
  passed = passed && all.value[2].key.value == "entry-c";
  return passed;
}

bool runLifecycleChecks() {
  ViewerModel viewer;
  bool passed = true;
  passed = passed && viewer.close().status == SupportStatus::not_open;
  passed = passed &&
           viewer.open(ResourceKey{}).status == SupportStatus::invalid_argument;
  const auto opened = viewer.open(ResourceKey{"viewer-asset"});
  passed = passed && opened.status == SupportStatus::success;
  passed = passed && opened.value.phase == ViewerPhase::open;
  passed = passed && viewer.open(ResourceKey{"other"}).status ==
                         SupportStatus::already_open;
  passed = passed && viewer.state().key.value == "viewer-asset";
  const auto closed = viewer.close();
  passed = passed && closed.status == SupportStatus::success;
  passed = passed && closed.value.phase == ViewerPhase::closed;
  passed = passed && viewer.state().key.value.empty();
  passed = passed && viewer.open(ResourceKey{"viewer-asset"}).status ==
                         SupportStatus::success;
  return passed;
}

bool runPaintChecks() {
  TexturePaintSession session;
  bool passed = true;
  passed = passed && session.startRender().status == SupportStatus::not_active;
  passed = passed && session.begin(PaintRegion{0, 0, 0, 1}).status ==
                         SupportStatus::invalid_argument;
  const PaintRegion region{2, 3, 4, 5};
  const auto begun = session.begin(region);
  passed = passed && begun.status == SupportStatus::success;
  passed = passed && begun.value.phase == TexturePaintPhase::active;
  passed = passed && begun.value.hasRegion;
  passed =
      passed && session.begin(region).status == SupportStatus::already_active;
  passed = passed && session.startRender().status == SupportStatus::success;
  passed = passed &&
           session.startRender().status == SupportStatus::already_rendering;
  passed = passed && session.endRender().status == SupportStatus::success;
  passed = passed && session.endRender().status == SupportStatus::not_rendering;
  passed = passed && session.end().status == SupportStatus::success;
  passed = passed && session.state().phase == TexturePaintPhase::idle;
  passed = passed && !session.state().hasRegion;
  passed = passed && session.end().status == SupportStatus::not_active;
  return passed;
}

bool runModelColorChecks() {
  EditorModel model{{"model"}, {{1, 2, 3, 4}, {5, 6, 7, 8}}};
  const auto updated = model.setColor(1, {9, 10, 11, 12});
  bool passed = true;
  passed = passed && updated.status == SupportStatus::success;
  passed = passed && updated.evidence == SupportEvidence::bounded_inference;
  passed = passed && model.colors[1].red == 9;
  passed = passed && model.colors[1].green == 10;
  passed = passed && model.colors[1].blue == 11;
  passed = passed && model.colors[1].alpha == 12;
  const auto missing = model.setColor(model.colors.size(), {13, 14, 15, 16});
  passed = passed && missing.status == SupportStatus::invalid_argument;
  passed = passed && missing.evidence == SupportEvidence::bounded_inference;
  passed = passed && model.colors.size() == 2;
  return passed;
}

bool runIsolationAndWriterChecks() {
  GameplayState gameplay{37};
  EditorModel model{{"model"}, {{1, 2, 3, 4}, {5, 6, 7, 8}}};
  const auto originalColors = model.colors;
  UnsupportedEditorSupportWriter writer;
  const auto saved = writer.save(model);
  bool passed = true;
  passed = passed && saved.status == SupportStatus::unsupported;
  passed = passed && saved.evidence == SupportEvidence::provisional;
  passed = passed && gameplay.score == 37;
  passed = passed && model.colors.size() == originalColors.size();
  for (std::size_t index = 0; index < model.colors.size(); ++index) {
    passed = passed && model.colors[index].red == originalColors[index].red;
    passed = passed && model.colors[index].green == originalColors[index].green;
    passed = passed && model.colors[index].blue == originalColors[index].blue;
    passed = passed && model.colors[index].alpha == originalColors[index].alpha;
  }
  return passed;
}

}  // namespace

int main() {
  const bool passed = runPaletteAndLoadChecks() && runLifecycleChecks() &&
                      runPaintChecks() && runModelColorChecks() &&
                      runIsolationAndWriterChecks();
  if (!passed) {
    std::cerr << "editor support tests failed\n";
    return 1;
  }
  return 0;
}
