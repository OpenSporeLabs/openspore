// PKG-SWARM-W1-010537B0 -- VA 0x010537b0
// Behavioural model test for FUN_010537b0 @ 0x010537b0.
//
// The one direct callee -- 0x00f47380 -- is defined here as an observer, so the test
// sees every transfer the reconstruction makes, with which argument, and gets to
// decide what the callee does to memory at the moment of the call.
//
// What is asserted is what the 12-instruction listing fixes, and nothing more:
//
//   * the two 4-byte stores, at the object's displacements 0x00 and 0x04, to the exact
//     immediates 0x013eb938 and 0x013ec458, IN THAT ORDER, on BOTH arms;
//   * that both stores complete BEFORE the conditional call, measured by the observer
//     reading the object while the call is in flight;
//   * that the body does not write the object again after the call returns, measured
//     by the observer scribbling over both words and the scribble surviving;
//   * that no byte of the object outside those eight bytes changes, checked by
//     comparing a buffer that carries guard bytes below the object and decoy words
//     above it;
//   * the one branch: bit 0 of the LOW BYTE of the entry stack word, with the other
//     three bytes of that word shown to be ignored;
//   * that the release receives the receiver itself, not a derivation of it;
//   * the return value (the receiver) and the saved-register/argument-cleanup pair,
//     both measured in a trampoline rather than asserted as conventions.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk it.
// Each names the wrong reconstruction it is aimed at:
//
//   A  the flag test is on bit 0 of the byte, and the branch polarity is JZ:
//   B  only the two words change: swapped constants, a displacement of 8, a byte-wide
//      store, an 8-byte store, or a store that also clobbers +0x08 is all caught
//   C  a null receiver is NOT safe: the body dereferences before the callee's own null
//      check can help, so the test never drives one and says so
//   D  the receiver may legitimately be a +0x04 sub-object (0x01053780 is
//      `sub ecx,4 / jmp 0x010537b0`), and the body must NOT re-apply that bias
//   E  bits 8..31 of the stack word are ignored: 0x00000100 does not release
//   F  the two immediates are the two the encoding carries, and they are not each
//      other and not the table head one slot away
//   G  the release argument is the receiver, not the +0x04 sub-object, not a pointer to
//      the word at +0x00, and not the value stored in the object
//   H  the ABI, measured: the callee popped its own argument word, ESI survives, ECX
//      carried the receiver, and EAX came back holding the receiver
//   I  the two store ORDER relative to the call, from both sides of the branch
//
// What is NOT asserted, and why:
//
//   * A null receiver. 0x010537b8 and 0x010537bf dereference the receiver with no
//     test of any kind, so `this == 0` faults at the first store and never reaches
//     0x00f47380 -- whose own null check is therefore unreachable from this caller.
//     Driving it would abort the test rather than refute anything, so the fact is
//     stated and not tested.
//   * Signed vs unsigned. There is no comparison in this body at all, only a TEST of
//     one bit, so there is no signedness for a reconstruction to get wrong. The test
//     does not pretend to exercise one.
//   * Argument order at the call. There is one argument, so there is no order to get
//     wrong; what IS checkable, and is checked, is WHICH pointer is handed over.
//   * What the two table heads point at. The body stores their addresses and never
//     dereferences either, so the test plants wild values in the object's two words
//     beforehand: a reconstruction that read through them would fault.
//   * Anything after the release returns other than EAX. The last three instructions
//     are `MOV EAX,ESI / POP ESI / RET 0x4` and there is nothing in them to vary.

#include "sw1_010537b0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_010537b0 {
namespace {

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// What the observer saw. `scramble_object` makes the callee overwrite both words with
// poison, so the caller can prove the two stores happened BEFORE the call and that
// nothing re-wrote them after it.
struct Observation {
  int release_calls = 0;
  const void* release_pointer = nullptr;
  bool release_sampled = false;
  Word word_at_zero_as_seen = 0;
  Word word_at_four_as_seen = 0;
  bool scramble_object = false;

  void reset() { *this = Observation(); }
};

Observation g_obs;

// Four guard bytes below the object and sixteen at and above it: 0x00..0x07 is the
// modelled receiver, 0x08..0x0f are trailing decoys, and the four bytes below are
// where a re-applied adjustor bias would land.
constexpr std::size_t kGuardBelow = 4;
constexpr std::size_t kObjectSize = 16;
constexpr std::size_t kFixtureSize = kGuardBelow + kObjectSize;
constexpr std::size_t kModelledSize = 8;
// What the observer leaves in the object's two words when `scramble_object` is set. A
// value the fixture never starts with, so "the body re-wrote it" and "the callee
// scribbled it" cannot be confused.
constexpr Word kObserverPoison = 0x5a5a1234u;

struct alignas(4) Fixture {
  unsigned char bytes[kFixtureSize];
};

void fill_word(unsigned char* base, std::size_t offset, Word value) {
  std::memcpy(base + offset, &value, sizeof value);
}

Word read_word(const unsigned char* base, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, base + offset, sizeof value);
  return value;
}

// A fixture with recognisable values everywhere: one guard word below the object, wild
// values in the two words the body overwrites (so "not written" is distinguishable from
// "written with something else", and so that a reconstruction which read through them
// would fault), and two decoy words above the modelled receiver.
Fixture make_fixture() {
  Fixture fixture;
  std::memset(fixture.bytes, 0, sizeof fixture.bytes);
  fill_word(fixture.bytes, 0, 0xdeadbeefu);                                  // guard, below
  fill_word(fixture.bytes, kGuardBelow + 0, 0xfeedfaceu);                   // object +0x00
  fill_word(fixture.bytes, kGuardBelow + 4, 0x0badf00du);                   // object +0x04
  fill_word(fixture.bytes, kGuardBelow + 8, 0x22222222u);                   // object +0x08
  fill_word(fixture.bytes, kGuardBelow + 12, 0x33333333u);                  // object +0x0c
  return fixture;
}

TableWordPair* object_of(Fixture& fixture) {
  return reinterpret_cast<TableWordPair*>(fixture.bytes + kGuardBelow);
}

struct ReceiverDiff {
  int inside = 0;
  int outside = 0;
};

ReceiverDiff diff_fixture(const Fixture& before, const Fixture& after) {
  ReceiverDiff diff;
  for (std::size_t index = 0; index < kFixtureSize; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    const std::size_t offset = index < kGuardBelow ? index : index - kGuardBelow;
    if (offset < kModelledSize) {
      ++diff.inside;
    } else {
      ++diff.outside;
    }
  }
  return diff;
}

}  // namespace

// 0x010537c8 -- the one direct transfer out of the body. cdecl, one dword argument,
// and the real callee null-checks it (0x00f47384 `TEST EAX,EAX` / 0x00f47386 `JE
// +0xc`), so the observer skips its work on a null argument for the same reason.
//
// It also does the one thing the machine cannot be asked to do and this test needs:
// it reads the object's two words AT THE MOMENT OF THE CALL. That is what makes the
// order of the two stores relative to the call observable, and `scramble_object`
// makes the reverse question observable too -- whether anything re-wrote them after
// the call returned.
extern "C" void PKG_SWARM_W1_010537B0_CDECL heap_release_00f47380(void* pointer) {
  ++g_obs.release_calls;
  g_obs.release_pointer = pointer;
  if (pointer == nullptr) {
    return;  // the callee's own null check, reproduced
  }
  const unsigned char* self = static_cast<const unsigned char*>(pointer);
  g_obs.release_sampled = true;
  g_obs.word_at_zero_as_seen = read_word(self, 0x0);
  g_obs.word_at_four_as_seen = read_word(self, 0x4);
  if (g_obs.scramble_object) {
    fill_word(static_cast<unsigned char*>(pointer), 0x0, kObserverPoison);
    fill_word(static_cast<unsigned char*>(pointer), 0x4, kObserverPoison);
  }
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_010537b0

namespace {

using namespace openspore::reconstruction::pkg_swarm_w1_010537b0;

// -- the cases the listing fixes, first ----------------------------------------

// A trampoline that pushes an arbitrary 4-byte stack word and calls the body through
// a register. It is the only way to present values wider than the body's declared
// `std::uint8_t` parameter, which is exactly what the "the other three bytes are
// ignored" case needs, and it is where ESP, EAX and ESI are sampled.
//
// It takes ONE out-pointer rather than four, and re-reads it after the call instead of
// holding it in a register: with four separate out-pointers the argument order is a
// thing the harness has to get right before it can measure anything, and getting it
// wrong silently writes the samples somewhere else instead of failing. The samples
// array is written by index, so its layout is stated here and not inferred.
//
// It is written as top-level assembly rather than as an inline-asm block on purpose.
// The inline form needs several register operands at once, and with the x86-32 PIE
// default reserving EBX plus a clobber list that has to name EAX, ECX and ESI, GCC
// reports "asm operand has impossible constraints or there are not enough registers"
// -- verified on this machine with g++ 16.2.1, for the block shape a previously
// accepted package in this repository uses. Every register used here is chosen here,
// so what the samples mean is stated by the code rather than negotiated by the
// register allocator.
extern "C" void sw1_trampoline_010537b0(std::uint32_t target, void* receiver,
                                        std::uint32_t argument_word, std::uint32_t* samples);

asm(".text\n"
    ".globl sw1_trampoline_010537b0\n"
    ".type sw1_trampoline_010537b0, @function\n"
    "sw1_trampoline_010537b0:\n"
    "  pushl %ebp\n"
    "  movl  %esp, %ebp\n"          /* ebp+0 is the saved ebp, ebp+4 the return address,
                                       so the FIRST argument is at ebp+8, not ebp+4 */
    "  movl  20(%ebp), %edx\n"      /* the samples array */
    "  movl  %esp, (%edx)\n"        /* [0] ESP, before the argument word exists */
    "  movl  8(%ebp), %eax\n"       /* the body under reconstruction */
    "  movl  12(%ebp), %ecx\n"      /* the receiver, into the thiscall register */
    "  movl  $0x5a5a5a5a, %esi\n"   /* canary in the callee-saved register it saves */
    "  pushl 16(%ebp)\n"            /* the one stack word, exactly four bytes */
    "  call  *%eax\n"               /* the callee pops it again (RET 0x4) */
    "  movl  20(%ebp), %edx\n"      /* re-read it: EDX is caller-saved */
    "  movl  %esp, 4(%edx)\n"       /* [1] ESP after: equal to [0] only on RET 0x4 */
    "  movl  %eax, 8(%edx)\n"       /* [2] the return register, sampled second */
    "  movl  %esi, 12(%edx)\n"      /* [3] the callee-saved register, sampled third */
    "  movl  %ebp, %esp\n"
    "  popl  %ebp\n"
    "  ret\n"
    ".size sw1_trampoline_010537b0, .-sw1_trampoline_010537b0\n");

struct Trampoline {
  std::uint32_t esp_before = 0;
  std::uint32_t esp_after = 0;
  std::uint32_t eax_after = 0;
  std::uint32_t esi_after = 0;
};
// The contract between the struct and the assembly above, stated where both are
// visible: the trampoline writes by INDEX into the array it is handed, so these four
// assertions are what make the sample names mean what they say. A layout change on
// either side stops the build instead of silently swapping two measurements.
static_assert(offsetof(Trampoline, esp_before) == 0, "samples[0] is ESP before the call");
static_assert(offsetof(Trampoline, esp_after) == 4, "samples[1] is ESP after the call");
static_assert(offsetof(Trampoline, eax_after) == 8, "samples[2] is EAX after the call");
static_assert(offsetof(Trampoline, esi_after) == 12, "samples[3] is ESI after the call");
static_assert(sizeof(Trampoline) == 16, "the trampoline writes four words, no more");

// Never inlined, and deliberately so: what this wrapper exists to measure is the
// stack around a real call, and an inlined copy lets the compiler fold the four
// argument pushes into whatever the surrounding case already has on its stack. With
// that, the second trampoline entry in a loop reads the previous call's canary out of
// the sample array as its receiver -- measured on this machine at -O2, where the
// wrapper was folded into the case and the object pointer's slot came back holding
// 0x5a5a5a5a. An out-of-line call is the form whose argument layout this file's
// assembly was written against, so it is the form that is used.
#if defined(_MSC_VER)
__declspec(noinline)
#else
__attribute__((noinline))
#endif
Trampoline call_with_word(TableWordPair* receiver, std::uint32_t argument_word) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&re_010537b0));
  Trampoline sample;
  sw1_trampoline_010537b0(target, receiver, argument_word, &sample.esp_before);
  return sample;
}

// A. The flag test is `TEST byte ptr [ESP+0x4],0x1` and the branch is JZ, so bit 0 of
// the low byte being SET runs the release and being CLEAR skips it. Both sides, and
// the boundary cases on either side of the bit.
void case_branch_polarity_and_bit() {
  struct Row {
    std::uint8_t flag;
    bool expect_release;
  };
  const Row rows[] = {
      {0x00u, false}, {0x01u, true},  {0x02u, false}, {0x03u, true},
      {0x7eu, false}, {0x7fu, true},  {0x80u, false}, {0x81u, true},
      {0xfcu, false}, {0xffu, true},
  };
  for (const Row& row : rows) {
    g_obs.reset();
    Fixture fixture = make_fixture();
    const TableWordPair* const result = re_010537b0(object_of(fixture), row.flag);
    const int wanted = row.expect_release ? 1 : 0;
    check(g_obs.release_calls == wanted,
          row.expect_release ? "A: bit 0 set, the release runs"
                             : "A: bit 0 clear, the release is skipped");
    check(result == object_of(fixture), "A: the body returns the receiver on both arms");
  }
}

// B. Only the two words at +0x00 and +0x04 change, and they change to the two
// immediates. The fixture carries four guard bytes below the object and three decoy
// words above it, so a swapped pair, a displacement of 8, a byte-wide store, an
// 8-byte store, a store at +0x08, or a write through the object as a POINTER instead
// of into it are all caught here.
void case_exactly_two_words_change() {
  g_obs.reset();
  Fixture fixture = make_fixture();
  Fixture before = fixture;
  re_010537b0(object_of(fixture), 0x01u);

  check(read_word(fixture.bytes + kGuardBelow, 0x0) == kTableHeadAtZero,
        "B1: the word at +0x00 is 0x013eb938");
  check(read_word(fixture.bytes + kGuardBelow, 0x4) == kTableHeadAtFour,
        "B2: the word at +0x04 is 0x013ec458");
  check(read_word(fixture.bytes + kGuardBelow, 0x0) != kTableHeadAtFour,
        "B3: the two words are not each other, so a swapped pair is refuted");
  check(read_word(fixture.bytes + kGuardBelow, 0x8) == 0x22222222u,
        "B4: the decoy word at +0x08 is untouched");
  check(read_word(fixture.bytes + kGuardBelow, 12) == 0x33333333u,
        "B5: the decoy word at +0x0c is untouched");
  check(read_word(fixture.bytes, 0) == 0xdeadbeefu,
        "B6: the guard word below the object is untouched: no downward bias");

  const ReceiverDiff diff = diff_fixture(before, fixture);
  check(diff.outside == 0,
        "B7: no byte outside the object's first eight changed, guards included");
  check(diff.inside == kModelledSize,
        "B8: all eight bytes of the first two words changed, so both stores are dword-wide");

  // The same, on the arm that does not release: the stores are unconditional, so the
  // object must reach exactly the same state.
  g_obs.reset();
  Fixture quiet = make_fixture();
  Fixture quiet_before = quiet;
  re_010537b0(object_of(quiet), 0x00u);
  check(read_word(quiet.bytes + kGuardBelow, 0x0) == kTableHeadAtZero &&
            read_word(quiet.bytes + kGuardBelow, 0x4) == kTableHeadAtFour,
        "B9: both stores run on the arm that does not release");
  const ReceiverDiff quiet_diff = diff_fixture(quiet_before, quiet);
  check(quiet_diff.outside == 0 && quiet_diff.inside == kModelledSize,
        "B10: and the object ends in the same state on that arm");
}

// C. The two words are POINTERS, and the body stores them without reading through
// them. The fixture above already plants 0xdeadbeef / 0xfeedface in them; a
// reconstruction that dereferenced either would fault on the first store, which is
// what makes this case worth stating rather than leaving implicit.
void case_stored_words_are_never_dereferenced() {
  g_obs.reset();
  Fixture fixture = make_fixture();
  check(read_word(fixture.bytes + kGuardBelow, 0x0) == 0xfeedfaceu &&
            read_word(fixture.bytes + kGuardBelow, 0x4) == 0x0badf00du,
        "C1: the fixture starts with wild values where the table heads go");
  re_010537b0(object_of(fixture), 0x01u);
  check(read_word(fixture.bytes + kGuardBelow, 0x0) == kTableHeadAtZero &&
            read_word(fixture.bytes + kGuardBelow, 0x4) == kTableHeadAtFour,
        "C2: both wild values were replaced by the immediates, with no fault: nothing "
        "was read through them");
}

// D. REFUTE: the receiver may be a +0x04 sub-object. 0x01053780 is
// `83 e9 04 sub ecx,0x4 / e9 28 00 00 00 jmp 0x010537b0`, an adjustor thunk that has
// already biased the receiver down to the object base, and this body must not bias it
// again. A model that re-applied the -4 would write the two words four bytes too low;
// the word at the object base is the decoy that catches it.
void case_subobject_receiver_is_not_rebiased() {
  g_obs.reset();
  Fixture fixture = make_fixture();
  TableWordPair* const subobject =
      reinterpret_cast<TableWordPair*>(fixture.bytes + kGuardBelow + 4);
  re_010537b0(subobject, 0x01u);

  check(read_word(fixture.bytes + kGuardBelow, 0x0) == 0xfeedfaceu,
        "D1: the object base was NOT written: the body does not re-apply the adjustor");
  check(read_word(fixture.bytes + kGuardBelow, 0x4) == kTableHeadAtZero,
        "D2: the first store landed at the pointer it was handed");
  check(read_word(fixture.bytes + kGuardBelow, 0x8) == kTableHeadAtFour,
        "D3: and the second store four bytes after it");
  check(g_obs.release_pointer == subobject,
        "D4: the release receives that same pointer, not the biased-down object base");
}

// E. REFUTE: only the low byte of the stack word is read. Bits 8..31 are ignored, so
// 0x00000100 does NOT release even though the word is non-zero, and 0x00000101 does.
// A model that tested the whole word for `!= 0`, or for bit 8, or for bit 0 of a
// sign-extended byte, is refuted in at least one of these rows.
void case_only_the_low_byte_participates() {
  struct Row {
    std::uint32_t word;
    bool expect_release;
  };
  const Row rows[] = {
      {0x00000000u, false}, {0x00000001u, true},  {0x00000100u, false},
      {0x00000101u, true},  {0x0000fe00u, false}, {0x0000ff01u, true},
      {0xfffffffeu, false}, {0xffffffffu, true},
  };
  for (const Row& row : rows) {
    g_obs.reset();
    Fixture fixture = make_fixture();
    call_with_word(object_of(fixture), row.word);
    const int wanted = row.expect_release ? 1 : 0;
    check(g_obs.release_calls == wanted,
          row.expect_release ? "E: bit 0 of the low byte set, the release runs"
                             : "E: bit 0 of the low byte clear, nothing runs");
  }
}

// F. REFUTE: the release is handed the receiver, not one of the several other things
// a reconstruction might reach for: not the +0x04 sub-object, not a pointer to the
// word at +0x00, not the table head that was just stored, and not a copy of it.
void case_release_argument_is_the_receiver() {
  g_obs.reset();
  Fixture fixture = make_fixture();
  TableWordPair* const object = object_of(fixture);
  re_010537b0(object, 0x01u);

  check(g_obs.release_pointer == static_cast<const void*>(object),
        "F1: the release receives the object pointer");
  check(g_obs.release_pointer != static_cast<const void*>(reinterpret_cast<unsigned char*>(object) + 4),
        "F2: not the +0x04 sub-object");
  check(g_obs.release_pointer !=
            static_cast<const void*>(reinterpret_cast<unsigned char*>(object) - 4),
        "F3: not a downward-biased object base");
  check(g_obs.release_pointer != reinterpret_cast<const void*>(kTableHeadAtZero) &&
            g_obs.release_pointer != reinterpret_cast<const void*>(kTableHeadAtFour),
        "F4: not the stored table head values");
  // F5 would be a duplicate and is not written: the address OF the word at +0x00 is the
  // object address itself, so comparing the release against it would just restate F1.
  // What a two-level mistake actually produces is the VALUE held in that word, which is
  // what F4 already rules out.
}

// G. REFUTE: write ORDER. The observer reads the object while the call is in flight,
// so a reconstruction that released before storing, or that only stored on the releasing
// arm, is refuted; and with `scramble_object` set, the callee overwrites both words and
// the test proves nothing re-wrote them afterwards.
void case_store_order_relative_to_the_call() {
  // Both stores precede the call, on the arm that calls.
  g_obs.reset();
  Fixture fixture = make_fixture();
  g_obs.scramble_object = false;
  re_010537b0(object_of(fixture), 0x01u);
  check(g_obs.release_sampled, "G1: the observer sampled the object during the call");
  check(g_obs.word_at_zero_as_seen == kTableHeadAtZero,
        "G2: the word at +0x00 already held 0x013eb938 when the call was made");
  check(g_obs.word_at_four_as_seen == kTableHeadAtFour,
        "G3: the word at +0x04 already held 0x013ec458 when the call was made");

  // Nothing re-writes them afterwards: the poison the callee left survives the return.
  g_obs.reset();
  Fixture poisoned = make_fixture();
  g_obs.scramble_object = true;
  re_010537b0(object_of(poisoned), 0x01u);
  check(read_word(poisoned.bytes + kGuardBelow, 0x0) == kObserverPoison &&
            read_word(poisoned.bytes + kGuardBelow, 0x4) == kObserverPoison,
        "G4: the callee's poison survives the return, so the body writes nothing after "
        "the call");
  check(g_obs.release_calls == 1, "G5: exactly one call in that case");
}

// H. REFUTE: the ABI, measured rather than asserted as a convention. ESP is sampled
// before the push and after the return (equal only when the callee popped its own
// argument word, `RET 0x4`), ESI is loaded with a canary and read back (equal only if
// the body restored it, `PUSH ESI` / `POP ESI`), and EAX is read at the instruction
// boundary after the call (the receiver, `MOV EAX,ESI`).
void case_abi_measured_in_a_trampoline() {
  g_obs.reset();
  Fixture fixture = make_fixture();
  const Trampoline sample = call_with_word(object_of(fixture), 0x00000003u);

  check(g_obs.release_calls == 1, "H1: the trampoline really reached the body");
  check(sample.esp_after == sample.esp_before,
        "H2: the callee popped its own 4-byte argument word (RET 0x4)");
  check(sample.esi_after == 0x5a5a5a5au,
        "H3: ESI arrived at the caller unchanged, so the body restored it");
  check(sample.eax_after == static_cast<std::uint32_t>(
                                reinterpret_cast<std::uintptr_t>(object_of(fixture))),
        "H4: EAX holds the receiver on return");
  check(g_obs.release_pointer == static_cast<const void*>(object_of(fixture)),
        "H5: ECX carried the receiver the trampoline was given, so the body's own copy "
        "of it is the same address");

  // The same trampoline with the flag clear: the return value is produced on that arm
  // too, by the branch target itself.
  g_obs.reset();
  Fixture quiet = make_fixture();
  const Trampoline quiet_sample = call_with_word(object_of(quiet), 0x00000002u);
  check(g_obs.release_calls == 0, "H6: the no-release arm made no call");
  check(quiet_sample.eax_after == static_cast<std::uint32_t>(
                                      reinterpret_cast<std::uintptr_t>(object_of(quiet))),
        "H7: and it still returned the receiver: MOV EAX,ESI is the branch target");
}

// I. Two calls, two objects, opposite flags: nothing carries over, and each object
// ends in the state its own call produced.
void case_calls_are_independent() {
  g_obs.reset();
  Fixture first = make_fixture();
  Fixture second = make_fixture();
  re_010537b0(object_of(first), 0x01u);
  const int after_first = g_obs.release_calls;
  re_010537b0(object_of(second), 0x00u);
  const int after_second = g_obs.release_calls;

  check(after_first == 1 && after_second == 1, "I1: one call in the first, none in the second");
  check(g_obs.release_pointer == static_cast<const void*>(object_of(first)),
        "I2: the single call named the FIRST object, so the second call did not retarget it");
  check(read_word(first.bytes + kGuardBelow, 0x0) == kTableHeadAtZero &&
            read_word(second.bytes + kGuardBelow, 0x0) == kTableHeadAtZero,
        "I3: both objects carry the two immediates, whichever arm wrote them");
}

// J. The two immediates the body stores, and the two receiver displacements, against
// the values this package states and the encodings they come from.
void verify_constants() {
  check(kReceiverWordAtZero == 0x0u, "J1: the first store is at the object's +0x00");
  check(kReceiverWordAtFour == 0x4u, "J2: the second store is at the object's +0x04");
  check(kTableHeadAtZero == 0x013eb938u, "J3: 0x010537bf carries 0x013eb938");
  check(kTableHeadAtFour == 0x013ec458u, "J4: 0x010537b8 carries 0x013ec458");
  check(kTableHeadAtZero != kTableHeadAtFour, "J5: the two immediates differ");
  check(sizeof(TableWordPair) == 8,
        "J6: the modelled receiver ends after the second word, which is the last byte "
        "the body writes");
  check(kReceiverWordAtFour + 4 == sizeof(TableWordPair),
        "J7: +0x04 plus a dword is the end of the modelled receiver");
}

}  // namespace

int main() {
  verify_constants();
  case_branch_polarity_and_bit();
  case_exactly_two_words_change();
  case_stored_words_are_never_dereferenced();
  case_subobject_receiver_is_not_rebiased();
  case_only_the_low_byte_participates();
  case_release_argument_is_the_receiver();
  case_store_order_relative_to_the_call();
  case_abi_measured_in_a_trampoline();
  case_calls_are_independent();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
