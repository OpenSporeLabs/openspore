// Model test for 0x006a2a80 (App::PropertyList::Clear).
//
// Three claims are checked, all of them observable from the disassembly.
//
// 1. Span arithmetic: the multiply/shift block at 0x006a2a8f..0x006a2ac3 is
//    reproduced bit for bit and asserted to return -(last - first) for spans of
//    0, 1, 2, ... 8 entries, which is what makes the ADD at 0x006a2ac3 rewind
//    `last` to `first`. The delta is asserted, not the "cleared" property, so
//    the test fails if the magic constant is wrong.
//
// 2. Element release: the flags gate (entry+0x14 bit 0x04, i.e. property+0x10
//    bit 0x04) and the 0x18 stride are asserted by driving the ported
//    0x00685a30 over a mixed-flag range and counting the resets.
//
// 3. End state: `last` lands on `first` for a populated list, is untouched for
//    an empty one, and operations_done advances by exactly one. The
//    copy_entry_range port is asserted to be called with first == last, i.e.
//    the range the original passes is empty.

#include "property_clear_wave12.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <vector>

namespace {

using openspore::reconstruction::pkg_property_clear_wave12::
    ClearSpanDelta_006a2a80;
using openspore::reconstruction::pkg_property_clear_wave12::OpaqueProperty;
using openspore::reconstruction::pkg_property_clear_wave12::OpaquePropertyEntry;
using openspore::reconstruction::pkg_property_clear_wave12::OpaquePropertyMap;
using openspore::reconstruction::pkg_property_clear_wave12::OpaquePropertyList;
using openspore::reconstruction::pkg_property_clear_wave12::PropertyClearPorts;
using openspore::reconstruction::pkg_property_clear_wave12::ReleaseEntryRange_00685a30;
using openspore::reconstruction::pkg_property_clear_wave12::
    App__PropertyList__Clear_006a2a80_impl;

int failures = 0;

void expect(bool condition, const char* what) {
  if (!condition) {
    ++failures;
    std::printf("FAIL %s\n", what);
  }
}

int reset_calls = 0;
int copy_calls = 0;
bool copy_saw_empty_range = false;
OpaquePropertyEntry* copy_first_arg = nullptr;
OpaquePropertyEntry* copy_last_arg = nullptr;
OpaquePropertyEntry* copy_out_arg = nullptr;
OpaquePropertyMap* release_self = nullptr;
OpaquePropertyEntry* release_first = nullptr;
OpaquePropertyEntry* release_last = nullptr;

void ResetPort(OpaqueProperty* property, std::uint8_t clear_value) {
  ++reset_calls;
  if (clear_value == 0) {
    property->flags = 0;
    property->type = 0;
  }
}

OpaquePropertyEntry* CopyPort(OpaquePropertyEntry* first,
                              OpaquePropertyEntry* last,
                              OpaquePropertyEntry* out) {
  ++copy_calls;
  copy_first_arg = first;
  copy_last_arg = last;
  copy_out_arg = out;
  if (first == last) {
    copy_saw_empty_range = true;
    return out;
  }
  OpaquePropertyEntry* dst = out;
  for (OpaquePropertyEntry* src = first; src != last; ++src, dst += 1) {
    *dst = *src;
  }
  return dst;
}

void ReleasePort(OpaquePropertyMap* self, OpaquePropertyEntry* first,
                 OpaquePropertyEntry* last) {
  release_self = self;
  release_first = first;
  release_last = last;
  ReleaseEntryRange_00685a30(self, first, last, ResetPort);
}

const PropertyClearPorts kPorts = {CopyPort, ReleasePort, ResetPort};

void ResetProbes() {
  reset_calls = 0;
  copy_calls = 0;
  copy_saw_empty_range = false;
  copy_first_arg = nullptr;
  copy_last_arg = nullptr;
  copy_out_arg = nullptr;
  release_self = nullptr;
  release_first = nullptr;
  release_last = nullptr;
}

}  // namespace

int main() {
  // 1. Span arithmetic. 0x006a2a80: ADD [esi+4],edx must rewind last to first.
  for (int count = 0; count <= 8; ++count) {
    const std::int32_t span = 0x18 * count;
    expect(ClearSpanDelta_006a2a80(span) == -span,
           "ClearSpanDelta_006a2a80 returns -span for a well-formed span");
  }

  // 2. Element release: only entries whose flags carry bit 0x04 are reset, and
  //    the walk uses the 0x18 stride.
  std::vector<OpaquePropertyEntry> entries(4);
  entries[0].property.flags = 0x0000;
  entries[1].property.flags = 0x0004;
  entries[2].property.flags = 0x0001;
  entries[3].property.flags = 0x0007;
  reset_calls = 0;
  ReleaseEntryRange_00685a30(nullptr, entries.data(),
                             entries.data() + entries.size(), ResetPort);
  expect(reset_calls == 2, "release resets exactly the bit-0x04 entries");

  // 3. End state on a populated list.
  std::vector<OpaquePropertyEntry> live(3);
  for (std::size_t i = 0; i < live.size(); ++i) {
    live[i].id = static_cast<std::uint32_t>(i);
    live[i].property.flags = 0x0004;
  }
  OpaquePropertyList list;
  list.vtable = nullptr;
  list.ref_count = 1;
  list.properties.first = live.data();
  list.properties.last = live.data() + live.size();
  list.properties.capacity = live.data() + live.size();
  list.operations_done = 41;

  ResetProbes();
  App__PropertyList__Clear_006a2a80_impl(&list, kPorts);

  expect(copy_calls == 1, "copy port called once");
  expect(copy_saw_empty_range, "copy port receives an empty range");
  expect(copy_first_arg == copy_last_arg,
         "copy port first and last arguments are equal");
  expect(copy_out_arg == live.data(), "copy port out argument is properties.first");
  expect(release_self == &list.properties, "release port this is list+0x18");
  expect(release_first == live.data(), "release port first is properties.first");
  expect(release_last == live.data() + 3,
         "release port last is the pre-clear properties.last");
  expect(reset_calls == 3, "every flagged entry is reset");
  expect(list.properties.last == list.properties.first,
         "properties.last is rewound to properties.first");
  expect(list.operations_done == 42, "operations_done advances by one");

  // Empty list: every observable is a no-op, including the counter staying at
  // first (the INC is unconditional, so the counter still advances).
  OpaquePropertyEntry storage;
  storage.id = 0;
  storage.property.flags = 0x0004;
  OpaquePropertyList empty;
  empty.vtable = nullptr;
  empty.ref_count = 1;
  empty.properties.first = &storage;
  empty.properties.last = &storage;
  empty.properties.capacity = &storage;
  empty.operations_done = 7;

  ResetProbes();
  App__PropertyList__Clear_006a2a80_impl(&empty, kPorts);
  expect(reset_calls == 0, "empty list resets nothing");
  expect(empty.properties.last == empty.properties.first,
         "empty list leaves properties.last at properties.first");
  expect(empty.operations_done == 8,
         "empty list still advances operations_done once");

  if (failures != 0) {
    std::printf("%d check(s) failed\n", failures);
    return 1;
  }
  std::printf("ok\n");
  return 0;
}
