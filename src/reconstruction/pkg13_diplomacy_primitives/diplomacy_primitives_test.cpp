#include "diplomacy_primitives.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace {

using openspore::reconstruction::pkg13_diplomacy_primitives::
    RelationshipLookup_00d01410;
using openspore::reconstruction::pkg13_diplomacy_primitives::
    RelationshipMapSelect_00d01ab0;

struct ObservedMap {
  unsigned char bytes[0x10];
};

struct ObservedNode {
  unsigned char bytes[0x20];
};

struct ObservedRecord {
  std::uint32_t key;
  unsigned char bytes[0x1c];
};

struct ObservedContext {
  std::uint32_t context_word;
};

struct ObservedManager {
  unsigned char bytes[0xb4];
};

static_assert(sizeof(ObservedRecord) == 0x20, "observed selector stride");

ObservedMap map{};
ObservedNode node{};
ObservedRecord records[2]{};
ObservedContext context{0};
ObservedManager manager{};
OpaqueRelationshipNode* selected_node = nullptr;
OpaqueRelationshipRecord* selected_candidate = nullptr;
OpaqueSpaceContext* selected_context =
    reinterpret_cast<OpaqueSpaceContext*>(&context);
bool swap_keys = false;
int normalize_calls = 0;
int selector_calls = 0;
int context_calls = 0;
int high_bit_calls = 0;
std::uint32_t selected_key_a = 0U;
std::uint32_t selected_key_b = 0U;
std::uint32_t selected_context_key = 0U;
std::uint32_t selected_ignored_word = 0U;
OpaqueRelationshipMap* selected_begin = nullptr;
OpaqueRelationshipMap* selected_end = nullptr;

namespace openspore::reconstruction::pkg13_diplomacy_primitives {

extern "C" void PKG13_PRIM_CDECL
pkg13_unresolved_00d009a0(std::uint32_t* key_a, std::uint32_t* key_b) {
  ++normalize_calls;
  if (swap_keys) {
    const std::uint32_t temporary = *key_a;
    *key_a = *key_b;
    *key_b = temporary;
  }
}

extern "C" void PKG13_PRIM_THISCALL pkg13_unresolved_00d00f80(
    OpaqueRelationshipMap* receiver, OpaqueRelationshipNode** output,
    std::uint32_t* key_pair) {
  assert(receiver == reinterpret_cast<OpaqueRelationshipMap*>(&map));
  selected_key_a = key_pair[0];
  selected_key_b = key_pair[1];
  *output = selected_node;
}

extern "C" OpaqueSpaceContext* PKG13_PRIM_CDECL pkg13_unresolved_010212a0() {
  ++context_calls;
  return selected_context;
}

extern "C" std::uint32_t PKG13_PRIM_CDECL
pkg13_unresolved_00ba6650(std::uint32_t value) {
  ++high_bit_calls;
  return value >> 31U;
}

extern "C" std::uint32_t PKG13_PRIM_FASTCALL
pkg13_unresolved_00ce6950(OpaqueSpaceContext* receiver) {
  assert(receiver == reinterpret_cast<OpaqueSpaceContext*>(&context));
  return context.context_word;
}

extern "C" OpaqueRelationshipRecord* PKG13_PRIM_CDECL pkg13_unresolved_00d01210(
    OpaqueRelationshipRecord* begin, OpaqueRelationshipRecord* end,
    std::uint32_t* key, std::uint32_t ignored_word) {
  ++selector_calls;
  selected_begin = reinterpret_cast<OpaqueRelationshipMap*>(begin);
  selected_end = reinterpret_cast<OpaqueRelationshipMap*>(end);
  selected_context_key = *key;
  selected_ignored_word = ignored_word;
  return selected_candidate;
}

}  // namespace openspore::reconstruction::pkg13_diplomacy_primitives

void ResetObservation() {
  std::memset(&map, 0, sizeof(map));
  std::memset(&node, 0, sizeof(node));
  std::memset(records, 0, sizeof(records));
  std::memset(&context, 0, sizeof(context));
  std::memset(&manager, 0, sizeof(manager));
  selected_node = nullptr;
  selected_candidate = nullptr;
  selected_context = reinterpret_cast<OpaqueSpaceContext*>(&context);
  swap_keys = false;
  normalize_calls = 0;
  selector_calls = 0;
  context_calls = 0;
  high_bit_calls = 0;
  selected_key_a = 0U;
  selected_key_b = 0U;
  selected_context_key = 0U;
  selected_ignored_word = 0U;
  selected_begin = nullptr;
  selected_end = nullptr;
  records[0].key = 10U;
  records[1].key = 20U;
  const auto begin = reinterpret_cast<std::uintptr_t>(&records[0]);
  const auto end = reinterpret_cast<std::uintptr_t>(&records[2]);
  std::memcpy(manager.bytes + 0x9c, &begin, sizeof(begin));
  std::memcpy(manager.bytes + 0xa0, &end, sizeof(end));
  manager.bytes[0xb0] = 0x7dU;
}

void TestRelationshipLookupSentinelAndPayload() {
  ResetObservation();
  const auto sentinel = reinterpret_cast<OpaqueRelationshipNode*>(
      reinterpret_cast<unsigned char*>(&map) + 0x04U);
  selected_node = sentinel;
  assert(RelationshipLookup_00d01410(
             reinterpret_cast<OpaqueRelationshipMap*>(&map), 4U, 9U) ==
         nullptr);
  assert(normalize_calls == 1);
  assert(selected_key_a == 4U);
  assert(selected_key_b == 9U);

  ResetObservation();
  swap_keys = true;
  selected_node = sentinel;
  RelationshipLookup_00d01410(reinterpret_cast<OpaqueRelationshipMap*>(&map),
                              4U, 9U);
  assert(selected_key_a == 9U);
  assert(selected_key_b == 4U);

  ResetObservation();
  selected_node = reinterpret_cast<OpaqueRelationshipNode*>(&node);
  OpaqueRelationshipEntry* result = RelationshipLookup_00d01410(
      reinterpret_cast<OpaqueRelationshipMap*>(&map), 4U, 9U);
  assert(result == reinterpret_cast<OpaqueRelationshipEntry*>(
                       reinterpret_cast<unsigned char*>(&node) + 0x18U));
}

void TestMapSelectionFallbacksAndSelection() {
  ResetObservation();
  auto* receiver = reinterpret_cast<OpaqueRelationshipManager*>(&manager);
  auto* fallback = reinterpret_cast<OpaqueRelationshipMap*>(
      reinterpret_cast<unsigned char*>(&manager) + 0x24U);
  selected_candidate = reinterpret_cast<OpaqueRelationshipRecord*>(&records[2]);
  assert(RelationshipMapSelect_00d01ab0(receiver, 1U, 2U) == fallback);
  assert(context_calls == 1);
  assert(selector_calls == 1);

  ResetObservation();
  selected_candidate = reinterpret_cast<OpaqueRelationshipRecord*>(&records[2]);
  assert(RelationshipMapSelect_00d01ab0(receiver, 0x80000000U, 0x80000001U) ==
         fallback);
  assert(selector_calls == 0);

  ResetObservation();
  context.context_word = 25U;
  selected_candidate = reinterpret_cast<OpaqueRelationshipRecord*>(&records[1]);
  assert(RelationshipMapSelect_00d01ab0(receiver, 1U, 2U) ==
         reinterpret_cast<OpaqueRelationshipMap*>(
             reinterpret_cast<unsigned char*>(&records[1]) + 0x04U));
  assert(selector_calls == 1);
  assert(selected_begin ==
         reinterpret_cast<OpaqueRelationshipMap*>(&records[0]));
  assert(selected_end == reinterpret_cast<OpaqueRelationshipMap*>(&records[2]));
  assert(selected_context_key == 25U);
  assert(selected_ignored_word == 0x7dU);

  ResetObservation();
  context.context_word = 5U;
  selected_candidate = reinterpret_cast<OpaqueRelationshipRecord*>(&records[1]);
  assert(RelationshipMapSelect_00d01ab0(receiver, 1U, 2U) == fallback);

  ResetObservation();
  selected_context = nullptr;
  assert(RelationshipMapSelect_00d01ab0(receiver, 1U, 2U) == fallback);
  assert(context_calls == 1);
  assert(selector_calls == 0);
}

void TestSelectorNormalizationAndPartialHighBits() {
  ResetObservation();
  context.context_word = 25U;
  selected_candidate = reinterpret_cast<OpaqueRelationshipRecord*>(&records[1]);
  swap_keys = true;
  assert(RelationshipMapSelect_00d01ab0(
             reinterpret_cast<OpaqueRelationshipManager*>(&manager),
             0x80000000U, 1U) ==
         reinterpret_cast<OpaqueRelationshipMap*>(
             reinterpret_cast<unsigned char*>(&records[1]) + 0x04U));
  assert(selector_calls == 1);

  ResetObservation();
  context.context_word = 25U;
  selected_candidate = reinterpret_cast<OpaqueRelationshipRecord*>(&records[1]);
  assert(RelationshipMapSelect_00d01ab0(
             reinterpret_cast<OpaqueRelationshipManager*>(&manager), 1U,
             0x80000000U) !=
         reinterpret_cast<OpaqueRelationshipMap*>(manager.bytes + 0x24U));
  assert(selector_calls == 1);
}

}  // namespace

int main() {
  TestRelationshipLookupSentinelAndPayload();
  TestMapSelectionFallbacksAndSelection();
  TestSelectorNormalizationAndPartialHighBits();
}
