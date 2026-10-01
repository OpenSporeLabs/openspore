#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "receiver_member_offset_00d20610.hpp"

namespace openspore::reconstruction::pkg_00d20610_receiver_member_offset {
namespace {

constexpr std::size_t kPageSize = 4096U;
constexpr std::size_t kDisplacement = 0x1c8U;

int g_checks = 0;

void check(bool condition) {
  ++g_checks;
  if (!condition) {
    std::_Exit(1);
  }
}

#define CHECK(expression)                 \
  do {                                    \
    check(static_cast<bool>(expression)); \
  } while (false)

// A receiver the model test owns end to end, with guard words on both sides, so
// that a reconstruction which WRITES through the receiver, or which reads it,
// is caught by a byte comparison rather than by nothing at all.
// The body is larger than the displacement on purpose. A reconstruction that
// wrote through the address it returns would land at receiver+0x1c8, so the
// fixture has to own that address; the decoy words there are what such a write
// would clobber.
struct ReceiverFixture {
  std::array<std::uint32_t, 4> prefix;
  std::array<std::uint8_t, 0x200> body;
  std::array<std::uint32_t, 4> suffix;
};

void fill(ReceiverFixture& fixture) {
  fixture.prefix = {0x80000000U, 0xffffffffU, 0x0badc0deU, 0xfeedfaceU};
  for (std::size_t index = 0; index < fixture.body.size(); ++index) {
    fixture.body[index] = static_cast<std::uint8_t>(index * 29U + 11U);
  }
  fixture.suffix = {0x13579bdfU, 0x2468ace0U, 0xdeadbeefU, 0x0f1e2d3cU};
}

// 1. The result is the receiver's address plus the LEA displacement, and nothing
// else. This is the whole behavioural claim the seven bytes make.
void test_result_is_receiver_plus_displacement() {
  const std::array<std::uintptr_t, 6> bases = {
      0U,
      1U,
      0x1000U,
      0x7fff0000U,
      0x400000U,
      0xfffff000U,
  };
  for (std::uintptr_t base : bases) {
    auto* receiver = reinterpret_cast<OpaqueReceiver*>(base);
    const std::uintptr_t result = reinterpret_cast<std::uintptr_t>(
        receiver_member_offset_00d20610(receiver));
    CHECK(result == base + kDisplacement);
  }
}

// 2. The displacement is exactly 0x1c8 and not a neighbour. Each of these is a
// single-bit mutation of the constant; the original passes all of them by not
// producing their values.
void test_displacement_is_not_a_neighbour() {
  const std::uintptr_t base = 0x10000U;
  auto* receiver = reinterpret_cast<OpaqueReceiver*>(base);
  const std::uintptr_t result = reinterpret_cast<std::uintptr_t>(
      receiver_member_offset_00d20610(receiver));

  CHECK(result != base + 0x1c7U);
  CHECK(result != base + 0x1c9U);
  CHECK(result != base + 0x1c4U);
  CHECK(result != base + 0x1ccU);
  CHECK(result != base + 0x0c8U);
  CHECK(result != base + 0x2c8U);
  CHECK(result != base + 0x1c0U);
  CHECK(result != base);
}

// 3. The receiver is not modified. A body that stored through ECX -- the only
// way a two-instruction function could -- would move a guard word.
void test_receiver_is_not_modified() {
  for (std::uint32_t seed = 0U; seed < 4U; ++seed) {
    ReceiverFixture fixture{};
    fill(fixture);
    if (seed != 0U) {
      fixture.body[kDisplacement] = static_cast<std::uint8_t>(seed * 61U);
    }
    const ReceiverFixture before = fixture;

    (void)receiver_member_offset_00d20610(
        reinterpret_cast<OpaqueReceiver*>(&fixture.prefix[0]));

    CHECK(std::memcmp(&fixture, &before, sizeof(fixture)) == 0);
    CHECK(fixture.prefix == before.prefix);
    CHECK(fixture.suffix == before.suffix);
  }
}

// 4. LEA computes an address and does not read memory. Point the receiver at a
// PROT_NONE page such that receiver+0x1c8 lands exactly on the page's first
// unmapped byte: a reconstruction that loaded through the result, or through the
// receiver, would fault here and the original does not.
void test_no_memory_access() {
  void* mapping =
      mmap(nullptr, kPageSize, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  CHECK(mapping != MAP_FAILED);
  auto* receiver = reinterpret_cast<OpaqueReceiver*>(
      static_cast<std::uint8_t*>(mapping) + kPageSize - kDisplacement);

  const std::uintptr_t result = reinterpret_cast<std::uintptr_t>(
      receiver_member_offset_00d20610(receiver));

  CHECK(result == reinterpret_cast<std::uintptr_t>(mapping) + kPageSize);
  CHECK(munmap(mapping, kPageSize) == 0);
}

// 5. The result is a distinct address from the receiver for every receiver: a
// reconstruction returning the receiver unchanged, or returning a value rather
// than an address, fails here.
void test_result_is_distinct_from_receiver() {
  const std::array<std::uintptr_t, 4> bases = {0U, 4U, 0x800U, 0x20000U};
  for (std::uintptr_t base : bases) {
    auto* receiver = reinterpret_cast<OpaqueReceiver*>(base);
    CHECK(reinterpret_cast<std::uintptr_t>(receiver) !=
          reinterpret_cast<std::uintptr_t>(
              receiver_member_offset_00d20610(receiver)));
    CHECK(reinterpret_cast<std::uintptr_t>(receiver_member_offset_00d20610(
              receiver)) ==
          base + kDisplacement);
  }
}

// 6. Two receivers one byte apart give results one byte apart: the function
// adds, it does not load a per-object constant.
void test_result_tracks_the_receiver_not_an_object() {
  auto* low = reinterpret_cast<OpaqueReceiver*>(static_cast<std::uintptr_t>(0x2000));
  auto* high =
      reinterpret_cast<OpaqueReceiver*>(static_cast<std::uintptr_t>(0x2001));
  const std::uintptr_t low_result =
      reinterpret_cast<std::uintptr_t>(receiver_member_offset_00d20610(low));
  const std::uintptr_t high_result =
      reinterpret_cast<std::uintptr_t>(receiver_member_offset_00d20610(high));
  CHECK(high_result - low_result == 1U);
  CHECK(low_result == 0x2000U + kDisplacement);
  CHECK(high_result == 0x2001U + kDisplacement);
}

void report() { std::printf("checks=%d\n", g_checks); }

}  // namespace
}  // namespace openspore::reconstruction::pkg_00d20610_receiver_member_offset

int main() {
  namespace ns = openspore::reconstruction::pkg_00d20610_receiver_member_offset;
  ns::test_result_is_receiver_plus_displacement();
  ns::test_displacement_is_not_a_neighbour();
  ns::test_receiver_is_not_modified();
  ns::test_no_memory_access();
  ns::test_result_is_distinct_from_receiver();
  ns::test_result_tracks_the_receiver_not_an_object();
  ns::report();
}