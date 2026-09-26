// Wave-13 worker batch b02 -- target 0x005a9200
// Clean-room reconstruction from SporeApp.exe 3.1.0.22 (sha256 25d42a7a...9d914e).
//
// Observed identity: Editors::EditorRequest::Submit(Editors::EditorRequest*)
//   * caller 0x005a94d0 allocates the argument with size 0x9c, which is exactly
//     ASSERT_SIZE(Editors::EditorRequest, 0x9C) in the Spore-ModAPI header, and
//     immediately calls 0x005a9200 then slot +8 of the object's vtable.
//   * every field the body touches lands on a documented EditorRequest member:
//     +0x0c mEditorName (default -1), +0x10..+0x1b mModelKey (ResourceKey),
//     +0x1c mCallingGameModeID, +0x24 mEditableTests (ContentValidation = 4 x int32).
//   * the return is the byte 1 in AL, matching "static bool Submit(...)".
// The two message posts and the achievement-progress key stay opaque ports; see
// reconstruction/metadata/wave13-w1-dispatch-b02/005a9200.json.

#pragma once

#include <cstdint>

namespace openspore::wave13::b02 {

// Spore::ResourceKey, SDK Spore/ResourceKey.h: instanceID / typeID / groupID.
struct ResourceKey {
    std::uint32_t instanceID;
    std::uint32_t typeID;
    std::uint32_t groupID;
};

// Spore::Editors::ContentValidation, SDK Spore/Editors/ContentValidation.h: int32_t flags[4].
struct ContentValidation {
    std::int32_t flags[4];
};

// Partial layout of Spore::Editors::EditorRequest. Only the members this
// translation unit reads or writes are named; the gaps are kept as padding so
// the offsets stay byte-exact with the observed [reg+disp] accesses.
struct EditorRequest {
    void** vtable;                              // +0x00  IRefCounted dtor / +4 AddRef / +8 Release
    std::uint32_t field_04;                     // +0x04
    std::int32_t mRefCount;                     // +0x08
    std::int32_t mEditorName;                   // +0x0c  documented default -1
    ResourceKey mModelKey;                      // +0x10  instanceID / typeID / groupID
    std::uint32_t mCallingGameModeID;           // +0x1c
    std::uint8_t mbIsFirstTimeInEditor;         // +0x20
    std::uint8_t field_21[3];                   // +0x21
    ContentValidation mEditableTests;           // +0x24
    std::uint8_t field_34[0x90 - 0x34];         // +0x34 .. +0x8f
    std::uint32_t field_90;                     // +0x90
    void* mpCollectableItems;                   // +0x94
    void* mpNext;                               // +0x98
};
static_assert(sizeof(EditorRequest) == 0x9c, "EditorRequest is 0x9c bytes in the original");

// ---------------------------------------------------------------------------
// Opaque ports. Declared, not implemented: no original body is claimed for any
// of these, and none of them is inlined from the target.
// ---------------------------------------------------------------------------

// 0x0067dd10 -- Ghidra SDK symbol Graphics::IRenderer::Get(), reads global
// 0x015fd8b0. 0 args, returns IRenderer*.
struct IRenderer;
IRenderer* graphics_renderer_get_port();

// Virtual slot +0x38 of Graphics::IRenderer. The SDK names it func38h and
// declares no parameters; the observed result is stored into
// EditorRequest::mCallingGameModeID.
std::uint32_t IRenderer_func38h_via_slot_38(IRenderer* renderer);

// 0x0067dcc0 -- Ghidra SDK symbol App::IAppSystem::Get(), reads global
// 0x015fd890. The concrete interface behind 0x015fd890 is NOT established
// (the singleton has exactly one writer, 0x0067deb0, with no callers), and the
// observed 4-argument shape at slot +0x18 contradicts the SDK's
// IAppSystem::InitPlugins(1 arg) at the same slot. Modelled as a notify port.
struct AppSingletonPort;
AppSingletonPort* app_singleton_get_port();

// Virtual slot +0x18 of AppSingletonPort. Observed call shape is
// (uint32 id, void* payload, 0, 0) with ECX as receiver.
void app_singleton_notify_slot_18(AppSingletonPort* self,
                                 std::uint32_t message_id,
                                 void* payload,
                                 void* arg3,
                                 void* arg4);

// 0x00f473a0 -> 0x009289f0. Six-argument, caller-cleanup allocator thunk. Every
// observed call passes (size, &"App", 0, 0, 0, 0). Returns null is not handled
// by the target, which then writes through the null pointer.
void* app_object_allocate_port(std::uint32_t size,
                               const char* type_name,
                               std::uint32_t a2,
                               std::uint32_t a3,
                               std::uint32_t a4,
                               std::uint32_t a5);

// 0x005a8f80. Takes the request's mModelKey in EAX (register argument, not
// thiscall). Resolves the editor id for a model key.
std::int32_t resolve_editor_name_from_model_key(ResourceKey* model_key);

// 0x0067cab0 -- two-instruction getter, reads global 0x015fcc50, RET with no
// immediate so it consumes no stack. The 0x1003 pushed before it stays on the
// stack and is consumed by the next call.
void* global_015fcc50_get_port();

// 0x00801bb0 -- __thiscall(void* self, uint32 key). The 0x1003 pushed at
// 0x005a92e5 is this call's only stack argument. The returned bool is discarded
// by the target, so the call is a side-effecting cache probe.
bool global_015fcc50_probe_1003(void* self, std::uint32_t key);

// 0x00675250 -- two-instruction getter, reads global 0x015fc250, RET with no
// immediate. The three values pushed before it stay on the stack and become the
// stack arguments of 0x00676ed0.
void* global_015fc250_get_port();

// 0x00676ed0 -- __thiscall, RET 0xC, three stack arguments. Body shape matches
// Pollinator::cAchievementsManager::SetProgressFlags: OR/AND-NOT a 32-bit mask
// at +4 of the record returned by 0x00676660, then re-evaluate if bit 0 of the
// record is set. The first stack argument is popped and never read.
void set_progress_flags_slot(void* self,
                             std::uint32_t arg1_unused,
                             std::uint32_t progress_flags,
                             bool set_flag);

// The 4 x int32 image at 0x015da7c4, Ghidra SDK symbol
// Editors::ContentValidation::sIllegalCharacters. Read as four dwords.
extern const std::int32_t g_content_validation_s_illegal_characters[4];

// The singleton at 0x015fd918, dereferenced as [+0x3c] then [+0x118].
extern void* g_app_properties_015fd918;

}  // namespace openspore::wave13::b02
