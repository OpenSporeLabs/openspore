#include <cassert>
#include <cstdint>
#include <deque>
#include <vector>

#include "resource_database_wave6.hpp"

namespace {

using openspore::reconstruction::pkg_resource_database_wave6::
    database_directory_files_get_ref_count_0069d3f0;
using openspore::reconstruction::pkg_resource_database_wave6::
    database_packed_file_get_stream_008d86b0;
using openspore::reconstruction::pkg_resource_database_wave6::
    install_type_value_node_allocator;
using openspore::reconstruction::pkg_resource_database_wave6::
    OpaqueDatabasePackedFile;
using openspore::reconstruction::pkg_resource_database_wave6::
    OpaqueDirectoryFiles;
using openspore::reconstruction::pkg_resource_database_wave6::OpaqueIndexBucket;
using openspore::reconstruction::pkg_resource_database_wave6::OpaquePackedIndex;
using openspore::reconstruction::pkg_resource_database_wave6::
    OpaqueResourceManager;
using openspore::reconstruction::pkg_resource_database_wave6::OpaqueStream;
using openspore::reconstruction::pkg_resource_database_wave6::OpaqueTypeBucket;
using openspore::reconstruction::pkg_resource_database_wave6::OpaqueTypeEntry;
using openspore::reconstruction::pkg_resource_database_wave6::
    OpaqueTypeValueList;
using openspore::reconstruction::pkg_resource_database_wave6::
    OpaqueTypeValueNode;
using openspore::reconstruction::pkg_resource_database_wave6::
    packed_index_check_files_in_size_range_008db310;
using openspore::reconstruction::pkg_resource_database_wave6::
    resource_manager_project_type_values_008dff30;

std::deque<OpaqueTypeValueNode>* g_type_nodes = nullptr;

OpaqueTypeValueNode* allocate_type_value_node() {
  assert(g_type_nodes != nullptr);
  g_type_nodes->emplace_back();
  return &g_type_nodes->back();
}

OpaqueTypeValueList make_destination(OpaqueTypeValueNode* sentinel) {
  OpaqueTypeValueList destination{};
  destination.word_0 = 0x12345678u;
  destination.head = sentinel;
  return destination;
}

std::vector<std::uint32_t> collect_values(
    const OpaqueTypeValueList& destination) {
  std::vector<std::uint32_t> values;
  for (OpaqueTypeValueNode* node = destination.head; node->word_4 != nullptr;
       node = node->word_4) {
    values.push_back(node->value);
  }
  return values;
}

void test_refcount_getter_preserves_value() {
  OpaqueDirectoryFiles directory{};
  directory.refcount = 7;
  assert(database_directory_files_get_ref_count_0069d3f0(&directory) == 7);
  assert(directory.refcount == 7);
}

void test_stream_getter_returns_current_stream() {
  OpaqueStream stream{};
  OpaqueDatabasePackedFile file{};
  file.current_stream = &stream;
  assert(database_packed_file_get_stream_008d86b0(&file) == &stream);
  assert(file.current_stream == &stream);
}

void test_index_range_predicate() {
  OpaqueIndexBucket sentinel{};
  OpaqueIndexBucket first{};
  OpaqueIndexBucket second{};
  first.next = &second;
  second.next = &sentinel;
  std::uint8_t storage[0x300];
  first.data_offset = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(storage + 0x100));
  first.data_size = 0x20;
  second.data_offset = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(storage + 0x200));
  second.data_size = 0x20;
  OpaqueIndexBucket* slots[3] = {nullptr, &first, &sentinel};
  OpaquePackedIndex index{};
  index.buckets = slots;
  index.bucket_count = 2;
  assert(packed_index_check_files_in_size_range_008db310(&index, nullptr, 0));
  assert(packed_index_check_files_in_size_range_008db310(&index, storage + 0x40,
                                                         0x20));
  assert(!packed_index_check_files_in_size_range_008db310(
      &index, storage + 0xf0, 0x20));
  assert(packed_index_check_files_in_size_range_008db310(
      &index, storage + 0x120, 0x20));
  assert(!packed_index_check_files_in_size_range_008db310(
      &index, storage + 0x1f0, 0x20));
}

void test_type_value_projection() {
  OpaqueTypeValueNode value_sentinel{};
  OpaqueTypeBucket type_sentinel{};
  OpaqueTypeValueList destination = make_destination(&value_sentinel);
  OpaqueTypeEntry entries[4] = {{10u, 0u}, {20u, 0u}, {30u, 0u}, {40u, 0u}};
  OpaqueTypeBucket first{};
  OpaqueTypeBucket second{};
  first.key = 1u;
  first.values_begin = entries;
  first.values_end = entries + 2;
  first.next = &second;
  second.key = 7u;
  second.values_begin = entries + 2;
  second.values_end = entries + 4;
  second.next = nullptr;
  OpaqueTypeBucket* slots[3] = {nullptr, &first, &type_sentinel};
  OpaqueResourceManager manager{};
  manager.type_map.buckets = slots;
  manager.type_map.bucket_count = 2;
  g_type_nodes = new std::deque<OpaqueTypeValueNode>();
  install_type_value_node_allocator(allocate_type_value_node);

  assert(resource_manager_project_type_values_008dff30(&manager, &destination,
                                                       0xffffffffu) == 4u);
  assert((collect_values(destination) ==
          std::vector<std::uint32_t>{40u, 30u, 20u, 10u}));
  assert(destination.head != &value_sentinel);

  OpaqueTypeValueNode known_sentinel{};
  OpaqueTypeValueList known_destination = make_destination(&known_sentinel);
  assert(resource_manager_project_type_values_008dff30(
             &manager, &known_destination, 7u) == 2u);
  assert((collect_values(known_destination) ==
          std::vector<std::uint32_t>{40u, 30u}));

  OpaqueTypeValueNode unknown_sentinel{};
  OpaqueTypeValueList unknown_destination = make_destination(&unknown_sentinel);
  assert(resource_manager_project_type_values_008dff30(
             &manager, &unknown_destination, 99u) == 0u);
  assert(unknown_destination.head == &unknown_sentinel);

  install_type_value_node_allocator(nullptr);
  delete g_type_nodes;
  g_type_nodes = nullptr;
}

}

int main() {
  test_refcount_getter_preserves_value();
  test_stream_getter_returns_current_stream();
  test_index_range_predicate();
  test_type_value_projection();
}
