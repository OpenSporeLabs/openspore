#pragma once

namespace openspore::reconstruction::pkg10_editor_dispatch {

using EditorCommandUInt32 = unsigned int;

struct OpaqueEditorUI;
struct OpaqueEditor;
struct OpaqueEditorModeManager;
struct OpaqueUiMessage;
struct OpaqueUiWindow;
struct OpaquePreferences;
struct OpaquePropertyValue;

struct OpaquePreferenceQuery {
  unsigned char opaque_prefix[0x0c];
  unsigned char enabled;
  unsigned char padding[3];
  unsigned short flags;
  unsigned short trailing_flags;
};

struct OpaquePropertyValue {
  unsigned char bytes[0x14];
};

struct OpaqueSelectionProvider;
struct OpaqueDispatchTarget;

inline constexpr EditorCommandUInt32 kUiMessageOuterA4 = 0x9a1552d3u;
inline constexpr EditorCommandUInt32 kUiMessageOuterA4Subvalue = 0x503517b0u;
inline constexpr EditorCommandUInt32 kUiMessageComponentActivated = 0x287259f6u;
inline constexpr EditorCommandUInt32 kUiMessageSelectionPrefix = 0x1cu;
inline constexpr EditorCommandUInt32 kUiMessageSelectionSubvalue = 1u;
inline constexpr EditorCommandUInt32 kEditorUiModeZero = 0xf019c2e7u;
inline constexpr EditorCommandUInt32 kEditorUiModeOne = 0xf019c2f3u;
inline constexpr EditorCommandUInt32 kEditorUiModeTwo = 0x70218642u;
inline constexpr EditorCommandUInt32 kEditorUiUndo = 0xb006ef6eu;
inline constexpr EditorCommandUInt32 kEditorUiRedo = 0xf006efa5u;
inline constexpr EditorCommandUInt32 kEditorUiPreferences = 0x864a768u;
inline constexpr EditorCommandUInt32 kEditorUiPendingFlag = 0x864a771u;
inline constexpr EditorCommandUInt32 kEditorUiDispatchPair = 0x864a77du;
inline constexpr EditorCommandUInt32 kEditorUiHelp = 0x47bc978u;
inline constexpr EditorCommandUInt32 kEditorModePort = 0x00dbdba1u;

static_assert(sizeof(EditorCommandUInt32) == 4,
              "the command ABI uses 32-bit words");
static_assert(sizeof(void*) == 4,
              "the command ABI uses 32-bit object pointers");
static_assert(sizeof(OpaquePreferenceQuery) == 0x14,
              "the preference query preserves its observed 0x14-byte extent");
static_assert(__builtin_offsetof(OpaquePreferenceQuery, enabled) == 0x0c,
              "the preference query value byte is at +0x0c");
static_assert(__builtin_offsetof(OpaquePreferenceQuery, flags) == 0x10,
              "the preference query flags word is at +0x10");
static_assert(__builtin_offsetof(OpaquePreferenceQuery, trailing_flags) == 0x12,
              "the preference query trailing flags word is at +0x12");

bool __thiscall editor_ui_handle_message(OpaqueEditorUI*, EditorCommandUInt32,
                                         OpaqueUiMessage*);

}
