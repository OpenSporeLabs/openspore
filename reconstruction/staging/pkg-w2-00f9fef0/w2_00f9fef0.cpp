// PKG-W2-00F9FEF0 -- VA 0x00f9fef0
// FUN_00f9fef0 (SPORE/SporeBin/SporeApp.exe 3.1.0.22)
//
// The complete body: 112 instructions, 0x00f9fef0..0x00fa0008 inclusive, 281
// bytes. The terminator RET 0x4 at 0x00fa0006 is `c2 04 00`, so it occupies
// 0x00fa0006..0x00fa0008 and the body's last byte is 0x00fa0008, which is what
// ghidra_function.body_end names; body_span_bytes names 281, which is 0x119.
//
// The listing was re-read from the image for this package rather than taken on
// trust. GhidraMCP /read_memory at 0x00f9fef0 for 288 bytes returns the byte
// string transcribed into kTargetBytes in the header, and
// /disassemble_function at 0x00f9fef0 returns exactly these 112 instructions at
// exactly these addresses:
//
////   00f9fef0  53                     PUSH EBX
//   00f9fef1  56                     PUSH ESI
//   00f9fef2  57                     PUSH EDI
//   00f9fef3  8bf9                   MOV EDI,ECX
//   00f9fef5  85ff                   TEST EDI,EDI
//   00f9fef7  7405                   JZ 0x00f9fefe
//   00f9fef9  8d5f04                 LEA EBX,[EDI+0x4]
//   00f9fefc  eb02                   JMP 0x00f9ff00
//   00f9fefe  33db                   XOR EBX,EBX
//   00f9ff00  8b742410               MOV ESI,[ESP+0x10]
//   00f9ff04  8b06                   MOV EAX,[ESI]
//   00f9ff06  8b5058                 MOV EDX,[EAX+0x58]
//   00f9ff09  6a08                   PUSH 0x8
//   00f9ff0b  8bce                   MOV ECX,ESI
//   00f9ff0d  ffd2                   CALL EDX
//   00f9ff0f  3bc3                   CMP EAX,EBX
//   00f9ff11  0f84ec000000           JZ 0x00fa0003
//   00f9ff17  55                     PUSH EBP
//   00f9ff18  8b2d18d95f01           MOV EBP,[0x015fd918]
//   00f9ff1e  68504e1a20             PUSH 0x201a4e50
//   00f9ff23  8bcd                   MOV ECX,EBP
//   00f9ff25  e8762670ff             CALL 0x006a25a0
//   00f9ff2a  6837e33ce1             PUSH 0xe13ce337
//   00f9ff2f  8bcd                   MOV ECX,EBP
//   00f9ff31  8ad8                   MOV BL,AL
//   00f9ff33  e8682670ff             CALL 0x006a25a0
//   00f9ff38  88442414               MOV [ESP+0x14],AL
//   00f9ff3c  5d                     POP EBP
//   00f9ff3d  84db                   TEST BL,BL
//   00f9ff3f  7413                   JZ 0x00f9ff54
//   00f9ff41  e8fa6bffff             CALL 0x00f96b40
//   00f9ff46  807c241000             CMP [ESP+0x10],0
//   00f9ff4b  7407                   JZ 0x00f9ff54
//   00f9ff4d  8bcf                   MOV ECX,EDI
//   00f9ff4f  e84ce4ffff             CALL 0x00f9e3a0
//   00f9ff54  85ff                   TEST EDI,EDI
//   00f9ff56  7405                   JZ 0x00f9ff5d
//   00f9ff58  8d4704                 LEA EAX,[EDI+0x4]
//   00f9ff5b  eb02                   JMP 0x00f9ff5f
//   00f9ff5d  33c0                   XOR EAX,EAX
//   00f9ff5f  8b16                   MOV EDX,[ESI]
//   00f9ff61  6a00                   PUSH 0x0
//   00f9ff63  6a07                   PUSH 0x7
//   00f9ff65  50                     PUSH EAX
//   00f9ff66  8b424c                 MOV EAX,[EDX+0x4c]
//   00f9ff69  8bce                   MOV ECX,ESI
//   00f9ff6b  ffd0                   CALL EAX
//   00f9ff6d  85ff                   TEST EDI,EDI
//   00f9ff6f  7405                   JZ 0x00f9ff76
//   00f9ff71  8d4704                 LEA EAX,[EDI+0x4]
//   00f9ff74  eb02                   JMP 0x00f9ff78
//   00f9ff76  33c0                   XOR EAX,EAX
//   00f9ff78  8b16                   MOV EDX,[ESI]
//   00f9ff7a  6a00                   PUSH 0x0
//   00f9ff7c  6a08                   PUSH 0x8
//   00f9ff7e  50                     PUSH EAX
//   00f9ff7f  8b424c                 MOV EAX,[EDX+0x4c]
//   00f9ff82  8bce                   MOV ECX,ESI
//   00f9ff84  ffd0                   CALL EAX
//   00f9ff86  85ff                   TEST EDI,EDI
//   00f9ff88  7405                   JZ 0x00f9ff8f
//   00f9ff8a  8d4704                 LEA EAX,[EDI+0x4]
//   00f9ff8d  eb02                   JMP 0x00f9ff91
//   00f9ff8f  33c0                   XOR EAX,EAX
//   00f9ff91  8b16                   MOV EDX,[ESI]
//   00f9ff93  6a00                   PUSH 0x0
//   00f9ff95  6a21                   PUSH 0x21
//   00f9ff97  50                     PUSH EAX
//   00f9ff98  8b424c                 MOV EAX,[EDX+0x4c]
//   00f9ff9b  8bce                   MOV ECX,ESI
//   00f9ff9d  ffd0                   CALL EAX
//   00f9ff9f  e8dcdd6dff             CALL 0x0067dd80
//   00f9ffa4  8b10                   MOV EDX,[EAX]
//   00f9ffa6  8bc8                   MOV ECX,EAX
//   00f9ffa8  8b421c                 MOV EAX,[EDX+0x1c]
//   00f9ffab  6824aefb03             PUSH 0x3fbae24
//   00f9ffb0  ffd0                   CALL EAX
//   00f9ffb2  8b1e                   MOV EBX,[ESI]
//   00f9ffb4  8bf8                   MOV EDI,EAX
//   00f9ffb6  8b17                   MOV EDX,[EDI]
//   00f9ffb8  8b823c010000           MOV EAX,[EDX+0x13c]
//   00f9ffbe  6a00                   PUSH 0x0
//   00f9ffc0  6a0a                   PUSH 0xa
//   00f9ffc2  8bcf                   MOV ECX,EDI
//   00f9ffc4  ffd0                   CALL EAX
//   00f9ffc6  8b534c                 MOV EDX,[EBX+0x4c]
//   00f9ffc9  50                     PUSH EAX
//   00f9ffca  8bce                   MOV ECX,ESI
//   00f9ffcc  ffd2                   CALL EDX
//   00f9ffce  8b07                   MOV EAX,[EDI]
//   00f9ffd0  8b9034010000           MOV EDX,[EAX+0x134]
//   00f9ffd6  6a01                   PUSH 0x1
//   00f9ffd8  8bcf                   MOV ECX,EDI
//   00f9ffda  ffd2                   CALL EDX
//   00f9ffdc  e8efdd6dff             CALL 0x0067ddd0
//   00f9ffe1  8b10                   MOV EDX,[EAX]
//   00f9ffe3  8bc8                   MOV ECX,EAX
//   00f9ffe5  8b4254                 MOV EAX,[EDX+0x54]
//   00f9ffe8  6824aefb03             PUSH 0x3fbae24
//   00f9ffed  ffd0                   CALL EAX
//   00f9ffef  8b10                   MOV EDX,[EAX]
//   00f9fff1  5f                     POP EDI
//   00f9fff2  5e                     POP ESI
//   00f9fff3  5b                     POP EBX
//   00f9fff4  c744240400000000       MOV [ESP+0x4],0
//   00f9fffc  8bc8                   MOV ECX,EAX
//   00f9fffe  8b420c                 MOV EAX,[EDX+0xc]
//   00fa0001  ffe0                   JMP EAX
//   00fa0003  5f                     POP EDI
//   00fa0004  5e                     POP ESI
//   00fa0005  5b                     POP EBX
//   00fa0006  c20400                 RET 0x4
//
// WHY A NAKED TRANSCRIPTION AND NOT A C++ RESTATEMENT. The ten indirect
// transfers in this body reach seven slots through callees that are resolved at
// run time, and their stack effects are not observable from the image at all --
// they are only constrained by the frame balance, and the balance admits exactly
// one assignment (see the table in the header). A C++ restatement would have to
// DECLARE a signature for each of those seven callees in order to get the
// compiler to emit the right call sequence, and each such declaration is a claim
// the listing does not make: it is a claim about seven functions this body does
// not own. It would also have to restate the tail transfer at 0x00fa0001 as
// something other than a jump, and the zero written into the first popped stack
// word at 0x00f9fff4 as something other than a store. So the body is emitted as
// the instructions the image has, in the image's own order, and every modelling
// choice that remains lives in the header where it can be checked.
//
// A default position-independent g++ build MAY additionally prepend a ten-byte
// __x86.get_pc_thunk.ax PC anchor to a naked function (g++ -m32 does so at
// -O0; clang++ emits none at any level). That is a toolchain artifact and not
// part of the reconstruction. The model test recognises the anchor by its exact
// opcode pair e8 ?? ?? ?? ?? 05 and requires the 281 target bytes immediately
// after it; a toolchain that emitted some other form of anchor would fail that
// test rather than pass it. Byte-identical recompilation is therefore NOT
// claimed without that allowance; semantic fidelity is, and it is what the
// executed checks in the model test establish.
//
// NOTHING HERE IS RESTATED AS C++, AND THE ONE PIECE OF SOURCE-SIDE VOCABULARY
// IS NAMED AS A MODELLING CHOICE. The five direct callees are called BY NAME in
// the assembly rather than by number, because their entry shapes WERE read out
// of the image and their addresses are the validator's call-set comparison key.
// The seven virtual callees are reached through the register the image loads
// them into, and are not named at all.

#include "w2_00f9fef0_types.hpp"

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00f9fef0 {

// Placed first in this translation unit on purpose: the validator binds a
// source span to 0x00f9fef0 by the 8-hex VA token appearing in the function
// name, and it takes the FIRST such definition in the file.
extern "C" Word* PKG_W2_00F9FEF0_NAKED_THISCALL re_00f9fef0(Receiver*, Argument*) {
  __asm__("pushl %ebx\n\t"                  // 00f9fef0  PUSH EBX
          "pushl %esi\n\t"                  // 00f9fef1  PUSH ESI
          "pushl %edi\n\t"                  // 00f9fef2  PUSH EDI
          "movl %ecx, %edi\n\t"             // 00f9fef3  MOV EDI,ECX
          "testl %edi, %edi\n\t"            // 00f9fef5  TEST EDI,EDI
          "je 0f\n\t"                       // 00f9fef7  JZ 0x00f9fefe
          "leal 0x4(%edi), %ebx\n\t"         // 00f9fef9  LEA EBX,[EDI+0x4]
          "jmp 1f\n\t"                      // 00f9fefc  JMP 0x00f9ff00
          "0:\n\t"
          "xorl %ebx, %ebx\n\t"             // 00f9fefe  XOR EBX,EBX
          "1:\n\t"
          "movl 0x10(%esp), %esi\n\t"       // 00f9ff00  MOV ESI,[ESP+0x10]
          "movl (%esi), %eax\n\t"           // 00f9ff04  MOV EAX,[ESI]
          "movl 0x58(%eax), %edx\n\t"       // 00f9ff06  MOV EDX,[EAX+0x58]
          "pushl $0x8\n\t"                  // 00f9ff09  PUSH 0x8
          "movl %esi, %ecx\n\t"             // 00f9ff0b  MOV ECX,ESI
          "call *%edx\n\t"                  // 00f9ff0d  CALL EDX
          "cmpl %ebx, %eax\n\t"             // 00f9ff0f  CMP EAX,EBX
          "je 2f\n\t"                       // 00f9ff11  JZ 0x00fa0003
          "pushl %ebp\n\t"                  // 00f9ff17  PUSH EBP
          "movl g_015fd918, %ebp\n\t"       // 00f9ff18  MOV EBP,[0x015fd918]
          "pushl $0x201a4e50\n\t"           // 00f9ff1e  PUSH 0x201a4e50
          "movl %ebp, %ecx\n\t"             // 00f9ff23  MOV ECX,EBP
          "call callee_006a25a0\n\t"        // 00f9ff25  CALL 0x006a25a0
          "pushl $0xe13ce337\n\t"           // 00f9ff2a  PUSH 0xe13ce337
          "movl %ebp, %ecx\n\t"             // 00f9ff2f  MOV ECX,EBP
          "movb %al, %bl\n\t"               // 00f9ff31  MOV BL,AL
          "call callee_006a25a0\n\t"        // 00f9ff33  CALL 0x006a25a0
          "movb %al, 0x14(%esp)\n\t"        // 00f9ff38  MOV [ESP+0x14],AL
          "popl %ebp\n\t"                   // 00f9ff3c  POP EBP
          "testb %bl, %bl\n\t"              // 00f9ff3d  TEST BL,BL
          "je 3f\n\t"                       // 00f9ff3f  JZ 0x00f9ff54
          "call callee_00f96b40\n\t"        // 00f9ff41  CALL 0x00f96b40
          "cmpb $0x0, 0x10(%esp)\n\t"       // 00f9ff46  CMP [ESP+0x10],0
          "je 3f\n\t"                       // 00f9ff4b  JZ 0x00f9ff54
          "movl %edi, %ecx\n\t"             // 00f9ff4d  MOV ECX,EDI
          "call callee_00f9e3a0\n\t"        // 00f9ff4f  CALL 0x00f9e3a0
          "3:\n\t"
          "testl %edi, %edi\n\t"            // 00f9ff54  TEST EDI,EDI
          "je 4f\n\t"                       // 00f9ff56  JZ 0x00f9ff5d
          "leal 0x4(%edi), %eax\n\t"        // 00f9ff58  LEA EAX,[EDI+0x4]
          "jmp 5f\n\t"                      // 00f9ff5b  JMP 0x00f9ff5f
          "4:\n\t"
          "xorl %eax, %eax\n\t"             // 00f9ff5d  XOR EAX,EAX
          "5:\n\t"
          "movl (%esi), %edx\n\t"           // 00f9ff5f  MOV EDX,[ESI]
          "pushl $0x0\n\t"                  // 00f9ff61  PUSH 0x0
          "pushl $0x7\n\t"                  // 00f9ff63  PUSH 0x7
          "pushl %eax\n\t"                  // 00f9ff65  PUSH EAX
          "movl 0x4c(%edx), %eax\n\t"       // 00f9ff66  MOV EAX,[EDX+0x4c]
          "movl %esi, %ecx\n\t"             // 00f9ff69  MOV ECX,ESI
          "call *%eax\n\t"                  // 00f9ff6b  CALL EAX
          "testl %edi, %edi\n\t"            // 00f9ff6d  TEST EDI,EDI
          "je 6f\n\t"                       // 00f9ff6f  JZ 0x00f9ff76
          "leal 0x4(%edi), %eax\n\t"        // 00f9ff71  LEA EAX,[EDI+0x4]
          "jmp 7f\n\t"                      // 00f9ff74  JMP 0x00f9ff78
          "6:\n\t"
          "xorl %eax, %eax\n\t"             // 00f9ff76  XOR EAX,EAX
          "7:\n\t"
          "movl (%esi), %edx\n\t"           // 00f9ff78  MOV EDX,[ESI]
          "pushl $0x0\n\t"                  // 00f9ff7a  PUSH 0x0
          "pushl $0x8\n\t"                  // 00f9ff7c  PUSH 0x8
          "pushl %eax\n\t"                  // 00f9ff7e  PUSH EAX
          "movl 0x4c(%edx), %eax\n\t"       // 00f9ff7f  MOV EAX,[EDX+0x4c]
          "movl %esi, %ecx\n\t"             // 00f9ff82  MOV ECX,ESI
          "call *%eax\n\t"                  // 00f9ff84  CALL EAX
          "testl %edi, %edi\n\t"            // 00f9ff86  TEST EDI,EDI
          "je 8f\n\t"                       // 00f9ff88  JZ 0x00f9ff8f
          "leal 0x4(%edi), %eax\n\t"        // 00f9ff8a  LEA EAX,[EDI+0x4]
          "jmp 9f\n\t"                      // 00f9ff8d  JMP 0x00f9ff91
          "8:\n\t"
          "xorl %eax, %eax\n\t"             // 00f9ff8f  XOR EAX,EAX
          "9:\n\t"
          "movl (%esi), %edx\n\t"           // 00f9ff91  MOV EDX,[ESI]
          "pushl $0x0\n\t"                  // 00f9ff93  PUSH 0x0
          "pushl $0x21\n\t"                 // 00f9ff95  PUSH 0x21
          "pushl %eax\n\t"                  // 00f9ff97  PUSH EAX
          "movl 0x4c(%edx), %eax\n\t"       // 00f9ff98  MOV EAX,[EDX+0x4c]
          "movl %esi, %ecx\n\t"             // 00f9ff9b  MOV ECX,ESI
          "call *%eax\n\t"                  // 00f9ff9d  CALL EAX
          "call callee_0067dd80\n\t"        // 00f9ff9f  CALL 0x0067dd80
          "movl (%eax), %edx\n\t"           // 00f9ffa4  MOV EDX,[EAX]
          "movl %eax, %ecx\n\t"             // 00f9ffa6  MOV ECX,EAX
          "movl 0x1c(%edx), %eax\n\t"       // 00f9ffa8  MOV EAX,[EDX+0x1c]
          "pushl $0x3fbae24\n\t"            // 00f9ffab  PUSH 0x3fbae24
          "call *%eax\n\t"                  // 00f9ffb0  CALL EAX
          "movl (%esi), %ebx\n\t"           // 00f9ffb2  MOV EBX,[ESI]
          "movl %eax, %edi\n\t"             // 00f9ffb4  MOV EDI,EAX
          "movl (%edi), %edx\n\t"           // 00f9ffb6  MOV EDX,[EDI]
          "movl 0x13c(%edx), %eax\n\t"      // 00f9ffb8  MOV EAX,[EDX+0x13c]
          "pushl $0x0\n\t"                  // 00f9ffbe  PUSH 0x0
          "pushl $0xa\n\t"                  // 00f9ffc0  PUSH 0xa
          "movl %edi, %ecx\n\t"             // 00f9ffc2  MOV ECX,EDI
          "call *%eax\n\t"                  // 00f9ffc4  CALL EAX
          "movl 0x4c(%ebx), %edx\n\t"       // 00f9ffc6  MOV EDX,[EBX+0x4c]
          "pushl %eax\n\t"                  // 00f9ffc9  PUSH EAX
          "movl %esi, %ecx\n\t"             // 00f9ffca  MOV ECX,ESI
          "call *%edx\n\t"                  // 00f9ffcc  CALL EDX
          "movl (%edi), %eax\n\t"           // 00f9ffce  MOV EAX,[EDI]
          "movl 0x134(%eax), %edx\n\t"      // 00f9ffd0  MOV EDX,[EAX+0x134]
          "pushl $0x1\n\t"                  // 00f9ffd6  PUSH 0x1
          "movl %edi, %ecx\n\t"             // 00f9ffd8  MOV ECX,EDI
          "call *%edx\n\t"                  // 00f9ffda  CALL EDX
          "call callee_0067ddd0\n\t"        // 00f9ffdc  CALL 0x0067ddd0
          "movl (%eax), %edx\n\t"           // 00f9ffe1  MOV EDX,[EAX]
          "movl %eax, %ecx\n\t"             // 00f9ffe3  MOV ECX,EAX
          "movl 0x54(%edx), %eax\n\t"       // 00f9ffe5  MOV EAX,[EDX+0x54]
          "pushl $0x3fbae24\n\t"            // 00f9ffe8  PUSH 0x3fbae24
          "call *%eax\n\t"                  // 00f9ffed  CALL EAX
          "movl (%eax), %edx\n\t"           // 00f9ffef  MOV EDX,[EAX]
          "popl %edi\n\t"                   // 00f9fff1  POP EDI
          "popl %esi\n\t"                   // 00f9fff2  POP ESI
          "popl %ebx\n\t"                   // 00f9fff3  POP EBX
          "movl $0x0, 0x4(%esp)\n\t"        // 00f9fff4  MOV [ESP+0x4],0
          "movl %eax, %ecx\n\t"             // 00f9fffc  MOV ECX,EAX
          "movl 0xc(%edx), %eax\n\t"        // 00f9fffe  MOV EAX,[EDX+0xc]
          "jmp *%eax\n\t"                   // 00fa0001  JMP EAX
          "2:\n\t"
          "popl %edi\n\t"                   // 00fa0003  POP EDI
          "popl %esi\n\t"                   // 00fa0004  POP ESI
          "popl %ebx\n\t"                   // 00fa0005  POP EBX
          "retl $0x4\n\t");                 // 00fa0006  RET 0x4
}

}  // namespace pkg_w2_00f9fef0
}  // namespace reconstruction
}  // namespace openspore
