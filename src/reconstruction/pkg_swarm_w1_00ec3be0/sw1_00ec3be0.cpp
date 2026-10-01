// PKG-SWARM-W1-00EC3BE0 -- VA 0x00ec3be0
// FUN_00ec3be0 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22), the Sporepedia-online
// property handler at the last slot of the table at 0x014890f4.
//
// THE COMPLETE BODY: 58 instructions, 0x00ec3be0..0x00ec3c90 inclusive,
// 177 bytes (ghidra_function.body_start 0x00ec3be0, body_end 0x00ec3c91, size
// 177). The listing below was re-derived from the image bytes for this package
// with `objdump -D -b binary -m i386 -M intel` over the 0xb1 bytes at the file
// offset for this VA. It reproduces the committed Ghidra listing instruction for
// instruction, at the same addresses and with the same lengths, so nothing in
// this model rests on a re-parse. The six bytes after the last RET are INT3
// padding, not part of the body.
//
//   00ec3be0  56                    PUSH ESI
//   00ec3be1  8B 74 24 08           MOV ESI,[ESP+0x8]
//   00ec3be5  57                    PUSH EDI
//   00ec3be6  56                    PUSH ESI
//   00ec3be7  8B F9                 MOV EDI,ECX
//   00ec3be9  E8 42 E9 77 FF        CALL 0x00642530
//   00ec3bee  8B 06                 MOV EAX,[ESI]
//   00ec3bf0  3D A7 84 35 5A        CMP EAX,0x5a3584a7
//   00ec3bf5  77 3D                 JA 0x00ec3c34
//   00ec3bf7  74 23                 JZ 0x00ec3c1c
//   00ec3bf9  3D C8 AF E8 15        CMP EAX,0x15e8afc8
//   00ec3bfe  0F 85 88 00 00 00     JNZ 0x00ec3c8c
//   00ec3c04  81 7E 04 5D A7 E1 02  CMP DWORD PTR [ESI+0x4],0x2e1a75d
//   00ec3c0b  75 7F                 JNZ 0x00ec3c8c
//   00ec3c0d  83 7E 08 01           CMP DWORD PTR [ESI+0x8],0x1
//   00ec3c11  0F 94 C0              SETZ AL
//   00ec3c14  88 47 78              MOV BYTE PTR [EDI+0x78],AL
//   00ec3c17  5F                    POP EDI
//   00ec3c18  5E                    POP ESI
//   00ec3c19  C2 04 00              RET 0x4
//   00ec3c1c  81 7E 04 5D A7 E1 02  CMP DWORD PTR [ESI+0x4],0x2e1a75d
//   00ec3c23  75 67                 JNZ 0x00ec3c8c
//   00ec3c25  83 7E 08 01           CMP DWORD PTR [ESI+0x8],0x1
//   00ec3c29  0F 94 C1              SETZ CL
//   00ec3c2c  88 4F 79              MOV BYTE PTR [EDI+0x79],CL
//   00ec3c2f  5F                    POP EDI
//   00ec3c30  5E                    POP ESI
//   00ec3c31  C2 04 00              RET 0x4
//   00ec3c34  3D 14 BA 1F B9        CMP EAX,0xb91fba14
//   00ec3c39  74 3E                 JZ 0x00ec3c79
//   00ec3c3b  3D 35 5E 2F D2        CMP EAX,0xd22f5e35
//   00ec3c40  74 1F                 JZ 0x00ec3c61
//   00ec3c42  3D DD 75 46 DB        CMP EAX,0xdb4675dd
//   00ec3c47  75 43                 JNZ 0x00ec3c8c
//   00ec3c49  81 7E 04 5D A7 E1 02  CMP DWORD PTR [ESI+0x4],0x2e1a75d
//   00ec3c50  75 3A                 JNZ 0x00ec3c8c
//   00ec3c52  83 7E 08 01           CMP DWORD PTR [ESI+0x8],0x1
//   00ec3c56  0F 94 C2              SETZ DL
//   00ec3c59  88 57 7C              MOV BYTE PTR [EDI+0x7c],DL
//   00ec3c5c  5F                    POP EDI
//   00ec3c5d  5E                    POP ESI
//   00ec3c5e  C2 04 00              RET 0x4
//   00ec3c61  81 7E 04 5D A7 E1 02  CMP DWORD PTR [ESI+0x4],0x2e1a75d
//   00ec3c68  75 22                 JNZ 0x00ec3c8c
//   00ec3c6a  83 7E 08 01           CMP DWORD PTR [ESI+0x8],0x1
//   00ec3c6e  0F 94 C0              SETZ AL
//   00ec3c71  88 47 7B              MOV BYTE PTR [EDI+0x7b],AL
//   00ec3c74  5F                    POP EDI
//   00ec3c75  5E                    POP ESI
//   00ec3c76  C2 04 00              RET 0x4
//   00ec3c79  81 7E 04 5D A7 E1 02  CMP DWORD PTR [ESI+0x4],0x2e1a75d
//   00ec3c80  75 0A                 JNZ 0x00ec3c8c
//   00ec3c82  83 7E 08 01           CMP DWORD PTR [ESI+0x8],0x1
//   00ec3c86  0F 94 C1              SETZ CL
//   00ec3c89  88 4F 7A              MOV BYTE PTR [EDI+0x7a],CL
//   00ec3c8c  5F                    POP EDI
//   00ec3c8d  5E                    POP ESI
//   00ec3c8e  C2 04 00              RET 0x4
//
// WHAT THE BODY IS. A five-way property handler. It is handed a pointer to a
// 12-byte key record, delegates the record once to 0x00642530, and then matches
// the record's first word against five hashed key ids. On a match it checks the
// record's second word against the single type hash 0x2e1a75d and writes the
// boolean `(record's third word == 1)` into one byte of the receiver. Every one
// of those five bytes is distinct, so the five ids are five separate flags. On
// any other key id, or on a type-hash miss, the body returns having written
// nothing.
//
// THE DISPATCH IS A SIGNED-LOOKING TREE OVER UNSIGNED VALUES, and that is the
// single most fragile thing in it. 0x00ec3bf5 is `JA` (opcode 0x77), an UNSIGNED
// above, and the pivot 0x5a3584a7 is a POSITIVE value while three of the five
// key ids (0xb91fba14, 0xd22f5e35, 0xdb4675dd) have the high bit set. Read as
// SIGNED, all three of those ids compare as negative, fall below the pivot, and
// the entire high group becomes dead: two of the five flags would be
// unreachable and the other three would take the wrong arm. Nothing in the
// disassembly says "unsigned" in words -- it is the opcode.
//
// The two halves are exactly a binary search tree on the key id, and the two
// constants that fix that are the pivot at 0x00ec3bf0 and the three-way test at
// 0x00ec3c34..0x00ec3c42. 0x15e8afc8 and 0x5a3584a7 are both below the pivot
// unsigned and are tested in the low half (0x00ec3bf7 JZ, then 0x00ec3bf9
// CMP); the other three are above it and are tested in the high half. The model
// reproduces that tree, including the fact that the low half tests the EQUAL
// case first and only then the other member.
//
// THE FIVE STORES DIFFER ONLY IN THEIR DESTINATION AND IN WHICH REGISTER CARRIES
// THE SETZ RESULT: AL for 0x15e8afc8 and 0xd22f5e35, CL for 0x5a3584a7 and
// 0xb91fba14, DL for 0xdb4675dd. The register choice is not a semantic fact --
// the byte stored is the SETZ result either way -- but it is reproduced in the
// per-arm comments so a reader can match arm to arm against the bytes.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and none of the
// 58 instructions is a register- or memory-operand transfer. The one reference
// to this VA in the binary is a DATA reference: the xref from 0x01489144 is this
// body's entry point stored at the last word of a 21-word code-pointer run whose
// first word is 0x00641400 -- the very address the analogue record for
// 0x00641400 names, on the same table. So the body is a member of a class's
// table and this reconstruction deliberately models none of that: the body
// contains no dispatch and never reads the receiver's +0x00, so no slot boundary
// and no dispatch member is declared. See the header's note (2).
//
// GLOBALS: none. No instruction in the body names a data-segment address, and
// the only absolute operands are the call target and the five conditional
// branch targets, all of them code.

#include "sw1_00ec3be0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00ec3be0 {

extern "C" void SW1_00EC3BE0_THISCALL re_00ec3be0(
    SporepediaOnlineAsset* receiver, const PropertyKeyRecord* key) {
  // 00ec3be0  PUSH ESI
  // 00ec3be1  MOV ESI,[ESP+0x8]
  //
  // With ESP one push below the entry value, [ESP+0x8] is the single ordinary
  // stack word: entry_ESP+0x4. The machine parse reports local_extent 0 and
  // esp_unresolved false, so this is the only stack slot the body ever touches
  // and the one `RET 0x4` consumes.
  //
  // 00ec3be5  PUSH EDI
  // 00ec3be6  PUSH ESI
  // 00ec3be7  MOV EDI,ECX
  //
  // The receiver is aliased into EDI and every receiver access in the body goes
  // through that alias -- which is why the machine-derived receiver record names
  // ECX with shape R-ALIAS rather than reporting ECX's own operands. ECX is
  // never read again after this instruction: the call takes the receiver through
  // ECX implicitly, and the five stores go through EDI.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00ec3be9  CALL 0x00642530
  //
  // One direct call, made UNCONDITIONALLY and BEFORE anything is read: no branch
  // precedes it, and every one of the ten terminators is downstream of it. The
  // argument is the key pointer that was pushed at 00ec3be6, and the receiver
  // travels in ECX, still holding what the two pushes left there.
  //
  // The callee's own 160 bytes (quoted in the header) show it dereferencing that
  // same pointer as a 12-byte record, comparing its +0x04 against the same type
  // hash and storing its +0x08 into the receiver -- so this is a sibling handler
  // for the same property vocabulary, and this body is the one that owns the
  // five boolean keys. Its EAX return is not read: the very next instruction
  // (00ec3bee) overwrites EAX from memory without looking at it. The model
  // discards it explicitly so the test can plant a poison return and prove the
  // discard is real.
  (void)sporepedia_property_apply_00642530(receiver, key);

  // 00ec3bee  MOV EAX,[ESI]
  //
  // The key id, read as a VALUE out of the record the caller handed over -- one
  // level of indirection, not two. There is no pointer stored in the record and
  // no pointer in the receiver: the receiver is never read at all on any path of
  // this body, and the five things the machine-derived receiver record lists
  // (0x78..0x7c, written_through 5) are all writes.
  const Word id = *word_at(key, kRecordIdDisplacement);

  // 00ec3bf0  CMP EAX,0x5a3584a7
  // 00ec3bf5  JA  0x00ec3c34
  //
  // The UNSIGNED above that splits the tree -- see the header comment on why this
  // one instruction is load-bearing. The high half is the three ids whose high
  // bit is set, and the low half is the two that are not.
  if (id > kPivotId_5a3584a7) {
    // 00ec3c34  CMP EAX,0xb91fba14
    // 00ec3c39  JZ  0x00ec3c79
    if (id == kKeyId_b91fba14) {
      // 00ec3c79  CMP DWORD PTR [ESI+0x4],0x2e1a75d
      // 00ec3c80  JNZ 0x00ec3c8c
      //
      // The type-hash guard every arm opens with. A different type hash is not
      // this body's key and nothing is written: the record is left entirely to
      // the callee that was already given it.
      if (*word_at(key, kRecordTypeDisplacement) != kTypeHash) {
        return;
      }
      // 00ec3c82  CMP DWORD PTR [ESI+0x8],0x1
      // 00ec3c86  SETZ CL
      // 00ec3c89  MOV BYTE PTR [EDI+0x7a],CL
      //
      // The value test is an EQUALITY against 1, not a non-zero test. Value 0
      // and value 2 both store 0, and only 1 stores 1; SETZ is what makes that
      // so, and it is why the model writes a boolean rather than storing the
      // value word itself.
      self[0x7a] =
          (*word_at(key, kRecordValueDisplacement) == 1u) ? std::uint8_t{1} : std::uint8_t{0};
      // 00ec3c8c  POP EDI; POP ESI; RET 0x4
      return;
    }

    // 00ec3c3b  CMP EAX,0xd22f5e35
    // 00ec3c40  JZ  0x00ec3c61
    if (id == kKeyId_d22f5e35) {
      // 00ec3c61  CMP DWORD PTR [ESI+0x4],0x2e1a75d
      // 00ec3c68  JNZ 0x00ec3c8c
      if (*word_at(key, kRecordTypeDisplacement) != kTypeHash) {
        return;
      }
      // 00ec3c6a  CMP DWORD PTR [ESI+0x8],0x1
      // 00ec3c6e  SETZ AL
      // 00ec3c71  MOV BYTE PTR [EDI+0x7b],AL
      self[0x7b] =
          (*word_at(key, kRecordValueDisplacement) == 1u) ? std::uint8_t{1} : std::uint8_t{0};
      // 00ec3c8c
      return;
    }

    // 00ec3c42  CMP EAX,0xdb4675dd
    // 00ec3c47  JNZ 0x00ec3c8c
    //
    // The last test of the high half. A miss here is the only miss that falls
    // THROUGH to the shared epilogue rather than jumping to it, which is why
    // this arm is the one the model ends with an unconditional return.
    if (id == kKeyId_db4675dd) {
      // 00ec3c49  CMP DWORD PTR [ESI+0x4],0x2e1a75d
      // 00ec3c50  JNZ 0x00ec3c8c
      if (*word_at(key, kRecordTypeDisplacement) != kTypeHash) {
        return;
      }
      // 00ec3c52  CMP DWORD PTR [ESI+0x8],0x1
      // 00ec3c56  SETZ DL
      // 00ec3c59  MOV BYTE PTR [EDI+0x7c],DL
      self[0x7c] =
          (*word_at(key, kRecordValueDisplacement) == 1u) ? std::uint8_t{1} : std::uint8_t{0};
      // 00ec3c5c
      return;
    }
    // 00ec3c47  JNZ 0x00ec3c8c -- an id above the pivot that is none of the
    // three. Nothing is written and the body returns.
    return;
  }

  // 00ec3bf7  JZ 0x00ec3c1c
  //
  // Reached only when the JA at 00ec3bf5 did not fire, i.e. id <= the pivot
  // UNSIGNED. The low half tests the pivot's own value first and the other low id
  // second, in that order; the model keeps the order so the arm-to-arm
  // correspondence with the bytes is checkable line by line.
  if (id == kKeyId_5a3584a7) {
    // 00ec3c1c  CMP DWORD PTR [ESI+0x4],0x2e1a75d
    // 00ec3c23  JNZ 0x00ec3c8c
    if (*word_at(key, kRecordTypeDisplacement) != kTypeHash) {
      return;
    }
    // 00ec3c25  CMP DWORD PTR [ESI+0x8],0x1
    // 00ec3c29  SETZ CL
    // 00ec3c2c  MOV BYTE PTR [EDI+0x79],CL
    self[0x79] =
        (*word_at(key, kRecordValueDisplacement) == 1u) ? std::uint8_t{1} : std::uint8_t{0};
    // 00ec3c2f
    return;
  }

  // 00ec3bf9  CMP EAX,0x15e8afc8
  // 00ec3bfe  JNZ 0x00ec3c8c
  //
  // The last test of the whole dispatch, and the only one the model inverts,
  // because the machine's polarity here is a JNZ to the epilogue: any id that is
  // not 0x15e8afc8 leaves the body having written nothing.
  if (id != kKeyId_15e8afc8) {
    return;
  }

  // 00ec3c04  CMP DWORD PTR [ESI+0x4],0x2e1a75d
  // 00ec3c0b  JNZ 0x00ec3c8c
  if (*word_at(key, kRecordTypeDisplacement) != kTypeHash) {
    return;
  }
  // 00ec3c0d  CMP DWORD PTR [ESI+0x8],0x1
  // 00ec3c11  SETZ AL
  // 00ec3c14  MOV BYTE PTR [EDI+0x78],AL
  //
  // The lowest of the five flags, and the one the layout makes notable: 0x78 is
  // the first of five CONSECUTIVE bytes, so the five key ids are five
  // neighbouring flag slots rather than five unrelated fields. That is an
  // observation about the displacements, not a claim that the object is a struct
  // of five bools -- nothing in this body establishes a type, a layout or a
  // meaning for any of them.
  self[0x78] =
      (*word_at(key, kRecordValueDisplacement) == 1u) ? std::uint8_t{1} : std::uint8_t{0};
  // 00ec3c17  POP EDI; POP ESI; RET 0x4
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00ec3be0
