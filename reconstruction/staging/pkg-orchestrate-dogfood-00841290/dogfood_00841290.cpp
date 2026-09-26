#include "dogfood_00841290.hpp"

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-00841290 needs MSVC or GCC CC macros"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_00841290 {

OpaqueReleasePorts g_dogfood_00841290_ports{};

// RE: 0x00841290 has no ABI projection in the briefing; the contract below is
// derived from the 27-instruction disassembly at 0x00841290..0x008412d3.
// RE: 0x008412a9 MOV EAX,[ECX] and 0x008412ae MOV EAX,[EAX+0x3c] load the
// receiver's vtable word and then vtable index 15. ECX is not reloaded, so the
// slot is entered with the unmodified receiver in ECX.
// RE: 0x008412ab MOV EDX,[EBP+0x8] and 0x008412b7 PUSH EDX forward the single
// incoming stack word to the slot; 0x008412d3 RET 0x4 proves one four-byte
// caller-pushed slot cleaned by the callee.
// RE: 0x008412bf CALL EAX is the only call. No direct callee exists and the
// returned EAX is never read, so the slot's return value is discarded.
// RE: 0x008412c1 MOV AL,0x1 makes the result a constant true.
// RE: The EBX/ESI/EDI push-pop pairs (0x008412b1..0x008412b3 and
// 0x008412cd..0x008412cf) are compiler frame churn with no semantic effect, and
// the FS:[0x0] chain installed at 0x00841293..0x008412a1 is the SEH scope
// record for an unwind handler at 0x01217640 whose state word at [EBP-4] is
// written 0 at 0x008412b8 and never set again. Ghidra defines no function at
// 0x01217640, so the unwind path is left unmodeled and gated in the sidecar.
extern "C" bool PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
argscript_formatparser_release_00841290(OpaqueFormatParser* parser,
                                        OpaqueWord argument_08) {
  parser->vtable->release_3c(parser, argument_08);
  return true;
}

}

#undef PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
