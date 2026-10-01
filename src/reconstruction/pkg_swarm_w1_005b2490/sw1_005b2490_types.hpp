// PKG-SWARM-W1-005B2490 -- VA 0x005b2490
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_005b2490 @ 0x005b2490.
//
// The whole body is four instructions and eight bytes, re-read from the image for
// this package (GhidraMCP /read_memory at 0x005b2490, 8 bytes):
//
//   hex  : 8b 41 18 | 40 | 89 41 18 | c3
//   0x005b2490  8B 41 18    MOV EAX, dword ptr [ECX + 0x18]     (3 bytes)
//   0x005b2493  40          INC EAX                            (1 byte)
//   0x005b2494  89 41 18    MOV dword ptr [ECX + 0x18], EAX     (3 bytes)
//   0x005b2497  C3          RET                                 (1 byte)
//
// 3 + 1 + 3 + 1 == 8, which is the whole span: entry 0x005b2490 through 0x005b2497
// inclusive, and ghidra_function agrees on both ends (body_start 0x005b2490,
// body_end 0x005b2497, size_bytes 8, 4 instructions, parse {declared_count 4,
// unparsed 0, degraded false, flow_complete true}). NOTE ON A NUMBER IN THE
// BRIEFING, because it looks like a contradiction and is not: the briefing's abi
// preview carries "original_bytes": 5837 and its own nested "original_bytes": 5867.
// Those are fields of the `{"truncated": true, "preview": ...}` envelope the
// abi_infer preview string wraps -- a different record's prose, truncated into
// this pack's preview -- and the machine-parse record for this body is the
// {declared_count 4, unparsed 0, degraded false} above. The eight bytes are also
// what the four instruction lengths give, independently, so 8 is the span.
//
// HONESTY NOTE ON WHERE EVERY OFFSET IN THIS HEADER COMES FROM:
//
//  * The single receiver displacement, 0x18, is read out of this body's own
//    listing: it is the ModRM displacement byte of the 8B 41 18 at 0x005b2490 and
//    of the 89 41 18 at 0x005b2494. It is the complete set the machine-derived
//    receiver record enumerates (receiver.offsets = [24], register ECX,
//    shape R-DIRECT, bounds_only true, written_through 1, max_offset 24).
//
//  * sizeof(Receiver) == 0x1c is a LOWER BOUND and nothing more. It is
//    0x18 + 4: the four bytes this body reads and writes, and the first address
//    this body would touch past the model. Nothing in these four instructions
//    fixes the object's real size, and the real object is certainly larger: the
//    address 0x005b2490 is a virtual slot in several tables (see the slot
//    constants below), so a dispatch word exists at +0x00, and at least one other
//    function in one of those tables reaches to +0x397. A caller must supply an
//    object of at least 0x1c bytes; this model asserts nothing beyond that.
//
//  * No member is named. The word at +0x18 is the only thing this body addresses,
//    and no record says what it is. It is called "the word at +0x18" and is
//    written `opaque` in the struct. Calling it a counter, a version, a reference
//    count, a generation, a sequence number or an index would be a member story
//    four instructions cannot carry, so none of those words is used as a name.
//
//  * The slot displacements and the this-adjustment constants below are read out
//    of the DATA SEGMENT, not out of this body, and they are recorded for the
//    integrator and for the model test. None of them is modelled as a member and
//    none is used to name anything: this body never reads the word at +0x00, so
//    declaring a dispatch pointer at that offset would be a claim its listing
//    does not make.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-005b2490 requires an x86-32 target"
#endif

// The calling convention is spelled once, here, and the reconstructed body names
// the macro. It is not a convenience choice -- it is fixed by machine facts:
//
//   PKG_SW1_005B2490_THISCALL  __thiscall. ECX carries a receiver that is
//     dereferenced at 0x005b2490 before any definite write to it (obs-0001/0002 of
//     the ABI inference), and the abi record carries hidden_this true,
//     hidden_this_register ECX, receiver true, receiver_register ECX. The
//     record's own confidence is INFERRED, and the corroboration it lacks is
//     third-party; this package supplies that corroboration from the entry points
//     that reach the body, all three of which adjust the incoming ECX as a `this`
//     pointer before jumping here (see kThunkThisAdjustments below). The
//     terminator is a bare RET (C3, 0x005b2497) with no immediate and the body
//     reads no stack slot at all, so there is no ordinary stack argument and
//     nothing for the callee to clean: 0 bytes, caller side, which is what the
//     abi record states (stack_cleanup_bytes 0, owner "caller") and what the
//     terminator's form independently confirms.
//
// GCC 16 rejects the bare MSVC keywords, so the attribute form is the portable
// spelling and the keyword form is kept for MSVC.
#if defined(_MSC_VER)
#define PKG_SW1_005B2490_THISCALL __thiscall
#else
#define PKG_SW1_005B2490_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_005b2490 {

// The receiver's word, at the one displacement this body addresses (+0x18). The
// width of the arithmetic EAX performs is the one thing the listing does fix about
// that word: 8B reads a dword, 40 increments all 32 bits of EAX, and 89 stores a
// dword back. Signedness is NOT fixed -- INC EAX is bit-identical for a signed and
// an unsigned counter, and nothing in these four instructions tests the sign -- so
// the value is modelled as an unsigned 32-bit word, whose wraparound at 0xffffffff
// is the machine's, and the sign question is left open in the sidecar.
//
// The alias is kept for the RECEIVER'S word: the displacement accessor below, the
// body's own load and store, and the model test's decoys, seeds and fixtures all
// name it. The FUNCTION's declared return type is deliberately NOT spelled with
// it -- see the declaration at the bottom of this header.
using Word = std::uint32_t;

// The receiver. Opaque on purpose: this body reaches exactly one dword, at 0x18,
// and the struct below declares no member for it. Writing it as a byte run and
// reaching it through a displacement is the honest shape, because a member access
// would assert an identity the machine-derived receiver record cannot corroborate
// (bounds_only true: it states where the body was seen reaching, and not which
// member is which).
struct alignas(4) Receiver {
  std::array<std::uint8_t, 0x1c> opaque_00{};  // 0x00..0x1b
};
static_assert(sizeof(Receiver) == 0x1c,
              "0x18 + 4 is the last byte this body touches, and a lower bound only");

// The one receiver displacement. 0x18, from the ModRM byte of 8B 41 18 at
// 0x005b2490 and of 89 41 18 at 0x005b2494, and the whole of
// abi_derived.receiver.offsets ([24]).
constexpr std::size_t kReceiverWord18Displacement = 0x18;

// The extent facts, as values, so the model test can assert them against the
// listing instead of against prose. 4 instructions, 8 bytes, one basic block, and
// no transfer out of the body: the four instructions contain no CALL and no JMP,
// the machine dispatch record counts 0 indirect calls with 0 vtable-shaped loads,
// and the xref export records no outgoing call edge.
constexpr int kInstructionCount = 4;
constexpr std::size_t kBodySpanBytes = 8;
constexpr int kBasicBlockCount = 1;
constexpr int kDirectCalleeCount = 0;
constexpr int kStackArgumentSlots = 0;
constexpr std::size_t kStackCleanupBytes = 0;

// The entry addresses of the three code references to 0x005b2490, and the ECX
// adjustment each of them performs before jumping there. All three were read as
// bytes, and each is a two-instruction sequence -- SUB ECX, imm8 ; JMP 0x005b2490
// -- which is the shape a COMDAT-folded `this` adjustment takes:
//
//   0x0057a5d0  83 E9 04       SUB ECX,0x4      ; E9 B8 7E 03 00  JMP 0x005b2490
//   0x0057a5f0  83 E9 10       SUB ECX,0x10     ; E9 98 7E 03 00  JMP 0x005b2490
//   0x005b8550  83 E9 14       SUB ECX,0x14     ; E9 38 9F FF FF  JMP 0x005b2490
//
// This is the corroboration the ABI record's `conventions.corroboration:
// "not_available"` was missing: a first argument that is adjusted by a constant
// before use, and never consumed, is a `this` pointer, not a cdecl parameter. It
// is NOT used to name a base class, to size the receiver, or to claim a multiple
// inheritance offset -- what it fixes is only that ECX is a receiver and that the
// body itself is not the thing adjusting it.
constexpr std::uint32_t kThisAdjustingEntryPoints[] = {0x0057a5d0u, 0x0057a5f0u, 0x005b8550u};
constexpr std::uint32_t kThunkThisAdjustments[] = {0x4u, 0x10u, 0x14u};
constexpr int kThisAdjustingEntryPointCount = 3;

// Where the body's own address sits in the tables the address is referenced from.
// Read by dumping the tables' own bytes; these are data-segment facts and none of
// them is modelled as a member.
//
//   0x013f57f8  slot +0x00 = 0x005b2490   (the two dwords below it are
//              0x008816f0 and 0x00000000, the shape of a complete-object locator
//              and a null destructor entry, so 0x013f57f8 is a table head)
//   0x013f7028  slot +0x10 = 0x005b2490   and slot +0x04 = 0x005b8550, i.e. the
//              -0x14 this-adjusting thunk one slot above it
//
// The record associates 12 tables with this VA and the xref export carries 15
// data references to it, of which 14 are the three thunks' own slots. What any of
// those slots is CALLED is identified by no record in this package: this binary
// carries no MSVC RTTI, so the slot has no name here and none is invented.
constexpr std::uint32_t kTableWithBodyAtSlot0 = 0x013f57f8u;
constexpr std::uint32_t kTableWithBodyAtSlot10 = 0x013f7028u;
constexpr std::size_t kSlotDisplacementAtSlot0 = 0x00u;
constexpr std::size_t kSlotDisplacementAtSlot10 = 0x10u;

// The only way this body touches its receiver: a dword at a stated displacement.
// A member access would assert an identity the evidence does not carry.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                        displacement);
}

// FUN_005b2490 @ 0x005b2490, reconstructed.
//
// __thiscall, receiver in ECX, no ordinary stack argument at all, bare `RET`.
// The declared return type is the 32-bit word the listing leaves in EAX; the
// machine-derived ABI record leaves it "unclassified_in_EAX", which is a statement
// about the record and not a licence to declare void -- the listing shows the
// value plainly, at 0x005b2493 and 0x005b2494, and a reconstruction that dropped
// it would lose a machine fact.
//
// WHY THE RETURN TYPE IS SPELLED `std::uint32_t` AND NOT `Word`, THOUGH THEY ARE
// THE SAME TYPE. The two names denote one width and the body is byte-identical
// either way; the difference is only who can read the width off the declaration.
// `Word` is an alias this package introduced, so a static reader of the
// declaration cannot compute a width from it -- an alias could name anything --
// and a 4-byte machine return then has nothing to be compared with. The machine
// width is a fact and the C spelling is a source-side choice, so the
// width-computable spelling is the one that states the fact. `std::uint32_t` is
// that spelling: 4 bytes on this x86-32 target, and exactly what 8B / 40 / 89
// read, increment and write. `Word` stays for the receiver's word, where the
// alias carries no claim that a reader has to verify. The SIGN remains open and
// is recorded as such in the sidecar: INC EAX is bit-identical for a signed and
// an unsigned word and nothing here tests bit 31, so this spelling fixes the
// width and the wrap and asserts nothing about the sign beyond what the listing
// forces.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
extern "C" std::uint32_t PKG_SW1_005B2490_THISCALL re_005b2490(Receiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_005b2490
