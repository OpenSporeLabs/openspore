#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "dogfood_005c5ee0.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-005c5ee0 requires MSVC or GCC CCs"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0 {
namespace {

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

enum EventId : unsigned int {
  kEventNone = 0u,
  kEventTeardown = 1u,
  kEventRelease = 2u
};

const std::size_t kEventCapacity = 4;

EventId events[kEventCapacity]{};
std::size_t event_count = 0;
unsigned int teardown_calls = 0;
unsigned int release_calls = 0;
OpaquePaletteMain* teardown_receivers[kEventCapacity]{};
void* release_arguments[kEventCapacity]{};

void record_event(EventId event) {
  if (event_count < kEventCapacity) {
    events[event_count] = event;
  }
  ++event_count;
}

void PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL
teardown_005c5e90(OpaquePaletteMain* main) {
  if (teardown_calls < kEventCapacity) {
    teardown_receivers[teardown_calls] = main;
  }
  ++teardown_calls;
  record_event(kEventTeardown);
}

void PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL release_00f47380(void* pointer) {
  if (release_calls < kEventCapacity) {
    release_arguments[release_calls] = pointer;
  }
  ++release_calls;
  record_event(kEventRelease);
}

struct Fixture {
  OpaquePaletteMain main{};
  OpaquePaletteMainVtable vtable{};
  OpaquePaletteMainSubobjectVtable subobject_vtable{};
};

void initialize_fixture(Fixture& fixture) {
  event_count = 0;
  teardown_calls = 0;
  release_calls = 0;
  for (std::size_t index = 0; index < kEventCapacity; ++index) {
    events[index] = kEventNone;
    teardown_receivers[index] = nullptr;
    release_arguments[index] = nullptr;
  }

  fixture.main = OpaquePaletteMain{};
  fixture.vtable = OpaquePaletteMainVtable{};
  fixture.vtable.slot_00 = &palettes_palette_main_get_category_005c5ee0;
  fixture.vtable.slot_04 = 0x00804901u;
  fixture.subobject_vtable = OpaquePaletteMainSubobjectVtable{};
  fixture.subobject_vtable.slot_00 = 0x00ae4340u;
  fixture.subobject_vtable.slot_04 = 0x00ae4330u;
  fixture.subobject_vtable.slot_08 = 0x005c5e80u;
  fixture.subobject_vtable.slot_0c = 0x005c5bf0u;
  fixture.main.vtable_00 = &fixture.vtable;
  fixture.main.vtable_08 =
      reinterpret_cast<std::uintptr_t>(&fixture.subobject_vtable);

  g_dogfood_005c5ee0_ports = GetCategoryPorts{};
  g_dogfood_005c5ee0_ports.teardown_005c5e90 = teardown_005c5e90;
  g_dogfood_005c5ee0_ports.release_00f47380 = release_00f47380;
}

// 0x005c5ee3 calls 0x005c5e90 with no push, so the teardown happens once,
// before any branch, with the receiver word untouched.
void test_teardown_runs_first_and_unconditionally() {
  Fixture fixture{};
  initialize_fixture(fixture);

  palettes_palette_main_get_category_005c5ee0(&fixture.main, 0u);

  check(teardown_calls == 1u);
  check(teardown_receivers[0] == &fixture.main);
  check(event_count == 1u);
  check(events[0] == kEventTeardown);
}

// 0x005c5ee8 tests bit 0 only, and 0x005c5eed skips the release when it is
// clear. Words with other bits set must not release.
void test_release_runs_only_when_bit0_is_set() {
  const OpaqueWord words[4] = {0x00000000u, 0x00000001u, 0x00000002u,
                               0x00000003u};
  const bool expected_release[4] = {false, true, false, true};

  for (std::size_t index = 0; index < 4u; ++index) {
    Fixture fixture{};
    initialize_fixture(fixture);

    palettes_palette_main_get_category_005c5ee0(&fixture.main, words[index]);

    check(teardown_calls == 1u);
    if (expected_release[index]) {
      check(release_calls == 1u);
      check(event_count == 2u);
      check(events[0] == kEventTeardown);
      check(events[1] == kEventRelease);
    } else {
      check(release_calls == 0u);
      check(event_count == 1u);
      check(events[0] == kEventTeardown);
    }
  }
}

// 0x005c5eef pushes ESI, the saved receiver, so the release port receives the
// receiver and not the stack word or the teardown result.
void test_release_receives_the_receiver_word() {
  Fixture fixture{};
  initialize_fixture(fixture);

  palettes_palette_main_get_category_005c5ee0(&fixture.main, 0x00000001u);

  check(release_calls == 1u);
  check(release_arguments[0] == static_cast<void*>(&fixture.main));
  check(teardown_receivers[0] == &fixture.main);
}

// 0x005c5ef8 loads EAX with the saved receiver on both paths, so the returned
// word is the receiver even on the path that released it.
void test_return_value_is_the_receiver_on_both_paths() {
  Fixture fixture{};
  initialize_fixture(fixture);

  check(palettes_palette_main_get_category_005c5ee0(&fixture.main, 0u) ==
        &fixture.main);
  check(release_calls == 0u);

  check(palettes_palette_main_get_category_005c5ee0(&fixture.main, 1u) ==
        &fixture.main);
  check(release_calls == 1u);
}

// There is no null test anywhere in the eleven instructions, so a null receiver
// reaches both ports unchanged instead of being filtered.
void test_null_receiver_reaches_both_ports_unguarded() {
  Fixture fixture{};
  initialize_fixture(fixture);

  check(palettes_palette_main_get_category_005c5ee0(nullptr, 0x00000001u) ==
        nullptr);

  check(teardown_calls == 1u);
  check(teardown_receivers[0] == nullptr);
  check(release_calls == 1u);
  check(release_arguments[0] == nullptr);
}

// The body never dereferences the receiver: it stores no receiver word, so the
// two published vtable words survive untouched.
void test_receiver_words_are_never_written() {
  Fixture fixture{};
  initialize_fixture(fixture);
  const OpaquePaletteMainVtable* const before_vtable_00 =
      fixture.main.vtable_00;
  const std::uintptr_t before_word_04 = fixture.main.word_04;
  const std::uintptr_t before_vtable_08 = fixture.main.vtable_08;

  palettes_palette_main_get_category_005c5ee0(&fixture.main, 0x00000001u);

  check(fixture.main.vtable_00 == before_vtable_00);
  check(fixture.main.word_04 == before_word_04);
  check(fixture.main.vtable_08 == before_vtable_08);
  check(fixture.vtable.slot_00 == &palettes_palette_main_get_category_005c5ee0);
  check(fixture.vtable.slot_04 == 0x00804901u);
}

// The zero-initialized ports table must not be callable, so the body is only
// usable once a host installs both slots.
void test_ports_default_to_null() {
  const GetCategoryPorts defaults{};
  check(defaults.teardown_005c5e90 == nullptr);
  check(defaults.release_00f47380 == nullptr);
  check(sizeof(GetCategoryPorts) == 8);
}

void test_modeled_signatures() {
  using EntrySignature = OpaquePaletteMain*(
      PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL*)(OpaquePaletteMain*,
                                                  OpaqueWord);
  using TeardownSignature =
      void(PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL*)(OpaquePaletteMain*);
  using ReleaseSignature = void(PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL*)(void*);

  static_assert(
      std::is_same<decltype(&palettes_palette_main_get_category_005c5ee0),
                   EntrySignature>::value,
      "entry is thiscall with the receiver in ECX and one stack word");
  static_assert(
      std::is_same<OpaquePaletteMainGetCategory005c5ee0, EntrySignature>::value,
      "vtable slot 0x00 carries the entry point shape");
  static_assert(
      std::is_same<OpaquePaletteMainTeardown005c5e90, TeardownSignature>::value,
      "0x005c5e90 port takes the receiver and no stack word");
  static_assert(
      std::is_same<OpaquePaletteMainRelease00f47380, ReleaseSignature>::value,
      "0x00f47380 port is cdecl with one reclaimed stack word");
  static_assert(
      sizeof(decltype(&palettes_palette_main_get_category_005c5ee0)) == 4,
      "entry point width");
}

}

int run_model() {
  failures = 0;
  test_teardown_runs_first_and_unconditionally();
  test_release_runs_only_when_bit0_is_set();
  test_release_receives_the_receiver_word();
  test_return_value_is_the_receiver_on_both_paths();
  test_null_receiver_reaches_both_ports_unguarded();
  test_receiver_words_are_never_written();
  test_ports_default_to_null();
  test_modeled_signatures();
  return failures == 0 ? 0 : 1;
}

}

int main() {
  return openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::
      run_model();
}

#undef PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL
