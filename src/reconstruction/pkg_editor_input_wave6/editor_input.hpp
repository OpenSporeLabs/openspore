#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "editor input wave6 staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_editor_input_wave6 {

using TargetWord = std::uint32_t;

#if defined(_MSC_VER)
#define PKG_EDITOR_INPUT_THISCALL __thiscall
#else
#define PKG_EDITOR_INPUT_THISCALL __attribute__((thiscall))
#endif

struct OpaqueEditor {
  std::uint8_t opaque[0x500];
};

struct OpaqueEditorObject {
  std::uint8_t opaque[0xe00];
};

struct OpaqueModeTarget;
struct OpaqueSelectionTarget;

using ModeMouseDown = void(PKG_EDITOR_INPUT_THISCALL*)(OpaqueModeTarget*,
                                                       TargetWord, float, float,
                                                       TargetWord);
using ModeMouseUp = bool(PKG_EDITOR_INPUT_THISCALL*)(OpaqueModeTarget*,
                                                     TargetWord, float, float,
                                                     TargetWord);
using ModeMouseMove = void(PKG_EDITOR_INPUT_THISCALL*)(OpaqueModeTarget*, float,
                                                       float, TargetWord);
using ModeKeyDown = bool(PKG_EDITOR_INPUT_THISCALL*)(OpaqueModeTarget*,
                                                     TargetWord, TargetWord);
using ModeKeyUp = void(PKG_EDITOR_INPUT_THISCALL*)(OpaqueModeTarget*,
                                                   TargetWord, TargetWord);

struct OpaqueModeVtable {
  void* slot_00[4];
  ModeMouseDown mouse_down_10;
  ModeMouseUp mouse_up_14;
  ModeMouseMove mouse_move_18;
  ModeKeyDown key_down_1c;
  ModeKeyUp key_up_20;
};

struct OpaqueModeTarget {
  OpaqueModeVtable* vtable;
  std::uint8_t opaque[0x100];
};

using SelectionRelease =
    void(PKG_EDITOR_INPUT_THISCALL*)(OpaqueSelectionTarget*);
using SelectionMouseUp = bool(PKG_EDITOR_INPUT_THISCALL*)(
    OpaqueSelectionTarget*, TargetWord, float, float, TargetWord);
using SelectionMove = bool(PKG_EDITOR_INPUT_THISCALL*)(OpaqueSelectionTarget*,
                                                       float, float,
                                                       TargetWord);
using SelectionQuery =
    TargetWord(PKG_EDITOR_INPUT_THISCALL*)(OpaqueSelectionTarget*);
using SelectionFinish =
    void(PKG_EDITOR_INPUT_THISCALL*)(OpaqueSelectionTarget*);
using SelectionStatus =
    bool(PKG_EDITOR_INPUT_THISCALL*)(OpaqueSelectionTarget*);

struct OpaqueSelectionVtable {
  void* slot_00;
  SelectionRelease release_04;
  void* slot_08[2];
  SelectionMouseUp mouse_up_10;
  void* slot_14[2];
  SelectionMove mouse_move_1c;
  void* slot_20[2];
  SelectionQuery query_28;
  void* slot_2c;
  SelectionFinish finish_30;
  SelectionStatus status_34;
};

struct OpaqueSelectionTarget {
  OpaqueSelectionVtable* vtable;
  std::uint8_t opaque[0x100];
};

struct OpaqueInputHooks {
  virtual ~OpaqueInputHooks() = default;

  virtual void game_key_down(void*, TargetWord, TargetWord) {}
  virtual void game_key_up(void*, TargetWord, TargetWord) {}
  virtual void state_refresh(OpaqueEditor*) {}
  virtual std::uint8_t dispatch_wheel(OpaqueEditor*, TargetWord, float, float,
                                      TargetWord, TargetWord) {
    return 0;
  }
  virtual bool graphics_available() const { return false; }
  virtual bool key_gate_primary() const { return false; }
  virtual bool key_gate_secondary() const { return false; }
  virtual bool key_path_ready(TargetWord) const { return false; }
  virtual void mouse_down_precheck(OpaqueEditor*) {}
  virtual void mouse_down_blocked(OpaqueEditor*) {}
  virtual bool mouse_down_mode0(OpaqueEditor*, TargetWord, float, float,
                                TargetWord) {
    return false;
  }
  virtual void mouse_down_mode1(OpaqueEditor*, TargetWord, float, float,
                                TargetWord) {}
  virtual bool mouse_down_tail(OpaqueEditor*, TargetWord, float, float,
                               TargetWord) {
    return false;
  }
  virtual void mouse_up_simple(OpaqueEditor*, TargetWord, float, float,
                               TargetWord) {}
  virtual void mouse_up_cleanup(OpaqueEditor*, TargetWord, std::uint8_t,
                                std::uint8_t) {}
  virtual void selection_side_effect(OpaqueSelectionTarget*, TargetWord) {}
  virtual void editor_object_release(OpaqueEditor*) {}
  virtual void key_path(OpaqueEditor*, TargetWord, TargetWord) {}
  virtual void key_command(OpaqueEditor*, TargetWord, TargetWord) {}
  virtual void key_undo_redo(OpaqueEditor*, TargetWord) {}
  virtual void key_pending_clear(OpaqueEditor*) {}
  virtual void key_external_path(OpaqueEditor*, TargetWord) {}
};

extern OpaqueInputHooks* g_input_hooks;

static_assert(sizeof(TargetWord) == 4, "editor input words are 32-bit");
static_assert(sizeof(void*) == 4, "editor input pointers are 32-bit");
static_assert(sizeof(ModeMouseDown) == 4, "mode mouse-down slot is 32-bit");
static_assert(sizeof(ModeMouseUp) == 4, "mode mouse-up slot is 32-bit");
static_assert(sizeof(ModeMouseMove) == 4, "mode mouse-move slot is 32-bit");
static_assert(sizeof(ModeKeyDown) == 4, "mode key-down slot is 32-bit");
static_assert(sizeof(ModeKeyUp) == 4, "mode key-up slot is 32-bit");
static_assert(offsetof(OpaqueModeVtable, mouse_down_10) == 0x10,
              "mode mouse-down slot offset");
static_assert(offsetof(OpaqueModeVtable, mouse_up_14) == 0x14,
              "mode mouse-up slot offset");
static_assert(offsetof(OpaqueModeVtable, mouse_move_18) == 0x18,
              "mode mouse-move slot offset");
static_assert(offsetof(OpaqueModeVtable, key_down_1c) == 0x1c,
              "mode key-down slot offset");
static_assert(offsetof(OpaqueModeVtable, key_up_20) == 0x20,
              "mode key-up slot offset");
static_assert(offsetof(OpaqueSelectionVtable, release_04) == 0x04,
              "selection release slot offset");
static_assert(offsetof(OpaqueSelectionVtable, mouse_up_10) == 0x10,
              "selection mouse-up slot offset");
static_assert(offsetof(OpaqueSelectionVtable, mouse_move_1c) == 0x1c,
              "selection mouse-move slot offset");
static_assert(offsetof(OpaqueSelectionVtable, query_28) == 0x28,
              "selection query slot offset");
static_assert(offsetof(OpaqueSelectionVtable, finish_30) == 0x30,
              "selection finish slot offset");
static_assert(offsetof(OpaqueSelectionVtable, status_34) == 0x34,
              "selection status slot offset");

bool PKG_EDITOR_INPUT_THISCALL editor_input_005737d0(OpaqueEditor*, float,
                                                     float, TargetWord);
bool PKG_EDITOR_INPUT_THISCALL editor_input_00585890(OpaqueEditor*, TargetWord,
                                                     TargetWord);
bool PKG_EDITOR_INPUT_THISCALL editor_input_00585d10(OpaqueEditor*, TargetWord,
                                                     float, float, TargetWord);
bool PKG_EDITOR_INPUT_THISCALL editor_input_00588570(OpaqueEditor*, TargetWord,
                                                     float, float, TargetWord);
bool PKG_EDITOR_INPUT_THISCALL editor_input_0058ac10(OpaqueEditor*, TargetWord,
                                                     TargetWord);
bool PKG_EDITOR_INPUT_THISCALL editor_input_0058b650(OpaqueEditor*, TargetWord,
                                                     float, float, TargetWord);

#undef PKG_EDITOR_INPUT_THISCALL

}
