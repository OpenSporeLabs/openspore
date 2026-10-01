#pragma once

// Reconstruction of 0x00980510 -- UTFWin::PerspectiveEffect::GetProxyID
// Binary: SPORE/SporeBin/SporeApp.exe 3.1.0.22
//   sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// Original body, 6 bytes, 2 instructions, exhaustive:
//   0x00980510  MOV EAX,0x202
//   0x00980515  RET
//
// The body reads no memory, no register other than EAX as an output, and
// terminates in a bare RET. It is a vtable slot implementation: the target's
// only reference in the whole program is the DATA word at 0x014440e4, which is
// slot +0x14 of the vtable based at 0x014440d0.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin PerspectiveEffect GetProxyID (0x00980510) requires x86-32"
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

namespace openspore::reconstruction::pkg_utfwin_perspective_proxyid_00980510 {

using OpaqueWord = std::uint32_t;

#if defined(_MSC_VER)
#define PKG_PP_THISCALL __thiscall
#else
#define PKG_PP_THISCALL __attribute__((thiscall))
#endif

// The receiver is left opaque on purpose: this body addresses no field of it.
// The vtable pointer at +0x00 is declared only because the target's sole
// reference is the vtable slot that holds this body.
struct PerspectiveEffect;

using ProxyIdSlot = OpaqueWord(PKG_PP_THISCALL*)(PerspectiveEffect*);

// Vtable image at 0x014440d0, slots +0x00..+0x5c, read live from the binary.
// The base is delimited from below: the word at 0x014440cc is 0x00000000.
// Whether the image continues past +0x5c is not established here.
struct alignas(4) PerspectiveEffectVTable {
  OpaqueWord slot_00 = 0;  // 0x00980320 -- Ghidra thunk_FUN_0083f5d0, JMP 0x0083f5d0
  OpaqueWord slot_04 = 0;  // 0x009800e0 -- Ghidra FUN_009800e0, 4-byte body
  OpaqueWord slot_08 = 0;  // 0x00980490 -- Ghidra FUN_00980490
  OpaqueWord slot_0c = 0;  // 0x009804e0 -- UTFWin::PerspectiveEffect::func80h
  OpaqueWord slot_10 = 0;  // 0x00e31100
  OpaqueWord slot_14 = 0;  // 0x00980510 -- GetProxyID, this body
  OpaqueWord slot_18 = 0;  // 0x00980520 -- no function record in Ghidra
  OpaqueWord slot_1c = 0;  // 0x006f2f20 -- Ghidra FUN_006f2f20, shared default
  OpaqueWord slot_20 = 0;  // 0x006f2f20
  OpaqueWord slot_24 = 0;  // 0x006f2f20
  OpaqueWord slot_28 = 0;  // 0x006f2f20
  OpaqueWord slot_2c = 0;  // 0x00951230 -- shared UTFWin slot, PKG-UTFWIN-CORE-WAVE6
  OpaqueWord slot_30 = 0;  // 0x00951220 -- shared UTFWin slot, PKG-UTFWIN-CORE-WAVE6
  OpaqueWord slot_34 = 0;  // 0x00951220
  OpaqueWord slot_38 = 0;  // 0x006f2f20
  OpaqueWord slot_3c = 0;  // 0x00951220
  OpaqueWord slot_40 = 0;  // 0x00951230
  OpaqueWord slot_44 = 0;  // 0x00951230
  OpaqueWord slot_48 = 0;  // 0x00dde980
  OpaqueWord slot_4c = 0;  // 0x006f2f20
  OpaqueWord slot_50 = 0;  // 0x00dde980
  OpaqueWord slot_54 = 0;  // 0x00dde980
  OpaqueWord slot_58 = 0;  // 0x00b267f0
  OpaqueWord slot_5c = 0;  // 0x00b267f0
};

// The same 24 words as a flat image, so a test can assert the recorded slot
// values without depending on struct layout.
inline constexpr OpaqueWord kPerspectiveEffectVTableImage[] = {
    0x00980320u, 0x009800e0u, 0x00980490u, 0x009804e0u, 0x00e31100u,
    0x00980510u, 0x00980520u, 0x006f2f20u, 0x006f2f20u, 0x006f2f20u,
    0x006f2f20u, 0x00951230u, 0x00951220u, 0x00951220u, 0x006f2f20u,
    0x00951220u, 0x00951230u, 0x00951230u, 0x00dde980u, 0x006f2f20u,
    0x00dde980u, 0x00dde980u, 0x00b267f0u, 0x00b267f0u,
};

inline constexpr std::size_t kPerspectiveEffectVTableSlotCount = 24;
inline constexpr std::size_t kPerspectiveEffectVTableExtentBytes = 0x60;
inline constexpr OpaqueWord kPerspectiveEffectVTableBase = 0x014440d0u;
inline constexpr OpaqueWord kPerspectiveEffectVTablePredecessorTerminator =
    0x00000000u;  // word at 0x014440cc

// Slot +0x14 is index 5 and holds this body. The offset is fixed by the
// target's single reference at 0x014440e4 = 0x014440d0 + 0x14.
inline constexpr std::size_t kGetProxyIdSlotIndex = 5;
inline constexpr std::size_t kGetProxyIdSlotOffset = 0x14;
inline constexpr OpaqueWord kGetProxyIdVa = 0x00980510u;
// The only reference to the target in the whole program: one DATA word, this
// address, holding the target's VA.
inline constexpr OpaqueWord kGetProxyIdReferenceWord = 0x014440e4u;

// The one immediate the body materialises: MOV EAX,0x202 at 0x00980510.
inline constexpr OpaqueWord kPerspectiveEffectProxyId = 0x202u;

static_assert(sizeof(void*) == 4,
              "UTFWin PerspectiveEffect vtable pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "opaque words are 32-bit");
static_assert(offsetof(PerspectiveEffectVTable, slot_14) == kGetProxyIdSlotOffset,
              "GetProxyID occupies vtable slot +0x14");
static_assert(offsetof(PerspectiveEffectVTable, slot_5c) == 0x5c,
              "last recorded slot offset");
static_assert(sizeof(PerspectiveEffectVTable) == kPerspectiveEffectVTableExtentBytes,
              "recorded vtable image extent");
static_assert(sizeof(kPerspectiveEffectVTableImage) / sizeof(OpaqueWord) ==
                  kPerspectiveEffectVTableSlotCount,
              "flat image and slot count agree");
static_assert(kGetProxyIdSlotIndex * 4 == kGetProxyIdSlotOffset,
              "slot index and slot offset agree");
static_assert(kGetProxyIdVa == kPerspectiveEffectVTableImage[kGetProxyIdSlotIndex],
              "recorded slot +0x14 is the target VA");
static_assert(kPerspectiveEffectVTableBase + kGetProxyIdSlotOffset ==
                  kGetProxyIdReferenceWord,
              "the reference word is the vtable base plus slot +0x14");
static_assert(0x202u == 514u, "proxy id literal is 0x202");

extern "C" OpaqueWord PKG_PP_THISCALL get_proxy_id_00980510(
    PerspectiveEffect* self);

}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
