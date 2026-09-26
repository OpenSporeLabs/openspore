#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "helper_wave3.hpp"

namespace openspore::reconstruction::pkg11_h4_helper_wave3 {
namespace {

constexpr std::size_t kPageSize = 4096U;

struct AddressWindowFixture {
  std::array<std::uint32_t, 2> prefix;
  OpaqueAddressWindow window;
  std::array<std::uint32_t, 2> canary;
};

struct ContextFixture {
  std::array<std::uint32_t, 2> prefix;
  OpaqueContext context;
  std::array<std::uint32_t, 2> canary;
};

void check(bool condition) {
  if (!condition) {
    std::_Exit(1);
  }
}

#define CHECK(expression)                 \
  do {                                    \
    check(static_cast<bool>(expression)); \
  } while (false)

void fill_address_window_fixture(AddressWindowFixture& fixture) {
  fixture.prefix = {0x80000000U, 0xffffffffU};
  for (std::size_t index = 0; index < fixture.window.opaque.size(); ++index) {
    fixture.window.opaque[index] = static_cast<std::uint8_t>(index * 13U + 7U);
  }
  fixture.canary = {0xdeadbeefU, 0x13579bdfU};
}

void fill_context_fixture(ContextFixture& fixture, OpaqueContextWord word) {
  fixture.prefix = {0x80000000U, 0xffffffffU};
  for (std::size_t index = 0; index < fixture.context.opaque_prefix.size();
       ++index) {
    fixture.context.opaque_prefix[index] =
        static_cast<std::uint8_t>(index * 11U + 5U);
  }
  fixture.context.context_word = word;
  fixture.canary = {0xdeadbeefU, 0x13579bdfU};
}

void test_address_window_offset_and_canaries() {
  AddressWindowFixture fixture{};
  fill_address_window_fixture(fixture);
  const AddressWindowFixture before = fixture;
  const std::uintptr_t receiver =
      reinterpret_cast<std::uintptr_t>(&fixture.window);

  OpaqueAddressWindow* result = address_window_offset_005c65e0(&fixture.window);

  CHECK(reinterpret_cast<std::uintptr_t>(result) == receiver + 0x3cU);
  CHECK(fixture.prefix == before.prefix);
  CHECK(fixture.canary == before.canary);
  CHECK(fixture.window.opaque == before.window.opaque);
  CHECK(std::memcmp(&fixture, &before, sizeof(fixture)) == 0);
}

void test_address_window_does_not_read_result() {
  void* mapping =
      mmap(nullptr, kPageSize, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  CHECK(mapping != MAP_FAILED);
  auto* receiver = reinterpret_cast<OpaqueAddressWindow*>(
      static_cast<std::uint8_t*>(mapping) + kPageSize - 0x3cU);
  OpaqueAddressWindow* result = address_window_offset_005c65e0(receiver);
  CHECK(reinterpret_cast<std::uintptr_t>(result) ==
        reinterpret_cast<std::uintptr_t>(mapping) + kPageSize);
  CHECK(munmap(mapping, kPageSize) == 0);
}

void test_address_window_null_and_near_null() {
  OpaqueAddressWindow* null_result = address_window_offset_005c65e0(nullptr);
  CHECK(reinterpret_cast<std::uintptr_t>(null_result) == 0x3cU);

  auto* near_null =
      reinterpret_cast<OpaqueAddressWindow*>(static_cast<std::uintptr_t>(1));
  OpaqueAddressWindow* near_null_result =
      address_window_offset_005c65e0(near_null);
  CHECK(reinterpret_cast<std::uintptr_t>(near_null_result) == 0x3dU);
}

void test_context_word_propagation_and_no_mutation() {
  constexpr std::array<OpaqueContextWord, 5> words = {
      0U, 0xffffffffU, 0x80000000U, 0x13579bdfU, 0x2468ace0U};

  for (OpaqueContextWord word : words) {
    ContextFixture fixture{};
    fill_context_fixture(fixture, word);
    const ContextFixture before = fixture;

    OpaqueContextWord result = context_word_read_00ce6950(&fixture.context);

    CHECK(result == word);
    CHECK(fixture.prefix == before.prefix);
    CHECK(fixture.canary == before.canary);
    CHECK(fixture.context.opaque_prefix == before.context.opaque_prefix);
    CHECK(std::memcmp(&fixture, &before, sizeof(fixture)) == 0);
  }
}

template <typename Function>
void expect_segmentation_fault(Function function) {
  const pid_t child = fork();
  CHECK(child >= 0);
  if (child == 0) {
    function();
    std::_Exit(0);
  }
  int status = 0;
  CHECK(waitpid(child, &status, 0) == child);
  CHECK(WIFSIGNALED(status));
  CHECK(WTERMSIG(status) == SIGSEGV);
}

void test_context_null_and_near_null_fault() {
  expect_segmentation_fault([] { context_word_read_00ce6950(nullptr); });
  expect_segmentation_fault([] {
    context_word_read_00ce6950(
        reinterpret_cast<OpaqueContext*>(static_cast<std::uintptr_t>(1)));
  });
}

}

}

int main() {
  namespace ns = openspore::reconstruction::pkg11_h4_helper_wave3;
  ns::test_address_window_offset_and_canaries();
  ns::test_address_window_does_not_read_result();
  ns::test_address_window_null_and_near_null();
  ns::test_context_word_propagation_and_no_mutation();
  ns::test_context_null_and_near_null_fault();
}
