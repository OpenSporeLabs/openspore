// PKG-SWARM-W1-00641FD0 -- model test for VA 0x00641fd0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22)
//
// This is a falsification test, not a walk-through. It defines every direct
// callee of the body under reconstruction as an OBSERVER, so it sees every
// transfer the reconstruction makes -- which callee, with which arguments, in
// which order, and what each did to memory at the moment of the call -- and then
// drives the reconstruction with inputs chosen to BREAK the highest-risk
// hypotheses rather than to confirm them.
//
// THE THREE DIRECT CALLEES, all defined here as observers and nowhere else (and
// all three with the linkage the package header declares, which is why they sit
// outside this file's anonymous namespace):
//
//   0x0067cb30  cdecl, no argument. Sampled for: the value it returns must be the
//               base of the +0x5c read, and it must be reached exactly once and
//               only on the paths that get past the dispatch.
//   0x00613860  __thiscall, one stack word. Sampled for: that the word is the
//               receiver's OWN +0x08, passed by value and not by address, and
//               that the receiver is the service, not the object this body was
//               called on.
//   0x00612f50  __thiscall, four stack words. Sampled for: the argument ORDER, the
//               literal zero in the fourth, the identity of the third (the out
//               pointer), and -- the point of the whole test -- the value the out
//               pointer holds AT THE MOMENT OF THE CALL, which is the only way to
//               see the frame store at 0x00642030 rather than infer it.
//
// Plus the two two-level dispatches, supplied as tables the test owns: the
// receiver's (slot index 36 = 0x90 / 4) and the resolved handle's (slot index
// 1 = 0x04 / 4). Each table carries a distinct trap observer in the neighbouring
// slot on BOTH sides, and a decoy table is planted one level off at the
// receiver's +0x04 and at the handle's +0x04, so a reconstruction that dispatches
// one slot off, reads the wrong level of either table, or dispatches through a
// decoy planted at the wrong depth is caught rather than merely suspected. The
// receiver additionally carries a decoy FUNCTION POINTER at its own +0x90, which
// is what a collapsed two-level read would call.
//
// WHAT THIS TEST ASSERTS, in one place: the exit word of all five gate failures
// and of the two armed paths; that the cached word is a WORD (returned, not
// dereferenced, not tested as a byte); the sentinel 0xffffffff in BOTH words of
// the 8-byte object at the moment of the dispatch; that the two data arguments of
// 0x00612f50 are the values the dispatch WROTE rather than the sentinel; the
// argument order of both wide calls; that the acquire runs on the FAILURE arm as
// well as on the success arm; that it does not run at all when the resolved word
// is null; the displacement of both slots and the depth of both tables; the
// receiver is written by nothing; that nothing carries between two calls; and
// that the out slot is nulled by the body itself before the callee sees it.
//
// WHAT THIS TEST DELIBERATELY DOES NOT ASSERT, and why:
//
//  * The MEANING of the receiver's +0x3c word, of the +0x08 word, of the 8-byte
//    sentinel, of the 0x04/0x90 slots, or of the handle. No record fixes any of
//    them and the listing shows only that they are read, passed and returned.
//  * The prior contents of the out slot. The machine never initialises it, so its
//    value before 0x00642030 is indeterminate stack residue. The model seeds it
//    with a marker purely so that the store at 0x00642030 is observable; the test
//    asserts the value AT THE CALL, never the value before it.
//  * The return value of the acquire, or of 0x00612f50 beyond its byte. The
//    listing makes the acquire's return dead (0x00642053 overwrites EAX) and the
//    body only tests 0x00612f50's byte for non-zero.
//  * The upper three bytes of any callee's return. The body tests AL and nothing
//    else; the observers deliberately return 0x80 where the body must see "true".
//  * A receiver whose table word is null. The listing has no null test there, so
//    such a call would read the slot word out of the null page: the case is not
//    driven, because on this host it is a fault rather than an observation.
//  * Anything about the C types beyond the width.

#include "sw1_00641fd0_types.hpp"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace openspore::reconstruction::pkg_swarm_w1_00641fd0 {

// ============================ the scaffolding for the observers ============
//
// The three direct callees themselves are defined at the BOTTOM of this file,
// outside the anonymous namespace: the reconstruction's own translation unit
// reaches them through the package header's external declarations, so an
// internal-linkage definition would be a different function.

namespace {

// ---------------------------------------------------------------- scaffolding

int g_failures = 0;

#define CHECK(condition, ...)                                   \
  do {                                                          \
    if (!(condition)) {                                         \
      ++g_failures;                                             \
      std::printf("FAIL %s:%d: ", __FILE__, __LINE__);           \
      std::printf(__VA_ARGS__);                                 \
      std::printf("\n");                                        \
    }                                                           \
  } while (false)

#define CHECK_EQ_U(actual, expected, label)                              \
  do {                                                                   \
    const unsigned long long a_ = static_cast<unsigned long long>(actual);\
    const unsigned long long e_ = static_cast<unsigned long long>(expected);\
    if (a_ != e_) {                                                      \
      ++g_failures;                                                      \
      std::printf("FAIL %s:%d: %s is 0x%llx, expected 0x%llx\n", __FILE__, \
                  __LINE__, (label), a_, e_);                            \
    }                                                                    \
  } while (false)

using Body = void*(PKG_SW1_00641FD0_THISCALL*)(SporepediaAssetDataOtdb*);

// A table the test owns. 40 slots is the smallest run that covers index 36 with
// a decoy on either side; the same run covers index 1 for the handle.
struct Table {
  std::uint32_t slots[40];
};
static_assert(sizeof(Table) == 160, "40 dword slots");

// The objects the test hands the body. All three are plain byte runs with a
// generous tail, so a decoy can be planted at any neighbouring displacement and
// read back as a word without going out of bounds.
struct Fixture {
  std::uint8_t receiver[0x100];  // 0x40 is what the body reaches; the tail is decoys
  std::uint8_t root[0x80];
  std::uint8_t handle[0x40];
  Table receiver_table;
  Table handle_table;
  Table decoy_table;
};

Fixture g_fixture;

// The observer log. One string per event, so an ordering mistake shows up as a
// sequence mismatch rather than as a count.
std::vector<std::string> g_log;

// -- what each observer recorded ---------------------------------------------
std::uint32_t g_global_getter_calls = 0;
std::uint32_t g_key_present_calls = 0;
Service* g_key_present_receiver = nullptr;
Word g_key_present_argument = 0;
std::uint32_t g_resolve_calls = 0;
Service* g_resolve_receiver = nullptr;
Word g_resolve_first = 0;
Word g_resolve_second = 0;
void** g_resolve_out = nullptr;
Word g_resolve_fourth = 0;
void* g_resolve_out_at_call = nullptr;  // what *out held when the callee was entered


// How each observer behaves is configuration, not code, so one reconstruction
// serves every case.
struct Plan {
  std::uint8_t resolve_return = 1;          // the slot +0x90 dispatch's byte
  Word resolve_writes_first = 0xaaaa1111u;  // what the dispatch leaves in the pair
  Word resolve_writes_second = 0xbbbb2222u;
  std::uint8_t key_present_return = 1;      // 0x00613860's byte
  std::uint8_t resolve_out_return = 1;      // 0x00612f50's byte
  void* resolve_out_value = nullptr;        // what 0x00612f50 leaves in *out
  Word root_service_slot = 0;               // the word at the root's +0x5c
  Word receiver_cached = 0;                 // the word at the receiver's +0x3c
  Word receiver_argument = 0x0badf00du;     // the word at the receiver's +0x08
  std::uint32_t* root_service_target;       // the Service* handed over
};

Plan g_plan;

// The one service every case uses, so a stray receiver is visible as a pointer
// that is not it.
alignas(4) std::uint8_t g_service_object[0xa0] = {};

Service* the_service() { return reinterpret_cast<Service*>(g_plan.root_service_target); }

void configure() {
  std::memset(&g_fixture, 0, sizeof(g_fixture));
  g_log.clear();
  g_plan = Plan();
  g_global_getter_calls = 0;
  g_key_present_calls = 0;
  g_resolve_calls = 0;
  g_key_present_receiver = nullptr;
  g_key_present_argument = 0;
  g_resolve_receiver = nullptr;
  g_resolve_first = 0;
  g_resolve_second = 0;
  g_resolve_out = nullptr;
  g_resolve_fourth = 0;
  g_resolve_out_at_call = nullptr;
  g_plan.root_service_target = reinterpret_cast<std::uint32_t*>(g_service_object);
  g_plan.root_service_slot = reinterpret_cast<Word>(the_service());
  *word_at(g_fixture.root, kServiceRootServiceDisplacement) = g_plan.root_service_slot;
  // The receiver's own +0x5c is a DECOY: a valid service word, planted so that a
  // reconstruction reading the +0x5c from the wrong base dispatches into a callee
  // it should never reach.
  *word_at(g_fixture.receiver, kServiceRootServiceDisplacement) =
      reinterpret_cast<Word>(the_service());
}

// -- the slot +0x90 dispatch on the receiver --------------------------------
std::uint8_t PKG_SW1_00641FD0_THISCALL resolve_slot_90_observer(
    SporepediaAssetDataOtdb* self, HandlePair* pair) {
  (void)self;
  char text[128];
  std::snprintf(text, sizeof text, "resolve90(pair=%08x,%08x)",
                static_cast<unsigned>(pair->field_00),
                static_cast<unsigned>(pair->field_04));
  g_log.emplace_back(text);
  pair->field_00 = g_plan.resolve_writes_first;
  pair->field_04 = g_plan.resolve_writes_second;
  return g_plan.resolve_return;
}

std::uint8_t PKG_SW1_00641FD0_THISCALL resolve_slot_trap(SporepediaAssetDataOtdb* self,
                                                        HandlePair* pair) {
  (void)self;
  (void)pair;
  g_log.emplace_back("TRAP: receiver table, a slot other than 0x90 was called");
  return 0x7fu;
}

// -- the slot +0x04 dispatch on the resolved handle -------------------------
void PKG_SW1_00641FD0_THISCALL acquire_slot_04_observer(Acquired* self) {
  char text[128];
  std::snprintf(text, sizeof text, "acquire04(self=%p)", static_cast<void*>(self));
  g_log.emplace_back(text);
}

void PKG_SW1_00641FD0_THISCALL acquire_slot_trap(Acquired* self) {
  (void)self;
  g_log.emplace_back("TRAP: handle table, a slot other than 0x04 was called");
}

// ------------------------------------------------------------------ the case

Body the_body() { return &sporepedia_cached_handle_00641fd0; }

SporepediaAssetDataOtdb* receiver() {
  return reinterpret_cast<SporepediaAssetDataOtdb*>(g_fixture.receiver);
}

// The receiver's table: the real dispatch at index 36, a trap at 35 and at 37.
void arm_receiver_table() {
  std::memset(g_fixture.receiver_table.slots, 0, sizeof(g_fixture.receiver_table.slots));
  g_fixture.receiver_table.slots[kResolveSlotIndex - 1] =
      reinterpret_cast<std::uint32_t>(&resolve_slot_trap);
  g_fixture.receiver_table.slots[kResolveSlotIndex] =
      reinterpret_cast<std::uint32_t>(&resolve_slot_90_observer);
  g_fixture.receiver_table.slots[kResolveSlotIndex + 1] =
      reinterpret_cast<std::uint32_t>(&resolve_slot_trap);
  *word_at(g_fixture.receiver, kReceiverTableDisplacement) =
      reinterpret_cast<Word>(g_fixture.receiver_table.slots);
}

// A second table, identical in shape, parked at the receiver's +0x04 and holding
// traps where the real one holds the observer -- plus a decoy function pointer at
// the receiver's own +0x90, which is what a body that skipped the first level of
// the dispatch would call.
void arm_receiver_decoy_table() {
  std::memset(g_fixture.decoy_table.slots, 0, sizeof(g_fixture.decoy_table.slots));
  for (int index = 0; index < 40; ++index) {
    g_fixture.decoy_table.slots[index] = reinterpret_cast<std::uint32_t>(&resolve_slot_trap);
  }
  *word_at(g_fixture.receiver, kReceiverTableDisplacement + 4) =
      reinterpret_cast<Word>(g_fixture.decoy_table.slots);
  *word_at(g_fixture.receiver, kResolveSlotDisplacement) =
      reinterpret_cast<Word>(&resolve_slot_trap);
}

// The handle's table: the real acquire at index 1, traps at 0 and 2, a decoy table
// one level off at the handle's +0x04, and a decoy function pointer at the
// handle's own +0x04.
void arm_handle_table() {
  std::memset(g_fixture.handle_table.slots, 0, sizeof(g_fixture.handle_table.slots));
  g_fixture.handle_table.slots[kAcquireSlotIndex - 1] =
      reinterpret_cast<std::uint32_t>(&acquire_slot_trap);
  g_fixture.handle_table.slots[kAcquireSlotIndex] =
      reinterpret_cast<std::uint32_t>(&acquire_slot_04_observer);
  g_fixture.handle_table.slots[kAcquireSlotIndex + 1] =
      reinterpret_cast<std::uint32_t>(&acquire_slot_trap);
  *word_at(g_fixture.handle, kReceiverTableDisplacement) =
      reinterpret_cast<Word>(g_fixture.handle_table.slots);
  std::memset(g_fixture.decoy_table.slots, 0, sizeof(g_fixture.decoy_table.slots));
  for (int index = 0; index < 40; ++index) {
    g_fixture.decoy_table.slots[index] = reinterpret_cast<std::uint32_t>(&acquire_slot_trap);
  }
  *word_at(g_fixture.handle, kReceiverTableDisplacement + 4) =
      reinterpret_cast<Word>(g_fixture.decoy_table.slots);
  *word_at(g_fixture.handle, kAcquireSlotDisplacement) =
      reinterpret_cast<Word>(&acquire_slot_trap);
}

std::string joined_log() {
  std::string text;
  for (const std::string& entry : g_log) {
    if (!text.empty()) {
      text += " | ";
    }
    text += entry;
  }
  return text;
}

void expect_log(const char* label, const std::vector<std::string>& expected) {
  if (g_log == expected) {
    return;
  }
  ++g_failures;
  std::printf("FAIL %s: the transfer sequence is wrong\n  want: ", label);
  for (std::size_t i = 0; i < expected.size(); ++i) {
    std::printf("%s%s", i ? " | " : "", expected[i].c_str());
  }
  std::printf("\n  got:  %s\n", joined_log().c_str());
}

void expect_no_trap(const char* label) {
  for (const std::string& entry : g_log) {
    CHECK(entry.compare(0, 5, "TRAP") != 0, "%s: a decoy slot was dispatched -- %s", label,
          entry.c_str());
  }
}

void expect_no_acquire(const char* label) {
  for (const std::string& entry : g_log) {
    CHECK(entry.compare(0, 9, "acquire04") != 0, "%s: the acquire ran unexpectedly", label);
  }
}

// =============================================================== the cases ===

// A. The cached fast path. Nonzero at the receiver's +0x3c returns that word and
// reaches NOTHING else -- no dispatch, no callee, no frame store.
void case_cached_word_is_returned_verbatim() {
  const Word values[4] = {0x00000001u, 0x00000100u, 0x12345678u, 0xffffffffu};
  for (Word value : values) {
    configure();
    arm_receiver_table();
    *word_at(g_fixture.receiver, kReceiverCachedWordDisplacement) = value;
    // Decoys either side of the real displacement, both nonzero: a body that read
    // +0x38 or +0x40 would return one of these instead.
    *word_at(g_fixture.receiver, kReceiverCachedWordDisplacement - 4) = 0xdeadbeefu;
    *word_at(g_fixture.receiver, kReceiverCachedWordDisplacement + 4) = 0xfeedfaceu;
    void* result = the_body()(receiver());
    CHECK_EQ_U(reinterpret_cast<Word>(result), value,
               "A: the cached word is the return value, unchanged");
    expect_log("A: the cached path calls nothing at all", {});
  }
  // The mirror image: the real word zero with its neighbours nonzero must NOT take
  // the fast path, because the body tests its own displacement and no other.
  configure();
  arm_receiver_table();
  arm_handle_table();
  *word_at(g_fixture.receiver, kReceiverCachedWordDisplacement - 4) = 0xdeadbeefu;
  *word_at(g_fixture.receiver, kReceiverCachedWordDisplacement + 4) = 0xfeedfaceu;
  g_plan.resolve_out_value = g_fixture.handle;
  (void)the_body()(receiver());
  CHECK(!g_log.empty() && g_log[0].compare(0, 9, "resolve90") == 0,
        "A2: a zero at +0x3c with nonzero neighbours does not take the fast path");
}

// B. The whole chain, and every argument the listing fixes.
void case_full_chain() {
  configure();
  arm_receiver_table();
  arm_receiver_decoy_table();
  arm_handle_table();
  g_plan.resolve_writes_first = 0xaaaa1111u;
  g_plan.resolve_writes_second = 0xbbbb2222u;
  g_plan.receiver_argument = 0x0badf00du;
  g_plan.resolve_out_value = g_fixture.handle;
  *word_at(g_fixture.receiver, kReceiverArgumentDisplacement) = g_plan.receiver_argument;

  void* result = the_body()(receiver());
  CHECK_EQ_U(reinterpret_cast<Word>(result), reinterpret_cast<Word>(g_fixture.handle),
             "B: the resolved handle is the return value");

  std::vector<std::string> want;
  char text[192];
  std::snprintf(text, sizeof text, "resolve90(pair=%08x,%08x)", 0xffffffffu, 0xffffffffu);
  want.emplace_back(text);  // the object is seeded with 0xffffffff in BOTH words
  want.emplace_back("global0067cb30()");
  std::snprintf(text, sizeof text, "key00613860(self=%p,arg=%08x)",
                static_cast<void*>(the_service()), 0x0badf00du);
  want.emplace_back(text);
  std::snprintf(text, sizeof text,
                "resolve4(self=%p,first=%08x,second=%08x,out=%p,fourth=%08x)",
                static_cast<void*>(the_service()), 0xaaaa1111u, 0xbbbb2222u, g_resolve_out, 0u);
  want.emplace_back(text);
  std::snprintf(text, sizeof text, "acquire04(self=%p)", static_cast<void*>(g_fixture.handle));
  want.emplace_back(text);
  expect_log("B: the whole chain, in order", want);
  expect_no_trap("B");

  CHECK(g_key_present_receiver == the_service(),
        "B: 0x00613860's receiver is the service from the root's +0x5c, not the receiver");
  CHECK_EQ_U(g_key_present_argument, 0x0badf00du,
             "B: 0x00613860's argument is the receiver's +0x08 word");
  CHECK(g_resolve_receiver == the_service(), "B: 0x00612f50's receiver is the service");
  CHECK_EQ_U(g_resolve_first, 0xaaaa1111u,
             "B: 0x00612f50's FIRST argument is the frame object's first word");
  CHECK_EQ_U(g_resolve_second, 0xbbbb2222u,
             "B: 0x00612f50's SECOND argument is the frame object's second word");
  CHECK_EQ_U(g_resolve_fourth, 0u, "B: 0x00612f50's fourth argument is the literal 0");
  CHECK(g_resolve_out != nullptr, "B: 0x00612f50's third argument is a pointer to a word");
  CHECK(g_resolve_out_at_call == nullptr,
        "B: the body zeroes the out slot itself (0x00642030) before the call -- an "
        "uninitialised or seed-marked slot would be non-null here");
  CHECK_EQ_U(g_global_getter_calls, 1, "B: the global getter is reached exactly once");
  CHECK_EQ_U(g_key_present_calls, 1, "B: 0x00613860 is reached exactly once");
  CHECK_EQ_U(g_resolve_calls, 1, "B: 0x00612f50 is reached exactly once");
}

// C. The dispatch's byte and 0x00613860's byte are tested for NON-ZERO, not
// against 1, and a false byte stops the chain where the listing says it stops.
void case_byte_tests_are_not_equality() {
  configure();
  arm_receiver_table();
  arm_handle_table();
  g_plan.resolve_return = 0x80u;
  g_plan.resolve_out_value = g_fixture.handle;
  void* result = the_body()(receiver());
  CHECK_EQ_U(reinterpret_cast<Word>(result), reinterpret_cast<Word>(g_fixture.handle),
             "C1: a dispatch byte of 0x80 is TRUE to this body");
  CHECK_EQ_U(g_resolve_calls, 1, "C1: 0x80 on the dispatch does not stop the chain");

  configure();
  arm_receiver_table();
  g_plan.resolve_return = 0u;
  (void)the_body()(receiver());
  expect_log("C2: a zero dispatch byte returns null immediately",
             {std::string("resolve90(pair=ffffffff,ffffffff)")});
  CHECK_EQ_U(g_global_getter_calls, 0, "C2: the global getter is not reached");
  CHECK_EQ_U(g_key_present_calls, 0, "C2: 0x00613860 is not reached");
  CHECK_EQ_U(g_resolve_calls, 0, "C2: 0x00612f50 is not reached");

  configure();
  arm_receiver_table();
  arm_handle_table();
  g_plan.key_present_return = 0x80u;
  g_plan.resolve_out_value = g_fixture.handle;
  (void)the_body()(receiver());
  CHECK_EQ_U(g_resolve_calls, 1, "C3: 0x80 from 0x00613860 is TRUE to this body");
}

// D. The +0x5c read is on the object the global getter returned. The receiver
// carries a decoy service word at its own +0x5c, so a reconstruction reading the
// wrong base would carry on into 0x00613860.
void case_service_word_is_on_the_global() {
  configure();
  arm_receiver_table();
  *word_at(g_fixture.root, kServiceRootServiceDisplacement) = 0u;
  (void)the_body()(receiver());
  expect_log("D: a null service word on the global stops the chain",
             {std::string("resolve90(pair=ffffffff,ffffffff)"), std::string("global0067cb30()")});
  CHECK_EQ_U(g_key_present_calls, 0, "D: the decoy service on the receiver is never used");
  CHECK_EQ_U(g_resolve_calls, 0, "D: the chain stops at the null service word");
}

// E. The argument to 0x00613860 is the receiver's +0x08, and the decoys planted at
// +0x04 and +0x0c are not.
void case_key_argument_displacement() {
  configure();
  arm_receiver_table();
  arm_handle_table();
  g_plan.resolve_out_value = g_fixture.handle;
  g_plan.receiver_argument = 0x00c0ffeeu;
  *word_at(g_fixture.receiver, kReceiverArgumentDisplacement) = 0x00c0ffeeu;
  *word_at(g_fixture.receiver, kReceiverArgumentDisplacement - 4) = 0x11111111u;
  *word_at(g_fixture.receiver, kReceiverArgumentDisplacement + 4) = 0x22222222u;
  (void)the_body()(receiver());
  CHECK_EQ_U(g_key_present_argument, 0x00c0ffeeu,
             "E: the argument is the receiver's +0x08, not a neighbouring word");
}

// F. The widest call's argument order. A body that passed the second word first,
// or that passed the sentinel rather than what the dispatch wrote, is refuted.
void case_wide_call_argument_order() {
  configure();
  arm_receiver_table();
  arm_handle_table();
  g_plan.resolve_writes_first = 0x11110000u;
  g_plan.resolve_writes_second = 0x22220000u;
  g_plan.resolve_out_value = g_fixture.handle;
  (void)the_body()(receiver());
  CHECK_EQ_U(g_resolve_first, 0x11110000u, "F: first argument, order not swapped");
  CHECK_EQ_U(g_resolve_second, 0x22220000u, "F: second argument, order not swapped");
  CHECK(g_resolve_first != g_resolve_second,
        "F: the two arguments differ here, so a swap is actually observable");
  // A dispatch that writes NEITHER word leaves the sentinel in both, and the
  // re-read must then pass the sentinel: the body keeps no copy in a register
  // across the call.
  configure();
  arm_receiver_table();
  arm_handle_table();
  g_plan.resolve_writes_first = 0xffffffffu;
  g_plan.resolve_writes_second = 0xffffffffu;
  g_plan.resolve_out_value = g_fixture.handle;
  (void)the_body()(receiver());
  CHECK_EQ_U(g_resolve_first, 0xffffffffu, "F2: an untouched first word stays 0xffffffff");
  CHECK_EQ_U(g_resolve_second, 0xffffffffu, "F2: an untouched second word stays 0xffffffff");
}

// G. The acquire runs on the FAILURE arm too. 0x00612f50 returns zero but leaves
// a real handle behind: the listing still takes the reference and returns null.
void case_acquire_runs_on_the_failing_arm() {
  configure();
  arm_receiver_table();
  arm_handle_table();
  g_plan.resolve_out_return = 0u;
  g_plan.resolve_out_value = g_fixture.handle;
  void* result = the_body()(receiver());
  CHECK_EQ_U(reinterpret_cast<Word>(result), 0u,
             "G: a zero from 0x00612f50 returns null even though it left a handle");
  bool acquired = false;
  for (const std::string& entry : g_log) {
    acquired = acquired || entry.compare(0, 9, "acquire04") == 0;
  }
  CHECK(acquired, "G: the acquire still runs on the arm that returns null (0x0064205e)");
}

// H. The other direction: a nonzero from 0x00612f50 with a NULL out word. No
// acquire, and the result is null -- not the callee's byte, not 1.
void case_true_arm_with_null_handle() {
  configure();
  arm_receiver_table();
  arm_handle_table();
  g_plan.resolve_out_return = 1u;
  g_plan.resolve_out_value = nullptr;
  void* result = the_body()(receiver());
  CHECK_EQ_U(reinterpret_cast<Word>(result), 0u,
             "H: the returned word is the out slot, so a null slot returns null even "
             "when the callee said TRUE");
  expect_no_acquire("H");
  CHECK_EQ_U(g_resolve_calls, 1, "H: 0x00612f50 was reached");
}

// I. Both two-level dispatches, at the depth and the slot the listing fixes.
void case_dispatch_depth_and_slot() {
  configure();
  arm_receiver_table();
  arm_receiver_decoy_table();
  arm_handle_table();
  g_plan.resolve_out_value = g_fixture.handle;
  (void)the_body()(receiver());
  expect_no_trap("I");
  bool saw_resolve = false;
  bool saw_acquire = false;
  for (const std::string& entry : g_log) {
    saw_resolve = saw_resolve || entry.compare(0, 9, "resolve90") == 0;
    saw_acquire = saw_acquire || entry.compare(0, 9, "acquire04") == 0;
  }
  CHECK(saw_resolve, "I: the slot at 0x90 of the receiver's OWN table was dispatched");
  CHECK(saw_acquire, "I: the slot at 0x04 of the HANDLE'S own table was dispatched");
}

// J. Nothing is written to the receiver. Byte-comparing the whole 0x40-byte run
// the body reaches is the only way to keep "this body caches nothing" falsifiable
// rather than assumed.
void case_receiver_is_not_written() {
  configure();
  arm_receiver_table();
  arm_handle_table();
  g_plan.resolve_out_value = g_fixture.handle;
  std::uint8_t before[0x40];
  std::memcpy(before, g_fixture.receiver, sizeof before);
  for (int call = 0; call < 3; ++call) {
    (void)the_body()(receiver());
  }
  CHECK(std::memcmp(before, g_fixture.receiver, sizeof before) == 0,
        "J: three calls left every byte of the receiver's 0x40-byte run unchanged");
  configure();
  arm_receiver_table();
  *word_at(g_fixture.receiver, kReceiverCachedWordDisplacement) = 0x5a5a5a5au;
  std::memcpy(before, g_fixture.receiver, sizeof before);
  (void)the_body()(receiver());
  CHECK(std::memcmp(before, g_fixture.receiver, sizeof before) == 0,
        "J2: the cached path writes nothing either");
}

// K. Nothing carries between calls. Two calls in a row with the dispatch writing
// different words each time: a reconstruction that kept the 8-byte object alive
// across calls hands the second call the first call's values.
void case_no_state_carries_between_calls() {
  configure();
  arm_receiver_table();
  arm_handle_table();
  g_plan.resolve_out_value = g_fixture.handle;

  g_plan.resolve_writes_first = 0x0a0a0a0au;
  g_plan.resolve_writes_second = 0x0b0b0b0bu;
  (void)the_body()(receiver());
  CHECK_EQ_U(g_resolve_first, 0x0a0a0a0au, "K: the first call's first word");
  CHECK_EQ_U(g_resolve_second, 0x0b0b0b0bu, "K: the first call's second word");
  CHECK_EQ_U(g_global_getter_calls, 1, "K: one global getter call after the first call");

  g_plan.resolve_writes_first = 0xffffffffu;
  g_plan.resolve_writes_second = 0xffffffffu;
  (void)the_body()(receiver());
  CHECK_EQ_U(g_resolve_first, 0xffffffffu,
             "K2: the second call re-seeds the object rather than reusing the first "
             "call's words");
  CHECK_EQ_U(g_resolve_second, 0xffffffffu, "K2: the second word, likewise");
  CHECK_EQ_U(g_global_getter_calls, 2, "K2: the chain runs again in full");
  CHECK_EQ_U(g_resolve_calls, 2, "K2: 0x00612f50 is reached once per call");
  CHECK_EQ_U(g_key_present_calls, 2, "K2: 0x00613860 is reached once per call");
  expect_no_trap("K");
}

}  // namespace

// ================= the three direct callees, in their own definitions =======
//
// They are written here, outside the anonymous namespace, because the
// reconstruction's translation unit reaches them through the package header's
// external declarations. Each one records what it was handed and returns a
// configured byte; the two dispatch tables are the test's own, not the header's.

void* PKG_SW1_00641FD0_CDECL service_root_global_0067cb30(void) {
  ++g_global_getter_calls;
  g_log.emplace_back("global0067cb30()");
  return g_fixture.root;
}

std::uint8_t PKG_SW1_00641FD0_THISCALL service_key_present_00613860(Service* receiver,
                                                                    Word argument) {
  ++g_key_present_calls;
  g_key_present_receiver = receiver;
  g_key_present_argument = argument;
  char text[128];
  std::snprintf(text, sizeof text, "key00613860(self=%p,arg=%08x)", static_cast<void*>(receiver),
                static_cast<unsigned>(argument));
  g_log.emplace_back(text);
  return g_plan.key_present_return;
}

std::uint8_t PKG_SW1_00641FD0_THISCALL service_handle_resolve_00612f50(Service* receiver,
                                                                       Word first, Word second,
                                                                       void** out, Word fourth) {
  ++g_resolve_calls;
  g_resolve_receiver = receiver;
  g_resolve_first = first;
  g_resolve_second = second;
  g_resolve_out = out;
  g_resolve_fourth = fourth;
  g_resolve_out_at_call = *out;
  char text[192];
  std::snprintf(text, sizeof text,
                "resolve4(self=%p,first=%08x,second=%08x,out=%p,fourth=%08x)",
                static_cast<void*>(receiver), static_cast<unsigned>(first),
                static_cast<unsigned>(second), static_cast<void*>(out),
                static_cast<unsigned>(fourth));
  g_log.emplace_back(text);
  *out = g_plan.resolve_out_value;
  return g_plan.resolve_out_return;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641fd0

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w1_00641fd0;  // NOLINT
  case_cached_word_is_returned_verbatim();
  case_full_chain();
  case_byte_tests_are_not_equality();
  case_service_word_is_on_the_global();
  case_key_argument_displacement();
  case_wide_call_argument_order();
  case_acquire_runs_on_the_failing_arm();
  case_true_arm_with_null_handle();
  case_dispatch_depth_and_slot();
  case_receiver_is_not_written();
  case_no_state_carries_between_calls();
  if (g_failures != 0) {
    std::printf("%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("all checks passed\n");
  return 0;
}
