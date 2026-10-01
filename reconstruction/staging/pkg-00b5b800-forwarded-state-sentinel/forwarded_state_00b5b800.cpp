#include "forwarded_state_00b5b800.hpp"

// 0x00b5b800 -- borrowed receiver + 0x20 forwarded state, with a 0xffffffff
// null sentinel. Twenty bytes, seven instructions, and nothing else:
//
//     0x00b5b800  e8 1b 1b fe ff      CALL   0x00b3d320
//     0x00b5b805  85 c0               TEST   EAX,EAX
//     0x00b5b807  74 07               JE     0x00b5b810
//     0x00b5b809  8b c8               MOV    ECX,EAX
//     0x00b5b80b  e9 20 6f ee ff      JMP    0x00a42730
//     0x00b5b810  83 c8 ff            OR     EAX,0xffffffff
//     0x00b5b813  c3                  RET
//
// The body is read instruction for instruction from two independent machine
// sources on the pinned binary (objdump on SporeApp.exe and the live Ghidra
// bridge's listing plus its 24-byte memory read); see the header. Both agree
// byte for byte and the Ghidra function body runs 0x00b5b800..0x00b5b813 with
// INT3 padding immediately outside, so twenty bytes is the whole body and there
// is no hidden tail.
//
// What is modelled:
//
//   * the CALL target reads one borrowed absolute dword and returns it;
//   * TEST/JE splits on that value being null -- the two paths are the entire
//     control flow, and the JE displacement lands on the null arm;
//   * the non-null path moves the same value into ECX and TAIL-JUMPS, it does
//     not call and then continue, so the field reader's RET is this root's
//     return;
//   * the tail-jump target is a plain 32-bit load through ECX at the forwarded
//     displacement -- not a vtable load, not an interface call, no second
//     indirection;
//   * the null path ORs the all-ones immediate into EAX and returns that word.
//
// What is deliberately NOT modelled, because the machine does not say it:
//
//   * no class, struct member or field NAME for the 0x20 storage. It is an
//     opaque byte run with a displacement, and the header says so;
//   * no pointer, interface, mode-id or enum type for the result. The
//     corroborated consumer at 0x00ad1f63 compares the result against an
//     address-shaped word and does not dereference it, so the result stays a
//     32-bit scalar;
//   * no allocation, no store, no lock, no reference count, no teardown. The
//     receiver is BORROWED: this function neither retains nor releases it, and
//     the returned word is a borrowed view that is valid only while the global
//     receiver and its field stay live;
//   * no initialiser for the receiver slot. Nothing in these twenty bytes says
//     who stores that global, so the model's starting value is a placeholder
//     and every test below SETS the slot before reading it back.
//
// The sentinel domains are kept apart on purpose. The all-ones word this root
// returns on the null path is its own null sentinel. The address-shaped words
// the corroborated consumer compares against belong to a separate encoded-state
// family; nothing in this body normalises one into the other, and the null arm
// does not return pointer null.

namespace openspore::reconstruction::pkg_00b5b800 {

ReceiverGlobalImage g_receiver_global_image{};
ForwardedReceiverImage g_forwarded_receiver_image{};

Word& g_0167eaec = g_receiver_global_image.slot;
std::uint8_t* g_forwarded_receiver = g_forwarded_receiver_image.bytes;
Word& g_forwarded_receiver_field =
    *reinterpret_cast<Word*>(g_forwarded_receiver + kForwardedFieldDisplacement);

Word read_receiver_slot() {
  // 0x00b3d320  a1 ec ea 67 01   MOV EAX, DS:0x0167eaec
  // 0x00b3d325  c3               RET
  return g_0167eaec;
}

Word read_forwarded_field(Word receiver) {
  // 0x00a42730  8b 41 20   MOV EAX, DWORD PTR [ECX+0x20]
  // 0x00a42733  c3          RET
  //
  // A plain displacement load through the receiver, with no second
  // indirection: there is no vtable involved and no dispatch occurs.
  return *reinterpret_cast<const Word*>(static_cast<std::uintptr_t>(receiver) +
                                        kForwardedFieldDisplacement);
}

Word PKG_00B5B800_CALL forwarded_state_00b5b800() {
  // 0x00b5b800  e8 1b 1b fe ff      CALL   0x00b3d320
  // 0x00b5b805  85 c0               TEST   EAX,EAX
  // 0x00b5b807  74 07               JE     null_arm
  // 0x00b5b809  8b c8               MOV    ECX,EAX
  // 0x00b5b80b  e9 20 6f ee ff      JMP    0x00a42730      (tail jump)
  const Word receiver = read_receiver_slot();
  if (receiver != Word{0}) {
    // 0x00b5b809  8b c8   MOV ECX,EAX
    // 0x00b5b80b  e9 ...   JMP  0x00a42730
    //
    // The machine's TEST/JE compares the WHOLE of EAX, and the jump is a TAIL
    // JUMP: the field reader's RET is this root's return, so nothing executes
    // after the read in the machine and nothing is executed after it here.
    return read_forwarded_field(receiver);
  }
  // 0x00b5b810  83 c8 ff   OR EAX,0xffffffff
  // 0x00b5b813  c3         RET
  //
  // imm8 is sign extended to the full 32-bit register, so the immediate ff
  // becomes the all-ones word. It is a sentinel, NOT pointer null: the two are
  // different values and normalising them would misstate the null arm.
  return kNullSentinel;
}

}  // namespace openspore::reconstruction::pkg_00b5b800
