#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "dogfood_00b72370.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-00b72370 requires MSVC or GCC CCs"
#endif

// Semantic test for Simulator::cObjectPool_::DeleteObject @ 0x00b72370.
//
// Everything asserted here is a property of the 31-instruction body at
// 0x00b72370..0x00b723c0, not of the C++ spelling: the publish order, the two
// guard arms, the eight-iteration bound, the callee-visible stack order of the
// dispatched call, and the per-iteration re-read of the vtable slot.
namespace openspore::reconstruction::pkg_orchestrate_dogfood_00b72370 {
namespace {

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

struct Observation {
  OpaqueDispatchTarget* receiver;
  OpaqueWord receiver_minus_four;
  OpaqueWord source_word;
  const char* handler;
};

const std::size_t kObservationCapacity = 16;

Observation observations[kObservationCapacity]{};
std::size_t observation_count = 0;
unsigned int accessor_calls = 0;
unsigned int first_handler_calls = 0;
unsigned int second_handler_calls = 0;
OpaqueDispatchTarget* configured_target = nullptr;

// The live 0x01465004 window read from SporeApp.exe; the eight loop words.
const OpaqueWord kSourceTable[8] = {0x025630b7u, 0x0477c00du, 0x031018b9u,
                                    0x02e9973eu, 0x032f76e7u, 0x04d80d9eu,
                                    0x00f62defu, 0x0182c582u};

struct Fixture {
  OpaqueObjectPoolReceiver pool{};
  OpaqueDispatchTarget target{};
  OpaqueDispatchTargetVtable vtable{};
};

Fixture* current_fixture = nullptr;

OpaqueDispatchTarget* PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL
acquire_dispatch_target_00883860() {
  ++accessor_calls;
  return configured_target;
}

void record(OpaqueDispatchTarget* receiver, OpaqueWord receiver_minus_four,
            OpaqueWord source_word, const char* handler) {
  if (observation_count < kObservationCapacity) {
    observations[observation_count].receiver = receiver;
    observations[observation_count].receiver_minus_four = receiver_minus_four;
    observations[observation_count].source_word = source_word;
    observations[observation_count].handler = handler;
  }
  ++observation_count;
}

void PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
operation_24(OpaqueDispatchTarget* receiver, OpaqueWord receiver_minus_four,
             OpaqueWord source_word) {
  ++first_handler_calls;
  record(receiver, receiver_minus_four, source_word, "operation_24");
}

void PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
replacement_operation_24(OpaqueDispatchTarget* receiver,
                         OpaqueWord receiver_minus_four,
                         OpaqueWord source_word) {
  ++second_handler_calls;
  record(receiver, receiver_minus_four, source_word, "replacement");
}

void initialize_fixture(Fixture& fixture) {
  current_fixture = &fixture;
  observation_count = 0;
  accessor_calls = 0;
  first_handler_calls = 0;
  second_handler_calls = 0;
  configured_target = &fixture.target;
  fixture.pool = OpaqueObjectPoolReceiver{};
  fixture.vtable = OpaqueDispatchTargetVtable{};
  fixture.vtable.operation_24 = operation_24;
  fixture.target = OpaqueDispatchTarget{};
  fixture.target.vtable_00 = &fixture.vtable;

  g_dogfood_00b72370_ports = DeleteObjectPorts{};
  g_dogfood_00b72370_ports.acquire_dispatch_target_00883860 =
      acquire_dispatch_target_00883860;
  g_dogfood_00b72370_globals = DeleteObjectGlobals{};
  for (std::size_t index = 0; index < 8u; ++index) {
    g_dogfood_00b72370_globals.word_01465004[index] = kSourceTable[index];
  }
}

OpaqueWord expected_receiver_minus_four() {
  return word_of(&current_fixture->pool) - 4u;
}

void test_published_record_matches_the_five_stores() {
  Fixture fixture{};
  initialize_fixture(fixture);

  delete_object_model(&fixture.pool);

  check(accessor_calls == 1u);
  check(fixture.pool.record_target_20 == &fixture.target);
  check(fixture.pool.record_token_24 == expected_receiver_minus_four());
  check(fixture.pool.record_source_base_28 == 0x01465004u);
  check(fixture.pool.record_source_word_count_2c == 0x8u);
  check(fixture.pool.record_trailing_30 == 0u);
  // The five stores are one contiguous 0x14-byte descriptor at +0x20.
  const PublishedDeleteRecord* const record = reinterpret_cast<
      const PublishedDeleteRecord*>(reinterpret_cast<std::uint8_t*>(&fixture.pool) +
                                    kRecordBaseOffset);
  check(record->target_00 == &fixture.target);
  check(record->token_04 == expected_receiver_minus_four());
  check(record->source_base_08 == kSourceTableVa);
  check(record->source_word_count_0c == kSourceTableWordCount);
  check(record->trailing_10 == 0u);
}

void test_loop_visits_eight_source_words_in_ascending_order() {
  Fixture fixture{};
  initialize_fixture(fixture);

  delete_object_model(&fixture.pool);

  check(observation_count == 8u);
  check(first_handler_calls == 8u);
  for (std::size_t index = 0; index < 8u; ++index) {
    check(observations[index].receiver == &fixture.target);
    check(observations[index].receiver_minus_four ==
          expected_receiver_minus_four());
    check(observations[index].source_word == kSourceTable[index]);
  }
}

void test_source_window_is_never_rewritten() {
  Fixture fixture{};
  initialize_fixture(fixture);

  delete_object_model(&fixture.pool);

  for (std::size_t index = 0; index < 8u; ++index) {
    check(g_dogfood_00b72370_globals.word_01465004[index] ==
          kSourceTable[index]);
  }
}

void test_slot_word_is_reread_on_every_iteration() {
  Fixture fixture{};
  initialize_fixture(fixture);

  // 0x00b723aa/0x00b723ac reload the vtable pointer and the slot word on every
  // pass, so overwriting the slot between two passes changes the callee.
  fixture.vtable.operation_24 = operation_24;
  delete_object_model(&fixture.pool);
  check(first_handler_calls == 8u);
  check(second_handler_calls == 0u);

  // Second run with the slot already pointing at the replacement: all eight
  // iterations go to the replacement, never to the original.
  observation_count = 0;
  first_handler_calls = 0;
  second_handler_calls = 0;
  fixture.vtable.operation_24 = replacement_operation_24;
  delete_object_model(&fixture.pool);
  check(first_handler_calls == 0u);
  check(second_handler_calls == 8u);
}

void test_null_dispatch_target_still_publishes_and_dispatches_nothing() {
  Fixture fixture{};
  initialize_fixture(fixture);
  configured_target = nullptr;

  delete_object_model(&fixture.pool);

  check(accessor_calls == 1u);
  check(observation_count == 0u);
  check(fixture.pool.record_target_20 == nullptr);
  check(fixture.pool.record_token_24 == expected_receiver_minus_four());
  check(fixture.pool.record_source_base_28 == 0x01465004u);
  check(fixture.pool.record_source_word_count_2c == 0x8u);
  check(fixture.pool.record_trailing_30 == 0u);
}

void test_null_token_word_skips_the_loop_after_publishing() {
  Fixture fixture{};
  initialize_fixture(fixture);

  // 0x00b7239e TEST EBX,EBX / 0x00b723a0 JZ: the second guard arm. Driven
  // through the split body because reaching it through the entry function would
  // need a receiver word of 0x4, and the unconditional stores that precede the
  // test would then fault.
  publish_and_dispatch_delete_record(&fixture.pool, &fixture.target, nullptr);

  check(observation_count == 0u);
  check(fixture.pool.record_target_20 == &fixture.target);
  check(fixture.pool.record_token_24 == 0u);
  check(fixture.pool.record_source_base_28 == kSourceTableVa);
  check(fixture.pool.record_source_word_count_2c == kSourceTableWordCount);
  check(fixture.pool.record_trailing_30 == 0u);
}

void test_ports_and_globals_default_to_null() {
  const DeleteObjectPorts defaults{};
  check(defaults.acquire_dispatch_target_00883860 == nullptr);
  const DeleteObjectGlobals empty_globals{};
  for (std::size_t index = 0; index < 8u; ++index) {
    check(empty_globals.word_01465004[index] == 0u);
  }
}

void test_modeled_signatures() {
  using EntrySignature = void(PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL*)(
      OpaqueObjectPoolReceiver*);
  using OperationSignature = void(PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL*)(
      OpaqueDispatchTarget*, OpaqueWord, OpaqueWord);
  using AccessorSignature =
      OpaqueDispatchTarget*(PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL*)();

  static_assert(std::is_same<decltype(&delete_object_00b72370),
                             EntrySignature>::value,
                "target is thiscall with the receiver in ECX and no stack word");
  static_assert(
      std::is_same<OpaqueDispatchTargetOperation24, OperationSignature>::value,
      "dispatch slot takes the receiver, the receiver-minus-four word, and "
      "the source-table word");
  static_assert(
      std::is_same<OpaqueDispatchTargetGet00883860, AccessorSignature>::value,
      "accessor port stays a bare cdecl accessor with no stack word");
  static_assert(sizeof(decltype(&delete_object_00b72370)) == 4,
                "entry point width");
  static_assert(kStackCleanupBytes == 0u,
                "0x00b723c0 is a plain RET, so the callee pops nothing");
  static_assert(kDispatchSlotDisplacement == 0x24u,
                "0x00b723ac reads the slot at displacement 0x24");
  static_assert(kSourceTableWindowBytes == 0x20u,
                "0x00b723b8 compares the byte index against 0x20");
}

}

int run_model() {
  failures = 0;
  test_published_record_matches_the_five_stores();
  test_loop_visits_eight_source_words_in_ascending_order();
  test_source_window_is_never_rewritten();
  test_slot_word_is_reread_on_every_iteration();
  test_null_dispatch_target_still_publishes_and_dispatches_nothing();
  test_null_token_word_skips_the_loop_after_publishing();
  test_ports_and_globals_default_to_null();
  test_modeled_signatures();
  return failures == 0 ? 0 : 1;
}

}

int main() {
  return openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::
      run_model();
}

#undef PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
