// PKG-SWARM-W1-00A85070 -- VA 0x00a85070
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00a85070 @ 0x00a85070.
//
// The complete body is 13 instructions, 30 bytes, 0x00a85070..0x00a8508c
// inclusive (ghidra_function.body_start 0x00a85070, body_end 0x00a8508d
// exclusive, size_bytes 30), re-read from the image bytes for this package:
//
//   00a85070  PUSH ESI                     56
//   00a85071  MOV ESI,ECX                  8B F1
//   00a85073  MOV ECX,dword ptr [ESP + 0x8] 8B 4C 24 08
//   00a85077  MOV EAX,dword ptr [ECX]      8B 01
//   00a85079  MOV EDX,dword ptr [EAX + 0x20] 8B 50 20
//   00a8507c  CALL EDX                     FF D2
//   00a8507e  MOV EDX,dword ptr [EAX]      8B 10
//   00a85080  MOV ECX,EAX                  8B C8
//   00a85082  MOV EAX,dword ptr [EDX + 0x60] 8B 42 60
//   00a85085  CALL EAX                     FF D0
//   00a85087  MOV dword ptr [ESI + 0x10],EAX 89 46 10
//   00a8508a  POP ESI                      5E
//   00a8508b  RET 0xc                      C2 0C 00
//
// HONESTY NOTE ON WHERE EVERY OFFSET IN THIS HEADER COMES FROM, because the
// split matters to a reader:
//
//  * The three displacements the body itself shows -- 0x00 (twice, on the words at
//    0x00a85077 and 0x00a8507e), 0x20 (0x00a85079), 0x60 (0x00a85082) and 0x10
//    (0x00a85087) -- are read out of its own 13-instruction listing. 0x00 is the
//    only displacement the listing writes twice, and it is the one the two-level
//    chase is built from.
//
//  * The size of the receiver (0x6c) is NOT this body's evidence. This body
//    writes one dword at receiver+0x10 and reads nothing else on the receiver, so
//    it bounds the object from below at 0x14 only. The 0x6c figure comes from a
//    DIFFERENT body: the constructor at 0x00a853b0, which installs the very
//    vtable this function is an entry of (0x00a853d8 `MOV dword ptr [ESI],
//    0x1458024`) and whose last write to a scalar is `MOV dword ptr [ESI + 0x68],
//    0xffffffff` at 0x00a8544d, i.e. the object is at least 0x6c bytes. That is a
//    second listing, and it is cited as such; nothing below 0x6c is claimed.
//
//  * The word at receiver+0x10 is left an OPAQUE 4-byte slot, not a pointer
//    member, even though other bodies in the same vtable treat it as one. The
//    reason is that this body only ever STORES into it (0x00a85087) and never
//    reads it, so nothing in THIS listing fixes its type. Two other listings are
//    recorded below as context, and the type claim they would support is
//    deliberately not taken here.
//
//  * No member is named. Every sub-object below is spelled field_<hex offset> or
//    opaque_<range>, which states where it lives and nothing about what it is
//    for. The three type names are chosen for the access SHAPE this body uses
//    (one word at +0x00; words at +0x00 and +0x20) and carry no claim about what
//    the objects are.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00a85070 requires an x86-32 target"
#endif

// The one convention this body needs. Spelled per toolchain: GCC 16 rejects the
// bare MSVC keywords outright, so the x86-32 attribute form is the portable
// spelling and the keyword form is kept for MSVC.
//
//   PKG_SW1_00A85070_THISCALL  this body is __thiscall. The two things that fix
//     it are its own bytes: 0x00a85073 loads the first ordinary argument with
//     displacement 0x08 taken against the prologue's PUSH ESI (so it lands on
//     entry_ESP + 4, the first argument slot, not on a receiver-slot register),
//     and 0x00a8508b is `RET 0xc`, which pops the return address plus two words
//     -- callee-owned cleanup, so not cdecl and not fastcall.
#if defined(_MSC_VER)
#define PKG_SW1_00A85070_THISCALL __thiscall
#else
#define PKG_SW1_00A85070_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00a85070 {

using Word = std::uint32_t;

// The displacements this body was seen reaching, as values. Each row says which
// instruction it came from; none of them is a member name.
//
//   kOwnerLeadDisplacement   0x00  0x00a85077  MOV EAX,dword ptr [ECX]
//   kFirstTargetDisplacement 0x20  0x00a85079  MOV EDX,dword ptr [EAX + 0x20]
//   kSecondBaseDisplacement  0x00  0x00a8507e  MOV EDX,dword ptr [EAX]
//   kSecondTargetDisplacement 0x60 0x00a85082  MOV EAX,dword ptr [EDX + 0x60]
//   kReceiverResultDisplacement 0x10 0x00a85087 MOV dword ptr [ESI + 0x10],EAX
constexpr std::size_t kOwnerLeadDisplacement = 0x0u;
constexpr std::size_t kFirstTargetDisplacement = 0x20u;
constexpr std::size_t kSecondBaseDisplacement = 0x0u;
constexpr std::size_t kSecondTargetDisplacement = 0x60u;
constexpr std::size_t kReceiverResultDisplacement = 0x10u;

// The same two target fetches expressed as vtable slot INDICES, i.e. the
// displacement divided by the 4-byte slot width. These are arithmetic identities,
// not second evidence: 0x20 / 4 == 8 and 0x60 / 4 == 0x18. They are named here
// only so a reader who counts slots in a vtable does not have to redo the
// division, and the model asserts nothing from them.
constexpr std::size_t kFirstTargetSlotIndex = kFirstTargetDisplacement / 4u;    // 8
constexpr std::size_t kSecondTargetSlotIndex = kSecondTargetDisplacement / 4u;  // 0x18

// The first ordinary stack argument's target. This body reads exactly ONE word
// from it -- the dword at +0x00, at 0x00a85077 -- and never writes it, never
// reaches past it, and never passes its address anywhere. 0x04 bytes is therefore
// the exact observed extent, and the bytes at +0x00 are the only ones named.
struct OwnerObject {
  std::array<std::uint8_t, 0x04> opaque_00{};  // +0x00: read at 0x00a85077, nothing else
};
static_assert(sizeof(OwnerObject) == 0x04,
              "this body reads one dword at owner+0x00 and nothing else");

// The object reached at OwnerObject+0x00 (the value the body calls EAX at
// 0x00a85077, and hands to the second indirect call in ECX at 0x00a85080).
//
// This body reads exactly TWO words from it:
//
//   +0x00  0x00a8507e  MOV EDX,dword ptr [EAX]      -> the base of the second
//                                                       target fetch
//   +0x20  0x00a85079  MOV EDX,dword ptr [EAX + 0x20] -> the first target itself
//
// and never writes it, and never reads a byte in between. The run between +0x04
// and +0x1f is therefore named as opaque, and the object is 0x24 bytes as
// observed (the +0x20 read is four bytes long).
//
// WHAT THE TWO READS ARE IS NOT SETTLED, and the type does not pretend otherwise.
// The +0x20 word is fetched from the object and called with `owner` in ECX
// (0x00a85073 left it there and nothing overwrote it before 0x00a8507c), so it is
// either a vtable slot whose receiver happens to be the owner -- i.e. the object
// IS this body's owner's vtable pointer -- or a plain callback word stored in an
// object, invoked with the owner as its single argument. Both readings produce
// byte-identical machine behaviour, so the listing cannot separate them and the
// model asserts neither. The +0x00 word is then used as a TABLE BASE at +0x60
// (0x00a85082) with the object itself as the receiver, which is the shape of a
// virtual call on a polymorphic object whose vtable pointer sits at +0x00.
struct SlotObject {
  std::array<std::uint8_t, 0x04> opaque_00{};   // +0x00: read at 0x00a8507e
  std::array<std::uint8_t, 0x1c> opaque_04_1f{};  // +0x04..+0x1f: never touched
  Word field_20{};                              // +0x20: read at 0x00a85079
};
static_assert(sizeof(SlotObject) == 0x24,
              "0x20 + 4 is the last byte this body reads on the dispatch object");
static_assert(offsetof(SlotObject, field_20) == 0x20,
              "first target displacement");

// The receiver (ECX at 0x00a85071, aliased into ESI). This body touches exactly
// one thing on it: the dword at +0x10, written at 0x00a85087. It reads nothing,
// and it writes nothing else.
//
// The size below is not this body's evidence -- see the header note. It is the
// 0x6c minimum from the constructor 0x00a853b0, cited as a second listing, and
// it is the reason the +0x10 store is in bounds. Bytes +0x00..+0x0f and
// +0x14..+0x6b are declared as an opaque run because no instruction in this body
// names them. (For the record, and deliberately NOT modelled as members: the
// constructor stores a vtable pointer at +0x00 and a second one at +0x04, its
// argument at +0x0c, zero at +0x08 and at +0x10, a zero byte at +0x14, floats at
// +0x18/+0x1c/+0x20, zero halfwords at +0x24/+0x26, floats at +0x28..+0x34, an
// initialised member at +0x38, floats at +0x5c/+0x60/+0x64 and -1 at +0x68.)
struct Receiver {
  std::array<std::uint8_t, 0x6c> opaque_00{};  // 0x00..0x6b
};
static_assert(sizeof(Receiver) == 0x6c,
              "0x68 + 4 is the last scalar the constructor 0x00a853b0 writes");
static_assert(kReceiverResultDisplacement + sizeof(Word) <= sizeof(Receiver),
              "the one dword this body writes lies inside the ctor-bounded object");

// -- the indirect callees ----------------------------------------------------
// This body has NO direct callee: 0x00a8507c is `CALL EDX` and 0x00a85085 is
// `CALL EAX`, both register-indirect, and the brief's callees list is empty
// (ghidra_function.callees [] and abi_derived.dispatch.call_offsets []). There is
// therefore no named direct callee to declare, and the honest boundary object
// here is the SHAPE of an indirect call, which the listing does fix:
//
//   * the target is a 4-byte word read out of memory, never an immediate and
//     never a register-held address (0x00a85079, 0x00a85082);
//   * the call passes exactly ONE register argument, ECX, and nothing is pushed:
//     the body is 13 instructions with no PUSH other than the prologue's
//     `PUSH ESI`, and no stack write between 0x00a85073 and 0x00a85085 -- so the
//     callee signature is (receiver) with no stack arguments;
//   * the value the call leaves in EAX is the callee's whole observable output:
//     the first call's EAX is read back by the body at 0x00a8507e, and the second
//     call's EAX is stored and returned.
//
// That is the typedef below, and it is declared void*-receiving on purpose: the
// two calls hand it two objects of different and unidentifiable types (the owner
// at 0x00a8507c, the dispatch object at 0x00a85085), and the machine fixes only
// that each is a 4-byte value in ECX.
using IndirectCall = Word(PKG_SW1_00A85070_THISCALL*)(void* receiver);

// Reads the 4-byte word at `base_word + displacement`, where `base_word` is a
// register value the machine is treating as an address.
//
// Named load_slot because that is what the displacement at 0x60 is -- a fetch
// from a dispatch table at a fixed slot offset -- and because 0x20 is read the
// same way. The NAME is not a claim that both are vtable slots: see the
// SlotObject note. The helper takes the base as a Word rather than a pointer
// because in the machine the base lives in a register (EAX at 0x00a85077/0x7e,
// EDX at 0x00a85082) and, in the second fetch, is whatever the first call left
// in EAX.
inline Word load_slot(Word base_word, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base_word) +
                                        displacement);
}

// The same read, with the base arriving as a pointer instead of as a register
// value: 0x00a85077 is `MOV EAX,dword ptr [ECX]`, where the base is a pointer
// this body was handed. Both helpers spell ONE machine shape (read the 4-byte
// word at base+displacement); they differ only in where the base came from, and
// the model uses each one where the listing does.
inline Word read_word(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                        displacement);
}

// The single indirect transfer, as the model performs it: fetch a 4-byte target
// out of a table, call it with one register argument, and take the EAX it leaves.
inline Word invoke_slot(Word target_word, void* receiver) {
  return reinterpret_cast<IndirectCall>(static_cast<std::uintptr_t>(target_word))(
      receiver);
}

// -- model instrumentation ---------------------------------------------------
// The one physical EAX.
//
// WHY THIS EXISTS, stated plainly because it is the single highest-risk reading
// in this body: after the first indirect call (0x00a8507c) the body does NOT
// reload [ECX]. 0x00a8507e is `MOV EDX,dword ptr [EAX]` -- it re-reads through
// EAX, i.e. through whatever the first callee left there -- and 0x00a85080 then
// hands that same EAX to the second call in ECX. So the second dispatch's receiver
// AND its table base are both the post-call EAX. A source-level reconstruction
// that reloaded arg1->field_00 there would be a DIFFERENT function whenever the
// first callee writes EAX, and nothing in this listing says whether it does
// (see the sidecar's unresolved questions).
//
// The model therefore threads a single explicit EAX word through the body and
// exposes it, so the model test can (a) assert the EAX value the machine holds at
// each call site and (b) drive a first callee that deliberately clobbers it and
// observe where the second dispatch then goes. This word is instrumentation of the
// model's own register file: it is NOT a machine global, it is not addressable by
// the original code, and no instruction in the body names it.
Word eax_register();

// FUN_00a85070 @ 0x00a85070.
//
// __thiscall, receiver in ECX, two ordinary stack words of which the body reads
// only the first, `RET 0xc`. The terminator is machine-observed (0x00a8508b
// `C2 0C 00`) and the read slot is machine-observed (0x00a85073 `MOV ECX,
// dword ptr [ESP + 0x8]`, taken with ESP at entry-4 after the PUSH ESI, landing on
// entry_ESP + 4). The SECOND stack word exists because `RET 0xc` consumes three
// words in total; no instruction in the body reads it and nothing else about it
// is fixed, so it is declared and left unnamed.
//
// Return type is a 4-byte word. The value in EAX at 0x00a85087 is the second
// call's EAX, it is stored at receiver+0x10, and the epilogue (POP ESI; RET 0xc)
// does not touch EAX, so the caller receives exactly what was stored. The ABI
// record classifies it as unclassified_in_EAX and no record gives it a C++ type;
// the sibling bodies in the same vtable that read receiver+0x10 treat that word
// as a pointer (see the Receiver note), but this body never reads it, so the
// return is declared as the raw word the machine moves and nothing more is
// claimed.
extern "C" Word PKG_SW1_00A85070_THISCALL re_00a85070(Receiver* receiver,
                                                       OwnerObject* owner,
                                                       Word second_stack_word);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00a85070
