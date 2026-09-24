#pragma once

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <variant>
#include <vector>

#include "ResourceKey.hpp"
#include "Stream.hpp"

namespace openspore::assets {

enum class PropertyType : uint8_t {
  none = 0,
  boolean = 1,
  int32 = 9,
  uint32 = 10,
  float32 = 13,
  string8 = 18,
  string16 = 19,
  key = 32,
  text = 34,
};

using PropertyValue = std::variant<bool, int32_t, uint32_t, float, ResourceKey>;

struct PropertyEntry {
  uint32_t id = 0;
  PropertyValue value = false;
};

struct PropertyLimits {
  size_t maxEntries = 4096;
};

enum class PropertyErrorCode {
  ok,
  invalid_input,
  not_found,
  duplicate_id,
  limit_exceeded,
  parent_cycle,
  parent_depth_exceeded,
  unsupported_format,
  unsupported_version,
  malformed_data,
  unsupported_property,
  stream_failure,
};

struct PropertyResult {
  PropertyErrorCode code = PropertyErrorCode::ok;
  std::string error;

  explicit operator bool() const { return code == PropertyErrorCode::ok; }
};

class IPropertyStore {
 public:
  virtual ~IPropertyStore() = default;

  virtual PropertyResult set_local(uint32_t id, PropertyValue value) = 0;
  virtual PropertyResult get(uint32_t id, PropertyValue& value) const = 0;
  virtual PropertyResult get_local(uint32_t id, PropertyValue& value) const = 0;
  virtual PropertyResult read_local(IStream& stream) = 0;
  virtual PropertyResult write_local(
      IStream& stream, const std::vector<PropertyEntry>& entries) = 0;
  virtual const IPropertyStore* parent() const noexcept { return nullptr; }
};

class LocalPropertyStore final : public IPropertyStore {
 public:
  static constexpr size_t kMaxParentDepth = 64;

  explicit LocalPropertyStore(const IPropertyStore* parent = nullptr,
                              PropertyLimits limits = {});

  LocalPropertyStore(const LocalPropertyStore&) = delete;
  LocalPropertyStore& operator=(const LocalPropertyStore&) = delete;

  PropertyResult set_local(uint32_t id, PropertyValue value) override;
  PropertyResult get(uint32_t id, PropertyValue& value) const override;
  PropertyResult get_local(uint32_t id, PropertyValue& value) const override;
  PropertyResult read_local(IStream& stream) override;
  PropertyResult write_local(
      IStream& stream, const std::vector<PropertyEntry>& entries) override;

  std::vector<PropertyEntry> entries() const;
  size_t size() const noexcept { return values_.size(); }
  uint64_t operationCount() const noexcept { return operationCount_; }
  const IPropertyStore* parent() const noexcept override { return parent_; }
  void setParent(const IPropertyStore* parent) noexcept { parent_ = parent; }
  const PropertyLimits& limits() const noexcept { return limits_; }

 private:
  const IPropertyStore* parent_ = nullptr;
  PropertyLimits limits_;
  std::map<uint32_t, PropertyValue> values_;
  uint64_t operationCount_ = 0;
};

PropertyType typeOf(const PropertyValue& value) noexcept;

}  // namespace openspore::assets
