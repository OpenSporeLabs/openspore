// 0x00baf700 — global hashed-name intern table, get-or-create.
//
// Original bytes (ghidra_read_memory 0x00baf700,152 =
// 51 8b 4c 24 08 53 e8 75 17 08 00 8b d8 8d 44 24 0c 50 8d 4c 24 08 51
// b9 1c c6 56 01 89 5c 24 14 e8 bd 02 a0 00 8b 44 24 04 3d 20 c6 56 01
// 74 08 8b 40 14 5b 59 c2 04 00 56 57 e8 f1 e6 ac ff 8d 54 24 14 52
// b9 1c c6 56 01 bf 8e 70 8e 22 00 8b f0 8b 0e 85 c9 74 0d c7 06 00 00
// 00 00 8b 01 8b 50 04 ff d2 8b 07 8b 50 2c 56 68 14 de 68 05 53
// 8b cf ff d2 8d 44 24 14 50 b9 1c c6 56 01 e8 3c 8e 22 00 8b 00 5f
// 5e 5b 59 c2 04 00):
//   0x00baf700  51                PUSH ECX                ; save incoming ECX
//   0x00baf701  8b 4c 24 08       MOV ECX, dword ptr [ESP + 0x8]   ; the stack arg
//   0x00baf705  53                PUSH EBX
//   0x00baf706  e8 75170800       CALL 0x00c30e80         ; EAX left in EBX
//   0x00baf70b  8b d8             MOV EBX, EAX
//   0x00baf70d  8d 44 24 0c       LEA EAX, [ESP + 0xC]
//   0x00baf711  50                PUSH EAX
//   0x00baf712  8d 4c 24 08       LEA ECX, [ESP + 0x8]
//   0x00baf716  51                PUSH ECX
//   0x00baf717  b9 1c c6 56 01    MOV ECX, 0x0156C61C     ; the global table
//   0x00baf71c  89 5c 24 14       MOV dword ptr [ESP + 0x14], EBX   ; key := EBX
//   0x00baf720  e8 bd02a000       CALL 0x00e5c780         ; lower_bound
//   0x00baf725  8b 44 24 04       MOV EAX, dword ptr [ESP + 0x4]    ; node
//   0x00baf729  3d 20 c6 56 01    CMP EAX, 0x0156C620     ; the end sentinel
//   0x00baf72e  74 08             JZ 0x00baf738           ; miss
//   0x00baf730  8b 40 14          MOV EAX, dword ptr [EAX + 0x14]    ; HIT: value
//   0x00baf733  5b                POP EBX
//   0x00baf734  59                POP ECX
//   0x00baf735  c2 04 00          RET 0x4
//   0x00baf738  56 57             PUSH ESI ; PUSH EDI     ; miss path
//   0x00baf73a  e8 f1e6acff       CALL 0x0067de30         ; factory host
//   0x00baf73f  8d 54 24 14       LEA EDX, [ESP + 0x14]
//   0x00baf743  52                PUSH EDX
//   0x00baf744  b9 1c c6 56 01    MOV ECX, 0x0156C61C
//   0x00baf749  bf 8e708e2200     MOV EDI, EAX
//   0x00baf74b  e8 708e2200       CALL 0x00dd85c0         ; operator[]
//   0x00baf750  8b f0             MOV ESI, EAX           ; ESI = &node->value
//   0x00baf752  8b 0e             MOV ECX, dword ptr [ESI]
//   0x00baf754  85 c9             TEST ECX, ECX
//   0x00baf756  74 0d             JZ 0x00baf765
//   0x00baf758  c7 06 00000000    MOV dword ptr [ESI], 0
//   0x00baf75e  8b 01             MOV EAX, dword ptr [ECX]
//   0x00baf760  8b 50 04          MOV EDX, dword ptr [EAX + 0x4]
//   0x00baf763  ff d2             CALL EDX                ; vtable slot +0x04
//   0x00baf765  8b 07             MOV EAX, dword ptr [EDI]
//   0x00baf767  8b 50 2c          MOV EDX, dword ptr [EAX + 0x2C]
//   0x00baf76a  56                PUSH ESI               ; arg3: &value slot
//   0x00baf76b  68 14de6805       PUSH 0x568DE14          ; arg2: factory key
//   0x00baf770  53                PUSH EBX               ; arg1: the hashed name
//   0x00baf771  8b cf             MOV ECX, EDI
//   0x00baf773  ff d2             CALL EDX                ; vtable slot +0x2C
//   0x00baf775  8d 44 24 14       LEA EAX, [ESP + 0x14]
//   0x00baf779  50                PUSH EAX
//   0x00baf77a  b9 1c c6 56 01    MOV ECX, 0x0156C61C
//   0x00baf77f  e8 3c8e2200       CALL 0x00dd85c0         ; re-fetch the slot
//   0x00baf784  8b 00             MOV EAX, dword ptr [EAX]
//   0x00baf786  5f 5e 5b 59       POP EDI ; POP ESI ; POP EBX ; POP ECX
//   0x00baf78a  c2 04 00          RET 0x4
//
// ABI: exactly one callee-cleaned stack dword (`RET 0x4`).  Caller 0x00c784c0
// pushes EDI at 0x00c78560 / 0x00c785c3 and does NOT adjust ESP afterwards —
// the following ADD ESP,0xC at 0x00c78583 belongs to the three pushes for
// 0x0040cf10 — so the callee owns the cleanup and the encoding is __stdcall.
// The incoming ECX is preserved by the PUSH ECX / POP ECX pair and is never
// read, so the function is a static member taking one argument.
//
// The key is produced by 0x00c30e80, which reads [receiver+0x58] and a flag,
// then returns port_00c30cc0's 32-bit constant for that (group, sub) pair
// (0x00c30cc0 is a two-level switch returning 0xACB9635D, 0x4FEDE4A6, ... with
// a 0x4E5855B9 default).  These are hashed type/config names.
//
// 0x568DE14, the constant handed to vtable slot +0x2C, is named in
// Spore-ModAPI "Spore ModAPI/Spore/Simulator/SimulatorEnums.h:411":
// "RelationshipEvents corresponds to configurations in 0x0568DE14
// (space_npc_relationship_effects~)".  The +0x2C callee itself is a runtime
// vtable entry and was NOT resolved, so the class that owns it is unresolved.

#include "sim_core_b06_opaque.hpp"

namespace sim_core_b06 {

// Returns the interned object registered for the hashed name that `selector`
// denotes, creating it on first use.  Never returns null on the create path
// unless the factory's +0x2C slot declines to store anything.
std::uint32_t SimCore_00baf700_getOrCreateInterned(std::uint32_t selector) {
    // 0x00baf706: ECX is the incoming stack argument here; 0x00baf70b keeps the
    // returned hashed name in EBX and reuses it for both the lookup and the
    // factory call.
    const std::uint32_t hashedName =
        port_00c30e80_selectHashedName(reinterpret_cast<OpaqueReceiver_B3D290*>(selector));
    const std::uint32_t key = hashedName;

    // 0x00baf70d..0x00baf720: port_00e5c780_lookup(&g_internedObjectTable, &key, &node)
    OrderedKeyMapNode* node = nullptr;
    port_00e5c780_lookup(&g_internedObjectTable, &key, &node);

    // 0x00baf729 CMP EAX,0x0156C620 / 0x00baf72e JZ 0x00baf738: the table's own
    // end sentinel is the miss condition, not a null node pointer.
    if (node != g_internedObjectTable.endNode) {
        // 0x00baf730: hit, return the mapped value at node+0x14 verbatim.
        return node->value;
    }

    // ---- miss path, 0x00baf738 ----
    // 0x00baf73a: the factory host singleton.
    auto* host = reinterpret_cast<OpaqueFactoryHost*>(getGlobal_015FD8A8());

    // 0x00baf74b: find-or-insert; the returned pointer is &node->value.
    std::uint32_t* slot = port_00dd85c0_at(&g_internedObjectTable, &key);

    // 0x00baf752..0x00baf763: if a previous occupant exists, clear the slot
    // BEFORE releasing it, then run its vtable slot +0x04 destructor.  The
    // order matters and is preserved: store 0 at 0x00baf758, call at 0x00baf763.
    if (*slot != 0u) {
        std::uint32_t stale = *slot;
        *slot = 0u;
        void (*release)(void*) = reinterpret_cast<void (*)(void*)>(host->vtable->release);
        release(reinterpret_cast<void*>(stale));
    }

    // 0x00baf767..0x00baf773: vtable slot +0x2C with
    // (hashedName, 0x0568DE14 = space_npc_relationship_effects~, slot).
    using CreateOrStore = void (*)(OpaqueFactoryHost*, std::uint32_t, std::uint32_t, std::uint32_t*);
    CreateOrStore createOrStore =
        reinterpret_cast<CreateOrStore>(host->vtable->createOrStore);
    createOrStore(host, key, 0x0568DE14u, slot);

    // 0x00baf775..0x00baf784: re-fetch the slot after the factory call rather
    // than reusing the earlier pointer, because the call may have reallocated
    // or rebalanced the tree.  The return value is the *re-read* slot content.
    slot = port_00dd85c0_at(&g_internedObjectTable, &key);
    return *slot;
}

}  // namespace sim_core_b06
