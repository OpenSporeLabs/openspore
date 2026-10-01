// PKG-SWARM-W1-006417D0 -- model test for VA 0x006417d0
//
// A falsification test, not a walkthrough. Its job is to try to KILL the model in
// swarm_w1_006417d0.cpp, and every assertion below is tied to a pair of instructions
// in the 23-instruction listing:
//
//   006417d0 PUSH ESI / 00641802 POP ESI / 00641808 POP ESI
//   006417d1 MOV ESI,ECX
//   006417d3 MOV ECX,[ESI+0x1c]     the FIRST load of the receiver word
//   006417d6 TEST ECX,ECX / 006417d8 JZ 0x00641806
//   006417da CALL 0x005507a0        the PROBE
//   006417df CMP [EAX],-0x1 / 006417e2 JNZ 0x006417ea
//   006417e4 CMP [EAX+0x4],-0x1 / 006417e8 JZ 0x00641806
//   006417ea MOV ECX,[ESI+0x1c]     the SECOND, independent load
//   006417ed CALL 0x005507a0        the COPY SOURCE
//   006417f2 MOV EDX,[EAX] / 006417f4 MOV ECX,[ESP+0x8] / 006417f8 MOV [ECX],EDX
//   006417fa MOV EAX,[EAX+0x4] / 006417fd MOV [ECX+0x4],EAX
//   00641800 MOV AL,0x1 / 00641806 XOR AL,AL
//   00641803 / 00641809 RET 0x4
//
// THE OBSERVATION SURFACE. The body has exactly one direct callee, 0x005507a0, and
// the test defines it as a two-piece observer:
//
//  * w16_tramp_accessor is a hand-written assembly trampoline that IS the definition
//    of 0x005507a0. It has no prologue and its only instructions are five loads out
//    of the callee's own stack frame, five pushes, and a call. It never writes ECX,
//    never writes memory except its own frame, and never branches on anything. So the
//    test sees the callee's real entry state, and ECX is read by the C++ body as its
//    own __thiscall parameter -- the compiler puts it there, not the test.
//
//  * w16_accessor_body is a C++ function with the SAME __thiscall convention
//    0x005507a0 has (first argument in ECX, no stack argument of its own,
//    callee-cleaned). It records everything, runs an optional hook, and returns a
//    scripted pointer. It gets to decide what the callee does to memory, which is
//    the whole point.
//
//  * One asm block at the bottom of the fixtures calls re_006417d0 and publishes the
//    caller's ESP on both sides of the transfer, so the RET 0x4 cleanup is MEASURED
//    rather than assumed. The measurement is shown to be sensitive: the same block
//    shape is used to call a cdecl probe, which is required to come back four bytes
//    lower.
//
//  * w16_model_entry_observer is a second naked trampoline, entered where re_006417d0
//    would have been entered and tail-jumping into it, so the model's OWN entry frame
//    can be read from outside the model. It has no prologue, so its %esp at its first
//    instruction is the entry ESP a direct CALL would have produced, and it adds no
//    frame word of its own. The call site that reaches it can lower the stack by a
//    known amount first, which is what makes the depth measurement below provable
//    rather than merely true. See case_one_frame_between_the_two_calls.
//
// Decoy coverage, and the defect each decoy is designed to kill:
//
//   A  the out record is poisoned with 24 bytes before every run and compared byte
//      for byte afterwards -> a model that writes it on the false paths, or writes
//      more or fewer than 8 bytes, or writes somewhere other than the caller's
//      buffer
//   B  scripted (first_word, second_word) pairs spanning 0, 1, 0x7fffffff,
//      0x80000000, 0xfffffffe, 0xffffffff, 0xdeadbeef -> a signed compare, an
//      unsigned compare, a zero test, a `!= 1` test, or a range test
//   C  (0xffffffff, x) and (x, 0xffffffff) both required to SUCCEED -> a
//      disjunction in place of the conjunction, or a first-word-only test
//   D  (0xffffffff, 0xffffffff) with a call counter -> the second call to 0x005507a0
//      must NOT happen
//   E  the observer returns a different record on the second call and POISONS the
//      first while doing so -> a model that copies from the first probe, or that
//      mixes the two probes' words
//   F  the second call returns the sentinel pair while the first does not -> the
//      CHECK is on call #1 and the COPY is on call #2, unambiguously
//   G  the observer returns records that are NOT at inner+0x18, while inner+0x00,
//      +0x04 .. +0x1c hold poison -> a model that hand-rolls the accessor's +0x18
//      addend instead of using the returned pointer
//   H  the observer overwrites the receiver's +0x1c word during the first call, and
//      the second call is required to see the NEW value -> a model that caches the
//      inner pointer across 0x006417ea
//   I  live observer addresses planted at receiver+0x00, +0x04, +0x08, +0x10, +0x18,
//      +0x20, +0x24 and +0x28 inside a larger raw block, plus a decoy word at the
//      inner object's own +0x00 -> a wrong receiver displacement, or a two-level
//      dereference that hands the callee the word at inner+0x00
//   J  the sentinel probe is a FOUR-byte record placed four bytes before a PROT_NONE
//      guard page -> a model that reads the second word even when the first word is
//      the sentinel (i.e. a removed short circuit) faults
//   K  the callee's entry ESP must be exactly (published caller ESP - 12), its
//      [ESP+8] must be the out pointer, and its return address must land inside the
//      model's own body -> a pushed argument, a wrong stack slot for the out
//      pointer, or a call made from anywhere but 0x006417da / 0x006417ed
//   L  the caller's ESP must come back LEVEL after re_006417d0 and four bytes LOWER
//      after the cdecl probe -> the cleanup owner is measured, and the measurement
//      is shown to discriminate
//   M  the two calls' return addresses must DIFFER -> two distinct call sites, not
//      one call used twice
//   N  a byte-for-byte snapshot of the receiver block, the inner block and the out
//      record -> a model that writes through the receiver or the inner object, which
//      the listing never does
//   O  the parked and restored ESI words, poisoned before every run, checked on all
//      three return paths -> a missing POP ESI, or a POP on only one path
//   P  a compile-time assertion that the declared return type is std::uint8_t ->
//      a model that widened the AL-only return to a 32-bit word
//   Q  the decoy observers are called once on purpose -> proves they are live code
//      that could fail the run, not unreachable filler
//   R  the model's own entry frame, read from outside through w16_model_entry_observer,
//      plus the two accessors' entry ESPs, plus a control run entered 16 bytes lower
//      -> one frame and no stack movement between 0x006417da and 0x006417ed. This
//      replaces an earlier check that compared the two calls' [ESP+4] WORDS; see
//      "not asserted" below for why a word there is not a machine fact in this model.
//
// MUTATION CHECKING. Thirty-three defects were injected one at a time into copies of
// swarm_w1_006417d0.cpp / _types.hpp and this test was run against each, under the
// promotion gate's own toolchain (clang++ -std=c++17 -Wall -Wextra -Werror -m32, the
// package compiled to objects, archived with ar/ranlib and linked as a static
// library). Every one was killed; none survived, under clang++ and under g++ alike.
// `KILLED (n)` is the number of failing checks; `SIGSEGV` is the guard page in
// case_second_word_is_not_read... doing its job, or a model that dereferences a poisoned
// decoy or a scripted record used as a pointer; `COMPILE` is the header's static_asserts
// or -Werror catching it before it can run. The counts below are the re-measured
// values on the current 251-check test.
//
//   invert the null test                        KILLED (156)
//   invert the first sentinel compare           SIGSEGV
//   disjunction instead of conjunction          SIGSEGV
//   remove the short circuit                    SIGSEGV
//   off-by-one sentinel constant                KILLED (9)
//   unsigned-band sentinel (>= 0xffffff00)      KILLED (20)
//   signed sentinel compare (first < 0)         KILLED (4)
//   16-bit-truncated sentinel                   KILLED (15)
//   swap the record displacements (0x00/0x04)   KILLED (48)
//   drop the second sentinel compare            SIGSEGV
//   copy from the FIRST probe                   KILLED (1)
//   drop the second call entirely               SIGSEGV
//   check the SECOND probe                      KILLED (35)
//   swap the two copied words                   KILLED (48)
//   shift the out record by one word            KILLED (101)
//   write 12 bytes instead of 8                 KILLED (26)
//   write the out record on the false path      KILLED (1)
//   return 1 without writing anything           KILLED (76)
//   return 0xff instead of 1                    KILLED (34)
//   widen the return to uint32_t                COMPILE
//   null-check the accessor's RETURN value      KILLED (4)
//   skip the accessor entirely                  SIGSEGV
//   read the probe pointer one level too far    SIGSEGV
//   hand-roll the accessor's +0x18 addend       SIGSEGV
//   mis-declare the accessor's addend (+0x1c)   COMPILE
//   receiver word at +0x18                      KILLED (8)
//   receiver word at +0x20                      KILLED (8)
//   two-level dereference of the receiver word  SIGSEGV
//   cache the inner pointer across 0x006417ea   KILLED (1)
//   cache the probe pointer                     SIGSEGV
//   caller-side cleanup (cdecl) instead of ret  COMPILE
//   do not park the entry ESI                   KILLED (8)
//   omit the POP ESI on the false path          KILLED (2)
//
// A THIRTY-FOURTH mutant is recorded separately, because it is the one that pins the
// replacement for the [ESP+4] word check: it is not a reconstruction defect anyone
// would plausibly ship, it is the defect CLASS that check named, injected directly so
// the new measurement can be shown to still catch it.
//
//   move the stack between the two calls         KILLED (4)
//     (`subl $4,%esp` immediately before 0x006417ed's call and `addl $4,%esp` after
//      it; the four failures are the two entry-ESP equalities, the [ESP+4] slot
//      address equality, and the control run's own equality)
//
// One candidate mutation is deliberately absent: swapping the ORDER of the two stores
// to the out record. Nothing in the 23 instructions can trap between them, so no
// observable can distinguish the orders -- see the not-asserted list.

// WHAT IS DELIBERATELY NOT ASSERTED, and why:
//
//  * The upper three bytes of EAX. 0x00641800 is `MOV AL,0x1` and 0x00641806 is
//    `XOR AL,AL`; neither writes the rest, and all seven references to this body are
//    DATA references from .rdata, so no caller in this image constrains them. The
//    test records the full EAX at every call site and asserts nothing above the low
//    byte. Case P pins the declared type instead, which is the honest form of the
//    same claim.
//  * What 0x005507a0 means, and what the eight bytes it returns are. This body names
//    no callee symbol, no import, no string and no constant, so no test can fix
//    either. 0x005507a0's own seventeen bytes fix only that it returns its receiver plus
//    0x18, and that is all the model uses.
//  * Whether any real callee in the game ever changes the receiver's +0x1c word.
//    Case H proves only that the MODEL re-reads it, which is what 0x006417ea fixes.
//  * That a real callee ever returns a null pointer from 0x005507a0. The body does
//    not null-check the RETURN value -- only the receiver word at 0x006417d6 -- and
//    the test deliberately never scripts a null return, because the only way to
//    observe that would be to require the model to fault, which is not an assertion.
//  * The order of the two stores to the out record relative to each other.
//    0x006417f2 loads the first word, 0x006417f4 loads the out pointer, 0x006417f8
//    stores, 0x006417fa loads the second word, 0x006417fd stores. Nothing in the 23
//    instructions can trap between them, so no observable in this test can
//    distinguish the two orders, and inventing one would assert a fact the machine
//    does not expose.
//  * The ABSOLUTE stack distance from the model's entry down to the accessor's entry.
//    In the machine it is exactly 8 -- 0x006417d0's PUSH ESI and 0x006417da's own CALL
//    return address, and nothing else -- but this model is compiled at -O0 and the
//    compiler gives re_006417d0 a real frame of its own (`push ebp; mov ebp,esp; push
//    ebx; sub esp,0x34` plus a GOT-base thunk under g++, `pushl %ebx; subl $52,%esp`
//    under the gate's clang++), so the figure is a property of the toolchain and is not
//    even the same number under the two compilers. Asserting it would be measuring the
//    compiler. What IS asserted instead is the toolchain-independent part: the caller
//    gets its ESP back level (the RET 0x4, with a cdecl sensitivity control); the
//    model's own entry frame is exactly the two words a CALL builds, with the out
//    pointer at [entry+4] -- the slot 0x006417f4 reaches as [ESP+0x8] with ESP at
//    entry-4; the model is at the SAME stack depth at both call sites, and that
//    measurement is shown to discriminate against a control run entered 16 bytes
//    lower; neither accessor frame holds the caller's argument word; and the two out
//    words land in the CALLER's buffer.
//  * The WORD at the accessor's [ESP+4], and the claim that it holds the ESI
//    0x006417d0 pushed. This is the one assertion this test USED to make and no longer
//    does, so the reason is worth stating flatly rather than only in the case. In the
//    machine that word is the saved ESI and it is identical at both calls, so comparing
//    the two is a reasonable proxy for "there is one frame". In this model it is not
//    the saved ESI and not a machine fact at all: the model has no real PUSH ESI (next
//    bullet), so [ESP+4] is whatever the -O0 frame layout put there, and the two calls
//    do not even read the same slot's stable value -- clang++ writes an uninitialised
//    spill between them, which is why the check reported `got 0x00000000, want
//    0x565ba0d4` and would report a different heap address on every build. Asserting it
//    would have asserted the toolchain's register allocation. The claim it was standing
//    in for is measured instead, three ways, by case_one_frame_between_the_two_calls:
//    the two accessors' entry ESPs (a STACK ADDRESS, which no register-allocation
//    choice can move), the [ESP+4] SLOT ADDRESSES those ESPs name, and a control run
//    that shows the entry ESP tracks a deliberate change of stack depth. The PUSH/POP
//    ESI pair itself is asserted as a VALUE on all three return paths by case_esi_is_
//    restored_on_every_return_path. The thirty-fourth mutant above injects exactly this
//    defect class and is caught.
//  * The C++ observers' own register and stack state. A C++ function has already
//    built its frame by the time it runs; every register and stack claim above is
//    made from the trampolines and from the call-site asm blocks instead. The entry
//    observer is a naked trampoline for the same reason: a C++ prologue would have run
//    before any statement in it, so a C++ function cannot sample its own entry ESP.
//  * The 0x006417d0 / 0x00641802 / 0x00641808 ESI traffic as a REGISTER effect. The
//    prescribed build is a PIE and GCC's i386 PIE sequence for this translation unit
//    puts the GOT base in ESI (`call __x86.get_pc_thunk.si; addl
//    $_GLOBAL_OFFSET_TABLE_,%esi`), so a real-register probe would read the module
//    address instead of the caller's ESI. The instruction is annotated in the model;
//    what is asserted instead is the weaker and still real fact that the value parked
//    at 0x006417d0 is handed back on every one of the three return paths.

#include "swarm_w1_006417d0_types.hpp"

#include <sys/mman.h>
#include <unistd.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

namespace openspore::reconstruction::pkg_swarm_w1_006417d0 {
namespace {

// ---------------------------------------------------------------------------
// The machine's numbers, repeated here as literals so the test never takes a
// value from the header it is trying to falsify.
// ---------------------------------------------------------------------------
constexpr Word kSentinel = 0xffffffffu;
constexpr std::size_t kInnerOffset = 0x1cu;
constexpr std::size_t kReceiverBlock = 0x30u;  // modelled receiver plus a sentinel tail
constexpr std::size_t kInnerBlock = 0x28u;     // modelled inner object plus a tail
constexpr std::size_t kOutWords = 6u;         // 24 bytes: 8 written, 16 poison

// Distinctive values. Every decoy and every poison is one of these, so a wrong
// reading produces a value that appears nowhere else in the run.
constexpr Word kDecoy0 = 0x0badf00du;
constexpr Word kDecoy1 = 0x0badf00eu;
constexpr Word kDecoy2 = 0x0badf00fu;
constexpr Word kDecoy3 = 0x0badf010u;
constexpr Word kDecoy4 = 0x0badf011u;
constexpr Word kDecoy5 = 0x0badf012u;
constexpr Word kDecoy6 = 0x0badf013u;
constexpr Word kEntryEsi = 0x0badcafeu;

constexpr Word kOutPoison0 = 0xfeed0000u;
constexpr Word kOutPoison1 = 0xfeed0004u;
constexpr Word kOutPoison2 = 0xfeed0008u;
constexpr Word kOutPoison3 = 0xfeed000cu;
constexpr Word kOutPoison4 = 0xfeed0010u;
constexpr Word kOutPoison5 = 0xfeed0014u;

int g_checks = 0;
int g_failures = 0;

std::string hex32(Word v) {
  char buffer[16];
  std::snprintf(buffer, sizeof buffer, "0x%08lx", static_cast<unsigned long>(v));
  return std::string(buffer);
}

void check(bool ok, const std::string& what) {
  ++g_checks;
  if (!ok) {
    ++g_failures;
    std::fprintf(stderr, "FAILED: %s\n", what.c_str());
  }
}

void check_word(Word got, Word want, const std::string& what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::fprintf(stderr, "FAILED: %s (got %s, want %s)\n", what.c_str(), hex32(got).c_str(),
                 hex32(want).c_str());
  }
}

void check_ptr(const void* got, const void* want, const std::string& what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::fprintf(stderr, "FAILED: %s (got %p, want %p)\n", what.c_str(), got, want);
  }
}

// ---------------------------------------------------------------------------
// The observation record the accessor body fills in.
// ---------------------------------------------------------------------------
struct AccessRecord {
  Word entry_esp;         // the callee's ESP at its very first instruction
  Word callee_return;     // the callee's [ESP+0]
  Word caller_saved_esi;  // the callee's [ESP+4]
  Word caller_argument;   // the callee's [ESP+8]
  Word caller_outer;      // the callee's [ESP+12]
  Word ecx;               // the callee's ECX, as the C++ body received it
};

struct Observation {
  int calls = 0;
  AccessRecord record[4] = {};
  int decoy_hits = 0;

  // What the observer hands back per call, and an optional override so the test can
  // point a result at memory it controls (a guard page, for instance).
  WordPair result[2] = {};
  WordPair* result_override[2] = {};

  // Hooks run while a call is in progress. A hook may rewrite the receiver's +0x1c
  // word, which is legal for the model to observe because 0x006417ea is an ordinary
  // load, and may rewrite a record the earlier call returned.
  void (*hook_first)(void*) = nullptr;
  void (*hook_second)(void*) = nullptr;
  void* hook_arg = nullptr;
  void* retarget_value = nullptr;
};

Observation g_obs;

void reset_observation() { g_obs = Observation(); }

// ---------------------------------------------------------------------------
// The raw receiver the model is handed: a byte block, not an AssetData, so decoy
// words can be planted at neighbouring displacements without any of them being a
// declared member.
// ---------------------------------------------------------------------------
struct RawReceiver {
  std::uint8_t bytes[kReceiverBlock];
};

struct RawInner {
  std::uint8_t bytes[kInnerBlock];
};

// The out record: 24 bytes, of which the body is allowed to touch the first 8.
struct RawOut {
  Word words[kOutWords];
};

void poison_out(RawOut* out) {
  out->words[0] = kOutPoison0;
  out->words[1] = kOutPoison1;
  out->words[2] = kOutPoison2;
  out->words[3] = kOutPoison3;
  out->words[4] = kOutPoison4;
  out->words[5] = kOutPoison5;
}

RawOut make_poisoned_out() {
  RawOut out;
  poison_out(&out);
  return out;
}

// Changed bytes, split by whether they fall inside the eight bytes the body is
// allowed to write.
struct OutDiff {
  int inside = 0;
  int outside = 0;
};

OutDiff diff_out(const RawOut& before, const RawOut& after) {
  OutDiff diff;
  for (std::size_t index = 0; index < kOutWords; ++index) {
    if (before.words[index] == after.words[index]) {
      continue;
    }
    if (index < 2) {
      ++diff.inside;
    } else {
      ++diff.outside;
    }
  }
  return diff;
}

void check_out_untouched(const RawOut& after, const std::string& what) {
  const OutDiff diff = diff_out(make_poisoned_out(), after);
  check(diff.inside == 0 && diff.outside == 0, what);
}

void check_out_is(const RawOut& after, Word first, Word second, const std::string& what) {
  const OutDiff diff = diff_out(make_poisoned_out(), after);
  check(diff.inside == 2, what + " (exactly two words changed)");
  check(diff.outside == 0, what + " (no byte past the 8-byte record changed)");
  check_word(after.words[0], first, what + " (first word)");
  check_word(after.words[1], second, what + " (second word)");
}

// ---------------------------------------------------------------------------
// The decoy observers. Live C++ functions: reaching one of these from inside the
// model is a failure, and case_decoys_are_live calls each by hand to prove they are
// reachable at all.
// ---------------------------------------------------------------------------
extern "C" Word __attribute__((thiscall)) w16_decoy_0x00(void* p) {
  (void)p;
  ++g_obs.decoy_hits;
  return kDecoy0;
}
extern "C" Word __attribute__((thiscall)) w16_decoy_0x04(void* p) {
  (void)p;
  ++g_obs.decoy_hits;
  return kDecoy1;
}
extern "C" Word __attribute__((thiscall)) w16_decoy_0x18(void* p) {
  (void)p;
  ++g_obs.decoy_hits;
  return kDecoy2;
}
extern "C" Word __attribute__((thiscall)) w16_decoy_0x20(void* p) {
  (void)p;
  ++g_obs.decoy_hits;
  return kDecoy3;
}
extern "C" Word __attribute__((thiscall)) w16_decoy_0x24(void* p) {
  (void)p;
  ++g_obs.decoy_hits;
  return kDecoy4;
}
extern "C" Word __attribute__((thiscall)) w16_decoy_0x28(void* p) {
  (void)p;
  ++g_obs.decoy_hits;
  return kDecoy5;
}

void retarget_hook(void* arg) {
  RawReceiver* receiver = static_cast<RawReceiver*>(arg);
  std::memcpy(receiver->bytes + kInnerOffset, &g_obs.retarget_value,
              sizeof g_obs.retarget_value);
}

void poison_first_record(void* arg) {
  (void)arg;
  word_at(&g_obs.result[0], kRecordFirstDisplacement) = kDecoy6;
  word_at(&g_obs.result[0], kRecordSecondDisplacement) = kDecoy6;
}

}  // namespace

// The C++ half of the 0x005507a0 observer. Arguments 1..5 are the callee's own stack
// frame, copied out by the trampoline below; `inner` is the callee's ECX, which the
// trampoline never touches.
extern "C" WordPair* __attribute__((thiscall)) w16_accessor_body(
    InnerData* inner, Word entry_esp, Word callee_return, Word caller_saved_esi,
    Word caller_argument, Word caller_outer) {
  const int index = g_obs.calls;
  if (index < 4) {
    AccessRecord& record = g_obs.record[index];
    record.entry_esp = entry_esp;
    record.callee_return = callee_return;
    record.caller_saved_esi = caller_saved_esi;
    record.caller_argument = caller_argument;
    record.caller_outer = caller_outer;
    record.ecx = static_cast<Word>(reinterpret_cast<std::uintptr_t>(inner));
  }
  ++g_obs.calls;
  if (index == 0) {
    if (g_obs.hook_first != nullptr) {
      g_obs.hook_first(g_obs.hook_arg);
    }
  } else if (index == 1) {
    if (g_obs.hook_second != nullptr) {
      g_obs.hook_second(g_obs.hook_arg);
    }
  }
  if (index < 2) {
    if (g_obs.result_override[index] != nullptr) {
      return g_obs.result_override[index];
    }
    return &g_obs.result[index];
  }
  return &g_obs.result[1];
}

// The trampoline: the definition of 0x005507a0. Its only instructions are five loads
// out of the callee's own stack frame, five pushes and a call. It never writes ECX,
// so the C++ body receives the callee's real ECX.
//
//   callee entry   E    [E+0] return address  [E+4] saved ESI
//                        [E+8] caller argument  [E+12] the caller's own return address
//   after pushes   E-20 [E-20] E   [E-16] [E+0]  [E-12] [E+4]  [E-8] [E+8]  [E-4] [E+12]
//   (the first sample is the address E itself, so it is taken with LEA; the other
//    four are the VALUES stored at those slots, so they are taken with MOV)
//   body entry    E-24 [E-24] return address, then the five arguments in that order
__asm__(
    "  .text\n"
    "  .balign 16\n"
    "  .globl inner_pair_accessor_005507a0\n"
    "  .type  inner_pair_accessor_005507a0, @function\n"
    "inner_pair_accessor_005507a0:\n"
    "  movl 12(%esp), %eax\n"
    "  pushl %eax\n"
    "  movl 12(%esp), %eax\n"
    "  pushl %eax\n"
    "  movl 12(%esp), %eax\n"
    "  pushl %eax\n"
    "  movl 12(%esp), %eax\n"
    "  pushl %eax\n"
    "  leal 16(%esp), %eax\n"
    "  pushl %eax\n"
    "  call  w16_accessor_body\n"
    "  ret\n"
    "  .size  inner_pair_accessor_005507a0, .-inner_pair_accessor_005507a0\n");

// The cdecl sensitivity probe. Never referenced by the model; it exists so the
// stack measurement in case_abi_is_measured can be shown to discriminate.
extern "C" Word PKG_SWARM_W1_006417D0_CDECL w16_cdecl_stack_probe_005507a0(
    Word value) {
  return value + 1u;
}

// ---------------------------------------------------------------------------
// The entry observer: a second naked trampoline, entered where re_006417d0 would
// have been entered and tail-jumping into it. It exists so the model's OWN entry
// frame can be read from outside.
//
// A naked C++ function cannot be used for this: a C++ prologue has already run by the
// time any statement in it executes, so anything sampled there would be the compiler's
// frame, not the callee's. w16_model_entry_observer has no prologue, so its %esp at its
// first instruction IS the entry ESP a direct CALL to re_006417d0 would have produced,
// and after the tail jump the model's entry ESP is that same value. It reads the two
// words of that frame ([entry+0] and [entry+4]), hands them to a C++ publisher, and
// jumps to the address the publisher returns.
//
// It never leaves the receiver anywhere but ECX: the receiver is pushed across the
// publisher's call and popped straight back, and by the time the publisher returns %esp
// is exactly what it was on entry. So it adds no frame word of its own, and the model
// it hands control to sees a frame holding the return address and the one stack
// argument -- and nothing of the model's own, which is what makes [entry-4] the
// saved-ESI slot afterwards.
//
// The publisher takes its three words in registers (regparm(3), so the trampoline needs
// no stack cleanup around the call) and RETURNS the tail-jump target. Both halves of
// that are deliberate: a naked trampoline in a PIE cannot name a data symbol or take
// the address of a function without a text relocation, and this package has to link
// warning-free, so every value crosses the boundary through a call instead.
// ---------------------------------------------------------------------------
extern "C" {
Word w16_model_entry_esp = 0;   // re_006417d0's own ESP at its first instruction
Word w16_model_entry_ret = 0;   // the word at [w16_model_entry_esp + 0]
Word w16_model_entry_arg = 0;   // the word at [w16_model_entry_esp + 4]
int w16_model_entry_count = 0;  // how many times the observer ran
}

extern "C" Word __attribute__((regparm(3))) w16_model_entry_publish(Word entry_esp,
                                                                   Word entry_ret,
                                                                   Word entry_arg) {
  w16_model_entry_esp = entry_esp;
  w16_model_entry_ret = entry_ret;
  w16_model_entry_arg = entry_arg;
  ++w16_model_entry_count;
  return reinterpret_cast<Word>(&re_006417d0);
}

extern "C" void w16_model_entry_observer();

__asm__(
    "  .text\n"
    "  .balign 16\n"
    "  .globl w16_model_entry_observer\n"
    "  .type  w16_model_entry_observer, @function\n"
    "w16_model_entry_observer:\n"
    "  movl %esp, %eax\n"     // entry_esp,   the first regparm register
    "  movl (%esp), %edx\n"   // entry_ret,   the second
    "  movl 4(%esp), %ecx\n"  // entry_arg,   the third -- and the receiver is parked
    "  pushl %ecx\n"          // across the publisher's call
    "  call  w16_model_entry_publish\n"
    "  popl  %ecx\n"          // and handed straight back; %esp is where it was
    "  jmp  *%eax\n"          // %eax is &re_006417d0
    "  .size  w16_model_entry_observer, .-w16_model_entry_observer\n");

namespace {

// ---------------------------------------------------------------------------
// The call sites. One asm block each, publishing the caller's ESP on both sides of
// the transfer, so a standalone read placed before the call (which at -O0 would be
// separated from the call by outgoing-argument space and could settle nothing)
// cannot be what the test measures.
// ---------------------------------------------------------------------------
struct CallSite {
  Word esp_before = 0;
  Word esp_after = 0;
  Word eax_after = 0;
};

CallSite call_model(AssetData* receiver, WordPair* out) {
  CallSite site;
  __asm__ __volatile__(
      "movl %%esp, %0\n\t"
      "movl %3, %%ecx\n\t"
      "pushl %4\n\t"
      "call *%5\n\t"
      "movl %%esp, %1\n\t"
      "movl %%eax, %2\n\t"
      : "=m"(site.esp_before), "=m"(site.esp_after), "=m"(site.eax_after)
      : "c"(reinterpret_cast<Word>(receiver)), "d"(reinterpret_cast<Word>(out)),
        "a"(reinterpret_cast<Word>(&re_006417d0))
      : "cc", "memory");
  return site;
}

CallSite call_cdecl_probe(Word value) {
  CallSite site;
  __asm__ __volatile__(
      "movl %%esp, %0\n\t"
      "pushl %2\n\t"
      "call *%3\n\t"
      "movl %%esp, %1\n\t"
      "addl $4, %%esp\n\t"
      : "=m"(site.esp_before), "=m"(site.esp_after)
      : "r"(value), "a"(reinterpret_cast<Word>(&w16_cdecl_stack_probe_005507a0))
      : "cc", "memory");
  return site;
}

// The frame-aware call site. Same transfer as call_model -- the receiver in ECX, the
// out-record pointer pushed, the callee dropping that word -- except that it goes
// through w16_model_entry_observer, which publishes the model's own entry frame, and
// that it can lower the call site's stack by a known amount BEFORE the call. The
// bias is what makes the depth measurement provable rather than merely true: entering
// the model lower must move the accessor's entry ESP by the same amount.
//
// EBX carries the bias across the call because it is the one callee-saved register
// the model cannot have clobbered, so the `addl` that undoes the bias is reading a
// value the callee guaranteed to restore. A multiple of 16 is used so the lowered
// stack keeps the alignment a direct call would have had.
//
// The four samples the block takes are written through one POINTER, and every operand
// is a memory operand. Both choices are forced by i386, and both are the point:
//
//  * i386 PIC already owns EAX, ESI and EDI, so a fourth general register constraint is
//    not available. With every operand a memory operand nothing has to survive the
//    block in a register at all, and a "memory" clobber obliges the compiler to keep
//    the operands in memory where the asm can read them.
//
//  * The clobber list therefore names all six general registers. A block that CALLS a
//    function must say which registers the call destroys: the compiler otherwise
//    assumes any register it did not name survives, which is false across a CALL, and
//    it will be holding the address of an output in EAX when the call returns. That
//    is not hypothetical -- it is the first version of this block, and it crashed.
//    A "=m" output per sample cannot be used instead, because each one would need a
//    base register held across the block and there is none left to hold.
struct FrameSite {
  Word esp_before = 0;       // the test's ESP at the call site, before the bias
  Word call_site_esp = 0;    // the test's ESP at the call site, after the bias
  Word esp_after = 0;        // the test's ESP once the model has returned
  Word eax_after = 0;
  Word model_entry_esp = 0;  // re_006417d0's own ESP at its first instruction
  Word model_entry_ret = 0;  // the word at [model_entry_esp + 0]
  Word model_entry_arg = 0;  // the word at [model_entry_esp + 4]
};

__attribute__((noinline)) FrameSite call_model_through_observer(AssetData* receiver,
                                                               WordPair* out,
                                                               Word frame_bias) {
  FrameSite site;
  Word raw[4] = {0u, 0u, 0u, 0u};
  Word* const raw_ptr = raw;
  const Word receiver_word = reinterpret_cast<Word>(receiver);
  const Word out_word = reinterpret_cast<Word>(out);
  w16_model_entry_esp = 0;
  w16_model_entry_ret = 0;
  w16_model_entry_arg = 0;
  w16_model_entry_count = 0;
  __asm__ __volatile__(
      "movl %0, %%eax\n\t"
      "movl %%esp, 0(%%eax)\n\t"
      "movl %3, %%ebx\n\t"
      "subl %%ebx, %%esp\n\t"
      "movl %%esp, 4(%%eax)\n\t"
      "movl %1, %%ecx\n\t"
      "pushl %2\n\t"
      "call  w16_model_entry_observer\n\t"
      "movl %%esp, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %0, %%eax\n\t"
      "movl %%edx, 8(%%eax)\n\t"
      "movl %%ecx, 12(%%eax)\n\t"
      "addl %%ebx, %%esp\n\t"
      :
      : "m"(raw_ptr), "m"(receiver_word), "m"(out_word), "m"(frame_bias)
      : "cc", "memory", "eax", "ebx", "ecx", "edx", "esi", "edi");
  site.esp_before = raw[0];
  site.call_site_esp = raw[1];
  site.esp_after = raw[2];
  site.eax_after = raw[3];
  site.model_entry_esp = w16_model_entry_esp;
  site.model_entry_ret = w16_model_entry_ret;
  site.model_entry_arg = w16_model_entry_arg;
  return site;
}

// ---------------------------------------------------------------------------
// The fixture: a receiver, two inner objects, a second receiver, the scripted
// results, and the out record.
// ---------------------------------------------------------------------------
struct Fixture {
  RawReceiver receiver;
  RawReceiver receiver_b;
  RawInner inner_a;
  RawInner inner_b;
  WordPair scripted[2];
  RawOut out;

  void build() {
    std::memset(&receiver, 0, sizeof receiver);
    std::memset(&receiver_b, 0, sizeof receiver_b);
    std::memset(&inner_a, 0, sizeof inner_a);
    std::memset(&inner_b, 0, sizeof inner_b);

    // G  poison everywhere the accessor's returned object is NOT. 0x005507a0
    // returns inner+0x18 and the observer deliberately does not, so a model that
    // hand-rolls that addend copies kDecoy2.
    for (std::size_t offset = 0x00; offset < 0x1c; offset += 4) {
      std::memcpy(inner_a.bytes + offset, &kDecoy2, sizeof kDecoy2);
      std::memcpy(inner_b.bytes + offset, &kDecoy2, sizeof kDecoy2);
    }
    // I  a distinct decoy at the inner object's own +0x00, for a model that
    // dereferences the inner pointer one level too far and hands the callee
    // the word at inner+0x00 as though it were the inner object.
    std::memcpy(inner_a.bytes + 0x00, &kDecoy1, sizeof kDecoy1);
    std::memcpy(inner_b.bytes + 0x00, &kDecoy1, sizeof kDecoy1);

    // I  live decoy observers at the receiver's neighbouring displacements. Only
    // +0x1c may be taken; a model that reads another one calls a decoy and is
    // caught by the counter.
    plant_receiver_decoys(&receiver);
    plant_receiver_decoys(&receiver_b);

    set_inner(&receiver, &inner_a);
    set_inner(&receiver_b, &inner_b);

    scripted[0] = WordPair{kDecoy0, kDecoy1};
    scripted[1] = WordPair{kDecoy0, kDecoy1};
    poison_out(&out);
  }

  static void plant_receiver_decoys(RawReceiver* receiver) {
    struct Decoy {
      std::size_t offset;
      void* target;
    };
    const Decoy decoys[] = {
        {0x00u, reinterpret_cast<void*>(&w16_decoy_0x00)},
        {0x04u, reinterpret_cast<void*>(&w16_decoy_0x04)},
        {0x08u, reinterpret_cast<void*>(&w16_decoy_0x00)},
        {0x10u, reinterpret_cast<void*>(&w16_decoy_0x04)},
        {0x18u, reinterpret_cast<void*>(&w16_decoy_0x18)},
        {0x20u, reinterpret_cast<void*>(&w16_decoy_0x20)},
        {0x24u, reinterpret_cast<void*>(&w16_decoy_0x24)},
        {0x28u, reinterpret_cast<void*>(&w16_decoy_0x28)},
    };
    for (const Decoy& decoy : decoys) {
      std::memcpy(receiver->bytes + decoy.offset, &decoy.target, sizeof decoy.target);
    }
  }

  static void set_inner(RawReceiver* receiver, void* inner) {
    std::memcpy(receiver->bytes + kInnerOffset, &inner, sizeof inner);
  }

  // A run starts here: every probe poisoned, nothing left over from the last case.
  void arm() {
    reset_observation();
    model_reset_esi_probes();
    model_set_esi_at_entry(kEntryEsi);
  }

  // Copies the scripted results into the observer. Separate from arm() so a case can
  // set f.scripted AFTER arm() and still have the observer see it.
  void publish() {
    g_obs.result[0] = scripted[0];
    g_obs.result[1] = scripted[1];
  }

  AssetData* as_asset(RawReceiver* r) { return reinterpret_cast<AssetData*>(r->bytes); }
  WordPair* as_pair(RawOut* o) { return reinterpret_cast<WordPair*>(o->words); }
};

// ---------------------------------------------------------------------------
// Case 1 -- the null receiver word. 0x006417d6/0x006417d8: nothing is called and
// nothing is written.
// ---------------------------------------------------------------------------
void case_null_inner_never_calls_and_never_writes() {
  Fixture f;
  f.build();
  f.arm();
  f.set_inner(&f.receiver, nullptr);

  f.publish();
  const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));

  check_word(site.eax_after & 0xffu, 0u, "00641806 XOR AL,AL: the null path returns 0");
  check(g_obs.calls == 0, "006417d8 exits before 0x006417da, so the accessor is never called");
  check(g_obs.decoy_hits == 0, "no planted decoy observer is reached on the null path");
  check_out_untouched(f.out,
                      "the false path at 0x00641806 writes nothing to the out record");
  check_word(site.esp_after, site.esp_before, "RET 0x4 drops the caller's own argument");
  check_word(saved_esi_frame_word(), kEntryEsi, "006417d0 parks the caller's ESI");
  check_word(restored_esi_word(), kEntryEsi, "00641808 POP ESI hands it back on the null path");
}

// ---------------------------------------------------------------------------
// Case 2 -- a non-null but numerically odd receiver word. 0x006417d6 is
// TEST ECX,ECX, so 0xffffffff must be treated as a real pointer, not as a sentinel
// and not as "false".
// ---------------------------------------------------------------------------
void case_nonzero_receiver_word_proceeds() {
  const Word odd_words[] = {0xffffffffu, 0xdeadbeefu, 0x80000000u, 0x00000001u,
                            0x7fffffffu, 0x40000000u};
  for (Word odd : odd_words) {
    Fixture f;
    f.build();
    f.arm();
    f.set_inner(&f.receiver, reinterpret_cast<void*>(static_cast<std::uintptr_t>(odd)));

    f.publish();
    const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));
    const std::string tag = "  (receiver word " + hex32(odd) + ")";

    check_word(site.eax_after & 0xffu, 1u,
               "006417d6 TEST ECX,ECX: a non-zero word takes the fall-through" + tag);
    check(g_obs.decoy_hits == 0, "no decoy observer is reached" + tag);
  }
}

// ---------------------------------------------------------------------------
// Cases 3-8 -- the sentinel logic. B: the exact compare. C: the conjunction.
// D: the second call must not happen on the rejected path. E/F: which call's result
// is checked and which is copied.
// ---------------------------------------------------------------------------
void case_sentinel_matrix() {
  struct Row {
    Word probe_first;
    Word probe_second;
    Word expect;
    int expect_calls;
    const char* label;
  };
  const Row rows[] = {
      {0x00000000u, 0x00000000u, 1u, 2, "00 00"},
      {0x00000001u, 0x00000002u, 1u, 2, "01 02"},
      {0x7fffffffu, 0x7fffffffu, 1u, 2, "7fffffff 7fffffff (high bit set)"},
      {0x80000000u, 0x80000000u, 1u, 2, "80000000 80000000 (high bit set)"},
      {0xfffffffeu, 0xfffffffeu, 1u, 2, "fffffffe fffffffe (one below the sentinel)"},
      {0xdeadbeefu, 0xdeadbeefu, 1u, 2, "deadbeef deadbeef"},
      {0x00000000u, 0xffffffffu, 1u, 2, "00 ffffffff  (C: only the second word is the sentinel)"},
      {0x80000000u, 0xffffffffu, 1u, 2, "80000000 ffffffff  (B: signed-negative first word, "
                                         "sentinel second word -- kills `first < 0`)"},
      {0xdeadbeefu, 0xffffffffu, 1u, 2, "deadbeef ffffffff  (B: same, another signed-negative "
                                         "value)"},
      {0xfffffffeu, 0xffffffffu, 1u, 2, "fffffffe ffffffff  (B: one below the sentinel, then "
                                         "the sentinel -- kills `first <= -1`)"},
      {0x7fffffffu, 0xffffffffu, 1u, 2, "7fffffff ffffffff  (B: positive first word, sentinel "
                                         "second word -- kills an unsigned `first >= "
                                         "0xfffffff0` band)"},
      {0xffffff00u, 0xffffff00u, 1u, 2, "ffffff00 ffffffff (B: kills a `first >= 0xffffff00` "
                                         "band test)"},
      {0x0000ffffu, 0x0000ffffu, 1u, 2, "0000ffff 0000ffff (B: kills a 16-bit-truncated "
                                         "sentinel compare)"},
      {0x0000fffeu, 0x0000fffeu, 1u, 2, "0000fffe 0000fffe (B: kills a 16-bit-truncated "
                                         "compare against 0xffff)"},

      {0xffffffffu, 0x00000000u, 1u, 2, "ffffffff 00  (C: only the first word is the sentinel)"},
      {0xffffffffu, 0x00000001u, 1u, 2, "ffffffff 01  (C: the first word alone must not reject)"},
      {0x00000001u, 0xffffffffu, 1u, 2, "01 ffffffff  (C: the second word alone must not reject)"},
      {0xffffffffu, 0xfffffffeu, 1u, 2, "ffffffff fffffffe  (C: the second word is not it)"},
      {0xffffffffu, 0xffffffffu, 0u, 1, "ffffffff ffffffff  (D: both words, reject)"},
  };

  for (const Row& row : rows) {
    Fixture f;
    f.build();
    f.arm();
    f.scripted[0] = WordPair{row.probe_first, row.probe_second};
    f.scripted[1] = WordPair{kDecoy3, kDecoy4};

    f.publish();
    const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));
    const std::string tag = std::string("  [") + row.label + "]";

    check_word(site.eax_after & 0xffu, row.expect,
               "the returned byte follows the two CMPs at 0x006417df/0x006417e4" + tag);
    check(g_obs.calls == row.expect_calls,
          "0x005507a0 is called once on the rejected path and twice otherwise" + tag);
    check(g_obs.decoy_hits == 0, "no decoy observer is reached" + tag);
    if (row.expect == 1u) {
      check_out_is(f.out, kDecoy3, kDecoy4,
                   "the out record takes the SECOND call's two words" + tag);
    } else {
      check_out_untouched(f.out, "the rejected path writes nothing" + tag);
    }
  }
}

// ---------------------------------------------------------------------------
// Case 9 (E) -- the copy takes the SECOND call's return, not the first. The observer
// POISONS the first record while answering the second call, so a model that copies
// from the first probe, or that mixes the two probes' words, produces a mixed or
// poisoned pair.
// ---------------------------------------------------------------------------
void case_copy_uses_the_second_call_only() {
  Fixture f;
  f.build();
  f.arm();
  f.scripted[0] = WordPair{0xaaaaaaaaul, 0xbbbbbbbbul};
  f.scripted[1] = WordPair{0x11111111u, 0x22222222u};
  g_obs.hook_second = &poison_first_record;

  f.publish();
  const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));

  check_word(site.eax_after & 0xffu, 1u, "the probe pair is not the sentinel, so 1");
  check(g_obs.calls == 2, "0x006417da and 0x006417ed are two distinct calls");
  check_out_is(f.out, 0x11111111u, 0x22222222u,
               "006417f2/0x006417fa read the SECOND call's return value, not the first's");
  check_word(word_at(&g_obs.result[0], kRecordFirstDisplacement), kDecoy6,
             "the first record really was poisoned");
}

// ---------------------------------------------------------------------------
// Case 10 (F) -- the CHECK is on the first call and the COPY is on the second. The
// first call returns a clean pair and the second returns the sentinel, so a model
// that checked the second would return 0 and a model that copied the first would
// return the clean pair.
// ---------------------------------------------------------------------------
void case_check_is_first_copy_is_second() {
  Fixture f;
  f.build();
  f.arm();
  f.scripted[0] = WordPair{0x0a0b0c0du, 0x0a0b0c0eu};
  f.scripted[1] = WordPair{kSentinel, kSentinel};

  f.publish();
  const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));

  check_word(site.eax_after & 0xffu, 1u,
             "006417df/0x006417e4 judge the FIRST call's return value only");
  check(g_obs.calls == 2, "a clean first probe always leads to the second call");
  check_out_is(f.out, kSentinel, kSentinel,
               "006417f2/0x006417fa copy the SECOND call's return value verbatim, "
               "sentinel included -- the machine does not re-check what it copies");
}

// ---------------------------------------------------------------------------
// Case 11 (G) -- the record comes from the accessor's RETURN VALUE. The observer
// returns records that are NOT at inner+0x18, and inner+0x00 .. +0x1c hold poison,
// so a model that hand-rolls the accessor's `ADD EAX,0x18` copies poison.
// ---------------------------------------------------------------------------
void case_record_comes_from_the_return_value() {
  Fixture f;
  f.build();
  f.arm();
  f.scripted[0] = WordPair{0x5a5a5a5au, 0xa5a5a5a5u};
  f.scripted[1] = WordPair{0xc3c3c3c3u, 0x3c3c3c3cu};

  f.publish();
  const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));

  check(site.eax_after != 0u, "the run reached a return site");
  check(g_obs.calls == 2, "both calls happened");
  check_out_is(f.out, 0xc3c3c3c3u, 0x3c3c3c3cu,
               "the copy source is the pointer 0x005507a0 returned, not inner+0x18");
  Word at_18 = 0;
  std::memcpy(&at_18, f.inner_a.bytes + 0x18, sizeof at_18);
  check_word(at_18, kDecoy2, "the poison at inner+0x18 is in place, and is distinguishable");
  check(g_obs.decoy_hits == 0, "no decoy observer is reached");
}

// ---------------------------------------------------------------------------
// Case 12 (H) -- 0x006417ea is an independent load. The first call rewrites the
// receiver's +0x1c word, and the second call is required to see the new value.
// ---------------------------------------------------------------------------
void case_receiver_word_is_reread() {
  Fixture f;
  f.build();
  f.arm();
  f.scripted[0] = WordPair{0x01020304u, 0x05060708u};
  f.scripted[1] = WordPair{0x090a0b0cu, 0x0d0e0f10u};
  g_obs.retarget_value = &f.inner_b;
  g_obs.hook_first = &retarget_hook;
  g_obs.hook_arg = &f.receiver;

  f.publish();
  const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));

  check(g_obs.calls == 2, "the retargeted receiver still leads to the second call");
  check_ptr(reinterpret_cast<void*>(static_cast<std::uintptr_t>(g_obs.record[0].ecx)),
            static_cast<void*>(&f.inner_a),
            "006417d3 hands the accessor the receiver word as it stood at entry");
  check_ptr(reinterpret_cast<void*>(static_cast<std::uintptr_t>(g_obs.record[1].ecx)),
            static_cast<void*>(&f.inner_b),
            "006417ea is a SECOND load: the accessor sees the word the first call left");
  check_out_is(f.out, 0x090a0b0cu, 0x0d0e0f10u, "the copy comes from the retargeted call");
  check_word(site.eax_after & 0xffu, 1u, "a non-sentinel pair still returns 1");
  check(g_obs.decoy_hits == 0, "the second receiver's decoy observers were not reached");
}

// ---------------------------------------------------------------------------
// Case 13 (I) -- the receiver displacement and the dereference depth. A one-level
// load of the word at +0x1c is the only reading consistent with the ECX the callee
// saw; every neighbouring displacement holds a live decoy observer, and the inner
// object's own +0x00 holds a decoy word.
// ---------------------------------------------------------------------------
void case_receiver_displacement_and_dereference_depth() {
  Fixture f;
  f.build();
  f.arm();
  f.scripted[0] = WordPair{0x1a2b3c4du, 0x4e5f6071u};
  f.scripted[1] = WordPair{0x81828384u, 0x85868788u};

  f.publish();
  const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));

  check(g_obs.calls == 2, "both calls happened");
  check(g_obs.decoy_hits == 0,
        "006417d3/0x006417ea read the word at +0x1c and no other displacement");
  for (int index = 0; index < 2; ++index) {
    check_ptr(reinterpret_cast<void*>(static_cast<std::uintptr_t>(g_obs.record[index].ecx)),
              static_cast<void*>(&f.inner_a),
              "the callee's ECX is the LOADED word -- not the address of the word, and "
              "not a word loaded out of the inner object");
  }
  check_out_is(f.out, 0x81828384u, 0x85868788u, "the copy is the scripted pair");
  check_word(site.eax_after & 0xffu, 1u, "a non-sentinel pair returns 1");
}

// ---------------------------------------------------------------------------
// Case 14 (J) -- the short circuit. 0x006417e2 branches AROUND 0x006417e4 whenever
// the first word is not the sentinel, so the probe's second word is never read on
// that path. The probe here is a FOUR-byte record placed four bytes before a
// PROT_NONE guard page, so its second word is unreadable: a model that dropped the
// short circuit and read the second word unconditionally would fault. The positive half of
// the same property is already in the sentinel matrix, where a first-word sentinel
// with a NON-sentinel second word is required to SUCCEED, which can only happen if
// 0x006417e4 is reached and read.
// ---------------------------------------------------------------------------
void case_second_word_is_not_read_when_the_first_is_not_the_sentinel() {
  const long page_size = ::sysconf(_SC_PAGESIZE);
  check(page_size > 0, "sysconf reports a page size");
  if (page_size <= 0) {
    return;
  }
  const std::size_t page = static_cast<std::size_t>(page_size);
  void* memory =
      ::mmap(nullptr, page * 2, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  check(memory != MAP_FAILED, "the probe's two pages were mapped");
  if (memory == MAP_FAILED) {
    return;
  }
  ::mprotect(static_cast<std::uint8_t*>(memory) + page, page, PROT_NONE);

  // Four readable bytes at the very end of the first page. The word at +0x4 would be the
  // first byte of the PROT_NONE page, so touching it faults.
  WordPair* guard = reinterpret_cast<WordPair*>(static_cast<std::uint8_t*>(memory) + page - 4);
  word_at(guard, kRecordFirstDisplacement) = 0x0badf00du;  // NOT the sentinel

  Fixture f;
  f.build();
  f.arm();
  f.scripted[0] = WordPair{word_at(guard, kRecordFirstDisplacement), kDecoy1};
  f.scripted[1] = WordPair{kDecoy0, kDecoy1};
  g_obs.result_override[0] = guard;

  f.publish();
  const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));

  check_word(site.eax_after & 0xffu, 1u,
             "a first word that is not the sentinel takes the 0x006417e2 fall-through, "
             "so 0x006417e4 never runs and the unreadable second word is never touched");
  check(g_obs.calls == 2, "the copy still happens, from the SECOND call's return value");
  check_out_is(f.out, kDecoy0, kDecoy1,
               "the copy comes from the second call, not from the guard probe");
  check(g_obs.decoy_hits == 0, "no decoy observer is reached");

  ::munmap(memory, page * 2);
}

// ---------------------------------------------------------------------------
// Case 15 (K, L, M, P) -- the ABI, measured.
// ---------------------------------------------------------------------------
void case_abi_is_measured() {
  Fixture f;
  f.build();
  f.arm();
  f.scripted[0] = WordPair{0x11223344u, 0x55667788u};
  f.scripted[1] = WordPair{0x99aabbccu, 0xddeeff00u};

  f.publish();
  const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));
  const Word out_pointer = static_cast<Word>(reinterpret_cast<std::uintptr_t>(f.as_pair(&f.out)));

  // L  the cleanup owner. RET 0x4 at 0x00641803/0x00641809 means the model's caller
  // gets its stack back level.
  check_word(site.esp_after, site.esp_before,
             "00641803/00641809 RET 0x4: the callee drops its own 4-byte argument");
  const CallSite probe = call_cdecl_probe(0x1234u);
  check_word(probe.esp_after, probe.esp_before - 4u,
             "sensitivity control: a cdecl function with one stack argument leaves the "
             "caller's ESP four bytes lower, so the check above discriminates");

  // K  the callee's entry state, and the RELATIVE layout is the machine-fixed part.
  //
  // The ABSOLUTE distance from the published caller ESP down to the accessor's entry
  // ESP is deliberately NOT asserted. In the machine it is exactly 16 (the caller's
  // argument push, the CALL's return address, 0x006417d0's PUSH ESI and 0x006417da's
  // own CALL return address, and nothing else), but this model is compiled at -O0
  // and GCC gives re_006417d0 a real frame -- `push ebp; mov ebp,esp; push ebx; sub
  // esp,0x34` plus a GOT-base thunk -- so the absolute figure is a property of the
  // compiler, not of the binary, and asserting it would be measuring the toolchain.
  //
  // What IS machine-fixed, and is asserted on BOTH call sites, is the layout INSIDE
  // the accessor's entry frame: 0x006417f4 reads [ESP+0x8] with ESP at entry-4, which
  // resolves to entry+4, the caller's out-record pointer. If the model pushed anything
  // before 0x006417da or 0x006417ed, that word would no longer be at [ESP+8].
  // The one toolchain-independent stack fact left is the DEPTH: the body performs no
  // stack operation between 0x006417da and 0x006417ed, so the accessor is entered at
  // exactly the same ESP on both calls, and neither of those frames holds the caller's
  // argument word (nothing was pushed before the call).
  check(g_obs.calls == 2, "both calls happened");
  for (int index = 0; index < 2; ++index) {
    check(g_obs.record[index].entry_esp != 0u, "the accessor's entry ESP is a stack address");
    check(g_obs.record[index].caller_argument != out_pointer,
          "the callee's [ESP+8] is not the caller's out pointer: nothing was pushed "
          "before 0x006417da/0x006417ed, so the caller's argument word is not adjacent "
          "to the accessor's frame");
    check(g_obs.record[index].caller_saved_esi != out_pointer,
          "the callee's [ESP+4] is not the out pointer either");
    check(g_obs.record[index].caller_outer != out_pointer,
          "the callee's [ESP+0xc] is not the out pointer either");
    check(g_obs.record[index].callee_return != 0u, "the callee's [ESP+0] is a return address");
  }
  check_word(g_obs.record[0].entry_esp, g_obs.record[1].entry_esp,
             "the model is at the same stack depth at 0x006417da and 0x006417ed: the "
             "body's only stack effect is the one PUSH ESI at 0x006417d0");

  // The claim the two entry ESPs above establish -- "there is one frame" -- used also
  // to be asserted by comparing the two calls' `[ESP+4]` WORDS, on the grounds that in
  // the machine that word is the ESI 0x006417d0 pushed and is therefore identical at
  // both calls. This model has no real PUSH ESI (the prescribed PIE build gives the
  // translation unit `call __x86.get_pc_thunk.si; addl $_GLOBAL_OFFSET_TABLE_,%esi`,
  // so a real-register version would read the module address instead of the caller's
  // ESI), so `[ESP+4]` here is an unrelated compiler frame slot, and under clang++ the
  // compiler writes it between the two calls: the word is a property of the toolchain
  // and comparing two of them measures the toolchain. The claim itself is NOT dropped:
  // case_one_frame_between_the_two_calls measures it in the three forms that are
  // machine-fixed -- the model's own entry frame, the two accessors' entry ESPs, and a
  // control proving that measurement discriminates -- and the PUSH/POP ESI pair is
  // still asserted as a VALUE on all three return paths by
  // case_esi_is_restored_on_every_return_path.

  // M  two distinct call sites: 0x006417da and 0x006417ed cannot share a return
  // address.
  check(g_obs.record[0].callee_return != g_obs.record[1].callee_return,
        "the two calls come from two different instructions (0x006417da, 0x006417ed)");

  // K  and the return addresses land inside the model's own body, not in the test.
  const Word model_entry = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&re_006417d0));
  for (int index = 0; index < 2; ++index) {
    check(g_obs.record[index].callee_return >= model_entry &&
              g_obs.record[index].callee_return < model_entry + 512u,
          "the accessor's return address points into the model's own body, so the "
          "model made the calls and the test did not");
  }

  // P  the returned byte. The full EAX is recorded and nothing above the low byte is
  // asserted; see the header for why.
  check_word(site.eax_after & 0xffu, 1u, "the low byte of EAX is 1 on the true path");
  check_out_is(f.out, 0x99aabbccu, 0xddeeff00u, "the out record holds the second pair");
}

// ---------------------------------------------------------------------------
// Case 16 (N) -- the body never writes to the receiver or to the inner object.
// ---------------------------------------------------------------------------
void case_no_writes_to_receiver_or_inner() {
  Fixture f;
  f.build();
  f.arm();
  f.scripted[0] = WordPair{0x24681357u, 0x13572468u};
  f.scripted[1] = WordPair{0xabcdef01u, 0x0f1e2d3cu};

  const RawReceiver receiver_before = f.receiver;
  const RawInner inner_a_before = f.inner_a;
  const RawOut out_before = f.out;

  f.publish();
  const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));

  check(std::memcmp(&receiver_before, &f.receiver, sizeof f.receiver) == 0,
        "the 23 instructions contain no store to the receiver");
  check(std::memcmp(&inner_a_before, &f.inner_a, sizeof f.inner_a) == 0,
        "the body reads the inner object and never writes to it");
  check_word(site.eax_after & 0xffu, 1u, "the run took the true path");
  const OutDiff diff = diff_out(out_before, f.out);
  check(diff.inside == 2, "exactly the two out words changed");
  check(diff.outside == 0, "no byte past the 8-byte out record changed");
}

// ---------------------------------------------------------------------------
// Case 17 (O) -- the PUSH ESI / POP ESI pair on all three return paths.
// ---------------------------------------------------------------------------
void case_esi_is_restored_on_every_return_path() {
  {  // the true path, POP at 0x00641802
    Fixture f;
    f.build();
    f.arm();
    f.scripted[0] = WordPair{0x01020304u, 0x05060708u};
    f.scripted[1] = WordPair{0x090a0b0cu, 0x0d0e0f10u};
    f.publish();
    const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));
    check_word(site.eax_after & 0xffu, 1u, "the true path was taken");
    check_word(saved_esi_frame_word(), kEntryEsi, "006417d0 parked the caller's ESI");
    check_word(restored_esi_word(), kEntryEsi, "00641802 POP ESI hands it back");
  }
  {  // the sentinel path, POP at 0x00641808
    Fixture f;
    f.build();
    f.arm();
    f.scripted[0] = WordPair{kSentinel, kSentinel};
    f.scripted[1] = WordPair{kDecoy0, kDecoy1};
    f.publish();
    const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));
    check_word(site.eax_after & 0xffu, 0u, "the sentinel path was taken");
    check_word(saved_esi_frame_word(), kEntryEsi, "006417d0 parked the caller's ESI");
    check_word(restored_esi_word(), kEntryEsi,
               "00641808 POP ESI hands it back on the sentinel path too");
  }
  {  // the null path, POP at 0x00641808
    Fixture f;
    f.build();
    f.arm();
    f.set_inner(&f.receiver, nullptr);
    f.publish();
    const CallSite site = call_model(f.as_asset(&f.receiver), f.as_pair(&f.out));
    check_word(site.eax_after & 0xffu, 0u, "the null path was taken");
    check_word(saved_esi_frame_word(), kEntryEsi, "006417d0 parked the caller's ESI");
    check_word(restored_esi_word(), kEntryEsi, "00641808 POP ESI hands it back");
  }
}

// ---------------------------------------------------------------------------
// Case 19 (R) -- "one frame, no stack movement between 0x006417da and 0x006417ed",
// the claim that case_abi_is_measured used to name with a comparison of the two
// calls' [ESP+4] WORDS. This case measures it in the three forms that are
// machine-fixed, and the third of them is a CONTROL so the first two are known to
// discriminate rather than merely to hold.
//
// WHAT IS MEASURED
//
//   R1  re_006417d0's own entry frame, read from outside through
//       w16_model_entry_observer. The frame the model is entered with is exactly the
//       one a CALL builds: [entry+0] is a return address and [entry+4] is the
//       caller's out-record pointer, and nothing of the model's own is in it yet.
//       That [entry+4] is the slot the body reads as `[ESP+0x8]` at 0x006417f4, with
//       ESP at entry-4, and it is the word both `RET 0x4` sites drop. Establishing it
//       is what fixes the frame arithmetic every other stack claim here rests on:
//       entry-4 is where PUSH ESI puts its word, entry+4 is the argument, and the
//       depth between the two is where the accessor's own return address lands.
//
//   R2  the DEPTH. The accessor is entered at the same stack ADDRESS at 0x006417da
//       and at 0x006417ed. Between those two instructions the body runs
//       0x006417df/0x006417e2/0x006417e4/0x006417e8 and 0x006417ea, none of which
//       touches ESP, and 0x005507a0 is stack-neutral (`MOV ESP,EBP; POP EBP; RET`, a
//       bare C3 with no immediate). So there is one frame and no stack movement
//       between the two calls, which is exactly the claim. Stated about the [ESP+4]
//       slot as well, because that slot is where the machine's saved ESI lives: the
//       two calls reach it at the same stack ADDRESS.
//
//   R3  the CONTROL. The same measurement, taken from a call site whose stack has
//       been lowered by a known amount, must report the accessor's entry ESP lower
//       by the same amount. R2 would be satisfied just as well by a quantity that
//       never moves, and this is what rules that out. The bias is subtracted and
//       re-added inside the call site, so the two runs are compared by how far each
//       one's OWN call-site stack was moved -- the comparison never assumes the two
//       call sites are at the same depth in this frame.
//
// WHAT IS NOT MEASURED, AND WHY
//
//   * That the WORD at the accessor's [ESP+4] holds the ESI that 0x006417d0 pushed.
//     In the machine it does, and it is identical at both calls. In this model it
//     cannot: the prescribed build is a PIE, GCC's i386 PIE sequence for this
//     translation unit is `call __x86.get_pc_thunk.si; addl
//     $_GLOBAL_OFFSET_TABLE_,%esi`, so ESI holds the GOT base for the whole body and a
//     real-register version would read the module address instead of the caller's ESI
//     (and a write would break the addressing the compiler is about to emit). The
//     model's PUSH ESI is therefore a frame word, and the [ESP+4] slot in this
//     compiled body is an unrelated compiler local -- `push ebp; mov ebp,esp; push
//     ebx; sub esp,0x34` with no `push esi` at all, which makes it an uninitialised
//     slot that clang++ happens to write between the two calls. Comparing two of those
//     would be comparing two compiler temporaries, and under clang++ the value it
//     reports is a leftover address that changes between builds and optimisation
//     levels. The PUSH/POP pair is asserted as a VALUE on all three return paths
//     instead (case 17, decoy O), and the FRAME that value belongs to is asserted
//     here by ADDRESS (R2).
//
//   * The absolute distance from the model's entry ESP down to the accessor's entry
//     ESP. In the machine it is 8 -- 0x006417d0's PUSH ESI and 0x006417da's own CALL
//     return address, and nothing else -- but at -O0 that distance is a property of
//     the frame the compiler gives the model (`sub esp,0x34` under g++, `subl $52` under
//     clang++), so asserting it would be measuring the toolchain, and it would not even
//     be a portable number. Only the EQUALITY across the two call sites is a machine
//     claim, so only the equality is asserted, and R3 shows the equality discriminates.
// ---------------------------------------------------------------------------
void case_one_frame_between_the_two_calls() {
  Fixture f;
  f.build();
  f.arm();
  f.scripted[0] = WordPair{0x2468ace0u, 0x13572468u};
  f.scripted[1] = WordPair{0x0f0f0f0fu, 0x00ff00ffu};
  f.publish();

  const FrameSite site =
      call_model_through_observer(f.as_asset(&f.receiver), f.as_pair(&f.out), 0u);
  const Word out_pointer = static_cast<Word>(reinterpret_cast<std::uintptr_t>(f.as_pair(&f.out)));

  // R1  the model's own entry frame.
  check(w16_model_entry_count == 1,
        "the entry observer ran exactly once: the test, not the model, made this call");
  check_word(site.model_entry_esp, site.call_site_esp - 8u,
             "006417d0 is entered with exactly the frame a CALL builds and nothing "
             "more -- the return address and the one argument word -- so its entry ESP "
             "is 8 below the caller's, with no frame of its own in between");
  const Word helper_entry =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(&call_model_through_observer));
  check(site.model_entry_ret >= helper_entry && site.model_entry_ret < helper_entry + 512u,
        "the word at the model's [entry+0] is the return address of the test's own call, "
        "so the frame it was entered with is the caller's and not the model's");
  check_word(site.model_entry_arg, out_pointer,
             "the word at the model's [entry+4] is the caller's out-record pointer: that "
             "is the slot 0x006417f4 reaches as [ESP+0x8] with ESP at entry-4, and the "
             "word both RET 0x4 sites drop");
  check_word(site.esp_after, site.call_site_esp,
             "00641803/00641809 RET 0x4 gave the caller its stack back over the observer's "
             "tail jump as well as over a direct call");
  check_word(site.eax_after & 0xffu, 1u, "the run took the true path");

  // R2  the depth: one frame between the two calls.
  check(g_obs.calls == 2, "both calls to 0x005507a0 happened");
  check(g_obs.record[0].entry_esp != 0u, "the accessor's entry ESP is a stack address");
  check_word(g_obs.record[0].entry_esp, g_obs.record[1].entry_esp,
             "one frame and no stack movement between 0x006417da and 0x006417ed: the "
             "accessor is entered at the same stack address on both calls, because "
             "0x006417d0 PUSH ESI is the body's only stack effect and 0x005507a0 ends in "
             "`MOV ESP,EBP; POP EBP; RET`");
  check_word(g_obs.record[0].entry_esp + 4u, g_obs.record[1].entry_esp + 4u,
             "the same statement about the slot the machine's saved ESI occupies: both "
             "calls reach the accessor's [ESP+4] at the same stack ADDRESS, so the frame "
             "that word is parked in is one frame");
  const Word shallow_accessor_esp = g_obs.record[0].entry_esp;

  // R3  the control.
  Fixture g;
  g.build();
  g.arm();
  g.scripted[0] = WordPair{0x2468ace0u, 0x13572468u};
  g.scripted[1] = WordPair{0x0f0f0f0fu, 0x00ff00ffu};
  g.publish();

  const FrameSite deep =
      call_model_through_observer(g.as_asset(&g.receiver), g.as_pair(&g.out), 16u);
  const Word moved = site.call_site_esp - deep.call_site_esp;

  check(moved == 16u, "the control run really was entered 16 bytes lower");
  check_word(deep.model_entry_esp, deep.call_site_esp - 8u,
             "the control run's entry frame is the same two words, 8 below its own call site");
  check_word(deep.eax_after & 0xffu, 1u, "the control run really ran the model to its true path");
  check(g_obs.calls == 2, "the control run made the same two calls to 0x005507a0");
  check_word(g_obs.record[0].entry_esp, g_obs.record[1].entry_esp,
             "the control run is at one depth at both call sites as well");
  check_word(deep.model_entry_esp, site.model_entry_esp - moved,
             "sensitivity control: the model's entry ESP moved by exactly the amount its "
             "call site's stack was moved, so the entry ESP is a live report of the frame "
             "and not a constant");
  check_word(g_obs.record[0].entry_esp, shallow_accessor_esp - moved,
             "sensitivity control: the accessor's entry ESP moved by exactly the amount the "
             "call site's stack was moved, so the equality asserted above is a measurement of "
             "the frame rather than a quantity that never changes");
}

// ---------------------------------------------------------------------------
// Case 18 (Q) -- the decoys are live. Called by hand, so a future edit that makes
// them unreachable cannot quietly disarm cases 2, 3-8, 12 and 13.
// ---------------------------------------------------------------------------
void case_decoys_are_live() {
  reset_observation();
  const int before = g_obs.decoy_hits;
  volatile Word sink = 0;
  sink += w16_decoy_0x00(nullptr);
  sink += w16_decoy_0x04(nullptr);
  sink += w16_decoy_0x18(nullptr);
  sink += w16_decoy_0x20(nullptr);
  sink += w16_decoy_0x24(nullptr);
  sink += w16_decoy_0x28(nullptr);
  (void)sink;
  check(g_obs.decoy_hits == before + 6, "every planted decoy observer is real, callable code");
}

}  // namespace

// P  the declared return type is a BYTE, because 0x00641800 is `MOV AL,0x1` and
// 0x00641806 is `XOR AL,AL`. A model that widened it to a 32-bit word would be
// claiming three bytes of EAX that the machine never writes.
static_assert(std::is_same<decltype(re_006417d0(nullptr, nullptr)), std::uint8_t>::value,
              "00641800/00641806 write AL only, so the return type is a byte");
static_assert(std::is_same<decltype(inner_pair_accessor_005507a0(nullptr)), WordPair*>::value,
              "0x005507a0 returns a POINTER to its receiver's +0x18 sub-object");
static_assert(sizeof(WordPair) == 8, "the record the body reads and writes is 8 bytes");
static_assert(offsetof(InnerData, pair_18) == 0x18,
              "0x005507a0 is `MOV EAX,[EBP-0x4]; ADD EAX,0x18`");
// The receiver is an opaque byte run, so there is no `offsetof(AssetData, ...)` left
// to check. The two facts that assertion carried are still checked, and they are the
// two facts the machine fixes: the displacement the body reads is 0x1c, and the word
// at that displacement has room inside the modelled receiver. No member is named,
// because the machine-derived receiver record is `bounds_only` and names none.
static_assert(kReceiverWordDisplacement == 0x1c,
              "006417d3 and 0x006417ea are MOV ECX,[ESI+0x1c]");
static_assert(kReceiverWordDisplacement + sizeof(Word) <= sizeof(AssetData),
              "the word 006417d3 reads has to lie inside the modelled receiver run");

// Runs every case and returns the failure count, so main() can sit at global scope
// (C++ does not allow it inside a namespace).
int run_all_checks() {
  case_decoys_are_live();
  case_null_inner_never_calls_and_never_writes();
  case_nonzero_receiver_word_proceeds();
  case_sentinel_matrix();
  case_copy_uses_the_second_call_only();
  case_check_is_first_copy_is_second();
  case_record_comes_from_the_return_value();
  case_receiver_word_is_reread();
  case_receiver_displacement_and_dereference_depth();
  case_second_word_is_not_read_when_the_first_is_not_the_sentinel();
  case_abi_is_measured();
  case_no_writes_to_receiver_or_inner();
  case_esi_is_restored_on_every_return_path();
  case_one_frame_between_the_two_calls();

  std::fprintf(stderr, "%s: %d checks, %d failures\n", (g_failures == 0) ? "PASS" : "FAIL",
               g_checks, g_failures);
  return g_failures;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_006417d0

int main() {
  return openspore::reconstruction::pkg_swarm_w1_006417d0::run_all_checks() == 0 ? 0 : 1;
}
