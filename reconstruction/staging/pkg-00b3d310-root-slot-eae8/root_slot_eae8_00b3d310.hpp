#pragma once

// Reconstruction of FUN_00b3d310 @ 0x00b3d310 (SporeApp.exe 3.1.0.22,
// SHA-256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// EVIDENCE BASIS -- everything below is read off the target's own
// two-instruction body plus the committed data-reference artifact for that
// body. Nothing is inherited from the sibling accessors at
// 0x00b3d2a0/0x00b3d300/0x00b3d3a0/ 0x00b3d400, and nothing about the contents
// of the slot is claimed.
//
//   0x00b3d310  a1 e8 ea 67 01   MOV EAX, dword ptr [0x0167eae8]
//   0x00b3d315  c3               RET
//
//   raw bytes 0x00b3d310: a1 e8 ea 67 01 c3 (6 bytes). The two bytes that
//   follow (0xcc, INT3 pad) are NOT part of the body and are excluded. `a1` is
//   MOV r32, moffs32, so the four operand bytes are an absolute 32-bit address
//   in little-endian order: e8 ea 67 01 -> 0x0167eae8. Ghidra decompilation:
//   `return DAT_0167eae8;` Ghidra /disassemble_function: exactly 2
//   instructions, listing_state complete.
//   knowledgegraph/triage/datarefs-2540f2ca.tsv: one row for this body --
//   `00b3d310  0167eae8  read  .data -wr`. Read, never written, by this body.
//   ghidra_get_xrefs_to(0x0167eae8): 1 reference total, the READ above. There
//   is no WRITE reference anywhere in the current analysis state, so no
//   publisher of this slot has been located and none is claimed.
//
// WHAT THE BODY IS
//
// A load-and-return of one 32-bit word from a fixed absolute address. There is
// no branch, no call, no flag test, no register save, no loop, no arithmetic
// and no store anywhere in the body, so:
//
//   * the slot is READ on every entry and is left byte-identical;
//   * the result is a pure function of the slot's current contents;
//   * ECX is never read in any form, so there is no register receiver;
//   * the bare RET pops nothing, so the caller owns stack cleanup and there are
//     zero ordinary stack arguments;
//   * the byte sequence is identical under __cdecl, __stdcall, __thiscall and
//     __fastcall. The ABI record says so itself (`C10`, confidence UNKNOWN) and
//     records why it abstains: "no_discriminator: no stack-argument read and no
//     positive receiver evidence". The spelling below is therefore a
//     SOURCE-SIDE CHOICE among four byte-identical options, not a recovered
//     fact.
//
// THE POINTEE
//
// `OpaqueRootSlotTarget` is an INCOMPLETE type and is never defined, sized, or
// named after anything. The machine fixes the width of the value in EAX (four
// bytes) and nothing else. That the word is used as an object address is
// corroborated outside this body and is stated as such in the .cpp: the ABI
// record classifies EAX as `pointer_like`, and two independently read callers
// dereference the returned word at displacement +0x20 immediately after the
// call (0x00acd13a `CMP dword ptr [EAX + 0x20], 0x1` after `CALL 0x00b3d310` at
// 0x00acd135; 0x00b82985 `CMP dword ptr [EAX + 0x20], EBX` after `CALL
// 0x00b3d310` at 0x00b8297e). No member at +0x20 is declared here, because this
// body's own listing reaches no displacement at all and a member name would be
// an identity claim nothing in this package corroborates.
//
// kSlotAddress is tied to the ENCODING, not to prose: the test recomposes the
// four imm32 bytes from kSlotAddress and requires them to spell the bytes read
// from 0x00b3d310, so the two statements cannot drift apart.

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00b3d310 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00B3D310_CDECL __cdecl
#else
#define PKG_00B3D310_CDECL __attribute__((cdecl))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_00b3d310_root_slot_eae8 {

using Word = std::uint32_t;

// The absolute address the body's operand bytes spell: `a1 e8 ea 67 01` is
// MOV EAX, moffs32 with a little-endian disp32, so this is a VALUE the
// instruction carries, not a member of any type and not an offset.
constexpr Word kSlotAddress = 0x0167eae8u;

// The slot itself. Named with the repository's `g_<va8>` global convention so
// the validator can read it as the data address the body touches. It is a plain
// 32-bit word: the body neither writes it nor knows anything else about it.
extern "C" {
extern Word g_0167eae8;
}

// The value the body returns, as an opaque pointer. The type is INCOMPLETE and
// is never defined: the machine fixes the four-byte width of what crosses EAX
// and nothing about the object it addresses. No member of it is declared
// anywhere in this package, and `kSlotAddress` is not an offset into it.
struct OpaqueRootSlotTarget;

// x86-32 cdecl: no hidden register receiver (ECX is never read), zero ordinary
// stack arguments, the caller pops (bare RET), and one 32-bit word returns in
// EAX. See the header comment: the four conventions are byte-identical here and
// this one is a source-side choice.
using AbiRootSlotAccessor00b3d310 =
    OpaqueRootSlotTarget*(PKG_00B3D310_CDECL*)();

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00b3d310, and it is the ONLY definition in
// this package that carries it: every helper is named without an address, so a
// helper can never be mistaken for a direct call target of the body (which
// makes none).
OpaqueRootSlotTarget* PKG_00B3D310_CDECL simulator_root_slot_eae8_00b3d310();

static_assert(sizeof(Word) == 4, "words on this target are 32-bit");
static_assert(sizeof(void*) == 4, "pointers on this target are 32-bit");
static_assert(sizeof(OpaqueRootSlotTarget*) == 4,
              "the modelled return crosses the ABI as one 32-bit word");
static_assert(sizeof(AbiRootSlotAccessor00b3d310) == sizeof(void*),
              "modelled entry is a plain zero-argument function pointer");
static_assert(kSlotAddress == 0x0167eae8u,
              "the slot address is the value 0x0167eae8, compared by value");
static_assert(kSlotAddress == static_cast<Word>(0x0167eae8u),
              "the slot address is one 32-bit word, not a wider quantity");
static_assert(std::is_same<decltype(&simulator_root_slot_eae8_00b3d310),
                           AbiRootSlotAccessor00b3d310>::value,
              "the declared entry matches the modelled ABI type exactly");

}  // namespace pkg_00b3d310_root_slot_eae8
}  // namespace reconstruction
}  // namespace openspore

#undef PKG_00B3D310_CDECL