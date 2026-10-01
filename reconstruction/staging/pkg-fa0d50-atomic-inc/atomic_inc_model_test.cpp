#include "atomic_inc.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <thread>
#include <vector>

namespace {

using openspore::reconstruction::pkg_fa0d50_atomic_inc::Word;
using openspore::reconstruction::pkg_fa0d50_atomic_inc::kReceiverAdjust;

// The machine ABI asserted at compile time: a __thiscall member taking the
// receiver in ECX and nothing on the stack. Declaring the slot with any
// other signature fails to build, so the convention is a checked fact here
// rather than a comment.
std::uint32_t(PKG_FA0D50_ATOMIC_INC_THISCALL *const kReceiverSlot)(std::uint8_t*) =
    &openspore::reconstruction::pkg_fa0d50_atomic_inc::atomic_increment_00fa0d50;

struct Receiver {
  std::uint8_t pad[kReceiverAdjust];
  Word counter;
};

void FillCanary(Receiver& receiver) {
  std::memset(&receiver, 0xA5, sizeof(receiver));
}

}  // namespace

int main() {
  // The counter lives at receiver +0x14 (ADD ECX,0x14), not at offset 0: a
  // body that dropped the adjust reads the canary and returns 0xa6.
  Receiver receiver;
  FillCanary(receiver);
  receiver.counter = 41;
  Word const got = kReceiverSlot(reinterpret_cast<std::uint8_t*>(&receiver));
  assert(got == 42);
  assert(receiver.counter == 42);

  // XADD.LOCK leaves the OLD value in EAX and INC EAX makes the returned
  // word the NEW value: a body that dropped INC EAX returns 0 here.
  Receiver second;
  FillCanary(second);
  second.counter = 0;
  assert(kReceiverSlot(reinterpret_cast<std::uint8_t*>(&second)) == 1);
  assert(second.counter == 1);

  // Only the dword at +0x14 is written; the canary around it is intact.
  Receiver third;
  FillCanary(third);
  third.counter = 7;
  kReceiverSlot(reinterpret_cast<std::uint8_t*>(&third));
  for (std::size_t i = 0; i < kReceiverAdjust; ++i) {
    assert(third.pad[i] == 0xA5);
  }
  assert(third.counter == 8);

  // The LOCK prefix makes the read-modify-write one atomic step: concurrent
  // increments through the slot lose nothing, which a plain
  // read-then-write body does not.
  constexpr int kThreads = 4;
  constexpr int kPerThread = 2500;
  Receiver shared;
  FillCanary(shared);
  shared.counter = 0;
  std::vector<std::thread> workers;
  workers.reserve(kThreads);
  for (int t = 0; t < kThreads; ++t) {
    workers.emplace_back([&shared] {
      for (int i = 0; i < kPerThread; ++i) {
        kReceiverSlot(reinterpret_cast<std::uint8_t*>(&shared));
      }
    });
  }
  for (std::thread& worker : workers) {
    worker.join();
  }
  assert(shared.counter == kThreads * kPerThread);

  return 0;
}
