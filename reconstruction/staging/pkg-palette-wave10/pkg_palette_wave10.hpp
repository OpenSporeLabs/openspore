#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-PALETTE-WAVE10 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4,
              "PKG-PALETTE-WAVE10 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "PKG-PALETTE-WAVE10 target words are 32-bit");
static_assert(sizeof(std::uint16_t) == 2,
              "PKG-PALETTE-WAVE10 target text units are 16-bit");

#if defined(_MSC_VER)
#define PKG_PALETTE_W10_THISCALL __thiscall
#define PKG_PALETTE_W10_STDCALL __stdcall
#define PKG_PALETTE_W10_CDECL __cdecl
#else
#define PKG_PALETTE_W10_THISCALL __attribute__((thiscall))
#define PKG_PALETTE_W10_STDCALL __attribute__((stdcall))
#define PKG_PALETTE_W10_CDECL __attribute__((cdecl))
#endif

struct OpaqueResourceKey {
  std::uint32_t word00;
  std::uint32_t word04;
  std::uint32_t word08;
};

struct OpaqueTextBuffer {
  const std::uint16_t* begin;
  std::uint16_t* cursor;
  std::uint16_t* end;
};

struct OpaqueRectF {
  float field00;
  float field04;
  float field08;
  float field0c;
};

struct OpaqueProperty {
  std::uint8_t opaque00[0x12];
  std::uint16_t field12;
  std::uint8_t opaque14[0x0c];
};

struct OpaquePropertyList {
  void* vtable;
};

struct OpaquePropertyManager {
  void* vtable;
};

struct OpaqueLocalizedText {
  std::uint8_t opaque[0x10];
};

struct OpaqueElement {
  void* vtable;
};

struct OpaquePageCategory {
  std::uint8_t opaque00[0x88];
  OpaqueElement** field88;
  OpaqueElement** field8c;
  std::uint8_t opaque90[0x10];
  std::int32_t fielda0;
};

struct OpaquePageText {
  void* vtable;
};

struct OpaquePageNav {
  void* vtable;
};

struct OpaquePage {
  void* vtable00;
  std::uint8_t opaque04[0x10];
  OpaquePageCategory* field14;
  OpaquePageText* field18;
  OpaquePageNav* field1c;
  std::int32_t field20;
  std::int32_t field24;
  std::uint8_t opaque28[0x78];
};

struct OpaqueEntry {
  void* vtable00;
  void* vtable08;
  std::uint8_t opaque10[0x40];
  std::uint32_t field48;
  std::uint32_t field4c;
  std::uint8_t field50;
  std::uint8_t opaque51[3];
  std::uint32_t field54;
  std::uint32_t field58;
  OpaqueLocalizedText field5c;
  void* field6c;
  std::uint8_t field70;
  std::uint8_t opaque71[3];
  std::uint32_t field74;
  std::uint32_t field78;
  OpaqueResourceKey field7c;
  std::uint32_t field88;
  std::uint8_t opaque8c[4];
};

struct OpaquePaletteGroup {
  std::uint8_t opaque00[0x0c];
  OpaqueElement** field0c;
  OpaqueElement** field10;
  std::uint8_t opaque14[0x5c];
  std::uint8_t field70;
  std::uint8_t opaque71[0x0f];
};

struct OpaqueAppProps {
  std::uint8_t opaque00[0x3c];
  void* field3c;
  std::uint8_t opaque40[0xd8];
  std::uint32_t field118;
};

struct OpaqueApp {
  void* vtable;
  std::uint8_t opaque04[0x38];
  OpaqueAppProps* field3c;
};

struct OpaquePalette {
  void* vtable00;
  std::uint8_t opaque04[0x0c];
  void* field10;
  std::uint8_t opaque14[0x08];
  OpaqueElement* field1c;
  OpaqueElement* field20;
  OpaqueElement* field24;
  OpaqueElement* field28;
  OpaqueElement* field2c;
  std::uint8_t opaque30[0x3c];
  OpaquePaletteGroup* field6c;
  std::uint8_t opaque70[0x04];
  OpaqueElement** field74;
  OpaqueElement** field78;
  std::uint8_t opaque7c[0x0c];
  OpaquePageCategory** field88;
  OpaquePageCategory** field8c;
  std::uint8_t opaque90[0x10];
  std::int32_t fielda0;
  std::uint8_t opaquea4[0x04];
  std::int32_t fielda8;
  std::uint32_t fieldac;
  std::int32_t fieldb0;
};

struct OpaqueToggle {
  std::uint8_t opaque[0x18];
};

static_assert(sizeof(OpaqueResourceKey) == 0x0c, "resource key size");
static_assert(offsetof(OpaqueResourceKey, word04) == 0x04,
              "resource key second word offset");
static_assert(offsetof(OpaqueResourceKey, word08) == 0x08,
              "resource key third word offset");
static_assert(sizeof(OpaqueTextBuffer) == 0x0c, "text buffer size");
static_assert(sizeof(OpaqueRectF) == 0x10, "float rect size");
static_assert(offsetof(OpaqueProperty, field12) == 0x12, "property tag offset");
static_assert(sizeof(OpaqueProperty) == 0x20, "property size");
static_assert(offsetof(OpaquePageCategory, field88) == 0x88,
              "category array begin offset");
static_assert(offsetof(OpaquePageCategory, field8c) == 0x8c,
              "category array end offset");
static_assert(offsetof(OpaquePageCategory, fielda0) == 0xa0,
              "category current index offset");
static_assert(offsetof(OpaquePage, field14) == 0x14, "page category offset");
static_assert(offsetof(OpaquePage, field18) == 0x18, "page text offset");
static_assert(offsetof(OpaquePage, field1c) == 0x1c, "page nav offset");
static_assert(offsetof(OpaquePage, field20) == 0x20,
              "page cached index offset");
static_assert(offsetof(OpaquePage, field24) == 0x24,
              "page cached count offset");
static_assert(offsetof(OpaqueEntry, field48) == 0x48, "entry id offset");
static_assert(offsetof(OpaqueEntry, field4c) == 0x4c, "entry id wide offset");
static_assert(offsetof(OpaqueEntry, field50) == 0x50, "entry flag offset");
static_assert(offsetof(OpaqueEntry, field54) == 0x54, "entry key a offset");
static_assert(offsetof(OpaqueEntry, field58) == 0x58, "entry key b offset");
static_assert(offsetof(OpaqueEntry, field5c) == 0x5c, "entry text offset");
static_assert(offsetof(OpaqueEntry, field6c) == 0x6c, "entry group offset");
static_assert(offsetof(OpaqueEntry, field70) == 0x70, "entry flag wide offset");
static_assert(offsetof(OpaqueEntry, field74) == 0x74, "entry group key offset");
static_assert(offsetof(OpaqueEntry, field78) == 0x78,
              "entry group count offset");
static_assert(offsetof(OpaqueEntry, field7c) == 0x7c, "entry array key offset");
static_assert(offsetof(OpaqueEntry, field88) == 0x88,
              "entry array key 2 offset");
static_assert(sizeof(OpaqueEntry) == 0x90, "entry size");
static_assert(offsetof(OpaquePaletteGroup, field0c) == 0x0c,
              "palette group begin offset");
static_assert(offsetof(OpaquePaletteGroup, field10) == 0x10,
              "palette group end offset");
static_assert(offsetof(OpaquePaletteGroup, field70) == 0x70,
              "palette group flag offset");
static_assert(offsetof(OpaquePalette, field1c) == 0x1c, "palette host offset");
static_assert(offsetof(OpaquePalette, field20) == 0x20, "palette lead offset");
static_assert(offsetof(OpaquePalette, field24) == 0x24, "palette title offset");
static_assert(offsetof(OpaquePalette, field28) == 0x28, "palette body offset");
static_assert(offsetof(OpaquePalette, field2c) == 0x2c, "palette tail offset");
static_assert(offsetof(OpaquePalette, field6c) == 0x6c, "palette group offset");
static_assert(offsetof(OpaquePalette, field74) == 0x74, "palette pages offset");
static_assert(offsetof(OpaquePalette, field78) == 0x78,
              "palette pages end offset");
static_assert(offsetof(OpaquePalette, field88) == 0x88,
              "palette categories offset");
static_assert(offsetof(OpaquePalette, field8c) == 0x8c,
              "palette categories end offset");
static_assert(offsetof(OpaquePalette, fielda0) == 0xa0,
              "palette category index offset");
static_assert(offsetof(OpaquePalette, fielda8) == 0xa8,
              "palette row index offset");
static_assert(offsetof(OpaquePalette, fieldac) == 0xac,
              "palette selection offset");
static_assert(offsetof(OpaquePalette, fieldb0) == 0xb0,
              "palette row width offset");
static_assert(offsetof(OpaqueAppProps, field118) == 0x118, "app props offset");
static_assert(offsetof(OpaqueApp, field3c) == 0x3c, "app props slot offset");

namespace openspore::reconstruction::pkg_palette_wave10 {

using PropertyListSlot04 = void (*)(OpaquePropertyList*);
using PropertyListSlot24 = bool (*)(OpaquePropertyList*, std::uint32_t,
                                    OpaqueProperty**);
using PropertyListSlot2c = OpaquePropertyList* (*)(OpaquePropertyList*,
                                                   std::uint32_t, std::uint32_t,
                                                   OpaquePropertyList**);
using PageNavSlot7c = void (*)(OpaquePageNav*, std::uint32_t, std::uint32_t);
using PageTextSlot80 = void (*)(OpaquePageText*, const std::uint16_t*);
using ElementSlot28 = void (*)(OpaqueElement*, std::uint32_t, std::uint32_t);
using ElementSlot38 = const float* (*)(OpaqueElement*);
using ElementSlot6c = void (*)(OpaqueElement*, const OpaqueRectF*);

extern "C" {

void PKG_PALETTE_W10_THISCALL pkg_palette_w10_005c0a60(OpaquePage*,
                                                       std::uint32_t);
bool PKG_PALETTE_W10_THISCALL pkg_palette_w10_005c1e20(OpaqueEntry*,
                                                       const OpaqueResourceKey*,
                                                       std::uint32_t);
void PKG_PALETTE_W10_THISCALL pkg_palette_w10_005c3000(OpaquePalette*);
void PKG_PALETTE_W10_THISCALL pkg_palette_w10_005c3cb0(OpaquePalette*,
                                                       std::uint32_t);

bool PKG_PALETTE_W10_THISCALL unresolved_005c29c0(OpaquePageCategory*,
                                                  std::uint32_t);
OpaqueTextBuffer* PKG_PALETTE_W10_CDECL unresolved_0041e050(
    OpaqueTextBuffer*, const std::uint16_t*, std::int32_t, std::int32_t);
void PKG_PALETTE_W10_CDECL unresolved_00f47380(void*);

OpaquePropertyList* PKG_PALETTE_W10_CDECL unresolved_0067de30();
const std::uint8_t* PKG_PALETTE_W10_THISCALL
unresolved_0041e920(OpaqueProperty*);
const std::uint32_t* PKG_PALETTE_W10_THISCALL
unresolved_0041ea00(OpaqueProperty*);
void PKG_PALETTE_W10_CDECL unresolved_006a12a0(OpaquePropertyList*,
                                               std::uint32_t, std::uint32_t*);
void PKG_PALETTE_W10_CDECL unresolved_006a1250(OpaquePropertyList*,
                                               std::uint32_t,
                                               OpaqueResourceKey*);
void PKG_PALETTE_W10_CDECL unresolved_006a0ae0(OpaquePropertyList*,
                                               std::uint32_t, std::uint32_t*,
                                               OpaqueResourceKey*);
void PKG_PALETTE_W10_CDECL unresolved_006a1360(OpaquePropertyList*,
                                               std::uint32_t,
                                               OpaqueLocalizedText*);

OpaqueToggle* PKG_PALETTE_W10_THISCALL unresolved_008105b0(std::uint32_t,
                                                           std::uint32_t);
int PKG_PALETTE_W10_THISCALL unresolved_005c2aa0(OpaquePalette*);
int PKG_PALETTE_W10_STDCALL unresolved_005c2a30(std::uint32_t);
void PKG_PALETTE_W10_THISCALL unresolved_005c2590(OpaquePalette*, std::int32_t);
void PKG_PALETTE_W10_CDECL unresolved_004a88d0(std::uint32_t);
OpaquePageCategory* PKG_PALETTE_W10_THISCALL unresolved_005c2e50(OpaquePalette*,
                                                                 std::int32_t);
std::uint32_t PKG_PALETTE_W10_THISCALL unresolved_005c8fc0(OpaquePageCategory*);
int PKG_PALETTE_W10_THISCALL unresolved_005c29e0(OpaquePalette*, std::uint32_t);
bool PKG_PALETTE_W10_THISCALL unresolved_005c3bd0(OpaquePalette*, std::int32_t);

extern const std::uint16_t* g_text_013f7c30;
extern std::uint16_t g_text_01667bac[1];
extern OpaqueTextBuffer g_text_01667bac_buffer;
extern std::uint32_t g_word_01514dd0;
extern float g_float_01486110;
extern OpaqueApp* g_dword_015fd918;
}

}
