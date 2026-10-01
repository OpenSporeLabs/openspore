// PKG-APP-PROLIST-WAVE13 -- model test for VA 0x006a2f10,
// App::PropertyList::AddPropertiesFrom.
//
// The two callees are machine-observed but semantically unresolved, so this
// test supplies recording stubs with the observed calling surfaces (one stack
// dword each, receiver in ECX) and checks only what 0x006a2f10 itself does.
//
// The machine body, 30 instructions:
//
//   006a2f10  MOV EAX,[ESP+0x4]     the one stack dword, `other`
//   006a2f15  MOV EBP,ECX           the receiver alias (EBP is general here)
//   006a2f17  CMP EBP,EAX / JZ      self-copy refused, bare return
//   006a2f1c  MOV ESI,[EAX+0x18]    the ARGUMENT's range begin
//   006a2f20  MOV EDI,[EAX+0x1c]    the ARGUMENT's range end
//   006a2f28  LEA EBX,[EBP+0x18]    the RECEIVER's storage address, held in a
//                                   register for the whole loop
//   006a2f30  LEA EAX,[ESI+0x4]     element+0x4, the second word of the call
//   006a2f37  CALL 0x006a2d30      pops one word (RET 0x4), returns a pointer
//   006a2f3c  MOV ECX,EAX          that result becomes the next receiver
//   006a2f3e  CALL 0x00542b80      pops the word 0x006a2d30 left behind
//   006a2f43  ADD ESI,0x18         the element stride
//   006a2f4b  INC dword ptr [EBP+0x34]   the receiver's completion word
//   006a2f51  RET 0x4              the callee pops `other`
//
// Every test below attacks a reading the listing permits but the reconstruction
// could get wrong:
//
//   * field vs other-object field -- 0x18 and 0x1c are read from the ARGUMENT
//     while 0x18 is ALSO the receiver's storage address handed to the callee, and
//     0x34 is written on the RECEIVER. Two objects with different content at
//     every one of those offsets separate the two.
//   * pointer identity vs content equality -- the guard is CMP EBP,EAX, an exact
//     pointer comparison. Two distinct lists holding identical range words must
//     still copy.
//   * the loop's shape -- the full ordered sequence of (element, element+0x4)
//     pairs is recorded, which pins the 0x18 stride, the iteration count, the
//     argument order, and the fact that the second callee receives the element
//     pointer the first call left on the stack.
//   * the completion word -- exactly one increment per call that gets past the
//     self-copy guard, including the empty-range call, and never on the
//     argument.
//   * no incidental writes -- both objects are compared byte for byte after
//     every call; only the receiver's word at +0x34 may differ.
//   * return semantics not over-claimed -- the declared result is void, and the
//     test pins that. It does NOT assert anything about EAX on exit: on the
//     loop path EAX holds 0x00542b80's result and on the early-exit path it
//     holds the incoming stack word, so no single value is the "returned" one.
//   * the calling convention -- the declared contract (receiver in ECX, one
//     callee-popped stack word) is pinned at the type level and exercised
//     through a pointer of that type. A runtime stack-drift measurement was
//     tried and dropped: on i386-ELF the compiler reserves the outgoing
//     argument area itself, so the caller's ESP is unchanged whether the callee
//     pops or not.
//
// Build (x86-32):
//   clang++ -m32 -std=c++17 -Wall -Wextra -Werror -O2 -I. \
//       app_property_list_add_from_006a2f10.cpp \
//       app_property_list_add_from_006a2f10_model_test.cpp
//   ./app_property_list_add_from_006a2f10_model_test && echo PASS

#include "app_property_list_add_from_006a2f10.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

namespace {

// Every element the loop visits, in order, with the pair of words each call
// receives. Recording the whole sequence is what pins the stride and the
// argument order; checking only the last pair would not.
struct VisitRecord {
  OpaquePropertyStorage* storage;
  OpaquePropertyElement* element;
  OpaquePropertyWord* word_after_first;
};

struct CallRecord {
  unsigned inserts;
  unsigned assigns;
  OpaquePropertyStorage* last_storage;
  OpaquePropertyWord* last_word_after_first;
  OpaquePropertyElement* last_assigned;
  OpaquePropertyElement* last_source;
  VisitRecord visits[8];
  unsigned visit_count;
};

CallRecord g_record;
OpaquePropertyElement g_scratch_a;
OpaquePropertyElement g_scratch_b;
OpaquePropertyElement g_scratch_c;

int g_failures = 0;

void check(bool condition, const char *what) {
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s\n", what);
  }
}

// Independent expectations, computed here rather than through the header's
// accessors, so a wrong accessor in the header cannot make the test agree with
// a wrong body.
OpaquePropertyStorage* expected_storage(const OpaquePropertyList* receiver) {
  return reinterpret_cast<OpaquePropertyStorage*>(
      reinterpret_cast<unsigned char*>(const_cast<OpaquePropertyList*>(receiver)) +
      0x18u);
}

OpaquePropertyWord* expected_word_after_first(OpaquePropertyElement* element) {
  return reinterpret_cast<OpaquePropertyWord*>(
      reinterpret_cast<unsigned char*>(element) + 0x04u);
}

OpaquePropertyElement* expected_next(OpaquePropertyElement* element) {
  return reinterpret_cast<OpaquePropertyElement*>(
      reinterpret_cast<unsigned char*>(element) + 0x18u);
}

constexpr std::size_t kReceiverBytes = 0x38;

// The elements are packed at the stride the listing shows, 0x18, so a range's
// end pointer sits on the lattice the loop walks and the iteration count is
// determined by the END pointer rather than by a guess. The stride itself is
// then pinned by the exact addresses visited, which a 0x20 (or 0x10) stride
// would miss.
struct Objects {
  alignas(4) std::uint8_t receiver_bytes[kReceiverBytes];
  alignas(4) std::uint8_t other_bytes[kReceiverBytes];
  alignas(4) OpaquePropertyElement elements[4];

  OpaquePropertyList* receiver() {
    return reinterpret_cast<OpaquePropertyList*>(receiver_bytes);
  }
  OpaquePropertyList* other() {
    return reinterpret_cast<OpaquePropertyList*>(other_bytes);
  }
  OpaquePropertyElement* element(std::size_t index) { return &elements[index]; }
  std::size_t completion_word(const OpaquePropertyList* list) const {
    const auto* bytes = reinterpret_cast<const unsigned char*>(list);
    std::uint32_t value = 0;
    std::memcpy(&value, bytes + 0x34u, sizeof(value));
    return value;
  }
};

// The element at a raw byte offset from element(0), for stride falsification.
OpaquePropertyElement* raw_element_at(Objects& objects,
                                      std::size_t byte_offset) {
  return reinterpret_cast<OpaquePropertyElement*>(
      reinterpret_cast<unsigned char*>(objects.element(0)) + byte_offset);
}

void seed(Objects& objects, std::size_t receiver_counter,
          std::size_t other_counter) {
  std::memset(objects.receiver_bytes, 0xa5, sizeof(objects.receiver_bytes));
  std::memset(objects.other_bytes, 0x5a, sizeof(objects.other_bytes));
  std::memset(objects.elements, 0x3c, sizeof(objects.elements));
  // The range words are pointers, so they must be written last: the fill above
  // would otherwise leave them as patterns.
  objects.receiver()->range_begin_018 = objects.element(0);
  objects.receiver()->range_end_01c = objects.element(0);
  objects.other()->range_begin_018 = objects.element(0);
  objects.other()->range_end_01c = objects.element(0);
  objects.receiver()->completed_copies_034 =
      static_cast<std::uint32_t>(receiver_counter);
  objects.other()->completed_copies_034 =
      static_cast<std::uint32_t>(other_counter);
}

void snapshot_receiver(const Objects& objects, std::uint8_t* out) {
  std::memcpy(out, objects.receiver_bytes, sizeof(objects.receiver_bytes));
}

void snapshot_other(const Objects& objects, std::uint8_t* out) {
  std::memcpy(out, objects.other_bytes, sizeof(objects.other_bytes));
}

// True when the two receiver images differ in no byte except the four at 0x34.
// A memcmp cannot express that, and counting differing bytes with memcmp's
// return value cannot either -- this walks the image.
bool only_completion_word_changed(const std::uint8_t* before,
                                  const std::uint8_t* after) {
  for (std::size_t index = 0; index < kReceiverBytes; ++index) {
    const bool is_completion_word = index >= 0x34u && index < 0x38u;
    if (is_completion_word) {
      continue;
    }
    if (before[index] != after[index]) {
      return false;
    }
  }
  return true;
}

} // namespace

// The declared contract, pinned: receiver in ECX, one 4-byte callee-popped
// stack word (RET 0x4 at 0x006a2f51), and no result. A value return would be a
// new claim the machine record does not support, so it must stop the build.
static_assert(
    std::is_same<decltype(&app_property_list_add_properties_from_006a2f10),
                 void(__thiscall *)(OpaquePropertyList *,
                                    OpaquePropertyList *)>::value,
    "0x006a2f10 takes the receiver in ECX plus one callee-popped stack word "
    "and produces no result");

extern "C" OpaquePropertyElement *__thiscall unresolved_006a2d30(
    OpaquePropertyStorage *storage, OpaquePropertyWord *word_after_first) {
  ++g_record.inserts;
  g_record.last_storage = storage;
  g_record.last_word_after_first = word_after_first;
  if (g_record.visit_count < 8u) {
    g_record.visits[g_record.visit_count].storage = storage;
    g_record.visits[g_record.visit_count].word_after_first = word_after_first;
    ++g_record.visit_count;
  }
  // Three distinguishable results, so "the second callee's receiver is the
  // first callee's result" can be checked per iteration.
  switch (g_record.inserts) {
    case 1u:
      return &g_scratch_a;
    case 2u:
      return &g_scratch_b;
    default:
      return &g_scratch_c;
  }
}

extern "C" void __thiscall unresolved_00542b80(OpaquePropertyElement *element,
                                              OpaquePropertyElement *source) {
  ++g_record.assigns;
  g_record.last_assigned = element;
  g_record.last_source = source;
  if (g_record.visit_count != 0u) {
    g_record.visits[g_record.visit_count - 1u].element = element;
  }
}

int main() {
  Objects objects;
  std::uint8_t receiver_before[kReceiverBytes];
  std::uint8_t other_before[kReceiverBytes];

  // 1. Self-copy: 0x006a2f19 JZ 0x006a2f50 exits before the loop and before
  //    INC dword ptr [EBP+0x34], so nothing is called and nothing increments.
  seed(objects, 3u, 9u);
  g_record = CallRecord();
  snapshot_receiver(objects, receiver_before);
  snapshot_other(objects, other_before);
  app_property_list_add_properties_from_006a2f10(objects.receiver(),
                                                 objects.receiver());
  check(g_record.inserts == 0U, "self-copy must not call 0x006a2d30");
  check(g_record.assigns == 0U, "self-copy must not call 0x00542b80");
  check(objects.completion_word(objects.receiver()) == 3U,
        "self-copy must not increment the word at 0x34");
  check(std::memcmp(receiver_before, objects.receiver_bytes,
                    sizeof(receiver_before)) == 0,
        "self-copy must not write the receiver at all");
  check(only_completion_word_changed(receiver_before,
                                     objects.receiver_bytes),
        "the self-copy guard compares pointers, so not even the completion "
        "word moves");

  // 2. The guard is pointer identity, not content equality: two DISTINCT
  //    objects holding the same range words are not a self-copy.
  seed(objects, 0u, 0u);
  objects.other()->range_begin_018 = objects.element(1);
  objects.other()->range_end_01c = objects.element(2);
  objects.receiver()->range_begin_018 = objects.element(1);
  objects.receiver()->range_end_01c = objects.element(2);
  g_record = CallRecord();
  app_property_list_add_properties_from_006a2f10(objects.receiver(),
                                                 objects.other());
  check(g_record.inserts == 1U,
        "two distinct objects with equal, non-empty range words are not a "
        "self-copy");
  check(g_record.visits[0].word_after_first ==
            expected_word_after_first(objects.element(1)),
        "the range walked is the one both objects name");
  check(objects.completion_word(objects.receiver()) == 1U,
        "such a copy still counts as one completed copy");

  // 3. Empty range: 0x006a2f25 JZ 0x006a2f4b skips the loop and the POP EBX,
  //    and still reaches the increment.
  seed(objects, 4u, 11u);
  objects.other()->range_begin_018 = objects.element(0);
  objects.other()->range_end_01c = objects.element(0);
  g_record = CallRecord();
  snapshot_receiver(objects, receiver_before);
  snapshot_other(objects, other_before);
  app_property_list_add_properties_from_006a2f10(objects.receiver(),
                                                 objects.other());
  check(g_record.inserts == 0U, "empty range must not call 0x006a2d30");
  check(g_record.assigns == 0U, "empty range must not call 0x00542b80");
  check(objects.completion_word(objects.receiver()) == 5U,
        "empty range must still increment the word at 0x34");
  check(objects.completion_word(objects.other()) == 11U,
        "the word at 0x34 belongs to the RECEIVER: the argument's must not "
        "move");
  check(std::memcmp(other_before, objects.other_bytes,
                    sizeof(other_before)) == 0,
        "the argument must not be written at all");
  check(only_completion_word_changed(receiver_before,
                                     objects.receiver_bytes),
        "on the empty path only the receiver's word at 0x34 changes");

  // 4. Two elements: the whole ordered sequence is checked, and every field
  //    that belongs to the other object is checked to be the other object's.
  seed(objects, 0u, 7u);
  objects.receiver()->range_begin_018 = objects.element(0);
  objects.receiver()->range_end_01c = objects.element(0);
  objects.other()->range_begin_018 = objects.element(0);
  objects.other()->range_end_01c = objects.element(2);
  g_record = CallRecord();
  snapshot_receiver(objects, receiver_before);
  snapshot_other(objects, other_before);
  app_property_list_add_properties_from_006a2f10(objects.receiver(),
                                                 objects.other());
  check(g_record.inserts == 2U, "two elements must give two 0x006a2d30 calls");
  check(g_record.assigns == 2U, "two elements must give two 0x00542b80 calls");
  check(g_record.visit_count == 2U, "exactly two loop iterations");

  // The stride is 0x18 and the visited elements are the ARGUMENT's range.
  check(g_record.visits[0].word_after_first ==
            expected_word_after_first(objects.element(0)),
        "iteration 1 must pass element0+0x4, so the stride begins at 0x18");
  check(g_record.visits[1].word_after_first ==
            expected_word_after_first(expected_next(objects.element(0))),
        "iteration 2 must pass element0+0x18+0x4");
  check(g_record.visits[1].word_after_first !=
            expected_word_after_first(raw_element_at(objects, 0x20u)),
        "the stride is 0x18: a 0x20 step would land elsewhere");
  check(g_record.visits[1].word_after_first !=
            expected_word_after_first(raw_element_at(objects, 0x10u)),
        "the stride is 0x18: a 0x10 step would land elsewhere");

  // ECX of the first call is the RECEIVER's storage word, never the argument's
  // and never the receiver's base.
  check(g_record.visits[0].storage == expected_storage(objects.receiver()),
        "ECX of 0x006a2d30 must be receiver+0x18");
  check(g_record.visits[0].storage != expected_storage(objects.other()),
        "the storage word belongs to the receiver, not to the argument");
  check(reinterpret_cast<unsigned char*>(g_record.visits[0].storage) !=
            reinterpret_cast<unsigned char*>(objects.receiver()),
        "ECX is receiver+0x18, not the receiver itself");

  // The second callee's receiver is the first callee's result, and its stack
  // word is the element pointer the first call left behind.
  check(g_record.visits[0].element == &g_scratch_a,
        "0x00542b80 must receive the first 0x006a2d30 result as its receiver");
  check(g_record.visits[1].element == &g_scratch_b,
        "and the second result on the second iteration");
  check(g_record.visits[0].element != g_record.visits[1].element,
        "the two iterations must not share a callee result");
  check(g_record.last_source == expected_next(objects.element(0)),
        "0x00542b80 must receive element0+0x18, the pointer the first call "
        "left on the stack");

  // One increment per call, whatever the element count, on the receiver only.
  check(objects.completion_word(objects.receiver()) == 1U,
        "one increment per call, whatever the element count");
  check(objects.completion_word(objects.other()) == 7U,
        "the argument's word at 0x34 must be untouched");

  // Only the receiver's word at 0x34 may differ, on both objects.
  check(std::memcmp(other_before, objects.other_bytes,
                    sizeof(other_before)) == 0,
        "the argument must be byte-identical after a two-element copy");
  check(only_completion_word_changed(receiver_before,
                                     objects.receiver_bytes),
        "exactly one word of the receiver changed, and it is the word at 0x34");
  check(std::memcmp(receiver_before + 0x34u, objects.receiver_bytes + 0x34u, 4U) !=
            0,
        "the word at 0x34 really did change on the two-element path");

  // 5. Three elements through the same pair of callees: the count and the
  //    ordering still hold, and the result sequence is per-iteration.
  seed(objects, 0u, 0u);
  objects.other()->range_begin_018 = objects.element(0);
  objects.other()->range_end_01c = objects.element(3);
  g_record = CallRecord();
  app_property_list_add_properties_from_006a2f10(objects.receiver(),
                                                 objects.other());
  check(g_record.inserts == 3U, "three elements must give three insert calls");
  check(g_record.assigns == 3U, "three elements must give three assign calls");
  check(objects.completion_word(objects.receiver()) == 1U,
        "still exactly one completion increment");
  check(g_record.visits[2].word_after_first ==
            expected_word_after_first(objects.element(2)),
        "the third iteration visits element0+0x36");

  // 6. The call is made through the modelled convention, so the argument
  //    arrives on the stack intact and the receiver in ECX is the caller's.
  seed(objects, 2u, 0u);
  objects.other()->range_begin_018 = objects.element(0);
  objects.other()->range_end_01c = objects.element(1);
  g_record = CallRecord();
  using EntryPoint = void(__thiscall *)(OpaquePropertyList *,
                                       OpaquePropertyList *);
  const EntryPoint target = &app_property_list_add_properties_from_006a2f10;
  target(objects.receiver(), objects.other());
  check(g_record.inserts == 1U,
        "the stack word reached the body: one element was copied");
  check(g_record.last_storage == expected_storage(objects.receiver()),
        "the receiver the body aliased into EBP is the caller's object");
  check(objects.completion_word(objects.receiver()) == 3U,
        "the completion word is the caller's receiver, at +0x34");

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("006a2f10 model test: all checks passed\n");
  return 0;
}
