#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-EDITOR-ADC40-FLAG requires an x86-32 target"
#endif

// The convention token is carried by a macro, exactly once, so the declaration
// names it once instead of repeating a compiler keyword at every entry point.
#if defined(_MSC_VER)
#define PKG_EDITOR_ADC40_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_ADC40_THISCALL __attribute__((thiscall))
#else
#error "PKG-EDITOR-ADC40-FLAG requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_adc40_flag {

using Byte = std::uint8_t;
using Field = std::uint8_t;

static_assert(sizeof(void*) == 4,
              "editor adc40 flag requires 32-bit pointers");
static_assert(sizeof(Field) == 1,
              "the observed load at 0x004adc4a is byte-wide");

// The receiver layout carries exactly one machine-derived fact: the single
// byte the body reads, at 0x4f. Everything below 0x4f is unmodelled padding
// and everything the object may hold above 0x4f is outside the extent this
// package claims.
//
// No SDK type is named. Ghidra names two of the direct callers
// Editors::cEditor::sub_581F70 and Editors::cEditor::OnMouseDown, but the
// sampled call sites load the receiver from a +0x28 member of the caller's own
// object and from a stack local, so the receiver is a general opaque object
// pointer and no concrete class is corroborated.
struct alignas(4) OpaqueEditorFlag {
  Byte opaque_000[0x4f];
  Byte byte_04f;
};

static_assert(offsetof(OpaqueEditorFlag, byte_04f) == 0x4f,
              "0x004adc4a reads receiver+0x4f");

// 0x004adc40: 17 bytes, 9 instructions, one basic block, no callee, no
// branch, no write, no guard. The receiver arrives in ECX, the result is the
// single byte at receiver+0x4f, and the body ends in a bare RET, so there is
// no stack argument and the caller owns stack cleanup.
extern "C" Field PKG_EDITOR_ADC40_THISCALL
FUN_004adc40(OpaqueEditorFlag* self);

}  // namespace openspore::reconstruction::pkg_editor_adc40_flag

#undef PKG_EDITOR_ADC40_THISCALL
