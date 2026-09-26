// reconstruction/staging/wave13-w1-core-b07/00643a40_eastl_map_find_or_insert.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00643a40 (3.1.0.22, image base
// 0x00400000). Body 0x00643a40..0x00643aba, 51 instructions, 125 bytes.
//
// Contract reconstructed from the binary: an EASTL ordered map keyed on a
// 4-byte word. Given a pointer to the key it walks the red-black tree for the
// exact match; on a hit it returns the address of that node's 4-byte mapped
// slot, otherwise it builds {key, 0} in its own frame, asks 0x006432d0 to
// insert it with the walk's best candidate as the hint, and returns the
// address of the newly created mapped slot. The insert publishes the new node
// through the caller's own argument word, which is why the body zeroes that
// word before the call and reloads it afterwards.
//
// Not claimed: the identity of the owning object (this receiver is a bare
// container; callers place it at receiver+0x10, +0x2c, +0x5c, +0x1b0) and the
// domain meaning of the 4-byte mapped values.

#include "b07_opaque_types.hpp"

namespace openspore {
namespace b07 {
namespace t00643a40 {

// 0x006432d0, the single callee. Reached only on a miss.
// It takes (container, address of the caller's key argument word, the walk's
// candidate node, address of the {key,0} pair, 0) and writes the created node
// pointer back through the third-from-top argument, which is exactly what
// 0x00579b50 does with `*param_2 = iVar1` when 0x00643a40 passes the address
// of its argument word down as param_2.
using InsertWithHintFn = b07::InsertWithHintFn;

// The two halves of the value that 0x00643a40 materialises in its own frame:
//   0x00643a77 MOV dword ptr [ESP + 0xc],EAX   -> pair.key    = *keyPtr
//   0x00643a94 MOV dword ptr [ESP + 0x20],0x0  -> pair.mapped = 0
struct ValuePair {
    Word key;
    Word mapped;
};

// Returns the address of the 4-byte mapped slot for *keyPtr, inserting
// {*keyPtr, 0} when the key is absent. Zero is never returned by the original
// on the miss path unless the insert port fails to publish a node.
Word find_or_insert_mapped(OrderedMap* map, const Word* keyPtr, InsertWithHintFn insert) {
    // 0x00643a40 MOV EAX,dword ptr [ECX + 0xc] : root == anchor.mpNodeParent
    Word node = map->anchorParent;
    // 0x00643a48 LEA ESI,[ECX + 0x4] : end() sentinel
    const Word end = word_of(map) + 4;
    Word candidate = end;

    if (node != 0) {
        const Word key = *keyPtr;
        // 0x00643a52 TEST EAX,EAX / 0x00643a54 JZ 0x00643a6a
        do {
            if (node != 0) {
                const MapNode* entry = pointer_at<MapNode>(node);
                // 0x00643a58 CMP dword ptr [EAX + 0x10],EBP
                if (entry->key < key) {
                    // 0x00643a5b JC -> 0x00643a64 MOV EAX,dword ptr [EAX]
                    node = entry->mpNodeRight;
                } else {
                    candidate = node;
                    // 0x00643a5d MOV EDX,EAX
                    node = entry->mpNodeLeft;  // 0x00643a5f MOV EAX,[EAX+0x4]
                }
            }
            // 0x00643a66 TEST EAX,EAX / 0x00643a68 JNZ 0x00643a58
        } while (node != 0);
    }

    // 0x00643a6a CMP EDX,ESI / 0x00643a6c JZ 0x00643a75
    if (candidate != end) {
        const MapNode* entry = pointer_at<MapNode>(candidate);
        // 0x00643a70 CMP EAX,dword ptr [EDX + 0x10] with EAX = *keyPtr, and
        // 0x00643a73 JNC to the hit path, so the hit test is
        // target >= candidate.key. The walk only ever keeps a candidate whose
        // key is >= the target, so the two together mean exact equality.
        if (*keyPtr >= entry->key) {
            // 0x00643ab3 LEA EAX,[EDX + 0x14]
            return candidate + 0x14;
        }
    }

    // Miss. 0x00643a7b/0x00643a80 zero and then reload the argument word; the
    // insert port publishes the created node through that same word.
    ValuePair pair;
    pair.key = *keyPtr;   // 0x00643a75 MOV EAX,dword ptr [EDI]
    pair.mapped = 0;      // 0x00643a94 MOV dword ptr [ESP + 0x20],0x0
    Word keySlot = 0;     // 0x00643a7b MOV byte ptr [ESP + 0x18],0x0

    // 0x00643a8a..0x00643a9c: push 0, &pair, this, the argument-word address
    // (0x00643a8d MOV dword ptr [EAX],EDX fills the reserved slot with the
    // candidate), then CALL 0x006432d0 with ECX = the container.
    insert(word_of(map), &keySlot, candidate, reinterpret_cast<const Word*>(&pair), 0);

    // 0x00643aa1 MOV EAX,dword ptr [ESP + 0x18]
    // 0x00643aa5 ADD EAX,0x14
    return keySlot + 0x14;
}

}  // namespace t00643a40
}  // namespace b07
}  // namespace openspore
