// pkg-this-adjustor-fwd -- VA 0x00c372b0
// Behavioural model test for FUN_00c372b0 @ 0x00c372b0.
//
// The body is two instructions:
//   00c372b0  ADD ECX,0x7b8        the receiver is adjusted by +0x7b8
//   00c372b6  JMP 0x00feba90        a single ESP-neutral direct jump
//
// What is asserted is what those two instructions fix, and nothing more:
//
//   * the receiver is adjusted by EXACTLY +0x7b8 before the callee sees it --
//     the callee must receive receiver + 0x7b8 in ECX, not the incoming
//     receiver and not any other displacement;
//   * the callee is reached, exactly once, and its return value is returned
//     unchanged;
//   * the byte the callee reads is at (receiver + 0x7b8) + 0x18, which is the
//     end-to-end consequence of the adjustment composed with the callee's own
//     +0x18 field displacement;
//   * the stack is balanced across the whole call (ESP unchanged), which is the
//     forwarded caller-cleanup fact, measured;
//   * the return width is one byte, forwarded from the callee's AL-only write.
//
// The callee is defined here as a test double that models the tail target
// 0x00feba90's observable contract, read off its own listing
// (`MOV AL,byte ptr [ECX + 0x18] ; RET`): the receiver arrives in ECX (the
// __thiscall receiver, which the C++ parameter is), the byte at [receiver +
// 0x18] is read, and that byte is returned. The receiver is recorded so the
// test can require it to be the ADJUSTED receiver.
//
// The cases marked DECOY and MUTANT exist to try to BREAK the reconstruction,
// not to walk it. Each names a wrong reconstruction it is aimed at:
//
//   DECOY  a byte is planted at receiver + 0x18, where a thunk that DID NOT
//          adjust would read, and the real byte at receiver + 0x7d0, where the
//          adjusted thunk reads. The reconstruction must return the real byte;
//          a wrong adjustment reads the decoy and fails.
//   MUTANT a function that forwards the UNADJUSTED receiver is defined and
//          driven, and the test requires the callee to have received the
//          UNADJUSTED receiver -- the observation that rejects it. A
//          reconstruction that behaved like the mutant is caught by the same
//          assertion the main cases make.
//
// What is NOT asserted, and why:
//
//   * That the callee's +0x18 field means anything. The displacement is the
//     callee's own, read off its listing; the test pins the composition
//     (thunk's +0x7b8 then callee's +0x18) and never the field's identity.
//   * That the tail target 0x00feba90 is reached through a vtable. It is not:
//     the transfer is a direct JMP to a static target. (The callee is itself a
//     slot of four vptr-backed vftables, but that is a fact about the callee,
//     not a dispatch this body performs.)
//   * Anything about the class layout. No class name is inferred and no member
//     is named; the receiver is an opaque byte run.

#include "this_adjustor_fwd.hpp"

#include <cassert>
#include <cstdint>

namespace ns = openspore::reconstruction::pkg_this_adjustor_fwd;

namespace {

// The byte the callee reads, as the machine spells it: `MOV AL,byte ptr
// [ECX + 0x18]` at 0x00feba90. The displacement is the callee's own, read off
// its listing; it is a fact about the callee, not about this thunk.
constexpr std::size_t kCalleeFieldDisplacement = 0x18;

// The highest byte the whole call touches: the thunk adjusts by +0x7b8 and the
// callee reads at +0x18 above that, so the last byte is at receiver + 0x7d0.
constexpr std::size_t kLastTouchedByte = 0x7b8 + 0x18;

struct Storage {
  unsigned char bytes[kLastTouchedByte + 1];
};

// What the callee test double observed.
std::uintptr_t g_callee_receiver = 0;
int g_callee_calls = 0;

std::uintptr_t esp_read() {
  std::uintptr_t value = 0;
  asm volatile("mov %%esp, %0" : "=r"(value) :: "memory");
  return value;
}

void reset() {
  g_callee_receiver = 0;
  g_callee_calls = 0;
}

}  // namespace

// The callee test double: the tail target 0x00feba90's observable contract.
// The receiver arrives in ECX (the __thiscall receiver, which the C++ parameter
// is), the byte at [receiver + 0x18] is read, and that byte is returned. The
// receiver is recorded so the test can require it to be the ADJUSTED receiver.
extern "C" std::uint8_t PKG_THIS_ADJUSTOR_FWD_THISCALL re_00feba90(void* receiver) {
  ++g_callee_calls;
  g_callee_receiver = reinterpret_cast<std::uintptr_t>(receiver);
  return *reinterpret_cast<unsigned char*>(static_cast<char*>(receiver) + kCalleeFieldDisplacement);
}

namespace {

// A mutant that injects the defect this test exists to catch: it forwards the
// UNADJUSTED receiver. It is not the reconstruction; it is the wrong
// reconstruction the main cases' assertions are shaped to reject.
extern "C" std::uint8_t PKG_THIS_ADJUSTOR_FWD_THISCALL re_00c372b0_unadjusted(void* receiver) {
  return re_00feba90(static_cast<unsigned char*>(receiver));
}

}  // namespace

int main() {
  using ns::kReceiverAdjustorDelta;
  using ns::re_00c372b0;

  // Case 1: the adjustment. The callee must receive receiver + 0x7b8, not the
  // incoming receiver and not any other displacement.
  {
    Storage storage = {};
    reset();
    (void)re_00c372b0(storage.bytes);
    assert(g_callee_calls == 1);
    assert(g_callee_receiver ==
           reinterpret_cast<std::uintptr_t>(storage.bytes) + kReceiverAdjustorDelta);
  }

  // Case 2: the end-to-end byte. The byte the callee reads is at
  // (receiver + 0x7b8) + 0x18 = receiver + 0x7d0, and the thunk returns it.
  {
    Storage storage = {};
    reset();
    storage.bytes[kLastTouchedByte] = 0x5a;
    const std::uint8_t result = re_00c372b0(storage.bytes);
    assert(result == 0x5a);
    assert(g_callee_receiver ==
           reinterpret_cast<std::uintptr_t>(storage.bytes) + kReceiverAdjustorDelta);
  }

  // Case 3 (DECOY): a decoy byte is planted at receiver + 0x18, where a thunk
  // that DID NOT adjust would read, and the real byte at receiver + 0x7d0. The
  // reconstruction must return the real byte; a wrong adjustment reads the
  // decoy and fails this assertion.
  {
    Storage storage = {};
    reset();
    storage.bytes[kCalleeFieldDisplacement] = 0xa5;  // decoy: unadjusted read
    storage.bytes[kLastTouchedByte] = 0x5a;          // real: adjusted read
    const std::uint8_t result = re_00c372b0(storage.bytes);
    assert(result == 0x5a);
    assert(storage.bytes[kCalleeFieldDisplacement] == 0xa5);  // decoy untouched
  }

  // Case 4: the stack balance. The thunk pushes nothing and the callee's RET
  // returns to the caller, so ESP is unchanged across the call -- the
  // forwarded caller-cleanup fact, measured.
  {
    Storage storage = {};
    reset();
    const std::uintptr_t esp_before = esp_read();
    (void)re_00c372b0(storage.bytes);
    const std::uintptr_t esp_after = esp_read();
    assert(esp_before == esp_after);
  }

  // Case 5: the return width. The callee writes AL only, so the value that
  // comes back is one byte; the thunk returns it unchanged.
  {
    Storage storage = {};
    reset();
    storage.bytes[kLastTouchedByte] = 0xff;
    const std::uint8_t result = re_00c372b0(storage.bytes);
    assert(result == 0xff);
  }

  // Case 6 (MUTANT): the unadjusted-forwarding mutant is driven, and the test
  // requires the callee to have received the UNADJUSTED receiver -- the
  // observation that rejects it. The main cases' adjustment assertion is the
  // same assertion, aimed at the reconstruction.
  {
    Storage storage = {};
    reset();
    (void)re_00c372b0_unadjusted(storage.bytes);
    assert(g_callee_receiver == reinterpret_cast<std::uintptr_t>(storage.bytes));
  }

  return 0;
}
