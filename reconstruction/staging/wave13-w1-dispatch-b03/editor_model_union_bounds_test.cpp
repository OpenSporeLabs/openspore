#include "editor_model_union_bounds.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

namespace {

using openspore::reconstruction::wave13_w1_dispatch_b03::BoundingBox;
using openspore::reconstruction::wave13_w1_dispatch_b03::EditorRigblockPort;
using openspore::reconstruction::wave13_w1_dispatch_b03::EditorRigblockPtrSlot;
using openspore::reconstruction::wave13_w1_dispatch_b03::OpaqueEditorModel;

struct Rigblock {
  float lower[3];
  float upper[3];
  int hidden_result;
  int bounds_calls;
};

std::vector<Rigblock*> g_rigblocks;
int g_union_calls = 0;
int g_empty_calls = 0;
int g_copy_calls = 0;
float g_last_written[6];

void reset() {
  g_union_calls = 0;
  g_empty_calls = 0;
  g_copy_calls = 0;
  std::memset(g_last_written, 0, sizeof(g_last_written));
}

int failures = 0;

void expect(bool condition, const char* what) {
  if (!condition) {
    std::printf("FAIL %s\n", what);
    ++failures;
  }
}

void expect_near(float got, float want, const char* what) {
  if (got != want) {
    std::printf("FAIL %s: got %f want %f\n", what, static_cast<double>(got),
                static_cast<double>(want));
    ++failures;
  }
}

}  // namespace

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {
namespace unresolved_ports {

void __fastcall bounding_box_make_empty(BoundingBox* box) {
  ++g_empty_calls;
  for (int i = 0; i < 3; ++i) {
    box->lower[i] = 3.402823466e+38f;
    box->upper[i] = -3.402823466e+38f;
  }
}

BoundingBox* __thiscall rigblock_get_bounds(EditorRigblockPort* port,
                                            BoundingBox* out, int, char, char) {
  auto* const self = reinterpret_cast<Rigblock*>(port);
  ++self->bounds_calls;
  *out = *reinterpret_cast<const BoundingBox*>(&self->lower[0]);
  return out;
}

void __thiscall bounding_box_union_in_place(BoundingBox* acc,
                                             const BoundingBox* other) {
  ++g_union_calls;
  if (acc->lower[0] > acc->upper[0]) {
    *acc = *other;
    return;
  }
  for (int i = 0; i < 3; ++i) {
    if (other->lower[i] < acc->lower[i]) {
      acc->lower[i] = other->lower[i];
    }
    if (other->upper[i] > acc->upper[i]) {
      acc->upper[i] = other->upper[i];
    }
  }
}

void* __thiscall copy_six_dwords(void* dst, const void* src) {
  ++g_copy_calls;
  std::memcpy(dst, src, 24);
  std::memcpy(g_last_written, src, 24);
  return dst;
}

unsigned char __fastcall rigblock_is_hidden_or_filtered(
    EditorRigblockPort* port) {
  return static_cast<unsigned char>(
      reinterpret_cast<Rigblock*>(port)->hidden_result);
}

}  // namespace unresolved_ports
}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03

int main() {
  using namespace openspore::reconstruction::wave13_w1_dispatch_b03;

  Rigblock blocks[4];
  auto make = [](float lx, float ly, float lz, float ux, float uy, float uz,
                 int hidden) {
    Rigblock b;
    b.lower[0] = lx;
    b.lower[1] = ly;
    b.lower[2] = lz;
    b.upper[0] = ux;
    b.upper[1] = uy;
    b.upper[2] = uz;
    b.hidden_result = hidden;
    b.bounds_calls = 0;
    return b;
  };

  // The vector holds one intrusive pointer per element, so the storage the
  // body indexes is an array of pointers, not an array of rigblocks.
  EditorRigblockPtrSlot slots[4];
  std::memset(slots, 0, sizeof(slots));
  slots[0].ptr = reinterpret_cast<EditorRigblockPort*>(&blocks[0]);
  slots[1].ptr = reinterpret_cast<EditorRigblockPort*>(&blocks[1]);
  slots[2].ptr = reinterpret_cast<EditorRigblockPort*>(&blocks[2]);
  slots[3].ptr = reinterpret_cast<EditorRigblockPort*>(&blocks[3]);

  OpaqueEditorModel model;
  std::memset(&model, 0, sizeof(model));
  BoundingBox out;
  std::memset(&out, 0, sizeof(out));

  // Case 1: empty rigblock list. 0x004ad599 JBE is taken, so the out parameter
  // receives the empty-box sentinel and the return value is the out parameter.
  model.mRigblocks.begin = nullptr;
  model.mRigblocks.end = nullptr;
  reset();
  auto* const r1 = editor_model_union_bounds_004ad550(&model, &out, 0);
  expect(r1 == &out, "empty list: returns the out parameter");
  expect(g_empty_calls == 2, "empty list: the accumulator is emptied twice");
  expect(g_copy_calls == 1, "empty list: exactly one store to the out box");
  expect_near(out.lower[0], 3.402823466e+38f,
              "empty list: lower is +FLT_MAX, not zero");
  expect_near(out.upper[0], -3.402823466e+38f,
              "empty list: upper is -FLT_MAX");

  // Case 2: three rigblocks, filter clear. Element 0 seeds, 1 and 2 are unioned.
  blocks[0] = make(0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0);
  blocks[1] = make(-1.f, 0.f, 0.f, 0.5f, 2.f, 1.f, 0);
  blocks[2] = make(0.f, -3.f, 0.f, 1.f, 1.f, 4.f, 0);
  model.mRigblocks.begin = reinterpret_cast<unsigned char*>(&slots[0]);
  model.mRigblocks.end = reinterpret_cast<unsigned char*>(&slots[0]) + 3 * 4;
  reset();
  auto* const r2 = editor_model_union_bounds_004ad550(&model, &out, 0);
  expect(r2 == &out, "three blocks: returns the out parameter");
  expect(blocks[0].bounds_calls == 1 && blocks[1].bounds_calls == 1 &&
             blocks[2].bounds_calls == 1,
         "three blocks: every element's bounds are computed exactly once");
  expect(g_union_calls == 2, "three blocks: two unions, for elements 1 and 2");
  expect_near(out.lower[0], -1.f, "union lower.x");
  expect_near(out.lower[1], -3.f, "union lower.y");
  expect_near(out.lower[2], 0.f, "union lower.z");
  expect_near(out.upper[0], 1.f, "union upper.x");
  expect_near(out.upper[1], 2.f, "union upper.y");
  expect_near(out.upper[2], 4.f, "union upper.z");

  // Case 3: filter non-zero. Element 0 is still read unconditionally; only
  // elements 1..n-1 are gated.
  blocks[0] = make(0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0);
  blocks[1] = make(-1.f, 0.f, 0.f, 0.5f, 2.f, 1.f, 0);  // filtered out
  blocks[2] = make(0.f, -3.f, 0.f, 1.f, 1.f, 4.f, 1);    // kept
  reset();
  editor_model_union_bounds_004ad550(&model, &out, 1);
  expect(blocks[0].bounds_calls == 1,
         "filtered: element 0 is read even when the filter is on");
  expect(blocks[1].bounds_calls == 0,
         "filtered: element 1 skipped, bounds never computed");
  expect(blocks[2].bounds_calls == 1, "filtered: element 2 kept");
  expect(g_union_calls == 1, "filtered: exactly one union");
  expect_near(out.lower[0], 0.f,
              "filtered: the skipped element did not widen the box");
  expect_near(out.upper[2], 4.f, "filtered: the kept element did widen it");

  // Case 4: a single rigblock. The loop body never runs.
  blocks[3] = make(9.f, 9.f, 9.f, 9.f, 9.f, 9.f, 1);
  blocks[0].bounds_calls = 0;
  model.mRigblocks.end = reinterpret_cast<unsigned char*>(&slots[0]) + 4;
  reset();
  editor_model_union_bounds_004ad550(&model, &out, 0);
  expect(g_union_calls == 0, "one block: no unions");
  expect(blocks[0].bounds_calls == 1, "one block: bounds read once");
  expect(blocks[3].bounds_calls == 0,
         "one block: the trailing element is never touched");
  expect_near(out.lower[0], 0.f, "one block: lower comes from element 0");
  expect_near(out.upper[2], 1.f, "one block: the box is element 0's own box");

  if (failures == 0) {
    std::printf("004ad550 model test: all cases passed\n");
    return 0;
  }
  std::printf("004ad550 model test: %d failure(s)\n", failures);
  return 1;
}
