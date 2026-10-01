// PKG-PROPMANAGER-CREATE-WAVE15 -- VA 0x006a3330
// App::cPropManager::CreateResource
// SPORE/SporeBin/SporeApp.exe, 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// Machine listing: 77 instructions, body 0x006a3330..0x006a33f9 inclusive
// (reconstruction/evidence/006a3330/evidence.json :: categories.disassembly).
// Every statement below names the instruction it comes from, so the source and
// the listing can be compared line by line.
//
// ABI, machine-derived (categories.abi): __thiscall. The receiver arrives in
// ECX and is copied to EBX at 0x006a3356 (MOV EBX,ECX); every later receiver
// access goes through that alias, which is why a literal scan of the listing for
// ECX operands finds no displacement at all. Four ordinary stack dwords are
// read, at entry_ESP+0x8, +0xc, +0x10 and +0x14, none of them written. The
// terminator is RET 0x10 at 0x006a33da and again at 0x006a33f9, so this callee
// owns sixteen bytes of cleanup, which rules cdecl and fastcall out and makes
// __thiscall the only convention consistent with the epilogue. The machine
// record lists only two of the four slots and abstained from the rest
// ("flow_not_modelled", "slot_gaps_present"), so the four-slot reading is taken
// from the listing's own [ESP + 0x20] / +0x24 / +0x28 / +0x2c operands rather
// than from the record.
//
// Control flow: two conditional branches, JZ 0x006a337a at 0x006a336a and
// JZ 0x006a33dd at 0x006a33b9, both with targets inside this body. The listing
// is closed.
//
// Calls: exactly the two CALL immediates the xref export records as out-edges
// from this record, 0x00f473a0 at 0x006a3358 and 0x006a1b90 at 0x006a3373, and
// no JMP anywhere in the body, so there is no tail call to name. The four
// register-indirect transfers are the virtual dispatch and are modelled through
// function-pointer locals; no record in this repository names what any of the
// four slots holds.
//
// Globals: the listing names two data-segment addresses, 0x1408b44 (pushed as
// the second word of the factory call) and 0x1408b34 (pushed as the single word
// of the 0x006a1b90 call). The xref export records data_reference_count 0 for
// this record and carries no data-reference edge type at all, so no second
// machine side corroborates either address through the export, and no record
// types either one. A direct byte read of the same binary at the two addresses
// is recorded beside each push below; that read is new evidence, not an export
// edge, so it does not and cannot move the GLOBALS check off WARN. The
// addresses are given no name, no declared type and no meaning beyond what the
// bytes at them are.

#include "prop_manager_create_resource_006a3330.hpp"

namespace openspore::reconstruction::pkg_propmanager_create_wave15 {

namespace {

// Byte-wise word load at a machine displacement. Displacements are passed in as
// values rather than written inline as `object + n` so that this body asserts
// no member layout: the machine-derived receiver record is a set of
// displacements observed through ECX (offsets [0], bounds_only true), not a
// field list, and no record in this repository names a member for any word this
// body touches.
template <typename Value>
Value load_word(const void* object, TargetWord offset) {
  const auto* base = static_cast<const unsigned char*>(object);
  unsigned char bytes[sizeof(Value)];
  for (TargetWord index = 0; index < sizeof(Value); ++index) {
    bytes[index] = base[index + offset];
  }
  Value value;
  auto* destination = reinterpret_cast<unsigned char*>(&value);
  for (TargetWord index = 0; index < sizeof(Value); ++index) {
    destination[index] = bytes[index];
  }
  return value;
}

// The table word is read as a table, and the slot is read out of the table --
// two separate machine steps (e.g. 0x006a337e then 0x006a3380), kept as two.
template <typename Function>
Function load_slot(const void* table, TargetWord offset) {
  return load_word<Function>(table, offset);
}

void store_word(void* object, TargetWord offset, TargetWord value) {
  auto* base = static_cast<unsigned char*>(object);
  for (TargetWord index = 0; index < sizeof(TargetWord); ++index) {
    base[index + offset] = static_cast<unsigned char>(value >> (8 * index));
  }
}

}  // namespace

extern "C" bool __thiscall
app_prop_manager_create_resource_006a3330(OpaquePropManager* receiver,
                                          OpaqueSourceObject* source,
                                          void** created_out,
                                          void* apply_second,
                                          TargetWord apply_fourth) {
  // 0x006a3330 PUSH -0x1
  // 0x006a3332 PUSH 0x120d70a
  // 0x006a3337 MOV EAX,FS:[0x0]
  // 0x006a333d PUSH EAX
  // 0x006a333e MOV dword ptr FS:[0x0],ESP
  //   The body opens a two-word record on the FS chain before it touches
  //   anything else: the scope table, then the displaced chain word. The
  //   companion state word is the one 0x006a3364 and 0x006a3385 rewrite. The
  //   record is spelled as two opaque words, not as a C++ try block: the listing
  //   contains no catch clause, no landing pad and no scope table read, and no
  //   record in this repository names the scope table.
  const TargetWord scope_table = 0x120d70a;
  TargetWord scope_state = kScopeStateUnwind;
  const TargetWord displaced_chain = enter_scope_frame(scope_table, scope_state);

  // 0x006a3345 PUSH ECX
  // 0x006a3346 PUSH EBX
  // 0x006a3347 PUSH ESI
  // 0x006a3348 PUSH EDI
  //   Four saved registers, restored by the POP EDI / POP ESI / POP EBX pairs at
  //   0x006a33c7..0x006a33cb on the success path and at 0x006a33ea..0x006a33ee
  //   on the failure path. EBX is then reused as the receiver alias and the
  //   saved copy is dead, so only the ECX slot is read back, at 0x006a33cc and
  //   at 0x006a33e6.
  //
  // 0x006a3349 XOR ESI,ESI
  //   The object the rest of the body works on starts as a null word. It is
  //   overwritten at 0x006a3378 only when the factory call succeeded, so the
  //   null can survive into the writes at 0x006a3391..0x006a33a1; this body
  //   contains no test of it, and neither does the reconstruction.
  OpaqueResource* created = nullptr;

  // 0x006a334b PUSH ESI
  // 0x006a334c PUSH ESI
  // 0x006a334d PUSH ESI
  // 0x006a334e PUSH ESI
  // 0x006a334f PUSH 0x1408b44
  // 0x006a3354 PUSH 0x38
  // 0x006a3356 MOV EBX,ECX
  //   The receiver alias, taken before the call so the call cannot lose it.
  OpaquePropManager* const self = receiver;

  // 0x006a3358 CALL 0x00f473a0
  //   Six words: the constant 0x38, the data-segment address 0x1408b44, and
  //   four null words from the pushes above. The receiver is not passed, and
  //   ECX still holds this function's own receiver when the transfer is made.
  //   Nothing in this repository says what the factory is or what the 0x38 is
  //   measured in; both are passed on as the listing passes them.
  //
  //   The address 0x1408b44 is a data-segment address the body PUSHes, i.e. the
  //   value passed is the address itself, not what lives there. A byte read of
  //   the same binary (GhidraMCP /read_memory, length 64, recorded in the
  //   package sidecar) returns at 0x1408b44 the 23 bytes 41 70 70 2f 50 72 6f
  //   70 65 72 74 79 4c 69 73 74 2f 43 72 65 61 74 65 00 -- a NUL-terminated
  //   ASCII literal spelling App/PropertyList/Create. That is what the bytes at
  //   the address are, read straight from this exact binary; nothing in the
  //   record types the object, so no C++ type is declared for it here and the
  //   address is still passed as the bare word the listing pushes.
  //
  // 0x006a335d ADD ESP,0x18
  //   Twenty-four bytes, six words, cleaned here: this target does not own the
  //   cleanup of its own arguments.
  void* const handle = prop_list_factory_00f473a0(0x38,
                                                 0x1408b44,
                                                 0,
                                                 0,
                                                 0,
                                                 0);

  // 0x006a3360 MOV dword ptr [ESP + 0xc],EAX
  //   The factory's result is parked in a frame slot, the one the four saved
  //   registers left behind. It is read again at 0x006a336c only if the test
  //   below falls through.
  //
  // 0x006a3364 MOV dword ptr [ESP + 0x18],ESI
  //   The state word, set to the null word this body started from.
  scope_state = 0;

  // 0x006a3368 CMP EAX,ESI
  // 0x006a336a JZ 0x006a337a
  //   A null factory result skips the single transfer below and lands on the
  //   block that starts at 0x006a337a with `created` still null.
  if (handle != nullptr) {
    // 0x006a336c PUSH 0x1408b34
    // 0x006a3371 MOV ECX,EAX
    // 0x006a3373 CALL 0x006a1b90
    //   One data-segment address and the factory's result in ECX. The address is
    //   the second of the two the body names. A byte read of the same binary
    //   (GhidraMCP /read_memory, length 64, recorded in the package sidecar)
    //   returns at 0x1408b34 the 15 bytes 43 72 65 61 74 65 52 65 73 6f 75 72
    //   63 65 00 -- a NUL-terminated ASCII literal spelling CreateResource,
    //   followed by two zero pad bytes before 0x1408b44 begins. The two
    //   literals are adjacent in the data segment and the body pushes the
    //   second one where it pushes the first. Again: the bytes at the address
    //   are a read fact, the object type is not established, and the address is
    //   passed on as the bare word the listing pushes.
    //
    // 0x006a3378 MOV ESI,EAX
    //   The object every later access in this body is made through.
    created = reinterpret_cast<OpaqueResource*>(create_named_006a1b90(
        handle, 0x1408b34));
  }

  // 0x006a337a MOV EDI,dword ptr [ESP + 0x20]
  //   entry_ESP+0x8: the first ordinary stack argument, hoisted once and used
  //   twice -- as the receiver of the transfer below and as one of the four
  //   words handed to the transfer after it. 24 bytes above ESP here: four
  //   saved registers, three scope words, and the return address.
  OpaqueSourceObject* const source_object = source;

  // 0x006a337e MOV EAX,dword ptr [EDI]
  // 0x006a3380 MOV EDX,dword ptr [EAX + 0x10]
  //   The table word of that argument at displacement 0, then the slot word at
  //   byte displacement 0x10 of it. No record names either member; the shape is
  //   a table and a slot in it, and that is all that is claimed.
  //
  // 0x006a3383 MOV ECX,EDI
  //   The argument object becomes the callee's receiver.
  //
  // 0x006a3385 MOV dword ptr [ESP + 0x18],0xffffffff
  //   The state word is put back to the value the prologue pushed.
  scope_state = kScopeStateUnwind;

  // 0x006a338d CALL EDX
  //   Dispatch site one of four. Register-indirect, no stack word, receiver in
  //   ECX. The result is a pointer the three reads below are made through.
  OpaqueDescriptor* const descriptor =
      load_slot<SlotAt10>(load_word<void*>(source_object, 0), 0x10)(source_object);

  // 0x006a338f MOV ECX,dword ptr [EAX]
  // 0x006a3391 MOV dword ptr [ESI + 0x8],ECX
  // 0x006a3394 MOV EDX,dword ptr [EAX + 0x4]
  // 0x006a3397 MOV ECX,dword ptr [ESP + 0x28]
  // 0x006a339b MOV dword ptr [ESI + 0xc],EDX
  // 0x006a339e MOV EAX,dword ptr [EAX + 0x8]
  // 0x006a33a1 MOV dword ptr [ESI + 0x10],EAX
  //   Three words copied out of the descriptor and into the object, at byte
  //   displacements 0x8, 0xc and 0x10 of the destination and 0x0, 0x4 and 0x8
  //   of the source. They are interleaved in the listing, and the interleaving
  //   is preserved here because the 0x006a3397 load in the middle of it is a
  //   stack argument for the transfer after this block. No record names any of
  //   the six words; they are copied as they are read.
  store_word(created, 0x8, load_word<TargetWord>(descriptor, 0x0));
  store_word(created, 0xc, load_word<TargetWord>(descriptor, 0x4));
  store_word(created, 0x10, load_word<TargetWord>(descriptor, 0x8));

  // 0x006a3397 MOV ECX,dword ptr [ESP + 0x28]
  //   The entry_ESP+0x10 word is hoisted here, in the middle of the three
  //   stores above, and kept until it is pushed at 0x006a33ae. Its value is
  //   never inspected; it is only carried to the transfer below.

  // 0x006a33a4 MOV EAX,dword ptr [ESP + 0x2c]
  //   entry_ESP+0x14, the fourth ordinary stack argument, the last of the four
  //   words this transfer is handed.
  //
  // 0x006a33a8 MOV EDX,dword ptr [EBX]
  // 0x006a33aa MOV EDX,dword ptr [EDX + 0x24]
  //   The one access this body makes to its own receiver: the table word at
  //   displacement 0 through the EBX alias, then the slot word at byte
  //   displacement 0x24 of it. This is the only receiver displacement the
  //   machine record enumerates, and it enumerates it because of this alias --
  //   ECX itself is never used as a memory base in the listing.
  //
  // 0x006a33ad PUSH EAX
  // 0x006a33ae PUSH ECX
  // 0x006a33af PUSH ESI
  // 0x006a33b0 PUSH EDI
  //   Four words, pushed in that order, so the callee sees the entry_ESP+0x10
  //   word first and the entry_ESP+0x8 object last.
  //
  // 0x006a33b1 MOV ECX,EBX
  //   The receiver alias becomes the callee's receiver.
  //
  // 0x006a33b3 CALL EDX
  //   Dispatch site two of four. Register-indirect, four stack words, receiver
  //   in ECX. No record names the target; the four words are handed on in the
  //   order the pushes put them, and the frame is balanced across the transfer,
  //   so the callee owns the cleanup of the four -- the reason this slot's type
  //   is declared __thiscall rather than caller-cleanup.
  const int applied = load_slot<SlotAt24>(load_word<void*>(self, 0), 0x24)(
      self, source_object, created, apply_second, apply_fourth);

  // 0x006a33b5 MOV ECX,ESI
  //   A write to the receiver register that no later instruction reads:
  //   0x006a33c7..0x006a33cc take their words from the stack, not from ECX, and
  //   the same is true of the failure path at 0x006a33e6. It is reproduced as a
  //   note rather than as a statement, because a C++ reconstruction has nowhere
  //   to put a write whose value is never observed.
  //
  // 0x006a33b7 TEST AL,AL
  // 0x006a33b9 JZ 0x006a33dd
  //   The low byte of the transfer's result decides the two exits. Only AL is
  //   tested, so only AL is claimed to be meaningful about the return word.
  if (applied != 0) {
    // 0x006a33bb MOV EAX,dword ptr [ESP + 0x24]
    // 0x006a33bf MOV dword ptr [EAX],ESI
    //   entry_ESP+0xc is written through: the object this body built is stored
    //   into the word the caller supplied. This is the only write through that
    //   argument anywhere in the body.
    store_word(created_out, 0, reinterpret_cast<TargetWord>(created));

    // 0x006a33c1 MOV EDX,dword ptr [ESI]
    // 0x006a33c3 MOV EAX,dword ptr [EDX]
    // 0x006a33c5 CALL EAX
    //   Dispatch site three of four. The table word of the object just stored
    //   through, and its entry at displacement 0. The body reads nothing the
    //   transfer returns.
    load_slot<SlotAt00>(load_word<void*>(created, 0), 0)(created);

    // 0x006a33c7 POP EDI
    // 0x006a33c8 POP ESI
    // 0x006a33c9 MOV AL,0x1
    // 0x006a33cb POP EBX
    // 0x006a33cc MOV ECX,dword ptr [ESP + 0x4]
    // 0x006a33d0 MOV dword ptr FS:[0x0],ECX
    // 0x006a33d7 ADD ESP,0x10
    // 0x006a33da RET 0x10
    //   The result byte is set to 1 and the chain word this prologue displaced
    //   is put back before sixteen bytes of frame and arguments are released.
    //   Only AL is written, so the upper three bytes of the returned word are
    //   whatever the last transfer left there; the reconstruction returns a
    //   bool, which is the only reading the two exits support.
    leave_scope_frame(displaced_chain);
    return true;
  }

  // 0x006a33dd MOV EDX,dword ptr [ESI]
  // 0x006a33df MOV EAX,dword ptr [EDX + 0x8]
  // 0x006a33e2 PUSH 0x1
  // 0x006a33e4 CALL EAX
  //   Dispatch site four of four, on the failure path only: the same table, one
  //   entry further in, handed the immediate word 1. Nothing the body holds is
  //   passed besides that word, and nothing the transfer returns is read.
  load_slot<SlotAt08>(load_word<void*>(created, 0), 0x8)(created, 0x1);

  // 0x006a33e6 MOV ECX,dword ptr [ESP + 0x10]
  // 0x006a33ea POP EDI
  // 0x006a33eb POP ESI
  // 0x006a33ec XOR AL,AL
  // 0x006a33ee POP EBX
  // 0x006a33ef MOV dword ptr FS:[0x0],ECX
  // 0x006a33f6 ADD ESP,0x10
  // 0x006a33f9 RET 0x10
  //   The result byte is zeroed and the epilogue matches the other one, offset
  //   by the single word the failure transfer pushed. Note that the word the
  //   caller supplied at entry_ESP+0xc is NOT written on this path: the object
  //   built at 0x006a3378 is dropped without ever being published.
  leave_scope_frame(displaced_chain);
  return false;
}

}  // namespace openspore::reconstruction::pkg_propmanager_create_wave15
