#pragma once

// Reconstruction of Terrain::cTerrainSphere::GetSimDataRTT @ 0x00f968b0
// (SporeApp.exe 3.1.0.22, sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Every constant in this header is read out of the 0x50 byte body
// 0x00f968b0..0x00f968ff. Nothing here is inferred from a name: the SDK carries
// no declaration for cTerrainSphere, so the layout below is the machine's, not
// the header's.

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-terrain-getsimdatartt-00f968b0 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_GSDR_THISCALL __thiscall
#else
#define PKG_GSDR_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0 {

// Selector ids pushed as the single stack argument of the callee.
//   0x00f968c9  PUSH 0x8   -> first query
//   0x00f968e3  PUSH 0x7   -> second query
inline constexpr std::uint32_t kSelectorIdFirst = 0x8u;
inline constexpr std::uint32_t kSelectorIdSecond = 0x7u;

// Byte offset of the dispatched slot inside the callee's vtable.
//   0x00f968c6  MOV EDX,dword ptr [EAX + 0x58]   (reloaded verbatim at 0x00f968e0)
inline constexpr std::uint32_t kSelectorSlotOffset = 0x58u;
inline constexpr std::uint32_t kSelectorSlotIndex = 0x58u / 4u;  // 22

// Offset of the anchor field inside the receiver, relative to ECX.
//   0x00f968b2  MOV ESI,ECX            -> ESI = receiver
//   0x00f968b9  LEA EDI,[ESI + 0x4]    -> EDI = &receiver->anchor
//   0x00f968d7  ADD ESI,0x4            -> ESI = &receiver->anchor (second compare)
inline constexpr std::uint32_t kAnchorFieldOffset = 0x04u;

// The value the body returns on success. MOV EAX,0x1 at 0x00f968ef; every
// other path leaves EAX zeroed by XOR EAX,EAX at 0x00f968fa.
inline constexpr std::uint32_t kReturnTrue = 0x1u;
inline constexpr std::uint32_t kReturnFalse = 0x0u;

struct alignas(4) OpaqueRttData;
struct alignas(4) OpaqueSelectorProvider;

// The object the body dispatches on. Only two facts are observable: the vtable
// pointer at +0x00 (MOV EAX,[EBX] at 0x00f968c4 and 0x00f968de) and the slot at
// +0x58. Everything past the vtable pointer is untouched by this target.
struct alignas(4) OpaqueSelectorProviderVTable {
  // Slots +0x00 .. +0x54: 22 entries, never read by this target.
  std::array<void*, 22> slots_00{};
  // Slot +0x58: the only dispatch site, taken twice.
  void* (PKG_GSDR_THISCALL* select_58)(OpaqueSelectorProvider*,
                                       std::uint32_t selector_id) = nullptr;
};

struct alignas(4) OpaqueSelectorProvider {
  OpaqueSelectorProviderVTable* vtable = nullptr;
  std::array<std::uint8_t, 8> opaque_04{};
};

// The anchored sub-object. The body only ever takes its ADDRESS, so its extent
// is not observable here; four bytes is the smallest honest blob and no code in
// this package depends on it being right.
struct alignas(4) OpaqueRttData {
  std::array<std::uint8_t, 4> bytes_00{};
};

// Receiver layout. Only +0x04 is read by 0x00f968b0. The four named pointers are
// NOT observed here: they come from the sibling virtual 0x00f96870, which sits in
// the same vtable (0x01490be8 slot 13 and slot 38) and compares the word at
// +0xFC against &this+0x30, &this+0x74 and &this+0xB8. They are recorded so the
// anchor's own address is exact and so the class is not modelled as a bare
// two-word struct.
struct alignas(4) OpaqueTerrainSphere {
  std::array<std::uint8_t, 0x04> opaque_00{};              // +0x00
  OpaqueRttData anchor_04;                                 // +0x04  <- the anchor
  std::array<std::uint8_t, 0x28> opaque_08{};              // +0x08 .. +0x2f
  OpaqueRttData* sibling_30 = nullptr;                     // +0x30
  std::array<std::uint8_t, 0x40> opaque_34{};              // +0x34 .. +0x73
  OpaqueRttData* sibling_74 = nullptr;                     // +0x74
  std::array<std::uint8_t, 0x40> opaque_78{};              // +0x78 .. +0xb7
  OpaqueRttData* sibling_b8 = nullptr;                     // +0xb8
  std::array<std::uint8_t, 0x40> opaque_bc{};              // +0xbc .. +0xfb
  OpaqueRttData* sibling_fc = nullptr;                     // +0xfc
};

// The one ordinary stack argument is read at [ESP + 0x10] AFTER the three
// prologue pushes (MOV EBX,dword ptr [ESP + 0x10] at 0x00f968c0), i.e. at
// [entry_esp + 4]; the body then callee-cleans it (RET 0x4 at 0x00f968f5 and
// 0x00f968fd). So: one hidden receiver in ECX, one stack pointer argument,
// stack cleanup owned by the callee.
extern "C" bool PKG_GSDR_THISCALL get_sim_data_rtt_00f968b0(
    OpaqueTerrainSphere* self, OpaqueSelectorProvider* provider);

}  // namespace openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0

static_assert(sizeof(void*) == 4,
              "pkg-terrain-getsimdatartt-00f968b0 requires 32-bit pointers");
static_assert(offsetof(
                  openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::
                      OpaqueSelectorProviderVTable,
                  select_58) == 0x58,
              "the only dispatch site of 0x00f968b0 is the +0x58 slot");
static_assert(sizeof(openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::
                         OpaqueSelectorProviderVTable) == 0x5c,
              "22 preceding slots plus the +0x58 slot");
static_assert(offsetof(openspore::reconstruction::
                           pkg_terrain_getsimdatartt_00f968b0::OpaqueTerrainSphere,
                       anchor_04) == 0x04,
              "the anchor is the field at receiver + 0x04");
static_assert(offsetof(openspore::reconstruction::
                           pkg_terrain_getsimdatartt_00f968b0::OpaqueTerrainSphere,
                       sibling_30) == 0x30,
              "sibling anchor observed in 0x00f96870");
static_assert(offsetof(openspore::reconstruction::
                           pkg_terrain_getsimdatartt_00f968b0::OpaqueTerrainSphere,
                       sibling_74) == 0x74,
              "sibling anchor observed in 0x00f96870");
static_assert(offsetof(openspore::reconstruction::
                           pkg_terrain_getsimdatartt_00f968b0::OpaqueTerrainSphere,
                       sibling_b8) == 0xb8,
              "sibling anchor observed in 0x00f96870");
static_assert(offsetof(openspore::reconstruction::
                           pkg_terrain_getsimdatartt_00f968b0::OpaqueTerrainSphere,
                       sibling_fc) == 0xfc,
              "the compared word of 0x00f96870");
static_assert(sizeof(openspore::reconstruction::
                         pkg_terrain_getsimdatartt_00f968b0::OpaqueTerrainSphere) ==
                  0x100,
              "receiver extent implied by the sibling virtual's +0xfc read");
