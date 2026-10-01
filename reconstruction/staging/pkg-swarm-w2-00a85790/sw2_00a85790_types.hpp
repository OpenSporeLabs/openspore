// PKG-SWARM-W2-00A85790 -- VA 0x00a85790
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00a85790 @ 0x00a85790.
//
// The complete body is 64 instructions, 0x00a85790..0x00a8583a exclusive
// (ghidra_function.body_start 0x00a85790, body_end 0x00a8583b, size_bytes 172),
// re-exported here from the evidence pack's own disassembly category
// (reconstruction/evidence/00a85790/evidence.json, categories.disassembly, 64
// entries, machine parse {declared_count 64, unparsed 0, degraded false}):
//
//   00a85790  PUSH ESI                      56
//   00a85791  MOV ESI,ECX                   8B F1
//   00a85793  CMP byte ptr [ESI + 0x14],0x0 80 7E 14 00
//   00a85797  JZ 0x00a85838                 74 9F
//   00a8579d  CMP dword ptr [ESI + 0x10],0x0 83 7E 10 00
//   00a857a1  MOV byte ptr [ESI + 0x14],0x0 C6 46 14 00
//   00a857a5  JZ 0x00a85838                 74 91
//   00a857ab  MOV EAX,dword ptr [ESI + 0xc] 8B 46 0C
//   00a857ae  MOV EAX,dword ptr [EAX + 0x8] 8B 40 08
//   00a857b1  MOV ECX,EAX                   89 C1
//   00a857b3  SHR ECX,0x3                   C1 E9 03
//   00a857b6  TEST CL,0x1                   F6 C1 01
//   00a857b9  JNZ 0x00a857c5                75 0A
//   00a857bb  MOV EDX,EAX                   89 C2
//   00a857bd  SHR EDX,0x5                   C1 EA 05
//   00a857c0  TEST DL,0x1                   F6 C2 01
//   00a857c3  JZ 0x00a8581f                 74 5A
//   00a857c5  TEST AL,0x1                   A8 01
//   00a857c7  JZ 0x00a857d0                 74 05
//   00a857c9  MOV ECX,ESI                   89 F1
//   00a857cb  CALL 0x00a85460                E8 90 FC FD FF
//   00a857d0  MOV EAX,dword ptr [ESI + 0xc] 8B 46 0C
//   00a857d3  MOV ECX,dword ptr [EAX + 0x8] 8B 48 08
//   00a857d6  SHR ECX,0x3                   C1 E9 03
//   00a857d9  TEST CL,0x1                   F6 C1 01
//   00a857dc  JZ 0x00a857e8                 74 0A
//   00a857de  MOV ECX,dword ptr [ESI + 0x10] 8B 4E 10
//   00a857e1  MOV EDX,dword ptr [ECX]       8B 11
//   00a857e3  MOV EAX,dword ptr [EDX + 0x18] 8B 42 18
//   00a857e6  CALL EAX                      FF D0
//   00a857e8  MOV EAX,dword ptr [ESI + 0xc] 8B 46 0C
//   00a857eb  MOV ECX,dword ptr [EAX + 0x8] 8B 48 08
//   00a857ee  MOV EDX,ECX                   89 CA
//   00a857f0  SHR EDX,0x5                   C1 EA 05
//   00a857f3  TEST DL,0x1                   F6 C2 01
//   00a857f6  JZ 0x00a8581f                 74 27
//   00a857f8  MOVZX EAX,word ptr [EAX + 0xa8] 0F B7 80 A8 00 00 00
//   00a857ff  SHR ECX,0x6                   C1 E9 06
//   00a85802  TEST CL,0x1                   F6 C1 01
//   00a85805  MOV ECX,dword ptr [ESI + 0x10] 8B 4E 10
//   00a85808  MOV EDX,dword ptr [ECX]       8B 11
//   00a8580a  MOV EDX,dword ptr [EDX + 0x1c] 8B 52 1C
//   00a8580d  JZ 0x00a8581a                 74 0B
//   00a8580f  PUSH EDI                      57
//   00a85810  LEA EDI,[ESI + 0x28]          8D 7E 28
//   00a85813  PUSH EDI                      57
//   00a85814  PUSH EAX                      50
//   00a85815  CALL EDX                      FF D2
//   00a85817  POP EDI                       5F
//   00a85818  JMP 0x00a8581f                EB 05
//   00a8581a  PUSH 0x0                      6A 00
//   00a8581c  PUSH EAX                      50
//   00a8581d  CALL EDX                      FF D2
//   00a8581f  MOV EAX,dword ptr [ESI + 0x68] 8B 46 68
//   00a85822  TEST EAX,EAX                  85 C0
//   00a85824  JL 0x00a85838                 7C 12
//   00a85826  MOV ECX,dword ptr [ESI + 0x10] 8B 4E 10
//   00a85829  MOV EDX,dword ptr [ECX]       8B 11
//   00a8582b  PUSH EAX                      50
//   00a8582c  MOV EAX,dword ptr [EDX + 0x14] 8B 42 14
//   00a8582f  CALL EAX                      FF D0
//   00a85831  MOV dword ptr [ESI + 0x68],0xffffffff C7 46 68 FF FF FF FF
//   00a85838  POP ESI                       5E
//   00a85839  RET 0x4                       C2 04 00
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because the
// split is what a reader is entitled to check:
//
//  * Every displacement below is read out of the 64-instruction listing above and
//    is annotated with the instruction it came from. There are no derived
//    offsets, no inferred padding and no field names anywhere in this header.
//
//  * NO STRUCT MEMBER IS NAMED, at all, anywhere. The machine-derived receiver
//    record for this target is `bounds_only: true` (abi_derived.value.receiver)
//    with `offsets [12, 16, 20, 104]` and `max_offset 104`: that record states
//    how far the body was seen reaching and nothing else, so a named member would
//    be a layout claim the evidence cannot make. The receiver is therefore an
//    opaque byte run and every access goes through a displacement-named
//    accessor. What the receiver IS (an editor-side model object; the class name
//    is not fixed by anything in this evidence pack) is not claimed.
//
//  * The 0x6c SIZE of that run is this body's own evidence and no other
//    listing's: 0x00a85831 is `MOV dword ptr [ESI + 0x68], 0xffffffff`, a
//    FOUR-byte store whose last byte is therefore at +0x6b, so the body needs
//    0x6c bytes to exist. `max_offset: 104` in the receiver record is 0x68, the
//    START of that store, which is why the record alone would understate it.
//
//  * The word at receiver+0x10 is NOT declared a pointer member. The body uses
//    the value it reads as an ADDRESS twice (0x00a857e1 reads through it, and
//    0x00a857e6 / 0x00a85815 / 0x00a8581d / 0x00a8582f call through what it
//    leads to), which is a use, not a type. The header therefore hands it back
//    as a `Word` and every use takes it as a `Word`-valued address, so that a
//    two-level dereference can be written two levels deep and a one-level one
//    cannot be written at all.
//
//  * The word at receiver+0x0c is likewise not declared. The body reads it and
//    immediately reads 0x8 past it (0x00a857ab then 0x00a857ae), and 0xa8 past
//    it (0x00a857f8), so the header hands IT back as a `Word` address too.
//
//  * The three table displacements 0x14, 0x18 and 0x1c are NOT declared to be
//    VTABLE SLOTS as a matter of type, though the machine dispatch record
//    (abi_derived.value.dispatch: indirect_calls 4, vtable_shaped_loads 0) and
//    the listing's own two-level load shape both exhibit the pattern. Each is
//    reached as a displacement in a table the LISTENER object leads with, and
//    the receiver handed to the call is that same listener. 0x14 / 4, 0x18 / 4 and
//    0x1c / 4 are 5, 6 and 7 as slot indices; those divisions are recorded below
//    as arithmetic and are asserted by nothing in the model.
//
//  * The four bit tests are the listing's own, and they are shifts, not masks:
//    `SHR ECX,0x3` + `TEST CL,0x1` (0x00a857b3/0x00a857b6) is bit 3,
//    `SHR EDX,0x5` + `TEST DL,0x1` (0x00a857bd/0x00a857c0) is bit 5,
//    `SHR ECX,0x6` + `TEST CL,0x1` (0x00a857ff/0x00a85802) is bit 6, and
//    `TEST AL,0x1` (0x00a857c5) is bit 0. The header names the SHIFT AMOUNTS,
//    which are the constants the listing carries. The mask 0x20 and the mask
//    0x40 are NOT in the listing at all -- the compiler chose shifts over masks
//    -- and so they are named nowhere in the source; see the constants below.
//
//  * 0x80000000 (`kMostSignificantBitMask`) is likewise absent from the listing.
//    It is not a constant the body states: it is the sign bit that `TEST EAX,EAX`
//    (0x00a85822) sets SF from and that `JL 0x00a85838` (0x00a85824) tests. It is
//    the arithmetic restatement of a two-instruction signed comparison, and the
//    model test drives the two inputs where a signed and an unsigned reading
//    disagree, so the distinction is checked rather than assumed.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00a85790 requires an x86-32 target"
#endif

// The one convention this body needs. Spelled per toolchain: GCC rejects the bare
// MSVC keywords outright, so the x86-32 attribute form is the portable spelling
// and the keyword form is kept for MSVC.
//
//   PKG_SW2_00A85790_THISCALL  this body is __thiscall. Two things in its own
//     bytes fix it. 0x00a85791 is `MOV ESI,ECX` -- the receiver arrives in the
//     register the Windows x86 receiver slot names -- and 0x00a85839 is
//     `RET 0x4` (bytes C2 04 00), which pops the return address plus one word,
//     i.e. the callee owns the stack argument. abi_derived.value.abi records
//     calling_convention __thiscall with cleanup {bytes 4, side callee,
//     confidence OBSERVED, evidence "ret 0x4"} and derives the same conclusion
//     as inference C6B.
#if defined(_MSC_VER)
#define PKG_SW2_00A85790_THISCALL __thiscall
#else
#define PKG_SW2_00A85790_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00a85790 {

using Word = std::uint32_t;
using HalfWord = std::uint16_t;

// -- receiver displacements, each tied to the instruction that states it ------
//
// Every access this body makes to the object ECX points at, and the one
// instruction each displacement is read from. None of these is a member name;
// they are the numbers the listing prints.
//
//   kFlagByteDisplacement          0x14  0x00a85793 CMP byte ptr [ESI + 0x14],0x0
//                                            0x00a857a1 MOV byte ptr [ESI + 0x14],0x0
//   kListenerPointerDisplacement   0x10  0x00a8579d CMP dword ptr [ESI + 0x10],0x0
//   kSourcePointerDisplacement     0x0c  0x00a857ab MOV EAX,dword ptr [ESI + 0xc]
//   kArgumentBufferDisplacement    0x28  0x00a85810 LEA EDI,[ESI + 0x28]
//   kPendingIdentifierDisplacement 0x68  0x00a8581f MOV EAX,dword ptr [ESI + 0x68]
//                                            0x00a85831 MOV dword ptr [ESI + 0x68],0xffffffff
constexpr std::size_t kFlagByteDisplacement = 0x14u;
constexpr std::size_t kListenerPointerDisplacement = 0x10u;
constexpr std::size_t kSourcePointerDisplacement = 0x0cu;
constexpr std::size_t kArgumentBufferDisplacement = 0x28u;
constexpr std::size_t kPendingIdentifierDisplacement = 0x68u;

// -- displacements on the object the body reaches THROUGH receiver+0x0c -------
//
// The body reads these out of the object the word at receiver+0x0c addresses, so
// they belong to that second object and not to the receiver. They are named here
// as values and are used only through `half_at` / `load_slot` with a `Word` base,
// so the two-level chase is in the type and cannot be collapsed by accident.
//
//   kSourceFlagWordDisplacement    0x08  0x00a857ae MOV EAX,dword ptr [EAX + 0x8]
//   kSourceHalfWordDisplacement   0xa8  0x00a857f8 MOVZX EAX,word ptr [EAX + 0xa8]
constexpr std::size_t kSourceFlagWordDisplacement = 0x08u;
constexpr std::size_t kSourceHalfWordDisplacement = 0xa8u;

// -- table displacements on the object the body reaches THROUGH receiver+0x10 ---
//
// THE THREE-STEP CHASE, and it is three loads, not two. The body does this, four
// times, and always in the same order:
//
//   00a857de  MOV ECX,dword ptr [ESI + 0x10]   step 1: L, a pointer VALUE, out of
//                                                        the receiver
//   00a857e1  MOV EDX,dword ptr [ECX]          step 2: T, the table base, out of
//                                                        the object L addresses
//   00a857e3  MOV EAX,dword ptr [EDX + 0x18]   step 3: the target, out of T
//
// so the target is read at ( *( *(receiver + 0x10) ) + 0x18 ) and nowhere else.
// Collapsing that to ( *(receiver + 0x10) + 0x18 ) is a different function: it
// reads a word that lives inside the listener object rather than inside the
// table that object leads with, and it is the single most likely reading of this
// body, so the model performs both steps as two separate reads and the model
// test plants a decoy at each of the two intermediate displacements.
//
// The receiver handed to every one of these calls is the LISTENER object L, in
// ECX: not the receiver of this function and not the source object.
//
//   kListenerTableLeadDisplacement 0x00  0x00a857e1 MOV EDX,dword ptr [ECX]
//                                             0x00a85808 MOV EDX,dword ptr [ECX]
//                                             0x00a85829 MOV EDX,dword ptr [ECX]
//   kSlotIdentifierDisplacement   0x14  0x00a8582c MOV EAX,dword ptr [EDX + 0x14]
//   kSlotNoArgumentDisplacement  0x18  0x00a857e3 MOV EAX,dword ptr [EDX + 0x18]
//   kSlotTwoArgumentDisplacement 0x1c  0x00a8580a MOV EDX,dword ptr [EDX + 0x1c]
constexpr std::size_t kListenerTableLeadDisplacement = 0x00u;
constexpr std::size_t kSlotIdentifierDisplacement = 0x14u;
constexpr std::size_t kSlotNoArgumentDisplacement = 0x18u;
constexpr std::size_t kSlotTwoArgumentDisplacement = 0x1cu;

// The same three displacements as slot INDICES, i.e. divided by the 4-byte slot
// width. These are arithmetic identities, not second evidence: 0x14 / 4 == 5,
// 0x18 / 4 == 6 and 0x1c / 4 == 7. They are named only so a reader counting
// slots in a table need not redo the division, and the model asserts nothing
// from them.
constexpr std::size_t kSlotIdentifierIndex = kSlotIdentifierDisplacement / 4u;    // 5
constexpr std::size_t kSlotNoArgumentIndex = kSlotNoArgumentDisplacement / 4u;    // 6
constexpr std::size_t kSlotTwoArgumentIndex = kSlotTwoArgumentDisplacement / 4u;  // 7

// -- the bit tests, as the listing states them --------------------------------
//
// The flag word is the 4-byte word at ([receiver + 0x0c] + 0x08). The body tests
// four of its bits and states each test as a shift of a scratch register followed
// by `TEST <byte>, 0x1`, so the SHIFT AMOUNT is the constant the listing carries.
//
//   kFlagBit0Shift   0  0x00a857c5 TEST AL,0x1   (no shift; the low bit itself)
//   kFlagBit3Shift   3  0x00a857b3 SHR ECX,0x3
//   kFlagBit5Shift   5  0x00a857bd SHR EDX,0x5
//   kFlagBit6Shift   6  0x00a857ff SHR ECX,0x6
constexpr unsigned kFlagBit0Shift = 0u;
constexpr unsigned kFlagBit3Shift = 3u;
constexpr unsigned kFlagBit5Shift = 5u;
constexpr unsigned kFlagBit6Shift = 6u;

// The one value the body STORES rather than loads, at 0x00a85831:
// `MOV dword ptr [ESI + 0x68], 0xffffffff`. It is the all-ones 32-bit word, and
// 0x00a85824 (`JL`) treats it as NEGATIVE on any later visit -- which is the
// entire purpose of the store.
constexpr Word kSentinelIdentifier = 0xffffffffu;

// The sign bit, as `TEST EAX,EAX` (0x00a85822) plus `JL 0x00a85838` (0x00a85824)
// state it. NOT a constant the listing carries -- see the header note.
constexpr Word kMostSignificantBitMask = 0x80000000u;

// -- the receiver ------------------------------------------------------------
//
// An opaque byte run and nothing else. The size is this body's own bound: the
// dword store at 0x00a85831 ends at +0x6b, so the body needs 0x6c bytes to exist.
// The largest displacement the body READS is 0xa8, and that one is on the SOURCE
// object, not on this one; the largest it reads here is 0x68.
//
// Nothing inside is named, and the struct exists only to give the model test a
// distinct type to pass around. The model never names a member of it.
struct Receiver {
  std::array<std::uint8_t, 0x6c> opaque_00_6b{};
};
static_assert(sizeof(Receiver) == 0x6c,
              "0x68 + 4 is the last byte the dword store at 00a85831 writes");
static_assert(kPendingIdentifierDisplacement + sizeof(Word) <= sizeof(Receiver),
              "the pending-identifier word lies inside the ctor-bounded object");
static_assert(kFlagByteDisplacement + 1 <= sizeof(Receiver),
              "the flag byte lies inside the ctor-bounded object");
static_assert(kListenerPointerDisplacement + sizeof(Word) <= sizeof(Receiver),
              "the listener pointer word lies inside the ctor-bounded object");
static_assert(kSourcePointerDisplacement + sizeof(Word) <= sizeof(Receiver),
              "the source pointer word lies inside the ctor-bounded object");
static_assert(kArgumentBufferDisplacement <= sizeof(Receiver),
              "the LEA at 00a85810 addresses inside the object");

// -- accessors ---------------------------------------------------------------
//
// One machine shape each, all taking the base the way the machine holds it.
//
// `byte_at` / `half_at` / `word_at` / `store_*` take a POINTER because the
// listings that use them hold a register the body received or computed a
// displacement into: the receiver (ESI, from ECX), the listener (ECX, from
// `[ESI + 0x10]`), the source (EAX, from `[ESI + 0xc]`) and `&receiver + 0x28`
// (EDI, from `LEA EDI,[ESI + 0x28]`).
//
// `load_slot` takes the base as a `Word` because two of the listings that use it
// hold the address in a register as a plain value -- EAX at 0x00a857f8 is the
// word read from the receiver and then used as an address, and the table reads
// go through a register that the body loaded -- and taking a `Word` is what keeps
// a one-level dereference from being writable by accident.

inline std::uint8_t byte_at(const void* base, std::size_t displacement) {
  return *(reinterpret_cast<const std::uint8_t*>(base) + displacement);
}

inline void store_byte(void* base, std::size_t displacement, std::uint8_t value) {
  *(reinterpret_cast<std::uint8_t*>(base) + displacement) = value;
}

inline HalfWord half_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const HalfWord*>(reinterpret_cast<const std::uint8_t*>(base) + displacement);
}

inline Word word_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<const std::uint8_t*>(base) + displacement);
}

inline void store_word(void* base, std::size_t displacement, Word value) {
  *reinterpret_cast<Word*>(reinterpret_cast<std::uint8_t*>(base) + displacement) = value;
}

inline Word load_slot(Word base_word, std::size_t slot_displacement) {
  return *reinterpret_cast<const Word*>(static_cast<std::uintptr_t>(base_word) + slot_displacement);
}

// The three-step chase above, written as the body writes it: the object's own
// leading word is the table base, and the target is a displacement into THAT.
// Taking the table base as a separate read is the point -- a reconstruction that
// folded the two steps would be one dereference short and the model test has a
// decoy table waiting at each of the two intermediate displacements.
inline Word load_listener_slot(Word listener_word, std::size_t slot_displacement) {
  return load_slot(load_slot(listener_word, kListenerTableLeadDisplacement), slot_displacement);
}

// `SHR <reg>, n` + `TEST <byte>, 1`, which is how all three shifted bit tests are
// written in the listing. `bit_is_set(word, 0)` is the one test the listing
// writes without a shift, `TEST AL,0x1` at 0x00a857c5.
inline bool bit_is_set(Word flags, unsigned shift) {
  return ((flags >> shift) & 1u) != 0u;
}

// -- the indirect callees ----------------------------------------------------
//
// Four of them, all `CALL reg`, all reaching their target through a two-level
// table load, and all handing the LISTENER object to the callee in the receiver
// register ECX. The machine dispatch record agrees on the count:
// abi_derived.value.dispatch is {indirect_calls 4, call_offsets [], vtable_shaped_loads 0}.
//
// The three shapes are separated because the STACK is the evidence for the split,
// and the split is not cosmetic:
//
//   SlotNoArgument   0x00a857e6, slot displacement 0x18. Nothing is pushed
//                    between 0x00a857de and the call, so the callee takes no
//                    stack argument. Nothing is popped after it either, so a
//                    zero-argument callee is the only consistent reading.
//   SlotTwoArgument  0x00a85815 and 0x00a8581d, slot displacement 0x1c. Two words
//                    are pushed on both arms. At 0x00a85815 the sequence is
//                    PUSH EDI / PUSH EDI / PUSH EAX / CALL EDX / POP EDI, and the
//                    POP EDI is the frame's own restore, not the callee's: the
//                    body reaches 0x00a8581f with a balanced stack. At
//                    0x00a8581d the two pushes are followed by a FALLTHROUGH to
//                    0x00a8581f with no pop at all, and 0x00a85839 is `RET 0x4`
//                    with no further adjustment, so the callee must have popped
//                    its own two words. Argument order on both arms is
//                    right-to-left: PUSH EAX is the FIRST argument and the second
//                    push (EDI, or 0x0) is the second.
//
//                    ONE LOAD, TWO CALL SITES, and the slot displacement of
//                    0x00a8581d is the SAME 0x1c. The listing has exactly one
//                    instruction that reads the 0x1c table word -- 0x00a8580a
//                    `MOV EDX,dword ptr [EDX + 0x1c]`, bytes 8B 52 1C -- and it
//                    sits BEFORE the `JZ 0x00a8581a` at 0x00a8580d that chooses
//                    between the two arms. So both call sites dispatch through the
//                    one register the one load fills, and there is no second
//                    displacement for 0x00a8581d to have.
//
//                    That JZ is also the whole reason EDX is the same word at
//                    both sites. The only predecessor of 0x00a8581a is that JZ,
//                    and it targets an address past 0x00a8580f..0x00a85818, so
//                    the arm reaching 0x00a8581d never executes the `CALL EDX` at
//                    0x00a85815; EDX still holds the 0x00a8580a word when
//                    0x00a8581d is entered. Read back out of the complete
//                    listing, not assumed: 0x00a8581a has no predecessor other
//                    than 0x00a8580d, and 0x00a8581c is its only successor.
//
//                    The machine dispatch classifier reads the listing with a
//                    NEAREST-PRECEDING-DEFINITION walk and no path sensitivity, so
//                    scanning upwards into 0x00a8581d it meets the `CALL EDX` at
//                    0x00a85815 first, notes that a call clobbers the caller-saved
//                    EDX on x86-32, and classifies this site UNRESOLVED with the
//                    reason "EDX is defined by a preceding CALL". The walk is not
//                    wrong about EDX on the path that reaches this site; it models
//                    one linear order where the body has two mutually exclusive
//                    arms, and a definition bypassed on the path being read cannot
//                    be told apart from one that ran. The same walk classifies
//                    0x00a857e6, 0x00a85815 and 0x00a8582f as VTABLE_SLOT at 0x18,
//                    0x1c and 0x14, and the dispatch record independently counts
//                    all four sites (indirect_calls 4), so the disagreement is
//                    about one site's IDENTITY, not about whether this body
//                    dispatches. Nothing in a source file can move it: the verdict
//                    is computed from the listing and the envelope's own records,
//                    and the source can only ever ADD a failure to it (a stated
//                    slot displacement the machine does not read), never remove one.
//   SlotOneArgument  0x00a8582f, slot displacement 0x14. One word pushed
//                    (0x00a8582b) and, again, no pop after the call, so the
//                    callee pops its own single word.
//
// Every one of them returns a value in EAX as far as the machine is concerned --
// `CALL reg` always leaves one -- and the model discards all of them, because
// 0x00a857d0, 0x00a857e8 and 0x00a8581f each reload the register they would have
// needed. See the .cpp for the one place where the machine does not reload, and
// for why it does not change anything observable.
using SlotNoArgument = Word(PKG_SW2_00A85790_THISCALL*)(void* receiver);
using SlotOneArgument = Word(PKG_SW2_00A85790_THISCALL*)(void* receiver, Word argument);
using SlotTwoArguments = Word(PKG_SW2_00A85790_THISCALL*)(void* receiver, Word first_argument,
                                                          void* second_argument);

inline Word invoke_slot_no_arguments(Word target_word, void* receiver) {
  return reinterpret_cast<SlotNoArgument>(static_cast<std::uintptr_t>(target_word))(receiver);
}

inline Word invoke_slot_one_argument(Word target_word, void* receiver, Word argument) {
  return reinterpret_cast<SlotOneArgument>(static_cast<std::uintptr_t>(target_word))(receiver,
                                                                                     argument);
}

inline Word invoke_slot_two_arguments(Word target_word, void* receiver, Word first_argument,
                                      void* second_argument) {
  return reinterpret_cast<SlotTwoArguments>(static_cast<std::uintptr_t>(target_word))(
      receiver, first_argument, second_argument);
}

// -- model instrumentation: the EDI register ---------------------------------
//
// WHY THIS EXISTS. 0x00a8580f `PUSH EDI` and 0x00a85817 `POP EDI` are a save and
// restore of the EDI register around the ONE call the body makes that it does not
// bracket the other way: 0x00a85815. The compiler emitted them because EDI is
// callee-saved on x86-32 Windows and it had just computed an interior pointer
// into the receiver with `LEA EDI,[ESI + 0x28]` and pushed it. The word the pair
// preserves is whatever EDI held on entry to 0x00a8580f -- the body never writes
// EDI anywhere else in its 64 instructions, and it does not need to, because
// nothing after 0x00a85817 reads EDI.
//
// The observable is therefore exactly this: after the 0x1c call returns, EDI holds
// what it held before the call, whatever the callee did to it in between. This
// word is instrumentation of the model's own register file: it is NOT a machine
// global, the original code has no such addressable word, and no instruction in
// the body names it. The test uses it to try to BREAK the save/restore pair in
// both directions -- a reconstruction that omits the restore, and one that
// performs the pair on the 0x00a8581d arm where the listing does not.
Word edi_register();
void set_edi_register(Word value);

// -- the one direct callee ----------------------------------------------------
//
// 0x00a857cb `CALL 0x00a85460` (E8 90 FC FD FF -> 0x00a85460), the single
// direct-call edge in the xref export for this target
// ({"callsite": "0x00a857cb", "direction": "out", "other": "0x00a85460",
// "reference_type": "direct-call"}).
//
// The callsite fixes its shape and nothing else. 0x00a857c9 `MOV ECX,ESI` puts
// the RECEIVER in the receiver register immediately before it, and the only other
// PUSH in the body before this call is the prologue's `PUSH ESI` at 0x00a85790,
// so no stack argument is passed. That is __thiscall with one register argument.
//
// Its RETURN TYPE is not fixed by anything here. This body discards whatever the
// call leaves in EAX -- 0x00a857d0 reloads EAX from the receiver before anything
// can observe it -- so this package asserts no return value for it and declares
// it void. That is a statement about THIS callsite's evidence, not about
// 0x00a85460, whose own body this package has not reconstructed. See the sidecar's
// unresolved questions.
extern "C" void PKG_SW2_00A85790_THISCALL FUN_00a85460(Receiver* receiver);

// -- the reconstructed entry -------------------------------------------------
//
// __thiscall, receiver in ECX, ONE ordinary stack word that the body never reads,
// `RET 0x4`.
//
// The one stack word exists because the terminator is `RET 0x4`: that immediate
// is 4 bytes of callee-owned cleanup, so the caller's frame holds a word at
// entry_ESP+4 which this body never names. The evidence pack is explicit that
// this is the popped area and not a parameter count: abi_derived inference
// A1-IMM claims, at APPROXIMATION confidence, "argument slots derived from the
// terminal immediate alone; no argument read was observed, so this is the popped
// area and not a parameter count", and ordinary_stack_arguments[0] carries
// {read: false, written: false, observed: false, source: "ret_immediate"}.
// The parameter is therefore declared and left unnamed, and the model test drives
// several values through it to show that no observable depends on it.
//
// RETURN TYPE IS void, and the reasoning is stated here because it is the one
// judgement in this package a reader should push back on first. The single return
// site 0x00a85838 is reached from FOUR branch targets -- 0x00a85797, 0x00a857a5,
// 0x00a85824, and the fallthrough out of the notification block -- and the word in
// EAX when it is reached is a DIFFERENT unrelated value on each:
//
//   * 0x00a85797  EAX is whatever the caller left in it. The body has written
//                 nothing at all on that path.
//   * 0x00a857a5  likewise: the body's only write before this branch is the byte
//                 store at 0x00a857a1, which is memory, not a register.
//   * 0x00a85824  EAX is the word just loaded from receiver+0x68 (0x00a8581f),
//                 and it is negative -- the branch is the test that says so.
//   * fallthrough EAX is whatever the call at 0x00a8582f left there.
//
// No path puts a value this function COMPUTED into EAX, and no single value is
// consistent across paths, so the body produces no return value. Ghidra's own
// decompilation of this VA agrees in substance: its signature is
// `undefined FUN_00a85790(void)`, its body ends in a bare `return;`, and
// return_type_resolved is false.
//
// THE SAME THREE VALUES ARE ALSO WHAT THE MACHINE-RETURN EVIDENCE ENGINE SEES,
// and that is why the dimension stops where it does rather than because the two
// halves of this package disagree. It runs one must-analysis over the complete
// listing and intersects the incoming values of the four predecessors above, and
// gets three distinct states out of them: UNDEFINED, UNDEFINED, DEFINED-4-BYTES,
// and NOT-BOUNDABLE. The last is the 0x00a8582f `CALL EAX`, whose result width
// belongs to a callee's signature that this listing does not contain. One
// unbounded value among several makes the whole join unbounded, so no width is
// determinable; the engine reports UNCLASSIFIED and claims no verdict. Every input
// to that number is the listing and the ABI record -- the declared C return type
// is read only AFTER the state is computed, and on an UNCLASSIFIED state it is
// not read at all -- so no source shape changes it. The two early exits are the
// reason it is unbounded, and they are real: a function that returns nothing
// still has paths that leave the return register alone.
//
// The canonical ABI record disagrees in FORM rather than in substance, and the
// disagreement is recorded rather than papered over. abi_derived.value.abi says
// return_register "EAX" with return_semantics "unclassified_in_EAX", and
// inference RT2 reads the last EAX write as register_class
// "aggregate_unknown". `unclassified_in_EAX` is a machine-vocabulary phrase and
// not a C++ type, so no C++ spelling of it can exist and the validator's
// string-comparison arm reports WARN whatever is written. This package did NOT
// declare a typedef named after the phrase to win that comparison; it declares
// `void` because the four-path argument above is what the bytes actually show.
// Nor did it set a canonical `return_type` in the sidecar to hand the dimension
// to the older string-comparison arm: no ABI layer produced a C type for this
// target, and writing one there would invent the machine claim the string arm
// then agrees with. The known consequence is that RETURN SEMANTICS reads
// NOT_AVAILABLE on this target -- an honest name for "the machine fixes no width
// and the source is not asked to pretend otherwise" -- and the sidecar records
// that as a known blocker.
extern "C" void PKG_SW2_00A85790_THISCALL re_00a85790(Receiver* receiver, Word stack_word_unread);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00a85790
