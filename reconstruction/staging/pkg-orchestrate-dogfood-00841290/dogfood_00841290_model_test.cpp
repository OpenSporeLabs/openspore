#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "dogfood_00841290.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-00841290 needs MSVC or GCC CC macros"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_00841290 {
namespace {

int failures = 0;

struct ObservedDispatch {
  OpaqueFormatParser* receiver = nullptr;
  OpaqueWord argument = 0;
  unsigned int calls = 0;
  OpaqueWord result = 0;
};

ObservedDispatch observed_primary{};
ObservedDispatch observed_alternate{};
unsigned int wrong_slot_calls = 0;

OpaqueWord word_of(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

OpaqueWord PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
release_3c_primary(OpaqueFormatParser* receiver, OpaqueWord argument) {
  observed_primary.receiver = receiver;
  observed_primary.argument = argument;
  ++observed_primary.calls;
  return observed_primary.result;
}

OpaqueWord PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
release_3c_alternate(OpaqueFormatParser* receiver, OpaqueWord argument) {
  observed_alternate.receiver = receiver;
  observed_alternate.argument = argument;
  ++observed_alternate.calls;
  return observed_alternate.result;
}

OpaqueWord PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
wrong_slot_04(OpaqueFormatParser*, OpaqueWord) {
  ++wrong_slot_calls;
  return 0u;
}

struct Fixture {
  OpaqueFormatParser parser{};
  OpaqueFormatParserVtable vtable{};
  OpaqueFormatParser other_parser{};
  OpaqueFormatParserVtable other_vtable{};
  OpaqueWord canary = 0u;
};

void initialize(Fixture& fixture) {
  observed_primary = ObservedDispatch{};
  observed_alternate = ObservedDispatch{};
  wrong_slot_calls = 0u;

  fixture.vtable = OpaqueFormatParserVtable{};
  fixture.vtable.slots_00[0] = 0x00ff35d0u;
  fixture.vtable.slots_00[1] = reinterpret_cast<std::uintptr_t>(&wrong_slot_04);
  fixture.vtable.slots_00[14] = 0x01234567u;
  fixture.vtable.release_3c = &release_3c_primary;
  fixture.parser = OpaqueFormatParser{};
  fixture.parser.vtable = &fixture.vtable;

  fixture.other_vtable = OpaqueFormatParserVtable{};
  fixture.other_vtable.slots_00[0] = 0x00ff35d0u;
  fixture.other_vtable.slots_00[1] =
      reinterpret_cast<std::uintptr_t>(&wrong_slot_04);
  fixture.other_vtable.release_3c = &release_3c_alternate;
  fixture.other_parser = OpaqueFormatParser{};
  fixture.other_parser.vtable = &fixture.other_vtable;

  fixture.canary = 0x5a5a5a5au;

  g_dogfood_00841290_ports = OpaqueReleasePorts{};
}

void test_dispatches_once_through_slot_3c() {
  Fixture fixture{};
  initialize(fixture);
  observed_primary.result = 0xdeadbeefu;

  const bool released =
      argscript_formatparser_release_00841290(&fixture.parser, 0x12345678u);

  check(released);
  check(observed_primary.calls == 1u);
  check(observed_alternate.calls == 0u);
  check(wrong_slot_calls == 0u);
  check(observed_primary.receiver == &fixture.parser);
  check(observed_primary.argument == 0x12345678u);
  check(observed_primary.result == 0xdeadbeefu);
}

void test_result_is_true_when_slot_result_is_discarded() {
  Fixture fixture{};
  initialize(fixture);
  observed_primary.result = 0u;

  const bool released =
      argscript_formatparser_release_00841290(&fixture.parser, 1u);

  check(released);
  check(observed_primary.calls == 1u);
  check(observed_primary.result == 0u);
}

void test_receiver_and_vtable_are_not_modified() {
  Fixture fixture{};
  initialize(fixture);
  observed_primary.result = 0xffffffffu;

  const bool released =
      argscript_formatparser_release_00841290(&fixture.parser, 2u);

  check(released);
  check(observed_primary.calls == 1u);
  check(wrong_slot_calls == 0u);
  check(fixture.parser.vtable == &fixture.vtable);
  check(fixture.vtable.release_3c == &release_3c_primary);
  check(fixture.vtable.slots_00[0] == 0x00ff35d0u);
  check(fixture.vtable.slots_00[14] == 0x01234567u);
  check(fixture.canary == 0x5a5a5a5au);
  check(fixture.other_parser.vtable == &fixture.other_vtable);
  check(fixture.other_vtable.release_3c == &release_3c_alternate);
  check(observed_alternate.calls == 0u);
}

void test_stack_word_is_forwarded_verbatim() {
  Fixture fixture{};
  initialize(fixture);
  const OpaqueWord words[4] = {0u, 1u, 0xffffffffu, 0x80000000u};

  for (std::size_t index = 0u; index < 4u; ++index) {
    const bool released =
        argscript_formatparser_release_00841290(&fixture.parser, words[index]);
    check(released);
    check(observed_primary.argument == words[index]);
  }

  check(observed_primary.calls == 4u);

  const OpaqueWord pointer_word = word_of(&fixture.canary);
  const bool pointer_released =
      argscript_formatparser_release_00841290(&fixture.parser, pointer_word);

  check(pointer_released);
  check(observed_primary.calls == 5u);
  check(observed_primary.argument == pointer_word);
  check(observed_primary.argument != 0u);
}

void test_dispatch_target_follows_receiver_vtable() {
  Fixture fixture{};
  initialize(fixture);
  observed_alternate.result = 0x7fu;

  const bool primary_released =
      argscript_formatparser_release_00841290(&fixture.parser, 3u);
  const bool alternate_released =
      argscript_formatparser_release_00841290(&fixture.other_parser, 4u);

  check(primary_released);
  check(alternate_released);
  check(observed_primary.calls == 1u);
  check(observed_alternate.calls == 1u);
  check(observed_primary.receiver == &fixture.parser);
  check(observed_alternate.receiver == &fixture.other_parser);
  check(observed_primary.argument == 3u);
  check(observed_alternate.argument == 4u);
  check(observed_primary.receiver != observed_alternate.receiver);
}

void test_ports_and_observed_vtable_anchors_are_default_null() {
  check(g_dogfood_00841290_ports.release_3c == nullptr);
  check(sizeof(OpaqueReleasePorts) == 4);
  check(vtable_0141c930 == 0x0141c930u);
  check(vtable_0141c97c == 0x0141c97cu);
  check(vtable_0141c97c - vtable_0141c930 == 0x4cu);
  check(vtable_0141c97c == vtable_0141c930 + 0x4cu);
}

void test_modeled_signatures() {
  using ReleaseSignature = bool(PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL*)(
      OpaqueFormatParser*, OpaqueWord);
  using SlotSignature = OpaqueWord(PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL*)(
      OpaqueFormatParser*, OpaqueWord);

  static_assert(std::is_same<decltype(&argscript_formatparser_release_00841290),
                             ReleaseSignature>::value,
                "release is thiscall with one four-byte stack word and a "
                "boolean result");
  static_assert(std::is_same<FormatParserReleaseSlot3c, SlotSignature>::value,
                "slot keeps the receiver in ECX and one stack word");
  static_assert(
      std::is_same<decltype(&release_3c_primary), SlotSignature>::value,
      "fake matches the modeled slot signature");
  static_assert(std::is_same<decltype(&wrong_slot_04), SlotSignature>::value,
                "wrong-slot sentinel matches the modeled slot signature");
  static_assert(sizeof(decltype(&argscript_formatparser_release_00841290)) == 4,
                "entry point width");
  static_assert(offsetof(OpaqueFormatParserVtable, release_3c) == 0x3c,
                "dispatch slot offset");
}

int run_model() {
  failures = 0;
  test_dispatches_once_through_slot_3c();
  test_result_is_true_when_slot_result_is_discarded();
  test_receiver_and_vtable_are_not_modified();
  test_stack_word_is_forwarded_verbatim();
  test_dispatch_target_follows_receiver_vtable();
  test_ports_and_observed_vtable_anchors_are_default_null();
  test_modeled_signatures();
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_orchestrate_dogfood_00841290::
      run_model();
}

#undef PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
