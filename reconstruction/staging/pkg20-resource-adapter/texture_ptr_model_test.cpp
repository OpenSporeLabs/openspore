#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <vector>

#include "texture_ptr.hpp"

namespace {

using openspore::reconstruction::pkg20_resource_adapter::OpaqueTexture;
using openspore::reconstruction::pkg20_resource_adapter::TexturePtr;
using openspore::reconstruction::pkg20_resource_adapter::TexturePtr_Set;

enum class Operation {
  RhsAcquire,
  SlotStore,
  OldRelease,
  Clamp,
};

struct OperationTrace {
  void record(Operation operation) { operations.push_back(operation); }

  bool matches(std::initializer_list<Operation> expected) const {
    return operations == std::vector<Operation>(expected);
  }

  std::vector<Operation> operations;
};

OpaqueTexture make_texture(std::int32_t refcount) {
  OpaqueTexture texture{};
  texture.refcount = refcount;
  return texture;
}

void trace_texture_ptr_set(TexturePtr* slot, OpaqueTexture* rhs,
                           OperationTrace* trace) {
  OpaqueTexture* old = slot->value;
  if (old == rhs) {
    return;
  }
  if (rhs != nullptr) {
    trace->record(Operation::RhsAcquire);
    (void)__sync_fetch_and_add(&rhs->refcount, 1);
  }
  trace->record(Operation::SlotStore);
  slot->value = rhs;
  if (old == nullptr) {
    return;
  }
  trace->record(Operation::OldRelease);
  (void)__sync_fetch_and_add(&old->refcount, -1);
  const std::int32_t observed = __sync_fetch_and_add(&old->refcount, 0);
  if (observed < 1) {
    trace->record(Operation::Clamp);
    (void)__sync_fetch_and_add(&old->refcount, 1);
  }
}

void test_null_rhs_replaces_old_and_clamps() {
  OpaqueTexture old = make_texture(1);
  TexturePtr slot{&old};
  TexturePtr_Set(&slot, nullptr);
  assert(slot.value == nullptr);
  assert(old.refcount == 1);
}

void test_same_pointer_is_noop() {
  OpaqueTexture texture = make_texture(4);
  TexturePtr slot{&texture};
  OperationTrace trace;
  trace_texture_ptr_set(&slot, &texture, &trace);
  assert(trace.operations.empty());
  TexturePtr_Set(&slot, &texture);
  assert(slot.value == &texture);
  assert(texture.refcount == 4);
}

void test_distinct_pointer_replaces_and_clamps() {
  OpaqueTexture old = make_texture(1);
  OpaqueTexture rhs = make_texture(0);
  TexturePtr slot{&old};
  TexturePtr_Set(&slot, &rhs);
  assert(slot.value == &rhs);
  assert(old.refcount == 1);
  assert(rhs.refcount == 1);
}

void test_refcount_clamp_restores_one() {
  OpaqueTexture old = make_texture(1);
  OpaqueTexture rhs = make_texture(0);
  TexturePtr slot{&old};
  TexturePtr_Set(&slot, &rhs);
  assert(slot.value == &rhs);
  assert(old.refcount == 1);
  assert(rhs.refcount == 1);
}

void test_replacement_order_publishes_rhs_before_old_release() {
  OpaqueTexture old = make_texture(1);
  OpaqueTexture rhs = make_texture(2);
  TexturePtr slot{&old};
  OperationTrace trace;
  trace_texture_ptr_set(&slot, &rhs, &trace);
  assert(trace.matches({Operation::RhsAcquire, Operation::SlotStore,
                        Operation::OldRelease, Operation::Clamp}));
  assert(slot.value == &rhs);
  assert(old.refcount == 1);
  assert(rhs.refcount == 3);

  OpaqueTexture production_old = make_texture(1);
  OpaqueTexture production_rhs = make_texture(2);
  TexturePtr production_slot{&production_old};
  TexturePtr_Set(&production_slot, &production_rhs);
  assert(production_slot.value == &production_rhs);
  assert(production_old.refcount == 1);
  assert(production_rhs.refcount == 3);
}

}

int main() {
  test_null_rhs_replaces_old_and_clamps();
  test_same_pointer_is_noop();
  test_distinct_pointer_replaces_and_clamps();
  test_refcount_clamp_restores_one();
  test_replacement_order_publishes_rhs_before_old_release();
}
