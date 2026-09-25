#include "argscript_parser.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG_ARGS_THIS_CALL __thiscall
#else
#define PKG_ARGS_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_wave6 {

ParserPorts g_argscript_parser_ports{};

namespace {

template <typename Function>
Function load_slot(const OpaqueFormatParserVtable* vtable,
                   std::size_t offset) {
  Function function = nullptr;
  std::memcpy(&function, reinterpret_cast<const std::uint8_t*>(vtable) + offset,
              sizeof(function));
  return function;
}

OpaqueWord load_word(const void* object, std::size_t offset) {
  OpaqueWord value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(object) + offset,
              sizeof(value));
  return value;
}

void store_word(void* object, std::size_t offset, OpaqueWord value) {
  std::memcpy(static_cast<std::uint8_t*>(object) + offset, &value,
              sizeof(value));
}

class ExceptionFrame {
 public:
  ExceptionFrame()
      : previous_(g_argscript_parser_ports.read_exception_list != nullptr
                      ? g_argscript_parser_ports.read_exception_list()
                      : 0) {}

  ~ExceptionFrame() {
    if (g_argscript_parser_ports.write_exception_list != nullptr) {
      g_argscript_parser_ports.write_exception_list(previous_);
    }
  }

 private:
  OpaqueWord previous_;
};

}

OpaqueWord PKG_ARGS_THIS_CALL release_00841290(OpaqueFormatParser* parser,
                                                OpaqueWord argument) {
  ExceptionFrame exception_frame;
  const ReleaseDispatch dispatch =
      load_slot<ReleaseDispatch>(parser->vtable, 0x3c);
  const OpaqueWord result = dispatch(parser, argument);
  return (result & 0xffffff00U) | 1U;
}

OpaqueWord PKG_ARGS_THIS_CALL create_definition_safe_00841440(
    OpaqueFormatParser* parser, OpaqueWord first, OpaqueWord second) {
  store_word(parser, 0x30, second == 0 ? 0 : second - 4U);
  store_word(parser, 0x04, first);
  store_word(parser, 0x0c, second);
  return first;
}

OpaqueWord PKG_ARGS_THIS_CALL read_result_008414c0(
    OpaqueFormatParser* parser) {
  return load_word(&parser->field_154, 0);
}

OpaqueWord PKG_ARGS_THIS_CALL format_result_008414d0(
    OpaqueFormatParser* parser) {
  const OpaqueWord source = load_word(&parser->field_e0, 0);
  const OpaqueWord value = static_cast<OpaqueWord>(parser->field_f0);
  g_argscript_parser_ports.format_error(&parser->field_f4, "%s:%d", source,
                                         value);
  return load_word(&parser->field_f4, 0);
}

float* PKG_ARGS_THIS_CALL set_flag_00841540(OpaqueFormatParser* parser,
                                             float* output,
                                             const char* input) {
  char* cursor = const_cast<char*>(input);
  output[0] = g_argscript_parser_ports.parse_number(&parser->lexer, &cursor);
  if (g_argscript_parser_ports.consume_if(&parser->lexer, &cursor, ',') != 0) {
    output[1] =
        g_argscript_parser_ports.parse_number(&parser->lexer, &cursor);
  } else {
    output[1] = output[0];
  }
  return output;
}

}
