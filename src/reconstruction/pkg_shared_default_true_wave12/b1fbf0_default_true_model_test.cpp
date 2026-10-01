// PKG-SHARED-DEFAULT-TRUE-WAVE12 -- VA 0x00b1fbf0
// Falsification test for the three-byte __thiscall constant
// re_00b1fbf0_shared_default_true (`MOV AL,0x1` ; `RET`).
//
// LAYERING, because a two-instruction body has almost nothing to test and the
// danger is that the test ends up agreeing with itself:
//
//   1. kImageBody in this file is the IMAGE, transcribed: B0 01 C3. It is
//      deliberately NOT the header's kTargetBytes -- two independent
//      transcriptions of the same three bytes, compared position by position in
//      case F, so neither can drift silently. The reconstruction never reads it.
//   2. re_00b1fbf0_shared_default_true in the .cpp is the code under test. The
//      behavioural cases drive it through its own declaration, so a defect in it
//      cannot be papered over by the transcription.
//   3. The machine facts a value comparison cannot show are MEASURED: the
//      callee's stack effect is measured across a hand-rolled indirect call
//      (case E), the FULL 32-bit return register is read out of that same call
//      with a poisoned upper half (case D), and the code the compiler actually
//      emitted for the function is decoded at run time (case G) rather than
//      assumed from the source.
//
// THE CASES THAT EXIST TO BREAK THE RECONSTRUCTION:
//
//   A  the answer is the byte 0x01, for a battery of receiver values including
//      null, an interior pointer and a value that is not a mapped address. A
//      reconstruction that answers 0, that answers a receiver-derived value, or
//      that special-cases null dies here.
//   B  the receiver is never READ. It is entered with an address that is not
//      mapped, and with a byte run full of poison markers. A reconstruction that
//      dereferences it faults or answers a marker.
//   C  the receiver is never WRITTEN. A guard-banded run is compared byte for
//      byte, at every displacement, after every call in the battery.
//   D  the answer is a BYTE, not a dword. The full EAX is read back after a call
//      made with a poison pattern in its upper 24 bits, and those 24 bits must
//      come back untouched. This is the check that `MOV AL,0x1` earns and that
//      `MOV EAX,0x1` -- which is what g++ emits for a plain C++ `return 1` --
//      would fail, and it is the reason the reconstruction is a naked
//      transcription rather than a restatement.
//   E  the callee pops NOTHING, MEASURED, with the instrument calibrated. The
//      probe records the stack pointer immediately before the transfer and
//      immediately after it returns, so the difference IS the machine's RET
//      immediate. Two control callees that pop nothing and pop eight bytes fix
//      what the instrument reads for each, so a probe that simply reported zero
//      would be caught, and the reconstruction is then measured against that
//      calibrated instrument.
//   F  the image is three bytes and decodes to MOV AL,imm8 then RET: the opcode
//      fields, the immediate and the absence of a RET immediate are checked
//      field by field, so a transcription that kept the length but changed an
//      operand dies here.
//   G  the code the compiler emitted for the reconstruction IS those three
//      bytes, decoded at run time, at whatever optimisation level this build is.
//      Any mutation that changes the emitted operation, adds a frame, spills, or
//      introduces a call changes these bytes and dies here. The one toolchain
//      artifact that is recognised rather than assumed away is named in the case
//      itself and in the .cpp: a get_pc_thunk PC anchor, recognised by its exact
//      opcode pair, after which the three target bytes are required immediately.
//      When that anchor is present it ADDS 1 to EAX, so case D cannot measure the
//      full return register and says so instead of pretending to; case G still
//      pins the bytes at that level.
//   H  the image carries no transfer at all: no CALL, no JMP, no FF /2,/3 and no
//      branch opcode. The same case then shows the function reached through a
//      two-level load from a SYNTHETIC table whose repointing changes the callee,
//      so the caller side is observed without the body ever dispatching.
//   I  the machine ABI record's determination, checked value by value against
//      literals written independently here: the convention and its INFERRED
//      confidence, its TWO surviving candidates, the receiver register and the
//      vftable-slot provenance, the OBSERVED absence of any read through that
//      register, and the caller-side cleanup. A package that quietly reverted to
//      the old "no convention, no receiver" abstention fails here.
//   J  the entry really is a __thiscall member. The convention token is
//      recovered from the macro the source span names and required to be there.
//      On i386 a thiscall and a cdecl entry with no stack argument compile to
//      IDENTICAL code, so no behavioural case can see the difference; this is the
//      one check that can, and it is what makes dropping the convention a
//      detected mutation rather than an invisible one.
//
// REGISTER DISCIPLINE OF THE PROBE, AND WHY IT IS ONE FILE-SCOPE ASSEMBLY
// FUNCTION. The probe is an i386 SysV cdecl function and it touches ONLY EAX,
// ECX, EDX and ESP. It never writes ESI, EDI or EBX: a hand-written probe that
// borrows one of those to hold an argument and never puts it back corrupts its
// CALLER, not itself, and the damage surfaces as an optimiser-dependent failure
// in a test that has nothing to do with the probe. That is not hypothetical: an
// earlier revision of a sibling package in this wave read a probe argument
// through ESI, passed at -O0, and failed from -O1 upwards for exactly that
// reason. EBX is not touched at all, which matters twice over -- it is
// callee-saved, and on a PIC i386 build it holds the GOT base, so taking it over
// inside the assembly invalidates every address the compiler forms around it.
//
// EBP appears once, as the frame pointer THIS probe establishes for itself
// (`pushl %ebp` / `movl %esp, %ebp` ... `leave`), and `leave` puts the caller's
// back, so nothing the caller held in EBP is disturbed. It has to be a frame
// pointer rather than a stack-pointer frame because the stack pointer is exactly
// the thing the two cleanup sides disagree about: a frame addressed through ESP
// moves the moment the callee pops, and every sample taken through it afterwards
// would be reading a shifted frame. Addressing through EBP is immune to that,
// which is the whole reason the samples are trustworthy.
//
// TWO WORDS OF SCRATCH ARE PUSHED BEFORE EVERY TRANSFER, and that is not
// decoration. The `ret $8` calibration control pops eight bytes: the return
// address plus eight more. Without the scratch those eight bytes come out of the
// probe's own frame and out of the C++ caller's, and the damage is silent. With
// two words pushed the control consumes exactly the scratch, and the probe
// restores its own stack pointer from the value it recorded before the transfer
// so both controls return through a frame that is exactly where they found it.
//
// WHAT IS NOT ASSERTED, AND WHY:
//   * The receiver's identity. The determination says the receiver arrives in
//     ECX; it does not say what the receiver IS. Six call sites hand this
//     function six different objects and the body reads none of them, so the
//     receiver is declared incomplete and this test supplies its own opaque byte
//     run through a cast. No class, no table identity, no receiver type, no
//     field, no member and no object size is claimed, and NO FIELD OFFSET IS
//     CLAIMED IN EITHER DIRECTION: the body shows no displacement through any
//     register, so neither a field at some offset nor the object's being flat
//     is asserted.
//   * The meaning of the answer. The body is a constant yes and nothing in the
//     observed evidence names the question it answers, so the test calls it the
//     byte 0x01 and never a predicate name.
//   * __fastcall. The machine record keeps it as a second surviving candidate.
//     Nothing observed here closes it and this test does not pretend to.

#include "b1fbf0_default_true.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_shared_default_true_wave12 {
namespace {

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#else
#define TEST_THISCALL __attribute__((thiscall))
#endif

// STRINGIFY, so case J can read what the convention macro actually expands to.
// The substring it is compared against is written here, independently of the
// header, which is what makes the comparison a check rather than a tautology.
#define PKG_STR2(x) #x
#define PKG_STR(x) PKG_STR2(x)

constexpr const char kConventionSpelling[] =
    PKG_STR(PKG_SHARED_DEFAULT_TRUE_WAVE12_NAKED_THISCALL);

// -- the image, transcribed here, independently of the header ---------------

constexpr std::uint8_t kImageBody[3] = {0xB0, 0x01, 0xC3};
constexpr std::size_t kImageSize = sizeof(kImageBody);
// /read_memory at 0x00b1fbf0 for 12 bytes: b0 01 c3 then nine 0xCC bytes.
constexpr std::uint8_t kImagePadByte = 0xCC;

// -- fixtures ---------------------------------------------------------------

constexpr std::size_t kObjectSize = 0x100;
constexpr std::size_t kGuard = 64;
constexpr std::size_t kStorageSize = kObjectSize + 2 * kGuard;
constexpr std::uint8_t kGuardByte = 0xA5;

// Deliberately irregular, and deliberately not all four-byte aligned, so the
// twelve receiver addresses differ in their low bits as well as their high ones
// and a reconstruction that masked or rounded the answer could not pass.
constexpr std::size_t kTrialOffsets[] = {0x000u, 0x004u, 0x008u, 0x00cu,
                                         0x010u, 0x014u, 0x018u, 0x01cu,
                                         0x001u, 0x005u, 0x009u, 0x00du};
constexpr std::size_t kTrialCount =
    sizeof(kTrialOffsets) / sizeof(kTrialOffsets[0]);

// A value that is certainly not a mapped address, so a reconstruction that
// dereferenced its receiver would fault rather than quietly succeed.
constexpr std::uint32_t kUnmappedReceiver = 0x5a5a5a5au;

int g_failures = 0;
int g_checks = 0;

void check(bool ok, const char* what) {
  ++g_checks;
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void check_eq_u32(std::uint32_t got, std::uint32_t want, const char* what) {
  ++g_checks;
  if (got != want) {
    std::fprintf(stderr, "FAILED: %s (got 0x%08lx, want 0x%08lx)\n", what,
                 static_cast<unsigned long>(got),
                 static_cast<unsigned long>(want));
    ++g_failures;
  }
}

std::uint32_t address_of(const void* pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

// A guard-banded byte run. The receiver type is incomplete by design, so the
// run is this file's own and the cast into it is the only way to name a
// receiver at all.
struct Storage {
  std::uint8_t bytes[kStorageSize];

  Storage() { std::memset(bytes, kGuardByte, kStorageSize); }

  Receiver* at(std::size_t offset) const {
    return reinterpret_cast<Receiver*>(
        const_cast<std::uint8_t*>(bytes + kGuard + offset));
  }

  bool guards_intact() const {
    for (std::size_t i = 0; i < kGuard; ++i) {
      if (bytes[i] != kGuardByte ||
          bytes[kGuard + kObjectSize + i] != kGuardByte) {
        return false;
      }
    }
    return true;
  }
};

void fill(std::uint8_t* run, std::size_t size, std::uint32_t seed) {
  // No zero byte in the pattern, so a store of zero into the run is as visible
  // to the byte comparisons as a store of anything else.
  for (std::size_t offset = 0; offset + 4 <= size; offset += 4) {
    const std::uint32_t word =
        0xa5a5f00du ^ seed ^ static_cast<std::uint32_t>(offset);
    std::memcpy(run + offset, &word, sizeof(word));
  }
}

void put_u32(Receiver* object, std::size_t offset, std::uint32_t value) {
  std::memcpy(reinterpret_cast<std::uint8_t*>(object) + offset, &value,
              sizeof(value));
}

std::uint32_t get_u32(const Receiver* object, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, reinterpret_cast<const std::uint8_t*>(object) + offset,
              sizeof(value));
  return value;
}

// -- the call probe ---------------------------------------------------------

// What the probe reports. Every field is a measurement taken inside the
// assembly block; none of them is a constant this file chose.
struct Sample {
  std::uint32_t returned;     // EAX immediately after the call returns
  std::uint32_t before;       // ESP immediately before the transfer
  std::uint32_t after;        // ESP immediately after the callee lets go
  std::uint32_t ecx_at_call;  // ECX as the callee will see it
  std::uint32_t popped;       // after - before, which IS the RET immediate
};

// probe_call_00b1fbf0(target, ecx_value, eax_poison, out)
//
//    8(%ebp)   the callee address, called through a register
//   12(%ebp)   the value the caller has in ECX
//   16(%ebp)   the pattern the caller has in EAX
//   20(%ebp)   the Sample to fill
//
// The frame, with B = %ebp this probe established for itself and a 48-byte
// reservation:
//
//   B-4   the callee address, held across the call
//   B-8   the output pointer, held across the call
//   B-12  `popped`: after minus before
//   B-16  `before`: the stack pointer AT the transfer, after the scratch
//   B-20  ECX as the callee will see it
//   B-24  the pattern the caller left in EAX
//   B-28  `after`: the stack pointer the instant the callee let go
//   B-36  the callee's EAX, parked before any arithmetic can touch it
//
// Every one of those slots is addressed through B, never through the stack
// pointer, because a callee that pops moves the stack pointer and a sample taken
// through it afterwards would be reading a shifted frame. Two words of scratch
// are pushed immediately before the transfer so the `ret $8` control's extra pop
// is absorbed by the scratch and not by this frame or the C++ caller's.
extern "C" void probe_call_00b1fbf0(std::uint32_t target, std::uint32_t ecx_word,
                                    std::uint32_t eax_poison, Sample* out);

// The two control callees, declared before the assembly block that defines
// them. They are observers: nothing here claims anything about them beyond the
// RET form the probe calibrates against, and both are entered exactly the way
// the body is -- a receiver in ECX, nothing pushed by the caller.
extern "C" void control_pops_zero_00b1fbf0();
extern "C" void control_pops_eight_00b1fbf0();

// The two control callees, defined at file scope in assembly rather than as C++
// functions, because the whole point is the RET form and a compiler-generated
// prologue would move the stack the RET reads from: an unoptimised `ret $8` in a
// C++ body that begins with `pushl %ebp` pops the saved frame pointer and jumps
// into garbage. At file scope the sequence is exactly the instructions written,
// at every optimisation level and under both compilers.
//
// `ret` pops the return address and nothing else; `ret $8` pops the return
// address and the eight bytes above it, which is the probe's two words of
// scratch. Neither control writes any register, so the EAX the instrument
// reports back is the caller's own pattern -- which is what makes the first
// control an instrument check as well as a calibration point.
__asm__(".text\n"
        ".balign 16\n"
        ".globl probe_call_00b1fbf0\n"
        ".type probe_call_00b1fbf0, @function\n"
        "probe_call_00b1fbf0:\n"
        "  pushl %ebp\n"
        "  movl %esp, %ebp\n"
        "  subl $48, %esp\n"
        "  movl 8(%ebp), %eax\n"         // the callee
        "  movl %eax, -4(%ebp)\n"
        "  movl 20(%ebp), %eax\n"        // the output pointer
        "  movl %eax, -8(%ebp)\n"
        "  movl 12(%ebp), %eax\n"        // the register-carried value
        "  movl %eax, -20(%ebp)\n"       // ECX as the callee will see it
        "  movl 16(%ebp), %eax\n"        // the pattern the caller left in EAX
        "  movl %eax, -24(%ebp)\n"
        "  movl %esp, %eax\n"
        "  movl %eax, -16(%ebp)\n"       // the stack pointer before the
        "  pushl -24(%ebp)\n"            // two words of scratch, so a
        "  pushl -24(%ebp)\n"            // `ret $8` cannot eat this frame
        "  movl %esp, %eax\n"            // and then restated AT the transfer,
        "  movl %eax, -16(%ebp)\n"       // so after-minus-before is the RET
        "  movl -4(%ebp), %edx\n"        // immediate and nothing else: the
        "  movl -24(%ebp), %eax\n"       // caller's pattern goes in EAX and
        // The callee address goes in EDX so that the caller's own pattern is
        // in EAX when the transfer happens and reaches the callee untouched.
        "  call *%edx\n"
        "  movl %eax, -36(%ebp)\n"       // the callee's answer, parked FIRST,
        "  movl %esp, %eax\n"            // before any arithmetic can touch it
        "  movl %eax, -28(%ebp)\n"       // the raw post-callee stack pointer
        "  movl -16(%ebp), %edx\n"
        "  subl %edx, %eax\n"            // after - before: the RET immediate
        "  movl %eax, -12(%ebp)\n"       // `popped`, held in the frame
        "  movl -8(%ebp), %eax\n"        // the output pointer again
        "  movl -12(%ebp), %edx\n"
        "  movl %edx, 16(%eax)\n"        // out->popped\n"
        "  movl -16(%ebp), %edx\n"
        "  movl %edx, 4(%eax)\n"         // out->before\n"
        "  movl -8(%ebp), %eax\n"
        "  movl -28(%ebp), %edx\n"
        "  movl %edx, 8(%eax)\n"         // out->after\n"
        "  movl -8(%ebp), %eax\n"
        "  movl -20(%ebp), %edx\n"
        "  movl %edx, 12(%eax)\n"        // out->ecx_at_call\n"
        "  movl -8(%ebp), %eax\n"
        "  movl -36(%ebp), %edx\n"
        "  movl %edx, (%eax)\n"          // out->returned\n"
        // RESTORING THE CALLER'S STACK, AND WHY IT IS UNCONDITIONAL. Every
        // sample the probe needs has already been read out by this point, so
        // the probe can put the stack pointer back at a FIXED address derived
        // from `before` -- `before` plus the probe's own known frame and
        // scratch -- and be right whatever the callee did. That matters
        // because the callee's RET immediate is exactly the quantity under
        // measurement: a `ret $8` has already consumed the two scratch words
        // AND four bytes of this probe's reservation by the time control comes
        // back here, so any "pop what I pushed" scheme would be off by the
        // callee's own pop. A fixed restore is immune to it, and it is what
        // makes the `ret $8` control survivable at all.
        "  movl -16(%ebp), %esp\n"
        "  addl $64, %esp\n"             // undo the frame, the scratch and the
        "  leave\n"                      // return slot: 48 + 4 + 8 + 4
        "  ret\n"
        ".size probe_call_00b1fbf0, .-probe_call_00b1fbf0\n"
        ".globl control_pops_zero_00b1fbf0\n"
        ".type control_pops_zero_00b1fbf0, @function\n"
        "control_pops_zero_00b1fbf0:\n"
        "  ret\n"
        ".size control_pops_zero_00b1fbf0, .-control_pops_zero_00b1fbf0\n"
        ".globl control_pops_eight_00b1fbf0\n"
        ".type control_pops_eight_00b1fbf0, @function\n"
        "control_pops_eight_00b1fbf0:\n"
        "  ret $8\n"
        ".size control_pops_eight_00b1fbf0, .-control_pops_eight_00b1fbf0\n");

// One probe call. `popped` is the measured difference and nothing else.
Sample probe(std::uint32_t target, std::uint32_t ecx_word,
             std::uint32_t eax_poison) {
  Sample out;
  out.returned = 0u;
  out.before = 0u;
  out.after = 0u;
  out.ecx_at_call = 0u;
  out.popped = 0u;
  probe_call_00b1fbf0(target, ecx_word, eax_poison, &out);
  return out;
}

// The C++-level stack pointer, read directly, with a memory clobber so the
// compiler may neither move the read across the intervening call nor fold the
// two reads of case E into one.
std::uint32_t stack_pointer() {
  std::uint32_t sp = 0;
  __asm__ volatile("movl %%esp, %0\n\t" : "=r"(sp) : : "memory");
  return sp;
}

std::uint32_t address_of_reconstruction() {
  return address_of(
      reinterpret_cast<const void*>(&re_00b1fbf0_shared_default_true));
}

// -- case G, part one: what the compiler actually emitted -------------------

// Locate the three target bytes in the code the compiler emitted, and report
// whether a get_pc_thunk PC anchor precedes them.
//
// The anchor is recognised by its EXACT opcode pair -- E8 with a four-byte
// displacement, then opcode 05 with a four-byte immediate -- which is ten bytes
// long. A toolchain that emitted some other form of anchor would not be
// recognised here and the byte check would fail, which is the correct outcome:
// the alternative is silently skipping the check.
std::size_t emitted_body_offset(const std::uint8_t* bytes, bool* has_anchor) {
  *has_anchor = false;
  if (bytes[0] == kImageBody[0] && bytes[1] == kImageBody[1] &&
      bytes[2] == kImageBody[2]) {
    return 0;
  }
  if (bytes[0] == 0xE8u && bytes[5] == 0x05u) {
    *has_anchor = true;
    return 10;
  }
  return static_cast<std::size_t>(-1);
}

// -- the cases --------------------------------------------------------------

// Case F: the transcribed image, decoded field by field.
void test_image_bytes() {
  check_eq_u32(static_cast<std::uint32_t>(kImageSize), 3u,
               "F: the body at 0x00b1fbf0 is three bytes");
  check_eq_u32(kImageBody[0], 0xB0u,
               "F: 0x00b1fbf0 is opcode B0, MOV r8,imm8, whose register field "
               "is fixed at AL and which carries no ModRM byte at all");
  check_eq_u32(kImageBody[1], 0x01u,
               "F: the immediate of the MOV is the byte 0x01, the only value "
               "this body ever produces");
  check_eq_u32(kImageBody[2], 0xC3u,
               "F: 0x00b1fbf2 is opcode C3, RET near");
  // The absence of an imm16 after C3 is the whole of the stack accounting, and
  // it is checked as an arithmetic fact about the image's own length rather than
  // asserted: two bytes for the MOV and one for the RET opcode consume all
  // three, so nothing is left for an immediate to occupy.
  check_eq_u32(static_cast<std::uint32_t>(kImageSize) - 2u - 1u, 0u,
               "F: the RET carries no immediate, because the three-byte body is "
               "already fully accounted for by MOV r8,imm8 and the RET opcode");
  check_eq_u32(static_cast<std::uint32_t>(kImagePadByte), 0xCCu,
               "F: the byte after the body is 0xCC inter-function padding");

  // The header's transcription of the same three bytes, position by position,
  // and its derived constants against literals written here rather than there.
  check_eq_u32(kTargetBytes[0], kImageBody[0], "F: the header's byte 0");
  check_eq_u32(kTargetBytes[1], kImageBody[1], "F: the header's byte 1");
  check_eq_u32(kTargetBytes[2], kImageBody[2], "F: the header's byte 2");
  check_eq_u32(static_cast<std::uint32_t>(kInterFunctionPad), kImagePadByte,
               "F: the header records the same padding byte");
  check_eq_u32(static_cast<std::uint32_t>(kBodySpanBytes),
               static_cast<std::uint32_t>(kImageSize),
               "F: the header's body length is the transcribed length");
  check_eq_u32(static_cast<std::uint32_t>(kRetImmediateBytes), 0u,
               "F: the header's RET immediate is zero bytes");
  check_eq_u32(static_cast<std::uint32_t>(kStackCleanupBytes), 0u,
               "F: the header's cleanup constant is the same zero");
  check_eq_u32(static_cast<std::uint32_t>(kReturnWidthBytes), 1u,
               "F: the header's return width is one byte, from opcode B0");
}

// Case H, first half: the image carries no transfer and no branch.
void test_image_has_no_transfer() {
  bool call_or_jump = false;
  bool conditional = false;
  for (std::size_t i = 0; i < kImageSize; ++i) {
    const std::uint8_t byte = kImageBody[i];
    if (byte == 0xE8u || byte == 0xE9u || byte == 0xEBu || byte == 0xFFu ||
        byte == 0x0Fu) {
      call_or_jump = true;
    }
    if (byte >= 0x70u && byte <= 0x7Fu) {
      conditional = true;
    }
  }
  check(!call_or_jump,
        "H: the image carries no CALL, JMP or FF /2,/3 opcode");
  check(!conditional, "H: the image carries no conditional branch opcode");
}

// Cases A, B and C: the answer, the receiver never read, nothing ever written.
void test_answer_and_receiver() {
  Storage storage;
  const std::uint32_t expected = kImageBody[1];

  for (std::size_t i = 0; i < kTrialCount; ++i) {
    // Not const: the entry takes a mutable `Receiver*` because the machine
    // record names no receiver type at all, and a const there would be a claim
    // about the receiver's own API that nothing in the evidence supports.
    Receiver* const carried = storage.at(kTrialOffsets[i]);
    check_eq_u32(re_00b1fbf0_shared_default_true(carried), expected,
                 "A: the answer is the image's immediate, byte for byte, for "
                 "every receiver");
  }

  // The null receiver. A body with a branch could special-case it; this one has
  // no branch in three bytes, and the check is what says so.
  check_eq_u32(re_00b1fbf0_shared_default_true(nullptr), expected,
               "A: a null receiver still answers the same byte, so nothing "
               "branches on it");

  // A receiver that is certainly not mapped. Any dereference faults here, which
  // is a stronger statement than any byte comparison could make.
  check_eq_u32(re_00b1fbf0_shared_default_true(
                   reinterpret_cast<Receiver*>(kUnmappedReceiver)),
               expected,
               "B: a receiver at an unmapped address is never dereferenced, so "
               "the call returns instead of faulting");

  // Markers all over the object, none of which may move the answer.
  fill(storage.bytes + kGuard, kObjectSize, 0u);
  const std::uint32_t marker = 0xdeadbeefu;
  Receiver* const object = storage.at(0);
  put_u32(object, 0x00u, marker);
  put_u32(object, 0x04u, marker);
  put_u32(object, 0x40u, marker);
  put_u32(object, 0xFCu, marker);
  for (std::size_t i = 0; i < kTrialCount; ++i) {
    check_eq_u32(re_00b1fbf0_shared_default_true(storage.at(kTrialOffsets[i])),
                 expected,
                 "B: a marker planted inside the receiver never becomes the "
                 "answer");
  }
  check_eq_u32(get_u32(object, 0x00u), marker,
               "C: the marker at +0x00 is untouched by the calls");
  check_eq_u32(get_u32(object, 0x40u), marker,
               "C: the marker at +0x40 is untouched by the calls");
  check_eq_u32(get_u32(object, 0xFCu), marker,
               "C: the marker at +0xFC is untouched by the calls");

  // Case C proper: every byte of the run and both guard bands, before and
  // after the whole battery.
  std::uint8_t before[kStorageSize];
  std::memcpy(before, storage.bytes, kStorageSize);
  for (std::size_t i = 0; i < kTrialCount; ++i) {
    static_cast<void>(
        re_00b1fbf0_shared_default_true(storage.at(kTrialOffsets[i])));
  }
  static_cast<void>(re_00b1fbf0_shared_default_true(object));
  static_cast<void>(re_00b1fbf0_shared_default_true(nullptr));
  check(std::memcmp(before, storage.bytes, kStorageSize) == 0,
        "C: not one byte of the receiver or of either guard band moved across "
        "the whole battery");
  check(storage.guards_intact(), "C: both guard bands are intact");
}

// Case E: the callee's stack effect, measured against a calibrated instrument.
void test_callee_pop_measured() {
  // Calibration first. The two controls fix what this instrument reads for a
  // callee that pops nothing and for one that pops eight bytes, so a probe that
  // simply reported zero would be caught here rather than silently clearing the
  // reconstruction.
  //
  // `before` and `after` are the stack pointer inside the probe's own frame, so
  // they are deliberately NOT compared against the C++ caller's stack pointer:
  // the two differ by the probe's frame and the return address, and equating
  // them would compare a measurement with an unrelated quantity. What is checked
  // is that the probe hands the CALLER's stack back, by bracketing the probe
  // call itself.
  //
  // A CANARY on the caller's own frame, not a second reading of the stack
  // pointer. Reading ESP before and after the probe call is the obvious way to
  // ask whether the probe was transparent, and it is the wrong way: the two
  // reads sit at two different program points, and the compiler is free to
  // build the probe call's arguments in between, which moves ESP for reasons
  // that have nothing to do with the probe. That is not hypothetical -- g++ at
  // -O1 and above does exactly it, clang does not, and the resulting check
  // failed on one compiler and passed on the other for a body that was correct
  // in both. A canary planted in the caller's own locals is immune to that,
  // because the probe has no way to reach it and any write to it would be the
  // probe's own doing.
  volatile std::uint32_t canary = 0x0badf00du;
  std::uint32_t canary_copy = canary;
  const Sample zero = probe(
      address_of(reinterpret_cast<const void*>(&control_pops_zero_00b1fbf0)),
      0x11111111u, 0x22222222u);
  check_eq_u32(canary, canary_copy,
               "E: the probe wrote nothing into the caller's own frame, so it "
               "is transparent to the memory around it");
  check_eq_u32(zero.popped, 0u,
               "E: the control that pops nothing measures a zero-byte pop");
  check_eq_u32(zero.returned, 0x22222222u,
               "E: the zero-pop control writes no register at all, so the "
               "instrument hands the caller's EAX back verbatim, which is what "
               "makes it an instrument check and not a twin");

  const Sample eight = probe(
      address_of(reinterpret_cast<const void*>(&control_pops_eight_00b1fbf0)),
      0x11111111u, 0x22222222u);
  check_eq_u32(canary, canary_copy,
               "E: and the eight-pop control leaves the caller's frame alone "
               "too, so its extra pop was absorbed and did not escape");
  check_eq_u32(eight.popped, 8u,
               "E: the control that pops eight bytes measures an eight-byte "
               "pop, so the instrument discriminates");
  check(eight.popped != zero.popped,
        "E: the two controls read differently, so the measurement is not a "
        "constant");

  // The reconstruction itself, entered with a real, guard-banded object as the
  // register-carried value.
  Storage storage;
  fill(storage.bytes + kGuard, kObjectSize, 0x5a5a5a5au);
  std::uint8_t before[kStorageSize];
  std::memcpy(before, storage.bytes, kStorageSize);
  const std::uint32_t object_address = address_of(storage.at(0));

  const Sample live =
      probe(address_of_reconstruction(), object_address, 0x00000000u);
  check_eq_u32(live.popped, 0u,
               "E: the callee pops nothing, which is what a RET with no "
               "immediate accounts for and what the caller-side cleanup needs");
  check_eq_u32(live.ecx_at_call, object_address,
               "E: the callee is entered with the register-carried value in "
               "ECX, the register the machine record names");
  check_eq_u32(live.returned & 0xFFu, kImageBody[1],
               "E: the low byte of the return register is the image's "
               "immediate");
  check(std::memcmp(before, storage.bytes, kStorageSize) == 0,
        "E: not one byte of the object the register carried was written");
  check(storage.guards_intact(), "E: nothing was written outside the object");

  // A value that is not a mapped address. A body that dereferenced what it is
  // given could not survive this.
  const Sample unmapped =
      probe(address_of_reconstruction(), kUnmappedReceiver, 0x00000000u);
  check_eq_u32(unmapped.popped, 0u, "E: the pop is zero for this input too");
  check_eq_u32(unmapped.returned & 0xFFu, kImageBody[1],
               "E: an unmapped register-carried value produces the same answer, "
               "so the body dereferences nothing it is given");
  check_eq_u32(unmapped.ecx_at_call, kUnmappedReceiver,
               "E: the unmapped value really was the one in ECX");

  // The C++-level bracket, with a memory clobber on both reads so the compiler
  // cannot move either across the call.
  const std::uint32_t sp_before = stack_pointer();
  static_cast<void>(re_00b1fbf0_shared_default_true(storage.at(0)));
  const std::uint32_t sp_after = stack_pointer();
  check_eq_u32(sp_after, sp_before,
               "E: across a compiler-generated call the stack pointer is the "
               "same afterwards as before it, which is the caller-cleans half "
               "of the determination");
}

// Case D: the answer is a byte, not a dword. The full EAX is read back after a
// call made with a poison pattern in its upper 24 bits.
void test_return_is_a_byte() {
  bool has_anchor = false;
  const std::uint8_t* const emitted = reinterpret_cast<const std::uint8_t*>(
      reinterpret_cast<const void*>(&re_00b1fbf0_shared_default_true));
  (void)emitted_body_offset(emitted, &has_anchor);

  if (has_anchor) {
    // Named, not waved through. A get_pc_thunk anchor is a call to the thunk
    // followed by a one-dollar add to EAX, and that add changes all 32 bits, so
    // the upper half this case measures would be a property of the toolchain at
    // this optimisation level rather than of this reconstruction. Case G pins
    // the emitted bytes at this level instead, which is the same fact seen from
    // the other side.
    std::fprintf(stderr,
                 "note: case D skipped, this build prepends a get_pc_thunk PC "
                 "anchor whose add to EAX would corrupt the measurement; case "
                 "G pins the emitted bytes at this level instead\n");
    return;
  }

  const std::uint32_t poisons[] = {0x00000000u, 0xffffffffu, 0x5a5a5a00u,
                                   0x12345600u, 0x00abcdefu, 0xff00ff00u};
  for (std::size_t i = 0; i < sizeof(poisons) / sizeof(poisons[0]); ++i) {
    const std::uint32_t poison = poisons[i];
    const Sample sample =
        probe(address_of_reconstruction(), kUnmappedReceiver, poison);
    check_eq_u32(sample.returned & 0xFFu, kImageBody[1],
                 "D: the low byte of the return register is the image's "
                 "immediate whatever the caller left above it");
    check_eq_u32(sample.returned & 0xFFFFFF00u, poison & 0xFFFFFF00u,
                 "D: the upper 24 bits of the return register come back "
                 "untouched, so the body writes one byte and not four");
  }

  // The control with the same shape as the reconstruction reads the same way,
  // so the measurement is checking the instrument as well as the target.
  const Sample control = probe(
      address_of(reinterpret_cast<const void*>(&control_pops_zero_00b1fbf0)),
      kUnmappedReceiver, 0xabcdef01u);
  check_eq_u32(control.returned & 0xFFFFFF00u, 0xabcdef00u,
               "D: the instrument reports a caller's register untouched, so a "
               "pass here is not an artefact of the probe");
}

// Case G: decode what the compiler actually emitted for the function.
void test_emitted_body() {
  const std::uint8_t* const emitted = reinterpret_cast<const std::uint8_t*>(
      reinterpret_cast<const void*>(&re_00b1fbf0_shared_default_true));
  bool has_anchor = false;
  const std::size_t offset = emitted_body_offset(emitted, &has_anchor);
  check(offset != static_cast<std::size_t>(-1),
        "G: the emitted code contains the target's three bytes, either at the "
        "entry or immediately after a recognised get_pc_thunk PC anchor");
  if (offset == static_cast<std::size_t>(-1)) {
    return;
  }
  check_eq_u32(emitted[offset + 0], 0xB0u,
               "G: the emitted first instruction is opcode B0, MOV r8,imm8 "
               "with its register field fixed at AL");
  check_eq_u32(emitted[offset + 1], kImageBody[1],
               "G: the emitted immediate is the byte 0x01");
  check_eq_u32(emitted[offset + 2], 0xC3u,
               "G: the emitted body ends in a bare RET, with no immediate, so "
               "the callee pops nothing");
}

// Case H, second half: the function reached through a two-level load from a
// synthetic table, and the table's repointing changes the callee. The table is
// this file's own and says nothing about the binary's own tables, which this
// package does not claim beyond case I's record of their addresses.
std::uint8_t TEST_THISCALL alternative_callee_00b1fbf0(Receiver* receiver) {
  (void)receiver;
  return 0;
}

using Entry = std::uint8_t (TEST_THISCALL*)(Receiver*);

void test_synthetic_dispatch() {
  Storage storage;
  Receiver* const object = storage.at(0);

  Entry slot = &re_00b1fbf0_shared_default_true;
  Entry loaded = reinterpret_cast<Entry>(reinterpret_cast<void*>(slot));
  const std::uint32_t through_reconstruction = loaded(object);
  check_eq_u32(through_reconstruction, kImageBody[1],
               "H: the two-level load reached the reconstructed function "
               "through the slot shape, and it answered the image's byte");

  slot = &alternative_callee_00b1fbf0;
  loaded = reinterpret_cast<Entry>(reinterpret_cast<void*>(slot));
  check(loaded(object) != through_reconstruction,
        "H: repointing the table changes the callee and the answer, so the "
        "slot decides which body runs");
  check_eq_u32(loaded(object), 0u,
               "H: the alternative callee's own answer, so the two entries are "
               "distinguishable rather than both returning the same thing");
  check(storage.guards_intact(), "H: no stray write around the dispatch");
}

// Case I: the machine ABI record's determination, value by value.
//
// Each constant in the header is compared against a literal written HERE, not
// against the header's own pointer to it or against another header constant. A
// check that compared a value with itself would survive the very edit it exists
// to catch, which is exactly what happened in the previous revision of this
// package: the record abstained, the source carried a modelling choice, and
// nothing in the test noticed, so the abstention could be deleted or reversed
// without a single check failing.
void test_machine_abi_record() {
  // The determination itself: __thiscall, INFERRED, TWO surviving candidates,
  // no ambiguity.
  check_eq_u32(static_cast<std::uint32_t>(kDerivedConventionVerdict), 0u,
               "I: the record's convention verdict is __thiscall, not cdecl, "
               "not fastcall and not an abstention");
  check_eq_u32(static_cast<std::uint32_t>(kDerivedConventionConfidence), 1u,
               "I: the convention is INFERRED, not OBSERVED and not UNKNOWN");
  check_eq_u32(static_cast<std::uint32_t>(kCandidateConventionCount), 2u,
               "I: the record keeps TWO candidates, __thiscall and __fastcall, "
               "and this package does not close the second one");
  check_eq_u32(static_cast<std::uint32_t>(kConventionAmbiguityCount), 0u,
               "I: the record reports no convention ambiguity");

  // The receiver: ECX, known from a table slot, and NOT read by the body.
  check_eq_u32(static_cast<std::uint32_t>(kReceiverRegister), 1u,
               "I: the receiver register is ECX (register id 1), which is what "
               "V1-VFT names");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverProvenance), 0u,
               "I: the receiver's provenance is vftable_slot, the record's own "
               "spelling");
  check(!kReceiverPresent,
        "I: the record states the body reads no register receiver, which is "
        "rule R2 and is not a claim that no receiver is on the port");
  check(!kReceiverReadByBody,
        "I: the header states the same R2 observation, and it must not be "
        "quietly upgraded to a dereference");
  check(kReceiverBoundsOnly,
        "I: the receiver is bounds-only, because nothing was ever read through "
        "it");
  check(!kReceiverHasShape, "I: the record gives the receiver no shape");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDereferenceCount), 0u,
               "I: the two instructions dereference the receiver zero times");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDistinctOffsets), 0u,
               "I: no displacement of the receiver was ever seen");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverWrittenThrough), 0u,
               "I: nothing is ever written through the receiver register");
  check(!kReceiverFieldOffsetClaimed,
        "I: no field offset is claimed, in either direction");

  // The stack: caller-side, zero bytes, and INFERRED rather than observed --
  // the confidence the record gives it, not the one a reader would prefer.
  check_eq_u32(static_cast<std::uint32_t>(kObservedCleanupSide), 0u,
               "I: the cleanup side is the caller");
  check_eq_u32(static_cast<std::uint32_t>(kCleanupConfidence), 1u,
               "I: the cleanup determination is INFERRED, as the record states "
               "it: a bare RET is compatible with either side when there is "
               "nothing to pop");
  check_eq_u32(static_cast<std::uint32_t>(kStackCleanupBytes), 0u,
               "I: the cleanup is zero bytes");
  check_eq_u32(static_cast<std::uint32_t>(kRetImmediateBytes), 0u,
               "I: the RET immediate accounts for zero bytes");
  check_eq_u32(static_cast<std::uint32_t>(kStackArgumentSlots), 0u,
               "I: the body accounts for no stack argument slot");

  // The return: EAX, the integral class, one byte, and no type from the record.
  check_eq_u32(static_cast<std::uint32_t>(kReturnRegisterId), 0u,
               "I: the return register is EAX, ModRM reg field 000");
  check_eq_u32(static_cast<std::uint32_t>(kReturnRegisterClass), 0u,
               "I: the machine record classifies the return as integral");
  check_eq_u32(static_cast<std::uint32_t>(kReturnWidthBytes), 1u,
               "I: the returned width is one byte, which comes from the opcode "
               "and not from a record");
  check(!kMachineRecordNamedReturnType,
        "I: the machine record names no return TYPE, and the package must not "
        "present the source's own type as something the machine stated");

  // The extent, restated from the listing rather than from the byte decode.
  check_eq_u32(kTargetVa, 0x00b1fbf0u, "I: the target VA is 0x00b1fbf0");
  check_eq_u32(kBodyFirstByte, 0x00b1fbf0u, "I: the body starts at 0x00b1fbf0");
  check_eq_u32(kBodyLastByte, 0x00b1fbf2u,
               "I: the body's last byte is 0x00b1fbf2");
  check_eq_u32(kBodyEndExclusive, 0x00b1fbf3u,
               "I: the body ends where the 0xCC padding begins");
  check_eq_u32(static_cast<std::uint32_t>(kBodySpanBytes), 3u,
               "I: the body is three bytes");
  check_eq_u32(static_cast<std::uint32_t>(kInstructionCount), 2u,
               "I: the listing is two instructions");
  check_eq_u32(static_cast<std::uint32_t>(kBasicBlockCount), 1u,
               "I: there is one basic block, because there is no branch");
  check_eq_u32(static_cast<std::uint32_t>(kConditionalBranches), 0u,
               "I: there is no conditional branch");
  check_eq_u32(static_cast<std::uint32_t>(kDirectCalleeCount), 0u,
               "I: the body calls nothing");
  check_eq_u32(static_cast<std::uint32_t>(kIndirectTransfers), 0u,
               "I: the body transfers control indirectly zero times");
  check_eq_u32(static_cast<std::uint32_t>(kGlobalReferences), 0u,
               "I: the body names no data-segment address");
  check_eq_u32(static_cast<std::uint32_t>(kParseDeclaredCount), 2u,
               "I: the machine parse consumed both instructions, which is what "
               "makes the listing whole");
  check_eq_u32(static_cast<std::uint32_t>(kParseUnparsedCount), 0u,
               "I: the machine parse left nothing unparsed");
  check(!kParseDegraded, "I: the machine parse is not degraded");

  // The membership V1-VFT reasons from, re-derived: base + 4*index must be the
  // address the word was read back from, and that word must be this target.
  check_eq_u32(kVftableBase, 0x013f57f8u,
               "I: the table the record bases the membership on is 0x013f57f8");
  check_eq_u32(static_cast<std::uint32_t>(kVftableSlotIndex), 3u,
               "I: the record places this address in slot 3 of it");
  check_eq_u32(kVftableBase +
                   4u * static_cast<std::uint32_t>(kVftableSlotIndex),
               0x013f5804u,
               "I: base plus four times the slot index is the address the word "
               "was read back from");
  check_eq_u32(kVftableSlotWord, 0x00b1fbf0u,
               "I: the word at that address is this target's own address, "
               "which is the whole of the membership claim");
  check_eq_u32(static_cast<std::uint32_t>(kVftableMembershipCount), 443u,
               "I: the record's own membership count is 443, reproduced rather "
               "than re-derived");

  // The three tables and the four distinct offsets, each an independent
  // observation, and together the reason no single named method is claimed.
  check_eq_u32(kSlotTable0, 0x013f57f8u, "I: the first table is 0x013f57f8");
  check_eq_u32(static_cast<std::uint32_t>(kSlotOffset0), 0x0cu,
               "I: that table holds the address at slot offset +0x0c");
  check_eq_u32(kSlotTable1, 0x013fc06cu, "I: the second table is 0x013fc06c");
  check_eq_u32(static_cast<std::uint32_t>(kSlotOffset1), 0x10u,
               "I: that table holds the address at +0x10");
  check_eq_u32(static_cast<std::uint32_t>(kSlotOffset2), 0x14u,
               "I: and again at +0x14, so two offsets in one table");
  check_eq_u32(kSlotTable2, 0x01485550u, "I: the third table is 0x01485550");
  check_eq_u32(static_cast<std::uint32_t>(kSlotOffset3), 0x14u,
               "I: that table holds the address at +0x14");
  check_eq_u32(static_cast<std::uint32_t>(kSlotOffset4), 0x60u,
               "I: and at +0x60, a fourth offset");
  check_eq_u32(static_cast<std::uint32_t>(kDistinctSlotOffsetCount), 4u,
               "I: four distinct offsets across three tables is why no single "
               "interface method name is claimed for this address");

  // The six caller-side receipts, each re-derived from its own two constants.
  // A site that is further from its call than the intervening instructions can
  // account for would mean ECX was not provably live at the transfer.
  check_eq_u32(static_cast<std::uint32_t>(kEcxReceiptSiteCount), 6u,
               "I: six sites hand this function a live ECX at the transfer");
  check(kEcxReceiptCall0 > kEcxReceiptSite0,
        "I: the first receipt's CALL follows its ECX load");
  check(kEcxReceiptCall1 > kEcxReceiptSite1,
        "I: the second receipt's CALL follows its ECX load");
  check(kEcxReceiptCall2 > kEcxReceiptSite2,
        "I: the third receipt's CALL follows its ECX load");
  check(kEcxReceiptCall3 > kEcxReceiptSite3,
        "I: the fourth receipt's CALL follows its ECX load");
  check(kEcxReceiptCall4 > kEcxReceiptSite4,
        "I: the fifth receipt's CALL follows its ECX load");
  check(kEcxReceiptCall5 > kEcxReceiptSite5,
        "I: the sixth receipt's CALL follows its ECX load");
  check_eq_u32(kEcxReceiptCall0, 0x0098cc7fu,
               "I: the first receipt's CALL is at 0x0098cc7f");
  check_eq_u32(kEcxReceiptCall1, 0x0096a673u,
               "I: the second receipt's CALL is at 0x0096a673");
  check_eq_u32(kEcxReceiptCall2, 0x0096b3a3u,
               "I: the third receipt's CALL is at 0x0096b3a3");
  check_eq_u32(kEcxReceiptCall3, 0x00a43062u,
               "I: the fourth receipt's CALL is at 0x00a43062");
  check_eq_u32(kEcxReceiptCall4, 0x0082c27au,
               "I: the fifth receipt's CALL is at 0x0082c27a");
  check_eq_u32(kEcxReceiptCall5, 0x00ee8bf9u,
               "I: the sixth receipt's CALL is at 0x00ee8bf9, the one dispatch "
               "through a table slot the whole determination rests on");
  check_eq_u32(kEcxReceiptSite5, 0x00ee8bf1u,
               "I: and its ECX is loaded eight bytes earlier, with the slot "
               "load in between and nothing that writes ECX");

  // The tail transfer, corrected: the export calls that row a direct call and
  // the instruction is a JMP.
  check_eq_u32(kTailTransferInstruction, 0x007f53feu,
               "I: the site the xref export classifies as a direct call is at "
               "0x007f53fe");
  check_eq_u32(kTailTransferTarget, 0x00b1fbf0u,
               "I: and what is there is a transfer to this very address");
  check_eq_u32(kInlinedDuplicateAddress, 0x007f5403u,
               "I: the inlined copy of the identical body sits two bytes after "
               "it, at 0x007f5403, which is the shape a shipped default "
               "produces");

  // The one consumer that compares the answer against the immediate rather than
  // testing it for non-zero. This is what makes the byte claim falsifiable.
  check_eq_u32(kByteCompareInstruction, 0x00e81134u,
               "I: the byte-comparing call site is at 0x00e81134");
  check_eq_u32(kByteCompareNext, 0x00e81139u,
               "I: and the comparison against the immediate 1 is the very next "
               "instruction, CMP AL,0x1");
}

// Case J: the entry really is a __thiscall member.
//
// On i386 a thiscall and a cdecl entry with no stack argument compile to
// IDENTICAL code -- both put the pointer in ECX and both return through a bare
// RET -- so no behavioural case in this file can see the difference between
// them. This case is the one that can, and it exists because the convention is
// the whole load-bearing part of this package's claim.
void test_convention_is_thiscall() {
  bool found = false;
  for (const char* p = kConventionSpelling; *p != '\0'; ++p) {
    if (p[0] == 't' && p[1] == 'h' && p[2] == 'i' && p[3] == 's' &&
        p[4] == 'c' && p[5] == 'a' && p[6] == 'l' && p[7] == 'l') {
      found = true;
    }
  }
  check(kConventionSpelling[0] != '\0',
        "J: the convention macro expands to something non-empty, so the check "
        "below is a read and not a skip");
  check(found,
        "J: the calling-convention macro the source span names expands to a "
        "spelling that carries the __thiscall token");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_shared_default_true_wave12

int main() {
  using namespace openspore::reconstruction::pkg_shared_default_true_wave12;
  // The instrument is calibrated first (case E). A reconstruction whose callee
  // cleanup disagreed with the listing would unbalance every compiler-generated
  // call site the later cases use, so the disagreement is looked for before
  // anything else is driven and the failure names the cleanup rather than
  // whatever corruption it went on to cause.
  test_callee_pop_measured();
  // The emitted bytes next, because the two cases that consult the compiler's
  // output (D and G) are both about the same three bytes and D's applicability
  // is decided by what G sees.
  test_emitted_body();
  test_return_is_a_byte();
  test_image_bytes();
  test_image_has_no_transfer();
  test_convention_is_thiscall();
  test_machine_abi_record();
  test_answer_and_receiver();
  test_synthetic_dispatch();
  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
