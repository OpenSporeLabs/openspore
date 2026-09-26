#include "pkg_record_io_wave6.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG_RECORD_IO_THISCALL __thiscall
#else
#define PKG_RECORD_IO_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_record_io_wave6 {
namespace {

template <typename Value>
Value load(const void* base, std::size_t offset) {
  Value value{};
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store(void* base, std::size_t offset, Value value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + offset, &value, sizeof(value));
}

template <typename Function>
Function load_slot(OpaqueIStream* stream, std::size_t offset) {
  static_assert(sizeof(Function) == sizeof(std::uint32_t),
                "x86-32 function pointer width");
  const std::uint32_t word = load<std::uint32_t>(stream->vtable, offset);
  Function function{};
  std::memcpy(&function, &word, sizeof(function));
  return function;
}

using StateSlot = std::uint32_t(PKG_RECORD_IO_THISCALL*)(OpaqueIStream*);
using ReadDataSlot = void(PKG_RECORD_IO_THISCALL*)(OpaqueIStream*, void*,
                                                   std::uint32_t);
using SeekSlot = std::uint32_t(PKG_RECORD_IO_THISCALL*)(OpaqueIStream*,
                                                        std::int32_t,
                                                        std::uint32_t);
using ReadSlot = std::int32_t(PKG_RECORD_IO_THISCALL*)(OpaqueIStream*,
                                                       std::uint32_t, void*);

constexpr std::size_t kRecordReadFallback = 0x04;
constexpr std::size_t kRecordReadPrimary = 0x28;
constexpr std::size_t kRecordWriteState = 0x48;
constexpr std::size_t kRecordWriteEmbeddedStream = 0x0c;
constexpr std::size_t kRecordWritePosition = 0x40;
constexpr std::size_t kRecordWriteLimit = 0x44;

void default_prepare(OpaqueRecordWrite*) {}

bool default_read(OpaqueRecordWrite*, void*, std::uint32_t, std::uint32_t) {
  return false;
}

RecordWritePorts ports{default_prepare, default_read};

}

void record_io_set_record_write_ports(RecordWritePorts new_ports) {
  ports.prepare =
      new_ports.prepare == nullptr ? default_prepare : new_ports.prepare;
  ports.read = new_ports.read == nullptr ? default_read : new_ports.read;
}

void PKG_RECORD_IO_THISCALL record_read_data_008dc820(OpaqueRecordRead* record,
                                                      void* data,
                                                      std::uint32_t size) {
  OpaqueIStream* primary =
      reinterpret_cast<OpaqueIStream*>(record->bytes + kRecordReadPrimary);
  OpaqueIStream* fallback =
      reinterpret_cast<OpaqueIStream*>(record->bytes + kRecordReadFallback);
  const StateSlot state = load_slot<StateSlot>(primary, 0x10u);
  if (state(primary) != 0u) {
    const ReadDataSlot read = load_slot<ReadDataSlot>(primary, 0x28u);
    read(primary, data, size);
    return;
  }
  const ReadDataSlot read = load_slot<ReadDataSlot>(fallback, 0x28u);
  read(fallback, data, size);
}

bool PKG_RECORD_IO_THISCALL record_write_seek_008dcab0(
    OpaqueRecordWrite* record, std::int32_t amount, std::uint32_t operation) {
  auto* state = record->bytes + 0x20u;
  if (load<std::uint32_t>(state - 0x04u, 0u) == 0u) {
    return false;
  }
  auto* receiver = reinterpret_cast<OpaqueRecordWrite*>(state - 0x20u);
  ports.prepare(receiver);
  if (load<std::uint8_t>(state, kRecordWriteState) != 0u) {
    OpaqueIStream* stream =
        reinterpret_cast<OpaqueIStream*>(state + kRecordWriteEmbeddedStream);
    const SeekSlot seek = load_slot<SeekSlot>(stream, 0x28u);
    return seek(stream, amount, operation) != 0u;
  }

  std::uint32_t position = load<std::uint32_t>(state, kRecordWritePosition);
  const std::uint32_t limit = load<std::uint32_t>(state, kRecordWriteLimit);
  const std::uint32_t signed_amount = static_cast<std::uint32_t>(amount);
  const std::uint32_t magnitude = 0u - signed_amount;

  if (operation == 0u) {
    if (amount < 0) {
      position = 0u;
    } else if (signed_amount > limit) {
      position = limit;
    } else {
      position = signed_amount;
    }
  } else if (operation == 1u) {
    if (amount < 0) {
      position = magnitude > position ? 0u : position + signed_amount;
    } else if (position + signed_amount > limit) {
      position = limit;
    } else {
      position += signed_amount;
    }
  } else if (operation == 2u) {
    if (amount < 0) {
      position = magnitude > limit ? 0u : limit + signed_amount;
    } else {
      position = signed_amount > limit ? limit : signed_amount;
    }
  }
  store<std::uint32_t>(state, kRecordWritePosition, position);
  return true;
}

std::int32_t PKG_RECORD_IO_THISCALL record_write_read_008dcb70(
    OpaqueRecordWrite* record, std::uint32_t size, void* data) {
  auto* state = record->bytes + 0x20u;
  if (load<std::uint32_t>(state - 0x04u, 0u) == 0u) {
    return -1;
  }
  auto* receiver = reinterpret_cast<OpaqueRecordWrite*>(state - 0x20u);
  ports.prepare(receiver);
  if (load<std::uint8_t>(state, kRecordWriteState) != 0u) {
    OpaqueIStream* stream =
        reinterpret_cast<OpaqueIStream*>(state + kRecordWriteEmbeddedStream);
    const ReadSlot read = load_slot<ReadSlot>(stream, 0x30u);
    return read(stream, size, data);
  }

  std::uint32_t position = load<std::uint32_t>(state, kRecordWritePosition);
  const std::uint32_t limit = load<std::uint32_t>(state, kRecordWriteLimit);
  const std::uint32_t end_position = position + size;
  std::uint32_t available = size;
  if (limit < end_position || end_position < position) {
    available = limit - position;
  }
  if (available != 0u && !ports.read(receiver, data, position, available)) {
    available = 0u;
  }
  position += available;
  store<std::uint32_t>(state, kRecordWritePosition, position);
  return static_cast<std::int32_t>(available);
}

bool PKG_RECORD_IO_THISCALL fixed_memory_stream_seek_0093b950(
    OpaqueFixedMemoryStream* stream, std::int32_t amount,
    std::uint32_t operation) {
  std::uint32_t position = load<std::uint32_t>(stream->bytes, 0x14u);
  const std::uint32_t size = load<std::uint32_t>(stream->bytes, 0x0cu);
  const std::uint32_t word = static_cast<std::uint32_t>(amount);
  if (operation == 0u) {
    position = word;
  } else if (operation == 1u) {
    position += word;
  } else if (operation == 2u) {
    position = size + word;
  }
  if (position <= size) {
    store<std::uint32_t>(stream->bytes, 0x14u, position);
    return true;
  }
  store<std::uint32_t>(stream->bytes, 0x14u, size);
  return false;
}

}

#undef PKG_RECORD_IO_THISCALL
