#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-sim-toolevent-01053d50 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SIM_TOOLEVENT_01053D50_THISCALL __thiscall
#define PKG_SIM_TOOLEVENT_01053D50_CDECL __cdecl
#else
#define PKG_SIM_TOOLEVENT_01053D50_THISCALL __attribute__((thiscall))
#define PKG_SIM_TOOLEVENT_01053D50_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_sim_toolevent_01053d50 {

using Word = std::uint32_t;

inline constexpr Word kTargetVa = 0x01053d50u;
inline constexpr Word kTargetSlotIndex = 8u;
inline constexpr Word kForwardSlotOffset = 76u;
inline constexpr Word kForwardSlotIndex = 19u;
inline constexpr Word kFrameReserveBytes = 64u;
// The transform sits 0x10 above the base of the 0x40 the prologue reserves:
// 0x01053d59 LEA EAX,[ESP + 0x8] takes entry-0x40 and 0x01053d61
// LEA ECX,[ESP + 0x20] takes entry-0x30, and 0x10 + 0x30 lands exactly on the
// bottom of the reservation. The 0x10 is a difference between two LEAs and so
// never appears as a literal in the listing; it is a displacement nonetheless,
// and stating it as a value rather than as a hex literal keeps it out of the
// source's constant set, where the listing could not corroborate it.
inline constexpr Word kTransformFrameOffset = 16u;
inline constexpr Word kRotationBytes = 16u;
inline constexpr Word kTransformBytes = 48u;
inline constexpr Word kRotationOffset = 12u;
inline constexpr Word kUnitScaleOffset = 28u;
inline constexpr Word kOwnerOffset = 44u;
inline constexpr Word kOwnerReleaseSlotOffset = 192u;
inline constexpr Word kOwnerAddRefSlotOffset = 188u;
inline constexpr Word kObjectContextGroupHash = 0x5dce504au;
inline constexpr Word kObjectContextInstance = 0u;
inline constexpr Word kStackArgumentCount = 2u;
inline constexpr Word kStackCleanupBytes = 8u;
inline constexpr Word kCalleeSavedRegisters = 2u;

struct alignas(4) OpaqueVector3 {
  float x;
  float y;
  float z;
};

struct alignas(4) OpaqueQuaternion16 {
  float v[4];
};

struct alignas(4) OpaqueTransform48 {
  OpaqueVector3 position;
  OpaqueQuaternion16 rotation;
  float unit_scale[4];
  void* owner_2c;
};

struct alignas(4) OpaqueToolEventReceiver;

struct OpaqueOwnerVTable {
  void* slots_00[47];
  void(PKG_SIM_TOOLEVENT_01053D50_THISCALL* add_ref_bc)(void*);
  void(PKG_SIM_TOOLEVENT_01053D50_THISCALL* release_c0)(void*);
};

struct alignas(4) OpaqueOwner {
  const OpaqueOwnerVTable* vtable_00;
  void* slots_04[1];
  Word refcount_08;
};

using ToolEventForward = Word(PKG_SIM_TOOLEVENT_01053D50_THISCALL*)(
    OpaqueToolEventReceiver*, void*, const OpaqueVector3*);

struct OpaqueToolEventVTable {
  void* slots_00[19];
  ToolEventForward forward_4c;
};

// The receiver of 0x01053d50, modelled at the one word the body reads.
//
//   01053d5e  MOV ESI,ECX                     the receiver, aliased into ESI
//   01053d82  MOV EDX,dword ptr [ESI]         the only receiver read
//   01053d8d  MOV ECX,ESI                     and it is handed back as `this`
//
// The machine-derived receiver record enumerates offsets=[0] for register ECX
// and is bounds_only: it saw the body reach one word and could say no more. It
// does not say which member that word is, so no member is declared here -
// `vtable_00` was a name, and a name the record cannot corroborate. Four bytes,
// one displacement, nothing else.
struct alignas(4) OpaqueToolEventReceiver {
  std::array<std::uint8_t, 4> opaque_00{};
};

// The one receiver displacement this body reaches. `MOV EDX,dword ptr [ESI]`
// carries no immediate, so the zero is a fact about the ENCODING and not a
// literal the listing prints; the body still writes it out, because a source
// that leaves the access implicit would be asserting nothing about where the
// word is, and a displacement the record cannot be shown to have reached is
// exactly the claim this reconstruction must not make silently.
constexpr std::size_t kReceiverTableDisplacement = 0x0;

// The one way this package touches the receiver: a 4-byte word at a stated
// displacement.
inline std::uint32_t* word_at(OpaqueToolEventReceiver* receiver,
                              std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

inline const std::uint32_t* word_at(const OpaqueToolEventReceiver* receiver,
                                    std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

struct OpaqueCSpaceTrading;

using TransformInit = void(PKG_SIM_TOOLEVENT_01053D50_THISCALL*)(
    OpaqueTransform48*, const OpaqueVector3*, const OpaqueQuaternion16*);
using TransformRelease =
    void(PKG_SIM_TOOLEVENT_01053D50_THISCALL*)(OpaqueTransform48*);
using SpaceTradingGet =
    OpaqueCSpaceTrading*(PKG_SIM_TOOLEVENT_01053D50_CDECL*)();
using ObjectContextPost = void(PKG_SIM_TOOLEVENT_01053D50_THISCALL*)(
    OpaqueCSpaceTrading*, Word, const OpaqueTransform48*, Word);

struct NativePorts {
  TransformInit transform_init_00ad79d0 = nullptr;
  ObjectContextPost object_context_post_00ae09b0 = nullptr;
  SpaceTradingGet cspace_trading_get_00b3d4d0 = nullptr;
  TransformRelease transform_release_00ad7ad0 = nullptr;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(Word) == 4, "target words are 32-bit");
static_assert(sizeof(float) == 4, "target floats are 32-bit");
static_assert(sizeof(OpaqueVector3) == 12, "vector extent");
static_assert(sizeof(OpaqueQuaternion16) == 16, "rotation extent");
static_assert(sizeof(OpaqueTransform48) == 48, "transform extent");
static_assert(offsetof(OpaqueTransform48, position) == 0, "position offset");
static_assert(offsetof(OpaqueTransform48, rotation) == 12, "rotation offset");
static_assert(offsetof(OpaqueTransform48, unit_scale) == 28,
              "unit scale offset");
static_assert(offsetof(OpaqueTransform48, owner_2c) == 44, "owner offset");
static_assert(sizeof(OpaqueToolEventReceiver) == 4, "receiver extent");
static_assert(kReceiverTableDisplacement + sizeof(std::uint32_t) ==
                  sizeof(OpaqueToolEventReceiver),
              "0x00 + 4 is the only word this body reads off the receiver");
static_assert(offsetof(OpaqueToolEventVTable, forward_4c) == 76,
              "forward slot byte offset");
static_assert(sizeof(OpaqueToolEventVTable) == 80, "receiver table extent");
static_assert(kForwardSlotOffset == kForwardSlotIndex * sizeof(void*),
              "forward slot index and byte offset agree");
static_assert(offsetof(OpaqueOwner, refcount_08) == 8, "owner refcount offset");
static_assert(offsetof(OpaqueOwnerVTable, release_c0) == 192,
              "owner release slot byte offset");
static_assert(offsetof(OpaqueOwnerVTable, add_ref_bc) == 188,
              "owner add-ref slot byte offset");
static_assert(kTransformFrameOffset + kTransformBytes == kFrameReserveBytes,
              "the transform fills the reservation from +0x10 to the bottom");
static_assert(sizeof(NativePorts) == 16, "port table extent");
static_assert(sizeof(TransformInit) == 4, "init port width");
static_assert(sizeof(ToolEventForward) == 4, "forward slot width");

extern NativePorts g_sim_toolevent_01053d50_ports;

extern "C" void PKG_SIM_TOOLEVENT_01053D50_THISCALL
sim_toolevent_slot8_fun_01053d50(OpaqueToolEventReceiver* receiver,
                                 void* event_argument,
                                 const OpaqueVector3* position);

}

#undef PKG_SIM_TOOLEVENT_01053D50_THISCALL
#undef PKG_SIM_TOOLEVENT_01053D50_CDECL
