// PKG-DFW-01053DB0 -- VA 0x01053db0
// Simulator::cDefaultBeamTool::func4Ch, SporeApp.exe 3.1.0.22.
//
// The complete machine listing, the calling-convention derivation and the
// reason no member of any record-named type is named in this package are all
// in dfw_01053db0_types.hpp. This file is the body.
//
// Shape, in the listing's own order:
//   01053db0  PUSH ESI                       save the callee-saved register
//   01053db1  MOV ESI,[ESP + 0x8]            receiver = first stack argument
//   01053db5  MOV ECX,[ESI + 0x124]          read the owned-target word
//   01053dbb  TEST ECX,ECX / 01053dbd JZ     null -> skip the whole block
//   01053dbf  CALL 0x00cb3c70                ECX = owned target, nothing pushed
//   01053dc4  MOV ECX,[ESI + 0x124]          SECOND read of the same word
//   01053dca  TEST ECX,ECX / 01053dcc JZ     null -> skip clear and dispatch
//   01053dce  MOV [ESI + 0x124],0            clear BEFORE the dispatch
//   01053dd8  MOV EAX,[ECX]                  the target's own table word
//   01053dda  MOV EDX,[EAX + 0x4]            the table's word at 0x4
//   01053ddd  CALL EDX                       ECX still the target
//   01053ddf  MOV ECX,ESI                     gate receiver is the tool
//   01053de1  CALL 0x0104cd50                nothing pushed
//   01053de6  POP ESI                        restored before the last two calls
//   01053de7  TEST AL,AL / 01053de9 JZ       clear gate -> skip the reset path
//   01053deb  CALL 0x00b3d3c0                accessor, no argument
//   01053df0  MOV ECX,EAX                    its result is the next receiver
//   01053df2  CALL 0x00b78860                nothing pushed
//   01053df7  MOV AL,0x1                     the only write to the result byte
//   01053df9  RET 0x4                        callee pops the one stack word
//
// Both conditional release branches converge on 01053ddf, so the gate call and
// the whole relationship path run on EVERY return, whether or not a target was
// owned. That is a property of the listing, not a choice made here.

#include "dfw_01053db0_types.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_dfw_01053db0 {
namespace {

// The four direct callees are named in dfw_01053db0_types.hpp and are declared
// there, not here: this package does not own any of them, so it declares no
// body for any of them. The test supplies a recording observer for each.

using Word = std::uint32_t;

// Raw 4-byte loads and one raw 4-byte store. Each takes a plain address and
// carries no displacement of its own, so every displacement this body uses is
// written literally at the instruction it belongs to, where a reader -- or the
// validator -- can check it against the listing instead of taking it on trust.

// 01053db5 / 01053dc4  MOV ECX,dword ptr [ESI + 0x124]
// 01053dd8             MOV EAX,dword ptr [ECX]
//
// A 4-byte read. Nothing in any record for this target says which member of
// OpaqueBeamToolState lives at 0x124, so it is modelled as an opaque word: the
// pointer type is only the use 01053dd8 makes of it -- the body itself
// dereferences it -- and not a claim about the memory it names.
OpaqueBeamTarget* load_pointer(const unsigned char* address) {
  OpaqueBeamTarget* word = nullptr;
  std::memcpy(&word, address, sizeof word);
  return word;
}

// 01053dd8  MOV EAX,dword ptr [ECX]
//
// The same read at displacement zero, named apart so the caller does not have to
// write a bare `+ 0x0` the listing does not write either: the listing's operand
// here is a plain [ECX], which is the access at offset zero and not a missing
// displacement.
const OpaqueBeamTargetVTable* load_pointer_at_0(const OpaqueBeamTarget* target) {
  const unsigned char* base = reinterpret_cast<const unsigned char*>(target);
  OpaqueBeamTargetVTable* table = nullptr;
  std::memcpy(&table, base, sizeof table);
  return table;
}

// 01053dda  MOV EDX,dword ptr [EAX + 0x4]
//
// The second of the body's two table-shaped loads. Its type is the persisted
// record's own: void (__thiscall *)(OpaqueBeamTarget *). The ECX-receiver shape
// is read off the listing, not assumed: ECX was loaded with this same pointer at
// 01053dc4 and nothing between there and the call writes ECX, and nothing is
// pushed for the call.
BeamTargetSlotFn load_slot(const unsigned char* address) {
  BeamTargetSlotFn slot = nullptr;
  std::memcpy(&slot, address, sizeof slot);
  return slot;
}

// 01053dce  MOV dword ptr [ESI + 0x124],0x0
//
// The only store the body makes, and it is the immediate zero the listing names.
// It lands on the word read above and before the dispatch, so the receiver
// holds no pointer while the call through the table word runs.
void store_word_zero(unsigned char* address) {
  const Word zero = 0;
  std::memcpy(address, &zero, sizeof zero);
}

}  // namespace

extern "C" std::uint8_t PKG_DFW_01053DB0_STDCALL
dfw_01053db0_func4Ch_release(void* receiver) {
  // 01053db0  PUSH ESI
  // 01053db1  MOV ESI,dword ptr [ESP + 0x8]
  //
  // The saved-register push and the receiver load are the two instructions that
  // fix the ABI: after the push, ESP + 0x8 is the entry-ESP + 0x4 slot, so the
  // receiver is the first stack argument. The body reads no other stack slot,
  // and 01053df9 returns with an immediate of four, so exactly one 4-byte
  // argument exists. The incoming ECX is never read.
  unsigned char* const base = static_cast<unsigned char*>(receiver);

  // 01053db5  MOV ECX,dword ptr [ESI + 0x124]
  // 01053dbb  TEST ECX,ECX
  // 01053dbd  JZ 0x01053ddf
  //
  // The word is read and tested. A zero word jumps to 0x01053ddf, which is the
  // shared tail, so the mark, the clear and the dispatch are all skipped
  // together and the slot is left exactly as it was found.
  //
  // This is the first of the three accesses this body makes to a receiver word,
  // and the machine-derived record contains NO observation of any of them: its
  // observations for this body record the +0x124 load only as obs-0005, a
  // REG_WRITE to ECX, with no memory event and no displacement, and its
  // receiver sub-record carries offsets == [] and written_through == 0. The
  // bytes are what is modelled here.
  OpaqueBeamTarget* owned = load_pointer(base + 0x124);
  if (owned != nullptr) {
    // 01053dbf  CALL 0x00cb3c70
    //
    // ECX still holds the word just read and nothing is pushed, so this is an
    // ECX-receiver member call on the owned target. Its return value is
    // discarded: the next instruction reloads the slot from memory rather than
    // using anything this call returned, and nothing in the listing reads a
    // register the call would have written.
    beam_mark_00cb3c70(owned);

    // 01053dc4  MOV ECX,dword ptr [ESI + 0x124]
    // 01053dca  TEST ECX,ECX
    // 01053dcc  JZ 0x01053ddf
    //
    // A SECOND load of the same displacement, three instructions after the
    // first, and it is a genuine memory access rather than a reuse of the
    // register: 01053dc4's own operand is [ESI + 0x124], not the register 01053db5
    // loaded. If the call above changed the slot, this instruction sees the
    // change and the test below can send control to 0x01053ddf with the clear
    // and the dispatch both skipped. It is modelled as a reload for that reason,
    // and the model test proves the distinction by having the observer clear the
    // slot across the 01053dbf call.
    owned = load_pointer(base + 0x124);
    if (owned != nullptr) {
      // 01053dce  MOV dword ptr [ESI + 0x124],0x0
      //
      // The clear precedes 01053dd8 and 01053ddd. The order is observable and
      // is not an artefact of the compiler: the store is a separate instruction
      // at a lower address than the two table loads, and the dispatch's
      // receiver is a register copy taken before the store. The model test
      // reads the slot from inside the dispatched call and requires it to be
      // zero there.
      store_word_zero(base + 0x124);

      // 01053dd8  MOV EAX,dword ptr [ECX]
      // 01053dda  MOV EDX,dword ptr [EAX + 0x4]
      //
      // Two loads, two different objects: the first reads the target's own
      // table word at displacement zero, the second reads the word at
      // displacement 0x4 of whatever that first load named. The target pointer
      // is still in ECX, so the call that follows is a member call on the
      // target and not on the receiver.
      const OpaqueBeamTargetVTable* const vtable = load_pointer_at_0(owned);

      // The one indirect transfer in the body. Its return value is discarded:
      // 01053de1 is a call, not a use of EAX, and the only write to the result
      // byte is 01053df7.
      const unsigned char* const table_words =
          reinterpret_cast<const unsigned char*>(vtable);
      load_slot(table_words + 0x4)(owned);
    }
  }

  // 01053ddf  MOV ECX,ESI
  // 01053de1  CALL 0x0104cd50
  //
  // Reached from above and from both release branches, so it runs on every
  // return. The receiver handed to the predicate is the receiver word, not the
  // owned target: the register is reloaded from ESI, which still holds the
  // first stack argument. Nothing is pushed. Whether that callee is a member of
  // the same class is not claimed here -- the body only shows the shape.
  if (beam_gate_0104cd50(reinterpret_cast<const OpaqueBeamToolState*>(base)) != 0) {
    // 01053deb  CALL 0x00b3d3c0
    //
    // An accessor called with no argument and nothing pushed; the listing
    // contains no push anywhere, so no ordinary argument is built for it.
    void* const relationship = beam_singleton_00b3d3c0();

    // 01053df0  MOV ECX,EAX
    // 01053df2  CALL 0x00b78860
    //
    // The accessor's EAX result becomes the ECX receiver of the next call
    // unchanged, and nothing is pushed. The word the accessor returns has no
    // type in any record for this target, so it is carried as an untyped
    // pointer and is not given a layout.
    beam_reset_00b78860(relationship);
  }

  // 01053de7  TEST AL,AL
  // 01053de9  JZ 0x01053df7
  //
  // The gate result byte decides only whether the block above runs. It is not
  // the returned value: the branch target 0x01053df7 is the instruction after
  // the reset, and a clear gate therefore still returns the byte written next.
  // A clear gate touches no global and no receiver word on the way out.

  // 01053df7  MOV AL,0x1
  //
  // The single write to the result byte, on every path, and the only one: no
  // other instruction in the body writes AL after the gate call. So the low
  // byte of the result register is the constant 0x1 whatever the gate, the
  // owned-target word and the two relationship calls did. That is the whole of
  // what the machine fixes about the result, and it is why the declared return
  // type is uint8_t and not bool: the byte and its constant value are observed,
  // while the persisted record's prose ("Unconditional success") and the live
  // prototype's `bool` are interpretations of it, not measurements. The upper
  // three bytes of EAX are whatever the last executed call left there and are
  // not claimed to be anything.
  //
  // 01053df9  RET 0x4
  //
  // Callee-side cleanup of one word, which is the __stdcall arity declared in
  // the header. The compiled entry ends in `c2 04 00  ret $0x4`.
  return 0x1u;
}

}  // namespace openspore::reconstruction::pkg_dfw_01053db0
