#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-record-io-wave6 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_RECORD_IO_THISCALL __thiscall
#else
#define PKG_RECORD_IO_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_record_io_wave6 {

struct OpaqueIStreamVtable {
  std::uint32_t slots[16];
};

struct OpaqueIStream {
  OpaqueIStreamVtable* vtable;
};

struct OpaqueRecordRead {
  std::uint8_t bytes[0x70];
};

struct OpaqueRecordWrite {
  std::uint8_t bytes[0x27c];
};

struct OpaqueFixedMemoryStream {
  std::uint8_t bytes[0x18];
};

struct OpaqueMemoryStream {
  std::uint8_t bytes[0x24];
};

struct RecordWritePorts {
  void (*prepare)(OpaqueRecordWrite*);
  bool (*read)(OpaqueRecordWrite*, void*, std::uint32_t, std::uint32_t);
};

static_assert(sizeof(void*) == 4, "pkg-record-io-wave6 pointers are 32-bit");
static_assert(sizeof(OpaqueRecordRead) == 0x70,
              "PFRecordRead opaque size");
static_assert(sizeof(OpaqueRecordWrite) == 0x27c,
              "PFRecordWrite opaque size");
static_assert(sizeof(OpaqueFixedMemoryStream) == 0x18,
              "FixedMemoryStream opaque size");
static_assert(sizeof(OpaqueMemoryStream) == 0x24,
              "MemoryStream opaque size");

void PKG_RECORD_IO_THISCALL record_read_data_008dc820(
    OpaqueRecordRead* record, void* data, std::uint32_t size);
bool PKG_RECORD_IO_THISCALL record_write_seek_008dcab0(
    OpaqueRecordWrite* record, std::int32_t amount, std::uint32_t operation);
std::int32_t PKG_RECORD_IO_THISCALL record_write_read_008dcb70(
    OpaqueRecordWrite* record, std::uint32_t size, void* data);
bool PKG_RECORD_IO_THISCALL fixed_memory_stream_seek_0093b950(
    OpaqueFixedMemoryStream* stream, std::int32_t amount,
    std::uint32_t operation);

void record_io_set_record_write_ports(RecordWritePorts ports);

}

#undef PKG_RECORD_IO_THISCALL
