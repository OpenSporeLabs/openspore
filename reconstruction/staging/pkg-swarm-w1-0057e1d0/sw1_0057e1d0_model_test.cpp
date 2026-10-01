// PKG-SWARM-W1-0057E1D0 -- VA 0x0057e1d0
// Behavioural model test for FUN_0057e1d0 @ 0x0057e1d0.
//
// The one direct callee -- 0x00f47380 -- is defined here as an observer, so the
// test sees every transfer the reconstruction makes, with which argument, in
// which order, and can sample the receiver's bytes at the moment of each call. A
// second helper, the adjusting thunk at 0x0057a700, is modelled as a plain
// function so that the only caller edge this target actually has can be driven.
//
// What is asserted is what the 23-instruction listing fixes and nothing more:
//
//   * the two transfers, once each, and their order (the +0x0c word, then the
//     receiver);
//   * the four receiver displacements (0x00 and 0x04 written, 0x0c and 0x14 read)
//     and, by byte-comparing the receiver before and after, that NO other byte of
//     it changes -- including an 8-byte sentinel tail past the object;
//   * the two stored constants, in the right two slots: 0x013eb938 at +0x00 and
//     0x013ef094 at +0x04;
//   * the WRITE ORDERING: both stores are already in memory when the release of
//     the receiver runs, sampled from inside the observer;
//   * the span test, including that its compare is SIGNED (opcode 0x7E) and that
//     the mask rounds DOWN to even;
//   * the null-word guard at 0x0057e1e3, driven with a wide span so a
//     reconstruction that dropped it would release a null word;
//   * the flag test: bit 0 only, and on a byte;
//   * the return value being the receiver, on BOTH arms;
//   * the adjusting thunk's arithmetic: entered with pointer P, the two stores
//     land at P-4 and P, never at P and P+4.
//
// The cases exist to try to BREAK the reconstruction, not to walk it. Each names
// a wrong reconstruction it is aimed at:
//
//   A  all three conditions true: two releases, in order, on the right
//      arguments, and the receiver returned on both arms;
//   B  WRITE ORDERING and target identity: the release observer samples the
//      receiver and must already see 0x013eb938 at +0x00 and 0x013ef094 at
//      +0x04. A model that stored them after the release is killed here;
//   C  SIGNED vs UNSIGNED compare at 0x0057e1de -- four inputs on which the two
//      readings disagree. This is the fact the whole body turns on;
//   D  the mask is present: differences of 1 and 3 must NOT release, because
//      `AND ECX,0xfffffffe` turns them into 0 and 2. A model that dropped the
//      AND releases on both;
//   E  the null guard at 0x0057e1e3 with an over-threshold span, so only the
//      guard can stop the release;
//   F  FLAG POLARITY and BIT WIDTH: 0x00, 0x02, 0x80 and 0xfe must not release
//      the receiver, 0x01, 0x03 and 0xff must. A model testing bit 1, or testing
//      the byte for non-zero, is killed here;
//   G  POINTER LEVEL: the argument is the WORD READ at the receiver's +0x0c, not
//      the address of that word, not the receiver, not the receiver+0x0c, and not
//      the neighbouring words at +0x08 or +0x10 -- decoys for all of which the
//      test plants real pointers;
//   H  WRONG RECEIVER OFFSET: decoy dwords at +0x08 and +0x10 are never written
//      and the byte diff over the whole object plus its sentinel tail is empty
//      outside 0x00..0x07;
//   I  THE ADJUSTING THUNK: entered with P, the stores land at P-4 and P. A model
//      that believed its `this` WAS the caller's pointer would read its run pair
//      from P+0x0c and P+0x14 -- both planted with decoys -- and write its stores
//      at P and P+4, also planted. All four are caught.
//
// What is NOT asserted, and why:
//
//   * The calling conventions themselves. GCC's x86-32 port ACCEPTS but IGNORES
//     `cdecl` and `thiscall` as function attributes, so a model test built with it
//     cannot measure either. Both are read off the original image's bytes
//     (0x0057e210 `C2 04 00`, 0x00f47394 `C3`) and the fact is recorded in the
//     package header and the sidecar rather than asserted here.
//   * Whether the byte at entry+4 is read as a byte or as a dword. From the
//     caller's side a `std::uint8_t` parameter and a masked dword parameter are
//     indistinguishable; what IS asserted is the observable consequence, that only
//     bit 0 of that byte reaches the branch (case F).
//   * The RELATIVE order of the two stores. No instruction observes memory
//     between 0x0057e1f5 and 0x0057e1fc, and the test adds no instrumentation
//     there, so a model writing +0x04 first and a model writing +0x00 first are
//     indistinguishable. The reconstruction reproduces the listing's order; the
//     test does not pretend to check it.
//   * What the two stored constants MEAN. That 0x013eb938 and 0x013ef094 are
//     dispatch-table addresses is a package-header claim about the constants. The
//     test checks the two values and their two slots and nothing about them.
//   * What the pair of words at +0x0c and +0x14 measures. The test never divides
//     the difference and never converts it to a count, because no instruction in
//     the body does.
//   * That 0x00f47380 releases heap memory. The observer records and does nothing,
//     so a model passing some other pointer is caught, but nothing here tests what
//     the callee does with the pointer -- that identification is INFERRED from its
//     own seven instructions and from its use on both a sub-buffer and the object.
//
// Heap blocks handed to the observer are real malloc'd blocks and are freed by
// the test, so a run leaks nothing. Where a case needs a fixed address to drive
// the wraparound inputs of case C it uses a fabricated value, which is safe
// because the observer never dereferences what it is given.

#include "sw1_0057e1d0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_0057e1d0 {
namespace {

// Machine displacements, restated here as this file's own literals so the test
// does not take the reconstruction's header constants on trust.
//   0x00 and 0x04  the two words the body WRITES
//   0x0c and 0x14  the two words the body READS
//   0x08 and 0x10  the neighbouring decoys it must never touch
constexpr std::size_t kZero = 0x00u;
constexpr std::size_t kFour = 0x04u;
constexpr std::size_t kRunBegin = 0x0cu;
constexpr std::size_t kRunEnd = 0x14u;
constexpr std::size_t kDecoyBelow = 0x08u;
constexpr std::size_t kDecoyAbove = 0x10u;
constexpr std::size_t kReceiverSize = 24u;
constexpr std::size_t kSentinel = 8u;

// The two stored constants, restated independently of the reconstruction.
constexpr Word kStoredAtZero = 0x013eb938u;
constexpr Word kStoredAtFour = 0x013ef094u;

// The decoy words, all distinct from each other and from the run pair, so a
// pointer identity check can tell which one the body used.
constexpr Word kDecoyWordBelow = 0x00a0a0a0u;
constexpr Word kDecoyWordAbove = 0x00b0b0b0u;
constexpr Word kDecoyWordFour = 0x00c0c0c0u;
constexpr Word kDecoyWordLow = 0x00e0e0e0u;
constexpr Word kDecoyWordHigh = 0x00f0f0f0u;
constexpr Word kDecoyWordCallerPlusFour = 0x00ddddddu;

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// A receiver big enough for the 24 bytes the body reaches, plus a sentinel tail
// so an overrun past 0x17 would show up in the byte comparison.
struct Receiver {
  unsigned char bytes[kReceiverSize + kSentinel];
};

Word read_word(const void* base, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, static_cast<const unsigned char*>(base) + displacement,
              sizeof value);
  return value;
}

void write_word(void* base, std::size_t displacement, Word value) {
  std::memcpy(static_cast<unsigned char*>(base) + displacement, &value, sizeof value);
}

void* block(std::size_t size, unsigned char fill) {
  void* memory = std::malloc(size);
  if (memory != nullptr) {
    std::memset(memory, fill, size);
  }
  return memory;
}

// The receiver the current case is exercising, so the observer can sample it at a
// moment the caller cannot see.
Receiver* g_active = nullptr;

struct Observation {
  int log[4] = {};
  int log_length = 0;
  int release_calls = 0;
  void* release_arg[4] = {};
  // Sampled INSIDE each release, so the position of the two stores in the sequence
  // is observable: 0x0057e1f5 and 0x0057e1fc both run before 0x0057e205.
  Word seen_at_zero[4] = {};
  Word seen_at_four[4] = {};
  bool sampled[4] = {};

  void reset() { *this = Observation(); }
};

Observation g_obs;

// How many bytes of the receiver changed inside the two stored words and how many
// changed outside them. The body writes exactly those eight bytes and nothing
// else, so every changed byte has to fall inside them.
struct ReceiverDiff {
  int inside = 0;
  int outside = 0;
};

ReceiverDiff diff_receiver(const Receiver& before, const Receiver& after) {
  ReceiverDiff diff;
  for (std::size_t index = 0; index < sizeof before.bytes; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    if (index < kZero + 2 * sizeof(Word)) {
      ++diff.inside;
    } else {
      ++diff.outside;
    }
  }
  return diff;
}

// A case: a receiver before the call, a receiver after, the value the body
// returned, and the run block so the caller can free it.
struct Case {
  Receiver before;
  Receiver after;
  Object* returned = nullptr;
  void* run_block = nullptr;
};

Case make_case(void* run_block, Word run_end_value, std::uint8_t deleting_flag) {
  Case item;
  std::memset(&item.after, 0, sizeof item.after);
  write_word(item.after.bytes, kRunBegin,
             static_cast<Word>(reinterpret_cast<std::uintptr_t>(run_block)));
  write_word(item.after.bytes, kRunEnd, run_end_value);
  // Decoys one word below and one word above the pair. A reconstruction reading
  // +0x08 or +0x10 instead of +0x0c or +0x14 would hand one of these over.
  write_word(item.after.bytes, kDecoyBelow, kDecoyWordBelow);
  write_word(item.after.bytes, kDecoyAbove, kDecoyWordAbove);
  // A decoy in the +0x04 word, so "the +0x04 store did not happen" shows up as an
  // unchanged byte rather than as an absence.
  write_word(item.after.bytes, kFour, kDecoyWordFour);
  item.before = item.after;
  item.run_block = run_block;

  g_obs.reset();
  g_active = &item.after;
  item.returned = re_0057e1d0(reinterpret_cast<Object*>(item.after.bytes),
                              deleting_flag);
  g_active = nullptr;
  return item;
}

// The invariant every case shares: the two stores, the two slots, the two
// neighbouring decoys untouched. `base` is the address the body's ECX pointed at,
// which on the thunk path is four below the pointer the caller held.
void check_stores(const unsigned char* base) {
  check(read_word(base, kZero) == kStoredAtZero,
        "the word at +0x00 is the constant the listing stores there");
  check(read_word(base, kFour) == kStoredAtFour,
        "the word at +0x04 is the constant the listing stores there");
  check(read_word(base, kDecoyBelow) == kDecoyWordBelow,
        "the decoy dword at +0x08 is never written");
  check(read_word(base, kDecoyAbove) == kDecoyWordAbove,
        "the decoy dword at +0x10 is never written");
}

void check_sentinel(const Case& item) {
  for (std::size_t index = 0; index < kSentinel; ++index) {
    check(item.after.bytes[kReceiverSize + index] == 0,
          "the sentinel tail past the receiver is untouched");
  }
}

}  // namespace

// 0x0057e1e8 and 0x0057e205 -- the release. cdecl, one pointer word, null
// tolerated (0x00f47386 JZ). The observer records the pointer and samples the
// receiver's two stored words, and deliberately does NOT free anything: this test
// asserts what the reconstruction passes, not what the callee does with it.
extern "C" void PKG_SW1_0057E1D0_CDECL heap_release_00f47380(void* pointer) {
  ++g_obs.release_calls;
  if (g_obs.log_length < 4) {
    g_obs.log[g_obs.log_length] = 0;
  }
  ++g_obs.log_length;
  if (g_obs.release_calls >= 1 && g_obs.release_calls <= 4) {
    g_obs.release_arg[g_obs.release_calls - 1] = pointer;
    if (g_active != nullptr) {
      g_obs.seen_at_zero[g_obs.release_calls - 1] = read_word(g_active->bytes, kZero);
      g_obs.seen_at_four[g_obs.release_calls - 1] = read_word(g_active->bytes, kFour);
      g_obs.sampled[g_obs.release_calls - 1] = true;
    }
  }
}

namespace {

// 0x0057a700 / 0x0057a703 -- the ONLY caller edge the xref export records for this
// VA (one reference, UNCONDITIONAL_CALL, from 0x0057a703). Its two instructions
// are `SUB ECX,0x4` and `JMP 0x0057e1d0`, so a caller holding P enters this body
// with P-4. Modelled as a plain function taking the caller's pointer, because
// that is the whole of what the two instructions do.
Object* adjusting_thunk_0057a700(Object* caller_pointer, std::uint8_t flag) {
  unsigned char* const base = reinterpret_cast<unsigned char*>(caller_pointer);
  return re_0057e1d0(reinterpret_cast<Object*>(base - 4), flag);
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w1_0057e1d0

int main() {
  namespace recon = openspore::reconstruction::pkg_swarm_w1_0057e1d0;
  using recon::Case;
  using recon::Word;
  using recon::check;
  using recon::read_word;
  using recon::kDecoyBelow;
  using recon::kDecoyWordLow;
  using recon::kDecoyWordHigh;
  using recon::kFour;
  using recon::kRunBegin;
  using recon::kRunEnd;
  using recon::kStoredAtFour;
  using recon::kStoredAtZero;
  using recon::kZero;

  // -- A: every condition true, direct entry ---------------------------------
  {
    void* run = recon::block(8, 0xa5);
    const Word begin = static_cast<Word>(reinterpret_cast<std::uintptr_t>(run));
    Case item = recon::make_case(run, begin + 8u, 0x01);

    check(recon::g_obs.release_calls == 2,
          "A: exactly two releases when the flag is set");
    check(recon::g_obs.log_length == 2 && recon::g_obs.log[0] == 0 &&
              recon::g_obs.log[1] == 0,
          "A: both transfers are releases, in that order");
    check(recon::g_obs.release_arg[0] == run, "A: the first release gets the +0x0c word");
    check(recon::g_obs.release_arg[1] == item.after.bytes,
          "A: the second release gets the receiver itself");
    check(item.returned == reinterpret_cast<recon::Object*>(item.after.bytes),
          "A: the body returns the receiver it was entered with, on the release path");
    recon::check_stores(item.after.bytes);
    const recon::ReceiverDiff diff = recon::diff_receiver(item.before, item.after);
    check(diff.inside == 8, "A: all eight stored bytes changed");
    check(diff.outside == 0, "A: no byte outside the two stored words changed");
    recon::check_sentinel(item);
    std::free(run);
  }

  // -- A': the return value on the fall-through path as well -----------------
  {
    void* run = recon::block(8, 0xa5);
    const Word begin = static_cast<Word>(reinterpret_cast<std::uintptr_t>(run));
    Case item = recon::make_case(run, begin + 8u, 0x00);
    check(recon::g_obs.release_calls == 1,
          "A': only the run word is released when the flag is clear");
    check(item.returned == reinterpret_cast<recon::Object*>(item.after.bytes),
          "A': the body returns the receiver on the no-release path as well");
    recon::check_stores(item.after.bytes);
    std::free(run);
  }

  // -- B: write ordering and target identity ---------------------------------
  {
    void* run = recon::block(8, 0x5a);
    const Word begin = static_cast<Word>(reinterpret_cast<std::uintptr_t>(run));
    Case item = recon::make_case(run, begin + 8u, 0x01);
    check(recon::g_obs.sampled[0] && recon::g_obs.sampled[1],
          "B: both releases were observed from inside the call");
    check(recon::g_obs.seen_at_zero[1] == kStoredAtZero,
          "B: +0x00 already holds its constant when the receiver is released");
    check(recon::g_obs.seen_at_four[1] == kStoredAtFour,
          "B: +0x04 already holds its constant when the receiver is released");
    recon::check_stores(item.after.bytes);
    std::free(run);
  }

  // -- C: SIGNED vs UNSIGNED compare at 0x0057e1de ---------------------------
  // The body is `CMP ECX,0x2` / `JLE`, and JLE (0x7E) is the SIGNED form. A
  // difference whose bit 31 survives `AND ECX,0xfffffffe` is negative as a signed
  // 32-bit value, so it is <= 2 and nothing is released. An unsigned reading of the
  // same three instructions releases on every one of the negative rows below.
  {
    struct Input {
      std::int64_t delta;  // end - begin, applied modulo 2^32
      int expected;        // releases expected
      const char* why;
    };
    const Input inputs[] = {
        {4, 2, "C: a positive span of 4 releases the run word"},
        {6, 2, "C: a positive span of 6 releases the run word"},
        {0x7ffffffe, 2, "C: a large positive span releases the run word"},
        {-2, 1, "C: a span of -2 masks to 0xfffffffe, signed -2, so nothing is released"},
        {-4, 1, "C: a span of -4 masks to 0xfffffffc, signed -4, so nothing is released"},
        {static_cast<std::int64_t>(0x80000000u), 1,
         "C: a span of 0x80000000 is signed INT_MIN, so nothing is released"},
        {0, 1, "C: a span of 0 is not over the threshold"},
    };
    const Word base = 0x00002000u;
    for (const Input& input : inputs) {
      const Word begin = base;
      const Word end = begin + static_cast<Word>(input.delta);
      void* run = reinterpret_cast<void*>(static_cast<std::uintptr_t>(begin));
      Case item = recon::make_case(run, end, 0x01);
      check(recon::g_obs.release_calls == input.expected, input.why);
      if (input.expected == 2) {
        check(recon::g_obs.release_arg[0] == run,
              "C: the positive-span release gets the +0x0c word");
      }
      recon::check_stores(item.after.bytes);
    }
  }

  // -- D: the mask rounds DOWN to even ---------------------------------------
  {
    // Differences of 1 and 3 become 0 and 2 under `AND ECX,0xfffffffe`, and both
    // are <= 2. A reconstruction that dropped the AND releases on both.
    const Word base = 0x00003000u;
    const std::int64_t no_release[] = {1, 2, 3};
    for (std::int64_t delta : no_release) {
      void* run = reinterpret_cast<void*>(static_cast<std::uintptr_t>(base));
      const Word end = base + static_cast<Word>(delta);
      Case item = recon::make_case(run, end, 0x01);
      check(recon::g_obs.release_calls == 1,
            "D: a span of 1, 2 or 3 rounds down to 0 or 2 and does not release");
      recon::check_stores(item.after.bytes);
    }
    const std::int64_t release[] = {4, 5, 6};
    for (std::int64_t delta : release) {
      void* run = reinterpret_cast<void*>(static_cast<std::uintptr_t>(base));
      const Word end = base + static_cast<Word>(delta);
      Case item = recon::make_case(run, end, 0x01);
      check(recon::g_obs.release_calls == 2,
            "D: a span of 4, 5 or 6 rounds down to 4 or 6 and does release");
      recon::check_stores(item.after.bytes);
    }
  }

  // -- E: the null guard at 0x0057e1e3 --------------------------------------
  {
    // A comfortably over-threshold span with a null word. Only `TEST EAX,EAX` can
    // stop the release, so a model that dropped it releases a null word.
    Case item = recon::make_case(nullptr, 0x00004010u, 0x01);
    check(recon::g_obs.release_calls == 1,
          "E: a null +0x0c word is not released even with a wide span");
    check(recon::g_obs.release_arg[0] == item.after.bytes,
          "E: the only release is the receiver");
    recon::check_stores(item.after.bytes);
  }

  // -- F: flag polarity and bit width ----------------------------------------
  {
    struct Input {
      std::uint8_t flag;
      int expected;
      const char* why;
    };
    const Input inputs[] = {
        {0x00, 1, "F: flag 0x00 does not release the receiver"},
        {0x02, 1, "F: flag 0x02 does not release the receiver: only bit 0 is tested"},
        {0xfe, 1, "F: flag 0xfe does not release the receiver: only bit 0 is tested"},
        {0x80, 1, "F: flag 0x80 does not release the receiver: the high bits are ignored"},
        {0x01, 2, "F: flag 0x01 releases the receiver"},
        {0x03, 2, "F: flag 0x03 releases the receiver"},
        {0xff, 2, "F: flag 0xff releases the receiver"},
    };
    for (const Input& input : inputs) {
      void* run = recon::block(8, 0x3c);
      const Word begin = static_cast<Word>(reinterpret_cast<std::uintptr_t>(run));
      Case item = recon::make_case(run, begin + 8u, input.flag);
      check(recon::g_obs.release_calls == input.expected, input.why);
      if (input.expected == 2) {
        check(recon::g_obs.release_arg[1] == item.after.bytes,
              "F: the second release is the receiver and not the run word");
      } else {
        check(recon::g_obs.release_arg[0] == run,
              "F: the first release is the run word either way");
      }
      recon::check_stores(item.after.bytes);
      recon::check_sentinel(item);
      std::free(run);
    }
  }

  // -- G, H and I: entered through the adjusting thunk at 0x0057a700 ---------
  //
  // The body's `this` is four below the pointer the caller holds, so the run pair
  // lives at self+0x0c and self+0x14 and the two stores land at self and self+0x04
  // -- which are P-4 and P. A model that believed its `this` WAS the caller's
  // pointer would instead read its run pair from P+0x0c and P+0x14 and write its
  // stores at P and P+4, so decoys are planted at exactly those four places.
  //
  // The buffer layout, given self = wide+4 and P = wide+8, is therefore:
  //
  //   wide+0    P-8    untouched, asserted zero
  //   wide+4    P-4    the +0x00 store   (and the caller's +0x04 store slot)
  //   wide+8    P      the +0x04 store   (and the caller's +0x00 store slot)
  //   wide+12   self+0x08   decoy word, must survive
  //   wide+16   self+0x0c   the REAL run begin
  //   wide+20   self+0x10   -- and, under the caller's hypothesis, P+0x0c: the
  //                            decoy run-begin word. ONE address, two roles: the
  //                            two hypotheses differ by exactly the thunk's four
  //                            bytes, so self+0x10 and P+0x0c are the same word and
  //                            cannot both carry decoys. The caller's role is the
  //                            one kept, because it is the only one that can catch
  //                            a pointer-believing model; the +0x10 word's
  //                            non-interference is already asserted on every direct
  //                            path above, where no such collision exists.
  //   wide+24   self+0x14   the REAL run end
  //   wide+28   P+0x14      the decoy run-end word, must survive
  {
    unsigned char wide[64];
    std::memset(wide, 0, sizeof wide);

    void* run = recon::block(8, 0xc3);
    const Word run_address = static_cast<Word>(reinterpret_cast<std::uintptr_t>(run));

    unsigned char* const self = wide + 4;      // what the body's ECX receives
    unsigned char* const caller_p = wide + 8;  // what the caller holds

    recon::write_word(self, kRunBegin, run_address);
    recon::write_word(self, kRunEnd, run_address + 8u);
    recon::write_word(self, kDecoyBelow, recon::kDecoyWordBelow);
    // The caller's run-pair decoys, placed as P+0x0c and P+0x14.
    recon::write_word(caller_p, kRunBegin, kDecoyWordLow);
    recon::write_word(caller_p, kRunEnd, kDecoyWordHigh);

    recon::g_obs.reset();
    recon::g_active = reinterpret_cast<recon::Receiver*>(self);
    recon::Object* const returned = recon::adjusting_thunk_0057a700(
        reinterpret_cast<recon::Object*>(caller_p), 0x01);
    recon::g_active = nullptr;

    check(returned == reinterpret_cast<recon::Object*>(self),
          "I: the body returns the pointer it was ENTERED with, not the caller's");
    check(recon::g_obs.release_calls == 2, "I: the thunk path makes the same two releases");
    check(recon::g_obs.release_arg[0] == run,
          "G: the first release is the word read at the body's +0x0c, not P+0x0c");
    check(recon::g_obs.release_arg[1] == self,
          "G: the second release is the body's own receiver, i.e. P-4");
    check(recon::g_obs.seen_at_zero[1] == kStoredAtZero &&
              recon::g_obs.seen_at_four[1] == kStoredAtFour,
          "B/I: both stores are already in memory when the receiver is released");

    // The two store slots, relative to the CALLER's pointer P.
    check(read_word(self, kZero) == kStoredAtZero, "I: P-4 receives the +0x00 constant, not P");
    check(read_word(caller_p, 0) == kStoredAtFour, "I: P receives the +0x04 constant, not P+4");
    // P+4 is self+0x08, so the +0x08 decoy below doubles as the store-side decoy:
    // a model that wrote its stores at P and P+4 would clobber it.
    // The neighbours and the two caller-hypothesis decoys, all of which must
    // survive untouched.
    check(read_word(self, kDecoyBelow) == recon::kDecoyWordBelow,
          "H: the decoy at the body's +0x08 is never written");
    check(read_word(caller_p, kRunBegin) == kDecoyWordLow,
          "G: the decoy run-begin word is never read or written");
    check(read_word(caller_p, kRunEnd) == kDecoyWordHigh,
          "G: the decoy run-end word is never read or written");
    check(read_word(self, kRunEnd) == run_address + 8u,
          "H: the real run-end word at the body's +0x14 is never written");
    check(read_word(wide, 0) == 0u, "H: nothing is written at P-8");
    std::free(run);
  }

  if (recon::g_failures == 0) {
    std::printf("pkg-swarm-w1-0057e1d0: all model checks passed\n");
    return 0;
  }
  std::fprintf(stderr, "pkg-swarm-w1-0057e1d0: %d model check(s) failed\n",
               recon::g_failures);
  return 1;
}
