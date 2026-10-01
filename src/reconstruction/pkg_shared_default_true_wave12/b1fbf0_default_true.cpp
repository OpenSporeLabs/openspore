// PKG-SHARED-DEFAULT-TRUE-WAVE12 -- VA 0x00b1fbf0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The literal body, three bytes transcribed from the image:
//
//   00b1fbf0  b0 01   MOV AL,0x1
//   00b1fbf2  c3      RET
//
// See b1fbf0_default_true.hpp for the byte-level decode, for the determination
// that names __thiscall (rule V1-VFT, the only one of the record's six
// inferences that carries a calling-convention claim), for the R2 observation
// that the body never reads the register V1-VFT says carries the receiver, for
// the six caller-side sites where a live ECX is demonstrably in the register at
// the transfer, and for the explicit list of what is NOT claimed: no class, no
// table identity, no receiver type, no field offset in either direction, and not
// __fastcall, which the record keeps open as a second candidate.

#include "b1fbf0_default_true.hpp"

// The header spells the convention token once and leaves both macros defined,
// so the body below names one rather than repeating a spelling. Either branch
// carries the token `thiscall`, which is what the validator's convention
// resolution follows.
#if defined(_MSC_VER)
#define PKG_SHARED_DEFAULT_TRUE_WAVE12_THISCALL __thiscall
#define PKG_SHARED_DEFAULT_TRUE_WAVE12_NAKED_THISCALL __declspec(naked) __thiscall
#else
#define PKG_SHARED_DEFAULT_TRUE_WAVE12_THISCALL __attribute__((thiscall))
#define PKG_SHARED_DEFAULT_TRUE_WAVE12_NAKED_THISCALL __attribute__((naked, thiscall))
#endif

namespace openspore::reconstruction::pkg_shared_default_true_wave12 {

// The static_asserts are assertions, not documentation: each pins a fact the
// header states, so an edit to either side without the other fails the build
// instead of passing silently. They cost nothing at run time.
//
// They are at file scope rather than inside the function for one concrete
// reason, and it is a correctness one rather than a stylistic one: the machine
// listing for this target carries exactly ONE hexadecimal literal, 0x1, and a
// hexadecimal literal written in the target's own source span is a constant the
// listing cannot corroborate. The address arithmetic below is therefore checked
// against the header's own constants here and re-derived from literals written
// independently in the model test, rather than restated as a literal inside the
// span.
static_assert(kRetImmediateBytes == 0,
              "the RET at 0x00b1fbf2 carries no imm16, so the callee pops zero "
              "bytes and the caller owns all cleanup");
static_assert(kStackCleanupBytes == 0,
              "a bare RET accounts for no callee-side stack cleanup at all");
static_assert(kBodySpanBytes == 3,
              "MOV r8,imm8 is two bytes and a bare RET is one: three in total");
static_assert(kReturnWidthBytes == 1,
              "opcode B0 is MOV r8,imm8 with its register field fixed at AL, "
              "so exactly one byte of the return register is written");
static_assert(kReceiverFieldOffsetClaimed == false,
              "the body contains no memory operand through any register, so no "
              "field offset is claimed in either direction");
static_assert(!kReceiverReadByBody,
              "rule R2 observed that ECX is never read; this transcription "
              "reads no register, which is the same statement");
static_assert(kReceiverDistinctOffsets == 0 && kReceiverDereferenceCount == 0,
              "the machine record enumerates no receiver displacement and "
              "observes no load or store through the receiver register");
static_assert(kVftableBase + 4u * static_cast<std::uint32_t>(kVftableSlotIndex) ==
                  0x013f5804u,
              "the table base and the slot index the record gives must name the "
              "address whose word the image was read back from");
static_assert(kVftableSlotWord == kTargetVa,
              "the word read back out of the image at that address is this "
              "target's own address, which is what the membership rests on");
static_assert(kBodyFirstByte == kTargetVa && kBodyLastByte == 0x00b1fbf2u,
              "the body span the header states must be the span the disassembly "
              "and the live read agree on");

// Placed first among this file's definitions on purpose: the validator binds a
// source span to 0x00b1fbf0 by the 8-hex VA token appearing in the function
// name, and it takes the FIRST such definition in the file.
extern "C" std::uint8_t PKG_SHARED_DEFAULT_TRUE_WAVE12_NAKED_THISCALL
re_00b1fbf0_shared_default_true(Receiver*) {
  // Two instructions, transcribed. There is nothing else to write, because
  // there is nothing else in the body: no callee, no global, no memory operand,
  // no stack word, no frame, no register read and no branch.
  //
  //   00b1fbf0  movb $0x1, %al    ; the byte 0x01 into AL, and only AL
  //   00b1fbf2  ret               ; no immediate: the callee pops nothing
  //
  // Byte fidelity: all three bytes are pinned against the binary's own bytes
  // (kTargetBytes in the header) by the model test, at every optimisation level
  // and under both compilers. There is no rel32 displacement, no register-move
  // spelling ambiguity and no alignment padding inside a three-byte body, so
  // there is nothing to allow for.
  //
  // One toolchain artifact is recognised and excluded, and it is named rather
  // than waved through: a default position-independent build MAY prepend a
  // ten-byte get_pc_thunk PC anchor (g++ -m32 -O0 prepends one to a naked
  // function; clang++ -m32 emits none at any level). The anchor is recognised by
  // its exact opcode pair -- E8 with a rel32 displacement, then opcode 05 -- and
  // the three target bytes are then required immediately after it. That anchor
  // is not part of the target's body, and a toolchain that emitted some other
  // form of anchor would fail the model test rather than pass it.
  __asm__("movb $0x1, %al\n\t"  // 00b1fbf0  B0 01
          "ret\n\t");            // 00b1fbf2  C3
}

}  // namespace openspore::reconstruction::pkg_shared_default_true_wave12
