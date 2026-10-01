// Focused semantic test for the 0x0067e730 reconstruction.
//
// What is testable, and what is not. The observable behaviour of this body is
// the chain walk and the argument shape of the one indirect call it makes per
// node. Those are what this file checks. What it cannot check is what the
// dispatch entry at +0x1C does, what the argument word means, what 0x00921580
// does inside, and which concrete function the +0x1C slot holds at runtime: the
// listing fixes none of them, and this test asserts none of them. Both callees
// are substituted through the port table, so the test proves the traversal and
// the call shape, not the callees.

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "cheat_dispatch_func44h_0067e730.hpp"

#if defined(_MSC_VER)
#define TEST44_THISCALL __thiscall
#define TEST44_CDECL __cdecl
#else
#define TEST44_THISCALL __attribute__((thiscall))
#define TEST44_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::cheat_func44h_0067e730 {
namespace {

using namespace openspore::reconstruction::cheat_func44h_0067e730;

std::vector<std::string>* events = nullptr;
std::vector<std::string> last_log;
std::vector<int> seen_leading;
std::vector<OpaqueWord> seen_trailing;
std::vector<void*> seen_receiver;
OpaqueWord* forced_next = nullptr;
int step_calls = 0;
int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void record(const char* name) { events->push_back(name); }

// Stand-ins for objects the body only ever holds through a pointer. Each one
// mirrors exactly the displacements the listing reads, and nothing else.
struct FakeTable {
  OpaqueWord prefix[7]{};
  DispatchEntry entry = nullptr;
};

struct FakeReceiver {
  FakeTable* table = nullptr;
};

struct FakeNode {
  OpaqueWord prefix[4]{};
  FakeReceiver* receiver = nullptr;
};

struct FakeManager {
  OpaqueWord prefix[19]{};       // +0x00 .. +0x4B
  OpaqueWord terminator_04c{};   // +0x4C, address-taken, never loaded
  FakeNode* head_050 = nullptr;  // +0x50, the chain head
};

// The layouts above must place the fields where the listing reads them, or the
// test would be exercising a different object graph than the binary's.
static_assert(offsetof(FakeManager, terminator_04c) == kManagerTerminatorOffset,
              "the terminator word must sit at manager+0x4C");
static_assert(offsetof(FakeManager, head_050) == kManagerHeadOffset,
              "the chain head word must sit at manager+0x50");
static_assert(offsetof(FakeNode, receiver) == kNodeReceiverOffset,
              "the per-node receiver word must sit at node+0x10");
static_assert(offsetof(FakeReceiver, table) == kReceiverTableOffset,
              "the receiver's table word must be its first word");
static_assert(offsetof(FakeTable, entry) == kTableEntryOffset,
              "the dispatch entry must sit at table+0x1C");

void TEST44_THISCALL dispatch_stub(OpaqueWord* receiver, int leading_word,
                                   OpaqueWord event_argument) {
  seen_receiver.push_back(receiver);
  seen_leading.push_back(leading_word);
  seen_trailing.push_back(event_argument);
  record("dispatch");
}

void TEST44_THISCALL other_dispatch_stub(OpaqueWord* receiver,
                                         int leading_word,
                                         OpaqueWord event_argument) {
  seen_receiver.push_back(receiver);
  seen_leading.push_back(leading_word);
  seen_trailing.push_back(event_argument);
  record("other_dispatch");
}

struct StepEdge {
  OpaqueWord* from;
  OpaqueWord* to;
};

std::vector<StepEdge> step_edges;
OpaqueWord* terminator = nullptr;

// 0x00921580 is cdecl: it takes the node and returns the word the body moves
// into ESI. The stub reproduces only that contract.
OpaqueWord* TEST44_CDECL step_stub(OpaqueWord* node) {
  record("step");
  ++step_calls;
  if (forced_next != nullptr && step_calls == 1) {
    return forced_next;
  }
  for (const StepEdge& edge : step_edges) {
    if (edge.from == node) {
      return edge.to;
    }
  }
  return terminator;
}

Ports make_ports() {
  Ports ports;
  ports.next_00921580 = &step_stub;
  return ports;
}

// One run of the entry over a freshly built chain, with a fresh event log.
void run(FakeManager& manager, OpaqueWord event) {
  std::vector<std::string> log;
  events = &log;
  seen_leading.clear();
  seen_trailing.clear();
  seen_receiver.clear();
  step_calls = 0;

  Ports ports = make_ports();
  g_cheat_func44h_ports = &ports;
  func44h_0067e730(reinterpret_cast<OpaqueWord*>(&manager), event);
  g_cheat_func44h_ports = nullptr;

  events = nullptr;
  last_log = log;
}

struct Chain {
  FakeManager manager{};
  FakeNode nodes[3]{};
  FakeReceiver receivers[3]{};
  FakeTable tables[3]{};
};

// Builds a manager whose head is nodes[0] and whose stepper walks 0 -> 1 -> 2
// -> terminator, each node dispatching through its own table.
Chain make_chain() {
  Chain chain;
  terminator = chain_terminator(reinterpret_cast<OpaqueWord*>(&chain.manager));
  step_edges.clear();
  forced_next = nullptr;
  for (int i = 0; i < 3; ++i) {
    chain.tables[i].entry = &dispatch_stub;
    chain.receivers[i].table = &chain.tables[i];
    chain.nodes[i].receiver = &chain.receivers[i];
  }
  // The second node dispatches through a different table with a different
  // entry, so the test can show the table word is reloaded per iteration.
  chain.tables[1].entry = &other_dispatch_stub;
  step_edges.push_back({reinterpret_cast<OpaqueWord*>(&chain.nodes[0]),
                        reinterpret_cast<OpaqueWord*>(&chain.nodes[1])});
  step_edges.push_back({reinterpret_cast<OpaqueWord*>(&chain.nodes[1]),
                        reinterpret_cast<OpaqueWord*>(&chain.nodes[2])});
  step_edges.push_back({reinterpret_cast<OpaqueWord*>(&chain.nodes[2]),
                        terminator});
  chain.manager.head_050 = &chain.nodes[0];
  return chain;
}

// 0x0067e738/0x0067e73a: with the head equal to the terminator address the body
// leaves before the loop, so no node is dispatched and the stepper is never
// called. Nothing dereferences the head in that case.
void test_empty_chain_dispatches_nothing() {
  Chain chain = make_chain();
  chain.manager.head_050 =
      reinterpret_cast<FakeNode*>(terminator);
  run(chain.manager, 0x11223344u);
  check(last_log.empty());
  check(step_calls == 0);
  check(seen_receiver.empty());
}

// 0x0067e741..0x0067e75b: one dispatch per node, in chain order, each followed
// by exactly one successor fetch.
void test_every_node_is_dispatched_once_in_order() {
  Chain chain = make_chain();
  run(chain.manager, 0x11223344u);
  check(seen_receiver.size() == 3u);
  if (seen_receiver.size() == 3u) {
    check(seen_receiver[0] == &chain.receivers[0]);
    check(seen_receiver[1] == &chain.receivers[1]);
    check(seen_receiver[2] == &chain.receivers[2]);
  }
  check(last_log.size() == 6u);
  if (last_log.size() == 6u) {
    check(last_log[0] == "dispatch");
    check(last_log[1] == "step");
    check(last_log[2] == "other_dispatch");
    check(last_log[3] == "step");
    check(last_log[4] == "dispatch");
    check(last_log[5] == "step");
  }
  check(step_calls == 3);
}

// The receiver's table word and its +0x1C entry are loaded fresh on every
// iteration (0x0067e744/0x0067e746 are inside the loop), so consecutive nodes
// may dispatch through different entries. The mixed log above already shows the
// second node using other_dispatch_stub; this pins the count per entry.
void test_table_is_reloaded_per_node() {
  Chain chain = make_chain();
  run(chain.manager, 0x00000001u);
  int dispatch_events = 0;
  int other_events = 0;
  for (const std::string& name : last_log) {
    if (name == "dispatch") {
      ++dispatch_events;
    } else if (name == "other_dispatch") {
      ++other_events;
    }
  }
  check(dispatch_events == 2);
  check(other_events == 1);
}

// 0x0067e74a pushes the literal zero. The sibling entry 0x0067e6f0 pushes one
// from the same walk, so a non-zero leading word here would mean the two bodies
// had been confused.
void test_leading_word_is_literal_zero() {
  Chain chain = make_chain();
  run(chain.manager, 0xffffffffu);
  check(seen_leading.size() == 3u);
  for (int leading : seen_leading) {
    check(leading == 0);
  }
  check(kLeadingWord == 0u);
}

// 0x0067e73d hoists entry_ESP+0x4 into EBX before the loop head; every
// iteration must therefore pass that one word through unchanged, including the
// iterations that run after two prior dispatches.
void test_event_argument_reaches_every_dispatch() {
  const OpaqueWord words[] = {0x00000000u, 0x00000001u, 0x7fffffffu,
                              0x80000000u, 0xffffffffu};
  for (OpaqueWord word : words) {
    Chain chain = make_chain();
    run(chain.manager, word);
    check(seen_trailing.size() == 3u);
    for (OpaqueWord seen : seen_trailing) {
      check(seen == word);
    }
  }
}

// The successor is fetched AFTER the dispatch (0x0067e74c then 0x0067e74f), so
// a dispatch that unlinks the rest of the chain is observed by the same run:
// the second node is never reached. This is the ordering the listing fixes and
// the reason the argument hoist is not the only hoisted thing.
void test_successor_is_fetched_after_the_dispatch() {
  Chain chain = make_chain();
  forced_next = terminator;
  run(chain.manager, 0x00000001u);
  check(seen_receiver.size() == 1u);
  if (seen_receiver.size() == 1u) {
    check(seen_receiver[0] == &chain.receivers[0]);
  }
  check(step_calls == 1);
}

// The terminator is the ADDRESS of the manager word at +0x4C, so its stored
// value is inert: a garbage value there must neither be dispatched through nor
// end the walk early, and the walk still stops on the address.
void test_terminator_is_an_address_not_a_value() {
  Chain chain = make_chain();
  chain.manager.terminator_04c = 0xdeadbeefu;
  run(chain.manager, 0x00000001u);
  check(seen_receiver.size() == 3u);
  check(step_calls == 3);
  for (void* receiver : seen_receiver) {
    check(reinterpret_cast<OpaqueWord*>(receiver) != terminator);
  }
}

// The stepper's return value is what the bottom test compares, so a chain that
// points at the terminator one step early simply ends; nothing else terminates
// the loop.
void test_loop_stops_only_on_the_terminator_address() {
  Chain chain = make_chain();
  step_edges.clear();
  step_edges.push_back({reinterpret_cast<OpaqueWord*>(&chain.nodes[0]),
                        terminator});
  run(chain.manager, 0x00000001u);
  check(seen_receiver.size() == 1u);
  check(step_calls == 1);
}

// Displacement pins, restated at run time so a header edit that keeps the
// source compiling still fails the test.
void test_displacements() {
  check(kManagerTerminatorOffset == 0x4c);
  check(kManagerHeadOffset == 0x50);
  check(kNodeReceiverOffset == 0x10);
  check(kReceiverTableOffset == 0x0);
  check(kTableEntryOffset == 0x1c);
  check(sizeof(OpaqueWord) == 4);
  check(sizeof(void*) == 4);
}

int run_tests() {
  test_displacements();
  test_empty_chain_dispatches_nothing();
  test_every_node_is_dispatched_once_in_order();
  test_table_is_reloaded_per_node();
  test_leading_word_is_literal_zero();
  test_event_argument_reaches_every_dispatch();
  test_successor_is_fetched_after_the_dispatch();
  test_terminator_is_an_address_not_a_value();
  test_loop_stops_only_on_the_terminator_address();
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::cheat_func44h_0067e730::
      run_tests();
}

#undef TEST44_CDECL
#undef TEST44_THISCALL
