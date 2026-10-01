// PKG-SWARM-W1-0057E1D0 -- VA 0x0057e1d0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_0057e1d0 @ 0x0057e1d0, an x86-32
// __thiscall routine whose shape is a scalar deleting destructor.
//
// HONESTY NOTE ON WHERE EVERY OFFSET AND CONSTANT IN THIS HEADER COMES FROM,
// because the split matters to a reader:
//
//  * The four receiver displacements this body reaches -- 0x00, 0x04, 0x0c and
//    0x14 -- are read straight out of its own 23-instruction listing, and they
//    are the complete set the machine-derived receiver record enumerates
//    (receiver.offsets = [0, 4, 12, 20], register ECX, written_through 2). The
//    listing shows the two of them it writes (0x00 and 0x04) as bare `[ESI]`
//    and `[ESI + 0x4]`, and the two it reads as `[ESI + 0xc]` and
//    `[ESI + 0x14]`.
//      0057e1d3  MOV EAX,dword ptr [ESI + 0xc]      read, 4 bytes
//      0057e1d6  MOV ECX,dword ptr [ESI + 0x14]     read, 4 bytes
//      0057e1f5  MOV dword ptr [ESI + 0x4],0x13ef094  write, 4 bytes
//      0057e1fc  MOV dword ptr [ESI],0x13eb938     write, 4 bytes
//
//  * The receiver is modelled as an opaque 24-byte run and NO member is named,
//    even for the two words this body writes. The reason is not caution, it is
//    that the record is `bounds_only`: it says where the body was seen reaching
//    and not which member is which, so it can neither confirm nor refute a name.
//    Calling the word at +0x00 a "vtable pointer" would be a member story, and
//    the evidence that these two constants ARE dispatch-table addresses (see
//    below) is evidence about the CONSTANTS, not about a member layout. The
//    displacement constants below are the named form of the listing's own
//    operands, and nothing more.
//
//  * That said, the two stored constants are firmly identified as dispatch-table
//    (vtable) addresses, and this is stated here rather than guessed:
//      - 0x013ef094 sits immediately after the NUL of the UTF-16-ish string
//        " Editor" that ends at 0x013ef093, and its first five dwords are
//        0x0041d780, 0x0047d670, 0x00461290, 0x00472970, 0x00472a70 -- a run of
//        .text code addresses, read directly out of the image at 0x013ef094.
//      - 0x013eb938 is followed by 0x011e06d0, 0x011e06d0 and 0x00517400, and
//        0x011e06d0 is itself `FF 25 68 C4 3C 01` = `JMP DWORD PTR
//        [0x013cc468]`, an import thunk. Ghidra's own decompilation of this VA
//        renders the constant as `&PTR_purecall_013eb938`, which is its
//        PTR_<target>_<addr> naming rule and therefore independent agreement
//        that the dword at 0x013eb938 is a pointer to a function.
//      - each address carries a very large number of DATA references from
//        destructor-shaped sites: 741 for 0x013ef094 and 609 for 0x013eb938.
//        Two base-class dispatch tables shared by a deep hierarchy is exactly
//        that signature.
//    None of that fixes how many slots either table has, or which class either
//    belongs to. See unresolved_questions in the metadata sidecar.
//
//  * The two constants are NOT a guess about the object's class graph, and the
//    matching constructor is recorded only as corroboration of the LAYOUT: the
//    routine at 0x0057a6d0 (0x0057a6d0..0x0057a6ff, read directly from the
//    image) writes 0x013f585c to the receiver's +0x00, 0x013f5858 to its +0x04,
//    0x01667bac to its +0x0c and +0x10, and 0x01667bae to its +0x14. The two
//    words this body reads at +0x0c and +0x14 are therefore words the matching
//    constructor writes, and the object is at least 24 bytes.
//
//  * THE ADJUSTING THUNK. 0x0057a700 is `SUB ECX,0x4` and 0x0057a703 is
//    `JMP 0x0057e1d0` (bytes E9 C8 3A 00 00, read from the image), and that is
//    the ONLY caller edge the xref export records for this VA
//    (get_xrefs_to 0x0057e1d0 -> one reference, UNCONDITIONAL_CALL, from
//    0x0057a703). So the address a caller holds when it enters this body is FOUR
//    GREATER than the pointer this body receives in ECX. The two stores land at
//    (caller pointer - 4) and (caller pointer). Both 0x0057a700 and 0x0057e1d0
//    also appear as adjacent entries of the table at 0x013f57f8 -- 0x013f585c
//    holds 0x0057a700 and 0x013f5868 holds 0x0057e1d0, i.e. displacements +0x64
//    and +0x70 from the table's own start address -- and that table is what this
//    target's own record names (vtables: ["vtable:0x013f57f8"]). What the class
//    graph actually is, and which of the two is the adjusting entry, is not
//    settled by this body and is not claimed.
//
//  * Two of the four receiver words are read as VALUES and used AS A POINTER
//    without a second dereference: 0x0057e1e7 pushes EAX, and EAX is the dword
//    the body read at 0x0057e1d3. The model therefore reads a Word and converts
//    it to a pointer exactly once, and the model test plants decoys at the
//    neighbouring displacements (0x08 and 0x10) to refute a reconstruction that
//    reads one word too low or too high. The word at +0x0c is NOT the address of
//    the object and the word at +0x14 is NOT a count of objects; nothing in this
//    body says what either holds beyond "the difference of the two, rounded down
//    to an even number and compared against 2, decides whether the first is
//    released".

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-0057e1d0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC 16 rejects the
// bare MSVC keywords outright, so the x86-32 attribute form is the portable
// spelling and the keyword form is kept for MSVC. Both are asserted by machine
// facts, not chosen for convenience:
//
//   PKG_SW1_0057E1D0_THISCALL  the reconstructed body. Fixed by the receiver in
//     ECX (0x0057e1d1 `MOV ESI,ECX`, dereferenced at 0x0057e1d3 before any
//     definite write) together with `RET 0x4` at 0x0057e210 -- the callee pops
//     the four bytes of its one ordinary stack argument, which rules out cdecl.
//
//   PKG_SW1_0057E1D0_CDECL     0x00f47380, the only direct callee. Its terminator
//     is the single byte C3 (`RET`) with no immediate, read from the image at
//     0x00f47394, so it returns without touching ESP; both call sites drop their
//     own argument with `ADD ESP,0x4` (0x0057e1ed and 0x0057e20a).
//
// HONEST LIMIT ON BOTH: GCC's x86-32 port ACCEPTS but IGNORES `cdecl` and
// `thiscall` as function attributes, so a model test compiled with it cannot
// measure either convention and this package does not pretend to. Both facts are
// read off the original image's bytes, and the model test asserts only what a
// C++ translation can actually observe. See the sidecar's validation.not_verified.
#if defined(_MSC_VER)
#define PKG_SW1_0057E1D0_THISCALL __thiscall
#define PKG_SW1_0057E1D0_CDECL __cdecl
#else
#define PKG_SW1_0057E1D0_THISCALL __attribute__((thiscall))
#define PKG_SW1_0057E1D0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_0057e1d0 {

using Word = std::uint32_t;

// The receiver. An opaque run and nothing else: the four displacements this body
// reaches are carried by the constants below, and no member is declared, because
// the machine-derived receiver record is bounds_only and a name would be a claim
// it cannot adjudicate. 24 bytes is the size this body's own listing requires
// (0x0057e1d6 reads four bytes at +0x14) and it is also exactly the size the
// matching constructor at 0x0057a6d0 writes into (its last store is a dword at
// +0x14). Both numbers are written in decimal on purpose: the source span's
// hexadecimal literals are compared against the listing's, and the listing
// contains no 0x18.
struct alignas(4) Object {
  std::array<std::uint8_t, 24> opaque_00;  // 0x00..0x17
};
static_assert(sizeof(Object) == 24, "the +0x14 dword read ends the modelled receiver");

// The four receiver displacements, as values. Each names where a word lives and
// nothing about what it is for.
constexpr std::size_t kAtZero = 0;    // written at 0x0057e1fc
constexpr std::size_t kAtFour = 0x4;  // written at 0x0057e1f5
constexpr std::size_t kRunBegin = 0xc;
constexpr std::size_t kRunEnd = 0x14;

// The two constants the body STORES. Both are the address of a dispatch table;
// see the header comment for the evidence. They are written in the body with
// the listing's own spelling, so this block is the named form of them and the
// static assertions below tie the two together.
constexpr Word kStoredAtZero = 0x13eb938;
constexpr Word kStoredAtFour = 0x13ef094;

// The arithmetic of the span test, exactly as the machine spells it:
//   0057e1d9  SUB ECX,EAX          ECX = [ESI+0x14] - [ESI+0xc]
//   0057e1db  AND ECX,0xfffffffe   clear the low bit
//   0057e1de  CMP ECX,0x2
//   0057e1e1  JLE 0x0057e1f0       SIGNED less-or-equal
constexpr Word kSpanRoundDownMask = 0xfffffffe;
constexpr Word kSpanThreshold = 0x2;

// The single ordinary stack argument, tested bit 0 only:
//   0057e1f0  TEST byte ptr [ESP + 0x8],0x1
constexpr std::uint8_t kDeletingFlagMask = 0x1;

// The only way the body under reconstruction touches the receiver: a word at a
// stated displacement. A member access would assert an identity the
// machine-derived record cannot corroborate.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                       displacement);
}

static_assert(kStoredAtFour == 0x13ef094 && kStoredAtZero == 0x13eb938,
              "the two stored dispatch-table addresses, as the listing spells them");
static_assert(kAtFour == 0x4 && kRunBegin == 0xc && kRunEnd == 0x14,
              "the three non-zero receiver displacements, as the listing spells them");
static_assert(kSpanRoundDownMask == 0xfffffffe && kSpanThreshold == 0x2,
              "the span test's mask and threshold, as the listing spells them");
static_assert(kRunEnd + sizeof(Word) == sizeof(Object),
              "the +0x14 dword read ends the modelled receiver");

// -- the one direct callee ----------------------------------------------------
// Declared here, and not defined here: the model test defines it as an observer.
// Its signature is fixed by its own bytes, not by its decompilation (which the
// bridge could not produce at all -- "Decompilation did not complete"):
//
//   00f47380  MOV EAX,dword ptr [ESP + 0x4]   the one stack word
//   00f47384  TEST EAX,EAX
//   00f47386  JZ 0x00f47394                  a null argument is a no-op
//   00f47388  MOV ECX,dword ptr [0x016c8b44]  a global service table
//   00f4738e  PUSH EAX
//   00f4738f  CALL 0x009276c0
//   00f47394  RET                            no immediate: cdecl
//
// The name says what this package USES it for, not what it is. That it releases
// a heap block is INFERRED, not observed: the shape (null-tolerant, one pointer,
// dispatching through a global at 0x016c8b44, and used by this body on both a
// sub-buffer and on the object itself) is the shape of a release operator, but
// no record in this repository identifies 0x00f47380 by name.
extern "C" void PKG_SW1_0057E1D0_CDECL heap_release_00f47380(void* pointer);

// FUN_0057e1d0 @ 0x0057e1d0.
//
// __thiscall, receiver in ECX, exactly one ordinary stack argument, `RET 0x4`.
// The terminator is machine-observed (0x0057e210 `C2 04 00`), the argument count
// is not a guess (0x0057e1f0 reads [ESP+0x8] with ESP at entry-4, which is
// entry+4, and `RET 0x4` then consumes the return address plus that one word),
// and Ghidra's own record agrees on the shape (parameters: [], parameter_count 0,
// hidden this in ECX, one observed stack slot of size 1 at entry_ESP+0x4).
//
// The return type is the receiver pointer. 0x0057e20d is `MOV EAX,ESI` -- a
// single unconditional store of the receiver alias into the return register,
// reached by falling through from the store pair on the no-free path and by the
// branch at 0x0057e202 landing on it after the free on the other -- and the body's
// own record calls the return `unclassified_in_EAX`, which describes the same
// shape (a value left in EAX) without classifying it. That the two vtable-store
// and release paths are precisely the MSVC scalar-deleting-destructor idiom is an
// INFERENCE from the shape, and no record names the class.
extern "C" Object* PKG_SW1_0057E1D0_THISCALL re_0057e1d0(
    Object* receiver, std::uint8_t deleting_flag);

}  // namespace openspore::reconstruction::pkg_swarm_w1_0057e1d0
