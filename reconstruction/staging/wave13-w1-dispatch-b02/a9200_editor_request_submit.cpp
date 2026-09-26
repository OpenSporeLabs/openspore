// Wave-13 worker batch b02 -- target 0x005a9200
// Observed body: FUN_005a9200, 705 bytes, 0x005a9200..0x005a94c0, 199 instructions.
// Reconstructed as Editors::EditorRequest::Submit(Editors::EditorRequest*).
//
// Every statement below is anchored to an instruction address in the original;
// see reconstruction/metadata/wave13-w1-dispatch-b02/005a9200.json for the full
// address-to-claim table. Semantics are preserved, not the pseudocode shape:
// the 34-way comparison tree is a linear search over a constant id table and is
// written here as a table walk that returns the same bit index.

#include "a9200_editor_request_submit.hpp"

namespace openspore::wave13::b02 {
namespace {

// ---------------------------------------------------------------------------
// The 34-way comparison tree at 0x005a92fb..0x005a94bc.
//
// This is NOT a jump table: the listing is a hand-rolled binary search over
// CMP/JZ/JG pairs with no indexed load, so it is reproduced as an ordered
// constant table walked linearly. ECX ends up holding the bit index, 0 when no
// case matches (XOR ECX,ECX at 0x005a92f9 is the only zero source).
//
// The three constants 0x1d2ec0a4..0x1d2ec0a7 are one range test, not four
// cases: CMP EAX,0x1d2ec0a7 / JG and CMP EAX,0x1d2ec0a4 / JGE, both to the
// MOV ECX,0x5 block at 0x005a93d4. The table therefore lists the low bound and
// carries a stride.
// ---------------------------------------------------------------------------

struct IdToBit {
    std::uint32_t id;
    std::uint8_t stride;  // 1 for a single id, 4 for the 0x1d2ec0a4 range
    std::uint8_t bit;
};

// Sorted ascending, matching the JG/JZ ladder order of the original.
constexpr IdToBit kEditorIdToBit[] = {
    {0x8707be7du, 1, 0x9},   // 0x005a932b JZ -> 0x005a94b7
    {0x8f963dcbu, 1, 0xb},   // 0x005a9336 JZ -> 0x005a9466
    {0x96b24187u, 1, 0xf},   // 0x005a9341 JZ -> 0x005a934c MOV ECX,0xf
    {0x99e92f05u, 1, 0x9},   // 0x005a931e JZ -> 0x005a94b7
    {0x9ad7d4aau, 1, 0xa},   // 0x005a935d JZ -> 0x005a94ad
    {0x9adf00a9u, 1, 0x8},   // 0x005a9368 JZ -> 0x005a9384
    {0xa56567f7u, 1, 0xe},   // 0x005a936f JZ -> 0x005a937a
    {0xb7af8ff8u, 1, 0x6},   // 0x005a9311 JZ -> 0x005a9422
    {0xbdd15f3du, 1, 0x9},   // 0x005a93a2 JZ -> 0x005a94b7
    {0xbc1041e6u, 1, 0xd},   // 0x005a939b JZ -> 0x005a93b4
    {0xc15695dau, 1, 0xd},   // 0x005a93ad JZ -> 0x005a93b4
    {0xf670aa43u, 1, 0xa},   // 0x005a938e JZ -> 0x005a94ad
    {0x156276d1u, 1, 0x7},   // 0x005a93bb JZ -> 0x005a9406
    {0x1a4e0708u, 1, 0xc},   // 0x005a93c2 JZ -> 0x005a948d
    {0x1d2ec0a0u, 1, 0x5},   // 0x005a93cd JZ -> 0x005a93d4
    {0x1d2ec0a4u, 4, 0x5},   // 0x005a9306 JGE -> 0x005a93d4 (covers ..0x1d2ec0a7)
    {0x1f2a25b6u, 1, 0xb},   // 0x005a93f1 JZ -> 0x005a9466
    {0x2090a11bu, 1, 0xd},   // 0x005a93f8 JZ -> 0x005a93b4
    {0x247e2615u, 1, 0x7},   // 0x005a93ff JZ -> 0x005a9406
    {0x281f5960u, 1, 0x6},   // 0x005a93ef JZ -> 0x005a9422
    {0x290adaceu, 1, 0x6},   // 0x005a940d JZ -> 0x005a9422
    {0x2a5147a9u, 1, 0xb},   // 0x005a9414 JZ -> 0x005a9466
    {0x312e9d6au, 1, 0x6},   // 0x005a941b JZ -> 0x005a9422
    {0x37e82da1u, 1, 0xe},   // 0x005a93e6 JZ -> 0x005a937a
    {0x441cd3e6u, 1, 0xc},   // 0x005a9476 JZ -> 0x005a948d
    {0x449c040fu, 1, 0xc},   // 0x005a947d JZ -> 0x005a948d
    {0x465c50bau, 1, 0x6},   // 0x005a9484 JZ -> 0x005a9422
    {0x4e3f7777u, 1, 0x9},   // 0x005a9474 JZ -> 0x005a94b7
    {0x5bf8f774u, 1, 0x6},   // 0x005a949b JZ -> 0x005a9422
    {0x72c49181u, 1, 0x9},   // 0x005a9499 JZ -> 0x005a94b7
    {0x7d433fadu, 1, 0xa},   // 0x005a94a2 JZ -> 0x005a94ad
};

// Result of the tree: 0 when no case matches, otherwise 5..15 inclusive.
// Values 0..4 are unreachable in the original: no arm produces them.
std::uint8_t editor_id_to_bit_index(std::int32_t editor_id) {
    const std::uint32_t key = static_cast<std::uint32_t>(editor_id);
    for (const IdToBit& e : kEditorIdToBit) {
        if (key >= e.id && key < e.id + e.stride) {
            return e.bit;
        }
    }
    return 0;
}

}  // namespace

// The 0x40-byte App message object allocated at 0x005a9289. Only the three
// observed members are named; the 16 bytes at 0x013eb844 (+0) .. 0x013eb850
// (+0xc) and the two literals that follow it ("queuing %ls for bake\n" and
// "No key -- you need to save the model first.\n") are the class's own data.
// Slots +0/+4/+8 are the deleting destructor 0x004230e0, an AddRef-shaped
// 0x00432a50 and a Release-shaped 0x00404f90.
struct AppBakeMessagePort {
    void** vtable;  // +0x00
    std::uint32_t field_04;
    std::uint32_t field_08;
    std::uint8_t pad0c[0x24];
    std::uint32_t message_id;  // +0x30, written 0x00e11332
    std::uint32_t field_34;
    std::uint32_t field_38;
};

std::uint8_t FUN_005a9200_reconstruct(EditorRequest* request) {
    // 0x005a9211: MOV EDI,dword ptr [ESP + 0x10] -- the single stack argument.
    EditorRequest* const req = request;

    // 0x005a9203..0x005a920f: IRenderer::Get(), then virtual slot +0x38 on it.
    // 0x005a9218: the result lands in mCallingGameModeID.
    req->mCallingGameModeID = IRenderer_func38h_via_slot_38(graphics_renderer_get_port());

    // 0x005a9215..0x005a922c: four-dword zero test over mEditableTests.flags.
    bool all_zero = true;
    for (int i = 0; i < 4; ++i) {
        if (req->mEditableTests.flags[i] != 0) {
            all_zero = false;
            break;
        }
    }
    // 0x005a922e..0x005a924c: seed from Editors::ContentValidation::
    // sIllegalCharacters, four consecutive dwords at 0x015da7c4.
    if (all_zero) {
        for (int i = 0; i < 4; ++i) {
            req->mEditableTests.flags[i] = g_content_validation_s_illegal_characters[i];
        }
    }

    // 0x005a924f: CMP dword ptr [EDI + 0xc],0xffffffff -- the -1 sentinel on
    // mEditorName. 0x005a9255 passes &mModelKey in EAX to the resolver.
    if (req->mEditorName == -1) {
        req->mEditorName = resolve_editor_name_from_model_key(&req->mModelKey);
    }

    // 0x005a9260: the notify singleton, cached in ESI.
    AppSingletonPort* const app = app_singleton_get_port();

    // 0x005a9265..0x005a9278: four pushes, so slot +0x18 takes
    // (0xb03bc30c, req, 0, 0).
    app_singleton_notify_slot_18(app, 0xb03bc30cu, req, nullptr, nullptr);

    // 0x005a927a..0x005a9289: six pushes then CALL 0x00f473a0, cleaned by
    // ADD ESP,0x18 at 0x005a928e. Size 0x40, type name "App" at 0x013ebc58.
    auto* message = static_cast<AppBakeMessagePort*>(
        app_object_allocate_port(0x40, "App", 0, 0, 0, 0));

    // The original does not survive a null return. 0x005a9356 sets EBX to 0 and
    // jumps to 0x005a92c5, which is MOV dword ptr [EBX + 0x30],0xe11332, i.e.
    // a write to linear address 0x30. Preserved verbatim, including the fault.
    if (message == nullptr) {
        message->message_id = 0x00e11332u;  // 0x005a92c7, deliberately UB
    }

    // 0x005a9299: field_30 = 0; 0x005a92a0: derived vtable 0x013eb90c;
    // 0x005a92a8..0x005a92ab: XCHG dword ptr [EAX + 0x4],ECX with ECX = 0, so
    // field_04 becomes 0 and the old field_04 lands in ECX; 0x005a92ad: base
    // vtable 0x013eb844; 0x005a92b3: field_38 = 0.
    message->field_38 = 0;
    message->field_04 = 0;

    // 0x005a92ba..0x005a92c3: virtual slot +0x04 of vtable 0x013eb844, which
    // holds 0x00432a50. That body is LOCK / INC [this+4] / return old, i.e. the
    // AddRef of a refcount kept at +4.
    {
        void* const addref = message->vtable[1];
        using AddRefFn = std::uint32_t (*)(AppBakeMessagePort*);
        reinterpret_cast<AddRefFn>(addref)(message);
    }

    // 0x005a92c7: message_id = 0x00e11332. 0x005a92d0: field_08 = 0x00dbdba1,
    // an odd immediate, not a pointer: 0x00dbdba1 lies in .text and holds
    // instruction bytes, so this is an id constant.
    message->message_id = 0x00e11332u;
    message->field_08 = 0x00dbdba1u;

    // 0x005a92d7..0x005a92e3: the same four-argument shape on slot +0x18, now
    // carrying the message object.
    app_singleton_notify_slot_18(app, message->message_id, message, nullptr, nullptr);

    // 0x005a92e5: PUSH 0x1003 survives 0x0067cab0, whose RET has no immediate.
    // 0x005a92ef: MOV ECX,EAX then 0x005a92f1 CALL 0x00801bb0 consumes it as
    // the only stack argument. The bool result is never read.
    global_015fcc50_probe_1003(global_015fcc50_get_port(), 0x1003);

    // 0x005a92f6: the switch key is mEditorName.
    const std::uint8_t bit = editor_id_to_bit_index(req->mEditorName);

    // 0x005a9427..0x005a942f: the App property gate. Two dependent loads and a
    // non-zero test; JNZ at 0x005a9436 skips the whole block.
    void* const* const props_slot = reinterpret_cast<void* const*>(
        reinterpret_cast<std::uint8_t*>(g_app_properties_015fd918) + 0x3c);
    const auto* const props = static_cast<const std::uint8_t*>(*props_slot);
    if (props[0x118] == 0 && bit != 0) {
        // 0x005a943c..0x005a9441: mask = 1 << bit.
        const std::uint32_t mask = 1u << bit;
        // 0x005a9443..0x005a9446 push three dwords that 0x00675250 does not pop
        // (its RET has no immediate), so they are the stack arguments of
        // 0x00676ed0. Its first argument, 0x00d082675a, is popped unread.
        set_progress_flags_slot(global_015fc250_get_port(), 0x00d082675au, mask, true);
    }

    // 0x005a9457..0x005a945e: virtual slot +0x08 of vtable 0x013eb844, which
    // holds 0x00404f90 -- LOCK / DEC [this+4] / call slot +0 with 1 at zero.
    {
        void* const release = message->vtable[2];
        using ReleaseFn = std::uint32_t (*)(AppBakeMessagePort*);
        reinterpret_cast<ReleaseFn>(release)(message);
    }

    // 0x005a9462: MOV AL,0x1. Only the low byte is written, so bits 8..31 of
    // EAX are undefined on exit; every caller inspected discards the value.
    return 1;
}

}  // namespace openspore::wave13::b02
