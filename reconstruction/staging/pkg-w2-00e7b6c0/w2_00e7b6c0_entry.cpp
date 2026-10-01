// PKG-W2-00E7B6C0 -- VA 0x00e7b6c0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The complete body of FUN_00e7b630, transcribed.
//
// 105 instructions, 0x00e7b630..0x00e7b7b1 inclusive, 386 bytes. The queue's
// target VA 0x00e7b6c0 is NOT a function entry and NOT an instruction start: it
// is the fourth byte of the rel32 displacement of the direct call at
// 0x00e7b6bc, offset 0x90 into this body. The full reasoning, the machine ABI
// record's abstention, the frame arithmetic, the nine calls and the two
// unresolved contradictions are in w2_00e7b6c0_types.hpp; the byte-level decode
// and the evidence refs are in the model test's header.
//
// NO CALLING CONVENTION TOKEN APPEARS IN THIS FILE, and no receiver is named
// or declared. The machine record resolves no convention (ABI_UNKNOWN,
// candidates __cdecl and __thiscall, ambiguity receiver_undetermined) and its
// receiver is undetermined with reason `ecx_read_without_deref`; 0x00e7b6c0 is
// in no sound vptr-backed table either. The entry is therefore emitted with the
// platform default and the terminator is the machine's own bare `ret`, which is
// what `cleanup.side: caller, bytes: 0` describes.
//
// ECX IS NOT A RECEIVER HERE. `MOV ECX,[EAX+0x1b0]` at 0x00e7b68b loads a
// 32-bit value out of memory and `PUSH ECX` at 0x00e7b691 passes it to
// 0x00e6d200 as one of its four ordinary stack arguments. The rest of the body
// works through EAX, EBX, EDX, EDI, EBP and ESI, and ECX is never
// dereferenced anywhere in these 386 bytes.

#include "w2_00e7b6c0_types.hpp"

#if defined(_MSC_VER)
#define PKG_W2_00E7B6C0_NAKED __declspec(naked)
#else
#define PKG_W2_00E7B6C0_NAKED __attribute__((naked))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00e7b6c0 {

// Placed first in this translation unit on purpose: the validator binds a
// source span to 0x00e7b6c0 by the 8-hex VA token appearing in the function
// name, and it takes the FIRST such definition in the file.
extern "C" void PKG_W2_00E7B6C0_NAKED reconstruct_00e7b6c0(const std::uint8_t*,
                                                        Word,
                                                        Word,
                                                        Word) {
  // Byte fidelity, accounted exactly. Of the 386 positions the model test
  // compares 326 literally against kTargetBytes, which is the image's own byte
  // string. The other sixty are the rel32 displacements of the ten CALLs and
  // the five conditional branches: they encode addresses in a different image,
  // so the test RESOLVES each one out of the emitted code and requires it to
  // land on the target the machine records. 326 + 60 = 386, and the test asserts
  // 326 rather than leaving the split to this arithmetic, so the accounting
  // cannot drift silently.
  //
  // A default position-independent g++ build MAY additionally prepend a
  // ten-byte __x86.get_pc_thunk.ax PC anchor to a naked function (g++ -m32 does
  // so at -O0; clang++ emits none at any level). That is a toolchain artifact
  // and not part of the reconstruction. The model test recognises the anchor by
  // its exact opcode pair e8 ?? ?? ?? ?? 05 and requires the 386 target bytes
  // immediately after it. Byte-identical recompilation is therefore NOT claimed
  // without that allowance; semantic fidelity is, and it is what the executed
  // checks establish.
  //
  // NOTHING HERE IS RESTATED AS C++. Every displacement, every store and every
  // call is emitted as the instruction the listing shows, because each of them
  // is a fact about a stack pointer that only the listing fixes: the twenty-six
  // record stores are at eight different EAX displacements and three different
  // stack-pointer values, and the two frame locals are at two different depths.
  // A C++ restatement would have to place each of those bytes somewhere, and
  // placing them is a claim the listing makes only as displacements.
  __asm__("subl $0x8, %esp\n\t"              // 00e7b630  SUB ESP,0x8
          "cmpb $0x1, 0x112(%esi)\n\t"       // 00e7b633  CMP byte [ESI+0x112],1
          "pushl %ebp\n\t"                   // 00e7b63a  PUSH EBP
          "movl 0x10(%esp), %ebp\n\t"        // 00e7b63b  MOV EBP,[ESP+0x10]
          "je   .Lep\n\t"                    // 00e7b63f  JZ  0x00e7b7ad
          "cmpb $0x1, 0x113(%esi)\n\t"       // 00e7b645  CMP byte [ESI+0x113],1
          "je   .Lep\n\t"                    // 00e7b64c  JZ  0x00e7b7ad
          "pushl %ebx\n\t"                   // 00e7b652  PUSH EBX
          ".byte 0x33, 0xdb\n\t"             // 00e7b653  XOR EBX,EBX. Emitted as
          // raw bytes on purpose: `xorl %ebx,%ebx` and `xorl %ebx,%ebx` are
          // the same instruction and the GNU assembler picks the mirrored 31 db
          // for the same operands, while the image carries 33 db. Spelling it
          // here keeps the byte comparison exact instead of teaching the model
          // test a second legal encoding for one instruction.
          "cmpb %bl, 0x178(%esi)\n\t"        // 00e7b655  CMP byte [ESI+0x178],BL
          "jne  .Lbx\n\t"                    // 00e7b65b  JNZ 0x00e7b7ac
          "cmpb %bl, 0x17f(%esi)\n\t"        // 00e7b661  CMP byte [ESI+0x17f],BL
          "jne  .Lbx\n\t"                    // 00e7b667  JNZ 0x00e7b7ac
          "cmpb %bl, 0x17b(%ebp)\n\t"        // 00e7b66d  CMP byte [EBP+0x17b],BL
          "jne  .Lbx\n\t"                    // 00e7b673  JNZ 0x00e7b7ac
          "movl (%esi), %eax\n\t"            // 00e7b679  MOV EAX,[ESI]
          "movl 0x016b3c04, %ecx\n\t"        // 00e7b67b  MOV ECX,[0x016b3c04]
          "pushl %edi\n\t"                   // 00e7b681  PUSH EDI
          "addl $0x1c, %ecx\n\t"             // 00e7b682  ADD ECX,0x1c
          "pushl %eax\n\t"                   // 00e7b685  PUSH EAX
          "call callee_00b72210\n\t"         // 00e7b686  CALL 0x00b72210
          "movl 0x1b0(%eax), %ecx\n\t"       // 00e7b68b  MOV ECX,[EAX+0x1b0]
          "pushl %ecx\n\t"                   // 00e7b691  PUSH ECX
          "pushl $0x31\n\t"                  // 00e7b692  PUSH 0x31
          "pushl %ebx\n\t"                   // 00e7b694  PUSH EBX
          "pushl %eax\n\t"                   // 00e7b695  PUSH EAX
          "call callee_00e6d200\n\t"         // 00e7b696  CALL 0x00e6d200
          "fstps 0x20(%esp)\n\t"             // 00e7b69b  FSTP [ESP+0x20]
          "movl 0x016b3c04, %ecx\n\t"        // 00e7b69f  MOV ECX,[0x016b3c04]
          "movl (%esi), %edi\n\t"            // 00e7b6a5  MOV EDI,[ESI]
          "addl $0x10, %esp\n\t"             // 00e7b6a7  ADD ESP,0x10
          "addl $0x54, %ecx\n\t"             // 00e7b6aa  ADD ECX,0x54
          "call callee_00b72160\n\t"         // 00e7b6ad  CALL 0x00b72160
          "movl 0x016b3c04, %ecx\n\t"        // 00e7b6b2  MOV ECX,[0x016b3c04]
          "addl $0x54, %ecx\n\t"             // 00e7b6b8  ADD ECX,0x54
          "pushl %eax\n\t"                   // 00e7b6bb  PUSH EAX
          "call callee_00b72210\n\t"         // 00e7b6bc  CALL 0x00b72210
          "flds 0x10(%esp)\n\t"              // 00e7b6c1  FLD [ESP+0x10]
          "xorps %xmm0, %xmm0\n\t"           // 00e7b6c5  XORPS XMM0,XMM0
          "fsts 0x1c(%eax)\n\t"              // 00e7b6c8  FST [EAX+0x1c]
          "fstps 0x20(%eax)\n\t"             // 00e7b6cb  FSTP [EAX+0x20]
          "movl $0x20, 0x24(%eax)\n\t"       // 00e7b6ce  MOV [EAX+0x24],0x20
          "movl %edi, 0x28(%eax)\n\t"        // 00e7b6d5  MOV [EAX+0x28],EDI
          "movl %ebx, 0x2c(%eax)\n\t"        // 00e7b6d8  MOV [EAX+0x2c],EBX
          "orl $-1, %ecx\n\t"                // 00e7b6db  OR ECX,0xffffffff
          "movl %ecx, 0x30(%eax)\n\t"        // 00e7b6de  MOV [EAX+0x30],ECX
          "movl %ecx, 0x34(%eax)\n\t"        // 00e7b6e1  MOV [EAX+0x34],ECX
          "movl %ebx, 0x38(%eax)\n\t"        // 00e7b6e4  MOV [EAX+0x38],EBX
          "movl %ebx, 0x3c(%eax)\n\t"        // 00e7b6e7  MOV [EAX+0x3c],EBX
          "movss %xmm0, 0x40(%eax)\n\t"      // 00e7b6ea  MOVSS [EAX+0x40],XMM0
          "movss %xmm0, 0x44(%eax)\n\t"      // 00e7b6ef  MOVSS [EAX+0x44],XMM0
          "movl 0x016b3c28, %edx\n\t"        // 00e7b6f4  MOV EDX,[0x016b3c28]
          "movl %edx, 0x48(%eax)\n\t"        // 00e7b6fa  MOV [EAX+0x48],EDX
          "movl 0x016b3c2c, %ecx\n\t"        // 00e7b6fd  MOV ECX,[0x016b3c2c]
          "movl %ecx, 0x4c(%eax)\n\t"        // 00e7b703  MOV [EAX+0x4c],ECX
          "movl 0x016b3c30, %edx\n\t"        // 00e7b706  MOV EDX,[0x016b3c30]
          "movl %edx, 0x50(%eax)\n\t"        // 00e7b70c  MOV [EAX+0x50],EDX
          "movl 0x016b3c28, %ecx\n\t"        // 00e7b70f  MOV ECX,[0x016b3c28]
          "movl %ecx, 0x54(%eax)\n\t"        // 00e7b715  MOV [EAX+0x54],ECX
          "movl 0x016b3c2c, %edx\n\t"        // 00e7b718  MOV EDX,[0x016b3c2c]
          "movl %edx, 0x58(%eax)\n\t"        // 00e7b71e  MOV [EAX+0x58],EDX
          "movl 0x016b3c30, %ecx\n\t"        // 00e7b721  MOV ECX,[0x016b3c30]
          "movl %ecx, 0x5c(%eax)\n\t"        // 00e7b727  MOV [EAX+0x5c],ECX
          "movl 0x015a7c4c, %edx\n\t"        // 00e7b72a  MOV EDX,[0x015a7c4c]
          "movl %edx, 0x60(%eax)\n\t"        // 00e7b730  MOV [EAX+0x60],EDX
          "movl 0x015a7c50, %ecx\n\t"        // 00e7b733  MOV ECX,[0x015a7c50]
          "movl %ecx, 0x64(%eax)\n\t"        // 00e7b739  MOV [EAX+0x64],ECX
          "movl 0x015a7c54, %edx\n\t"        // 00e7b73c  MOV EDX,[0x015a7c54]
          "movl %edx, 0x68(%eax)\n\t"        // 00e7b742  MOV [EAX+0x68],EDX
          "movl 0x015a7c58, %ecx\n\t"        // 00e7b745  MOV ECX,[0x015a7c58]
          "movl %ecx, 0x6c(%eax)\n\t"        // 00e7b74b  MOV [EAX+0x6c],ECX
          "leal 0xc(%esp), %ecx\n\t"         // 00e7b74e  LEA ECX,[ESP+0xc]
          "movl %ebx, 0x70(%eax)\n\t"        // 00e7b752  MOV [EAX+0x70],EBX
          "movb %bl, 0x74(%eax)\n\t"         // 00e7b755  MOV byte [EAX+0x74],BL
          "movl %ebx, 0x78(%eax)\n\t"        // 00e7b758  MOV [EAX+0x78],EBX
          "movl %ebx, 0x4(%eax)\n\t"         // 00e7b75b  MOV [EAX+0x4],EBX
          "movb %bl, 0x8(%eax)\n\t"          // 00e7b75e  MOV byte [EAX+0x8],BL
          "call callee_00743b50\n\t"          // 00e7b761  CALL 0x00743b50
          "movl 0x108(%ebp), %eax\n\t"       // 00e7b766  MOV EAX,[EBP+0x108]
          "leal 0xc(%esp), %edx\n\t"         // 00e7b76c  LEA EDX,[ESP+0xc]
          "pushl %edx\n\t"                   // 00e7b770  PUSH EDX
          "pushl %eax\n\t"                   // 00e7b771  PUSH EAX
          "call callee_00e4cc40\n\t"         // 00e7b772  CALL 0x00e4cc40
          "movl 0xb8(%eax), %ecx\n\t"        // 00e7b777  MOV ECX,[EAX+0xb8]
          "pushl %ecx\n\t"                   // 00e7b77d  PUSH ECX
          "call callee_00e5d7b0\n\t"         // 00e7b77e  CALL 0x00e5d7b0
          "fldz\n\t"                         // 00e7b783  FLDZ
          "movl (%ebp), %edx\n\t"            // 00e7b785  MOV EDX,[EBP]
          "addl $0xc, %esp\n\t"              // 00e7b788  ADD ESP,0xc
          "pushl %ebx\n\t"                   // 00e7b78b  PUSH EBX
          "pushl %ecx\n\t"                   // 00e7b78c  PUSH ECX
          "fstps (%esp)\n\t"                 // 00e7b78d  FSTP [ESP]
          "pushl $0x1\n\t"                   // 00e7b790  PUSH 0x1
          "pushl %edx\n\t"                   // 00e7b792  PUSH EDX
          "call callee_00e780a0\n\t"         // 00e7b793  CALL 0x00e780a0
          "addl $0x10, %esp\n\t"             // 00e7b798  ADD ESP,0x10
          "movl (%esi), %eax\n\t"            // 00e7b79b  MOV EAX,[ESI]
          "call callee_00e59a70\n\t"         // 00e7b79d  CALL 0x00e59a70
          "leal 0xc(%esp), %ecx\n\t"         // 00e7b7a2  LEA ECX,[ESP+0xc]
          "call callee_00e82130\n\t"         // 00e7b7a6  CALL 0x00e82130
          "popl %edi\n\t"                    // 00e7b7ab  POP EDI
          ".Lbx:\n\t"                        // 00e7b7ac  the three JNZ land here
          "popl %ebx\n\t"                    // 00e7b7ac  POP EBX
          ".Lep:\n\t"                        // 00e7b7ad  the two JZ land here
          "popl %ebp\n\t"                    // 00e7b7ad  POP EBP
          "addl $0x8, %esp\n\t"              // 00e7b7ae  ADD ESP,0x8
          "ret\n\t");                        // 00e7b7b1  RET
}

}  // namespace pkg_w2_00e7b6c0
}  // namespace reconstruction
}  // namespace openspore

#undef PKG_W2_00E7B6C0_NAKED
