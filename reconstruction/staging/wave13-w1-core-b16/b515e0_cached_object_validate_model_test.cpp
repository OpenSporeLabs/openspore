// Model test for 0x00b515e0.
//
// The body of this function is a control-flow decision tree over two globals
// and two identity comparisons, so the model test drives the six reachable
// states and checks the exact side-effect signature of each:
//
//   state                     latch written   release called   builder called
//   ------------------------------------------------------------------------
//   guard null                      no              no              no
//   cache null                      yes             no             yes
//   manager mismatch                yes            yes             yes
//   subid mismatch                  yes            yes             yes
//   both match                      no              no              no
//   (cache survives mismatch)       -- see note
//
// The last column is the observation that matters most: because the release
// port always nulls the cached-object global, the three mismatch/absence paths
// collapse onto the same "rebuild and latch" tail, and the model asserts that
// collapse rather than assuming it.

#include "b515e0_cached_object_validate.hpp"

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace {

using namespace openspore::reconstruction::wave13_w1_core_b16;

int failures = 0;

// A cGameInputManager pointer that is deliberately not the one the accessor
// returns, so the first identity check can be driven to fail.
constexpr std::uint32_t kForeignManager = 0x99990000u;
constexpr std::uint32_t kSubid = 0x22220000u;

void expect(bool condition, const char* what) {
  if (!condition) {
    ++failures;
    std::printf("FAIL %s\n", what);
  }
}

// Port doubles with observable call counters.
struct PortState {
  int release_calls = 0;
  int builder_calls = 0;
  int slot_calls = 0;
  std::uint32_t* manager = nullptr;
  std::uint32_t* slot_subobject = nullptr;
  std::uint32_t* slot_result = nullptr;
  std::uint32_t slot_result_subid = 0;
};

PortState g_ports;

struct State {
  int release_calls;
  int builder_calls;
  int slot_calls;
  std::uint8_t latch;
};

// `cache_present` selects whether the cached-object global holds a pointer or
// is null. Any other non-zero sentinel would be dereferenced for real, so the
// real storage address is installed instead.
State run(std::uint32_t guard, bool cache_present, bool manager_matches,
          std::uint32_t recorded_subid, std::uint32_t current_subid) {
  static std::uint32_t gim_storage[0x30];
  static std::uint32_t subobject_storage[0x10];
  static std::uint32_t result_storage[0x10];
  static ObservedCachedSubobjectB515e0 tracked;
  static ObservedCachedObjectB515e0 cached;
  static ObservedReceiverB515e0 receiver;

  std::memset(&tracked, 0, sizeof(tracked));
  std::memset(&cached, 0, sizeof(cached));
  std::memset(&receiver, 0, sizeof(receiver));
  std::memset(gim_storage, 0, sizeof(gim_storage));
  std::memset(subobject_storage, 0, sizeof(subobject_storage));
  std::memset(result_storage, 0, sizeof(result_storage));

  g_ports = PortState{};
  g_ports.manager = gim_storage;
  g_ports.slot_subobject = subobject_storage;
  g_ports.slot_result = result_storage;
  g_ports.slot_result_subid = current_subid;

  gim_storage[0x24 / 4] = reinterpret_cast<std::uint32_t>(subobject_storage);
  tracked.field_34_recorded_manager = manager_matches
                                          ? reinterpret_cast<std::uint32_t>(
                                                reinterpret_cast<std::uintptr_t>(
                                                    gim_storage))
                                          : kForeignManager;
  tracked.field_3c_recorded_subid = recorded_subid;
  cached.field_1c_subobject = &tracked;
  receiver.field_30_rebuilt_latch = 0;

  *kGuardGlobal_0167ecd0 = guard;
  *kCachedObjectGlobal_0167ecd4 = cache_present
                                      ? reinterpret_cast<std::uint32_t>(
                                            reinterpret_cast<std::uintptr_t>(
                                                &cached))
                                      : 0u;

  SimCachedObjectValidate_00b515e0(&receiver);

  State s;
  s.release_calls = g_ports.release_calls;
  s.builder_calls = g_ports.builder_calls;
  s.slot_calls = g_ports.slot_calls;
  s.latch = receiver.field_30_rebuilt_latch;
  return s;
}

}  // namespace

// The counting doubles live in the port namespace itself, not in an anonymous
// one, so they bind to the declarations the reconstruction calls.
namespace openspore::reconstruction::wave13_w1_core_b16 {

std::uint32_t* port_00b3d310_singletonReceiver() {
  return reinterpret_cast<std::uint32_t*>(0x00AABBCCu);
}

std::uint32_t* port_00b3d350_gameInputManagerGet() { return g_ports.manager; }

std::uint32_t* port_virtualSlot0C_of_gameInputManagerSubobject(
    std::uint32_t* sub) {
  ++g_ports.slot_calls;
  if (sub != g_ports.slot_subobject) {
    ++failures;
    std::printf(
        "FAIL slot +0x0c receiver is not the [gim + 0x24] sub-object\n");
  }
  g_ports.slot_result[0x08 / 4] = g_ports.slot_result_subid;
  return g_ports.slot_result;
}

void port_00b512f0_ensureCachedObjectBuilt() { ++g_ports.builder_calls; }

void port_00b4f7f0_releaseCachedObject() {
  ++g_ports.release_calls;
  // Observed at 0x00b4f81f: the release port always leaves the global null.
  *kCachedObjectGlobal_0167ecd4 = 0;
}

}  // namespace openspore::reconstruction::wave13_w1_core_b16

int main() {
  // 0x00b515ea: master guard null -> total no-op, latch untouched.
  State s = run(/*guard=*/0, false, true, kSubid, kSubid);
  expect(s.release_calls == 0 && s.builder_calls == 0 && s.slot_calls == 0,
         "guard null performs no port call at all");
  expect(s.latch == 0, "guard null does not write the +0x30 latch");

  // 0x00b515f3: cached object absent -> build and latch, no identity check.
  s = run(/*guard=*/1, /*cache_present=*/false, true, kSubid, kSubid);
  expect(s.builder_calls == 1 && s.release_calls == 0 && s.slot_calls == 0,
         "absent cache builds once and skips both identity checks");
  expect(s.latch == 1, "absent cache sets the +0x30 latch");

  // Both identity checks satisfied -> nothing happens at all.
  s = run(/*guard=*/1, /*cache_present=*/true, true, kSubid, kSubid);
  expect(s.release_calls == 0 && s.builder_calls == 0 && s.slot_calls == 1,
         "fresh cache calls only the slot +0x0c virtual and keeps everything");
  expect(s.latch == 0, "fresh cache leaves the +0x30 latch untouched");

  // 0x00b51606: manager pointer identity broken -> release then rebuild, and
  // the second identity check is never reached.
  s = run(/*guard=*/1, /*cache_present=*/true, false, kSubid, kSubid);
  expect(s.slot_calls == 0, "manager mismatch short-circuits the slot +0x0c call");
  expect(s.release_calls == 1, "manager mismatch releases exactly once");
  expect(s.builder_calls == 1, "manager mismatch rebuilds in the same call");
  expect(s.latch == 1, "manager mismatch sets the +0x30 latch");

  // 0x00b51622: sub-object identity broken -> same shared release tail.
  s = run(/*guard=*/1, /*cache_present=*/true, true, kSubid, 0x88880000u);
  expect(s.slot_calls == 1, "subid mismatch reaches the slot +0x0c call");
  expect(s.release_calls == 1 && s.builder_calls == 1,
         "subid mismatch releases then rebuilds in the same call");
  expect(s.latch == 1, "subid mismatch sets the +0x30 latch");

  if (failures != 0) {
    std::printf("%d check(s) failed\n", failures);
    return 1;
  }
  std::printf("all checks passed\n");
  return 0;
}
