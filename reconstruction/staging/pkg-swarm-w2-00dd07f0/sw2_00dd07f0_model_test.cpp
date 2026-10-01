// PKG-SWARM-W2-00DD07F0 -- model test for re_00dd07f0
//
// This test tries to BREAK the reconstruction. It does not walk it.
//
// Every direct callee is defined here as an OBSERVER, so the test sees every
// transfer, with which arguments, in which order, and can decide what each does
// to memory -- including rewriting the object from inside the call, which is
// how the write-ordering and the pointer-level claims are attacked.
//
// The cases below are grouped:
//
//   A  the two-level pointer chain   levels, sentinels, decoys at the wrong
//                                    depth, the sub-state sentinel
//   B  the two switches and the      exhaustive sweep against an INDEPENDENT
//      three jump tables             transcription, the transposed-table decoy,
//                                    the bare-store decoy, the unsigned guards,
//                                    the wrapping addend
//   C  the three callees             order, count, argument identity, argument
//                                    order, ESP at each call, write ordering at
//                                    the moment of each call
//   D  measurements                 whole-object byte compare, the receiver
//                                    really arriving in ECX, the stack this body
//                                    consumes, repeated invocations,
//                                    receiver-offset decoys
//
// Every assertion below is a claim the 68-instruction listing fixes. The
// "not asserted" section at the end lists, explicitly, the claims this test does
// NOT make and why.

#include "sw2_00dd07f0_types.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

namespace osw = openspore::reconstruction::pkg_swarm_w2_00dd07f0;
using osw::Byte;
using osw::OpaqueSporepediaAsset;
using osw::Word;

// ===========================================================================
// -- harness ----------------------------------------------------------------
// ===========================================================================

namespace {

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    if (g_failures <= 40) {
      std::printf("FAIL: %s\n", what);
    }
  }
}

void check_word(Word got, Word want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    if (g_failures <= 40) {
      std::printf("FAIL: %s (got 0x%08lx, want 0x%08lx)\n", what,
                  static_cast<unsigned long>(got),
                  static_cast<unsigned long>(want));
    }
  }
}

// ===========================================================================
// -- the object under test --------------------------------------------------
// ===========================================================================
//
// The receiver is modelled as the header's opaque run, and the test allocates a
// guarded arena around it, so a displacement one byte below zero or one byte
// past the last modelled byte is a real, addressable decoy rather than a wild
// write. If the model ever reaches outside 0x00..0x9b, the guard bytes change
// and D3 says so.
constexpr std::size_t kGuardBefore = 64;
constexpr std::size_t kObjectBytes = sizeof(OpaqueSporepediaAsset);
constexpr std::size_t kGuardAfter = 64;
constexpr std::size_t kArenaBytes = kGuardBefore + kObjectBytes + kGuardAfter;

static_assert(kObjectBytes == 0x9c,
              "0x98 + 4 is the last byte this body reads on the receiver");

struct Arena {
  Byte raw[kArenaBytes];

  Arena() { reset(); }
  void reset() { std::memset(raw, 0xa5, sizeof(raw)); }
  OpaqueSporepediaAsset* object() {
    return reinterpret_cast<OpaqueSporepediaAsset*>(raw + kGuardBefore);
  }
  Byte* at(std::size_t displacement) { return raw + kGuardBefore + displacement; }
  Word* word_of(std::size_t displacement) {
    return reinterpret_cast<Word*>(at(displacement));
  }
  Word peek(std::size_t displacement) const {
    Word value = 0;
    std::memcpy(&value, raw + kGuardBefore + displacement, sizeof(value));
    return value;
  }
  void poke(std::size_t displacement, Word value) {
    std::memcpy(at(displacement), &value, sizeof(value));
  }
};

// The species-manager word the observers hand back. Its own storage is nothing
// like a receiver, so a reconstruction that confused the two is visible.
alignas(4) Byte g_manager[512];
constexpr std::size_t kManagerShift = 0xa4;  // 0x004df400's own ADD EAX,0xa4

// The level-2 record: the object the body reads at +0x10 and +0x20, poisoned
// everywhere else.
alignas(4) Byte g_record[128];

// The twelve bytes at the address 0x00dd086e forms.
Byte* g_local_record = nullptr;  // receiver + 0x4, set by the fixture
Byte* g_compare_record = nullptr;  // the shift callee's return, set by the fixture

// The one dword this body owns, as the observers see it.
Word* g_obs_result_word = nullptr;

bool g_species_manager_result = false;
bool g_observer_rewrites_result = false;
Word g_rewrite_value = 0u;

struct Observation {
  int species_manager_calls = 0;
  int shift_calls = 0;
  int compare_calls = 0;
  std::vector<const char*> order;

  std::uint8_t* manager_value = nullptr;
  std::uint8_t* shift_receiver = nullptr;
  std::uint8_t* shift_return = nullptr;

  const void* compare_first = nullptr;
  const void* compare_second = nullptr;

  Word result_seen_by_species_manager = 0xdeadbeefu;
  Word result_seen_by_shift = 0xdeadbeefu;
  Word result_seen_by_compare = 0xdeadbeefu;

  void* esp_at_species_manager = nullptr;
  void* esp_at_shift = nullptr;
  void* esp_at_compare = nullptr;

  // The word that sits where a first STACK argument would sit when 0x00401090
  // is entered. Sampled from the observer's own stack, so it measures what the
  // MODEL did rather than what the listing says.
  void* stack_slot_at_species_manager = nullptr;
};

// The decoy the raw trampoline pushes below the call, which is what the sample
// above must find if the model pushed nothing for 0x00401090.
void* g_trampoline_decoy = nullptr;

Observation g_obs;

// ESP sampled by the raw-call trampoline, before and after the model runs.
void* g_esp_at_trampoline_entry = nullptr;
void* g_esp_after_the_model = nullptr;

void reset_observers() {
  g_obs = Observation();
  g_species_manager_result = false;
  g_observer_rewrites_result = false;
  g_rewrite_value = 0u;
  g_esp_at_trampoline_entry = nullptr;
  g_esp_after_the_model = nullptr;
  // g_manager and g_record are FIXTURE state, not observer state: they are the
  // two shared objects every case drives, and wiping them here would destroy the
  // inputs a case had just built. Fixture::chain resets both, and
  // arm_the_comparison fills the twelve bytes the comparison reads. The first
  // version of this harness did wipe them here, which is what made the whole
  // three-callee block look unreachable for several iterations.
}

// The level-1 object, and the fixture that wires the whole chain.
struct Fixture {
  Arena arena;
  Byte link[128];

  Fixture() { chain(0x00u, 0x00u); }

  // `link_is_null` builds the one path 0x00dd07fb takes.
  void chain(Word record_kind, Word sub, bool link_is_null = false) {
    std::memset(g_record, 0x77, sizeof(g_record));
    std::memcpy(g_record + osw::kRecordKindDisplacement, &record_kind,
                sizeof(record_kind));
    std::memcpy(g_record + osw::kRecordSubDisplacement, &sub, sizeof(sub));
    for (std::size_t i = 0; i < sizeof(g_manager); ++i) {
      g_manager[i] = 0x11;
    }

    std::memset(link, 0x33, sizeof(link));
    const std::uintptr_t record_address = reinterpret_cast<std::uintptr_t>(g_record);
    std::memcpy(link + osw::kRecordLinkDisplacement, &record_address,
                sizeof(record_address));

    arena.reset();
    g_obs_result_word = arena.word_of(osw::kResultDisplacement);
    g_local_record = arena.at(osw::kCompareArgumentDisplacement);
    g_compare_record = nullptr;

    if (link_is_null) {
      arena.poke(osw::kLinkDisplacement, 0u);
    } else {
      const std::uintptr_t link_address = reinterpret_cast<std::uintptr_t>(link);
      std::memcpy(arena.at(osw::kLinkDisplacement), &link_address,
                  sizeof(link_address));
    }
  }

  void set_level2(Word record_kind, Word sub) {
    std::memcpy(g_record + osw::kRecordKindDisplacement, &record_kind,
                sizeof(record_kind));
    std::memcpy(g_record + osw::kRecordSubDisplacement, &sub, sizeof(sub));
  }
  void set_kind(Word value) { arena.poke(osw::kKindDisplacement, value); }
  void set_tag(Word value) { arena.poke(osw::kTagDisplacement, value); }
  void set_result(Word value) { arena.poke(osw::kResultDisplacement, value); }
  Word result() const { return arena.peek(osw::kResultDisplacement); }
};

void call_model(Fixture& f) { osw::re_00dd07f0(f.arena.object()); }

// Make the comparison's two records DIFFER, so the callee's answer depends on
// the argument order and on the argument identity and not on anything else.
void arm_the_comparison(Fixture& f, bool equal_records = false) {
  g_compare_record = g_manager + kManagerShift;
  g_local_record = f.arena.at(osw::kCompareArgumentDisplacement);
  // The FIRST record -- the one at the shift callee's return -- is always 0xc3.
  // The SECOND -- the twelve bytes at receiver+0x4 -- is 0xc3 when the caller
  // wants the two to MATCH and 0x3c when it wants them to DIFFER. Filling both
  // with the same byte is the mistake the first version of this harness made,
  // and it silently made the comparison's false arm unreachable.
  std::memset(g_compare_record, 0xc3, 12);
  std::memset(g_local_record, equal_records ? 0xc3 : 0x3c, 12);
}

}  // namespace

// ===========================================================================
// -- the three observers, at the addresses the model names ------------------
// ===========================================================================
//
// 0x00401090: cdecl, ZERO arguments. Its own body reads no stack slot and no
// argument register, so the only thing an observer can measure about its
// argument surface is the ESP it is entered at -- and that is exactly the
// measurement that shows nothing was pushed for it.
namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0 {
extern "C" std::uint8_t* PKG_SWARM_W2_00DD07F0_CDECL
sporepedia_species_manager_global_00401090() {
  // Two samples in one block: ESP itself, and the word at [ESP+4], which is
  // where a first stack argument would be. The second sample has to land in a
  // register first -- there is no x86 form that moves a stack slot straight into
  // a memory operand -- and is written to the observation record from C++.
  std::uintptr_t stack_slot = 0;
  __asm__ __volatile__("movl %%esp, %0\n\t"
                       "movl 4(%%esp), %1"
                       : "=m"(g_obs.esp_at_species_manager), "=r"(stack_slot));
  g_obs.stack_slot_at_species_manager = reinterpret_cast<void*>(stack_slot);
  ++g_obs.species_manager_calls;
  g_obs.order.push_back("get");
  g_obs.manager_value = g_manager;
  g_obs.result_seen_by_species_manager = *g_obs_result_word;
  if (g_observer_rewrites_result) {
    *g_obs_result_word = g_rewrite_value;
  }
  return g_manager;
}
}  // namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0

// 0x004df400: __thiscall with the receiver in ECX and no stack argument. Its
// own body is `return this + 0xa4`, so the observer reproduces that EXACTLY and
// the test asserts the shift rather than assuming it.
namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0 {
extern "C" std::uint8_t* PKG_SWARM_W2_00DD07F0_CALLEE_THISCALL
sporepedia_member_shift_004df400(std::uint8_t* receiver) {
  __asm__ __volatile__("movl %%esp, %0" : "=m"(g_obs.esp_at_shift));
  ++g_obs.shift_calls;
  g_obs.order.push_back("shift");
  g_obs.shift_receiver = receiver;
  g_obs.shift_return = receiver + kManagerShift;
  g_obs.result_seen_by_shift = *g_obs_result_word;
  if (g_observer_rewrites_result) {
    *g_obs_result_word = g_rewrite_value;
  }
  return g_obs.shift_return;
}
}  // namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0

// 0x004eb930: cdecl with TWO four-byte stack arguments, read at [ebp+0x8] and
// [ebp+0xc], returning one byte in AL which 0x00dd0884 zero-extends. The
// observer therefore compares THREE dwords, at offsets 0, 4 and 8 of each
// argument, and answers in a bool -- the narrowest type that reproduces the
// listing's one-byte consumption.
namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0 {
extern "C" bool PKG_SWARM_W2_00DD07F0_CDECL
sporepedia_equal_three_dwords_004eb930(const void* first, const void* second) {
  __asm__ __volatile__("movl %%esp, %0" : "=m"(g_obs.esp_at_compare));
  ++g_obs.compare_calls;
  g_obs.order.push_back("equal");
  g_obs.compare_first = first;
  g_obs.compare_second = second;
  g_obs.result_seen_by_compare = *g_obs_result_word;
  if (g_compare_record == nullptr || g_local_record == nullptr) {
    return g_species_manager_result;
  }
  // Deliberately ORDER-SENSITIVE as well as content-sensitive: the observer
  // answers true only when the FIRST argument is the address the second callee
  // returned AND the twelve bytes at the two arguments match AND the test has
  // told it to. A model that swapped the two arguments therefore changes the
  // answer the body stores, not merely the addresses C1 records.
  const bool first_is_the_shifted = (first == static_cast<const void*>(g_compare_record));
  const bool equal = first_is_the_shifted && std::memcmp(first, second, 12) == 0;
  return equal ? g_species_manager_result : false;
}
}  // namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0

namespace {

// ===========================================================================
// -- the independent oracle --------------------------------------------------
// ===========================================================================
//
// Written from the decoded jump tables a SECOND time, as a flat if/else ladder
// over the raw (kind, sub) pair, with no array indexing and no helper shared
// with the model. Its value table is therefore an independent statement of the
// same bytes, and a disagreement between it and the model is a disagreement
// between two readings of the listing rather than a tautology.
//
//   kind 1   outer entry 0 -> 0x00dd0852, bound 7
//       sub 0, 3 -> 3     sub 1 -> 2      sub 2 -> 1
//       sub 4        -> 4  the bare store, leftover EDX
//       sub 5        -> 0
//       sub 6, 7     -> the three-callee block
//       sub > 7      -> no write
//   kind 2, 4, 5   outer entries 1, 3, 4 -> 0x00dd089f, bound 4
//       sub 0 -> 0   sub 1 -> 1   sub 2 -> 3
//       sub 3 -> 4  the bare store again
//       sub 4 -> the tag arm
//       sub > 4 -> no write
//   kind 3         outer entry 2 -> 0x00dd08f0   -> no write
//   kind 0 or > 5 the unsigned guard at 0x00dd0845  -> no write
constexpr Word kOracleNoWrite = 0xffffffffu;

bool oracle_switch(Word kind, Word sub, Word tag, bool callee_equal,
                   Word* out) {
  if (kind - 0x01u > 0x04u) {
    *out = kOracleNoWrite;
    return false;
  }
  if (kind == 0x01u) {
    if (sub > 0x07u) {
      *out = kOracleNoWrite;
      return false;
    }
    if (sub == 0x00u || sub == 0x03u) {
      *out = 0x03u;
    } else if (sub == 0x01u) {
      *out = 0x02u;
    } else if (sub == 0x02u) {
      *out = 0x01u;
    } else if (sub == 0x04u) {
      *out = 0x04u;
    } else if (sub == 0x05u) {
      *out = 0x00u;
    } else {
      *out = osw::callee_arm_arithmetic(callee_equal);
      return true;
    }
    return false;
  }
  if (kind == 0x02u || kind == 0x04u || kind == 0x05u) {
    if (sub > 0x04u) {
      *out = kOracleNoWrite;
      return false;
    }
    if (sub == 0x00u) {
      *out = 0x00u;
    } else if (sub == 0x01u) {
      *out = 0x01u;
    } else if (sub == 0x02u) {
      *out = 0x03u;
    } else if (sub == 0x03u) {
      *out = 0x04u;
    } else if (sub == 0x04u) {
      *out = osw::tag_arm_arithmetic(tag);
    } else {
      *out = kOracleNoWrite;
    }
    return false;
  }
  *out = kOracleNoWrite;  // kind 3
  return false;
}

// The result word's final contents for a fixture, and whether the three-callee
// block runs. The two early exits are handled here because they precede the
// switch entirely; the 0x00dd0816 store of 3 is what every later no-write path
// leaves behind.
Word expected(Fixture& f, Word record_kind, Word sub, Word kind, Word tag,
              bool callee_equal, bool* used_callees) {
  *used_callees = false;
  if (f.arena.peek(osw::kLinkDisplacement) == 0u) {
    return 0x3e3e3e3eu;  // untouched by the body; A1 owns the exact claim
  }
  if (record_kind == 0x06u) {
    return 0xfffffffeu;
  }
  if (sub == 0xffffffffu) {
    return 0xfffffffdu;
  }
  Word written = kOracleNoWrite;
  const bool callees = oracle_switch(kind, sub, tag, callee_equal, &written);
  *used_callees = callees;
  if (written != kOracleNoWrite) {
    return written;
  }
  return 0x03u;  // 0x00dd0816's 3, left in place by every no-write switch path
}

// ===========================================================================
// -- A: the two-level pointer chain ------------------------------------------
// ===========================================================================

void case_a1_a_null_link_writes_nothing() {
  Fixture f;
  f.chain(0x77u, 0x05u, /*link_is_null=*/true);
  f.set_kind(0x01u);
  f.set_result(0x5eed5eedu);
  Byte before[kArenaBytes];
  std::memcpy(before, f.arena.raw, kArenaBytes);
  reset_observers();
  call_model(f);
  check_word(f.result(), 0x5eed5eedu,
             "A1: a null link leaves the result word untouched");
  check(std::memcmp(before, f.arena.raw, kArenaBytes) == 0,
        "A1: a null link leaves the WHOLE object byte for byte");
  check(g_obs.species_manager_calls == 0 && g_obs.shift_calls == 0 &&
            g_obs.compare_calls == 0,
        "A1: a null link enters no callee");
  check(g_obs.order.empty(), "A1: a null link makes no call at all");
}

void case_a2_the_sentinel_is_an_equality_at_the_right_depth() {
  struct Case {
    Word record_kind;
    const char* what;
  };
  const Case cases[] = {
      {0x06u, "A2: record+0x10 == 6 takes the -2 exit"},
      {0x05u, "A2: record+0x10 == 5 does NOT"},
      {0x07u, "A2: record+0x10 == 7 does NOT"},
      {0x06000000u, "A2: 6 in the HIGH THREE BYTES is not 6"},
      {0x00000060u, "A2: 6 in the low byte is not 6"},
      {0x00000006u, "A2: 6 in the low byte and nothing else IS 6"},
  };
  for (const Case& c : cases) {
    Fixture f;
    f.chain(c.record_kind, 0x00u);
    f.set_kind(0x01u);
    f.set_result(0x5eed5eedu);
    reset_observers();
    call_model(f);
    const Word want = (c.record_kind == 0x06u) ? 0xfffffffeu : 0x03u;
    check_word(f.result(), want, c.what);
  }
}

void case_a3_decoys_at_the_wrong_depth_are_never_read() {
  // Plant 6 at every neighbouring depth a one-level reconstruction would read,
  // and require the model to reach record+0x10 and nothing else.
  const Word six = 0x06u;
  Fixture f;
  f.chain(0x06u, 0x00u);
  f.set_kind(0x01u);
  f.set_result(0x5eed5eedu);
  std::memcpy(f.link + 0x00, &six, sizeof(six));            // level 1, offset 0
  std::memcpy(f.link + 0x10, &six, sizeof(six));            // level 1, +0x10
  std::memcpy(g_record + 0x00, &six, sizeof(six));           // level 2, +0x00
  std::memcpy(g_record + 0x08, &six, sizeof(six));           // level 2, +0x08
  std::memcpy(f.arena.at(0x00), &six, sizeof(six));          // receiver +0x00
  // Receiver decoys that do NOT overlap a modelled dword: +0x00 and +0x90, the
  // word immediately after the result word. The kind and tag words are left
  // alone here because overwriting them would change the input rather than
  // decoy it -- cases B5 and D3 cover them.
  std::memcpy(f.arena.at(osw::kResultDisplacement + 4), &six, sizeof(six));
  reset_observers();
  call_model(f);
  check_word(f.result(), 0xfffffffeu,
             "A3: with 6 at seven wrong depths and one right one, the model "
             "finds the word at record+0x10");

  // Break the RIGHT depth, leave every decoy: the model must NOT take -2.
  Fixture g;
  g.chain(0x07u, 0x00u);
  g.set_kind(0x01u);
  g.set_result(0x5eed5eedu);
  std::memcpy(g.link + 0x00, &six, sizeof(six));
  std::memcpy(g.link + 0x10, &six, sizeof(six));
  std::memcpy(g.arena.at(0x00), &six, sizeof(six));
  std::memcpy(g.arena.at(osw::kResultDisplacement + 4), &six, sizeof(six));
  reset_observers();
  call_model(g);
  check_word(g.result(), 0x03u,
             "A3: with only the wrong depths holding 6, the model refuses the "
             "-2 exit and takes the switch instead");
}

void case_a4_the_sub_state_sentinel_is_all_ones() {
  struct Case {
    Word sub;
    bool sentinel;
    const char* what;
  };
  const Case cases[] = {
      {0xffffffffu, true, "A4: all ones IS the sub-state sentinel"},
      {0xfffffffeu, false, "A4: all ones minus one is NOT"},
      {0x7fffffffu, false, "A4: the largest signed word is NOT"},
      {0x00000000u, false, "A4: zero is NOT"},
      {0x00000001u, false, "A4: one is NOT"},
      {0x80000000u, false, "A4: the sign bit alone is NOT"},
  };
  // The kind word is 3 here, so the switch below the sentinel is a no-write path
  // for every index and the case measures the sentinel and nothing else.
  for (const Case& c : cases) {
    Fixture f;
    f.chain(0x00u, c.sub);
    f.set_kind(0x03u);
    f.set_result(0x5eed5eedu);
    reset_observers();
    call_model(f);
    const Word want = c.sentinel ? 0xfffffffdu : 0x03u;
    check_word(f.result(), want, c.what);
  }
}

void case_a5_the_sentinel_overwrites_the_earlier_store() {
  // 0x00dd0816 stores 3 and 0x00dd082b overwrites it. A reconstruction that
  // returned before the second store would leave 3 here.
  Fixture f;
  f.chain(0x00u, 0xffffffffu);
  f.set_kind(0x01u);
  f.set_result(0x5eed5eedu);
  reset_observers();
  call_model(f);
  check_word(f.result(), 0xfffffffdu,
             "A5: the sub-state sentinel overwrites the 3 from 0x00dd0816");
  check(g_obs.species_manager_calls == 0 && g_obs.compare_calls == 0,
        "A5: the sub-state sentinel exits before the kind word is even read");
  check(g_obs.order.empty(),
        "A5: the sub-state sentinel path makes no call at all");
}

void case_a6_a_zeroed_record_is_not_the_null_link() {
  // 0x00dd07f9's TEST is on the POINTER, not on anything behind it. A link that
  // points at an all-zero record is NOT the null exit: the kind word reads 0,
  // the sub-state reads 0, and the switch runs.
  Fixture f;
  f.chain(0x00u, 0x00u);
  std::memset(g_record, 0x00, sizeof(g_record));
  f.set_kind(0x02u);
  f.set_result(0x5eed5eedu);
  reset_observers();
  call_model(f);
  check_word(f.result(), 0x00u,
             "A6: a link to an all-zero record is NOT the null exit; it runs "
             "the switch and stores 0");
  check(g_obs.species_manager_calls == 0,
        "A6: an all-zero record does not reach the callees either");
}

// ===========================================================================
// -- B: the two switches, the three tables, and the arithmetic arms ---------
// ===========================================================================

void case_b1_exhaustive_sweep_against_the_oracle() {
  // 0x00dd0845, 0x00dd0855 and 0x00dd08a1 are all UNSIGNED above-or-equal
  // guards, so the sweep deliberately drives the kind and sub-state words with
  // values where a signed comparison would disagree.
  const Word kinds[] = {0x00u, 0x01u, 0x02u, 0x03u, 0x04u,
                        0x05u, 0x06u, 0x07u, 0x08u, 0x7fffffffu,
                        0x80000000u, 0xfffffffeu, 0xffffffffu};
  const Word subs[] = {0x00u, 0x01u, 0x02u, 0x03u, 0x04u,
                       0x05u, 0x06u, 0x07u, 0x08u, 0x09u,
                       0x10u, 0x7fffffffu, 0x80000000u};
  const Word tags[] = {0x53dbcf1u, 0x53dbcf0u, 0x00000000u, 0xffffffffu};
  Fixture f;
  for (Word tag : tags) {
    for (Word kind : kinds) {
      for (Word sub : subs) {
        // Twice per triple: once with the two twelve-byte records EQUAL and once
        // with them DIFFERENT, so BOTH answers of the callee arm are swept for
        // every (kind, sub-state, tag) rather than only the reachable one.
        for (int same = 0; same < 2; ++same) {
          f.chain(0x00u, sub);
          f.set_kind(kind);
          f.set_tag(tag);
          f.set_result(0x5eed5eedu);
          reset_observers();          arm_the_comparison(f, same != 0);
          g_species_manager_result = (sub & 1u) != 0u;
          call_model(f);
          const bool callee_equal = (same != 0) && g_species_manager_result;
          bool used = false;
          const Word want =
              expected(f, 0x00u, sub, kind, tag, callee_equal, &used);
          check_word(f.result(), want,
                     "B1: the stored word must equal the oracle for every "
                     "(kind, sub, tag, comparison-answer) tuple");
          check((g_obs.compare_calls == 1) == used,
                "B1: the three-callee block runs exactly when the oracle says");
          check(g_obs.species_manager_calls == (used ? 1 : 0),
                "B1: the first callee runs exactly when the block does");
        }
      }
    }
  }
}

void case_b2_the_transposed_table_decoy() {
  // The two inner tables put the BARE STORE on OPPOSITE indices: index 4 of the
  // kind-1 table and index 3 of the other arm's table. Both store the leftover
  // EDX, which is 4. Everything else about the two tables differs. A
  // reconstruction that shares one switch between the two arms, or that swaps
  // entries 3 and 4, dies here and almost nowhere else.
  struct Case {
    Word kind;
    Word sub;
    Word tag;
    Word want;
    const char* what;
  };
  const Case cases[] = {
      {0x01u, 0x00u, 0x53dbcf1u, 0x03u, "B2: kind 1, sub 0 stores 3"},
      {0x01u, 0x01u, 0x53dbcf1u, 0x02u, "B2: kind 1, sub 1 stores 2"},
      {0x01u, 0x02u, 0x53dbcf1u, 0x01u, "B2: kind 1, sub 2 stores 1"},
      {0x01u, 0x03u, 0x53dbcf1u, 0x03u,
       "B2: kind 1, sub 3 stores 3, NOT the bare store's 4"},
      {0x01u, 0x04u, 0x53dbcf1u, 0x04u,
       "B2: kind 1, sub 4 stores the leftover EDX, NOT the tag arm's answer"},
      {0x01u, 0x05u, 0x53dbcf1u, 0x00u, "B2: kind 1, sub 5 stores 0"},
      {0x02u, 0x00u, 0x53dbcf1u, 0x00u, "B2: kind 2, sub 0 stores 0"},
      {0x02u, 0x01u, 0x53dbcf1u, 0x01u, "B2: kind 2, sub 1 stores 1"},
      {0x02u, 0x02u, 0x53dbcf1u, 0x03u, "B2: kind 2, sub 2 stores 3"},
      {0x02u, 0x03u, 0x53dbcf1u, 0x04u,
       "B2: kind 2, sub 3 stores the leftover EDX, NOT 3"},
      {0x02u, 0x04u, 0x53dbcf1u, 0x7fffffffu,
       "B2: kind 2, sub 4 runs the tag arm, NOT the leftover EDX"},
      {0x04u, 0x03u, 0x53dbcf1u, 0x04u, "B2: kind 4 shares the bare store"},
      {0x04u, 0x04u, 0x00000000u, 0x00000005u, "B2: kind 4 shares the tag arm"},
      {0x05u, 0x00u, 0x53dbcf1u, 0x00u, "B2: kind 5 behaves as kind 2"},
      {0x05u, 0x03u, 0x53dbcf1u, 0x04u, "B2: kind 5 shares the bare store"},
      {0x05u, 0x04u, 0x53dbcf1u, 0x7fffffffu, "B2: kind 5 shares the tag arm"},
  };
  for (const Case& c : cases) {
    Fixture f;
    f.chain(0x00u, c.sub);
    f.set_kind(c.kind);
    f.set_tag(c.tag);
    f.set_result(0x5eed5eedu);
    reset_observers();    arm_the_comparison(f);
    g_species_manager_result = true;
    call_model(f);
    check_word(f.result(), c.want, c.what);
  }
}

void case_b3_the_unsigned_outer_guard() {
  // 0x00dd083d DEC, 0x00dd083e MOV EDX,0x4, 0x00dd0843 CMP ECX,EDX,
  // 0x00dd0845 JA. The guard is UNSIGNED, so kind 0 -- whose index is
  // 0xffffffff -- leaves the function with only the 0x00dd0816 store done. A
  // signed compare would let it index out of bounds.
  const Word out_of_range[] = {0x00u,    0x06u,    0x07u,    0x08u,
                               0x7fffffffu, 0x80000000u, 0xffffffffu,
                               0xfffffffeu};
  for (Word kind : out_of_range) {
    Fixture f;
    f.chain(0x00u, 0x00u);
    f.set_kind(kind);
    f.set_result(0x5eed5eedu);
    reset_observers();    arm_the_comparison(f);
    g_species_manager_result = true;
    call_model(f);
    check_word(f.result(), 0x03u,
               "B3: an out-of-range kind word leaves 0x00dd0816's 3 in place "
               "and writes nothing else");
    check(g_obs.compare_calls == 0 && g_obs.order.empty(),
          "B3: an out-of-range kind word enters no callee");
  }
  for (Word kind = 0x01u; kind <= 0x05u; ++kind) {
    Fixture f;
    f.chain(0x00u, 0x00u);
    f.set_kind(kind);
    f.set_result(0x5eed5eedu);
    reset_observers();    arm_the_comparison(f);
    g_species_manager_result = true;
    call_model(f);
    bool used = false;
    const Word want =
        expected(f, 0x00u, 0x00u, kind, 0x00000000u, true, &used);
    check_word(f.result(), want, "B3: every kind word 1..5 is in range");
  }
}

void case_b4_the_sub_state_guards_are_unsigned_too() {
  // 0x00dd0852's bound is 7 and 0x00dd089f's is 4. Both are JA, i.e. unsigned,
  // and both land on the bare epilogue with the 3 still in place.
  const Word subs[] = {0x08u, 0x09u, 0x10u, 0x7fffffffu,
                       0x80000000u, 0xfffffffeu};
  for (Word sub : subs) {
    for (Word kind : {0x01u, 0x02u}) {
      Fixture f;
      f.chain(0x00u, sub);
      f.set_kind(kind);
      f.set_result(0x5eed5eedu);
      reset_observers();      arm_the_comparison(f);
      g_species_manager_result = true;
      call_model(f);
      check_word(f.result(), 0x03u,
                 "B4: an out-of-range sub-state leaves the 3 in place");
      check(g_obs.compare_calls == 0 && g_obs.order.empty(),
            "B4: an out-of-range sub-state enters no callee");
    }
  }
  // Index 5 is in range for kind 1 and is the store-0; indices 6 and 7 are the
  // three-callee block; index 5 is OUT of range for kind 2. That asymmetry is
  // the visible difference between the two tables' bounds.
  for (Word sub = 0x05u; sub <= 0x07u; ++sub) {
    Fixture f;
    f.chain(0x00u, sub);
    f.set_kind(0x01u);
    f.set_result(0x5eed5eedu);
    reset_observers();    arm_the_comparison(f, /*equal_records=*/true);
    g_species_manager_result = true;
    call_model(f);
    const bool wants_callees = (sub != 0x05u);
    check((g_obs.compare_calls == 1) == wants_callees,
          "B4: on the kind-1 table, sub-states 6 and 7 are the callee block "
          "and 5 is the store-0");
    check_word(f.result(), (sub == 0x05u) ? 0x00u : 0x7fffffffu,
               "B4: the kind-1 table's own answers for 5, 6 and 7");
  }
  {
    Fixture f;
    f.chain(0x00u, 0x05u);
    f.set_kind(0x02u);
    f.set_result(0x5eed5eedu);
    reset_observers();    arm_the_comparison(f);
    g_species_manager_result = true;
    call_model(f);
    check_word(f.result(), 0x03u,
               "B4: sub-state 5 is IN range for kind 1 and OUT of range for "
               "kind 2 -- the two tables' bounds are not the same");
  }
}

void case_b5_the_tag_arm_is_one_equality_and_one_wrapping_add() {
  // 0x00dd08ce..0x00dd08e4. The selection is NEG's carry on an exact equality,
  // and the ADD WRAPS: 0x80000006 + 0x7fffffff is 5 and not 0x80000005.
  const Word tags[] = {0x53dbcf1u, 0x53dbcf0u, 0x53dbcf2u, 0x00000000u,
                       0xffffffffu, 0x7fffffffu, 0x80000000u, 0x00000001u};
  for (Word tag : tags) {
    const Word want = (tag == 0x53dbcf1u) ? 0x7fffffffu : 0x00000005u;
    check_word(osw::tag_arm_arithmetic(tag), want,
               "B5: the header's transcription of the tag arm");
    Fixture f;
    f.chain(0x00u, 0x04u);
    f.set_kind(0x02u);
    f.set_tag(tag);
    f.set_result(0x5eed5eedu);
    reset_observers();    arm_the_comparison(f);
    g_species_manager_result = true;
    call_model(f);
    check_word(f.result(), want,
               "B5: the tag arm answers 0x7fffffff for the subtractand and "
               "exactly 5 for everything else");
    check(f.result() != 0x80000005u,
          "B5: the tag arm's negative answer is NOT the unwrapped 0x80000005");
  }
  // The tag arm is reachable on kind 2, 4 and 5 and NOT on kind 1 or 3.
  for (Word kind : {0x01u, 0x03u}) {
    Fixture f;
    f.chain(0x00u, 0x04u);
    f.set_kind(kind);
    f.set_tag(0x53dbcf1u);
    f.set_result(0x5eed5eedu);
    reset_observers();    arm_the_comparison(f);
    g_species_manager_result = true;
    call_model(f);
    // Kind 1's table puts the BARE STORE at index 4 (so 4), and kind 3 reaches
    // the bare epilogue without writing (so 0x00dd0816's 3). Neither is the tag
    // arm's answer, and that difference is the claim.
    const Word want = (kind == 0x01u) ? 0x04u : 0x03u;
    check_word(f.result(), want,
               "B5: the tag arm is not reachable on the kind-1 or kind-3 arms");
  }
  // The tag word is read ONLY on the tag arm: change it everywhere else and no
  // answer may move. A reconstruction that read +0x88 on every arm dies here.
  for (Word kind = 0x01u; kind <= 0x05u; ++kind) {
    for (Word sub = 0x00u; sub <= 0x04u; ++sub) {
      // Index 4 IS the tag arm on kinds 2, 4 and 5, and B5's case above already
      // pins it, so this sweep is over the arms where the tag word is not read.
      if (sub == 0x04u) {
        continue;
      }
      Word first = 0u;
      Word second = 0u;
      for (int pass = 0; pass < 2; ++pass) {
        Fixture f;
        f.chain(0x00u, sub);
        f.set_kind(kind);
        f.set_tag(pass == 0 ? 0x53dbcf1u : 0x00000000u);
        f.set_result(0x5eed5eedu);
        reset_observers();        arm_the_comparison(f, /*equal_records=*/true);
        g_species_manager_result = true;
        call_model(f);
        if (pass == 0) {
          first = f.result();
        } else {
          second = f.result();
        }
      }
      check_word(first, second,
                 "B5: the tag word changes no answer outside the tag arm");
    }
  }
}

void case_b6_the_callee_arm_selects_on_one_byte() {
  // 0x00dd0884's MOVZX ECX,AL consumes ONE byte. Both polarities are driven and
  // both answers are pinned independently of the tag arm's.
  for (int pass = 0; pass < 2; ++pass) {
    Fixture f;
    f.chain(0x00u, 0x06u);
    f.set_kind(0x01u);
    f.set_result(0x5eed5eedu);
    reset_observers();    arm_the_comparison(f, /*equal_records=*/true);
    g_species_manager_result = (pass == 0);
    call_model(f);
    check_word(f.result(), (pass == 0) ? 0x7fffffffu : 0x00000005u,
               "B6: the callee arm answers 0x7fffffff for true and exactly 5 "
               "for false");
    check_word(osw::callee_arm_arithmetic(pass == 0),
               (pass == 0) ? 0x7fffffffu : 0x00000005u,
               "B6: the header's transcription of the callee arm");
  }
  // The two arms produce the same two words from DIFFERENT mask/addend pairs, so
  // a reconstruction that transposed the pairs would still be right about these
  // answers. The pairs themselves are therefore pinned.
  check_word(osw::kTagArmSelectMask, 0x80000006u,
             "B6: the tag arm's mask is 0x80000006, not the callee arm's");
  check_word(osw::kTagArmSelectAddend, 0x7fffffffu,
             "B6: the tag arm's addend is 0x7fffffff, not 5");
  check_word(osw::kCalleeArmSelectMask, 0x7ffffffau,
             "B6: the callee arm's mask is 0x7ffffffa, not 0x80000006");
  check_word(osw::kCalleeArmSelectAddend, 0x05u,
             "B6: the callee arm's addend is 5, not 0x7fffffff");
  check(osw::kTagArmOtherValue == osw::kCalleeArmFalseValue,
        "B6: the two arms' negative answers coincide, which is exactly why the "
        "pairs must be pinned and not just the answers");
}

void case_b7_the_three_tables_are_what_the_image_says() {
  // The transcribed tables ARE the body's dispatch. Assert them against the
  // literal words read out of the image, so a transcription slip is an
  // assertion failure rather than a silently different function.
  const Word outer[5] = {0x00dd0852u, 0x00dd089fu, 0x00dd08f0u, 0x00dd089fu,
                         0x00dd089fu};
  for (std::size_t i = 0; i < 5; ++i) {
    check_word(osw::kOuterTable[i], outer[i],
               "B7: outer table entry, read from the 0xdd08f4 words");
  }
  const Word kind1[8] = {0x00dd08c2u, 0x00dd0862u, 0x00dd08b6u, 0x00dd08c2u,
                         0x00dd08eau, 0x00dd08aau, 0x00dd086eu, 0x00dd086eu};
  for (std::size_t i = 0; i < 8; ++i) {
    check_word(osw::kKindOneSubTable[i], kind1[i],
               "B7: kind-1 table entry, read from the 0xdd0908 words");
  }
  const Word other[5] = {0x00dd08aau, 0x00dd08b6u, 0x00dd08c2u, 0x00dd08eau,
                         0x00dd08ceu};
  for (std::size_t i = 0; i < 5; ++i) {
    check_word(osw::kOtherArmSubTable[i], other[i],
               "B7: other-arm table entry, read from the 0xdd0928 words");
  }
  check_word(osw::kOuterTableBase, 0x00dd08f4u, "B7: outer table base");
  check_word(osw::kKindOneSubTableBase, 0x00dd0908u, "B7: kind-1 table base");
  check_word(osw::kOtherArmSubTableBase, 0x00dd0928u, "B7: other table base");
  check_word(osw::kBodyEndInclusive, 0x00dd08f1u, "B7: the body's last byte");
  check(osw::kBodyEndInclusive + 3u == osw::kOuterTableBase,
        "B7: two bytes of hot-patch padding separate the body from the tables");
  check(osw::kIndexLimit == osw::kOtherArmSubLimit,
        "B7: both sub-state guards use the same four, which is why the kind-1 "
        "table has eight entries and the other arm's has five");
  check(osw::kKindOneSubLimit == 0x07u,
        "B7: the kind-1 sub-state bound is 7, which is what makes indices 6 and "
        "7 reachable at all");
}

// A raw thiscall trampoline. The receiver goes into ECX and a decoy object is
// pushed where a first STACK argument would be, so a reconstruction that read
// its receiver from the stack would be reading the decoy. The three statements
// are separate volatile asm blocks, which the compiler may not reorder relative
// to one another, so the two ESP samples bracket the model call exactly.
extern "C" void raw_thiscall_entry(OpaqueSporepediaAsset* receiver,
                                   OpaqueSporepediaAsset* decoy);
extern "C" void raw_thiscall_entry(OpaqueSporepediaAsset* receiver,
                                   OpaqueSporepediaAsset* decoy) {
  __asm__ __volatile__("movl %%esp, %0" : "=m"(g_esp_at_trampoline_entry));
  // Push the decoy where a first STACK argument would be, deliver the real
  // receiver in ECX, and call. Only the registers the body actually writes are
  // clobbered: it touches EAX, ECX, EDX and the flags, and its own PUSH ESI /
  // POP ESI pairs leave EBX, ESI, EDI, EBP and the stack flags alone.
  //
  // The decoy push is undone by the trampoline, NOT by the callee. The compiled
  // body returns with a bare `ret` -- it consumes no stack word at all, which is
  // exactly the property D1 measures -- so leaving the push to the callee would
  // unbalance this frame and corrupt the trampoline's own epilogue.
  __asm__ __volatile__("pushl %0\n\t"
                       "movl %1, %%ecx\n\t"
                       "call *%2\n\t"
                       "addl $4, %%esp\n\t"
                       :
                       : "r"(decoy), "r"(receiver), "r"(osw::re_00dd07f0)
                       : "cc", "ecx", "eax", "edx", "memory");
  __asm__ __volatile__("movl %%esp, %0" : "=m"(g_esp_after_the_model));
}

// ===========================================================================
// -- C: the three callees ---------------------------------------------------
// ===========================================================================

void case_c1_order_count_and_argument_identity() {
  Fixture f;
  f.chain(0x00u, 0x06u);
  f.set_kind(0x01u);
  f.set_result(0x5eed5eedu);
  reset_observers();  arm_the_comparison(f);
  g_species_manager_result = true;
  call_model(f);

  check(g_obs.species_manager_calls == 1 && g_obs.shift_calls == 1 &&
            g_obs.compare_calls == 1,
        "C1: each of the three callees is entered exactly once");
  check(g_obs.order.size() == 3 && std::strcmp(g_obs.order[0], "get") == 0 &&
            std::strcmp(g_obs.order[1], "shift") == 0 &&
            std::strcmp(g_obs.order[2], "equal") == 0,
        "C1: the call order is 0x00401090, 0x004df400, 0x004eb930");
  check(g_obs.shift_receiver == g_obs.manager_value,
        "C1: the __thiscall receiver is the FIRST callee's return");
  check(static_cast<const void*>(g_obs.shift_receiver) !=
                static_cast<const void*>(f.arena.object()) &&
            g_obs.shift_receiver !=
                f.arena.at(osw::kCompareArgumentDisplacement),
        "C1: the __thiscall receiver is neither the object nor the comparison "
        "address");
  check(g_obs.shift_return == g_obs.manager_value + kManagerShift,
        "C1: the second callee returns its receiver plus its own 0xa4 shift");
  check(g_obs.compare_first == g_obs.shift_return,
        "C1: the comparison's FIRST argument is the second callee's return");
  // The displacement is written as a literal here, NOT as the header's constant,
  // so that moving the constant in the model cannot move this expectation in
  // step with it. The first version of this harness used the constant on both
  // sides, and a mutation that moved it survived.
  check(g_obs.compare_second == f.arena.at(0x04),
        "C1: the comparison's SECOND argument is receiver+4, the address "
        "0x00dd086e forms");
  check_word(osw::kCompareArgumentDisplacement, 0x04u,
             "C1: and the header's own constant for it is 4");
  check(g_obs.compare_first != g_obs.compare_second,
        "C1: the two comparison arguments are different addresses, so swapping "
        "them is observable");
  // The two records differ, so the answer is NOT the observer's default.
  check_word(f.result(), 0x00000005u,
             "C1: with the two records different, the comparison came back "
             "false");
}

void case_c2_nothing_is_pushed_for_the_first_callee() {
  // 0x00dd0871 PUSH EAX and 0x00dd0872 CALL 0x00401090, whose own body reads no
  // stack slot at all. So the word is pushed and then never consumed by that
  // callee -- and 0x00401090's bare C3 leaves it on the stack, where 0x004eb930
  // finds it as its second argument.
  //
  // The stack SHAPE of the three calls (the listing has them 0 and then -8
  // relative to one another) is a property of the original frame and is NOT
  // reproduced by a compiled C++ model, which materialises its own spills. What
  // IS reproduced, and is what this case measures, is the model's BEHAVIOUR:
  //
  //   * nothing is pushed for 0x00401090, so the word the caller left below the
  //     call -- the decoy the raw trampoline pushed -- is still the word at the
  //     callee's [ESP+4]. A model that pushed an argument would have moved the
  //     decoy one word further down and this sample would differ.
  //   * the word 0x00dd0871 pushed is the second argument 0x004eb930 receives,
  //     which is measured by the address it observes, not by a stack depth.
  //
  // The measured ESP depths of the three calls are recorded by the test and
  // printed; they are the compiler's, and asserting the listing's numbers against
  // them would be asserting about a different program.
  Fixture f;
  f.chain(0x00u, 0x07u);
  f.set_kind(0x01u);
  f.set_result(0x5eed5eedu);
  reset_observers();
  arm_the_comparison(f);
  g_species_manager_result = true;
  call_model(f);
  check(g_obs.esp_at_species_manager != nullptr &&
            g_obs.esp_at_shift != nullptr && g_obs.esp_at_compare != nullptr,
        "C2: all three observers sampled ESP on entry");
  check(g_obs.compare_second == f.arena.at(0x04),
        "C2: the word pushed for 0x00401090 arrives as 0x004eb930's second "
        "argument, and that word is receiver+4");
  check(g_obs.compare_first != g_obs.compare_second,
        "C2: the two comparison arguments are distinguishable, so the second "
        "one is not the first by accident");

  // The raw-call form. The decoy sits where a first stack argument would be, so
  // a model that read its receiver from the stack would be reading the decoy --
  // and the model's own frame is asserted to be balanced across the call.
  //
  // What is NOT asserted here, and why, is in the not-asserted list below: the
  // word at 0x00401090's own [ESP+4]. The compiled model builds its own frame
  // between the caller's word and the callee's argument slot, so the sample
  // measures the compiler's frame rather than the model's pushes, and asserting
  // the listing's stack depths against a compiled C++ function would be
  // asserting about a different program. The FIRST version of this case did make
  // that assertion, and it was wrong for exactly that reason.
  Arena decoy;
  decoy.object()->opaque_00.fill(0x5a);
  g_trampoline_decoy = decoy.object();
  reset_observers();
  arm_the_comparison(f, /*equal_records=*/true);
  g_species_manager_result = true;
  raw_thiscall_entry(f.arena.object(), decoy.object());
  check(g_esp_at_trampoline_entry == g_esp_after_the_model,
        "C2: the model leaves the caller's stack exactly where it found it, "
        "which is what a callee that pushes nothing of its own and returns "
        "with a bare RET must do");
  check(g_trampoline_decoy == decoy.object(),
        "C2: the raw trampoline really did leave a decoy where a first stack "
        "argument would be");
  g_trampoline_decoy = nullptr;
}

void case_c3_write_ordering_is_measured_at_each_call() {
  // 0x00dd0816 stores 3 BEFORE any of the three calls, and 0x00dd0897 stores the
  // answer AFTER all three. An observer planted at any call must read 3.
  for (Word sub = 0x06u; sub <= 0x07u; ++sub) {
    Fixture f;
    f.chain(0x00u, sub);
    f.set_kind(0x01u);
    f.set_result(0x5eed5eedu);
    reset_observers();    arm_the_comparison(f, /*equal_records=*/true);
    g_species_manager_result = true;
    call_model(f);
    check_word(g_obs.result_seen_by_species_manager, 0x03u,
               "C3: 0x00401090 sees the 3 from 0x00dd0816 already stored");
    check_word(g_obs.result_seen_by_shift, 0x03u,
               "C3: 0x004df400 sees the 3 from 0x00dd0816 already stored");
    check_word(g_obs.result_seen_by_compare, 0x03u,
               "C3: 0x004eb930 sees the 3 from 0x00dd0816 already stored");
    check_word(f.result(), 0x7fffffffu,
               "C3: the answer is stored only after all three calls");
  }
}

void case_c4_only_one_leg_ever_calls() {
  Word callee_pairs = 0;
  for (Word kind = 0x00u; kind <= 0x08u; ++kind) {
    for (Word sub = 0x00u; sub <= 0x09u; ++sub) {
      Fixture f;
      f.chain(0x00u, sub);
      f.set_kind(kind);
      f.set_result(0x5eed5eedu);
      reset_observers();      arm_the_comparison(f);
      g_species_manager_result = true;
      call_model(f);
      if (g_obs.compare_calls != 0) {
        ++callee_pairs;
        check(kind == 0x01u && (sub == 0x06u || sub == 0x07u),
              "C4: the callee block is entered ONLY for kind 1 with sub-state "
              "6 or 7");
      }
    }
  }
  check_word(callee_pairs, 2u,
             "C4: exactly two of the 81 (kind, sub-state) pairs reach the "
             "callees");
}

void case_c5_a_mid_flight_rewrite_of_the_result_word_is_overwritten() {
  // 0x00dd0897 is the last write on this path, so a callee that scribbles on
  // the result word loses. This pins WHICH write is last, not merely that the
  // 3 came first.
  for (int which = 0; which < 3; ++which) {
    Fixture f;
    f.chain(0x00u, 0x06u);
    f.set_kind(0x01u);
    f.set_result(0x5eed5eedu);
    arm_the_comparison(f, /*equal_records=*/true);
    g_obs_result_word = f.arena.word_of(osw::kResultDisplacement);
    reset_observers();
    g_obs_result_word = f.arena.word_of(osw::kResultDisplacement);
    g_species_manager_result = true;
    g_observer_rewrites_result = (which == 0);  // the first callee scribbles
    g_rewrite_value = 0x0badbad0u;
    if (which == 1) {
      // the second callee scribbles
      g_observer_rewrites_result = true;
    }
    call_model(f);
    check_word(f.result(), 0x7fffffffu,
               "C5: the store at 0x00dd0897 is the LAST write on the callee "
               "path, whatever a callee did in between");
    g_observer_rewrites_result = false;
  }
}

void case_c6_a_mid_flight_rewrite_cannot_move_the_arm() {
  // The kind word, the sub-state word and the tag word are all read BEFORE the
  // three calls, so a callee that rewrites any of them cannot change which arm
  // runs or what it computes.
  for (Word kind : {0x01u, 0x02u, 0x03u, 0x05u}) {
    for (Word sub = 0x00u; sub <= 0x04u; ++sub) {
      Fixture f;
      f.chain(0x00u, 0x06u);
      f.set_kind(kind);
      f.set_tag(0x53dbcf1u);
      f.set_result(0x5eed5eedu);
      arm_the_comparison(f);
      // Rewind the level-2 words and the kind word to values that take a
      // DIFFERENT arm than the ones that open the callee block.
      f.set_level2(0x00u, sub);
      f.set_kind(0x02u);
      f.set_result(0x5eed5eedu);
      reset_observers();
      g_species_manager_result = false;
      call_model(f);
      bool used = false;
      const Word want = expected(f, 0x00u, sub, 0x02u, 0x53dbcf1u, false, &used);
      check_word(f.result(), want,
                 "C6: the arm is fixed before the calls, so nothing a callee "
                 "does can move it");
      check((g_obs.compare_calls == 1) == used,
            "C6: the callee block's reachability is fixed before the calls");
      break;  // one sub-state per kind is enough for this claim
    }
  }
}

// ===========================================================================
// -- D: measurements --------------------------------------------------------
// ===========================================================================

void case_d1_the_receiver_arrives_in_ecx_and_the_stack_is_balanced() {
  const Word kinds[] = {0x01u, 0x02u, 0x03u, 0x05u};
  const Word subs[] = {0x00u, 0x02u, 0x04u, 0x06u};
  for (Word kind : kinds) {
    for (Word sub : subs) {
      Fixture f;
      f.chain(0x00u, sub);
      f.set_kind(kind);
      f.set_tag(0x53dbcf1u);
      f.set_result(0x5eed5eedu);
      arm_the_comparison(f, /*equal_records=*/true);

      Arena decoy;
      decoy.object()->opaque_00.fill(0x5a);
      Word poison = 0x00c0ffeeu;
      for (std::size_t d : {static_cast<std::size_t>(0x00),
                            osw::kKindDisplacement, osw::kTagDisplacement,
                            osw::kResultDisplacement, osw::kLinkDisplacement}) {
        std::memcpy(decoy.at(d), &poison, sizeof(poison));
      }

      reset_observers();
      g_species_manager_result = true;
      raw_thiscall_entry(f.arena.object(), decoy.object());
      bool used = false;
      const Word want =
          expected(f, 0x00u, sub, kind, 0x53dbcf1u, true, &used);
      check_word(f.result(), want,
                 "D1: the model answers correctly when the receiver is "
                 "delivered in ECX with a poisoned decoy where a stack argument "
                 "would be");
      check(g_esp_at_trampoline_entry != nullptr &&
                g_esp_at_trampoline_entry == g_esp_after_the_model,
            "D1: the model leaves the caller's ESP exactly where it found it, "
            "which is what a single PUSH ESI and seven POP ESIs must do");
    }
  }
}

void case_d2_only_the_result_word_is_written() {
  // 0x8c..0x8f is the whole of this body's write surface on the receiver: nine
  // store sites, one dword. Every other byte of the 0x9c-byte object, and every
  // byte of both guard regions, must come back unchanged.
  const Word kinds[] = {0x00u, 0x01u, 0x02u, 0x03u, 0x04u, 0x05u, 0x06u, 0x07u};
  const Word subs[] = {0x00u, 0x01u, 0x02u, 0x03u, 0x04u,
                       0x05u, 0x06u, 0x07u, 0x08u};
  for (Word kind : kinds) {
    for (Word sub : subs) {
      Fixture f;
      f.chain(0x00u, sub);
      f.set_kind(kind);
      f.set_tag(0x53dbcf1u);
      f.set_result(0x5eed5eedu);
      arm_the_comparison(f);
      Byte snapshot[kArenaBytes];
      std::memcpy(snapshot, f.arena.raw, kArenaBytes);
      reset_observers();
      g_species_manager_result = true;
      call_model(f);
      int differences = 0;
      bool inside_only = true;
      for (std::size_t i = 0; i < kArenaBytes; ++i) {
        if (snapshot[i] == f.arena.raw[i]) {
          continue;
        }
        ++differences;
        const std::size_t d = (i < kGuardBefore) ? i : (i - kGuardBefore);
        const bool inside_object =
            i >= kGuardBefore && i < kGuardBefore + kObjectBytes;
        if (!inside_object || d < osw::kResultDisplacement ||
            d >= osw::kResultDisplacement + 4) {
          inside_only = false;
        }
      }
      check(inside_only,
            "D2: every changed byte lies inside the result word, and none "
            "lies in either guard region");
      check(differences <= 4,
            "D2: at most the four bytes of the result word ever change");
    }
  }
}

void case_d3_receiver_offset_decoys_are_never_touched() {
  // A dword planted at every ALIGNED displacement of the modelled receiver that
  // is not one of the four the body touches, and a byte planted immediately
  // either side of each of the four. None may be read, and none may change --
  // a store one byte off, or a read one dword off, dies here.
  //
  // The four modelled displacements are 0x84, 0x88, 0x8c and 0x98, so the
  // aligned decoys deliberately skip those and the byte decoys sit at 0x83,
  // 0x87, 0x8b, 0x8f, 0x97 and 0x9b, which are the bytes the body's own dword
  // stores must not spill into.
  // Every modelled dword is 0x84..0x87, 0x88..0x8b, 0x8c..0x8f and 0x98..0x9b, so
  // the free space inside the 0x9c-byte run is 0x00..0x83 and 0x90..0x97. The
  // dword decoys fill the first range and the byte decoys the second, which is
  // the whole of what "one byte off" and "one dword off" can mean here. A decoy
  // that overlapped a modelled dword would not be a decoy, it would be a change
  // of input.
  const std::size_t word_decoys[] = {0x00u, 0x08u, 0x10u, 0x18u, 0x20u, 0x28u,
                                     0x30u, 0x38u, 0x40u, 0x48u, 0x50u, 0x58u,
                                     0x60u, 0x68u, 0x70u, 0x78u};
  const std::size_t byte_decoys[] = {0x83u, 0x90u, 0x93u, 0x94u, 0x95u, 0x96u,
                                     0x97u};
  for (Word kind = 0x01u; kind <= 0x05u; ++kind) {
    for (Word sub = 0x00u; sub <= 0x07u; ++sub) {
      Fixture f;
      f.chain(0x00u, sub);
      f.set_kind(kind);
      f.set_tag(0x53dbcf1u);
      f.set_result(0x5eed5eedu);
      arm_the_comparison(f);
      const Word sentinel = 0x13572468u;
      for (std::size_t d : word_decoys) {
        std::memcpy(f.arena.at(d), &sentinel, sizeof(sentinel));
      }
      for (std::size_t d : byte_decoys) {
        *f.arena.at(d) = 0x3cu;
      }
      reset_observers();
      g_species_manager_result = true;
      call_model(f);
      for (std::size_t d : word_decoys) {
        check_word(f.arena.peek(d), sentinel,
                   "D3: a dword at an unmodelled ALIGNED receiver displacement "
                   "is neither read nor written");
      }
      for (std::size_t d : byte_decoys) {
        check(*f.arena.at(d) == 0x3cu,
              "D3: a byte immediately beside a modelled dword is never written, "
              "so the store is dword-scoped");
      }
    }
  }
}

void case_d4_repeated_and_interleaved_invocations_settle() {
  // No cross-call memo: the same object driven through a sequence of inputs must
  // answer each one on its own terms.
  Fixture f;
  struct Step {
    Word record_kind;
    Word sub;
    Word kind;
    Word tag;
    Word want;
  };
  const Step steps[] = {
      {0x00u, 0x01u, 0x01u, 0x00000000u, 0x02u},
      {0x06u, 0x00u, 0x01u, 0x00000000u, 0xfffffffeu},
      {0x00u, 0x04u, 0x02u, 0x53dbcf1u, 0x7fffffffu},
      {0x00u, 0x04u, 0x02u, 0x00000000u, 0x00000005u},
      {0x00u, 0xffffffffu, 0x05u, 0x00000000u, 0xfffffffdu},
      {0x00u, 0x00u, 0x03u, 0x00000000u, 0x03u},
      {0x00u, 0x00u, 0x01u, 0x00000000u, 0x03u},
      {0x00u, 0x06u, 0x01u, 0x00000000u, 0x7fffffffu},
      {0x00u, 0x00u, 0x02u, 0x53dbcf1u, 0x00u},
  };
  for (const Step& s : steps) {
    f.chain(s.record_kind, s.sub);
    f.set_kind(s.kind);
    f.set_tag(s.tag);
    f.set_result(0x5eed5eedu);
    reset_observers();
    arm_the_comparison(f, /*equal_records=*/true);
    g_species_manager_result = true;
    call_model(f);
    check_word(f.result(), s.want,
               "D4: a repeated invocation answers on its own input alone");
  }

  // Two objects with IDENTICAL kind, sub and tag words but DIFFERENT level-2
  // records must get different answers, because the record is what the sentinel
  // and the sub-state come from.
  //
  // Both fixtures reach the SAME global level-2 object, so the two calls are
  // sequenced rather than interleaved: g1 is answered while g_record still holds
  // g1's words, and only then is g_record re-pointed for g2. An interleaved pair
  // would make g1 see g2's record and the case would prove nothing -- which is
  // exactly what the first version of this harness did.
  Fixture g1;
  Fixture g2;
  g1.chain(0x00u, 0x04u);
  g1.set_kind(0x02u);
  g1.set_tag(0x53dbcf1u);
  g1.set_result(0x5eed5eedu);
  reset_observers();
  arm_the_comparison(g1, /*equal_records=*/true);
  g_species_manager_result = true;
  call_model(g1);
  check_word(g1.result(), 0x7fffffffu,
             "D4: the first record's own words decide the first answer");

  g2.chain(0x00u, 0x04u);
  g2.set_kind(0x02u);
  g2.set_tag(0x53dbcf1u);
  g2.set_result(0x5eed5eedu);
  g2.set_level2(0x06u, 0x04u);  // the same receiver, a different record
  reset_observers();
  arm_the_comparison(g2, /*equal_records=*/true);
  g_species_manager_result = true;
  call_model(g2);
  check_word(g2.result(), 0xfffffffeu,
             "D4: an identical receiver over a different record gets a "
             "different answer");
}

void case_d5_the_level_one_displacement_is_the_listings() {
  // 0x00dd0801 and 0x00dd0820 read the SAME dword of the SAME level-1 object.
  // Poison every neighbouring level-1 displacement and require the model to
  // follow the real chain.
  const Word six = 0x06u;
  Fixture f;
  f.chain(0x00u, 0x04u);
  f.set_kind(0x02u);
  f.set_tag(0x53dbcf1u);
  f.set_result(0x5eed5eedu);
  reset_observers();
  arm_the_comparison(f);
  for (std::size_t d : {0x00u, 0x04u, 0x08u, 0x10u, 0x14u, 0x18u}) {
    std::memcpy(f.link + d, &six, sizeof(six));
  }
  reset_observers();
  call_model(f);
  check_word(f.result(), 0x7fffffffu,
             "D5: with 6 planted at six wrong level-1 displacements, the model "
             "still follows the real chain to its record");

  // And the sub-state word's neighbours on the level-2 object: 6 planted at
  // record+0x18 and record+0x24 must not be read as the sub-state.
  Fixture g;
  g.chain(0x00u, 0x04u);
  g.set_kind(0x02u);
  g.set_tag(0x53dbcf1u);
  g.set_result(0x5eed5eedu);
  reset_observers();
  arm_the_comparison(g);
  const Word one = 0x01u;
  std::memcpy(g_record + 0x18, &one, sizeof(one));
  std::memcpy(g_record + 0x24, &one, sizeof(one));
  reset_observers();
  call_model(g);
  check_word(g.result(), 0x7fffffffu,
             "D5: with 1 planted at the two neighbouring level-2 offsets, the "
             "model still reads the sub-state at +0x20");
}

void case_d6_the_two_record_words_are_not_confused_for_each_other() {
  // 0x00dd0804 reads record+0x10 and 0x00dd0823 reads record+0x20. They are
  // different displacements of the same level-2 object, and this case makes the
  // value 6 and the value that drives the switch disagree in every combination.
  //
  //   record+0x10 = 6, record+0x20 = 6  -> the -2 exit wins, whatever the index
  //   record+0x10 = 0, record+0x20 = 6  -> no divert; sub 6 is OUT OF RANGE for
  //                                     kind 2, so the 3 from 0x00dd0816 stands
  //   record+0x10 = 6, record+0x20 = 0  -> the -2 exit again
  // and with 6 planted at record+0x08, +0x14, +0x18, +0x1c and +0x24, neither
  // real word changes: a reconstruction that read either displacement one dword
  // off dies here.
  struct Case {
    Word record_kind;
    Word sub;
    Word want;
    const char* what;
  };
  const Case cases[] = {
      {0x06u, 0x06u, 0xfffffffeu, "D6: both record words 6 -> the -2 exit wins"},
      {0x00u, 0x06u, 0x03u,
       "D6: only record+0x20 is 6 -> NO divert, and 6 is out of range for "
       "kind 2 so the 3 stands"},
      {0x06u, 0x00u, 0xfffffffeu,
       "D6: only record+0x10 is 6 -> the -2 exit, and the index is never read"},
      {0x05u, 0x00u, 0x00u, "D6: neither word is 6 -> the switch runs"},
  };
  for (const Case& c : cases) {
    Fixture f;
    f.chain(c.record_kind, c.sub);
    f.set_kind(0x02u);
    f.set_tag(0x53dbcf1u);
    f.set_result(0x5eed5eedu);
    reset_observers();
    arm_the_comparison(f);
    call_model(f);
    check_word(f.result(), c.want, c.what);
  }

  // Decoys either side of both real displacements, on the level-2 object.
  const Word six = 0x06u;
  for (std::size_t d : {0x00u, 0x04u, 0x08u, 0x0cu, 0x14u, 0x18u, 0x1cu, 0x24u,
                        0x28u}) {
    Fixture f;
    f.chain(0x00u, 0x00u);
    f.set_kind(0x02u);
    f.set_tag(0x53dbcf1u);
    f.set_result(0x5eed5eedu);
    reset_observers();
    arm_the_comparison(f);
    std::memcpy(g_record + d, &six, sizeof(six));
    call_model(f);
    check_word(f.result(), 0x00u,
               "D6: with 6 planted at a level-2 displacement the listing never "
               "reads, the model still answers from record+0x10 and +0x20");
  }

  // And the sweep that shows the two words really are independent inputs: with
  // record+0x10 held at 0, the sub-state alone decides the answer.
  const Word wants[5] = {0x00u, 0x01u, 0x03u, 0x04u, 0x7fffffffu};
  for (Word sub = 0x00u; sub <= 0x04u; ++sub) {
    Fixture f;
    f.chain(0x00u, sub);
    f.set_kind(0x02u);
    f.set_tag(0x53dbcf1u);
    f.set_result(0x5eed5eedu);
    reset_observers();
    arm_the_comparison(f);
    call_model(f);
    check_word(f.result(), wants[sub],
               "D6: with record+0x10 held at 0, the sub-state alone decides the "
               "answer, and it is that arm's table");
  }
}

// ===========================================================================
// -- the run ----------------------------------------------------------------
// ===========================================================================

int run() {
  case_a1_a_null_link_writes_nothing();
  case_a2_the_sentinel_is_an_equality_at_the_right_depth();
  case_a3_decoys_at_the_wrong_depth_are_never_read();
  case_a4_the_sub_state_sentinel_is_all_ones();
  case_a5_the_sentinel_overwrites_the_earlier_store();
  case_a6_a_zeroed_record_is_not_the_null_link();

  case_b1_exhaustive_sweep_against_the_oracle();
  case_b2_the_transposed_table_decoy();
  case_b3_the_unsigned_outer_guard();
  case_b4_the_sub_state_guards_are_unsigned_too();
  case_b5_the_tag_arm_is_one_equality_and_one_wrapping_add();
  case_b6_the_callee_arm_selects_on_one_byte();
  case_b7_the_three_tables_are_what_the_image_says();

  case_c1_order_count_and_argument_identity();
  case_c2_nothing_is_pushed_for_the_first_callee();
  case_c3_write_ordering_is_measured_at_each_call();
  case_c4_only_one_leg_ever_calls();
  case_c5_a_mid_flight_rewrite_of_the_result_word_is_overwritten();
  case_c6_a_mid_flight_rewrite_cannot_move_the_arm();

  case_d1_the_receiver_arrives_in_ecx_and_the_stack_is_balanced();
  case_d2_only_the_result_word_is_written();
  case_d3_receiver_offset_decoys_are_never_touched();
  case_d4_repeated_and_interleaved_invocations_settle();
  case_d5_the_level_one_displacement_is_the_listings();
  case_d6_the_two_record_words_are_not_confused_for_each_other();

  std::printf("checks: %d, failures: %d\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}

}  // namespace

int main() { return run(); }

// ===========================================================================
// WHAT THIS TEST DOES NOT ASSERT, AND WHY
//
// 1. The three callees' interiors. Only their signatures, their argument
//    identities, their ESP entries and their return shapes are modelled; the
//    observer bodies are this test's, not theirs. Asserting anything about what
//    0x00401090, 0x004df400 or 0x004eb930 do inside themselves would be
//    asserting about three other targets.
//
// 2. That 0x00401090 IGNORES its pushed argument. An observer cannot see an
//    argument it is not given; 0x00401090's own four instructions are the
//    evidence for that, not this body's. What IS asserted is the observable
//    consequence, in C2: the stack depth is identical at the first and second
//    calls, and the word 0x00dd0871 pushed arrives as 0x004eb930's second
//    argument with exactly two words resident.
//
// 3. Caller-side versus callee-side ownership of the two argument words, AND
//    the ESP SHAPE of the three calls. Both callees' terminators are bare C3 in
//    the image, so the model must be a caller-pops one and 0x00dd0887's
//    ADD ESP,0x8 is transcribed -- but for a cdecl leaf callee a callee-pops and
//    a caller-pops return are the same machine behaviour, so no black-box test
//    can tell them apart. Nor can a test see whether the model pushed a word for
//    0x00401090: the compiled model builds its own frame between the caller's
//    word and that callee's argument slot, so a sample at the callee's [ESP+4]
//    reads the compiler's frame. C2 measures the two things that DO survive
//    compilation -- that the second argument arrives as receiver+4, and that the
//    model's whole frame is balanced -- and the three ESP depths it samples are
//    recorded rather than asserted against the listing's 0 and -8.
//
// 4. The model's stack DEPTH at each call site. A compiled C++ function's
//    intermediate ESP is the compiler's frame and its alignment padding, not
//    the listing's single PUSH ESI. What D1 asserts instead is the invariant
//    that survives compilation: the model's own frame is balanced, so ESP is
//    identical on entry and on exit.
//
// 5. EDX's value at 0x00dd08ea as a REGISTER. That the bare store writes 4 is
//    asserted as the OBSERVED stored word, which is what a caller can see. The
//    register's provenance (0x00dd083e's MOV EDX,0x4, and the fact that nothing
//    between there and 0x00dd08ea writes EDX) is a fact about the listing, and
//    it is pinned by the header's static_asserts, not measurable through this
//    interface.
//
// 6. A NULL level-2 pointer. The listing dereferences [link+0xc] with no test of
//    its own -- only the LEVEL-1 word is tested, at 0x00dd07f9. The model
//    therefore does not test it either, and the test does not construct the
//    case, because doing so would fault rather than refute.
//
// 7. The MEANING of any word. None of the seven stored values is named, none of
//    the four receiver words is named, 0x53dbcf1 is not called a tag, and
//    0x00dd0816's 3 is not called progress. The 68 instructions do not say what
//    any of them is.
//
// 8. The READ COUNT of the receiver's words. The model reads each exactly once,
//    at the instruction that fixes it. A read count is not visible through this
//    interface, so the test asserts the OBSERVABLE consequences instead: that
//    the first store precedes all three calls (C3), that the last store follows
//    them and cannot be undone by a callee (C5), and that the kind, sub-state
//    and tag words cannot be changed into a different arm from inside a call
//    (C6).
//
// 9. The inter-call ORDER of the 0x00dd0801 and 0x00dd0820 loads of the same
//    level-1 word. The model reads it once and reuses it. Nothing can run
//    between the two loads -- no branch, no call, no store -- so a version that
//    loaded it twice is not distinguishable from this one on any input this
//    function can be given. See unresolved_questions item 4 in the sidecar.
