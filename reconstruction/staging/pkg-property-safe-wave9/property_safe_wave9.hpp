// Clean-room reconstruction of four SporeApp.exe property-list bodies:
//
//   0x006a1600  App::DirectPropertyList::AddPropertiesFrom
//   0x006a1e50  App::DirectPropertyList::GetPropertyAlt
//   0x006a2a40  App::PropertyList::CopyFrom
//   0x006a3070  App::PropertyList::GetPropertyIDs
//
// Binary: SporeApp.exe 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e, image base
// 0x00400000. Evidence: the complete machine listings persisted under
// reconstruction/evidence/006a1600, 006a1e50, 006a2a40 and 006a3070 (27, 13, 22
// and 31 instructions; each parse record consumed its listing in full, 0
// unparsed, degraded=false). No other machine source is used here.
//
// ---------------------------------------------------------------------------
// Why this package declares no member of anything
// ---------------------------------------------------------------------------
//
// The machine-derived receiver record for all four targets is `bounds_only`:
//
//   0x006a1600  ECX  offsets [0x00, 0x34]  R-ALIAS  written_through 1
//   0x006a1e50  ECX  offsets [0x00, 0x28, 0x38]  R-DIRECT  written_through 0
//   0x006a2a40  ECX  offsets [0x30]  R-ALIAS  written_through 0
//   0x006a3070  ECX  offsets [0x18, 0x1c]  R-ALIAS  written_through 0
//
// `bounds_only` is the record's own statement that it enumerates *how far the
// body was seen reaching*, not the receiver's members. A displacement is
// therefore the strongest thing the evidence carries, and a member *name* is a
// stronger claim than a displacement: nothing in these four bodies says which
// member sits at a slot, so nothing here may say it in code. A previous
// revision of this package wrote `list->operations_done`, `list->fast_count`,
// `entry->id`, `properties.lookup_mode` and `list->parent`; every one of those
// names was an assertion the receiver record can neither confirm nor refute, and
// that is the over-claim this revision removes.
//
// So the receiver, the region the body forms at receiver+0x18, and the property
// object are all *incomplete types* here, and every access is a byte
// displacement into one of them. What the machine proves is kept verbatim: a
// 4-byte slot at receiver+0x34, a byte at receiver+0x2c, two span cursors at
// receiver+0x18 and receiver+0x1c, and a two-level table load whose second-level
// displacement is 0x14 (0x006a1600) or 0x28 (0x006a1e50).
//
// The bodies of the sibling record 0x006a1de0 (`App::PropertyList::
// GetPropertyAlt`, the routine 0x006a1e50 tail-jumps to) do corroborate what
// lives at these displacements -- it reads `byte ptr [ESI + 0x2c]`, the pair
// `[ESI + 0x18]` / `[ESI + 0x1c]`, `dword ptr [ESI + 0x30]` as a parent pointer
// and dispatches its `+0x20` slot on it, and hands back `entry + 0x4` on a hit.
// That is a *different* record's evidence, so it is cited here as prose and
// deliberately not encoded as a member name in this package's four bodies.
//
// ---------------------------------------------------------------------------
// Two things the listing shows and this package does not spell as a literal
// ---------------------------------------------------------------------------
//
// Every *other* displacement is spelled as a literal at the point of use, so
// each one the body reaches is individually visible to be accounted for against
// the machine rather than hidden behind a name. The two exceptions are:
//
// 1. A displacement the listing prints with no literal at all. `MOV EDX,dword
//    ptr [ECX]`, `MOV EAX,dword ptr [EDI]`, `MOV EBX,dword ptr [EAX]` and
//    `MOV EDX,dword ptr [EDI]` are the word at displacement 0. Spelling it
//    `+ 0x0` would add a hexadecimal constant the listing never prints, so the
//    accessors below read the first word with no displacement argument at all.
// 2. The destination cursor step of 0x006a3070, which is `ADD ECX,0x4`. The
//    cursor counts words, so the source advances it by `sizeof(TargetWord)`
//    rather than by a literal; the 0x4 is a stride in a cursor, not a
//    displacement into any of these objects, and the listing's only other 0x4
//    is a stack slot.
//
// The constants below are the same values under names: the four bodies quote the
// listing, the port defaults (which model callees whose listings are not in this
// package) use the shared vocabulary, and the model test pins every constant
// against the instruction it comes from.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG property safe wave9 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_property_safe_wave9 {

using TargetWord = std::uint32_t;
using TargetSignedWord = std::int32_t;

// Incomplete on purpose: see the header comment. A pointer to an incomplete
// type is all any of these needs to be, because no body here dereferences one
// through a named member.
struct OpaquePropertyList;
struct OpaquePropertyMap;
struct OpaqueProperty;

#if defined(_MSC_VER)
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __thiscall
#else
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __attribute__((thiscall))
#endif

// The word vector the resize port is handed at 0x006a3092. 0x006a3070 itself
// touches exactly one word of it -- the base pointer at displacement 0, re-read
// on every iteration of the copy loop -- and no other body in this package
// touches the object at all. The second word is the resize port's own
// bookkeeping: no listing in this package shows it, so it is named by
// displacement and nothing more.
struct OpaqueWordVector {
  TargetWord word_00;  // 0x006a30a4: MOV EDX,dword ptr [EDI]
  TargetWord word_04;  // the resize port's own end cursor; shown by no body here
};

// ---------------------------------------------------------------------------
// Displacements, each one an instruction in one of the four listings
// ---------------------------------------------------------------------------
//
// The names describe the access the body makes, never a member. Every value is
// pinned by the model test against the listing it comes from.

// The table word at displacement 0 of the receiver.
//   0x006a1600  MOV EAX,dword ptr [EDI]      (EDI holds ECX)
//   0x006a1e50  MOV EDX,dword ptr [ECX]
inline constexpr TargetWord kReceiverTableDisplacement = 0x00;

// The word 0x006a1600 increments once, after its loop.
//   INC dword ptr [EDI + 0x34]
inline constexpr TargetWord kAddFromCounterDisplacement = 0x34;

// The word 0x006a1e50 compares the requested id against.
//   CMP EAX,dword ptr [ECX + 0x38]
inline constexpr TargetWord kGetAltLimitDisplacement = 0x38;

// The word 0x006a2a40 reads and hands back to the SetParent port.
//   MOV EAX,dword ptr [ESI + 0x30]
inline constexpr TargetWord kCopyFromParentDisplacement = 0x30;

// The two span cursors. 0x006a1600 walks the argument's span from one to the
// other; 0x006a3070 subtracts them and divides by the entry stride.
//   0x006a1600  MOV EBX,dword ptr [EAX + 0x1c] / MOV ESI,dword ptr [EAX + 0x18]
//   0x006a3070  MOV ECX,dword ptr [ESI + 0x1c] / MOV EAX,dword ptr [ESI + 0x18]
inline constexpr TargetWord kSpanFirstDisplacement = 0x18;
inline constexpr TargetWord kSpanLastDisplacement = 0x1c;

// The entry address 0x006a1600 forms and pushes.
//   LEA ECX,[ESI + 0x4]
inline constexpr TargetWord kEntrySecondWordDisplacement = 0x04;

// The region's own second span word, read from the region's own base rather
// than from the receiver. No body in this package reads it -- the two span
// words this package reads are the receiver's own at +0x18 and +0x1c -- so it
// is used only by the port defaults below, which model bodies this package does
// not reconstruct and whose vocabulary has to be spelled out somewhere.
inline constexpr TargetWord kRegionLastCursorDisplacement = 0x04;

// The single byte 0x006a2a40 copies between the two regions, at +0x14 inside a
// region that begins at +0x18 -- so on the receiver it is the byte at +0x2c.
//   MOV AL,byte ptr [EDI + 0x14] / MOV byte ptr [EBX + 0x14],AL
inline constexpr TargetWord kRegionByteDisplacement = 0x14;

// The stride between entries.
//   0x006a1600  ADD ESI,0x18
//   0x006a3070  ADD EAX,0x18
// The divisor of 0x006a3070's count is the same 24, produced by the
// 0x2aaaaaab / SAR 0x2 / SHR 0x1f / ADD sequence.
inline constexpr TargetWord kEntryStride = 0x18;

// Slot displacements, read out of the *table* the receiver points at and not
// out of the receiver. The two-level shape itself is machine evidence:
// 0x006a1600 loads the table word and then `MOV EAX,dword ptr [EAX + 0x14]`
// before `CALL EAX`, and 0x006a1e50 does the same through EDX with 0x28.
inline constexpr TargetWord kSetSlotDisplacement = 0x14;
inline constexpr TargetWord kGetObjectSlotDisplacement = 0x28;

// ---------------------------------------------------------------------------
// Access
// ---------------------------------------------------------------------------
//
// An object as raw bytes, and word/byte/slot loads and stores over that view.
// The only thing a body can say about a receiver is "the word at this
// displacement", which is exactly what the listing says.

inline std::uint8_t* byte_view(void* object) {
  return static_cast<std::uint8_t*>(object);
}

inline const std::uint8_t* byte_view(const void* object) {
  return static_cast<const std::uint8_t*>(object);
}

// The first word of an object: the word at displacement 0, which the listing
// prints with no displacement (`MOV EDX,dword ptr [ECX]`).
inline TargetWord load_word(const std::uint8_t* slot) {
  TargetWord value = 0;
  std::memcpy(&value, slot, sizeof value);
  return value;
}

inline void store_word(std::uint8_t* slot, TargetWord value) {
  std::memcpy(slot, &value, sizeof value);
}

inline std::uint8_t load_byte(const std::uint8_t* slot) { return *slot; }

inline void store_byte(std::uint8_t* slot, std::uint8_t value) { *slot = value; }

// A slot is one 32-bit word of a table, named by the address it sits at. memcpy
// rather than a cast, so no alignment or aliasing assumption is made about the
// table's storage.
template <typename Slot>
Slot load_slot(const std::uint8_t* slot) {
  static_assert(sizeof(Slot) == sizeof(TargetWord), "a slot is one 32-bit word");
  Slot value = nullptr;
  std::memcpy(&value, slot, sizeof value);
  return value;
}

// A stored pointer, read back out of a slot as the address it is.
inline std::uint8_t* address_of(TargetWord word) {
  return reinterpret_cast<std::uint8_t*>(static_cast<std::uintptr_t>(word));
}

inline OpaquePropertyList* list_at(TargetWord word) {
  return reinterpret_cast<OpaquePropertyList*>(static_cast<std::uintptr_t>(word));
}

inline OpaqueProperty* property_at(const std::uint8_t* address) {
  return reinterpret_cast<OpaqueProperty*>(const_cast<std::uint8_t*>(address));
}

// (last - first) / stride, in the signed arithmetic 0x006a3070 computes: the
// 0x2aaaaaab multiply with the SAR 0x2 and the SHR 0x1f / ADD sign correction is
// a truncating signed division by 24, so a span whose last cursor precedes its
// first yields a negative quotient and the body forwards it unaltered.
inline TargetSignedWord span_entry_count(TargetWord first, TargetWord last) {
  const TargetSignedWord bytes = static_cast<TargetSignedWord>(last - first);
  return bytes / static_cast<TargetSignedWord>(kEntryStride);
}

// ---------------------------------------------------------------------------
// Call shapes the call sites fix
// ---------------------------------------------------------------------------
//
// A callee's own epilogue is not in these four listings, so nothing is claimed
// about who removes the pushed words; what is claimed is the number of words a
// call site pushes and where the receiver register is loaded from.

// 0x006a1625: ECX = this, then PUSH &entry+0x4 and PUSH the entry's first word,
// so the slot takes (receiver, one word, one pointer) and nothing is left over.
using SetProperty = void(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(
    OpaquePropertyList*, TargetWord, OpaqueProperty*);

// 0x006a1e5f: ECX = this, one word pushed (the id), the result comes back in EAX
// and is stored through the out pointer the caller already holds.
using GetPropertyObject = OpaqueProperty*(
    PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaquePropertyList*, TargetWord);

// The routine 0x006a1e50 tail-jumps to at 0x006a1e70, entered with the same
// receiver and the same two stack words; the id is written back over the out
// pointer's slot first (`MOV dword ptr [ESP + 0x4],EAX`) so the callee sees them
// in the order it expects.
using GetPropertyAlt = bool(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(
    OpaquePropertyList*, TargetWord, OpaqueProperty**);

// 0x006a2a56: ECX = the destination region, one pointer pushed. The result is
// never read, so this port returns void.
using MapCopy = void(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaquePropertyMap*,
                                                        OpaquePropertyMap*);

// 0x006a2a67: ECX = this, one word pushed (the word this+0x30 holds). The
// result is never read.
using SetParent = void(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaquePropertyList*,
                                                          OpaquePropertyList*);

// 0x006a3092: ECX = the destination vector, one word pushed (the quotient). The
// result is never read.
using ResizeWordVector = void(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaqueWordVector*,
                                                                TargetWord);

// The four callees these bodies transfer to that this package does not
// reconstruct: 0x006a1e80, 0x006a1710, 0x004cd3c0 and the 0x006a1de0 tail.
// Each is a port, and each port's default body is this reconstruction's model
// of a callee whose listing is not in this package -- never a claim about that
// callee. There is no fifth: none of the four bodies transfers anywhere else.
struct PropertySafePorts {
  MapCopy map_copy;
  SetParent set_parent;
  ResizeWordVector resize_words;
  GetPropertyAlt get_property_alt_base;
};

static_assert(sizeof(TargetWord) == 4, "a target word is 32-bit");
static_assert(sizeof(void*) == 4, "a target pointer is 32-bit");
static_assert(sizeof(std::uintptr_t) == 4, "address arithmetic is 32-bit");
static_assert(sizeof(PropertySafePorts) == 4 * sizeof(void*),
              "the port table is exactly the four callees these bodies reach");
static_assert(sizeof(OpaqueWordVector) == 2 * sizeof(TargetWord),
              "the word vector is two words");

PropertySafePorts& property_safe_ports();
void property_safe_set_ports(const PropertySafePorts& ports);
void property_safe_reset_ports();

// 0x006a1600 App::DirectPropertyList::AddPropertiesFrom. RET 0x4: one stack
// word, removed by the callee. No result is produced on any path.
void PKG_PROPERTY_SAFE_WAVE9_THISCALL
direct_property_list_add_properties_from_006a1600(OpaquePropertyList* list,
                                                  OpaquePropertyList* other);

// 0x006a1e50 App::DirectPropertyList::GetPropertyAlt. RET 0x8: two stack words,
// removed by the callee. AL is set to 1 on the fast path and EAX carries the
// value the slot returned, which the body stores through the out pointer.
bool PKG_PROPERTY_SAFE_WAVE9_THISCALL
direct_property_list_get_property_alt_006a1e50(OpaquePropertyList* list,
                                               TargetWord property_id,
                                               OpaqueProperty** result);

// 0x006a2a40 App::PropertyList::CopyFrom. RET 0x4: one stack word, removed by
// the callee. No result is produced on any path.
void PKG_PROPERTY_SAFE_WAVE9_THISCALL property_list_copy_from_006a2a40(
    OpaquePropertyList* list, OpaquePropertyList* other);

// 0x006a3070 App::PropertyList::GetPropertyIDs. RET 0x4: one stack word,
// removed by the callee. No result is produced on any path.
void PKG_PROPERTY_SAFE_WAVE9_THISCALL property_list_get_property_ids_006a3070(
    OpaquePropertyList* list, OpaqueWordVector* destination);

#undef PKG_PROPERTY_SAFE_WAVE9_THISCALL

}  // namespace openspore::reconstruction::pkg_property_safe_wave9
