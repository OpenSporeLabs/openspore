#pragma once

#include <cstddef>

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// The receiver. Only the offsets that the observed accessor family around
// 0x004adb00 touches are declared, and they are declared because a single SDK
// struct declaration, Spore/Editors/EditorModel.h, reproduces all of them in
// order:
//
//   /* 38h */ float mBounds;                     getter 0x004adaa0, setter 0x004ada80
//   /* 3Ch */ float mFeetBounds;                 setter 0x004adac0
//   /* 40h */ float mMinHeight;   // -2.0         setter 0x004adae0, getter 0x004adb00
//   /* 44h */ float mMaxHeight;   //  2.0         setter 0x004adb20, getter 0x004adb40
//   /* 4Ch */ bool   mShowHiddenHandles;         getter 0x004adb80, setter 0x004adba0
//   /* 4Dh */ bool   mShowBoneLengthHandles;     getter 0x004adbc0, setter 0x004adbe0
//   /* 4Eh */ bool   mUseBoundsForDelete;        setter 0x004adb60
//
// No vtable for that class was located, so the owning type is recorded as a
// bounded candidate and not as an established fact.
struct OpaqueEditorModel {
  unsigned char pad_000_038[0x38];
  float mBounds;              // +0x38
  float mFeetBounds;          // +0x3c
  float mMinHeight;           // +0x40  <- the field this target reads
  float mMaxHeight;           // +0x44
  float mMinimumLeglessHeight;  // +0x48
  unsigned char mShowHiddenHandles;        // +0x4c
  unsigned char mShowBoneLengthHandles;    // +0x4d
  unsigned char mUseBoundsForDelete;       // +0x4e
};

static_assert(sizeof(void*) == 4, "the target is x86-32");
static_assert(offsetof(OpaqueEditorModel, mBounds) == 0x38,
              "the +0x38 sibling accessors agree with EditorModel::mBounds");
static_assert(offsetof(OpaqueEditorModel, mFeetBounds) == 0x3c,
              "the +0x3c setter agrees with EditorModel::mFeetBounds");
static_assert(offsetof(OpaqueEditorModel, mMinHeight) == 0x40,
              "0x004adb0a FLD dword ptr [EAX + 0x40] reads this field");
static_assert(offsetof(OpaqueEditorModel, mMaxHeight) == 0x44,
              "the +0x44 sibling accessors agree with EditorModel::mMaxHeight");
static_assert(offsetof(OpaqueEditorModel, mShowHiddenHandles) == 0x4c,
              "the +0x4c byte accessors agree with mShowHiddenHandles");
static_assert(offsetof(OpaqueEditorModel, mShowBoneLengthHandles) == 0x4d,
              "the +0x4d byte accessors agree with mShowBoneLengthHandles");
static_assert(offsetof(OpaqueEditorModel, mUseBoundsForDelete) == 0x4e,
              "the +0x4e byte setter agrees with mUseBoundsForDelete");

// 0x004adb00. __thiscall, ECX receiver, no stack argument, bare RET, and the
// result is an x87 ST0 float rather than an XMM0 or EAX value.
float __thiscall editor_model_min_height_getter_004adb00(
    const OpaqueEditorModel* model);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
