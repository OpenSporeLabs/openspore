// PKG-SWARM-W2-00A980B0 -- VA 0x00a980b0
// FUN_00a980b0 (SPORE/SporeBin/SporeApp.exe 3.1.0.22)
//
// The complete body: 112 instructions, 325 bytes, 0x00a980b0..0x00a981f4
// inclusive. Every line of the model below is annotated with the instruction it
// comes from; the header carries the full listing arithmetic, the frame
// resolution and the honesty notes about what is and is not claimed.
//
// WHAT THE BODY IS, in one paragraph, and every clause of it is a fact of the
// listing rather than a reading of intent. It tests one byte of its receiver and
// does nothing at all if that byte is already non-zero (0x00a980b6/0x00a980ba).
// Otherwise it sets that byte to one (0x00a980c5), stores a cleared 32-bit SSE
// scalar at the receiver's +0x14 (0x00a980c9), and asks a global singleton
// accessor for a service object (0x00a980ce). If the accessor returned null it
// stops there (0x00a980d9). If not, it reads a flag word out of a second object
// the receiver points at and makes between zero and four calls through ONE
// dispatch slot of the service's own leading word -- one wide call whose second
// argument is a 0x40-byte stack buffer the body fills, and up to three narrow
// calls whose second argument is a 0x10-byte stack buffer it rewrites each time.
//
// FRAME, resolved once against entry ESP so every displacement below is a fact:
//
//   0x00a980b0  SUB ESP,0x50      ESP = entry - 0x50
//   0x00a980b3  PUSH EDI          ESP = entry - 0x54
//   0x00a980c3  PUSH EBP          ESP = entry - 0x58
//   0x00a980c4  PUSH ESI          ESP = entry - 0x5c
//
// so the body runs at entry-0x5c, the 0x10-byte outgoing buffer is at entry-0x50
// and the 0x40-byte one is at entry-0x40. 0x10 + 0x40 == 0x50: the two outgoing
// buffers account for the whole reserved frame.
//
// CONTROL FLOW: ten conditional branches, every target inside the body, no
// unconditional branch, no loop and no exception handling. The graph is a chain
// of four guarded blocks, each falling into the next, and one early exit:
//
//   0x00a980ba  JNZ 0x00a981ee   the already-set path: straight to POP EDI
//   0x00a980d9  JZ  0x00a981ec   the null-service path: straight to POP ESI
//   0x00a980eb  JZ  0x00a9816c   the wide block's own gate, and the five
//                               conditional fills inside it
//   0x00a98173  JZ  0x00a98191   the bit-0 narrow block's gate
//   0x00a9819c  JZ  0x00a981be   the bit-1 narrow block's gate
//   0x00a981ca  JZ  0x00a981ec   the bit-2 narrow block's gate
//
// GLOBALS: none named. No instruction in the 112 names a data-segment address.
// The one global in the neighbourhood, 0x16514cc, is read by the CALLEE at
// 0x00883860 and not by this body.
//
// DISPATCH: four indirect sites, all `CALL EDX`, and the machine dispatch record
// agrees -- abi_derived.dispatch reports indirect_calls 4, call_offsets [] and
// vtable_shaped_loads 0. All four read the target the same way, out of the
// service's leading word at displacement 0 and then at displacement 0x14:
//
//   0x00a98159/0x00a9815e  0x00a98175/0x00a98177
//   0x00a9819e/0x00a981a0  0x00a981cc/0x00a981ce
//
// 0x14 / 4 == slot index 5. The lead is re-read before every one of the four
// calls, never hoisted out, and the model keeps that dependence rather than
// reading it once.
//
// VTABLE MEMBERSHIP, verified against the image and used for nothing else: the
// xref export carries a single edge, `data` from 0x01458790, and the dword at
// 0x01458788+0x08 is 0x00a980b0, so this body is slot index 2 of the table whose
// head is 0x01458788. The table's neighbouring slots are 0x00a98090 at +0x00,
// 0x004ae250 at +0x04 and 0x00a98200 at +0x0c, and the word after its fifteenth
// entry is the ASCII "area", so the table is fifteen entries long. Nothing here
// names the class.

#include "sw2_00a980b0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00a980b0 {
namespace {

// The three flag-bit groupings, tied to the instructions that fix them. These
// are assertions, not documentation: they fail the build if a constant in the
// header is ever edited away from the listing, and each message names the
// instruction the value came from. The bit NUMBERS are written in decimal
// because the listing spells them as `SHR` immediates and a decimal literal
// states the same value without adding a hexadecimal token.
static_assert(kReceiverReadyByteDisplacement == 0x10u, "the +0x10 byte at 00a980b6");
static_assert(kReceiverFloatDisplacement == 0x14u, "the +0x14 dword at 00a980c9");
static_assert(kReceiverAttributePointerDisplacement == 0x0cu, "the +0x0c word at 00a980df");
static_assert(kReceiverAddressTakenDisplacement == 0x18u, "the +0x18 LEA at 00a98152");
static_assert(kReceiverTrailingWordDisplacement == 0x50u, "the +0x50 word at 00a9814b");
static_assert(kAttributeFlagsDisplacement == 0x08u, "the +0x08 flags word at 00a980e2");
static_assert(kAttributeFirstArgumentDisplacement == 0x0cu, "the +0x0c word at 00a9815b");
static_assert(kDispatchSlotDisplacement == 0x14u, "the +0x14 slot fetch at 00a9815e");
static_assert(kServiceDispatchTableDisplacement == 0u, "the +0x00 lead read at 00a98159");
static_assert(kNarrowSelectorDisplacement == 0u, "the +0x00 selector store at 00a981b4");
static_assert(kNarrowTrailingDisplacement == 4u, "the +0x04 store at 00a98187");
// The wide buffer's eight slots: five conditional fills at stride eight from
// base+0x00, then the three unconditional ones at base+0x28, +0x30 and +0x38.
static_assert(kWideSlot0Displacement == 0x00u, "the bit-5 fill at 00a980ff");
static_assert(kWideSlot1Displacement == 0x08u, "the bit-6 fill at 00a98111");
static_assert(kWideSlot2Displacement == 0x10u, "the bit-7 fill at 00a98123");
static_assert(kWideSlot3Displacement == 0x18u, "the bit-8 fill at 00a98135");
static_assert(kWideSlot4Displacement == 0x20u, "the bit-9 fill at 00a98147");
static_assert(kWideSlot5Displacement == 0x28u, "the address store at 00a98155");
static_assert(kWideSlot6Displacement == 0x30u, "the +0x50 copy at 00a9814e");
static_assert(kWideSlot7Displacement == 0x38u, "the zero store at 00a980ed");
static_assert(kWideSlotStride == 8u, "five fills at base+00/08/10/18/20 and three at 28/30/38");
static_assert(kWideSlot7Displacement + sizeof(Word) <= kWideBufferSize,
              "the last slot's dword ends inside the 0x40-byte buffer");
static_assert(kWideSlot0Displacement + kWideSlotStride * 7u == kWideSlot7Displacement,
              "the eight slots are at a uniform stride of 8 from base+0x00");
static_assert(kNarrowTrailingDisplacement + sizeof(Word) <= kNarrowBufferSize,
              "the +0x04 store lies inside the 0x10-byte buffer");

// The bit tests, as they are read out of the listing. Each is a `TEST ...,0x1`
// on ONE BYTE after a logical right shift, so it is an unsigned bit test on the
// word read at the attribute object's +0x08 -- not a comparison, so there is no
// signedness and no threshold to get wrong.
static_assert(kGateWideCallBit == 3u, "SHR ECX,0x3 at 00a980e5 then TEST CL,0x1");
static_assert(kNarrowCallBit0 == 0u, "TEST byte ptr [EAX + 0x8],0x1 at 00a9816f");
static_assert(kNarrowCallBit1 == 1u, "SHR ECX,0x1 at 00a98197 then TEST CL,0x1");
static_assert(kNarrowCallBit2 == 2u, "SHR ECX,0x2 at 00a981c4 then TEST CL,0x1");
static_assert(kWideFillBit5 == 5u, "SHR EDX,0x5 at 00a980f4 then TEST DL,0x1");
static_assert(kWideFillBit6 == 6u, "SHR EDX,0x6 at 00a98106 then TEST DL,0x1");
static_assert(kWideFillBit7 == 7u, "SHR EDX,0x7 at 00a98118 then TEST DL,0x1");
static_assert(kWideFillBit8 == 8u, "SHR EDX,0x8 at 00a9812a then TEST DL,0x1");
static_assert(kWideFillBit9 == 9u, "SHR EDX,0x9 at 00a9813c then TEST DL,0x1");

// The two immediates the narrow calls push as their first argument, and the two
// that distinguish the third site from the other two. Both immediates appear in
// the listing at 0x00a98180, 0x00a981a9 and 0x00a981d7.
static_assert(kNarrowArgumentForSelector0 == 0x0e7a8471u, "PUSH 0xe7a8471 at 00a98180");
static_assert(kNarrowArgumentForSelector1 == 0x0e7a8471u, "PUSH 0xe7a8471 at 00a981a9");
static_assert(kNarrowArgumentForSelector2 == 0x0e7a8473u, "PUSH 0xe7a8473 at 00a981d7");
static_assert(kNarrowArgumentForSelector2 != kNarrowArgumentForSelector1,
              "the third site pushes a different immediate from the first two");

// BIT 4 IS NEVER TESTED, and the shift sequence proves it: 3, 5, 6, 7, 8, 9.
// There is no `SHR ...,0x4` anywhere in the body, so no displacement in the
// header is gated on bit 4 and the model must not read it. A bit-4-only flag
// word is a decoy in the model test and this is the assertion that catches a
// reconstruction that invented a fourth wide fill.
static_assert(kWideFillBit5 != 4u, "no SHR immediate of 4 exists in the 112 instructions");
static_assert(kWideFillBit6 != 4u, "no SHR immediate of 4 exists in the 112 instructions");
static_assert(kWideFillBit7 != 4u, "no SHR immediate of 4 exists in the 112 instructions");
static_assert(kWideFillBit8 != 4u, "no SHR immediate of 4 exists in the 112 instructions");
static_assert(kWideFillBit9 != 4u, "no SHR immediate of 4 exists in the 112 instructions");

// The `TEST` immediates the body uses are all 0x1, on a single byte. So the whole
// flag test is one bit at a time and there is no mask wider than one bit.
static_assert(kReadyByteSet == 0x01u, "MOV byte ptr [EDI + 0x10],0x1 at 00a980c5");

// The two buffers are the whole frame: 0x10 + 0x40 == 0x50, the SUB immediate.
static_assert(kNarrowBufferSize + kWideBufferSize == 0x50u,
              "the two outgoing buffers account for the whole reserved frame");

// One bit test, the shape 0x00a980e5/0x00a980e8 states: shift the word right by
// the bit number and look at its low bit. Named for what the listing does, not
// for what it means.
inline bool bit_is_set(Word word, unsigned bit) {
  return ((word >> bit) & 1u) != 0u;
}

}  // namespace

// The one direct callee, 0x00a980ce. The model test defines it; nothing in this
// translation unit does, because the original's own definition is a two-
// instruction global read that this body has no business re-implementing.
extern "C" ServiceObject* acquire_00883860();

extern "C" void PKG_SW2_00A980B0_THISCALL re_00a980b0(Receiver* receiver, Word stack_argument) {
  // 00a980b3  PUSH EDI
  // 00a980b4  MOV EDI,ECX
  //
  // EDI is the receiver alias for the whole body and the epilogue's POP EDI is
  // the only thing that restores it. Every receiver access below goes through
  // it, and none of them is through a pointer the body loaded, so the receiver
  // is the object ECX named and not anything inside it.
  //
  // The receiver is taken as a byte run. No member is named anywhere: the
  // machine receiver record is `bounds_only: true` and enumerates only the four
  // displacements it saw, so it states where the body reached and not which
  // member is which. See the header.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // The single ordinary stack word is never read. `RET 0x4` names it, and
  // nothing else in the 112 instructions touches it. It is named here only so
  // the signature is the machine's, and it is deliberately unused: the model test
  // fills it with a poison pattern and asserts the body leaves the frame alone.
  (void)stack_argument;

  // 00a980b6  CMP byte ptr [EDI + 0x10],0x0
  // 00a980ba  JNZ 0x00a981ee
  //
  // THE WHOLE GUARD. A byte at the receiver's +0x10 is compared against zero
  // and, if it is anything else, the body jumps to 0x00a981ee, which is the
  // `POP EDI` of the epilogue: no PUSH EBP, no PUSH ESI, no store, no call. So
  // the entire body runs at most once per receiver. The test is a byte compare
  // against zero and not a bit test, so ANY non-zero byte takes the exit --
  // including a byte whose only set bit is one the body never looks at. The
  // model test drives 0x01, 0x80, 0xff and 0x7f to pin that down.
  if (byte_at(self, kReceiverReadyByteDisplacement) != 0u) {
    return;
  }

  // 00a980c0  XORPS XMM0,XMM0
  //
  // XMM0 is cleared and its ONLY use is the store two instructions later. It is
  // never read again and the early-exit path above never reaches this
  // instruction, so no caller can receive a value this body computes. See the
  // header's note on why the return type is void and why the machine record's
  // `float_or_x87_in_XMM0` is not adopted.
  const float cleared_scalar = 0.0f;

  // 00a980c3  PUSH EBP
  // 00a980c4  PUSH ESI
  //
  // From here to the epilogue the frame is entry-0x5c, which is what makes the
  // two outgoing buffers' displacements below mean what they mean. Both
  // registers are restored by the epilogue's POP ESI / POP EBP and are otherwise
  // used as plain zeros and as the service handle.
  //
  // 00a980c5  MOV byte ptr [EDI + 0x10],0x1
  //
  // The one-byte store that latches the guard. It is a BYTE store (opcode C6 47
  // 10 01), not a dword, and it writes the literal 1. It happens AFTER the test
  // and BEFORE anything that can fail, so nothing below can leave the receiver
  // un-latched.
  store_byte(self, kReceiverReadyByteDisplacement, kReadyByteSet);

  // 00a980c9  MOVSS dword ptr [EDI + 0x14],XMM0
  //
  // A four-byte store at the receiver's +0x14 of the cleared SSE scalar. MOVSS
  // is the single-precision scalar form, so the four bytes written are
  // 0x00000000, which is +0.0f read back as a float. It is the last use of XMM0
  // in the body. The model writes the float's bit pattern rather than zeroing
  // four bytes blindly, so the test can read it back through a float and check
  // the store is the 32-bit single-precision one the opcode names.
  store_word(self, kReceiverFloatDisplacement, float_bits(cleared_scalar));

  // 00a980ce  CALL 0x00883860
  //
  // THE ONE DIRECT CALL. Nothing is pushed, so the accessor takes no arguments,
  // and its result is the only thing the body uses afterwards. In the original
  // this is `mov eax,ds:0x16514cc; ret` -- a global singleton getter -- and the
  // model goes through the injection point so the test can also return null.
  ServiceObject* const service = acquire_00883860();

  // 00a980d3  MOV ESI,EAX
  //
  // ESI is the service handle for the rest of the body. It is a plain register
  // move with no null test of its own; the null test is the next instruction.
  //
  // 00a980d5  XOR EBP,EBP
  //
  // EBP is zeroed once and never written again, and it is pushed as the THIRD
  // argument at all four call sites. So every call's third argument is 0, and
  // the zero is established here rather than at each site.
  //
  // 00a980d7  CMP ESI,EBP
  // 00a980d9  JZ 0x00a981ec
  //
  // A null test on the service. If it is null the body jumps to the epilogue's
  // POP ESI -- note that this exit runs the POP ESI and the POP EBP, because
  // both pushes happened, and then falls into POP EDI. Nothing else in the body
  // executes, so the receiver is left latched and cleared and no dispatch
  // happens.
  if (service == nullptr) {
    return;
  }

  // 00a980df  MOV EAX,dword ptr [EDI + 0xc]
  //
  // The one pointer the body holds over an object. The word at the receiver's
  // +0x0c is a POINTER and is used as one: it is LOADED, and every read below is
  // through the value it holds, at the attribute object's own displacements. Two
  // levels, and this is where it is easy to get wrong -- the address of the field
  // is not the object the field points at. The model test plants the flag word
  // in the pointed-at object and a different one at the receiver's +0x08, so a
  // model that used the field's address rather than its value reads the wrong
  // word and takes a different path.
  AttributeObject* const attributes = reinterpret_cast<AttributeObject*>(
      static_cast<std::uintptr_t>(word_at(self, kReceiverAttributePointerDisplacement)));

  // The two outgoing buffers. They are the frame's own storage, and the frame is
  // exactly their sum, so nothing else in the 0x50 bytes is live. Both are
  // modelled as byte runs for the same reason the receiver is: the machine says
  // which displacements are written and nothing about what the words are.
  std::uint8_t narrow_buffer[kNarrowBufferSize] = {};
  std::uint8_t wide_buffer[kWideBufferSize] = {};

  // 00a980e2  MOV ECX,dword ptr [EAX + 0x8]
  // 00a980e5  SHR ECX,0x3
  // 00a980e8  TEST CL,0x1
  // 00a980eb  JZ 0x00a9816c
  //
  // The gate of the wide block. The word at the attribute object's +0x08 is a
  // BIT FIELD, and this is its bit 3: shift the whole word right by three and
  // test the low BYTE's low bit. There is no sign, no threshold and no
  // comparison -- a logical right shift followed by a bit test, so the only way
  // to be wrong here is to test a different bit, and the model test plants a
  // word whose only set bit is the gate bit and one whose only set bit is each
  // of its neighbours.
  //
  // Note what the gate does NOT do: it does not merely decide whether the fills
  // happen, it decides whether the CALL happens. When bit 3 is clear the body
  // jumps to 0x00a9816c, which is the first instruction of the NEXT block, so
  // none of the five fill tests below is even evaluated.
  if (bit_is_set(word_at(attributes, kAttributeFlagsDisplacement), kGateWideCallBit)) {
    // 00a980ed  MOV dword ptr [ESP + 0x54],EBP
    //
    // With ESP at entry-0x5c, [ESP + 0x54] is entry-0x08, which is base+0x38 of
    // the wide buffer: the eighth and last slot. It is stored FIRST, before any
    // flag test, and it is the literal zero EBP holds. Every other store into
    // this buffer happens after it, so an observer that reads the buffer at the
    // moment of the call sees this word already zeroed.
    store_word(wide_buffer, kWideSlot7Displacement, 0u);

    // 00a980f1 .. 00a98147   five `SHR`/`TEST` pairs
    //
    // Each pair re-reads the SAME flags word from memory -- the body does not
    // keep it in a register across the five tests -- shifts it and tests one bit.
    // The five sources are five CONSECUTIVE dwords of the attribute object,
    // starting one slot after the word the gate and the two narrow blocks read:
    //
    //   bit 5  00a980fc  [EAX + 0x10]  ->  base+0x00   (00a980ff)
    //   bit 6  00a9810e  [EAX + 0x14]  ->  base+0x08   (00a98111)
    //   bit 7  00a98120  [EAX + 0x18]  ->  base+0x10   (00a98123)
    //   bit 8  00a98132  [EAX + 0x1c]  ->  base+0x18   (00a98135)
    //   bit 9  00a98144  [EAX + 0x20]  ->  base+0x20   (00a98147)
    //
    // A clear bit leaves its slot at whatever was there before, and this body
    // writes nothing else into it, so a slot whose bit is clear is NOT zeroed
    // and NOT set to any default: it is untouched. The model therefore
    // initialises the buffer once and writes only the slots whose bits are set,
    // and the model test fills every slot with a distinct sentinel first so a
    // reconstruction that zeroed the buffer, or that wrote the wrong slot, is
    // caught rather than passing on an accidentally-zeroed array.
    //
    // The flags word is read once into a local here. That is a C++ convenience
    // and it is safe for THIS body: no call happens between the five tests, so
    // nothing can change the word between them. The two re-reads that DO matter
    // -- across the calls -- are written out as explicit re-reads below.
    const Word flags = word_at(attributes, kAttributeFlagsDisplacement);

    // 00a980fa  JZ 0x00a98103   skips the 0x00a980fc/0x00a980ff pair
    if (bit_is_set(flags, kWideFillBit5)) {
      store_word(wide_buffer, kWideSlot0Displacement,
                 word_at(attributes, kAttributeWordForBit5Displacement));
    }
    // 00a9810c  JZ 0x00a98115   skips the 0x00a9810e/0x00a98111 pair
    if (bit_is_set(flags, kWideFillBit6)) {
      store_word(wide_buffer, kWideSlot1Displacement,
                 word_at(attributes, kAttributeWordForBit6Displacement));
    }
    // 00a9811e  JZ 0x00a98127   skips the 0x00a98120/0x00a98123 pair
    if (bit_is_set(flags, kWideFillBit7)) {
      store_word(wide_buffer, kWideSlot2Displacement,
                 word_at(attributes, kAttributeWordForBit7Displacement));
    }
    // 00a98130  JZ 0x00a98139   skips the 0x00a98132/0x00a98135 pair
    if (bit_is_set(flags, kWideFillBit8)) {
      store_word(wide_buffer, kWideSlot3Displacement,
                 word_at(attributes, kAttributeWordForBit8Displacement));
    }
    // 00a98142  JZ 0x00a9814b   skips the 0x00a98144/0x00a98147 pair
    if (bit_is_set(flags, kWideFillBit9)) {
      store_word(wide_buffer, kWideSlot4Displacement,
                 word_at(attributes, kAttributeWordForBit9Displacement));
    }

    // 00a9814b  MOV ECX,dword ptr [EDI + 0x50]
    // 00a9814e  MOV dword ptr [ESP + 0x4c],ECX
    //
    // [ESP + 0x4c] is entry-0x10, which is base+0x30: the seventh slot. It is
    // the receiver's OWN word at +0x50, copied in whole, and it is copied
    // UNCONDITIONALLY -- it is outside the five flag tests, so it happens
    // whether or not bits 5..9 are set, as long as the gate bit 3 was.
    store_word(wide_buffer, kWideSlot6Displacement,
               word_at(self, kReceiverTrailingWordDisplacement));

    // 00a98152  LEA EDX,[EDI + 0x18]
    // 00a98155  MOV dword ptr [ESP + 0x44],EDX
    //
    // [ESP + 0x44] is entry-0x18, which is base+0x28: the sixth slot. This is
    // an ADDRESS, not a read: the LEA computes the receiver's +0x18 and the body
    // never dereferences it. A reconstruction that stored the VALUE at +0x18
    // here, or that read it as a pointer and stored what it points at, would be
    // reading an object this body never touches. The model test plants a
    // decoy word at +0x18 for exactly that.
    store_word(wide_buffer, kWideSlot5Displacement,
               address_word_at(self, kReceiverAddressTakenDisplacement));

    // 00a98159  MOV EDX,dword ptr [ESI]
    //
    // The dispatch table lead, re-read from the service at displacement 0. It
    // is read HERE, after the seven stores above, and it is read again before
    // each of the three narrow calls below. The body never hoists it, so if one
    // of the callees replaced the service's leading word, the next call would go
    // somewhere else. The model keeps that: it re-reads rather than caching.
    const Word wide_table = word_at(service, kServiceDispatchTableDisplacement);

    // 00a9815b  MOV EAX,dword ptr [EAX + 0xc]
    //
    // EAX is still the attribute pointer, so this is the attribute object's
    // word at +0x0c -- the dword that becomes the call's FIRST argument. It is
    // read after the lead and before the target fetch, and it is a VALUE passed
    // by value, not a pointer the callee is given.
    const Word wide_argument1 = word_at(attributes, kAttributeFirstArgumentDisplacement);

    // 00a9815e  MOV EDX,dword ptr [EDX + 0x14]
    //
    // The target: the word 0x14 bytes into the table the lead named, i.e. slot
    // index 5. A 4-byte word read out of memory, never an immediate, and the
    // lead is not checked for null first.
    //
    // 00a98161  PUSH EBP            third argument, the zero from 0x00a980d5
    // 00a98162  LEA ECX,[ESP + 0x20] with ESP at entry-0x60, so entry-0x40:
    //                              the base of the 0x40-byte buffer
    // 00a98166  PUSH ECX            second argument
    // 00a98167  PUSH EAX            first argument
    // 00a98168  MOV ECX,ESI         the receiver: the service, unchanged
    // 00a9816a  CALL EDX
    //
    // So the argument order is (first=the attribute word at +0x0c, second=the
    // 0x40-byte buffer, third=0) with the service in ECX, and the callee pops
    // all twelve bytes -- which is what keeps the frame balanced through to
    // 0x00a981ef/0x00a981f2. The result is discarded: the very next instruction
    // reloads EAX from the receiver.
    dispatch_through_slot(wide_table, service, wide_argument1, wide_buffer, 0u);
  }

  // THE TWO IMMEDIATES, restated inside the span on purpose. The three narrow
  // sites push 0x0e7a8471, 0x0e7a8471 and 0x0e7a8473 as their first argument
  // (0x00a98180, 0x00a981a9, 0x00a981d7) and nothing else in the body contains
  // either value. The header already carries the constants and its own
  // assertions; these three are repeated here so that the values appear in the
  // reconstructed FUNCTION rather than only in a header, and can therefore be
  // checked against the machine listing's immediates directly.
  static_assert(kNarrowArgumentForSelector0 == 0x0e7a8471u, "PUSH 0xe7a8471 at 00a98180");
  static_assert(kNarrowArgumentForSelector1 == 0x0e7a8471u, "PUSH 0xe7a8471 at 00a981a9");
  static_assert(kNarrowArgumentForSelector2 == 0x0e7a8473u, "PUSH 0xe7a8473 at 00a981d7");
  static_assert(kNarrowArgumentForSelector0 == kNarrowArgumentForSelector1,
                "00a98180 and 00a981a9 push the same immediate");

  // 00a9816c  MOV EAX,dword ptr [EDI + 0xc]
  //
  // The attribute pointer is RE-READ from the receiver, not kept in a register
  // across the call above. That is a real dependence: if the wide callee wrote
  // the receiver's +0x0c, the three blocks below would read a different object.
  // The model re-reads it, and the model test uses a callee that rewrites
  // +0x0c to prove the dependence is real rather than written out of
  // convenience.
  //
  // 00a9816f  TEST byte ptr [EAX + 0x8],0x1
  // 00a98173  JZ 0x00a98191
  //
  // BIT 0 of the same flags word, read as a byte this time: the first two bits
  // are tested without a shift, and only bit 2 below needs one. Byte versus word
  // makes no difference to bit 0 on a little-endian target, and the model reads
  // the word and tests bit 0.
  // ... and 0x00a9816c re-loads the pointer itself, so the flag test below reads
  // whatever object the receiver points at NOW, not the one it pointed at before
  // the wide call. The model reads the word again rather than reusing the local,
  // because that dependence is in the listing.
  AttributeObject* const attributes_after_wide = reinterpret_cast<AttributeObject*>(
      static_cast<std::uintptr_t>(word_at(self, kReceiverAttributePointerDisplacement)));
  if (bit_is_set(word_at(attributes_after_wide, kAttributeFlagsDisplacement), kNarrowCallBit0)) {
    // 00a98175  MOV EDX,dword ptr [ESI]           the lead, read again
    // 00a98177  MOV EDX,dword ptr [EDX + 0x14]    the same slot, 0x14
    // 00a9817a  PUSH EBP                          third argument, 0
    // 00a9817b  LEA EAX,[ESP + 0x10]              with ESP at entry-0x60 this is
    //                                            entry-0x50: the 0x10-byte buffer
    // 00a9817f  PUSH EAX                          second argument
    // 00a98180  PUSH 0xe7a8471                    first argument
    // 00a98185  MOV ECX,ESI                       the receiver
    // 00a98187  MOV dword ptr [ESP + 0x20],EBP    with ESP at entry-0x68 this is
    //                                            entry-0x48: the buffer's +0x04
    // 00a9818b  MOV dword ptr [ESP + 0x18],EBP    entry-0x50: the buffer's +0x00
    // 00a9818f  CALL EDX
    //
    // The narrow call for selector 0. Note the store order: BOTH buffer words are
    // written AFTER all three arguments are already on the stack, and the +0x04
    // word is written BEFORE the +0x00 word. Both are literal zeros here. The
    // model keeps that order, so a reconstruction that wrote the selector first
    // and the zero second would be observationally identical -- the model test
    // therefore checks the VALUES at the call, not the order of two stores that
    // cannot be told apart, and says so.
    store_word(narrow_buffer, kNarrowTrailingDisplacement, 0u);
    store_word(narrow_buffer, kNarrowSelectorDisplacement, kSelectorForBit0);
    dispatch_through_slot(word_at(service, kServiceDispatchTableDisplacement), service,
                          kNarrowArgumentForSelector0, narrow_buffer, 0u);
  }

  // 00a98191  MOV EAX,dword ptr [EDI + 0xc]        the attribute pointer again
  // 00a98194  MOV ECX,dword ptr [EAX + 0x8]        the flags word again
  // 00a98197  SHR ECX,0x1
  // 00a98199  TEST CL,0x1
  // 00a9819c  JZ 0x00a981be
  //
  // BIT 1, reached by shifting the word right by one. Same shape as the gate,
  // one shift lower, and the same re-read of both the pointer and the word after
  // the previous call.
  AttributeObject* const attributes_after_bit0 = reinterpret_cast<AttributeObject*>(
      static_cast<std::uintptr_t>(word_at(self, kReceiverAttributePointerDisplacement)));
  if (bit_is_set(word_at(attributes_after_bit0, kAttributeFlagsDisplacement), kNarrowCallBit1)) {
    // 00a9819e .. 00a981bc   the same four-instruction argument sequence
    //
    // The ONLY differences from the bit-0 site are the first argument (the same
    // immediate 0x0e7a8471) and the selector written into the buffer's +0x00,
    // which is the immediate 1 here rather than EBP's zero. The +0x04 word is
    // EBP again, so it is zero again. The buffer is the SAME 0x10 bytes as the
    // bit-0 site used, not a second one, so this site's +0x00 store overwrites
    // that site's -- the model test checks exactly that.
    store_word(narrow_buffer, kNarrowTrailingDisplacement, 0u);
    store_word(narrow_buffer, kNarrowSelectorDisplacement, kSelectorForBit1);
    dispatch_through_slot(word_at(service, kServiceDispatchTableDisplacement), service,
                          kNarrowArgumentForSelector1, narrow_buffer, 0u);
  }

  // 00a981be  MOV EAX,dword ptr [EDI + 0xc]        the attribute pointer again
  // 00a981c1  MOV ECX,dword ptr [EAX + 0x8]        the flags word again
  // 00a981c4  SHR ECX,0x2
  // 00a981c7  TEST CL,0x1
  // 00a981ca  JZ 0x00a981ec
  //
  // BIT 2, the last of the three. Its false target is 0x00a981ec, the epilogue,
  // so this is the end of the chain.
  AttributeObject* const attributes_after_bit1 = reinterpret_cast<AttributeObject*>(
      static_cast<std::uintptr_t>(word_at(self, kReceiverAttributePointerDisplacement)));
  if (bit_is_set(word_at(attributes_after_bit1, kAttributeFlagsDisplacement), kNarrowCallBit2)) {
    // 00a981cc .. 00a981ea   the same four-instruction argument sequence
    //
    // Two differences from the first two sites and both are real: the first
    // argument is the OTHER immediate, 0x0e7a8473 against 0x0e7a8471, and the
    // selector in the buffer's +0x00 is the immediate 2 rather than EBP. So the
    // three narrow sites are distinguished by (immediate, selector) as
    // (0x0e7a8471, 0), (0x0e7a8471, 1) and (0x0e7a8473, 2) -- the first and
    // third arguments do NOT move in step with each other, and a reconstruction
    // that paired them up would be wrong twice out of three. The +0x04 word is
    // EBP, so it is zero for the third time.
    store_word(narrow_buffer, kNarrowTrailingDisplacement, 0u);
    store_word(narrow_buffer, kNarrowSelectorDisplacement, kSelectorForBit2);
    dispatch_through_slot(word_at(service, kServiceDispatchTableDisplacement), service,
                          kNarrowArgumentForSelector2, narrow_buffer, 0u);
  }

  // 00a981ec  POP ESI
  // 00a981ed  POP EBP
  // 00a981ee  POP EDI
  // 00a981ef  ADD ESP,0x50
  // 00a981f2  RET 0x4
  //
  // THE THREE EXITS, and they do not all run the same epilogue:
  //
  //   0x00a980ba -> 0x00a981ee   only POP EDI. Neither PUSH EBP nor PUSH ESI
  //                               happened on that path, and the guard's byte
  //                               was already non-zero, so nothing was latched.
  //   0x00a980d9 / 0x00a981ca -> 0x00a981ec
  //                               POP ESI, POP EBP, then falls into POP EDI.
  //   fall-through              all three, in reverse order of the pushes.
  //
  // ADD ESP,0x50 releases the frame and RET 0x4 consumes the return address and
  // the one ordinary stack word. No general-purpose register that could carry a
  // result is written by any of these five instructions, so whatever a caller
  // receives in EAX, ECX, EDX, ESI, EDI or EBP is whatever it left there. That
  // is the third leg of the void return type: the body has no result to hand
  // back, and the epilogue is careful not to invent one.
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00a980b0
