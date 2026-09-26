// 0x00ba61b0 — SimCore_00ba61b0_make_planet_record
//
// 44 instructions, 116 bytes, 5 direct callees, 1 virtual call. cdecl: the
// function ends in a bare RET (0x00BA6223) after `ADD ESP,0xC`, so the caller
// owns all stack cleanup and both arguments are read from the caller's frame.
//
//   00ba61b0  6A 00 x4            PUSH 0 ; PUSH 0 ; PUSH 0 ; PUSH 0
//   00ba61b8  68 E0 5E 46 01     PUSH 0x01465EF0      <- type descriptor
//   00ba61bd  68 B0 01 00 00     PUSH 0x1B0           <- 0x1B0 = 432 bytes
//   00ba61c2  E8 ...              CALL 0x00F473A0
//   00ba61c7  83 C4 18            ADD ESP,0x18
//   00ba61ca  85 C0               TEST EAX,EAX
//   00ba61cc  74 09               JZ 0x00ba61d7
//   00ba61ce  8B C8               MOV ECX,EAX
//   00ba61d0  E8 ...              CALL 0x00B8E180       <- 459-byte constructor
//   00ba61d5  EB 02               JMP 0x00ba61d9
//   00ba61d7  33 C0               XOR EAX,EAX           <- null on alloc failure
//
// The literal passed to the allocator is read live out of .rdata as
// "Simulator/cPlanetRecord". Together with the 0x1B0 allocation size and the
// header triple written afterwards, that is the only named type in this batch.
//
// The three header dwords written after construction are (+0x08, planet id),
// (+0x0C, 0x5220CB8) and (+0x10, 1). 0x5220CB8 is read as an immediate here and
// is NOT resolved to any property, type or class; no name is claimed for it.

#include "wave13_w1_core_b08.hpp"

namespace openspore {
namespace wave13_w1_core_b08 {

extern "C" void SimCore_00ba61b0_make_planet_record(std::uint32_t planet_id,
                                                    OpaqueCPlanetRecord** out_record);

extern "C" void SimCore_00ba61b0_make_planet_record(std::uint32_t planet_id,
                                                    OpaqueCPlanetRecord** out_record) {
    // PUSH 0 x4 ; PUSH 0x01465EF0 ; PUSH 0x1B0 ; CALL 0x00F473A0 ; ADD ESP,0x18
    void* raw = port_00f473a0_alloc(0x1B0u, "Simulator/cPlanetRecord", 0u, 0u, 0u, 0u);

    // TEST EAX,EAX ; JZ -> XOR EAX,EAX ; otherwise MOV ECX,EAX ; CALL 0x00B8E180
    OpaqueCPlanetRecord* record =
        raw != nullptr ? static_cast<OpaqueCPlanetRecord*>(raw) : nullptr;
    if (record != nullptr) {
        port_00b8e180_construct(record);
    }

    // 0x00BA61E6 MOV [ESI],EAX -- the out-pointer is written before the setter
    // runs, and re-read at 0x00BA61ED, 0x00BA6204 and 0x00BA620C.
    *out_record = record;

    // PUSH EDI ; MOV ECX,EAX ; CALL 0x00B8DA80 (RET 0x4) -- sets +0x184
    port_00b8da80_set_key(record, planet_id);

    // 0x00BA61EF ADD EAX,0x8 ; MOV [EAX],EDI ; MOV ECX,0x5220CB8 ;
    // 0x00BA61F9 MOV [EAX+0x4],ECX ; MOV EDX,1 ; MOV [EAX+0x8],EDX
    record->f_08 = planet_id;
    record->f_0C = 0x5220CB8u;
    record->f_10 = 1u;

    // 0x00BA6204 MOV ECX,[ESI] ; MOV EAX,[ECX] ; MOV EDX,[EAX] ; CALL EDX
    record->vtable->slot_00(record);

    // PUSH EAX ; PUSH 1 ; CALL 0x006AC040 ; PUSH ECX ; CALL 0x006AD010 ;
    // ADD ESP,0xC ; POP EDI ; POP ESI ; RET
    port_006ac040_register(record, 1u);
    port_006ad010_notify(record);
}

}  // namespace wave13_w1_core_b08
}  // namespace openspore
