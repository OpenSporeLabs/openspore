// PKG-DFW-006A14D0 -- VA 0x006a14d0
// App::PropertyList::CopyAllPropertiesFrom
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, image base 0x00400000)
//
// Machine listing, 25 instructions, body 0x006a14d0..0x006a1506 inclusive
// (Ghidra body_end 0x006a1508 exclusive, body_span_bytes 57, image base 0x00400000,
// rva 0x2a14d0, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e). Read live
// from the GhidraMCP bridge at 127.0.0.1:8089 and cross-checked against the
// persisted pack reconstruction/evidence/006a14d0/evidence.json, whose disassembly
// category carries the same 25 instructions.
//
//   006a14d0  PUSH ESI
//   006a14d1  PUSH EDI
//   006a14d2  MOV EDI,dword ptr [ESP + 0xc]
//   006a14d6  MOV ESI,ECX
//   006a14d8  CMP ESI,EDI
//   006a14da  JZ 0x006a1504
//   006a14dc  MOV ECX,dword ptr [ESI + 0x30]
//   006a14df  TEST ECX,ECX
//   006a14e1  JZ 0x006a14f1
//   006a14e3  MOV dword ptr [ESI + 0x30],0x0
//   006a14ea  MOV EAX,dword ptr [ECX]
//   006a14ec  MOV EDX,dword ptr [EAX + 0x4]
//   006a14ef  CALL EDX
//   006a14f1  MOV EAX,dword ptr [ESI]
//   006a14f3  MOV EDX,dword ptr [EAX + 0x48]
//   006a14f6  MOV ECX,ESI
//   006a14f8  CALL EDX
//   006a14fa  MOV EAX,dword ptr [ESI]
//   006a14fc  MOV EDX,dword ptr [EAX + 0x38]
//   006a14ff  PUSH EDI
//   006a1500  MOV ECX,ESI
//   006a1502  CALL EDX
//   006a1504  POP EDI
//   006a1505  POP ESI
//   006a1506  RET 0x4
//
// Structure, in the order the listing fixes it:
//
//   * A self-reference refuses the whole operation. 0x006a14d8/0x006a14da compare
//     the receiver against the single ordinary stack argument and branch straight
//     to the epilogue at 0x006a1504. The comparison is pointer identity and
//     nothing else: no alias test, no range test, no offset adjustment appears
//     anywhere in the 25 instructions. A self-reference dispatches nothing at all.
//
//   * The receiver's word at displacement 0x30 is detached before it is used.
//     0x006a14dc loads it into ECX, 0x006a14df/0x006a14e1 skip the whole block
//     when it is zero, and 0x006a14e3 stores zero back at the same displacement
//     BEFORE the dispatch at 0x006a14ef. The order is observable: an observer of
//     that dispatch sees the receiver's word already cleared. A null word skips
//     the store as well as the dispatch, and the store is the body's only write.
//
//   * The dispatch at 0x006a14ef is made ON THE HELD OBJECT, not on the receiver.
//     ECX still holds the word loaded at 0x006a14dc and nothing overwrote it, so
//     the three instructions 0x006a14ea/0x006a14ec/0x006a14ef read the held
//     object's own table and transfer control to that table's word at
//     displacement 0x4. No stack word is pushed.
//
//   * The next two dispatches are both made on the RECEIVER, and the body re-reads
//     the receiver's table for each: 0x006a14f1 reads dword ptr [ESI] for the
//     0x006a14f3 read of displacement 0x48, and 0x006a14fa reads dword ptr [ESI]
//     again for the 0x006a14fc read of displacement 0x38. Only the third is given
//     an argument, the single PUSH EDI at 0x006a14ff. The second read is a real
//     re-read in the listing, so a model that cached the table pointer would be
//     wrong in a way this test can see.
//
//   * Reaching 0x006a14f1 is unconditional on every non-self-reference path, so
//     both receiver dispatches happen on every path that gets past the guard.
//
// The table displacements are named constants below rather than inline literals,
// and that is a statement about what they are rather than a presentation choice:
// 0x4, 0x38 and 0x48 are indices into a table this body READS, not displacements
// into the receiver, and writing them as receiver-style "+ 0x4" expressions would
// claim the receiver owns words there. The machine-derived receiver record for
// this target enumerates exactly two displacements, 0x0 and 0x30, and the only
// displacement this body applies to the receiver is written inline as 0x30, in
// the listing's own spelling, because that is what the machine says.
//
// Vtable placement, read live as raw bytes and decoded as 4-byte words. This body
// is installed at displacement 0x34 in two table images, which is what makes it
// shared rather than duplicated:
//
//   table 0x01408820  +0x04 = 0x00432b50   +0x34 = 0x006a14d0 (this body)
//                     +0x38 = 0x006a1510   +0x48 = 0x006a2a80
//                     +0x4c = 0x00000000, a null terminator
//   table 0x01408870  +0x04 = 0x00432b50   +0x34 = 0x006a14d0 (this body)
//                     +0x38 = 0x006a1510   +0x48 = 0x006a2b20
//                     +0x4c begins the byte string "App/cDirectPropertyL", so this
//                     image has no null terminator; the name follows the last slot
//
// Ghidra names 0x006a2a80 "App::PropertyList::Clear" and 0x006a2b20
// "App::DirectPropertyList::Clear". Those names are imported from the SDK symbol
// XML, not read out of the binary, so this file uses them only to say that the two
// images carry DIFFERENT code at displacement 0x48 -- a fact read out of the bytes,
// independent of either name -- and not to attach a class to either.
//
// The record's vtables list also contains "vtable:0x00432b50" and
// "vtable:0x006a14d0". Both are artifacts of a vtable scan that treated a code
// address sitting in a slot, and this function's own address sitting in another
// class's slot, as the start of a table. Neither is a table this body dispatches
// through, and nothing here is built on either.
//
// Return semantics. The declared return type is void, which is the record's own
// token: the knowledge index carries types = ["void"] and the resolved Ghidra
// prototype is "void App::PropertyList::CopyAllPropertiesFrom(...)". No path writes
// a value into EAX that the epilogue hands on. EAX's last writes on the longest
// path are the two table-pointer reads at 0x006a14f1 and 0x006a14fa, the three
// slot-word reads at 0x006a14ec/0x006a14f3/0x006a14fc, and the dead results of
// the three dispatched callees; 0x006a1504, 0x006a1505 and 0x006a1506 do not touch
// it. On the self-reference path EAX is not written at all, so it still holds
// whatever the caller left there, which is another reason this is void and not a
// register word the body means to return.

#include "dfw_006a14d0_types.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_dfw_006a14d0 {
namespace {

// Table displacements, in the listing's own spelling. See the file header: these
// index a table this body reads, not the receiver.
constexpr std::size_t kSlotOfHeldWord = 0x4;    // 0x006a14ec  MOV EDX,dword ptr [EAX + 0x4]
constexpr std::size_t kSlotOfThirdCall = 0x38;  // 0x006a14fc  MOV EDX,dword ptr [EAX + 0x38]
constexpr std::size_t kSlotOfSecondCall = 0x48; // 0x006a14f3  MOV EDX,dword ptr [EAX + 0x48]

// A 4-byte read of an arbitrary address, by memcpy so no object type is claimed
// for the memory. The listing's own shape: every datum this body reads is a
// 4-byte word and is only ever treated as a word.
void *read_word(const void *address) {
  void *word = nullptr;
  std::memcpy(&word, address, sizeof word);
  return word;
}

// A 4-byte write of null to an arbitrary address, by memcpy for the same reason.
// The listing's shape: 0x006a14e3 writes exactly one dword, of the value zero.
void write_null_word(void *address) {
  void *const zero = nullptr;
  std::memcpy(address, &zero, sizeof zero);
}

// Addressing a displacement inside an opaque block. Both boundary types are
// deliberately incomplete, so pointer arithmetic on them is not available and
// every access goes through a byte address instead -- which is also the only way
// to state an access that claims no member.
const void *at_word(const void *base, std::size_t displacement) {
  return static_cast<const unsigned char *>(base) + displacement;
}

}  // namespace

extern "C" void PKG_DFW_006A14D0_THISCALL
app_property_list_CopyAllPropertiesFrom_006a14d0(OpaquePropertyList *receiver, OpaquePropertyList *other) {
  // 0x006a14d0  PUSH ESI
  // 0x006a14d1  PUSH EDI
  //
  // The prologue saves the two scratch registers the body then uses. There is no
  // C-level counterpart to model and none is invented: the two words are restored
  // by the POP EDI / POP ESI pair at 0x006a1504/0x006a1505, which is reached from
  // every path including the self-reference refusal below, so the pair is balanced
  // in every case. The two pushes are also why 0x006a14d2 reads its argument at
  // [ESP + 0xc] rather than at [ESP + 0x4]: entry_ESP+0x4 plus the eight bytes
  // pushed here. The ABI record states the same arithmetic.
  unsigned char *const base = reinterpret_cast<unsigned char *>(receiver);

  // 0x006a14d2  MOV EDI,dword ptr [ESP + 0xc]   the one ordinary stack argument
  // 0x006a14d6  MOV ESI,ECX                     the receiver, aliased out of ECX
  //
  // EDI takes the argument and ESI takes the receiver, and the two are compared
  // against each other on the next instruction, so the two roles are kept in two
  // separate locals here for the same reason the machine keeps them in two
  // registers.

  // 0x006a14d8  CMP ESI,EDI
  // 0x006a14da  JZ 0x006a1504
  //
  // Pointer identity, and the branch target is the epilogue rather than a body
  // block, so the whole operation is refused: no word is read from the receiver, no
  // store happens and none of the three dispatches is made. Nothing below is
  // reached, so nothing below has to be undone on the way out.
  if (receiver == other) {
    return;
  }

  // 0x006a14dc  MOV ECX,dword ptr [ESI + 0x30]
  //
  // The body's only read through a receiver displacement other than zero, and its
  // only write. It is written inline as 0x30 rather than through a named constant
  // because that is the machine displacement, transcribed; the header explains why
  // the three table displacements are treated differently.
  OpaqueVtableObject *const held =
      static_cast<OpaqueVtableObject *>(read_word(base + 0x30u));

  // 0x006a14df  TEST ECX,ECX
  // 0x006a14e1  JZ 0x006a14f1
  //
  // The branch target is 0x006a14f1, the receiver's own first dispatch, and not
  // the store below. So a null word skips the store AND the dispatch together: the
  // receiver's word at 0x30 is left exactly as it was found, which is a claim
  // about the store, and the block below runs unconditionally on the other path.
  if (held != nullptr) {
    // 0x006a14e3  MOV dword ptr [ESI + 0x30],0x0
    //
    // The detach, and the ordering is load-bearing. The store precedes the dispatch
    // at 0x006a14ef, so anything reached through that dispatch sees the receiver's
    // word already zero. The evidence pack carries this as an observable whose
    // motivation is not established: 0x00432b50's own listing shows no path that
    // reads a child's word at 0x30, so why the order is this way is not claimed
    // here. The order itself is in the listing and is modelled.
    write_null_word(base + 0x30u);

    // 0x006a14ea  MOV EAX,dword ptr [ECX]
    // 0x006a14ec  MOV EDX,dword ptr [EAX + 0x4]
    // 0x006a14ef  CALL EDX
    //
    // Dispatched ON THE HELD OBJECT, not on the receiver. ECX still holds the word
    // read at 0x006a14dc; the store just above wrote through the receiver, not
    // through ECX, so nothing has replaced it. No stack word is pushed, and both
    // table images this body is installed in hold 0x00432b50 at displacement 0x04,
    // whose own listing spills ECX as its receiver (0x00432b56) and returns with a
    // bare RET and no stack adjustment (0x00432bd9) -- which is what a call with
    // nothing pushed requires. The transfer is modelled as the address being handed
    // to a bridge; the header says why.
    void *const held_vtable = read_word(held);
    dispatch_through_slot_0(read_word(at_word(held_vtable, kSlotOfHeldWord)), held);
  }

  // 0x006a14f1  MOV EAX,dword ptr [ESI]
  // 0x006a14f3  MOV EDX,dword ptr [EAX + 0x48]
  // 0x006a14f6  MOV ECX,ESI
  // 0x006a14f8  CALL EDX
  //
  // Dispatched on the RECEIVER, with ECX reloaded from the ESI alias first, and
  // with nothing pushed. This is reached both by falling out of the block above and
  // by jumping here from 0x006a14e1, so it runs on every path past the guard. The
  // two table images disagree at this displacement (0x006a2a80 against 0x006a2b20),
  // so this is the step the body is genuinely polymorphic in, and both of those
  // callees end in a bare RET with no stack adjustment (0x006a2acb and
  // 0x006a2b76), which is what this call shape requires.
  void *const receiver_vtable = read_word(receiver);
  dispatch_through_slot_0(
      read_word(at_word(receiver_vtable, kSlotOfSecondCall)), receiver);

  // 0x006a14fa  MOV EAX,dword ptr [ESI]
  // 0x006a14fc  MOV EDX,dword ptr [EAX + 0x38]
  // 0x006a14ff  PUSH EDI
  // 0x006a1500  MOV ECX,ESI
  // 0x006a1502  CALL EDX
  //
  // Dispatched on the RECEIVER again, through a SECOND read of the receiver's table
  // pointer: 0x006a14fa repeats the 0x006a14f1 read rather than reusing its result,
  // so whether that matters is a question about what ran in between, not about this
  // body. It is modelled as a re-read because that is what the listing does, and
  // nothing is claimed about whether the receiver's table can change here.
  //
  // The single stack word is the ordinary argument, and it is the same value the
  // guard compared against: the source, not a copy of it and not the receiver. Both
  // table images hold the same 0x006a1510 at this displacement, and that callee
  // ends in RET 0x4 (0x006a1533) after reading its own argument at [ESP + 0xc]
  // (0x006a1512) -- a callee-cleaned single stack word, which is exactly what the
  // PUSH at 0x006a14ff sets up, and is why this body can leave that push to the
  // callee.
  void *const receiver_vtable_again = read_word(receiver);
  dispatch_through_slot_1(
      read_word(at_word(receiver_vtable_again, kSlotOfThirdCall)), receiver, other);

  // 0x006a1504  POP EDI
  // 0x006a1505  POP ESI
  // 0x006a1506  RET 0x4
  //
  // The epilogue, shared with the self-reference path. EAX is not touched, so no
  // return value is produced on this path or on that one, and RET 0x4 pops the one
  // ordinary stack word the caller pushed -- the callee owns the cleanup, which is
  // the second half of the machine basis for the callee-cleaned __thiscall the
  // header declares.
}

}  // namespace openspore::reconstruction::pkg_dfw_006a14d0
