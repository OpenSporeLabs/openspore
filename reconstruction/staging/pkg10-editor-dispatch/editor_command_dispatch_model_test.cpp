#include "editor_command_dispatch.hpp"

namespace openspore::reconstruction::pkg10_editor_dispatch {

using UInt8 = unsigned char;
using UInt32 = EditorCommandUInt32;

struct OpaqueEditor {};
struct OpaqueEditorModeManager {};
struct OpaqueUiWindow {};
struct OpaquePreferences {};
struct OpaqueSelectionProvider {};

struct OpaqueDispatchTarget {
  void* vtable;
};

namespace model {

enum Kind : UInt8 {
  layout,
  notify,
  subcommand,
  mode,
  undo,
  redo,
  message_id,
  route,
  slot_a4,
  slot_1c4,
  preference_reset,
  preference_query,
  preference_clear,
  preference_lookup,
  preference_apply,
  pending,
  save,
  open_mode,
  lookup,
  cast,
  target28,
  target7c,
  selection_id,
  clear_selection,
  set_selection,
};

struct Event {
  Kind kind;
  UInt32 first;
  UInt32 second;
  const void* object;
};

Event events[256];
unsigned int event_count;
unsigned int failures;
UInt8 layout_ready_result;
UInt8 dispatch_result;
UInt8 slot_a4_result;
UInt8 preference_flags;
UInt32 route_result;
UInt32 preference_value_result;
UInt32 dispatch_pair_original;
UInt32 selected_id;
OpaquePreferences preferences;
OpaqueSelectionProvider selection_provider;
OpaqueDispatchTarget* lookup_result;
OpaqueDispatchTarget* secondary_target;
OpaqueUiMessage* replacement_message;
UInt32 replacement_message_id;
bool slot_a4_mutate;
const void* reset_property_argument;
bool reset_property_is_preferences;

void reset() {
  event_count = 0;
  failures = 0;
  layout_ready_result = 1;
  dispatch_result = 0;
  slot_a4_result = 1;
  preference_flags = 0;
  route_result = 0;
  preference_value_result = 0x12345678u;
  dispatch_pair_original = 0;
  selected_id = 0;
  lookup_result = nullptr;
  secondary_target = nullptr;
  replacement_message = nullptr;
  replacement_message_id = 0;
  slot_a4_mutate = false;
  reset_property_argument = nullptr;
  reset_property_is_preferences = false;
}

void add(Kind kind, UInt32 first = 0, UInt32 second = 0,
         const void* object = nullptr) {
  if (event_count < 256) {
    events[event_count++] = Event{kind, first, second, object};
  }
}

void expect(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void expect_event(unsigned int index, Kind kind, UInt32 first = 0,
                  UInt32 second = 0, const void* object = nullptr) {
  expect(index < event_count);
  if (index >= event_count) {
    return;
  }
  const Event& event = events[index];
  expect(event.kind == kind && event.first == first && event.second == second &&
         event.object == object);
}

void expect_count(unsigned int count) { expect(event_count == count); }

}

struct TestEditorUI {
  unsigned char bytes[0x12c];
};

struct TestMessage {
  void* vtable;
  unsigned char bytes[0x18];
  UInt32 event_type;
  UInt32 subcommand;
  UInt32 payload;
};

struct TestWindow {
  void* vtable;
  UInt32 stored;
};

struct TestForwarder {
  void* vtable;
};

struct TestPreferenceList {
  void* vtable;
};

struct TestEditor {
  unsigned char bytes[0x9c];
};

struct TestTarget {
  void* vtable;
};

using MessageSlot20 = UInt32(__thiscall*)(OpaqueUiMessage*);
using WindowSlotA4 = UInt8(__thiscall*)(OpaqueUiWindow*, UInt32*,
                                        OpaqueUiMessage**);
using WindowSlot1C4 = UInt32(__thiscall*)(OpaqueUiWindow*, OpaqueUiMessage*,
                                          UInt32);
using ForwardSlot18 = UInt32(__thiscall*)(void*, UInt32, OpaqueUiMessage*);
using PreferenceSlot14 = void(__thiscall*)(OpaquePreferences*, UInt32,
                                           OpaquePreferenceQuery*);
using SelectionSlot4 = UInt32(__thiscall*)(OpaqueSelectionProvider*);
using TargetSlot28NoArgs = UInt32(__thiscall*)(OpaqueDispatchTarget*);
using TargetSlot28Args = UInt32(__thiscall*)(OpaqueDispatchTarget*, UInt32,
                                             UInt32);
using TargetSlot7C = void(__thiscall*)(OpaqueDispatchTarget*, UInt32, UInt32);

template <typename Value>
void store(void* object, UInt32 offset, Value value) {
  auto* destination = static_cast<unsigned char*>(object) + offset;
  const auto* source = reinterpret_cast<const unsigned char*>(&value);
  for (unsigned int index = 0; index < sizeof(Value); ++index) {
    destination[index] = source[index];
  }
}

template <typename Value>
Value load(const void* object, UInt32 offset) {
  const auto* source = static_cast<const unsigned char*>(object) + offset;
  Value value;
  auto* destination = reinterpret_cast<unsigned char*>(&value);
  for (unsigned int index = 0; index < sizeof(Value); ++index) {
    destination[index] = source[index];
  }
  return value;
}

namespace unresolved_contracts {

OpaquePreferences* g_preferences_property_list;

UInt8 __thiscall layout_is_ready(void* object) {
  model::add(model::layout, 0, 0, object);
  return model::layout_ready_result;
}

void __cdecl notify_command(UInt32 value) { model::add(model::notify, value); }

void __thiscall set_active_mode(OpaqueEditorModeManager* manager, UInt32 mode) {
  model::add(model::mode, mode, 0, manager);
}

UInt8 __thiscall dispatch_subcommand(OpaqueEditorModeManager* manager,
                                     UInt32 value) {
  model::add(model::subcommand, value, 0, manager);
  return model::dispatch_result;
}

void __thiscall editor_undo(OpaqueEditor* editor, bool first, bool second) {
  model::add(model::undo, first, second, editor);
}

void __thiscall editor_redo(OpaqueEditor* editor) {
  model::add(model::redo, 0, 0, editor);
}

void* __thiscall lookup_dispatch_target(void* owner, UInt32 key, UInt32 flag) {
  model::add(model::lookup, key, flag, owner);
  return model::lookup_result;
}

OpaqueDispatchTarget* __cdecl cast_dispatch_target(void* object) {
  model::add(model::cast, 0, 0, object);
  return model::secondary_target;
}

OpaquePreferenceQuery* __thiscall reset_preference_query(
    OpaquePreferenceQuery* query, OpaquePropertyValue* property_value) {
  model::add(model::preference_reset, 0, 0, query);
  model::add(model::preference_reset, 0, 0, property_value);
  model::reset_property_argument = property_value;
  model::reset_property_is_preferences =
      property_value ==
      reinterpret_cast<OpaquePropertyValue*>(g_preferences_property_list);
  query->flags = 0;
  query->trailing_flags = 0;
  return query;
}

void __thiscall clear_preference_query(OpaquePreferenceQuery* query,
                                       UInt8 zero) {
  model::expect(zero == 0);
  model::add(model::preference_clear, zero, 0, query);
  query->flags = 0;
  query->trailing_flags = 0;
}

void* __cdecl lookup_preference_value(UInt32 key, UInt32 mode) {
  model::add(model::preference_lookup, key, mode);
  return reinterpret_cast<void*>(model::preference_value_result);
}

void __thiscall apply_preference_value(OpaquePreferences* preferences,
                                       void* value) {
  model::add(model::preference_apply,
             static_cast<UInt32>(reinterpret_cast<unsigned int>(value)), 0,
             preferences);
}

UInt8 __thiscall save_editor(OpaqueEditor* editor, UInt32 mode) {
  model::add(model::save, mode, 0, editor);
  return 0xa5;
}

UInt8 __cdecl open_game_mode(void* mode) {
  model::add(model::open_mode, 0, 0, mode);
  return 0xb6;
}

OpaqueSelectionProvider* __cdecl selection_provider() {
  return &model::selection_provider;
}

void __thiscall clear_editor_selection(OpaqueEditor* editor) {
  model::add(model::clear_selection, 0, 0, editor);
}

void __thiscall set_editor_selection(OpaqueEditor* editor, UInt32 first,
                                     UInt32 second) {
  model::add(model::set_selection, first, second, editor);
}

}

UInt32 __thiscall message_slot_20(OpaqueUiMessage*) {
  model::add(model::message_id);
  return 0x44u;
}

UInt8 __thiscall window_slot_a4(OpaqueUiWindow*, UInt32* message_id,
                                OpaqueUiMessage** message) {
  model::add(model::slot_a4);
  if (model::slot_a4_mutate) {
    *message_id = model::replacement_message_id;
    *message = model::replacement_message;
  }
  return model::slot_a4_result;
}

UInt32 __thiscall window_slot_1c4(OpaqueUiWindow* window,
                                  OpaqueUiMessage* message, UInt32 message_id) {
  model::add(model::slot_1c4,
             static_cast<UInt32>(reinterpret_cast<unsigned int>(message)),
             message_id, window);
  return 0xabcdef01u;
}

UInt32 __thiscall forward_slot_18(void*, UInt32 message_id, OpaqueUiMessage*) {
  model::add(model::route, message_id);
  return model::route_result;
}

void __thiscall preference_slot_14(OpaquePreferences*, UInt32 key,
                                   OpaquePreferenceQuery* query) {
  model::expect(query->enabled == 1);
  model::expect(query->trailing_flags == 0);
  model::add(model::preference_query, key, 0, query);
  query->flags = model::preference_flags;
}

UInt32 __thiscall selection_slot_4(OpaqueSelectionProvider*) {
  model::add(model::selection_id);
  return model::selected_id;
}

UInt32 __thiscall target_slot_28_no_args(OpaqueDispatchTarget*) {
  model::add(model::target28, 0, 0);
  return model::dispatch_pair_original;
}

UInt32 __thiscall target_slot_28_args(OpaqueDispatchTarget*, UInt32 first,
                                      UInt32 second) {
  model::add(model::target28, first, second);
  return 0;
}

void __thiscall target_slot_7c(OpaqueDispatchTarget*, UInt32 first,
                               UInt32 second) {
  model::add(model::target7c, first, second);
}

bool run() {
  TestEditorUI ui;
  TestEditor editor;
  TestEditor model_sink;
  TestMessage message;
  TestMessage replacement;
  TestWindow window;
  TestForwarder forwarder;
  TestPreferenceList preferences;
  TestTarget target;
  TestTarget secondary;
  unsigned int message_vtable[9]{};
  unsigned int window_vtable[115]{};
  unsigned int forward_vtable[7]{};
  unsigned int preference_vtable[6]{};
  unsigned int selection_vtable[2]{};
  unsigned int target_vtable[32]{};
  unsigned int secondary_vtable[11]{};

  message_vtable[8] = reinterpret_cast<unsigned int>(message_slot_20);
  window_vtable[41] = reinterpret_cast<unsigned int>(window_slot_a4);
  forward_vtable[6] = reinterpret_cast<unsigned int>(forward_slot_18);
  preference_vtable[5] = reinterpret_cast<unsigned int>(preference_slot_14);
  selection_vtable[1] = reinterpret_cast<unsigned int>(selection_slot_4);
  target_vtable[10] = reinterpret_cast<unsigned int>(target_slot_28_no_args);
  target_vtable[31] = reinterpret_cast<unsigned int>(target_slot_7c);
  secondary_vtable[10] = reinterpret_cast<unsigned int>(target_slot_28_args);
  store(&message, 0, static_cast<void*>(message_vtable));
  store(&window, 0, static_cast<void*>(window_vtable));
  window_vtable[113] = reinterpret_cast<unsigned int>(window_slot_1c4);
  store(&forwarder, 0, static_cast<void*>(forward_vtable));
  store(&preferences, 0, static_cast<void*>(preference_vtable));
  store(&model::selection_provider, 0, static_cast<void*>(selection_vtable));
  store(&target, 0, static_cast<void*>(target_vtable));

  store(&ui, 0x58, reinterpret_cast<OpaqueEditor*>(&editor));
  store(&ui, 0x70, reinterpret_cast<OpaqueUiWindow*>(&window));
  store(&ui, 0x7c, static_cast<void*>(&forwarder));
  store(&ui, 0x9d, static_cast<UInt8>(1));
  store(&ui, 0x108, static_cast<UInt8>(0));
  store(&editor, 0x3c, 0x100u);
  store(&editor, 0x98, static_cast<void*>(&model_sink));
  auto* message_object = reinterpret_cast<OpaqueUiMessage*>(&message);
  auto* ui_object = reinterpret_cast<OpaqueEditorUI*>(&ui);
  auto* editor_object = reinterpret_cast<OpaqueEditor*>(&editor);
  auto* preferences_object = reinterpret_cast<OpaquePreferences*>(&preferences);
  auto* manager = reinterpret_cast<OpaqueEditorModeManager*>(
      reinterpret_cast<unsigned char*>(ui_object) - 1);
  unresolved_contracts::g_preferences_property_list = preferences_object;

  model::reset();
  message.event_type = kUiMessageOuterA4;
  message.subcommand = kUiMessageOuterA4Subvalue;
  model::slot_a4_result = 0;
  model::expect(editor_ui_handle_message(ui_object, 7, message_object));
  model::expect_count(2);
  model::expect_event(0, model::layout, 0, 0, &ui.bytes[0x10]);
  model::expect_event(1, model::slot_a4);

  model::reset();
  model::slot_a4_result = 1;
  model::slot_a4_mutate = true;
  model::replacement_message = reinterpret_cast<OpaqueUiMessage*>(&replacement);
  model::replacement_message_id = 0x13572468u;
  message.event_type = kUiMessageOuterA4;
  message.subcommand = kUiMessageOuterA4Subvalue;
  model::expect(editor_ui_handle_message(ui_object, 7, message_object));
  model::expect_count(3);
  model::expect_event(1, model::slot_a4);
  model::expect_event(
      2, model::slot_1c4,
      static_cast<UInt32>(reinterpret_cast<unsigned int>(&replacement)),
      0x13572468u, &window);
  model::expect(load<UInt32>(&model_sink, 0x58) == 0xabcdef01u);

  model::reset();
  message.event_type = kUiMessageOuterA4;
  message.subcommand = kUiMessageOuterA4Subvalue - 1;
  model::expect(!editor_ui_handle_message(ui_object, 7, message_object));
  model::expect_count(1);

  model::reset();
  model::layout_ready_result = 0;
  model::expect(!editor_ui_handle_message(ui_object, 7, message_object));
  model::expect_count(1);
  model::reset();
  model::layout_ready_result = 1;
  store(&ui, 0x9d, static_cast<UInt8>(0));
  model::expect(!editor_ui_handle_message(ui_object, 7, message_object));
  model::expect_count(1);
  store(&ui, 0x9d, static_cast<UInt8>(1));
  store(&ui, 0x9e, static_cast<UInt8>(1));
  model::reset();
  model::expect(!editor_ui_handle_message(ui_object, 7, message_object));
  model::expect_count(1);
  store(&ui, 0x9e, static_cast<UInt8>(0));

  message.event_type = kUiMessageComponentActivated;
  message.subcommand = 0;
  model::reset();
  model::dispatch_result = 1;
  model::expect(editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(3);
  model::expect_event(0, model::layout);
  model::expect_event(1, model::message_id);
  model::expect_event(2, model::subcommand, 0x44u, 0, manager);

  model::reset();
  model::dispatch_result = 0;
  message.subcommand = kEditorUiModeZero;
  model::expect(editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(4);
  model::expect_event(2, model::subcommand, 0x44u, 0, manager);
  model::expect_event(3, model::mode, 0, 0, manager);

  model::reset();
  message.subcommand = kEditorUiModeOne;
  model::expect(editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(4);
  model::expect_event(3, model::mode, 1, 0, manager);

  model::reset();
  message.subcommand = kEditorUiModeTwo;
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(3);
  model::expect_event(2, model::subcommand, 0x44u, 0, manager);

  model::reset();
  message.subcommand = 0x12345678u;
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(3);
  model::expect_event(2, model::subcommand, 0x44u, 0, manager);

  model::reset();
  message.subcommand = kEditorUiUndo;
  model::expect(editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(5);
  model::expect_event(3, model::notify, 0xc355901au);
  model::expect_event(4, model::undo, 1, 1, editor_object);

  model::reset();
  message.subcommand = kEditorUiRedo;
  model::expect(editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(5);
  model::expect_event(3, model::notify, 0x677f1fb8u);
  model::expect_event(4, model::redo, 0, 0, editor_object);

  const UInt32 route_hashes[] = {0x447c4e8u, 0x3f67720u, 0x447b968u, 0x447b980u,
                                 0x447c040u, 0x56be960u, 0x5adbea8u};
  for (unsigned int index = 0; index < 7; ++index) {
    model::reset();
    message.subcommand = route_hashes[index];
    model::route_result = index & 1u;
    model::expect(
        editor_ui_handle_message(ui_object, 0x1234u, message_object) ==
        ((index & 1u) != 0));
    model::expect_count(4);
    model::expect_event(3, model::route, 0x1234u);
  }

  model::reset();
  message.subcommand = kEditorUiHelp;
  model::expect(editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(5);
  model::expect_event(3, model::notify, 0xa03e74b2u);
  model::expect_event(4, model::open_mode, 0, 0,
                      reinterpret_cast<const void*>(kEditorModePort));

  model::reset();
  message.subcommand = kEditorUiPreferences;
  model::preference_flags = 4;
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(8);
  model::expect(!model::reset_property_is_preferences);
  model::expect(model::reset_property_argument != nullptr);
  model::expect_event(2, model::preference_reset, 0, 0,
                      model::reset_property_argument);
  model::expect_event(3, model::preference_query, 0x087c4363u);
  model::expect_event(4, model::preference_clear, 0, 0,
                      model::events[1].object);
  model::expect_event(5, model::preference_lookup, 0x011ac192u);
  model::expect_event(6, model::preference_apply, 0x12345678u, 0,
                      preferences_object);
  model::expect_event(7, model::save, 0, 0, editor_object);
  model::expect(load<UInt8>(&ui, 0x108) == 1);

  model::reset();
  store(&ui, 0x58, static_cast<void*>(nullptr));
  message.subcommand = kEditorUiPreferences;
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(6);
  model::expect_event(4, model::preference_lookup, 0x011ac192u);
  model::expect_event(5, model::preference_apply, 0x12345678u, 0,
                      preferences_object);
  store(&ui, 0x58, static_cast<void*>(editor_object));

  model::reset();
  message.subcommand = kEditorUiPendingFlag;
  store(&ui, 0x108, static_cast<UInt8>(0));
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(3);
  model::expect(load<UInt8>(&ui, 0x108) == 1);

  store(&target, 0, static_cast<void*>(target_vtable));
  store(&secondary, 0, static_cast<void*>(secondary_vtable));
  model::reset();
  model::secondary_target = reinterpret_cast<OpaqueDispatchTarget*>(&secondary);
  message.subcommand = kEditorUiDispatchPair;
  store(&ui, 0x10c, static_cast<void*>(&target));
  model::lookup_result = reinterpret_cast<OpaqueDispatchTarget*>(&target);
  model::dispatch_pair_original = 6;
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(9);
  model::expect_event(2, model::subcommand, 0x44u, 0, manager);
  model::expect_event(3, model::lookup, 0x864a768u, 1, &target);
  model::expect_event(4, model::cast, 0, 0, &target);
  model::expect_event(5, model::target28, 0, 0, &target);
  model::expect_event(6, model::target28, 1, 1, &secondary);
  model::expect_event(7, model::target7c, 2, 1, &target);
  model::expect_event(8, model::target7c, 0x10, 1, &target);

  model::reset();
  model::lookup_result = nullptr;
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(4);
  model::expect_event(2, model::subcommand, 0x44u, 0, manager);
  model::expect_event(3, model::lookup, 0x864a768u, 1, &target);

  model::reset();
  message.event_type = kUiMessageSelectionPrefix;
  message.subcommand = kUiMessageSelectionSubvalue;
  message.payload = 9;
  model::selected_id = 9;
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(4);
  model::expect_event(1, model::selection_id);
  model::expect_event(2, model::clear_selection, 0, 0, editor_object);
  model::expect_event(3, model::set_selection, 0, 0xffffffffu, editor_object);

  model::reset();
  message.payload = 10;
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(2);

  message.event_type = 0xffffffffu;
  message.subcommand = 0;
  model::reset();
  model::expect(!editor_ui_handle_message(ui_object, 0x1234u, message_object));
  model::expect_count(1);

  return model::failures == 0;
}

}

extern "C" void* memset(void* destination, int value, unsigned long size) {
  auto* bytes = static_cast<unsigned char*>(destination);
  for (unsigned long index = 0; index < size; ++index) {
    bytes[index] = static_cast<unsigned char>(value);
  }
  return destination;
}

extern "C" void* memcpy(void* destination, const void* source,
                        unsigned long size) {
  auto* output = static_cast<unsigned char*>(destination);
  const auto* input = static_cast<const unsigned char*>(source);
  for (unsigned long index = 0; index < size; ++index) {
    output[index] = input[index];
  }
  return destination;
}

int main() {
  return openspore::reconstruction::pkg10_editor_dispatch::run() ? 0 : 1;
}
