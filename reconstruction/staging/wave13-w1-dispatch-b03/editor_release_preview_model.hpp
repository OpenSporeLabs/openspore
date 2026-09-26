#pragma once

#include <cstddef>

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// The receiver is an Editors::cEditor. Only one member slot is touched, so the
// type stays opaque instead of inventing the full cEditor layout: the leading
// pad reproduces the observed slot offset and nothing else is claimed.
// Observed: 0x005772b3 reads dword [ECX + 0xf0] and 0x005772d6 writes it.
struct OpaqueEditor {
  unsigned char pad_000_F0[0xf0];
  void* field_F0_ModelPtr;  // +0xf0, Model*
};

// The released object is a Spore::Graphics::Model. Only the fields this body
// reads are declared; the gaps reproduce the observed offsets and no other
// Model member is claimed here.
// Offsets: Spore/Graphics/Model.h in the Spore-ModAPI SDK.
struct OpaqueModel {
  void* mpWorld;             // +0x00 IModelWorld*
  int mFlags;                // +0x04
  unsigned char pad_008_040[0x40 - 0x08];
  int mnRefCount;            // +0x40
  int mGroupFlags[2];        // +0x44
  unsigned char mColor[12];  // +0x4c Math::ColorRGBA
};

// The virtual receiver. Only the vtable pointer is known; the world object
// itself is not reconstructed.
struct OpaqueModelWorld {
  void** vtable;
};

// Spore/Graphics/IModelWorld.h declares:
//   /* 16Ch */ virtual bool SetInWorld(Model* model, bool visible) = 0;
//   /* 170h */ virtual void FinalRelease(Model* model, bool) = 0;
// Both match the arg counts and the 0x16c / 0x170 slot loads observed at
// 0x005772c4 and 0x00577301. Spelled as explicit thiscall ports because the
// observed form is `PUSH args; MOV EAX,[EDX+slot]; CALL EAX` with ECX already
// holding the world.
using ModelWorldSetInWorldSlot =
    int(__thiscall*)(OpaqueModelWorld*, OpaqueModel*, int);
using ModelWorldFinalReleaseSlot =
    void(__thiscall*)(OpaqueModelWorld*, OpaqueModel*, int);

static_assert(sizeof(void*) == 4, "the target is x86-32");
static_assert(offsetof(OpaqueEditor, field_F0_ModelPtr) == 0xf0,
              "the observed Model* member lives at +0xf0");
static_assert(offsetof(OpaqueModel, mFlags) == 0x04,
              "Model::mFlags is read at +0x04 for the FinalRelease bool");
static_assert(offsetof(OpaqueModel, mnRefCount) == 0x40,
              "Model::mnRefCount is compared and decremented at +0x40");
static_assert(offsetof(OpaqueModel, mGroupFlags) == 0x44,
              "Model::mGroupFlags starts at +0x44");
static_assert(offsetof(OpaqueModel, mColor) == 0x4c,
              "Model::mColor starts at +0x4c");
static_assert(sizeof(ModelWorldSetInWorldSlot) == 4,
              "an x86-32 virtual slot holds one 32-bit function pointer");
static_assert(sizeof(ModelWorldFinalReleaseSlot) == 4,
              "an x86-32 virtual slot holds one 32-bit function pointer");

// 0x005772b0: cEditor member, ECX receiver, bare RET, no stack arguments.
void __thiscall editor_release_preview_model_005772b0(OpaqueEditor*);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
