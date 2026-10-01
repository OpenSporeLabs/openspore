// PKG-CHEAT-DISPATCH-0067E6F0 -- behavioural model test for SporeApp.exe VA
// 0x0067e6f0 (App::cCheatManager::func40h), build 3.1.0.22, image base
// 0x00400000.
//
// Provenance. The target under test is the 26-instruction body
// 0x0067e6f0..0x0067e726. Its listing is persisted in
// reconstruction/evidence/0067e6f0/evidence.json, its bounded ABI record,
// mechanics and unresolved questions in
// reconstruction/metadata/pkg-cheat-dispatch-0067e6f0/0067e6f0.json, and its
// structural verdict in reconstruction/evidence/0067e6f0/validation.json, which
// pins the reconstruction under test at
// sha256 f7cfab131ae7a8246a88c3f9001d38545f81f3f64d6844a546bf640ef6d976d8.
// That digest covers
// reconstruction/staging/pkg-cheat-dispatch-0067e6f0/cheat_dispatch_0067e6f0.cpp
// and is not touched by this file. Every check below names the machine
// instruction whose behaviour it pins.
//
// What is testable, and what is not. What this body observably does is test one
// receiver byte, walk a chain, make one indirect call per node and one direct
// call per step. All of that is substituted here: the two callees are stubs, so
// the test proves the traversal, the call shape and the read-only property, not
// the callees. What the listing fixes and this test therefore asserts: the
// +0x64 gate, the address-valued terminator at +0x4c, the head at +0x50, the
// TWO-LEVEL dispatch load node+0x10 -> receiver+0x00 -> table+0x1c
// (0x0067e707, 0x0067e70a, 0x0067e70c) together with its reloading on every
// iteration, the literal leading word 1, the unchanged trailing word, the order
// dispatch-then-successor, and the total absence of writes.
//
// The two levels are asserted separately from the reloading, because a one-level
// read and a two-level read differ in WHICH object the slot comes from, not in
// how often it is read. test_dispatch_is_a_two_level_load is that check: it
// plants a decoy entry at the receiver's own +0x1c -- the same displacement, one
// level up -- and requires it to stay uncalled while the table's +0x1c entry is
// the one 0x0067e712 calls.
//
// What the evidence does NOT fix, and this test deliberately does NOT assert:
// the meaning of the event argument, the meaning of the +0x64 byte, what the
// +0x1c slot holds, what 0x00921580 is, and whether the table is a vtable. The
// sibling entry 0x0067e730 (App::cCheatManager::func44h) pushes the literal 0
// from the same walk and carries no +0x64 gate; that is a contrast of observed
// bytes only, and neither body is claimed to say what the leading word means.

#include "cheat_dispatch_0067e6f0.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <vector>

#if defined(_MSC_VER)
#define PKG_CHEAT_DISPATCH_0067E6F0_CDECL __cdecl
#else
#define PKG_CHEAT_DISPATCH_0067E6F0_CDECL __attribute__((cdecl))
#endif

#if defined(_MSC_VER)
#define PKG_CHEAT_DISPATCH_0067E6F0_THISCALL __thiscall
#else
#define PKG_CHEAT_DISPATCH_0067E6F0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_cheat_dispatch_0067e6f0 {
namespace {

// Receiver displacements. The header deliberately names only the node-relative,
// receiver-relative and call-table-relative ones, so the three receiver-word
// displacements are restated here and pinned at run time in
// test_displacement_pins(). kReceiverTableOffset (0x0067e70a) and
// kCallTableEntryOffset (0x0067e70c) come from the header and are pinned there.
constexpr std::size_t kGateByteOffset = 0x64;    // 0x0067e6f0 CMP byte ptr [ECX+0x64],0
constexpr std::size_t kTerminatorOffset = 0x4c;  // 0x0067e6fb LEA EDI,[ECX+0x4c]
constexpr std::size_t kChainHeadOffset = 0x50;    // 0x0067e6f7 MOV ESI,dword ptr [ECX+0x50]

int failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++failures;
  }
}

// ---------------------------------------------------------------------------
// Event log. Both callees append here, so the interleaving the listing fixes
// (dispatch, then successor fetch) is observable and not just a call count.
// ---------------------------------------------------------------------------
using EventLog = std::vector<const char*>;

EventLog g_log;
EventLog* g_events = nullptr;

struct StepEdge {
  OpaqueWord* from;
  OpaqueWord* to;
};

std::vector<StepEdge> g_step_edges;
OpaqueWord* g_terminator = nullptr;   // the address the stepper hands back at the end
OpaqueWord* g_forced_next = nullptr;  // when set, step 1 returns this instead
int g_step_calls = 0;
int g_dispatch_calls = 0;

// Per-dispatch observations, one entry per call, in call order.
std::vector<OpaqueWord*> g_seen_receiver;
std::vector<int> g_seen_leading;
std::vector<OpaqueWord> g_seen_trailing;
std::vector<int> g_seen_entry_id;

// Modelling knobs for the one check that needs a callee to misbehave.
bool g_detach_on_first_dispatch = false;
struct FakeManager* g_manager = nullptr;

void record(const char* name) {
  if (g_events != nullptr) {
    g_events->push_back(name);
  }
}

// Compares a word the dispatch was handed against the address of a fake object.
// The body only ever carries these around as machine words, so every identity
// check goes through this.
bool is_address_of(OpaqueWord* seen, const void* object) {
  return seen == reinterpret_cast<const OpaqueWord*>(object);
}

// ---------------------------------------------------------------------------
// Fake objects. These are stand-ins for memory the body only ever holds through
// a pointer, and they mirror exactly the displacements the listing reads and
// nothing else. They deliberately carry no named members for anything the
// listing does not reach, and no member here asserts a meaning: a receiver word
// at +0x64 is a byte the body tests, a word at +0x50 is a link, and a word at
// +0x4c is never loaded at all.
// ---------------------------------------------------------------------------

// The word the body calls through: 0x0067e70c MOV EDX,dword ptr [EAX+0x1c].
struct FakeTable {
  OpaqueWord prefix[7]{};  // +0x00 .. +0x17
  DispatchEntry entry = nullptr;  // +0x1c
};

// The receiver the node dispatches through. It is the object 0x0067e707 puts in
// ECX, and the dispatch load chain that starts there is TWO levels deep:
//
//   0x0067e70a  MOV EAX,dword ptr [ECX]        EAX = the receiver's FIRST word,
//                                             which is a table pointer and not
//                                             the call target
//   0x0067e70c  MOV EDX,dword ptr [EAX + 0x1c] EDX = the table's slot, one level
//                                             below that pointer
//   0x0067e712  CALL EDX                      the body's only indirect transfer
//
// The decoy slot below is what makes the first level loadable as a load and the
// second one necessary. A DECOY entry is planted at the receiver's OWN +0x1c --
// the same displacement as the real slot, one level up -- so a reconstruction
// that collapsed the chain into a single read dispatches through something this
// test can name and count, instead of calling whatever bytes happen to sit
// there. No instruction in the 26-instruction listing reads [ECX+0x1c].
// See test_dispatch_is_a_two_level_load.
struct FakeReceiver {
  FakeTable* table = nullptr;                          // +0x00, 0x0067e70a
  OpaqueWord filler_04[6]{};                           // +0x04 .. +0x1b, never read
  DispatchEntry decoy_receiver_slot = nullptr;         // +0x1c, never read by the listing
};

// A chain node: 0x0067e707 MOV ECX,dword ptr [ESI+0x10] is the only node word
// the body reads. The link word the stepper consults is not visible to it, so
// the node here has none.
struct FakeNode {
  OpaqueWord prefix[4]{};  // +0x00 .. +0x0f
  FakeReceiver* receiver = nullptr;  // +0x10
};

// Fill every byte of `object`, padding included, with `pattern`.
//
// This is a std::memset, written out. The fixture types below carry default
// member initialisers so that a default-constructed object is well defined, and
// that makes them non-trivial, which -Wclass-memaccess (gcc, and therefore this
// package under the repository's -Werror) rejects for std::memset even though
// the intent here is exactly a byte pattern, not a value assignment. Writing the
// bytes directly states the intent, keeps the test's starting state identical
// under both compilers, and loses no assertion.
template <class T>
inline void fill_bytes(T& object, unsigned char pattern) {
  unsigned char* bytes = reinterpret_cast<unsigned char*>(&object);
  for (std::size_t index = 0; index < sizeof(T); ++index) {
    bytes[index] = pattern;
  }
}

// The array form is separate because a call such as fill_bytes(chain.nodes, ...)
// would otherwise deduce T from the decayed pointer and lose the extent, so
// sizeof(T) would be sizeof(one element) and only the first node would be
// filled. Binding the array by reference keeps the whole run in scope.
template <class T, std::size_t Count>
inline void fill_bytes(T (&array)[Count], unsigned char pattern) {
  fill_bytes(array[0], pattern);
  for (std::size_t index = 1; index < Count; ++index) {
    fill_bytes(array[index], pattern);
  }
}

struct FakeManager {
  OpaqueWord prefix[19]{};      // +0x00 .. +0x4b
  OpaqueWord terminator_04c{};  // +0x4c, address-taken by 0x0067e6fb, never loaded
  FakeNode* head_050 = nullptr; // +0x50, the chain head
  OpaqueWord gap_054[4]{};      // +0x54 .. +0x63
  unsigned char gate_064 = 0;   // +0x64, tested once at 0x0067e6f0, never written
  OpaqueWord tail_068[4]{};     // +0x68 .. onward
};

// If any of these layouts drifted the test would be exercising a different object
// graph than the binary's, so they are compile-time.
static_assert(offsetof(FakeTable, entry) == kCallTableEntryOffset,
              "the dispatch entry must sit at table+0x1c");
static_assert(offsetof(FakeNode, receiver) == kNodeWordOffset,
              "the per-node receiver word must sit at node+0x10");
static_assert(offsetof(FakeManager, terminator_04c) == kTerminatorOffset,
              "the terminator word must sit at manager+0x4c");
static_assert(offsetof(FakeManager, head_050) == kChainHeadOffset,
              "the chain head word must sit at manager+0x50");
static_assert(offsetof(FakeManager, gate_064) == kGateByteOffset,
              "the gate byte must sit at manager+0x64");
static_assert(offsetof(FakeReceiver, table) == kReceiverTableOffset,
              "the table word must be the receiver's first word, at receiver+0x0");
static_assert(offsetof(FakeReceiver, decoy_receiver_slot) == kCallTableEntryOffset,
              "the decoy must sit at receiver+0x1c, the same displacement as the real slot");

// ---------------------------------------------------------------------------
// The indirect call, 0x0067e712 CALL EDX. Each stub is a distinct address, so
// the three tables hold three different words in their +0x1c slots and the walk
// can only visit them in the order the chain gives.
// ---------------------------------------------------------------------------
void note_dispatch(int entry_id, OpaqueWord* receiver, int leading_word,
                   OpaqueWord event_argument) {
  ++g_dispatch_calls;
  g_seen_entry_id.push_back(entry_id);
  g_seen_receiver.push_back(receiver);
  g_seen_leading.push_back(leading_word);
  g_seen_trailing.push_back(event_argument);
  record("dispatch");
  if (g_detach_on_first_dispatch && g_dispatch_calls == 1) {
    // The dispatched receiver severs the chain it was handed. The successor the
    // stepper hands back is now the terminator, and the head word is rewritten
    // as well, so a reconstruction that re-read the head at +0x50 instead of
    // calling 0x00921580 would also stop here and could not tell the two apart
    // on this check -- the ordering proof is the "step" event below.
    g_step_edges.clear();
    if (g_manager != nullptr) {
      g_manager->head_050 = reinterpret_cast<FakeNode*>(g_terminator);
    }
    record("detach");
  }
}

void PKG_CHEAT_DISPATCH_0067E6F0_THISCALL entry_stub_a(OpaqueWord* receiver, int leading_word,
                             OpaqueWord event_argument) {
  note_dispatch(0, receiver, leading_word, event_argument);
}

void PKG_CHEAT_DISPATCH_0067E6F0_THISCALL entry_stub_b(OpaqueWord* receiver, int leading_word,
                             OpaqueWord event_argument) {
  note_dispatch(1, receiver, leading_word, event_argument);
}

void PKG_CHEAT_DISPATCH_0067E6F0_THISCALL entry_stub_c(OpaqueWord* receiver, int leading_word,
                             OpaqueWord event_argument) {
  note_dispatch(2, receiver, leading_word, event_argument);
}

// The DECOY at receiver+0x1c. Reaching this stub means the slot load was made
// from the receiver instead of from the receiver's table, i.e. that the
// 0x0067e70a level was skipped. It records entry id -1 and its own event name,
// so the failure is reported by name and by count rather than as a call through
// arbitrary bytes.
void PKG_CHEAT_DISPATCH_0067E6F0_THISCALL decoy_receiver_slot_stub(OpaqueWord* receiver, int leading_word,
                                        OpaqueWord event_argument) {
  ++g_dispatch_calls;
  g_seen_receiver.push_back(receiver);
  g_seen_leading.push_back(leading_word);
  g_seen_trailing.push_back(event_argument);
  g_seen_entry_id.push_back(-1);
  record("decoy_receiver_slot");
  if (g_detach_on_first_dispatch && g_dispatch_calls == 1) {
    g_step_edges.clear();
    if (g_manager != nullptr) {
      g_manager->head_050 = reinterpret_cast<FakeNode*>(g_terminator);
    }
    record("detach");
  }
}

// ---------------------------------------------------------------------------
// 0x00921580, called once per dispatched node. The listing fixes only that it
// takes the current node and returns the word 0x0067e71a moves into ESI, and
// that the caller drops the argument at 0x0067e71c; the stub reproduces that
// contract and nothing about what 0x00921580 actually is.
// ---------------------------------------------------------------------------
OpaqueWord* PKG_CHEAT_DISPATCH_0067E6F0_CDECL step_stub(OpaqueWord* node) {
  record("step");
  ++g_step_calls;
  if (g_forced_next != nullptr && g_step_calls == 1) {
    return g_forced_next;
  }
  for (const StepEdge& edge : g_step_edges) {
    if (edge.from == node) {
      return edge.to;
    }
  }
  return g_terminator;
}

}  // namespace

// The header declares this slot and the reconstruction calls it; nothing defines
// it, so this translation unit supplies the stub. The definition follows an
// extern declaration, so the const object keeps external linkage as the header
// intends.
ChainStepper const next_node_00921580 = &step_stub;

namespace {

// Three nodes, three receivers, three tables, three distinct entry stubs, wired
// so the stepper walks 0 -> 1 -> 2 -> terminator. Every chain built here
// terminates, because the last edge and the fallback both return the terminator
// address.
struct Chain {
  FakeManager manager{};
  FakeNode nodes[3]{};
  FakeReceiver receivers[3]{};
  FakeTable tables[3]{};
};

void build_chain(Chain& chain) {
  // Memset first so every byte, padding included, starts from a known pattern
  // and the byte-comparisons below cannot pass on indeterminate bytes.
  fill_bytes(chain.manager, 0xa5);
  fill_bytes(chain.nodes, 0x5a);
  fill_bytes(chain.receivers, 0x3c);
  fill_bytes(chain.tables, 0xc3);

  g_manager = &chain.manager;
  g_terminator = reinterpret_cast<OpaqueWord*>(&chain.manager.terminator_04c);
  g_forced_next = nullptr;
  g_detach_on_first_dispatch = false;
  g_step_edges.clear();

  chain.tables[0].entry = &entry_stub_a;
  chain.tables[1].entry = &entry_stub_b;
  chain.tables[2].entry = &entry_stub_c;
  for (int i = 0; i < 3; ++i) {
    chain.receivers[i].table = &chain.tables[i];
    chain.receivers[i].decoy_receiver_slot = &decoy_receiver_slot_stub;
    chain.nodes[i].receiver = &chain.receivers[i];
  }
  g_step_edges.push_back({reinterpret_cast<OpaqueWord*>(&chain.nodes[0]),
                         reinterpret_cast<OpaqueWord*>(&chain.nodes[1])});
  g_step_edges.push_back({reinterpret_cast<OpaqueWord*>(&chain.nodes[1]),
                         reinterpret_cast<OpaqueWord*>(&chain.nodes[2])});
  g_step_edges.push_back({reinterpret_cast<OpaqueWord*>(&chain.nodes[2]),
                         g_terminator});
  chain.manager.head_050 = &chain.nodes[0];
  chain.manager.gate_064 = 0;  // the gate is opened per test
}

// One run of the entry, with the observation state cleared first.
void run(FakeManager& manager, OpaqueWord event_argument) {
  EventLog log;
  g_events = &log;
  g_seen_receiver.clear();
  g_seen_leading.clear();
  g_seen_trailing.clear();
  g_seen_entry_id.clear();
  g_step_calls = 0;
  g_dispatch_calls = 0;

  cCheatManager_func40h_0067e6f0(reinterpret_cast<OpaqueWord*>(&manager),
                                 event_argument);

  g_events = nullptr;
  g_log = log;
}

// Compares the whole log against the exact sequence the listing fixes.
void check_log(const EventLog& expected, const char* what) {
  if (g_log.size() != expected.size()) {
    check(false, what);
    return;
  }
  bool same = true;
  for (std::size_t i = 0; i < expected.size(); ++i) {
    if (std::strcmp(g_log[i], expected[i]) != 0) {
      same = false;
    }
  }
  check(same, what);
}

// ---------------------------------------------------------------------------
// Checks
// ---------------------------------------------------------------------------

// 0x0067e6f0 CMP byte ptr [ECX+0x64],0x0 / 0x0067e6f4 JZ 0x0067e726. With the
// gate byte clear the body returns before the register saves, so a fully built
// chain is present and still nothing happens. The direct caller's argument is
// read only at 0x0067e703, which is never reached, so two different argument
// words must both be inert.
void test_gate_clear_returns_immediately() {
  Chain chain;
  build_chain(chain);
  const OpaqueWord words[] = {0x00000000u, 0xffffffffu};
  for (OpaqueWord event_argument : words) {
    run(chain.manager, event_argument);
    check(g_dispatch_calls == 0,
          "0x0067e6f4 returns before the loop: no dispatch when the gate byte is zero");
    check(g_step_calls == 0,
          "0x00921580 is never called when the gate byte is zero");
    check(g_log.empty(),
          "no event at all when the gate byte is zero, for any caller argument");
    check(g_seen_receiver.empty(),
          "no dispatched receiver when the gate byte is zero");
  }
}

// The same gate byte, non-zero. This is the only difference from the check above
// and it is what makes the walk happen at all.
void test_gate_set_enters_the_walk() {
  Chain chain;
  build_chain(chain);
  chain.manager.gate_064 = 1;
  run(chain.manager, 0x00000001u);
  check(g_dispatch_calls == 3,
        "a non-zero gate byte is the whole precondition for the walk");
}

// 0x0067e6fe CMP ESI,EDI / 0x0067e700 JZ 0x0067e724. The head word is loaded
// once at 0x0067e6f7 and compared against the terminator ADDRESS before the
// EBX save, so an empty chain leaves without pushing anything and without
// calling either callee.
void test_empty_chain_exits_before_the_loop() {
  Chain chain;
  build_chain(chain);
  chain.manager.gate_064 = 1;
  chain.manager.head_050 = reinterpret_cast<FakeNode*>(g_terminator);
  run(chain.manager, 0x11223344u);
  check(g_dispatch_calls == 0,
        "0x0067e700 exits before the loop body: an empty chain dispatches nothing");
  check(g_step_calls == 0,
        "0x00921580 is not called for an empty chain");
  check(g_log.empty(), "an empty chain produces no events at all");
}

// 0x0067e712 CALL EDX then 0x0067e715 CALL 0x00921580, once per node, with the
// back edge at 0x0067e721 landing on 0x0067e707. One dispatch per node, in
// chain order, each followed by exactly one successor fetch.
void test_one_dispatch_and_one_step_per_node_in_order() {
  Chain chain;
  build_chain(chain);
  chain.manager.gate_064 = 1;
  run(chain.manager, 0x11223344u);
  check(g_dispatch_calls == 3, "one dispatch per node");
  check(g_step_calls == 3, "one successor fetch per node");
  check(g_seen_receiver.size() == 3u, "three dispatched receivers, in chain order");
  if (g_seen_receiver.size() == 3u) {
    check(is_address_of(g_seen_receiver[0], &chain.receivers[0]), "node 0 dispatches through its own receiver");
    check(is_address_of(g_seen_receiver[1], &chain.receivers[1]), "node 1 dispatches through its own receiver");
    check(is_address_of(g_seen_receiver[2], &chain.receivers[2]), "node 2 dispatches through its own receiver");
  }
  const EventLog expected = {"dispatch", "step", "dispatch", "step", "dispatch", "step"};
  check_log(expected,
            "0x0067e712/0x0067e715 interleave as dispatch,step,dispatch,step,dispatch,step");
}

// 0x0067e707 MOV ECX,dword ptr [ESI+0x10], 0x0067e70a MOV EAX,dword ptr [ECX]
// and 0x0067e70c MOV EDX,dword ptr [EAX+0x1c] all sit inside the loop body, so
// the per-node receiver, its table word and that table's +0x1c entry are loaded
// again on every iteration. Three tables holding three different entry stubs
// prove the reloading: a reconstruction that cached any of the three words would
// dispatch the wrong stub, or the wrong receiver, from the second node on.
//
// This check is about RELOADING, not about the depth of the load. The depth has
// its own check, test_dispatch_is_a_two_level_load, because a one-level read and
// a two-level read differ in which object the slot comes from, not in how often.
void test_node_receiver_and_table_entry_are_reloaded_per_iteration() {
  Chain chain;
  build_chain(chain);
  chain.manager.gate_064 = 1;
  run(chain.manager, 0x00000001u);
  check(g_seen_entry_id.size() == 3u, "one entry per node");
  if (g_seen_entry_id.size() == 3u) {
    check(g_seen_entry_id[0] == 0, "node 0 dispatched through its own table's +0x1c entry");
    check(g_seen_entry_id[1] == 1, "node 1 dispatched through its own table's +0x1c entry");
    check(g_seen_entry_id[2] == 2, "node 2 dispatched through its own table's +0x1c entry");
  }
  check(chain.tables[0].entry != chain.tables[1].entry,
        "the three tables really do hold three distinct words at +0x1c");
  check(chain.tables[1].entry != chain.tables[2].entry,
        "the three tables really do hold three distinct words at +0x1c");
}

// The dispatch is a TWO-LEVEL load, and this check names the level that a
// one-level read would lose. It is deliberately self-contained -- one node, one
// receiver, one table, wired by hand -- so that the two objects holding a word
// at displacement 0x1c are unambiguous and neither can be a side effect of the
// shared three-node chain.
//
//   0x0067e70a  MOV EAX,dword ptr [ECX]          level one: the receiver's first
//                                                 word, a TABLE POINTER
//   0x0067e70c  MOV EDX,dword ptr [EAX + 0x1c]   level two: the slot, read out of
//                                                 THAT pointer
//   0x0067e712  CALL EDX                        the call goes through level two
//
// The decoy sits at the receiver's OWN +0x1c: the same displacement, one level
// up, the word a one-level read would pick up. [ECX+0x1c] appears nowhere in the
// 26-instruction listing, so the decoy must never be called, while the table's
// +0x1c entry must be called exactly once with the receiver -- not the table --
// in ECX, because 0x0067e707 is what put the receiver there.
void test_dispatch_is_a_two_level_load() {
  FakeTable table{};
  FakeReceiver receiver{};
  FakeNode node{};
  FakeManager manager{};
  fill_bytes(table, 0xc3);
  fill_bytes(receiver, 0x3c);
  fill_bytes(node, 0x5a);
  fill_bytes(manager, 0xa5);

  table.entry = &entry_stub_a;                       // +0x1c on the TABLE
  receiver.table = &table;                           // +0x00 on the RECEIVER
  receiver.decoy_receiver_slot = &decoy_receiver_slot_stub;  // +0x1c on the RECEIVER
  node.receiver = &receiver;                         // +0x10 on the NODE
  manager.head_050 = &node;
  manager.gate_064 = 1;

  // The stepper has no edges, so it hands back the terminator and the single-node
  // chain ends after one iteration.
  g_manager = &manager;
  g_terminator = reinterpret_cast<OpaqueWord*>(&manager.terminator_04c);
  g_forced_next = nullptr;
  g_detach_on_first_dispatch = false;
  g_step_edges.clear();

  check(receiver.decoy_receiver_slot != table.entry,
        "the decoy at receiver+0x1c and the entry at table+0x1c are distinct words");
  check(reinterpret_cast<const unsigned char*>(&receiver) + kCallTableEntryOffset !=
            reinterpret_cast<const unsigned char*>(&table) + kCallTableEntryOffset,
        "the two +0x1c words live in two different objects, so only one can be read");

  run(manager, 0x00000001u);

  check(g_seen_entry_id.size() == 1u, "exactly one dispatch is made");
  check(!g_seen_entry_id.empty() && g_seen_entry_id[0] == 0,
        "0x0067e70c/0x0067e712 call the table's +0x1c entry, not the receiver's decoy");
  check(g_seen_receiver.size() == 1u && is_address_of(g_seen_receiver[0], &receiver),
        "0x0067e707 leaves the RECEIVER in ECX; the table pointer is not the callee's this");
  check(g_step_calls == 1, "the stepper runs once for the single node");
  const EventLog expected = {"dispatch", "step"};
  check_log(expected,
            "0x0067e712 reaches only the table's +0x1c entry: dispatch, then step");

  // Belt and braces: the decoy must be absent from the log under its own name,
  // so a future stub swap cannot hide it behind a count.
  bool decoy_seen = false;
  for (const char* event : g_log) {
    if (std::strcmp(event, "decoy_receiver_slot") == 0) {
      decoy_seen = true;
    }
  }
  check(!decoy_seen,
        "the decoy at receiver+0x1c is never called: [ECX+0x1c] is not in the listing");
}

// 0x0067e710 PUSH 0x1. The leading word is that literal, on every iteration, for
// every caller argument. The sibling entry 0x0067e730 pushes 0 from the same
// walk; that contrast is observed bytes, and what the leading word means is not
// established by either listing, so nothing is asserted about it.
void test_leading_word_is_the_literal_one() {
  Chain chain;
  build_chain(chain);
  chain.manager.gate_064 = 1;
  const OpaqueWord words[] = {0x00000000u, 0xffffffffu};
  for (OpaqueWord event_argument : words) {
    run(chain.manager, event_argument);
    check(g_seen_leading.size() == 3u, "one leading word per dispatch");
    for (int leading_word : g_seen_leading) {
      check(leading_word == 1, "0x0067e710 passes the literal 1 on every dispatch");
    }
  }
}

// 0x0067e702 PUSH EBX / 0x0067e703 MOV EBX,dword ptr [ESP+0x10] hoist the
// entry_ESP+0x4 word before the loop head, and 0x0067e70f PUSH EBX forwards
// that one word on every iteration, including the ones after two prior
// dispatches. The word's meaning is not established; only its identity is.
void test_event_argument_reaches_every_dispatch_unchanged() {
  Chain chain;
  build_chain(chain);
  chain.manager.gate_064 = 1;
  const OpaqueWord words[] = {0x00000000u, 0x00000001u, 0x7fffffffu,
                              0x80000000u, 0xffffffffu};
  for (OpaqueWord event_argument : words) {
    run(chain.manager, event_argument);
    check(g_seen_trailing.size() == 3u,
          "one trailing word per dispatch, for every swept argument");
    for (OpaqueWord seen : g_seen_trailing) {
      check(seen == event_argument,
            "0x0067e70f forwards the entry argument unchanged on every node");
    }
  }
}

// 0x0067e6fb LEA EDI,[ECX+0x4c] is address arithmetic, not a load: no
// instruction in the body reads the four bytes stored there. A garbage value at
// +0x4c must therefore leave the walk untouched, must never be dispatched
// through, and must come back unchanged.
void test_terminator_is_an_address_never_a_value() {
  Chain chain;
  build_chain(chain);
  chain.manager.gate_064 = 1;
  chain.manager.terminator_04c = 0xdeadbeefu;
  run(chain.manager, 0x00000001u);
  check(g_dispatch_calls == 3,
        "a garbage value at +0x4c does not shorten or lengthen the walk");
  check(g_step_calls == 3,
        "a garbage value at +0x4c does not change the number of successor fetches");
  for (OpaqueWord* receiver : g_seen_receiver) {
    check(receiver != g_terminator,
          "the word at +0x4c is never dispatched through: the marker is its address");
  }
  check(chain.manager.terminator_04c == 0xdeadbeefu,
        "the word at +0x4c is never written by the walk");
}

// The receiver is read at +0x64, +0x50 and address-taken at +0x4c, and no
// instruction in the 26 stores through any register, so every byte of it comes
// back as it was -- on the gated-off path and on the walking path.
void test_the_receiver_is_never_written() {
  Chain chain;
  build_chain(chain);
  unsigned char before[sizeof chain.manager];
  std::memcpy(before, &chain.manager, sizeof before);
  run(chain.manager, 0x00000001u);
  check(std::memcmp(before, &chain.manager, sizeof before) == 0,
        "no byte of the receiver is written when the gate byte is zero");

  chain.manager.gate_064 = 1;
  std::memcpy(before, &chain.manager, sizeof before);
  run(chain.manager, 0xffffffffu);
  check(std::memcmp(before, &chain.manager, sizeof before) == 0,
        "no byte of the receiver is written on the walking path");
}

// The same for everything the walk reaches: the chain nodes, the dispatched
// receivers and their tables are all held through pointers and all read only.
// A store that wrote back the value it had just read would leave the bytes
// identical and is not observable here; every store that changes a byte is.
void test_the_body_writes_nothing_beyond_the_receiver() {
  Chain chain;
  build_chain(chain);
  chain.manager.gate_064 = 1;
  unsigned char nodes_before[sizeof chain.nodes];
  unsigned char receivers_before[sizeof chain.receivers];
  unsigned char tables_before[sizeof chain.tables];
  std::memcpy(nodes_before, chain.nodes, sizeof nodes_before);
  std::memcpy(receivers_before, chain.receivers, sizeof receivers_before);
  std::memcpy(tables_before, chain.tables, sizeof tables_before);

  run(chain.manager, 0x00000001u);
  check(g_dispatch_calls == 3, "the walked chain is the three-node one");
  check(std::memcmp(nodes_before, chain.nodes, sizeof nodes_before) == 0,
        "no byte of any chain node is written");
  check(std::memcmp(receivers_before, chain.receivers, sizeof receivers_before) == 0,
        "no byte of any dispatched receiver is written");
  check(std::memcmp(tables_before, chain.tables, sizeof tables_before) == 0,
        "no byte of any call table is written");
}

// 0x0067e712 CALL EDX precedes 0x0067e714/0x0067e715, so the successor is
// fetched after the dispatch and a dispatch that severs the chain is observed by
// the same run: one node dispatched, one successor fetch, and the two following
// nodes never reached.
void test_successor_is_fetched_after_the_dispatch() {
  Chain chain;
  build_chain(chain);
  chain.manager.gate_064 = 1;
  g_detach_on_first_dispatch = true;
  run(chain.manager, 0x00000001u);
  check(g_dispatch_calls == 1,
        "a dispatch that detaches the chain is seen by the same run: only node 0 is dispatched");
  check(g_seen_receiver.size() == 1u, "only one receiver is dispatched");
  if (g_seen_receiver.size() == 1u) {
    check(is_address_of(g_seen_receiver[0], &chain.receivers[0]), "the node dispatched is the chain head's node");
  }
  check(g_step_calls == 1, "the stepper is still called once, after the dispatch");
  const EventLog expected = {"dispatch", "detach", "step"};
  check_log(expected,
            "0x0067e712 runs before 0x0067e715: dispatch, then the severed successor");
}

// Displacement pins restated at run time, so a header or body edit that keeps
// the source compiling still fails here. kNodeWordOffset and
// kCallTableEntryOffset come from the header; the three receiver displacements
// are spelled only in the body, so they are restated as constants above and
// checked here against the listing.
void test_displacement_pins() {
  check(kGateByteOffset == 0x64, "the gate byte is the one at receiver+0x64");
  check(kTerminatorOffset == 0x4c, "the terminator marker is the address of receiver+0x4c");
  check(kChainHeadOffset == 0x50, "the chain head word is at receiver+0x50");
  check(kNodeWordOffset == 0x10, "the per-node receiver word is at node+0x10");
  check(kReceiverTableOffset == 0x0,
        "0x0067e70a loads the receiver's first word, so the table word is at receiver+0x0");
  check(kCallTableEntryOffset == 0x1c, "the dispatch entry is at table+0x1c");
  check(sizeof(OpaqueWord) == 4, "an opaque word is one 32-bit machine word");
  check(sizeof(void*) == 4, "the target is 32-bit");
}

int run_tests() {
  test_displacement_pins();
  test_gate_clear_returns_immediately();
  test_gate_set_enters_the_walk();
  test_empty_chain_exits_before_the_loop();
  test_one_dispatch_and_one_step_per_node_in_order();
  test_node_receiver_and_table_entry_are_reloaded_per_iteration();
  test_dispatch_is_a_two_level_load();
  test_leading_word_is_the_literal_one();
  test_event_argument_reaches_every_dispatch_unchanged();
  test_terminator_is_an_address_never_a_value();
  test_the_receiver_is_never_written();
  test_the_body_writes_nothing_beyond_the_receiver();
  test_successor_is_fetched_after_the_dispatch();
  if (failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_cheat_dispatch_0067e6f0

int main() {
  return openspore::reconstruction::pkg_cheat_dispatch_0067e6f0::run_tests();
}
