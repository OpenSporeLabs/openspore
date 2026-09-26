// Clean-room reconstruction of SporeApp.exe 0x0062f540.
//
// Order of operations, offsets, immediates and branch polarity are transcribed
// from the live disassembly listing of 0x0062f540..0x0062f5b8. Nothing here is
// invented; unresolved callees are declared as ports in the header.

#include "playmode_backgrounds_0062f540.hpp"

namespace openspore {
namespace dispatch_b05 {

// 0x0062f540: SUB ESP,0x14 / PUSH ESI / MOV ESI,ECX / PUSH EDI
// 0x0062f547: LEA ECX,[ESP + 0x8] -> the 0x14-byte temporary at ESP0-0x14
// 0x0062f54b: CALL 0x006b5060
void PlayModeBackgrounds_0062f540_UpdatePageNumbers(
    PlayModeBackgrounds0062f540* self) {
    alignas(4) std::uint8_t localized_string[0x14];
    void* const text_scratch = localized_string;

    // 0x0062f544: the receiver is taken from ECX, not from a stack slot.
    PlayModeBackgrounds0062f540* const receiver = self;

    LocalizedString0062f540_ctor006b5060(text_scratch);

    // 0x0062f550: MOV ECX,dword ptr [ESI + 0x34] is the hidden receiver load for
    // the thiscall at 0x0062f558, NOT a dead store: 0x00634dc4 is
    // `ADD ECX,0x14`, an MSVC this-adjustment.
    IWindow0062f540* const page_count_window =
        PlayModeUI0062f540_find_window_by_id00634dc0(
            receiver->field_34_play_mode_ui, kControlIdBgPageCount);

    // 0x0062f55f: TEST EDI,EDI / 0x0062f561: JZ 0x0062f5aa
    // Both the localized-string setup and the two global writes are inside this
    // guard; a null lookup result skips straight to the destructor.
    if (page_count_window != nullptr) {
        // 0x0062f563..0x0062f576: three pushed dwords, callee pops 0xc.
        // 0x0062f563 pushes L"*BG Page Count*" as the third, unread argument.
        (void)LocalizedString0062f540_set_localized006b54b0(
            text_scratch, kLocalizationIdPageCountFormat,
            kAlternateIdPageCountFormat, kDebugTagBgPageCount);

        // 0x0062f57b: MOV EAX,dword ptr [ESI + 0x38]
        // 0x0062f57e: MOV ECX,dword ptr [0x015f7cf4]
        // 0x0062f584: INC EAX
        // 0x0062f585: MOV dword ptr [ECX + 0x20],EAX
        g_localized_arg_table_015f7cf4->field_20 =
            receiver->field_38_page_index + 1;

        // 0x0062f588: MOV EDX,dword ptr [ESI + 0x3c]
        // 0x0062f58b: MOV EAX,[0x015f7cf4]   (re-read, absolute addressing)
        // 0x0062f590: INC EDX
        // 0x0062f591: MOV dword ptr [EAX + 0x24],EDX
        g_localized_arg_table_015f7cf4->field_24 =
            receiver->field_3c_page_count + 1;

        // 0x0062f594: MOV ESI,dword ptr [EDI]      -> vtable
        // 0x0062f596: LEA ECX,[ESP + 0x8]          -> the temporary again
        // 0x0062f59a: CALL 0x006b55c0              -> resolved text in EAX
        const char16_t* const caption =
            LocalizedString0062f540_resolve006b55c0(text_scratch);

        // 0x0062f59f: MOV EDX,dword ptr [ESI + 0x80]  -> vtable slot +0x80
        // 0x0062f5a5: PUSH EAX
        // 0x0062f5a6: MOV ECX,EDI
        // 0x0062f5a8: CALL EDX
        IWindow0062f540_vslot80_set_caption(page_count_window, caption);
    }

    // 0x0062f5aa: LEA ECX,[ESP + 0x8] / 0x0062f5ae: CALL 0x006b5240
    LocalizedString0062f540_dtor006b5240(text_scratch);

    // 0x0062f5b3..0x0062f5b8: POP EDI / POP ESI / ADD ESP,0x14 / RET
    // Bare RET: the caller owns all stack cleanup, and no stack argument was
    // ever pushed by this function.
}

}  // namespace dispatch_b05
}  // namespace openspore
