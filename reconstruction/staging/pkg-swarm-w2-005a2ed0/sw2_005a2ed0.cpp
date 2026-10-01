// PKG-SWARM-W2-005A2ED0 -- VA 0x005a2ed0
// FUN_005a2ed0 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 22 instructions, 0x005a2ed0..0x005a2f1c inclusive, 79
// bytes (ghidra_function.body_start 0x005a2ed0, body_end 0x005a2f1e, span_bytes
// 79). The byte at 0x005a2f1f is INT3 padding, not body.
//
// THE WHOLE BODY IN ONE SENTENCE, in the order the instructions execute: store
// three .rdata words into the receiver at +0x00, +0x04 and +0x08; if the word
// the receiver holds at +0x10 is not null, take the table that word's pointee
// names at its own +0x00 and call that table's slot at offset 0x04 with the
// pointee as the receiver and no stack word; then store a second, different
// triple of .rdata words into the receiver at +0x08, +0x04 and +0x00 in that
// order; then, if bit 0 of the one stack argument is set, pass the receiver to
// 0x00f47380; and return the receiver.
//
// FRAME, resolved against the entry ESP so every stack claim below is a fact
// rather than a habit. Entry ESP is 0 in the walk. The body pushes once, at
// 0x005a2ed0, and pops once, at 0x005a2f1b, and its terminator is `C2 04 00`
// (RET 0x4). So the walk is:
//
//   entry-4    the saved ESI from the prologue's own `push esi`
//   entry+0    the return address
//   entry+0x4  the single ordinary stack argument, a BYTE: read at 0x005a2ef5
//              as `test byte ptr [esp+0x8],0x1` (one word outstanding, so
//              entry_ESP-4 + 0x8 == entry_ESP+0x4), and popped by the
//              terminator's own immediate
//
// and the intermediate `push esi` / `call 0x00f47380` pair is balanced by
// `add esp,0x4` at 0x005a2f16 -- which is itself the evidence that 0x00f47380
// is cdecl, because the callee's own body ends in a bare `c3` (see the header).
//
// RECEIVER ALIASING. ECX is copied into ESI at 0x005a2ed1 and every receiver
// access in the body goes through ESI. ECX is then REWRITTEN at 0x005a2ee7 with
// the word loaded from receiver+0x10, and it is that second value, not the
// receiver, that the CALL at 0x005a2ef3 passes. This is why the machine-derived
// receiver record reports register ECX with shape R-ALIAS while the only
// displacement a literal scan of ECX's own operands can find is zero: the
// receiver's four displacements (0x00, 0x04, 0x08, 0x10) are all reached through
// the alias. The record enumerates exactly those four, and bounds_only says that
// is where the body was SEEN reaching, not which member is which -- which is why
// this source declares no member and reaches the receiver through displacements.
//
// THE ONE INDIRECT TRANSFER, and it is the whole risk of this body. 0x005a2ef3
// is `ff d2`, a call through a register, and the register is built by TWO loads:
//
//   0x005a2ee7  8b 4e 10   mov  ecx,[esi+0x10]     ECX = the WORD at +0x10
//   0x005a2eee  8b 01      mov  eax,[ecx]          EAX = the word at the POINTEE's +0x00
//   0x005a2ef0  8b 50 04   mov  edx,[eax+0x4]      EDX = table[+0x4]
//   0x005a2ef3  ff d2      call edx
//
// Three things follow, and each is a way to be wrong:
//
//   * the word at +0x10 is a POINTER, not a dispatch word. Reading it as a
//     dispatch word makes the body one level short, and the one-level model
//     calls through the word at +0x10 itself -- which in the test is a decoy.
//   * the callee's receiver is the POINTEE, i.e. the value ECX holds at the
//     CALL. Nothing between 0x005a2ee7 and 0x005a2ef3 rewrites ECX, and nothing
//     after the CALL reads it. Passing receiver+0x10 (the address of the word)
//     or the receiver base is a different machine; the test measures what the
//     callee actually receives and plants a distinct observer at each of the
//     three candidate addresses.
//   * the slot is at BYTE displacement 0x04, which is dword index 1 of that
//     table. It is not slot 0, and it is not an index the body names; 0x04 is
//     the displacement of the load itself. A decoy in slot 0 and a decoy in slot
//     2 of the same table separate all three readings.
//
// GLOBALS: none beyond the six .rdata immediates, which are stored, not read.
// The xref export records data_reference_count 0 for this VA, so the validator's
// GLOBALS dimension can corroborate the mode of a data address only against the
// listing, and that is a WARN for any body that stores a .rdata address; the
// sidecar records it as a known blocker rather than dodging it by omitting the
// stores.

#include "sw2_005a2ed0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_005a2ed0 {
namespace {

// Model instrumentation, at namespace scope because the stores it records are
// partly unobservable from outside the body. See the header for why this is
// instrumentation and not a machine global.
Word g_store_count = 0;
Word g_store_displacement[8] = {0, 0, 0, 0, 0, 0, 0, 0};
Word g_store_value[8] = {0, 0, 0, 0, 0, 0, 0, 0};
Word g_dispatch_calls = 0;
void* g_last_pointee = nullptr;
std::uint8_t* g_flag_slot = nullptr;
void* g_receiver = nullptr;

void note_store(std::size_t displacement, Word value) {
  if (g_store_count < 8u) {
    g_store_displacement[g_store_count] = static_cast<Word>(displacement);
    g_store_value[g_store_count] = value;
  }
  ++g_store_count;
}

}  // namespace

ReceiverStoreLog receiver_store_log() {
  ReceiverStoreLog log;
  log.count = g_store_count;
  for (unsigned index = 0; index < 8u; ++index) {
    log.displacement[index] = g_store_displacement[index];
    log.value[index] = g_store_value[index];
  }
  return log;
}

std::uint8_t* deleting_flag_address() {
  return g_flag_slot;
}

void* receiver_address() {
  return g_receiver;
}

void* last_dispatched_pointee() {
  return g_last_pointee;
}

std::uint32_t dispatch_call_count() {
  return g_dispatch_calls;
}

extern "C" SwarmW2005a2ed0Receiver* SWARM_W2_005A2ED0_THISCALL re_005a2ed0(
    SwarmW2005a2ed0Receiver* receiver, std::uint8_t deleting_flag) {
  // 005a2ed0  push esi
  //
  // 005a2ed1  mov esi,ecx
  //
  // The prologue saves ESI and takes a private copy of the receiver. Every
  // receiver access below is through that copy, and the ECX that the machine
  // record calls the receiver register is written over again at 0x005a2ee7 --
  // which is the single fact that makes the two-level reading below mandatory
  // rather than optional.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);
  g_receiver = self;
  g_flag_slot = &deleting_flag;
  g_store_count = 0;
  g_dispatch_calls = 0;
  g_last_pointee = nullptr;

  // 005a2ed3  mov DWORD PTR [esi],0x13f69c8
  //
  // 005a2ed9  mov DWORD PTR [esi+0x4],0x13f69b8
  //
  // 005a2ee0  mov DWORD PTR [esi+0x8],0x13f69b4
  //
  // The first triple, in ASCENDING displacement: +0x00, then +0x04, then +0x08.
  // Three unconditional 32-bit stores of three different .rdata addresses. The
  // immediates are the encodings' own (`c7 06 c8 69 3f 01`, `c7 46 04 b8 69
  // 3f 01`, `c7 46 08 b4 69 3f 01`), and the record's single vtable association
  // for this VA, vtable:0x013f69b4, is the third of them -- which corroborates
  // that +0x08 receives a dispatch word of some kind and identifies nothing
  // else. No member is named for any of the three displacements.
  *word_at(self, kReceiverWrite00) = kFirstTripleHeadAt00;
  note_store(kReceiverWrite00, kFirstTripleHeadAt00);
  *word_at(self, kReceiverWrite04) = kFirstTripleHeadAt04;
  note_store(kReceiverWrite04, kFirstTripleHeadAt04);
  *word_at(self, kReceiverWrite08) = kFirstTripleHeadAt08;
  note_store(kReceiverWrite08, kFirstTripleHeadAt08);

  // 005a2ee7  mov ecx,dword ptr [esi+0x10]
  //
  // One 32-bit READ at the receiver's +0x10, and it is the only receiver word
  // this body reads. What the word IS is settled by the next two instructions
  // and by nothing else: it is a POINTER, because the body dereferences it
  // before it does anything else with it. Read as a value the body would have
  // one dereference fewer than it has, and the CALL would go to a different
  // address.
  void* const pointee = pointer_at(self, kReceiverRead10);
  g_last_pointee = pointee;

  // 005a2eea  test ecx,ecx
  //
  // 005a2eec  je 0x005a2ef5
  //
  // The null test is on the value just loaded, not on the receiver and not on
  // the receiver's own dispatch word. `85 c9` is `test ecx,ecx` and `74 07` is
  // JZ rel8, so the guard is "the word at +0x10 is zero". A null pointee skips
  // the call AND skips nothing else: the three stores above have already
  // happened and the three below happen either way.
  if (pointee != nullptr) {
    // 005a2eee  mov eax,dword ptr [ecx]
    //
    // ONE level of dereference of the loaded word, with no displacement: the
    // dword at the POINTEe's own +0x00. Two levels below the receiver, so the
    // word at receiver+0x10 is a pointer to an object and this is that object's
    // first word. The body then treats what it reads as a table pointer, and
    // the test's decoys make each other reading call a different function.
    void** const pointee_vtable = *reinterpret_cast<void***>(pointee);

    // 005a2ef0  mov edx,dword ptr [eax+0x4]
    //
    // The slot word, at BYTE displacement 0x04 of the table -- dword index 1.
    // The 0x4 below is the instruction's own operand, written as the literal the
    // encoding carries so the slot offset is checkable against the listing; the
    // header names the same value as kDispatchSlotDisplacement and pins it with
    // a static assertion, and the model test asserts both that it is 0x04 and
    // that 0x04 is dword index 1 and not index 0 or 2. It is the only slot
    // displacement this body can name.
    DispatchSlot const slot = slot_at(pointee_vtable, 0x4);

    // 005a2ef3  call edx
    //
    // The indirect call. The callee's receiver is the POINTEE: ECX still holds
    // the word loaded at 0x005a2ee7, because nothing between that load and this
    // CALL rewrites it, and nothing after the CALL reads it again. It is NOT
    // receiver+0x10, the address of the word, and NOT the receiver base -- each
    // of those is a different machine and the test measures which one the callee
    // receives.
    //
    // The body establishes NO stack word for this callee: there is no push
    // between the loads and the CALL, and no stack adjustment after it. What
    // the callee does with its own arguments beyond that receiver is not
    // observable from these twenty-two instructions and is not claimed.
    //
    // The return value is DISCARDED. The next instruction is the flag test at
    // 0x005a2ef5, which writes no register, and `mov eax,esi` at 0x005a2f19
    // overwrites EAX before the RET on both paths -- so whatever this callee
    // leaves in EAX is gone.
    slot(reinterpret_cast<DispatchedObject*>(pointee));
    ++g_dispatch_calls;
  }

  // 005a2ef5  test byte ptr [esp+0x8],0x1
  //
  // The ONE stack read in the body, and it is a BYTE. The displacement 0x8 is
  // not an ordinary frame offset: one word is outstanding (the prologue's saved
  // ESI), so entry_ESP-4 + 0x8 == entry_ESP+0x4, which is the first ordinary
  // stack argument and the four bytes this body's own `ret 0x4` pops. The mask
  // is 0x1, one bit, tested for being SET or CLEAR by the `je` at 0x005a2f0e.
  //
  // The read happens HERE -- after the guarded call and before the second
  // triple -- which is observable: the test's dispatch observer overwrites the
  // flag byte from inside the call, and the body then acts on the modified
  // value. A reconstruction that sampled the flag before the call, or after the
  // `je`, is a different body.
  //
  // The 0x1 is the instruction's own immediate (`test byte ptr [esp+0x8],0x1`),
  // written as the literal the encoding carries so the mask is checkable
  // against the listing. The header names the same value as kDeletingFlagMask.
  const bool deleting = (deleting_flag & 0x1) != 0u;

  // 005a2efa  mov DWORD PTR [esi+0x8],0x13ef094
  //
  // 005a2f01  mov DWORD PTR [esi+0x4],0x13eb394
  //
  // 005a2f08  mov DWORD PTR [esi],0x13eb938
  //
  // The second triple, in DESCENDING displacement: +0x08, then +0x04, then
  // +0x00 -- the reverse of the first triple's order, and three addresses that
  // are different from the first triple's three. The order is a machine fact and
  // it is invisible in the final state, because each word ends up holding its own
  // triple's value whichever order the stores were made in; only the store log
  // can separate the two readings, which is what the test's store-order case is
  // for. Still unconditional: the `je` that consumes the flag is the NEXT
  // instruction, so these three stores happen on the deleting path and on the
  // non-deleting path alike.
  *word_at(self, kReceiverWrite08) = kSecondTripleHeadAt08;
  note_store(kReceiverWrite08, kSecondTripleHeadAt08);
  *word_at(self, kReceiverWrite04) = kSecondTripleHeadAt04;
  note_store(kReceiverWrite04, kSecondTripleHeadAt04);
  *word_at(self, kReceiverWrite00) = kSecondTripleHeadAt00;
  note_store(kReceiverWrite00, kSecondTripleHeadAt00);

  // 005a2f0e  je 0x005a2f19
  //
  // The branch on the flag read at 0x005a2ef5. `74 09` is JZ rel8, so it is
  // TAKEN when bit 0 of the flag byte is CLEAR -- that is, when `deleting` is
  // false -- and it jumps past the call. The three stores between the TEST and
  // this JZ are `mov dword ptr [esi...],imm32`, which write no flags, so the
  // flags this branch consumes are exactly the ones 0x005a2ef5 set. The polarity
  // is the single easiest thing here to invert, and the test drives flag values
  // 0x00, 0x01, 0x02, 0x03, 0x80 and 0xff so a test of "non-zero" instead of
  // "bit 0 set" is separated from the real one.
  if (deleting) {
    // 005a2f10  push esi
    //
    // 005a2f11  call 0x00f47380
    //
    // The one direct call. The receiver -- the ESI copy, i.e. the same pointer
    // the body was entered with -- is the single pushed word, and it is pushed
    // immediately before the call, so the callee's own first instruction
    // (`mov eax,[esp+0x4]` with no push outstanding) fixes both the argument
    // and its order. The callee is cdecl: its body ends in a bare `c3`, and the
    // next instruction here drops the word.
    //
    // 005a2f16  add esp,0x4
    //
    // The caller-side cleanup, which is what makes the cdecl reading a fact
    // rather than a preference: a callee-cleaned callee would have popped these
    // four bytes itself and this ADD would skip the return address.
    deallocate_00f47380(self);

    // The callee's EAX is DEAD. Nothing between the ADD and the `mov eax,esi`
    // below reads it, and the `mov` overwrites it.
  }

  // 005a2f19  mov eax,esi
  //
  // The return value is the RECEIVER, on both paths, and it is the value ESI
  // has held since 0x005a2ed1 -- not a re-read of the receiver's memory. That
  // distinction is observable and the test uses it: the deallocation observer
  // overwrites the receiver's first word, and the body still returns the pointer
  // it was entered with.
  //
  // 005a2f1b  pop esi
  //
  // 005a2f1c  ret 0x4
  //
  // The saved ESI is restored and the terminator pops the four-byte stack
  // argument. The frame is otherwise already balanced by the ADD above, so this
  // RET consumes nothing but the return address and that one argument word.
  return receiver;
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_005a2ed0
