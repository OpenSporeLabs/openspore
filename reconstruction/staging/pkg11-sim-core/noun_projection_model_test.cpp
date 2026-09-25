#include <cassert>
#include <cstdint>
#include <vector>

#include "noun_projection.hpp"

namespace openspore::reconstruction::pkg11_sim_core {

namespace model {

enum class EventKind : std::uint8_t {
  create,
  insert,
  clear,
  filter,
  add,
};

struct Event {
  EventKind kind;
  NounProjectionVector* value;
  NounListNode* node;
  TargetWord id;

  bool operator==(const Event& other) const {
    return kind == other.kind && value == other.value && node == other.node &&
           id == other.id;
  }
};

std::vector<Event> events;
std::vector<std::uint8_t> filter_results;
std::size_t filter_index = 0;
NounProjectionVector* created = nullptr;
NounMapEntry inserted{};

void reset() {
  events.clear();
  filter_results.clear();
  filter_index = 0;
  created = nullptr;
  inserted = {};
}

}

#if defined(_MSC_VER)
#define PKG11_TEST_THISCALL __thiscall
#else
#define PKG11_TEST_THISCALL __attribute__((thiscall))
#endif

NounMapInsertResult* PKG11_TEST_THISCALL
noun_projection_insert_00ba8420(OrderedMap* map, NounMapInsertResult* output,
                                const NounMapPair* pair, void* context) {
  assert(context == nullptr);
  model::events.push_back(
      model::Event{model::EventKind::insert, pair->value, nullptr, pair->key});
  model::inserted.entry.base.left = nullptr;
  model::inserted.entry.base.right = nullptr;
  model::inserted.entry.base.parent = nullptr;
  model::inserted.entry.key = pair->key;
  model::inserted.value = pair->value;
  map->anchor.parent = &model::inserted.entry.base;
  ++map->size;
  output->entry = &model::inserted;
  output->inserted = 1;
  return output;
}

#undef PKG11_TEST_THISCALL

namespace {

NounProjectionVector* create_callback() {
  model::events.push_back(
      model::Event{model::EventKind::create, model::created, nullptr, 0});
  return model::created;
}

void clear_callback(NounProjectionVector* value) {
  model::events.push_back(
      model::Event{model::EventKind::clear, value, nullptr, 0});
}

std::uint8_t filter_callback(NounListNode* node, TargetWord id) {
  model::events.push_back(
      model::Event{model::EventKind::filter, nullptr, node, id});
  const std::uint8_t result = model::filter_index < model::filter_results.size()
                                  ? model::filter_results[model::filter_index]
                                  : 0;
  ++model::filter_index;
  return result;
}

void add_callback(NounProjectionVector* value, NounListNode* node) {
  model::events.push_back(model::Event{model::EventKind::add, value, node, 0});
}

void initialize_empty_list(NounProjection& projection) {
  projection.list_sentinel.next_link = &projection.list_sentinel.next_link;
}

void add_list_node(NounProjection& projection, NounListNode& node) {
  node.next_link = projection.list_sentinel.next_link;
  projection.list_sentinel.next_link = &node.next_link;
}

NounMapEntry* install_hit(NounProjection& projection, TargetWord key,
                          NounProjectionVector& value, NounMapEntry& entry) {
  entry.entry.base.left = nullptr;
  entry.entry.base.right = nullptr;
  entry.entry.base.parent = nullptr;
  entry.entry.key = key;
  entry.value = &value;
  projection.noun_map.anchor.parent = &entry.entry.base;
  projection.noun_map.size = 1;
  return &entry;
}

void test_clean_borrowed_hit() {
  NounProjection projection{};
  NounProjectionVector value{};
  NounMapEntry entry{};
  initialize_empty_list(projection);
  NounMapEntry* installed = install_hit(projection, 0x42, value, entry);
  model::reset();

  NounProjectionVector* result =
      pkg11_sim_core_00b21340(&projection, create_callback, clear_callback,
                              add_callback, filter_callback, 0x42);

  assert(result == &value);
  assert(projection.noun_map.anchor.parent == &installed->entry.base);
  assert(projection.noun_map.size == 1);
  assert(model::events.empty());
}

void test_exact_key_with_greater_right_child_takes_create_insert_path() {
  NounProjection projection{};
  NounProjectionVector existing{};
  NounProjectionVector created{};
  NounMapEntry entry{};
  NounMapEntry greater{};
  NounListNode node{};
  initialize_empty_list(projection);
  add_list_node(projection, node);
  entry.entry.base.right = &greater.entry.base;
  entry.entry.key = 0x42;
  entry.value = &existing;
  greater.entry.key = 0x43;
  greater.value = &existing;
  projection.noun_map.anchor.parent = &entry.entry.base;
  projection.noun_map.size = 2;
  created.needs_update = 1;
  model::reset();
  model::created = &created;
  model::filter_results = {1};

  NounProjectionVector* result =
      pkg11_sim_core_00b21340(&projection, create_callback, clear_callback,
                              add_callback, filter_callback, 0x42);

  assert(result == &created);
  assert(projection.noun_map.anchor.parent == &model::inserted.entry.base);
  assert(projection.noun_map.size == 3);
  assert(model::inserted.entry.key == 0x42);
  assert(model::inserted.value == &created);
  assert(created.needs_update == 0);
  assert(model::events ==
         (std::vector<model::Event>{
             model::Event{model::EventKind::create, &created, nullptr, 0},
             model::Event{model::EventKind::insert, &created, nullptr, 0x42},
             model::Event{model::EventKind::clear, &created, nullptr, 0},
             model::Event{model::EventKind::filter, nullptr, &node, 0x42},
             model::Event{model::EventKind::add, &created, &node, 0},
         }));
}

void test_dirty_filter_add_order() {
  NounProjection projection{};
  NounProjectionVector value{};
  NounMapEntry entry{};
  NounListNode first{};
  NounListNode second{};
  initialize_empty_list(projection);
  add_list_node(projection, second);
  add_list_node(projection, first);
  NounMapEntry* installed = install_hit(projection, 0x42, value, entry);
  value.needs_update = 1;
  model::reset();
  model::filter_results = {0, 1};

  NounProjectionVector* result =
      pkg11_sim_core_00b21340(&projection, create_callback, clear_callback,
                              add_callback, filter_callback, 0x42);

  assert(result == &value);
  assert(projection.noun_map.anchor.parent == &installed->entry.base);
  assert(value.needs_update == 0);
  assert(model::events ==
         (std::vector<model::Event>{
             model::Event{model::EventKind::clear, &value, nullptr, 0},
             model::Event{model::EventKind::filter, nullptr, &first, 0x42},
             model::Event{model::EventKind::filter, nullptr, &second, 0x42},
             model::Event{model::EventKind::add, &value, &second, 0},
         }));
}

void test_miss_create_insert_and_return() {
  NounProjection projection{};
  NounProjectionVector created{};
  NounListNode node{};
  initialize_empty_list(projection);
  add_list_node(projection, node);
  created.needs_update = 1;
  model::reset();
  model::created = &created;
  model::filter_results = {1};

  NounProjectionVector* result =
      pkg11_sim_core_00b21340(&projection, create_callback, clear_callback,
                              add_callback, filter_callback, 0x99);

  assert(result == &created);
  assert(projection.noun_map.anchor.parent == &model::inserted.entry.base);
  assert(projection.noun_map.size == 1);
  assert(model::inserted.entry.key == 0x99);
  assert(model::inserted.value == &created);
  assert(created.needs_update == 0);
  assert(model::events ==
         (std::vector<model::Event>{
             model::Event{model::EventKind::create, &created, nullptr, 0},
             model::Event{model::EventKind::insert, &created, nullptr, 0x99},
             model::Event{model::EventKind::clear, &created, nullptr, 0},
             model::Event{model::EventKind::filter, nullptr, &node, 0x99},
             model::Event{model::EventKind::add, &created, &node, 0},
         }));
}

void test_dirty_empty_list() {
  NounProjection projection{};
  NounProjectionVector value{};
  NounMapEntry entry{};
  initialize_empty_list(projection);
  NounMapEntry* installed = install_hit(projection, 0x42, value, entry);
  value.needs_update = 1;
  model::reset();

  NounProjectionVector* result =
      pkg11_sim_core_00b21340(&projection, create_callback, clear_callback,
                              add_callback, filter_callback, 0x42);

  assert(result == &value);
  assert(projection.noun_map.anchor.parent == &installed->entry.base);
  assert(value.needs_update == 0);
  assert(model::events ==
         (std::vector<model::Event>{
             model::Event{model::EventKind::clear, &value, nullptr, 0},
         }));
}

}

}

int main() {
  openspore::reconstruction::pkg11_sim_core::test_clean_borrowed_hit();
  openspore::reconstruction::pkg11_sim_core::
      test_exact_key_with_greater_right_child_takes_create_insert_path();
  openspore::reconstruction::pkg11_sim_core::test_dirty_filter_add_order();
  openspore::reconstruction::pkg11_sim_core::
      test_miss_create_insert_and_return();
  openspore::reconstruction::pkg11_sim_core::test_dirty_empty_list();
}
