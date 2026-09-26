#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG resource database wave6 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_resource_database_wave6 {

struct OpaqueDirectoryFiles {
  std::uint8_t prefix[8];
  std::int32_t refcount;
};

struct OpaqueStream {};

struct OpaqueDatabasePackedFile {
  std::uint8_t prefix[0x260];
  OpaqueStream* current_stream;
};

struct OpaqueIndexBucket {
  std::uint8_t prefix[0x0c];
  std::uint32_t data_offset;
  std::uint32_t data_size;
  std::uint8_t reserved[8];
  OpaqueIndexBucket* next;
};

struct OpaquePackedIndex {
  std::uint8_t prefix[0x2c];
  OpaqueIndexBucket** buckets;
  std::uint32_t bucket_count;
};

struct OpaqueTypeEntry {
  std::uint32_t value;
  std::uint32_t tail;
};

struct OpaqueTypeBucket {
  std::uint32_t key;
  OpaqueTypeEntry* values_begin;
  OpaqueTypeEntry* values_end;
  std::uint32_t word_0c;
  std::uint32_t word_10;
  std::uint32_t word_14;
  OpaqueTypeBucket* next;
};

struct OpaqueTypeMap {
  std::uint32_t word_0;
  OpaqueTypeBucket** buckets;
  std::uint32_t bucket_count;
};

struct OpaqueResourceManager {
  std::uint8_t prefix[0x30];
  OpaqueTypeMap type_map;
};

struct OpaqueTypeValueNode {
  void* word_0;
  OpaqueTypeValueNode* word_4;
  std::uint32_t value;
};

struct OpaqueTypeValueList {
  std::uint32_t word_0;
  OpaqueTypeValueNode* head;
};

static_assert(sizeof(void*) == 4,
              "resource database wave6 requires 32-bit pointers");
static_assert(offsetof(OpaqueDirectoryFiles, refcount) == 0x08,
              "directory refcount offset");
static_assert(offsetof(OpaqueDatabasePackedFile, current_stream) == 0x260,
              "packed-file stream offset");
static_assert(offsetof(OpaquePackedIndex, buckets) == 0x2c,
              "packed-index bucket offset");
static_assert(offsetof(OpaquePackedIndex, bucket_count) == 0x30,
              "packed-index bucket count offset");
static_assert(offsetof(OpaqueIndexBucket, data_offset) == 0x0c,
              "index data offset");
static_assert(offsetof(OpaqueIndexBucket, data_size) == 0x10,
              "index data size");
static_assert(offsetof(OpaqueIndexBucket, next) == 0x1c,
              "index bucket link offset");
static_assert(offsetof(OpaqueTypeBucket, next) == 0x18,
              "type bucket link offset");
static_assert(offsetof(OpaqueResourceManager, type_map) == 0x30,
              "resource manager type map offset");
static_assert(offsetof(OpaqueTypeMap, buckets) == 0x04,
              "type map bucket offset");
static_assert(offsetof(OpaqueTypeMap, bucket_count) == 0x08,
              "type map bucket count offset");
static_assert(offsetof(OpaqueTypeValueList, head) == 0x04,
              "type value list head offset");
static_assert(offsetof(OpaqueTypeValueNode, value) == 0x08,
              "type value node payload offset");
static_assert(sizeof(OpaqueDirectoryFiles) == 0x0c, "directory file size");
static_assert(sizeof(OpaqueDatabasePackedFile) == 0x264, "packed-file size");
static_assert(sizeof(OpaqueIndexBucket) == 0x20, "index bucket size");
static_assert(sizeof(OpaquePackedIndex) == 0x34, "packed-index size");
static_assert(sizeof(OpaqueTypeBucket) == 0x1c, "type bucket size");
static_assert(sizeof(OpaqueTypeMap) == 0x0c, "type map size");
static_assert(sizeof(OpaqueTypeValueNode) == 0x0c, "type value node size");
static_assert(sizeof(OpaqueTypeValueList) == 0x08, "type value list size");

using OpaqueTypeValueNodeAllocator = OpaqueTypeValueNode* (*)();

void install_type_value_node_allocator(OpaqueTypeValueNodeAllocator allocator);

#if defined(_MSC_VER)
#define PKG_RESOURCE_DATABASE_THISCALL __thiscall
#else
#define PKG_RESOURCE_DATABASE_THISCALL __attribute__((thiscall))
#endif

std::int32_t PKG_RESOURCE_DATABASE_THISCALL
database_directory_files_get_ref_count_0069d3f0(OpaqueDirectoryFiles* self);

OpaqueStream* PKG_RESOURCE_DATABASE_THISCALL
database_packed_file_get_stream_008d86b0(OpaqueDatabasePackedFile* self);

bool PKG_RESOURCE_DATABASE_THISCALL
packed_index_check_files_in_size_range_008db310(OpaquePackedIndex* self,
                                                const void* file_data_begin,
                                                std::size_t size);

std::uint32_t PKG_RESOURCE_DATABASE_THISCALL
resource_manager_project_type_values_008dff30(OpaqueResourceManager* self,
                                              OpaqueTypeValueList* destination,
                                              std::uint32_t type_id);

#undef PKG_RESOURCE_DATABASE_THISCALL

}
