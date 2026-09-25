#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "utfwin_effects_wave6.hpp"

namespace openspore::reconstruction::pkg_utfwin_effects_wave6 {
namespace model {

enum class Kind : std::uint8_t {
  allocator,
  factory,
  construct_0096fe30,
  construct_0097e380,
  adjust_0097e4a0,
  blend_007f5eb0,
  color_slot_5c,
  adjust_00980490,
};

struct Event {
  Kind kind;
  Opaque first;
  Opaque second;
  Opaque third;
  Opaque fourth;
};

std::array<Event, 32> events{};
std::size_t event_count;
Opaque allocator_result;
Opaque* factory_result;
Opaque adjustment_result;
Opaque blend_result;
Opaque virtual_result;

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(
      reinterpret_cast<std::uintptr_t>(pointer));
}

void add(Kind kind, Opaque first = 0, Opaque second = 0, Opaque third = 0,
         Opaque fourth = 0) {
  assert(event_count < events.size());
  events[event_count++] = Event{kind, first, second, third, fourth};
}

void reset() {
  event_count = 0;
  allocator_result = 0;
  factory_result = nullptr;
  adjustment_result = 0;
  blend_result = 0;
  virtual_result = 0;
}

template <typename Function>
Opaque function_word(Function function) {
  static_assert(sizeof(Opaque) == sizeof(Function),
                "function pointer width mismatch");
  Opaque word{};
  std::memcpy(&word, &function, sizeof(word));
  return word;
}

template <typename Function>
Function function_from(Opaque word) {
  static_assert(sizeof(Opaque) == sizeof(Function),
                "function pointer width mismatch");
  Function function{};
  std::memcpy(&function, &word, sizeof(function));
  return function;
}

void assert_rect(const FloatRect& rect, float left, float top, float right,
                 float bottom) {
  assert(rect.left == left);
  assert(rect.top == top);
  assert(rect.right == right);
  assert(rect.bottom == bottom);
}

void color_slot_5c(OpaqueColorTarget* target, Opaque value) {
  add(Kind::color_slot_5c, pointer_word(target), value, virtual_result);
  virtual_result = value;
}

}

}

using namespace openspore::reconstruction::pkg_utfwin_effects_wave6;
using namespace openspore::reconstruction::pkg_utfwin_effects_wave6::model;

extern "C" Opaque pkg18_re_009512c0() {
  add(Kind::allocator);
  return allocator_result;
}

extern "C" Opaque* pkg18_re_009512d0(Opaque size, Opaque alignment,
                                     const char* name, Opaque allocator) {
  add(Kind::factory, size, alignment, pointer_word(name), allocator);
  return factory_result;
}

extern "C" void PKG_UTFWIN_THISCALL pkg18_re_0096fe30(Opaque* object) {
  add(Kind::construct_0096fe30, pointer_word(object));
}

extern "C" Opaque* PKG_UTFWIN_THISCALL pkg18_re_0097e380(Opaque* object) {
  add(Kind::construct_0097e380, pointer_word(object));
  return object;
}

extern "C" Opaque PKG_UTFWIN_THISCALL pkg18_re_0097e4a0(Opaque object,
                                                        Opaque token) {
  add(Kind::adjust_0097e4a0, object, token);
  return adjustment_result;
}

extern "C" Opaque pkg18_re_007f5eb0(Opaque from, Opaque to, float amount) {
  Opaque amount_bits{};
  std::memcpy(&amount_bits, &amount, sizeof(amount_bits));
  add(Kind::blend_007f5eb0, from, to, amount_bits);
  return blend_result;
}

extern "C" Opaque PKG_UTFWIN_THISCALL pkg18_re_00980490(
    Opaque object, std::uint8_t flags) {
  add(Kind::adjust_00980490, object, flags);
  return adjustment_result;
}

namespace {

void test_0096fec0_factory_and_dispatch() {
  Opaque instance{};
  const FactorySlot slot = function_from<FactorySlot>(
      function_word(utfwin_0096fec0));
  reset();
  allocator_result = 0x00112233u;
  factory_result = &instance;
  Opaque* result = slot(0, 0xaaaaaaaau, 0);
  assert(result == &instance);
  assert(event_count == 3);
  assert(events[0].kind == Kind::allocator);
  assert(events[1].kind == Kind::factory);
  assert(events[1].first == 0x60u);
  assert(events[1].second == 4u);
  assert(events[1].third == 0x014424f4u);
  assert(events[1].fourth == 0x00112233u);
  assert(events[2].kind == Kind::construct_0096fe30);
  assert(events[2].first == pointer_word(&instance));

  reset();
  allocator_result = 0x00445566u;
  factory_result = &instance;
  result = slot(0x12345678u, 0xbbbbbbbbu, 0x00778899u);
  assert(result == &instance);
  assert(event_count == 2);
  assert(events[0].kind == Kind::factory);
  assert(events[0].fourth == 0x00778899u);
  assert(events[1].kind == Kind::construct_0096fe30);

  reset();
  allocator_result = 0x00abcdefu;
  factory_result = nullptr;
  result = slot(0, 0, 0);
  assert(result == nullptr);
  assert(event_count == 2);
  assert(events[0].kind == Kind::allocator);
  assert(events[1].kind == Kind::factory);
}

void test_0097e440_factory_and_dispatch() {
  Opaque instance{};
  const FactorySlot slot = function_from<FactorySlot>(
      function_word(utfwin_0097e440));
  reset();
  allocator_result = 0x10203040u;
  factory_result = &instance;
  Opaque* result = slot(0x11111111u, 0x22222222u, 0);
  assert(result == &instance);
  assert(event_count == 3);
  assert(events[0].kind == Kind::allocator);
  assert(events[1].kind == Kind::factory);
  assert(events[1].first == 0x760u);
  assert(events[1].second == 4u);
  assert(events[1].third == 0x014433f8u);
  assert(events[1].fourth == 0x10203040u);
  assert(events[2].kind == Kind::construct_0097e380);
  assert(events[2].first == pointer_word(&instance));

  reset();
  factory_result = nullptr;
  result = slot(0, 0, 0x50607080u);
  assert(result == nullptr);
  assert(event_count == 1);
  assert(events[0].kind == Kind::factory);
  assert(events[0].fourth == 0x50607080u);
}

void test_constant_return_slots() {
  const ConstantSlot glide = function_from<ConstantSlot>(
      function_word(utfwin_0096ffc0));
  const ConstantSlot simple = function_from<ConstantSlot>(
      function_word(utfwin_0097e890));
  const ConstantSlot modulate = function_from<ConstantSlot>(
      function_word(utfwin_00980200));
  assert(glide(0, 0xffffffffu) == 0x01442694u);
  assert(simple(0x12345678u, 0) == 0x01436b0u);
  assert(modulate(0, 0xabcdef01u) == 0x01443e4cu);
}

void test_adjusted_this_slots() {
  const AdjustSlot inflate = function_from<AdjustSlot>(
      function_word(utfwin_0097e550));
  const AdjustSlot perspective = function_from<AdjustSlot>(
      function_word(utfwin_00980470));
  reset();
  adjustment_result = 0xfeedbeefu;
  assert(inflate(0x12345678u, 0xaf3dad29u) == adjustment_result);
  assert(event_count == 1);
  assert(events[0].kind == Kind::adjust_0097e4a0);
  assert(events[0].first == 0x1234566cu);
  assert(events[0].second == 0xaf3dad29u);

  reset();
  adjustment_result = 0x0badf00du;
  assert(inflate(0, 0) == adjustment_result);
  assert(events[0].first == 0xfffffff4u);

  reset();
  adjustment_result = 0x0055aa55u;
  assert(perspective(0x87654321u, 0xfe) == adjustment_result);
  assert(event_count == 1);
  assert(events[0].kind == Kind::adjust_00980490);
  assert(events[0].first == 0x87654315u);
  assert(events[0].second == 0xfeu);
}

void test_0097e990_branches_and_mutation_order() {
  const RectTransformSlot slot = function_from<RectTransformSlot>(
      function_word(utfwin_0097e990));
  const FloatRect source{1.0f, 2.0f, 7.0f, 11.0f};
  OpaqueLayout layout{};

  layout.flags = 0x00;
  FloatRect destination{20.0f, 30.0f, 50.0f, 70.0f};
  assert(slot(&layout, &source, &destination));
  assert_rect(destination, 14.0f, 21.0f, 50.0f, 70.0f);

  layout.flags = 0x05;
  destination = {20.0f, 30.0f, 50.0f, 70.0f};
  assert(slot(&layout, &source, &destination));
  assert_rect(destination, 20.0f, 30.0f, 50.0f, 70.0f);

  layout.flags = 0x0a;
  destination = {20.0f, 30.0f, 50.0f, 70.0f};
  assert(slot(&layout, &source, &destination));
  assert_rect(destination, 20.0f, 30.0f, 44.0f, 61.0f);

  layout.flags = 0x0f;
  destination = {20.0f, 30.0f, 50.0f, 70.0f};
  assert(slot(&layout, &source, &destination));
  assert_rect(destination, 20.0f, 30.0f, 44.0f, 61.0f);

  layout.flags = 0x0e;
  FloatRect aliased{1.0f, 2.0f, 7.0f, 11.0f};
  assert(slot(&layout, &aliased, &aliased));
  assert_rect(aliased, 1.0f, 2.0f, 1.0f, 2.0f);
}

void test_0097ea50_field_copies() {
  const RectStoreSlot slot = function_from<RectStoreSlot>(
      function_word(utfwin_0097ea50));
  OpaqueLayout layout{};
  layout.vtable = 0x11223344u;
  layout.flags = 0xa5u;
  const FloatRect source{-0.0f, 2.5f, 8.0f, -4.0f};
  slot(&layout, &source);
  assert(layout.vtable == 0x11223344u);
  assert(layout.flags == 0xa5u);
  assert_rect(layout.stored, -0.0f, 2.5f, 8.0f, -4.0f);
  assert_rect(source, -0.0f, 2.5f, 8.0f, -4.0f);

  const FloatRect* aliased = &layout.stored;
  slot(&layout, aliased);
  assert_rect(layout.stored, -0.0f, 2.5f, 8.0f, -4.0f);
}

void test_00980120_blend_then_virtual_dispatch() {
  OpaqueColorVtable vtable{};
  vtable.slot_5c = function_word(color_slot_5c);
  OpaqueColorTarget target{};
  target.vtable = &vtable;
  OpaqueModulateEffect effect{};
  effect.vtable = 0x55667788u;
  effect.color_64 = 0x11223344u;
  effect.color_68 = 0x99aabbccu;
  const ModulateSlot slot = function_from<ModulateSlot>(
      function_word(utfwin_00980120));
  reset();
  blend_result = 0xddeeff00u;
  slot(&effect, &target, 0.25f);
  assert(event_count == 2);
  assert(events[0].kind == Kind::blend_007f5eb0);
  assert(events[0].first == effect.color_64);
  assert(events[0].second == effect.color_68);
  assert(events[0].third == 0x3e800000u);
  assert(events[1].kind == Kind::color_slot_5c);
  assert(events[1].first == pointer_word(&target));
  assert(events[1].second == blend_result);
  assert(virtual_result == blend_result);
  assert(effect.vtable == 0x55667788u);
  assert(effect.color_64 == 0x11223344u);
  assert(effect.color_68 == 0x99aabbccu);

  reset();
  blend_result = 0;
  slot(&effect, &target, -0.0f);
  assert(event_count == 2);
  assert(events[0].kind == Kind::blend_007f5eb0);
  assert(events[0].third == 0x80000000u);
  assert(events[1].kind == Kind::color_slot_5c);
  assert(events[1].second == 0);
}

}

int main() {
  test_0096fec0_factory_and_dispatch();
  test_0097e440_factory_and_dispatch();
  test_constant_return_slots();
  test_adjusted_this_slots();
  test_0097e990_branches_and_mutation_order();
  test_0097ea50_field_copies();
  test_00980120_blend_then_virtual_dispatch();
}
