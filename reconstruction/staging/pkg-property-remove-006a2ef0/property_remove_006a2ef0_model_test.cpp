// PKG-PROPERTY-REMOVE-006A2EF0 -- model test for the reconstruction of VA
// 0x006a2ef0.
//
// Plain int main(), explicit checks, no framework and no external dependency.
// The one callee this package does not own (0x006a2cb0) is defined here as a
// recording observer, so every claim the reconstruction makes about the call is
// checked against what the machine listing fixes: the receiver the port is
// invoked on (ESI + 0x18, formed by the LEA at 0x006a2ef8), the fact that the
// port is handed the *address* of the caller's property-id word rather than the
// word (LEA 0x006a2ef3 / PUSH 0x006a2ef7), the unconditional increment of the
// word at ESI + 0x34 (0x006a2f00) including on the port's no-removal path, and
// the port's result reaching the caller untouched (no write to EAX between
// 0x006a2f00 and the RET 0x4 at 0x006a2f04).
//
// The receiver is opaque in the reconstruction, so the test supplies the
// smallest object that satisfies the two accesses the body makes: a byte at
// +0x18 and a 32-bit counter at +0x34.

#include "property_remove_006a2ef0.hpp"

#include <cstdint>
#include <cstdio>

// The recording observer for 0x006a2cb0. It lives in the package's own
// namespace, not an anonymous one, because it has to *define* the port this
// package declares: a definition in an unnamed namespace would be a different
// entity and the reconstructed body's call would still be unresolved.
namespace openspore {
namespace reconstruction {
namespace pkg_property_remove_006a2ef0 {

int g_calls = 0;
const void *g_last_receiver = nullptr;
std::uint32_t g_last_property_id = 0;
bool g_last_argument_was_address = false;
int g_port_result = 0;

int PKG_PROPERTY_REMOVE_006A2EF0_THISCALL property_list_map_remove_006a2cb0(
    OpaquePropertyMap *receiver, const std::uint32_t *property_id) {
  ++g_calls;
  g_last_receiver = receiver;
  g_last_argument_was_address = (property_id != nullptr);
  g_last_property_id = property_id ? *property_id : 0u;
  return g_port_result;
}

}  // namespace pkg_property_remove_006a2ef0
}  // namespace reconstruction
}  // namespace openspore

namespace {

using namespace openspore::reconstruction::pkg_property_remove_006a2ef0;

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char *what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL: %s\n", what);
  }
}

void check_eq_int(long long got, long long want, const char *what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL: %s (got %lld, want %lld)\n", what, got, want);
  }
}

// The receiver, sized to cover both displacements the body names and nothing
// more. +0x18 is the port's receiver, +0x34 is the mutation counter.
struct FakePropertyList {
  std::uint8_t filler[0x18];
  std::uint32_t port_receiver_tag;  // +0x18
  std::uint8_t filler2[0x34 - 0x18 - 4];
  std::uint32_t mutation_count;     // +0x34
};

void reset_observer() {
  g_calls = 0;
  g_last_receiver = nullptr;
  g_last_property_id = 0;
  g_last_argument_was_address = false;
  g_port_result = 0;
}

// The property-list counter lives at +0x34, which is exactly the displacement
// the source names through kPortReceiverDisplacement's sibling constant. Read
// it the way the body does rather than through a struct member, so the test
// cannot silently agree with a wrong offset.
std::uint32_t counter_at_34(void *self) {
  return *reinterpret_cast<std::uint32_t *>(
      reinterpret_cast<std::uintptr_t>(self) + 0x34);
}

}  // namespace

int main() {
  static_assert(sizeof(FakePropertyList) >= 0x38,
                "the fake receiver must cover the +0x34 access");

  // --- 1. The port sees the +0x18 sub-object as its receiver ---------------
  {
    FakePropertyList list = {};
    list.port_receiver_tag = 0xC0FFEE01u;
    list.mutation_count = 0;
    reset_observer();
    g_port_result = 1;

    const int removed = property_list_remove_property_006a2ef0(
        reinterpret_cast<OpaquePropertyList *>(&list), 0x1234u);

    check_eq_int(g_calls, 1, "the body makes exactly one call");
    // LEA ECX,[ESI+0x18] at 0x006a2ef8: the port's receiver is this + 0x18.
    check(g_last_receiver ==
              reinterpret_cast<const void *>(
                  reinterpret_cast<std::uintptr_t>(&list) + 0x18),
          "the port receiver is the +0x18 sub-object");
    // LEA EAX,[ESP+0x8] / PUSH EAX at 0x006a2ef3/0x006a2ef7: the port is handed
    // the address of the caller's property-id word, not the word.
    check(g_last_argument_was_address, "the port argument is a pointer");
    check_eq_int(g_last_property_id, 0x1234, "the pointed-to word is the property id");
    // 0x006a2f00: INC dword ptr [ESI+0x34].
    check_eq_int(counter_at_34(&list), 1, "the +0x34 counter is incremented once");
    // No write to EAX between the call and the RET 0x4, so the port's result
    // is what RemoveProperty returns.
    check_eq_int(removed, 1, "the port's result is returned unchanged");
  }

  // --- 2. The increment is unconditional, including the no-removal path ----
  // The listing has no conditional branch at all, so the counter moves even
  // when the port reports that nothing was removed.
  {
    FakePropertyList list = {};
    list.mutation_count = 7;
    reset_observer();
    g_port_result = 0;

    const int removed = property_list_remove_property_006a2ef0(
        reinterpret_cast<OpaquePropertyList *>(&list), 0u);

    check_eq_int(removed, 0, "the port's no-removal result is returned unchanged");
    check_eq_int(counter_at_34(&list), 8,
                 "the counter is incremented on the no-removal path too");
    check_eq_int(g_calls, 1, "the no-removal path still calls the port exactly once");
  }

  // --- 3. Repeated calls accumulate, one per call -------------------------
  {
    FakePropertyList list = {};
    list.mutation_count = 0;
    reset_observer();

    for (int i = 0; i < 3; ++i) {
      g_port_result = i;
      const int removed = property_list_remove_property_006a2ef0(
          reinterpret_cast<OpaquePropertyList *>(&list), 0x40u + i);
      check_eq_int(removed, i, "each call returns its own port result");
    }
    check_eq_int(g_calls, 3, "three calls reach the port");
    check_eq_int(counter_at_34(&list), 3, "three calls increment the counter three times");
  }

  // --- 4. The port observes the caller's own word, not a copy -------------
  // The body pushes the address of the incoming stack word, so the port reads
  // the value the caller passed rather than a reconstructed copy of it.
  {
    FakePropertyList list = {};
    reset_observer();
    g_port_result = 1;
    const std::uint32_t property_id = 0xDEADBEEFu;
    (void)property_list_remove_property_006a2ef0(
        reinterpret_cast<OpaquePropertyList *>(&list), property_id);
    check_eq_int(g_last_property_id, 0xDEADBEEF,
                 "the port reads the caller's property-id word");
  }

  if (g_failures != 0) {
    std::printf("%d of %d checks failed\n", g_failures, g_checks);
    return 1;
  }
  std::printf("ok: %d checks\n", g_checks);
  return 0;
}
