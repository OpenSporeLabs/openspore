// See Dbpf.hpp. Clean-room implementation, independently authored.
#include "Dbpf.hpp"

#include <cstring>

#include "Stream.hpp"

namespace openspore::assets {

namespace {

// Header field offsets in the 96-byte DBPF v3 header.
constexpr size_t kMagicSize = 4;
constexpr size_t kHeaderSize = 96;
constexpr size_t kOffIndexCount = 0x24;
constexpr size_t kOffIndexOffset = 0x40;
constexpr uint16_t kCompQfs = 0xFFFF;
constexpr uint32_t kSizeMask = 0x7FFFFFFFu;

uint32_t peekU32(const uint8_t* data, size_t size, size_t off, bool& ok) {
  if (off + 4 > size) {
    ok = false;
    return 0;
  }
  uint32_t v = 0;
  std::memcpy(&v, data + off, 4);
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  v = ((v & 0xFFu) << 24) | ((v & 0xFF00u) << 8) | ((v & 0xFF0000u) >> 8) |
      ((v & 0xFF000000u) >> 24);
#endif
  return v;
}

}  // namespace

bool parseDbpfIndex(const uint8_t* data, size_t size,
                    std::vector<DbpfEntry>& out, std::string& error) {
  out.clear();
  if (data == nullptr || size < kHeaderSize) {
    error = "dbpf: image smaller than 96-byte header";
    return false;
  }
  if (std::memcmp(data, "DBPF", kMagicSize) != 0) {
    if (std::memcmp(data, "DBBF", kMagicSize) == 0) {
      error = "dbpf: DBBF 64-bit variant not supported (offsets are 8 bytes)";
    } else {
      error = "dbpf: bad magic (want DBPF)";
    }
    return false;
  }
  bool ok = true;
  const uint32_t count = peekU32(data, size, kOffIndexCount, ok);
  const uint32_t indexOff = peekU32(data, size, kOffIndexOffset, ok);
  if (!ok) {
    error = "dbpf: truncated header";
    return false;
  }
  if (indexOff < kHeaderSize) {
    error = "dbpf: index offset overlaps header";
    return false;
  }
  if (static_cast<uint64_t>(indexOff) + 4 > size) {
    error = "dbpf: index offset past end of image";
    return false;
  }
  Reader r(data + indexOff, size - indexOff);
  const uint32_t flags = r.readU32();
  uint32_t sharedType = 0;
  uint32_t sharedGroup = 0;
  bool haveType = false;
  bool haveGroup = false;
  if ((flags & 1u) != 0u) {
    sharedType = r.readU32();
    haveType = true;
  }
  if ((flags & 2u) != 0u) {
    sharedGroup = r.readU32();
    haveGroup = true;
  }
  if ((flags & 4u) != 0u) {
    r.skip(4);
  }
  if (!r.ok()) {
    error = "dbpf: truncated index header";
    return false;
  }
  const size_t rowSize = 20u + (haveType ? 0u : 4u) + (haveGroup ? 0u : 4u);
  if (static_cast<uint64_t>(count) > r.remaining() / rowSize) {
    error = "dbpf: index count exceeds available bytes";
    return false;
  }
  out.reserve(count);
  for (uint32_t i = 0; i < count; ++i) {
    DbpfEntry e;
    e.type = haveType ? sharedType : r.readU32();
    e.group = haveGroup ? sharedGroup : r.readU32();
    e.instance = r.readU32();
    e.offset = r.readU32();
    e.storedSize = r.readU32() & kSizeMask;
    e.memSize = r.readU32();
    const uint16_t comp = r.readU16();
    r.skip(1);  // saved-game flag, not needed for extraction
    r.skip(1);  // padding
    e.compression = comp;
    e.compressed = (comp == kCompQfs);
    if (!r.ok()) {
      error = "dbpf: truncated index row " + std::to_string(i);
      out.clear();
      return false;
    }
    out.push_back(e);
  }
  return true;
}

bool qfsDecompress(const uint8_t* data, size_t size, std::vector<uint8_t>& out,
                   std::string& error) {
  out.clear();
  if (data == nullptr || size < 5) {
    error = "qfs: record shorter than 5-byte header";
    return false;
  }
  if ((data[0] != 0x10 && data[0] != 0x50) || data[1] != 0xFB) {
    error = "qfs: bad header magic (want 10FB or 50FB)";
    return false;
  }
  // Decompressed size is the only big-endian field in the stream.
  const size_t want = (static_cast<size_t>(data[2]) << 16) |
                      (static_cast<size_t>(data[3]) << 8) |
                      static_cast<size_t>(data[4]);
  out.resize(want);
  size_t in = 5;
  size_t pos = 0;
  auto need = [&](size_t n) { return in + n <= size; };
  while (pos < want) {
    if (!need(1)) {
      error = "qfs: truncated control byte";
      out.clear();
      return false;
    }
    const uint8_t c = data[in++];
    size_t literals = 0;
    size_t copies = 0;
    size_t back = 0;
    if (c >= 252) {
      literals = c & 3u;
    } else if (c >= 224) {
      literals = ((static_cast<size_t>(c) & 0x1Fu) << 2) + 4;
    } else if (c >= 192) {
      if (!need(3)) {
        error = "qfs: truncated long-match token";
        out.clear();
        return false;
      }
      const uint8_t b1 = data[in];
      const uint8_t b2 = data[in + 1];
      const uint8_t b3 = data[in + 2];
      in += 3;
      literals = c & 3u;
      copies = ((static_cast<size_t>(c) & 0x0Cu) << 6) + b3 + 5;
      back = ((static_cast<size_t>(c) & 0x10u) << 12) +
             (static_cast<size_t>(b1) << 8) + b2 + 1;
    } else if (c >= 128) {
      if (!need(2)) {
        error = "qfs: truncated mid-match token";
        out.clear();
        return false;
      }
      const uint8_t b1 = data[in];
      const uint8_t b2 = data[in + 1];
      in += 2;
      literals = (b1 & 0xC0u) >> 6;
      copies = (c & 0x3Fu) + 4;
      back = ((static_cast<size_t>(b1) & 0x3Fu) << 8) + b2 + 1;
    } else {
      if (!need(1)) {
        error = "qfs: truncated short-match token";
        out.clear();
        return false;
      }
      const uint8_t b1 = data[in++];
      literals = c & 3u;
      copies = ((c & 0x1Cu) >> 2) + 3;
      back = ((static_cast<size_t>(c) & 0x60u) << 3) + b1 + 1;
    }
    if (literals > 0) {
      if (!need(literals) || pos + literals > want) {
        error = "qfs: truncated literal run";
        out.clear();
        return false;
      }
      std::memcpy(out.data() + pos, data + in, literals);
      in += literals;
      pos += literals;
    }
    if (back > pos || pos + copies > want) {
      // A back-reference past the start, or output past the declared size,
      // means a corrupt or hostile stream: fail instead of overrunning.
      if (copies > 0 || back > pos) {
        error = "qfs: invalid back-reference";
        out.clear();
        return false;
      }
    }
    for (size_t k = 0; k < copies; ++k) {
      out[pos] = out[pos - back];
      ++pos;
    }
  }
  return true;
}

bool extractDbpfRecord(const uint8_t* pkg, size_t pkgSize,
                       const DbpfEntry& entry, std::vector<uint8_t>& out,
                       std::string& error) {
  out.clear();
  if (pkg == nullptr ||
      static_cast<uint64_t>(entry.offset) + entry.storedSize > pkgSize) {
    error = "dbpf: record extent past end of image";
    return false;
  }
  if (entry.compression != 0u && entry.compression != kCompQfs) {
    error = "dbpf: unsupported compression";
    return false;
  }
  const uint8_t* raw = pkg + entry.offset;
  if (!entry.compressed) {
    out.assign(raw, raw + entry.storedSize);
    return true;
  }
  if (!qfsDecompress(raw, entry.storedSize, out, error)) {
    return false;
  }
  if (out.size() != entry.memSize) {
    error = "dbpf: decompressed size " + std::to_string(out.size()) +
            " != index memSize " + std::to_string(entry.memSize);
    out.clear();
    return false;
  }
  return true;
}

int findDbpfEntry(const std::vector<DbpfEntry>& entries, uint32_t type,
                  uint32_t group, uint32_t instance) {
  for (size_t i = 0; i < entries.size(); ++i) {
    if (entries[i].type == type && entries[i].group == group &&
        entries[i].instance == instance) {
      return static_cast<int>(i);
    }
  }
  return -1;
}

}  // namespace openspore::assets
