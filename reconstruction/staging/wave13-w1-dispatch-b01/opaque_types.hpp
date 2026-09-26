// Opaque receiver/subobject declarations for package wave13-w1-dispatch-b01.
//
// Nothing here is an SDK class. SporeApp.exe carries no MSVC RTTI, so every type
// below is named for the role the disassembly proves it plays and nothing more.
// Only the offsets that a live instruction in this batch actually reads or
// writes are declared; every other byte of the object stays opaque padding.

#pragma once

#include <cstddef>
#include <cstdint>

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// Receiver of 0x004c49e0 / 0x004c4630. Provenance of that receiver is not
// uniform across the call sites: cEditor+0x150 (0x00574a28, 0x0057c5bb,
// 0x0058c570), cEditor+0x140 (0x005930a2) and +0xe0 of an unrelated caller
// object (0x005ab6f5). The two pointer members at +0x18 / +0x1c are the only
// fields this batch establishes.
struct OpaqueTwoSlotOwner {
    std::uint8_t opaque_000[0x18];
    void* slot_018;
    void* slot_01c;
    std::uint8_t opaque_020[0x65];  // 0x004c4630 reads a byte at +0x84
    std::uint8_t opaque_085[0x100];
};
static_assert(offsetof(OpaqueTwoSlotOwner, slot_018) == 0x18, "");
static_assert(offsetof(OpaqueTwoSlotOwner, slot_01c) == 0x1c, "");

// Node of the chained hash map walked by 0x00421950. Field order is read from
// 0x0042199b (key compare at +0x0), 0x00421989 (next at +0x8) and 0x0045b27a
// (value at +0x4). Widths are 4 bytes each; no key hashing function is visible.
struct HashMapNode {
    std::uint32_t key;
    std::uint32_t value;
    HashMapNode* next;
};

// Map body at this+8 for 0x0045b210: bucket array pointer at +0x4, bucket
// count at +0x8. The "end" slot is bucket_array[bucket_count], one past the
// last bucket, and is what the not-found path yields.
struct HashMapBody {
    std::uint32_t opaque_000;
    HashMapNode** buckets;
    std::uint32_t bucket_count;
};

// Owner of the HashMapBody at +0x8. Nothing else of this object is read.
struct OpaqueIdRegistry {
    std::uint8_t opaque_000[0x8];
    HashMapBody map_008;
};

// Receiver of 0x00438700. SDK candidate: Editors::EditorRigblock
// (Spore/Editors/EditorRigblock.h). The candidate rests on three observations,
// not on RTTI: (1) 0x00435a10 writes bits 0..0x3B of the dword at +0xdc8,
// which is exactly the span of the SDK enum EditorRigblockBoolAttributes;
// (2) the constructor-shaped 0x004a0b70 allocates 0xe08 bytes with the tag
// "Editor" and then calls 0x00435a10(0x14, 1), i.e. sets bit 0x14, which the
// SDK names kEditorRigblockModelIsNullBlock; (3) 0x00435a10 gates on
// this->field_28 with the 0x004adc40 predicate, the same pairing 0x00438700
// uses. Fields below +0x3e4 are NOT declared.
struct OpaqueEditorRigblock {
    std::uint8_t opaque_000[0x28];
    void* field_028;   // sub-object whose +0x4f byte 0x004adc40 reads
    std::uint8_t opaque_02c[0x30c];
    std::uint32_t field_33c;
    std::uint8_t opaque_340[0xa0];
    void* field_3e0;   // second sub-object, propagated by 0x004388b0
    std::uint8_t opaque_3e4[0x9e4];
    std::uint32_t flags_dc8;  // 60-bit EditorRigblockBoolAttributes bitfield
};

// Receiver of 0x004adb40 / 0x004adc20. This is the sub-object stored at
// rigblock+0x28, NOT the rigblock: 0x00438700 calls 0x004adc40 on
// self->field_28. The four flag bytes at +0x4c..+0x4f and the float run at
// +0x40/+0x44/+0x48 are proven by the accessor family at 0x004adaa0,
// 0x004adb00, 0x004adb60, 0x004adb80, 0x004adba0, 0x004adbc0, 0x004adbe0 and
// 0x004adc00. The float at +0x38 is proven by 0x004adaa0.
struct OpaqueEditorBlockSettings {
    std::uint8_t opaque_000[0x38];
    float field_038;
    std::uint8_t opaque_03c[0x4];
    float field_040;
    float field_044;
    float field_048;
    std::uint8_t flag_04c;
    std::uint8_t flag_04d;
    std::uint8_t flag_04e;
    std::uint8_t flag_04f;
};
static_assert(offsetof(OpaqueEditorBlockSettings, field_044) == 0x44, "");
static_assert(offsetof(OpaqueEditorBlockSettings, flag_04f) == 0x4f, "");

// Receiver of 0x00573d70. The receiver is the cEditor itself: callers inside
// Editors::cEditor::SetActiveMode (0x00587496), OnExit (0x00587d04) and
// OnKeyDown (0x0058aecb) pass their own EBP/ESI, and the callee reads the same
// offsets those callers use for cEditor members (+0xe4, +0xd4, +0xd0).
struct OpaqueEditor {
    std::uint8_t opaque_000[0xd0];
    void* field_0d0;
    void* field_0d4;
    std::uint8_t opaque_0d8[0xc];
    void* field_0e4;  // current primary part, refcounted
    std::uint8_t opaque_0e8[0xc];
    void* field_0f4;  // secondary part, cleared on a primary change
    std::uint8_t opaque_0f8[0x48];
    std::uint8_t flag_0140;
    std::uint8_t flag_0141;
    std::uint8_t opaque_0142[0x1];
};
static_assert(offsetof(OpaqueEditor, field_0e4) == 0xe4, "");
static_assert(offsetof(OpaqueEditor, field_0f4) == 0xf4, "");
static_assert(offsetof(OpaqueEditor, flag_0140) == 0x140, "");
static_assert(offsetof(OpaqueEditor, flag_0141) == 0x141, "");

// ---------------------------------------------------------------------------
// Opaque ports. Declared, never given a fabricated body.
// ---------------------------------------------------------------------------

// 0x004388b0(void* self, void* candidate): walks the vector pair at self+0x340 /
// self+0x344 looking for an element whose first dword equals candidate, and when
// the element is absent runs a release/notify sequence. Called from four sites
// in 0x00438700; the exact role is bounded, not established.
void Port_004388b0(void* self, void* candidate);

// 0x004adc40(void* self): returns the byte at self+0x4f.
std::uint8_t Port_004adc40(void* self);

// 0x004a7e60(void* self): byte predicate, false for a null receiver.
std::uint8_t Port_004a7e60(void* self);

// 0x0044f220(void* self): returns the dword at self+0x1c0.
std::uint32_t Port_0044f220(void* self);

// 0x00421950(HashMapBody* map, HashMapNode** out_pair, const std::uint32_t* key):
// writes a two-dword {node, slot} pair. On a hit the first word is the matched
// node; on a miss the first word is the dereferenced end sentinel and the second
// word is the sentinel slot address. Caller-cleaned 8 bytes.
void Port_00421950(HashMapBody* map, std::uint32_t* out_pair, const std::uint32_t* key);

// 0x0047e6c0(void* self): returns the dword at self+0x10.
void* Port_0047e6c0(void* self);

// 0x0047ec20(void* self): returns the dword at self+0x1c.
std::uint32_t Port_0047ec20(void* self);

// 0x00435ed0(std::uint32_t marker, void* payload): cdecl, 8 bytes caller-cleaned.
void Port_00435ed0(std::uint32_t marker, void* payload);

// 0x00573c00(void* editor, void* arg2, std::uint32_t arg3): thiscall, RET 0x8.
void __attribute__((thiscall)) Port_00573c00(void* editor, void* arg2,
                                       std::uint32_t arg3);

// 0x00572770(void** slot): returns slot[0]->vtable[0x0c](0x50a993c) or 0.
void* Port_00572770(void** slot);

// 0x0043c3d0(void* list, void* item): linear index of item, -1 when absent.
std::int32_t Port_0043c3d0(void* list, void* item);

// 0x0043e760(void* list, std::uint32_t index): marks list item `index` selected.
void Port_0043e760(void* list, std::uint32_t index);

// 0x0043e7e0(void* list, std::uint32_t index, std::uint8_t value): marks the
// list item `index` unselected and propagates.
void Port_0043e7e0(void* list, std::uint32_t index, std::uint8_t value);

// 0x00572020 carries the SDK-derived name Audio::StopAudio
// (Spore/Audio/AudioSystem.h declares it at 0x571F40 / 0x572020). Observed
// shape here is cdecl, two stack words, bare RET, 8 bytes caller-cleaned.
void Port_00572020(void* instance, std::uint32_t arg2);

// Refcount hooks reached through the primary part's vtable.
// 0x00573e78 dispatches slot +0x00, 0x00573e88 dispatches slot +0x04.
void Port_vtbl_addref(void* self);
void Port_vtbl_release(void* self);
// 0x00573e14 / 0x00573eb3 dispatch slot +0x30 with (3,1) and (0,1).
void Port_vtbl_30_set_state(void* self, std::uint32_t a, std::uint32_t b);
// 0x00573e2f dispatches slot +0x0c with the type id 0x50a993c.
void* Port_vtbl_0c_query(void* self, std::uint32_t type_id);
// 0x00573ebc dispatches slot +0x10 and compares the result to 0x50a993c.
std::uint32_t Port_vtbl_10_type_id(void* self);

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
