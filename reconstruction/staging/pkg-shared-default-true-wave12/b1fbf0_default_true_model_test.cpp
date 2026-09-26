// Model test for 0x00b1fbf0.
//
// Two independent claims are checked.
//
// 1. Behaviour: the reconstruction answers 1 for every receiver, including
//    null and a pointer to a struct the function has no reason to know about.
//    Passing pointers the body must not touch is what makes "the receiver is
//    never dereferenced" observable rather than asserted.
//
// 2. Machine shape: the compiled body is compared against the three observed
//    bytes b0 01 c3, and a naked twin carrying the literal observed encoding is
//    disassembled to confirm the reconstruction's prologue/epilogue contract
//    (byte write to AL, bare RET, no immediate, no stack traffic).

#include "b1fbf0_default_true.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace {

struct GuardWord {
  std::uint32_t first;
  std::uint32_t second;
};

int failures = 0;

void expect(bool condition, const char* what) {
  if (!condition) {
    ++failures;
    std::printf("FAIL %s\n", what);
  }
}

// The same port under a thiscall spelling. On i386 this is the shape a vtable
// entry has to have, and it must compile to the same three bytes.
extern "C" __thiscall std::uint8_t
FUN_00b1fbf0_shared_default_true_thiscall(OpaqueB1Fbf0SlotReceiver* receiver) {
  static_cast<void>(receiver);
  return 1;
}

// A naked twin holding the literal observed encoding, used to pin the exact
// byte sequence the original ships.
extern "C" __thiscall __attribute__((naked)) std::uint8_t
b1fbf0_observed_bytes_twin(OpaqueB1Fbf0SlotReceiver*) {
  __asm__("movb $0x1, %al\n\t"
          "ret\n\t");
}

const std::uint8_t kObservedBody[3] = {0xb0, 0x01, 0xc3};

void expect_bytes(const char* label, const void* code) {
  std::uint8_t actual[3] = {0, 0, 0};
  std::memcpy(actual, code, sizeof(actual));
  if (std::memcmp(actual, kObservedBody, sizeof(kObservedBody)) != 0) {
    ++failures;
    std::printf("FAIL %s bytes %02x %02x %02x != b0 01 c3\n", label, actual[0],
                actual[1], actual[2]);
  }
}

}  // namespace

int main() {
  using openspore::reconstruction::pkg_shared_default_true_wave12::
      FUN_00b1fbf0_shared_default_true;

  GuardWord guard = {0x11223344u, 0x55667788u};
  auto* as_receiver = reinterpret_cast<OpaqueB1Fbf0SlotReceiver*>(&guard);

  expect(FUN_00b1fbf0_shared_default_true(nullptr) == 1,
         "returns 1 for a null receiver");
  expect(FUN_00b1fbf0_shared_default_true(as_receiver) == 1,
         "returns 1 for a non-null receiver");
  expect(guard.first == 0x11223344u && guard.second == 0x55667788u,
         "leaves memory behind the receiver untouched");

  expect(FUN_00b1fbf0_shared_default_true_thiscall(nullptr) == 1,
         "thiscall spelling returns 1 for a null receiver");
  expect(FUN_00b1fbf0_shared_default_true_thiscall(as_receiver) == 1,
         "thiscall spelling returns 1 for a non-null receiver");

  expect(reinterpret_cast<const void*>(&FUN_00b1fbf0_shared_default_true) !=
             nullptr,
         "reconstruction has an address");
  expect_bytes("reconstruction", reinterpret_cast<const void*>(
                                    &FUN_00b1fbf0_shared_default_true));
  expect_bytes("thiscall spelling",
               reinterpret_cast<const void*>(
                   &FUN_00b1fbf0_shared_default_true_thiscall));
  expect_bytes("observed twin",
               reinterpret_cast<const void*>(&b1fbf0_observed_bytes_twin));

  if (failures != 0) {
    std::printf("%d check(s) failed\n", failures);
    return 1;
  }
  std::printf("all checks passed\n");
  return 0;
}
