#pragma once

// Calling convention. The token `thiscall` is carried once per macro, which is
// what the validator's `_convention_defines` resolves, and the non-MSVC arm is
// the attribute form both clang and gcc accept in a -m32 unit.
#if defined(_MSC_VER)
#define PKG_00E31100_SHARED_ZERO_RESULT_THISCALL __thiscall
#else
#define PKG_00E31100_SHARED_ZERO_RESULT_THISCALL __attribute__((thiscall))
#endif

// Reconstruction of 0x00e31100 (SporeApp.exe 3.1.0.22, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// WHAT THIS FUNCTION IS, HONESTLY
// -------------------------------
// 0x00e31100 is a three-byte shared "result is zero" stub:
//
//     0x00e31100  33 c0   XOR EAX,EAX
//     0x00e31102  c3      RET
//
// Both instructions read live off the bridge (/disassemble_function, then
// /read_memory at 0x00e31100 len 8, which returns 33c0c3 followed by the
// 0xcc INT3 fill 0x00e31103..0x00e31109 that is padding and not body).
//
// The whole body is two instructions and there is nothing else in it: no branch,
// no call, no flag test, no register save, no loop, no memory operand of any
// kind. The linker folded this address across many classes - the vftable-slot
// predicate P(T) in tools/reconstruction_tooling/vftables.py finds it as a slot
// value, and a direct read of the committed export
// .spore-analysis/ghidra-exports/vtables.json measures 508 tables containing
// 0x00e31100. No rule can attribute it to one owning class and none is
// attempted: this package models a shared default member function, not a member
// of any named type.
//
// RETURN: THE FULL 32 BITS OF EAX
// -------------------------------
// 33 c0 is XOR EAX,EAX - the operand is the full 32-bit register, so all four
// bytes of EAX are written with zero and none of them is indeterminate at the
// RET. That is the difference from a one-byte stub such as 0x00b1e4d0 (30 c0,
// XOR AL,AL), whose upper 24 bits are indeterminate; here they are not. The
// derived ABI record reports return_register EAX, return_semantics
// integral_in_EAX, register_class integral, so the declared return is the
// 32-bit integral std::int32_t, whose zero is the value EAX provably carries.
// That is also the width src/reconstruction/pkg08_cell_mode already uses for
// this call site: OpaqueIterator is std::int32_t there, and the value flows into
// a four-byte local cursor word, which is consistent with a four-byte write.
//
// ABI (derived, confidence INFERRED, verdict ABI_INFERRED)
// ---------------------------------------------------------
// __thiscall, and the source span states that literally. The derivation is a
// disjunction over an exhaustive set, not a preference:
//   * V1-VFT clause 1: the address is a slot of a vptr-backed vftable (508
//     tables), so it is a non-static virtual member function and has a receiver;
//   * V1-VFT clause 2: the terminal is a bare RET, so the callee pops nothing;
//   * V1-VFT clause 3: no stack word is read as an argument (the body names no
//     memory operand at all);
//   * on x86-32 MSVC the only remaining place a receiver can arrive is a
//     register, and of __thiscall/__fastcall only ECX carries it (clause 5
//     removes __fastcall: EDX is never read either).
// The receiver is therefore in ECX, there are 0 ordinary stack arguments, and
// the caller cleans the stack. The body never reads ECX in any form, so the
// receiver parameter below is unnamed: naming it would be a claim the listing
// does not make.
//
// THE PORT SPELLING IN pkg08_cell_mode IS THE SAME MACHINE CALL
// -------------------------------------------------------------
// src/reconstruction/pkg08_cell_mode/mode_on_exit.hpp declares
// `using IteratorBegin00e31100 = OpaqueIterator (*)();` - a zero-argument
// function pointer, receiver normalized away. That is not a competing claim
// about this body; it is the same call with the dead ECX register dropped. The
// model test proves the two shapes are observationally identical here by
// running both trampolines against this entry and against a reference that
// returns a non-zero value. This package keeps the ECX receiver because that is
// what the vftable evidence states; the pkg08 spelling is recorded in
// AbiIteratorBegin00e31100 below so both are in one place.
//
// WHAT IS NOT CLAIMED
// -------------------
// No class identity (508 tables, and no MSVC RTTI in this binary), no receiver
// layout (the body names no memory operand, so no displacement, no extent, no
// member), no field of any struct, no global, no callee, no branch, and no
// semantics beyond "the result is zero": whether the hundreds of classes use
// this slot as an absent-value answer, an empty-collection count, a default
// capability report or a placeholder is not observable from this body. The slot
// INDEX is a property of the owning table, not of this entry: it is 8 in the
// modelled image at 0x013f6364 and ranges over 1..38 across the 508 tables, so
// no single index is claimed as "the" slot.

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "shared zero-result stub 0x00e31100 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00e31100_shared_zero_result_stub {

// The complete machine body, read from the live Ghidra bridge
// (/disassemble_function 0x00e31100 and /read_memory at the same address):
// two instructions, three bytes. Kept in the header because every claim in this
// package is a claim about these bytes.
constexpr std::uint8_t kTargetBytes[3] = {
    0x33,  // 0x00e31100 XOR EAX,EAX
    0xc0,  //   XOR EAX,EAX, ModRM c0 (reg,reg form: EAX with EAX)
    0xc3,  // 0x00e31102 RET (bare: the callee pops nothing)
};

// 0xcc INT3 fill observed at 0x00e31103..0x00e31109. Padding between functions,
// NOT part of the body, recorded so a reader can see it was seen and excluded.
constexpr std::uint8_t kPaddingByte = 0xcc;

static_assert(kTargetBytes[0] == 0x33 && kTargetBytes[1] == 0xc0,
              "0x00e31100 is XOR EAX,EAX (33 c0): a FULL 32-bit write of zero to "
              "EAX, not a one-byte write to AL");
static_assert(kTargetBytes[2] == 0xc3,
              "0x00e31102 is a bare RET (c3): caller cleanup, zero stack words");

// The vftable image this stub was observed in, modelled as a standalone table
// and NOT embedded in any receiver type: the body never reads the receiver, so
// no vtable-pointer field is claimed on it. V1-VFT observed the stub at slot
// INDEX 8 of the vptr-backed table at 0x013f6364 (read live: the word at
// 0x013f6364 + 8*4 == 0x013f6384 is 0x00e31100); slots 0..7 are unobserved and
// are zero-filled here as placeholders, with no value claimed for them. Only
// this one table's index is stated; across the 508 tables that hold this
// address the index varies over 1..38 and no index is claimed as global.
struct SharedZeroResultVTable {
  std::array<std::uint32_t, 8> leading_slots{};       // slots 0..7 unobserved
  std::uint32_t slot_8_shared_zero_result = 0x00e31100u;  // this table's slot 8
};

static_assert(sizeof(SharedZeroResultVTable) == 0x24,
              "slot index 8 is byte offset 32 in the image");
static_assert(offsetof(SharedZeroResultVTable, slot_8_shared_zero_result) == 32,
              "V1-VFT observed 0x00e31100 at slot index 8 of the vptr-backed "
              "vftable at 0x013f6364");

// The modelled entry: __thiscall, receiver in ECX, zero ordinary stack
// arguments, caller cleanup, 32-bit integral return.
using AbiSharedZeroResult00e31100 =
    std::int32_t(PKG_00E31100_SHARED_ZERO_RESULT_THISCALL*)(void*);

// The spelling src/reconstruction/pkg08_cell_mode uses at its 0x00e31100 port:
// no explicit arguments, same 32-bit return. Recorded here so the two forms sit
// in one place. The C types differ; the MACHINE call does not, because the
// body reads ECX in no form, so whether the caller sets ECX is unobservable at
// this entry. The model test exercises both shapes for exactly that reason.
using AbiIteratorBegin00e31100 = std::int32_t (*)();

static_assert(sizeof(AbiSharedZeroResult00e31100) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00e31100. The receiver is unnamed because
// the body never reads ECX.
std::int32_t PKG_00E31100_SHARED_ZERO_RESULT_THISCALL
shared_zero_result_00e31100(void*);

// The width of the entry's OWN declared return, measured by deducing it off an
// UNEVALUATED call to the entry rather than off a restatement of it, so
// narrowing the entry cannot pass silently. (An earlier version of this package
// asserted only sizeof(std::int32_t) == 4, which the typedef below satisfied no
// matter what the entry itself declared; the mutation harness caught exactly
// that.) decltype on the call expression, not a template specialization on
// `R(Args...)`: the entry carries a calling-convention attribute that such a
// specialization would not match, and the call is unevaluated so the function
// need not be constexpr.
static_assert(
    sizeof(decltype(shared_zero_result_00e31100(nullptr))) == 4,
    "the entry's declared return is the 32 bits the machine writes: "
    "XOR EAX,EAX names the full register, so a one-byte return would "
    "contradict the listing");

}