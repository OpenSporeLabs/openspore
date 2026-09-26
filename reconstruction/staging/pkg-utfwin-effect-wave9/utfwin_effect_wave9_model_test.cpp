#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <utility>

#include "utfwin_effect_wave9.hpp"

namespace openspore::reconstruction::pkg_utfwin_effect_wave9 {
namespace {

struct OpaqueState {
  std::array<Opaque, 12> words{};
};

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Opaque fallback_count = 0;
Opaque fallback_object = 0;
Opaque fallback_token = 0;

Opaque shared_count = 0;
Opaque shared_object = 0;
Opaque shared_token = 0;

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

template <typename To, typename From>
Opaque function_word(From function) {
  static_assert(sizeof(To) == sizeof(From), "function pointer width mismatch");
  Opaque result{};
  std::memcpy(&result, &function, sizeof(result));
  return result;
}

template <typename To>
To function_from(Opaque word) {
  static_assert(sizeof(To) == sizeof(Opaque),
                "function pointer width mismatch");
  To result{};
  std::memcpy(&result, &word, sizeof(result));
  return result;
}

extern "C" Opaque PKG_W9_THISCALL wave9_fallback_00951240(Opaque object,
                                                          Opaque token) {
  ++fallback_count;
  fallback_object = object;
  fallback_token = token;
  if (token == 0x6ec581fdu) {
    return object;
  }
  if ((token == 0xee3f516eu || token == 0xeec58382u) && object != 0u) {
    return object + 0x04u;
  }
  return 0u;
}

extern "C" Opaque PKG_W9_THISCALL wave9_fallback_00950eb0(Opaque object,
                                                          Opaque token) {
  ++shared_count;
  shared_object = object;
  shared_token = token;
  if (token == 0x2f009dd0u) {
    return object;
  }
  if ((token == 0xee3f516eu || token == 0xeec58382u) && object != 0u) {
    return object + 0x04u;
  }
  return 0u;
}

extern "C" Opaque PKG_W9_THISCALL wave9_dispatch_00980330(Opaque object,
                                                          Opaque token) {
  if (token != 0xef865d7eu) {
    return wave9_fallback_00950eb0(object, token);
  }
  if (object != 0u) {
    return object + 0x0cu;
  }
  return 0u;
}

Opaque call_three_argument(Opaque object, Opaque first, Opaque second,
                           Opaque third) {
  Opaque result = 0;
#if defined(__GNUC__) || defined(__clang__)
  __asm__ volatile(
      "pushl %[third]\n\t"
      "pushl %[second]\n\t"
      "pushl %[first]\n\t"
      "call utfwin_wave9_00980c50\n\t"
      "movl %%eax, %[result]\n\t"
      "addl $12, %%esp\n\t"
      : [result] "=a"(result)
      : [object] "c"(object), [first] "D"(first), [second] "S"(second),
        [third] "b"(third)
      : "cc", "memory");
#else
  const ThreeArgumentSlot target = utfwin_wave9_00980c50;
  result = target(object, first, second, third);
#endif
  return result;
}

void test_00980480_dispatch_and_vtable_slot() {
  OpaqueVtableA vtable{};
  vtable.slot_3c = function_word<MessageSlot>(utfwin_wave9_00980480);
  const MessageSlot slot = function_from<MessageSlot>(vtable.slot_3c);
  OpaqueState state{};
  state.words[0] = 0x10203040u;
  const Opaque object = pointer_word(&state);
  const Opaque adjusted = object - 0x04u;
  const std::array<Opaque, 12> before = state.words;

  shared_count = 0;
  shared_object = 0;
  shared_token = 0;

  check(slot(object, 0xef865d7eu) == object + 0x08u);
  check(shared_count == 0u);

  check(slot(object, 0x2f009dd0u) == adjusted);
  check(shared_count == 1u);
  check(shared_object == adjusted);
  check(shared_token == 0x2f009dd0u);

  check(slot(object, 0xee3f516eu) == object);
  check(shared_count == 2u);
  check(shared_object == adjusted);
  check(shared_token == 0xee3f516eu);

  check(slot(object, 0xeec58382u) == object);
  check(shared_count == 3u);
  check(shared_token == 0xeec58382u);

  check(slot(object, 0x12345678u) == 0u);
  check(shared_count == 4u);
  check(shared_token == 0x12345678u);

  check(slot(object, 0xef865d7fu) == 0u);
  check(shared_count == 5u);
  check(shared_token == 0xef865d7fu);

  check(shared_count == 5u);
  check(slot(0u, 0xef865d7eu) == 0x00000008u);
  check(shared_count == 5u);
  check(slot(0u, 0x2f009dd0u) == 0xfffffffcu);
  check(shared_count == 6u);
  check(shared_object == 0xfffffffcu);
  check(slot(0u, 0xee3f516eu) == 0u);
  check(shared_count == 7u);
  check(slot(0u, 0xeec58382u) == 0u);
  check(shared_count == 8u);
  check(slot(0u, 0x12345678u) == 0u);
  check(shared_count == 9u);
  check(state.words == before);
}

void test_00950eb0_shared_port_selector_matrix() {
  OpaqueState state{};
  const Opaque object = pointer_word(&state);

  shared_count = 0;
  shared_object = 0;
  shared_token = 0;

  check(wave9_fallback_00950eb0(object, 0x2f009dd0u) == object);
  check(wave9_fallback_00950eb0(object, 0xee3f516eu) == object + 0x04u);
  check(wave9_fallback_00950eb0(object, 0xeec58382u) == object + 0x04u);
  check(wave9_fallback_00950eb0(object, 0xef865d7eu) == 0u);
  check(wave9_fallback_00950eb0(object, 0x00000000u) == 0u);
  check(wave9_fallback_00950eb0(object, 0xffffffffu) == 0u);
  check(wave9_fallback_00950eb0(0u, 0x2f009dd0u) == 0u);
  check(wave9_fallback_00950eb0(0u, 0xee3f516eu) == 0u);
  check(wave9_fallback_00950eb0(0u, 0xeec58382u) == 0u);
  check(shared_count == 9u);
  check(shared_object == 0u);
  check(shared_token == 0xeec58382u);
}

void test_00980330_port_special_path_exclusivity() {
  OpaqueState state{};
  const Opaque object = pointer_word(&state);

  shared_count = 0;
  shared_object = 0;
  shared_token = 0;

  check(wave9_dispatch_00980330(object, 0xef865d7eu) == object + 0x0cu);
  check(shared_count == 0u);
  check(wave9_dispatch_00980330(0u, 0xef865d7eu) == 0u);
  check(shared_count == 0u);

  const std::array<std::pair<Opaque, Opaque>, 6> shared_matrix = {{
      {0x2f009dd0u, object},
      {0xee3f516eu, object + 0x04u},
      {0xeec58382u, object + 0x04u},
      {0xef2b293bu, 0u},
      {0xeef3af8cu, 0u},
      {0x12345678u, 0u},
  }};
  for (const auto& entry : shared_matrix) {
    check(wave9_dispatch_00980330(object, entry.first) == entry.second);
  }
  check(shared_count == 6u);
  check(shared_object == object);
  check(shared_token == 0x12345678u);
}

void test_009804e0_event_branches() {
  OpaqueVtableB vtable{};
  vtable.slot_0c = function_word<TokenSlot>(utfwin_wave9_009804e0);
  vtable.slot_14 = function_word<ProxySlot>(utfwin_wave9_00980510);
  const TokenSlot token_slot = function_from<TokenSlot>(vtable.slot_0c);
  const ProxySlot proxy_slot = function_from<ProxySlot>(vtable.slot_14);
  OpaqueState state{};
  const Opaque object = pointer_word(&state);
  const std::array<Opaque, 12> before = state.words;

  shared_count = 0;
  shared_object = 0;
  shared_token = 0;

  check(token_slot(object, 0xef2b293bu) == object + 0x0cu);
  check(shared_count == 0u);

  check(token_slot(object, 0x2f009dd0u) == object);
  check(shared_count == 1u);
  check(shared_object == object);
  check(shared_token == 0x2f009dd0u);

  check(token_slot(object, 0xee3f516eu) == object + 0x04u);
  check(shared_count == 2u);
  check(token_slot(object, 0xeec58382u) == object + 0x04u);
  check(shared_count == 3u);
  check(token_slot(object, 0x12345678u) == 0u);
  check(shared_count == 4u);
  check(token_slot(object, 0xef865d7eu) == 0u);
  check(shared_count == 5u);
  check(shared_token == 0xef865d7eu);

  check(token_slot(0u, 0xef2b293bu) == 0u);
  check(shared_count == 5u);
  check(token_slot(0u, 0x2f009dd0u) == 0u);
  check(shared_count == 6u);
  check(token_slot(0u, 0xee3f516eu) == 0u);
  check(shared_count == 7u);
  check(token_slot(0u, 0xeec58382u) == 0u);
  check(shared_count == 8u);
  check(token_slot(0u, 0x12345678u) == 0u);
  check(shared_count == 9u);

  check(proxy_slot(object) == 0x202u);
  check(proxy_slot(0u) == 0x202u);
  check(state.words == before);
}

void test_00980c50_return_width_and_caller_cleanup() {
  OpaqueVtableC vtable{};
  vtable.slot_50 = function_word<ThreeArgumentSlot>(utfwin_wave9_00980c50);
  const ThreeArgumentSlot slot =
      function_from<ThreeArgumentSlot>(vtable.slot_50);
  check(slot == utfwin_wave9_00980c50);
  check(vtable.slot_50 ==
        function_word<ThreeArgumentSlot>(utfwin_wave9_00980c50));
  OpaqueState state{};
  const Opaque object = pointer_word(&state);
  const std::array<Opaque, 12> before = state.words;

  check(call_three_argument(object, 0u, 0u, 0u) == 0xcf2b2ad5u);
  check(call_three_argument(object, 0x11111111u, 0x22222222u, 0x33333333u) ==
        0xcf2b2ad5u);
  check(call_three_argument(0u, 0xffffffffu, 0xeeeeeeeeu, 0xddddddddu) ==
        0xcf2b2ad5u);
  check(state.words == before);
}

void test_009817c0_image_and_state_branches() {
  OpaqueVtableD vtable_d{};
  OpaqueVtableE vtable_e{};
  vtable_d.slot_24 = function_word<ImageSlot>(utfwin_wave9_009817c0);
  vtable_e.slot_88 = function_word<ImageSlot>(utfwin_wave9_009817c0);
  const ImageSlot slot_d = function_from<ImageSlot>(vtable_d.slot_24);
  const ImageSlot slot_e = function_from<ImageSlot>(vtable_e.slot_88);
  OpaqueState state{};
  const Opaque object = pointer_word(&state);
  const std::array<Opaque, 12> before = state.words;
  const std::array<Opaque, 2> live_tokens = {0xeec58382u, 0xeef3af8cu};

  fallback_count = 0;
  fallback_object = 0;
  fallback_token = 0;

  for (const Opaque token : live_tokens) {
    const Opaque expected =
        token == 0xeec58382u ? object + 0x04u : object + 0x0cu;
    check(slot_d(object, token) == expected);
    check(slot_e(object, token) == expected);
  }
  check(fallback_count == 0u);

  check(slot_d(0u, 0xeec58382u) == 0u);
  check(slot_d(0u, 0xeef3af8cu) == 0u);
  check(slot_d(object, 0x6ec581fdu) == object);
  check(fallback_count == 1u);
  check(fallback_object == object);
  check(fallback_token == 0x6ec581fdu);
  check(slot_d(object, 0xee3f516eu) == object + 0x04u);
  check(fallback_count == 2u);
  check(fallback_object == object);
  check(fallback_token == 0xee3f516eu);
  check(slot_d(object, 0x12345678u) == 0u);
  check(fallback_count == 3u);
  check(fallback_token == 0x12345678u);
  check(slot_d(0u, 0x6ec581fdu) == 0u);
  check(slot_d(0u, 0xee3f516eu) == 0u);
  check(state.words == before);
}

}

int run_tests() {
  test_00980480_dispatch_and_vtable_slot();
  test_00950eb0_shared_port_selector_matrix();
  test_00980330_port_special_path_exclusivity();
  test_009804e0_event_branches();
  test_00980c50_return_width_and_caller_cleanup();
  test_009817c0_image_and_state_branches();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_utfwin_effect_wave9::run_tests();
}
