// PKG-SPOREPEDIA-OWNED-SLOT-NOTIFY -- VA 0x00ec3bc0
// Sporepedia, sporepedia-online cluster (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Machine listing, 13 instructions, body 0x00ec3bc0..0x00ec3bdd inclusive
// (Ghidra body_end 0x00ec3bdd, body_span_bytes 30). Every line of the model
// below is annotated with the instruction it comes from.
//
//   00ec3bc0  PUSH ESI
//   00ec3bc1  MOV ESI,ECX                 the receiver alias
//   00ec3bc3  CALL 0x00641e10              the first direct transfer
//   00ec3bc8  MOV EAX,dword ptr [ESI + 0x20]   the receiver's word at 0x20
//   00ec3bcd  JZ 0x00ec3bdc                -> the tail, skipping the block
//   00ec3bcf  SUB ESI,-0x80                the address receiver + 0x80
//   00ec3bd2  PUSH ESI                     second word of the pair
//   00ec3bd3  PUSH EAX                     first word of the pair
//   00ec3bd4  CALL 0x00eec760              the second direct transfer
//   00ec3bd9  ADD ESP,0x8                  caller-cleaned two words
//   00ec3bdc  POP ESI
//   00ec3bdd  RET
//
// The two TEST/JZ at 0x00ec3bcb/0x00ec3bcd (TEST EAX,EAX is elided above only to
// keep the annotation short) test that one word and nothing else.
//
// ABI, machine-derived: __thiscall. The receiver arrives in ECX, is aliased into
// ESI at 0x00ec3bc1 and dereferenced through that alias before any definite write
// to it; the terminator is a bare RET at 0x00ec3bdd with no immediate and no
// stack reads, so the caller owns the stack. Nothing in the body pushes an
// ordinary argument of its own: the only two pushes, 0x00ec3bd2 and 0x00ec3bd3,
// are the argument pair of the second direct callee and are consumed by the
// ADD ESP,0x8 at 0x00ec3bd9.
//
// There are exactly two transfers and both are direct immediates, which is what
// the xref export records for the two outgoing edges of this body:
// 0x00641e10 at 0x00ec3bc3 and 0x00eec760 at 0x00ec3bd4. No transfer in the body
// is computed: abi_derived.dispatch records indirect_calls=0 and the listing has
// no register- or memory-operand transfer, so this file declares no slot
// boundary of any kind.
//
// The receiver is addressed only through machine displacements, and no member is
// named, because no record for this target says which member any of them is.
// The machine-derived receiver record enumerates exactly one displacement, 0x20,
// and it was observed through the ESI alias rather than through ECX's own
// operands; 0x80 is the base adjustment at 0x00ec3bcf, so the address the second
// callee receives is written in decimal below. Both facts are stated so the
// reader can see that nothing was dropped.

#include "sporepedia_owned_slot_notify_types.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_sporepedia_owned_slot_notify {
namespace {

// 0x00ec3bc8  MOV EAX,dword ptr [ESI + 0x20]
//
// A dword read at a machine displacement. The body reads one receiver word and
// writes none, and nothing here gives that word a type, a name or a meaning; the
// pointer type it is returned as is the use 0x00ec3bd3 makes of it, not a claim
// about the memory it names.
OpaqueOwnedBlock *load_pointer_word(const void *address) {
  OpaqueOwnedBlock *word = nullptr;
  std::memcpy(&word, address, sizeof word);
  return word;
}

}  // namespace

extern "C" unclassified_in_EAX PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_THISCALL
sporepedia_owned_slot_notify_FUN_00ec3bc0(void *receiver) {
  // 0x00ec3bc1  MOV ESI,ECX
  unsigned char *const base = static_cast<unsigned char *>(receiver);

  // 0x00ec3bc3  CALL 0x00641e10
  //
  // The first direct transfer, and the only one that runs before this body reads
  // anything of its own. ECX still holds the receiver here, nothing is pushed,
  // and the call leaves the stack exactly as it found it.
  //
  // Cross-target note, deliberately kept out of the model below: the staged
  // candidate for 0x00641e10
  // (reconstruction/metadata/pkg-sporepedia-slot-release/00641e10.json) writes
  // zero into the receiver's word at displacement 0x20 at 0x00641e1e, and it does
  // so before it reads the pointee's dispatch word and before it calls its own
  // two-word helper at 0x005bf0e0. If that reading of the sibling is right and the
  // two bodies do share a receiver, then the word this body goes on to test has
  // already been zeroed and the JZ below is the taken path. Two things stop that
  // from being a claim here: nothing in any record for THIS target shows the two
  // bodies share a receiver, and the sibling landed an honest WARN (its own
  // indirect transfer does not resolve), so its candidate is unconfirmed. The
  // read and the branch below are therefore modelled from this listing alone and
  // left to stand on their own; the question is carried in the sidecar's
  // unresolved_questions rather than resolved here.
  slot_release_00641e10(receiver);

  // 0x00ec3bc8  MOV EAX,dword ptr [ESI + 0x20]
  //
  // The word is read after the call above and tested immediately, so the value
  // this body acts on is the one the call left in the receiver, not one this
  // body produced. 0x20 is the only displacement the machine-derived receiver
  // record enumerates for this body.
  OpaqueOwnedBlock *const owned = load_pointer_word(base + 0x20u);

  // 0x00ec3bcb  TEST EAX,EAX
  // 0x00ec3bcd  JZ 0x00ec3bdc
  //
  // The branch target is inside this body and lands on the shared tail at
  // 0x00ec3bdc, so an empty word skips the whole block and still pops the saved
  // ESI and returns.
  if (owned != nullptr) {
    // 0x00ec3bcf  SUB ESI,-0x80
    // 0x00ec3bd2  PUSH ESI
    // 0x00ec3bd3  PUSH EAX
    //
    // ESI stops being the receiver alias here: the instruction adds 128 to it
    // and the result is the address handed to the callee as its second
    // argument. The body never dereferences that address itself -- the live
    // decompilation of 0x00eec760 is what writes through it -- so it is a base
    // adjustment rather than a receiver field, and it is spelled in decimal for
    // the same reason. EAX, pushed last, is the first argument, and it is the
    // word read above rather than a value this body computed.
    //
    // 0x00ec3bd4  CALL 0x00eec760
    // 0x00ec3bd9  ADD ESP,0x8
    //
    // The second direct transfer, caller-cleaned, taking exactly those two
    // words. Its return is the last value this body leaves in EAX, which is
    // why the declared return type is the ABI record's own unclassified word:
    // the body does not classify it and neither does the record.
    return sporepedia_bounds_fill_00eec760(owned,
                                           reinterpret_cast<BoundsWords *>(base + 128u));
  }

  // 0x00ec3bdc  POP ESI
  // 0x00ec3bdd  RET
  //
  // EAX still holds the word the TEST just examined, and this path is only
  // reached when that word was zero, so the word returned here is zero. The
  // body classifies nothing about it either way.
  return 0u;
}

}  // namespace openspore::reconstruction::pkg_sporepedia_owned_slot_notify
