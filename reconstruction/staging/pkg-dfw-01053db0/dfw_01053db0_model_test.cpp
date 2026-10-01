// PKG-DFW-01053DB0 -- VA 0x01053db0
// Model test for Simulator::cDefaultBeamTool::func4Ch.
//
// Plain int main(), explicit checks, no framework and no external dependency.
// The four callees this package does not own are defined here as recording
// observers; each one records the arguments it was handed and returns a value
// the test chooses, so which branch the reconstruction takes is observed rather
// than inferred.
//
// What the checks are anchored to: the 23-instruction listing and nothing else.
// Every assertion below names the instruction, or the pair of instructions, it
// is fixing, and none of them rests on a name, a type or a meaning that the
// listing does not carry.

#include "dfw_01053db0_types.hpp"

#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_dfw_01053db0 {

// One recorded step. `first` and `second` are the words the callee was handed,
// compared as uintptr_t so no pointer type is invented for them.
struct Step {
  const char* name;
  std::uintptr_t first;
  std::uintptr_t second;
};

enum { kMaxSteps = 64 };
Step g_steps[kMaxSteps];
int g_step_count = 0;

void record(const char* name, const void* first, const void* second) {
  if (g_step_count < kMaxSteps) {
    g_steps[g_step_count].name = name;
    g_steps[g_step_count].first = reinterpret_cast<std::uintptr_t>(first);
    g_steps[g_step_count].second = reinterpret_cast<std::uintptr_t>(second);
    ++g_step_count;
  }
}

// ---------------------------------------------------------------------------
// Observer state
// ---------------------------------------------------------------------------

// Value the gate observer returns for 01053de1.
std::uint8_t g_gate_result = 0;
// When set, the mark observer stores a null through g_mark_target_slot, so the
// model can see the slot change across the 01053dbf call. This is the only way
// the test can tell the re-load at 01053dc4 from a reuse of the register copy.
bool g_mark_clears_slot = false;
// Where the mark observer writes when g_mark_clears_slot is set. The test points
// it at receiver + 0x124, the displacement 01053dbf's own callee would be
// reaching if it wrote there.
void* g_mark_target_slot = nullptr;
// Value the singleton observer returns for 01053deb.
void* g_singleton_result = nullptr;

// TEST INSTRUMENT, NOT A MODEL CLAIM. The slot observer uses this to see WHEN
// the store at 01053dce happens relative to the call at 01053ddd. The listing
// gives that callee no way to reach the receiver -- it receives the target in
// ECX and nothing else -- so the back-pointer below is a probe on the harness
// side and asserts nothing about the original callee. What it observes is the
// reconstruction's own ordering, which the listing already fixes by address
// order alone.
const unsigned char* g_probe_receiver = nullptr;
std::uintptr_t g_slot_saw_owned_word = 0xffffffffu;

// ---------------------------------------------------------------------------
// The four observers for the callees this package does not own
// ---------------------------------------------------------------------------

// 01053dbf  CALL 0x00cb3c70   (ECX = the owned target, nothing pushed)
extern "C" void PKG_DFW_01053DB0_THISCALL beam_mark_00cb3c70(OpaqueBeamTarget* target) {
  record("mark", target, nullptr);
  if (g_mark_clears_slot && g_mark_target_slot != nullptr) {
    const std::uint32_t zero = 0;
    std::memcpy(g_mark_target_slot, &zero, sizeof zero);
  }
}

// 01053de1  CALL 0x0104cd50   (ECX = the receiver, nothing pushed)
extern "C" std::uint8_t PKG_DFW_01053DB0_THISCALL
beam_gate_0104cd50(const OpaqueBeamToolState* tool) {
  record("gate", tool, nullptr);
  return g_gate_result;
}

// 01053deb  CALL 0x00b3d3c0   (no argument, nothing pushed)
extern "C" void* PKG_DFW_01053DB0_CDECL beam_singleton_00b3d3c0() {
  record("singleton", nullptr, nullptr);
  return g_singleton_result;
}

// 01053df2  CALL 0x00b78860   (ECX = the accessor's EAX result, nothing pushed)
extern "C" void PKG_DFW_01053DB0_THISCALL beam_reset_00b78860(void* relationship) {
  record("reset", relationship, nullptr);
}

// The body's one indirect transfer, 01053ddd, standing in for the table word
// read at displacement 0x4 of the target's own table word. ECX is the target.
void PKG_DFW_01053DB0_THISCALL slot_observer_at_4(OpaqueBeamTarget* target) {
  record("slot", target, nullptr);
  if (g_probe_receiver != nullptr) {
    std::uint32_t seen = 0;
    std::memcpy(&seen, g_probe_receiver + 0x124, sizeof seen);
    g_slot_saw_owned_word = seen;
  }
}

// A decoy at the same 0x4 displacement of the OTHER object, so the two-level
// shape of 01053dd8/01053dda is tested rather than assumed: a reconstruction
// that read the 0x4 word from the target instead of from the table lands here
// and is caught by name, instead of jumping through a null table.
void PKG_DFW_01053DB0_THISCALL decoy_slot_observer(OpaqueBeamTarget* target) {
  record("decoy", target, nullptr);
}

namespace {

// ---------------------------------------------------------------------------
// Harness
// ---------------------------------------------------------------------------

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (condition) {
    std::printf("ok    %s\n", what);
  } else {
    ++g_failures;
    std::printf("FAIL  %s\n", what);
  }
}

// One recorded step is Step above; these two walk the recorded trace.
void reset_trace() {
  g_step_count = 0;
  for (int i = 0; i < kMaxSteps; ++i) {
    g_steps[i].name = "";
    g_steps[i].first = 0u;
    g_steps[i].second = 0u;
  }
}

bool trace_is(const char* const* expected, int count) {
  if (g_step_count != count) return false;
  for (int i = 0; i < count; ++i) {
    if (std::strcmp(g_steps[i].name, expected[i]) != 0) return false;
  }
  return true;
}

int index_of(const char* name) {
  for (int i = 0; i < g_step_count; ++i) {
    if (std::strcmp(g_steps[i].name, name) == 0) return i;
  }
  return -1;
}

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

enum { kReceiverBytes = 0x200, kTargetBytes = 0x80, kTableBytes = 0x40 };

struct Fixture {
  alignas(8) unsigned char receiver[kReceiverBytes];
  alignas(8) unsigned char target[kTargetBytes];
  alignas(8) unsigned char table[kTableBytes];
  alignas(8) unsigned char decoy_table[kTableBytes];
};

void set_owned_word(Fixture& f, const void* value) {
  std::memcpy(f.receiver + 0x124, &value, sizeof value);
}

std::uintptr_t owned_word(const Fixture& f) {
  std::uintptr_t value = 0;
  std::memcpy(&value, f.receiver + 0x124, sizeof value);
  return value;
}

void arm(Fixture& f) {
  // 01053dda  MOV EDX,dword ptr [EAX + 0x4]
  //
  // The real table carries the real slot at 0x4 and a decoy at 0x0, so reading
  // the wrong word of the right table is caught by name too.
  BeamTargetSlotFn real_slot = &slot_observer_at_4;
  BeamTargetSlotFn decoy = &decoy_slot_observer;
  std::memcpy(f.table + 0x4, &real_slot, sizeof real_slot);
  std::memcpy(f.table + 0x0, &decoy, sizeof decoy);
  std::memcpy(f.decoy_table + 0x0, &decoy, sizeof decoy);
  std::memcpy(f.decoy_table + 0x4, &real_slot, sizeof real_slot);

  // 01053dd8  MOV EAX,dword ptr [ECX]
  //
  // The target's own word at displacement zero is the real table; the decoy
  // table is planted at the target's 0x4, which the listing never reads, so
  // reaching it means the 0x4 displacement was applied to the wrong object.
  OpaqueBeamTargetVTable* table = reinterpret_cast<OpaqueBeamTargetVTable*>(f.table);
  OpaqueBeamTargetVTable* wrong = reinterpret_cast<OpaqueBeamTargetVTable*>(f.decoy_table);
  std::memcpy(f.target + 0x0, &table, sizeof table);
  std::memcpy(f.target + 0x4, &wrong, sizeof wrong);

  g_probe_receiver = f.receiver;
  g_slot_saw_owned_word = 0xffffffffu;
}

std::uint8_t run(Fixture& f) {
  reset_trace();
  g_mark_target_slot = f.receiver + 0x124;
  g_slot_saw_owned_word = 0xffffffffu;
  return dfw_01053db0_func4Ch_release(f.receiver);
}

// ---------------------------------------------------------------------------
// 1. The unconditional tail. 01053ddf is reached from the entry, from 01053dbd
//    and from 01053dcc, so the gate call at 01053de1 runs on every return.
// ---------------------------------------------------------------------------
void check_gate_always_runs(Fixture& f) {
  g_gate_result = 0;
  g_mark_clears_slot = false;
  g_singleton_result = nullptr;
  set_owned_word(f, nullptr);
  const std::uint8_t r = run(f);

  const char* const expected[] = {"gate"};
  check(trace_is(expected, 1), "01053de1: the gate is evaluated on the null-target path");
  check(index_of("gate") == 0, "01053ddf: nothing precedes the gate call");
  check(r == 0x1u, "01053df7: a null owned word still returns the constant byte");
  check(owned_word(f) == 0u, "01053dbf/01053dce: a null owned word is not written");
}

// ---------------------------------------------------------------------------
// 2. The four callees and the register each is handed. On the full path the
//    trace is mark, dispatch, gate: the mark and the dispatch both receive the
//    owned-target word (01053db5 loaded it and nothing overwrote ECX before
//    01053ddd), while the gate receives the receiver word reloaded from ESI at
//    01053ddf. Nothing is pushed for any of the three.
// ---------------------------------------------------------------------------
void check_callee_arguments(Fixture& f) {
  g_gate_result = 0;
  g_mark_clears_slot = false;
  set_owned_word(f, f.target);
  const std::uint8_t r = run(f);

  const char* const expected[] = {"mark", "slot", "gate"};
  check(trace_is(expected, 3), "01053dbf/01053ddd/01053de1: mark, dispatch, then gate");
  check(index_of("decoy") < 0,
        "01053dda: the 0x4 word is read from the table, not from the target");
  check(g_steps[0].first == reinterpret_cast<std::uintptr_t>(f.target),
        "01053dbf: ECX is the owned-target word read at 01053db5");
  check(g_steps[1].first == reinterpret_cast<std::uintptr_t>(f.target),
        "01053ddd: ECX is still the owned target, not the receiver");
  check(g_steps[2].first == reinterpret_cast<std::uintptr_t>(f.receiver),
        "01053ddf: the gate receiver is the receiver word, not the owned target");
  check(r == 0x1u, "01053df7: a released target still returns the constant byte");
}

// ---------------------------------------------------------------------------
// 3. The release sequence and its ORDER. 01053dce clears the slot before the
//    two table loads and the call, and 01053dd8/01053dda read two different
//    objects: the target's own word at displacement 0, then the word at
//    displacement 4 of whatever that named.
// ---------------------------------------------------------------------------
void check_release_order(Fixture& f) {
  g_gate_result = 0;
  g_mark_clears_slot = false;
  set_owned_word(f, f.target);
  const std::uint8_t r = run(f);

  const char* const expected[] = {"mark", "slot", "gate"};
  check(trace_is(expected, 3), "01053ddd then 01053de1: the dispatch runs before the gate");
  check(g_steps[1].first == reinterpret_cast<std::uintptr_t>(f.target),
        "01053ddd: ECX is still the owned target, not the receiver");
  check(g_slot_saw_owned_word == 0u,
        "01053dce before 01053ddd: the slot is already clear when the dispatch runs");
  check(owned_word(f) == 0u, "01053dce: the slot is left zero after the call");
  check(r == 0x1u, "01053df7: the full release path returns the constant byte");
}

// ---------------------------------------------------------------------------
// 4. 01053dc4 is a genuine SECOND load. The mark observer clears the slot across
//    the 01053dbf call, so the re-read at 01053dc4 sees a null word and
//    01053dcc jumps to 0x01053ddf: no clear, no dispatch. A reconstruction that
//    reused the register copy from 01053db5 would dispatch.
// ---------------------------------------------------------------------------
void check_second_load_is_real(Fixture& f) {
  g_gate_result = 0;
  g_mark_clears_slot = true;
  set_owned_word(f, f.target);
  const std::uint8_t r = run(f);
  g_mark_clears_slot = false;

  const char* const expected[] = {"mark", "gate"};
  check(trace_is(expected, 2), "01053dcc: a slot cleared across 01053dbf suppresses the dispatch");
  check(owned_word(f) == 0u, "01053dce: the clear is skipped on the second-null path");
  check(g_slot_saw_owned_word == 0xffffffffu,
        "01053ddd: the indirect transfer does not run when 01053dcc branches");
  check(r == 0x1u, "01053df7: the suppressed-release path returns the constant byte");
}

// ---------------------------------------------------------------------------
// 5. The relationship path. 01053de7 tests the gate byte and 01053de9 skips
//    01053deb..01053df2 when it is clear; when it is set, the accessor's result
//    becomes the next call's ECX receiver unchanged.
// ---------------------------------------------------------------------------
void check_relationship_paths(Fixture& f) {
  set_owned_word(f, nullptr);

  int token = 0;
  g_singleton_result = nullptr;
  g_gate_result = 0;
  const std::uint8_t r0 = run(f);
  const char* const skipped[] = {"gate"};
  check(trace_is(skipped, 1), "01053de9: a clear gate skips 01053deb and 01053df2 entirely");

  // A distinct non-null word, so the second call's receiver can be told apart
  // from every other pointer in the fixture.
  g_singleton_result = &token;
  g_gate_result = 0xffu;
  const std::uint8_t r1 = run(f);
  const char* const taken[] = {"gate", "singleton", "reset"};
  check(trace_is(taken, 3), "01053de7: a set gate runs the accessor and then the reset");
  check(g_steps[2].first == reinterpret_cast<std::uintptr_t>(&token),
        "01053df0: the accessor's result becomes the reset's ECX receiver unchanged");
  check(r0 == 0x1u, "01053df7: the clear-gate path returns the constant byte");
  check(r1 == 0x1u, "01053df7: the set-gate path returns the same constant byte");

  // The gate byte is a value the listing tests, not a truthiness the body
  // computes: 01053de7 is TEST AL,AL, so any non-zero byte takes the branch.
  g_gate_result = 0x01u;
  const std::uint8_t r2 = run(f);
  check(index_of("singleton") >= 0, "01053de7: a gate byte of 0x01 takes the branch");
  check(r2 == 0x1u, "01053df7: the returned byte is independent of the gate byte");

  g_singleton_result = nullptr;
  g_gate_result = 0;
}

// ---------------------------------------------------------------------------
// 6. 01053df9  RET 0x4 -- the callee pops one word.
//
// The probe reads ESP either side of a single call, so the only movement in
// between is the call itself: zero means the callee popped its own argument,
// four means it left the word for the caller.
//
// The pointer it calls through is stdcall-typed INDEPENDENTLY of how the entry
// is declared, so this is a measurement of what the entry actually emits and not
// a restatement of the header. It reaches the entry's address through void* and
// memcpy rather than by assignment, because an assignment would have to agree
// with the declaration and would then follow it; a cast would be diagnosed by
// -Wextra's -Wcast-function-type. What the probe cannot establish is anything
// about a callee that legitimately used a different convention -- the machine
// terminator is the independent evidence for that, and it is `c2 04 00 ret $0x4`
// in the compiled object.
// ---------------------------------------------------------------------------
std::uint32_t callee_stack_delta(Fixture& f) {
  using Entry = std::uint8_t(PKG_DFW_01053DB0_STDCALL*)(void*);
  Entry entry = nullptr;
  void* raw = reinterpret_cast<void*>(&dfw_01053db0_func4Ch_release);
  std::memcpy(&entry, &raw, sizeof entry);
#if defined(__i386__) && defined(__GNUC__)
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %0" : "=r"(before) :: "memory");
  (void)entry(f.receiver);
  __asm__ __volatile__("movl %%esp, %0" : "=r"(after) :: "memory");
  return before - after;
#else
  (void)entry;
  return 0u;
#endif
}

void check_stack_discipline(Fixture& f) {
  g_gate_result = 0;
  g_mark_clears_slot = false;
  set_owned_word(f, nullptr);
  (void)run(f);
  check(callee_stack_delta(f) == 0u,
        "01053df9: the callee pops its one 4-byte stack word (RET 0x4)");
}

// ---------------------------------------------------------------------------
// 7. The result byte is the only thing the body fixes about the return, and it
//    is the same constant on every reachable combination of the two conditions.
// ---------------------------------------------------------------------------
void check_return_is_constant_everywhere(Fixture& f) {
  int token = 0;
  g_singleton_result = &token;

  int same = 0;
  for (int owned_index = 0; owned_index < 2; ++owned_index) {
    for (int gate_index = 0; gate_index < 2; ++gate_index) {
      for (int clear_index = 0; clear_index < 2; ++clear_index) {
        g_gate_result = gate_index ? 0xffu : 0x00u;
        g_mark_clears_slot = clear_index != 0;
        set_owned_word(f, owned_index ? static_cast<const void*>(f.target) : nullptr);
        if (run(f) == 0x1u) ++same;
      }
    }
  }
  g_mark_clears_slot = false;
  g_gate_result = 0;
  g_singleton_result = nullptr;
  set_owned_word(f, nullptr);

  check(same == 8, "01053df7: all 8 input combinations return the same byte");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_01053db0

int main() {
  using namespace openspore::reconstruction::pkg_dfw_01053db0;

  Fixture f;
  std::memset(&f, 0, sizeof f);
  arm(f);

  check_gate_always_runs(f);
  check_callee_arguments(f);
  check_release_order(f);
  check_second_load_is_real(f);
  check_relationship_paths(f);
  check_stack_discipline(f);
  check_return_is_constant_everywhere(f);

  std::printf("\n%d/%d checks passed\n", g_checks - g_failures, g_checks);
  return g_failures == 0 ? 0 : 1;
}
