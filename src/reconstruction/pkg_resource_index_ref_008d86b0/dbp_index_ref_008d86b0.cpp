#include "dbp_index_ref_008d86b0.hpp"

namespace openspore::reconstruction::pkg_resource_index_ref_008d86b0 {

#if defined(_MSC_VER)
#define OPENSPORE_INDEX_REF_THISCALL __thiscall
#else
#define OPENSPORE_INDEX_REF_THISCALL __attribute__((thiscall))
#endif

// VA 0x008d86b0, instructions at 0x008d86b0 (6 bytes) and 0x008d86b6 (1 byte),
// followed by INT3 padding at 0x008d86b7.
//
// The whole body is a single 32-bit load out of the receiver followed by a
// return. There is no test, no branch and no call, so the emitted code for
// this definition on x86-32 is byte-identical to the original:
//
//   8B 81 60 02 00 00   MOV EAX, dword ptr [ECX + 0x260]
//   C3                  RET
//
// (verified: clang++ -m32 -O2 -std=c++17 -c on this file yields exactly
//  8b 81 60 02 00 00  c3  for the entry symbol).
//
// The load is written as a DISPLACEMENT into the opaque carrier, not as
// `file->index_ref`. The machine-derived receiver record for this VA enumerates
// offsets=[0x260] and is bounds_only, so it states where the body reached and
// not which member it found there; a member name on this line would be a field
// identity with nothing behind it. What the listing does establish, and what this
// definition reproduces, is the width (4 bytes), the displacement (0x260 under
// ECX), the direction (read only) and the absence of any test on the value.
//
// Ownership: the value is handed back raw. The adjacent vtable slot +0x50
// (0x008d86c0) is the paired writer - it AddRefs the incoming pointer, stores
// it at +0x260 and Releases the outgoing one - so the field is a non-owning
// handle and the caller of this accessor inherits no reference. Adding an
// AddRef here would be a semantic invention; the machine does not do it, and
// the model test pins that by giving the pointee a live refcount ledger and
// asserting it stays empty.
ObservedIndexObject* OPENSPORE_INDEX_REF_THISCALL destroy_index_008d86b0(
    ObservedIndexRefCarrier* file) {
  return reinterpret_cast<ObservedIndexObject*>(
      *reinterpret_cast<const std::uint32_t*>(
          reinterpret_cast<const std::uint8_t*>(file) + 0x260));
}

#undef OPENSPORE_INDEX_REF_THISCALL

}
