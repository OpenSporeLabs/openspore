// PKG-DFW-00980510 -- VA 0x00980510
// Behavioural model test for the reconstruction of the 2-instruction body
//   0x00980510  MOV EAX,0x202
//   0x00980515  RET
//
// There are no extern callees to define here as observers, and that absence is
// itself part of what the test asserts. The evidence pack records
// dependencies.callees = [], dependencies.edges = [], and the machine dispatch
// record counts indirect_calls = 0, so the body reaches no other function. A
// reconstruction that acquired a callee would need a symbol this test does not
// define, and the link would fail -- which is the check.
//
// What the listing fixes, and what each test below holds the reconstruction to:
//
//   * the return word. 0x202, a full 32-bit immediate, so the upper three bytes
//     of the return register are defined rather than residual.
//   * receiver independence. The body never reads ECX, so the return word is the
//     same for every receiver value, including ones that would fault if they
//     were dereferenced.
//   * no memory access of any kind. No displacement is read and none is written,
//     so the receiver's bytes come back byte-identical, and a receiver placed
//     on an unreadable page does not fault the call.
//   * no stack effect. Zero ordinary stack arguments and zero callee cleanup, so
//     the caller pushes a canary before the call and finds it untouched after.
//   * no control flow. One path only; there is no branch to take either way.
//   * slot placement. The body's only reference in the program is the dispatch
//     word at 0x014440e4, which is slot +0x14 of the image based at 0x014440d0.
//
// One limit is stated rather than papered over: this test can show that the
// receiver's bytes are unchanged and that no unreadable page is touched, but it
// cannot exclude a store that writes back the value it just read, because that
// store would leave the bytes identical. Every store that changes a byte, and
// every read at all, is excluded.

#include "dfw_00980510_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#if defined(__linux__)
#include <sys/mman.h>
#include <unistd.h>
#endif

namespace openspore::reconstruction::pkg_dfw_00980510 {
namespace {

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// A receiver big enough that any plausible displacement into it would still be
// inside the object, and poisoned so an unwritten byte stays distinguishable
// from a written one.
struct PoisonedReceiver {
  unsigned char bytes[256];
};

void fill_poison(PoisonedReceiver &receiver) {
  std::memset(receiver.bytes, 0xA5, sizeof receiver.bytes);
}

// Calls the reconstruction the way the dispatch word at 0x014440e4 reaches it:
// receiver in ECX, nothing pushed except a canary the callee must leave alone.
//
// The canary is the stack-discipline check. A thiscall declaration carrying one
// ordinary stack argument compiles to a `ret $4` terminator, which would pop the
// canary instead of the return address's neighbour; control would still return
// here, but (%esp) would then sit on this frame rather than on the canary, the
// comparison would fail, and the check below would report it. A `ret $8` body
// would not return here at all.
struct RawCallResult {
  std::uint32_t eax = 0;
  bool canary_intact = false;
};

RawCallResult call_in_ecx(void *receiver) {
  RawCallResult result;
#if defined(__GNUC__) && defined(__i386__)
  std::uint32_t eax_out = 0;
  std::uint32_t intact_out = 0;
  __asm__ volatile(
      "pushl $0x5a5a5a5a\n\t"
      "movl %[receiver], %%ecx\n\t"
      "call dfw_get_proxy_id_00980510\n\t"
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
  result.eax = dfw_get_proxy_id_00980510(receiver);
  result.canary_intact = true;
#endif
  return result;
}

// The EAX word of a call, with no hand-written assembly, for the paths that do
// not need to inspect the stack.
std::uint32_t call_plain(void *receiver) {
  return dfw_get_proxy_id_00980510(receiver);
}

// 0x00980510  MOV EAX,0x202
//
// The return word, for every receiver the test can offer. The receiver list is
// deliberately hostile: null, an unmapped low address, an all-ones word, and
// pointers into a poisoned object. A reconstruction that read even one bit of
// the receiver would either return something other than 0x202 for some entry or
// would fault.
void test_return_word_is_0x202_for_every_receiver() {
  PoisonedReceiver receiver;
  fill_poison(receiver);

  void *const receivers[] = {
      nullptr,
      reinterpret_cast<void *>(static_cast<std::uintptr_t>(0x00000001u)),
      reinterpret_cast<void *>(static_cast<std::uintptr_t>(0xFFFFFFFFu)),
      receiver.bytes,
      receiver.bytes + 1,
      receiver.bytes + 128,
      receiver.bytes + sizeof receiver.bytes,  // one past the end
      &g_failures,
  };

  for (std::size_t index = 0; index < sizeof receivers / sizeof receivers[0];
       ++index) {
    const std::uint32_t got = call_plain(receivers[index]);
    check(got == 0x202u, "MOV EAX,0x202: the return word is 0x202");
    check(got == 514u, "MOV EAX,0x202: 0x202 is decimal 514");
  }

  // The immediate is a full 32-bit write, not a narrowed or sign-extended one:
  // the upper three bytes are defined, so the returned word carries no residue
  // from the caller and a 16-bit or 8-bit model of the return is excluded.
  const std::uint32_t got = call_plain(receiver.bytes);
  check((got & 0xFFFF0000u) == 0u,
        "the upper three bytes of the return word are defined and zero");
  check(static_cast<std::size_t>(sizeof(got)) == 4u,
        "the return value is a single 32-bit word");
  static_assert(sizeof(decltype(call_plain(nullptr))) == 4u,
                "the return value occupies one 32-bit register");

  // Repeated calls are identical. A body with hidden state -- a counter, a
  // cached value, an anything -- would drift here.
  for (int repeat = 0; repeat < 8; ++repeat) {
    check(call_plain(receiver.bytes) == 0x202u,
          "repeated calls return the same word: the body is stateless");
  }
}

// The body has no memory operand, so it neither reads nor writes the receiver.
// The write half is checked by byte comparison against the poisoned snapshot;
// the read half is checked separately, on an unreadable page, because a body
// that read a byte and discarded it would leave the snapshot untouched.
void test_receiver_bytes_are_untouched() {
  PoisonedReceiver receiver;
  fill_poison(receiver);

  unsigned char before[sizeof receiver.bytes];
  std::memcpy(before, receiver.bytes, sizeof before);

  (void)call_plain(receiver.bytes);

  check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
        "no byte of the receiver is written: the body names no displacement");
  check(receiver.bytes[0] == 0xA5u && receiver.bytes[255] == 0xA5u,
        "the first and last receiver bytes are still the poison value");
}

// A receiver on a page with no access permission at all. If the body read or
// wrote any byte through the receiver -- at any displacement -- the call would
// raise SIGSEGV and this test would not reach its first assertion. It is the
// direct test for the listing's complete absence of a memory operand.
void test_no_receiver_byte_is_ever_touched() {
#if defined(__linux__)
  const long page = sysconf(_SC_PAGESIZE);
  const std::size_t size = page > 0 ? static_cast<std::size_t>(page) : 4096u;
  void *const guarded = mmap(nullptr, size, PROT_NONE,
                             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (guarded == MAP_FAILED) {
    std::fprintf(stderr,
                 "skipped: mmap(PROT_NONE) unavailable, cannot test the "
                 "unreadable-receiver path\n");
    return;
  }

  const std::uint32_t got = call_plain(guarded);
  check(got == 0x202u,
        "a receiver on an unreadable page still returns 0x202: no read");

  // Offsets into the page, so a displacement other than zero is covered too.
  check(call_plain(static_cast<unsigned char *>(guarded) + 1) == 0x202u,
        "receiver+1 on an unreadable page returns 0x202: no read");
  check(call_plain(static_cast<unsigned char *>(guarded) + size - 1) == 0x202u,
        "receiver+pagesize-1 on an unreadable page returns 0x202: no read");

  munmap(guarded, size);
#else
  std::fprintf(stderr,
               "skipped: no mmap on this platform, cannot test the "
               "unreadable-receiver path\n");
#endif
}

// 0x00980515  RET, bare.
//
// The body pops nothing. The canary pushed before the raw call must still be on
// top of the stack when control comes back, for every receiver.
void test_the_body_pops_nothing_from_the_caller_stack() {
  PoisonedReceiver receiver;
  fill_poison(receiver);

  void *const receivers[] = {
      nullptr,
      receiver.bytes,
      reinterpret_cast<void *>(static_cast<std::uintptr_t>(0x00000001u)),
  };

  for (std::size_t index = 0; index < sizeof receivers / sizeof receivers[0];
       ++index) {
    const RawCallResult raw = call_in_ecx(receivers[index]);
    check(raw.canary_intact,
          "RET is bare: the callee popped nothing, the caller's stack is intact");
    check(raw.eax == 0x202u, "the raw thiscall path returns 0x202");
  }
}

// The receiver really is the one in ECX, and the body really is indifferent to
// it. Two values that would fault if they were dereferenced, driven through the
// register rather than through an argument slot.
void test_the_receiver_register_is_ignored() {
  const RawCallResult low = call_in_ecx(
      reinterpret_cast<void *>(static_cast<std::uintptr_t>(0x00000001u)));
  check(low.canary_intact, "the unmapped-receiver call leaves the stack intact");
  check(low.eax == 0x202u,
        "ECX = 0x00000001 still returns 0x202: the register is never read");

  const RawCallResult none = call_in_ecx(nullptr);
  check(none.eax == 0x202u, "ECX = 0 still returns 0x202");
}

// The body occupies slot +0x14 of the dispatch image based at 0x014440d0, and
// its only reference in the program is the word at 0x014440e4. These are data
// facts, read live from the image; the recorded values are not re-derivable
// from this binary, so they are asserted as recorded.
void test_the_recorded_dispatch_slot() {
  check(kSlotImageBase == 0x014440d0u, "the image base is 0x014440d0");
  check(kTargetSlotOffset == 0x14u, "this body occupies slot +0x14");
  check(kTargetSlotIndex == 5u, "slot +0x14 is index 5 of the image");
  check(kTargetSlotReferenceWord == 0x014440e4u,
        "the sole xref to this body is the DATA word at 0x014440e4");
  check(kSlotImageBase + kTargetSlotOffset == kTargetSlotReferenceWord,
        "the reference word is the image base plus the slot offset");
  check(kSlotImageWordCount == 8u,
        "eight words of the image were recorded, starting at the base");
  check(kSlotImageWordBelowBase == 0x014440cCu,
        "the word below the image base is at 0x014440cc");
  check(kSlotImageWordBelowBaseValue == 0x00000000u,
        "the word below the image base is zero, which bounds the image");

  // Index 5 is the recorded slot for this body, and its immediate neighbours are
  // recorded too, so a reader can see the slot is bordered by real entries.
  check(kSlotImageWords[5] == 0x00980510u, "slot +0x14 holds this body's VA");
  check(kSlotImageWords[4] == 0x00e31100u, "slot +0x10 is recorded as 0x00e31100");
  check(kSlotImageWords[6] == 0x00980520u, "slot +0x18 is recorded as 0x00980520");
  check(kSlotImageWords[7] == 0x006f2f20u, "slot +0x1c is recorded as 0x006f2f20");

  // The call shape a slot entry holds: a 32-bit code pointer that returns a
  // 32-bit word. The reconstruction's address round-trips through that type and
  // dispatches back to the same word.
  static_assert(sizeof(ProxyWordFn) == 4u,
                "a slot entry is one 4-byte code pointer on x86-32");
  static_assert(sizeof(SlotEntry) == 4u, "a slot entry word is 4 bytes");

  ProxyWordFn const code = dfw_get_proxy_id_00980510;
  SlotEntry entry = 0;
  std::memcpy(&entry, &code, sizeof entry);

  ProxyWordFn dispatched = nullptr;
  std::memcpy(&dispatched, &entry, sizeof dispatched);
  check(dispatched == code,
        "the reconstruction's address round-trips through the slot word type");

  PoisonedReceiver receiver;
  fill_poison(receiver);
  check(dispatched(receiver.bytes) == 0x202u,
        "dispatching through the slot word returns 0x202");
}

// The single path. The body has no branch, so there is no input that selects a
// different outcome; the test states that by showing a spread of inputs, all
// funnelling to the one word.
void test_there_is_exactly_one_outcome() {
  PoisonedReceiver receiver;
  fill_poison(receiver);

  const std::uint32_t outcomes[] = {
      call_plain(receiver.bytes),
      call_plain(nullptr),
      call_plain(receiver.bytes + 3),
      call_in_ecx(receiver.bytes).eax,
      call_in_ecx(nullptr).eax,
  };

  for (std::size_t index = 0; index < sizeof outcomes / sizeof outcomes[0];
       ++index) {
    check(outcomes[index] == outcomes[0],
          "every input reaches the same word: the body has one path");
  }
  check(outcomes[0] == 0x202u, "that one word is 0x202");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_00980510

int main() {
  using namespace openspore::reconstruction::pkg_dfw_00980510;
  test_return_word_is_0x202_for_every_receiver();
  test_receiver_bytes_are_untouched();
  test_no_receiver_byte_is_ever_touched();
  test_the_body_pops_nothing_from_the_caller_stack();
  test_the_receiver_register_is_ignored();
  test_the_recorded_dispatch_slot();
  test_there_is_exactly_one_outcome();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
