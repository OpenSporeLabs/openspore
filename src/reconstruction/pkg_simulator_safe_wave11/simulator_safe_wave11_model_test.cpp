#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

#include "simulator_safe_wave11.hpp"

#if defined(_MSC_VER)
#define PKG_SIMULATOR_SAFE_WAVE11_CDECL __cdecl
#define PKG_SIMULATOR_SAFE_WAVE11_THISCALL __thiscall
#else
#define PKG_SIMULATOR_SAFE_WAVE11_CDECL __attribute__((cdecl))
#define PKG_SIMULATOR_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_simulator_safe_wave11 {
namespace {

static_assert(std::is_void<decltype(dispatch_key_00628450(
                  static_cast<OpaqueObject00628*>(nullptr), TargetWord{0},
                  TargetWord{0}, TargetWord{0}))>::value,
              "00628450 returns no value on any path");
static_assert(
    std::is_same<
        decltype(cycle_key_006286a0(static_cast<OpaqueEditor00628*>(nullptr))),
        TargetWord>::value,
    "006286a0 is a thiscall on the receiver alone, with no stack argument, and "
    "returns a full unsigned word in eax");
static_assert(std::is_void<decltype(release_child_0062c910(
                  static_cast<OpaqueEditor00628*>(nullptr)))>::value,
              "0062c910 returns no value on any path");

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

enum Step : TargetWord {
  kStepProvider = 1u,
  kStepAcquire,
  kStepSlot04,
  kStepSlot08,
  kStepRandom,
  kStepInnerRelease,
};

constexpr TargetWord kStepLimit = 16u;
std::array<TargetWord, kStepLimit> g_order{};
TargetWord g_order_count = 0u;

void push_step(TargetWord step) {
  if (g_order_count < kStepLimit) {
    g_order[g_order_count] = step;
  }
  ++g_order_count;
}

template <std::size_t N>
bool order_is(const std::array<TargetWord, N>& expected) {
  if (g_order_count != expected.size()) {
    return false;
  }
  for (std::size_t i = 0u; i < expected.size(); ++i) {
    if (g_order[i] != expected[i]) {
      return false;
    }
  }
  return true;
}

struct StubObject {
  OpaqueObject00628 base;
  OpaqueVtable00628 vtable;
};

OpaqueObject00628* as_object(StubObject* stub) { return &stub->base; }

TargetWord address(const void* pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

StubObject g_provider{};
StubObject g_acquired{};
StubObject g_held_94{};
StubObject g_held_cc{};
StubObject g_held_0c{};
StubObject g_global{};

TargetWord g_provider_calls = 0u;
TargetWord g_acquire_calls = 0u;
TargetWord g_slot04_calls = 0u;
std::array<const void*, 4> g_slot04_receiver = {};
TargetWord g_slot08_calls = 0u;
TargetWord g_slot08_key[4] = {};
TargetWord g_slot08_arg2[4] = {};
TargetWord g_slot08_arg3[4] = {};
std::array<const void*, 4> g_slot08_receiver = {};
TargetByte g_slot08_result = 0u;

TargetWord g_random_calls = 0u;
TargetWord g_random_range = 0u;
TargetWord g_random_script[8] = {};
TargetWord g_random_next = 0u;
TargetWord g_random_count = 0;

TargetWord g_inner_release_calls = 0u;

void reset_counters() {
  g_order_count = 0u;
  g_provider_calls = 0u;
  g_acquire_calls = 0u;
  g_slot04_calls = 0u;
  g_slot08_calls = 0u;
  g_slot08_result = 0u;
  g_random_calls = 0u;
  g_random_range = 0u;
  g_random_next = 0u;
  g_random_count = 0u;
  g_inner_release_calls = 0u;
}

void arm_random(TargetWord first, TargetWord second, TargetWord third) {
  g_random_script[0] = first;
  g_random_script[1] = second;
  g_random_script[2] = third;
  g_random_count = 3u;
  g_random_next = 0u;
}

template <typename Fn>
TargetWord as_word(Fn fn) {
  return reinterpret_cast<TargetWord>(fn);
}

void PKG_SIMULATOR_SAFE_WAVE11_THISCALL
stub_destroy_0004(OpaqueObject00628* self) {
  push_step(kStepSlot04);
  if (g_slot04_calls < 4u) {
    g_slot04_receiver[g_slot04_calls] = self;
  }
  ++g_slot04_calls;
}

void PKG_SIMULATOR_SAFE_WAVE11_THISCALL
stub_release_0008(OpaqueObject00628* self) {
  push_step(kStepSlot08);
  if (g_slot08_calls < 4u) {
    g_slot08_receiver[g_slot08_calls] = self;
  }
  ++g_slot08_calls;
}

TargetByte PKG_SIMULATOR_SAFE_WAVE11_THISCALL stub_dispatch_0008(
    OpaqueObject00628* self, TargetWord key, TargetWord arg2, TargetWord arg3) {
  push_step(kStepSlot08);
  if (g_slot08_calls < 4u) {
    g_slot08_key[g_slot08_calls] = key;
    g_slot08_arg2[g_slot08_calls] = arg2;
    g_slot08_arg3[g_slot08_calls] = arg3;
    g_slot08_receiver[g_slot08_calls] = self;
  }
  ++g_slot08_calls;
  return g_slot08_result;
}

OpaqueObject00628* PKG_SIMULATOR_SAFE_WAVE11_THISCALL
stub_acquire_005c(OpaqueObject00628*) {
  push_step(kStepAcquire);
  ++g_acquire_calls;
  return as_object(&g_acquired);
}

OpaqueObject00628* PKG_SIMULATOR_SAFE_WAVE11_CDECL port_provider_0067ddd0() {
  push_step(kStepProvider);
  ++g_provider_calls;
  return as_object(&g_provider);
}

TargetWord PKG_SIMULATOR_SAFE_WAVE11_THISCALL
port_random_00a68fb0(TargetWord* state, TargetWord range) {
  push_step(kStepRandom);
  ++g_random_calls;
  g_random_range = range;
  ++(*state);
  return g_random_next < g_random_count ? g_random_script[g_random_next++] : 0u;
}

TargetByte PKG_SIMULATOR_SAFE_WAVE11_THISCALL
port_release_0062c340(OpaqueEditor00628*) {
  push_step(kStepInnerRelease);
  ++g_inner_release_calls;
  return 0u;
}

void clear_vtable(OpaqueVtable00628* vtable) {
  std::memset(vtable, 0, sizeof(*vtable));
}

void setup_acquire(OpaqueVtable00628* vtable) {
  clear_vtable(vtable);
  vtable->slot_5c = as_word(&stub_acquire_005c);
}

void setup_dispatch(OpaqueVtable00628* vtable) {
  clear_vtable(vtable);
  vtable->slot_08 = as_word(&stub_dispatch_0008);
}

void setup_release(OpaqueVtable00628* vtable) {
  clear_vtable(vtable);
  vtable->slot_08 = as_word(&stub_release_0008);
}

void setup_destroy(OpaqueVtable00628* vtable) {
  clear_vtable(vtable);
  vtable->slot_04 = as_word(&stub_destroy_0004);
}

void bind_stub(StubObject* stub, void (*setup)(OpaqueVtable00628*)) {
  setup(&stub->vtable);
  stub->base.vtable = &stub->vtable;
}

struct PortScope {
  SimulatorRuntime00628 saved;
  bool script_random;

  explicit PortScope(bool use_scripted_random)
      : saved(simulator_runtime_00628()), script_random(use_scripted_random) {
    simulator_runtime_00628().provider_0067ddd0 = port_provider_0067ddd0;
    if (script_random) {
      simulator_runtime_00628().random_00a68fb0 = port_random_00a68fb0;
    }
    simulator_runtime_00628().release_0062c340 = port_release_0062c340;
  }

  ~PortScope() { simulator_runtime_00628() = saved; }

  PortScope(const PortScope&) = delete;
  PortScope& operator=(const PortScope&) = delete;
};

struct Fixture {
  PortScope ports;
  OpaqueEditor00628 editor;
  OpaqueVtable00628 blend_vtable;

  explicit Fixture(bool use_scripted_random = true)
      : ports(use_scripted_random) {
    std::memset(&editor, 0, sizeof(editor));
    std::memset(&blend_vtable, 0, sizeof(blend_vtable));
    reset_counters();

    bind_stub(&g_provider, setup_acquire);
    bind_stub(&g_acquired, setup_dispatch);
    bind_stub(&g_held_94, setup_destroy);
    bind_stub(&g_held_cc, setup_release);
    bind_stub(&g_held_0c, setup_destroy);
    bind_stub(&g_global, setup_release);

    blend_vtable.slot_08 = as_word(&stub_release_0008);
    editor.vtable = &blend_vtable;
    editor.field_3588.vtable = &blend_vtable;
    editor.field_0c = as_object(&g_provider);
    editor.field_cc = as_object(&g_held_cc);
    editor.field_3614 = nullptr;
    simulator_runtime_00628().global_015f7cf4 = nullptr;
    simulator_runtime_00628().random_state_01601760 = 0u;
  }
};

void test_dispatch_accepts_once() {
  Fixture fixture;
  g_slot08_result = 1u;
  dispatch_key_00628450(nullptr, 0x11223344u, 0x55667788u, 0x99aabbccu);
  check(g_provider_calls == 1u, "00628450 fetches the provider once");
  check(g_acquire_calls == 1u, "00628450 acquires once through slot 0x5c");
  check(g_slot08_calls == 1u, "00628450 dispatches once when accepted");
  check(g_slot08_key[0] == 0x11223344u, "00628450 forwards the key");
  check(g_slot08_arg2[0] == 0u, "00628450 pushes a zero middle argument");
  check(g_slot08_arg3[0] == 0x99aabbccu, "00628450 forwards the context");
  check(g_slot08_receiver[0] == as_object(&g_acquired),
        "00628450 dispatches on the acquired object");
}

void test_dispatch_falls_back() {
  Fixture fixture;
  g_slot08_result = 0u;
  dispatch_key_00628450(nullptr, 0x11223344u, 0x55667788u, 0x99aabbccu);
  check(g_slot08_calls == 2u, "00628450 dispatches twice when refused");
  check(g_slot08_key[1] == 0xe18d6423u,
        "00628450 replays the fallback key 0xe18d6423");
  check(g_slot08_arg2[1] == 0u,
        "00628450 pushes a zero middle argument on the fallback");
  check(g_slot08_arg3[1] == 0x99aabbccu,
        "00628450 keeps the context on the fallback");
  const std::array<TargetWord, 4> expected = {kStepProvider, kStepAcquire,
                                              kStepSlot08, kStepSlot08};
  check(order_is(expected), "00628450 acquires before it dispatches");
}

void test_dispatch_keeps_supplied_subject() {
  Fixture fixture;
  g_slot08_result = 1u;
  dispatch_key_00628450(as_object(&g_acquired), 0x1u, 0x2u, 0x3u);
  check(g_provider_calls == 0u, "00628450 skips the provider when supplied");
  check(g_acquire_calls == 0u, "00628450 skips the acquire when supplied");
  check(g_slot08_calls == 1u, "00628450 dispatches on the supplied subject");
  check(g_slot08_receiver[0] == as_object(&g_acquired),
        "00628450 keeps the supplied subject as the receiver");
}

void test_cycle_default_lcg() {
  Fixture fixture(false);
  const TargetWord first = cycle_key_006286a0(&fixture.editor);
  check(first == 0x0431df93u, "006286a0 maps the first lcg draw to 0x0431df93");
  check(simulator_runtime_00628().random_state_01601760 == 0x00003039u,
        "006286a0 leaves the lcg state at 0x00003039 after one draw");
  check(fixture.editor.state_36d4 == first,
        "006286a0 stores the accepted candidate at +0x36d4");
  const TargetWord second = cycle_key_006286a0(&fixture.editor);
  check(second == 0x044d7999u,
        "006286a0 redraws past a collision and lands on 0x044d7999");
  check(simulator_runtime_00628().random_state_01601760 == 0xa70427dfu,
        "006286a0 advances the lcg state to 0xa70427df after two draws");
  check(fixture.editor.state_36d4 == second,
        "006286a0 overwrites +0x36d4 with the later candidate");
}

void test_cycle_candidate_table() {
  const TargetWord expected[6] = {0x0431df93u, 0x0431df9au, 0x0431df9fu,
                                  0x0431dfa6u, 0x044d798cu, 0x044d7999u};
  for (TargetWord draw = 0u; draw < 6u; ++draw) {
    Fixture fixture;
    arm_random(draw, 0u, 0u);
    fixture.editor.state_36d4 = 0u;
    const TargetWord got = cycle_key_006286a0(&fixture.editor);
    check(got == expected[draw], "006286a0 maps a draw to its candidate");
    check(g_random_calls == 1u, "006286a0 accepts the first draw");
    check(g_random_range == 6u, "006286a0 draws from a range of six");
  }
}

void test_cycle_out_of_range_keeps_receiver_id() {
  Fixture fixture;
  arm_random(9u, 0u, 0u);
  fixture.editor.state_36d4 = 0u;
  const TargetWord got = cycle_key_006286a0(&fixture.editor);
  check(got == address(&fixture.editor),
        "006286a0 keeps the receiver derived id above the draw range");
  check(g_random_calls == 1u, "006286a0 leaves a distinct receiver id alone");
  check(fixture.editor.state_36d4 == address(&fixture.editor),
        "006286a0 stores the receiver derived id at +0x36d4");
}

void test_cycle_receiver_id_retries() {
  Fixture fixture;
  arm_random(9u, 0u, 0u);
  fixture.editor.state_36d4 = address(&fixture.editor);
  const TargetWord got = cycle_key_006286a0(&fixture.editor);
  check(got == 0x0431df93u,
        "006286a0 redraws while the receiver id collides with the stored one");
  check(g_random_calls == 2u,
        "006286a0 redraws once past the colliding receiver id");
  check(fixture.editor.state_36d4 == 0x0431df93u,
        "006286a0 stores the accepted candidate over the receiver id");
}

void test_cycle_retries_on_collision() {
  Fixture fixture;
  arm_random(0u, 0u, 1u);
  fixture.editor.state_36d4 = 0x0431df93u;
  const TargetWord got = cycle_key_006286a0(&fixture.editor);
  check(got == 0x0431df9au, "006286a0 redraws past a colliding candidate");
  check(g_random_calls == 3u, "006286a0 redraws once per collision");
  check(fixture.editor.state_36d4 == 0x0431df9au,
        "006286a0 overwrites +0x36d4 with the accepted candidate");
}

void test_release_order() {
  Fixture fixture;
  fixture.editor.field_94 = as_object(&g_held_94);
  fixture.editor.field_0c = as_object(&g_held_0c);
  simulator_runtime_00628().global_015f7cf4 = as_object(&g_global);
  release_child_0062c910(&fixture.editor);
  const std::array<TargetWord, 5> expected = {
      kStepSlot04, kStepSlot08, kStepSlot08, kStepSlot08, kStepSlot04};
  check(order_is(expected), "0062c910 releases in the recorded order");
  check(g_slot04_receiver[0] == as_object(&g_held_94),
        "0062c910 destroys the +0x94 holder first");
  check(g_slot04_receiver[1] == as_object(&g_held_0c),
        "0062c910 destroys the +0x0c holder last, as the tail transfer");
  check(g_slot08_receiver[0] == as_object(&g_held_cc),
        "0062c910 releases the +0xcc holder first");
  check(g_slot08_receiver[1] == &fixture.editor.field_3588,
        "0062c910 releases the +0x3588 blend against its own address");
  check(g_slot08_receiver[2] == as_object(&g_global),
        "0062c910 releases the global holder third");
  check(g_inner_release_calls == 0u,
        "0062c910 skips the inner release on an empty +0xc8 slot");
  check(fixture.editor.field_94 == nullptr, "0062c910 clears the +0x94 slot");
  check(fixture.editor.field_cc == nullptr, "0062c910 clears the +0xcc slot");
  check(fixture.editor.field_0c == nullptr, "0062c910 clears the +0x0c slot");
  check(simulator_runtime_00628().global_015f7cf4 == nullptr,
        "0062c910 clears the global slot");
}

void test_release_runs_inner_release() {
  Fixture fixture;
  simulator_runtime_00628().global_015f7cf4 = as_object(&g_global);
  fixture.editor.field_0c = nullptr;
  release_child_0062c910(&fixture.editor);
  check(g_inner_release_calls == 0u,
        "0062c910 gates the inner release on the +0xc8 slot only");
  check(g_slot04_calls == 0u, "0062c910 destroys nothing without a +0x94 slot");
}

void test_release_unconditional_ports() {
  Fixture fixture;
  fixture.editor.field_0c = nullptr;
  release_child_0062c910(&fixture.editor);
  const std::array<TargetWord, 2> expected = {kStepSlot08, kStepSlot08};
  check(order_is(expected), "0062c910 crosses only the unconditional ports");
  check(g_slot08_receiver[0] == as_object(&g_held_cc),
        "0062c910 keeps the +0xcc port first");
  check(g_slot08_receiver[1] == &fixture.editor.field_3588,
        "0062c910 always releases the +0x3588 blend");
  check(g_inner_release_calls == 0u,
        "0062c910 skips the inner release on an empty +0xc8 slot");
  check(fixture.editor.field_cc == nullptr,
        "0062c910 still clears the +0xcc slot");
  check(fixture.editor.field_0c == nullptr,
        "0062c910 leaves an empty +0x0c slot null");
  check(fixture.editor.field_94 == nullptr,
        "0062c910 leaves an empty +0x94 slot null");
}

}  // namespace

}  // namespace openspore::reconstruction::pkg_simulator_safe_wave11

int main() {
  using namespace openspore::reconstruction::pkg_simulator_safe_wave11;
  test_dispatch_accepts_once();
  test_dispatch_falls_back();
  test_dispatch_keeps_supplied_subject();
  test_cycle_default_lcg();
  test_cycle_candidate_table();
  test_cycle_out_of_range_keeps_receiver_id();
  test_cycle_receiver_id_retries();
  test_cycle_retries_on_collision();
  test_release_order();
  test_release_runs_inner_release();
  test_release_unconditional_ports();

  if (g_failures == 0) {
    std::printf("ok: simulator safe wave11 model checks passed\n");
  } else {
    std::printf("failed: %d simulator safe wave11 model checks\n", g_failures);
  }
  return g_failures == 0 ? 0 : 1;
}
