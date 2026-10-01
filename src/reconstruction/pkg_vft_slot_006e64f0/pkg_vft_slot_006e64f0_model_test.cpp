// PKG-VFT-SLOT-006E64F0 -- VA 0x006e64f0
// Behavioural model test for the reconstruction of the 2-instruction body
//   0x006e64f0  LEA EAX,[ECX + 0x4]
//   0x006e64f3  RET
//
// There are no extern callees to define here as observers, and that absence
// is itself part of what the test asserts. The evidence pack records
// dependencies.callees = [], dependencies.edges with no outgoing row, and
// the machine dispatch record counts indirect_calls = 0, so the body
// reaches no other function. A reconstruction that acquired a callee would
// need a symbol this test does not define, and the link would fail --
// which is the check.
//
// What the listing fixes, and what each test below holds the
// reconstruction to:
//
//   * the return value. EAX is the receiver's address plus 0x4, for every
//     receiver -- the LEA is unconditional and the receiver is the only
//     input the body has. A reconstruction that used any other
//     displacement fails the first test.
//   * no memory access. LEA computes an address; it does not read or write
//     the bytes at it. Asserted on a PROT_NONE page (a read would fault)
//     and on a poisoned snapshot (a write would show).
//   * no stack effect. The RET is bare and no stack word is read, so the
//     callee pops nothing: a canary pushed before a raw thiscall must be
//     intact on return.
//   * the receiver arrives in ECX, not on the stack: the return value
//     tracks ECX, and a word the caller leaves in the outgoing-argument
//     area is ignored.
//   * no control flow. One path, one outcome.
//   * vftable slot placement. The body is slot 12 of the vptr-backed table
//     at 0x013faea0; the dispatch that reaches it is the two-level load
//     object -> vtable -> slot, and the test asserts that shape rather
//     than collapsing it to object -> slot.

#include "pkg_vft_slot_006e64f0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#if defined(__linux__)
#include <sys/mman.h>
#include <unistd.h>
#endif

namespace openspore::reconstruction::pkg_vft_slot_006e64f0 {
namespace {

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// A receiver big enough that any plausible displacement into it would
// still be inside the object, and poisoned so an unwritten byte stays
// distinguishable from a written one.
struct PoisonedReceiver {
  unsigned char bytes[256];
};

void fill_poison(PoisonedReceiver &receiver) {
  std::memset(receiver.bytes, 0xA5, sizeof receiver.bytes);
}

// Calls the reconstruction the way a vtable slot is reached: receiver in
// ECX, nothing pushed except a canary the callee must leave alone.
//
// The canary is the stack-discipline check. A thiscall declaration carrying
// one ordinary stack argument compiles to a `ret $4` terminator, which
// would pop the canary instead of the return address's neighbour; control
// would still return here, but (%esp) would then sit on this frame rather
// than on the canary, the comparison would fail, and the check below
// would report it. A `ret $8` body would not return here at all.
struct RawCallResult {
  void* eax = nullptr;
  bool canary_intact = false;
};

RawCallResult call_in_ecx(void* receiver) {
  RawCallResult result;
#if defined(__GNUC__) && defined(__i386__)
  void* eax_out = nullptr;
  unsigned char intact_out = 0;
  __asm__ volatile(
      "pushl $0x5a5a5a5a\n\t"
      "movl %[receiver], %%ecx\n\t"
      "call re_006e64f0\n\t"
      "movl %%eax, %%edx\n\t"
      "cmpl $0x5a5a5a5a, (%%esp)\n\t"
      "sete %%cl\n\t"
      "movl %%edx, %%eax\n\t"
      "movzbl %%cl, %%edx\n\t"
      "addl $4, %%esp\n\t"
      : "=&a"(eax_out), "=&d"(intact_out)
      : [receiver] "r"(receiver)
      : "ecx", "cc", "memory");
  result.eax = eax_out;
  result.canary_intact = (intact_out != 0u);
#else
  result.eax = re_006e64f0(receiver);
  result.canary_intact = true;
#endif
  return result;
}

// The return value of a call, with no hand-written assembly, for the paths
// that do not need to inspect the stack.
void* call_plain(void* receiver) {
  return re_006e64f0(receiver);
}

// 0x006e64f0  LEA EAX,[ECX + 0x4]
//
// The return value, for every receiver the test can offer. The receiver
// list is deliberately hostile: null, an unmapped low address, an
// all-ones word, and pointers into a poisoned object. A reconstruction
// that read even one bit of the receiver would either return something
// other than receiver + 0x4 for some entry or would fault.
void test_the_return_value_is_the_receiver_plus_0x4() {
  PoisonedReceiver receiver;
  fill_poison(receiver);

  void* const receivers[] = {
      nullptr,
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x00000001u)),
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0xFFFFFFFFu)),
      receiver.bytes,
      receiver.bytes + 1,
      receiver.bytes + 128,
      receiver.bytes + sizeof receiver.bytes,  // one past the end
      &g_failures,
  };

  for (std::size_t index = 0; index < sizeof receivers / sizeof receivers[0];
       ++index) {
    void* const expected = static_cast<unsigned char*>(receivers[index]) +
                           kReceiverByteDisplacement;
    check(call_plain(receivers[index]) == expected,
          "LEA EAX,[ECX + 0x4]: the return value is the receiver plus 0x4");
  }

  // The displacement is exactly the one the instruction states. This is
  // the mutation the first test exists to catch: a body that computed the
  // receiver plus any other displacement fails here for every receiver.
  check(call_plain(receiver.bytes) == receiver.bytes + 0x4u,
        "the displacement is 0x4, not 0x0 and not any larger field offset");
  check(call_plain(receiver.bytes) != receiver.bytes,
        "a bare [ECX] with no displacement is excluded: the value differs");
  check(call_plain(receiver.bytes) != receiver.bytes + 0x3cu,
        "the displacement is 0x4, not 0x3c");

  // The return is a single 32-bit register word: a pointer on this target.
  static_assert(sizeof(void*) == 4u, "the return value occupies one 32-bit register");
  check(sizeof(call_plain(receiver.bytes)) == 4u,
        "the return value is one 32-bit word");

  // Repeated calls are identical. A body with hidden state -- a counter,
  // a cached value, an anything -- would drift here.
  for (int repeat = 0; repeat < 8; ++repeat) {
    check(call_plain(receiver.bytes) == receiver.bytes + 0x4u,
          "repeated calls return the same value: the body is stateless");
  }
}

// The body performs no memory access, so it neither reads nor writes the
// receiver. The write half is checked by byte comparison against the
// poisoned snapshot; the read half is checked separately, on an unreadable
// page, because a body that read a byte and discarded it would leave the
// snapshot untouched.
void test_the_receiver_bytes_are_untouched() {
  PoisonedReceiver receiver;
  fill_poison(receiver);

  unsigned char before[sizeof receiver.bytes];
  std::memcpy(before, receiver.bytes, sizeof before);

  (void)call_plain(receiver.bytes);

  check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
        "no byte of the receiver is written: LEA stores nothing");
  check(receiver.bytes[0] == 0xA5u && receiver.bytes[255] == 0xA5u,
        "the first and last receiver bytes are still the poison value");
}

// A receiver on a page with no access permission at all. If the body read
// or wrote any byte through the receiver -- at any displacement -- the
// call would raise SIGSEGV and this test would not reach its first
// assertion. It is the direct test for the listing's complete absence of a
// memory access: LEA takes the receiver's address and nothing else.
void test_no_receiver_byte_is_ever_touched() {
#if defined(__linux__)
  const long page = sysconf(_SC_PAGESIZE);
  const std::size_t size = page > 0 ? static_cast<std::size_t>(page) : 4096u;
  void* const guarded = mmap(nullptr, size, PROT_NONE,
                             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (guarded == MAP_FAILED) {
    std::fprintf(stderr,
                 "skipped: mmap(PROT_NONE) unavailable, cannot test the "
                 "unreadable-receiver path\n");
    return;
  }

  check(call_plain(guarded) ==
            static_cast<unsigned char*>(guarded) + kReceiverByteDisplacement,
        "a receiver on an unreadable page still returns its address plus 0x4: "
        "no read");

  // Offsets into the page, so a displacement other than the one modelled is
  // covered too.
  check(call_plain(static_cast<unsigned char *>(guarded) + 1) ==
            static_cast<unsigned char *>(guarded) + 1 + kReceiverByteDisplacement,
        "receiver+1 on an unreadable page returns its address plus 0x4: no read");
  check(call_plain(static_cast<unsigned char *>(guarded) + size - 1) ==
            static_cast<unsigned char *>(guarded) + size - 1 + kReceiverByteDisplacement,
        "receiver+pagesize-1 on an unreadable page returns its address plus "
        "0x4: no read");

  munmap(guarded, size);
#else
  std::fprintf(stderr,
               "skipped: no mmap on this platform, cannot test the "
               "unreadable-receiver path\n");
#endif
}

// 0x006e64f3  RET, bare.
//
// The body pops nothing. The canary pushed before the raw call must still
// be on top of the stack when control comes back, for every receiver.
void test_the_body_pops_nothing_from_the_caller_stack() {
  PoisonedReceiver receiver;
  fill_poison(receiver);

  void* const receivers[] = {
      nullptr,
      receiver.bytes,
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x00000001u)),
  };

  for (std::size_t index = 0; index < sizeof receivers / sizeof receivers[0];
       ++index) {
    const RawCallResult raw = call_in_ecx(receivers[index]);
    check(raw.canary_intact,
          "RET is bare: the callee popped nothing, the caller's stack is intact");
    check(raw.eax ==
              static_cast<unsigned char*>(receivers[index]) +
                  kReceiverByteDisplacement,
          "the raw thiscall path returns the receiver plus 0x4");
  }
}

// The receiver really is the one in ECX, and the body really is indifferent
// to everything else the caller leaves behind. Two values that would fault
// if they were dereferenced, driven through the register rather than
// through an argument slot; and a word planted in the outgoing-argument
// area that a stack-receiver reconstruction would pick up instead.
void test_the_receiver_register_is_ecx_and_the_stack_is_ignored() {
  const RawCallResult low = call_in_ecx(
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x00000001u)));
  check(low.canary_intact, "the unmapped-receiver call leaves the stack intact");
  check(low.eax == reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x00000005u)),
        "ECX = 0x00000001 returns 0x00000005: the register is the receiver");

  const RawCallResult none = call_in_ecx(nullptr);
  check(none.eax == reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x00000004u)),
        "ECX = 0 returns 0x00000004: the register is the receiver");

  // A stack-receiver reconstruction reads the first callee-popped word.
  // Under thiscall nothing is popped, so there is no such word: the
  // outgoing-argument area belongs to the caller and the body never
  // reads it. Driven by the canary test above; stated here as the
  // positive claim that the return tracks ECX and nothing else.
  PoisonedReceiver receiver;
  fill_poison(receiver);
  check(call_in_ecx(receiver.bytes).eax == receiver.bytes + 0x4u,
        "the return tracks ECX, not a stack word the caller left behind");
}

// The body occupies slot +0x30 of the vptr-backed table based at
// 0x013faea0, and the image scan finds it in 66 such tables. These are
// data facts, read live from the image; the recorded values are not
// re-derivable from this binary, so they are asserted as recorded.
void test_the_recorded_vftable_membership() {
  check(kMembershipCount == 66u,
        "the image scan finds this body in 66 vptr-backed vftables");
  check(kFirstTableBase == 0x013faea0u, "the first table base is 0x013faea0");
  check(kFirstTableSlotIndex == 12u, "this body occupies slot 12 of that table");
  check(kFirstTableSlotByteOffset == 0x30u, "slot 12 is byte offset 0x30");
  check(kFirstTableSlotWord == 0x013faed0u,
        "the slot word is the table base plus the slot offset");
  check(kWordBelowFirstTableBase == 0x013fae9cu,
        "the word below the table base is at 0x013fae9c");
  check(kWordBelowFirstTableBaseValue == 0x00000000u,
        "the word below the table base is zero, which bounds the table");

  // Index 12 is the recorded slot for this body, and its immediate
  // neighbours are recorded too, so a reader can see the slot is bordered
  // by real entries.
  check(kFirstTableWordCount == 16u,
        "sixteen words of the table were recorded, starting at the base");
  check(kFirstTableWords[12] == 0x006e64f0u, "slot +0x30 holds this body's VA");
  check(kFirstTableWords[11] == 0x00606d60u, "slot +0x2c is recorded as 0x00606d60");
  check(kFirstTableWords[13] == 0x009892e0u, "slot +0x34 is recorded as 0x009892e0");

  // The call shape a slot entry holds: a 32-bit code pointer that takes the
  // receiver in ECX and returns a 32-bit word. The reconstruction's
  // address round-trips through that type.
  static_assert(sizeof(SlotFn) == 4u,
                "a slot entry is one 4-byte code pointer on x86-32");
  static_assert(sizeof(SlotEntry) == 4u, "a slot entry word is 4 bytes");

  SlotFn const code = re_006e64f0;
  SlotEntry entry = 0;
  std::memcpy(&entry, &code, sizeof entry);

  SlotFn dispatched = nullptr;
  std::memcpy(&dispatched, &entry, sizeof dispatched);
  check(dispatched == code,
        "the reconstruction's address round-trips through the slot word type");
}

// The dispatch that reaches this body is a two-level load: the object's
// first word is a vptr to the table, and the slot is a word of that table.
// The collapsed one-level reading -- object -> slot -- reads a word of the
// object's own storage instead, and must not reach this body. The
// distinction is the whole content of the vptr mechanism, so it is
// asserted rather than assumed.
void test_the_slot_is_reached_by_a_two_level_load() {
  // A local image of the recorded table, word for word, with slot 12
  // holding the reconstruction's own address: the recorded word is this
  // body's VA in the original image, which is not a pointer this process
  // can call, so the dispatch is exercised against the same shape with
  // the real target. The recorded word itself is asserted in
  // test_the_recorded_vftable_membership, where it is a data fact.
  OpaqueWord table[kFirstTableWordCount];
  std::memcpy(table, kFirstTableWords, sizeof table);
  table[kFirstTableSlotIndex] = reinterpret_cast<OpaqueWord>(re_006e64f0);

  // An object laid out the way the dispatch finds one: its first word is
  // the vptr, and the words after it are the object's own storage. They
  // are filled with an address that is not this body, so a collapsed
  // one-level load reads a different function and the distinction is
  // observable rather than notional.
  OpaqueWord object[kFirstTableWordCount];
  object[0] = reinterpret_cast<OpaqueWord>(table);
  for (std::size_t index = 1; index < kFirstTableWordCount; ++index) {
    object[index] = 0x00400000u;
  }

  // Level 1: object -> vtable.
  OpaqueWord* const vtable = reinterpret_cast<OpaqueWord*>(object[0]);
  check(vtable == table, "level 1: the object's vptr is the table base");

  // Level 2: vtable -> slot.
  SlotFn const slot = reinterpret_cast<SlotFn>(vtable[kFirstTableSlotIndex]);
  check(slot == re_006e64f0,
        "level 2: slot 12 of the table holds the reconstruction");

  // The collapsed one-level reading must NOT reach this body: it reads
  // the object's own word 12, which is not the slot.
  SlotFn const collapsed =
      reinterpret_cast<SlotFn>(object[kFirstTableSlotIndex]);
  check(collapsed != slot,
        "the collapsed one-level load reads a different word: the two-level "
        "shape is required");

  // Dispatching through the two-level load reaches the reconstruction and
  // returns the receiver plus 0x4.
  PoisonedReceiver receiver;
  fill_poison(receiver);
  check(slot(receiver.bytes) == receiver.bytes + kReceiverByteDisplacement,
        "dispatching through the two-level load returns the receiver plus 0x4");
}

// The single path. The body has no branch, so for a FIXED receiver there
// is no input that selects a different outcome: the plain call and the raw
// thiscall must agree, and a spread of receivers must each funnel to their
// own receiver plus 0x4 and to nothing else.
void test_there_is_exactly_one_outcome() {
  PoisonedReceiver receiver;
  fill_poison(receiver);

  void* const receivers[] = {
      receiver.bytes,
      receiver.bytes + 3,
      nullptr,
  };

  for (std::size_t index = 0; index < sizeof receivers / sizeof receivers[0];
       ++index) {
    void* const expected =
        static_cast<unsigned char*>(receivers[index]) + kReceiverByteDisplacement;
    check(call_plain(receivers[index]) == expected,
          "the plain call reaches the receiver plus 0x4");
    check(call_in_ecx(receivers[index]).eax == expected,
          "the raw thiscall reaches the same value: one path, one outcome");
  }
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_vft_slot_006e64f0

int main() {
  using namespace openspore::reconstruction::pkg_vft_slot_006e64f0;
  test_the_return_value_is_the_receiver_plus_0x4();
  test_the_receiver_bytes_are_untouched();
  test_no_receiver_byte_is_ever_touched();
  test_the_body_pops_nothing_from_the_caller_stack();
  test_the_receiver_register_is_ecx_and_the_stack_is_ignored();
  test_the_recorded_vftable_membership();
  test_the_slot_is_reached_by_a_two_level_load();
  test_there_is_exactly_one_outcome();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
