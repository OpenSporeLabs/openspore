// Bounded reconstruction of the body of SporeApp.exe 0x0067e730
// (App::cCheatManager::func44h). Every line below is read off the
// 24-instruction listing quoted in the header; the address in each comment is
// the instruction it models. No line is inferred from behaviour, and the body
// writes nothing, so every access modelled here is a read.

#include "cheat_dispatch_func44h_0067e730.hpp"

#if defined(_MSC_VER)
#define PKG_CHEAT44_THISCALL __thiscall
#else
#define PKG_CHEAT44_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::cheat_func44h_0067e730 {

Ports* g_cheat_func44h_ports = nullptr;

// 0x0067e730  PUSH ESI                     register saves; no source effect
// 0x0067e734  PUSH EDI
// 0x0067e73c  PUSH EBX                     -- on the fall-through path only,
//                                              see the empty-chain exit below
extern "C" void PKG_CHEAT44_THISCALL func44h_0067e730(
    OpaqueWord* manager, OpaqueWord event_argument) {
  // 0x0067e731  MOV ESI,dword ptr [ECX + 0x50]    the chain head, read once
  OpaqueWord* node = chain_first(manager);
  // 0x0067e735  LEA EDI,dword ptr [ECX + 0x4C]    the chain end marker is the
  //                                              ADDRESS of the receiver word
  //                                              at +0x4C; its stored value is
  //                                              never loaded by this body
  OpaqueWord* const terminator = chain_terminator(manager);
  // 0x0067e738  CMP ESI,EDI
  // 0x0067e73a  JZ 0x0067e75e                    empty chain: straight to
  //                                              POP EDI, so EBX is neither
  //                                              saved nor restored and the
  //                                              argument is never read
  if (node == terminator) {
    return;
  }
  // 0x0067e73c  PUSH EBX
  // 0x0067e73d  MOV EBX,dword ptr [ESP + 0x10]   entry_ESP+0x4: the one
  //                                              ordinary argument, hoisted
  //                                              before the loop head and
  //                                              reused by every iteration
  const OpaqueWord event = event_argument;
  Ports& ports = *g_cheat_func44h_ports;
  // 0x0067e759  CMP ESI,EDI / 0x0067e75b  JNZ 0x0067e741   bottom test, back
  //                                              edge in body
  while (node != terminator) {
    // 0x0067e741  MOV ECX,dword ptr [ESI + 0x10] the receiver this node
    //                                              dispatches through
    OpaqueWord* const receiver = node_receiver(node);
    // 0x0067e744  MOV EAX,dword ptr [ECX]         the receiver's table word,
    // 0x0067e746  MOV EDX,dword ptr [EAX + 0x1C] then the entry at +0x1C --
    //                                              both reloaded every step, so
    //                                              consecutive nodes may use
    //                                              different tables
    // 0x0067e749  PUSH EBX                       trailing argument
    // 0x0067e74a  PUSH 0x0                        leading argument, literally 0
    // 0x0067e74c  CALL EDX                        the body's only indirect
    //                                              transfer; the callee must
    //                                              remove its own eight bytes or
    //                                              ESP would grow every step
    receiver_entry(receiver)(receiver, static_cast<int>(kLeadingWord), event);
    // 0x0067e74e  PUSH ESI                       argument for the stepper
    // 0x0067e74f  CALL 0x00921580
    // 0x0067e754  MOV ESI,EAX
    // 0x0067e756  ADD ESP,0x4                     cdecl: the body drops the
    //                                              argument itself
    node = ports.next_00921580(node);
  }
  // 0x0067e75d  POP EBX / 0x0067e75e  POP EDI / 0x0067e75f  POP ESI
  // 0x0067e760  RET 0x4                          no value is produced: EAX is
  //                                              written only by the table load
  //                                              and by the 0x00921580 result,
  //                                              both consumed by the loop. The
  //                                              callee removes the 4-byte stack
  //                                              argument.
}

}

#undef PKG_CHEAT44_THISCALL
