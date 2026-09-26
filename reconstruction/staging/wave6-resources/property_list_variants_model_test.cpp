#include <cassert>
#include <cstdint>

#include "property_list_variants.hpp"

namespace {

using namespace openspore::reconstruction::wave6_resources;

bool parent_has_result = false;
TargetWord parent_has_id = 0;
std::size_t parent_has_calls = 0;
Property* parent_object_result = nullptr;
TargetWord parent_object_id = 0;
std::size_t parent_object_calls = 0;

#if defined(_MSC_VER)
#define WAVE6_TEST_THISCALL __thiscall
#else
#define WAVE6_TEST_THISCALL __attribute__((thiscall))
#endif

bool WAVE6_TEST_THISCALL parent_has(PropertyList*, TargetWord property_id) {
  ++parent_has_calls;
  parent_has_id = property_id;
  return parent_has_result;
}

Property* WAVE6_TEST_THISCALL parent_object(PropertyList*,
                                            TargetWord property_id) {
  ++parent_object_calls;
  parent_object_id = property_id;
  return parent_object_result;
}

#undef WAVE6_TEST_THISCALL

void test_has_property() {
  PropertyMapEntry entries[3]{};
  entries[0].key = 4;
  entries[1].key = 8;
  entries[2].key = 12;
  PropertyList list{};
  list.properties.entries_begin = entries;
  list.properties.entries_end = entries + 3;
  list.properties.lookup_mode = 0x44;
  list.name_key = {1, 2, 3};

  assert(property_list_has_property_006a2470(&list, 8));
  assert(!property_list_has_property_006a2470(&list, 6));
  assert(list.name_key.instance_id == 1);

  HasParentVtable parent_vtable{};
  parent_vtable.get_at_1c = parent_has;
  PropertyList parent{};
  parent.vftable = reinterpret_cast<PropertyListVtable*>(&parent_vtable);
  list.parent = &parent;
  parent_has_result = true;
  parent_has_calls = 0;
  assert(property_list_has_property_006a2470(&list, 6));
  assert(parent_has_calls == 1);
  assert(parent_has_id == 6);
}

void test_get_property_object() {
  PropertyMapEntry entries[2]{};
  entries[0].key = 10;
  entries[1].key = 20;
  PropertyList list{};
  list.properties.entries_begin = entries;
  list.properties.entries_end = entries + 2;

  assert(property_list_get_property_object_006a24d0(&list, 10) ==
         &entries[0].property);
  assert(property_list_get_property_object_006a24d0(&list, 15) ==
         reinterpret_cast<Property*>(static_cast<std::uintptr_t>(0x016027d0u)));

  Property parent_property{};
  parent_object_result = &parent_property;
  parent_object_calls = 0;
  ObjectParentVtable parent_vtable{};
  parent_vtable.get_at_28 = parent_object;
  PropertyList parent{};
  parent.vftable = reinterpret_cast<PropertyListVtable*>(&parent_vtable);
  list.parent = &parent;
  assert(property_list_get_property_object_006a24d0(&list, 15) ==
         &parent_property);
  assert(parent_object_calls == 1);
  assert(parent_object_id == 15);
}

}

int main() {
  test_has_property();
  test_get_property_object();
}
