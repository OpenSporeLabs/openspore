#pragma once

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_UTFWIN_DRAWABLE_THISCALL __thiscall
#else
#define PKG_UTFWIN_DRAWABLE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_drawable_wave9 {

using OpaqueWord = std::uint32_t;

struct OpaqueObject;
struct OpaqueObjectVTable;
struct OpaqueTreeNodeWire;

using OpaqueSlot14 = OpaqueWord(PKG_UTFWIN_DRAWABLE_THISCALL*)(OpaqueObject*);

struct OpaqueObjectVTable {
  OpaqueWord slot_00 = 0;
  OpaqueWord slot_04 = 0;
  OpaqueWord slot_08 = 0;
  OpaqueWord slot_0c = 0;
  OpaqueWord slot_10 = 0;
  OpaqueSlot14 slot_14 = nullptr;
};

struct OpaqueObject {
  OpaqueObjectVTable* vtable_00 = nullptr;
};

struct OpaqueDrawableWire {
  OpaqueWord field_00 = 0;
  OpaqueWord field_04 = 0;
  OpaqueWord field_08 = 0;
  OpaqueWord field_0c = 0;
};

struct OpaqueSpinnerDrawableWire {
  OpaqueDrawableWire base{};
  OpaqueWord images_10[3]{};
};

struct OpaqueImageDrawableWire {
  OpaqueDrawableWire base{};
  OpaqueWord scale_10 = 0;
  OpaqueWord flags_14 = 0;
  OpaqueWord tiling_18 = 0;
  OpaqueWord alignment_h_1c = 0;
  OpaqueWord alignment_v_20 = 0;
  OpaqueWord image_24 = 0;
  OpaqueWord outline_28[10]{};
};

struct OpaqueStdDrawableWire {
  OpaqueDrawableWire base{};
  OpaqueWord images_10[8]{};
  OpaqueWord scale_type_30 = 0;
  OpaqueWord scale_area_34[4]{};
  OpaqueWord scale_factor_44[2]{};
  OpaqueWord hit_mask_4c = 0;
  OpaqueWord property_50 = 0;
  OpaqueWord outline_54[10]{};
};

struct OpaqueListNode {
  OpaqueListNode* next = nullptr;
  OpaqueListNode* previous = nullptr;
};

struct OpaqueTreeNodeList {
  OpaqueListNode anchor{};
};

struct OpaqueString16 {
  OpaqueWord begin_00 = 0;
  OpaqueWord end_04 = 0;
  OpaqueWord capacity_08 = 0;
  OpaqueWord allocator_0c = 0;
};

struct OpaqueTreeNodeWire {
  OpaqueObjectVTable* vtable_00 = nullptr;
  OpaqueWord interface_vtable_04 = 0;
  OpaqueWord ref_count_08 = 0;
  OpaqueListNode* next_0c = nullptr;
  OpaqueListNode* previous_10 = nullptr;
  OpaqueWord tree_view_14 = 0;
  OpaqueTreeNodeWire* parent_18 = nullptr;
  OpaqueTreeNodeList children_1c{};
  OpaqueWord field_24 = 0;
  OpaqueWord node_flags_28 = 0;
  OpaqueWord text_style_2c = 0;
  OpaqueWord field_30 = 0;
  OpaqueString16 caption_34{};
  OpaqueWord node_id_44 = 0;
  OpaqueWord icon_48 = 0;
  OpaqueWord object_4c = 0;
};

extern "C" void PKG_UTFWIN_DRAWABLE_THISCALL
re_009849a0(OpaqueObject* self, OpaqueDrawableWire* target);
extern "C" OpaqueWord PKG_UTFWIN_DRAWABLE_THISCALL
re_00985ce0(OpaqueObject* self);
extern "C" void PKG_UTFWIN_DRAWABLE_THISCALL
re_00987ae0(OpaqueObject* self, OpaqueDrawableWire* target);
extern "C" OpaqueWord PKG_UTFWIN_DRAWABLE_THISCALL
re_00b267d0(OpaqueObject* self, OpaqueWord selector);

static_assert(sizeof(void*) == 4, "UTFWin drawable pointers are 32-bit");
static_assert(sizeof(OpaqueObjectVTable) == 0x18, "UTFWin opaque vtable size");
static_assert(sizeof(OpaqueDrawableWire) == 0x10, "UTFWin drawable base size");
static_assert(offsetof(OpaqueDrawableWire, field_04) == 0x04,
              "UTFWin drawable field offset");
static_assert(offsetof(OpaqueDrawableWire, field_08) == 0x08,
              "UTFWin drawable refcount offset");
static_assert(offsetof(OpaqueDrawableWire, field_0c) == 0x0c,
              "UTFWin drawable derived vtable offset");
static_assert(sizeof(OpaqueSpinnerDrawableWire) == 0x1c,
              "UTFWin spinner drawable size");
static_assert(offsetof(OpaqueSpinnerDrawableWire, images_10) == 0x10,
              "UTFWin spinner image offset");
static_assert(sizeof(OpaqueImageDrawableWire) == 0x50,
              "UTFWin image drawable size");
static_assert(offsetof(OpaqueImageDrawableWire, alignment_h_1c) == 0x1c,
              "UTFWin image horizontal alignment offset");
static_assert(offsetof(OpaqueImageDrawableWire, alignment_v_20) == 0x20,
              "UTFWin image vertical alignment offset");
static_assert(offsetof(OpaqueImageDrawableWire, image_24) == 0x24,
              "UTFWin image field offset");
static_assert(offsetof(OpaqueImageDrawableWire, outline_28) == 0x28,
              "UTFWin image outline offset");
static_assert(sizeof(OpaqueStdDrawableWire) == 0x7c,
              "UTFWin standard drawable size");
static_assert(offsetof(OpaqueStdDrawableWire, scale_type_30) == 0x30,
              "UTFWin standard scale type offset");
static_assert(offsetof(OpaqueStdDrawableWire, scale_area_34) == 0x34,
              "UTFWin standard scale area offset");
static_assert(offsetof(OpaqueStdDrawableWire, scale_factor_44) == 0x44,
              "UTFWin standard scale factor offset");
static_assert(offsetof(OpaqueStdDrawableWire, hit_mask_4c) == 0x4c,
              "UTFWin standard hit mask offset");
static_assert(offsetof(OpaqueStdDrawableWire, outline_54) == 0x54,
              "UTFWin standard outline offset");
static_assert(sizeof(OpaqueListNode) == 0x08,
              "UTFWin intrusive list node size");
static_assert(sizeof(OpaqueTreeNodeList) == 0x08, "UTFWin intrusive list size");
static_assert(offsetof(OpaqueTreeNodeWire, next_0c) == 0x0c,
              "UTFWin tree next offset");
static_assert(offsetof(OpaqueTreeNodeWire, previous_10) == 0x10,
              "UTFWin tree previous offset");
static_assert(offsetof(OpaqueTreeNodeWire, children_1c) == 0x1c,
              "UTFWin tree children offset");
static_assert(offsetof(OpaqueTreeNodeWire, node_flags_28) == 0x28,
              "UTFWin tree flags offset");
static_assert(offsetof(OpaqueTreeNodeWire, caption_34) == 0x34,
              "UTFWin tree caption offset");
static_assert(sizeof(OpaqueString16) == 0x10, "UTFWin string size");
static_assert(sizeof(OpaqueTreeNodeWire) == 0x50, "UTFWin tree node size");

}
