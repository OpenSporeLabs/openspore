#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Gmdl.hpp"
#include "ResourceStore.hpp"
#include "Rw4.hpp"

namespace openspore::assets {

constexpr uint32_t kGmdlType = 0x00E6BCE5u;

enum class ModelFormat {
  gmdl,
  rw4,
};

enum class AnimationStatus {
  none,
  opaque_trailer,
  unsupported,
};

enum class ModelLoadCode {
  ok,
  invalid_key,
  not_found,
  provider_failure,
  source_failure,
  unsupported_type,
  unsupported_version,
  unsupported_format,
  unsupported_material,
  malformed_record,
  unsupported_animation,
};

struct ModelRecord {
  ResourceKey key;
  ModelFormat format = ModelFormat::gmdl;
  GmdlModel gmdl;
  Rw4 rw4;
  bool hasGmdl = false;
  bool hasRw4 = false;
  AnimationStatus animation = AnimationStatus::none;
};

struct ModelLoadResult {
  ModelLoadCode code = ModelLoadCode::ok;
  ModelRecord record;
  std::string error;

  explicit operator bool() const { return code == ModelLoadCode::ok; }
};

struct ModelAnimationResult {
  ModelLoadCode code = ModelLoadCode::ok;
  std::string error;

  explicit operator bool() const { return code == ModelLoadCode::ok; }
};

class IModelStore {
 public:
  virtual ~IModelStore() = default;
  virtual ModelLoadResult load(const ResourceKey& key) const = 0;
  virtual ModelAnimationResult loadAnimation(const ResourceKey& key) const = 0;
};

class ModelStore final : public IModelStore {
 public:
  explicit ModelStore(IContentStore& store) : store_(&store) {}

  ModelLoadResult load(const ResourceKey& key) const override;
  ModelAnimationResult loadAnimation(const ResourceKey& key) const override;

 private:
  IContentStore* store_ = nullptr;
};

}  // namespace openspore::assets
