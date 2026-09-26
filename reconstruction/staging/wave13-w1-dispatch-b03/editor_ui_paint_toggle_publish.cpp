#include "editor_ui_paint_toggle_publish.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// Byte is the 0/1 flag type: the observed stores are MOV byte ptr ...,0x1 and
// MOV byte ptr ...,BL, and both consumers reload the byte before widening it to
// a dword for the virtual call.
using Byte = unsigned char;

namespace {

using unresolved_ports::classify_paint_availability;
using unresolved_ports::editor_ui_publish_undo_state_005dc800;
using unresolved_ports::layout_find_element;
using unresolved_ports::provider_set_toggle;

// 0x005dd7ec PUSH 0x1 / 0x005dd7ec PUSH 0x5b6e484 - the element id and mode
// are the same in both lookup attempts; only the layout context differs.
constexpr unsigned int kPaintToggleElementId = 0x5b6e484u;
constexpr int kLookupMode = 1;

// The jump table at 0x005dd840, read live: five dwords, entries 0, 1 and 2 all
// pointing at 0x005dd7d4 and entries 3 and 4 all pointing at 0x005dd7ce.
// 0x005dd7d4 is `MOV byte ptr [ESP+0xc],0x1` and 0x005dd7ce is
// `MOV byte ptr [ESP+0xc],BL` with BL already zeroed at 0x005dd7b0.
// Both fall into 0x005dd7d9, which is `MOV byte ptr [ESP+0x10],0x1`.
//
// So: cases 0..2 set the second flag, cases 3..4 leave it zero, and ALL FIVE
// cases set the first flag. The bounds check that precedes the table is
// 0x005dd7c2 CMP EAX,0x4 / 0x005dd7c5 JA, an UNSIGNED comparison, so a
// negative classification also falls through to the no-op.
void apply_switch(Byte* first_flag, Byte* second_flag, int mode) {
  if (static_cast<unsigned int>(mode) > 4u) {
    return;
  }
  *second_flag = (mode <= 2) ? Byte{1} : Byte{0};
  *first_flag = Byte{1};
}

}  // namespace

// Reconstructed body of 0x005dd7a0 (159 bytes, 55 instructions, image base
// 0x00400000). See reconstruction/metadata/wave13-w1-dispatch-b03/005dd7a0.json.
//
// Order of operations, from the disassembly:
//   1. classify the paint state through [ui + 0x5c]
//   2. both flags start at zero
//   3. if ui->field_102 and the classification is 0..4, apply the jump table
//   4. if ui->field_D1 is zero, clear the SECOND flag only
//   5. resolve element 0x5b6e484 from mMainUI, falling back to mSharedUI
//   6. call vtable slot +0x7c with (1, first_flag) and then (2, second_flag)
//   7. tail-transfer to 0x005dc800 with the same receiver
void __thiscall editor_ui_publish_paint_toggle_005dd7a0(OpaqueEditorUi* ui) {
  // 0x005dd7a5 MOV ESI,ECX / 0x005dd7a7 MOV ECX,[ESI+0x5c] / 0x005dd7ab
  // CALL 0x0057aaa0 - the classification is asked of the +0x5c pointer, which
  // the SDK names cEditor* mpEditor.
  const int mode = classify_paint_availability(ui->mpEditor);

  // 0x005dd7b0 XOR EBX,EBX / 0x005dd7b2 MOV byte [ESP+0x10],BL /
  // 0x005dd7b6 MOV byte [ESP+0xc],BL - both flags start at zero.
  Byte first_flag = 0;
  Byte second_flag = 0;

  // 0x005dd7ba CMP byte ptr [ESI+0x102],BL / 0x005dd7c0 JZ 0x005dd7de
  if (ui->field_102 != 0) {
    // 0x005dd7c2 CMP EAX,0x4 / 0x005dd7c5 JA 0x005dd7de /
    // 0x005dd7c7 JMP dword ptr [EAX*0x4 + 0x5dd840]
    apply_switch(&first_flag, &second_flag, mode);
  }

  // 0x005dd7de CMP byte ptr [ESI+0xd1],BL / 0x005dd7e4 JNZ 0x005dd7ea /
  // 0x005dd7e6 MOV byte [ESP+0xc],BL.
  // A zero here clears the second flag. It can never set it, so field_D1 is a
  // one-way inhibit rather than a second source of truth.
  if (ui->field_D1 == 0) {
    second_flag = 0;
  }

  // 0x005dd7ea PUSH 0x1 / 0x005dd7ec PUSH 0x5b6e484 / 0x005dd7f1 LEA ECX,
  // [ESI+0x14] / 0x005dd7f4 CALL 0x008105b0
  void* provider =
      layout_find_element(&ui->mMainUI, kPaintToggleElementId, kLookupMode);

  // 0x005dd7f9 CMP EAX,EBX / 0x005dd7fb JNZ 0x005dd80c
  if (provider == nullptr) {
    // 0x005dd7fd PUSH 0x1 / 0x005dd7ff PUSH 0x5b6e484 / 0x005dd804 LEA ECX,
    // [ESI+0x2c] / 0x005dd807 CALL 0x008105b0 - the fallback layout.
    provider =
        layout_find_element(&ui->mSharedUI, kPaintToggleElementId, kLookupMode);
  }

  // 0x005dd80c MOV EDI,EAX / 0x005dd80e CMP EDI,EBX / 0x005dd810 JZ 0x005dd832
  if (provider != nullptr) {
    // 0x005dd812 MOV ECX,[ESP+0x10] / 0x005dd816 MOV EAX,[EDI] /
    // 0x005dd818 MOV EDX,[EAX+0x7c] / 0x005dd81b PUSH ECX / 0x005dd81c
    // PUSH 0x1 / 0x005dd81e MOV ECX,EDI / 0x005dd820 CALL EDX
    provider_set_toggle(provider, 1, first_flag);

    // 0x005dd822..0x005dd830: the same slot again with selector 2 and the
    // second flag. Both calls are unconditional once a provider exists, and
    // neither return value is examined.
    provider_set_toggle(provider, 2, second_flag);
  }

  // 0x005dd832 POP EDI / 0x005dd833 MOV ECX,ESI / POP ESI / POP EBX /
  // ADD ESP,0x8 / 0x005dd83a JMP 0x005dc800.
  // A tail transfer, not a call: the epilogue runs first and the receiver is
  // reloaded into ECX immediately before the jump, so the callee-clean
  // convention carries over and no return address is left behind.
  editor_ui_publish_undo_state_005dc800(ui);
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
