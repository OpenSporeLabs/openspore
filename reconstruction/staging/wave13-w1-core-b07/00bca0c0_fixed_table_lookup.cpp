// reconstruction/staging/wave13-w1-core-b07/00bca0c0_fixed_table_lookup.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00bca0c0 (image base
// 0x00400000). Body 0x00bca0c0..0x00bca111, 37 instructions, 84 bytes.
//
// Contract reconstructed from the binary: a linear search over eight fixed
// 0x44-byte records starting at this+0x20. Two 32-bit key fields must match
// exactly. Two further key fields are compared only when the corresponding
// argument is non-zero, so a zero argument is a wildcard. On a hit the record's
// 16-bit identifier is returned in bits 0..15 and the slot index in bits
// 16..31; when all eight slots are exhausted the function returns 0xffffffff,
// which is the one value no record can produce because the index never
// reaches 16 bits.
//
// Not claimed: the meaning of the four key fields and of the 16-bit
// identifier, and the owning class (caller 0x00ba48b0 passes the sub-object
// found at its own +0xb48).

#include "b07_opaque_types.hpp"

namespace openspore {
namespace b07 {
namespace t00bca0c0 {

inline constexpr int kSlotCount = 8;
inline constexpr Word kNoMatch = 0xffffffffu;

// Packs (record id, slot index) exactly as the original does:
//   0x00bca105 MOVZX EAX,word ptr [EAX + -0x8]   -> 16-bit id
//   0x00bca10a SHL EDX,0x10                      -> slot index into bits 16+
//   0x00bca10e OR EAX,EDX
Word find_record(RecordTable* table, Word key1, Word key2, Word key3, Word key4) {
    for (std::uint32_t slot = 0; slot < kSlotCount; ++slot) {
        const TableRecord& record = table->slots[slot];

        // 0x00bca0d8 CMP dword ptr [EAX + -0x4],EBX / 0x00bca0db JZ next
        if (record.key1 != key1) {
            continue;
        }
        // 0x00bca0dd CMP dword ptr [EAX],EDI / 0x00bca0df JZ next
        if (record.key2 != key2) {
            continue;
        }
        // 0x00bca0e1 TEST ESI,ESI / 0x00bca0e3 JZ match
        if (key3 != 0 && record.key3 != key3) {
            continue;  // 0x00bca0e5 CMP dword ptr [EAX + 0x14],ESI
        }
        // 0x00bca0ea TEST ECX,ECX / 0x00bca0ec JZ match
        if (key4 != 0 && record.key4 != key4) {
            continue;  // 0x00bca0ee CMP dword ptr [EAX + 0x18],ECX
        }
        return static_cast<Word>(record.id) | (slot << 16);
    }

    // 0x00bca0fe OR EAX,0xffffffff
    return kNoMatch;
}

}  // namespace t00bca0c0
}  // namespace b07
}  // namespace openspore
