// PKG-SWARM-W1-005732F0 -- VA 0x005732f0 (FUN_005732f0)
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_005732f0 @ 0x005732f0.
//
// THE COMPLETE LISTING (19 instructions, 60 bytes, 0x005732f0..0x0057332b
// inclusive). Re-derived from the image bytes for this package with
//
//   objdump -d --start-address=0x5732f0 --stop-address=0x573340
//           SPORE/SporeBin/SporeApp.exe
//
// and it agrees with the committed Ghidra listing instruction for instruction and
// byte for byte, so nothing below rests on the decompiler (there is none for this
// VA: evidence.evidence.missing_sections names DECOMPILATION).
//
//   005732f0  PUSH ESI                              56
//   005732f1  MOV ESI,ECX                           8b f1
//   005732f3  MOV ECX,dword ptr [ESI + 0x308]       8b 8e 08 03 00 00
//   005732f9  TEST ECX,ECX                          85 c9
//   005732fb  JZ 0x0057330e                         74 11
//   005732fd  MOV dword ptr [ESI + 0x308],0x0       c7 86 08 03 00 00 00 00 00 00
//   00573307  MOV EAX,dword ptr [ECX]                8b 01
//   00573309  MOV EDX,dword ptr [EAX + 0x4]          8b 50 04
//   0057330c  CALL EDX                              ff d2
//   0057330e  MOV ECX,dword ptr [ESI + 0x30c]       8b 8e 0c 03 00 00
//   00573314  TEST ECX,ECX                          85 c9
//   00573316  JZ 0x0057332a                         74 12
//   00573318  MOV dword ptr [ESI + 0x30c],0x0       c7 86 0c 03 00 00 00 00 00 00
//   00573322  MOV EAX,dword ptr [ECX]                8b 01
//   00573324  MOV EDX,dword ptr [EAX + 0x4]          8b 50 04
//   00573327  POP ESI                               5e
//   00573328  JMP EDX                               ff e2
//   0057332a  POP ESI                               5e
//   0057332b  RET                                   c3
//
//   0057332c..0057332f are four INT3 (cc) pad bytes before the next function, so
//   the body ends where the record says it ends (body_start 0x005732f0, body_end
//   0x0057332b, size_bytes 60).
//
// WHAT THE BODY IS, in the words the listing supports and no further:
//
//   * It is a leaf. abi_derived.dispatch records indirect_calls 2, call_offsets []
//   and vtable_shaped_loads 0; there is no direct transfer anywhere in the
//   19 instructions, so this header declares no direct callee to declare.
//   * It is a virtual call site on TWO receiver members, in a fixed order, each
//   through the same two-level load and each through the table word at the same
//   displacement 0x4. Both members are cleared to 0 BEFORE their own transfer.
//   * The second transfer is a TAIL transfer: 0x00573327 pops the saved receiver
//   and 0x00573328 jumps to the slot word, so the callee returns straight to this
//   body's own caller and its EAX is this body's return value.
//   * Its receiver is aliased out of ECX into ESI in the prologue. That is not
//     bookkeeping: ECX is the receiver register of both transfers, so the member
//     objects have to travel in it, and the incoming receiver has to live
//     somewhere else before the first MOV ECX at 0x005732f3 overwrites it.
//
// HONESTY NOTE ON WHERE EVERY OFFSET IN THIS HEADER COMES FROM:
//
//  * 0x308 and 0x30c are read straight out of this body's own listing, and they
//    are the complete set the machine-derived receiver record enumerates
//    (receiver.register ECX, receiver.offsets [776, 780] = [0x308, 0x30c],
//    receiver.written_through 2, receiver.bounds_only true). The record states
//    where the body was seen reaching and nothing about which member is which, so
//    neither member is named here: they are field_308 and field_30c, displacements.
//  * 0x4 is the displacement of the table word this body reads at 0x00573309 and
//    0x00573324. It is a slot displacement in the objects the members point at, not
//    a receiver offset, and it is kept in its own constant for that reason.
//  * 0x0 is the immediate of the two stores at 0x005732fd and 0x00573318.
//  * The modelled receiver size 0x310 is a LOWER BOUND, and nothing more: it is
//    0x30c + 4, the last byte the body writes. The real object is larger -- sibling
//    methods of the same table reach 0x397 (see the sidecar) -- but this body
//    neither reads nor writes a byte past 0x30f, so the run stops where the
//    evidence stops.
//
// NOTHING IS NAMED AS A CONCEPT. No SDK symbol, no class, no member role. The
// binary carries no MSVC RTTI (the word below the table at 0x013f57f8 is zero, per
// reconstruction/metadata/pkg-dogfood-00580cb0-a1/00580cb0.json, which read the
// same table), the record associates this body with a table but the xref export
// records zero vtable references, and no decompilation exists. Calling either
// member a listener, a handler, a sink or an owner would be a member story this
// evidence does not carry.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-005732f0 requires an x86-32 target"
#endif

// The one calling convention this body has. It is not a choice: the body takes its
// receiver in ECX (0x005732f1 reads ECX, and 0x005732f3 overwrites it, so ECX is
// the register the incoming receiver arrived in), it pushes nothing at all for the
// caller to clean, and its only terminator is a bare RET (0x0057332b, byte c3) with
// no immediate. abi_derived.verdict is ABI_INFERRED, conventions.calling_convention
// is __thiscall and conventions.confidence is INFERRED; inference C5 records the
// same zero-byte cleanup.
//
// The convention is spelled per toolchain: GCC rejects the bare MSVC keywords under
// -std=c++17, so the x86-32 attribute form is used and the keyword form is kept for
// MSVC.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_005732F0_THISCALL __thiscall
#define PKG_SWARM_W1_005732F0_CDECL __cdecl
#else
#define PKG_SWARM_W1_005732F0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_005732F0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_005732f0 {

using Word = std::uint32_t;

// The object each member word points at. Exactly one byte of its layout is machine
// evidence and one word of it is read:
//
//   00573307 / 00573322   MOV EAX,dword ptr [ECX]
//
// i.e. the leading dword of the object is a pointer that the body then indexes at
// displacement 0x4. Nothing else about these objects is shown by this listing: their
// size, their class, the number of slots in their table, and what slot 0x4 does are
// all unresolved (see the sidecar). The type is therefore a single word, and
// sizeof() below states that this is the model's floor, not the object's real size.
struct DispatchTarget {
  Word* table_at_00;  // MOV EAX,[ECX] -- the object's own leading word
};
static_assert(sizeof(DispatchTarget) == 4,
              "the only byte of these objects this listing reads is their leading word");

// The receiver. This body reads two words of it and writes two words of it, all by
// displacement, and touches nothing else:
//
//   005732f3  MOV ECX,dword ptr [ESI + 0x308]     read
//   005732fd  MOV dword ptr [ESI + 0x308],0x0     write
//   0057330e  MOV ECX,dword ptr [ESI + 0x30c]     read
//   00573318  MOV dword ptr [ESI + 0x30c],0x0     write
//
// so the type declares no members: naming either one would assert an identity the
// bounds_only receiver record cannot corroborate. Every access in the model goes
// through a displacement into this byte run, and the run is 0x310 bytes long because
// 0x30c + 4 is the last byte the body writes.
struct alignas(4) Receiver {
  std::array<std::uint8_t, 0x310> opaque_00{};
};
static_assert(sizeof(Receiver) == 0x310, "0x30c + 4 is the last byte the body writes");

// The receiver displacements this body was seen reaching, as values. They are
// offsets, not member names: nothing here says what either word is for, only where
// it sits and that the body reads it once and then writes 0 to it.
constexpr std::size_t kReceiverFirstMemberDisplacement = 0x308;
constexpr std::size_t kReceiverSecondMemberDisplacement = 0x30c;

// The table-word displacement, fixed twice in the listing (0x00573309 and
// 0x00573324). It belongs to the object a member points at, not to the receiver, and
// the two are never confused in the model: the model reads the member first and only
// then indexes its table.
constexpr std::size_t kDispatchTableDisplacement = 0x4;

// The immediate both stores write (0x005732fd, 0x00573318).
constexpr Word kClearedWord = 0x0;

// The EAX placeholder for the one path this body never writes EAX on.
//
// Paths out of this body, and what each leaves in EAX:
//   P1  member 0x308 non-null, member 0x30c null   -> EAX is the FIRST transfer's
//       return value (0x0057330c CALL EDX, then 0x0057330e..0x0057332b touch no
//       register EAX).
//   P2  member 0x30c non-null (whatever 0x308 was) -> EAX is the SECOND transfer's
//       return value, because 0x00573328 is a tail jump.
//   P3  both members null                          -> EAX is NEVER WRITTEN by this
//       body on that path: 0x005732f0..0x005732fb touch no register EAX, and
//       0x0057330e..0x0057332b touch none either. Whatever arrived in EAX leaves.
//
// P3 therefore has no machine-determined return word, and the model needs a value to
// return from a non-void function. The constant below is that placeholder and ONLY
// that: it is a modelling choice, labelled APPROXIMATION in the sidecar, and the
// model test states explicitly that it does not assert it. The declared return type
// is `Word` for the same reason -- the machine fixes the WIDTH (EAX) and the
// record's own inference classifies the value as pointer-like
// (abi.return_semantics "pointer_like_in_EAX", inference RT2), but the C type of a
// value the body forwards from a dynamic callee is a source-side choice.
constexpr Word kEaxUnwrittenOnTheNoMemberPath = 0x0;

// The transfer itself, as a type. The slot word is loaded out of an object's table
// at displacement 0x4 and transferred to; this listing never shows what is on the
// other side of that word, so the signature below is the WIDEST honest shape for a
// transfer whose argument count and return type are unobserved: it takes the receiver
// the machine passes in ECX and returns the word the machine leaves in EAX. It is
// deliberately NOT a member-function pointer: nothing in the listing says the
// target is a member of any class, and spelling it as one would assert a receiver
// relationship the table word cannot be asked about.
using SlotFn = Word (PKG_SWARM_W1_005732F0_CDECL*)(void* object);

// The leading word of a member object, read the way 0x00573307 / 0x00573322 read it:
// one dereference of a bare [ECX], with NO displacement. Exposed so the model reads
// a pointer where the machine reads a pointer; a model that read the member's VALUE
// as if it were the table, or the table's value as if it were the callee, is a
// two-level error this package's test drives directly.
inline const Word* table_of(const void* object) {
  return *reinterpret_cast<Word* const*>(object);
}

// The only way the body touches the receiver: a word at a stated displacement.
// A member access would assert an identity the bounds_only receiver record cannot
// corroborate, and the model therefore never writes one.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

static_assert(kReceiverSecondMemberDisplacement + sizeof(Word) == sizeof(Receiver),
              "0x30c + 4 ends the modelled receiver run");
static_assert(kReceiverFirstMemberDisplacement + 4 == kReceiverSecondMemberDisplacement,
              "the two member words are adjacent: 0x308 and 0x30c");

// -- the two indirect transfers ------------------------------------------------
// There are NO direct callees to declare: the complete 19-instruction listing names
// no CALL or JMP with an absolute operand, and abi_derived.dispatch agrees
// (indirect_calls 2, call_offsets []). The two transfers are:
//
//   0x0057330c  CALL EDX   EDX = *(table_of(member_308) + 0x4), ECX = member_308
//   0x00573328  JMP  EDX   EDX = *(table_of(member_30c) + 0x4), ECX = member_30c
//
// Both are indirect, both are the same shape, and the second one is a tail transfer.
// The dispatch helper below performs exactly the machine's three-step sequence --
// read the receiver into ECX, transfer to the table word, take EAX back -- because
// a plain C++ call would put the ENCLOSING receiver in ECX and would therefore model
// the wrong object. It is declared here and defined in the .cpp; the model test
// supplies the slot's own side of the transfer as an observer, which is what lets the
// test read ECX at the moment of the transfer and measure the receiver register the
// listing fixes.
Word dispatch_slot(SlotFn slot, void* object);

// FUN_005732f0 @ 0x005732f0.
//
// __thiscall, receiver in ECX, ZERO ordinary stack arguments, terminator
// `RET` (0x0057332b, byte c3) with no immediate on the one path that returns to its
// own caller, and a tail jump on the path that does not. Both records agree on the
// shape: ghidra_function.signature is "undefined FUN_005732f0(void)" with
// parameter_count 0, and abi_derived records stack_cleanup_bytes 0, owner caller.
//
// Return type: `Word`, and that is the one place this declaration goes beyond what
// the machine proves. The width is machine-fixed (EAX, abi.return_register) and the
// record classifies the value as pointer-like; the C type is a source-side choice,
// and the P3 path above is not machine-determined at all. See the sidecar's
// return_semantics and unresolved_questions for what stays open.
extern "C" Word PKG_SWARM_W1_005732F0_THISCALL re_005732f0(Receiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_005732f0
