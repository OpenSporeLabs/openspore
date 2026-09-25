#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

#include "diplomacy_transitions.hpp"

namespace openspore::reconstruction::pkg13_diplomacy_transitions {
namespace {

#if defined(_MSC_VER)
#define TEST_CDECL __cdecl
#define TEST_STDCALL __stdcall
#define TEST_THISCALL __thiscall
#else
#define TEST_CDECL __attribute__((cdecl))
#define TEST_STDCALL __attribute__((stdcall))
#define TEST_THISCALL __attribute__((thiscall))
#endif

std::vector<std::string> trace;
std::vector<std::string> pair_order;
OpaqueRelationshipManager manager{};
OpaqueTransitionRecord first_record{};
OpaqueTransitionRecord second_record{};
OpaqueTransitionRecord current_record{};
OpaqueRelationshipMap relationship_map{};
OpaqueRelationshipEntry relationship_entry{};
OpaqueEventFactory event_factory_object{};
OpaqueCurrentRoot current_root_object{};
OpaqueTransitionRecord* current_result = &current_record;
OpaqueTransitionRecord* event_second_result = &current_record;
OpaqueRelationshipEntry* lookup_result = &relationship_entry;
std::uint8_t predicate_result = 0;
OpaqueWord root_result = 0;
OpaqueWord root_followup_result = 0;
OpaqueCurrentRoot* current_root_result = &current_root_object;
OpaqueWord array_root_result = 0;
OpaqueWord array_lookup_result = 0;

void log_event(const char* value) { trace.emplace_back(value); }

const char* record_name(OpaqueTransitionRecord* record) {
  if (record == &first_record) {
    return "first";
  }
  if (record == &second_record) {
    return "second";
  }
  if (record == &current_record) {
    return "current";
  }
  return "unknown";
}

void record_pair(const char* name, OpaqueTransitionRecord* receiver,
                 OpaqueTransitionRecord* stack_arg) {
  log_event(name);
  assert(receiver != nullptr && stack_arg != nullptr);
  pair_order.emplace_back(std::string(record_name(receiver)) + ":" +
                          record_name(stack_arg));
}

OpaqueTransitionRecord* TEST_CDECL current_player() {
  log_event("current");
  return current_result;
}

OpaqueRelationshipMap* TEST_THISCALL select_map(OpaqueRelationshipManager*,
                                                OpaqueWord first_key,
                                                OpaqueWord second_key) {
  trace.push_back("select:" + std::to_string(first_key) + ":" +
                  std::to_string(second_key));
  return &relationship_map;
}

OpaqueRelationshipEntry* TEST_STDCALL lookup(OpaqueRelationshipMap*,
                                             OpaqueWord first_key,
                                             OpaqueWord second_key) {
  trace.push_back("lookup:" + std::to_string(first_key) + ":" +
                  std::to_string(second_key));
  return lookup_result;
}

std::uint8_t TEST_THISCALL predicate(OpaqueRelationshipManager*,
                                     OpaqueTransitionRecord*,
                                     OpaqueTransitionRecord*) {
  log_event("predicate");
  return predicate_result;
}

void TEST_THISCALL pair_c32830(OpaqueTransitionRecord* receiver,
                               OpaqueTransitionRecord* stack_arg) {
  record_pair("c32830", receiver, stack_arg);
}

void TEST_THISCALL pair_c327a0(OpaqueTransitionRecord* receiver,
                               OpaqueTransitionRecord* stack_arg) {
  record_pair("c327a0", receiver, stack_arg);
}

void TEST_THISCALL pair_c345f0(OpaqueTransitionRecord* receiver,
                               OpaqueTransitionRecord* stack_arg) {
  record_pair("c345f0", receiver, stack_arg);
}

void TEST_THISCALL pair_c34680(OpaqueTransitionRecord* receiver,
                               OpaqueTransitionRecord* stack_arg) {
  record_pair("c34680", receiver, stack_arg);
}

void TEST_THISCALL cleanup(OpaqueTransitionRecord* record) {
  log_event("cleanup");
  assert(record != nullptr);
}

OpaqueWord TEST_CDECL root(OpaqueTransitionRecord* record) {
  log_event("root");
  assert(record == &first_record);
  return root_result;
}

OpaqueWord TEST_THISCALL root_followup(OpaqueWord root) {
  log_event("root-followup");
  assert(root == root_result);
  return root_followup_result;
}

void TEST_THISCALL root_callback_c78450(OpaqueWord owner,
                                        OpaqueTransitionRecord* record) {
  log_event("root-callback-c78450");
  assert(owner == root_followup_result);
  assert(record == &first_record);
}

void TEST_THISCALL root_callback_c7bd40(OpaqueWord owner,
                                        OpaqueTransitionRecord* record) {
  log_event("root-callback-c7bd40");
  assert(owner == root_followup_result);
  assert(record == &first_record);
}

OpaqueEventFactory* TEST_CDECL event_factory_port() {
  log_event("event-factory");
  return &event_factory_object;
}

void TEST_THISCALL event_dispatch(OpaqueEventFactory* factory,
                                  OpaqueWord event_id, OpaqueEventRecord* event,
                                  OpaqueWord zero) {
  trace.push_back("event:" + std::to_string(event_id));
  assert(factory == &event_factory_object);
  assert(event != nullptr);
  assert(event->vtable == static_cast<void*>(&relationship_map));
  assert(event->zero == 0);
  assert(event->first == &first_record);
  assert(event->second == event_second_result);
  assert(event->cleanup_bitmask == 0);
  assert(zero == 0);
}

void TEST_THISCALL event_cleanup(OpaqueEventRecord* event) {
  log_event("event-cleanup");
  assert(event != nullptr);
  assert(event->vtable == static_cast<void*>(&relationship_map));
  assert(event->first == &first_record);
  assert(event->second == event_second_result);
  assert(event->cleanup_bitmask == 0);
}

void TEST_THISCALL apply(OpaqueRelationshipManager*, OpaqueRelationshipMap*,
                         OpaqueWord first_key, OpaqueWord second_key,
                         OpaqueWord selector, float value) {
  trace.push_back("apply:" + std::to_string(first_key) + ":" +
                  std::to_string(second_key) + ":" + std::to_string(selector) +
                  ":" + std::to_string(value));
}

OpaqueWord TEST_THISCALL array_root(OpaqueTransitionRecord* record) {
  log_event("array-root");
  assert(record == &first_record);
  return array_root_result;
}

OpaqueWord TEST_CDECL array_lookup(OpaqueWord selector, OpaqueWord object) {
  trace.push_back("array-lookup:" + std::to_string(selector) + ":" +
                  std::to_string(object));
  return array_lookup_result;
}

void TEST_THISCALL array_apply(OpaqueWord result, OpaqueWord selector,
                               OpaqueWord object) {
  assert(result == array_lookup_result);
  assert(selector == 0xc09edaacu);
  assert(object == array_root_result + 0x504u);
  trace.push_back("array-apply:" + std::to_string(result) + ":" +
                  std::to_string(selector) + ":" + std::to_string(object));
}

OpaqueCurrentRoot* TEST_CDECL current_root() {
  log_event("current-root");
  return current_root_result;
}

OpaqueWord TEST_THISCALL current_empire_key(OpaqueCurrentRoot* root) {
  log_event("current-empire-key");
  assert(root == &current_root_object);
  return root->empire_key;
}

void TEST_THISCALL post_transition(OpaqueRelationshipManager*, OpaqueWord key,
                                   OpaqueWord selector, float value) {
  trace.push_back("post:" + std::to_string(key) + ":" +
                  std::to_string(selector) + ":" + std::to_string(value));
}

void reset() {
  trace.clear();
  pair_order.clear();
  first_record = OpaqueTransitionRecord{};
  second_record = OpaqueTransitionRecord{};
  current_record = OpaqueTransitionRecord{};
  first_record.key = 1;
  second_record.key = 2;
  current_record.key = 1;
  relationship_entry.flags = 3;
  current_result = &current_record;
  event_second_result = &current_record;
  lookup_result = &relationship_entry;
  predicate_result = 0;
  root_result = 7;
  root_followup_result = 8;
  current_root_result = &current_root_object;
  current_root_object = OpaqueCurrentRoot{};
  current_root_object.empire_key = 1;
  array_root_result = 10;
  array_lookup_result = 11;
  auto& ports = diplomacy_transition_ports();
  ports.current_player = current_player;
  ports.select_map = select_map;
  ports.lookup = lookup;
  ports.transition_predicate = predicate;
  ports.pair_c32830 = pair_c32830;
  ports.pair_c327a0 = pair_c327a0;
  ports.pair_c345f0 = pair_c345f0;
  ports.pair_c34680 = pair_c34680;
  ports.cleanup = cleanup;
  ports.root = root;
  ports.root_followup = root_followup;
  ports.root_callback_c78450 = root_callback_c78450;
  ports.root_callback_c7bd40 = root_callback_c7bd40;
  ports.event_factory = event_factory_port;
  ports.event_dispatch = event_dispatch;
  ports.event_cleanup = event_cleanup;
  ports.apply_transition = apply;
  ports.array_root = array_root;
  ports.array_lookup = array_lookup;
  ports.array_apply = array_apply;
  ports.current_root = current_root;
  ports.current_empire_key = current_empire_key;
  ports.post_transition = post_transition;
  ports.event_vtable = &relationship_map;
}

void test_d01e30_null_rhs_uses_current_and_event() {
  reset();
  DiplomacyTransition_00d01e30(&manager, &first_record, nullptr);
  assert(trace.size() == 10);
  assert(trace[0] == "current");
  assert(trace[1] == "select:1:1");
  assert(trace[2] == "lookup:1:1");
  assert(trace[3] == "c32830");
  assert(trace[4] == "c32830");
  assert(trace[5] == "event-factory");
  assert(trace[6] == "event:71589188");
  assert(trace[7] == "event-cleanup");
  assert(trace[8] == "cleanup");
  assert(trace[9] == "cleanup");
  assert(pair_order.size() == 2);
  assert(pair_order[0] == "first:current");
  assert(pair_order[1] == "current:first");
  assert(relationship_entry.flags == 1);
}

void test_d01e30_distinct_reverse_branch() {
  reset();
  current_result = &first_record;
  DiplomacyTransition_00d01e30(&manager, &first_record, &second_record);
  assert(trace.size() == 9);
  assert(trace[1] == "select:1:2");
  assert(trace[2] == "lookup:1:2");
  assert(trace[3] == "select:2:1");
  assert(trace[4] == "lookup:2:1");
  assert(trace[5] == "c32830");
  assert(trace[6] == "c32830");
  assert(trace[7] == "cleanup");
  assert(trace[8] == "cleanup");
  assert(pair_order.size() == 2);
  assert(pair_order[0] == "first:second");
  assert(pair_order[1] == "second:first");
}

void test_d038e0_predicate_false_cleanup_only() {
  reset();
  current_result = &first_record;
  DiplomacyTransition_00d038e0(&manager, &first_record, &second_record);
  assert(trace.size() == 4);
  assert(trace[0] == "current");
  assert(trace[1] == "predicate");
  assert(trace[2] == "cleanup");
  assert(trace[3] == "cleanup");
}

void test_d038e0_predicate_true_distinct_and_null_lookup() {
  reset();
  current_result = &first_record;
  predicate_result = 1;
  lookup_result = nullptr;
  DiplomacyTransition_00d038e0(&manager, &first_record, &second_record);
  assert(trace.size() == 10);
  assert(trace[2] == "select:1:2");
  assert(trace[3] == "lookup:1:2");
  assert(trace[4] == "select:2:1");
  assert(trace[5] == "lookup:2:1");
  assert(trace[6] == "c327a0");
  assert(trace[7] == "c327a0");
  assert(trace[8] == "cleanup");
  assert(trace[9] == "cleanup");
  assert(pair_order.size() == 2);
  assert(pair_order[0] == "first:second");
  assert(pair_order[1] == "second:first");
}

void test_d065a0_predicate_true_returns() {
  reset();
  predicate_result = 1;
  DiplomacyTransition_00d065a0(&manager, &first_record, &second_record);
  assert(trace.size() == 2);
  assert(trace[0] == "current");
  assert(trace[1] == "predicate");
}

void test_d065a0_false_distinct_applies_both_directions() {
  reset();
  current_result = &first_record;
  DiplomacyTransition_00d065a0(&manager, &first_record, &second_record);
  assert(trace.size() == 19);
  assert(trace[1] == "predicate");
  assert(trace[2] == "select:1:2");
  assert(trace[3] == "lookup:1:2");
  assert(trace[4] == "lookup:1:2");
  assert(trace[5] == "select:2:1");
  assert(trace[6] == "lookup:2:1");
  assert(trace[7] == "lookup:2:1");
  assert(trace[8] == "c345f0");
  assert(trace[9] == "c345f0");
  assert(trace[10] == "cleanup");
  assert(trace[11] == "cleanup");
  assert(trace[12] == "select:2:1");
  assert(trace[13] == "apply:2:1:100180397:1.000000");
  assert(trace[14] == "array-root");
  assert(trace[15] == "array-lookup:3231636140:1294");
  assert(trace[16] == "array-apply:11:3231636140:1294");
  assert(trace[17] == "select:1:2");
  assert(trace[18] == "apply:1:2:100180397:1.000000");
  assert(pair_order.size() == 2);
  assert(pair_order[0] == "first:second");
  assert(pair_order[1] == "second:first");
}

void test_d065a0_current_branch_and_array_ports() {
  reset();
  predicate_result = 0;
  current_result = &first_record;
  DiplomacyTransition_00d065a0(&manager, &first_record, nullptr);
  assert(trace.size() == 17);
  assert(trace[5] == "c345f0");
  assert(trace[6] == "c345f0");
  assert(trace[7] == "cleanup");
  assert(trace[8] == "cleanup");
  assert(trace[9] == "root");
  assert(trace[10] == "root-followup");
  assert(trace[11] == "root-callback-c7bd40");
  assert(trace[12] == "array-root");
  assert(trace[13] == "array-lookup:3231636140:1294");
  assert(trace[14] == "array-apply:11:3231636140:1294");
  assert(trace[15] == "select:1:1");
  assert(trace[16] == "apply:1:1:100180397:1.000000");
  assert(pair_order.size() == 2);
  assert(pair_order[0] == "first:first");
  assert(pair_order[1] == "first:first");
}

void test_d06920_nested_transition_and_post_callback() {
  reset();
  current_result = &first_record;
  predicate_result = 1;
  DiplomacyTransition_00d06920(&manager, &first_record, &second_record);
  assert(trace.size() == 22);
  assert(trace[0] == "current");
  assert(trace[1] == "current");
  assert(trace[2] == "predicate");
  assert(trace[3] == "select:1:2");
  assert(trace[4] == "lookup:1:2");
  assert(trace[5] == "select:2:1");
  assert(trace[6] == "lookup:2:1");
  assert(trace[7] == "c327a0");
  assert(trace[8] == "c327a0");
  assert(trace[9] == "cleanup");
  assert(trace[10] == "cleanup");
  assert(trace[11] == "select:1:2");
  assert(trace[12] == "lookup:1:2");
  assert(trace[13] == "select:2:1");
  assert(trace[14] == "lookup:2:1");
  assert(trace[15] == "c34680");
  assert(trace[16] == "c34680");
  assert(trace[17] == "cleanup");
  assert(trace[18] == "cleanup");
  assert(trace[19] == "current-root");
  assert(trace[20] == "current-empire-key");
  assert(trace[21] == "post:1:109783352:1.000000");
  assert(pair_order.size() == 4);
  assert(pair_order[0] == "first:second");
  assert(pair_order[1] == "second:first");
  assert(pair_order[2] == "first:second");
  assert(pair_order[3] == "second:first");
}

void test_d06920_same_current_event_path() {
  reset();
  current_result = &first_record;
  event_second_result = &first_record;
  predicate_result = 1;
  DiplomacyTransition_00d06920(&manager, &first_record, nullptr);
  assert(trace.size() == 24);
  assert(trace[7] == "root");
  assert(trace[8] == "root-followup");
  assert(trace[9] == "root-callback-c78450");
  assert(trace[16] == "event-factory");
  assert(trace[17] == "event:71589187");
  assert(trace[18] == "event-cleanup");
  assert(trace[19] == "cleanup");
  assert(trace[20] == "cleanup");
  assert(trace[21] == "current-root");
  assert(trace[22] == "current-empire-key");
  assert(trace[23] == "post:1:109783352:1.000000");
  assert(pair_order.size() == 4);
  assert(pair_order[0] == "first:first");
  assert(pair_order[1] == "first:first");
  assert(pair_order[2] == "first:first");
  assert(pair_order[3] == "first:first");
}

}

}

using namespace openspore::reconstruction::pkg13_diplomacy_transitions;

int main() {
  test_d01e30_null_rhs_uses_current_and_event();
  test_d01e30_distinct_reverse_branch();
  test_d038e0_predicate_false_cleanup_only();
  test_d038e0_predicate_true_distinct_and_null_lookup();
  test_d065a0_predicate_true_returns();
  test_d065a0_false_distinct_applies_both_directions();
  test_d065a0_current_branch_and_array_ports();
  test_d06920_nested_transition_and_post_callback();
  test_d06920_same_current_event_path();
}
