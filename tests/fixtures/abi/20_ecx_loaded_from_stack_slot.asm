MOV EAX,dword ptr [ESP + 0x8]
MOV ECX,dword ptr [ESP + 0xc]
MOV EDX,dword ptr [ESP + 0x10]
MOV dword ptr [ECX],EAX
MOV EAX,dword ptr [ESP + 0x4]
MOV dword ptr [EDX],EAX
RET
