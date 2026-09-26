// reconstruction/staging/wave13-w1-core-b11/00c30e80_selector_id_from_manager.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00c30e80 (image base
// 0x00400000). Body 0x00c30e80..0x00c30ead, 17 instructions, 46 bytes.
//
// Observed contract: compute a 32-bit selector id and hand it to the two-
// argument switch at 0x00c30cc0 together with the receiver's dword at +0x58.
// The switch's result is this function's result.
//
//   flag = 1                                  when the pointer at
//            [0x0167eae0]->+0x74 is null,
//          = [ [0x0167eae0]->+0x74 ]->+0x1248 otherwise.
//
// Evidence, instruction by instruction:
//   0x00c30e80: 56                       PUSH ESI
//   0x00c30e81: 8b f1                    MOV ESI,ECX
//   0x00c30e83: e8 78 c4 f0 ff          CALL 0x00b3d300   -> EAX = [0x0167eae0]
//   0x00c30e88: 8b c8                    MOV ECX,EAX
//   0x00c30e8a: e8 01 6f 33 00          CALL 0x00f67d90   -> EAX = [EAX + 0x74]
//   0x00c30e8f: 8b c8                    MOV ECX,EAX
//   0x00c30e91: b8 01 00 00 00          MOV EAX,0x1      <- default flag = 1
//   0x00c30e96: 85 c9                    TEST ECX,ECX
//   0x00c30e98: 74 05                    JZ 0x00c30e9f     <- keep the default
//   0x00c30e9a: e8 81 45 04 00          CALL 0x00c75420   -> EAX = [ECX + 0x1248]
//   0x00c30e9f: 50                       PUSH EAX          <- arg2 = flag
//   0x00c30ea0: 8b 46 58                 MOV EAX,dword ptr [ESI + 0x58]
//   0x00c30ea3: 50                       PUSH EAX          <- arg1 = receiver enum
//   0x00c30ea4: e8 17 fe ff ff          CALL 0x00c30cc0
//   0x00c30ea9: 83 c4 08                 ADD ESP,0x8       <- caller cleans 8 bytes
//   0x00c30eac: 5e                       POP ESI
//   0x00c30ead: c3                       RET
//
// 0x00b3d300 is exactly "MOV EAX,dword ptr [0x0167eae0] ; RET", 0x00f67d90 is
// exactly "MOV EAX,dword ptr [ECX + 0x74] ; RET" and 0x00c75420 is exactly
// "MOV EAX,dword ptr [ECX + 0x1248] ; RET". All three were read this way live.
//
// 0x00c30cc0 was also read, in full (110 instructions). It is a bare-RET function
// reading [ESP+4] and [ESP+8], so it is cdecl with two stack arguments:
//   - arg1 is bounds-checked against 0x12 (CMP ECX,0x12 / JA default); out of
//     range falls through to MOV EAX,0x4e5855b9 / RET.
//   - a 19-byte index table at 0x00c30e6c (00 01 02 03 04 05 06 07 08 00 01 02
//     03 04 05 06 07 06) selects one of nine 4-byte jump targets from the table
//     at 0x00c30e48, each of which then branches on arg2 == 0, 1, 2 and returns
//     a distinct constant. Any arg2 outside 0..2 also yields 0x4e5855b9.
// The 27 constants are reproduced in the table below so the shape of the
// callee is recorded, not just its call.
//
// Analogue: 0x00c30eb0, 0x2f bytes after this body's end, is the one-argument
// form - it switches on the same receiver field [ECX + 0x58] through its own
// 19-entry table at 0x00c30f38 and returns addresses in 0x014025xx and
// 0x0146b7xx instead of small integers.
//
// Not claimed: what the +0x58 enumeration denotes, what the returned 32-bit
// values denote, and what the +0x74 / +0x1248 chain under 0x0167eae0 is. The
// globals hold zero in the file image, so nothing about their runtime contents
// is observed.

#include "b11_opaque_types.hpp"

namespace openspore {
namespace b11 {
namespace t00c30e80 {

// Observed receiver offset passed as the switch's first argument.
inline constexpr std::size_t kSelectorOffset = 0x58;
// Upper bound accepted by 0x00c30cc0, exclusive.
inline constexpr Dword kSelectorCount = 0x12;
// The constant 0x00c30cc0 returns for any out-of-range first or second
// argument.
inline constexpr Dword kDefaultId = 0x4e5855b9u;

// The nine index-table blocks of 0x00c30cc0, each holding the three constants
// for arg2 == 0, 1, 2. Read live from the disassembly; not interpreted.
struct SelectorIds {
    Dword byVariant[3];
};
inline constexpr SelectorIds kSelectorIds[9] = {
    {{0xacb9635du, 0x4fede4a6u, 0xed2bbcc8u}},  // block 0, reached by arg1 0
    {{0x04a83b77u, 0x250f78b4u, 0x12486202u}},  // block 1, reached by arg1 1
    {{0x5d054a25u, 0x076b1a6eu, 0x8aa5a470u}},  // block 2, reached by arg1 2
    {{0xdf83b46du, 0xb308c5d6u, 0x21d2a5b8u}},  // block 3, reached by arg1 3
    {{0x59878688u, 0xacd3a4cfu, 0xf9b2cbadu}},  // block 4, reached by arg1 4
    {{0xb8196164u, 0x62166b9bu, 0x01100719u}},  // block 5, reached by arg1 5
    {{0xe80abf05u, 0x901a654eu, 0x18271550u}},  // block 6, reached by arg1 6 and 17
    {{0x401c6160u, 0x86a04027u, 0x3001d0a5u}},  // block 7, reached by arg1 7..16
    {{0x25885eafu, 0x7e56d6ccu, 0x87d7829au}},  // block 8, reached by arg1 8
};
// The 19-byte index table at 0x00c30e6c that maps arg1 to a block.
inline constexpr Bool kSelectorToBlock[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 0,
                                              1, 2, 3, 4, 5, 6, 7, 6};

// Standalone equivalent of 0x00c30cc0, transcribed from its disassembly.
Dword selector_id_lookup(Dword selector, Dword variant) {
    if (selector >= kSelectorCount) {
        return kDefaultId;  // 0x00c30cc9 CMP ECX,0x12 / 0x00c30ccc JA
    }
    if (variant > 2) {
        return kDefaultId;  // every block's third SUB/JNZ falls to 0x00c30e44
    }
    return kSelectorIds[kSelectorToBlock[selector]].byVariant[variant];
}

// Observed receiver: the singleton handle lives at global 0x0167eae0.
Dword selector_id_from_manager(EnumField58Owner* self, GlobalGetterEae0Fn manager,
                               Word74GetterFn managerSlot, Word1248GetterFn slotValue,
                               SelectorIdLookupFn lookup) {
    // 0x00c30e83 / 0x00c30e88
    const Dword managerHandle = manager();
    // 0x00c30e8a
    const Dword slot = managerSlot(reinterpret_cast<Ptr>(managerHandle));

    // 0x00c30e91: the default is materialised before the null test.
    Dword variant = 1;
    // 0x00c30e96 / 0x00c30e98
    if (slot != 0) {
        // 0x00c30e9a
        variant = slotValue(reinterpret_cast<Ptr>(slot));
    }

    // 0x00c30e9f PUSH EAX / 0x00c30ea3 PUSH EAX - right to left, so [ESP+4] is
    // the receiver's selector and [ESP+8] is the variant.
    // 0x00c30ea4 CALL 0x00c30cc0 / 0x00c30ea9 ADD ESP,0x8
    return lookup(self->field58, variant);
    // 0x00c30eac POP ESI / 0x00c30ead RET - the switch already returned in EAX.
}

}  // namespace t00c30e80
}  // namespace b11
}  // namespace openspore
