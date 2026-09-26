#include "cheat_dispatch_0067e730.hpp"

#if defined(_MSC_VER)
#define PKG_CHEAT_CDECL __cdecl
#define PKG_CHEAT_THISCALL __thiscall
#define PKG_CHEAT_NOINLINE __declspec(noinline)
#else
#define PKG_CHEAT_CDECL __attribute__((cdecl))
#define PKG_CHEAT_THISCALL __attribute__((thiscall))
#define PKG_CHEAT_NOINLINE __attribute__((noinline))
#endif

namespace openspore::reconstruction::dogfood_after_02_0067e730 {

DispatchPorts* g_dispatch_ports = nullptr;

namespace detail {

// Reproduces 0x0067e749..0x0067e74c exactly: the receiver goes to ECX, the two
// stack arguments are pushed right to left so the flag lands at [ESP+0x0] and
// the event word at [ESP+0x4], and the callee reclaims its own eight bytes
// (__thiscall with two stack arguments). Nothing is popped afterwards in the
// original either, so nothing is popped here.
template <typename Entry, typename Receiver, typename Arg1, typename Arg2>
PKG_CHEAT_NOINLINE void call_entry(Entry entry, Receiver receiver, Arg1 first,
                                   Arg2 second) {
  __asm__ volatile(
      "movl %1, %%eax\n\t"
      "movl %0, %%ecx\n\t"
      "pushl %3\n\t"
      "pushl %2\n\t"
      "call *%%eax\n\t"
      :
      : "r"(receiver), "m"(entry), "r"(first), "r"(second)
      : "eax", "cc", "ecx", "edx", "memory");
}

}

// 0x0067e730  PUSH ESI
// 0x0067e731  MOV ESI,[ECX+0x50]        ; chain head
// 0x0067e735  LEA EDI,[ECX+0x4c]        ; address of the embedded terminator
// 0x0067e73a  JZ  0x0067e75e            ; empty chain leaves without touching EBX
// 0x0067e73d  MOV EBX,[ESP+0x10]        ; the one stack argument, hoisted once
// 0x0067e741  MOV ECX,[ESI+0x10]        ; per-node receiver
// 0x0067e746  MOV EDX,[EAX+0x1c]        ; table entry seven
// 0x0067e74a  PUSH 0x0                  ; the flag argument, literally zero
// 0x0067e74c  CALL EDX
// 0x0067e74f  CALL 0x00921580           ; cdecl, node in, successor out
// 0x0067e75b  JNZ 0x0067e741
// 0x0067e760  RET 0x4                   ; callee drops the stack argument
//
// The loop keeps no state of its own: EBX is loaded before the head instruction
// at 0x0067e741 and the back edge skips it, so the event word is hoisted out of
// the loop exactly as the machine hoists it.
extern "C" void PKG_CHEAT_THISCALL cCheatManager_func44h_0067e730(
    CheatManager* manager, OpaqueWord event_argument) {
  DispatchNode* node = chain_first(manager);
  DispatchNode* const terminator = chain_terminator(manager);
  DispatchPorts& ports = *g_dispatch_ports;
  while (node != terminator) {
    call_entry(receiver_entry(node_receiver(node)), node_receiver(node), false,
               event_argument);
    node = ports.next_00921580(node);
  }
}

}

#undef PKG_CHEAT_CDECL
#undef PKG_CHEAT_THISCALL
#undef PKG_CHEAT_NOINLINE
