#pragma once

// Reconstruction of FUN_00c6a960 @ 0x00c6a960 (SporeApp.exe 3.1.0.22).
//
// Evidence basis, re-read for this package:
//   * disassembly 0x00c6a960..0x00c6a967 - four instructions, eight bytes:
//       0x00c6a960  8b 41 08          MOV  EAX,dword ptr [ECX + 0x8]
//       0x00c6a963  40                 INC  EAX
//       0x00c6a964  89 41 08          MOV  dword ptr [ECX + 0x8],EAX
//       0x00c6a967  c3                 RET
//     followed by 0xcc INT3 padding at 0x00c6a968..0x00c6a96b, read live.
//   * raw bytes at 0x00c6a960: 8b 41 08 40 89 41 08 c3.
//   * decompilation: `*(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;`
//   * receiver record: register=ECX, offsets=[0x8], bounds_only,
//     written_through=1, distinct_offsets=1, max_offset=8, shape R-DIRECT.
//   * ABI record: __thiscall, receiver ECX, ret form RET with no immediate,
//     stack cleanup 0 owned by the caller, zero stack arguments.
//   * GLOBALS: the committed data-reference artifact records no data reference
//     out of 0x00c6a960, and the complete listing names no data-segment
//     address. The body touches no global.
//   * CONTROL FLOW: the complete four-instruction listing contains no
//     conditional branch. The body is straight-line by the listing itself.
//   * VIRTUAL DISPATCH: the body names no indirect transfer through a register
//     or a memory operand; the dispatch record agrees at 0. The entry is a
//     dispatch TARGET, never a dispatcher.
//
// WHAT IS PROVED AND WHAT IS NOT.
//
// Proved by the eight bytes above, with nothing added:
//   * the receiver is ECX, __thiscall, no stack argument, no callee cleanup;
//   * exactly one receiver word is touched, the 32-bit word at +0x8;
//   * that word is both READ and WRITTEN (the only write-through the record
//     reports, written_through=1);
//   * the transformation on it is +1, i.e. an increment, and nothing else - no
//     compare, no branch, no clamp, no saturation, no second store;
//   * the post-increment value is left in EAX at the RET, because INC EAX is
//     the last write to EAX and MOV [ECX+8],EAX does not touch it. So the
//     increment is a post-increment whose result is returned in EAX;
//   * the return is not `_Bool`-like: INC EAX is a full 32-bit add with no
//     truncation to a byte or to a zero/one flag anywhere in the body.
//
// NOT proved by the eight bytes, and therefore not claimed below:
//   * what the +0x8 word MEANS. A reference count, a generation counter, an
//     access tally and a use count all increment identically. The layout
//     comment in this file records the partner-body argument for the reference
//     -count reading and marks it as cross-body evidence, not as something
//     these instructions state;
//   * whether the word may legally hold 0 or a negative value on entry. The
//     body tests nothing, so a receiver whose word is already 0x7fffffff
//     wraps to 0x80000000. That is the observed behaviour and the model
//     reproduces it; whether any caller can reach it is not established here;
//   * the class that owns the vtable slot. There is no MSVC RTTI in this
//     binary, so the owning class is not recoverable from these instructions.
//   * the declared return TYPE. See the return-semantics note below.
//
// CROSS-BODY EVIDENCE, kept separate from the machine evidence above.
//
// The committed vtable export (`.spore-analysis/ghidra-exports/vtables.json`)
// records 342 HIGH-confidence tables whose slots contain 0x00c6a960. Of those,
// 341 also contain 0x007b86e0, and in 338 the partner sits at slot +1, i.e.
// immediately after this entry. That partner body's own listing is
// `mov eax,[ecx+8]; add ecx,4; add eax,-1; mov [ecx+4],eax; ...` - a
// decrement of the same word at the same +0x8 displacement. An entry that
// increments and an immediately following entry that decrements the same
// receiver word is a retain/release pair, and that reading is what the
// variable names in this package reflect. It remains a cross-body inference:
// this package's own target does not state it.
//
// Three tables place the partner at slot -1 rather than +1
// (0x01455a2c, and two others), so "+1 in every table" is FALSE and is not
// claimed. One further table contains this entry with no partner at all. The
// slot index itself varies per table (0 through 36 across the 342), which is
// the normal shape for an inherited virtual: the index is a property of the
// owning class, not of the entry.
//
// RETURN SEMANTICS. EAX holds the post-increment value at the RET. That is a
// statement about the machine state, not about the source-level signature:
// Ghidra types the entry `void __fastcall FUN_00c6a960(int)`, the derived ABI
// record reports return_semantics=unclassified_in_EAX with void_possible=false,
// and none of the 35 sampled call sites reads EAX afterwards. This header
// therefore declares the return as `std::int32_t` (the value EAX provably
// carries) and the port type documents that no observed caller consumes it. A
// `void`-returning declaration would compile to the same eight bytes; which one
// the original source used is not established.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c6a960 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00C6A960_THISCALL __thiscall
#else
#define PKG_00C6A960_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c6a960_refcount_increment {

static_assert(sizeof(void*) == 4,
              "FUN_00c6a960 reconstruction requires 32-bit pointers");
static_assert(sizeof(std::int32_t) == 4,
              "the +0x8 word the body reads and writes is 32 bits wide");
static_assert(sizeof(std::uint32_t) == 4,
              "the +0x8 word the body reads and writes is 32 bits wide");

// The single displacement this body names, from `MOV EAX,dword ptr
// [ECX + 0x8]` and `MOV dword ptr [ECX + 0x8],EAX`. Stated as a value rather
// than as a member name: the receiver record enumerates displacements
// (bounds_only) and does not say which member is which. The increment applied
// to it, from INC EAX, is the second constant the body names.
constexpr std::size_t kCounterDisplacement = 0x8;
constexpr std::int32_t kCounterIncrement = 1;

// The receiver, modelled exactly as far as the machine reached and no further.
// The dispatch record puts a vptr at +0x00 and 0x00c6a960 is the target of a
// slot load out of such a table in 342 recorded tables, but the body itself
// never reads [ECX+0x00] - it is the dispatch word, not data this entry reads.
// +0x04 is opaque and is never touched. +0x08 is the word the body reads and
// writes. The extent is a modelling bound, not a recovered allocation size.
struct alignas(4) OpaqueRefCountedReceiver {
  void** vtable_000 = nullptr;                    // +0x00, dispatch word
  std::uint8_t opaque_004 = 0;                   // +0x04, never touched
  std::int32_t counter_008 = 0;                  // +0x08, read and written
};

static_assert(sizeof(OpaqueRefCountedReceiver) == 0x0c,
              "modeled receiver extent through the last word the body writes");
static_assert(offsetof(OpaqueRefCountedReceiver, vtable_000) == 0x00,
              "the dispatch word is at receiver+0x00");
static_assert(offsetof(OpaqueRefCountedReceiver, opaque_004) == 0x04,
              "the opaque byte sits at receiver+0x04");
static_assert(offsetof(OpaqueRefCountedReceiver, counter_008) == 0x08,
              "the counted word is at receiver+0x08");
static_assert(kCounterDisplacement ==
                  offsetof(OpaqueRefCountedReceiver, counter_008),
              "the header constant is the displacement the listing names");
static_assert(kCounterDisplacement + sizeof(std::int32_t) ==
                  sizeof(OpaqueRefCountedReceiver),
              "the counted word ends the modeled receiver extent");

// The only way this package touches the receiver: a 4-byte word at a stated
// displacement, addressed arithmetically. A member access would assert an
// identity the bounds_only receiver record cannot confirm.
inline std::int32_t* word_at(OpaqueRefCountedReceiver* receiver,
                             std::size_t displacement) {
  return reinterpret_cast<std::int32_t*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

inline const std::int32_t* word_at(const OpaqueRefCountedReceiver* receiver,
                                   std::size_t displacement) {
  return reinterpret_cast<const std::int32_t*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// The port type of the virtual slot this entry occupies. No recorded call site
// reads EAX after the call, so the return value is modelled because the
// machine state fixes it, not because a caller consumes it. The slot index
// differs per owning table (0..36 across the 342 HIGH-confidence tables), so
// no index is baked into the type.
using RefCountIncrement00c6a960 =
    std::int32_t(PKG_00C6A960_THISCALL*)(OpaqueRefCountedReceiver*);

// The eight bytes read live at 0x00c6a960..0x00c6a967. Stated here so the
// reconstruction's instruction sequence is pinned in code and not only in
// prose. The 0xcc INT3 pad at 0x00c6a968 is deliberately excluded.
constexpr std::uint8_t kTargetBytes[8] = {
    0x8b, 0x41, 0x08, 0x40, 0x89, 0x41, 0x08, 0xc3,
};

// 0x00c6a960  MOV EAX,dword ptr [ECX + 0x8]
// 0x00c6a963  INC EAX
// 0x00c6a964  MOV dword ptr [ECX + 0x8],EAX
// 0x00c6a967  RET
//
// Returns the post-increment value; see the return-semantics note above.
extern "C" std::int32_t PKG_00C6A960_THISCALL refcount_increment_00c6a960(
    OpaqueRefCountedReceiver* receiver);

// 0x00801220  JMP 0x00c6a960
//
// A one-instruction tail thunk onto this entry, observed in the caller list as
// thunk_FUN_00c6a960. It adjusts no register, pushes nothing and returns to its
// own caller, so the thunk's receiver is this entry's receiver unchanged. It
// is declared here only so the model test can dispatch through it; it is not a
// separate target.
extern "C" std::int32_t PKG_00C6A960_THISCALL thunk_00801220_jmp_00c6a960(
    OpaqueRefCountedReceiver* receiver);

}

#undef PKG_00C6A960_THISCALL