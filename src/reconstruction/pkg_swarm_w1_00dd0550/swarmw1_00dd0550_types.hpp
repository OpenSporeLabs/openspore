// PKG-SWARM-W1-00DD0550 -- VA 0x00dd0550
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00dd0550 @ 0x00dd0550. The whole body is
// 16 instructions over 36 bytes (0x00dd0550..0x00dd0573), so this header states
// very little and every line of it is traceable to a byte or to a machine record.
//
// HONESTY NOTE ON WHERE EVERY DECLARATION IN THIS HEADER COMES FROM, because
// the split is the whole content of this package:
//
//  * The ONE receiver displacement this body shows is 0x80, read at 0x00dd055c
//    (`MOV EDX,dword ptr [ESI + 0x80]`). The machine-derived receiver record
//    agrees exactly and completely: receiver.offsets = [128], register ECX,
//    shape R-ALIAS, written_through 0, max_offset 128, distinct_offsets 1. So
//    the modelled receiver declares exactly one named member, at exactly the one
//    offset the record enumerates. Nothing here is a layout guess.
//
//  * The receiver is addressed through an ALIAS, not through ECX directly:
//    0x00dd0551 `MOV ESI,ECX` and every later receiver access is `[ESI + 0x80]`.
//    That is what receiver.shape "R-ALIAS" records, and it is why the body
//    pushes ESI at 0x00dd0550 and pops it on both exits (0x00dd056e,
//    0x00dd0572) -- the saved register is the caller-saved-value carrier, not a
//    callee-saved obligation being honoured for its own sake. abi.saved_registers
//    is exactly ["ESI"].
//
//  * NO member below +0x80 is named. The body reads nothing else on the receiver
//    and writes nothing on it at all (receiver.written_through = 0), so the whole
//    run 0x00..0x7f is opaque bytes and is modelled as such. This body is a
//    VIRTUAL method -- its only three cross-references are DATA references from
//    vtable tables (0x0147cab0, 0x0147cb78, 0x0147cc68) and it has ZERO direct
//    callers -- so a dispatch word at +0x00 is overwhelmingly likely, but the
//    listing never reads +0x00 and naming it would be a claim the machine does
//    not support. It is therefore left inside the opaque run.
//
//  * 0x00b3d2a0's return value is treated as an INCOMPLETE type, not as a struct.
//    That callee is two instructions (`MOV EAX,[0x0167eae4]; RET`) and its own
//    body never dereferences what it returns; this body only compares the pointer
//    against 0 (0x00dd0558) and hands it straight to 0x00ba6dc0 as the ECX
//    receiver (0x00dd0567). Declaring a layout for it here would be inventing
//    structure this package's own listings do not show.
//
//  * The type and the field are named field_80 for the same reason every offset
//    in this package is spelled by address: the target's own record carries no
//    SDK name for this VA (ghidra_function.sdk_name is null, sdk_type is null,
//    name is the placeholder FUN_00dd0550), so there is nothing to name it after.
//
//  * WHAT 0x80 IS FOR is not claimed here. It is read as one 32-bit word, tested
//    against zero, and pushed as a single stack argument. Its consumer
//    (0x00ba6dc0) does use the word as a packed index -- it masks 0xffffff,
//    splits at bit 12 with a 5-stride table and a 0xfff column, and shifts the
//    top byte out as a third argument -- so "a packed index" is an INFERENCE
//    drawn from the callee's body, recorded in the sidecar, and deliberately not
//    baked into a member name.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00dd0550 requires an x86-32 target"
#endif

// The calling convention below is spelled per toolchain. GCC rejects the bare
// MSVC keywords outright, so the x86-32 attribute form is the portable spelling
// and the keyword form is kept for MSVC. The convention is asserted by machine
// facts, not chosen for convenience: abi.calling_convention is __thiscall with
// hidden_this true, hidden_this_register ECX, stack_cleanup_bytes 0,
// stack_cleanup_owner "caller", saved_registers ["ESI"], ret_form "RET" with no
// immediate, and abi_derived.conventions.confidence is INFERRED with
// completeness CORE_RESOLVED. The bare RET with no immediate is what fixes the
// argument count at zero for this body: 0x00dd056e..0x00dd056f and
// 0x00dd0572..0x00dd0573 are `POP ESI; RET` and POP ESI restores ESP to the
// entry value, so there is no argument word for the callee to drop.
//
// One macro covers both the reconstructed body and the one direct callee that
// needs it. 0x00ba6dc0 is __thiscall by its own bytes: it reads its single
// argument at 0x00ba6dc1 `MOV ESI,dword ptr [ESP + 0x8]` -- taken with ESP one
// PUSH below the entry value, so [ESP+0x8] is the entry-level first stack word
// -- and it returns at 0x00ba6dcd / 0x00ba6dfc with `RET 0x4`, i.e. it drops that
// word itself. 0x00b3d2a0 needs no macro at all and is declared plain: see below.
#if defined(_MSC_VER)
#define PKG_SWARMW1_00DD0550_THISCALL __thiscall
#define PKG_SWARMW1_00DD0550_CDECL __cdecl
#else
#define PKG_SWARMW1_00DD0550_THISCALL __attribute__((thiscall))
#define PKG_SWARMW1_00DD0550_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00dd0550 {

using Word = std::uint32_t;

// The object 0x00b3d2a0 hands back and this body then hands to 0x00ba6dc0 as
// the ECX receiver at 0x00dd0567. Deliberately INCOMPLETE: this body never
// dereferences it, and neither does 0x00b3d2a0. The only thing this package
// knows about it is that 0x00ba6dc0 -- a DIFFERENT body, outside this package's
// scope -- reads one word at ITS receiver's +0xc8 and then indexes a table that
// word points at. Nothing in the 36 bytes of 0x00dd0550 reads +0xc8, so this
// header declares no member at that offset and makes no claim about it.
struct OpaqueStarTable;

// The receiver. One named member at the one offset the body reads, and an
// opaque run in front of it, and nothing after it.
//
//   0x00dd0551  MOV ESI,ECX                     ECX (the receiver) -> ESI
//   0x00dd055c  MOV EDX,dword ptr [ESI + 0x80]  the single receiver read
//
// The body makes no write of any kind through the receiver: the machine record
// states receiver.written_through = 0, and the complete 16-instruction listing
// contains no store to [ESI..] or to any other receiver-derived address. So
// 0x00..0x7f is an opaque run and 0x84.. is outside this body's reach; the
// struct is sized to 0x84 because 0x80 + 4 is the last byte the body reads.
struct alignas(4) SporepediaOnlineReceiver {
  std::array<std::uint8_t, 0x80> opaque_00;  // 0x00..0x7f, never touched here
  Word field_80;                            // the only receiver word the body reads
};

// The one receiver displacement, as a value. Named for the address it names and
// not for any role: 0x00dd055c encodes 0x80 and the machine receiver record
// enumerates 128 and nothing else.
constexpr std::size_t kReceiverKeyDisplacement = 0x80;

static_assert(offsetof(SporepediaOnlineReceiver, field_80) == 0x80,
              "0x00dd055c reads [ESI + 0x80]: the key word sits at receiver + 0x80");
static_assert(kReceiverKeyDisplacement == 0x80,
              "the receiver record enumerates 128 (0x80) and no other displacement");
static_assert(sizeof(SporepediaOnlineReceiver) == 0x84,
              "0x80 + 4 is the last byte the body reads on the receiver");
static_assert(offsetof(SporepediaOnlineReceiver, opaque_00) == 0x00,
              "the opaque run starts at the receiver itself");

// The only way the body under reconstruction touches its receiver: one 32-bit
// load at a stated displacement. A member access would assert an identity the
// machine-derived record explicitly declines to assert (receiver.bounds_only is
// true: the record states where the body was seen reaching, not which member is
// which).
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                       displacement);
}

// -- the two direct callees -------------------------------------------------
// Each is declared here and none is defined here: the model test defines both as
// observers, so it sees every transfer, with which argument, in which order.
// Both signatures are fixed by the CALLEE's own bytes, not by this body's
// decompilation and not by this body's argument count.

// 0x00b3d2a0, called at 0x00dd0553. Declared with NO parameters and NO receiver,
// which is the honest reading of its own two-instruction body:
//
//   0x00b3d2a0  MOV EAX,[0x0167eae4]
//   0x00b3d2a5  RET
//
// It reads no register and no stack slot: not ECX, not [ESP+0x4], nothing. So
// there is no receiver to bind and no argument to push, and the machine record
// agrees (ghidra_function.signature "undefined FUN_00b3d2a0(void)",
// parameter_count 0, locals_count 0; callers_dependencies is the only place a
// call xref exists, and there is not a single DATA xref). The ECX value at the
// 0x00dd0553 call site IS the receiver -- 0x00dd0551 copied it to ESI and left
// ECX alone -- but because this callee provably ignores ECX, that fact is
// inobservable and is deliberately NOT modelled as a receiver binding. The
// global slot it reads is recorded in the sidecar, not declared here: this
// package's own body names no data address at all.
//
// It returns a 32-bit word whose only observable properties, for the 36 bytes
// under reconstruction, are (a) it is compared against 0 at 0x00dd0558 and
// (b) it becomes the ECX receiver of 0x00ba6dc0 at 0x00dd0567. Returning an
// incomplete-type pointer is the correct C++ spelling of exactly those two
// facts: the caller only ever asks "is it null" and "hand it on".
extern "C" OpaqueStarTable* PKG_SWARMW1_00DD0550_CDECL root_slot_00b3d2a0(void);

// 0x00ba6dc0, called at 0x00dd0569. __thiscall, receiver in ECX, exactly one
// ordinary stack word, callee-owned cleanup. Fixed by the callee's own bytes:
//
//   0x00ba6dc0  PUSH ESI
//   0x00ba6dc1  MOV ESI,[ESP + 0x8]        <- the entry-level first stack word
//   0x00ba6dc5  CMP ESI,-0x1
//   0x00ba6dc8  JNZ 0x00ba6dd0
//   0x00ba6dca  XOR EAX,EAX                <- sentinel -1 arm returns 0
//   0x00ba6dcc  POP ESI
//   0x00ba6dcd  RET 0x4                    <- callee drops the word
//   0x00ba6dd0  MOV ECX,[ECX + 0xc8]       <- receiver is read at +0xc8
//   ...
//   0x00ba6dfc  RET 0x4
//
// The one stack word is the 0x80 key: 0x00dd0566 pushes EDX (loaded from
// [ESI+0x80] at 0x00dd055c) and 0x00dd0567 moves the FIRST call's EAX into ECX,
// so the receiver of this call is the global slot value and NOT this body's
// receiver. That is the single most consequential fact in the body and the one
// the model test attacks hardest.
//
// The return is one 32-bit word in EAX, forwarded unchanged by 0x00dd056e
// (`POP ESI`) and 0x00dd056f (`RET`): POP ESI does not touch EAX, so the callee's
// value is what this body returns. abi_derived.return records register EAX,
// register_class "integral", void_possible false -- hence the Word, not a
// pointer and not void. What the word DENOTES is 0x00ba6dc0's business (its
// 0x00ba6df6 call to 0x00bbaa60 returns a planet-record-shaped value) and is
// recorded as an inference in the sidecar, not as a type here.
extern "C" Word PKG_SWARMW1_00DD0550_THISCALL lookup_00ba6dc0(OpaqueStarTable* receiver,
                                                              Word key);

// FUN_00dd0550 @ 0x00dd0550.
//
// __thiscall, receiver in ECX, ZERO ordinary stack arguments, bare RET. Every
// part of that is machine-observed rather than assumed:
//
//   receiver        abi.receiver true, abi.receiver_register ECX,
//                   abi.hidden_this true, abi.hidden_this_register ECX; and
//                   0x00dd0551 `MOV ESI,ECX` consumes ECX before anything else.
//   argument count  cleanup.bytes 0, cleanup.side "caller", ret_form "RET" with
//                   imm null, and both exits are `POP ESI; RET` (0x00dd056e..f,
//                   0x00dd0572..3). A PUSH/POP pair of 4 bytes cannot itself be
//                   an argument: the PUSH at 0x00dd0566 is consumed by 0x00ba6dc0
//                  's own RET 0x4 and never survives to an exit, so no argument
//                   word is live across the terminator.
//   saved register  abi.saved_registers ["ESI"], matching 0x00dd0550 PUSH ESI
//                   and the two POP ESI.
//
// Ghidra's own prototype for this VA is "undefined FUN_00dd0550(void)" with
// ghidra_calling_convention null and ghidra_parameter_count 0, and the live
// decompilation opens "undefined4 __fastcall FUN_00dd0550(int param_1)". The
// __fastcall reading is contradicted by the listing on two counts and is not
// adopted: (1) there is no second argument -- no [EDX] is ever read, and the
// only register ECX feeds is the receiver copy at 0x00dd0551; (2) the
// decompilation's `param_1 + 0x80` is this body's ECX receiver, so the
// decompiler modelled the hidden receiver as a stack slot and shifted the
// argument frame up by one. The listing does not.
//
// Return type is Word. The machine record fixes the register (EAX) and the class
// (integral, void_possible false) but not the type (abi_derived.return.type is
// null and ghidra_function.return_type_resolved is false), so the declared type
// is the width and class the record does fix and nothing finer.
extern "C" Word PKG_SWARMW1_00DD0550_THISCALL re_00dd0550(
    SporepediaOnlineReceiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00dd0550
