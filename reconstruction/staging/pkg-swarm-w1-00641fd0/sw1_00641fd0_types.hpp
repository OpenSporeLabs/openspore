// PKG-SWARM-W1-00641FD0 -- VA 0x00641fd0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00641fd0, the unnamed Sporepedia member
// function at VA 0x00641fd0 in the `sporepedia-online` cluster.
//
// HONESTY NOTE ON WHERE EVERY CONSTANT IN THIS HEADER COMES FROM, because this
// body reaches four different objects and the split matters to a reader:
//
//  * 0x00, 0x08 and 0x3c on the receiver, 0x5c on the object the global getter
//    returns, 0x90 as a slot displacement on the receiver's own table and 0x04
//    as a slot displacement on the resolved handle's table are read straight out
//    of this body's own 62-instruction listing. The listing was re-decoded from
//    the 157 image bytes at 0x00641fd0..0x0064206c for this package and matches
//    the committed record instruction for instruction:
//
//      00641fd0  83 ec 0c           SUB  ESP,0xc
//      00641fd3  56                 PUSH ESI
//      00641fd4  8b f1              MOV  ESI,ECX
//      00641fd6  8b 46 3c           MOV  EAX,DWORD PTR [ESI+0x3c]
//      00641fd9  85 c0              TEST EAX,EAX
//      00641fdb  0f 85 87 00 00 00  JNE  0x642068
//      00641fe1  83 c8 ff           OR   EAX,0xffffffff
//      00641fe4  57                 PUSH EDI
//      00641fe5  89 44 24 0c        MOV  DWORD PTR [ESP+0xc],EAX
//      00641fe9  89 44 24 10        MOV  DWORD PTR [ESP+0x10],EAX
//      00641fed  8b 06              MOV  EAX,DWORD PTR [ESI]
//      00641fef  8b 90 90 00 00 00  MOV  EDX,DWORD PTR [EAX+0x90]
//      00641ff5  8d 4c 24 0c        LEA  ECX,[ESP+0xc]
//      00641ff9  51                 PUSH ECX
//      00641ffa  8b ce              MOV  ECX,ESI
//      00641ffc  ff d2              CALL EDX
//      00641ffe  84 c0              TEST AL,AL
//      00642000  74 63              JE   0x642065
//      00642002  e8 29 ab 03 00     CALL 0x67cb30
//      00642007  8b 78 5c           MOV  EDI,DWORD PTR [EAX+0x5c]
//      0064200a  85 ff              TEST EDI,EDI
//      0064200c  74 57              JE   0x642065
//      0064200e  8b 46 08           MOV  EAX,DWORD PTR [ESI+0x8]
//      00642011  50                 PUSH EAX
//      00642012  8b cf              MOV  ECX,EDI
//      00642014  e8 47 18 fd ff     CALL 0x613860
//      00642019  84 c0              TEST AL,AL
//      0064201b  74 48              JE   0x642065
//      0064201d  8b 54 24 10        MOV  EDX,DWORD PTR [ESP+0x10]
//      00642021  8b 44 24 0c        MOV  EAX,DWORD PTR [ESP+0xc]
//      00642025  6a 00              PUSH 0x0
//      00642027  8d 4c 24 0c        LEA  ECX,[ESP+0xc]
//      0064202b  51                 PUSH ECX
//      0064202c  52                 PUSH EDX
//      0064202d  50                 PUSH EAX
//      0064202e  8b cf              MOV  ECX,EDI
//      00642030  c7 44 24 18 00...  MOV  DWORD PTR [ESP+0x18],0x0
//      00642038  e8 13 0f fd ff     CALL 0x612f50
//      0064203d  8b 4c 24 08        MOV  ECX,DWORD PTR [ESP+0x8]
//      00642041  84 c0              TEST AL,AL
//      00642043  74 15              JE   0x64205a
//      00642045  8b f1              MOV  ESI,ECX
//      00642047  85 c9              TEST ECX,ECX
//      00642049  74 07              JE   0x642052
//      0064204b  8b 11              MOV  EDX,DWORD PTR [ECX]
//      0064204d  8b 42 04           MOV  EAX,DWORD PTR [EDX+0x4]
//      00642050  ff d0              CALL EAX
//      00642052  5f                 POP  EDI
//      00642053  8b c6              MOV  EAX,ESI
//      00642055  5e                 POP  ESI
//      00642056  83 c4 0c           ADD  ESP,0xc
//      00642059  c3                 RET
//      0064205a  85 c9              TEST ECX,ECX
//      0064205c  74 07              JE   0x642065
//      0064205e  8b 11              MOV  EDX,DWORD PTR [ECX]
//      00642060  8b 42 04           MOV  EAX,DWORD PTR [EDX+0x4]
//      00642063  ff d0              CALL EAX
//      00642065  33 c0              XOR  EAX,EAX
//      00642067  5f                 POP  EDI
//      00642068  5e                 POP  ESI
//      00642069  83 c4 0c           ADD  ESP,0xc
//      0064206c  c3                 RET
//
//    Those 157 bytes decode to exactly these 62 instructions and stop on
//    0x0064206c + 1, which is what fixes the body extent independently of the
//    committed record (body_start 0x00641fd0, body_end 0x0064206c,
//    body_span_bytes 157, size_bytes 157 -- all four agree, and the machine parse
//    record agrees at declared_count 62, unparsed 0, degraded false).
//
//  * The layouts of the three sub-objects are NOT shown by this body. It reads
//    one word of each and hands addresses around, so the sub-objects are opaque
//    byte runs here and the offsets the DIRECT CALLEES reach inside two of them
//    are recorded below as words, not as members:
//      - 0x00613860 reads the service at +0x1c and +0x20 and one byte at +0x84
//        (0x61386a, 0x61386e, 0x613863) and compares its own first argument
//        against the leading word of an element (0x613889);
//      - 0x00612f50 reads the service at +0x88 and +0x8c and one byte at +0x9c
//        (0x612f5b, 0x612f62, 0x612f54) and walks elements on a 0x10 stride
//        (0x612f8f LEA ECX,[EAX+0x10]).
//    Nothing in this set says what any of those words is FOR.
//
//  * No member is named. Every sub-object below is spelled field_<hex offset>,
//    which states where it lives and nothing about what it is for. The class
//    name SporepediaAssetDataOtdb is INFERRED, not machine-fixed: this target's
//    own record carries name "FUN_00641fd0" and class_type null. The name comes
//    from vtable co-membership -- this body's data-side xrefs are at 0x013ff6e4,
//    0x014627f4, 0x0147ca94, 0x0147cb5c, 0x0147cc4c, 0x0148912c and 0x0148944c,
//    each of which reads 0x00641fd0 in the image, and the tables at 0x013ff648
//    and 0x013ff6ac are the same two the record lists as the match basis for the
//    reconstructed neighbours 0x00641400, 0x00641460, 0x00641770, 0x006417b0,
//    0x006417c0, 0x00641810, 0x00641820 and 0x00641850, every one of which the
//    repository research queue names Sporepedia::cSPAssetDataOTDB::*.
//
//  * The 8-byte frame object and the resolved handle's table word are the two
//    things this body both writes and reads, and both are modelled as pointers
//    because that is the only way the machine uses them: the frame object is
//    passed BY ADDRESS to the slot +0x90 dispatch (0x00641ff5) and the resolved
//    word is dereferenced through ITS OWN leading word (0x0064204b, 0x0064205e).
//    Reading either as a value would be the two-level-dereference bug.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00641fd0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare
// MSVC keywords outright on this target, so the x86-32 attribute form is the
// portable spelling and the keyword form is kept for MSVC. Both are asserted by
// machine facts, not chosen for convenience:
//
//   PKG_SW1_00641FD0_THISCALL  this body and three of the four things it calls.
//     This body: 0x00641fd4 `MOV ESI,ECX` takes the receiver out of ECX, every
//     receiver access goes through ESI, 0x00641ffa puts the SAME object back in
//     ECX for the slot +0x90 dispatch, and the terminator is a bare `RET` on both
//     exits (0x00642059 and 0x0064206c, bytes c3) with no immediate, so the
//     cleanup side is zero bytes either way. 0x00613860 ends `C2 04 00` (RET
//     0x4, 0x6138a1), 0x00612f50 ends `C2 10 00` (RET 0x10 on both exits,
//     0x612fad and 0x61300f) and each of them takes its receiver in ECX
//     (0x613861 and 0x612f52 `MOV ESI,ECX`), so the callee owns the cleanup.
//   PKG_SW1_00641FD0_CDECL  0x0067cb30, the global getter. Its whole body is six
//     bytes -- `A1 70 CC 5F 01 C3`, i.e. `MOV EAX,ds:0x15fcc70; RET` -- with no
//     stack argument and no read of ECX, so it is cdecl with exactly zero
//     argument words.
#if defined(_MSC_VER)
#define PKG_SW1_00641FD0_THISCALL __thiscall
#define PKG_SW1_00641FD0_CDECL __cdecl
#else
#define PKG_SW1_00641FD0_THISCALL __attribute__((thiscall))
#define PKG_SW1_00641FD0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00641fd0 {

using Word = std::uint32_t;

// The 8-byte object the body's own frame carries at entry_ESP-8 .. entry_ESP-5
// and hands to the slot +0x90 dispatch BY ADDRESS.
//
//   00641fe1  OR  EAX,0xffffffff        materialises 0xffffffff (EAX is already
//                                       zero here, so the OR itself is dead)
//   00641fe5  MOV  DWORD PTR [ESP+0xc],EAX   with ESP = entry-20, so entry-8
//   00641fe9  MOV  DWORD PTR [ESP+0x10],EAX  with ESP = entry-20, so entry-4
//   00641ff5  LEA  ECX,[ESP+0xc]        with ESP = entry-20, so the ADDRESS
//                                       handed over is entry-8 -- one pointer
//                                       covering both words, which is why the
//                                       two words are one object here
//   0064201d  MOV  EDX,DWORD PTR [ESP+0x10]  with ESP = entry-20, so entry-4
//   00642021  MOV  EAX,DWORD PTR [ESP+0xc]   with ESP = entry-20, so entry-8
//
// The two words are re-read from the frame after the dispatch returns, so the
// values the dispatch wrote into the object are what the 0x00612f50 call gets --
// the body does not keep them in registers across the call.
struct HandlePair {
  Word field_00;
  Word field_04;
};
static_assert(sizeof(HandlePair) == 8, "0x00641ff5 hands one 8-byte address to the slot");
static_assert(offsetof(HandlePair, field_00) == 0, "entry-8");
static_assert(offsetof(HandlePair, field_04) == 4, "entry-4");

// The receiver. This body reads exactly three words of it and writes none:
//
//   00641fd6  MOV  EAX,DWORD PTR [ESI+0x3c]   the early-out value, returned
//                                            unchanged at 0x00642068
//   00641fed  MOV  EAX,DWORD PTR [ESI]        the table word, the FIRST level of
//                                            the slot +0x90 dispatch
//   0064200e  MOV  EAX,DWORD PTR [ESI+0x8]    the one word pushed as the first
//                                            stack argument of 0x00613860
//
// The machine-derived receiver record enumerates offsets [0, 8, 60] with register
// ECX, shape R-ALIAS, written_through 0 and bounds_only true -- i.e. it states
// where the body was seen reaching and not which member is which. So this type
// declares NO member: 0x04..0x07, 0x09..0x3b and 0x40 and beyond are never read
// or written here, and calling any of them a key store, a cache or a flag would
// be a member story this body's evidence does not carry. The receiver is an
// opaque run whose last byte the body touches is 0x3f, the last byte of the
// dword loaded at 0x00641fd6.
struct alignas(4) SporepediaAssetDataOtdb {
  std::array<std::uint8_t, 0x40> opaque_00;  // 0x00..0x3f
};

// The object the global getter returns. This body reads one word of it:
//
//   00642002  CALL 0x0067cb30               -> EAX is ds:0x15fcc70
//   00642007  MOV  EDI,DWORD PTR [EAX+0x5c]  the service, the receiver of the
//                                            next two calls
//
// The address 0x015fcc70 is NOT written in the reconstruction's function body:
// it is a data-segment address and this body contains no data operand at all,
// so naming it in the span would be a claim the body does not make. It is
// recorded here, in the header, and in the metadata sidecar instead. Nothing else
// of this object is reached, so the run ends one byte past that word.
struct alignas(4) ServiceRoot {
  std::array<std::uint8_t, 0x60> opaque_00;  // 0x00..0x5f
};

// The service: the receiver of 0x00613860 and 0x00612f50. This body passes it
// in ECX and never dereferences it. The offsets below are the two callees' own,
// read from their image bytes, and are recorded as values rather than as
// members: 0x00613860 touches +0x1c (0x61386a), +0x20 (0x61386e) and the byte
// +0x84 (0x613863); 0x00612f50 touches +0x88 (0x612f5b), +0x8c (0x612f62) and
// the byte +0x9c (0x612f54). 0x9c is the last byte either reaches, so the run is
// 0xa0 bytes. No other byte of the service is touched by anything in this set.
struct alignas(4) Service {
  std::array<std::uint8_t, 0xa0> opaque_00;  // 0x00..0x9f
};

// The object 0x00612f50 leaves in the frame word at entry_ESP-12, and the only
// thing this body does with it is read its own leading word and call the slot at
// +0x04 of that:
//
//   00642030  MOV  DWORD PTR [ESP+0x18],0x0   the frame word is zeroed, with
//                                            ESP = entry-36, so entry-12
//   0064203d  MOV  ECX,DWORD PTR [ESP+0x8]    the word is read back, with
//                                            ESP = entry-20, so entry-12
//   0064204b  MOV  EDX,DWORD PTR [ECX]        the first level of the acquire
//   0064204d  MOV  EAX,DWORD PTR [EDX+0x4]    the slot
//   (0x0064205e and 0x00642060 are the same two instructions on the other arm)
//
// The 0x10 bytes below are one leading word plus padding: 0x10 is a model
// rounding chosen so the run is a whole number of words, and nothing in this set
// reads the handle past its own +0x00.
struct alignas(4) Acquired {
  std::array<std::uint8_t, 0x10> opaque_00;  // 0x00..0x0f
};

// The slot the body dispatches through on ITSELF: 0x00641fed loads the table
// word out of the receiver's +0x00, 0x00641fef loads the slot word out of THAT
// at +0x90, and 0x00641ffc calls the register. The signature is taken from the
// call site, which is what the machine fixes: ECX = the receiver itself
// (0x00641ffa), one stack word = the address of the 8-byte frame object
// (0x00641ff9), and the return examined as a BYTE (0x00641ffe `TEST AL,AL`).
// Its declaring class is not fixed by this body: the word at 0x01462764+0x90 is
// 0x00641fd0 -- this body -- and the word at 0x01489090+0x90 is 0x006417d0, so
// the same slot holds a different function in a different table.
using ResolveSlot90 =
    std::uint8_t(PKG_SW1_00641FD0_THISCALL*)(SporepediaAssetDataOtdb*, HandlePair*);

// The slot the body dispatches through on the RESOLVED handle: 0x0064204b /
// 0x0064204d read the handle's own leading word and the slot at +0x04 of it, and
// 0x00642050 calls the register with ECX = the handle and no stack word. Its
// return value is dead on both arms -- 0x00642053 overwrites EAX with ESI on the
// true arm and 0x00642065 zeroes it on the false one -- so it is modelled as
// void and the model test asserts nothing about it.
using AcquireSlot04 = void(PKG_SW1_00641FD0_THISCALL*)(Acquired*);

// The tables the two dispatches read. A test can plant a distinct observer in
// every slot and see which index the reconstruction calls; 37 slots is the
// smallest run that covers index 36 (0x90 / 4) with a decoy either side.
static_assert(sizeof(void*) == 4, "this package is the 32-bit pointer model");
static_assert(sizeof(ResolveSlot90) == 4, "a slot is one address");
static_assert(offsetof(SporepediaAssetDataOtdb, opaque_00) == 0, "the receiver starts at its own +0x00");
static_assert(sizeof(SporepediaAssetDataOtdb) == 0x40, "0x3c + 4 is the last byte the body touches");
static_assert(sizeof(ServiceRoot) == 0x60, "0x5c + 4 is the last byte the body touches");
static_assert(sizeof(Service) == 0xa0, "0x9c is the last byte either callee touches");
static_assert(sizeof(Acquired) == 0x10, "the handle run ends one word past the table word");

// The displacements this body was seen reaching, as values.
//
//  * On the receiver: 0x3c is the early-out word (0x00641fd6), 0x00 is the table
//    word (0x00641fed) and 0x08 is the argument of 0x00613860 (0x0064200e).
//  * On the service root: 0x5c is the service word (0x00642007).
//  * On the receiver's table: 0x90 is the slot displacement (0x00641fef), index
//    36. It is NOT the index this body itself sits at in the table its own
//    xrefs name: reading 0x013ff6e4 in the image gives 0x00641fd0, which is
//    0x013ff6ac + 0x38, index 14. The two are provably independent.
//  * On the resolved handle's table: 0x04 is the slot displacement (0x0064204d
//    and 0x00642060), index 1.
constexpr std::size_t kReceiverCachedWordDisplacement = 0x3c;
constexpr std::size_t kReceiverTableDisplacement = 0x00;
constexpr std::size_t kReceiverArgumentDisplacement = 0x08;
constexpr std::size_t kServiceRootServiceDisplacement = 0x5c;
constexpr std::size_t kResolveSlotDisplacement = 0x90;
constexpr std::size_t kResolveSlotIndex = kResolveSlotDisplacement / sizeof(Word);  // 36
constexpr std::size_t kAcquireSlotDisplacement = 0x04;
constexpr std::size_t kAcquireSlotIndex = kAcquireSlotDisplacement / sizeof(Word);  // 1

// The two displacements inside the 8-byte frame object, and the value the body
// puts in both of them. 0xffffffff is the immediate of 0x00641fe1, the only
// instruction in the body that writes that constant, and the body then copies it
// into both words at 0x00641fe5 and 0x00641fe9.
constexpr std::size_t kHandlePairFirstDisplacement = 0x00;
constexpr std::size_t kHandlePairSecondDisplacement = 0x04;
constexpr Word kUnsetHandleWord = 0xffffffffu;

// INSTRUMENTATION, not a machine value. The frame word at entry_ESP-12 is
// written exactly once by this body (0x00642030, zero) and read back at
// 0x0064203d; the machine never initialises it, so the value it held before
// that store is indeterminate stack residue and no claim is made about it. The
// model seeds the local with this non-null marker purely so that the store at
// 0x00642030 is OBSERVABLE from the model test: the 0x00612f50 observer samples
// the word it is handed and must see null there, so a reconstruction that drops
// the store is refuted instead of passing on an accident of the initial value.
// The marker is never dereferenced by the reconstruction; if a defect left it in
// place the reconstruction would hand the callee this address, which is what
// makes the defect visible.
inline void* const kFrameSeedMarker = reinterpret_cast<void*>(0x0f00d00du);

// The only way the body under reconstruction touches any of the above: a word at
// a stated displacement, and a slot word out of a table word. A named member
// access would assert an identity the machine-derived receiver record cannot
// corroborate -- it is bounds_only, with offsets [0, 8, 60].
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                       displacement);
}

// The same read, as a reference, for the two stores the body makes into its own
// frame (0x00641fe5 and 0x00641fe9). A pointer return is not an lvalue, so the
// stores go through this instead; the address and the width are identical.
inline Word& word_ref(void* base, std::size_t displacement) {
  return *word_at(base, displacement);
}

// The second level of a two-level dispatch, as the body performs it: read one
// slot word out of a table word. The displacement is an argument rather than a
// `+ 0x..` so that the slot the reconstruction names is the slot the listing
// reads, not a displacement folded into a pointer expression.
inline void* load_slot(void* table, std::size_t displacement) {
  return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(table) + displacement);
}

// -- the three direct callees ------------------------------------------------
// Each is declared here, and none is defined here: the model test defines all
// three as observers. Every signature below is fixed by the callee's own bytes,
// re-read from the image for this package, not by its decompilation.

// 0x0067cb30, called once at 0x00642002 with no stack word and no receiver. Its
// entire body is `MOV EAX,ds:0x15fcc70; RET`, so it returns one global's value
// and touches nothing else. The convention is not decidable from its own bytes
// (zero arguments, bare RET, ECX never read); the cdecl spelling is used because
// the callee demonstrably takes no receiver.
extern "C" void* PKG_SW1_00641FD0_CDECL service_root_global_0067cb30(void);

// 0x00613860, called once at 0x00642014 with the receiver in ECX and one stack
// word -- the dword the body read at the receiver's +0x08. Terminator
// `C2 04 00` (0x6138a1), so the callee owns the one word. It reads that word at
// 0x613885 (`MOV ECX,[ESP+0xc]` with its own two pushes and its own cleanup,
// i.e. entry+4) and compares it UNSIGNED against the leading word of an array
// element (0x613889 `CMP ECX,[EAX]` / 0x61388b `JB`), and it returns a byte
// normalised to {0, 1} (`SETNE DL` at 0x61389a, `MOV AL,DL` at 0x61389e). The
// body only tests that byte for non-zero, so the declared return type is
// std::uint8_t and the model test drives 0x80 through it.
extern "C" std::uint8_t PKG_SW1_00641FD0_THISCALL service_key_present_00613860(
    Service* receiver, Word argument);

// 0x00612f50, called once at 0x00642038 with the receiver in ECX and FOUR stack
// words, terminator `C2 10 00` on both exits (0x612fad, 0x61300f), so the callee
// owns all sixteen bytes. Argument order is fixed by this body's own push
// sequence and by the callee's own reads, not by either decompilation: the pushes
// run 0x0 (0x00642025), the address of the frame word (0x00642027/0x0064202b),
// then the frame's second word (0x0064202c) and its first word (0x0064202d), so
// the first stack word is the frame's FIRST word, the second is its SECOND word,
// the third is the out-pointer and the fourth is the literal zero. The callee
// reads its first argument as a dword at 0x612f7c and takes its address at
// 0x612f69, and it may store through one of its pointer arguments at 0x612fec.
// It returns a byte normalised to {0, 1} (`XOR AL,AL` at 0x612faa, `MOV AL,0x1`
// at 0x61300c).
extern "C" std::uint8_t PKG_SW1_00641FD0_THISCALL service_handle_resolve_00612f50(
    Service* receiver, Word first, Word second, void** out, Word fourth);

// FUN_00641fd0 @ 0x00641fd0.
//
// __thiscall, receiver in ECX, NO ordinary stack argument, bare `RET` on both
// exits, two saved registers (ESI pushed at 0x00641fd3, EDI at 0x00641fe4, both
// popped on every exit). The terminator is machine-observed (0x00642059 and
// 0x0064206c, bytes c3) and the argument count is not a guess: the epilogue pops
// EDI then ESI and `ADD ESP,0xc` (0x00642067..0x00642069) lands ESP back on the
// entry value, and a `RET` with no immediate consumes only the return address.
// The record agrees (stack_arguments.derived_slots 0, observed_slots 0,
// cleanup.bytes 0, side "caller", ret_form "RET").
//
// Return type is void*. Three exits, three different words in EAX, and no single
// C type fits all three: 0x00642068 returns the receiver's own +0x3c word
// unchanged, 0x00642053 returns the word the callee left in the frame's
// out-slot, and 0x00642065 returns the literal 0. void* is the only declaration
// under which all three compile, and it is the width the machine fixes. The
// record's own return claim is the string "integral_in_EAX" (abi.return_semantics
// and abi_derived.return.register_class "integral"), which is a claim about the
// register and not about a C type; see the sidecar's unresolved_questions.
extern "C" void* PKG_SW1_00641FD0_THISCALL sporepedia_cached_handle_00641fd0(
    SporepediaAssetDataOtdb* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641fd0
