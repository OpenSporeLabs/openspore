#include "editor_release_preview_model.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

namespace {

using Bool8 = unsigned char;

// 0x005772b3: MOV EAX,dword ptr [ESI + 0xf0]
OpaqueModel* load_editor_model(OpaqueEditor* editor) {
  return static_cast<OpaqueModel*>(editor->field_F0_ModelPtr);
}

// 0x005772bd/0x005772bf: MOV ECX,[EAX] ; MOV EDX,[ECX]
// The receiver of both virtual calls is Model::mpWorld, not the Model itself.
OpaqueModelWorld* load_model_world(OpaqueModel* model) {
  return static_cast<OpaqueModelWorld*>(model->mpWorld);
}

template <typename Slot>
Slot load_slot(OpaqueModelWorld* world, unsigned int offset) {
  auto* const address = reinterpret_cast<const unsigned char*>(world->vtable) +
                        offset;
  Slot slot;
  __builtin_memcpy(&slot, address, sizeof(slot));
  return slot;
}

}  // namespace

// Reconstructed body of 0x005772b0 (92 bytes, 36 instructions, image base
// 0x00400000). Operation order, field offsets, constants, branch polarity,
// receiver and return semantics all come from the disassembly; see
// reconstruction/metadata/wave13-w1-dispatch-b03/005772b0.json.
//
// 0x0040f360 is the out-of-line twin of the tail half of this body: the same
// mnRefCount compare, the same (mFlags >> 31) & 1 bool, the same 0x170
// dispatch. It differs in that it returns the new refcount in EAX, while this
// body additionally performs the +0x16c SetInWorld call and clears the editor
// slot before releasing.
void __thiscall editor_release_preview_model_005772b0(OpaqueEditor* editor) {
  OpaqueModel* model = load_editor_model(editor);

  // 0x005772b9: TEST EAX,EAX ; 0x005772bb: JZ 0x0057730a
  if (model == nullptr) {
    return;
  }

  // 0x005772c1 PUSH 0x0 / 0x005772c3 PUSH EAX / 0x005772c4 MOV EAX,[EDX+0x16c]
  // 0x005772ca CALL EAX
  // IModelWorld::SetInWorld(model, /*visible=*/false); result discarded.
  OpaqueModelWorld* const world = load_model_world(model);
  const ModelWorldSetInWorldSlot set_in_world =
      load_slot<ModelWorldSetInWorldSlot>(world, 0x16c);
  set_in_world(world, model, 0);

  // 0x005772cc: MOV EAX,dword ptr [ESI + 0xf0]
  // The slot is reloaded because SetInWorld is allowed to clear it.
  model = load_editor_model(editor);

  // 0x005772d2: TEST EAX,EAX ; 0x005772d4: JZ 0x0057730a
  if (model == nullptr) {
    return;
  }

  // 0x005772d6: MOV dword ptr [ESI + 0xf0],0x0
  editor->field_F0_ModelPtr = nullptr;

  // 0x005772e0 MOV ECX,[EAX+0x40] / 0x005772e3 CMP ECX,0x1 / 0x005772e6 JLE
  // 0x005772e8 DEC ECX / 0x005772e9 MOV [EAX+0x40],ECX / 0x005772ec POP ESI
  // 0x005772ed RET
  if (model->mnRefCount > 1) {
    --model->mnRefCount;
    return;
  }

  // 0x005772f2 PUSH EBX is the only EBX touch and the matching POP EBX is at
  // 0x00577309, so EBX is saved on the FinalRelease path alone.
  // 0x005772f3 MOV EBX,[EAX+0x4] / 0x005772f6 SHR EBX,0x1f / 0x005772f9 AND
  // BL,0x1 / 0x005772fc MOVZX ESI,BL -> bool from bit 31 of Model::mFlags.
  // 0x00577301 MOV EAX,[EDX+0x170] / 0x00577307 CALL EAX
  // IModelWorld::FinalRelease(model, (mFlags >> 31) & 1);
  const Bool8 release_flag =
      static_cast<Bool8>((static_cast<unsigned int>(model->mFlags) >> 31) & 1u);
  const ModelWorldFinalReleaseSlot final_release =
      load_slot<ModelWorldFinalReleaseSlot>(world, 0x170);
  final_release(world, model, release_flag);
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
