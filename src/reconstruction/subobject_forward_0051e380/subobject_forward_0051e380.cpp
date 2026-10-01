// Bounded reconstruction of the body of SporeApp.exe 0x0051e380. Every line
// below is read off the ten-instruction listing quoted in the header; the
// address in each comment is the instruction it models. Nothing is inferred
// from behaviour, and the body writes no memory at all.

#include "subobject_forward_0051e380.hpp"

// The header #undefines its convention macro at the end of the include guard;
// the definition below restores it for this translation unit.
#if defined(_MSC_VER)
#define PKG_SUBFWD_THISCALL __thiscall
#else
#define PKG_SUBFWD_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::subobject_forward_0051e380 {

// Production wiring points this at a Ports holding the real 0x00453540 entry.
// It starts null so an unwired call faults instead of transferring to a
// garbage address; the model test sets it before the single call it makes.
Ports* g_subobject_forward_ports = nullptr;

// 0x0051e380  PUSH EBP / 0x0051e381 MOV EBP,ESP / 0x0051e383 SUB ESP,0x10
//   the frame. The compiler establishes and tears it down around the call.
// 0x0051e386  MOV dword ptr [EBP-0x10],ECX / 0x0051e389 MOV ECX,dword ptr
//   [EBP-0x10] / 0x0051e38c ADD ECX,0x4
//   the receiver is spilled and reloaded, then adjusted by kSubobjectAdjustor;
//   the callee's receiver is the subobject at receiver+0x4, never the receiver
//   itself.
// 0x0051e38f  CALL 0x00453540
//   the body's only transfer: a direct call, no stack argument pushed, the
//   receiver arriving in ECX.
// 0x0051e394  MOV ESP,EBP / 0x0051e396 POP EBP / 0x0051e397 RET
//   the bare RET returns whatever the callee left in EAX.
extern "C" std::uint32_t PKG_SUBFWD_THISCALL subobject_forward_0051e380(
    OpaqueReceiver* self) {
  return g_subobject_forward_ports->decrement_00453540(adjusted_this(self));
}

}  // namespace openspore::reconstruction::subobject_forward_0051e380
