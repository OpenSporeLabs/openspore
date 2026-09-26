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

namespace openspore::reconstruction::pkg_orchestrate_dogfood_00b72370 {
namespace {

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

OpaqueWord word_of(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

struct Observation {
  OpaqueDispatchTarget* receiver;
  OpaqueWord receiver_minus_four;
  OpaqueWord source_word;
};

const std::size_t kObservationCapacity = 16;

Observation observations[kObservationCapacity]{};
std::size_t observation_count = 0;
unsigned int accessor_calls = 0;
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

void PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
operation_24(OpaqueDispatchTarget* receiver, OpaqueWord receiver_minus_four,
             OpaqueWord source_word) {
  if (observation_count < kObservationCapacity) {
    observations[observation_count].receiver = receiver;
    observations[observation_count].receiver_minus_four = receiver_minus_four;
    observations[observation_count].source_word = source_word;
  }
  ++observation_count;
}

void initialize_fixture(Fixture& fixture) {
  current_fixture = &fixture;
  observation_count = 0;
  accessor_calls = 0;
  configured_target = &fixture.target;
  fixture.pool = OpaqueObjectPoolReceiver{};
  fixture.vtable = OpaqueDispatchTargetVtable{};
  fixture.vtable.operation_24 = operation_24;
  fixture.target = OpaqueDispatchTarget{};
  fixture.target.vtable = &fixture.vtable;

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

void test_state_stores_match_disassembly() {
  Fixture fixture{};
  initialize_fixture(fixture);

  simulator_c_object_pool_delete_object_00b72370(&fixture.pool);

  check(accessor_calls == 1u);
  check(fixture.pool.dispatch_target_20 == word_of(&fixture.target));
  check(fixture.pool.receiver_minus_four_24 == expected_receiver_minus_four());
  check(fixture.pool.table_base_28 == 0x01465004u);
  check(fixture.pool.table_word_count_2c == 0x8u);
  check(fixture.pool.zero_word_30 == 0u);
}

void test_dispatch_loop_visits_eight_source_words_in_order() {
  Fixture fixture{};
  initialize_fixture(fixture);

  simulator_c_object_pool_delete_object_00b72370(&fixture.pool);

  check(observation_count == 8u);
  for (std::size_t index = 0; index < 8u; ++index) {
    check(observations[index].receiver == &fixture.target);
    check(observations[index].receiver_minus_four ==
          expected_receiver_minus_four());
    check(observations[index].source_word == kSourceTable[index]);
  }
}

void test_state_stores_precede_the_dispatch() {
  Fixture fixture{};
  initialize_fixture(fixture);
  configured_target = nullptr;

  simulator_c_object_pool_delete_object_00b72370(&fixture.pool);

  check(accessor_calls == 1u);
  check(observation_count == 0u);
  check(fixture.pool.dispatch_target_20 == 0u);
  check(fixture.pool.receiver_minus_four_24 == expected_receiver_minus_four());
  check(fixture.pool.table_base_28 == 0x01465004u);
  check(fixture.pool.table_word_count_2c == 0x8u);
  check(fixture.pool.zero_word_30 == 0u);
}

void test_source_window_is_not_rewritten() {
  Fixture fixture{};
  initialize_fixture(fixture);

  simulator_c_object_pool_delete_object_00b72370(&fixture.pool);

  for (std::size_t index = 0; index < 8u; ++index) {
    check(g_dogfood_00b72370_globals.word_01465004[index] ==
          kSourceTable[index]);
  }
}

void test_ports_are_null_by_default() {
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

  static_assert(
      std::is_same<decltype(&simulator_c_object_pool_delete_object_00b72370),
                   EntrySignature>::value,
      "target is thiscall with the receiver in ECX and no stack word");
  static_assert(
      std::is_same<OpaqueDispatchTargetOperation24, OperationSignature>::value,
      "dispatch slot takes the receiver, the receiver-minus-four "
      "word, and the source-table word");
  static_assert(
      std::is_same<OpaqueDispatchTargetGet00883860, AccessorSignature>::value,
      "accessor port stays a bare cdecl accessor with no stack word");
  static_assert(
      sizeof(decltype(&simulator_c_object_pool_delete_object_00b72370)) == 4,
      "entry point width");
}

}

int run_model() {
  failures = 0;
  test_state_stores_match_disassembly();
  test_dispatch_loop_visits_eight_source_words_in_order();
  test_state_stores_precede_the_dispatch();
  test_source_window_is_not_rewritten();
  test_ports_are_null_by_default();
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
