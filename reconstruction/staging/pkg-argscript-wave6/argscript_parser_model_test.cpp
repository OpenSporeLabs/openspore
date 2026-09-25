#include "argscript_parser.hpp"

#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#if defined(_MSC_VER)
#define PKG_ARGS_THIS_CALL __thiscall
#else
#define PKG_ARGS_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_wave6 {
namespace {

using Trace = std::vector<std::string>;

struct ParserFailure {
  OpaqueWord expected;
};

Trace trace;
OpaqueWord last_release_argument = 0;
OpaqueWord exception_previous = 0x55667788U;
OpaqueLexer* expected_lexer = nullptr;
OpaqueWord expected_delimiter = 0;

OpaqueWord read_exception_list() {
  trace.emplace_back("read-exception");
  return exception_previous;
}

void write_exception_list(OpaqueWord value) {
  trace.emplace_back("write-exception");
  assert(value == exception_previous);
}

OpaqueWord release_dispatch(OpaqueFormatParser* parser, OpaqueWord argument) {
  trace.emplace_back("release-dispatch");
  assert(parser != nullptr);
  last_release_argument = argument;
  return 0x12345678U;
}

void format_error(OpaqueString* destination, const char* format,
                  OpaqueWord source, OpaqueWord value) {
  trace.emplace_back(std::string("format:") + format + ":" +
                     std::to_string(static_cast<std::uint32_t>(value)));
  assert(destination != nullptr);
  const auto offset = static_cast<std::intptr_t>(
      static_cast<std::int32_t>(static_cast<std::uint32_t>(value)));
  destination->begin = reinterpret_cast<char*>(
      reinterpret_cast<std::uintptr_t>(source) + offset);
  destination->end = destination->begin + 1;
  destination->capacity = destination->begin + 1;
}

float PKG_ARGS_THIS_CALL parse_number(OpaqueLexer* lexer, char** cursor) {
  assert(lexer == expected_lexer);
  assert(cursor != nullptr);
  assert(*cursor != nullptr);
  trace.emplace_back("parse-number");
  char* end = nullptr;
  const float value = std::strtof(*cursor, &end);
  if (end != *cursor) {
    *cursor = end;
  }
  return value;
}

std::uint8_t PKG_ARGS_THIS_CALL consume_if(OpaqueLexer* lexer, char** cursor,
                                           OpaqueWord delimiter) {
  assert(lexer == expected_lexer);
  assert(cursor != nullptr);
  assert(*cursor != nullptr);
  assert(delimiter == expected_delimiter);
  trace.emplace_back("consume");
  while (**cursor != '\0' &&
         std::isspace(static_cast<unsigned char>(**cursor)) != 0) {
    ++*cursor;
  }
  if (**cursor == '\0') {
    return 0;
  }
  if (static_cast<unsigned char>(**cursor) !=
      static_cast<unsigned char>(delimiter)) {
    trace.emplace_back("consume-error");
    throw ParserFailure{delimiter};
  }
  ++*cursor;
  return 1;
}

void install_ports() {
  g_argscript_parser_ports.read_exception_list = read_exception_list;
  g_argscript_parser_ports.write_exception_list = write_exception_list;
  g_argscript_parser_ports.format_error = format_error;
  g_argscript_parser_ports.parse_number = parse_number;
  g_argscript_parser_ports.consume_if = consume_if;
}

OpaqueWord read_word(const void* object, std::size_t offset) {
  OpaqueWord value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(object) + offset,
              sizeof(value));
  return value;
}

void install_release_slot(OpaqueFormatParser* parser) {
  OpaqueFormatParserVtable vtable{};
  ReleaseDispatch dispatch = release_dispatch;
  std::memcpy(&vtable.slots[0x3c / sizeof(OpaqueWord)], &dispatch,
              sizeof(dispatch));
  parser->vtable = &vtable;
}

void test_release() {
  OpaqueFormatParser parser{};
  install_release_slot(&parser);
  trace.clear();
  last_release_argument = 0;
  const OpaqueWord result = release_00841290(&parser, 0x89abcdefU);
  assert(result == 0x12345601U);
  assert(last_release_argument == 0x89abcdefU);
  assert(trace.size() == 3);
  assert(trace[0] == "read-exception");
  assert(trace[1] == "release-dispatch");
  assert(trace[2] == "write-exception");
}

void test_create_definition_safe() {
  OpaqueFormatParser parser{};
  OpaqueLine line{};
  char name[] = "__name";
  const OpaqueWord first = reinterpret_cast<OpaqueWord>(&line);
  const OpaqueWord second = reinterpret_cast<OpaqueWord>(name + 4);

  assert(create_definition_safe_00841440(&parser, first, second) == first);
  assert(read_word(&parser, 0x04) == first);
  assert(read_word(&parser, 0x0c) == second);
  assert(read_word(&parser, 0x30) == second - 4U);

  assert(create_definition_safe_00841440(&parser, first, 0) == first);
  assert(read_word(&parser, 0x30) == 0);
  assert(read_word(&parser, 0x04) == first);
  assert(read_word(&parser, 0x0c) == 0);
}

void test_read_result() {
  OpaqueFormatParser parser{};
  char marker[] = "result";
  parser.field_154.begin = marker;
  assert(read_result_008414c0(&parser) ==
         reinterpret_cast<OpaqueWord>(marker));
}

void test_format_result() {
  OpaqueFormatParser parser{};
  char source[] = "source";
  char old[] = "old";
  parser.field_e0.begin = source;
  parser.field_f0 = -7;
  parser.field_f4.begin = old;
  trace.clear();

  const OpaqueWord result = format_result_008414d0(&parser);
  const OpaqueWord expected = reinterpret_cast<OpaqueWord>(source - 7);
  assert(result == expected);
  assert(parser.field_f4.begin == source - 7);
  assert(trace.size() == 1);
  assert(trace[0] == "format:%s:%d:4294967289");
}

void test_set_flag_pair() {
  OpaqueFormatParser parser{};
  expected_lexer = &parser.lexer;
  expected_delimiter = static_cast<OpaqueWord>(',');
  trace.clear();

  char input[] = "1.5,2.25";
  float output[2]{};
  float* result = set_flag_00841540(&parser, output, input);
  assert(result == output);
  assert(output[0] == 1.5F);
  assert(output[1] == 2.25F);
  assert(trace.size() == 4);
  assert(trace[0] == "parse-number");
  assert(trace[1] == "consume");
  assert(trace[2] == "parse-number");
}

void test_set_flag_duplicate() {
  OpaqueFormatParser parser{};
  expected_lexer = &parser.lexer;
  expected_delimiter = static_cast<OpaqueWord>(',');
  trace.clear();

  char input[] = "3";
  float output[2]{};
  assert(set_flag_00841540(&parser, output, input) == output);
  assert(output[0] == 3.0F);
  assert(output[1] == 3.0F);
  assert(trace.size() == 2);
  assert(trace[1] == "consume");
}

void test_set_flag_error() {
  OpaqueFormatParser parser{};
  expected_lexer = &parser.lexer;
  expected_delimiter = static_cast<OpaqueWord>(',');
  trace.clear();

  char input[] = "4x";
  float output[2]{};
  bool caught = false;
  try {
    set_flag_00841540(&parser, output, input);
  } catch (const ParserFailure& failure) {
    caught = true;
    assert(failure.expected == static_cast<OpaqueWord>(','));
  }
  assert(caught);
  assert(output[0] == 4.0F);
  assert(output[1] == 0.0F);
  assert(trace.size() == 3);
  assert(trace[2] == "consume-error");
}

void run() {
  install_ports();
  test_release();
  test_create_definition_safe();
  test_read_result();
  test_format_result();
  test_set_flag_pair();
  test_set_flag_duplicate();
  test_set_flag_error();
}

}

}

int main() {
  openspore::reconstruction::pkg_argscript_wave6::run();
}
