// PKG-SWARM-W2-00A980B0 -- VA 0x00a980b0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00a980b0 @ 0x00a980b0.
//
// THE COMPLETE BODY: 112 instructions, 325 bytes, 0x00a980b0..0x00a981f4
// inclusive (0x00a981f5 is the first INT3 pad byte). Re-read from the image for
// this package rather than taken on trust:
//
//   objdump -D -b binary -m i386 -M intel --adjust-vma=0x00a980b0 <325 bytes>
//
// agrees instruction for instruction with ghidra_function (body_start
// 0x00a980b0, size_bytes 325) and with the committed disassembly listing (112
// instructions). The record's body_end 0x00a981f4 is the LAST body byte, not an
// exclusive end: the terminator at 0x00a981f2 is `C2 04 00`, so the exclusive end
// is 0x00a981f5. Nothing is truncated and no byte outside 0x00a980b0..0x00a981f4
// is claimed by this package.
//
// THE FRAME, resolved once against entry ESP, because every displacement in the
// body is stated against the CURRENT ESP and only this resolution makes any of
// them mean anything:
//
//   0x00a980b0  SUB ESP,0x50      ESP = entry - 0x50
//   0x00a980b3  PUSH EDI          ESP = entry - 0x54
//   0x00a980c3  PUSH EBP          ESP = entry - 0x58      (first-call path only)
//   0x00a980c4  PUSH ESI          ESP = entry - 0x5c      (first-call path only)
//
// So the steady-state ESP for the whole body is entry - 0x5c, and the frame
// proper -- the 0x50 bytes the SUB reserved -- is entry-0x50 .. entry-0x01. The
// twelve bytes the three PUSHes consume sit BELOW it and hold the outgoing
// arguments of the indirect calls.
//
// With that base, the two buffers the body hands to its callees are:
//
//   entry - 0x50 .. entry - 0x41   0x10 bytes, the argument of the three
//                                  narrow calls (0x00a9817b, 0x00a981a4, 0x00a981d2)
//   entry - 0x40 .. entry - 0x01   0x40 bytes, the argument of the wide call
//                                  (0x00a98162)
//
// 0x10 + 0x40 == 0x50, so the two outgoing buffers account for the reserved
// frame byte for byte and nothing in it is left over. That exact fit is the
// evidence for the two sizes below; it is arithmetic over the observed
// displacements, and it is corroborated here (INFERRED), not assumed.
//
// HONESTY NOTE ON WHERE EVERY OFFSET IN THIS HEADER COMES FROM:
//
//  * Every displacement below is read out of this body's own 112-instruction
//    listing, and every one names the instruction it came from. Nothing is
//    borrowed from another listing.
//
//  * NO MEMBER IS NAMED, anywhere, for any of the three objects. The machine
//    receiver record (abi.receiver / abi_derived.receiver) carries
//    `bounds_only: true` with offsets [12, 16, 20, 80] and register ECX: it
//    states where the body was seen reaching and nothing about which member is
//    which. So the receiver is modelled as an opaque byte run and reached only
//    through displacement-named accessors, and so is everything else. Each
//    object's comment says what the body DOES at each displacement -- read,
//    write, address-taken, bit test -- and stops there.
//
//  * The role words in the constant names ("ready flag", "attribute pointer")
//    name the SHAPE of the access, not a field identity. `ready flag` means
//    "the byte the body tests for non-zero and then sets to one"; `attribute
//    pointer` means "the word the body dereferences to reach a second object".
//    Neither is a claim about what the field is for in the original class.
//
//  * The 0x40-byte buffer is modelled as EIGHT 8-BYTE SLOTS. The five
//    conditional fills land at base+0x00, +0x08, +0x10, +0x18, +0x20 and the
//    three unconditional ones at base+0x28, +0x30, +0x38, so the stride is 8 and
//    is a fact of the displacements. That each slot is a PAIR of dwords is
//    INFERRED from the frame fitting exactly: the 0x40-byte region is one
//    object (nothing else in the frame is addressable), it is 0x40 bytes long,
//    and the machine writes 8 dwords at stride 8. What each pair MEANS is not
//    fixed by this body and is not claimed.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00a980b0 requires an x86-32 target"
#endif

// The one convention this body needs. Spelled per toolchain: GCC rejects the bare
// MSVC keyword outright, so the x86-32 attribute form is the portable spelling and
// the keyword form is kept for MSVC.
//
//   PKG_SW2_00A980B0_THISCALL  this body is __thiscall.
//
//   The receiver arrives in ECX: 0x00a980b4 `MOV EDI,ECX` is the second
//   instruction and ECX is never reloaded from anywhere afterwards.
//
//   The callee owns the stack cleanup: 0x00a981f2 is `RET 0x4`.
//
//   And the three indirect calls in the body are callee-cleaned too, which is
//   what fixes the convention for THEM as well and is the only reason the
//   frame balances. Each pushes exactly three dwords (12 bytes) and the
//   successor of every `CALL EDX` is an instruction that does not touch ESP;
//   if any of the four callees returned with a bare `RET`, the twelve bytes
//   would still be on the stack when 0x00a981ef `ADD ESP,0x50` and 0x00a981f2
//   `RET 0x4` ran, and the caller's ESP would be 12 bytes short. So each callee
//   pops its own arguments, which is __thiscall and not cdecl.
#if defined(_MSC_VER)
#define PKG_SW2_00A980B0_THISCALL __thiscall
#else
#define PKG_SW2_00A980B0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00a980b0 {

using Word = std::uint32_t;

inline Word word_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline void store_word(void* base, std::size_t displacement, Word value) {
  *reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement) = value;
}

inline std::uint8_t byte_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline void store_byte(void* base, std::size_t displacement, std::uint8_t value) {
  *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) + displacement) = value;
}

// 0x00a98152 `LEA EDX,[EDI + 0x18]`: the address of an interior receiver member,
// handed to the callee as a dword. The body never reads through it.
inline Word address_word_at(const void* base, std::size_t displacement) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline std::uint32_t float_bits(float value) {
  Word bits = 0;
  __builtin_memcpy(&bits, &value, sizeof(bits));
  return bits;
}

inline float bits_to_float(Word bits) {
  float value = 0.0f;
  __builtin_memcpy(&value, &bits, sizeof(value));
  return value;
}

// ===========================================================================
// The receiver: ECX at 0x00a980b4, aliased into EDI. An opaque byte run.
// ===========================================================================
//
// Reached at five displacements, and this is the whole of what the body knows
// about it:
//
//   +0x0c  0x00a980df  MOV EAX,[EDI + 0xc]        READ dword, then dereferenced
//   +0x10  0x00a980b6  CMP byte ptr [EDI + 0x10],0     READ byte
//   +0x10  0x00a980c5  MOV byte ptr [EDI + 0x10],1    WRITE byte
//   +0x14  0x00a980c9  MOVSS dword ptr [EDI + 0x14],XMM0  WRITE dword
//   +0x18  0x00a98152  LEA EDX,[EDI + 0x18]             ADDRESS TAKEN
//   +0x50  0x00a9814b  MOV ECX,[EDI + 0x50]              READ dword
//
// Bound: 0x54 bytes. That is THIS body's own bound and no other listing's: the
// highest displacement it reaches is 0x50 and it reads four bytes there, so the
// object is at least 0x54 bytes. The abi record's `max_offset` is 80 == 0x50,
// which agrees. No smaller bound is possible from this body and no larger one is
// claimed.
constexpr std::size_t kReceiverSize = 0x54u;
constexpr std::size_t kReceiverAttributePointerDisplacement = 0x0cu;
constexpr std::size_t kReceiverReadyByteDisplacement = 0x10u;
constexpr std::size_t kReceiverFloatDisplacement = 0x14u;
constexpr std::size_t kReceiverAddressTakenDisplacement = 0x18u;
constexpr std::size_t kReceiverTrailingWordDisplacement = 0x50u;

// An opaque byte run. No member is named; every access below is a displacement
// through one of the accessors, and each displacement's comment says which
// instruction it came from and what the body does there.
struct Receiver {
  std::array<std::uint8_t, kReceiverSize> opaque_00{};
};
static_assert(sizeof(Receiver) == 0x54u,
              "0x50 + 4 is the last byte 0x00a9814b reads on the receiver");
static_assert(kReceiverTrailingWordDisplacement + sizeof(Word) <= sizeof(Receiver),
              "the +0x50 read lies inside this body's own bound of the object");
static_assert(kReceiverAddressTakenDisplacement < sizeof(Receiver),
              "the +0x18 address taken at 0x00a98152 lies inside the object");

// The value 0x00a980c5 writes into the +0x10 byte, and the value 0x00a980c9
// writes through XMM0 as a dword. Both are literal 1 and literal zero in the
// listing; the second is `MOVSS` of an XMM0 that 0x00a980c0 `XORPS XMM0,XMM0`
// has just cleared, so the four bytes stored are 0x00000000, which is +0.0f
// read back as a float.
constexpr std::uint8_t kReadyByteSet = 0x01u;

// ===========================================================================
// The object the receiver's +0x0c word points at. An opaque byte run.
// ===========================================================================
//
// Reached at seven displacements, all through the pointer the body loads at
// 0x00a980df and re-loads at 0x00a9816c, 0x00a98191 and 0x00a981be:
//
//   +0x08  0x00a980e2, 0x00a980f1, 0x00a98103, 0x00a98115, 0x00a98127,
//          0x00a98139, 0x00a9816f (TEST byte), 0x00a98194, 0x00a981c1
//          READ dword, used ONLY as a bit field: bits 0, 1, 2, 3, 5, 6, 7, 8, 9
//   +0x0c  0x00a9815b  MOV EAX,[EAX + 0xc]   READ dword, becomes argument 1
//   +0x10  0x00a980fc  READ dword, copied to wide slot 0 when bit 5 is set
//   +0x14  0x00a9810e  READ dword, copied to wide slot 1 when bit 6 is set
//   +0x18  0x00a98120  READ dword, copied to wide slot 2 when bit 7 is set
//   +0x1c  0x00a98132  READ dword, copied to wide slot 3 when bit 8 is set
//   +0x20  0x00a98144  READ dword, copied to wide slot 4 when bit 9 is set
//
// Bound: 0x24 bytes, again this body's own bound and no other listing's. The
// bit-4 word at +0x10 is NOT tested by this body: the sequence of shifts is
// 3, 5, 6, 7, 8, 9 and 4 is absent, so bit 4 of the flags word governs nothing
// here. The model therefore never reads bit 4 and the model test plants a word
// with bit 4 set and the gate bit clear to prove it changes nothing.
constexpr std::size_t kAttributeObjectSize = 0x24u;
constexpr std::size_t kAttributeFlagsDisplacement = 0x08u;
constexpr std::size_t kAttributeFirstArgumentDisplacement = 0x0cu;
constexpr std::size_t kAttributeWordForBit5Displacement = 0x10u;
constexpr std::size_t kAttributeWordForBit6Displacement = 0x14u;
constexpr std::size_t kAttributeWordForBit7Displacement = 0x18u;
constexpr std::size_t kAttributeWordForBit8Displacement = 0x1cu;
constexpr std::size_t kAttributeWordForBit9Displacement = 0x20u;

struct AttributeObject {
  std::array<std::uint8_t, kAttributeObjectSize> opaque_00{};
};
static_assert(sizeof(AttributeObject) == 0x24u,
              "0x20 + 4 is the last byte 0x00a98144 reads on the attribute object");
static_assert(kAttributeWordForBit9Displacement + sizeof(Word) <= sizeof(AttributeObject),
              "the bit-9 source word lies inside this body's own bound");

// The flag bits this body tests, in the order it tests them, as BIT NUMBERS and
// not as displacements. Each was read off a `SHR` immediate: 0x00a980e5 SHR
// ECX,0x3 / 0x00a980e8 TEST CL,0x1 is bit 3; 0x00a980f4/0x00a98106/0x00a98118/
// 0x00a9812a/0x00a9813c SHR 5/6/7/8/9 are bits 5, 6, 7, 8 and 9; and
// 0x00a9806f TEST byte ptr [EAX+0x8],0x1, 0x00a98197 SHR ECX,0x1 and
// 0x00a981c4 SHR ECX,0x2 are bits 0, 1 and 2. The tests are `TEST ... ,0x1` on
// one byte after a logical right shift, so they are unsigned bit tests and
// carry no signedness question at all.
constexpr unsigned kGateWideCallBit = 3u;
constexpr unsigned kNarrowCallBit0 = 0u;
constexpr unsigned kNarrowCallBit1 = 1u;
constexpr unsigned kNarrowCallBit2 = 2u;
constexpr unsigned kWideFillBit5 = 5u;
constexpr unsigned kWideFillBit6 = 6u;
constexpr unsigned kWideFillBit7 = 7u;
constexpr unsigned kWideFillBit8 = 8u;
constexpr unsigned kWideFillBit9 = 9u;

// ===========================================================================
// The service object. An opaque byte run, and the base of the one dispatch.
// ===========================================================================
//
// The body holds it in ESI from 0x00a980d3 to the end of the body and uses it
// for exactly one thing, four times: 0x00a98159, 0x00a98175, 0x00a9819e and
// 0x00a981cc are all `MOV EDX,dword ptr [ESI]` -- the leading word read fresh
// before EVERY one of the four indirect calls, never hoisted -- and each is
// followed by `MOV EDX,dword ptr [EDX + 0x14]`. So:
//
//   the leading word at displacement 0   is a dispatch table base
//   the word at displacement 0x14        is the target, for all four sites
//   0x14 / 4 == slot index 5
//
// 0x00a980d9 `JZ 0x00a981ec` after `CMP ESI,EBP` with EBP zeroed at 0x00a980d5
// is a null test on this object, so the bound is one word. Nothing else in the
// body touches it.
constexpr std::size_t kServiceSize = 0x04u;
constexpr std::size_t kServiceDispatchTableDisplacement = 0x00u;
constexpr std::size_t kDispatchSlotDisplacement = 0x14u;
constexpr std::size_t kDispatchSlotIndex = kDispatchSlotDisplacement / 4u;

struct ServiceObject {
  std::array<std::uint8_t, kServiceSize> opaque_00{};
};
static_assert(sizeof(ServiceObject) == 0x04,
              "the body only tests the service for null and reads its leading word");
static_assert(kDispatchSlotIndex == 5u,
              "0x14 / 4 is slot 5; arithmetic, not evidence");

// ===========================================================================
// The two outgoing argument buffers.
// ===========================================================================
//
// The 0x40-byte one, the argument of the single wide call. EIGHT 8-BYTE SLOTS,
// of which this body writes the first dword of eight and never the second:
//
//   slot 0  base+0x00  0x00a980ff  conditional on flag bit 5, from the
//                                  attribute object's +0x10
//   slot 1  base+0x08  0x00a98111  conditional on flag bit 6, from +0x14
//   slot 2  base+0x10  0x00a98123  conditional on flag bit 7, from +0x18
//   slot 3  base+0x18  0x00a98135  conditional on flag bit 8, from +0x1c
//   slot 4  base+0x20  0x00a98147  conditional on flag bit 9, from +0x20
//   slot 5  base+0x28  0x00a98155  unconditional, the ADDRESS of the receiver's
//                                  +0x18 (LEA at 0x00a98152, not a read of it)
//   slot 6  base+0x30  0x00a9814e  unconditional, the receiver's +0x50 word
//   slot 7  base+0x38  0x00a980ed  unconditional, literal zero, stored FIRST
//
// The second dword of every slot is never written by this body. It is left
// exactly as it was on entry, which the model reproduces by not touching it and
// the model test checks by planting a sentinel in each.
//
// The 0x10-byte one, the argument of the three narrow calls, and it is the SAME
// 0x10 bytes all three times -- the body writes it, calls, and comes back to
// write it again:
//
//   +0x00  0x00a9818b / 0x00a981b4 / 0x00a981e2   the selector: 0, 1, 2
//   +0x04  0x00a98187 / 0x00a981b0 / 0x00a981de   always literal zero
//
// Note the store ORDER at each of the three sites: the +0x04 word is written
// FIRST and the +0x00 word SECOND, after all three arguments are already on the
// stack. The model keeps that order because it is the order the listing states.
constexpr std::size_t kWideBufferSize = 0x40u;
constexpr std::size_t kWideSlotStride = 8u;
constexpr std::size_t kWideSlot0Displacement = 0x00u;
constexpr std::size_t kWideSlot1Displacement = 0x08u;
constexpr std::size_t kWideSlot2Displacement = 0x10u;
constexpr std::size_t kWideSlot3Displacement = 0x18u;
constexpr std::size_t kWideSlot4Displacement = 0x20u;
constexpr std::size_t kWideSlot5Displacement = 0x28u;
constexpr std::size_t kWideSlot6Displacement = 0x30u;
constexpr std::size_t kWideSlot7Displacement = 0x38u;

constexpr std::size_t kNarrowBufferSize = 0x10u;
constexpr std::size_t kNarrowSelectorDisplacement = 0x00u;
constexpr std::size_t kNarrowTrailingDisplacement = 0x04u;

// The two immediates the body pushes as argument 1 of the narrow calls. Both are
// read straight off the listing: 0x00a98180, 0x00a981a9 and 0x00a981d7. The
// first two sites push 0x0e7a8471 and the third pushes 0x0e7a8473; they differ
// by two, and nothing in this body says what either names.
constexpr Word kNarrowArgumentForSelector0 = 0x0e7a8471u;
constexpr Word kNarrowArgumentForSelector1 = 0x0e7a8471u;
constexpr Word kNarrowArgumentForSelector2 = 0x0e7a8473u;

// The three selectors the +0x00 word takes, in the order the sites write them:
// 0x00a9818b stores EBP, which 0x00a980d5 zeroed; 0x00a981b4 stores the
// immediate 1; 0x00a981e2 stores the immediate 2.
constexpr Word kSelectorForBit0 = 0u;
constexpr Word kSelectorForBit1 = 1u;
constexpr Word kSelectorForBit2 = 2u;

// ===========================================================================
// The transfer boundaries.
// ===========================================================================

// THE ONE DIRECT CALLEE. 0x00a980ce `CALL 0x00883860` is the body's only direct
// transfer (ghidra_function.callees and the xref export both list it and nothing
// else). It is called with nothing pushed and its result is the value the body
// goes on to use, so the model calls through this pointer and the model test
// supplies the definition, which is what lets the test substitute a null service
// and drive the early exit at 0x00a980d9.
//
// WHAT IT IS, read from the image at 0x00883860 and nothing more:
//
//   00883860  mov eax, ds:0x16514cc
//   00883865  ret
//
// Two instructions, a bare `RET`, one global word read, one global pointer
// returned. So it is a singleton accessor: a no-argument, caller-cleanup (cdecl)
// getter for a global pointer. The neighbouring 0x00883870 is the matching setter
// (`mov ecx,[esp+4]; mov eax,[ds:0x16514cc]; mov [ds:0x16514cc],ecx; ret`) and
// returns the previous value. The body's null test at 0x00a980d9 is therefore a
// test for "no singleton installed yet", which is what makes that early exit
// reachable. No C++ class name is claimed for the object it returns.
using ServiceAccessor = ServiceObject* (*)();

// The FOUR INDIRECT CALLS, one signature for all of them, taken from the three
// pushes and the ECX move that precede each `CALL EDX`:
//
//   0x00a98161/0x00a98166/0x00a98167   PUSH 0 (arg3), PUSH ptr (arg2), PUSH word (arg1)
//   0x00a98168                        MOV ECX,ESI
//   0x00a9816a                        CALL EDX
//
// and identically at 0x00a9817a/0x00a9817f/0x00a98180, 0x00a981a3/0x00a981a8/
// 0x00a981a9 and 0x00a981d1/0x00a981d6/0x00a981d7. Argument 1 is the FIRST push
// and therefore the word at the top of the stack at the call; argument 3 is the
// LAST push and is EBP, which 0x00a980d5 zeroed and which nothing between then
// and the call writes -- so argument 3 is 0 on all four sites. The receiver is
// the service object, unchanged in ECX from 0x00a980d3. The callee pops the
// twelve bytes (see the convention macro above).
//
// The result is DISCARDED at all four sites: the instruction after each CALL
// either reloads EAX from the receiver (0x00a9816c) or falls straight into the
// epilogue (0x00a981ec), and no EAX the callee leaves is read. So the return
// type below is void because the body uses nothing, not because the callee
// produces nothing.
using DispatchSlot = void(PKG_SW2_00A980B0_THISCALL*)(ServiceObject* receiver,
                                                       Word argument1,
                                                       void* argument2,
                                                       Word argument3);

// The dispatch itself, as the model performs it: given the dispatch TABLE word --
// which the body has just read out of the service at displacement zero, at
// 0x00a98159, 0x00a98175, 0x00a9819e or 0x00a981cc -- read the target word out of
// that table at the slot displacement (0x00a9815e and its three twins) and call
// it. The lead read is NOT done here: the body never hoists it, it re-reads it
// before every one of the four calls, and a model that read the lead once would
// be a different function whenever a callee replaced the service's leading word.
// Both reads are 4-byte word reads out of memory and neither base is checked.
inline Word load_slot(Word table_word, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(table_word) + displacement);
}

inline void dispatch_through_slot(Word table_word, ServiceObject* receiver, Word argument1,
                                  void* argument2, Word argument3) {
  const Word target = load_slot(table_word, kDispatchSlotDisplacement);
  reinterpret_cast<DispatchSlot>(static_cast<std::uintptr_t>(target))(receiver, argument1, argument2,
                                                                      argument3);
}

// FUN_00a980b0 @ 0x00a980b0.
//
// __thiscall. The receiver arrives in ECX (0x00a980b4) and is aliased into EDI;
// the callee pops four bytes of ordinary stack argument (0x00a981f2 `RET 0x4`).
// That one stack word is NEVER READ by any of the 112 instructions -- it exists
// only because the terminator's immediate names it -- so it is declared and left
// unnamed, and the model test asserts it is not touched.
//
// Return type is void. The two facts that fix it are the two facts a reader
// should not have to take on trust: the body's only definition of XMM0 is
// 0x00a980c0 `XORPS XMM0,XMM0`, whose result is consumed one instruction later
// by the store at 0x00a980c9 and never read again; and the 0x00a980ba `JNZ`
// path to 0x00a981ee never writes XMM0 at all, so a caller taking the early exit
// receives whatever XMM0 it arrived with. There is therefore no value this body
// produces for a caller on both paths, and the machine record's naming of XMM0
// as the return register (abi.return_semantics `float_or_x87_in_XMM0`,
// abi.return.void_possible false) is the inference's RT1 rule firing on the mere
// presence of an SSE instruction. That disagreement is recorded rather than
// papered over; see the package metadata's unresolved_questions.
extern "C" void PKG_SW2_00A980B0_THISCALL re_00a980b0(Receiver* receiver, Word stack_argument);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00a980b0
