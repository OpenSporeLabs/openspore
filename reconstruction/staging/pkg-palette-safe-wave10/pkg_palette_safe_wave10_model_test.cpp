#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <type_traits>

#include "pkg_palette_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_PALETTE_SAFE_TEST_THISCALL __thiscall
#define PKG_PALETTE_SAFE_TEST_CDECL __cdecl
#else
#define PKG_PALETTE_SAFE_TEST_THISCALL __attribute__((thiscall))
#define PKG_PALETTE_SAFE_TEST_CDECL __attribute__((cdecl))
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

namespace openspore::reconstruction::pkg_palette_safe_wave10 {
namespace {

constexpr std::size_t kMaxSlots = 8;
constexpr std::size_t kMaxEvents = 24;
constexpr std::size_t kMaxRows = 4;
constexpr std::size_t kElementCount = 5;

enum Event : std::uint32_t {
  kEventProbe = 1,
  kEventNav,
  kEventFormat,
  kEventText,
  kEventCommit,
  kEventQuery,
  kEventRows,
  kEventLeadBounds,
  kEventHostBounds,
  kEventTitleBounds,
  kEventBodyBounds,
  kEventTailBounds,
  kEventTitleApply,
  kEventBodyApply,
  kEventPoison
};

int g_failures = 0;

void check(bool ok, const char *what) {
  if (ok) {
    return;
  }
  ++g_failures;
  std::printf("FAIL %s\n", what);
}

using PageSignature = void(PKG_PALETTE_SAFE_TEST_THISCALL *)(OpaquePage *,
                                                             Word);
using PaletteSignature =
    void(PKG_PALETTE_SAFE_TEST_THISCALL *)(OpaquePalette *);

static_assert(std::is_same<decltype(&page_visible_slots_refresh_005c0a60),
                           PageSignature>::value,
              "005c0a60 is a thiscall taking the receiver plus one stack word");
static_assert(std::is_same<decltype(&palette_row_layout_005c3000),
                           PaletteSignature>::value,
              "005c3000 is a thiscall taking the receiver alone");
static_assert(
    std::is_same<decltype(std::declval<PageSignature>()(
                     std::declval<OpaquePage *>(), std::declval<Word>())),
                 void>::value,
    "005c0a60 returns nothing");
static_assert(std::is_same<decltype(std::declval<PaletteSignature>()(
                               std::declval<OpaquePalette *>())),
                           void>::value,
              "005c3000 returns nothing");
static_assert(std::is_same<decltype(&unresolved_005c29c0),
                           bool(PKG_PALETTE_SAFE_TEST_THISCALL *)(
                               OpaquePageCategory *, Word)>::value,
              "005c29c0 is a thiscall taking the category plus one stack word");
static_assert(
    std::is_same<decltype(&unresolved_005c2aa0), std::int32_t (*)()>::value,
    "005c2aa0 is a cdecl taking no argument at all");
static_assert(std::is_same<decltype(&unresolved_0041e050),
                           void(PKG_PALETTE_SAFE_TEST_CDECL *)(
                               OpaqueTextBuffer *, const TextUnit *,
                               std::int32_t, std::int32_t)>::value,
              "0041e050 is a cdecl taking the buffer plus three stack words");
static_assert(std::is_same<decltype(&unresolved_00f47380),
                           void(PKG_PALETTE_SAFE_TEST_CDECL *)(void *)>::value,
              "00f47380 is a cdecl taking the one stack word it frees");
static_assert(std::is_same<decltype(&unresolved_008105b0),
                           OpaqueFeature *(PKG_PALETTE_SAFE_TEST_THISCALL
                                               *)(OpaqueFeatureHost *, Word,
                                                  Word)>::value,
              "008105b0 is a thiscall taking the host plus two stack words");
static_assert(sizeof(OpaqueCategorySlot) == 8,
              "the category slot probe is indexed by an eight byte stride");
static_assert(
    offsetof(OpaquePageCategory, current_a0) == 0xa0,
    "the compacted index is compared against the category current slot");
static_assert(offsetof(OpaquePage, cached_index_20) == 0x20 &&
                  offsetof(OpaquePage, cached_total_24) == 0x24,
              "the cached pair occupies the two words at +0x20 and +0x24");
static_assert(offsetof(OpaquePalette, rows_begin_74) == 0x74 &&
                  offsetof(OpaquePalette, rows_end_78) == 0x78,
              "the stacked decision reads the row vector at +0x74 and +0x78");
static_assert(offsetof(OpaquePaletteGroup, wide_70) == 0x70,
              "the wide decision reads the group flag at +0x70");

struct Trace {
  std::uint32_t events[kMaxEvents];
  std::size_t event_count;

  std::uint32_t probe_calls;
  std::uint32_t probe_index[kMaxSlots];
  OpaquePageCategory *probe_this[kMaxSlots];
  OpaquePage *probe_swap_page;
  OpaquePageCategory *probe_swap_category;
  std::uint32_t probe_swap_at;
  std::uint8_t probe_visible[kMaxSlots];

  std::uint32_t nav_calls;
  OpaquePageNav *nav_this[kMaxEvents];
  Word nav_first[kMaxEvents];
  Word nav_second[kMaxEvents];

  std::uint32_t text_calls;
  OpaquePageText *text_this[kMaxEvents];
  const TextUnit *text_units[kMaxEvents];

  std::uint32_t format_calls;
  OpaqueTextBuffer *format_buffer[kMaxEvents];
  const TextUnit *format_text[kMaxEvents];
  std::int32_t format_first[kMaxEvents];
  std::int32_t format_second[kMaxEvents];
  std::int32_t format_span_bytes;
  bool format_null_begin;

  std::uint32_t commit_calls;
  void *commit_text[kMaxEvents];

  std::uint32_t query_calls;
  OpaqueFeatureHost *query_host[kMaxEvents];
  Word query_feature[kMaxEvents];
  Word query_count[kMaxEvents];
  OpaqueFeature *query_result;

  std::uint32_t rows_calls;
  std::int32_t rows_result;

  std::uint32_t bounds_calls;
  OpaqueElement *bounds_this[kMaxEvents];
  std::uint32_t apply_calls;
  OpaqueElement *apply_this[kMaxEvents];
  OpaqueRect apply_rect[kMaxEvents];

  std::uint32_t poison_calls;

  void reset() {
    event_count = 0;
    std::memset(events, 0, sizeof(events));
    probe_calls = 0;
    std::memset(probe_index, 0, sizeof(probe_index));
    std::memset(probe_this, 0, sizeof(probe_this));
    probe_swap_page = nullptr;
    probe_swap_category = nullptr;
    probe_swap_at = 0;
    std::memset(probe_visible, 0, sizeof(probe_visible));
    nav_calls = 0;
    std::memset(nav_this, 0, sizeof(nav_this));
    std::memset(nav_first, 0, sizeof(nav_first));
    std::memset(nav_second, 0, sizeof(nav_second));
    text_calls = 0;
    std::memset(text_this, 0, sizeof(text_this));
    std::memset(text_units, 0, sizeof(text_units));
    format_calls = 0;
    std::memset(format_buffer, 0, sizeof(format_buffer));
    std::memset(format_text, 0, sizeof(format_text));
    std::memset(format_first, 0, sizeof(format_first));
    std::memset(format_second, 0, sizeof(format_second));
    format_span_bytes = 6;
    format_null_begin = false;
    commit_calls = 0;
    std::memset(commit_text, 0, sizeof(commit_text));
    query_calls = 0;
    std::memset(query_host, 0, sizeof(query_host));
    std::memset(query_feature, 0, sizeof(query_feature));
    std::memset(query_count, 0, sizeof(query_count));
    query_result = nullptr;
    rows_calls = 0;
    rows_result = 0;
    bounds_calls = 0;
    std::memset(bounds_this, 0, sizeof(bounds_this));
    apply_calls = 0;
    std::memset(apply_this, 0, sizeof(apply_this));
    std::memset(apply_rect, 0, sizeof(apply_rect));
    poison_calls = 0;
  }
};

Trace g_trace;

void push_event(std::uint32_t event) {
  if (g_trace.event_count < kMaxEvents) {
    g_trace.events[g_trace.event_count] = event;
  }
  ++g_trace.event_count;
}

bool events_are(std::initializer_list<std::uint32_t> expected) {
  if (g_trace.event_count != expected.size()) {
    return false;
  }
  std::size_t index = 0;
  for (const std::uint32_t event : expected) {
    if (g_trace.events[index] != event) {
      return false;
    }
    ++index;
  }
  return true;
}

Word bits_of(Real value) {
  Word raw = 0;
  std::memcpy(&raw, &value, sizeof(raw));
  return raw;
}

bool same_float(Real left, Real right) {
  return bits_of(left) == bits_of(right);
}

bool same_rect(const OpaqueRect &left, const OpaqueRect &right) {
  return same_float(left.x, right.x) && same_float(left.y, right.y) &&
         same_float(left.w, right.w) && same_float(left.h, right.h);
}

struct ElementFixture {
  OpaqueElementVtable vtable;
  OpaqueElement element;
  OpaqueRect bounds;
  std::uint32_t bounds_event;
  std::uint32_t apply_event;
};

ElementFixture g_lead;
ElementFixture g_host;
ElementFixture g_title;
ElementFixture g_body;
ElementFixture g_tail;
ElementFixture *const g_elements[kElementCount] = {&g_lead, &g_host, &g_title,
                                                   &g_body, &g_tail};

struct PageFixture {
  OpaquePage page;
  OpaquePageCategory category;
  OpaqueCategorySlot slots[kMaxSlots];
  OpaquePageText text;
  OpaquePageTextVtable text_vtable;
  OpaquePageNav nav;
  OpaquePageNavVtable nav_vtable;
};

struct PaletteFixture {
  OpaquePalette palette;
  OpaquePaletteGroup group;
  OpaqueElement *rows[kMaxRows];
  OpaqueFeatureHost feature_host;
  OpaqueFeature feature;
  OpaqueApp app;
  OpaqueAppProps props;
};

const OpaqueRect *PKG_PALETTE_SAFE_TEST_THISCALL
element_bounds_stub(OpaqueElement *self);

void PKG_PALETTE_SAFE_TEST_THISCALL element_apply_stub(OpaqueElement *self,
                                                       const OpaqueRect *rect);

void PKG_PALETTE_SAFE_TEST_THISCALL nav_mode_stub(OpaquePageNav *self,
                                                  Word first, Word second);

void PKG_PALETTE_SAFE_TEST_THISCALL text_set_stub(OpaquePageText *self,
                                                  const TextUnit *units);

std::uint32_t apply_event_of(const OpaqueElement *element);

std::uint32_t poison_slot() {
  ++g_trace.poison_calls;
  push_event(kEventPoison);
  return 0;
}

std::uint32_t event_of(const OpaqueElement *element) {
  for (std::size_t index = 0; index < kElementCount; ++index) {
    if (&g_elements[index]->element == element) {
      return g_elements[index]->bounds_event;
    }
  }
  return kEventPoison;
}

OpaqueRect &rect_of(const OpaqueElement *element) {
  for (std::size_t index = 0; index < kElementCount; ++index) {
    if (&g_elements[index]->element == element) {
      return g_elements[index]->bounds;
    }
  }
  return g_lead.bounds;
}

void bind_element(ElementFixture *fixture, std::uint32_t bounds_event,
                  std::uint32_t apply_event, Real x, Real y, Real w, Real h) {
  const std::uintptr_t poison = reinterpret_cast<std::uintptr_t>(&poison_slot);
  for (std::size_t index = 0; index < 14; ++index) {
    fixture->vtable.slots_00_37[index] = poison;
  }
  for (std::size_t index = 0; index < 12; ++index) {
    fixture->vtable.slots_3c_6b[index] = poison;
  }
  fixture->vtable.bounds38 = &element_bounds_stub;
  fixture->vtable.apply6c = &element_apply_stub;
  fixture->element.vtable = &fixture->vtable;
  fixture->bounds.x = x;
  fixture->bounds.y = y;
  fixture->bounds.w = w;
  fixture->bounds.h = h;
  fixture->bounds_event = bounds_event;
  fixture->apply_event = apply_event;
}

const OpaqueRect *PKG_PALETTE_SAFE_TEST_THISCALL
element_bounds_stub(OpaqueElement *self) {
  if (g_trace.bounds_calls < kMaxEvents) {
    g_trace.bounds_this[g_trace.bounds_calls] = self;
  }
  ++g_trace.bounds_calls;
  push_event(event_of(self));
  return &rect_of(self);
}

void PKG_PALETTE_SAFE_TEST_THISCALL element_apply_stub(OpaqueElement *self,
                                                       const OpaqueRect *rect) {
  if (g_trace.apply_calls < kMaxEvents) {
    g_trace.apply_this[g_trace.apply_calls] = self;
    g_trace.apply_rect[g_trace.apply_calls] = *rect;
  }
  ++g_trace.apply_calls;
  push_event(apply_event_of(self));
}

void PKG_PALETTE_SAFE_TEST_THISCALL nav_mode_stub(OpaquePageNav *self,
                                                  Word first, Word second) {
  if (g_trace.nav_calls < kMaxEvents) {
    g_trace.nav_this[g_trace.nav_calls] = self;
    g_trace.nav_first[g_trace.nav_calls] = first;
    g_trace.nav_second[g_trace.nav_calls] = second;
  }
  ++g_trace.nav_calls;
  push_event(kEventNav);
}

void PKG_PALETTE_SAFE_TEST_THISCALL text_set_stub(OpaquePageText *self,
                                                  const TextUnit *units) {
  if (g_trace.text_calls < kMaxEvents) {
    g_trace.text_this[g_trace.text_calls] = self;
    g_trace.text_units[g_trace.text_calls] = units;
  }
  ++g_trace.text_calls;
  push_event(kEventText);
}

void bind_page(PageFixture *fixture) {
  std::memset(fixture, 0, sizeof(*fixture));
  const std::uintptr_t poison = reinterpret_cast<std::uintptr_t>(&poison_slot);
  for (std::size_t index = 0; index < 32; ++index) {
    fixture->text_vtable.slots_00_7f[index] = poison;
  }
  fixture->text_vtable.set80 = &text_set_stub;
  fixture->text.vtable = &fixture->text_vtable;
  for (std::size_t index = 0; index < 31; ++index) {
    fixture->nav_vtable.slots_00_7b[index] = poison;
  }
  fixture->nav_vtable.mode7c = &nav_mode_stub;
  fixture->nav.vtable = &fixture->nav_vtable;
  fixture->page.vtable = nullptr;
  fixture->page.category_14 = &fixture->category;
  fixture->page.text_18 = &fixture->text;
  fixture->page.nav_1c = &fixture->nav;
  fixture->page.cached_index_20 = 0;
  fixture->page.cached_total_24 = 0;
  fixture->category.begin_88 = fixture->slots;
  fixture->category.end_8c = fixture->slots;
  fixture->category.current_a0 = 0;
}

void span_slots(PageFixture *fixture, std::int32_t bytes) {
  fixture->category.begin_88 = fixture->slots;
  fixture->category.end_8c = reinterpret_cast<OpaqueCategorySlot *>(
      reinterpret_cast<char *>(fixture->slots) + bytes);
}

void bind_palette(PaletteFixture *fixture) {
  std::memset(fixture, 0, sizeof(*fixture));
  bind_element(&g_lead, kEventLeadBounds, kEventPoison, 1.0F, 2.0F, 3.0F,
               40.0F);
  bind_element(&g_host, kEventHostBounds, kEventPoison, 5.0F, 60.0F, 7.0F,
               80.0F);
  bind_element(&g_title, kEventTitleBounds, kEventTitleApply, 9.0F, 10.0F,
               11.0F, 34.0F);
  bind_element(&g_body, kEventBodyBounds, kEventBodyApply, 13.0F, 14.0F, 15.0F,
               50.0F);
  bind_element(&g_tail, kEventTailBounds, kEventPoison, 17.0F, 18.0F, 19.0F,
               70.0F);
  for (std::size_t index = 0; index < kMaxRows; ++index) {
    fixture->rows[index] = &g_body.element;
  }
  fixture->palette.vtable = nullptr;
  fixture->palette.feature_host_10 = &fixture->feature_host;
  fixture->palette.host_1c = &g_host.element;
  fixture->palette.lead_20 = &g_lead.element;
  fixture->palette.title_24 = &g_title.element;
  fixture->palette.body_28 = &g_body.element;
  fixture->palette.tail_2c = &g_tail.element;
  fixture->palette.group_6c = &fixture->group;
  fixture->palette.rows_begin_74 = fixture->rows;
  fixture->palette.rows_end_78 = fixture->rows;
  fixture->group.begin_0c = fixture->rows;
  fixture->group.end_10 = fixture->rows;
  fixture->group.wide_70 = 0;
  fixture->app.props_3c = &fixture->props;
  fixture->props.flag_118 = 0;
  fixture->feature.vtable = nullptr;
  g_table_015fd918 = &fixture->app;
}

void span_rows(PaletteFixture *fixture, std::int32_t bytes) {
  fixture->palette.rows_begin_74 = fixture->rows;
  fixture->palette.rows_end_78 = reinterpret_cast<OpaqueElement **>(
      reinterpret_cast<char *>(fixture->rows) + bytes);
}

void span_group(PaletteFixture *fixture, std::int32_t bytes) {
  fixture->group.begin_0c = fixture->rows;
  fixture->group.end_10 = reinterpret_cast<OpaqueElement **>(
      reinterpret_cast<char *>(fixture->rows) + bytes);
}

void reset_all(PageFixture *page, PaletteFixture *palette) {
  g_trace.reset();
  std::memset(g_scratch_01667bac, 0, sizeof(g_scratch_01667bac));
  g_row_gap_01486110 = 5.0F;
  bind_page(page);
  bind_palette(palette);
}

void test_page_null_category_is_inert() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  page.page.category_14 = nullptr;
  std::uint8_t before[sizeof(OpaquePage)];
  std::memcpy(before, &page.page, sizeof(before));
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.event_count == 0, "a null category reaches no port");
  check(std::memcmp(before, &page.page, sizeof(before)) == 0,
        "a null category leaves the page untouched");
}

void test_page_null_text_is_inert() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 3 * 8);
  for (std::size_t index = 0; index < 3; ++index) {
    g_trace.probe_visible[index] = 1;
  }
  page.page.text_18 = nullptr;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.event_count == 0, "a null text slot reaches no port");
  check(page.page.cached_index_20 == 0 && page.page.cached_total_24 == 0,
        "a null text slot leaves the cached pair alone");
}

void test_page_empty_category_disables_nav() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.probe_calls == 0, "an empty category probes no slot");
  check(g_trace.nav_calls == 1, "an empty category still calls the nav slot");
  check(g_trace.nav_first[0] == 1 && g_trace.nav_second[0] == 0,
        "an empty category passes the pair one and zero");
  check(g_trace.nav_this[0] == &page.nav,
        "the nav slot receives the +0x1c page slot");
  check(g_trace.format_calls == 0 && g_trace.text_calls == 0,
        "an empty category formats no label");
  check(events_are({kEventNav}), "an empty category only touches the nav slot");
}

void test_page_one_visible_slot_disables_nav() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 3 * 8);
  g_trace.probe_visible[0] = 1;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.probe_calls == 3, "every slot is probed once");
  check(g_trace.probe_index[0] == 0 && g_trace.probe_index[1] == 1 &&
            g_trace.probe_index[2] == 2,
        "the probe walks the slots in order");
  check(g_trace.nav_calls == 1 && g_trace.nav_second[0] == 0,
        "a single visible slot keeps the nav pair at one and zero");
  check(g_trace.format_calls == 0 && g_trace.commit_calls == 0,
        "a single visible slot formats no label");
  check(events_are({kEventProbe, kEventProbe, kEventProbe, kEventNav}),
        "probing precedes the nav slot");
}

void test_page_two_visible_slots_format_label() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 3 * 8);
  for (std::size_t index = 0; index < 3; ++index) {
    g_trace.probe_visible[index] = 1;
  }
  page.category.current_a0 = 1;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.nav_calls == 1 && g_trace.nav_first[0] == 1 &&
            g_trace.nav_second[0] == 1,
        "two visible slots enable the nav pair");
  check(g_trace.format_calls == 1, "the label is formatted once");
  check(g_trace.format_first[0] == 2 && g_trace.format_second[0] == 3,
        "the label carries the one based slot and the visible total");
  check(g_trace.format_text[0] == g_format_013f7c30,
        "the label uses the observed percent i over percent i literal");
  check(g_trace.text_calls == 1 && g_trace.text_this[0] == &page.text,
        "the text slot receives the label once");
  check(g_trace.text_units[0] == g_scratch_01667bac,
        "the text slot receives the formatted begin pointer");
  check(
      g_trace.commit_calls == 1 && g_trace.commit_text[0] == g_scratch_01667bac,
      "a six byte label is committed through the port");
  check(page.page.cached_index_20 == 1 && page.page.cached_total_24 == 3,
        "the cached pair records the compacted index and the total");
  check(events_are({kEventProbe, kEventProbe, kEventProbe, kEventNav,
                    kEventFormat, kEventText, kEventCommit}),
        "the label path runs probe, nav, format, text and commit in order");
}

void test_page_hidden_current_slot_falls_back_to_zero() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 3 * 8);
  g_trace.probe_visible[0] = 1;
  g_trace.probe_visible[2] = 1;
  page.category.current_a0 = 2;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.format_first[0] == 2 && g_trace.format_second[0] == 2,
        "a visible current slot maps onto the compacted index");
  check(page.page.cached_index_20 == 1 && page.page.cached_total_24 == 2,
        "the cached index follows the compacted position");
}

void test_page_current_slot_before_first_visible_keeps_zero() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 3 * 8);
  g_trace.probe_visible[1] = 1;
  g_trace.probe_visible[2] = 1;
  page.category.current_a0 = 0;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.format_first[0] == 1 && g_trace.format_second[0] == 2,
        "a hidden current slot leaves the label at one of two");
  check(page.page.cached_index_20 == 0,
        "a hidden current slot caches the zero index");
}

void test_page_cached_pair_short_circuits_label() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 3 * 8);
  for (std::size_t index = 0; index < 3; ++index) {
    g_trace.probe_visible[index] = 1;
  }
  page.category.current_a0 = 1;
  page.page.cached_index_20 = 1;
  page.page.cached_total_24 = 3;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.nav_calls == 1 && g_trace.nav_second[0] == 1,
        "the nav slot still runs before the cached comparison");
  check(g_trace.format_calls == 0 && g_trace.text_calls == 0 &&
            g_trace.commit_calls == 0,
        "a matching cached pair suppresses the whole label path");
  check(events_are({kEventProbe, kEventProbe, kEventProbe, kEventNav}),
        "a matching cached pair stops after the nav slot");
}

void test_page_cached_total_mismatch_still_formats() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 3 * 8);
  for (std::size_t index = 0; index < 3; ++index) {
    g_trace.probe_visible[index] = 1;
  }
  page.category.current_a0 = 1;
  page.page.cached_index_20 = 1;
  page.page.cached_total_24 = 2;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.format_calls == 1 && g_trace.format_second[0] == 3,
        "a stale cached total reformats the label");
  check(page.page.cached_total_24 == 3, "the stale cached total is refreshed");
}

void test_page_null_nav_still_updates_label() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 2 * 8);
  g_trace.probe_visible[0] = 1;
  g_trace.probe_visible[1] = 1;
  page.page.nav_1c = nullptr;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.nav_calls == 0, "a null nav slot is skipped");
  check(g_trace.format_calls == 1 && g_trace.text_calls == 1 &&
            g_trace.commit_calls == 1,
        "a null nav slot does not stop the label path");
  check(events_are(
            {kEventProbe, kEventProbe, kEventFormat, kEventText, kEventCommit}),
        "a null nav slot drops only the nav event");
}

void test_page_label_span_gate_skips_commit() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 2 * 8);
  g_trace.probe_visible[0] = 1;
  g_trace.probe_visible[1] = 1;
  g_trace.format_span_bytes = 2;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.commit_calls == 0, "a two byte label is not committed");
  check(page.page.cached_total_24 == 2,
        "the cached pair is written before the label gate");

  reset_all(&page, &palette);
  span_slots(&page, 2 * 8);
  g_trace.probe_visible[0] = 1;
  g_trace.probe_visible[1] = 1;
  g_trace.format_span_bytes = 3;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.commit_calls == 0, "a three byte label masks down to two");

  reset_all(&page, &palette);
  span_slots(&page, 2 * 8);
  g_trace.probe_visible[0] = 1;
  g_trace.probe_visible[1] = 1;
  g_trace.format_span_bytes = 4;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.commit_calls == 1, "a four byte label clears the gate");
}

void test_page_null_label_pointer_skips_commit() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 2 * 8);
  g_trace.probe_visible[0] = 1;
  g_trace.probe_visible[1] = 1;
  g_trace.format_null_begin = true;
  g_trace.format_span_bytes = 6;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.text_calls == 1 && g_trace.text_units[0] == nullptr,
        "the null begin pointer is still handed to the text slot");
  check(g_trace.commit_calls == 0,
        "a null begin pointer is never handed to the commit port");
  check(page.page.cached_total_24 == 2,
        "the cached pair is written before the label gates");
}

void test_page_slot_span_uses_eight_byte_stride() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 20);
  for (std::size_t index = 0; index < kMaxSlots; ++index) {
    g_trace.probe_visible[index] = 1;
  }
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.probe_calls == 2, "a twenty byte span yields two slots");
  check(g_trace.format_second[0] == 2, "both slots are visible and counted");

  reset_all(&page, &palette);
  span_slots(&page, 24);
  for (std::size_t index = 0; index < kMaxSlots; ++index) {
    g_trace.probe_visible[index] = 1;
  }
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.probe_calls == 3, "a twenty four byte span yields three slots");

  reset_all(&page, &palette);
  span_slots(&page, 7);
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.probe_calls == 0, "a seven byte span yields no slot");
}

void test_page_category_pointer_is_reloaded_each_iteration() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  OpaquePageCategory swapped;
  std::memset(&swapped, 0, sizeof(swapped));
  swapped.begin_88 = page.slots;
  swapped.end_8c = page.slots + kMaxSlots;
  swapped.current_a0 = 2;
  page.category.current_a0 = 0;
  span_slots(&page, 4 * 8);
  for (std::size_t index = 0; index < 4; ++index) {
    g_trace.probe_visible[index] = 1;
  }
  g_trace.probe_swap_page = &page.page;
  g_trace.probe_swap_category = &swapped;
  g_trace.probe_swap_at = 1;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.probe_calls == 4, "every visible slot is probed once");
  check(g_trace.probe_this[0] == &page.category &&
            g_trace.probe_this[1] == &page.category &&
            g_trace.probe_this[2] == &swapped &&
            g_trace.probe_this[3] == &swapped,
        "the probe receiver is reloaded from +0x14 on every iteration");
  check(g_trace.format_calls == 1 && g_trace.format_first[0] == 3 &&
            g_trace.format_second[0] == 4,
        "the compacted index follows the reloaded category word");
  check(page.page.cached_index_20 == 2 && page.page.cached_total_24 == 4,
        "the reloaded category word drives the cached pair");

  reset_all(&page, &palette);
  std::memset(&swapped, 0, sizeof(swapped));
  swapped.begin_88 = page.slots;
  swapped.end_8c = page.slots + kMaxSlots;
  swapped.current_a0 = 0;
  page.category.current_a0 = 0;
  span_slots(&page, 4 * 8);
  for (std::size_t index = 0; index < 4; ++index) {
    g_trace.probe_visible[index] = 1;
  }
  g_trace.probe_swap_page = &page.page;
  g_trace.probe_swap_category = &swapped;
  g_trace.probe_swap_at = 1;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.format_calls == 1 && g_trace.format_first[0] == 1 &&
            g_trace.format_second[0] == 4,
        "a reloaded category matching slot zero still compacts to zero");
  check(page.page.cached_index_20 == 0 && page.page.cached_total_24 == 4,
        "the reloaded category word still drives the cached pair");
}

void test_page_writes_only_the_cached_pair() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 3 * 8);
  for (std::size_t index = 0; index < 3; ++index) {
    g_trace.probe_visible[index] = 1;
  }
  page.category.current_a0 = 2;
  std::uint8_t before[sizeof(OpaquePage)];
  std::memcpy(before, &page.page, sizeof(before));
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(std::memcmp(before, reinterpret_cast<const std::uint8_t *>(&page.page),
                    0x20) == 0,
        "the page words below +0x20 are untouched");
  check(std::memcmp(before + 0x20,
                    reinterpret_cast<const std::uint8_t *>(&page.page) + 0x20,
                    sizeof(OpaquePage) - 0x20) != 0,
        "the cached pair at +0x20 and +0x24 is written");
  check(page.page.category_14 == &page.category &&
            page.page.text_18 == &page.text && page.page.nav_1c == &page.nav,
        "the page slots at +0x14 +0x18 and +0x1c are untouched");
}

std::uint32_t g_page_probe_result = 0;

void PKG_PALETTE_SAFE_TEST_CDECL page_stack_probe(OpaquePage *self,
                                                  Word argument,
                                                  Word third_word,
                                                  Word guard_low,
                                                  Word guard_high) {
  std::uint32_t *const canary =
      static_cast<std::uint32_t *>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  static_cast<void>(third_word);
  const PageSignature refresh = &page_visible_slots_refresh_005c0a60;
  refresh(self, argument);
  check(canary[0] == 0xc0dec0deu, "the stack canary below the call held");
  check(canary[1] == 0xfeedfaceu, "the second stack canary word held");
  check(guard_low == 0x11223344u, "the word after the second argument held");
  check(guard_high == 0x55667788u, "the word after the third argument held");
  g_page_probe_result = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
}

void test_page_stack_discipline() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_slots(&page, 2 * 8);
  g_trace.probe_visible[0] = 1;
  g_trace.probe_visible[1] = 1;
  std::uint8_t with_zero_third[sizeof(OpaquePage)];
  std::uint8_t with_set_third[sizeof(OpaquePage)];
  page_stack_probe(&page.page, 0u, 0x00000000u, 0x11223344u, 0x55667788u);
  std::memcpy(with_zero_third, &page.page, sizeof(with_zero_third));
  page_stack_probe(&page.page, 0u, 0xffffffffu, 0x11223344u, 0x55667788u);
  std::memcpy(with_set_third, &page.page, sizeof(with_set_third));
  check(std::memcmp(with_zero_third, with_set_third, sizeof(with_zero_third)) ==
            0,
        "the third stack word never influences the observed effect");
  check(g_page_probe_result ==
            (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u),
        "the callee released exactly the one word it was given");
  check(page.page.cached_total_24 == 2,
        "the probe call still reached the label path");
}

void test_palette_base_layout() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  palette_row_layout_005c3000(&palette.palette);
  check(g_trace.query_calls == 1, "the feature query is issued once");
  check(g_trace.query_feature[0] == 0x05d3f56bu && g_trace.query_count[0] == 1u,
        "the feature query carries the observed id and count");
  check(g_trace.query_host[0] == &palette.feature_host,
        "the feature query receiver is the +0x10 host");
  check(g_trace.rows_calls == 0, "a zero application flag skips the row count");
  check(g_trace.apply_calls == 1 && g_trace.apply_this[0] == &g_body.element,
        "only the body rectangle is applied");
  const OpaqueRect expected = {13.0F, 5.0F, 15.0F, 47.0F};
  check(same_rect(g_trace.apply_rect[0], expected),
        "the base body rectangle is x thirteen, gap, width, tail minus gap");
  check(g_trace.bounds_calls == 2, "the body and tail bounds are queried");
  check(events_are(
            {kEventQuery, kEventBodyBounds, kEventTailBounds, kEventBodyApply}),
        "the base pass runs query, body, tail and body apply in order");
}

void test_palette_row_mask_selects_stacked() {
  PageFixture page;
  PaletteFixture palette;
  const std::int32_t spans[] = {0, 3, 4, 5, 8};
  const bool stacked[] = {false, false, true, true, true};
  for (std::size_t index = 0; index < 5; ++index) {
    reset_all(&page, &palette);
    span_rows(&palette, spans[index]);
    palette_row_layout_005c3000(&palette.palette);
    const Real expected = stacked[index] ? 45.0F : 5.0F;
    check(same_float(g_trace.apply_rect[0].y, expected),
          "the row span mask decides the stacked offset");
    check(g_trace.bounds_calls == (stacked[index] ? 3u : 2u),
          "the lead bounds are queried only when the rows are stacked");
  }
}

void test_palette_feature_block_moves_the_title() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  g_trace.query_result = &palette.feature;
  palette_row_layout_005c3000(&palette.palette);
  check(g_trace.apply_calls == 2, "the title and body rectangles are applied");
  check(g_trace.apply_this[0] == &g_title.element &&
            g_trace.apply_this[1] == &g_body.element,
        "the title rectangle is applied before the body rectangle");
  const OpaqueRect expected_title = {9.0F, 5.0F, 11.0F, 29.0F};
  check(same_rect(g_trace.apply_rect[0], expected_title),
        "the title rectangle spans the base offset plus its own height");
  const OpaqueRect expected_body = {13.0F, 34.0F, 15.0F, 47.0F};
  check(same_rect(g_trace.apply_rect[1], expected_body),
        "the body offset follows the applied title height plus the gap");
  check(events_are({kEventQuery, kEventTitleBounds, kEventTitleApply,
                    kEventBodyBounds, kEventTailBounds, kEventBodyApply}),
        "the feature pass runs query, title, body, tail and both applies");
}

void test_palette_stacked_feature_block_chains_offsets() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_rows(&palette, 8);
  g_trace.query_result = &palette.feature;
  palette_row_layout_005c3000(&palette.palette);
  const OpaqueRect expected_title = {9.0F, 45.0F, 11.0F, 69.0F};
  check(same_rect(g_trace.apply_rect[0], expected_title),
        "the title rectangle starts below the stacked lead offset");
  const OpaqueRect expected_body = {13.0F, 74.0F, 15.0F, 47.0F};
  check(same_rect(g_trace.apply_rect[1], expected_body),
        "the body offset follows the stacked title rectangle");
}

void test_palette_null_title_skips_feature_block() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  g_trace.query_result = &palette.feature;
  palette.palette.title_24 = nullptr;
  palette_row_layout_005c3000(&palette.palette);
  check(g_trace.apply_calls == 1 && g_trace.apply_this[0] == &g_body.element,
        "a null title applies no title rectangle");
  check(same_float(g_trace.apply_rect[0].y, 5.0F),
        "a null title leaves the body offset at the gap");
  check(g_trace.bounds_calls == 2, "a null title queries no title bounds");
}

void test_palette_null_body_stops_after_feature_block() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  g_trace.query_result = &palette.feature;
  palette.palette.body_28 = nullptr;
  palette_row_layout_005c3000(&palette.palette);
  check(g_trace.apply_calls == 1 && g_trace.apply_this[0] == &g_title.element,
        "a null body still applies the title rectangle");
  check(g_trace.bounds_calls == 1, "a null body queries no body bounds");
  check(events_are({kEventQuery, kEventTitleBounds, kEventTitleApply}),
        "a null body stops after the query, the title bounds and the apply");
}

void test_palette_app_flag_gates_stacked() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_rows(&palette, 8);
  palette_row_layout_005c3000(&palette.palette);
  check(g_trace.rows_calls == 0, "a zero application flag skips the row count");
  check(same_float(g_trace.apply_rect[0].y, 45.0F),
        "a zero application flag keeps the stacked offset");

  reset_all(&page, &palette);
  span_rows(&palette, 8);
  palette.props.flag_118 = 1;
  g_trace.rows_result = 0;
  palette_row_layout_005c3000(&palette.palette);
  check(g_trace.rows_calls == 1,
        "a set application flag asks the palette for its distinct rows");
  check(same_float(g_trace.apply_rect[0].y, 5.0F),
        "a zero distinct row count clears the stacked offset");
  check(events_are({kEventQuery, kEventRows, kEventBodyBounds, kEventTailBounds,
                    kEventBodyApply}),
        "the row count is asked right after the feature query");

  reset_all(&page, &palette);
  span_rows(&palette, 8);
  palette.props.flag_118 = 1;
  g_trace.rows_result = 1;
  palette_row_layout_005c3000(&palette.palette);
  check(same_float(g_trace.apply_rect[0].y, 45.0F),
        "a distinct row count of one keeps the stacked offset");
}

void test_palette_wide_group_uses_host_edge() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_group(&palette, 8);
  palette_row_layout_005c3000(&palette.palette);
  const OpaqueRect expected = {13.0F, 5.0F, 15.0F, 55.0F};
  check(same_rect(g_trace.apply_rect[0], expected),
        "a group span above four bytes takes the host lower edge");
  check(events_are(
            {kEventQuery, kEventBodyBounds, kEventHostBounds, kEventBodyApply}),
        "the wide pass queries the host instead of the tail");

  reset_all(&page, &palette);
  span_group(&palette, 4);
  palette.group.wide_70 = 1;
  palette_row_layout_005c3000(&palette.palette);
  check(same_float(g_trace.apply_rect[0].h, 55.0F),
        "a group span of exactly four bytes still honours the wide flag");
}

void test_palette_narrow_group_uses_tail_edge() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_group(&palette, 4);
  palette_row_layout_005c3000(&palette.palette);
  const OpaqueRect expected = {13.0F, 5.0F, 15.0F, 47.0F};
  check(same_rect(g_trace.apply_rect[0], expected),
        "a narrow group takes the tail height minus the gap");

  reset_all(&page, &palette);
  span_group(&palette, 0);
  palette.palette.tail_2c = nullptr;
  palette_row_layout_005c3000(&palette.palette);
  check(same_float(g_trace.apply_rect[0].h, 50.0F),
        "a narrow group without a tail keeps the measured body height");
  check(g_trace.bounds_calls == 1,
        "a narrow group without a tail queries once");
}

void test_palette_null_lead_keeps_base_offset() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_rows(&palette, 8);
  palette.palette.lead_20 = nullptr;
  palette_row_layout_005c3000(&palette.palette);
  check(same_float(g_trace.apply_rect[0].y, 5.0F),
        "a stacked palette without a lead keeps the gap offset");
  check(g_trace.bounds_calls == 2, "a null lead queries no lead bounds");
}

void test_palette_null_host_falls_back_to_tail_when_wide() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_group(&palette, 8);
  palette.palette.host_1c = nullptr;
  palette_row_layout_005c3000(&palette.palette);
  check(same_float(g_trace.apply_rect[0].h, 47.0F),
        "a wide group without a host falls back to the tail height");
  check(events_are(
            {kEventQuery, kEventBodyBounds, kEventTailBounds, kEventBodyApply}),
        "a missing host still falls through to the tail bounds");
}

void test_palette_row_gap_is_read_from_the_global() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  g_row_gap_01486110 = 2.5F;
  palette_row_layout_005c3000(&palette.palette);
  const OpaqueRect expected = {13.0F, 2.5F, 15.0F, 49.5F};
  check(same_rect(g_trace.apply_rect[0], expected),
        "the row gap global drives both the offset and the tail trim");
  check(bits_of(g_trace.apply_rect[0].y) == 0x40200000u,
        "the offset keeps the exact bit pattern of the gap global");
}

std::uint32_t g_palette_probe_result = 0;

void PKG_PALETTE_SAFE_TEST_CDECL palette_stack_probe(OpaquePalette *self,
                                                     Word guard_low,
                                                     Word guard_high) {
  std::uint32_t *const canary =
      static_cast<std::uint32_t *>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  const PaletteSignature layout = &palette_row_layout_005c3000;
  layout(self);
  check(canary[0] == 0xc0dec0deu, "the palette stack canary held");
  check(canary[1] == 0xfeedfaceu, "the second palette canary word held");
  check(guard_low == 0x11223344u,
        "the word the palette entry must not pop held");
  check(guard_high == 0x55667788u, "the word after the first guard held");
  g_palette_probe_result = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
}

void test_palette_stack_discipline() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  palette_stack_probe(&palette.palette, 0x11223344u, 0x55667788u);
  check(g_palette_probe_result ==
            (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u),
        "the palette entry released no stack word of its own");
  check(g_trace.apply_calls == 1,
        "the palette probe call still applied the body rectangle");
}

void test_palette_row_count_port_takes_no_argument() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  span_rows(&palette, 8);
  palette.props.flag_118 = 1;
  g_trace.rows_result = 0;
  palette_stack_probe(&palette.palette, 0x11223344u, 0x55667788u);
  check(g_trace.rows_calls == 1,
        "the distinct row port is reached through the stack probe");
  check(g_palette_probe_result ==
            (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u),
        "the distinct row port releases no stack word of its own");
  check(g_trace.poison_calls == 0,
        "the distinct row port call reaches no unmodelled slot");
  check(same_float(g_trace.apply_rect[0].y, 5.0F),
        "a zero distinct row count still clears the stacked offset");
}

void test_palette_never_reaches_an_unmodelled_slot() {
  PageFixture page;
  PaletteFixture palette;
  reset_all(&page, &palette);
  g_trace.query_result = &palette.feature;
  span_rows(&palette, 8);
  span_group(&palette, 8);
  palette_row_layout_005c3000(&palette.palette);
  check(g_trace.poison_calls == 0, "the palette pass reads only the two slots");
  check(g_trace.apply_calls == 2,
        "the full palette pass applies both rectangles");
  span_slots(&page, 2 * 8);
  g_trace.probe_visible[0] = 1;
  g_trace.probe_visible[1] = 1;
  page_visible_slots_refresh_005c0a60(&page.page, 0u);
  check(g_trace.poison_calls == 0, "the page pass reads only the two slots");
  check(g_trace.text_calls == 1, "the page pass still reaches the text slot");
}

std::uint32_t apply_event_of(const OpaqueElement *element) {
  for (std::size_t index = 0; index < kElementCount; ++index) {
    if (&g_elements[index]->element == element) {
      return g_elements[index]->apply_event;
    }
  }
  return kEventPoison;
}

}

extern "C" bool PKG_PALETTE_SAFE_TEST_THISCALL
unresolved_005c29c0(OpaquePageCategory *self, Word index) {
  static_cast<void>(self);
  const std::uint32_t probe = g_trace.probe_calls;
  if (probe < kMaxSlots) {
    g_trace.probe_index[probe] = index;
    g_trace.probe_this[probe] = self;
  }
  ++g_trace.probe_calls;
  push_event(kEventProbe);
  const bool visible = index < kMaxSlots && g_trace.probe_visible[index] != 0;
  if (g_trace.probe_swap_page != nullptr && probe == g_trace.probe_swap_at) {
    g_trace.probe_swap_page->category_14 = g_trace.probe_swap_category;
    g_trace.probe_swap_page = nullptr;
  }
  return visible;
}

extern "C" OpaqueFeature *PKG_PALETTE_SAFE_TEST_THISCALL
unresolved_008105b0(OpaqueFeatureHost *self, Word feature, Word count) {
  const std::uint32_t slot = g_trace.query_calls;
  if (slot < kMaxEvents) {
    g_trace.query_host[slot] = self;
    g_trace.query_feature[slot] = feature;
    g_trace.query_count[slot] = count;
  }
  ++g_trace.query_calls;
  push_event(kEventQuery);
  return g_trace.query_result;
}

extern "C" std::int32_t PKG_PALETTE_SAFE_TEST_CDECL unresolved_005c2aa0(void) {
  ++g_trace.rows_calls;
  push_event(kEventRows);
  return g_trace.rows_result;
}

extern "C" void PKG_PALETTE_SAFE_TEST_CDECL
unresolved_0041e050(OpaqueTextBuffer *buffer, const TextUnit *format,
                    std::int32_t first, std::int32_t second) {
  const std::uint32_t slot = g_trace.format_calls;
  if (slot < kMaxEvents) {
    g_trace.format_buffer[slot] = buffer;
    g_trace.format_text[slot] = format;
    g_trace.format_first[slot] = first;
    g_trace.format_second[slot] = second;
  }
  ++g_trace.format_calls;
  push_event(kEventFormat);
  const std::uintptr_t begin =
      g_trace.format_null_begin
          ? 0u
          : reinterpret_cast<std::uintptr_t>(g_scratch_01667bac);
  buffer->begin = reinterpret_cast<TextUnit *>(begin);
  buffer->cursor = buffer->begin;
  buffer->end = reinterpret_cast<TextUnit *>(
      begin + static_cast<std::uintptr_t>(g_trace.format_span_bytes));
}

extern "C" void PKG_PALETTE_SAFE_TEST_CDECL unresolved_00f47380(void *text) {
  const std::uint32_t slot = g_trace.commit_calls;
  if (slot < kMaxEvents) {
    g_trace.commit_text[slot] = text;
  }
  ++g_trace.commit_calls;
  push_event(kEventCommit);
}

}

namespace openspore::reconstruction::pkg_palette_safe_wave10 {
namespace {

void run_all() {
  test_page_null_category_is_inert();
  test_page_null_text_is_inert();
  test_page_empty_category_disables_nav();
  test_page_one_visible_slot_disables_nav();
  test_page_two_visible_slots_format_label();
  test_page_hidden_current_slot_falls_back_to_zero();
  test_page_current_slot_before_first_visible_keeps_zero();
  test_page_cached_pair_short_circuits_label();
  test_page_cached_total_mismatch_still_formats();
  test_page_null_nav_still_updates_label();
  test_page_label_span_gate_skips_commit();
  test_page_null_label_pointer_skips_commit();
  test_page_slot_span_uses_eight_byte_stride();
  test_page_category_pointer_is_reloaded_each_iteration();
  test_page_writes_only_the_cached_pair();
  test_page_stack_discipline();
  test_palette_base_layout();
  test_palette_row_mask_selects_stacked();
  test_palette_feature_block_moves_the_title();
  test_palette_stacked_feature_block_chains_offsets();
  test_palette_null_title_skips_feature_block();
  test_palette_null_body_stops_after_feature_block();
  test_palette_app_flag_gates_stacked();
  test_palette_wide_group_uses_host_edge();
  test_palette_narrow_group_uses_tail_edge();
  test_palette_null_lead_keeps_base_offset();
  test_palette_null_host_falls_back_to_tail_when_wide();
  test_palette_row_gap_is_read_from_the_global();
  test_palette_stack_discipline();
  test_palette_row_count_port_takes_no_argument();
  test_palette_never_reaches_an_unmodelled_slot();
}

int report() {
  if (g_failures != 0) {
    std::printf("pkg-palette-safe-wave10: %d failure(s)\n", g_failures);
    return 1;
  }
  std::printf("pkg-palette-safe-wave10: all checks passed\n");
  return 0;
}

}
}

int main() {
  openspore::reconstruction::pkg_palette_safe_wave10::run_all();
  return openspore::reconstruction::pkg_palette_safe_wave10::report();
}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

#undef PKG_PALETTE_SAFE_TEST_THISCALL
#undef PKG_PALETTE_SAFE_TEST_CDECL
