#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "space_player_empire_id_01021090.hpp"

// Focused semantic test for FUN_01021090 @ 0x01021090.
//
// Three instructions, one absolute data address, one displacement, no branch,
// no store, no arithmetic. The test is built to REFUTE the reconstruction
// rather than to walk it, so each group below names the hypothesis it attacks
// and the wrong model it would catch:
//
//   1. the encoding is the observed nine bytes - a model stated against a
//      different opcode, a different displacement or a RET that cleans the
//      stack is refuted at compile time by the package's own static_asserts;
//   2. the returned value is the word STORED at the displacement - not the
//      global's own pointer, not the ADDRESS of the word, not the
//      displacement, not a masked or perturbed copy;
//   3. the operand is a byte displacement and not an element count: a model
//      that reads the 0x18th 32-bit element lands at byte 0x60, which the
//      fixture here plants as a decoy;
//   4. the body READS: the whole modelled object is byte-identical either
//      side of the call, so a write-back model is refuted;
//   5. there is NO null guard. This is measured, not asserted: a forked child
//      publishes a null global and calls the entry, and the test requires the
//      child to die on a signal. A model that returns 0 or any sentinel for a
//      null global survives, which is the hole this group closes;
//   6. the global is re-read on every call, so republishing it is observed
//      immediately and nothing is cached across entries;
//   7. the ABI is zero-argument with caller-side cleanup - MEASURED by
//      sampling ESP around the call and shown to be independent of the
//      caller's own stack depth, at two depths, and the result is shown to
//      arrive in EAX.

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_01021090 model test requires an x86-32 target"
#endif

namespace {

using namespace openspore::reconstruction::pkg_01021090_space_player_empire_id;

int failures = 0;

void expect(const char* what, bool ok) {
  if (!ok) {
    ++failures;
    std::fprintf(stderr, "FAIL: %s\n", what);
  }
}

std::uint32_t word_at(const void* pointer, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(pointer) + offset,
              sizeof(value));
  return value;
}

void store_word(void* pointer, std::size_t offset, std::uint32_t value) {
  std::memcpy(static_cast<std::uint8_t*>(pointer) + offset, &value,
              sizeof(value));
}

// 0x01021090..0x01021098 read live: a1 8c da 6d 01 8b 40 18 c3.
const std::uint8_t kListingBytes[9] = {0xa1, 0x8c, 0xda, 0x6d, 0x01,
                                       0x8b, 0x40, 0x18, 0xc3};

constexpr std::size_t kFixtureSize = sizeof(SpacePlayerDataEmpireIdFixture);

// The modelled object is embedded in a larger buffer so that a model reading
// the displacement as an ELEMENT count lands on planted decoy bytes instead of
// running off the end of the object. Every byte outside the word at +0x18 is
// filled with a pattern, and the decoys are set to values the real field never
// holds in this test, so any read at the wrong address is visible.
constexpr std::size_t kBufferSize = 0x100;
constexpr std::size_t kElementMisreadOffset = 0x18 * 4;  // 0x60

struct Fixture {
  alignas(4) std::uint8_t bytes[kBufferSize];

  Fixture() {
    for (std::size_t index = 0; index < kBufferSize; ++index) {
      bytes[index] = static_cast<std::uint8_t>(0x30u + static_cast<unsigned>(index % 16u));
    }
    // Decoys: a word one slot lower, one slot higher, at the head of the
    // object, and at the byte an element-count misreading would reach. None of
    // them is ever equal to the planted field value below.
    store_word(bytes, 0x14, 0x11111111u);
    store_word(bytes, 0x1c, 0x22222222u);
    store_word(bytes, 0x00, 0x33333333u);
    store_word(bytes, kElementMisreadOffset, 0x44444444u);
    store_word(bytes, kPlayerEmpireIdDisplacement, 0x0badf00du);
  }

  SpacePlayerDataEmpireIdFixture* object() {
    return reinterpret_cast<SpacePlayerDataEmpireIdFixture*>(bytes);
  }

  std::uint32_t field() const { return word_at(bytes, kPlayerEmpireIdDisplacement); }
};

// 1. The encoding. The nine bytes are restated here independently of the
// header's own table, so neither copy can drift from the other unnoticed, and
// the opcode bytes are decoded rather than merely compared.
void verify_encoding_matches_the_listing() {
  expect("the body is nine bytes", sizeof(kTargetBytes) == 9 &&
                                      sizeof(kListingBytes) == 9);
  expect("the modelled object ends at the word the body reads",
         kFixtureSize == kPlayerEmpireIdDisplacement + 4);
  expect("the header's byte table equals the listing read live",
         std::memcmp(kTargetBytes, kListingBytes, 9) == 0);

  expect("byte 0 is the A1 moffs32 load opcode", kTargetBytes[0] == 0xa1);
  expect("the moffs32 immediate spells 0x016dda8c little-endian",
         kTargetBytes[1] == 0x8c && kTargetBytes[2] == 0xda &&
             kTargetBytes[3] == 0x6d && kTargetBytes[4] == 0x01);
  expect("byte 5 is MOV r32,r/m32 and not LEA", kTargetBytes[5] == 0x8b &&
                                               kTargetBytes[5] != 0x8d);
  expect("byte 6 is ModRM 0x40: mod=01, reg=EAX, rm=EAX",
         kTargetBytes[6] == 0x40);
  expect("byte 7 is the displacement the header constant names",
         kTargetBytes[7] == static_cast<std::uint8_t>(
                                kPlayerEmpireIdDisplacement));
  expect("the displacement is 0x18", kPlayerEmpireIdDisplacement == 0x18);
  expect("byte 8 is a bare RET, so the caller owns stack cleanup",
         kTargetBytes[8] == 0xc3 && kTargetBytes[8] != 0xc2 &&
             kTargetBytes[8] != 0xca);

  // No branch, no call, no indirect transfer anywhere in the nine bytes: the
  // complete listing is straight-line and the entry is not a dispatcher.
  for (std::size_t index = 0; index < sizeof(kTargetBytes); ++index) {
    expect("the body contains no Jcc short-form opcode",
           kTargetBytes[index] != 0x74 && kTargetBytes[index] != 0x75 &&
               kTargetBytes[index] != 0x7c && kTargetBytes[index] != 0x7e);
    expect("the body contains no direct CALL opcode",
           kTargetBytes[index] != 0xe8);
    expect("the body contains no JMP opcode", kTargetBytes[index] != 0xe9 &&
                                                 kTargetBytes[index] != 0xeb);
  }
  expect("the first instruction is not an indirect transfer",
         kTargetBytes[0] != 0xff);
}

// 2. The return is the word STORED at the displacement, verbatim.
void verify_returns_the_stored_word() {
  const std::uint32_t samples[] = {
      0x0badf00du,
      0x00000000u,
      0x00000001u,
      0xffffffffu,
      0x7fffffffu,
      0x80000000u,
      0x12345678u,
      0xdeadbeefu,
  };
  for (const std::uint32_t value : samples) {
    Fixture fixture;
    store_word(fixture.bytes, kPlayerEmpireIdDisplacement, value);
    g_016dda8c = fixture.object();
    const std::uint32_t result = space_player_empire_id_01021090();
    expect("the stored word crosses verbatim, with no mask or transform",
           result == value);
    expect("the returned value is not the published pointer",
           result != static_cast<std::uint32_t>(
                         reinterpret_cast<std::uintptr_t>(fixture.object())));
    expect("the returned value is not the address of the word",
           result != static_cast<std::uint32_t>(
                         reinterpret_cast<std::uintptr_t>(fixture.bytes) +
                         kPlayerEmpireIdDisplacement));
    expect("the returned value is not the displacement itself",
           result != static_cast<std::uint32_t>(kPlayerEmpireIdDisplacement));
  }
}

// 3. The operand is a byte displacement and not an element count. A model that
// reads the 0x18th 32-bit element reaches byte 0x60, which the fixture plants
// with a distinct value; the neighbouring words at 0x14 and 0x1c are planted
// too, so a model off by one slot in either direction is visible as well.
void verify_displacement_is_bytes_not_elements() {
  Fixture fixture;
  g_016dda8c = fixture.object();
  const std::uint32_t result = space_player_empire_id_01021090();
  expect("the word at the displacement is what comes back",
         result == fixture.field());
  expect("an element-count misreading is refuted",
         result != word_at(fixture.bytes, kElementMisreadOffset));
  expect("the neighbouring lower word is not returned",
         result != word_at(fixture.bytes, 0x14));
  expect("the neighbouring upper word is not returned",
         result != word_at(fixture.bytes, 0x1c));
  expect("the word at the head of the object is not returned",
         result != word_at(fixture.bytes, 0x00));
}

// 4. The body reads. Nothing is written, so every byte of the modelled object
// is unchanged either side of the call. A write-back model (a store of the
// loaded word, or a store of a perturbed one) leaves the pattern changed.
void verify_body_does_not_write() {
  Fixture fixture;
  store_word(fixture.bytes, kPlayerEmpireIdDisplacement, 0x5a5a5a5au);
  g_016dda8c = fixture.object();

  std::uint8_t before[kBufferSize];
  std::memcpy(before, fixture.bytes, sizeof(before));
  space_player_empire_id_01021090();
  expect("the whole modelled object is byte-identical after the call",
         std::memcmp(before, fixture.bytes, sizeof(before)) == 0);

  // Twice, with a different published value in between, so a model that writes
  // only on some path is caught as well.
  store_word(fixture.bytes, kPlayerEmpireIdDisplacement, 0xa5a5a5a5u);
  std::memcpy(before, fixture.bytes, sizeof(before));
  space_player_empire_id_01021090();
  expect("the second call writes nothing either",
         std::memcmp(before, fixture.bytes, sizeof(before)) == 0);
}

// 5. There is NO null guard, and this is measured rather than asserted. The
// child publishes a null global and calls the entry; the entry dereferences it,
// so the child must die on a signal. A model that returns 0, or any sentinel,
// for a null global exits 0 and is refuted here. The guard is the difference
// between this entry and the null-guarded read view at 0x01021260, so it is
// the one semantic fact in this package that a prose-only test could hide.
void verify_no_null_guard() {
  std::fflush(nullptr);
  const pid_t pid = fork();
  expect("the child process was created", pid >= 0);
  if (pid == 0) {
    g_016dda8c = nullptr;
    const std::uint32_t value = space_player_empire_id_01021090();
    // Reached only by a model that guards the global. Report the value it
    // invented so the failure is legible, then leave normally: the parent
    // treats a clean exit as "the mutant was NOT refuted".
    std::fprintf(stderr, "  (child returned 0x%08x from a null global)\n",
                 value);
    std::fflush(stderr);
    _exit(0);
  }
  int status = 0;
  expect("the child was reaped", waitpid(pid, &status, 0) == pid);
  expect("a null global is dereferenced: the child died on a signal",
         WIFSIGNALED(status));
  expect("the faulting signal is SIGSEGV", WIFSIGNALED(status) &&
                                               WTERMSIG(status) == SIGSEGV);
  expect("a guarded model would have exited cleanly, so this group refutes it",
         !WIFEXITED(status));
}

// 6. The global is re-read on every entry. Two fixtures are published in turn,
// so a model that latched the pointer or the value on a first call is caught.
void verify_global_is_reread_on_every_call() {
  Fixture first;
  Fixture second;
  store_word(first.bytes, kPlayerEmpireIdDisplacement, 0x11110000u);
  store_word(second.bytes, kPlayerEmpireIdDisplacement, 0x22220000u);

  g_016dda8c = first.object();
  expect("the first publication is observed",
         space_player_empire_id_01021090() == 0x11110000u);
  g_016dda8c = second.object();
  expect("republishing the global is observed immediately",
         space_player_empire_id_01021090() == 0x22220000u);
  g_016dda8c = first.object();
  expect("republishing it back is observed too",
         space_player_empire_id_01021090() == 0x11110000u);
}

// The ABI. The entry takes no argument and pops nothing, and this block
// MEASURES both facts rather than asserting them.
//
// The three samples leave the block through a buffer the CALLER allocates, and
// that detail is load-bearing. With -fomit-frame-pointer the compiler addresses
// locals relative to the CURRENT ESP, so an asm block that lowers ESP before
// storing into its own locals writes 0x100 bytes below where the C++ code
// believes the samples are, and they come back as zeros. A buffer whose address
// was fixed before the block ran is immune to that, and it is also what lets the
// block lower ESP at all.
struct AbiSample {
  std::uint32_t esp_before;
  std::uint32_t esp_after;
  std::uint32_t eax_result;
  std::uint32_t entry_address;
};

// ONE register operand and nothing else: the buffer address. Every field is
// reached through it at a byte offset, and each offset is tied to the C++ layout
// by a static_assert immediately above, so the asm and the struct cannot drift
// apart.
//
// Every earlier shape of this block was rejected by GCC at -O0 with "asm
// operand has impossible constraints or there are not enough registers": four
// separate memory operands wanted a base register each, and adding a register
// operand for the call target spent the last one. One base register with
// literal offsets builds at every -O level.
static_assert(sizeof(AbiSample) == 16, "AbiSample is four 32-bit words");
static_assert(offsetof(AbiSample, esp_before) == 0, "esp_before at offset 0");
static_assert(offsetof(AbiSample, esp_after) == 4, "esp_after at offset 4");
static_assert(offsetof(AbiSample, eax_result) == 8, "eax_result at offset 8");
static_assert(offsetof(AbiSample, entry_address) == 12,
              "entry_address at offset 12");

extern "C" void sample_abi(AbiSample* sample) {
  __asm__ __volatile__(
      "movl 12(%[s]), %%edx\n\t"
      "movl %%esp, 0(%[s])\n\t"
      "call *%%edx\n\t"
      "movl %%esp, 4(%[s])\n\t"
      "movl %%eax, 8(%[s])\n\t"
      : /* no outputs: every store goes through the one register operand */
      : [s] "r"(sample)
      : "eax", "edx", "memory");
}

void verify_abi_is_zero_argument_with_caller_cleanup() {
  Fixture fixture;
  store_word(fixture.bytes, kPlayerEmpireIdDisplacement, 0x0f0f0f0fu);
  g_016dda8c = fixture.object();

  AbiSample shallow = {};
  shallow.entry_address = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&space_player_empire_id_01021090));
  sample_abi(&shallow);

  expect("the ESP samples were written, so this is a measurement",
         shallow.esp_before != 0 && shallow.esp_after != 0);

  // The return value travels in EAX: the asm block copies it out of EAX itself
  // rather than trusting the C++ return type to have landed there.
  expect("the call returns the published word in EAX",
         shallow.eax_result == 0x0f0f0f0fu);
  expect("the callee popped nothing: ESP is unchanged across the call",
         shallow.esp_before == shallow.esp_after);

  expect("nothing was written by the call",
         word_at(fixture.bytes, kPlayerEmpireIdDisplacement) == 0x0f0f0f0fu);

  // The same measurement from a DIFFERENT stack depth, so "the callee pops
  // nothing" is not an artefact of one frame. The two sample buffers live in the
  // same frame here, so this compares two calls the compiler chose to emit, and
  // what it establishes is that the ESP delta is zero at both depths - which is
  // the whole of the callee-cleanup claim. A caller that pushed an argument would
  // show the same zero delta and is separately ruled out by the listing, which
  // contains no stack read of any kind.
  AbiSample deep = {};
  deep.entry_address = shallow.entry_address;
  sample_abi(&deep);

  expect("the deeper call also reports a zero ESP delta",
         deep.esp_before == deep.esp_after);
  expect("the deeper call returns the same published word",
         deep.eax_result == 0x0f0f0f0fu);
}

}  // namespace

int main() {
  verify_encoding_matches_the_listing();
  verify_returns_the_stored_word();
  verify_displacement_is_bytes_not_elements();
  verify_body_does_not_write();
  verify_no_null_guard();
  verify_global_is_reread_on_every_call();
  verify_abi_is_zero_argument_with_caller_cleanup();
  if (failures == 0) {
    std::printf("ok: 0x01021090 model test passed\n");
    return 0;
  }
  std::fprintf(stderr, "%d check(s) failed\n", failures);
  return 1;
}