#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <vector>

#include "helper_wave2.hpp"

namespace openspore::reconstruction::pkg11_h3_helper_wave2 {
namespace {

enum class Event {
  add_ref,
  allocate,
  deallocate,
  release,
  teardown,
  dependencies,
};

struct PendingBlock {
  std::uint32_t marker;
  std::array<OpaqueNoun*, 8> entries;
  std::uint32_t guard;
};

std::vector<Event> events;
std::vector<std::size_t> allocation_sizes;
std::vector<PendingBlock*> allocated_blocks;
std::vector<PendingBlock*> deallocated_blocks;
std::vector<std::pair<OpaqueNoun*, int>> ref_counts;
OpaqueNounManager* current_manager = nullptr;
bool allocation_fails = false;

PendingBlock* new_block(std::uint32_t marker) {
  auto* block = new PendingBlock{};
  block->marker = marker;
  block->guard = 0xfeedfaceU;
  allocated_blocks.push_back(block);
  return block;
}

PendingBlock* block_from_entries(OpaqueNoun** entries) {
  return reinterpret_cast<PendingBlock*>(
      reinterpret_cast<std::uint8_t*>(entries) -
      offsetof(PendingBlock, entries));
}

OpaqueNoun** allocate_entries(std::size_t bytes) {
  events.push_back(Event::allocate);
  allocation_sizes.push_back(bytes);
  if (allocation_fails) {
    return nullptr;
  }
  return new_block(0x80000001U)->entries.data();
}

void deallocate_entries(OpaqueNoun** entries) {
  events.push_back(Event::deallocate);
  PendingBlock* block = block_from_entries(entries);
  deallocated_blocks.push_back(block);
  block->marker = 0U;
}

void reset_state() {
  for (PendingBlock* block : allocated_blocks) {
    delete block;
  }
  events.clear();
  allocation_sizes.clear();
  allocated_blocks.clear();
  deallocated_blocks.clear();
  ref_counts.clear();
  current_manager = nullptr;
  allocation_fails = false;
  g_pending_growth_ports_00aea5d0.allocate = &allocate_entries;
  g_pending_growth_ports_00aea5d0.deallocate = &deallocate_entries;
}

void cleanup_blocks() {
  for (PendingBlock* block : allocated_blocks) {
    delete block;
  }
  allocated_blocks.clear();
  deallocated_blocks.clear();
}

void check(bool condition) {
  if (!condition) {
    std::_Exit(1);
  }
}

#define CHECK(expression)                 \
  do {                                    \
    check(static_cast<bool>(expression)); \
  } while (false)

bool queue_contains(OpaqueNoun* noun) {
  OpaqueNoun** begin = current_manager->pending.begin;
  OpaqueNoun** end = current_manager->pending.end;
  if (begin == nullptr) {
    return false;
  }
  for (OpaqueNoun** entry = begin; entry != end; ++entry) {
    if (*entry == noun) {
      return true;
    }
  }
  return false;
}

int& ref_count(OpaqueNoun* noun) {
  for (auto& entry : ref_counts) {
    if (entry.first == noun) {
      return entry.second;
    }
  }
  ref_counts.emplace_back(noun, 0);
  return ref_counts.back().second;
}

void __attribute__((thiscall)) record_add_ref(OpaqueNoun* noun) {
  CHECK(noun != nullptr);
  CHECK(noun->vtable != nullptr);
  ++ref_count(noun);
  events.push_back(Event::add_ref);
}

void __attribute__((thiscall)) record_release(OpaqueNoun* noun) {
  CHECK(noun != nullptr);
  CHECK(noun->vtable != nullptr);
  int& count = ref_count(noun);
  CHECK(count > 0);
  --count;
  events.push_back(Event::release);
}

void __attribute__((thiscall)) record_teardown(OpaqueNounManager* manager,
                                               OpaqueNoun* noun) {
  CHECK(manager == current_manager);
  CHECK(noun != nullptr);
  CHECK(noun->vtable != nullptr);
  CHECK(noun->destruction_pending == 1U);
  CHECK(events.back() == Event::release);
  if (manager->pending.begin != nullptr) {
    CHECK(queue_contains(noun));
  }
  events.push_back(Event::teardown);
}

void __attribute__((thiscall)) record_dependencies(OpaqueNounManager* manager,
                                                   OpaqueNoun* noun) {
  CHECK(manager == current_manager);
  CHECK(noun != nullptr);
  CHECK(noun->vtable != nullptr);
  CHECK(events.back() == Event::teardown);
  events.push_back(Event::dependencies);
}

OpaqueNounVtable make_noun() { return {&record_add_ref, &record_release}; }

void test_in_place_append() {
  reset_state();
  OpaqueNounManager manager{};
  OpaqueNoun noun{};
  OpaqueNounVtable vtable = make_noun();
  noun.vtable = &vtable;
  PendingBlock* block = new_block(0x80000001U);
  manager.pending.begin = block->entries.data();
  manager.pending.end = block->entries.data();
  manager.pending.capacity = block->entries.data() + 2;
  current_manager = &manager;
  const std::uint32_t marker_before = block->marker;
  const std::uint32_t guard_before = block->guard;

  noun_manager_logical_destroy_00b225d0(&manager, &noun);

  CHECK(noun.destruction_pending == 1U);
  CHECK(manager.pending.begin == block->entries.data());
  CHECK(manager.pending.end == block->entries.data() + 1);
  CHECK(manager.pending.capacity == block->entries.data() + 2);
  CHECK(block->entries[0] == &noun);
  CHECK(block->entries[1] == nullptr);
  CHECK(block->marker == marker_before);
  CHECK(block->guard == guard_before);
  CHECK(allocation_sizes.empty());
  CHECK(deallocated_blocks.empty());
  CHECK(events ==
        (std::vector<Event>{Event::add_ref, Event::add_ref, Event::release,
                            Event::teardown, Event::dependencies}));

  noun.vtable = nullptr;
  current_manager = nullptr;
}

void test_empty_growth_append() {
  reset_state();
  OpaqueNounManager manager{};
  OpaqueNoun noun{};
  OpaqueNounVtable vtable = make_noun();
  noun.vtable = &vtable;
  current_manager = &manager;

  noun_manager_logical_destroy_00b225d0(&manager, &noun);

  CHECK(allocated_blocks.size() == 1U);
  PendingBlock* block = allocated_blocks.front();
  CHECK(block->marker == 0x80000001U);
  CHECK(block->guard == 0xfeedfaceU);
  CHECK(manager.pending.begin == block->entries.data());
  CHECK(manager.pending.end == block->entries.data() + 1);
  CHECK(manager.pending.capacity == block->entries.data() + 1);
  CHECK(block->entries[0] == &noun);
  CHECK(allocation_sizes == (std::vector<std::size_t>{sizeof(OpaqueNoun*)}));
  CHECK(deallocated_blocks.empty());
  CHECK(events == (std::vector<Event>{Event::add_ref, Event::allocate,
                                      Event::add_ref, Event::release,
                                      Event::teardown, Event::dependencies}));

  noun.vtable = nullptr;
  current_manager = nullptr;
}

void test_full_growth_append() {
  reset_state();
  OpaqueNounManager manager{};
  OpaqueNoun first{};
  OpaqueNoun second{};
  OpaqueNounVtable first_vtable = make_noun();
  OpaqueNounVtable second_vtable = make_noun();
  first.vtable = &first_vtable;
  second.vtable = &second_vtable;
  PendingBlock* old_block = new_block(0x80000001U);
  old_block->entries[0] = &first;
  manager.pending.begin = old_block->entries.data();
  manager.pending.end = old_block->entries.data() + 1;
  manager.pending.capacity = old_block->entries.data() + 1;
  current_manager = &manager;
  const std::uint32_t old_guard = old_block->guard;

  noun_manager_logical_destroy_00b225d0(&manager, &second);

  CHECK(allocated_blocks.size() == 2U);
  PendingBlock* new_block_value = allocated_blocks.back();
  CHECK(new_block_value->marker == 0x80000001U);
  CHECK(new_block_value->guard == 0xfeedfaceU);
  CHECK(manager.pending.begin == new_block_value->entries.data());
  CHECK(manager.pending.end == new_block_value->entries.data() + 2);
  CHECK(manager.pending.capacity == new_block_value->entries.data() + 2);
  CHECK(new_block_value->entries[0] == &first);
  CHECK(new_block_value->entries[1] == &second);
  CHECK(old_block->marker == 0U);
  CHECK(old_block->guard == old_guard);
  CHECK(deallocated_blocks == (std::vector<PendingBlock*>{old_block}));
  CHECK(allocation_sizes ==
        (std::vector<std::size_t>{2U * sizeof(OpaqueNoun*)}));
  CHECK(events ==
        (std::vector<Event>{Event::add_ref, Event::allocate, Event::add_ref,
                            Event::deallocate, Event::release, Event::teardown,
                            Event::dependencies}));

  first.vtable = nullptr;
  second.vtable = nullptr;
  current_manager = nullptr;
}

void test_middle_insertion() {
  reset_state();
  OpaqueNounManager manager{};
  OpaqueNoun first{};
  OpaqueNoun second{};
  OpaqueNoun third{};
  OpaqueNoun inserted{};
  OpaqueNounVtable first_vtable = make_noun();
  OpaqueNounVtable second_vtable = make_noun();
  OpaqueNounVtable third_vtable = make_noun();
  OpaqueNounVtable inserted_vtable = make_noun();
  first.vtable = &first_vtable;
  second.vtable = &second_vtable;
  third.vtable = &third_vtable;
  inserted.vtable = &inserted_vtable;
  PendingBlock* block = new_block(0x80000001U);
  block->entries[0] = &first;
  block->entries[1] = &second;
  block->entries[2] = &third;
  ref_counts.clear();
  ref_counts.emplace_back(&first, 1);
  ref_counts.emplace_back(&second, 1);
  ref_counts.emplace_back(&third, 1);
  manager.pending.begin = block->entries.data();
  manager.pending.end = block->entries.data() + 3;
  manager.pending.capacity = block->entries.data() + 4;
  OpaqueNoun* source_value = &inserted;
  OpaqueNoun** source = &source_value;

  pending_vector_insert_00aea5d0(&manager.pending, block->entries.data() + 1,
                                 source);

  CHECK(manager.pending.begin == block->entries.data());
  CHECK(manager.pending.end == block->entries.data() + 4);
  CHECK(manager.pending.capacity == block->entries.data() + 4);
  CHECK(block->entries[0] == &first);
  CHECK(block->entries[1] == &inserted);
  CHECK(block->entries[2] == &second);
  CHECK(block->entries[3] == &third);
  CHECK(block->entries[4] == nullptr);
  CHECK(ref_count(&first) == 1);
  CHECK(ref_count(&second) == 1);
  CHECK(ref_count(&third) == 1);
  CHECK(ref_count(&inserted) == 1);
  CHECK(allocation_sizes.empty());
  CHECK(deallocated_blocks.empty());
  CHECK(events ==
        (std::vector<Event>{Event::add_ref, Event::add_ref, Event::release,
                            Event::add_ref, Event::release}));

  first.vtable = nullptr;
  second.vtable = nullptr;
  third.vtable = nullptr;
  inserted.vtable = nullptr;
}

void test_spare_capacity_append() {
  reset_state();
  OpaqueNounManager manager{};
  OpaqueNoun first{};
  OpaqueNoun second{};
  OpaqueNoun inserted{};
  OpaqueNounVtable first_vtable = make_noun();
  OpaqueNounVtable second_vtable = make_noun();
  OpaqueNounVtable inserted_vtable = make_noun();
  first.vtable = &first_vtable;
  second.vtable = &second_vtable;
  inserted.vtable = &inserted_vtable;
  PendingBlock* block = new_block(0x80000001U);
  block->entries[0] = &first;
  block->entries[1] = &second;
  block->entries[2] = reinterpret_cast<OpaqueNoun*>(0x80000001U);
  block->entries[3] = reinterpret_cast<OpaqueNoun*>(0xffffffffU);
  ref_counts.clear();
  ref_counts.emplace_back(&first, 1);
  ref_counts.emplace_back(&second, 1);
  manager.pending.begin = block->entries.data();
  manager.pending.end = block->entries.data() + 2;
  manager.pending.capacity = block->entries.data() + 4;
  OpaqueNoun* source_value = &inserted;
  OpaqueNoun** source = &source_value;
  const std::uint32_t marker_before = block->marker;
  const std::uint32_t guard_before = block->guard;

  pending_vector_insert_00aea5d0(&manager.pending, manager.pending.end, source);

  CHECK(manager.pending.begin == block->entries.data());
  CHECK(manager.pending.end == block->entries.data() + 3);
  CHECK(manager.pending.capacity == block->entries.data() + 4);
  CHECK(block->entries[0] == &first);
  CHECK(block->entries[1] == &second);
  CHECK(block->entries[2] == &inserted);
  CHECK(block->entries[3] == reinterpret_cast<OpaqueNoun*>(0xffffffffU));
  CHECK(block->marker == marker_before);
  CHECK(block->guard == guard_before);
  CHECK(ref_count(&first) == 1);
  CHECK(ref_count(&second) == 1);
  CHECK(ref_count(&inserted) == 1);
  CHECK(events == (std::vector<Event>{Event::add_ref}));

  first.vtable = nullptr;
  second.vtable = nullptr;
  inserted.vtable = nullptr;
}

void test_zero_marker_skips_deallocation() {
  reset_state();
  OpaqueNounManager manager{};
  OpaqueNoun first{};
  OpaqueNoun second{};
  OpaqueNounVtable first_vtable = make_noun();
  OpaqueNounVtable second_vtable = make_noun();
  first.vtable = &first_vtable;
  second.vtable = &second_vtable;
  PendingBlock* old_block = new_block(0U);
  old_block->entries[0] = &first;
  manager.pending.begin = old_block->entries.data();
  manager.pending.end = old_block->entries.data() + 1;
  manager.pending.capacity = old_block->entries.data() + 1;
  current_manager = &manager;

  noun_manager_logical_destroy_00b225d0(&manager, &second);

  CHECK(allocated_blocks.size() == 2U);
  CHECK(old_block->marker == 0U);
  CHECK(old_block->guard == 0xfeedfaceU);
  CHECK(deallocated_blocks.empty());
  CHECK(manager.pending.begin == allocated_blocks.back()->entries.data());
  CHECK(manager.pending.capacity ==
        allocated_blocks.back()->entries.data() + 2);

  first.vtable = nullptr;
  second.vtable = nullptr;
  current_manager = nullptr;
}

void test_null_end_in_place_boundary() {
  reset_state();
  OpaqueNounManager manager{};
  OpaqueNoun noun{};
  OpaqueNounVtable vtable = make_noun();
  noun.vtable = &vtable;
  manager.pending.begin = nullptr;
  manager.pending.end = nullptr;
  manager.pending.capacity = reinterpret_cast<OpaqueNoun**>(sizeof(void*));
  current_manager = &manager;

  noun_manager_logical_destroy_00b225d0(&manager, &noun);

  CHECK(manager.pending.begin == nullptr);
  CHECK(manager.pending.end == reinterpret_cast<OpaqueNoun**>(sizeof(void*)));
  CHECK(allocation_sizes.empty());
  CHECK(deallocated_blocks.empty());
  CHECK(events == (std::vector<Event>{Event::add_ref, Event::release,
                                      Event::teardown, Event::dependencies}));

  noun.vtable = nullptr;
  current_manager = nullptr;
}

struct EmbeddedOwner {
  std::uint32_t prefix[2];
  OpaqueEmbeddedObject receiver;
  std::uint32_t suffix[2];
};

void test_embedded_receiver_offset() {
  EmbeddedOwner owner{};
  owner.prefix[0] = 0x80000000U;
  owner.prefix[1] = 0xffffffffU;
  owner.receiver.first_word = 0x80000000U;
  owner.receiver.trailing_words[0] = 0xffffffffU;
  owner.receiver.trailing_words[1] = 0xdeadbeefU;
  owner.receiver.trailing_words[2] = 0x80000001U;
  owner.suffix[0] = 0xcafebabeU;
  owner.suffix[1] = 0x7fffffffU;
  const EmbeddedOwner before = owner;
  const std::array<std::uint32_t, 3> values = {0U, 0x80000000U, 0xffffffffU};

  for (std::uint32_t value : values) {
    owner.receiver.first_word = value;
    embedded_object_first_word_init_00743b50(&owner.receiver);
    CHECK(owner.receiver.first_word == 0U);
  }

  CHECK(owner.prefix[0] == before.prefix[0]);
  CHECK(owner.prefix[1] == before.prefix[1]);
  CHECK(owner.receiver.trailing_words[0] == before.receiver.trailing_words[0]);
  CHECK(owner.receiver.trailing_words[1] == before.receiver.trailing_words[1]);
  CHECK(owner.receiver.trailing_words[2] == before.receiver.trailing_words[2]);
  CHECK(owner.suffix[0] == before.suffix[0]);
  CHECK(owner.suffix[1] == before.suffix[1]);
}

struct StrategyOwner {
  std::array<std::uint32_t, 2> prefix;
  OpaqueStrategyBaseWire receiver;
  std::array<std::uint32_t, 3> suffix;
};

void test_strategy_constructor() {
  StrategyOwner owner{};
  owner.prefix[0] = 0x80000000U;
  owner.prefix[1] = 0xffffffffU;
  owner.receiver.word_00 = 0xffffffffU;
  owner.receiver.word_04 = 0xffffffffU;
  owner.receiver.word_08 = 0xffffffffU;
  owner.receiver.word_0c = 0xffffffffU;
  owner.receiver.word_10 = 0xffffffffU;
  owner.receiver.word_14 = 0xffffffffU;
  owner.receiver.word_18 = 0xffffffffU;
  owner.suffix[0] = 0xdeadbeefU;
  owner.suffix[1] = 0x80000001U;
  owner.suffix[2] = 0U;
  const std::array<std::uint32_t, 2> prefix_before = owner.prefix;
  const std::array<std::uint32_t, 3> suffix_before = owner.suffix;

  strategy_base_constructor_00b5b960(&owner.receiver);

  CHECK(owner.receiver.word_00 == kPrimaryVtable_01461580);
  CHECK(owner.receiver.word_04 == kSecondaryVtable_01461578);
  CHECK(owner.receiver.word_08 == 0U);
  CHECK(owner.receiver.word_0c == kDisabledSentinel);
  CHECK(owner.receiver.word_10 == kDisabledSentinel);
  CHECK(owner.receiver.word_14 == kDisabledSentinel);
  CHECK(owner.receiver.word_18 == 0U);
  CHECK(owner.prefix == prefix_before);
  CHECK(owner.suffix == suffix_before);
  CHECK(kStrategyBaseWrites_00b5b960 == (std::array<StrategyBaseWrite, 8>{{
                                            {0x04, 0x013ef094U},
                                            {0x08, 0U},
                                            {0x00, 0x01461580U},
                                            {0x04, 0x01461578U},
                                            {0x0c, 0xffffffffU},
                                            {0x10, 0xffffffffU},
                                            {0x14, 0xffffffffU},
                                            {0x18, 0U},
                                        }}));

  strategy_base_constructor_00b5b960(&owner.receiver);
  CHECK(owner.receiver.word_00 == kPrimaryVtable_01461580);
  CHECK(owner.receiver.word_04 == kSecondaryVtable_01461578);
  CHECK(owner.receiver.word_08 == 0U);
  CHECK(owner.receiver.word_0c == kDisabledSentinel);
  CHECK(owner.receiver.word_10 == kDisabledSentinel);
  CHECK(owner.receiver.word_14 == kDisabledSentinel);
  CHECK(owner.receiver.word_18 == 0U);
}

template <typename Function>
void expect_fault(Function function) {
  const pid_t child = fork();
  CHECK(child >= 0);
  if (child == 0) {
    function();
    std::_Exit(0);
  }
  int status = 0;
  CHECK(waitpid(child, &status, 0) == child);
  CHECK(WIFSIGNALED(status));
  CHECK(WTERMSIG(status) == SIGSEGV);
}

void test_fault_boundaries() {
  reset_state();
  OpaqueNounManager manager{};
  OpaqueNoun noun{};
  OpaqueNounVtable vtable = make_noun();
  noun.vtable = &vtable;
  current_manager = &manager;

  expect_fault([&] { noun_manager_logical_destroy_00b225d0(nullptr, &noun); });
  expect_fault(
      [&] { noun_manager_logical_destroy_00b225d0(&manager, nullptr); });
  noun.vtable = nullptr;
  expect_fault([&] { noun_manager_logical_destroy_00b225d0(&manager, &noun); });
  noun.vtable = &vtable;
  allocation_fails = true;
  expect_fault([&] { noun_manager_logical_destroy_00b225d0(&manager, &noun); });
  allocation_fails = false;
  noun.vtable = nullptr;
  current_manager = nullptr;

  expect_fault([] { embedded_object_first_word_init_00743b50(nullptr); });
  expect_fault([] {
    embedded_object_first_word_init_00743b50(
        reinterpret_cast<OpaqueEmbeddedObject*>(std::uintptr_t{1}));
  });
  expect_fault([] { strategy_base_constructor_00b5b960(nullptr); });
  expect_fault([] {
    strategy_base_constructor_00b5b960(
        reinterpret_cast<OpaqueStrategyBaseWire*>(std::uintptr_t{1}));
  });
}

}

extern "C" void __attribute__((thiscall)) noun_manager_teardown_00b20d30(
    OpaqueNounManager* manager, OpaqueNoun* noun) {
  record_teardown(manager, noun);
}

extern "C" void __attribute__((thiscall)) noun_manager_dependencies_00b201a0(
    OpaqueNounManager* manager, OpaqueNoun* noun) {
  record_dependencies(manager, noun);
}

}

int main() {
  namespace ns = openspore::reconstruction::pkg11_h3_helper_wave2;
  ns::test_in_place_append();
  ns::test_empty_growth_append();
  ns::test_full_growth_append();
  ns::test_middle_insertion();
  ns::test_spare_capacity_append();
  ns::test_zero_marker_skips_deallocation();
  ns::test_null_end_in_place_boundary();
  ns::test_embedded_receiver_offset();
  ns::test_strategy_constructor();
  ns::test_fault_boundaries();
  ns::cleanup_blocks();
}
