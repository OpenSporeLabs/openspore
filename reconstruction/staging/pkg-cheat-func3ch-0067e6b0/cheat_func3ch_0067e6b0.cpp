#include "cheat_func3ch_0067e6b0.hpp"

#if defined(_MSC_VER)
#define PKG_CHEAT3_THISCALL __thiscall
#else
#define PKG_CHEAT3_THISCALL __attribute__((thiscall))
#endif

// 0x0067e6b0, instruction by instruction:
//
//   PUSH ESI                       ; the only callee-save; no EBP frame
//   MOV ESI,ECX                    ; ESI = the receiver, and stays it to the end
//   CALL 0x0067e2b0                ; thiscall, receiver in ECX, no stack arg
//   TEST byte ptr [ESP+0x8],0x1    ; entry_ESP+0x4, the low byte only
//   JZ   0x0067e6c8                ; bit 0 clear: skip the submit, fall to the epilogue
//   PUSH ESI                       ; the receiver is also the submit argument
//   CALL 0x00f47380                ; cdecl, one stack argument
//   ADD ESP,0x4                    ; the caller drops it
//   MOV EAX,ESI                    ; EAX = the receiver on the only exit path
//   POP ESI
//   RET 0x4                        ; the callee reclaims the gate word
//
// The gate word is tested AFTER the first call, so the order of the two
// callees is load-bearing: the teardown always runs, and the submit runs after
// it, never before.
//
// Both callees are reached through the port table so the model test can
// substitute stubs; each field name carries the callee VA the listing shows.

namespace openspore::reconstruction::pkg_cheat_func3ch_0067e6b0 {

Ports* g_cheat_func3ch_ports = nullptr;

extern "C" CheatManager* PKG_CHEAT3_THISCALL func3_ch_0067e6b0(
    CheatManager* manager, OpaqueWord gate_word) {
  Ports& ports = *g_cheat_func3ch_ports;

  // Unconditional: there is no gate on this call in the listing.
  ports.teardown_0067e2b0(manager);

  // 0x0067e6b8 tests bit 0 of the low byte and nothing else, so bits 1..31 of
  // the word are inert here however the callees treat them.
  if (gate_word & kGateMask) {
    ports.submit_00f47380(manager);
  }

  // 0x0067e6c8: EAX receives the receiver, on both the taken and the untaken
  // branch. The SDK signature declares void; the machine does not agree, and
  // the machine is what this file reconstructs.
  return manager;
}

}

#undef PKG_CHEAT3_THISCALL
