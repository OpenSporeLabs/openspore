#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "sporepedia_access.hpp"

struct Pkg16EditableVtable {
  Pkg16EditableSlot slots[25];
};

struct Pkg16AssetData {
  Pkg16EditableVtable* vtable;
  std::uint32_t opaque[11];
};

static_assert(sizeof(void*) == 4, "PKG-16 requires 32-bit pointers");
static_assert(sizeof(Pkg16EditableSlot) == 4, "PKG-16 requires 32-bit slots");
static_assert(offsetof(Pkg16AssetData, vtable) == 0, "vtable moved");
static_assert(sizeof(Pkg16AssetData) >= 0x2c,
              "field +0x28 must be addressable");
static_assert(sizeof(std::uint64_t) == 8, "PKG-16 destination must be 64-bit");

static std::uint8_t expected_editable_result = 0;
static Pkg16AssetData* expected_receiver = nullptr;

static std::uint8_t __thiscall editable_slot_60(Pkg16AssetData* self) {
  assert(self == expected_receiver);
  return expected_editable_result;
}

enum class Pkg16InvalidAccess : std::uint8_t {
  editable_null,
  editable_empty,
  editable_invalid,
  has_name_null,
  has_name_invalid,
};

[[noreturn]] static void run_invalid_access(Pkg16InvalidAccess access) {
  Pkg16AssetData empty{};
  Pkg16AssetData* self = &empty;
  if (access == Pkg16InvalidAccess::editable_null ||
      access == Pkg16InvalidAccess::has_name_null) {
    self = nullptr;
  } else if (access == Pkg16InvalidAccess::editable_invalid ||
             access == Pkg16InvalidAccess::has_name_invalid) {
    self = reinterpret_cast<Pkg16AssetData*>(std::uintptr_t{1});
  }
  volatile std::uint32_t result =
      access == Pkg16InvalidAccess::has_name_null ||
              access == Pkg16InvalidAccess::has_name_invalid
          ? sporepedia_has_name_00641770(self)
          : sporepedia_is_editable_00641400(self);
  _exit(result ? 2 : 3);
}

static void expect_segmentation_fault(Pkg16InvalidAccess access) {
  const pid_t child = fork();
  assert(child >= 0);
  if (child == 0) {
    run_invalid_access(access);
  }
  int status = 0;
  assert(waitpid(child, &status, 0) == child);
  assert(WIFSIGNALED(status));
  assert(WTERMSIG(status) == SIGSEGV);
}

static Pkg16MetadataWord to_metadata_word(Pkg16AssetData* metadata) {
  return static_cast<Pkg16MetadataWord>(
      reinterpret_cast<std::uintptr_t>(metadata));
}

static void store_field_28(Pkg16AssetData& self, Pkg16MetadataWord value) {
  std::memcpy(reinterpret_cast<unsigned char*>(&self) + 0x28, &value,
              sizeof(value));
}

static float call_staged_get_asset_id_006417c0(Pkg16AssetData* self,
                                               std::uint64_t* destination) {
  float result = 0.0F;
  __asm__ volatile(
      "movl %1, %%ecx\n\t"
      "pushl %2\n\t"
      "call sporepedia_get_asset_id_006417c0\n\t"
      "addl $4, %%esp\n\t"
      "fsts %0\n\t"
      : "=m"(result)
      : "r"(self), "r"(destination)
      : "eax", "edx", "ecx", "memory", "st");
  return result;
}

static void run() {
  std::array<Pkg16EditableSlot, 25> slots{};
  slots[24] = editable_slot_60;
  Pkg16EditableVtable vtable{};
  std::memcpy(vtable.slots, slots.data(), sizeof(vtable.slots));
  Pkg16AssetData data{};
  data.vtable = &vtable;
  expected_receiver = &data;

  expected_editable_result = 0;
  assert(sporepedia_is_editable_00641400(&data) == 0);
  expected_editable_result = 1;
  assert(sporepedia_is_editable_00641400(&data) == 1);

  Pkg16AssetData metadata{};
  Pkg16AssetData other_metadata{};
  const Pkg16MetadataWord metadata_word = to_metadata_word(&metadata);
  const Pkg16MetadataWord other_metadata_word =
      to_metadata_word(&other_metadata);
  assert(metadata_word != other_metadata_word);
  store_field_28(data, metadata_word);
  assert(sporepedia_has_name_00641770(&data) == metadata_word);
  assert(reinterpret_cast<Pkg16AssetData*>(static_cast<std::uintptr_t>(
             sporepedia_has_name_00641770(&data))) == &metadata);
  store_field_28(data, other_metadata_word);
  assert(sporepedia_has_name_00641770(&data) == other_metadata_word);
  assert(reinterpret_cast<Pkg16AssetData*>(static_cast<std::uintptr_t>(
             sporepedia_has_name_00641770(&data))) == &other_metadata);
  store_field_28(data, 0u);
  assert(sporepedia_has_name_00641770(&data) == 0);
  store_field_28(data, UINT32_MAX);
  assert(sporepedia_has_name_00641770(&data) == UINT32_MAX);

  std::uint64_t destination = UINT64_C(0x0123456789abcdef);
  const float observed = call_staged_get_asset_id_006417c0(&data, &destination);
  assert(observed == -1.0F);
  assert(destination == UINT64_C(0x0123456789abcdef));
  assert(call_staged_get_asset_id_006417c0(nullptr, &destination) == -1.0F);
  assert(destination == UINT64_C(0x0123456789abcdef));
  assert(call_staged_get_asset_id_006417c0(&data, nullptr) == -1.0F);
  assert(call_staged_get_asset_id_006417c0(nullptr, nullptr) == -1.0F);

  Pkg16AssetData empty{};
  assert(call_staged_get_asset_id_006417c0(&empty, nullptr) == -1.0F);
  auto* invalid = reinterpret_cast<Pkg16AssetData*>(std::uintptr_t{1});
  assert(call_staged_get_asset_id_006417c0(invalid, nullptr) == -1.0F);

  expect_segmentation_fault(Pkg16InvalidAccess::editable_null);
  expect_segmentation_fault(Pkg16InvalidAccess::editable_empty);
  expect_segmentation_fault(Pkg16InvalidAccess::editable_invalid);
  expect_segmentation_fault(Pkg16InvalidAccess::has_name_null);
  expect_segmentation_fault(Pkg16InvalidAccess::has_name_invalid);
}

int main() { run(); }
