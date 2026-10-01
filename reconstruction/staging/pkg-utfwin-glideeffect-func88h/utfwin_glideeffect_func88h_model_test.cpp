#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "utfwin_glideeffect_func88h.hpp"

namespace openspore::reconstruction::pkg_utfwin_glideeffect_func88h {
namespace model {

enum class Kind : std::uint8_t {
  scalar_deleting_0096ffd0,
  vector_deleting_0096ff20,
};

struct Event {
  Kind kind;
  Opaque object;
  Opaque flag;
  Opaque result;
};

std::array<Event, 8> events{};
std::size_t event_count;

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

void add(Kind kind, Opaque object, Opaque flag, Opaque result) {
  assert(event_count < events.size());
  events[event_count++] = Event{kind, object, flag, result};
}

void reset() { event_count = 0; }

}

}

using namespace openspore::reconstruction::pkg_utfwin_glideeffect_func88h;
using namespace openspore::reconstruction::pkg_utfwin_glideeffect_func88h::
    model;

// The tail target 0x0096FFD0 is not this target, so the model test supplies
// the oracle. It reproduces the two facts the reconstruction depends on: the
// receiver it observes is 0x0C below the receiver the thunk was handed, and
// exactly one stack word arrives, of which only bit 0 is tested.
extern "C" Opaque PKG_G8_THISCALL
pkg_g8_re_0096ffd0(GlideEffect* object, std::uint32_t deleting_flag) {
  const Opaque freed =
      (deleting_flag & kFunc88hConstants.delete_flag_mask) != 0;
  add(Kind::scalar_deleting_0096ffd0, pointer_word(object), deleting_flag,
      freed);
  return pointer_word(object);
}

extern "C" Opaque PKG_G8_THISCALL
pkg_g8_re_0096ff20(GlideEffect* object, std::uint32_t vector_delete_flag) {
  add(Kind::vector_deleting_0096ff20, pointer_word(object), vector_delete_flag,
      0x00efffbcu);
  return pointer_word(object);
}

namespace {

// The receiver the thunk is handed points at the subobject that lives 0x0C
// bytes above the most-derived object.
alignas(4) std::uint8_t object_storage[sizeof(GlideEffect) + 0x0c] = {};
GlideEffect* most_derived() {
  return reinterpret_cast<GlideEffect*>(object_storage);
}
GlideEffectBiStateSubobject* subobject() {
  return reinterpret_cast<GlideEffectBiStateSubobject*>(object_storage + 0x0c);
}

void test_abi_record() {
  assert(kFunc88hAbi.receiver_register == -1);
  assert(kFunc88hAbi.receiver_shift_bytes == 0x0c);
  assert(kFunc88hAbi.ordinary_stack_words == 1);
  assert(kFunc88hAbi.stack_cleanup_bytes == 4);
  assert(std::strcmp(kFunc88hAbi.return_type, "void") == 0);
}

void test_constants_match_listing() {
  assert(kFunc88hConstants.receiver_adjustment == 0x0cu);
  assert(kFunc88hConstants.tail_target == 0x0096ffd0u);
  assert(kFunc88hConstants.body_end_inclusive == 0x0096ff77u);
  assert(kFunc88hConstants.int3_pad_end == 0x0096ff7fu);
  assert(kFunc88hConstants.sole_data_xref == 0x0144258cu);
  assert(kFunc88hConstants.vtable_run_base == 0x01442584u);
  assert(kFunc88hConstants.dtor_primary_vtable == 0x014425d8u);
  assert(kFunc88hConstants.dtor_layout_vtable == 0x014425c0u);
  assert(kFunc88hConstants.dtor_bistate_vtable == 0x01442584u);
  assert(kFunc88hConstants.dtor_field_60_value == 0x013eb938u);
  assert(kFunc88hConstants.delete_flag_mask == 0x01u);
  assert(kFunc88hConstants.receiver_adjustment == kFunc88hReceiverAdjustment);
  assert(kFunc88hConstants.sole_data_xref ==
         kFunc88hConstants.vtable_run_base + 0x08u);
  assert(kFunc88hConstants.dtor_bistate_vtable ==
         kFunc88hConstants.vtable_run_base);
}

void test_vtable_run_holds_this_target() {
  assert(kGlideEffectVTableRun.slot_08 == 0x0096ff70u);
  assert(kGlideEffectVTableRun.slot_0c == 0x0096ff90u);
  assert(offsetof(GlideEffectVTableRun, slot_08) == 0x08);
}

// The receiver the tail target observes must be the most-derived object, i.e.
// exactly 0x0C below the pointer handed to the thunk.
void test_receiver_is_adjusted_by_minus_0x0c() {
  reset();
  func88h_0096ff70(subobject(), 0u);
  assert(event_count == 1);
  assert(events[0].kind == Kind::scalar_deleting_0096ffd0);
  assert(events[0].object == pointer_word(most_derived()));
  assert(events[0].object ==
         pointer_word(subobject()) - kFunc88hConstants.receiver_adjustment);
  assert(events[0].flag == 0u);
}

// Exactly one stack word is forwarded, unmodified.
void test_single_stack_word_is_forwarded() {
  const std::uint32_t flags[] = {0x00000000u, 0x00000001u, 0x00000004u,
                                 0x80000000u};
  for (const std::uint32_t flag : flags) {
    reset();
    func88h_0096ff70(subobject(), flag);
    assert(event_count == 1);
    assert(events[0].kind == Kind::scalar_deleting_0096ffd0);
    assert(events[0].flag == flag);
  }
}

// Only bit 0 of the forwarded word is meaningful to the callee.
void test_only_low_flag_bit_matters_downstream() {
  reset();
  func88h_0096ff70(subobject(), 0u);
  assert(events[0].result == 0u);
  reset();
  func88h_0096ff70(subobject(), 0x00000001u);
  assert(events[0].result == 1u);
  reset();
  func88h_0096ff70(subobject(), 0x00ffffffu);
  assert(events[0].result == 1u);
}

// The thunk performs no store of its own: only the callee ever writes memory.
void test_thunk_writes_nothing_before_the_tail_call() {
  reset();
  most_derived()->reference_count_08 = 0x0000002a;
  func88h_0096ff70(subobject(), 0x00000001u);
  assert(most_derived()->reference_count_08 == 0x0000002a);
  most_derived()->reference_count_08 = 0;
  assert(event_count == 1);
}

// The +0x0C receiver adjustment lines up with the SDK-documented
// IBiStateEffect subobject of UTFWin::GlideEffect.
void test_adjustment_target_is_the_bistate_subobject() {
  assert(offsetof(GlideEffect, bi_state_interface_vtable_0c) == 0x0c);
  assert(sizeof(GlideEffectBiStateSubobject) == 0x0c);
  assert(sizeof(GlideEffect) == 0x70);
  assert(pointer_word(most_derived_below(subobject())) ==
         pointer_word(most_derived()));
}

// The vector-deleting sibling of the same leaf block uses the same receiver
// adjustment, which is what makes the pair look like a dtor slot pair.
void test_vector_sibling_shares_the_receiver_adjustment() {
  reset();
  func88h_vector_0096ff90(subobject(), 0u);
  assert(event_count == 1);
  assert(events[0].kind == Kind::vector_deleting_0096ff20);
  assert(events[0].object == pointer_word(most_derived()));
  assert(events[0].object ==
         pointer_word(subobject()) - kFunc88hConstants.receiver_adjustment);
}

}

int main() {
  test_abi_record();
  test_constants_match_listing();
  test_vtable_run_holds_this_target();
  test_receiver_is_adjusted_by_minus_0x0c();
  test_single_stack_word_is_forwarded();
  test_only_low_flag_bit_matters_downstream();
  test_thunk_writes_nothing_before_the_tail_call();
  test_adjustment_target_is_the_bistate_subobject();
  test_vector_sibling_shares_the_receiver_adjustment();
  return 0;
}
