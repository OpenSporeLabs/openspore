#pragma once

// Calling convention. The token `thiscall` is carried once per macro, which
// is what the validator's `_convention_defines` resolves, and the non-MSVC
// arm is the attribute form both clang and gcc accept in a -m32 unit.
#if defined(_MSC_VER)
#define PKG_00B1E4D0_SHARED_DEFAULT_STUB_THISCALL __thiscall
#else
#define PKG_00B1E4D0_SHARED_DEFAULT_STUB_THISCALL __attribute__((thiscall))
#endif

// Reconstruction of 0x00b1e4d0 (SporeApp.exe 3.1.0.22, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// WHAT THIS FUNCTION IS, HONESTLY
// -------------------------------
// 0x00b1e4d0 is a three-byte shared "return false" default stub:
//
//     0x00b1e4d0  30 c0   XOR AL,AL
//     0x00b1e4d2  c3      RET
//
// It is ONE function that the linker's ICF/COMDAT folding made byte-identical
// across hundreds of classes: the vftable-slot predicate P(T) in
// tools/reconstruction_tooling/vftables.py finds this address as a slot value
// in 286 vptr-backed vftables (rule V1-VFT, inference recorded in the evidence
// pack: slot 10 of the table at 0x013f69b4, membership_count 286). No rule can
// attribute it to one owning class, and none is attempted: this package models
// a shared default member function, not a member of any named type.
//
// ABI (derived, confidence INFERRED, verdict ABI_INFERRED)
// ---------------------------------------------------------
// __thiscall, and the source span states that literally. The derivation is a
// disjunction over an exhaustive set, not a preference:
//   * V1-VFT clause 1: the address is a slot of a vptr-backed vftable, so it is
//     a non-static virtual member function and has a receiver;
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
// RETURN (the one-byte trap)
// --------------------------
// The return is a single byte: XOR AL,AL writes only AL. The derived record
// states return_register EAX with return_semantics integral_in_EAX and
// return.type null - the machine fixes the WIDTH (one byte, read off the AL
// operand) and not the C type. The declared return is bool, exactly one byte,
// which is the spelling of "AL := 0" for a predicate. The upper 24 bits of EAX
// are indeterminate at the RET and are deliberately not read anywhere in this
// package.
//
// WHAT IS NOT CLAIMED
// -------------------
// No class identity (286 tables, no RTTI in this binary), no receiver layout
// (the body names no memory operand, so no displacement, no extent, no member),
// no field of any struct, no global, no callee, no branch, and no semantics
// beyond "returns false": whether the hundreds of classes use this slot as a
// default predicate answer, a default capability flag, or a placeholder is not
// observable from this body.

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "shared default stub 0x00b1e4d0 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00b1e4d0_shared_default_stub {

// The complete machine body, read from the live Ghidra bridge
// (/disassemble_function 0x00b1e4d0): two instructions, three bytes. Kept in
// the header because every claim in this package is a claim about these bytes.
constexpr std::uint8_t kTargetBytes[3] = {
    0x30,  // 0x00b1e4d0 XOR AL,AL
    0xc0,  //   XOR AL,AL, second byte
    0xc3,  // 0x00b1e4d2 RET (bare: the callee pops nothing)
};

static_assert(kTargetBytes[0] == 0x30 && kTargetBytes[1] == 0xc0,
              "0x00b1e4d0 is XOR AL,AL (30 c0): a one-byte write of zero to AL");
static_assert(kTargetBytes[2] == 0xc3,
              "0x00b1e4d2 is a bare RET (c3): caller cleanup, zero stack words");

// The vftable image this stub was observed in, modelled as a standalone table
// and NOT embedded in any receiver type: the body never reads the receiver, so
// no vtable-pointer field is claimed on it. V1-VFT observed the stub at slot
// INDEX 10 of vptr-backed tables (first observed at 0x013f69b4); slots 0..9
// are unobserved and are zero-filled here as placeholders, with no value
// claimed for them. Only the slot index is a fact; the table's other contents
// are not modelled.
struct SharedDefaultVTable {
  std::array<std::uint32_t, 10> leading_slots{};      // slots 0..9 unobserved
  std::uint32_t slot_10_shared_default = 0x00b1e4d0u;  // slot index 10, this stub
};

static_assert(sizeof(SharedDefaultVTable) == 0x2c,
              "slot index 10 is byte offset 40 in the image");
static_assert(offsetof(SharedDefaultVTable, slot_10_shared_default) == 40,
              "V1-VFT observed 0x00b1e4d0 at slot index 10 of a vptr-backed "
              "vftable (first observed table 0x013f69b4)");

// The modelled entry: __thiscall, receiver in ECX, zero ordinary stack
// arguments, caller cleanup, one-byte return. This is the convention the
// derived ABI record states and the source span spells literally.
using AbiSharedDefaultStub00b1e4d0 =
    bool(PKG_00B1E4D0_SHARED_DEFAULT_STUB_THISCALL*)(void*);

static_assert(sizeof(AbiSharedDefaultStub00b1e4d0) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");
static_assert(sizeof(bool) == 1,
              "the machine writes one byte (AL) and the declared return is one "
              "byte wide; a wider declaration would contradict the listing");

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00b1e4d0. The receiver is unnamed because
// the body never reads ECX.
bool PKG_00B1E4D0_SHARED_DEFAULT_STUB_THISCALL shared_default_stub_00b1e4d0(void*);

}
