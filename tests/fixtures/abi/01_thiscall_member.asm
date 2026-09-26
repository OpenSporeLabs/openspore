PUSH EBP
MOV EBP,ESP
SUB ESP,0x10
MOV EAX,dword ptr [ECX + 0x8]
MOV dword ptr [ECX + 0xc],EAX
MOV EAX,dword ptr [ECX + 0x10]
ADD EAX,0x4
MOV dword ptr [ECX + 0x14],EAX
MOV EAX,dword ptr [EBP + 0x8]
TEST EAX,EAX
JZ 0x00100050
MOV EAX,dword ptr [ECX + 0x8]
MOV dword ptr [EBP + 0xc],EAX
MOV ESP,EBP
POP EBP
RET
