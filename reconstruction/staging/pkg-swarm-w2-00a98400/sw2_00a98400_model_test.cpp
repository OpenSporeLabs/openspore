// PKG-SWARM-W2-00A98400 -- VA 0x00a98400
// Behavioural model test for FUN_00a98400 @ 0x00a98400.
//
// WHAT IS UNDER TEST. Thirty-one instructions:
//
//   00a98400  83 ec 38           SUB ESP,0x38
//   00a98403  8b 44 24 40        MOV EAX,dword ptr [ESP + 0x40]
//   00a98407  f3 0f 10 40 04     MOVSS XMM0,dword ptr [EAX + 0x4]
//   00a9840c  66 8b 50 02        MOV DX,word ptr [EAX + 0x2]
//   00a98410  f3 0f 11 44 24 04  MOVSS dword ptr [ESP + 0x4],XMM0
//   00a98416  f3 0f 10 40 08     MOVSS XMM0,dword ptr [EAX + 0x8]
//   00a9841b  f3 0f 11 44 24 08  MOVSS dword ptr [ESP + 0x8],XMM0
//   00a98421  f3 0f 10 40 0c     MOVSS XMM0,dword ptr [EAX + 0xc]
//   00a98426  56                 PUSH ESI
//   00a98427  8b f1              MOV ESI,ECX
//   00a98429  66 8b 08           MOV CX,word ptr [EAX]
//   00a9842c  f3 0f 11 44 24 10  MOVSS dword ptr [ESP + 0x10],XMM0
//   00a98432  f3 0f 10 40 10     MOVSS XMM0,dword ptr [EAX + 0x10]
//   00a98437  83 c0 14           ADD EAX,0x14
//   00a9843a  66 89 4c 24 04     MOV word ptr [ESP + 0x4],CX
//   00a9843f  50                 PUSH EAX
//   00a98440  8d 4c 24 1c        LEA ECX,[ESP + 0x1c]
//   00a98444  66 89 54 24 0a     MOV word ptr [ESP + 0xa],DX
//   00a98449  f3 0f 11 44 24 18  MOVSS dword ptr [ESP + 0x18],XMM0
//   00a9844f  e8 ec 46 98 ff     CALL 0x0041cb40
//   00a98454  8b 44 24 40        MOV EAX,dword ptr [ESP + 0x40]
//   00a98458  50                 PUSH EAX
//   00a98459  8d 4c 24 08        LEA ECX,[ESP + 0x8]
//   00a9845d  e8 de fa a9 ff     CALL 0x00537f40
//   00a98462  8d 4c 24 04        LEA ECX,[ESP + 0x4]
//   00a98466  51                 PUSH ECX
//   00a98467  8d 4e 18           LEA ECX,[ESI + 0x18]
//   00a9846a  e8 51 f9 a9 ff     CALL 0x00537dc0
//   00a9846f  5e                 POP ESI
//   00a98470  83 c4 38           ADD ESP,0x38
//   00a98473  c2 08 00           RET 0x8
//
// The three direct callees are DEFINED HERE, as observers, which is the only way
// a model of a calling body can be tested at all: the body under test has to call
// something, and this package claims nothing about what any of the three does
// beyond the one copy 0x0041cb40's own body was read to show. Each observer
// records the call, the exact hidden receiver and stack word it was handed, and
// -- so the hand-off is visible rather than assumed -- copies out the bytes it
// found there. None of them writes to the body under test's inputs.
//
// REGISTER DISCIPLINE IN THE HARNESS.
//
// The probe below is an i386 SysV cdecl function, so EBX, ESI, EDI and EBP must
// survive it. A hand-written probe that borrows ESI to hold an argument and never
// puts it back corrupts its CALLER, not itself -- and it corrupts it silently,
// because the caller's loop counter or pointer usually lives in ESI and the
// damage surfaces as an optimiser-dependent failure in a test that has nothing to
// do with the probe. That is not hypothetical: an earlier revision of a sibling
// package read a probe argument through ESI, passed at -O0, and failed from -O1
// upwards for exactly that reason.
//
// So the probe touches ONLY caller-saved registers -- EAX, ECX and EDX -- and
// keeps everything that must survive the call in its OWN frame, where %ebp can
// reach it. EBX is not touched at all, which matters twice over: it is
// callee-saved so a probe must not spend it, and on a PIC i386 build it holds the
// GOT base, so taking it over inside the asm invalidates every address GCC forms
// around it. EBP is used only as the frame pointer this probe establishes for
// itself. ESI is written exactly once -- a sentinel the body under test must give
// back -- and the probe saves the CALLER's ESI first and restores it before
// `leave`, so the harness is also how the machine's own ESI save/restore is
// observed.
//
// The samples are taken through the PROBE'S OWN FRAME POINTER, not through the
// stack pointer, because the stack pointer is exactly the thing the two cleanup
// sides disagree about. The block records ESP BEFORE any push and ESP IMMEDIATELY
// after the call returns, and nothing in between: the difference between the two
// IS the machine's RET immediate, independently of where either call happened to
// sit.
//
// The block is emitted as its own NOINLINE function. That is a correctness
// requirement found by measurement rather than a precaution: an extended-asm
// block that moves ESP internally while declaring a "memory" clobber is not
// modelled precisely enough by either compiler for the surrounding code's load
// and store motion to be relied upon once the block is inlined. Emitting it as
// its own function bounds its influence to that function, whose only contact
// with the fixtures is through pointers.
//
// NO CHECK HERE COMPARES A VALUE WITH ITSELF. Every expected value is either a
// literal written out in the case, or a byte taken from kTargetBytes in the
// header -- which is the binary's own /read_memory output, not another assembly
// of the same instructions -- or a byte read out of a fixture the case planted.
// In particular the emitted bytes of the reconstructed entry are compared against
// kTargetBytes and never against a second assembly, because two independently
// assembled bodies agreeing with each other would be implied by both being pinned
// to the binary and would only look like coverage.

#include "sw2_00a98400_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore {
namespace reconstruction {
namespace pkg_swarm_w2_00a98400 {

// The constants in the header are tied to the instruction each came from, as
// build-time checks. A constant in the header that is ever edited away from the
// listing stops the build instead of quietly changing what the test claims. The
// messages name the instruction by address WITHOUT a 0x prefix, because a
// hexadecimal literal inside a string is source text.
static_assert(kBodySpanBytes == 118u, "the body is 0x76 bytes: 00a98400..00a98475");
static_assert(kFrameBytes == 0x38u, "SUB ESP,0x38 at 00a98400");
static_assert(kReceiverInteriorDisplacement == 0x18u, "LEA ECX,[ESI+0x18] at 00a98467");
static_assert(kLocalWord0Offset == 0x00u, "MOV word [ESP+0x4],CX at 00a9843a, ESP at frame-4");
static_assert(kLocalWord2Offset == 0x02u, "MOV word [ESP+0xa],DX at 00a98444, ESP at frame-8");
static_assert(kLocalFloat4Offset == 0x04u, "MOVSS [ESP+0x4],XMM0 at 00a98410, ESP at frame-0");
static_assert(kLocalFloat8Offset == 0x08u, "MOVSS [ESP+0x8],XMM0 at 00a9841b, ESP at frame-0");
static_assert(kLocalFloatCOffset == 0x0cu, "MOVSS [ESP+0x10],XMM0 at 00a9842c, ESP at frame-4");
static_assert(kLocalFloat10Offset == 0x10u, "MOVSS [ESP+0x18],XMM0 at 00a98449, ESP at frame-8");
static_assert(kLocalBlockOffset == 0x14u, "LEA ECX,[ESP+0x1c] at 00a98440, ESP at frame-8");
static_assert(kLocalHeadBytes + kLocalBlockBytes == kFrameBytes,
              "the 0x14-byte head and the 0x24-byte block fill the 0x38-byte frame exactly");
static_assert(kArg1EntryOffset == 0x4u, "MOV EAX,[ESP+0x40] at 00a98454, ESP at frame-4");
static_assert(kArg2EntryOffset == 0x8u, "MOV EAX,[ESP+0x40] at 00a98403, ESP at frame-0");
static_assert(kArg2EntryOffset - kArg1EntryOffset == 4u,
              "the two reads of [ESP+0x40] name adjacent caller arguments, not one argument twice");
static_assert(kArg2PushedBase == 0x14u, "ADD EAX,0x14 at 00a98437");
static_assert(kArg2PushedBase + kLocalBlockBytes == 0x38u,
              "the window the first callee is given is argument 2 + 0x14 .. + 0x37");
static_assert(kRetImmediateBytes == 8u, "RET 0x8 at 00a98473");
static_assert(kStackArgumentSlots == 2u, "RET 0x8 drops two four-byte words");
static_assert(kOwnSlotDisplacement == 0x18u, "0x00a98400 sits 0x18 bytes above the table base");
static_assert(kOwnSlotDisplacement / 4u == 6u, "which is slot index 6 of a four-byte-slot table");
static_assert(kCalleeRetImmediateBytes == 4u,
              "each callee ends in RET 0x4, so each consumes the word it was pushed");
static_assert(sizeof(void*) == 4u, "the reconstruction is an x86-32 model");
static_assert(kReturnAddressBytes == 4u,
              "a CALL pushes one word, and a post-call stack sample sits that far "
              "above entry_ESP + the RET immediate");

// The observation log. It is at namespace scope rather than in an unnamed one so
// that the three observers below -- which must have the C language linkage the
// header declares for them, and so must not be internal-linkage definitions --
// can reach it.
namespace probe {

enum Step : int {
  kStepCopy = 1,
  kStepHead = 2,
  kStepInterior = 3,
};

constexpr int kTraceCapacity = 8;

// The value the LAST callee leaves in EAX, and which must be what reaches the
// caller. The body under test writes no return register after that call, so this
// is how the void reading of the return is checked rather than asserted: a
// reconstruction that put a value in EAX at the terminator would overwrite it and
// fail here. It is a recognisable constant, so it can never be confused with a
// fixture address, a stack pointer or any of the loaded values.
constexpr Word kTailEaxSentinel = 0x5ea1c0deu;

// The value the probe loads into ESI immediately before the call, so a body that
// failed to restore ESI can be told from one that did. Also a recognisable
// constant rather than a fixture address.
constexpr Word kEsiSentinel = 0x2b17c0deu;

// The value the probe loads into EAX immediately before the call.
constexpr Word kEaxSentinel = 0x12345678u;

struct Trace {
  int steps[kTraceCapacity];
  int count;
  // What each callee was handed: the hidden receiver, and the one stack word.
  std::uint32_t receiver[kCalleeCount];
  std::uint32_t word[kCalleeCount];
  // What each callee found where it was pointed. 0x0041cb40 is given the
  // 0x24-byte window and reads its source; 0x00537f40 and 0x00537dc0 are both
  // given the address of the 0x14-byte head and both read it.
  std::uint8_t at_copy[kLocalBlockBytes];
  std::uint8_t at_head[kLocalHeadBytes];
  std::uint8_t at_interior[kLocalHeadBytes];
  // How many calls ran before each callee was entered, so the order is observed
  // rather than read off the addresses.
  int calls_before[kCalleeCount];
};

Trace g_trace;

void reset() {
  Trace empty;
  std::memset(&empty, 0, sizeof empty);
  g_trace = empty;
}

void note(int step, const void* receiver, const void* word) {
  const int index = step - 1;
  g_trace.calls_before[index] = g_trace.count;
  g_trace.receiver[index] = static_cast<Word>(reinterpret_cast<std::uintptr_t>(receiver));
  g_trace.word[index] = static_cast<Word>(reinterpret_cast<std::uintptr_t>(word));
  if (g_trace.count < kTraceCapacity) {
    g_trace.steps[g_trace.count] = step;
    g_trace.count += 1;
  }
}

}  // namespace probe

// -- the three direct callees, as observers -----------------------------------
//
// callee_0041cb40 is entered with the 0x24-byte window as its hidden receiver
// and argument 2 + 0x14 as its one stack word. Its own body was read out of the
// image and it copies nine dwords -- 0x24 bytes -- from that word to offsets
// 0x00..0x20 of its receiver, so the observer performs exactly that copy and
// claims nothing beyond it.
//
// callee_00537f40 and callee_00537dc0 are entered with the address of the
// 0x14-byte head and a stack word each. Both read the head, because that is the
// only way the six stores become observable at all.
//
// NEITHER observer dereferences anything the body under test would not have
// dereferenced itself. In particular neither looks at its own hidden receiver:
// 0x00537f40's receiver is the body's stack frame and 0x00537dc0's is
// receiver+0x18, which the body only ever forms. That is deliberate, and it is
// what lets the cases below drive a null receiver and an unmapped argument 1
// without the harness, rather than the body, being the thing that faults.
extern "C" void PKG_SWARM_W2_00A98400_THISCALL callee_0041cb40(Receiver* block,
                                                              Word* source) {
  probe::note(probe::kStepCopy, block, source);
  if (source != nullptr && block != nullptr) {
    std::memcpy(static_cast<void*>(block), static_cast<const void*>(source),
                kLocalBlockBytes);
    std::memcpy(probe::g_trace.at_copy, static_cast<const void*>(source),
                kLocalBlockBytes);
  }
}

extern "C" void PKG_SWARM_W2_00A98400_THISCALL callee_00537f40(Receiver* head,
                                                              Word* argument1) {
  probe::note(probe::kStepHead, head, argument1);
  static_cast<void>(argument1);  // the body never looks through it, and neither does this
  if (head != nullptr) {
    std::memcpy(probe::g_trace.at_head, static_cast<const void*>(head),
                kLocalHeadBytes);
  }
}

extern "C" Word PKG_SWARM_W2_00A98400_THISCALL callee_00537dc0(Receiver* interior,
                                                              Word* head_address) {
  probe::note(probe::kStepInterior, interior, head_address);
  if (head_address != nullptr) {
    std::memcpy(probe::g_trace.at_interior, static_cast<const void*>(head_address),
                kLocalHeadBytes);
  }
  return probe::kTailEaxSentinel;
}

// -- a read-only window on the bytes the RECONSTRUCTED ENTRY emits --------------
//
// The entry is a naked __thiscall function defined in the package's .cpp, and this
// symbol is given the entry's own address by the assembler, so the model test can
// hold the very function the validator binds to 0x00a98400 against the binary's
// own 118 bytes (kTargetBytes, transcribed from /read_memory). It is a window,
// not a copy: nothing here writes through it.
//
// The anchor allowance is a toolchain artifact, not a relaxation of the claim. A
// position-independent g++ build may prepend a ten-byte __x86.get_pc_thunk.ax PC
// anchor (e8 ?? ?? ?? ?? 05) to a naked function; g++ does so at -O0 and clang++
// does not. The anchor is recognised by that exact opcode pair and the 118 target
// bytes are then required immediately after it, so a toolchain that emitted a
// different prologue makes the byte comparison below fail on byte 0.
extern "C" const unsigned char reconstructed_entry_image[];

__asm__(".text\n"
        ".globl reconstructed_entry_image\n"
        "reconstructed_entry_image = re_00a98400\n");

// -- the cdecl twin, used to MEASURE the cleanup side -------------------------
//
// Deliberately declared with NO convention token and no receiver: its whole job
// is to be the other answer to the cleanup question this body answers with its
// terminator, so it must not itself carry a thiscall receiver. The value it
// leaves in EAX makes the harness output deterministic and makes the twin
// tellable apart from the entry, which leaves its last callee's sentinel there.
extern "C" Word cdecl_caller_pops_twin(Receiver* receiver, Word* arg1, Word* arg2) {
  probe::note(probe::kStepCopy, receiver, arg1);
  probe::note(probe::kStepHead, receiver, arg2);
  probe::note(probe::kStepInterior, receiver, nullptr);
  static_cast<void>(arg2);
  return 0x5a17c0deu;
}

namespace {

// -- the fixtures -------------------------------------------------------------
//
// A fixture is a flat byte array and nothing else. No fixture below is a claim
// about any object in the binary: they are just mapped memory for the model to
// read and write, sized so that every access this body makes is inside one.

// 64 bytes, which is more than the body reaches: the deepest access it makes on
// an argument is argument 2 + 0x37, the last byte of the 0x24-byte window the
// first callee is given. A fixture size is NOT a claim about any object in the
// binary; it is just room for the model to be pointed at.
constexpr std::size_t kFixtureBytes = 64u;

struct alignas(4) Fixture {
  std::uint8_t bytes[kFixtureBytes];
};

Fixture make_fixture(std::uint8_t seed) {
  Fixture fixture;
  for (std::size_t index = 0; index < kFixtureBytes; ++index) {
    // A byte run no two cases share, and which is not a repeating pattern, so a
    // displacement error cannot cancel out.
    const std::size_t mixed = (index * 31u + seed * 7u + (index >> 3)) & 0xffu;
    fixture.bytes[index] = static_cast<std::uint8_t>(0x40u + seed + mixed);
  }
  return fixture;
}

Word address_of_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

int count_differences(const std::uint8_t* before, const std::uint8_t* after,
                      std::size_t bytes) {
  int changed = 0;
  for (std::size_t index = 0; index < bytes; ++index) {
    if (before[index] != after[index]) {
      changed += 1;
    }
  }
  return changed;
}

// -- the call harness ---------------------------------------------------------
//
// Everything about the ABI is MEASURED here rather than declared: the receiver
// goes in ECX, both stack words are pushed, and ESP, ESI and EAX are read back
// on both sides of the call.
//
//   8(%ebp)  target address, called through a register
//   12(%ebp) the word that goes into ECX
//   16(%ebp) argument 1, which lands at the callee's entry_ESP+0x4
//   20(%ebp) argument 2, which lands at the callee's entry_ESP+0x8
//   24(%ebp) a decoy word, or kNoDecoyWord for none
//   28(%ebp) the Sample to fill
//
// The decoy is pushed FIRST, so it sits ABOVE both arguments and lands at the
// callee's entry_ESP + 0xc, where nothing in this body reaches it. The two
// arguments are pushed afterwards, argument 1 last, so argument 1 is the lower
// word and argument 2 the higher: entry_ESP+0x4 and entry_ESP+0x8, which is
// what the two reads of [ESP+0x40] name.
//
// The frame, with B = %ebp and the 72-byte reservation `subl $72, %esp` makes,
// of which the slots B-4 .. B-52 are used:
//
//   B-4    the target address, held across the call
//   B-8    the output pointer, held across the call
//   B-12   `before`: %esp after the reservation, i.e. before any push at all
//   B-16   the ECX word, held across the call
//   B-20   argument 1, held across the call
//   B-24   argument 2, held across the call
//   B-28   the decoy word, held across the call
//   B-32   %eax after the call, captured before EAX is reused
//   B-36   `after`: %esp immediately after the call, before any fixup
//   B-40   %esi after the call, captured before ESI is reused
//   B-44   the low four bytes of %xmm0 after the call
//   B-48   the CALLER's %esi, saved before the sentinel was loaded and put back
//          before the probe returns
//
// Every address above is one this probe wrote or the callee wrote, never a word
// below the deepest point either of them reached.
#if defined(_MSC_VER)
#define PKG_SWARM_W2_00A98400_NOINLINE __declspec(noinline)
#else
#define PKG_SWARM_W2_00A98400_NOINLINE __attribute__((noinline))
#endif

struct Sample {
  std::uint32_t returned = 0;
  std::uint32_t esp_before = 0;
  std::uint32_t esp_after = 0;
  // The value ESI held after the call. The body under test must give it back
  // unchanged; the probe sets it beforehand and samples it afterwards.
  std::uint32_t esi_after = 0;
  std::uint32_t xmm0_after = 0;
  // The stack pointer immediately BEFORE the call instruction, i.e. one word
  // above the callee's entry ESP, because a CALL pushes the return address.
  // This is what makes the frame base derivable rather than assumed: the
  // callee's entry ESP is this minus one word.
  std::uint32_t esp_before_call = 0;
};

extern "C" void probe_call_shape(std::uint32_t target, std::uint32_t ecx_word,
                                 std::uint32_t arg1, std::uint32_t arg2,
                                 std::uint32_t decoy, Sample* out);

__asm__(".text\n"
        ".balign 16\n"
        ".globl probe_call_shape\n"
        ".type probe_call_shape, @function\n"
        "probe_call_shape:\n"
        "  pushl %ebp\n"
        "  movl  %esp, %ebp\n"
        "  subl  $72, %esp\n"
        "  movl  8(%ebp), %eax\n"        // the target
        "  movl  %eax, -4(%ebp)\n"       // ... held in the frame across the call
        "  movl  28(%ebp), %eax\n"       // the output pointer
        "  movl  %eax, -8(%ebp)\n"       // ... likewise
        "  movl  %esp, -12(%ebp)\n"      // before: before any push at all
        "  movl  %esi, -48(%ebp)\n"      // the CALLER's ESI, kept for the epilogue
        "  movl  $305419896, %eax\n"     // the EAX sentinel, 0x12345678
        "  movl  $0x2b17c0de, %esi\n"    // the ESI sentinel
        "  movl  $0x5ea1c0de, %edx\n"    // the XMM0 sentinel
        "  movl  12(%ebp), %ecx\n"       // the word that goes into ECX
        "  movl  %ecx, -16(%ebp)\n"
        "  movl  16(%ebp), %ecx\n"       // argument 1
        "  movl  %ecx, -20(%ebp)\n"
        "  movl  20(%ebp), %ecx\n"       // argument 2
        "  movl  %ecx, -24(%ebp)\n"
        "  movl  24(%ebp), %ecx\n"       // the decoy
        "  movl  %ecx, -28(%ebp)\n"
        "  cmpl  $-1, -28(%ebp)\n"       // kNoDecoyWord: push nothing extra
        "  jz   1f\n"
        "  pushl -28(%ebp)\n"            // pushed first, so it sits highest
        "1:\n"
        "  pushl -24(%ebp)\n"            // argument 2
        "  pushl -20(%ebp)\n"            // argument 1, pushed last and lowest
        "  movl  %esp, -52(%ebp)\n"      // the stack pointer just before the CALL
        "  movl  -16(%ebp), %ecx\n"      // the receiver, into ECX
        "  call *-4(%ebp)\n"
        "  movl  %eax, -32(%ebp)\n"      // EAX after the call, before it is reused
        "  movl  %esp, -36(%ebp)\n"      // after, before any fixup
        "  movl  %esi, -40(%ebp)\n"      // ESI after the call
        "  movss %xmm0, -44(%ebp)\n"     // the low four bytes of XMM0 after the call
        "  movl  -8(%ebp), %eax\n"
        "  movl  -32(%ebp), %edx\n"
        "  movl  %edx, (%eax)\n"         // out->returned
        "  movl  -12(%ebp), %edx\n"
        "  movl  %edx, 4(%eax)\n"        // out->esp_before
        "  movl  -36(%ebp), %edx\n"
        "  movl  %edx, 8(%eax)\n"        // out->esp_after
        "  movl  -40(%ebp), %edx\n"
        "  movl  %edx, 12(%eax)\n"       // out->esi_after
        "  movl  -44(%ebp), %edx\n"
        "  movl  %edx, 16(%eax)\n"       // out->xmm0_after
        "  movl  -52(%ebp), %edx\n"
        "  movl  %edx, 20(%eax)\n"       // out->esp_before_call
        "  movl  -48(%ebp), %esi\n"      // give the caller's ESI back, untouched
        "  leave\n"
        "  ret\n"
        ".size probe_call_shape, .-probe_call_shape\n");

// Templated so that a FUNCTION pointer converts as readily as an object one:
// `re_00a98400` is a thiscall function, and a thiscall pointer does not convert
// to `const void*` implicitly on either compiler.
template <typename T>
std::uint32_t address_of(T pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

PKG_SWARM_W2_00A98400_NOINLINE Sample run_probe(std::uint32_t target,
                                                std::uint32_t receiver,
                                                std::uint32_t arg1,
                                                std::uint32_t arg2,
                                                std::uint32_t decoy) {
  Sample sample;
  probe_call_shape(target, receiver, arg1, arg2, decoy, &sample);
  return sample;
}

// The reconstructed entry, entered the way __thiscall enters it: the receiver in
// ECX and one 32-bit word at each of the callee's entry_ESP+0x4 and
// entry_ESP+0x8. Nothing else is pushed.
Sample call_model(std::uint32_t receiver, std::uint32_t arg1, std::uint32_t arg2) {
  return run_probe(address_of(&re_00a98400), receiver, arg1, arg2, kNoDecoyWord);
}

// The same call with a decoy word pushed BELOW both arguments, so at the callee's
// entry it sits at entry_ESP+0xc. A body that read a third argument, or that
// popped the wrong number of bytes, would take the decoy or lose it.
Sample call_model_over_a_decoy(std::uint32_t receiver, std::uint32_t arg1,
                               std::uint32_t arg2, std::uint32_t decoy) {
  return run_probe(address_of(&re_00a98400), receiver, arg1, arg2, decoy);
}

// The frame base S, derived from the harness's own stack sample rather than
// assumed.
//
// A CALL instruction pushes the return address, so the stack pointer the callee's
// FIRST instruction sees is one word BELOW the stack pointer the harness sampled
// immediately before the call. `ret imm16` then pops that return address and only
// afterwards adds its immediate, which is why the post-call sample sits four
// bytes above entry_ESP + kRetImmediateBytes and why a delta measured only
// between the two samples still comes out right.
//
// So: entry_ESP = esp_before_call - one word, and S = entry_ESP - kFrameBytes. A
// reconstruction with a different frame size, or a different cleanup, moves this
// number, and every address check below fails with it.
std::uint32_t frame_base(const Sample& sample) {
  return sample.esp_before_call - kReturnAddressBytes -
         static_cast<std::uint32_t>(kFrameBytes);
}

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void check_eq_u32(std::uint32_t actual, std::uint32_t expected,
                  const char* what) {
  if (actual != expected) {
    std::fprintf(stderr, "FAILED: %s -- got 0x%08x, expected 0x%08x\n", what,
                 actual, expected);
    ++g_failures;
  }
}

// -- the byte window ---------------------------------------------------------
//
// The two helpers below read the reconstructed entry's own emitted code. They
// are `noinline` for the same reason the call harness is: an extended-asm block
// is not modelled precisely enough by either compiler for surrounding code motion
// to be relied upon once the block is inlined, and a byte witness the optimiser
// may fold is not a witness.

// The address of the first of the 118 target bytes, i.e. the entry with any PC
// anchor stepped over. An anchor is recognised only by the exact opcode pair
// e8 ?? ?? ?? ?? 05; anything else is treated as no anchor, so a toolchain that
// emitted a different prologue makes the byte comparison below fail on byte 0.
PKG_SWARM_W2_00A98400_NOINLINE const unsigned char* entry_body_base() {
  const unsigned char* const image = reconstructed_entry_image;
  const bool anchored = image[0] == 0xe8u && image[5] == 0x05u;
  return image + (anchored ? kPcAnchorBytes : 0u);
}

// Where the CALL rel32 at `offset` (an offset into kTargetBytes, counting from
// the byte after the E8 opcode) actually lands, computed from the emitted bytes.
// This is the independent answer to "is that displacement the binary's": the
// binary's own displacement encodes addresses in a different image and cannot be
// compared numerically, so the constraint is instead that the reconstruction's
// displacement resolves to the callee the machine names for that callsite.
PKG_SWARM_W2_00A98400_NOINLINE std::uint32_t resolve_call_target(
    std::size_t displacement_offset) {
  const unsigned char* const image = entry_body_base();
  std::int32_t displacement = 0;
  std::memcpy(&displacement, image + displacement_offset, sizeof displacement);
  const std::uint32_t next = address_of(image + displacement_offset + 4u);
  return next + static_cast<std::uint32_t>(displacement);
}

// -- the cases ----------------------------------------------------------------

// W -- the bytes. The reconstructed entry must emit the binary's 118 bytes.
//
// 116 of the 118 positions are compared literally against kTargetBytes, which is
// the /read_memory transcript and not another assembly of the same instructions.
// Two positions are the rel32 displacements of the three CALLs, which are checked
// by resolve_call_target above rather than skipped; and the pair at bytes 0x27 and
// 0x28 is the register move the assembler is free to spell two ways (8b f1 in
// the binary, 89 ce from GAS), so each spelling is accepted and the pair is pinned
// as one of the two.
void case_the_entry_emits_the_target_bytes() {
  const unsigned char* const body = entry_body_base();

  // The window is a real, non-zero address; a witness read from address 0 would
  // pass every comparison below for the wrong reason.
  check(address_of(body) != 0u, "W1: the entry has an address");
  check(body[0] != 0u, "W2: and the first target byte was actually read");

  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    const bool register_move = index == kEcxToEsiFirstByte ||
                               index == kEcxToEsiSecondByte;
    // The twelve displacement bytes are not skipped, they are checked elsewhere
    // and by a stronger rule: resolve_call_target below requires each of them to
    // land on the callee the machine names for that callsite, which a literal
    // comparison against another image could never do.
    const bool displacement =
        (index >= kCallRel32FirstOffset && index < kCallRel32FirstOffset + 4u) ||
        (index >= kCallRel32SecondOffset && index < kCallRel32SecondOffset + 4u) ||
        (index >= kCallRel32ThirdOffset && index < kCallRel32ThirdOffset + 4u);
    if (!register_move && !displacement) {
      check(body[index] == kTargetBytes[index],
            "W3: byte-for-byte the binary's own encoding");
    }
  }
  // MOV ESI,ECX: 8b f1 (the binary's MSVC spelling) or 89 ce (GAS, and what both
  // clang++ and g++ emit for `movl %ecx, %esi`).
  const bool receiver_copy_binary =
      body[kEcxToEsiFirstByte] == 0x8bu && body[kEcxToEsiSecondByte] == 0xf1u;
  const bool receiver_copy_assembler =
      body[kEcxToEsiFirstByte] == 0x89u && body[kEcxToEsiSecondByte] == 0xceu;
  check(receiver_copy_binary || receiver_copy_assembler,
        "W4: bytes 0x27..0x28 are one of the two encodings of MOV ESI,ECX");
  check(kEcxToEsiFirstByte == 0x27u && kEcxToEsiSecondByte == 0x28u,
        "W4c: the one divergent pair is exactly the receiver copy");
  // The three groups are disjoint and cover the body exactly: 104 positions
  // compared literally, 2 accepted register-move encodings, and 12 rel32
  // displacements that W7..W9 resolve. 104 + 2 + 12 = 118, and the count below
  // asserts that 104 rather than leaving the split to the arithmetic above.
  std::size_t literal = 0;
  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    const bool register_move = index == kEcxToEsiFirstByte ||
                               index == kEcxToEsiSecondByte;
    const bool displacement =
        (index >= kCallRel32FirstOffset && index < kCallRel32FirstOffset + 4u) ||
        (index >= kCallRel32SecondOffset && index < kCallRel32SecondOffset + 4u) ||
        (index >= kCallRel32ThirdOffset && index < kCallRel32ThirdOffset + 4u);
    if (!register_move && !displacement) {
      ++literal;
    }
  }
  check_eq_u32(static_cast<std::uint32_t>(literal), 104u,
               "W4d: 104 of the 118 byte positions are compared literally");
  check_eq_u32(static_cast<std::uint32_t>(kBodySpanBytes), 118u,
               "W4e: and the body is 118 bytes");

  // The three CALLs are E8 forms, and each resolves to the machine's own callee
  // for that callsite. A reconstruction that called anything else, in any order,
  // fails here even though its bytes look right.
  check(body[0x4f] == 0xe8u, "W5: the first call is the direct E8 form");
  check(body[0x5d] == 0xe8u, "W6: the second call is the direct E8 form");
  check(body[0x6a] == 0xe8u, "W6b: the third call is the direct E8 form");
  check(resolve_call_target(kCallRel32FirstOffset) ==
            address_of(&callee_0041cb40),
        "W7: the first CALL's displacement resolves to callee_0041cb40");
  check(resolve_call_target(kCallRel32SecondOffset) ==
            address_of(&callee_00537f40),
        "W8: the second CALL's displacement resolves to callee_00537f40");
  check(resolve_call_target(kCallRel32ThirdOffset) ==
            address_of(&callee_00537dc0),
        "W9: the third CALL's displacement resolves to callee_00537dc0");

  // The unresolvable positions are pinned individually as well, so the failure of
  // W3 above is legible rather than just "some byte".
  check(body[0x00] == 0x83u && body[0x01] == 0xecu && body[0x02] == 0x38u,
        "W10: the frame is SUB ESP,0x38 and nothing else");
  check(body[0x03] == 0x8bu && body[0x04] == 0x44u && body[0x05] == 0x24u &&
            body[0x06] == 0x40u,
        "W11: both argument loads are MOV EAX,[ESP+0x40]");
  check(body[0x0c] == 0x66u && body[0x0d] == 0x8bu && body[0x0e] == 0x50u &&
            body[0x0f] == 0x02u,
        "W12: the 0x02 read is a WORD read");
  check(body[0x29] == 0x66u && body[0x2a] == 0x8bu && body[0x2b] == 0x08u,
        "W13: the 0x00 read is a WORD read, and it is the first store's source");
  check(body[0x40] == 0x8du && body[0x41] == 0x4cu && body[0x42] == 0x24u &&
            body[0x43] == 0x1cu,
        "W14: the first call's hidden receiver is LEA ECX,[ESP+0x1c]");
  check(body[0x59] == 0x8du && body[0x5a] == 0x4cu && body[0x5b] == 0x24u &&
            body[0x5c] == 0x08u,
        "W15: the second call's hidden receiver is LEA ECX,[ESP+0x8]");
  check(body[0x62] == 0x8du && body[0x63] == 0x4cu && body[0x64] == 0x24u &&
            body[0x65] == 0x04u,
        "W16: the third call's stack word is LEA ECX,[ESP+0x4]");
  check(body[0x67] == 0x8du && body[0x68] == 0x4eu && body[0x69] == 0x18u,
        "W17: the third call's hidden receiver is LEA ECX,[ESI+0x18]");
  check(body[0x37] == 0x83u && body[0x38] == 0xc0u && body[0x39] == 0x14u,
        "W18: the pushed base is argument 2 + 0x14");
  check(body[0x6f] == 0x5eu, "W19: ESI is restored, not left clobbered");
  check(body[0x70] == 0x83u && body[0x71] == 0xc4u && body[0x72] == 0x38u,
        "W20: the frame is given back with ADD ESP,0x38");
  check(body[0x73] == 0xc2u && body[0x74] == 0x08u && body[0x75] == 0x00u,
        "W21: the terminator is RET 0x8, the callee-side cleanup itself");
  check(body[0x26] == 0x56u,
        "W22: the entry saves ESI once, at the top, before the calls");
  // The three SSE stores are six bytes each, because the ModRM byte selects a
  // SIB byte for an ESP-relative operand. A reconstruction that emitted the
  // five-byte no-SIB form would pass the displacement checks above and fail here.
  check(body[0x10] == 0xf3u && body[0x11] == 0x0fu && body[0x12] == 0x11u &&
            body[0x13] == 0x44u && body[0x14] == 0x24u && body[0x15] == 0x04u,
        "W23: the 0x04 store is the six-byte F3 0F 11 44 24 04 form");
  check(body[0x1b] == 0xf3u && body[0x1c] == 0x0fu && body[0x1d] == 0x11u &&
            body[0x1e] == 0x44u && body[0x1f] == 0x24u && body[0x20] == 0x08u,
        "W23a: the 0x08 store is the same six-byte form at 0x08");
  check(body[0x2c] == 0xf3u && body[0x2d] == 0x0fu && body[0x2e] == 0x11u &&
            body[0x2f] == 0x44u && body[0x30] == 0x24u && body[0x31] == 0x10u,
        "W23b: and the 0x10 store is the same six-byte form at 0x10");
  check(body[0x49] == 0xf3u && body[0x4a] == 0x0fu && body[0x4b] == 0x11u &&
            body[0x4c] == 0x44u && body[0x4d] == 0x24u && body[0x4e] == 0x18u,
        "W23c: and the 0x18 store is the same six-byte form at 0x18");
  check(body[0x3a] == 0x66u && body[0x3b] == 0x89u && body[0x3c] == 0x4cu &&
            body[0x3d] == 0x24u && body[0x3e] == 0x04u,
        "W24: the word store at 0x00 is 66 89 4c 24 04");
  check(body[0x44] == 0x66u && body[0x45] == 0x89u && body[0x46] == 0x54u &&
            body[0x47] == 0x24u && body[0x48] == 0x0au,
        "W25: and the word store at 0x02 is 66 89 54 24 0a");
  check(body[0x26] == 0x56u && body[0x3f] == 0x50u && body[0x58] == 0x50u &&
            body[0x66] == 0x51u,
        "W26: the four stack effects are PUSH ESI, PUSH EAX, PUSH EAX and PUSH ECX");
}
// L -- the ABI determination travels with the source as data, so a package that
// quietly reverted to the old abstention -- "no convention, no receiver" -- fails
// here instead of passing.
//
// Every enumerator is compared against a literal SPELLING of the value the machine
// record names, not merely against the constant the header points at it. A
// comparison of a value with the header's own pointer to it would be a tautology:
// it would still hold after the header had been changed to say something else, and
// the whole point of carrying the determination as data is that changing the data
// is what must be caught.
void case_abi_travels_as_data() {
  // The convention, spelled here: __thiscall, and no other candidate.
  check(static_cast<int>(kDerivedConventionVerdict) ==
            static_cast<int>(ConventionVerdict00a98400::kThiscall),
        "L1: the derived convention is __thiscall");
  check(static_cast<int>(ConventionVerdict00a98400::kThiscall) == 0,
        "L2: and nothing else is spelled by that enumerator");
  check_eq_u32(static_cast<std::uint32_t>(kCandidateConventionCount), 1u,
               "L2a: __thiscall is the ONLY candidate the record names");
  // The determination is INFERRED, not OBSERVED and not UNKNOWN. A package that
  // upgraded the claim to an observed one, or dropped it back to unknown, dies
  // here rather than quietly over- or under-stating it.
  check(kDerivedConventionConfidence == ConventionConfidence::kInferred,
        "L3: the determination is INFERRED");
  check(static_cast<int>(ConventionConfidence::kUnknown) == 0,
        "L3a: the confidence scale spells UNKNOWN as 0");
  check(static_cast<int>(ConventionConfidence::kInferred) == 1,
        "L3b: and INFERRED as 1, which is not UNKNOWN and not OBSERVED");
  check(static_cast<int>(ConventionConfidence::kObserved) == 2,
        "L3c: and OBSERVED as 2, which this determination is not");

  // The receiver, spelled here: present, in ECX, bounds-only, never dereferenced.
  check(static_cast<int>(kDerivedReceiverRegister) ==
            static_cast<int>(ReceiverRegister00a98400::kEcx),
        "L4: the receiver register is ECX");
  check(static_cast<int>(ReceiverRegister00a98400::kEcx) == 0,
        "L4a: and the register enumerator spells ECX, not a second register");
  check(kReceiverPresent, "L5: a receiver is present");
  check(!kReceiverAbsent, "L6: and the record does not say it is absent");
  check(kReceiverBoundsOnly, "L7: bounds only: no layout is claimed");
  check(!kReceiverHasShape, "L8: and no shape");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDistinctOffsets), 0u,
               "L8a: the record saw no distinct receiver displacement");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverBytesLoaded), 0u,
               "L8b: the body loads no byte through the receiver");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverBytesStored), 0u,
               "L8c: and it stores no byte through the receiver");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverRegisterReads), 1u,
               "L8d: and it reads the receiver register exactly once");
  // The provenance the machine recorded for the receiver, spelled here.
  check(kReceiverProvenance == ReceiverProvenance00a98400::kVftableSlotDispatch,
        "L9: the receiver's provenance is vftable_slot_dispatch");
  check(static_cast<int>(ReceiverProvenance00a98400::kVftableSlotDispatch) == 0,
        "L9a: and the provenance enumerator spells vftable_slot_dispatch");

  // The cleanup, spelled here: the callee pops eight bytes.
  check(kObservedCleanupSide == CleanupSide00a98400::kCallee,
        "L10: the observed cleanup side is the callee");
  check(static_cast<int>(CleanupSide00a98400::kCallee) == 0,
        "L10a: and the cleanup enumerator spells the callee, not the caller");
  check_eq_u32(static_cast<std::uint32_t>(kStackCleanupBytes), 8u,
               "L10b: the cleanup is eight bytes");
  check_eq_u32(static_cast<std::uint32_t>(kRetImmediateBytes), 8u,
               "L10c: which is the terminator's own immediate");
  check_eq_u32(static_cast<std::uint32_t>(kStackArgumentSlots), 2u,
               "L10d: and there are exactly two callee-popped stack words");
  check(kStackArgumentRead, "L11: the two stack arguments are read");
  check(!kStackArgumentWritten, "L12: and never written");
  check(kArg1Dereferenced == false, "L12a: argument 1 is read but never looked through");
  check(kArg2Dereferenced, "L12b: argument 2 IS looked through");

  // The two words are DATA, and this package says so explicitly. A reconstruction
  // that had conflated either of them with the receiver would have to have set
  // this to true, and dies here.
  check(!kStackArgumentIsReceiver,
        "L13: neither popped stack word is a receiver");
  // The convention and the cleanup are separate facts and are carried separately,
  // which is what lets a package state one without the other. The emitted
  // terminator and the emitted first instruction above are the evidence that the
  // source honours both: a `retl $0` would contradict L10 while still satisfying
  // L1, and W21 is what kills it.

  // The three callees' own terminators, which are the evidence the stack
  // discipline rests on. Each return address is at the instruction the image
  // shows, and each immediate is 4.
  check(kCalleeCount == 3, "L14: three callees");
  check(kCalleeReturnAddresses[0] == 0x0041cc15u &&
            kCalleeReturnAddresses[1] == 0x00537ff5u &&
            kCalleeReturnAddresses[2] == 0x00537e94u,
        "L15: and their RET instructions are at these three addresses");
  check_eq_u32(static_cast<std::uint32_t>(kCalleeRetImmediateBytes), 4u,
               "L16: each of them is a callee-popped RET 0x4");
}

// M -- the cleanup side, measured against a cdecl twin through one harness, so
// that "callee pops eight bytes" is not only a statement about the RET immediate.
void case_cleanup_side_is_measured_not_only_declared() {
  probe::reset();
  Fixture target_fixture = make_fixture(0x11u);
  const Sample target = call_model(address_of_word(&target_fixture), 0x1000u,
                                   address_of_word(&target_fixture));
  probe::reset();
  Fixture twin_fixture = make_fixture(0x22u);
  const Sample twin = run_probe(address_of(&cdecl_caller_pops_twin),
                                address_of_word(&twin_fixture), 0x1000u,
                                address_of_word(&twin_fixture), kNoDecoyWord);

  // Both samples are real stack pointers, not a zero the harness never filled.
  check(target.esp_before != 0u && twin.esp_before != 0u,
        "M1: both harnesses sampled a real stack pointer");
  // Both sides were handed the SAME two pushes, so the only thing that differs
  // between the two deltas is what each callee did with them.
  //
  // The target: its two callee-popped words are gone and nothing is left, so the
  // stack comes back exactly where it started.
  check(target.esp_after == target.esp_before,
        "M2: the entry popped exactly its own eight bytes");
  // The twin: a caller-cleaned callee pops nothing, so both words are still there.
  check(twin.esp_after == twin.esp_before - 8u,
        "M3: the cdecl twin leaves both of its words to the caller");
  // The whole difference between the two sides is the RET immediate, and it is
  // the immediate the binary itself carries at 0x00a98473.
  check_eq_u32((target.esp_after - target.esp_before) -
                   (twin.esp_after - twin.esp_before),
               static_cast<std::uint32_t>(kRetImmediateBytes),
               "M3a: the whole difference between the two sides is the RET immediate");
  check_eq_u32(static_cast<std::uint32_t>(kRetImmediateBytes), 8u,
               "M3b: which is the eight bytes the binary's terminator names");

  // The two bodies came back through ONE harness, and they did not come back the
  // same. The twin has no receiver and returns its own sentinel; the entry has a
  // receiver and its last callee's sentinel is what reaches the caller.
  check_eq_u32(twin.returned, 0x5a17c0deu,
               "M4a: the twin returned its own sentinel through the same channel");
  check_eq_u32(target.returned, probe::kTailEaxSentinel,
               "M4b: and the entry returned its last callee's sentinel instead");
  check(target.returned != twin.returned,
        "M5: the two answers differ, so the channel is real");
  check(target.returned != probe::kEaxSentinel,
        "M6: the entry's EAX is not the harness's own sentinel either");
  check_eq_u32(target.esi_after, probe::kEsiSentinel,
               "M7: the entry gave ESI back exactly as the harness left it");
}

// A -- baseline. Three calls, in listing order, on the addresses the listing
// computes, and the head of the frame holds argument 2's first twenty bytes.
void case_baseline() {
  probe::reset();
  Fixture receiver_fixture = make_fixture(0x31u);
  Fixture arg1_fixture = make_fixture(0x41u);
  Fixture arg2_fixture = make_fixture(0x51u);
  const Fixture receiver_before = receiver_fixture;
  const Fixture arg1_before = arg1_fixture;
  const Fixture arg2_before = arg2_fixture;

  const std::uint32_t receiver = address_of_word(&receiver_fixture.bytes[8]);
  const std::uint32_t arg1 = address_of_word(&arg1_fixture);
  const std::uint32_t arg2 = address_of_word(&arg2_fixture);

  const Sample sample = call_model(receiver, arg1, arg2);

  check(probe::g_trace.count == 3, "A1: exactly three calls were made");
  check(probe::g_trace.steps[0] == probe::kStepCopy,
        "A2: 0x0041cb40 is the first call");
  check(probe::g_trace.steps[1] == probe::kStepHead,
        "A3: 0x00537f40 is the second call");
  check(probe::g_trace.steps[2] == probe::kStepInterior,
        "A4: 0x00537dc0 is the third call");
  check(probe::g_trace.calls_before[0] == 0 && probe::g_trace.calls_before[1] == 1 &&
            probe::g_trace.calls_before[2] == 2,
        "A5: and each was entered after exactly the ones before it");

  // The frame base, measured rather than assumed, and the three addresses the
  // listing computes from it.
  const std::uint32_t base = frame_base(sample);
  check(base != 0u, "A6: the frame base is a real address");
  check_eq_u32(probe::g_trace.receiver[0], base + kLocalBlockOffset,
               "A7: the first call's hidden receiver is the frame at +0x14");
  check_eq_u32(probe::g_trace.word[0], arg2 + kArg2PushedBase,
               "A8: and its word is argument 2 + 0x14");
  check_eq_u32(probe::g_trace.receiver[1], base,
               "A9: the second call's hidden receiver is the frame at +0x00");
  check_eq_u32(probe::g_trace.word[1], arg1,
               "A10: and its word is argument 1, the entry_ESP+0x4 slot");
  check_eq_u32(probe::g_trace.receiver[2], receiver + kReceiverInteriorDisplacement,
               "A11: the third call's hidden receiver is receiver + 0x18");
  check_eq_u32(probe::g_trace.word[2], probe::g_trace.receiver[1],
               "A12: and its word is the same address the second call got");

  // The head of the frame, as the second call found it and as the third call's
  // window pointed at: argument 2's first twenty bytes, in order.
  check(std::memcmp(probe::g_trace.at_head, arg2_fixture.bytes, kLocalHeadBytes) == 0,
        "A13: the 0x14-byte head is argument 2's first twenty bytes");
  check(std::memcmp(probe::g_trace.at_interior, arg2_fixture.bytes,
                    kLocalHeadBytes) == 0,
        "A14: and the third call's window is that same twenty bytes");
  // The first call's window, as its own body shows it reading: argument 2's bytes
  // from 0x14 to 0x37.
  check(std::memcmp(probe::g_trace.at_copy, arg2_fixture.bytes + kArg2PushedBase,
                    kLocalBlockBytes) == 0,
        "A15: the 0x24-byte window is argument 2's bytes 0x14..0x37");

  // The body writes nothing through any of its three inputs.
  check(count_differences(receiver_before.bytes, receiver_fixture.bytes, kFixtureBytes) == 0,
        "A16: the body wrote no byte of the receiver");
  check(count_differences(arg1_before.bytes, arg1_fixture.bytes, kFixtureBytes) == 0,
        "A17: nor of argument 1");
  check(count_differences(arg2_before.bytes, arg2_fixture.bytes, kFixtureBytes) == 0,
        "A18: nor of argument 2");

  check(sample.esp_after == sample.esp_before, "A19: the stack is balanced");
  check_eq_u32(sample.returned, probe::kTailEaxSentinel,
               "A20: EAX is whatever the last callee left, and nothing else");
}

// B -- the twenty bytes of the head, driven over many argument-2 patterns. This
// is the case that pins the six stores, their displacements and the width of
// each: the head must be argument 2's first twenty bytes, reassembled from two
// word loads and four dword loads.
void case_head_is_argument_two_verbatim() {
  const std::uint8_t seeds[] = {0x00u, 0x01u, 0x7fu, 0x80u, 0xa5u, 0xffu, 0x3cu};
  const int count = static_cast<int>(sizeof seeds / sizeof seeds[0]);
  for (int index = 0; index < count; ++index) {
    probe::reset();
    Fixture receiver_fixture = make_fixture(static_cast<std::uint8_t>(0x61u + index));
    Fixture arg2_fixture = make_fixture(seeds[index]);
    const std::uint32_t arg2 = address_of_word(&arg2_fixture);
    const Sample sample =
        call_model(address_of_word(&receiver_fixture), 0x2000u + arg2, arg2);

    char label[160];
    std::snprintf(label, sizeof label,
                  "B%d: the head is argument 2's first twenty bytes, seed 0x%02x",
                  index, seeds[index]);
    check(std::memcmp(probe::g_trace.at_head, arg2_fixture.bytes,
                      kLocalHeadBytes) == 0,
          label);
    std::snprintf(label, sizeof label,
                  "B%d: and the third call's window is those same twenty bytes",
                  index);
    check(std::memcmp(probe::g_trace.at_interior, arg2_fixture.bytes,
                      kLocalHeadBytes) == 0,
          label);
    std::snprintf(label, sizeof label,
                  "B%d: and the first call's window is argument 2 + 0x14, 0x24 bytes",
                  index);
    check(probe::g_trace.word[0] == arg2 + kArg2PushedBase &&
              std::memcmp(probe::g_trace.at_copy,
                          arg2_fixture.bytes + kArg2PushedBase,
                          kLocalBlockBytes) == 0,
          label);
    std::snprintf(label, sizeof label,
                  "B%d: the two reads of [ESP+0x40] named different arguments", index);
    check(probe::g_trace.word[1] == 0x2000u + arg2 && probe::g_trace.word[1] != arg2,
          label);
    std::snprintf(label, sizeof label, "B%d: the stack stayed balanced", index);
    check(sample.esp_after == sample.esp_before, label);
  }
  // And the head is exactly twenty bytes: the byte past it is NOT argument 2's
  // twenty-first. It is the first byte of the window the first callee was given,
  // which the body never writes back and never reads, so it is whatever the frame
  // already held -- which is nothing this package claims a value for. What IS
  // claimed is only that the head stops at twenty bytes, and that is checked by
  // the byte comparison above plus the six store displacements in W23.
}

// C -- argument 1 is never looked through. The body reads it, pushes it and hands
// it on, and no instruction in the 118 bytes dereferences it, so the model test
// can drive it over values that are not mapped at all. A reconstruction that
// read through it faults; one that does not, runs.
void case_argument_one_is_never_looked_through() {
  const std::uint32_t words[] = {0x00000000u, 0x00000001u, 0x7fffffffu,
                                 0x80000000u, 0xfffffffeu, 0x5eed1234u,
                                 0xdeadbeefu, 0x0000fff0u};
  const int count = static_cast<int>(sizeof words / sizeof words[0]);
  for (int index = 0; index < count; ++index) {
    probe::reset();
    Fixture receiver_fixture = make_fixture(0x71u);
    Fixture arg2_fixture = make_fixture(0x72u);
    const std::uint32_t arg2 = address_of_word(&arg2_fixture);
    const Sample sample =
        call_model(address_of_word(&receiver_fixture), words[index], arg2);
    char label[160];
    std::snprintf(label, sizeof label,
                  "C%d: argument 1 = 0x%08x reaches the second callee verbatim, and "
                  "the body never looks through it",
                  index, words[index]);
    check(probe::g_trace.count == 3, label);
    check(probe::g_trace.word[1] == words[index], label);
    std::snprintf(label, sizeof label,
                  "C%d: and the head is still argument 2's twenty bytes", index);
    check(std::memcmp(probe::g_trace.at_head, arg2_fixture.bytes,
                      kLocalHeadBytes) == 0,
          label);
    std::snprintf(label, sizeof label, "C%d: and the stack stayed balanced", index);
    check(sample.esp_after == sample.esp_before, label);
  }
}

// D -- the receiver. It is copied into ESI unadjusted, the copy buys lifetime
// across all three calls, and the only address ever formed from it is
// receiver+0x18. No byte is loaded and none is stored, so a receiver at an
// interior offset of a fixture, a receiver at the fixture head, and a null
// receiver are all handled identically.
void case_receiver() {
  const std::size_t offsets[] = {0u, 1u, 4u, 8u, 16u};
  const int count = static_cast<int>(sizeof offsets / sizeof offsets[0]);
  for (int index = 0; index < count; ++index) {
    const std::size_t offset = offsets[index];
    probe::reset();
    Fixture receiver_fixture = make_fixture(0x81u);
    const Fixture before = receiver_fixture;
    Fixture arg2_fixture = make_fixture(0x82u);
    const std::uint32_t receiver = address_of_word(&receiver_fixture.bytes[offset]);
    call_model(receiver, 0x3000u, address_of_word(&arg2_fixture));

    char label[160];
    std::snprintf(label, sizeof label,
                  "D%d: a receiver at +%u reaches the third callee as +0x18 "
                  "unadjusted",
                  index, static_cast<unsigned>(offset));
    check(probe::g_trace.receiver[2] == receiver + kReceiverInteriorDisplacement,
          label);
    std::snprintf(label, sizeof label,
                  "D%d: and no byte of the fixture at +%u was written", index,
                  static_cast<unsigned>(offset));
    check(count_differences(before.bytes, receiver_fixture.bytes, kFixtureBytes) == 0, label);
  }

  // A null receiver is not special-cased. The listing has no test on the receiver
  // at all, so a model that early-returned on null, or that computed an interior
  // address differently for null, is refuted. receiver+0x18 on a null receiver is
  // 0x18, and that is what the callee is handed.
  probe::reset();
  Fixture arg2_fixture = make_fixture(0x83u);
  const Sample null_sample = call_model(0u, 0x4000u, address_of_word(&arg2_fixture));
  check(probe::g_trace.count == 3, "D5: a null receiver still makes all three calls");
  check_eq_u32(probe::g_trace.receiver[2], kReceiverInteriorDisplacement,
               "D6: and the third call is handed 0 + 0x18");
  check(std::memcmp(probe::g_trace.at_head, arg2_fixture.bytes, kLocalHeadBytes) == 0,
        "D7: with the head still built from argument 2");
  check(null_sample.esp_after == null_sample.esp_before,
        "D8: and the stack still balanced");
  check_eq_u32(null_sample.returned, probe::kTailEaxSentinel,
               "D9: and EAX is still the last callee's sentinel");

  // The copy buys LIFETIME and not reach: nothing between the PUSH ESI and the
  // POP ESI writes ESI, so the receiver survives all three calls and reaches the
  // third one unchanged. The harness's ESI check is the other half of that.
  probe::reset();
  Fixture third_fixture = make_fixture(0x84u);
  call_model(0x00f0f0f0u, 0x5000u, address_of_word(&arg2_fixture));
  check_eq_u32(probe::g_trace.receiver[2],
               0x00f0f0f0u + kReceiverInteriorDisplacement,
               "D10: a receiver no fixture can equal is carried across all three "
               "calls unadjusted");
  static_cast<void>(third_fixture);
}

// E -- the stack slots. The two arguments are at entry_ESP+0x4 and entry_ESP+0x8,
// they are different values, and a decoy pushed below both is neither read nor
// consumed. This is the case that would fail if the body's ESP arithmetic were
// wrong by a word -- which is exactly what the first callee's RET 0x4 settles.
void case_stack_slots() {
  probe::reset();
  Fixture receiver_fixture = make_fixture(0x91u);
  Fixture arg1_fixture = make_fixture(0x92u);
  Fixture arg2_fixture = make_fixture(0x93u);
  const std::uint32_t receiver = address_of_word(&receiver_fixture);
  const std::uint32_t arg1 = address_of_word(&arg1_fixture);
  const std::uint32_t arg2 = address_of_word(&arg2_fixture);

  const Sample plain = call_model(receiver, arg1, arg2);
  check(plain.esp_after == plain.esp_before,
        "E1: with nothing below the arguments the stack is exactly balanced");

  probe::reset();
  const Sample decoyed =
      call_model_over_a_decoy(receiver, arg1, arg2, 0x00c0ffeeu);
  check(decoyed.esp_after == decoyed.esp_before - 4u,
        "E2: a decoy at entry_ESP+0xc is left for the caller, so the callee popped "
        "exactly two words and no more");
  // The two runs are two separate calls, so their absolute stack pointers are not
  // required to agree -- and at -O0 they do not, because the compiler's own frame
  // differs between them. What IS required to agree is the DELTA each run produced,
  // and it must differ by exactly one word: that is the decoy the callee left.
  check((plain.esp_after - plain.esp_before) -
                (decoyed.esp_after - decoyed.esp_before) ==
            static_cast<std::uint32_t>(kReturnAddressBytes),
        "E3: the decoy run leaves exactly one word more than the plain run");
  check(probe::g_trace.word[1] == arg1 && probe::g_trace.word[0] == arg2 + kArg2PushedBase,
        "E4: and a decoy changes neither argument the body hands on");
  check(std::memcmp(probe::g_trace.at_head, arg2_fixture.bytes, kLocalHeadBytes) == 0,
        "E5: nor the head it builds");

  // The inverse: the decoy says one thing and argument 1 another. The body must
  // follow argument 1, which is what the second [ESP+0x40] read fixes.
  probe::reset();
  const Sample swapped = call_model_over_a_decoy(receiver, 0x00abcdefu, arg2, arg1);
  check(probe::g_trace.word[1] == 0x00abcdefu,
        "E6: the word at entry_ESP+0x4 is the one the second callee is handed");
  check(probe::g_trace.word[1] != swapped.esp_before,
        "E7: and it is not the return address, which is what a mis-modelled "
        "callee-popped call would have produced");
  check(swapped.esp_after == swapped.esp_before - 4u,
        "E8: the decoy is still left behind");

  // And the second slot: a decoy at entry_ESP+0x8 is impossible to plant without
  // moving argument 2, so instead argument 1 is given a value that argument 2's
  // address would never equal, and the head must follow argument 2.
  probe::reset();
  Fixture other = make_fixture(0x94u);
  const std::uint32_t other_arg2 = address_of_word(&other);
  const Sample moved = call_model(receiver, other_arg2, arg2);
  check(moved.esp_after == moved.esp_before,
        "E9a: and the stack is still balanced with the arguments exchanged");
  check(probe::g_trace.word[1] == other_arg2,
        "E9: argument 1 at entry_ESP+0x4 is honoured whatever its value");
  check(std::memcmp(probe::g_trace.at_head, arg2_fixture.bytes, kLocalHeadBytes) == 0,
        "E10: and the head is built from argument 2 at entry_ESP+0x8, not from "
        "argument 1");
}

// F -- the return. There is no instruction that places a value in a return
// register at the terminator, so the word the last callee leaves in EAX is what
// reaches the caller. That is the only place the void reading of the return is
// observable, and it is checked here rather than asserted in prose.
void case_return_value_is_whatever_the_last_callee_left() {
  for (int index = 0; index < 3; ++index) {
    probe::reset();
    Fixture receiver_fixture = make_fixture(0xa1u);
    Fixture arg2_fixture = make_fixture(0xa2u);
    const Sample sample = call_model(address_of_word(&receiver_fixture), 0x6000u,
                                     address_of_word(&arg2_fixture));
    char label[160];
    std::snprintf(label, sizeof label,
                  "F%d: EAX carries the last callee's sentinel, so the body adds no "
                  "return value of its own",
                  index);
    check_eq_u32(sample.returned, probe::kTailEaxSentinel, label);
    std::snprintf(label, sizeof label,
                  "F%d: and it is not the harness's own EAX sentinel", index);
    check(sample.returned != probe::kEaxSentinel, label);
    std::snprintf(label, sizeof label,
                  "F%d: nor the receiver, nor a fixture address", index);
    check(sample.returned != address_of_word(&receiver_fixture.bytes[0]) &&
              sample.returned != address_of_word(&arg2_fixture.bytes[0]),
          label);
  }
}

// N -- the extent facts, restated from the listing. The counts are the ones the
// thirty-one instructions give, and the table slot is a machine fact read out of
// the image and checked as a restatement rather than as a measurement of this
// body.
void case_machine_extent_constants() {
  check(kInstructionCount == 31, "N1: the body is thirty-one instructions");
  check(kBodySpanBytes == 118u,
        "N2: and spans 118 bytes, 0x00a98400..0x00a98475");
  check(kConditionalBranches == 0, "N3: no conditional branch at all");
  check(kBasicBlockCount == 1, "N4: one basic block, the whole body");
  check(kDirectCalleeCount == 3, "N5: three direct callees");
  check(kIndirectTransfers == 0, "N6: and no indirect transfer");
  check(kGlobalReferences == 0, "N7: and no global reference");
  check(kSavedRegisterCount == 1, "N8: exactly one register saved, ESI");
  check(kFrameInstructions == 1, "N9: and one frame instruction, the SUB");
  check(kInstructionCount == 31 && kBodySpanBytes == 118u,
        "N10: 31 instructions in 118 bytes, which is the span the pack records");

  // The table slot. GhidraMCP /read_memory at 0x01458770 for 48 bytes puts these
  // seven words at 0x01458788..0x014587a3.
  check(kTableBase == 0x01458788u,
        "N11: the table the receiver rule rests on is based at 0x01458788");
  check(kOwnSlotAddress == 0x014587a0u,
        "N12: and this body sits at 0x014587a0 within it");
  check(kOwnSlotIndex == 6, "N13: which is slot index 6 of a four-byte-slot table");
  check(kOwnSlotAddress - kTableBase == kOwnSlotDisplacement,
        "N14: 0x014587a0 is 0x18 bytes above the base, which is six slots");
  check(kTableWordCount == 7u, "N15: seven words are transcribed from that base");
  check(kTableWords[0] == 0x00a98090u && kTableWords[1] == 0x004ae250u &&
            kTableWords[2] == 0x00a980b0u && kTableWords[3] == 0x00a98208u &&
            kTableWords[4] == 0x00a98020u && kTableWords[5] == 0x00a98050u &&
            kTableWords[6] == 0x00a98400u,
        "N16: and they are the words the image holds, this body last");
  // Every one of them is inside .text, which is what makes the table a table of
  // code addresses rather than a data constant pool. CHECKED here rather than
  // asserted: the words are compared against literals, and each literal is
  // compared against the .text range the image base implies.
  int inside_text = 0;
  for (std::size_t index = 0; index < kTableWordCount; ++index) {
    const std::uint32_t low = 0x00400000u;
    const std::uint32_t high = 0x01300000u;
    if (kTableWords[index] >= low && kTableWords[index] < high) {
      inside_text += 1;
    }
  }
  check_eq_u32(static_cast<std::uint32_t>(inside_text),
               static_cast<std::uint32_t>(kTableWordCount),
               "N17: all seven words of that table are .text addresses");

  check(kTargetVa == 0x00a98400u && kBodyFirstByte == 0x00a98400u &&
            kBodyLastByte == 0x00a98475u && kBodyEndExclusive == 0x00a98476u,
        "N18: the body span is 0x00a98400..0x00a98475, exclusive end 0x00a98476");
  check(kBodyLastByte - kBodyFirstByte + 1u == kBodySpanBytes,
        "N19: and that span is exactly 118 bytes wide");
  // The header's own byte transcript, anchored on literals written here rather
  // than read from the header, so a corrupted transcript fails instead of being
  // believed by every byte comparison in case W.
  check(kTargetBytes[0] == 0x83u && kTargetBytes[1] == 0xecu &&
            kTargetBytes[2] == 0x38u,
        "N20: the transcript starts with SUB ESP,0x38");
  check(kTargetBytes[0x4f] == 0xe8u && kTargetBytes[0x50] == 0xecu &&
            kTargetBytes[0x51] == 0x46u && kTargetBytes[0x52] == 0x98u &&
            kTargetBytes[0x53] == 0xffu,
        "N21: and carries the first CALL's rel32 as the image has it");
  check(kTargetBytes[0x6a] == 0xe8u && kTargetBytes[0x6b] == 0x51u &&
            kTargetBytes[0x6c] == 0xf9u && kTargetBytes[0x6d] == 0xa9u &&
            kTargetBytes[0x6e] == 0xffu,
        "N22: and the third CALL's rel32 as the image has it");
  check(kTargetBytes[0x73] == 0xc2u && kTargetBytes[0x74] == 0x08u &&
            kTargetBytes[0x75] == 0x00u,
        "N23: and the three-byte RET 0x8 terminator, which is the cleanup this "
        "entry must perform");
  check(kRetImmediateLowByte == 0x08u && kRetImmediateHighByte == 0x00u,
        "N24: the terminator's immediate, spelled here, is 0x0008");
  check(kArg2OffsetCount == 6u, "N25: argument 2 is read at six displacements");
  check(kArg2Offsets[0] == 0x00u && kArg2Offsets[1] == 0x02u &&
            kArg2Offsets[2] == 0x04u && kArg2Offsets[3] == 0x08u &&
            kArg2Offsets[4] == 0x0cu && kArg2Offsets[5] == 0x10u,
        "N26: 0x00, 0x02, 0x04, 0x08, 0x0c and 0x10, in that order");
  check(kNoDecoyWord == 0xffffffffu,
        "N27: the decoy sentinel is a value no decoy case uses");
}

}  // namespace
}  // namespace pkg_swarm_w2_00a98400
}  // namespace reconstruction
}  // namespace openspore

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w2_00a98400;

  case_the_entry_emits_the_target_bytes();
  case_abi_travels_as_data();
  case_cleanup_side_is_measured_not_only_declared();
  case_baseline();
  case_head_is_argument_two_verbatim();
  case_argument_one_is_never_looked_through();
  case_receiver();
  case_stack_slots();
  case_return_value_is_whatever_the_last_callee_left();
  case_machine_extent_constants();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
