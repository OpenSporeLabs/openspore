#include "sporepedia_access.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace openspore::reconstruction::pkg16_sporepedia {

struct EditableVtable {
  EditableSlot slots[25];
};

struct AssetData {
  EditableVtable *vtable;
  std::uint32_t opaque[11];
};

static_assert(sizeof(void *) == 4, "PKG-16 requires 32-bit pointers");
static_assert(sizeof(EditableSlot) == 4, "PKG-16 requires 32-bit slots");
static_assert(offsetof(AssetData, vtable) == 0, "vtable moved");
static_assert(sizeof(AssetData) >= 0x2c, "field +0x28 must be addressable");
static_assert(sizeof(std::uint64_t) == 8, "PKG-16 destination must be 64-bit");

namespace {

bool expected_editable_result = false;
AssetData *expected_receiver = nullptr;

bool __thiscall editable_slot_60(AssetData *self) {
  assert(self == expected_receiver);
  return expected_editable_result;
}

enum class InvalidAccess : std::uint8_t {
  editable_null,
  editable_empty,
  editable_invalid,
  has_name_null,
  has_name_invalid,
};

[[noreturn]] void run_invalid_access(InvalidAccess access) {
  AssetData empty{};
  AssetData *self = &empty;
  if (access == InvalidAccess::editable_null ||
      access == InvalidAccess::has_name_null) {
    self = nullptr;
  } else if (access == InvalidAccess::editable_invalid ||
             access == InvalidAccess::has_name_invalid) {
    self = reinterpret_cast<AssetData *>(std::uintptr_t{1});
  }
  volatile bool result = access == InvalidAccess::has_name_null ||
                             access == InvalidAccess::has_name_invalid
                         ? sporepedia_has_name_00641770(self)
                         : sporepedia_is_editable_00641400(self);
  _exit(result ? 2 : 3);
}

void expect_segmentation_fault(InvalidAccess access) {
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

void store_field_28(AssetData &self, std::uint32_t value) {
  std::memcpy(reinterpret_cast<unsigned char *>(&self) + 0x28, &value,
              sizeof(value));
}

void run() {
  std::array<EditableSlot, 25> slots{};
  slots[24] = editable_slot_60;
  EditableVtable vtable{};
  std::memcpy(vtable.slots, slots.data(), sizeof(vtable.slots));
  AssetData data{};
  data.vtable = &vtable;
  expected_receiver = &data;

  expected_editable_result = false;
  assert(!sporepedia_is_editable_00641400(&data));
  expected_editable_result = true;
  assert(sporepedia_is_editable_00641400(&data));

  store_field_28(data, 0u);
  assert(!sporepedia_has_name_00641770(&data));
  store_field_28(data, 1u);
  assert(sporepedia_has_name_00641770(&data));
  store_field_28(data, 0x100u);
  assert(!sporepedia_has_name_00641770(&data));
  store_field_28(data, UINT32_MAX);
  assert(sporepedia_has_name_00641770(&data));

  std::uint64_t destination = UINT64_C(0x0123456789abcdef);
  const float observed = sporepedia_get_asset_id_006417c0(&data, &destination);
  std::fprintf(stderr, "%a\n", static_cast<double>(observed));
  assert(observed == -1.0F);
  assert(destination == UINT64_C(0x0123456789abcdef));
  assert(sporepedia_get_asset_id_006417c0(nullptr, &destination) == -1.0F);
  assert(destination == UINT64_C(0x0123456789abcdef));
  assert(sporepedia_get_asset_id_006417c0(&data, nullptr) == -1.0F);
  assert(sporepedia_get_asset_id_006417c0(nullptr, nullptr) == -1.0F);

  AssetData empty{};
  assert(sporepedia_get_asset_id_006417c0(&empty, nullptr) == -1.0F);

  expect_segmentation_fault(InvalidAccess::editable_null);
  expect_segmentation_fault(InvalidAccess::editable_empty);
  expect_segmentation_fault(InvalidAccess::editable_invalid);
  expect_segmentation_fault(InvalidAccess::has_name_null);
  expect_segmentation_fault(InvalidAccess::has_name_invalid);
}

}

}

int main() {
  openspore::reconstruction::pkg16_sporepedia::run();
}
