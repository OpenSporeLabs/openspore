// Standalone model test for the reconstruction of SporeApp.exe 0x00635760.
// Build:
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror -I <dir> \
//       utfwin_00635760.cpp utfwin_00635760_model_test.cpp \
//       -o /tmp/opencode/00635760-model && /tmp/opencode/00635760-model
//
// Scope note: the byte-exact body in utfwin_00635760.cpp is a naked __thiscall
// function. Linux i386 clang has no __thiscall, so this test enters it through
// UtfWin_00635760_host_bridge, which stages the original register and stack
// layout and then calls it. The bridge is a host shim and is not part of the
// reconstructed body.

#include "utfwin_00635760.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace openspore::reconstruction::wave13_pilot_dispatch_b00;

namespace {

// ---------------------------------------------------------------------------
// Test double for the single direct callee 0x00634dc0. It reproduces the two
// questions 0x00634dc0 asks the window interface: GetControlID() at +0x1C and
// FindWindowByID(id, true) at +0xF0. It is a port double, not a reconstruction
// of 0x00634dc0.
// ---------------------------------------------------------------------------
struct WindowEntry {
  OpaqueUtfWinWindow window;
  std::uint32_t control_id;
  const char *tag;
};

std::vector<WindowEntry> *g_windows = nullptr;
int g_dispatch_count = 0;
std::uint32_t g_last_flag = 0u;
bool g_last_value = false;
const char *g_last_window = nullptr;
int failures = 0;

// Registry stand-in: only +0x14 is claimed, so the vector pair goes there.
struct RegistryImage {
  std::uint32_t pad_before_14[5];
  std::uint32_t begin;
  std::uint32_t end;
};

std::uint32_t test_get_control_id(const void *self) {
  return reinterpret_cast<const WindowEntry *>(self)->control_id;
}

void *test_find_window_by_id(void *, std::uint32_t control_id, bool recursive) {
  if (!recursive) {
    std::printf("FAIL: 0x00634dc0 always passes bRecursive = true\n");
    std::exit(1);
  }
  for (auto &candidate : *g_windows) {
    if (candidate.control_id == control_id) {
      return &candidate.window;
    }
  }
  return nullptr;
}

void *test_get_object_by_type(void *, std::uint32_t type) {
  if (type != 0xEEEE8218u) { // UTFWin::IWindow::TYPE
    std::printf("FAIL: type id was 0x%08X\n", type);
    std::exit(1);
  }
  return &g_windows->front().window;
}

void test_set_flag(void *self, UtfWinWindowFlag flag, bool value) {
  ++g_dispatch_count;
  g_last_flag = static_cast<std::uint32_t>(flag);
  g_last_value = value;
  g_last_window = reinterpret_cast<WindowEntry *>(self)->tag;
  std::printf("  -> SetFlag(window=%s, flag=0x%X, value=%d)\n", g_last_window,
              g_last_flag, value ? 1 : 0);
}

// The +0x7C target reached by the tail transfer at 0x0063577d. It inherits the
// caller's frame, so the two words below the return address are its flag and
// value arguments and it must pop them itself: the observed RET 0x8 shape.
__attribute__((naked)) void tail_set_flag(void *, UtfWinWindowFlag, bool) {
  // On entry: ECX = window, 4(%esp) = flag (written by 0x00635773), 8(%esp) =
  // value, 0(%esp) = the original return address.
  __asm__("pushl 8(%esp)\n\t" // value
          "pushl 8(%esp)\n\t" // flag
          "pushl %ecx\n\t"    // window
          "call record_set_flag\n\t"
          "addl $12, %esp\n\t" // record_set_flag is cdecl
          "ret $8\n\t");
}

OpaqueUtfWinWindowVtable *make_vtable() {
  static OpaqueUtfWinWindowVtable table;
  std::memset(&table, 0, sizeof(table));
  table.get_object_by_type = &test_get_object_by_type;
  table.get_control_id = &test_get_control_id;
  table.set_flag = &tail_set_flag;
  table.find_window_by_id = &test_find_window_by_id;
  return &table;
}

void reset_counters() {
  g_dispatch_count = 0;
  g_last_flag = 0u;
  g_last_value = false;
  g_last_window = nullptr;
}

void expect(bool condition, const char *what) {
  if (!condition) {
    std::printf("FAIL: %s\n", what);
    ++failures;
  }
}

} // namespace

// The port: the only direct callee of the reconstructed body. The original
// 0x00634dc0 is __thiscall, so the receiver arrives in ECX.
extern "C" __attribute__((naked)) OpaqueUtfWinWindow *
utfwin_registry_find_window_by_control_id(OpaqueUtfWinRootRegistry *,
                                          std::uint32_t) {
  __asm__(
      "pushl %ecx\n\t"    // registry ; stack: REG | RET | ID
      "pushl 8(%esp)\n\t" // control id ; stack: ID | REG | RET | ID
      "call utfwin_find_window_helper\n\t"
      // The helper's RET already consumed the CALL's return address, so only
      // the stub's own two pushed words have to be discarded before the RET 4.
      "addl $8, %esp\n\t"
      "ret $4\n\t"); // RET 0x4, exactly like the original callee
}

extern "C" void *utfwin_find_window_helper(std::uint32_t control_id,
                                           void *registry_object) {
  auto *image = reinterpret_cast<RegistryImage *>(registry_object);
  const std::uint32_t count = (image->end - image->begin) / 4u;
  if (count == 0u) {
    return nullptr; // 0x00634dc0 returns null for an empty vector
  }
  for (auto &candidate : *g_windows) {
    if (test_get_control_id(&candidate) == control_id) {
      return &candidate.window;
    }
  }
  for (auto &candidate : *g_windows) {
    void *found = test_find_window_by_id(&candidate.window, control_id, true);
    if (found != nullptr) {
      return found;
    }
  }
  return nullptr;
}

int main() {
  std::setvbuf(stdout, nullptr, _IONBF, 0);
  std::vector<WindowEntry> windows;
  OpaqueUtfWinWindowVtable *vtable = make_vtable();
  windows.push_back({{vtable}, 0x00406678u, "root"});
  windows.push_back({{vtable}, 0x040666B8u, "child"});
  g_windows = &windows;

  RegistryImage image{};
  image.begin = 1u;
  image.end = 1u + 4u; // one element, matching vector<ptr> count arithmetic
  auto *registry = reinterpret_cast<OpaqueUtfWinRootRegistry *>(&image);

  std::printf("case 1: hide a known control id (visible=false)\n");
  reset_counters();
  UtfWin_00635760_set_flag_by_control_id(registry, 0x00406678u, false);
  expect(g_dispatch_count == 1, "case 1 dispatched exactly once");
  expect(g_last_flag == 0x1u, "case 1 used kWinFlagVisible (0x1)");
  expect(g_last_value == false, "case 1 forwarded the boolean unchanged");
  expect(std::strcmp(g_last_window, "root") == 0, "case 1 found the root");

  std::printf("case 2: show a known control id (visible=true)\n");
  reset_counters();
  UtfWin_00635760_set_flag_by_control_id(registry, 0x040666B8u, true);
  expect(g_dispatch_count == 1, "case 2 dispatched exactly once");
  expect(g_last_flag == 0x1u, "case 2 used kWinFlagVisible (0x1)");
  expect(g_last_value == true, "case 2 forwarded true unchanged");
  expect(std::strcmp(g_last_window, "child") == 0, "case 2 found the child");

  std::printf("case 3: unknown control id -> no dispatch\n");
  reset_counters();
  UtfWin_00635760_set_flag_by_control_id(registry, 0xDEADBEEFu, true);
  expect(g_dispatch_count == 0, "case 3 performed no SetFlag");

  std::printf("case 4: empty registry -> no dispatch\n");
  image.begin = 0u;
  image.end = 0u;
  reset_counters();
  UtfWin_00635760_set_flag_by_control_id(registry, 0x00406678u, true);
  expect(g_dispatch_count == 0, "case 4 performed no SetFlag");

  std::printf("case 5: the set_visible alias agrees\n");
  image.begin = 1u;
  image.end = 1u + 4u;
  reset_counters();
  UtfWin_00635760_set_visible_by_control_id(registry, 0x040666B8u, true);
  expect(g_dispatch_count == 1 && g_last_flag == 0x1u && g_last_value,
         "case 5 forwarded show to the child window");

  if (failures != 0) {
    std::printf("%d FAILURE(S)\n", failures);
    return 1;
  }
  std::printf("OK\n");
  return 0;
}

extern "C" void record_set_flag(void *self, UtfWinWindowFlag flag, bool value) {
  test_set_flag(self, flag, value);
}
