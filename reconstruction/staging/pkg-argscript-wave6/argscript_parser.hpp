#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-argscript staging requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-argscript target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "PKG-argscript target words are 32-bit");

#if defined(_MSC_VER)
#define PKG_ARGS_THIS_CALL __thiscall
#else
#define PKG_ARGS_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_wave6 {

using OpaqueWord = std::uint32_t;

struct OpaqueString {
  char* begin = nullptr;
  char* end = nullptr;
  char* capacity = nullptr;
  void* allocator = nullptr;
};

struct OpaqueLexer {
  std::array<std::uint8_t, 0x20> bytes{};
};

struct OpaqueLine {
  std::array<std::uint8_t, 0x44> bytes{};
};

struct OpaqueMap {
  std::array<std::uint8_t, 0x20> bytes{};
};

struct OpaqueVector {
  std::array<std::uint8_t, 0x14> bytes{};
};

struct OpaqueFormatParserVtable {
  using Slot = OpaqueWord;
  std::array<Slot, 0xd0 / sizeof(Slot)> slots{};
};

struct OpaqueFormatParser {
  OpaqueFormatParserVtable* vtable = nullptr;
  OpaqueWord field_04 = 0;
  std::int32_t field_08 = 0;
  std::uint8_t field_0c = 0;
  std::array<std::uint8_t, 3> padding_0d{};
  std::int32_t field_10 = 0;
  void* trace_stream = nullptr;
  std::int32_t field_18 = 0;
  std::int32_t field_1c = 0;
  std::int32_t field_20 = 0;
  std::int32_t field_24 = 0;
  void* data = nullptr;
  OpaqueMap parsers;
  OpaqueLexer lexer;
  OpaqueMap definitions;
  OpaqueMap variables;
  OpaqueMap global_variables;
  std::int32_t field_cc = 0;
  OpaqueString field_d0;
  OpaqueString field_e0;
  std::int32_t field_f0 = 0;
  OpaqueString field_f4;
  std::int32_t field_104 = 0;
  OpaqueVector blocks;
  OpaqueVector special_blocks;
  OpaqueString current_scope;
  OpaqueVector scope_lengths;
  OpaqueString field_154;
  std::uint8_t field_164 = 0;
  std::array<std::uint8_t, 3> padding_165{};
  std::int32_t field_168 = 0;
  OpaqueLine temp_line;
  OpaqueString temp_string;
};

static_assert(sizeof(OpaqueString) == 0x10,
              "ArgScript string prefix has the observed width");
static_assert(sizeof(OpaqueLexer) == 0x20,
              "ArgScript lexer has the observed width");
static_assert(sizeof(OpaqueLine) == 0x44,
              "ArgScript line has the observed width");
static_assert(sizeof(OpaqueMap) == 0x20,
              "ArgScript map has the observed width");
static_assert(sizeof(OpaqueVector) == 0x14,
              "ArgScript vector has the observed width");
static_assert(sizeof(OpaqueFormatParserVtable) == 0xd0,
              "ArgScript parser vtable has the observed width");
static_assert(sizeof(OpaqueFormatParser) == 0x1c0,
              "ArgScript parser has the observed width");
static_assert(offsetof(OpaqueFormatParser, field_04) == 0x04,
              "ArgScript parser field_04 offset");
static_assert(offsetof(OpaqueFormatParser, parsers) == 0x2c,
              "ArgScript parser map offset");
static_assert(offsetof(OpaqueFormatParser, lexer) == 0x4c,
              "ArgScript parser lexer offset");
static_assert(offsetof(OpaqueFormatParser, field_d0) == 0xd0,
              "ArgScript parser field_d0 offset");
static_assert(offsetof(OpaqueFormatParser, field_e0) == 0xe0,
              "ArgScript parser field_e0 offset");
static_assert(offsetof(OpaqueFormatParser, field_f0) == 0xf0,
              "ArgScript parser field_f0 offset");
static_assert(offsetof(OpaqueFormatParser, field_f4) == 0xf4,
              "ArgScript parser field_f4 offset");
static_assert(offsetof(OpaqueFormatParser, field_154) == 0x154,
              "ArgScript parser field_154 offset");
static_assert(offsetof(OpaqueFormatParser, field_164) == 0x164,
              "ArgScript parser field_164 offset");
static_assert(offsetof(OpaqueFormatParser, field_168) == 0x168,
              "ArgScript parser field_168 offset");
static_assert(offsetof(OpaqueFormatParser, temp_line) == 0x16c,
              "ArgScript parser temp line offset");
static_assert(offsetof(OpaqueFormatParser, temp_string) == 0x1b0,
              "ArgScript parser temp string offset");

using ReadExceptionList = OpaqueWord (*)();
using WriteExceptionList = void (*)(OpaqueWord);
using ReleaseDispatch = OpaqueWord (*)(OpaqueFormatParser*, OpaqueWord);
using FormatError = void (*)(OpaqueString*, const char*, OpaqueWord, OpaqueWord);
using ParseNumber = float(PKG_ARGS_THIS_CALL*)(OpaqueLexer*, char**);
using ConsumeIf = std::uint8_t(PKG_ARGS_THIS_CALL*)(OpaqueLexer*, char**,
                                                     OpaqueWord);

struct ParserPorts {
  ReadExceptionList read_exception_list = nullptr;
  WriteExceptionList write_exception_list = nullptr;
  FormatError format_error = nullptr;
  ParseNumber parse_number = nullptr;
  ConsumeIf consume_if = nullptr;
};

extern ParserPorts g_argscript_parser_ports;

OpaqueWord PKG_ARGS_THIS_CALL release_00841290(OpaqueFormatParser* parser,
                                                OpaqueWord argument);

OpaqueWord PKG_ARGS_THIS_CALL create_definition_safe_00841440(
    OpaqueFormatParser* parser, OpaqueWord first, OpaqueWord second);

OpaqueWord PKG_ARGS_THIS_CALL read_result_008414c0(
    OpaqueFormatParser* parser);

OpaqueWord PKG_ARGS_THIS_CALL format_result_008414d0(
    OpaqueFormatParser* parser);

float* PKG_ARGS_THIS_CALL set_flag_00841540(OpaqueFormatParser* parser,
                                             float* output,
                                             const char* input);

}

#undef PKG_ARGS_THIS_CALL
