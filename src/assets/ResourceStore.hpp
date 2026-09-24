#pragma once

#include <any>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Dbpf.hpp"
#include "ResourceKey.hpp"
#include "compat/ResourceProvider.hpp"

namespace openspore::assets {

enum class ContentErrorCode {
  ok,
  invalid_key,
  invalid_input,
  malformed_index,
  unsupported_format,
  invalid_extent,
  unsupported_compression,
  decompression_failed,
  size_mismatch,
  not_found,
  provider_failure,
  unsupported_operation,
};

struct RecordLocator {
  ResourceKey key;
  uint64_t offset = 0;
  size_t sourceSize = 0;
  size_t storedSize = 0;
  size_t memorySize = 0;
  uint16_t compression = 0;

  bool withinExtent() const noexcept;
  bool compressed() const noexcept { return compression == 0xFFFFu; }
};

struct LookupResult {
  ContentErrorCode code = ContentErrorCode::ok;
  RecordLocator locator;
  std::string error;

  explicit operator bool() const { return code == ContentErrorCode::ok; }
};

struct ReadResult {
  ContentErrorCode code = ContentErrorCode::ok;
  std::vector<uint8_t> bytes;
  std::string error;

  explicit operator bool() const { return code == ContentErrorCode::ok; }
};

class IContentStore {
 public:
  virtual ~IContentStore() = default;

  virtual LookupResult lookup(const ResourceKey& key) const = 0;
  virtual ReadResult read(const ResourceKey& key) const = 0;
};

class DbpfContentStore final : public IContentStore {
 public:
  DbpfContentStore(const uint8_t* packageData, size_t packageSize);
  DbpfContentStore(const DbpfContentStore&) = delete;
  DbpfContentStore& operator=(const DbpfContentStore&) = delete;

  LookupResult lookup(const ResourceKey& key) const override;
  ReadResult read(const ResourceKey& key) const override;

  bool valid() const noexcept { return parseError_.empty(); }
  size_t entryCount() const noexcept { return entries_.size(); }

 private:
  const uint8_t* packageData_ = nullptr;
  size_t packageSize_ = 0;
  std::vector<DbpfEntry> entries_;
  ContentErrorCode parseErrorCode_ = ContentErrorCode::malformed_index;
  std::string parseError_;
};

class ResourceProviderContentStore final : public IContentStore {
 public:
  explicit ResourceProviderContentStore(compat::IResourceProvider& provider)
      : provider_(&provider) {}
  ResourceProviderContentStore(const ResourceProviderContentStore&) = delete;
  ResourceProviderContentStore& operator=(const ResourceProviderContentStore&) =
      delete;

  LookupResult lookup(const ResourceKey& key) const override;
  ReadResult read(const ResourceKey& key) const override;

 private:
  compat::IResourceProvider* provider_ = nullptr;
};

enum class RecordCodecErrorCode {
  ok,
  invalid_input,
  unsupported_type,
  decode_failed,
};

struct RecordCodecResult {
  RecordCodecErrorCode code = RecordCodecErrorCode::ok;
  std::any record;
  std::string error;

  explicit operator bool() const { return code == RecordCodecErrorCode::ok; }
};

class IRecordCodec {
 public:
  virtual ~IRecordCodec() = default;

  virtual RecordCodecResult decode(uint32_t typeId, const uint8_t* data,
                                   size_t size) = 0;
};

class RecordCodecRegistry final : public IRecordCodec {
 public:
  bool registerCodec(uint32_t typeId, std::shared_ptr<IRecordCodec> codec);

  RecordCodecResult decode(uint32_t typeId, const uint8_t* data,
                           size_t size) override;

 private:
  std::unordered_map<uint32_t, std::shared_ptr<IRecordCodec>> codecs_;
};

}  // namespace openspore::assets
