// PKG-SWARM-W2-00A98200 -- VA 0x00a98200
// FUN_00a98200 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 110 instructions, 0x00a98200..0x00a98336 inclusive, with the
// terminator RET 0x4 at 0x00a98336 (opcode C2 04 00, so the body's last byte is
// 0x00a98338 and the committed Ghidra record's body_end names that byte). Every
// line below is annotated with the instruction it comes from; the full listing is
// in the header.
//
// WHAT THE BODY IS, in one sentence: it tests and clears a latch byte on the
// receiver, obtains a service object from a global, and then makes up to four
// INDEPENDENT indirect calls through one table slot, each guarded by its own bit
// of a flag word, passing the address of a small frame object built for that call.
//
// FOUR INDEPENDENT CONDITIONAL CALLS, not a switch and not a chain. Each block
// re-reads the record pointer from the receiver (0x00a98227, 0x00a9824c,
// 0x00a98279, 0x00a982a3) and each test is `SHR` + `TEST <8-bit reg>,1` + `JZ`, so
// the four guards are four separate bits of the same word and a run with all four
// set makes all four calls, in listing order, with no fallthrough between them.
// The two earlier JZ targets (0x00a9824c, 0x00a98279, 0x00a982a3) are the NEXT
// block's entry, which is the only sense in which the blocks are sequential.
//
// BIT 3 OF THE FLAG WORD IS NEVER TESTED. The shifts the listing uses are 1, 2, 4,
// 5, 6, 7, 8 and 9; nothing shifts by 3. So the guard set is {0, 1, 2, 4} for
// calls and {5, 6, 7, 8, 9} for the eight-dword list's first five words, and a
// flag word with bit 3 set and nothing else set makes NO call at all.

#include "sw2_00a98200_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00a98200 {
namespace {

// -- the model's frame ------------------------------------------------------
// FRAME-0 is ESP as it stands after the prologue's three pushes, and this is the
// byte run that stands for the 0x58 bytes the body then names. It is WIDER than
// the 0x50 the prologue reserved, because 0x00a982b1 really does write four bytes
// past the top of the reservation (kListWord7Offset + 4 == kFrameByteCount). The
// bytes below FRAME-0+0x0c are the three pushed slots and are never named by any
// instruction, so the model leaves them alone.
struct alignas(4) Frame {
  std::array<Byte, kFrameByteCount> bytes;
};

// The one instrumentation word, documented in the header: it stands for whatever
// the frame already held when this body was entered. The body does not initialise
// LIST dwords 0..4, so without a word to stand for the prior content the model
// could not state -- and its test could not check -- that those five dwords reach
// the callee untouched.
Word g_frame_poison = 0;

// -- the assertions that tie every constant above to the instruction it came
// from. These are build-time checks, not documentation: if a constant in the
// header is ever edited away from the listing, the build stops here. The messages
// name the instruction by address WITHOUT a 0x prefix, because a hexadecimal
// literal inside a string is source text and is read as a constant by the
// repository's own constant extractor.
static_assert(kReceiverRecordPointerOffset == 0x0c, "MOV EAX,[EDI + 0xc] at 00a98227");
static_assert(kReceiverLatchOffset == 0x10, "CMP [EDI + 0x10],0x0 at 00a98206 and the store at 00a98212");
static_assert(kReceiverInteriorOffset == 0x18, "LEA EDX,[EDI + 0x18] at 00a98316");
static_assert(kReceiverPayloadOffset == 0x50, "MOV ECX,[EDI + 0x50] at 00a9830f");
static_assert(kRecordFlagsOffset == 0x08, "TEST byte ptr [EAX + 0x8],0x1 at 00a9822a");
static_assert(kRecordCallKeyOffset == 0x0c, "MOV EAX,[EAX + 0xc] at 00a9831f");
static_assert(kRecordValue0Offset == 0x10, "MOV ECX,[EAX + 0x10] at 00a982c0");
static_assert(kRecordValue1Offset == 0x14, "MOV ECX,[EAX + 0x14] at 00a982d2");
static_assert(kRecordValue2Offset == 0x18, "MOV ECX,[EAX + 0x18] at 00a982e4");
static_assert(kRecordValue3Offset == 0x1c, "MOV ECX,[EAX + 0x1c] at 00a982f6");
static_assert(kRecordValue4Offset == 0x20, "MOV ECX,[EAX + 0x20] at 00a98308");
static_assert(kFlagBit0Mask == 0x1, "TEST byte ptr [EAX + 0x8],0x1 at 00a9822a");
static_assert(kFlagProbeMask == 0x1, "TEST CL,0x1 at 00a98254, TEST DL,0x1 at 00a982bb");
static_assert(kFlagBit1Shift == 0x1, "SHR ECX,0x1 at 00a98252");
static_assert(kFlagBit2Shift == 0x2, "SHR ECX,0x2 at 00a9827f");
static_assert(kFlagBit4Shift == 0x4, "SHR ECX,0x4 at 00a982a9");
static_assert(kFlagBit5Shift == 0x5, "SHR EDX,0x5 at 00a982b8");
static_assert(kFlagBit6Shift == 0x6, "SHR EDX,0x6 at 00a982ca");
static_assert(kFlagBit7Shift == 0x7, "SHR EDX,0x7 at 00a982dc");
static_assert(kFlagBit8Shift == 0x8, "SHR EDX,0x8 at 00a982eb");
static_assert(kFlagBit9Shift == 0x9, "SHR EDX,0x9 at 00a98300");
static_assert(kKeyFlagOffA == 0xe7a8472, "PUSH at 00a9823b and 00a98264");
static_assert(kKeyFlagOffB == 0xe7a8474, "PUSH at 00a98292");
static_assert(kPairFlagOn == 0x1, "MOV dword ptr [ESP + 0x18],0x1 at 00a9826f");
static_assert(kServiceSlotDisplacement == 0x14, "MOV EDX,[EDX + 0x14] at 00a98232, 0x00a9825b, 0x00a98289, 0x00a98322");
static_assert(kFrameReservedBytes == 0x50, "SUB ESP,0x50 at 00a98200");
static_assert(kPairBaseOffset == 0x0c, "LEA EAX,[ESP + 0x10] at 00a98236 with ESP at frame-4");
static_assert(kPairSecondWordOffset == 0x14, "MOV dword ptr [ESP + 0x20],EBP at 00a98242 with ESP at frame-0xc");
static_assert(kListBaseOffset == 0x1c, "LEA ECX,[ESP + 0x20] at 00a98326 with ESP at frame-4");
static_assert(kListWord0Offset == 0x1c, "MOV dword ptr [ESP + 0x1c],ECX at 00a982c3");
static_assert(kListWord1Offset == 0x24, "MOV dword ptr [ESP + 0x24],ECX at 00a982d5");
static_assert(kListWord2Offset == 0x2c, "MOV dword ptr [ESP + 0x2c],ECX at 00a982e7");
static_assert(kListWord3Offset == 0x34, "MOV dword ptr [ESP + 0x34],ECX at 00a982f9");
static_assert(kListWord4Offset == 0x3c, "MOV dword ptr [ESP + 0x3c],ECX at 00a9830b");
static_assert(kListWord5Offset == 0x44, "MOV dword ptr [ESP + 0x44],EDX at 00a98319");
static_assert(kListWord6Offset == 0x4c, "MOV dword ptr [ESP + 0x4c],ECX at 00a98312");
static_assert(kListWord7Offset == 0x54, "MOV dword ptr [ESP + 0x54],EBP at 00a982b1");
static_assert(kListWord7Offset + sizeof(Word) == kFrameByteCount,
              "00a982b1 names four bytes past the 0x50 the prologue reserved, so the frame is that wide");
static_assert(kPairBaseOffset + sizeof(Word) < kPairSecondWordOffset,
              "the two pair dwords are 8 bytes apart, not adjacent: 0x0c then 0x14");
static_assert(kPairSecondWordOffset == kPairBaseOffset + kFrameStride,
              "the pair sits on the same 8-byte stride as the list");
static_assert(kListBaseOffset == kPairBaseOffset + 2 * kFrameStride,
              "the list begins two strides above the pair, which is what 00a98326 computes");
static_assert(kFrameStride == 2 * sizeof(Word),
              "every frame dword is 8 bytes apart: 0x0c, 0x14, 0x1c, 0x24, 0x2c, 0x34, 0x3c, 0x44, 0x4c, 0x54");
static_assert(kFrameByteCount == kPairBaseOffset + 9 * kFrameStride + sizeof(Word),
              "ten dwords on an 8-byte stride from 0x0c put the last at 0x54, and the frame ends at 0x58");
static_assert(kReceiverPayloadOffset + sizeof(Word) == kReceiverSpanBytes,
              "0x50 + 4 is the last byte the body names on the receiver");
static_assert(kRecordValue4Offset + sizeof(Word) == kRecordSpanBytes,
              "0x20 + 4 is the last byte the body names on the record");
static_assert(kServiceLeadingWordOffset + sizeof(Word) == kServiceSpanBytes,
              "the service's leading word is the only thing the body names on it");

// Reads the record pointer out of the receiver, freshly, on every block. This is
// deliberately NOT hoisted: the machine executes
//   MOV EAX,dword ptr [EDI + 0xc]
// once per block, so a record rewritten by one of the four callees is picked up
// by the next block on the machine and a hoisted copy in a model would not be.
// The model test drives exactly that (a callee that swaps the record pointer) and
// the assertion is that the later blocks see the new record.
Record* read_record(void* self) {
  return reinterpret_cast<Record*>(word_at(self, kReceiverRecordPointerOffset));
}

// The two-level fetch the listing performs four times, with the SERVICE's leading
// word re-read on every one of them. Same reasoning as read_record: the four
// callees run between the fetches, so a hoisted table base would be a different
// function. The test drives a callee that rewrites the service's leading word.
Word fetch_target(ServiceObject* service) {
  return load_table_word(word_at(service, kServiceLeadingWordOffset), kServiceSlotDisplacement);
}

// The flag bit guards. Each takes the flag word and the shift the listing used,
// and each returns the boolean `TEST <8-bit reg>,1` returns after that shift.
// Nothing here tests bit 3: the listing never shifts by 0x3.
bool flag_bit(const Record* record, Word shift) {
  return ((word_at(record, kRecordFlagsOffset) >> shift) & kFlagProbeMask) != 0;
}

}  // namespace

Word frame_poison_word() { return g_frame_poison; }

void set_frame_poison_word(Word poison) { g_frame_poison = poison; }

extern "C" void PKG_SWARM_W2_00A98200_THISCALL re_00a98200(Receiver* receiver,
                                                          Word unused_stack_word) {
  // 00a98200  SUB ESP,0x50
  // 00a98203  PUSH EDI
  // 00a98204  MOV EDI,ECX
  //
  // EDI becomes the receiver alias and every receiver access below goes through
  // it. That is why the machine receiver record names register ECX with shape
  // R-ALIAS and why a scan that only reads ECX's own operands finds no receiver
  // displacement at all: the body never addresses `[ECX + n]`.
  (void)unused_stack_word;
  void* const self = receiver;

  // 00a98206  CMP byte ptr [EDI + 0x10],0x0
  // 00a9820a  JZ 0x00a98332
  //
  // The latch. The branch target 0x00a98332 is `POP EDI` -- the epilogue from
  // AFTER `POP EBP`, not a shared one -- so the taken path undoes the SUB and the
  // single PUSH EDI and returns. It does not reach the PUSH EBP / PUSH ESI pair
  // at 0x00a98210, which is the reason this body has two different stack depths
  // and the reason the model returns here rather than falling into a shared tail.
  //
  // The comparison is against zero, so this is an EQUALITY test, not a
  // non-zero test: any non-zero latch byte -- 1, 2, 0x80, 0xff -- takes the
  // active path. The model test drives 0x01, 0x80 and 0xff.
  if (byte_at(self, kReceiverLatchOffset) == 0) {
    // 00a98332  POP EDI
    // 00a98333  ADD ESP,0x50
    // 00a98336  RET 0x4
    return;
  }

  // 00a98210  PUSH EBP
  // 00a98211  PUSH ESI
  //
  // Both are saved here and restored at 0x00a98330/0x00a98331. EBP is not a frame
  // pointer (there is no `MOV EBP,ESP`); it is borrowed as the literal-zero third
  // stack argument of all four indirect calls and is zeroed immediately below.
  // ESI is the service pointer. Neither save has an observable effect on memory.
  //
  // 00a98212  MOV byte ptr [EDI + 0x10],0x0
  //
  // THE LATCH IS CLEARED HERE, on the active path only, and BEFORE the service
  // lookup. So a run with a non-zero latch and a null service still leaves the
  // receiver's +0x10 at zero, and a run whose latch was already zero never writes
  // it at all. One byte, the low half of the dword at 0x10; the three bytes above
  // it are not touched.
  mutable_byte_at(self, kReceiverLatchOffset) = 0;

  // 00a98216  CALL 0x00883860
  // 00a9821b  MOV ESI,EAX
  //
  // The one direct call. Nothing is pushed before it, so it carries no stack
  // argument; the callee's own first instruction is `MOV EAX,[0x016514cc]`, so it
  // reads no register either and the ECX still holding the receiver is a stale
  // value rather than an argument. Its five bytes are `A1 CC 14 65 01` / `C3` --
  // cdecl, no cleanup, one global read, return unchanged.
  ServiceObject* const service = openspore_acquire_service_00883860();

  // 00a9821d  XOR EBP,EBP
  //
  // EBP becomes 0 and stays 0: no instruction after this writes it, which is what
  // makes the fourth PUSH of every indirect call a literal zero rather than a
  // reload. It is also what the null test below compares against.
  const Word zero = 0;

  // 00a9821f  CMP ESI,EBP
  // 00a98221  JZ 0x00a98330
  //
  // A POINTER-VERSUS-ZERO test on the service word -- a full 32-bit compare, so
  // 0x00000001 is non-null and takes the active path. The target 0x00a98330 is
  // `POP ESI`, i.e. the epilogue with the EBP and EDI pops still to come, which
  // is balanced because both were pushed above.
  if (service == nullptr) {
    return;
  }

  // The frame. The prologue reserved it at 0x00a98200, so its lifetime starts
  // there, but no instruction between the prologue and this point names it, so the
  // model introduces it here. It is seeded with the instrumentation word, which
  // stands for the content the frame already had -- see the header's frame note
  // and fact (A): this body writes LIST dwords 0..4 only inside a flag test, so
  // their prior content reaches the callee and is observable.
  Frame frame;
  for (std::size_t index = 0; index < kFrameByteCount; index += sizeof(Word)) {
    mutable_word_at(&frame, index) = g_frame_poison;
  }

  // ---- block 1: flag bit 0, key 0xe7a8472, the pair with its first dword 0 ---
  //
  // 00a98227  MOV EAX,dword ptr [EDI + 0xc]
  // 00a9822a  TEST byte ptr [EAX + 0x8],0x1
  // 00a9822e  JZ 0x00a9824c
  //
  // The record pointer is re-read here and in each of the three blocks below; see
  // read_record. The guard is a BYTE test of the flag word's low byte, which on
  // x86-32 little-endian is the same bit 0 the later dword reads reach, and the
  // model keeps the byte form because the listing uses it.
  if ((byte_at(read_record(self), kRecordFlagsOffset) & kFlagBit0Mask) != 0) {
    // 00a98230  MOV EDX,dword ptr [ESI]
    // 00a98232  MOV EDX,dword ptr [EDX + 0x14]
    const Word target = fetch_target(service);

    // 00a98235  PUSH EBP
    // 00a98236  LEA EAX,[ESP + 0x10]
    // 00a9823a  PUSH EAX
    // 00a9823b  PUSH 0xe7a8472
    // 00a98240  MOV ECX,ESI
    // 00a98242  MOV dword ptr [ESP + 0x20],EBP
    // 00a98246  MOV dword ptr [ESP + 0x18],EBP
    // 00a9824a  CALL EDX
    //
    // THREE STACK WORDS, PUSHED RIGHT TO LEFT, so the argument order is
    // (key, address-of-pair, zero) and the register argument is ECX = ESI, the
    // service object. The two stores land on the pair's dword 1 and dword 0 --
    // EBP is zero, so this block writes 0 into BOTH -- and they happen AFTER the
    // pushes but BEFORE the call, which is the only part of that order the callee
    // can observe. The target was fetched before the pushes, which is likewise
    // unobservable to the callee but is the order the listing states.
    mutable_word_at(&frame, kPairSecondWordOffset) = zero;
    mutable_word_at(&frame, kPairBaseOffset) = zero;
    invoke_table_word(target, service, kKeyFlagOffA, address_at(&frame, kPairBaseOffset), zero);
  }

  // ---- block 2: flag bit 1, key 0xe7a8472, the pair with its first dword 1 ---
  //
  // 00a9824c  MOV EAX,dword ptr [EDI + 0xc]
  // 00a9824f  MOV ECX,dword ptr [EAX + 0x8]
  // 00a98252  SHR ECX,0x1
  // 00a98254  TEST CL,0x1
  // 00a98257  JZ 0x00a98279
  //
  // The flag word is read as a DWORD here (and from here on), shifted right by
  // one and the low bit tested. The shift is 32-bit, so bits above 31 wrap to
  // nothing and bit 31 lands in bit 30 -- it can never reach bit 0, so the high
  // bits of the word cannot make this guard fire.
  if (flag_bit(read_record(self), kFlagBit1Shift)) {
    // 00a98259..00a98277 -- the same shape as block 1, with two differences the
    // listing makes explicit: the KEY is 0xe7a8472 again (0x00a98264), and
    // 00a9826f writes the LITERAL 1 into the pair's first dword instead of EBP.
    const Word target = fetch_target(service);
    mutable_word_at(&frame, kPairSecondWordOffset) = zero;
    mutable_word_at(&frame, kPairBaseOffset) = kPairFlagOn;
    invoke_table_word(target, service, kKeyFlagOffA, address_at(&frame, kPairBaseOffset), zero);
  }

  // ---- block 3: flag bit 2, key 0xe7a8474, the pair with both dwords 0 ------
  //
  // 00a98279  MOV EAX,dword ptr [EDI + 0xc]
  // 00a9827c  MOV ECX,dword ptr [EAX + 0x8]
  // 00a9827f  SHR ECX,0x2
  // 00a98282  TEST CL,0x1
  // 00a98285  JZ 0x00a982a3
  //
  // Identical to block 2 but for the shift and the key: 0x00a98292 pushes
  // 0xe7a8474, one of the two constants in this body, and the pair's first dword
  // is EBP again (0x00a9829d), so it is 0.
  if (flag_bit(read_record(self), kFlagBit2Shift)) {
    const Word target = fetch_target(service);
    mutable_word_at(&frame, kPairSecondWordOffset) = zero;
    mutable_word_at(&frame, kPairBaseOffset) = zero;
    invoke_table_word(target, service, kKeyFlagOffB, address_at(&frame, kPairBaseOffset), zero);
  }

  // ---- block 4: flag bit 4, key from the record, the eight-dword list -------
  //
  // 00a982a3  MOV EAX,dword ptr [EDI + 0xc]
  // 00a982a6  MOV ECX,dword ptr [EAX + 0x8]
  // 00a982a9  SHR ECX,0x4
  // 00a982ac  TEST CL,0x1
  // 00a982af  JZ 0x00a98330
  //
  // This guard is the odd one out: when it is CLEAR the branch leaves the whole
  // body (0x00a98330 is the epilogue), not the next block, because there is no
  // fifth block. The flag word is RE-READ for every one of the five list-slot
  // tests below rather than kept in a register, which is the listing's own choice
  // and means a callee that rewrites the flag word changes the remaining slots.
  if (flag_bit(read_record(self), kFlagBit4Shift)) {
    // 00a982b1  MOV dword ptr [ESP + 0x54],EBP
    //
    // LIST dword 7, written FIRST and unconditionally, four bytes past the 0x50
    // the prologue reserved. It is the literal zero EBP holds.
    mutable_word_at(&frame, kListWord7Offset) = zero;

    // 00a982b5..00a982c3  SHR EDX,0x5 / TEST DL,0x1 -> LIST dword 0 from the
    // record's +0x10. Each of the five slots below is guarded by its own shift and
    // written ONLY when its guard holds; nothing zeroes them first, so a clear
    // guard leaves the frame's prior content in place and the callee receives it.
    if (flag_bit(read_record(self), kFlagBit5Shift)) {
      mutable_word_at(&frame, kListWord0Offset) = word_at(read_record(self), kRecordValue0Offset);
    }
    // 00a982c7..00a982d5  shift 6 -> LIST dword 1 from the record's +0x14
    if (flag_bit(read_record(self), kFlagBit6Shift)) {
      mutable_word_at(&frame, kListWord1Offset) = word_at(read_record(self), kRecordValue1Offset);
    }
    // 00a982d9..00a982e7  shift 7 -> LIST dword 2 from the record's +0x18
    if (flag_bit(read_record(self), kFlagBit7Shift)) {
      mutable_word_at(&frame, kListWord2Offset) = word_at(read_record(self), kRecordValue2Offset);
    }
    // 00a982eb..00a982f9  shift 8 -> LIST dword 3 from the record's +0x1c
    if (flag_bit(read_record(self), kFlagBit8Shift)) {
      mutable_word_at(&frame, kListWord3Offset) = word_at(read_record(self), kRecordValue3Offset);
    }
    // 00a982fd..00a9830b  shift 9 -> LIST dword 4 from the record's +0x20
    if (flag_bit(read_record(self), kFlagBit9Shift)) {
      mutable_word_at(&frame, kListWord4Offset) = word_at(read_record(self), kRecordValue4Offset);
    }

    // 00a9830f  MOV ECX,dword ptr [EDI + 0x50]
    // 00a98312  MOV dword ptr [ESP + 0x4c],ECX
    //
    // LIST dword 6: the receiver's own +0x50 dword, copied, UNCONDITIONALLY. This
    // is a value, not an address -- nothing in the body takes its address or
    // branches on it.
    mutable_word_at(&frame, kListWord6Offset) = word_at(self, kReceiverPayloadOffset);

    // 00a98316  LEA EDX,[EDI + 0x18]
    // 00a98319  MOV dword ptr [ESP + 0x44],EDX
    //
    // LIST dword 5: the ADDRESS of the receiver's own +0x18, stored, also
    // unconditionally. This is the one place in the body where an interior
    // receiver address is taken and handed out rather than a value read out of
    // the receiver, and it is why the two are not interchangeable in a
    // reconstruction: a model that copied the dword at +0x18 instead of the
    // address of +0x18 would be a different function, and the test drives a
    // receiver whose +0x18 dword and whose +0x18 address are different values.
    mutable_word_at(&frame, kListWord5Offset) =
        static_cast<Word>(reinterpret_cast<std::uintptr_t>(address_at(self, kReceiverInteriorOffset)));

    // 00a9831d  MOV EDX,dword ptr [ESI]
    // 00a9831f  MOV EAX,dword ptr [EAX + 0xc]
    // 00a98322  MOV EDX,dword ptr [EDX + 0x14]
    //
    // The target is fetched from the service's leading word, and the key is the
    // record's OWN +0x0c dword -- the only place in the body where the first
    // stack argument is a value read out of memory rather than an immediate. The
    // key can therefore be anything, including 0xe7a8472, and is not checked.
    const Word target = fetch_target(service);
    const Word key = word_at(read_record(self), kRecordCallKeyOffset);

    // 00a98325  PUSH EBP
    // 00a98326  LEA ECX,[ESP + 0x20]
    // 00a9832a  PUSH ECX
    // 00a9832b  PUSH EAX
    // 00a9832c  MOV ECX,ESI
    // 00a9832e  CALL EDX
    //
    // The same three-word, right-to-left shape as the other three calls, with the
    // list's address in place of the pair's. The pointer is computed AFTER the
    // PUSH EBP, which is why the listing spells it as a displacement from a
    // different ESP than the stores above do; both name the same address, and the
    // model uses the store-side constant.
    //
    // The callee's return value lands in EAX and is NEVER read: no instruction
    // between here and 0x00a98330 names EAX, and the epilogue does not move it.
    invoke_table_word(target, service, key, address_at(&frame, kListBaseOffset), zero);
  }

  // 00a98330  POP ESI
  // 00a98331  POP EBP
  // 00a98332  POP EDI
  // 00a98333  ADD ESP,0x50
  // 00a98336  RET 0x4
  //
  // The epilogue. Three pops restore the two borrowed registers and the receiver
  // alias, ADD ESP gives back the reserved window, and RET 0x4 consumes the return
  // address plus the one stack word this body never reads. Nothing here touches
  // EAX, which is why no path produces a value for the caller and the declared
  // return type is void. The frame's own `return` is placed at the ends of the
  // three early exits above and falls off the end here; all four reach the same
  // RET 0x4.
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00a98200
