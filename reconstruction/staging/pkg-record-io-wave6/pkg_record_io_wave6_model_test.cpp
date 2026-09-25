#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

#include "pkg_record_io_wave6.hpp"

#if defined(_MSC_VER)
#define PKG_RECORD_IO_TEST_THISCALL __thiscall
#else
#define PKG_RECORD_IO_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

using openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream;
using openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream;
using openspore::reconstruction::pkg_record_io_wave6::OpaqueIStreamVtable;
using openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead;
using openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite;
using openspore::reconstruction::pkg_record_io_wave6::RecordWritePorts;
using openspore::reconstruction::pkg_record_io_wave6::
    fixed_memory_stream_seek_0093b950;
using openspore::reconstruction::pkg_record_io_wave6::
    record_io_set_record_write_ports;
using openspore::reconstruction::pkg_record_io_wave6::
    record_read_data_008dc820;
using openspore::reconstruction::pkg_record_io_wave6::
    record_write_read_008dcb70;
using openspore::reconstruction::pkg_record_io_wave6::
    record_write_seek_008dcab0;

std::vector<std::string> events;
std::array<std::uint8_t, 32> source{{0}};
OpaqueIStream* observed_stream;
void* observed_data;
std::uint32_t observed_size;
std::int32_t observed_amount;
std::uint32_t observed_operation;
std::uint32_t state_result;
bool read_result;
std::uint32_t memory_seek_result;
std::int32_t memory_read_result;

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
void set_slot(OpaqueIStreamVtable& vtable, std::size_t offset,
              Function function) {
  const std::uintptr_t raw = reinterpret_cast<std::uintptr_t>(function);
  const std::uint32_t word = static_cast<std::uint32_t>(raw);
  std::memcpy(reinterpret_cast<std::uint8_t*>(&vtable.slots[0]) + offset,
              &word, sizeof(word));
}

void store_stream(void* base, std::size_t offset, OpaqueIStream* stream) {
  const std::uintptr_t raw = reinterpret_cast<std::uintptr_t>(stream);
  store<std::uint32_t>(base, offset, static_cast<std::uint32_t>(raw));
}

std::uint32_t PKG_RECORD_IO_TEST_THISCALL state_slot(OpaqueIStream* stream) {
  events.push_back("state");
  observed_stream = stream;
  return state_result;
}

void PKG_RECORD_IO_TEST_THISCALL read_data_slot(OpaqueIStream* stream,
                                                void* data,
                                                std::uint32_t size) {
  events.push_back("read-data");
  observed_stream = stream;
  observed_data = data;
  observed_size = size;
  if (data != nullptr && size != 0u) {
    const std::uint32_t count =
        size < source.size() ? size : static_cast<std::uint32_t>(source.size());
    std::memcpy(data, source.data(), count);
  }
}

void prepare_record(OpaqueRecordWrite* record) {
  events.push_back("prepare");
  observed_stream = reinterpret_cast<OpaqueIStream*>(record);
}

bool read_record(OpaqueRecordWrite*, void* data, std::uint32_t position,
                 std::uint32_t size) {
  events.push_back("read-record");
  observed_stream = nullptr;
  observed_data = data;
  observed_size = size;
  observed_amount = static_cast<std::int32_t>(position);
  if (!read_result) {
    return false;
  }
  if (data != nullptr && size != 0u) {
    std::memcpy(data, source.data() + position, size);
  }
  return true;
}

std::uint32_t PKG_RECORD_IO_TEST_THISCALL memory_seek_slot(
    OpaqueIStream* stream, std::int32_t amount, std::uint32_t operation) {
  events.push_back("memory-seek");
  observed_stream = stream;
  observed_amount = amount;
  observed_operation = operation;
  return memory_seek_result;
}

std::int32_t PKG_RECORD_IO_TEST_THISCALL memory_read_slot(
    OpaqueIStream* stream, std::uint32_t size, void* data) {
  events.push_back("memory-read");
  observed_stream = stream;
  observed_size = size;
  observed_data = data;
  return memory_read_result;
}

void reset() {
  events.clear();
  for (std::uint8_t& value : source) {
    value = 0u;
  }
  for (std::size_t index = 0; index < source.size(); ++index) {
    source[index] = static_cast<std::uint8_t>(index + 1u);
  }
  observed_stream = nullptr;
  observed_data = nullptr;
  observed_size = 0u;
  observed_amount = 0;
  observed_operation = 0u;
  state_result = 1u;
  read_result = true;
  memory_seek_result = 1u;
  memory_read_result = 0;
  record_io_set_record_write_ports(RecordWritePorts{prepare_record, read_record});
}

void initialize_record(OpaqueRecordWrite& record, std::uint32_t position,
                       std::uint32_t limit, std::uint8_t state) {
  std::memset(record.bytes, 0, sizeof(record.bytes));
  store<std::uint32_t>(record.bytes, 0x1c, 1u);
  store<std::uint32_t>(record.bytes, 0x60, position);
  store<std::uint32_t>(record.bytes, 0x64, limit);
  store<std::uint8_t>(record.bytes, 0x68, state);
}

void test_record_read_dispatch() {
  reset();
  OpaqueIStreamVtable primary_vtable{};
  OpaqueIStreamVtable fallback_vtable{};
  OpaqueIStream primary{&primary_vtable};
  OpaqueIStream fallback{&fallback_vtable};
  set_slot(primary_vtable, 0x10u, state_slot);
  set_slot(primary_vtable, 0x28u, read_data_slot);
  set_slot(fallback_vtable, 0x10u, state_slot);
  set_slot(fallback_vtable, 0x28u, read_data_slot);

  OpaqueRecordRead record{};
  store_stream(record.bytes, 0x24, &fallback);
  store_stream(record.bytes, 0x48, &primary);
  std::array<std::uint8_t, 4> data{{}};

  record_read_data_008dc820(&record, data.data(), 4u);
  assert(events.size() == 2u);
  assert(events[0] == "state");
  assert(events[1] == "read-data");
  assert(observed_stream == &primary);
  assert(observed_data == data.data());
  assert(observed_size == 4u);
  assert(data == std::array<std::uint8_t, 4>{{1u, 2u, 3u, 4u}});

  events.clear();
  state_result = 0u;
  record_read_data_008dc820(&record, data.data(), 2u);
  assert(events.size() == 2u);
  assert(observed_stream == &fallback);
  assert(observed_size == 2u);
}

void test_record_write_seek_local() {
  reset();
  OpaqueRecordWrite record{};
  initialize_record(record, 2u, 5u, 0u);

  assert(record_write_seek_008dcab0(&record, -1, 0u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 0u);
  assert(record_write_seek_008dcab0(&record, 9, 0u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 5u);
  assert(record_write_seek_008dcab0(&record, 3, 0u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 3u);
  assert(record_write_seek_008dcab0(&record, -3, 1u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 0u);
  assert(record_write_seek_008dcab0(&record, 4, 1u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 4u);
  assert(record_write_seek_008dcab0(&record, -1, 1u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 3u);
  assert(record_write_seek_008dcab0(&record, -3, 2u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 2u);
  assert(record_write_seek_008dcab0(&record, -6, 2u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 0u);
  assert(record_write_seek_008dcab0(&record, 3, 2u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 3u);
  assert(record_write_seek_008dcab0(&record, 9, 2u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 5u);
  assert(record_write_seek_008dcab0(&record, 100, 7u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 5u);
}

void test_record_write_seek_delegates() {
  reset();
  OpaqueRecordWrite record{};
  initialize_record(record, 2u, 5u, 1u);
  OpaqueIStreamVtable vtable{};
  set_slot(vtable, 0x28u, memory_seek_slot);
  store<std::uint32_t>(
      record.bytes, 0x2c,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&vtable)));
  memory_seek_result = 0u;

  assert(!record_write_seek_008dcab0(&record, -2, 2u));
  assert(events.size() == 2u);
  assert(events[0] == "prepare");
  assert(events[1] == "memory-seek");
  assert(observed_stream ==
         reinterpret_cast<OpaqueIStream*>(record.bytes + 0x2c));
  assert(observed_amount == -2);
  assert(observed_operation == 2u);
  assert(load<std::uint32_t>(record.bytes, 0x60) == 2u);
}

void test_record_write_read_local() {
  reset();
  OpaqueRecordWrite record{};
  initialize_record(record, 2u, 5u, 0u);
  std::array<std::uint8_t, 8> data{{}};

  assert(record_write_read_008dcb70(&record, 3u, data.data()) == 3);
  assert((data[0] == 3u && data[1] == 4u && data[2] == 5u));
  assert(load<std::uint32_t>(record.bytes, 0x60) == 5u);
  assert(events.size() == 2u);
  assert(events[0] == "prepare");
  assert(events[1] == "read-record");

  events.clear();
  assert(record_write_read_008dcb70(&record, 1u, data.data()) == 0);
  assert(events.size() == 1u);
  assert(events[0] == "prepare");

  initialize_record(record, 2u, 5u, 0u);
  read_result = false;
  assert(record_write_read_008dcb70(&record, 2u, data.data()) == 0);
  assert(load<std::uint32_t>(record.bytes, 0x60) == 2u);

  initialize_record(record, 2u, 5u, 0u);
  read_result = true;
  assert(record_write_read_008dcb70(&record, 0u, data.data()) == 0);
  assert(events.size() == 4u);
  assert(load<std::uint32_t>(record.bytes, 0x60) == 2u);

  assert(record_write_read_008dcb70(&record, std::numeric_limits<std::uint32_t>::max(),
                                   data.data()) == 3);
  assert(load<std::uint32_t>(record.bytes, 0x60) == 5u);
}

void test_record_write_read_delegates() {
  reset();
  OpaqueRecordWrite record{};
  initialize_record(record, 2u, 5u, 1u);
  OpaqueIStreamVtable vtable{};
  set_slot(vtable, 0x30u, memory_read_slot);
  store<std::uint32_t>(
      record.bytes, 0x2c,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&vtable)));
  memory_read_result = 7;
  std::array<std::uint8_t, 4> data{{}};

  assert(record_write_read_008dcb70(&record, 4u, data.data()) == 7);
  assert(events.size() == 2u);
  assert(events[0] == "prepare");
  assert(events[1] == "memory-read");
  assert(observed_stream ==
         reinterpret_cast<OpaqueIStream*>(record.bytes + 0x2c));
  assert(observed_size == 4u);
  assert(observed_data == data.data());
  assert(load<std::uint32_t>(record.bytes, 0x60) == 2u);
}

void test_record_write_invalid() {
  reset();
  OpaqueRecordWrite record{};
  assert(!record_write_seek_008dcab0(&record, 1, 0u));
  assert(record_write_read_008dcb70(&record, 1u, nullptr) == -1);
  assert(events.empty());
}

void test_fixed_memory_stream_seek() {
  OpaqueFixedMemoryStream stream{};
  store<std::uint32_t>(stream.bytes, 0x0c, 5u);
  store<std::uint32_t>(stream.bytes, 0x14, 2u);

  assert(fixed_memory_stream_seek_0093b950(&stream, 3, 0u));
  assert(load<std::uint32_t>(stream.bytes, 0x14) == 3u);
  assert(fixed_memory_stream_seek_0093b950(&stream, 2, 1u));
  assert(load<std::uint32_t>(stream.bytes, 0x14) == 5u);
  assert(fixed_memory_stream_seek_0093b950(&stream, 1, 1u) == false);
  assert(load<std::uint32_t>(stream.bytes, 0x14) == 5u);
  assert(fixed_memory_stream_seek_0093b950(&stream, -2, 2u));
  assert(load<std::uint32_t>(stream.bytes, 0x14) == 3u);
  assert(!fixed_memory_stream_seek_0093b950(&stream, 2, 2u));
  assert(load<std::uint32_t>(stream.bytes, 0x14) == 5u);
  assert(fixed_memory_stream_seek_0093b950(&stream, 7u, 7u));
  assert(load<std::uint32_t>(stream.bytes, 0x14) == 5u);
  assert(fixed_memory_stream_seek_0093b950(&stream, -1, 0u) == false);
  assert(load<std::uint32_t>(stream.bytes, 0x14) == 5u);
}

}

int main() {
  test_record_read_dispatch();
  test_record_write_seek_local();
  test_record_write_seek_delegates();
  test_record_write_read_local();
  test_record_write_read_delegates();
  test_record_write_invalid();
  test_fixed_memory_stream_seek();
}
