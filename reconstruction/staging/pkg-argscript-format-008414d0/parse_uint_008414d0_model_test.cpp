#include <cassert>
#include <cstdio>
#include <cstring>
#include <type_traits>

#include "parse_uint_008414d0.hpp"

namespace openspore::reconstruction::pkg_argscript_format_008414d0 {
namespace {

struct Recorder {
  int calls = 0;
  const OpaqueString* destination = nullptr;
  char const* format = nullptr;
  OpaqueWord first = 0;
  OpaqueWord second = 0;
  char assigned[64]{};
  bool writes = false;
};

Recorder g_recorder;

void recording_port(OpaqueString* destination, char const* format,
                    OpaqueWord first, OpaqueWord second) {
  ++g_recorder.calls;
  g_recorder.destination = destination;
  g_recorder.format = format;
  g_recorder.first = first;
  g_recorder.second = second;
  if (!g_recorder.writes) {
    return;
  }
  std::snprintf(g_recorder.assigned, sizeof(g_recorder.assigned), "%s",
                "assigned");
  destination->begin = g_recorder.assigned;
  destination->end = g_recorder.assigned + std::strlen(g_recorder.assigned);
}

class PortScope {
 public:
  explicit PortScope(CopyFormattedToString port) {
    previous_ = g_argscript_format_ports.copy_formatted_00840c20;
    g_argscript_format_ports.copy_formatted_00840c20 = port;
  }
  ~PortScope() { g_argscript_format_ports.copy_formatted_00840c20 = previous_; }

 private:
  CopyFormattedToString previous_;
};

// 0x008414d0 pushes exactly one variadic word per format conversion and
// nothing else; the port must be entered once with the observed operands.
void test_call_contract_is_exact() {
  OpaqueFormatParser parser{};
  char source[] = "source";
  parser.field_0e0.begin = source;
  parser.field_0f0 = -7;

  g_recorder = Recorder{};
  g_recorder.writes = false;
  {
    PortScope scope(&recording_port);
    (void)parse_uint_008414d0(&parser);
  }

  assert(g_recorder.calls == 1);
  assert(g_recorder.destination == &parser.field_0f4);
  assert(std::strcmp(g_recorder.format, "%s:%d") == 0);
  assert(g_recorder.first ==
         static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(source)));
  assert(g_recorder.second == 0xfffffff9U);
}

// 0x008414f0 reloads word 0 of the destination string after the call, so the
// return value is whatever the callee left there, not the pre-call value.
void test_return_follows_destination_begin() {
  OpaqueFormatParser parser{};
  char source[] = "source";
  char before[] = "before";
  parser.field_0e0.begin = source;
  parser.field_0f4.begin = before;
  parser.field_0f4.end = before + std::strlen(before);

  g_recorder = Recorder{};
  g_recorder.writes = false;
  char const* untouched = nullptr;
  {
    PortScope scope(&recording_port);
    untouched = parse_uint_008414d0(&parser);
  }
  (void)untouched;
  assert(untouched == before);

  g_recorder = Recorder{};
  g_recorder.writes = true;
  char const* rewritten = nullptr;
  {
    PortScope scope(&recording_port);
    rewritten = parse_uint_008414d0(&parser);
  }
  (void)rewritten;
  assert(rewritten == g_recorder.assigned);
  assert(rewritten == parser.field_0f4.begin);
}

// The word at +0xf0 is forwarded verbatim; no sign or zero extension is
// inserted before it reaches the "%d" conversion.
void test_field_0f0_is_forwarded_verbatim() {
  OpaqueFormatParser parser{};
  parser.field_0f0 = -1;
  g_recorder = Recorder{};
  g_recorder.writes = false;
  {
    PortScope scope(&recording_port);
    (void)parse_uint_008414d0(&parser);
  }
  assert(g_recorder.second == 0xffffffffU);

  parser.field_0f0 = 0;
  g_recorder = Recorder{};
  g_recorder.writes = false;
  {
    PortScope scope(&recording_port);
    (void)parse_uint_008414d0(&parser);
  }
  assert(g_recorder.second == 0u);
}

// The package-local model of 0x00840c20 reproduces the observed
// strlen(scratch) - 1 range handed to the assign step, so the destination ends
// up one character shorter than the scratch text.
void test_model_assigns_observed_range() {
  OpaqueFormatParser parser{};
  char source[] = "parser.kb";
  char buffer[32];
  std::memset(buffer, 'x', sizeof(buffer));
  parser.field_0e0.begin = source;
  parser.field_0f0 = 42;
  parser.field_0f4.begin = buffer;
  parser.field_0f4.end = buffer + sizeof(buffer);

  {
    PortScope scope(&model_copy_formatted_00840c20);
    const char* result = parse_uint_008414d0(&parser);
    (void)result;
    assert(result == buffer);
    assert(std::strcmp(buffer, "parser.kb:4") == 0);
    assert(buffer[sizeof(buffer) - 1] == 'x');
  }
}

// A destination whose end word leaves no room for the observed range takes the
// 0x00454cb0 reallocation branch, which this package deliberately leaves
// unmodelled: nothing is written.
void test_model_grow_branch_is_unmodelled() {
  OpaqueFormatParser parser{};
  char source[] = "parser.kb";
  char buffer[8];
  std::memset(buffer, 'x', sizeof(buffer));
  parser.field_0e0.begin = source;
  parser.field_0f0 = 42;
  parser.field_0f4.begin = buffer;
  parser.field_0f4.end = buffer + 4;

  {
    PortScope scope(&model_copy_formatted_00840c20);
    const char* result = parse_uint_008414d0(&parser);
    (void)result;
    assert(result == buffer);
    for (std::size_t i = 0; i < sizeof(buffer); ++i) {
      assert(buffer[i] == 'x');
    }
  }
}

// The default port is the package-local model, never null, so the observed
// call site always has a callee.
void test_default_port_is_installed() {
  assert(g_argscript_format_ports.copy_formatted_00840c20 ==
         &model_copy_formatted_00840c20);
}

// The entry point is a __thiscall member of the opaque receiver, so a null
// receiver is the only argument a caller can pass without touching memory.
void test_entry_point_is_thiscall() {
  using Target = decltype(parse_uint_008414d0(
      static_cast<OpaqueFormatParser*>(nullptr)));
  static_assert(std::is_same<Target, char const*>::value,
                "0x008414f0 returns the destination string begin word");
  static_assert(sizeof(Target) == 4, "32-bit return register width");
  using Callee = decltype(&model_copy_formatted_00840c20);
  static_assert(std::is_same<Callee, CopyFormattedToString>::value,
                "observed callee word shape");
  static_assert(std::is_same<OpaqueWord, std::uint32_t>::value,
                "operands are raw 32-bit words");
}

int run() {
  test_call_contract_is_exact();
  test_return_follows_destination_begin();
  test_field_0f0_is_forwarded_verbatim();
  test_model_assigns_observed_range();
  test_model_grow_branch_is_unmodelled();
  test_default_port_is_installed();
  test_entry_point_is_thiscall();
  return 0;
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_argscript_format_008414d0

int main() {
  return openspore::reconstruction::pkg_argscript_format_008414d0::run();
}
