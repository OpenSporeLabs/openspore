#include "PropertyStore.hpp"

#include <algorithm>
#include <cstring>
#include <utility>

namespace openspore::assets {
namespace {

constexpr uint8_t kFormatVersion = 1;

uint32_t readU32(const uint8_t* data) {
  return static_cast<uint32_t>(data[0]) |
         (static_cast<uint32_t>(data[1]) << 8u) |
         (static_cast<uint32_t>(data[2]) << 16u) |
         (static_cast<uint32_t>(data[3]) << 24u);
}

void writeU32(uint32_t value, uint8_t* data) {
  data[0] = static_cast<uint8_t>(value & 0xFFu);
  data[1] = static_cast<uint8_t>((value >> 8u) & 0xFFu);
  data[2] = static_cast<uint8_t>((value >> 16u) & 0xFFu);
  data[3] = static_cast<uint8_t>((value >> 24u) & 0xFFu);
}

PropertyResult streamFailure(const StreamResult& result,
                             const char* operation) {
  return {PropertyErrorCode::stream_failure,
          std::string("property: ") + operation + ": " + result.error};
}

PropertyResult readValue(IStream& stream, PropertyType type,
                         PropertyValue& value) {
  uint8_t bytes[12] = {};
  if (type == PropertyType::boolean) {
    const StreamResult result = stream.read_exact(bytes, 1);
    if (!result) {
      return streamFailure(result, "read bool");
    }
    if (bytes[0] > 1u) {
      return {PropertyErrorCode::malformed_data,
              "property: bool value must be 0 or 1"};
    }
    value = bytes[0] != 0u;
    return {};
  }
  if (type == PropertyType::int32 || type == PropertyType::uint32 ||
      type == PropertyType::float32) {
    const StreamResult result = stream.read_exact(bytes, 4);
    if (!result) {
      return streamFailure(result, "read scalar");
    }
    const uint32_t bits = readU32(bytes);
    if (type == PropertyType::int32) {
      int32_t number = 0;
      std::memcpy(&number, &bits, sizeof(number));
      value = number;
    } else if (type == PropertyType::uint32) {
      value = bits;
    } else {
      float number = 0.0F;
      std::memcpy(&number, &bits, sizeof(number));
      value = number;
    }
    return {};
  }
  if (type == PropertyType::key) {
    const StreamResult result = stream.read_exact(bytes, sizeof(bytes));
    if (!result) {
      return streamFailure(result, "read key");
    }
    ResourceKey key;
    key.type = readU32(bytes);
    key.group = readU32(bytes + 4);
    key.instance = readU32(bytes + 8);
    value = key;
    return {};
  }
  return {PropertyErrorCode::unsupported_property,
          "property: unsupported type tag " +
              std::to_string(static_cast<unsigned int>(type))};
}

PropertyResult writeValue(IStream& stream, const PropertyEntry& entry) {
  uint8_t bytes[12] = {};
  if (const auto* value = std::get_if<bool>(&entry.value)) {
    bytes[0] = *value ? 1u : 0u;
    const StreamResult result = stream.write_all(bytes, 1);
    return result ? PropertyResult{} : streamFailure(result, "write bool");
  }
  if (const auto* value = std::get_if<int32_t>(&entry.value)) {
    writeU32(static_cast<uint32_t>(*value), bytes);
    const StreamResult result = stream.write_all(bytes, 4);
    return result ? PropertyResult{} : streamFailure(result, "write int32");
  }
  if (const auto* value = std::get_if<uint32_t>(&entry.value)) {
    writeU32(*value, bytes);
    const StreamResult result = stream.write_all(bytes, 4);
    return result ? PropertyResult{} : streamFailure(result, "write uint32");
  }
  if (const auto* value = std::get_if<float>(&entry.value)) {
    uint32_t bits = 0;
    std::memcpy(&bits, value, sizeof(bits));
    writeU32(bits, bytes);
    const StreamResult result = stream.write_all(bytes, 4);
    return result ? PropertyResult{} : streamFailure(result, "write float");
  }
  const auto* key = std::get_if<ResourceKey>(&entry.value);
  if (key == nullptr) {
    return {PropertyErrorCode::unsupported_property,
            "property: unsupported value variant"};
  }
  writeU32(key->type, bytes);
  writeU32(key->group, bytes + 4);
  writeU32(key->instance, bytes + 8);
  const StreamResult result = stream.write_all(bytes, sizeof(bytes));
  return result ? PropertyResult{} : streamFailure(result, "write key");
}

}  // namespace

LocalPropertyStore::LocalPropertyStore(const IPropertyStore* parent,
                                       PropertyLimits limits)
    : parent_(parent), limits_(limits) {}

PropertyType typeOf(const PropertyValue& value) noexcept {
  if (std::holds_alternative<bool>(value)) {
    return PropertyType::boolean;
  }
  if (std::holds_alternative<int32_t>(value)) {
    return PropertyType::int32;
  }
  if (std::holds_alternative<uint32_t>(value)) {
    return PropertyType::uint32;
  }
  if (std::holds_alternative<float>(value)) {
    return PropertyType::float32;
  }
  return PropertyType::key;
}

PropertyResult LocalPropertyStore::set_local(uint32_t id, PropertyValue value) {
  const bool inserted = values_.find(id) == values_.end();
  if (inserted && values_.size() >= limits_.maxEntries) {
    return {PropertyErrorCode::limit_exceeded,
            "property: local entry limit exceeded"};
  }
  values_[id] = std::move(value);
  ++operationCount_;
  return {};
}

PropertyResult LocalPropertyStore::get(uint32_t id,
                                       PropertyValue& value) const {
  std::vector<const IPropertyStore*> visited;
  const IPropertyStore* current = this;
  size_t depth = 0;
  while (current != nullptr) {
    const PropertyResult local = current->get_local(id, value);
    if (local.code != PropertyErrorCode::not_found) {
      return local;
    }
    const IPropertyStore* next = current->parent();
    if (next == nullptr) {
      return {PropertyErrorCode::not_found, "property: not found"};
    }
    if (std::find(visited.begin(), visited.end(), current) != visited.end()) {
      return {PropertyErrorCode::parent_cycle, "property: parent lookup cycle"};
    }
    visited.push_back(current);
    if (depth >= kMaxParentDepth) {
      return {PropertyErrorCode::parent_depth_exceeded,
              "property: parent lookup depth exceeded"};
    }
    current = next;
    ++depth;
  }
  return {PropertyErrorCode::not_found, "property: not found"};
}

PropertyResult LocalPropertyStore::get_local(uint32_t id,
                                             PropertyValue& value) const {
  const auto found = values_.find(id);
  if (found == values_.end()) {
    return {PropertyErrorCode::not_found, "property: not found locally"};
  }
  value = found->second;
  return {};
}

PropertyResult LocalPropertyStore::read_local(IStream& stream) {
  uint8_t header[8] = {};
  StreamResult result = stream.read_exact(header, sizeof(header));
  if (!result) {
    return streamFailure(result, "read header");
  }
  if (header[0] != 'O' || header[1] != 'P' || header[2] != 'R' ||
      header[3] != 'P') {
    return {PropertyErrorCode::unsupported_format,
            "property: unsupported local property format"};
  }
  if (header[4] != kFormatVersion || header[5] != 0u) {
    return {PropertyErrorCode::unsupported_version,
            "property: unsupported local property version"};
  }
  if (header[6] != 0u || header[7] != 0u) {
    return {PropertyErrorCode::malformed_data,
            "property: nonzero reserved header bytes"};
  }
  uint8_t countBytes[4] = {};
  result = stream.read_exact(countBytes, sizeof(countBytes));
  if (!result) {
    return streamFailure(result, "read count");
  }
  const uint32_t count = readU32(countBytes);
  if (static_cast<size_t>(count) > limits_.maxEntries) {
    return {PropertyErrorCode::limit_exceeded,
            "property: decoded entry count exceeds limit"};
  }
  values_.clear();
  for (uint32_t index = 0; index < count; ++index) {
    uint8_t idBytes[4] = {};
    result = stream.read_exact(idBytes, sizeof(idBytes));
    if (!result) {
      return streamFailure(result, "read property id");
    }
    const uint32_t id = readU32(idBytes);
    if (values_.find(id) != values_.end()) {
      return {PropertyErrorCode::duplicate_id,
              "property: duplicate local property id"};
    }
    uint8_t typeByte = 0;
    result = stream.read_exact(&typeByte, 1);
    if (!result) {
      return streamFailure(result, "read property type");
    }
    PropertyValue value = false;
    const PropertyResult decoded =
        readValue(stream, static_cast<PropertyType>(typeByte), value);
    if (!decoded) {
      return decoded;
    }
    values_.emplace(id, std::move(value));
  }
  return {};
}

PropertyResult LocalPropertyStore::write_local(
    IStream& stream, const std::vector<PropertyEntry>& entries) {
  if (entries.size() > limits_.maxEntries) {
    return {PropertyErrorCode::limit_exceeded,
            "property: local entry limit exceeded"};
  }
  std::vector<PropertyEntry> ordered = entries;
  std::sort(ordered.begin(), ordered.end(),
            [](const PropertyEntry& lhs, const PropertyEntry& rhs) {
              return lhs.id < rhs.id;
            });
  for (size_t index = 1; index < ordered.size(); ++index) {
    if (ordered[index - 1].id == ordered[index].id) {
      return {PropertyErrorCode::duplicate_id,
              "property: duplicate local property id"};
    }
  }
  uint8_t header[8] = {'O', 'P', 'R', 'P', kFormatVersion, 0, 0, 0};
  uint8_t countBytes[4] = {};
  writeU32(static_cast<uint32_t>(ordered.size()), countBytes);
  StreamResult result = stream.write_all(header, sizeof(header));
  if (!result) {
    return streamFailure(result, "write header");
  }
  result = stream.write_all(countBytes, sizeof(countBytes));
  if (!result) {
    return streamFailure(result, "write count");
  }
  for (const PropertyEntry& entry : ordered) {
    uint8_t idBytes[4] = {};
    writeU32(entry.id, idBytes);
    result = stream.write_all(idBytes, sizeof(idBytes));
    if (!result) {
      return streamFailure(result, "write property id");
    }
    const uint8_t type = static_cast<uint8_t>(typeOf(entry.value));
    result = stream.write_all(&type, 1);
    if (!result) {
      return streamFailure(result, "write property type");
    }
    const PropertyResult written = writeValue(stream, entry);
    if (!written) {
      return written;
    }
  }
  return {};
}

std::vector<PropertyEntry> LocalPropertyStore::entries() const {
  std::vector<PropertyEntry> result;
  result.reserve(values_.size());
  for (const auto& entry : values_) {
    result.push_back({entry.first, entry.second});
  }
  return result;
}

}  // namespace openspore::assets
