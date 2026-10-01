// PKG-SWARM-W2-00F999E0 -- VA 0x00f999e0
// Behavioural model test for FUN_00f999e0 @ 0x00f999e0.
//
// EVERY direct callee is defined here as an observer, so the test sees every transfer
// the reconstruction makes, with which arguments, in which order, and decides what it
// does to memory:
//
//   * 0x00f48a70 is a global getter (`MOV EAX,ds:0x16c8eb0 ; RET`, six bytes). The
//     observer returns a fixture-chosen word; the test then requires that exact word
//     to arrive as the RECEIVER of the next call, which is the one-level/two-level
//     distinction that matters here.
//   * 0x00f699b0 is a zero-argument __thiscall on ECX. The observer records the
//     pointer ECX carried.
//   * the two table slots are called through ASSEMBLY STUBS, because the shape being
//     tested is the shape inline C cannot see: the stub records ECX and the word at
//     entry+4 verbatim, before any C code runs, and then tail-routes to a plain cdecl
//     worker. That is what makes "the receiver is in ECX", "the selector is the whole
//     byte 7 at entry+4" and "the second slot is handed nothing at all" measurements
//     rather than assertions.
//
// What is asserted is what the 80-instruction listing fixes, and nothing more:
//
//   * the two direct calls, their order, and that the value 0x00f48a70 returns is the
//     RECEIVER of 0x00f699b0 and not a member of this function's own receiver;
//   * both dispatches: the receiver's +0x00 is a table ADDRESS, the slot displacement
//     indexes that table, ECX carries the receiver, the selector is a stack word the
//     callee owns, and the table word is read TWICE with a call in between;
//   * the five gates, their polarity, their order, and the fact that the +0x370 gate
//     compares against AL, which is provably zero at that point;
//   * the compare loop: a group rejects iff BOTH of its pairs are ORDERED-equal, in
//     all four pair combinations, plus the two cases (+0.0/-0.0 and NaN) where a
//     byte-wise reading of the same four bytes disagrees;
//   * the exact set of twenty-four scanned group bases, pinned from BOTH sides: every
//     one of them rejects, and every neighbouring base that is not scanned does not;
//   * that the body writes NOTHING to the receiver, byte for byte over the whole
//     modelled receiver;
//   * the return register's composition: one flag byte over the last callee's word
//     masked to its high twenty-four bits;
//   * the ABI: a bare RET, so ESP is unchanged across the call (MEASURED), and the
//     receiver in ECX.
//
// What is NOT asserted, and why:
//
//   * That 0x16c8eb0 holds any particular object, or that 0x00f699b0 returns what its
//     own body computes. 0x00f699b0's body is a DIFFERENT function and its global
//     state is not in this body; the test substitutes an observer and asserts only the
//     receiver it was handed.
//   * That the runtime object holds 0x00fa0e60 at slot +0x4c and 0x00fa0d80 at +0x30.
//     Those are the entries this class's table holds in the image, but a derived class
//     may override either, so the test supplies its own table and asserts only which
//     SLOT DISPLACEMENT the reconstruction indexes.
//   * Anything about what the twenty-four groups MEAN. The record is bounds_only and
//     no field is named, so the test pins the layout and never the meaning.
//   * The high three bytes of the return register as the COMPILER leaves them. The
//     model publishes the word it composes through dead_return_word(); the trampoline
//     reads only AL out of EAX, because how the C++ return type lands in the register
//     is the compiler's business and not a claim about the machine.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk it.
// Each names a wrong reconstruction it is aimed at:
//
//   A  gate 1 false. The 0x00f999f3 exit must be reached with NO further transfer: a
//      model that evaluates the table slots, or the flag bytes, before the first gate
//      shows up as a callee count of 1 instead of 2.
//   B  AL vs bit 0. 0x00f999ef/0x00f99a02/0x00f99a17 are `TEST AL,AL`, so all eight
//      bits count. Driven with 0x00000100 (AL clear, low word nonzero) and
//      0x0000ff00 (AL clear) against 0x0000fe00 (AL set, bit 0 clear). A `& 1` gate
//      fails all three.
//   C  which callee and which argument, and WHICH OF THE TWO SLOTS IS HANDED A STACK
//      WORD AT ALL. The stubs measure ECX and the word at their own entry+4, and the
//      zero-argument half is asserted where the i386 calling convention puts it: the
//      +0x4c callee must find the selector 7 at its own [entry+4] and the +0x30 callee
//      must find neither the selector nor the receiver there, so nothing was pushed for
//      it. That replaced an assertion that compared the two stubs' entry ESPs against
//      each other, which on x86-32 at -O0 reads the compiler's call-site scratch layout
//      rather than the machine: clang never materialises a push for a callee-cleaned
//      argument, so the two entry ESPs are equal there (measured: g++ 16, clang++ 0)
//      and the strict inequality the check needed is unsatisfiable.
//   D  which slot, and which level. A table with a distinct decoy at every index
//      except +0x4c and +0x30; plus a table whose every index is a decoy; plus a
//      receiver whose +0x00 is a function ADDRESS rather than a table address.
//   E  gate 3 (the +0x370 byte) with decoy bytes at +0x36f, +0x371, +0x4f3, +0x4f5.
//   F  gate 2's polarity, against gate 1's: gate 2 is 0->0 and gate 1 is nonzero->1.
//   G  gate 4 (the +0x30 slot) and gate 5 (the +0x4f4 byte).
//   H  the compare polarity, in all four pair combinations. This is the case the
//      committed decompilation inverts, so it is the one that matters most.
//   I  a quiet NaN against its own bit pattern: ordered-unequal, so the group passes.
//   J  +0.0f against -0.0f: ordered-equal, so the group rejects.
//   K  the scanned set, from both sides: all twenty-four bases reject, and their
//      neighbours one group away -- including the next outer index and the third
//      inner index -- do not.
//   L  the dead return word, on every exit, with each callee poisoned in turn.
//   M  the receiver is read-only, byte for byte.
//   N  the ABI: ESP across the call, and the receiver in ECX.
//   O  the table word is read twice: the +0x4c observer rewrites the receiver's +0x00
//      and the +0x30 call must follow the SECOND table.

#include "sw2_00f999e0_types.hpp"

#include <cstdio>
#include <cstring>
#include <limits>

namespace ns = openspore::reconstruction::pkg_swarm_w2_00f999e0;
using ns::Receiver;
using ns::Word;

// -- the observation record ------------------------------------------------------
struct Observation {
  int global_getter_calls = 0;
  int direct_predicate_calls = 0;
  int slot_4c_calls = 0;
  int slot_30_calls = 0;
  int decoy_calls = 0;

  // The receiver each transfer was actually handed, as the CALLER sees it.
  std::uintptr_t direct_predicate_receiver = 0;
  // What the assembly stubs read out of the machine state, before any C code runs.
  std::uint32_t stub_ecx = 0;
  std::uint32_t stub_arg_word = 0;
  std::uint32_t stub_esp = 0;
  // The ESP the +0x30 stub saw, kept so the test can require it to equal the +0x4c
  // stub's: the body pushes nothing for the second slot.
  std::uint32_t slot_30_esp = 0;
  // Decoy identity, so a failure names WHICH neighbouring slot was taken.
  const void* decoy_at = nullptr;

  // Fixtures, not claims.
  Word global_getter_result = 0;
  Word direct_predicate_result = 0;
  Word slot_4c_result = 0;
  Word slot_30_result = 0;
  Word slot_30_result_b = 0;
  // When set, the +0x4c observer overwrites the receiver's table word with this.
  bool retarget_table = false;
  std::uint8_t* retarget_value = nullptr;

  // Counters and captured machine state only: `run` uses this, so a case that arms a
  // callee's return value before calling run keeps it.
  void reset_counters() {
    global_getter_calls = 0;
    direct_predicate_calls = 0;
    slot_4c_calls = 0;
    slot_30_calls = 0;
    decoy_calls = 0;
    direct_predicate_receiver = 0;
    stub_ecx = 0;
    stub_arg_word = 0;
    stub_esp = 0;
    slot_30_esp = 0;
    decoy_at = nullptr;
  }

  // Everything, fixtures included. `build_open` uses this, so every case starts from
  // the same open-gate state.
  void reset() { *this = Observation(); }
};

Observation g_seen;


// Machine state the assembly stubs publish, one triple per stub: what ECX carried,
// what word sat at entry+4, and what ESP was. They are plain C-linkage words so the
// stubs can name them, and they exist because the shape under test is the shape a C
// observer cannot see: the callee's entry state, read before any C code runs.
// Declared, never defined in C++: an `extern "C"` variable may not carry an
// initializer, and a file-scope `static` is emitted under a mangled local name a
// top-level asm cannot reach. The storage is therefore declared with `.comm` in
// the assembly block below and is common, so it starts at zero as the C++ side
// assumes.
extern "C" std::uint32_t g_stub_ecx_4c;
extern "C" std::uint32_t g_stub_arg_word_4c;
extern "C" std::uint32_t g_stub_esp_4c;
extern "C" std::uint32_t g_stub_ecx_30;
extern "C" std::uint32_t g_stub_arg_word_30;
extern "C" std::uint32_t g_stub_esp_30;
extern "C" std::uint32_t g_stub_ecx_30b;
extern "C" std::uint32_t g_stub_arg_word_30b;
extern "C" std::uint32_t g_stub_esp_30b;
extern "C" std::uint32_t g_stub_ret_4c;
extern "C" std::uint32_t g_stub_ret_30;
extern "C" std::uint32_t g_stub_ret_30b;

// The assembly stubs, declared so C++ can take their addresses and plant them in a
// table. The definitions are in the asm block below.
extern "C" void sw2_slot_4c_stub();
extern "C" void sw2_slot_30_stub();
extern "C" void sw2_slot_30b_stub();

// The second table's address, so the +0x4c worker can point the receiver's table word
// at it. A fixture, not a claim about the machine.
std::uint8_t* g_table_b_address = nullptr;

extern "C" {

// Two thiscall stubs, written in assembly so the entry state is exactly what the
// machine hands a callee. Each records ECX, the word at entry+4 and ESP, then tail
// routes to a plain cdecl worker. `ret` with no immediate is deliberate: it is the
// machine's own shape for a callee that owns its argument word.
// The stubs address their record words PC-relatively (`symbol - 1b(%eax)` with EIP
// fetched by a call/pop pair), so nothing in this block needs an absolute relocation
// and the test binary links clean as a PIE. `.comm` gives the words common storage,
// which starts at zero, which is what the C++ declarations assume.
// The stubs address their record words PC-relatively (`symbol - 1b(%eax)` with EIP
// fetched by a call/pop pair), so nothing in this block needs an absolute relocation
// and the test binary links clean as a PIE. `.comm` gives the words common storage,
// which starts at zero, which is what the C++ declarations assume.
//
// The +0x4c stub ends `ret $4` and the +0x30 stubs end `ret`, because that IS the
// difference between the two slots in the machine: this body pushes the selector word
// and never drops it, so the +0x4c callee owns it (the entry this class's table holds
// there ends `C2 04 00`), while nothing is pushed for +0x30 and its entry ends a bare
// `C3`. GCC's __thiscall on a function POINTER type is callee-cleanup on this
// toolchain, so the reconstruction relies on exactly that, and a stub that returned
// bare would leave four bytes on the stack per call and corrupt the frame -- which is
// a real property of the ABI, not a harness detail.
// The stubs address their record words PC-relatively (`symbol - <label>(%eax)` with the
// label address fetched by a call/pop pair), so nothing in this block needs an absolute
// relocation and the test binary links clean as a PIE. `.comm` gives the words common
// storage, which starts at zero, which is what the C++ declarations assume.
//
// ECX is recorded FIRST, while it is still intact, because the cdecl worker each stub
// routes to clobbers it. The +0x4c stub ends `ret $4` and the two +0x30 stubs end
// `ret`, because that IS the difference between the slots in the machine: this body
// pushes the selector word and never drops it, so the +0x4c callee owns it (the entry
// this class's table holds at that slot ends `C2 04 00`), while nothing is pushed for
// +0x30 and its entry ends a bare `C3`. GCC's __thiscall on a function POINTER type is
// callee-cleanup on this toolchain, so the reconstruction relies on exactly that, and a
// stub that returned bare would leave four bytes on the stack per call and corrupt the
// frame -- a real property of the ABI, not a harness detail.
// Three thiscall stubs, written in assembly so the entry state is exactly what the
// machine hands a callee. Each records ECX, the word at entry+4 and ESP, runs a plain
// cdecl worker, and returns the worker's value in EAX.
//
// Two details are load-bearing, and both were got wrong on the first build:
//
//  * The worker's return value must survive the fetch of a label address. The fetch is
//    a call/pop pair and a call does not clobber EAX, so EDX carries the label address
//    and EAX keeps the value. Popping the label address INTO EAX and then storing EAX
//    publishes a code address as the callee's return, which the caller's gate then
//    reads as "nonzero" -- the failure this test exists to catch, arriving from the
//    harness instead of from the model.
//  * The +0x4c stub ends `ret $4` and the two +0x30 stubs end `ret`, because that IS
//    the difference between the slots in the machine: this body pushes the selector
//    word and never drops it, so the +0x4c callee owns it (the entry this class's table
//    holds at that slot ends `C2 04 00`), while nothing is pushed for +0x30 and its
//    entry ends a bare `C3`. GCC's __thiscall on a function POINTER type is
//    callee-cleanup on this toolchain, so the reconstruction relies on exactly that,
//    and a bare-returning stub would leave four bytes on the stack per call and
//    corrupt the frame -- a real property of the ABI, not a harness detail.
//
// The record words are addressed PC-relatively (`symbol - <label>(%edx)`), so no
// absolute relocation is needed and the test binary links clean as a PIE. `.comm` gives
// the words common storage, which starts at zero, as the C++ side assumes.
asm(".comm g_stub_ecx_4c,4,4\n.comm g_stub_arg_word_4c,4,4\n.comm g_stub_esp_4c,4,4\n"
    ".comm g_stub_ecx_30,4,4\n.comm g_stub_arg_word_30,4,4\n.comm g_stub_esp_30,4,4\n"
    ".comm g_stub_ecx_30b,4,4\n.comm g_stub_arg_word_30b,4,4\n.comm g_stub_esp_30b,4,4\n"
    ".comm g_stub_ret_4c,4,4\n.comm g_stub_ret_30,4,4\n.comm g_stub_ret_30b,4,4\n"
    ".text\n"
    ".globl sw2_slot_4c_stub\n"
    ".type sw2_slot_4c_stub, @function\n"
    "sw2_slot_4c_stub:\n"
    "  call 1f\n"
    "1:\n"
    "  popl %eax\n"
    "  movl %ecx, g_stub_ecx_4c - 1b(%eax)\n"
    "  pushl 4(%esp)\n"
    "  pushl g_stub_ecx_4c - 1b(%eax)\n"
    "  call sw2_slot_4c_worker\n"
    "  addl $8, %esp\n"
    "  call 2f\n"
    "2:\n"
    "  popl %edx\n"
    "  movl %eax, g_stub_ret_4c - 2b(%edx)\n"
    "  movl 4(%esp), %ecx\n"
    "  movl %ecx, g_stub_arg_word_4c - 2b(%edx)\n"
    "  movl %esp, %ecx\n"
    "  movl %ecx, g_stub_esp_4c - 2b(%edx)\n"
    "  movl g_stub_ret_4c - 2b(%edx), %eax\n"
    "  ret $4\n"
    ".size sw2_slot_4c_stub, .-sw2_slot_4c_stub\n"
    ".globl sw2_slot_30_stub\n"
    ".type sw2_slot_30_stub, @function\n"
    "sw2_slot_30_stub:\n"
    "  call 1f\n"
    "1:\n"
    "  popl %eax\n"
    "  movl %ecx, g_stub_ecx_30 - 1b(%eax)\n"
    "  pushl g_stub_ecx_30 - 1b(%eax)\n"
    "  call sw2_slot_30_worker\n"
    "  addl $4, %esp\n"
    "  call 2f\n"
    "2:\n"
    "  popl %edx\n"
    "  movl %eax, g_stub_ret_30 - 2b(%edx)\n"
    "  movl 4(%esp), %ecx\n"
    "  movl %ecx, g_stub_arg_word_30 - 2b(%edx)\n"
    "  movl %esp, %ecx\n"
    "  movl %ecx, g_stub_esp_30 - 2b(%edx)\n"
    "  movl g_stub_ret_30 - 2b(%edx), %eax\n"
    "  ret\n"
    ".size sw2_slot_30_stub, .-sw2_slot_30_stub\n"
    ".globl sw2_slot_30b_stub\n"
    ".type sw2_slot_30b_stub, @function\n"
    "sw2_slot_30b_stub:\n"
    "  call 1f\n"
    "1:\n"
    "  popl %eax\n"
    "  movl %ecx, g_stub_ecx_30b - 1b(%eax)\n"
    "  pushl g_stub_ecx_30b - 1b(%eax)\n"
    "  call sw2_slot_30b_worker\n"
    "  addl $4, %esp\n"
    "  call 2f\n"
    "2:\n"
    "  popl %edx\n"
    "  movl %eax, g_stub_ret_30b - 2b(%edx)\n"
    "  movl 4(%esp), %ecx\n"
    "  movl %ecx, g_stub_arg_word_30b - 2b(%edx)\n"
    "  movl %esp, %ecx\n"
    "  movl %ecx, g_stub_esp_30b - 2b(%edx)\n"
    "  movl g_stub_ret_30b - 2b(%edx), %eax\n"
    "  ret\n"
    ".size sw2_slot_30b_stub, .-sw2_slot_30b_stub\n");
}  // extern "C"


// The two direct callees and the six slot decoys live INSIDE the package namespace,
// because that is where the package header declares them and C++ does not allow a
// namespaced function to be defined from outside it.
namespace openspore::reconstruction::pkg_swarm_w2_00f999e0 {
// -- the two direct callees ------------------------------------------------------
// 0x00f48a70: six bytes, `MOV EAX,ds:0x16c8eb0 ; RET`. The fixture chooses the value;
// nothing here claims what the global holds.
extern "C" PKG_SW2_00F999E0_CDECL Word global_object_00f48a70(void) {
  ++g_seen.global_getter_calls;
  return g_seen.global_getter_result;
}

// 0x00f699b0: a zero-argument __thiscall on ECX. The observer records the pointer ECX
// carried, which is the measurement of "the value the getter returned became a
// RECEIVER, one level below this function's own".
extern "C" PKG_SW2_00F999E0_THISCALL Word global_predicate_00f699b0(void* receiver) {
  ++g_seen.direct_predicate_calls;
  g_seen.direct_predicate_receiver = reinterpret_cast<std::uintptr_t>(receiver);
  return g_seen.direct_predicate_result;
}

// -- the decoys, one identity per neighbouring slot -------------------------------
// Each records WHICH of them was called, so a failure names the slot rather than just
// saying "a decoy fired". All three take the receiver in ECX through the same
// convention the real slots do, so a model that indexes the wrong slot reaches one of
// them rather than crashing.
extern "C" PKG_SW2_00F999E0_THISCALL Word decoy_below_4c(Receiver* self, Word selector) {
  ++g_seen.decoy_calls;
  g_seen.decoy_at = reinterpret_cast<const void*>(&decoy_below_4c);
  g_seen.stub_arg_word = selector;
  g_seen.stub_ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(self));
  return 0;
}
extern "C" PKG_SW2_00F999E0_THISCALL Word decoy_above_4c(Receiver* self, Word selector) {
  ++g_seen.decoy_calls;
  g_seen.decoy_at = reinterpret_cast<const void*>(&decoy_above_4c);
  g_seen.stub_arg_word = selector;
  g_seen.stub_ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(self));
  return 0;
}
extern "C" PKG_SW2_00F999E0_THISCALL Word decoy_below_30(Receiver* self) {
  ++g_seen.decoy_calls;
  g_seen.decoy_at = reinterpret_cast<const void*>(&decoy_below_30);
  g_seen.stub_ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(self));
  return 1;
}
extern "C" PKG_SW2_00F999E0_THISCALL Word decoy_above_30(Receiver* self) {
  ++g_seen.decoy_calls;
  g_seen.decoy_at = reinterpret_cast<const void*>(&decoy_above_30);
  g_seen.stub_ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(self));
  return 1;
}
extern "C" PKG_SW2_00F999E0_THISCALL Word decoy_elsewhere_first(Receiver* self, Word selector) {
  ++g_seen.decoy_calls;
  g_seen.decoy_at = reinterpret_cast<const void*>(&decoy_elsewhere_first);
  g_seen.stub_arg_word = selector;
  g_seen.stub_ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(self));
  return 0;
}
extern "C" PKG_SW2_00F999E0_THISCALL Word decoy_elsewhere_second(Receiver* self) {
  ++g_seen.decoy_calls;
  g_seen.decoy_at = reinterpret_cast<const void*>(&decoy_elsewhere_second);
  g_seen.stub_ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(self));
  return 1;
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00f999e0

using ns::decoy_below_30;
using ns::decoy_below_4c;
using ns::decoy_above_30;
using ns::decoy_above_4c;
using ns::decoy_elsewhere_first;
using ns::decoy_elsewhere_second;


namespace {

int g_failures = 0;

void fail(const char* what) {
  std::fprintf(stderr, "FAILED: %s\n", what);
  ++g_failures;
}

void check(bool ok, const char* what) {
  if (!ok) {
    fail(what);
  }
}

void check_eq_u32(Word got, Word want, const char* what) {
  if (got != want) {
    std::fprintf(stderr, "FAILED: %s (got 0x%08x, want 0x%08x)\n", what, got, want);
    ++g_failures;
  }
}

void check_eq_int(long got, long want, const char* what) {
  if (got != want) {
    std::fprintf(stderr, "FAILED: %s (got %ld, want %ld)\n", what, got, want);
    ++g_failures;
  }
}

void check_eq_addr(std::uintptr_t got, const void* want, const char* what) {
  const std::uintptr_t expected = reinterpret_cast<std::uintptr_t>(want);
  if (got != expected) {
    std::fprintf(stderr, "FAILED: %s (got %p, want %p)\n", what,
                 reinterpret_cast<const void*>(got), want);
    ++g_failures;
  }
}

// The machine's own displacements, as literals in the harness, so that a wrong one is
// a wrong one HERE and not in the reconstruction.
constexpr std::size_t kTableWord = 0x0;      // MOV EAX,[ESI]
constexpr std::size_t kFlagByte = 0x370;     // CMP BYTE [ESI+0x370],AL
constexpr std::size_t kSecondFlagByte = 0x4f4;  // CMP BYTE [ESI+0x4f4],0
constexpr std::size_t kCursor = 0x438;       // ADD ESI,0x438
constexpr std::size_t kOuterStride = 0x10;   // ADD ESI,0x10
constexpr std::size_t kInnerBack = 0xc0;     // LEA ECX,[ESI+0xffffff40]
constexpr std::size_t kGroupStride = 0x60;   // ADD ECX,0x60
constexpr std::size_t kLead = 0x4;           // the group's first float is 4 below
constexpr std::size_t kFourth = 0x5c;        // the fourth group's base
constexpr std::size_t kPairSpan = 0x8;       // UCOMISS operand, 8 past the left
constexpr unsigned kOuterCount = 6;          // CMP EDI,0x6
constexpr unsigned kInnerCount = 2;          // CMP EDX,0x2
constexpr std::size_t kSelector = 0x7;       // PUSH 0x7
// The four group bases, relative to the receiver: inner #0, inner #1, the first
// unrolled group and the second unrolled group, each for every outer index.
constexpr std::size_t kGroup0Base = kCursor - kInnerBack - kLead;  // 0x374
constexpr std::size_t kGroup1Base = kGroup0Base + kGroupStride;    // 0x3d4
constexpr std::size_t kGroup2Base = kGroup1Base + kGroupStride;    // 0x434
constexpr std::size_t kGroup3Base = kGroup2Base + kGroupStride;    // 0x494

static_assert(kGroup0Base == 0x374, "inner group 0 base is receiver + 0x374");
static_assert(kGroup3Base == 0x494, "the fourth group base is receiver + 0x494");
static_assert(kCursor - kLead == 0x434, "the third group base is receiver + 0x434");

// THE INNER TRIP COUNT, pinned to the instruction form that fixes it. The inner stride
// 0x60 is exactly six times the outer stride 0x10, so no count can be read off the
// address set: "inner index 2" is the base of the first UNROLLED group and "outer index
// 6" is "inner index 0 one row down". The count therefore comes from the listing's own
// form -- `CMP EDX,0x2` at 0x00f99a61, a signed JL against a counter that is zeroed at
// 0x00f99a30 and incremented at 0x00f99a5d BEFORE the compare -- and the two asserts
// below bind the harness's copy of that constant to the layout it implies, so a
// kInnerCount that disagreed with the group families would be a build error rather than
// a silently differently-shaped fixture. The RUNTIME half (a group at inner index 1 is
// reached at the TOP outer index, where no outer iteration can produce its address) is
// asserted in case K, and the aliasing that stops the address set from pinning the count
// from above is asserted there too.
static_assert(kInnerCount == 2,
              "CMP EDX,0x2 at 0x00f99a61: the inner loop's trip count, incremented first");
static_assert(kGroup0Base + (kInnerCount - 1) * kGroupStride == kGroup1Base,
              "the LAST inner row sits kInnerCount-1 group strides below the first");
static_assert(kGroup1Base + kGroupStride == kGroup2Base,
              "the first unrolled group is one group stride past the last inner row, "
              "which is why the inner count cannot be read off the address set");


// -- the workers the stubs route to ----------------------------------------------
// Plain cdecl, so the stub's explicit push of the two words is the whole convention.
extern "C" Word sw2_slot_4c_worker(Receiver* self, Word selector);
extern "C" Word sw2_slot_30_worker(Receiver* self);
extern "C" Word sw2_slot_30b_worker(Receiver* self);

extern "C" Word sw2_slot_4c_worker(Receiver* self, Word selector) {
  ++g_seen.slot_4c_calls;
  g_seen.stub_arg_word = selector;
  if (g_seen.retarget_table && g_seen.retarget_value != nullptr) {
    Word address = static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_table_b_address));
    std::memcpy(g_seen.retarget_value, &address, sizeof address);
  }
  g_seen.stub_ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(self));
  return g_seen.slot_4c_result;
}

extern "C" Word sw2_slot_30_worker(Receiver* self) {
  ++g_seen.slot_30_calls;
  g_seen.stub_ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(self));
  return g_seen.slot_30_result;
}

extern "C" Word sw2_slot_30b_worker(Receiver* self) {
  ++g_seen.slot_30_calls;
  g_seen.stub_ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(self));
  return g_seen.slot_30_result_b;
}

// -- the ABI trampoline ----------------------------------------------------------
// Puts the receiver in ECX, samples ESP on both sides of the call and reads the whole
// of EAX afterwards, so the cleanup is MEASURED rather than asserted as a convention
// and the returned BYTE is read out of the register rather than out of the declared
// type. The trampoline pushes nothing, because the reconstruction takes no ordinary
// stack argument, so any imbalance it reports is the reconstruction's.
struct AbiProbe {
  std::uint32_t esp_before;
  std::uint32_t esp_after;
  std::uint32_t eax;
};

extern "C" void probe_re_00f999e0(Receiver* receiver, AbiProbe* probe) {
  // The receiver is pushed onto the stack FIRST, so the register the compiler picks
  // for it can be anything; ECX is then loaded from that pushed word, which is what
  // the machine's own first instruction sees. All three outputs are early-clobber and
  // "ecx" is clobbered, so none of them can land in a register the sequence writes.
  __asm__ volatile(
      "pushl  %[rec]\n\t"
      "movl   (%%esp), %%ecx\n\t"
      "movl   %%esp, %[before]\n\t"
      "call   re_00f999e0\n\t"
      "movl   %%esp, %[after]\n\t"
      "movl   %%eax, %[out]\n\t"
      "addl   $4, %%esp\n\t"
      : [before] "=&r"(probe->esp_before),
        [after] "=&r"(probe->esp_after),
        [out] "=&r"(probe->eax)
      : [rec] "r"(receiver)
      : "memory", "cc", "ecx");
}

// -- the fixture ------------------------------------------------------------------
// The receiver occupies the first bytes of the arena, so a byte-level assertion over
// it is a byte-level assertion over the model. The two tables sit far above it, so a
// table word can never be confused with a receiver byte.
struct alignas(16) Arena {
  std::uint8_t bytes[0x3000];
};

constexpr std::size_t kTableOffsetA = 0x2000;
constexpr std::size_t kTableOffsetB = 0x2100;
constexpr std::size_t kTableBytes = 0x100;  // 64 slots, which covers +0x4c

struct Fixture {
  Arena arena{};
  std::uint8_t snapshot[0x600];

  std::uint8_t* self() { return arena.bytes; }
  Receiver* receiver() { return reinterpret_cast<Receiver*>(arena.bytes); }
  std::uint8_t* table_a() { return arena.bytes + kTableOffsetA; }
  std::uint8_t* table_b() { return arena.bytes + kTableOffsetB; }

  // A table with a distinct decoy at every index except the two the listing uses.
  void build_table(std::uint8_t* table) {
    std::memset(table, 0, kTableBytes);
    Word word = 0;
    for (std::size_t offset = 0; offset < kTableBytes; offset += 4) {
      const void* target = reinterpret_cast<const void*>(&decoy_elsewhere_first);
      if (offset == 0x2c) target = reinterpret_cast<const void*>(&decoy_below_30);
      if (offset == 0x34) target = reinterpret_cast<const void*>(&decoy_above_30);
      if (offset == 0x48) target = reinterpret_cast<const void*>(&decoy_below_4c);
      if (offset == 0x50) target = reinterpret_cast<const void*>(&decoy_above_4c);
      std::memcpy(&word, &target, sizeof word);
      std::memcpy(table + offset, &word, sizeof word);
    }
    // The two real slots, as words in the table.
    const void* first = reinterpret_cast<const void*>(&sw2_slot_4c_stub);
    std::memcpy(table + 0x4c, &first, sizeof word);
    const void* second = reinterpret_cast<const void*>(&sw2_slot_30_stub);
    std::memcpy(table + 0x30, &second, sizeof word);
  }

  // Every index a decoy, so ANY dispatch is caught. Used for the wrong-level case.
  //
  // The decoy at +0x30 is the ZERO-STACK-WORD one, and that is not a preference: the two
  // slots are called with different stack shapes and both conventions in use here are
  // callee-cleanup, so a callee pops exactly as many words as it DECLARES. The +0x4c
  // site pushes the selector and its callee owns it (the machine's own entry ends
  // `C2 04 00`, which sw2_slot_4c_stub reproduces with `ret $4`); the +0x30 site pushes
  // nothing and its callee ends a bare `ret`. A one-word decoy planted at +0x30
  // therefore pops four bytes the call site never pushed, and the reconstruction's frame
  // is four bytes out when its epilogue runs -- so the body returns through a clobbered
  // slot. g++ happens to have twelve bytes of scratch around the +0x4c call and absorbs
  // it; clang++ has none and the process dies before a single check is reported. The
  // table still holds a decoy at EVERY index, which is what this case is for, and the
  // +0x30 slot still holds a decoy; only the decoy's arity now matches the slot it
  // occupies, so a wrong dispatch is still caught and reported rather than fatal.
  void build_hostile_table(std::uint8_t* table) {
    std::memset(table, 0, kTableBytes);
    Word word = 0;
    for (std::size_t offset = 0; offset < kTableBytes; offset += 4) {
      const void* target = reinterpret_cast<const void*>(&decoy_elsewhere_first);
      if (offset == 0x30) target = reinterpret_cast<const void*>(&decoy_elsewhere_second);
      std::memcpy(&word, &target, sizeof word);
      std::memcpy(table + offset, &word, sizeof word);
    }
  }

  // The default fixture: all five gates open and no group rejecting, with every float
  // in the scan window distinct so no pair is accidentally ordered-equal.
  void build_open() {
    std::memset(arena.bytes, 0, sizeof arena.bytes);
    build_table(table_a());
    build_table(table_b());
    g_table_b_address = table_b();

    Word table_a_address = 0;
    const void* a = table_a();
    std::memcpy(&table_a_address, &a, sizeof table_a_address);
    std::memcpy(self() + kTableWord, &table_a_address, sizeof table_a_address);

    // Distinct, and never equal to their partner eight bytes away.
    for (std::size_t offset = 0x300; offset < 0x600; offset += 4) {
      const float value = static_cast<float>(offset) + 0.5f;
      std::memcpy(arena.bytes + offset, &value, sizeof value);
    }
    // Gate 3 wants 0 and gate 5 wants nonzero; the neighbouring decoys are the
    // opposite, so a model that reads either of them takes the other branch.
    arena.bytes[kFlagByte] = 0x00;
    arena.bytes[kFlagByte - 1] = 0xff;
    arena.bytes[kFlagByte + 1] = 0xff;
    arena.bytes[kSecondFlagByte] = 0x01;
    arena.bytes[kSecondFlagByte - 1] = 0x00;
    arena.bytes[kSecondFlagByte + 1] = 0x00;

    g_seen.reset();
    g_seen.global_getter_result = 0x0000a5a5u;  // AL is set -> gate 1 opens
    g_seen.direct_predicate_result = 1u;
    g_seen.slot_4c_result = 0u;  // AL is clear -> gate 2 opens
    g_seen.slot_30_result = 1u;  // AL is set -> gate 4 opens
  }

  std::uint8_t* group(std::size_t base) { return self() + base; }

  // A group whose pair 0 is (left, left) and pair 1 is (right, right) when the two
  // flags say so, so all four combinations are reachable from one helper.
  void plant_group(std::size_t base, bool pair0_equal, bool pair1_equal) {
    const float a0 = 100.0f;
    const float a2 = pair0_equal ? 100.0f : 101.0f;
    const float a1 = 200.0f;
    const float a3 = pair1_equal ? 200.0f : 201.0f;
    std::uint8_t* g = self() + base;
    std::memcpy(g + 0, &a0, sizeof a0);
    std::memcpy(g + 4, &a1, sizeof a1);
    std::memcpy(g + kPairSpan, &a2, sizeof a2);
    std::memcpy(g + 4 + kPairSpan, &a3, sizeof a3);
  }

  void take_snapshot() {
    std::memcpy(snapshot, arena.bytes, sizeof snapshot);
  }

  void check_untouched(const char* what) {
    for (std::size_t i = 0; i < sizeof snapshot; ++i) {
      if (arena.bytes[i] != snapshot[i]) {
        std::fprintf(stderr, "FAILED: %s (receiver byte +0x%zx changed)\n", what, i);
        ++g_failures;
        return;
      }
    }
  }
};

// The four scanned bases for one outer index.
void group_bases(unsigned outer_index, std::size_t out[4]) {
  const std::size_t step = kCursor + outer_index * kOuterStride;
  out[0] = step - kInnerBack - kLead;
  out[1] = out[0] + kGroupStride;
  out[2] = step - kLead;
  out[3] = step + kFourth;
}

// One run of the reconstruction through the trampoline, with the observation reset.
std::uint32_t run(Fixture& fixture, AbiProbe* probe) {
  // Counters only: the callee return values are per-case inputs and re-arming them
  // here would silently undo whatever the case just set.
  g_seen.reset_counters();
  probe->esp_before = 0;
  probe->esp_after = 0;
  probe->eax = 0;
  probe_re_00f999e0(fixture.receiver(), probe);
  return probe->eax;
}

}  // namespace

int main() {
  // =====================================================================
  // A / F / G: the five gates, their polarity, their order, and the short
  // circuit. The callee counts ARE the order: no gate is evaluated before the
  // one in front of it.
  // =====================================================================
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    // Gate 1 false: nothing after it may be evaluated.
    g_seen.direct_predicate_result = 0u;
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "A: gate 1 false returns 0");
    check_eq_int(g_seen.global_getter_calls, 1, "A: the global getter is called once");
    check_eq_int(g_seen.direct_predicate_calls, 1, "A: the direct predicate is called once");
    check_eq_int(g_seen.slot_4c_calls, 0, "A: the +0x4c slot is not reached");
    check_eq_int(g_seen.slot_30_calls, 0, "A: the +0x30 slot is not reached");
    check_eq_int(g_seen.decoy_calls, 0, "A: no decoy is reached");
  }
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    // Gate 2, opposite polarity: the slot returning NONZERO exits.
    g_seen.slot_4c_result = 1u;
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "F: gate 2 nonzero returns 0");
    check_eq_int(g_seen.slot_4c_calls, 1, "F: the +0x4c slot is called once");
    check_eq_int(g_seen.slot_30_calls, 0, "F: the +0x30 slot is not reached");
  }
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    // Gate 3: the +0x370 byte.
    f.self()[kFlagByte] = 0x01;
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "E: a nonzero +0x370 byte returns 0");
    check_eq_int(g_seen.slot_30_calls, 0, "E: the +0x30 slot is not reached");
    // And the reverse: the neighbouring decoys are nonzero, so a model that reads
    // either of them exits while the machine does not.
    f.build_open();
    f.self()[kFlagByte] = 0x00;
    f.self()[kFlagByte - 1] = 0x00;
    f.self()[kFlagByte + 1] = 0x00;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "E: +0x370 read, not its neighbours, so the scan runs");
  }
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    // Gate 4: the +0x30 slot returning zero exits.
    g_seen.slot_30_result = 0u;
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "G: the +0x30 slot returning zero returns 0");
    // Gate 5: the +0x4f4 byte, against its neighbours.
    f.build_open();
    f.self()[kSecondFlagByte] = 0x00;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "G: a zero +0x4f4 byte returns 0");
    f.build_open();
    f.self()[kSecondFlagByte - 1] = 0xff;
    f.self()[kSecondFlagByte + 1] = 0xff;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "G: +0x4f4 read, not its neighbours, so the scan runs");
  }
  {
    // The open fixture, unmolested, must run the whole scan and return 1.
    Fixture f;
    f.build_open();
    AbiProbe probe;
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "all gates open and no group equal returns 1");
    check_eq_int(g_seen.slot_4c_calls, 1, "the +0x4c slot is called exactly once");
    check_eq_int(g_seen.slot_30_calls, 1, "the +0x30 slot is called exactly once");
    check_eq_int(g_seen.decoy_calls, 0, "no decoy slot is reached");
  }

  // =====================================================================
  // B: AL is the gate, all eight bits of it, not bit 0.
  // =====================================================================
  {
    Fixture f;
    AbiProbe probe;
    // Gate 1 is `TEST AL,AL ; JNZ <continue>`, so a CLEAR AL closes it. A word of
    // 0x00000100 has a clear AL and a nonzero low word: `TEST AL,AL` reads it as
    // zero, `word & 1` does not.
    f.build_open();
    g_seen.direct_predicate_result = 0x00000100u;
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "B: a 0x100 word has AL clear, so gate 1 closes");
    check_eq_int(g_seen.slot_30_calls, 0, "B: the scan is not reached");
    // AL set, bit 0 clear: `TEST AL,AL` reads it as nonzero, `word & 1` does not.
    f.build_open();
    g_seen.direct_predicate_result = 0x000000feu;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "B: a 0xfe word has AL set, so gate 1 opens");
    check_eq_int(g_seen.slot_30_calls, 1, "B: the scan is reached");
    // Gate 2 has the OPPOSITE polarity -- `JNZ <return 0>` -- so the same two words
    // must close and open it the other way round. A reconstruction that reuses gate
    // 1's polarity here returns the complement of the machine on both.
    f.build_open();
    g_seen.slot_4c_result = 0x00000100u;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "B: a 0x100 word from +0x4c has AL clear, so gate 2 opens");
    f.build_open();
    g_seen.slot_4c_result = 0x000000feu;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "B: a 0xfe word from +0x4c closes gate 2");
    // And the +0x30 slot, the third TEST AL,AL: a clear AL closes gate 4.
    f.build_open();
    g_seen.slot_30_result = 0x00000100u;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "B: a 0x100 word from +0x30 closes gate 4");
  }

  // =====================================================================
  // C: which callee, which argument, which register, which order.
  // =====================================================================
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    g_seen.global_getter_result = 0x0000b0b0u;  // a distinct, recognisable word
    g_seen.direct_predicate_result = 1u;
    g_seen.slot_4c_result = 0u;
    g_seen.slot_30_result = 1u;
    probe_re_00f999e0(f.receiver(), &probe);
    // The value the getter returned became the RECEIVER of the next call, one level
    // below this function's own receiver, and not a member of it.
    check_eq_addr(g_seen.direct_predicate_receiver,
                  reinterpret_cast<const void*>(static_cast<std::uintptr_t>(0x0000b0b0u)),
                  "C: the getter's word is the receiver of the direct predicate");
    // The +0x4c stub's own view of the machine state.
    check_eq_addr(g_stub_ecx_4c, f.self(), "C: the +0x4c callee finds the receiver in ECX");
    check_eq_u32(g_stub_arg_word_4c, kSelector,
                 "C: the +0x4c callee finds the selector 7 at entry+4");
    // The +0x30 slot is handed the receiver in ECX and NOTHING ELSE.
    check_eq_addr(g_stub_ecx_30, f.self(), "C: the +0x30 callee finds the receiver in ECX");
    // The zero-argument half of the same claim, and this is where the check used to
    // read the machine wrong.
    //
    // The previous form of this assertion compared the two stubs' ENTRY ESP against
    // each other -- "the +0x30 stub must see exactly four bytes MORE stack than the
    // +0x4c stub did" -- on the reasoning that the only difference between the two
    // call sites is the one word the body pushes for +0x4c. That reasoning is a fact
    // about the LISTING and not about the compiler, and on x86-32 at -O0 it is false
    // for clang: clang never materialises a `push` for a callee-cleaned __thiscall
    // argument, it stores the word into the outgoing-argument area at the current ESP
    // and lets the callee's own `ret $4` take it, so both stubs are entered at the
    // same ESP and the difference collapses to 0. g++ pads the call site with
    // `sub $0xc,%esp` / `add $0xc,%esp` and shows 16. The measurement was reading the
    // compiler's scratch layout, not the machine.
    //
    // What the machine fixes, and what both compilers agree on, is the WORD at each
    // callee's own entry+4 -- the i386 calling convention puts the first stack
    // argument there, and the two stubs already read it before any C code runs. So the
    // claim is now asserted where it belongs, in the callee's own frame: the +0x4c
    // callee finds the selector (checked just above) and the +0x30 callee finds no
    // selector. A body that pushed a word for the second slot as well would put one
    // there; a body that pushed the receiver instead would put the other.
    check(g_stub_arg_word_30 != kSelector,
          "C: the body pushes an argument word for +0x4c and none for +0x30: the +0x30 "
          "callee finds no selector at its own entry+4");
    check(g_stub_arg_word_30 != static_cast<Word>(reinterpret_cast<std::uintptr_t>(f.self())),
          "C: and the +0x30 callee finds no receiver word there either -- nothing at all "
          "was pushed for that slot, its receiver travels in ECX");
    // What the old ESP comparison also covered, and where it is covered now: a body
    // that mis-balanced the argument area around the callee-cleaned +0x4c call does
    // not survive case N, which measures the caller's ESP on both sides of the whole
    // call (`esp_after == esp_before`), and an uncompensated one dies at the body's
    // own `RET`. The frame shape those two slots imply is therefore still pinned, and
    // it is pinned through a channel that does not depend on which compiler built the
    // call site.
    // And the worker's own return value really does travel back in EAX, which is what
    // the caller's next gate reads.
    check_eq_u32(g_stub_ret_4c, 0u, "C: the +0x4c callee returns its worker's word in EAX");
    check_eq_u32(g_stub_ret_30, 1u, "C: the +0x30 callee returns its worker's word in EAX");
    (void)probe;
  }

  // =====================================================================
  // D: which slot, and which LEVEL of indirection. Four decoys, four shapes.
  // =====================================================================
  {
    // D1: the neighbouring slots hold named decoys, so an off-by-one displacement is
    // identifiable rather than merely fatal.
    Fixture f;
    f.build_open();
    AbiProbe probe;
    Word table_address = 0;
    const void* a = f.table_a();
    std::memcpy(&table_address, &a, sizeof table_address);
    std::memcpy(f.self() + kTableWord, &table_address, sizeof table_address);
    // Re-point the two real slots at decoys so ANY dispatch is a violation.
    Word word = 0;
    const void* below = reinterpret_cast<const void*>(&decoy_below_4c);
    std::memcpy(&word, &below, sizeof word);
    std::memcpy(f.table_a() + 0x4c, &word, sizeof word);
    std::memcpy(f.table_a() + 0x50, &word, sizeof word);
    const void* above30 = reinterpret_cast<const void*>(&decoy_above_30);
    std::memcpy(&word, &above30, sizeof word);
    std::memcpy(f.table_a() + 0x30, &word, sizeof word);
    std::memcpy(f.table_a() + 0x2c, &word, sizeof word);
    run(f, &probe);
    check(g_seen.decoy_calls > 0, "D1: a table with only decoys at +0x4c and +0x30 is caught");
    check(g_seen.slot_4c_calls == 0, "D1: the +0x4c stub is not reached");
    check(g_seen.slot_30_calls == 0, "D1: the +0x30 stub is not reached");
  }
  {
    // D2: an OFF-BY-ONE slot displacement. The real +0x4c stub is planted one slot
    // further on, at +0x50, with a decoy at +0x4c. A reconstruction that adds the
    // wrong displacement reaches a decoy; the real stub must not be called at all.
    Fixture f;
    f.build_open();
    AbiProbe probe;
    Word word = 0;
    const void* below = reinterpret_cast<const void*>(&decoy_below_4c);
    std::memcpy(&word, &below, sizeof word);
    std::memcpy(f.table_a() + 0x4c, &word, sizeof word);
    const void* real = reinterpret_cast<const void*>(&sw2_slot_4c_stub);
    std::memcpy(f.table_a() + 0x50, &real, sizeof word);
    run(f, &probe);
    check(g_seen.decoy_calls > 0, "D2: a decoy at +0x4c is reached instead of the stub");
    check(g_seen.slot_4c_calls == 0,
          "D2: the +0x4c stub one slot further on is NOT called, so the displacement is +0x4c");
  }
  {
    // D3: a HOSTILE table. Every index of the table the receiver names is a decoy,
    // including index 0 -- so a reconstruction that forgets the slot displacement, or
    // that indexes the receiver instead of the table, lands on a decoy too. This is
    // the wrong-base and wrong-level case, driven safely: the alternative decoy for it
    // (a bare function address in the receiver's +0x00) would make a two-level reader
    // execute the callee's own code bytes as a table, which is a crash rather than a
    // diagnosis.
    Fixture f;
    f.build_open();
    AbiProbe probe;
    f.build_hostile_table(f.table_b());
    Word table_address = 0;
    const void* b = f.table_b();
    std::memcpy(&table_address, &b, sizeof table_address);
    std::memcpy(f.self() + kTableWord, &table_address, sizeof table_address);
    run(f, &probe);
    check(g_seen.decoy_calls > 0, "D3: a hostile table is caught");
    check(g_seen.slot_4c_calls == 0, "D3: no real +0x4c stub is reached");
    check(g_seen.slot_30_calls == 0, "D3: no real +0x30 stub is reached");
    // The table's index 0 is a decoy, which is the "forgot the displacement" half.
    Word index_zero = 0;
    std::memcpy(&index_zero, f.table_b(), sizeof index_zero);
    check(index_zero != 0u, "D3: the hostile table's index 0 is a decoy, not a hole");
  }

  // =====================================================================
  // H: the compare polarity, in all four pair combinations. The case the
  // committed decompilation inverts, so it is the one that matters most.
  // =====================================================================
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    std::size_t base = 0;
    std::size_t bases[4];
    group_bases(2, bases);
    base = bases[1];
    // Pair 0 equal, pair 1 equal -> the group rejects.
    f.build_open();
    f.plant_group(base, true, true);
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "H: both pairs ordered-equal -> 0");
    // Pair 0 equal, pair 1 not -> pass.
    f.build_open();
    f.plant_group(base, true, false);
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "H: only pair 0 ordered-equal -> 1");
    // Pair 0 not, pair 1 equal -> pass.
    f.build_open();
    f.plant_group(base, false, true);
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "H: only pair 1 ordered-equal -> 1");
    // Neither equal -> pass.
    f.build_open();
    f.plant_group(base, false, false);
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "H: neither pair ordered-equal -> 1");
  }

  // =====================================================================
  // I / J: ORDERED equality. The two cases where a byte-wise reading of the
  // same four bytes gives the opposite answer.
  // =====================================================================
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    std::size_t bases[4];
    group_bases(4, bases);
    const std::size_t base = bases[3];
    // J: +0.0f against -0.0f. The machine's UCOMISS calls them equal; their bytes
    // differ, so a memcmp-style compare passes and the model test catches it.
    f.build_open();
    std::uint8_t* g = f.group(base);
    const float positive_zero = 0.0f;
    const float negative_zero = -0.0f;
    const float one = 1.0f;
    std::memcpy(g + 0, &positive_zero, sizeof positive_zero);
    std::memcpy(g + 4, &one, sizeof one);
    std::memcpy(g + kPairSpan, &negative_zero, sizeof negative_zero);
    std::memcpy(g + 4 + kPairSpan, &one, sizeof one);
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "J: +0.0f against -0.0f is ordered-equal, so the group rejects");
    // I: a quiet NaN against the same bit pattern. UCOMISS is unordered, so the
    // group passes; a byte-wise compare would call them equal and reject.
    f.build_open();
    const float nan_value = std::numeric_limits<float>::quiet_NaN();
    std::memcpy(g + 0, &nan_value, sizeof nan_value);
    std::memcpy(g + 4, &one, sizeof one);
    std::memcpy(g + kPairSpan, &nan_value, sizeof nan_value);
    std::memcpy(g + 4 + kPairSpan, &one, sizeof one);
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "I: NaN against its own bits is unordered, so the group passes");
    // And a NaN in the SECOND pair alone, with the first pair equal: the machine
    // reaches the second compare and it is unordered, so the group passes.
    f.build_open();
    f.plant_group(base, true, true);
    std::memcpy(g + 4 + kPairSpan, &nan_value, sizeof nan_value);
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "I: an unordered second pair passes even when the first is equal");
  }

  // =====================================================================
  // K: the scanned set, pinned from the inside, and the two decoys that the
  // layout actually admits.
  //
  // The twenty-four bases are {receiver + 0x374 + 0x10k, k = 0..23}: the four
  // families the body walks (0x374, 0x3d4, 0x434, 0x494 at outer index 0) are exactly
  // this run at k = 0, 6, 12 and 18, because the inner stride 0x60 is six times the
  // outer stride 0x10. Each base is asserted to reject, which pins the run's start, its
  // stride and its length from the inside.
  //
  // There is almost NO clean negative decoy in this layout, and that is a property of
  // the machine rather than a gap in the test. The bases are 0x10 apart and each group
  // is 0xc bytes wide, so any address between two bases is inside one of their spans;
  // the run is additionally bracketed below by the +0x370 flag byte and above by the
  // +0x4f4 one, and the table word sits at +0x00. The decoys below are the ones that
  // survive all three constraints, and the test PROVES each of them is clean -- no
  // overlap with a scanned span, no touch of a flag byte, no touch of the table word --
  // rather than assuming it. A decoy that failed that proof would be reported as a
  // test-construction error instead of silently proving nothing.
  //
  // The loop COUNTS are therefore not argued positionally (they cannot be: "outer
  // index 6" and "inner index 0 one row down" are the same address). They come from the
  // listing's own forms -- `CMP EDX,0x2` at 0x00f99a61 and `CMP EDI,0x6` at 0x00f99aa5,
  // both a signed JL against a counter incremented first -- together with the fact that
  // a group planted at a base of EVERY outer index, the fifth included, is reached,
  // which is what rules out a shorter loop. The sub-case "the inner count, from the
  // inside" makes that runtime half explicit for the inner loop rather than leaving it
  // implied by the sweep: at the TOP outer index the LAST inner row is at +0x424, whose
  // nearest outer row-0 base is outer index 11, which the six-iteration outer loop never
  // takes, so only the inner loop's second row can produce it.
  // =====================================================================
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;

    // The scanned set, built the way the body builds it and then compared against the
    // literal run, so a change to either the harness or the constants is caught.
    std::size_t scanned[24];
    unsigned scanned_count = 0;
    for (unsigned i = 0; i < kOuterCount; ++i) {
      std::size_t bases[4];
      group_bases(i, bases);
      for (unsigned g = 0; g < 4; ++g) {
        scanned[scanned_count++] = bases[g];
      }
    }
    check_eq_int(static_cast<long>(scanned_count), 24, "K: the scan covers twenty-four groups");
    // The body walks the four families of each outer index in turn, so the set as built
    // is outer-major. Sorted, it must be one 0x10-stride run -- and the sort is written
    // out rather than delegated so a wrong order is a wrong order here.
    for (unsigned n = 1; n < scanned_count; ++n) {
      const std::size_t key = scanned[n];
      unsigned m = n;
      while (m > 0 && scanned[m - 1] > key) {
        scanned[m] = scanned[m - 1];
        --m;
      }
      scanned[m] = key;
    }
    for (unsigned n = 0; n < scanned_count; ++n) {
      if (scanned[n] != 0x374u + 0x10u * n) {
        std::fprintf(stderr,
                     "FAILED: K: the scanned set is not one 0x10-stride run from receiver "
                     "+ 0x374 (entry %u is +0x%zx, want +0x%zx)\n",
                     n, scanned[n], 0x374u + 0x10u * n);
        ++g_failures;
      }
    }

    // Every one of them rejects.
    for (unsigned n = 0; n < scanned_count; ++n) {
      f.build_open();
      f.plant_group(scanned[n], true, true);
      const Word eax = run(f, &probe);
      if ((eax & 0xffu) != 0u) {
        std::fprintf(stderr, "FAILED: K: +0x%zx is a scanned base and does not reject\n",
                     scanned[n]);
        ++g_failures;
      }
    }

    // -- the inner trip count, from the inside ---------------------------------
    // The count cannot be read off the address set (see the static_assert above), so it
    // is measured instead: kInnerCount rows of the inner loop per outer iteration, each
    // one kGroupStride below the last, and the LAST of them reached at the TOP outer
    // index. That last part is what makes the evidence discriminating rather than
    // circular: at outer index kOuterCount-1 the last inner row sits at
    // 0x374 + 0x10*(kOuterCount-1) + kInnerCount*0x60, which as an OUTER row-0 base
    // would be outer index (kOuterCount-1) + 6*kInnerCount -- past the outer loop's own
    // count, so no outer iteration can produce that address and the inner loop's second
    // row is the only thing that can. A single-step inner loop therefore fails here, and
    // a single-family outer loop fails one step up the same argument.
    for (unsigned i = 0; i < kOuterCount; ++i) {
      std::size_t bases[4];
      group_bases(i, bases);
      for (unsigned row = 0; row < kInnerCount; ++row) {
        const std::size_t base = bases[0] + row * kGroupStride;
        if (base != bases[row]) {
          std::fprintf(stderr,
                       "FAILED: K: inner row %u of outer index %u is +0x%zx, but the "
                       "harness's family %u is +0x%zx\n",
                       row, i, base, row, bases[row]);
          ++g_failures;
        }
        if (base >= bases[kInnerCount]) {
          std::fprintf(stderr,
                       "FAILED: K: inner row %u of outer index %u (+0x%zx) is at or past "
                       "the first unrolled group (+0x%zx)\n",
                       row, i, base, bases[kInnerCount]);
          ++g_failures;
        }
      }
      // The address the inner loop would reach one row FURTHER, and which is already
      // the first unrolled group's base. Asserted so the limit of the address set is on
      // the record: this is exactly why the runtime evidence bounds the count from
      // below only, and why the exact value is the listing's `CMP EDX,0x2`.
      if (bases[0] + kInnerCount * kGroupStride != bases[kInnerCount]) {
        std::fprintf(stderr,
                     "FAILED: K: the row one past the last inner row is not the first "
                     "unrolled group's base at outer index %u\n",
                     i);
        ++g_failures;
      }
    }
    // The discriminating pair itself, named by address: at the top outer index the last
    // inner row is +0x424, and the nearest OUTER row-0 base is eleven 0x10 strides up
    // the run, i.e. an outer index the loop never takes. Planting a rejecting group
    // there must return 0, which no single-step inner loop and no shorter outer loop
    // can produce.
    {
      std::size_t bases[4];
      group_bases(kOuterCount - 1, bases);
      const std::size_t last_inner_row = bases[0] + (kInnerCount - 1) * kGroupStride;
      if (last_inner_row != 0x424u) {
        std::fprintf(stderr,
                     "FAILED: K: the last inner row at the top outer index is +0x%zx, "
                     "not +0x424\n",
                     last_inner_row);
        ++g_failures;
      }
      f.build_open();
      f.plant_group(last_inner_row, true, true);
      if ((run(f, &probe) & 0xffu) != 0u) {
        std::fprintf(stderr,
                     "FAILED: K: +0x%zx is inner index %u of outer index %u and is "
                     "reached, so the inner loop runs %u times\n",
                     last_inner_row, kInnerCount - 1, kOuterCount - 1, kInnerCount);
        ++g_failures;
      }
    }

    // The clean negative decoys, with the cleanliness proof.
    const std::size_t kGroupSpan = 0xc;
    const std::size_t kFlagSpanLow = kFlagByte;            // the +0x370 byte
    const std::size_t kFlagSpanHigh = kSecondFlagByte;     // the +0x4f4 byte
    const std::size_t decoys[] = {
        kFlagByte - kGroupSpan,   // 0x364: one group below the run, and its last byte
                                  // IS the +0x370 flag, which plant_group writes as
                                  // 100.0f's low byte -- already 0 in the open fixture,
                                  // so the flag is left exactly as it was
        0x8,                      // just above the receiver's own table word
        0x374u + 0x190u,          // one group past the +0x4f4 flag
        0x374u + 0x290u,          // and one past that
    };
    for (unsigned n = 0; n < sizeof decoys / sizeof decoys[0]; ++n) {
      const std::size_t base = decoys[n];
      if (base + kGroupSpan > sizeof f.arena.bytes) {
        std::fprintf(stderr, "FAILED: K: decoy +0x%zx runs off the arena\n", base);
        ++g_failures;
        continue;
      }
      for (unsigned s = 0; s < scanned_count; ++s) {
        if (base < scanned[s] + kGroupSpan && scanned[s] < base + kGroupSpan) {
          std::fprintf(stderr, "FAILED: K: decoy +0x%zx overlaps the scanned group +0x%zx\n",
                       base, scanned[s]);
          ++g_failures;
        }
      }
      if (base <= kFlagSpanLow && kFlagSpanLow < base + kGroupSpan) {
        // The one decoy that deliberately writes the flag byte, and only because it
        // writes the value the flag already holds.
        std::fprintf(stderr,
                     "FAILED: K: decoy +0x%zx writes the +0x370 flag with a new value\n", base);
        ++g_failures;
      }
      if (base <= kFlagSpanHigh && kFlagSpanHigh < base + kGroupSpan) {
        std::fprintf(stderr,
                     "FAILED: K: decoy +0x%zx writes the +0x4f4 flag with a new value\n", base);
        ++g_failures;
      }
      if (base < 4) {
        std::fprintf(stderr, "FAILED: K: decoy +0x%zx overlaps the receiver's table word\n", base);
        ++g_failures;
      }
      f.build_open();
      const std::uint8_t flag_before = f.self()[kFlagByte];
      f.plant_group(base, true, true);
      if (f.self()[kFlagByte] != flag_before) {
        std::fprintf(stderr, "FAILED: K: decoy +0x%zx moved the +0x370 flag\n", base);
        ++g_failures;
      }
      const Word eax = run(f, &probe);
      if ((eax & 0xffu) != 1u) {
        std::fprintf(stderr,
                     "FAILED: K: +0x%zx is not a scanned base, and planting a rejecting "
                     "group there changed the answer\n",
                     base);
        ++g_failures;
      }
    }
  }

  // =====================================================================
  // M: the receiver is read-only, byte for byte, on a scan that runs to
  // completion and on one that exits early.
  // =====================================================================
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    std::size_t bases[4];
    group_bases(5, bases);
    f.plant_group(bases[2], true, true);
    f.take_snapshot();
    run(f, &probe);
    f.check_untouched("M: the body writes no receiver byte on the early exit");
    f.build_open();
    f.take_snapshot();
    run(f, &probe);
    f.check_untouched("M: the body writes no receiver byte on the full scan");
    // And on the first exit, before any of the scan runs.
    f.build_open();
    g_seen.direct_predicate_result = 0u;
    f.take_snapshot();
    run(f, &probe);
    f.check_untouched("M: the body writes no receiver byte on the first exit");
  }

  // =====================================================================
  // L: the dead return register, on every exit, with each callee poisoned.
  // =====================================================================
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    const Word kPoison = 0xdeadbe00u;
    // Exit at 0x00f999f3 after the first gate: the word is the DIRECT predicate's.
    g_seen.direct_predicate_result = kPoison;
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "L: the first exit returns 0");
    check_eq_u32(ns::dead_return_word(), kPoison & 0xffffff00u,
                 "L: the first exit keeps the direct predicate's high bytes");
    // Exit at 0x00f999f3 after gate 2: the word is the +0x4c slot's.
    f.build_open();
    g_seen.slot_4c_result = kPoison | 0x01u;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "L: gate 2 returns 0");
    check_eq_u32(ns::dead_return_word(), (kPoison | 0x01u) & 0xffffff00u,
                 "L: gate 2 keeps the +0x4c slot's high bytes");
    // Exit at 0x00f999f3 after gate 4: the word is the +0x30 slot's.
    f.build_open();
    g_seen.slot_30_result = kPoison;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "L: gate 4 returns 0");
    check_eq_u32(ns::dead_return_word(), kPoison & 0xffffff00u,
                 "L: gate 4 keeps the +0x30 slot's high bytes");
    // Exit at 0x00f99aaf from the compare loop: the word is STILL the +0x30 slot's,
    // because no instruction in the loop writes the return register.
    f.build_open();
    g_seen.slot_30_result = kPoison | 0x01u;
    std::size_t bases[4];
    group_bases(1, bases);
    f.plant_group(bases[0], true, true);
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 0u, "L: a rejecting group returns 0");
    check_eq_u32(ns::dead_return_word(), (kPoison | 0x01u) & 0xffffff00u,
                 "L: the compare loop writes no byte of the return register");
    // Exit at 0x00f99aab: bit 0 is SET over the same high bytes, because that exit is
    // `MOV AL,0x1` and not a clear.
    f.build_open();
    g_seen.slot_30_result = kPoison | 0x02u;
    eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "L: the full scan returns 1");
    check_eq_u32(ns::dead_return_word(), ((kPoison | 0x02u) & 0xffffff00u) | 1u,
                 "L: the return-1 exit sets only bit 0 over the +0x30 slot's word");
    // A model that reuses the FIRST gate's result rather than the last callee's is
    // caught here: the two differ by construction in the case above only if the +0x30
    // slot's word is not the getter's, so check the getter's word directly too.
    f.build_open();
    g_seen.global_getter_result = 0x11111111u;
    g_seen.slot_30_result = 0x22222222u;
    eax = run(f, &probe);
    check_eq_u32(ns::dead_return_word(), 0x22222200u | 1u,
                 "L: the last callee's word is the one left in the return register");
  }

  // =====================================================================
  // N: the ABI. A bare RET, so ESP is unchanged across the call, measured
  // rather than asserted; and the receiver arrives in ECX.
  // =====================================================================
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    // The +0x4c slot is the one that pushes a word, so the balance is measured with
    // that transfer actually happening.
    std::size_t bases[4];
    group_bases(0, bases);
    f.plant_group(bases[3], true, true);
    probe_re_00f999e0(f.receiver(), &probe);
    check_eq_u32(probe.esp_after, probe.esp_before,
                 "N: ESP is unchanged across the call, so the return is a bare RET");
    check_eq_u32(probe.eax & 0xffu, 0u, "N: the returned byte is read out of the register");
    // The same on the return-1 path.
    f.build_open();
    probe_re_00f999e0(f.receiver(), &probe);
    check_eq_u32(probe.esp_after, probe.esp_before, "N: ESP is unchanged on the return-1 path");
    check_eq_u32(probe.eax & 0xffu, 1u, "N: the return-1 byte is read out of the register");
  }

  // =====================================================================
  // O: the table word is read TWICE. The +0x4c observer rewrites the
  // receiver's +0x00 and the +0x30 call must follow the SECOND table.
  // =====================================================================
  {
    Fixture f;
    f.build_open();
    AbiProbe probe;
    // table_b's +0x30 holds a DIFFERENT stub, so the identity of the callee is the
    // measurement of which table was used.
    Word word = 0;
    const void* second_b = reinterpret_cast<const void*>(&sw2_slot_30b_stub);
    std::memcpy(&word, &second_b, sizeof word);
    std::memcpy(f.table_b() + 0x30, &word, sizeof word);
    g_seen.slot_30_result_b = 1u;

    g_stub_ecx_30 = 0;
    g_stub_esp_30 = 0;
    g_stub_ecx_30b = 0;
    g_stub_esp_30b = 0;
    g_seen.retarget_table = true;
    g_seen.retarget_value = f.self() + kTableWord;
    Word eax = run(f, &probe);
    check_eq_u32(eax & 0xffu, 1u, "O: the scan still returns 1 after the retarget");
    check(g_stub_esp_30b != 0u, "O: the +0x30 call followed the SECOND table");
    check_eq_u32(g_stub_ecx_30b, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(f.self())),
                 "O: the second table's +0x30 stub found the receiver in ECX");
    check_eq_u32(g_stub_esp_30, 0u,
                 "O: the FIRST table's +0x30 stub was not reached, so the word at the "
                 "receiver's +0x00 was read twice");
    check_eq_int(g_seen.slot_30_calls, 1,
                 "O: exactly one +0x30 call happened, the second table's");
    (void)word;
  }

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("pkg-swarm-w2-00f999e0: all checks passed\n");
  return 0;
}
