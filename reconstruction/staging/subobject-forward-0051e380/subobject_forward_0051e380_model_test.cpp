// Focused semantic test for the 0x0051e380 reconstruction.
//
// What is testable, and what is not. The observable behaviour of this body is
// the shape of the one call it makes: the callee's receiver is the subobject
// at receiver+0x4 (not the receiver, not receiver+0x8), the call carries no
// stack argument, it happens exactly once, the receiver is not mutated, and
// the word the callee leaves in EAX is what the body returns. Those are what
// this file checks. What it cannot check is what 0x00453540 does inside, which
// concrete subobject type the displacement names, and which class the vftable
// belongs to: the listing fixes none of them, and this test asserts none of
// them. The callee is substituted through the port, so the test proves the
// call shape and the forwarding, not the callee.
//
// Each check below is written so that a specific mutation of the
// reconstruction fails it: dropping the adjustor, adjusting by the wrong
// displacement, returning a constant instead of the callee's word, calling
// more than once, or writing to the receiver.

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "subobject_forward_0051e380.hpp"

// The header #undefines its convention macro at the end of the include guard;
// the definition below restores it for this translation unit.
#if defined(_MSC_VER)
#define PKG_SUBFWD_THISCALL __thiscall
#else
#define PKG_SUBFWD_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::subobject_forward_0051e380 {
namespace {

using namespace openspore::reconstruction::subobject_forward_0051e380;

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

// The word the stub leaves in EAX. A value the body could not produce on its
// own, so a reconstruction that returns a constant instead of forwarding the
// callee's result is caught by the equality check below.
constexpr std::uint32_t kSentinelReturn = 0x51e38000u;

// The displacement the machine states at 0x0051e38c (ADD ECX,0x4), pinned
// here independently of the implementation's own constant so that a wrong
// adjustor in the reconstruction is caught rather than followed. The two
// constants are cross-checked below.
constexpr std::size_t kExpectedAdjustor = 0x04;

OpaqueSubobject* seen_self = nullptr;
int call_count = 0;

// The callee's entry shape, reproduced exactly: ECX is the receiver, no stack
// argument, bare RET. The signature is the compile-time half of the
// zero-ordinary-argument claim -- a thunk that pushed an argument would have
// to change this type or add a cast to do so.
std::uint32_t PKG_SUBFWD_THISCALL decrement_stub(OpaqueSubobject* self) {
  seen_self = self;
  ++call_count;
  return kSentinelReturn;
}

// A fake receiver large enough to hold the subobject at +0x4 and the word the
// callee reads at subobject+0x4. The body never dereferences any of it, so the
// contents are a pattern, not a layout.
struct FakeReceiver {
  unsigned char bytes[16];
};

// The subobject base the callee must be invoked on: the receiver advanced by
// the machine-stated displacement, computed with the test-side constant so the
// expectation does not follow the implementation's own adjustor.
OpaqueSubobject* expected_subobject(FakeReceiver* receiver) {
  return reinterpret_cast<OpaqueSubobject*>(
      reinterpret_cast<unsigned char*>(receiver) + kExpectedAdjustor);
}

bool same_bytes(const unsigned char* left, const unsigned char* right,
                std::size_t count) {
  for (std::size_t offset = 0; offset < count; ++offset) {
    if (left[offset] != right[offset]) {
      return false;
    }
  }
  return true;
}

}  // namespace

// One run of the target over a freshly patterned receiver, with the callee
// substituted by the stub. Returns true iff every check held.
bool run() {
  FakeReceiver receiver{};
  for (std::size_t offset = 0; offset < sizeof(receiver.bytes); ++offset) {
    receiver.bytes[offset] =
        static_cast<unsigned char>(offset * 37u + 11u);
  }
  unsigned char before[sizeof(receiver.bytes)];
  std::memcpy(before, receiver.bytes, sizeof(receiver.bytes));

  Ports ports{};
  ports.decrement_00453540 = &decrement_stub;
  g_subobject_forward_ports = &ports;

  const std::uint32_t result =
      subobject_forward_0051e380(reinterpret_cast<OpaqueReceiver*>(&receiver));

  g_subobject_forward_ports = nullptr;

  // The adjustor: the callee's receiver is the subobject at receiver+0x4.
  // Fails if the body calls with the receiver itself or a wrong displacement.
  check(call_count == 1);
  check(kSubobjectAdjustor == kExpectedAdjustor);
  check(seen_self == expected_subobject(&receiver));

  // The return: the body forwards the callee's EAX unchanged. Fails if the
  // body returns a constant, returns void, or transforms the value.
  check(result == kSentinelReturn);

  // The receiver is not mutated: the body spills and reloads ECX but writes
  // no memory. Fails if the body stores to the receiver or the subobject.
  check(same_bytes(before, receiver.bytes, sizeof(receiver.bytes)));

  // The callee is invoked exactly once. Fails if the body calls it in a loop
  // or more than once per invocation.
  check(call_count == 1);

  return failures == 0;
}

}  // namespace openspore::reconstruction::subobject_forward_0051e380

int main() {
  return openspore::reconstruction::subobject_forward_0051e380::run() ? 0 : 1;
}
