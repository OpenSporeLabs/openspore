#include "ResourceStore.hpp"

#include "Dbpf.hpp"

namespace openspore::assets {
namespace {

ContentErrorCode classifyParseError(const std::string& error) {
  if (error.find("DBBF") != std::string::npos ||
      error.find("bad magic") != std::string::npos) {
    return ContentErrorCode::unsupported_format;
  }
  return ContentErrorCode::malformed_index;
}

}  // namespace

bool RecordLocator::withinExtent() const noexcept {
  return offset <= sourceSize &&
         static_cast<uint64_t>(storedSize) <= sourceSize - offset;
}

DbpfContentStore::DbpfContentStore(const uint8_t* packageData,
                                   size_t packageSize)
    : packageData_(packageData), packageSize_(packageSize) {
  if (packageData_ == nullptr) {
    parseErrorCode_ = ContentErrorCode::invalid_input;
    parseError_ = packageSize_ == 0 ? "resource: empty package image"
                                    : "resource: null package image";
    return;
  }
  if (packageSize_ == 0) {
    parseErrorCode_ = ContentErrorCode::invalid_input;
    parseError_ = "resource: empty package image";
    return;
  }
  if (!parseDbpfIndex(packageData_, packageSize_, entries_, parseError_)) {
    parseErrorCode_ = classifyParseError(parseError_);
    entries_.clear();
  }
}

LookupResult DbpfContentStore::lookup(const ResourceKey& key) const {
  if (!key.isComplete()) {
    return {ContentErrorCode::invalid_key,
            {},
            "resource: lookup requires a complete key"};
  }
  if (!parseError_.empty()) {
    return {parseErrorCode_, {}, parseError_};
  }
  const int index = findDbpfEntry(entries_, key.type, key.group, key.instance);
  if (index < 0) {
    return {ContentErrorCode::not_found,
            {},
            "resource: record not found in package"};
  }
  const DbpfEntry& entry = entries_[static_cast<size_t>(index)];
  RecordLocator locator;
  locator.key = key;
  locator.offset = entry.offset;
  locator.sourceSize = packageSize_;
  locator.storedSize = entry.storedSize;
  locator.memorySize = entry.memSize;
  locator.compression = entry.compression;
  if (!locator.withinExtent()) {
    return {ContentErrorCode::invalid_extent,
            {},
            "resource: record extent exceeds package image"};
  }
  if (entry.compression != 0u && entry.compression != 0xFFFFu) {
    return {ContentErrorCode::unsupported_compression,
            {},
            "resource: unsupported DBPF compression 0x" + [&entry] {
              static constexpr char kHex[] = "0123456789ABCDEF";
              std::string value(4, '0');
              for (size_t i = 0; i < value.size(); ++i) {
                const size_t shift = (value.size() - 1u - i) * 4u;
                value[i] = kHex[(entry.compression >> shift) & 0xFu];
              }
              return value;
            }()};
  }
  return {ContentErrorCode::ok, locator, {}};
}

ReadResult DbpfContentStore::read(const ResourceKey& key) const {
  const LookupResult located = lookup(key);
  if (!located) {
    return {located.code, {}, located.error};
  }
  const int index = findDbpfEntry(entries_, key.type, key.group, key.instance);
  if (index < 0) {
    return {ContentErrorCode::not_found,
            {},
            "resource: record disappeared after lookup"};
  }
  std::vector<uint8_t> bytes;
  std::string error;
  if (!extractDbpfRecord(packageData_, packageSize_,
                         entries_[static_cast<size_t>(index)], bytes, error)) {
    if (entries_[static_cast<size_t>(index)].compression == 0xFFFFu) {
      std::vector<uint8_t> decompressed;
      std::string qfsError;
      if (qfsDecompress(packageData_ + located.locator.offset,
                        located.locator.storedSize, decompressed, qfsError) &&
          decompressed.size() != located.locator.memorySize) {
        return {ContentErrorCode::size_mismatch, {}, error};
      }
    }
    return {ContentErrorCode::decompression_failed, {}, error};
  }
  if (bytes.size() != located.locator.memorySize) {
    return {ContentErrorCode::size_mismatch,
            {},
            "resource: extracted size does not match DBPF memSize"};
  }
  return {ContentErrorCode::ok, std::move(bytes), {}};
}

LookupResult ResourceProviderContentStore::lookup(
    const ResourceKey& key) const {
  if (!key.isComplete()) {
    return {ContentErrorCode::invalid_key,
            {},
            "resource: lookup requires a complete key"};
  }
  return {ContentErrorCode::unsupported_operation,
          {},
          "resource: IResourceProvider does not expose record locators"};
}

ReadResult ResourceProviderContentStore::read(const ResourceKey& key) const {
  if (!key.isComplete()) {
    return {ContentErrorCode::invalid_key,
            {},
            "resource: read requires a complete key"};
  }
  std::vector<uint8_t> bytes;
  std::string error;
  if (provider_ == nullptr ||
      !provider_->fetch(key.type, key.group, key.instance, bytes, error)) {
    return {ContentErrorCode::provider_failure, {}, error};
  }
  return {ContentErrorCode::ok, std::move(bytes), {}};
}

bool RecordCodecRegistry::registerCodec(uint32_t typeId,
                                        std::shared_ptr<IRecordCodec> codec) {
  if (!codec) {
    return false;
  }
  return codecs_.emplace(typeId, std::move(codec)).second;
}

RecordCodecResult RecordCodecRegistry::decode(uint32_t typeId,
                                              const uint8_t* data,
                                              size_t size) {
  const auto found = codecs_.find(typeId);
  if (found == codecs_.end()) {
    return {RecordCodecErrorCode::unsupported_type,
            {},
            "record codec: unsupported type"};
  }
  if (size != 0 && data == nullptr) {
    return {
        RecordCodecErrorCode::invalid_input, {}, "record codec: null input"};
  }
  RecordCodecResult result = found->second->decode(typeId, data, size);
  if (result.code != RecordCodecErrorCode::ok) {
    result.record.reset();
    return result;
  }
  if (!result.record.has_value()) {
    return {RecordCodecErrorCode::decode_failed,
            {},
            "record codec: decoder returned no typed record"};
  }
  return result;
}

}  // namespace openspore::assets
