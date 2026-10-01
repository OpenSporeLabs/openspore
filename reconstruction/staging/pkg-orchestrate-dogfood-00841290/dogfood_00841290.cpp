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
// RE: The dispatch is written as two DISPLACEMENTS rather than as member
// accesses. The machine-derived receiver record for this target enumerates the
// displacements the body was seen using through ECX -- 0x00 and 0x3c -- with
// `bounds_only` set, and that is all it carries: a set of displacements says
// where the body reached, never which member occupies an offset, and the record
// follows the ECX alias into the second load, which is why it enumerates 0x3c
// even though no instruction names ECX there. Naming a member of the receiver
// would assert a field identity no machine record corroborates, so the wire
// struct in the header exists for the model test's observation surface and is
// never named from this body.
extern "C" bool PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
argscript_formatparser_release_00841290(OpaqueFormatParser* parser,
                                        OpaqueWord argument_08) {
  auto *const receiver = reinterpret_cast<unsigned char *>(parser);

  // 0x008412a9  MOV EAX,dword ptr [ECX]     the receiver word at displacement 0x00
  auto *const table = reinterpret_cast<unsigned char *>(
      *reinterpret_cast<const OpaqueWord *>(receiver + 0x00));

  // 0x008412ae  MOV EAX,dword ptr [EAX+0x3c]  the code word at displacement
  // 0x3c of THAT object, not of the receiver: two dereferences, in this order.
  const auto slot = reinterpret_cast<FormatParserReleaseSlot3c>(
      *reinterpret_cast<const OpaqueWord *>(table + 0x3c));

  // 0x008412ab  MOV EDX,dword ptr [EBP+0x8]  the one incoming stack word
  // 0x008412b1..0x008412b4  PUSH EBX/ESI/EDI, MOV [EBP-0x10],ESP  frame churn
  // 0x008412b7  PUSH EDX                     it is forwarded to the slot
  // 0x008412b8  MOV dword ptr [EBP-0x4],0x0  the SEH scope state word, never set
  // 0x008412bf  CALL EAX                     the slot, entered with the
  //                                           UNMODIFIED receiver still in ECX
  //                                           (0x008412a9 read ECX, never wrote
  //                                           it) and its result discarded
  slot(parser, argument_08);

  // 0x008412c1  MOV AL,0x1                   the result is a constant true, not
  //                                           the slot's return value
  // 0x008412c3..0x008412d0  POP EDI/ESI/EBX, MOV ESP,EBP, POP EBP
  return true;
}

}

#undef PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
