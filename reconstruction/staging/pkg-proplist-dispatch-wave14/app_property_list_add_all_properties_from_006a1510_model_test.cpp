// PKG-PROLIST-DISPATCH-WAVE14 -- behavioural model test for VA 0x006a1510,
// App::PropertyList::AddAllPropertiesFrom.
// SPORE/SporeBin/SporeApp.exe, 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// Every claim this test makes comes from the 19-instruction body, and every
// check below names the instruction it comes from. The whole body is:
//
//   0x006a1510  PUSH ESI
//   0x006a1511  PUSH EDI
//   0x006a1512  MOV EDI,dword ptr [ESP + 0xc]
//   0x006a1516  MOV EAX,dword ptr [EDI + 0x30]
//   0x006a1519  MOV ESI,ECX
//   0x006a151b  TEST EAX,EAX
//   0x006a151d  JZ 0x006a1527
//   0x006a151f  MOV EDX,dword ptr [ESI]
//   0x006a1521  PUSH EAX
//   0x006a1522  MOV EAX,dword ptr [EDX + 0x38]
//   0x006a1525  CALL EAX
//   0x006a1527  MOV EDX,dword ptr [ESI]
//   0x006a1529  MOV EAX,dword ptr [EDX + 0x30]
//   0x006a152c  PUSH EDI
//   0x006a152d  MOV ECX,ESI
//   0x006a152f  CALL EAX
//   0x006a1531  POP EDI
//   0x006a1532  POP ESI
//   0x006a1533  RET 0x4
//
// The two dispatch targets are NOT known. No record in this repository names
// what the table words at displacement 0x38 and 0x30 hold, and the xref export
// carries no outgoing call edge, because both transfers are register-indirect.
// So the test supplies its own receiver, its own two table images and its own
// stubs, and asserts only what THIS BODY does with them: which slots it
// dispatches through, in what order, with which receiver and which stack word,
// and what it leaves in EAX. The stubs belong to the test, not to the game: a
// stub that does something no real target would do is still a legal thing for
// the test to do, because what is under examination is the caller's use of the
// callee's calling surface, not the callee's behaviour.
//
// What this test deliberately does NOT assert, because the evidence does not
// fix it (see reconstruction/metadata/pkg-proplist-dispatch-wave14/006a1510.json
// :: unresolved_questions, all six of which remain open):
//
//   * what either slot holds, or what either slot does internally;
//   * what the word read at 0x006a1516 MEANS. The listing reads it once out of
//     the ARGUMENT object, tests it for null, and passes it on. This test calls
//     it a word and nothing more. The decompiler's name for it, mpParent, is
//     one decompiler's guess over a read that mixes the receiver and the
//     argument, and is not adopted;
//   * whether the two slot callees really pop the stack word they are handed.
//     That is an INFERENCE from a frame balanced with no ADD ESP after either
//     CALL, and the stubs here pop it only because the reconstruction's slot
//     types declare they do. If a slot target turns out to be cdecl, these two
//     types change and nothing else in the body does;
//   * whether the return type is void or an unclassified 32-bit word. The
//     machine-derived ABI record classes the EAX word as aggregate_unknown with
//     type null; Ghidra types the same function void. The header reports both
//     records and calls the disagreement an open question. This test does not
//     settle it. It only checks that the word the body hands back is bit-for-bit
//     the word the second transfer produced, which is the one statement that
//     holds under either typing of the function.
//
// Two more limits worth stating plainly:
//
//   * The receiver record is bounds_only and enumerates displacement 0 and
//     nothing else. That is an observation of where the body was seen reaching,
//     not an enumeration of the object, so this test builds fake objects whose
//     layout is a choice of the test and pins that choice with static_assert and
//     with a run-time displacement check. Nothing here claims the real
//     receiver's layout, which no record in this repository gives.
//   * A store that wrote back the value it had just read would leave the bytes
//     identical and so pass the "nothing is written" check below. That store is
//     not observable through this interface and is not claimed to be excluded;
//     every store that changes a byte is excluded.

#include "app_property_list_add_all_properties_from_006a1510.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

// The stubs below are free functions carrying an x86-32 thiscall convention
// (receiver in ECX, one popped stack word), which is a non-class use of the
// attribute. GCC warns about exactly that; the warning is suppressed rather
// than the convention weakened. Same guard as
// all_copy_from_properties_006a14d0_model_test.cpp.
#if !defined(_MSC_VER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#define PKG_TEST_THISCALL __attribute__((thiscall))
#else
#define PKG_TEST_THISCALL __thiscall
#endif

namespace openspore::reconstruction::pkg_proplist_dispatch_wave14 {

namespace {

// Machine displacements, never names. 0x0 is the only receiver word this body
// reads (0x006a151f and 0x006a1527, both MOV EDX,dword ptr [ESI]); 0x38 and 0x30
// are the two slot displacements (0x006a1522 and 0x006a1529); 0x30 is also the
// displacement of the one word this body reads out of its stack argument
// (0x006a1516, on the register holding that argument since 0x006a1512).
constexpr std::size_t kTableWordDisplacement = 0x00u;
constexpr std::size_t kSlot30Displacement = 0x30u;
constexpr std::size_t kSlot38Displacement = 0x38u;
constexpr std::size_t kArgumentWordDisplacement = 0x30u;

// A word that cannot be an address of anything in this test, so "the pushed word
// is the data word and not the slot address" is decidable.
constexpr TargetWord kSampleWord = 0xc0ffee01u;

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// Builds a message for a check that runs inside a loop, so the failing case can
// be named. check() stays the two-argument printer the other model tests use.
const char *label(const char *what, const char *which) {
  static char buffer[224];
  std::snprintf(buffer, sizeof buffer, "%s [%s]", what, which);
  return buffer;
}

// ---------------------------------------------------------------------------
// The fake objects. Their layout is pinned twice: by static_assert at compile
// time and by check() at run time, so a change to either struct that moved a
// word off its machine displacement fails loudly instead of quietly testing
// the wrong thing.
// ---------------------------------------------------------------------------

// The receiver. 0x006a151f and 0x006a1527 read exactly one word out of it, the
// table word at displacement 0, so one field is all the body can reach. The
// tail exists so the "nothing is written" check has bytes beyond the table word
// to compare.
struct alignas(4) FakeReceiver {
  void *table;                    // displacement 0x0
  unsigned char tail[0x3c] = {};  // never reached by the body
};
static_assert(offsetof(FakeReceiver, table) == kTableWordDisplacement,
              "the receiver's table word must sit at displacement 0x0");
static_assert(sizeof(FakeReceiver) > kArgumentWordDisplacement,
              "the receiver must be a whole object to byte-compare");

// A table image. Both slots the body reads are placed at their own machine
// displacements and the gaps are left as padding, so a slot word the body reads
// at the wrong displacement lands on a zero word rather than accidentally on
// the other stub.
struct alignas(4) FakeTable {
  unsigned char head[0x30] = {};  // displacement 0x0 .. 0x2f, not read
  SlotAt30 slot_30;               // 0x006a1529  MOV EAX,[EDX + 0x30]
  unsigned char gap[0x04] = {};   // displacement 0x34 .. 0x37, not read
  SlotAt38 slot_38;               // 0x006a1522  MOV EAX,[EDX + 0x38]
};
static_assert(offsetof(FakeTable, slot_30) == kSlot30Displacement,
              "the 0x30 slot must sit at displacement 0x30 of the table");
static_assert(offsetof(FakeTable, slot_38) == kSlot38Displacement,
              "the 0x38 slot must sit at displacement 0x38 of the table");

// The stack argument. The body reads exactly one word out of it, at
// displacement 0x30, and passes that same word on as the 0x38 transfer's stack
// argument.
struct alignas(4) FakeArgument {
  unsigned char head[0x30] = {};  // displacement 0x0 .. 0x2f, not read
  TargetWord word_30;             // 0x006a1516  MOV EAX,[EDI + 0x30]
};
static_assert(offsetof(FakeArgument, word_30) == kArgumentWordDisplacement,
              "the argument's word must sit at displacement 0x30");

// ---------------------------------------------------------------------------
// The observation. One entry per observed dispatch, recorded in call order.
// ---------------------------------------------------------------------------

struct Event {
  enum Kind {
    kSlot38,   // the 0x38 transfer, whichever table image supplied the target
    kSlot30A,  // the 0x30 entry of table image A
    kSlot30B   // the 0x30 entry of table image B
  };
  Kind kind;
  OpaquePropertyList *receiver;   // what the callee received in ECX
  TargetWord word;                 // the word pushed at 0x006a1521
  OpaquePropertyList *stack_arg;   // the word pushed at 0x006a152c
  int generation;                  // table rebindings that had happened
};

constexpr int kEventCapacity = 4;
Event g_events[kEventCapacity];
int g_event_count = 0;
int g_generation = 0;

// Table image A is the one live on entry. Table image B is the one a 0x38
// target may rebind the receiver onto, and its 0x30 entry is a DIFFERENT stub
// so that the re-read at 0x006a1527 is observable.
FakeTable g_table_a;
FakeTable g_table_b;

TargetWord g_slot38_result = 0u;
TargetWord g_slot30_result = 0u;
bool g_slot38_rebinds_table = false;

const char *kind_name(Event::Kind kind) {
  switch (kind) {
    case Event::kSlot38:
      return "0x38";
    case Event::kSlot30A:
      return "0x30(table-a)";
    case Event::kSlot30B:
      return "0x30(table-b)";
  }
  return "?";
}

void record(Event::Kind kind, OpaquePropertyList *receiver, TargetWord word,
            OpaquePropertyList *stack_arg) {
  if (g_event_count >= kEventCapacity) {
    return;
  }
  Event &event = g_events[g_event_count++];
  event.kind = kind;
  event.receiver = receiver;
  event.word = word;
  event.stack_arg = stack_arg;
  event.generation = g_generation;
}

// The whole event log as one string, for the failure message of an ordering
// check. An ordering claim is only as good as the log it was read out of.
const char *describe_log() {
  static char buffer[224];
  const int shown = g_event_count < kEventCapacity ? g_event_count : kEventCapacity;
  std::snprintf(buffer, sizeof buffer, "event log: count=%d [", g_event_count);
  std::size_t used = std::strlen(buffer);
  for (int index = 0; index < shown; ++index) {
    const std::size_t room = sizeof buffer - used;
    std::snprintf(buffer + used, room, "%s%s", index == 0 ? "" : ", ",
                  kind_name(g_events[index].kind));
    used += std::strlen(buffer + used);
  }
  std::snprintf(buffer + used, sizeof buffer - used, "]");
  return buffer;
}

// ---------------------------------------------------------------------------
// The stubs. Signatures are spelled exactly as the header's two slot types
// spell them, so no cast is involved and a mismatch would be a compile error.
// ---------------------------------------------------------------------------

// 0x006a1525  CALL EAX -- the 0x38 target. Receiver in ECX (0x006a1519 wrote
// ESI from ECX and nothing rewrote ECX on this path) and the word pushed at
// 0x006a1521 as its single stack word. Optionally rebinds the receiver's table
// word, which is what makes the re-read at 0x006a1527 observable.
extern "C" TargetWord PKG_TEST_THISCALL slot38_stub(OpaquePropertyList *self,
                                                    TargetWord word) {
  record(Event::kSlot38, self, word, nullptr);
  if (g_slot38_rebinds_table) {
    reinterpret_cast<FakeReceiver *>(self)->table = &g_table_b;
    ++g_generation;
  }
  return g_slot38_result;
}

// 0x006a152f  CALL EAX -- the 0x30 target of table image A. Receiver in ECX by
// way of 0x006a152d MOV ECX,ESI, and the word pushed at 0x006a152c, which is
// `other` itself because 0x006a1512 put it in EDI.
extern "C" TargetWord PKG_TEST_THISCALL slot30_stub_a(OpaquePropertyList *self,
                                                      OpaquePropertyList *other) {
  record(Event::kSlot30A, self, 0u, other);
  return g_slot30_result;
}

// The same slot of the second table image. Reaching this stub is the proof that
// the body re-read the table word rather than carrying the first one.
extern "C" TargetWord PKG_TEST_THISCALL slot30_stub_b(OpaquePropertyList *self,
                                                      OpaquePropertyList *other) {
  record(Event::kSlot30B, self, 0u, other);
  return g_slot30_result;
}

// ---------------------------------------------------------------------------
// Fixtures.
// ---------------------------------------------------------------------------

void init_tables() {
  g_table_a.slot_30 = &slot30_stub_a;
  g_table_a.slot_38 = &slot38_stub;
  g_table_b.slot_30 = &slot30_stub_b;
  g_table_b.slot_38 = &slot38_stub;
}

void reset_observation() {
  for (Event &event : g_events) {
    event.kind = Event::kSlot38;
    event.receiver = nullptr;
    event.word = 0u;
    event.stack_arg = nullptr;
    event.generation = 0;
  }
  g_event_count = 0;
  g_generation = 0;
  g_slot38_result = 0u;
  g_slot30_result = 0u;
  g_slot38_rebinds_table = false;
}

// A non-zero pattern past the table word, so a stray write anywhere in the
// receiver shows up in the byte comparison instead of writing a zero over a
// zero.
void make_receiver(FakeReceiver *receiver, FakeTable *table) {
  std::memset(receiver->tail, 0xa5, sizeof receiver->tail);
  receiver->table = table;
}

void make_argument(FakeArgument *argument, TargetWord word) {
  std::memset(argument->head, 0x5a, sizeof argument->head);
  argument->word_30 = word;
}

unclassified_in_EAX call_body(FakeReceiver *receiver, FakeArgument *other) {
  return app_property_list_add_all_properties_from_006a1510(
      reinterpret_cast<OpaquePropertyList *>(receiver),
      reinterpret_cast<OpaquePropertyList *>(other));
}

// ---------------------------------------------------------------------------
// The checks.
// ---------------------------------------------------------------------------

// 0x006a151f / 0x006a1527, 0x006a1522 / 0x006a1529, 0x006a1516. The
// displacements this test relies on, restated at run time so a struct that
// drifted cannot make the behavioural checks below pass for the wrong reason.
void test_the_displacements_are_the_ones_the_listing_shows() {
  check(offsetof(FakeReceiver, table) == kTableWordDisplacement,
        "the receiver's table word is at displacement 0x0 (0x006a151f, 0x006a1527)");
  check(offsetof(FakeTable, slot_30) == kSlot30Displacement,
        "the second slot is at displacement 0x30 of the table (0x006a1529)");
  check(offsetof(FakeTable, slot_38) == kSlot38Displacement,
        "the first slot is at displacement 0x38 of the table (0x006a1522)");
  check(offsetof(FakeArgument, word_30) == kArgumentWordDisplacement,
        "the argument's word is at displacement 0x30 (0x006a1516)");
  check(sizeof(TargetWord) == 4, "a TargetWord is the four bytes the listing moves");
  check(sizeof(void *) == 4, "a table and a slot word are pointers on this target");
}

// 0x006a151b TEST EAX,EAX / 0x006a151d JZ 0x006a1527. A zero word takes the
// branch, and the target of that branch is the second block's own table load,
// so the second transfer still runs and the first one does not run at all.
void test_a_zero_word_skips_only_the_38_slot() {
  FakeArgument argument;
  FakeReceiver receiver;
  make_argument(&argument, 0u);
  make_receiver(&receiver, &g_table_a);
  reset_observation();
  g_slot30_result = 0x00c0ffeeu;

  const unclassified_in_EAX got = call_body(&receiver, &argument);

  check(g_event_count == 1,
        label("a zero word dispatches exactly once", describe_log()));
  if (g_event_count == 1) {
    check(g_events[0].kind == Event::kSlot30A,
          "0x006a151d JZ skips the whole first block, so no 0x38 transfer runs");
  }
  check(got == 0x00c0ffeeu,
        "the second transfer still runs on the zero-word path and is the result");
}

// 0x006a1525 then 0x006a152f. A non-zero word falls through the branch, and
// the two transfers happen in the order the listing gives them.
void test_a_non_zero_word_runs_both_slots_in_order() {
  FakeArgument argument;
  FakeReceiver receiver;
  make_argument(&argument, kSampleWord);
  make_receiver(&receiver, &g_table_a);
  reset_observation();

  call_body(&receiver, &argument);

  check(g_event_count == 2,
        label("a non-zero word dispatches exactly twice", describe_log()));
  if (g_event_count == 2) {
    check(g_events[0].kind == Event::kSlot38,
          "0x006a1525 CALL EAX dispatches the 0x38 slot first");
    check(g_events[1].kind == Event::kSlot30A,
          "0x006a152f CALL EAX dispatches the 0x30 slot second");
  }
}

// 0x006a1512 / 0x006a1516 / 0x006a1521 and 0x006a1510 / 0x006a1519 / 0x006a1525.
// The single stack word of the first transfer is the word read out of the
// argument, pushed before the slot word is loaded, and its receiver is this
// function's own receiver because ECX is never rewritten on that path.
void test_the_38_slot_gets_the_argument_word_and_this_receiver() {
  FakeArgument argument;
  FakeReceiver receiver;
  make_argument(&argument, kSampleWord);
  make_receiver(&receiver, &g_table_a);
  reset_observation();

  call_body(&receiver, &argument);

  const TargetWord slot_address = static_cast<TargetWord>(
      reinterpret_cast<std::uintptr_t>(&g_table_a.slot_38));

  check(kSampleWord != slot_address,
        "the planted word is distinguishable from the slot's address");
  if (g_event_count == 2) {
    check(g_events[0].word == kSampleWord,
          "0x006a1521 PUSH EAX pushes the word read at 0x006a1516");
    check(g_events[0].word != slot_address,
          "the 0x38 transfer does not receive the slot address as its argument");
    check(g_events[0].receiver ==
              reinterpret_cast<OpaquePropertyList *>(&receiver),
          "0x006a1525 dispatches on this function's own receiver, not the table");
    check(g_events[0].receiver !=
              reinterpret_cast<OpaquePropertyList *>(&g_table_a),
          "the 0x38 transfer's receiver is not the table image");
  }
}

// 0x006a152c PUSH EDI / 0x006a152d MOV ECX,ESI. The second transfer is
// dispatched on the same receiver, with `other` itself as its stack word --
// EDI holds the stack argument because 0x006a1512 read it there.
void test_the_30_slot_gets_the_receiver_and_other() {
  FakeArgument argument;
  FakeReceiver receiver;
  make_argument(&argument, kSampleWord);
  make_receiver(&receiver, &g_table_a);
  reset_observation();

  call_body(&receiver, &argument);

  if (g_event_count == 2) {
    check(g_events[1].receiver ==
              reinterpret_cast<OpaquePropertyList *>(&receiver),
          "0x006a152d MOV ECX,ESI hands the 0x30 slot this function's receiver");
    check(g_events[1].stack_arg ==
              reinterpret_cast<OpaquePropertyList *>(&argument),
          "0x006a152c PUSH EDI hands the 0x30 slot the stack argument itself");
  }
}

// 0x006a1527 MOV EDX,[ESI]. The table word is read AGAIN after the first
// dispatch, on both paths. The 0x38 target here rebinds the receiver's table
// word, so the second transfer can only reach table image B's entry if the body
// re-read the word rather than carrying the first one in a register.
void test_the_table_word_is_re_read_before_the_30_slot() {
  FakeArgument argument;
  FakeReceiver receiver;
  make_argument(&argument, kSampleWord);
  make_receiver(&receiver, &g_table_a);
  reset_observation();
  g_slot38_rebinds_table = true;
  g_slot30_result = 0x0badc0deu;

  const unclassified_in_EAX got = call_body(&receiver, &argument);

  check(g_event_count == 2,
        label("the rebinding case still dispatches twice", describe_log()));
  if (g_event_count == 2) {
    check(g_events[0].kind == Event::kSlot38,
          "the first transfer is bound from the table live on entry");
    check(g_events[0].generation == 0,
          "the first transfer is dispatched before anything rebinds the table");
    check(g_events[1].kind == Event::kSlot30B,
          "0x006a1527 re-reads the table word, so the 0x30 transfer goes "
          "through the second table image");
    check(g_events[1].generation == 1,
          "the second transfer is dispatched after the table word changed");
  }
  check(got == 0x0badc0deu,
        "the re-read does not disturb the return: it is still the 0x30 word");
}

// 0x006a1529 / 0x006a152f. The return word is exactly the word the second
// transfer left in EAX -- the last write to EAX in the body, with no operation
// between it and RET 0x4. Swept across both paths and across the whole width.
void test_the_return_is_exactly_the_30_slot_word() {
  struct ReturnCase {
    TargetWord value;
    const char *text;
  };
  static const ReturnCase cases[] = {
      {0x00000000u, "0x00000000"}, {0x00000001u, "0x00000001"},
      {0x0000ffffu, "0x0000ffff"}, {0x7fffffffu, "0x7fffffff"},
      {0x80000000u, "0x80000000"}, {0xffffffffu, "0xffffffff"},
  };

  for (const ReturnCase &each : cases) {
    FakeArgument argument;
    FakeReceiver receiver;

    // Non-zero argument word: both transfers run.
    make_argument(&argument, kSampleWord);
    make_receiver(&receiver, &g_table_a);
    reset_observation();
    g_slot38_result = 0x11111111u;
    g_slot30_result = each.value;
    check(call_body(&receiver, &argument) == each.value,
          label("the body returns the 0x30 word unchanged, non-zero argument "
                "word",
                each.text));

    // Zero argument word: only the second transfer runs, and it is still the
    // word that comes back.
    make_argument(&argument, 0u);
    make_receiver(&receiver, &g_table_a);
    reset_observation();
    g_slot30_result = each.value;
    check(call_body(&receiver, &argument) == each.value,
          label("the body returns the 0x30 word unchanged, zero argument word",
                each.text));
  }
}

// 0x006a1525. The first transfer's result is dead: 0x006a1529 overwrites EAX
// before anything can observe it. A poison value here must not reach the
// caller.
void test_the_38_slot_result_is_dead() {
  static const TargetWord poisons[] = {0xffffffffu, 0xdeadbeefu, 0x00000001u};
  static const char *const texts[] = {"0xffffffff", "0xdeadbeef", "0x00000001"};

  for (int index = 0; index < 3; ++index) {
    FakeArgument argument;
    FakeReceiver receiver;
    make_argument(&argument, kSampleWord);
    make_receiver(&receiver, &g_table_a);
    reset_observation();
    g_slot38_result = poisons[index];
    g_slot30_result = 0x12345678u;

    const unclassified_in_EAX got = call_body(&receiver, &argument);

    check(got == 0x12345678u,
          label("whatever the 0x38 transfer returns, the body returns the "
                "0x30 word",
                texts[index]));
    check(got != poisons[index],
          label("the 0x38 transfer's poison value never reaches the caller",
                texts[index]));
  }
}

// The body reads four words and writes none: the argument's word at 0x30
// (0x006a1516) and the receiver's table word at 0x0 (0x006a151f, 0x006a1527)
// are the only memory it reaches, and the listing holds no store. So neither
// object may come back with a single byte changed. See the header of this file
// for the one store this cannot see: a write-back of the value just read.
void test_neither_the_receiver_nor_the_argument_is_written() {
  FakeArgument argument;
  FakeReceiver receiver;
  unsigned char receiver_before[sizeof(FakeReceiver)];
  unsigned char argument_before[sizeof(FakeArgument)];

  // The non-zero path, which is the one that dispatches twice.
  make_argument(&argument, kSampleWord);
  make_receiver(&receiver, &g_table_a);
  std::memcpy(receiver_before, &receiver, sizeof receiver_before);
  std::memcpy(argument_before, &argument, sizeof argument_before);
  reset_observation();
  call_body(&receiver, &argument);
  check(std::memcmp(receiver_before, &receiver, sizeof receiver_before) == 0,
        "no byte of the receiver is written on the non-zero-word path");
  check(std::memcmp(argument_before, &argument, sizeof argument_before) == 0,
        "no byte of the argument is written on the non-zero-word path");

  // And the zero path, which is the one that would tempt a store of zero.
  make_argument(&argument, 0u);
  make_receiver(&receiver, &g_table_a);
  std::memcpy(receiver_before, &receiver, sizeof receiver_before);
  std::memcpy(argument_before, &argument, sizeof argument_before);
  reset_observation();
  call_body(&receiver, &argument);
  check(std::memcmp(receiver_before, &receiver, sizeof receiver_before) == 0,
        "no byte of the receiver is written on the zero-word path");
  check(std::memcmp(argument_before, &argument, sizeof argument_before) == 0,
        "no byte of the argument is written on the zero-word path");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_proplist_dispatch_wave14

int main() {
  using namespace openspore::reconstruction::pkg_proplist_dispatch_wave14;
  init_tables();
  test_the_displacements_are_the_ones_the_listing_shows();
  test_a_zero_word_skips_only_the_38_slot();
  test_a_non_zero_word_runs_both_slots_in_order();
  test_the_38_slot_gets_the_argument_word_and_this_receiver();
  test_the_30_slot_gets_the_receiver_and_other();
  test_the_table_word_is_re_read_before_the_30_slot();
  test_the_return_is_exactly_the_30_slot_word();
  test_the_38_slot_result_is_dead();
  test_neither_the_receiver_nor_the_argument_is_written();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}

#if !defined(_MSC_VER)
#pragma GCC diagnostic pop
#endif

#undef PKG_TEST_THISCALL
