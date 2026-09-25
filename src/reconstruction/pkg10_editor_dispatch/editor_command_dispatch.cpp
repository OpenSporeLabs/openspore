#include "editor_command_dispatch.hpp"

namespace openspore::reconstruction::pkg10_editor_dispatch {

namespace unresolved_contracts {

using UInt8 = unsigned char;
using UInt32 = EditorCommandUInt32;

extern OpaquePreferences* g_preferences_property_list;

extern UInt8 __thiscall layout_is_ready(void*);
extern void __cdecl notify_command(UInt32);
extern void __thiscall set_active_mode(OpaqueEditorModeManager*, UInt32);
extern UInt8 __thiscall dispatch_subcommand(OpaqueEditorModeManager*, UInt32);
extern void __thiscall editor_undo(OpaqueEditor*, bool, bool);
extern void __thiscall editor_redo(OpaqueEditor*);
extern void* __thiscall lookup_dispatch_target(void*, UInt32, UInt32);
extern OpaqueDispatchTarget* __cdecl cast_dispatch_target(void*);
extern OpaquePreferenceQuery* __thiscall reset_preference_query(
    OpaquePreferenceQuery*, OpaquePropertyValue*);
extern void __thiscall clear_preference_query(OpaquePreferenceQuery*, UInt8);

extern void* __cdecl lookup_preference_value(UInt32, UInt32);
extern void __thiscall apply_preference_value(OpaquePreferences*, void*);
extern UInt8 __thiscall save_editor(OpaqueEditor*, UInt32);
extern UInt8 __cdecl open_game_mode(void*);
extern OpaqueSelectionProvider* __cdecl selection_provider();
extern void __thiscall clear_editor_selection(OpaqueEditor*);
extern void __thiscall set_editor_selection(OpaqueEditor*, UInt32, UInt32);

}

namespace {

using namespace unresolved_contracts;
using UInt8 = unsigned char;
using UInt32 = EditorCommandUInt32;
using Bool8 = unsigned char;
using Bool8NoArgs = Bool8(__thiscall*)(OpaqueUiWindow*, UInt32*,
                                       OpaqueUiMessage**);
using UInt32WindowMessageId = UInt32(__thiscall*)(OpaqueUiWindow*,
                                                  OpaqueUiMessage*, UInt32);
using UInt32Forwarded = UInt32(__thiscall*)(void*, UInt32, OpaqueUiMessage*);
using UInt32MessageId = UInt32(__thiscall*)(OpaqueUiMessage*);

using PreferenceSlot14Adapter = void(__thiscall*)(OpaquePreferences*, UInt32,
                                                  OpaquePreferenceQuery*);
using SelectionSlot4 = UInt32(__thiscall*)(OpaqueSelectionProvider*);
using TargetSlot28NoArgs = UInt32(__thiscall*)(OpaqueDispatchTarget*);
using TargetSlot28Args = UInt32(__thiscall*)(OpaqueDispatchTarget*, UInt32,
                                             UInt32);
using TargetSlot7C = void(__thiscall*)(OpaqueDispatchTarget*, UInt32, UInt32);

template <typename Value>
Value load(const void* object, UInt32 offset) {
  const auto* source = static_cast<const unsigned char*>(object) + offset;
  unsigned char bytes[sizeof(Value)];
  for (unsigned int index = 0; index < sizeof(Value); ++index) {
    bytes[index] = source[index];
  }
  Value value;
  auto* destination = reinterpret_cast<unsigned char*>(&value);
  for (unsigned int index = 0; index < sizeof(Value); ++index) {
    destination[index] = bytes[index];
  }
  return value;
}

template <typename Value>
void store(void* object, UInt32 offset, Value value) {
  auto* destination = static_cast<unsigned char*>(object) + offset;
  const auto* source = reinterpret_cast<const unsigned char*>(&value);
  for (unsigned int index = 0; index < sizeof(Value); ++index) {
    destination[index] = source[index];
  }
}

template <typename Function>
Function load_slot(void* object, UInt32 offset) {
  return load<Function>(object, offset);
}

OpaqueEditorModeManager* manager_base(OpaqueEditorUI* ui) {
  return reinterpret_cast<OpaqueEditorModeManager*>(
      reinterpret_cast<unsigned char*>(ui) - 1);
}

bool handle_outer_a4(OpaqueEditorUI* ui, UInt32 message_id,
                     OpaqueUiMessage* message) {
  auto* window = load<OpaqueUiWindow*>(ui, 0x70);
  const auto accepted =
      load_slot<Bool8NoArgs>(window, 0xa4)(window, &message_id, &message);
  if (accepted == 0) {
    return true;
  }

  const auto result = load_slot<UInt32WindowMessageId>(window, 0x1c4)(
      window, message, message_id);
  auto* editor = load<OpaqueEditor*>(ui, 0x58);
  auto* model = load<void*>(editor, 0x98);
  auto* destination = load<UInt32*>(model, 0x58);
  store(destination, 0, result);
  return true;
}

bool route_message(OpaqueEditorUI* ui, UInt32 message_id,
                   OpaqueUiMessage* message) {
  auto* owner = load<void*>(ui, 0x7c);
  auto* forwarder = load<void*>(owner, 0xc);
  return load_slot<UInt32Forwarded>(forwarder, 0x18)(forwarder, message_id,
                                                     message) != 0;
}

bool handle_preferences(OpaqueEditorUI* ui) {
  OpaquePreferenceQuery query{};
  OpaquePropertyValue property_value{};
  query.enabled = 1;

  auto* preferences = g_preferences_property_list;
  const auto reset_result = reset_preference_query(&query, &property_value);
  static_cast<void>(reset_result);
  load_slot<PreferenceSlot14Adapter>(preferences, 0x14)(preferences,
                                                        0x087c4363u, &query);
  if ((query.flags & 4u) != 0) {
    clear_preference_query(&query, 0);
  }
  auto* value = lookup_preference_value(0x011ac192u, 0);
  apply_preference_value(preferences, value);
  store<UInt8>(ui, 0x108, 1);
  auto* editor = load<OpaqueEditor*>(ui, 0x58);
  if (editor != nullptr) {
    const auto save_result = save_editor(editor, 0);
    static_cast<void>(save_result);
  }
  return false;
}

bool handle_dispatch_pair(OpaqueEditorUI* ui) {
  auto* owner = load<void*>(ui, 0x10c);
  auto* result = lookup_dispatch_target(owner, 0x864a768u, 1);
  if (result == nullptr) {
    return false;
  }

  auto* target = static_cast<OpaqueDispatchTarget*>(result);
  auto* secondary = cast_dispatch_target(target);
  const auto original = load_slot<TargetSlot28NoArgs>(target, 0x28)(target);
  const auto flag = static_cast<UInt32>((original >> 1) & 1u);
  const auto secondary_result =
      load_slot<TargetSlot28Args>(secondary, 0x28)(secondary, 1, flag);
  static_cast<void>(secondary_result);
  load_slot<TargetSlot7C>(target, 0x7c)(target, 2, flag);
  load_slot<TargetSlot7C>(target, 0x7c)(target, 0x10, flag);
  return false;
}

bool route_component_subcommand(OpaqueEditorUI* ui, UInt32 message_id,
                                OpaqueUiMessage* message) {
  auto* message_owner = load<void*>(message, 0);
  const auto subcommand = load_slot<UInt32MessageId>(
      message_owner, 0x20)(static_cast<OpaqueUiMessage*>(message_owner));
  if (dispatch_subcommand(manager_base(ui), subcommand) != 0) {
    return true;
  }

  auto subcommand_value = load<UInt32>(message, 0xc);
  const auto signed_value = static_cast<int>(subcommand_value);
  if (signed_value > 0x447c4e8) {
    if (subcommand_value == 0x864a768u) {
      return handle_preferences(ui);
    }
    if (subcommand_value == 0x47bc978u) {
      notify_command(0xa03e74b2u);
      const auto open_result =
          open_game_mode(reinterpret_cast<void*>(kEditorModePort));
      static_cast<void>(open_result);
      return true;
    }
    if (subcommand_value == 0x56be960u || subcommand_value == 0x5adbea8u) {
      return route_message(ui, message_id, message);
    }
    if (signed_value > 0x864a768) {
      if (subcommand_value == 0x864a771u) {
        store<UInt8>(ui, 0x108, 1);
        return false;
      }
      if (subcommand_value == 0x864a77du) {
        return handle_dispatch_pair(ui);
      }
      subcommand_value -= 0xcu;
      subcommand_value -= 0x67bcdec5u;
      if (subcommand_value == 0) {
        set_active_mode(manager_base(ui), 2);
        return true;
      }
    }
    return false;
  }
  if (subcommand_value == 0x447c4e8u) {
    return route_message(ui, message_id, message);
  }
  if (signed_value > 0x3f67720) {
    subcommand_value -= 0x447b968u;
    if (subcommand_value == 0) {
      return route_message(ui, message_id, message);
    }
    subcommand_value -= 0x18u;
    if (subcommand_value == 0) {
      return route_message(ui, message_id, message);
    }
    subcommand_value -= 0x6c0u;
    if (subcommand_value == 0) {
      return route_message(ui, message_id, message);
    }
    return false;
  }
  if (subcommand_value == 0x3f67720u) {
    return route_message(ui, message_id, message);
  }
  if (signed_value > static_cast<int>(0xf019c2e7u)) {
    if (subcommand_value == 0xf019c2f3u) {
      set_active_mode(manager_base(ui), 1);
      return true;
    }
    return false;
  }
  if (subcommand_value == 0xf019c2e7u) {
    set_active_mode(manager_base(ui), 0);
    return true;
  }
  if (subcommand_value == 0xb006ef6eu) {
    notify_command(0xc355901au);
    editor_undo(load<OpaqueEditor*>(ui, 0x58), true, true);
    return true;
  }
  if (subcommand_value == 0xf006efa5u) {
    notify_command(0x677f1fb8u);
    editor_redo(load<OpaqueEditor*>(ui, 0x58));
    return true;
  }
  return false;
}

bool handle_selection(OpaqueEditorUI* ui, OpaqueUiMessage* message) {
  auto* provider = selection_provider();
  const auto selected = load_slot<SelectionSlot4>(provider, 0x4)(provider);
  if (load<UInt32>(message, 0x18) != selected) {
    return false;
  }
  auto* editor = load<OpaqueEditor*>(ui, 0x58);
  clear_editor_selection(editor);
  if ((load<UInt32>(editor, 0x3c) & 0x100u) != 0) {
    set_editor_selection(editor, 0, 0xffffffffu);
  }
  return false;
}

}

bool __thiscall editor_ui_handle_message(OpaqueEditorUI* ui, UInt32 message_id,
                                         OpaqueUiMessage* message) {
  auto* layout = reinterpret_cast<unsigned char*>(ui) + 0x10;
  if (layout_is_ready(layout) == 0 || load<UInt8>(ui, 0x9d) == 0 ||
      load<UInt8>(ui, 0x9e) != 0) {
    return false;
  }

  const auto event_type = load<UInt32>(message, 0x8);
  if (event_type == kUiMessageOuterA4 &&
      load<UInt32>(message, 0xc) == kUiMessageOuterA4Subvalue) {
    return handle_outer_a4(ui, message_id, message);
  }
  if (event_type == kUiMessageComponentActivated) {
    return route_component_subcommand(ui, message_id, message);
  }
  if (event_type == kUiMessageSelectionPrefix &&
      load<UInt32>(message, 0xc) == kUiMessageSelectionSubvalue) {
    return handle_selection(ui, message);
  }
  return false;
}

}
