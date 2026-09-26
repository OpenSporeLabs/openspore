PUSH EBP
MOV EBP,ESP
SUB ESP,0x20
MOV dword ptr [EBP + -0x4],0x0
MOV EAX,dword ptr [EBP + 0x8]
TEST EAX,EAX
JNE 0x00400070
MOV dword ptr [EBP + -0x8],0x0
PUSH dword ptr [EBP + -0x8]
PUSH EAX
MOV ECX,dword ptr [ECX + 0x4]
CALL 0x00903400
ADD ESP,0x8
MOV dword ptr [EBP + -0x4],0x1
MOV EAX,dword ptr [EBP + 0xc]
RET
