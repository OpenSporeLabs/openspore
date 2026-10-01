// PKG-SWARM-W2-00577310 -- VA 0x00577310
// Behavioural model test for FUN_00577310, the lazily-initialising editor setup
// at slot +0x48 of the code-pointer table at 0x013f57f8.
//
// The five direct callees and the three dispatch shapes are all defined here as
// observers, so the test sees every transfer the reconstruction makes, with which
// arguments, in which order, and gets to decide what each does to memory while
// it is there. That is the only way to test the orderings this body actually
// has: the acquire happens BEFORE the member is stored, the release AFTER it,
// the query's out-parameter is zeroed between the pushes and the call, and the
// fourth registration reuses the third record's frame slot.
//
// WHAT IS ASSERTED is what the 147-instruction listing fixes and nothing more:
//
//   * the cold-start guard is a NULL TEST ON THE RECEIVER'S +0x308 WORD and
//     nothing else, so a warm receiver performs no factory call, no constructor
//     call and none of the three registrations on that member;
//   * both factory calls get the SAME six words in the same order, with the
//     ADDRESS of the seven-byte string "Editor" (0x013eb430) as the second;
//   * a null from the factory does NOT return early: the member stays null, the
//     swap is skipped because null equals null, and THREE registrations are still
//     made, on a null receiver;
//   * the swap's order -- acquire at slot +0x0, THEN store, THEN release at slot
//     +0x4 -- observed at the moment of each transfer;
//   * a replacement equal to the member already stored causes no acquire, no
//     store and no release at all;
//   * three distinct 12-byte registration records on the +0x308 member, checked
//     BYTE at the address the callee receives, twelve bytes apart in order;
//   * the fourth registration goes to the +0x30c member and is written at the
//     THIRD record's frame address, so the addresses the callee receives are
//     compared and not merely the contents;
//   * the incoming argument is cleared in place and that very word is the
//     query's out-parameter;
//   * the query's argument order: subject = the ORIGINAL argument, weight = the
//     ADDRESS 0x0150cdd4, out = the already-cleared word;
//   * the lookup's argument order, and that the body tests the OUT WORD the
//     callee wrote rather than the callee's bool -- in BOTH directions, because
//     the two are driven to disagree;
//   * the tail release, reached from the false arm, the zero-instance arm and the
//     fall-out arm, and not reached from the sentinel arm;
//   * that the block at 0x00577406..0x00577413 is never entered;
//   * the ABI, MEASURED rather than asserted: ESP sampled before and after, equal
//     only if the frame balances;
//   * that exactly eight receiver bytes ever change, at 0x308 and 0x30c, checked
//     by byte-diffing a 0x320-byte probe pre-filled with a pattern.
//
// The cases marked REFUTE try to BREAK the reconstruction rather than walk it.
// Each names the wrong reconstruction it is aimed at:
//
//   A  a wrong receiver displacement, a dword store where the machine has none,
//      or a wrong id on the wrong registration;
//   B  the guard read as something other than "the +0x308 member is null", or the
//      cold block made unconditional, or the swap's equality test inverted;
//   C  a null from the factory treated as an allocation-failure early return;
//   D  the swap's order changed -- store before acquire, release before store,
//      release of the new member, or release of a member never replaced;
//   E  two records overlapping, a fourth record given storage of its own instead
//      of aliasing the third, or the wrong receiver on a registration;
//   F  the query's polarity at 0x0057742d;
//   G  the lookup's bool used instead of its out word, and the reverse;
//   H  a release through a null table because the answer word was not tested;
//   I  the dead block at 0x00577406 entered, i.e. a second release of the handle;
//   J  a one-level slot read, a slot read off the object rather than its table,
//      or a wrong slot displacement (nine decoy words sit in the same table);
//   K  the sentinel read as "non-zero" instead of "== 0xffffffff", driven with
//      0, 1, 0x80000000, 0xfffffffe and 0xffffffff;
//   L  a re-initialisation on every call instead of a one-shot cold block.
//
// What is NOT asserted, and why:
//
//   * EAX on return. The declared return type is void and the machine leaves
//     three different incidental words there depending on the path, so there is
//     nothing to say about it. (The two facts around it that DO matter are
//     asserted: the lookup's bool is discarded, and the out word is not.)
//   * WHICH register carries each intermediate. The bytes use EAX/EDX for the
//     first swap and EDX/EAX for the second; that is register allocation with no
//     effect on memory, and the per-site comments in the .cpp record it so the
//     arms stay matchable to the listing.
//   * What 0x007b1e90 does beyond reading the record's first and third words. The
//     observer records and mutates; everything it does is a fixture, not a claim
//     about that body.
//   * The 12-byte record's MIDDLE word, 0x510a95b. This body writes it on all
//     four registrations and no body read here consumes it, so the test asserts
//     the three words as bytes and claims nothing about what any of them MEANS.
//   * That the cell at 0x0150cdd4 really holds 0x3f800000. The body FORWARDS
//     whatever the cell holds, so the test drives the package-scope cell with a
//     different word (0x40490fdb, pi*f) and asserts the forwarded value matches
//     what it set. The image's own value is recorded in the header and asserted
//     nowhere, because nothing this body does observes it.
//   * The receiver's real size and its class. 0x310 is this package's lower
//     bound (0x30c plus one dword), not a layout claim, and no record in this
//     repository names a class.

#include "w2_00577310_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w2_00577310 {
namespace {

// The displacements and constants, as literals, so a wrong one in the header
// cannot silently agree with a wrong one in the .cpp.
constexpr std::size_t kTool = 0x308u;
constexpr std::size_t kTarget = 0x30cu;
constexpr Word kIdOne = 0x8104e4b0u;
constexpr Word kIdTwo = 0x9d1fcc2fu;
constexpr Word kIdThree = 0x7d708f46u;
constexpr Word kMiddle = 0x510a95bu;
constexpr Word kTail = 0x40464100u;
constexpr Word kImageWeightCell = 0x3f800000u;   // what the committed image holds at 0x0150cdd4
constexpr Word kDrivenWeightCell = 0x40490fdbu;  // pi*f, which the image does NOT hold
constexpr Word kClassNameAddress = 0x013eb430u;
constexpr Word kExpectedLookupKey = 0x700ed5e1u;
constexpr Word kAllOnes = 0xffffffffu;
constexpr Word kFactoryFirst = 0x34u;
constexpr std::size_t kSlotAcquire = 0x00u;
constexpr std::size_t kSlotRelease = 0x04u;
constexpr std::size_t kSlotQuery = 0x2cu;

// The modeled receiver is 0x310 bytes; the probe is that plus a 0x10-byte canary
// past its end, so a store at 0x310 or beyond shows up as a changed byte.
constexpr std::size_t kProbeSize = 0x320u;
// The table is 0x30 bytes so that slot +0x2c is the last word in it. The other
// nine words hold a decoy value, so a wrong slot displacement cannot land on a
// working observer and quietly agree.
constexpr std::size_t kSlotWords = 12u;
constexpr Word kDecoyWord = 0xdeadbeefu;

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

std::uintptr_t address_of(const void* pointer) {
  return reinterpret_cast<std::uintptr_t>(pointer);
}

// -- the fake objects ----------------------------------------------------------
// The table lives in its OWN object and the dispatched object holds only a
// POINTER to it at +0x00, because the machine reads the table pointer out of the
// object and then reads the code word out of the table:
//     MOV EAX,DWORD PTR [EDI]      level one, the table pointer
//     MOV EDX,DWORD PTR [EAX]      level two, one code word out of the table
// Keeping them apart is what makes a one-level reconstruction crash instead of
// quietly agreeing.
struct SlotTable {
  Word word[kSlotWords];
};

struct FakeObject {
  SlotTable* table_pointer;  // must be the object's first word
  Word payload[8];
};

static_assert(sizeof(SlotTable) == kSlotWords * sizeof(Word),
              "the table is an array of code words, exactly as the machine loads it");
static_assert(offsetof(FakeObject, table_pointer) == 0u,
              "the table pointer is the object's first word, at +0x00");

// -- the observer log ----------------------------------------------------------
constexpr int kMaxCalls = 16;

struct RegisterCall {
  const void* receiver;
  const PropertyRecord* record_address;
  Word words[3];
  int sequence;
};

struct SlotCall {
  const void* object;
  int sequence;
};

struct Log {
  // factory[0] is the first call, factory[1] the second; the reconstruction calls
  // the factory at most twice in one invocation.
  Word factory_seen[2][6];
  int factory_calls[2];  // reset at the start of every invocation
  int factory_total;     // cumulative across every invocation
  int construct_calls;
  int construct_argument;
  int construct_instance_is_receiver;

  RegisterCall reg[kMaxCalls];
  int reg_total;

  SlotCall acquire[kMaxCalls];
  int acquire_total;
  SlotCall release[kMaxCalls];
  int release_total;

  int query_calls;
  const void* query_object;
  Word query_subject;
  Word query_weight;
  Word* query_out;
  Word query_out_at_call;
  int query_sequence;

  int lookup_calls;
  const void* lookup_object;
  Word lookup_key;
  Word* lookup_out;
  Word lookup_out_at_call;
  int lookup_sequence;

  Word tool_member_at_first_acquire;
  Word target_member_at_first_acquire;

  int sequence;
};

Log g_log;

// What the factory hands back, per call. A queue rather than a hook, so the
// observer body stays a plain function.
Word g_factory_queue[4] = {0u, 0u, 0u, 0u};
int g_factory_queue_used = 0;
Word* g_tool_member = nullptr;
Word* g_target_member = nullptr;
const void* g_global_object = nullptr;

// What the query and the lookup answer, and whether they say yes.
Word g_query_written = 0u;
bool g_query_true = false;
Word g_lookup_written = 0u;
bool g_lookup_true = false;

void reset_state() {
  std::memset(&g_log, 0, sizeof(g_log));
  for (int index = 0; index < 4; ++index) {
    g_factory_queue[index] = 0u;
  }
  g_factory_queue_used = 0;
  g_query_written = 0u;
  g_query_true = false;
  g_lookup_written = 0u;
  g_lookup_true = false;
  g_query_weight_cell = kDrivenWeightCell;
}

// -- the three dispatch shapes, as observers -----------------------------------
void acquire_observer(void* object) {
  if (g_log.acquire_total < kMaxCalls) {
    g_log.acquire[g_log.acquire_total].object = object;
    g_log.acquire[g_log.acquire_total].sequence = ++g_log.sequence;
    if (g_log.acquire_total == 0 && g_tool_member != nullptr) {
      g_log.tool_member_at_first_acquire = *g_tool_member;
      g_log.target_member_at_first_acquire = *g_target_member;
    }
    ++g_log.acquire_total;
  }
}

void release_observer(void* object) {
  if (g_log.release_total < kMaxCalls) {
    g_log.release[g_log.release_total].object = object;
    g_log.release[g_log.release_total].sequence = ++g_log.sequence;
    ++g_log.release_total;
  }
}

bool query_observer(void* object, Word subject, Word weight, Word* out) {
  ++g_log.query_calls;
  g_log.query_sequence = ++g_log.sequence;
  g_log.query_object = object;
  g_log.query_subject = subject;
  g_log.query_weight = weight;
  g_log.query_out = out;
  // Sampled BEFORE the write: 0x005773ef stored zero over this word, so a model
  // that cleared it later, or not at all, is caught right here.
  g_log.query_out_at_call = (out != nullptr) ? *out : kAllOnes;
  if (out != nullptr) {
    *out = g_query_written;
  }
  return g_query_true;
}

void install_table(SlotTable& table) {
  for (std::size_t index = 0; index < kSlotWords; ++index) {
    table.word[index] = kDecoyWord;
  }
  table.word[kSlotAcquire / 4] =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(&acquire_observer));
  table.word[kSlotRelease / 4] =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(&release_observer));
  table.word[kSlotQuery / 4] =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(&query_observer));
}

void bind_table(FakeObject& object, SlotTable& table) {
  object.table_pointer = &table;
}

// -- the five direct callees ---------------------------------------------------
extern "C" Word W2_00577310_CDECL factory_lookup_00f473a0(Word first_argument,
                                                        const char* class_name,
                                                        Word third_argument,
                                                        Word fourth_argument,
                                                        Word fifth_argument,
                                                        Word sixth_argument) {
  const int slot = (g_log.factory_calls[0] == 0) ? 0 : 1;
  if (g_log.factory_calls[slot] < 6) {
    g_log.factory_seen[slot][0] = first_argument;
    g_log.factory_seen[slot][1] = static_cast<Word>(address_of(class_name));
    g_log.factory_seen[slot][2] = third_argument;
    g_log.factory_seen[slot][3] = fourth_argument;
    g_log.factory_seen[slot][4] = fifth_argument;
    g_log.factory_seen[slot][5] = sixth_argument;
  }
  ++g_log.factory_calls[slot];
  ++g_log.factory_total;
  const Word result = g_factory_queue_used < 4 ? g_factory_queue[g_factory_queue_used] : 0u;
  ++g_factory_queue_used;
  return result;
}

extern "C" void* W2_00577310_THISCALL construct_in_place_007b07e0(
    void* instance, Word argument) {
  ++g_log.construct_calls;
  g_log.construct_argument = static_cast<int>(argument);
  g_log.construct_instance_is_receiver = (instance != nullptr) ? 1 : 0;
  // 007b07e0's own 0x007b0852 `MOV EAX,ESI` shows it returns its receiver, so
  // returning `instance` here is the fixture the reconstruction relies on.
  return instance;
}

extern "C" void W2_00577310_THISCALL record_register_007b1e90(
    void* receiver, const PropertyRecord* record) {
  if (g_log.reg_total < kMaxCalls) {
    RegisterCall& call = g_log.reg[g_log.reg_total];
    call.receiver = receiver;
    call.record_address = record;
    call.words[0] = record->field_00;
    call.words[1] = record->field_04;
    call.words[2] = record->field_08;
    call.sequence = ++g_log.sequence;
    ++g_log.reg_total;
  }
  // Deliberately does NOT copy the record forward. A real callee can be handed
  // the same frame slot twice, and the reconstruction must not assume otherwise.
}

extern "C" void* W2_00577310_CDECL global_object_0067de30(void) {
  return const_cast<void*>(g_global_object);
}

extern "C" bool W2_00577310_CDECL instance_id_lookup_006a12a0(
    void* object, Word key, Word* out_parameter) {
  ++g_log.lookup_calls;
  g_log.lookup_sequence = ++g_log.sequence;
  g_log.lookup_object = object;
  g_log.lookup_key = key;
  g_log.lookup_out = out_parameter;
  // 0x00577495 zeroes this frame word AFTER the three pushes and BEFORE the call.
  g_log.lookup_out_at_call = (out_parameter != nullptr) ? *out_parameter : kAllOnes;
  if (out_parameter != nullptr) {
    *out_parameter = g_lookup_written;
  }
  return g_lookup_true;
}

// -- the receiver probe --------------------------------------------------------
struct Probe {
  std::uint8_t bytes[kProbeSize];
};

EditorReceiver* as_receiver(Probe& probe) {
  return reinterpret_cast<EditorReceiver*>(probe.bytes);
}

void fill_probe(Probe& probe, std::uint8_t pattern) {
  for (std::size_t index = 0; index < kProbeSize; ++index) {
    probe.bytes[index] = static_cast<std::uint8_t>(pattern + index);
  }
}

struct Diff {
  int at_tool = 0;
  int at_target = 0;
  int elsewhere = 0;
  std::size_t first_elsewhere = kProbeSize;
};

Diff diff_probe(const Probe& before, const Probe& after) {
  Diff diff;
  for (std::size_t index = 0; index < kProbeSize; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    if (index >= kTool && index < kTool + 4) {
      ++diff.at_tool;
    } else if (index >= kTarget && index < kTarget + 4) {
      ++diff.at_target;
    } else {
      ++diff.elsewhere;
      if (diff.first_elsewhere > index) {
        diff.first_elsewhere = index;
      }
    }
  }
  return diff;
}

// -- the ABI probe -------------------------------------------------------------
extern "C" Word probe_stack_pointer() {
  Word value = 0u;
  __asm__ __volatile__("movl %%esp, %0" : "=r"(value));
  return value;
}

// -- the scenario --------------------------------------------------------------
struct Bound {
  FakeObject object;
  SlotTable table;
};

struct Scenario {
  Probe probe;
  Bound fresh_a;
  Bound fresh_b;
  Bound old_tool;
  Bound old_target;
  Bound global_holder;
  Bound answer_holder;
};

void arm(Scenario& scenario, Word tool_word, Word target_word) {
  fill_probe(scenario.probe, 0x11u);
  install_table(scenario.fresh_a.table);
  install_table(scenario.fresh_b.table);
  install_table(scenario.old_tool.table);
  install_table(scenario.old_target.table);
  install_table(scenario.global_holder.table);
  install_table(scenario.answer_holder.table);
  bind_table(scenario.fresh_a.object, scenario.fresh_a.table);
  bind_table(scenario.fresh_b.object, scenario.fresh_b.table);
  bind_table(scenario.old_tool.object, scenario.old_tool.table);
  bind_table(scenario.old_target.object, scenario.old_target.table);
  bind_table(scenario.global_holder.object, scenario.global_holder.table);
  bind_table(scenario.answer_holder.object, scenario.answer_holder.table);
  *word_at(as_receiver(scenario.probe), kTool) = tool_word;
  *word_at(as_receiver(scenario.probe), kTarget) = target_word;
  reset_state();
  g_tool_member = word_at(as_receiver(scenario.probe), kTool);
  g_target_member = word_at(as_receiver(scenario.probe), kTarget);
  g_global_object = &scenario.global_holder.object;
}

bool invoke(Scenario& scenario, Word argument) {
  // The per-invocation counters and the factory's return queue are reset here,
  // because a factory call is "the first factory call of THIS invocation" from
  // the reconstruction's point of view and nothing else.
  g_log.factory_calls[0] = 0;
  g_log.factory_calls[1] = 0;
  g_factory_queue_used = 0;
  const Word before = probe_stack_pointer();
  re_00577310(as_receiver(scenario.probe), argument);
  return before == probe_stack_pointer();
}

Word word_of(const Scenario& scenario, std::size_t displacement) {
  return *word_at(&scenario.probe, displacement);
}

bool record_is(const RegisterCall& call, Word id) {
  return call.words[0] == id && call.words[1] == kMiddle && call.words[2] == kTail;
}

int factory_calls_total() { return g_log.factory_calls[0] + g_log.factory_calls[1]; }

}  // namespace

// The suite lives inside the package namespace so it can reach the observers and
// the accessors unqualified; `main` itself is global because that is where the
// runtime looks for it.
int run_tests() {
  Scenario scenario;

  // ==========================================================================
  // CASE A -- the whole path: cold receiver, query says yes, lookup answers.
  // REFUTE: a wrong receiver displacement, a dword store where the machine has
  // none, a wrong id on the wrong registration, a wrong registration receiver.
  // ==========================================================================
  {
    arm(scenario, 0u, 0u);
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_factory_queue[1] = static_cast<Word>(address_of(&scenario.fresh_b.object));
    g_query_true = true;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_true = true;
    g_lookup_written = 0x00c0ffeeu;
    const Probe before = scenario.probe;
    const bool balanced = invoke(scenario, 0x1234u);

    check(balanced, "case A: the body leaves ESP exactly where it found it");
    check(g_log.factory_calls[0] == 1 && g_log.factory_calls[1] == 1,
          "case A: the factory is called exactly twice, once per member");
    check(g_log.construct_calls == 2, "case A: the constructor is called once per member");
    check(static_cast<Word>(g_log.construct_argument) == kAllOnes,
          "case A: the constructor's stack word is 0xffffffff");
    for (int call = 0; call < 2; ++call) {
      check(g_log.factory_seen[call][0] == kFactoryFirst,
            "case A: the factory's first argument is 0x34 on both calls");
      check(g_log.factory_seen[call][1] == kClassNameAddress,
            "case A: the factory's second argument is the ADDRESS 0x013eb430 on both calls");
      check(g_log.factory_seen[call][2] == 0u && g_log.factory_seen[call][3] == 0u &&
                g_log.factory_seen[call][4] == 0u && g_log.factory_seen[call][5] == 0u,
            "case A: the factory's four remaining arguments are zero on both calls");
    }

    check(g_log.reg_total == 4, "case A: four registration calls, not three and not five");
    check(g_log.reg[0].receiver == &scenario.fresh_a.object,
          "case A: registration one is on the +0x308 member");
    check(g_log.reg[1].receiver == &scenario.fresh_a.object,
          "case A: registration two is on the +0x308 member");
    check(g_log.reg[2].receiver == &scenario.fresh_a.object,
          "case A: registration three is on the +0x308 member");
    check(g_log.reg[3].receiver == &scenario.fresh_b.object,
          "case A: registration four is on the +0x30c member, not the +0x308 one");
    check(record_is(g_log.reg[0], kIdOne), "case A: registration one carries id 0x8104e4b0");
    check(record_is(g_log.reg[1], kIdTwo), "case A: registration two carries id 0x9d1fcc2f");
    check(record_is(g_log.reg[2], kIdThree), "case A: registration three carries id 0x7d708f46");
    check(g_log.reg[3].words[0] == 0x00c0ffeeu && g_log.reg[3].words[1] == kMiddle &&
              g_log.reg[3].words[2] == kTail,
          "case A: registration four carries the instance id and the two shared words");
    check(address_of(g_log.reg[0].record_address) != address_of(g_log.reg[1].record_address) &&
              address_of(g_log.reg[1].record_address) != address_of(g_log.reg[2].record_address),
          "case E refuted: the three registration records are at three different addresses");
    check(address_of(g_log.reg[1].record_address) - address_of(g_log.reg[0].record_address) == 12u &&
              address_of(g_log.reg[2].record_address) - address_of(g_log.reg[1].record_address) == 12u,
          "case E refuted: the records are twelve bytes apart, in order");
    check(g_log.reg[3].record_address == g_log.reg[2].record_address,
          "case E refuted: the fourth registration is written over the THIRD record's slot");

    check(g_log.query_calls == 1, "case A: the query runs exactly once");
    check(g_log.query_object == &scenario.global_holder.object,
          "case A: the query's receiver is the object the global accessor returned");
    check(g_log.query_subject == 0x1234u,
          "case I refuted: the query's subject is the ORIGINAL argument, not the cleared word");
    check(g_log.query_weight == kDrivenWeightCell,
          "case H refuted: the query's second argument is the cell's CONTENTS, forwarded, "
          "not a hard-coded constant and not an address");
    check(g_log.query_out_at_call == 0u,
          "case K refuted: the out-parameter was already zero when the query was entered");
    check(g_log.query_out != nullptr, "case A: the query was given an out-parameter");

    check(g_log.lookup_calls == 1, "case A: the instance-id lookup runs exactly once");
    check(g_log.lookup_object == &scenario.answer_holder.object,
          "case A: the lookup's first argument is the object the query answered with");
    check(g_log.lookup_key == kExpectedLookupKey, "case A: the lookup's second argument is 0x700ed5e1");
    check(g_log.lookup_out_at_call == 0u,
          "case K refuted: the lookup's out word was zeroed BEFORE the call");

    check(g_log.acquire_total == 2, "case A: two acquires, one per member");
    check(g_log.acquire[0].object == &scenario.fresh_a.object, "case A: the first acquire is the new tool");
    check(g_log.acquire[1].object == &scenario.fresh_b.object, "case A: the second acquire is the new target");
    check(g_log.release_total == 1, "case A: exactly one release, of the query's answer");
    check(g_log.release[0].object == &scenario.answer_holder.object,
          "case A: the release is on the object the query answered with");
    check(g_log.tool_member_at_first_acquire == 0u,
          "case D refuted: the acquire on the new tool runs BEFORE the member is stored");
    check(g_log.acquire[0].sequence < g_log.query_sequence,
          "case D refuted: the cold swap completes before the query runs");

    const Diff diff = diff_probe(before, scenario.probe);
    check(diff.at_tool == 4, "case A refuted: exactly the four bytes of the +0x308 word change");
    check(diff.at_target == 4, "case A refuted: exactly the four bytes of the +0x30c word change");
    check(diff.elsewhere == 0, "case A refuted: no other receiver byte changes");
    check(word_of(scenario, kTool) == static_cast<Word>(address_of(&scenario.fresh_a.object)),
          "case A: the +0x308 word holds the constructed tool");
    check(word_of(scenario, kTarget) == static_cast<Word>(address_of(&scenario.fresh_b.object)),
          "case A: the +0x30c word holds the constructed target");
  }

  // ==========================================================================
  // CASE B -- a warm receiver. REFUTE: the guard read as something other than
  // "the +0x308 member is null", or the cold block made unconditional.
  // ==========================================================================
  {
    // Both members warm and the query answering no, so the ONLY things this
    // invocation can do are run the query and the tail release. Anything the
    // cold block would have done shows up immediately as a failure.
    arm(scenario, static_cast<Word>(address_of(&scenario.old_tool.object)),
        static_cast<Word>(address_of(&scenario.old_target.object)));
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_query_true = false;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    const Probe before = scenario.probe;
    const bool balanced = invoke(scenario, 0x55u);

    check(balanced, "case B: the body leaves ESP exactly where it found it");
    check(factory_calls_total() == 0, "case B refuted: a warm receiver performs no factory call");
    check(g_log.construct_calls == 0,
          "case B refuted: a warm receiver performs no constructor call");
    check(g_log.reg_total == 0, "case B refuted: a warm receiver performs no registration at all");
    check(g_log.acquire_total == 0, "case B refuted: no acquire on a warm receiver");
    check(g_log.lookup_calls == 0, "case B: a false query runs no lookup");
    check(g_log.release_total == 1 &&
              g_log.release[0].object == &scenario.answer_holder.object,
          "case B: only the tail release runs on a warm receiver");
    const Diff diff = diff_probe(before, scenario.probe);
    check(diff.elsewhere == 0 && diff.at_tool == 0 && diff.at_target == 0,
          "case B refuted: a warm receiver with a false query is not written to at all");
  }

  // ==========================================================================
  // CASE C -- the sentinel. REFUTE: the test read as "non-zero" instead of
  // "== 0xffffffff". Driven with 0, 1, 0x80000000, 0xfffffffe and 0xffffffff.
  // ==========================================================================
  {
    const Word subjects[5] = {0xffffffffu, 0x00000000u, 0x00000001u, 0x80000000u,
                              0xfffffffeu};
    for (std::size_t index = 0; index < 5; ++index) {
      arm(scenario, 0u, 0u);
      g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
      g_factory_queue[1] = 0u;
      g_query_true = true;
      g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
      const bool balanced = invoke(scenario, subjects[index]);
      check(balanced, "case C: the body leaves ESP exactly where it found it");
      check(g_log.reg_total == 3,
            "case C: the cold block's three registrations run whatever the argument is");
      if (subjects[index] == kAllOnes) {
        check(g_log.query_calls == 0, "case K refuted: 0xffffffff is the sentinel and stops the body");
        check(g_log.lookup_calls == 0, "case C: the sentinel arm performs no lookup");
        check(g_log.release_total == 0, "case M refuted: the sentinel arm performs no release");
      } else {
        check(g_log.query_calls == 1,
              "case K refuted: every argument other than 0xffffffff reaches the query");
      }
    }
  }

  // ==========================================================================
  // CASE D -- the factory returns null. REFUTE: an allocation-failure early
  // return. The bytes install a null replacement and carry on regardless.
  // ==========================================================================
  {
    arm(scenario, 0u, 0u);
    g_factory_queue[0] = 0u;
    g_query_true = false;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    invoke(scenario, 0x7u);
    check(g_log.construct_calls == 0, "case D: a null factory result skips the constructor");
    check(g_log.reg_total == 3,
          "case D refuted: a null factory result still registers three times instead of returning");
    check(g_log.reg[0].receiver == nullptr && g_log.reg[1].receiver == nullptr &&
              g_log.reg[2].receiver == nullptr,
          "case D refuted: the registrations go to the NULL member rather than being skipped");
    check(g_log.acquire_total == 0, "case D: a null replacement causes no acquire");
    check(g_log.release_total == 1 && g_log.release[0].object == &scenario.answer_holder.object,
          "case D refuted: the swap is skipped as equal, so the old member is not released");
    check(word_of(scenario, kTool) == 0u, "case D: the +0x308 member is left null");
  }

  // ==========================================================================
  // CASE E -- the swap's equality test, on the SECOND swap (the first is gated
  // by the very null test that makes the swap run). REFUTE: the equality test
  // inverted or dropped, which would acquire and release a member it did not
  // change.
  // ==========================================================================
  {
    arm(scenario, static_cast<Word>(address_of(&scenario.old_tool.object)), 0u);
    // The cold block is skipped, so the factory is called ONCE in this
    // invocation and its return value is the replacement for +0x30c.
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.old_tool.object));
    g_query_true = true;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_true = true;
    g_lookup_written = 0x22u;
    // The +0x30c member already holds exactly what the factory will produce.
    *word_at(as_receiver(scenario.probe), kTarget) =
        static_cast<Word>(address_of(&scenario.old_tool.object));
    invoke(scenario, 0x9u);
    check(g_log.acquire_total == 0,
          "case E refuted: a replacement equal to the member causes no acquire");
    check(g_log.release_total == 1 && g_log.release[0].object == &scenario.answer_holder.object,
          "case E refuted: a replacement equal to the member causes no member release");
    check(g_log.reg_total == 1 && g_log.reg[0].receiver == &scenario.old_tool.object,
          "case E: the fourth registration still runs, on the unchanged member");
  }

  // ==========================================================================
  // CASE F -- the query says no. REFUTE: the polarity of the 0x0057742d branch.
  // ==========================================================================
  {
    arm(scenario, 0u, 0u);
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_factory_queue[1] = static_cast<Word>(address_of(&scenario.fresh_b.object));
    g_query_true = false;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_true = true;
    g_lookup_written = 0x33u;
    const Probe before = scenario.probe;
    invoke(scenario, 0xau);
    check(g_log.factory_calls[1] == 0, "case F refuted: a false query builds no second member");
    check(g_log.reg_total == 3, "case F: a false query still leaves the three cold registrations");
    check(g_log.lookup_calls == 0, "case F refuted: a false query performs no lookup");
    check(g_log.release_total == 1 && g_log.release[0].object == &scenario.answer_holder.object,
          "case F: a false query still releases the word it left behind");
    const Diff diff = diff_probe(before, scenario.probe);
    check(diff.at_target == 0, "case F refuted: the +0x30c member is untouched on a false query");
  }

  // ==========================================================================
  // CASE G -- the lookup's bool is DISCARDED and its out word is what counts.
  // REFUTE: a reconstruction that branches on the callee's return value. Both
  // directions are driven, and they disagree.
  // ==========================================================================
  {
    // G1: the callee returns FALSE but writes a non-zero id.
    arm(scenario, 0u, 0u);
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_factory_queue[1] = static_cast<Word>(address_of(&scenario.fresh_b.object));
    g_query_true = true;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_true = false;
    g_lookup_written = 0x00abcdefu;
    invoke(scenario, 0xbu);
    check(g_log.reg_total == 4,
          "case G refuted: a lookup returning false but writing an id still registers it");
    check(g_log.reg[3].words[0] == 0x00abcdefu,
          "case G refuted: the fourth record carries the id the callee WROTE");

    // G2: the callee returns TRUE but writes zero.
    arm(scenario, 0u, 0u);
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_factory_queue[1] = static_cast<Word>(address_of(&scenario.fresh_b.object));
    g_query_true = true;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_true = true;
    g_lookup_written = 0u;
    invoke(scenario, 0xcu);
    check(g_log.reg_total == 3,
          "case G refuted: a lookup returning true but writing zero does NOT register");
    check(g_log.acquire_total == 2,
          "case G: the second member was still built and acquired before the lookup");
    check(g_log.release_total == 1 && g_log.release[0].object == &scenario.answer_holder.object,
          "case G: the tail release still runs after a zero instance id");
  }

  // ==========================================================================
  // CASE H -- a query that answers with NULL. REFUTE: a release through a null
  // table, i.e. a model that dropped the guard at 0x005774d5.
  // ==========================================================================
  {
    arm(scenario, 0u, 0u);
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_factory_queue[1] = static_cast<Word>(address_of(&scenario.fresh_b.object));
    g_query_true = false;
    g_query_written = 0u;
    invoke(scenario, 0xdu);
    check(g_log.release_total == 0, "case H refuted: a null answer releases nothing");
    check(g_log.lookup_calls == 0, "case H: a false query with a null answer runs no lookup");
  }

  // ==========================================================================
  // CASE I -- the dead block at 0x00577406. REFUTE: any second release of the
  // handle before the query. The body stores zero over the caller's argument
  // word at 0x005773ef and the only call in between is the six-byte global
  // accessor, so that block can never be entered. Exactly one release of the
  // handle happens in the whole call, and it is the tail one.
  // ==========================================================================
  {
    arm(scenario, 0u, 0u);
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_factory_queue[1] = 0u;
    g_query_true = false;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_written = 0u;
    invoke(scenario, 0x80000000u);
    check(g_log.query_out_at_call == 0u,
          "case I refuted: the out-parameter the query was handed already held zero");
    check(g_log.release_total == 1,
          "case I refuted: exactly one release of the handle runs, so 0x00577406 is never entered");
    check(g_log.release[0].sequence > g_log.query_sequence,
          "case I refuted: the one release happens AFTER the query, not before it");
  }

  // ==========================================================================
  // CASE J -- pointer level and slot displacement. REFUTE: a one-level slot
  // read, a slot read off the object rather than off its table, or a wrong slot
  // displacement. Nine decoy words sit in the same table, and a decoy value is
  // planted where a one-level read would find it.
  // ==========================================================================
  {
    arm(scenario, 0u, 0u);
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_factory_queue[1] = static_cast<Word>(address_of(&scenario.fresh_b.object));
    g_query_true = true;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_true = true;
    g_lookup_written = 0x44u;
    // Decoys: distinct non-code words at the neighbouring slot displacements, so
    // a model that read +0x1 for the acquire, +0x0 for the release or +0x28 for
    // the query would call through 0x11111111 and crash rather than agree.
    scenario.fresh_a.table.word[1] = 0x11111111u;
    scenario.fresh_a.table.word[11] = 0x22222222u;
    scenario.fresh_b.table.word[2] = 0x33333333u;
    scenario.global_holder.table.word[1] = 0x44444444u;
    scenario.answer_holder.table.word[3] = 0x55555555u;
    // And a data word where a one-level read would find a slot: the object's own
    // +0x00 is the TABLE POINTER, so a model that read the slot off the object
    // would call through an address and fault.
    scenario.fresh_a.object.payload[0] = 0x66666666u;
    invoke(scenario, 0xeu);
    check(g_log.acquire_total == 2 && g_log.release_total == 1 && g_log.query_calls == 1,
          "case J refuted: the slots were read out of the tables at the right displacements");
    check(g_log.query_object == &scenario.global_holder.object,
          "case J: the query went through the global holder's table, not another object's");
  }

  // ==========================================================================
  // CASE K -- an old member that IS replaced. REFUTE: releasing the new member,
  // or releasing the old one before storing the new one.
  // ==========================================================================
  {
    arm(scenario, 0u, static_cast<Word>(address_of(&scenario.old_target.object)));
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_factory_queue[1] = static_cast<Word>(address_of(&scenario.fresh_b.object));
    g_query_true = true;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_true = true;
    g_lookup_written = 0x55u;
    invoke(scenario, 0xfu);
    check(g_log.release_total == 2, "case K: the replaced old member and the answer are released");
    check(g_log.release[0].object == &scenario.old_target.object,
          "case K refuted: the OLD member of the +0x30c swap is released, not the new one");
    check(g_log.acquire[1].sequence < g_log.release[0].sequence,
          "case K refuted: the acquire on the new member precedes the release of the old one");
    check(g_log.release[1].object == &scenario.answer_holder.object,
          "case K: the tail release of the query's answer comes last");
    check(g_log.acquire_total == 2, "case K: both replacements are acquired");
    check(g_log.target_member_at_first_acquire ==
              static_cast<Word>(address_of(&scenario.old_target.object)),
          "case K refuted: the +0x30c member is still the OLD one when a new member is acquired");
  }

  // ==========================================================================
  // CASE L -- three consecutive calls on one receiver. REFUTE: a body that
  // re-initialises the cold block on every call. The +0x308 member is written
  // once and every later call finds it warm.
  // ==========================================================================
  {
    arm(scenario, 0u, 0u);
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_a.object));
    g_factory_queue[1] = 0u;
    g_query_true = true;
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_true = true;
    g_lookup_written = 0x66u;
    invoke(scenario, 0x10u);
    const int after_first = g_log.factory_total;
    const int regs_after_first = g_log.reg_total;
    // The +0x30c member is still null after the first invocation, because the
    // second factory was handed the queue's default null and null equals null.
    check(after_first == 2 && word_of(scenario, kTarget) == 0u,
          "case L: the first call builds the tool and leaves the target null");
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_b.object));
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_written = 0x77u;
    invoke(scenario, 0x11u);
    const int after_second = g_log.factory_total;
    const int regs_after_second = g_log.reg_total;
    g_factory_queue[0] = static_cast<Word>(address_of(&scenario.fresh_b.object));
    g_query_written = static_cast<Word>(address_of(&scenario.answer_holder.object));
    g_lookup_written = 0x88u;
    invoke(scenario, 0x12u);

    check(after_second == 3,
          "case L refuted: the second call builds only the +0x30c member, the cold block is skipped");
    check(g_log.factory_total == 4,
          "case L refuted: the third call also builds only the +0x30c member");
    check(regs_after_first == 4 && regs_after_second == 5 && g_log.reg_total == 6,
          "case L refuted: each later call adds only the fourth registration");
    check(g_log.reg[5].receiver == &scenario.fresh_b.object,
          "case L: the last registration is on the +0x30c member built by the second call");
    check(g_log.acquire_total == 2,
          "case L refuted: the third call's replacement equals the member, so it is not acquired");
  }

  if (g_failures == 0) {
    std::printf("pkg-swarm-w2-00577310: every model-test case passed\n");
    return 0;
  }
  std::fprintf(stderr, "pkg-swarm-w2-00577310: %d assertion failure(s)\n", g_failures);
  return 1;
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00577310

int main() {
  return openspore::reconstruction::pkg_swarm_w2_00577310::run_tests();
}
