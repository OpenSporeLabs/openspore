#include <array>
#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <vector>

#include "dbpF_integrity.hpp"
#include "pf_record_read.hpp"
#include "property_list_access.hpp"
#include "resource_index.hpp"

namespace {

using namespace openspore::reconstruction::wave6_resources;

enum class IndexOperation {
  Allocate,
  Zero,
  Release,
};

std::vector<IndexOperation> index_trace;
std::vector<std::array<TargetWord, 4>> index_allocations;
std::vector<std::array<TargetWord, 3>> index_releases;
std::array<std::array<ResourceNode*, 4>, 2> allocated_index_storage{};
std::size_t index_allocation_count = 0;

ResourceNode** trace_allocate(IndexAllocator*, TargetWord bytes, TargetWord zero,
                             TargetWord tag) {
  index_trace.push_back(IndexOperation::Allocate);
  index_allocations.push_back({bytes, zero, tag, 0});
  ResourceNode** result =
      allocated_index_storage[index_allocation_count++].data();
  return result;
}

void trace_zero_fill(ResourceNode** buckets, TargetWord value, TargetWord bytes) {
  index_trace.push_back(IndexOperation::Zero);
  for (TargetWord offset = 0; offset < bytes / sizeof(TargetWord); ++offset) {
    buckets[offset] = reinterpret_cast<ResourceNode*>(value);
  }
}

TargetWord trace_release(IndexAllocator*, ResourceNode** buckets,
                         TargetWord bytes) {
  index_trace.push_back(IndexOperation::Release);
  index_releases.push_back({reinterpret_cast<TargetWord>(buckets), bytes, 0});
  return 0x55;
}

void reset_index_trace() {
  index_trace.clear();
  index_allocations.clear();
  index_releases.clear();
  index_allocation_count = 0;
  for (auto& storage : allocated_index_storage) {
    storage.fill(nullptr);
  }
}

void test_index_rehash_and_sentinel() {
  reset_index_trace();
  IndexOwner owner{};
  ResourceNode** original_buckets = new ResourceNode*[3]{};
  owner.source_buckets = original_buckets;
  owner.source_bucket_count = 3;
  owner.allocator = reinterpret_cast<IndexAllocator*>(0x1000);
  owner.allocation_tag = 0xabc12345u;
  ResourceNode nodes[3]{};
  nodes[0] = {5, owner.source_buckets[1]};
  nodes[1] = {3, owner.source_buckets[2]};
  nodes[2] = {7, nullptr};
  owner.source_buckets[0] = &nodes[0];
  owner.source_buckets[1] = &nodes[1];
  owner.source_buckets[2] = &nodes[2];
  const IndexServices services{trace_allocate, trace_zero_fill, trace_release};
  set_index_services(&services);

  const TargetWord result =
      resource_manager_initialize_008de530(&owner, 2);

  assert(result == 0x55u);
  assert(owner.source_bucket_count == 2);
  assert(owner.source_buckets[2] == reinterpret_cast<ResourceNode*>(UINT32_MAX));
  assert(owner.source_buckets[0] == nullptr);
  assert(owner.source_buckets[1] == &nodes[2]);
  assert(nodes[2].next == &nodes[1]);
  assert(nodes[1].next == &nodes[0]);
  assert(nodes[0].next == nullptr);
  assert(index_trace ==
         std::vector<IndexOperation>({IndexOperation::Allocate,
                                      IndexOperation::Zero,
                                      IndexOperation::Release}));
  assert(index_allocations.size() == 1);
  assert(index_allocations[0][0] == 12);
  assert(index_allocations[0][1] == 0);
  assert(index_allocations[0][2] == 0xabc12345u);
  assert(index_releases.size() == 1);
  assert(index_releases[0][1] == 16);
  set_index_services(nullptr);
  delete[] original_buckets;
}

void test_index_small_old_count_skips_release() {
  reset_index_trace();
  IndexOwner owner{};
  ResourceNode** original_buckets = new ResourceNode*[1]{};
  owner.source_buckets = original_buckets;
  owner.source_bucket_count = 1;
  owner.allocator = reinterpret_cast<IndexAllocator*>(0x1000);
  const IndexServices services{trace_allocate, trace_zero_fill, trace_release};
  set_index_services(&services);

  assert(resource_manager_initialize_008de530(&owner, 1) == 1);
  assert(owner.source_bucket_count == 1);
  assert(owner.source_buckets[1] == reinterpret_cast<ResourceNode*>(UINT32_MAX));
  assert(index_trace ==
         std::vector<IndexOperation>({IndexOperation::Allocate,
                                      IndexOperation::Zero}));
  set_index_services(nullptr);
  delete[] original_buckets;
}

Property* parent_result = nullptr;
TargetWord parent_property_id = 0;
std::size_t parent_calls = 0;

bool parent_lookup(PropertyList*, TargetWord property_id, Property** result) {
  ++parent_calls;
  parent_property_id = property_id;
  *result = parent_result;
  return true;
}

void test_property_list_lookup_and_parent_fallback() {
  PropertyMapEntry entries[3]{};
  entries[0].key = 10;
  entries[1].key = 20;
  entries[2].key = 30;
  PropertyList list{};
  list.name_key = {1, 2, 3};
  list.properties.entries_begin = entries;
  list.properties.entries_end = entries + 3;
  list.properties.lookup_mode = 0x7d;

  Property* result = reinterpret_cast<Property*>(0xdeadbeef);
  assert(property_list_get_property_006a2530(&list, 20, &result));
  assert(result == &entries[1].property);
  assert(list.name_key.instance_id == 1);
  assert(list.properties.lookup_mode == 0x7d);

  result = reinterpret_cast<Property*>(0xdeadbeef);
  assert(!property_list_get_property_006a2530(&list, 15, &result));
  assert(result == reinterpret_cast<Property*>(0xdeadbeef));

  Property parent_property{};
  parent_result = &parent_property;
  parent_calls = 0;
  PropertyList parent{};
  PropertyListVtable parent_vtable{};
  parent_vtable.get_property_at_24 = parent_lookup;
  parent.vftable = &parent_vtable;
  list.parent = &parent;
  result = nullptr;
  assert(property_list_get_property_006a2530(&list, 15, &result));
  assert(result == &parent_property);
  assert(parent_calls == 1);
  assert(parent_property_id == 15);
}

std::vector<TargetWord> pf_construct_tags;
std::vector<TargetWord> pf_reset_calls;

void trace_construct(MemoryStream*, TargetWord tag) {
  pf_construct_tags.push_back(tag);
}

TargetWord trace_reset(MemoryStream*) {
  pf_reset_calls.push_back(1);
  return 0;
}

void test_pf_record_position_branches() {
  const PFRecordReadServices services{trace_construct, trace_reset};
  set_pf_record_read_services(&services);
  pf_construct_tags.clear();
  pf_reset_calls.clear();

  ResourceKey key{11, 22, 33};
  RecordInfo info{0x100, 0x300, 0x700, 0, 0, 0};
  PFRecordRead record{};
  int parent = 0;
  PFRecordRead* result = pf_record_read_set_position_008dcdc0(
      &record, &info, &key, &parent);
  assert(result == &record);
  assert(record.type == 0x12e4a891u);
  assert(record.name_key.instance_id == 11);
  assert(record.name_key.type_id == 22);
  assert(record.name_key.group_id == 33);
  assert(record.parent_dbp == &parent);
  assert(record.file_access == 1);
  assert(record.offset == 0);
  assert(record.size == 0x300);
  assert(record.flags == 0);
  assert(record.stream_ref_count == 1);
  assert(pf_construct_tags == std::vector<TargetWord>({0x140a30c}));
  assert(pf_reset_calls.size() == 1);

  info.flags = 1;
  info.compressed_size = 0x100;
  info.memory_size = 0x800;
  result = pf_record_read_set_position_008dcdc0(&record, &info, &key, &parent);
  assert(result == &record);
  assert(record.size == 0x800);
  assert(record.flags == 1);

  info.flags = 0;
  info.compressed_size = 0x200;
  result = pf_record_read_set_position_008dcdc0(&record, &info, &key, &parent);
  assert(result == &record);
  assert(record.size == 0x200);
  assert(record.flags == 1);
  set_pf_record_read_services(nullptr);
}

enum class IntegrityOperation {
  Open,
  Validate,
  Repair,
  Close,
};

std::vector<IntegrityOperation> integrity_trace;
std::array<TargetWord, 4> open_arguments{};
std::array<TargetWord, 3> close_arguments{};
std::size_t validate_calls = 0;
std::size_t repair_calls = 0;
bool validate_result = false;
bool repair_result = false;
int zone_marker = 0;

void* trace_open(IndexObjectAllocator*, TargetWord first, TargetWord second,
                 TargetWord third) {
  integrity_trace.push_back(IntegrityOperation::Open);
  open_arguments = {first, second, third, 0};
  return &zone_marker;
}

void trace_close(IndexObjectAllocator*, void* object, TargetWord argument) {
  integrity_trace.push_back(IntegrityOperation::Close);
  close_arguments = {reinterpret_cast<TargetWord>(object), argument, 0};
}

bool trace_validate(ObservedDatabasePackedFile*, void*, void*, void*) {
  integrity_trace.push_back(IntegrityOperation::Validate);
  ++validate_calls;
  return validate_result;
}

bool trace_repair(ObservedDatabasePackedFile*, void*, void*, void*, void*) {
  integrity_trace.push_back(IntegrityOperation::Repair);
  ++repair_calls;
  return repair_result;
}

void test_dbpF_integrity_order() {
  integrity_trace.clear();
  open_arguments = {};
  close_arguments = {};
  validate_calls = 0;
  repair_calls = 0;
  validate_result = false;
  repair_result = false;
  IndexObjectAllocatorVtable vtable{};
  vtable.open_at_08 = trace_open;
  vtable.close_at_0c = trace_close;
  IndexObjectAllocator allocator{&vtable};
  ObservedDatabasePackedFile file{};
  file.allocator = &allocator;
  const DBPFIntegrityServices services{trace_validate, trace_repair};
  set_dBPF_integrity_services(&services);
  int record = 0;
  int arg3 = 0;
  int arg4 = 0;
  int arg5 = 0;

  assert(!database_packed_file_verify_index_008d9320(
      &file, nullptr, nullptr, &arg3, &arg4, &arg5));
  assert(integrity_trace.empty());

  assert(!database_packed_file_verify_index_008d9320(
      &file, nullptr, &record, &arg3, &arg4, &arg5));
  assert(integrity_trace ==
         std::vector<IntegrityOperation>({IntegrityOperation::Open,
                                          IntegrityOperation::Close}));
  assert(close_arguments[0] == reinterpret_cast<TargetWord>(&zone_marker));
  assert(close_arguments[1] == 0);

  integrity_trace.clear();
  validate_result = true;
  repair_result = true;
  assert(database_packed_file_verify_index_008d9320(
      &file, nullptr, &record, &arg3, &arg4, &arg5));
  assert(integrity_trace ==
         std::vector<IntegrityOperation>({IntegrityOperation::Open,
                                          IntegrityOperation::Validate,
                                          IntegrityOperation::Repair,
                                          IntegrityOperation::Close}));
  assert(validate_calls == 2);
  assert(repair_calls == 1);
  assert(open_arguments[0] == 0);
  assert(open_arguments[1] == 0x140a0fc);
  assert(open_arguments[2] == reinterpret_cast<TargetWord>(&arg3));
  set_dBPF_integrity_services(nullptr);
}

}

int main() {
  test_index_rehash_and_sentinel();
  test_index_small_old_count_skips_release();
  test_property_list_lookup_and_parent_fallback();
  test_pf_record_position_branches();
  test_dbpF_integrity_order();
}
