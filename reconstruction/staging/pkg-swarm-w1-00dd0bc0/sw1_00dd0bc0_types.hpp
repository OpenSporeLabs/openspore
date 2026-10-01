// PKG-SWARM-W1-00DD0BC0 -- VA 0x00dd0bc0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for the scalar deleting destructor at 0x00dd0bc0.
//
// WHAT THIS HEADER CLAIMS, AND WHERE EACH CLAIM COMES FROM
//
// The body is 14 instructions, 0x00dd0bc0..0x00dd0bf1 inclusive, and its
// disassembly was re-derived from the image bytes for this package (objdump over
// the 0x32 bytes at file offset 0x9cffc0, RVA 0x9d0bc0) rather than taken on trust.
// It reproduces the 14 committed instructions at the same addresses with the same
// lengths, targets and displacements:
//
//   dd0bc0: 56                    push   esi
//   dd0bc1: 8b f1                 mov    esi,ecx
//   dd0bc3: c7 06 f8 c9 47 01     mov    DWORD PTR [esi],0x147c9f8
//   dd0bc9: c7 46 10 e8 c9 47 01  mov    DWORD PTR [esi+0x10],0x147c9e8
//   dd0bd0: c7 46 14 78 cc 47 01  mov    DWORD PTR [esi+0x14],0x147cc78
//   dd0bd7: e8 b4 15 87 ff        call   0x642190
//   dd0bdc: f6 44 24 08 01        test   BYTE PTR [esp+0x8],0x1
//   dd0be1: 74 09                 je     0xdd0bec
//   dd0be3: 56                    push   esi
//   dd0be4: e8 97 67 17 00        call   0xf47380
//   dd0be9: 83 c4 04              add    esp,0x4
//   dd0bec: 8b c6                 mov    eax,esi
//   dd0bee: 5e                    pop    esi
//   dd0bef: c2 04 00              ret    0x4
//
//   0x00dd0bf2..0x00dd0bfb is ten 0xcc bytes (INT3 padding), so the 50-byte body
//   is followed by nothing: there is no fallthrough and no second entry.
//
// EVERY OFFSET AND CONSTANT IN THIS HEADER, WITH THE INSTRUCTION THAT FIXES IT
//
//   receiver+0x00  <- 0x00dd0bc3 `MOV DWORD PTR [esi],0x147c9f8`   (word, WRITE)
//   receiver+0x10  <- 0x00dd0bc9 `MOV DWORD PTR [esi+0x10],0x147c9e8` (word, WRITE)
//   receiver+0x14  <- 0x00dd0bd0 `MOV DWORD PTR [esi+0x14],0x147cc78` (word, WRITE)
//   entry+4        <- 0x00dd0bdc `TEST BYTE PTR [esp+0x8],0x1` with ESP = entry-4
//                    (the one `PUSH ESI` at 0x00dd0bc0 makes the frame exactly four
//                    bytes deep, so entry-4 + 8 is entry+4: the first ordinary stack
//                    argument) -- and 0x00dd0bef `RET 0x4`, which is what pops it.
//   mask 0x01      <- 0x00dd0bdc, the immediate of the TEST
//   cleanup 4      <- 0x00dd0be9 `ADD ESP,0x4` (the 0x00f47380 argument) and
//                    0x00dd0bef `RET 0x4` (the flag word)
//
// Those three receiver displacements ARE the complete set the machine-derived
// receiver record enumerates: abi_derived.receiver is
// {register ECX, offsets [0, 16, 20], max_offset 20, bounds_only true,
// written_through 3, shape R-ALIAS}. Three writes, three displacements, no read
// of the receiver at all anywhere in the body -- this function only ever STORES to
// the receiver, and it reads nothing back.
//
// WHY NO MEMBER IS NAMED FOR THOSE THREE DISPLACEMENTS
//
// The record is bounds_only: it says where the body was seen reaching and not which
// member is which, and three displacements with no read cannot distinguish a word
// from a pointer. The three stores are certainly the object's dispatch words -- that
// is argued from the image below, not from the record -- but naming a struct member
// would be an identity claim the machine-derived record cannot corroborate, so this
// header declares NO member for any of them and the model reaches each one by
// displacement. The constants are named, because a constant is a value and a value
// is what the instruction fixes.
//
// WHAT THE THREE STORED CONSTANTS ARE, AND WHY (image facts, not names)
//
// 0x0147c9f8, 0x0147c9e8 and 0x0147cc78 are all in the data segment, so the body's
// three immediates are three data addresses. Reading the image's own words at those
// addresses gives:
//
//   0x0147c9f8 +0x00 : 0x00dd0bc0  <- THIS BODY'S OWN ADDRESS
//   0x0147c9f8 +0x04 : 0x00641340
//   0x0147c9f8 +0x08 : 0x00c2e4e0
//   0x0147c9f8 +0x0c : 0x00641810
//   ... (ten words read; the run continues)
//
//   0x0147c9e8 +0x08 : 0x00dd0bb0  <- 0x00dd0bb0 is `83 e9 10 / e9 58 00 00 00`,
//                                   i.e. `SUB ECX,0x10; JMP 0x00dd0bc0`
//   0x0147ca30 +0x90 : 0x00dd0bc0  <- and, identically, 0x0147ca70 +0x50
//   0x0147ca70 +0x50 : 0x00dd0bc0
//
//   0x0147cc78 +0x00 : 0x00dd0b40  <- 0x00dd0b40 is `83 e9 14 / e9 78 00 00 00`,
//                                   i.e. `SUB ECX,0x14; JMP 0x00dd0bc0`
//
// So the word at receiver+0x00 is installed from a table whose FIRST entry is this
// body, and the words at receiver+0x10 and receiver+0x14 are installed from tables
// whose destructing entries are two adjust-and-jump thunks that subtract exactly
// 0x10 and 0x14 from the receiver and land on this body. That is what fixes the
// three displacements as three DISPATCH WORDS at three subobject offsets, and it
// is why the class has one primary subobject at +0x00 plus two further subobjects at
// +0x10 and +0x14. It is a layout argument, and it is recorded as one; no record in
// this repository names the class.
//
// CORROBORATION #1 -- the sibling body at 0x00642210, instruction for instruction
//
// The 24 bytes at 0x00642210 are the same body with the three stores removed:
//
//   642210: 56                    push   esi
//   642211: 8b f1                 mov    esi,ecx
//   642213: e8 78 ff ff ff        call   0x642190     <- the SAME base destructor
//   642218: f6 44 24 08 01        test   BYTE PTR [esp+0x8],0x1   <- SAME displacement
//   64221d: 74 09                 je     0x642228     <- SAME +9
//   64221f: 56                    push   esi
//   642220: e8 5b 51 90 00        call   0xf47380     <- the SAME deallocation port
//   642225: 83 c4 04              add    esp,0x4
//   642228: 8b c6                 mov    eax,esi
//   64222a: 5e                    pop    esi
//   64222b: c2 04 00              ret    0x4
//
// The two bodies agree on the prologue, the alias register, the frame depth, the
// displacement and mask of the flag test, the branch polarity and distance, both
// call targets, the caller-side cleanup, the returned word and the terminator. Every
// one of those is a fact about 0x00dd0bc0 independently of its own bytes.
//
// CORROBORATION #2 -- the constructor at 0x00dd0b50, in the same image
//
// 0x00dd0b7a / 0x00dd0b80 / 0x00dd0b87 install the same three constants at the same
// three displacements (0x00dd0b50 first calls 0x00642100, a constructor, and only
// then writes 0x147c9f8 / 0x147c9e8 / 0x147cc78 to [esi], [esi+0x10] and [esi+0x14]).
// The destructor and the constructor of one class writing the same three words to
// the same three displacements is what makes them dispatch words rather than three
// unrelated data values. That constructor also writes further words at +0x78, +0x7c,
// +0x80, +0x84, +0x88, +0x8c, +0x90 and +0x98, so the real object is at least 0x9c
// bytes long -- but THIS body never reaches past 0x17, so the type below is
// 0x18 bytes and no more. That is a statement about this body's reach, not a claim
// about the object's size.
//
// CORROBORATION #3 -- the base destructor 0x00642190 has the same three-store shape
//
// 0x00642190 (already reconstructed, in this repository as
// sporepedia_asset_destroy_00642190) opens `PUSH ESI / MOV ESI,ECX /
// MOV [ESI],0x13ff648 / MOV [ESI+0x10],0x1462748 / MOV [ESI+0x14],0x1462738`, i.e.
// the identical five-instruction prologue with a different triple of constants, and
// it ends `MOV ECX,ESI / POP ESI / JMP 0x006412a0` -- a TAIL JUMP, which is what
// establishes that it takes no stack argument and does not clean one up. Its three
// displacements are the same three as this body's.
//
// CORROBORATION #4 -- the deallocation port 0x00f47380
//
// 0x00f47380 is 21 bytes: `MOV EAX,[esp+4] / TEST EAX,EAX / JE 0xf47394 /
// MOV ECX,DWORD PTR ds:0x16c8b44 / PUSH EAX / CALL 0x9276c0 / RET` (0x00f47380,
// 0x00f47384, 0x00f47386, 0x00f47388, 0x00f4738e, 0x00f4738f, 0x00f47394). Its
// terminator is a bare `C3` with no immediate, which is why 0x00dd0be9 has to drop
// the pushed word itself; it null-checks its argument; and 0x006421d0 calls it the
// same way for the same purpose. This repository already names it
// `free_00f47380` in the promoted package pkg-sporepedia-safe-wave10, as
// `void __cdecl (Word)`; the declaration below deliberately matches that one, and
// the two must not drift apart.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00dd0bc0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare
// MSVC keywords, so the x86-32 attribute form is the portable spelling and the
// keyword form is kept for MSVC. Both are fixed by machine facts, not chosen:
//
//   PKG_SWARM_W1_00DD0BC0_THISCALL  this body and its 0x00642190 callee. The
//     receiver arrives in ECX (0x00dd0bc1 `MOV ESI,ECX`, with 0x00dd0bc3
//     dereferencing it before any definite write) and the terminator is
//     `RET 0x4` (0x00dd0bef, bytes C2 04 00), so the callee owns the four-byte
//     argument word. 0x00642190's own tail jump to 0x006412a0 leaves it with no
//     stack argument to own, which is consistent.
//   PKG_SWARM_W1_00DD0BC0_CDECL     0x00f47380, whose last byte is a bare `C3`
//     (0x00f47394) with no immediate: it returns without touching ESP, and
//     0x00dd0be9 drops the pushed word with `ADD ESP,0x4` itself.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_00DD0BC0_THISCALL __thiscall
#define PKG_SWARM_W1_00DD0BC0_CDECL __cdecl
#else
#define PKG_SWARM_W1_00DD0BC0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_00DD0BC0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00dd0bc0 {

using Word = std::uint32_t;

// The receiver, as an opaque byte run.
//
// 0x00dd0bc3 / 0x00dd0bc9 / 0x00dd0bd0 write three words at 0x00, 0x10 and 0x14 and
// the body reads nothing from the receiver at any point, so 0x18 bytes is exactly
// the reach: the last byte written is receiver+0x17. Nothing is named, for the
// reason in the file header: the receiver record is bounds_only and a store-only
// body cannot say which member is which.
struct alignas(4) OpaqueSporepediaAsset {
  std::array<std::uint8_t, 0x18> opaque_00;  // 0x00..0x17
};

// The three receiver displacements, as values. 0x00 is the primary dispatch word,
// 0x10 and 0x14 the two further subobject dispatch words; the descriptions come
// from the table contents read out of the image (see the file header), and are not
// member names, because none is declared.
constexpr std::size_t kReceiverWord00Displacement = 0x00;
constexpr std::size_t kReceiverWord10Displacement = 0x10;
constexpr std::size_t kReceiverWord14Displacement = 0x14;

// The three immediates the body stores, one per displacement, exactly as the three
// instructions give them. Each is a data-segment address in the 3.1.0.22 image.
constexpr Word kObjectTableAt00 = 0x0147c9f8u;
constexpr Word kObjectTableAt10 = 0x0147c9e8u;
constexpr Word kObjectTableAt14 = 0x0147cc78u;

// The two adjust-and-jump thunks that name this body as the destructor of the
// subobjects at +0x10 and +0x14. They are NOT referenced by the model -- the body
// never dispatches -- and they are recorded so a reviewer can check the layout
// argument in the file header against the bytes rather than taking it on trust.
constexpr Word kAdjustingThunkForDisplacement10 = 0x00dd0bb0u;  // SUB ECX,0x10; JMP 0x00dd0bc0
constexpr Word kAdjustingThunkForDisplacement14 = 0x00dd0b40u;  // SUB ECX,0x14; JMP 0x00dd0bc0

// The flag word at entry+4. The machine reads ONE BYTE of it and masks with 0x01,
// so bit 0 is the only bit it examines; every other bit of the word is ignored.
constexpr std::uint8_t kDeletingFlagMask = 0x01u;

// 0x00dd0be9 `ADD ESP,0x4` and 0x00dd0bef `RET 0x4`: two callee-side cleanups, one
// for the word pushed for 0x00f47380 and one for the flag word. The terminator
// pops four bytes, so the flag occupies a four-byte stack slot even though the TEST
// reads one byte of it.
constexpr std::size_t kPushedWordCleanupBytes = 0x04;
constexpr std::size_t kStackCleanupBytes = 0x04;

// The only way this body touches the receiver: a word at a stated displacement. A
// member access would assert an identity the machine-derived record cannot
// corroborate, so the model goes through these helpers instead. The one-argument
// form takes an already-formed address (`word_at(self + 0x10)`), the two-argument
// form a base and a displacement; the model's three stores use the first so that
// the displacement each instruction fixes stays visible in the code.
inline Word* word_at(void* address) { return reinterpret_cast<Word*>(address); }

inline const Word* word_at(const void* address) {
  return reinterpret_cast<const Word*>(address);
}

inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

static_assert(sizeof(OpaqueSporepediaAsset) == 0x18,
              "0x14 + 4 is the last byte the body writes on the receiver");
static_assert(kReceiverWord14Displacement + sizeof(Word) == sizeof(OpaqueSporepediaAsset),
              "the last stored word ends the modeled receiver exactly");
static_assert(kReceiverWord10Displacement + 4 == kReceiverWord14Displacement,
              "the +0x10 and +0x14 words are adjacent, not overlapping");
static_assert(kReceiverWord00Displacement + 4 <= kReceiverWord10Displacement,
              "the +0x00 word and the +0x10 word do not overlap");

// -- the two direct callees ---------------------------------------------------
// Each is declared here, and none is defined here: the model test defines both as
// observers. Both signatures are fixed by the callee's own bytes.

// 0x00642190, called at 0x00dd0bd7 with the receiver left in ECX and NO stack
// argument. __thiscall, and the callee owns no cleanup because its last two
// instructions are `POP ESI` (0x00642204) and `JMP 0x006412a0` (0x00642205) -- a
// tail jump, so it cannot be popping a caller's argument and does not.
//
// This repository already owns this address: reconstruction/metadata/
// pkg-sporepedia-safe-wave10/006422190.json and the promoted
// src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.hpp both
// name it sporepedia_asset_destroy_00642190 with exactly this shape, and this
// package's own target record names it the same way. The name is reused so the
// model does not invent a competing one; no other package's header is included
// here, and nothing about 0x00642190's interior is asserted by this package.
extern "C" void PKG_SWARM_W1_00DD0BC0_THISCALL sporepedia_asset_destroy_00642190(
    OpaqueSporepediaAsset* asset);

// 0x00f47380, called at 0x00dd0be4 with the receiver pushed as the single stack
// word. cdecl: the callee's terminator is a bare `C3` (0x00f47394) and the body
// drops the word itself with `ADD ESP,0x4` (0x00dd0be9). Its own first act is
// `MOV EAX,[esp+4]` (0x00f47380) and it null-checks that word (`TEST EAX,EAX`,
// 0x00f47384), so a null pointer is a no-op for it -- a fact about the CALLEE,
// used here only to describe the callee and asserted by nothing in this package.
//
// NOTE ON WHAT 0x00dd0be9 IS AND IS NOT. The `ADD ESP,0x4` is recorded because it is
// instruction 10 of 14 and because the callee's bare `C3` is what requires it. It is
// NOT observable through the model test, and the test says so rather than pretending
// otherwise: for a leaf callee that does not touch the caller's stack, a callee-pops
// and a caller-pops return are the same machine behaviour, and two mutations of the
// test's own port observer -- one dropping the word, one dropping it twice -- both
// left the test green. The convention is established by the callee's bytes, which are
// real evidence; it just is not evidence a black-box observer can exercise.
extern "C" void PKG_SWARM_W1_00DD0BC0_CDECL sporepedia_free_00f47380(Word address);

// -- the body -----------------------------------------------------------------
//
// __thiscall, receiver in ECX, exactly ONE ordinary stack argument, `RET 0x4`.
// The argument count is not a guess. The frame is four bytes deep from the single
// `PUSH ESI` at 0x00dd0bc0, so 0x00dd0bdc's `[esp+0x8]` is entry+4, which is the
// first ordinary argument slot; `RET 0x4` then consumes the return address plus
// that one four-byte word, and the walk balances exactly. Ghidra's own local for
// the slot is `Stack[0x4]:1` typed `byte`, and the machine-derived ABI record
// reports one ordinary stack slot, `observed: true`, `sizes: [1]`, and
// `stack_cleanup_bytes: 4` with the callee as owner -- all of which agree.
//
// Return type is a POINTER TO THE RECEIVER, and that is a machine fact and not a
// convention: 0x00dd0bec `MOV EAX,ESI` executes on BOTH arms (it sits after the
// 0x00dd0be1 join, reached by falling through from the 0x00f47380 call or by the
// branch), and ESI is the receiver alias from 0x00dd0bc1 which is never
// reassigned. So EAX holds the receiver on every path out of this body. (The
// derived ABI record classifies that EAX as `aggregate_unknown` with type null,
// which is a statement about its classifier and not about the listing; the sidecar
// records the disagreement.)
extern "C" OpaqueSporepediaAsset* PKG_SWARM_W1_00DD0BC0_THISCALL re_00dd0bc0(
    OpaqueSporepediaAsset* receiver, std::uint8_t deleting_flag);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00dd0bc0
