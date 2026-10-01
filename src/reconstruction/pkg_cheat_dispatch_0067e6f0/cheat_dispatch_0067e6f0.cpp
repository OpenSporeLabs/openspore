// Bounded reconstruction of the body of SporeApp.exe 0x0067e6f0
// (App::cCheatManager::func40h). Every line below is read off the 26-instruction
// listing in reconstruction/evidence/0067e6f0/evidence.json; the address in each
// comment is the instruction it models. No line is inferred from behaviour, and
// the body writes nothing, so every access modelled here is a read.

#include "cheat_dispatch_0067e6f0.hpp"

#if defined(_MSC_VER)
#define PKG_CHEAT_DISPATCH_0067E6F0_THISCALL __thiscall
#else
#define PKG_CHEAT_DISPATCH_0067E6F0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_cheat_dispatch_0067e6f0 {

extern "C" void PKG_CHEAT_DISPATCH_0067E6F0_THISCALL cCheatManager_func40h_0067e6f0(OpaqueWord* manager, OpaqueWord event_argument) {
  // 0x0067e6f0  CMP byte ptr [ECX + 0x64],0x0
  // 0x0067e6f4  JZ 0x0067e726                    gate clear: return untouched
  auto* const self = reinterpret_cast<unsigned char*>(manager);
  if (self[0x64] == 0u) {
    return;
  }
  // 0x0067e6f6  PUSH ESI                         register saves, no source effect
  // 0x0067e6fa  PUSH EDI
  // 0x0067e6fb  LEA EDI,[ECX + 0x4c]              terminator is the ADDRESS of the
  //                                              receiver word at +0x4c; the body
  //                                              never loads the bytes stored there
  auto* const terminator = reinterpret_cast<OpaqueWord*>(self + 0x4c);
  // 0x0067e6f7  MOV ESI,dword ptr [ECX + 0x50]    first chain link
  auto* node = *reinterpret_cast<OpaqueWord* const*>(self + 0x50);
  // 0x0067e6fe  CMP ESI,EDI                      empty chain exits before the loop
  // 0x0067e700  JZ 0x0067e724
  // 0x0067e702  PUSH EBX
  // 0x0067e703  MOV EBX,dword ptr [ESP + 0x10]   the entry stack argument, read
  //                                              once and reused on every step
  while (node != terminator) {
    // 0x0067e707  MOV ECX,dword ptr [ESI + 0x10] the receiver this node dispatches
    // 0x0067e70a  MOV EAX,dword ptr [ECX]         through, loaded fresh every step
    auto* const entry_receiver =
        reinterpret_cast<OpaqueWord*>(word_at(node, kNodeWordOffset));
    // The load at 0x0067e70a is a level of its own: EAX is the receiver's FIRST
    // word, and the slot read at 0x0067e70c is taken from that word, not from
    // the receiver. The header declares the displacement separately for exactly
    // this reason, and both loads are inside the loop, so consecutive nodes may
    // reach different tables through different receivers.
    const auto* const table = reinterpret_cast<const OpaqueWord*>(
        word_at(entry_receiver, kReceiverTableOffset));
    // 0x0067e70c  MOV EDX,dword ptr [EAX + 0x1c] the word the call is made through
    const auto entry = reinterpret_cast<DispatchEntry>(
        word_at(table, kCallTableEntryOffset));
    // 0x0067e70f  PUSH EBX                       trailing argument
    // 0x0067e710  PUSH 0x1                        leading argument
    // 0x0067e712  CALL EDX                        the body's only indirect transfer;
    //                                              the slot's identity is unproven
    entry(entry_receiver, 1, event_argument);
    // 0x0067e714  PUSH ESI                       argument for the stepper
    // 0x0067e715  CALL 0x00921580
    // 0x0067e71a  MOV ESI,EAX
    // 0x0067e71c  ADD ESP,0x4                     cdecl: the body drops the argument
    node = next_node_00921580(node);
    // 0x0067e71f  CMP ESI,EDI
    // 0x0067e721  JNZ 0x0067e707                  bottom test, back edge in body
  }
  // 0x0067e723  POP EBX / 0x0067e724 POP EDI / 0x0067e725 POP ESI
  // 0x0067e726  RET 0x4                          no value is produced; the callee
  //                                              removes the 4-byte stack argument
}

}
