#pragma once

// Reconstruction of FUN_00c04590 @ 0x00c04590 (SporeApp.exe 3.1.0.22).
//
// Evidence basis (all from the verified LIVE evidence pack for this target,
// filled from the live Ghidra bridge on SporeApp.exe, plus one bounded adjacent
// read and two sampled callers; no broad sweeps):
//   * disassembly 0x00c04590..0x00c04596 - exactly two instructions:
//       0x00c04590  8b 81 74 16 00 00   MOV EAX,dword ptr [ECX + 0x1674]
//       0x00c04596  c3                  RET
//     raw bytes 0x00c04590: 8b 81 74 16 00 00 c3 (the following three 0xcc
//     bytes are the INT3 pad after the body and are not part of it)
//   * Ghidra decompilation: `return *(undefined4 *)(param_1 + 0x1674);`
//   * ABI record (INFERRED): __thiscall, hidden receiver in ECX, one distinct
//     receiver displacement 0x1674 (max_offset 5748), nothing written through
//     the receiver, bare RET so the callee pops nothing and the caller owns
//     stack cleanup, return value in EAX.
//   * CORROBORATION for the field's identity, from the IMMEDIATELY ADJACENT
//     function 0x00c045a0 (one bounded read, not a sweep): it writes the SAME
//     displacement. 0x00c045a4 `MOV ECX,dword ptr [ESI + 0x1674]` and
//     0x00c045cf `MOV dword ptr [ESI + 0x1674],EDI`, with a null test on the
//     incoming value before the store, a call through `[EAX]` (vtable slot +0x0)
//     on the incoming value before the store, and a call through `[EAX+0x4]`
//     (vtable slot +0x4) on the OUTGOING value after it. That is a
//     retain-new / store / release-old swap, so the word at +0x1674 holds a
//     refcounted object pointer, and 0x00c04590 is its read side.
//
// The body is a 32-bit LOAD, not an address computation: it returns the VALUE
// stored in the receiver's word at displacement 0x1674. That distinction is the
// whole content of this reconstruction and the model test pins it from both
// sides (a value, not the address; the value, not a neighbouring word).
//
// THE BEHAVIOURAL CLAIM THIS PACKAGE ADDS OVER "IT IS A GETTER": 0x00c04590 is
// a RAW, NON-RETAINING read. Its neighbour 0x00c045a0 shows what retaining
// looks like in this very object - an explicit indirect call through the
// pointer's own vtable. The target's two-instruction body contains no call, no
// test, no arithmetic and no store, so it neither acquires a reference nor
// releases one, and it leaves the receiver byte-identical. A reconstruction that
// "helpfully" retained, or that returned a fresh copy/handle, is refuted by the
// model test's guard bands and side-effect probes.
//
// The receiver is `bounds_only` (offsets=[0x1674], max_offset=5748, no write),
// so the machine fixes WHERE the body reached and never WHICH member of any
// type occupies that word. `OpaqueReceiver` therefore declares no member at
// all and the receiver is reached only through the `word_at` displacement
// accessor.
//
// The return type is std::uint32_t, the width-computable builtin that the load
// states. The adjacent setter and the sampled callers both treat the returned
// word as a base for further access (0x00b6b4c0 reads `*(int *)(result +
// 0x15c)`; 0x00accf80 calls through `**(code **)result`), which agrees with the
// ABI record's `return_semantics: pointer_like_in_EAX` and with the refcounted
// pointer the neighbour stores. But the machine fixes only the WIDTH, and this
// package asserts no C pointer type, no pointee type and no vtable identity
// beyond the two slots 0x00c045a0 is observed to call. What the pointee is
// remains open; see the unresolved questions in the package report.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00c04590 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00C04590_THISCALL __thiscall
#else
#define PKG_00C04590_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c04590_field_getter_0x1674 {

using Word = std::uint32_t;

struct OpaqueReceiver;

// The displacement the body reached, from `MOV EAX,dword ptr [ECX + 0x1674]` at
// 0x00c04590. It is a value, not a member: the receiver record enumerates
// displacements and cannot say which member of any type is which. Its identity
// as a refcounted-object-pointer slot is corroborated by the adjacent
// 0x00c045a0, which stores through the same displacement, but no member name
// is asserted here.
constexpr std::size_t kWordDisplacement = 0x1674;

// Receiver of the target function, modelled at exactly the width the machine
// reached and no more: 4-byte aligned, 0x00..0x1677, i.e. the prefix through the
// one word the body loads. Nothing below 0x1674 is read or written by the body.
// This extent is a MODELLING BOUND, not a recovered allocation size: the
// listing fixes the single displacement 0x1674 and says nothing about how large
// the real object is. The sampled caller 0x00b6b4c0 reads `result + 0x15c`, so
// the real object is at least that large too; the package deliberately does not
// size it beyond what the target itself touches.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0x1678> opaque_bytes{};  // 0x00..0x1677
};

// The only way this package touches the receiver: a 32-bit word at a stated
// displacement. Naming a member instead would assert an identity the receiver
// record (bounds_only) cannot corroborate.
inline Word* word_at(OpaqueReceiver* receiver, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(receiver) +
                                 displacement);
}

inline Word word_at(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// x86-32 thiscall: receiver in ECX, 0 ordinary stack arguments, caller cleans
// the stack (bare RET), and a 32-bit value return in EAX.
using AbiFieldGetter00c04590 =
    Word(PKG_00C04590_THISCALL*)(OpaqueReceiver*);

static_assert(sizeof(Word) == 4, "words are 32-bit");
static_assert(sizeof(void*) == 4, "pointers are 32-bit");
static_assert(sizeof(OpaqueReceiver) == 0x1678,
              "modeled receiver extent ends at the loaded word");
static_assert(offsetof(OpaqueReceiver, opaque_bytes) == 0,
              "the receiver's first byte is its base");
static_assert(kWordDisplacement + sizeof(Word) == sizeof(OpaqueReceiver),
              "the only displacement the body reaches ends the modeled extent");
static_assert(kWordDisplacement == 5748u,
              "0x1674 is the value 5748, compared semantically not by spelling");
static_assert(std::is_same<AbiFieldGetter00c04590,
                           Word(PKG_00C04590_THISCALL*)(OpaqueReceiver*)>::value,
              "modeled entry carries the ECX receiver and returns one word");

// Entry point under reconstruction. The name carries the displacement
// (0x1674 -> "0x1674") plus the 8-hex target VA so the validator can bind this
// span to 0x00c04590.
Word PKG_00C04590_THISCALL field_getter_0x1674_00c04590(
    OpaqueReceiver* receiver);

}

#undef PKG_00C04590_THISCALL
