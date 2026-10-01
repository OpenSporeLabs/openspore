// Model test for 0x00841290 (PKG-ORCHESTRATE-DOGFOOD-00841290).
//
// The machine body, 27 instructions, one basic block:
//
//   008412a9  MOV EAX,dword ptr [ECX]          receiver word at +0x00
//   008412ab  MOV EDX,dword ptr [EBP+0x8]      the one incoming stack word
//   008412ae  MOV EAX,dword ptr [EAX+0x3c]     the code word at +0x3c of THAT
//   008412b7  PUSH EDX                        the stack word, forwarded
//   008412bf  CALL EAX                        the slot, receiver still in ECX
//   008412c1  MOV AL,0x1                      the result is a constant true
//   008412d3  RET 0x4                         the callee pops the stack word
//
// This test exists to falsify the readings that a plausible-looking
// reconstruction could get wrong, not to walk the happy path:
//
//   * one-level vs two-level dereference -- a decoy code address is planted in
//     the RECEIVER at +0x3c. A body that read the slot out of the receiver
//     instead of out of the object the receiver's first word points at would
//     enter the decoy, and the decoy counts its own invocations.
//   * the exact slot displacement -- fifteen decoys occupy +0x00..+0x38
//     (vtable indices 0..14, including the neighbour at +0x38) and only +0x3c
//     (index 15) holds the real slot. Any off-by-one in the slot arithmetic
//     enters a decoy.
//   * vtable pointer depth and load ordering -- two receivers with two
//     different tables must reach two different targets, and the slot must be
//     entered with the receiver UNMODIFIED: the body reads ECX at 0x008412a9
//     and never writes it, so the table pointer the slot observes is the one the
//     caller installed.
//   * pointer vs pointee -- the word at +0x00 is a pointer to the table, and the
//     word at +0x3c of the table is a code address. Calling the pointer, or the
//     address of the slot, or dereferencing the code address once more, all
//     reach something other than the recorded slot.
//   * return semantics not over-claimed -- the body's result is `MOV AL,0x1`
//     AFTER the call, so it is a constant true whatever the slot returns. The
//     slot returns 0, 0xffffffff and 0xdeadbeef in turn and the entry point must
//     return true every time; a body that forwarded the slot's result, or that
//     reported the slot's success, would fail.
//   * constants compared by VALUE -- the observed vtable anchors and the 0x4c
//     gap between them are compared as numbers, never by spelling.
//
// Deliberately NOT asserted: the calling convention of the SLOT itself. The
// listing proves the state the slot is ENTERED in (receiver in ECX, one pushed
// stack word) and nothing about how it returns, so the slot's prototype below
// is this package's model and is labelled as such. A runtime stack-drift
// measurement of the outer entry point was also tried and dropped: on i386-ELF
// the compiler reserves the outgoing argument area itself, so the caller's ESP
// is unchanged whether the callee pops the word or not.
//
// Build (x86-32):
//   clang++ -m32 -std=c++17 -Wall -Wextra -Werror -O2 \
//       -I. dogfood_00841290.cpp dogfood_00841290_model_test.cpp
//   ./dogfood_00841290_model_test && echo PASS

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

#include "dogfood_00841290.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_00841290_TEST_THISCALL __thiscall
#else
#define PKG_ORCHESTRATE_DOGFOOD_00841290_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_00841290 {
namespace {

int g_failures = 0;

void check(bool condition, const char *what) {
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s\n", what);
  }
}

struct ObservedDispatch {
  OpaqueFormatParser* receiver = nullptr;
  OpaqueWord argument = 0;
  unsigned int calls = 0;
  OpaqueWord result = 0;
  // What the slot saw in the receiver's first word when it was entered. The
  // listing reads ECX at 0x008412a9 and never writes it, so the slot must
  // observe the caller's table pointer unchanged.
  const void* dispatch_word_seen = nullptr;
};

ObservedDispatch observed_primary{};
ObservedDispatch observed_alternate{};
unsigned int decoy_calls = 0;
unsigned int receiver_level_decoy_calls = 0;

template <class T>
OpaqueWord word_of(T pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The declared entry-point contract, pinned: receiver in ECX, one 4-byte
// callee-popped stack word (RET 0x4 at 0x008412d3), and a boolean result. A
// change to any of the three stops this file from compiling, which is the point:
// each is a claim the machine record would have to be re-checked against.
using EntryPoint = bool(PKG_ORCHESTRATE_DOGFOOD_00841290_TEST_THISCALL *)(
    OpaqueFormatParser*, OpaqueWord);
static_assert(
    std::is_same<EntryPoint,
                 decltype(&argscript_formatparser_release_00841290)>::value,
    "the entry point takes the receiver in ECX, one callee-popped stack word, "
    "and returns a boolean");

// The modelled slot contract. The listing proves the state the slot is entered
// in -- receiver in ECX, one pushed word -- and does not show how the slot
// returns, so the return type here is the package's model, not a machine fact.
using SlotSignature =
    OpaqueWord(PKG_ORCHESTRATE_DOGFOOD_00841290_TEST_THISCALL *)(
        OpaqueFormatParser*, OpaqueWord);

OpaqueWord PKG_ORCHESTRATE_DOGFOOD_00841290_TEST_THISCALL
release_3c_primary(OpaqueFormatParser* receiver, OpaqueWord argument) {
  observed_primary.receiver = receiver;
  observed_primary.argument = argument;
  ++observed_primary.calls;
  observed_primary.dispatch_word_seen =
      receiver != nullptr ? reinterpret_cast<const void*>(receiver->dispatch_00)
                          : nullptr;
  return observed_primary.result;
}

OpaqueWord PKG_ORCHESTRATE_DOGFOOD_00841290_TEST_THISCALL
release_3c_alternate(OpaqueFormatParser* receiver, OpaqueWord argument) {
  observed_alternate.receiver = receiver;
  observed_alternate.argument = argument;
  ++observed_alternate.calls;
  observed_alternate.dispatch_word_seen =
      receiver != nullptr ? reinterpret_cast<const void*>(receiver->dispatch_00)
                          : nullptr;
  return observed_alternate.result;
}

// Fifteen of these fill vtable indices 0..14, so only index 15 (+0x3c) is the
// real slot. One of them is also planted in the RECEIVER at +0x3c, where a
// one-level reading of the dispatch would find it.
OpaqueWord PKG_ORCHESTRATE_DOGFOOD_00841290_TEST_THISCALL
decoy_slot(OpaqueFormatParser*, OpaqueWord) {
  ++decoy_calls;
  return 0u;
}

OpaqueWord PKG_ORCHESTRATE_DOGFOOD_00841290_TEST_THISCALL
receiver_level_decoy(OpaqueFormatParser*, OpaqueWord) {
  ++receiver_level_decoy_calls;
  return 0u;
}

// The receiver has to be 0x40 bytes so a decoy can be planted at +0x3c, which
// the wire struct (one pointer) does not cover on its own. That is the whole
// point: the decoy must be reachable at the same displacement the body uses on
// the second dereference, so a one-level reading cannot pass unnoticed.
struct alignas(4) ReceiverArena {
  unsigned char bytes[0x40];
};

constexpr std::size_t kReceiverSlotDisplacement = 0x3c;
constexpr std::size_t kTableSlotDisplacement = 0x3c;

struct Fixture {
  ReceiverArena parser_arena{};
  ReceiverArena other_parser_arena{};
  OpaqueFormatParserVtable vtable{};
  OpaqueFormatParserVtable other_vtable{};
  OpaqueWord canary = 0u;

  OpaqueFormatParser* parser() {
    return reinterpret_cast<OpaqueFormatParser*>(parser_arena.bytes);
  }
  OpaqueFormatParser* other_parser() {
    return reinterpret_cast<OpaqueFormatParser*>(other_parser_arena.bytes);
  }
};

unsigned char* receiver_slot_address(Fixture& fixture) {
  return fixture.parser_arena.bytes + kReceiverSlotDisplacement;
}

void initialize(Fixture& fixture) {
  observed_primary = ObservedDispatch{};
  observed_alternate = ObservedDispatch{};
  decoy_calls = 0u;
  receiver_level_decoy_calls = 0u;

  fixture.vtable = OpaqueFormatParserVtable{};
  fixture.other_vtable = OpaqueFormatParserVtable{};

  // Indices 0..14 are decoys; index 15 (+0x3c) is the real slot. Filling the
  // whole modelled prefix is what makes the exact slot displacement a test
  // rather than an assertion.
  for (std::size_t index = 0; index < 15u; ++index) {
    fixture.vtable.slots_00[index] =
        reinterpret_cast<std::uintptr_t>(&decoy_slot);
    fixture.other_vtable.slots_00[index] =
        reinterpret_cast<std::uintptr_t>(&decoy_slot);
  }
  fixture.vtable.release_3c = &release_3c_primary;
  fixture.other_vtable.release_3c = &release_3c_alternate;

  std::memset(fixture.parser_arena.bytes, 0, sizeof(fixture.parser_arena.bytes));
  std::memset(fixture.other_parser_arena.bytes, 0,
              sizeof(fixture.other_parser_arena.bytes));
  fixture.parser()->dispatch_00 = &fixture.vtable;
  fixture.other_parser()->dispatch_00 = &fixture.other_vtable;

  // The one-level decoy: a valid code address at receiver+0x3c.
  const OpaqueWord decoy_address = word_of(&receiver_level_decoy);
  std::memcpy(receiver_slot_address(fixture), &decoy_address,
              sizeof(decoy_address));

  fixture.canary = 0x5a5a5a5au;

  g_dogfood_00841290_ports = OpaqueReleasePorts{};
}

// The happy path, and the shape of the call: exactly one entry into the slot at
// +0x3c, with the receiver and the forwarded word passed verbatim.
void test_dispatches_once_through_slot_3c() {
  Fixture fixture{};
  initialize(fixture);
  observed_primary.result = 0xdeadbeefu;

  const bool released =
      argscript_formatparser_release_00841290(fixture.parser(), 0x12345678u);

  check(released, "the entry point reports true");
  check(observed_primary.calls == 1u, "the slot at +0x3c is entered once");
  check(observed_alternate.calls == 0u, "the other receiver's slot is not");
  check(decoy_calls == 0u,
        "no vtable index below 15 may be entered: the slot displacement is "
        "exactly 0x3c");
  check(receiver_level_decoy_calls == 0u,
        "the code word at +0x3c belongs to the TABLE, not to the receiver");
  check(observed_primary.receiver == fixture.parser(),
        "the slot is entered with the caller's receiver in ECX");
  check(observed_primary.argument == 0x12345678u,
        "the incoming stack word is forwarded verbatim");
  check(observed_primary.result == 0xdeadbeefu,
        "precondition: the slot returned a distinctive value");
}

// Two-level dereference, isolated. Everything else is identical to the happy
// path except that the receiver's own +0x3c holds a decoy code address and the
// table's +0x3c holds the real slot. A body reading the slot out of the
// receiver enters the decoy; a body reading it out of the word the receiver's
// first word points at enters the real slot.
void test_slot_is_read_from_the_table_not_from_the_receiver() {
  Fixture fixture{};
  initialize(fixture);

  check(fixture.parser()->dispatch_00 == &fixture.vtable,
        "precondition: the receiver's first word is the table pointer");
  check(*reinterpret_cast<const OpaqueWord*>(
            fixture.parser_arena.bytes + kReceiverSlotDisplacement) ==
            word_of(&receiver_level_decoy),
        "precondition: a decoy code address sits at receiver+0x3c");

  const bool released = argscript_formatparser_release_00841290(fixture.parser(), 1u);

  check(released, "the entry point reports true");
  check(observed_primary.calls == 1u, "the table's slot at +0x3c is entered");
  check(receiver_level_decoy_calls == 0u,
        "receiver+0x3c is a decoy and must never be called");
  check(decoy_calls == 0u, "no other table index may be entered");
}

// Load ordering: the table pointer the slot observes must be the one the caller
// installed, i.e. the body read ECX at 0x008412a9 and did not write it before
// the call.
void test_slot_observes_the_unmodified_receiver() {
  Fixture fixture{};
  initialize(fixture);
  const ReceiverArena snapshot = fixture.parser_arena;

  argscript_formatparser_release_00841290(fixture.parser(), 2u);

  check(observed_primary.dispatch_word_seen == &fixture.vtable,
        "the slot must see the caller's table pointer, not a modified one");
  check(std::memcmp(&snapshot, &fixture.parser_arena,
                    sizeof(fixture.parser_arena)) == 0,
        "the body writes nothing: the receiver must be byte-identical after "
        "the call, decoy included");
  check(fixture.parser()->dispatch_00 == &fixture.vtable,
        "the receiver's first word survives the call");
  check(fixture.vtable.slots_00[0] ==
            reinterpret_cast<std::uintptr_t>(&decoy_slot),
        "the table is not modified either");
  check(fixture.vtable.release_3c == &release_3c_primary,
        "the slot word in the table is not modified");
}

// Vtable pointer depth: two receivers, two tables, two targets. A body that
// cached or ignored the table pointer would enter the same slot twice.
void test_dispatch_target_follows_receiver_table() {
  Fixture fixture{};
  initialize(fixture);
  observed_alternate.result = 0x7fu;

  const bool primary_released =
      argscript_formatparser_release_00841290(fixture.parser(), 3u);
  const bool alternate_released =
      argscript_formatparser_release_00841290(fixture.other_parser(), 4u);

  check(primary_released && alternate_released,
        "both receivers report true");
  check(observed_primary.calls == 1u, "the first receiver's slot ran once");
  check(observed_alternate.calls == 1u, "the second receiver's slot ran once");
  check(observed_primary.receiver == fixture.parser(),
        "the first call used the first receiver");
  check(observed_alternate.receiver == fixture.other_parser(),
        "the second call used the second receiver");
  check(observed_primary.receiver != observed_alternate.receiver,
        "the two calls must not share a receiver");
  check(observed_primary.argument == 3u && observed_alternate.argument == 4u,
        "each call forwards its own stack word");
}

// Return semantics. MOV AL,0x1 at 0x008412c1 runs AFTER the call, so the result
// is a constant true. A body that returned the slot's result, or that reported
// whether the slot succeeded, would return false or 0xffffffff here.
void test_result_is_constant_true_whatever_the_slot_returns() {
  const OpaqueWord slot_results[4] = {0u, 0xffffffffu, 0xdeadbeefu, 1u};
  for (const OpaqueWord result : slot_results) {
    Fixture fixture{};
    initialize(fixture);
    observed_primary.result = result;

    const bool released =
        argscript_formatparser_release_00841290(fixture.parser(), 9u);

    check(released, "the result is a constant true, not the slot's result");
    check(observed_primary.calls == 1u, "the slot still ran exactly once");
    check(observed_primary.result == result,
          "precondition: the slot did return the value under test");
  }
}

// The word is forwarded verbatim, including a value that is itself a pointer.
void test_stack_word_is_forwarded_verbatim() {
  Fixture fixture{};
  initialize(fixture);
  const OpaqueWord words[4] = {0u, 1u, 0xffffffffu, 0x80000000u};

  for (std::size_t index = 0u; index < 4u; ++index) {
    const bool released =
        argscript_formatparser_release_00841290(fixture.parser(), words[index]);
    check(released, "each invocation reports true");
    check(observed_primary.argument == words[index],
          "the stack word is forwarded bit for bit");
  }
  check(observed_primary.calls == 4u, "four invocations, four entries");

  const OpaqueWord pointer_word = word_of(&fixture.canary);
  const bool pointer_released =
      argscript_formatparser_release_00841290(fixture.parser(), pointer_word);

  check(pointer_released, "a pointer-valued word is forwarded too");
  check(observed_primary.calls == 5u, "the fifth invocation ran");
  check(observed_primary.argument == pointer_word,
        "a pointer-valued word is not truncated or rejected");
}

// Constants compared by value. The two observed vtable anchors and the gap
// between them are numbers; the slot index is 0x3c/4, not a spelling.
void test_constants_by_value() {
  check(g_dogfood_00841290_ports.release_3c == nullptr,
        "the default port table is null");
  check(sizeof(OpaqueReleasePorts) == 4, "single default-null port");
  check(vtable_0141c930 == 0x0141c930u, "first observed vtable anchor");
  check(vtable_0141c97c == 0x0141c97cu, "second observed vtable anchor");
  check(vtable_0141c97c - vtable_0141c930 == 0x4cu,
        "the gap between the anchors is 0x4c by value");
  check(vtable_0141c97c == vtable_0141c930 + 0x4cu,
        "the second anchor is the first plus the gap");
  check(0x3c / sizeof(std::uintptr_t) == 15u,
        "the slot displacement 0x3c is vtable index 15");
  check(15u * sizeof(std::uintptr_t) == kTableSlotDisplacement,
        "index 15 and displacement 0x3c are the same word");
  check(kReceiverSlotDisplacement == kTableSlotDisplacement,
        "the decoy in the receiver sits at the same displacement the body's "
        "second dereference uses on the table");
}

// The modelled signatures, pinned so a later edit cannot quietly change what the
// slot or the entry point is called with.
void test_modeled_signatures() {
  static_assert(std::is_same<decltype(&release_3c_primary), SlotSignature>::value,
                "the fake matches the modelled slot signature");
  static_assert(std::is_same<decltype(&decoy_slot), SlotSignature>::value,
                "the decoy matches the modelled slot signature");
  static_assert(std::is_same<decltype(&receiver_level_decoy), SlotSignature>::value,
                "the receiver-level decoy matches the modelled slot signature");
  static_assert(sizeof(decltype(&argscript_formatparser_release_00841290)) == 4,
                "entry point width");
  static_assert(offsetof(OpaqueFormatParserVtable, release_3c) == 0x3c,
                "the modelled slot sits at displacement 0x3c");
  static_assert(offsetof(OpaqueFormatParser, dispatch_00) == 0x00,
                "the receiver's dispatch word is at displacement 0x00");
  static_assert(sizeof(OpaqueFormatParser) == 4,
                "only the dispatch word is declared; the decoy at +0x3c is "
                "planted in a wider arena by the test");
}

int run_model() {
  g_failures = 0;
  test_dispatches_once_through_slot_3c();
  test_slot_is_read_from_the_table_not_from_the_receiver();
  test_slot_observes_the_unmodified_receiver();
  test_dispatch_target_follows_receiver_table();
  test_result_is_constant_true_whatever_the_slot_returns();
  test_stack_word_is_forwarded_verbatim();
  test_constants_by_value();
  test_modeled_signatures();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}

} // namespace

} // namespace openspore::reconstruction::pkg_orchestrate_dogfood_00841290

int main() {
  return openspore::reconstruction::pkg_orchestrate_dogfood_00841290::run_model();
}

#undef PKG_ORCHESTRATE_DOGFOOD_00841290_TEST_THISCALL
