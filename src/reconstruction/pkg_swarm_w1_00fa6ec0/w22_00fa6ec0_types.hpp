// PKG-SWARM-W1-00FA6EC0 -- VA 0x00fa6ec0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for the vtable method at 0x00fa6ec0
// (FUN_00fa6ec0 in the image; no SDK name, no class name -- see the sidecar).
//
// HONESTY NOTE ON WHERE EVERY OFFSET IN THIS HEADER COMES FROM, because the split
// is the whole point of writing it down:
//
//  A. Displacements this body shows itself, in its own 40-instruction listing.
//     The machine-derived receiver record enumerates exactly five, and the body
//     reads and writes exactly those five:
//       0x00fa6ec4  MOV EBX,dword ptr [ESI + 0x770]
//       0x00fa6ecb  MOV EDI,dword ptr [ESI + 0x774]
//       0x00fa6ef2  ADD dword ptr [ESI + 0x774],EAX
//       0x00fa6ef8  MOV EBX,dword ptr [ESI + 0x784]
//       0x00fa6efe  MOV EDI,dword ptr [ESI + 0x788]
//       0x00fa6f25  ADD dword ptr [ESI + 0x788],ECX
//       0x00fa6f2b  INC dword ptr [ESI + 0x814]
//     receiver.offsets = [1904, 1908, 1924, 1928, 2068] = 0x770, 0x774, 0x784,
//     0x788, 0x814, register ECX, shape R-ALIAS, written_through 3. The record
//     carries bounds_only: it says where the body was seen reaching and not which
//     member is which, so NO member of the receiver is named anywhere below.
//
//  B. Sub-layouts this body does NOT show, read off OTHER listings in the same
//     image, each re-read for this package:
//
//     B1. The three-word vector header (first / last / capacity). Two sibling
//         methods of the SAME vtable fix all three displacements, and they are
//         not inferred from this body:
//           - 0x00fa7220, slot +0x64 of the same table, forms LEA ESI,[EDI+0x798]
//             (0x00fa72ef) as the vector's address, then reads
//               0x00fa730a  MOV EAX,dword ptr [ESI]        -> first   (offset +0x00)
//               0x00fa730c  MOV EDX,dword ptr [ESI + 0x4]  -> last    (offset +0x04)
//               0x00fa733c  MOV ECX,dword ptr [ESI + 0x4]  (again, the same last)
//               0x00fa733f  CMP ECX,dword ptr [ESI + 0x8]  -> capacity(offset +0x08)
//             and shrinks the vector with 0x00fa7324
//               ADD dword ptr [ESI + 0x4],0xffffff54  (last -= 0xAC).
//           - 0x00fa5040, slot +0x58 of the same table, indexes elements from
//             [EBP+0x784] (0x00fa5074, 0x00fa50b0, 0x00fa52c8) and walks the last
//             word [EBP+0x788] as the loop bound (0x00fa51fb, 0x00fa53f0), and
//             ends with 0x00fa541b ADD dword ptr [EAX + 0x774],0xffffff54.
//
//     B2. That the two 4-byte words THIS body pairs are (first, last) of such a
//         header and not (last, first) of a mirrored one. 0x00fa5040 settles it
//         for the 0x784/0x788 pair and the argument is identical for the
//         0x770/0x774 pair: it takes an element index, does
//           0x00fa53e4  IMUL ESI,ESI,0xac
//           0x00fa53ea  ADD ESI,dword ptr [EBP + 0x770]
//           0x00fa53f0  MOV EDI,dword ptr [EAX + 0x774]
//           0x00fa53f8  LEA ESI,[EBP + 0xac]
//           0x00fa53fe  CMP ESI,EDI
//           0x00fa5400  JNC 0x00fa5417
//         i.e. it computes (last - first) element-sized steps by ADDING to the
//         word at +0x770 and COMPARING against the word at +0x774. A word that
//         can be stepped forward from and a word that terminates a forward walk
//         are the first and the last of a forward range, in that order.
//
//     B3. The 0x14-byte stride between successive vector headers: 0x00fa5040
//         steps four sub-ranges of its own with ADD EBX,0x14 (0x00fa51db) and
//         CMP EAX,0x4 (0x00fa51de), and the three headers the same table's
//         methods reach are at receiver+0x770, +0x784 and +0x798 -- 0x14 apart.
//         The 0x14 stride therefore holds a 12-byte header plus four bytes no
//         listing in this set explains, which is why the header below is
//         declared 0x14 bytes with its last four left opaque rather than
//         packed to 0x0c.
//
//     B4. The 0xAC element, from the body of the single direct callee
//         (0x00f9f770 calls 0x00f9f620, whose own 68-instruction listing copies
//         the destination from the source field by field):
//           - 0x00f9f629  CALL 0x00537dc0  over 0x00..0x37 (this body never sees
//             what it writes, so the 0x38-byte head stays opaque);
//           - twenty-four FLD/FSTP float pairs at +0x38 .. +0x94 inclusive, i.e.
//             0x38, 0x3c, 0x40, ... 0x94 -- 24 floats, 0x60 bytes;
//           - five dword copies at +0x98, +0x9c, +0xa0, +0xa4, +0xa8.
//         0x38 + 0x60 + 0x14 == 0xAC, and 0xAC is the stride both this body and
//         0x00f9f770 step by (0x00fa6eec / 0x00fa53e4), so the element size and
//         the copy's own footprint agree exactly.
//         The word at +0xA8 is additionally compared, as a dword, against a
//         32-bit argument in 0x00fa5040 (0x00fa5080 CMP dword ptr [ECX],EDI with
//         ECX = element + 0xA8) and in 0x00fa7220 -- so it is a 4-byte value
//         something matches elements by. Nothing here says what it identifies.
//         The four floats at +0x38, +0x3C, +0x40, +0x44 are read back with
//         COMISS/MOVSS in 0x00fa5040 (0x00fa52d6, 0x00fa52e1, 0x00fa52ed,
//         0x00fa52f9), which independently confirms the float type of the run
//         that starts at +0x38.
//
//  C. NOT established by anything, and therefore absent: the name of the class,
//     the name of the method, what the 0x814 counter counts, what the 0xAC
//     element's +0xA8 word names, and the MEANING of the value this body leaves
//     in EAX. The single data reference to this body in the whole image is from
//     the address that holds its pointer inside the table at 0x01490be8 (this
//     body at that table's slot +0x60, 0x01490be8 + 0x60 = 0x01490c48, read off
//     the table's own bytes), so nothing CALLS this body in the image and no
//     caller ever reads what it returns. That the EAX bits are fixed and that
//     their meaning is not is the honest split, and it is what the model does.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00fa6ec0 requires an x86-32 target"
#endif

// The two conventions below are spelled per toolchain, because GCC rejects the
// bare MSVC keywords outright and the x86-32 attribute form is the portable
// spelling. Both are machine facts, not preferences:
//
//   PKG_SWARM_W1_00FA6EC0_THISCALL  this body. The receiver arrives in ECX
//     (0x00fa6ec2 MOV ESI,ECX and every one of the seven receiver accesses above
//     then goes through that alias), the body's only stack traffic is the
//     argument words of the two calls it makes, and its terminator at
//     0x00fa6f37 is a single byte C3 -- RET with no immediate. Nothing in the
//     listing reads an ordinary argument slot: entry_ESP+4 and entry_ESP+8 are
//     never touched, so the body consumes no stack argument and leaves nothing
//     for the caller to clean. (That the body reads no argument slot is also why
//     __fastcall, which the decompiler guessed and which abi_derived lists as a
//     candidate, cannot be REFUTED from argument passing alone; see the
//     unresolved_questions in the sidecar.)
//
//   PKG_SWARM_W1_00FA6EC0_CDECL  0x00f9f770, the one direct callee. Its own
//     terminator at 0x00f9f7a0 and 0x00f9f7a7 is `RET` with no immediate
//     (5D 5B C3 and 5B C3), and this body drops all six argument words itself
//     with 0x00fa6f31 ADD ESP,0x18. The callee owns nothing on the stack.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_00FA6EC0_THISCALL __thiscall
#define PKG_SWARM_W1_00FA6EC0_CDECL __cdecl
#else
#define PKG_SWARM_W1_00FA6EC0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_00FA6EC0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00fa6ec0 {

using Word = std::uint32_t;

// The 0xAC-byte element the two vector headers index. See B4 above for the
// instruction each line comes from. Nothing here is named for what it is: the
// head is opaque because the callee hands it to another function, and the word
// at +0xA8 is a 4-byte value something matches elements by and nothing says
// what.
struct Element {
  std::array<std::uint8_t, 0x38> opaque_00_37;  // 0x00..0x37, copied by the callee's own first call
  std::array<float, 24> field_38_94;            // 0x38..0x97, twenty-four FLD/FSTP floats
  std::array<Word, 4> field_98_a4;              // 0x98..0xa7, four dword copies
  Word field_a8;                                // 0xa8, the 4-byte value elements are matched on
};
static_assert(sizeof(Element) == 0xac, "0x00f9f620 copies 0x00..0xab and nothing past it");
static_assert(offsetof(Element, field_38_94) == 0x38, "float run starts at 0x38");
static_assert(offsetof(Element, field_98_a4) == 0x98, "dword run starts at 0x98");
static_assert(offsetof(Element, field_a8) == 0xa8, "the matched word sits at 0xa8");
static_assert(offsetof(Element, field_a8) + sizeof(Word) == 0xac, "the element ends the stride exactly");

// The three-word vector header embedded in the receiver, at receiver+0x770 and
// receiver+0x784 (and, from the sibling methods, at +0x798). Declared 0x14 bytes
// because that is the stride the class's own methods step by (B3); the last four
// bytes are left opaque because no listing in this set explains them.
struct ElementVector {
  Element* field_00;                             // first; stepped forward from by 0x00fa5040
  Element* field_04;                             // last; terminates the forward walk of 0x00fa5040
  Element* field_08;                             // capacity; the word 0x00fa733f compares last against
  std::array<std::uint8_t, 8> opaque_0c_13;     // 0x0c..0x13, unexplained by any listing here
};
static_assert(sizeof(ElementVector) == 0x14, "0x14 is the stride between successive headers");
static_assert(offsetof(ElementVector, field_08) == 0x8, "capacity offset");
static_assert(offsetof(ElementVector, opaque_0c_13) == 0xc, "the unexplained tail starts at 0x0c");

// The receiver. NO member of it is named, and none can be: the machine-derived
// receiver record is bounds_only and enumerates the five displacements above as
// places the body reached, with no statement about which member is which. The
// type is therefore a byte run of the observed extent, and the five
// displacements are published below as values.
//
// The extent is 0x818 because +0x814 is the last word the body touches and the
// word is 4 bytes. That is a floor, not a claim about the object's real size:
// 0x00fa7220 and 0x00fa5040 write the words at +0x818 and read +0x218..+0x268
// of the same receiver, so the class is larger than this model draws it and the
// bytes this body never looks at are not modelled.
struct alignas(4) Owner {
  std::array<std::uint8_t, 0x818> opaque_00{};  // 0x00..0x817
};

// The five receiver displacements, as values. 0x770/0x774 are the first and last
// words of the header at +0x770; 0x784/0x788 the first and last words of the
// header at +0x784; 0x814 the single word the body increments. "first" and
// "last" describe what the sibling listings do with the words (B1, B2), not a
// member name this body could have known.
constexpr std::size_t kFirstPairFirstDisplacement = 0x770;
constexpr std::size_t kFirstPairLastDisplacement = 0x774;
constexpr std::size_t kSecondPairFirstDisplacement = 0x784;
constexpr std::size_t kSecondPairLastDisplacement = 0x788;
constexpr std::size_t kCounterDisplacement = 0x814;

// The stride both this body and its callee step by. 0x00fa6eec and 0x00fa6f1f
// multiply the element count by it before storing it, 0x00fa6edb..0x00fa6eec
// divide the byte span by it, and 0x00fa6f25 stores the product. It is also
// exactly sizeof(Element), which is what ties the two together.
constexpr std::size_t kElementStride = 0xac;

// The multiplier the body loads twice, at 0x00fa6edb and 0x00fa6f0e, as a bit
// pattern. Read as a signed 32-bit integer it is -799063683, and 0x2FA0BE83 =
// 799063683 is floor(2^37 / 172) + 1 -- the constant the compiler uses for a
// SIGNED division by 0xAC. The multiplication at 0x00fa6ee0 / 0x00fa6f13 is the
// signed one-operand IMUL (F7 EF), so the multiplier enters the product signed,
// and the two correction instructions that follow (SAR EDX,0x5 then
// SHR 0x1f / ADD) turn the resulting negative floor into a truncation toward
// zero. The consequence -- that a positive span yields a NEGATIVE adjustment --
// is the one thing a reconstruction that writes a plain `span / 0xAC` gets
// backwards, and the model test drives spans that separate the two.
constexpr Word kQuotientMagic = 0xd05f417d;

// The only way the body under reconstruction touches any of the above: a 4-byte
// word or a pointer at a stated displacement. A member access would assert an
// identity the bounds-only receiver record cannot corroborate, so the model
// reaches the receiver the way the machine does.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline Element** pointer_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Element**>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

static_assert(sizeof(Owner) == 0x818, "0x814 + 4 is the last byte this body writes on the receiver");
static_assert(kCounterDisplacement + sizeof(Word) == sizeof(Owner),
              "the counter word ends the modelled receiver");
static_assert(kElementStride == sizeof(Element), "the stride and the element size are the same number");

// -- the one direct callee ----------------------------------------------------
// Declared here, defined nowhere in the reconstruction: the package's own model
// test defines it as an observer. The signature is fixed by the callee's own
// 24 instructions, not by its (failed) decompilation:
//
//   0x00f9f770  PUSH EBX
//   0x00f9f771  MOV EBX,[ESP + 0xc]      arg2
//   0x00f9f775  PUSH ESI
//   0x00f9f776  MOV ESI,[ESP + 0xc]      arg1
//   0x00f9f77a  CMP ESI,EBX              arg1 == arg2 ?
//   0x00f9f77c  JZ 0x00f9f7a1             -> MOV EAX,[ESP+0x14] (arg2); return
//   0x00f9f77e  PUSH EDI
//   0x00f9f77f  MOV EDI,[ESP + 0x18]     arg3
//   loop:
//   0x00f9f783  PUSH ESI
//   0x00f9f784  MOV ECX,EDI              destination in the hidden receiver
//   0x00f9f786  CALL 0x00f9f620           element assign, source on the stack
//   0x00f9f78b  ADD ESI,0xac
//   0x00f9f791  ADD EDI,0xac
//   0x00f9f797  CMP ESI,EBX
//   0x00f9f799  JNZ loop
//   0x00f9f79b  MOV EAX,EDI              return the destination end
//
// So the three arguments are (source_first, source_last, destination), the loop
// copies FORWARD while source_first != source_last, the element step is 0xAC, the
// empty-range exit returns arg2 and the loop exit returns the destination end.
// Both return values are uninteresting to this body, which overwrites EAX at
// 0x00fa6edb and 0x00fa6f0e with its own immediate and never reads either.
extern "C" Element* PKG_SWARM_W1_00FA6EC0_CDECL element_range_move_00f9f770(
    Element* source_first, Element* source_last, Element* destination);

// The method under reconstruction.
//
// __thiscall, receiver in ECX, no ordinary argument at all (see the macro
// comment), terminator a bare RET at 0x00fa6f37. The return type is Word
// because the body's LAST write to EAX is 0x00fa6f13 IMUL EDI, whose low half is
// the low 32 bits of a 64-bit signed product -- so the bits are fixed by the
// listing and the model reproduces them exactly. What they MEAN is not fixed by
// anything: the only reference to this body in the image is its own pointer in
// the table at 0x01490be8, no code in the image calls it, and abi_derived
// records the return as unclassified_in_EAX with register_class
// aggregate_unknown. Word is therefore a statement about the width and the bit
// pattern, not about a value.
extern "C" Word PKG_SWARM_W1_00FA6EC0_THISCALL re_00fa6ec0(Owner* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00fa6ec0
