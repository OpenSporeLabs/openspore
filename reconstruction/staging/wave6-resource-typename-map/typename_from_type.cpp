#include "typename_from_type.hpp"

#include <new>

namespace openspore::reconstruction::wave6_resource_typename_map {

#if defined(_MSC_VER)
#define WAVE6_TYPENAME_THISCALL __thiscall
#else
#define WAVE6_TYPENAME_THISCALL __attribute__((thiscall))
#endif

namespace {

TypeNameListNode* default_allocate_node(TargetWord bytes, TargetWord, TargetWord,
                                        TargetWord, TargetWord, TargetWord) {
  return static_cast<TypeNameListNode*>(::operator new(bytes));
}

// Faithful to the shared lookup at 0x00aea1b0: key % bucket_count selects the
// slot, the chain is walked through +0x18, and a miss reports the sentinel
// stored at buckets[bucket_count].
void default_lookup_chunk(TypeChunkMap* map, TypeChunkIterator* out,
                          TargetWord* type_id) {
  const TargetWord bucket = *type_id % map->bucket_count;
  out->slot = &map->buckets[bucket];
  TypeChunkNode* node = *out->slot;
  while (node != nullptr) {
    if (node->type_id == *type_id) {
      out->node = node;
      return;
    }
    node = node->next;
  }
  out->slot = &map->buckets[map->bucket_count];
  out->node = *out->slot;
}

const TypeNameMapServices kDefaultServices{default_allocate_node,
                                           default_lookup_chunk};

// The duplicated append block shared by both branches (0x008dffd1..0x008dffe1
// and 0x008e0089..0x008e0099). It is a doubly linked insert before the position
// iterator: the new node links forward to the position itself, links back to
// position->prev, then position->prev is relinked to the new node on both
// sides. The position is never advanced, so a list sentinel keeps the source
// order and a mid-list position prepends.
std::uint32_t append_chunk_entries(const TypeNameMapServices& services,
                                   TypeNameListNode* position,
                                   TypenameChunkEntry* first,
                                   TypenameChunkEntry* last) {
  std::uint32_t appended = 0;
  for (TypenameChunkEntry* entry = first; entry != last; ++entry) {
    TypeNameListNode* node = services.allocate_node(
        kListNodeBytes, kAllocatorName, 0, 0, kAllocatorFile, kAllocatorLine);
    node->value = entry->value;
    node->next = position;
    node->prev = position->prev;
    position->prev->next = node;
    position->prev = node;
    ++appended;
  }
  return appended;
}

}

TypeNameMapServices& type_name_map_services() {
  static TypeNameMapServices services = kDefaultServices;
  return services;
}

void set_type_name_map_services(const TypeNameMapServices* services) {
  type_name_map_services() = services == nullptr ? kDefaultServices : *services;
}

std::uint32_t WAVE6_TYPENAME_THISCALL get_typename_from_type_008dff30(
    ResourceManagerCarrier* manager, TypeNameListNode* position,
    TargetWord type_id) {
  TypeNameMapServices& services = type_name_map_services();
  TypeChunkMap& map = manager->type_chunks;

  std::uint32_t appended = 0;

  if (type_id == kAllTypesQuery) {
    // 0x008dff44..0x008dff7a: the scan starts at buckets[0] and every null
    // slot is skipped without a bound check, which is safe only because the
    // sentinel slot at buckets[bucket_count] is never null.
    TypeChunkNode** cursor = map.buckets;
    TypeChunkNode* node = *cursor;
    while (node == nullptr) {
      ++cursor;
      node = *cursor;
    }
    TypeChunkNode* const end = map.buckets[map.bucket_count];
    while (node != end) {
      appended += append_chunk_entries(services, position, node->chunk_first,
                                       node->chunk_last);
      node = node->next;
      if (node == nullptr) {
        // 0x008dfff9..0x008e000a: chain exhausted, resume the bucket array.
        ++cursor;
        while (*cursor == nullptr) {
          ++cursor;
        }
        node = *cursor;
      }
    }
    return appended;
  }

  // 0x008e0022..0x008e0031: thiscall lookup on the receiver map with the
  // address of the type argument; the query word is passed by reference.
  TypeChunkIterator iterator{};
  services.lookup_chunk(&map, &iterator, &type_id);
  if (iterator.node == map.buckets[map.bucket_count]) {
    return appended;
  }
  TypenameChunkEntry* const first = iterator.node->chunk_first;
  TypenameChunkEntry* const last = iterator.node->chunk_last;
  if (first == last) {
    return appended;
  }
  appended += append_chunk_entries(services, position, first, last);
  return appended;
}

#undef WAVE6_TYPENAME_THISCALL

}
