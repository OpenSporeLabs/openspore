#pragma once

// Reconstruction of FUN_00c0c0e0 @ 0x00c0c0e0 (SporeApp.exe 3.1.0.22).
//
// Evidence basis (all from the live Ghidra bridge on SporeApp.exe, collected into
// reconstruction/evidence/00c0c0e0/):
//   * complete 9-instruction listing, body_start 0x00c0c0e0, body_end 0x00c0c0fb,
//     body_span_bytes 28, parse record declared_count 9 / unparsed 0 /
//     degraded false / flow_complete true:
//       0x00c0c0e0  8b 81 84 0e 00 00     MOV EAX,dword ptr [ECX + 0xe84]
//       0x00c0c0e6  85 c0                 TEST EAX,EAX
//       0x00c0c0e8  74 0f                 JZ 0x00c0c0f9
//       0x00c0c0ea  80 b8 88 03 00 00 00  CMP byte ptr [EAX + 0x388],0x0
//       0x00c0c0f1  74 06                 JZ 0x00c0c0f9
//       0x00c0c0f3  b8 01 00 00 00        MOV EAX,0x1
//       0x00c0c0f8  c3                    RET
//       0x00c0c0f9  33 c0                 XOR EAX,EAX
//       0x00c0c0fb  c3                    RET
//   * raw bytes 0x00c0c0e0: 8b 81 84 0e 00 00 85 c0 74 0f 80 b8 88 03 00 00
//     00 74 06 b8 01 00 00 00 c3 33 c0 c3
//   * derived ABI: calling_convention __thiscall, receiver register ECX,
//     receiver bounds_only with offsets [0xe84, 0x120c] and written_through 0,
//     cleanup 0 bytes owned by the caller (both terminators are a bare RET with
//     no immediate and there is no stack read anywhere in the body),
//     return register EAX, return_semantics integral_in_EAX, dispatch
//     {call_offsets: [], indirect_calls: 0, vtable_shaped_loads: 0}, no callees.
//
// WHAT THE BODY IS, AS A TRANSCRIPTION AND NOTHING MORE:
//
//     linked = *(uint32_t *)(receiver + 0xe84);
//     return (linked != 0 && *(uint8_t *)(linked + 0x388) != 0) ? 1 : 0;
//
// A two-level guarded byte probe. The first load is a 32-bit word at 0xe84 of the
// receiver; the body tests that word against zero and, only if it is non-zero,
// uses it as a base and reads one byte at 0x388 of whatever it points at. Both
// conditional branches land on the same 0x00c0c0f9 block, which is the
// `XOR EAX,EAX` / `RET` that returns 0; the fall-through writes 1 and returns.
// The body therefore stores nothing, calls nothing, saves no register, and its
// only memory effects are those two loads.
//
// WHAT THE EVIDENCE DOES NOT CARRY, AND IS NOT CLAIMED HERE:
//   * the identity of either object. `receiver` is a name for the `this` the
//     convention delivers in ECX, and the object reached through the 0xe84 word
//     is a name for the second base register's target. Neither is named as a
//     type member anywhere: the derived receiver record is `bounds_only`, so it
//     states only how far the body was seen reaching (0xe84, 0x120c) and never
//     which member of any type is which. Both objects are modelled as opaque
//     byte runs sized to the access, and the two displacements are the only
//     accessor spelling.
//   * what the 0xe84 word is. The machine tests it against zero and then
//     dereferences it, so it is modelled as an opaque 32-bit base and nothing
//     more: it is not called a pointer to any class, and it is not given a
//     pointee type beyond the opaque byte run the second access needs.
//   * what the 0xe88..0x120c tail of the receiver bounds means. The derived
//     record enumerates 0x120c, which this body's listing does not show; that is
//     the record's own lower bound and is deliberately not reproduced as an
//     access here.
//   * any SDK name. The function is `FUN_00c0c0e0`; the subsystem tag is
//     "Simulator" and no class is associated.
//
// NAMING: `linked_flag_probe_00c0c0e0` describes the SHAPE the listing fixes --
// a link word followed by a flag byte -- and asserts nothing about what either
// is. `linked` is the body's own word for the 0xe84 value; it says the machine
// follows it, not what it points at. The name carries the 8-hex target VA so
// the validator can bind this span to 0x00c0c0e0, and it is the only definition
// in the package that does.
//
// RETURN: declared `std::uint32_t`, a width-computable builtin, and not an
// alias. The derived record says the return register is EAX and classifies the
// last write to it as integral; the body proves more than that by writing EAX in
// full on both exits (`MOV EAX,0x1` and `XOR EAX,EAX`, both 32-bit), so the
// value the caller reads is a 32-bit register. The C type is a source-side
// choice among the 4-byte integral types and is not verified by the machine.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00c0c0e0 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00C0C0E0_THISCALL __thiscall
#else
#define PKG_00C0C0E0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c0c0e0_linked_flag_probe {

// The width the machine's first load fixes: `MOV EAX,dword ptr [ECX + 0xe84]`
// is a 32-bit load and the value in EAX is what the second access is based on.
// An alias for the fixtures and the accessors only -- the reconstructed entry's
// return type is spelled `std::uint32_t` and never this name, so the declared
// return width stays computable from the declaration itself.
using Word = std::uint32_t;

struct OpaqueReceiver;
struct OpaqueLinkedObject;

// The two displacements the complete 9-instruction listing names, as values.
//
//   0x00c0c0e0  MOV EAX,dword ptr [ECX + 0xe84]  -> the receiver displacement
//   0x00c0c0ea  CMP byte ptr [EAX + 0x388],0x0   -> the second object's
//
// Note the second base register: 0x388 is reached through EAX, which by then
// holds the value loaded from the receiver, NOT through ECX. It is therefore not
// a receiver displacement at all, and it is modelled on `OpaqueLinkedObject`
// rather than on `OpaqueReceiver` for exactly that reason. Each constant is
// spelled as a value and not as `receiver->member`: the derived receiver record
// is `bounds_only`, so it identifies no member by name.
constexpr std::size_t kReceiverLinkDisplacement = 0xe84;
constexpr std::size_t kLinkedFlagDisplacement = 0x388;

// The receiver, modelled at exactly the width the body reaches and no more:
// 0x00..0xe87, 4-byte aligned, i.e. the prefix through the one 32-bit word at
// 0xe84. Bytes 0x00..0xe83 are never read or written by the body. No member is
// declared, because no evidence in this package names one; the extent is a
// modelling bound, not a recovered allocation size.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0xe88> opaque_bytes{};  // 0x00..0xe87
};

// The object the 0xe84 word is used as a base for, modelled the same way: the
// prefix through the single byte the body reads at 0x388. Bytes 0x00..0x387 are
// never touched. The type exists to give the second access a base to be spelled
// against; it asserts nothing about the object's real layout or identity.
struct alignas(1) OpaqueLinkedObject {
  std::array<std::uint8_t, 0x389> opaque_bytes{};  // 0x00..0x388
};

// The only two ways this package touches either object: a 4-byte word at a
// stated displacement, and a single byte at a stated displacement. Naming a
// member instead would assert an identity the `bounds_only` receiver record
// cannot corroborate.
inline Word receiver_word(OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(receiver) +
                                  displacement);
}

inline Word receiver_word(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

inline std::uint8_t linked_flag_byte(const OpaqueLinkedObject* object,
                                     std::size_t displacement) {
  return *reinterpret_cast<const std::uint8_t*>(
      reinterpret_cast<std::uintptr_t>(object) + displacement);
}

inline std::uint8_t& linked_flag_byte(OpaqueLinkedObject* object,
                                      std::size_t displacement) {
  return *reinterpret_cast<std::uint8_t*>(
      reinterpret_cast<std::uintptr_t>(object) + displacement);
}

// x86-32 thiscall: the receiver arrives in ECX, there is no ordinary stack
// argument, both terminators are a bare RET with no immediate so the callee pops
// nothing and the caller owns the stack, and the result is a 32-bit value in
// EAX.
using AbiLinkedFlagProbe00c0c0e0 = std::uint32_t(PKG_00C0C0E0_THISCALL*)(
    OpaqueReceiver*);

static_assert(sizeof(void*) == 4, "pointers are 32-bit");
static_assert(sizeof(Word) == 4, "the 0xe84 load is a 32-bit load");
static_assert(sizeof(std::uint32_t) == 4, "the return value is 32-bit wide");
static_assert(sizeof(std::uint8_t) == 1, "the 0x388 read is a single byte");
static_assert(kReceiverLinkDisplacement == 0xe84,
              "MOV EAX,dword ptr [ECX + 0xe84] @ 0x00c0c0e0");
static_assert(kLinkedFlagDisplacement == 0x388,
              "CMP byte ptr [EAX + 0x388],0x0 @ 0x00c0c0ea");
static_assert(kReceiverLinkDisplacement + sizeof(Word) == sizeof(OpaqueReceiver),
              "the only receiver displacement the body reaches ends the modelled extent");
static_assert(kLinkedFlagDisplacement + sizeof(std::uint8_t) ==
                  sizeof(OpaqueLinkedObject),
              "the only linked-object displacement the body reaches ends its modelled extent");
static_assert(offsetof(OpaqueReceiver, opaque_bytes) == 0,
              "the receiver's first byte is its base");
static_assert(offsetof(OpaqueLinkedObject, opaque_bytes) == 0,
              "the linked object's first byte is its base");
static_assert(std::is_same<AbiLinkedFlagProbe00c0c0e0,
                           std::uint32_t(PKG_00C0C0E0_THISCALL*)(
                               OpaqueReceiver*)>::value,
              "modeled entry carries the ECX receiver and returns a 32-bit value");

// Entry point under reconstruction. The name carries the 8-hex target VA so the
// validator can bind this span to 0x00c0c0e0, and it is the package's only
// definition that does.
std::uint32_t PKG_00C0C0E0_THISCALL linked_flag_probe_00c0c0e0(OpaqueReceiver* receiver);

}

#undef PKG_00C0C0E0_THISCALL
