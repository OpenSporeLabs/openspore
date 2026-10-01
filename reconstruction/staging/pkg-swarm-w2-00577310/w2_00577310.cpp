// PKG-SWARM-W2-00577310 -- VA 0x00577310
// FUN_00577310 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22), slot +0x48 of the
// 24-word code-pointer table at 0x013f57f8.
//
// THE COMPLETE BODY: 147 instructions, 0x00577310..0x005774e8 inclusive, 473
// bytes (ghidra_function.body_start 0x00577310, body_end 0x005774e8,
// body_span_bytes 473). The listing below was re-derived for this package with
// `objdump -D -b binary -m i386 -M intel --adjust-vma=0x00577310` over the 0x1d9
// bytes at the file offset for this VA. It reproduces the committed Ghidra
// listing instruction for instruction, at the same addresses and with the same
// lengths, so nothing in this model rests on a re-parse.
//
//   00577310  83 ec 28              SUB ESP,0x28
//   00577313  53                    PUSH EBX
//   00577314  56                    PUSH ESI
//   00577315  8b f1                 MOV ESI,ECX
//   00577317  83 be 08 03 00 00 00  CMP DWORD PTR [ESI+0x308],0x0
//   0057731e  57                    PUSH EDI
//   0057731f  0f 85 bd 00 00 00     JNZ 0x005773e2
//   00577325  6a 00                 PUSH 0x0
//   00577327  6a 00                 PUSH 0x0
//   00577329  6a 00                 PUSH 0x0
//   0057732b  6a 00                 PUSH 0x0
//   0057732d  68 30 b4 3e 01        PUSH 0x13eb430
//   00577332  6a 34                 PUSH 0x34
//   00577334  e8 67 00 9d 00        CALL 0x00f473a0
//   00577339  83 c4 18              ADD ESP,0x18
//   0057733c  85 c0                 TEST EAX,EAX
//   0057733e  74 0d                 JE 0x0057734d
//   00577340  6a ff                 PUSH 0xffffffff
//   00577342  8b c8                 MOV ECX,EAX
//   00577344  e8 97 94 23 00        CALL 0x007b07e0
//   00577349  8b f8                 MOV EDI,EAX
//   0057734b  eb 02                 JMP 0x0057734f
//   0057734d  33 ff                 XOR EDI,EDI
//   0057734f  8b 9e 08 03 00 00     MOV EBX,DWORD PTR [ESI+0x308]
//   00577355  3b fb                 CMP EDI,EBX
//   00577357  74 1f                 JE 0x00577378
//   00577359  85 ff                 TEST EDI,EDI
//   0057735b  74 08                 JE 0x00577365
//   0057735d  8b 07                 MOV EAX,DWORD PTR [EDI]
//   0057735f  8b 10                 MOV EDX,DWORD PTR [EAX]
//   00577361  8b cf                 MOV ECX,EDI
//   00577363  ff d2                 CALL EDX
//   00577365  89 be 08 03 00 00     MOV DWORD PTR [ESI+0x308],EDI
//   0057736b  85 db                 TEST EBX,EBX
//   0057736d  74 09                 JE 0x00577378
//   0057736f  8b 03                 MOV EAX,DWORD PTR [EBX]
//   00577371  8b 50 04              MOV EDX,DWORD PTR [EAX+0x4]
//   00577374  8b cb                 MOV ECX,EBX
//   00577376  ff d2                 CALL EDX
//   00577378  8b 8e 08 03 00 00     MOV ECX,DWORD PTR [ESI+0x308]
//   0057737e  8d 44 24 10           LEA EAX,[ESP+0x10]
//   00577382  bf 5b a9 10 05        MOV EDI,0x510a95b
//   00577387  bb 00 41 46 40        MOV EBX,0x40464100
//   0057738c  50                    PUSH EAX
//   0057738d  c7 44 24 14 b0 e4 04 81 89  MOV DWORD PTR [ESP+0x14],0x8104e4b0
//   00577395  89 7c 24 18           MOV DWORD PTR [ESP+0x18],EDI
//   00577399  89 5c 24 1c           MOV DWORD PTR [ESP+0x1c],EBX
//   0057739d  e8 ee aa 23 00        CALL 0x007b1e90
//   005773a2  8d 4c 24 1c           LEA ECX,[ESP+0x1c]
//   005773a6  51                    PUSH ECX
//   005773a7  8b 8e 08 03 00 00     MOV ECX,DWORD PTR [ESI+0x308]
//   005773ad  c7 44 24 20 2f cc 1f 9d  MOV DWORD PTR [ESP+0x20],0x9d1fcc2f
//   005773b5  89 7c 24 24           MOV DWORD PTR [ESP+0x24],EDI
//   005773b9  89 5c 24 28           MOV DWORD PTR [ESP+0x28],EBX
//   005773bd  e8 ce aa 23 00        CALL 0x007b1e90
//   005773c2  8b 8e 08 03 00 00     MOV ECX,DWORD PTR [ESI+0x308]
//   005773c8  8d 54 24 28           LEA EDX,[ESP+0x28]
//   005773cc  52                    PUSH EDX
//   005773cd  c7 44 24 2c 46 8f 70 7d  MOV DWORD PTR [ESP+0x2c],0x7d708f46
//   005773d5  89 7c 24 30           MOV DWORD PTR [ESP+0x30],EDI
//   005773d9  89 5c 24 34           MOV DWORD PTR [ESP+0x34],EBX
//   005773dd  e8 ae aa 23 00        CALL 0x007b1e90
//   005773e2  8b 5c 24 38           MOV EBX,DWORD PTR [ESP+0x38]
//   005773e6  83 fb ff              CMP EBX,0xffffffff
//   005773e9  0f 84 f1 00 00 00     JE 0x005774e0
//   005773ef  c7 44 24 38 00 00 00 00  MOV DWORD PTR [ESP+0x38],0x0
//   005773f7  e8 34 6a 10 00        CALL 0x0067de30
//   005773fc  8b 4c 24 38           MOV ECX,DWORD PTR [ESP+0x38]
//   00577400  8b f8                 MOV EDI,EAX
//   00577402  85 c9                 TEST ECX,ECX
//   00577404  74 0f                 JE 0x00577415
//   00577406  c7 44 24 38 00 00 00 00  MOV DWORD PTR [ESP+0x38],0x0
//   0057740e  8b 01                 MOV EAX,DWORD PTR [ECX]
//   00577410  8b 50 04              MOV EDX,DWORD PTR [EAX+0x4]
//   00577413  ff d2                 CALL EDX
//   00577415  8b 15 d4 cd 50 01     MOV EDX,DWORD PTR ds:0x0150cdd4
//   0057741b  8b 07                 MOV EAX,DWORD PTR [EDI]
//   0057741d  8b 40 2c              MOV EAX,DWORD PTR [EAX+0x2c]
//   00577420  8d 4c 24 38           LEA ECX,[ESP+0x38]
//   00577424  51                    PUSH ECX
//   00577425  52                    PUSH EDX
//   00577426  53                    PUSH EBX
//   00577427  8b cf                 MOV ECX,EDI
//   00577429  ff d0                 CALL EAX
//   0057742b  84 c0                 TEST AL,AL
//   0057742d  0f 84 9e 00 00 00     JE 0x005774d1
//   00577433  6a 00                 PUSH 0x0
//   00577435  6a 00                 PUSH 0x0
//   00577437  6a 00                 PUSH 0x0
//   00577439  6a 00                 PUSH 0x0
//   0057743b  68 30 b4 3e 01        PUSH 0x13eb430
//   00577440  6a 34                 PUSH 0x34
//   00577442  e8 59 ff 9c 00        CALL 0x00f473a0
//   00577447  83 c4 18              ADD ESP,0x18
//   0057744a  85 c0                 TEST EAX,EAX
//   0057744c  74 0d                 JE 0x0057745b
//   0057744e  6a ff                 PUSH 0xffffffff
//   00577450  8b c8                 MOV ECX,EAX
//   00577452  e8 89 93 23 00        CALL 0x007b07e0
//   00577457  8b f8                 MOV EDI,EAX
//   00577459  eb 02                 JMP 0x0057745d
//   0057745b  33 ff                 XOR EDI,EDI
//   0057745d  8b 9e 0c 03 00 00     MOV EBX,DWORD PTR [ESI+0x30c]
//   00577463  3b fb                 CMP EDI,EBX
//   00577465  74 1f                 JE 0x00577486
//   00577467  85 ff                 TEST EDI,EDI
//   00577469  74 08                 JE 0x00577473
//   0057746b  8b 17                 MOV EDX,DWORD PTR [EDI]
//   0057746d  8b 02                 MOV EAX,DWORD PTR [EDX]
//   0057746f  8b cf                 MOV ECX,EDI
//   00577471  ff d0                 CALL EAX
//   00577473  89 be 0c 03 00 00     MOV DWORD PTR [ESI+0x30c],EDI
//   00577479  85 db                 TEST EBX,EBX
//   0057747b  74 09                 JE 0x00577486
//   0057747d  8b 13                 MOV EDX,DWORD PTR [EBX]
//   0057747f  8b 42 04              MOV EAX,DWORD PTR [EDX+0x4]
//   00577482  8b cb                 MOV ECX,EBX
//   00577484  ff d0                 CALL EAX
//   00577486  8b 54 24 38           MOV EDX,DWORD PTR [ESP+0x38]
//   0057748a  8d 4c 24 0c           LEA ECX,[ESP+0xc]
//   0057748e  51                    PUSH ECX
//   0057748f  68 e1 d5 0e 70        PUSH 0x700ed5e1
//   00577494  52                    PUSH EDX
//   00577495  c7 44 24 18 00 00 00 00  MOV DWORD PTR [ESP+0x18],0x0
//   0057749d  e8 fe 9d 12 00        CALL 0x006a12a0
//   005774a2  8b 44 24 18           MOV EAX,DWORD PTR [ESP+0x18]
//   005774a6  83 c4 0c              ADD ESP,0xc
//   005774a9  85 c0                 TEST EAX,EAX
//   005774ab  74 24                 JE 0x005774d1
//   005774ad  8b 8e 0c 03 00 00     MOV ECX,DWORD PTR [ESI+0x30c]
//   005774b3  89 44 24 28           MOV DWORD PTR [ESP+0x28],EAX
//   005774b7  8d 44 24 28           LEA EAX,[ESP+0x28]
//   005774bb  50                    PUSH EAX
//   005774bc  c7 44 24 30 5b a9 10 05  MOV DWORD PTR [ESP+0x30],0x510a95b
//   005774c4  c7 44 24 34 00 41 46 40  MOV DWORD PTR [ESP+0x34],0x40464100
//   005774cc  e8 bf a9 23 00        CALL 0x007b1e90
//   005774d1  8b 4c 24 38           MOV ECX,DWORD PTR [ESP+0x38]
//   005774d5  85 c9                 TEST ECX,ECX
//   005774d7  74 07                 JE 0x005774e0
//   005774d9  8b 11                 MOV EDX,DWORD PTR [ECX]
//   005774db  8b 42 04              MOV EAX,DWORD PTR [EDX+0x4]
//   005774de  ff d0                 CALL EAX
//   005774e0  5f                    POP EDI
//   005774e1  5e                    POP ESI
//   005774e2  5b                    POP EBX
//   005774e3  83 c4 28              ADD ESP,0x28
//   005774e6  c2 04 00              RET 0x4
//
// WHAT THE BODY IS, in one paragraph. A lazily-initialising editor setup. It
// holds two object pointers in the receiver, at +0x308 and +0x30c. On the first
// call it builds the +0x308 one -- ask a factory for an object named "Editor"
// (0x013eb430 is that string, 0x34 is its first argument), construct it in place
// with the all-ones word, swap it into the member acquiring the new one and
// releasing the old one through the table slots at +0x0 and +0x4 -- and then
// registers three 12-byte records on it. Then, for the caller's argument unless
// it is the all-ones sentinel, it asks a global object (fetched by the six-byte
// accessor 0x0067de30) a yes/no question through the table slot at +0x2c, and on
// a yes builds the SECOND member object the same way, looks an instance id up on
// the object the query returned, and registers that id as a fourth record on the
// second member. Finally, if the query left a non-null word in the caller's
// argument slot, that word is released through the slot at +0x4.
//
// THE FRAME IS THE LOAD-BEARING PART, and it is settled by two independent
// facts rather than by arithmetic alone.
//
// FACT ONE. `MOV EBX,DWORD PTR [ESP+0x38]` at 0x005773e2 is reached from TWO
// paths: by fall-through from the third registration call, and by the `JNZ` at
// 0x0057731f, which arrives having pushed nothing but the three saved registers.
// For one instruction to read the same word on both paths, ESP must be the same
// on both, so every one of the three `PUSH`es at 0x0057738c, 0x005773a6 and
// 0x005773cc must have been undone by its own callee. That fixes ESP at
// entry_ESP-0x34 on both paths and therefore puts [ESP+0x38] at entry_ESP+0x4 --
// the caller's own argument word.
//
// FACT TWO, INDEPENDENT AND FROM ANOTHER BODY'S BYTES. 0x007b1e90's terminator
// is `C2 04 00` at 0x007b1f3b, i.e. RET 0x4: it pops its own single stack word.
// Its own prologue is five pushes and its 0x007b1ea7 `MOV EBX,[ESP+0x18]`
// therefore reads ITS entry_ESP+0x4, which is the word this body pushed. The
// same callee's 0x007b1ead `MOV EDI,[EBX+0x8]` / 0x007b1eb4
// `CMP EDI,0x40464100` reads the THIRD word of the record this body wrote and
// compares it against the constant this body wrote, so the callee corroborates
// both the 12-byte size and the tail value.
//
// UNDER THAT FRAME the three registration records are three CONTIGUOUS 12-byte
// slots at entry_ESP-0x24, -0x18 and -0xc, with the fourth record's frame
// displacement 0x005774b7 `LEA EAX,[ESP+0x28]` landing on the THIRD record's
// address exactly. The fourth registration overwrites the third record in place.
// That is a fact about the frame and the model keeps it, as a single
// `kFrameBytes` array the test can address.
// (The alternative reading -- that the callees do not pop -- makes the three
// records overlap each other at one word, makes [ESP+0x38] at 0x005773e2 read
// the third record's own tail word instead of the caller's argument, and is
// refuted by 0x007b1f3b outright. It is recorded because it is the natural first
// guess, not because it survives.)
//
// THE INCOMING ARGUMENT IS ITSELF AN OUT-PARAMETER. 0x005773ef stores 0 over
// the caller's argument slot, and 0x00577420 then hands that very address to the
// slot +0x2c call as its fourth pushed word. So the body clears the caller's
// word, gives the callee a pointer to it, and reads the callee's answer back out
// of it at 0x00577486 and 0x005774d1. The model keeps the word in a local of its
// own and passes that local's address, which is what lets the test make the
// callee write through it and then check that the model reads the written value
// rather than the value the caller passed.
//
// 0x00577406..0x00577413 IS UNREACHABLE, and the model says so rather than
// hiding it. 0x005773ef stores 0 into the argument slot; the only instruction
// between there and the `TEST ECX,ECX` at 0x00577402 is the call to 0x0067de30,
// whose entire body is `MOV EAX,[0x015fd8a8]` / `RET` -- six bytes that read one
// absolute cell and can reach no caller's frame. ECX is therefore reloaded with
// 0 at 0x005773fc, the `JE` at 0x00577404 is always taken, and the release of
// that word never runs. The block is reproduced because it is in the listing and
// the test can prove it is never entered; it is reproduced as a real conditional
// rather than deleted, because deleting it would hide a fact a reader of the
// bytes can check.
//
// DISPATCH. Seven indirect transfers, all of them the same two-level shape: a
// table pointer is read out of an object, then a code word is read out of the
// table at +0x0 (twice for the new member, once for the query), +0x4 (twice for
// the old member, once for the tail release) or +0x2c (once, the query). The
// receiver of the body is never dispatched through: the body never reads its
// +0x00. The three shapes are the three `using` types in the header, reached
// only through `vtable_word_at`.
//
// The +0x2c query's second argument is the CONTENTS of the cell at 0x0150cdd4:
// 0x00577415 is `MOV EDX,DWORD PTR DS:0x0150cdd4`, a load, and 0x00577425 pushes
// EDX. The callee therefore receives a bare word and reads no pointer. The cell
// holds 0x3f800000 in the committed image (the single 1.0f); the model holds the
// cell in a package-scope word and forwards whatever it holds, which is what the
// two instructions fix, and the test drives that word with a value the image does
// not hold so a hard-coded reconstruction is refuted.
//
// The instance-id lookup's BOOL is DISCARDED. 0x0067749d's callee returns a
// bool in AL; 0x005774a2 overwrites EAX from the frame word the callee wrote and
// 0x005774a9 tests THAT. The model reads the frame word and the test drives a
// case where the callee returns false and still writes a non-zero word, and
// another where it returns true and writes zero -- only the second pair of
// behaviours is what the bytes implement.
//
// NOT MODELLED: the saved-register traffic (POP EDI / POP ESI / POP EBX /
// ADD ESP,0x28 at 0x005774e0..0x005774e3) has no C++ expression, so the model
// asserts only that it leaves the stack balanced, which the test measures. The
// unconditional `JMP 0x0057734f` and `JMP 0x0057745d` are intra-procedural and
// become the two arms of a single conditional each. The value left in EAX at the
// three epilogue entries is incidental and path-dependent, so nothing is
// modelled for it and nothing is asserted about it.

#include "w2_00577310_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00577310 {

// The word at 0x0150cdd4, held here because that cell is in the original
// program's .data at an address no model process can map. The image holds
// 0x3f800000 (the single 1.0f); the model forwards whatever is here, which is
// what 0x00577415 and 0x00577425 say, and the model test overwrites it with a
// value the image does not hold so that a hard-coded reconstruction is caught.
Word g_query_weight_cell = kQueryWeightCellImageValue;

extern "C" void W2_00577310_THISCALL re_00577310(EditorReceiver* receiver,
                                                  Word argument) {
  // 00577310  SUB ESP,0x28
  // 00577313  PUSH EBX
  // 00577314  PUSH ESI
  // 00577315  MOV ESI,ECX
  //
  // The receiver is aliased into ESI and every receiver access in the body goes
  // through that alias -- which is why the machine-derived receiver record names
  // ECX with shape R-ALIAS rather than reporting ECX's own operands. Its
  // displacement list is 0x308 and 0x30c, both read AND written, and it is
  // bounds_only, so the two are reached through accessors and no member is named.
  std::uint8_t* const self = byte_at(receiver, 0u);
  Word* const tool_member = word_at(self, kReceiverToolMemberDisplacement);
  Word* const target_member = word_at(self, kReceiverTargetMemberDisplacement);

  // The frame. SUB ESP,0x28 reserves forty bytes at entry_ESP-0x28, i.e. at
  // +0x0c of the base the three saved-register pushes leave behind, and the
  // frame's five addressed words are +0x0c (the lookup's out word) and the three
  // 12-byte records at +0x10, +0x1c and +0x28. The fourth registration record
  // reuses +0x28. Modelled as one array so that aliasing is a real aliasing and
  // not a comment about one.
  alignas(4) std::uint8_t frame[kFrameBytes];

  // 00577317  CMP DWORD PTR [ESI+0x308],0x0
  // 0057731f  JNZ 0x005773e2
  //
  // The ONLY guard on the whole initialisation block, and it is a null test on
  // the member, not on anything the caller passed. A warm receiver skips
  // everything down to the argument test, which is why the third registration
  // call is reached with the member either freshly built or already there.
  if (*tool_member == 0u) {
    // 00577325  PUSH 0x0 / 0x0 / 0x0 / 0x0
    // 0057732d  PUSH 0x13eb430
    // 00577332  PUSH 0x34
    // 00577334  CALL 0x00f473a0
    // 00577339  ADD ESP,0x18
    //
    // Six words, pushed right to left, so the first argument is 0x34 and the
    // second is the ADDRESS of the seven-byte ASCII string "Editor" at
    // 0x013eb430. The body drops all six itself, which is what makes the callee
    // cdecl: ADD ESP,0x18 is 6*4.
    const Word fresh = factory_lookup_00f473a0(kFactoryFirstArgument,
                                                reinterpret_cast<const char*>(
                                                    kFactoryClassNameAddress),
                                                0u, 0u, 0u, 0u);

    // 0057733c  TEST EAX,EAX
    // 0057733e  JE 0x0057734d
    // 00577340  PUSH 0xffffffff
    // 00577342  MOV ECX,EAX
    // 00577344  CALL 0x007b07e0
    // 00577349  MOV EDI,EAX
    // 0057734b  JMP 0x0057734f
    // 0057734d  XOR EDI,EDI
    //
    // A null from the factory is NOT an early return: the branch skips the
    // constructor and produces a null replacement, and the swap below then runs
    // with a null member and a null replacement -- which are EQUAL, so the whole
    // swap is skipped and three registration calls are made on a NULL receiver.
    // That is what the bytes do and the model reproduces it; a "bail out on
    // allocation failure" reconstruction would take a different path and is one
    // of the cases the test refutes.
    void* replacement = 0;
    if (fresh != 0u) {
      // 007b07e0 is __thiscall with one stack word and its own 0x007b0852
      // `MOV EAX,ESI` shows it hands its receiver back; the body takes that word
      // as the replacement.
      replacement = construct_in_place_007b07e0(reinterpret_cast<void*>(fresh),
                                                kConstructorArgument);
    }

    // 0057734f  MOV EBX,DWORD PTR [ESI+0x308]
    // 00577355  CMP EDI,EBX
    // 00577357  JE 0x00577378
    //
    // The old member is captured BEFORE the store and is released AFTER it, so
    // the order acquire-new / store / release-old is observable to both slot
    // functions. The equality short-circuit means a member that already holds
    // exactly what the factory would produce causes no acquire, no store and no
    // release at all.
    void* const previous = reinterpret_cast<void*>(*tool_member);
    if (replacement != previous) {
      // 00577359  TEST EDI,EDI
      // 0057735b  JE 0x00577365
      // 0057735d  MOV EAX,DWORD PTR [EDI]        <- level one: the table pointer
      // 0057735f  MOV EDX,DWORD PTR [EAX]        <- level two: slot +0x0
      // 00577361  MOV ECX,EDI
      // 00577363  CALL EDX
      if (replacement != 0) {
        const AcquireSlot acquire = reinterpret_cast<AcquireSlot>(
            vtable_word_at(replacement, kSlotAcquireDisplacement));
        acquire(replacement);
      }
      // 00577365  MOV DWORD PTR [ESI+0x308],EDI
      *tool_member = static_cast<Word>(reinterpret_cast<std::uintptr_t>(replacement));

      // 0057736b  TEST EBX,EBX
      // 0057736d  JE 0x00577378
      // 0057736f  MOV EAX,DWORD PTR [EBX]        <- level one
      // 00577371  MOV EDX,DWORD PTR [EAX+0x4]    <- level two: slot +0x4
      // 00577374  MOV ECX,EBX
      // 00577376  CALL EDX
      //
      // The release of the OLD member happens after the store, and is guarded
      // on the old member being non-null -- which it is, because the whole block
      // was entered on `*tool_member == 0`. The guard is reproduced anyway: it
      // is the instruction, and a reconstruction that dropped it would call
      // through a null table on a different input.
      if (previous != 0) {
        const ReleaseSlot release = reinterpret_cast<ReleaseSlot>(
            vtable_word_at(previous, kSlotReleaseDisplacement));
        release(previous);
      }
    }

    // 00577378  MOV ECX,DWORD PTR [ESI+0x308]
    // 0057737e  LEA EAX,[ESP+0x10]
    //
    // The receiver of all three registrations is the member RE-READ from the
    // frame, not the value in a register: a constructor that stored something
    // other than what it returned, or an acquire that changed the member, would
    // both show up here. The model re-reads the member for each call for the
    // same reason.
    void* const tool = reinterpret_cast<void*>(*tool_member);

    // 00577382  MOV EDI,0x510a95b
    // 00577387  MOV EBX,0x40464100
    //
    // Two of the three record words are built once in registers and stored into
    // all three records. They are constants, not values derived from anything.
    // The third record's tail is the same 0x40464100 the callee compares against
    // at 0x007b1eb4, which is why the model does not treat it as opaque.
    //
    // 0057738c  PUSH EAX
    // 0057738d  MOV DWORD PTR [ESP+0x14],0x8104e4b0
    // 00577395  MOV DWORD PTR [ESP+0x18],EDI
    // 00577399  MOV DWORD PTR [ESP+0x1c],EBX
    // 0057739d  CALL 0x007b1e90
    *frame_word_at(frame, kFrameRecordOneDisplacement + kRecordIdDisplacement) = kRecordIdOne;
    *frame_word_at(frame, kFrameRecordOneDisplacement + kRecordMiddleDisplacement) =
        kRecordMiddleWord;
    *frame_word_at(frame, kFrameRecordOneDisplacement + kRecordTailDisplacement) = kRecordTailWord;
    record_register_007b1e90(tool, reinterpret_cast<const PropertyRecord*>(
                                    frame_word_at(frame, kFrameRecordOneDisplacement)));

    // 005773a2  LEA ECX,[ESP+0x1c]
    // 005773a6  PUSH ECX
    // 005773a7  MOV ECX,DWORD PTR [ESI+0x308]
    // 005773ad  MOV DWORD PTR [ESP+0x20],0x9d1fcc2f
    // 005773b5  MOV DWORD PTR [ESP+0x24],EDI
    // 005773b9  MOV DWORD PTR [ESP+0x28],EBX
    // 005773bd  CALL 0x007b1e90
    //
    // The SECOND record's displacement is +0x1c, which is exactly twelve bytes
    // past the first: under this frame the three records are adjacent and
    // distinct. A one-past read of the first record's address would put them at
    // +0x10 and +0x14 and make the third overlap the second; that is the frame
    // error the two arguments of this reconstruction are chosen to make
    // impossible, and the test checks the addresses the callee actually receives.
    *frame_word_at(frame, kFrameRecordTwoDisplacement + kRecordIdDisplacement) = kRecordIdTwo;
    *frame_word_at(frame, kFrameRecordTwoDisplacement + kRecordMiddleDisplacement) =
        kRecordMiddleWord;
    *frame_word_at(frame, kFrameRecordTwoDisplacement + kRecordTailDisplacement) = kRecordTailWord;
    record_register_007b1e90(reinterpret_cast<void*>(*tool_member),
                             reinterpret_cast<const PropertyRecord*>(
                                 frame_word_at(frame, kFrameRecordTwoDisplacement)));

    // 005773c2  MOV ECX,DWORD PTR [ESI+0x308]
    // 005773c8  LEA EDX,[ESP+0x28]
    // 005773cc  PUSH EDX
    // 005773cd  MOV DWORD PTR [ESP+0x2c],0x7d708f46
    // 005773d5  MOV DWORD PTR [ESP+0x30],EDI
    // 005773d9  MOV DWORD PTR [ESP+0x34],EBX
    // 005773dd  CALL 0x007b1e90
    *frame_word_at(frame, kFrameRecordThreeDisplacement + kRecordIdDisplacement) = kRecordIdThree;
    *frame_word_at(frame, kFrameRecordThreeDisplacement + kRecordMiddleDisplacement) =
        kRecordMiddleWord;
    *frame_word_at(frame, kFrameRecordThreeDisplacement + kRecordTailDisplacement) = kRecordTailWord;
    record_register_007b1e90(reinterpret_cast<void*>(*tool_member),
                             reinterpret_cast<const PropertyRecord*>(
                                 frame_word_at(frame, kFrameRecordThreeDisplacement)));
  }

  // 005773e2  MOV EBX,DWORD PTR [ESP+0x38]
  // 005773e6  CMP EBX,0xffffffff
  // 005773e9  JE 0x005774e0
  //
  // The caller's one argument, read at entry_ESP+0x4, and the all-ones word is
  // its sentinel. Note this is an EQUALITY against 0xffffffff, not a non-zero
  // test: argument 0 is a real subject, and the test drives both.
  Word handle = argument;
  if (handle == kSentinelWord) {
    // 005774e0 -- the epilogue, reached from here. Note what is NOT done on this
    // arm: no global accessor, no query, no lookup, no release, and no write to
    // either member beyond whatever the cold block above already did.
    return;
  }

  // 005773ef  MOV DWORD PTR [ESP+0x38],0x0
  //
  // The caller's own argument word is cleared IN PLACE. The model keeps it in a
  // local, so `handle` becomes zero here -- and the address the model hands to
  // the query is this local's, which is what reproduces the aliasing the bytes
  // get for free from the frame layout.
  handle = 0u;

  // 005773f7  CALL 0x0067de30
  //
  // No argument in any register and none on the stack. The callee is six bytes:
  // `MOV EAX,[0x015fd8a8]` / `RET`. Whatever ECX held is irrelevant to it, and
  // whatever this body leaves in ECX for it is not read afterwards. The test's
  // observer is a no-argument function precisely so that a reconstruction which
  // passed the receiver here would not compile.
  void* const global = global_object_0067de30();

  // 005773fc  MOV ECX,DWORD PTR [ESP+0x38]
  // 00577400  MOV EDI,EAX
  // 00577402  TEST ECX,ECX
  // 00577404  JE 0x00577415
  // 00577406  MOV DWORD PTR [ESP+0x38],0x0
  // 0057740e  MOV EAX,DWORD PTR [ECX]
  // 00577410  MOV EDX,DWORD PTR [EAX+0x4]
  // 00577413  CALL EDX
  //
  // UNREACHABLE, and reproduced rather than deleted. `handle` was stored as zero
  // two instructions above the only call that intervenes, and that call is the
  // six-byte global accessor, which reads one absolute cell and touches no
  // caller's frame. So the reloaded value is zero, the `JE` is always taken and
  // this release never runs. The conditional is written as the machine has it so
  // that a reader can check the claim against the bytes, and the test proves the
  // block is not entered by checking that exactly one release of the handle
  // happens in the whole call -- the tail one at 0x005774de.
  if (handle != 0u) {
    // 00577406 stores 0 into the argument word and 0x0057740e/0x00577410/0x00577413
    // then release the value ECX was holding at 0x005773fc, i.e. the value from
    // BEFORE that store. Captured first here so the release is of the old value.
    void* const doomed = reinterpret_cast<void*>(handle);
    handle = 0u;
    const ReleaseSlot early = reinterpret_cast<ReleaseSlot>(
        vtable_word_at(doomed, kSlotReleaseDisplacement));
    early(doomed);
  }

  // 00577415  MOV EDX,DWORD PTR ds:0x0150cdd4
  //
  // A LOAD of the cell's contents into EDX, not an address-of: 0x00577425
  // pushes EDX, so the slot +0x2c call's second argument is the WORD the cell
  // holds, and the callee reads no pointer at all. In the committed image the
  // cell holds 0x3f800000, the IEEE-754 single 1.0f. The model holds the cell in
  // a package-scope word (the cell's address is not mappable in a model process)
  // and forwards whatever it holds, which is the behaviour the two instructions
  // fix; the test drives it with a value the image does not hold so that a
  // reconstruction which hard-codes 0x3f800000 is refuted.
  const Word weight = g_query_weight_cell;

  // 0057741b  MOV EAX,DWORD PTR [EDI]        <- level one on the global object
  // 0057741d  MOV EAX,DWORD PTR [EAX+0x2c]   <- level two: the query slot
  // 00577420  LEA ECX,[ESP+0x38]             <- the caller's argument slot again
  // 00577424  PUSH ECX                       <- fourth pushed: the out-parameter
  // 00577425  PUSH EDX                       <- third pushed: the cell's word
  // 00577426  PUSH EBX                       <- second pushed: the subject
  // 00577427  MOV ECX,EDI
  // 00577429  CALL EAX
  //
  // Four words, pushed right to left, so the argument order is
  // (subject, weight, out-parameter) after the receiver. The subject is
  // the caller's argument as it was BEFORE the clear at 0x005773ef -- EBX still
  // holds it -- which is the one place the body keeps a second copy of an
  // incoming value, and the test checks the subject is the ORIGINAL argument
  // while the out-parameter is a pointer to the cleared word. `handle` is zero
  // here and `argument` is not, exactly as EBX and the frame slot diverge in the
  // machine.
  const QuerySlot query = reinterpret_cast<QuerySlot>(
      vtable_word_at(global, kSlotQueryDisplacement));
  const bool hit = query(global, argument, weight, &handle);

  // 0057742b  TEST AL,AL
  // 0057742d  JE 0x005774d1
  //
  // The only test of the query's answer. A false answer skips the entire second
  // half -- the second factory, the second member swap, the instance-id lookup
  // and the fourth registration -- and goes straight to the tail release, which
  // still runs on whatever the query left in the argument word.
  if (hit) {
    // 00577433..00577442  the same six factory words as before, and the same
    // null-tolerant constructor, and 00577447 ADD ESP,0x18.
    const Word second = factory_lookup_00f473a0(kFactoryFirstArgument,
                                                reinterpret_cast<const char*>(
                                                    kFactoryClassNameAddress),
                                                0u, 0u, 0u, 0u);
    // 0057744a  TEST EAX,EAX
    // 0057744c  JE 0x0057745b
    // 0057744e  PUSH 0xffffffff
    // 00577450  MOV ECX,EAX
    // 00577452  CALL 0x007b07e0
    // 00577457  MOV EDI,EAX
    // 00577459  JMP 0x0057745d
    // 0057745b  XOR EDI,EDI
    void* second_replacement = 0;
    if (second != 0u) {
      second_replacement = construct_in_place_007b07e0(
          reinterpret_cast<void*>(second), kConstructorArgument);
    }

    // 0057745d  MOV EBX,DWORD PTR [ESI+0x30c]
    // 00577463  CMP EDI,EBX
    // 00577465  JE 0x00577486
    // 00577467  TEST EDI,EDI
    // 00577469  JE 0x00577473
    // 0057746b  MOV EDX,DWORD PTR [EDI]       <- level one
    // 0057746d  MOV EAX,DWORD PTR [EDX]       <- level two: slot +0x0
    // 0057746f  MOV ECX,EDI
    // 00577471  CALL EAX
    // 00577473  MOV DWORD PTR [ESI+0x30c],EDI
    // 00577479  TEST EBX,EBX
    // 0057747b  JE 0x00577486
    // 0057747d  MOV EDX,DWORD PTR [EBX]       <- level one
    // 0057747f  MOV EAX,DWORD PTR [EDX+0x4]   <- level two: slot +0x4
    // 00577482  MOV ECX,EBX
    // 00577484  CALL EAX
    //
    // The second swap, byte for byte the same sequence as the first except that
    // it stores into the receiver's +0x30c and that the new member's code word
    // goes through EDX where the first one went through EAX. Register choice is
    // not a semantic fact and the model does not reproduce it; the destination
    // displacement and the acquire/store/release order are semantic and it does.
    void* const second_previous = reinterpret_cast<void*>(*target_member);
    if (second_replacement != second_previous) {
      if (second_replacement != 0) {
        const AcquireSlot acquire_second = reinterpret_cast<AcquireSlot>(
            vtable_word_at(second_replacement, kSlotAcquireDisplacement));
        acquire_second(second_replacement);
      }
      *target_member =
          static_cast<Word>(reinterpret_cast<std::uintptr_t>(second_replacement));
      if (second_previous != 0) {
        const ReleaseSlot release_second = reinterpret_cast<ReleaseSlot>(
            vtable_word_at(second_previous, kSlotReleaseDisplacement));
        release_second(second_previous);
      }
    }

    // 00577486  MOV EDX,DWORD PTR [ESP+0x38]
    //
    // The query's ANSWER, read back out of the caller's argument word. This is
    // the first argument of the lookup, and it is the value the query callee
    // wrote -- not the value the caller passed and not the query's bool.
    const Word subject = handle;

    // 0057748a  LEA ECX,[ESP+0xc]
    // 0057748e  PUSH ECX                       <- third pushed: the out-parameter
    // 0057748f  PUSH 0x700ed5e1                <- second pushed: the key
    // 00577494  PUSH EDX                       <- first pushed: the subject
    //
    // Three words, right to left. The callee is cdecl: bare RET at 0x006a12da.
    // Its own body writes the instance id into ITS THIRD argument (0x006a12cf
    // with the stack already balanced by the inner __thiscall at 0x006a12b7), so
    // the out-parameter really is the frame word at +0x0c.
    //
    // 00577495  MOV DWORD PTR [ESP+0x18],0x0
    //
    // ...and it is zeroed AFTER all three pushes and BEFORE the call, so the
    // callee is handed a word that already holds 0 whatever was in the frame.
    // The test reads it from inside the observer, which is the only way to catch
    // a model that cleared it earlier or not at all.
    *frame_word_at(frame, kFrameLookupOutDisplacement) = 0u;
    const bool reported = instance_id_lookup_006a12a0(
        reinterpret_cast<void*>(subject), kLookupKey,
        frame_word_at(frame, kFrameLookupOutDisplacement));

    // 005774a2  MOV EAX,DWORD PTR [ESP+0x18]
    // 005774a6  ADD ESP,0xc
    //
    // EAX is reloaded from the frame word, so the callee's AL is DISCARDED. The
    // model discards it too; the test drives the lookup to return false while
    // still writing a non-zero word (the fourth registration must then happen)
    // and to return true while writing zero (it must not).
    static_cast<void>(reported);

    // 005774a9  TEST EAX,EAX
    // 005774ab  JE 0x005774d1
    //
    // The branch is on the OUT WORD, not on the callee's bool. A zero instance
    // id skips the fourth registration and nothing else -- the second member
    // swap above has already happened and is NOT undone.
    const Word instance = *frame_word_at(frame, kFrameLookupOutDisplacement);
    if (instance != 0u) {
      // 005774ad  MOV ECX,DWORD PTR [ESI+0x30c]
      //
      // The FOURTH registration goes to the SECOND member, not the first, and
      // the receiver is re-read from the frame again.
      //
      // 005774b3  MOV DWORD PTR [ESP+0x28],EAX
      // 005774b7  LEA EAX,[ESP+0x28]
      // 005774bb  PUSH EAX
      // 005774bc  MOV DWORD PTR [ESP+0x30],0x510a95b
      // 005774c4  MOV DWORD PTR [ESP+0x34],0x40464100
      // 005774cc  CALL 0x007b1e90
      //
      // +0x28 IS THE THIRD RECORD'S ADDRESS. This fourth registration overwrites
      // the third record's three words in place; it does not get a new frame
      // slot. The first two words of the fourth record are the instance id and
      // the same 0x510a95b the third record's middle word held, so the third
      // record is destroyed by the time this body returns. That is not a
      // reconstruction artefact -- it is what the two LEAs at 0x005773c8 and
      // 0x005774b7 say -- and the model keeps it by having ONE array and one
      // displacement constant, which is also what the test's aliasing check
      // reads.
      *frame_word_at(frame, kFrameRecordFourDisplacement + kRecordIdDisplacement) = instance;
      *frame_word_at(frame, kFrameRecordFourDisplacement + kRecordMiddleDisplacement) =
          kRecordMiddleWord;
      *frame_word_at(frame, kFrameRecordFourDisplacement + kRecordTailDisplacement) = kRecordTailWord;
      record_register_007b1e90(reinterpret_cast<void*>(*target_member),
                               reinterpret_cast<const PropertyRecord*>(
                                   frame_word_at(frame, kFrameRecordFourDisplacement)));
    }
  }

  // 005774d1  MOV ECX,DWORD PTR [ESP+0x38]
  // 005774d5  TEST ECX,ECX
  // 005774d7  JE 0x005774e0
  // 005774d9  MOV EDX,DWORD PTR [ECX]        <- level one
  // 005774db  MOV EAX,DWORD PTR [EDX+0x4]    <- level two: slot +0x4
  // 005774de  CALL EAX
  //
  // The single tail release, on the query's answer, and it is reached from three
  // different places: the query answering false (0x0057742d), the instance id
  // being zero (0x005774ab) and falling out of the hit arm. A query that never
  // ran -- the sentinel arm -- never reaches it, and a query that answered false
  // still does. The guard is on the WORD, so a query that wrote a null answer
  // releases nothing.
  if (handle != 0u) {
    const ReleaseSlot tail = reinterpret_cast<ReleaseSlot>(
        vtable_word_at(reinterpret_cast<void*>(handle), kSlotReleaseDisplacement));
    tail(reinterpret_cast<void*>(handle));
  }

  // 005774e0  POP EDI
  // 005774e1  POP ESI
  // 005774e2  POP EBX
  // 005774e3  ADD ESP,0x28
  // 005774e6  RET 0x4
  //
  // Three saved registers and forty bytes of frame, then CALLEE-owned cleanup of
  // the one argument word -- `C2 04 00`, not a bare RET, which is what rules out
  // cdecl for this body. EAX is not written on any path, which is why the return
  // type is void and the test asserts nothing about it.
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00577310
