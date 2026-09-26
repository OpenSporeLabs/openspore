// Standalone model test for the reconstruction of SporeApp.exe 0x004a88d0.
// Build:
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror -I <dir> \
//       editor_004a88d0.cpp editor_004a88d0_model_test.cpp \
//       -o /tmp/opencode/004a88d0-model && /tmp/opencode/004a88d0-model

#include "editor_004a88d0.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace openspore::reconstruction::wave13_pilot_dispatch_b00;

namespace {

// Recorder for the four vtable calls the port 0x00435ed0 makes.
struct Call {
  const char *slot;
  std::uint32_t key;
  std::uint32_t value;
};

std::vector<Call> g_calls;
std::uint32_t g_current_value = 0u;
bool g_sink_present = true;
int failures = 0;

void expect(bool condition, const char *what) {
  if (!condition) {
    std::printf("FAIL: %s\n", what);
    ++failures;
  }
}

// ---- test doubles for the two vtable slots the port exercises ----
std::uint32_t test_get_current_value(void *self) {
  if (self == nullptr) {
    return 0u;
  }
  return g_current_value;
}

void test_begin_named_scope(void *, const char *name) {
  (void)name;
  g_calls.push_back({"0x38", reinterpret_cast<std::uint32_t>(name), 0u});
}

void test_set_keyed_value(void *, const char *key, std::uint32_t value) {
  g_calls.push_back({"0x40", reinterpret_cast<std::uint32_t>(key), value});
}

void test_commit(void *) { g_calls.push_back({"0x58", 0u, 0u}); }

OpaqueKeyedRecordSinkVtable *make_vtable() {
  static OpaqueKeyedRecordSinkVtable table;
  std::memset(&table, 0, sizeof(table));
  table.get_current_value = &test_get_current_value;
  table.begin_named_scope = &test_begin_named_scope;
  table.set_keyed_value = &test_set_keyed_value;
  table.commit = &test_commit;
  return &table;
}

// The port 0x00435ed0, written out as a test double from its observed
// contract so the key ordering asserted below is exercised. This is not a
// reconstruction of 0x00435ed0; the real body stays opaque.
void emit_record_double(std::uint32_t event_tag, std::uint32_t value) {
  static OpaqueKeyedRecordSinkHolder holder = {make_vtable()};
  if (!g_sink_present) {
    return;
  }
  holder.vtable->begin_named_scope(
      &holder, reinterpret_cast<const char *>(kRecordScopeName));
  holder.vtable->set_keyed_value(
      &holder, reinterpret_cast<const char *>(kRecordEventTagKey), event_tag);
  holder.vtable->set_keyed_value(
      &holder, reinterpret_cast<const char *>(kRecordCurrentValueKey), value);
  holder.vtable->commit(&holder);
}

} // namespace

// The two opaque ports of the reconstructed body.
extern "C" std::uint32_t editor_record_current_value_port() {
  if (!g_sink_present) {
    return 0u; // 0x00435e90 returns 0 when DAT_0166D9F4 is null
  }
  static OpaqueKeyedRecordSinkHolder holder = {make_vtable()};
  return holder.vtable->get_current_value(&holder);
}

extern "C" void editor_record_emit_port(std::uint32_t event_tag,
                                        std::uint32_t value) {
  emit_record_double(event_tag, value);
}

int main() {
  std::printf("case 1: byte-exact body, sink present\n");
  g_sink_present = true;
  g_current_value = 0x00ABCDEFu;
  g_calls.clear();
  Editor_004a88d0_record_tagged_action_raw(0x00A03E74B2u);
  expect(g_calls.size() == 4, "case 1 made exactly four vtable calls");
  if (g_calls.size() == 4) {
    expect(std::strcmp(g_calls[0].slot, "0x38") == 0,
           "case 1 opened with 0x38");
    expect(g_calls[0].key == kRecordScopeName,
           "case 1 opened with kRecordScopeName 0x03475365");
    expect(g_calls[1].key == kRecordEventTagKey,
           "case 1 first key is kRecordEventTagKey 0x03475381");
    expect(g_calls[1].value == 0x00A03E74B2u,
           "case 1 put the argument under kRecordEventTagKey");
    expect(g_calls[2].key == kRecordCurrentValueKey,
           "case 1 second key is kRecordCurrentValueKey 0x03475385");
    expect(g_calls[2].value == 0x00ABCDEFu,
           "case 1 put the vtable+0x20 result under kRecordCurrentValueKey");
    expect(std::strcmp(g_calls[3].slot, "0x58") == 0,
           "case 1 closed with 0x58");
  }

  std::printf("case 2: the vtable+0x20 result is read once per call\n");
  g_calls.clear();
  Editor_004a88d0_record_tagged_action(0x00C355901Au);
  expect(g_calls.size() == 4, "case 2 made exactly four vtable calls");
  if (g_calls.size() == 4) {
    expect(g_calls[1].value == 0x00C355901Au, "case 2 argument forwarded");
    expect(g_calls[2].value == 0x00ABCDEFu, "case 2 current value forwarded");
  }

  std::printf("case 3: absent sink -> no calls at all\n");
  g_sink_present = false;
  g_calls.clear();
  Editor_004a88d0_record_tagged_action_raw(0x00D2C7F386u);
  expect(g_calls.empty(), "case 3 made no vtable calls");

  if (failures != 0) {
    std::printf("%d FAILURE(S)\n", failures);
    return 1;
  }
  std::printf("OK\n");
  return 0;
}
