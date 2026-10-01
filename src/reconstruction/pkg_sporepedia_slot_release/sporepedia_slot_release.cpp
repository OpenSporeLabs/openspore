// PKG-SPOREPEDIA-SLOT-RELEASE -- VA 0x00641e10
// Sporepedia, sporepedia-online cluster (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Machine listing, 19 instructions, body 0x00641e10..0x00641e3a inclusive
// (Ghidra body_end 0x00641e3a, body_span_bytes 43). Every line of the model
// below is annotated with the instruction it comes from.
//
//   00641e10  PUSH ESI
//   00641e11  PUSH EDI
//   00641e12  MOV EDI,ECX                     the receiver alias
//   00641e14  MOV ECX,dword ptr [EDI + 0x20]   the receiver's word at 0x20
//   00641e17  LEA ESI,[EDI + 0x20]             the address of that same word
//   00641e1a  TEST ECX,ECX
//   00641e1c  JZ 0x00641e2b                    -> the tail, skipping the block
//   00641e1e  MOV dword ptr [ESI],0x0          the word at 0x20 is cleared first
//   00641e24  MOV EAX,dword ptr [ECX]          the pointee's dispatch word
//   00641e26  MOV EDX,dword ptr [EAX + 0x4]    the slot at displacement 4
//   00641e29  CALL EDX                         the indirect transfer
//   00641e2b  PUSH ESI
//   00641e2c  ADD EDI,0x4                      a base adjustment, not a field
//   00641e2f  PUSH EDI
//   00641e30  CALL 0x005bf0e0                  the one direct transfer
//   00641e35  ADD ESP,0x8                      caller-cleaned two words
//   00641e38  POP EDI
//   00641e39  POP ESI
//   00641e3a  RET
//
// ABI, machine-derived: __thiscall. The receiver arrives in ECX, is dereferenced
// before any definite write to it (0x00641e14) and is aliased into EDI at
// 0x00641e12; the terminator is a bare RET at 0x00641e3a with no immediate and
// no stack reads, so the caller owns the stack. Nothing in the body pushes an
// ordinary argument of its own: the only two pushes, at 0x00641e2b and
// 0x00641e2f, are the argument pair of the direct callee and are consumed by
// the ADD ESP,0x8 at 0x00641e35.
//
// The two transfers are of different kinds and only one of them is direct:
//
//   0x00641e29  CALL EDX     indirect. EDX is loaded at 0x00641e26 from the
//                             pointee's dispatch word, so this is a virtual
//                             transfer through a slot. abi_derived.dispatch
//                             records indirect_calls=1, which agrees with the
//                             listing.
//   0x00641e30  CALL 0x005bf0e0   the only direct transfer, and the only
//                             address the xref export carries out of this body.
//
// Nothing in the record names the slot's callee, so it is not named here. The
// slot is read and called; what it resolves to is unresolved, and the model says
// so rather than inventing a target.
//
// The receiver is addressed only through machine displacements. The
// machine-derived receiver record enumerates exactly one, 0x20, and it does not
// say which member that word is -- so no member name appears in this file.
//
// Every 0x literal the listing carries is accounted for here, and each is
// accounted for as what the instruction actually does with it:
//
//   0x20   receiver word: read (0x00641e14), addressed (0x00641e17),
//          cleared (0x00641e1e), passed by address (0x00641e2b). The only
//          displacement the receiver record enumerates.
//   0x0    the cleared value at 0x00641e1e. Modelled as a stored null
//          pointer; no machine record gives the word a type, so nothing more
//          is claimed for the zero.
//   0x4    read at 0x00641e26 as the slot's byte displacement in the
//          POINTEE'S dispatch word -- a different object from the receiver, so
//          it is not a receiver displacement and the receiver record's silence
//          on it says nothing about the receiver. Modelled below as dword
//          index 1, which is the same byte.
//   0x4    AGAIN, at 0x00641e2c: ADD EDI,0x4 is a base adjustment that forms
//          the address receiver+4. The body never dereferences through that
//          address, so it is not a field access; it is written below as a
//          pointer advance.
//   0x8    ADD ESP,0x8 at 0x00641e35, the caller-side cleanup of the direct
//          callee's two-word argument pair. Encoded by declaring that callee
//          __cdecl.
//
// A receiver record with bounds_only set states where the body was seen
// reaching and nothing more, so it is not an enumeration of the receiver's
// words and it cannot refute one. 0x20 agreeing with it is corroboration of
// that one displacement, not a layout.

#include "sporepedia_slot_release.hpp"

#include <cstring>

// The header states the conventions for consumers of the declaration; the same
// pair is repeated here so that the convention of the definition below is
// spelled in the translation unit that defines it. Both are guarded by the same
// condition, so the two definitions are identical and the redefinition is
// benign.
#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL __thiscall
#define PKG_SPOREPEDIA_SLOT_RELEASE_CDECL __cdecl
#else
#define PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL __attribute__((thiscall))
#define PKG_SPOREPEDIA_SLOT_RELEASE_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_sporepedia_slot_release {
namespace {

// A dword read at a machine displacement. The body performs exactly two reads
// of receiver words (0x00641e14) and one write (0x00641e1e); nothing here
// gives the word a type, a name or a meaning.
void *receiver_word(const unsigned char *base, std::size_t displacement) {
  void *word = nullptr;
  std::memcpy(&word, base + displacement, sizeof word);
  return word;
}

void store_receiver_word(unsigned char *base, std::size_t displacement,
                         void *value) {
  std::memcpy(base + displacement, &value, sizeof value);
}

// 0x00641e24  MOV EAX,dword ptr [ECX]
//
// The pointee's first word. It is read, never written, and the body never
// dereferences the value it holds: the word is used only as the base of the
// slot read that follows, so this is a load of one level and the slot read is a
// second. No machine record names the type behind it, so it is opaque here.
const OpaqueDispatchTable *vtable_of(const void *object) {
  const OpaqueDispatchTable *table = nullptr;
  std::memcpy(&table, object, sizeof table);
  return table;
}

// 0x00641e26  MOV EDX,dword ptr [EAX + 0x4]
//
// Displacement 4 of the dispatch word is the second dword of that block, which
// the model writes as index 1 (1 * 4 bytes = displacement 4). The index form is
// used so the read cannot be mistaken for a receiver displacement: the base here
// is the pointee's dispatch word, and the machine-derived receiver record --
// which enumerates 0x20 and no other displacement, for the receiver -- has no
// standing over a word inside the pointee. The value is transferred to control at
// 0x00641e29, so it is a code address; the record names neither the table nor
// the index, and the model asserts only the shape the two instructions have.
OpaqueSlotTarget slot_target_at(const OpaqueDispatchTable *vtable,
                                std::size_t slot_index) {
  OpaqueSlotTarget target = nullptr;
  std::memcpy(&target,
              reinterpret_cast<const unsigned char *>(vtable) +
                  slot_index * sizeof(OpaqueSlotTarget),
              sizeof target);
  return target;
}

}  // namespace

extern "C" unclassified_in_EAX PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL
sporepedia_dispatch_owned_slot_FUN_00641e10(void *receiver) {
  // 0x00641e12  MOV EDI,ECX
  unsigned char *const base = static_cast<unsigned char *>(receiver);

  // 0x00641e14  MOV ECX,dword ptr [EDI + 0x20]
  // 0x00641e17  LEA ESI,[EDI + 0x20]
  //
  // The word is read before the test and before the write, so the value tested
  // below is the one the body acts on, not one it produced. 0x20 is the only
  // displacement the machine-derived receiver record enumerates for this body.
  void *const owned = receiver_word(base, 0x20u);

  // 0x00641e1a  TEST ECX,ECX
  // 0x00641e1c  JZ 0x00641e2b
  //
  // The branch target is inside this body, and it skips the clear, the slot read
  // and the indirect transfer while still reaching the tail at 0x00641e2b. An
  // empty word therefore still runs the direct callee.
  if (owned != nullptr) {
    // 0x00641e1e  MOV dword ptr [ESI],0x0
    //
    // The word is cleared before the slot is read and before control is
    // transferred through it, so the receiver no longer holds the pointee while
    // the pointee's slot runs, and a re-entry into this body from that slot
    // would take the empty branch.
    store_receiver_word(base, 0x20u, nullptr);

    // 0x00641e24  MOV EAX,dword ptr [ECX]
    const OpaqueDispatchTable *const vtable = vtable_of(owned);

    // 0x00641e26  MOV EDX,dword ptr [EAX + 0x4]
    const OpaqueSlotTarget slot = slot_target_at(vtable, 1u);

    // 0x00641e29  CALL EDX
    //
    // The only indirect transfer in the body. ECX is untouched between
    // 0x00641e14 and here, so the pointee arrives as the receiver and nothing
    // is pushed; the body does not adjust ESP afterwards, so the transfer's own
    // convention has to leave the stack as it found it. What the slot is, and
    // what it does with the pointee, is not established by any record for this
    // target and is not modelled here.
    slot(owned);
  }

  // 0x00641e2b  PUSH ESI          second word of the pair: &receiver[0x20]
  // 0x00641e2c  ADD EDI,0x4        first word of the pair: receiver + 4. The
  //                                body only forms this address and hands it
  //                                over; it never reads or writes through it,
  //                                so it is not a receiver field, and the
  //                                receiver record's not enumerating 0x4 is
  //                                consistent with that rather than a conflict.
  // 0x00641e2f  PUSH EDI
  // 0x00641e30  CALL 0x005bf0e0
  // 0x00641e35  ADD ESP,0x8
  //
  // Reached from both the fall-through and the 0x00641e1c branch, so the direct
  // callee runs once per call whatever the state of the word. ADD ESP,0x8 is the
  // caller dropping that pair, which is what makes the callee __cdecl in the
  // header; nothing in the body itself adjusts the stack around the transfer.
  // Its return is the last value this body leaves in EAX, which is why the
  // declared return type is the ABI record's own unclassified word: the body
  // does not classify it, and the record does not either.
  return FUN_005bf0e0(base + 4u, base + 0x20u);
}

}  // namespace openspore::reconstruction::pkg_sporepedia_slot_release
