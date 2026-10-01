// PKG-SWARM-W1-00FA5580 -- VA 0x00fa5580
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00fa5580 @ 0x00fa5580, a method on the class
// whose table is at 0x01490be8 (this body occupies that table's slot +0x68; read
// out of the image, and the same place the xref from 0x01490c50 comes from). The
// table is recorded here and in the .cpp's file header and is deliberately NOT
// modelled: the body contains no indirect transfer and never reads a word at the
// receiver's +0x00.
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because the split
// matters to a reader:
//
//  * The two receiver displacements this body shows are 0x798 and 0x79c, read at
//    0x00fa5584/0x00fa558a, 0x00fa55a8, 0x00fa55cf and 0x00fa55f2 and written at
//    0x00fa55f2. They are also, exactly, the two displacements the machine-derived
//    receiver record enumerates (receiver.offsets = [1944, 1948], register ECX,
//    shape R-ALIAS, bounds_only true). An independent alias-aware scan of the
//    complete 46-instruction listing, which follows MOV ESI,ECX at 0x00fa5582,
//    reaches the same pair and no other. So the pair is fixed twice over.
//
//  * The 0xac element stride and the element's +0xa8 key word are NOT receiver
//    displacements and are not in that record. They are fixed by this body's own
//    instruction bytes, cited one by one in the .cpp: the stride by 0x00fa55bd
//    (ADD EDX,0xac), 0x00fa55d5 (IMUL ECX,ECX,0xac) and 0x00fa55f2
//    (ADD dword ptr [ESI+0x79c],0xffffff54, i.e. -0xac), and the key offset by
//    0x00fa55b2 (LEA EDX,[EDI+0xa8]) together with 0x00fa55b8 (CMP dword ptr
//    [EDX],EBX), the only place the 32-bit key word is ever compared. Nothing
//    else about an element is claimed: its other 0xa8 bytes are an opaque run.
//
//  * The ONE direct callee's shape (0x00f9f770) is read out of its own 0x38 bytes
//    in the same image, not out of any record. See the declaration at the bottom.
//
//  * No member of the receiver is named. The machine-derived record is bounds_only
//    and says where the body was seen reaching, not which member is which, so the
//    receiver is an opaque byte run and the .cpp reaches it by displacement.
//    Likewise nothing inside an element is named except the word at +0xa8, which
//    is named by its offset and not by what it is for.
//
//  * What the two receiver words ARE is not claimed here either. A sibling body
//    in the same class (0x00fa72e3, not this package's) reads the same pair as
//    begin/end of a 0xac-stride array and decrements the second by 0xac on removal,
//    and a second sibling (0x00fa9d78) increments it by (span/0xac)*0xac through
//    the same 0x00f9f770. That is corroboration from other listings, not evidence
//    from this body, so it is recorded here as context and nothing is named
//    because of it.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00fa5580 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC 16 rejects the bare
// MSVC keywords outright, so the x86-32 attribute form is the portable spelling and
// the keyword form is kept for MSVC. Both are asserted by machine facts:
//
//   PKG_SWARM_W1_00FA5580_THISCALL  this body. The receiver arrives in ECX and is
//     dereferenced at 0x00fa5584 before any definite write, and the body
//     terminates with `C2 04 00` (RET 0x4) on both of its return sites
//     (0x00fa55cc and 0x00fa5601), so the callee owns the one argument word.
//   PKG_SWARM_W1_00FA5580_CDECL     0x00f9f770, the only direct callee. Its last
//     three bytes are `5E C3` (POP ESI; RET) with no immediate -- it returns
//     without touching ESP -- and this body drops the three words itself at
//     0x00fa55ef with `ADD ESP,0xc`.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_00FA5580_THISCALL __thiscall
#define PKG_SWARM_W1_00FA5580_CDECL __cdecl
#else
#define PKG_SWARM_W1_00FA5580_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_00FA5580_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00fa5580 {

using Word = std::uint32_t;

// One element of the array the receiver embeds. 0xac bytes, with the single word
// this body compares at the element's own +0xa8.
//
// 0xa8 is 0x00fa55b2's displacement and 0xac is 0x00fa55bd's, 0x00fa55d5's and
// 0x00fa55f2's; the model test builds arrays of these and plants keys at +0xa8,
// and a decoy word at +0x00 of every element in every case. Nothing here says what
// the key word is, what the other 0xa8 bytes are, or why a key sits at 0xa8 of a
// 0xac record.
struct alignas(4) Element {
  std::array<std::uint8_t, 0xa8> field_00;  // 0x00..0xa7, opaque; never read here
  Word field_a8;                            // the one word this body compares
};
static_assert(sizeof(Element) == 0xac, "0xa8 + 4 is the last byte the body reads of an element");
static_assert(offsetof(Element, field_a8) == 0xa8, "key word offset inside an element");

// The receiver. This body reads two of its words and writes one, all three by
// displacement, and touches nothing else on it:
//
//   0x00fa5584  MOV EDX,dword ptr [ESI + 0x79c]     read
//   0x00fa558a  SUB EDX,dword ptr [ESI + 0x798]     read
//   0x00fa55a8  MOV EDI,dword ptr [ESI + 0x798]     read
//   0x00fa55cf  MOV EDX,dword ptr [ESI + 0x79c]     read  (the same word again)
//   0x00fa55f2  ADD dword ptr [ESI + 0x79c],-0xac   write
//
// So the model ends the receiver at 0x7a0, the byte after the last one written. No
// member is declared, and 0x00..0x797 and 0x7a0 onward are never touched by this
// body. The model test plants decoy words either side of both fields and asserts
// they do not move.
struct alignas(4) Receiver {
  std::array<std::uint8_t, 0x7a0> opaque_00{};
};

// The machine writes ONE byte of the return register on both exits -- XOR AL,AL at
// 0x00fa55c9 and MOV AL,0x1 at 0x00fa55fe -- so bits 8..31 of EAX at either return
// are whatever the last full-register write left there. This is the mask those three
// bytes are read through, and it is stated here rather than in the body because the
// body's hex literals are all supposed to be literals the 46-instruction listing
// itself contains, and the listing contains no 0xffffff00.
constexpr Word kReturnHighBytesMask = 0xffffff00u;

// The two receiver displacements, as values, and the element's own two.
constexpr std::size_t kReceiverLowerDisplacement = 0x798;  // read at 0x00fa558a / 0x00fa55a8
constexpr std::size_t kReceiverUpperDisplacement = 0x79c;  // read at 0x00fa5584 / 0x00fa55cf, written at 0x00fa55f2
constexpr std::size_t kElementKeyDisplacement = 0xa8;       // LEA EDX,[EDI+0xa8] at 0x00fa55b2
constexpr std::size_t kElementStride = 0xac;                // ADD EDX,0xac / IMUL ECX,ECX,0xac / ADD [..],-0xac

// -- the magic-multiply count --------------------------------------------------
// 0x00fa5590..0x00fa559f, six instructions, transcribed step for step:
//
//   00fa5590  MOV EAX,0x2fa0be83
//   00fa5595  IMUL EDX                 EDX:EAX = 0x2fa0be83 * (end - begin)
//   00fa5597  SAR EDX,0x5              the high word, shifted arithmetically
//   00fa559a  MOV EAX,EDX
//   00fa559c  SHR EAX,0x1f             0x00000000 or 0xffffffff
//   00fa559f  ADD EAX,EDX
//
// 0x2fa0be83 is 799063683 and 0x2fa0be83 * 0xac == 2^37 + 4 exactly, so the six
// instructions are the compiler's expansion of a division by 0xac with the standard
// signed-magic correction. Two facts about that expansion are worth stating because
// the model test asserts both and a plain C division asserts neither:
//
//   * For a NON-NEGATIVE span the sequence equals span / 0xac exactly. Verified
//     over every span in [0, 0x7fffffff] and at 0xac*k for k in [0, 12000]: zero
//     divergences. The accumulated error is 4/2^37 per element, i.e. at most
//     0.063 of an element at the largest 32-bit span.
//
//   * For a NEGATIVE span it does NOT equal the C result. floor((0x2fa0be83*span)/
//     2^37) - 1 is returned, and for a negative span that is one below the
//     truncating quotient, always: span -0xac gives -3 where C gives -1, span -0xac*
//     256 gives -258 where C gives -256. That is a property of these six
//     instructions, not an inference: ADD EAX,EDX with 0xffffffff in EAX moves a
//     negative quotient one further from zero. Nothing in this body prevents a
//     negative span -- the two words it subtracts are independent loads -- so the
//     model reproduces the six instructions rather than the division, and the
//     difference is observable in the caller-visible part of EAX (see the .cpp's
//     return-section note and the model test's case K).
constexpr Word kCountMagic = 0x2fa0be83u;
constexpr int kCountShift = 37;  // 32 (the IMUL high word) + 5 (SAR EDX,0x5)

inline std::int32_t element_count_from_span(std::int32_t span_bytes) {
  // Pinned rather than assumed: the shift below is a transliteration of SAR, and a
  // right shift of a negative signed value is implementation-defined before C++20.
  // Every toolchain this package is built with implements it as arithmetic; if one
  // ever did not, this would stop compiling rather than quietly compute a different
  // count than the machine.
  static_assert((static_cast<std::int64_t>(-64) >> 2) == -16,
                "a signed right shift must be arithmetic for SAR EDX,0x5 to be modelled");
  // 00fa5590 00fa5595 -- the 64-bit product in EDX:EAX.
  const std::int64_t product = static_cast<std::int64_t>(kCountMagic) *
                               static_cast<std::int64_t>(span_bytes);
  // 00fa5597 00fa559a -- SAR EDX,0x5, which on the 64-bit product is a shift by 37.
  const std::int32_t quotient = static_cast<std::int32_t>(product >> kCountShift);
  // 00fa559c 00fa559f -- SHR EAX,0x1f contributes 0 or 0xffffffff, i.e. 0 or -1.
  const std::uint32_t subtract = static_cast<std::uint32_t>(quotient) >> 31;
  return static_cast<std::int32_t>(static_cast<std::uint32_t>(quotient) - subtract);
}

// The only way the body under reconstruction touches the receiver or an element: a
// 32-bit word at a stated displacement. A member access would assert an identity
// the machine-derived record cannot corroborate, so none is used.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline Element* element_at(Element* base, std::int32_t index) {
  return reinterpret_cast<Element*>(reinterpret_cast<std::uintptr_t>(base) +
                                    static_cast<std::size_t>(index) * kElementStride);
}

static_assert(kReceiverUpperDisplacement + sizeof(Word) == sizeof(Receiver),
              "0x79c + 4 is the last byte the body writes on the receiver");
static_assert(kElementKeyDisplacement + sizeof(Word) == kElementStride,
              "the key word ends the 0xac element exactly");

// -- the one direct callee -----------------------------------------------------
// 0x00f9f770, called once, at 0x00fa55ea. Its shape is read out of its own bytes,
// 0x00f9f770..0x00f9f7a7 in the same image, because no record for that address
// exists in this repository:
//
//   00f9f770  PUSH EBX
//   00f9f771  MOV EBX,[ESP+0xc]     ESP=entry-4  -> entry+8  = the SECOND word
//   00f9f775  PUSH ESI
//   00f9f776  MOV ESI,[ESP+0xc]     ESP=entry-8  -> entry+4  = the FIRST word
//   00f9f77a  CMP ESI,EBX
//   00f9f77c  JE   0x00f9f7a1        first == second -> nothing to move
//   00f9f77e  PUSH EDI
//   00f9f77f  MOV EDI,[ESP+0x18]    ESP=entry-12 -> entry+0xc = the THIRD word
//   00f9f783  PUSH ESI              the first word
//   00f9f784  MOV ECX,EDI           the third word
//   00f9f786  CALL 0x00f9f620       -> copies the pushed word INTO its ECX receiver
//   00f9f78b  ADD ESI,0xac
//   00f9f791  ADD EDI,0xac
//   00f9f797  CMP ESI,EBX
//   00f9f799  JNE  0x00f9f783
//   00f9f79b  MOV EAX,EDI           returns the third word one stride past the last move
//   ...       POP EDI / POP ESI / POP EBX / RET        <- plain RET: cdecl
//   00f9f7a1  MOV EAX,[ESP+0x14]    ESP=entry-8 -> entry+0xc = the third word
//
// THE COPY DIRECTION IS FIXED BY 0x00f9f620, NOT BY THE ARGUMENT NAMES, and this is
// the one place a two-level mistake would be silent. 0x00f9f620 is __thiscall on
// its ECX receiver with one stack word, and its own body reads the STACK WORD and
// writes ECX: 0x00f9f622 `MOV EDI,[ESP+0xc]` takes the argument, 0x00f9f62e
// `FLD DWORD PTR [EDI+0x38]` / 0x00f9f631 `FSTP DWORD PTR [ESI+0x38]` loads from
// the argument and stores into ESI, which 0x00f9f627 `MOV ESI,ECX` set to the
// receiver. So in 0x00f9f770's loop the FIRST word is what gets copied FROM and the
// THIRD word is what gets copied INTO, and the loop's condition compares the first
// word against the second. Read the other way round the whole body would duplicate
// the element it removes instead of closing the gap, which is a claim about array
// contents that the callee's own 0x00f9f620 refutes.
//
// So the signature is (first_source, source_limit, first_destination): for as long
// as the read cursor has not reached source_limit, the element under the read cursor
// is copied into the element under the write cursor, both advancing by one 0xac
// stride, and the callee returns the write cursor one stride past its last use. The
// three words arrive in the order this body pushes them at 0x00fa55e7..0x00fa55e9,
// right to left:
//
//   first_source      = EAX at 0x00fa55dd (LEA EAX,[ECX+0xac]) -- the successor
//   source_limit      = EDX at 0x00fa55cf (the receiver's +0x79c), pushed second
//   first_destination = ECX at 0x00fa55db (ADD ECX,EDI)       -- the matched element
//
// and the effect is that every element after the match moves down one 0xac slot. The
// return value is this body's dead EAX and is modelled only as such.
extern "C" Element* PKG_SWARM_W1_00FA5580_CDECL array_shift_tail_down_00f9f770(
    Element* first_source, Element* source_limit, Element* first_destination);

// FUN_00fa5580 @ 0x00fa5580.
//
// __thiscall, receiver in ECX, exactly ONE ordinary stack argument, `RET 0x4` on
// both return sites (0x00fa55cc and 0x00fa5601). The argument is that word:
// 0x00fa55ae reads it with `MOV EBX,[ESP+0x10]` and the ESP in effect there is
// entry-12, so entry-12+0x10 is entry+4 -- the single argument slot -- and 0x00fa55b8
// compares it against each element's +0xa8 word as a full 32-bit value. Nothing
// reads a second slot, and the frame balances: three pushes in the prologue (EBX,
// ESI, EDI), the one cdecl call cleaned by the body's own `ADD ESP,0xc`, and the
// matching three pops in each epilogue before `RET 0x4` consumes the argument word.
// Ghidra's own record for this VA reports "undefined FUN_00fa5580(void)" with
// ghidra_parameter_count 0, which is its reading of an unclassified convention, not
// a claim that the body takes no argument.
//
// Return type is std::uint8_t, and the width is a machine fact rather than a
// choice: the two exits write AL only -- `XOR AL,AL` at 0x00fa55c9 and
// `MOV AL,0x1` at 0x00fa55fe -- and no instruction on any path writes the other
// three bytes of EAX. The record's own return vocabulary is
// return_semantics "integral_in_EAX" with return_register EAX and NO return_type
// field, so the C type is not recoverable from it: bool, char and uint8_t are all
// one byte and the machine fixes only the width. Of those, uint8_t is the one
// declared, because it asserts the width and nothing else. What the upper 24 bits
// of EAX hold at each return is stated in the .cpp and asserted by the model test
// through an EAX-sampling trampoline, because it is the strongest observable
// difference between this body and a reconstruction that returns a full word.
extern "C" std::uint8_t PKG_SWARM_W1_00FA5580_THISCALL re_00fa5580(Receiver* receiver,
                                                                  Word key);

// Model instrumentation, not a machine global and not part of the machine's
// observable surface: bits 8..31 of EAX at the last return, as composed by the model
// exactly as the machine composes them (see the RETURN WORD note in the .cpp).
//
// It is modelled because it is the only channel through which the six count
// instructions at 0x00fa5590..0x00fa559f can be observed at all: for a negative span
// the count differs from a C division by one, both are `<= 0`, both take the not-found
// arm, and the difference surfaces nowhere else. The C-visible return value is the
// low byte, which is all the declared 1-byte type promises, and the model test reads
// the two halves of the same word through this accessor.
std::uint32_t dead_return_word();

}  // namespace openspore::reconstruction::pkg_swarm_w1_00fa5580
