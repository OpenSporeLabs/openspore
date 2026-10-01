#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "property_set_006a2e20.hpp"

#if defined(_MSC_VER)
#define PKG15_TEST_THISCALL __thiscall
#else
#define PKG15_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_proplist_setprop_w15 {
namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

MapEntry* last_error_receiver = nullptr;
TargetWord error_arguments[8];
std::size_t error_calls = 0;

std::size_t insert_calls = 0;
TargetWord insert_key = 0;
bool last_lookup_inserted = false;

Property source_value{};

Property* PKG15_TEST_THISCALL assign_property(Property* destination,
                                             Property* source) {
  // Mirrors 0x00542b80 exactly on the fast path: four dwords copied, the type
  // word taken from the source, and the flags recomposed as
  // (source.flags & ~0x0002) | (destination.flags & 0x0002).
  if ((source->field_10 & 0x0008u) == 0 &&
      ((destination->field_10 & 0x0002u) == 0 ||
       destination->field_12 == source->field_12)) {
    std::memcpy(destination->field_00_0f.data(), source->field_00_0f.data(),
                destination->field_00_0f.size());
    destination->field_12 = source->field_12;
    destination->field_10 = static_cast<std::uint16_t>(
        (source->field_10 & 0xfffdu) | (destination->field_10 & 0x0002u));
  } else {
    destination->field_10 = source->field_10;
    destination->field_12 = source->field_12;
  }
  return destination;
}

void PKG15_TEST_THISCALL seed_error_port_model(MapEntry* receiver,
                                               TargetWord argument) {
  // 0x0093db80 with argument 0 returns after its own `TEST byte [ESI+0x10],4`,
  // so the model records the receiver and the argument and changes nothing.
  last_error_receiver = receiver;
  error_arguments[error_calls] = argument;
  ++error_calls;
}

MapLookup* PKG15_TEST_THISCALL find_or_insert_model(PropertyMap* map,
                                                    MapLookup* out,
                                                    MapEntry* seed) {
  ++insert_calls;
  insert_key = seed->field_00;
  MapEntry* slot = property_map_lower_bound(*map, seed->field_00);
  if (slot != map->field_04 && !(seed->field_00 < slot->field_00)) {
    out->field_00 = slot;
    out->field_04 = 0;
    last_lookup_inserted = false;
    return out;
  }
  // 0x006a2940: splice a fresh slot in at the sorted position, write the key at
  // slot+0, clear the new entry's words at +0x14 and +0x16, then assign the
  // seed's +4 Property into slot+4.
  MapEntry* end = map->field_04;
  for (MapEntry* cursor = end; cursor > slot; --cursor) {
    cursor[0] = cursor[-1];
  }
  slot->field_00 = seed->field_00;
  slot->field_04.field_10 = 0;
  slot->field_04.field_12 = 0;
  assign_property(&slot->field_04, &seed->field_04);
  map->field_04 = end + 1;
  out->field_00 = slot;
  out->field_04 = 1;
  last_lookup_inserted = true;
  return out;
}

void reset_list(PropertyList& list, MapEntry* begin, MapEntry* end) {
  std::memset(&list, 0, sizeof(list));
  list.field_18.field_00 = begin;
  list.field_18.field_04 = end;
}

void make_source(TargetWord payload, std::uint16_t type, std::uint16_t flags) {
  std::memset(&source_value, 0, sizeof(source_value));
  std::memcpy(source_value.field_00_0f.data(), &payload, sizeof(payload));
  source_value.field_10 = flags;
  source_value.field_12 = type;
}

void test_abi_and_layout() {
  static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
  static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
  static_assert(sizeof(Property) == 0x14, "property size from 0x00542b80");
  static_assert(offsetof(Property, field_10) == 0x10, "flags word offset");
  static_assert(offsetof(Property, field_12) == 0x12, "type word offset");
  static_assert(sizeof(MapEntry) == 0x18, "map entry stride from 0x00612db0");
  static_assert(offsetof(MapEntry, field_04) == 0x04, "entry property offset");
  static_assert(offsetof(MapEntry, field_04) + sizeof(Property) == 0x18,
                "the key plus the property fill the stride exactly");
  static_assert(sizeof(PropertyMap) == 0x18, "property map size");
  static_assert(offsetof(PropertyMap, field_04) == 0x04, "map end offset");
  static_assert(offsetof(PropertyMap, field_14) == 0x14, "map mode offset");
  // Offsets the 0x006a2e20 body itself reads.
  static_assert(offsetof(PropertyList, field_18) == 0x18, "map base offset");
  static_assert(offsetof(PropertyList, field_34) == 0x34, "counter offset");
  // The mode byte the body loads with `MOVZX ECX, byte ptr [EDI + 0x2c]` is
  // PropertyMap::field_14 reached through the map that starts at +0x18.
  check(offsetof(PropertyList, field_18) + offsetof(PropertyMap, field_14) ==
        0x2c);
}

void test_existing_entry_assigns_in_place() {
  PropertyList list{};
  MapEntry entries[3]{};
  reset_list(list, entries, entries + 2);
  entries[0].field_00 = 10;
  entries[1].field_00 = 20;
  list.field_34 = 5;

  insert_calls = 0;
  error_calls = 0;
  make_source(0x1234u, 9u, 0u);

  property_set_006a2e20(&list, 20u, &source_value);

  check(insert_calls == 0);
  check(error_calls == 0);
  check(list.field_18.field_04 == entries + 2);
  check(entries[1].field_04.field_12 == 9u);
  TargetWord stored = 0;
  std::memcpy(&stored, entries[1].field_04.field_00_0f.data(), sizeof(stored));
  check(stored == 0x1234u);
  check(list.field_34 == 6);
}

void test_missing_entry_inserts_in_sorted_position() {
  PropertyList list{};
  MapEntry entries[4]{};
  reset_list(list, entries, entries + 2);
  entries[0].field_00 = 10;
  entries[1].field_00 = 30;
  list.field_34 = 0;

  insert_calls = 0;
  error_calls = 0;
  make_source(0x5678u, 1u, 0u);

  property_set_006a2e20(&list, 20u, &source_value);

  check(insert_calls == 1);
  check(insert_key == 20u);
  check(last_lookup_inserted);
  check(error_calls == 0);
  check(list.field_18.field_04 == entries + 3);
  check(entries[0].field_00 == 10u);
  check(entries[1].field_00 == 20u);
  check(entries[2].field_00 == 30u);
  check(entries[1].field_04.field_12 == 1u);
  check(list.field_34 == 1);
}

void test_empty_map_creates_first_entry() {
  PropertyList list{};
  MapEntry entries[2]{};
  reset_list(list, entries, entries);
  list.field_34 = 0;

  insert_calls = 0;
  error_calls = 0;
  make_source(7u, 1u, 0u);

  property_set_006a2e20(&list, 3u, &source_value);

  check(insert_calls == 1);
  check(list.field_18.field_04 == entries + 1);
  check(entries[0].field_00 == 3u);
  check(entries[0].field_04.field_12 == 1u);
  check(list.field_34 == 1);
}

void test_read_only_source_reports_through_error_port() {
  PropertyList list{};
  MapEntry entries[2]{};
  reset_list(list, entries, entries);
  list.field_34 = 0;

  insert_calls = 0;
  error_calls = 0;
  // Bit 0x0004 in the source flags survives the assign into the seed, so the
  // post-insert test fires and the reporter is called with argument 0.
  make_source(1u, 1u, 0x0004u);

  property_set_006a2e20(&list, 5u, &source_value);

  check(insert_calls == 1);
  check(error_calls == 1);
  check(error_arguments[0] == 0u);
  // 0x006a2ec8 hands the reporter the seed entry, not the seed Property.
  check(last_error_receiver != nullptr);
  check(last_error_receiver->field_00 == 5u);
  // The insert still happened and the counter still moved once.
  check(list.field_18.field_04 == entries + 1);
  check((entries[0].field_04.field_10 & 0x0004u) != 0);
  check(list.field_34 == 1);
}

void test_writable_source_does_not_report() {
  // Bit 0x0002 is what 0x00542b80 preserves from the destination and what
  // 0x0093db80 tests before clearing, so a source carrying it is not
  // read-only and the post-insert test must stay quiet.
  PropertyList list{};
  MapEntry entries[2]{};
  reset_list(list, entries, entries);

  insert_calls = 0;
  error_calls = 0;
  make_source(2u, 1u, 0x0002u);

  property_set_006a2e20(&list, 6u, &source_value);

  check(insert_calls == 1);
  check(error_calls == 0);
  check(list.field_18.field_04 == entries + 1);
}

void test_counter_increments_exactly_once_per_call() {
  PropertyList list{};
  MapEntry entries[3]{};
  reset_list(list, entries, entries + 1);
  entries[0].field_00 = 1;
  list.field_34 = 0;

  make_source(1u, 1u, 0u);
  for (int index = 0; index < 5; ++index) {
    property_set_006a2e20(&list, 1u, &source_value);
  }
  check(list.field_34 == 5);

  for (int index = 0; index < 3; ++index) {
    property_set_006a2e20(&list, 2u, &source_value);
  }
  check(list.field_34 == 8);
}

void test_lower_bound_semantics() {
  MapEntry entries[5]{};
  PropertyMap map{};
  map.field_00 = entries;
  map.field_04 = entries + 5;
  entries[0].field_00 = 2;
  entries[1].field_00 = 4;
  entries[2].field_00 = 6;
  entries[3].field_00 = 8;
  entries[4].field_00 = 10;

  check(property_map_lower_bound(map, 1) == entries + 0);
  check(property_map_lower_bound(map, 2) == entries + 0);
  check(property_map_lower_bound(map, 3) == entries + 1);
  check(property_map_lower_bound(map, 5) == entries + 2);
  check(property_map_lower_bound(map, 6) == entries + 2);
  check(property_map_lower_bound(map, 7) == entries + 3);
  check(property_map_lower_bound(map, 11) == entries + 5);
}

}  // namespace

}  // namespace openspore::reconstruction::pkg_proplist_setprop_w15

int main() {
  using namespace openspore::reconstruction::pkg_proplist_setprop_w15;

  set_property_assign(assign_property);
  set_seed_error_port(seed_error_port_model);
  set_map_find_or_insert(find_or_insert_model);

  test_abi_and_layout();
  test_existing_entry_assigns_in_place();
  test_missing_entry_inserts_in_sorted_position();
  test_empty_map_creates_first_entry();
  test_read_only_source_reports_through_error_port();
  test_writable_source_does_not_report();
  test_counter_increments_exactly_once_per_call();
  test_lower_bound_semantics();
  return 0;
}
