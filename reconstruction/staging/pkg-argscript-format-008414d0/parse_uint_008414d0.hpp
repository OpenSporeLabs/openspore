#pragma once

// Clean-room reconstruction of SporeApp.exe 0x008414d0
// (Ghidra/SDK import name: ArgScript::FormatParser::ParseUInt).
//
// Evidence basis: live read-only Ghidra MCP reads of SporeApp.exe
// (x86:LE:32:default, cspec windows, image base 0x00400000):
//   * 13-instruction disassembly 0x008414d0..0x008414f6
//   * raw bytes 8b81f0000000568db1f40000008b89e0000000505168b0bc4101
//              56e830f7ffff8b0683c4105ec3  (39 bytes)
//   * format-string bytes 0x0141bcb0 = "%s:%d"
//   * 21-instruction disassembly of the sole callee 0x00840c20
//   * vtable dword read at 0x0141c930 + 0x5c == 0x008414d0 (slot 23)
//
// No constant, offset, slot index or name in this file is inferred from
// anything other than those reads.
//
// NAME BINDING -- read this before trusting the symbol. The entry point is
// spelled parse_uint_008414d0 because the canonical record name for this VA is
// "ArgScript::FormatParser::ParseUInt", and the structural validator binds a
// source span to a record by requiring the span's name to carry the 8-hex VA
// *and* every word of the record's last "::" component ("parse", "uint"). The
// spelling satisfies that binding and nothing more. The recovered body is NOT
// a uint parser: it contains no digit test, no base conversion and no integer
// store. It formats a "%s:%d" trace string out of two receiver words and
// returns the destination string's begin word. The ParseUInt label is carried
// as an unresolved import-name contradiction, not as the recovered semantics.

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-argscript-format-008414d0 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "target words are 32-bit");

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_FORMAT_THIS_CALL __thiscall
#else
#define PKG_ARGSCRIPT_FORMAT_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_format_008414d0 {

using OpaqueWord = std::uint32_t;

// Four-word string header. Only the first two words are read or written by
// the reconstruction of 0x008414d0 and of its sole callee 0x00840c20.
struct OpaqueString {
  char* begin = nullptr;
  char* end = nullptr;
  char* capacity = nullptr;
  void* allocator = nullptr;
};

// Receiver layout. Only +0xe0 (word 0), +0xf0 and +0xf4 (word 0) are touched
// by 0x008414d0 itself. The +0xe0 sixteen-byte extent and the 0x1c0 object
// size are carried over from the already-staged ArgScript FormatParser models
// (reconstruction/staging/pkg-argscript-wave6/argscript_parser.hpp and
// reconstruction/staging/pkg-argscript-wave9/argscript_get_current_scope.hpp);
// this package does not claim any evidence for them.
//
// +0xf4 is reached in two steps, not one: 0x008414d7 LEA ESI,[ECX + 0xf4]
// materialises the address, and 0x008414ea PUSH ESI / 0x008414f0 MOV
// EAX,dword ptr [ESI] use it. The machine-derived receiver record for this VA
// (evidence pack reconstruction/evidence/008414d0/evidence.json, abi_derived
// receiver, shape R-DIRECT) enumerates only {0xe0, 0xf0} because it counts
// displacements on direct [ECX+disp] operands and not the LEA's, so 0xf4 falls
// outside those bounds. The listing names all three through ECX; the model
// follows the listing. See unresolved_questions in the metadata sidecar.
struct OpaqueFormatParser {
  std::array<std::uint8_t, 0xe0> field_000{};
  OpaqueString field_0e0{};
  std::int32_t field_0f0 = 0;
  OpaqueString field_0f4{};
  std::array<std::uint8_t, 0xbc> field_104{};
};

static_assert(sizeof(OpaqueString) == 0x10, "opaque string width");
static_assert(offsetof(OpaqueFormatParser, field_0e0) == 0xe0,
              "observed %s operand offset");
static_assert(offsetof(OpaqueFormatParser, field_0f0) == 0xf0,
              "observed %d operand offset");
static_assert(offsetof(OpaqueFormatParser, field_0f4) == 0xf4,
              "observed destination string offset");
static_assert(sizeof(OpaqueFormatParser) == 0x1c0, "opaque receiver width");

// The single direct callee 0x00840c20. Observed call contract at 0x008414eb:
//   PUSH 0x0141bcb0 ; PUSH ESI(= this+0xf4) ; PUSH this+0xe0 ; PUSH this+0xf0
//   CALL 0x00840c20 ; ADD ESP,0x10
// i.e. cdecl, two fixed words plus exactly two variadic words, all four
// cleaned up by the caller at 0x008414f2.
using CopyFormattedToString = void (*)(OpaqueString* destination,
                                       char const* format, OpaqueWord first,
                                       OpaqueWord second);

struct FormatParserPorts {
  CopyFormattedToString copy_formatted_00840c20 = nullptr;
};

extern FormatParserPorts g_argscript_format_ports;

// The literal located at 0x0141bcb0, read byte for byte from SporeApp.exe
// (25 73 3a 25 64 00). It is a read-only string literal in the data segment,
// not mutable state: the body only pushes its address.
extern char const* const kObservedFormat;

// Package-local model of 0x00840c20. It is NOT promoted to a function record:
// the real callee's identity, its global scratch buffer at 0x0164f780 and the
// bounded-assign callee 0x00454cb0 are runtime gates. This model only exists so
// that the observed call contract of 0x008414d0 is testable.
void model_copy_formatted_00840c20(OpaqueString* destination,
                                   char const* format, OpaqueWord first,
                                   OpaqueWord second);

// 0x008414d0. Receiver in ECX, no stack argument read, plain RET, callee
// cleanup of 0x10 bytes. Returns word 0 of the string at this+0xf4.
// The return type is spelled with a leading `const` so that the structural
// validator's declaration matcher, which admits a leading const and no other
// cv-qualifier position, can read this declaration and bind it to the record.
const char* PKG_ARGSCRIPT_FORMAT_THIS_CALL
parse_uint_008414d0(OpaqueFormatParser* parser);

}  // namespace openspore::reconstruction::pkg_argscript_format_008414d0

#undef PKG_ARGSCRIPT_FORMAT_THIS_CALL
