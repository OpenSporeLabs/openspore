#pragma once

// VA 0x008d86b0 - Resource::DatabasePackedFile::DestroyIndex
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22).
//
// Machine body (7 bytes, complete, from the live binary):
//   008d86b0  8B 81 60 02 00 00   MOV EAX, dword ptr [ECX + 0x260]
//   008d86b6  C3                  RET
//   008d86b7  CC                  INT3 padding, not part of the function
//
// WHAT THE RECEIVER EVIDENCE CARRIES FOR THIS BODY, AND WHAT IT DOES NOT. The
// machine-derived receiver record enumerates offsets=[0x260] for register ECX
// and is bounds_only: it saw the body reach one word of the receiver and could
// say no more. The complete two-instruction listing agrees, and it establishes
// four things about that word and nothing else: it is 4 bytes wide (`dword`),
// it sits at displacement 0x260 under ECX, it is READ (never written), and the
// read is unconditional - there is no TEST, no branch and no call in the body.
//
// It establishes nothing about which member of the carrier occupies that word.
// `index_ref` was such a name, and the machine-derived record cannot confirm
// it: a record of displacements says where the body reached, not what it found
// there. So the carrier below declares no member at all and the body reaches
// the word as a displacement.
//
// The pointee is a different matter and is kept: the adjacent vtable slot +0x50
// (0x008d86c0) treats [this+0x260] as a polymorphic object and drives it
// through its vtable - AddRef at vtable +0x04, Release at vtable +0x08 - and
// FUN_008d8c50 calls vtable +0x28 on the same pointer. That is evidence, from
// other bodies, about the OBJECT the word holds; it is not evidence about the
// word itself, and no EA class name is claimed for it. The concrete class of
// the pointee is not identified anywhere in the binary, so the pointee is
// modelled only as a vtable-bearing handle.

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "resource index-ref reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_resource_index_ref_008d86b0 {

struct ObservedIndexObject;

// Partial vtable model. Only the two slots this reconstruction can prove are
// declared; FUN_008d8c50 also calls the +0x28 slot of the same pointee, which
// is not modelled here. The slot targets are __thiscall on the pointee, not on
// the vtable: 0x008d86dd loads the vtable pointer into EAX, loads the slot
// from [EAX+0x4] into EDX, then sets ECX to the pointee (ESI) before CALL EDX.
struct ObservedIndexObjectVtable {
  void* slot_00;
  void (*add_ref_at_04)(ObservedIndexObject*);
  void (*release_at_08)(ObservedIndexObject*);
};

struct ObservedIndexObject {
  ObservedIndexObjectVtable* vtable;
};

// Carrier for the `this` of the target, modelled as far as the evidence reaches
// and no further: an opaque run of 0x264 bytes, the prefix through the last word
// the body reads. No member is declared.
//
// Two displacements of this object appear in this package's evidence, and
// neither of them is a member name:
//
//   +0x14   read by the adjacent vtable slot +0x50 (0x008d86c0, at 0x008d86c3
//           `CMP dword ptr [EBX + 0x14],0x0`) as a plain zero/non-zero gate on
//           the paired write. THIS BODY NEVER READS IT.
//   +0x260  the one word 0x008d86b0 reads.
//
// The 0x264 extent is a modelling bound chosen to hold the word at 0x260, not a
// recovered allocation size. (The original model carried 0x280 bytes; nothing
// in this package's evidence mentions a byte past 0x263, so the extra 28 bytes
// were padding with no witness behind them and are dropped.)
struct alignas(4) ObservedIndexRefCarrier {
  std::array<std::uint8_t, 0x264> opaque_00{};
};

// The two carrier displacements this package has evidence for, as values. The
// second is the one 0x008d86b0 itself reads; the first belongs to the adjacent
// writer at 0x008d86c0 and is listed so the model test can drive that writer.
constexpr std::size_t kCarrierStateGateDisplacement = 0x14;
constexpr std::size_t kCarrierIndexWordDisplacement = 0x260;

// The only way this package touches the carrier: a 4-byte word at a stated
// displacement. A member access would assert an identity the receiver record
// (offsets=[0x260], bounds_only) cannot confirm.
inline std::uint32_t* word_at(ObservedIndexRefCarrier* file,
                              std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(file) + displacement);
}

inline const std::uint32_t* word_at(const ObservedIndexRefCarrier* file,
                                    std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(file) + displacement);
}

#if defined(_MSC_VER)
#define OPENSPORE_INDEX_REF_THISCALL __thiscall
#else
#define OPENSPORE_INDEX_REF_THISCALL __attribute__((thiscall))
#endif

// VA 0x008d86b0 - Resource::DatabasePackedFile::DestroyIndex.
//
// __thiscall, receiver in ECX, no stack argument (plain RET, not RET 0x4),
// result in EAX. Pure accessor: it copies the word and performs no
// AddRef/Release, no null test and no branch of any kind.
ObservedIndexObject* OPENSPORE_INDEX_REF_THISCALL destroy_index_008d86b0(
    ObservedIndexRefCarrier* file);

#undef OPENSPORE_INDEX_REF_THISCALL

static_assert(sizeof(void*) == 4, "observed pointers are 32-bit");
static_assert(kCarrierIndexWordDisplacement + sizeof(std::uint32_t) ==
                  sizeof(ObservedIndexRefCarrier),
              "0x260 + 4 is the last byte this body reads");
static_assert(kCarrierStateGateDisplacement + sizeof(std::uint32_t) <
                  kCarrierIndexWordDisplacement,
              "the two observed carrier words do not overlap");
static_assert(offsetof(ObservedIndexObjectVtable, add_ref_at_04) == 0x04,
              "AddRef vtable slot");
static_assert(offsetof(ObservedIndexObjectVtable, release_at_08) == 0x08,
              "Release vtable slot");

}
