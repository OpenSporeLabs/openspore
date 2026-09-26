#pragma once

#include <cstddef>
#include <cstdint>

// Observed body of 0x004df420, 28 bytes, 12 instructions, read from
// SporeApp.exe 3.1.0.22 at sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469 d914e:
//
//   55              PUSH EBP                        ; 0x004df420
//   8b ec           MOV EBP,ESP                     ; 0x004df421
//   51              PUSH ECX                        ; 0x004df423
//   89 4d fc        MOV [EBP-0x4],ECX               ; 0x004df424
//   8b 45 fc        MOV EAX,[EBP-0x4]               ; 0x004df427
//   05 a4 00 00 00  ADD EAX,0xa4                    ; 0x004df42a
//   50              PUSH EAX                        ; 0x004df42f
//   8b 4d fc        MOV ECX,[EBP-0x4]               ; 0x004df430
//   e8 18 01 00 00  CALL 0x004df550                 ; 0x004df433
//   8b e5           MOV ESP,EBP                     ; 0x004df438
//   5d              POP EBP                         ; 0x004df43a
//   c3              RET                             ; 0x004df43b, bare
//
// The frame releases zero stack bytes and the only register consumed besides
// the return register is ECX, so the convention is receiver-in-ECX __thiscall:
//
//   - ECX is forwarded to 0x004df550, which independently dereferences it as
//     `this` at [ECX+0x4] and [ECX+0xa4], so ECX is a receiver;
//   - [EBP+0x8] is never read, so there is no ordinary stack argument;
//   - the single PUSH is the outgoing argument 0x004df550 reads at its own
//     [EBP+0x8] and pops with its own RET 0x4 at 0x004df6c2.
//
// cdecl is excluded because the receiver would then arrive on the stack and no
// stack slot is read. stdcall is excluded by the receiver register. fastcall is
// excluded because EDX is never read and never forwarded, which also refutes
// the __fastcall the Ghidra decompilation attributes to this body.
#if defined(_MSC_VER)
#define PKG_DF420_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_DF420_THISCALL __attribute__((thiscall))
#else
#error "PKG-DOGFOOD-004DF420-A1 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_dogfood_004df420_a1 {

using OpaqueWord = std::uint32_t;
using OpaqueByte = std::uint8_t;

static_assert(sizeof(void *) == 4, "this package reconstructs x86-32 code");
static_assert(sizeof(OpaqueWord) == 4, "every observed word is 32-bit");

// The twelve byte key block that 0x004df550 reads through its first stack
// argument.
//
// It is read as three consecutive dwords and all twelve bytes are copied: at
// 0x004df5a6 (word zero), 0x004df5ab (word one) and 0x004df5b1 (word two) on
// the copy taken from the key argument itself, and at 0x004df5c9, 0x004df5ce
// and 0x004df5d4 on the copy taken from the receiver's own +0xa4.
//
// The second copy is what settles the block's placement. Its source address is
// computed as `receiver + 0xa4` (MOV EDX,[EBP-0x88] then ADD EDX,0xa4 at
// 0x004df5bd/0x004df5c3) and the three words are then read through that
// address at +0, +4 and +8. So the twelve bytes are stored INLINE at receiver
// +0xa4. They are not a pointer to a key elsewhere, and reading them requires
// no indirection beyond the receiver itself.
//
// Word zero carries the meaning that decides the callee's control flow: it is
// the word 0x004df562 compares against zero, and its local copy is the word
// 0x004df5b7 compares against zero. Because this package always passes
// `&receiver->key_0a4`, those two comparisons read the same dword; see the
// port contract below for the consequence.
//
// No field name, declared type or meaning is asserted for the three words.
// They are named by offset because the offset is observed and the name is not.
struct alignas(4) OpaqueKeyTriple {
  OpaqueWord word_00;
  OpaqueWord word_04;
  OpaqueWord word_08;
};

// Receiver wire layout for 0x004df420.
//
// Only one physical fact about the receiver is load bearing for this target,
// and it is read from the machine body rather than inherited from any sibling
// package: the body forms `receiver + 0xa4` by pointer arithmetic on the
// forwarded ECX value and hands that address to 0x004df550 as its key.
//
// The body never dereferences the receiver. Pointer arithmetic on a forwarded
// pointer is not a load, so no word of the receiver is read or written here and
// nothing inside +0x04..+0xa3 is asserted. That gap is carried as opaque
// bytes rather than described.
//
// The covered prefix ends at 0xaf. It is a proven lower bound on the bytes this
// target can touch, NOT the size of the real object. Nothing in this body
// bounds the object, and two observed call sites dereference the RETURNED word
// at offsets 0x51c and 0x5b0, so the object behind that return is certainly
// larger than this prefix. Where it ends is unresolved.
struct alignas(4) OpaqueSpeciesReceiver {
  OpaqueWord word_000;
  OpaqueByte opaque_004[0xa0];
  OpaqueKeyTriple key_0a4;
};

static_assert(offsetof(OpaqueSpeciesReceiver, word_000) == 0x00,
              "receiver +0x00 is the word this body never dereferences");
static_assert(offsetof(OpaqueSpeciesReceiver, opaque_004) == 0x04,
              "opaque gap starts at receiver +0x04");
static_assert(offsetof(OpaqueSpeciesReceiver, key_0a4) == 0xa4,
              "the address formed by ADD EAX,0xa4 at 0x004df42a");
static_assert(sizeof(OpaqueKeyTriple) == 0x0c,
              "0x004df550 copies three dwords from the key");
static_assert(sizeof(OpaqueSpeciesReceiver) == 0xb0,
              "covered prefix is a proven lower bound, not the object size");

// Port, not a promotion.
//
// 0x004df550 is a separate, separately owned VA. This package declares it
// VA-suffixed so the emitted call set stays comparable against the machine, and
// ships no stub for it in the library sense: the model test supplies a
// recording stand-in so the argument identity and the return forwarding are
// observable without a second reconstruction in the way.
//
// Contract read from the callee's own 108 instructions, not assumed:
//
//   signature   __thiscall; receiver in ECX; one four byte stack argument read
//               at [EBP+0x8]; RET 0x4 at 0x004df6c2; dword result in EAX.
//   argument    a pointer to a twelve byte block, read through and copied
//               verbatim, never written. Hence const.
//   receiver    dereferenced at [ECX+0x4] and [ECX+0xa4] by the callee, so it
//               is a pointer to a structure at least 0xa8 bytes wide.
//   result      produced at 0x004df6bc by MOV EAX,[EBP-0x4], where the local
//               slot holds either a value read out of a container at
//               receiver+0x4 or the result of the allocation the miss path
//               performs, and is null on every early exit. It is modelled as an
//               opaque 32-bit word: the machine proves the width and the
//               null-ability, and does not prove a declared type.
//
// One consequence of the argument identity is worth recording because it is a
// static reachability result rather than a style choice. 0x004df550 contains a
// substitution branch at 0x004df5bd..0x004df5ff that replaces the caller's key
// with the receiver's own +0xa4 block. That branch is gated on the key's word
// zero being zero (CMP [EBP-0x10],0x0 / JNZ 0x004df604 at
// 0x004df5b7/0x004df5bb). Because this target always passes
// `&receiver->key_0a4`, the key's word zero IS the receiver's +0xa4 word, which
// the callee already tested at 0x004df56d (CMP [ECX+0xa4],0x0) on the way in:
// if it is zero the callee has already returned null at 0x004df576, and if it
// is non-zero the JNZ skips the substitution. So on this caller's path the
// substitution is never executed.
//
// That is a claim about 0x004df550 reachable from this call site, not a claim
// about the rest of the callee: 0x004df550 has 77 direct call sites and other
// callers pass unrelated keys, for which the substitution is live. It is stated
// here only so the next reader does not model a fallback this caller cannot
// reach, and the model test asserts the algebra that makes it dead.
extern "C" OpaqueWord PKG_DF420_THISCALL
unresolved_004df550(OpaqueSpeciesReceiver *self, const OpaqueKeyTriple *key);

// Reconstruction of 0x004df420.
//
// The symbol carries the Ghidra function label "FUN_004df420" as a lowercase
// "fun" token beside the VA, so the record's Ghidra name and this candidate
// span bind to one another deterministically.
extern "C" OpaqueWord PKG_DF420_THISCALL
dogfood_species_key_resolve_fun_004df420(OpaqueSpeciesReceiver *self);

}  // namespace openspore::reconstruction::pkg_dogfood_004df420_a1

#undef PKG_DF420_THISCALL
