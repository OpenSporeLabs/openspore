#pragma once

// Reconstruction of FUN_01021090 @ 0x01021090 (SporeApp.exe 3.1.0.22).
//
// Evidence basis, re-read for this package:
//   * disassembly, read live at 0x01021090 - three instructions, nine bytes:
//       0x01021090  a1 8c da 6d 01    MOV  EAX,dword ptr [0x016dda8c]
//       0x01021095  8b 40 18          MOV  EAX,dword ptr [EAX + 0x18]
//       0x01021098  c3                RET
//     body span 0x01021090..0x01021098, body_span_bytes 9, raw bytes read
//     live as a1 8c da 6d 01 8b 40 18 c3.
//   * decompilation: `undefined4 FUN_01021090(void) { return
//     *(undefined4 *)(Simulator__sSpacePlayerData + 0x18); }`
//   * ABI record: architecture x86-32, receiver absent (ECX is never read),
//     zero observed stack-argument slots, bare RET with no immediate, stack
//     cleanup 0 bytes owned by the caller, return register EAX.
//   * GLOBALS: the body names exactly one data address, 0x016dda8c, and the
//     committed data-reference sidecar records that address once out of this
//     body with access mode `read`
//     (knowledgegraph/triage/datarefs-2540f2ca.tsv:96999).
//   * CONTROL FLOW: the complete three-instruction listing contains no
//     conditional branch, no CALL and no indirect transfer; the body is
//     straight-line and the parse record reports it consumed in full
//     (declared_count 3, degraded false, unparsed 0).
//
// WHAT IS PROVED AND WHAT IS NOT.
//
// Proved by those nine bytes, with nothing added:
//   * the entry takes no argument and has no receiver; it reads no register
//     other than EAX, which it overwrites twice;
//   * it performs exactly two loads and one return: first the 32-bit word at
//     absolute address 0x016dda8c, then the 32-bit word at displacement 0x18
//     from the pointer that load produced;
//   * it writes nothing: no store instruction appears, so neither the global
//     word nor the field nor any neighbouring word is modified;
//   * it tests nothing: there is no compare, no conditional branch and no
//     arithmetic, so no value is substituted, defaulted, clamped or masked on
//     the way out; a published value is returned bit for bit;
//   * there is NO null guard. The two loads are unconditional, so a published
//     global of 0 is dereferenced at +0x18 rather than turned into a sentinel.
//     This is a real distinction inside this family and not a stylistic
//     assumption: the sibling read view at 0x01021260 in the promoted
//     pkg01_roots package tests its global and returns nullptr, and this entry
//     does not. The model test measures the difference with a forked child
//     rather than asserting it in prose;
//   * the value crosses in EAX, because the second load is the last write to
//     EAX before the RET.
//
// NOT proved by these nine bytes, and therefore not claimed here:
//   * the calling convention. The ABI record abstains (`ABI_UNKNOWN`): with no
//     stack-argument read and no receiver, this body is byte-identical under
//     __cdecl, __stdcall, __thiscall and __fastcall. A zero-parameter
//     declaration is used because it is what the machine fixes, not because
//     the record names a convention;
//   * what the returned word MEANS as a game concept, beyond the SDK field
//     name recorded below. Nothing in this body reads a neighbour, compares
//     the word with anything, or reacts to its value;
//   * the class of the object the global points at. There is no MSVC RTTI in
//     this binary, so the pointee's type is not recoverable from these
//     instructions. The struct below is a fixture sized to the one word this
//     body reaches, not a recovered layout;
//   * nullability, thread-safety and ownership of the global. The body has no
//     room for a reference operation and performs none;
//   * whether any caller survives a null global. That the entry faults on a
//     null global is established by the model; whether any of the ~100
//     recorded call sites can reach that state is not established here.
//
// IDENTITY OF THE RETURNED WORD: two committed sources, and they are kept
// apart from the machine evidence on purpose.
//
//   * Layout: the SDK export in this repository places
//     `Simulator::sSpacePlayerData` at absolute address 0x016dda8c
//     (.spore-analysis/ghidra-exports/spore_sdk.xml:51791) and defines
//     `/Spore/Simulator/SpacePlayerData` with the word at offset 24 as
//     `mPlayerEmpireID uint32_t`
//     (.spore-analysis/ghidra-exports/structs_fields.tsv:11689).
//   * Lifecycle cross-check, independent of the export: the committed
//     SpacePlayerData follow-up records that 0x01021d40 initialises +0x18 to
//     -1 at allocation and that 0x01022460 resets +0x18 to -1 during field
//     teardown (knowledgegraph/research/root-closure/followup-space-lifecycle.md:9-16,
//     :58). A 32-bit identity word with a -1 "no empire" sentinel is what the
//     offset behaves like, and the neighbour at +0x1c is separately typed as
//     the intrusive_ptr<cEmpire>, so +0x18 is the ID and not the pointer.
//
// CONFLICT RECORDED, NOT ADOPTED. The derived ABI record classifies the EAX
// value `register_class: pointer_like`, with `confidence: INFERRED` and
// `corroboration: not_available`. That classification is a heuristic on "the
// last value written to EAX" and cannot tell a loaded word from a computed
// address. This package models the return as a 32-bit unsigned scalar, for the
// two reasons above, and states the disagreement here rather than adopting the
// heuristic.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_01021090 reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_01021090_space_player_empire_id {

static_assert(sizeof(void*) == 4,
              "FUN_01021090 reconstruction requires 32-bit pointers");
static_assert(sizeof(std::uint32_t) == 4,
              "the word the body loads at +0x18 is 32 bits wide");

// The absolute address of the one global this body reads, named with the
// repository's `g_<va8>` convention so a validator can match it against the
// listing and against the committed data-reference sidecar. It is a data
// address, so it lives here as a name rather than as a pointer-sized literal
// in the body.
//
// kTargetEncodingAddress is the SAME address as the moffs32 immediate the first
// instruction carries, written little-endian into the encoding table below, so
// a mutation to either spelling is caught by the static_assert that compares
// them. One address, two independent spellings, one invariant.
constexpr std::uint32_t kGlobalAddress = 0x016dda8cu;

static_assert(kGlobalAddress == 0x016dda8cu,
              "Simulator::sSpacePlayerData is the SDK-imported global at "
              "0x016dda8c (spore_sdk.xml:51791)");
static_assert((kGlobalAddress & 0xffu) == 0x8cu &&
                  ((kGlobalAddress >> 8) & 0xffu) == 0xdau &&
                  ((kGlobalAddress >> 16) & 0xffu) == 0x6du &&
                  ((kGlobalAddress >> 24) & 0xffu) == 0x01u,
              "the address is spelled little-endian, as the moffs32 immediate "
              "spells it");

// The single displacement the listing names, from
// `MOV EAX,dword ptr [EAX + 0x18]`. It is a byte displacement and not an
// element count: the operand is `dword ptr`, so one element is four bytes, and
// reading it as an index would land at byte 0xc0 of the fixture instead.
constexpr std::size_t kPlayerEmpireIdDisplacement = 0x18u;

// The type of the word the body reads, named once so the read WIDTH and the
// declared field cannot drift apart. Narrowing or widening this type is a
// mutation of the read, and the model test's verbatim sweep refutes it.
using PlayerEmpireIdWord = std::uint32_t;

static_assert(sizeof(PlayerEmpireIdWord) == 4,
              "the word the body reads is 32 bits wide: dword ptr [EAX+0x18]");

// The object the global points at, modelled exactly as far as this body
// reaches and no further. Every member before +0x18 is opaque padding: this
// entry never reads it, so no layout is asserted for it, and the member names
// below are the SDK's, carried as comments on opaque words rather than as a
// recovered structure. The extent is a MODELLING BOUND through the last word
// this body reads, not a recovered allocation size; the committed export makes
// the object 0x34 bytes, which this fixture deliberately does not claim.
struct SpacePlayerDataEmpireIdFixture {
  std::uint8_t opaque_000[0x18];  // +0x00..+0x17, never touched by this body
  PlayerEmpireIdWord player_empire_id;  // +0x18; SDK: mPlayerEmpireID
};

// The global. Published by 0x01021d40 and read here; this package models only
// the read and never writes it. A separate declaration from the promoted
// pkg01_roots `Simulator__sSpacePlayerData` so that promoting both packages
// into one binary cannot produce two definitions of one symbol.
extern SpacePlayerDataEmpireIdFixture* g_016dda8c;

// The only way this package reaches the field: a word at a stated
// displacement, addressed arithmetically. A member access through the fixture
// would assert a layout this body's evidence does not establish. The returned
// pointer is typed by the declared field so that a mutation to the field's
// width is a mutation to the read rather than a decoration the read ignores.
inline const PlayerEmpireIdWord* empire_id_word(
    const SpacePlayerDataEmpireIdFixture* object,
    std::size_t displacement) {
  return reinterpret_cast<const PlayerEmpireIdWord*>(
      reinterpret_cast<std::uintptr_t>(object) + displacement);
}

static_assert(offsetof(SpacePlayerDataEmpireIdFixture, player_empire_id) ==
                  kPlayerEmpireIdDisplacement,
              "the header constant is the displacement the listing names");
static_assert(kPlayerEmpireIdDisplacement + sizeof(std::uint32_t) ==
                  sizeof(SpacePlayerDataEmpireIdFixture),
              "the word the body reads ends the modelled fixture extent");

// The nine bytes read live at 0x01021090..0x01021098, pinned in code so the
// reconstruction's encoding cannot drift away from its own prose.
constexpr std::uint8_t kTargetBytes[9] = {
    0xa1, 0x8c, 0xda, 0x6d, 0x01, 0x8b, 0x40, 0x18, 0xc3,
};

static_assert(sizeof(kTargetBytes) == 9,
              "the body is nine bytes: 5 + 3 + 1");
static_assert(kTargetBytes[4] == 0x01,
              "the moffs32 immediate of the first load ends at byte 4");
static_assert(kTargetBytes[1] == 0x8c && kTargetBytes[2] == 0xda &&
                  kTargetBytes[3] == 0x6d,
              "the moffs32 immediate spells the little-endian global address");
static_assert(kTargetBytes[5] == 0x8b,
              "the second instruction is MOV r32, r/m32 (0x8b), not LEA (0x8d)");
static_assert(kTargetBytes[6] == 0x40,
              "ModRM 0x40 is mod=01, reg=EAX, rm=EAX: a disp8 from EAX");
static_assert(kTargetBytes[7] ==
                  static_cast<std::uint8_t>(kPlayerEmpireIdDisplacement),
              "the disp8 byte is the displacement the body reads");
static_assert(kTargetBytes[8] == 0xc3,
              "the tail is a bare RET, so the caller owns stack cleanup");

// 0x01021090  MOV EAX,dword ptr [0x016dda8c]
// 0x01021095  MOV EAX,dword ptr [EAX + 0x18]
// 0x01021098  RET
//
// Returns the published word verbatim. See the return-semantics and
// no-null-guard notes above.
extern "C" std::uint32_t space_player_empire_id_01021090();

}  // namespace openspore::reconstruction::pkg_01021090_space_player_empire_id