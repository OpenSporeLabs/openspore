// Reconstruction of 0x004b09b0 - out-of-line operator= of a one-word intrusive
// reference holder.
//
// Complete body, read live at 0x004b09b0 (558bec 83ec08 894df8 ... c20800,
// then INT3 pad), 32 instructions, frame 0x8:
//
//   PUSH EBP / MOV EBP,ESP / SUB ESP,8
//   MOV [EBP-8],ECX                  ; this
//   MOV EAX,[EBP-8] / MOV ECX,[EBP+8]
//   CMP ECX,[EAX]                    ; new == held ? skip everything
//   JZ  0x004b09f9
//   MOV EDX,[EBP-8] / MOV EAX,[EDX] / MOV [EBP-4],EAX   ; pTemp = held
//   CMP [EBP+8],0                    ; new != 0 ?
//   JZ  0x004b09de
//   MOV ECX,[EBP+8] / MOV EDX,[ECX] / MOV ECX,[EBP+8]
//   MOV EAX,[EDX+4] / CALL EAX      ; new->vslot_04()      (thiscall, no args)
//   MOV ECX,[EBP-8] / MOV EDX,[EBP+8] / MOV [ECX],EDX     ; held = new
//   CMP [EBP-4],0                    ; pTemp != 0 ?
//   JZ  0x004b09f9
//   MOV EAX,[EBP-4] / MOV EDX,[EAX] / MOV ECX,[EBP-4]
//   MOV EAX,[EDX+8] / CALL EAX      ; pTemp->vslot_08()    (thiscall, no args)
//   MOV EAX,[EBP-8]                  ; return this
//   MOV ESP,EBP / POP EBP / RET 4    ; callee pops the one stack word
//
// The order is fixed and observable: the incoming pointer is acquired at
// +0x04 BEFORE the store, and the outgoing pointer is released at +0x08 AFTER
// the store. The +0x08 slot is proved to be the release side by the inlined
// clear at 0x00573c9f, which zeroes the holder first and then calls
// [ECX]->vslot_08 on the value it removed.
//
// Two slot identities are asserted only as INFERRED names, from the direction
// each slot is called in plus the SDK declaration of DefaultRefCounted as
// { ~DefaultRefCounted, AddRef, Release, GetReferenceCount }: +0x04 acquires,
// +0x08 releases. The slots themselves are observed.
#pragma once

#include <cstdint>

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

// The pointee. Three virtual slots are reachable from this function: +0x00 is
// never called here, +0x04 and +0x08 are. The vtable shape
// { dtor, acquire, release } is the SDK's DefaultRefCounted; the concrete
// pointee at the two editor callsites is Editors::EditorRigblock, whose SDK
// declaration is `class EditorRigblock : public DefaultRefCounted,
// public Object`.
struct RefCountedPointee_004b09b0 {
    void** vptr;  // +0x00
    // +0x04 acquire:  INFERRED AddRef, no arguments, thiscall
    // +0x08 release:  INFERRED Release, no arguments, thiscall
};

// Ports for the two observed indirect calls. Declared, not defined: the
// concrete callee is a property of the pointee's class.
extern "C" void __attribute__((thiscall))
PORT_pointee_acquire_004b09b0(RefCountedPointee_004b09b0* self);
extern "C" void __attribute__((thiscall))
PORT_pointee_release_004b09b0(RefCountedPointee_004b09b0* self);

// The holder. One word, matching every observed receiver: Editors::cEditor
// uses it at +0xCCh (mpActivePart) and +0xD0h (mpMovingPart).
struct IntrusiveRefHolder_004b09b0 {
    RefCountedPointee_004b09b0* held;  // +0x00
};

// The body. Returns the holder itself, which is what lets the observed
// callsites ignore the result.
// ABI note: the original is an MSVC __thiscall member, so the receiver
// arrives in ECX and the single stack word is popped by the callee (RET 4 at
// 0x004b09ff). A free function cannot express both halves of that on the
// i386 System V ABI - __attribute__((thiscall)) places the receiver in ECX
// but leaves the stack word to the caller - so the port keeps both
// parameters explicit and the generated cleanup differs by construction.
extern "C" IntrusiveRefHolder_004b09b0* FUN_004b09b0_assign(
    IntrusiveRefHolder_004b09b0* self, RefCountedPointee_004b09b0* incoming);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
