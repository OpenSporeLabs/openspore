.text
.globl ArchetypeRelationshipsID_00c30e20
.type ArchetypeRelationshipsID_00c30e20, @function
ArchetypeRelationshipsID_00c30e20:
    movl 8(%esp), %ecx
    subl $0, %ecx
    je .Lrelationship_zero
    subl $1, %ecx
    je .Lrelationship_one
    subl $1, %ecx
    jne .Lrelationship_passthrough
    movl $0x87d7829a, %eax
    ret
.Lrelationship_one:
    movl $0x7e56d6cc, %eax
    ret
.Lrelationship_zero:
    movl $0x25885eaf, %eax
    ret
.Lrelationship_passthrough:
    ret
.size ArchetypeRelationshipsID_00c30e20, .-ArchetypeRelationshipsID_00c30e20

.globl ArchetypeRelationshipsIDIncoming_00c30e20
.type ArchetypeRelationshipsIDIncoming_00c30e20, @function
ArchetypeRelationshipsIDIncoming_00c30e20:
    movl 4(%esp), %ecx
    movl 8(%esp), %edx
    movl 12(%esp), %eax
    pushl %edx
    pushl %ecx
    call ArchetypeRelationshipsID_00c30e20
    addl $8, %esp
    ret
.size ArchetypeRelationshipsIDIncoming_00c30e20, .-ArchetypeRelationshipsIDIncoming_00c30e20
