#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "cell_ai_selection.hpp"

namespace {

using openspore::reconstruction::pkg06a_cell_ai_selection::
    cell_ai_select_profile_00e52910;
using openspore::reconstruction::pkg06a_cell_ai_selection::g_cell_game_016b3c04;
using openspore::reconstruction::pkg06a_cell_ai_selection::ObservedCellAiData;
using openspore::reconstruction::pkg06a_cell_ai_selection::
    ObservedCellCellResource;

static_assert(sizeof(void*) == 4);
static_assert(sizeof(ObservedCellAiData) == 0xb4);
static_assert(offsetof(ObservedCellAiData, type) == 0);
static_assert(offsetof(ObservedCellCellResource, normal) == 0xe0);
static_assert(offsetof(ObservedCellCellResource, ai_hard) == 0x194);
static_assert(offsetof(ObservedCellCellResource, ai_easy) == 0x248);
static_assert(sizeof(ObservedCellCellResource) > 0x248);

int failures = 0;

struct Fixture {
  std::array<std::byte, 0x5280> game{};
  ObservedCellCellResource resource{};
};

template <typename T>
std::array<std::byte, sizeof(T)> snapshot(const T& value) {
  std::array<std::byte, sizeof(T)> result{};
  std::memcpy(result.data(), &value, sizeof(T));
  return result;
}

template <typename T>
bool unchanged(const T& value, const std::array<std::byte, sizeof(T)>& before) {
  return std::memcmp(&value, before.data(), sizeof(T)) == 0;
}

std::uint32_t read_u32(const std::byte* object, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, object + offset, sizeof(value));
  return value;
}

void write_u32(std::byte* object, std::size_t offset, std::uint32_t value) {
  std::memcpy(object + offset, &value, sizeof(value));
}

void write_i32(std::byte* object, std::size_t offset, std::int32_t value) {
  std::memcpy(object + offset, &value, sizeof(value));
}

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void set_difficulty(Fixture& fixture, std::int32_t difficulty) {
  const std::uint32_t serializable_address =
      read_u32(fixture.game.data(), 0x5190);
  write_i32(reinterpret_cast<std::byte*>(
                static_cast<std::uintptr_t>(serializable_address)),
            0x7c, difficulty);
}

void verify_selection(Fixture& fixture, std::int32_t difficulty,
                      ObservedCellAiData* expected) {
  set_difficulty(fixture, difficulty);
  const auto game_before = snapshot(fixture.game);
  const auto resource_before = snapshot(fixture.resource);
  const auto normal_before = snapshot(fixture.resource.normal);
  const auto hard_before = snapshot(fixture.resource.ai_hard);
  const auto easy_before = snapshot(fixture.resource.ai_easy);

  ObservedCellAiData* result =
      cell_ai_select_profile_00e52910(&fixture.resource);

  check(result == expected);
  check(unchanged(fixture.game, game_before));
  check(unchanged(fixture.resource, resource_before));
  check(unchanged(fixture.resource.normal, normal_before));
  check(unchanged(fixture.resource.ai_hard, hard_before));
  check(unchanged(fixture.resource.ai_easy, easy_before));
}

}

int main() {
  Fixture fixture{};
  std::byte* serializable = fixture.game.data() + 0x100;
  write_u32(fixture.game.data(), 0x5190,
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(serializable)));
  fixture.resource.normal.type = 10;
  fixture.resource.ai_easy.type = 20;
  fixture.resource.ai_hard.type = 30;
  g_cell_game_016b3c04 = fixture.game.data();

  verify_selection(fixture, 0, &fixture.resource.ai_easy);
  verify_selection(fixture, 2, &fixture.resource.ai_hard);
  verify_selection(fixture, 1, &fixture.resource.normal);
  verify_selection(fixture, -1, &fixture.resource.normal);

  fixture.resource.ai_easy.type = -1;
  fixture.resource.ai_hard.type = -1;
  verify_selection(fixture, 0, &fixture.resource.normal);
  verify_selection(fixture, 2, &fixture.resource.normal);

  fixture.resource.normal.type = -1;
  verify_selection(fixture, 1, &fixture.resource.normal);
  verify_selection(fixture, -1, &fixture.resource.normal);

  return failures == 0 ? 0 : 1;
}
