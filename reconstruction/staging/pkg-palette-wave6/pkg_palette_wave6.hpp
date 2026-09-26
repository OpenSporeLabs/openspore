#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-PALETTE-WAVE6 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4,
              "PKG-PALETTE-WAVE6 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "PKG-PALETTE-WAVE6 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG_PALETTE_THISCALL __thiscall
#define PKG_PALETTE_STDCALL __stdcall
#define PKG_PALETTE_CDECL __cdecl
#else
#define PKG_PALETTE_THISCALL __attribute__((thiscall))
#define PKG_PALETTE_STDCALL __attribute__((stdcall))
#define PKG_PALETTE_CDECL __attribute__((cdecl))
#endif

struct OpaqueResourceKey {
  std::uint32_t word0;
  std::uint32_t word1;
  std::uint32_t word2;
};

struct OpaqueViewerObject {
  std::uint8_t opaque[0x18];
};

struct OpaqueViewerItem {
  void* vtable;
  std::uint32_t field04;
  OpaqueViewerObject* field08;
  std::uint32_t field0c;
  std::uint32_t field10;
  OpaqueViewerObject* field14;
  std::uint8_t opaque18[0x14];
  std::uint32_t field2c;
  std::uint8_t field30;
  std::uint8_t field31;
  std::uint8_t field32;
  std::uint8_t field33;
};

struct OpaqueAdvancedItemViewer {
  void* vtable;
  std::uint8_t opaque04[0x3c];
  OpaqueViewerObject* field40;
  std::uint8_t opaque44[0x40];
  float field84;
  float field88;
  std::uint8_t opaque8c[8];
  float field94;
  std::uint8_t opaque98[0x68];
  std::uint32_t field100;
  std::uint8_t opaque104[0x65];
  std::uint8_t field169;
  std::uint8_t field16a;
  std::uint8_t field16b;
  std::uint8_t opaque16c[0x10];
  OpaqueViewerItem* field17c;
  OpaqueViewerObject* field180;
  std::uint8_t field184;
  std::uint8_t opaque185[3];
  float field188;
  std::uint8_t opaque18c[8];
  void* field194;
  std::uint8_t field198;
  std::uint8_t opaque199[0x2f];
};

struct OpaquePaletteMain {
  std::uint8_t opaque[0x40];
};

struct OpaquePalettePage {
  std::uint8_t opaque[0x84];
};

struct OpaqueCommandLine {
  std::uint32_t field00;
  std::uint32_t field04;
  std::uint32_t field08;
  std::uint32_t field0c;
};

struct OpaqueRect {
  float field00;
  float field04;
  float field08;
  float field0c;
};

struct OpaqueSwatchManager;
struct OpaqueSwatchState;
struct OpaqueGraphicsRoot;
struct OpaqueGraphicsContext;
struct OpaqueRenderTarget;
struct OpaqueAppSystem;

static_assert(offsetof(OpaqueViewerObject, opaque) == 0,
              "opaque viewer object vtable offset");
static_assert(sizeof(OpaqueViewerObject) == 0x18, "opaque viewer object size");
static_assert(offsetof(OpaqueViewerItem, vtable) == 0x00,
              "viewer item vtable offset");
static_assert(offsetof(OpaqueViewerItem, field08) == 0x08,
              "viewer item callback offset");
static_assert(offsetof(OpaqueViewerItem, field14) == 0x14,
              "viewer item producer offset");
static_assert(offsetof(OpaqueViewerItem, field2c) == 0x2c,
              "viewer item key offset");
static_assert(offsetof(OpaqueViewerItem, field31) == 0x31,
              "viewer item flag offset");
static_assert(sizeof(OpaqueViewerItem) == 0x34, "viewer item size");
static_assert(offsetof(OpaqueAdvancedItemViewer, field84) == 0x84,
              "viewer first layout offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field88) == 0x88,
              "viewer second layout offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field94) == 0x94,
              "viewer scaled field offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field100) == 0x100,
              "viewer state value offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field169) == 0x169,
              "viewer ready field offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field16a) == 0x16a,
              "viewer item state offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field16b) == 0x16b,
              "viewer tooltip field offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field17c) == 0x17c,
              "viewer item pointer offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field180) == 0x180,
              "viewer resource object offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field184) == 0x184,
              "viewer scale guard offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field188) == 0x188,
              "viewer scale source offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field194) == 0x194,
              "viewer secondary render offset");
static_assert(offsetof(OpaqueAdvancedItemViewer, field198) == 0x198,
              "viewer item state guard offset");
static_assert(sizeof(OpaqueAdvancedItemViewer) == 0x1c8, "viewer object size");

namespace openspore::reconstruction::pkg_palette_wave6 {

using ViewerItemSlot08 =
    std::uint8_t(PKG_PALETTE_THISCALL*)(OpaqueViewerObject*, void*);
using ViewerObjectSlot04 = void(PKG_PALETTE_THISCALL*)(OpaqueViewerObject*);
using ViewerObjectSlot08 = void(PKG_PALETTE_THISCALL*)(OpaqueViewerObject*);
using ViewerObjectSlot28 = void(PKG_PALETTE_THISCALL*)(OpaqueViewerObject*,
                                                       OpaqueViewerObject*,
                                                       void*,
                                                       OpaqueViewerItem*);
using ViewerSlot34 =
    OpaqueRenderTarget*(PKG_PALETTE_THISCALL*)(OpaqueAdvancedItemViewer*,
                                               std::uint32_t, std::uint32_t);
using GraphicsSlot04 =
    OpaqueGraphicsContext*(PKG_PALETTE_THISCALL*)(OpaqueGraphicsRoot*);
using GraphicsSlot34 =
    OpaqueRect*(PKG_PALETTE_THISCALL*)(OpaqueGraphicsContext*);
using AppSlot14 = void(PKG_PALETTE_THISCALL*)(OpaqueAppSystem*, std::uint32_t,
                                              OpaqueCommandLine*,
                                              std::uint32_t);

extern "C" {

OpaquePaletteMain* PKG_PALETTE_THISCALL pkg_palette_005c5ee0(OpaquePaletteMain*,
                                                             std::uint32_t);
OpaquePalettePage* PKG_PALETTE_THISCALL pkg_palette_005c8bc0(OpaquePalettePage*,
                                                             std::uint32_t);
void PKG_PALETTE_THISCALL pkg_palette_005f4750(OpaqueAdvancedItemViewer*);

void PKG_PALETTE_THISCALL unresolved_005c5e90(OpaquePaletteMain*);
void PKG_PALETTE_CDECL unresolved_00f47380(OpaquePaletteMain*);

OpaqueSwatchManager* PKG_PALETTE_CDECL unresolved_00401020();
OpaqueSwatchState* PKG_PALETTE_THISCALL
unresolved_0113ae10(OpaqueSwatchManager*);

OpaqueViewerObject* PKG_PALETTE_CDECL
unresolved_00f473a0(std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
                    std::uint32_t, std::uint32_t);

OpaqueViewerObject* PKG_PALETTE_THISCALL unresolved_0059f030(
    OpaqueViewerObject*, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);

void PKG_PALETTE_THISCALL unresolved_005ed320(OpaqueSwatchManager*,
                                              std::uint32_t);
void PKG_PALETTE_THISCALL unresolved_005ee480(OpaqueSwatchManager*,
                                              OpaqueViewerObject*,
                                              OpaqueViewerItem*,
                                              OpaqueViewerObject*,
                                              std::uint32_t);
OpaqueGraphicsRoot* PKG_PALETTE_CDECL unresolved_0067caa0();
OpaqueRenderTarget* PKG_PALETTE_CDECL unresolved_0067cad0(OpaqueRenderTarget*);
extern float g_palette_width_multiplier;
extern float g_palette_height_multiplier;
void PKG_PALETTE_STDCALL unresolved_0080d710(OpaqueRenderTarget*, std::uint32_t,
                                             std::uint8_t);
void PKG_PALETTE_THISCALL unresolved_008283a0(OpaqueSwatchManager*, float,
                                              float, float, float);
OpaqueAppSystem* PKG_PALETTE_CDECL unresolved_0067dcc0();
}

}
