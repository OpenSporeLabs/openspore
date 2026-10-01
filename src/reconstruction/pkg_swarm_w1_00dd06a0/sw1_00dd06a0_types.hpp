// PKG-SWARM-W1-00DD06A0 -- VA 0x00dd06a0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for the scalar accessor at 0x00dd06a0, the only
// inbound reference to which is one word in a data table.
//
// THE LISTING THIS WAS WRITTEN AGAINST, RE-DERIVED FROM THE IMAGE
//
// objdump -D -b binary -m i386 -M intel --adjust-vma=0x00dd06a0 over the 0x60
// bytes of SPORE/SporeBin/SporeApp.exe at file offset 0x9cfaa0 (RVA 0x9d06a0)
// reproduces the 26 committed instructions at the same addresses, with the same
// lengths, targets and displacements:
//
//   dd06a0: 56                       push   esi
//   dd06a1: 8b f1                    mov    esi,ecx
//   dd06a3: 83 be 84 00 00 00 01     cmp    DWORD PTR [esi+0x84],0x1
//   dd06aa: 75 19                    jne    0xdd06c5
//   dd06ac: 8b 86 88 00 00 00        mov    eax,DWORD PTR [esi+0x88]
//   dd06b2: 83 e8 02                 sub    eax,0x2
//   dd06b5: f7 d8                    neg    eax
//   dd06b7: 1b c0                    sbb    eax,eax
//   dd06b9: 25 34 7f 57 ff           and    eax,0xff577f34
//   dd06be: 05 45 f0 ff ff           add    eax,0xfffff045
//   dd06c3: 5e                       pop    esi
//   dd06c4: c3                       ret
//   dd06c5: 81 be 88 00 00 00 79     cmp    DWORD PTR [esi+0x88],0xff576f79
//   dd06cc: 6f 57 ff
//   dd06cf: 74 1a                    je     0xdd06eb
//   dd06d1: e8 7a db d9 ff           call   0xb6e250
//   dd06d6: 84 c0                    test   al,al
//   dd06d8: 74 11                    je     0xdd06eb
//   dd06da: 8b 86 88 00 00 00        mov    eax,DWORD PTR [esi+0x88]
//   dd06e0: 50                       push   eax
//   dd06e1: e8 ea e9 d9 ff           call   0xb6f0d0
//   dd06e6: 83 c4 04                 add    esp,0x4
//   dd06e9: 5e                       pop    esi
//   dd06ea: c3                       ret
//   dd06eb: b8 79 6f 57 ff           mov    eax,0xff576f79
//   dd06f0: 5e                       pop    esi
//   dd06f1: c3                       ret
//
//   dd06f2 onwards is 0xcc (INT3 padding), so the 82-byte body is followed by
//   nothing: there is no fallthrough and no second entry inside the padding.
//   26 instructions, 82 bytes, 0x00dd06a0..0x00dd06f1 inclusive. Both numbers
//   agree with ghidra_function.size_bytes 82 and body_end 0x00dd06f1.
//
// EVERY OFFSET AND CONSTANT IN THIS HEADER, WITH THE INSTRUCTION THAT FIXES IT
//
//   receiver+0x84 (word, READ)  <- 0x00dd06a3 `CMP DWORD PTR [esi+0x84],0x1`
//                                 -- the only read of this displacement
//   receiver+0x88 (word, READ)  <- 0x00dd06ac `MOV EAX,[esi+0x88]`, and again
//                                 at 0x00dd06c5 `CMP ...[esi+0x88],0xff576f79`,
//                                 and again at 0x00dd06da `MOV EAX,[esi+0x88]`
//                                 -- three reads of the same word
//   immediate 0x01              <- 0x00dd06a3, the value the kind word is
//                                 compared against, and the only value it is
//                                 compared against
//   immediate 0x02              <- 0x00dd06b2 `SUB EAX,0x2`
//   immediate 0xff577f34        <- 0x00dd06b9 `AND EAX,0xff577f34`
//   immediate 0xfffff045        <- 0x00dd06be `ADD EAX,0xfffff045` (= -0xfbb)
//   immediate 0xff576f79        <- 0x00dd06c5 `CMP ...,0xff576f79` AND
//                                 0x00dd06eb `MOV EAX,0xff576f79`
//   immediate 0x04              <- 0x00dd06e6 `ADD ESP,0x4`
//
// Those two receiver displacements ARE the complete set the machine-derived
// receiver record enumerates: abi_derived.receiver is
// {register ECX, offsets [132, 136], max_offset 136, written_through 0,
// shape R-ALIAS}. Two reads, two displacements, and NOT ONE WRITE anywhere in
// the body: this function never modifies the object it is called on. The shape
// is R-ALIAS because the base register the listing's own memory operands name is
// ESI (0x00dd06a1 `MOV ESI,ECX`) while the record's base register is ECX, and
// ECX is never dereferenced directly again.
//
// WHY THE 0x84 ARM'S ARITHMETIC IS NOT A BRANCH
//
// 0x00dd06ac..0x00dd06be is five instructions with no conditional jump in it, and
// they compute one of exactly two words. Written out instruction by instruction,
// with f = the word at receiver+0x88:
//
//   0x00dd06ac  MOV  EAX,f
//   0x00dd06b2  SUB  EAX,0x2          EAX = f - 2
//   0x00dd06b5  NEG  EAX              EAX = -(f-2) = 2-f ; CF = (f != 2)
//   0x00dd06b7  SBB  EAX,EAX          EAX = -CF, i.e. 0 if f == 2, ~0 otherwise
//   0x00dd06b9  AND  EAX,0xff577f34   EAX = 0 if f == 2, 0xff577f34 otherwise
//   0x00dd06be  ADD  EAX,0xfffff045   EAX = 0xfffff045 if f == 2, else
//                                          0xff577f34 + 0xfffff045 = 0xff576f79
//
// 0x00dd06b7's carry is NEG's: NEG sets CF to 1 exactly when the operand it
// negated was non-zero, and the operand is f-2. So the arm's SELECTION is made
// on `f == 2`, bit-exactly. Its two results are 0xfffff045 and 0xff576f79, and
// the detail that is easy to get wrong is that 0x00dd06be's ADD is
// UNCONDITIONAL: SBB's 0 falls straight into it, so the f == 2 case returns the
// addend on its own, 0xfffff045, which is the -4027 Ghidra's decompilation
// renders as `- 0xfbb`. The arm produces no zero on any input. Both identities --
// 0xff577f34 + 0xfffff045 == 0xff576f79 and the f == 2 value being 0xfffff045 --
// are checked by static_asserts against kind_arm_arithmetic() below, which is
// what makes the table above a machine fact rather than an observation about
// behaviour.
//
// The interesting part, and the reason the non-zero selection was written as one
// masked constant plus one addend: the value the ADD produces on that arm is
// EXACTLY the value 0x00dd06eb materialises with `MOV EAX,0xff576f79`, and it is
// ALSO exactly the value 0x00dd06c5 compares against. One 32-bit word is
// therefore the single "nothing to report" answer of this function, reached from
// all three of its non-lookup exits, and is also the one input that short-
// circuits the lookup. This package asserts that the three paths produce the
// same word; it does NOT assert what that word means, because nothing in the
// listing says (see unresolved_questions item 3 in the sidecar).
//
// WHY NO MEMBER IS NAMED FOR THOSE TWO DISPLACEMENTS
//
// The receiver record is bounds_only: it states where the body was seen reaching
// and not which member is which. Two read-only dwords 4 bytes apart cannot
// distinguish a kind from a count, or an id from a pointer. So this header
// declares NO member for either, and the model reaches each one by displacement
// through word_at(). The constants ARE named, because a constant is a value and a
// value is what the instruction fixes.
//
// WHAT THE TWO DISPLACEMENTS ARE CALLED ELSEWHERE IN THE SAME TABLE
//
// This is corroboration, and it is deliberately kept out of the model's type.
// The only inbound reference to 0x00dd06a0 anywhere in the image is the single
// dword at 0x0147cbe4 (verified by searching the whole file for the little
// endian pattern a0 06 dd 00: exactly one hit, at file offset 0x107bfe4, which
// maps to VA 0x0147cbe4). The record carries the table address for this VA as
// 0x0147cbbc, so this body is the word at 0x0147cbbc + 0x28 of that table.
//
// Two neighbouring words of that same table are code addresses in this body's own
// neighbourhood, and their bodies were read for this package:
//
//   0x00dd0650  MOV EAX,[ECX+0x84] / DEC EAX / CMP EAX,0x4 / JA /
//               JMP DWORD PTR [EAX*0x4+0x00dd0680]
//   0x00dd0990  MOV ECX,[ECX+0x84] / ... / DEC ECX / CMP ECX,0x4 / JA /
//               JMP DWORD PTR [ECX*0x4+0x00dd09e0]
//
// Both switch on the SAME displacement this body reads at 0x00dd06a3, through the
// same `DEC / CMP 0x4 / JA` guard over a five-entry table, and 0x00dd0990 writes a
// three-dword out record (an id and two floats) per case. So the word at +0x84
// is a small discriminant with a handful of arms, on an object these three
// members share, and the word at +0x88 is a 32-bit value handed to a lookup.
// The model asserts the DISPLACEMENTS and the USES and stops there: naming the
// discriminant's enum, or the looked-up value's type, would be a story the
// listing does not carry.
//
// The same table's word at +0x30 is 0x00dd0700, whose whole body is
// `FLD DWORD PTR [ECX+0x90] / RET` -- a float at +0x90 of the same object. The
// constructor at 0x00dd0b50 (a different table, 0x0147c9f8, and therefore a
// different vtable address; class identity across the two is NOT asserted here)
// zeroes +0x84 and +0x88 and writes a float at +0x90. It is recorded because it
// shows both of this body's displacements are initialised, and nothing more is
// taken from it.
//
// ANOMALY, RECORDED RATHER THAN RESOLVED
//
// The word at 0x0147cbbc + 0x2c is 0xf0ff0300, which is below the image base and
// so is not a code address, in a run where every other word read is either a code
// address or another data address. That is an observation about the table, not
// about this body: the model declares no slot boundary and no slot index, and the
// sidecar carries the anomaly as an open question. What IS machine-checked is
// narrower and is what the model relies on: the body's own address appears
// exactly once in the image as a dword, and that word is at 0x0147cbe4.
//
// THE TWO CALLEES, ESTABLISHED FROM THEIR OWN BYTES
//
// 0x00b6e250, 27 bytes, 0x00b6e250..0x00b6e26a:
//   b6e250: 83 3d 78 79 68 01 00  cmp DWORD PTR ds:0x1687978,0x0
//   b6e257: 74 0f                 je  0xb6e268
//   b6e259: 83 3d cc b0 56 01 00  cmp DWORD PTR ds:0x156b0cc,0x0
//   b6e260: 74 06                 je  0xb6e268
//   b6e262: b8 01 00 00 00        mov eax,0x1
//   b6e267: c3                    ret
//   b6e268: 33 c0                 xor eax,eax
//   b6e26a: c3                    ret
// It reads no stack slot at all, so it takes zero arguments; both terminators are
// bare C3, so it owns no cleanup; and it returns 0 or 1 in EAX, and 0x00dd06d6
// tests AL, i.e. bit 0 of the low byte. The two data words it compares are
// recorded in this header as context and are referenced by nothing in the model.
//
// 0x00b6f0d0, 0x63 bytes, 0x00b6f0d0..0x00b6f132:
//   b6f0d0: 8b 44 24 04           mov eax,DWORD PTR [esp+0x4]   <- the argument
//   b6f0d4: 8d 4c 24 04           lea ecx,[esp+0x4]             <- its address
//   b6f0d8: 51                    push ecx
//   b6f0d9: b9 b8 b0 56 01        mov ecx,0x156b0b8
//   b6f0de: 89 44 24 08           mov DWORD PTR [esp+0x8],eax   <- value copy
//   b6f0e2: e8 59 fd ff ff        call 0xb6ee40
//   b6f0e7..b6f130: three float lanes of [EAX+0],[EAX+4],[EAX+8] scaled by
//                  ds:0x13f2100, truncated, and packed into EAX
//   b6f132: c3                    ret
// One four-byte stack argument, read by a dword MOV, and a bare C3 terminator,
// which is why 0x00dd06e6 has to drop the pushed word with ADD ESP,0x4 itself.
// Its EAX result is a packed 32-bit word built from three floats. The interior
// is the callee's business and is NOT modelled: the model only needs the
// signature, and only the value of the single argument is asserted.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00dd06a0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare
// MSVC keywords, so the x86-32 attribute form is the portable spelling and the
// keyword form is kept for MSVC. Both are fixed by machine facts:
//
//   PKG_SWARM_W1_00DD06A0_THISCALL  this body. The receiver arrives in ECX
//     (0x00dd06a1 `MOV ESI,ECX`, and 0x00dd06a3 dereferences it before any
//     definite write to ECX) and all three terminators are a bare `C3`
//     (0x00dd06c4, 0x00dd06ea, 0x00dd06f1) with no immediate, so the function
//     consumes no stack argument word and the caller owns all cleanup. That is
//     consistent with abi_derived.cleanup = {bytes 0, side caller} and with
//     abi_derived.conventions.calling_convention "__thiscall" (candidate set
//     [__thiscall, __fastcall], confidence INFERRED). Ghidra's own prototype
//     says __fastcall; see the ABI note in the .cpp.
//   PKG_SWARM_W1_00DD06A0_CDECL     both direct callees, 0x00b6e250 and
//     0x00b6f0d0. Each terminates in a bare `C3` (0x00b6e26a and 0x00b6f132)
//     with no immediate, so neither touches ESP, and 0x00dd06e6 drops the
//     argument word with ADD ESP,0x4.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_00DD06A0_THISCALL __thiscall
#define PKG_SWARM_W1_00DD06A0_CDECL __cdecl
#else
#define PKG_SWARM_W1_00DD06A0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_00DD06A0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00dd06a0 {

using Word = std::uint32_t;

// The receiver, as an opaque byte run.
//
// The body reads two dwords, at +0x84 and +0x88, and writes nothing at all, so
// 0x8c bytes is exactly the reach: the last byte read is receiver+0x8b. The
// class's constructor at 0x00dd0b50 writes a float at +0x90, so the real object
// is longer than this; 0x8c is a statement about THIS body's reach and not a
// claim about the object's size. Nothing is named, for the reason in the file
// header: the receiver record is bounds_only, and a read-only dword pair cannot
// say what any member is.
struct alignas(4) OpaqueSporepediaAsset {
  std::array<std::uint8_t, 0x8c> opaque_00;  // 0x00..0x8b
};

// The two receiver displacements, as values. 0x84 is the word 0x00dd06a3 compares
// against 1 and that two neighbours of this body in the same table switch on
// through a `DEC / CMP 0x4 / JA` five-way jump table; 0x88 is the word compared
// against 0xff576f79 and handed to the lookup. Neither description is a member
// name, because no member is declared.
constexpr std::size_t kKindDisplacement = 0x84;
constexpr std::size_t kIdDisplacement = 0x88;

// The single value the kind word is compared against, from 0x00dd06a3's
// immediate. Nothing else is compared against it: no other value routes into the
// 0x84 arm, and 0x00dd06aa is an unconditional-enough JNZ on that one compare.
constexpr Word kKindArmValue = 0x01u;

// 0x00dd06b2's immediate. The 0x84 arm subtracts it from the word at +0x88 and
// then asks whether the result is zero, by NEG's carry rather than by a compare.
constexpr Word kKindArmSubtractand = 0x02u;

// 0x00dd06b9's and 0x00dd06be's immediates, and the words they add up to.
//
// The ADD at 0x00dd06be is UNCONDITIONAL, which is the detail that decides this
// arm's whole value table: SBB's 0 falls through into it just as SBB's ~0 does.
// So the addend is not merely part of how the non-zero selection is formed --
// on its own it IS the value the id==2 case returns.
constexpr Word kKindArmSelectMask = 0xff577f34u;
constexpr Word kKindArmSelectAddend = 0xfffff045u;

// What the 0x84 arm returns when the id equals the subtractand: 0 + 0xfffff045,
// i.e. 0xfffff045, which as a signed 32-bit word is the -4027 the decompiler
// renders as `- 0xfbb`. It is NOT zero, and nothing in the arm produces a zero.
constexpr Word kKindArmSelectedValue = 0xfffff045u;

// The word 0x00dd06c5 compares against and 0x00dd06eb materialises, and the
// value the 0x84 arm returns for every id other than the subtractand. So this
// single 32-bit word is both this function's "nothing to report" answer and its
// "there is nothing to look up" input.
constexpr Word kAbsentValue = 0xff576f79u;

// 0x00dd06e6 `ADD ESP,0x4`: the caller-side drop of the one word pushed at
// 0x00dd06e0. It is recorded because it is instruction 22 of 26 and because the
// callee's bare C3 is what requires it. It is NOT observable through the model
// test, and the test says so instead of pretending otherwise: for a cdecl leaf
// callee, a callee-pops and a caller-pops return are the same machine behaviour.
// What the model test DOES measure is the other direction -- that this body
// itself consumes no stack word at all -- by sampling ESP around a raw call.
constexpr std::size_t kCallArgumentCleanupBytes = 0x04;

// -- context constants, read out of the image, referenced by no code ---------
// These are recorded so a reviewer can check the two claims in the file header
// against the bytes rather than taking them on trust. The model does not read
// them and the model test does not assert them.

// The two data words 0x00b6e250 compares against zero (0x00b6e250 and
// 0x00b6e259). Its own reading of them is: both must be non-zero, or it returns
// 0.
constexpr Word kProbeGlobalA = 0x01687978u;
constexpr Word kProbeGlobalB = 0x0156b0ccu;

// The data address the record carries for this VA, and the displacement of this
// body's own address within it. The single dword reference to 0x00dd06a0 in the
// whole image sits at 0x0147cbbc + 0x28. The word at +0x2c of that run is
// 0xf0ff0300, which is not a code address -- see the anomaly note in the file
// header and unresolved_questions item 2 in the sidecar. No slot boundary is
// declared anywhere in this package and no slot index is asserted.
constexpr Word kRecordedTableAddress = 0x0147cbbcu;
constexpr std::size_t kRecordedSlotDisplacement = 0x28;

// The only way this body touches the receiver: a dword at a stated displacement.
// A member access would assert an identity the machine-derived record cannot
// corroborate, so the model goes through this helper. The single-argument form
// takes an already-formed address, which is what `self + 0x84` produces, so the
// displacement each instruction fixes stays visible in the code.
inline Word* word_at(void* address) { return reinterpret_cast<Word*>(address); }

inline const Word* word_at(const void* address) {
  return reinterpret_cast<const Word*>(address);
}

static_assert(sizeof(OpaqueSporepediaAsset) == 0x8c,
              "0x88 + 4 is the last byte this body reads on the receiver");
static_assert(kIdDisplacement + sizeof(Word) == sizeof(OpaqueSporepediaAsset),
              "the last read word ends the modelled receiver exactly");
static_assert(kKindDisplacement + 4 == kIdDisplacement,
              "the +0x84 and +0x88 words are adjacent, not overlapping");
static_assert(kKindArmSelectMask + kKindArmSelectAddend == kAbsentValue,
              "0x00dd06b9's mask and 0x00dd06be's addend add up to exactly the word "
              "0x00dd06c5 compares against and 0x00dd06eb materialises");

// The 0x84 arm's five arithmetic instructions, transcribed one-for-one:
//
//   00dd06ac  MOV  EAX,[ESI+0x88]         EAX = id
//   00dd06b2  SUB  EAX,0x2                EAX = id - 2        (wrapping)
//   00dd06b5  NEG  EAX                    EAX = 2 - id ; CF = (id != 2)
//   00dd06b7  SBB  EAX,EAX                EAX = -CF, i.e. 0 or ~0
//   00dd06b9  AND  EAX,0xff577f34         0 or 0xff577f34
//   00dd06be  ADD  EAX,0xfffff045         0xfffff045 or 0xff576f79
//
// The last row is the one that is easy to get wrong: the ADD is unconditional,
// so the SBB's 0 does not stay 0. The arm's two results are 0xfffff045 (which
// is what Ghidra's decompilation renders as `- 0xfbb`, a signed -4027) and
// 0xff576f79 (which it renders as `-0xa89087`). The arm produces NO zero.
//
// The model in the .cpp states the arm as the two-valued expression these five
// instructions are equivalent to, because the intermediate EAX values are not
// observable: nothing between 0x00dd06ac and 0x00dd06be touches memory, calls
// anything, or reaches a callee, and EAX is overwritten by the next instruction
// on both arms. This helper exists so that equivalence is a compile-time fact
// rather than a claim in a comment -- the assertions below are the arm's value
// table, derived from the instructions and not observed from the model.
inline constexpr Word kind_arm_arithmetic(Word id) {
  const Word sub = id - 0x02u;             // 00dd06b2
  const Word neg = 0u - sub;               // 00dd06b5  (CF = (sub != 0))
  const Word sbb = (neg == 0u) ? 0u : 0xffffffffu;  // 00dd06b7  EAX = -CF
  return (sbb & 0xff577f34u) + 0xfffff045u;  // 00dd06b9, 00dd06be
}

static_assert(kind_arm_arithmetic(0x00000002u) == kKindArmSelectedValue,
              "NEG sets CF 0 for id 2, so SBB yields 0, and the UNCONDITIONAL "
              "ADD then leaves 0xfffff045 -- the arm does not return 0");
static_assert(kind_arm_arithmetic(0x00000003u) == kAbsentValue,
              "for any id other than 2 the arm returns exactly the word 0x00dd06eb "
              "materialises and 0x00dd06c5 compares against");
static_assert(kind_arm_arithmetic(0x00000001u) == kAbsentValue,
              "the subtractand is 2, not 1: 0x00dd06b2's immediate is 0x02");
static_assert(kind_arm_arithmetic(0x00000000u) == kAbsentValue,
              "the subtraction is unsigned-wrapping, so id 0 is not 2");
static_assert(kind_arm_arithmetic(0xfffffffeu) == kAbsentValue,
              "and wrapping does not make any other id into 2: (id-2)==0 in "
              "unsigned arithmetic holds only for id == 2");
static_assert(kind_arm_arithmetic(0x80000000u) == kAbsentValue,
              "the selection is an equality, not a signed or unsigned range test");
static_assert(kKindArmSelectedValue != 0u,
              "the arm's id==2 case is 0xfffff045, which is the addend alone");
static_assert(kKindArmSelectedValue + (0xff577f34u) == kAbsentValue,
              "the two results of the arm differ by exactly 0xff577f34, the mask");

// -- the two direct callees -------------------------------------------------
// Each is declared here, and none is defined here: the model test defines both as
// observers. Both signatures are fixed by the callee's own bytes, read from the
// image for this package (see the file header), not by any decompilation.

// 0x00b6e250, called at 0x00dd06d1 with NOTHING pushed. cdecl, zero arguments:
// the callee reads no stack slot, its two terminators are bare C3, and the
// instruction immediately before the call is the JZ that 0x00dd06d8 ends, not a
// PUSH. It returns 0 or 1 in EAX and this body tests AL (0x00dd06d6), i.e. bit
// 0 of the low byte, so the boolean is the whole of what the body observes.
//
// The model test's observer samples ESP at its own entry and the trampoline
// samples ESP immediately before the call, so "nothing was pushed for this call"
// is a MEASURED equality in the test and not only a claim here.
extern "C" bool PKG_SWARM_W1_00DD06A0_CDECL sporepedia_db_ready_probe_00b6e250();

// 0x00b6f0d0, called at 0x00dd06e1 with the single word pushed at 0x00dd06e0.
// cdecl, one four-byte stack argument: the callee reads it as a dword
// (0x00b6f0d0 `MOV EAX,[esp+0x4]`), it takes its own address at 0x00b6f0d4, and
// its terminator is a bare C3, which is what forces 0x00dd06e6's ADD ESP,0x4.
//
// The argument is a BY VALUE word, not a pointer: what 0x00dd06e0 pushes is the
// dword 0x00dd06da loaded, and the callee's first act is a dword load of that
// slot. The model test plants a decoy one level down and asserts the observer
// receives the word itself.
//
// The return type is a 32-bit word. 0x00b6f0d0 builds EAX from three scaled
// float lanes and returns it, and this body passes it straight through as its own
// return; the interior is the callee's and is not modelled.
extern "C" Word PKG_SWARM_W1_00DD06A0_CDECL sporepedia_lookup_packed_00b6f0d0(
    Word key);

// -- the body -----------------------------------------------------------------
//
// __thiscall, receiver in ECX, ZERO ordinary stack arguments, bare `RET` on all
// three exits (0x00dd06c4, 0x00dd06ea, 0x00dd06f1).
//
// The zero-argument claim is derived and not assumed. One linear walk of ESP
// through all 26 instructions: entry ESP is 0 in the walk; 0x00dd06a0's PUSH ESI
// makes it -4; 0x00dd06e0's PUSH EAX makes it -8; 0x00dd06e6's ADD ESP,0x4 takes
// it back to -4; and each of the three POP ESI instructions returns it to 0
// before its RET. The walk ends at 0 on all three paths, and no return site
// carries an immediate, so nothing is popped. That agrees with
// abi_derived.abi: stack_cleanup_bytes 0, side caller, stack_arguments absent.
//
// Return type is a signed 32-bit word. All three exits write EAX and nothing
// else: a 32-bit immediate at 0x00dd06eb, the arithmetic result at 0x00dd06be,
// and the lookup's own EAX at 0x00dd06e1, whose only subsequent instruction is
// ADD ESP,0x4, which cannot change it. The derived ABI record classifies that
// EAX as `aggregate_unknown` with return_semantics 'unclassified_in_EAX', which
// is a statement about its classifier rather than about the listing; the
// disagreement is recorded in the sidecar rather than papered over.
extern "C" std::int32_t PKG_SWARM_W1_00DD06A0_THISCALL re_00dd06a0(
    OpaqueSporepediaAsset* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00dd06a0
