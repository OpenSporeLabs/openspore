#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-argscript-formatparser-setflag requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "target words are 32-bit");

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_FP_SETFLAG_THIS_CALL __thiscall
#define PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL __stdcall
#define PKG_ARGSCRIPT_FP_SETFLAG_CALLER_NOTE \
  "built as a true thiscall: ECX carries the receiver"
#elif defined(__clang__)
#define PKG_ARGSCRIPT_FP_SETFLAG_THIS_CALL __attribute__((thiscall))
#define PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL __attribute__((stdcall))
#define PKG_ARGSCRIPT_FP_SETFLAG_CALLER_NOTE \
  "built as a true thiscall: ECX carries the receiver"
#else
// GCC rejects __attribute__((thiscall)) on a free function (-Werror=attributes:
// "'thiscall' attribute is used for non-class method"). The machine receiver is
// genuinely a `this`, but a free function cannot spell that in GCC, so under GCC
// the receiver stays an explicit first parameter and the register assignment is
// not reproduced by the compiler. The ABI claim is carried by the clang and MSVC
// builds; see the metadata sidecar for the call-site proof that backs it.
#define PKG_ARGSCRIPT_FP_SETFLAG_THIS_CALL
#define PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL __attribute__((stdcall))
#define PKG_ARGSCRIPT_FP_SETFLAG_CALLER_NOTE \
  "receiver is an explicit parameter: GCC cannot apply thiscall to a free function"
#endif

namespace openspore::reconstruction::pkg_argscript_formatparser_setflag {

// Sub-object addressed at this+0x4c (LEA ESI,[ECX+0x4c] at 0x00841542).
// 0x00841540 passes &field_04c as the ECX `self` of both ports and never
// dereferences it itself, so no field of this sub-object is read or written by
// the target. Only its address is observable; its real width and layout are
// unresolved, so a single opaque word stands in for it.
//
// The member NAME below is reconstruction-asserted and is NOT machine
// corroborated: the knowledge index carries `types.FormatParser` with an empty
// `fields` array, and Ghidra reports `class_namespace_exists: false` for
// FormatParser, so no struct layout exists anywhere in the corpus against which
// `field_04c` could be checked. Only the DISPLACEMENT 0x4c is machine-observed,
// and it is observed twice: as the LEA disp8 in this body, and as the receiver
// that the caller at 0x0082fdd9 loads into ECX before the call.
struct OpaqueScanContext {
  std::uint32_t opaque_word = 0;
};

// Prefix-only model of ArgScript::FormatParser. The total object size and every
// field other than the +0x4c sub-object are unresolved; the bytes below the
// prefix are deliberately absent rather than invented.
struct OpaqueFormatParser {
  std::array<std::uint8_t, 0x4c> field_000{};
  OpaqueScanContext field_04c{};
};

static_assert(offsetof(OpaqueFormatParser, field_04c) == 0x4c,
              "scan sub-object offset");

// Unresolved dependency ports. Neither VA is owned by this package and neither
// is promoted to a function record; they are package-local function pointers so
// the target's control flow can be exercised without inventing their bodies.
//
// 0x0083e470 ends in RET 0x4 -> __stdcall, one stack argument. It reads the
// cursor's char pointer, accumulates a value and returns it in ST0.
// 0x0083d290 ends in RET 0x8 -> __stdcall, two stack arguments. It skips
// leading space via 0x0083ce90, returns false on an exhausted string, and
// otherwise consumes exactly one character and returns true.
using ParseNumberFn = float(PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL*)(
    OpaqueScanContext* self, const char** cursor);
using ExpectCharFn = bool(PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL*)(
    OpaqueScanContext* self, const char** cursor, char expected);

float PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL default_parse_number_port(
    OpaqueScanContext* self, const char** cursor);
bool PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL default_expect_char_port(
    OpaqueScanContext* self, const char** cursor, char expected);

// Package-local port table. Assign before calling the model when real scanner
// behaviour is required. The defaults are inert and shape preserving: neither
// advances the cursor nor consumes input, and ParseNumber yields +0.0f.
struct ScanPorts {
  ParseNumberFn parse_number;
  ExpectCharFn expect_char;
  ScanPorts()
      : parse_number(&default_parse_number_port),
        expect_char(&default_expect_char_port) {}
};

ScanPorts& scan_ports();

// ArgScript::FormatParser::SetFlag, VA 0x00841540.
//
// Calling convention is __thiscall, and it is proved at the call edge rather
// than assumed from the body. The single call site, in the caller 0x0082f9a0:
//
//   0x0082fdd0  PUSH ESI                ; stack word 1 (cursor)
//   0x0082fdd1  LEA EDX,[ESP+0xe0]      ; stack word 0 (out), a caller stack slot
//   0x0082fdd8  PUSH EDX
//   0x0082fdd9  LEA ECX,[ESP+0x168]     ; receiver, a caller stack sub-object
//   0x0082fde0  CALL 0x00841540
//   0x0082fde5  MOVSS XMM0,dword ptr [EAX]      ; out[0]
//   0x0082fde9  MOVSS XMM1,dword ptr [EAX+0x4]  ; out[1]
//
// The caller pushes exactly two words and the callee retires with RET 0x8, so
// the stack accounts for two arguments and nothing else; the receiver is loaded
// into ECX and never pushed. __stdcall cannot explain that shape, because
// __stdcall passes every argument on the stack, so an ECX-borne receiver would
// have to be a third stack word that RET 0x8 does not account for. The same
// two MOVSS reads confirm the return value is a pointer to two consecutive
// 32-bit floats, not an x87 ST0 result.
float* PKG_ARGSCRIPT_FP_SETFLAG_THIS_CALL
pkg_argscript_formatparser_set_flag_00841540(OpaqueFormatParser* parser,
                                             float* out,
                                             const char** cursor);

}
