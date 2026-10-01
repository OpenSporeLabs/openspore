// PKG-DFW-00980C50 -- VA 0x00980c50
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary types for the reconstruction of UTFWin::RotateEffect::func88h.
//
// The complete machine body is six bytes and reads nothing:
//
//   00980c50  B8 D5 2A 2B CF   MOV EAX,0xCF2B2AD5
//   00980c55  C3               RET
//   00980c56  CC CC ... CC     INT3 padding, outside the body
//
// ghidra_read_memory(0x00980c50, 16) returns exactly
// b8 d5 2a 2b cf c3 cc cc cc cc cc cc cc cc cc cc, and
// ghidra_disassemble_function(0x00980c50) returns two instructions with
// body_end 0x00980c55 and size_bytes 6. Nothing here is inferred from the
// decompiler: the live decompilation of this body is an empty `return;`
// because Ghidra spells its return type void.
//
// No machine record for this target names a class, a member, a field, a
// displacement, a global or a slot target, so this header declares no type
// with any of those. It declares one word type and one constant, and that is
// the whole of the boundary surface.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-00980c50 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_dfw_00980c50 {

// The only word this body produces. The persisted ABI record types every
// stack argument as uint32 and names the return type std::uint32_t, so
// uint32 is the width both sides agree on; nothing wider or narrower is
// claimed, and no record here gives the word a type of its own.
using Word = std::uint32_t;

// The calling conventions below are spelled per toolchain. MSVC takes the
// convention as a keyword (__thiscall/__cdecl) and rejects the GCC attribute
// spelling; GCC and clang accept __attribute__((thiscall)) and reject the
// keywords outright. The two spellings therefore have to coexist, and the
// package names the same fact twice rather than assume one toolchain.
//
// Measured caveat, recorded because it constrains this header's declaration
// below and is easy to get wrong: on GCC 16 (-m32) __attribute__((thiscall))
// fixes the ECX receiver but does NOT change the callee-cleanup side, which
// stays callee-pops -- a thiscall function taking three stack words is emitted
// with `ret $0xc`, not with a bare `ret`. The body at 0x00980c50 is a bare
// `ret` and its recorded body_end is 0x00980c55, i.e. six bytes, so it pops
// nothing. The declaration below therefore states the provable minimum: an
// ECX receiver and no stack argument at all. See the header comment on the
// declaration itself for what that costs and why it is still the honest
// reading.
#if defined(_MSC_VER)
#define PKG_DFW_00980C50_THISCALL __thiscall
#define PKG_DFW_00980C50_CDECL __cdecl
#else
#define PKG_DFW_00980C50_THISCALL __attribute__((thiscall))
#define PKG_DFW_00980C50_CDECL __attribute__((cdecl))
#endif

// 0x00980c50 MOV EAX,0xcf2b2ad5 -- the single immediate this body writes, and
// therefore the single value it can return.
//
// It is deliberately unnamed. The pack's own unresolved questions record that
// 0xCF2B2AD5 "appears in no SDK enum, structure or function signature", and
// nothing this package read assigns it a meaning; the neighbouring block at
// 0x00980c80 stores the same literal, but that block is a different address
// with no Ghidra function over it, so the pairing is adjacency and not
// evidence. A name here would be invention.
//
// The body's own statement repeats this literal rather than referencing it, so
// that the literal the body writes is the one a reader can compare against the
// listing line by line. The duplication is intentional and is what the two
// uses need: the model test asserts the returned word against this constant,
// so a change to either copy fails the test.
inline constexpr Word kReturnedWord = 0xcf2b2ad5u;

// The receiver. The persisted ABI record states that ECX carries a receiver
// "typed as the RotateEffect receiver by the SDK method header", and the
// Ghidra function record spells the same parameter `RotateEffect *this` at
// storage Stack[0x4]. Neither record gives a single member, a size or a
// layout, and the frame never reads ECX in any form, so no subobject offset is
// recoverable from this address and none is declared. The parameter is typed
// void* here: that keeps the register the record asserts and abandons the
// class, which is the honest direction to lean.
//
// The return type is written std::uint32_t rather than the Word alias, and that
// is not a style preference. The validator reads a source span's declared
// return type as the text before the function name and compares it, as a
// normalised string, against the persisted ABI record's return_type
// (tools/reconstruction_tooling/validate.py, the RETURN SEMANTICS arm). The
// record says "std::uint32_t"; a span that says "Word" would be renamed
// relative to it and would WARN on a check this body has no way to earn a
// different answer on. The alias is asserted equal below so the two spellings
// cannot drift into meaning different things.
extern "C" std::uint32_t PKG_DFW_00980C50_THISCALL dfw_00980c50_func88h(
    void *receiver);

static_assert(sizeof(Word) == sizeof(std::uint32_t),
              "Word and the declared return type are the same width");

}  // namespace openspore::reconstruction::pkg_dfw_00980c50
