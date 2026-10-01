#include "utfwin_settiling_wave13.hpp"

namespace openspore::reconstruction::pkg_utfwin_settiling_wave13 {
namespace {

// Stand-ins for the three absolute addresses the observed accessor 0x011e58c0
// and its initialiser 0x011e5870 touch. Their numeric identity is recorded in
// the header as named constants; the model needs them only so the control flow
// and the returned pointer identity are testable on the host.
OpaqueWord g_init_guard_016f4b08 = 0;
OpaqueWord g_second_guard_016f4b00 = 0;
OpaqueWord g_pointer_slot_016f4af4 = 0;

// First word of the static object. The observed initialiser FUN_011eb950
// writes vtable 0x014f6f80 here, and the atexit thunk FUN_013cb3f0 ->
// FUN_011eb940 writes vtable 0x0140de80 here instead. The model stores the
// former so that "the object is a vtable-bearing static" is observable.
OpaqueWord g_object_storage_016f4afc = 0;

// The observed initialiser, modelled only to the depth the target's own
// behaviour depends on: on first use it publishes the static object, and the
// accessor's pointer slot is left pointing at that object forever after.
void shared_object_initialise_011e5870() {
  if ((g_second_guard_016f4b00 & 1u) == 0u) {
    g_second_guard_016f4b00 |= 1u;
    g_object_storage_016f4afc = kAccessorObjectVTable_014f6f80;
  }
  if (g_pointer_slot_016f4af4 == 0u) {
    g_pointer_slot_016f4af4 = kAccessorObjectStorage_016f4afc;
  }
}

}

// Accessor 0x011e58c0. Zero arguments, caller-cleanup, one dword result: the
// pointer to the process-wide static object. First call runs the initialiser,
// later calls fall straight through to the pointer load.
extern "C" OpaqueWord PKG_UTFWIN_SETTILING_CDECL PKG_UTFWIN_SETTILING_NOINLINE
utfwin_shared_object_accessor_011e58c0() {
  if ((g_init_guard_016f4b08 & 1u) == 0u) {
    g_init_guard_016f4b08 |= 1u;
    shared_object_initialise_011e5870();
  }
  return g_pointer_slot_016f4af4;
}

// 0x00fd9460. Two dword stores into the receiver, in this order, with the
// accessor's result going to +0x08 and the incoming argument going to +0x04.
// Nothing else in the receiver is read or written, and no value is returned.
//
// The two stores are written as DISPLACEMENTS into an opaque receiver, not as
// member accesses. What the machine-derived receiver record carries for this
// target is the set of displacements the body was seen using through ECX --
// 0x04 and 0x08 -- and that is all it carries: `bounds_only` is set, and a set
// of displacements says where the body reached, never which member occupies
// each of those offsets. Naming a member here would therefore assert a field
// identity that no machine record corroborates, so the member names live only
// in the model test's observation surface (see the header) and never in the
// reconstructed body.
extern "C" void PKG_UTFWIN_SETTILING_THISCALL
set_tiling_00fd9460(OpaqueSetTilingReceiverWire *self, OpaqueWord tiling) {
  // 0x00fd9460  MOV EAX,dword ptr [ESP + 0x4]  `tiling` arrives in EAX
  // 0x00fd9464  PUSH ESI / 0x00fd9465  MOV ESI,ECX  the receiver is aliased
  auto *const receiver = reinterpret_cast<unsigned char *>(self);

  // 0x00fd9467  MOV dword ptr [ESI + 0x4], EAX
  *reinterpret_cast<volatile OpaqueWord *>(receiver + 0x04) = tiling;

  // 0x00fd946a  CALL 0x011e58c0   the only call in the body
  const OpaqueWord shared = utfwin_shared_object_accessor_011e58c0();

  // 0x00fd946f  MOV dword ptr [ESI + 0x8], EAX   the callee's result, verbatim
  *reinterpret_cast<volatile OpaqueWord *>(receiver + 0x08) = shared;

  // 0x00fd9472  POP ESI
  // 0x00fd9473  RET 0x4   the callee pops the 4-byte argument word itself
  //
  // Not observable in the receiver, and deliberately not asserted by the model
  // test: the relative order of the two stores. The callee is handed no pointer
  // into the receiver, so no post-state distinguishes "store, call, store" from
  // "call, store, store". The listing fixes the order and this body follows it;
  // the test pins what is observable (which value lands at which displacement,
  // and that no other byte moves) and stops there.
}

}
