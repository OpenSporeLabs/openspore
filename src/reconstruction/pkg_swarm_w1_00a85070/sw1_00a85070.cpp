// PKG-SWARM-W1-00A85070 -- VA 0x00a85070
// FUN_00a85070 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 13 instructions, 0x00a85070..0x00a8508c inclusive
// (ghidra_function.body_start 0x00a85070, body_end 0x00a8508d, size_bytes 30).
// Every line of the model below is annotated with the instruction it comes from.
//
//   00a85070  PUSH ESI                       56
//   00a85071  MOV ESI,ECX                    8B F1
//   00a85073  MOV ECX,dword ptr [ESP + 0x8]  8B 4C 24 08
//   00a85077  MOV EAX,dword ptr [ECX]        8B 01
//   00a85079  MOV EDX,dword ptr [EAX + 0x20] 8B 50 20
//   00a8507c  CALL EDX                       FF D2
//   00a8507e  MOV EDX,dword ptr [EAX]        8B 10
//   00a85080  MOV ECX,EAX                    8B C8
//   00a85082  MOV EAX,dword ptr [EDX + 0x60] 8B 42 60
//   00a85085  CALL EAX                       FF D0
//   00a85087  MOV dword ptr [ESI + 0x10],EAX 89 46 10
//   00a8508a  POP ESI                        5E
//   00a8508b  RET 0xc                        C2 0C 00
//
// The two 0xCC bytes at 0x00a8508d..0x00a8508e are INT3 padding, not body: the
// 30-byte span ends at 0x00a8508c and the next 0xcc is the usual MSVC inter-
// function filler. Nothing below claims them.
//
// CONTROL FLOW: there is none. The body has zero conditional branches, zero
// unconditional branches and zero loops; the 13 instructions fall through once
// and terminate at 0x00a8508b. So the whole behaviour is two indirect transfers
// and one store, in that order, on every call. There is consequently no arm, no
// guard, no null check and no exception handling to model: the receiver+0x10 store
// happens exactly once per call whatever the callees do.
//
// FRAME, resolved once against the entry ESP so every displacement below is a
// fact and not a guess. Entry ESP is 0 in the walk.
//
//   entry+0    the return address
//   entry+4    the FIRST ordinary argument, the owner. 0x00a85073 reads it with
//              the displacement 0x08 taken against ESP = entry-4 (the prologue's
//              PUSH ESI), so entry-4 + 8 = entry+4. This is the only argument
//              word the body reads.
//   entry+8    the SECOND ordinary argument. No instruction in the body names it;
//              it exists because 0x00a8508b is `RET 0xc`, which consumes the
//              return address plus two words. See the header.
//   entry-4    the saved ESI, pushed at 0x00a85070 and popped at 0x00a8508a.
//
// The frame balances: POP ESI returns ESP to entry and `RET 0xc` lands it on
// entry+12 = entry+4 + 8, so the callee owns both argument words. That is the
// first half of the __thiscall claim; the second half is that the body's only
// register argument arrives in ECX, which 0x00a85073 shows by loading the owner
// straight into the receiver register before the first indirect call.
//
// VIRTUAL DISPATCH: two indirect transfers, and the brief's own machine record
// agrees -- abi_derived.dispatch reports indirect_calls 2, call_offsets [] and
// vtable_shaped_loads 0. Both are `CALL reg` (0x00a8507c FF D2, 0x00a85085 FF
// D0), and both targets are fetched with the shape `MOV reg, [base + disp]`:
//
//   site 1  0x00a85077/0x00a85079  base = *owner        disp = 0x20
//           receiver (ECX) = owner
//   site 2  0x00a8507e/0x00a85082  base = **owner       disp = 0x60
//           receiver (ECX) = *owner
//
// Both targets are read as plain 4-byte words out of memory: neither is an
// immediate, and neither base is checked. The two reads of the base are one and
// the same address -- site 1's base is the word at owner+0x00, and site 2's base
// is the word at that same word's +0x00 -- so the chase is two dereferences deep
// from the owner, not two independent objects.
//
// THIS BODY IS ITSELF A VTABLE ENTRY. The vtable export associates it with
// vtable 0x01458024, and the association is checked here against the table's own
// bytes and its single xref: the dword at 0x01458024 is 0x00a85070, and the only
// reference to 0x01458024 anywhere in the program is the DATA xref from
// 0x00a853d8 inside the constructor 0x00a853b0, whose instruction is
// `MOV dword ptr [ESI], 0x1458024`. So this function is the FIRST slot (byte
// offset +0) of the vtable that this class installs on its own receiver. The
// class itself is not named here: nothing in the evidence fixes a C++ name for
// it, and the vtable's other fifteen entries are not enough to derive one.
//
// GLOBALS: none. No instruction in the 13 names a data-segment address. The
// constructor does read four float constants and a string pointer, but that is
// the constructor's evidence, not this body's, and none of them appears here.
//
// THE EAX DEPENDENCE, which is the one thing a reader must not gloss over: after
// site 1, 0x00a8507e re-reads through EAX instead of reloading [ECX], and
// 0x00a85080 hands that same EAX to site 2 as its receiver. So both the receiver
// and the table base of site 2 are the value site 1's callee left in EAX. The
// model threads one explicit EAX word so this dependency is visible and testable
// instead of being silently optimised into a re-read; see the header's
// instrumentation note and the sidecar's unresolved questions.

#include "sw1_00a85070_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00a85070 {
namespace {

// The three target displacements, tied to the instructions that fix them. These
// are assertions, not documentation: they fail the build if a constant in the
// header is ever edited away from the listing, and each message names the
// instruction the value came from.
static_assert(kFirstTargetDisplacement == 0x20, "the +0x20 fetch at 00a85079");
static_assert(kSecondTargetDisplacement == 0x60, "the +0x60 fetch at 00a85082");
static_assert(kReceiverResultDisplacement == 0x10, "the store at 00a85087");
// The two base reads are at displacement zero (00a85077 on the owner, 00a8507e on
// the dispatch object). Written in decimal so the model's only hexadecimal
// literals are the three the listing carries as displacements.
static_assert(kOwnerLeadDisplacement == 0, "the owner read at 00a85077");
static_assert(kSecondBaseDisplacement == 0, "the base read at 00a8507e");

// The model's single EAX. It is instrumentation, not a machine global: no
// instruction names it, and the original code has no such addressable word. It
// lives at namespace scope because the model test reads it at the two call sites
// through eax_register().
Word g_eax = 0;

}  // namespace

Word eax_register() { return g_eax; }

extern "C" Word PKG_SW1_00A85070_THISCALL re_00a85070(Receiver* receiver,
                                                       OwnerObject* owner,
                                                       Word) {
  // 00a85070  PUSH ESI
  // 00a85071  MOV ESI,ECX
  //
  // ESI is the receiver alias and the only register this body saves. Every
  // receiver access below goes through it, and the epilogue's POP ESI restores
  // it, so the alias is a frame fact with no other observable.
  //
  // The receiver is taken as a byte run and the single access below is a
  // DISPLACEMENT into it. Nothing at +0x00..+0x0f or +0x14..+0x6b is read or
  // written by this body; the 0x6c size is the constructor 0x00a853b0's, cited in
  // the header, and this body on its own would only bound the object at 0x14.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00a85073  MOV ECX,dword ptr [ESP + 0x8]
  //
  // The first ordinary argument, loaded into the RECEIVER register. It is the
  // owner: the body's only later use of ECX is to hand it, unchanged, to site 1
  // at 0x00a8507c, and the body's only use of the argument word is the read at
  // 0x00a85077. The displacement 0x08 is taken against ESP = entry-4 (the
  // PUSH ESI), so it lands on entry+4 -- the first argument slot, which is also
  // what `RET 0xc` later confirms this callee owns.
  //
  // ECX is the receiver slot, so the receiver of site 1 is the argument itself and
  // NOT the object at some offset inside it.
  void* const owner_receiver = owner;

  // 00a85077  MOV EAX,dword ptr [ECX]
  //
  // ONE dereference of the owner, at displacement 0 (kOwnerLeadDisplacement). The
  // result is not the owner and not a member of the owner: it is the single word
  // the owner leads with, and the body then uses it as an ADDRESS, twice, in two
  // different roles:
  //
  //   as a table base  -- 0x00a85079 reads [EAX + 0x20] and calls that;
  //   as a receiver    -- 0x00a85080 moves it into ECX for site 2.
  //
  // A reconstruction that read a member of the owner here instead, or that
  // treated EAX as the owner rather than as the owner's leading word, would be
  // dereferencing a different object; the model test plants decoys at both
  // depths for exactly that.
  g_eax = read_word(owner, kOwnerLeadDisplacement);

  // 00a85079  MOV EDX,dword ptr [EAX + 0x20]
  //
  // Site 1's target: the word 0x20 bytes into the object EAX addresses
  // (kFirstTargetDisplacement). 0x20 / 4 == slot index 8, recorded in the header
  // as arithmetic and asserted by nothing.
  //
  // Whether that word is a VTABLE SLOT or a plain callback word inside an object
  // is not settled by the machine: if the object is this owner's vtable pointer
  // then the receiver and the table belong together and this is an ordinary
  // virtual call; if the object is a callback holder then the receiver is the
  // owner passed as the callee's single argument. Both readings execute the same
  // three instructions, so the model does the fetch and the call and asserts
  // nothing about which one it is.
  const Word first_target = load_slot(g_eax, kFirstTargetDisplacement);

  // 00a8507c  CALL EDX
  //
  // The first indirect transfer. One register argument, ECX, which is still the
  // owner (0x00a85073 set it and nothing has written ECX since); no stack
  // argument, no immediate, no target check. The callee's EAX output is the only
  // thing the machine can see afterwards, and the body reads it immediately.
  g_eax = invoke_slot(first_target, owner_receiver);

  // 00a8507e  MOV EDX,dword ptr [EAX]
  //
  // THE INSTRUCTION THAT DECIDES THE SECOND HALF OF THIS BODY. It reads through
  // EAX, and EAX is the value the call above just returned -- the body does NOT
  // reload [ECX] here, so it does not re-derive the owner->+0x00 word after a
  // call it cannot analyse. Site 2's table base is therefore whatever the first
  // callee left behind, and the model keeps that dependency instead of papering
  // over it with a re-read. Displacement 0 (kSecondBaseDisplacement).
  const Word second_base = load_slot(g_eax, kSecondBaseDisplacement);

  // 00a85080  MOV ECX,EAX
  //
  // Site 2's receiver is that same post-call EAX -- the very address site 2's
  // table base was read from. So the receiver and the base are one and the same
  // value: site 2 is a dispatch through the leading word of the object the body
  // already had in hand, not through a fresh owner lookup.
  void* const second_receiver =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(g_eax));

  // 00a85082  MOV EAX,dword ptr [EDX + 0x60]
  //
  // Site 2's target: the word 0x60 bytes into the table EDX named
  // (kSecondTargetDisplacement). 0x60 / 4 == slot index 0x18, again arithmetic and
  // again asserted by nothing. The displacement is 0x60 and not 0x20: the two
  // sites read DIFFERENT offsets of the same chase, and the model test fills the
  // neighbouring slots with decoy observers so a swapped or fumbled displacement
  // cannot pass.
  g_eax = load_slot(second_base, kSecondTargetDisplacement);

  // 00a85085  CALL EAX
  //
  // The second indirect transfer. Same shape as the first: one register argument
  // (ECX, the value from 0x00a85080), no stack argument, no check. Its EAX output
  // is the body's result, so the value the caller receives is decided here and
  // nowhere else.
  g_eax = invoke_slot(g_eax, second_receiver);

  // 00a85087  MOV dword ptr [ESI + 0x10],EAX
  //
  // The only memory write in the body: one dword, at the receiver's displacement
  // 0x10 (kReceiverResultDisplacement), holding exactly the value in EAX. It is
  // not a byte or a halfword store (opcode 89 46 10 is the 3-byte dword form), it
  // is not a store through a pointer the body loaded (it is [ESI + 0x10], i.e.
  // the receiver itself, not anything the calls returned), and it is not an
  // increment or an exchange: the EAX value replaces whatever was there.
  //
  // It happens AFTER both calls return, which the model test checks by having
  // each observer read the receiver's +0x10 at the moment it is entered.
  *reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(self) +
                           kReceiverResultDisplacement) = g_eax;

  // 00a8508a  POP ESI
  // 00a8508b  RET 0xc
  //
  // The epilogue restores the one saved register and returns past the return
  // address and both argument words. It touches no general-purpose register that
  // carries the result -- POP ESI and RET leave EAX alone -- so the value in EAX
  // at 0x00a85087 is the value the caller receives. That identity (returned ==
  // stored) is a fact of these three instructions, and the model asserts it.
  return g_eax;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00a85070
