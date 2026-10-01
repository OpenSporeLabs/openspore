#pragma once

// Reconstruction of the 0x008db310 index bounds probe
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22).
//
// Evidence basis, re-read for this package: the complete 57-instruction listing
// 0x008db310..0x008db38d and the machine-derived receiver record for it
// (register ECX, offsets=[0x2c, 0x30, 0x34, 0x38], bounds_only).
//
// WHAT THE RECEIVER EVIDENCE CARRIES, AND WHAT IT DOES NOT. The listing reaches
// the receiver through ECX at exactly two displacements:
//
//   0x008db320  MOV EDX,dword ptr [ECX + 0x2c]   -> 0x008db343's base
//   0x008db33d  MOV ESI,dword ptr [ECX + 0x30]
//   0x008db340  MOV ECX,dword ptr [ECX + 0x2c]   -> read a second time
//
// The record's own enumeration (0x2c, 0x30, 0x34, 0x38) is a lower bound: it saw
// the body reach the word at 0x2c and could say no more, and the two extra
// values are its "seen somewhere" residue. Either way it is a SET OF OFFSETS. It
// says where the body reached and not which member is which, so the carrier type
// below declares no member: `slots_2c` and `end_slot_30` were names this
// evidence cannot corroborate, and the receiver is instead an opaque run the
// body reaches as displacements.
//
// The item node is a different object - the body dereferences a pointer the slot
// array holds, and it reads three of its words - and its own layout is stated by
// the same three instructions: 0x008db350 `MOV ESI,[EAX + 0x10]`,
// 0x008db357 `MOV ECX,[EAX + 0xc]` and 0x008db364 `MOV EAX,[EAX + 0x1c]`. Those
// are displacements, so the body writes them as displacements. What the node
// means - a key, a length, a chain link - is not in this body's evidence, and the
// 0x20-byte extent is a modelling bound chosen to hold the three words, not a
// recovered allocation size.

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-orchestrate-dogfood-008db310 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-008db310 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_008db310 {

using OpaqueWord = std::uint32_t;

// The node the body walks, as three displacements and nothing else:
//   0x008db350  MOV ESI,dword ptr [EAX + 0x10]
//   0x008db357  MOV ECX,dword ptr [EAX + 0xc]
//   0x008db364  MOV EAX,dword ptr [EAX + 0x1c]
struct alignas(4) OpaqueItemNode {
  std::uint8_t opaque_00[0x20]{};
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(sizeof(OpaqueItemNode) == 0x20,
              "0x1c + 4 is the last word the body reads on a node");

// The carrier, as two displacements and nothing else:
//   0x008db320 / 0x008db340  MOV ...,dword ptr [ECX + 0x2c]
//   0x008db33d               MOV ESI,dword ptr [ECX + 0x30]
struct alignas(4) OpaqueWriteCarrier {
  std::uint8_t opaque_00[0x34]{};
};

static_assert(sizeof(OpaqueWriteCarrier) == 0x34,
              "0x30 + 4 is the last word the body reads on the carrier");

// Every displacement the body is seen reaching, as values.
constexpr std::size_t kCarrierSlotArrayDisplacement = 0x2c;
constexpr std::size_t kCarrierEndSlotDisplacement = 0x30;
constexpr std::size_t kNodeRecordBeginDisplacement = 0xc;
constexpr std::size_t kNodeRecordSizeDisplacement = 0x10;
constexpr std::size_t kNodeChainDisplacement = 0x1c;

// The only way this package touches the carrier or a node: a 4-byte word at a
// stated displacement. A member access would assert an identity the receiver
// record (a set of displacements, bounds_only) cannot confirm.
inline OpaqueWord* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<OpaqueWord*>(reinterpret_cast<std::uintptr_t>(base) +
                                       displacement);
}

inline const OpaqueWord* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const OpaqueWord*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

static_assert(kCarrierEndSlotDisplacement + sizeof(OpaqueWord) ==
                  sizeof(OpaqueWriteCarrier),
              "the end-slot word ends the modeled carrier");
static_assert(kNodeChainDisplacement + sizeof(OpaqueWord) == sizeof(OpaqueItemNode),
              "the chain word ends the modeled node");
static_assert(kCarrierSlotArrayDisplacement + sizeof(OpaqueWord) ==
                  kCarrierEndSlotDisplacement,
              "the two receiver words are adjacent and non-overlapping");
static_assert(kNodeRecordBeginDisplacement + sizeof(OpaqueWord) ==
                  kNodeRecordSizeDisplacement,
              "the two record words are adjacent and non-overlapping");

using DispatchSlot014368bc = bool(PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL*)(
    OpaqueWriteCarrier*, void*, OpaqueWord);

struct alignas(4) OpaquePorts {
  DispatchSlot014368bc dispatch_014368bc = nullptr;
};

static_assert(sizeof(DispatchSlot014368bc) == 4, "dispatch port width");
static_assert(sizeof(OpaquePorts) == 4, "port table extent");
static_assert(
    std::is_same<DispatchSlot014368bc,
                 bool(PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL*)(
                     OpaqueWriteCarrier*, void*, OpaqueWord)>::value,
    "dispatch entry takes the carrier and the two observed stack words");

extern OpaquePorts g_pf_index_write_008db310_ports;

extern "C" bool PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
pf_index_write_bounds_008db310(OpaqueWriteCarrier* index, void* destination,
                               OpaqueWord destination_size);

}

#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
