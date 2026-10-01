// PKG-DFW-006A2E20 -- VA 0x006a2e20
// App::PropertyList::SetProperty (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 65 instructions, 0x006a2e20..0x006a2ee5 inclusive
// (ghidra_function.body_start 0x006a2e20, body_end 0x006a2ee7, size 200). Every
// line of the model below is annotated with the instruction it comes from.
//
// The listing this was written against was re-derived from the image bytes for
// this package rather than taken on trust, because three instruction boundaries
// in the committed Ghidra listing do not add up (0x006a2e74 is a 3-byte
// `CMP EAX,[EDI+0x1c]` = 3B 47 1C, and the two 11-byte MOV-immediate stores at
// 0x006a2eaa and 0x006a2ebc end at 0x006a2eb2 and 0x006a2ec7). objdump over the
// raw bytes gives the same 65 instructions at the same addresses with those
// three lengths corrected, and the call targets, branch targets and operand
// displacements are identical. Nothing in the model depends on the difference.
//
//   006a2e20  MOV EAX,FS:[0x0]
//   006a2e26  PUSH -0x1
//   006a2e28  PUSH 0x120d6b8
//   006a2e2d  PUSH EAX
//   006a2e2e  MOV dword ptr FS:[0x0],ESP
//   006a2e35  SUB ESP,0x20
//   006a2e38  PUSH EBX
//   006a2e39  PUSH ESI
//   006a2e3a  PUSH EDI
//   006a2e3b  MOV EDI,ECX
//   006a2e3d  MOVZX ECX,byte ptr [EDI + 0x2c]
//   006a2e41  MOV EBX,dword ptr [EDI + 0x1c]
//   006a2e44  MOV EAX,dword ptr [EDI + 0x18]
//   006a2e47  LEA ESI,[EDI + 0x18]
//   006a2e4a  PUSH ECX
//   006a2e4b  LEA EDX,[ESP + 0x40]
//   006a2e4f  PUSH EDX
//   006a2e50  PUSH EBX
//   006a2e51  PUSH EAX
//   006a2e52  CALL 0x00612db0
//   006a2e57  MOV EDX,dword ptr [ESP + 0x4c]
//   006a2e5b  ADD ESP,0x10
//   006a2e5e  CMP EAX,EBX
//   006a2e60  JZ 0x006a2e6d
//   006a2e62  CMP EDX,dword ptr [EAX]
//   006a2e64  JB 0x006a2e6d
//   006a2e66  LEA ECX,[EAX + 0x18]
//   006a2e69  CMP EAX,ECX
//   006a2e6b  JNZ 0x006a2e6f
//   006a2e6d  MOV EAX,EBX
//   006a2e6f  MOV ECX,dword ptr [ESP + 0x40]
//   006a2e73  PUSH ECX
//   006a2e74  CMP EAX,dword ptr [EDI + 0x1c]
//   006a2e77  JZ 0x006a2e83
//   006a2e79  LEA ECX,[EAX + 0x4]
//   006a2e7c  CALL 0x00542b80
//   006a2e81  JMP 0x006a2ed1
//   006a2e83  MOV dword ptr [ESP + 0x18],EDX
//   006a2e87  XOR EDX,EDX
//   006a2e89  XOR EAX,EAX
//   006a2e8b  LEA ECX,[ESP + 0x1c]
//   006a2e8f  MOV word ptr [ESP + 0x2c],DX
//   006a2e94  MOV word ptr [ESP + 0x2e],AX
//   006a2e99  CALL 0x00542b80
//   006a2e9e  LEA EDX,[ESP + 0x14]
//   006a2ea2  PUSH EDX
//   006a2ea3  LEA EAX,[ESP + 0x10]
//   006a2ea7  PUSH EAX
//   006a2ea8  MOV ECX,ESI
//   006a2eaa  MOV dword ptr [ESP + 0x3c],0x0
//   006a2eb2  CALL 0x006a2c50
//   006a2eb7  TEST byte ptr [ESP + 0x28],0x4
//   006a2ebc  MOV dword ptr [ESP + 0x34],0xffffffff
//   006a2ec4  JZ 0x006a2ed1
//   006a2ec6  PUSH 0x0
//   006a2ec8  LEA ECX,[ESP + 0x1c]
//   006a2ecc  CALL 0x0093db80
//   006a2ed1  INC dword ptr [EDI + 0x34]
//   006a2ed4  MOV ECX,dword ptr [ESP + 0x2c]
//   006a2ed8  POP EDI
//   006a2ed9  POP ESI
//   006a2eda  POP EBX
//   006a2edb  MOV dword ptr FS:[0x0],ECX
//   006a2ee2  ADD ESP,0x2c
//   006a2ee5  RET 0x8
//
// FRAME, resolved once against the entry ESP so every displacement below is a
// fact and not a guess. Entry ESP is 0 in the walk; `RET 0x8` then lands ESP at
// +12, which is entry+4 (return address) +8 (the two argument words), so the
// frame balances and the walk is right. Two independent checks agree: 0x006a2ed4
// reads [ESP+0x2c] = entry-12, which is exactly where `PUSH EAX` at 0x006a2e2d
// put the old FS:[0], so the epilogue restores the exception head it installed;
// and the three POPs plus `ADD ESP,0x2c` land back on entry ESP exactly.
//
//   entry-12  the saved FS:[0] (the SEH record's Next word); restored at 0x006a2edb
//   entry-8   the exception handler 0x0120d6b8, pushed at 0x006a2e28
//   entry-4   the 4-byte try-level word: -1 from `PUSH -0x1`, then 0 from
//             0x006a2eaa and 0xffffffff from 0x006a2ebc
//   entry-36  the seed entry's key dword, written at 0x006a2e83
//   entry-32  the seed entry's embedded 0x14-byte record: the destination of the
//             0x006a2e99 call and the receiver of the 0x006a2ecc call
//   entry-16  that record's word at +16 (the model's field_10), zeroed at
//             0x006a2e8f and tested at 0x006a2eb7
//   entry-14  that record's word at +18 (the model's field_12), zeroed at 0x006a2e94
//   entry-44  the 8-byte find-or-insert out record, the FIRST argument of 0x006a2c50
//   entry+4   the first ordinary argument: the ordered key. 0x006a2e4b takes its
//             address and 0x006a2e57 reads the word back through it.
//   entry+8   the second ordinary argument: the source record, pushed once at
//             0x006a2e73 and handed to 0x00542b80 on both arms.
//
// The last two rows are the ABI, derived and not assumed. 0x006a2e4b's
// `LEA EDX,[ESP + 0x40]` is taken with ESP at entry-60, so the pointer is
// entry+4; 0x006a2e57's `MOV EDX,[ESP + 0x4c]` is read with ESP at entry-72 and
// lands on the same entry+4; 0x006a2e6f's `MOV ECX,[ESP + 0x40]` is read with
// ESP back at entry-56 and lands on entry+8. The key argument is the one compared
// against each element's leading dword at 0x006a2e62 and stored as the seed key
// at 0x006a2e83, so it is the ordered key and not a count or an index. Ghidra's
// decompilation of this VA disagrees on the order (it passes its `propertyID` to
// 0x00542b80 and its `pValue` to 0x006a2c50) because it modelled the hidden
// receiver as a stack slot and shifted every argument up by one; the listing
// does not.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the 65
// instructions contain no register- or memory-operand transfer. The xref export
// carries a data-side reference from 0x01408834, which is 0x01408820 + 0x14 --
// this body is that table's fourteenth slot, confirmed by reading the table's own
// bytes -- but the body itself never reads a dispatch word, so no slot boundary
// is declared anywhere in this model and nothing at the receiver's +0x00 is named.
//
// GLOBALS: none. No instruction in the body names a data-segment address; the
// only absolute operand outside the body is the exception handler 0x0120d6b8
// pushed as an immediate, which is code, not a global.

#include "dfw_006a2e20_types.hpp"

namespace openspore::reconstruction::pkg_dfw_006a2e20 {
namespace {

// Model instrumentation, not a machine global: the 4-byte frame word at entry-4.
// See the header for why it is modelled at all. It has to live at namespace scope
// rather than as a local because nothing in the body reads it, and a local that
// is written and never read is a warning under -Wall.
std::int32_t g_try_level = -1;

}  // namespace

std::int32_t try_level_word() { return g_try_level; }

extern "C" void PKG_DFW_006A2E20_THISCALL dfw_property_set_006a2e20(
    PropertyList* receiver, Word key, Property* source) {
  // 006a2e3b  MOV EDI,ECX
  //
  // EDI becomes the receiver alias and every receiver access in the body goes
  // through it, including the last one at 0x006a2ed1. ECX is then reused as an
  // argument register, which is why nothing here reads a receiver field through
  // ECX and why the machine-derived receiver record reports register ECX with
  // shape R-ALIAS.
  //
  // The receiver is taken as a byte run and every access below is a
  // DISPLACEMENT into it. The record enumerates offsets=[0x18, 0x1c, 0x2c, 0x34]
  // and is bounds_only: it says where the body was seen reaching and not which
  // member is which, so no member name is written for any of them. The three
  // reads and the one write are all of it; nothing at +0x00..+0x17 or
  // +0x2d..+0x33 is touched.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 006a2e3d  MOVZX ECX,byte ptr [EDI + 0x2c]
  //
  // One byte, zero-extended, and that byte is receiver+0x2c. It is also the byte
  // the embedded array object reads at its own +0x14 (0x006a2c58
  // MOVZX EAX,BYTE PTR [ESI+0x14]), because the map starts at receiver+0x18 and
  // 0x006a2ea8 hands &self+0x18 to 0x006a2c50 as its receiver - 0x18 + 0x14 ==
  // 0x2c, which is the same byte and not two. The body pushes the widened word
  // at 0x006a2e4a as the last argument of the search.
  const Word mode = static_cast<Word>(self[0x2c]);

  // 006a2e41  MOV EBX,dword ptr [EDI + 0x1c]
  MapEntry* const end =
      *reinterpret_cast<MapEntry* const*>(self + 0x1c);

  // 006a2e44  MOV EAX,dword ptr [EDI + 0x18]
  MapEntry* const begin =
      *reinterpret_cast<MapEntry* const*>(self + 0x18);

  // 006a2e47  LEA ESI,[EDI + 0x18]
  //
  // ESI is the address of the embedded array object and nothing else: it is
  // moved into ECX at 0x006a2ea8 and is not touched again, so the body forms the
  // address once and reuses it. It is the SAME address 0x006a2e44 just read a
  // word out of; the two are not two fields.
  PropertyMap* const map = reinterpret_cast<PropertyMap*>(self + 0x18);

  // 006a2e4a  PUSH ECX          -- the mode word
  // 006a2e4b  LEA EDX,[ESP + 0x40]
  // 006a2e4f  PUSH EDX          -- &key
  // 006a2e50  PUSH EBX          -- end
  // 006a2e51  PUSH EAX          -- begin
  // 006a2e52  CALL 0x00612db0
  //
  // Four words, right to left, and the callee is cdecl: 0x006a2e5b drops all
  // sixteen bytes itself. The key goes over BY ADDRESS -- the machine hands the
  // search a pointer to its own first argument slot, and 0x00612db0 dereferences
  // that third parameter rather than taking the word -- so the model passes the
  // address of its key parameter, which is the same relationship.
  MapEntry* candidate =
      entry_array_lower_bound_00612db0(begin, end, &key, mode);

  // 006a2e5b  ADD ESP,0x10
  //
  // The cdecl cleanup. It is the first thing after the call, so nothing this
  // callee returned in EAX is disturbed by it.

  // 006a2e5e  CMP EAX,EBX
  // 006a2e60  JZ 0x006a2e6d
  //
  // The end-of-array case, tested before the key is looked at, so the short
  // circuit below is ordered the same way: when the search returned the end
  // pointer the leading dword of the end pointer is never read.
  //
  // 006a2e62  CMP EDX,dword ptr [EAX]
  // 006a2e64  JB 0x006a2e6d
  //
  // EDX is the key word re-read through the pointer at 0x006a2e57, and `CMP
  // a,b` / `JB` is the unsigned below test a < b, so the branch is taken exactly
  // when key < the element's leading dword. That word sits at the element's own
  // displacement 0 (kElementKeyDisplacement), fixed by 0x00612db0's stride-0x18
  // scan and by 0x006a2940's `MOV [EAX],ECX`. It is a real instruction: Ghidra
  // prints it as `JC`, the carry-set synonym for the `JB rel8` (opcode 0x72) the
  // bytes at 0x006a2e64 actually are. The committed listing's parse record
  // reports 65 of 65 consumed with 0 unparsed and degraded false, so nothing is
  // missing here and the instruction is modelled, not dropped.
  //
  // 006a2e66  LEA ECX,[EAX + 0x18]
  // 006a2e69  CMP EAX,ECX
  // 006a2e6b  JNZ 0x006a2e6f
  //
  // The one-past-the-end overflow probe the search leaves behind: ECX is EAX plus
  // the 0x18 element stride, so the compare can never be equal and the JNZ is
  // always taken. It is reproduced as the comment it is -- it makes no decision
  // and the model carries no branch for it.
  //
  // So the two tests above are the whole selection, and both land on the same
  // normalisation. The leading dword belongs to the ELEMENT, not to the receiver
  // and not to the map: a reconstruction that read it off either of those would
  // be reading a different object, and the model test drives exactly that
  // confusion.
  if (candidate == end ||
      key < *word_at(candidate, kElementKeyDisplacement)) {
    // 006a2e6d  MOV EAX,EBX
    candidate = end;
  }

  // 006a2e6f  MOV ECX,dword ptr [ESP + 0x40]
  //
  // The second ordinary argument, loaded into ECX and pushed at 0x006a2e73. Note
  // the displacement is the same 0x40 as 0x006a2e4b's LEA but the stack is 0x10
  // higher, which is what makes the two land on different argument slots
  // (entry-56 + 0x40 = entry+8, against entry-60 + 0x40 = entry+4).
  //
  // 006a2e73  PUSH ECX
  // 006a2e74  CMP EAX,dword ptr [EDI + 0x1c]
  // 006a2e77  JZ 0x006a2e83
  //
  // The arm test: the normalised candidate is compared against the array end one
  // more time, and equality means the key is not in the array.
  if (candidate == end) {
    // 006a2e83  MOV dword ptr [ESP + 0x18],EDX
    //
    // The seed entry's key dword, at entry-36. The seed entry is a 0x18-stride
    // element that lives in this frame only and is never itself stored into the
    // array by this body: 0x006a2c50 is the one that splices it in, and it does
    // so from the pointer this body passes. Only the key is written here, and it
    // is written BEFORE the record is assigned, which the model test checks by
    // having its 0x00542b80 observer read the seed's own leading dword.
    //
    // The seed is an 0x18-byte run rather than a MapEntry value: 0x18 is the
    // element stride every callee listing agrees on, and the body only ever
    // takes its address and writes two words inside it.
    std::uint8_t seed[0x18]{};
    *word_at(seed, kElementKeyDisplacement) = key;
    Property* const seed_record = reinterpret_cast<Property*>(
        word_at(seed, kElementRecordDisplacement));

    // 006a2e87  XOR EDX,EDX
    // 006a2e89  XOR EAX,EAX
    //
    // Zeroing two registers to supply the two zero words below. Neither register
    // survives; EDX's key copy is already stored and EAX was the dead candidate.
    //
    // 006a2e8b  LEA ECX,[ESP + 0x1c]
    //
    // ECX = entry-32, the seed entry's record, and it becomes the destination of
    // the assign call. entry-32 is entry-36 plus 4, so this is the record at the
    // entry's own +0x04 -- the same +0x04 the found arm addresses at 0x006a2e79
    // and the same +0x04 0x006a2940 gives a fresh element.
    //
    // 006a2e8f  MOV word ptr [ESP + 0x2c],DX     -> entry-16 = record + 16
    // 006a2e94  MOV word ptr [ESP + 0x2e],AX     -> entry-14 = record + 18
    //
    // The two words 0x00542b80 reads on its destination before it overwrites
    // them: +16 is the word it recomposes (it keeps the destination's own bit
    // 0x0002 and takes the rest from the source) and +18 is the word it compares
    // and then copies. Both are cleared first so the recomposition and the
    // comparison start from a known zero. Nothing in the 0x14-byte record between
    // +0x00 and +16 is touched by this body -- those eight bytes are left to
    // 0x00542b80, which is why the model's zero-initialised seed is a
    // determinism aid and not a claim about what the callee writes.
    *halfword_at(seed_record, kRecordFlagsDisplacement) = 0;
    *halfword_at(seed_record, kRecordTypeDisplacement) = 0;

    // 006a2e99  CALL 0x00542b80
    //
    // The assign, onto the frame's own seed record. The single argument is the
    // word pushed at 0x006a2e73, so this is the same source the found arm hands
    // over. The callee pops it (RET 0x4), which is what brings the stack back to
    // entry-56 for the next LEA.
    property_assign_00542b80(seed_record, source);

    // 006a2e9e  LEA EDX,[ESP + 0x14]
    // 006a2ea2  PUSH EDX
    // 006a2ea3  LEA EAX,[ESP + 0x10]
    // 006a2ea7  PUSH EAX
    // 006a2ea8  MOV ECX,ESI
    // 006a2eaa  MOV dword ptr [ESP + 0x3c],0x0
    // 006a2eb2  CALL 0x006a2c50
    //
    // The find-or-insert. Argument order comes from the callee's own frame reads
    // rather than from its decompilation: with ESP at entry-56 the first LEA gives
    // entry-36 (the seed entry) and after that push the second gives entry-44 (the
    // out record), and 0x006a2c78 reads the FIRST stack word as the record it
    // writes while 0x006a2c51 reads the SECOND as the entry it takes the key
    // from. So the seed entry is the second argument and the out record is the
    // first, and the model pushes them in that order.
    //
    // The store at 0x006a2eaa lands on entry-4 with ESP at entry-64, which is the
    // slot `PUSH -0x1` filled at 0x006a2e26: the try-level word of the exception
    // scope this prologue installed, set to 0 for the duration of the scope. The
    // matching 0xffffffff below closes it. Nothing in this body reads the word,
    // so the only thing about it a test can see is the order of the two stores
    // around this call, and that is what the model records.
    FindOrInsertResult result{};
    g_try_level = 0;
    property_map_find_or_insert_006a2c50(map, &result,
                                         reinterpret_cast<MapEntry*>(seed));

    // 006a2ebc  MOV dword ptr [ESP + 0x34],0xffffffff
    g_try_level = -1;

    // 006a2eb7  TEST byte ptr [ESP + 0x28],0x4
    //
    // Read before the store above, with ESP at entry-56, so entry-56 + 0x28 is
    // entry-16: the low byte of the very word 0x006a2e8f zeroed, which is the
    // seed record's +16. A byte test of bit 0x04 of that word is bit 0x0004 of
    // the 16-bit word, so the model tests the word.
    //
    // The value being tested is whatever 0x00542b80 left there, because the
    // assign above recomposed that word from the source record. The test is
    // therefore on the SOURCE's bit 0x0004, mirrored in by the assign -- and the
    // source is only read, never written, by this body.
    if ((*halfword_at(seed_record, kRecordFlagsDisplacement) & 0x4u) != 0) {
      // 006a2ec6  PUSH 0x0
      // 006a2ec8  LEA ECX,[ESP + 0x1c]
      // 006a2ecc  CALL 0x0093db80
      //
      // ESP is entry-60 after the push, so entry-60 + 0x1c is entry-32: the
      // receiver is the seed record itself, not the entry, and not the array end
      // -- which is the same address 0x006a2e8b handed the assign. The callee's
      // own first act is `TEST BYTE PTR [ESI+0x10],0x4` (0x0093db83), the very
      // test this body just made, and with the argument 0 its clearing half
      // (guarded by `CMP BYTE PTR [ESP+0x8],0x0` at 0x0093d9d) does not run, so
      // the call reports and returns. The guard is not redundant: the callee
      // reads the receiver's word itself, and this body is the one that decides
      // to call at all.
      editor_query_clear_flags_0093db80(seed_record, 0);
    }
    // 006a2ec4  JZ 0x006a2ed1 falls in here when the bit is clear.
  } else {
    // 006a2e79  LEA ECX,[EAX + 0x4]
    // 006a2e7c  CALL 0x00542b80
    //
    // The other arm. The candidate's own record at the element's displacement
    // 0x04 (kElementRecordDisplacement) is the destination, the key is already
    // there, and the array is not modified by this body: no insertion, no
    // reordering, no store into the receiver at all on this path except the
    // counter below. The callee pops the argument (RET 0x4).
    property_assign_00542b80(
        reinterpret_cast<Property*>(word_at(candidate, kElementRecordDisplacement)),
        source);

    // 006a2e81  JMP 0x006a2ed1
  }

  // 006a2ed1  INC dword ptr [EDI + 0x34]
  //
  // Reached from the found arm by the jump and from the insert arm by falling
  // through, including through the 0x0093db80 call, so the receiver's word at
  // +0x34 moves exactly once per call on every path. 0x006a2ed1 is also the only
  // memory write this body makes to the receiver itself, and it is reached after
  // the exception head is still installed, so the increment happens inside the
  // scope rather than in a cleanup handler.
  ++*reinterpret_cast<Word*>(self + 0x34);

  // 006a2ed4  MOV ECX,dword ptr [ESP + 0x2c]
  // 006a2ed8  POP EDI
  // 006a2ed9  POP ESI
  // 006a2eda  POP EBX
  // 006a2edb  MOV dword ptr FS:[0x0],ECX
  // 006a2ee2  ADD ESP,0x2c
  // 006a2ee5  RET 0x8
  //
  // The epilogue, unmodelled: it restores EDI/ESI/EBX, puts back the exception
  // head it saved at 0x006a2e2d, drops the frame and returns past two argument
  // words. None of it produces a value -- EAX is whatever the last path left in
  // it, and the three paths leave three different dead words in it -- which is
  // why the declared return type is void.
}

}  // namespace openspore::reconstruction::pkg_dfw_006a2e20
