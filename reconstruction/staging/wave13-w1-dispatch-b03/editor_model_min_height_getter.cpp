#include "editor_model_min_height_getter.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// Reconstructed body of 0x004adb00 (17 bytes, 9 instructions, image base
// 0x00400000). See reconstruction/metadata/wave13-w1-dispatch-b03/004adb00.json.
//
// The whole body is: spill the ECX receiver to the incoming stack slot, reload
// it, push it into the x87 stack, and return. The receiver is never null-checked
// and no other field is touched.
float __thiscall editor_model_min_height_getter_004adb00(
    const OpaqueEditorModel* model) {
  // 0x004adb00 PUSH EBP / 0x004adb01 MOV EBP,ESP / 0x004adb03 PUSH ECX
  // 0x004adb04 MOV dword ptr [EBP - 0x4],ECX
  // The spill exists so the frame is symmetric; the value is reloaded at
  // 0x004adb07 and ECX is not read again afterwards.
  //
  // 0x004adb07 MOV EAX,dword ptr [EBP - 0x4]
  // 0x004adb0a FLD dword ptr [EAX + 0x40]
  //   A 32-bit float load into x87 ST0. The return travels in ST0, not XMM0
  //   and not EAX; every observed caller consumes it with FSTP.
  //
  // 0x004adb0d MOV ESP,EBP / 0x004adb0f POP EBP / 0x004adb10 RET
  //   A bare RET with no immediate, so the callee owns no stack cleanup and
  //   there is no stack argument to pop.
  volatile const float* const field = &model->mMinHeight;
  return *field;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
