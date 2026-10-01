// PKG-SW1-00A649A0 -- VA 0x00a649a0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for the 4-byte Sporepedia accessor at 0x00a649a0.
//
// THE COMPLETE BODY, re-read out of the image bytes for this package rather
// than taken on trust. GhidraMCP /read_memory at 0x00a649a0 returns
//
//   8b 41 6c c3 cc cc cc cc cc cc cc cc cc cc cc cc ...
//   ^^^^^^^^^^ 0x00a649a0..0x00a649a3, the whole 4-byte body
//                 then twelve 0xcc pad bytes
//
// and /disassemble_function at 0x00a649a0 agrees on exactly two instructions with
// body_end 0x00a649a3 and size 4:
//
//   00a649a0  8B 41 6C   MOV EAX,DWORD PTR [ECX+0x6C]   (3 bytes)
//   00a649a3  C3         RET                             (1 byte)
//
// So the span is 4 bytes, not 5 and not 8, and the trailing 0xcc run belongs to
// the inter-function padding that follows it: the next body starts at 0x00a649a8
// (its first bytes are 8B 49 70 = `MOV ECX,[ECX+0x70]`). Nothing in this package
// claims a byte of 0x00a649a4..0x00a649af.
//
// WHAT THE 3 BYTES FIX, spelled out because a 4-byte body has exactly one place
// to be wrong:
//   * 8B /r, ModRM = 0x41 -> mod = 01 (one-byte displacement follows), reg = 000
//     = EAX, r/m = 001 = ECX. The destination register is EAX and the only
//     addressed register is ECX.
//   * disp8 = 0x6C. 0x6C is 108 decimal, which is exactly the single entry of
//     the machine record's receiver.offsets ([108]). The displacement is a
//     non-negative one-byte constant, so the addressed field is inside the
//     receiver at +0x6c and never beyond +0x7c; no sign extension is possible.
//   * 0x8B is a 32-bit load of one dword. It does NOT set any flag, and it
//     performs exactly one memory read of exactly four bytes.
//   * C3 is RET with no immediate. There is no 0x00 byte after it, so the callee
//     pops nothing: this frame's stack cleanup is 0 bytes, and combined with the
//     absence of any argument read there are no stack arguments at all.
//
// HONESTY NOTE ON WHAT IS NOT CLAIMED HERE, and why:
//
//  * No name for the field. Nothing in these 4 bytes, in the 14 vtable runs the
//    index associates with this VA, or in the one caller (0x00a53d20, see
//    .cpp) says what the word at +0x6c means. The machine record types the
//    returned register as "pointer_like" (abi_derived.return_semantics
//    "pointer_like_in_EAX", confidence INFERRED) but that is a register-class
//    guess about the VALUE, not a dereference: the body never dereferences
//    anything it loaded, and modelling a pointee here would be inventing a
//    second level. So nothing inside the receiver is named at all: the run is
//    opaque, the word comes back through `word_at(self, kFieldDisplacement)` as
//    an unnamed 4-byte value, and the model test plants a decoy so that a
//    two-level read would be caught (case P).
//  * No class name and no SDK name. ghidra_function.sdk_name is null and this
//    binary has no MSVC RTTI (docs/AGENTS: class structure comes only from
//    vtable data and SDK structures), so the receiver is spelled Receiver.
//  * No vtable slot number. docs/analysis/vtables.json labels the run at
//    0x013ff648 "VTAB_013ff648_40slots" in namespace Sporepedia, and the dword
//    at 0x013ff6d0 is 0x00a649a0 (verified by /read_memory for this package),
//    i.e. 0x88 = 34 dwords past that head. Whether that is "slot 34" or "slot
//    33" depends on whether the head dword itself is counted as a slot, which
//    this target does not settle, so no slot number is declared anywhere in this
//    package. Only the raw byte offset is asserted.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00a649a0 requires an x86-32 target"
#endif

// The calling convention below is spelled per toolchain. GCC rejects the bare
// MSVC keywords outright, so the x86-32 attribute form is the portable spelling
// and the keyword form is kept for MSVC. The choice is a machine fact and not a
// convenience, and both halves of it are anchored in the image:
//
//   PKG_SW1_00A649A0_THISCALL  the receiver arrives in ECX and the callee pops
//     nothing. The ECX half is 0x00a649a0 itself: the body's one memory
//     instruction addresses [ECX+0x6c] and there is no other register, so the
//     pointer in ECX is the receiver. The zero-cleanup half is the terminator
//     C3 with no immediate. The direct call site agrees from the other side:
//     0x00a53d97 loads ECX from [ESI+0x9c], 0x00a53da5 calls 0x00a649a0, and the
//     very next instruction, 0x00a53daa, is FLD DOUBLE PTR [ESP+0x18] with no
//     ADD ESP,n between them -- so the caller pushed no argument and expects no
//     callee cleanup. For a zero-argument thiscall, "no immediate on the RET"
//     and "0 bytes of cleanup" are the same statement, which is why a bare RET
//     is compatible with either and __thiscall is the convention the pair
//     together fixes.
#if defined(_MSC_VER)
#define PKG_SW1_00A649A0_THISCALL __thiscall
#else
#define PKG_SW1_00A649A0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00a649a0 {

using Word = std::uint32_t;

// -- the one displacement this body states ---------------------------------
//
//   kFieldDisplacement  0x6c  0x00a649a0  MOV EAX,dword ptr [ECX + 0x6c]
//
// A NUMBER THE LISTING PRINTS, and the whole of what the machine fixes about
// the receiver. It is not a member. The machine-derived receiver record for this
// target is `bounds_only: true` (abi_derived.value.receiver) with `offsets [108]`
// and `max_offset 108`: that record says how far the body was seen reaching and
// nothing more, so it corroborates the DISPLACEMENT and cannot corroborate the
// identity of a word stored there. Naming a member at that offset would assert a
// layout and a role the evidence pack does not contain, so the receiver is an
// opaque byte run below and every access goes through the displacement-named
// accessor that follows it.
constexpr std::size_t kFieldDisplacement = 0x6cu;

// The receiver, as this body alone fixes it: an opaque byte run, and a name for
// nothing inside it.
//
// The run is 0xa4 bytes because that is the MODEL's own test affordance and not a
// claim about the real object: the model test plants decoy words at 0x60, 0x64,
// 0x68, 0x70, 0x74 and 0xa0 so that a reconstruction reading a neighbouring
// displacement, a neighbouring access size or the wrong pointer level is refuted
// rather than merely unimplemented (cases A, B, I, J, P). This body touches one
// word, at +0x6c, and nothing else in the run; the size of the surrounding class
// is not fixed by these 4 bytes and nothing here asserts how big the real one is.
struct Receiver {
  std::array<std::uint8_t, 0xa4> opaque_00_a3;
};
static_assert(sizeof(Receiver) == 0xa4,
              "the model test plants its last decoy dword at 0xa0..0xa3");
static_assert(kFieldDisplacement + sizeof(Word) <= sizeof(Receiver),
              "the disp8 of 0x00a649a0 addresses four bytes inside the run");
static_assert(sizeof(Word) == 4, "0x8B is a 32-bit load");

// The one read this body performs, written as a displacement into the run instead
// of as a member access.
//
// `word_at` takes the base as a POINTER because that is how the machine holds it:
// the receiver arrives in ECX and 0x00a649a0 dereferences that register directly,
// with no intermediate address computed and no second load. Handing the base back
// as a `Word` and reinterpreting it would let a reconstruction write a second,
// invented level of indirection, and case P is the decoy waiting for exactly that.
inline Word word_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<const std::uint8_t*>(base) + displacement);
}

// The machine image of the body, kept as data so the model test can check the
// reconstruction against the bytes rather than against a restatement of them.
// Index 0 is 0x00a649a0; the array is exactly 4 long, which is the whole span.
inline constexpr std::array<std::uint8_t, 4> kBodyBytes = {0x8Bu, 0x41u, 0x6Cu,
                                                           0xC3u};

namespace machine {

// Derived from kBodyBytes only. These are conveniences for the test and the
// comments; nothing in re_00a649a0() reads them, so no defect injected into the
// reconstruction can be masked by them.
constexpr std::size_t kEntryVa = 0x00a649a0u;
constexpr std::size_t kSpanBytes = kBodyBytes.size();          // 4
constexpr std::size_t kInstructionCount = 2u;                  // 8B.., C3
constexpr std::uint8_t kLoadOpcode = kBodyBytes[0];            // 0x8B
constexpr std::uint8_t kLoadModRm = kBodyBytes[1];             // 0x41
constexpr std::uint8_t kLoadDisplacement = kBodyBytes[2];     // 0x6C
constexpr std::uint8_t kTerminator = kBodyBytes[3];            // 0xC3
// ModRM 0x41: mod = 0b01 (disp8 present), reg = 0b000 (EAX), r/m = 0b001 (ECX).
constexpr std::uint8_t kModRmMod = static_cast<std::uint8_t>(kLoadModRm >> 6);
constexpr std::uint8_t kModRmReg = static_cast<std::uint8_t>((kLoadModRm >> 3) & 7u);
constexpr std::uint8_t kModRmRm = static_cast<std::uint8_t>(kLoadModRm & 7u);
// Operand-size and address-size prefixes are both 0x66, so 0x8B is dword/dword.
constexpr bool kIs32BitLoad = (kLoadOpcode == 0x8Bu) && (kModRmMod == 1u) &&
                              (kModRmReg == 0u) && (kModRmRm == 1u);
// A bare RET: C3, and there is no byte after it in the body, so the immediate
// that C2 would carry is 0 by absence rather than by a stored zero.
constexpr bool kIsBareRet = (kTerminator == 0xC3u) && (kSpanBytes == 4u);

}  // namespace machine

// No direct callees are declared, and that is a machine fact rather than an
// omission: abi_derived.callees is [], ghidra_function.callees is [], the
// listing's two instructions contain no E8 (call rel32), no FF /2 (call
// reg/mem), no 0F 1x (call through a memory operand) and no jump. The model test
// asserts the absence from the byte table itself (case H) so a defect that added
// a call to the reconstruction would be caught.

// The reconstruction. extern "C" so the symbol name is findable verbatim by the
// validator, and the 8-hex target VA is embedded in it.
extern "C" Word PKG_SW1_00A649A0_THISCALL re_00a649a0(Receiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00a649a0
