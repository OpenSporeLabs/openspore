PUSH EBP
MOV EBP,ESP
SUB ESP,0x24
MOV dword ptr [EBP + -0x18],ECX
MOV EAX,dword ptr [EDX + 0x4]
MOV dword ptr [ECX],EAX
MOV EAX,dword ptr [EBP + 0x8]
MOV dword ptr [ECX + 0x4],EAX
MOV EAX,dword ptr [ECX + 0x8]
MOV ESP,EBP
POP EBP
RET 0x4
