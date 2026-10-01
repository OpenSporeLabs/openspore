#pragma once

// PKG-VFT-SLOT-006E64F0 -- VA 0x006e64f0
// Binary: SPORE/SporeBin/SporeApp.exe, version 3.1.0.22
//   sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// The complete original body: 4 bytes, 2 instructions, exhaustive.
//
//   0x006e64f0  8d 41 04   LEA EAX,[ECX + 0x4]
//   0x006e64f3  c3         RET
//
// The bytes were read back live from the image (read_memory @ 0x006e64f0:
// 8d 41 04 c3, then 0xcc padding) and match the bridge's
// /disassemble_function listing instruction for instruction.
//
// What the listing fixes, and what it does not:
//
//   * The body computes one value: the receiver's address plus 0x4, in EAX.
//     LEA is an address computation, not a load -- no byte of the receiver
//     is read, and nothing is written anywhere.
//   * The body has no branch, no call, no jump and no indirect transfer.
//     It is straight-line and self-contained.
//   * The terminator is a bare RET with no immediate and no stack adjustment,
//     and no stack slot is ever read. Zero ordinary stack arguments, zero
//     bytes of callee cleanup, caller owns the stack.
//   * The return register word is exactly ECX + 0x4, a 32-bit value.
//
// What is INFERRED and is not claimed as observed here:
//
//   * The receiver. The body never dereferences ECX -- LEA takes its address
//     without a memory access through it -- so the machine-derived ABI
//     record's receiver evidence is "ecx_address_taken_without_memory_access"
//     and the listing alone cannot name a receiver register. The persisted
//     record asserts __thiscall with the receiver in ECX on the strength of
//     one fact: 0x006e64f0 is the value of a slot in 66 vptr-backed vftables
//     (predicate P of tools/reconstruction_tooling/vftables.py, measured on
//     this image), and an MSVC x86-32 virtual member receives its receiver in
//     ECX. The derived record reaches the same convention through rule
//     V1-VFT: vftable slot membership, caller cleanup, no stack-argument read,
//     no incoming EDX read. This package therefore models a receiver in ECX
//     and says so; it does not claim the body observed one.
//   * The receiver's type. No record for this target names a class layout;
//     the machine-derived receiver record is bounds_only with an empty
//     offset set. The receiver is declared as void* here: the most opaque
//     spelling available, which claims nothing about the pointee. No struct
//     is typedef'd and no member is named.
//   * What the returned address denotes. The body computes receiver + 0x4
//     and returns it; whether that address is a member, a byte past the
//     vptr, or something else is not established by two instructions that
//     never dereference it. The displacement is recorded as a fact about
//     the instruction, not as a field identity.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-vft-slot-006e64f0 requires an x86-32 target"
#endif

// Portable calling-convention spelling. MSVC spells the convention as a
// keyword; GCC and clang only accept the __attribute__ form on a non-member
// declaration. The reconstruction declares a free function rather than a C++
// member, so the convention is carried by the macro rather than by the
// class. The arity matters as much as the convention: under -m32 GCC's
// thiscall implies callee-pops, so a body that took one ordinary stack
// argument would be emitted as `ret $4` and would pop a word the caller
// pushed. This body takes no ordinary stack argument, so the emitted
// terminator is the bare `ret` the listing shows.
#if defined(_MSC_VER)
#define PKG_VFT_SLOT_006E64F0_THISCALL __thiscall
#else
#define PKG_VFT_SLOT_006E64F0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_vft_slot_006e64f0 {

// An unnamed 32-bit machine word. Used for the vtable image below, which is
// read as opaque data; it is deliberately NOT the return type, which is
// spelled as a width-computable builtin (see pkg_vft_slot_006e64f0.cpp).
using OpaqueWord = std::uint32_t;

// -- Body geometry, read off the listing ------------------------------------

// Entry point, and the only function the record names for this VA.
inline constexpr OpaqueWord kTargetVa = 0x006e64f0u;
// The bare RET, and therefore the last byte of the body.
inline constexpr OpaqueWord kBodyEndVa = 0x006e64f3u;
// 4 bytes: the 3-byte LEA at kTargetVa plus the 1-byte RET.
inline constexpr std::size_t kBodyByteCount = 4u;
inline constexpr std::size_t kInstructionCount = 2u;

// -- The one displacement ---------------------------------------------------

// 0x006e64f0 is 8d 41 04: LEA EAX,[ECX + 0x4]. The displacement the
// instruction states is 0x4, and the static_assert below pins the constant
// to the address it was read from so a future edit fails at compile time
// rather than silently. The constant is named for the displacement it is,
// not for a member: the receiver record is bounds_only and names no field.
inline constexpr std::size_t kReceiverByteDisplacement = 0x4u;
static_assert(kReceiverByteDisplacement == 0x4u,
              "LEA EAX,dword ptr [ECX + 0x4] @ 0x006e64f0");

// -- Vftable membership -----------------------------------------------------

// These are observations about the data segment, not about the body. They
// are here because they are the evidence that this function is a slot
// implementation, and the receiver convention above rests on that evidence.
//
// The sound predicate P of tools/reconstruction_tooling/vftables.py, run
// over this image, finds 0x006e64f0 as a slot value in 66 distinct
// vptr-backed vftables. The first of them, by address, is recorded below
// together with the sixteen words that were actually read from it; the
// remaining 65 are counted, not transcribed. No code in the image calls
// the address directly, which is what a virtual slot looks like.
inline constexpr std::size_t kMembershipCount = 66u;
inline constexpr OpaqueWord kFirstTableBase = 0x013faea0u;
inline constexpr std::size_t kFirstTableSlotIndex = 12u;
inline constexpr std::size_t kFirstTableSlotByteOffset =
    kFirstTableSlotIndex * 4u;
inline constexpr OpaqueWord kFirstTableSlotWord =
    kFirstTableBase + kFirstTableSlotByteOffset;
// The dword immediately below the table base is zero, which bounds the
// table from below.
inline constexpr OpaqueWord kWordBelowFirstTableBase =
    kFirstTableBase - 4u;
inline constexpr OpaqueWord kWordBelowFirstTableBaseValue = 0x00000000u;

// The sixteen words of the first table starting at its base, read live
// (read_memory @ 0x013faea0, 64 bytes). Index 12 is this body. The
// neighbours are recorded so a reader can see that the slot is bounded by
// real entries rather than by silence; nothing here attributes a role to
// any of them.
inline constexpr OpaqueWord kFirstTableWords[] = {
    0x00608080u,  // +0x00
    0x00608060u,  // +0x04
    0x00608020u,  // +0x08
    0x00608000u,  // +0x0c
    0x006087b0u,  // +0x10
    0x00607190u,  // +0x14
    0x00608550u,  // +0x18
    0x00608590u,  // +0x1c
    0x00607290u,  // +0x20
    0x00801400u,  // +0x24
    0x00606d50u,  // +0x28
    0x00606d60u,  // +0x2c
    0x006e64f0u,  // +0x30 -- this body
    0x009892e0u,  // +0x34
    0x00a09f50u,  // +0x38
    0x006c10e0u,  // +0x3c
};
inline constexpr std::size_t kFirstTableWordCount =
    sizeof(kFirstTableWords) / sizeof(kFirstTableWords[0]);

// The shape of one slot of such a table: a 32-bit code pointer that takes
// the receiver in ECX and returns a 32-bit word. Nothing more is claimed
// about the table's types.
using SlotEntry = OpaqueWord;
using SlotFn = void* (PKG_VFT_SLOT_006E64F0_THISCALL*)(void*);

// -- The reconstruction -----------------------------------------------------

// Declared here, defined in pkg_vft_slot_006e64f0.cpp.
//
// The receiver is `void*` rather than a named object type: the body
// addresses no member of it, and the record's own receiver evidence is
// bounds_only with an empty offset set.
//
// The return type is written out as `void*` rather than through a local
// alias. The machine return is one 32-bit word in EAX whose value is the
// receiver's address plus 0x4; a pointer is four bytes on this target and
// is the most literal spelling of an address computation's result. The
// width is what the machine evidence corroborates; the exact C type
// spelling remains a source-side choice among the types of that width.
extern "C" void* PKG_VFT_SLOT_006E64F0_THISCALL re_006e64f0(void* self);

// The dispatch-table word values are 4 bytes on this target; the whole
// model is meaningless otherwise.
static_assert(sizeof(void*) == 4, "x86-32 pointer width is required");
static_assert(sizeof(OpaqueWord) == 4, "opaque words are 4 bytes");

// The image arithmetic is self-consistent, and the recorded slot really is
// this body. Both facts are checked here so a future edit to either side
// fails at compile time rather than silently.
static_assert(kFirstTableSlotIndex * 4u == kFirstTableSlotByteOffset,
              "slot index and slot byte offset must agree");
static_assert(kFirstTableBase + kFirstTableSlotByteOffset == kFirstTableSlotWord,
              "the slot word must be the table base plus the slot offset");
static_assert(kFirstTableWords[kFirstTableSlotIndex] == kTargetVa,
              "the recorded slot at +0x30 must hold this body's VA");
static_assert(kBodyEndVa - kTargetVa + 1u == kBodyByteCount,
              "the body spans entry through the RET inclusive");

}  // namespace openspore::reconstruction::pkg_vft_slot_006e64f0
