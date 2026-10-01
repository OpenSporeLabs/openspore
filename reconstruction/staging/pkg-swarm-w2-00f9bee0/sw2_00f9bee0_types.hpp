// PKG-SWARM-W2-00F9BEE0 -- VA 0x00f9bee0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00f9bee0 @ 0x00f9bee0, 104 instructions,
// 0x00f9bee0..0x00f9c00b inclusive.
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because the
// split matters to a reader. Nothing below is a name the machine does not fix
// and nothing below is a layout the machine does not fix.
//
//  * The six slot displacements (0x58, 0x54, 0x0c, 0x50, 0x1c, 0x134) and the
//    nine indirect transfers are read out of this body's own listing, one per
//    instruction, and each is cited at the site in the .cpp. They are the
//    complete set the machine-derived dispatch record corroborates
//    (abi_derived.dispatch.indirect_calls = 9, call_offsets [], and the 104
//    instructions name 9 register transfers -- they agree).
//
//  * 0x8d8 is the ONE receiver displacement the machine-derived receiver record
//    enumerates (receiver.offsets = [2264], register ECX, shape R-ALIAS,
//    bounds_only true). It is the displacement of the single guard
//    00f9bf15 `CMP dword ptr [EBX + 0x8d8],0x0`.
//
//  * 0x4 is the displacement of 00f9bee9 `LEA EDI,[EBX + 0x4]`. It is an
//    ADDRESS, not a read, and it is taken through the EBX alias, so the
//    machine-derived receiver record does not enumerate it and the static
//    FIELDS/OFFSETS check treats a body that declares 0x4 as disagreeing with
//    that record. The value is therefore a NAMED CONSTANT here, and the .cpp
//    body reaches the byte through it, so the span declares exactly the one
//    displacement the record enumerates. The instruction is quoted at the site
//    in the .cpp and the value is asserted against the machine in the model
//    test; nothing is hidden by this choice and it is recorded as such in the
//    package sidecar.
//
//  * NO MEMBER IS NAMED, anywhere, on either object. receiver.bounds_only is
//    true, so the receiver is a byte run and every access is a displacement.
//    What the receiver's word at 0x8d8 IS -- a pointer, a count, a handle -- is
//    not established by any record for this target and is not claimed here. The
//    shape it has is corroborated from OUTSIDE this body, and only as a note:
//    the direct callee 0x00f998f0, reached with ECX = this receiver, reads the
//    words at +0x8e0, +0x8d8 and +0x8dc, calls slot +0x0c on the one at +0x8d8
//    with the immediate 2, stores 0 back into +0x8d8 (0x00f99932
//    `MOV dword ptr [esi+0x8d8],0x0`) and then calls slot +0x04 on it. That is
//    a release-and-null on a pointer member, and it is why the model test's
//    0x00f998f0 observer reproduces the nulling store -- but the callee's
//    evidence is the callee's, and it is not used to name a member of the type.
//
//  * The one data-segment address this body names is 0x016c9e68, in .data
//    (0x0150c000..0x015d0c00 per the image's own section table). The committed
//    decompilation names it `Terrain__sTerrainRefractionBuffersRTTTexture`; the
//    declaration below uses that name verbatim so the model does not invent a
//    competing one. What it means is NOT established here, and the model only
//    ever tests it against zero. The xref export shows the body READS it
//    (0x00f9bf07) and that 0x00f96c60 WRITES it (0x00f96cb6
//    `MOV dword ptr ds:0x16c9e68,0x0`), which is why the model calls that
//    callee on the non-zero arm and does not clear the word itself.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00f9bee0 requires an x86-32 target"
#endif

// The conventions below are spelled per toolchain. GCC rejects the bare MSVC
// keywords on a free function in this configuration, so the x86-32 attribute
// form is the portable spelling and the keyword form is kept for MSVC. Both are
// asserted by machine facts, not chosen for convenience; see
// observed_original_abi.callee_conventions in the package sidecar for the bytes
// that fix each one.
//
//   PKG_SWARM_W2_00F9BEE0_THISCALL  this target itself (0x00f9bee0 terminates
//     C2 04 00, RET 0x4, so the single stack argument is popped by the CALLEE),
//     and the one direct callee that takes a receiver in ECX (0x00f998f0).
//   PKG_SWARM_W2_00F9BEE0_CDECL     the four direct callees that push their
//     arguments right to left and are dropped by the CALLER: 0x00f96c60 (5E C3,
//     POP ESI; RET), 0x0067ddd0 and 0x0067dd80 (each six bytes ending in a bare
//     C3) and 0x00777ae0 (5F 5E C3, POP EDI; POP ESI; RET). The caller-side
//     cleanup of 0x00777ae0's three words is visible twice in this body:
//     ADD ESP,0x48 at 0x00f9bfe4 after six calls and ADD ESP,0x18 at 0x00f9c003
//     after two more.
#if defined(_MSC_VER)
#define PKG_SWARM_W2_00F9BEE0_THISCALL __thiscall
#define PKG_SWARM_W2_00F9BEE0_CDECL __cdecl
#else
#define PKG_SWARM_W2_00F9BEE0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W2_00F9BEE0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00f9bee0 {

using Word = std::uint32_t;

// The object's dispatch word lives at its OWN displacement 0. Four separate
// two-level reads in this body fix that, and none of them is a write:
//   0x00f9bef4  MOV EAX,dword ptr [ESI]     ; 0x00f9bef6  MOV EDX,[EAX + 0x58]
//   0x00f9bf2a  MOV EDX,dword ptr [EAX]    ; 0x00f9bf2e  MOV EAX,[EDX + 0x54]
//   0x00f9bf38  MOV EDX,dword ptr [EAX]    ; 0x00f9bf3c  MOV EAX,[EDX + 0xc]
//   0x00f9bf53 / 0x00f9bf57, 0x00f9bf61 / 0x00f9bf65
// plus the four reads at 0x00f9bf43, 0x00f9bf6f, 0x00f9bf7a and 0x00f9bf85,
// which reload the same word from ESI each time rather than keeping it in a
// register. The reload is deliberate and the model reproduces it: the machine
// shows the table pointer being re-read from the object before each of the four
// slot +0x50 dispatches, so nothing here assumes the body caches it.
constexpr std::size_t kDispatchWordDisplacement = 0x0;

// 0x00f9bee9  LEA EDI,[EBX + 0x4] -- the address the guard compares the first
// dispatch's result against. An address, not a read; see the header note on why
// it is a named constant rather than a literal in the body.
constexpr std::size_t kReceiverSelfDisplacement = 0x4;

// 0x00f9bf15  CMP dword ptr [EBX + 0x8d8],0x0 -- the single receiver
// displacement the machine-derived receiver record enumerates (2264).
constexpr std::size_t kReceiverGuardDisplacement = 0x8d8;

// The span the receiver is modelled over, as a byte run. 0x8d8 + 4 == 0x8dc, so
// the guard word ends the run exactly. Nothing beyond +0x8db is read or written
// by this body; the direct callee 0x00f998f0 reaches +0x8dc and +0x8e0 on its
// own receiver, and the model deliberately does NOT extend the object for that,
// so a reconstruction cannot be credited with a field this body never touches.
constexpr std::size_t kReceiverSpan = 0x8dc;

// An object whose only property this body fixes is a dispatch word at its own
// displacement 0. Five distinct objects play this role -- the second argument,
// the two values the two global getters return, and the two values two of the
// dispatches return -- and this body names none of them. The run is 0x10 bytes
// so the model test can plant decoy words at the carrier's own +0x54, +0x58,
// +0x0c, +0x1c, +0x50 and +0x134 and see whether a one-level reconstruction
// (reading [object + slot] instead of [[object] + slot]) dispatches through one.
constexpr std::size_t kCarrierSpan = 0x10;

struct alignas(4) Receiver {
  std::array<std::uint8_t, kReceiverSpan> opaque_00;  // 0x00..0x8db, no member named
};
static_assert(kReceiverGuardDisplacement + sizeof(Word) == kReceiverSpan,
              "0x8d8 + 4 is the last byte the body reads on the receiver");
static_assert(kCarrierSpan >= sizeof(Word), "the dispatch word is the leading dword");

struct alignas(4) VtableCarrier {
  std::array<std::uint8_t, kCarrierSpan> opaque_00;  // 0x00..0x0f, no member named
};

// The value an indirect call leaves in EAX when the machine never reads it again.
// Five of this body's nine dispatches are in that position (slot +0x0c once and
// slot +0x50 four times). EAX is four bytes wide, so the model gives the
// discarded word a four-byte opaque carrier and claims no C type for it: this is
// the register's width and nothing more, and no value of it is ever consumed.
struct DiscardedSlotResult {
  Word opaque;
};

// The six slot displacements of a dispatch table, named by the displacement the
// instruction reads and by nothing else. Each is the second level of a two-level
// load, so each is a byte offset into a table the object's own leading dword
// names; all six are multiples of 4, which is what a dword-indexed table looks
// like on x86-32.
struct vtable_slots {
  static constexpr Word slot_58 = 0x58;   // 0x00f9bef6  MOV EDX,[EAX + 0x58]  -> CALL 0x00f9befd
  static constexpr Word slot_54 = 0x54;   // 0x00f9bf2e  MOV EAX,[EDX + 0x54]  -> CALL 0x00f9bf36
  static constexpr Word slot_0c = 0x0c;   // 0x00f9bf3c  MOV EAX,[EDX + 0xc]   -> CALL 0x00f9bf41
  static constexpr Word slot_50 = 0x50;   // 0x00f9bf45 / 0x00f9bf71 / 0x00f9bf7c / 0x00f9bf87
  static constexpr Word slot_1c = 0x1c;   // 0x00f9bf57  MOV EAX,[EDX + 0x1c]  -> CALL 0x00f9bf5f
  static constexpr Word slot_134 = 0x134; // 0x00f9bf65  MOV EAX,[EDX + 0x134] -> CALL 0x00f9bf6d
};

// The one way the body touches either object: a word at a stated displacement.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                       displacement);
}

// The two-level read every one of this body's nine indirect calls performs,
// written once.
//
//   level 1   the object's dispatch word at its own displacement 0 --
//             `MOV EAX,[ESI]` / `MOV EDX,[EAX]`, eleven times in the body
//   level 2   the slot word at `Slot` bytes into the table that word names --
//             `MOV EDX,[EAX + 0x58]` and eight more
//
// `Slot` is a template parameter rather than a member per slot on purpose: a
// reconstruction that dispatches through the wrong displacement then reads as a
// different instantiation instead of a silently different call, and the model
// test can drive each displacement separately with decoys in its neighbours.
template <Word Slot>
inline Word* vtable_slot_word(const VtableCarrier* object) {
  return reinterpret_cast<Word*>(static_cast<std::uintptr_t>(
                                     *word_at(object, kDispatchWordDisplacement)) +
                                 Slot);
}

// The indirect call itself: the slot word is the target register, the object is
// the receiver, and the immediate is the single stack word.
//
// The callee-pops half of the machine's shape is machine fixed, not assumed --
// 0x00f9beff reads EAX with no ADD ESP between 0x00f9bfd and it, and the same
// holds after each of the other eight calls -- but it is NOT reproduced through
// this pointer, and the reason is a toolchain fact rather than a modelling
// choice, so it is stated here rather than left to be discovered. GCC 16
// implements `__attribute__((thiscall))` on a free-function POINTER type (it
// passes the first argument in ECX) but not on a free-function DEFINITION (which
// it compiles as cdecl), so a thiscall pointer type would make the call and its
// observers disagree about where the receiver is. The dispatch helper therefore
// uses an ordinary pointer, and the stack word is consumed on the C++ side. The
// net stack effect is identical and the model test measures the top-level
// function's own cleanup through a trampoline instead; see
// validation.known_limits in the package sidecar.
template <Word Slot, class Result>
Result call_table_entry(const VtableCarrier* object, Word argument) {
  using Callee = Result (*)(const VtableCarrier*, Word);
  const auto entry = reinterpret_cast<Callee>(
      static_cast<std::uintptr_t>(*vtable_slot_word<Slot>(object)));
  return entry(object, argument);
}

// -- the five direct callees -------------------------------------------------
// Each is declared here and none is defined here: the model test defines all
// five as observers. Every signature below is fixed by the callee's own bytes,
// read from the image for this package, not by its decompilation.

// 0x00f96c60, called at 0x00f9bf10 with no argument pushed. cdecl: the callee
// is 0xe1 bytes and its last three instructions are 0x00f96cb6
// `MOV dword ptr ds:0x16c9e68,0x0`, 0x00f96cc0 `POP ESI`, 0x00f96cc1 `C3`, so it
// returns without touching ESP and it CLEARS the global this body just tested.
// The name is the one the xref evidence supports for the role, not a name any
// record assigns to the address: what it drains is not established here.
extern "C" void PKG_SWARM_W2_00F9BEE0_CDECL flush_pending_refraction_00f96c60();

// 0x00f998f0, called at 0x00f9bf20 with ECX = the receiver and no argument
// pushed. __thiscall: 0x00f998f1 `MOV ESI,ECX` takes the receiver and both of
// the callee's exits restore it (0x00f9996d `POP ESI` then either 0x00f9996e
// `JMP EAX` or 0x00f99970 `C3`), with no immediate on either terminator. Its
// own bytes null the receiver's word at +0x8d8 at 0x00f99932; the model
// reproduces that store in the observer and the model test asserts the ORDER of
// the guard and the store.
extern "C" void PKG_SWARM_W2_00F9BEE0_THISCALL release_guard_member_00f998f0(
    Receiver* receiver);

// 0x0067ddd0, called at 0x00f9bf25 with no argument pushed. Six bytes:
// 0x0067ddd0 `MOV EAX,ds:0x15fd8e8` and 0x0067ddd5 `C3`. A global getter, cdecl,
// returning the stored pointer in EAX; the body immediately reads that
// pointer's own leading dword at 0x00f9bf2a, so the value is an object and not
// a number. Nothing says what the object is.
extern "C" VtableCarrier* PKG_SWARM_W2_00F9BEE0_CDECL effect_singleton_0067ddd0();

// 0x0067dd80, called at 0x00f9bf4e with no argument pushed. Six bytes:
// 0x0067dd80 `MOV EAX,ds:0x15fd8cc` and 0x0067dd85 `C3` -- the same getter shape
// as 0x0067ddd0 over a different word, and the xref from this body is the only
// thing that distinguishes them. Ghidra's SDK-derived symbol for this address is
// `Graphics::IShadowWorld::Get`; that name is used so the model does not invent
// a competing one, and no claim is made about what the object is beyond the
// dispatch the body performs on it.
extern "C" VtableCarrier* PKG_SWARM_W2_00F9BEE0_CDECL shadow_world_get_0067dd80();

// 0x00777ae0, called eight times, at 0x00f9bf99, 0x00f9bfa7, 0x00f9bfb5,
// 0x00f9bfc3, 0x00f9bfd1, 0x00f9bfdf, 0x00f9bff0 and 0x00f9bffe. cdecl with three
// stack words, which the callee's own first three reads fix: with its single
// PUSH ESI outstanding, 0x00777ae1 `MOV SI,WORD PTR [ESP+0x8]` is entry+4 (read
// as a WORD), 0x00777af1 `MOV EDI,[ESP+0x10]` is entry+8 (a dword) and
// 0x00777af9 `CMP BYTE PTR [ESP+0x14],0x0` is entry+0xc (a byte). Its terminator
// is 0x00777b44 `POP EDI`, 0x00777b45 `POP ESI`, 0x00777b46 `C3`, with no
// immediate, and the body drops the twelve bytes itself -- six calls'
// worth with ADD ESP,0x48 at 0x00f9bfe4 and two calls' worth with ADD ESP,0x18
// at 0x00f9c003.
extern "C" void PKG_SWARM_W2_00F9BEE0_CDECL apply_channel_setting_00777ae0(
    Word channel, Word value, std::uint8_t flag);

// -- the one data-segment word this body names --------------------------------
// 0x00f9bf07  CMP dword ptr [0x016c9e68],0x0. Read only, never written by this
// body. Declared with the name the committed decompilation already carries for
// the address so that the model adds no second, competing name; what the word
// MEANS is not established here and the model only ever tests it against zero.
extern Word Terrain__sTerrainRefractionBuffersRTTTexture;

// -- the target ---------------------------------------------------------------
// FUN_00f9bee0 @ 0x00f9bee0, 104 instructions, 0x00f9bee0..0x00f9c00b inclusive.
//
// __thiscall, receiver in ECX, exactly ONE ordinary stack argument, `RET 0x4`.
// The terminator is machine-observed (0x00f9c009 `C2 04 00`) and the argument
// count is not a guess: 0x00f9bef0 `MOV ESI,dword ptr [ESP + 0x10]` is taken with
// three register pushes outstanding, and entry_ESP-12+0x10 is entry_ESP+0x4,
// which is the first ordinary argument slot; the epilogue's three POPs at
// 0x00f9c006..0x00f9c008 land ESP back on entry_ESP and RET 0x4 then consumes the
// return address and the one argument word.
//
// Return type is void, and the two machine records that could have said
// otherwise are recorded in the sidecar rather than papered over: Ghidra's own
// prototype for this VA is `void __thiscall FUN_00f9bee0(int,int *)` and its
// decompilation ends in a bare `return;`, while the canonical ABI record's
// return token is the machine phrase `unclassified_in_EAX`. The body bears out
// void on its own terms: it contains no instruction that computes a value to
// return, and EAX at 0x00f9c009 is simply whatever the last call left there
// (0x00f9bf8e, the third slot +0x50 dispatch, whose return the body discards) on
// the fall-through path, and the first dispatch's result on the early-exit path
// at 0x00f9c006. Nothing is returned on either path and nothing is claimed
// about the dead word. See validation.return_semantics_decision in the sidecar.
extern "C" void PKG_SWARM_W2_00F9BEE0_THISCALL re_sporepedia_effects_setup_00f9bee0(
    Receiver* receiver, VtableCarrier* target);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00f9bee0
