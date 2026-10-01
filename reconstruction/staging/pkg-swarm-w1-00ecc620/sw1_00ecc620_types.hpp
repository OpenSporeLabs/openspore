// PKG-SWARM-W1-00ECC620 -- VA 0x00ecc620
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for the vector deleting destructor at 0x00ecc620
// (Ghidra: FUN_00ecc620).
//
// WHAT THIS HEADER CLAIMS, AND WHERE EACH CLAIM COMES FROM
//
// The body is 26 instructions, 0x00ecc620..0x00ecc676 inclusive, and its
// disassembly was re-derived from the image bytes for this package (objdump -d
// over SPORE/SporeBin/SporeApp.exe at 0x00ecc620) rather than taken on trust. It
// reproduces the 26 committed instructions at the same addresses with the same
// lengths, targets and displacements:
//
//   ecc620: 56                    push   esi
//   ecc621: 8b f1                 mov    esi,ecx
//   ecc623: c7 06 b0 93 48 01     mov    DWORD PTR [esi],0x14893b0
//   ecc629: c7 46 10 9c 93 48 01  mov    DWORD PTR [esi+0x10],0x148939c
//   ecc630: c7 46 14 8c 93 48 01  mov    DWORD PTR [esi+0x14],0x148938c
//   ecc637: 8b 86 80 00 00 00     mov    eax,DWORD PTR [esi+0x80]
//   ecc63d: 8b 8e 88 00 00 00     mov    ecx,DWORD PTR [esi+0x88]
//   ecc643: 2b c8                 sub    ecx,eax
//   ecc645: 83 e1 fe              and    ecx,0xfffffffe
//   ecc648: 83 f9 02              cmp    ecx,0x2
//   ecc64b: 7e 0d                 jle    0xecc65a
//   ecc64d: 85 c0                 test   eax,eax
//   ecc64f: 74 09                 je     0xecc65a
//   ecc651: 50                    push   eax
//   ecc652: e8 29 ad 07 00        call   0xf47380
//   ecc657: 83 c4 04              add    esp,0x4
//   ecc65a: 8b ce                 mov    ecx,esi
//   ecc65c: e8 2f 5b 77 ff        call   0x642190
//   ecc661: f6 44 24 08 01        test   BYTE PTR [esp+0x8],0x1
//   ecc666: 74 09                 je     0xecc671
//   ecc668: 56                    push   esi
//   ecc669: e8 12 ad 07 00        call   0xf47380
//   ecc66e: 83 c4 04              add    esp,0x4
//   ecc671: 8b c6                 mov    eax,esi
//   ecc673: 5e                    pop    esi
//   ecc674: c2 04 00              ret    0x4
//
//   0x00ecc677..0x00ecc67f is nine 0xcc bytes (INT3 padding), so the 87-byte body
//   is followed by nothing: there is no fallthrough and no second entry.
//
// EVERY OFFSET AND CONSTANT IN THIS HEADER, WITH THE INSTRUCTION THAT FIXES IT
//
//   receiver+0x00  <- 0x00ecc623 `MOV DWORD PTR [esi],0x14893b0`          (word, WRITE)
//   receiver+0x10  <- 0x00ecc629 `MOV DWORD PTR [esi+0x10],0x148939c`     (word, WRITE)
//   receiver+0x14  <- 0x00ecc630 `MOV DWORD PTR [esi+0x14],0x148938c`     (word, WRITE)
//   receiver+0x80  <- 0x00ecc637 `MOV EAX,DWORD PTR [esi+0x80]`          (word, READ)
//   receiver+0x88  <- 0x00ecc63d `MOV ECX,DWORD PTR [esi+0x88]`          (word, READ)
//   entry+4        <- 0x00ecc661 `TEST BYTE PTR [esp+0x8],0x1` with ESP = entry-4
//                    (the one `PUSH ESI` at 0x00ecc620 makes the frame exactly four
//                    bytes deep, so entry-4 + 8 is entry+4: the first ordinary stack
//                    argument) -- and 0x00ecc674 `RET 0x4`, which is what pops it.
//   mask 0x01      <- 0x00ecc661, the immediate of the TEST
//   mask 0xfffffffe <- 0x00ecc645, the immediate of the AND
//   bound 0x02     <- 0x00ecc648, the immediate of the CMP
//   cleanup 4      <- 0x00ecc657 and 0x00ecc66e (`ADD ESP,0x4`, the 0x00f47380
//                    argument) and 0x00ecc674 (`RET 0x4`, the flag word)
//
// Those five receiver displacements ARE the complete set the machine-derived
// receiver record enumerates: abi_derived.receiver is
// {register ECX, offsets [0, 16, 20, 128, 136], written_through 3, bounds_only
// true}. Three writes, two reads, five displacements, and nothing else on the
// receiver is touched by this body -- in particular the words at +0x04..+0x0f,
// +0x18..+0x7f, +0x81..+0x87 and +0x89 onward are never read or written here.
//
// WHY NO MEMBER IS NAMED FOR THOSE FIVE DISPLACEMENTS
//
// The record is bounds_only: it says where the body was seen reaching and not
// which member is which. The three stores are certainly the object's dispatch
// words -- that is argued from the image below, not from the record -- but
// naming a struct member would be an identity claim the machine-derived record
// cannot corroborate, so this header declares NO member for any of the five and
// the model reaches each one by displacement. The constants are named, because a
// constant is a value and a value is what the instruction fixes.
//
// WHAT THE THREE STORED CONSTANTS ARE, AND WHY (image facts, not names)
//
// 0x014893b0, 0x0148939c and 0x0148938c are all in the .rdata segment, so the
// body's three immediates are three data addresses. Reading the image's own
// words at those addresses gives (0x014893b0 shown 12 words; the run continues):
//
//   0x014893b0 +0x00 : 0x00ecc620  <- THIS BODY'S OWN ADDRESS
//   0x014893b0 +0x04 : 0x00641340
//   0x014893b0 +0x08 : 0x00c2e4e0
//   0x014893b0 +0x0c : 0x00ecc530
//   0x014893b0 +0x10 : 0x00641820
//   0x014893b0 +0x14 : 0x00641850
//   0x014893b0 +0x18 : 0x006414e0
//   0x014893b0 +0x1c : 0x00641500
//   0x014893b0 +0x20 : 0x00641860
//   0x014893b0 +0x24 : 0x00641770
//   0x014893b0 +0x28 : 0x00641870
//   0x014893b0 +0x2c : 0x00641780
//
//   0x0148939c +0x00 : 0x00c6a960
//   0x0148939c +0x04 : 0x007b86e0
//   0x0148939c +0x08 : 0x00ecc600  <- 0x00ecc600 is `83 e9 10 / e9 1b 00 00 00`,
//                                   i.e. `SUB ECX,0x10; JMP 0x00ecc620`
//   0x0148939c +0x0c : 0x00ecc510
//   0x0148939c +0x10 : 0x00000000
//   0x0148939c +0x14 : 0x00ecc620  <- and again, 0x014893b0
//
//   0x0148938c +0x00 : 0x00ecc610  <- 0x00ecc610 is `83 e9 14 / e9 0b 00 00 00`,
//                                   i.e. `SUB ECX,0x14; JMP 0x00ecc620`
//   0x0148938c +0x10 : 0x0148939c
//   0x0148938c +0x24 : 0x014893b0
//
// So the word at receiver+0x00 is installed from a table whose FIRST entry is
// this body, and the words at receiver+0x10 and receiver+0x14 are installed from
// tables whose destructing entries are two adjust-and-jump thunks that subtract
// exactly 0x10 and 0x14 from the receiver and land on this body. That is what
// fixes the three displacements as three DISPATCH WORDS at three subobject
// offsets, and it is why the class has one primary subobject at +0x00 plus two
// further subobjects at +0x10 and +0x14. It is a layout argument, and it is
// recorded as one; no record in this repository names the class.
//
// CORROBORATION #1 -- the constructor at 0x00ecc780, in the same image
//
// 0x00ecc780 calls 0x00ecc680 (a constructor) first, then zeroes byte [esi+0x78]
// and word [esi+0x7c], and then writes the SAME three constants -- 0x014893b0,
// 0x0148939c, 0x0148938c -- to the SAME three displacements [esi], [esi+0x10]
// and [esi+0x14] (0x00ecc795 / 0x00ecc79b / 0x00ecc7a2). A destructor and a
// constructor of one class writing the same three words to the same three
// displacements is what makes them dispatch words rather than three unrelated
// data values.
//
// The same constructor also writes 0x01667bac to [esi+0x80] AND [esi+0x84] and
// 0x01667bae to [esi+0x88] (0x00ecc7a9 / 0x00ecc7b4 / 0x00ecc7ba). Those are the
// two words this body READS at +0x80 and +0x88, and their initial difference is
// 0x01667bae - 0x01667bac = 2, which is exactly the value the 0x00ecc645/0x00ecc648
// pair REJECTS -- so the freshly constructed object is not deallocated, and the
// guard's purpose is visible. Note the constructor also writes +0x84, which this
// body never reads: a sibling function at 0x00ecc530 reads +0x80 and +0x84
// instead, so the two words are distinct and picking the wrong pair is a real
// and easy error. This package reads +0x80 and +0x88 and no other pair.
//
// CORROBORATION #2 -- the base destructor 0x00642190 has the same three-store shape
//
// 0x00642190 (already reconstructed, in this repository as
// sporepedia_asset_destroy_00642190) opens `PUSH ESI / MOV ESI,ECX /
// MOV [ESI],0x13ff648 / MOV [ESI+0x10],0x1462748 / MOV [ESI+0x14],0x1462738`, i.e.
// the identical five-instruction prologue with a different triple of constants, and
// it ends `MOV ECX,ESI / POP ESI / JMP 0x006412a0` -- a TAIL JUMP, which is what
// establishes that it takes no stack argument and does not clean one up. Its three
// displacements are the same three as this body's. It also reads and conditionally
// frees the word at its own +0x40 (`MOV EAX,[ESI+0x40] / CMP EAX,[ESI+0x50] /
// PUSH EAX / CALL 0xf47380`, 0x006421c3..0x006421d0) -- the identical guard idiom
// this body uses for its +0x80/+0x88 pair, which is why that idiom is a data-shape
// test and not a coincidence.
//
// CORROBORATION #3 -- the shape of the deallocation port 0x00f47380
//
// 0x00f47380 is 21 bytes: `MOV EAX,[esp+4] / TEST EAX,EAX / JE 0xf47394 /
// MOV ECX,DWORD PTR ds:0x16c8b44 / PUSH EAX / CALL 0x9276c0 / RET` (0x00f47380,
// 0x00f47384, 0x00f47386, 0x00f47388, 0x00f4738e, 0x00f4738f, 0x00f47394). Its
// terminator is a bare `C3` with no immediate, which is why 0x00ecc657 and
// 0x00ecc66e have to drop the pushed words themselves; it null-checks its
// argument; and 0x006421d0 calls it the same way for the same purpose. This
// repository already names it `sporepedia_free_00f47380` in the promoted package
// pkg-sporepedia-safe-wave10, as `void __cdecl (Word)`; the declaration below
// deliberately matches that one, and the two must not drift apart.
//
// WHAT THE SHAPE OF THE WHOLE BODY IS (an argument, stated as one)
//
// Four independent byte facts line up into the standard MSVC "vector deleting
// destructor" shape, and each of them is checkable against the bytes:
//
//  (a) A ONE-BYTE stack argument at entry+4 is tested against bit 0 only
//      (0x00ecc661). 0x00642210, 24 bytes at that address, is the same body with
//      the buffer guard removed: `PUSH ESI / MOV ESI,ECX / CALL 0x642190 /
//      TEST BYTE PTR [esp+0x8],0x1 / JE +9 / PUSH ESI / CALL 0xf47380 /
//      ADD ESP,0x4 / MOV EAX,ESI / POP ESI / RET 0x4` -- identical prologue, frame
//      depth, displacement, mask, branch polarity and distance, both call targets,
//      the caller-side cleanup, the returned word and the terminator.
//  (b) That same flag, when set, causes `operator delete(this)` (0x00ecc668).
//  (c) The base destructor 0x00642190 is called with ECX = the receiver first
//      (0x00ecc65a), so the whole class chain runs inside this call.
//  (d) `MOV EAX,ESI` (0x00ecc671) runs on BOTH arms, so this body returns `this`.
//
// 0x00ecc510, at 0x0148939c+0x0c, is the matching scalar-destructor thunk and it
// confirms the reading from the other side: it compares the flag word against the
// sentinel 0x5cd3f947 (`CMP EAX,0x5cd3f947`, 0x00ecc514) and on a match returns
// the adjusted `this` with `LEA EAX,[ECX-0x10] / RET 0x4`, which is the compiler's
// way of telling the deleting form from the non-deleting one.
//
// WHAT THE CLASS IS CALLED (one step removed from this VA, and labelled as such)
//
// 0x00ecc7d0 is the factory for this class. It calls 0x00ecc780 (the constructor
// above) on a block obtained from 0x00f473a0 with the size immediate 0x90
// (0x00ecc7fb) and the string immediate 0x01489468 (0x00ecc7f6). The bytes at
// 0x01489468 in this image are the NUL-terminated ASCII string
// "Sporepedia/AssetData/cSPScenarioCaptainAssetData", and 0x01489468 has exactly
// one reference anywhere in .text, at 0x00ecc7f7, inside that allocation. So the
// 0x90-byte object built by 0x00ecc780 and torn down by 0x00ecc620 is, on the
// evidence of its own allocator call, a Sporepedia::AssetData asset. The name is
// NOT used as a type name below: it is one indirection away from this body, this
// VA's own records carry `ghidra_name` FUN_00ecc620 and `sdk_name` null, and the
// reconstruction should not import an unverified name into a signature. It is
// recorded so a reviewer can check the chain against the bytes.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00ecc620 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare
// MSVC keywords, so the x86-32 attribute form is the portable spelling and the
// keyword form is kept for MSVC. Both are fixed by machine facts, not chosen:
//
//   PKG_SWARM_W1_00ECC620_THISCALL  this body and its 0x00642190 callee. The
//     receiver arrives in ECX (0x00ecc621 `MOV ESI,ECX`, with 0x00ecc623
//     dereferencing it before any definite write) and the terminator is
//     `RET 0x4` (0x00ecc674, bytes C2 04 00), so the callee owns the four-byte
//     argument word. 0x00642190's own tail jump to 0x006412a0 leaves it with no
//     stack argument to own, which is consistent.
//   PKG_SWARM_W1_00ECC620_CDECL     0x00f47380, whose last byte is a bare `C3`
//     (0x00f47394) with no immediate: it returns without touching ESP, and
//     0x00ecc657 / 0x00ecc66e drop the pushed words with `ADD ESP,0x4` themselves.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_00ECC620_THISCALL __thiscall
#define PKG_SWARM_W1_00ECC620_CDECL __cdecl
#else
#define PKG_SWARM_W1_00ECC620_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_00ECC620_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00ecc620 {

using Word = std::uint32_t;

// The receiver, as an opaque byte run.
//
// 0x00ecc623 / 0x00ecc629 / 0x00ecc630 write words at 0x00, 0x10 and 0x14 and
// 0x00ecc637 / 0x00ecc63d read words at 0x80 and 0x88, so 0x8c bytes is exactly the
// reach: the last byte read is receiver+0x8b. Nothing is named, for the reason in
// the file header: the receiver record is bounds_only.
//
// The class is 0x90 bytes, not 0x8c: the allocation in the factory at 0x00ecc7d0
// passes the size immediate 0x90. That is a statement about the object, from a
// function one indirection away, and it is deliberately not used as this type's
// size -- the size below is this body's reach, and nothing in this body reads or
// writes the last four bytes.
struct alignas(4) OpaqueSporepediaAssetData {
  std::array<std::uint8_t, 0x8c> opaque_00;  // 0x00..0x8b
};

// The five receiver displacements, as values. 0x00, 0x10 and 0x14 are the three
// dispatch words; 0x80 and 0x88 are the two ends of the run the 0x00ecc637..0x00ecc64b
// guard measures. The descriptions come from the table contents read out of the
// image and from the constructor's own stores (see the file header), and are not
// member names, because none is declared.
constexpr std::size_t kReceiverWord00Displacement = 0x00;
constexpr std::size_t kReceiverWord10Displacement = 0x10;
constexpr std::size_t kReceiverWord14Displacement = 0x14;
constexpr std::size_t kReceiverSpanBeginDisplacement = 0x80;
constexpr std::size_t kReceiverSpanEndDisplacement = 0x88;

// The three immediates the body stores, one per displacement, exactly as the three
// instructions give them. Each is a .rdata address in the 3.1.0.22 image.
constexpr Word kObjectTableAt00 = 0x014893b0u;
constexpr Word kObjectTableAt10 = 0x0148939cu;
constexpr Word kObjectTableAt14 = 0x0148938cu;

// The two adjust-and-jump thunks that name this body as the destructor of the
// subobjects at +0x10 and +0x14. They are NOT referenced by the model -- the body
// never dispatches -- and they are recorded so a reviewer can check the layout
// argument in the file header against the bytes rather than taking it on trust.
constexpr Word kAdjustingThunkForDisplacement10 = 0x00ecc600u;  // SUB ECX,0x10; JMP 0x00ecc620
constexpr Word kAdjustingThunkForDisplacement14 = 0x00ecc610u;  // SUB ECX,0x14; JMP 0x00ecc620

// 0x00ecc645 `AND ECX,0xfffffffe` and 0x00ecc648 `CMP ECX,0x2`, kept as named
// values because they are immediates in the listing and the two are a matched
// pair: the mask makes the compared quantity even, which is what lets the compare
// stand in for "more than one element".
constexpr Word kDistanceMask = 0xfffffffeu;
constexpr Word kDistanceBound = 0x02u;

// The flag word at entry+4. The machine reads ONE BYTE of it and masks with 0x01,
// so bit 0 is the only bit it examines; every other bit of the word is ignored.
// This is a fact about the listing, and it is also why the model's second
// parameter is a std::uint8_t.
constexpr std::uint8_t kDeletingFlagMask = 0x01u;

// 0x00ecc657 / 0x00ecc66e `ADD ESP,0x4` and 0x00ecc674 `RET 0x4`: two
// caller-side cleanups for the words pushed for 0x00f47380 and one callee-side
// cleanup for the flag word. The terminator pops four bytes, so the flag occupies
// a four-byte stack slot even though the TEST reads one byte of it.
constexpr std::size_t kPushedWordCleanupBytes = 0x04;
constexpr std::size_t kStackCleanupBytes = 0x04;

// 0x00ecc648 `CMP ECX,0x2` with 0x00ecc64b `JLE`: a SIGNED less-or-equal, so the
// body frees only when the masked distance is a signed value strictly greater than
// two. Written without an implementation-defined unsigned-to-signed conversion:
// a 32-bit word compares greater than 2 as a signed quantity exactly when bit 31
// is clear and the word is not 0, 1 or 2. The model test walks the boundary and
// checks this predicate against the signed reading instruction by instruction.
inline bool signed_greater_than_distance_bound(Word value) {
  return (value & 0x80000000u) == 0u && value > kDistanceBound;
}

// 0x00ecc643 / 0x00ecc645 / 0x00ecc648 / 0x00ecc64b / 0x00ecc64d / 0x00ecc64f,
// as one predicate. The subtraction is 32-bit and wraps; the AND keeps bit 0
// clear; the compare is signed; and the second test is on the BEGIN word, not on
// the distance, which is why a zero begin is skipped even when the span is wide.
inline bool span_requires_deallocation(Word begin, Word end) {
  const Word distance = end - begin;                                       // 00ecc643
  const Word masked = distance & kDistanceMask;                            // 00ecc645
  return signed_greater_than_distance_bound(masked) && begin != 0u;         // 00ecc648/4b/4d/4f
}

// The only way this body touches the receiver: a word at a stated displacement. A
// member access would assert an identity the machine-derived record cannot
// corroborate, so the model goes through these helpers instead. The one-argument
// form takes an already-formed address (`word_at(self + 0x10)`), the two-argument
// form a base and a displacement; the model's five accesses use the second so that
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

static_assert(sizeof(OpaqueSporepediaAssetData) == 0x8c,
              "0x88 + 4 is the last byte the body reads on the receiver");
static_assert(kReceiverSpanEndDisplacement + sizeof(Word) == sizeof(OpaqueSporepediaAssetData),
              "the last read word ends the modeled receiver exactly");
static_assert(kReceiverWord14Displacement + sizeof(Word) <= kReceiverSpanBeginDisplacement,
              "the three dispatch words and the span begin do not overlap");
static_assert(kReceiverSpanBeginDisplacement + 4 == kReceiverSpanEndDisplacement - 4,
              "the span begin sits one dword below the middle word, which is not read");
static_assert(kReceiverWord10Displacement + 4 == kReceiverWord14Displacement,
              "the +0x10 and +0x14 words are adjacent, not overlapping");
static_assert(kReceiverWord00Displacement + 4 <= kReceiverWord10Displacement,
              "the +0x00 word and the +0x10 word do not overlap");
static_assert(kDistanceMask == 0xfffffffeu, "the immediate of AND ECX at 0x00ecc645");
static_assert(kDistanceBound == 0x02u, "the immediate of CMP ECX at 0x00ecc648");
static_assert(kDeletingFlagMask == 0x01u, "the immediate of TEST BYTE PTR at 0x00ecc661");

// -- the two direct callees ---------------------------------------------------
// Each is declared here, and none is defined here: the model test defines both as
// observers. Both signatures are fixed by the callee's own bytes.

// 0x00642190, called at 0x00ecc65c with the receiver left in ECX and NO stack
// argument. __thiscall, and the callee owns no cleanup because its last two
// instructions are `POP ESI` (0x00642204) and `JMP 0x006412a0` (0x00642205) -- a
// tail jump, so it cannot be popping a caller's argument and does not.
//
// This repository already owns this address:
// reconstruction/metadata/pkg-sporepedia-safe-wave10/00642190.json names it
// sporepedia_asset_destroy_00642190, and this package's own target record names it
// the same way (briefing.callees[0]). The name is reused so the model does not
// invent a competing one; no other package's header is included here, and nothing
// about 0x00642190's interior is asserted by this package -- only that it takes
// the receiver in ECX, takes no stack argument, and does not clean one up.
extern "C" void PKG_SWARM_W1_00ECC620_THISCALL sporepedia_asset_destroy_00642190(
    OpaqueSporepediaAssetData* asset);

// 0x00f47380, called at 0x00ecc652 with the span begin pushed as the single stack
// word, and again at 0x00ecc669 with the receiver pushed. cdecl: the callee's
// terminator is a bare `C3` (0x00f47394) and the body drops each word itself with
// `ADD ESP,0x4` (0x00ecc657 and 0x00ecc66e). Its own first act is
// `MOV EAX,[esp+4]` (0x00f47380) and it null-checks that word (`TEST EAX,EAX`,
// 0x00f47384), so a null pointer is a no-op for it -- a fact about the CALLEE,
// used here only to describe the callee and asserted by nothing in this package.
//
// NOTE ON WHAT THE TWO `ADD ESP,0x4` ARE AND ARE NOT. They are recorded because
// they are instructions 13 and 23 of 26 and because the callee's bare `C3` is what
// requires them. They are NOT observable through the model test, and the test says
// so rather than pretending otherwise: for a leaf callee that does not touch the
// caller's stack, a callee-pops and a caller-pops return are the same machine
// behaviour. The convention is established by the callee's bytes, which are real
// evidence; it just is not evidence a black-box observer can exercise.
extern "C" void PKG_SWARM_W1_00ECC620_CDECL sporepedia_free_00f47380(Word address);

// -- the body -----------------------------------------------------------------
//
// __thiscall, receiver in ECX, exactly ONE ordinary stack argument, `RET 0x4`.
// The argument count is not a guess. The frame is four bytes deep from the single
// `PUSH ESI` at 0x00ecc620, so 0x00ecc661's `[esp+0x8]` is entry+4, which is the
// first ordinary argument slot; `RET 0x4` then consumes the return address plus
// that one four-byte word, and the walk balances exactly. Ghidra's own local for
// the slot is `Stack[0x4]:1` typed `byte`, and the machine-derived ABI record
// reports one ordinary stack slot, `observed: true`, `sizes: [1]`, and
// `stack_cleanup_bytes: 4` with the callee as owner -- all of which agree.
//
// Return type is a POINTER TO THE RECEIVER, and that is a machine fact and not a
// convention: 0x00ecc671 `MOV EAX,ESI` executes on BOTH arms (it sits after the
// 0x00ecc666 join, reached by falling through from the 0x00f47380 call or by the
// branch), and ESI is the receiver alias from 0x00ecc621 which is never
// reassigned. So EAX holds the receiver on every path out of this body. (The
// derived ABI record classifies that EAX as `unclassified_in_EAX` with type null,
// which is a statement about its classifier and not about the listing.)
extern "C" OpaqueSporepediaAssetData* PKG_SWARM_W1_00ECC620_THISCALL re_00ecc620(
    OpaqueSporepediaAssetData* receiver, std::uint8_t deleting_flag);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00ecc620
