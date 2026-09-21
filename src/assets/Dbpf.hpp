// Clean-room DBPF v3 package reader + EA QFS (RefPack) decompressor.
//
// Independently authored for OpenSpore (behavior cross-checked against our own
// Python reference tool, never translated from it). Covers the 32-bit DBPF
// variant used by Spore's .package files: 96-byte header, inline file index,
// per-record QFS compression flag. The 64-bit DBBF variant is rejected.
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace openspore::assets {

// One file-index row: identity (type/group/instance) plus the on-disk extent
// and the decompressed size.
struct DbpfEntry {
  uint32_t type = 0;
  uint32_t group = 0;
  uint32_t instance = 0;
  uint32_t offset = 0; // byte offset of the stored (possibly compressed) record
  uint32_t storedSize = 0; // bytes on disk
  uint32_t memSize = 0;    // decompressed byte count
  bool compressed = false; // QFS/RefPack when true
};

// Parses the DBPF header + file index from a whole-package image.
// False + error on bad magic, truncated header/index, or DBBF input.
bool parseDbpfIndex(const uint8_t *data, size_t size,
                    std::vector<DbpfEntry> &out, std::string &error);

// EA QFS (RefPack) decompression over a stored record image.
// False + error on a bad magic header or truncated token stream.
bool qfsDecompress(const uint8_t *data, size_t size, std::vector<uint8_t> &out,
                   std::string &error);

// Extracts one record from the package image, decompressing when flagged.
// False + error when the extent runs past the image or decompression fails.
bool extractDbpfRecord(const uint8_t *pkg, size_t pkgSize,
                       const DbpfEntry &entry, std::vector<uint8_t> &out,
                       std::string &error);

// Linear lookup of an index row by identity; -1 when absent.
int findDbpfEntry(const std::vector<DbpfEntry> &entries, uint32_t type,
                  uint32_t group, uint32_t instance);

} // namespace openspore::assets
