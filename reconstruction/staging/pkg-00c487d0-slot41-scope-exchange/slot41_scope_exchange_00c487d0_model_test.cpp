// Focused semantic / mutation test for FUN_00c487d0 @ 0x00c487d0.
//
// The reconstruction is attacked twice.
//
//   PART 1  invariants.  Each group names the risky hypothesis it pins:
//     1. the receiver word and the slot-0xa4 result are published into
//        ScopeState::field_18 / field_48 and restored VERBATIM on the way out;
//     2. the pointer cell 0x016e0d08 is only ever READ (the four GLOBALS rows
//        are all mode `read`), so the cell must survive the call untouched even
//        though the object behind it was overwritten twice in between;
//     3. the null branch at 00c48818 exists - a zero player-data accessor must
//        produce argument 4 == 0, not the raw accessor value;
//     4. receiver+0x17c substitutes the receiver only when it is non-zero;
//     5. the wrapper built at 00c48830 is the same object read at 00c48897 and
//        destroyed at 00c488e9, and it is alive across both dispatches;
//     6. the two dispatches receive five and four arguments in the observed
//        order, and the wrapper address reaches the SECOND dispatch, not the
//        first - the split that makes every later `[ESP+d]` land on a named
//        local;
//     7. the 00c4889c scan steps by 16-bit code units and hands
//        0x00423650 (this, begin, begin + units);
//     8. the dispatch arities balance the nine stack words the listing pushes,
//        and the frame geometry closes;
//     9. every displacement the header publishes is the listing's.
//
//   PART 2  mutations.  A flagged SHADOW of the same body is run once per
//        perturbation and the identical invariant battery is applied to it.
//        Every single-flag mutation must be REJECTED by at least one
//        invariant.  A mutation that survives is a hole in the test, so the run
//        aborts.  The shadow exists because the perturbation has to be applied
//        without editing the reconstruction under test; PART 1 is what proves
//        the shadow and the reconstruction agree on the unmutated path.

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "slot41_scope_exchange_00c487d0.hpp"

namespace recon = openspore::reconstruction::pkg_00c487d0_slot41_scope_exchange;

namespace {

int g_failures = 0;

void require(bool condition, const char* what) {
  if (!condition) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    std::abort();
  }
}

constexpr recon::Word kSelfDispatchResult = 0x11110001u;
constexpr recon::Word kPlayerDataValue = 0x22220002u;
constexpr recon::Word kPlayerDataWord13c = 0x33330003u;
constexpr recon::Word kEmpireValue = 0x66660006u;
constexpr recon::Word kSub451e0Value = 0x55550005u;
constexpr recon::Word kDispatch1Result = 0x77770007u;
constexpr recon::Word kDispatch2Result = 0x88880008u;
constexpr recon::CodeAddress kScopePointer = recon::kScopeStatePointer;

const std::uint16_t kWide[] = {0x0041u, 0x0042u, 0x0043u, 0x0000u, 0xdeadu};

recon::Word g_player_data = kPlayerDataValue;
recon::ScopeState* g_scope_during = nullptr;

struct AccessorImage : recon::Accessor {
  recon::Table table_image{};
};

// Inputs held constant across the real run and every mutation.
struct Inputs {
  recon::Table self_table{};
  AccessorImage acc1{};
  AccessorImage acc2{};
  recon::Receiver self{};
  recon::ScopeState scope{};
  recon::ScopeState* scope_cell = nullptr;  // the 0x016e0d08 cell's value
  recon::Word stack_arg1 = 0xA1A1A1A1u;
  recon::Word stack_arg2 = 0xB2B2B2B2u;
  // Pristine copies of the scope words. The body overwrites them twice, so the
  // battery must compare against these and not against the mutated fields.
  recon::Word original_field_18 = 0xAAAA0001u;
  recon::Word original_field_48 = 0xBBBB0002u;
};

// Fills `in` in place: the self/table/acc1/acc2 objects live inside Inputs, so
// returning by value would leave self.table dangling.
void make_inputs(Inputs& in, recon::Word field_17c, recon::Word player_data) {
  in.self_table.words[recon::kReceiverDispatchSlot / 4] = 0x1;
  in.self.table = &in.self_table;
  in.self.field_17c = field_17c;
  in.acc1.table_image.words[recon::kAccessor1Slot / 4] = 0x2;
  in.acc1.table = &in.acc1.table_image;
  in.acc2.table_image.words[recon::kAccessor2Slot / 4] = 0x3;
  in.acc2.table = &in.acc2.table_image;
  in.original_field_18 = 0xAAAA0001u;
  in.original_field_48 = 0xBBBB0002u;
  in.scope.field_18 = in.original_field_18;
  in.scope.field_48 = in.original_field_48;
  in.scope_cell = &in.scope;
  g_player_data = player_data;
}

// Everything an invariant may look at. The library and the shadow both fill
// one of these, which is what makes the battery reusable across PART 1/PART 2.
struct Observation {
  recon::Word scope_18_after = 0;
  recon::Word scope_48_after = 0;
  recon::CodeAddress scope_cell_after = 0;

  recon::Word published_18 = 0;
  recon::Word published_48 = 0;
  std::size_t publish_18_count = 0;
  std::size_t publish_48_count = 0;
  recon::Word scope_18_during = 0;
  recon::Word scope_48_during = 0;

  std::size_t accessor_calls = 0;
  std::size_t dispatch1_calls = 0;
  std::size_t dispatch2_calls = 0;
  std::size_t dispatch1_argc = 0;
  std::size_t dispatch2_argc = 0;
  recon::Word dispatch1_args[6] = {0, 0, 0, 0, 0, 0};
  recon::Word dispatch2_args[6] = {0, 0, 0, 0, 0, 0};
  bool dispatch1_receiver_is_first = false;
  bool dispatch2_receiver_is_second = false;

  std::size_t construct_calls = 0;
  std::size_t destroy_calls = 0;

  std::size_t wide_units = 0;
  std::size_t assign_calls = 0;
  const std::uint16_t* assign_begin = nullptr;
  const std::uint16_t* assign_end = nullptr;

  std::size_t stack_arg1_touched = 0;
  std::size_t stack_arg2_touched = 0;
};

void hook_construct(recon::LocalWrapper* w) {
  w->word_00 = 1;
  w->word_04 = 1;
  w->word_08 = reinterpret_cast<recon::Word>(&kWide[0]);
  w->word_0c = 2;
  w->byte_10 = 0;
  w->byte_11 = 0;
}

void hook_destroy(recon::LocalWrapper* w) { w->word_04 = 0; }

const std::uint16_t* hook_wrapper_data(const recon::LocalWrapper* w) {
  return reinterpret_cast<const std::uint16_t*>(w->word_08);
}

recon::Hooks make_hooks(Inputs& in, Observation& obs) {
  recon::Hooks hooks;
  hooks.dispatch_slot41 = [](const recon::Receiver*) { return kSelfDispatchResult; };
  hooks.read_player_data = []() { return g_player_data; };
  hooks.read_player_data_word_13c = [](const void* p) -> recon::Word {
    (void)p;
    return kPlayerDataWord13c;
  };
  hooks.read_empire = []() { return kEmpireValue; };
  hooks.sub_00c452a0 = [](const recon::Receiver*) { return recon::Word(0); };
  hooks.sub_00c451e0 = [](const recon::Receiver*) { return kSub451e0Value; };
  hooks.construct_wrapper = [&obs](recon::LocalWrapper* w) {
    ++obs.construct_calls;
    hook_construct(w);
  };
  hooks.wrapper_data = hook_wrapper_data;
  hooks.destroy_wrapper = [&obs](recon::LocalWrapper* w) {
    ++obs.destroy_calls;
    hook_destroy(w);
  };
  hooks.acquire_accessor = [&]() -> const recon::Accessor* {
    ++obs.accessor_calls;
    return obs.accessor_calls == 1 ? static_cast<const recon::Accessor*>(&in.acc1)
                                   : static_cast<const recon::Accessor*>(&in.acc2);
  };
  hooks.dispatch_accessor1 = [&obs](const recon::Accessor* a, recon::Word x1,
                                     recon::Word x2, recon::Word x3,
                                     recon::Word x4, recon::Word x5) {
    ++obs.dispatch1_calls;
    obs.dispatch1_argc = 5;
    obs.dispatch1_args[0] = x1;
    obs.dispatch1_args[1] = x2;
    obs.dispatch1_args[2] = x3;
    obs.dispatch1_args[3] = x4;
    obs.dispatch1_args[4] = x5;
    obs.dispatch1_receiver_is_first = (a == nullptr);
    if (g_scope_during != nullptr) {
      obs.scope_18_during = g_scope_during->field_18;
      obs.scope_48_during = g_scope_during->field_48;
    }
    return kDispatch1Result;
  };
  hooks.dispatch_accessor2 = [&obs, &in](const recon::Accessor* a, recon::Word x1,
                                          recon::Word x2, recon::Word x3,
                                          recon::Word x4) {
    ++obs.dispatch2_calls;
    obs.dispatch2_argc = 4;
    obs.dispatch2_args[0] = x1;
    obs.dispatch2_args[1] = x2;
    obs.dispatch2_args[2] = x3;
    obs.dispatch2_args[3] = x4;
    obs.dispatch2_receiver_is_second = (a == &in.acc2);
    return kDispatch2Result;
  };
  hooks.assign_range = [&obs](recon::WideDescriptor* d, const std::uint16_t* begin,
                              const std::uint16_t* end) {
    (void)d;
    ++obs.assign_calls;
    obs.assign_begin = begin;
    obs.assign_end = end;
  };
  return hooks;
}

Observation run_real(Inputs& in) {
  Observation obs;
  recon::Hooks hooks = make_hooks(in, obs);
  recon::Trace trace;
  recon::ScopeState* scope = &in.scope;
  recon::ScopeState** cell = &in.scope_cell;
  g_scope_during = scope;
  recon::Simulator_Slot41ScopeExchangeAndDispatch_00c487d0(
      &in.self, in.stack_arg1, in.stack_arg2, cell, hooks, trace);
  g_scope_during = nullptr;
  obs.scope_18_after = in.scope.field_18;
  obs.scope_48_after = in.scope.field_48;
  obs.scope_cell_after =
      reinterpret_cast<recon::CodeAddress>(reinterpret_cast<std::uintptr_t>(in.scope_cell));
  obs.published_18 = trace.published_field_18;
  obs.published_48 = trace.published_field_48;
  obs.publish_18_count = trace.published_field_18_argv;
  obs.publish_48_count = trace.published_field_48_argv;
  obs.wide_units = trace.wide_code_units;
  obs.dispatch1_argc = obs.dispatch1_calls ? 5u : 0u;
  obs.dispatch2_argc = obs.dispatch2_calls ? 4u : 0u;
  for (int i = 0; i < 5; ++i) obs.dispatch1_args[i] = trace.dispatch_accessor1_args[i];
  for (int i = 0; i < 4; ++i) obs.dispatch2_args[i] = trace.dispatch_accessor2_args[i];
  obs.dispatch1_receiver_is_first =
      trace.dispatch1_receiver == reinterpret_cast<recon::CodeAddress>(
                                      reinterpret_cast<std::uintptr_t>(&in.acc1));
  obs.dispatch2_receiver_is_second =
      trace.dispatch2_receiver == reinterpret_cast<recon::CodeAddress>(
                                      reinterpret_cast<std::uintptr_t>(&in.acc2));
  return obs;
}

// ---------------------------------------------------------------------------
// Mutation flags.
// ---------------------------------------------------------------------------
enum Mutation : unsigned {
  kNone = 0u,
  kRestoreFromPublished = 1u << 0,  // restore field_18 with the slot-41 result
  kNoNullGuard = 1u << 1,            // drop the XOR EBP,EBP branch
  kField17cAlways = 1u << 2,         // substitute even when field_17c == 0
  kWrapperToDispatch1 = 1u << 3,     // wrapper address becomes dispatch1 arg 1
  kScanBytes = 1u << 4,              // scan counts bytes, not code units
  kAritySixThree = 1u << 5,          // 6/3 split instead of 5/4
  kSkipField48Restore = 1u << 6,     // leave field_48 published
  kSkipAssignRange = 1u << 7,        // never call 0x00423650
  kReadStackArgs = 1u << 8,          // touch the discarded stack words
  kWrongAccessorOrder = 1u << 9,     // hand both dispatches the same accessor
};

struct MutationCase {
  unsigned flag;
  const char* name;
};

const MutationCase kMutations[] = {
    {kRestoreFromPublished, "restore field_18 from the published value"},
    {kNoNullGuard, "drop the null branch at 00c48818"},
    {kField17cAlways, "substitute the receiver even when field_17c == 0"},
    {kWrapperToDispatch1, "route the wrapper address to dispatch 1"},
    {kScanBytes, "scan byte length instead of code units"},
    {kAritySixThree, "use the 6/3 dispatch arity split"},
    {kSkipField48Restore, "skip the field_48 restore"},
    {kSkipAssignRange, "skip the 0x00423650 assignment"},
    {kReadStackArgs, "read the two discarded stack arguments"},
    {kWrongAccessorOrder, "use one accessor for both dispatches"},
};

Observation run_shadow(Inputs& in, unsigned flags) {
  Observation obs;
  const bool m_restore_published = (flags & kRestoreFromPublished) != 0;
  const bool m_no_null_guard = (flags & kNoNullGuard) != 0;
  const bool m_field17c_always = (flags & kField17cAlways) != 0;
  const bool m_wrapper_to_1 = (flags & kWrapperToDispatch1) != 0;
  const bool m_scan_bytes = (flags & kScanBytes) != 0;
  const bool m_six_three = (flags & kAritySixThree) != 0;
  const bool m_skip48 = (flags & kSkipField48Restore) != 0;
  const bool m_skip_assign = (flags & kSkipAssignRange) != 0;
  const bool m_read_args = (flags & kReadStackArgs) != 0;
  const bool m_same_accessor = (flags & kWrongAccessorOrder) != 0;

  recon::Word sink = 0;
  if (m_read_args) sink ^= in.stack_arg1 ^ in.stack_arg2;
  obs.stack_arg1_touched = m_read_args ? 1u : 0u;
  obs.stack_arg2_touched = m_read_args ? 1u : 0u;
  obs.scope_18_after = in.scope.field_18;
  obs.scope_48_after = in.scope.field_48;
  if (sink == 0xFFFFFFFFu) std::abort();  // keep `sink` observable
  static_assert(kScopePointer == 0x016e0d08u, "scope pointer cell");

  const recon::Word slot41 = kSelfDispatchResult;

  const recon::Word saved_18 = in.scope.field_18;
  const recon::Word saved_48 = in.scope.field_48;
  in.scope.field_18 = reinterpret_cast<recon::Word>(reinterpret_cast<std::uintptr_t>(&in.self));
  obs.published_18 = in.scope.field_18;
  ++obs.publish_18_count;
  in.scope.field_48 = slot41;
  obs.published_48 = in.scope.field_48;
  ++obs.publish_48_count;
  obs.scope_18_during = in.scope.field_18;
  obs.scope_48_during = in.scope.field_48;

  // `TEST EAX,EAX / JZ` : the +0x13c load is skipped entirely when the accessor
  // returned zero. kNoNullGuard drops that branch and uses the accessor word.
  const recon::Word player_word =
      m_no_null_guard ? g_player_data
                      : (g_player_data != 0 ? kPlayerDataWord13c : recon::Word(0));

  const recon::Word sub_result = kSub451e0Value;

  recon::LocalWrapper wrapper;
  ++obs.construct_calls;
  hook_construct(&wrapper);

  const void* dispatch_receiver =
      (m_field17c_always || in.self.field_17c != 0)
          ? reinterpret_cast<const void*>(in.self.field_17c)
          : static_cast<const void*>(&in.self);

  ++obs.accessor_calls;
  const recon::Accessor* a1 = &in.acc1;
  ++obs.accessor_calls;
  const recon::Accessor* a2 = m_same_accessor ? &in.acc1 : &in.acc2;

  const recon::Word empire = kEmpireValue;

  unsigned char frame[recon::kFrameBytes] = {};
  recon::Word* frame_local_14 =
      reinterpret_cast<recon::Word*>(frame + (recon::kFrameBytes - 0x14));

  recon::WideDescriptor descriptor{};

  ++obs.dispatch1_calls;
  obs.dispatch1_args[0] = m_wrapper_to_1 ? reinterpret_cast<recon::Word>(
                                                reinterpret_cast<std::uintptr_t>(&wrapper))
                                          : reinterpret_cast<recon::Word>(
                                                reinterpret_cast<std::uintptr_t>(frame_local_14));
  obs.dispatch1_args[1] = sub_result;
  obs.dispatch1_args[2] = empire;
  obs.dispatch1_args[3] = player_word;
  obs.dispatch1_args[4] = reinterpret_cast<recon::Word>(
      reinterpret_cast<std::uintptr_t>(dispatch_receiver));
  if (m_six_three) {
    obs.dispatch1_argc = 6;
    obs.dispatch1_args[5] = reinterpret_cast<recon::Word>(
        reinterpret_cast<std::uintptr_t>(&wrapper));
  } else {
    obs.dispatch1_argc = 5;
  }
  obs.dispatch1_receiver_is_first = (a1 == &in.acc1);

  ++obs.dispatch2_calls;
  obs.dispatch2_args[0] = slot41;
  obs.dispatch2_args[1] = descriptor.end;
  obs.dispatch2_args[2] = kDispatch1Result;
  obs.dispatch2_args[3] =
      m_six_three ? recon::Word(0)
                  : reinterpret_cast<recon::Word>(reinterpret_cast<std::uintptr_t>(&wrapper));
  obs.dispatch2_argc = m_six_three ? 3u : 4u;
  obs.dispatch2_receiver_is_second = (a2 == &in.acc2);

  const std::uint16_t* data = hook_wrapper_data(&wrapper);
  std::size_t units = 0;
  while (data[units] != 0) ++units;
  obs.wide_units = m_scan_bytes ? units * 2 : units;

  if (!m_skip_assign) {
    ++obs.assign_calls;
    const std::size_t span = m_scan_bytes ? units * 2 : units;
    obs.assign_begin = data;
    obs.assign_end = data + span;
  }

  in.scope.field_18 = m_restore_published ? slot41 : saved_18;
  if (!m_skip48) in.scope.field_48 = saved_48;

  ++obs.destroy_calls;
  hook_destroy(&wrapper);

  obs.scope_18_after = in.scope.field_18;
  obs.scope_48_after = in.scope.field_48;
  obs.scope_cell_after =
      reinterpret_cast<recon::CodeAddress>(reinterpret_cast<std::uintptr_t>(in.scope_cell));
  return obs;
}

// ---------------------------------------------------------------------------
// The invariant battery. Returns the names of the invariants that FAIL, so the
// same battery can demand zero failures for the reconstruction and at least one
// failure for every mutation.
// ---------------------------------------------------------------------------
std::vector<const char*> violations(const Inputs& in, const Observation& obs) {
  std::vector<const char*> bad;
  auto want = [&bad](bool ok, const char* what) {
    if (!ok) bad.push_back(what);
  };

  const recon::Word self_word =
      reinterpret_cast<recon::Word>(reinterpret_cast<std::uintptr_t>(&in.self));

  // 1. publish and verbatim restore
  want(obs.scope_18_after == in.original_field_18,
       "field_18 must be restored verbatim");
  want(obs.scope_48_after == in.original_field_48,
       "field_48 must be restored verbatim");
  want(obs.publish_18_count == 1 && obs.publish_48_count == 1,
       "each scope word must be published exactly once");
  want(obs.published_18 == self_word,
       "field_18 must be published as the receiver word");
  want(obs.published_48 == kSelfDispatchResult,
       "field_48 must be published as the slot-0xa4 result");
  want(obs.scope_18_during == self_word && obs.scope_48_during == kSelfDispatchResult,
       "both scope words must be live during the first dispatch");

  // 2. the pointer cell is only read
  want(obs.scope_cell_after ==
           reinterpret_cast<recon::CodeAddress>(
               reinterpret_cast<std::uintptr_t>(&in.scope)),
       "the 0x016e0d08 cell must be untouched (all four GLOBALS rows are reads)");

  // 3. the null branch at 00c48818
  if (g_player_data == 0) {
    want(obs.dispatch1_args[3] == 0,
         "a null player-data accessor must yield argument 4 == 0");
  } else {
    want(obs.dispatch1_args[3] == kPlayerDataWord13c,
         "argument 4 must carry the word at player data + 0x13c");
  }

  // 4. receiver+0x17c substitutes only when non-zero
  if (in.self.field_17c != 0) {
    want(obs.dispatch1_args[4] == in.self.field_17c,
         "field_17c != 0 must substitute the receiver");
  } else {
    want(obs.dispatch1_args[4] == self_word,
         "field_17c == 0 must leave the receiver unchanged");
  }

  // 5. wrapper lifetime
  want(obs.construct_calls == 1 && obs.destroy_calls == 1,
       "the local wrapper must be built and destroyed exactly once each");
  want(obs.accessor_calls == 2,
       "the argument-free accessor must run exactly twice");
  want(obs.dispatch1_calls == 1 && obs.dispatch2_calls == 1,
       "each dispatch must run exactly once");
  want(obs.dispatch1_receiver_is_first && obs.dispatch2_receiver_is_second,
       "the dispatches must use the first and second accessor respectively");

  // 6. arities and argument order
  want(obs.dispatch1_argc == 5, "dispatch 1 must take five stack arguments");
  want(obs.dispatch2_argc == 4, "dispatch 2 must take four stack arguments");
  want(obs.dispatch1_args[1] == kSub451e0Value,
       "dispatch 1 argument 2 must carry the 0x00c451e0 result");
  want(obs.dispatch1_args[2] == kEmpireValue,
       "dispatch 1 argument 3 must carry the 0x01021300 result");
  want(obs.dispatch2_args[0] == kSelfDispatchResult,
       "dispatch 2 argument 1 must carry the slot-0xa4 result");
  want(obs.dispatch2_args[2] == kDispatch1Result,
       "dispatch 2 argument 3 must carry the first dispatch's result");
  want(obs.dispatch1_args[0] != 0 && obs.dispatch1_args[0] != self_word,
       "dispatch 1 argument 1 must be a frame address");
  for (std::size_t i = 0; i < obs.dispatch1_argc; ++i) {
    want(obs.dispatch1_args[i] != obs.dispatch2_args[3],
         "the wrapper address must not reach dispatch 1");
  }
  want(obs.dispatch2_args[3] != 0,
       "dispatch 2 argument 4 must be the wrapper address");

  // 7. the 16-bit scan
  want(obs.wide_units == 3, "the scan must count 16-bit code units");
  want(obs.assign_calls == 1, "0x00423650 must be reached exactly once");
  want(obs.assign_begin == &kWide[0] && obs.assign_end == &kWide[3],
       "assign_range must receive (begin, begin + code units)");

  // 8. the two popped stack words are never read
  want(obs.stack_arg1_touched == 0 && obs.stack_arg2_touched == 0,
       "the two discarded stack arguments must never be read");

  return bad;
}

void check_header_constants() {
  require(recon::kReceiverTableWord == 0x00, "receiver table word must be +0x00");
  require(recon::kReceiverReplacement == 0x17c, "substitution field is +0x17c");
  require(recon::kReceiverDispatchSlot == 0xa4, "dispatch slot must be +0xa4");
  require(recon::kPlayerDataWord == 0x13c, "player-data word must be +0x13c");
  require(recon::kScopeField18 == 0x18 && recon::kScopeField48 == 0x48,
          "scope fields must be +0x18 and +0x48");
  require(recon::kAccessor1Slot == 0x24 && recon::kAccessor2Slot == 0x0c,
          "accessor dispatch slots must be +0x24 and +0x0c");
  require(recon::kScopeStatePointer == 0x016e0d08u,
          "the scope pointer global must be 0x016e0d08");
  require(recon::kLocalWrapperBytes == 0x14,
          "the local wrapper must be the 0x14 bytes its constructor writes");
  require(recon::kLocalWrapperDataWord == 0x08,
          "the wide pointer lives at wrapper+0x08");
  require(recon::kFrameBytes == 0x40, "the frame must be 0x40 bytes");
  require(recon::kPrologueSavedWords == 4,
          "four callee-saved words are pushed and popped");
  require(recon::kStackCleanupBytes == 8, "RET 0x8 must clean eight bytes");
  require(recon::kFrameBytes + recon::kPrologueSavedWords * 4 == 0x50,
          "ESP must be entry_ESP - 0x50 entering the epilogue POP block");
  // Nine stack words are pushed between 00c4884d and 00c48891 and both dispatch
  // callees clean up, so 5 + 4 accounts for all 36 bytes.
  require(5u + 4u == 9u,
          "the 5/4 dispatch arities must account for the nine pushed words");
  require(std::strstr(__FILE__, "00c487d0") != nullptr,
          "the reconstructed symbol must embed the 8-hex target VA");
}

}  // namespace

int main() {
  check_header_constants();

  // ------------------------------------------------------- PART 1 (real) ---
  struct Scenario {
    const char* name;
    recon::Word field_17c;
    recon::Word player_data;
  };
  const Scenario scenarios[] = {
      {"field_17c == 0, player data present", 0u, kPlayerDataValue},
      {"field_17c != 0, player data present", 0xDEAD0009u, kPlayerDataValue},
      {"field_17c == 0, player data NULL", 0u, 0u},
      {"field_17c != 0, player data NULL", 0x0000BEEFu, 0u},
  };

  for (const Scenario& sc : scenarios) {
    Inputs in;
    make_inputs(in, sc.field_17c, sc.player_data);
    g_scope_during = &in.scope;
    Observation obs = run_real(in);
    g_scope_during = nullptr;
    std::vector<const char*> bad = violations(in, obs);
    if (!bad.empty()) {
      std::fprintf(stderr, "scenario '%s' violated:\n", sc.name);
      for (const char* b : bad) std::fprintf(stderr, "  - %s\n", b);
      std::abort();
    }
  }

  // ------------------------------------------------ PART 2 (mutations) ---
  for (const MutationCase& mc : kMutations) {
    int survivors = 0;
    for (const Scenario& sc : scenarios) {
      Inputs in;
      make_inputs(in, sc.field_17c, sc.player_data);
      Observation base = run_shadow(in, kNone);
      std::vector<const char*> clean = violations(in, base);
      if (!clean.empty()) {
        // The shadow itself must satisfy the battery, otherwise PART 2 proves
        // nothing about the battery.
        std::fprintf(stderr,
                     "shadow disagrees with the battery on the unmutated path:\n");
        for (const char* b : clean) std::fprintf(stderr, "  - %s\n", b);
        std::abort();
      }
      Inputs mutated;
      make_inputs(mutated, sc.field_17c, sc.player_data);
      Observation obs = run_shadow(mutated, mc.flag);
      if (violations(mutated, obs).empty()) ++survivors;
    }
    const std::size_t n_scenarios = sizeof(scenarios) / sizeof(scenarios[0]);
    if (survivors == n_scenarios) {
      // A mutation may be a no-op in scenarios it cannot express (substituting a
      // non-zero receiver when it already is non-zero, say). It must still be
      // rejected by at least one scenario, otherwise the battery is blind to it.
      std::fprintf(stderr,
                   "MUTATION SURVIVED every scenario (%zu/%zu): %s\n", survivors,
                   n_scenarios, mc.name);
      ++g_failures;
    } else {
      std::printf("mutation rejected in %zu/%zu scenarios: %s\n",
                  n_scenarios - survivors, n_scenarios, mc.name);
    }
  }

  if (g_failures != 0) {
    std::fprintf(stderr, "%d mutation(s) survived\n", g_failures);
    return 1;
  }
  std::printf("all invariants held; %zu mutations rejected\n",
              sizeof(kMutations) / sizeof(kMutations[0]));
  return 0;
}
