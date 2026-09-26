// wave13-w1-core-b15 — shared opaque receiver/port declarations.
//
// Every type here is deliberately opaque. SporeApp.exe carries no MSVC RTTI, so
// class identity can only come from a located vtable or an SDK header whose
// signature AND body both agree. For the six targets in this batch no such
// vtable was located, so no owning class is asserted anywhere below.
//
// The port functions are DECLARED ONLY. They stand for observed call targets
// whose concrete semantics could not be established from the binary. No bodies
// are fabricated here; b15_model_test.cpp supplies recording stubs purely so
// that the reconstructed control flow can be executed and observed.

#ifndef OPENSPORE_WAVE13_W1_CORE_B15_B15_OPAQUE_TYPES_HPP
#define OPENSPORE_WAVE13_W1_CORE_B15_B15_OPAQUE_TYPES_HPP

#include <cstddef>
#include <cstdint>

namespace openspore::wave13_w1_core_b15 {

// ---------------------------------------------------------------------------
// Process heap manager
// ---------------------------------------------------------------------------
// [0x016c8b44] holds a pointer to the process heap manager; the file image
// stores 0 there, so the pointer is installed at runtime.
//
// 0x00f47380 is a seven-instruction thunk:
//   MOV EAX,[ESP+4] ; TEST EAX,EAX ; JZ out ;
//   MOV ECX,[0x016c8b44] ; PUSH EAX ; CALL 0x009276c0 ; out: RET
// 0x009276c0 takes the manager in ECX, takes a CRITICAL_SECTION from
// [manager+0x4e4], brackets 0x00926fd0 with Enter/LeaveCriticalSection, and
// 0x00926fd0 is a free-list allocator: it reads the block header at
// [payload-8] (free-list link) and [payload-4] (size | flags, low 3 bits are
// flags, bit 31 set on the free path), coalesces with neighbours held in the
// manager's list at +0x3c, tracks the low/high watermark at +0x488/+0x48c, and
// calls VirtualFree with MEM_RELEASE for whole-page blocks.
//
// OBSERVED ROLE: release one heap block. The concrete manager type is NOT
// established, so it stays an opaque port.
struct OpaqueHeapManager;

// == 0x00f47380. Releases exactly one block; the null test lives inside.
void heap_release_port(void* payload) noexcept;

// ---------------------------------------------------------------------------
// 0x00ff2e30 — node teardown
// ---------------------------------------------------------------------------
// The receiver is dereferenced at +0x00, +0x28 and +0x3c. 0x00ff2d80 shows
// +0x28/+0x2c and +0x3c/+0x40 are (begin, end) pointer pairs walked as
// 4-byte-element ranges, and callers of 0x00ff2e30 push the same pointer that
// they then hand to heap_release_port. Layout beyond those five words is
// unknown and is NOT invented.
struct OpaqueNode {
    void* field_00;                // 0x00ff2e64  MOV ESI,dword ptr [ESI]
    std::uint32_t pad_04_to_27[9];
    void* field_28;                // 0x00ff2e4e  second guarded release
    void* field_2c;
    std::uint32_t pad_30_to_3b[3];
    void* field_3c;                // 0x00ff2e38  first guarded release
    void* field_40;
};
static_assert(offsetof(OpaqueNode, field_28) == 0x28, "OpaqueNode::field_28");
static_assert(offsetof(OpaqueNode, field_2c) == 0x2c, "OpaqueNode::field_2c");
static_assert(offsetof(OpaqueNode, field_3c) == 0x3c, "OpaqueNode::field_3c");
static_assert(offsetof(OpaqueNode, field_40) == 0x40, "OpaqueNode::field_40");

// == 0x00ff2d80. Called with ECX = the same receiver at 0x00ff2e33, and also
// called directly by 0x00c8c2a0 at 0x00c8c339 with no subsequent free, so its
// role is "release the contents of the two ranges" rather than "destroy".
void node_release_contents_port(OpaqueNode* self) noexcept;

// ---------------------------------------------------------------------------
// 0x00ff0870 / 0x00ff0760 / 0x00ff07e0 / 0x00ff07a0 — counter and bitmask
// ---------------------------------------------------------------------------
// Four sibling routines in the 0x00ff0700..0x00ff0870 block agree on this
// layout: a 32-bit counter at +0x24, an 8-bit mask at +0x28, and a
// 7-byte-stride array at [+0x7c, +0x80). Nothing else about the object is
// established.
struct OpaqueCounter {
    std::uint32_t pad_00_to_23[9];
    std::int32_t counter_24;          // 0x00ff0893 load / 0x00ff0863 DEC
    std::uint8_t mask_28;             // 0x00ff0870 MOVZX / 0x00ff07e1,0x00ff080c
    std::uint8_t pad_29_to_7b[0x53];
    std::uint8_t* records_7c;         // 0x00ff07cf ; stride 7 (0x00ff07c6 LEA/SUB)
    std::uint8_t* records_end_80;     // 0x00ff07a1
};
static_assert(offsetof(OpaqueCounter, counter_24) == 0x24, "OpaqueCounter::counter_24");
static_assert(offsetof(OpaqueCounter, mask_28) == 0x28, "OpaqueCounter::mask_28");
static_assert(offsetof(OpaqueCounter, records_7c) == 0x7c, "OpaqueCounter::records_7c");
static_assert(offsetof(OpaqueCounter, records_end_80) == 0x80, "OpaqueCounter::records_end_80");

// ---------------------------------------------------------------------------
// 0x00dd6df0 — key/record manager
// ---------------------------------------------------------------------------
// The embedded container at +0x28 is walked by 0x00e5c780 as a red-black tree:
// [+0x28] root, [+0x2c] header/sentinel, [+0x30] first node, node[+0x10] key,
// node[+0x14] mapped value, node[+0x04]/[+0x08] in-order links. The record's
// [+0x68, +0x6c) pair is a (first, last) byte range compared by 0x0087d9a0, and
// [+0xc] is a flag dword. Record layout past those words is unknown.
struct OpaqueRecord {
    std::uint32_t pad_00_to_0b[3];
    std::uint32_t flags_0c;             // 0x00dd6e86 AND 0xffffffbf ; 0x00dd6e8a OR 1
    std::uint32_t pad_10_to_67[0x16];
    const std::uint8_t* range_first_68;  // 0x00dd6e75 LEA ECX,[ESI+0x68]
    const std::uint8_t* range_last_6c;   // 0x00dd6e6f ; empty is gate 7
    std::uint32_t pad_70_to_13f[0x34];
    std::uint32_t pad_140_to_143;
    std::uint32_t pad_144_to_147;
    std::uint32_t field_148;             // 0x00dd6ea2 key handed to 0x00dd6bc0
    std::uint32_t pad_14c_to_14f;
    std::uint32_t field_150;
};
static_assert(offsetof(OpaqueRecord, flags_0c) == 0x0c, "OpaqueRecord::flags_0c");
static_assert(offsetof(OpaqueRecord, range_first_68) == 0x68, "OpaqueRecord::range_first_68");
static_assert(offsetof(OpaqueRecord, range_last_6c) == 0x6c, "OpaqueRecord::range_last_6c");
static_assert(offsetof(OpaqueRecord, field_148) == 0x148, "OpaqueRecord::field_148");

struct OpaqueRecordMap {
    std::uint32_t pad_00_to_27[10];
    void* tree_root_28;         // 0x00dd6e0f LEA ECX,[EDI+0x28]
    void* tree_header_2c;       // 0x00dd6e1d ; "not found" sentinel
    void* tree_first_30;        // 0x00dd5dd0 list head
    std::int32_t pad_34_to_63[12];
    std::int32_t live_count_64;  // 0x00dd6bc0 decrements param_1 + 0x64
    std::uint32_t pad_68_to_6b;
    void* field_6c;             // 0x00dd6bc0 tests this against 0
};
static_assert(offsetof(OpaqueRecordMap, tree_root_28) == 0x28, "OpaqueRecordMap::tree_root_28");
static_assert(offsetof(OpaqueRecordMap, tree_header_2c) == 0x2c, "OpaqueRecordMap::tree_header_2c");
static_assert(offsetof(OpaqueRecordMap, tree_first_30) == 0x30, "OpaqueRecordMap::tree_first_30");
static_assert(offsetof(OpaqueRecordMap, live_count_64) == 0x64, "OpaqueRecordMap::live_count_64");

// 0x00e5c780: __thiscall tree_lower_bound(out_node*, key*). Leaves the out
// pointer in EAX; on a miss it stores the header node (tree + 4).
void* tree_lower_bound_port(void* tree, void** out_node, const std::uint32_t* key) noexcept;

// 0x008105b0: one-argument global lookup helper. Its decompiled body dereferences
// its argument at +0x14 and 0x00810200 walks a container at [+0x64, +0x68), so
// the argument is a pointer to a statically allocated descriptor. The
// descriptors actually passed (0x035ee914, 0x047d4388, 0x00f15f4bd, ...) are
// NOT present in the mapped image, so whether they are hashes, obfuscated
// addresses or something else is UNRESOLVED. Treated as opaque handles.
void* global_lookup_port(std::uint32_t descriptor) noexcept;

// The two virtual calls 0x00dd6df0 makes on the handles it obtains. The slot
// offsets (+0xf0 and +0x0c) and the pushed arguments are observed; the vtables
// themselves were not located, so neither the concrete callee nor the owning
// class is named.
void* virtual_slot_f0_port(void* handle, std::uint32_t arg, std::uint32_t flag) noexcept;
void* virtual_slot_0c_port(void* handle, std::uint32_t arg) noexcept;

// 0x005c3d90: callee-cleaning one-argument routine that walks a 16-bit string
// to its terminator and forwards (begin, begin + halfbyte_length) to 0x00423650.
void wide_string_normalise_port(const std::uint16_t* text) noexcept;

// 0x00dd60c0 / 0x00dd5dd0 / 0x00dd6bc0.
void record_process_port(OpaqueRecordMap* self, OpaqueRecord* rec) noexcept;
OpaqueRecord* record_find_by_range_port(OpaqueRecordMap* self, OpaqueRecord* rec) noexcept;
void record_erase_port(OpaqueRecordMap* self, std::uint32_t key) noexcept;

// ---------------------------------------------------------------------------
// 0x00d1e610 — mode dispatch
// ---------------------------------------------------------------------------
// 0x00b3d300..0x00b3d4d5 is a table of 22 identical five-instruction accessors,
// each "MOV EAX,[0x0167XXXX] ; RET". The SDK import named some of them
// (cSimulatorSystem::Get @ 0x00b3d330 -> [0x0167eaf0],
// cGameModeManager::Get @ 0x00b3d420 -> [0x0167eb2c],
// cGameInputManager::Get @ 0x00b3d350 -> [0x0167eaf8], ...). The two this
// target needs, 0x00b3d300 -> [0x0167eae0] and 0x00b3d320 -> [0x0167eaec],
// were NOT named by the import, so their owning classes are unknown.
struct OpaqueSimSubsystem {
    std::uint32_t pad_00_to_1f[8];
    std::uint32_t selector_20;  // 0x00a42730 ; compared against three constants
    std::uint32_t pad_24_to_53[12];
    std::uint32_t object_54;    // 0x00b1fdb0 ; returned for two of the selectors
    std::uint32_t pad_58_to_6f[6];
    std::uint32_t handle_70;    // 0x00bfc5f0 ; null-checked before the second hop
};
static_assert(offsetof(OpaqueSimSubsystem, selector_20) == 0x20, "OpaqueSimSubsystem::selector_20");
static_assert(offsetof(OpaqueSimSubsystem, object_54) == 0x54, "OpaqueSimSubsystem::object_54");
static_assert(offsetof(OpaqueSimSubsystem, handle_70) == 0x70, "OpaqueSimSubsystem::handle_70");

struct OpaqueSimHolder {
    std::uint32_t pad_00_to_11b[0x47];
    std::uint32_t value_11c;    // 0x00c00650
};
static_assert(offsetof(OpaqueSimHolder, value_11c) == 0x11c, "OpaqueSimHolder::value_11c");

// 0x00b3d300 -> [0x0167eae0], 0x00b3d320 -> [0x0167eaec], 0x00b5b800 selector.
OpaqueSimSubsystem* subsystem_a_port() noexcept;
OpaqueSimSubsystem* subsystem_b_port() noexcept;
std::uint32_t selector_port() noexcept;

// ---------------------------------------------------------------------------
// 0x00c0b370 / 0x00c0c2f0 — members of one large Simulator object
// ---------------------------------------------------------------------------
// A whole-image scan for the displacements 0xe3c and 0xeac finds exactly five
// and sixteen referencing instructions respectively, all on the same object in
// 0x00c0xxxx / 0x00c1xxxx. That object also holds polymorphic sub-objects at
// +0x58, +0xb50, +0xb58, +0xb6c, +0xc0 and +0xe7c (virtual calls through
// [subobj] at slots +0x04, +0x1c, +0x20, +0x2c, +0x48 and +0x58) and pointer
// ranges at [+0x15c,+0x160) and [+0x170,+0x174). None of it is named, so only
// the two scalar fields this batch needs are modelled.
struct OpaqueSimState {
    std::uint32_t pad_00_to_e3b[0x38f];
    std::int32_t field_e3c;   // 0x00c0b374 store ; 0x00c0c68c sole reader
    std::uint32_t pad_e40_to_eab[0x2b];
    std::int32_t field_eac;   // 0x00c0c2f0 load ; 0x00c0c304 store
    std::uint32_t pad_eb0_to_1623[0x1dd];
    std::uint32_t field_1624;
};
static_assert(offsetof(OpaqueSimState, field_e3c) == 0xe3c, "OpaqueSimState::field_e3c");
static_assert(offsetof(OpaqueSimState, field_eac) == 0xeac, "OpaqueSimState::field_eac");
static_assert(offsetof(OpaqueSimState, field_1624) == 0x1624, "OpaqueSimState::field_1624");

}  // namespace openspore::wave13_w1_core_b15

#endif  // OPENSPORE_WAVE13_W1_CORE_B15_B15_OPAQUE_TYPES_HPP
