// PKG-APP-PROPERTY-GET-WAVE15 -- focused model test for VA 0x006a2530,
// App::PropertyList::GetProperty.
//
// The single direct callee (0x00612db0) is machine-observed but belongs to a
// different target, so this test supplies a transcription of its 33-instruction
// body and checks only what 0x006a2530 itself decides: which range and key it
// forwards, the hit predicate, exactly what it writes through the out pointer,
// when it escalates to the parent port at vtable+0x24, and that it mutates
// nothing.

#include "property_list_get_property_006a2530.hpp"

#include <cstdio>
#include <cstring>

namespace {

using openspore::reconstruction::pkg_app_property_get_wave15::Property;
using openspore::reconstruction::pkg_app_property_get_wave15::PropertyEntry;
using openspore::reconstruction::pkg_app_property_get_wave15::PropertyList;
using openspore::reconstruction::pkg_app_property_get_wave15::PropertyListVtable;
using openspore::reconstruction::pkg_app_property_get_wave15::kEntryStride;
using openspore::reconstruction::pkg_app_property_get_wave15::kEntryValueOffset;

struct HelperRecord {
  unsigned calls;
  const PropertyEntry* begin;
  const PropertyEntry* end;
  std::uint32_t property_id;
  std::uint32_t ignored_byte;
};

struct ParentRecord {
  unsigned calls;
  const PropertyList* receiver;
  std::uint32_t property_id;
  Property** result;
  Property* publish;
  bool answer;
};

HelperRecord g_helper;
ParentRecord g_parent;
unsigned g_decoy_calls = 0;

int g_failures = 0;

void check(bool condition, const char* what) {
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s\n", what);
  }
}

}  // namespace

// Transcription of 0x00612db0. The element count is the byte distance between
// the two range pointers divided by the 0x18 stride (IMUL 0x2AAAAAAB / SAR 2 /
// SHR 0x1F), then a halving probe: the key at base + 24 * (count / 2) decides
// which half survives, and the whole-element step is 0x18. It returns the first
// element whose key is >= propertyID, or mpEnd. The fourth argument is accepted
// and never read, exactly as in the original, and the bare RET pops nothing.
extern "C" PropertyEntry* __attribute__((cdecl))
property_list_lower_bound_00612db0(PropertyEntry* mpBegin, PropertyEntry* mpEnd,
                                   const std::uint32_t* propertyID,
                                   std::uint32_t ignored_mValueCompare_byte) {
  ++g_helper.calls;
  g_helper.begin = mpBegin;
  g_helper.end = mpEnd;
  g_helper.property_id = *propertyID;
  g_helper.ignored_byte = ignored_mValueCompare_byte;

  PropertyEntry* current = mpBegin;
  const auto distance = reinterpret_cast<std::uintptr_t>(mpEnd) -
                        reinterpret_cast<std::uintptr_t>(mpBegin);
  std::size_t count = static_cast<std::size_t>(distance) / kEntryStride;
  while (count != 0) {
    const std::size_t half = count / 2;
    PropertyEntry* const middle = current + half;
    if (middle->first < *propertyID) {
      current = middle + 1;
      count -= half + 1;
    } else {
      count = half;
    }
  }
  return current;
}

// Recording stand-in for whatever a concrete parent list installs at
// vtable+0x24. It publishes `publish` into the caller's out pointer when asked to
// succeed, so the test can see that 0x006a2530 forwards the caller's own out
// pointer rather than one of its own.
extern "C" bool __attribute__((thiscall))
parent_port_006a2530_test(PropertyList* parent, std::uint32_t propertyID,
                          Property** result) {
  ++g_parent.calls;
  g_parent.receiver = parent;
  g_parent.property_id = propertyID;
  g_parent.result = result;
  if (g_parent.answer && g_parent.publish != nullptr) {
    *result = g_parent.publish;
  }
  return g_parent.answer;
}

// A second port, installed at vtable+0x28. The body must never reach it: the SDK
// vtable puts GetPropertyObject there, not GetProperty.
extern "C" bool __attribute__((thiscall))
decoy_port_006a2530_test(PropertyList* parent, std::uint32_t propertyID,
                         Property** result) {
  ++g_decoy_calls;
  (void)parent;
  (void)propertyID;
  (void)result;
  return false;
}

namespace {

void reset() {
  g_helper = HelperRecord{};
  g_parent = ParentRecord{};
  g_decoy_calls = 0;
}

// Builds a receiver over a raw 0x38-byte block so the offsets under test are the
// ones the binary uses, not the ones a C++ layout would pick.
PropertyList* make_list(std::uint8_t* block, PropertyEntry* begin,
                        PropertyEntry* end, std::int32_t value_compare,
                        PropertyList* parent) {
  std::memset(block, 0, sizeof(PropertyList));
  auto* list = reinterpret_cast<PropertyList*>(block);
  list->_vftable0 = nullptr;
  list->mProperties.mpBegin = begin;
  list->mProperties.mpEnd = end;
  list->mProperties.mValueCompare = value_compare;
  list->mpParent = parent;
  return list;
}

}  // namespace

int main() {
  alignas(4) PropertyEntry table[4] = {};
  table[0].first = 10;
  table[0].second.mnFlags = 0x0102;
  table[0].second.mnType = 1;
  table[1].first = 20;
  table[1].second.mnFlags = 0x0304;
  table[1].second.mnType = 2;
  table[2].first = 30;
  table[2].second.mnFlags = 0x0506;
  table[2].second.mnType = 3;
  table[3].first = 40;
  table[3].second.mnFlags = 0x0708;
  table[3].second.mnType = 4;

  Property* const sentinel = reinterpret_cast<Property*>(
      static_cast<std::uintptr_t>(0x016027d0u));

  alignas(4) std::uint8_t child_bytes[sizeof(PropertyList)];
  alignas(4) std::uint8_t parent_bytes[sizeof(PropertyList)];
  alignas(4) std::uint8_t empty_bytes[sizeof(PropertyList)];
  alignas(4) std::uint8_t vtable_bytes[sizeof(PropertyListVtable)];
  alignas(4) std::uint8_t snapshot[sizeof(PropertyList)];

  PropertyList* const parent =
      make_list(parent_bytes, table + 4, table + 4, 0x11, nullptr);
  PropertyList* const child =
      make_list(child_bytes, table, table + 4, 0x5a, parent);

  std::memset(vtable_bytes, 0, sizeof(vtable_bytes));
  auto* const vtable = reinterpret_cast<PropertyListVtable*>(vtable_bytes);
  vtable->GetProperty = &parent_port_006a2530_test;
  // The vtable models +0x28 as an untyped slot (the SDK types it
  // GetPropertyObject, whose return type differs from this port's), so the
  // decoy is installed through a void* lvalue.
  reinterpret_cast<void*&>(vtable->GetPropertyObject) =
      reinterpret_cast<void*>(&decoy_port_006a2530_test);
  child->_vftable0 = vtable;
  parent->_vftable0 = vtable;

  // 1. Exact local hit publishes the address of the value half and reports true.
  //    0x006a256b ADD EAX,0x4 ; 0x006a256f MOV [ECX],EAX ; 0x006a2571 MOV AL,1.
  {
    reset();
    Property* out = nullptr;
    check(property_list_get_property_006a2530(child, 20, &out), "hit returns true");
    check(out == &table[1].second,
          "hit publishes the address of entry+0x04, not the entry");
    check(out->mnType == 2 && out->mnFlags == 0x0304,
          "the published pointer reads back as the stored Property value");
    check(g_helper.calls == 1, "hit performs exactly one helper call");
    check(g_helper.begin == table && g_helper.end == table + 4,
          "helper receives the +0x18/+0x1c range");
    check(g_helper.property_id == 20, "helper receives the requested id");
    check(g_helper.ignored_byte == 0x5a,
          "low byte of the +0x2c word is forwarded as the fourth helper argument");
    check(g_parent.calls == 0, "a local hit never escalates");
  }

  // 2. Lower bound lands on a strictly greater key, so it is not a hit even
  //    though the helper returned a non-end pointer. 0x006a2556/0x006a2558.
  {
    reset();
    g_parent.answer = true;
    g_parent.publish = sentinel;
    Property* out = nullptr;
    check(property_list_get_property_006a2530(child, 25, &out),
          "key-above reject falls through to the parent");
    check(out == sentinel, "parent writes into the caller's out pointer");
    check(g_parent.calls == 1, "reject escalates exactly once");
    check(g_parent.receiver == parent, "parent receiver comes from +0x30");
    check(g_parent.property_id == 25, "parent port receives the original id");
    check(g_parent.result == &out, "parent port receives the caller's out pointer");
    check(g_decoy_calls == 0, "the +0x28 slot is never dispatched to");
    check(g_helper.begin == table && g_helper.end == table + 4,
          "only the receiver's own range is searched before escalating");
  }

  // 3. Property id above every key: the lower bound returns mpEnd and the end
  //    sentinel is rejected. 0x006a2552/0x006a2554.
  {
    reset();
    g_parent.answer = false;
    Property* out = sentinel;
    check(!property_list_get_property_006a2530(child, 99, &out),
          "above-top id escalates and the parent answers false");
    check(out == sentinel, "a false parent leaves the out pointer alone");
    check(g_parent.calls == 1, "end sentinel escalates exactly once");
  }

  // 4. Chain root reached with a null parent: false, out pointer untouched, and
  //    no second helper call. 0x006a257c/0x006a2590.
  {
    reset();
    Property* out = sentinel;
    check(!property_list_get_property_006a2530(parent, 20, &out),
          "null parent answers false");
    check(out == sentinel, "false path never writes the out pointer");
    check(g_helper.calls == 1, "only the receiver's own range is searched");
    check(g_parent.calls == 0, "null parent is never dispatched to");
  }

  // 5. Empty table: begin == end, so the helper sees a zero count and returns
  //    begin, which the sentinel test rejects.
  {
    reset();
    g_parent.answer = true;
    g_parent.publish = sentinel;
    auto* empty = make_list(empty_bytes, table + 4, table + 4, 0x00, parent);
    empty->_vftable0 = vtable;
    Property* out = nullptr;
    check(property_list_get_property_006a2530(empty, 20, &out),
          "empty local table escalates to the parent");
    check(g_helper.calls == 1, "empty range is still one helper call");
    check(out == sentinel, "empty local table publishes nothing of its own");
  }

  // 6. Lowest and highest keys both hit locally without touching the parent.
  {
    reset();
    Property* out = nullptr;
    check(property_list_get_property_006a2530(child, 10, &out), "first key hits");
    check(out == &table[0].second, "first key publishes entry+0x04");
    out = nullptr;
    check(property_list_get_property_006a2530(child, 40, &out), "last key hits");
    check(out == &table[3].second, "last key publishes entry+0x04");
    check(g_parent.calls == 0, "local hits never consult the parent");
  }

  // 7. The body is a pure read: no byte of the receiver changes, including the
  //    +0x34 word that sibling bodies such as 0x006a2f10 do increment.
  {
    reset();
    std::memcpy(snapshot, child_bytes, sizeof(PropertyList));
    Property* out = nullptr;
    (void)property_list_get_property_006a2530(child, 25, &out);
    (void)property_list_get_property_006a2530(child, 20, &out);
    (void)property_list_get_property_006a2530(child, 99, &out);
    check(std::memcmp(snapshot, child_bytes, sizeof(PropertyList)) == 0,
          "0x006a2530 mutates no receiver byte");
  }

  // 8. The published pointer is a borrow into the receiver's own table, not a
  //    copy and not a fresh allocation: it stays valid and stable after the
  //    call returns, which is what ADD EAX,0x4 / MOV [ECX],EAX does.
  {
    reset();
    Property* out = nullptr;
    (void)property_list_get_property_006a2530(child, 30, &out);
    check(out == &table[2].second, "published pointer aliases the table entry");
    check(reinterpret_cast<std::uintptr_t>(out) -
              reinterpret_cast<std::uintptr_t>(&table[2]) ==
          kEntryValueOffset,
          "published pointer is exactly entry+0x04");
  }

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("all checks passed\n");
  return 0;
}
