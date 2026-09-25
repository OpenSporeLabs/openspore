#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "sim_helpers.hpp"

namespace openspore::reconstruction::pkg11_h1_sim_helpers {

struct OpaqueSimulationManager {
  std::array<std::uint8_t, 0x24> bytes{};
};

struct OpaqueRelationshipManager {
  std::array<std::uint8_t, 0x100> bytes{};
};

namespace {

OpaqueSimulationManager* root_value = nullptr;
int root_calls = 0;
int read_calls = 0;
OpaqueSimulationManager* read_receiver = nullptr;

void store_shared_gate(OpaqueSimulationManager& manager,
                       SharedGateValue value) {
  std::memcpy(manager.bytes.data() + 0x20, &value, sizeof(value));
}

void reset_shared_gate_trace() {
  root_value = nullptr;
  root_calls = 0;
  read_calls = 0;
  read_receiver = nullptr;
}

void test_shared_gate() {
  reset_shared_gate_trace();
  assert(pkg11_sim_helpers_00b5b800() == 0xffffffffU);
  assert(root_calls == 1);
  assert(read_calls == 0);
  assert(read_receiver == nullptr);

  OpaqueSimulationManager manager{};
  for (std::size_t index = 0; index < manager.bytes.size(); ++index) {
    manager.bytes[index] = static_cast<std::uint8_t>(index * 7U + 3U);
  }
  store_shared_gate(manager, 0x01654c10U);
  const auto before = manager.bytes;
  root_value = &manager;
  assert(pkg11_sim_helpers_00b5b800() == 0x01654c10U);
  assert(root_calls == 2);
  assert(read_calls == 1);
  assert(read_receiver == &manager);
  assert(manager.bytes == before);

  store_shared_gate(manager, 0xffffffffU);
  assert(pkg11_sim_helpers_00b5b800() == 0xffffffffU);
  store_shared_gate(manager, 0xdeadbeefU);
  assert(pkg11_sim_helpers_00b5b800() == 0xdeadbeefU);
  assert(root_calls == 4);
  assert(read_calls == 3);
}

void test_progression_badge_base() {
  struct DerivedProgressionBadge {
    OpaqueProgressionBadgeBase base;
    std::array<std::uint8_t, 0x11> tail{};
  };

  DerivedProgressionBadge object{};
  object.base.primary_vtable = 0xa5a5a5a5U;
  object.base.state_04 = 0x5a5a5a5aU;
  object.base.secondary_vtable = 0xa5a5a5a5U;
  object.base.state_0c = 0xa5U;
  object.base.state_0d = 0x5aU;
  object.base.state_0e = 0xa5U;
  for (std::size_t index = 0; index < object.tail.size(); ++index) {
    object.tail[index] = static_cast<std::uint8_t>(index + 1U);
  }
  const auto tail_before = object.tail;

  pkg11_sim_helpers_00b5b6c0(&object.base);

  assert(object.base.primary_vtable == kPrimaryVtable);
  assert(object.base.state_04 == 0U);
  assert(object.base.secondary_vtable == kSecondaryVtable);
  assert(object.base.state_0c == 0U);
  assert(object.base.state_0d == 0U);
  assert(object.base.state_0e == 0U);
  assert(object.tail == tail_before);
}

enum class InvalidReceiver { null_receiver, near_null_receiver };

[[noreturn]] void run_invalid_constructor(InvalidReceiver invalid) {
  auto* receiver = invalid == InvalidReceiver::null_receiver
                       ? nullptr
                       : reinterpret_cast<OpaqueProgressionBadgeBase*>(
                             std::uintptr_t{1});
  pkg11_sim_helpers_00b5b6c0(receiver);
  _exit(0);
}

void expect_constructor_fault(InvalidReceiver invalid) {
  const pid_t child = fork();
  assert(child >= 0);
  if (child == 0) {
    run_invalid_constructor(invalid);
  }
  int status = 0;
  assert(waitpid(child, &status, 0) == child);
  assert(WIFSIGNALED(status));
  assert(WTERMSIG(status) == SIGSEGV);
}

void test_relationship_manager_accessor() {
  OpaqueRelationshipManager manager{};
  g_relationship_manager_0167eb14 = nullptr;
  assert(pkg11_sim_helpers_00b3d3c0() == nullptr);

  const auto before = manager.bytes;
  g_relationship_manager_0167eb14 = &manager;
  assert(pkg11_sim_helpers_00b3d3c0() == &manager);
  assert(manager.bytes == before);

  auto* invalid = reinterpret_cast<OpaqueRelationshipManager*>(
      std::uintptr_t{1});
  g_relationship_manager_0167eb14 = invalid;
  assert(pkg11_sim_helpers_00b3d3c0() == invalid);
  g_relationship_manager_0167eb14 = nullptr;
}

}

extern "C" OpaqueSimulationManager* manager_root_00b3d320() {
  ++root_calls;
  return root_value;
}

extern "C" SharedGateValue __attribute__((fastcall))
read_shared_gate_00a42730(OpaqueSimulationManager* manager) {
  ++read_calls;
  read_receiver = manager;
  SharedGateValue value = 0;
  std::memcpy(&value, manager->bytes.data() + 0x20, sizeof(value));
  return value;
}

}

int main() {
  openspore::reconstruction::pkg11_h1_sim_helpers::test_shared_gate();
  openspore::reconstruction::pkg11_h1_sim_helpers::test_progression_badge_base();
  openspore::reconstruction::pkg11_h1_sim_helpers::
      expect_constructor_fault(
          openspore::reconstruction::pkg11_h1_sim_helpers::
              InvalidReceiver::null_receiver);
  openspore::reconstruction::pkg11_h1_sim_helpers::
      expect_constructor_fault(
          openspore::reconstruction::pkg11_h1_sim_helpers::
              InvalidReceiver::near_null_receiver);
  openspore::reconstruction::pkg11_h1_sim_helpers::
      test_relationship_manager_accessor();
}
