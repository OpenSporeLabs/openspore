#include <cassert>
#include <cstdint>

#include "utfwin_perspective_009804e0.hpp"

using namespace openspore::reconstruction::pkg_utfwin_perspective_009804e0;

namespace {

void* call_target(PerspectiveEffect* receiver, ObjectTypeId type_id) {
  return func80h_009804e0(receiver, type_id);
}

void* call_thunk_04(SubObjectVTable* receiver, ObjectTypeId type_id) {
  return cast_thunk_sub_04_00980660(receiver, type_id);
}

void* call_thunk_0c(SubObjectVTable* receiver, ObjectTypeId type_id) {
  return cast_thunk_sub_0c_00980670(receiver, type_id);
}

// 0x009804f8 LEA EAX,[ECX+0xc]: the recognised type word yields object+0x0c.
void test_perspective_type_word_returns_twelfth_dword() {
  PerspectiveEffect effect{};
  effect.vtable_00 = new PerspectiveEffectVTable();
  effect.vtable_04 = new SubObjectVTable();
  effect.vtable_0c = new SubObjectVTable();

  void* result = call_target(&effect, object_type_id::kIPerspectiveEffect);
  assert(result == &effect.vtable_0c);
  assert(result == reinterpret_cast<std::uint8_t*>(&effect) + 0x0c);

  delete effect.vtable_00;
  delete effect.vtable_04;
  delete effect.vtable_0c;
}

// 0x009804fe XOR EAX,EAX: a null receiver never yields a dangling offset.
void test_null_receiver_returns_null() {
  assert(call_target(nullptr, object_type_id::kIPerspectiveEffect) == nullptr);
  assert(call_target(nullptr, object_type_id::kIWinProc) == nullptr);
  assert(call_target(nullptr, object_type_id::kObject) == nullptr);
  assert(call_target(nullptr, object_type_id::kILayoutElement) == nullptr);
  assert(call_target(nullptr, 0x12345678u) == nullptr);
}

// 0x009804ef JMP 0x00950eb0: every other type word is answered by the base
// implementation - the object itself for IWinProc, object+4 for Object and
// ILayoutElement, null for anything else.
void test_other_type_words_fall_through_to_base_cast() {
  PerspectiveEffect effect{};

  assert(call_target(&effect, object_type_id::kIWinProc) == &effect);
  assert(call_target(&effect, object_type_id::kObject) ==
         reinterpret_cast<std::uint8_t*>(&effect) + 4);
  assert(call_target(&effect, object_type_id::kILayoutElement) ==
         reinterpret_cast<std::uint8_t*>(&effect) + 4);

  // UTFWin::IWindow is a real ObjectTYPE value that this class does not carry.
  assert(call_target(&effect, object_type_id::kIWindow) == nullptr);
  assert(call_target(&effect, 0x00000000u) == nullptr);
  assert(call_target(&effect, 0xffffffffu) == nullptr);
  // 0x01be8ca6 is the other word re_00957510 recognises for its own class.
  assert(call_target(&effect, 0x01be8ca6u) == nullptr);
}

// The +0x0c sub-object vftable (0x01444098) holds thunk 0x00980670 in its Cast
// slot, so casting through the returned pointer re-enters the same function
// with the receiver adjusted back to the complete object.
void test_returned_sub_object_round_trips_through_thunk() {
  PerspectiveEffect effect{};
  effect.vtable_0c = new SubObjectVTable();

  void* sub_object = call_target(&effect, object_type_id::kIPerspectiveEffect);
  assert(sub_object == &effect.vtable_0c);
  assert(call_thunk_0c(static_cast<SubObjectVTable*>(sub_object),
                       object_type_id::kIPerspectiveEffect) == &effect.vtable_0c);
  assert(call_thunk_0c(static_cast<SubObjectVTable*>(sub_object),
                       object_type_id::kObject) ==
         reinterpret_cast<std::uint8_t*>(&effect) + 4);
  assert(call_thunk_0c(static_cast<SubObjectVTable*>(sub_object), 0xdeadbeefu) ==
         nullptr);

  delete effect.vtable_0c;
}

// The +0x04 sub-object vftable (0x014440b4) holds thunk 0x00980660 in its Cast
// slot; that thunk subtracts 4 from the receiver before jumping to the target.
void test_second_sub_object_round_trips_through_four_byte_thunk() {
  PerspectiveEffect effect{};
  effect.vtable_04 = new SubObjectVTable();

  assert(call_thunk_04(reinterpret_cast<SubObjectVTable*>(&effect.vtable_04), object_type_id::kIPerspectiveEffect) ==
         &effect.vtable_0c);
  assert(call_thunk_04(reinterpret_cast<SubObjectVTable*>(&effect.vtable_04), object_type_id::kIWinProc) == &effect);
  assert(call_thunk_04(reinterpret_cast<SubObjectVTable*>(&effect.vtable_04), 0x00000000u) == nullptr);

  delete effect.vtable_04;
}

// The object head word at +0x08 is initialised to 0 by the constructor and no
// ObjectTYPE word in either implementation maps to it.
void test_eighth_dword_is_not_reachable_through_cast() {
  PerspectiveEffect effect{};

  assert(effect.field_08 == 0);
  for (ObjectTypeId word = 1; word < 0x10000u; word += 0x37u) {
    void* result = call_target(&effect, word);
    assert(result == nullptr || result == &effect ||
           result == reinterpret_cast<std::uint8_t*>(&effect) + 4 ||
           result == &effect.vtable_0c);
  }
}

}

int main() {
  test_perspective_type_word_returns_twelfth_dword();
  test_null_receiver_returns_null();
  test_other_type_words_fall_through_to_base_cast();
  test_returned_sub_object_round_trips_through_thunk();
  test_second_sub_object_round_trips_through_four_byte_thunk();
  test_eighth_dword_is_not_reachable_through_cast();
  return 0;
}
