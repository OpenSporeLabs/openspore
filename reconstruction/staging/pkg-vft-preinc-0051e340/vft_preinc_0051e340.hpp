#pragma once

// Reconstruction of 0x0051e340 -- virtual member (vftable slot), receiver in ECX.
// Binary: SPORE/SporeBin/SporeApp.exe 3.1.0.22
//   sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// Original body, 52 bytes, 20 instructions, exhaustive:
//   0x0051e340  PUSH EBP
//   0x0051e341  MOV EBP,ESP
//   0x0051e343  SUB ESP,0xc
//   0x0051e346  MOV dword ptr [EBP + -0x8],ECX
//   0x0051e349  MOV EAX,dword ptr [EBP + -0x8]
//   0x0051e34c  ADD EAX,0x4
//   0x0051e34f  MOV dword ptr [EBP + -0x4],EAX
//   0x0051e352  MOV ECX,dword ptr [EBP + -0x4]
//   0x0051e355  MOV EDX,dword ptr [ECX + 0x4]
//   0x0051e358  ADD EDX,0x1
//   0x0051e35b  MOV dword ptr [EBP + -0xc],EDX
//   0x0051e35e  MOV EAX,dword ptr [EBP + -0x4]
//   0x0051e361  MOV ECX,dword ptr [EAX + 0x4]
//   0x0051e364  ADD ECX,0x1
//   0x0051e367  MOV EDX,dword ptr [EBP + -0x4]
//   0x0051e36a  MOV dword ptr [EDX + 0x4],ECX
//   0x0051e36d  MOV EAX,dword ptr [EBP + -0xc]
//   0x0051e370  MOV ESP,EBP
//   0x0051e372  POP EBP
//   0x0051e373  RET
//
// The body is a vftable slot implementation: 0x0051e340 is the value of a slot
// in 42 vptr-backed vftables (predicate P, tools/reconstruction_tooling/
// vftables.py), the callee pops nothing, and no stack word is read as an
// argument, so the receiver arrives in ECX and the convention is __thiscall
// (rule V1-VFT; see the sidecar's observed_original_abi). The class is not
// named: ICF collapse across 42 tables means membership yields "virtual
// member of some class", never a class identity.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "vft_preinc_0051e340 (0x0051e340) requires x86-32"
#endif

// The free-function __thiscall spelling below is deliberate: the original is a
// virtual member function, and the reconstruction keeps the machine's register
// receiver in the signature rather than modelling a C++ member. GCC rejects
// that spelling for a non-class method under -Wattributes, so the diagnostic
// is narrowed here instead of in the build flags.
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

namespace openspore::reconstruction::pkg_vft_preinc_0051e340 {

using OpaqueWord = std::uint32_t;

#if defined(_MSC_VER)
#define PKG_VP_THISCALL __thiscall
#else
#define PKG_VP_THISCALL __attribute__((thiscall))
#endif

// The receiver is left opaque on purpose. The machine-derived receiver record
// is bounds_only and enumerates no offsets: ECX is spilled, reloaded with the
// derived address receiver+4, and only then dereferenced, so the engine records
// "ecx_reassigned_before_deref" and no receiver-relative offset. No member
// name is claimed; the body addresses one dword at receiver+8.
struct Receiver;

// The slot type this body occupies in every table that holds it.
using SlotType = std::uint32_t(PKG_VP_THISCALL*)(Receiver*);

// Displacement constants, each pinned to the instruction that states it.
// kBaseDisplacement is the ADD EAX,0x4 operand: the machine forms the byte
// address receiver+4 and spills it. kFieldDisplacement is the [ECX + 0x4]
// operand: the field dword is read through that derived address. The field's
// receiver-relative offset is the composition of the two, which the machine
// never states as a single operand.
inline constexpr std::size_t kBaseDisplacement = 0x4;
inline constexpr std::size_t kFieldDisplacement = 0x4;
inline constexpr std::size_t kFieldReceiverOffset = 0x8;

static_assert(kBaseDisplacement == 0x4, "ADD EAX,0x4 @ 0x0051e34c");
static_assert(kFieldDisplacement == 0x4, "MOV EDX,dword ptr [ECX + 0x4] @ 0x0051e355");
static_assert(kFieldReceiverOffset == kBaseDisplacement + kFieldDisplacement,
              "the field dword sits at receiver+8: 0x0051e34c composes with 0x0051e355");
static_assert(sizeof(OpaqueWord) == 4, "opaque words are 32-bit");
static_assert(sizeof(void*) == 4, "receiver pointers are 32-bit");

// Vtable placement, read live from the binary. The engine's V1-VFT inference
// cites 42 memberships; the first is slot 0 of the table based at 0x013ef110,
// where the word at 0x013ef110 is 0x0051e340 and the next slot holds the
// adjacent virtual 0x0051e380. In other tables of the same family the pair
// sits at slots 14/15 (e.g. 0x013f2194, 0x013f21d8); the slot index is a
// property of each table, not of the body.
inline constexpr OpaqueWord kFirstVTableBase = 0x013ef110u;
inline constexpr std::size_t kFirstVTableSlotIndex = 0;
inline constexpr OpaqueWord kAdjacentVirtualVa = 0x0051e380u;
inline constexpr std::size_t kMembershipCount = 42;

static_assert(kFirstVTableSlotIndex * 4 == 0, "slot 0 sits at the table base");

extern "C" std::uint32_t PKG_VP_THISCALL vft_preinc_0051e340(Receiver* self);

}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
