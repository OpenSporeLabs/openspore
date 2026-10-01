#include "root_slot_00b3d260.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

// Model test for 0x00b3d260 (SporeApp.exe 3.1.0.22).
//
// The machine body is two instructions, six bytes:
//
//     0x00b3d260  a1 d8 ea 67 01   MOV EAX, DS:0x0167ead8
//     0x00b3d265  c3               RET
//
// so the whole of the observable contract is: load one dword from one absolute
// address, return all four bytes of it in EAX, change nothing else, touch no
// stack and no register.
//
// LAYERING, because a two-instruction body has almost nothing to test and the
// danger is that the test ends up agreeing with itself:
//
//   1. kTargetBytes in the header is the IMAGE, transcribed: A1 D8 EA 67 01 C3.
//      The G cases assert those bytes against literals and DECODE the four
//      operand bytes into kGlobalVa, so the transcription itself is under test
//      and cannot drift silently. The reconstruction never reads it.
//   2. root_slot_accessor_00b3d260() in the .cpp is the code under test. The
//      behavioural cases drive it through its own declaration, so a defect in it
//      cannot be papered over by the transcription.
//   3. The ABI facts a value comparison cannot show are MEASURED through
//      hand-rolled indirect-call trampolines: the callee's stack effect is
//      measured across the call (cases E and F) and the answer is read out of
//      EAX after that same call, so the C++ return path is not what is being
//      checked.
//
// The cases are written to REFUTE a plausible wrong reconstruction rather than
// to walk a right one:
//
//   A  the returned word IS the modelled slot, for values chosen so a
//      truncating or sign-extending return cannot pass;
//   B  it is the SLOT and not a neighbour -- two reference readers prove the
//      harness can tell those addresses apart, so this cannot pass vacuously;
//   C  it tracks the slot's CURRENT contents: not a cached value, not a
//      constant, and not the slot's ADDRESS;
//   D  all 32 bits of EAX carry the word, measured through a trampoline;
//   E  the bare RET pops nothing, measured the same way, and CALIBRATED against
//      two control callees (one that pops 0 bytes, one that pops 4) so a shim
//      that reported the same number for everything would be caught;
//   F  guard band: every word of the modelled image except the slot keeps its
//      canary and the slot itself is unchanged, so the body writes nothing;
//   G  the machine facts the whole package rests on, including that the address
//      constant really is decoded from the body bytes and that this slot is not
//      one of the four slots the Simulator root closure already closed;
//   H  the CONSUMER SHAPE three caller listings share, modelled: the returned
//      word is an object base whose first dword is a function table, and the
//      table's +0x24 / +0x30 / +0x38 words are the ones the real callers
//      dispatch. This is the check that separates "returns the slot's contents"
//      from "returns the slot's address" using the machine's own idiom.
//
// Direction B is the MUTATION TEST: fourteen deliberately wrong bodies live in
// this file, are driven through the SAME battery the reconstruction is graded
// by, and each one is REQUIRED to be refuted. A battery with no power to reject
// a known-wrong body cannot certify the right one, so the mutants being refuted
// is itself an assertion: if a mutant survives, the run fails even though the
// reconstruction passed every other case.
//
// The battery was additionally checked from OUTSIDE, by perturbing the
// reconstruction's own body in the package's .cpp and rebuilding under the
// promotion gate. All eleven value/aliasing perturbations are detected by the
// run (neighbour read low, neighbour read high, +1 addend, low-byte truncation,
// high-half-only, first-read caching, slot cleared, high neighbour dirtied,
// returns the slot's address, returns a hardcoded constant, returns zero), and
// the two ABI perturbations -- gaining a stack parameter, and becoming a
// callee-cleaning body -- are caught at compile time by the prototype
// static_assert. The unperturbed build passes.

#if !defined(__i386__) && !defined(_M_IX86)
#error "root slot 0x00b3d260 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00b3d260_root_slot {
namespace model {

using Word = std::uint32_t;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::uint32_t pointer_word(const void* pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The battery is driven through one signature so no mutant is graded by a laxer
// checker than the reconstruction is: zero arguments in, one 32-bit word out.
using Probe = std::uint32_t (*)();

// The reconstruction behind that signature.
std::uint32_t real_entry() {
  return root_slot_accessor_00b3d260();
}

std::uint32_t entry_address_of(Probe probe) {
  return pointer_word(reinterpret_cast<const void*>(probe));
}

// ---------------------------------------------------------------------------
// Measured call channels.
// ---------------------------------------------------------------------------

// The OBSERVED call shape at 0x00b32ac4 and 0x00c8e600, and the padded variant
// used to grade the mutants. ONE trampoline drives both.
//
// Why it is hand-written asm and not an `__asm__` block inside a C++ function:
// three of the mutants end in `ret 4`, `ret 8` and `ret 12`, so they leave the
// caller's ESP displaced by a width only the callee chooses. A C++ function
// whose epilogue does `add $0x1c,%esp` + pops cannot survive that -- it comes
// back through four registers of garbage. This trampoline therefore owns its own
// stack: it records `before`, makes the call, pops exactly as many words as it
// pushed, records `after`, and RESTORES ESP before returning. Whatever the callee
// did to the stack, the caller is left exactly as it was, so a mis-cleaned
// mutant is observed rather than crashed on.
//
// Position independence is deliberate: the context is read from the argument
// slot (`4(%esp)`), so the trampoline contains no absolute reference and links
// the same way under PIE and non-PIE. Every access is through the pointer it is
// handed.
struct TrampolineCtx {
  std::uint32_t target;      // the callee to reach
  std::uint32_t push_words;  // 0 for the observed shape, 2 for the padded one
  std::uint32_t answer;      // EAX after the call
  std::uint32_t before;      // ESP before the pushes
  std::uint32_t after;       // ESP after the pops
};

extern "C" void run_trampoline(TrampolineCtx* ctx);

__asm__(
    "  .text\n"
    "  .globl run_trampoline\n"
    "  .hidden run_trampoline\n"
    "  .type run_trampoline, @function\n"
    "run_trampoline:\n"
    "  movl 4(%esp), %edx\n\t"        /* ctx */
    "  movl (%edx), %eax\n\t"         /* target */
    "  movl %esp, 12(%edx)\n\t"       /* before */
    "  cmpl $2, 4(%edx)\n\t"
    "  jne 1f\n\t"
    "  pushl $0\n\t"
    "  pushl $0\n\t"
    "1:\n"
    "  call *%eax\n\t"
    "  movl %eax, 8(%edx)\n\t"        /* answer */
    "  cmpl $2, 4(%edx)\n\t"
    "  jne 2f\n\t"
    "  addl $8, %esp\n\t"
    "2:\n"
    "  movl %esp, 16(%edx)\n\t"       /* after */
    "  movl 12(%edx), %eax\n\t"
    "  movl %eax, %esp\n\t"           /* restore, whatever the callee did */
    "  ret\n\t"
    "  .size run_trampoline, .-run_trampoline\n");

struct EspSamples {
  std::uint32_t answer;
  std::uint32_t before;
  std::uint32_t after;
};

// push_words == 0: the observed shape. Nothing is pushed, so `before` equals
// `after` exactly when the callee popped nothing.
EspSamples call_probe_no_push(Probe probe) {
  TrampolineCtx ctx;
  ctx.target = entry_address_of(probe);
  ctx.push_words = 0;
  ctx.answer = 0;
  ctx.before = 0;
  ctx.after = 0;
  run_trampoline(&ctx);
  EspSamples samples;
  samples.answer = ctx.answer;
  samples.before = ctx.before;
  samples.after = ctx.after;
  return samples;
}

// push_words == 2: the uniform channel that grades every probe. Two words are
// pushed and two are popped, so a callee that cleans its own stack consumes only
// part of the area and `after` comes back off `before` -- by +4 for a `ret 4`,
// +8 for a `ret 8` and +12 for a `ret 12`. The correct body, a bare RET, leaves
// the two equal.
EspSamples call_probe_padded(Probe probe) {
  TrampolineCtx ctx;
  ctx.target = entry_address_of(probe);
  ctx.push_words = 2;
  ctx.answer = 0;
  ctx.before = 0;
  ctx.after = 0;
  run_trampoline(&ctx);
  EspSamples samples;
  samples.answer = ctx.answer;
  samples.before = ctx.before;
  samples.after = ctx.after;
  return samples;
}

// ---------------------------------------------------------------------------
// The modelled image.
// ---------------------------------------------------------------------------

// The modelled slot is the very storage the reconstruction reads: g_root_slot_image
// is defined in the package's .cpp, so the battery cannot drift onto a private
// copy of the slot. The guard words are test scaffolding; they are NOT the
// neighbouring dwords of .data.
std::uint32_t& modelled_slot() { return g_root_slot_image.slot; }

// Reference readers for the two words adjacent to the slot. They exist so the
// "it read the slot, not its neighbour" case can fail: without them a harness
// that could not distinguish the addresses would report the same answer for all
// three and the assertion would hold for the wrong reason.
std::uint32_t reference_reads_low_neighbour() { return g_root_slot_image.guard_lo[kGuardWords - 1]; }
std::uint32_t reference_reads_high_neighbour() { return g_root_slot_image.guard_hi[0]; }

// Push every word of the modelled image to the canary, then set the slot.
void arm_image(std::uint32_t slot_value) {
  for (std::size_t i = 0; i < kGuardWords; ++i) {
    g_root_slot_image.guard_lo[i] = kGuardCanary;
    g_root_slot_image.guard_hi[i] = kGuardCanary;
  }
  modelled_slot() = slot_value;
}

// The whole image as one span, so a whole-image comparison is a memcmp and not
// a loop that can forget a word.
const std::uint32_t* image_words() { return &g_root_slot_image.guard_lo[0]; }
constexpr std::size_t kImageWords = 2 * kGuardWords + 1;

// ---------------------------------------------------------------------------
// The consumer shape, modelled from 0x00b32ac4 / 0x00c8e600 / 0x00c9a755 /
// 0x00d58c38 / 0x00abf793: `mov edx,[eax]` then `mov ecx,eax` then dispatch
// through [edx+0x30], [edx+0x38] and [edx+0x24].
// ---------------------------------------------------------------------------

// The synthetic table is a flat byte run, not a struct of named members: the
// machine gives displacements, not a layout, and a struct would smuggle a
// claim about slot order that nothing in the binary states. The three
// dispatched slots are therefore addressed by their displacement, exactly as
// `mov eax,[edx+0x30]` addresses them.
constexpr std::size_t kSyntheticTableBytes = 0x3cu;

struct SyntheticCarrier {
  std::uint32_t table;  // first word: a function-table pointer, per the callers
  std::uint32_t payload;
};

static_assert(offsetof(SyntheticCarrier, table) == 0,
              "the callers read the function table through the base itself, at "
              "displacement 0");

std::uint8_t g_table[kSyntheticTableBytes];
SyntheticCarrier g_carrier;

// A word of the synthetic table at a byte displacement, the way the caller loads
// it: no structure is asserted, only the displacement.
std::uint32_t table_word(std::size_t displacement) {
  check(displacement + sizeof(std::uint32_t) <= kSyntheticTableBytes);
  std::uint32_t value = 0;
  std::memcpy(&value, &g_table[displacement], sizeof(value));
  return value;
}

void set_table_word(std::size_t displacement, std::uint32_t value) {
  check(displacement + sizeof(std::uint32_t) <= kSyntheticTableBytes);
  std::memcpy(&g_table[displacement], &value, sizeof(value));
}

// One callable: any `std::uint32_t (*)()`. Both the reconstruction and every
// mutant go through this one signature.
// ---------------------------------------------------------------------------
// Mutants: bodies that are wrong in exactly one way each.
// ---------------------------------------------------------------------------

std::uint32_t g_mutant_cache;
bool g_mutant_cache_primed = false;

// Wrong: the word below the slot.
std::uint32_t mutant_low_neighbour() {
  return g_root_slot_image.guard_lo[kGuardWords - 1];
}

// Wrong: the word above the slot.
std::uint32_t mutant_high_neighbour() {
  return g_root_slot_image.guard_hi[0];
}

// Wrong: the slot's ADDRESS instead of its contents.
std::uint32_t mutant_slot_address() {
  return pointer_word(&modelled_slot());
}

// Wrong: a hardcoded address where the machine loads memory.
std::uint32_t mutant_constant_global_va() { return kGlobalVa; }

// Wrong: the first value ever read, cached across calls.
std::uint32_t mutant_cached_first_read() {
  if (!g_mutant_cache_primed) {
    g_mutant_cache = modelled_slot();
    g_mutant_cache_primed = true;
  }
  return g_mutant_cache;
}

// Wrong: the low byte widened instead of the whole word.
std::uint32_t mutant_truncates_to_byte() {
  return modelled_slot() & 0xffu;
}

// Wrong: the low byte SIGN-extended instead of the whole word loaded.
std::uint32_t mutant_sign_extends_low_byte() {
  const std::int32_t low_byte = static_cast<std::int32_t>(static_cast<int>(modelled_slot() & 0xffu));
  return static_cast<std::uint32_t>(low_byte);
}

// Wrong: only the high half survives.
std::uint32_t mutant_keeps_high_half() { return modelled_slot() & 0xffff0000u; }

// Wrong: the body writes the slot even though the machine only reads it.
std::uint32_t mutant_clears_slot() {
  const std::uint32_t previous = modelled_slot();
  modelled_slot() = 0;
  return previous;
}

// Wrong: the body mutates the slot before returning it.
std::uint32_t mutant_bumps_slot() {
  modelled_slot() = modelled_slot() + 1u;
  return modelled_slot();
}

// Wrong: the body reaches past the slot and dirties a neighbour.
std::uint32_t mutant_clobbers_high_neighbour() {
  g_root_slot_image.guard_hi[0] = 0xdeadbeefu;
  return modelled_slot();
}

// Wrong: the callee pops FOUR bytes. Spelled in asm rather than with a compiler
// convention attribute on purpose: a __stdcall one-argument body reached through
// a zero-argument shim corrupts the shim's own return address, so the defect
// under test would be the shim, not the callee. Driven instead by the padded
// channel, which pushes the one word this terminator consumes.
#if defined(_MSC_VER)
__declspec(naked) std::uint32_t mutant_pops_four_bytes() { __asm { ret 4 } }
#else
__attribute__((naked)) std::uint32_t mutant_pops_four_bytes() { __asm__("ret $4"); }
#endif

// Wrong: the callee pops EIGHT bytes, i.e. an over-wide cleanup.
#if defined(_MSC_VER)
__declspec(naked) std::uint32_t mutant_pops_eight_bytes() { __asm { ret 8 } }
#else
__attribute__((naked)) std::uint32_t mutant_pops_eight_bytes() { __asm__("ret $8"); }
#endif

// Wrong: the callee pops TWELVE bytes, an over-wide cleanup again, one word
// wider again so it cannot hide behind the two-word area the channel provides.
#if defined(_MSC_VER)
__declspec(naked) std::uint32_t mutant_pops_twelve_bytes() { __asm { ret 12 } }
#else
__attribute__((naked)) std::uint32_t mutant_pops_twelve_bytes() { __asm__("ret $12"); }
#endif

// Calibration callees for the stack-effect measurement: one that pops nothing
// and one that pops four. Without them, a shim that reported the same ESP
// difference for every callee would look correct, and the measurement below
// would be a constant.
std::uint32_t control_pops_nothing() { return 0x5a5a5a5au; }

#if defined(_MSC_VER)
__declspec(naked) std::uint32_t control_pops_four() { __asm { ret 4 } }
#else
__attribute__((naked)) std::uint32_t control_pops_four() { __asm__("ret $4"); }
#endif

struct Mutant {
  const char* name;
  std::uint32_t (*entry)();
};

const Mutant kMutants[] = {
    {"low_neighbour", &mutant_low_neighbour},
    {"high_neighbour", &mutant_high_neighbour},
    {"slot_address", &mutant_slot_address},
    {"constant_global_va", &mutant_constant_global_va},
    {"cached_first_read", &mutant_cached_first_read},
    {"truncates_to_byte", &mutant_truncates_to_byte},
    {"sign_extends_low_byte", &mutant_sign_extends_low_byte},
    {"keeps_high_half", &mutant_keeps_high_half},
    {"clears_slot", &mutant_clears_slot},
    {"bumps_slot", &mutant_bumps_slot},
    {"clobbers_high_neighbour", &mutant_clobbers_high_neighbour},
    {"callee_pops_four_bytes", &mutant_pops_four_bytes},
    {"callee_pops_eight_bytes", &mutant_pops_eight_bytes},
    {"callee_pops_twelve_bytes", &mutant_pops_twelve_bytes},
};
constexpr std::size_t kMutantCount = sizeof(kMutants) / sizeof(kMutants[0]);

}  // namespace model
}  // namespace openspore::reconstruction::pkg_00b3d260_root_slot

namespace {

using namespace openspore::reconstruction::pkg_00b3d260_root_slot;
using namespace openspore::reconstruction::pkg_00b3d260_root_slot::model;

// The machine ABI, asserted against the declaration: zero parameters, 4-byte
// return. This is the compile-time gate -- change the prototype and this stops
// building.
static_assert(std::is_same<decltype(&root_slot_accessor_00b3d260),
                           AbiRootSlotAccessor00b3d260>::value,
              "0x00b3d260 takes no parameter (no stack word in the body, no "
              "register read, bare RET) and returns the 4-byte word it loads");
static_assert(sizeof(AbiRootSlotAccessor00b3d260) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");
static_assert(sizeof(void*) == 4u,
              "the modelled entry is a 32-bit code pointer, so this is an "
              "x86-32 reconstruction");
static_assert(sizeof(Word) == 4u, "the modelled word is one 32-bit dword");
static_assert(kMutantCount == 14, "the battery has fourteen known-wrong bodies");

// The three slot offsets the real callers dispatch through, taken from
// 0x00abf793 (+0x24), 0x00b32ac4 (+0x30) and 0x00c8e600 / 0x00c9a755 /
// 0x00d58c38 (+0x38). They are modelled, NOT claimed as this function's fields:
// they are the caller's displacements through a table this body hands back.
constexpr std::size_t kConsumerSlotDisplacement00 = 0x00;
constexpr std::size_t kConsumerSlotDisplacement24 = 0x24;
constexpr std::size_t kConsumerSlotDisplacement30 = 0x30;
constexpr std::size_t kConsumerSlotDisplacement38 = 0x38;

// ---------------------------------------------------------------------------
// The battery.
// ---------------------------------------------------------------------------

// One scenario: the image is armed, the probe is called through the uniform
// padded channel, and four machine facts are checked.
//
//   * the answer is the slot's contents;
//   * the answer is the full 32-bit word (the answer value itself carries the
//     high bit in the chosen trials);
//   * ESP is unchanged, i.e. the callee popped nothing;
//   * no word of the image moved, i.e. the body stored nothing.
bool probe_agrees(model::Probe probe, std::uint32_t expected) {
  arm_image(expected);

  const std::uint32_t* const image_before = image_words();
  const EspSamples samples = call_probe_padded(probe);
  const std::uint32_t* const image_after = image_words();

  if (samples.answer != expected) {
    return false;
  }
  if (samples.before != samples.after) {
    return false;
  }
  if (image_before != image_after) {
    return false;
  }
  for (std::size_t i = 0; i < kImageWords; ++i) {
    const std::uint32_t expected_word = (i == kGuardWords) ? expected : kGuardCanary;
    if (image_after[i] != expected_word) {
      return false;
    }
  }
  return true;
}

// Values chosen so a truncating, sign-extending or half-word return cannot
// survive them.
const std::uint32_t kTrialValues[] = {
    0u, 1u, 2u, 0x7fffffffu, 0x80000000u, 0x80000001u,
    0xdeadbeefu, 0xffffffffu, 0x0000ffffu, 0xffff0000u, kGlobalVa,
};
constexpr std::size_t kTrialCount = sizeof(kTrialValues) / sizeof(kTrialValues[0]);

bool probe_agrees_on_every_trial(model::Probe probe) {
  for (std::size_t index = 0; index < kTrialCount; ++index) {
    if (!probe_agrees(probe, kTrialValues[index])) {
      return false;
    }
  }
  return true;
}

// ---------------------------------------------------------------------------
// Direction A: the reconstruction must satisfy the whole battery.
// ---------------------------------------------------------------------------

// A. The returned word IS the modelled slot, across every trial.
void test_returns_the_slot_word() {
  check(probe_agrees_on_every_trial(&real_entry));
}

// B. It is the slot and not a neighbour. The two reference readers are checked
//    to return exactly the neighbour words, which is what makes this capable of
//    failing: a body reading either guard word gives an answer this test can see
//    is wrong.
void test_reads_the_slot_and_not_a_neighbour() {
  arm_image(0x12345678u);
  g_root_slot_image.guard_lo[kGuardWords - 1] = 0xdead0001u;
  g_root_slot_image.guard_hi[0] = 0xdead0002u;

  check(reference_reads_low_neighbour() == 0xdead0001u);
  check(reference_reads_high_neighbour() == 0xdead0002u);

  const EspSamples samples = call_probe_no_push(&real_entry);
  check(samples.answer == 0x12345678u);
  check(samples.answer != 0xdead0001u);
  check(samples.answer != 0xdead0002u);
}

// C. The entry tracks the slot's CURRENT contents: not a cached word, not a
//    constant, and not the address of the slot.
void test_tracks_the_slot_not_a_cached_or_constant_value() {
  arm_image(0u);
  check(call_probe_no_push(&real_entry).answer == 0u);

  modelled_slot() = 0x0f0f0f0fu;
  check(call_probe_no_push(&real_entry).answer == 0x0f0f0f0fu);

  // Repeated calls with an unchanged slot are stable (no side effect).
  check(call_probe_no_push(&real_entry).answer == 0x0f0f0f0fu);
  check(call_probe_no_push(&real_entry).answer == 0x0f0f0f0fu);

  // The neighbour is really a different storage, so the two answers cannot
  // coincide by construction.
  check(reference_reads_low_neighbour() != 0x0f0f0f0fu);

  // The value is the slot's CONTENTS: the slot's own VA comes back as itself,
  // while the modelled image's address is a different word entirely.
  modelled_slot() = kGlobalVa;
  check(call_probe_no_push(&real_entry).answer == kGlobalVa);
  check(call_probe_no_push(&real_entry).answer !=
        pointer_word(&g_root_slot_image.slot));
}

// D. All 32 bits of EAX carry the word, measured through an indirect call in the
//    observed shape (nothing pushed) rather than through the C++ return path.
void test_whole_eax_carries_the_word() {
  arm_image(0x80000001u);
  EspSamples top_bit = call_probe_no_push(&real_entry);
  check(top_bit.answer == 0x80000001u);

  arm_image(0xdeadbeefu);
  EspSamples marker = call_probe_no_push(&real_entry);
  check(marker.answer == 0xdeadbeefu);
}

// E. The bare RET pops nothing, MEASURED, and the measurement is calibrated
//    first so it cannot be reporting a constant.
void test_callee_pops_nothing() {
  // Calibration: a callee that pops nothing and a callee that pops four must be
  // told apart by this same channel. If they are not, the measurement is
  // worthless and the case below is skipped rather than passed silently.
  const EspSamples nothing = call_probe_no_push(&control_pops_nothing);
  const EspSamples four = call_probe_no_push(&control_pops_four);
  check(nothing.before == nothing.after);
  check(nothing.before != 0u);
  // A `ret 4` terminator pops the return address and then adds 4 to ESP, so a
  // caller that pushed nothing sees its own ESP come back FOUR BYTES HIGH.
  check(four.before != four.after);
  check(four.before + 4u == four.after);

  arm_image(0x0a0b0c0du);
  const EspSamples samples = call_probe_no_push(&real_entry);
  check(samples.before == samples.after);
  check(samples.before != 0u);  // the sample is a real stack address
}

// F. Guard band. The body performs one READ; it performs no store. Every word of
//    the modelled image other than the slot must still hold the canary after the
//    call, and the slot must be byte-for-byte what it was.
void test_writes_nothing_outside_the_slot() {
  arm_image(0x5a5a1234u);
  const std::uint32_t slot_before = modelled_slot();

  check(call_probe_no_push(&real_entry).answer == 0x5a5a1234u);

  check(modelled_slot() == slot_before);
  for (std::size_t i = 0; i < kGuardWords; ++i) {
    check(g_root_slot_image.guard_lo[i] == kGuardCanary);
    check(g_root_slot_image.guard_hi[i] == kGuardCanary);
  }

  // The neighbours are set to non-canary sentinels as well, so the guard check
  // is not passing merely because the neighbours happened to be untouched
  // canaries.
  g_root_slot_image.guard_lo[kGuardWords - 1] = 0x11111111u;
  g_root_slot_image.guard_hi[0] = 0x22222222u;
  const std::uint32_t slot_value = modelled_slot();
  check(call_probe_no_push(&real_entry).answer == slot_value);
  check(g_root_slot_image.guard_lo[kGuardWords - 1] == 0x11111111u);
  check(g_root_slot_image.guard_hi[0] == 0x22222222u);
  check(modelled_slot() == slot_value);
}

// G. The machine facts the whole package rests on, re-checked at run time,
//    including that the address constant really is decoded from the body bytes.
void test_machine_facts() {
  check(kEntryVa == 0x00b3d260u);
  check(kTerminalVa == 0x00b3d265u);
  check(kBodyBytes == 6u);
  check(kInstructionCount == 2u);
  check(kMemoryStores == 0u);
  check(kReturnWidthBytes == 4u);
  check(kStackArgumentWords == 0u);
  check(kCalleeCleanupBytes == 0u);
  check(!kHasReceiver);

  check(kTargetBytes[0] == 0xa1u);
  check(kTargetBytes[1] == 0xd8u);
  check(kTargetBytes[2] == 0xeau);
  check(kTargetBytes[3] == 0x67u);
  check(kTargetBytes[4] == 0x01u);
  check(kTargetBytes[5] == 0xc3u);

  const Word decoded = static_cast<Word>(static_cast<std::uint32_t>(kTargetBytes[1]) |
                                         (static_cast<std::uint32_t>(kTargetBytes[2]) << 8) |
                                         (static_cast<std::uint32_t>(kTargetBytes[3]) << 16) |
                                         (static_cast<std::uint32_t>(kTargetBytes[4]) << 24));
  check(decoded == kGlobalVa);
  check(kGlobalVa == 0x0167ead8u);

  // The global lies in the loader-zeroed tail of .data: offset inside the
  // section past SizeOfRawData, so no image initializer is claimed for it.
  check(kDataSectionVa == 0x0150c000u);
  check(kDataSectionVirtualSize == 0x00212764u);
  check(kDataSectionRawSize == 0x000c4c00u);
  check(kGlobalOffsetInSection == 0x00172ad8u);
  check(kGlobalOffsetInSection > kDataSectionRawSize);

  // This slot is its own: not the alternate noun slot, the alternate star slot,
  // the unidentified forward slot or the input-manager slot.
  check(kGlobalVa != kAlternateNounSlotVa);
  check(kGlobalVa != kAlternateStarSlotVa);
  check(kGlobalVa != kOpaqueForwardSlotVa);
  check(kGlobalVa != kInputManagerSlotVa);
  check(kAlternateNounSlotVa == 0x0167eae0u);
  check(kAlternateStarSlotVa == 0x0167eae4u);
  check(kOpaqueForwardSlotVa == 0x0167eaecu);
  check(kInputManagerSlotVa == 0x0167eaf8u);

  // The modelled image has exactly one non-guard word, and the accessor's global
  // reference really is that word.
  static_assert(sizeof(RootSlotImage) == (2 * kGuardWords + 1) * sizeof(std::uint32_t),
                "the modelled image is 2*kGuardWords+1 words");
  check(&g_0167ead8 == &g_root_slot_image.slot);
  check(offsetof(RootSlotImage, slot) == kGuardWords * sizeof(std::uint32_t));
}

// H. The consumer shape three caller listings share, modelled. The returned
//    word must be the carrier's ADDRESS -- which is what `mov edx,[eax]` then
//    needs -- and the carrier's first word must be the table pointer, with the
//    three dispatched displacements landing on the three words that were put
//    there.
void test_returned_word_is_the_consumer_shape_base() {
  static_assert(offsetof(SyntheticCarrier, table) == 0,
                "the callers read the function table through the base itself, "
                "at displacement 0");
  static_assert(kSyntheticTableBytes > kConsumerSlotDisplacement38,
                "the largest dispatched displacement, +0x38, lies inside the "
                "synthetic table run");

  for (std::size_t i = 0; i < kSyntheticTableBytes; ++i) {
    g_table[i] = 0x00u;
  }
  set_table_word(kConsumerSlotDisplacement00, 0x11111111u);
  set_table_word(kConsumerSlotDisplacement24, 0xaaaa0024u);
  set_table_word(kConsumerSlotDisplacement30, 0xbbbb0030u);
  set_table_word(kConsumerSlotDisplacement38, 0xcccc0038u);
  g_carrier.table = pointer_word(&g_table[0]);
  g_carrier.payload = 0x22222222u;

  // The accessor hands back whatever word the slot holds; put the carrier's
  // address there, exactly as the caller then reads it.
  modelled_slot() = pointer_word(&g_carrier);
  const std::uint32_t base = call_probe_no_push(&real_entry).answer;
  check(base == pointer_word(&g_carrier));

  // `mov edx,[eax]` on the returned word yields the table pointer ...
  const std::uint32_t edx = [&base]() {
    std::uint32_t loaded = 0;
    std::memcpy(&loaded, reinterpret_cast<const void*>(static_cast<std::uintptr_t>(base)),
                sizeof(loaded));
    return loaded;
  }();
  check(edx == pointer_word(&g_table[0]));

  // ... `mov ecx,eax`: the same word is the receiver ...
  check(base == pointer_word(&g_carrier));

  // ... and the three dispatched displacements are three distinct words of the
  // table, none of them the base and none of them each other.
  check(table_word(kConsumerSlotDisplacement00) == 0x11111111u);
  check(table_word(kConsumerSlotDisplacement24) == 0xaaaa0024u);
  check(table_word(kConsumerSlotDisplacement30) == 0xbbbb0030u);
  check(table_word(kConsumerSlotDisplacement38) == 0xcccc0038u);
  check(edx != base);
  check(table_word(kConsumerSlotDisplacement24) != table_word(kConsumerSlotDisplacement30));
  check(table_word(kConsumerSlotDisplacement30) != table_word(kConsumerSlotDisplacement38));
}

// Direction B, the mutation test: every known-wrong body must be rejected. A
// mutant that survives means the battery has lost its power to tell a correct
// body from a wrong one, so the run fails even though the reconstruction itself
// passed every case above.
void test_every_mutant_is_refuted() {
  for (std::size_t index = 0; index < kMutantCount; ++index) {
    const model::Mutant& mutant = kMutants[index];
    g_mutant_cache = 0u;
    g_mutant_cache_primed = false;

    if (probe_agrees_on_every_trial(mutant.entry)) {
      std::fprintf(stderr, "0x00b3d260: mutant '%s' SURVIVED the battery\n",
                   mutant.name);
      check(false);
    }
  }
}

}  // namespace

int main() {
  test_returns_the_slot_word();
  test_reads_the_slot_and_not_a_neighbour();
  test_tracks_the_slot_not_a_cached_or_constant_value();
  test_whole_eax_carries_the_word();
  test_callee_pops_nothing();
  test_writes_nothing_outside_the_slot();
  test_machine_facts();
  test_returned_word_is_the_consumer_shape_base();
  test_every_mutant_is_refuted();
  return 0;
}
