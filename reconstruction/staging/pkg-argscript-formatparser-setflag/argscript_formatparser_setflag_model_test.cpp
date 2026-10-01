#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "argscript_formatparser_setflag.hpp"

namespace openspore::reconstruction::pkg_argscript_formatparser_setflag {
namespace {

// Reference stand-ins for the two unresolved ports. They are NOT models of
// 0x0083e470 / 0x0083d290; they only let the target's own control flow be
// observed and asserted.
struct CallLog {
  int parse_calls = 0;
  int expect_calls = 0;
  char expect_char_seen = '\0';
  int order = 0;
  const void* self_seen[4] = {nullptr, nullptr, nullptr, nullptr};
  const char** cursor_seen[4] = {nullptr, nullptr, nullptr, nullptr};
};

CallLog g_log;

void reset_log() { g_log = CallLog{}; }

void record_call(OpaqueScanContext* self, const char** cursor) {
  if (g_log.order < 4) {
    g_log.self_seen[g_log.order] = self;
    g_log.cursor_seen[g_log.order] = cursor;
  }
  ++g_log.order;
}

float PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL ref_parse_number(
    OpaqueScanContext* self, const char** cursor) {
  record_call(self, cursor);
  ++g_log.parse_calls;
  // Mirror the observed port contract: read the cursor's char pointer, and
  // yield +0.0f without advancing on an exhausted string.
  if (**cursor == '\0') {
    return 0.0f;
  }
  char* end = nullptr;
  const float value = std::strtof(*cursor, &end);
  *cursor = end;
  return value;
}

bool PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL ref_expect_char(OpaqueScanContext* self,
                                                       const char** cursor,
                                                       char expected) {
  record_call(self, cursor);
  ++g_log.expect_calls;
  g_log.expect_char_seen = expected;
  if (**cursor == '\0') {
    return false;
  }
  *cursor = *cursor + 1;
  return true;
}

void install_reference_ports() {
  ScanPorts& ports = scan_ports();
  ports.parse_number = &ref_parse_number;
  ports.expect_char = &ref_expect_char;
}

// 0x00841542: ECX is this+0x4c for both ports, and both receive the very same
// address (&arg2 at [ESP+8]) as their cursor.
int test_ports_receive_subobject_and_shared_cursor() {
  OpaqueFormatParser parser{};
  reset_log();
  install_reference_ports();

  char text[] = "1.5,2.5";
  const char* cursor = text;
  float out[2] = {-1.0f, -1.0f};
  const float* returned =
      pkg_argscript_formatparser_set_flag_00841540(&parser, out, &cursor);

  if (g_log.parse_calls != 2 || g_log.expect_calls != 1) {
    return 1;
  }
  if (g_log.expect_char_seen != ',') {
    return 1;
  }
  for (int i = 0; i < g_log.order; ++i) {
    if (g_log.self_seen[i] != &parser.field_04c) {
      return 1;
    }
    if (g_log.cursor_seen[i] != &cursor) {
      return 1;
    }
  }
  if (returned != out) {
    return 1;
  }
  return 0;
}

// 0x00841557 / 0x00841575: comma present -> both words come from the parser.
int test_comma_separated_pair() {
  OpaqueFormatParser parser{};
  reset_log();
  install_reference_ports();

  char text[] = "1.5,2.5";
  const char* cursor = text;
  float out[2] = {-1.0f, -1.0f};
  pkg_argscript_formatparser_set_flag_00841540(&parser, out, &cursor);

  if (out[0] != 1.5f || out[1] != 2.5f) {
    return 1;
  }
  if (std::strcmp(cursor, "") != 0) {
    return 1;
  }
  return 0;
}

// 0x0084157f..0x00841583: no comma -> out[1] = out[0] and the second parse is
// never reached. This is the branch discriminator.
int test_missing_comma_collapses_range() {
  OpaqueFormatParser parser{};
  reset_log();
  install_reference_ports();

  char text[] = "3";
  const char* cursor = text;
  float out[2] = {-1.0f, -1.0f};
  pkg_argscript_formatparser_set_flag_00841540(&parser, out, &cursor);

  if (out[0] != 3.0f || out[1] != 3.0f) {
    return 1;
  }
  if (g_log.parse_calls != 1) {
    return 1;
  }
  if (std::strcmp(cursor, "") != 0) {
    return 1;
  }
  return 0;
}

// The branch is taken on the port's return value, not on string content: a
// trailing comma at end of text still runs the second parse, which then yields
// whatever the parser reports for an exhausted string. No end-of-text check.
int test_trailing_comma_runs_second_parse() {
  OpaqueFormatParser parser{};
  reset_log();
  install_reference_ports();

  char text[] = "4,";
  const char* cursor = text;
  float out[2] = {-1.0f, -1.0f};
  pkg_argscript_formatparser_set_flag_00841540(&parser, out, &cursor);

  if (out[0] != 4.0f || out[1] != 0.0f) {
    return 1;
  }
  if (g_log.parse_calls != 2) {
    return 1;
  }
  return 0;
}

// Both words are written on every exit; out[0] lands before the comma test.
int test_both_words_always_written() {
  OpaqueFormatParser parser{};
  reset_log();
  install_reference_ports();

  char text[] = "7";
  const char* cursor = text;
  float out[2] = {0.0f, 0.0f};
  std::memset(out, 0x7f, sizeof(out));
  pkg_argscript_formatparser_set_flag_00841540(&parser, out, &cursor);

  if (out[0] != 7.0f || out[1] != 7.0f) {
    return 1;
  }
  return 0;
}

// With the inert default ports the model still writes both words and still
// returns `out`; the collapse branch is taken because ExpectChar reports false.
int test_inert_default_ports() {
  OpaqueFormatParser parser{};
  ScanPorts& ports = scan_ports();
  ports.parse_number = &default_parse_number_port;
  ports.expect_char = &default_expect_char_port;

  char text[] = "1,2";
  const char* cursor = text;
  float out[2] = {-1.0f, -1.0f};
  const float* returned =
      pkg_argscript_formatparser_set_flag_00841540(&parser, out, &cursor);

  if (out[0] != 0.0f || out[1] != 0.0f) {
    return 1;
  }
  if (returned != out) {
    return 1;
  }
  if (cursor != text) {
    return 1;
  }
  return 0;
}

// The single call site at 0x0082fde0 reads the result as
//   0x0082fde5  MOVSS XMM0,dword ptr [EAX]
//   0x0082fde9  MOVSS XMM1,dword ptr [EAX+0x4]
// i.e. two independent 32-bit floats read back from the returned pointer. This
// pins that contract: the model must return the very pointer the caller pushed
// and must have filled both of its words, on both branch outcomes, so that the
// caller's two MOVSS reads are well defined.
int test_returned_pointer_yields_two_floats() {
  OpaqueFormatParser parser{};
  reset_log();
  install_reference_ports();

  {
    char paired[] = "1.5,2.5";
    const char* cursor = paired;
    float out[2] = {-1.0f, -1.0f};
    const float* returned =
        pkg_argscript_formatparser_set_flag_00841540(&parser, out, &cursor);
    if (returned == nullptr || returned[0] != 1.5f || returned[1] != 2.5f) {
      return 1;
    }
  }
  {
    char single[] = "8.25";
    const char* cursor = single;
    float out[2] = {-1.0f, -1.0f};
    const float* returned =
        pkg_argscript_formatparser_set_flag_00841540(&parser, out, &cursor);
    if (returned == nullptr || returned[0] != 8.25f || returned[1] != 8.25f) {
      return 1;
    }
  }
  return 0;
}

void test_abi_shape() {
  using Return = decltype(pkg_argscript_formatparser_set_flag_00841540(
      static_cast<OpaqueFormatParser*>(nullptr), static_cast<float*>(nullptr),
      static_cast<const char**>(nullptr)));
  static_assert(std::is_same<Return, float*>::value, "float* return type");
  static_assert(sizeof(Return) == sizeof(float*), "return width");
  static_assert(offsetof(OpaqueFormatParser, field_04c) == 0x4c,
                "ECX sub-object displacement");
}

}

int run() {
  if (test_ports_receive_subobject_and_shared_cursor() != 0) {
    return 1;
  }
  if (test_comma_separated_pair() != 0) {
    return 1;
  }
  if (test_missing_comma_collapses_range() != 0) {
    return 1;
  }
  if (test_trailing_comma_runs_second_parse() != 0) {
    return 1;
  }
  if (test_both_words_always_written() != 0) {
    return 1;
  }
  if (test_inert_default_ports() != 0) {
    return 1;
  }
  if (test_returned_pointer_yields_two_floats() != 0) {
    return 1;
  }
  test_abi_shape();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_argscript_formatparser_setflag::run();
}
