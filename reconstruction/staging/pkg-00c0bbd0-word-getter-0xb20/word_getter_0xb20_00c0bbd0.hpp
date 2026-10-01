#pragma once

// Reconstruction of FUN_00c0bbd0 @ 0x00c0bbd0 (SporeApp.exe 3.1.0.22).
//
// Evidence basis (all from the verified evidence pack for this target, which
// was filled from the live Ghidra bridge on SporeApp.exe):
//   * disassembly 0x00c0bbd0..0x00c0bbd6 - exactly two instructions:
//       0x00c0bbd0  8b 81 20 0b 00 00   MOV EAX,dword ptr [ECX + 0xb20]
//       0x00c0bbd6  c3                  RET
//     raw bytes 0x00c0bbd0: 8b 81 20 0b 00 00 c3 (the next byte, 0xcc, is the
//     INT3 pad after the body and is not part of it)
//   * Ghidra decompilation: `return *(undefined4 *)(param_1 + 0xb20);`
//   * ABI record (INFERRED): __thiscall, hidden receiver in ECX, one distinct
//     receiver displacement 0xb20, nothing written through the receiver, bare
//     RET so the callee pops nothing and the caller owns stack cleanup,
//     return value in EAX.
//
// The body is a 32-bit LOAD, not an address computation: it returns the VALUE
// stored in the receiver's word at displacement 0xb20. That distinction is the
// whole content of this reconstruction and the model test pins it from both
// sides (a value, not the address; the value, not a neighbouring word).
//
// The receiver is `bounds_only` (offsets=[0xb20], max_offset=2848, no write),
// so the machine fixes WHERE the body reached and never WHICH member of any
// type occupies that word. `OpaqueReceiver` therefore declares no member at
// all and the receiver is reached only through the `word_at` displacement
// accessor.
//
// The return type is std::uint32_t, the width-computable builtin that the load
// states. The ABI record's `return_semantics: pointer_like_in_EAX` is a
// register CLASS in the derived layer's own vocabulary, not a C type, and four
// sampled callers use the result only in equality comparisons and bitmasking
// without ever dereferencing it - so no pointer claim is made. What the word
// means (an id, a handle, an index, a pointer) is left open; see the
// unresolved questions in the package report.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00c0bbd0 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00C0BBD0_THISCALL __thiscall
#else
#define PKG_00C0BBD0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c0bbd0_word_getter_0xb20 {

using Word = std::uint32_t;

struct OpaqueReceiver;

// The displacement the body reached, from `MOV EAX,dword ptr [ECX + 0xb20]` at
// 0x00c0bbd0. It is a value, not a member: the receiver record enumerates
// displacements and cannot say which member of any type is which.
constexpr std::size_t kWordDisplacement = 0xb20;

// Receiver of the target function, modelled at exactly the width the machine
// reached and no more: 4-byte aligned, 0x00..0xb23, i.e. the prefix through the
// one word the body loads. Nothing below 0xb20 is read or written by the body.
// This extent is a MODELLING BOUND, not a recovered allocation size: the
// listing fixes the single displacement 0xb20 and says nothing about how large
// the real object is. Four sampled callers do show the object being indexed far
// past this word (e.g. `param_1[0x2c8]` = +0xb20, `param_1[0x3f4]` = +0xfd0
// and `param_1[0x4d4]` = +0x1350 in FUN_00c08350, and `*(int *)(param_2 +
// 0xb20)` read directly in FUN_00c02eb0), so the real receiver is larger; the
// package deliberately does not size it beyond what the target itself touches.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0xb24> opaque_bytes{};  // 0x00..0xb23
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
using AbiWordGetter00c0bbd0 =
    Word(PKG_00C0BBD0_THISCALL*)(OpaqueReceiver*);

static_assert(sizeof(Word) == 4, "words are 32-bit");
static_assert(sizeof(void*) == 4, "pointers are 32-bit");
static_assert(sizeof(OpaqueReceiver) == 0xb24,
              "modeled receiver extent ends at the loaded word");
static_assert(offsetof(OpaqueReceiver, opaque_bytes) == 0,
              "the receiver's first byte is its base");
static_assert(kWordDisplacement + sizeof(Word) == sizeof(OpaqueReceiver),
              "the only displacement the body reaches ends the modeled extent");
static_assert(kWordDisplacement == 2848u,
              "0xb20 is the value 2848, compared semantically not by spelling");
static_assert(std::is_same<AbiWordGetter00c0bbd0,
                           Word(PKG_00C0BBD0_THISCALL*)(OpaqueReceiver*)>::value,
              "modeled entry carries the ECX receiver and returns one word");

// Entry point under reconstruction. The name carries the displacement
// (0xb20 -> "0xb20") plus the 8-hex target VA so the validator can bind this
// span to 0x00c0bbd0.
Word PKG_00C0BBD0_THISCALL word_getter_0xb20_00c0bbd0(OpaqueReceiver* receiver);

}

#undef PKG_00C0BBD0_THISCALL
