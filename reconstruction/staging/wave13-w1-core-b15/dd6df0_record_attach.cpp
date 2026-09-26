// 0x00dd6df0 — 0x00dd6df0..0x00dd6eba, 74 instructions, 205 bytes.
//
//   0x00dd6df0 PUSH EBX
//   0x00dd6df1 MOV EBX,dword ptr [ESP + 0xc]   first stack argument
//   0x00dd6df5 PUSH ESI
//   0x00dd6df6 PUSH EDI
//   0x00dd6df7 MOV EDI,ECX                      receiver -> EDI
//   ...  seven independent early exits to 0x00dd6eb5 ...
//   0x00dd6ead POP EDI / 0x00dd6eae POP ESI / 0x00dd6eaf MOV AL,0x1
//   0x00dd6eb1 POP EBX / 0x00dd6eb2 RET 0x8
//   0x00dd6eb5 POP EDI / 0x00dd6eb6 POP ESI / 0x00dd6eb7 XOR AL,AL
//   0x00dd6eb9 POP EBX / 0x00dd6eba RET 0x8
//
// __thiscall, two 4-byte stack arguments, `RET 0x8` so the callee pops both.
// The answer is a BOOLEAN written to AL only on both paths, so bits 8..31 of
// EAX are undefined on return and every consumer must test AL. 0x00dd6eaf
// writes the byte 1; 0x00dd6eb7 zeroes AL.
//
// The seven gates, in source order, each falling through to `return false`:
//
//   1  0x00dd6df9  arg1 == 0
//   2  0x00dd6e20  tree_lower_bound returned the header node (this + 0x2c),
//                  i.e. the key is not present
//   3  0x00dd6e2b  the mapped value (node + 0x14) is null
//   4  0x00dd6e42  global_lookup_port(0x035ee914) returned null
//   5  0x00dd6e59  the vtable +0xf0 call on that handle with (0x047d4388, 1)
//                  returned null
//   6  0x00dd6e6b  the vtable +0x0c call on the second handle with
//                  (0x00f15f4bd) returned null
//   7  0x00dd6e78  the record's byte range [+0x68, +0x6c) is empty, tested as
//                  `TEST ([rec+0x6c] - [rec+0x68]), 0xfffffffe` / JZ
//
// Only after all seven does it mutate and publish:
//
//   0x00dd6e80  PUSH EBX ; 0x00dd6e81 CALL 0x005c3d90
//   0x00dd6e86  AND dword ptr [ESI + 0xc],0xffffffbf   clear flag bit 6
//   0x00dd6e8a  OR  dword ptr [ESI + 0xc],0x1           set  flag bit 0
//   0x00dd6e8f  MOV ECX,EDI ; 0x00dd6e91 CALL 0x00dd60c0(this, rec)
//   0x00dd6e97  MOV ECX,EDI ; 0x00dd6e99 CALL 0x00dd5dd0(this, rec)
//   0x00dd6e9e  TEST EAX,EAX ; JZ skip
//   0x00dd6ea2  MOV EAX,dword ptr [EAX + 0x48]
//   0x00dd6ea5  PUSH EAX ; MOV ECX,EDI ; 0x00dd6ea8 CALL 0x00dd6bc0(this, key)
//   0x00dd6eaf  MOV AL,0x1 ; return true
//
// The map: ECX for the lookup is `LEA ECX,[EDI + 0x28]`, and 0x00e5c780 walks
// it as a red-black tree comparing node[+0x10] against the searched key and
// storing the best node through an out-parameter (it leaves that out-pointer in
// EAX, which is why 0x00dd6e1b dereferences EAX). The not-found sentinel it
// stores is the header node at tree + 4, i.e. `this + 0x2c`; 0x00dd5dd0 walks
// the same nodes as an in-order list from `this + 0x30` back to `this + 0x2c`.
//
// 0x00dd5dd0's key is not a scalar: it calls 0x0087d9a0 on
// (rec + 0x68, candidate + 0x68), and 0x0087d9a0 is a byte-range equality test
// that first compares (last - first) for both operands and then walks the bytes.
// So +0x68/+0x6c really are a (first, last) byte pair, and gate 7 is "the
// record carries a non-empty payload".
//
// What is NOT established: the meaning of the three descriptor constants
// 0x035ee914 / 0x047d4388 / 0x00f15f4bd (0x008105b0's decompiled body
// dereferences its argument at +0x14, and none of those addresses is mapped in
// the program image, so they are either runtime-remapped or the helper's
// argument is not a plain pointer); the concrete class of the handles returned
// by the two virtual calls; the meanings of flag bits 0, 6 and 9 of the record
// dword at +0xc (bit 9 is what 0x00dd5dd0 and 0x00dd6bc0 gate on); and the
// owning class of `this`. The two virtual slots +0xf0 and +0x0c are recorded
// with their offsets but their tables were not located, so no concrete callee
// is named.

#include "b15_opaque_types.hpp"

namespace openspore::wave13_w1_core_b15 {

// 0x00dd6e75 / 0x00dd6e6f: the record's payload is a (first, last) byte pair.
inline bool range_is_empty(const OpaqueRecord* rec) noexcept {
    const auto bytes = static_cast<std::uint32_t>(rec->range_last_6c - rec->range_first_68);
    return (bytes & 0xfffffffeu) == 0;
}

bool attach_00dd6df0(OpaqueRecordMap* self, const std::uint16_t* arg1,
                     std::uint32_t arg2) noexcept {
    if (arg1 == nullptr) {
        return false;
    }

    void* node = nullptr;
    tree_lower_bound_port(&self->tree_root_28, &node, &arg2);
    if (node == self->tree_header_2c) {
        return false;
    }

    // 0x00dd6e28: MOV ESI,dword ptr [EAX + 0x14] — a plain 4-byte load of the
    // node's mapped value.
    const std::uint8_t* const node_bytes = static_cast<const std::uint8_t*>(node);
    OpaqueRecord* rec = nullptr;
    __builtin_memcpy(&rec, node_bytes + 0x14, sizeof rec);
    if (rec == nullptr) {
        return false;
    }

    void* const handle_a = global_lookup_port(0x035ee914u);
    if (handle_a == nullptr) {
        return false;
    }

    // 0x00dd6e4c: EAX = [ [handle_a] + 0xf0 ], ECX = handle_a, one stack
    // argument 0x047d4388 and a byte flag 1.  Slot offset only; the table was
    // not located, so this stays a port.
    void* const sub_a = virtual_slot_f0_port(handle_a, 0x047d4388u, 1);
    if (sub_a == nullptr) {
        return false;
    }

    // 0x00dd6e61: EAX = [ [sub_a] + 0x0c ], ECX = sub_a, one stack argument
    // 0x00f15f4bd.
    void* const sub_b = virtual_slot_0c_port(sub_a, 0x00f15f4bdu);
    if (sub_b == nullptr) {
        return false;
    }

    if (range_is_empty(rec)) {
        return false;
    }

    wide_string_normalise_port(arg1);

    rec->flags_0c &= ~0x40u;
    rec->flags_0c |= 0x1u;

    record_process_port(self, rec);

    OpaqueRecord* const other = record_find_by_range_port(self, rec);
    if (other != nullptr) {
        record_erase_port(self, other->field_148);
    }

    return true;
}

}  // namespace openspore::wave13_w1_core_b15
