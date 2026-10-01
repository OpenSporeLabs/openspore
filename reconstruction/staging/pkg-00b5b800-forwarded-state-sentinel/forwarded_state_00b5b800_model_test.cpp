#include "forwarded_state_00b5b800.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

// Model test for 0x00b5b800 (SporeApp.exe 3.1.0.22).
//
// The machine body is twenty bytes, seven instructions:
//
//     0x00b5b800  e8 1b 1b fe ff      CALL   0x00b3d320
//     0x00b5b805  85 c0               TEST   EAX,EAX
//     0x00b5b807  74 07               JE     0x00b5b810
//     0x00b5b809  8b c8               MOV    ECX,EAX
//     0x00b5b80b  e9 20 6f ee ff      JMP    0x00a42730
//     0x00b5b810  83 c8 ff            OR     EAX,0xffffffff
//     0x00b5b813  c3                  RET
//
// so the whole of the observable contract is: read one borrowed absolute dword;
// if it is null return the all-ones word, otherwise return the 32-bit word at
// receiver+0x20; touch no stack, allocate nothing, store nothing, take no
// receiver. Each test below is written to REFUTE a plausible wrong
// reconstruction rather than to walk a right one:
//
//   1. the non-null path returns the FORWARDED WORD, across values a truncating
//      or sign-extending return cannot survive;
//   2. it is the word at the +0x20 displacement and not its neighbours -- and
//      reference readers prove the harness can tell those addresses apart, so
//      this cannot pass vacuously;
//   3. the null path returns exactly 0xffffffff, for EVERY null spelling, and
//      does NOT return pointer null, zero, or the receiver;
//   4. the null test is over the whole 32 bits, not a byte or a halfword;
//   5. the entry tracks the receiver's CURRENT contents and the field's CURRENT
//      contents: not a cached word, not a constant, not the receiver's address;
//   6. all 32 bits of EAX carry the word (measured through a trampoline, not
//      through the C++ return path) and ESP is identical either side of the
//      call, so the bare RET popped nothing;
//   7. the corroborated consumer's two spellings agree: the inlined
//      receiver+0x20 read and the call to this root return the SAME word for
//      every modelled receiver, and the state it is compared against is a
//      separate domain from the null sentinel;
//   8. guard bands on BOTH modelled images: the body performs two reads and no
//      store, so nothing it touches may change;
//   9. the machine facts the whole package rests on are re-checked at run time,
//      including that every address constant is decoded from machine bytes.
//
// The ABI facts are checked at compile time by AbiForwardedState00b5b800 and
// the std::is_same assertion below: a prototype with any parameter, or with a
// different return width, does not build.

#if !defined(__i386__) && !defined(_M_IX86)
#error "forwarded state accessor 0x00b5b800 model test requires an x86-32 target"
#endif

namespace {

using openspore::reconstruction::pkg_00b5b800::AbiForwardedState00b5b800;
using openspore::reconstruction::pkg_00b5b800::ForwardedReceiverImage;
using openspore::reconstruction::pkg_00b5b800::forwarded_state_00b5b800;
using openspore::reconstruction::pkg_00b5b800::g_0167eaec;
using openspore::reconstruction::pkg_00b5b800::g_forwarded_receiver;
using openspore::reconstruction::pkg_00b5b800::g_forwarded_receiver_field;
using openspore::reconstruction::pkg_00b5b800::g_forwarded_receiver_image;
using openspore::reconstruction::pkg_00b5b800::g_receiver_global_image;
using openspore::reconstruction::pkg_00b5b800::kBodyBytes;
using openspore::reconstruction::pkg_00b5b800::kCalleeCleanupBytes;
using openspore::reconstruction::pkg_00b5b800::kEntryVa;
using openspore::reconstruction::pkg_00b5b800::kFieldReaderBytes;
using openspore::reconstruction::pkg_00b5b800::kForwardedFieldDisplacement;
using openspore::reconstruction::pkg_00b5b800::kForwardedObjectBytes;
using openspore::reconstruction::pkg_00b5b800::kHasReceiver;
using openspore::reconstruction::pkg_00b5b800::kInstructionCount;
using openspore::reconstruction::pkg_00b5b800::kMemoryReads;
using openspore::reconstruction::pkg_00b5b800::kMemoryStores;
using openspore::reconstruction::pkg_00b5b800::kNullSentinel;
using openspore::reconstruction::pkg_00b5b800::kReceiverGlobalVa;
using openspore::reconstruction::pkg_00b5b800::kReceiverGuardCanary;
using openspore::reconstruction::pkg_00b5b800::kReceiverGuardWords;
using openspore::reconstruction::pkg_00b5b800::kReceiverReaderBytes;
using openspore::reconstruction::pkg_00b5b800::kReturnWidthBytes;
using openspore::reconstruction::pkg_00b5b800::kStackArgumentWords;
using openspore::reconstruction::pkg_00b5b800::kTargetBytes;
using openspore::reconstruction::pkg_00b5b800::kTerminalVa;
using openspore::reconstruction::pkg_00b5b800::read_forwarded_field;
using openspore::reconstruction::pkg_00b5b800::read_receiver_slot;
using openspore::reconstruction::pkg_00b5b800::ReceiverGlobalImage;
using openspore::reconstruction::pkg_00b5b800::Word;

// The machine ABI, asserted against the declaration: zero parameters, 4-byte
// return, no receiver. This is the compile-time gate -- change the prototype and
// this stops building.
static_assert(std::is_same<decltype(&forwarded_state_00b5b800), AbiForwardedState00b5b800>::value,
              "0x00b5b800 takes no parameter (no stack operand in the body, no "
              "register read on entry, bare RET) and returns the 4-byte word it "
              "forwards");
static_assert(sizeof(AbiForwardedState00b5b800) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");
static_assert(sizeof(void*) == 4u,
              "the modelled entry is a 32-bit code pointer, so this is an "
              "x86-32 reconstruction");

// Calling the reconstruction only through the checked ABI type.
AbiForwardedState00b5b800 const kEntrySlot = &forwarded_state_00b5b800;

std::uint32_t entry_address() {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(kEntrySlot));
}

// Two words the corroborated consumer compares the result against. They are
// address shaped but nothing in the machine dereferences them; they exist here
// so the tests can show the null sentinel is a DIFFERENT domain from them, and
// so the borrowed forwarded word can be made to look like one of them and be
// told apart from the sentinel.
constexpr Word kConsumerStateFive = 0x01654c05u;
constexpr Word kConsumerStateFour = 0x01654c04u;

void arm_receiver_image() {
  for (std::size_t i = 0; i < kReceiverGuardWords; ++i) {
    g_receiver_global_image.guard_lo[i] = kReceiverGuardCanary;
  }
  for (std::size_t i = 0; i < kReceiverGuardWords; ++i) {
    g_receiver_global_image.guard_hi[i] = kReceiverGuardCanary;
  }
}

void arm_forwarded_receiver_image(std::uint8_t fill) {
  std::memset(g_forwarded_receiver_image.bytes, static_cast<int>(fill), kForwardedObjectBytes);
}

// The receiver the modelled global points at, and a second receiver with a
// controlled address shape, so a body that ignored the global cannot pass by
// accident and a narrower null test can be refuted.

// Big enough that the field reader at the modelled displacement stays inside
// the run from either probe point. Aligned so a probe at the start has a zero
// low half; a probe kByteOffsetWords words in has a zero low byte with a
// non-zero second byte.
alignas(65536) std::uint32_t g_aligned_object[1024] = {0};
constexpr std::size_t kByteOffsetWords = 0x100 / sizeof(std::uint32_t);
static_assert(kByteOffsetWords == 64,
              "the second probe sits 256 bytes into the aligned run, so its low "
              "byte is zero and its second byte is not");

Word address_of_forwarded_receiver() {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_forwarded_receiver));
}

// Reference readers for the words immediately either side of the forwarded one.
// They exist so the "it read the word at the forwarded displacement" checks can
// fail: without them a harness that could not distinguish the addresses would
// report the same answer for all three and the assertion would hold for the
// wrong reason.
Word& reference_reads_word_below() {
  return *reinterpret_cast<Word*>(g_forwarded_receiver + kForwardedFieldDisplacement - sizeof(Word));
}
Word& reference_reads_word_above() {
  return *reinterpret_cast<Word*>(g_forwarded_receiver + kForwardedFieldDisplacement + sizeof(Word));
}

// 1. The non-null path returns the forwarded word, across widths and signs a
//    truncating or sign-extending return cannot survive.
void test_non_null_path_returns_the_forwarded_word() {
  const Word values[] = {0u,
                         1u,
                         2u,
                         0x7fffffffu,
                         0x80000000u,
                         0xdeadbeefu,
                         kNullSentinel,
                         kConsumerStateFour,
                         kConsumerStateFive,
                         address_of_forwarded_receiver()};
  for (const Word value : values) {
    arm_receiver_image();
    arm_forwarded_receiver_image(0x11);
    g_forwarded_receiver_field = value;
    g_0167eaec = address_of_forwarded_receiver();
    assert(kEntrySlot() == value);
  }
}

// 2. It is the word at the forwarded displacement and not its neighbours. The
//    reference readers are first checked to return exactly the neighbour words,
//    which is what makes this capable of failing: a body reading below or above
//    the displacement gives an answer this test can see is wrong.
void test_reads_the_forwarded_displacement_and_not_a_neighbour() {
  arm_receiver_image();
  arm_forwarded_receiver_image(0x22);
  g_forwarded_receiver_field = 0x12345678u;
  g_0167eaec = address_of_forwarded_receiver();
  reference_reads_word_below() = 0xdead0001u;
  reference_reads_word_above() = 0xdead0002u;

  assert(reference_reads_word_below() == 0xdead0001u);
  assert(reference_reads_word_above() == 0xdead0002u);
  assert(kEntrySlot() == 0x12345678u);
  assert(kEntrySlot() != 0xdead0001u);
  assert(kEntrySlot() != 0xdead0002u);

  // The displacement is not the object start either: the two leading words of
  // the modelled run are set to values a wrong-displacement body would return.
  *reinterpret_cast<Word*>(g_forwarded_receiver) = 0xdead0003u;
  *reinterpret_cast<Word*>(g_forwarded_receiver + sizeof(Word)) = 0xdead0004u;
  assert(kEntrySlot() == 0x12345678u);
  assert(kEntrySlot() != 0xdead0003u);
  assert(kEntrySlot() != 0xdead0004u);
}

// 3. The null path returns exactly the all-ones sentinel, for every null
//    spelling the body could be handed, and it is NOT pointer null, NOT zero and
//    NOT the receiver.
void test_null_path_returns_the_all_ones_sentinel() {
  arm_receiver_image();
  arm_forwarded_receiver_image(0x33);
  g_forwarded_receiver_field = 0x5a5a5a5au;
  const Word forwarded = g_forwarded_receiver_field;

  for (std::size_t attempt = 0; attempt < 3; ++attempt) {
    g_0167eaec = 0u;
    const Word observed = kEntrySlot();
    assert(observed == kNullSentinel);
    // Explicitly NOT normalised to pointer null, and not the forwarded word.
    assert(observed != 0u);
    assert(observed != forwarded);
    // The null arm must not disturb the forwarded word.
    assert(g_forwarded_receiver_field == forwarded);
  }

  // The sentinel is a full 32-bit word, not a byte or a halfword value.
  assert(kNullSentinel == 0xffffffffu);
  assert(kNullSentinel != 0xffffu);
  assert(kNullSentinel != 0xffu);
}

// 4. The null test is over the whole 32 bits, not a byte and not a halfword.
//    Two receivers are used whose own addresses have a zero LOW HALF and a zero
//    LOW BYTE respectively while the whole 32-bit word is non-zero. A narrower
//    zero test would send either of them down the null arm; the machine's
//    TEST EAX,EAX sends both down the forwarded arm.
void test_null_test_covers_all_thirty_two_bits() {
  arm_forwarded_receiver_image(0x44);
  g_forwarded_receiver_field = 0x0badc0deu;

  // Receiver whose low HALF is zero: kills a 16-bit zero test.
  const std::uint32_t half_aligned = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&g_aligned_object[0]));
  assert((half_aligned & 0x0000ffffu) == 0u);
  assert((half_aligned & 0xffff0000u) != 0u);
  g_0167eaec = half_aligned;
  g_aligned_object[0 + kForwardedFieldDisplacement / sizeof(Word)] = 0x0badc0deu;
  assert(kEntrySlot() == 0x0badc0deu);

  // Receiver whose low BYTE is zero but whose second byte is not: kills an 8-bit
  // zero test.
  const std::uint32_t byte_aligned = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&g_aligned_object[kByteOffsetWords]));
  assert((byte_aligned & 0x000000ffu) == 0u);
  assert((byte_aligned & 0x0000ff00u) != 0u);
  assert((byte_aligned & 0xffff0000u) != 0u);
  g_0167eaec = byte_aligned;
  g_aligned_object[kByteOffsetWords + kForwardedFieldDisplacement / sizeof(Word)] = 0x0d0e0f10u;
  assert(kEntrySlot() == 0x0d0e0f10u);

  // And the genuinely-null word still yields the sentinel, so the two checks
  // above are not passing because the body always reads the same storage.
  g_0167eaec = 0u;
  assert(kEntrySlot() == kNullSentinel);

  // A receiver that is the modelled byte run is still non-null, for contrast.
  g_0167eaec = address_of_forwarded_receiver();
  assert(kEntrySlot() == g_forwarded_receiver_field);
}

// 5. The entry tracks CURRENT contents on both hops: not a cached word, not a
//    constant, and not the receiver's own address.
void test_tracks_current_contents_not_a_cached_or_constant_value() {
  arm_receiver_image();
  arm_forwarded_receiver_image(0x55);

  g_0167eaec = address_of_forwarded_receiver();
  g_forwarded_receiver_field = 0x0f0f0f0fu;
  assert(kEntrySlot() == 0x0f0f0f0fu);
  assert(kEntrySlot() == 0x0f0f0f0fu);  // stable: no side effect

  g_forwarded_receiver_field = kConsumerStateFive;
  assert(kEntrySlot() == kConsumerStateFive);
  g_forwarded_receiver_field = kConsumerStateFour;
  assert(kEntrySlot() == kConsumerStateFour);
  g_forwarded_receiver_field = kNullSentinel;
  assert(kEntrySlot() == kNullSentinel);
  g_forwarded_receiver_field = 0x01020304u;
  assert(kEntrySlot() == 0x01020304u);

  // It is the receiver's CONTENTS that decide, and the receiver's own address
  // is never the answer.
  assert(kEntrySlot() != address_of_forwarded_receiver());
  assert(read_receiver_slot() == address_of_forwarded_receiver());
  assert(kEntrySlot() == 0x01020304u);
}

// 6. All 32 bits of EAX carry the word, and the bare RET pops nothing. Measured
//    through a trampoline that reproduces the observed call shape (no argument
//    pushed, indirect call), so the C++ return path is not what is checked.
void test_whole_eax_carries_the_word_and_esp_is_untouched() {
  arm_receiver_image();
  arm_forwarded_receiver_image(0x66);
  g_0167eaec = address_of_forwarded_receiver();
  g_forwarded_receiver_field = 0xdeadbeefu;

  std::uint32_t eax_after = 0;
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  const std::uint32_t target = entry_address();
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[target], %%ebx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%eax, %[eaxv]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [eaxv] "=m"(eax_after), [after] "=m"(after)
                       : [target] "r"(target)
                       : "eax", "ebx", "cc", "memory");

  // The full 32-bit return, high bit included: a body returning AL or AX, or one
  // sign-extending a narrower load, fails here.
  assert(eax_after == 0xdeadbeefu);

  // The bare RET pops nothing: ESP is identical either side of the call. A
  // frame-allocating, callee-cleaning or argument-taking body fails here.
  assert(before == after);
  assert(before != 0u);  // the sample is a real stack address, not a constant

  // Re-measured on the NULL arm, so the check is not satisfied by one lucky
  // register state: the sentinel must also arrive in all of EAX.
  g_0167eaec = 0u;
  eax_after = 0;
  before = 0;
  after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[target], %%ebx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%eax, %[eaxv]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [eaxv] "=m"(eax_after), [after] "=m"(after)
                       : [target] "r"(target)
                       : "eax", "ebx", "cc", "memory");
  assert(eax_after == 0xffffffffu);
  assert(before == after);
}

// 7. The corroborated consumer at 0x00ad12a0 writes the same forwarded field
//    two ways -- inlined as receiver+0x20 and through a call to this root -- and
//    compares the two results against two different members of one encoded-state
//    family. Modelled here: for every receiver, the inlined read and the call
//    return the SAME word, and that word is a different domain from the null
//    sentinel the root itself produces.
void test_inlined_and_called_spellings_agree() {
  arm_receiver_image();
  arm_forwarded_receiver_image(0x77);
  const Word states[] = {kConsumerStateFour, kConsumerStateFive, 0u, kNullSentinel, 0x7fffffffu, 0x80000001u};
  for (const Word state : states) {
    g_0167eaec = address_of_forwarded_receiver();
    g_forwarded_receiver_field = state;

    // The call spelling.
    const Word via_call = kEntrySlot();
    // The inlined spelling the same function uses elsewhere: read the receiver
    // slot, then read the field through it.
    const Word inlined = read_forwarded_field(read_receiver_slot());
    assert(via_call == inlined);

    // The non-null arm forwards the word VERBATIM, including when the word
    // itself is zero or all ones: the gate is on the RECEIVER, never on the
    // value being forwarded. A body that conflated the two would return the
    // sentinel here.
    assert(via_call == state);
  }

  // The gate really is on the receiver: with the receiver null the very same
  // storage yields the sentinel, and the two consumer state values are a
  // different domain from it.
  g_0167eaec = 0u;
  assert(kEntrySlot() == kNullSentinel);
  assert(kNullSentinel != kConsumerStateFour);
  assert(kNullSentinel != kConsumerStateFive);
  g_0167eaec = address_of_forwarded_receiver();
  g_forwarded_receiver_field = kNullSentinel;
  assert(kEntrySlot() == kNullSentinel);  // the forwarded word is itself all ones
  g_forwarded_receiver_field = 0u;
  assert(kEntrySlot() == 0u);             // a zero word is forwarded, not sent

  // The two domain values are address shaped and are never dereferenced by the
  // machine, so the model keeps them as words.
  assert(kConsumerStateFour != kNullSentinel);
  assert(kConsumerStateFive != kNullSentinel);
  assert(kConsumerStateFour != kConsumerStateFive);
}

// 8. Guard bands on BOTH modelled images. The body performs two reads and no
//    store, so every byte it can reach must be exactly as it was left.
void test_writes_nothing_on_either_hop() {
  arm_receiver_image();
  arm_forwarded_receiver_image(0x88);
  g_0167eaec = address_of_forwarded_receiver();
  g_forwarded_receiver_field = 0x5a5a1234u;

  const Word receiver_before = g_0167eaec;
  const Word forwarded_before = g_forwarded_receiver_field;
  std::uint8_t snapshot[kForwardedObjectBytes];
  std::memcpy(snapshot, g_forwarded_receiver_image.bytes, kForwardedObjectBytes);

  // Non-null path.
  assert(kEntrySlot() == 0x5a5a1234u);
  assert(g_0167eaec == receiver_before);
  assert(g_forwarded_receiver_field == forwarded_before);
  assert(std::memcmp(snapshot, g_forwarded_receiver_image.bytes, kForwardedObjectBytes) == 0);
  for (std::size_t i = 0; i < kReceiverGuardWords; ++i) {
    assert(g_receiver_global_image.guard_lo[i] == kReceiverGuardCanary);
    assert(g_receiver_global_image.guard_hi[i] == kReceiverGuardCanary);
  }

  // Null path, with the guards set to non-canary sentinels so the guard check
  // is not passing merely because they happened to be untouched canaries.
  g_receiver_global_image.guard_lo[kReceiverGuardWords - 1] = 0x11111111u;
  g_receiver_global_image.guard_hi[0] = 0x22222222u;
  g_0167eaec = 0u;
  assert(kEntrySlot() == kNullSentinel);
  assert(g_0167eaec == 0u);  // the null arm does not write the slot either
  assert(g_forwarded_receiver_field == forwarded_before);
  assert(std::memcmp(snapshot, g_forwarded_receiver_image.bytes, kForwardedObjectBytes) == 0);
  assert(g_receiver_global_image.guard_lo[kReceiverGuardWords - 1] == 0x11111111u);
  assert(g_receiver_global_image.guard_hi[0] == 0x22222222u);
}

// 9. The machine facts the whole package rests on are re-checked at run time,
//    including that every address constant really is decoded from machine bytes.
void test_machine_facts() {
  assert(kEntryVa == 0x00b5b800u);
  assert(kTerminalVa == 0x00b5b813u);
  assert(kBodyBytes == 20u);
  assert(kInstructionCount == 7u);
  assert(kReturnWidthBytes == 4u);
  assert(kStackArgumentWords == 0u);
  assert(kCalleeCleanupBytes == 0u);
  assert(!kHasReceiver);
  assert(kMemoryReads == 2u);
  assert(kMemoryStores == 0u);

  // The root's own twenty bytes.
  assert(kTargetBytes[0] == 0xe8u);   // CALL rel32
  assert(kTargetBytes[5] == 0x85u);   // TEST EAX,EAX
  assert(kTargetBytes[7] == 0x74u);   // JE rel8
  assert(kTargetBytes[9] == 0x8bu);   // MOV ECX,EAX
  assert(kTargetBytes[11] == 0xe9u);  // JMP rel32
  assert(kTargetBytes[16] == 0x83u);  // OR EAX,imm8
  assert(kTargetBytes[18] == 0xffu);  // imm8 = ff
  assert(kTargetBytes[19] == 0xc3u);  // bare RET

  // The two direct targets' own bytes, and the addresses decoded from them.
  assert(kReceiverReaderBytes[0] == 0xa1u);
  assert(kReceiverReaderBytes[5] == 0xc3u);
  assert(kFieldReaderBytes[0] == 0x8bu);
  assert(kFieldReaderBytes[1] == 0x41u);
  assert(kFieldReaderBytes[2] == 0x20u);
  assert(kFieldReaderBytes[3] == 0xc3u);

  const Word decoded_global =
      static_cast<Word>(static_cast<std::uint32_t>(kReceiverReaderBytes[1]) |
                        (static_cast<std::uint32_t>(kReceiverReaderBytes[2]) << 8) |
                        (static_cast<std::uint32_t>(kReceiverReaderBytes[3]) << 16) |
                        (static_cast<std::uint32_t>(kReceiverReaderBytes[4]) << 24));
  assert(decoded_global == kReceiverGlobalVa);
  assert(kReceiverGlobalVa == 0x0167eaecu);

  // The displacements decode to the two direct targets named in the listing.
  const std::int32_t call_disp = static_cast<std::int32_t>(
      static_cast<std::uint32_t>(kTargetBytes[1]) |
      (static_cast<std::uint32_t>(kTargetBytes[2]) << 8) |
      (static_cast<std::uint32_t>(kTargetBytes[3]) << 16) |
      (static_cast<std::uint32_t>(kTargetBytes[4]) << 24));
  assert(static_cast<Word>(kEntryVa + 5 + call_disp) == 0x00b3d320u);
  const std::int32_t jmp_disp = static_cast<std::int32_t>(
      static_cast<std::uint32_t>(kTargetBytes[12]) |
      (static_cast<std::uint32_t>(kTargetBytes[13]) << 8) |
      (static_cast<std::uint32_t>(kTargetBytes[14]) << 16) |
      (static_cast<std::uint32_t>(kTargetBytes[15]) << 24));
  assert(static_cast<Word>(kEntryVa + 16 + jmp_disp) == 0x00a42730u);

  // The forwarded displacement and the sentinel.
  assert(kForwardedFieldDisplacement == 0x20u);
  assert(kNullSentinel == 0xffffffffu);

  // The modelled images: one non-guard word in the receiver image, an opaque
  // byte run for the forwarded one, and the field view really is the slot the
  // header names.
  static_assert(sizeof(ReceiverGlobalImage) == (2 * kReceiverGuardWords + 1) * sizeof(std::uint32_t),
                "the modelled receiver image is two guard runs around one slot");
  assert(&g_0167eaec == &g_receiver_global_image.slot);
  assert(g_forwarded_receiver == g_forwarded_receiver_image.bytes);
  assert(reinterpret_cast<std::uint8_t*>(&g_forwarded_receiver_field) ==
         g_forwarded_receiver + kForwardedFieldDisplacement);
  assert(reinterpret_cast<std::uintptr_t>(&g_forwarded_receiver_field) -
             reinterpret_cast<std::uintptr_t>(g_forwarded_receiver) ==
         kForwardedFieldDisplacement);
}

}  // namespace

int main() {
  test_non_null_path_returns_the_forwarded_word();
  test_reads_the_forwarded_displacement_and_not_a_neighbour();
  test_null_path_returns_the_all_ones_sentinel();
  test_null_test_covers_all_thirty_two_bits();
  test_tracks_current_contents_not_a_cached_or_constant_value();
  test_whole_eax_carries_the_word_and_esp_is_untouched();
  test_inlined_and_called_spellings_agree();
  test_writes_nothing_on_either_hop();
  test_machine_facts();
  return 0;
}
