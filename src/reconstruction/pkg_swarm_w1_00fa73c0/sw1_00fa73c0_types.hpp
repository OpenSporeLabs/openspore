// PKG-SWARM-W1-00FA73C0 -- VA 0x00fa73c0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00fa73c0 @ 0x00fa73c0.
//
// WHAT THIS BODY IS, IN THE WORDS THE MACHINE USES. 46 instructions, 140 bytes,
// 0x00fa73c0..0x00fa744b inclusive. The 140 bytes were read out of the image for
// this package (file offset = VA - 0x400000 - 0xc00, so 0x00fa73c0 is at file
// offset 0xba67c0, which is the .text section whose VMA 0x00401000 maps to file
// offset 0x400) and re-disassembled with objdump -b binary -m i386 -M intel. The
// result matches the committed 46-instruction Ghidra listing
// (reconstruction/evidence/00fa73c0/evidence.json, categories.disassembly)
// instruction for instruction at all 46 addresses, and the lengths add up exactly:
// 1+1+2+6+1+6+1+1+1+5+2+5+2+3+2+3+2+2+6+6+3+2+3+3+5+2+3+2+3+5+2+3+2+3+5+2+6+1+2+1+6+2+1+2+1+1
// = 140. abi_derived.parse reports {declared_count 46, unparsed 0, degraded
// false}. Nothing in this package depends on a listing that was not re-derived
// from those bytes.
//
//   00fa73c0  53                    push   ebx
//   00fa73c1  56                    push   esi
//   00fa73c2  8b f1                 mov    esi,ecx
//   00fa73c4  8b 9e 98 07 00 00     mov    ebx,DWORD PTR [esi+0x798]
//   00fa73ca  57                    push   edi
//   00fa73cb  8b be 9c 07 00 00     mov    edi,DWORD PTR [esi+0x79c]
//   00fa73d1  53                    push   ebx
//   00fa73d2  57                    push   edi
//   00fa73d3  57                    push   edi
//   00fa73d4  e8 97 83 ff ff        call   0x00f9f770
//   00fa73d9  2b fb                 sub    edi,ebx
//   00fa73db  b8 7d 41 5f d0        mov    eax,0xd05f417d
//   00fa73e0  f7 ef                 imul   edi
//   00fa73e2  c1 fa 05              sar    edx,0x5
//   00fa73e5  8b c2                 mov    eax,edx
//   00fa73e7  c1 e8 1f              shr    eax,0x1f
//   00fa73ea  03 c2                 add    eax,edx
//   00fa73ec  69 c0 ac 00 00 00     imul   eax,eax,0xac
//   00fa73f2  01 86 9c 07 00 00     add    DWORD PTR [esi+0x79c],eax
//   00fa73f8  8b 4e 28              mov    ecx,DWORD PTR [esi+0x28]
//   00fa73fb  8b 11                 mov    edx,DWORD PTR [ecx]
//   00fa73fd  8b 42 18              mov    eax,DWORD PTR [edx+0x18]
//   00fa7400  83 c4 0c              add    esp,0xc
//   00fa7403  68 0c 25 36 05        push   0x0536250c
//   00fa7408  ff d0                 call   eax
//   00fa740a  8b 4e 28              mov    ecx,DWORD PTR [esi+0x28]
//   00fa740d  8b 11                 mov    edx,DWORD PTR [ecx]
//   00fa740f  8b 42 18              mov    eax,DWORD PTR [edx+0x18]
//   00fa7412  68 0d 25 36 05        push   0x0536250d
//   00fa7417  ff d0                 call   eax
//   00fa7419  8b 4e 28              mov    ecx,DWORD PTR [esi+0x28]
//   00fa741c  8b 11                 mov    edx,DWORD PTR [ecx]
//   00fa741e  8b 42 18              mov    eax,DWORD PTR [edx+0x18]
//   00fa7421  68 9a 3f a2 03        push   0x03a23f9a
//   00fa7426  ff d0                 call   eax
//   00fa7428  8b 8e 0c 02 00 00     mov    ecx,DWORD PTR [esi+0x20c]
//   00fa742e  6a 00                 push   0x0
//   00fa7430  e8 db 3a 01 00        call   0x00fbaf10
//   00fa7435  8b 8e 0c 02 00 00     mov    ecx,DWORD PTR [esi+0x20c]
//   00fa743b  6a 00                 push   0x0
//   00fa743d  e8 0e 3b 01 00        call   0x00fbaf50
//   00fa7442  ff 86 14 08 00 00     inc    DWORD PTR [esi+0x814]
//   00fa7448  5f                    pop    edi
//   00fa7449  5e                    pop    esi
//   00fa744a  5b                    pop    ebx
//   00fa744b  c3                    ret
//
// HONESTY NOTE ON WHERE EVERY NAME IN THIS HEADER COMES FROM:
//
//  * No member of the receiver is named. The body reads five words of it and
//    writes through two of those five, every one of them by displacement, and
//    touches no other byte. The machine-derived receiver record is exactly that
//    and nothing more: register ECX, shape R-ALIAS, bounds_only true, offsets
//    [40, 524, 1944, 1948, 2068], distinct_offsets 5, max_offset 2068,
//    written_through 2, confidence SUPPORTED. It says where the body was seen
//    reaching and not what the words are for, so the receiver below is an opaque
//    0x818-byte run and every access in the .cpp is a displacement into it.
//    0x818 is not a claim about the class: it is 0x814 + 4, the last byte the
//    body writes.
//
//  * The two words at the displacements 0x798 and 0x79c are named
//    kRangeFirstField / kSnapField by what the body DOES with them and by what
//    0x00f9f770's own body does with the words it receives, and no more:
//    0x00fa73d1..0x00fa73d4 hand 0x00f9f770 the triple (word@0x79c, word@0x79c,
//    word@0x798), and 0x00f9f770's own first three instructions read its first
//    two stack words (EBX at 0x00f9f771, ESI at 0x00f9f776), compare them for
//    equality at 0x00f9f77a, and read the third (0x00f9f7a1) both as the early
//    return value and as the receiver of its per-element call. So the first two
//    arguments are a begin/end pair and the third is a third pointer. Whether
//    those three words are pointers AT ALL is NOT established by this body -- it
//    never dereferences any of the three itself -- so the model passes them
//    through as opaque words, not as typed pointers, and the model test plants
//    values that are not dereferenceable to prove nothing dereferences them.
//
//  * The word at the displacement 0x28 is a POINTER TO AN OBJECT, and that is a
//    fact rather than a naming choice: 0x00fa73fb `MOV EDX,[ECX]` dereferences it
//    and 0x00fa73fd `MOV EAX,[EDX+0x18]` dereferences the word that comes back.
//    Two levels, so a model that read the table word straight out of
//    receiver+0x28 would be reading an object that the machine never touches.
//    The offset of the dispatch word is +0x18, i.e. dword index 6, and the body
//    resolves the whole chain THREE SEPARATE TIMES (0x00fa73f8..0x00fa73fd,
//    0x00fa740a..0x00fa740f, 0x00fa7419..0x00fa741e). It does not cache the
//    resolved pointer, and the model test drives exactly that difference.
//
//  * The table at 0x01490be8 is the RECEIVER's class table, NOT the dispatch
//    table of the object at receiver+0x28, and the two must not be confused.
//    Reading the 0x90 bytes at 0x01490be8 in this image puts 0x00fa73c0 itself at
//    the table's displacement +0x70 (slot index 28), which is the address the
//    target's own xref at 0x01490c58 comes from -- so that table is the one this
//    body is an entry of. But its slot +0x18 holds 0x00fa0d70, whose own seven
//    bytes are `8b 81 cc 01 00 00 / c3` -- `MOV EAX,[ECX+0x1cc]; RET`, a
//    zero-argument getter with a BARE RET that removes no stack word. The body
//    under reconstruction pushes one word before each of its three dispatches and
//    never drops another one (the only `ADD ESP` in the body is 0x00fa7400
//    `ADD ESP,0xc`, and the frame ledger in the .cpp shows it accounts for
//    exactly 0x00f9f770's three words). A callee that removed nothing would leave
//    the stack 12 bytes short at 0x00fa7448, so the object at receiver+0x28 cannot
//    be one of that table, and the +0x18 entry of a table shaped like
//    0x01490be8 is a 0-argument getter rather than the one-argument
//    callee-cleaned callee the call sites require. The neighbouring slot +0x1c of
//    0x01490be8 does hold exactly the required shape -- 0x00fa0d90 is
//    `8b 44 24 04 / 89 81 d0 01 00 00 / c2 04 00`, a one-argument
//    callee-cleaned setter -- which is recorded here as the reason the two tables
//    are kept apart. Neither table is modelled as a member of anything.
//
//  * The word at the displacement 0x20c is likewise a pointer, passed as the
//    hidden receiver of 0x00fbaf10 and 0x00fbaf50 (0x00fa7428 and 0x00fa7435 --
//    two separate reads of the same displacement, not one cached word). Both
//    callees dereference their own ECX, so it must be a pointer. Its sub-layout
//    is NOT fixed by this body: the two callees read and write their receivers at
//    their own displacements 0x5c0, 0x5c4, 0x1f4 and 0x00, and 0x00fbaf10 adds
//    0x20c to ECX before tail-jumping to 0x00ac9480, so the model keeps the
//    object opaque and asserts nothing about its size.
//
//  * The 0xac stride and the 0xac multiplier are the same constant read twice,
//    and both come from the bytes: 0x00f9f78b `ADD ESI,0xac` / 0x00f9f791
//    `ADD EDI,0xac` in the callee, and 0x00fa73ec `IMUL EAX,EAX,0xac` in this
//    body. The magic 0xd05f417d and the shift 5 are read from 0x00fa73db and
//    0x00fa73e2. Nothing in the header rounds that to a "division" by anything;
//    the .cpp reproduces the six instructions and the model test proves what the
//    six instructions are equal to, over the whole 32-bit signed domain.
//
//  * The three dispatched immediates 0x0536250c, 0x0536250d and 0x03a23f9a are
//    reproduced exactly and are NOT named. The first two are adjacent integers;
//    that is an observation about their bit patterns, not a claim about their
//    meaning. No record in this repository says what any of the three is.
//
//  * The tables 0x016d6d30 and 0x016d6d70 that 0x00fbaf10 and 0x00fbaf50 index
//    with `LEA EAX,[EAX*4+0x16d6d30]` and `MOV ESI,[EAX*4+0x16d6d70]` lie outside
//    every section header in this file (.data ends at VMA 0x015d0c00), so their
//    contents are NOT recoverable from this image and nothing is claimed about
//    the words 0x00fbaf10 and 0x00fbaf50 would fetch. That is a callee's business
//    anyway; this package asserts only their own terminators and their receiver.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00fa73c0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare MSVC
// keywords, so the x86-32 attribute form is the portable spelling and the keyword form
// is kept for MSVC. Both are asserted by machine facts, not chosen for convenience:
//
//   PKG_SWARM_W1_00FA73C0_THISCALL  the body under reconstruction, 0x00fbaf10,
//     0x00fbaf50 and the three dispatch targets. The two direct callees' own bytes
//     are the hard evidence: 0x00fbaf10 ends `c2 04 00` and 0x00fbaf50 ends
//     `c2 04 00` (RET 0x4) after taking their receiver in ECX (0x00fbaf10
//     `CMP DWORD PTR [ECX+0x5c0],EAX` in its very first comparison,
//     0x00fbaf50 `MOV EDI,ECX` at 0x00fbaf55), so each owns the cleanup of the one
//     stack word it is given. The three dispatch targets are bound to the same
//     convention by the frame ledger: the body pushes one word before each of the
//     three and never drops another, and the three POPs at 0x00fa7448..0x00fa744a
//     restore exactly the three PUSHes of 0x00fa73c0/0x00fa73c1/0x00fa73ca, so the
//     stack is balanced at 0x00fa744b only if each of the three removed its own
//     word. The body under reconstruction is __thiscall on the same evidence: the
//     receiver arrives in ECX, is copied to ESI at 0x00fa73c2, and is dereferenced
//     (0x00fa73c4) before any definite write to it.
//   PKG_SWARM_W1_00FA73C0_CDECL  0x00f9f770, the one direct callee with an argument
//     list this body manages itself. Its own body is 0x38 bytes,
//     0x00f9f770..0x00f9f7a7, and BOTH of its exits are a bare `c3` with no
//     immediate (0x00f9f7a0 on the loop exit and 0x00f9f7a7 on the early return),
//     i.e. it returns without touching ESP. 0x00fa7400 `ADD ESP,0xc` is therefore
//     the CALLER's cleanup of its three words, which is the other half of the cdecl
//     pairing. abi_derived.conventions for this target independently reports
//     calling_convention __thiscall with candidates [__thiscall, __fastcall] and
//     cleanup {bytes 0, side caller}, and the abi record's saved_registers are
//     exactly the three the prologue pushes.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_00FA73C0_THISCALL __thiscall
#define PKG_SWARM_W1_00FA73C0_CDECL __cdecl
#else
#define PKG_SWARM_W1_00FA73C0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_00FA73C0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00fa73c0 {

using Word = std::uint32_t;

// The signature of the dispatch target. One hidden receiver in ECX plus one
// stack word, callee-cleaned -- see the convention note above for why the cleanup
// belongs to the callee. The receiver is typed void* because this body never
// looks inside the sub-object: it dereferences it exactly once, and only to read
// the dispatch word at +0x00.
using DwordThunk = void(PKG_SWARM_W1_00FA73C0_THISCALL*)(void* receiver, Word word);

// The receiver. The five displacements below are the complete set the body
// reaches, and nothing else on it is read or written:
//
//   0x00fa73c4  MOV EBX,DWORD PTR [ESI + 0x798]   read
//   0x00fa73cb  MOV EDI,DWORD PTR [ESI + 0x79c]   read
//   0x00fa73f2  ADD DWORD PTR [ESI + 0x79c],EAX   read-modify-write
//   0x00fa73f8  MOV ECX,DWORD PTR [ESI + 0x28]    read   (three times: 0x740a, 0x7419)
//   0x00fa7428  MOV ECX,DWORD PTR [ESI + 0x20c]   read   (twice: 0x7435)
//   0x00fa7442  INC DWORD PTR [ESI + 0x814]       read-modify-write
struct alignas(4) Receiver {
  std::array<std::uint8_t, 0x818> opaque_00{};  // 0x00..0x817
};

constexpr std::size_t kDispatchObjectDisplacement = 0x28;
constexpr std::size_t kTableObjectDisplacement = 0x20c;
constexpr std::size_t kRangeFirstFieldDisplacement = 0x798;
constexpr std::size_t kSnapFieldDisplacement = 0x79c;
constexpr std::size_t kCounterDisplacement = 0x814;

// The dispatch word's own displacement, read at 0x00fa73fd / 0x00fa740f /
// 0x00fa741e as `MOV EAX,DWORD PTR [EDX + 0x18]`. 0x18 is 4*6, so it is dword
// index 6 counting from the dispatch word itself. The model test fills indices 0
// through 8 with distinct markers so that an off-by-one-slot reconstruction calls
// the wrong marker and is caught.
constexpr std::size_t kDispatchWordDisplacement = 0x18;
constexpr std::size_t kDispatchWordIndex = 0x18 / 4;

// The three immediates, in the order the body pushes them.
constexpr Word kFirstDispatchWord = 0x0536250cu;
constexpr Word kSecondDispatchWord = 0x0536250du;
constexpr Word kThirdDispatchWord = 0x03a23f9au;

// The arithmetic at 0x00fa73d9..0x00fa73f2, as literals. 0xd05f417d is the
// immediate of 0x00fa73db; 5 is the shift count of 0x00fa73e2 `SAR EDX,0x5`;
// 0xac is the immediate of 0x00fa73ec `IMUL EAX,EAX,0xac`. 0xac is also the stride
// 0x00f9f770 steps both of its cursor words by (0x00f9f78b, 0x00f9f791).
constexpr Word kSnapMagic = 0xd05f417du;
constexpr unsigned kSnapShift = 5;
constexpr Word kSnapStride = 0xacu;

// The one and only way the body touches the receiver: a word or a pointer at a
// stated displacement. A member access would assert an identity the
// machine-derived receiver record cannot corroborate, because that record is
// bounds_only.
inline std::uint32_t* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                         displacement);
}

inline const std::uint32_t* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline void** pointer_at(void* base, std::size_t displacement) {
  return reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(base) +
                                  displacement);
}

static_assert(sizeof(Receiver) == 0x818,
              "0x814 + 4 is the last byte the body writes on the receiver");
static_assert(kCounterDisplacement + sizeof(Word) == sizeof(Receiver),
              "the counter word ends the modelled receiver");
static_assert(kDispatchWordDisplacement == kDispatchWordIndex * 4,
              "the dispatch word lives at dword index 6 of the sub-object's table");
static_assert(kSnapStride == 0xac,
              "0xac is both the IMUL immediate and 0x00f9f770's stride");

// Two's-complement reinterpretation of a 32-bit word as a signed value, written
// so that no step depends on an implementation-defined conversion:
//   * 0x00fa73e0 `IMUL EDI` is the SIGNED one-operand form, so the dividend and
//     the magic are both read as signed;
//   * 0x00fa73f2 `ADD DWORD PTR [ESI+0x79c],EAX` is a 32-bit add, so the store
//     wraps rather than being a checked operation.
inline std::int32_t as_signed(Word value) {
  return (value & 0x80000000u) != 0u
             ? (-1 - static_cast<std::int32_t>(~value))
             : static_cast<std::int32_t>(value);
}

// -- the three direct callees ------------------------------------------------
// Each is declared here, and none is defined here: the model test defines all
// three as observers. Every signature below is fixed by the callee's own bytes,
// not by its decompilation.

// 0x00f9f770, called at 0x00fa73d4. cdecl with exactly three stack words.
//
// Its own 0x38-byte body is the whole argument contract, and it is read here
// rather than taken from any record:
//   0x00f9f770 53                 PUSH EBX
//   0x00f9f771 8b 5c 24 0c        MOV EBX,DWORD PTR [ESP+0xc]   -> ESP=entry-4, so entry+0x8
//   0x00f9f775 56                 PUSH ESI
//   0x00f9f776 8b 74 24 0c        MOV ESI,DWORD PTR [ESP+0xc]   -> ESP=entry-8, so entry+0x4
//   0x00f9f77a 3b f3              CMP ESI,EBX
//   0x00f9f77c 74 23              JE 0x00f9f7a1
//   0x00f9f77e 57                 PUSH EDI
//   0x00f9f77f 8b 7c 24 18        MOV EDI,DWORD PTR [ESP+0x18]  -> ESP=entry-12, so entry+0xc
//   0x00f9f783 ...                loop: CALL 0x00f9f620 (ECX=EDI), ADD ESI,0xac, ADD EDI,0xac
//   0x00f9f7a0 c3                 RET                            (loop exit, bare)
//   0x00f9f7a1 8b 44 24 14        MOV EAX,DWORD PTR [ESP+0x14]  -> ESP=entry-8, so entry+0xc
//   0x00f9f7a7 c3                 RET                            (early return, bare)
//
// So: argument 1 and argument 2 are the ends of a range walked in 0xac steps and
// compared for equality first, and argument 3 is both the early return value and
// the receiver handed to 0x00f9f620 for each element. Both exits are bare RETs,
// so the caller owns the cleanup -- which 0x00fa7400 `ADD ESP,0xc` does.
//
// The words are typed void* because the callee walks them with a fixed stride and
// this body never dereferences them; whether they are pointers is unresolved and
// is listed in the sidecar.
extern "C" Word PKG_SWARM_W1_00FA73C0_CDECL for_each_stride_ac_00f9f770(
    void* range_first, void* range_last, void* parallel_first);

// 0x00fbaf10, called at 0x00fa7430. __thiscall, receiver in ECX, one stack word,
// callee-cleaned (`c2 04 00` at 0x00fbaf41). Its own body:
//   0x00fbaf10 8b 44 24 04        MOV EAX,DWORD PTR [ESP+0x4]    the argument
//   0x00fbaf14 39 81 c0 05 00 00  CMP DWORD PTR [ECX+0x5c0],EAX  early out if unchanged
//   0x00fbaf1c 85 c0              TEST EAX,EAX                   reject a negative id
//   0x00fbaf20 83 f8 10           CMP EAX,0x10                   reject an id >= 16
//   0x00fbaf25 89 81 c0 05 00 00  MOV DWORD PTR [ECX+0x5c0],EAX  store the id
//   0x00fbaf2b 8d 04 85 30 6d 6d 01 LEA EAX,[EAX*4+0x16d6d30]     table base + 4*id
//   0x00fbaf32 89 44 24 04        MOV DWORD PTR [ESP+0x4],EAX    rewrite the argument slot
//   0x00fbaf36 81 c1 0c 02 00 00  ADD ECX,0x20c                  bias the receiver
//   0x00fbaf3c e9 ...             JMP 0x00ac9480                 tail call
// The tail target 0x00ac9480 is itself __thiscall with one stack word and ends
// `c2 04 00`, so the 0x4 the two `ret 4`s remove is the same single word the
// caller pushed. The body under reconstruction always passes the literal 0, and
// with argument 0 the guard at 0x00fbaf20 passes (0 < 0x10) unless the receiver's
// word at +0x5c0 already holds 0, in which case the callee returns at 0x00fbaf41
// having done nothing. Which of the two happens is a property of the sub-object,
// so the model asserts neither and the observer does both.
extern "C" void PKG_SWARM_W1_00FA73C0_THISCALL select_from_table_a_00fbaf10(
    void* receiver, Word identifier);

// 0x00fbaf50, called at 0x00fa743d. __thiscall, receiver in ECX, one stack word,
// callee-cleaned (`c2 04 00` at 0x00fbaf9a). Its own body:
//   0x00fbaf50 8b 44 24 04        MOV EAX,DWORD PTR [ESP+0x4]
//   0x00fbaf55 8b f9              MOV EDI,ECX
//   0x00fbaf57 39 87 c4 05 00 00  CMP DWORD PTR [EDI+0x5c4],EAX
//   0x00fbaf66 8b 9f f4 01 00 00  MOV EBX,DWORD PTR [EDI+0x1f4]   the outgoing pointer
//   0x00fbaf6d 8b 34 85 70 6d 6d 01 MOV ESI,[EAX*4+0x16d6d70]      the incoming pointer
//   0x00fbaf7c..0x00fbaf82        CALL through [ESI] slot 0       attach the new one
//   0x00fbaf84 89 37 ...          MOV DWORD PTR [EDI+0x1f4],ESI  store it
//   0x00fbaf8e..0x00fbaf95        CALL through [EBX] slot 1       detach the old one
// Notice it touches a DIFFERENT receiver word than 0x00fbaf10: +0x5c4 against
// +0x5c0. That difference is a fact of the two callees' bytes and is why the model
// does not fold them into one operation. The word it dispatches through is at the
// table's own +0x00 and +0x04, and the word it fetches from 0x016d6d70 is not
// recoverable from this image -- so the observer is free to fabricate the incoming
// pointer and the model asserts nothing about what the callee would have done with
// the real one.
extern "C" void PKG_SWARM_W1_00FA73C0_THISCALL select_from_table_b_00fbaf50(
    void* receiver, Word identifier);

// The snap amount of 0x00fa73d9..0x00fa73ec, factored out of the body so the model
// test can drive THIS code over the whole 32-bit domain rather than over a handful
// of hand-picked inputs.
//
// It is the value EAX holds at 0x00fa73f2, given the two words the body had already
// read: `snap_delta_step(range_first, cursor)` reproduces 0x00fa73d9
// `SUB EDI,EBX`, 0x00fa73db `MOV EAX,0xd05f417d`, 0x00fa73e0 `IMUL EDI`,
// 0x00fa73e2 `SAR EDX,0x5`, 0x00fa73e5 `MOV EAX,EDX`, 0x00fa73e7 `SHR EAX,0x1f`,
// 0x00fa73ea `ADD EAX,EDX` and 0x00fa73ec `IMUL EAX,EAX,0xac` in that order. The
// body calls it and touches nothing in between, so the factoring is not observable.
//
// What the six arithmetic instructions are equal to -- an identity the model test
// proves and this comment does not assert -- is
//     -(trunc(delta / 172)) * 172        delta = cursor - range_first, wrapping
// over the whole 32-bit signed domain, with trunc() the C++ signed integer division
// (rounding toward zero). Nothing here rounds that to "a division by 172" or to
// any particular source expression: the two closed forms -(delta/172)*172 and
// (delta/-172)*172 are indistinguishable as integers, and the machine fixes the
// RESULT, not which of them the original source said.
//
// The name carries no address on purpose, and for two reasons that pull opposite
// ways, so both are recorded here. It does not carry 0x00fa73c0, which is the entry
// of the body under reconstruction: a helper stamped with the target's own address
// claims the target's identity, and sw1_snap_and_dispatch_00fa73c0 below is the
// definition that owns it. Nor does it carry 0x00fa73d9, the first instruction it
// models, unlike the other address-named helpers here -- for_each_stride_ac_00f9f770
// and select_from_table_a_00fbaf10 ARE real CALL targets, but this one is a fragment
// folded out of the target and not a callee, so an address in its name would read as
// a transfer of control that the body never makes. See the .cpp for the long form.
extern "C" Word snap_delta_step(Word range_first, Word cursor);

// FUN_00fa73c0 @ 0x00fa73c0.
//
// __thiscall, receiver in ECX, NO ordinary stack arguments, bare `RET`.
//
// The zero-argument surface is not an assumption. The prologue pushes exactly
// three words (0x00fa73c0, 0x00fa73c1, 0x00fa73ca) and the epilogue pops exactly
// three (0x00fa7448, 0x00fa7449, 0x00fa744a), with no SUB ESP, no LEA on ESP and
// no MOV EBP,ESP anywhere in the 46 instructions -- abi_derived.parse reports
// frame {fp false, sub null, lea_esp null, and_esp null, mov_ebp_esp false}. Every
// word the body pushes for a callee is either dropped by the body itself
// (0x00fa7400 `ADD ESP,0xc`) or by that callee (`ret 4`), so at 0x00fa7448 ESP is
// back on its entry value and the frame carries no argument slots at all.
//
// Return type is void, and that is a judgement the machine supports rather than a
// default. The last instruction that writes EAX on any path is 0x00fa741e
// `MOV EAX,DWORD PTR [EDX+0x18]`, the third dispatch's target load; after it the
// body only CALLs and INCs a memory word, and the INC does not touch EAX. So EAX
// is live at 0x00fa744b holding 0x00fbaf50's own return word, and nothing in this
// body writes a value there for its caller. The records disagree in how they say
// so and both are recorded in the sidecar: abi.return_semantics is
// "unclassified_in_EAX" and abi_derived.return is {register EAX,
// register_class aggregate_unknown, type null, void_possible false}, while the
// live decompilation of this VA is `void __fastcall FUN_00fa73c0(int param_1)`
// with an explicit bare `return;`, and ghidra_function.return_type is the
// unresolved string "undefined". void is what the bytes support; the residue in
// EAX is documented in the .cpp and the model test asserts nothing about it.
extern "C" void PKG_SWARM_W1_00FA73C0_THISCALL sw1_snap_and_dispatch_00fa73c0(
    Receiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00fa73c0
