// 0x007f8d10 — 0x007f8d10..0x007f8ef0, 158 instructions.
//
// Annotated listing (abridged; the full machine listing is the oracle).
//
// ABI.  `SUB ESP,0x8c` / `PUSH EBP,EBX,ESI,EDI` / `RET 0xc`: __thiscall with
// three 4-byte callee-cleaned stack arguments and a 0x8c-byte frame.  Frame
// arithmetic, used throughout:
//     entry_ESP = E0
//     0x007f8d10 SUB ESP,0x8c            ESP = E0-0x8c
//     0x007f8d16 PUSH EBP                 ESP = E0-0x90
//     0x007f8d3b PUSH EBX                 ESP = E0-0x94
//     0x007f8d3e PUSH ESI                 ESP = E0-0x98
//     0x007f8d56 PUSH EDI                 ESP = E0-0x9c
// so [ESP+0x94]=E0+0x4=arg1, [ESP+0x98]=E0+0x8=arg2, [ESP+0xa0]=E0+0x4=arg1,
// [ESP+0xa4]=E0+0x8=arg2, [ESP+0xa8]=E0+0xc=arg3, and [ESP+0x14]=E0-0x88 is
// the first word of the 0x88-byte stack prototype (the frame's low 0x8c bytes
// are exactly one element plus one pad word).
//
//   0x007f8d17 MOV EBP,[ESP+0x98]         arg2 -> EBP
//   0x007f8d1e MOV [ESP+0x4],ECX          spill the receiver
//   0x007f8d22 TEST EBP,EBP / JZ 0x007f8ee9     arg2 == 0 -> return
//   0x007f8d31 CMP dword ptr [EAX+0x4],0 / JZ 0x007f8ee9
//                                             arg1->[+4] == 0 -> return
//   0x007f8d3f LEA ESI,[ECX+0x4]           ESI = this+4, so [ESI]=begin,
//                                           [ESI+4]=end, [ESI+8]=capacity
//
// Element count.  0x007f8d47/0x007f8d4c load 0x78787879, IMUL by
// (end-begin) and 0x007f8d53 SAR EDX,6, then SHR 0x1f / ADD round it toward
// zero.  That is the signed division by 0x88: 0x78787879 * 0x88 = 0x40_0000_0038
// >= 2^38, and 0x78787879 * 0x89 = 0x40_0000_00B1 > 2^38 + 0x88, so the magic
// is exact for 0x88 and for nothing else.  The same sequence is recomputed at
// 0x007f8d9e, 0x007f8dc8 and 0x007f8da3 because the compiler does not keep the
// count live across the loop.
//
// Search (0x007f8d71..0x007f8db8, EBX = index, EBP = cursor):
//   0x007f8d71 JZ 0x007f8dc1               count == 0 -> skip
//   0x007f8d73 MOV EBP,[ESI]               cursor = begin
//   0x007f8d75 MOV EAX,[EBP] / 0x007f8d78 TEST EAX,EAX / 0x007f8d7a JZ 0x007f8e48
//                                           a null key terminates the scan
//   0x007f8d80 CMP EAX,[ESP+0xa4]          key == arg2 ?
//   0x007f8d90 CMP dword ptr [EBP+0x4],EDX / JZ 0x007f8e1c
//                                           and element->selector == arg3
//   0x007f8d99..0x007f8db8                 ++index; cursor += 0x88; loop while
//                                           index < count
// On a match, 0x007f8e1c..0x007f8e43 dispatches the embedded object's slot 0
// with (0.0f, 0.0f, 1, 0), reloads EBP = arg2 and jumps to 0x007f8dc3 — note it
// jumps PAST the FSTP ST0 at 0x007f8dc1, because the found path already
// consumed the FLDZ at 0x007f8e2a/0x007f8e31.  On the null-key break and on loop
// exhaustion, EBP is restored to arg2 and EDI is set to EBX.
//
// 0x007f8dc1 FSTP ST0 / 0x007f8e4f FSTP ST0     pop the FLDZ of 0x007f8d3c
// 0x007f8dc3..0x007f8ddb                         recompute count; if
//                                                 EDI != count, the matched
//                                                 index is reused in place
//                                                 (0x007f8e83)
//
// Append (0x007f8de1..0x007f8e81).  The prototype is pre-initialised with four
// words and then consumed:
//   0x007f8de6 [ESP+0x14] = 0                proto+0x00
//   0x007f8dea [ESP+0x1c] = 0x013f6400      proto+0x08
//   0x007f8df2 [ESP+0x24] = 0x013f63fc      proto+0x10
//   0x007f8dfa [ESP+0x28] = 0                proto+0x14
//   0x007f8dfe CMP ECX,[ESI+0x8] / JNC 0x007f8e58   end >= capacity -> grow
//   0x007f8e03..0x007f8e09                  end += 0x88
//   0x007f8e0c CMP ECX,EBX / JZ 0x007f8e83   end was 0 -> nothing to clone
//   0x007f8e15 CALL 0x007f6d90               ECX = the old end, arg = &proto
//   0x007f8e60 CALL 0x007f8820               ECX = this, args (old end, &proto)
//   0x007f8e65..0x007f8e72                  release proto+0x14 through slot 1
//   0x007f8e74..0x007f8e81                  release proto+0x00 through slot 1
//
// Install (0x007f8e83..0x007f8ea7).  slot = begin + index*0x88.
//   0x007f8e8b MOV ESI,[EDI]                displaced = slot->key
//   0x007f8e8d CMP EBP,ESI / JZ 0x007f8ea9  displaced == arg2 -> nothing to do
//   0x007f8e91..0x007f8e98                  dispatch arg2 through slot 0
//   0x007f8e9a MOV [EDI],EBP                slot->key = arg2
//   0x007f8e9c..0x007f8ea7                  if displaced, release it, slot 1
//
// Refresh (0x007f8ea9..0x007f8ed9)
//   0x007f8ebd MOV [EDI+0x4],EAX            slot->selector = arg3
//   0x007f8ec0 CALL 0x007f6ff0              ECX = slot+0x08, arg = arg1
//   0x007f8ed9 CALL EDX                     ECX = slot+0x08, EDX = slot[0xc],
//                                           args (slot+0x08, 0.0f, 0.0f, 0, 0)
//
// Publish and exit
//   0x007f8edb MOV EAX,[ESP+0x24]           the spilled receiver
//   0x007f8ee4 MOV byte ptr [EAX+0x1c],0x1
//   0x007f8eea ADD ESP,0x8c / 0x007f8ef0 RET 0xc
//
// Return value.  The ABI record's `return_semantics: float_or_x87_in_ST0` is a
// heuristic artifact of the FLDZ at 0x007f8d3c and is NOT what the body does.
// The x87 stack is empty at every RET, traced opcode by opcode (D9EE = FLDZ,
// DDD8 = FSTP ST0, both read back from the image):
//   0x007f8d24 / 0x007f8d35 early exits   FLDZ not yet executed -> depth 0
//   count == 0            0x007f8dc1 pop   1 -> 0
//   null key / exhausted  0x007f8e4f pop   1 -> 0
//   match                 0x007f8e2a FST peeks, 0x007f8e31 FSTP pops  1 -> 0,
//                         and 0x007f8e43 jumps past 0x007f8dc1
//   every path 0x007f8ec5 FLDZ 0 -> 1, 0x007f8ed1 FST peeks,
//                         0x007f8ed5 FSTP pops  1 -> 0
// Both FLDZ sites exist only to materialise the 0.0f that is then stored twice,
// as the second and third arguments of the dispatch at 0x007f8ed9 (and of the
// one at 0x007f8e35).  The return type is therefore void.
//
// NOT established, and not claimed anywhere above:
//   * the meaning of arg1 beyond its size (at least 0x80 bytes: 0x007f6ff0
//     copies 0x70 bytes from arg1+0x10 and reads arg1+0x04 and arg1+0x0c) and
//     of arg3, which is only ever compared and stored as a 32-bit word;
//   * the concrete class behind the two prototype vtable words 0x013f6400 and
//     0x013f63fc.  The committed edge export collapses both rows to the base
//     0x013f63fc and discards the slot addresses, and no indirect transfer in
//     this body dispatches through either word, so no slot index was needed and
//     none is asserted;
//   * the six indirect transfers' concrete callees.  Four of them
//     (0x007f8e72, 0x007f8e81, 0x007f8e98, 0x007f8ea7) dispatch through a
//     Handle's own leading vtable word and two (0x007f8e35, 0x007f8ed9)
//     through element+0x0c; all six are recorded as ports;
//   * the identity of 0x007f6d90 / 0x007f8820 / 0x007f6ff0 beyond the bodies
//     quoted in the header.  Two of the calls inside 0x007f8820
//     (`FUN_007f6d90(this->end - 0x88)` and `FUN_007f6d90(param_3)`) reach
//     Ghidra as one-argument calls, so their second argument is not recoverable
//     from the decompilation, and 0x007f7c00 / 0x007f7920 — the two calls that
//     initialise the new element on the grow route — were not resolved at all.
//     That matters: on the in-place route the new element's +0x00 is the
//     prototype's null, so 0x007f8ea7 (release a displaced handle) is dead
//     there, whereas on the grow route 0x007f7c00 moves the last live element
//     into the slot and its +0x00 is very probably non-null.  Which of the two
//     happens is decided by [end >= capacity] at 0x007f8dfe and is not settled
//     here;
//   * whether arg1 is required non-null.  0x007f8d31 reads arg1+0x04 with no
//     test of arg1, so a null arg1 faults rather than returning; the guard is
//     modelled exactly as written and is not hardened;
//   * the class of the receiver, and the 0x0c bytes at receiver+0x10..+0x1b.

#include "registry_ensure_entry_007f8d10.hpp"

namespace openspore::pkg_007f8d10 {
namespace {

// 0x007f8dc1 / 0x007f8d3f: the count is recomputed four times in the body from
// this one expression, signed and truncated toward zero.
std::uint32_t element_count(const Registry* self) noexcept {
    const auto bytes = static_cast<std::intptr_t>(self->end - self->begin);
    return static_cast<std::uint32_t>(bytes / static_cast<std::intptr_t>(kElementStride));
}

Element* element_at(const Registry* self, std::uint32_t index) noexcept {
    return reinterpret_cast<Element*>(self->begin + index * kElementStride);
}

constexpr std::uint32_t kNotFound = 0xffffffffu;

}  // namespace

void registry_ensure_entry_007f8d10(Registry* self, const void* arg1, void* arg2,
                                    std::uint32_t arg3) noexcept {
    // 0x007f8d22: the key handle is tested; a null key is a clean no-op.
    if (arg2 == nullptr) {
        return;
    }
    // 0x007f8d31: only arg1's word at +0x04 is tested, never arg1 itself.
    // 0x007f6ff0 copies that word into the element's dispatch word and the body
    // calls it twice, so this gate is "the template carries a callback".
    if (*reinterpret_cast<void* const*>(static_cast<const std::uint8_t*>(arg1) + 0x04) ==
        nullptr) {
        return;
    }

    Handle* const key = static_cast<Handle*>(arg2);

    // 0x007f8d71..0x007f8db8.  A null key in a slot ends the scan without a
    // match, exactly like running off the end: both leave index < count and
    // reuse the slot in place.
    std::uint32_t index = 0;
    const std::uint32_t count = element_count(self);
    if (count != 0u) {
        Element* cursor = element_at(self, 0);
        for (;;) {
            if (cursor->key_00 == nullptr) {
                break;
            }
            if (cursor->key_00 == key && cursor->selector_04 == arg3) {
                // 0x007f8e2e..0x007f8e35: this is the only difference between the
                // matched path and the reused one — the element is refreshed
                // before the install block runs, and `index` already names this
                // cursor.
                sub_dispatch_slot0(&cursor->sub_08, 0.0f, 0.0f, 1u, 0u);
                break;
            }
            ++index;
            if (index >= count) {
                break;
            }
            ++cursor;
        }
    }

    // 0x007f8dc3..0x007f8ddb: index == count means nothing was matched, so a new
    // element is appended.  EDI carried the loop index on the matched paths and
    // the count on the other two.
    if (index == count) {
        Proto proto;
        proto.handle_00 = nullptr;
        proto.vtable_08 = kElementVtableA;
        proto.vtable_10 = kElementVtableB;
        proto.handle_14 = nullptr;

        std::uint8_t* const old_end = self->end;
        if (old_end >= self->capacity) {
            // 0x007f8e58: ECX = this, args (old end, &proto).
            registry_place_one_more_007f8820(self, old_end, &proto);
        } else {
            // 0x007f8e03..0x007f8e15: bump first, then clone the last element
            // into the slot the bump just opened.  With no live element there is
            // nothing to clone and the prototype is only torn down.
            self->end = old_end + kElementStride;
            if (old_end != nullptr) {
                proto_copy_assign_007f6d90(old_end, &proto);
            }
        }

        // 0x007f8e65: proto+0x14 is released before proto+0x00.
        if (proto.handle_14 != nullptr) {
            handle_dispatch_slot1(proto.handle_14);
        }
        if (proto.handle_00 != nullptr) {
            handle_dispatch_slot1(proto.handle_00);
        }
    }

    // 0x007f8e83..0x007f8e9a: install the key.  A slot already holding this
    // exact key is left completely alone.
    Element* const slot = element_at(self, index);
    void* const displaced = slot->key_00;
    if (displaced != key) {
        handle_dispatch_slot0(key);
        slot->key_00 = key;
        // 0x007f8e9c: only a genuinely displaced handle is released.
        if (displaced != nullptr) {
            handle_dispatch_slot1(static_cast<Handle*>(displaced));
        }
    }

    // 0x007f8ebd..0x007f8ed9: refresh the element from the template, then
    // dispatch the embedded object's slot 0 a second time, this time with the
    // last two arguments 0 rather than (1, 0).
    slot->selector_04 = arg3;
    element_assign_template_007f6ff0(&slot->sub_08, arg1);
    sub_dispatch_slot0(&slot->sub_08, 0.0f, 0.0f, 0u, 0u);

    // 0x007f8ee4.
    self->flag_1c = 1u;
}

}  // namespace openspore::pkg_007f8d10
