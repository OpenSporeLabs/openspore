PUSH EBP
MOV EBP,ESP
MOV EAX,dword ptr [ECX + 0x4]
MOV EDX,dword ptr [EDX + 0x8]
ADD EAX,EDX
MOV dword ptr [ECX + 0x8],EAX
MOV EAX,dword ptr [ECX + 0xc]
ADD EAX,dword ptr [EDX + 0x10]
MOV ESP,EBP
POP EBP
RET
