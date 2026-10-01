// Bounded reconstruction of SporeApp.exe 3.1.0.22 at 0x0067dc80
// (App::IMessageManager::Get -- see the header's NAMING section for why the
// model is the scalar deleting-destructor wrapper the bytes actually show).
//
// Every line below is read off the 30 bytes quoted in the header; the address
// in each comment is the machine instruction the line models. Nothing is
// inferred from behaviour, and this body writes no memory, so every access it
// models is a read.

#include "get_0067dc80.hpp"

namespace openspore::reconstruction::pkg_app_imessage_manager_dtor {

MessageManagerDtorPorts g_imessage_manager_dtor_ports{};

namespace {

// Stable call targets for the transcription below. They forward to the
// injectable ports, so the two machine callees stay swappable while the
// instruction sequence of the body is preserved exactly.
extern "C" void PKG_IMSG_THISCALL imsg_complete_dtor_shim_0067db10(
    OpaqueMessageManagerOwner* self) {
  MessageManagerDtorPorts& ports = g_imessage_manager_dtor_ports;
  if (ports.complete_dtor_0067db10 != nullptr) {
    ports.complete_dtor_0067db10(self);
  }
}

extern "C" void PKG_IMSG_CDECL imsg_global_free_shim_00f47380(
    const void* pointer) {
  MessageManagerDtorPorts& ports = g_imessage_manager_dtor_ports;
  if (ports.global_free_00f47380 != nullptr) {
    ports.global_free_00f47380(pointer);
  }
}

}  // namespace

// The reconstructed entry point, instruction for instruction.
//
//   0067dc80  PUSH ESI                   save the callee-saved register the body
//                                        is about to clobber
//   0067dc81  MOV  ESI,ECX                spill the receiver; ECX is left intact
//                                        so the next call is still thiscall on
//                                        the same object
//   0067dc83  CALL 0x0067db10            the complete-object destructor, run
//                                        UNCONDITIONALLY -- before the flag is
//                                        read, so it runs on both paths
//   0067dc88  TEST byte ptr [ESP + 0x8],0x1
//                                        the frame here is saved ESI, return
//                                        address, argument -- hence +0x8 and not
//                                        +0x4 -- and the test is a BYTE test
//                                        (f6 44 24 08 01), so only bit 0 of
//                                        that byte is examined and the other
//                                        31 bits of the slot are never read
//   0067dc8d  JZ   0x0067dc98            bit 0 clear: skip the release
//   0067dc8f  PUSH ESI                   the release takes the receiver
//   0067dc90  CALL 0x00f47380            0x00f47380 is cdecl with one argument
//   0067dc95  ADD  ESP,0x4               and cleans nothing, so the body drops it
//   0067dc98  MOV  EAX,ESI               the receiver is returned on BOTH paths
//   0067dc9a  POP  ESI                   restore the saved register
//   0067dc9b  RET  0x4                   the callee pops the one dword argument
//
// There is no null check on the receiver anywhere in this body: a null receiver
// is forwarded to both callees, and 0x00f47380's own TEST EAX,EAX is the only
// guard on this path.
//
// Byte fidelity: with -fno-pic -no-pie the emitted sequence is instruction for
// instruction the original 30 bytes. Two encodings differ for free, because
// both spellings denote the same instruction: the original encodes the register
// moves as 8b f1 / 8b c6 (mov r32,r/m32) where the assembler picks 89 ce / 89 f0
// (mov r/m32,r32), and the two `call` displacements address the local shims
// rather than the original targets. Under a default position-independent build
// the compiler additionally prepends a nine-byte __x86.get_pc_thunk.ax PC
// anchor, which is a toolchain artifact and not part of the reconstruction.
extern "C" void* PKG_IMSG_NAKED_THISCALL
get_0067dc80(OpaqueMessageManagerOwner*, OpaqueWord) {
  __asm__("pushl %esi\n\t"          // 0067dc80  PUSH ESI
          "movl %ecx, %esi\n\t"     // 0067dc81  MOV  ESI,ECX
          "call imsg_complete_dtor_shim_0067db10\n\t"  // 0067dc83  CALL 0x0067db10
          "testb $1, 8(%esp)\n\t"   // 0067dc88  TEST byte ptr [ESP+0x8],0x1
          "jz 1f\n\t"               // 0067dc8d  JZ   0x0067dc98
          "pushl %esi\n\t"          // 0067dc8f  PUSH ESI
          "call imsg_global_free_shim_00f47380\n\t"    // 0067dc90  CALL 0x00f47380
          "addl $4, %esp\n\t"       // 0067dc95  ADD  ESP,0x4
          "1:\n\t"                  // 0067dc98
          "movl %esi, %eax\n\t"     // 0067dc98  MOV  EAX,ESI
          "popl %esi\n\t"           // 0067dc9a  POP  ESI
          "ret $4\n\t");            // 0067dc9b  RET  0x4
}

// The same three observable operations in ordinary C++, for the model test:
//   1. the complete destructor runs on every flag value;
//   2. the release runs only for bit 0 of the flag, strictly after the
//      destructor, and receives the receiver;
//   3. the receiver is returned either way.
extern "C" void* PKG_IMSG_CDECL
app_imessage_manager_delete_dispatch_0067dc80(OpaqueMessageManagerOwner* self,
                                              OpaqueWord deleting_flag) {
  MessageManagerDtorPorts& ports = g_imessage_manager_dtor_ports;
  // 0067dc83  CALL 0x0067db10 -- unconditional, ahead of the flag test
  if (ports.complete_dtor_0067db10 != nullptr) {
    ports.complete_dtor_0067db10(self);
  }
  // 0067dc88  TEST byte ptr [ESP+0x8],0x1 -- one bit of one byte, nothing else
  if ((deleting_flag & 1u) != 0u) {
    // 0067dc8f..0x0067dc95  PUSH ESI / CALL 0x00f47380 / ADD ESP,0x4
    imsg_global_free_shim_00f47380(self);
  }
  // 0067dc98  MOV EAX,ESI -- on both paths
  return self;
}

}  // namespace openspore::reconstruction::pkg_app_imessage_manager_dtor

#undef PKG_IMSG_CDECL
#undef PKG_IMSG_NAKED_THISCALL
#undef PKG_IMSG_THISCALL
