// Clean-room reconstruction of four SporeApp.exe property-list bodies:
// 0x006a1600, 0x006a1e50, 0x006a2a40 and 0x006a3070. See the header for the
// evidence, the receiver records, and why this package declares no member of
// any object it touches.
//
// Each body below is transcribed instruction group by instruction group, with
// the listing line each group comes from quoted beside it. Every displacement
// the listing prints is spelled as a literal at the point of use.

#include "property_safe_wave9.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_property_safe_wave9 {
namespace {

#if defined(_MSC_VER)
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __thiscall
#else
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __attribute__((thiscall))
#endif

// --- the four callees this package does not reconstruct --------------------
//
// Each default below models a body whose listing is not in this package. A
// default is this reconstruction's stand-in and is documented as such; it is
// never read as a claim about the callee.

// 0x006a1e80, reached at 0x006a2a56 with the destination region in ECX and the
// source region pushed. Its real body, growth policy and per-entry copy
// semantics are unresolved (runtime gate
// gate-property-list-map-copy-port-and-set-parent-runtime-behavior), so the
// model copies the source's span bytes into the destination and bounds the copy
// by the destination's own two span words -- the same pair of displacements
// 0x006a1600 and 0x006a3070 read on the receiver, read here from a region's own
// base -- because that is the only bound this package's own vocabulary offers.
// It never allocates.
void PKG_PROPERTY_SAFE_WAVE9_THISCALL default_map_copy_port(
    OpaquePropertyMap* destination, OpaquePropertyMap* source) {
  if (destination == nullptr || source == nullptr || destination == source) {
    return;
  }
  std::uint8_t* const source_first = address_of(load_word(byte_view(source)));
  const std::uint8_t* const source_last =
      address_of(load_word(byte_view(source) + kRegionLastCursorDisplacement));
  std::uint8_t* const destination_first =
      address_of(load_word(byte_view(destination)));
  const std::uint8_t* const destination_last =
      address_of(load_word(byte_view(destination) +
                           kRegionLastCursorDisplacement));
  if (source_first > source_last || destination_first > destination_last) {
    return;
  }
  std::size_t wanted = static_cast<std::size_t>(source_last - source_first);
  const std::size_t room =
      static_cast<std::size_t>(destination_last - destination_first);
  if (wanted > room) {
    wanted = room;
  }
  if (wanted != 0) {
    std::memmove(destination_first, source_first, wanted);
  }
}

// 0x006a1710, reached at 0x006a2a67. Its side effects on the word at this+0x30
// and on the counter are unresolved (the same runtime gate), so the model does
// nothing at all: the call is the evidence, its effect is not.
void PKG_PROPERTY_SAFE_WAVE9_THISCALL
default_set_parent_port(OpaquePropertyList*, OpaquePropertyList*) {}

// 0x004cd3c0, reached at 0x006a3092 with the destination vector in ECX and the
// signed quotient pushed. Its allocator, capacity policy and zero-fill are
// unresolved (runtime gate
// gate-property-list-word-vector-resize-port-behavior), so the model moves the
// vector's end word to base + count words and never allocates: a caller must
// have sized the storage. That is exactly the part 0x006a3070 can observe,
// since it re-reads the base word itself.
void PKG_PROPERTY_SAFE_WAVE9_THISCALL
default_resize_words_port(OpaqueWordVector* vector, TargetWord count) {
  if (vector == nullptr) {
    return;
  }
  const std::uint8_t* const base = address_of(load_word(byte_view(vector)));
  store_word(byte_view(vector) + sizeof(TargetWord),
             static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(base) +
                                     count * sizeof(TargetWord)));
}

// 0x006a1de0, tail-jumped to at 0x006a1e70 with the receiver and the same two
// stack words. That body is a record in its own right and is not reconstructed
// here; the model below follows it as read from its own listing, so the
// package's default port is a transcription of another record rather than an
// invention:
//
//   MOVZX EAX,byte ptr [ESI + 0x2c] / MOV EDX,[ESI + 0x18] / MOV EDI,[ESI + 0x1c]
//       the region byte and the two span cursors
//   CALL 0x00612db0                the search helper, whose own body is not
//                                   modelled here; the model searches inline
//   CMP EAX,EDI / JZ miss          a cursor at the end is a miss
//   CMP EDX,dword ptr [EAX] / JC   the first entry whose key is >= the id
//   LEA ECX,[EAX + 0x18]           the cursor the search stops on
//   MOV dword ptr [ECX],EAX ... no: ADD EAX,0x4; MOV [ECX],EAX; MOV AL,0x1
//                                   a hit stores entry+0x4 and returns true
//   MOV ECX,dword ptr [ESI + 0x30] a miss reads the word at +0x30
//   TEST ECX,ECX / JZ false        a null word ends the chain
//   MOV EAX,dword ptr [ECX] / MOV EDX,dword ptr [EAX + 0x20] / CALL EDX
//                                   otherwise the parent list's +0x20 slot is
//                                   tail-called with the same two words
bool PKG_PROPERTY_SAFE_WAVE9_THISCALL default_get_property_alt_base_port(
    OpaquePropertyList* list, TargetWord property_id, OpaqueProperty** result) {
  const std::uint8_t* cursor =
      address_of(load_word(byte_view(list) + kSpanFirstDisplacement));
  const std::uint8_t* const last =
      address_of(load_word(byte_view(list) + kSpanLastDisplacement));
  while (cursor < last) {
    const TargetWord key = load_word(cursor);
    if (key >= property_id) {
      break;
    }
    cursor += kEntryStride;
  }
  if (cursor == last || load_word(cursor) != property_id) {
    const TargetWord parent_word =
        load_word(byte_view(list) + kCopyFromParentDisplacement);
    if (parent_word == 0) {
      return false;
    }
    OpaquePropertyList* const parent = list_at(parent_word);
    const GetPropertyAlt defer =
        load_slot<GetPropertyAlt>(address_of(load_word(byte_view(parent))) + 0x20);
    return defer(parent, property_id, result);
  }
  *result = property_at(cursor + kEntrySecondWordDisplacement);
  return true;
}

#undef PKG_PROPERTY_SAFE_WAVE9_THISCALL

}  // namespace

PropertySafePorts& property_safe_ports() {
  static PropertySafePorts ports{default_map_copy_port, default_set_parent_port,
                                 default_resize_words_port,
                                 default_get_property_alt_base_port};
  return ports;
}

void property_safe_set_ports(const PropertySafePorts& ports) {
  property_safe_ports() = ports;
}

void property_safe_reset_ports() {
  property_safe_ports() = PropertySafePorts{
      default_map_copy_port, default_set_parent_port, default_resize_words_port,
      default_get_property_alt_base_port};
}

#if defined(_MSC_VER)
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __thiscall
#else
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __attribute__((thiscall))
#endif

// 0x006a1600 App::DirectPropertyList::AddPropertiesFrom
//
//   MOV EAX,dword ptr [ESP + 0x4]      the argument
//   MOV EDI,ECX                        the receiver, aliased
//   CMP EDI,EAX / JZ epilogue          receiver == argument returns untouched
//   MOV EBX,dword ptr [EAX + 0x1c]     the argument's last cursor
//   MOV ESI,dword ptr [EAX + 0x18]     the argument's first cursor
//   CMP ESI,EBX / JZ increment         an empty span skips the loop only
//   loop: MOV EAX,[EDI]                the table word, re-read every iteration
//         MOV EDX,[ESI]                the entry's first word
//         MOV EAX,[EAX + 0x14]         the table's slot
//         LEA ECX,[ESI + 0x4] / PUSH ECX / PUSH EDX / MOV ECX,EDI / CALL EAX
//         ADD ESI,0x18 / CMP ESI,EBX / JNZ loop
//   INC dword ptr [EDI + 0x34]         once, on every path but the early return
//   RET 0x4
void PKG_PROPERTY_SAFE_WAVE9_THISCALL
direct_property_list_add_properties_from_006a1600(OpaquePropertyList* list,
                                                  OpaquePropertyList* other) {
  if (list == other) {
    return;
  }
  const std::uint8_t* entry = address_of(load_word(byte_view(other) + 0x18));
  const std::uint8_t* const last =
      address_of(load_word(byte_view(other) + 0x1c));
  while (entry != last) {
    const std::uint8_t* const vtable_word =
        address_of(load_word(byte_view(list)));
    const SetProperty set = load_slot<SetProperty>(vtable_word + 0x14);
    set(list, load_word(entry), property_at(entry + 0x4));
    entry += 0x18;
  }
  store_word(byte_view(list) + 0x34,
             load_word(byte_view(list) + 0x34) + 1u);
}

// 0x006a1e50 App::DirectPropertyList::GetPropertyAlt
//
//   MOV EAX,dword ptr [ESP + 0x4]      the id
//   CMP EAX,dword ptr [ECX + 0x38] / JNC base
//                                    unsigned, so id == the word takes the base
//   MOV EDX,dword ptr [ECX]           the table word
//   PUSH EAX / MOV EAX,[EDX + 0x28] / CALL EAX
//   MOV ECX,dword ptr [ESP + 0x8]      the out pointer, re-read after the call
//   MOV dword ptr [ECX],EAX           stored only on this path
//   MOV AL,0x1 / RET 0x8
//   base: MOV dword ptr [ESP + 0x4],EAX / JMP 0x006a1de0
//                                    the id is written over the out pointer's
//                                    slot, then the base routine is entered with
//                                    the receiver and the same two words
bool PKG_PROPERTY_SAFE_WAVE9_THISCALL
direct_property_list_get_property_alt_006a1e50(OpaquePropertyList* list,
                                               TargetWord property_id,
                                               OpaqueProperty** result) {
  if (property_id < load_word(byte_view(list) + 0x38)) {
    const std::uint8_t* const vtable_word =
        address_of(load_word(byte_view(list)));
    const GetPropertyObject fetch =
        load_slot<GetPropertyObject>(vtable_word + 0x28);
    *result = fetch(list, property_id);
    return true;
  }
  return property_safe_ports().get_property_alt_base(list, property_id,
                                                     result);
}

// 0x006a2a40 App::PropertyList::CopyFrom
//
//   MOV EAX,dword ptr [ESP + 0x4] / MOV ESI,ECX
//   CMP ESI,EAX / JZ epilogue          receiver == argument returns untouched
//   LEA EDI,[EAX + 0x18]              the argument's region
//   LEA EBX,[ESI + 0x18]              the receiver's region
//   PUSH EDI / MOV ECX,EBX / CALL 0x006a1e80
//   MOV AL,byte ptr [EDI + 0x14]      one byte out of the argument's region
//   MOV byte ptr [EBX + 0x14],AL      stored into the receiver's region
//   MOV EAX,dword ptr [ESI + 0x30]    read after the call, not before
//   PUSH EAX / MOV ECX,ESI / CALL 0x006a1710
//   RET 0x4
void PKG_PROPERTY_SAFE_WAVE9_THISCALL property_list_copy_from_006a2a40(
    OpaquePropertyList* list, OpaquePropertyList* other) {
  if (list == other) {
    return;
  }
  OpaquePropertyMap* const source =
      reinterpret_cast<OpaquePropertyMap*>(byte_view(other) + 0x18);
  OpaquePropertyMap* const destination =
      reinterpret_cast<OpaquePropertyMap*>(byte_view(list) + 0x18);
  property_safe_ports().map_copy(destination, source);
  store_byte(byte_view(destination) + 0x14, load_byte(byte_view(source) + 0x14));
  property_safe_ports().set_parent(
      list, list_at(load_word(byte_view(list) + 0x30)));
}

// 0x006a3070 App::PropertyList::GetPropertyIDs
//
//   MOV ESI,ECX                        the receiver, aliased
//   MOV ECX,[ESI + 0x1c] / SUB ECX,[ESI + 0x18]
//                                    the span, in bytes
//   MOV EAX,0x2aaaaaab / IMUL ECX / SAR EDX,0x2 / MOV EAX,EDX / SHR EAX,0x1f
//   / ADD EAX,EDX                      a truncating signed division by 24
//   MOV EDI,[ESP + 0xc]                the destination vector
//   PUSH EAX / MOV ECX,EDI / CALL 0x004cd3c0
//                                    the raw quotient, forwarded unclamped
//   MOV EAX,[ESI + 0x18] / CMP EAX,[ESI + 0x1c] / JZ epilogue
//   loop: XOR ECX,ECX
//         MOV EBX,[EAX]                the entry's first word
//         MOV EDX,[EDI]                the destination's first word, re-read
//         MOV [ECX + EDX*1],EBX        stored at a word-indexed offset
//         ADD EAX,0x18 / ADD ECX,0x4
//         CMP EAX,[ESI + 0x1c] / JNZ loop
//   RET 0x4
//
// The loop's bound is the receiver's span and not the destination's end word:
// nothing here reads the destination's second word, and the model reproduces
// that, including the overflow a too-small destination would suffer. Both span
// cursors are re-read after the port call, because the listing reads them again
// there: the count is computed from the first pair of reads, the loop runs on
// the second.
void PKG_PROPERTY_SAFE_WAVE9_THISCALL property_list_get_property_ids_006a3070(
    OpaquePropertyList* list, OpaqueWordVector* destination) {
  const TargetWord first = load_word(byte_view(list) + 0x18);
  const TargetWord last = load_word(byte_view(list) + 0x1c);
  property_safe_ports().resize_words(
      destination, static_cast<TargetWord>(span_entry_count(first, last)));
  std::uint8_t* entry = address_of(load_word(byte_view(list) + 0x18));
  if (entry == address_of(load_word(byte_view(list) + 0x1c))) {
    return;
  }
  for (TargetWord index = 0;; ++index) {
    store_word(address_of(load_word(byte_view(destination))) +
                   index * sizeof(TargetWord),
               load_word(entry));
    entry += 0x18;
    if (entry == address_of(load_word(byte_view(list) + 0x1c))) {
      return;
    }
  }
}

#undef PKG_PROPERTY_SAFE_WAVE9_THISCALL

}  // namespace openspore::reconstruction::pkg_property_safe_wave9
