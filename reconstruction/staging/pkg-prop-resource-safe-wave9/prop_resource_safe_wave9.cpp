#include "prop_resource_safe_wave9.hpp"

#if defined(_MSC_VER)
#define PKG_PROP_SAFE_THISCALL __thiscall
#else
#define PKG_PROP_SAFE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_prop_resource_safe_wave9 {

void PKG_PROP_SAFE_THISCALL prop_manager_set_dev_mode_006a3300(
    OpaquePropManagerReceiver* manager, std::uint8_t value) {
  // 006a3300  MOV AL,byte ptr [ESP + 0x4]   the low byte of the argument slot
  // 006a3304  MOV byte ptr [ECX + 0x15],AL   one byte, at displacement 0x15
  // 006a3307  RET 0x4                        the callee pops the slot
  //
  // The whole body is that one store. It is written as a displacement into an
  // opaque receiver because a displacement is what the listing shows and a
  // member name is not: nothing in this pack says which member of the receiver
  // sits at 0x15, or that the receiver has one at all, so none is named. The
  // store is one byte wide because the storing instruction is a byte store, and
  // the value is the byte the caller wrote because the loading instruction
  // reads a byte.
  auto* const slot = reinterpret_cast<unsigned char*>(manager) + 0x15;
  *slot = value;
}

std::uint8_t PKG_PROP_SAFE_THISCALL record_write_flush_006c0550(
    void* receiver, Word argument_at_esp4, Word argument_at_esp8) {
  auto* const receiver_bytes = static_cast<unsigned char*>(receiver);

  // 006c0555  CMP dword ptr [ESI + -0x4],0x0
  // 006c0559  JZ 0x006c0581
  // A whole word against zero, not a byte and not a test of any single bit: every
  // non-zero value of any width takes the dispatch path. 006c0553  XOR AL,AL is
  // the zero the taken branch hands back, and it is AL that is zeroed -- the
  // three bytes above it are not written and are not modelled.
  if (load_word(slot_at(receiver_bytes, kRecordGateDisplacement)) == 0) {
    return 0;
  }

  // 006c055b  MOV EAX,dword ptr [ESI + 0x28] reads the word as a value and
  // 006c0562  LEA EDI,[ESI + 0x28] forms the same location as a this-pointer;
  // the two are one location, and the body uses it both ways.
  auto* const first_object = receiver_bytes + 0x28;

  // 006c055e  MOV EDX,dword ptr [EAX + 0x10]   the +0x10 word of the table the
  // word above points at, and 006c0567  CALL EDX dispatches it with ECX set to
  // the object -- 006c0565  MOV ECX,EDI -- and with no word pushed before the
  // call, so this port is handed the object and nothing else.
  void* const first_table = load_slot_table(first_object);
  if (load_access_port(slot_at(first_table, kAccessPortSlot))(first_object) == 0) {
    // 006c056b  JZ 0x006c0585 diverts to the other location, and the port's own
    // result is not this body's result on this path. Both table words are read
    // again here, after the port has run: 006c0585  MOV EDX,dword ptr
    // [ESI + 0x4] is a fresh load, not the one the access path made.
    auto* const second_object = receiver_bytes + 0x04;
    const WritePort second_write = load_write_port(
        slot_at(load_slot_table(second_object), kWritePortSlot));
    // 006c0585 through 006c0590 reach this port with no word pushed at all:
    // 006c058e  POP EDI and 006c058f  POP ESI restore the frame and 006c0590
    // JMP EDX transfers control, so the callee is entered with this caller's own
    // two words still in place and in the caller's order -- the ESP+0x4 word
    // first and the ESP+0x8 word second.
    return low_byte(
        second_write(second_object, argument_at_esp4, argument_at_esp8));
  }

  // 006c0571  MOV EAX,dword ptr [EDI] re-reads the first object's table word
  // rather than reusing the value 006c055b loaded, so a port that replaced the
  // table word is what 006c0577  MOV EAX,dword ptr [EAX + 0x38] reads the +0x38
  // word out of. The dispatch at 006c057e is a call, and the two argument words
  // are pushed in the order 006c057a  PUSH ECX (the ESP+0x8 word, recovered at
  // 006c056d) then 006c057b  PUSH EDX (the ESP+0x4 word, recovered at 006c0573),
  // so this port's first stack word is argument_at_esp8 -- the reverse of the
  // order the other port inherits. 006c0582  RET 0x8 then returns its result.
  const WritePort first_write = load_write_port(
      slot_at(load_slot_table(first_object), kWritePortSlot));
  return low_byte(first_write(first_object, argument_at_esp8, argument_at_esp4));
}

}

#undef PKG_PROP_SAFE_THISCALL
