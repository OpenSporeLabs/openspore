#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "dogfood_006a1de0.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-006a1de0 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_006a1de0 {
namespace {

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

struct LowerBoundObservation {
  unsigned int call_count;
  void* entries_begin;
  void* entries_end;
  const OpaqueWord* key_pointer;
  OpaqueWord key_value;
  std::uint8_t lookup_mode;
};

struct ParentDispatchObservation {
  unsigned int call_count;
  OpaquePropertyList* receiver;
  OpaqueWord property_id;
  OpaqueProperty** result;
};

LowerBoundObservation lower_bound_observation{};
ParentDispatchObservation parent_dispatch_observation{};
OpaquePropertyEntry* configured_lower_bound_result = nullptr;
bool configured_parent_return = false;

struct Fixture {
  OpaquePropertyList list{};
  OpaquePropertyListVtable list_vtable{};
  OpaquePropertyEntry entry_first{};
  OpaquePropertyEntry entry_second{};
  OpaquePropertyList parent{};
  OpaquePropertyListVtable parent_vtable{};
};

// OpaqueProperty is only forward declared: nothing about its size or layout is
// observed by 0x006a1de0. The out pointer therefore starts on a fixed
// non-null marker address so a store through it is detectable without
// instantiating an unknown type.
OpaqueProperty* untouched_out_marker() {
  return reinterpret_cast<OpaqueProperty*>(
      static_cast<std::uintptr_t>(0x00c0de00u));
}

OpaqueProperty* entry_slot_address(OpaquePropertyEntry* entry) {
  return reinterpret_cast<OpaqueProperty*>(
      reinterpret_cast<std::uint8_t*>(entry) + 0x04u);
}

// The 0x00612db0 port. It records the four pushed words and returns whatever
// the test configured; the body never inspects more than the return value.
OpaquePropertyEntry* PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL
lower_bound_00612db0(void* entries_begin, void* entries_end,
                     const OpaqueWord* key, std::uint8_t lookup_mode) {
  ++lower_bound_observation.call_count;
  lower_bound_observation.entries_begin = entries_begin;
  lower_bound_observation.entries_end = entries_end;
  lower_bound_observation.key_pointer = key;
  lower_bound_observation.key_value = key != nullptr ? *key : 0u;
  lower_bound_observation.lookup_mode = lookup_mode;
  return configured_lower_bound_result;
}

// The +0x20 slot of the object reached through list+0x30. The fake records the
// callee-visible words and forwards a configured AL. It deliberately leaves
// the out pointer untouched: whether the dispatched implementation writes
// through it is not observed by 0x006a1de0.
bool PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL
parent_operation_20(OpaquePropertyList* receiver, OpaqueWord property_id,
                    OpaqueProperty** result) {
  ++parent_dispatch_observation.call_count;
  parent_dispatch_observation.receiver = receiver;
  parent_dispatch_observation.property_id = property_id;
  parent_dispatch_observation.result = result;
  return configured_parent_return;
}

bool PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL
list_operation_20(OpaquePropertyList*, OpaqueWord, OpaqueProperty**) {
  return false;
}

bool PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL
list_operation_1c(OpaquePropertyList*, OpaqueWord) {
  return false;
}

void initialize_fixture(Fixture& fixture, OpaqueWord first_key,
                        OpaqueWord second_key) {
  lower_bound_observation = LowerBoundObservation{};
  parent_dispatch_observation = ParentDispatchObservation{};
  configured_lower_bound_result = nullptr;
  configured_parent_return = false;

  fixture = Fixture{};
  fixture.list_vtable = OpaquePropertyListVtable{};
  fixture.list_vtable.operation_1c = list_operation_1c;
  fixture.list_vtable.operation_20 = list_operation_20;
  fixture.list.vtable = &fixture.list_vtable;
  fixture.entry_first = OpaquePropertyEntry{};
  fixture.entry_first.key_00 = first_key;
  fixture.entry_second = OpaquePropertyEntry{};
  fixture.entry_second.key_00 = second_key;
  fixture.list.entries_begin_18 = &fixture.entry_first;
  fixture.list.entries_end_1c = &fixture.entry_second + 1;
  fixture.list.lookup_mode_2c = 0x5au;
  fixture.list.parent_30 = nullptr;
  fixture.parent_vtable = OpaquePropertyListVtable{};
  fixture.parent_vtable.operation_1c = list_operation_1c;
  fixture.parent_vtable.operation_20 = parent_operation_20;
  fixture.parent.vtable = &fixture.parent_vtable;

  g_dogfood_006a1de0_ports = GetPropertyAltPorts{};
  g_dogfood_006a1de0_ports.lower_bound_00612db0 = lower_bound_00612db0;
}

void test_lower_bound_port_receives_span_key_and_mode() {
  Fixture fixture{};
  initialize_fixture(fixture, 0x00000010u, 0x00000020u);
  configured_lower_bound_result = &fixture.entry_first;

  OpaqueProperty* out = untouched_out_marker();
  check(property_list_get_property_alt_006a1de0(&fixture.list, 0x00000010u,
                                                &out));

  check(lower_bound_observation.call_count == 1u);
  check(lower_bound_observation.entries_begin ==
        static_cast<void*>(&fixture.entry_first));
  check(lower_bound_observation.entries_end ==
        static_cast<void*>(
            static_cast<OpaquePropertyEntry*>(&fixture.entry_second + 1)));
  check(lower_bound_observation.key_pointer != nullptr);
  check(lower_bound_observation.key_value == 0x00000010u);
  check(lower_bound_observation.lookup_mode == 0x5au);
}

void test_hit_path_stores_entry_property_slot_address() {
  Fixture fixture{};
  initialize_fixture(fixture, 0x00000010u, 0x00000020u);
  configured_lower_bound_result = &fixture.entry_second;

  OpaqueProperty* out = untouched_out_marker();
  check(property_list_get_property_alt_006a1de0(&fixture.list, 0x00000020u,
                                                &out));

  check(out == entry_slot_address(&fixture.entry_second));
  check(out != untouched_out_marker());
  check(parent_dispatch_observation.call_count == 0u);
}

void test_lower_bound_end_pointer_is_a_miss() {
  Fixture fixture{};
  initialize_fixture(fixture, 0x00000010u, 0x00000020u);
  fixture.list.parent_30 = &fixture.parent;
  configured_lower_bound_result = fixture.list.entries_end_1c;
  configured_parent_return = true;

  OpaqueProperty* out = untouched_out_marker();
  check(property_list_get_property_alt_006a1de0(&fixture.list, 0x00000010u,
                                                &out));

  check(parent_dispatch_observation.call_count == 1u);
  check(parent_dispatch_observation.receiver == &fixture.parent);
  check(parent_dispatch_observation.property_id == 0x00000010u);
  check(parent_dispatch_observation.result == &out);
  check(out == untouched_out_marker());
}

void test_key_below_entry_key_is_a_miss() {
  Fixture fixture{};
  initialize_fixture(fixture, 0x00000010u, 0x00000020u);
  fixture.list.parent_30 = &fixture.parent;
  configured_lower_bound_result = &fixture.entry_second;
  configured_parent_return = false;

  OpaqueProperty* out = untouched_out_marker();
  check(!property_list_get_property_alt_006a1de0(&fixture.list, 0x00000010u,
                                                 &out));

  check(parent_dispatch_observation.call_count == 1u);
  check(out == untouched_out_marker());
}

void test_key_above_entry_key_is_still_a_hit() {
  Fixture fixture{};
  initialize_fixture(fixture, 0x00000000u, 0x00000000u);
  configured_lower_bound_result = &fixture.entry_first;

  OpaqueProperty* out = untouched_out_marker();
  check(property_list_get_property_alt_006a1de0(&fixture.list, 0xffffffffu,
                                                &out));

  check(out == entry_slot_address(&fixture.entry_first));
  check(parent_dispatch_observation.call_count == 0u);
}

void test_zero_key_matches_zero_entry_key() {
  Fixture fixture{};
  initialize_fixture(fixture, 0x00000000u, 0x00000000u);
  configured_lower_bound_result = &fixture.entry_first;

  OpaqueProperty* out = untouched_out_marker();
  check(property_list_get_property_alt_006a1de0(&fixture.list, 0u, &out));

  check(out == entry_slot_address(&fixture.entry_first));
  check(parent_dispatch_observation.call_count == 0u);
}

void test_miss_without_parent_returns_false_and_keeps_out_pointer() {
  Fixture fixture{};
  initialize_fixture(fixture, 0x00000010u, 0x00000020u);
  configured_lower_bound_result = fixture.list.entries_end_1c;

  OpaqueProperty* out = untouched_out_marker();
  check(!property_list_get_property_alt_006a1de0(&fixture.list, 0x00000099u,
                                                 &out));

  check(lower_bound_observation.call_count == 1u);
  check(parent_dispatch_observation.call_count == 0u);
  check(out == untouched_out_marker());
}

void test_miss_forwards_the_parent_slot_return_value() {
  Fixture fixture{};
  initialize_fixture(fixture, 0x00000010u, 0x00000020u);
  fixture.list.parent_30 = &fixture.parent;
  configured_lower_bound_result = fixture.list.entries_end_1c;
  configured_parent_return = true;

  OpaqueProperty* out = untouched_out_marker();
  check(property_list_get_property_alt_006a1de0(&fixture.list, 0x00000010u,
                                                &out));
  check(parent_dispatch_observation.call_count == 1u);

  configured_parent_return = false;
  check(!property_list_get_property_alt_006a1de0(&fixture.list, 0x00000010u,
                                                 &out));
  check(parent_dispatch_observation.call_count == 2u);
}

void test_ports_are_null_by_default() {
  const GetPropertyAltPorts defaults{};
  check(defaults.lower_bound_00612db0 == nullptr);
}

void test_modeled_signatures() {
  using EntrySignature = bool(PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL*)(
      OpaquePropertyList*, OpaqueWord, OpaqueProperty**);
  using LowerBoundSignature = OpaquePropertyEntry*(
      PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL*)(void*, void*, const OpaqueWord*,
                                               std::uint8_t);
  using SlotSignature = bool(PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL*)(
      OpaquePropertyList*, OpaqueWord, OpaqueProperty**);
  using HasPropertySlotSignature =
      bool(PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL*)(OpaquePropertyList*,
                                                       OpaqueWord);

  static_assert(
      std::is_same<decltype(&property_list_get_property_alt_006a1de0),
                   EntrySignature>::value,
      "target is thiscall with the receiver in ECX, one id word and one out "
      "pointer, both reclaimed by RET 0x8");
  static_assert(std::is_same<OpaquePropertyListLowerBound00612db0,
                             LowerBoundSignature>::value,
                "0x00612db0 stays cdecl with the dead mode word last");
  static_assert(
      std::is_same<OpaquePropertyListGetPropertyAlt20, SlotSignature>::value,
      "the +0x20 slot repeats the entry signature");
  static_assert(
      std::is_same<decltype(&list_operation_20), SlotSignature>::value,
      "the model test fake matches the +0x20 slot");
  static_assert(std::is_same<OpaquePropertyListHasProperty1c,
                             HasPropertySlotSignature>::value,
                "the +0x1c slot takes only the receiver and the id word");
  static_assert(sizeof(decltype(&property_list_get_property_alt_006a1de0)) == 4,
                "entry point width");
  static_assert(offsetof(OpaquePropertyListVtable, operation_20) == 0x20,
                "entry word sits at displacement 0x20 of 0x01408820");
  static_assert(sizeof(OpaquePropertyEntry) == 0x18, "entry stride");
}

}

int run_model() {
  failures = 0;
  test_lower_bound_port_receives_span_key_and_mode();
  test_hit_path_stores_entry_property_slot_address();
  test_lower_bound_end_pointer_is_a_miss();
  test_key_below_entry_key_is_a_miss();
  test_key_above_entry_key_is_still_a_hit();
  test_zero_key_matches_zero_entry_key();
  test_miss_without_parent_returns_false_and_keeps_out_pointer();
  test_miss_forwards_the_parent_slot_return_value();
  test_ports_are_null_by_default();
  test_modeled_signatures();
  return failures == 0 ? 0 : 1;
}

}

int main() {
  return openspore::reconstruction::pkg_orchestrate_dogfood_006a1de0::
      run_model();
}

#undef PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL
