// Clean-room compatibility boundary B1: resource access.
//
// Semantic responsibility: fetch record bytes by (type, group, instance)
// identity, hiding whether the bytes come from a DBPF package, memory, or
// (later) the original resource manager. Independently authored; adapts the
// existing src/assets/Dbpf.* parser, copies no EA code.
#pragma once

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

#include "assets/Dbpf.hpp"

namespace openspore::compat {

// Abstract record source. Producers: DbpfResourceProvider (real packages),
// MemoryResourceProvider (test stub standing in for the original side).
// Consumer: fetchGmdlModel (MeshSource.hpp) and any future loader.
class IResourceProvider {
 public:
  virtual ~IResourceProvider() = default;
  // False + error when the identity is absent or the record is unreadable.
  virtual bool fetch(uint32_t type, uint32_t group, uint32_t instance,
                     std::vector<uint8_t> &out, std::string &error) = 0;
};

// Production side: serves records from one borrowed DBPF package image
// (must outlive the provider). The index is re-parsed per fetch: stateless
// and cheap (28-byte rows).
class DbpfResourceProvider : public IResourceProvider {
 public:
  DbpfResourceProvider(const uint8_t *pkg, size_t size)
      : pkg_(pkg), size_(size) {}

  bool fetch(uint32_t type, uint32_t group, uint32_t instance,
             std::vector<uint8_t> &out, std::string &error) override {
    std::vector<assets::DbpfEntry> entries;
    if (!assets::parseDbpfIndex(pkg_, size_, entries, error)) {
      return false;
    }
    const int at = assets::findDbpfEntry(entries, type, group, instance);
    if (at < 0) {
      error = "compat: record not in package";
      return false;
    }
    return assets::extractDbpfRecord(pkg_, size_,
                                     entries[static_cast<size_t>(at)], out,
                                     error);
  }

 private:
  const uint8_t *pkg_;
  size_t size_;
};

// Original-side stub for tests: an in-memory identity -> bytes map. Lets the
// same consumer code run against "whatever the original would return"
// without a game install, demonstrating substitutability at the seam.
class MemoryResourceProvider : public IResourceProvider {
 public:
  void store(uint32_t type, uint32_t group, uint32_t instance,
             std::vector<uint8_t> bytes) {
    records_[std::make_tuple(type, group, instance)] = std::move(bytes);
  }

  bool fetch(uint32_t type, uint32_t group, uint32_t instance,
             std::vector<uint8_t> &out, std::string &error) override {
    const auto it = records_.find(std::make_tuple(type, group, instance));
    if (it == records_.end()) {
      error = "compat: record not in stub";
      return false;
    }
    out = it->second;
    return true;
  }

 private:
  std::map<std::tuple<uint32_t, uint32_t, uint32_t>, std::vector<uint8_t>>
      records_;
};

static_assert(std::is_base_of<IResourceProvider, DbpfResourceProvider>::value,
              "DBPF provider must satisfy the resource seam");
static_assert(std::is_base_of<IResourceProvider, MemoryResourceProvider>::value,
              "memory stub must satisfy the resource seam");

}  // namespace openspore::compat
