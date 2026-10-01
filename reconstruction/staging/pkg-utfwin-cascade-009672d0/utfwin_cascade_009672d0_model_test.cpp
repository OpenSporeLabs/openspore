#include <cassert>
#include <cstdint>

#include "utfwin_cascade_009672d0.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#else
#define TEST_THISCALL __attribute__((thiscall))
#endif

using openspore::reconstruction::pkg_utfwin_cascade_009672d0::Abi009672d0;
using openspore::reconstruction::pkg_utfwin_cascade_009672d0::Abi00950eb0;
using openspore::reconstruction::pkg_utfwin_cascade_009672d0::Opaque;
using openspore::reconstruction::pkg_utfwin_cascade_009672d0::
    kObjectTypeICascadeEffect;
using openspore::reconstruction::pkg_utfwin_cascade_009672d0::
    kObjectTypeILayoutElement;
using openspore::reconstruction::pkg_utfwin_cascade_009672d0::kObjectTypeIWinProc;
using openspore::reconstruction::pkg_utfwin_cascade_009672d0::kObjectTypeObject;

namespace {

int fallback_calls = 0;
Opaque fallback_object = 0;
Opaque fallback_type = 0;

Opaque pointer_value(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

Opaque* biased(Opaque word) {
  return reinterpret_cast<Opaque*>(word);
}

void reset() {
  fallback_calls = 0;
  fallback_object = 0;
  fallback_type = 0;
}

}

// Machine model of the tail callee at 0x00950eb0, transcribed from its 16
// instructions. It is a test double for a function this package does not
// reconstruct; the body reproduces the three comparisons and the two shared
// arms so the target's delegation is observable rather than asserted.
//
//   00950eb0  8b c1                 MOV EAX,ECX
//   00950eb2  8b 4c 24 04           MOV ECX,dword ptr [ESP + 0x4]
//   00950eb6  81 f9 d0 9d 00 2f     CMP ECX,0x2f009dd0
//   00950ebc  74 20                 JZ 0x00950ede
//   00950ebe  81 f9 6e 51 3f ee     CMP ECX,0xee3f516e
//   00950ec4  74 12                 JZ 0x00950ed8
//   00950ec6  81 f9 82 83 c5 ee     CMP ECX,0xeec58382
//   00950ecc  75 0e                 JNZ 0x00950edc
//   00950ece  85 c0                 TEST EAX,EAX
//   00950ed0  74 0a                 JZ 0x00950edc
//   00950ed2  83 c0 04              ADD EAX,0x4
//   00950ed5  c2 04 00              RET 0x4
//   00950ed8  85 c0                 TEST EAX,EAX
//   00950eda  75 0e ...  JNZ 0x00950ed2
//   00950edc  33 c0                 XOR EAX,EAX
//   00950ede  c2 04 00              RET 0x4
extern "C" Opaque* TEST_THISCALL cascade_type_fallback_00950eb0(Opaque object,
                                                                Opaque type) {
  ++fallback_calls;
  fallback_object = object;
  fallback_type = type;
  if (type == kObjectTypeIWinProc) {
    return biased(object);
  }
  if ((type == kObjectTypeObject || type == kObjectTypeILayoutElement) &&
      object != 0u) {
    return biased(object + 4u);
  }
  return nullptr;
}

namespace {

using openspore::reconstruction::pkg_utfwin_cascade_009672d0::
    handle_message_009672d0;

// 009672d4 CMP EAX,0x6f90a535 / 009672d9 JZ 0x009672e4 / 009672e8
// LEA EAX,[ECX + 0xc]: the only arm this body implements. The result is the
// receiver word biased by 0x0c, so it tracks the input rather than being a
// fixed value, and the delegate is never entered.
void test_own_type_arm_returns_receiver_plus_0x0c() {
  reset();
  const Abi009672d0 abi = handle_message_009672d0;
  const Opaque words[] = {0x12345000u, 0x7ffe0000u, 0x00b0000cu};
  for (const Opaque object : words) {
    assert(abi(object, kObjectTypeICascadeEffect) == biased(object + 0x0cu));
  }
  assert(fallback_calls == 0);
}

// 009672e4 TEST ECX,ECX / 009672e6 JZ 0x009672ee / 009672ee XOR EAX,EAX: a
// null receiver yields zero, which is not the biased address 0x0c that the
// taken arm would have produced for a non-null receiver of the same width.
void test_null_receiver_yields_null() {
  reset();
  const Abi009672d0 abi = handle_message_009672d0;
  assert(abi(0u, kObjectTypeICascadeEffect) == nullptr);
  assert(fallback_calls == 0);
}

// 009672db / 009672df: every other type word is handed to the tail callee with
// the receiver and the type word both intact. The three SDK words it recognises
// answer receiver+0x0, receiver+4 and receiver+4, so the pair as a whole is a
// cross-cast over those words.
void test_other_types_are_delegated_unchanged() {
  reset();
  const Abi009672d0 abi = handle_message_009672d0;
  const Opaque object = 0x12345000u;

  assert(abi(object, kObjectTypeIWinProc) == biased(object));
  assert(abi(object, kObjectTypeObject) == biased(object + 4u));
  assert(abi(object, kObjectTypeILayoutElement) == biased(object + 4u));
  assert(abi(object, 0x12345678u) == nullptr);

  assert(fallback_calls == 4);
  assert(fallback_object == object);
  assert(fallback_type == 0x12345678u);
}

// The delegate sees a null receiver too, and its two arms answer differently:
// the IWinProc arm returns the word unchanged, the other two return zero. Both
// still reach zero here, so the pair is only separable on a non-null receiver.
void test_null_receiver_through_the_delegate() {
  reset();
  const Abi009672d0 abi = handle_message_009672d0;
  assert(abi(0u, kObjectTypeIWinProc) == nullptr);
  assert(abi(0u, kObjectTypeObject) == nullptr);
  assert(abi(0u, kObjectTypeILayoutElement) == nullptr);
  assert(fallback_calls == 3);
  assert(fallback_object == 0u);
}

// The comparison is a single equality against one 32-bit word, so both
// neighbours of that word and every unrelated word must fall through to the
// delegate rather than being treated as the class's own type.
void test_neighbour_and_unrelated_words_fall_through() {
  reset();
  const Abi009672d0 abi = handle_message_009672d0;
  const Opaque object = 0x00b00000u;
  const Opaque words[] = {0x00000000u,
                          0x00000001u,
                          0xffffffffu,
                          0x6f90a534u,
                          0x6f90a536u,
                          0x6f90a535u ^ 0x80000000u};
  for (const Opaque word : words) {
    assert(abi(object, word) == nullptr);
  }
  assert(fallback_calls == 6);
  assert(fallback_object == object);
}

// The declared slot shape is reachable through a function pointer, which only
// holds if the one object word and the one 4-byte stack word bind as modelled.
void test_abi_projection_binds_receiver_and_type() {
  reset();
  const Abi009672d0 direct = handle_message_009672d0;
  const Abi00950eb0 delegate = cascade_type_fallback_00950eb0;
  std::uint8_t storage[0x40] = {};
  const Opaque receiver_word = pointer_value(storage + 0x10);

  assert(direct(receiver_word, kObjectTypeICascadeEffect) ==
         biased(receiver_word + 0x0cu));
  assert(direct(receiver_word, kObjectTypeILayoutElement) ==
         biased(receiver_word + 4u));
  assert(delegate(receiver_word, kObjectTypeIWinProc) == biased(receiver_word));
  // The callee never writes through the receiver word; storage is unchanged.
  for (const std::uint8_t byte : storage) {
    assert(byte == 0u);
  }
}

}

int main() {
  test_own_type_arm_returns_receiver_plus_0x0c();
  test_null_receiver_yields_null();
  test_other_types_are_delegated_unchanged();
  test_null_receiver_through_the_delegate();
  test_neighbour_and_unrelated_words_fall_through();
  test_abi_projection_binds_receiver_and_type();
}

#undef TEST_THISCALL
