#pragma once

// Reconstruction of FUN_00b7e380 @ 0x00b7e380 (SporeApp.exe 3.1.0.22).
//
// Evidence basis (all from the live Ghidra bridge on SporeApp.exe):
//   * disassembly 0x00b7e380..0x00b7e384 - exactly two instructions:
//       0x00b7e380  8d 41 2c               LEA EAX,dword ptr [ECX + 0x2c]
//       0x00b7e383  c3                     RET
//     raw bytes 0x00b7e380: 8d 41 2c c3
//   * V1-VFT rule: 0x00b7e380 is slot 38 of the vptr-backed vftable at
//     0x013ff648 (and also 0x01489090, 0x014893b0), so it is a non-static
//     virtual member function; the callee pops nothing and no stack word is
//     read as an argument, so the receiver is in ECX and the convention is
//     __thiscall with 0 ordinary stack arguments.
//
// The body computes EAX = ECX + 0x2c and returns. It is a getter that returns
// a pointer to a member at offset 0x2c of the receiver. The member's type is
// not established (the receiver is bounds_only), so the return type is void*.
//
// WHAT THE EVIDENCE DOES AND DOES NOT CARRY ABOUT THAT MEMBER: the machine
// proves a displacement (0x2c, under ECX) and a width (32-bit pointer in EAX).
// It does not prove which member of any type occupies that word, and nothing
// in this package's evidence pack names one. So `OpaqueReceiver` below
// declares no member at all - not `field_2c`, not a pointer, not a char - and
// the receiver is reached only through the `member_at` displacement accessor.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00b7e380 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00B7E380_THISCALL __thiscall
#else
#define PKG_00B7E380_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c {

using Opaque = std::uint32_t;

struct OpaqueReceiver;

// The vtable image this method was observed in, described as a standalone
// table and NOT embedded in OpaqueReceiver: the 0x00b7e380 body never reads
// [ECX+0x00], so no vtable pointer field is claimed on the receiver. Slot
// displacements are relative to the table base T. The table spans 39 slots
// (0x00..0x98); only slot 38 (+0x98) is named because it is the only slot
// this package's evidence reads.
struct OpaqueReceiverVTable {
  Opaque slots[39]{};  // T + 0x00 .. T + 0x98
};

// Slot 38 (+0x98) of the vtable image: the word this method is stored at.
inline Opaque& slot_98(OpaqueReceiverVTable& vtable) { return vtable.slots[38]; }
inline const Opaque& slot_98(const OpaqueReceiverVTable& vtable) { return vtable.slots[38]; }

// Receiver of the target function, modelled at exactly the width the machine
// read and no more: 0x30 bytes, 4-byte aligned, i.e. the prefix through the
// one word the body reaches. 0x00..0x2b is never read or written by the body,
// and 0x2c..0x2f is the word 0x00b7e380 computes an address for. No member is
// declared, because no evidence in this package names one; the extent is a
// modelling bound, not a recovered allocation size.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0x30> opaque_bytes{};  // 0x00..0x2f
};

// The displacement the body was observed reaching on the receiver, from
// `LEA EAX,dword ptr [ECX + 0x2c]` at 0x00b7e380. It is a value, not a member:
// the record enumerates displacements and cannot say which member is which.
constexpr std::size_t kMemberDisplacement = 0x2c;

// The only way this package touches the receiver: a 4-byte word at a stated
// displacement. Naming a member instead would assert an identity the receiver
// record (offsets=[0x2c], bounds_only) cannot corroborate.
inline Opaque* member_at(OpaqueReceiver* receiver, std::size_t displacement) {
  return reinterpret_cast<Opaque*>(reinterpret_cast<std::uintptr_t>(receiver) +
                                    displacement);
}

inline Opaque member_at(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const Opaque*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// x86-32 thiscall: receiver in ECX, 0 ordinary stack arguments, caller
// cleans the stack (bare RET), and a pointer return (EAX = ECX + 0x2c).
using AbiMemberPtr00b7e380 = void*(PKG_00B7E380_THISCALL*)(OpaqueReceiver*);

static_assert(sizeof(void*) == 4, "pointers are 32-bit");
static_assert(sizeof(Opaque) == 4, "opaque words are 32-bit");
static_assert(sizeof(OpaqueReceiver) == 0x30,
              "modeled receiver extent through the reached word");
static_assert(offsetof(OpaqueReceiver, opaque_bytes) == 0,
              "the receiver's first byte is its base");
static_assert(kMemberDisplacement + sizeof(Opaque) == sizeof(OpaqueReceiver),
              "the only displacement the body reaches ends the modeled extent");
static_assert(sizeof(OpaqueReceiverVTable) == 0x9c,
              "the vtable image spans 39 slots (0x00..0x98)");
static_assert(sizeof(OpaqueReceiverVTable) == 39 * sizeof(Opaque),
              "each vtable slot is one 32-bit word");
static_assert(
    std::is_same<AbiMemberPtr00b7e380,
                 void*(PKG_00B7E380_THISCALL*)(OpaqueReceiver*)>::value,
    "modeled entry carries the ECX receiver and returns a pointer");

// Entry point under reconstruction. The name carries the displacement
// (0x2c -> "0x2c") plus the 8-hex target VA so the validator can bind this
// span to 0x00b7e380.
void* PKG_00B7E380_THISCALL member_ptr_0x2c_00b7e380(OpaqueReceiver* receiver);

}

#undef PKG_00B7E380_THISCALL
