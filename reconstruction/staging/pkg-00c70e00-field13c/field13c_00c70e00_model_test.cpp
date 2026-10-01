// Focused semantic test for FUN_00c70e00 @ 0x00c70e00.
//
// The target body is six instructions and every one of them is load-bearing,
// so this reconstruction has four questions to answer, not one:
//
//   1. IS THE GUARD RIGHT? 0x00c70e06/0x00c70e08 test the LOADED WORD, and
//      the branch's rel8 is the length of the jump it skips, so the null arm
//      is 0x00c70e0f and the non-null arm is the entire tail transfer.
//   2. WHAT IS TRANSFERRED? 0x00c70e0a jumps with ECX still holding the word
//      0x00c70e00 loaded, so 0x00b8dab0 receives THAT word as its own
//      receiver. This is a claim about a register's contents across a
//      transfer, and it is the claim most easily got wrong.
//   3. WHAT COMES BACK? Both paths write a full dword of EAX - the tail
//      target's `MOV EAX,[ECX+0x194]` and `MOV EAX,imm32` - and the null arm's
//      constant is exactly 1.
//   4. WHAT DOES THE BODY TOUCH? One 32-bit read at displacement 0x13c, and
//      nothing written anywhere.
//
// Each group below names the hypothesis it tries to REFUTE:
//
//   A. the guard is on the LOADED WORD and its null arm returns 1;
//   B. the transferred object is the word at +0x13c and nothing else -
//      proved by value discrimination against THREE fully-formed decoy
//      receivers, not by a comparison of one expected value (see the arena
//      note below; this is the 0068f9b0 lesson and it is the heart of the
//      test);
//   C. 0x13c is a BYTE displacement, not an index and not a doubled value;
//   D. the body reads and never writes;
//   E. the value crosses verbatim and no truthiness filter or clamp exists;
//   F. a wrong DISPATCH TARGET is observable, and the callable sentinel placed
//      immediately past the last modelled slot is proven live rather than
//      assumed;
//   G. the ABI is ECX receiver / 0 stack arguments / caller cleanup, MEASURED
//      by sampling ESP across the call;
//   H. the encoding IS the observed 21 bytes, and the two addresses the
//      branch and the jump name are COMPUTED from the encoded operands rather
//      than restated, so a wrong rel8 or rel32 fails here;
//   I. the sampled call sites' ordered comparisons behave as the binary's do.
//
// A NOTE ON THE ARENA IN GROUPS B AND C, AND WHY IT IS BUILT THIS WAY.
//
// The reconstruction reads a pointer out of its receiver at +0x13c and hands
// that pointer to a function that reads +0x194 of whatever it is given. That
// shape has a failure mode that is worse than a crash: if the pointer at +0x13c
// is wrong by four bytes, and the four bytes after the modelled receiver happen
// to contain a perfectly good object, then the wrong reconstruction reads a
// valid word at a valid +0x194, returns a plausible value, and the test passes.
// The package pkg_job_continuation_0068f9b0 failed exactly that way: a vtable
// slot read at the wrong byte offset aliased a neighbouring valid pointer and
// the dispatch silently succeeded.
//
// The fix is to make every wrong choice land on something that WORKS. The arena
// below therefore holds FOUR fully-formed 0x198-byte tail receivers, each with
// a DIFFERENT word planted at its own +0x194:
//
//   +0x13c -> the planted receiver     -> returns kPlantedTailWord
//   +0x138 -> the near decoy           -> returns kNearDecoyTailWord
//   +0x140 -> the far decoy            -> returns kFarDecoyTailWord
//   (address of the word itself)       -> returns kAddressOfWordTrap
//   (this body's own receiver)         -> returns kSelfPassThroughTrap
//
// so a reconstruction that reads one word too low, one word too high, the
// ADDRESS of the word, or its own receiver through, returns a value that is
// wrong and DISTINGUISHABLE, and the assertion names which mistake was made.
// Nothing here relies on an out-of-bounds access faulting, and nothing relies
// on a wrong value merely differing from the right one by luck: each wrong
// choice has a value reserved for it and nothing else produces that value.
//
// The arena's neighbours are also fully formed rather than left as filler, and
// the filler itself is a non-zero ramp, so a read of ANY byte of the arena is
// visible in the result and a write to ANY byte of it is visible in the image.

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "field13c_00c70e00.hpp"

// The header undefines its convention macro, so the modelled ABI types are
// respelled here; they are the same thiscall pointer types the entry declares.
#if defined(_MSC_VER)
#define PKG_00C70E00_THISCALL __thiscall
#else
#define PKG_00C70E00_THISCALL __attribute__((thiscall))
#endif

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c70e00 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00c70e00_field13c {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

SlotWord pointer_word(const void* pointer) {
  return static_cast<SlotWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

// ---------------------------------------------------------------------------
// The arena
// ---------------------------------------------------------------------------

constexpr std::size_t kLeadCanaryOffset = 0x000;
constexpr std::size_t kLeadCanaryBytes = 0x040;
constexpr std::size_t kReceiverOffset = 0x040;   // 0x140 bytes -> ends 0x180
constexpr std::size_t kFarDecoyOffset = 0x180;   // 0x198 bytes -> ends 0x318
constexpr std::size_t kNearDecoyOffset = 0x318;  // 0x198 bytes -> ends 0x4b0
constexpr std::size_t kPlantedOffset = 0x4b0;    // 0x198 bytes -> ends 0x648
constexpr std::size_t kTrailCanaryOffset = 0x648;
constexpr std::size_t kTrailCanaryBytes = 0x040;
constexpr std::size_t kArenaBytes = kTrailCanaryOffset + kTrailCanaryBytes;

// The displacement under test, and the two words either side of it. 0x13c is
// the header's kFieldDisplacement; the neighbours are one word lower and one
// word higher, and BOTH are made to hand over a real receiver.
constexpr std::size_t kFieldOffset = 0x13c;
constexpr std::size_t kNearNeighbourOffset = 0x138;
constexpr std::size_t kFarNeighbourOffset = 0x140;
constexpr std::size_t kRightNeighbourOffset = 0x140;

// Where the four decoy traps live INSIDE the arena, i.e. what a wrong
// transfer reads at its own +0x194. These are the values reserved for the four
// wrong answers; nothing else in the test produces them.
constexpr std::size_t kPlantedTailWordAt = kPlantedOffset + 0x194;
constexpr std::size_t kNearDecoyWordAt = kNearDecoyOffset + 0x194;
constexpr std::size_t kFarDecoyWordAt = kFarDecoyOffset + 0x194;
// A transfer of the ADDRESS of the word at +0x13c would read here. That lands
// inside the FAR DECOY, which is a fully-formed receiver, so the mistake is
// caught by a reserved value rather than by a fault - the same discipline the
// one-word-low and one-word-high traps use.
constexpr std::size_t kAddressOfWordTrapAt = kReceiverOffset + kFieldOffset + 0x194;
// A transfer of this body's OWN receiver would read here, inside the far
// decoy - which is why that decoy is a fully-formed receiver and not filler.
constexpr std::size_t kSelfPassThroughTrapAt = kReceiverOffset + 0x194;

alignas(4) std::uint8_t g_arena[kArenaBytes];

// Values reserved for the four wrong answers of group B. Each is distinct from
// every other and from every value the correct reconstruction can return, and
// from the null arm's 1.
constexpr SlotWord kPlantedTailWord = 0x5a5aa5a5u;
constexpr SlotWord kNearDecoyTailWord = 0x13579bdfu;
constexpr SlotWord kFarDecoyTailWord = 0x0badf00du;
constexpr SlotWord kAddressOfWordTrap = 0x00c0ffeeu;
constexpr SlotWord kSelfPassThroughTrap = 0xdecafbadu;

// The value the callable sentinel returns. Reserved for it alone.
constexpr SlotWord kSentinelReturn = 0x5e4714e1u;
// The value a plausible-but-wrong dispatch target returns.
constexpr SlotWord kDecoyTargetReturn = 0x0ddba11u;

static_assert(kFieldOffset == kFieldDisplacement,
              "the test's offset is the header's displacement");
static_assert(kNearNeighbourOffset + 4u == kFieldOffset,
              "the planted left neighbour ends where the field begins");
static_assert(kFieldOffset + 4u == kRightNeighbourOffset,
              "the planted right neighbour begins where the field ends");
static_assert(kNearNeighbourOffset == kFieldDisplacement - 4u,
              "the left neighbour is one word low");
static_assert(kRightNeighbourOffset == kFieldDisplacement + 4u,
              "the right neighbour is one word high");
static_assert(kPlantedTailWordAt < kArenaBytes, "the planted trap is in range");
static_assert(kNearDecoyWordAt < kArenaBytes, "the near trap is in range");
static_assert(kFarDecoyWordAt < kArenaBytes, "the far trap is in range");
static_assert(kAddressOfWordTrapAt < kArenaBytes,
              "the address-of-word trap is in range");
static_assert(kSelfPassThroughTrapAt < kArenaBytes,
              "the self pass-through trap is in range");
static_assert(kSelfPassThroughTrapAt >= kFarDecoyOffset &&
                  kSelfPassThroughTrapAt < kFarDecoyOffset + 0x198u,
              "a self pass-through lands inside the far decoy, which is why "
              "that region is a real receiver and not filler");
static_assert(kAddressOfWordTrapAt >= kFarDecoyOffset &&
                  kAddressOfWordTrapAt < kFarDecoyOffset + 0x198u,
              "an address-of-word transfer lands inside the far decoy, which "
              "is a real receiver, so that mistake is caught by value and not "
              "by a fault");
static_assert(kAddressOfWordTrapAt != kFarDecoyWordAt,
              "the address-of-word trap and the far-decoy word are at different "
              "places, so a one-word-high read and an address-of-word read are "
              "two distinguishable mistakes rather than one");
static_assert(kPlantedTailWord != kNearDecoyTailWord &&
                  kPlantedTailWord != kFarDecoyTailWord &&
                  kPlantedTailWord != kAddressOfWordTrap &&
                  kPlantedTailWord != kSelfPassThroughTrap,
              "the five tags are pairwise distinct, so no two mistakes are "
              "confusable with one another");
static_assert(kNearDecoyTailWord != kFarDecoyTailWord &&
                  kNearDecoyTailWord != kAddressOfWordTrap &&
                  kNearDecoyTailWord != kSelfPassThroughTrap &&
                  kFarDecoyTailWord != kAddressOfWordTrap &&
                  kFarDecoyTailWord != kSelfPassThroughTrap &&
                  kAddressOfWordTrap != kSelfPassThroughTrap,
              "no two of the four wrong-answer tags collide");
static_assert(kPlantedTailWord != 1u && kNearDecoyTailWord != 1u &&
                  kFarDecoyTailWord != 1u && kAddressOfWordTrap != 1u &&
                  kSelfPassThroughTrap != 1u,
              "the null arm's constant 1 is not any trap tag");

// ---------------------------------------------------------------------------
// A dispatch table with a callable SENTINEL immediately past its last slot.
// ---------------------------------------------------------------------------

using TailTargetFn = SlotWord(PKG_00C70E00_THISCALL*)(OpaqueTailReceiver*);

// The listing names exactly ONE transfer target (0x00b8dab0), so the table
// models one real slot plus one trap. The trap is a real function with a
// reserved return value, deliberately placed in the word IMMEDIATELY after the
// last modelled slot - so a dispatch that reads one slot too far is recorded by
// its return value instead of landing on whatever the allocator happened to
// put next. See group F: the trap is proved live there, not assumed.
struct TailTargetTable {
  TailTargetFn modelled_b8dab0;
  TailTargetFn sentinel;
};

static_assert(sizeof(TailTargetTable) == 2u * sizeof(void*),
              "one modelled slot plus one trap, both code pointers");
static_assert(offsetof(TailTargetTable, modelled_b8dab0) == 0u,
              "the modelled slot is the first word");
static_assert(offsetof(TailTargetTable, sentinel) == sizeof(void*),
              "the sentinel occupies the word immediately past the last "
              "modelled slot, which is the whole point of placing it");

TailTargetTable g_targets;

// A plausible wrong target: callable, thiscall, and NOT the one the JMP names.
SlotWord PKG_00C70E00_THISCALL decoy_tail_target(OpaqueTailReceiver*) {
  return kDecoyTargetReturn;
}

// Reached only by a dispatch that reads the word past the last modelled slot.
// It records itself by returning a value reserved for it alone, so the
// assertion that fails is about WHICH target was dispatched rather than about
// a wild jump.
SlotWord PKG_00C70E00_THISCALL sentinel_tail_target(OpaqueTailReceiver*) {
  return kSentinelReturn;
}

// ---------------------------------------------------------------------------
// Arena access
// ---------------------------------------------------------------------------

void store_word(std::size_t arena_offset, SlotWord value) {
  std::memcpy(g_arena + arena_offset, &value, sizeof(value));
}

SlotWord load_word(std::size_t arena_offset) {
  SlotWord value = 0;
  std::memcpy(&value, g_arena + arena_offset, sizeof(value));
  return value;
}

// The receiver of the target function, as a typed view of the arena.
OpaqueReceiver* receiver() {
  return reinterpret_cast<OpaqueReceiver*>(g_arena + kReceiverOffset);
}

// One of the fully-formed tail receivers in the arena.
OpaqueTailReceiver* tail_at(std::size_t arena_offset) {
  return reinterpret_cast<OpaqueTailReceiver*>(g_arena + arena_offset);
}

// Fill every byte with a distinctive non-zero ramp, then lay the canaries and
// the five trap words. A read of ANY part of the arena is therefore visible in
// the returned value, and a write to ANY part is visible in the byte image.
void plant_arena() {
  for (std::size_t index = 0; index < kArenaBytes; ++index) {
    g_arena[index] = static_cast<std::uint8_t>((index * 7u + 3u) & 0xffu);
  }
  std::memset(g_arena + kLeadCanaryOffset, 0xa5, kLeadCanaryBytes);
  std::memset(g_arena + kTrailCanaryOffset, 0x5a, kTrailCanaryBytes);

  // The word at +0x13c points at the planted receiver. Both neighbours point
  // at real decoy receivers, so a one-word-low or one-word-high read hands the
  // tail a perfectly usable object and the mistake shows up in the VALUE.
  store_word(kReceiverOffset + kFieldOffset,
             pointer_word(g_arena + kPlantedOffset));
  store_word(kReceiverOffset + kNearNeighbourOffset,
             pointer_word(g_arena + kNearDecoyOffset));
  store_word(kReceiverOffset + kFarNeighbourOffset,
             pointer_word(g_arena + kFarDecoyOffset));

  // And the four words a wrong transfer reads at its own +0x194.
  store_word(kPlantedTailWordAt, kPlantedTailWord);
  store_word(kNearDecoyWordAt, kNearDecoyTailWord);
  store_word(kFarDecoyWordAt, kFarDecoyTailWord);
  store_word(kAddressOfWordTrapAt, kAddressOfWordTrap);
  store_word(kSelfPassThroughTrapAt, kSelfPassThroughTrap);

  g_targets.modelled_b8dab0 = &field_194_getter_00b8dab0;
  g_targets.sentinel = &sentinel_tail_target;
}

// ---------------------------------------------------------------------------
// Calling the entry
// ---------------------------------------------------------------------------

SlotWord entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&field13c_00c70e00));
}

// THE TRAMPOLINES' SHAPE, AND WHY IT IS THIS SHAPE. Three spellings were
// measured on this toolchain (g++ 16.2.1, clang++ 22.1.8, both -m32 -O0/-O1/
// -O2) and two of them failed, each in a way that reads exactly like a
// reconstruction defect:
//
//  (1) receiver and target in "r" constraints. The compiler is free to give the
//      call target and the receiver the SAME register, so `movl %[recv], %%ecx`
//      overwrites the target and the `call *` branches into the middle of the
//      arena.
//  (2) both operands as "m", so no register can be allocated at all. This fixed
//      (1) and then failed differently: with the operands at file scope - which
//      is where -fPIC forces them to become GOT-relative - g++ -O1 held the GOT
//      base in EDX across the call and computed the POST-call operand address
//      from it. The callee uses EDX as its own scratch (`mov 0x13c(%ecx),%edx`),
//      so the second sample was written through a clobbered base. Confirmed by
//      disassembly, and reproduced with the samples as plain function locals too.
//
// What is left has NO memory operand in any block that contains a call, and it
// pins the two operands to FIXED registers through "+c" and "+d", so neither
// allocation nor aliasing is possible:
//
//  * the receiver goes in ECX, which is what thiscall requires and what the
//    measured ABI asserts;
//  * the target goes in EDX, which the callee may clobber but never before the
//    CPU has already read it to take the transfer - so nothing after the call
//    depends on EDX;
//  * the result comes back in EAX through "=a", which is the return register
//    the machine record names, so the trampoline asserts the ABI rather than
//    assuming it.
//
// The target still goes through a variable as well, so the compiler cannot
// inline the body and destroy the very thing being measured.
//
// The plain call through a thiscall function pointer: receiver in ECX, nothing
// pushed, callee pops nothing.
SlotWord call_entry(OpaqueReceiver* recv) {
  std::uint32_t receiver_reg = pointer_word(recv);
  std::uint32_t target_reg = entry_address();
  std::uint32_t result = 0;
  __asm__ __volatile__("call *%2\n\t"
                       : "=a"(result), "+c"(receiver_reg), "+d"(target_reg)
                       :
                       : "memory");
  return result;
}

// ESP sampled before the call and the instant the callee has returned.
//
// A NOTE ON WHY THIS IS A MEASUREMENT AND NOT A COMMENT. `call` pushes a
// return address and `RET` pops it, so ESP is identical either side of a call
// whose callee owns no cleanup; a `RET 0x4` body would leave the second sample
// four bytes lower. The recorded tail at 0x00c70e14 is 0xc3, so zero bytes of
// callee cleanup is the expectation, and a reconstruction that grew a
// stack-argument interface fails the measurement rather than merely being
// named wrong.
//
// WHY THIS ONE USES A DIRECT CALL AND NO MEMORY OPERANDS. Two earlier
// spellings were measured and both failed under g++ -O1/-O2 with a sample that
// did not match the one just taken, which reads exactly like a reconstruction
// that failed to balance its stack:
//
//   (a) one asm block that sampled ESP, made the call and sampled ESP again,
//       with the two samples in function-local "=m" operands and the result
//       returned through an sret pointer. The samples were read back correctly
//       out of the callee, but the CALLER then read the struct members from
//       slots that were not the ones the callee had written.
//   (b) the same block with the samples at file scope as volatile, which moves
//       the operands into the GOT-relative addressing that -fPIC requires for
//       file-scope data. The generated code held the GOT base in EDX across
//       the call and computed the post-call operand address from it; the callee
//       uses EDX as its own scratch (`mov 0x13c(%ecx),%edx`), so the second
//       sample was written through a clobbered base and the slot kept its
//       initial value. Verified in the disassembly.
//
// What is left has NO memory operand anywhere and only two single-instruction
// asm blocks, each of which is a scheduling barrier because of its "memory"
// clobber: the sample before, a plain C++ call, the sample after. A direct
// call cannot be inlined, because `field13c_00c70e00` is defined in another
// translation unit and this build does not use LTO; it also cannot become a
// sibling call, because more code follows it in this function. So the call
// really is a call, and ESP either side of it is exactly the measurement.
// Nothing about what is measured has been weakened to get there.
volatile std::uint32_t g_esp_before_call = 0;
volatile std::uint32_t g_esp_after_return = 0;

SlotWord call_entry_measured(OpaqueReceiver* recv) {
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %0" : "=r"(before) : : "memory");
  const SlotWord result = field13c_00c70e00(recv);
  __asm__ __volatile__("movl %%esp, %0" : "=r"(after) : : "memory");
  g_esp_before_call = before;
  g_esp_after_return = after;
  return result;
}

// A reference call of the modelled tail target, through the table, so the
// entry's answer can be compared with what the tail target itself returns for
// the same object. The table indirection is deliberate: it is the only place
// in the test where the target is reached through a slot, so that group F can
// measure the slot discipline.
SlotWord call_tail_through_slot(OpaqueTailReceiver* recv) {
  // The VALUE stored in the slot, not the address of the slot: a target
  // address that is the address of the table would branch into the table.
  TailTargetFn const slot = g_targets.modelled_b8dab0;
  std::uint32_t receiver_reg = pointer_word(recv);
  std::uint32_t target_reg =
      pointer_word(reinterpret_cast<const void*>(slot));
  std::uint32_t result = 0;
  __asm__ __volatile__("call *%2\n\t"
                       : "=a"(result), "+c"(receiver_reg), "+d"(target_reg)
                       :
                       : "memory");
  return result;
}

// ---------------------------------------------------------------------------
// A. The guard is on the LOADED WORD, and the null arm returns 1.
// ---------------------------------------------------------------------------

void test_null_word_returns_the_listing_constant() {
  plant_arena();
  store_word(kReceiverOffset + kFieldOffset, 0u);

  const SlotWord result = call_entry(receiver());

  // 0x00c70e0f is `b8 01 00 00 00`. Exactly that constant, no more.
  check(result == 1u);
  check(result == kNullArmReturn);
  check(result != 0u);
  check(result != 2u);
  check(result != 0xffffffffu);
  // And the tail transfer did NOT happen. Had the guard been dropped the
  // transfer would have handed 0x00b8dab0 a null receiver and read at 0x194,
  // which faults; had it been inverted, a null word would have produced a tail
  // value instead of 1.
  check(result != kPlantedTailWord);
  check(result != kNearDecoyTailWord);
  check(result != kFarDecoyTailWord);
  check(result != kAddressOfWordTrap);
  check(result != kSelfPassThroughTrap);
  check(result != kSentinelReturn);

  // The guard tests the word and not the receiver. A guard on the receiver
  // pointer itself would have taken the tail arm for this very call, because
  // the receiver is non-null.
  check(receiver() != nullptr);
  check(load_word(kReceiverOffset + kFieldOffset) == 0u);
}

// ---------------------------------------------------------------------------
// B. The transferred object is the word at +0x13c and nothing else.
// ---------------------------------------------------------------------------

void test_transferred_object_is_the_word_at_0x13c() {
  plant_arena();
  OpaqueTailReceiver* const planted = tail_at(kPlantedOffset);

  const SlotWord result = call_entry(receiver());

  // The right answer: the word 0x00c70e00 loaded at +0x13c was transferred, and
  // 0x00b8dab0 read +0x194 of THAT object.
  check(result == kPlantedTailWord);
  check(result == load_word(kPlantedTailWordAt));
  check(result == call_tail_through_slot(planted));

  // Not one word low: the near decoy is a fully-formed receiver with its own
  // distinguishable word, so this mistake cannot pass by accident.
  check(result != kNearDecoyTailWord);
  check(load_word(kNearDecoyWordAt) == kNearDecoyTailWord);
  check(pointer_word(tail_at(kNearDecoyOffset)) ==
        load_word(kReceiverOffset + kNearNeighbourOffset));

  // Not one word high: same discipline, same reason.
  check(result != kFarDecoyTailWord);
  check(load_word(kFarDecoyWordAt) == kFarDecoyTailWord);
  check(pointer_word(tail_at(kFarDecoyOffset)) ==
        load_word(kReceiverOffset + kFarNeighbourOffset));

  // Not the ADDRESS of the word at +0x13c. That lands inside the planted
  // receiver and is caught by value, not by a fault.
  check(result != kAddressOfWordTrap);
  check(pointer_word(receiver() + 1) != pointer_word(planted));

  // Not this body's own receiver passed straight through.
  check(result != kSelfPassThroughTrap);

  // THE CHAIN, TRACKED ACROSS SEVERAL DISTINCT OBJECTS. Four further receivers
  // are planted, each with a different word at its own +0x194, and the answer
  // must follow the word AT +0x13c each time. A reconstruction that cached, or
  // that read some other slot, would answer with the first object's value
  // again.
  struct Case {
    std::size_t receiver_offset;
    std::size_t tail_offset;
    SlotWord expected;
  };
  const Case cases[] = {
      {kReceiverOffset + 0x00u, kPlantedOffset, 0x11111111u},
      {kReceiverOffset + 0x40u, kFarDecoyOffset, 0x22222222u},
      {kReceiverOffset + 0x80u, kNearDecoyOffset, 0x33333333u},
      {kReceiverOffset + 0x100u, kPlantedOffset, 0x44444444u},
  };
  for (std::size_t index = 0; index < sizeof(cases) / sizeof(cases[0]); ++index) {
    const Case& entry = cases[index];
    const std::size_t word_at = entry.tail_offset + 0x194u;
    store_word(word_at, entry.expected);
    store_word(entry.receiver_offset + kFieldOffset,
               pointer_word(g_arena + entry.tail_offset));

    OpaqueReceiver* alt = reinterpret_cast<OpaqueReceiver*>(
        g_arena + entry.receiver_offset);
    const SlotWord answer = call_entry(alt);

    check(answer == entry.expected);
    check(answer == load_word(word_at));
  }

  // The four cases really are four different answers, and none of them is the
  // planted tag: otherwise a reconstruction that always answered with the
  // first object would slip through the sweep above.
  for (std::size_t left = 0; left < 4u; ++left) {
    check(cases[left].expected != kPlantedTailWord);
    for (std::size_t right = left + 1u; right < 4u; ++right) {
      check(cases[left].expected != cases[right].expected);
    }
  }

  // And the answer is a function of the WORD, not of anything ambient: making
  // the word null changes it to 1 and back again. The arena is re-planted
  // first, because the sweep above deliberately overwrote the planted tag.
  plant_arena();
  store_word(kReceiverOffset + kFieldOffset, 0u);
  check(call_entry(receiver()) == 1u);
  store_word(kReceiverOffset + kFieldOffset, pointer_word(g_arena + kPlantedOffset));
  check(call_entry(receiver()) == kPlantedTailWord);

  // The header's named accessor and the entry's literal arithmetic are one and
  // the same address, which is the statement that stops the two spellings from
  // drifting apart silently. `field_at` returns the ADDRESS of the word; the
  // entry loads the word stored there, and these three lines are the whole
  // chain written out: address of the word, value in the word, value that
  // receiver's own +0x194 word.
  OpaqueTailReceiver* const word_address =
      field_at(receiver(), kFieldDisplacement);
  check(reinterpret_cast<std::uint8_t*>(word_address) ==
        g_arena + kReceiverOffset + kFieldOffset);
  check(load_word(kReceiverOffset + kFieldOffset) == pointer_word(planted));
  check(pointer_word(word_address) != pointer_word(planted));
  check(load_word(kReceiverOffset + kNearNeighbourOffset) ==
        pointer_word(tail_at(kNearDecoyOffset)));
  check(load_word(kReceiverOffset + kRightNeighbourOffset) ==
        pointer_word(tail_at(kFarDecoyOffset)));
  check(word_address != reinterpret_cast<OpaqueTailReceiver*>(receiver()));
  check(pointer_word(receiver() + 1) != pointer_word(word_address));
  check(tail_field_at(planted, kTailTargetDisplacement) == kPlantedTailWord);
}

// ---------------------------------------------------------------------------
// C. 0x13c is a BYTE displacement, not an index and not a doubled value.
// ---------------------------------------------------------------------------

void test_displacement_is_bytes_not_an_index() {
  plant_arena();

  const SlotWord result = call_entry(receiver());

  check(kFieldDisplacement == 0x13cu);
  check(kFieldDisplacement == 316u);
  check(kFieldIndexInWords == 79u);
  // Read as an element COUNT the disp32 would address word 0x13c, i.e. byte
  // 0x4f0, which is past the modelled extent of this body's receiver.
  check((kFieldDisplacement * kFieldWidth) > sizeof(OpaqueReceiver));
  check((2u * kFieldDisplacement) > sizeof(OpaqueReceiver));
  // Read as a WORD index it would address word 79 = byte 0x13c, which is the
  // same word; so the word-index reading is the byte reading here and cannot be
  // separated by value, and the reason the field offset is claimed as BYTES is
  // the encoding: ModRM 0x89 has mod=10, so a disp32 of BYTES follows.
  check((kFieldIndexInWords * kFieldWidth) == kFieldDisplacement);
  check(kTargetEncoding[1] == 0x89u);
  check((kTargetEncoding[1] >> 6) == 2u);
  // And the modelled receiver really does end at the byte after the field.
  check(kFieldOffset + sizeof(SlotWord) == sizeof(OpaqueReceiver));
  // The two displacements belong to two different objects, and the tail's is
  // strictly beyond this body's receiver - the check that stops the two
  // receivers being merged.
  check(kTailTargetDisplacement == 0x194u);
  check(kTailTargetDisplacement > sizeof(OpaqueReceiver));
  check(kTailTargetDisplacement != kFieldDisplacement);
  check(kTailTargetDisplacement + sizeof(SlotWord) == sizeof(OpaqueTailReceiver));
  check(result == kPlantedTailWord);
}

// ---------------------------------------------------------------------------
// D. The body reads. Every byte of the arena is unchanged across the call.
// ---------------------------------------------------------------------------

void test_body_writes_nothing() {
  plant_arena();
  std::uint8_t before[kArenaBytes];
  std::memcpy(before, g_arena, kArenaBytes);

  const SlotWord result = call_entry(receiver());
  check(result == kPlantedTailWord);

  check(std::memcmp(before, g_arena, kArenaBytes) == 0);

  // The null arm too: a reconstruction that published its constant into the
  // receiver would leave a mark that only this path could make.
  store_word(kReceiverOffset + kFieldOffset, 0u);
  std::memcpy(before, g_arena, kArenaBytes);
  check(call_entry(receiver()) == 1u);
  check(std::memcmp(before, g_arena, kArenaBytes) == 0);

  // Explicitly: the word at +0x13c is not cleared on the null path, so the
  // null arm is a RETURN and not a consume-and-publish.
  check(load_word(kReceiverOffset + kFieldOffset) == 0u);
  store_word(kReceiverOffset + kFieldOffset, pointer_word(g_arena + kPlantedOffset));
  std::memcpy(before, g_arena, kArenaBytes);
  check(call_entry(receiver()) == kPlantedTailWord);
  check(std::memcmp(before, g_arena, kArenaBytes) == 0);
  check(load_word(kReceiverOffset + kFieldOffset) ==
        pointer_word(g_arena + kPlantedOffset));
  // The canaries are intact, so nothing overran the arena either.
  for (std::size_t index = 0; index < kLeadCanaryBytes; ++index) {
    check(g_arena[kLeadCanaryOffset + index] == 0xa5u);
  }
  for (std::size_t index = 0; index < kTrailCanaryBytes; ++index) {
    check(g_arena[kTrailCanaryOffset + index] == 0x5au);
  }
}

// ---------------------------------------------------------------------------
// E. The value crosses verbatim; no clamp, mask or truthiness filter exists.
// ---------------------------------------------------------------------------

void test_value_crosses_verbatim() {
  const SlotWord interesting[] = {0u,
                                  1u,
                                  2u,
                                  4u,
                                  5u,
                                  0x7fffffffu,
                                  0x80000000u,
                                  0xfffffffeu,
                                  0xffffffffu};

  for (std::size_t index = 0; index < sizeof(interesting) / sizeof(interesting[0]);
       ++index) {
    plant_arena();
    store_word(kPlantedTailWordAt, interesting[index]);
    check(call_entry(receiver()) == interesting[index]);
  }

  // Every reachable byte pattern at +0x194 comes back unchanged, so no mask,
  // no shift, no sign-extension and no saturation survives.
  for (std::size_t high = 0; high < 4u; ++high) {
    for (std::size_t low = 0; low < 4u; ++low) {
      plant_arena();
      const std::uint32_t value =
          static_cast<std::uint32_t>((high << 8) | low);
      store_word(kPlantedTailWordAt, value);
      check(call_entry(receiver()) == value);
    }
  }

  // The guard is a test against ZERO and nothing else. Four further DISTINCT
  // addresses inside the arena are planted, each with its own word at +0x194,
  // and each takes the transfer - so a guard that filtered for "one particular
  // object", or that consulted the receiver instead of the word, would answer
  // differently for at least one of them.
  //
  // A NOTE ON WHAT IS DELIBERATELY NOT CLAIMED HERE, because it is the honest
  // bound of this test. A word that is NOT a usable address - 1, 3, 0x80000000,
  // 0xffffffff - cannot be exercised, because the modelled tail target has no
  // null check and faithfully reads at +0x194 of whatever it is handed: such a
  // word faults HERE exactly as it would in the original process. So this test
  // does NOT prove that the guard is a zero test rather than an
  // address-plausibility test. What it does prove is that the guard is a test
  // against zero: the null arm yields 1, and every address the arena holds
  // takes the transfer. The remaining distinction is bounded by the tail
  // target's own behaviour, not by anything this body does, and it is recorded
  // as unresolved rather than asserted.
  const std::size_t more_tails[] = {0x000u, 0x180u, 0x318u, 0x4b0u};
  const SlotWord more_expected[] = {0x01010101u, 0x02020202u, 0x03030303u,
                                    0x04040404u};
  for (std::size_t index = 0;
       index < sizeof(more_tails) / sizeof(more_tails[0]); ++index) {
    const std::size_t tail_offset = more_tails[index];
    const std::size_t word_at = tail_offset + 0x194u;
    check(word_at + 4u <= kArenaBytes);
    store_word(word_at, more_expected[index]);
    store_word(kReceiverOffset + kFieldOffset,
               pointer_word(g_arena + tail_offset));
    const SlotWord answer = call_entry(receiver());
    check(answer == more_expected[index]);
    check(answer != 1u);
    check(answer != kPlantedTailWord);
  }
  for (std::size_t left = 0; left < 4u; ++left) {
    for (std::size_t right = left + 1u; right < 4u; ++right) {
      check(more_expected[left] != more_expected[right]);
    }
  }

  // And the planted pointer still works after all of that.
  plant_arena();
  check(call_entry(receiver()) == kPlantedTailWord);
}

// ---------------------------------------------------------------------------
// F. A wrong DISPATCH TARGET is observable, and the sentinel is live.
// ---------------------------------------------------------------------------

void test_wrong_dispatch_target_is_observable() {
  plant_arena();
  OpaqueTailReceiver* const planted = tail_at(kPlantedOffset);

  // What the modelled target returns for the planted object.
  const SlotWord correct = call_tail_through_slot(planted);
  check(correct == kPlantedTailWord);

  // What the two wrong entries of the table return for it. Distinct from the
  // correct value and from each other, which is what makes a wrong dispatch
  // detectable at all: if the sentinel shared the correct value, a one-slot-too-
  // far dispatch would be invisible.
TailTargetFn const trap = g_targets.sentinel;
  std::uint32_t sentinel_answer = 0;
  std::uint32_t receiver_reg = pointer_word(planted);
  std::uint32_t trap_reg =
      pointer_word(reinterpret_cast<const void*>(trap));
  __asm__ __volatile__("call *%2\n\t"
                       : "=a"(sentinel_answer), "+c"(receiver_reg), "+d"(trap_reg)
                       :
                       : "memory");
  check(sentinel_answer == kSentinelReturn);
  check(sentinel_answer != correct);
  check(sentinel_answer != kDecoyTargetReturn);
  check(sentinel_answer != 1u);

  const SlotWord decoy_answer = decoy_tail_target(planted);
  check(decoy_answer == kDecoyTargetReturn);
  check(decoy_answer != correct);
  check(decoy_answer != sentinel_answer);

  // The table's shape: the trap is in the word immediately past the last
  // modelled slot, so there is no gap in which a neighbouring pointer could
  // hide and impersonate a valid target.
  check(offsetof(TailTargetTable, sentinel) == sizeof(void*));
  check(pointer_word(&g_targets.sentinel) ==
        pointer_word(reinterpret_cast<const std::uint8_t*>(&g_targets) +
                     sizeof(void*)));

  // And the entry's answer is the modelled target's answer, so it dispatched
  // to the modelled target and not to either of the others.
  check(call_entry(receiver()) == correct);
  check(call_entry(receiver()) != sentinel_answer);
  check(call_entry(receiver()) != decoy_answer);
}

// ---------------------------------------------------------------------------
// G. The ABI: ECX receiver, nothing pushed, callee pops nothing. Measured.
// ---------------------------------------------------------------------------

void test_abi_is_measured_not_assumed() {
  plant_arena();

  // The two samples, read out of the file-scope volatile slots.
const SlotWord measured = call_entry_measured(receiver());
  check(measured == kPlantedTailWord);
  const volatile std::uint32_t before = g_esp_before_call;
  const volatile std::uint32_t after = g_esp_after_return;
  check(after == before);

  // The receiver arrives in ECX: a body that read its word from a stack
  // argument instead could not produce the planted answer with nothing pushed.
  check(call_entry(receiver()) == kPlantedTailWord);

  // A second receiver at a different address yields a different answer, which
  // is what makes the result a function of the RECEIVER rather than of
  // anything ambient. The second receiver is a view over a different part of
  // the same arena, so its own field is at ITS +0x13c and is planted
  // independently of the first receiver's.
  OpaqueReceiver* const alt = reinterpret_cast<OpaqueReceiver*>(
      g_arena + kReceiverOffset + 0x40u);
  check(alt != receiver());
  store_word(kReceiverOffset + 0x40u + kFieldOffset, 0u);
  check(call_entry(alt) == 1u);
  check(call_entry(receiver()) == kPlantedTailWord);
  store_word(kReceiverOffset + 0x40u + kFieldOffset,
             pointer_word(g_arena + kFarDecoyOffset));
  store_word(kFarDecoyWordAt, 0x77777777u);
  check(call_entry(alt) == 0x77777777u);
  check(call_entry(receiver()) == kPlantedTailWord);
  plant_arena();
store_word(kReceiverOffset + 0x40u + kFieldOffset,
           pointer_word(g_arena + kPlantedOffset));
  check(call_entry(alt) == kPlantedTailWord);
  check(call_entry(receiver()) == kPlantedTailWord);

  // The modelled ABI types can express neither a stack argument nor a
  // by-reference return, so a reconstruction that grew one could not be
  // declared against them.
  static_assert(std::is_same<AbiField13c00c70e00,
                             SlotWord(PKG_00C70E00_THISCALL*)(
                                 OpaqueReceiver*)>::value,
                "the modelled entry carries the ECX receiver and returns one "
                "word");
  static_assert(std::is_same<AbiTailTransfer00b8dab0,
                             SlotWord(PKG_00C70E00_THISCALL*)(
                                 OpaqueTailReceiver*)>::value,
                "the modelled tail target carries ITS receiver in ECX");
  check(sizeof(AbiField13c00c70e00) == sizeof(void*));
  check(sizeof(AbiTailTransfer00b8dab0) == sizeof(void*));
  check(entry_address() != 0u);

  // The two receivers are different types on purpose: the tail target's own
  // displacement is beyond this body's receiver extent, so no object that is a
  // valid OpaqueReceiver can stand in for one.
  check(sizeof(OpaqueTailReceiver) > sizeof(OpaqueReceiver));
  check(alignof(OpaqueReceiver) == 4u);
  check(alignof(OpaqueTailReceiver) == 4u);
}

// ---------------------------------------------------------------------------
// H. The encoding IS the observed bytes, and both computed addresses are right.
// ---------------------------------------------------------------------------

void test_encoding_matches_the_observed_bytes() {
  // The six instructions, byte for byte, as read live at 0x00c70e00.
  const std::uint8_t expected[kTargetBodyBytes] = {
      0x8b, 0x89, 0x3c, 0x01, 0x00, 0x00, 0x85, 0xc9, 0x74, 0x05, 0xe9,
      0xa1, 0xcc, 0xf1, 0xff, 0xb8, 0x01, 0x00, 0x00, 0x00, 0xc3};
  for (std::size_t index = 0; index < kTargetBodyBytes; ++index) {
    check(kTargetEncoding[index] == expected[index]);
  }
  check(kTargetBodyBytes == 21u);

  // 0x00c70e00 MOV ECX,[ECX + 0x13c]. ModRM 0x89: mod=10 -> a disp32 follows;
  // reg=001 -> ECX; rm=001 -> ECX. Base and destination are the same register,
  // which is the in-place chain the tail transfer depends on.
  check(kTargetEncoding[0] == 0x8bu);
  check(kTargetEncoding[0] != 0x8du);  // 0x8d is LEA
  check(kTargetEncoding[1] == 0x89u);
  check((kTargetEncoding[1] >> 6) == 2u);
  check(((kTargetEncoding[1] >> 3) & 7u) == 1u);
  check((kTargetEncoding[1] & 7u) == 1u);
  check((static_cast<std::uint32_t>(kTargetEncoding[2]) |
         (static_cast<std::uint32_t>(kTargetEncoding[3]) << 8) |
         (static_cast<std::uint32_t>(kTargetEncoding[4]) << 16) |
         (static_cast<std::uint32_t>(kTargetEncoding[5]) << 24)) ==
        kFieldDisplacement);

  // 0x00c70e06 TEST ECX,ECX. ModRM 0xc9: reg=001 (ECX), rm=001 (ECX). The
  // flags come from the LOADED word.
  check(kTargetEncoding[6] == 0x85u);
  check(kTargetEncoding[7] == 0xc9u);
  check(((kTargetEncoding[7] >> 3) & 7u) == 1u);
  check((kTargetEncoding[7] & 7u) == 1u);

  // 0x00c70e08 JZ rel8 = +5, and 5 is the length of the instruction it skips.
  check(kTargetEncoding[8] == 0x74u);
  check(static_cast<std::int8_t>(kTargetEncoding[9]) == 5);
  check(kJumpInstructionBytes == 5u);
  check(static_cast<std::size_t>(kJzDisplacement) == kJumpInstructionBytes);

  // 0x00c70e0a JMP rel32, and the address it computes is 0x00b8dab0.
  check(kTargetEncoding[10] == 0xe9u);
  check(kComputedTailTarget == kTailTargetVa);
  check(kComputedTailTarget == 0x00b8dab0u);
  check(kTailTargetVa == 0x00b8dab0u);
  check(kTailTransferCallsite == 0x00c70e0au);

  // 0x00c70e0f MOV EAX,imm32 - the b8 form, a full 32-bit write, not b0.
  check(kTargetEncoding[15] == 0xb8u);
  check(kTargetEncoding[15] != 0xb0u);
  check((static_cast<std::uint32_t>(kTargetEncoding[16]) |
         (static_cast<std::uint32_t>(kTargetEncoding[17]) << 8) |
         (static_cast<std::uint32_t>(kTargetEncoding[18]) << 16) |
         (static_cast<std::uint32_t>(kTargetEncoding[19]) << 24)) == 1u);
  check(kNullArmReturn == 1u);

  // 0x00c70e14 is a bare RET.
  check(kTargetEncoding[20] == 0xc3u);
  check(kTargetEncoding[20] != 0xc2u);

  // The address the JZ names, computed rather than restated.
  check(kComputedNullArm == kNullArmAddress);
  check(kComputedNullArm == 0x00c70e0fu);

  // The three INT3 pad bytes after the body.
  check(kTargetPadByte == 0xccu);
  check(kTargetPadBytes == 3u);

  // THE TAIL TARGET'S OWN SEVEN BYTES, read live at 0x00b8dab0. This is what
  // makes "the transfer hands ECX over as the callee's receiver" a statement
  // about bytes: ModRM 0x81 has rm=001, i.e. the tail target reads through
  // ECX, and ECX is not rewritten between 0x00c70e00 and the jump.
  const std::uint8_t tail_expected[7] = {0x8b, 0x81, 0x94, 0x01, 0x00, 0x00, 0xc3};
  for (std::size_t index = 0; index < 7u; ++index) {
    check(kTailTargetEncoding[index] == tail_expected[index]);
  }
  check((kTailTargetEncoding[1] & 7u) == 1u);
  check((kTailTargetEncoding[1] >> 6) == 2u);
  check(((kTailTargetEncoding[1] >> 3) & 7u) == 0u);
  check((static_cast<std::uint32_t>(kTailTargetEncoding[2]) |
         (static_cast<std::uint32_t>(kTailTargetEncoding[3]) << 8) |
         (static_cast<std::uint32_t>(kTailTargetEncoding[4]) << 16) |
         (static_cast<std::uint32_t>(kTailTargetEncoding[5]) << 24)) ==
        kTailTargetDisplacement);
  check(kTailTargetEncoding[6] == 0xc3u);
  check(kTailTargetEncoding[6] != 0xc2u);
  // rm=ECX on the tail target and rm=ECX on this body's load: the same register
  // carries the receiver out of one and into the other, with nothing in
  // between that writes it.
  check((kTargetEncoding[1] & 7u) == (kTailTargetEncoding[1] & 7u));
  check(kTailTargetDisplacement == 0x194u);

  // The committed xref export records exactly one outgoing edge for this VA and
  // it names this target at the JMP's callsite.
  check(kRecordedOutgoingDirectCallEdges == 1u);
  check(kRecordedIncomingDirectCallEdges == 41u);
  check(kRecordedDistinctCallers == 32u);
  // The record's own verdict is an abstention, pinned rather than paraphrased.
  check(std::strlen(kAbiVerdictAbstained) == 11u);
  check(std::strcmp(kAbiVerdictAbstained, "ABI_UNKNOWN") == 0);
  check(kAbiVerdictAbstained[0] == 'A');
  check(kAbiVerdictAbstained[10] == 'N');
}

// ---------------------------------------------------------------------------
// I. The sampled call sites' ordered comparisons, as the binary's do.
// ---------------------------------------------------------------------------

void test_sampled_callers_ordered_comparisons() {
  // 0x00ba0251: 83 f8 05 = CMP EAX,0x00000005 (imm8 sign-extended)
  // 0x00ba0254: 75 04    = JNZ rel8
  // 0x00be212e: 83 f8 04 = CMP EAX,0x00000004
  // 0x00be2131: 0f 85 .. = JNZ rel32
  // 0x00d56c5e: 83 f8 04 = CMP EAX,0x00000004
  // 0x00d56c61: 0f 84 .. = JZ  rel32
  // 0x00ff74a4: 83 f8 05 = CMP EAX,0x00000005
  // 0x00ff74a7: 75 09    = JNZ rel8
  const std::uint8_t cmp_five_jnz[4] = {0x83, 0xf8, 0x05, 0x75};
  const std::uint8_t cmp_four_jnz[4] = {0x83, 0xf8, 0x04, 0x0f};
  const std::uint8_t cmp_four_jz[4] = {0x83, 0xf8, 0x04, 0x0f};
  check(cmp_five_jnz[0] == 0x83u);
  check(cmp_five_jnz[1] == 0xf8u);  // ModRM: reg=EAX, rm=EAX
  check(cmp_five_jnz[2] == 0x05u);
  check(cmp_five_jnz[3] == 0x75u);  // JNZ rel8
  check(cmp_four_jnz[0] == 0x83u);
  check(cmp_four_jnz[1] == 0xf8u);
  check(cmp_four_jnz[2] == 0x04u);
  check(cmp_four_jnz[3] == 0x0fu);
  check(cmp_four_jz[0] == 0x83u);
  check(cmp_four_jz[1] == 0xf8u);
  check(cmp_four_jz[2] == 0x04u);
  check(cmp_four_jz[3] == 0x0fu);

  // All four comparisons are UNSIGNED-equality against a small constant
  // (0x4 or 0x5), so the reconstruction must be able to produce both those
  // values and every other bit pattern, including 0 and the top-bit-set ones.
  const auto equals_five = [](SlotWord value) -> bool { return value == 5u; };
  const auto equals_four = [](SlotWord value) -> bool { return value == 4u; };

  plant_arena();
  store_word(kPlantedTailWordAt, 5u);
  check(equals_five(call_entry(receiver())));
  store_word(kPlantedTailWordAt, 4u);
  check(equals_four(call_entry(receiver())));
  store_word(kPlantedTailWordAt, 0u);
  check(call_entry(receiver()) == 0u);
  check(!equals_five(call_entry(receiver())));
  store_word(kPlantedTailWordAt, 0xffffffffu);
  check(call_entry(receiver()) == 0xffffffffu);
  check(!equals_four(call_entry(receiver())));

  // The null arm's 1 also orders against 4 and 5, which is why the sampled
  // comparisons are consistent with the two paths returning one 32-bit
  // quantity and do not by themselves prove they are the SAME quantity.
  plant_arena();
  store_word(kReceiverOffset + kFieldOffset, 0u);
  check(!equals_five(call_entry(receiver())));
  check(!equals_four(call_entry(receiver())));

  // Both values are reachable from the same call site shape, so the two paths
  // are not separated by any signature difference: the null arm yields 1, and
  // the transfer arm yields 1 when the transferred receiver's own +0x194 word
  // happens to hold 1. Nothing in the evidence says those two 1s are the same
  // quantity, and this package does not claim it.
  plant_arena();
  store_word(kReceiverOffset + kFieldOffset, 0u);
  check(call_entry(receiver()) == 1u);
  plant_arena();
  store_word(kPlantedTailWordAt, 1u);
  check(call_entry(receiver()) == 1u);
  // And the two are distinguishable the moment the transferred word differs.
  store_word(kPlantedTailWordAt, 2u);
  check(call_entry(receiver()) == 2u);
  check(call_entry(receiver()) != 1u);
  plant_arena();
  store_word(kReceiverOffset + kFieldOffset, 0u);
  check(call_entry(receiver()) == 1u);
}

}

}

namespace {

using namespace openspore::reconstruction::pkg_00c70e00_field13c;

int run_tests() {
  model::test_null_word_returns_the_listing_constant();
  model::test_transferred_object_is_the_word_at_0x13c();
  model::test_displacement_is_bytes_not_an_index();
  model::test_body_writes_nothing();
  model::test_value_crosses_verbatim();
  model::test_wrong_dispatch_target_is_observable();
  model::test_abi_is_measured_not_assumed();
  model::test_encoding_matches_the_observed_bytes();
  model::test_sampled_callers_ordered_comparisons();
  return 0;
}

}

int main() { return ::run_tests(); }

#undef PKG_00C70E00_THISCALL