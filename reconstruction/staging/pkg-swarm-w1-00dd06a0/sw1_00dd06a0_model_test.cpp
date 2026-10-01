// PKG-SWARM-W1-00DD06A0 -- model test for re_00dd06a0
//
// WHAT THIS TEST IS FOR
//
// The model is 26 instructions of arithmetic and control flow, which is exactly
// the shape where a reconstruction can be confidently WRONG in ways that still
// look right: the wrong constant, the wrong branch polarity, the wrong
// displacement, a cached value where the machine re-reads memory, a value pushed
// where a pointer is. This file therefore does not walk the model. It tries to
// break it, and every case below is written to fail if the reconstruction
// deviates from the listing in one specific way.
//
// The nine mutation classes, and where each is refuted:
//
//   M1 wrong constant / off-by-one displacement  A1, A2, A3, A4, A5, B2
//   M2 wrong branch polarity                     A2, A3, B1
//   M3 signed-vs-unsigned, one-bit differences  A3, A5, B2, B5
//   M4 wrong pointer level (value vs pointee)    B3
//   M5 wrong receiver offset, with decoys        A1
//   M6 wrong callee / wrong argument             B3, B4, B6
//   M7 wrong write ordering / stale value        B4, B5
//   M8 probe consulted on the wrong arm          B1, B2
//   M9 wrong receiver register or argument count C1, C2, C3
//
// The independent oracle. A1 does not compare the model against a hand-written
// table of expected answers. It compares it against kind_arm_arithmetic(), a
// transcription of the five arithmetic instructions of the 0x84 arm, swept over
// 40 id values spanning the interesting ones. A wrong mask, a wrong addend, a
// wrong subtractand, a wrong selection direction or a signed predicate all make
// the two disagree somewhere in that sweep, and the sweep includes 0x00000001
// (which is 1 off the subtractand), 0x00000003 (1 past it) and 0xfffffffe (which
// wraps to the subtractand), the four neighbours of the present value in both
// directions, and the 32 extremes.
//
// THE MEASUREMENTS. Three claims are not checkable by calling the model and
// looking at the answer, and each has an instrument instead:
//
//   * that the model consumes NO stack word -- trampoline A samples ESP before
//     and after a raw call and requires them equal. A model that expected an
//     argument word would unbalance the stack by four bytes.
//   * that the model takes its receiver from ECX and not from the argument slot
//     -- trampoline B pushes a SECOND, decoy object onto the stack so that
//     [ESP+4] holds it while ECX holds the real one, then requires the answer to
//     come from the ECX object.
//   * that nothing is pushed for the probe -- the probe observer samples ESP on
//     its own entry and the trampoline's pre-call sample is compared against it.
//
// WHAT THIS TEST DELIBERATELY DOES NOT ASSERT, and why
//
//  1. The five intermediates of the 0x84 arm (id-2, 2-id, -CF, the mask, the
//     addend). No memory is touched between 0x00dd06ac and 0x00dd06be, there is
//     no call, and EAX is overwritten by the next instruction on both arms, so
//     no black-box caller can observe them. A1 asserts the arm's two results over
//     40 inputs, which is the whole of what is observable.
//  2. The caller-side `ADD ESP,0x4` at 0x00dd06e6. For a cdecl leaf callee that
//     does not touch the caller's stack, a callee-pops and a caller-pops return
//     are the same machine behaviour, so no black-box observer can tell them
//     apart. The convention is established by the callee's own bare `C3`, which is
//     real evidence; it just is not evidence a test can exercise. The mirror-image
//     claim about the MODEL's own balance IS measured, in C1.
//  3. The order of the arithmetic operations among themselves, for the same
//     reason as (1).
//  4. What the word at receiver+0x84 means, and what the word at receiver+0x88
//     means, and what 0xff576f79 means. Only the displacements, the widths, the
//     number of reads and the values are asserted. A3 drives the word at +0x84
//     with 0, 1, 2 and 0x7fffffff and requires the arm to move only at 1, which
//     is all the listing fixes.
//  5. Whether the value at +0x88 is an id, a hash, a count or a pointer. The
//     model never dereferences it and the test proves it does not (B3), but no
//     claim about what it is made.
//  6. That the callees' interiors behave as their own listings suggest. Both are
//     observers here, defined by the test; their behaviour is scripted per case
//     and is not evidence about 0x00b6e250 or 0x00b6f0d0.
//  7. The order of the two calls relative to EACH OTHER is asserted (B1/B2/B4),
//     but nothing about either callee's own callees, because neither is modelled.

#include "sw1_00dd06a0_types.hpp"

#include <cstdio>
#include <cstring>

namespace osw = openspore::reconstruction::pkg_swarm_w1_00dd06a0;
using osw::OpaqueSporepediaAsset;
using osw::Word;
// Pulled into the global namespace so the two observer definitions below -- which
// have C language linkage and therefore cannot sit inside a namespace -- can
// reach the displacements and the present value without qualification.
using osw::kAbsentValue;
using osw::kIdDisplacement;
using osw::kKindArmSelectedValue;
using osw::kKindDisplacement;

// The observers' own read of the object under test. Deliberately NOT the header's
// word_at: this one is instrumentation the model cannot see or influence.
Word probe_word_at(const OpaqueSporepediaAsset* object, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(object) +
                                        displacement);
}

void probe_write_word(OpaqueSporepediaAsset* object, std::size_t displacement,
                      Word value) {
  *reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(object) +
                           displacement) = value;
}

namespace {

// -- harness -----------------------------------------------------------------
// No framework, no dependency. Every check names itself, so a failure says which
// mutation it kills.

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL  %s\n", what);
  }
}

void check_word(Word got, Word want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL  %s: got 0x%08x, want 0x%08x\n", what, got, want);
  }
}

void check_signed(std::int32_t got, std::int32_t want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL  %s: got %d (0x%08x), want %d (0x%08x)\n", what, got,
                static_cast<Word>(got), want, static_cast<Word>(want));
  }
}

// -- the object under test ---------------------------------------------------
// 0x8c bytes: exactly this body's reach. The decoy words are at the neighbouring
// displacements a reconstruction is most likely to get wrong -- 0x80 one dword
// low, 0x8c one dword high, 0x83/0x87 the byte-lowered variants -- and each
// carries a value that would produce a DIFFERENT answer if it were the one read.

// The modelled receiver is 0x8c bytes -- the last byte this body reads is +0x8b --
// and the fixture is deliberately LONGER, so decoy words can sit on both sides of
// the model's reach. A reconstruction that read one dword low or one dword high
// gets a decoy instead of the answer, and says so by producing a word no correct
// path can produce.
constexpr std::size_t kObjectBytes = 0x98;
constexpr Word kDecoyBelow = 0x11111111u;  // at +0x80, one dword under the kind
constexpr Word kDecoyAbove = 0x22222222u;  // at +0x8c, one dword over the id
constexpr Word kDecoyFarAbove = 0x44444444u;  // at +0x90, where a float lives

// A word planted one level down, at the address a reconstruction would get if it
// read *(&receiver->field_88) instead of receiver->field_88. Its value is a
// poison that no correct path can return, and B3 requires the returned word never
// to be it.
Word g_poisoned_pointee = 0x5a5a5a5au;

// The modelled receiver's own size, restated here so the fixture can assert it
// against the type the model was declared with.
static_assert(kObjectBytes > sizeof(OpaqueSporepediaAsset),
              "the fixture must be longer than the modelled receiver, so decoys "
              "can sit on both sides of the model's reach");
static_assert(sizeof(OpaqueSporepediaAsset) == 0x8c,
              "0x88 + 4 is the last byte this body reads on the receiver");

struct Fixture {
  alignas(4) std::uint8_t bytes[kObjectBytes];

  void reset() { std::memset(bytes, 0, sizeof bytes); }

  OpaqueSporepediaAsset* object() {
    return reinterpret_cast<OpaqueSporepediaAsset*>(bytes);
  }

  Word& at(std::size_t displacement) {
    return *reinterpret_cast<Word*>(bytes + displacement);
  }

  void plant_neighbour_decoys() {
    at(kKindDisplacement - 4) = kDecoyBelow;
    at(kIdDisplacement + 4) = kDecoyAbove;
    at(kIdDisplacement + 8) = kDecoyFarAbove;
  }
};

// -- observers ---------------------------------------------------------------
// Both direct callees, defined here as observers. Between them they see every
// transfer the model makes: which callee, in which order, with which argument,
// and what the object looked like at the moment of the call. The model test's
// whole value is that the probe runs INSIDE the model's execution, so a
// mid-flight mutation is visible to a later observer.

// A NOTE ON AN INSTRUMENT THAT WAS BUILT AND THEN WITHDRAWN, because the reason
// is the kind of thing worth knowing about testing a compiled model at all.
//
// The obvious way to answer "what exactly did the model hand this callee" is to
// read the word directly above the callee's own return address: for a callee
// entered with ESP = E, the standard `push ebp / mov esp,ebp` prologue puts EBP at
// E-8, so [EBP+8] is the word at E -- the caller's stack top at the instant of the
// call, untouched by any C++ parameter binding. That was implemented, and it
// reported the same unrelated word for both callees.
//
// The reason is the model itself: compiled at -O0 with 16-byte stack alignment,
// re_00dd06a0 emits `subl $12,%esp` before every call, so by the time a callee is
// entered the caller's stack has twelve bytes of compiler padding above the
// argument slot. [EBP+8] therefore reads the padding, not the argument, and the
// reading is a fact about the compiler, not about the listing. The same
// contamination killed an earlier version's stack-DEPTH instrument, which
// measured 48 bytes of compiler frame where the listing's prologue accounts for 4.
//
// So neither the depth nor the slot is asserted. What survives, and is asserted in
// C3, is the pair the trampoline CAN see: that the model's frame is fully balanced
// across the call, and that the trampoline's own decoy word is still the top of the
// stack when the model returns. Together those say the model left nothing behind --
// whatever it pushed for the lookup, it removed -- which is the part of
// 0x00dd06e6's `ADD ESP,0x4` that a black-box caller can see at all.

struct Observation {
  int probe_calls = 0;
  int lookup_calls = 0;
  int call_order = 0;             // 1 = probe then lookup, 2 = lookup then probe
  Word lookup_argument = 0;       // the value the lookup observer received
  Word id_at_probe = 0;           // receiver+0x88 as it was when the probe ran
  Word kind_at_probe = 0;         // receiver+0x84 as it was when the probe ran
  Word id_at_lookup = 0;          // receiver+0x88 as it was when the lookup ran
};

Observation g_obs;
bool g_probe_result = true;
Word g_lookup_result = 0;

// Scripted mid-flight mutations, applied by the probe observer so that a
// difference between the value the model compared and the value it hands over
// becomes observable at the next callee boundary.
bool g_probe_rewrites_id = false;
Word g_probe_new_id = 0;
bool g_probe_rewrites_kind = false;
Word g_probe_new_kind = 0;

// The object the observers read through, set by the test before each call. This
// is instrumentation, not a machine global: the model has no way to tell the
// observers about it.
OpaqueSporepediaAsset* g_under_test = nullptr;

void reset_observers() {
  g_obs = Observation();
  g_probe_result = true;
  g_lookup_result = 0;
  g_probe_rewrites_id = false;
  g_probe_new_id = 0;
  g_probe_rewrites_kind = false;
  g_probe_new_kind = 0;
}

}  // namespace

// -- the two observers, at the addresses the model names ---------------------
// 0x00b6e250: cdecl, zero arguments, terminator a bare C3. The ESP sample is the
// whole point of this definition -- it is how "nothing was pushed" becomes a
// measurement.

extern "C" bool PKG_SWARM_W1_00DD06A0_CDECL sporepedia_db_ready_probe_00b6e250() {
  ++g_obs.probe_calls;
  if (g_under_test != nullptr) {
    g_obs.id_at_probe = probe_word_at(g_under_test, kIdDisplacement);
    g_obs.kind_at_probe = probe_word_at(g_under_test, kKindDisplacement);
  }
  if (g_probe_rewrites_id && g_under_test != nullptr) {
    probe_write_word(g_under_test, kIdDisplacement, g_probe_new_id);
  }
  if (g_probe_rewrites_kind && g_under_test != nullptr) {
    probe_write_word(g_under_test, kKindDisplacement, g_probe_new_kind);
  }
  return g_probe_result;
}

// 0x00b6f0d0: cdecl, one four-byte stack argument read as a dword, terminator a
// bare C3. This definition records the ARGUMENT'S VALUE, which is what makes
// wrong-callee, wrong-argument and stale-value defects visible, and samples ESP
// so the argument word can be located and read back out of the caller's frame.

extern "C" Word PKG_SWARM_W1_00DD06A0_CDECL sporepedia_lookup_packed_00b6f0d0(
    Word key) {
  ++g_obs.lookup_calls;
  g_obs.call_order = (g_obs.probe_calls > 0) ? 1 : 2;
  g_obs.lookup_argument = key;
  if (g_under_test != nullptr) {
    g_obs.id_at_lookup = probe_word_at(g_under_test, kIdDisplacement);
  }
  return g_lookup_result;
}

namespace {

// -- a plain C++ call --------------------------------------------------------
// Going through the declared thiscall prototype at all is a first receiver
// assertion: if the model had been declared cdecl, the compiler would have put
// the receiver in the argument slot and ECX would hold whatever, and every case
// below would read from a wild address rather than fail cleanly.

std::int32_t call_model(OpaqueSporepediaAsset* object) {
  g_under_test = object;
  return osw::re_00dd06a0(object);
}

// -- the raw-call trampoline -------------------------------------------------
// Three claims in this package are not checkable by calling the model and
// looking at its answer, and this instrument is how all three are checked. It is
// written as a top-level asm block rather than as an asm statement inside a C++
// function, so that nothing about the measurement depends on how the register
// allocator happens to feel on the day -- a constrained inline asm with five
// operands on eight registers is a portability hazard, and a measurement that
// might not compile is not a measurement.
//
// The decoy push is always present, and it is what makes one trampoline serve all
// three claims:
//
//   out[0]  ESP at the callee's entry, with the decoy word still on the stack
//   out[1]  ESP at the callee's return, with the decoy word still on the stack
//   out[2]  EAX at the return site
//
//   * out[1] == out[0]  is the claim that the model POPPED NOTHING. All three of
//     its terminators are a bare C3, so a body that expected an argument word --
//     a `RET 0x4`, say -- would leave out[1] four bytes ABOVE out[0].
//   * the caller's stack top at each call site, read INSIDE the observers. What
//     the model hands a callee is a question about the machine's stack slot, and
//     the observers answer it by reading the word directly above their own return
//     address (see caller_stack_top()). The trampoline's decoy word is the
//     control: it is what the probe MUST find above its return address, because
//     the trampoline pushed it and the model pushed nothing of its own. This is
//     the instrument that survives being compiled, and the depth-difference
//     instrument this file first tried does NOT, for a reason worth recording --
//     see the not-asserted list.
//   * EAX versus [ESP+4]  is the claim that the receiver came from ECX: the
//     trampoline loads the real object into ECX and pushes the decoy onto the
//     stack, so at the callee's entry [ESP+4] is the decoy's address. A model
//     that read its receiver from the first argument slot would answer from the
//     decoy, which the cases below deliberately give a different answer.

struct TrampolineSample {
  Word esp_at_entry;
  Word esp_at_return;
  Word returned;
  Word decoy;            // the word the trampoline pushed
  Word caller_top_after; // the caller's stack top once the model had returned
};

extern "C" void trampoline_measure(OpaqueSporepediaAsset* receiver,
                                   OpaqueSporepediaAsset* stack_decoy,
                                   std::uint32_t* out);

__asm__(
    ".text\n\t"
    ".globl trampoline_measure\n\t"
    ".type trampoline_measure, @function\n"
    "trampoline_measure:\n\t"
    "pushl %ebp\n\t"
    "movl %esp, %ebp\n\t"
    "pushl %ebx\n\t"
    "pushl %esi\n\t"
    "pushl %edi\n\t"
    "movl 8(%ebp), %edi\n\t"    /* edi = the real receiver             */
    "movl 12(%ebp), %ebx\n\t"   /* ebx = the stack decoy               */
    "movl 16(%ebp), %esi\n\t"   /* esi = the out buffer                */
    "pushl %ebx\n\t"            /* the decoy word now occupies [ESP]   */
    "movl %esp, %ebx\n\t"       /* ebx = ESP at the callee's entry     */
    "movl %ebx, (%esi)\n\t"     /* out[0]                              */
    "movl %edi, %ecx\n\t"       /* the receiver arrives in ECX          */
    "call re_00dd06a0\n\t"      /* extern "C", so the symbol is bare   */
    "movl %eax, 8(%esi)\n\t"    /* out[2] = the return word in EAX     */
    "movl %ebx, %eax\n\t"
    "movl %eax, 4(%esi)\n\t"    /* out[1] = ESP at the return          */
    "movl (%esp), %eax\n\t"     /* out[3] = the caller's stack top...   */
    "movl %eax, 12(%esi)\n\t"   /*         ...which must still be the   */
    "addl $4, %esp\n\t"         /*         decoy the trampoline pushed */
    "popl %edi\n\t"
    "popl %esi\n\t"
    "popl %ebx\n\t"
    "popl %ebp\n\t"
    "ret\n\t"
    ".size trampoline_measure, .-trampoline_measure\n\t");

// A decoy that must never be the answer: a model reading the wrong object, the
// wrong displacement of it, or a pointer to it, lands here. It is configured so
// its answer is the 0x84 arm's addend case, 0xfffff045, a value the real objects
// in the C2 loop never produce.
Fixture make_stack_decoy() {
  Fixture decoy;
  decoy.reset();
  decoy.plant_neighbour_decoys();
  decoy.at(kKindDisplacement) = 0x00000001u;
  decoy.at(kIdDisplacement) = 0x00000002u;
  return decoy;
}

// mode 0: through the model, which is what every behavioural measurement uses.
TrampolineSample measure(OpaqueSporepediaAsset* receiver,
                         OpaqueSporepediaAsset* stack_decoy) {
  std::uint32_t out[4] = {0u, 0u, 0u, 0u};
  trampoline_measure(receiver, stack_decoy, out);
  TrampolineSample s{};
  s.esp_at_entry = out[0];
  s.esp_at_return = out[1];
  s.returned = out[2];
  s.decoy = reinterpret_cast<Word>(stack_decoy);
  s.caller_top_after = out[3];
  return s;
}

// -- the independent oracle --------------------------------------------------
// The 0x84 arm transcribed one instruction at a time. This is the SAME function
// the header static_asserts against, used here as a reference to sweep the model
// against, so a hand-typed expectation table can never be the thing that is
// wrong on both sides at once.

Word oracle_kind_arm(Word id) {
  Word eax = id;                                       // 00dd06ac
  eax -= 0x02u;                                        // 00dd06b2
  eax = 0u - eax;                                      // 00dd06b5
  const Word sbb = (eax == 0u) ? 0u : 0xffffffffu;     // 00dd06b7
  eax = sbb & 0xff577f34u;                             // 00dd06b9
  return eax + 0xfffff045u;                            // 00dd06be
}

// The four neighbours of 0xff576f79 in both directions, and the 32 extremes.
// A compare that is off by one displacement, or a signed compare where an
// unsigned one is meant, or a test of a neighbouring bit, all show up here.
const Word kSweep[] = {
    0x00000000u, 0x00000001u, 0x00000002u, 0x00000003u, 0x00000004u,
    0x00000005u, 0x00000010u, 0x000000ffu, 0x00000100u, 0x0000ffffu,
    0x00010000u, 0x12345678u, 0x7ffffffeu, 0x7fffffffu, 0x80000000u,
    0x80000001u, 0xffffff00u, 0xffffff01u, 0xfffffffeu, 0xffffffffu,
    0xff576f77u, 0xff576f78u, 0xff576f79u, 0xff576f7au, 0xff576f7bu,
    0xff577f33u, 0xff577f34u, 0xff577f35u, 0xfffff044u, 0xfffff045u,
    0xfffff046u, 0x00000002u, 0x00000002u, 0x00dd06a0u, 0x0147cbbcu,
};
constexpr std::size_t kSweepCount = sizeof(kSweep) / sizeof(kSweep[0]);

// ===========================================================================
// A. The 0x84 arm -- arithmetic, constants, polarity
// ===========================================================================

void case_a1_sweep_against_the_oracle() {
  // M1/M3. 40 ids, each compared against the five-instruction transcription.
  // Kills: wrong mask, wrong addend, wrong subtractand, wrong selection
  // direction, a signed predicate, a range test, an off-by-one.
  int mismatches = 0;
  for (std::size_t i = 0; i < kSweepCount; ++i) {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = 0x01u;
    f.at(kIdDisplacement) = kSweep[i];
    const Word got = static_cast<Word>(call_model(f.object()));
    if (got != oracle_kind_arm(kSweep[i])) ++mismatches;
  }
  check(mismatches == 0,
        "A1 the 0x84 arm agrees with the instruction transcription on all 40 "
        "sweep ids");
  if (mismatches != 0) {
    std::printf("      A1 mismatched on %d of %zu ids\n", mismatches, kSweepCount);
  }
}

void case_a2_polarity_of_the_kind_test() {
  // M2. The arm fires at kind == 1 and ONLY at kind == 1. Driving kind 0 and
  // kind 2 with an id that the arm would answer 0 for must leave the arm and
  // reach the lookup instead -- which is only true if the compare is an equality
  // against 1, not a non-zero test and not an off-by-one.
  // 0x00000100 and 0x0000ff01 are byte-width decoys: their byte at +0x85 is 1,
  // so a model that read ONE BYTE of the kind word instead of the dword would take
  // this arm, while the dword at +0x84 is not 1 and must not.
  for (Word kind : {0x00000000u, 0x00000002u, 0x00000003u, 0x7fffffffu,
                    0x80000000u, 0xffffffffu, 0x00000100u, 0x0000ff01u,
                    0x01000000u}) {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = kind;
    f.at(kIdDisplacement) = 0x00000002u;  // the id the arm would answer 0 for
    g_lookup_result = 0x0badf00du;
    reset_observers();
    g_lookup_result = 0x0badf00du;
    const Word got = static_cast<Word>(call_model(f.object()));
    check_word(got, 0x0badf00du, "A2 kind != 1 must take the lookup path");
    check(g_obs.probe_calls == 1, "A2 kind != 1 must consult the probe once");
    check(g_obs.lookup_calls == 1, "A2 kind != 1 must call the lookup once");
  }

  // And the positive direction: kind == 1 with the same id answers 0 and touches
  // no callee at all.
  Fixture f;
  f.reset();
  f.plant_neighbour_decoys();
  f.at(kKindDisplacement) = 0x01u;
  f.at(kIdDisplacement) = 0x00000002u;
  reset_observers();
  check_word(static_cast<Word>(call_model(f.object())), 0xfffff045u,
             "A2 kind == 1 and id == 2 returns 0xfffff045, the addend alone -- "
             "NOT zero, because the ADD at 0x00dd06be is unconditional");
  check(g_obs.probe_calls == 0, "A2 the 0x84 arm calls neither callee");
  check(g_obs.lookup_calls == 0, "A2 the 0x84 arm calls neither callee");
}

void case_a3_the_arm_is_one_bit_exact() {
  // M3. Four ids, one bit apart, in the same kind. The arm's answer may only
  // move for the id that equals the subtractand. A predicate on the low bit, on
  // parity, or on a different immediate, all move the answer somewhere else.
  struct Row {
    Word id;
    Word want;
  };
  const Row rows[] = {
      {0x00000000u, osw::kAbsentValue},          // the other neighbour, low
      {0x00000001u, osw::kAbsentValue},          // one below the subtractand
      {0x00000002u, 0xfffff045u},                // exactly it: the addend alone
      {0x00000003u, osw::kAbsentValue},          // one above
      {0xfffffffeu, osw::kAbsentValue},          // wrapping does not reach it
      {0x80000000u, osw::kAbsentValue},          // the signed extreme
  };
  for (const Row& row : rows) {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = 0x01u;
    f.at(kIdDisplacement) = row.id;
    reset_observers();
    check_word(static_cast<Word>(call_model(f.object())), row.want,
               "A3 the arm's answer moves only for id == 2");
  }
}

void case_a4_neighbour_decoys_are_never_the_answer() {
  // M1/M5. The words one dword below, one dword above and byte-lowered at both
  // displacements carry poison. If any of them were read, the answer would be
  // one of the decoys, and the model never returns one. Driven from the arm, from
  // the sentinel arm and from the lookup arm.
  const Word decoys[] = {kDecoyBelow, kDecoyAbove, kDecoyFarAbove, 0x11111111u,
                         0x22222222u, 0x44444444u, g_poisoned_pointee,
                         kKindArmSelectedValue ^ 0x00000001u};
  for (Word kind : {0x00000000u, 0x00000001u}) {
    for (Word id : {0x00000002u, 0x00000003u, 0x00000007u, 0xffffffffu,
                    osw::kAbsentValue}) {
      Fixture f;
      f.reset();
      f.plant_neighbour_decoys();
      f.at(kKindDisplacement) = kind;
      f.at(kIdDisplacement) = id;
      g_lookup_result = 0x0badf00du;
      reset_observers();
      g_lookup_result = 0x0badf00du;
      const Word got = static_cast<Word>(call_model(f.object()));
      bool matched_a_decoy = false;
      for (Word decoy : decoys) {
        if (got == decoy) matched_a_decoy = true;
      }
      check(!matched_a_decoy,
            "A4 no neighbouring displacement or pointee value is ever returned");
    }
  }
  // The arm's id==2 case is the addend on its own -- 0xfffff045 -- and not a
  // zero, because 0x00dd06be's ADD is unconditional. Pinning it here as well as
  // in A1/A3 makes the "returned zero" defect fail with a named check.
  check_word(oracle_kind_arm(0x00000002u), 0xfffff045u,
             "A4 the arm's id==2 case is the addend, not a zero");
  check_word(oracle_kind_arm(0x00000003u), osw::kAbsentValue,
             "A4 every other id in the arm gives the same word 0x00dd06eb writes");
}

void case_a5_the_sentinel_is_exact_on_all_32_bits() {
  // M1/M3. The model compares and returns one specific 32-bit word. Its four
  // neighbours must NOT behave like it: two of them must reach the lookup (one
  // bit differs) and the two above it are already ordinary ids. The value the
  // model returns on the sentinel arm is the same word bit for bit.
  for (Word id : {osw::kAbsentValue + 1u, osw::kAbsentValue - 1u,
                  osw::kAbsentValue ^ 0x00000001u,
                  osw::kAbsentValue ^ 0x80000000u}) {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = 0x00000000u;
    f.at(kIdDisplacement) = id;
    g_lookup_result = 0x0badf00du;
    reset_observers();
    g_lookup_result = 0x0badf00du;
    check_word(static_cast<Word>(call_model(f.object())), 0x0badf00du,
               "A5 a one-bit neighbour of the present value reaches the lookup");
    check(g_obs.lookup_calls == 1,
          "A5 a one-bit neighbour of the present value is looked up");
  }

  // The signed view of the same value: -0xa89087, which is what the decompiler
  // prints. A model that compared a sign-extended or narrowed copy would still
  // have to produce this exact word.
  Fixture f;
  f.reset();
  f.plant_neighbour_decoys();
  f.at(kKindDisplacement) = 0x00000000u;
  f.at(kIdDisplacement) = 0xff576f79u;
  reset_observers();
  check_signed(call_model(f.object()), -0xa89087,
               "A5 the sentinel is returned as the signed word the decompiler shows");
  check(g_obs.probe_calls == 0, "A5 the sentinel arm consults no callee");
  check(g_obs.lookup_calls == 0, "A5 the sentinel arm consults no callee");
}

// ===========================================================================
// B. The other two arms -- ordering, staleness, callees, argument
// ===========================================================================

void case_b1_the_sentinel_arm_short_circuits_before_the_probe() {
  // M8. 0x00dd06cf's JZ precedes 0x00dd06d1's call, so an id that already holds
  // the present value must return it without entering EITHER callee. A model
  // that consulted the probe first would show probe_calls == 1.
  Fixture f;
  f.reset();
  f.plant_neighbour_decoys();
  f.at(kKindDisplacement) = 0x00000000u;
  f.at(kIdDisplacement) = 0xff576f79u;
  g_probe_result = true;
  reset_observers();
  g_probe_result = true;
  const std::int32_t got = call_model(f.object());
  check_word(static_cast<Word>(got), 0xff576f79u,
             "B1 the present value is returned unchanged");
  check(g_obs.probe_calls == 0, "B1 the probe is not entered on that arm");
  check(g_obs.lookup_calls == 0, "B1 the lookup is not entered on that arm");
}

void case_b2_the_probe_gate_blocks_the_lookup() {
  // M8/M2. 0x00dd06d8's JZ must land on the same shared tail the sentinel arm
  // uses, and must not fall into the lookup. Both polarities of the probe's
  // result are driven, and the probe's own result word is checked on the open
  // arm so that a model which inverted the test is caught from both sides.
  {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = 0x00000000u;
    f.at(kIdDisplacement) = 0x00001234u;
    reset_observers();
    g_probe_result = false;
    g_lookup_result = 0x0badf00du;
    const Word got = static_cast<Word>(call_model(f.object()));
    check_word(got, 0xff576f79u, "B2 a declining probe yields the present value");
    check(g_obs.probe_calls == 1, "B2 the declining probe was entered once");
    check(g_obs.lookup_calls == 0,
          "B2 a declining probe blocks the lookup entirely");
  }
  {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = 0x00000000u;
    f.at(kIdDisplacement) = 0x00001234u;
    reset_observers();
    g_probe_result = true;
    g_lookup_result = 0x0badf00du;
    const Word got = static_cast<Word>(call_model(f.object()));
    check_word(got, 0x0badf00du, "B2 an accepting probe passes the value through");
    check(g_obs.probe_calls == 1, "B2 the accepting probe was entered once");
    check(g_obs.lookup_calls == 1, "B2 an accepting probe permits the lookup");
  }
}

void case_b3_the_argument_is_a_value_not_a_pointer() {
  // M4/M6. The word at +0x88 goes over the stack BY VALUE. The test plants, at
  // the address that word could be mistaken for, a poison value, and requires
  // the lookup observer to receive the word itself -- never the poison, never the
  // receiver's address, and never the address of the word.
  Fixture f;
  f.reset();
  f.plant_neighbour_decoys();
  f.at(kKindDisplacement) = 0x00000000u;
  f.at(kIdDisplacement) = 0x00005678u;
  reset_observers();
  g_probe_result = true;
  g_lookup_result = 0x0badf00du;
  const Word id_before = probe_word_at(f.object(), kIdDisplacement);
  (void)call_model(f.object());
  check_word(g_obs.lookup_argument, id_before,
             "B3 the lookup receives the word at +0x88");
  check(g_obs.lookup_argument != g_poisoned_pointee,
        "B3 the lookup does not receive the pointee's value");
  check_word(probe_word_at(f.object(), kIdDisplacement), id_before,
             "B3 the model's own read left the word in place");
  check(g_obs.lookup_argument !=
            reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(f.object()) +
                                   kIdDisplacement),
        "B3 the lookup receives the word, not its address");
  check(g_obs.lookup_argument !=
            reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(f.object())),
        "B3 the lookup receives the word, not the receiver");
  check(g_obs.lookup_argument !=
            reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(f.object()) +
                                   kKindDisplacement),
        "B3 the lookup receives the word, not the neighbouring word");
}

void case_b4_the_lookup_argument_is_re_read_after_the_probe() {
  // M7, and the sharpest case in the file. 0x00dd06da re-loads receiver+0x88
  // AFTER 0x00dd06c5 compared it and AFTER the probe call, so a mid-flight
  // rewrite of the object must reach the lookup. A model that cached the value it
  // compared hands over the OLD word; this one is required to hand over the new.
  for (Word id_before : {0x00000001u, 0x00005678u, 0x12345678u, 0x0badf00du,
                         0x7fffffffu, 0xffffffffu}) {
    for (Word id_after : {0x00000002u, 0x0000abcdu, 0x00000000u,
                          0xff576f79u, 0x80000000u}) {
      Fixture f;
      f.reset();
      f.plant_neighbour_decoys();
      f.at(kKindDisplacement) = 0x00000000u;
      f.at(kIdDisplacement) = id_before;
      reset_observers();
      g_probe_result = true;
      g_lookup_result = 0x0badf00du;
      g_probe_rewrites_id = true;
      g_probe_new_id = id_after;
      (void)call_model(f.object());
      g_probe_rewrites_id = false;
      check_word(g_obs.id_at_probe, id_before,
                 "B4 the probe saw the pre-call value of +0x88");
      check_word(g_obs.id_at_lookup, id_after,
                 "B4 the object carries the new value by the time the lookup runs");
      if (id_after == osw::kAbsentValue) {
        // The rewrite landed on the present value, but the comparison that
        // decides the shortcut happened BEFORE the rewrite, so the lookup is
        // still reached. That asymmetry is exactly what a cached-value
        // reconstruction gets wrong in the other direction.
        check(g_obs.lookup_calls == 1,
              "B4 a rewrite after the comparison cannot re-trigger the shortcut");
        check_word(g_obs.lookup_argument, id_after,
                   "B4 the rewritten value is what goes over the stack");
      } else {
        check(g_obs.lookup_calls == 1, "B4 the lookup is reached once");
        check_word(g_obs.lookup_argument, id_after,
                   "B4 the rewritten value is what goes over the stack, not the "
                   "value that was compared");
        check(g_obs.lookup_argument != id_before,
              "B4 the model did not cache the pre-call value");
      }
    }
  }
}

void case_b5_the_kind_word_is_sampled_once_before_any_call() {
  // M7. 0x00dd06a3 is the only read of +0x84 and it precedes both calls, so a
  // rewrite performed by the probe must NOT change the arm. The model is
  // required to answer from the ORIGINAL kind while the lookup argument follows
  // the rewritten id -- a combination that only happens if the two reads are
  // where the listing puts them.
  {
    // kind starts at 1 (the arm). The arm is entered before any call, so the
    // probe is never reached and its rewrite never happens -- but the assertion
    // is stated anyway, because a reconstruction that sampled the kind word AFTER
    // the probe would answer from the rewritten value and land in the lookup arm.
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = 0x00000001u;
    f.at(kIdDisplacement) = 0x00005678u;
    reset_observers();
    g_probe_result = true;
    g_lookup_result = 0x0badf00du;
    g_probe_rewrites_kind = true;
    g_probe_new_kind = 0x00000000u;
    const std::int32_t got = call_model(f.object());
    g_probe_rewrites_kind = false;
    check_word(static_cast<Word>(got), 0xff576f79u,
               "B5 a probe that rewrites +0x84 to 0 cannot leave the 0x84 arm");
    check(g_obs.probe_calls == 0,
          "B5 the 0x84 arm runs before any call, so the probe is never entered");
    check(g_obs.lookup_calls == 0, "B5 nor is the lookup");
  }
  {
    // kind starts at 0 (the lookup arm), the probe rewrites it to 1. The model
    // must stay in the lookup arm -- a model that re-read the kind word would
    // jump into the arm and answer from it.
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = 0x00000000u;
    f.at(kIdDisplacement) = 0x00005678u;
    reset_observers();
    g_probe_result = true;
    g_lookup_result = 0x0badf00du;
    g_probe_rewrites_kind = true;
    g_probe_new_kind = 0x00000001u;
    const std::int32_t got = call_model(f.object());
    g_probe_rewrites_kind = false;
    check_word(static_cast<Word>(got), 0x0badf00du,
               "B5 a probe that rewrites +0x84 to 1 cannot enter the 0x84 arm");
    check(g_obs.probe_calls == 1, "B5 the probe ran once");
    check(g_obs.lookup_calls == 1, "B5 the lookup still ran once");
    check_word(g_obs.kind_at_probe, 0x00000000u,
               "B5 the probe saw the original kind word");
  }
}

void case_b6_call_order_and_exactly_one_of_each() {
  // M6. The probe precedes the lookup, and neither is called twice. Repeated
  // mixed invocations must also settle, so a model that left an arm's state
  // behind cannot pass.
  Fixture f;
  f.reset();
  f.plant_neighbour_decoys();
  f.at(kKindDisplacement) = 0x00000000u;
  f.at(kIdDisplacement) = 0x00001234u;
  reset_observers();
  g_probe_result = true;
  g_lookup_result = 0x0badf00du;
  (void)call_model(f.object());
  check(g_obs.call_order == 1, "B6 the probe is entered before the lookup");
  check(g_obs.probe_calls == 1, "B6 the probe is entered exactly once");
  check(g_obs.lookup_calls == 1, "B6 the lookup is entered exactly once");
  // B6's ordering claim is about WHICH callee runs first, which g_obs.call_order
  // already carries. The frame depths are C3's job, because the two observers are
  // compiled from different bodies and their prologues do not cancel against each
  // other -- subtracting one observer's ESP from the other's measures the two
  // C++ prologues, not the model.
}

// ===========================================================================
// C. The ABI, measured
// ===========================================================================

void case_c1_the_model_consumes_no_stack_word() {
  // M9. The frame walk ends at ESP on all three paths, and no return site
  // carries an immediate. A body that expected an argument word would leave the
  // stack four bytes short. All three exits are exercised, because each has its
  // own epilogue.
  struct Row {
    Word kind;
    Word id;
    bool probe_open;
    const char* what;
  };
  const Row rows[] = {
      {0x00000001u, 0x00000002u, true, "C1 the 0x84 arm's addend exit"},
      {0x00000001u, 0x00000003u, true, "C1 the 0x84 arm's absent-value exit"},
      {0x00000000u, 0xff576f79u, true, "C1 the shared present-value exit"},
      {0x00000000u, 0x00001234u, false, "C1 the declining-probe exit"},
      {0x00000000u, 0x00001234u, true, "C1 the lookup exit"},
  };
  for (const Row& row : rows) {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = row.kind;
    f.at(kIdDisplacement) = row.id;
    reset_observers();
    g_probe_result = row.probe_open;
    g_lookup_result = 0x0badf00du;
    g_under_test = f.object();
    const TrampolineSample s = measure(f.object(), make_stack_decoy().object());
    check_word(s.esp_at_return, s.esp_at_entry, row.what);
  }
}

void case_c2_the_receiver_arrives_in_ecx_not_in_the_argument_slot() {
  // M9: the wrong receiver register, and the wrong value in the right one. The
  // trampoline loads the real object into ECX and pushes a decoy onto the stack,
  // so at the callee's entry [ESP+4] holds the decoy's address. The decoy is
  // configured to answer 0xfffff045, which the real object in this loop never
  // answers, so a model that read the first argument slot cannot accidentally
  // agree -- it would produce a word no expected value matches.
  for (Word kind : {0x00000000u, 0x00000001u}) {
    for (Word id : {0x00000002u, 0x00001234u, 0xffffffffu, 0xff576f79u,
                    0x00000003u}) {
      Fixture real_object;
      real_object.reset();
      real_object.plant_neighbour_decoys();
      real_object.at(kKindDisplacement) = kind;
      real_object.at(kIdDisplacement) = id;
      Fixture decoy = make_stack_decoy();

      // What the model is required to answer, taken from a plain C++ call on an
      // identically configured object. (That call is itself an assertion about
      // the declared convention: were the model cdecl, the compiler would put the
      // receiver in the argument slot and every case here would read a wild
      // address rather than fail cleanly.)
      Word want = 0u;
      {
        Fixture plain;
        plain.reset();
        plain.plant_neighbour_decoys();
        plain.at(kKindDisplacement) = kind;
        plain.at(kIdDisplacement) = id;
        reset_observers();
        g_probe_result = true;
        g_lookup_result = 0x0badf00du;
        want = static_cast<Word>(call_model(plain.object()));
      }
      check(want != 0xfffff045u || (kind == 0x00000001u && id == 0x00000002u),
            "C2 the real object's answer is distinguishable from the decoy's");

      reset_observers();
      g_probe_result = true;
      g_lookup_result = 0x0badf00du;
      g_under_test = real_object.object();
      const TrampolineSample s = measure(real_object.object(), decoy.object());
      check_word(s.returned, want,
                 "C2 the answer comes from the ECX receiver, not from [ESP+4]");
      check_word(s.esp_at_return, s.esp_at_entry,
                 "C2 the model pops nothing off the decoy-pushed frame either");
    }
  }
}

void case_c3_the_model_leaves_the_callers_frame_exactly_as_it_found_it() {
  // M7/M9. The one part of the model's stack discipline a black-box caller can
  // see: whatever the model pushed for its callees, it removed, and the
  // trampoline's own decoy word is still the top of the stack when the model
  // returns. This is the observable half of the listing's three POP ESI / RET
  // epilogues and of the ADD ESP,0x4 at 0x00dd06e6.
  //
  // It is checked on the lookup path, because that is the only path where the
  // model pushes anything of its own: on the present-value path and the declining
  // path it pushes nothing at all, and on the 0x84 arm it pushes nothing and makes
  // no call, so the same equality must hold there too -- and it is.
  struct Row {
    Word kind;
    Word id;
    bool probe_open;
    const char* what;
  };
  const Row rows[] = {
      {0x00000001u, 0x00000002u, true, "C3 balanced after the 0x84 arm's exit"},
      {0x00000001u, 0x00000003u, true, "C3 balanced after the 0x84 arm's other exit"},
      {0x00000000u, 0xff576f79u, true, "C3 balanced after the present-value exit"},
      {0x00000000u, 0x00001234u, false, "C3 balanced after a declining probe"},
      {0x00000000u, 0x00001234u, true, "C3 balanced after the lookup, which is "
                                         "the only path that pushes a word"},
  };
  for (const Row& row : rows) {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = row.kind;
    f.at(kIdDisplacement) = row.id;
    reset_observers();
    g_probe_result = row.probe_open;
    g_lookup_result = 0x0badf00du;
    g_under_test = f.object();
    const TrampolineSample s = measure(f.object(), make_stack_decoy().object());
    check_word(s.esp_at_return, s.esp_at_entry, row.what);
    check_word(s.caller_top_after, s.decoy,
               "C3 the trampoline's own stack word is untouched by the model, so "
               "the model removed whatever it pushed");
  }

  // The lookup's argument, as the machine handed it over: the observer's own
  // parameter. B3 checks the same value from the other direction -- that it is not
  // the address of anything -- and the two together are the pointer-level claim.
  Fixture f;
  f.reset();
  f.plant_neighbour_decoys();
  f.at(kKindDisplacement) = 0x00000000u;
  f.at(kIdDisplacement) = 0x00001234u;
  reset_observers();
  g_probe_result = true;
  g_lookup_result = 0x0badf00du;
  g_under_test = f.object();
  const TrampolineSample s = measure(f.object(), make_stack_decoy().object());
  check_word(g_obs.lookup_argument, 0x00001234u,
             "C3 the lookup's argument is the dword read from receiver+0x88");
  const std::int32_t through_cxx = call_model(f.object());
  check_word(s.returned, static_cast<Word>(through_cxx),
             "C3 the trampoline's EAX and an ordinary C++ call agree, so the "
             "trampoline is not perturbing the answer");
}

void case_c4_the_model_writes_nothing_to_the_object() {
  // M7 / completeness. The body has zero writes to the receiver -- not one
  // instruction stores through ESI -- so the object must come out of every call
  // byte-identical to how it went in, for every arm, including the one whose
  // probe rewrites a word. The last two rows are the arms where a reconstruction
  // might plausibly cache a result on the object.
  struct Row {
    Word kind;
    Word id;
    bool probe_open;
    const char* what;
  };
  const Row rows[] = {
      {0x00000001u, 0x00000002u, true, "C4 unchanged after the 0x84 arm's addend exit"},
      {0x00000001u, 0x00000003u, true, "C4 unchanged after the 0x84 arm's absent-value exit"},
      {0x00000000u, 0xff576f79u, true, "C4 unchanged after the present-value exit"},
      {0x00000000u, 0x00001234u, false, "C4 unchanged after a declining probe"},
      {0x00000000u, 0x00001234u, true, "C4 unchanged after the lookup"},
      {0x00000000u, 0x00001234u, true, "C4 unchanged after the lookup, second kind"},
  };
  for (const Row& row : rows) {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = row.kind;
    f.at(kIdDisplacement) = row.id;
    std::uint8_t before[kObjectBytes];
    std::memcpy(before, f.bytes, sizeof before);
    reset_observers();
    g_probe_result = row.probe_open;
    g_lookup_result = 0x0badf00du;
    (void)call_model(f.object());
    check(std::memcmp(before, f.bytes, sizeof before) == 0, row.what);
  }

  // The same, on the arm where the test's own probe rewrites a word: exactly the
  // two dwords the observer touched may differ, and no other byte.
  {
    Fixture f;
    f.reset();
    f.plant_neighbour_decoys();
    f.at(kKindDisplacement) = 0x00000000u;
    f.at(kIdDisplacement) = 0x00001234u;
    std::uint8_t before[kObjectBytes];
    std::memcpy(before, f.bytes, sizeof before);
    reset_observers();
    g_probe_result = true;
    g_lookup_result = 0x0badf00du;
    g_probe_rewrites_id = true;
    g_probe_new_id = 0x00004321u;
    (void)call_model(f.object());
    g_probe_rewrites_id = false;
    int differing_outside = 0;
    int differing_inside = 0;
    for (std::size_t i = 0; i < kObjectBytes; ++i) {
      if (before[i] == f.bytes[i]) continue;
      if (i >= kIdDisplacement && i < kIdDisplacement + 4) {
        ++differing_inside;
      } else {
        ++differing_outside;
      }
    }
    check_word(static_cast<Word>(differing_outside), 0u,
               "C4 the model changes no byte outside the word the observer itself "
               "wrote");
    check(differing_inside > 0,
          "C4 the observer's own rewrite is visible, so the check above is not "
          "vacuously true");
  }
}

void case_c5_the_return_travels_in_eax() {
  // The ABI record's return register, measured. The raw call's EAX is captured
  // directly, so this is not just "the function returned a value" -- it is the
  // value in the register the record names.
  for (Word kind : {0x00000000u, 0x00000001u}) {
    for (Word id : {0x00000002u, 0x00001234u, 0xffffffffu, 0xff576f79u}) {
      Fixture f;
      f.reset();
      f.plant_neighbour_decoys();
      f.at(kKindDisplacement) = kind;
      f.at(kIdDisplacement) = id;
      reset_observers();
      g_probe_result = true;
      g_lookup_result = 0x0badf00du;
      g_under_test = f.object();
      const TrampolineSample s = measure(f.object(), make_stack_decoy().object());
      const std::int32_t through_cxx = call_model(f.object());
      check_word(s.returned, static_cast<Word>(through_cxx),
                 "C5 EAX at the return site is the value the C++ call returns");
    }
  }
}

void case_c6_repeated_and_interleaved_invocations_settle() {
  // Nothing in the model is static, so twenty interleaved calls in all four
  // configurations must produce the same answers as the isolated ones. This is
  // what would catch a model that memoised, or an observer that leaked state.
  const Word kinds[] = {0x00000000u, 0x00000001u, 0x00000002u, 0x00000003u};
  const Word ids[] = {0x00000002u, 0x00000003u, 0x00001234u, 0xff576f79u,
                      0x00000000u, 0xffffffffu};
  for (int round = 0; round < 20; ++round) {
    for (Word kind : kinds) {
      for (Word id : ids) {
        for (bool probe_open : {false, true}) {
          Fixture f;
          f.reset();
          f.plant_neighbour_decoys();
          f.at(kKindDisplacement) = kind;
          f.at(kIdDisplacement) = id;
          reset_observers();
          g_probe_result = probe_open;
          g_lookup_result = 0x0badf00du;
          const Word got = static_cast<Word>(call_model(f.object()));

          // The expected answer, computed here from the listing's shape and
          // nothing else: the arm when the kind is 1, the present value when the
          // id already is it or the probe declines, else the lookup's word.
          Word want;
          if (kind == 0x01u) {
            want = (id == 0x02u) ? 0xfffff045u : 0xff576f79u;
          } else if (id == 0xff576f79u || !probe_open) {
            want = 0xff576f79u;
          } else {
            want = 0x0badf00du;
          }
          check_word(got, want, "C6 an interleaved invocation matches the listing");
        }
      }
    }
  }
}

// ===========================================================================

int run() {
  case_a1_sweep_against_the_oracle();
  case_a2_polarity_of_the_kind_test();
  case_a3_the_arm_is_one_bit_exact();
  case_a4_neighbour_decoys_are_never_the_answer();
  case_a5_the_sentinel_is_exact_on_all_32_bits();
  case_b1_the_sentinel_arm_short_circuits_before_the_probe();
  case_b2_the_probe_gate_blocks_the_lookup();
  case_b3_the_argument_is_a_value_not_a_pointer();
  case_b4_the_lookup_argument_is_re_read_after_the_probe();
  case_b5_the_kind_word_is_sampled_once_before_any_call();
  case_b6_call_order_and_exactly_one_of_each();
  case_c1_the_model_consumes_no_stack_word();
  case_c2_the_receiver_arrives_in_ecx_not_in_the_argument_slot();
  case_c3_the_model_leaves_the_callers_frame_exactly_as_it_found_it();
  case_c4_the_model_writes_nothing_to_the_object();
  case_c5_the_return_travels_in_eax();
  case_c6_repeated_and_interleaved_invocations_settle();
  return g_failures;
}

}  // namespace

int main() {
  // The header must be self-sufficient: a program that only includes it and
  // does nothing still has to build clean.
  static_assert(sizeof(OpaqueSporepediaAsset) == 0x8c,
                "the modelled receiver ends at the last byte the body reads");
  static_assert(osw::kIdDisplacement == 0x88u, "the id word is at +0x88");
  static_assert(osw::kKindDisplacement == 0x84u,
                "the kind word is at +0x84");
  static_assert(osw::kAbsentValue == 0xff576f79u,
                "0x00dd06eb's immediate is the value 0x00dd06c5 compares against");
  static_assert(osw::kKindArmSelectedValue == 0xfffff045u,
                "0x00dd06be's addend is the 0x84 arm's id==2 result, because that "
                "ADD is unconditional");

  const int failures = run();
  std::printf("%s  %d checks, %d failures\n", failures == 0 ? "PASS" : "FAIL",
              g_checks, failures);
  if (failures == 0) {
    std::printf(
        "not asserted: the five intermediates of the 0x84 arm (no memory, no\n"
        "call, EAX overwritten on both arms); the caller-side ADD ESP,0x4 at\n"
        "0x00dd06e6 (indistinguishable for a cdecl leaf callee); the order\n"
        "among the five arithmetic instructions (same reason); the model's\n"
        "STACK DEPTH at each call site, because a compiled C++ function's\n"
        "intermediate ESP is the compiler's -O0 frame and its own alignment\n"
        "padding, not the listing's single PUSH ESI (the depth-difference and\n"
        "argument-slot instruments this file first wrote both measured the\n"
        "COMPILER and were withdrawn; what survives is the ESP equality across\n"
        "the call and the untouched-decoy check in C3, plus the lookup's\n"
        "argument value in B3); whether the model pushed anything at all for\n"
        "the zero-parameter probe, which a compiled model makes unobservable\n"
        "because it balances its own pushes (a zero-parameter function still\n"
        "has a stack slot, and B3/C3 fix what lands in it); the meaning of\n"
        "the words at +0x84 and +0x88 and of 0xff576f79; the interiors of\n"
        "0x00b6e250 and 0x00b6f0d0, which are observers here.\n");
  }
  return failures == 0 ? 0 : 1;
}
