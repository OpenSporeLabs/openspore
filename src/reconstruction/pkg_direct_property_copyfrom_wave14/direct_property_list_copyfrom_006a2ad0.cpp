// Bounded x86-32 reconstruction of App::DirectPropertyList::CopyFrom.
//
//   VA            0x006a2ad0
//   Program       SPORE/SporeBin/SporeApp.exe 3.1.0.22
//                 (sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//   Body          0x006a2ad0 .. 0x006a2b15, 33 instructions, machine parse 33/33
//   Vtable        vtable:0x01408870, this function reached through the word at
//                 0x0140889c (the only function xref the record carries)
//
// Machine evidence for this body (reconstruction/evidence/006a2ad0/evidence.json,
// categories.disassembly) is the only listing used here. Every access below is a
// displacement that appears verbatim in that listing. No struct member is named,
// because no machine record names one: the derived ABI record
// (abi_derived.receiver) is `bounds_only` and enumerates only the displacements
// 0x0 and 0x30, which it observed through the EDI alias of the ECX receiver, so
// the layout of the receiver is not established here.
//
// `bounds_only` is what that record says about itself, and it decides what it can
// and cannot be used for. It states where the body was SEEN REACHING and nothing
// more: it is not an enumeration of the receiver's words, so a displacement this
// body uses which it does not list is uncorroborated, not contradicted. The
// record is also an observation, not a fact about the object -- the inference can
// only see displacements it was in a position to see. Concretely, the body
// addresses receiver displacement 0x18 (LEA ECX,[EDI + 0x18] at 0x006a2add) and
// the record does not enumerate it, and that is carried below as an open
// question rather than resolved either way. 0x0 and 0x30, which the record does
// enumerate, agree with what the body does at those displacements.
//
// The displacements this file writes, partitioned by the object they are on, so
// that no displacement is counted against the receiver record that does not
// speak for it:
//
//   receiver (EDI, the ECX receiver)   0x0  vtable word, read at 0x006a2af0
//                                     0x18 address handed to 0x006a28f0
//                                     0x30 word handed to 0x006a1710
//   argument object (EBX)             0x18 range begin, read at 0x006a2ae5
//                                     0x1c range end, read at 0x006a2ae8
//   element (ESI)                     0x0  first word, read at 0x006a2af2
//                                     0x4  address pushed at 0x006a2af7
//                                     0x18 stride, ADD ESI,0x18 at 0x006a2b00
//   receiver's table word             0x14 the function pointer, 0x006a2af4
//
// So of the five displacements this source declares, only 0x18 and 0x30 are
// receiver displacements; 0x4, 0x14 and 0x1c sit on the element, the table word
// and the argument object, where a receiver record has no standing. All five are
// written out because all five are in the listing, and none of them is dressed up
// as a member name to make a displacement disappear.
//
// Two direct transfers, both reproduced and neither invented:
//   0x006a28f0  LEA ECX,[EDI+0x18] / CALL 0x006a28f0, receiver only, no stack
//               argument. Its own body reads the two words at +0x0 and +0x4 of
//               that sub-object and advances the word at +0x4 by 0x18 per
//               element, so the call sizes the receiver's 0x18-stride element
//               range at displacement 0x18 to the element count of the source
//               list. It is declared, not defined: it is outside this package.
//   0x006a1710  App::PropertyList::SetParent, the name the Ghidra record carries
//               for that address; called with the receiver in ECX and one pushed
//               word read from the receiver at displacement 0x30.
//
// The body also dispatches virtually and that is modelled, not hidden. It reads
// the receiver's first word, reads the function pointer at displacement 0x14 of
// that word, and calls it through a function-pointer local. That word is a
// vtable pointer -- the record associates this body with vtable:0x01408870, and
// the only xref into the body is from a slot of that vtable -- but the slot
// target itself is UNRESOLVED: no machine record in this package names the
// function at that slot, so none is named here. Neither the slot index nor a
// member name for the receiver word is invented. The address of the vtable is
// deliberately not written as a literal in this file; the evidence pack records
// it, and the body reads it indirectly through the receiver.
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL __thiscall
#else
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL __attribute__((thiscall))
#endif

// The one indirect transfer target of this body. The two words pushed for it are
// the source element's first word (read at element + 0x0) and the address
// element + 0x4, in that order, with the receiver in ECX.
typedef void (PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL *SlotTarget_006a2ad0)(void *receiver, std::uint32_t first,
                                               void *second);

// 0x006a28f0: receiver-only call on the sub-object at receiver displacement 0x18.
// Defined outside this package; declared here because this body calls it.
extern "C" void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL App_unmodelled_element_range_resize_006a28f0(void *element_range);

// 0x006a1710, named App::PropertyList::SetParent by the Ghidra record. One pushed
// word, receiver in ECX.
extern "C" void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL App_PropertyList_SetParent_006a1710(void *receiver, void *parent);

extern "C" void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL App_DirectPropertyList_CopyFrom_006a2ad0(void *self, void *pOther) {
  // CMP EDI,EBX / JZ 0x006a2b13 -- the self-copy case skips the whole body and
  // reaches the epilogue directly, with EBX and EDI already pushed and ESI not.
  if (self == pOther) {
    return;
  }

  // LEA ECX,[EDI + 0x18] / CALL 0x006a28f0, before the source range is read.
  App_unmodelled_element_range_resize_006a28f0(static_cast<unsigned char *>(self) + 0x18);

  // The source range: begin at displacement 0x18, end at displacement 0x1c of the
  // argument object, both read after the resize above.
  const unsigned char *element =
      *reinterpret_cast<const unsigned char *const *>(static_cast<const unsigned char *>(pOther) + 0x18);
  const unsigned char *element_end =
      *reinterpret_cast<const unsigned char *const *>(static_cast<const unsigned char *>(pOther) + 0x1c);

  // CMP ESI,EBX / JZ 0x006a2b07 -- an empty source range skips the loop body and
  // still falls through to the tail call.
  if (element != element_end) {
    do {
      // MOV EDX,[ESI] -- the element's first word.
      const std::uint32_t first = *reinterpret_cast<const std::uint32_t *>(element);
      // LEA ECX,[ESI + 0x4] -- the second argument is the element's second field.
      void *second = static_cast<void *>(const_cast<unsigned char *>(element + 0x4));

      // MOV EAX,[EDI] then MOV EAX,[EAX + 0x14]: the receiver's first word, then
      // the function pointer at displacement 0x14 of it. Both reads are inside
      // the loop, so the slot is re-read per element.
      const unsigned char *vtable_word =
          *reinterpret_cast<const unsigned char *const *>(self);
      SlotTarget_006a2ad0 slot = *reinterpret_cast<SlotTarget_006a2ad0 *>(
          const_cast<unsigned char *>(vtable_word) + 0x14);

      // PUSH ECX / PUSH EDX / MOV ECX,EDI / CALL EAX -- the indirect transfer.
      // The target is unresolved; see the note above.
      slot(self, first, second);

      // ADD ESI,0x18 -- the element stride.
      element += 0x18;
      // CMP ESI,EBX / JNZ 0x006a2af0
    } while (element != element_end);
  }

  // MOV ECX,[EDI + 0x30] / PUSH ECX / MOV ECX,EDI / CALL 0x006a1710 -- reached
  // from both the empty-range and the loop-exit paths.
  App_PropertyList_SetParent_006a1710(
      self, *reinterpret_cast<void *const *>(static_cast<const unsigned char *>(self) + 0x30));
}
