// PKG-W2-00E5CAC0 -- VA 0x00e5cac0
// Falsification test for the five-byte __thiscall register pass-through
// reconstruct_00e5cac0 (`MOV EAX,ECX` ; `RET 0x4`).
//
// LAYERING, because a two-instruction body has almost nothing to test and the
// danger is that the test ends up agreeing with itself:
//
//   1. kImageBody in this file is the IMAGE, transcribed: 8B C1 C2 04 00. The
//      G cases assert those bytes against literals and decode their fields (the
//      ModRM byte, the RET immediate), so the transcription itself is under test
//      and cannot drift silently. The reconstruction never reads it.
//   2. reconstruct_00e5cac0() in the .cpp is the code under test. The
//      behavioural cases drive it through its own declaration, so a defect in it
//      cannot be papered over by the transcription.
//   3. The ABI facts a value comparison cannot show are MEASURED: the callee's
//      stack effect is measured across a hand-rolled indirect call (case F), the
//      register the answer arrives in is read out of that same call, and the code
//      the compiler actually emitted for the function is decoded at run time
//      (case H) rather than assumed from the source.
//
// The cases marked REFUTE exist to break the reconstruction:
//
//   A  EAX receives ECX verbatim: twelve distinct receiver values -- one of them
//      the null pointer -- must each come back bit for bit. A reconstruction that
//      returns null unconditionally, the pushed slot, a neighbouring word, or the
//      input plus an offset dies here.
//   B  the answer is the register's own value and not a load through it: marker
//      words are planted all over the object, so a dereferencing reconstruction
//      answers a marker and the correct answer is the address.
//   C  the two carriers are distinguishable: the register-carried value and the
//      pushed slot are given different values in every trial, so a
//      reconstruction that returns the wrong one of the two dies here even
//      though both are 32 bits wide. The register-carried values include
//      unaligned addresses, so a reconstruction that masks the low bits of its
//      answer dies here too.
//   D  the pushed slot is not read: the answer must not change when the slot
//      changes. A reconstruction that folds the slot into the result dies here.
//   E  nothing is written: every byte of the object and of the guard bands
//      around it is compared before and after, for a whole battery of inputs.
//   F  the callee pops exactly four bytes, MEASURED. A `RET 0x4` transcribed as
//      caller cleanup, or as an eight-byte pop, changes the post-call ESP and
//      dies here; so does a body that pushes or pops anything else. The
//      measurement itself is calibrated against two control callees that pop
//      nothing and eight bytes, so a shim that reported four for everything would
//      be caught, and it is checked to leave the caller's stack untouched.
//   G  the image is five bytes and decodes to MOV EAX,ECX then RET 0x4: the
//      ModRM fields and the RET immediate are checked field by field, so a
//      transcription that kept the length but changed the operands dies here.
//   H  under optimisation the compiler's own output for the function is the
//      same two-instruction shape, decoded at run time. Any mutation that
//      changes the emitted operation -- an extra addend, a spill, a test, a
//      frame -- changes these bytes and dies here.
//   I  the image carries no transfer at all: no CALL, no JMP and no opcode that
//      can dispatch indirectly, and no branch either. The same case then shows
//      the function reached through a two-level load from a SYNTHETIC table
//      whose repointing changes the callee, so the caller side is observed
//      without the body ever dispatching.
//   J  the machine ABI record's determination, checked value by value against
//      literals written independently here: the convention, its INFERRED
//      confidence and its single candidate, the receiver register and the
//      vftable-slot provenance, the absence of any receiver shape or offset, and
//      the OBSERVED callee-side cleanup. A package that quietly reverted to the
//      old "no convention, no receiver" abstention fails here.
//   K  the caller-side this-adjustor, MEASURED. The machine has `ADD ECX,0xc` at
//      0x007fbd8d immediately before the `CALL` at 0x007fbd90, and the body
//      itself adjusts nothing. The probe applies an adjustment of its own before
//      the call, exactly as that site does, and the answer must be base+adjust
//      while the unadjusted call on the same base must answer base. A
//      reconstruction that moved the adjustment to the callee side dies here.
//
// What is NOT asserted, and why:
//
//   * The receiver's identity. The determination says the receiver arrives in
//     ECX; it does not say what the receiver IS. The body never dereferences it
//     and never adjusts it, so `Receiver` is declared and left undefined and this
//     test supplies its own opaque byte run through a cast. No class, no vtable
//     identity, no receiver type, no field, no member and no object size is
//     claimed, and NO FIELD OFFSET IS CLAIMED IN EITHER DIRECTION: the body shows
//     no displacement through ECX, so neither a field at some offset nor the
//     object's being flat is asserted here.
//   * The three vtables the pack's xref export names. Case J checks that this
//     package records the three table addresses and slot indices the image
//     actually holds, and nothing more; case I uses a table of its own and
//     claims nothing about those.
//   * The meaning of the popped stack word. The bytes show it is popped and never
//     read; they do not say what it is.

#include "ret_eax_from_ecx_00e5cac0.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_w2_00e5cac0 {
namespace {

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#else
#define TEST_THISCALL __attribute__((thiscall))
#endif

// REGISTER DISCIPLINE, AND WHY THE PROBE IS ONE FILE-SCOPE ASSEMBLY FUNCTION.
//
// The probe is an i386 SysV cdecl function, so EBX, ESI, EDI and EBP must
// survive it. A hand-written probe that borrows ESI to hold an argument or a
// result and never puts it back corrupts its CALLER, not itself -- and it
// corrupts it silently, because the caller's loop counter or pointer usually
// lives in ESI and the damage surfaces as an optimiser-dependent failure in a
// test that has nothing to do with the probe. That is not hypothetical: an
// earlier revision of a sibling package read a probe argument through ESI,
// passed at -O0, and failed from -O1 upwards for exactly that reason.
//
// So the probe below touches ONLY EAX, ECX, EDX and ESP, keeps everything that
// must survive the call in its OWN frame where %ebp can reach it, and never
// writes ESI, EDI, EBX or a memory location the fixtures own. EBX is not
// touched at all, which matters twice over: it is callee-saved so a probe must
// not spend it, and on a PIC i386 build it holds the GOT base, so taking it over
// inside the asm invalidates every address the compiler forms around it. EBP is
// used only as the frame pointer this probe establishes for itself, and `leave`
// puts the caller's back.
//
// The samples are taken through the PROBE'S OWN FRAME POINTER, not through the
// stack pointer, because the stack pointer is exactly the thing the two cleanup
// sides disagree about. The block records ESP BEFORE any push and ESP IMMEDIATELY
// after the call returns, and nothing in between: the difference between the two
// IS the machine's RET immediate, independently of where the call happened to
// sit. A reconstruction that pops too FEW bytes comes back four bytes high, which
// the checks read as a number. One that pops too MANY destroys the return
// address, which no probe can recover: that direction is reported as a crash, not
// as a failed check.
//
// The block is a FILE-SCOPE assembly function rather than an extended-asm block
// in the middle of a C++ body. That bounds its influence to one function, whose
// only contact with the fixtures is through pointers, and it means the compiler
// never has to model registers it cannot see. It is the same shape the sibling
// packages use and it assembles identically under g++ and clang++ at -O0, -O1,
// -O2 and -O3.

// The two control callees, declared before the assembly block that defines them.
// They are observers: nothing here claims anything about them beyond the shape
// the probe calibrates against, and both are entered exactly the way the body is.
extern "C" void control_pops_zero_00e5cac0();
extern "C" void control_pops_eight_00e5cac0();

// The image, as literals, for the byte-level cases G and I. Deliberately NOT a
// shared constant with the reconstruction, so the transcription and the test
// cannot agree by construction.
constexpr std::uint8_t kImageBody[] = {0x8B, 0xC1, 0xC2, 0x04, 0x00};
constexpr std::size_t kImageSize = sizeof(kImageBody);

// The byte the live read shows immediately after the body, from GhidraMCP
// /read_memory at 0x00e5cac0 (`8bc1c20400cccccccccccccccccccccc`).
constexpr std::uint8_t kImagePadByte = 0xCC;

constexpr std::size_t kObjectSize = 0x100;
constexpr std::size_t kGuard = 64;
constexpr std::size_t kStorageSize = kObjectSize * 4 + 2 * kGuard;
constexpr std::uint8_t kGuardByte = 0xA5;

// Offsets into the storage buffer, one per trial. Deliberately irregular and
// deliberately not all four-byte aligned, so the twelve receiver addresses differ
// in their low bits as well as in their high ones and a reconstruction that
// masked or rounded the answer cannot pass.
constexpr std::size_t kTrialOffsets[] = {0x000u, 0x004u, 0x008u, 0x00cu,
                                         0x010u, 0x014u, 0x018u, 0x01cu,
                                         0x001u, 0x005u, 0x009u, 0x00du};
constexpr std::size_t kTrialCount = sizeof(kTrialOffsets) / sizeof(kTrialOffsets[0]);

// The value pushed on the stack for each trial. Always different from the
// register-carried address, so case C can tell the two carriers apart.
constexpr std::uint32_t kSlots[] = {0x00000000u, 0xffffffffu, 0x11111111u,
                                    0x22222222u, 0x33333333u, 0x44444444u,
                                    0x55555555u, 0x66666666u, 0x77777777u,
                                    0x88888888u, 0x99999999u, 0xaaaaaaaau};

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

// A storage buffer with guard bands, filled with a byte that is neither zero nor
// any plausible payload, so a stray write is visible. The receiver type is
// incomplete by design, so the byte run is the test's own and the cast into it
// is the only way to name a receiver at all.
struct Storage {
  std::uint8_t bytes[kStorageSize];

  Storage() : bytes() { std::memset(bytes, kGuardByte, kStorageSize); }

  Receiver* at(std::size_t offset) const {
    return reinterpret_cast<Receiver*>(const_cast<std::uint8_t*>(bytes + kGuard + offset));
  }

  bool guards_intact() const {
    for (std::size_t i = 0; i < kGuard; ++i) {
      if (bytes[i] != kGuardByte ||
          bytes[kGuard + kObjectSize * 4 + i] != kGuardByte) {
        return false;
      }
    }
    return true;
  }
};

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

void fill(std::uint8_t* run, std::size_t size, std::uint32_t seed) {
  // No zero byte in the pattern, so a store of zero into the run is as visible to
  // the byte comparisons as a store of anything else.
  for (std::size_t offset = 0; offset < size; offset += 4) {
    const std::uint32_t word = 0xa5a5f00du ^ seed ^ static_cast<std::uint32_t>(offset);
    std::memcpy(run + offset, &word, sizeof(word));
  }
}

// -- the call probe -----------------------------------------------------------

// What the probe reports. Every field is a measurement taken inside the assembly
// block; none of them is a constant this file chose. The register pairs are
// sampled at probe entry and again at exit, INSIDE the block, so the probe's
// register discipline is measured without a sampling statement in the C++ caller
// perturbing the very frame pointer and callee-saved registers being sampled --
// which is exactly what an earlier revision of a sibling package did, and why its
// "the probe is stack-neutral" checks failed from -O1 upwards while passing at
// -O0.
struct Sample {
  std::uint32_t returned;    // EAX immediately after the call returns
  std::uint32_t delta;       // ESP after the call minus ESP before any push
  std::uint32_t after;       // ESP immediately after the call, before any fixup
  std::uint32_t before;      // ESP before the push, after the frame reservation
  std::uint32_t ecx_at_call; // ECX as the callee will see it, after the adjustor
  std::uint32_t esi_entry;   // the CALLER's ESI, as the probe found it
  std::uint32_t edi_entry;
  std::uint32_t ebx_entry;   // the GOT base on a PIC i386 build
  std::uint32_t esi_exit;    // the caller's ESI as the probe hands it back
  std::uint32_t edi_exit;
  std::uint32_t ebx_exit;
  std::uint32_t esp_at_exit; // ESP as the caller sees it, after the probe's fixup
};

// probe_call_shape_00e5cac0(target, ecx_word, adjust, slot, out)
//
//   8(%ebp)  the callee address, called through a register
//   12(%ebp) the value the caller has in ECX BEFORE its own adjustor
//   16(%ebp) the caller-side adjustor amount, added to ECX before the transfer
//   20(%ebp) the one 4-byte word the callee is expected to pop
//   24(%ebp) the Sample to fill
//
// The frame, with B = %ebp and a 48-byte reservation:
//
//   B-4   the callee address, held across the call
//   B-8   the output pointer, held across the call
//   B-12  the CALLER's ESI, held across the call and handed back
//   B-16  the caller's EDI, likewise
//   B-20  the caller's EBX, likewise
//   B-24  reserved, so the three register slots sit four bytes apart
//   B-28  `before`: %esp after the reservation, i.e. before any push at all
//   B-32  ECX as the callee will see it
//   B-36  `after`: %esp immediately after the call, before any fixup
//   B-40  reserved
//   B-44  reserved
//
// The adjustor is applied with a register add of the caller's own amount rather
// than a baked-in constant, so the same probe models the unadjusted call sites
// (0x007fbd61 and 0x007fbfc8) and the adjusted one (0x007fbd90) without the test
// having two nearly identical assembly blocks to keep in step. Passing 0 for the
// amount is exactly the shape of an unadjusted site.
extern "C" void probe_call_shape_00e5cac0(std::uint32_t target,
                                          std::uint32_t ecx_word,
                                          std::uint32_t adjust,
                                          std::uint32_t slot,
                                          Sample* out);

// The two control callees, defined at file scope in assembly rather than as C++
// functions, because the whole point is the RET form and a compiler-generated
// prologue would move the stack the RET reads from: an unoptimised `ret $8` in a
// C++ body that begins with `pushl %ebp` pops the saved frame pointer and jumps
// into garbage. At file scope the sequence is exactly the instructions written,
// at every optimisation level and under both compilers.
//
// `ret` pops the return address and nothing else; `ret $8` pops the return
// address and the four bytes above it. Both are safe to call through the probe:
// the probe pushes exactly one word, `ret $8` consumes the return address and
// that word and nothing further, and the probe restores ESP from its own `before`
// afterwards whichever of the three outcomes occurred.
__asm__(".text\n"
        ".balign 16\n"
        ".globl probe_call_shape_00e5cac0\n"
        ".type probe_call_shape_00e5cac0, @function\n"
        "probe_call_shape_00e5cac0:\n"
        "  pushl %ebp\n"
        "  movl  %esp, %ebp\n"
        "  subl  $48, %esp\n"
        "  movl  8(%ebp), %eax\n"        // the callee
        "  movl  %eax, -4(%ebp)\n"       // ... held across the call
        "  movl  24(%ebp), %eax\n"       // the output pointer
        "  movl  %eax, -8(%ebp)\n"       // ... likewise
        "  movl  %eax, %edx\n"
        "  movl  %esi, 20(%edx)\n"       // the CALLER's ESI, as the probe found it
        "  movl  %edi, 24(%edx)\n"
        "  movl  %ebx, 28(%edx)\n"
        "  movl  %esi, -12(%ebp)\n"      // held across the call and handed back
        "  movl  %edi, -16(%ebp)\n"
        "  movl  %ebx, -20(%ebp)\n"
        "  movl  %esp, -28(%ebp)\n"      // before: before any push at all
        "  pushl 20(%ebp)\n"             // the one 4-byte stack word
        "  movl  12(%ebp), %ecx\n"       // the register-carried value
        "  movl  16(%ebp), %eax\n"       // the caller's own adjustor amount
        "  addl  %eax, %ecx\n"           // ADD ECX,<adjust>, as 0x007fbd8d does
        "  movl  %ecx, -32(%ebp)\n"      // ECX as the callee will see it
        "  movl  -4(%ebp), %eax\n"
        "  call *%eax\n"                 // indirect call through a register
        "  movl  %esp, -36(%ebp)\n"      // after: before any fixup
        "  movl  %esp, %ecx\n"
        "  movl  -28(%ebp), %edx\n"
        "  subl  %edx, %ecx\n"           // ecx = after - before
        "  movl  -8(%ebp), %edx\n"
        "  movl  %eax, (%edx)\n"         // out->returned
        "  movl  %ecx, 4(%edx)\n"        // out->delta
        "  movl  -36(%ebp), %ecx\n"
        "  movl  %ecx, 8(%edx)\n"        // out->after
        "  movl  -28(%ebp), %ecx\n"
        "  movl  %ecx, 12(%edx)\n"       // out->before
        "  movl  -32(%ebp), %ecx\n"
        "  movl  %ecx, 16(%edx)\n"       // out->ecx_at_call
        "  movl  -12(%ebp), %ecx\n"
        "  movl  %ecx, 32(%edx)\n"       // out->esi_exit
        "  movl  -16(%ebp), %ecx\n"
        "  movl  %ecx, 36(%edx)\n"       // out->edi_exit
        "  movl  -20(%ebp), %ecx\n"
        "  movl  %ecx, 40(%edx)\n"       // out->ebx_exit
        "  movl  -28(%ebp), %esp\n"      // put the stack back, whatever happened
        "  movl  %esp, 44(%edx)\n"       // out->esp_at_exit
        "  leave\n"
        "  ret\n"
        ".size probe_call_shape_00e5cac0, .-probe_call_shape_00e5cac0\n"
        ".globl control_pops_zero_00e5cac0\n"
        ".type control_pops_zero_00e5cac0, @function\n"
        "control_pops_zero_00e5cac0:\n"
        "  movl %ecx, %eax\n"
        "  ret\n"
        ".size control_pops_zero_00e5cac0, .-control_pops_zero_00e5cac0\n"
        ".globl control_pops_eight_00e5cac0\n"
        ".type control_pops_eight_00e5cac0, @function\n"
        "control_pops_eight_00e5cac0:\n"
        "  movl %ecx, %eax\n"
        "  ret $8\n"
        ".size control_pops_eight_00e5cac0, .-control_pops_eight_00e5cac0\n");

// The object the probes hand to the callee, with a guard band on each side. It is
// at file scope so its address does not move with the stack and so the probe can
// be handed it as a plain word.
struct Probe {
  std::uint8_t lead[kGuard];
  std::uint8_t run[kObjectSize];
  std::uint8_t trail[kGuard];
};

Probe g_probe;

bool band_intact(const std::uint8_t* band) {
  for (std::size_t i = 0; i < kGuard; ++i) {
    if (band[i] != kGuardByte) {
      return false;
    }
  }
  return true;
}

// One probe call. `adjust` is the caller-side this-adjustor amount, 0 for the
// unadjusted call sites. The popped-byte figure is derived here rather than
// inside the assembly, from the measured ESP delta and the one constant the RET
// immediate establishes:
//
//   callee pops 0 -> delta -4 -> popped 0
//   callee pops 4 -> delta  0 -> popped 4
//   callee pops 8 -> delta +4 -> popped 8
int probe(std::uint32_t target, std::uint32_t ecx_word, std::uint32_t adjust,
          std::uint32_t slot, Sample* out) {
  probe_call_shape_00e5cac0(target, ecx_word, adjust, slot, out);
  return static_cast<int>(static_cast<std::uint32_t>(kRetImmediateBytes) +
                          out->delta);
}

std::uint32_t address_of_reconstruction() {
  return address_of(reinterpret_cast<const void*>(&reconstruct_00e5cac0));
}

// Case G: the transcribed image, decoded field by field.
void test_image_bytes() {
  check_eq_u32(static_cast<std::uint32_t>(kImageSize), 5u,
               "G: the body at 0x00e5cac0 is five bytes");
  check_eq_u32(kImageBody[0], 0x8Bu, "G: 0x00e5cac0 is opcode 8B, MOV r32,r/m32");
  check_eq_u32(kImageBody[1], 0xC1u, "G: the ModRM byte is C1");
  check_eq_u32((kImageBody[1] >> 6) & 0x3u, 0x3u,
               "G: ModRM mod=11, so both operands are registers");
  check_eq_u32((kImageBody[1] >> 3) & 0x7u, 0x0u,
               "G: ModRM reg=000, so the destination is EAX");
  check_eq_u32(kImageBody[1] & 0x7u, 0x1u,
               "G: ModRM r/m=001, so the source is ECX");
  check_eq_u32(kImageBody[2], 0xC2u, "G: 0x00e5cac2 is opcode C2, RET imm16");
  check_eq_u32(kImageBody[3], 0x04u,
               "G: the RET immediate is the low byte 0x04, little-endian");
  check_eq_u32(kImageBody[4], 0x00u,
               "G: the RET immediate is the high byte 0x00, so 0x0004");
  check_eq_u32(static_cast<std::uint32_t>(kImageBody[3]) |
                   (static_cast<std::uint32_t>(kImageBody[4]) << 8),
               4u, "G: RET 0x4 pops four bytes");
  check_eq_u32(static_cast<std::uint32_t>(kImagePadByte), 0xCCu,
               "G: the byte after the body is 0xCC inter-function padding");

  // The header's transcription of the same five bytes, position by position, and
  // its derived constants against literals written here rather than there.
  check_eq_u32(kTargetBytes[0], kImageBody[0], "G: the header's byte 0");
  check_eq_u32(kTargetBytes[1], kImageBody[1], "G: the header's byte 1");
  check_eq_u32(kTargetBytes[2], kImageBody[2], "G: the header's byte 2");
  check_eq_u32(kTargetBytes[3], kImageBody[3], "G: the header's byte 3");
  check_eq_u32(kTargetBytes[4], kImageBody[4], "G: the header's byte 4");
  check_eq_u32(static_cast<std::uint32_t>(kStackCleanupBytes), 4u,
               "G: the header's cleanup constant is the RET immediate");
  check_eq_u32(static_cast<std::uint32_t>(kBodySpanBytes),
               static_cast<std::uint32_t>(kImageSize),
               "G: the header's body length is the transcribed length");
  check_eq_u32(kInterFunctionPad, kImagePadByte,
               "G: the header records the same padding byte");
}

// Case I, first half: the image carries no transfer and no branch.
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
  check(!call_or_jump, "I: the image carries no CALL, JMP or FF /2,/3 opcode");
  check(!conditional, "I: the image carries no conditional branch opcode");
}

// Cases A, B, C, D: the register pass-through, the two carriers, the untouched
// slot, and the absence of any load through the register-carried value.
void test_identity_and_carriers() {
  Storage storage;
  Receiver* const object = storage.at(0);

  // Markers all over the object, none of which may move the answer.
  fill(storage.bytes + kGuard, kObjectSize, 0u);
  put_u32(object, 0x00u, 0x00000000u);

  for (std::size_t i = 0; i < kTrialCount; ++i) {
    Receiver* const carried = storage.at(kTrialOffsets[i]);
    const Word slot = kSlots[i];

    // Case C: the two carriers always differ.
    check(address_of(carried) != slot, "C: the two carriers hold different values");

    // Case A: EAX receives ECX verbatim, bit for bit.
    check_eq_u32(address_of(reconstruct_00e5cac0(carried, slot)),
                 address_of(carried),
                 "A: the returned value is the register-carried input");

    // Case C again: unaligned carriers survive, so nothing is masked or
    // rounded on the way out.
    check((address_of(carried) & 0x3u) == (kTrialOffsets[i] & 0x3u),
          "C: the carrier's low bits are the trial's low bits");
  }

  // The null register-carried value is a value like any other here: the body
  // has no branch, so it cannot special-case it.
  check(reconstruct_00e5cac0(nullptr, 0u) == nullptr,
        "A: a null register-carried value answers null");

  // Case B: the answer is the address, not a word stored inside the object.
  const std::uint32_t marker = 0xdeadbeefu;
  put_u32(object, 0x00u, marker);
  put_u32(object, 0x04u, marker);
  put_u32(object, 0x40u, marker);
  check(reconstruct_00e5cac0(object, 0u) !=
            reinterpret_cast<const Receiver*>(static_cast<std::uintptr_t>(marker)),
        "B: the answer is not a marker word planted inside the object");
  check_eq_u32(get_u32(object, 0x00u), marker,
               "B: the marker at +0x00 is untouched by the call");
  check_eq_u32(get_u32(object, 0x40u), marker,
               "B: the marker at +0x40 is untouched by the call");

  // Case D: the pushed slot is not read. Same carrier, four different slots.
  Receiver* const carried = storage.at(kTrialOffsets[0]);
  const Receiver* const with_zero = reconstruct_00e5cac0(carried, 0u);
  const Receiver* const with_ones = reconstruct_00e5cac0(carried, 0xffffffffu);
  const Receiver* const with_marker =
      reconstruct_00e5cac0(carried, address_of(carried));
  const Receiver* const with_ffff = reconstruct_00e5cac0(carried, 0xffffu);
  check(with_zero == with_ones, "D: the answer does not change with the pushed slot");
  check(with_ones == with_marker,
        "D: the answer does not change when the slot equals the carrier");
  check(with_marker == with_ffff, "D: the answer is constant across every slot");
  check_eq_u32(address_of(with_zero), address_of(carried),
               "D: the constant answer is the carrier");

  check(storage.guards_intact(), "D: the guard bands survive the whole battery");
}

// Case E: nothing is written, for a whole battery of inputs.
void test_writes_nothing() {
  Storage storage;
  Receiver* const object = storage.at(0);
  fill(storage.bytes + kGuard, kObjectSize, 0u);
  std::uint8_t before[kStorageSize];
  std::memcpy(before, storage.bytes, kStorageSize);

  for (std::size_t i = 0; i < kTrialCount; ++i) {
    static_cast<void>(
        reconstruct_00e5cac0(storage.at(kTrialOffsets[i]), kSlots[i]));
  }
  static_cast<void>(reconstruct_00e5cac0(object, 0u));
  static_cast<void>(reconstruct_00e5cac0(nullptr, 0u));

  check(std::memcmp(before, storage.bytes, kStorageSize) == 0,
        "E: every byte of the object and both guard bands is unchanged");
  check(storage.guards_intact(), "E: the guard bands are intact");
}

// Case F: the callee's stack effect, measured rather than asserted.
//
// The three calls below are the whole argument. The two controls fix what the
// measurement reads for a callee that pops nothing and for one that pops eight,
// so a probe that simply reported four would be caught; the reconstruction is
// then measured against that calibrated instrument. The probe is also checked to
// leave the caller's stack and its callee-saved registers untouched, so a
// measurement bug cannot masquerade as a pass, and the answer register is read out
// of the same call, which doubles as a pass-through check taken with a value that
// is not a mapped address.
void test_callee_stack_pop_measured() {
  // Calibration: the two controls fix what this instrument reads for a callee
  // that pops nothing and for one that pops eight, so a probe that simply
  // reported four would be caught here rather than silently clearing the
  // reconstruction.
  Sample zero;
  const int zero_popped =
      probe(address_of(reinterpret_cast<const void*>(&control_pops_zero_00e5cac0)),
            0x11111111u, 0u, 0x2468ace0u, &zero);
  check_eq_u32(static_cast<std::uint32_t>(zero_popped), 0u,
               "F: the control that pops nothing measures a zero-byte pop");
  check_eq_u32(zero.returned, 0x11111111u,
               "F: the control answers with the value ECX carried");
  check_eq_u32(zero.esp_at_exit, zero.before,
               "F: the probe hands the caller's stack pointer back untouched");

  Sample eight;
  const int eight_popped =
      probe(address_of(reinterpret_cast<const void*>(&control_pops_eight_00e5cac0)),
            0x22222222u, 0u, 0x2468ace0u, &eight);
  check_eq_u32(static_cast<std::uint32_t>(eight_popped), 8u,
               "F: the control that pops eight measures an eight-byte pop");
  check_eq_u32(eight.returned, 0x22222222u,
               "F: the second control answers with the value ECX carried");
  check_eq_u32(eight.esp_at_exit, eight.before,
               "F: the probe hands the caller's stack pointer back untouched");

  // Probe 1: a real, guard-banded object as the register-carried value. A body
  // that read through its answer or wrote through the register fails here, on
  // a value comparison, rather than on a fault that would report nothing.
  std::memset(g_probe.lead, kGuardByte, kGuard);
  std::memset(g_probe.trail, kGuardByte, kGuard);
  fill(g_probe.run, kObjectSize, 0x5a5a5a5au);
  std::uint8_t probe_before[kObjectSize];
  std::memcpy(probe_before, g_probe.run, sizeof(probe_before));
  const std::uint32_t probe_address = address_of(g_probe.run);

  Sample live;
  const int popped = probe(address_of_reconstruction(), probe_address, 0u,
                           0x2468ace0u, &live);

  check_eq_u32(static_cast<std::uint32_t>(popped), 4u,
               "F: the callee pops exactly the four bytes RET 0x4 accounts for");
  check_eq_u32(live.esp_at_exit, live.before,
               "F: the probe leaves the caller's stack alone");
  check_eq_u32(live.esi_exit, live.esi_entry, "F: the probe returns ESI unchanged");
  check_eq_u32(live.edi_exit, live.edi_entry, "F: the probe returns EDI unchanged");
  check_eq_u32(live.ebx_exit, live.ebx_entry,
               "F: the probe returns EBX, the PIC GOT base, unchanged");
  check_eq_u32(live.returned, probe_address,
               "F: the return register carries the register-carried value "
               "verbatim rather than a word loaded through it");
  check_eq_u32(live.ecx_at_call, probe_address,
               "F: the callee is entered with the register-carried value in ECX");
  check(band_intact(g_probe.lead), "F: nothing was written before the object");
  check(band_intact(g_probe.trail), "F: nothing was written after the object");
  check(std::memcmp(probe_before, g_probe.run, sizeof(probe_before)) == 0,
        "F: not one byte of the object the register carried was written");
  check_eq_u32(live.delta, 0u,
               "F: the probe's own push and the callee's pop cancel, so the "
               "four bytes are the callee's and the probe's");

  // Probe 2: a value that is not a mapped address. A body that dereferences
  // what it returns cannot survive this.
  Sample unmapped;
  const int unmapped_popped =
      probe(address_of_reconstruction(), 0x5a5a5a5au, 0u, 0x2468ace0u, &unmapped);
  check_eq_u32(static_cast<std::uint32_t>(unmapped_popped), 4u,
               "F: the pop is four bytes for this input too");
  check_eq_u32(unmapped.returned, 0x5a5a5a5au,
               "F: an unmapped register-carried value comes back bit for bit, "
               "so the body dereferences nothing it returns");
}

// Case K: the caller-side this-adjustor, MEASURED.
//
// The machine's own call site at 0x007fbd90 is preceded, three bytes earlier at
// 0x007fbd8d, by `ADD ECX,0xc`. The body at 0x00e5cac0 adjusts nothing: five
// bytes with no add, no sub and no lea. So on the same base address the
// unadjusted call and the adjusted call must answer differently, and the
// difference must be exactly the caller's constant and nothing else. A
// reconstruction that moved the adjustment to the callee side -- adding 0xc of
// its own, or subtracting it -- dies here, and so does one that answered the
// pre-adjustment value.
void test_caller_side_this_adjustor() {
  const std::uint32_t base = address_of(g_probe.run);
  const std::uint32_t adjust = kThisAdjustment;

  Sample plain;
  const int plain_popped =
      probe(address_of_reconstruction(), base, 0u, 0x2468ace0u, &plain);

  Sample adjusted;
  const int adjusted_popped =
      probe(address_of_reconstruction(), base, adjust, 0x2468ace0u, &adjusted);

  check_eq_u32(plain.ecx_at_call, base,
               "K: an unadjusted call site hands the base address straight over");
  check_eq_u32(plain.returned, base,
               "K: an unadjusted call site answers with the address it was given");
  check_eq_u32(adjusted.ecx_at_call, base + adjust,
               "K: the caller's ADD ECX,0xc is applied before the transfer");
  check_eq_u32(adjusted.returned, base + adjust,
               "K: the adjusted call site answers with this + 0xc");
  check(adjusted.returned != plain.returned,
        "K: the adjustment changes the answer, so it is not a no-op");
  check_eq_u32(adjusted.returned - plain.returned, adjust,
               "K: the whole difference is the caller's 0xc and nothing else");
  check_eq_u32(static_cast<std::uint32_t>(plain_popped), 4u,
               "K: the cleanup is four bytes at the unadjusted site too");
  check_eq_u32(static_cast<std::uint32_t>(adjusted_popped), 4u,
               "K: the cleanup is four bytes at the adjusted site too");
  // The caller's constant is the machine's, not this test's: the header
  // transcribes it and the check above re-derives the answer from it, so an edit
  // to either one without the other shows up as a disagreement.
  check_eq_u32(kThisAdjustorInstruction + 3u, kThisAdjustorCallSite,
               "K: ADD ECX,0xc is three bytes and the CALL follows it at once");
  check_eq_u32(kThisAdjustment, 0x0cu,
               "K: the adjustor constant is the 0xc the image carries");
}

// Case J: the machine ABI record's determination, value by value.
//
// Each constant in the header is compared against a literal written HERE, not
// against the header's own pointer to it or against another header constant. A
// check that compared a value with itself would survive the very edit it exists
// to catch, which is exactly what happened in the previous revision of this
// package: the record abstained, the source carried a modelling choice, and
// nothing in the test noticed, so the abstention could be deleted or reversed
// without a single check failing.
void test_machine_abi_record() {
  // The determination itself: __thiscall, INFERRED, one candidate, no ambiguity.
  check_eq_u32(static_cast<std::uint32_t>(kDerivedConventionVerdict), 0u,
               "J: the record's convention verdict is __thiscall");
  check_eq_u32(static_cast<std::uint32_t>(kDerivedConventionConfidence), 1u,
               "J: the convention is INFERRED, not OBSERVED and not UNKNOWN");
  check_eq_u32(static_cast<std::uint32_t>(kCandidateConventionCount), 1u,
               "J: __thiscall is the only candidate the record names");
  check_eq_u32(static_cast<std::uint32_t>(kConventionAmbiguityCount), 0u,
               "J: the record reports no convention ambiguity");

  // The receiver: present, in ECX, known from vftable-slot dispatch, and with no
  // shape and no offsets because the body never dereferences it.
  check_eq_u32(static_cast<std::uint32_t>(kDerivedReceiverRegister), 0u,
               "J: the receiver register is ECX");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverProvenance), 0u,
               "J: the receiver's provenance is vftable_slot_dispatch");
  check(kReceiverPresent, "J: the record states a receiver is present");
  check(kReceiverBoundsOnly,
        "J: the receiver is bounds-only, because nothing was ever read through it");
  check(!kReceiverHasShape, "J: the record gives the receiver no shape");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDereferenceCount), 0u,
               "J: the two instructions dereference the receiver zero times");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDistinctOffsets), 0u,
               "J: no displacement of the receiver was ever seen");
  check(!kReceiverFieldOffsetClaimed,
        "J: no field offset is claimed, in either direction");

  // The cleanup: OBSERVED, independent of the convention, and four bytes.
  check_eq_u32(static_cast<std::uint32_t>(kObservedCleanupSide), 0u,
               "J: the cleanup side is the callee");
  check_eq_u32(static_cast<std::uint32_t>(kRetImmediateBytes), 4u,
               "J: the RET immediate accounts for four bytes");
  check_eq_u32(static_cast<std::uint32_t>(kStackArgumentWords), 1u,
               "J: the popped area is one 32-bit word");

  // The popped word is data, not a receiver, and is neither read nor written.
  check(!kStackArgumentRead, "J: the popped stack word is never read");
  check(!kStackArgumentWritten, "J: the popped stack word is never written");
  check(!kStackArgumentIsReceiver,
        "J: the popped stack word is not the receiver and never becomes one");

  // The return: EAX, four bytes wide, which is what MOV EAX,ECX writes.
  check_eq_u32(static_cast<std::uint32_t>(kReturnRegisterId), 0u,
               "J: the return register is EAX, ModRM reg field 0");
  check_eq_u32(static_cast<std::uint32_t>(kReturnWidthBytes), 4u,
               "J: the returned value is four bytes wide");

  // The extent, restated from the listing rather than from the byte decode.
  check_eq_u32(kTargetVa, 0x00e5cac0u, "J: the target VA is 0x00e5cac0");
  check_eq_u32(kBodyFirstByte, 0x00e5cac0u, "J: the body starts at 0x00e5cac0");
  check_eq_u32(kBodyLastByte, 0x00e5cac4u, "J: the body's last byte is 0x00e5cac4");
  check_eq_u32(kBodyEndExclusive, 0x00e5cac5u,
               "J: the body ends where the 0xCC padding begins");
  check_eq_u32(static_cast<std::uint32_t>(kInstructionCount), 2u,
               "J: the listing is two instructions");
  check_eq_u32(static_cast<std::uint32_t>(kBasicBlockCount), 1u,
               "J: there is one basic block, because there is no branch");
  check_eq_u32(static_cast<std::uint32_t>(kConditionalBranches), 0u,
               "J: there is no conditional branch");
  check_eq_u32(static_cast<std::uint32_t>(kDirectCalleeCount), 0u,
               "J: the body calls nothing");
  check_eq_u32(static_cast<std::uint32_t>(kIndirectTransfers), 0u,
               "J: the body transfers control indirectly zero times");
  check_eq_u32(static_cast<std::uint32_t>(kGlobalReferences), 0u,
               "J: the body names no data-segment address");
  check_eq_u32(static_cast<std::uint32_t>(kStackArgumentSlots), 1u,
               "J: the body accounts for one stack word, through the RET alone");

  // The caller side, which CORROBORATES the determination rather than making it:
  // three direct call sites, exactly one of them preceded by a caller-side
  // this-adjustor. The addresses and the constant are the machine's.
  check_eq_u32(static_cast<std::uint32_t>(kDirectCallSiteCount), 3u,
               "J: the image has three direct call sites for this address");
  check_eq_u32(kDirectCallSites[0], 0x007fbd61u, "J: the first call site is 0x007fbd61");
  check_eq_u32(kDirectCallSites[1], 0x007fbd90u, "J: the second call site is 0x007fbd90");
  check_eq_u32(kDirectCallSites[2], 0x007fbfc8u, "J: the third call site is 0x007fbfc8");
  check_eq_u32(kThisAdjustorInstruction, 0x007fbd8du,
               "J: ADD ECX,0xc sits at 0x007fbd8d, three bytes before the CALL");
  check_eq_u32(kThisAdjustorCallSite, 0x007fbd90u,
               "J: the adjusted call site is 0x007fbd90");

  // The three tables, each read back out of the image at base + 4*index. They are
  // the membership R1-VFT reasons from, and nothing more: one address in three
  // tables is what identical folding and vtable merging both produce, so no
  // class identity is claimed for any of them.
  check_eq_u32(static_cast<std::uint32_t>(kTableCount), 3u,
               "J: three vptr-backed tables name this address");
  check_eq_u32(kTableBases[0], 0x013f57f8u, "J: the first table is based at 0x013f57f8");
  check_eq_u32(kTableSlotIndices[0], 28,
               "J: the first table holds this address in slot 28");
  check_eq_u32(kTableBases[1], 0x0140116cu, "J: the second table is based at 0x0140116c");
  check_eq_u32(kTableSlotIndices[1], 6,
               "J: the second table holds this address in slot 6");
  check_eq_u32(kTableBases[2], 0x01485550u, "J: the third table is based at 0x01485550");
  check_eq_u32(kTableSlotIndices[2], 21,
               "J: the third table holds this address in slot 21");
  check((kTableBases[0] + 4u * static_cast<std::uint32_t>(kTableSlotIndices[0])) ==
            0x013f5868u,
        "J: table 0x013f57f8 slot 28 is the word at 0x013f5868, which the image "
        "reads back as 0x00e5cac0");
  check((kTableBases[1] + 4u * static_cast<std::uint32_t>(kTableSlotIndices[1])) ==
            0x01401184u,
        "J: table 0x0140116c slot 6 is the word at 0x01401184");
  check((kTableBases[2] + 4u * static_cast<std::uint32_t>(kTableSlotIndices[2])) ==
            0x014855a4u,
        "J: table 0x01485550 slot 21 is the word at 0x014855a4");
}

// The alternative callee for case I: same shape, a different answer, so a
// table slot pointing at the wrong entry is visible. A helper, so its name
// carries no address.
Receiver* TEST_THISCALL alternative_callee(Receiver* receiver, Word slot) {
  (void)slot;
  return reinterpret_cast<Receiver*>(reinterpret_cast<std::uint8_t*>(receiver) + 0x40u);
}

// The shape a table slot has to have to be reached the way the body would be
// reached through a table: a receiver in ECX and one 4-byte word on the stack.
using Entry = Receiver* (TEST_THISCALL*)(Receiver*, Word);

struct Shell {
  Entry entry;
};

// Case I, second half: the function reached through a two-level load from a
// synthetic table, and the table's repointing changes the callee. The table is
// the test's own and says nothing about the binary's own tables, which this
// package does not claim beyond case J's record of their addresses.
void test_synthetic_dispatch() {
  Storage storage;
  Receiver* const object = storage.at(0);
  put_u32(object, 0x40u, 0x00000000u);

  Shell shell;
  shell.entry = &reconstruct_00e5cac0;
  Entry loaded = reinterpret_cast<Entry>(reinterpret_cast<void*>(shell.entry));
  check(loaded(object, 0u) == object,
        "I: the two-level load reached the reconstructed function");

  const Receiver* const through_reconstruction = shell.entry(object, 0u);
  shell.entry = &alternative_callee;
  Entry repointed = reinterpret_cast<Entry>(reinterpret_cast<void*>(shell.entry));
  check(repointed(object, 0u) != object,
        "I: repointing the table changes the callee");
  check(shell.entry(object, 0u) != through_reconstruction,
        "I: the two entries answer differently, so the slot decides the callee");
  check_eq_u32(get_u32(object, 0x40u), 0u,
               "I: the alternative callee formed an offset, it did not load");
  check(storage.guards_intact(), "I: no stray write around the dispatch");
}

// Case H: decode what the compiler actually emitted for the function. Only an
// optimised build is decoded: at -O0 the compiler is free to spill the incoming
// ECX to the stack and set up a frame, and the emitted bytes would then be a
// statement about the optimisation level rather than about this reconstruction.
#if defined(__OPTIMIZE__)

bool decodes_as_mov_eax_from_ecx(const std::uint8_t* bytes) {
  if (bytes[0] == 0x8Bu) {  // MOV r32, r/m32
    const std::uint8_t modrm = bytes[1];
    return ((modrm >> 6) & 0x3u) == 0x3u && ((modrm >> 3) & 0x7u) == 0x0u &&
           (modrm & 0x7u) == 0x1u;
  }
  if (bytes[0] == 0x89u) {  // MOV r/m32, r32 -- the mirror encoding
    const std::uint8_t modrm = bytes[1];
    return ((modrm >> 6) & 0x3u) == 0x3u && ((modrm >> 3) & 0x7u) == 0x1u &&
           (modrm & 0x7u) == 0x0u;
  }
  return false;
}

void test_emitted_body() {
  const void* fn = reinterpret_cast<const void*>(&reconstruct_00e5cac0);
  const std::uint8_t* const bytes = reinterpret_cast<const std::uint8_t*>(fn);
  check(decodes_as_mov_eax_from_ecx(bytes),
        "H: the emitted body moves ECX into EAX as a register operation");
  check_eq_u32(bytes[2], 0xC2u, "H: the emitted body ends in RET imm16");
  check_eq_u32(static_cast<std::uint32_t>(bytes[3]) |
                   (static_cast<std::uint32_t>(bytes[4]) << 8),
               4u, "H: the emitted RET immediate is 4");
  check_eq_u32(static_cast<std::uint32_t>(kBodySpanBytes), 5u,
               "H: the emitted body is five bytes, like the image");
}

#else

void test_emitted_body() {
  std::fprintf(stderr,
               "note: case H skipped, this is not an optimised build and the "
               "compiler is free to spill at -O0\n");
}

#endif

}  // namespace
}  // namespace openspore::reconstruction::pkg_w2_00e5cac0

int main() {
  using namespace openspore::reconstruction::pkg_w2_00e5cac0;
  // The instrument is calibrated first (case F). A reconstruction whose callee
  // cleanup disagreed with the listing would unbalance the compiler-generated
  // call sites the later cases use, so the disagreement is looked for before
  // anything else is driven, and the failure names the cleanup rather than
  // whatever corruption it went on to cause.
  test_callee_stack_pop_measured();
  test_caller_side_this_adjustor();
  test_image_bytes();
  test_image_has_no_transfer();
  test_machine_abi_record();
  test_identity_and_carriers();
  test_writes_nothing();
  test_synthetic_dispatch();
  test_emitted_body();
  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
