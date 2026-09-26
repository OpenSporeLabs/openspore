#include "editor_ui_005dc310.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {

// 0x005dc310 -- 39 bytes, 17 instructions, read live.
//
//   0x005dc310  56           push esi
//   0x005dc311  57           push edi
//   0x005dc312  8b7c24 0c    mov  edi, dword ptr [esp + 0xc]
//   0x005dc316  8be1         mov  esi, ecx
//   0x005dc318  6a01         push 0x1
//   0x005dc31a  57           push edi
//   0x005dc31b  8d7608 14    lea  ecx, [esi + 0x14]
//   0x005dc31e  e8965cf8ff   call 0x008105b0
//   0x005dc323  85c0         test eax, eax
//   0x005dc325  750b         jnz  0x005dc332
//   0x005dc327  6a01         push 0x1
//   0x005dc329  57           push edi
//   0x005dc32a  8d7608 2c    lea  ecx, [esi + 0x2c]
//   0x005dc32d  e87e5cf8ff   call 0x008105b0
//   0x005dc332  5f           pop  edi
//   0x005dc333  5e           pop  esi
//   0x005dc334  c2 0400      ret  0x4
//
// Live bytes: 56 57 8b 7c 24 0c 8b e1 6a 01 57 8d 76 08 14 e8 96 5c
//             f8 ff 85 c0 75 0b 6a 01 57 8d 76 08 2c e8 7e 5c f8 ff
//             5f 5e c2 04 00.
//
// The decompiler types this `void`, which is wrong. Neither POP touches EAX,
// so the value in EAX on exit is the return of whichever 0x008105b0 call ran
// last, and every observed caller reads it:
//
//   0x005ddaba  e851e8ffff  call 0x005dc310
//   0x005ddabf  85c0        test eax, eax
//   0x005ddac1  740d        jz   0x005ddad0
//   0x005ddac3  8b10        mov  edx, dword ptr [eax]
//   0x005ddac9  8b427c      mov  eax, dword ptr [edx + 0x7c]
//   0x005ddace  ffd0        call eax            ; vtable slot +0x7c, (1, 1)
//
// so the port returns a pointer and the reconstruction returns one.
//
// Receiver provenance: 0x0058c7db in Editors::cEditor::Update does
// `mov ecx, dword ptr [esi + 0x78]` before the call, and the ModAPI header
// Spore/Editors/EditorUI.h records cEditor +0x78 as `mpEditorUI`. The SDK
// records EditorUI +0x14 as `mMainUI` and +0x2c as `mSharedUI`, both
// UTFWin::UILayout, and UILayout +0x14 as `mpLayoutObjects`. 0x008105b0 is
// exactly `if (layout->mpLayoutObjects) return scan(...) else return 0`, and
// 0x00810200 walks a pointer array comparing `vfunc +0x1c()` against the id
// and, when the flag is set, returning `vfunc +0xf0(id, 1)`, after calling
// `vfunc +0xc(0xEEEE8218)`. 0xEEEE8218 is `UTFWin::IWindow::TYPE` in
// Spore/UTFWin/IWindow.h. The two-shape lookup and the always-1 flag therefore
// match `UILayout::FindWindowByID(controlID, /*bRecursive=*/true)`, and the
// `flag` argument is dropped on the floor by the second call's result. The
// SDK name is recorded as a correspondence, not as this function's identity:
// the receiver is the EditorUI aggregate, not a UILayout.

extern "C" Opaque5dc310Window* __thiscall FUN_005dc310_reconstruct(
    void* editor_ui,
    std::uint32_t control_id) {
  auto* self = static_cast<std::uint8_t*>(editor_ui);

  // 0x005dc31b: first candidate is the sub-object at +0x14.
  Opaque5dc310Window* found = port_008105b0_find_in_layout(
      reinterpret_cast<Opaque5dc310Layout*>(self + 0x14), control_id, 1u);

  // 0x005dc323..0x005dc325: the second lookup runs only on a null answer.
  if (found == nullptr) {
    // 0x005dc32a: fallback is the sub-object at +0x2c. The 0x1 pushed at
    // 0x005dc327 is the same always-set flag as in the first call.
    found = port_008105b0_find_in_layout(
        reinterpret_cast<Opaque5dc310Layout*>(self + 0x2c), control_id, 1u);
  }

  // 0x005dc332..0x005dc334: the saved registers come back, the caller pops the
  // argument, and EAX is never written on the way out.
  return found;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
