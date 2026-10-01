// Reconstruction of SporeApp.exe 0x00b25f40 -- bounded x86-32 semantics.
//
// Every declaration here is pinned to an instruction of the 41-instruction body
// at 0x00b25f40..0x00b25f9e. Nothing about the receiver class, the concrete
// noun registry, or the callback words' meaning is claimed: the body reads none
// of them.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-00b25f40 reconstruction targets x86-32"
#endif

namespace openspore::reconstruction::pkg_00b25f40 {

// The body's terminator is `c2 04 00` RET 0x4 at 0x00b25f95 and 0x00b25f9e, so
// the callee pops its own four-byte stack argument. That is the whole of what
// the listing fixes about the convention: it says the argument is
// callee-cleaned and it does not say how a hidden receiver is passed, because
// the body never reads or writes ECX (the derived ABI record states the same
// absence). The two spellings below are the same code on this ELF i386-32
// target -- a probe of
// `__attribute__((thiscall))` against `__attribute__((stdcall))` finds the two
// types convertible, because there is no Windows ABI here to tell them apart --
// so MSVC gets the name the persisted ABI record uses and gcc gets the one it
// accepts on a free function.
#if defined(_MSC_VER) || defined(__clang__)
#define PKG_00B25F40_THISCALL __thiscall
#else
#define PKG_00B25F40_THISCALL __attribute__((stdcall))
#endif

// The hidden ECX receiver. The body never reads or writes ECX, so this type
// states only that a word arrives there and is forwarded; it is opaque on
// purpose and no layout is claimed for it.
struct NounProjection;

// The candidate the body returns. Only its first word -- the function table at
// displacement 0x00 -- is read by this body (`8b 13` MOV EDX,[EBX] at
// 0x00b25f7b); the opaque run below carries no claim about what follows.
struct NounObject;

// The vector the 0x00b21340 dependency returns. This body reads exactly two
// words of it, and only by displacement: +0x04 (`2b 77 04` SUB ESI,[EDI+0x4] at
// 0x00b25f67) and +0x08 (`8b 77 08` MOV ESI,[EDI+0x8] at 0x00b25f64).
//
// The two words are reached through displacements rather than named members.
// The machine-derived receiver record for this target is `bounds_only` with no
// base register and an empty offset set, so it states where the body was seen
// reaching and never which member is which: a member NAME would be a layout
// claim nothing here corroborates, while a displacement is a local fact the
// listing does state. No capacity, size or allocator word appears, because the
// body reads none and the listing names none.
constexpr std::size_t kContainerEndDisplacement = 0x08;
constexpr std::size_t kContainerBeginDisplacement = 0x04;

// Aligned to a pointer because the two words the body reads ARE pointers and
// are reached by displacement: a byte array would leave the container 1-aligned
// and the slots at +0x4 and +0x8 under-aligned, which one compiler tolerated
// and another did not. The alignment says nothing about a layout beyond the two
// displacements already claimed.
struct alignas(void*) NounProjectionVector {
  std::uint8_t opaque[kContainerEndDisplacement];
};

// Both accessors are lvalues so a test can repoint the container the way a
// probe would; the reconstruction itself only reads them.
inline NounObject* const*& container_begin(NounProjectionVector* container) {
  return *reinterpret_cast<NounObject* const**>(
      reinterpret_cast<std::uint8_t*>(container) + kContainerBeginDisplacement);
}

inline NounObject* const*& container_end(NounProjectionVector* container) {
  return *reinterpret_cast<NounObject* const**>(
      reinterpret_cast<std::uint8_t*>(container) + kContainerEndDisplacement);
}

// Byte displacement of the identity probe inside the candidate's function
// table: `8b 42 4c` MOV EAX,[EDX+0x4c] at 0x00b25f7d, dispatched by `ff d0`
// CALL EAX at 0x00b25f82 with ECX holding the candidate (`8b cb` MOV ECX,EBX at
// 0x00b25f80). The probe takes the candidate and returns a raw 32-bit word that
// the body compares whole against its stack argument (`3b 44 24 14` at
// 0x00b25f84); no stack argument is pushed for it.
//
// The slots below are unnamed filler: the body reads exactly one word of the
// table and this package says nothing about any other slot.
constexpr std::size_t kIdentitySlotOffset = 0x4c;
constexpr std::size_t kIdentitySlotWords = kIdentitySlotOffset / sizeof(void*);
// The same displacement written out, so editing kIdentitySlotOffset alone
// cannot move the table and the assertion together: the two are compared, not
// derived.
constexpr std::size_t kIdentitySlotOffsetFromListing = 0x4c;

using NounIdentityProbe = std::uint32_t(PKG_00B25F40_THISCALL*)(NounObject*);

struct NounObjectVtable {
  void* slots[kIdentitySlotWords];
  NounIdentityProbe slot_4c;
  // A second probe one word below the one the body dispatches. It exists so a
  // reconstruction that read 0x48 instead of 0x4c would call this and be
  // caught; nothing is claimed about what a real 0x48 slot means.
  NounIdentityProbe neighbour_below;
};

// The candidate. The body reads its FIRST word and nothing else (`8b 13` MOV
// EDX,[EBX] at 0x00b25f7b), then the table word at displacement 0x4c (`8b 42
// 4c` MOV EAX,[EDX+0x4c] at 0x00b25f7d).
//
// That first word is a BARE base load with no displacement byte in the
// encoding, so no offset is stated for it -- see
// docs/tooling/reconstruction-failure-modes.md section 1, where a stated 0x00
// would be an absence read as a constant. The one word below is only the
// storage that load needs: no larger object, no size, no member past the table
// word, and no name for what the table is.
struct NounObject {
  NounObjectVtable* first_word;
};

inline NounObjectVtable* candidate_table(NounObject* candidate) {
  return candidate->first_word;
}

// The 0x00b21340 dependency, named with its address so the call set is
// comparable against the xref export. It receives the hidden ECX receiver plus
// the five words the body pushes, and returns the vector; its own terminator is
// `c2 14 00` RET 0x14 at 0x00b21407, so it pops all five.
using NounProjectionLookupPort = NounProjectionVector*(
    PKG_00B25F40_THISCALL*)(NounProjection*, std::uint32_t, std::uint32_t,
                            std::uint32_t, std::uint32_t, std::uint32_t);

struct NativePorts {
  NounProjectionLookupPort noun_projection_lookup_00b21340;
};

extern NativePorts g_native_ports;

// The fifth word the body pushes (`68 6a 81 8c 01` PUSH 0x18c816a at
// 0x00b25f44). The data-reference artifact records one reference row out of
// this body to this address, in .reloc, with access mode "other"; the body
// pushes the address itself and never dereferences it, so nothing is claimed
// about what lives there.
extern std::uint32_t g_018c816a;

extern "C" NounObject* PKG_00B25F40_THISCALL noun_identity_resolver_00b25f40(
    NounProjection* receiver, std::uint32_t identity);

static_assert(sizeof(void*) == 4, "pkg-00b25f40 pointers are 32-bit");
static_assert(kContainerBeginDisplacement == 0x04,
              "MOV/SUB through EDI+0x4 at 0x00b25f64/0x00b25f67");
static_assert(kContainerEndDisplacement == 0x08,
              "MOV ESI,[EDI+0x8] at 0x00b25f64");
static_assert(
    kContainerEndDisplacement == sizeof(NounProjectionVector),
    "the container's two read words are its last two, and no third is claimed");
static_assert(kIdentitySlotOffset == kIdentitySlotOffsetFromListing,
              "MOV EAX,[EDX+0x4c] at 0x00b25f7d");
static_assert(offsetof(NounObjectVtable, slot_4c) == kIdentitySlotOffset,
              "MOV EAX,[EDX+0x4c] at 0x00b25f7d");
static_assert(offsetof(NounObjectVtable, neighbour_below) ==
                  kIdentitySlotOffset + sizeof(void*),
              "the neighbour probe sits one word below the dispatched slot");
static_assert(
    sizeof(NounObject) == sizeof(void*),
    "only the candidate's first word is read, by a bare base load with "
    "no displacement byte at 0x00b25f7b");
static_assert(sizeof(NounIdentityProbe) == 4, "probe target is one word");

}

#undef PKG_00B25F40_THISCALL
