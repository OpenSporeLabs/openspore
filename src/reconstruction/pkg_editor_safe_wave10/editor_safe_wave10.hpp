#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-editor-safe-wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_EDITOR_SAFE_THISCALL __thiscall
#else
#define PKG_EDITOR_SAFE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_safe_wave10 {

using Word = std::uint32_t;
using Real = float;

static_assert(sizeof(void*) == 4, "x86-32 pointers are four bytes");
static_assert(sizeof(Word) == 4, "the gate formal occupies one stack word");
static_assert(sizeof(Real) == 4, "each row component is a 32-bit float");

// ---------------------------------------------------------------------------
// The receiver.
//
// 005a2010 reaches ECX at exactly six displacements and at no others:
//
//   005a2022  MOV dword ptr [ECX + 0x80],EAX     first  primary word
//   005a2028  MOV dword ptr [ECX + 0x84],EDX     second primary word
//   005a202e  MOV dword ptr [ECX + 0x88],ESI     third  primary word
//   005a2036  MOV dword ptr [ECX + 0x74],EAX     first  mirrored word
//   005a2039  MOV dword ptr [ECX + 0x78],EDX     second mirrored word
//   005a203c  MOV dword ptr [ECX + 0x7c],ESI     third  mirrored word
//
// The machine-derived receiver record carrying those six is ``bounds_only``:
// it states where the body was seen reaching and says nothing about which
// member is which.  So this header declares no member and no sub-object, and
// every access is written as the displacement the listing prints.
// ``RowPublisherExtent`` is the *minimum* object consistent with the observed
// accesses -- a 4-byte word at the largest displacement the body touches -- and
// no claim is made about anything past that word, nor about anything in the
// body that is not one of the six stores.
// ---------------------------------------------------------------------------

constexpr std::size_t kPublisherExtentBytes = 0x8c;
static_assert(kPublisherExtentBytes == 0x88 + sizeof(Real),
              "the observed extent ends after the 4-byte word at +0x88");

struct RowPublisherExtent {
  std::uint8_t bytes[kPublisherExtentBytes];
};

// `CMP byte ptr [ESP + 0x10],0x0` / `JZ 0x005a203f`.
//
// The compare is BYTE-SIZED, so the body inspects the low byte of the fourth
// formal and skips the mirrored row when that byte is zero.  The formal itself
// is a 4-byte stack word -- `RET 0x10` releases sixteen bytes for four
// arguments -- so the body tests a byte *of* a word, not the word.  A 32-bit
// mask would be a different instruction: the listing contains no such mask.
inline std::uint8_t gate_low_byte(Word also_previous) {
  return static_cast<std::uint8_t>(also_previous);
}

void PKG_EDITOR_SAFE_THISCALL
editor_row_publish_005a2010(RowPublisherExtent* self, Real row_x, Real row_y,
                            Real row_z, Word also_previous);

}

#undef PKG_EDITOR_SAFE_THISCALL
