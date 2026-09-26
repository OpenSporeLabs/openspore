// Clean-room reconstruction of SporeApp.exe 0x0057ac00 (sha256 25d42a7a...9d914e).
//
// Evidence: live Ghidra (decompile + disassembly + read_memory + 6 callsite
// windows) on program SporeApp.exe. No proprietary EA source was consulted.
//
// The receiver is Editors::cEditor. Six of the offsets it touches are documented
// in Spore/Editors/Editor.h at exactly the observed positions:
//     /* 24h  */ PropertyListPtr mpPropList;
//     /* 48h  */ int              field_48;
//     /* 98h  */ EditorModel*     mpEditorModel;
//     /* 2A8h */ uint32_t         mSaveExtension;
//     /* 4B1h */ bool             field_4B1;
//     /* 4B2h */ bool             field_4B2;
// and the three direct callers reached from Ghidra-named methods are
// Editors::cEditor::CommitEditHistory (0x00586410), ::Undo (0x0058a5a0) and
// ::Redo (0x0058a950), whose SDK DeclareAddress comments (0x586410, 0x58A5A0,
// 0x58A950) match Ghidra's imported symbols exactly. No vtable containing
// 0x0057ac00 exists in .rdata/.data, so it is a non-virtual member and the SDK
// has no name for it. The class is asserted; the METHOD NAME IS NOT.

#pragma once

#include <cstddef>
#include <cstdint>

namespace openspore {
namespace dispatch_b05 {

// ---------------------------------------------------------------------------
// Opaque types. Layout is modelled only where the disassembly proves it.
// ---------------------------------------------------------------------------

// A 4 x uint32 capability mask, passed and returned by pointer and also built
// by value on the stack (0x0057ac6f..0x0057ac85).
struct EditMask0057ac00 {
    std::uint32_t word[4];
};

// Spore/CommonIDs.h documents these two literals as
//     crt = 0x2B978C46  (Creatures)
//     cll = 0x3D97A8E4  (Cells)
// and 0x0057ac93/0x0057ac9a compare mSaveExtension against exactly them.
inline constexpr std::uint32_t kAssetTypeCreature = 0x2b978c46u;
inline constexpr std::uint32_t kAssetTypeCell = 0x3d97a8e4u;

// Spore/Editors/EditorRigblock.h documents these as model capabilities
//     kModelCapabilityMouth     = 0xb00f0fec
//     kModelCapabilityCellMouth = 0x11b79301
// and 0x0057acba/0x0057acd6 push exactly them.
inline constexpr std::uint32_t kModelCapabilityMouth = 0xb00f0fecu;
inline constexpr std::uint32_t kModelCapabilityCellMouth = 0x11b79301u;

// Global bool property id read through 0x006a25a0 at 0x0057ac0f. The same id is
// read at the top of 0x004f3de0, which is the evaluator this function calls, so
// the id is a global "editing disabled" switch. The property's runtime value is
// not observable statically.
inline constexpr std::uint32_t kPropGlobalEditingDisabled = 0x055d7ca1u;

// Property ids resolved through App::Property::GetKey at 0x0057ad1d and
// 0x0057ad71. Both reappear inside 0x004f3de0, correlated with mask bits
// 0x40000 and 0x20 respectively.
inline constexpr std::uint32_t kPropertyIdMaskBit40000 = 0x7a926123u;
inline constexpr std::uint32_t kPropertyIdMaskBit20 = 0xf5cbe065u;

// Opaque property/undo-record receiver. The pointer at cEditor + 0x178 is a
// vector whose final element (0x0058a740, 0x0057eb69, 0x0058d2e8 all read
// [vector_end - 4]) is handed in as the record argument.
struct EditHistoryRecord0057ac00 {
    std::uint32_t opaque[1];
};

// cEditor. Only the offsets the body reads are modelled.
struct CEditor0057ac00 {
    std::uint32_t pad_0000[0x24 / 4];
    void* field_24_prop_list;      // 0x0057ad03: MOV EAX,dword ptr [ESI + 0x24]
    std::uint32_t pad_0028[0x20 / 4];
    std::uint32_t field_48;        // 0x0057ad36/0x0057ad87: LEA EDX,[ESI + 0x48]
                                  // passed by address to two helpers that
                                  // read-modify-write it
    std::uint32_t pad_004c[0x4c / 4];
    void* field_98_editor_model;   // 0x0057aca1: MOV ECX,dword ptr [ESI + 0x98]
    std::uint32_t pad_009c[0x1cc - 0x9c];
    void* field_1cc;               // 0x0057a960: MOV EAX,dword ptr [ECX + 0x1cc]
    std::uint32_t pad_1d0[0x2a8 - 0x1d0];
    std::uint32_t field_2a8_save_extension;  // 0x0057ac8d
    std::uint32_t pad_2ac[(0x4b1 - 0x2ac) / 4];
    std::uint8_t field_4b1;        // 0x0057ada5: CMP byte ptr [ESI + 0x4b1],0x0
    std::uint8_t field_4b2;        // 0x0057adae: CMP byte ptr [ESI + 0x4b2],0x0
};

// ---------------------------------------------------------------------------
// Opaque ports.
//
// NONE of the following is given a body. Where the operation could be read out
// of the callee, the description says so and names the evidence; otherwise the
// port stays opaque.
// ---------------------------------------------------------------------------

// 0x006a25a0, __thiscall, receiver in ECX loaded from the global 0x015fd918.
// Returns AL = whether global property <id> is non-zero. Named by Ghidra
// Prop_GetPropValueBool.
bool PropertyManager0057ac00_get_bool006a25a0(void* property_manager,
                                              std::uint32_t property_id);

// 0x006a1250, cdecl, three stack dwords, returns AL.
// 0x0057ad1c/0x0057ad71/0x0057ad77 push (&out_key, property_id, prop_list).
// Body: if prop_list == 0 return false; otherwise look the property up and, on
// success, copy its 12-byte ResourceKey (instanceID, typeID, groupID) into
// *out_key and return true. Ghidra names the symbol App::Property::GetKey.
bool PropertyList0057ac00_get_key006a1250(const void* prop_list,
                                          std::uint32_t property_id,
                                          void* out_resource_key);

// 0x0057a960, __thiscall with one stack argument (RET 0x4).
// out[0..3] = sub[+0x24..+0x30] AND {~g_015da7ec, ~g_015da7f0, ~g_015da7f4,
// ~g_015da7f8} respectively; all four are zero when this->field_1cc == 0.
void Editor0057ac00_collect_local_mask0057a960(const CEditor0057ac00* self,
                                               EditMask0057ac00* out);

// 0x0057a9e0, __thiscall with one stack argument. Starts from the globals
// 0x015daa40/44/48/4c, clears the same 0x015da7eX bits, and then, when
// this->field_1cc != 0, also clears everything 0x0057a960 would have produced.
// Returns its out pointer.
EditMask0057ac00* Editor0057ac00_collect_global_mask0057a9e0(
    const CEditor0057ac00* self, EditMask0057ac00* out);

// 0x004bac30, __thiscall, RET 0x18 (six stack dwords: a pointer, a 16-byte
// struct passed BY VALUE, and one trailing dword). Copies the incoming 16-byte
// struct to its own frame and tail-calls 0x004f3de0. Its return value is
// discarded by 0x0057ac00.
// The exact argument marshalling between 0x004bac30 and 0x004f3de0 is NOT
// resolved: 0x004bac5c pushes dword ptr [EBP + 0x8], which in that frame is the
// function's own return address.
void EditHistoryRecord0057ac00_evaluate004bac30(
    EditHistoryRecord0057ac00* record, EditMask0057ac00* out,
    EditMask0057ac00 requested_mask_by_value, std::uint32_t trailing);

// 0x004f3de0, the capability evaluator reached through 0x004bac30. It starts
// from an all-zero result mask, re-checks the same global property
// 0x055d7ca1, and for every bit set in the requested mask runs one predicate
// (0x004edeb0, 0x004ee3b0, 0x004ecec0, 0x004ed7f0, 0x004ed320, 0x004ee9b0,
// 0x004ee560, 0x004f1350, 0x004ef190, 0x004f01f0, 0x004f2610, 0x004f2210,
// 0x004f3650, 0x004f31c0, 0x004eda30) and keeps the bit only if the predicate
// also produced it. Observed capability bits: 0x1, 0x2, 0x4, 0x8, 0x10, 0x20,
// 0x40, 0x80, 0x100, 0x200, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000,
// 0x40000, 0x80000, 0x8000000. Modelled as an opaque port.
void CapabilityEvaluator0057ac00_evaluate004f3de0(
    EditMask0057ac00* out, EditHistoryRecord0057ac00* record,
    EditMask0057ac00 requested_mask_by_value, bool early_out);

// 0x00435b60, __thiscall with one stack dword. Linear search of a 0x14-byte
// record array at [self + 0xc0c, self + 0xc10); the search key is compared
// against the first dword of each record and the third dword of the match is
// returned, or 0 when nothing matches.
std::uint32_t Rigblock0057ac00_find_capability_value00435b60(
    const void* rigblock, std::uint32_t capability_id);

// Spore/Editors/EditorModel.h: /* 18h */ eastl::vector<EditorRigblockPtr>
// mRigblocks;, int GetRigblocksCount() const, EditorRigblock* GetRigblock(int).
// 0x004accf0 / 0x004accb0 match those two exactly.
std::int32_t EditorModel0057ac00_rigblock_count004accf0(
    const void* editor_model);
void* EditorModel0057ac00_rigblock_at004accb0(const void* editor_model,
                                              std::int32_t index);

// 0x004efb20, cdecl, three stack dwords, returns AL. Reads/writes bit 0x40000
// of its uint32* third argument and returns 0 when an enumerated set does not
// cover the requested key. Also mutates cEditor +0x48 in place.
bool EditHistoryRecord0057ac00_check_required004efb20(
    EditHistoryRecord0057ac00* record, std::uint32_t key_instance_id,
    std::uint32_t* in_out_mask);

// 0x004ef880, cdecl, three stack dwords. Same shape; owns bit 0x20.
bool EditHistoryRecord0057ac00_check_optional004ef880(
    EditHistoryRecord0057ac00* record, std::uint32_t key_instance_id,
    std::uint32_t* in_out_mask);

// 0x004edf40, cdecl, two stack dwords, bare RET. Compares the wide string
// against the table at 0x013ec468 (first entries L"creature_rotate",
// L"creature_size"), then scans its characters with 0x004f6ab0; it sets bit
// 0x100000 when the name is absent from the table, bit 0x200000 when a character
// lookup hits, and forces bit 0x10 otherwise. Its return value is discarded.
std::uint32_t NameTable0057ac00_refine004edf40(const char16_t* name,
                                               EditMask0057ac00* in_out_mask);

// Globals read. Live read_memory returns 16 zero bytes at 0x015da7e0 and 24 zero
// bytes at 0x015daa40, and 8 zero bytes at 0x015fd918: all three are
// runtime-initialised and have no static initialiser, so their runtime values
// are NOT established by static analysis.
extern std::uint32_t g_015da7ec;
extern std::uint32_t g_015da7f0;
extern std::uint32_t g_015da7f4;
extern std::uint32_t g_015da7f8;
extern std::uint32_t g_015daa40;
extern std::uint32_t g_015daa44;
extern std::uint32_t g_015daa48;
extern std::uint32_t g_015daa4c;
extern void* g_015fd918;  // property manager, receiver of 0x006a25a0

// ---------------------------------------------------------------------------
// Reconstructed body.
//
// 0x0057ac00, 166 instructions, 0x0057ac00..0x0057ae01, 516 bytes.
//
// ABI: __thiscall, receiver in ECX, FOUR stack dwords consumed by `RET 0x10`.
// Only three of them are read by the body:
//   [ESP+0x5c] = arg1, the 16-byte out buffer, also returned in EAX
//   [ESP+0x60] = arg2, the edit-history record
//   [ESP+0x64] = arg3, the part name
//   [ESP+0x68] = arg4, pushed as 1 at all six observed callsites and never read
// ---------------------------------------------------------------------------
extern "C" EditMask0057ac00* Editor_0057ac00_ComputeGrantedEditMask(
    CEditor0057ac00* self, EditMask0057ac00* out,
    EditHistoryRecord0057ac00* record, const char16_t* part_name,
    std::uint32_t early_out_flag);

}  // namespace dispatch_b05
}  // namespace openspore
