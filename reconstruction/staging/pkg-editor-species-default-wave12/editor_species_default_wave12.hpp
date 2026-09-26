#pragma once

#include <cstddef>
#include <cstdint>

// The observed body of 0x004df420 terminates with a bare RET, so it releases
// zero stack bytes, and the only register it consumes besides the return
// register is ECX: it spills ECX to a local slot, reloads it into EAX to form
// an address, reloads it into ECX and forwards it to 0x004df550.
//
// The convention is therefore __thiscall receiver-in-ECX:
//   - ECX is forwarded to 0x004df550, which independently dereferences ECX as
//     `this` at [ECX + 0x4] and [ECX + 0xa4], so ECX is a receiver and not an
//     ordinary argument;
//   - the body reads no entry stack slot, so there is no ordinary argument;
//   - the body pushes exactly one dword, the argument 0x004df550 reads at
//     [EBP + 0x8], and 0x004df550 pops it with RET 0x4.
//
// cdecl is excluded because the receiver would then have to arrive on the stack
// and no stack slot is read. stdcall is excluded by the receiver register.
// fastcall is excluded because EDX is never read and never forwarded.
#if defined(_MSC_VER)
#define PKG_EDITOR_SPECIES_DEFAULT_WAVE12_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_SPECIES_DEFAULT_WAVE12_THISCALL __attribute__((thiscall))
#else
#error \
    "PKG-EDITOR-SPECIES-DEFAULT-WAVE12 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_species_default_wave12 {

using OpaqueWord = std::uint32_t;
using OpaqueByte = std::uint8_t;

static_assert(sizeof(void *) == 4, "this package reconstructs x86-32 code");
static_assert(sizeof(OpaqueWord) == 4, "every observed word is 32-bit");

// The twelve byte block that 0x004df550 reads through its first stack argument.
//
// It is read as three consecutive dwords by 0x004df550 at 0x004df5a6 (word
// zero), 0x004df5ab (word one) and 0x004df5b1 (word two), which copy all
// twelve bytes into a local before probing again. Word zero is the identity
// that decides whether the fallback substitution happens: 0x004df562 compares
// it against zero and 0x004df5b7 compares the local copy of it against zero.
//
// No field name, declared type or meaning is asserted for these three words.
// They are named by offset because the offset is observed and the name is not.
struct alignas(4) OpaqueSpeciesKey3 {
  OpaqueWord word_00;
  OpaqueWord word_04;
  OpaqueWord word_08;
};

// Receiver wire layout for 0x004df420.
//
// Only two physical facts about the receiver are load bearing for this target,
// and both are read from the machine body rather than from a sibling package:
//
//   +0x00  0x004df420 never dereferences the receiver. It computes
//          `receiver + 0xa4` by pointer arithmetic on the forwarded ECX value.
//   +0xa4  0x004df420 forms `receiver + 0xa4` and passes it as the sole
//          argument of 0x004df550 (ADD EAX,0xa4 at 0x004df42a followed by
//          PUSH EAX at 0x004df42f). 0x004df550 then reads twelve bytes there,
//          both as its key argument and as the fallback it substitutes when the
//          key word zero is zero (CMP dword ptr [ECX + 0xa4],0x0 at
//          0x004df56d, and the twelve byte copy at 0x004df5c9/0x004df5ce/
//          0x004df5d4).
//
// The gap between them is carried as opaque bytes: 0x004df420 reads and writes
// nothing inside +0x04..+0xa3, and asserting anything about it would be a claim
// this target's body does not support.
//
// The covered prefix ends at 0xaf. It is a proven lower bound on the bytes this
// target can touch, NOT the size of the real object: nothing in this body
// proves where the object ends.
struct alignas(4) OpaqueSpeciesLinkRoot {
  OpaqueWord word_000;
  OpaqueByte opaque_004[0xa0];
  OpaqueSpeciesKey3 key_0a4;
};

static_assert(offsetof(OpaqueSpeciesLinkRoot, word_000) == 0x00,
              "receiver +0x00 is the word the body never dereferences");
static_assert(offsetof(OpaqueSpeciesLinkRoot, opaque_004) == 0x04,
              "opaque gap starts at receiver +0x04");
static_assert(offsetof(OpaqueSpeciesLinkRoot, key_0a4) == 0xa4,
              "the address formed by ADD EAX,0xa4 at 0x004df42a");
static_assert(sizeof(OpaqueSpeciesKey3) == 0x0c,
              "0x004df550 copies three dwords from the key");
static_assert(sizeof(OpaqueSpeciesLinkRoot) == 0xb0,
              "covered prefix is a proven lower bound, not the object size");

// Port, not a promotion.
//
// 0x004df550 is reconstructed separately by PKG-EDITOR-WAVE11 as
// editor_species_resolve_004df550 with exactly this contract: __thiscall,
// receiver in ECX, one dword stack argument, RET 0x4, dword result in EAX.
// This package declares the VA-suffixed port name so its own call set stays
// comparable against the machine, and does NOT depend on that package's staging
// symbol, which is not in src/ yet.
//
// Return type: a dword in EAX. The 0x004df550 body ends with
// "MOV EAX,[EBP-0x4] / MOV ESP,EBP / POP EBP / RET 0x4", so the callee produces
// the dword. Some observed call sites of 0x004df420 then dereference that word
// at large offsets (0x00c02734 reads [EAX + 0x5b0], 0x00aec396 reads
// [EAX + 0x51c]), which is consistent with a pointer, but no declared type is
// proven, so the port returns an opaque 32-bit word and the question is carried
// in the metadata record rather than answered here.
extern "C" OpaqueWord PKG_EDITOR_SPECIES_DEFAULT_WAVE12_THISCALL
unresolved_004df550(OpaqueSpeciesLinkRoot *self, const OpaqueSpeciesKey3 *key);

// Reconstruction of 0x004df420.
//
// The symbol carries the Ghidra function label "FUN_004df420" as a lowercase
// "fun" token next to the VA, so the record's Ghidra name
// (FUN_004df420) and the candidate span bind to one another deterministically.
extern "C" OpaqueWord PKG_EDITOR_SPECIES_DEFAULT_WAVE12_THISCALL
editor_species_resolve_fun_004df420(OpaqueSpeciesLinkRoot *self);

}  // namespace openspore::reconstruction::pkg_editor_species_default_wave12

#undef PKG_EDITOR_SPECIES_DEFAULT_WAVE12_THISCALL
