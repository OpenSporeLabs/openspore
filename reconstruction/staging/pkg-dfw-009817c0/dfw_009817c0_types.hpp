// PKG-DFW-009817C0 -- VA 0x009817c0
// UTFWin cluster (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Declarations for the reconstruction of the body the queue record names
// UTFWin::ScrollbarDrawable::SetImage. Read the .cpp header block before using
// any name here: the record's symbol is a binding label and is NOT what the
// machine body does.
//
// Every type below is a type the record already states. The evidence pack's
// `types` category for this target lists exactly two -- uint32_t and void* --
// and those are the only two this header uses. No class, no member, no field
// and no pointee is declared, because no record for this target names one.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-009817c0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. MSVC spells them as
// keywords (__thiscall/__cdecl) while GCC 16 rejects those keywords outright and
// accepts only the __attribute__ form, so the two spellings are kept side by side
// and the package names the macro.
//
// Only PKG_DFW_009817C0_THISCALL is used by this package's two declarations; the
// cdecl spelling is defined because it is the alternative a reader of this body
// has to rule out, and because the machine-derived record does. See the
// calling-convention paragraph in the .cpp for which half of the convention the
// machine proves and which half it does not.
#if defined(_MSC_VER)
#define PKG_DFW_009817C0_THISCALL __thiscall
#define PKG_DFW_009817C0_CDECL __cdecl
#else
#define PKG_DFW_009817C0_THISCALL __attribute__((thiscall))
#define PKG_DFW_009817C0_CDECL __attribute__((cdecl))
#endif

// Scoped opt-out for one warning, and only where this package needs it.
//
// GCC's -Wpedantic objects to a `thiscall` attribute on a non-class function:
// "'thiscall' attribute is used for non-class method". The model here is
// deliberately a free function, because no record for this target names an owning
// class -- inventing one would be a worse claim than modelling the receiver as an
// opaque pointer. The attribute is still applied, and it is not cosmetic: on
// x86-32 it is what makes the callee-cleaned 4-byte stack cleanup and the ECX
// receiver real machine behaviour in the compiled model rather than something
// asserted only in a comment. So the warning is suppressed for exactly the
// declarations and definitions that carry the attribute, and for nothing else.
//
// (The mandated build line, -Wall -Wextra -Werror, does not include -Wpedantic and
// is clean without this. It is here so that the package is also clean under the
// -Wpedantic compile gate the sibling packages use.)
#if defined(__GNUC__) && !defined(__clang__) && !defined(_MSC_VER)
#define PKG_DFW_009817C0_MODEL_BEGIN \
  _Pragma("GCC diagnostic push")     \
  _Pragma("GCC diagnostic ignored \"-Wattributes\"")
#define PKG_DFW_009817C0_MODEL_END _Pragma("GCC diagnostic pop")
#else
#define PKG_DFW_009817C0_MODEL_BEGIN
#define PKG_DFW_009817C0_MODEL_END
#endif

namespace openspore::reconstruction::pkg_dfw_009817c0 {

// The single ordinary stack argument, and the record's own spelling for it.
//
// The record's abi category calls this argument "hash" and types it uint32_t at
// entry_ESP+0x4, with the role text "32-bit comparison key, tested against four
// CMP immediates and never masked, widened or used as an index". The name and
// the type are the record's; the local spelling below is the same width, so no
// claim is added. What the name is NOT evidence of is that the value is a hash of
// anything: the body only ever compares it for equality, and no record here says
// what produces these four constants.
using Word = std::uint32_t;

// The two keys this body answers itself. Named here so the test can assert the
// branch boundaries at each constant and at constant +/- 1 without restating the
// immediates, and so nothing in the package has to invent a name for what the
// constants are: the record supplies the numbers and the comparison, and says
// nothing about their origin.
constexpr Word kKeyLocalPlus4 = 0xeec58382u;
constexpr Word kKeyLocalPlus12 = 0xeef3af8cu;

// The return word, spelled exactly as the record spells it.
//
// The persisted abi category for this target gives return_type "void*" and
// return_register EAX with return_width_bytes 4, and the machine agrees that
// EAX is written on every path (LEA EAX,[ECX+0x4], LEA EAX,[ECX+0xc],
// XOR EAX,EAX). void* is the weakest pointer spelling available and no pointee
// is claimed: the body takes the receiver's address and offsets it, and never
// dereferences it. See the honest tension recorded in the .cpp: the
// machine-derived sub-record classifies the same word as "integral_in_EAX", so
// the two machine records disagree about the word's category and the persisted
// one is followed here because it is the one the queue record publishes.
//
// This spelling is deliberately unspaced ("void*", not "void *"). A spaced
// spelling is the same token to a reader and a different token to the source-span
// resolver, which admits the return type as one unspaced run; a reformat that
// inserted the space would silently yield zero function spans for this VA.

// 0x009817c0. Callee-cleaned, one 4-byte stack word, receiver in ECX.
//
//   receiver -- the word the body tests at 0x009817db/0x009817e5 and offsets at
//               0x009817df/0x009817e9. Opaque: no record for this target names
//               what it points at, and the body never dereferences it.
//   key      -- the word at entry_ESP+0x4, read at 0x009817c0.
//
// The symbol embeds the record's own last name component (SetImage) because that
// is what binds this span to VA 009817c0 in the validator. It is a label, not a
// description: the body takes one comparison key and no image pointer, returns a
// pointer, and writes nothing at all. The contradiction is recorded in the
// sidecar as sdk-name-is-not-the-observed-behaviour.
PKG_DFW_009817C0_MODEL_BEGIN
extern "C" void* PKG_DFW_009817C0_THISCALL dfw_009817c0_SetImage(void* receiver, Word key);

// 0x00951240, the target of the JMP at 0x009817d6. This package does not own
// that VA and does not promote it to a record; it is declared here because the
// target's third control-flow path cannot be written without it.
//
// The contract below is read off that address's own 16-instruction live listing,
// not invented:
//
//   00951240  MOV EAX,ECX                  the receiver is copied out first
//   00951242  MOV ECX,dword ptr [ESP + 0x4]   the key becomes the new ECX
//   00951246  CMP ECX,0x6ec581fd  / JZ 0x0095126e
//   0095124e  CMP ECX,0xee3f516e  / JZ 0x00951268
//   00951256  CMP ECX,0xeec58382  / JNZ 0x0095126c
//   0095125e  TEST EAX,EAX / JZ 0x0095126c
//   00951262  ADD EAX,0x4
//   00951265  RET 0x4
//   00951268  TEST EAX,EAX / JNZ 0x00951262
//   0095126c  XOR EAX,EAX
//   0095126e  RET 0x4
//
// So: callee-cleaned, one 4-byte stack word, RET 0x4, and the exit word is
// pointer-shaped (EAX, formed by MOV EAX,ECX, ADD EAX,0x4 or XOR EAX,EAX). The
// callee also reuses ECX for its own comparison, so only the first word of the
// receiver is consumed and the receiver word itself is left readable in EAX --
// the shape the tail-jump site of 0x009817c0 depends on, and the reason the
// target writes EAX back to its own argument slot at 0x009817d2 before jumping.
// Its own ABI record is not in this package's evidence pack, so the return
// spelling is the same pointer word the target itself returns.
extern "C" void* PKG_DFW_009817C0_THISCALL dfw_009817c0_resolve_00951240(void* receiver, Word key);
PKG_DFW_009817C0_MODEL_END

}  // namespace openspore::reconstruction::pkg_dfw_009817c0
