#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-w1-core-b16 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4, "wave13-w1-core-b16 requires 32-bit pointers");

namespace openspore::reconstruction::wave13_w1_core_b16 {

// The two process-wide globals the observed body guards on. Both live in the
// 0x0167ecc8..0x0167ecdf neighbourhood and read as zero in the shipped image,
// so they are populated at runtime only.
//
//   0x0167ecd0  dword  read at 0x00b515e0 and by every other function in the
//                     create/release cluster. Acts as a master guard: while it
//                     is null, every path in the cluster returns immediately.
//   0x0167ecd4  dword  the cached object. Written by the lazy builder
//                     0x00b512f0 at 0x00b513e5 and nulled by the release port
//                     0x00b4f7f0 at 0x00b4f81f.
extern std::uint32_t* const kGuardGlobal_0167ecd0;
extern std::uint32_t* const kCachedObjectGlobal_0167ecd4;

// Receiver of 0x00b515e0. Layout is only partially established: +0x20, +0x30,
// +0x60, +0x64 and +0x14c8 are read or written by functions that provably
// operate on the same singleton (0x00b5a2d0, 0x00b5a390, 0x00b57a50), but the
// class name and the fields in between are unknown. Only the observed members
// are declared.
struct ObservedReceiverB515e0 {
  std::uint32_t field_00;
  std::uint32_t field_04;
  std::uint32_t field_08;
  std::uint32_t field_0c;
  std::uint32_t field_10;
  std::uint32_t field_14;
  std::uint32_t field_18;
  std::uint32_t field_1c;
  std::uint32_t field_20;
  std::uint32_t field_24;
  std::uint32_t field_28;
  std::uint32_t field_2c;
  // 0x00b5a390 writes the byte 0 at 0x00b5a3fe and 0x00b515e0 writes the byte
  // 1 at 0x00b51638. The pair behaves as a "cached object was (re)built"
  // latch; its name is not established.
  std::uint8_t field_30_rebuilt_latch;
  std::uint8_t field_31_padding[3];
  std::uint32_t field_34;
  std::uint32_t field_38;
  std::uint32_t field_3c;
  // 0x00b5a2e3 / 0x00b5a2e7 read this vector's begin/end pair and walk it
  // element by element.
  std::uint32_t field_60_vector_begin;
  std::uint32_t field_64_vector_end;
};

// The sub-object the cached object points at from its own +0x1c. Only two
// members of it are read by 0x00b515e0, and both are compared for identity.
// The intervening members are declared as padding because the binary never
// touches them from this function; no layout beyond the two proven offsets is
// claimed.
struct ObservedCachedSubobjectB515e0 {
  std::uint32_t padding_00_to_30[13];  // 0x00..0x30, never read here
  // Must equal the pointer returned by the cGameInputManager accessor.
  std::uint32_t field_34_recorded_manager;
  std::uint32_t padding_38;  // 0x38, never read here
  // Must equal [+0x08] of the result of the slot +0x0c virtual call.
  std::uint32_t field_3c_recorded_subid;
};

struct ObservedCachedObjectB515e0 {
  std::uint32_t padding_00_to_18[6];  // 0x00..0x18
  ObservedCachedSubobjectB515e0* field_1c_subobject;
};

// The singleton accessor 0x00b3d310, whose whole body is
//   0x00b3d310  a1 e8 ea 67 01   mov eax, dword ptr [0x0167eae8]
//   0x00b3d315  c3               ret
// Every one of the nine observed callers feeds its result straight into ECX
// before calling the port, so the receiver is always that singleton pointer.
std::uint32_t* port_00b3d310_singletonReceiver();

// 0x00b3d350, named Simulator::cGameInputManager::Get by the Spore-ModAPI
// import. Whole body:
//   0x00b3d350  a1 f8 ea 67 01   mov eax, dword ptr [0x0167eaf8]
//   0x00b3d355  c3               ret
std::uint32_t* port_00b3d350_gameInputManagerGet();

// The virtual at vtable slot +0x0c of [cGameInputManager + 0x24]. Entered with
// ECX equal to that sub-object and no stack argument; returns a pointer whose
// [+0x08] is compared. Concrete callee NOT resolved: the sub-object is only
// reachable through a runtime pointer, so no vtable address is observable from
// the static image.
std::uint32_t* port_virtualSlot0C_of_gameInputManagerSubobject(
    std::uint32_t* sub);

// 0x00b512f0 - the lazy builder. Reads global 0x0167ecd0, reads and writes
// global 0x0167ecd4, and returns immediately if the guard is null, if the
// cached object already exists, or if the input manager is null. Declared an
// opaque port: its 91-instruction body allocates through a runtime allocator
// vtable and is not reconstructed here.
void port_00b512f0_ensureCachedObjectBuilt();

// 0x00b4f7f0 - the release port. Reads global 0x0167ecd4 and leaves it null on
// every path (0x00b4f81f). Opaque port, same reason.
void port_00b4f7f0_releaseCachedObject();

// Observed body of 0x00b515e0: 32 instructions, 0x00b515e0..0x00b5163d.
//
// __thiscall by observed use: all nine callers load the receiver into ECX
// immediately before the call and none pushes a stack argument. The return
// value is discarded at every inspected site.
extern "C" void SimCachedObjectValidate_00b515e0(ObservedReceiverB515e0* self);

}  // namespace openspore::reconstruction::wave13_w1_core_b16
