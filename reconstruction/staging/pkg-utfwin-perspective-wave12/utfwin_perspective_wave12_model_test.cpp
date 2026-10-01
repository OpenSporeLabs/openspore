// Focused model test for 0x00980480
// (UTFWin::PerspectiveEffect::HandleUIMessage), a cross-vtable thunk.
//
// The entry point under test is a two-instruction body -- `SUB ECX, 0x4` then
// `JMP 0x00980330` -- so what is testable is the forwarding contract: that the
// secondary-base receiver is de-adjusted by exactly 0x4, that the single stack
// word is passed through untouched, and that the callee's result is returned
// verbatim. The tail callee 0x00980330 and its own tail 0x00950eb0 are NOT this
// package's target; they are transcribed here only so the forwarding has
// something to forward to, and every constant in them is the one the disassembly
// shows.

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "utfwin_perspective_wave12.hpp"

namespace openspore::reconstruction::pkg_utfwin_perspective_wave12 {
namespace model {

// Constants transcribed from the listing of 0x00980330 (CMP EAX,0xef865d7e) and
// of 0x00950eb0 (CMP ECX against 0x2f009dd0 / 0xee3f516e / 0xeec58382).
enum : Opaque {
  kPerspectiveHandledWord = 0xef865d7eu,
  kWinProcWord = 0x2f009dd0u,
  kObjectWord = 0xee3f516eu,
  kLayoutElementWord = 0xeec58382u,
};

struct Call {
  Opaque primary;
  Opaque word;
};

constexpr std::size_t kMaxCalls = 8;
Call calls[kMaxCalls];
std::size_t call_count;
Opaque scripted_result;
bool scripted_result_set;

void reset() {
  call_count = 0;
  scripted_result = 0;
  scripted_result_set = false;
}

void record(const void* receiver, Opaque word) {
  assert(call_count < kMaxCalls);
  calls[call_count].primary =
      static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(receiver));
  calls[call_count].word = word;
  ++call_count;
}

// The machine adds 0x04 / 0x0c to the receiver as a byte address and returns
// it in EAX, so the model does the same and re-types the result.
Opaque* offset_of(const void* receiver, std::size_t offset) {
  if (receiver == nullptr) {
    return nullptr;
  }
  const auto* bytes = static_cast<const unsigned char*>(receiver);
  return reinterpret_cast<Opaque*>(const_cast<unsigned char*>(bytes) + offset);
}

// Model of 0x00950eb0, the second link of the chain: returns the receiver plus
// 0x04 for two of its three immediates, and null for the third and for every
// unrecognised word.
Opaque* chain_00950eb0(const void* receiver, Opaque word) {
  if (word == kWinProcWord) {
    return nullptr;
  }
  if (word == kObjectWord || word == kLayoutElementWord) {
    return offset_of(receiver, 0x04);
  }
  return nullptr;
}

// Model of 0x00980330, the tail target of the thunk: one compared word yields
// the receiver plus 0x0c, anything else is forwarded down the chain.
Opaque* dispatch_00980330(const void* receiver, Opaque word) {
  record(receiver, word);
  if (scripted_result_set) {
    return reinterpret_cast<Opaque*>(static_cast<std::uintptr_t>(
        scripted_result));
  }
  if (word == kPerspectiveHandledWord) {
    return offset_of(receiver, 0x0c);
  }
  return chain_00950eb0(receiver, word);
}

// The SDK layout of UTFWin::PerspectiveEffect (SIZE 0x14) with the two
// secondary interface sub-objects at +0x04 and +0x0c.
struct PerspectiveEffectImage {
  Opaque primary_interface;
  Opaque layout_element_interface;
  Opaque reference_count;
  Opaque perspective_interface;
  float near_plane;
};

static_assert(sizeof(PerspectiveEffectImage) == 0x14, "object is 0x14 bytes");
static_assert(offsetof(PerspectiveEffectImage, layout_element_interface) == 0x04,
              "ILayoutElement sub-object at +0x04");
static_assert(offsetof(PerspectiveEffectImage, reference_count) == 0x08,
              "mnRefCount at +0x08");
static_assert(offsetof(PerspectiveEffectImage, perspective_interface) == 0x0c,
              "IPerspectiveEffect sub-object at +0x0c");
static_assert(offsetof(PerspectiveEffectImage, near_plane) == 0x10,
              "mfNearPlane at +0x10");

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

Opaque word_of(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The SDK-derived secondary sub-object, expressed the way the thunk receives
// it: a pointer to the base that begins 0x04 into the object.
Opaque* layout_subobject(PerspectiveEffectImage* object) {
  return reinterpret_cast<Opaque*>(reinterpret_cast<unsigned char*>(object) +
                                   kLayoutElementBaseOffset);
}

}

}

using namespace openspore::reconstruction::pkg_utfwin_perspective_wave12;
using namespace openspore::reconstruction::pkg_utfwin_perspective_wave12::model;

extern "C" Opaque* PKG_PERSPECTIVE_THISCALL dispatch_00980330(
    void* receiver, Opaque message_word) {
  return model::dispatch_00980330(receiver, message_word);
}

namespace {

// The thunk is reached through a slot, never by name, so the first test drives
// it through a function pointer of the slot type.
MessageSlot slot() {
  return function_from<MessageSlot>(
      function_word(handle_message_00980480));
}

void test_adjustment_is_exactly_four() {
  PerspectiveEffectImage object{};
  object.primary_interface = 0x11111111u;
  object.layout_element_interface = 0x22222222u;
  object.reference_count = 3u;
  object.perspective_interface = 0x33333333u;
  object.near_plane = 0.5f;

  Opaque* subobject = layout_subobject(&object);
  assert(word_of(subobject) == word_of(&object.layout_element_interface));

  reset();
  Opaque* result = slot()(subobject, model::kPerspectiveHandledWord);
  assert(call_count == 1);
  assert(calls[0].primary == word_of(&object));
  assert(calls[0].word == model::kPerspectiveHandledWord);
  // The callee returns the primary receiver plus 0x0c, which is the third
  // interface sub-object the SDK layout records.
  assert(result == &object.perspective_interface);
  // The stored value of that sub-object is the returned address, not data the
  // callee wrote: nothing in the chain stores through the receiver.
  assert(object.perspective_interface == 0x33333333u);
  // Nothing else in the object is touched by the two-instruction body.
  assert(object.primary_interface == 0x11111111u);
  assert(object.layout_element_interface == 0x22222222u);
  assert(object.reference_count == 3u);
  assert(object.near_plane == 0.5f);
}

void test_word_is_forwarded_untouched() {
  PerspectiveEffectImage object{};
  Opaque* subobject = layout_subobject(&object);

  // The two immediates the chain's second link recognises both return +0x04.
  reset();
  Opaque* result = slot()(subobject, model::kObjectWord);
  assert(call_count == 1);
  assert(calls[0].primary == word_of(&object));
  assert(calls[0].word == model::kObjectWord);
  assert(result == &object.layout_element_interface);

  reset();
  result = slot()(subobject, model::kLayoutElementWord);
  assert(calls[0].word == model::kLayoutElementWord);
  assert(result == &object.layout_element_interface);

  // The one immediate the chain answers with null, and any unknown word.
  reset();
  result = slot()(subobject, model::kWinProcWord);
  assert(calls[0].word == model::kWinProcWord);
  assert(result == nullptr);

  reset();
  result = slot()(subobject, 0x12345678u);
  assert(calls[0].word == 0x12345678u);
  assert(result == nullptr);
}

void test_result_is_the_callees_verbatim() {
  PerspectiveEffectImage object{};
  Opaque* subobject = layout_subobject(&object);

  reset();
  scripted_result_set = true;
  scripted_result = 0xdeadbeefu;
  Opaque* result = slot()(subobject, 0x00000001u);
  assert(result ==
         reinterpret_cast<Opaque*>(static_cast<std::uintptr_t>(0xdeadbeefu)));
  // The scripted result short-circuits the callee's own logic, so only the
  // forwarding is under test here.
  assert(call_count == 1);
  assert(calls[0].primary == word_of(&object));
  assert(calls[0].word == 0x00000001u);
  scripted_result_set = false;
}

// The body is `SUB ECX, 0x4` with no test of ECX first, so a null receiver is
// de-adjusted to a non-null address and the callee's own null check -- which
// tests the *adjusted* pointer -- never fires. Asserted because it is the one
// place the reconstruction could quietly have "helpfully" added a guard the
// machine does not have.
void test_null_receiver_is_still_deadjusted() {
  reset();
  slot()(nullptr, model::kPerspectiveHandledWord);
  assert(call_count == 1);
  assert(calls[0].primary == 0xfffffffcu);
  assert(calls[0].word == model::kPerspectiveHandledWord);

  reset();
  slot()(nullptr, model::kObjectWord);
  assert(calls[0].primary == 0xfffffffcu);
}

void test_sibling_thunk_uses_the_other_base() {
  // 0x00980470, reconstructed in PKG-UTFWIN-EFFECTS-WAVE6, subtracts 0x0c and
  // the two adjustments must stay distinct: same virtual, two base sub-objects.
  assert(kPerspectiveBaseOffset != kLayoutElementBaseOffset);
  assert(kLayoutElementThisAdjustment == 0x04);
}

}

int main() {
  test_adjustment_is_exactly_four();
  test_word_is_forwarded_untouched();
  test_result_is_the_callees_verbatim();
  test_null_receiver_is_still_deadjusted();
  test_sibling_thunk_uses_the_other_base();
}
