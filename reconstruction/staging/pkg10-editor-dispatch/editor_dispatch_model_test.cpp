#include "editor_dispatch.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <vector>

namespace openspore::reconstruction::pkg10_editor_dispatch {

struct OpaqueEditor {};
struct OpaqueEditorModeTarget;
struct OpaqueEditorModeManager;

struct OpaqueEditorModeTarget {
  EditorModeTargetSlot7C *vtable;
};

struct OpaqueEditorModeManager {
  std::array<std::uint8_t, 0x90> bytes{};
};

namespace model {

enum class EventKind : std::uint8_t {
  guard,
  editor,
  notify,
  lighting,
  slot,
  lookup,
  raw_lookup,
  target_state,
  raw_apply,
  raw_set,
  selector,
};

struct Event {
  EventKind kind;
  std::uint32_t first = 0;
  std::uint32_t second = 0;

  bool operator==(const Event &other) const {
    return kind == other.kind && first == other.first && second == other.second;
  }
};

std::vector<Event> events;
bool mode2_guard_result = true;
bool editor_set_active_mode_result = true;
OpaqueEditor *expected_guard_editor = nullptr;
OpaqueEditor *expected_selector_editor = nullptr;
std::uint32_t selector_lookup_key = 0;
void *selector_lookup_result = nullptr;
void *raw_lookup_result = nullptr;
void *expected_raw_lookup_object = nullptr;
void *expected_raw_state_object = nullptr;

void reset() { events.clear(); }

void add(EventKind kind, std::uint32_t first = 0, std::uint32_t second = 0) {
  events.push_back(Event{kind, first, second});
}

} // namespace model

namespace unresolved_contracts {

void *__thiscall mode2_guard(OpaqueEditor *editor, std::uint32_t selector) {
  assert(editor == model::expected_guard_editor);
  model::add(model::EventKind::guard, selector);
  return model::mode2_guard_result ? reinterpret_cast<void *>(std::uintptr_t{1})
                                   : nullptr;
}

void editor_mode_notify(std::uint32_t key) {
  model::add(model::EventKind::notify, key);
}

void *__thiscall raw_manager_lookup(void *object, std::uint32_t key,
                                    std::uint32_t flag) {
  assert(object == model::expected_raw_lookup_object);
  model::add(model::EventKind::raw_lookup, key, flag);
  return model::raw_lookup_result;
}

std::uint8_t __thiscall raw_manager_set_state(void *object,
                                              std::uint32_t state) {
  assert(object == model::expected_raw_state_object);
  model::add(model::EventKind::raw_set, state);
  return 0;
}

std::uint8_t __thiscall raw_manager_apply_state(void *object, void *value,
                                                std::uint32_t first,
                                                std::uint32_t second) {
  assert(object == model::expected_raw_state_object);
  assert(value == model::raw_lookup_result);
  model::add(model::EventKind::raw_apply, first, second);
  return 0;
}

std::uint8_t __thiscall target_selector(OpaqueEditor *editor) {
  assert(editor == model::expected_selector_editor);
  model::add(model::EventKind::selector, 0, 0x2a);
  return 0x2a;
}

} // namespace unresolved_contracts

bool __thiscall editor_set_active_mode(OpaqueEditor *, std::uint32_t mode,
                                       std::uint32_t flag) {
  model::add(model::EventKind::editor, static_cast<std::uint32_t>(mode), flag);
  return model::editor_set_active_mode_result;
}

void __thiscall editor_mode_manager_set_lighting(OpaqueEditorModeManager *,
                                                 std::uint32_t state) {
  model::add(model::EventKind::lighting, state);
}

void *__thiscall editor_mode_manager_lookup_target(OpaqueEditorModeManager *,
                                                   std::uint32_t key) {
  model::add(model::EventKind::lookup, key);
  return key == model::selector_lookup_key ? model::selector_lookup_result
                                           : nullptr;
}

void __thiscall
editor_mode_manager_apply_target_state(OpaqueEditorModeManager *,
                                       std::uint32_t key, std::uint32_t first,
                                       std::uint32_t second) {
  model::add(model::EventKind::target_state, key, first);
  assert(second == 1);
}

void __thiscall target_slot(OpaqueEditorModeTarget *, std::uint32_t first,
                            std::uint32_t second) {
  model::add(model::EventKind::slot, first, second);
}

template <typename Value>
void store(void *object, std::uintptr_t offset, Value value) {
  std::memcpy(static_cast<std::uint8_t *>(object) + offset, &value,
              sizeof(value));
}

template <typename Value>
Value load(const void *object, std::uintptr_t offset) {
  Value value;
  std::memcpy(&value, static_cast<const std::uint8_t *>(object) + offset,
              sizeof(value));
  return value;
}

void run() {
  OpaqueEditor editor;
  OpaqueEditorModeManager manager;
  std::array<EditorModeTargetSlot7C, 32> vtable{};
  vtable[kEditorModeTargetVtableSlot] = target_slot;
  OpaqueEditorModeTarget target{&vtable[0]};

  store<OpaqueEditor *>(&manager, 0x5c, &editor);
  store<OpaqueEditorModeTarget *>(&manager, 0x64, &target);
  store<OpaqueEditorModeTarget *>(&manager, 0x68, &target);
  store<OpaqueEditorModeTarget *>(&manager, 0x6c, &target);
  store<OpaqueEditorModeTarget *>(&manager, 0x80, &target);
  store<OpaqueEditorModeTarget *>(&manager, 0x84, &target);
  assert(load<OpaqueEditorModeTarget *>(&manager, 0x68) == &target);
  assert(load<EditorModeTargetSlot7C *>(&target, 0) == &vtable[0]);

  model::expected_guard_editor = &editor;
  model::expected_raw_lookup_object =
      reinterpret_cast<std::uint8_t *>(&manager) + 0x14;
  model::expected_raw_state_object =
      reinterpret_cast<std::uint8_t *>(&manager) + 0x44;

  store<std::uint32_t>(&manager, 0x60, 2);
  model::reset();
  model::mode2_guard_result = false;
  editor_mode_manager_set_active_mode(&manager, 2);
  assert(model::events.size() == 1);
  assert(model::events[0] == (model::Event{model::EventKind::guard, 0, 0}));

  store<std::uint32_t>(&manager, 0x60, 1);
  model::reset();
  model::mode2_guard_result = true;
  editor_mode_manager_set_active_mode(&manager, 1);
  assert(model::events.empty());

  model::editor_set_active_mode_result = false;
  store<std::uint32_t>(&manager, 0x60, 3);
  model::reset();
  editor_mode_manager_set_active_mode(&manager, 1);
  assert(model::events == (std::vector<model::Event>{
                              {model::EventKind::editor, 1, 0},
                          }));
  assert(load<std::uint32_t>(&manager, 0x60) == 3);
  model::editor_set_active_mode_result = true;

  model::raw_lookup_result = nullptr;
  model::selector_lookup_key = 0;
  model::selector_lookup_result = nullptr;
  model::expected_selector_editor = nullptr;
  store<std::uint32_t>(&manager, 0x60, 0);
  model::reset();
  editor_mode_manager_set_active_mode(&manager, 1);
  assert(model::events == (std::vector<model::Event>{
                              {model::EventKind::editor, 1, 0},
                              {model::EventKind::notify, 0x8c35f293u, 0},
                              {model::EventKind::lighting, 0, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::slot, 1, 1},
                              {model::EventKind::raw_lookup, 0x4fcc581u, 1},
                              {model::EventKind::raw_set, 0, 0},
                          }));
  assert(load<std::uint32_t>(&manager, 0x60) == 1);

  store<std::uint32_t>(&manager, 0x60, 1);
  model::reset();
  editor_mode_manager_set_active_mode(&manager, 2);
  assert(model::events == (std::vector<model::Event>{
                              {model::EventKind::guard, 0, 0},
                              {model::EventKind::editor, 2, 0},
                              {model::EventKind::notify, 0x8c35f293u, 0},
                              {model::EventKind::lighting, 0, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::lookup, 0x578ec50u, 0},
                              {model::EventKind::lookup, 0xf006efa5u, 0},
                              {model::EventKind::lookup, 0xb006ef6eu, 0},
                              {model::EventKind::lookup, 0x1140129du, 0},
                          }));
  assert(load<std::uint32_t>(&manager, 0x60) == 2);

  model::selector_lookup_key = 0x1140129du;
  model::selector_lookup_result = &target;
  model::expected_selector_editor = &editor;
  model::raw_lookup_result = nullptr;
  store<std::uint32_t>(&manager, 0x60, 2);
  model::reset();
  editor_mode_manager_set_active_mode(&manager, 0);
  assert(model::events == (std::vector<model::Event>{
                              {model::EventKind::editor, 0, 0},
                              {model::EventKind::notify, 0x8c35f293u, 0},
                              {model::EventKind::lighting, 0, 0},
                              {model::EventKind::slot, 1, 1},
                              {model::EventKind::lookup, 0x578ec50u, 0},
                              {model::EventKind::lookup, 0xf006efa5u, 0},
                              {model::EventKind::lookup, 0xb006ef6eu, 0},
                              {model::EventKind::lookup, 0x1140129du, 0},
                              {model::EventKind::selector, 0, 0x2a},
                              {model::EventKind::slot, 1, 0x2a},
                              {model::EventKind::slot, 1, 1},
                              {model::EventKind::lookup, 0x578ec50u, 0},
                              {model::EventKind::lookup, 0xf006efa5u, 0},
                              {model::EventKind::lookup, 0xb006ef6eu, 0},
                              {model::EventKind::slot, 1, 1},
                              {model::EventKind::slot, 1, 1},
                              {model::EventKind::raw_lookup, 0x4fcc580u, 1},
                              {model::EventKind::target_state, 0xf019c2e7u, 1},
                              {model::EventKind::raw_set, 0, 0},
                          }));
  assert(load<std::uint32_t>(&manager, 0x60) == 0);

  model::selector_lookup_key = 0;
  model::selector_lookup_result = nullptr;
  model::expected_selector_editor = nullptr;
  model::raw_lookup_result = &target;
  store<std::uint32_t>(&manager, 0x60, 3);
  model::reset();
  editor_mode_manager_set_active_mode(&manager, 0);
  assert(model::events == (std::vector<model::Event>{
                              {model::EventKind::editor, 0, 0},
                              {model::EventKind::notify, 0x8c35f293u, 0},
                              {model::EventKind::lighting, 0, 0},
                              {model::EventKind::slot, 1, 1},
                              {model::EventKind::lookup, 0x578ec50u, 0},
                              {model::EventKind::lookup, 0xf006efa5u, 0},
                              {model::EventKind::lookup, 0xb006ef6eu, 0},
                              {model::EventKind::slot, 1, 1},
                              {model::EventKind::slot, 1, 1},
                              {model::EventKind::raw_lookup, 0x4fcc580u, 1},
                              {model::EventKind::target_state, 0xf019c2e7u, 1},
                              {model::EventKind::raw_apply, 1, 0x5b598fau},
                              {model::EventKind::raw_set, 1, 0},
                          }));
  assert(load<std::uint32_t>(&manager, 0x60) == 0);

  model::raw_lookup_result = nullptr;
  store<std::uint32_t>(&manager, 0x60, 0);
  model::reset();
  editor_mode_manager_set_active_mode(&manager, 3);
  assert(model::events == (std::vector<model::Event>{
                              {model::EventKind::editor, 3, 0},
                              {model::EventKind::notify, 0x8c35f293u, 0},
                              {model::EventKind::lighting, 0, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::raw_set, 0, 0},
                          }));
  assert(load<std::uint32_t>(&manager, 0x60) == 3);

  model::raw_lookup_result = nullptr;
  store<std::uint32_t>(&manager, 0x60, 0);
  model::reset();
  editor_mode_manager_set_active_mode(&manager, UINT32_MAX);
  assert(model::events == (std::vector<model::Event>{
                              {model::EventKind::editor, UINT32_MAX, 0},
                              {model::EventKind::notify, 0x8c35f293u, 0},
                              {model::EventKind::lighting, 0, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::slot, 1, 0},
                              {model::EventKind::raw_set, 0, 0},
                          }));
  assert(load<std::uint32_t>(&manager, 0x60) == UINT32_MAX);
}

} // namespace openspore::reconstruction::pkg10_editor_dispatch

int main() { openspore::reconstruction::pkg10_editor_dispatch::run(); }
