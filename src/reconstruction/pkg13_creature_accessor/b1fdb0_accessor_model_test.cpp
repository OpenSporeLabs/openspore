#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "b1fdb0_accessor.hpp"

struct OpaqueNounManager {
  std::array<std::uint8_t, 0x58> bytes{};
};

namespace {

using openspore::reconstruction::pkg13_creature_accessor::
    OpaqueNounManagerField;
using openspore::reconstruction::pkg13_creature_accessor::
    pkg13_creature_accessor_00b1fdb0;

static_assert(sizeof(OpaqueNounManagerField) == 4,
              "the target field is one 32-bit word");
static_assert(sizeof(OpaqueNounManager) >= 0x58,
              "the observed field requires a 0x58-byte receiver prefix");

enum class InvalidReceiver { null_receiver, near_null_receiver };

void store_field(OpaqueNounManager& receiver, OpaqueNounManagerField value) {
  std::memcpy(receiver.bytes.data() + 0x54, &value, sizeof(value));
}

[[noreturn]] void run_invalid_access(InvalidReceiver invalid) {
  auto* receiver =
      invalid == InvalidReceiver::null_receiver
          ? nullptr
          : reinterpret_cast<OpaqueNounManager*>(std::uintptr_t{1});
  const volatile OpaqueNounManagerField result =
      pkg13_creature_accessor_00b1fdb0(receiver);
  _exit(result == 0 ? 2 : 3);
}

void expect_segmentation_fault(InvalidReceiver invalid) {
  const pid_t child = fork();
  assert(child >= 0);
  if (child == 0) {
    run_invalid_access(invalid);
  }
  int status = 0;
  assert(waitpid(child, &status, 0) == child);
  assert(WIFSIGNALED(status));
  assert(WTERMSIG(status) == SIGSEGV);
}

void run() {
  OpaqueNounManager receiver{};
  for (std::size_t index = 0; index < receiver.bytes.size(); ++index) {
    receiver.bytes[index] = static_cast<std::uint8_t>(index * 3U + 1U);
  }

  store_field(receiver, 0U);
  assert(pkg13_creature_accessor_00b1fdb0(&receiver) == 0U);

  store_field(receiver, 1U);
  assert(pkg13_creature_accessor_00b1fdb0(&receiver) == 1U);

  store_field(receiver, UINT32_MAX);
  assert(pkg13_creature_accessor_00b1fdb0(&receiver) == UINT32_MAX);

  store_field(receiver, 0xa5a55a5aU);
  const auto before = receiver.bytes;
  assert(pkg13_creature_accessor_00b1fdb0(&receiver) == 0xa5a55a5aU);
  assert(receiver.bytes == before);

  expect_segmentation_fault(InvalidReceiver::null_receiver);
  expect_segmentation_fault(InvalidReceiver::near_null_receiver);
}

}

int main() { run(); }
