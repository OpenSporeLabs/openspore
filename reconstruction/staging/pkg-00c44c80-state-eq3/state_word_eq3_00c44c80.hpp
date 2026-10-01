#pragma once

// Reconstruction of FUN_00c44c80 @ 0x00c44c80 (SporeApp.exe 3.1.0.22).
//
// Evidence basis (all from the live Ghidra bridge on SporeApp.exe, collected into
// reconstruction/evidence/00c44c80/):
//   * complete 4-instruction listing, body_start 0x00c44c80, body_end 0x00c44c8c,
//     body_span_bytes 13, parse record declared_count 4 / unparsed 0 /
//     degraded false / flow_complete true:
//       0x00c44c80  33 c0                 XOR EAX,EAX
//       0x00c44c82  83 b9 84 00 00 00 03  CMP dword ptr [ECX + 0x84],0x3
//       0x00c44c89  0f 94 c0              SETZ AL
//       0x00c44c8c  c3                    RET
//   * raw bytes 0x00c44c80: 33 c0 83 b9 84 00 00 00 03 0f 94 c0 c3
//   * decompilation: `return *(int *)(param_1 + 0x84) == 3;` (decompiler output is
//     evidence, not truth).
//   * derived ABI: calling_convention __thiscall, receiver register ECX,
//     receiver record bounds_only with offsets [0x84] and written_through 0,
//     cleanup 0 bytes owned by the caller (the single terminator is a bare RET
//     with no immediate and the body never reads the stack), return register
//     EAX, sret present=false, dispatch {call_offsets: [], indirect_calls: 0,
//     vtable_shaped_loads: 0}, no callees.
//
// WHAT THE BODY IS, AS A TRANSCRIPTION AND NOTHING MORE:
//
//     return *(uint32_t *)(receiver + 0x84) == 0x3;
//
// One load, one comparison, one flag materialisation. `XOR EAX,EAX` clears the
// whole return register first and `SETZ AL` then writes its low byte, so the
// value the caller reads in EAX is 0 or 1 with nothing left over from the upper
// three bytes - the body has no branch, no call, no loop, no register save and
// no store, and its only memory effect is the single 32-bit load at 0x84.
//
// WHAT THE EVIDENCE DOES NOT CARRY, AND IS NOT CLAIMED HERE:
//   * the identity of the word at 0x84. The machine compares it against 0x3 and
//     nothing else about it is observable here, so no type member is named: the
//     derived receiver record is `bounds_only`, which fixes how far the body was
//     seen reaching (0x84) and never which member of any type is which. The
//     receiver is an opaque byte run and 0x84 is the only accessor spelling.
//   * that 0x3 is a meaningful enumeration member. 0x3 is the immediate the
//     comparison names and nothing in this package's evidence enumerates the
//     values around it, so the comparison value is a constant and not a member of
//     a named enum.
//   * any class, vtable slot or SDK name. The function is `FUN_00c44c80`, the
//     subsystem tag is "Simulator", and the body's complete listing contains no
//     indirect transfer of any kind, so this package claims no virtual boundary.
//   * what the 43 callers do with the answer. They exist in the pack's
//     caller list (0x00ae9930, 0x00c4ef00, 0x00e98c80, 0x0102adf0, ...) and every
//     one of them reads AL/EAX afterwards, which is consistent with a predicate,
//     but this package reconstructs only this body.
//
// NAMING: `state_word_eq3_00c44c80` describes the shape the listing fixes - one
// 32-bit word at a stated displacement compared against 3 - and asserts nothing
// about what the word is or what state 3 means. The name carries the 8-hex target
// VA so the validator can bind this span to 0x00c44c80, and it is the only
// definition in this package that does.
//
// RETURN: declared `bool`, a width-computable builtin. The machine proves the
// width itself: `XOR EAX,EAX` writes all four bytes and `SETZ AL` writes one, so
// the last value-producing write to EAX is a single byte and the value the caller
// sees is a one-byte boolean. `bool` is the C type whose width is 1; the machine
// fixes the width and not the spelling.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00c44c80 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00C44C80_THISCALL __thiscall
#else
#define PKG_00C44C80_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c44c80_state_eq3 {

// The width the machine's single load fixes: `CMP dword ptr [ECX + 0x84],0x3` is
// a 32-bit comparison. An alias for the fixtures and the accessors only - the
// reconstructed entry's return type is spelled `bool` and never this name, so the
// declared return width stays computable from the declaration itself.
using Word = std::uint32_t;

struct OpaqueReceiver;

// The two values the complete 4-instruction listing names, as values.
//
//   0x00c44c82  CMP dword ptr [ECX + 0x84],0x3  -> the displacement, and the
//                                               -> comparison immediate
//
// Both are spelled as values and not as `receiver->member` and not as a named
// enumerator: the derived receiver record is `bounds_only`, so it identifies no
// member by name, and no evidence in this package enumerates the values the word
// at 0x84 can take.
constexpr std::size_t kStateDisplacement = 0x84;
constexpr Word kComparedValue = 0x3;

// The receiver, modelled at exactly the width the body reaches and no more:
// 0x00..0x87, 4-byte aligned, i.e. the prefix through the one 32-bit word at
// 0x84. Bytes 0x00..0x83 are never read or written by the body. No member is
// declared, because no evidence in this package names one; the extent is a
// modelling bound, not a recovered allocation size.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0x88> opaque_bytes{};  // 0x00..0x87
};

// The only way this package touches the receiver: a 4-byte word at a stated
// displacement. Naming a member instead would assert an identity the
// `bounds_only` receiver record cannot corroborate.
inline Word state_word(OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(receiver) +
                                  displacement);
}

inline Word state_word(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// x86-32 thiscall: the receiver arrives in ECX, there is no ordinary stack
// argument, the terminator is a bare RET with no immediate so the callee pops
// nothing and the caller owns the stack, and the result is a one-byte boolean in
// EAX (written in full by `XOR EAX,EAX`, then in its low byte by `SETZ AL`).
using AbiStateWordEq300c44c80 = bool(PKG_00C44C80_THISCALL*)(OpaqueReceiver*);

static_assert(sizeof(void*) == 4, "pointers are 32-bit");
static_assert(sizeof(Word) == 4, "the 0x84 access is a 32-bit access");
static_assert(sizeof(std::uint32_t) == 4, "the compared word is 32-bit wide");
static_assert(sizeof(bool) == 1, "the returned value is one byte wide");
static_assert(kStateDisplacement == 0x84,
              "CMP dword ptr [ECX + 0x84],0x3 @ 0x00c44c82");
static_assert(kComparedValue == 0x3,
              "the comparison immediate in CMP dword ptr [ECX + 0x84],0x3 @ 0x00c44c82 is 0x3");
static_assert(kStateDisplacement + sizeof(Word) == sizeof(OpaqueReceiver),
              "the only displacement the body reaches ends the modelled extent");
static_assert(offsetof(OpaqueReceiver, opaque_bytes) == 0,
              "the receiver's first byte is its base");
static_assert(std::is_same<AbiStateWordEq300c44c80,
                           bool(PKG_00C44C80_THISCALL*)(OpaqueReceiver*)>::value,
              "modeled entry carries the ECX receiver and returns a one-byte value");

// Entry point under reconstruction. The name carries the 8-hex target VA so the
// validator can bind this span to 0x00c44c80, and it is this package's only
// definition that does.
bool PKG_00C44C80_THISCALL state_word_eq3_00c44c80(OpaqueReceiver* receiver);

}

#undef PKG_00C44C80_THISCALL
