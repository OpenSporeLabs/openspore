#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-EDITOR-ADC40-SMOKE01 requires an x86-32 target"
#endif

// The convention token is carried by a macro so the declaration names it once.
// The validator resolves a #define to its convention token, so the entry point
// still counts as declaring a convention.
#if defined(_MSC_VER)
#define PKG_EDITOR_ADC40_SMOKE01_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_ADC40_SMOKE01_THISCALL __attribute__((thiscall))
#else
#error "PKG-EDITOR-ADC40-SMOKE01 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_adc40_smoke01 {

using Byte = std::uint8_t;

// The one machine-derived fact the body carries: a byte-wide load at
// receiver+0x4f, i.e. MOV AL, byte ptr [EAX + 0x4f] at 0x004adc4a.
static_assert(sizeof(Byte) == 1, "the load at 0x004adc4a is byte-wide");
static_assert(sizeof(void*) == 4, "this package targets 32-bit pointers");

// Receiver layout, modelled only as far as the body reads. Bytes below 0x4f are
// unmodelled padding; everything at or above 0x50 is outside the claimed extent.
//
// No SDK class is named. Ghidra names two of the 64 direct callers
// (Editors::cEditor::sub_581F70, Editors::cEditor::OnMouseDown), but the sampled
// call sites take the receiver from a +0x28 member of the caller's own object and
// from a stack local, so nothing corroborates one concrete receiver type.
struct alignas(4) OpaqueEditorFlag {
  Byte opaque_000[0x4f];
  Byte byte_04f;
};

static_assert(offsetof(OpaqueEditorFlag, byte_04f) == 0x4f,
              "0x004adc4a reads receiver+0x4f");

// 0x004adc40: 17 bytes, 9 instructions, one basic block, no callee, no branch,
// no write, no guard. The receiver arrives in ECX, the result is the single byte
// at receiver+0x4f, and the body ends in a bare RET (0xc3) with no immediate, so
// there is no stack argument and the caller owns stack cleanup.
extern "C" Byte PKG_EDITOR_ADC40_SMOKE01_THISCALL
FUN_004adc40(OpaqueEditorFlag* self);

}  // namespace openspore::reconstruction::pkg_editor_adc40_smoke01

#undef PKG_EDITOR_ADC40_SMOKE01_THISCALL
