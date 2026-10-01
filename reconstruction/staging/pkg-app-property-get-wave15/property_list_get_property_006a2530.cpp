// PKG-APP-PROPERTY-GET-WAVE15
// Reconstructed body of App::PropertyList::GetProperty, VA 0x006a2530.
//
// The body is a pure read. It binary-searches the receiver's own property table
// (mProperties, an eastl::vector_map of pair<uint32_t, Property>), publishes the
// ADDRESS of the matched pair's value half through the caller's out pointer on a
// hit, and otherwise re-enters the identical port on the parent list, walking
// the chain until some list holds the key or the chain runs out.
//
// Every offset cited in the comments is a memory operand of the 47-instruction
// listing, and every field name is the SDK's own (see the header's layout
// provenance). The two agree exactly.

#include "property_list_get_property_006a2530.hpp"

namespace openspore::reconstruction::pkg_app_property_get_wave15 {

extern "C" bool PKG15_THISCALL property_list_get_property_006a2530(
    PropertyList* list, std::uint32_t propertyID, Property** result) {
  // 0x006a2537 MOV EDX,[ESI+0x18] / 0x006a253b MOV EDI,[ESI+0x1c]: the map's
  // own first and last element.
  PropertyEntry* const mpBegin = list->mProperties.mpBegin;
  PropertyEntry* const mpEnd = list->mProperties.mpEnd;

  // 0x006a2533 MOVZX EAX,byte ptr [ESI+0x2c] loads the low byte of the map's
  // mValueCompare word and 0x006a253e pushes it as the helper's fourth argument.
  // The helper never reads that slot, so it is forwarded and ignored; it is
  // passed as the byte the machine pushes, not as the whole word.
  const auto ignored_compare_byte =
      static_cast<std::uint32_t>(static_cast<std::uint8_t>(
          list->mProperties.mValueCompare));

  // 0x006a253f LEA ECX,[ESP+0x10] takes the address of the caller's propertyID
  // slot, so the key is searched by reference; 0x006a2546 is the only named
  // direct call.
  PropertyEntry* const found = property_list_lower_bound_00612db0(
      mpBegin, mpEnd, &propertyID, ignored_compare_byte);

  // 0x006a2552..0x006a2563 collapses to a two-part hit test. Three comparisons
  // are emitted: JZ rejects the end sentinel, JC (opcode 0x72, the instruction
  // the machine ABI parser cannot name) rejects an entry whose key sorts above
  // propertyID, and the LEA ECX,[EAX+0x18] / CMP EAX,ECX / JNZ triple at
  // 0x006a255a is a tautology -- a node can never equal itself plus its own
  // size -- so the JNZ at 0x006a255f is always taken and both surviving rejects
  // land on the same MOV EAX,EDI clamp. The decompiler renders the tautology as
  // "puVar3 == puVar3 + 6", which carries no semantics and is not reproduced.
  if (found != mpEnd && propertyID >= found->first) {
    // 0x006a256b ADD EAX,0x4 then 0x006a256f MOV [ECX],EAX: what reaches the
    // caller is the ADDRESS of the pair's value half (&found->second), not the
    // four value bytes themselves. Nothing dereferences the pointer here.
    *result = &found->second;
    // 0x006a2571 MOV AL,0x1 -- only AL is defined; the upper three bytes of
    // EAX still hold the entry+4 address.
    return true;
  }

  // 0x006a2577..0x006a2589: a local miss is not answered locally.
  if (PropertyList* const parent = list->mpParent) {
    // 0x006a2582 MOV EAX,[ECX] reads the PARENT's vtable, not this receiver's.
    // ECX is already the parent, so the port has the same __thiscall shape with
    // two stack dwords: propertyID pushed first (0x006a2585), then the out
    // pointer (0x006a2584). The parent's bool comes back unchanged through
    // POP EDI / POP ESI / RET 0x8 at 0x006a258b..0x006a258d, so this is a
    // result-returning call, not a true tail call. The base vtable at 0x01408820
    // stores 0x006A2530 in this slot, so a base-typed parent re-enters this body
    // and the miss path is a walk up the parent chain.
    const auto* const parent_vtable = parent->_vftable0;
    return parent_vtable->GetProperty(parent, propertyID, result);
  }

  // 0x006a2591 XOR AL,AL. The out pointer is left exactly as the caller passed
  // it; the body never writes it on this path.
  return false;
}

}  // namespace openspore::reconstruction::pkg_app_property_get_wave15
