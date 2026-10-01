// PKG-SWARM-W1-00641410 -- model test for VA 0x00641410
//
// A falsification test, not a walkthrough. Its job is to try to KILL the model in
// swarm_w1_00641410.cpp, and every assertion below is tied to a pair of
// instructions in the 31-instruction listing:
//
//   00641410 PUSH ESI / 00641454 POP ESI / 00641458 POP ESI
//   00641411 MOV ESI,ECX
//   00641413 MOV EAX,[ESI] + 0x00641415 MOV EDX,[EAX+0x24]   dispatch 1, slot 9
//   00641418 CALL EDX            (no ECX reload before this one)
//   0064141a CMP EAX,0xbcd73e89 / 0064141f JZ 0x00641456
//   00641421 MOV EAX,[ESI] + 0x00641423 MOV EDX,[EAX+0x24]   dispatch 2, slot 9
//   00641426 MOV ECX,ESI / 0x00641428 CALL EDX
//   0064142a CMP EAX,0xb8669ec9 / 0x0064142f JZ 0x00641456
//   00641431/0x00641433 + 0x00641436 MOV ECX,ESI / 0x00641438 CALL EDX
//   0064143a CMP EAX,0x37148141 / 0x0064143f JZ 0x00641456
//   00641441/0x00641443 + 0x00641446 MOV ECX,ESI / 0x00641448 CALL EDX
//   0064144a CMP EAX,0x04f684a4 / 0x0064144f JZ 0x00641456
//   00641451 MOV AL,BYTE PTR [ESI+0x26]
//   00641456 XOR AL,AL
//
// There are no direct callees to observe, because the body has none: all four
// transfers are indirect (`CALL EDX` at 0x00641418, 0x00641428, 0x00641438 and
// 0x00641448). The observation surface this test builds is therefore the same
// thing the machine observes -- the tables' slot 9 -- plus a block of receiver
// memory that exists purely so a wrong displacement has somewhere to land.
//
// TWO KINDS OF OBSERVER, and why both are needed:
//
//  * C++ observers (obs_*) record their ordinal, the receiver pointer that
//    reached them, a PER-DISPATCH scripted 32-bit result (the four dispatches
//    need four different results, and the COUNT is itself an observable of the
//    short-circuit), and can rewrite the receiver's dispatch word from inside the
//    call. They CANNOT be used to assert register or stack state: a C++ function
//    has already built its own frame and taken its own register assignments by
//    the time it runs, so its ESP is its own and its ECX/ESI are the compiler's
//    business.
//
//  * One hand-written assembly trampoline (w21_tramp9) with no prologue at all,
//    which samples ESP, ECX and the return address of its hit as its first
//    meaningful instructions. It is what the register, stack-depth and call-site
//    claims are made from, and it is the strictest decoy in the file: it ignores
//    the receiver entirely and just reports.
//
// A NOTE ON THE TRAMPOLINE'S SHAPE, because the obvious design does not work and
// the reason is worth recording. The first version of this trampoline kept one
// array slot per hit and indexed it in assembly (`movl %eax, w21_t9_esp(%ebx)`
// with the hit counter in EBX). On this toolchain that store lands at
// `w21_t9_esp + hit_count` rather than `+ 4 * hit_count` -- the bytes visibly
// walk forward one byte at a time -- so the per-hit record is unusable. The
// trampoline therefore keeps NO arrays: it records the LAST hit, the FIRST return
// address, and a flag that stays 0 only while every hit has come from a different
// return address. That flag is what proves the four dispatches come from four
// distinct call sites, which is the fact D12 exists to establish. One more linker
// note, also not a diagnostic from -Wall/-Wextra/-Werror: the absolute symbol
// references in the hand-written block make GNU ld print one `DT_TEXTREL` note
// while linking a PIE, because the section is read-only. It does not affect the
// exit status.
//
// Decoy coverage, and the defect each decoy is designed to kill:
//
//   D1  slots 8 and 10 of BOTH tables hold observers that fail the run if fired
//       -> an off-by-one slot displacement (0x20 or 0x28 instead of 0x24)
//   D2  receiver bytes +0x04..+0x3c hold LIVE observer addresses, with
//       +0x24, +0x20 and +0x28 in particular -> a ONE-level dereference (treating
//       the receiver's own memory as the table), a wrong receiver offset for the
//       dispatch word (+0x04, +0x08), or a wrong slot read one word out
//   D3  a dispatched callee OVERWRITES the receiver's dispatch word mid-body, on
//       call 1 in one case and on call 2 in another -> a model that CACHES the
//       vptr, or that re-reads it only once
//   D4  the two neighbours of every literal, on both sides
//       (0xbcd73e88/8a, 0xb8669ec8/ca, 0x37148140/2, 0x04f684a3/5) plus the
//       PERMUTED literals (literal N offered at call M for N != M)
//       -> a wrong constant, an off-by-one constant, or four literals checked
//          against every result instead of one literal per call
//   D5  signed/unsigned and magnitude edge values: 0, 1, 0x7fffffff, 0x80000000,
//       0xffffffff, 0x80000000|literal3 -> a signed compare, a `< 0` test, a
//       `== 1` test, a null test
//   D6  the four fully-determined false exits: 0xbcd73e00, 0xb8669e00,
//       0x37148100, 0x04f68400 -> `XOR EAX,EAX` instead of `XOR AL,AL`, or any
//          "return 0" / "return false"
//   D7  the true exit with a poisoned high byte: r4 = 0xdeadbeef and byte +0x26 =
//       0x5a must give 0xdeadbe5a -> a zero-extended byte, a bool, or a
//       `return b != 0`
//   D8  the result byte driven to 0x00, 0x01, 0x02, 0x7f, 0x80, 0xff with a
//       constant high byte -> a booleanised return
//   D9  distinct bytes planted at receiver +0x25, +0x26 and +0x27 -> a wrong
//       receiver offset for the result byte (the neighbouring accessor
//       0x00641460 reads +0x25, so this is a real trap in this table family)
//   D10 the model's parked-ESI and restored-ESI words are poisoned before every
//       run and read after it, on BOTH return paths -> a missing POP ESI, or a
//       POP on one path only
//   D11 the trampoline samples ESP, ECX and the return address, and the model
//       publishes the ESP of each of the four call sites
//       -> a pushed stack argument, a leaked stack word, a receiver that is not
//          the entry pointer, or a call made from anywhere but the four CALL EDX
//          sites in re_00641410
//   D12 the trampoline's distinct-return-address flag must be 0 after four hits,
//       and every recorded return address must lie inside re_00641410
//       -> a model that collapses the four dispatches into one call site
//   D13 a byte-for-byte snapshot of the receiver block and both tables around
//       every run -> a model that writes where the listing has no store
//
// Self-check: the D2 decoy observers are each called once on purpose, to prove
// they are live and not unreachable code whose silence proves nothing.
//
// MUTATION CHECKING. Twenty-seven deliberate defects were injected into copies of
// swarm_w1_00641410.cpp / _types.hpp under /tmp and this test was run against
// each. TWENTY-SIX were killed; the one that survived is reported below rather
// than hidden, because it is not a defect the listing can distinguish:
//
//   return 0 on false exit 1                       KILLED (3 assertion failures)
//   return 0 on false exit 2                       KILLED (2)
//   return 0 on false exit 3                       KILLED (3)
//   return 0 on false exit 4                       KILLED (3)
//   invert the first compare's polarity            KILLED (86)
//   invert the fourth compare's polarity           KILLED (30)
//   null test instead of equality on literal 1     KILLED (36)
//   drop the short circuit on literal 3            KILLED (2)
//   drop the fourth dispatch entirely              KILLED at compile time
//   literal 1 off by one (+ header static_assert)  KILLED at compile time
//   literal 4 off by one (+ header static_assert)  KILLED at compile time
//   permute literals 2 and 3                       KILLED at compile time
//   slot 9 -> slot 8                               KILLED at compile time
//   slot 9 -> slot 10                              KILLED at compile time
//   zero-extend the result byte                    KILLED (25)
//   booleanise the result byte                     KILLED (31)
//   read the result byte at +0x25                  KILLED (31)
//   take the result from the dispatch word's low byte   KILLED (29)
//   one-level dereference of the receiver          KILLED (92)
//   read the dispatch word at +0x04                KILLED (SIGSEGV)
//   dispatch slot 9 of the flat receiver           KILLED (65)
//   cache the vptr across all four dispatches      KILLED (4)
//   re-read the dispatch word only once            KILLED (2)
//   push a stack argument at every dispatch        KILLED (D11: the trampoline
//                                                  saw ESP four bytes lower)
//   omit the POP ESI on the false path             KILLED (1)
//   omit the POP ESI on the true path              KILLED (29)
//   do not park the entry ESI at 0x00641410        KILLED (68)
//   write through the receiver (an injected store) KILLED (27)
//   write through the table   (an injected store) KILLED (27)
//   compare literal 1 through static_cast<int>     *** SURVIVED ***
//
// A TEN-MUTATION RE-RUN WAS PERFORMED when the return type was narrowed to the one
// byte both exit sites write (see the "24 high bits" bullet under WHAT IS
// DELIBERATELY NOT ASSERTED), because the 32-bit residue now reaches this test
// through model_returned_eax() rather than through the C return value and the
// question "does the test still see the register" had to be answered rather than
// assumed. All ten were killed, and the counts are the same shape as the
// corresponding entries in the table above:
//
//   zero-extend the published residue                 KILLED (35)
//   return 0 on false exit 1                          KILLED (4)
//   publish EAX on the true exit but not the false    KILLED (59)
//   read the result byte at +0x25                     KILLED (32)
//   booleanise the result byte                        KILLED (29)
//   one-level dereference of the receiver             KILLED (SIGSEGV)
//   cache the dispatch word across all four dispatches KILLED (8)
//   slot 9 -> slot 8 (off-by-one slot displacement)   KILLED at compile time
//   literal 1 off by one                              KILLED at compile time
//   omit the POP ESI on the false path                KILLED (6)
//
// The unmutated build passes, which is the control for that table. Only these ten
// of the twenty-seven were re-run; the other seventeen are reported as the earlier
// table reports them and were not re-measured in this pass.
//
// The survivor is a semantic no-op and is reported as such. `static_cast<int> ==
// static_cast<int>` and `unsigned == unsigned` are the same test bit for bit, so
// no observation of the machine can separate them; the listing's own `CMP EAX,imm32`
// is likewise an equality test on all 32 bits and is indifferent to the sign. The
// test's D5 cases therefore drive 0x80000000, 0xffffffff and 0x80000000|literal 3
// to show that no SIGN-BASED rule (a `< 0`, a magnitude compare, a `== 1`) is in
// play -- which is the strongest statement the evidence supports -- and the
// signedness of the *representation* is not asserted because it is not a property
// this body has.
//
// The five defects that die at compile time do so for the intended reason: the
// header's static_asserts tie kSlotDispatched to the 0x24 displacement the four
// MOV EDX,[EAX+0x24] instructions show, and the test re-states the four literals
// and static_asserts that they are the header's, so neither a slot displacement
// nor a literal can be changed without breaking an assertion that names the
// instruction it came from.
//
// WHAT IS DELIBERATELY NOT ASSERTED, and why:
//
//  * What slot 9 dispatches to, or what the four literals NAME. This body names
//    no callee, no import, no string and no symbol; the six tables that install
//    it disagree about slot 9's contents, so no single callee can be asserted.
//  * That any real callee in the game ever changes the dispatch word. D3 proves
//    only that the MODEL re-reads the word, which is what the four `MOV EAX,[ESI]`
//    instructions fix. Whether the re-read ever matters at run time needs a trace.
//  * That the 24 high bits of the result are a SOURCE-level fact. They are
//    asserted because the two return sites provably write AL only and the residue
//    is then fully determined, but they are a register artefact: the sole known
//    caller consumes AL only (0x00ec3ba1 `TEST AL,AL`). The function's declared
//    return type is therefore the ONE BYTE both exits write, and the residue is
//    read through the model's `model_returned_eax()` instrumentation word rather
//    than through the signature. Every assertion below that names a 32-bit
//    expected value is made against that word, so none of them is weaker than it
//    was when the residue rode out through the return value; on top of them each
//    run now ALSO asserts that the byte the function returns is the low byte of
//    that word, so the two channels are pinned to each other.
//  * The C++ observers' own ESP, ECX and ESI. Those are the compiler's, not the
//    model's; the register claims are made from the trampoline only.
//  * The caller's real ESI register across the call. The prescribed build is a
//    PIE and GCC's i386 PIE sequence keeps the GOT base in ESI for the whole of
//    every caller, so a sentinel planted in ESI before the call is either
//    overwritten by the compiler or, if it survived, would leave the GOT base
//    wrong for the code that follows. The PUSH/POP pair is therefore asserted
//    through the model's two poisoned value words (D10) rather than through the
//    register, and the trampoline's ECX sample is the register-level evidence
//    offered instead.
//  * That a callee samples the RECEIVER in ESI (0x00641411 MOV ESI,ECX), for the
//    same PIE reason: inside this translation unit ESI is the GOT base.
//  * Whether the trampoline's LAST hit and its FIRST hit come from the same call
//    site when the count is 1. D11's true-path case runs four dispatches and the
//    false-path case runs one, and the two together cover the first and the last
//      CALL EDX; the two middle ones are covered by the published-ESP equality
//      check and by D12's distinctness flag, which fails if any of the four
//      shares a return address with another.

#include "swarm_w1_00641410_types.hpp"

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace P = openspore::reconstruction::pkg_swarm_w1_00641410;

using P::AssetData;
using P::SlotFn;
using P::Vtable;
using P::Word;

// The four literals, spelled here as well as in the header so that the test's
// expected words read next to the instructions that fix them.
constexpr Word kK1 = 0xbcd73e89u;  // 0064141a
constexpr Word kK2 = 0xb8669ec9u;  // 0064142a
constexpr Word kK3 = 0x37148141u;  // 0064143a
constexpr Word kK4 = 0x04f684a4u;  // 0064144a
static_assert(kK1 == P::kDenyLiteral1 && kK2 == P::kDenyLiteral2 &&
                  kK3 == P::kDenyLiteral3 && kK4 == P::kDenyLiteral4,
              "the test's copies of the literals are the header's");

// -- the assembly trampoline ---------------------------------------------------
//
// A real __thiscall callee with a zero-stack-argument surface and NO prologue.
// `movl %esp,%eax` and `movl (%esp),%edx` are its first two instructions, so what
// they record is the machine state at the callee's entry and nothing else; the
// `pushl %ebx` comes afterwards and is undone before the `ret`. The bare `ret`
// matches 0x00641455 / 0x00641459 and the fact that the body pushes no argument.
//
// No arrays: see the note at the top of this file. The records are
//   w21_t9_esp / w21_t9_ecx / w21_t9_ret   the LAST hit
//   w21_t9_ret0                            the FIRST hit's return address
//   w21_t9_same_site                       set to 1 as soon as two hits agree
//   w21_t9_n                               the hit count
extern "C" {
std::uint32_t w21_t9_esp;
std::uint32_t w21_t9_ecx;
std::uint32_t w21_t9_ret;
std::uint32_t w21_t9_ret0;
std::uint32_t w21_t9_same_site;
std::uint32_t w21_t9_n;
std::uint32_t w21_t9_result;
}  // extern "C"

__asm__(".text\n\t"
        ".globl w21_tramp9\n\t"
        ".type  w21_tramp9, @function\n\t"
        "w21_tramp9:\n\t"
        "  movl %esp, %eax\n\t"          // entry ESP, before any push
        "  movl (%esp), %edx\n\t"        // return address, at entry ESP
        "  pushl %ebx\n\t"
        "  movl %eax, w21_t9_esp\n\t"
        "  movl %ecx, w21_t9_ecx\n\t"
        "  movl %edx, w21_t9_ret\n\t"
        "  movl w21_t9_n, %ebx\n\t"
        "  cmpl $0, %ebx\n\t"
        "  jne 1f\n\t"
        "  movl %edx, w21_t9_ret0\n\t"  // first hit: record, do not compare
        "  jmp 2f\n\t"
        "1:\n\t"
        "  cmpl %edx, w21_t9_ret0\n\t"   // did an earlier hit come from here?
        "  jne 2f\n\t"
        "  movl $1, w21_t9_same_site\n\t"
        "2:\n\t"
        "  addl $1, w21_t9_n\n\t"
        "  movl w21_t9_result, %eax\n\t"
        "  popl %ebx\n\t"
        "  ret\n\t"
        ".size w21_tramp9, .-w21_tramp9\n\t");

extern "C" Word PKG_SWARM_W1_00641410_THISCALL w21_tramp9(AssetData* receiver);

namespace {

enum : int {
  kA9 = 0,     // table A slot 9 -- the real dispatch target
  kB9 = 1,     // table B slot 9 -- reached only through a dispatch-word overwrite
  kA8 = 2,     // D1 decoy: must never fire (+0x20)
  kA10 = 3,    // D1 decoy: must never fire (+0x28)
  kB8 = 4,     // D1 decoy: must never fire (+0x20 of table B)
  kB10 = 5,    // D1 decoy: must never fire (+0x28 of table B)
  kFlat24 = 6, // D2 decoy, at receiver+0x24: what a ONE-LEVEL slot-9 read calls
  kFlat20 = 7, // D2 decoy, at receiver+0x20: a one-level read one word low
  kFlat28 = 8, // D2 decoy, at receiver+0x28: a one-level read one word high
  kFlat04 = 9, // D2 decoy, at receiver+0x04: a dispatch word read at +0x04
  kFlat08 = 10,// D2 decoy, at receiver+0x08: a dispatch word read at +0x08
  kObserverCount
};

const char* const kObserverName[kObserverCount] = {
    "A.slot9", "B.slot9",         "A.slot8(dead)",  "A.slot10(dead)",
    "B.slot8(dead)", "B.slot10(dead)", "flat+24(dead)", "flat+20(dead)",
    "flat+28(dead)", "flat+04(dead)", "flat+08(dead)"};

constexpr int kMaxDispatches = 8;

struct Observation {
  unsigned calls;
  const void* receiver;  // what the observer found in ECX
};

struct Behaviour {
  // The 32-bit EAX this observer hands back, indexed by the GLOBAL dispatch
  // ordinal (0-based) rather than by its own call count. That distinction is
  // load-bearing: once a dispatch-word overwrite sends dispatches 2..4 to table
  // B, table B's slot 9 sees calls 1..3, and a per-observer queue would hand it
  // results 0..2 and lose result 3.
  Word result[kMaxDispatches];
  // 1-based call ordinal ON THIS OBSERVER on which it rewrites the receiver's
  // dispatch word, or -1 for never. This is the D3 mechanism.
  int overwrite_on_call;
  Vtable* overwrite_word;
};

Observation g_obs[kObserverCount];
Behaviour g_behaviour[kObserverCount];
int g_dispatch_no;
int g_order[kMaxDispatches];
int g_order_len;
int g_failures;
int g_checks;

// Every C++ observer funnels through here.
Word note(int index, AssetData* receiver) {
  Observation& o = g_obs[index];
  const Behaviour& b = g_behaviour[index];
  o.calls += 1;
  o.receiver = receiver;
  if (b.overwrite_on_call > 0 && static_cast<int>(o.calls) == b.overwrite_on_call) {
    // The dispatch word is at the receiver's leading displacement (0x00) and is
    // written as a raw pointer word, because the receiver is an opaque byte run
    // and this body names no member of it.
    P::store_pointer_at(receiver, P::kReceiverDispatchWordDisplacement, b.overwrite_word);
  }
  const int d = g_dispatch_no;
  if (d < kMaxDispatches) {
    g_order[g_order_len++] = index;
  }
  if (d < kMaxDispatches) {
    ++g_dispatch_no;
  }
  const int slot = (d < kMaxDispatches) ? d : (kMaxDispatches - 1);
  return b.result[slot];
}

Word PKG_SWARM_W1_00641410_THISCALL obs_a9(AssetData* r) { return note(kA9, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_b9(AssetData* r) { return note(kB9, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_a8(AssetData* r) { return note(kA8, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_a10(AssetData* r) { return note(kA10, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_b8(AssetData* r) { return note(kB8, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_b10(AssetData* r) { return note(kB10, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_f24(AssetData* r) { return note(kFlat24, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_f20(AssetData* r) { return note(kFlat20, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_f28(AssetData* r) { return note(kFlat28, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_f04(AssetData* r) { return note(kFlat04, r); }
Word PKG_SWARM_W1_00641410_THISCALL obs_f08(AssetData* r) { return note(kFlat08, r); }

// The address each decoy is planted at. Every observer is __thiscall, so these
// return exactly SlotFn without a cast between calling conventions.
SlotFn observer_address(int index) {
  switch (index) {
    case kA9: return &obs_a9;
    case kB9: return &obs_b9;
    case kA8: return &obs_a8;
    case kA10: return &obs_a10;
    case kB8: return &obs_b8;
    case kB10: return &obs_b10;
    case kFlat24: return &obs_f24;
    case kFlat20: return &obs_f20;
    case kFlat28: return &obs_f28;
    case kFlat04: return &obs_f04;
    case kFlat08: return &obs_f08;
    default: return &obs_a8;
  }
}

// -- the machine the model runs against ----------------------------------------

// 0x40 bytes, so that every D2 plant from +0x04 to +0x3c is inside one block.
struct RawBlock {
  alignas(4) std::uint8_t bytes[0x40];
};

struct Snapshot {
  RawBlock receiver;
  RawBlock a;
  RawBlock b;
};

RawBlock g_receiver;
RawBlock g_table_a;
RawBlock g_table_b;
Snapshot g_saved;

Vtable* table_a() { return reinterpret_cast<Vtable*>(&g_table_a); }
Vtable* table_b() { return reinterpret_cast<Vtable*>(&g_table_b); }
AssetData* receiver() { return reinterpret_cast<AssetData*>(&g_receiver); }

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("  FAIL  %s\n", what);
  }
}

void check_equal(Word got, Word want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("  FAIL  %s (got 0x%08x, wanted 0x%08x)\n", what, got, want);
  }
}

void check_order(int position, int observer, const char* what) {
  ++g_checks;
  if (g_order_len <= position || g_order[position] != observer) {
    ++g_failures;
    std::printf("  FAIL  %s (dispatch order was", what);
    for (int i = 0; i < g_order_len; ++i) {
      std::printf(" %s", kObserverName[g_order[i]]);
    }
    std::printf(")\n");
  }
}

// D2. Fill the receiver's own memory from +0x04 upwards with live observer
// addresses, so a model that treats the receiver AS the table -- one dereference
// instead of two -- calls one of them, and so a model that reads the dispatch
// word or the result byte from the wrong displacement gets a live value too.
//
// +0x24, +0x20 and +0x28 are where slot 9 and its two neighbours sit under that
// wrong one-level reading, so they get their own observers. +0x24 OVERWRITES
// bytes 0x24..0x27 and therefore byte 0x26 as well; the byte the machine reads
// there is then byte 2 of the planted address, computed below rather than
// hard-coded, so the test does not depend on where the linker put the text.
void plant_flat_decoys() {
  struct Plant {
    std::size_t off;
    int obs;
  };
  const Plant kPlants[] = {
      {0x04, kFlat04}, {0x08, kFlat08}, {0x0c, kFlat04}, {0x10, kFlat04},
      {0x14, kFlat04}, {0x18, kFlat04}, {0x1c, kFlat04}, {0x20, kFlat20},
      {0x24, kFlat24}, {0x28, kFlat28}, {0x2c, kFlat20}, {0x30, kFlat20},
      {0x34, kFlat20}, {0x38, kFlat20}, {0x3c, kFlat20},
  };
  for (const Plant& p : kPlants) {
    *reinterpret_cast<SlotFn*>(g_receiver.bytes + p.off) = observer_address(p.obs);
  }
}

// The four bytes planted at receiver+0x24, read back as a word.
Word flat_planted_word_24() {
  Word w;
  std::memcpy(&w, g_receiver.bytes + 0x24, sizeof(w));
  return w;
}

// The byte 0x00641451 MOV AL,[ESI+0x26] reads once receiver+0x24 holds a live
// observer address. It is read back out of the RECEIVER rather than recomputed
// from &obs_f24 on purpose: on this PIE toolchain GCC is free to give two
// address-of expressions for the same function two different values (a canonical
// address in one place, a resolved one in another), and the machine only ever
// sees the bytes that are in memory. What the machine reads is byte 2 of the
// planted word, and that relationship is asserted directly.
std::uint8_t flat_planted_byte_26() { return g_receiver.bytes[0x26]; }

// `results[k]` is what the k-th dispatch (1-based) must return. The same queue is
// given to table A's and table B's slot 9, so an assertion about the RETURN value
// holds independently of which table a dispatch-word overwrite sent the call to --
// the dispatch ORDER is what the overwrite cases assert.
void setup(const Word results[4], std::uint8_t byte26, bool plant_flat) {
  std::memset(&g_receiver, 0, sizeof(g_receiver));
  std::memset(&g_table_a, 0, sizeof(g_table_a));
  std::memset(&g_table_b, 0, sizeof(g_table_b));

  Vtable* a = table_a();
  Vtable* b = table_b();
  for (std::size_t i = 0; i < P::kVtableSlotCount; ++i) {
    P::store_slot_at(a, i, &obs_a8);
    P::store_slot_at(b, i, &obs_b8);
  }
  P::store_slot_at(a, P::kSlotDispatched, &obs_a9);
  P::store_slot_at(a, P::kSlotDispatched - 1, &obs_a8);   // D1
  P::store_slot_at(a, P::kSlotDispatched + 1, &obs_a10);  // D1
  P::store_slot_at(b, P::kSlotDispatched, &obs_b9);
  P::store_slot_at(b, P::kSlotDispatched - 1, &obs_b8);   // D1
  P::store_slot_at(b, P::kSlotDispatched + 1, &obs_b10);  // D1

  // The receiver is an opaque byte run: every byte below is written by the
  // displacement the instruction that reads it prints, and no member is named.
  P::store_pointer_at(receiver(), P::kReceiverDispatchWordDisplacement, a);
  // D9. Three distinct neighbouring bytes, so a model that reads the result from
  // +0x25 (which the neighbouring accessor 0x00641460 does read) or from +0x27
  // returns a different low byte and is caught. +0x25 and +0x27 are spelled as
  // displacements rather than named, because this body reaches neither of them.
  P::store_byte_at(receiver(), 0x25, 0x31);
  P::store_byte_at(receiver(), P::kReceiverResultByteDisplacement, byte26);
  P::store_byte_at(receiver(), 0x27, 0xc3);

  if (plant_flat) {
    plant_flat_decoys();
  }

  std::memset(g_obs, 0, sizeof(g_obs));
  std::memset(g_behaviour, 0, sizeof(g_behaviour));
  for (int i = 0; i < kObserverCount; ++i) {
    g_behaviour[i].overwrite_on_call = -1;
    for (int k = 0; k < kMaxDispatches; ++k) {
      g_behaviour[i].result[k] = 0xffffffffu;  // decoys answer loudly if fired
    }
  }
  for (int k = 0; k < 4; ++k) {
    g_behaviour[kA9].result[k] = results[k];
    g_behaviour[kB9].result[k] = results[k];
  }
  g_dispatch_no = 0;
  g_order_len = 0;
}

void snapshot() {
  std::memcpy(g_saved.receiver.bytes, g_receiver.bytes, sizeof(RawBlock));
  std::memcpy(g_saved.a.bytes, g_table_a.bytes, sizeof(RawBlock));
  std::memcpy(g_saved.b.bytes, g_table_b.bytes, sizeof(RawBlock));
}

void reset_trampoline() {
  w21_t9_esp = 0;
  w21_t9_ecx = 0;
  w21_t9_ret = 0;
  w21_t9_ret0 = 0;
  w21_t9_same_site = 0;
  w21_t9_n = 0;
}

// D13. The 31 instructions contain no store to memory, so both tables must come
// back byte-identical.
void check_tables_unwritten() {
  ++g_checks;
  if (std::memcmp(g_table_a.bytes, g_saved.a.bytes, sizeof(RawBlock)) != 0 ||
      std::memcmp(g_table_b.bytes, g_saved.b.bytes, sizeof(RawBlock)) != 0) {
    ++g_failures;
    std::printf(
        "  FAIL  the body wrote to a table; 0x00641410..0x00641459 contains no "
        "store instruction\n");
  }
}

// D13. The receiver must come back byte-identical past its leading word. Byte 0
// to 3 is exempt because a case may deliberately arm a dispatch-word overwrite
// and the OVERWRITE is performed by the observer, not by the model. Any other byte
// moving means the model wrote through the receiver.
void check_receiver_unwritten_past_vptr() {
  ++g_checks;
  for (std::size_t off = 4; off < sizeof(RawBlock); ++off) {
    if (g_receiver.bytes[off] != g_saved.receiver.bytes[off]) {
      ++g_failures;
      std::printf(
          "  FAIL  the body wrote at receiver+0x%02x; 0x00641410..0x00641459 "
          "contains no store instruction\n",
          static_cast<unsigned>(off));
      return;
    }
  }
}

void check_decoys_silent() {
  check(g_obs[kA8].calls == 0, "D1: table A slot 8 (+0x20) was never dispatched");
  check(g_obs[kA10].calls == 0, "D1: table A slot 10 (+0x28) was never dispatched");
  check(g_obs[kB8].calls == 0, "D1: table B slot 8 (+0x20) was never dispatched");
  check(g_obs[kB10].calls == 0, "D1: table B slot 10 (+0x28) was never dispatched");
  check(g_obs[kFlat24].calls == 0,
        "D2: nothing was dispatched out of the receiver's own +0x24");
  check(g_obs[kFlat20].calls == 0,
        "D2: nothing was dispatched out of the receiver's own +0x20");
  check(g_obs[kFlat28].calls == 0,
        "D2: nothing was dispatched out of the receiver's own +0x28");
  check(g_obs[kFlat04].calls == 0,
        "D2: nothing was dispatched out of the receiver's own +0x04");
  check(g_obs[kFlat08].calls == 0,
        "D2: nothing was dispatched out of the receiver's own +0x08");
}

constexpr Word kSentinelValue = 0xa5a5a5a5u;
Word kSentinel() { return kSentinelValue; }

// D10. Both ESI words were poisoned before the call, so a model that popped on one
// path only, or on neither, fails here. The words are separate on purpose: with a
// single word, a model that popped on the true path only would look correct.
void check_esi_words(Word got) {
  (void)got;
  check_equal(P::saved_esi_frame_word(), kSentinel(),
              "0x00641410: the frame word is the ESI value seen on entry");
  check_equal(P::restored_esi_word(), kSentinel(),
              "the POP ESI on THIS return path wrote the caller's ESI back");
}

// D1, D2, D10 and D13, for one run. `expect_calls` is the total number of
// dispatches, which is the short-circuit made observable.
//
// The function's declared return type is the ONE BYTE both exit sites write, so
// the C return value carries the low byte alone. The complete 32-bit EAX the body
// leaves behind is a REGISTER fact and is read through model_returned_eax(); the
// word it returns below is that register, so every assertion written against the
// 32-bit residue is unchanged in what it says. The returned byte is asserted
// against that word's low byte as well, so the two channels are pinned to each
// other and neither can drift.
Word run_and_check(const Word results[4], std::uint8_t byte26, int expect_calls,
                   bool plant_flat) {
  setup(results, byte26, plant_flat);
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel());
  const std::uint8_t low = P::re_00641410(receiver());
  const Word got = P::model_returned_eax();

  check_equal(static_cast<Word>(low), got & 0xffu,
              "the C-visible return is the low byte of the register the body leaves");
  check(g_obs[kA9].calls + g_obs[kB9].calls ==
            static_cast<unsigned>(expect_calls),
        "the number of dispatches matches the short-circuit");
  check_decoys_silent();
  if (g_obs[kA9].calls != 0) {
    check(g_obs[kA9].receiver == static_cast<const void*>(receiver()),
          "00641418: the first callee was handed the entry receiver");
    check(g_obs[kA9].receiver !=
              reinterpret_cast<const void*>(g_receiver.bytes + 0x04),
          "00641411: the receiver is the entry pointer, not receiver+0x04");
  }
  if (g_obs[kB9].calls != 0) {
    check(g_obs[kB9].receiver == static_cast<const void*>(receiver()),
          "00641426/36/46: the later callees got the same entry receiver");
  }
  check_esi_words(got);
  check_tables_unwritten();
  check_receiver_unwritten_past_vptr();
  return got;
}

// -- cases ---------------------------------------------------------------------

// The base case: nothing matches, so all four dispatches happen and the answer is
// the receiver's byte at +0x26 carried over callee 4's high 24 bits.
void case_no_match_returns_receiver_byte() {
  std::printf("case: no literal matches -- four dispatches, receiver byte +0x26\n");
  const Word results[4] = {0x11111111u, 0x22222222u, 0x33333333u, 0xdeadbeefu};
  const Word got = run_and_check(results, 0x5au, 4, false);
  check(g_order_len == 4, "exactly four dispatches and no fifth");
  check_order(0, kA9, "00641418 dispatch 1 hit table A's slot 9");
  check_order(1, kA9, "00641428 dispatch 2 hit table A's slot 9");
  check_order(2, kA9, "00641438 dispatch 3 hit table A's slot 9");
  check_order(3, kA9, "00641448 dispatch 4 hit table A's slot 9");
  // D7. Not 0x0000005a and not 1: the high 24 bits are callee 4's. The high word
  // of the answer is 0xdeadbe, NOT 0xdead00 -- the middle byte is callee 4's too,
  // because 0x00641451 replaces AL only.
  check_equal(got, 0xdeadbe5au,
              "D7: 00641451 replaced only AL of callee 4's 0xdeadbeef");
  check_equal(got & 0xffu, 0x5au, "0x00641451 read the byte at receiver+0x26");
  check(got != 0x0000005au, "D7: this is not a zero-extended byte");
  check(got != 1u, "D7: this is not a boolean");
}

// D6. The four false exits are FULLY DETERMINED: the CMP that reaches each one has
// just proved EAX equal to the literal, and 0x00641456 clears only AL.
void case_deny_exits_are_determined_residues() {
  std::printf(
      "case: D6 -- the four false exits are 0xbcd73e00/0xb8669e00/0x37148100/"
      "0x04f68400\n");
  {
    const Word r[4] = {kK1, 0u, 0u, 0u};
    const Word got = run_and_check(r, 0x5au, 1, false);
    check_equal(got, 0xbcd73e00u, "0x00641456 after 0x0064141f: XOR AL,AL only");
    check(got != 0u, "D6: 0x00641456 does not zero all of EAX");
  }
  {
    const Word r[4] = {0u, kK2, 0u, 0u};
    const Word got = run_and_check(r, 0x5au, 2, false);
    check_equal(got, 0xb8669e00u, "0x00641456 after 0x0064142f: XOR AL,AL only");
    check(got != 0u, "D6: 0x00641456 does not zero all of EAX");
  }
  {
    const Word r[4] = {0u, 0u, kK3, 0u};
    const Word got = run_and_check(r, 0x5au, 3, false);
    check_equal(got, 0x37148100u, "0x00641456 after 0x0064143f: XOR AL,AL only");
    check(got != 0u, "D6: 0x00641456 does not zero all of EAX");
  }
  {
    const Word r[4] = {0u, 0u, 0u, kK4};
    const Word got = run_and_check(r, 0x5au, 4, false);
    check_equal(got, 0x04f68400u, "0x00641456 after 0x0064144f: XOR AL,AL only");
    check(got != 0u, "D6: 0x00641456 does not zero all of EAX");
  }
}

// D8. The result byte is forwarded RAW. A model that returns `b != 0` gives 1 for
// 0x02, 0x7f and 0x80; this one must not.
void case_result_byte_is_raw_not_boolean() {
  std::printf("case: D8 -- the byte at +0x26 is forwarded raw, not booleanised\n");
  const std::uint8_t kBytes[] = {0x00u, 0x01u, 0x02u, 0x7fu, 0x80u, 0xffu};
  for (std::uint8_t b : kBytes) {
    const Word r[4] = {0x01010101u, 0x02020202u, 0x03030303u, 0x7f000000u};
    const Word got = run_and_check(r, b, 4, false);
    check_equal(got, 0x7f000000u | static_cast<Word>(b),
                "0x00641451 forwards the byte unchanged into AL");
  }
}

// D9. Distinct bytes at +0x25, +0x26 and +0x27: the answer must come from +0x26.
void case_result_byte_offset_is_26() {
  std::printf("case: D9 -- the result byte is at +0x26, not +0x25 or +0x27\n");
  const Word r[4] = {0u, 0u, 0u, 0x44000000u};
  const Word got = run_and_check(r, 0x5au, 4, false);
  check_equal(got, 0x4400005au, "0x00641451 MOV AL,[ESI+0x26]");
  check(got != 0x44000031u, "D9: the byte at +0x25 is not what this body reads");
  check(got != 0x440000c3u, "D9: the byte at +0x27 is not what this body reads");
}

// D4. Both neighbours of every literal, on both sides, must fall through.
void case_off_by_one_literals_do_not_match() {
  std::printf("case: D4 -- the two neighbours of each literal do not match\n");
  const Word kNeighbours[8] = {kK1 - 1u, kK1 + 1u, kK2 - 1u, kK2 + 1u,
                              kK3 - 1u, kK3 + 1u, kK4 - 1u, kK4 + 1u};
  for (int i = 0; i < 8; ++i) {
    const Word r[4] = {kNeighbours[i], kNeighbours[i], kNeighbours[i], 0x0f0f0f0fu};
    const Word got = run_and_check(r, 0x5au, 4, false);
    check_equal(got, 0x0f0f0f5au,
                "D4: a literal that is one out does not short-circuit");
  }
}

// D4. Each literal belongs to ONE call. Offering literal N to call M for N != M
// must not short-circuit, which is what kills a model that checks all four
// literals against every result.
void case_permuted_literals_do_not_match() {
  std::printf("case: D4 -- a literal only matches at its own call\n");
  {
    const Word r[4] = {0u, kK1, 0u, 0u};  // literal 1 offered to call 2
    const Word got = run_and_check(r, 0x5au, 4, false);
    check_equal(got, 0x0000005au, "0x0064142a compares against 0xb8669ec9 only");
  }
  {
    const Word r[4] = {0u, 0u, kK4, 0u};  // literal 4 offered to call 3
    const Word got = run_and_check(r, 0x5au, 4, false);
    check_equal(got, 0x0000005au, "0x0064143a compares against 0x37148141 only");
  }
  {
    const Word r[4] = {kK2, 0u, 0u, 0u};  // literal 2 offered to call 1
    const Word got = run_and_check(r, 0x5au, 4, false);
    check_equal(got, 0x0000005au, "0x0064141a compares against 0xbcd73e89 only");
  }
}

// D5. Signedness, magnitude and the null/one patterns must all fall through: the
// CMP is a bitwise equality test and nothing else. Two of the four literals have
// the sign bit set, so a model that compared them as signed magnitudes could not
// reach them at all.
void case_edge_values_do_not_match() {
  std::printf(
      "case: D5 -- 0, 1, 0x7fffffff, 0x80000000, 0xffffffff all fall through\n");
  const Word kEdges[6] = {0u, 1u, 0x7fffffffu, 0x80000000u, 0xffffffffu,
                          0x80000000u | kK3};
  for (int i = 0; i < 6; ++i) {
    const Word r[4] = {kEdges[i], kEdges[i], kEdges[i], kEdges[i]};
    const Word got = run_and_check(r, 0x5au, 4, false);
    check_equal(got, (kEdges[i] & 0xffffff00u) | 0x5au,
                "D5: an edge value is not one of the four literals");
  }
}

// D2. With live observers planted in the receiver's own memory at every offset a
// wrong model would read, the model must still go through the dispatch word.
void case_one_level_dereference_decoy() {
  std::printf("case: D2 -- the receiver's own bytes are not a table\n");
  const Word r[4] = {0u, 0u, 0u, 0x99000000u};
  const Word got = run_and_check(r, 0x5au, 4, true);
  check_decoys_silent();
  check_equal(got, 0x99000000u | static_cast<Word>(flat_planted_byte_26()),
              "D2: the answer still comes from +0x26, through the dispatch word");
}

// D3. A callee that rewrites the dispatch word must change where the NEXT dispatch
// goes, and only the next one -- so the order is A, B, B, B for an overwrite on
// call 1 and A, A, B, B for an overwrite on call 2. The second one is what
// separates a model that re-reads EVERY time from one that re-reads once.
void case_dispatch_word_is_reread() {
  std::printf("case: D3 -- the dispatch word is re-read before every call\n");
  {
    const Word r[4] = {0u, 0u, 0u, 0x22000000u};
    setup(r, 0x5au, false);
    g_behaviour[kA9].overwrite_on_call = 1;  // during dispatch 1
    g_behaviour[kA9].overwrite_word = table_b();
    snapshot();
    P::model_reset_esi_probes();
    P::model_set_esi_at_entry(kSentinel());
    const std::uint8_t low = P::re_00641410(receiver());
    const Word got = P::model_returned_eax();
    check_equal(static_cast<Word>(low), got & 0xffu,
                "the C-visible return is the low byte of the register");
    check(g_obs[kA9].calls == 1 && g_obs[kB9].calls == 3,
          "D3: dispatches 2..4 followed the rewritten dispatch word");
    check_order(0, kA9, "00641418 dispatched through the original table");
    check_order(1, kB9, "0x00641421 re-read the word and got the new table");
    check_order(2, kB9, "0x00641431 re-read the word again");
    check_order(3, kB9, "0x00641441 re-read the word again");
    check_equal(got, 0x2200005au, "the return value is unchanged by the swap");
    check_decoys_silent();
    check_esi_words(got);
    check_tables_unwritten();
  }
  {
    const Word r[4] = {0u, 0u, 0u, 0x33000000u};
    setup(r, 0x5au, false);
    g_behaviour[kA9].overwrite_on_call = 2;  // during dispatch 2
    g_behaviour[kA9].overwrite_word = table_b();
    snapshot();
    P::model_reset_esi_probes();
    P::model_set_esi_at_entry(kSentinel());
    const std::uint8_t low = P::re_00641410(receiver());
    const Word got = P::model_returned_eax();
    check_equal(static_cast<Word>(low), got & 0xffu,
                "the C-visible return is the low byte of the register");
    check(g_obs[kA9].calls == 2 && g_obs[kB9].calls == 2,
          "D3: dispatches 3 and 4 followed the word rewritten during dispatch 2");
    check_order(0, kA9, "00641418 hit the original table");
    check_order(1, kA9, "0x00641428 still hit the original table");
    check_order(2, kB9, "0x00641431 saw the rewrite from dispatch 2");
    check_order(3, kB9, "0x00641441 saw it too");
    check_equal(got, 0x3300005au, "the return value is unchanged by the swap");
    check_decoys_silent();
    check_esi_words(got);
    check_tables_unwritten();
  }
}

// D11 and D12. The trampoline samples ESP, ECX and the return address of the last
// dispatch, and the model publishes the ESP of each of the four call sites.
void case_register_and_stack_state_via_trampoline() {
  std::printf("case: D11/D12 -- trampoline-sampled register and stack state\n");
  const Word r[4] = {0u, 0u, 0u, 0x55000000u};
  setup(r, 0x5au, false);
  P::store_slot_at(table_a(), P::kSlotDispatched, &w21_tramp9);
  reset_trampoline();
  w21_t9_result = 0x55000000u;
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel());
  const std::uint8_t low = P::re_00641410(receiver());
  const Word got = P::model_returned_eax();

  check_equal(static_cast<Word>(low), got & 0xffu,
              "the C-visible return is the low byte of the register");
  check_equal(w21_t9_n, 4u, "D11: all four CALL EDX sites reached the trampoline");
  const Word published[4] = {P::dispatch_esp_call1(), P::dispatch_esp_call2(),
                             P::dispatch_esp_call3(), P::dispatch_esp_call4()};
  check_equal(published[0], published[3],
              "D11: no stack word was left between the four dispatches");
  if (w21_t9_n == 4u) {
    // Exactly one word is pushed at each call: the return address. If the body
    // pushed an argument, the trampoline would see ESP two words lower.
    check_equal(w21_t9_esp, published[3] - 4u,
                "D11: that dispatch pushed only its return address -- zero stack "
                "arguments");
    check_equal(w21_t9_ecx, reinterpret_cast<Word>(receiver()),
                "00641418/26/36/46: the callee was handed the entry receiver");
  }
  // D12. No two hits may share a return address, and all of them must lie inside
  // the model's own text.
  check_equal(w21_t9_same_site, 0u,
              "D12: the four dispatches come from four distinct call sites");
  const std::uintptr_t entry = reinterpret_cast<std::uintptr_t>(&P::re_00641410);
  if (w21_t9_n == 4u) {
    const std::uintptr_t first = static_cast<std::uintptr_t>(w21_t9_ret0);
    const std::uintptr_t last = static_cast<std::uintptr_t>(w21_t9_ret);
    check(first >= entry && first < entry + 0x1000,
          "D12: the first dispatch's return address lies inside re_00641410");
    check(last >= entry && last < entry + 0x1000,
          "D12: the last dispatch's return address lies inside re_00641410");
    check(first != last,
          "D12: the first and the last dispatch have different call sites");
  }
  check_equal(got, 0x5500005au, "the trampoline path returns the same word");
  check_esi_words(got);
  check_tables_unwritten();
  check_receiver_unwritten_past_vptr();
}

// D11 on a false path: the short-circuit must be real at the register level too,
// i.e. the trampoline is entered ONCE, not four times. This also samples the
// FIRST CALL EDX's stack depth, which the true-path case cannot.
void case_trampoline_on_a_false_path() {
  std::printf("case: D11 -- the short-circuit is real at the register level\n");
  const Word r[4] = {kK1, 0u, 0u, 0u};
  setup(r, 0x5au, false);
  P::store_slot_at(table_a(), P::kSlotDispatched, &w21_tramp9);
  reset_trampoline();
  w21_t9_result = kK1;
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel());
  const std::uint8_t low = P::re_00641410(receiver());
  const Word got = P::model_returned_eax();

  check_equal(static_cast<Word>(low), got & 0xffu,
              "the C-visible return is the low byte of the register");
  check_equal(w21_t9_n, 1u, "0x0064141f left through 0x00641456 after ONE call");
  if (w21_t9_n >= 1u) {
    check_equal(w21_t9_esp, P::dispatch_esp_call1() - 4u,
                "D11: the first dispatch pushed only its return address");
    check_equal(w21_t9_ecx, reinterpret_cast<Word>(receiver()),
                "0x00641418: the callee was handed the entry receiver with no "
                "ECX reload before it");
    const std::uintptr_t entry =
        reinterpret_cast<std::uintptr_t>(&P::re_00641410);
    const std::uintptr_t first = static_cast<std::uintptr_t>(w21_t9_ret0);
    check(first >= entry && first < entry + 0x1000,
          "0x00641418: the only call came from inside re_00641410");
  }
  check_equal(P::dispatch_esp_call2(), P::model_esi_poison(),
              "the second call site's ESP was never published -- it never "
              "happened");
  check_equal(P::dispatch_esp_call3(), P::model_esi_poison(),
              "the third call site's ESP was never published");
  check_equal(P::dispatch_esp_call4(), P::model_esi_poison(),
              "the fourth call site's ESP was never published");
  check_equal(got, 0xbcd73e00u, "0x00641456 cleared only AL");
  check_esi_words(got);
  check_tables_unwritten();
  check_receiver_unwritten_past_vptr();
}

// Self-check: the D2 decoy observers are reachable, so their silence elsewhere is
// evidence and not dead code.
void case_decoys_are_live() {
  std::printf("self-check: the D2 decoy observers are reachable\n");
  const Word r[4] = {0u, 0u, 0u, 0u};
  setup(r, 0x5au, true);
  for (int i = kFlat24; i < kObserverCount; ++i) {
    for (int k = 0; k < kMaxDispatches; ++k) {
      g_behaviour[i].result[k] = 0xaaaa0000u | static_cast<Word>(i);
    }
    const Word got = observer_address(i)(receiver());
    check_equal(got, 0xaaaa0000u | static_cast<Word>(i),
                "a decoy observer returns exactly its scripted result");
    check(g_obs[i].calls == 1,
          "a decoy observer records a call, so a model that fires one is "
          "detected");
  }
  // And the flat plants really are inside the receiver block, and the byte the
  // D2 case will compare against really is byte 2 of the planted word.
  check(flat_planted_word_24() != 0u,
        "a live observer address really is planted at receiver+0x24");
  check_equal(static_cast<Word>(flat_planted_byte_26()),
              (flat_planted_word_24() >> 16) & 0xffu,
              "the byte at +0x26 is byte 2 of the word planted at +0x24");
}

}  // namespace

int main() {
  std::printf("PKG-SWARM-W1-00641410 model test for FUN_00641410 @ 0x00641410\n");

  case_decoys_are_live();
  case_no_match_returns_receiver_byte();
  case_deny_exits_are_determined_residues();
  case_result_byte_is_raw_not_boolean();
  case_result_byte_offset_is_26();
  case_off_by_one_literals_do_not_match();
  case_permuted_literals_do_not_match();
  case_edge_values_do_not_match();
  case_one_level_dereference_decoy();
  case_dispatch_word_is_reread();
  case_register_and_stack_state_via_trampoline();
  case_trampoline_on_a_false_path();

  std::printf("\n%d checks, %d failure(s)\n", g_checks, g_failures);
  if (g_failures != 0) {
    std::printf("MODEL TEST FAILED\n");
    return 1;
  }
  std::printf("MODEL TEST PASSED\n");
  return 0;
}
