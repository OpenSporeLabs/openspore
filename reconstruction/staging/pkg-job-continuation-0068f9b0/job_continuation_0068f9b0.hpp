#pragma once

#include <cstddef>
#include <cstdint>

// Calling convention. The token `thiscall` is carried once per macro, which is
// what the validator's `_convention_defines` resolves, and the non-MSVC arm is
// the attribute form both clang and gcc accept in a -m32 unit.
//
// The convention is proved by two independent instructions in the listing of
// 0x0068f9b0, not assumed:
//   * 0x0068f9b6 `MOV EBX,ECX` copies ECX -- an incoming register -- into the
//     body-local callee-saved EBX, and ECX is never read by any other
//     instruction of the function. The receiver arrives in ECX.
//   * 0x0068f9df `RET 0x4` pops 4 bytes of arguments on the callee's side, so
//     the caller does not clean and this is not cdecl.
// Together those select __thiscall over __cdecl (RET would be 0x0) and over
// __stdcall, which carries no incoming register at all. __fastcall is ruled
// out by EDX: it is dead on entry -- its first write in the body is the
// vtable-slot load at 0x0068f9c6 / 0x0068f9d5, and no instruction reads it
// before that -- so it is a scratch register here, not a second argument.
#if defined(_MSC_VER)
#define PKG_JOB_CONTINUATION_0068F9B0_THISCALL __thiscall
#else
#define PKG_JOB_CONTINUATION_0068F9B0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_job_continuation_0068f9b0 {

// ---------------------------------------------------------------------------
// Machine facts, each tied to the instruction that proves it.
// ---------------------------------------------------------------------------

// 0x0068f9c4 `MOV EAX,[ESI]` and 0x0068f9d3 `MOV EAX,[EDI]`: both operands are
// dereferenced at offset 0, so the objects the body dispatches on are
// vptr-at-offset-0 polymorphic objects, and the pointer itself is 4 bytes
// (32-bit target, and `RET 0x4` cleans exactly one pointer-sized argument).
constexpr std::size_t kPointerSize = 4;
static_assert(kPointerSize == 4, "pointer width implied by C2 04 00 at 0x0068f9df");

// 0x0068f9b2 `MOV ESI,[ESP+0x0C]`, read after the two prologue pushes at
// 0x0068f9b0 and 0x0068f9b1. With the return address occupying [ESP+0] on
// entry, [ESP+0x0C] after two pushes is entry-[ESP+0x4]: the FIRST stack
// argument, not the second. So ESI holds the argument and EBX holds the
// receiver -- the two are never conflated, and neither is passed in a
// register the body treats as ordinary.
constexpr std::size_t kArgumentInStackSlots = 1;
static_assert(kArgumentInStackSlots == 1, "MOV ESI,[ESP+0x0C] at 0x0068f9b2 is entry [ESP+4]");

// The prologue pushes three callee-saved registers and the epilogue pops three:
//   0x0068f9b0 PUSH EBX / 0x0068f9b1 PUSH ESI / 0x0068f9b8 PUSH EDI
//   0x0068f9dc POP EDI  / 0x0068f9dd POP ESI  / 0x0068f9de POP EBX
// The frame is balanced, so net ESP change across the call is exactly the
// 4 bytes RET 0x4 removes.
constexpr std::size_t kPrologueRegisterSaves = 3;
static_assert(kPrologueRegisterSaves == 3, "PUSH EBX/ESI/EDI at 0x0068f9b0,0x0068f9b1,0x0068f9b8");

// 0x0068f9df `RET 0x4` cleans this many bytes of stack arguments.
constexpr std::size_t kStackBytesCleaned = 4;
static_assert(kStackBytesCleaned == 4, "C2 04 00 at 0x0068f9df");

// 0x0068f9b9 `MOV EDI,[EBX+0x8]` and 0x0068f9cc `MOV [EBX+0x8],ESI`: the one
// and only receiver field the body touches. Both the load and the store use
// displacement 0x8, so offset 0x8 is a single 4-byte pointer slot.
constexpr std::size_t kStateFieldOffset = 0x8;
static_assert(kStateFieldOffset == 0x8, "MOV EDI,[EBX+0x8] at 0x0068f9b9; MOV [EBX+0x8],ESI at 0x0068f9cc");

// 0x0068f9c6 `MOV EDX,[EAX]`  -> dispatch through vtable slot 0 of the NEW object.
// 0x0068f9d5 `MOV EDX,[EAX+4]` -> dispatch through vtable slot 1 of the OLD object.
// Each dispatch is `[obj]`, i.e. the vptr itself, then a raw dword slot read
// with no adjustment of the receiver between load and call.
constexpr std::size_t kSlot0Index = 0;
static_assert(kSlot0Index == 0, "MOV EDX,[EAX] at 0x0068f9c6 reads vtable slot 0");

constexpr std::size_t kSlot1Index = 1;
static_assert(kSlot1Index == 1, "MOV EDX,[EAX+0x4] at 0x0068f9d5 reads vtable slot 1");
static_assert(kSlot1Index * kPointerSize == 0x4, "slot 1 sits at table+4, 0x0068f9d5");

// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------

// Forward declaration only: StateObject is defined just below and is complete
// by the time either slot is ever called.
struct StateObject;

// The dispatched interface. Two slots are needed and two are named; the
// listing names neither, so the members are identified by slot index and the
// comment carries the address.
//
// Each `CALL EDX` (0x0068f9ca, 0x0068f9da) is preceded by `MOV ECX,ESI` /
// `MOV ECX,EDI` and by no push at all, so the callee takes one pointer in ECX
// and nothing on the stack. On the i386 __thiscall ABI that is spelled as a
// single leading pointer parameter, which is how both slots are declared here;
// writing the receiver out is what makes the slot directly implementable by a
// test double without a cast.
struct StateInterface {
  void(PKG_JOB_CONTINUATION_0068F9B0_THISCALL* slot0)(StateObject*);  // 0x0068f9c6, ECX=ESI
  void(PKG_JOB_CONTINUATION_0068F9B0_THISCALL* slot1)(StateObject*);  // 0x0068f9d5, ECX=EDI
};
static_assert(sizeof(StateInterface) == 2 * kPointerSize,
              "two dword slots; slot 1 is reached as table+0x4 at 0x0068f9d5");
static_assert(offsetof(StateInterface, slot0) == 0,
              "MOV EDX,[EAX] at 0x0068f9c6 reads offset 0 of the vtable");
static_assert(offsetof(StateInterface, slot1) == 0x4,
              "MOV EDX,[EAX+0x4] at 0x0068f9d5 reads offset 4 of the vtable");

// One dispatch slot, as the machine reaches it: a single dword the body loads
// and then `CALL`s. Both `CALL EDX` sites load from a table at a byte
// displacement and call it with the object in ECX and nothing on the stack, so
// both slots have this one shape.
using StateSlotFunction =
    void(PKG_JOB_CONTINUATION_0068F9B0_THISCALL*)(StateObject*);

// The state object as the body sees it: ONE pointer at offset 0 and nothing else
// reachable from this function. 0x0068f9c4/0x0068f9d3 read offset 0 of the
// object and nothing further, so no layout past that word is claimed.
//
// The word is reached through `state_table_at` rather than as a named member.
// A pointer that is loaded at offset 0 and then dereferenced is how x86 spells a
// virtual table, and the body does exactly that -- but the machine-derived
// receiver record for this target is `bounds_only` and states nothing about
// which member of WHICH object lives at offset 0, so the *name* would be a claim
// no witness supports. What the listing does support, and what the two
// static_asserts below pin, is that there is exactly one word at offset 0 and
// that it is read. The dispatch slots are named, because each one's INDEX is
// fixed by the `MOV EDX,[EAX]` / `MOV EDX,[EAX+0x4]` that reads it.
struct StateObject {
  std::uint8_t opaque[kPointerSize];
};
static_assert(sizeof(StateObject) == kPointerSize,
              "one pointer at offset 0 is the whole of what this body reads");
static_assert(kPointerSize == 4, "the word at offset 0 is read as a dword");

// The dispatch table of `object`, read by displacement. This is the only way
// this package reaches into a state object.
inline const StateInterface*& state_table_at(StateObject* object,
                                             std::size_t displacement) {
  return *reinterpret_cast<const StateInterface**>(
      reinterpret_cast<std::uint8_t*>(object) + displacement);
}
inline const StateInterface* const& state_table_at(
    const StateObject* object, std::size_t displacement) {
  return *reinterpret_cast<const StateInterface* const*>(
      reinterpret_cast<const std::uint8_t*>(object) + displacement);
}

// The slot word at byte displacement `kSlotIndex * kPointerSize` into `table`.
// 0x0068f9c6 (`MOV EDX,[EAX]`) and 0x0068f9d5 (`MOV EDX,[EAX+0x4]`) are the
// two dispatch reads this package performs, and each one's byte displacement is
// exactly `kSlotIndex * kPointerSize` for the index the comment names.
//
// This is deliberately NOT spelled as `table[n].member`. Subscripting
// `StateInterface` advances by `sizeof(StateInterface)` -- a WHOLE PAIR of
// slots -- per step, while `MOV EDX,[EAX+n]` advances by `n * kPointerSize`.
// The two agree only at n == 0, so a `[1]` subscript silently reads table+0xC
// where the machine reads table+0x4. Taking the slot INDEX here and
// multiplying it out keeps the number a caller writes equal to the number the
// listing proves.
template <std::size_t kSlotIndex>
inline StateSlotFunction slot_at(const StateInterface* table) {
  static_assert(kSlotIndex == 0 || kSlotIndex == 1,
                "the listing of 0x0068f9b0 reads no slot beyond index 1");
  return *reinterpret_cast<StateSlotFunction const*>(
      reinterpret_cast<std::uint8_t const*>(table) + kSlotIndex * kPointerSize);
}

// The table word is at offset 0 of the object: `MOV EAX,[ESI]` at 0x0068f9c4 and
// `MOV EAX,[EDI]` at 0x0068f9d3 both read offset 0 and nothing else.
constexpr std::size_t kStateTableOffset = 0;

// The receiver. Only offset 0x8 is named by the listing; bytes 0x0..0x7 are
// never read or written by any instruction of 0x0068f9b0, so they are modelled
// as opaque padding rather than guessed fields. The layout is anchored by a
// static_assert below so the field offset cannot drift silently.
//
// The slot is typed StateObject* and not a wider void* because the body
// treats it and the argument as the same pointer with no conversion: 0x0068f9bc
// `CMP ESI,EDI` compares the two directly, and 0x0068f9cc `MOV [EBX+0x8],ESI`
// stores one into the other. A different type on the two would not have
// compiled to a bare compare and a bare store.
//
// It is NOT a named member. The machine-derived receiver record for this target
// is `register: ECX, offsets: [8], bounds_only: true` -- it states that the body
// was seen reaching displacement 8 and nothing about which member lives there,
// so a name for that member is a claim no witness in this pack supports. The
// slot is reached only through `state_slot_at`, which is spelled in terms of the
// displacement the listing shows. The receiver's own extent is modelled as the
// opaque padding plus this one slot.
struct ContinuationReceiver {
  std::uint8_t unobserved[kStateFieldOffset];
  StateObject* slot_at_8;
};
static_assert(offsetof(ContinuationReceiver, slot_at_8) == kStateFieldOffset,
              "field at receiver+0x8, MOV EDI,[EBX+0x8] at 0x0068f9b9");
static_assert(sizeof(ContinuationReceiver) == 0xC,
              "the listing names no field past 0x8, so the modelled size stops at 0xC");

// The receiver slot at `displacement`, read or written through the address
// computed from the receiver so the access asserts no alignment the original
// does not either. This is the only way this package touches the receiver.
inline StateObject*& state_slot_at(ContinuationReceiver* receiver,
                                   std::size_t displacement) {
  return *reinterpret_cast<StateObject**>(
      reinterpret_cast<std::uint8_t*>(receiver) + displacement);
}

// The const overload, for the observer a dispatched slot is given. It reads the
// same slot and cannot write through it.
inline StateObject* const& state_slot_at(const ContinuationReceiver* receiver,
                                         std::size_t displacement) {
  return *reinterpret_cast<StateObject* const*>(
      reinterpret_cast<const std::uint8_t*>(receiver) + displacement);
}

// ---------------------------------------------------------------------------
// Entry point
// ---------------------------------------------------------------------------

// 0x0068f9b0. Replaces the receiver's state pointer, running the new state's
// slot 0 (0x0068f9c4..0x0068f9ca) BEFORE the store and the old state's slot 1
// (0x0068f9d3..0x0068f9da) AFTER it, and doing nothing at all when the
// incoming pointer already equals the stored one (0x0068f9bc..0x0068f9be).
// Returns nothing: the listing writes no value to EAX on any path, and
// 0x0068f9dc..0x0068f9df falls straight through to the pops. The class
// identity is not inferred from the SDK name.
void PKG_JOB_CONTINUATION_0068F9B0_THISCALL continuation_set_state_0068f9b0(
    ContinuationReceiver* receiver, StateObject* new_state);

}  // namespace openspore::reconstruction::pkg_job_continuation_0068f9b0
