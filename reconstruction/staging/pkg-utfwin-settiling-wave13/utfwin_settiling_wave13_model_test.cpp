// Model test for 0x00fd9460, UTFWin::ImageDrawable::SetTiling.
//
// What the machine listing fixes, and what each test below therefore attacks:
//
//   00fd9460  MOV EAX,dword ptr [ESP + 0x4]   the one incoming stack word
//   00fd9464  PUSH ESI / 00fd9465  MOV ESI,ECX the receiver is aliased into ESI
//   00fd9467  MOV dword ptr [ESI + 0x4], EAX  store #1, at +0x04
//   00fd946a  CALL 0x011e58c0                 the only call
//   00fd946f  MOV dword ptr [ESI + 0x8], EAX  store #2, at +0x08
//   00fd9473  RET 0x4                         the callee pops the stack word
//
// so: both stores are 4-byte, at displacements 0x04 and 0x08 of the receiver;
// the value at +0x04 is the incoming argument verbatim; the value at +0x08 is
// the callee's result verbatim; the body produces no return value; and the
// caller hands the argument word to the callee's own cleanup.
//
// Not asserted, on purpose:
//
//   * The relative order of the two stores. The callee receives no pointer into
//     the receiver, so no post-state distinguishes store-call-store from
//     call-store-store, and a test that pretended to observe the order would be
//     asserting something the machine cannot show. The listing fixes the order
//     and the body follows it.
//   * The number of accessor invocations. 0x011e58c0's guard and pointer slot
//     are internal to that function, so a reconstruction that called it twice
//     would leave the same receiver state. The body makes exactly one call
//     because the listing contains exactly one CALL.
//   * The C type of the word published at +0x08 beyond its 32-bit width and
//     its origin. The value is the address of a process-wide static object; the
//     object's element type is not established and is not claimed.
//
// Build (x86-32):
/*
 * clang++ -m32 -std=c++17 -Wall -Wextra -Werror -O2 \
 * -I. utfwin_settiling_wave13.cpp utfwin_settiling_wave13_model_test.cpp
 * ./utfwin_settiling_wave13_model_test && echo PASS
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "utfwin_settiling_wave13.hpp"

namespace openspore::reconstruction::pkg_utfwin_settiling_wave13 {
namespace {

int g_failures = 0;

void check(bool condition, const char *what) {
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s\n", what);
  }
}

// The reconstruction declares no result, and the listing supports that: EAX
// holds the callee's result at the moment it is stored to +0x08 and is never
// forwarded to the caller, and the body terminates in RET 0x4 without producing
// one. If a future edit gives the entry point a value return, this stops
// compiling -- which is the point: an added return type is a claim the machine
// record would have to be re-checked against, not a free refactor.
static_assert(
    std::is_same<decltype(&set_tiling_00fd9460),
                 void(PKG_UTFWIN_SETTILING_THISCALL *)(OpaqueSetTilingReceiverWire *,
                                                        OpaqueWord)>::value,
    "0x00fd9460 produces no return value; a value return would be a new claim");

OpaqueSetTilingReceiverWire seeded_receiver() {
  OpaqueSetTilingReceiverWire receiver{};
  receiver.dispatch_00 = 0x01493d00u;
  receiver.word_04 = 0x11111111u;
  receiver.shared_object_ptr_08 = 0x22222222u;
  return receiver;
}

// The observed body is two dword stores, so only +0x04 and +0x08 may change and
// the dispatch word at +0x00, which the constructor installed, must survive.
void test_stores_both_words_to_proven_offsets() {
  OpaqueSetTilingReceiverWire receiver = seeded_receiver();
  const OpaqueSetTilingReceiverWire before = receiver;
  const OpaqueWord expected = utfwin_shared_object_accessor_011e58c0();

  set_tiling_00fd9460(&receiver, 0xdeadbeefu);

  check(receiver.word_04 == 0xdeadbeefu, "+0x04 must hold the argument");
  check(receiver.shared_object_ptr_08 == expected,
        "+0x08 must hold the accessor's result");
  check(receiver.dispatch_00 == before.dispatch_00,
        "the dispatch word at +0x00 must survive untouched");
}

// Pointer vs pointee, on the store that publishes an address. 0x011e58c0
// returns the pointer slot at 0x016f4af4, which the initialiser publishes as
// the address of the shared object at 0x016f4afc; the word that object itself
// holds is its vtable, 0x014f6f80. So the address and the pointee's first word
// are two different constants in this model, and a reconstruction that stored
// the pointee, or that published some non-zero word of its own, would satisfy a
// test that only asked "was anything published at +0x08" and fails here.
//
// The address is a stand-in for the original's absolute address, chosen so that
// the published value is observable on the host; it is deliberately NOT
// dereferenced, because 0x016f4afc is not mapped here and the original's
// storage is not part of this package's evidence.
void test_published_word_is_the_object_address_not_its_pointee() {
  OpaqueSetTilingReceiverWire receiver = seeded_receiver();

  set_tiling_00fd9460(&receiver, 7u);

  const OpaqueWord published = receiver.shared_object_ptr_08;
  const OpaqueWord returned = utfwin_shared_object_accessor_011e58c0();
  check(published == returned, "+0x08 must hold the accessor's return value");
  check(published == kAccessorObjectStorage_016f4afc,
        "+0x08 must hold the modelled address of the shared object");
  check(published != kAccessorObjectVTable_014f6f80,
        "+0x08 is the object's ADDRESS, not the vtable the object holds");
  check(returned != kAccessorObjectVTable_014f6f80,
        "the accessor's result is the address, not the pointee's first word");
  check(published != 0u, "+0x08 must not be null");
  check(published != receiver.word_04,
        "+0x08 must not repeat the argument that went to +0x04");
}

// Displacement, not index. 0x04 and 0x08 are byte displacements. Read as word
// indices they would be byte offsets 0x10 and 0x20, so a wider-than-modelled
// arena with a distinct byte in each of those places is what separates the two
// readings. It also pins the extent: the body writes no byte at or above 0x0c.
void test_displacements_are_byte_offsets_not_word_indices() {
  std::uint8_t arena[0x30];
  for (std::size_t index = 0; index < sizeof(arena); ++index) {
    arena[index] = static_cast<std::uint8_t>(0x10u + index);
  }
  auto *const receiver = reinterpret_cast<OpaqueSetTilingReceiverWire *>(arena);
  std::uint8_t before[sizeof(arena)] = {};
  std::memcpy(before, arena, sizeof(arena));

  set_tiling_00fd9460(receiver, 0x0badf00du);

  check(receiver->word_04 == 0x0badf00du, "+0x04 is the argument");
  check(receiver->shared_object_ptr_08 ==
            utfwin_shared_object_accessor_011e58c0(),
        "+0x08 is the accessor's result");

  // Every byte outside the two written displacements is bit-for-bit unchanged.
  // The two dword stores cover 0x04..0x07 and 0x08..0x0b, so 0x0c..0x0f (the
  // first word past the modelled extent), 0x10 and 0x20 (the WORD-index reading
  // of 0x04 and 0x08), and every other byte must be untouched.
  for (std::size_t index = 0; index < sizeof(arena); ++index) {
    if (index >= 0x04 && index < 0x0c) {
      continue;
    }
    if (arena[index] != before[index]) {
      std::fprintf(stderr, "FAIL byte 0x%02zx moved: 0x%02x -> 0x%02x\n", index,
                   before[index], arena[index]);
      ++g_failures;
      break;
    }
  }
}

// The store to +0x04 takes the incoming stack word, not the receiver. The
// observed body loads entry ESP+0x4 into EAX and only afterwards moves ECX
// into ESI, so if the two were transposed this test would fail.
void test_store_source_is_the_argument_not_the_receiver() {
  OpaqueSetTilingReceiverWire receiver = seeded_receiver();
  const OpaqueWord receiver_value = 0x33333333u;
  const OpaqueWord argument_value = 0x44444444u;

  set_tiling_00fd9460(&receiver, argument_value);

  check(receiver.word_04 == argument_value, "+0x04 must be the argument");
  check(receiver.word_04 != receiver_value, "+0x04 must not be the old content");
}

// The two stores must not alias, and neither may depend on the other's value.
void test_the_two_stores_are_independent() {
  OpaqueSetTilingReceiverWire a = seeded_receiver();
  OpaqueSetTilingReceiverWire b = seeded_receiver();

  set_tiling_00fd9460(&a, 0xaaaaaaaau);
  set_tiling_00fd9460(&b, 0xbbbbbbbbu);

  check(a.word_04 == 0xaaaaaaaau, "receiver a: +0x04 is its own argument");
  check(b.word_04 == 0xbbbbbbbbu, "receiver b: +0x04 is its own argument");
  check(a.word_04 != a.shared_object_ptr_08,
        "+0x04 and +0x08 must not alias: chosen argument differs from the "
        "accessor result");
}

// Zero is an ordinary payload for the tiling word, not a skip, and the store
// still happens. This is the case that would be lost by a "non-zero means set"
// style reconstruction.
void test_zero_tiling_is_still_stored() {
  OpaqueSetTilingReceiverWire receiver = seeded_receiver();
  const OpaqueWord expected = utfwin_shared_object_accessor_011e58c0();

  set_tiling_00fd9460(&receiver, 0u);

  check(receiver.word_04 == 0u, "a zero argument is stored, not skipped");
  check(receiver.shared_object_ptr_08 == expected,
        "a zero argument does not suppress the +0x08 store");
}

// The value published at +0x08 is the shared object's address and is therefore
// the same for every receiver and every invocation. The observed accessor
// returns the pointer slot at absolute address 0x016f4af4, which it sets to
// 0x016f4afc, and never re-points it.
void test_shared_object_pointer_is_stable_and_shared() {
  OpaqueSetTilingReceiverWire first = seeded_receiver();
  OpaqueSetTilingReceiverWire second = seeded_receiver();

  set_tiling_00fd9460(&first, 1u);
  set_tiling_00fd9460(&second, 2u);
  set_tiling_00fd9460(&first, 3u);

  check(first.shared_object_ptr_08 == second.shared_object_ptr_08,
        "two receivers must publish the same shared object address");
  check(first.shared_object_ptr_08 == utfwin_shared_object_accessor_011e58c0(),
        "the published address is the accessor's return");
  check(first.shared_object_ptr_08 != 0u, "the published address is not null");
  // The two receiver arguments differ, so the identical +0x08 value can only
  // come from the accessor and not from a copy of the argument.
  check(first.word_04 != second.word_04,
        "distinct arguments must stay distinct at +0x04");
  check(first.word_04 != first.shared_object_ptr_08,
        "the argument must not be republished at +0x08");
}

// Repeated invocation overwrites the stale tiling word and leaves the shared
// pointer alone.
void test_repeated_invocation_overwrites_stale_tiling() {
  OpaqueSetTilingReceiverWire receiver = seeded_receiver();

  set_tiling_00fd9460(&receiver, 0x11111111u);
  set_tiling_00fd9460(&receiver, 0xcafebabeu);
  check(receiver.word_04 == 0xcafebabeu, "the stale tiling word is overwritten");
  check(receiver.dispatch_00 == 0x01493d00u, "the dispatch word survives");

  set_tiling_00fd9460(&receiver, 0xfeedfaceu);
  check(receiver.word_04 == 0xfeedfaceu, "each call republishes its argument");
}

// The observed instruction stream is value independent, so the only memory the
// body may touch is +0x04 and +0x08. Masking those two out of the receiver must
// leave it byte identical to its pre-call state, for many argument values.
void test_only_the_two_published_offsets_change() {
  OpaqueSetTilingReceiverWire receiver = seeded_receiver();
  OpaqueSetTilingReceiverWire previous = receiver;

  for (OpaqueWord seed = 0; seed < 64u; ++seed) {
    const OpaqueWord tiling = 0x9e3779b9u * (seed + 1u);
    set_tiling_00fd9460(&receiver, tiling);

    check(receiver.word_04 == tiling, "+0x04 tracks the argument");

    OpaqueSetTilingReceiverWire diff = receiver;
    diff.word_04 = previous.word_04;
    diff.shared_object_ptr_08 = previous.shared_object_ptr_08;
    check(std::memcmp(&diff, &previous, sizeof(diff)) == 0,
          "no byte outside +0x04 and +0x08 may change");

    previous = receiver;
  }
}

// The callee-cleanup contract, asserted at the only level where it is
// observable from C++. The body ends in "RET 0x4", so the 4-byte argument word
// belongs to the callee and the receiver cannot be on the stack: __thiscall with
// one stack word is the reading this package takes, and the test pins the
// declared prototype to exactly that and then calls the entry point through a
// function pointer of that type, so the body is only ever exercised through the
// convention it claims.
//
// A runtime stack-drift measurement was tried and deliberately dropped: on
// i386-ELF the compiler reserves the outgoing argument area for a caller-cleanup
// callee and lets a callee-cleanup callee pop the word the caller wrote at ESP,
// so the caller's ESP is unchanged under BOTH conventions and no probe of the
// caller's stack can separate them. Asserting a measurement that cannot fail
// would be worse than asserting the contract, so the contract is asserted.
void test_callee_pops_the_argument_word() {
  using Fn = void(PKG_UTFWIN_SETTILING_THISCALL *)(OpaqueSetTilingReceiverWire *,
                                                   OpaqueWord);
  static_assert(std::is_same<Fn, decltype(&set_tiling_00fd9460)>::value,
                "the entry point takes the receiver in ECX and exactly one "
                "4-byte callee-popped stack word");
  const Fn target = &set_tiling_00fd9460;
  OpaqueSetTilingReceiverWire receiver = seeded_receiver();

  target(&receiver, 0x0badf00du);

  // A cdecl-flavoured entry point would have taken the receiver from the stack
  // and stored through that pointer instead, so where the two words land is also
  // a measurement of the receiver's register.
  check(receiver.word_04 == 0x0badf00du,
        "the stack word reached the body and landed at +0x04");
  check(receiver.shared_object_ptr_08 ==
            utfwin_shared_object_accessor_011e58c0(),
        "the ECX receiver was the one the caller passed");
  check(receiver.dispatch_00 == 0x01493d00u,
        "the receiver the body wrote through is the caller's object");
}

} // namespace

int run_tests() {
  test_stores_both_words_to_proven_offsets();
  test_published_word_is_the_object_address_not_its_pointee();
  test_displacements_are_byte_offsets_not_word_indices();
  test_store_source_is_the_argument_not_the_receiver();
  test_the_two_stores_are_independent();
  test_zero_tiling_is_still_stored();
  test_shared_object_pointer_is_stable_and_shared();
  test_repeated_invocation_overwrites_stale_tiling();
  test_only_the_two_published_offsets_change();
  test_callee_pops_the_argument_word();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}

} // namespace openspore::reconstruction::pkg_utfwin_settiling_wave13

int main() {
  return openspore::reconstruction::pkg_utfwin_settiling_wave13::run_tests();
}
