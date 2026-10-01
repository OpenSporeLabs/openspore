// PKG-SWARM-W1-010537B0 -- VA 0x010537b0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_010537b0 @ 0x010537b0.
//
// WHAT THIS BODY IS, IN THE WORDS THE MACHINE USES. Twelve instructions, 38 bytes,
// 0x010537b0..0x010537d5 inclusive:
//
//   010537b0  f6 44 24 04 01      TEST byte ptr [ESP + 0x4],0x1
//   010537b5  56                  PUSH ESI
//   010537b6  8b f1               MOV ESI,ECX
//   010537b8  c7 46 04 58 c4 3e 01 MOV dword ptr [ESI + 0x4],0x13ec458
//   010537bf  c7 06 38 b9 3e 01   MOV dword ptr [ESI],0x13eb938
//   010537c5  74 09               JZ 0x010537d0
//   010537c7  56                  PUSH ESI
//   010537c8  e8 b3 3b ef ff      CALL 0x00f47380
//   010537cd  83 c4 04            ADD ESP,0x4
//   010537d0  8b c6               MOV EAX,ESI
//   010537d2  5e                  POP ESI
//   010537d3  c2 04 00            RET 0x4
//
// The 38 bytes above were read out of the image for this package (file offset
// 0xc537b0 - 0x400000 + 0x400 = 0xc53bb0 in .text, whose VMA 0x401000 maps to file
// offset 0x400) and re-disassembled with objdump -b binary -m i386 -M intel. The
// committed 12-instruction Ghidra listing
// (reconstruction/evidence/010537b0/evidence.json, categories.disassembly) matches
// instruction for instruction at all twelve addresses, and the instruction lengths
// add up: 5+1+2+7+6+2+1+5+3+2+1+3 = 38. The two MOV-immediate stores are 7 and 6
// bytes (the opcode C7 /0 with a ModRM byte and a disp8, and with disp32, an
// immediate), the CALL's rel32 is 0xffef3bb3, and 0x010537c5 + 2 + 0x09 = 0x010537d0
// is where the JZ lands. Nothing in this package depends on a listing that was not
// re-derived from those bytes.
//
// HONESTY NOTE ON WHERE EVERY NAME IN THIS HEADER COMES FROM:
//
//  * No member of the receiver is named. The body writes two words at the object's
//    displacements 0x00 and 0x04 and touches no other byte of it, and the
//    machine-derived receiver record is exactly that: bounds_only true,
//    offsets [0, 4], distinct_offsets 2, max_offset 4, register ECX, shape R-ALIAS,
//    written_through 2, confidence INFERRED. It says where the body was seen
//    reaching and not what the words are for, so the receiver below is an opaque
//    0x08-byte run and every access in the .cpp is a displacement into it.
//
//  * The two words the body stores ARE table heads, and that is a machine fact read
//    out of .rdata, not a naming decision. Both immediates lie inside .rdata (VMA
//    0x013cc000, size 0x0013f5ae):
//      - 0x013eb938, read from the image, is 0x011e06d0, 0x011e06d0 and then
//        0x00517400 and character data -- i.e. a two-entry table whose entries are
//        both the same import thunk, and that thunk is
//        `FF 25 68 c4 3c 01  jmp DWORD PTR ds:0x13cc468`, a jump through the import
//        address table slot at 0x013cc468. That slot resolves, by reading the PE
//        import directory, to MSVCR90.dll!_purecall (hint 811). Ghidra's own
//        decompilation of this VA spells the constant `&PTR_purecall_013eb938`, which
//        is the same observation with a different vocabulary.
//      - 0x013ec458, read from the image, is 0x0055bf80, 0x005454f0, 0x00453540,
//        0x004535b0, 0x00000000 -- a table whose leading entry is 0x0055bf80, and
//        0x0055bf80 is a body of the same shape as the one under reconstruction:
//        `mov [ebp-4],ecx / mov eax,[ebp-4] / mov [eax],0x13ec458 / mov ecx,[ebp+8] /
//        and ecx,1 / je +0xc / push edx / call 0x00f47380 / ... / ret`.
//    Two independent bodies therefore install table heads into objects at the
//    object's displacement zero, which is what makes calling these two constants
//    table heads a fact rather than a guess. The body under reconstruction is the
//    same pattern with TWO such words, at +0x00 and +0x04.
//
//  * The object has a sub-object at +0x04, and that is fixed by a body outside this
//    target: 0x01053780 is 8 bytes, `83 e9 04  sub ecx,0x4` followed by
//    `e9 28 00 00 00  jmp 0x010537b0` -- a thiscall adjustor thunk that biases the
//    receiver down by four bytes and tail-jumps into this body. It is the xref the
//    target's own export records at 0x01053783 (the immediate of that JMP). So a
//    caller may legitimately hand this body a pointer four bytes above the object's
//    real base, and the body itself does NOT re-apply the bias: 0x010537b6 copies
//    ECX into ESI unchanged and both stores are through ESI. The model test drives
//    exactly that case.
//
//  * The class this destructor belongs to is NOT established here, and no name is
//    invented for it. See the sidecar's unresolved_questions for what was checked.
//
//  * The size of the receiver is 0x08 because 0x00 and 0x04 are the last byte the
//    body writes and the adjustor shows a sub-object at +0x04. It is NOT 0x0c: a
//    neighbouring body at 0x01053740 creates a three-word object
//    (`mov [eax],0x149b2e0 / mov [eax+4],0x149bad8 / mov [eax+8],0x0`, allocating
//    0xc bytes via the call at 0x0105374f to 0x00f473a0), but that is a DIFFERENT
//    function's factory for a MORE DERIVED class, and nothing in the 12 instructions
//    under reconstruction shows that object. The base sub-object this body receives
//    and rewrites needs only the two words it rewrites.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-010537b0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare MSVC
// keywords, so the x86-32 attribute form is the portable spelling and the keyword form
// is kept for MSVC. Both are asserted by machine facts, not chosen for convenience:
//
//   PKG_SWARM_W1_010537B0_THISCALL  the body under reconstruction and its adjustor
//     thunk 0x01053780. Both take their receiver in ECX and both end in `C2 04 00`
//     (RET 0x4) -- the bytes read directly out of the image -- so the callee owns the
//     cleanup of the one stack word, which rules out cdecl and fastcall. The
//     machine-derived record agrees: calling_convention __thiscall, stack_cleanup_bytes
//     4, stack_cleanup_owner callee, ret_form "RET 0x4", hidden_this true,
//     hidden_this_register ECX. The 0x01053780 bytes make it a second witness: a
//     thiscall function may adjust ECX and tail-jump, and only a callee that cleans
//     its own stack allows a JMP to replace a RET.
//   PKG_SWARM_W1_010537B0_CDECL  0x00f47380, the one direct callee. Its own body ends
//     `8b 44 24 04 / 85 c0 / 74 0c / 8b 0d 44 8b 6c 01 / 50 / e8 2c 03 9e ff / c3` --
//     a load of its single stack word, a null test, an indirect call through the
//     .data word 0x016c8b44, and a bare `C3` with no immediate, i.e. it returns
//     without touching ESP. 0x010537cd `ADD ESP,0x4` is therefore the CALLER's
//     cleanup, which is the other half of the cdecl pairing.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_010537B0_THISCALL __thiscall
#define PKG_SWARM_W1_010537B0_CDECL __cdecl
#else
#define PKG_SWARM_W1_010537B0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_010537B0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_010537b0 {

using Word = std::uint32_t;

// The object this destructor runs on. Two words, an opaque run, and no member names:
// see the honesty note above for why the two displacements are stated as offsets and
// why nothing is named for them.
struct alignas(4) TableWordPair {
  std::array<std::uint8_t, 0x08> opaque_00{};  // 0x00..0x07; the body writes 0x00..0x07
};
static_assert(sizeof(TableWordPair) == 0x08,
              "0x04 + 4 is the last byte the body writes on the receiver");
static_assert(alignof(TableWordPair) == 4, "the body writes two 4-byte words at +0x00 and +0x04");

// The two receiver displacements this body writes through, as values. 0x00 is the
// word 0x010537bf overwrites and 0x04 the word 0x010537b8 overwrites; together they
// are the complete set the machine-derived receiver record enumerates
// (receiver.offsets = [0, 4]).
constexpr std::size_t kReceiverWordAtZero = 0x00;
constexpr std::size_t kReceiverWordAtFour = 0x04;

// The two immediates the body stores, as values, so the model test can cross-check the
// literals the .cpp writes inline against a second, independent declaration. Reading
// them out of the image is what the header comment above documents.
constexpr Word kTableHeadAtZero = 0x013eb938u;  // 0x010537bf  MOV dword ptr [ESI],0x13eb938
constexpr Word kTableHeadAtFour = 0x013ec458u;  // 0x010537b8  MOV dword ptr [ESI + 0x4],0x13ec458

// The only way the body touches any of the above: a 4-byte word at a stated
// displacement into the object. A member access would assert an identity the
// bounds_only receiver record cannot corroborate.
inline std::uint32_t* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                         displacement);
}

inline const std::uint32_t* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// -- the one direct callee ----------------------------------------------------
// Declared here, defined in the model test as an observer. Its signature is fixed by
// its own bytes, not by its decompilation:
//
//   0x00f47380  8b 44 24 04           mov eax,DWORD PTR [esp+0x4]   ; its one argument
//   0x00f47384  85 c0                 test eax,eax                  ; and it null-checks it
//   0x00f47386  74 0c                 je  0x00f47394                ; skipping the work
//   0x00f47388  8b 0d 44 8b 6c 01     mov ecx,DWORD PTR ds:0x16c8b44 ; a .data word
//   0x00f4738e  50                    push eax
//   0x00f4738f  e8 2c 03 9e ff        call 0x009276c0               ; the release itself
//   0x00f47394  c3                    ret                           ; NO immediate
//
// What this body uses of it is narrower than what it is: one dword argument, the
// object address, and no return value. That the routine null-checks its argument is
// stated here because it is the one property of it that a test can lean on -- it does
// NOT make the CALLER null-safe, since 0x010537b8 and 0x010537bf dereference the
// receiver unconditionally and fault first on a null `this`. The name says "release",
// which is what its own shape is (a guarded one-argument hand-off to a release
// function held in a global); that it is a particular named CRT entry point is an
// inference from the null check plus the shape, not something its bytes state.
extern "C" void PKG_SWARM_W1_010537B0_CDECL heap_release_00f47380(void* pointer);

// FUN_010537b0 @ 0x010537b0 -- the scalar-deleting-destructor shape, reconstructed.
//
// __thiscall, receiver in ECX, exactly one ordinary stack argument, `RET 0x4`. The
// stack argument is read as a BYTE by the body's first instruction (0x010537b0
// `TEST byte ptr [ESP + 0x4],0x1`, taken with ESP still at its entry value), and only
// bit 0 of that byte is examined.
//
// The return type is a POINTER TO THE RECEIVER, and that is what the body does rather
// than what any record names: 0x010537d0 `MOV EAX,ESI` is reached by falling out of
// both arms -- the JZ target and the instruction after the release call -- so every
// path returns the receiver, unchanged, in EAX. The machine-derived record calls the
// same thing "unclassified_in_EAX" and its return sub-record carries
// register_class aggregate_unknown, void_possible false; Ghidra's decompilation types
// it `undefined4 *` and returns param_1. A four-byte pointer to the receiver agrees
// with all three; the C spelling is a source-side choice among the types of that
// width and is not machine-fixed. See the sidecar's RETURN SEMANTICS note.
extern "C" TableWordPair* PKG_SWARM_W1_010537B0_THISCALL re_010537b0(
    TableWordPair* receiver, std::uint8_t deleting_destructor_flag);

}  // namespace openspore::reconstruction::pkg_swarm_w1_010537b0
