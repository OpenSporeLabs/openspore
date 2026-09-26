#include "slot_vector_005c8480.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {
namespace {

// Receiver field offsets, each proven by a named instruction.
constexpr std::size_t kFirst = 0x0;      // 0x005c854e  mov eax, [edi]
constexpr std::size_t kLast = 0x4;       // 0x005c8489  mov eax, [edi + 4]
constexpr std::size_t kCapacity = 0x8;   // 0x005c848c  cmp eax, [edi + 8]

constexpr std::size_t kElementSize = 4;
// 0x005c8501 shifts the used count right by 2 to convert bytes to slots.
constexpr int kUsedCountShift = 2;
// 0x005c8524 pushes capacity*16 as the allocation size, i.e. 4 slots per
// capacity unit times 4 bytes per slot after the doubling at 0x005c8522.
constexpr int kSlotsPerCapacityUnit = 4;
constexpr std::size_t kAllocTag = 0xd1;  // 0x005c8512  push 0xd1
constexpr std::uint32_t kAllocGroup = 0x13ebb38;   // 0x005c8517
constexpr std::uint32_t kAllocType = 0x13eb430;    // 0x005c8524 ("Editor")

inline void** slot(Opaque5c8480SlotVector* self, std::size_t off) {
  return reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(self) + off);
}

}  // namespace

// 0x005c8480 -- 335 bytes, 133 instructions, read live in full.
//
// Two arms, split by 0x005c848c (CMP EAX,[EDI+8]; JZ 0x005c84ff):
//
//   grow arm (0x005c84ff..0x005c85c2) -- taken when last == capacity:
//     used = (last - first) / 4 as a signed count; if it is <= 0 the new
//     capacity is 1, otherwise it is doubled (0x005c8508  add eax, eax).
//     Capacity 0 is special-cased to a null block (0x005c8546) and the copy
//     is then skipped. Otherwise port_00f473a0 allocates
//     capacity*4*4 bytes tagged "Editor" (0x013eb430, read live as
//     45 64 69 74 6f 72 00 00) at allocator line 0xd1.
//     Then: memcpy(new, first, (void*)position - first) (0x005c855f);
//     the slot one past the copied prefix takes the caller's value and that
//     value gets vtable slot +0x4 if non-null (0x005c8571..0x005c8582);
//     memcpy(new + position + 4, position, last - position) (0x005c858f);
//     the old block is freed through 0x00f47380 only when it is non-null AND
//     the dword in front of it is non-null (0x005c85a1..0x005c85aa), which is
//     the allocator's size/cookie word;
//     and finally first/capacity/last are all rewritten (0x005c85bd..0x005c85c2)
//     with last computed as new + (last - position)/4*4 + 4.
//
//   in-capacity arm (0x005c8489..0x005c84fc) -- taken when last != capacity:
//     the slot at `last` is overwritten with the value at `last - 4` and that
//     value gets vtable slot +0x4 if non-null (0x005c84aa..0x005c84b8);
//     0x005c1dc0 then shifts a range with refcount fixups;
//     the value one past `position` is moved into `*value_in_out` with slot
//     +0x4 on the incoming value and slot +0x8 on the value it displaced;
//     last is advanced by 4.
//
// vtable slots +0x4 and +0x8 are observed across the whole binary to fire on
// the value ENTERING a container slot and on the value LEAVING one: 0x005c1dc0
// at 0x005c1ded/0x005c1dfc, 0x005c8480 at 0x005c84df/0x005c84ef, 0x00573c00 at
// 0x00573caa, 0x0045ac20 at 0x0045adc2/0x0045ade2. They are recorded as
// attach-shaped and detach-shaped; neither is named, and no vtable was located
// for the payload type.
//
// Structural caveat, recorded rather than smoothed over: on the in-capacity
// arm 0x005c1dc0 is handed the SECOND argument as its loop lower bound
// (0x005c84c2 push ebp), while the slot that receives the moved value is
// derived from the FIRST argument (0x005c8491 / 0x005c84a3). Those two only
// agree when the second argument is itself a slot inside the array. Both
// inspected callers (0x00586510 and 0x005c8a82) pass a stack address and
// only ever reach the grow arm, so the in-capacity arm's element algebra is
// reproduced structurally and is NOT claimed to be a correct general insert.
//
// Both inspected callers are the out-of-line slow half of a push_back whose
// fast half is inlined at the same site:
//   0x005864db  8b8664010000  mov eax, dword ptr [esi + 0x164]
//   0x005864e1  3b8668010000  cmp eax, dword ptr [esi + 0x168]
//   0x0058650a  8d5424 10     lea edx, [esp + 0x10]
//   0x0058650f  50            push eax
//   0x00586510  e86b1f0400    call 0x005c8480
// with the inlined fast half doing end++ / *old_end = value / value->slot4().
// cEditor +0x160 is the vector base (the SDK records cEditor +0x160 as
// `eastl::vector<DefaultRefCounted*> field_160`), so the receiver layout
// {first, last, capacity} at +0x160/+0x164/+0x168 matches the binary.

extern "C" void __thiscall FUN_005c8480_reconstruct(
    Opaque5c8480SlotVector* self,
    void* position,
    void** value_in_out) {
  void* const last = *slot(self, kLast);      // 0x005c8489
  void* const capacity = *slot(self, kCapacity);

  if (last != capacity) {
    // ---- in-capacity arm, 0x005c8489..0x005c84fc ----
    // 0x005c849b..0x005c84a3: the "one past position" cursor is only advanced
    // when position is strictly inside [value_in_out, last).
    auto* cursor = static_cast<std::uint8_t*>(position);
    if (!(position < value_in_out) && !(position >= last)) {
      cursor += kElementSize;
    }

    // 0x005c84a6..0x005c84b8: mirror the current last element into the slot
    // at `last` and run slot +0x4 on it.
    if (last != nullptr) {
      void* const previous_last = *reinterpret_cast<void**>(
          static_cast<std::uint8_t*>(last) - kElementSize);
      *reinterpret_cast<void**>(last) = previous_last;
      if (previous_last != nullptr) {
        auto* const vtable = *reinterpret_cast<void***>(previous_last);
        auto attach = reinterpret_cast<void (*)()>(vtable[1]);  // slot +0x4
        attach();
      }
    }

    // 0x005c84bd..0x005c84c3
    port_005c1dc0_shift_slots(value_in_out,
                              static_cast<std::uint8_t*>(last) - kElementSize,
                              last);

    // 0x005c84c8..0x005c84ef
    void* const incoming = *reinterpret_cast<void**>(cursor);
    void* const displaced = *value_in_out;
    if (incoming != displaced) {
      if (incoming != nullptr) {
        auto* const vtable = *reinterpret_cast<void***>(incoming);
        auto attach = reinterpret_cast<void (*)()>(vtable[1]);  // slot +0x4
        attach();
      }
      *value_in_out = incoming;
      if (displaced != nullptr) {
        auto* const vtable = *reinterpret_cast<void***>(displaced);
        auto detach = reinterpret_cast<void (*)()>(vtable[2]);  // slot +0x8
        detach();
      }
    }

    // 0x005c84f1
    *slot(self, kLast) = static_cast<std::uint8_t*>(last) + kElementSize;
    return;
  }

  // ---- grow arm, 0x005c84ff..0x005c85c2 ----
  auto used = static_cast<std::ptrdiff_t>(
      (static_cast<std::uint8_t*>(last) -
       static_cast<std::uint8_t*>(*slot(self, kFirst))) >>
      kUsedCountShift);

  // 0x005c8504..0x005c8546: a used count of 0 or less forces capacity 1, and
  // a capacity that doubles to 0 becomes a null block instead of an allocate.
  std::size_t new_capacity;
  void* new_block = nullptr;
  if (used <= 0) {
    new_capacity = 1;
  } else {
    auto doubled = static_cast<std::size_t>(used) * 2u;
    if (doubled == 0u) {
      new_capacity = 0;
      new_block = nullptr;  // 0x005c8546  mov dword ptr [esp+0x10], 0
    } else {
      new_capacity = doubled;
    }
  }

  if (new_block == nullptr && new_capacity != 0u) {
    // 0x005c8512..0x005c852a. The size argument is the capacity scaled twice
    // more (0x005c8520 / 0x005c8522), i.e. kSlotsPerCapacityUnit slots of
    // 4 bytes per capacity unit.
    new_block = port_00f473a0_alloc(
        new_capacity * kSlotsPerCapacityUnit * kElementSize, "Editor",
        kAllocGroup, kAllocType,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
        "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        kAllocTag);
  }

  // 0x005c8554..0x005c8567: copy [first, position) into the new block. The
  // memcpy return value is the block end, which is then biased by
  // (position - first)/4*4 -- the same value, so the copy length is
  // idempotent and only the running cursor matters.
  const std::size_t prefix_bytes = static_cast<std::size_t>(
      static_cast<std::uint8_t*>(position) -
      static_cast<std::uint8_t*>(*slot(self, kFirst)));
  auto* cursor = static_cast<std::uint8_t*>(
      memcpy(new_block, *slot(self, kFirst), prefix_bytes));

  // 0x005c856d..0x005c8582: the slot at the copy end takes the caller's
  // value, with slot +0x4 on it when non-null.
  if (cursor != nullptr) {
    void* const value = *value_in_out;
    *reinterpret_cast<void**>(cursor) = value;
    if (value != nullptr) {
      auto* const vtable = *reinterpret_cast<void***>(value);
      auto attach = reinterpret_cast<void (*)()>(vtable[1]);  // slot +0x4
      attach();
    }
  }

  // 0x005c8584..0x005c8597: shift the tail [position, last) up by one slot.
  const std::size_t tail_bytes = static_cast<std::size_t>(
      static_cast<std::uint8_t*>(last) - static_cast<std::uint8_t*>(position));
  cursor = static_cast<std::uint8_t*>(
      memcpy(cursor + kElementSize, position, tail_bytes));  cursor = static_cast<std::uint8_t*>(cursor) + (tail_bytes >> 2) * 4;

  // 0x005c859a..0x005c85af: release the old block, but only when both the
  // block and the allocator word in front of it are non-null.
  void* const old_block = *slot(self, kFirst);
  if (old_block != nullptr &&
      *reinterpret_cast<std::uint32_t*>(
          static_cast<std::uint8_t*>(old_block) - 4) != 0u) {
    port_00f47380_free(old_block);
  }

  // 0x005c85b2..0x005c85c2
  *slot(self, kLast) = cursor;
  *slot(self, kFirst) = new_block;
  *slot(self, kCapacity) = static_cast<std::uint8_t*>(new_block) +
                           new_capacity * kElementSize;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
