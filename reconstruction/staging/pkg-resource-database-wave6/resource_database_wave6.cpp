#include "resource_database_wave6.hpp"

namespace {

using openspore::reconstruction::pkg_resource_database_wave6::OpaqueTypeBucket;
using openspore::reconstruction::pkg_resource_database_wave6::OpaqueTypeEntry;
using openspore::reconstruction::pkg_resource_database_wave6::OpaqueTypeMap;
using openspore::reconstruction::pkg_resource_database_wave6::
    OpaqueTypeValueList;
using openspore::reconstruction::pkg_resource_database_wave6::
    OpaqueTypeValueNode;
using openspore::reconstruction::pkg_resource_database_wave6::
    OpaqueTypeValueNodeAllocator;

OpaqueTypeValueNodeAllocator g_type_value_allocator = nullptr;

struct TypeBucketLookup {
  OpaqueTypeBucket* bucket;
  OpaqueTypeBucket** slot;
};

TypeBucketLookup find_type_bucket(OpaqueTypeMap* map, std::uint32_t key) {
  OpaqueTypeBucket** slots = map->buckets;
  OpaqueTypeBucket** slot = &slots[key % map->bucket_count];
  OpaqueTypeBucket* bucket = *slot;
  while (bucket != nullptr) {
    if (bucket->key == key) {
      return {bucket, slot};
    }
    bucket = bucket->next;
  }
  slot = &slots[map->bucket_count];
  return {*slot, slot};
}

void append_type_value(OpaqueTypeValueList* destination, std::uint32_t value) {
  OpaqueTypeValueNode* node = g_type_value_allocator();
  node->value = value;
  node->word_0 = destination;
  OpaqueTypeValueNode* old_head = destination->head;
  node->word_4 = old_head;
  old_head->word_0 = node;
  destination->head = node;
}

}

namespace openspore::reconstruction::pkg_resource_database_wave6 {

void install_type_value_node_allocator(OpaqueTypeValueNodeAllocator allocator) {
  g_type_value_allocator = allocator;
}

#if defined(_MSC_VER)
#define PKG_RESOURCE_DATABASE_THISCALL __thiscall
#else
#define PKG_RESOURCE_DATABASE_THISCALL __attribute__((thiscall))
#endif

std::int32_t PKG_RESOURCE_DATABASE_THISCALL
database_directory_files_get_ref_count_0069d3f0(OpaqueDirectoryFiles* self) {
  std::int32_t observed = 0;
  __asm__ volatile("lock xaddl %0, %1"
                   : "+r"(observed), "+m"(self->refcount)
                   :
                   : "memory");
  return observed;
}

OpaqueStream* PKG_RESOURCE_DATABASE_THISCALL
database_packed_file_get_stream_008d86b0(OpaqueDatabasePackedFile* self) {
  return self->current_stream;
}

bool PKG_RESOURCE_DATABASE_THISCALL
packed_index_check_files_in_size_range_008db310(OpaquePackedIndex* self,
                                                const void* file_data_begin,
                                                std::size_t size) {
  if (size == 0) {
    return true;
  }

  OpaqueIndexBucket** slots = self->buckets;
  OpaqueIndexBucket** slot = slots;
  OpaqueIndexBucket* bucket = *slot;
  if (bucket == nullptr) {
    do {
      ++slot;
      bucket = *slot;
    } while (bucket == nullptr);
  }

  const std::uint32_t begin = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(file_data_begin));
  const std::uint32_t end = begin + static_cast<std::uint32_t>(size);
  OpaqueIndexBucket* sentinel = slots[self->bucket_count];
  while (bucket != sentinel) {
    const std::uint32_t data_size = bucket->data_size;
    if (data_size != 0) {
      const std::uint32_t data_end = bucket->data_offset + data_size;
      if (bucket->data_offset < end && begin < data_end) {
        return false;
      }
    }
    bucket = bucket->next;
    if (bucket == nullptr) {
      do {
        ++slot;
        bucket = *slot;
      } while (bucket == nullptr);
    }
  }
  return true;
}

std::uint32_t PKG_RESOURCE_DATABASE_THISCALL
resource_manager_project_type_values_008dff30(OpaqueResourceManager* self,
                                              OpaqueTypeValueList* destination,
                                              std::uint32_t type_id) {
  std::uint32_t result = 0;
  OpaqueTypeMap* map = &self->type_map;
  if (type_id == 0xffffffffu) {
    OpaqueTypeBucket** slots = map->buckets;
    OpaqueTypeBucket** slot = slots;
    OpaqueTypeBucket* bucket = *slot;
    if (bucket == nullptr) {
      do {
        ++slot;
        bucket = *slot;
      } while (bucket == nullptr);
    }
    OpaqueTypeBucket* sentinel = slots[map->bucket_count];
    while (bucket != sentinel) {
      OpaqueTypeEntry* entry = bucket->values_begin;
      while (entry != bucket->values_end) {
        ++result;
        append_type_value(destination, entry->value);
        entry += 1;
      }
      bucket = bucket->next;
      if (bucket == nullptr) {
        do {
          ++slot;
          bucket = *slot;
        } while (bucket == nullptr);
      }
    }
    return result;
  }

  const TypeBucketLookup lookup = find_type_bucket(map, type_id);
  OpaqueTypeEntry* entry = lookup.bucket->values_begin;
  while (entry != lookup.bucket->values_end) {
    ++result;
    append_type_value(destination, entry->value);
    entry += 1;
  }
  return result;
}

#undef PKG_RESOURCE_DATABASE_THISCALL

}
