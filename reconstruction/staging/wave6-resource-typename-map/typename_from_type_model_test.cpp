#include <array>
#include <cassert>
#include <cstdint>
#include <vector>

#include "typename_from_type.hpp"

namespace {

using namespace openspore::reconstruction::wave6_resource_typename_map;

struct AllocationRecord {
  TargetWord bytes;
  TargetWord name;
  TargetWord line;
  TargetWord flags;
  TargetWord file;
  TargetWord file_line;
};

std::vector<AllocationRecord> allocations;
std::vector<TargetWord> lookup_keys;
std::size_t lookup_calls = 0;
std::array<std::array<TypeNameListNode, 8>, 16> node_pool{};
std::size_t node_pool_used = 0;

TypeNameListNode* trace_allocate_node(TargetWord bytes, TargetWord name,
                                      TargetWord line, TargetWord flags,
                                      TargetWord file, TargetWord file_line) {
  allocations.push_back({bytes, name, line, flags, file, file_line});
  return &node_pool[node_pool_used++][0];
}

// Independent restatement of the shared lookup at 0x00aea1b0, used as a fake
// port so the tests can observe that the query word travels by reference.
void trace_lookup_chunk(TypeChunkMap* map, TypeChunkIterator* out,
                        TargetWord* type_id) {
  ++lookup_calls;
  lookup_keys.push_back(*type_id);
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

void install_traced_services() {
  const TypeNameMapServices services{trace_allocate_node, trace_lookup_chunk};
  set_type_name_map_services(&services);
}

void reset_trace() {
  allocations.clear();
  lookup_keys.clear();
  lookup_calls = 0;
  node_pool_used = 0;
}

TypeChunkNode* end_sentinel() {
  return reinterpret_cast<TypeChunkNode*>(0xffffffffu);
}

void test_specific_type_appends_in_source_order() {
  reset_trace();
  install_traced_services();

  TypenameChunkEntry entries[3]{};
  entries[0] = {0x1000u, 0xaaau};
  entries[1] = {0x2000u, 0xbbbu};
  entries[2] = {0x3000u, 0xcccu};
  TypeChunkNode node{};
  node.type_id = 4;  // 4 % 2 == 0, so the key lands in bucket 0
  node.chunk_first = entries;
  node.chunk_last = entries + 2;  // the third entry is out of range
  node.next = nullptr;

  TypeChunkNode* buckets[3]{};
  buckets[0] = &node;
  buckets[1] = nullptr;
  buckets[2] = end_sentinel();

  ResourceManagerCarrier manager{};
  manager.type_chunks.buckets = buckets;
  manager.type_chunks.bucket_count = 2;

  TypeNameListNode end{};
  end.next = &end;
  end.prev = &end;

  const std::uint32_t appended =
      get_typename_from_type_008dff30(&manager, &end, 4);
  assert(appended == 2);
  assert(lookup_calls == 1);
  assert((lookup_keys == std::vector<TargetWord>{4}));
  assert(allocations.size() == 2);
  for (const AllocationRecord& record : allocations) {
    assert(record.bytes == 0x0cu);
    assert(record.name == 0x013f2150u);
    assert(record.line == 0);
    assert(record.flags == 0);
    assert(record.file == 0x013ebb38u);
    assert(record.file_line == 0xd1u);
  }
  TypeNameListNode* first = end.next;
  TypeNameListNode* second = first->next;
  assert(first != &end);
  assert(second != &end);
  assert(first->value == 0x1000u);
  assert(second->value == 0x2000u);
  assert(second->next == &end);
  assert(first->prev == &end);
  assert(second->prev == first);
  assert(end.prev == second);
  assert(node_pool_used == 2);

  // The position iterator is never advanced, so a second call in front of the
  // first node prepends instead of appending.
  const std::uint32_t again =
      get_typename_from_type_008dff30(&manager, first, 4);
  assert(again == 2);
  assert(lookup_calls == 2);
  assert(end.next != first);
  assert(end.next->value == 0x1000u);
  assert(end.next->next->value == 0x2000u);
  assert(end.next->next->next == first);
  assert(first->prev == end.next->next);
  assert(end.next->prev == &end);
  assert(end.next->next->next->next == second);
  assert(second->value == 0x2000u);
  set_type_name_map_services(nullptr);
}

void test_miss_and_empty_chunk_return_zero() {
  reset_trace();
  install_traced_services();

  TypenameChunkEntry entries[1]{};
  entries[0] = {0x4444u, 0x5555u};
  TypeChunkNode node{};
  node.type_id = 9;
  node.chunk_first = entries + 1;  // empty half-open range
  node.chunk_last = entries + 1;
  node.next = nullptr;

  TypeChunkNode* buckets[2]{};
  buckets[0] = &node;
  buckets[1] = end_sentinel();

  ResourceManagerCarrier manager{};
  manager.type_chunks.buckets = buckets;
  manager.type_chunks.bucket_count = 1;

  TypeNameListNode end{};
  end.next = &end;
  end.prev = &end;

  // Present key with an empty range: the body returns before allocating.
  assert(get_typename_from_type_008dff30(&manager, &end, 9) == 0);
  assert(allocations.empty());

  // Absent key: the lookup reports the sentinel slot and the body returns.
  assert(get_typename_from_type_008dff30(&manager, &end, 11) == 0);
  assert(allocations.empty());
  assert(lookup_calls == 2);
  assert((lookup_keys == std::vector<TargetWord>{9, 11}));
  assert(end.next == &end);
  assert(end.prev == &end);
  set_type_name_map_services(nullptr);
}

void test_all_types_scan_skips_null_buckets_and_empty_chains() {
  reset_trace();
  install_traced_services();

  TypenameChunkEntry head[2]{};
  head[0] = {0xa0a0u, 0u};
  head[1] = {0xb0b0u, 0u};
  TypenameChunkEntry middle_head[1]{};
  middle_head[0] = {0u, 0u};
  TypenameChunkEntry last_two[2]{};
  last_two[0] = {0xd0d0u, 0u};
  last_two[1] = {0xe0e0u, 0u};

  TypeChunkNode end_node{};
  TypeChunkNode first{};
  TypeChunkNode middle{};
  TypeChunkNode last_bucket{};
  first.type_id = 1;
  first.chunk_first = head;
  first.chunk_last = head + 2;
  first.next = &middle;
  middle.type_id = 1;
  middle.chunk_first = middle_head;  // empty range
  middle.chunk_last = middle_head;
  middle.next = nullptr;  // chain end: resume the bucket array
  last_bucket.type_id = 3;
  last_bucket.chunk_first = last_two;
  last_bucket.chunk_last = last_two + 2;
  last_bucket.next = &end_node;
  end_node.type_id = 0;
  end_node.next = nullptr;

  TypeChunkNode* buckets[4]{};
  buckets[0] = nullptr;  // skipped by the probes at 0x008dff58 / 0x008e0006
  buckets[1] = &first;
  buckets[2] = &last_bucket;
  buckets[3] = &end_node;  // sentinel slot at index bucket_count

  ResourceManagerCarrier manager{};
  manager.type_chunks.buckets = buckets;
  manager.type_chunks.bucket_count = 3;

  TypeNameListNode end{};
  end.next = &end;
  end.prev = &end;

  const std::uint32_t appended =
      get_typename_from_type_008dff30(&manager, &end, kAllTypesQuery);
  assert(appended == 4);
  assert(lookup_calls == 0);  // the all-types branch never calls the map port

  std::vector<TargetWord> collected;
  for (TypeNameListNode* node = end.next; node != &end; node = node->next) {
    collected.push_back(node->value);
  }
  assert((collected == std::vector<TargetWord>{0xa0a0u, 0xb0b0u, 0xd0d0u,
                                               0xe0e0u}));
  assert(end.prev == end.next->next->next->next);
  assert(end.prev->next == &end);
  assert(allocations.size() == 4);
  set_type_name_map_services(nullptr);
}

void test_default_services_need_no_overrides() {
  reset_trace();
  set_type_name_map_services(nullptr);

  TypenameChunkEntry entries[1]{};
  entries[0] = {0x7777u, 0u};
  TypeChunkNode node{};
  node.type_id = 3;
  node.chunk_first = entries;
  node.chunk_last = entries + 1;
  node.next = nullptr;
  TypeChunkNode* buckets[2]{};
  buckets[0] = &node;
  buckets[1] = end_sentinel();

  ResourceManagerCarrier manager{};
  manager.type_chunks.buckets = buckets;
  manager.type_chunks.bucket_count = 1;
  TypeNameListNode end{};
  end.next = &end;
  end.prev = &end;

  assert(get_typename_from_type_008dff30(&manager, &end, 3) == 1);
  assert(end.next != &end);
  assert(end.next->value == 0x7777u);
  assert(end.next->next == &end);
  assert(end.next->prev == &end);
  assert(end.prev == end.next);
}

}

int main() {
  test_specific_type_appends_in_source_order();
  test_miss_and_empty_chunk_return_zero();
  test_all_types_scan_skips_null_buckets_and_empty_chains();
  test_default_services_need_no_overrides();
}
