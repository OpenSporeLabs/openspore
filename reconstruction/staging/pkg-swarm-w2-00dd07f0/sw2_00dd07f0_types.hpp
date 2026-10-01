// PKG-SWARM-W2-00DD07F0 -- VA 0x00dd07f0 (FUN_00dd07f0)
//
// SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e.
//
// WHAT THE BODY IS: a writer. Every one of its seven exits communicates through
// ONE dword of the receiver, at receiver+0x8c, and five of the seven write
// nothing at all. It reads a two-level pointer chain hanging off receiver+0x98,
// and depending on two discriminant words it either stores a small code or asks
// three direct callees a question whose answer is turned into a code.
//
// THE LISTING THIS WAS WRITTEN AGAINST, RE-DERIVED FROM THE IMAGE
//
// objdump -D -b binary -m i386 -M intel --adjust-vma=0x00dd07f0 over the 0x14c
// bytes of SPORE/SporeBin/SporeApp.exe at file offset 0x9d07f0 - 0x400000 +
// 0xfcb000 = 0x9c07f0 (RVA 0x9d07f0) reproduces the 68 committed instructions at
// the same addresses, with the same lengths, the same branch targets and the same
// operand displacements. Nothing in this model depends on a difference from the
// committed listing, because there is none:
//
//   00dd07f0  PUSH ESI
//   00dd07f1  MOV ESI,ECX
//   00dd07f3  MOV EAX,DWORD PTR [ESI + 0x98]
//   00dd07f9  TEST EAX,EAX
//   00dd07fb  JZ 0x00dd08f0
//   00dd0801  MOV ECX,DWORD PTR [EAX + 0xc]
//   00dd0804  CMP DWORD PTR [ECX + 0x10],0x6
//   00dd0808  JNZ 0x00dd0816
//   00dd080a  MOV DWORD PTR [ESI + 0x8c],0xfffffffe
//   00dd0814  POP ESI
//   00dd0815  RET
//   00dd0816  MOV DWORD PTR [ESI + 0x8c],0x3
//   00dd0820  MOV EDX,DWORD PTR [EAX + 0xc]
//   00dd0823  MOV EAX,DWORD PTR [EDX + 0x20]
//   00dd0826  CMP EAX,-0x1
//   00dd0829  JNZ 0x00dd0837
//   00dd082b  MOV DWORD PTR [ESI + 0x8c],0xfffffffd
//   00dd0835  POP ESI
//   00dd0836  RET
//   00dd0837  MOV ECX,DWORD PTR [ESI + 0x84]
//   00dd083d  DEC ECX
//   00dd083e  MOV EDX,0x4
//   00dd0843  CMP ECX,EDX
//   00dd0845  JA 0x00dd08f0
//   00dd084b  JMP DWORD PTR [ECX*0x4 + 0xdd08f4]
//   00dd0852  CMP EAX,0x7
//   00dd0855  JA 0x00dd08f0
//   00dd085b  JMP DWORD PTR [EAX*0x4 + 0xdd0908]
//   00dd0862  MOV DWORD PTR [ESI + 0x8c],0x2
//   00dd086c  POP ESI
//   00dd086d  RET
//   00dd086e  LEA EAX,[ESI + 0x4]
//   00dd0871  PUSH EAX
//   00dd0872  CALL 0x00401090
//   00dd0877  MOV ECX,EAX
//   00dd0879  CALL 0x004df400
//   00dd087e  PUSH EAX
//   00dd087f  CALL 0x004eb930
//   00dd0884  MOVZX ECX,AL
//   00dd0887  ADD ESP,0x8
//   00dd088a  NEG ECX
//   00dd088c  SBB ECX,ECX
//   00dd088e  AND ECX,0x7ffffffa
//   00dd0894  ADD ECX,0x5
//   00dd0897  MOV DWORD PTR [ESI + 0x8c],ECX
//   00dd089d  POP ESI
//   00dd089e  RET
//   00dd089f  CMP EAX,EDX
//   00dd08a1  JA 0x00dd08f0
//   00dd08a3  JMP DWORD PTR [EAX*0x4 + 0xdd0928]
//   00dd08aa  MOV DWORD PTR [ESI + 0x8c],0x0
//   00dd08b4  POP ESI
//   00dd08b5  RET
//   00dd08b6  MOV DWORD PTR [ESI + 0x8c],0x1
//   00dd08c0  POP ESI
//   00dd08c1  RET
//   00dd08c2  MOV DWORD PTR [ESI + 0x8c],0x3
//   00dd08cc  POP ESI
//   00dd08cd  RET
//   00dd08ce  MOV EDX,DWORD PTR [ESI + 0x88]
//   00dd08d4  SUB EDX,0x53dbcf1
//   00dd08da  NEG EDX
//   00dd08dc  SBB EDX,EDX
//   00dd08de  AND EDX,0x80000006
//   00dd08e4  ADD EDX,0x7fffffff
//   00dd08ea  MOV DWORD PTR [ESI + 0x8c],EDX
//   00dd08f0  POP ESI
//   00dd08f1  RET
//
// 68 instructions, 258 bytes, 0x00dd07f0..0x00dd08f1 inclusive. That agrees with
// ghidra_function.size_bytes 258, body_start 0x00dd07f0 and body_end 0x00dd08f1.
// The two bytes at 0x00dd08f2 are 8b ff (the standard hot-patch `MOV EDI,EDI`),
// and the three jump tables follow the body at 0x00dd08f4, so the body ends
// exactly where the data begins and nothing falls through into the tables.
//
// THE THREE JUMP TABLES, READ OUT OF THE IMAGE
//
// The body's three indirect transfers are switch dispatches, not virtual calls,
// and every one of them is transcribed here from the bytes at its own base so a
// reviewer can check the mapping without re-reading the image. Each base address
// is itself an operand of the JMP that uses it, so the bases are machine facts
// and the words they hold are machine facts too.
//
//   00dd084b  JMP [ECX*0x4 + 0xdd08f4]   index = *(receiver+0x84) - 1, 0..4
//             (guarded by 00dd0843's CMP ECX,EDX with EDX=4 and 00dd0845's JA)
//     [0] = 0x00dd0852   the kind word was 1: guard 00dd0852 CMP EAX,0x7, then
//                         00dd085b JMP [EAX*0x4 + 0xdd0908]
//     [1] = 0x00dd089f   the kind word was 2: guard 00dd089f CMP EAX,EDX with
//                         EDX=4, then 00dd08a3 JMP [EAX*0x4 + 0xdd0928]
//     [2] = 0x00dd08f0   the kind word was 3: the shared bare epilogue, which
//                         writes NOTHING
//     [3] = 0x00dd089f   the kind word was 4: the same arm as [1]
//     [4] = 0x00dd089f   the kind word was 5: the same arm as [1]
//
//   00dd085b  JMP [EAX*0x4 + 0xdd0908]   index = *(record+0x20), 0..7
//             (guarded by 00dd0852's CMP EAX,0x7 and 00dd0855's JA), reached
//             only when the kind word was 1
//     [0] = 0x00dd08c2   store 3
//     [1] = 0x00dd0862   store 2
//     [2] = 0x00dd08b6   store 1
//     [3] = 0x00dd08c2   store 3
//     [4] = 0x00dd08ea   store EDX  -- the bare store, skipping 00dd08ce..0x00dd08e4,
//                         so the value is whatever EDX already holds, and EDX is 4
//     [5] = 0x00dd08aa   store 0
//     [6] = 0x00dd086e   the three-callee block
//     [7] = 0x00dd086e   the three-callee block
//
//   00dd08a3  JMP [EAX*0x4 + 0xdd0928]   index = *(record+0x20), 0..4
//             (guarded by 00dd089f's CMP EAX,EDX with EDX=4 and 00dd08a1's JA),
//             reached when the kind word was 2, 4 or 5
//     [0] = 0x00dd08aa   store 0
//     [1] = 0x00dd08b6   store 1
//     [2] = 0x00dd08c2   store 3
//     [3] = 0x00dd08ea   store EDX -- again the bare store, and again EDX is 4
//     [4] = 0x00dd08ce   the six-instruction block that recomputes from
//                         *(receiver+0x88) and falls into 00dd08ea
//
// TWO THINGS IN THOSE TABLES THAT ARE EASY TO GET WRONG, AND THAT THE MODEL
// GETS RIGHT ONLY BECAUSE THE BYTES WERE READ
//
// 1. ENTRY 3 AND ENTRY 4 OF BOTH INNER TABLES POINT AT DIFFERENT INSTRUCTIONS OF
//    THE SAME BLOCK.  0x00dd08ea is the STORE at the tail of the 00dd08ce block;
//    0x00dd08ce is the TOP of that block. So an index of 3 stores the leftover
//    EDX -- which the guard at 00dd083e/00dd0843/00dd089f fixed at 4 -- and an
//    index of 4 stores the value recomputed from receiver+0x88. The two entries
//    are NOT the same outcome, and a reconstruction that maps both to 0x00dd08ce
//    is wrong on every sub-state of 3. (Ghidra's own decompilation gets this
//    right for the same reason: its `iVar3 = 4` initial value is the leftover
//    EDX of the 0x00dd08ea entry, not a store the listing contains.)
//
// 2. THE GUARD CONSTANT 4 IS ALSO A STORED RESULT.  0x00dd083e puts 4 in EDX for
//    the outer guard and 0x00dd089f reuses EDX for the inner guard, and on the
//    0x00dd08ea entries that same EDX is what lands in receiver+0x8c. So "4" is
//    simultaneously the largest legal index and one of this function's answers.
//    Nothing in the listing separates those two roles, and the model keeps them
//    as they are: the guard compares against the header's kIndexLimit, and the
//    store uses the header's kLeftoverGuardWord.
//
// THE POINTER CHAIN, AND WHY THE POINTER LEVELS ARE WHAT THEY ARE
//
//   00dd07f3  MOV EAX,[ESI+0x98]     level 0 -> level 1: link
//   00dd0801  MOV ECX,[EAX+0xc]      level 1 -> level 2: record
//   00dd0804  CMP [ECX+0x10],0x6    the discriminator, one dereference deeper
//   00dd0820  MOV EDX,[EAX+0xc]     the SAME word re-read, not a new link
//   00dd0823  MOV EAX,[EDX+0x20]    the sub-state, one dereference deeper
//
// `link` is dereferenced twice, and 0x00dd0801 and 0x00dd0820 read the SAME
// displacement of the SAME level-1 object, so the model reads it once and
// reuses it. That reuse is not an optimisation the source performed: the listing
// performs the load twice and this package models it as two named reads of the
// same value because nothing can run between them -- there is no call, no store
// and no branch between 0x00dd0801 and 0x00dd0820 on any path. See
// unresolved_questions item 4 for the one input that would distinguish them and
// why this body cannot produce it.
//
// `record` is a level-2 pointer: the machine reads [link+0xc] and then
// dereferences THAT. A reconstruction that treats [link+0xc] as the record's
// first member, or that reads [link+0x10] instead of [[link+0xc]+0x10], is wrong
// on every input. The model test plants a decoy at the wrong depth for exactly
// this reason.
//
// EVERY OFFSET AND CONSTANT IN THIS HEADER, WITH THE INSTRUCTION THAT FIXES IT
//
//   receiver+0x98 (word, READ)  <- 0x00dd07f3 `MOV EAX,[ESI+0x98]`, once
//   receiver+0x84 (word, READ)  <- 0x00dd0837 `MOV ECX,[ESI+0x84]`, once
//   receiver+0x88 (word, READ)  <- 0x00dd08ce `MOV EDX,[ESI+0x88]`, once
//   receiver+0x8c (word, WRITE) <- 0x00dd080a, 0x00dd0816, 0x00dd082b, 0x00dd0862,
//                                 0x00dd0897, 0x00dd08aa, 0x00dd08b6, 0x00dd08c2
//                                 and 0x00dd08ea. NINE store sites, one dword
//   receiver+0x04 (address TAKEN, not read by this body) <- 0x00dd086e
//                                 `LEA EAX,[ESI+0x4]`, the address handed to the
//                                 0x00401090 call and, as it turns out, still on
//                                 the stack for the 0x004eb930 call
//   link+0x0c     (word, READ)  <- 0x00dd0801 and again 0x00dd0820
//   record+0x10   (word, READ)  <- 0x00dd0804 `CMP [ECX+0x10],0x6`
//   record+0x20   (word, READ)  <- 0x00dd0823 `MOV EAX,[EDX+0x20]`
//
// The four receiver displacements -- 0x84, 0x88, 0x8c, 0x98 -- are exactly the
// set the machine-derived receiver record enumerates: abi_derived.receiver is
// {register ECX, offsets [132, 136, 140, 152], max_offset 152, written_through
// 9, shape R-ALIAS, bounds_only true}. Four displacements, nine writes through a
// pointer, and the shape is R-ALIAS because 0x00dd07f1 copies ECX into ESI and
// every receiver operand after that names ESI, so a naive ECX-only scan of the
// listing finds nothing in bounds.
//
// WHY NO MEMBER IS NAMED FOR ANY OF THOSE DISPLACEMENTS
//
// The receiver record is bounds_only: it states where the body was seen reaching
// and not which member is which, and it says so at SUPPORTED confidence. So this
// header declares NO member for receiver+0x84, +0x88, +0x8c or +0x98, and none
// for the level-1 and level-2 displacements either. Every access in the model
// goes through a displacement-named accessor with the displacement as a named
// constexpr, which asserts the ADDRESS and nothing about what lives there. The
// three values written are codes and the two values read are discriminants, but
// the listing does not say what any of them is called, so nothing is named.
// What IS named is every constant, because a constant is a value and a value is
// what the instruction fixes.
//
// THE THREE DIRECT CALLEES, ESTABLISHED FROM THEIR OWN BYTES
//
// 0x00401090, 10 bytes, 0x00401090..0x00401099, Ghidra name
// `Editors::cSpeciesManager::Get`:
//   401090: 55                 push ebp
//   401091: 8b ec              mov  ebp,esp
//   401093: a1 24 0c 5d 01     mov  eax,DWORD PTR ds:0x15d0c24
//   401098: 5d                 pop  ebp
//   401099: c3                 ret
// It reads NO stack slot and NO argument register, so it takes ZERO arguments
// and ignores the word 0x00dd0871 pushed for it. Its terminator is a bare C3,
// so it owns no cleanup and the pushed word is still on the stack when the next
// call is made -- which is why 0x00dd0887's ADD ESP,0x8 drops TWO words for the
// TWO calls. Its return is the data word at 0x015d0c24, which is the body of
// this callee and is recorded here as context; nothing in this model reads it.
//
// 0x004df400, 19 bytes, 0x004df400..0x004df412, Ghidra name `FUN_004df400`:
//   4df400: 55                 push ebp
//   4df401: 8b ec              mov  ebp,esp
//   4df403: 51                 push ecx
//   4df404: 89 4d fc           mov  DWORD PTR [ebp-0x4],ecx
//   4df407: 8b 45 fc           mov  eax,DWORD PTR [ebp-0x4]
//   4df40a: 05 a4 00 00 00     add  eax,0xa4
//   4df40f: 8b e5              mov  esp,ebp
//   4df411: 5d                 pop  ebp
//   4df412: c3                 ret
// __thiscall with the receiver in ECX -- 0x00dd0877's `MOV ECX,EAX` is the only
// thing that sets it up -- and no stack argument. Its whole body is `return
// this + 0xa4`. Its terminator is a bare C3.
//
// 0x004eb930, 0x43 bytes, 0x004eb930..0x004eb972, Ghidra name `FUN_004eb930`:
//   4eb930: 55                 push ebp
//   4eb931: 8b ec              mov  ebp,esp
//   4eb933: 51                 push ecx
//   4eb934: 8b 45 08           mov  eax,DWORD PTR [ebp+0x8]    <- argument 1
//   4eb937: 8b 4d 0c           mov  ecx,DWORD PTR [ebp+0xc]    <- argument 2
//   4eb93a: 8b 10              mov  edx,[eax]                   <- [arg1+0]
//   4eb93c: 3b 11              cmp  edx,[ecx]                   <- vs [arg2+0]
//   4eb93e: 75 25              jne  0x4eb965                    -> 0
//   4eb940: ... 8b 50 04 / 3b 51 04 / jne -> 0                <- [arg1+4] vs [arg2+4]
//   4eb94e: ... 8b 50 08 / 3b 51 08 / jne -> 0                <- [arg1+8] vs [arg2+8]
//   4eb95c: c7 45 fc 01 00 00 00   mov [ebp-0x4],0x1
//   4eb965: c7 45 fc 00 00 00 00   mov [ebp-0x4],0x0
//   4eb96c: 8a 45 fc           mov  al,BYTE PTR [ebp-0x4]
//   4eb96f: 8b e5              mov  esp,ebp
//   4eb971: 5d                 pop  ebp
//   4eb972: c3                 ret
// cdecl with TWO four-byte stack arguments, and it returns 1 in AL only if all
// three of the dwords at [arg1+0], [arg1+4] and [arg1+8] equal the dwords at the
// same three offsets of arg2. 0x00dd0884's MOVZX ECX,AL consumes exactly that
// one byte, which is why the model's declared return is bool rather than a word.
//
// ITS SECOND ARGUMENT IS THE WORD PUSHED FOR THE PREVIOUS CALL. Only one word
// is pushed between 0x00dd0872 and 0x00dd087f -- 0x00dd087e's PUSH EAX -- and
// 0x00401090's bare C3 removed only the return address, so at 0x00dd087f the
// stack holds:
//
//   [esp+0]  the return address
//   [esp+4]  0x00dd087e's PUSH EAX, i.e. 0x004df400's return  -> [ebp+0x8]
//   [esp+8]  0x00dd0871's PUSH EAX, i.e. LEA EAX,[ESI+0x4]     -> [ebp+0xc]
//
// So the comparison 0x004eb930 performs is between the twelve bytes at
// (0x004df400's return) and the twelve bytes at receiver+0x04, and 0x00dd0887's
// ADD ESP,0x8 drops both words afterwards. That the second word is the same
// address 0x00dd0871 pushed is a fact about the three instructions, not an
// inference; what the address MEANS is not fixed by them.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00dd07f0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare
// MSVC keywords, so the x86-32 attribute form is the portable spelling and the
// keyword form is kept for MSVC. Each is fixed by machine facts:
//
//   PKG_SWARM_W2_00DD07F0_THISCALL  this body. The receiver arrives in ECX:
//     0x00dd07f1 copies it into ESI, 0x00dd07f3 dereferences it through ESI
//     before any definite write to ECX, and all seven return sites are a bare
//     C3 (0x00dd0815, 0x00dd0836, 0x00dd086d, 0x00dd089e, 0x00dd08b5,
//     0x00dd08c1, 0x00dd08cd) or a bare C3 preceded by POP ESI (0x00dd08f1) --
//     never a `C2 imm16` -- so the function consumes no stack argument word and
//     the caller owns all cleanup. That matches abi_derived.cleanup
//     {bytes 0, side caller, evidence "ret with no immediate, no stack reads"}
//     and abi_derived.conventions.calling_convention "__thiscall".
//   PKG_SWARM_W2_00DD07F0_CDECL     0x00401090 and 0x004eb930. Both terminate in
//     a bare C3 (0x00401099 and 0x004eb972) with no immediate, so neither
//     touches ESP, and 0x00dd0887's ADD ESP,0x8 drops the two words.
//   PKG_SWARM_W2_00DD07F0_CALLEE_THISCALL  0x004df400, whose own body reads ECX
//     (0x004df404 stores it and 0x004df407 reloads it) and reads no stack slot,
//     and which also ends in a bare C3 at 0x004df412.
#if defined(_MSC_VER)
#define PKG_SWARM_W2_00DD07F0_THISCALL __thiscall
#define PKG_SWARM_W2_00DD07F0_CDECL __cdecl
#define PKG_SWARM_W2_00DD07F0_CALLEE_THISCALL __thiscall
#else
#define PKG_SWARM_W2_00DD07F0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W2_00DD07F0_CDECL __attribute__((cdecl))
#define PKG_SWARM_W2_00DD07F0_CALLEE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0 {

using Word = std::uint32_t;
using Byte = std::uint8_t;

// The receiver, as an opaque byte run with NO named member.
//
// The last byte this body touches is the fourth byte of the dword it loads at
// receiver+0x98, i.e. receiver+0x9b, so 0x9c bytes is exactly the reach. That is
// a statement about THIS body's reach and not a claim about the object's size:
// the record's max_offset is 152 = 0x98, which is the largest DISPLACEMENT, and
// a displacement is not a length. The class's own size is not in this listing.
struct alignas(4) OpaqueSporepediaAsset {
  std::array<Byte, 0x9c> opaque_00;  // 0x00..0x9b
};

// The four receiver displacements. Each is one instruction and no more, and the
// record's bounds_only flag is why none of them becomes a member name.
constexpr std::size_t kLinkDisplacement = 0x98;   // 0x00dd07f3, read once
constexpr std::size_t kKindDisplacement = 0x84;   // 0x00dd0837, read once
constexpr std::size_t kTagDisplacement = 0x88;    // 0x00dd08ce, read once
constexpr std::size_t kResultDisplacement = 0x8c;  // nine store sites

// 0x00dd086e's LEA displacement. This is an ADDRESS the body forms and hands on;
// it is not a dword this body reads, and the value it points at is read by
// 0x004eb930 rather than by this body. It is a named constant and not a literal
// in the model's text, for the same reason 0x00dd0887's ADD ESP,0x8 is: the model
// has no statement of its own for the formation, it only has the call.
constexpr std::size_t kCompareArgumentDisplacement = 0x04;

// The level-1 and level-2 displacements, read out of a chain that starts at
// receiver+0x98. They belong to OTHER objects, not to the receiver, which is
// exactly why they are not receiver fields and why the receiver record does not
// enumerate them.
constexpr std::size_t kRecordLinkDisplacement = 0x0c;  // 0x00dd0801, 0x00dd0820
constexpr std::size_t kRecordKindDisplacement = 0x10;  // 0x00dd0804
constexpr std::size_t kRecordSubDisplacement = 0x20;   // 0x00dd0823

// 0x00dd0804's immediate, the value *(record+0x10) is compared AGAINST for
// equality. It is not a range bound and not a "kind <= 6" test: 0x00dd0808 is
// JNZ, so exactly the word 6 takes the -2 exit and 5 and 7 do not.
constexpr Word kRecordKindSentinel = 0x06u;

// 0x00dd0826's `CMP EAX,-0x1`. It is a full-word equality test against all ones,
// not a sign test and not a zero test, so 0x7fffffff and 0xfffffffe both miss it.
constexpr Word kSubStateSentinel = 0xffffffffu;

// 0x00dd083d's DEC and 0x00dd083e's MOV EDX,0x4 and 0x00dd0843's CMP ECX,EDX and
// 0x00dd0845's JA. The outer index is (kind - 1) and the guard is UNSIGNED
// above-or-equal-5, so kind 0 and kind 0x80000000 leave the function without a
// write rather than wrapping into the table.
constexpr Word kOuterIndexBias = 0x01u;
constexpr Word kIndexLimit = 0x04u;
constexpr Word kLeftoverGuardWord = 0x04u;  // EDX, at 0x00dd083e

// 0x00dd0852's CMP EAX,0x7 and 0x00dd0855's JA: the guard on the kind-1 table.
constexpr Word kKindOneSubLimit = 0x07u;

// 0x00dd089f's CMP EAX,EDX and 0x00dd08a1's JA: the guard on the other two
// table arms. EDX is still the 0x00dd083e value, so the limit is 4 again.
constexpr Word kOtherArmSubLimit = 0x04u;

// The three jump-table bases. Each is the memory operand of the JMP that reads
// it, so the base is as much a machine fact as the words at it.
constexpr Word kOuterTableBase = 0x00dd08f4u;
constexpr Word kKindOneSubTableBase = 0x00dd0908u;
constexpr Word kOtherArmSubTableBase = 0x00dd0928u;

// The instruction addresses the three tables point at, as named values. These
// are the DECODED targets: they are words inside the tables, not operands of any
// committed listing instruction, so they are named here and used in the model by
// name rather than written as literals in its text.
constexpr Word kTargetKindOneArm = 0x00dd0852u;   // outer table entry [0]
constexpr Word kTargetOtherArm = 0x00dd089fu;     // outer table entries [1][3][4]
constexpr Word kTargetBareEpilogue = 0x00dd08f0u;  // outer table entry [2]
constexpr Word kTargetStore2 = 0x00dd0862u;
constexpr Word kTargetThreeCalleeBlock = 0x00dd086eu;
constexpr Word kTargetStore0 = 0x00dd08aau;
constexpr Word kTargetStore1 = 0x00dd08b6u;
constexpr Word kTargetStore3 = 0x00dd08c2u;
constexpr Word kTargetTagArm = 0x00dd08ceu;    // the recomputing block's top
constexpr Word kTargetBareStore = 0x00dd08eau;  // its store, reached directly

// The three tables, transcribed word for word from the bytes at their bases.
inline constexpr std::array<Word, 5> kOuterTable = {
    kTargetKindOneArm, kTargetOtherArm, kTargetBareEpilogue, kTargetOtherArm,
    kTargetOtherArm};

inline constexpr std::array<Word, 8> kKindOneSubTable = {
    kTargetStore3,     kTargetStore2,         kTargetStore1,
    kTargetStore3,     kTargetBareStore,      kTargetStore0,
    kTargetThreeCalleeBlock, kTargetThreeCalleeBlock};

inline constexpr std::array<Word, 5> kOtherArmSubTable = {
    kTargetStore0, kTargetStore1, kTargetStore3, kTargetBareStore,
    kTargetTagArm};

// The words the body stores, named. Each is one instruction's immediate.
constexpr Word kStoreKindSentinel = 0xfffffffeu;  // 0x00dd080a, as -2
constexpr Word kStoreProgress = 0x03u;           // 0x00dd0816, and 0x00dd08c2
constexpr Word kStoreSubSentinel = 0xfffffffdu;  // 0x00dd082b, as -3
constexpr Word kStore2 = 0x02u;                  // 0x00dd0862
constexpr Word kStore0 = 0x00u;                  // 0x00dd08aa
constexpr Word kStore1 = 0x01u;                  // 0x00dd08b6

// The tag arm at 0x00dd08ce..0x00dd08e4, instruction by instruction, with f = the
// dword at receiver+0x88:
//
//   00dd08ce  MOV  EDX,f
//   00dd08d4  SUB  EDX,0x53dbcf1      EDX = f - 0x53dbcf1   (wrapping)
//   00dd08da  NEG  EDX                EDX = 0x53dbcf1 - f ; CF = (f != 0x53dbcf1)
//   00dd08dc  SBB  EDX,EDX            EDX = -CF, i.e. 0 or ~0
//   00dd08de  AND  EDX,0x80000006     0 or 0x80000006
//   00dd08e4  ADD  EDX,0x7fffffff     0x7fffffff or 0x80000006+0x7fffffff
//
// The last row is the one that is easy to get wrong by eye. 0x80000006 +
// 0x7fffffff is 0x100000005, which wraps to 5 -- NOT to 0x80000005. The arm
// therefore stores 0x7fffffff or 0x00000005, and 5 is the same "no" answer the
// three-callee block produces on its false arm, reached from a different
// instruction and by a different route.
constexpr Word kTagArmSubtractand = 0x53dbcf1u;

// What 0x00dd08dc's SBB and 0x00dd088c's SBB produce as the "not selected"
// operand: all ones. It is named rather than written as a literal in the model's
// text because it is NOT one of this body's immediates -- it is what NEG's carry
// turns into -- and because a literal of that shape in the model's arithmetic
// would read as a displacement to any tool that cannot tell an addend from an
// offset. 0x00dd0826's own all-ones immediate is the separate
// kSubStateSentinel above.
constexpr Word kNegSelectFill = 0xffffffffu;
constexpr Word kTagArmSelectMask = 0x80000006u;
constexpr Word kTagArmSelectAddend = 0x7fffffffu;
constexpr Word kTagArmSelectedValue = 0x7fffffffu;  // f == the subtractand
constexpr Word kTagArmOtherValue = 0x05u;            // f != the subtractand

// The three-callee block at 0x00dd086e..0x00dd0894, instruction by instruction,
// with b = AL as 0x004eb930 left it:
//
//   00dd0884  MOVZX ECX,AL            ECX = b, zero-extended
//   00dd088a  NEG  ECX                ECX = -b ; CF = (b != 0)
//   00dd088c  SBB  ECX,ECX            ECX = -CF, i.e. ~0 for b != 0 else 0
//   00dd088e  AND  ECX,0x7ffffffa     0x7ffffffa or 0
//   00dd0894  ADD  ECX,0x5            0x7fffffff or 0x5
//
// Same two answers as the tag arm and from the opposite operand: here the mask
// plus the addend produces the LARGE one, where the tag arm's mask plus its
// addend produced the small one. The selection is on the ONE BYTE 0x00dd0884
// zero-extends, so a callee that returned 0x00000100 would read as false.
constexpr Word kCalleeArmSelectMask = 0x7ffffffau;
constexpr Word kCalleeArmSelectAddend = 0x05u;
constexpr Word kCalleeArmTrueValue = 0x7fffffffu;
constexpr Word kCalleeArmFalseValue = 0x05u;

// 0x00dd0887 `ADD ESP,0x8`: the caller-side drop of the two words pushed at
// 0x00dd0871 and 0x00dd087e. It is recorded because it is instruction 36 of 68
// and because both callees' bare C3s are what require it. It is NOT observable
// through the model test, and the test says so instead of pretending otherwise:
// for a cdecl leaf callee, a callee-pops and a caller-pops return are the same
// machine behaviour. What the model test DOES measure is the mirror-image claim
// about this body -- that it consumes no stack word of its own -- by sampling
// ESP around a raw call.
constexpr std::size_t kCallArgumentCleanupBytes = 0x08;

// -- context constants, read out of the image, referenced by no code ---------
// These are recorded so a reviewer can check the claims in the file header
// against the bytes rather than taking them on trust. The model does not read
// them and the model test does not assert them.

// 0x00401090's own body, in full: `MOV EAX,DWORD PTR ds:0x15d0c24`. So the
// 0x00401090 call's return is that data word, whatever LEA EAX,[ESI+0x4] pushed.
constexpr Word kSpeciesManagerGlobal = 0x015d0c24u;

// 0x004df400's own body, in full: `ADD EAX,0xa4` on its ECX receiver. So that
// call's return is its argument plus this displacement.
constexpr std::size_t kCalleeShiftDisplacement = 0xa4u;

// The three dword offsets 0x004eb930 compares on each of its two arguments.
constexpr std::size_t kCompareWidthBytes = 0x0cu;

// The two bytes at 0x00dd08f2 are 8b ff, the standard hot-patch MOV EDI,EDI, and
// the tables start at 0x00dd08f4. No slot boundary and no slot index is declared
// anywhere in this package. That is a measured decision and not a missing one, so
// the measurement is recorded here in full.
//
// (1) Nothing in the BODY fixes a slot. The three indirect transfers are
//     0x00dd084b JMP [ECX*0x4 + 0xdd08f4], 0x00dd085b JMP [EAX*0x4 + 0xdd0908]
//     and 0x00dd08a3 JMP [EAX*0x4 + 0xdd0928]: each transfers through a memory
//     operand with a scale factor, so each is a switch jump table and the
//     displacement in it is a TABLE BASE ADDRESS, not a slot index. The body
//     never loads a function pointer out of an object at all -- there is no
//     MOV r,[base+d] / MOV r,[r+d] / CALL r anywhere in the 68 instructions --
//     and the derived dispatch record says so independently, counting
//     vtable_shaped_loads: 0 beside its 3 indirect calls. There is therefore no
//     displacement in this body that a slot claim could name.
//
// (2) The record's four table addresses fix no slot either. The dword 0x00dd07f0
//     occurs exactly three times in the whole image, all in .rdata, at
//     0x0147cabc, 0x0147cb84 and 0x0147cc74 -- the record's three inbound
//     references. Relative to the four addresses the classifier names
//     (0x0147ca30, 0x0147ca70, 0x0147caf8, 0x0147cc14) those three land at
//     +140/+340/+580, +76/+276/+516, -60/+140/+380 and -344/-144/+96
//     respectively: mutually inconsistent, and two of the four even place a
//     reference BEFORE the base. No slot index follows from any of them.
//
// (3) What the image does show is why they are not slots. Each of the three is
//     the tenth dword (+0x24) of an .rdata record whose first TEN dwords are
//     byte-identical across all three copies -- 0x00dd0710, 0x00641cd0,
//     0x00641e10, 0x00641e40, 0x00642230, 0x00642530, 0x00dd0550, 0x00dd0580,
//     0x00a6fed0, 0x00dd07f0 -- with the eleventh differing (0x00dd0bc0,
//     0x00b1e4d0, 0x00dd0b40). Those records begin at 0x0147ca98, 0x0147cb60
//     and 0x0147cc50, i.e. at strides of 0xc8 and then 0xf0, so this is a
//     VARIABLE-LENGTH serialized asset table and not a vtable array. +0x24 is a
//     handler-function field of such a record, and naming it a vtable slot would
//     assert an object-relative load that no instruction in this body performs.
constexpr Word kBodyEndInclusive = 0x00dd08f1u;

// The only ways this body touches memory: a dword, or a pointer, at a stated
// displacement. A member access would assert an identity the machine-derived
// record cannot corroborate, so the model goes through these helpers. The
// single-argument form takes an already-formed address, which is what
// `self + 0x84` produces, so the displacement each instruction fixes stays
// visible in the model's text.
inline Word* word_at(void* address) { return reinterpret_cast<Word*>(address); }

inline const Word* word_at(const void* address) {
  return reinterpret_cast<const Word*>(address);
}

// The ONE place this model dereferences. Every level of the chain goes through
// it, once per level, so the number of indirections the model performs is
// countable: link_from dereferences once, record_from dereferences once, and
// word_at on a level-2 address dereferences nothing.
inline std::uint8_t* pointer_at(void* address) {
  return reinterpret_cast<std::uint8_t*>(*word_at(address));
}

// The level-1 and level-2 chase, as one named operation each, so the pointer
// LEVELS are the thing the model states rather than something a reader has to
// count casts to verify. There is exactly one dereference per call, and both are
// the machine's own single-load reads.
inline std::uint8_t* link_from(std::uint8_t* receiver) {
  return pointer_at(receiver + kLinkDisplacement);
}

inline std::uint8_t* record_from(std::uint8_t* link) {
  return pointer_at(link + kRecordLinkDisplacement);
}

// The tag arm's six instructions, transcribed so the equivalence is a
// compile-time fact rather than a claim in a comment. The ADD is unconditional,
// which is what makes 0x7fffffff -- not 0 -- the arm's zero-fallthrough case.
inline constexpr Word tag_arm_arithmetic(Word tag) {
  const Word sub = tag - kTagArmSubtractand;                  // 00dd08d4
  const Word neg = 0u - sub;                                   // 00dd08da (CF)
  const Word sbb = (neg == 0u) ? 0u : 0xffffffffu;            // 00dd08dc
  return (sbb & kTagArmSelectMask) + kTagArmSelectAddend;      // 00dd08de, 00dd08e4
}

// The three-callee block's five instructions after the MOVZX, transcribed the
// same way. The selection is on the callee's low BYTE, zero-extended.
inline constexpr Word callee_arm_arithmetic(bool equal) {
  const Word widened = equal ? 0xffffffffu : 0u;               // 00dd0884 MOVZX
  const Word neg = 0u - widened;                               // 00dd088a NEG
  const Word sbb = (neg == 0u) ? 0u : 0xffffffffu;            // 00dd088c SBB
  return (sbb & kCalleeArmSelectMask) + kCalleeArmSelectAddend;
}

static_assert(sizeof(OpaqueSporepediaAsset) == 0x9c,
              "0x98 + 4 is the last byte this body reads on the receiver");
static_assert(kLinkDisplacement + sizeof(Word) == sizeof(OpaqueSporepediaAsset),
              "the last read word ends the modelled receiver exactly");
static_assert(kResultDisplacement + sizeof(Word) <= kLinkDisplacement,
              "the +0x8c result word ends at +0x90 and the +0x98 link word begins "
              "eight bytes later, so the two do not overlap and the eight bytes "
              "between them are never touched by this body");
static_assert(kCompareArgumentDisplacement + kCompareWidthBytes <
                  kResultDisplacement,
              "the twelve bytes 0x004eb930 reads at the address 0x00dd086e forms "
              "end below the result word, so the callee cannot be reading what "
              "this body stores");

static_assert(kOuterTable[0] == kTargetKindOneArm &&
                  kOuterTable[2] == kTargetBareEpilogue &&
                  kOuterTable[1] == kOuterTable[3] &&
                  kOuterTable[3] == kOuterTable[4],
              "outer entry 2 is the bare epilogue and entries 1, 3 and 4 all "
              "share one arm -- the 0xdd08f4 words say exactly that");
static_assert(kKindOneSubTable[0] == kTargetStore3 &&
                  kKindOneSubTable[3] == kTargetStore3,
              "outer entry 0's table repeats the store-3 block at indices 0 and 3");
static_assert(kKindOneSubTable[4] == kTargetBareStore,
              "index 4 of the kind-1 table reaches the bare store, not the top of "
              "the recomputing block, so it stores the leftover guard word");
static_assert(kKindOneSubTable[6] == kTargetThreeCalleeBlock &&
                  kKindOneSubTable[7] == kTargetThreeCalleeBlock,
              "indices 6 and 7 of the kind-1 table are the same three-callee block");
static_assert(kOtherArmSubTable[3] == kTargetBareStore &&
                  kOtherArmSubTable[4] == kTargetTagArm,
              "on the other arm it is index 3 that reaches the bare store and "
              "index 4 that reaches the recomputing block -- the mirror image of "
              "the kind-1 table, and the single easiest thing to transpose here");
static_assert(kTagArmSelectMask + kTagArmSelectAddend == kTagArmOtherValue,
              "the mask plus the addend wraps to 5, not to 0x80000005");
static_assert(kCalleeArmSelectMask + kCalleeArmSelectAddend == kCalleeArmTrueValue,
              "in the other block the same pair sums to 0x7fffffff, which is why "
              "the two blocks are not interchangeable and a transcription that "
              "swaps their masks still produces the right words for the wrong "
              "reasons on half its inputs");
static_assert(kTagArmOtherValue == kCalleeArmFalseValue,
              "both blocks' negative answer is the same word 5, reached by two "
              "different routes");

static_assert(tag_arm_arithmetic(0x53dbcf1u) == kTagArmSelectedValue,
              "NEG's carry is zero only for the subtractand, and the ADD that "
              "follows it is unconditional");
static_assert(tag_arm_arithmetic(0x53dbcf0u) == kTagArmOtherValue,
              "one below the subtractand takes the other arm");
static_assert(tag_arm_arithmetic(0x53dbcf2u) == kTagArmOtherValue,
              "one above the subtractand takes the other arm too -- the selection "
              "is an equality and not a range");
static_assert(tag_arm_arithmetic(0x00000000u) == kTagArmOtherValue,
              "the subtraction is unsigned-wrapping, so 0 is not the subtractand");
static_assert(tag_arm_arithmetic(0x7fffffffu) == kTagArmOtherValue,
              "and wrapping does not make any other word into the subtractand");
static_assert(tag_arm_arithmetic(0x80000000u) == kTagArmOtherValue,
              "the selection is an equality, not a signed or unsigned range test");

static_assert(callee_arm_arithmetic(true) == kCalleeArmTrueValue,
              "a true answer wraps through the mask into the large word");
static_assert(callee_arm_arithmetic(false) == kCalleeArmFalseValue,
              "a false answer is the addend alone");
static_assert(kCalleeArmTrueValue == kTagArmSelectedValue,
              "the two blocks share their true answer");
static_assert(kTagArmSelectedValue != 0u,
              "neither block produces zero on any input");

// -- the three direct callees -------------------------------------------------
// Each is declared here, and none is defined here: the model test defines all
// three as observers. All three signatures are fixed by the callee's own bytes,
// read from the image for this package (see the file header).

// 0x00401090, called at 0x00dd0872 with the word pushed at 0x00dd0871. cdecl,
// ZERO arguments: the callee reads no stack slot and no argument register, and
// its own body is four instructions that load a data word into EAX. Its
// terminator is a bare C3, so it leaves that pushed word on the stack -- which is
// why 0x004eb930 receives it as its own second argument.
//
// The model test's observer samples ESP at its own entry and the trampoline
// samples ESP immediately before each call, so "the first callee consumed
// nothing and left the word in place" is a MEASURED equality in the test and not
// only a claim here.
extern "C" std::uint8_t* PKG_SWARM_W2_00DD07F0_CDECL
sporepedia_species_manager_global_00401090();

// 0x004df400, called at 0x00dd0879 with ECX set by 0x00dd0877 to exactly what
// 0x00401090 returned. __thiscall, NO stack argument: the callee's first act is
// to store ECX and reload it, and it reads no [ebp+0x8]. Its whole body is that
// reload, an ADD and a bare C3, so its return is its receiver plus the header's
// kCalleeShiftDisplacement.
//
// The model test's observer asserts both halves: the receiver it is handed is the
// previous callee's return and not the object and not the comparison address, and
// its own return is the receiver plus the shift.
extern "C" std::uint8_t* PKG_SWARM_W2_00DD07F0_CALLEE_THISCALL
sporepedia_member_shift_004df400(std::uint8_t* receiver);

// 0x004eb930, called at 0x00dd087f with the word pushed at 0x00dd087e as its
// first argument and the word pushed at 0x00dd0871, still on the stack, as its
// second. cdecl, TWO four-byte stack arguments: the callee reads [ebp+0x8] and
// [ebp+0xc] and dereferences both. It returns one byte in AL, and 0x00dd0884's
// MOVZX ECX,AL consumes exactly that byte.
//
// The pointer level is TWO on each side and the model test plants decoy twelve
// byte records at the neighbouring depths so that a reconstruction reading
// [arg1+0..8] as a value, or reading the record at the wrong level, is refuted
// rather than merely discouraged.
extern "C" bool PKG_SWARM_W2_00DD07F0_CDECL
sporepedia_equal_three_dwords_004eb930(const void* first,
                                       const void* second);

// The reconstruction itself. Declared here so the model test can call it through
// the same header, and defined in the .cpp of this package. The name embeds the
// target's 8-hex VA, which is what binds this span to the target record.
extern "C" void PKG_SWARM_W2_00DD07F0_THISCALL re_00dd07f0(
    OpaqueSporepediaAsset* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0
