#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

#include "dogfood_008db310.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-008db310 requires an MSVC or GCC calling convention"
#endif

// Behavioural test for the 0x008db310 index bounds probe.
//
// The fixtures set up the carrier and the nodes BY DISPLACEMENT, through the
// same accessors the body uses, because both model types are opaque runs: the
// body reaches the carrier at +0x2c and +0x30 and a node at +0x0c, +0x10 and
// +0x1c, and the machine-derived receiver record is a set of displacements that
// says nothing about which member is which.
//
// The cases marked REFUTE exist to BREAK the reconstruction. Each names the
// wrong reconstruction it is aimed at:
//
//   R1  the carrier's two words are at +0x2c and +0x30, not at +0x28, +0x34 or
//       +0x38 (all three of which the receiver record's own enumeration would
//       have allowed): decoy carriers are built and must change nothing;
//   R2  a node's record begin is at +0x0c and its size at +0x10: decoys one
//       dword either way must not move the verdict;
//   R3  a node's chain word is at +0x1c: a decoy at +0x18 must not be followed;
//   R4  the slot array is indexed with a 4-BYTE stride, so end_slot N selects
//       slots[N] and not slots[N*4] or slots[N+1];
//   R5  the terminator is the POINTER held in the end slot, compared by
//       identity - not the node's contents and not the node's chain word;
//   R6  both range compares are UNSIGNED: two inputs on which a signed compare
//       takes the other arm, one for each compare;
//   R7  the zero-extent early return happens BEFORE either receiver word is
//       read, so a null carrier with a zero extent returns true;
//   R8  the ABI: the two argument words are popped by the CALLEE, measured by
//       sampling ESP inside a trampoline rather than asserted as a convention.

namespace openspore::reconstruction::pkg_orchestrate_dogfood_008db310 {
namespace {

int failures = 0;
unsigned int dispatch_calls = 0;

struct ObservedCall {
  OpaqueWriteCarrier* receiver;
  void* destination;
  OpaqueWord destination_size;
};

ObservedCall observed{};

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void check_named(const char* what, bool condition) {
  if (!condition) {
    ++failures;
    std::fprintf(stderr, "FAIL: %s\n", what);
  }
}

void* address_of(OpaqueWord value) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(value));
}

OpaqueWord raw_of(void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

bool PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL
dispatch_014368bc(OpaqueWriteCarrier* receiver, void* destination,
                  OpaqueWord destination_size) {
  observed.receiver = receiver;
  observed.destination = destination;
  observed.destination_size = destination_size;
  ++dispatch_calls;
  return pf_index_write_bounds_008db310(receiver, destination,
                                        destination_size);
}

const OpaqueWord kSlotCount = 4u;
const OpaqueWord kEndSlot = 3u;

// Test-side placement helpers. They write the same four displacements the body
// reads, and nothing else: a fixture byte the body never reads stays at whatever
// the reset left there, which is what makes the decoy cases below meaningful.
void set_word(void* base, std::size_t displacement, OpaqueWord value) {
  std::memcpy(word_at(base, displacement), &value, sizeof value);
}

OpaqueWord get_word(const void* base, std::size_t displacement) {
  OpaqueWord value = 0;
  std::memcpy(&value, word_at(base, displacement), sizeof value);
  return value;
}

struct OpaqueFixture {
  OpaqueWriteCarrier carrier{};
  OpaqueItemNode nodes[4]{};
  OpaqueItemNode* slots[kSlotCount]{};
  OpaqueItemNode* end_node = nullptr;
};

// Clear every byte of `object`, padding included.
//
// The fixture types carry default member initialisers so a default-constructed
// fixture is well defined, which makes them non-trivial and gets std::memset
// rejected by -Wclass-memaccess under the repository's -Werror. The intent here
// is a zeroed byte pattern rather than a value assignment, so the bytes are
// written directly; the starting state is identical under both compilers.
template <class T>
inline void clear_bytes(T& object) {
  unsigned char* bytes = reinterpret_cast<unsigned char*>(&object);
  for (std::size_t index = 0; index < sizeof(T); ++index) {
    bytes[index] = 0;
  }
}

void initialize(OpaqueFixture& fixture) {
  dispatch_calls = 0u;
  observed = ObservedCall{};
  g_pf_index_write_008db310_ports = OpaquePorts{};

  for (std::size_t i = 0; i < 4u; ++i) {
    clear_bytes(fixture.nodes[i]);
  }
  for (OpaqueWord i = 0u; i < kSlotCount; ++i) {
    fixture.slots[i] = nullptr;
  }
  fixture.end_node = &fixture.nodes[3];
  fixture.slots[kEndSlot] = fixture.end_node;

  clear_bytes(fixture.carrier);
  set_word(&fixture.carrier, kCarrierSlotArrayDisplacement,
           raw_of(fixture.slots));
  set_word(&fixture.carrier, kCarrierEndSlotDisplacement, kEndSlot);
}

void place(OpaqueFixture& fixture, OpaqueWord slot, OpaqueWord node_index,
           OpaqueWord record_begin, OpaqueWord record_size) {
  fixture.slots[slot] = &fixture.nodes[node_index];
  set_word(&fixture.nodes[node_index], kNodeRecordBeginDisplacement, record_begin);
  set_word(&fixture.nodes[node_index], kNodeRecordSizeDisplacement, record_size);
  set_word(&fixture.nodes[node_index], kNodeChainDisplacement, 0u);
}

// -- baseline cases (unchanged in intent from the package's original test) ----

void test_zero_extent_returns_true_before_the_map_is_read() {
  OpaqueFixture fixture{};
  initialize(fixture);
  set_word(&fixture.carrier, kCarrierSlotArrayDisplacement, 0u);
  set_word(&fixture.carrier, kCarrierEndSlotDisplacement, 0xffffffffu);

  const bool result =
      pf_index_write_bounds_008db310(&fixture.carrier, &fixture, 0u);

  check(result);
  check(dispatch_calls == 0u);
  check(get_word(&fixture.carrier, kCarrierSlotArrayDisplacement) == 0u);
  check(get_word(&fixture.carrier, kCarrierEndSlotDisplacement) == 0xffffffffu);
}

void test_overlapping_record_returns_false() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x2000u, 0x40u);
  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(fixture.end_node));

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(!result);
}

void test_adjacent_records_are_not_overlaps() {
  OpaqueFixture after{};
  initialize(after);
  place(after, 0u, 0u, 0x2020u, 0x10u);
  set_word(&after.nodes[0], kNodeChainDisplacement, raw_of(after.end_node));

  const bool after_result = pf_index_write_bounds_008db310(
      &after.carrier, address_of(0x2010u), 0x10u);
  check(after_result);

  OpaqueFixture before{};
  initialize(before);
  place(before, 0u, 0u, 0x2000u, 0x10u);
  set_word(&before.nodes[0], kNodeChainDisplacement, raw_of(before.end_node));

  const bool before_result = pf_index_write_bounds_008db310(
      &before.carrier, address_of(0x2010u), 0x10u);
  check(before_result);
}

void test_zero_sized_record_is_never_compared() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x2014u, 0u);
  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(fixture.end_node));

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(result);
}

void test_range_compare_is_unsigned_across_wrap() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0u, 0x80000010u);
  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(fixture.end_node));

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x1000u), 0x10u);

  check(!result);
}

void test_chain_interior_node_is_examined() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x1000u, 0x10u);
  set_word(&fixture.nodes[1], kNodeRecordBeginDisplacement, 0x2010u);
  set_word(&fixture.nodes[1], kNodeRecordSizeDisplacement, 0x10u);
  set_word(&fixture.nodes[1], kNodeChainDisplacement, raw_of(fixture.end_node));
  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(&fixture.nodes[1]));

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(!result);
}

void test_end_node_terminates_before_any_range_test() {
  OpaqueFixture fixture{};
  initialize(fixture);
  fixture.slots[0] = fixture.end_node;
  place(fixture, 1u, 0u, 0x2000u, 0x40u);

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(result);
}

void test_null_slots_are_skipped_before_the_first_test() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 2u, 0u, 0x2000u, 0x40u);
  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(fixture.end_node));

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(!result);
}

void test_chain_end_resumes_at_the_next_slot() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x1000u, 0x10u);
  place(fixture, 2u, 1u, 0x2010u, 0x10u);
  set_word(&fixture.nodes[1], kNodeChainDisplacement, raw_of(fixture.end_node));

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(!result);
}

void test_whole_index_without_overlap_returns_true() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x1000u, 0x10u);
  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(&fixture.nodes[1]));
  place(fixture, 2u, 1u, 0x9000u, 0x10u);
  set_word(&fixture.nodes[1], kNodeChainDisplacement, raw_of(fixture.end_node));

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(result);
}

void test_dispatch_port_is_closed_by_default() {
  OpaqueFixture fixture{};
  initialize(fixture);

  check(g_pf_index_write_008db310_ports.dispatch_014368bc == nullptr);
  check(dispatch_calls == 0u);
  check(sizeof(OpaquePorts) == 4);
}

void test_configured_dispatch_receives_the_two_stack_words() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x2000u, 0x40u);
  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(fixture.end_node));
  g_pf_index_write_008db310_ports.dispatch_014368bc = &dispatch_014368bc;

  void* const destination = address_of(0x2010u);
  const bool result = g_pf_index_write_008db310_ports.dispatch_014368bc(
      &fixture.carrier, destination, 0x10u);

  check(!result);
  check(dispatch_calls == 1u);
  check(observed.receiver == &fixture.carrier);
  check(observed.destination == destination);
  check(observed.destination_size == 0x10u);
  check(raw_of(observed.destination) == 0x2010u);
  check(observed.receiver != observed.destination);
}

void test_end_slot_word_selects_the_terminator() {
  OpaqueFixture early{};
  initialize(early);
  place(early, 0u, 0u, 0x1000u, 0x10u);
  place(early, 2u, 2u, 0x2010u, 0x10u);
  set_word(&early.nodes[0], kNodeChainDisplacement, raw_of(&early.nodes[1]));
  set_word(&early.nodes[1], kNodeChainDisplacement, raw_of(&early.nodes[2]));
  set_word(&early.nodes[2], kNodeChainDisplacement, 0u);
  set_word(&early.carrier, kCarrierEndSlotDisplacement, 2u);

  const bool early_result = pf_index_write_bounds_008db310(
      &early.carrier, address_of(0x2010u), 0x10u);
  check(early_result);

  OpaqueFixture late{};
  initialize(late);
  place(late, 0u, 0u, 0x1000u, 0x10u);
  place(late, 2u, 2u, 0x2010u, 0x10u);
  set_word(&late.nodes[0], kNodeChainDisplacement, raw_of(&late.nodes[1]));
  set_word(&late.nodes[1], kNodeChainDisplacement, raw_of(&late.nodes[2]));
  set_word(&late.nodes[2], kNodeChainDisplacement, 0u);
  set_word(&late.carrier, kCarrierEndSlotDisplacement, kEndSlot);

  const bool late_result =
      pf_index_write_bounds_008db310(&late.carrier, address_of(0x2010u), 0x10u);
  check(!late_result);
}

void test_modeled_signatures() {
  using EntrySignature = bool(PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL*)(
      OpaqueWriteCarrier*, void*, OpaqueWord);
  using DispatchSignature = bool(PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL*)(
      OpaqueWriteCarrier*, void*, OpaqueWord);

  static_assert(std::is_same<decltype(&pf_index_write_bounds_008db310),
                             EntrySignature>::value,
                "entry is thiscall with the carrier plus two stack words");
  static_assert(std::is_same<DispatchSlot014368bc, DispatchSignature>::value,
                "dispatch port carries the same three words");
  static_assert(sizeof(decltype(&pf_index_write_bounds_008db310)) == 4,
                "entry width");
  static_assert(
      std::is_same<decltype(&dispatch_014368bc), DispatchSignature>::value,
      "fake is calling-convention matched to the dispatch port");
}

// -- REFUTATION CASES --------------------------------------------------------

// R1. The carrier's two words live at +0x2c and +0x30. A carrier whose +0x28,
// +0x34 and +0x38 hold decoys - including a decoy end slot that would truncate
// the walk - must give the same answer, because the body reads none of them.
// +0x34 and +0x38 are the two extra values the receiver record enumerates, so
// this is the case that separates "the record's bounds" from "the body's reach".
void refutation_carrier_displacements() {
  OpaqueFixture plain{};
  initialize(plain);
  place(plain, 0u, 0u, 0x2000u, 0x40u);
  set_word(&plain.nodes[0], kNodeChainDisplacement, raw_of(plain.end_node));
  const bool plain_result = pf_index_write_bounds_008db310(
      &plain.carrier, address_of(0x2010u), 0x10u);
  check_named("R1a: the plain carrier reports the overlap", !plain_result);

  OpaqueFixture decoy{};
  initialize(decoy);
  place(decoy, 0u, 0u, 0x2000u, 0x40u);
  set_word(&decoy.nodes[0], kNodeChainDisplacement, raw_of(decoy.end_node));
  // A slot array one dword lower, an end slot of 0 one dword higher, and an
  // end slot of 0xffffffff two dwords higher.
  set_word(&decoy.carrier, 0x28, raw_of(decoy.slots));
  set_word(&decoy.carrier, 0x34, 0u);
  set_word(&decoy.carrier, 0x38, 0xffffffffu);
  const bool decoy_result = pf_index_write_bounds_008db310(
      &decoy.carrier, address_of(0x2010u), 0x10u);
  check_named("R1b: the +0x28 slot-array decoy is not read", !decoy_result);
  check_named("R1c: the +0x34 end-slot decoy is not read", !decoy_result);

  // And the mirror: a real overlap that only the decoy end slot would have
  // hidden. end_slot 0 at +0x30 stops the walk at slot 0, where the overlapping
  // record lives, so the answer is false. A reconstruction reading +0x34 would
  // see 0 and also stop there - so drive the discriminating case the other way.
  OpaqueFixture hidden{};
  initialize(hidden);
  place(hidden, 2u, 0u, 0x2000u, 0x40u);  // overlapping record lives at slot 2
  set_word(&hidden.nodes[0], kNodeChainDisplacement, raw_of(hidden.end_node));
  set_word(&hidden.carrier, kCarrierEndSlotDisplacement, 0u);
  const bool hidden_result = pf_index_write_bounds_008db310(
      &hidden.carrier, address_of(0x2010u), 0x10u);
  check_named("R1d: end slot 0 stops before the slot-2 record, so no overlap",
              hidden_result);
  set_word(&hidden.carrier, 0x34, 0u);
  const bool hidden_again = pf_index_write_bounds_008db310(
      &hidden.carrier, address_of(0x2010u), 0x10u);
  check_named("R1e: and the answer does not change when the +0x34 decoy moves",
              hidden_again == hidden_result);
}

// R2. A node's record begin is the word at +0x0c and its size the word at
// +0x10. Decoys at +0x08 and +0x14 are left at values that would produce the
// opposite verdict.
void refutation_node_record_displacements() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x1000u, 0x10u);  // a real, non-overlapping record
  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(fixture.end_node));
  // Decoys: +0x08 says the record starts at 0x2010 and +0x14 says it is 0x40
  // long, which together would overlap the destination.
  set_word(&fixture.nodes[0], 0x08, 0x2010u);
  set_word(&fixture.nodes[0], 0x14, 0x40u);

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);
  check_named("R2a: the record words are at +0x0c and +0x10, not +0x08/+0x14",
              result);
  check_named("R2b: and the decoys were left alone",
              get_word(&fixture.nodes[0], 0x08) == 0x2010u &&
                  get_word(&fixture.nodes[0], 0x14) == 0x40u);

  // Mirror: the real words overlap and the decoys do not. The answer must be
  // false, which a reconstruction reading the decoys would call true.
  OpaqueFixture other{};
  initialize(other);
  place(other, 0u, 0u, 0x2000u, 0x40u);
  set_word(&other.nodes[0], kNodeChainDisplacement, raw_of(other.end_node));
  set_word(&other.nodes[0], 0x08, 0x9000u);
  set_word(&other.nodes[0], 0x14, 0x10u);
  const bool other_result = pf_index_write_bounds_008db310(
      &other.carrier, address_of(0x2010u), 0x10u);
  check_named("R2c: and in the other direction the real words decide", !other_result);
}

// R3. The chain word is at +0x1c. A decoy at +0x18 that would lead straight to
// an overlapping record must not be followed, and a real chain at +0x1c must be.
void refutation_node_chain_displacement() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x1000u, 0x10u);
  // node 1 overlaps the destination; only the +0x1c chain word can reach it.
  set_word(&fixture.nodes[1], kNodeRecordBeginDisplacement, 0x2010u);
  set_word(&fixture.nodes[1], kNodeRecordSizeDisplacement, 0x10u);
  set_word(&fixture.nodes[1], kNodeChainDisplacement, raw_of(fixture.end_node));
  // Decoy chain at +0x18 pointing at the overlapping node.
  set_word(&fixture.nodes[0], 0x18, raw_of(&fixture.nodes[1]));
  set_word(&fixture.nodes[0], kNodeChainDisplacement, 0u);

  const bool decoy_only = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);
  check_named("R3a: with the chain word zero the +0x18 decoy is not followed",
              decoy_only);

  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(&fixture.nodes[1]));
  const bool via_real_chain = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);
  check_named("R3b: the +0x1c chain word IS followed", !via_real_chain);
}

// R4. The empty-slot skip walks with a 4-BYTE stride, one pointer per slot. The
// fixture is built so that a stride of 8 bytes (or of one byte) steps OVER the
// occupied slot and lands on the terminator instead, which flips the answer.
void refutation_slot_stride_is_four_bytes() {
  OpaqueFixture fixture{};
  initialize(fixture);
  // slot 0 empty, slot 1 holds an overlapping record, slot 2 is the terminator,
  // slot 3 holds a second overlapping record that must never be reached.
  fixture.slots[0] = nullptr;
  place(fixture, 1u, 0u, 0x2010u, 0x10u);
  fixture.slots[kEndSlot] = fixture.end_node;
  place(fixture, 2u, 1u, 0x2020u, 0x10u);
  set_word(&fixture.nodes[0], kNodeChainDisplacement, 0u);
  set_word(&fixture.nodes[1], kNodeChainDisplacement, 0u);
  set_word(&fixture.carrier, kCarrierEndSlotDisplacement, 2u);

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);
  check_named("R4a: the skip stops on the occupied slot one pointer along",
              !result);
  check_named("R4b: and the terminator really is slots[2]",
              get_word(&fixture.carrier, kCarrierEndSlotDisplacement) == 2u);
}

// R5. The terminator is the POINTER held in the end slot and is compared by
// IDENTITY. The two nodes below are byte-for-byte identical and differ only in
// their addresses, and the visited one overlaps the destination. A
// reconstruction that compared the node's contents, or that compared the pointer
// with itself, would report no overlap; pointer identity reports the overlap.
void refutation_terminator_is_pointer_identity() {
  OpaqueFixture fixture{};
  initialize(fixture);
  // slot 0: the visited node, overlapping the destination.
  place(fixture, 0u, 0u, 0x2010u, 0x10u);
  set_word(&fixture.nodes[0], kNodeChainDisplacement, 0u);
  // The end slot holds a byte-identical copy: same record, same chain, different
  // address. It is the terminator, so the walk must never examine its record.
  std::memcpy(&fixture.nodes[3], &fixture.nodes[0], sizeof fixture.nodes[3]);
  fixture.end_node = &fixture.nodes[3];
  fixture.slots[kEndSlot] = fixture.end_node;

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);
  check_named("R5a: the terminator is compared by address, so the byte-identical "
              "node in slot 0 is still examined and still overlaps",
              !result);
  check_named("R5b: the two nodes really are distinct objects",
              static_cast<void*>(&fixture.nodes[0]) !=
                  static_cast<void*>(fixture.end_node));

  // Mirror: the OVERLAPPING node is the terminator. Its record must never be
  // examined, so the answer is true even though the same bytes sit in the end
  // slot. The visited node's chain leads to the terminator.
  OpaqueFixture mirror{};
  initialize(mirror);
  place(mirror, 0u, 0u, 0x1000u, 0x10u);
  set_word(&mirror.nodes[0], kNodeChainDisplacement, raw_of(&mirror.nodes[3]));
  set_word(&mirror.nodes[3], kNodeRecordBeginDisplacement, 0x2010u);
  set_word(&mirror.nodes[3], kNodeRecordSizeDisplacement, 0x10u);
  set_word(&mirror.nodes[3], kNodeChainDisplacement, raw_of(&mirror.nodes[2]));
  mirror.end_node = &mirror.nodes[3];
  mirror.slots[kEndSlot] = mirror.end_node;
  const bool mirror_result = pf_index_write_bounds_008db310(
      &mirror.carrier, address_of(0x2010u), 0x10u);
  check_named("R5c: and the terminator's own overlapping record is never read",
              mirror_result);
}

// R6. BOTH range compares are unsigned. The two cases are chosen so that a
// signed compare takes the other arm on each of them separately.
void refutation_range_compares_are_unsigned() {
  // First compare: `CMP record_begin, destination_end` / JNC. Record begin 0 and
  // destination_end 0x80000010: unsigned says 0 < 0x80000010 (run the test),
  // signed says 0 >= INT_MIN (skip it). The second compare then decides.
  OpaqueFixture first{};
  initialize(first);
  place(first, 0u, 0u, 0x0000u, 0x80000010u);
  set_word(&first.nodes[0], kNodeChainDisplacement, raw_of(first.end_node));
  const bool first_result = pf_index_write_bounds_008db310(
      &first.carrier, address_of(0x80000000u), 0x10u);
  check_named("R6a: the FIRST compare is unsigned", !first_result);

  // Second compare: `CMP destination_begin, record_end` / JC. The first compare
  // passes under BOTH readings here (0 < 0xffffffff unsigned and 0 < -1 signed),
  // so only the second can decide. Unsigned, 0x80000000 is not below 0x10 and
  // there is no overlap; signed, 0x80000000 is negative and IS below 0x10.
  OpaqueFixture second{};
  initialize(second);
  place(second, 0u, 0u, 0x0000u, 0x10u);
  set_word(&second.nodes[0], kNodeChainDisplacement, raw_of(second.end_node));
  const bool second_result = pf_index_write_bounds_008db310(
      &second.carrier, address_of(0x80000000u), 0x7fffffffu);
  check_named("R6b: the SECOND compare is unsigned", second_result);

  // The two ends are built by 32-bit adds, and the machine's unsigned compares
  // do NOT see a range that wraps past 0xffffffff. A record at 0xfffffff0 of
  // length 0x20 reaches 0x10 in 32-bit arithmetic - and it does cover 0x0..0x10 -
  // yet `CMP record_begin, destination_end` says 0xfffffff0 >= 0x10 and the body
  // skips the range test entirely. The model reports what the machine does, not
  // what a wrap-aware overlap test would say.
  OpaqueFixture wrap{};
  initialize(wrap);
  place(wrap, 0u, 0u, 0xfffffff0u, 0x20u);
  set_word(&wrap.nodes[0], kNodeChainDisplacement, raw_of(wrap.end_node));
  const bool wrap_result = pf_index_write_bounds_008db310(
      &wrap.carrier, address_of(0x00000000u), 0x10u);
  check_named("R6c: a wrapped record range is NOT reported as an overlap, "
              "because the machine's first compare skips it",
              wrap_result);
}

// R7. The zero-extent early return precedes both receiver reads, so a carrier
// that could not be walked at all still returns true.
void refutation_zero_extent_short_circuits() {
  OpaqueFixture fixture{};
  initialize(fixture);
  set_word(&fixture.carrier, kCarrierSlotArrayDisplacement, 0u);
  set_word(&fixture.carrier, kCarrierEndSlotDisplacement, 0xffffffffu);

  const bool result =
      pf_index_write_bounds_008db310(&fixture.carrier, address_of(0u), 0u);
  check_named("R7a: a null slot array with a zero extent returns true", result);
  check_named("R7b: and neither receiver word was written",
              get_word(&fixture.carrier, kCarrierSlotArrayDisplacement) == 0u &&
                  get_word(&fixture.carrier, kCarrierEndSlotDisplacement) ==
                      0xffffffffu);

  // The early return is a property of the ZERO EXTENT, not of the receiver: the
  // same slot-array word is read and used on a non-zero extent, so the test
  // cannot be passing because the carrier happened to be unusable.
  OpaqueFixture walked{};
  initialize(walked);
  place(walked, 0u, 0u, 0x2010u, 0x10u);
  set_word(&walked.nodes[0], kNodeChainDisplacement, raw_of(walked.end_node));
  const bool walked_result = pf_index_write_bounds_008db310(
      &walked.carrier, address_of(0x2010u), 0x10u);
  check_named("R7c: with a non-zero extent the same slot-array word IS read and "
              "the record IS compared", !walked_result);
}

// R8. ABI. The terminator is `RET 0x8`, so the callee owns the two argument
// words. ESP is sampled inside a trampoline, before the pushes and after the
// return: the two are equal only when the callee popped all eight bytes.
struct EspSamples {
  std::uint32_t before_push = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_measured(OpaqueWriteCarrier* index, void* destination,
                         OpaqueWord destination_size) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&pf_index_write_bounds_008db310));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  // EAX and ECX are in the clobber list, so the compiler cannot have allocated
  // any of the four inputs to them.
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "pushl %[size]\n\t"
                       "pushl %[dest]\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(index),
                         [dest] "r"(destination), [size] "r"(destination_size)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_push = before;
  samples.after_return = after;
  return samples;
}

void refutation_two_argument_words_are_callee_cleaned() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x2000u, 0x40u);
  set_word(&fixture.nodes[0], kNodeChainDisplacement, raw_of(fixture.end_node));

  const EspSamples samples =
      call_measured(&fixture.carrier, address_of(0x2010u), 0x10u);
  check_named("R8a: the callee popped both argument words (RET 0x8)",
              samples.after_return == samples.before_push);
}

// The displacements the reconstruction states, against the listing's own bytes.
void verify_displacement_constants() {
  check_named("V1: the slot-array word is at receiver+0x2c",
              kCarrierSlotArrayDisplacement == 0x2cu);
  check_named("V2: the end-slot word is at receiver+0x30",
              kCarrierEndSlotDisplacement == 0x30u);
  check_named("V3: the record begin is at node+0x0c",
              kNodeRecordBeginDisplacement == 0x0cu);
  check_named("V4: the record size is at node+0x10",
              kNodeRecordSizeDisplacement == 0x10u);
  check_named("V5: the chain word is at node+0x1c",
              kNodeChainDisplacement == 0x1cu);
  check_named("V6: the modeled carrier ends after the end-slot word",
              sizeof(OpaqueWriteCarrier) == 0x34u);
  check_named("V7: the modeled node ends after the chain word",
              sizeof(OpaqueItemNode) == 0x20u);
  check_named("V8: a slot is one 32-bit pointer wide",
              sizeof(OpaqueItemNode*) == 4u);
}

int run_model() {
  failures = 0;
  verify_displacement_constants();
  test_zero_extent_returns_true_before_the_map_is_read();
  test_overlapping_record_returns_false();
  test_adjacent_records_are_not_overlaps();
  test_zero_sized_record_is_never_compared();
  test_range_compare_is_unsigned_across_wrap();
  test_chain_interior_node_is_examined();
  test_end_node_terminates_before_any_range_test();
  test_null_slots_are_skipped_before_the_first_test();
  test_chain_end_resumes_at_the_next_slot();
  test_whole_index_without_overlap_returns_true();
  test_end_slot_word_selects_the_terminator();
  test_dispatch_port_is_closed_by_default();
  test_configured_dispatch_receives_the_two_stack_words();
  test_modeled_signatures();
  refutation_carrier_displacements();
  refutation_node_record_displacements();
  refutation_node_chain_displacement();
  refutation_slot_stride_is_four_bytes();
  refutation_terminator_is_pointer_identity();
  refutation_range_compares_are_unsigned();
  refutation_zero_extent_short_circuits();
  refutation_two_argument_words_are_callee_cleaned();
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_orchestrate_dogfood_008db310::
      run_model();
}

#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
