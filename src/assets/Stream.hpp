// Clean-room OpenSpore asset helpers: little-endian byte cursor.
//
// Independently authored for OpenSpore; no EA code, no third-party code.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

namespace openspore::assets {

// Non-owning little-endian cursor over a byte range. Every read is
// bounds-checked: on overrun ok() latches false and further reads yield zero,
// so callers can chain reads and check ok() once at the end.
class Reader {
public:
  Reader(const uint8_t *data, size_t size) : data_(data), size_(size) {}
  explicit Reader(const std::vector<uint8_t> &bytes)
      : data_(bytes.data()), size_(bytes.size()) {}

  bool ok() const { return ok_; }
  size_t offset() const { return pos_; }
  size_t remaining() const { return pos_ < size_ ? size_ - pos_ : 0; }

  uint8_t readU8() {
    if (remaining() < 1) {
      ok_ = false;
      return 0;
    }
    return data_[pos_++];
  }

  uint16_t readU16() {
    if (remaining() < 2) {
      ok_ = false;
      return 0;
    }
    uint16_t v = 0;
    std::memcpy(&v, data_ + pos_, 2);
    pos_ += 2;
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    v = static_cast<uint16_t>((v << 8) | (v >> 8));
#endif
    return v;
  }

  uint32_t readU32() {
    if (remaining() < 4) {
      ok_ = false;
      return 0;
    }
    uint32_t v = 0;
    std::memcpy(&v, data_ + pos_, 4);
    pos_ += 4;
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    v = ((v & 0xFFu) << 24) | ((v & 0xFF00u) << 8) | ((v & 0xFF0000u) >> 8) |
        ((v & 0xFF000000u) >> 24);
#endif
    return v;
  }

  float readF32() {
    uint32_t bits = readU32();
    float v = 0.0F;
    std::memcpy(&v, &bits, 4);
    return v;
  }

  // Advances past n bytes; false (and latches !ok) when truncated.
  bool skip(size_t n) {
    if (remaining() < n) {
      ok_ = false;
      return false;
    }
    pos_ += n;
    return true;
  }

  // Borrows a pointer to n bytes at the cursor (into the source buffer).
  bool readView(size_t n, const uint8_t *&out) {
    if (remaining() < n) {
      ok_ = false;
      return false;
    }
    out = data_ + pos_;
    pos_ += n;
    return true;
  }

private:
  const uint8_t *data_ = nullptr;
  size_t size_ = 0;
  size_t pos_ = 0;
  bool ok_ = true;
};

} // namespace openspore::assets
