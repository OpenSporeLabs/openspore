#include "editor_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_EDITOR_SAFE_THISCALL __thiscall
#else
#define PKG_EDITOR_SAFE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_safe_wave10 {

// 005a2010  CMP  byte ptr [ESP + 0x10],0x0
// 005a2015  MOV  EAX,dword ptr [ESP + 0x4]
// 005a2019  MOV  EDX,dword ptr [ESP + 0x8]
// 005a201d  PUSH ESI
// 005a201e  MOV  ESI,dword ptr [ESP + 0x10]
// 005a2022  MOV  dword ptr [ECX + 0x80],EAX
// 005a2028  MOV  dword ptr [ECX + 0x84],EDX
// 005a202e  MOV  dword ptr [ECX + 0x88],ESI
// 005a2034  JZ   0x005a203f
// 005a2036  MOV  dword ptr [ECX + 0x74],EAX
// 005a2039  MOV  dword ptr [ECX + 0x78],EDX
// 005a203c  MOV  dword ptr [ECX + 0x7c],ESI
// 005a203f  POP  ESI
// 005a2040  RET  0x10
//
// Three formals are loaded into EAX, EDX and ESI and each is stored twice at
// most; the gate is one byte of the fourth formal.  EAX and EDX are read before
// the PUSH, so the three row words are all loaded off the argument block and
// not out of the receiver: nothing in the body reads the receiver, and a
// displacement in a store is not an index and is never re-read.
//
// The receiver record is `bounds_only`, so the six stores below are written as
// the displacements the listing prints and no member is named: the machine
// proves where the body reached, not what lives there.  The stores are plain
// 4-byte moves, so the bit patterns of the formals arrive untouched.
void PKG_EDITOR_SAFE_THISCALL
editor_row_publish_005a2010(RowPublisherExtent* self, Real row_x, Real row_y,
                            Real row_z, Word also_previous) {
  std::uint8_t* const reach = reinterpret_cast<std::uint8_t*>(self);
  *reinterpret_cast<Real*>(reach + 0x80) = row_x;  // 005a2022 [ECX + 0x80],EAX
  *reinterpret_cast<Real*>(reach + 0x84) = row_y;  // 005a2028 [ECX + 0x84],EDX
  *reinterpret_cast<Real*>(reach + 0x88) = row_z;  // 005a202e [ECX + 0x88],ESI
  if (gate_low_byte(also_previous) != 0u) {       // 005a2010 / 005a2034 JZ
    *reinterpret_cast<Real*>(reach + 0x74) = row_x;  // 005a2036 [ECX + 0x74],EAX
    *reinterpret_cast<Real*>(reach + 0x78) = row_y;  // 005a2039 [ECX + 0x78],EDX
    *reinterpret_cast<Real*>(reach + 0x7c) = row_z;  // 005a203c [ECX + 0x7c],ESI
  }
}

}

#undef PKG_EDITOR_SAFE_THISCALL
