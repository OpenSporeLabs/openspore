#include "job_continuation_0068f9b0.hpp"

namespace openspore::reconstruction::pkg_job_continuation_0068f9b0 {

// The whole body of 0x0068f9b0, instruction for instruction. Every comment
// names the address it comes from; nothing here is inferred from the SDK name
// `App::cJob::Continuation`, which is corroboration at best.
//
//   0x0068f9b0  PUSH EBX
//   0x0068f9b1  PUSH ESI
//   0x0068f9b2  MOV ESI,[ESP+0x0C]   ; the first stack argument
//   0x0068f9b6  MOV EBX,ECX          ; receiver
//   0x0068f9b8  PUSH EDI
//   0x0068f9b9  MOV EDI,[EBX+0x8]    ; the currently stored state
//   0x0068f9bc  CMP ESI,EDI
//   0x0068f9be  JE  0x0068f9dc        ; unchanged -> do nothing at all
//   0x0068f9c0  TEST ESI,ESI
//   0x0068f9c2  JE  0x0068f9cc        ; new state null -> skip its slot 0
//   0x0068f9c4  MOV EAX,[ESI]
//   0x0068f9c6  MOV EDX,[EAX]        ; vtable slot 0
//   0x0068f9c8  MOV ECX,ESI
//   0x0068f9ca  CALL EDX
//   0x0068f9cc  MOV [EBX+0x8],ESI    ; store, unconditionally past the test
//   0x0068f9cf  TEST EDI,EDI
//   0x0068f9d1  JE  0x0068f9dc        ; old state null -> skip its slot 1
//   0x0068f9d3  MOV EAX,[EDI]
//   0x0068f9d5  MOV EDX,[EAX+0x4]    ; vtable slot 1
//   0x0068f9d8  MOV ECX,EDI
//   0x0068f9da  CALL EDX
//   0x0068f9dc  POP EDI / POP ESI / POP EBX
//   0x0068f9df  RET 0x4
//
// Three properties the ordering above fixes, each worth stating because a
// plausible-looking rewrite loses one of them:
//   1. EDI is loaded ONCE, at 0x0068f9b9, before either virtual call. A body
//      that re-read state_slot_at(receiver, kStateFieldOffset) when it reaches 0x0068f9d3 dispatches slot
//      1 on whatever slot 0 left behind.
//   2. The store at 0x0068f9cc happens BETWEEN the two calls, so slot 0
//      observes the OLD field and slot 1 observes the NEW one.
//   3. The store is reached on the null-new path too (0x0068f9c2 jumps to
//      0x0068f9cc, past the call), so passing a null state CLEARS the field.
//      Only the equality test at 0x0068f9be skips the store entirely.
//
// Return type is void. The listing never writes a result to EAX on any path;
// the fallthrough at 0x0068f9dc..0x0068f9df reaches the pops with EAX holding
// whatever the last `CALL EDX` left, and the early-out path at 0x0068f9be
// returns without EAX ever being written at all. Nothing in the bytes defines
// that value, so nothing here propagates it.

void PKG_JOB_CONTINUATION_0068F9B0_THISCALL continuation_set_state_0068f9b0(
    ContinuationReceiver* receiver, StateObject* new_state) {
  // 0x0068f9b9. Read once and held, as EDI is.
  StateObject* const old_state = state_slot_at(receiver, kStateFieldOffset);

  // 0x0068f9bc CMP ESI,EDI / 0x0068f9be JE. A pointer comparison, so this is
  // an identity test, not an inequality of contents: handing back the state
  // already stored is a no-op that runs neither virtual and does not rewrite
  // the field. Both-null lands here too, by the same comparison.
  if (new_state == old_state) {
    return;
  }

  // 0x0068f9c0 TEST ESI,ESI / 0x0068f9c2 JE 0x0068f9cc. Guarded on the
  // incoming pointer only, and it jumps to the STORE, not past it.
  if (new_state != nullptr) {
    // 0x0068f9c4..0x0068f9ca: slot 0 of the new object, ECX = new_state.
    // `slot_at<kSlot0Index>` reads table+0x0, which is `MOV EDX,[EAX]` at
    // 0x0068f9c6 -- the slot index, not an array subscript.
    slot_at<kSlot0Index>(state_table_at(new_state, kStateTableOffset))(
        new_state);
  }

  // 0x0068f9cc. Unconditional past the equality test: reached with a null
  // new_state too, which is how the field is cleared.
  state_slot_at(receiver, kStateFieldOffset) = new_state;

  // 0x0068f9cf TEST EDI,EDI / 0x0068f9d1 JE 0x0068f9dc. Guarded on the
  // captured old value, not on the field as it stands now.
  if (old_state != nullptr) {
    // 0x0068f9d3..0x0068f9da: slot 1 of the old object, ECX = old_state.
    // EDI holds the object pointer, not its vtable, so 0x0068f9d3 is the
    // second vptr load of the body -- the same `MOV EAX,[reg]` shape as
    // 0x0068f9c4. `slot_at<kSlot1Index>` reads table+0x4, which is
    // `MOV EDX,[EAX+0x4]` at 0x0068f9d5.
    slot_at<kSlot1Index>(state_table_at(old_state, kStateTableOffset))(
        old_state);
  }
}

}  // namespace openspore::reconstruction::pkg_job_continuation_0068f9b0
