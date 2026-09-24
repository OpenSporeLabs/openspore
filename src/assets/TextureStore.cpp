#include "TextureStore.hpp"

#include <algorithm>
#include <limits>
#include <utility>

namespace openspore::assets {

namespace {

TextureCode contentCode(ContentErrorCode code) {
  switch (code) {
    case ContentErrorCode::invalid_key:
      return TextureCode::invalid_key;
    case ContentErrorCode::not_found:
      return TextureCode::not_found;
    case ContentErrorCode::provider_failure:
      return TextureCode::provider_failure;
    case ContentErrorCode::unsupported_format:
      return TextureCode::unsupported_format;
    default:
      return TextureCode::source_failure;
  }
}

TextureCode decodeCode(const std::string& error) {
  if (error.find("unsupported fourcc") != std::string::npos) {
    return TextureCode::unsupported_format;
  }
  return TextureCode::malformed_record;
}

bool validMip(const ImageRGBA& image) {
  if (image.width == 0 || image.height == 0) {
    return false;
  }
  const size_t width = image.width;
  const size_t height = image.height;
  if (width > std::numeric_limits<size_t>::max() / height) {
    return false;
  }
  const size_t pixels = width * height;
  return pixels <= std::numeric_limits<size_t>::max() / 4u &&
         image.pixels.size() == pixels * 4u;
}

uint32_t mipDimension(uint32_t base, size_t level) {
  return level >= 32u ? 1u : std::max<uint32_t>(1u, base >> level);
}

bool validImageRecord(const ImageRecord& image) {
  if (image.envelope.fourcc != kDxt5Fourcc || image.envelope.width == 0 ||
      image.envelope.height == 0 || image.envelope.mipCount == 0 ||
      image.mips.size() != image.envelope.mipCount) {
    return false;
  }
  for (size_t level = 0; level < image.mips.size(); ++level) {
    const ImageRGBA& mip = image.mips[level];
    if (!validMip(mip) ||
        mip.width != mipDimension(image.envelope.width, level) ||
        mip.height != mipDimension(image.envelope.height, level)) {
      return false;
    }
  }
  return true;
}

}  // namespace

TextureLoadResult TextureStore::load(const ResourceKey& key) const {
  if (!key.isComplete()) {
    return {TextureCode::invalid_key,
            {},
            "texture: load requires a complete resource key"};
  }
  if (key.type != kRasterType) {
    return {TextureCode::unsupported_type,
            {},
            "texture: unsupported resource type 0x" + std::to_string(key.type)};
  }
  if (store_ == nullptr) {
    return {TextureCode::provider_failure,
            {},
            "texture: content store is unavailable"};
  }
  const ReadResult bytes = store_->read(key);
  if (!bytes) {
    return {contentCode(bytes.code), {}, bytes.error};
  }
  ImageRecord record;
  record.key = key;
  std::string error;
  if (!decodeRasterMips(bytes.bytes.data(), bytes.bytes.size(), record.mips,
                        record.envelope, error)) {
    return {decodeCode(error), {}, "texture: raster decode failed: " + error};
  }
  for (const ImageRGBA& mip : record.mips) {
    if (!validMip(mip)) {
      return {TextureCode::invalid_image,
              {},
              "texture: decoded mip has invalid dimensions or pixels"};
    }
  }
  return {TextureCode::ok, std::move(record), {}};
}

TextureUploadResult TextureStore::upload(const ImageRecord& image) {
  if (image.mips.empty()) {
    return {TextureCode::invalid_image, kInvalidTextureHandle, 0,
            "texture: image record has no mips"};
  }
  if (!validImageRecord(image)) {
    return {TextureCode::invalid_image, kInvalidTextureHandle, 0,
            "texture: image record does not match its DXT5 mip envelope"};
  }
  if (renderer_ == nullptr) {
    return {TextureCode::upload_failed, kInvalidTextureHandle, 0,
            "texture: renderer is unavailable"};
  }
  const TextureHandle handle = renderer_->createTexture(image.mips.front());
  if (handle == kInvalidTextureHandle) {
    return {TextureCode::upload_failed, kInvalidTextureHandle,
            image.mips.size(), "texture: renderer rejected the image"};
  }
  return {TextureCode::ok, handle, image.mips.size(), {}};
}

void TextureStore::release(TextureHandle handle) {
  if (renderer_ != nullptr && handle != kInvalidTextureHandle) {
    renderer_->destroyTexture(handle);
  }
}

}  // namespace openspore::assets
