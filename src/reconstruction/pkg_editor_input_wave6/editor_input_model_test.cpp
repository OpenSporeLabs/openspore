#include <cassert>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "editor_input.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#else
#define TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_input_wave6 {
namespace {

using namespace openspore::reconstruction::pkg_editor_input_wave6;

struct Event {
  const char* name;
  TargetWord first;
  TargetWord second;
  float x;
  float y;
  std::uint8_t result;
};

std::vector<Event>* test_events = nullptr;
bool mode_key_down_result = true;
bool selection_result = true;

void record(const char* name, TargetWord first = 0, TargetWord second = 0,
            float x = 0.0F, float y = 0.0F, std::uint8_t result = 0) {
  test_events->push_back(Event{name, first, second, x, y, result});
}

template <typename Value>
void put(OpaqueEditor* editor, std::size_t offset, Value value) {
  std::memcpy(editor->opaque + offset, &value, sizeof(value));
}

template <typename Value>
Value get(const OpaqueEditor* editor, std::size_t offset) {
  Value value{};
  std::memcpy(&value, editor->opaque + offset, sizeof(value));
  return value;
}

void TEST_THISCALL mode_mouse_down(OpaqueModeTarget*, TargetWord button,
                                   float x, float y, TargetWord state) {
  record("mode_down", button, state, x, y);
}

bool TEST_THISCALL mode_mouse_up(OpaqueModeTarget*, TargetWord button, float x,
                                 float y, TargetWord state) {
  record("mode_up", button, state, x, y, 1);
  return true;
}

void TEST_THISCALL mode_mouse_move(OpaqueModeTarget*, float x, float y,
                                   TargetWord state) {
  record("mode_move", state, 0, x, y);
}

bool TEST_THISCALL mode_key_down(OpaqueModeTarget*, TargetWord key,
                                 TargetWord modifiers) {
  record("mode_key_down", key, modifiers, 0.0F, 0.0F, 1);
  return mode_key_down_result;
}

void TEST_THISCALL mode_key_up(OpaqueModeTarget*, TargetWord key,
                               TargetWord modifiers) {
  record("mode_key_up", key, modifiers);
}

void TEST_THISCALL selection_release(OpaqueSelectionTarget*) {
  record("selection_release");
}

bool TEST_THISCALL selection_mouse_up(OpaqueSelectionTarget*, TargetWord button,
                                      float x, float y, TargetWord state) {
  record("selection_up", button, state, x, y, selection_result ? 1 : 0);
  return selection_result;
}

bool TEST_THISCALL selection_move(OpaqueSelectionTarget*, float x, float y,
                                  TargetWord state) {
  record("selection_move", state, 0, x, y, 1);
  return true;
}

TargetWord TEST_THISCALL selection_query(OpaqueSelectionTarget*) {
  record("selection_query", 0x55u);
  return 0x55u;
}

void TEST_THISCALL selection_finish(OpaqueSelectionTarget*) {
  record("selection_finish");
}

bool TEST_THISCALL selection_status(OpaqueSelectionTarget*) {
  record("selection_status", 0, 0, 0.0F, 0.0F, 1);
  return true;
}

struct TestHooks : OpaqueInputHooks {
  std::vector<Event> events;
  bool wheel_result = true;
  bool graphics = true;
  bool path_ready = false;

  void game_key_down(void*, TargetWord key, TargetWord modifiers) override {
    record("game_key_down", key, modifiers);
  }

  void game_key_up(void*, TargetWord key, TargetWord modifiers) override {
    record("game_key_up", key, modifiers);
  }

  void state_refresh(OpaqueEditor*) override { record("refresh"); }

  std::uint8_t dispatch_wheel(OpaqueEditor*, TargetWord delta, float x, float y,
                              TargetWord state, TargetWord extra) override {
    record("wheel", delta, extra, x, y, static_cast<std::uint8_t>(state));
    return wheel_result ? 1 : 0;
  }

  bool graphics_available() const override { return graphics; }

  bool key_path_ready(TargetWord key) const override {
    return path_ready && key == 0x0d;
  }

  bool mouse_down_tail(OpaqueEditor*, TargetWord button, float x, float y,
                       TargetWord state) override {
    record("mouse_down_tail", button, state, x, y, 1);
    return true;
  }

  void mouse_up_simple(OpaqueEditor*, TargetWord button, float x, float y,
                       TargetWord state) override {
    record("mouse_up_simple", button, state, x, y);
  }

  void mouse_up_cleanup(OpaqueEditor*, TargetWord button, std::uint8_t result,
                        std::uint8_t status) override {
    record("mouse_up_cleanup", button, status, 0.0F, 0.0F, result);
  }

  void selection_side_effect(OpaqueSelectionTarget*,
                             TargetWord value) override {
    record("selection_side_effect", value);
  }

  void key_path(OpaqueEditor*, TargetWord key, TargetWord token) override {
    record("key_path", key, token);
  }

  void key_command(OpaqueEditor*, TargetWord key, TargetWord command) override {
    record("key_command", key, command);
  }

  void key_undo_redo(OpaqueEditor*, TargetWord key) override {
    record("key_undo_redo", key);
  }

  void key_external_path(OpaqueEditor*, TargetWord key) override {
    record("key_external_path", key);
  }
};

void reset_editor(OpaqueEditor& editor, TargetWord mode_value,
                  OpaqueModeTarget* mode_target,
                  OpaqueSelectionTarget* selection) {
  editor = OpaqueEditor{};
  put(&editor, 0x31c, mode_value);
  put(&editor, 0x7c, mode_target);
  put(&editor, 0x148, selection);
}

void test_mouse_move() {
  OpaqueEditor editor{};
  OpaqueModeTarget mode_target{};
  OpaqueModeVtable mode_vtable{};
  mode_vtable.mouse_move_18 = mode_mouse_move;
  mode_target.vtable = &mode_vtable;
  reset_editor(editor, 2, &mode_target, nullptr);

  assert(!editor_input_005737d0(&editor, 1.5F, 2.5F, 0x38));
  assert(get<float>(&editor, 0x28) == 1.5F);
  assert(get<float>(&editor, 0x2c) == 2.5F);
  assert(get<TargetWord>(&editor, 0x30) == 0x38u);
  assert(get<std::uint8_t>(&editor, 0x38) == 1);
  assert(test_events->size() == 1);
  assert((*test_events)[0].name == std::string("mode_move"));

  OpaqueSelectionTarget selection_target{};
  OpaqueSelectionVtable selection_vtable{};
  selection_vtable.mouse_move_1c = selection_move;
  selection_vtable.query_28 = selection_query;
  selection_target.vtable = &selection_vtable;
  reset_editor(editor, 0, &mode_target, &selection_target);
  test_events->clear();
  assert(editor_input_005737d0(&editor, 2.0F, 3.0F, 0));
  assert(test_events->size() == 3);
  assert((*test_events)[0].name == std::string("selection_move"));
  assert((*test_events)[1].name == std::string("selection_query"));
  assert((*test_events)[2].name == std::string("selection_side_effect"));
}

void test_key_up() {
  test_events->clear();
  OpaqueEditor editor{};
  OpaqueModeTarget mode_target{};
  OpaqueModeVtable mode_vtable{};
  mode_vtable.key_up_20 = mode_key_up;
  mode_target.vtable = &mode_vtable;
  reset_editor(editor, 2, &mode_target, nullptr);

  assert(!editor_input_00585890(&editor, 0x11, 7));
  assert(get<TargetWord>(&editor, 0x30) == 0);
  assert(test_events->size() == 4);
  assert((*test_events)[0].name == std::string("game_key_up"));
  assert((*test_events)[1].name == std::string("refresh"));
  assert((*test_events)[2].name == std::string("mode_key_up"));
  assert((*test_events)[3].name == std::string("refresh"));

  test_events->clear();
  assert(!editor_input_00585890(&editor, 0x22, 0x10));
  assert(get<TargetWord>(&editor, 0x30) == 0x22u);
  assert(test_events->size() == 4);

  test_events->clear();
  assert(!editor_input_00585890(&editor, 0x23, 0x12));
  assert(get<TargetWord>(&editor, 0x30) == 0x23u);
  assert(test_events->size() == 4);

  test_events->clear();
  assert(!editor_input_00585890(&editor, 0x24, 0x13));
  assert(get<TargetWord>(&editor, 0x30) == 0x23u);
  assert(test_events->size() == 4);
}

void test_wheel() {
  test_events->clear();
  OpaqueEditor editor{};
  OpaqueModeTarget mode_target{};
  reset_editor(editor, 0, &mode_target, nullptr);

  assert(editor_input_00585d10(&editor, 0x78, 3.0F, 4.0F, 9));
  assert(test_events->size() == 1);
  assert((*test_events)[0].name == std::string("wheel"));
  assert((*test_events)[0].first == 0x78u);
}

void test_mouse_down() {
  test_events->clear();
  OpaqueEditor editor{};
  OpaqueModeTarget mode_target{};
  OpaqueModeVtable mode_vtable{};
  mode_vtable.mouse_down_10 = mode_mouse_down;
  mode_target.vtable = &mode_vtable;
  reset_editor(editor, 2, &mode_target, nullptr);
  put(&editor, 0x84, 1u);

  assert(editor_input_00588570(&editor, 0x3e8, 1.0F, 2.0F, 3));
  assert(get<TargetWord>(&editor, 0x34) == 0x3e8u);
  assert(test_events->size() == 2);
  assert((*test_events)[0].name == std::string("mode_down"));
  assert((*test_events)[1].name == std::string("mouse_down_tail"));

  reset_editor(editor, 0, nullptr, nullptr);
  test_events->clear();
  assert(!editor_input_00588570(&editor, 0x3e9, 1.0F, 2.0F, 3));
  assert(get<TargetWord>(&editor, 0x34) == 0x3e9u);
  assert(get<std::uint8_t>(&editor, 0x2b4) == 1);
  assert(test_events->empty());
}

void test_mouse_up() {
  test_events->clear();
  OpaqueEditor editor{};
  OpaqueModeTarget mode_target{};
  OpaqueSelectionTarget selection_target{};
  OpaqueSelectionVtable selection_vtable{};
  selection_vtable.mouse_up_10 = selection_mouse_up;
  selection_vtable.query_28 = selection_query;
  selection_vtable.finish_30 = selection_finish;
  selection_vtable.status_34 = selection_status;
  selection_vtable.release_04 = selection_release;
  selection_target.vtable = &selection_vtable;
  reset_editor(editor, 0, &mode_target, &selection_target);
  put(&editor, 0xd0, 1u);
  put(&editor, 0x34, 0x3e8u);

  assert(editor_input_0058b650(&editor, 0x3e8, 5.0F, 6.0F, 7));
  assert(get<TargetWord>(&editor, 0x34) == 0);
  assert(test_events->size() == 6);
  assert((*test_events)[0].name == std::string("selection_up"));
  assert((*test_events)[1].name == std::string("selection_status"));
  assert((*test_events)[2].name == std::string("selection_side_effect"));
  assert((*test_events)[3].name == std::string("selection_finish"));
  assert((*test_events)[4].name == std::string("selection_release"));
  assert((*test_events)[5].name == std::string("mouse_up_cleanup"));

  reset_editor(editor, 0, nullptr, nullptr);
  put(&editor, 0x34, 0x3e8u);
  test_events->clear();
  assert(!editor_input_0058b650(&editor, 0x3e8, 1.0F, 2.0F, 3));
  assert(get<TargetWord>(&editor, 0x34) == 0);
  assert(get<std::uint8_t>(&editor, 0x2b3) == 1);
  assert(test_events->size() == 1);
  assert((*test_events)[0].name == std::string("mouse_up_simple"));

  OpaqueModeVtable mode_vtable{};
  mode_vtable.mouse_up_14 = mode_mouse_up;
  mode_target.vtable = &mode_vtable;
  reset_editor(editor, 2, &mode_target, nullptr);
  put(&editor, 0x34, 0x3e8u);
  test_events->clear();
  assert(!editor_input_0058b650(&editor, 0x3e8, 1.0F, 2.0F, 3));
  assert(test_events->size() == 1);
  assert((*test_events)[0].name == std::string("mode_up"));
}

void test_key_down_original_branches() {
  const TargetWord keys[] = {0x42, 0x46, 0x48, 0x4e, 0x53, 0xbf};
  OpaqueEditor editor{};

  for (TargetWord key : keys) {
    reset_editor(editor, 0, nullptr, nullptr);
    test_events->clear();
    assert(!editor_input_0058ac10(&editor, key, 0));
    assert(test_events->size() == 3);
  }
}

void test_key_down() {
  test_events->clear();
  OpaqueEditor editor{};
  OpaqueModeTarget mode_target{};
  reset_editor(editor, 0, &mode_target, nullptr);
  put(&editor, 0x3c, 1u);

  assert(editor_input_0058ac10(&editor, 0x31, 0));
  assert(test_events->size() == 4);
  assert((*test_events)[3].name == std::string("key_command"));
  assert((*test_events)[3].second == 0x13u);

  test_events->clear();
  assert(!editor_input_0058ac10(&editor, 0x11, 0));
  assert(get<TargetWord>(&editor, 0x30) == 0x11u);
  assert(test_events->size() == 3);

  OpaqueModeVtable mode_vtable{};
  mode_vtable.key_down_1c = mode_key_down;
  mode_target.vtable = &mode_vtable;
  reset_editor(editor, 2, &mode_target, nullptr);
  test_events->clear();
  assert(editor_input_0058ac10(&editor, 0x20, 3));
  assert(test_events->size() == 4);
  assert((*test_events)[3].name == std::string("mode_key_down"));
}

}

int run_tests() {
  TestHooks hooks;
  test_events = &hooks.events;
  g_input_hooks = &hooks;
  test_mouse_move();
  test_key_up();
  test_wheel();
  test_mouse_down();
  test_mouse_up();
  test_key_down_original_branches();
  test_key_down();
  g_input_hooks = nullptr;
  test_events = nullptr;
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_editor_input_wave6::run_tests();
}

#undef TEST_THISCALL
