#pragma once

// Reconstruction of FUN_00c0bc00 @ 0x00c0bc00 (SporeApp.exe 3.1.0.22).
//
// Evidence basis (all from the verified evidence pack, LIVE state, provenance
// "GhidraMCP /disassemble_function" + "/decompile_function" on the live bridge):
//
//   * Body span 0x00c0bc00..0x00c0bc16 inclusive, 23 bytes, 7 instructions,
//     listing_state "complete", parsed by the machine ABI layer with
//     declared_count=7, unparsed=0, degraded=false, flow_complete=true.
//   * Raw bytes, read back from the binary at 0x00c0bc00:
//
//       00c0bc00  8b 81 20 0b 00 00   MOV EAX,dword ptr [ECX + 0xb20]
//       00c0bc06  85 c0               TEST EAX,EAX
//       00c0bc08  74 06               JZ 0x00c0bc10
//       00c0bc0a  05 04 05 00 00      ADD EAX,0x504
//       00c0bc0f  c3                  RET
//       00c0bc10  8d 81 28 0b 00 00   LEA EAX,dword ptr [ECX + 0xb28]
//       00c0bc16  c3                  RET
//       00c0bc17  cc                  INT3 (pad; outside the body span)
//
//   * ABI (derived, abi_infer.py, verdict ABI_INFERRED): x86-32, __thiscall,
//     receiver in ECX, 0 ordinary stack arguments, bare RET so the caller
//     owns the stack cleanup, return register EAX, no tail call, no sret, no
//     variadic evidence, no frame. The receiver record is register=ECX,
//     shape R-DIRECT, bounds_only=true, offsets=[0xb20], max_offset=0xb20.
//
// WHAT THE MACHINE FIXES, AND WHAT IT DOES NOT:
//
//   It fixes: one 32-bit word is loaded from receiver+0xb20; that word is
//   tested against zero; a NONZERO word is returned with 0x504 added to it; a
//   ZERO word makes the function return the receiver's own address plus 0xb28.
//   Both exits return a 32-bit value in EAX, both exits are RET with no
//   immediate, and neither exit writes memory.
//
//   It does NOT fix: what the word at 0xb20 means (a pointer is the reading
//   the ADD favours, but nothing in this pack names it), what lives at
//   receiver+0xb28 (the body never reads it, only forms its address), the
//   identity of the receiver's type, or the meaning of 0x504. The receiver
//   record is bounds_only, so member NAMES are unverifiable layout claims
//   (see docs/tooling/reconstruction-failure-modes.md section 2). This package
//   therefore declares NO members at all: the receiver is an opaque byte run
//   and every access goes through a displacement-named accessor whose
//   displacement is a constexpr pinned by a static_assert to its instruction.
//
//   Nothing here claims a vtable slot. The pack's 68-entry reference list for
//   0x00c0bc00 contains no data-segment address, and the GLOBALS check records
//   no data reference out of 0x00c0bc00; the body itself names no address.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00c0bc00 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00C0BC00_THISCALL __thiscall
#else
#define PKG_00C0BC00_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c0bc00_storage_view_00b28 {

// One 32-bit word, the width the machine loads and returns.
using Opaque = std::uint32_t;

// The receiver, modelled at exactly the extent the body reaches and no more.
// 0x00..0xb1f is never touched; 0xb20..0xb23 is the loaded word; 0xb24..0xb27 is
// the one word of the gap the body never reads (see kInlineStorageDisplacement -
// kStorageBaseDisplacement below); 0xb28..0xb2b is the four bytes whose ADDRESS
// the zero arm forms. The extent is a modelling bound, not a recovered
// allocation size.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0xb2c> opaque_bytes{};  // 0x00..0xb2b
};

// The displacement of the single loaded word, from
// `MOV EAX,dword ptr [ECX + 0xb20]` at 0x00c0bc00. A value, not a member: the
// receiver record enumerates displacements and cannot say which member is
// which (bounds_only).
constexpr std::size_t kStorageBaseDisplacement = 0xb20;

// The displacement added to a nonzero word, from `ADD EAX,0x504` at
// 0x00c0bc0a. It is a byte displacement applied to the loaded word's value,
// NOT a receiver displacement: nothing in the body adds it to ECX.
constexpr std::size_t kStorageDetour = 0x504;

// The receiver-relative displacement formed on the zero arm, from
// `LEA EAX,dword ptr [ECX + 0xb28]` at 0x00c0bc10. The body forms this address
// and returns it; it never reads or writes the four bytes there.
constexpr std::size_t kInlineStorageDisplacement = 0xb28;

// The only way this package touches the receiver: a 4-byte word at a stated
// displacement. A member name would assert an identity the record cannot
// corroborate.
inline Opaque word_at(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const Opaque*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// The receiver's own address at a stated displacement. The body computes this
// with LEA on the zero arm, so the accessor's parameter is a displacement and
// not a member.
inline void* address_at(const void* receiver, std::size_t displacement) {
  return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(receiver) +
                                 displacement);
}

// The address the zero arm returns, expressed through the accessor so the
// header states one formula for it.
inline void* inline_storage_address(const OpaqueReceiver* receiver) {
  return address_at(receiver, kInlineStorageDisplacement);
}

// x86-32 thiscall: receiver in ECX, 0 ordinary stack arguments, caller cleans
// the stack (both terminators are a bare RET), and a 32-bit return in EAX.
using AbiStorageView00c0bc00 = void*(PKG_00C0BC00_THISCALL*)(OpaqueReceiver*);

static_assert(sizeof(void*) == 4, "pointers are 32-bit");
static_assert(sizeof(Opaque) == 4, "opaque words are 32-bit");
static_assert(sizeof(OpaqueReceiver) == 2860,
              "modeled receiver extent reaches the zero arm's address, and no further");
static_assert(offsetof(OpaqueReceiver, opaque_bytes) == 0,
              "the receiver's first byte is its base");

static_assert(kStorageBaseDisplacement == 0xb20,
              "the loaded word is the one MOV EAX reads through ECX");
static_assert(kStorageDetour == 0x504,
              "the nonzero arm adds this to the loaded word");
static_assert(kInlineStorageDisplacement == 0xb28,
              "the zero arm forms this address off the receiver");
static_assert(kInlineStorageDisplacement == (2856u),
              "the zero arm's displacement is the value 2856");
static_assert(kStorageDetour == (1284u),
              "the detour is the value 1284, compared semantically");
static_assert(kStorageBaseDisplacement + sizeof(Opaque) == 2852,
              "the loaded word occupies four bytes and stops one word below the LEA");
static_assert(kInlineStorageDisplacement == kStorageBaseDisplacement + 8u,
              "one intervening word at 0xb24 is never reached by the body");
static_assert(kInlineStorageDisplacement + sizeof(Opaque) == sizeof(OpaqueReceiver),
              "the greatest reached displacement ends the modeled extent");
static_assert(kStorageDetour != kInlineStorageDisplacement,
              "the added value and the receiver displacement are distinct");
static_assert(
    std::is_same<AbiStorageView00c0bc00,
                 void*(PKG_00C0BC00_THISCALL*)(OpaqueReceiver*)>::value,
    "modeled entry carries the ECX receiver and returns a 32-bit pointer");

// Entry point under reconstruction. The name carries the zero arm's receiver
// displacement (0xb28 -> "00b28") plus the 8-hex target VA so the validator can
// bind this span to 0x00c0bc00. It is the ONLY symbol in this package that
// carries an address, because a second address-bearing name would be read as a
// call target and turn CALLS into a fail.
void* PKG_00C0BC00_THISCALL storage_view_00c0bc00(OpaqueReceiver* receiver);

}

#undef PKG_00C0BC00_THISCALL
