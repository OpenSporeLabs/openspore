PUSH EBP
MOV EBP,ESP
SUB ESP,0x20
MOV EAX,dword ptr [EBP + 0x8]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [ECX + 0x1c]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [ECX + 0x20]
MOV dword ptr [EBP + -0x1c],EAX
MOV EAX,dword ptr [EBP + 0xc]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [ECX + 0x24]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [EBP + 0x10]
MOV dword ptr [EBP + -0x1c],EAX
MOV EAX,dword ptr [ECX + 0x28]
MOV dword ptr [EBP + -0x1c],EAX
MOV ESP,EBP
POP EBP
RET 0xc
