PUSH EBP
MOV EBP,ESP
SUB ESP,0x8
MOV dword ptr [EBP + -0x8],ECX
MOV EAX,dword ptr [0x016f2618]
MOV ECX,dword ptr FS:[0x2c]
MOV EDX,dword ptr [ECX + EAX*0x4]
MOV EAX,dword ptr [EBP + -0x8]
MOV dword ptr [EDX + 0x4],EAX
MOV ECX,dword ptr [EBP + 0x8]
PUSH ECX
MOV EDX,dword ptr [EBP + -0x8]
MOV EAX,dword ptr [EDX + 0x3a9c]
PUSH EAX
CALL 0x00903400
ADD ESP,0x8
MOV dword ptr [EBP + -0x4],EAX
MOV ESP,EBP
POP EBP
RET 0x4
