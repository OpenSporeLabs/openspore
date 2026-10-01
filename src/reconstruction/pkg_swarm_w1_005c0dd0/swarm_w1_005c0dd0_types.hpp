// PKG-SWARM-W1-005C0DD0 -- VA 0x005c0dd0
// FUN_005c0dd0, subsystem Sporepedia (SPORE/SporeBin/SporeApp.exe 3.1.0.22,
// image base 0x400000, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e,
// RVA 0x1c0dd0).
//
// THE BODY. Four bytes, two instructions, and nothing else:
//
//   005c0dd0  8A 41 24    MOV AL, byte ptr [ECX + 0x24]
//   005c0dd3  C3          RET
//
// Those four bytes were re-read out of the image for this package with
// GhidraMCP /read_memory at 0x005c0dd0, which returns
// `138 65 36 195 204 204 204 204` == 8A 41 24 C3 CC CC CC CC. The first four
// bytes are the two instructions above; the four 0xCC bytes that follow are
// MSVC inter-function padding. The same read is what settles the EXACT LENGTH:
// the body is 0x005c0dd0..0x005c0dd3 inclusive, span_bytes 4, instruction_count
// 2, and ghidra_function.body_end is 0x005c0dd3 (the RET's own byte, inclusive).
// The 0xCC run was verified to run to 0x005c0ddf by a second disassembly of
// 0x005c0da0..0x005c0def, which shows the preceding function ending at
// 0x005c0dc1 with `RET 0x8` and padding from 0x005c0dc4 -- so 0x005c0dd0 is an
// isolated four-byte leaf, not a slice of something longer.
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because for a
// body this small the whole claim IS the constants:
//
//  * kBodyBytes, kLoadLength, kRetOffset, kSpanBytes, kInstructionCount. Direct
//    transcription of the image bytes named above.
//
//  * kReceiverFlagByteDisplacement == 0x24. Two independent machine witnesses
//    agree and nothing else proposes a value: the instruction's own ModRM/disp
//    byte (8A 41 24 encodes displacement 0x24) and the machine-derived receiver
//    record, which is
//        {register: ECX, shape: R-DIRECT, offsets: [36], distinct_offsets: 1,
//         max_offset: 36, written_through: 0, bounds_only: true, present: true,
//         confidence: INFERRED}
//    36 decimal is 0x24. `bounds_only` means the record states where the body
//    was seen reaching and says nothing about which member is which, which is
//    why no member is NAMED below: the offset is a fact, the identity of the
//    byte is not established by any record for this target.
//
//  * kReceiverObservedExtent == 0x25. 0x24 + the one byte read, i.e. the extent
//    the body was observed touching. It is NOT a claimed object size: the real
//    object is certainly larger (0x25 is not 4-aligned) and nothing in this
//    evidence fixes its size or its class. The model test deliberately plants its
//    decoy bytes past this extent, past +0x2c, so nothing here can be the reason
//    a case passes.
//
//  * kReturnWidthBytes == 1. The only definition of the return register EAX in
//    the body is the 8A form, whose DESTINATION OPERAND is AL, so the machine
//    writes one byte. That is the whole width claim, and it is read off the
//    operand rather than guessed from the "returns a flag" shape of the code
//    around it.
//
//  * kLoadIsPartialRegisterWrite == true. `8A 41 24` is not `0F B6 41 24`
//    (MOVZX EAX, byte ptr [ECX+0x24], four bytes). The compiler chose the
//    three-byte form, so bits 8..31 of EAX are left exactly as the caller left
//    them. This is recorded as a constant so the model and its test cannot
//    quietly drift into claiming a zero-extension the machine does not perform.
//
//  * kReferencedTableCount == 12, kReferencedSlotCount == 6, kReferencedSlotIndices
//    and kReferencedTableAddresses. Read out of the committed export
//    .spore-analysis/ghidra-exports/vtables.json, which lists this address in
//    twelve tables at SIX different slot indices. That is the reason no slot
//    boundary is declared anywhere in this package: a single slot number cannot
//    be right for six different ones, and the body reads no dispatch word to
//    begin with (see VIRTUAL DISPATCH below).
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, the two
// instructions contain no register- or memory-operand transfer, and the
// xref export records no outgoing edge of any type. The body's only memory
// operand is the byte load through ECX, which is a direct field read and not a
// slot read.
//
// CALLEES: none, and none declared. The complete listing is two instructions and
// neither is a transfer; `callees` is empty, `external_callees` is unavailable
// (and so empty), and the machine-vs-machine rule is two independent sources
// both recording no outgoing transfer. The reference package for this VA's
// neighbourhood declares four extern callees because its body makes four calls;
// declaring even one here would be inventing a transfer the bytes do not
// contain. The model test therefore has no callee to observe, and says so in
// its own header.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-005c0dd0 requires an x86-32 target"
#endif

// The convention is __thiscall and the machine fixes it rather than the model
// choosing it: the body's only memory operand is based on ECX, ECX is never
// written before that read, and the terminator is a bare `RET` with no
// immediate and there is no stack read anywhere in the body -- a
// callee-cleaned `RET imm16` and a caller-cleaned `RET` with zero arguments are
// the same shape here, and both records (persisted and derived) resolve to
// __thiscall with cleanup side "caller" and 0 bytes.
//
// GCC 16 rejects the bare MSVC keywords, so the x86-32 attribute form is the
// portable spelling and the keyword form is kept for MSVC. This mirrors the
// reference package; see its recorded note that the prescribed macro pattern
// itself is not -Wpedantic-clean on GCC. The mandated gate does not enable
// -Wpedantic.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_005C0DD0_THISCALL __thiscall
#else
#define PKG_SWARM_W1_005C0DD0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_005c0dd0 {

// -- the body, byte for byte ------------------------------------------------
// 8A 41 24 C3, transcribed from /read_memory at 0x005c0dd0.
constexpr std::array<std::uint8_t, 4> kBodyBytes = {0x8a, 0x41, 0x24, 0xc3};
// The load is three bytes (modrm 0x41 = [ECX+disp8], then the disp8 itself), so
// the terminator is the fourth byte.
constexpr std::size_t kLoadLength = 3;
constexpr std::size_t kRetOffset = 3;
constexpr std::size_t kSpanBytes = 4;
constexpr std::size_t kInstructionCount = 2;
// The load's displacement byte, and the value it encodes. The 0x24 constant in
// the body comes from the second of these two facts, not from the first.
constexpr std::uint8_t kLoadDisplacementByte = 0x24;
constexpr std::size_t kReceiverFlagByteDisplacement = 0x24;
// 0x24 + the one byte read. The observed extent, not a claimed object size.
constexpr std::size_t kReceiverObservedExtent = 0x25;
// The return register's definition writes AL, so the machine's return width is
// one byte.
constexpr std::size_t kReturnWidthBytes = 1;
// The 8A form is a partial register write. Bits 8..31 of EAX are NOT set by the
// body and are not asserted anywhere in this package.
constexpr bool kLoadIsPartialRegisterWrite = true;
// Zero ordinary stack arguments; a bare RET with no immediate.
constexpr std::size_t kStackArgumentSlots = 0;
constexpr std::size_t kStackCleanupBytes = 0;

// -- the receiver ------------------------------------------------------------
// An opaque byte run of the observed extent. No member is declared for the byte
// at 0x24 because the machine-derived receiver record is `bounds_only`: it
// enumerates the displacement and identifies nothing. Calling that byte a flag,
// an enabled-bit, a mode or a predicate would be a member story this evidence
// does not carry, and the one place a reader might be tempted to reach for one
// is closed in the .cpp: both direct callers consume the result as a raw byte
// or a zero test, and NEITHER of them establishes a domain.
struct alignas(1) SporepediaByteRecord {
  std::array<std::uint8_t, kReceiverObservedExtent> opaque;
};
static_assert(sizeof(SporepediaByteRecord) == 0x25,
              "the observed extent is the displacement plus the one byte read");

// The only way this body touches the receiver: a byte at a stated displacement.
// A member access would assert an identity the receiver record cannot
// corroborate, and a `field_24` name in the body would make the reconstruction
// claim a field the machine evidence only bounds.
inline const std::uint8_t* byte_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint8_t*>(base) + displacement;
}

inline std::uint8_t* byte_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint8_t*>(base) + displacement;
}

// -- the twelve tables that reference this address ---------------------------
// From .spore-analysis/ghidra-exports/vtables.json. Recorded for the integrator
// and asserted by the model test so a transcription error cannot pass silently;
// deliberately NOT modelled as a slot, because six different indices appear and
// the body never reads a dispatch word. Every entry there that neighbours this
// one in those tables is exported with sdk=true and a
// `Sporepedia::cSPAssetDataOTDB::` name; THIS entry is exported with sdk=false
// and carries no name, so no class and no method name is claimed for it.
constexpr std::size_t kReferencedTableCount = 12;
constexpr std::size_t kReferencedSlotCount = 6;
constexpr std::array<std::size_t, 6> kReferencedSlotIndices = {4, 14, 15, 26, 29, 33};
constexpr std::array<std::uint32_t, 12> kReferencedTableAddresses = {
    0x013f7cc0, 0x013f7de0, 0x013ff648, 0x013ff6ac, 0x0147c9e8, 0x0147ca30,
    0x0147cbbc, 0x0147cc14, 0x01489090, 0x014890f4, 0x014893b0, 0x01489414};

// -- the reconstructed symbol ------------------------------------------------
// __thiscall, receiver in ECX, zero ordinary stack arguments, bare `RET`.
//
// The return type is std::uint8_t and the choice is deliberately the least
// committal spelling of what the machine fixes. The machine fixes a WIDTH of
// one byte (the destination operand is AL) and nothing else: `bool`,
// `unsigned char` and `std::uint8_t` all compile to these same three bytes, and
// nothing in the body masks the value to {0, 1}, so `bool` would claim a domain
// the evidence does not establish. See the .cpp for what is and is not asserted
// about bits 8..31 of EAX.
//
// A wider return type would be a contradiction: the machine writes AL, so
// `int`/`std::uint32_t` would assert four bytes the body does not produce.
extern "C" std::uint8_t PKG_SWARM_W1_005C0DD0_THISCALL re_005c0dd0(
    SporepediaByteRecord* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_005c0dd0
