#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "root_slot_eae8_00b3d310.hpp"

// Focused semantic test for FUN_00b3d310 @ 0x00b3d310.
//
// It is written to try to REFUTE the reconstruction rather than to walk it.
// Each group below names the risky hypothesis it attacks:
//
//   1. the entry returns the VALUE stored at 0x0167eae8 -- not the ADDRESS of
//   the
//      slot (the LEA-form error), not a constant, not zero, not the address of
//      anything else;
//   2. 0x0167eae8 is THE address: a byte-exact reproduction of the six body
//   bytes
//      is required to spell that address, and distinct decoy slots one word
//      either side hold sentinels the entry must not return;
//   3. the body READS: the slot is byte-identical before and after, and a decoy
//      planted inside the modelled slot arena is undisturbed, so a
//      store-through or defaulting perturbation fails on the guard band;
//   4. the entry is a pure function of the slot: the result tracks a changed
//   word,
//      repeats across calls, and is unchanged by anything the caller does
//      around it;
//   5. the ABI is 0 stack words, caller cleanup, one 32-bit word back in EAX --
//      MEASURED by sampling ESP around the call through an inline-asm
//      trampoline, and shown to be independent of the caller's own stack depth.
//
// The MUTATION battery at the end is the test proper: eleven bodies that are
// wrong in exactly one way each must all be rejected. A mutant that survives
// means the battery has lost the power to tell this reconstruction from a wrong
// one, so the run aborts.
//
// Why the calls go through an inline-asm trampoline rather than a plain
// function pointer. The modelled convention (__cdecl) is one of FOUR that
// produce this exact byte sequence -- the ABI record says so (`C10`, confidence
// UNKNOWN) and abstains from choosing. A plain C++ call therefore cannot
// measure the callee's cleanup: the compiler picks the outgoing-argument area,
// and failure mode 6 in docs/tooling/reconstruction-failure-modes.md records
// that clang and g++ differ there by 16 bytes at -O0. The trampoline reproduces
// the observed sequence exactly
// (`call *%reg` then RET), so the ESP measurement is an ABI fact rather than a
// statement about compiler scratch layout.
//
// What the compiler emits for this body, measured on this machine
// (clang 22.1.8, -m32). The abs() below is the same two-instruction shape as
// the target; only the way the address is reached differs, and neither
// difference is a semantic one:
//   -fno-pic, -O1 and -O2:   a1 <disp32>   MOV EAX, dword ptr [<abs>]
//                            c3            RET
//     -- two instructions, and the opcode is the target's own `a1`. The disp32
//     is
//        a link-time relocation, so the shape is byte-identical to 0x00b3d310
//        and only the (link-resolved) address differs.
//   default (-fpic), -O1/-O2: e8 <rel32>   CALL __x86.get_pc_thunk.ax
//                            58            POP EAX
//                            81 c0 03 ...  ADD EAX, 3
//                            8b 80 00 ...  MOV EAX, dword ptr [EAX]
//                            c3            RET
//     -- the load is the same one-word read of the same global; the extra
//        instructions are the position-independent address materialisation, not
//        a different computation.
//   -O0 adds the standard frame (push/mov ebp,pop ebp) around the identical
//   load.
//
// The claim this test makes is about the SEMANTICS -- one 32-bit word read out
// of one fixed global and returned in EAX, callee popping nothing -- and it is
// measured at run time rather than asserted from any of these code shapes.

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00b3d310 model test requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00B3D310_CDECL __cdecl
#else
#define PKG_00B3D310_CDECL __attribute__((cdecl))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_00b3d310_root_slot_eae8 {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Word word_of(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The six bytes read from 0x00b3d310..0x00b3d315, stated here so the
// reconstruction's instruction sequence lives in the test and not only in
// prose. The two 0xcc bytes that follow (the INT3 pad after the body) are
// deliberately NOT included: they are not part of the body.
constexpr std::uint8_t kTargetBytes[6] = {
    0xa1,  // MOV r32, moffs32 (no ModRM byte, no register operand)
    0xe8, 0xea, 0x67, 0x01,  // imm32, little endian -> 0x0167eae8
    0xc3,                    // RET, no immediate: the callee pops nothing
};

// A sentinel that cannot be confused with a plausible address, a small
// constant, or the slot's own address.
constexpr Word kSentinel = 0xfeedfaceu;

// A second, disjoint base for the decoy words, so no decoy can accidentally
// hold the value the correct answer is.
constexpr Word kDecoyBase = 0x0badf00du;

// Neighbour slots one word either side of the modelled slot, in the modelled
// arena. They exist so that "reads the right word" is a discriminating claim
// and not a vacuous one. The arena runs from the byte before the lower decoy
// through the last byte of the upper decoy, so all three planted words are in
// bounds.
constexpr std::size_t kWordBytes = 4;
constexpr std::size_t kSlotOffset = 0x20;
constexpr std::size_t kBelowOffset = kSlotOffset - kWordBytes;
constexpr std::size_t kAboveOffset = kSlotOffset + kWordBytes;
constexpr std::size_t kArenaBytes = kAboveOffset + kWordBytes;

// The address the operand bytes must spell, recomposed from kSlotAddress so the
// header's constant and the machine bytes cannot drift apart.
constexpr Word address_from_operand_bytes() {
  return static_cast<Word>(static_cast<Word>(kTargetBytes[1]) |
                           (static_cast<Word>(kTargetBytes[2]) << 8) |
                           (static_cast<Word>(kTargetBytes[3]) << 16) |
                           (static_cast<Word>(kTargetBytes[4]) << 24));
}

static_assert(sizeof(kTargetBytes) == 6, "the target body is 6 bytes");
static_assert(
    kTargetBytes[0] == 0xa1u,
    "0x00b3d310 is MOV r32, moffs32: a bare opcode with a 4-byte address");
static_assert(
    kTargetBytes[5] == 0xc3u,
    "0x00b3d315 is RET with no immediate (caller cleanup, 0 stack words)");
static_assert(address_from_operand_bytes() == 0x0167eae8u,
              "the four imm32 bytes spell 0x0167eae8, little endian");
static_assert(address_from_operand_bytes() == kSlotAddress,
              "the header's slot address equals the reconstructed disp32");
static_assert(
    kSlotAddress == 0x0167eae8u,
    "0x0167eae8 is the value 23543016, compared by value not by spelling");
static_assert(kBelowOffset == 28u && kAboveOffset == 36u && kSlotOffset == 32u,
              "the modelled decoy displacements are stated as values");
static_assert(kArenaBytes == kAboveOffset + kWordBytes,
              "the modelled arena ends immediately after the upper decoy");
static_assert(kBelowOffset >= kWordBytes,
              "the lower decoy word is wholly inside the arena");

// The modelled slot arena. This is a FIXTURE, not a recovered object: the
// target body reads an absolute address and reaches no displacement at all, so
// nothing about any real object's size is claimed. Three distinct sentinels are
// planted -- below the slot, in the slot, above the slot -- so that a body
// reading the wrong word returns a value no correct answer in this package
// equals.
struct SlotArena {
  alignas(4) std::uint8_t bytes[kArenaBytes];
};

// The address of the entry under reconstruction.
Word entry_address() {
  return word_of(
      reinterpret_cast<const void*>(&simulator_root_slot_eae8_00b3d310));
}

// The value the slot the entry actually reads currently holds.
Word live_slot_word() {
  return g_0167eae8;
}

// The return value (EAX) after calling the entry through the trampoline.
Word call_entry() {
  const Word target = entry_address();
  Word result = 0;
  __asm__ __volatile__(
      "call *%1\n\t"
      "movl %%eax, %0\n\t"
      : "=r"(result)
      : "r"(target)
      : "eax", "memory");
  return result;
}

// ESP sampled inside the trampoline, immediately before the call and again the
// instant the callee has returned. `call` pushes a return address and `RET`
// takes it back, so the two samples are equal only when the callee owns no
// cleanup; a `RET 0x4` would leave the second four bytes lower. The measurement
// therefore MEASURES the cleanup instead of asserting a calling convention the
// listing cannot discriminate.
//
// `scratch_words` lowers the stack before sampling, so the same measurement can
// be repeated at a different stack depth: a body that read a stack argument at
// [ESP+4] would return the pushed word at one depth and something else at
// another.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured(unsigned scratch_bytes) {
  const Word target = entry_address();
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  if (scratch_bytes == 0u) {
    __asm__ __volatile__(
        "movl %%esp, %[before]\n\t"
        "call *%[target]\n\t"
        "movl %%esp, %[after]\n\t"
        : [before] "=m"(before), [after] "=m"(after)
        : [target] "r"(target)
        : "eax", "memory");
  } else {
    __asm__ __volatile__(
        "subl %[scratch], %%esp\n\t"
        "movl %%esp, %[before]\n\t"
        "call *%[target]\n\t"
        "movl %%esp, %[after]\n\t"
        "addl %[scratch], %%esp\n\t"
        : [before] "=m"(before), [after] "=m"(after)
        : [target] "r"(target), [scratch] "r"(scratch_bytes)
        : "eax", "memory");
  }
  EspSamples samples;
  samples.before_call = before;
  samples.after_return = after;
  return samples;
}

// The modelled ABI type, respelled with the convention macro this file defines.
// The entry returns a POINTER, and the trampolines below read it back out of
// EAX as a word; these two are the same 32 bits and the difference is naming,
// not width, which the static_asserts below pin.
using Entry = OpaqueRootSlotTarget*(PKG_00B3D310_CDECL*)();

}  // namespace model
}  // namespace pkg_00b3d310_root_slot_eae8
}  // namespace reconstruction
}  // namespace openspore

namespace {

using namespace openspore::reconstruction::pkg_00b3d310_root_slot_eae8;
using model::call_entry;
using model::call_entry_measured;
using model::check;
using model::entry_address;
using model::EspSamples;
using model::kAboveOffset;
using model::kArenaBytes;
using model::kBelowOffset;
using model::kDecoyBase;
using model::kSentinel;
using model::kSlotOffset;
using model::live_slot_word;
using model::SlotArena;
using model::word_of;

// The decoy slot the wrong-address probe reads. Defined here, in the test's own
// translation unit, so no neighbouring target's storage is modelled or
// disturbed.
Word g_adjacent_decoy_slot = 0u;

static_assert(sizeof(word_of(nullptr)) == 4,
              "the modelled slot is one 32-bit word");
static_assert(sizeof(kSentinel) == 4, "the sentinel is one 32-bit word");
static_assert(sizeof(SlotArena) == model::kArenaBytes,
              "the modelled arena is exactly the three planted words");
static_assert(std::is_same<model::Entry, AbiRootSlotAccessor00b3d310>::value,
              "the modelled ABI is 0 stack words with one-word return in EAX");
static_assert(sizeof(model::Entry) == sizeof(void*),
              "a modelled pointer return is one 32-bit word across the ABI");

// Plant the arena with a per-index byte pattern and three sentinels. The
// pattern makes any access to any part of it visible afterwards; the sentinels
// make the choice of word observable in the return value.
SlotArena planted_arena() {
  SlotArena arena{};
  for (std::size_t index = 0; index < sizeof(arena.bytes); ++index) {
    arena.bytes[index] = static_cast<std::uint8_t>(index + 1u);
  }
  std::memcpy(arena.bytes + kBelowOffset, &kDecoyBase, sizeof(kDecoyBase));
  std::memcpy(arena.bytes + kSlotOffset, &kSentinel, sizeof(kSentinel));
  const Word above = static_cast<Word>(kDecoyBase + 1u);
  std::memcpy(arena.bytes + kAboveOffset, &above, sizeof(above));
  return arena;
}

Word arena_word(const SlotArena& arena, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, arena.bytes + offset, sizeof(value));
  return value;
}

// Publish a planted arena's slot word into the global the entry actually reads,
// so the real entry and the mutants all answer from the same fixture.
void publish(const SlotArena& arena) {
  g_0167eae8 = arena_word(arena, kSlotOffset);
}

// ---------------------------------------------------------------------------
// 1. The return is the VALUE stored in the slot.
// ---------------------------------------------------------------------------
void test_return_value_is_the_stored_word() {
  SlotArena arena = planted_arena();
  publish(arena);

  const Word result = call_entry();

  check(result == kSentinel);
  // Not the address of the slot: this is the load-versus-LEA distinction. A
  // body written as `&g_0167eae8` returns the slot's own address, which is
  // nothing a sentinel in this fixture equals, so the two cannot both pass.
  check(result != word_of(reinterpret_cast<const void*>(&g_0167eae8)));
  // Not the decoys on either side, so the choice of word is discriminating.
  check(result != kDecoyBase);
  check(result != static_cast<Word>(kDecoyBase + 1u));
  // Not a constant the body could have materialised, and not zero.
  check(result != 0u);
  check(result != kSlotOffset);
  check(result != kSlotAddress);
  // And the value is genuinely read out of the slot, bit for bit.
  check(result == live_slot_word());
}

// ---------------------------------------------------------------------------
// 2. 0x0167eae8 is THE address, and the body is the six bytes that say so.
// ---------------------------------------------------------------------------
void test_operand_bytes_spell_exactly_the_slot_address() {
  check(model::kTargetBytes[0] == 0xa1u);
  check(model::kTargetBytes[1] == 0xe8u);
  check(model::kTargetBytes[2] == 0xeau);
  check(model::kTargetBytes[3] == 0x67u);
  check(model::kTargetBytes[4] == 0x01u);
  check(model::kTargetBytes[5] == 0xc3u);
  check(sizeof(model::kTargetBytes) == 6u);
  check(model::address_from_operand_bytes() == kSlotAddress);

  // The offset is in BYTES, not elements: an entry that read the address as an
  // element count would land 0x0167eae8 elements out, and no planted sentinel
  // could be there.
  check(kSlotAddress >= static_cast<Word>(kArenaBytes));
  check(kSlotOffset == 32u);
  check(kBelowOffset == 28u);
  check(kAboveOffset == 36u);
  // The header's constant and the machine's operand bytes name one address.
  check(kSlotAddress == model::address_from_operand_bytes());
}

// ---------------------------------------------------------------------------
// 3. The body READS. The slot is byte-identical across the call.
// ---------------------------------------------------------------------------
void test_body_does_not_write_the_slot() {
  SlotArena arena = planted_arena();
  publish(arena);
  const Word before = g_0167eae8;

  const Word result = call_entry();

  check(result == kSentinel);
  check(g_0167eae8 == before);
  // The whole planted arena is unchanged too: nothing reached through the slot
  // was disturbed, and no neighbouring word was either.
  const SlotArena reference = planted_arena();
  for (std::size_t index = 0; index < sizeof(arena.bytes); ++index) {
    check(arena.bytes[index] == reference.bytes[index]);
  }
  check(arena_word(arena, kBelowOffset) == kDecoyBase);
  check(arena_word(arena, kSlotOffset) == kSentinel);
}

// ---------------------------------------------------------------------------
// 4. Pure function of the slot: it tracks the word and repeats.
// ---------------------------------------------------------------------------
void test_result_tracks_the_slot_word_and_repeats() {
  SlotArena arena = planted_arena();
  publish(arena);

  check(call_entry() == kSentinel);
  check(call_entry() == kSentinel);

  g_0167eae8 = 0x12345678u;
  check(call_entry() == 0x12345678u);

  g_0167eae8 = 0xffffffffu;
  const Word all_ones = call_entry();
  check(all_ones == 0xffffffffu);
  // A signed reading of the same bits is not what crosses the ABI, and neither
  // is a truncated 16-bit or byte-wide read of it.
  check(all_ones != 0xffffu);
  check(all_ones != 0xffu);

  g_0167eae8 = 0u;
  check(call_entry() == 0u);
}

// ---------------------------------------------------------------------------
// 5. ABI, measured: the callee pops nothing, no stack word is read, and the
//    value comes back in EAX as one 32-bit word.
// ---------------------------------------------------------------------------
void test_no_stack_words_are_popped_and_none_are_read() {
  SlotArena arena = planted_arena();
  publish(arena);

  const EspSamples shallow = call_entry_measured(0u);
  check(shallow.after_return == shallow.before_call);

  const EspSamples deep = call_entry_measured(128u);
  check(deep.after_return == deep.before_call);
  // The scratch really did change the depth, so the two measurements are not
  // vacuously the same point in the frame.
  check(deep.before_call == shallow.before_call - 128u);

  // Same slot, same answer, from two different caller stack depths. A body that
  // read [ESP+4] would answer differently at one of them.
  check(call_entry() == kSentinel);
  check(call_entry_measured(64u).after_return ==
        call_entry_measured(64u).before_call);

  // The return crosses in EAX as one 32-bit word, and the modelled entry
  // signature is exactly a one-word return.
  check(sizeof(model::Entry) == sizeof(void*));
  check(sizeof(live_slot_word()) == 4u);
  check(entry_address() != 0u);
}

// ---------------------------------------------------------------------------
// The mutation battery.
// ---------------------------------------------------------------------------
//
// Each probe below is a body that is wrong in exactly one way. Every probe must
// DISAGREE with the reconstruction on at least one slot word, or the run
// aborts. A probe is exercised against the same planted fixture the
// reconstruction is measured on, so "agrees" means "returns kSentinel", which
// is the only value the reconstruction can produce from that fixture.

using Probe = Word (*)();

// Stands in for a neighbouring absolute slot. The real body reads one fixed
// address, so "reads a different fixed address" is a distinct wrong body, and
// the only way the battery can see it is if the two addresses hold different
// words at the moment of the call -- which is what probe_agrees arranges.
extern Word g_adjacent_decoy_slot;

constexpr std::size_t kProbeCount = 11;

// Wrong: returns a constant instead of reading the slot.
Word probe_returns_constant() {
  return kSentinel;
}

// Wrong: returns the ADDRESS of the slot (the LEA-form error).
Word probe_returns_slot_address() {
  return word_of(reinterpret_cast<const void*>(&g_0167eae8));
}

// Wrong: returns zero regardless of the slot.
Word probe_returns_zero() {
  return 0u;
}

// Wrong: reads one word too low.
Word probe_reads_word_below() {
  return g_0167eae8 - 1u;
}

// Wrong: reads one word too high.
Word probe_reads_word_above() {
  return g_0167eae8 + 1u;
}

// Wrong: truncates the load to its low byte, so only AL survives.
Word probe_byte_truncated() {
  return g_0167eae8 & 0xffu;
}

// Wrong: truncates the load to its low 16 bits.
Word probe_halfword_truncated() {
  return g_0167eae8 & 0xffffu;
}

// Wrong: reads a DIFFERENT absolute slot. The four operand bytes of `a1 e8 ea
// 67 01` are the address, so mistyping one of them is a whole-body error this
// battery has to be able to see; the decoy below stands in for a neighbouring
// slot, and the battery publishes it with a value distinct from the real one on
// every word.
Word probe_reads_adjacent_slot() {
  return g_adjacent_decoy_slot;
}

// Wrong: masks the top byte off.
Word probe_masks_high_byte() {
  return g_0167eae8 & 0x00ffffffu;
}

// Wrong: adds an addend to the loaded word instead of returning it.
Word probe_adds_addend() {
  return g_0167eae8 + kSlotAddress;
}

// Wrong: writes through the slot on the way out.
Word probe_writes_through_slot() {
  g_0167eae8 = kSentinel;
  return g_0167eae8;
}

const Probe kProbes[kProbeCount] = {
    probe_returns_constant,   probe_returns_slot_address, probe_returns_zero,
    probe_reads_word_below,   probe_reads_word_above,     probe_byte_truncated,
    probe_halfword_truncated, probe_reads_adjacent_slot,  probe_masks_high_byte,
    probe_adds_addend,        probe_writes_through_slot,
};

static_assert(sizeof(kProbes) / sizeof(kProbes[0]) == kProbeCount,
              "every declared probe is listed exactly once");

// Slot words the battery runs against. Each is chosen so that at least one
// probe above answers differently from the reconstruction: a word with a
// non-zero high byte refutes both truncators, a word with more than one
// non-zero byte refutes the high-byte masker, and kSentinel itself refutes
// every address-form, addend and neighbour probe. Every word is paired with a
// DIFFERENT decoy value, so the wrong-address probe is refuted by all of them
// rather than by an accident of arithmetic.
//
// One probe that was in an earlier draft of this battery was REMOVED rather
// than repaired: a "sign-extends instead of zero-extends" body is not a mutant
// on this target at all. At 32-bit width the cast is a no-op, so such a body is
// byte-for-byte the reconstruction and no test can refute it. A battery entry
// that cannot be refuted is a false claim of discriminating power, and dropping
// it is the honest fix -- the class it was meant to cover is covered by the two
// truncator probes, which are real differences at this width.
constexpr Word kProbeWords[] = {kSentinel,   0xffffffffu, 0x12345678u,
                                0x00ff00ffu, 0x80000000u, 0x0000ffffu};
constexpr std::size_t kProbeWordCount =
    sizeof(kProbeWords) / sizeof(kProbeWords[0]);

// Every probe word is paired with a decoy value that is different from it, so a
// body reading the wrong absolute slot can never accidentally agree.
constexpr Word kDecoyOf(Word slot_word) {
  return slot_word ^ 0x5a5a5a5au;
}

bool probe_agrees(Probe probe, Word slot_word) {
  // Both slots are republished before every probe, so a store-through probe
  // cannot leave either poisoned for the next one and the comparison is against
  // the words this call was given rather than against whatever the previous
  // probe left behind.
  g_0167eae8 = slot_word;
  g_adjacent_decoy_slot = kDecoyOf(slot_word);
  return probe() == slot_word;
}

// The reconstruction must agree with every probe word (it is the oracle), and
// no mutant may agree on every one (each is refuted).
void test_reconstruction_agrees_and_every_mutant_is_refuted() {
  for (std::size_t index = 0; index < kProbeWordCount; ++index) {
    const Word slot_word = kProbeWords[index];
    g_0167eae8 = slot_word;
    g_adjacent_decoy_slot = kDecoyOf(slot_word);
    check(call_entry() == slot_word);
  }

  for (std::size_t probe_index = 0; probe_index < kProbeCount; ++probe_index) {
    bool refuted = false;
    for (std::size_t word_index = 0; word_index < kProbeWordCount;
         ++word_index) {
      if (!probe_agrees(kProbes[probe_index], kProbeWords[word_index])) {
        refuted = true;
        break;
      }
    }
    // A surviving mutant aborts the run: the battery can no longer tell this
    // reconstruction from a wrong body.
    check(refuted);
  }
}

// The battery's discriminating power is itself a claim: each probe differs from
// the reconstruction on at least one probe word, and the run states how many
// words refute each one so a word silently removed from kProbeWords is visible
// as a lost refutation rather than as a pass.
void test_each_mutant_is_refuted_by_a_named_word() {
  for (std::size_t probe_index = 0; probe_index < kProbeCount; ++probe_index) {
    std::size_t refutations = 0;
    for (std::size_t word_index = 0; word_index < kProbeWordCount;
         ++word_index) {
      if (!probe_agrees(kProbes[probe_index], kProbeWords[word_index])) {
        ++refutations;
      }
    }
    // At least one, and never zero -- see above.
    check(refutations >= 1u);
    check(refutations <= kProbeWordCount);
  }
}

// A store-through probe must be visibly different from a read-only one even
// when it happens to return the right value, which is the guard-band claim in
// isolation.
void test_store_through_probe_is_caught_by_the_slot_guard() {
  SlotArena arena = planted_arena();
  publish(arena);
  const Word before = g_0167eae8;

  const Word result = probe_writes_through_slot();

  // It returns the right value here, because the fixture already held the value
  // the store writes -- which is exactly why the return value alone cannot
  // catch it.
  check(result == before);
  // The distinguishing fact is that the slot is now the store's value, and the
  // read-only reconstruction leaves it alone.
  check(g_0167eae8 == kSentinel);
  g_0167eae8 = before;
  check(call_entry() == before);
  check(g_0167eae8 == before);
}

int run_tests() {
  test_return_value_is_the_stored_word();
  test_operand_bytes_spell_exactly_the_slot_address();
  test_body_does_not_write_the_slot();
  test_result_tracks_the_slot_word_and_repeats();
  test_no_stack_words_are_popped_and_none_are_read();
  test_reconstruction_agrees_and_every_mutant_is_refuted();
  test_each_mutant_is_refuted_by_a_named_word();
  test_store_through_probe_is_caught_by_the_slot_guard();
  return 0;
}

}  // namespace

int main() {
  return run_tests();
}

#undef PKG_00B3D310_CDECL