// PKG-SWARM-W1-00641780 -- model test for VA 0x00641780
//
// A falsification test, not a walkthrough. Its job is to try to KILL the model in
// swarm_w1_00641780.cpp, and every assertion below is tied to a pair of
// instructions in the 19-instruction listing:
//
//   00641780 PUSH ESI / 006417a0 POP ESI / 006417a4 POP ESI
//   00641781 MOV ESI,ECX
//   00641783 MOV EAX,[ESI]        + 00641785 MOV EDX,[EAX + 0x10]   slot 4, first
//   0064178a TEST EAX,EAX / 0064178c JZ 0x006417a2
//   0064178e MOV EAX,[ESI]        + 00641790 MOV EDX,[EAX + 0xc]   slot 3, second
//   00641793 MOV ECX,ESI
//   00641797 TEST EAX,EAX / 00641799 JZ 0x006417a2
//   0064179b MOV EAX,0x1 / 006417a2 XOR EAX,EAX
//
// There are no direct callees to observe, because the body has none: both
// transfers are indirect (`CALL EDX` at 0x00641788 and 0x00641795). So the
// observation surface this test builds is the same thing the machine observes --
// two tables' worth of slots -- and every cell is an observer that records what
// it was handed and returns a scripted 32-bit word.
//
// TWO KINDS OF OBSERVER, and why both are needed:
//
//  * C++ observers (note()/obs_*) record their ordinal, the receiver pointer
//    that reached them, and a scripted result. They can also mutate the
//    receiver's dispatch word from inside the call, which is the only way to
//    distinguish a re-reading model from a caching one. They CANNOT be used to
//    assert register or stack state: a C++ function has already built its own
//    frame and taken its own register assignments by the time it runs, so its
//    ESP is its own and its ECX/ESI are the compiler's business.
//
//  * Two hand-written assembly trampolines (w13_tramp4 / w13_tramp3) that sample
//    ESP, ECX, ESI and the return address as their FIRST and only meaningful
//    instructions, with no prologue at all. They are what the register and
//    argument-surface claims are made from, and they are the strictest decoys in
//    the file: they ignore the receiver entirely and just report.
//
// Decoy coverage, and the defect each decoy is designed to kill:
//
//   D1  slots 2 and 5 of table A hold observers that fail the run if fired
//       -> an off-by-one slot displacement (0x08 or 0x14 instead of 0x10/0x0c)
//   D2  receiver bytes +0x0c and +0x10, and +0x04..+0x3c, hold live observer
//       addresses -> a ONE-level dereference (treating the receiver's own memory
//          as the table) or a wrong receiver offset
//   D3  the first dispatched callee overwrites the receiver's dispatch word,
//       pointing it at a different table -> a model that CACHES the vptr instead
//          of re-reading it at 0x0064178e
//   D4  scripted results 0, 1, 2, 0x7fffffff, 0x80000000, 0xdeadbeef, 0xffffffff
//       -> a `== 1` test instead of the 32-bit `TEST EAX,EAX`, a signed compare,
//          or a low-byte projection
//   D5  the caller's ESI is set to a sentinel and sampled IMMEDIATELY after the
//       call on both return paths -> a missing POP ESI, or a POP on only one path
//   D6  the trampolines sample ECX and ESI at the top of the first instruction
//       -> a model that does not pass the entry receiver, or does not alias it
//          into ESI at 0x00641781
//   D7  the trampolines sample ESP at the top of the first instruction and the
//       model publishes the ESP of each call site
//       -> a pushed stack argument, or a stack word leaked between the two
//          dispatches.  ESP_callee == ESP_callsite - 4 is exactly "the CALL
//          pushed its return address and nothing else".
//   D8  the trampolines sample the return address, which must land inside the
//       model's own text -> a call made from anywhere but 0x00641788/0x00641795
//   D9  a byte-for-byte snapshot of the receiver block and both tables around
//       every run -> a model that writes through the receiver, which the listing
//       shows it never does
//   D10 slot-4-before-slot-3, asserted as an exact ordinal sequence
//       -> a swapped call order, which still returns the right bit
//
// Self-check: the D2 decoys are called once on purpose, to prove they are live
// observers and not unreachable code that could never fail the test.
//
// MUTATION CHECKING. Eighteen deliberate defects were injected into copies of
// swarm_w1_00641780.cpp / _types.hpp in /tmp and this test was run against each.
// Every one was killed; none survived:
//
//   invert the first test's polarity      KILLED (93 assertion failures)
//   test `!= 1` instead of `== 0`         KILLED (80)
//   remove the short circuit              KILLED (15)
//   project the second result to a byte   KILLED (9)
//   return 0xffffffff instead of 1        KILLED (75)
//   forward slot 3's result instead of 1  KILLED (67)
//   omit the POP ESI on the false path    KILLED (2)
//   cache the vptr across 0x0064178e      KILLED (5)
//   one-level dereference of the receiver KILLED (30)
//   read the dispatch word at +0x04       KILLED (SIGSEGV, an invalid vtable)
//   slot 4 -> 5                           KILLED at compile time (static_assert)
//   slot 3 -> 2                           KILLED at compile time (static_assert)
//   swap the two dispatch slots           KILLED (26)
//   do not park the entry ESI             KILLED (30)
//   invert the second test's polarity     KILLED (81)
//   push a stack argument at 0x00641788   KILLED (D7: callee entered 8 bytes
//                                          below the published call-site ESP)
//
// The two slot-constant defects dying at compile time rather than at run time is
// the intended outcome: the header's static_asserts tie kSlotCalledFirst and
// kSlotCalledSecond to the 0x10 and 0x0c displacements the instructions show, so
// an off-by-one slot cannot be written at all without editing that assertion.
//
// RE-MEASURED BY rp02 after the FIELDS/OFFSETS repair, which replaced the two
// struct members with opaque byte runs and displacement-named accessors. Three of
// the eighteen entries above are affected in HOW they die, and each was injected
// again into a copy under reconstruction/staging's package to confirm the kill
// still exists. No entry was removed and the "none survived" claim is unchanged.
//
//   kSlotCalledFirst 4 -> 5          STILL a compile-time static_assert failure:
//                                     kSlotCalledFirst is now derived as
//                                     kSlotCalledFirstIndex * kCellWidthBytes and
//                                     pinned by static_assert(kSlotCalledFirst ==
//                                     0x10), so moving the index to 5 fails the
//                                     build with "cell 4 is the 0x10 displacement
//                                     of 0x00641785".
//   kSlotCalledSecond 3 -> 2         SAME, via kSlotCalledSecondIndex and
//                                     static_assert(kSlotCalledSecond == 0x0c).
//   read the dispatch word at +0x04   NOW a compile-time static_assert failure
//                                     rather than a SIGSEGV:
//                                     kDispatchWordDisplacement is pinned to 0x00
//                                     by static_assert. The old kill was real and
//                                     so is the new one, earlier.
//   one-level dereference            STILL KILLED AT RUN TIME, and now also
//                                     unrepresentable. `word_through` takes its
//                                     base as a Word, so replacing it with
//                                     `word_at(self, kSlotCalledFirst)` is a
//                                     compile error (the table word becomes
//                                     unused). Forced past that -- both loads
//                                     rewritten one-level and the unused words
//                                     referenced -- D2 fires 49 times and the run
//                                     exits 1, so the decoys remain the witness
//                                     rather than the type system alone. The 30
//                                     above is the pre-repair count; 49 is this
//                                     re-measurement.
//
// WHAT IS DELIBERATELY NOT ASSERTED, and why:
//
//  * What the two callees MEAN. This body names no callee, no import, no string
//    and no constant, so no test can fix their identity, and asserting one would
//    be asserting something the 19 instructions do not say.
//  * That any real callee in the game ever changes the dispatch word. Case 7
//    proves only that the MODEL re-reads it, which is what 0x0064178e fixes.
//  * Anything about the 0x0c receiver bytes after the dispatch word. They are
//    carried as opaque; D2 plants live values there only to catch a wrong
//    displacement and asserts nothing about their content.
//  * The C++ observers' own ESP, ECX and ESI. Those are the compiler's, not the
//    model's; the register and stack claims are made from the trampolines only.
//  * That a callee samples the RECEIVER in ESI (0x00641781 MOV ESI,ECX). The
//    prescribed build is a PIE, and GCC's i386 PIE sequence for re_00641780 puts
//    the GOT base in ESI (`call __x86.get_pc_thunk.si; addl
//    $_GLOBAL_OFFSET_TABLE_,%esi`), so the trampoline samples the module address
//    instead of the receiver and the assertion would be measuring the toolchain.
//    The instruction is annotated in the model; what is asserted instead is the
//    weaker, still real fact that nothing between the two dispatches moves ESI.
//  * The 0x00641780/0x006417a0/0x006417a4 ESI traffic as a REGISTER effect. For
//    the same PIE reason the model carries it as a value pair (parked word and
//    restored word, each poisoned before every run) rather than reading and
//    writing the real register. The two words are separate on purpose: with one
//    word, a model that popped on only the true path would look correct.

#include "swarm_w1_00641780_types.hpp"

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace P = openspore::reconstruction::pkg_swarm_w1_00641780;

using P::AssetData;
using P::SlotFn;
using P::Word;
using P::store_word;
using P::store_word_through;
using P::word_at;

// -- the assembly trampolines ----------------------------------------------
//
// Each is a real __thiscall callee with a zero-stack-argument surface and NO
// prologue: the four `movl`s are its first four instructions, so what they
// record is the machine state at the callee's entry and nothing else. `ret` with
// no immediate matches 0x006417a1/0x006417a5 and the fact that the body pushes
// no argument.
extern "C" {
std::uint32_t w13_t4_esp;
std::uint32_t w13_t4_ecx;
std::uint32_t w13_t4_esi;
std::uint32_t w13_t4_ret;
std::uint32_t w13_t4_hits;
std::uint32_t w13_t4_result;

std::uint32_t w13_t3_esp;
std::uint32_t w13_t3_ecx;
std::uint32_t w13_t3_esi;
std::uint32_t w13_t3_ret;
std::uint32_t w13_t3_hits;
std::uint32_t w13_t3_result;
}  // extern "C"

__asm__(".text\n\t"
        ".globl w13_tramp4\n\t"
        ".type  w13_tramp4, @function\n\t"
        "w13_tramp4:\n\t"
        "  movl %esp, w13_t4_esp\n\t"
        "  movl %ecx, w13_t4_ecx\n\t"
        "  movl %esi, w13_t4_esi\n\t"
        "  movl (%esp), %eax\n\t"
        "  movl %eax, w13_t4_ret\n\t"
        "  movl $1, w13_t4_hits\n\t"
        "  movl w13_t4_result, %eax\n\t"
        "  ret\n\t"
        ".size w13_tramp4, .-w13_tramp4\n\t"
        ".globl w13_tramp3\n\t"
        ".type  w13_tramp3, @function\n\t"
        "w13_tramp3:\n\t"
        "  movl %esp, w13_t3_esp\n\t"
        "  movl %ecx, w13_t3_ecx\n\t"
        "  movl %esi, w13_t3_esi\n\t"
        "  movl (%esp), %eax\n\t"
        "  movl %eax, w13_t3_ret\n\t"
        "  movl $1, w13_t3_hits\n\t"
        "  movl w13_t3_result, %eax\n\t"
        "  ret\n\t"
        ".size w13_tramp3, .-w13_tramp3\n\t");

extern "C" PKG_SWARM_W1_00641780_THISCALL std::uint32_t w13_tramp4(AssetData*);
extern "C" PKG_SWARM_W1_00641780_THISCALL std::uint32_t w13_tramp3(AssetData*);

namespace {

enum : int {
  kA_slot2 = 0,    // decoy: must never fire (0x00641785 must not read +0x08)
  kA_slot3 = 1,    // the second dispatch target of table A (0x00641790, +0x0c)
  kA_slot4 = 2,    // the FIRST dispatch target of table A (0x00641785, +0x10)
  kA_slot5 = 3,    // decoy: must never fire (must not read +0x14)
  kB_slot3 = 4,    // second dispatch target of table B, reached only through the
                   // dispatch-word overwrite of case 7
  kB_slot4 = 5,    // decoy: must never fire
  kFlat_slot3 = 6, // D2 decoy, planted at receiver+0x0c and +0x08
  kFlat_slot4 = 7, // D2 decoy, planted at receiver+0x10 and +0x04
  kObserverCount
};

const char* const kObserverName[kObserverCount] = {
    "A.slot2(dead)", "A.slot3",         "A.slot4", "A.slot5(dead)",
    "B.slot3",       "B.slot4(dead)",   "flat+0c(dead)", "flat+10(dead)"};

struct Observation {
  unsigned calls;
  const void* receiver;  // what the observer found in ECX
};

struct Behaviour {
  std::uint32_t result;    // the 32-bit EAX this observer hands back
  Word overwrite_word;      // non-zero: write this into the receiver's dispatch
                            // word (displacement kDispatchWordDisplacement) on entry
};

Observation g_obs[kObserverCount];
Behaviour g_behaviour[kObserverCount];
int g_order[kObserverCount];
int g_order_len;
int g_failures;
int g_checks;

// Every C++ observer funnels through here. `overwrite_word` is the D3 mechanism:
// it mutates the dispatch word from inside the first callee, which is the only
// way to tell a re-reading model from a caching one. Zero means "leave it alone",
// so the store is skipped rather than writing a null table base.
std::uint32_t note(int index, AssetData* receiver) {
  Observation& o = g_obs[index];
  const Behaviour& b = g_behaviour[index];
  o.calls += 1;
  o.receiver = receiver;
  if (b.overwrite_word != 0) {
    store_word(receiver, P::kDispatchWordDisplacement, b.overwrite_word);
  }
  g_order[g_order_len++] = index;
  return b.result;
}

std::uint32_t PKG_SWARM_W1_00641780_THISCALL obs_a_slot2(AssetData* r) {
  return note(kA_slot2, r);
}
std::uint32_t PKG_SWARM_W1_00641780_THISCALL obs_a_slot3(AssetData* r) {
  return note(kA_slot3, r);
}
std::uint32_t PKG_SWARM_W1_00641780_THISCALL obs_a_slot4(AssetData* r) {
  return note(kA_slot4, r);
}
std::uint32_t PKG_SWARM_W1_00641780_THISCALL obs_a_slot5(AssetData* r) {
  return note(kA_slot5, r);
}
std::uint32_t PKG_SWARM_W1_00641780_THISCALL obs_b_slot3(AssetData* r) {
  return note(kB_slot3, r);
}
std::uint32_t PKG_SWARM_W1_00641780_THISCALL obs_b_slot4(AssetData* r) {
  return note(kB_slot4, r);
}
std::uint32_t PKG_SWARM_W1_00641780_THISCALL obs_flat_slot3(AssetData* r) {
  return note(kFlat_slot3, r);
}
std::uint32_t PKG_SWARM_W1_00641780_THISCALL obs_flat_slot4(AssetData* r) {
  return note(kFlat_slot4, r);
}

// -- the machine the model runs against --------------------------------------

// 0x40 bytes, so that receiver+0x0c and receiver+0x10 are inside the block and
// the D2 decoys can be live function pointers there.
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

// The model test's own planting helper, and the only place a table cell is ever
// written. The tables are raw byte blocks -- nothing in the package declares a
// cell array any more, because the machine-derived receiver record is bounds_only
// and names no member -- so a cell is addressed by its dword index and written
// through the package's own displacement accessor. The bytes written are the same
// bytes `Vtable::slots[index]` wrote, at the same offsets; only the spelling of
// the address changed, and D1 below is what proves the offsets did not.
void plant(Word table, std::size_t index, SlotFn fn) {
  store_word_through(table, index * P::kCellWidthBytes,
                     static_cast<Word>(reinterpret_cast<std::uintptr_t>(fn)));
}

Word table_a() {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_table_a));
}
Word table_b() {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_table_b));
}
AssetData* receiver() { return reinterpret_cast<AssetData*>(&g_receiver); }

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("  FAIL  %s\n", what);
  }
}

void check_equal(std::uint32_t got, std::uint32_t want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("  FAIL  %s (got 0x%08x, wanted 0x%08x)\n", what, got, want);
  }
}

void note_order(int position, int observer, const char* what) {
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
// instead of two -- calls one of them. +0x0c and +0x10 in particular are where
// slots 3 and 4 sit under that wrong reading.
void plant_one_level_decoys() {
  for (std::size_t off = 0x04;
       off + sizeof(SlotFn) <= sizeof(g_receiver.bytes); off += sizeof(SlotFn)) {
    SlotFn* const cell = reinterpret_cast<SlotFn*>(g_receiver.bytes + off);
    *cell = ((off % 0x08) == 0x00) ? &obs_flat_slot4 : &obs_flat_slot3;
  }
}

void setup(std::uint32_t slot4_result, std::uint32_t slot3_result) {
  std::memset(&g_receiver, 0, sizeof(g_receiver));
  std::memset(&g_table_a, 0, sizeof(g_table_a));
  std::memset(&g_table_b, 0, sizeof(g_table_b));

  Word a = table_a();
  Word b = table_b();
  plant(a, 0, &obs_a_slot2);
  plant(a, 1, &obs_a_slot2);
  plant(a, 2, &obs_a_slot2);  // D1, lower neighbour of cell 3 (+0x0c)
  plant(a, 3, &obs_a_slot3);  // 0x0c, the second dispatch
  plant(a, 4, &obs_a_slot4);  // 0x10, the first dispatch
  plant(a, 5, &obs_a_slot5);  // D1, upper neighbour of cell 4 (+0x14)
  for (std::size_t i = 6; i < P::kTableCellCount; ++i) {
    plant(a, i, &obs_a_slot2);
  }
  plant(b, 0, &obs_b_slot4);
  plant(b, 1, &obs_b_slot4);
  plant(b, 2, &obs_b_slot4);
  plant(b, 3, &obs_b_slot3);
  plant(b, 4, &obs_b_slot4);  // D1: must never fire
  for (std::size_t i = 5; i < P::kTableCellCount; ++i) {
    plant(b, i, &obs_b_slot4);
  }

  plant_one_level_decoys();
  store_word(receiver(), P::kDispatchWordDisplacement, a);

  std::memset(g_obs, 0, sizeof(g_obs));
  std::memset(g_behaviour, 0, sizeof(g_behaviour));
  g_behaviour[kA_slot3].result = slot3_result;
  g_behaviour[kA_slot4].result = slot4_result;
  g_behaviour[kB_slot3].result = 0x00000099u;
  g_behaviour[kFlat_slot3].result = 0xffffffffu;
  g_behaviour[kFlat_slot4].result = 0xffffffffu;
  g_order_len = 0;
}

// D9. The body performs no store, so the receiver and both tables must come back
// byte-identical.
void check_tables_unwritten() {
  ++g_checks;
  if (std::memcmp(g_table_a.bytes, g_saved.a.bytes, sizeof(RawBlock)) != 0 ||
      std::memcmp(g_table_b.bytes, g_saved.b.bytes, sizeof(RawBlock)) != 0) {
    ++g_failures;
    std::printf(
        "  FAIL  the body wrote to a table; 0x00641780..0x006417a5 contains no "
        "store instruction\n");
  }
}

void check_receiver_unwritten() {
  ++g_checks;
  if (std::memcmp(g_receiver.bytes, g_saved.receiver.bytes, sizeof(RawBlock)) !=
      0) {
    ++g_failures;
    std::printf(
        "  FAIL  the body wrote to the receiver; 0x00641780..0x006417a5 contains "
        "no store instruction\n");
  }
}

void check_no_writes() {
  check_tables_unwritten();
  check_receiver_unwritten();
}

void snapshot() {
  std::memcpy(g_saved.receiver.bytes, g_receiver.bytes, sizeof(RawBlock));
  std::memcpy(g_saved.a.bytes, g_table_a.bytes, sizeof(RawBlock));
  std::memcpy(g_saved.b.bytes, g_table_b.bytes, sizeof(RawBlock));
}

constexpr std::uint32_t kSentinel = 0xa5a5a5a5u;

// D1, D2, D9 and the receiver-identity half of the argument surface, for the
// C++-observer cases. `esi_after` must be sampled by the caller IMMEDIATELY
// after the model call, because the libc printf that a failing check() calls
// clobbers ESI on i386.
void check_common(std::uint32_t sentinel, std::uint32_t esi_after) {
  check(g_obs[kA_slot2].calls == 0,
        "D1: table A slot 2 (+0x08) was never dispatched");
  check(g_obs[kA_slot5].calls == 0,
        "D1: table A slot 5 (+0x14) was never dispatched");
  check(g_obs[kB_slot4].calls == 0,
        "D1: table B slot 4 (+0x10) was never dispatched");
  check(g_obs[kFlat_slot3].calls == 0,
        "D2: nothing was dispatched out of the receiver's own memory");
  check(g_obs[kFlat_slot4].calls == 0,
        "D2: nothing was dispatched out of the receiver's own memory");

  if (g_obs[kA_slot4].calls != 0) {
    check(g_obs[kA_slot4].receiver == static_cast<const void*>(receiver()),
          "00641788: the first callee was handed the entry receiver");
  }
  if (g_obs[kA_slot3].calls != 0) {
    check(g_obs[kA_slot3].receiver == static_cast<const void*>(receiver()),
          "00641793: the second callee was handed the same entry receiver");
  }
  check(g_obs[kA_slot4].receiver !=
            reinterpret_cast<const void*>(g_receiver.bytes + 0x04),
        "00641781: the receiver is the entry pointer, not receiver+0x04");
  check(g_obs[kA_slot3].receiver !=
            reinterpret_cast<const void*>(g_receiver.bytes + 0x08),
        "00641781: the receiver is the entry pointer, not receiver+0x08");

  // D5. 0x00641780 parks the caller's ESI and the POP at this path's return site
  // gives it back. Both words are checked and both were poisoned before the call,
  // so a model that popped on one path only, or on neither, fails here.
  check_equal(P::saved_esi_frame_word(), sentinel,
              "0x00641780: the frame word is the ESI value seen on entry");
  check_equal(esi_after, sentinel,
              "D5: the POP ESI on THIS return path wrote the caller's ESI back");

  check_no_writes();
}

void case_true_both_non_zero() {
  std::printf("case 1: both dispatched callees return non-zero\n");
  setup(0x12345678u, 0x00000001u);
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  const std::uint32_t r = P::re_00641780(receiver());
  const std::uint32_t esi_after = P::restored_esi_word();
  check_equal(r, 1u, "0064179b MOV EAX,0x1 -- the result is the literal 1");
  check(g_order_len == 2, "exactly two dispatches happened");
  note_order(0, kA_slot4, "D10: slot 4 (+0x10) is dispatched first");
  note_order(1, kA_slot3, "D10: slot 3 (+0x0c) is dispatched second");
  check_common(kSentinel, esi_after);
}

void case_first_zero_short_circuits() {
  std::printf("case 2: slot 4 returns 0 -- slot 3 must not be reached\n");
  setup(0x00000000u, 0x00000001u);
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  const std::uint32_t r = P::re_00641780(receiver());
  const std::uint32_t esi_after = P::restored_esi_word();
  check_equal(r, 0u, "006417a2 XOR EAX,EAX -- the result is a full 32-bit zero");
  check(g_order_len == 1, "exactly one dispatch happened");
  note_order(0, kA_slot4, "D10: the single dispatch is slot 4");
  check(g_obs[kA_slot3].calls == 0,
        "0064178c JZ exits before 0x0064178e re-reads the dispatch word");
  check_common(kSentinel, esi_after);
}

void case_second_zero() {
  std::printf("case 3: slot 4 non-zero, slot 3 zero -- shared false block\n");
  setup(0xffffffffu, 0x00000000u);
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  const std::uint32_t r = P::re_00641780(receiver());
  const std::uint32_t esi_after = P::restored_esi_word();
  check_equal(r, 0u, "00641799 JZ takes the shared 0x006417a2 false block");
  check(g_order_len == 2, "both dispatches happened");
  note_order(0, kA_slot4, "D10: slot 4 is dispatched first");
  note_order(1, kA_slot3, "D10: slot 3 is dispatched second");
  check_common(kSentinel, esi_after);
}

void case_both_zero() {
  std::printf("case 4: both zero -- the short circuit still holds\n");
  setup(0x00000000u, 0x00000000u);
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  const std::uint32_t r = P::re_00641780(receiver());
  const std::uint32_t esi_after = P::restored_esi_word();
  check_equal(r, 0u, "the false path returns zero");
  check(g_order_len == 1, "slot 3 was never dispatched");
  check_common(kSentinel, esi_after);
}

void case_result_is_a_fresh_one() {
  std::printf("case 5: 0x0064179b builds a new 1 -- nothing is forwarded\n");
  setup(0xdeadbeefu, 0xfeedfaceu);
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  const std::uint32_t r = P::re_00641780(receiver());
  const std::uint32_t esi_after = P::restored_esi_word();
  check_equal(r, 1u, "the result is the literal 1");
  check(r != 0xdeadbeefu, "slot 4's result is not forwarded");
  check(r != 0xfeedfaceu, "slot 3's result is not forwarded");
  check((r & 0xffffff00u) == 0u, "the literal 1 fills all 32 bits, not one byte");
  check_common(kSentinel, esi_after);
}

// D4. Both TEST instructions are 32-bit null tests. 0x80000000 is negative as a
// signed word and 0xdeadbeef has a zero low byte; a `== 1` test, a signed
// compare or a low-byte projection would each fail here.
void case_full_32_bit_zero_test() {
  static const std::uint32_t kNonZero[] = {0x00000001u, 0x00000002u, 0x000000ffu,
                                           0x7fffffffu, 0x80000000u, 0xfffffffeu,
                                           0xffffffffu, 0xdeadbeefu};
  const std::size_t n = sizeof(kNonZero) / sizeof(kNonZero[0]);
  std::printf("case 6: D4 -- 32-bit null test, not ==1, not signed, not a byte\n");
  int local_failures = 0;
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = 0; j < n; ++j) {
      setup(kNonZero[i], kNonZero[j]);
      P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
      const std::uint32_t r = P::re_00641780(receiver());
      if (r != 1u) {
        ++local_failures;
        if (local_failures < 4) {
          std::printf("  FAIL  D4: slot4=0x%08x slot3=0x%08x must yield 1, "
                      "got 0x%08x\n",
                      kNonZero[i], kNonZero[j], r);
        }
      }
    }
  }
  ++g_checks;
  g_failures += local_failures;
  if (local_failures > 4) {
    std::printf("  ... and %d further D4 mismatches\n", local_failures - 4);
  }
  check_equal(local_failures, 0, "D4: all 64 non-zero/non-zero pairs yield 1");

  setup(0x00000000u, 0xffffffffu);
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  check_equal(P::re_00641780(receiver()), 0u,
              "D4: a zero from slot 4 yields 0");
  setup(0xffffffffu, 0x00000000u);
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  check_equal(P::re_00641780(receiver()), 0u,
              "D4: a zero from slot 3 yields 0");
}

// D3. 0x0064178e is an independent load, so the second dispatch must come out of
// the dispatch word as the FIRST callee left it. Table B's slot 3 is the only
// way to tell the two models apart: table A's slot 3 is a different observer.
void case_dispatch_word_is_reread() {
  std::printf("case 7: D3 -- the dispatch word is re-read at 0x0064178e\n");
  setup(0x00000042u, 0x00000000u);
  g_behaviour[kA_slot4].overwrite_word = table_b();
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  const std::uint32_t r = P::re_00641780(receiver());
  const std::uint32_t esi_after = P::restored_esi_word();
  check_equal(r, 1u, "the swapped table's slot 3 decides the result");
  check(g_order_len == 2, "exactly two dispatches happened");
  note_order(0, kA_slot4, "D10: the first dispatch is table A slot 4");
  note_order(1, kB_slot3, "D3: the second dispatch is table B slot 3");
  check(g_obs[kA_slot3].calls == 0,
        "D3: table A's slot 3 was NOT used -- the vptr was not cached");
  check(word_at(receiver(), P::kDispatchWordDisplacement) == table_b(),
        "the body has no store, so the word the callee wrote still stands");
  check_tables_unwritten();
  check_equal(P::saved_esi_frame_word(), kSentinel,
              "0x00641780: the frame word is the ESI value seen on entry");
  check_equal(esi_after, kSentinel,
              "D5: the POP at this return path wrote the caller's ESI back");

  // Same swap, but the replacement callee returns zero: the AND must still
  // apply through the new table.
  setup(0x00000042u, 0x00000000u);
  g_behaviour[kA_slot4].overwrite_word = table_b();
  g_behaviour[kB_slot3].result = 0x00000000u;
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  const std::uint32_t r2 = P::re_00641780(receiver());
  const std::uint32_t esi_after2 = P::restored_esi_word();
  check_equal(r2, 0u, "D3: a zero from the swapped table's slot 3 yields 0");
  check(g_order_len == 2, "exactly two dispatches happened");
  note_order(0, kA_slot4, "D10: the first dispatch is table A slot 4");
  note_order(1, kB_slot3, "D3: the second dispatch is table B slot 3");
  check(g_obs[kA_slot3].calls == 0, "D3: table A's slot 3 was not used");
  check_tables_unwritten();
  check_equal(P::saved_esi_frame_word(), kSentinel,
              "0x00641780: the frame word is the ESI value seen on entry");
  check_equal(esi_after2, kSentinel,
              "D5: the POP at this return path wrote the caller's ESI back");
}

// D2 on its own: the receiver's own memory is shaped like a table of live
// observers, and none of them may be reached.
void case_one_level_dereference_decoy() {
  std::printf("case 8: D2 -- a one-level read of the receiver must not happen\n");
  setup(0x00000011u, 0x00000022u);
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  const std::uint32_t r = P::re_00641780(receiver());
  const std::uint32_t esi_after = P::restored_esi_word();
  check_equal(r, 1u, "the two-level read still reaches table A");
  check(g_obs[kFlat_slot3].calls == 0,
        "D2: MOV EAX,[ESI] loads a POINTER; receiver+0x0c is not a slot");
  check(g_obs[kFlat_slot4].calls == 0,
        "D2: MOV EAX,[ESI] loads a POINTER; receiver+0x10 is not a slot");
  check_equal(g_obs[kA_slot4].calls, 1u, "table A slot 4 ran exactly once");
  check_equal(g_obs[kA_slot3].calls, 1u, "table A slot 3 ran exactly once");
  check_common(kSentinel, esi_after);
}

// D5 on each return path specifically: 0x006417a4 is a second POP ESI and a
// restoration there is easy to omit.
void case_register_restored_on_both_paths() {
  std::printf("case 9: D5 -- the saved ESI is restored on BOTH return paths\n");
  static const std::uint32_t kSentinels[] = {0x00000000u, 0x00000001u,
                                             0x12345678u, 0xffffffffu};
  const std::size_t n = sizeof(kSentinels) / sizeof(kSentinels[0]);
  for (std::size_t i = 0; i < n; ++i) {
    for (int false_path = 0; false_path < 2; ++false_path) {
      if (false_path == 0) {
        setup(0x11111111u, 0x22222222u);  // takes 0x0064179b / 0x006417a0
      } else {
        setup(0x11111111u, 0x00000000u);  // takes 0x006417a2 / 0x006417a4
      }
      P::model_reset_esi_probes();
      P::model_set_esi_at_entry(kSentinels[i]);
      const std::uint32_t r = P::re_00641780(receiver());
      const std::uint32_t esi_after = P::restored_esi_word();
      check_equal(P::saved_esi_frame_word(), kSentinels[i],
                  "0x00641780: the frame word is the ESI value seen on entry");
      check_equal(esi_after, kSentinels[i],
                  "D5: the POP at 0x006417a0 and the POP at 0x006417a4 both "
                  "write the caller's ESI back");
      check_equal(r, false_path == 0 ? 1u : 0u,
                  "the return path taken is the one the results imply");
    }
  }
}

// D6, D7, D8. The trampolines have no prologue, so what they record IS the
// callee's entry state. Everything asserted here is a statement about the four
// register transfers at 0x00641783/85/88 and 0x0064178e/90/93/95.
void case_register_and_stack_state_via_trampolines() {
  std::printf("case 10: D6/D7/D8 -- ECX, ESI, ESP and the return address at "
              "both dispatches\n");
  setup(0x00000005u, 0x00000006u);
  Word a = table_a();
  plant(a, P::kSlotCalledSecondIndex, &w13_tramp3);
  plant(a, P::kSlotCalledFirstIndex, &w13_tramp4);
  w13_t3_hits = 0;
  w13_t4_hits = 0;
  w13_t3_result = 0x0000b0b0u;
  w13_t4_result = 0x0000f0f0u;
  snapshot();
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(kSentinel);
  const std::uint32_t r = P::re_00641780(receiver());
  const std::uint32_t esi_after = P::restored_esi_word();

  check_equal(r, 1u, "the trampoline results are consumed as 32-bit words");
  check_equal(w13_t4_hits, 1u, "D10: slot 4 was dispatched exactly once");
  check_equal(w13_t3_hits, 1u, "D10: slot 3 was dispatched exactly once");

  // D6. The receiver really arrives in ECX at both dispatches, and 0x00641781
  // really aliases it into ESI for the duration of both calls.
  check_equal(w13_t4_ecx, reinterpret_cast<std::uint32_t>(receiver()),
              "00641781/00641788: slot 4 receives the entry receiver in ECX");
  check_equal(w13_t3_ecx, reinterpret_cast<std::uint32_t>(receiver()),
              "00641793: slot 3 receives the same receiver in ECX");
  // 00641781 MOV ESI,ECX is a machine fact that this build cannot let the model
  // prove, and the reason is in the header: a PIE of this translation unit keeps
  // the GOT base in ESI (`call __x86.get_pc_thunk.si; addl
  // $_GLOBAL_OFFSET_TABLE_,%esi`), so the trampoline samples the module address,
  // not the receiver. What IS still decidable is that nothing between the two
  // dispatches moves ESI, and that is asserted.
  check_equal(w13_t4_esi, w13_t3_esi,
              "nothing between 0x00641788 and 0x00641795 moves ESI");

  // D7. Exactly one word is pushed at each call: the return address. If the body
  // pushed an argument, the trampoline would see ESP two words lower.
  check_equal(w13_t4_esp, P::dispatch_esp_first_call() - 4,
              "D7: 0x00641788 pushed only its return address -- zero stack "
              "arguments");
  check_equal(w13_t3_esp, P::dispatch_esp_second_call() - 4,
              "D7: 0x00641795 pushed only its return address -- zero stack "
              "arguments");
  check_equal(P::dispatch_esp_first_call(), P::dispatch_esp_second_call(),
              "D7: no stack word was left between the two dispatches");

  // D8. Both calls came out of the model's own text.
  const std::uintptr_t entry =
      reinterpret_cast<std::uintptr_t>(&P::re_00641780);
  const std::uintptr_t r4 = static_cast<std::uintptr_t>(w13_t4_ret);
  const std::uintptr_t r3 = static_cast<std::uintptr_t>(w13_t3_ret);
  check(r4 >= entry && r4 < entry + 0x400,
        "D8: the first call's return address lies inside re_00641780");
  check(r3 >= entry && r3 < entry + 0x400,
        "D8: the second call's return address lies inside re_00641780");
  check(r4 != r3, "D8: the two dispatches have distinct call sites");

  check(g_obs[kFlat_slot3].calls == 0 && g_obs[kFlat_slot4].calls == 0,
        "D2: the receiver's own bytes are not a table");
  check(g_obs[kA_slot2].calls == 0 && g_obs[kA_slot5].calls == 0,
        "D1: the neighbouring slots were not dispatched");
  check_equal(P::saved_esi_frame_word(), kSentinel,
              "0x00641780: the frame word is the ESI value seen on entry");
  check_equal(esi_after, kSentinel,
              "D5: the POP at this return path wrote the caller's ESI back");
  check_no_writes();
}

// Self-check for D2: the decoy observers are reachable, so their silence in
// cases 1..10 is evidence and not dead code.
void case_decoys_are_live() {
  std::printf("self-check: the D2 decoy observers are reachable\n");
  setup(0x00000011u, 0x00000022u);
  g_behaviour[kFlat_slot3].result = 0xaaaaaaaau;
  g_behaviour[kFlat_slot4].result = 0xbbbbbbbbu;
  const std::uint32_t a = obs_flat_slot3(receiver());
  const std::uint32_t b = obs_flat_slot4(receiver());
  check(a == 0xaaaaaaaau && b == 0xbbbbbbbbu,
        "a decoy observer returns exactly its scripted result");
  check(g_obs[kFlat_slot3].calls == 1 && g_obs[kFlat_slot4].calls == 1,
        "a decoy observer records a call, so cases 1..10 can detect one");
}

}  // namespace

int main() {
  std::printf(
      "PKG-SWARM-W1-00641780 model test for FUN_00641780 @ 0x00641780\n");
  P::model_reset_esi_probes();
  P::model_set_esi_at_entry(0x5a5a5a5au);

  case_decoys_are_live();
  case_true_both_non_zero();
  case_first_zero_short_circuits();
  case_second_zero();
  case_both_zero();
  case_result_is_a_fresh_one();
  case_full_32_bit_zero_test();
  case_dispatch_word_is_reread();
  case_one_level_dereference_decoy();
  case_register_restored_on_both_paths();
  case_register_and_stack_state_via_trampolines();

  std::printf("\n%d checks, %d failure(s)\n", g_checks, g_failures);
  if (g_failures != 0) {
    std::printf("MODEL TEST FAILED\n");
    return 1;
  }
  std::printf("MODEL TEST PASSED\n");
  return 0;
}
