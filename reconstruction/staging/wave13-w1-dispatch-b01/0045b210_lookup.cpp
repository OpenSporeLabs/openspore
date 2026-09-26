#include "0045b210_lookup.hpp"

#include <cstring>

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// 0x0045b210: SUB ESP,0x60 ; LEA EAX,[EBP+8] ; PUSH EAX ; LEA ECX,[EBP-8] ;
// PUSH ECX ; ECX = this+8 ; CALL 0x00421950 ; then the end-sentinel compare and
// the value load.
//
// 0x00421950 returns {node, slot}. On a miss the first word is
// buckets[bucket_count] (the sentinel one past the last bucket) and the second
// word is &buckets[bucket_count]. The reconstruction of the sentinel therefore
// reproduces the original's miss path exactly: reading one past the bucket array
// is the original's own end() idiom, not an added guard.
extern "C" __attribute__((thiscall)) std::uint32_t FUN_0045b210_LookupValueById(OpaqueIdRegistry* self,
                                                       std::uint32_t id) {
    std::uint32_t pair[2] = {0u, 0u};
    HashMapBody* map = &self->map_008;
    Port_00421950(map, pair, &id);

    // 0x0045b238 / 0x0045b23e / 0x0045b241: end = buckets + bucket_count * 4.
    HashMapNode* const* const end_slot = map->buckets + map->bucket_count;
    std::uint32_t sentinel = 0u;
    std::memcpy(&sentinel, end_slot, sizeof(sentinel));
    if (pair[0] == sentinel) {
        return 0u;  // 0x0045b26d: XOR EAX,EAX on the miss edge
    }
    // 0x0045b27a: MOV EDX,[ECX+4] on the hit edge, i.e. node->value.
    return reinterpret_cast<HashMapNode*>(pair[0])->value;
}

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
