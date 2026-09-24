#include "ModelStore.hpp"

#include <utility>

namespace openspore::assets {

namespace {

ModelLoadResult failure(ModelLoadCode code, std::string error) {
  return {code, {}, std::move(error)};
}

ModelLoadCode contentCode(ContentErrorCode code) {
  switch (code) {
    case ContentErrorCode::invalid_key:
      return ModelLoadCode::invalid_key;
    case ContentErrorCode::not_found:
      return ModelLoadCode::not_found;
    case ContentErrorCode::provider_failure:
      return ModelLoadCode::provider_failure;
    case ContentErrorCode::unsupported_format:
      return ModelLoadCode::unsupported_format;
    default:
      return ModelLoadCode::source_failure;
  }
}

bool contains(const std::string& value, const char* needle) {
  return value.find(needle) != std::string::npos;
}

ModelLoadCode parseCode(const std::string& error) {
  if (contains(error, "unsupported version")) {
    return ModelLoadCode::unsupported_version;
  }
  if (contains(error, "material info") || contains(error, "shader-data")) {
    return ModelLoadCode::unsupported_material;
  }
  if (contains(error, "unsupported") || contains(error, "unknown ftype") ||
      contains(error, "unknown type")) {
    return ModelLoadCode::unsupported_format;
  }
  return ModelLoadCode::malformed_record;
}

bool hasAnimationSection(const Rw4& container) {
  for (const Rw4Section& section : container.sections) {
    if ((section.tc >= 0x70000u && section.tc <= 0x7000Fu) ||
        section.tc == 0x200AFu || section.tc == 0xFF0000u ||
        section.tc == 0xFF0001u || section.tc == 0xFF0002u) {
      return true;
    }
  }
  return false;
}

}  // namespace

ModelLoadResult ModelStore::load(const ResourceKey& key) const {
  if (!key.isComplete()) {
    return failure(ModelLoadCode::invalid_key,
                   "model: load requires a complete resource key");
  }
  if (store_ == nullptr) {
    return failure(ModelLoadCode::provider_failure,
                   "model: content store is unavailable");
  }
  if (key.type != kGmdlType && key.type != kRw4Type) {
    return failure(
        ModelLoadCode::unsupported_type,
        "model: unsupported resource type 0x" + std::to_string(key.type));
  }
  const ReadResult bytes = store_->read(key);
  if (!bytes) {
    return failure(contentCode(bytes.code), bytes.error);
  }
  ModelRecord record;
  record.key = key;
  if (key.type == kGmdlType) {
    std::string parseError;
    if (!parseGmdl(bytes.bytes.data(), bytes.bytes.size(), record.gmdl,
                   parseError)) {
      return failure(parseCode(parseError),
                     "model: GMDL decode failed: " + parseError);
    }
    record.format = ModelFormat::gmdl;
    record.hasGmdl = true;
    record.animation = AnimationStatus::opaque_trailer;
  } else {
    std::string parseError;
    if (!parseRw4(bytes.bytes.data(), bytes.bytes.size(), record.rw4,
                  parseError)) {
      return failure(parseCode(parseError),
                     "model: RW4 decode failed: " + parseError);
    }
    record.format = ModelFormat::rw4;
    record.hasRw4 = true;
    record.animation = hasAnimationSection(record.rw4)
                           ? AnimationStatus::unsupported
                           : AnimationStatus::none;
  }
  return {ModelLoadCode::ok, std::move(record), {}};
}

ModelAnimationResult ModelStore::loadAnimation(const ResourceKey& key) const {
  if (!key.isComplete()) {
    return {ModelLoadCode::invalid_key,
            "model: animation load requires a complete resource key"};
  }
  return {ModelLoadCode::unsupported_animation,
          "model: animation payload execution is unsupported"};
}

}  // namespace openspore::assets
