#include <sys/mman.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

#include "root_accessors.hpp"

namespace openspore::reconstruction::pkg11_h2_root_accessors {

constexpr std::uintptr_t kSlotPageAddress = 0x0167e000U;
constexpr std::size_t kPageSize = 4096U;
constexpr std::array<std::uintptr_t, 4> kSlotOffsets = {0x0b10U, 0x0b24U,
                                                        0x0b5cU, 0x0b30U};

using Slot = volatile RootWord*;
using Slots = std::array<Slot, 4>;

static_assert(sizeof(std::uintptr_t) == 4,
              "absolute slots require 32-bit pointers");
static_assert(std::is_same_v<decltype(&root_accessor_00b3d3b0), RootAccessor>);
static_assert(std::is_same_v<decltype(&root_accessor_00b3d3e0), RootAccessor>);
static_assert(std::is_same_v<decltype(&root_accessor_00b3d3f0), RootAccessor>);
static_assert(std::is_same_v<decltype(&root_accessor_00b3d430), RootAccessor>);

Slots mapped_slots() {
  return {reinterpret_cast<Slot>(kSlotPageAddress + kSlotOffsets[0]),
          reinterpret_cast<Slot>(kSlotPageAddress + kSlotOffsets[1]),
          reinterpret_cast<Slot>(kSlotPageAddress + kSlotOffsets[2]),
          reinterpret_cast<Slot>(kSlotPageAddress + kSlotOffsets[3])};
}

std::array<RootWord, 4> read_slots(const Slots& slots) {
  return {slots[0][0], slots[1][0], slots[2][0], slots[3][0]};
}

void test_raw_word_propagation(const Slots& slots) {
  constexpr std::array<RootWord, 4> values = {0U, 0xffffffffU, 0x13579bdfU,
                                              0x2468ace0U};
  const std::array<RootAccessor, 4> accessors = {
      &root_accessor_00b3d3b0, &root_accessor_00b3d3e0, &root_accessor_00b3d3f0,
      &root_accessor_00b3d430};

  for (std::size_t index = 0; index < slots.size(); ++index) {
    slots[index][0] = values[index];
    assert(accessors[index]() == values[index]);
  }
  assert(read_slots(slots) == values);
}

void test_null_and_sentinel_words(const Slots& slots) {
  const std::array<RootAccessor, 4> accessors = {
      &root_accessor_00b3d3b0, &root_accessor_00b3d3e0, &root_accessor_00b3d3f0,
      &root_accessor_00b3d430};

  for (std::size_t index = 0; index < slots.size(); ++index) {
    slots[index][0] = 0U;
    assert(accessors[index]() == 0U);
    assert(slots[index][0] == 0U);
    slots[index][0] = 0xffffffffU;
    assert(accessors[index]() == 0xffffffffU);
    assert(slots[index][0] == 0xffffffffU);
  }
}

void test_no_mutation(const Slots& slots) {
  constexpr std::array<RootWord, 4> values = {0U, 0xffffffffU, 0x13579bdfU,
                                              0x2468ace0U};
  const std::array<RootAccessor, 4> accessors = {
      &root_accessor_00b3d3b0, &root_accessor_00b3d3e0, &root_accessor_00b3d3f0,
      &root_accessor_00b3d430};

  for (std::size_t index = 0; index < slots.size(); ++index) {
    slots[index][0] = values[index];
  }
  const auto before = read_slots(slots);
  for (std::size_t index = 0; index < slots.size(); ++index) {
    assert(accessors[index]() == before[index]);
  }
  assert(read_slots(slots) == before);
}

void test_call_and_identity_boundaries(const Slots& slots) {
  constexpr std::array<RootWord, 4> values = {0x10203040U, 0x50607080U,
                                              0x90a0b0c0U, 0xd0e0f001U};
  const std::array<RootAccessor, 4> accessors = {
      &root_accessor_00b3d3b0, &root_accessor_00b3d3e0, &root_accessor_00b3d3f0,
      &root_accessor_00b3d430};

  for (std::size_t index = 0; index < slots.size(); ++index) {
    slots[index][0] = values[index];
  }
  for (std::size_t index = 0; index < accessors.size(); ++index) {
    assert(accessors[index]() == values[index]);
    for (std::size_t other = 0; other < accessors.size(); ++other) {
      if (other != index) {
        assert(accessors[other]() != values[index]);
      }
    }
  }
}

}

int main() {
  void* expected_page = reinterpret_cast<void*>(
      openspore::reconstruction::pkg11_h2_root_accessors::kSlotPageAddress);
  void* mapping = mmap(
      expected_page,
      openspore::reconstruction::pkg11_h2_root_accessors::kPageSize,
      PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
  assert(mapping == expected_page);
  std::memset(mapping, 0,
              openspore::reconstruction::pkg11_h2_root_accessors::kPageSize);

  const auto slots =
      openspore::reconstruction::pkg11_h2_root_accessors::mapped_slots();
  openspore::reconstruction::pkg11_h2_root_accessors::test_raw_word_propagation(
      slots);
  openspore::reconstruction::pkg11_h2_root_accessors::
      test_null_and_sentinel_words(slots);
  openspore::reconstruction::pkg11_h2_root_accessors::test_no_mutation(slots);
  openspore::reconstruction::pkg11_h2_root_accessors::
      test_call_and_identity_boundaries(slots);
  assert(
      munmap(mapping,
             openspore::reconstruction::pkg11_h2_root_accessors::kPageSize) ==
      0);
}
