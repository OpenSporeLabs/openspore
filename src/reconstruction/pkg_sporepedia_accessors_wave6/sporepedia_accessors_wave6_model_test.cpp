#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <initializer_list>

#include "sporepedia_accessors_wave6.hpp"

struct Pkg16AssetData {
  std::uint8_t bytes[0x2c];
};

struct Pkg16AssetMetadata {
  std::uint32_t words[64];
};

struct Pkg16WideString {
  std::uint32_t begin;
  std::uint32_t end;
  std::uint32_t capacity;
  std::uint32_t allocator;
};

namespace {

static_assert(sizeof(void*) == 4, "x86-32 pointers are required");
static_assert(sizeof(Pkg16AssetData) >= 0x2c, "asset prefix is too small");
static_assert(sizeof(Pkg16AssetMetadata) >= 0xb0,
              "metadata prefix is too small");
static_assert(offsetof(Pkg16WideString, begin) == 0, "string layout moved");
static_assert(offsetof(Pkg16WideString, end) == 4, "string layout moved");
static_assert(offsetof(Pkg16WideString, capacity) == 8, "string layout moved");

std::uint32_t read_word(const void* address) {
  std::uint32_t value = 0;
  std::memcpy(&value, address, sizeof(value));
  return value;
}

void write_word(void* address, std::uint32_t value) {
  std::memcpy(address, &value, sizeof(value));
}

std::uint32_t asset_word(Pkg16AssetData& asset, std::size_t offset) {
  return read_word(asset.bytes + offset);
}

void store_asset_word(Pkg16AssetData& asset, std::size_t offset,
                      std::uint32_t value) {
  write_word(asset.bytes + offset, value);
}

std::uint32_t metadata_word(Pkg16AssetMetadata& metadata, std::size_t offset) {
  return read_word(metadata.words + offset / 4U);
}

void store_metadata_word(Pkg16AssetMetadata& metadata, std::size_t offset,
                         std::uint32_t value) {
  write_word(reinterpret_cast<unsigned char*>(metadata.words) + offset, value);
}

struct RawQword {
  std::uint32_t low;
  std::uint32_t high;
};

RawQword call_author_id(Pkg16AssetData* self, std::uint32_t high_seed) {
  RawQword result{};
  __asm__ volatile(
      "movl %3, %%edx\n\t"
      "movl %2, %%ecx\n\t"
      "call sporepedia_get_author_id_00641820\n\t"
      "movl %%eax, %0\n\t"
      "movl %%edx, %1\n\t"
      : "=m"(result.low), "=m"(result.high)
      : "m"(self), "m"(high_seed)
      : "eax", "edx", "ecx", "memory");
  return result;
}

std::uint32_t call_func7ch(Pkg16AssetData* self, std::uint32_t eax_seed) {
  std::uint32_t result = 0;
  __asm__ volatile(
      "movl %2, %%eax\n\t"
      "movl %1, %%ecx\n\t"
      "call sporepedia_func7ch_00641460\n\t"
      "movl %%eax, %0\n\t"
      : "=m"(result)
      : "m"(self), "m"(eax_seed)
      : "eax", "ecx", "memory");
  return result;
}

void call_time(Pkg16AssetData* self, Pkg16WideString* output) {
  __asm__ volatile(
      "movl %0, %%ecx\n\t"
      "pushl %1\n\t"
      "call sporepedia_get_time_created_00641860\n\t"
      :
      : "m"(self), "m"(output)
      : "eax", "edx", "ecx", "memory");
}

Pkg16AssetData asset;
Pkg16AssetMetadata metadata;
Pkg16WideString author_name{};
Pkg16WideString tags{};
Pkg16WideString destination{};
Pkg16WideString* observed_time_destination = nullptr;
unsigned time_helper_calls = 0;

}

extern "C" __thiscall Pkg16WideString* pkg16_author_name_00414e10(
    Pkg16AssetMetadata* value) {
  assert(value == &metadata);
  return reinterpret_cast<Pkg16WideString*>(
      static_cast<std::uintptr_t>(metadata_word(*value, 0x78)));
}

extern "C" __thiscall std::uint32_t pkg16_author_id_00550880(
    Pkg16AssetMetadata* value) {
  assert(value == &metadata);
  return metadata_word(*value, 0x58);
}

extern "C" __thiscall Pkg16WideString* pkg16_tags_005508c0(
    Pkg16AssetMetadata* value) {
  assert(value == &metadata);
  return reinterpret_cast<Pkg16WideString*>(
      static_cast<std::uintptr_t>(metadata_word(*value, 0x88)));
}

extern "C" __thiscall void pkg16_time_helper_00550cf0(Pkg16AssetMetadata* value,
                                                      Pkg16WideString* output) {
  assert(value == &metadata);
  ++time_helper_calls;
  observed_time_destination = output;
  if (output == nullptr) {
    assert(metadata_word(*value, 0xac) == metadata_word(*value, 0xb0));
  }
}

namespace {

void reset() {
  std::memset(&asset, 0, sizeof(asset));
  std::memset(&metadata, 0, sizeof(metadata));
  std::memset(&author_name, 0, sizeof(author_name));
  std::memset(&tags, 0, sizeof(tags));
  std::memset(&destination, 0, sizeof(destination));
  observed_time_destination = nullptr;
  time_helper_calls = 0;
}

void test_byte_accessor() {
  reset();
  for (const std::uint32_t value : {0U, 1U, 0x7fU, 0xffU, 0x1234U}) {
    store_asset_word(asset, 0x24, 0xa5a50000U | 0x25U);
    std::memset(asset.bytes + 0x25, 0, 1);
    asset.bytes[0x25] = static_cast<std::uint8_t>(value);
    const std::uint32_t observed = call_func7ch(&asset, 0xabcdef00U);
    const std::uint32_t expected = 0xabcdef00U | (value & 0xffU);
    assert(observed == expected);
  }
  asset.bytes[0x25] = 0xff;
  const std::uint32_t before = asset_word(asset, 0x24);
  assert(call_func7ch(&asset, 0x12345678U) == 0x123456ffU);
  assert(asset_word(asset, 0x24) == before);
}

void test_constant_accessor() {
  reset();
  assert(sporepedia_func3ch_006417b0(&asset) == 0x80000001U);
  assert(sporepedia_func3ch_006417b0(nullptr) == 0x80000001U);
  const auto invalid = reinterpret_cast<Pkg16AssetData*>(std::uintptr_t{1});
  assert(sporepedia_func3ch_006417b0(invalid) == 0x80000001U);
}

void test_author_name_accessor() {
  reset();
  store_asset_word(
      asset, 0x1c,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&metadata)));
  store_metadata_word(metadata, 0x78,
                      static_cast<std::uint32_t>(
                          reinterpret_cast<std::uintptr_t>(&author_name)));
  assert(sporepedia_get_author_name_00641810(&asset) == &author_name);
  store_asset_word(asset, 0x1c, 0);
  assert(sporepedia_get_author_name_00641810(&asset) == nullptr);
}

void test_author_id_accessor() {
  reset();
  store_asset_word(
      asset, 0x1c,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&metadata)));
  store_metadata_word(metadata, 0x58, 0x89abcdefU);
  const RawQword populated = call_author_id(&asset, 0x01234567U);
  assert(populated.low == 0x89abcdefU);
  assert(populated.high == 0x01234567U);
  store_asset_word(asset, 0x1c, 0);
  const RawQword empty = call_author_id(&asset, 0x01234567U);
  assert(empty.low == 0);
  assert(empty.high == 0x01234567U);
}

void test_tags_accessor() {
  reset();
  store_asset_word(
      asset, 0x1c,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&metadata)));
  store_metadata_word(
      metadata, 0x88,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&tags)));
  assert(sporepedia_get_tags_00641850(&asset) == &tags);
  store_asset_word(asset, 0x1c, 0);
  assert(sporepedia_get_tags_00641850(&asset) == nullptr);
}

void test_time_accessor() {
  reset();
  store_asset_word(
      asset, 0x1c,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&metadata)));
  store_metadata_word(metadata, 0xac, 0x1000U);
  store_metadata_word(metadata, 0xb0, 0x1000U);
  destination.begin = 0x2000U;
  destination.end = 0x2004U;
  call_time(&asset, &destination);
  assert(time_helper_calls == 1);
  assert(observed_time_destination == &destination);
  assert(destination.begin == 0x2000U);
  assert(destination.end == 0x2004U);

  time_helper_calls = 0;
  observed_time_destination = nullptr;
  store_asset_word(asset, 0x1c, 0);
  call_time(&asset, &destination);
  assert(time_helper_calls == 0);
  assert(observed_time_destination == nullptr);
  assert(destination.begin == 0x2000U);
  assert(destination.end == 0x2004U);

  store_asset_word(
      asset, 0x1c,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&metadata)));
  call_time(&asset, nullptr);
  assert(time_helper_calls == 1);
  assert(observed_time_destination == nullptr);
}

enum class InvalidKind { func7ch, author_name, author_id, tags, time };

[[noreturn]] void run_invalid(InvalidKind kind) {
  Pkg16AssetData* self = reinterpret_cast<Pkg16AssetData*>(std::uintptr_t{1});
  volatile std::uint32_t result = 0;
  switch (kind) {
    case InvalidKind::func7ch:
      result = call_func7ch(self, 0x12345678U);
      break;
    case InvalidKind::author_name:
      result = reinterpret_cast<std::uint32_t>(
          sporepedia_get_author_name_00641810(self));
      break;
    case InvalidKind::author_id:
      result = call_author_id(self, 0x12345678U).low;
      break;
    case InvalidKind::tags:
      result =
          reinterpret_cast<std::uint32_t>(sporepedia_get_tags_00641850(self));
      break;
    case InvalidKind::time:
      call_time(self, &destination);
      break;
  }
  _exit(result == 0 ? 2 : 3);
}

void expect_segmentation_fault(InvalidKind kind) {
  const pid_t child = fork();
  assert(child >= 0);
  if (child == 0) {
    run_invalid(kind);
  }
  int status = 0;
  assert(waitpid(child, &status, 0) == child);
  assert(WIFSIGNALED(status));
  assert(WTERMSIG(status) == SIGSEGV);
}

}

int main() {
  test_byte_accessor();
  test_constant_accessor();
  test_author_name_accessor();
  test_author_id_accessor();
  test_tags_accessor();
  test_time_accessor();
  expect_segmentation_fault(InvalidKind::func7ch);
  expect_segmentation_fault(InvalidKind::author_name);
  expect_segmentation_fault(InvalidKind::author_id);
  expect_segmentation_fault(InvalidKind::tags);
  expect_segmentation_fault(InvalidKind::time);
}
