#include "editor_ui_paint_toggle_publish.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

namespace {

using openspore::reconstruction::wave13_w1_dispatch_b03::OpaqueEditorUi;

struct Call {
  int selector;
  int state;
};

std::vector<Call> g_calls;
int g_classify_calls = 0;
int g_main_lookups = 0;
int g_shared_lookups = 0;
bool g_main_has_element = true;
bool g_shared_has_element = true;
bool g_main_ui_present = true;
int g_tail_calls = 0;
const void* g_main_ctx = nullptr;
const void* g_shared_ctx = nullptr;
void* g_main_provider = reinterpret_cast<void*>(0x1000);
void* g_shared_provider = reinterpret_cast<void*>(0x2000);
void* g_used_provider = nullptr;

int failures = 0;

void expect(bool condition, const char* what) {
  if (!condition) {
    std::printf("FAIL %s\n", what);
    ++failures;
  }
}

void reset() {
  g_calls.clear();
  g_classify_calls = 0;
  g_main_lookups = 0;
  g_shared_lookups = 0;
  g_main_has_element = true;
  g_shared_has_element = true;
  g_main_ui_present = true;
  g_tail_calls = 0;
  g_used_provider = nullptr;
}

}  // namespace

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// The classification the fake hands back; the test sets it per case.
int g_fake_mode = 0;

namespace unresolved_ports {

int __fastcall classify_paint_availability(void*) {
  ++g_classify_calls;
  return g_fake_mode;
}

void* __thiscall layout_find_element(OpaqueUiLayout* context, unsigned int id,
                                    int mode) {
  if (id != 0x5b6e484u || mode != 1) {
    std::printf("FAIL unexpected lookup id/mode\n");
    ++failures;
  }
  if (context == nullptr) {
    std::printf("FAIL null layout context\n");
    ++failures;
    return nullptr;
  }
  // The first context is mMainUI, the second mSharedUI. The test tells them
  // apart by a sentinel pointer installed below.
  if (context == g_main_ctx) {
    ++g_main_lookups;
    return g_main_has_element ? g_main_provider : nullptr;
  }
  ++g_shared_lookups;
  return g_shared_has_element ? g_shared_provider : nullptr;
}

void __thiscall provider_set_toggle(void* provider, int selector, int state) {
  g_used_provider = provider;
  g_calls.push_back(Call{selector, state});
}

void __fastcall editor_ui_publish_undo_state_005dc800(OpaqueEditorUi*) {
  ++g_tail_calls;
}

}  // namespace unresolved_ports

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03

int main() {
  using namespace openspore::reconstruction::wave13_w1_dispatch_b03;

  OpaqueEditorUi ui;
  std::memset(&ui, 0, sizeof(ui));
  g_main_ctx = &ui.mMainUI;
  g_shared_ctx = &ui.mSharedUI;
  ui.mpEditor = reinterpret_cast<void*>(&ui);
  ui.field_D1 = 1;
  ui.field_102 = 1;
  ui.field_104 = 1;

  // Case 1: field_102 set, classification 0. Both flags 1, provider is mMainUI.
  reset();
  g_fake_mode = 0;
  editor_ui_publish_paint_toggle_005dd7a0(&ui);
  expect(g_calls.size() == 2, "mode 0: two toggle calls");
  expect(g_calls[0].selector == 1 && g_calls[0].state == 1, "mode 0: (1,1)");
  expect(g_calls[1].selector == 2 && g_calls[1].state == 1, "mode 0: (2,1)");
  expect(g_used_provider == g_main_provider, "mode 0: mMainUI provider used");
  expect(g_shared_lookups == 0, "mode 0: mSharedUI never consulted");
  expect(g_tail_calls == 1, "mode 0: tail target entered once");

  // Case 2: classification 1 and 2 also set the second flag.
  for (int mode : {1, 2}) {
    reset();
    g_fake_mode = mode;
    editor_ui_publish_paint_toggle_005dd7a0(&ui);
    expect(g_calls.size() == 2, "modes 1-2: two toggle calls");
    expect(g_calls[1].state == 1, "modes 1-2: second flag is 1");
    expect(g_calls[0].state == 1, "modes 1-2: first flag is 1");
  }

  // Case 3: classifications 3 and 4 clear the second flag but keep the first.
  for (int mode : {3, 4}) {
    reset();
    g_fake_mode = mode;
    editor_ui_publish_paint_toggle_005dd7a0(&ui);
    expect(g_calls[0].state == 1, "modes 3-4: first flag stays 1");
    expect(g_calls[1].state == 0, "modes 3-4: second flag is 0");
  }

  // Case 4: a classification outside 0..4 makes the bounds check skip the
  // table entirely, so both flags stay 0.
  reset();
  g_fake_mode = 5;
  editor_ui_publish_paint_toggle_005dd7a0(&ui);
  expect(g_calls[0].state == 0, "mode 5: first flag stays 0");
  expect(g_calls[1].state == 0, "mode 5: second flag stays 0");
  reset();
  g_fake_mode = -1;
  editor_ui_publish_paint_toggle_005dd7a0(&ui);
  expect(g_calls[0].state == 0, "mode -1: the unsigned bounds check skips too");
  expect(g_calls[1].state == 0, "mode -1: second flag stays 0");

  // Case 5: field_102 clear bypasses the whole switch, whatever the mode.
  reset();
  ui.field_102 = 0;
  g_fake_mode = 0;
  editor_ui_publish_paint_toggle_005dd7a0(&ui);
  expect(g_calls[0].state == 0, "field_102 clear: first flag stays 0");
  expect(g_calls[1].state == 0, "field_102 clear: second flag stays 0");
  ui.field_102 = 1;

  // Case 6: field_D1 clear can only clear the second flag.
  reset();
  ui.field_D1 = 0;
  g_fake_mode = 0;
  editor_ui_publish_paint_toggle_005dd7a0(&ui);
  expect(g_calls[0].state == 1, "field_D1 clear: first flag unaffected");
  expect(g_calls[1].state == 0, "field_D1 clear: second flag forced to 0");
  ui.field_D1 = 1;

  // Case 7: mMainUI misses the element, mSharedUI has it.
  reset();
  g_main_has_element = false;
  g_fake_mode = 0;
  editor_ui_publish_paint_toggle_005dd7a0(&ui);
  expect(g_main_lookups == 1 && g_shared_lookups == 1,
         "fallback: both layouts consulted once");
  expect(g_used_provider == g_shared_provider,
         "fallback: the mSharedUI provider is used");

  // Case 8: neither layout has the element. No toggle calls at all, but the
  // tail target is still entered.
  reset();
  g_main_has_element = false;
  g_shared_has_element = false;
  g_fake_mode = 0;
  editor_ui_publish_paint_toggle_005dd7a0(&ui);
  expect(g_calls.empty(), "no provider: no toggle calls");
  expect(g_tail_calls == 1, "no provider: the tail target still runs");

  if (failures == 0) {
    std::printf("005dd7a0 model test: all cases passed\n");
    return 0;
  }
  std::printf("005dd7a0 model test: %d failure(s)\n", failures);
  return 1;
}
