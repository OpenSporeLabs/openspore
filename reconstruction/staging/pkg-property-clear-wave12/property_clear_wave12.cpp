#include "property_clear_wave12.hpp"

namespace openspore::reconstruction::pkg_property_clear_wave12 {

void ReleaseEntryRange_00685a30(OpaquePropertyMap* self,
                                OpaquePropertyEntry* first,
                                OpaquePropertyEntry* last,
                                ResetPropertyValue reset_property_value) {
  (void)self;
  while (first < last) {
    // 0x00685a40: TEST byte ptr [ESI + 0x14], 0x4
    // entry+0x14 is property+0x10, the low byte of the flags word.
    if ((first->property.flags & 0x0004u) != 0) {
      // 0x00685a46..0x00685a4b: PUSH 0; LEA ECX,[ESI+4]; CALL 0x0093db80
      reset_property_value(&first->property, 0);
    }
    first += 1;  // 0x00685a50: ADD ESI,0x18
  }
}

TargetSignedWord ClearSpanDelta_006a2a80(TargetSignedWord span) {
  // 0x006a2aa6..0x006a2ac1, instruction for instruction:
  //   SUB  EDI,EBP
  //   MOV  EAX,0xd5555555
  //   IMUL EDI
  //   SAR  EDX,0x2
  //   MOV  EAX,EDX
  //   SHR  EAX,0x1f
  //   ADD  EAX,EDX
  //   LEA  EDX,[EAX + EAX*2]
  //   ADD  EDX,EDX
  //   ADD  EDX,EDX
  //   ADD  EDX,EDX
  const TargetSignedWord high =
      static_cast<TargetSignedWord>((static_cast<std::int64_t>(span) *
                                    static_cast<TargetSignedWord>(0xd5555555)) >>
                                   32);
  const TargetSignedWord halved = static_cast<TargetSignedWord>(high >> 2);
  const TargetSignedWord biased =
      static_cast<TargetSignedWord>(static_cast<std::uint32_t>(halved) >> 31);
  const TargetSignedWord groups = static_cast<TargetSignedWord>(biased + halved);
  return static_cast<TargetSignedWord>(groups * 0x18);
}

void App__PropertyList__Clear_006a2a80_impl(
    OpaquePropertyList* list, PropertyClearPorts ports) {
  OpaquePropertyEntry* const first = list->properties.first;  // 0x006a2a85
  OpaquePropertyEntry* const last = list->properties.last;    // 0x006a2a89

  // 0x006a2a8f..0x006a2a97: PUSH first; PUSH last; PUSH last; CALL 0x00612b20
  // The range passed is empty (first == last), so nothing is copied and the
  // helper returns its `out` argument, i.e. `first`.
  OpaquePropertyEntry* const cursor = ports.copy_entry_range(last, last, first);

  // 0x006a2a9d..0x006a2aa1: PUSH [esi+4] (last); PUSH eax (cursor);
  //                        MOV ecx,esi (= list+0x18); CALL 0x00685a30
  ports.release_entry_range(&list->properties, cursor, last);

  // 0x006a2ac3: ADD dword ptr [ESI + 0x4], EDX
  // For every well-formed span the delta is -(last - first), so last is
  // rewound to first and the range is emptied.
  // SUB EDI,EBP is a byte subtraction of the two pointers, not an element
  // count; the reconstruction converts to a byte span explicitly.
  const TargetSignedWord span = static_cast<TargetSignedWord>(
      reinterpret_cast<const char*>(last) - reinterpret_cast<const char*>(first));
  list->properties.last =
      reinterpret_cast<OpaquePropertyEntry*>(reinterpret_cast<char*>(last) +
                                            ClearSpanDelta_006a2a80(span));

  // 0x006a2ac6: INC dword ptr [EBX + 0x34]
  list->operations_done += 1;
}

}  // namespace openspore::reconstruction::pkg_property_clear_wave12
