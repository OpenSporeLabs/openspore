#include "pkg_palette_safe_wave10.hpp"

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
namespace {

constexpr std::int32_t kSlotShift = 3;
constexpr std::int32_t kSlotBytes = 8;
constexpr std::int32_t kLabelSpanMask = static_cast<std::int32_t>(0xfffffffeU);
constexpr std::int32_t kLabelSpanLimit = 2;
constexpr std::int32_t kRowSpanMask = static_cast<std::int32_t>(0xfffffffcU);
constexpr std::int32_t kStackedSpan = 4;
constexpr std::int32_t kWideSpan = 4;
constexpr std::int32_t kFeatureRows = 1;
constexpr std::int32_t kNavEnabled = 1;
constexpr std::int32_t kNavOff = 0;
constexpr Word kFeatureId = 0x05d3f56bU;
constexpr Word kFeatureCount = 1U;

static_assert(kSlotBytes == (1 << kSlotShift),
              "category slots are indexed by an eight byte stride");
static_assert(kLabelSpanMask == ~1, "label span gate clears the low bit");
static_assert(kRowSpanMask == ~3, "row span gate clears the low two bits");

const TextUnit kFormatText[] = {0x0025U, 0x0069U, 0x002fU,
                                0x0025U, 0x0069U, 0x0000U};

}

const TextUnit* g_format_013f7c30 = kFormatText;
TextUnit g_scratch_01667bac[2] = {0U, 0U};
Real g_row_gap_01486110 = 5.0F;
void* g_table_015fd918 = nullptr;

extern "C" void PKG_PALETTE_SAFE_THISCALL
page_visible_slots_refresh_005c0a60(OpaquePage* self, Word argument) {
  static_cast<void>(argument);
  OpaquePageCategory* const category = self->category_14;
  if (category == nullptr) {
    return;
  }
  if (self->text_18 == nullptr) {
    return;
  }
  const std::int32_t slots =
      static_cast<std::int32_t>(
          reinterpret_cast<std::uintptr_t>(category->end_8c) -
          reinterpret_cast<std::uintptr_t>(category->begin_88)) >>
      kSlotShift;
  std::int32_t total = 0;
  std::int32_t selected = 0;
  volatile OpaquePage* const page = self;
  for (std::int32_t index = 0; index < slots; ++index) {
    if (unresolved_005c29c0(page->category_14, static_cast<Word>(index))) {
      if (index == page->category_14->current_a0) {
        selected = total;
      }
      ++total;
    }
  }
  if (total >= 2) {
    if (self->nav_1c != nullptr) {
      self->nav_1c->vtable->mode7c(self->nav_1c, static_cast<Word>(kNavEnabled),
                                   static_cast<Word>(kNavEnabled));
    }
    if (self->cached_index_20 == selected && self->cached_total_24 == total) {
      return;
    }
    OpaqueTextBuffer buffer = {g_scratch_01667bac, g_scratch_01667bac,
                               g_scratch_01667bac + 2};
    unresolved_0041e050(&buffer, g_format_013f7c30, selected + 1, total);
    self->text_18->vtable->set80(self->text_18, buffer.begin);
    const std::int32_t span = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(buffer.end) -
        reinterpret_cast<std::uintptr_t>(buffer.begin));
    self->cached_index_20 = selected;
    self->cached_total_24 = total;
    if ((span & kLabelSpanMask) <= kLabelSpanLimit) {
      return;
    }
    if (buffer.begin == nullptr) {
      return;
    }
    unresolved_00f47380(const_cast<TextUnit*>(buffer.begin));
    return;
  }
  if (self->nav_1c != nullptr) {
    self->nav_1c->vtable->mode7c(self->nav_1c, static_cast<Word>(kNavEnabled),
                                 static_cast<Word>(kNavOff));
  }
}

extern "C" void PKG_PALETTE_SAFE_THISCALL
palette_row_layout_005c3000(OpaquePalette* self) {
  const std::int32_t row_span = static_cast<std::int32_t>(
      reinterpret_cast<std::uintptr_t>(self->rows_end_78) -
      reinterpret_cast<std::uintptr_t>(self->rows_begin_74));
  bool stacked = (row_span & kRowSpanMask) >= kStackedSpan;
  OpaqueFeature* const feature =
      unresolved_008105b0(self->feature_host_10, kFeatureId, kFeatureCount);
  const bool featured = feature != nullptr;
  OpaquePaletteGroup* const group = self->group_6c;
  const std::int32_t group_span = static_cast<std::int32_t>(
      reinterpret_cast<std::uintptr_t>(group->end_10) -
      reinterpret_cast<std::uintptr_t>(group->begin_0c));
  const bool wide =
      (group_span & kRowSpanMask) > kWideSpan || group->wide_70 != 0;
  OpaqueApp* const app = static_cast<OpaqueApp*>(g_table_015fd918);
  if (app->props_3c->flag_118 != 0 && unresolved_005c2aa0() < kFeatureRows) {
    stacked = false;
  }
  Real offset = g_row_gap_01486110;
  if (stacked && self->lead_20 != nullptr) {
    const OpaqueRect lead = *self->lead_20->vtable->bounds38(self->lead_20);
    offset = lead.h + g_row_gap_01486110;
  }
  if (featured && self->title_24 != nullptr) {
    const OpaqueRect title = *self->title_24->vtable->bounds38(self->title_24);
    OpaqueRect rect = {title.x, offset, title.w, (title.h - title.y) + offset};
    self->title_24->vtable->apply6c(self->title_24, &rect);
    offset = rect.h + g_row_gap_01486110;
  }
  if (self->body_28 == nullptr) {
    return;
  }
  const OpaqueRect body = *self->body_28->vtable->bounds38(self->body_28);
  OpaqueRect rect = {body.x, offset, body.w, body.h};
  if (wide && self->host_1c != nullptr) {
    const OpaqueRect host = *self->host_1c->vtable->bounds38(self->host_1c);
    rect.h = host.y - g_row_gap_01486110;
  } else if (self->tail_2c != nullptr) {
    const OpaqueRect tail = *self->tail_2c->vtable->bounds38(self->tail_2c);
    rect.h = (tail.h - tail.y) - g_row_gap_01486110;
  }
  self->body_28->vtable->apply6c(self->body_28, &rect);
}

}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

#undef PKG_PALETTE_SAFE_THISCALL
#undef PKG_PALETTE_SAFE_CDECL
