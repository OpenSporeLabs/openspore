#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-argscript-wave9 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "the loaded word is 32-bit");

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_WAVE9_THIS_CALL __thiscall
#else
#define PKG_ARGSCRIPT_WAVE9_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_wave9 {

// ---------------------------------------------------------------------------
// The receiver.
//
// The whole of 00d1dcd0 is:
//
//   00d1dcd0  MOV EAX,dword ptr [ECX + 0x130]
//   00d1dcd6  RET
//
// One 4-byte word is read through ECX, at displacement 0x130, and nothing is
// written.  The machine-derived receiver record agrees exactly: register ECX,
// ``bounds_only``, ``distinct_offsets: 1``, ``offsets: [0x130]``,
// ``written_through: 0``.
//
// ``bounds_only`` means the record states where the body was seen reaching and
// nothing about which member is which, so this header names no member, declares
// no sub-object and asserts no layout.  ``ParserExtent`` is the *minimum* object
// the single observed access fits in -- a 4-byte word at 0x130 -- and is not a
// claim about the size of the real receiver: the body reads one word and gives
// no evidence about anything past it.  In particular there is no evidence here
// for a string, a length, a capacity or an allocator living at that word, and
// none is declared.
// ---------------------------------------------------------------------------

constexpr std::size_t kParserExtentBytes = 0x134;
static_assert(kParserExtentBytes == 0x130 + sizeof(std::uint32_t),
              "one 4-byte word at displacement 0x130, and nothing further");

struct ParserExtent {
  std::uint8_t bytes[kParserExtentBytes];
};

// The body returns that word, and the canonical ABI record for this target
// types it `char *` with the value travelling in EAX across a plain `RET`.
// `char *` is that record's claim and is reproduced here for agreement; the
// machine establishes the width (a dword in EAX) and not the element type.
char* PKG_ARGSCRIPT_WAVE9_THIS_CALL
pkg_argscript_get_current_scope_00d1dcd0(ParserExtent* parser);

}

#undef PKG_ARGSCRIPT_WAVE9_THIS_CALL
