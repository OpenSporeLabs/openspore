// Clean-room reconstruction of SporeApp.exe 0x0062f540 (sha256 25d42a7a...9d914e).
//
// Evidence: live Ghidra (decompile + disassembly + read_memory) on program SporeApp.exe.
// No proprietary EA source was consulted. Spore-ModAPI headers were read as
// *candidates only; nothing in them is asserted unless the observed body agrees.
//
// Every offset, immediate, branch polarity and call form below is transcribed from
// the disassembly listing; instruction addresses are given as proof comments.

#pragma once

#include <cstdint>

namespace openspore {
namespace dispatch_b05 {

// ---------------------------------------------------------------------------
// Opaque receiver.
//
// Only the three offsets this function actually touches are modelled. The
// enclosing class is *not* reconstructed: the SDK header
// (Spore/Editors/PlayModeBackgrounds.h) places mpPlayModeUI at +0x34,
// mCurrentPageIndex at +0x38 and mExtraPageCount ("total pages is this + 1") at
// +0x3c, which agrees with the observed accesses, but the SDK's own
// DeclareAddress comment for UpdatePageNumbers (0x62F520 / 0x62F570) does not
// land on 0x0062f540 and no vtable containing 0x0062f540 exists in .rdata/.data,
// so the class identity stays a candidate. The +0x3C "+1" reading comes straight
// from 0x0062f58b/0x0062f590/0x0062f591 and is independent of the SDK.
// ---------------------------------------------------------------------------
struct PlayModeBackgrounds0062f540 {
    std::uint32_t pad_0000[0x34 / 4];  // 0x00..0x33 : never read here
    void* field_34_play_mode_ui;       // 0x0062f550: MOV ECX,dword ptr [ESI + 0x34]
    std::int32_t field_38_page_index;  // 0x0062f57b: MOV EAX,dword ptr [ESI + 0x38]
    std::int32_t field_3c_page_count;  // 0x0062f588: MOV EDX,dword ptr [ESI + 0x3c]
};

// ---------------------------------------------------------------------------
// Opaque UTFWin::IWindow.
//
// Slot +0x80 is the only virtual reached. Spore/UTFWin/IWindow.h declares
//   /* 80h */ virtual void SetCaption(const char16_t* pCaption) = 0;
// and the same header declares /* 7Ch */ SetFlag(WindowFlags,bool) and
// /* 1Ch */ GetControlID(), both of which are observed at the *other* two
// callees of this function's neighbourhood (0x0062e600 calls slot +0x7c with
// (1,0)/(1,1) and 0x00634dc0 calls slot +0x1c). The slot-0x80 identity is
// therefore a strong candidate, not an asserted name.
// ---------------------------------------------------------------------------
struct IWindow0062f540 {
    void** vtable;  // 0x0062f594: MOV ESI,dword ptr [EDI] -> ESI+0x80 at 0x0062f59f
};

// ---------------------------------------------------------------------------
// Opaque argument table reached through the single global pointer 0x015f7cf4.
// Only +0x20 and +0x24 are written by this function. The 51 xrefs to that
// address (51 read/write references recorded by Ghidra) show sibling writers at
// +0x18, +0x1c, +0x28, +0x2c and +0x34, which is the signature of a shared
// localized-string substitution table. The concrete type is NOT established.
// ---------------------------------------------------------------------------
struct LocalizedArgTable0062f540 {
    std::uint32_t pad_0000[0x20 / 4];
    std::int32_t field_20;  // 0x0062f585: MOV dword ptr [ECX + 0x20],EAX
    std::int32_t field_24;  // 0x0062f591: MOV dword ptr [EAX + 0x24],EDX
};

// ---------------------------------------------------------------------------
// Opaque ports. Declared, never given bodies.
// ---------------------------------------------------------------------------

// 0x006b5060 - constructor of a 0x14-byte stack temporary (SUB ESP,0x14 at
// 0x0062f540, LEA ECX,[ESP+0x8] at 0x0062f547). Internally builds a
// "UI/SP::cString" (FUN_00f473a0(0x10,"UI/SP::cString",...) inside 0x006b55c0).
void LocalizedString0062f540_ctor006b5060(void* self);

// 0x006b5240 - destructor of the same 0x14-byte temporary (0x0062f5ae).
void LocalizedString0062f540_dtor006b5240(void* self);

// 0x006b54b0 - __thiscall, RET 0xc, so it consumes three stack dwords. It reads
// only the first two: 0x006b54ec MOV EBP,dword ptr [ESP + 0x20] (arg 1, the
// localization id) and 0x006b54fc CMP dword ptr [ESP + 0x24],-1 (arg 2, compared
// against the -1 "none" sentinel). The third pushed dword is never read.
// Returns bool in AL; the caller discards it.
bool LocalizedString0062f540_set_localized006b54b0(
    void* self, std::uint32_t localization_id, std::uint32_t alternate_id,
    std::uint32_t debug_tag_wide_string);

// 0x006b55c0 - __thiscall, returns the resolved text pointer in EAX.
const char16_t* LocalizedString0062f540_resolve006b55c0(void* self);

// 0x00634dc0 - __thiscall with ECX as a hidden receiver and one stack dword.
// 0x00634dc4 is `ADD ECX,0x14`, the MSVC this-adjustment into the sub-object that
// Spore/Editors/PlayModeUI.h documents as `/* 14h */ UTFWin::UILayout mMainLayout`.
// The body iterates a registry, calls slot +0x0c on each entry with the literal
// 0xeeee8218 (UTFWin::IWindow::TYPE in Spore/UTFWin/IWindow.h) and compares
// slot +0x1c (GetControlID) against the argument, falling back to slot +0xf0.
// This is the documented "Finds a window with the given control ID in the main
// PlayMode layout" operation; the SDK name FindWindowByID stays a candidate.
IWindow0062f540* PlayModeUI0062f540_find_window_by_id00634dc0(
    void* play_mode_ui, std::uint32_t control_id);

// IWindow vtable slot +0x80, called through EDX with ECX = the window.
void IWindow0062f540_vslot80_set_caption(const IWindow0062f540* self,
                                         const char16_t* caption);

// Global pointer to the shared localized-string argument table. Live read of
// 0x015f7cf4 returns 16 zero bytes, i.e. it is a .bss-style runtime-initialised
// pointer with no static initialiser. It is dereferenced WITHOUT a null check at
// 0x0062f585, so a non-null lookup result implies a non-null global.
extern LocalizedArgTable0062f540* const g_localized_arg_table_015f7cf4;

// Observed immediates.
// 0x0062f553 PUSH 0x47ed688 : the control id looked up in the PlayMode layout.
// 0x0062f56d PUSH 0x7518573e : the localization id handed to 0x006b54b0.
// 0x0062f568 PUSH 0x47ed777 : the alternate id (compared against -1 by callee).
// 0x0062f563 PUSH 0x13fe404 : pointer to the wide literal L"*BG Page Count*".
inline constexpr std::uint32_t kControlIdBgPageCount = 0x047ed688u;
inline constexpr std::uint32_t kLocalizationIdPageCountFormat = 0x7518573eu;
inline constexpr std::uint32_t kAlternateIdPageCountFormat = 0x047ed777u;
inline constexpr std::uint32_t kDebugTagBgPageCount = 0x013fe404u;

// ---------------------------------------------------------------------------
// Reconstructed body.
// ---------------------------------------------------------------------------

// 0x0062f540, 25 instructions, 0x79 bytes, .text.
// __thiscall, receiver in ECX, no stack arguments, void return, bare RET.
void PlayModeBackgrounds_0062f540_UpdatePageNumbers(
    PlayModeBackgrounds0062f540* self);

}  // namespace dispatch_b05
}  // namespace openspore
