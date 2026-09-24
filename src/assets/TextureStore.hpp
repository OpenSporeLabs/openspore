#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "ResourceStore.hpp"
#include "Texture.hpp"
#include "renderer/Renderer.hpp"

namespace openspore::assets {

constexpr uint32_t kRasterType = 0x2F4E681Cu;

using TextureHandle = openspore::TextureHandle;
constexpr TextureHandle kInvalidTextureHandle = openspore::kInvalidTexture;

struct ImageRecord {
  ResourceKey key;
  RasterEnvelope envelope;
  std::vector<ImageRGBA> mips;
};

enum class TextureCode {
  ok,
  invalid_key,
  not_found,
  provider_failure,
  source_failure,
  unsupported_type,
  unsupported_format,
  malformed_record,
  invalid_image,
  upload_failed,
};

struct TextureLoadResult {
  TextureCode code = TextureCode::ok;
  ImageRecord record;
  std::string error;

  explicit operator bool() const { return code == TextureCode::ok; }
};

struct TextureUploadResult {
  TextureCode code = TextureCode::ok;
  TextureHandle handle = kInvalidTextureHandle;
  size_t mipCount = 0;
  std::string error;

  explicit operator bool() const { return code == TextureCode::ok; }
};

class ITextureStore {
 public:
  virtual ~ITextureStore() = default;
  virtual TextureLoadResult load(const ResourceKey& key) const = 0;
  virtual TextureUploadResult upload(const ImageRecord& image) = 0;
  virtual void release(TextureHandle handle) = 0;
};

class TextureStore final : public ITextureStore {
 public:
  TextureStore(IContentStore& store, openspore::IRenderer& renderer)
      : store_(&store), renderer_(&renderer) {}

  TextureLoadResult load(const ResourceKey& key) const override;
  TextureUploadResult upload(const ImageRecord& image) override;
  void release(TextureHandle handle) override;

 private:
  IContentStore* store_ = nullptr;
  openspore::IRenderer* renderer_ = nullptr;
};

}  // namespace openspore::assets
