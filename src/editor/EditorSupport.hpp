#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace openspore::editor {

enum class SupportStatus {
  success,
  unsupported,
  invalid_argument,
  not_found,
  already_open,
  not_open,
  not_active,
  not_rendering,
  already_active,
  already_rendering,
  invalid_state,
  failure,
};

enum class SupportEvidence {
  blueprint_backed,
  existing_openspore_behavior,
  bounded_inference,
  provisional,
};

template <typename T>
struct SupportResult {
  SupportStatus status = SupportStatus::failure;
  SupportEvidence evidence = SupportEvidence::provisional;
  T value{};

  explicit operator bool() const { return status == SupportStatus::success; }
};

template <>
struct SupportResult<void> {
  SupportStatus status = SupportStatus::failure;
  SupportEvidence evidence = SupportEvidence::provisional;

  explicit operator bool() const { return status == SupportStatus::success; }
};

struct ResourceKey {
  std::string value;

  bool empty() const { return value.empty(); }
};

inline bool operator==(const ResourceKey& left, const ResourceKey& right) {
  return left.value == right.value;
}

inline bool operator!=(const ResourceKey& left, const ResourceKey& right) {
  return !(left == right);
}

struct EditorColor {
  std::uint8_t red = 0;
  std::uint8_t green = 0;
  std::uint8_t blue = 0;
  std::uint8_t alpha = 0;
};

struct PaletteEntry {
  ResourceKey key;
  std::string identity;
  std::string category;
  std::string name;
};

struct PaletteFilter {
  ResourceKey key;
  std::string identity;
  std::string category;
  std::string name;
};

struct EditorSupportAssets {
  ResourceKey key;
  std::vector<PaletteEntry> palette;
};

class IEditorSupportAssets {
 public:
  virtual ~IEditorSupportAssets() = default;
  virtual SupportResult<EditorSupportAssets> load(const ResourceKey& key) = 0;
};

class InMemoryEditorSupportAssets final : public IEditorSupportAssets {
 public:
  explicit InMemoryEditorSupportAssets(std::vector<EditorSupportAssets> assets);

  SupportResult<EditorSupportAssets> load(const ResourceKey& key) override;

 private:
  std::vector<EditorSupportAssets> assets_;
};

class IPaletteCatalog {
 public:
  virtual ~IPaletteCatalog() = default;
  virtual SupportResult<std::vector<PaletteEntry>> query(
      const PaletteFilter& filter) const = 0;
};

class PaletteCatalog final : public IPaletteCatalog {
 public:
  explicit PaletteCatalog(std::vector<PaletteEntry> entries);

  SupportResult<std::vector<PaletteEntry>> query(
      const PaletteFilter& filter) const override;

 private:
  std::vector<PaletteEntry> entries_;
};

enum class ViewerPhase {
  closed,
  open,
};

struct ViewerState {
  ViewerPhase phase = ViewerPhase::closed;
  ResourceKey key;
};

class IViewerModel {
 public:
  virtual ~IViewerModel() = default;
  virtual SupportResult<ViewerState> open(const ResourceKey& key) = 0;
  virtual SupportResult<ViewerState> close() = 0;
  virtual ViewerState state() const = 0;
};

class ViewerModel final : public IViewerModel {
 public:
  SupportResult<ViewerState> open(const ResourceKey& key) override;
  SupportResult<ViewerState> close() override;
  ViewerState state() const override;

 private:
  ViewerState state_;
};

struct PaintRegion {
  std::uint32_t x = 0;
  std::uint32_t y = 0;
  std::uint32_t width = 0;
  std::uint32_t height = 0;

  bool valid() const { return width != 0 && height != 0; }
};

enum class TexturePaintPhase {
  idle,
  active,
  rendering,
};

struct TexturePaintState {
  TexturePaintPhase phase = TexturePaintPhase::idle;
  PaintRegion region;
  bool hasRegion = false;
};

class TexturePaintSession {
 public:
  SupportResult<TexturePaintState> begin(const PaintRegion& region);
  SupportResult<TexturePaintState> startRender();
  SupportResult<TexturePaintState> endRender();
  SupportResult<TexturePaintState> end();
  TexturePaintState state() const;

 private:
  TexturePaintState state_;
};

struct EditorModel {
  ResourceKey key;
  std::vector<EditorColor> colors;

  SupportResult<void> setColor(std::size_t index, const EditorColor& color);
};

class IEditorSupportWriter {
 public:
  virtual ~IEditorSupportWriter() = default;
  virtual SupportResult<void> save(const EditorModel& model) = 0;
};

class UnsupportedEditorSupportWriter final : public IEditorSupportWriter {
 public:
  SupportResult<void> save(const EditorModel& model) override;
};

}  // namespace openspore::editor
