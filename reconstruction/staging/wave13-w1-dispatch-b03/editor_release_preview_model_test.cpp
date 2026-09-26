#include "editor_release_preview_model.hpp"

#include <cstdio>

namespace {

using openspore::reconstruction::wave13_w1_dispatch_b03::OpaqueModel;

struct FakeModelWorld {
  void** vtable;
  int set_in_world_calls;
  int final_release_calls;
  const void* set_in_world_arg0;
  int set_in_world_arg1;
  const void* final_release_arg0;
  int final_release_arg1;
};

int __thiscall fake_set_in_world(void*, OpaqueModel* model, int visible) {
  auto* self = static_cast<FakeModelWorld*>(model->mpWorld);
  ++self->set_in_world_calls;
  self->set_in_world_arg0 = model;
  self->set_in_world_arg1 = visible;
  return 1;
}

void __thiscall fake_final_release(void*, OpaqueModel* model, int flag) {
  auto* self = static_cast<FakeModelWorld*>(model->mpWorld);
  ++self->final_release_calls;
  self->final_release_arg0 = model;
  self->final_release_arg1 = flag;
}

void* g_vtable[0x170 / 4 + 1] = {};

FakeModelWorld g_world = {g_vtable, 0, 0, nullptr, 0, nullptr, 0};

int failures = 0;

void expect(bool condition, const char* what) {
  if (!condition) {
    std::printf("FAIL %s\n", what);
    ++failures;
  }
}

}  // namespace

int main() {
  using namespace openspore::reconstruction::wave13_w1_dispatch_b03;

  // The reconstruction reads its slots out of Model::mpWorld, so the fake
  // world needs a real vtable with the entries at +0x16c and +0x170.
  g_vtable[0x16c / 4] = reinterpret_cast<void*>(&fake_set_in_world);
  g_vtable[0x170 / 4] = reinterpret_cast<void*>(&fake_final_release);
  g_world.vtable = g_vtable;

  // Case 1: null editor slot. 0x005772bb JZ -> return with no side effect.
  {
    OpaqueEditor editor = {};
    editor.field_F0_ModelPtr = nullptr;
    g_world.set_in_world_calls = 0;
    g_world.final_release_calls = 0;
    editor_release_preview_model_005772b0(&editor);
    expect(g_world.set_in_world_calls == 0, "null slot: no SetInWorld");
    expect(g_world.final_release_calls == 0, "null slot: no FinalRelease");
  }

  // Case 2: refcount > 1. 0x005772e6 JLE not taken -> decrement and return,
  // no FinalRelease, and the editor slot is cleared.
  {
    OpaqueModel model = {};
    OpaqueEditor editor = {};
    model.mpWorld = &g_world;
    model.mnRefCount = 3;
    model.mFlags = static_cast<int>(0x80000000u);
    editor.field_F0_ModelPtr = &model;
    g_world.set_in_world_calls = 0;
    g_world.final_release_calls = 0;
    editor_release_preview_model_005772b0(&editor);
    expect(g_world.set_in_world_calls == 1, "refcount>1: one SetInWorld");
    expect(g_world.set_in_world_arg0 == &model, "SetInWorld gets the model");
    expect(g_world.set_in_world_arg1 == 0, "SetInWorld visible arg is false");
    expect(model.mnRefCount == 2, "refcount>1: decremented");
    expect(editor.field_F0_ModelPtr == nullptr, "refcount>1: slot cleared");
    expect(g_world.final_release_calls == 0, "refcount>1: no FinalRelease");
  }

  // Case 3: refcount == 1 -> JLE taken -> FinalRelease with bit 31 of mFlags.
  {
    OpaqueModel model = {};
    OpaqueEditor editor = {};
    model.mpWorld = &g_world;
    model.mnRefCount = 1;
    model.mFlags = static_cast<int>(0x80000001u);
    editor.field_F0_ModelPtr = &model;
    g_world.set_in_world_calls = 0;
    g_world.final_release_calls = 0;
    editor_release_preview_model_005772b0(&editor);
    expect(g_world.final_release_calls == 1, "refcount==1: one FinalRelease");
    expect(g_world.final_release_arg0 == &model, "FinalRelease gets the model");
    expect(g_world.final_release_arg1 == 1,
           "FinalRelease bool is bit 31 of mFlags");
    expect(editor.field_F0_ModelPtr == nullptr, "refcount==1: slot cleared");
  }

  // Case 4: refcount == 1 with bit 31 clear -> the bool argument is 0.
  {
    OpaqueModel model = {};
    OpaqueEditor editor = {};
    model.mpWorld = &g_world;
    model.mnRefCount = 1;
    model.mFlags = 0x7fffffff;
    editor.field_F0_ModelPtr = &model;
    g_world.set_in_world_calls = 0;
    g_world.final_release_calls = 0;
    editor_release_preview_model_005772b0(&editor);
    expect(g_world.final_release_calls == 1, "refcount==1: one FinalRelease");
    expect(g_world.final_release_arg1 == 0,
           "FinalRelease bool is 0 when bit 31 of mFlags is clear");
  }

  // Case 5: refcount == 0 also takes the JLE branch, because CMP ECX,1 / JLE
  // is a signed <= comparison, so FinalRelease runs with no decrement.
  {
    OpaqueModel model = {};
    OpaqueEditor editor = {};
    model.mpWorld = &g_world;
    model.mnRefCount = 0;
    model.mFlags = 0;
    editor.field_F0_ModelPtr = &model;
    g_world.set_in_world_calls = 0;
    g_world.final_release_calls = 0;
    editor_release_preview_model_005772b0(&editor);
    expect(g_world.final_release_calls == 1, "refcount==0: FinalRelease runs");
    expect(model.mnRefCount == 0, "refcount==0: no decrement happened");
  }

  if (failures == 0) {
    std::printf("005772b0 model test: all cases passed\n");
    return 0;
  }
  std::printf("005772b0 model test: %d failure(s)\n", failures);
  return 1;
}
