#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "resource_index.hpp"

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6 resource reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::wave6_resources {

struct RecordInfo {
  TargetWord chunk_offset;
  TargetWord compressed_size;
  TargetWord memory_size;
  std::uint16_t flags;
  std::uint8_t is_saved;
  std::uint8_t opaque_0f;
};

struct MemoryStream {
  std::array<std::uint8_t, 0x24> opaque;
};

struct PFRecordRead {
  void* vftable0;
  std::int32_t ref_count;
  TargetWord type;
  ResourceKey name_key;
  void* parent_dbp;
  TargetWord file_access;
  void* stream_vtable;
  std::int32_t field_24;
  std::int32_t field_28;
  MemoryStream internal_buffer;
  RecordInfo dbpf_item;
  TargetWord offset;
  TargetWord size;
  std::uint8_t flags;
  std::array<std::uint8_t, 3> opaque_69_6b;
  std::int32_t stream_ref_count;
};

using ConstructMemoryStream = void (*)(MemoryStream*, TargetWord);
using ResetMemoryStream = TargetWord (*)(MemoryStream*);

struct PFRecordReadServices {
  ConstructMemoryStream construct_memory_stream;
  ResetMemoryStream reset_memory_stream;
};

#if defined(_MSC_VER)
#define WAVE6_PF_RECORD_THISCALL __thiscall
#else
#define WAVE6_PF_RECORD_THISCALL __attribute__((thiscall))
#endif

PFRecordReadServices& pf_record_read_services();
void set_pf_record_read_services(const PFRecordReadServices* services);
PFRecordRead* WAVE6_PF_RECORD_THISCALL pf_record_read_set_position_008dcdc0(
    PFRecordRead* record, RecordInfo* info, ResourceKey* name_key,
    void* parent_dbp);

#undef WAVE6_PF_RECORD_THISCALL

static_assert(sizeof(RecordInfo) == 0x10, "record info extent");
static_assert(offsetof(RecordInfo, flags) == 0x0c, "record flags offset");
static_assert(sizeof(MemoryStream) == 0x24, "memory stream extent");
static_assert(sizeof(PFRecordRead) == 0x70, "PFRecordRead extent");
static_assert(offsetof(PFRecordRead, type) == 0x08, "record type offset");
static_assert(offsetof(PFRecordRead, name_key) == 0x0c,
              "record conceptual key offset");
static_assert(offsetof(PFRecordRead, parent_dbp) == 0x18,
              "record parent DBPF offset");
static_assert(offsetof(PFRecordRead, file_access) == 0x1c,
              "record file access offset");
static_assert(offsetof(PFRecordRead, internal_buffer) == 0x2c,
              "record stream buffer offset");
static_assert(offsetof(PFRecordRead, dbpf_item) == 0x50,
              "record persistence metadata offset");
static_assert(offsetof(PFRecordRead, offset) == 0x60, "record offset field");
static_assert(offsetof(PFRecordRead, size) == 0x64, "record size field");
static_assert(offsetof(PFRecordRead, flags) == 0x68, "record flags field");
static_assert(offsetof(PFRecordRead, stream_ref_count) == 0x6c,
              "record stream refcount field");

}
