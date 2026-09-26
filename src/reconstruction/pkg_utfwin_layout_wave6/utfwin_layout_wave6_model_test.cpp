#include <array>
#include <cassert>
#include <cstring>
#include <vector>

#include "utfwin_layout_wave6.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_CDECL __cdecl
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_CDECL __attribute__((cdecl))
#endif

using openspore::reconstruction::pkg_utfwin_layout_wave6::Abi009601e0;
using openspore::reconstruction::pkg_utfwin_layout_wave6::Abi00961260;
using openspore::reconstruction::pkg_utfwin_layout_wave6::Abi00961300;
using openspore::reconstruction::pkg_utfwin_layout_wave6::Abi00962830;
using openspore::reconstruction::pkg_utfwin_layout_wave6::Abi009646d0;
using openspore::reconstruction::pkg_utfwin_layout_wave6::Abi00967e20;
using openspore::reconstruction::pkg_utfwin_layout_wave6::Abi00967e60;
using openspore::reconstruction::pkg_utfwin_layout_wave6::Abi00967e80;
using openspore::reconstruction::pkg_utfwin_layout_wave6::Abi0096feb0;
using openspore::reconstruction::pkg_utfwin_layout_wave6::IntrusiveNode;
using openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager;
using openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow;
using openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindowVtable;
using openspore::reconstruction::pkg_utfwin_layout_wave6::Opaque;
using openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject;
using openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastVtable;
using openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier;
using openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueIndexCarrier;
using openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueTailVtable;

namespace {

using openspore::reconstruction::pkg_utfwin_layout_wave6::
    pkg_utfwin_layout_wave6_009601e0;
using openspore::reconstruction::pkg_utfwin_layout_wave6::
    pkg_utfwin_layout_wave6_00961260;
using openspore::reconstruction::pkg_utfwin_layout_wave6::
    pkg_utfwin_layout_wave6_00961300;
using openspore::reconstruction::pkg_utfwin_layout_wave6::
    pkg_utfwin_layout_wave6_00962830;
using openspore::reconstruction::pkg_utfwin_layout_wave6::
    pkg_utfwin_layout_wave6_009646d0;
using openspore::reconstruction::pkg_utfwin_layout_wave6::
    pkg_utfwin_layout_wave6_00967e20;
using openspore::reconstruction::pkg_utfwin_layout_wave6::
    pkg_utfwin_layout_wave6_00967e60;
using openspore::reconstruction::pkg_utfwin_layout_wave6::
    pkg_utfwin_layout_wave6_00967e80;
using openspore::reconstruction::pkg_utfwin_layout_wave6::
    pkg_utfwin_layout_wave6_0096feb0;

enum class Kind : std::uint8_t {
  parent,
  unlink_insert,
  manager,
  common_cast,
  transfer_00962bc0,
  transfer_0096f240,
  tail_8c,
};

struct Event {
  Kind kind;
  std::array<Opaque, 4> values{};
};

std::array<Event, 64> events{};
std::size_t event_count = 0;
LayoutWindow* parent_result = nullptr;
std::size_t cast_count = 0;
OpaqueCastObject* cast_object = nullptr;
Opaque** cast_output = nullptr;
Opaque* cast_destination = nullptr;
Opaque* cast_slot_value = nullptr;
Opaque transfer_object = 0;
Opaque transfer_flags = 0;
Opaque transfer_result = 0;
Opaque tail_object = 0;
Opaque tail_argument = 0;
Opaque tail_stored = 0;
Opaque tail_result = 0x89abcdefu;
bool tail_saw_stored = false;

Opaque word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

void record(Kind kind, Opaque first = 0, Opaque second = 0, Opaque third = 0,
            Opaque fourth = 0) {
  assert(event_count < events.size());
  events[event_count++] = Event{kind, {first, second, third, fourth}};
}

void reset() {
  event_count = 0;
  parent_result = nullptr;
  cast_count = 0;
  cast_object = nullptr;
  cast_output = nullptr;
  cast_destination = nullptr;
  cast_slot_value = nullptr;
  transfer_object = 0;
  transfer_flags = 0;
  transfer_result = 0;
  tail_object = 0;
  tail_argument = 0;
  tail_stored = 0;
  tail_saw_stored = false;
}

void init_node(IntrusiveNode* node) {
  node->next = node;
  node->previous = node;
}

void append_node(IntrusiveNode* root, IntrusiveNode* node) {
  IntrusiveNode* last = root->previous;
  last->next = node;
  node->previous = last;
  node->next = root;
  root->previous = node;
}

std::vector<LayoutWindow*> node_order(IntrusiveNode* root) {
  std::vector<LayoutWindow*> result;
  IntrusiveNode* current = root->next;
  while (current != root) {
    result.push_back(reinterpret_cast<LayoutWindow*>(
        reinterpret_cast<std::uint8_t*>(current) -
        offsetof(LayoutWindow, sibling_04)));
    current = current->next;
  }
  return result;
}

LayoutWindow* TEST_THISCALL query_parent(LayoutWindow* object) {
  record(Kind::parent, word(object));
  return parent_result;
}

Opaque** TEST_THISCALL cast_slot_d0(OpaqueCastObject* object, Opaque** output) {
  ++cast_count;
  cast_object = object;
  cast_output = output;
  *output = cast_destination;
  return &cast_slot_value;
}

Opaque TEST_THISCALL tail_slot_8c(Opaque* object, Opaque argument) {
  tail_object = word(object);
  tail_argument = argument;
  Opaque* adjusted = reinterpret_cast<Opaque*>(word(object) + 0x20cu);
  tail_stored = adjusted[0x34u / sizeof(Opaque)];
  tail_saw_stored = tail_stored == 0x13579bdfu;
  record(Kind::tail_8c, word(object), argument, tail_stored);
  return tail_result;
}

}

extern "C" Opaque* TEST_THISCALL pkg_re_00951240(Opaque object, Opaque type) {
  record(Kind::common_cast, object, type);
  if (type == 0x06ec581fdu) {
    return reinterpret_cast<Opaque*>(object);
  }
  if ((type == 0xee3f516eu || type == 0xeec58382u) && object != 0) {
    return reinterpret_cast<Opaque*>(object + 4u);
  }
  return nullptr;
}

extern "C" void TEST_CDECL pkg_re_008fe6d0(IntrusiveNode* position,
                                           IntrusiveNode* unused,
                                           IntrusiveNode* node) {
  static_cast<void>(unused);
  record(Kind::unlink_insert, word(position), word(unused), word(node));
  if (position == node) {
    return;
  }
  IntrusiveNode* node_next = node->next;
  IntrusiveNode* node_previous = node->previous;
  node_previous->next = node_next;
  node_next->previous = node_previous;
  IntrusiveNode* position_previous = position->previous;
  position_previous->next = node;
  node->previous = position_previous;
  node->next = position;
  position->previous = node;
}

extern "C" void TEST_THISCALL pkg_re_00958110(LayoutManager* manager) {
  record(Kind::manager, word(manager));
  if (manager->state_25 != 0) {
    return;
  }
  manager->state_25 = 1;
  IntrusiveNode* root = &manager->queue_18;
  while (root->previous != root) {
    IntrusiveNode* current = root->previous;
    IntrusiveNode* previous = current->previous;
    previous->next = root;
    root->previous = previous;
    if (previous != root) {
      previous->next = nullptr;
      previous->previous = nullptr;
    }
    current->previous = nullptr;
  }
}

extern "C" Opaque* TEST_THISCALL pkg_re_00962bc0(Opaque* object, Opaque flags) {
  transfer_object = word(object);
  transfer_flags = flags;
  record(Kind::transfer_00962bc0, transfer_object, transfer_flags,
         transfer_result);
  return reinterpret_cast<Opaque*>(transfer_result);
}

extern "C" Opaque* TEST_THISCALL pkg_re_0096f240(Opaque* object, Opaque type) {
  record(Kind::transfer_0096f240, word(object), type);
  if (type == 0x030d54acu) {
    return object;
  }
  if (type == 0xeec58382u) {
    return reinterpret_cast<Opaque*>(word(object) + 4u);
  }
  return pkg_re_00951240(word(object), type);
}

namespace {

void test_009601e0_fast_and_virtual() {
  reset();
  OpaqueCastVtable vtable{};
  vtable.slot_d0 = cast_slot_d0;
  OpaqueCastObject object{&vtable};
  std::array<Opaque, 32> storage{};
  Opaque* output = storage.data() + 4;
  Opaque* candidate = storage.data() + 8;
  candidate[0x34u / sizeof(Opaque)] = word(&object) - 4u;
  Opaque expected_output = word(candidate) + 4u;

  const Abi009601e0 abi = pkg_utfwin_layout_wave6_009601e0;
  abi(&object, output, candidate);
  assert(*output == expected_output);
  assert(candidate == reinterpret_cast<Opaque*>(expected_output));
  assert(cast_count == 0);

  reset();
  vtable.slot_d0 = cast_slot_d0;
  object.vtable = &vtable;
  storage.fill(0);
  output = storage.data() + 4;
  candidate = storage.data() + 8;
  candidate[0x34u / sizeof(Opaque)] = 0;
  cast_destination = storage.data() + 20;
  cast_slot_value = reinterpret_cast<Opaque*>(0x10203040u);
  abi(&object, output, candidate);
  assert(*output == reinterpret_cast<Opaque>(cast_slot_value));
  assert(candidate == cast_destination);
  assert(cast_count == 1);
  assert(cast_object == &object);
  assert(cast_output == &candidate);
  assert(cast_output != &output);
}

void test_00961260_store() {
  reset();
  OpaqueCastVtable vtable{};
  OpaqueCastObject object{&vtable};
  Opaque output = 0;
  const Abi00961260 abi = pkg_utfwin_layout_wave6_00961260;
  object.value_38 = 0x12345678u;
  abi(&object, &output);
  assert(output == object.value_38);
  assert(output != word(&object) + 0x38u);
  object.value_38 = 0x87654321u;
  abi(&object, &output);
  assert(output == object.value_38);
}

void test_00961300_null_parent_and_mutation() {
  reset();
  LayoutWindowVtable child_vtable{};
  child_vtable.slot_10 = query_parent;
  LayoutWindow parent{};
  LayoutManager manager{};
  init_node(&manager.queue_18);
  LayoutWindow children[3]{};
  IntrusiveNode* root = &parent.children_38;
  init_node(root);
  for (LayoutWindow& child : children) {
    child.vtable = &child_vtable;
    init_node(&child.sibling_04);
    append_node(root, &child.sibling_04);
  }
  parent.manager_30 = &manager;
  parent_result = &parent;
  children[0].flags_28 = 0;
  children[1].flags_28 = 0;
  children[2].flags_28 = 0;

  const Abi00961300 abi = pkg_utfwin_layout_wave6_00961300;
  abi(&parent, nullptr);
  assert(event_count == 0);

  abi(&parent, &children[0]);
  assert((node_order(root) == std::vector<LayoutWindow*>{
                                  &children[1], &children[2], &children[0]}));
  assert(event_count == 3);
  assert(events[0].kind == Kind::parent);
  assert(events[0].values[0] == word(&children[0]));
  assert(events[1].kind == Kind::unlink_insert);
  assert(events[1].values[0] == word(root));
  assert(events[1].values[1] == word(root));
  assert(events[1].values[2] == word(&children[0].sibling_04));
  assert(events[1].values[2] != events[1].values[0]);
  assert(events[2].kind == Kind::manager);
  assert(manager.state_25 == 1);

  reset();
  parent_result = &parent;
  manager.state_25 = 0;
  init_node(root);
  for (LayoutWindow& child : children) {
    init_node(&child.sibling_04);
    append_node(root, &child.sibling_04);
  }
  children[0].flags_28 = 0x40u;
  children[1].flags_28 = 0;
  children[2].flags_28 = 0x40u;
  abi(&parent, &children[2]);
  assert((node_order(root) == std::vector<LayoutWindow*>{
                                  &children[0], &children[2], &children[1]}));
  assert(event_count == 2);
  assert(events[0].kind == Kind::parent);
  assert(events[1].kind == Kind::manager);

  reset();
  parent_result = &parent;
  manager.state_25 = 0;
  init_node(root);
  for (LayoutWindow& child : children) {
    init_node(&child.sibling_04);
    append_node(root, &child.sibling_04);
  }
  children[0].flags_28 = 0x40u;
  children[1].flags_28 = 0x40u;
  children[2].flags_28 = 0x40u;
  abi(&parent, &children[1]);
  assert((node_order(root) == std::vector<LayoutWindow*>{
                                  &children[0], &children[2], &children[1]}));
  assert(event_count == 2);

  reset();
  parent_result = reinterpret_cast<LayoutWindow*>(0x11111111u);
  children[0].flags_28 = 0;
  abi(&parent, &children[0]);
  assert(event_count == 1);
  assert(events[0].kind == Kind::parent);
}

void test_00962830_transfer() {
  reset();
  Opaque object = 0x12345678u;
  transfer_result = 0x00fedcbau;
  const Abi00962830 abi = pkg_utfwin_layout_wave6_00962830;
  Opaque* result = abi(reinterpret_cast<Opaque*>(object), 0xa5u);
  assert(result == reinterpret_cast<Opaque*>(transfer_result));
  assert(transfer_object == 0x12345674u);
  assert(transfer_flags == 0xa5u);
  assert(event_count == 1);
  assert(events[0].kind == Kind::transfer_00962bc0);
}

void test_009646d0_dispatch() {
  reset();
  const Opaque object = 0x12345000u;
  assert(pkg_utfwin_layout_wave6_009646d0(object, 0x2f02135cu) ==
         reinterpret_cast<Opaque*>(object + 0x0cu));
  assert(pkg_utfwin_layout_wave6_009646d0(object, 0xeec58382u) ==
         reinterpret_cast<Opaque*>(object + 4u));
  assert(pkg_utfwin_layout_wave6_009646d0(0, 0x2f02135cu) == nullptr);
  assert(pkg_utfwin_layout_wave6_009646d0(0, 0xeec58382u) == nullptr);
  assert(pkg_utfwin_layout_wave6_009646d0(object, 0x06ec581fdu) ==
         reinterpret_cast<Opaque*>(object));
  assert(pkg_utfwin_layout_wave6_009646d0(object, 0xee3f516eu) ==
         reinterpret_cast<Opaque*>(object + 4u));
  assert(pkg_utfwin_layout_wave6_009646d0(object, 0x12345678u) == nullptr);
  assert(event_count == 3);
}

void test_00967e20_bounds() {
  reset();
  OpaqueIndexCarrier object{};
  Opaque values[6]{};
  const Abi00967e20 abi = pkg_utfwin_layout_wave6_00967e20;
  abi(&object, 0, &values[0]);
  abi(&object, 5, &values[5]);
  abi(&object, 6, &values[1]);
  abi(&object, 0xffffffffu, &values[2]);
  abi(nullptr, 6, &values[3]);
  assert(object.values_14[0] == &values[0]);
  assert(object.values_14[1] == nullptr);
  assert(object.values_14[2] == nullptr);
  assert(object.values_14[3] == nullptr);
  assert(object.values_14[4] == nullptr);
  assert(object.values_14[5] == &values[5]);
}

void test_00967e60_store_and_return() {
  reset();
  OpaqueImageCarrier object{};
  Opaque value = 0x12345678u;
  const Abi00967e60 abi = pkg_utfwin_layout_wave6_00967e60;
  Opaque* result = abi(&object, reinterpret_cast<Opaque*>(value));
  assert(result == reinterpret_cast<Opaque*>(value));
  assert(object.value_2c == result);
  result = abi(&object, nullptr);
  assert(result == nullptr);
  assert(object.value_2c == nullptr);
}

void test_00967e80_store_then_tail_virtual() {
  reset();
  OpaqueTailVtable vtable{};
  vtable.slot_8c = tail_slot_8c;
  std::vector<Opaque> memory((0x20cu + 0x38u) / sizeof(Opaque) + 4u, 0);
  reinterpret_cast<OpaqueTailVtable**>(memory.data())[0] = &vtable;
  Opaque* object = memory.data() + 0x20cu / sizeof(Opaque);
  const Abi00967e80 abi = pkg_utfwin_layout_wave6_00967e80;
  const Opaque result = abi(object, 0x13579bdfu);
  assert(result == 0x89abcdefu);
  assert(object[0x34u / sizeof(Opaque)] == 0x13579bdfu);
  assert(tail_object == word(memory.data()));
  assert(tail_argument == 1);
  assert(tail_saw_stored);
  assert(event_count == 1);
  assert(events[0].kind == Kind::tail_8c);
}

void test_0096feb0_transfer_and_cast() {
  reset();
  const Abi0096feb0 abi = pkg_utfwin_layout_wave6_0096feb0;
  const Opaque object = 0x12345000u;
  assert(abi(reinterpret_cast<Opaque*>(object), 0x030d54acu) ==
         reinterpret_cast<Opaque*>(object - 4u));
  assert(abi(reinterpret_cast<Opaque*>(object), 0xeec58382u) ==
         reinterpret_cast<Opaque*>(object));
  assert(abi(reinterpret_cast<Opaque*>(object), 0x06ec581fdu) ==
         reinterpret_cast<Opaque*>(object - 4u));
  assert(abi(reinterpret_cast<Opaque*>(object), 0xee3f516eu) ==
         reinterpret_cast<Opaque*>(object));
  assert(abi(reinterpret_cast<Opaque*>(object), 0x12345678u) == nullptr);
  assert(abi(nullptr, 0x030d54acu) == reinterpret_cast<Opaque*>(0xfffffffcu));
  assert(abi(nullptr, 0xeec58382u) == nullptr);
}

}

int main() {
  test_009601e0_fast_and_virtual();
  test_00961260_store();
  test_00961300_null_parent_and_mutation();
  test_00962830_transfer();
  test_009646d0_dispatch();
  test_00967e20_bounds();
  test_00967e60_store_and_return();
  test_00967e80_store_then_tail_virtual();
  test_0096feb0_transfer_and_cast();
}

#undef TEST_CDECL
#undef TEST_THISCALL
