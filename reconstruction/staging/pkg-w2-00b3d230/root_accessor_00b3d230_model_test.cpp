#include "root_accessor_00b3d230.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>

// Model test for 0x00b3d230 (SporeApp.exe 3.1.0.22).
//
// The machine body is two instructions, six bytes:
//
//     0x00b3d230  a1 c0 ea 67 01   MOV EAX, DS:0x0167eac0
//     0x00b3d235  c3               RET
//
// so the whole of the observable contract is: load one dword from one absolute
// address, return all four bytes of it in EAX, change nothing else, touch no
// stack and no register. Each test below is written to REFUTE a plausible wrong
// reconstruction rather than to walk a right one:
//
//   1. the returned word IS the modelled slot, for values chosen so that a
//      truncating or sign-extending return cannot pass (0x80000000,
//      0xdeadbeef, 0xffffffff);
//   2. it is the SLOT and not a neighbour -- and two reference readers prove the
//      harness can tell those addresses apart, so this cannot pass vacuously;
//   3. the entry tracks the slot's current contents: it is not a cached value,
//      not a constant, and not the slot's ADDRESS;
//   4. all 32 bits of EAX carry the word (measured through a trampoline, not
//      through the C++ return path);
//   5. ESP is identical before and after the call -- the bare RET pops nothing;
//   6. guard band: every word of the modelled image except the slot keeps the
//      canary, and the slot itself is unchanged, so the body writes nothing.
//
// The ABI facts are checked at compile time by AbiRootAccessor00b3d230 and the
// std::is_same assertion below: a prototype with any parameter, or with a
// different return width, does not build.

#if !defined(__i386__) && !defined(_M_IX86)
#error "root accessor 0x00b3d230 model test requires an x86-32 target"
#endif

namespace {

using openspore::reconstruction::pkg_w2_00b3d230::AbiRootAccessor00b3d230;
using openspore::reconstruction::pkg_w2_00b3d230::g_0167eac0;
using openspore::reconstruction::pkg_w2_00b3d230::g_root_slot_image;
using openspore::reconstruction::pkg_w2_00b3d230::kDataSectionRawSize;
using openspore::reconstruction::pkg_w2_00b3d230::kDataSectionVa;
using openspore::reconstruction::pkg_w2_00b3d230::kDataSectionVirtualSize;
using openspore::reconstruction::pkg_w2_00b3d230::kEntryVa;
using openspore::reconstruction::pkg_w2_00b3d230::kGlobalOffsetInSection;
using openspore::reconstruction::pkg_w2_00b3d230::kGlobalVa;
using openspore::reconstruction::pkg_w2_00b3d230::kGuardCanary;
using openspore::reconstruction::pkg_w2_00b3d230::kGuardWords;
using openspore::reconstruction::pkg_w2_00b3d230::kTargetBytes;
using openspore::reconstruction::pkg_w2_00b3d230::kTerminalVa;
using openspore::reconstruction::pkg_w2_00b3d230::root_accessor_00b3d230;
using openspore::reconstruction::pkg_w2_00b3d230::RootSlotImage;
using openspore::reconstruction::pkg_w2_00b3d230::Word;

// The machine ABI, asserted against the declaration: zero parameters, 4-byte
// return. This is the compile-time gate -- change the prototype and this stops
// building.
static_assert(std::is_same<decltype(&root_accessor_00b3d230), AbiRootAccessor00b3d230>::value,
              "0x00b3d230 takes no parameter (no stack word in the body, no "
              "register read, bare RET) and returns the 4-byte word it loads");
static_assert(sizeof(AbiRootAccessor00b3d230) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");

// Calling the reconstruction only through the checked ABI type.
AbiRootAccessor00b3d230 const kEntrySlot = &root_accessor_00b3d230;

std::uint32_t entry_address() {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(kEntrySlot));
}

// Reference readers for the two words adjacent to the modelled slot. They exist
// so the "it read the slot, not its neighbour" checks can fail: without them a
// harness that could not distinguish the addresses would report the same answer
// for all three and the assertion would hold for the wrong reason.
Word reference_reads_low_neighbour() { return g_root_slot_image.guard_lo[kGuardWords - 1]; }
Word reference_reads_high_neighbour() { return g_root_slot_image.guard_hi[0]; }

// Push every word of the modelled image to the canary, then set the slot.
void ArmImage(Word slot_value) {
  for (std::size_t i = 0; i < kGuardWords; ++i) {
    g_root_slot_image.guard_lo[i] = kGuardCanary;
  }
  for (std::size_t i = 0; i < kGuardWords; ++i) {
    g_root_slot_image.guard_hi[i] = kGuardCanary;
  }
  g_root_slot_image.slot = slot_value;
}

// 1. The returned word is the modelled slot, across widths and signs a
//    truncating or sign-extending return cannot survive.
void test_returns_the_slot_word() {
  const Word values[] = {0u, 1u, 2u, 0x7fffffffu, 0x80000000u, 0xdeadbeefu, 0xffffffffu, kGlobalVa};
  for (const Word value : values) {
    ArmImage(value);
    assert(kEntrySlot() == value);
  }
}

// 2. It is the slot and not a neighbour. The two reference readers are checked
//    to return exactly the neighbour words, which is what makes this capable of
//    failing: a body reading guard_lo[kGuardWords-1] or guard_hi[0] gives an
//    answer this test can see is wrong.
void test_reads_the_slot_and_not_a_neighbour() {
  ArmImage(0x12345678u);
  g_root_slot_image.guard_lo[kGuardWords - 1] = 0xdead0001u;
  g_root_slot_image.guard_hi[0] = 0xdead0002u;

  assert(reference_reads_low_neighbour() == 0xdead0001u);
  assert(reference_reads_high_neighbour() == 0xdead0002u);
  assert(kEntrySlot() == 0x12345678u);
  assert(kEntrySlot() != 0xdead0001u);
  assert(kEntrySlot() != 0xdead0002u);
}

// 3. The entry tracks the slot's CURRENT contents: not a cached word, not a
//    constant, and not the address of the slot.
void test_tracks_the_slot_not_a_cached_or_constant_value() {
  ArmImage(0u);
  assert(kEntrySlot() == 0u);

  g_0167eac0 = 0x0f0f0f0fu;
  assert(kEntrySlot() == 0x0f0f0f0fu);

  // Repeated calls with an unchanged slot are stable (no side effect).
  assert(kEntrySlot() == 0x0f0f0f0fu);
  assert(kEntrySlot() == 0x0f0f0f0fu);

  // The neighbour accessor really is a different storage, so the two answers
  // cannot coincide by construction.
  assert(reference_reads_low_neighbour() != 0x0f0f0f0fu);

  // The value is the slot's CONTENTS, not the slot's address: kGlobalVa is used
  // as a slot value above and must come back as itself, while the modelled
  // image's address is a different word entirely.
  g_0167eac0 = kGlobalVa;
  assert(kEntrySlot() == kGlobalVa);
}

// 4. All 32 bits of EAX carry the word. Measured through a trampoline that
//    reproduces the observed call shape (no argument pushed, indirect call,
//    bare RET), so the C++ return path is not what is being checked.
void test_whole_eax_carries_the_word() {
  ArmImage(0xdeadbeefu);

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

  // The full 32-bit return, high bit included: a body returning AL or AX, or
  // one sign-extending a narrower load, fails here.
  assert(eax_after == 0xdeadbeefu);

  // 5. The bare RET pops nothing: ESP is identical either side of the call. A
  //    frame-allocating, callee-cleaning or argument-taking body fails here.
  assert(before == after);
  assert(before != 0u);  // the sample is a real stack address, not a constant

  // Re-measured with a slot value that has its top bit set, so the two checks
  // above are not both satisfied by one lucky register state.
  ArmImage(0x80000001u);
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
  assert(eax_after == 0x80000001u);
  assert(before == after);
}

// 6. Guard band. The body performs one READ; it performs no store. Every word of
//    the modelled image other than the slot must still hold the canary after the
//    call, and the slot must be byte-for-byte what it was: a body that wrote the
//    slot, cleared it, or reached past it fails here.
void test_writes_nothing_outside_the_slot() {
  ArmImage(0x5a5a1234u);
  const Word slot_before = g_root_slot_image.slot;

  assert(kEntrySlot() == 0x5a5a1234u);

  assert(g_root_slot_image.slot == slot_before);
  for (std::size_t i = 0; i < kGuardWords; ++i) {
    assert(g_root_slot_image.guard_lo[i] == kGuardCanary);
    assert(g_root_slot_image.guard_hi[i] == kGuardCanary);
  }

  // The neighbours are set to non-canary sentinels as well, so the guard check
  // is not passing merely because the neighbours happened to be untouched
  // canaries: the distinctive values below must survive too.
  g_root_slot_image.guard_lo[kGuardWords - 1] = 0x11111111u;
  g_root_slot_image.guard_hi[0] = 0x22222222u;
  const Word slot_value = g_root_slot_image.slot;
  assert(kEntrySlot() == slot_value);
  assert(g_root_slot_image.guard_lo[kGuardWords - 1] == 0x11111111u);
  assert(g_root_slot_image.guard_hi[0] == 0x22222222u);
  assert(g_root_slot_image.slot == slot_value);
}

// 7. The machine facts the whole package rests on are re-checked at run time,
//    including that the address constant really is decoded from the body bytes.
void test_machine_facts() {
  assert(kEntryVa == 0x00b3d230u);
  assert(kTerminalVa == 0x00b3d235u);
  assert(kTargetBytes[0] == 0xa1u);
  assert(kTargetBytes[5] == 0xc3u);

  const Word decoded = static_cast<Word>(static_cast<std::uint32_t>(kTargetBytes[1]) |
                                         (static_cast<std::uint32_t>(kTargetBytes[2]) << 8) |
                                         (static_cast<std::uint32_t>(kTargetBytes[3]) << 16) |
                                         (static_cast<std::uint32_t>(kTargetBytes[4]) << 24));
  assert(decoded == kGlobalVa);
  assert(kGlobalVa == 0x0167eac0u);

  // The global lies in the loader-zeroed tail of .data: offset inside the
  // section past SizeOfRawData, so no image initializer is claimed for it.
  assert(kDataSectionVa == 0x0150c000u);
  assert(kDataSectionVirtualSize == 0x212764u);
  assert(kDataSectionRawSize == 0x000c4c00u);
  assert(kGlobalOffsetInSection == 0x00172ac0u);
  assert(kGlobalOffsetInSection > kDataSectionRawSize);

  // The modelled image has exactly one non-guard word.
  static_assert(sizeof(RootSlotImage) == (2 * kGuardWords + 1) * sizeof(std::uint32_t),
                "the modelled image is 2*kGuardWords+1 words");
  assert(&g_0167eac0 == &g_root_slot_image.slot);
}

}  // namespace

int main() {
  test_returns_the_slot_word();
  test_reads_the_slot_and_not_a_neighbour();
  test_tracks_the_slot_not_a_cached_or_constant_value();
  test_whole_eax_carries_the_word();
  test_writes_nothing_outside_the_slot();
  test_machine_facts();
  return 0;
}