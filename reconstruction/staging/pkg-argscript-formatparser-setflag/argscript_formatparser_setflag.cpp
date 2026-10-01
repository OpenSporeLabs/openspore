#include "argscript_formatparser_setflag.hpp"

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_FP_SETFLAG_THIS_CALL __thiscall
#define PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL __stdcall
#elif defined(__clang__)
#define PKG_ARGSCRIPT_FP_SETFLAG_THIS_CALL __attribute__((thiscall))
#define PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL __attribute__((stdcall))
#else
#define PKG_ARGSCRIPT_FP_SETFLAG_THIS_CALL
#define PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_argscript_formatparser_setflag {

float PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL default_parse_number_port(
    OpaqueScanContext* /*self*/, const char** /*cursor*/) {
  return 0.0f;
}

bool PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL default_expect_char_port(
    OpaqueScanContext* /*self*/, const char** /*cursor*/,
    char /*expected*/) {
  return false;
}

ScanPorts& scan_ports() {
  static ScanPorts ports{};
  return ports;
}

float* PKG_ARGSCRIPT_FP_SETFLAG_THIS_CALL
pkg_argscript_formatparser_set_flag_00841540(OpaqueFormatParser* parser,
                                             float* out,
                                             const char** cursor) {
  // 0x00841545/0x0084154c: out[0] = ScanContext::ParseNumber(cursor).
  out[0] = scan_ports().parse_number(&parser->field_04c, cursor);

  // 0x00841555..0x00841557: PUSH 0x2c then FSTP DWORD PTR [EDI]. The store
  // lands before the separator test, so word 0 is always written.
  //
  // 0x00841557 is d9 1f, i.e. opcode D9 with ModRM 0b00_011_111: mod=00,
  // reg=/3, rm=111 -> [EDI]. D9 /3 is FSTP m32fp. GNU objdump, LLVM objdump and
  // the Ghidra listing all render it `fstp DWORD PTR [edi]`. A reading of
  // reg=011 as FSTCW is a decode error: FSTCW is D9 /7 (FNSTCW), and D9 /5 is
  // FLDCW; /3 is FSTP and it pops, which is what balances the PUSH-set x87
  // stack left by 0x0083e470.
  //
  // 0x00841559..0x00841567: if (ScanContext::ExpectChar(cursor, ',')).
  if (scan_ports().expect_char(&parser->field_04c, cursor, ',')) {
    // 0x00841569..0x00841575: out[1] = ScanContext::ParseNumber(cursor).
    // 0x00841575 is d9 5f 04: ModRM 0b01_011_111 with disp8 0x04, again
    // reg=/3 -> FSTP DWORD PTR [EDI+0x4].
    out[1] = scan_ports().parse_number(&parser->field_04c, cursor);
  } else {
    // 0x0084157f..0x00841583: d9 07 is FLD DWORD PTR [EDI] (ModRM
    // 0b00_000_111, reg=/0) followed by d9 5f 04 FSTP DWORD PTR [EDI+0x4].
    // Together they are out[1] = out[0], collapsing the range to a single
    // value. The FLD is balanced by the FSTP, so the x87 stack is empty at
    // both exits and EAX, not ST0, carries the return value.
    out[1] = out[0];
  }

  // 0x00841578 and 0x00841581: MOV EAX,EDI on both exits. The caller reads
  // [EAX] and [EAX+0x4] as two MOVSS floats.
  return out;
}

}

#undef PKG_ARGSCRIPT_FP_SETFLAG_STD_CALL
#undef PKG_ARGSCRIPT_FP_SETFLAG_THIS_CALL
