// Reconstruction of FUN_00c12310 @ 0x00c12310 (SporeApp.exe 3.1.0.22).
//
// The whole of the evidence for this file is the 87-instruction listing at
// 0x00c12310..0x00c123e8, quoted instruction by instruction below, and the
// reasoning that connects it lives in create_cache_object_00c12310.hpp. Read
// that header first: it is where the ABI, the receiver bounds, the two tables
// and the three cleanup conventions are each tied to the bytes that fix them.
//
// WHAT THIS BODY IS, IN THE ONLY TERMS THE LISTING SUPPORTS: it is handed a
// receiver, three stack words and a one-byte flag; it reads a pointer out of
// the receiver, hands that pointer and one of its arguments to a helper that
// may write the argument back, asks a manager for a result, bails out twice,
// and otherwise walks six virtual slots of the receiver's own pointer in a
// fixed order, then calls a second helper and conditionally caches the created
// object in the receiver. Every call below is a `CALL` in the listing and
// every condition is a `JZ`/`JNZ` in the listing.
//
// Every displacement is written here as the LITERAL the listing prints, and
// each literal is tied to the header's named constant by a `static_assert` in
// the same statement, so the two cannot drift apart. The literals are the
// point: they are the machine's own spellings and a reviewer can read them
// against the quoted instruction without translating anything.

#include "create_cache_object_00c12310.hpp"

namespace openspore::reconstruction::pkg_00c12310_create_cache_object {

// The three stack words, named for the roles the listing gives them and for
// nothing more. `argument0` is the word read twice before any call (EBP at
// 0x00c12324, EDI at 0x00c12342) and once after (EBP at 0x00c123b1);
// `argument1` is the word read once, late, at 0x00c123c5; `flag` is the byte
// compared at 0x00c1237d. The header fixes each one's entry_ESP offset.
extern "C" OpaqueCreated* PKG_00C12310_THISCALL create_cached_object_00c12310(
    OpaqueOwner* self, Word argument0, Word argument1, std::uint8_t flag) {
  // Each literal below is the DISPLACEMENT the listing prints, not an address.
  // The instruction each one belongs to is named in the message with a BARE
  // eight-hex token and no `0x` prefix, because a message string is a live
  // expression operand and validate._hex_tokens scans it: a `0x`-prefixed
  // address in a message would be read as a constant the source states, and no
  // listing contains one (docs/tooling/reconstruction-failure-modes.md,
  // rule 8). The full addresses are in the comments above each block, where
  // comments are stripped before the check runs.
  static_assert(kReceiverPrototyperDisplacement == 0xb54,
                "the word the listing compares against zero at c12318");
  static_assert(kReceiverCachedObjectDisplacement == 0xe88,
                "the word the listing stores into at c123db");
  static_assert(kManagerResultFlagDisplacement == 0x1c,
                "the byte the listing reads its flag from at c123d5");
  static_assert(kStackCleanupBytes == 0x0c, "the terminator at c123e7");

  // 0x00c12314  8b f1           MOV ESI,ECX                  receiver into ESI
  // 0x00c12316  33 ff           XOR EDI,EDI                  EDI = 0
  // 0x00c12318  39 be 54 0b 00 00
  //                            CMP dword ptr [ESI + 0xb54],EDI
  // 0x00c1231e  0f 84 bd 00 00 00
  //                            JZ 0x00c123e1                -> EAX = EDI = 0
  //
  // The one guard the body has on entry, and it is a NULL test on the
  // receiver's own pointer, not on any argument. The listing loads that word
  // here and the dispatch block reads it again, so the test is on the value
  // the dispatch would use.
  if (*word_at(self, 0xb54) == 0u) {
    // 0x00c123e1  8b c7        MOV EAX,EDI                 EAX = 0
    // 0x00c123e3..e6            POP EDI/ESI/EBP/EBX
    // 0x00c123e7  c2 0c 00     RET 0xc
    return nullptr;
  }

  // 0x00c12324  8b 6c 24 14   MOV EBP,dword ptr [ESP + 0x14]  argument0, once
  // 0x00c12328  8d 44 24 14   LEA EAX,[ESP + 0x14]            &argument0
  // 0x00c1232c  50            PUSH EAX
  // 0x00c1232d  55            PUSH EBP
  // 0x00c1232e  56            PUSH ESI
  // 0x00c1232f  89 6c 24 20   MOV dword ptr [ESP + 0x20],EBP
  //
  // The `MOV [ESP+0x20],EBP` is worth reading rather than skipping: with
  // three pushes outstanding ESP is entry_ESP-0x1c, so [ESP+0x20] is
  // entry_ESP+0x4 -- the argument's OWN slot. The instruction stores the value
  // it just read back over the slot it was read from, and the `LEA` hands the
  // callee the address of that same slot. So the third argument is an
  // out-parameter ALIASING the first argument, and the store establishes the
  // callee's incoming state rather than introducing a fourth datum. This
  // package therefore models it as a local the callee may write, not as a
  // separate variable: `resolved` starts as `argument0`.
  Word resolved = argument0;
  // 0x00c12333  e8 78 a2 ff ff  CALL 0x00c0c5b0
  // 0x00c12338  83 c4 0c        ADD ESP,0xc       caller pops three words
  resolve_prototype_00c0c5b0(self, argument0, &resolved);

  // 0x00c1233b  e8 e0 a7 a6 ff  CALL 0x0067cb20   no pushes, nothing added
  OpaqueManager* const manager = manager_root_0067cb20();

  // 0x00c12340  8b 10        MOV EDX,dword ptr [EAX]         the manager's
  // table 0x00c12342  8b 7c 24 14  MOV EDI,dword ptr [ESP + 0x14]  argument0,
  // AGAIN 0x00c12346  8b c8        MOV ECX,EAX                    ECX = manager
  // 0x00c12348  8b 42 40     MOV EAX,dword ptr [EDX + 0x40]
  // 0x00c1234b  57           PUSH EDI
  // 0x00c1234c  ff d0        CALL EAX
  // 0x00c1234e  8b d8        MOV EBX,EAX                    EBX =
  // manager_result 0x00c12350  85 db        TEST EBX,EBX 0x00c12352  75 07 JNZ
  // 0x00c1235b
  //
  // The second `MOV ...,dword ptr [ESP + 0x14]` is a RE-READ of the argument
  // slot and it is not redundant: 0x00c0c5b0 was handed that slot's address
  // three instructions earlier and may have written through it. The manager's
  // +0x40 therefore receives the RESOLVED value, while the prototyper's +0x40
  // further down receives the ORIGINAL `argument0` that EBP has been holding
  // since 0x00c12324. Those are the same word in this reconstruction -- the
  // model test proves it by having the helper write a different value and
  // showing that the manager sees the new one and the prototyper the old one.
  OpaqueManagerResult* const manager_result =
      table_of<OpaqueManagerVTable>(manager)->slot_40(manager, resolved);
  if (manager_result == nullptr) {
    // 0x00c12354..e6   POP EDI/ESI/EBP/EBX
    // 0x00c12358  c2 0c 00     RET 0xc
    //
    // EAX is the null the +0x40 call just returned, so this exit returns 0
    // with no further write: no store, no third callee, receiver untouched.
    // The model test diffs the whole object to say so.
    return nullptr;
  }

  // 0x00c1235b  8b 8e 54 0b 00 00  MOV ECX,dword ptr [ESI + 0xb54]
  // 0x00c12361  8b 11              MOV EDX,dword ptr [ECX]
  // 0x00c12363  8b 42 08           MOV EAX,dword ptr [EDX + 0x8]
  // 0x00c12366  6a 00              PUSH 0x0
  // 0x00c12368  57                 PUSH EDI
  // 0x00c12369  ff d0              CALL EAX
  // 0x00c1236b  8b 8e 54 0b 00 00  MOV ECX,dword ptr [ESI + 0xb54]
  // 0x00c12371  8b 11              MOV EDX,dword ptr [ECX]
  // 0x00c12373  8b f8              MOV EDI,EAX    EDI = the created object
  //
  // Six of the seven dispatches RE-READ receiver+0xb54 and the table word
  // before every single call (0x5b/0x61, 0x6b/0x71, 0x84/0x8c, 0x98/0x9e,
  // 0xa6/0xac, 0xb5/0xbb). The listing does not hoist them and this package
  // does not either: each dispatch re-reads, so a callee that replaced the
  // receiver's pointer would change which table the NEXT call goes through.
  // The model test plants a decoy prototyper and shows the re-read is what
  // picks it up, which a hoisted read could not do.
  OpaquePrototyper* const prototyper_08 =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  OpaqueCreated* const created = table_of<OpaquePrototyperVTable>(prototyper_08)
                                     ->slot_08(prototyper_08, resolved, 0u);

  // 0x00c12375  8b 42 0c        MOV EAX,dword ptr [EDX + 0xc]
  // 0x00c12378  6a 01           PUSH 0x1
  // 0x00c1237a  57              PUSH EDI
  // 0x00c1237b  ff d0           CALL EAX
  OpaquePrototyper* const prototyper_0c =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  table_of<OpaquePrototyperVTable>(prototyper_0c)
      ->slot_0c(prototyper_0c, created, 1u);

  // 0x00c1237d  80 7c 24 1c 00  CMP byte ptr [ESP + 0x1c],0x0
  // 0x00c12382  74 14              JZ 0x00c12398
  //
  // A ONE-BYTE compare of the third stack word, against zero. The width is
  // part of the claim: a reconstruction that read four bytes here would be
  // reading a byte the machine never reads, and one that tested the word for
  // truthiness would take the branch on a different set of inputs.
  if (flag != 0u) {
    // 0x00c12384  8b 8e 54 0b 00 00  MOV ECX,dword ptr [ESI + 0xb54]
    // 0x00c1238a  d9 ee              FLDZ                  push 0.0f
    // 0x00c1238c  8b 11              MOV EDX,dword ptr [ECX]
    // 0x00c1238e  8b 42 14           MOV EAX,dword ptr [EDX + 0x14]
    // 0x00c12391  51                 PUSH ECX             scratch word
    // 0x00c12392  d9 1c 24           FSTP float ptr [ESP] 0.0f there, x87
    // popped 0x00c12395  57                 PUSH EDI 0x00c12396  ff d0 CALL EAX
    //
    // The FLDZ/FSTP pair IS the argument: a 4-byte float zero. The `PUSH ECX`
    // word the FSTP overwrites is not an argument, and the x87 stack is empty
    // again afterwards -- which is why this body's return value travels in EAX
    // and not in ST0 (see the header's note 4). `FSTP float ptr` says float and
    // not double, so the argument is 4 bytes wide.
    OpaquePrototyper* const prototyper_14 =
        reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
    const float zero = 0.0f;
    static_assert(sizeof(zero) == sizeof(kZeroFloatBits),
                  "the FSTP at c12392 writes 4 bytes, not 8");
    table_of<OpaquePrototyperVTable>(prototyper_14)
        ->slot_14(prototyper_14, created, zero);
  }

  // 0x00c12398  8b 8e 54 0b 00 00  MOV ECX,dword ptr [ESI + 0xb54]
  // 0x00c1239e  8b 11              MOV EDX,dword ptr [ECX]
  // 0x00c123a0  8b 42 18           MOV EAX,dword ptr [EDX + 0x18]
  // 0x00c123a3  57                 PUSH EDI
  // 0x00c123a4  ff d0              CALL EAX
  OpaquePrototyper* const prototyper_18 =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  table_of<OpaquePrototyperVTable>(prototyper_18)
      ->slot_18(prototyper_18, created);

  // 0x00c123a6  8b 8e 54 0b 00 00  MOV ECX,dword ptr [ESI + 0xb54]
  // 0x00c123ac  8b 11              MOV EDX,dword ptr [ECX]
  // 0x00c123ae  8b 42 40           MOV EAX,dword ptr [EDX + 0x40]
  // 0x00c123b1  55                 PUSH EBP    <-- argument0, the ORIGINAL
  // 0x00c123b2  57                 PUSH EDI
  // 0x00c123b3  ff d0              CALL EAX
  //
  // EBP, not EDI. The push is the word read at 0x00c12324, BEFORE 0x00c0c5b0
  // could have written through the aliasing out-parameter, while the manager's
  // +0x40 and every other prototyper dispatch used the re-read EDI. So +0x40
  // is reached with the pre-call value and the rest with the post-call value.
  OpaquePrototyper* const prototyper_40 =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  table_of<OpaquePrototyperVTable>(prototyper_40)
      ->slot_40(prototyper_40, created, argument0);

  // 0x00c123b5  8b 8e 54 0b 00 00  MOV ECX,dword ptr [ESI + 0xb54]
  // 0x00c123bb  8b 11              MOV EDX,dword ptr [ECX]
  // 0x00c123bd  8b 42 3c           MOV EAX,dword ptr [EDX + 0x3c]
  // 0x00c123c0  6a 00              PUSH 0x0
  // 0x00c123c2  57                 PUSH EDI
  // 0x00c123c3  ff d0              CALL EAX
  //
  // The +0x3c slot comes AFTER the +0x40 one, not before: the listing's slot
  // order is 0x08, 0x0c, [0x14], 0x18, 0x40, 0x3c, and the model test pins that
  // order as a sequence, so a reconstruction that sorted the offsets would
  // fail even though every offset it used would individually be right.
  OpaquePrototyper* const prototyper_3c =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  table_of<OpaquePrototyperVTable>(prototyper_3c)
      ->slot_3c(prototyper_3c, created, 0u);

  // 0x00c123c5  8b 4c 24 18     MOV ECX,dword ptr [ESP + 0x18]  argument1
  // 0x00c123c9  53              PUSH EBX                      manager_result
  // 0x00c123ca  51              PUSH ECX                      argument1
  // 0x00c123cb  57              PUSH EDI                      created
  // 0x00c123cc  56              PUSH ESI                      this
  // 0x00c123cd  e8 7e de ff ff  CALL 0x00c10250
  // 0x00c123d2  83 c4 10        ADD ESP,0x10    caller pops four words
  attach_created_object_00c10250(self, created, argument1, manager_result);

  // 0x00c123d5  80 7b 1c 01     CMP byte ptr [EBX + 0x1c],0x1
  // 0x00c123d9  74 06              JZ 0x00c123e1
  // 0x00c123db  89 be 88 0e 00 00
  //                            MOV dword ptr [ESI + 0xe88],EDI
  // 0x00c123e1  8b c7           MOV EAX,EDI
  //
  // The one-byte flag is on the MANAGER'S RESULT, one level out from anything
  // the receiver owns, and the test is against ONE, not against zero: the
  // store happens for every value except 1. Inverting that is the easiest
  // thing to get wrong here, so the model test pins both directions.
  if (*byte_at(manager_result, 0x1c) != 1u) {
    *word_at(self, 0xe88) = pointer_word(created);
  }

  // 0x00c123e1  8b c7        MOV EAX,EDI      EAX = the created object
  // 0x00c123e3  5f           POP EDI
  // 0x00c123e4  5e           POP ESI
  // 0x00c123e5  5d           POP EBP
  // 0x00c123e6  5b           POP EBX
  // 0x00c123e7  c2 0c 00     RET 0xc
  //
  // The body returns the object it created, and returns it UNCONDITIONALLY on
  // this path: the +0xe88 store above is conditional but the EAX materialising
  // is not, so a receiver whose manager result carries the flag 1 still gets
  // the object back and simply does not get it cached.
  return created;
}

}  // namespace openspore::reconstruction::pkg_00c12310_create_cache_object
