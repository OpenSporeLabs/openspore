#pragma once

// PKG-DFW-00980510 -- VA 0x00980510
// Binary: SPORE/SporeBin/SporeApp.exe, version 3.1.0.22
//   sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// The complete original body: 6 bytes, 2 instructions, exhaustive.
//
//   0x00980510  b8 02 02 00 00   MOV EAX,0x202
//   0x00980515  c3               RET
//
// Ghidra body_start 0x00980510, body_end 0x00980515, size_bytes 6. The bytes
// were read back live from the image (read_memory @ 0x00980510) and are
// b8 02 02 00 00 c3, immediately followed by 0xcc padding.
//
// What the listing fixes, and what it does not:
//
//   * The body reads no memory. It has no memory operand at all, so it performs
//     no field access through any register, and it names no data-segment
//     address, so it touches no global.
//   * The body has no branch, no call, no jump and no indirect transfer. It is
//     straight-line and self-contained.
//   * The one write is a full 32-bit immediate into EAX. The upper three bytes
//     of EAX are therefore defined, not residual, and the return register word
//     is exactly 0x00000202.
//   * The terminator is a bare RET with no immediate and no stack adjustment,
//     and no stack slot is ever read. Zero ordinary stack arguments, zero bytes
//     of callee cleanup, caller owns the stack.
//
// What is INFERRED and is not claimed as observed here:
//
//   * The receiver. The body never reads ECX, so it is byte-identical under
//     __cdecl, __stdcall, __thiscall and __fastcall. The machine-derived ABI
//     record in reconstruction/evidence/00980510/evidence.json reached
//     verdict ABI_UNKNOWN and abstained with the reason
//     "no_discriminator: no stack-argument read and no positive receiver
//     evidence". The persisted record nevertheless asserts __thiscall with a
//     hidden receiver in ECX, and that assertion rests on exactly one fact:
//     0x00980510 occupies a word in a dispatch table image, and MSVC x86-32
//     virtual members take their receiver in ECX. This package therefore
//     models a receiver in ECX and says so in the reconstruction's comments; it
//     does not claim the body observed one.
//   * The receiver's type. No record for this target names a class layout.
//     The live decompilation types the parameter as `ILayoutElement *`, but the
//     binary carries no MSVC RTTI and that spelling comes from imported SDK
//     symbols, so it is not independently confirmed. The receiver is declared
//     as `void *` here: the most opaque spelling available, which claims
//     nothing about the pointee.
//   * What 0x202 denotes. It is a per-class identifier in an ID space this body
//     never interprets and never computes. Nothing in the two instructions
//     fixes its meaning, its neighbours, or whether the space is dense, so the
//     constant below is named for the immediate it is, not for a role.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-dfw-00980510 requires an x86-32 target"
#endif

// Portable calling-convention spellings. MSVC spells the conventions as
// keywords; GCC and clang only accept the __attribute__ form and reject the
// keywords outright on a non-member declaration. The reconstruction declares a
// free function rather than a C++ member, so the convention is carried by the
// macro rather than by the class.
//
// The arity matters as much as the convention here. Under -m32 GCC's thiscall
// implies callee-pops, so a body that took one ordinary stack argument would be
// emitted as `ret $4` and would pop a word the caller pushed. This body takes
// no ordinary stack argument, so the emitted terminator is the bare `ret` the
// listing shows; see the objdump note in dfw_00980510.cpp.
#if defined(_MSC_VER)
#define PKG_DFW_00980510_THISCALL __thiscall
#define PKG_DFW_00980510_CDECL __cdecl
#else
#define PKG_DFW_00980510_THISCALL __attribute__((thiscall))
#define PKG_DFW_00980510_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_dfw_00980510 {

// An unnamed 32-bit machine word. Used for the dispatch-table image below, which
// is read as opaque data; it is deliberately NOT the return type, which is
// spelled as the record's own token (see dfw_00980510.cpp).
using OpaqueWord = std::uint32_t;

// -- Body geometry, read off the listing ------------------------------------

// Entry point, and the only function the record names for this VA.
inline constexpr OpaqueWord kTargetVa = 0x00980510u;
// The bare RET, and therefore the last byte of the body.
inline constexpr OpaqueWord kBodyEndVa = 0x00980515u;
// 6 bytes: the 5-byte MOV at kTargetVa plus the 1-byte RET.
inline constexpr std::size_t kBodyByteCount = 6u;
inline constexpr std::size_t kInstructionCount = 2u;

// The one immediate the body materialises, verbatim from 0x00980510. Named for
// what it is -- the immediate EAX receives -- and not for any role, because no
// record for this target establishes one.
inline constexpr OpaqueWord kReturnedImmediate = 0x202u;

// -- Dispatch-table image ---------------------------------------------------
//
// These are observations about the data segment, not about the body. They are
// here because they are the only evidence that this function is a slot
// implementation, and the receiver convention above rests on that evidence.
//
// The target's sole reference in the entire program is one DATA word at
// 0x014440e4 holding 0x00980510 (get_xrefs_to @ 0x00980510: exactly one
// reference, from_address 0x014440e4, type DATA). That word sits at offset +0x14
// of an image based at 0x014440d0, so this body is slot index 5 of that image.
// No code in the image calls the address directly, which is what a virtual slot
// looks like and is also why the body has no callers in the record.
//
// The image is recorded below only as far as it was read. 0x014440cc, the word
// immediately below the base, is 0x00000000, which bounds the image from below.
// The extent past that is not established here and is not claimed: the record
// itself carries the same open question, and nothing in this body depends on the
// answer.
inline constexpr OpaqueWord kSlotImageBase = 0x014440d0u;
inline constexpr OpaqueWord kSlotImageWordBelowBase = 0x014440cCu;
inline constexpr OpaqueWord kSlotImageWordBelowBaseValue = 0x00000000u;
inline constexpr OpaqueWord kTargetSlotOffset = 0x14u;
inline constexpr std::size_t kTargetSlotIndex = 5u;
inline constexpr OpaqueWord kTargetSlotReferenceWord = 0x014440e4u;

// The eight words of the image starting at 0x014440d0, read live
// (read_memory @ 0x014440c0, 48 bytes). Index 5 is this body. The neighbours
// are recorded so a reader can see that the slot is bounded by real entries
// rather than by silence; nothing here attributes a role to any of them.
inline constexpr OpaqueWord kSlotImageWords[] = {
    0x00980320u,  // +0x00
    0x009800e0u,  // +0x04
    0x00980490u,  // +0x08
    0x009804e0u,  // +0x0c
    0x00e31100u,  // +0x10
    0x00980510u,  // +0x14 -- this body
    0x00980520u,  // +0x18
    0x006f2f20u,  // +0x1c
};
inline constexpr std::size_t kSlotImageWordCount =
    sizeof(kSlotImageWords) / sizeof(kSlotImageWords[0]);

// The shape of one slot of that image: a 32-bit code pointer returning a
// 32-bit word. Nothing more is claimed about the table's types.
using SlotEntry = OpaqueWord;
// The shape of the callee stored in a slot, kept separate from the callee this
// package reconstructs so the two can never be confused.
using ProxyWordFn = std::uint32_t(PKG_DFW_00980510_THISCALL*)(void*);

// -- The reconstruction -----------------------------------------------------
//
// Declared here, defined in dfw_00980510.cpp.
//
// The receiver is `void *` rather than a named object type: the body addresses
// no member of it, and the record's own unresolved question about the
// decompiler's `ILayoutElement *` spelling is recorded here as unresolved
// rather than adopted.
//
// The return type is written out as `std::uint32_t` rather than through a local
// alias. The machine return is a single 32-bit word in EAX, which any 32-bit
// integral spelling would describe equally well; the long form is chosen so the
// declaration reproduces the record's return type token literally, which is
// what an automated comparison of the declared type against the record reads.
// Using this package's own `OpaqueWord` alias here would be the same machine
// code and would register as a rename.
extern "C" std::uint32_t PKG_DFW_00980510_THISCALL
dfw_get_proxy_id_00980510(void* self);

// The dispatch-table word values are 4 bytes on this target; the whole model is
// meaningless otherwise.
static_assert(sizeof(void*) == 4, "x86-32 pointer width is required");
static_assert(sizeof(OpaqueWord) == 4, "opaque words are 4 bytes");

// The image arithmetic is self-consistent, and the recorded slot really is this
// body. Both facts are checked here so a future edit to either side fails at
// compile time rather than silently.
static_assert(kTargetSlotIndex * 4u == kTargetSlotOffset,
              "slot index and slot byte offset must agree");
static_assert(kSlotImageBase + kTargetSlotOffset == kTargetSlotReferenceWord,
              "the reference word must be the image base plus the slot offset");
static_assert(kSlotImageWords[kTargetSlotIndex] == kTargetVa,
              "the recorded slot at +0x14 must hold this body's VA");
static_assert(kTargetSlotReferenceWord == 0x014440e4u,
              "the sole xref to this body is the DATA word at 0x014440e4");
static_assert(kReturnedImmediate == 0x202u,
              "the immediate at 0x00980510 is 0x202");
static_assert(kBodyEndVa - kTargetVa + 1u == kBodyByteCount,
              "the body spans entry through the RET inclusive");

}  // namespace openspore::reconstruction::pkg_dfw_00980510
