// Clean-room OpenSpore asset helpers: little-endian byte cursor.
//
// Independently authored for OpenSpore; no EA code, no third-party code.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace openspore::assets {

// Non-owning little-endian cursor over a byte range. Every read is
// bounds-checked: on overrun ok() latches false and further reads yield zero,
// so callers can chain reads and check ok() once at the end.
class Reader {
 public:
  Reader(const uint8_t* data, size_t size) : data_(data), size_(size) {}
  explicit Reader(const std::vector<uint8_t>& bytes)
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

  // Big-endian u32. Only the GMDL refCount word is stored BE on v8 records.
  uint32_t readU32BE() {
    if (remaining() < 4) {
      ok_ = false;
      return 0;
    }
    const uint8_t* p = data_ + pos_;
    pos_ += 4;
    return (static_cast<uint32_t>(p[0]) << 24) |
           (static_cast<uint32_t>(p[1]) << 16) |
           (static_cast<uint32_t>(p[2]) << 8) | static_cast<uint32_t>(p[3]);
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
  bool readView(size_t n, const uint8_t*& out) {
    if (remaining() < n) {
      ok_ = false;
      return false;
    }
    out = data_ == nullptr ? nullptr : data_ + pos_;
    pos_ += n;
    return true;
  }

 private:
  const uint8_t* data_ = nullptr;
  size_t size_ = 0;
  size_t pos_ = 0;
  bool ok_ = true;
};

enum class StreamStatus {
  ok,
  closed,
  already_closed,
  invalid_argument,
  short_read,
  short_write,
  io_error,
  unsupported,
};

struct StreamResult {
  StreamStatus status = StreamStatus::ok;
  size_t bytesTransferred = 0;
  std::string error;

  explicit operator bool() const { return status == StreamStatus::ok; }
};

class IStream {
 public:
  virtual ~IStream() = default;

  StreamResult read_exact(void* destination, size_t size);
  StreamResult write_all(const void* source, size_t size);
  StreamResult close();

 protected:
  virtual StreamResult read_some(void* destination, size_t size) = 0;
  virtual StreamResult write_some(const void* source, size_t size) = 0;
  virtual StreamResult do_close() { return {}; }

  bool isClosed() const { return closed_; }

 private:
  bool closed_ = false;
};

class MemoryInputStream final : public IStream {
 public:
  MemoryInputStream(const uint8_t* data, size_t size)
      : data_(data), size_(size) {}
  explicit MemoryInputStream(const std::vector<uint8_t>& bytes)
      : MemoryInputStream(bytes.data(), bytes.size()) {}

  size_t position() const { return position_; }
  size_t remaining() const { return position_ < size_ ? size_ - position_ : 0; }

 protected:
  StreamResult read_some(void* destination, size_t size) override;
  StreamResult write_some(const void*, size_t) override;

 private:
  const uint8_t* data_ = nullptr;
  size_t size_ = 0;
  size_t position_ = 0;
};

class MemoryOutputStream final : public IStream {
 public:
  explicit MemoryOutputStream(std::vector<uint8_t> initial = {},
                              size_t maxWriteSize = 0)
      : bytes_(std::move(initial)), maxWriteSize_(maxWriteSize) {}

  void setMaxWriteSize(size_t maxWriteSize) { maxWriteSize_ = maxWriteSize; }
  const std::vector<uint8_t>& bytes() const { return bytes_; }
  std::vector<uint8_t> take() { return std::move(bytes_); }

 protected:
  StreamResult read_some(void*, size_t) override;
  StreamResult write_some(const void* source, size_t size) override;

 private:
  std::vector<uint8_t> bytes_;
  size_t maxWriteSize_ = 0;
};

inline StreamResult IStream::read_exact(void* destination, size_t size) {
  if (size != 0 && destination == nullptr) {
    return {StreamStatus::invalid_argument, 0, "stream: null read destination"};
  }
  if (closed_) {
    return {StreamStatus::closed, 0, "stream: read after close"};
  }
  if (size == 0) {
    return {};
  }
  auto* current = static_cast<uint8_t*>(destination);
  size_t transferred = 0;
  while (transferred < size) {
    const StreamResult result =
        read_some(current + transferred, size - transferred);
    if (result.bytesTransferred > size - transferred) {
      return {StreamStatus::io_error, transferred,
              "stream: read count exceeds request"};
    }
    transferred += result.bytesTransferred;
    if (result.status != StreamStatus::ok) {
      return {result.status, transferred, result.error};
    }
    if (result.bytesTransferred == 0) {
      return {StreamStatus::short_read, transferred,
              "stream: read made no progress"};
    }
  }
  return {StreamStatus::ok, size, {}};
}

inline StreamResult IStream::write_all(const void* source, size_t size) {
  if (size != 0 && source == nullptr) {
    return {StreamStatus::invalid_argument, 0, "stream: null write source"};
  }
  if (closed_) {
    return {StreamStatus::closed, 0, "stream: write after close"};
  }
  if (size == 0) {
    return {};
  }
  const auto* current = static_cast<const uint8_t*>(source);
  size_t transferred = 0;
  while (transferred < size) {
    const StreamResult result =
        write_some(current + transferred, size - transferred);
    if (result.bytesTransferred > size - transferred) {
      return {StreamStatus::io_error, transferred,
              "stream: write count exceeds request"};
    }
    transferred += result.bytesTransferred;
    if (result.status != StreamStatus::ok) {
      return {result.status, transferred, result.error};
    }
    if (result.bytesTransferred == 0) {
      return {StreamStatus::short_write, transferred,
              "stream: write made no progress"};
    }
  }
  return {StreamStatus::ok, size, {}};
}

inline StreamResult IStream::close() {
  if (closed_) {
    return {StreamStatus::already_closed, 0, "stream: already closed"};
  }
  StreamResult result = do_close();
  if (result.status == StreamStatus::ok) {
    closed_ = true;
  }
  return result;
}

inline StreamResult MemoryInputStream::read_some(void* destination,
                                                 size_t size) {
  if (size == 0) {
    return {};
  }
  if (data_ == nullptr && size_ != 0) {
    return {StreamStatus::invalid_argument, 0,
            "stream: input has no backing data"};
  }
  if (remaining() == 0) {
    return {StreamStatus::short_read, 0, "stream: end of input"};
  }
  const size_t count = size < remaining() ? size : remaining();
  std::memcpy(destination, data_ + position_, count);
  position_ += count;
  return {StreamStatus::ok, count, {}};
}

inline StreamResult MemoryInputStream::write_some(const void*, size_t) {
  return {StreamStatus::unsupported, 0, "stream: input is read-only"};
}

inline StreamResult MemoryOutputStream::read_some(void*, size_t) {
  return {StreamStatus::unsupported, 0, "stream: output is write-only"};
}

inline StreamResult MemoryOutputStream::write_some(const void* source,
                                                   size_t size) {
  if (size == 0) {
    return {};
  }
  size_t count = size;
  if (maxWriteSize_ != 0 && count > maxWriteSize_) {
    count = maxWriteSize_;
  }
  const auto* current = static_cast<const uint8_t*>(source);
  bytes_.insert(bytes_.end(), current, current + count);
  return {StreamStatus::ok, count, {}};
}

}  // namespace openspore::assets
