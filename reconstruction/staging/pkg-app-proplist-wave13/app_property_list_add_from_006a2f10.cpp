// PKG-APP-PROLIST-WAVE13 -- VA 0x006a2f10
// App::PropertyList::AddPropertiesFrom
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Machine listing, 30 instructions, body 0x006a2f10..0x006a2f51 inclusive
// (Ghidra body_end 0x006a2f53, body_span_bytes 68). Every line of the
// reconstruction below is annotated with the instruction it comes from, so the
// two can be compared without leaving this file.
//
// ABI, machine-derived: __thiscall. The receiver arrives in ECX and is aliased
// into EBP at 0x006a2f15 (MOV EBP,ECX); there is no MOV EBP,ESP, so EBP is a
// general register in this body and the whole receiver access goes through that
// alias. One ordinary stack dword at entry_ESP+0x4, read at 0x006a2f10 and
// never written. The body terminates RET 0x4 at 0x006a2f51, so the callee pops
// that dword: cdecl and fastcall are both excluded by that terminator.
//
// The direct transfers in the body are exactly three, and they are NOT three
// calls:
//
//   0x006a2f37  CALL 0x006a2d30   a call
//   0x006a2f3e  CALL 0x00542b80   a call
//   0x006a2f2b  JMP  0x006a2f30   an unconditional jump into the loop head
//                                 0x006a2f30, which is INSIDE this body
//
// 0x006a2f30 is the top of the loop body block (LEA EAX,[ESI+0x4]); control
// re-enters it from 0x006a2f48 (JNZ 0x006a2f30) and falls out of it at
// 0x006a2f4a (POP EBX). The jump at 0x006a2f2b is the loop preheader's jump over
// the increment-and-test tail, so it is intra-procedural: it is not a tail call
// and 0x006a2f30 is not a callee. It is modelled below as a for-loop, which is
// the same control flow without the manual preheader jump.

#include "app_property_list_add_from_006a2f10.hpp"

// 0x006a2f10  MOV EAX,dword ptr [ESP + 0x4]   the one stack dword: `other`
// 0x006a2f14  PUSH EBP                        EBP saved; not a frame pointer
// 0x006a2f15  MOV EBP,ECX                      the receiver alias
// 0x006a2f17  CMP EBP,EAX
// 0x006a2f19  JZ 0x006a2f50                    -> POP EBP; RET 0x4
//
// A self-copy is refused before anything is pushed beyond EBP, so the
// completion word is NOT incremented for it and the early exit is a bare
// return. The comparison is a pointer-identity test on the two arguments: no
// aliasing, offset or range test appears in the body.
extern "C" void __thiscall app_property_list_add_properties_from_006a2f10(
    OpaquePropertyList *receiver, OpaquePropertyList *other) {
  if (receiver == other) {
    return;
  }

  // 0x006a2f1b  PUSH ESI
  // 0x006a2f1c  MOV ESI,dword ptr [EAX + 0x18]   the argument's range begin
  // 0x006a2f1f  PUSH EDI
  // 0x006a2f20  MOV EDI,dword ptr [EAX + 0x1c]   the argument's range end,
  //                                               hoisted into a register and
  //                                               compared against ESI, not
  //                                               re-read per iteration
  OpaquePropertyElement *const first = property_list_range_begin(other);
  OpaquePropertyElement *const last = property_list_range_end(other);

  // 0x006a2f23  CMP ESI,EDI
  // 0x006a2f25  JZ 0x006a2f4b                    -> INC dword ptr [EBP+0x34]
  //
  // An empty range skips the loop and the POP EBX with it, and still falls
  // through to the completion increment, so a copy of an empty list counts as
  // one completed copy. The for-loop below has exactly that shape: zero
  // iterations, then the increment.
  //
  // 0x006a2f27  PUSH EBX
  // 0x006a2f28  LEA EBX,[EBP + 0x18]             the receiver's storage word,
  //                                               held in a register for the
  //                                               whole loop and passed in ECX
  OpaquePropertyStorage *const storage = property_list_storage(receiver);

  // 0x006a2f2b  JMP 0x006a2f30                   loop preheader; see the file
  //                                              header note on why this is
  //                                              not a tail call
  for (OpaquePropertyElement *element = first; element != last;
       element = property_element_next(element)) {
    // 0x006a2f30  LEA EAX,[ESI + 0x4]
    // 0x006a2f33  PUSH EAX                        second stack dword
    // 0x006a2f34  PUSH ESI                        first stack dword
    // 0x006a2f35  MOV ECX,EBX
    // 0x006a2f37  CALL 0x006a2d30
    //
    // The callee ends in RET 0x4 (0x006a2e1a), so it consumes exactly one of
    // the two words pushed here: the one at [ESP+4] on entry, which is
    // element+0x4. The element word pushed at 0x006a2f34 is left on the stack
    // for the second call.
    OpaquePropertyElement *const inserted =
        unresolved_006a2d30(storage, property_element_word_after_first(element));

    // 0x006a2f3c  MOV ECX,EAX                     the first callee's result
    //                                             becomes the second's
    //                                             receiver
    // 0x006a2f3e  CALL 0x00542b80
    //
    // This callee also ends in RET 0x4 (0x00542c24), so it consumes the word
    // 0x006a2d30 left behind, which is `element`. Its return value is dead:
    // 0x006a2f43 overwrites EAX before anything can observe it.
    unresolved_00542b80(inserted, element);

    // 0x006a2f43  ADD ESI,0x18                    the element stride
    // 0x006a2f46  CMP ESI,EDI
    // 0x006a2f48  JNZ 0x006a2f30
  }

  // 0x006a2f4a  POP EBX
  // 0x006a2f4b  INC dword ptr [EBP + 0x34]
  //
  // The only receiver displacement the machine-derived receiver record
  // enumerates for this target (0x34, reached through the EBP alias of ECX).
  // It is stated here as a literal displacement rather than as a member
  // access, because the receiver record is a set of displacements and names no
  // member; what the word means -- a completed-copy counter, a generation, a
  // version -- is not established by this body.
  ++*reinterpret_cast<volatile std::uint32_t *>(
      reinterpret_cast<unsigned char *>(receiver) + 0x34u);

  // 0x006a2f4e  POP EDI
  // 0x006a2f4f  POP ESI
  // 0x006a2f50  POP EBP
  // 0x006a2f51  RET 0x4
}
