#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-palette-safe-wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_PALETTE_SAFE_THISCALL __thiscall
#define PKG_PALETTE_SAFE_CDECL __cdecl
#else
#define PKG_PALETTE_SAFE_THISCALL __attribute__((thiscall))
#define PKG_PALETTE_SAFE_CDECL __attribute__((cdecl))
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

namespace openspore::reconstruction::pkg_palette_safe_wave10 {

using Word = std::uint32_t;
using Real = float;
using TextUnit = std::uint16_t;

static_assert(sizeof(void*) == 4, "x86-32 pointers are four bytes");
static_assert(sizeof(Word) == 4, "target words are four bytes");
static_assert(sizeof(Real) == 4, "target row components are 32-bit floats");
static_assert(sizeof(TextUnit) == 2, "target text units are 16-bit");

struct alignas(4) OpaqueTextBuffer {
  TextUnit* begin;
  TextUnit* cursor;
  TextUnit* end;
};

static_assert(sizeof(OpaqueTextBuffer) == 12,
              "text buffer is a pointer triple");
static_assert(offsetof(OpaqueTextBuffer, cursor) == 4, "text cursor offset");
static_assert(offsetof(OpaqueTextBuffer, end) == 8, "text buffer end offset");

struct alignas(4) OpaqueRect {
  Real x;
  Real y;
  Real w;
  Real h;
};

static_assert(sizeof(OpaqueRect) == 16, "row rectangle is four floats");
static_assert(offsetof(OpaqueRect, x) == 0x00, "row rectangle first column");
static_assert(offsetof(OpaqueRect, y) == 0x04, "row rectangle second column");
static_assert(offsetof(OpaqueRect, w) == 0x08, "row rectangle third column");
static_assert(offsetof(OpaqueRect, h) == 0x0c, "row rectangle fourth column");

struct alignas(4) OpaqueCategorySlot {
  void* element;
  std::uint8_t flag_04;
  std::uint8_t opaque_05[3];
};

static_assert(sizeof(OpaqueCategorySlot) == 8,
              "category slots are eight bytes");
static_assert(offsetof(OpaqueCategorySlot, element) == 0x00,
              "category slot element offset");
static_assert(offsetof(OpaqueCategorySlot, flag_04) == 0x04,
              "category slot visibility byte offset");

struct alignas(4) OpaquePageCategory {
  std::uint8_t opaque_00_87[0x88];
  OpaqueCategorySlot* begin_88;
  OpaqueCategorySlot* end_8c;
  std::uint8_t opaque_90_9f[0x10];
  std::int32_t current_a0;
};

static_assert(sizeof(OpaquePageCategory) == 0xa4, "category observed extent");
static_assert(offsetof(OpaquePageCategory, begin_88) == 0x88,
              "category slot vector begin offset");
static_assert(offsetof(OpaquePageCategory, end_8c) == 0x8c,
              "category slot vector end offset");
static_assert(offsetof(OpaquePageCategory, current_a0) == 0xa0,
              "category current slot offset");

struct alignas(4) OpaqueElementVtable;
struct alignas(4) OpaquePageNavVtable;
struct alignas(4) OpaquePageTextVtable;

struct alignas(4) OpaqueElement {
  OpaqueElementVtable* vtable;
};

struct alignas(4) OpaqueFeatureHost {
  void* vtable;
  std::uint8_t opaque_04_17[0x14];
};

static_assert(sizeof(OpaqueFeatureHost) == 0x18,
              "feature host observed extent");

struct alignas(4) OpaqueFeature {
  void* vtable;
};

struct alignas(4) OpaquePageNav {
  OpaquePageNavVtable* vtable;
};

struct alignas(4) OpaquePageText {
  OpaquePageTextVtable* vtable;
};

struct alignas(4) OpaquePage {
  void* vtable;
  std::uint8_t opaque_04_13[0x10];
  OpaquePageCategory* category_14;
  OpaquePageText* text_18;
  OpaquePageNav* nav_1c;
  std::int32_t cached_index_20;
  std::int32_t cached_total_24;
};

static_assert(sizeof(OpaquePage) == 0x28, "page observed extent");
static_assert(offsetof(OpaquePage, category_14) == 0x14,
              "page category offset");
static_assert(offsetof(OpaquePage, text_18) == 0x18, "page text offset");
static_assert(offsetof(OpaquePage, nav_1c) == 0x1c, "page nav offset");
static_assert(offsetof(OpaquePage, cached_index_20) == 0x20,
              "page cached index offset");
static_assert(offsetof(OpaquePage, cached_total_24) == 0x24,
              "page cached total offset");

struct alignas(4) OpaquePaletteGroup {
  std::uint8_t opaque_00_0b[0x0c];
  OpaqueElement** begin_0c;
  OpaqueElement** end_10;
  std::uint8_t opaque_14_6f[0x5c];
  std::uint8_t wide_70;
  std::uint8_t opaque_71_73[3];
};

static_assert(sizeof(OpaquePaletteGroup) == 0x74, "group observed extent");
static_assert(offsetof(OpaquePaletteGroup, begin_0c) == 0x0c,
              "group page vector begin offset");
static_assert(offsetof(OpaquePaletteGroup, end_10) == 0x10,
              "group page vector end offset");
static_assert(offsetof(OpaquePaletteGroup, wide_70) == 0x70,
              "group wide flag offset");

struct alignas(4) OpaqueAppProps {
  std::uint8_t opaque_00_117[0x118];
  std::int32_t flag_118;
};

static_assert(offsetof(OpaqueAppProps, flag_118) == 0x118,
              "application stacked rows flag offset");

struct alignas(4) OpaqueApp {
  std::uint8_t opaque_00_3b[0x3c];
  OpaqueAppProps* props_3c;
};

static_assert(offsetof(OpaqueApp, props_3c) == 0x3c,
              "application property table offset");

struct alignas(4) OpaquePalette {
  void* vtable;
  std::uint8_t opaque_04_0f[0x0c];
  OpaqueFeatureHost* feature_host_10;
  std::uint8_t opaque_14_1b[0x08];
  OpaqueElement* host_1c;
  OpaqueElement* lead_20;
  OpaqueElement* title_24;
  OpaqueElement* body_28;
  OpaqueElement* tail_2c;
  std::uint8_t opaque_30_6b[0x3c];
  OpaquePaletteGroup* group_6c;
  std::uint8_t opaque_70_73[4];
  OpaqueElement** rows_begin_74;
  OpaqueElement** rows_end_78;
};

static_assert(sizeof(OpaquePalette) == 0x7c, "palette observed extent");
static_assert(offsetof(OpaquePalette, feature_host_10) == 0x10,
              "palette feature host offset");
static_assert(offsetof(OpaquePalette, host_1c) == 0x1c, "palette host offset");
static_assert(offsetof(OpaquePalette, lead_20) == 0x20, "palette lead offset");
static_assert(offsetof(OpaquePalette, title_24) == 0x24,
              "palette title offset");
static_assert(offsetof(OpaquePalette, body_28) == 0x28, "palette body offset");
static_assert(offsetof(OpaquePalette, tail_2c) == 0x2c, "palette tail offset");
static_assert(offsetof(OpaquePalette, group_6c) == 0x6c,
              "palette group offset");
static_assert(offsetof(OpaquePalette, rows_begin_74) == 0x74,
              "palette row vector begin offset");
static_assert(offsetof(OpaquePalette, rows_end_78) == 0x78,
              "palette row vector end offset");

using ElementBounds38 =
    const OpaqueRect*(PKG_PALETTE_SAFE_THISCALL*)(OpaqueElement*);
using ElementApplyRect6c = void(PKG_PALETTE_SAFE_THISCALL*)(OpaqueElement*,
                                                            const OpaqueRect*);
using PageNavMode7c = void(PKG_PALETTE_SAFE_THISCALL*)(OpaquePageNav*, Word,
                                                       Word);
using PageTextSet80 = void(PKG_PALETTE_SAFE_THISCALL*)(OpaquePageText*,
                                                       const TextUnit*);

struct alignas(4) OpaqueElementVtable {
  std::uintptr_t slots_00_37[14];
  ElementBounds38 bounds38;
  std::uintptr_t slots_3c_6b[12];
  ElementApplyRect6c apply6c;
};

struct alignas(4) OpaquePageNavVtable {
  std::uintptr_t slots_00_7b[31];
  PageNavMode7c mode7c;
};

struct alignas(4) OpaquePageTextVtable {
  std::uintptr_t slots_00_7f[32];
  PageTextSet80 set80;
};

static_assert(sizeof(decltype(OpaqueElementVtable::bounds38)) == 4,
              "element bounds slot is one pointer");
static_assert(sizeof(decltype(OpaqueElementVtable::apply6c)) == 4,
              "element rectangle slot is one pointer");
static_assert(sizeof(decltype(OpaquePageNavVtable::mode7c)) == 4,
              "page nav mode slot is one pointer");
static_assert(sizeof(decltype(OpaquePageTextVtable::set80)) == 4,
              "page text slot is one pointer");
static_assert(offsetof(OpaqueElementVtable, bounds38) == 0x38,
              "element bounds slot index");
static_assert(offsetof(OpaqueElementVtable, apply6c) == 0x6c,
              "element rectangle slot index");
static_assert(offsetof(OpaquePageNavVtable, mode7c) == 0x7c,
              "page nav mode slot index");
static_assert(offsetof(OpaquePageTextVtable, set80) == 0x80,
              "page text slot index");
static_assert(sizeof(OpaqueElementVtable) == 0x70,
              "element vtable observed span");
static_assert(sizeof(OpaquePageNavVtable) == 0x80, "nav vtable observed span");
static_assert(sizeof(OpaquePageTextVtable) == 0x84,
              "text vtable observed span");

extern const TextUnit* g_format_013f7c30;
extern TextUnit g_scratch_01667bac[2];
extern Real g_row_gap_01486110;
extern void* g_table_015fd918;

extern "C" {

void PKG_PALETTE_SAFE_THISCALL
page_visible_slots_refresh_005c0a60(OpaquePage* self, Word argument);

void PKG_PALETTE_SAFE_THISCALL palette_row_layout_005c3000(OpaquePalette* self);

bool PKG_PALETTE_SAFE_THISCALL unresolved_005c29c0(OpaquePageCategory* self,
                                                   Word index);

OpaqueFeature* PKG_PALETTE_SAFE_THISCALL
unresolved_008105b0(OpaqueFeatureHost* self, Word feature, Word count);

std::int32_t PKG_PALETTE_SAFE_CDECL unresolved_005c2aa0(void);

void PKG_PALETTE_SAFE_CDECL unresolved_0041e050(OpaqueTextBuffer* buffer,
                                                const TextUnit* format,
                                                std::int32_t first,
                                                std::int32_t second);

void PKG_PALETTE_SAFE_CDECL unresolved_00f47380(void* text);
}

}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

#undef PKG_PALETTE_SAFE_THISCALL
#undef PKG_PALETTE_SAFE_CDECL
