#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "dogfood_0095fa30.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-0095fa30 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30 {
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

OpaqueWindow* argument_of(OpaqueWindowLayout* layout) {
  return reinterpret_cast<OpaqueWindow*>(layout);
}

// The modeled receiver extent from the header static_asserts.
const std::size_t kWindowExtent = 0x84u;
const std::size_t kSlotOffset = 0x80u;

std::uint8_t* bytes_of(OpaqueWindowLayout* window) {
  return reinterpret_cast<std::uint8_t*>(window);
}

void fill_pattern(OpaqueWindowLayout* window) {
  std::uint8_t* const bytes = bytes_of(window);
  for (std::size_t index = 0; index < kWindowExtent; ++index) {
    bytes[index] = static_cast<std::uint8_t>(0x11u + index);
  }
}

struct Fixture {
  OpaqueWindowLayout window{};
  OpaqueWindowLayout argument_window{};
};

void initialize_fixture(Fixture& fixture) {
  fixture.window = OpaqueWindowLayout{};
  fixture.argument_window = OpaqueWindowLayout{};
  fill_pattern(&fixture.window);
  g_dogfood_0095fa30_ports = TargetPorts{};
}

void test_stack_argument_is_stored_at_receiver_offset_0080() {
  Fixture fixture{};
  initialize_fixture(fixture);

  utfwin_window_is_ancestor_of_0095fa30(&fixture.window,
                                        argument_of(&fixture.argument_window));

  check(fixture.window.opaque_0080 == argument_of(&fixture.argument_window));
  check(word_of(fixture.window.opaque_0080) ==
        word_of(&fixture.argument_window));
}

void test_only_the_slot_word_is_written() {
  Fixture fixture{};
  initialize_fixture(fixture);

  std::uint8_t before[kWindowExtent];
  const std::uint8_t* const seed = bytes_of(&fixture.window);
  for (std::size_t index = 0; index < kWindowExtent; ++index) {
    before[index] = seed[index];
  }

  utfwin_window_is_ancestor_of_0095fa30(&fixture.window,
                                        argument_of(&fixture.argument_window));

  const std::uint8_t* const written = bytes_of(&fixture.window);
  for (std::size_t index = 0; index < kSlotOffset; ++index) {
    check(written[index] == before[index]);
  }
  const OpaqueWord stored = word_of(&fixture.argument_window);
  for (std::size_t index = 0; index < 4u; ++index) {
    check(written[kSlotOffset + index] ==
          static_cast<std::uint8_t>((stored >> (8u * index)) & 0xffu));
  }
}

void test_null_argument_is_stored_without_a_guard() {
  Fixture fixture{};
  initialize_fixture(fixture);
  fixture.window.opaque_0080 = argument_of(&fixture.argument_window);
  check(fixture.window.opaque_0080 != nullptr);

  utfwin_window_is_ancestor_of_0095fa30(&fixture.window, nullptr);

  check(fixture.window.opaque_0080 == nullptr);
  const std::uint8_t* const written = bytes_of(&fixture.window);
  check(written[0] == 0x11u);
  check(written[kSlotOffset - 1u] == static_cast<std::uint8_t>(0x11u + 0x7fu));
}

void test_repeated_call_overwrites_the_slot() {
  Fixture fixture{};
  initialize_fixture(fixture);

  utfwin_window_is_ancestor_of_0095fa30(&fixture.window,
                                        argument_of(&fixture.argument_window));
  check(fixture.window.opaque_0080 == argument_of(&fixture.argument_window));

  utfwin_window_is_ancestor_of_0095fa30(&fixture.window,
                                        argument_of(&fixture.window));
  check(fixture.window.opaque_0080 == argument_of(&fixture.window));
}

void test_ports_table_carries_no_callable_slot() {
  // The proven body has no CALL, so the table has no member to install; only
  // its extent and the single shared instance are checkable at run time.
  const TargetPorts defaults{};
  check(sizeof(defaults) == 1u);
  TargetPorts* const first = &g_dogfood_0095fa30_ports;
  TargetPorts* const second = &g_dogfood_0095fa30_ports;
  check(first == second);
}

void test_modeled_signatures() {
  using EntrySignature = void(PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL*)(
      OpaqueWindowLayout*, OpaqueWindow*);

  static_assert(
      std::is_same<decltype(&utfwin_window_is_ancestor_of_0095fa30),
                   EntrySignature>::value,
      "target is thiscall with the receiver in ECX and one stack word");
  static_assert(std::is_same<Abi0095fa30, EntrySignature>::value,
                "modeled typedef matches the declared entry");
  static_assert(offsetof(OpaqueWindowLayout, opaque_0080) == 0x80,
                "written slot stays at receiver+0x80");
  static_assert(sizeof(OpaqueWindowLayout) == 0x84,
                "modeled receiver extent stops after the written slot");
  static_assert(sizeof(decltype(&utfwin_window_is_ancestor_of_0095fa30)) == 4,
                "entry point width");
}

}

int run_model() {
  failures = 0;
  test_stack_argument_is_stored_at_receiver_offset_0080();
  test_only_the_slot_word_is_written();
  test_null_argument_is_stored_without_a_guard();
  test_repeated_call_overwrites_the_slot();
  test_ports_table_carries_no_callable_slot();
  test_modeled_signatures();
  return failures == 0 ? 0 : 1;
}

}

int main() {
  return openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30::
      run_model();
}

#undef PKG_ORCHESTRATE_DOGFOOD_0095FA30_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL
