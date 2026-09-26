#pragma once

#include <cstddef>

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// Spore/MathUtils.h Vector3 is not needed here. Two byte flags and three
// sub-object addresses are all this body touches.
//
// Spore/Editors/EditorUI.h declares, and every offset below was read out of the
// disassembly of 0x005dd7a0 and its tail target 0x005dc800:
//   /* 14h */ UTFWin::UILayout mMainUI;     LEA ECX,[ESI+0x14] at 0x005dd7f1
//   /* 2Ch */ UTFWin::UILayout mSharedUI;   LEA ECX,[ESI+0x2c] at 0x005dd804
//   /* 5Ch */ cEditor* mpEditor;            MOV ECX,[ESI+0x5c] at 0x005dd7a7
//   /* D1h */ bool field_D1;   // true      CMP byte ptr [ESI+0xd1],BL at 0x005dd7de
//   /* 102h*/ bool field_102;              CMP byte ptr [ESI+0x102],BL at 0x005dd7ba
//   /* 104h*/ bool field_104;              read by the tail target 0x005dc800
// with ASSERT_SIZE(EditorUI, 0x12C).
//
// The class name is recorded as a strong candidate only: no vtable for it was
// located, and this binary has no MSVC RTTI.
// A stand-in for UTFWin::UILayout, which the SDK declares at /* 14h */ mMainUI
// and /* 2Ch */ mSharedUI. Only the ADDRESS of each is ever used here - as the
// thiscall receiver of the element lookup - so no layout content is claimed and
// the type is kept minimal.
struct OpaqueUiLayout {
  int unmodelled;
};

struct OpaqueEditorUi {
  unsigned char pad_000_014[0x14];
  OpaqueUiLayout mMainUI;      // +0x14, the first lookup context
  unsigned char pad_018_02C[0x2c - 0x18];
  OpaqueUiLayout mSharedUI;    // +0x2c, the fallback lookup context
  unsigned char pad_030_05C[0x5c - 0x30];
  void* mpEditor;             // +0x5c, cEditor*
  unsigned char pad_060_0D1[0xd1 - 0x60];
  unsigned char field_D1;     // +0xd1
  unsigned char pad_0D2_102[0x102 - 0xd2];
  unsigned char field_102;    // +0x102
  unsigned char pad_103_104[1];
  unsigned char field_104;    // +0x104
};

// The 5-valued classification produced by 0x0057aaa0. The three cases that map
// to flagB = 1 are 0, 1 and 2; the two that map to flagB = 0 are 3 and 4.
enum PaintAvailability : int {
  kPaintBoth = 0,
  kPaintFirstOnly = 1,
  kPaintNeither = 2,
  kPaintNoKeysPropertyFalse = 3,
  kPaintNoKeysNoMatch = 4,
};

static_assert(sizeof(void*) == 4, "the target is x86-32");
static_assert(offsetof(OpaqueEditorUi, mMainUI) == 0x14,
              "the first provider lookup context is at +0x14");
static_assert(offsetof(OpaqueEditorUi, mSharedUI) == 0x2c,
              "the fallback provider lookup context is at +0x2c");
static_assert(offsetof(OpaqueEditorUi, mpEditor) == 0x5c,
              "the 5-valued classification is asked of the +0x5c pointer");
static_assert(offsetof(OpaqueEditorUi, field_D1) == 0xd1,
              "the +0xd1 byte can only clear the second flag");
static_assert(offsetof(OpaqueEditorUi, field_102) == 0x102,
              "the +0x102 byte gates the whole classification");
static_assert(offsetof(OpaqueEditorUi, field_104) == 0x104,
              "the +0x104 byte is read by the tail target 0x005dc800");

// Unresolved ports. Shapes come from the disassembly; the operation behind each
// is recorded as far as the callee's own decompiled body allowed.
namespace unresolved_ports {

// 0x0057aaa0(cEditor* editor) -> int in 0..4.
// Queries the bool property 0x55d7ca1 and compares the editor's ResourceKey at
// +0x48..+0x54 against two other keys, with the editor bytes at +0x4b3 and
// +0x4b4 as a precondition. Returns one of the five PaintAvailability values.
extern int __fastcall classify_paint_availability(void* editor);

// 0x008105b0(UILayout* context, uint32_t element_id, int mode) -> provider*.
// Returns null when the id is not present in that layout. Called first on
// mMainUI and then, only on failure, on mSharedUI.
extern void* __thiscall layout_find_element(OpaqueUiLayout*, unsigned int,
                                            int);

// Virtual slot +0x7c of the resolved provider, thiscall with callee-clean and
// two stack arguments: an integer selector (1 then 2) and a boolean state.
// 0x005dc800 performs the same two calls on a provider resolved from the same
// two layouts with different element ids, 0x612efea and 0x612efeb.
extern void __thiscall provider_set_toggle(void*, int selector,
                                           int state);

// 0x005dc800(EditorUI* ui). The tail target, reached by JMP not CALL, with the
// receiver already back in ECX. It re-reads [ui+0x5c], re-runs the same
// classification, reads [ui+0xd1] and [ui+0x104], and performs the same
// vtable+0x7c pattern for the ids 0x612efea and 0x612efeb.
extern void __fastcall editor_ui_publish_undo_state_005dc800(OpaqueEditorUi*);

}  // namespace unresolved_ports

// 0x005dd7a0. __thiscall, ECX receiver, no stack argument, no return value.
// Not a virtual entry: Ghidra lists 14 xrefs to it, all UNCONDITIONAL_CALL.
void __thiscall editor_ui_publish_paint_toggle_005dd7a0(OpaqueEditorUi* ui);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
