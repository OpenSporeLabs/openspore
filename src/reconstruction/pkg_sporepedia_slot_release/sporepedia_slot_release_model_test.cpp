// PKG-SPOREPEDIA-SLOT-RELEASE -- VA 0x00641e10
// Behavioural model test for FUN_00641e10.
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, x86-32)
//
// The body has two transfers and one external callee, and this test supplies the
// other halves of both: the address the body reaches through the pointee's
// dispatch word is defined here as an observer, and 0x005bf0e0 -- the one direct
// callee, which the package's header declares and nothing defines -- is defined
// here as a stub that records the pair of pointers it is handed and returns a
// word this test chooses.
//
// What is asserted is what the 19-instruction listing fixes, and nothing more:
//
//   0x00641e14/0x00641e17  the receiver's word is read at 0x20 and its address
//                           is taken
//   0x00641e1a/0x00641e1c  the test on that word, and the block it skips
//   0x00641e1e            the body's only write, and that it precedes the transfer
//   0x00641e24/26/29      the two-level slot read out of the pointee's dispatch
//                           word, and the transfer through it
//   0x00641e2b/2c/2f/30   the direct callee's two-word argument pair, on both paths
//   0x00641e35            the caller-side cleanup, encoded by a cdecl callee
//   0x00641e3a            the word the body leaves in EAX
//
// What is NOT asserted, because no record for this target fixes it: what the
// receiver's word at 0x20 is (the receiver record enumerates the displacement and
// names no member), what the pointee or its dispatch block is, whether that block
// is a class vtable, what the slot at displacement 4 resolves to in the original,
// and what 0x005bf0e0 does with the pair it is given. Both stubs below are
// observers and neither is asked to model a callee. The open questions this test
// deliberately leaves open are listed in
// reconstruction/metadata/pkg-sporepedia-slot-release/00641e10.json
// (unresolved_questions) and in reconstruction/evidence/00641e10/validation.json.

#include "sporepedia_slot_release.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_sporepedia_slot_release {

// 0x00641e10, defined in the package's own translation unit. The header declares
// only the direct callee, so the reconstructed body is declared here with the same
// portable calling-convention spelling the package uses. The C language linkage
// puts the name in the global namespace, so every call below is unqualified -- the
// same entity, reached by a different route through the name lookup.
extern "C" unclassified_in_EAX PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL
sporepedia_dispatch_owned_slot_FUN_00641e10(void *receiver);

namespace {

// Machine displacements, not member names. 0x20 is the only receiver word the
// body reads, writes or passes by address, and it is the only displacement the
// machine-derived receiver record enumerates (receiver.offsets=[32], bounds_only).
constexpr std::size_t kReceiverWordOffset = 0x20u;
// 0x00641e26 MOV EDX,dword ptr [EAX + 0x4] -- displacement 4 of the block the
// slot read reaches, which is its second dword. The receiver record has no
// standing over that block: it is not the receiver.
constexpr std::size_t kSlotDisplacement = 4u;
constexpr std::size_t kSlotIndex = 1u;
// 0x00641e2c ADD EDI,0x4 -- the base adjustment forming the callee's first
// argument. The body hands the address over and never dereferences it.
constexpr std::size_t kFirstArgumentOffset = 4u;
// Two receiver words the record does not enumerate. Neither is reached in the
// original; they are planted in one test below so that a body which read a
// different displacement would be caught rather than pass silently.
constexpr std::size_t kBelowReceiverWordOffset = 0x18u;
constexpr std::size_t kAboveReceiverWordOffset = 0x24u;

static_assert(sizeof(void *) == 4u, "x86-32: a pointer and the word at 0x20 are the same four bytes");
static_assert(kSlotDisplacement == kSlotIndex * sizeof(OpaqueSlotTarget),
              "displacement 4 is the block's second dword, read as index 1");

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// Everything the two observers saw. Only what a stub was handed is recorded, plus
// the sequence numbers that fix the order of the two transfers. Nothing here
// names a member, a table, a slot target or a contract.
struct Observation {
  int step = 0;
  // the index-0 word of the block the slot read reaches
  int decoy_calls = 0;
  // the word at displacement 4 of that block, i.e. the one 0x00641e26 reads
  int slot_calls = 0;
  int slot_step = -1;
  const void *slot_this = nullptr;
  const void *slot_word = nullptr;
  // the pointee's own displacement-4 word. It is a distinct third address on
  // purpose: only a one-level read of 0x00641e24 would ever reach it.
  int pointee_slot_calls = 0;
  // a receiver word at a displacement the record does not enumerate
  int poison_calls = 0;
  // 0x005bf0e0
  int callee_calls = 0;
  int callee_step = -1;
  const void *callee_first = nullptr;
  const void *callee_second = nullptr;
  unclassified_in_EAX callee_result = 0u;
  // the receiver under test, so an observer can read it through the test's own
  // pointer. Neither stub receives it from the body.
  unsigned char *receiver = nullptr;
};

Observation g_obs;

// The block 0x00641e24 loads: two dwords, nothing more. 0x00641e26 takes its
// displacement 4 and 0x00641e29 transfers control through that; no record names
// it, and this test does not call it a vtable.
struct SlotBlock {
  OpaqueSlotTarget index0;  // displacement 0
  OpaqueSlotTarget index1;  // displacement 4
};

// The pointee the body holds in ECX at 0x00641e14.
//
// Its first word is the block 0x00641e24 loads. Its own displacement-4 word is a
// THIRD address, distinct from both words of that block, and it is planted to be
// the one the body must not reach: the slot comes out of the block, never out of
// the pointee itself. What that word is, and whether the original writes or even
// reads it, is not established by any record for this target -- no machine record
// enumerates the pointee's words -- and nothing is claimed about it beyond the one
// negative: the body's slot is not it.
struct Pointee {
  const SlotBlock *dispatch_word;  // offset 0 -- the block 0x00641e24 loads
  OpaqueSlotTarget displacement4;  // offset 4 -- never the slot
};

// A receiver large enough for the word at 0x20 and for the two words the first
// argument's base adjustment passes over. Filled with a non-zero byte so that a
// write to any displacement other than 0x20 is visible in the byte comparison,
// and so that the zero path has something other than zeroes to preserve.
struct Receiver {
  unsigned char bytes[256];
};

void fill_receiver(Receiver &receiver) {
  std::memset(receiver.bytes, 0xa5, sizeof receiver.bytes);
}

// The receiver is an opaque word-addressed block, so the test plants and reads
// words in it the same way the machine does: at a displacement, one word wide.
void plant_word(Receiver &receiver, std::size_t displacement, const void *value) {
  std::memcpy(receiver.bytes + displacement, &value, sizeof value);
}

const void *read_word(const unsigned char *base, std::size_t displacement) {
  const void *word = nullptr;
  std::memcpy(&word, base + displacement, sizeof word);
  return word;
}

}  // namespace

// 0x00641e26 reads displacement 4 of the block. A body that read displacement 0
// instead would transfer control here instead, and this counter would move.
extern "C" void PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL slot_index0_decoy(void *) {
  ++g_obs.decoy_calls;
}

// The pointee's own displacement-4 word, planted as a second decoy. 0x00641e24
// loads the pointee's FIRST word into EAX and 0x00641e26 reads displacement 4 of
// EAX, so the address the transfer reaches lives in the block the first word
// points at, never in the pointee. A model that read displacement 4 of the
// pointee instead -- one load where the listing has two -- would arrive here, and
// this counter is what would say so. Nothing else in the fixture can catch that
// mistake: the block's index 0 and index 1 are the other two candidate addresses,
// and neither of them is this one.
extern "C" void PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL slot_pointee_plus4(void *) {
  ++g_obs.pointee_slot_calls;
}

// 0x00641e24/0x00641e26/0x00641e29 -- the word at displacement 4. The observer
// is asked for two things and no more: which pointer it was handed in ECX, and
// what the receiver's word at 0x20 already reads when it is entered. The second
// is read through the test's own pointer to the receiver, not through anything
// the body passed. It records nothing about what the body should do next: the
// slot's own contract is unresolved for this target, and the model calls it
// through a typedef that returns void, so nothing is asserted here about the
// value the slot leaves behind.
extern "C" void PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL slot_displacement4(void *pointee) {
  ++g_obs.slot_calls;
  g_obs.slot_step = g_obs.step++;
  g_obs.slot_this = pointee;
  g_obs.slot_word = read_word(g_obs.receiver, kReceiverWordOffset);
}

// Reached only if the body acted on a receiver word the record does not
// enumerate, i.e. a displacement other than 0x20.
extern "C" void PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL slot_never_taken(void *) {
  ++g_obs.poison_calls;
}

// 0x005bf0e0, the one direct transfer, at 0x00641e30. The package's header
// declares this entity and nothing defines it, so this translation unit does;
// with C language linkage it is the same entity the package calls. The stub
// records the two pointers it is handed, in the order the pushes leave them
// (0x00641e2b pushes the address of the word at 0x20 first, 0x00641e2f pushes
// receiver+4 second, so receiver+4 is the first argument), and returns the word
// the test set. It does not dereference either pointer: what this callee does
// with the pair is an open question for this target, and reading through them
// here would be the test inventing an answer.
extern "C" unclassified_in_EAX PKG_SPOREPEDIA_SLOT_RELEASE_CDECL
FUN_005bf0e0(void *first, void *second) {
  ++g_obs.callee_calls;
  g_obs.callee_step = g_obs.step++;
  g_obs.callee_first = first;
  g_obs.callee_second = second;
  return g_obs.callee_result;
}

namespace {

// Builds the fixture every non-zero test uses: the receiver's word at 0x20 holds
// `pointee`, `pointee`'s first word points at `block`, `block` is
// { decoy_at_index_0, observer_at_index_1 }, and the pointee's OWN displacement-4
// word holds a third, distinct decoy.
//
// Three distinct addresses are in play, and which one the body reaches is the
// whole point of the fixture. The listing is two loads: 0x00641e24
// MOV EAX,dword ptr [ECX] takes the pointee's first word as the base, and
// 0x00641e26 MOV EDX,dword ptr [EAX + 0x4] takes displacement 4 of THAT, so the
// slot is block.index1. A one-level read -- taking displacement 4 of the
// pointee, which is what an identity cast at 0x00641e24 would produce -- would
// instead arrive at pointee.displacement4, the second decoy, which is a
// different function from both of the block's words. So the fixture discriminates
// the two-level load at 0x00641e24 from the one-level one, and the check on
// pointee_slot_calls is the one that says which happened.
void build_fixture(Receiver &receiver, SlotBlock &block, Pointee &pointee) {
  fill_receiver(receiver);
  block.index0 = &slot_index0_decoy;
  block.index1 = &slot_displacement4;
  pointee.dispatch_word = &block;
  pointee.displacement4 = &slot_pointee_plus4;
  plant_word(receiver, kReceiverWordOffset, &pointee);
}

void begin_run(unsigned char *receiver, unclassified_in_EAX result) {
  g_obs = Observation{};
  g_obs.receiver = receiver;
  g_obs.callee_result = result;
}

// 0x00641e24/0x00641e26/0x00641e29 and 0x00641e1e. The transfer reaches the
// block's index 1 and neither of the two decoys, the pointee arrives in ECX with
// nothing pushed, and the receiver's word at 0x20 already reads zero by then --
// which is 0x00641e1e having run before control left the body.
void test_the_slot_transfer_and_the_order_of_the_clear() {
  Receiver receiver;
  SlotBlock block;
  Pointee pointee;
  build_fixture(receiver, block, pointee);

  begin_run(receiver.bytes, 0u);
  sporepedia_dispatch_owned_slot_FUN_00641e10(receiver.bytes);

  check(g_obs.slot_calls == 1,
        "0x00641e24 loads the pointee's first word and 0x00641e26 takes its "
        "displacement 4, so 0x00641e29 transfers to the block's index 1, once");
  check(g_obs.pointee_slot_calls == 0,
        "0x00641e24 is a load: the slot is the block's displacement 4, never the "
        "pointee's own +0x4 word, which is a different function");
  check(g_obs.decoy_calls == 0,
        "0x00641e26 is displacement 4, not 0: the block's index 0 is never "
        "transferred to");
  check(g_obs.slot_this == &pointee,
        "0x00641e29 hands the pointee to the slot in ECX, with nothing pushed");
  check(g_obs.slot_word == nullptr,
        "0x00641e1e has already cleared the word at 0x20 when the slot is entered");
  check(g_obs.slot_step >= 0 && g_obs.slot_step < g_obs.callee_step,
        "the indirect transfer at 0x00641e29 precedes the direct one at 0x00641e30");
}

// 0x00641e1c JZ 0x00641e2b. A zero word takes the branch: the clear, the slot
// read and the transfer are all inside the skipped block, while the tail at
// 0x00641e2b..0x00641e30 is reached either way, so the direct callee still runs
// once. The body writes nothing at all on this path.
void test_the_zero_word_takes_the_jz_and_still_reaches_the_tail() {
  Receiver receiver;
  fill_receiver(receiver);
  plant_word(receiver, kReceiverWordOffset, nullptr);
  unsigned char before[sizeof receiver.bytes];
  std::memcpy(before, receiver.bytes, sizeof before);

  begin_run(receiver.bytes, 0x5a5a5a5au);
  const unclassified_in_EAX got =
      sporepedia_dispatch_owned_slot_FUN_00641e10(receiver.bytes);

  check(g_obs.slot_calls == 0,
        "0x00641e1c JZ skips the block: no slot word is read and none is called");
  check(g_obs.decoy_calls == 0 && g_obs.pointee_slot_calls == 0,
        "on the zero path no address of the pointee's block, and no address of "
        "the pointee itself, is transferred to");
  check(g_obs.callee_calls == 1,
        "the tail at 0x00641e2b runs on both paths, so 0x00641e30 runs exactly once");
  check(g_obs.callee_first == receiver.bytes + kFirstArgumentOffset,
        "the first argument is receiver+4, the base adjustment at 0x00641e2c");
  check(g_obs.callee_second == receiver.bytes + kReceiverWordOffset,
        "the second argument is &receiver[0x20], the address taken at 0x00641e17");
  check(got == 0x5a5a5a5au,
        "the word left in EAX at 0x00641e3a is the word 0x005bf0e0 returned");
  check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
        "the zero path writes no byte of the receiver: 0x00641e1e is inside the skipped block");
}

// 0x00641e2b/0x00641e2c/0x00641e2f/0x00641e30 on the non-null path: the same
// callee, the same pair of pointers, once. Together with 0x00641e1e being the
// body's only write, this is the whole mutation the body performs on the
// receiver, so the byte comparison is stated as the full expected image.
void test_the_non_null_path_calls_the_callee_once_with_the_same_pair() {
  Receiver receiver;
  SlotBlock block;
  Pointee pointee;
  build_fixture(receiver, block, pointee);
  unsigned char before[sizeof receiver.bytes];
  std::memcpy(before, receiver.bytes, sizeof before);
  const Pointee pointee_before = pointee;
  const SlotBlock block_before = block;

  begin_run(receiver.bytes, 0x00c0ffeeu);
  const unclassified_in_EAX got =
      sporepedia_dispatch_owned_slot_FUN_00641e10(receiver.bytes);

  check(g_obs.callee_calls == 1,
        "0x00641e30 is reached once on the non-null path as well");
  check(g_obs.callee_first == receiver.bytes + kFirstArgumentOffset,
        "the first argument is receiver+4, the base adjustment at 0x00641e2c");
  check(g_obs.callee_second == receiver.bytes + kReceiverWordOffset,
        "the second argument is &receiver[0x20], the address taken at 0x00641e17");
  check(got == 0x00c0ffeeu,
        "the word left in EAX at 0x00641e3a is the word 0x005bf0e0 returned");

  // 0x00641e1e is the only write in the body, and it writes one word at 0x20.
  // Every other byte must come back exactly as it went in, including the two
  // poison words of the next test -- this receiver has no poison words, so the
  // expectation is: before, with four bytes of zero at 0x20.
  unsigned char expected[sizeof receiver.bytes];
  std::memcpy(expected, before, sizeof expected);
  std::memset(expected + kReceiverWordOffset, 0, sizeof(void *));
  check(std::memcmp(expected, receiver.bytes, sizeof receiver.bytes) == 0,
        "the only receiver bytes that change are the four at 0x20");
  check(read_word(receiver.bytes, kReceiverWordOffset) == nullptr,
        "the word at 0x20 is null once the body returns");
  // 0x00641e24 and 0x00641e26 read the pointee and its block; the listing
  // stores nothing in either, so both must come back byte for byte. The block is
  // checked as well as the pointee because the slot address is read out of it.
  check(std::memcmp(&pointee_before, &pointee, sizeof pointee) == 0,
        "no word of the pointee is written: 0x00641e24 and 0x00641e26 only read it");
  check(std::memcmp(&block_before, &block, sizeof block) == 0,
        "no word of the block is written: the slot is read out of it, not stored to it");
}

// 0x20 is the only receiver displacement the body acts on, and this is the
// behavioural restatement of it: three receiver words are planted, one at 0x20
// and two at displacements the machine-derived receiver record does not
// enumerate, and only the one at 0x20 may be dispatched through.
//
// Each poison pointee gets its own block as well as its own +0x4 word, so that a
// body which read either of those displacements -- as a one-level read or as the
// two-level one -- arrives at slot_never_taken and is caught, instead of landing
// on the real observer by accident.
void test_only_the_0x20_receiver_word_is_acted_on() {
  Receiver receiver;
  SlotBlock block;
  SlotBlock poison_block;
  Pointee at_0x20;
  Pointee below;
  Pointee above;
  build_fixture(receiver, block, at_0x20);
  poison_block.index0 = &slot_index0_decoy;
  poison_block.index1 = &slot_never_taken;
  below.dispatch_word = &poison_block;
  below.displacement4 = &slot_never_taken;
  above.dispatch_word = &poison_block;
  above.displacement4 = &slot_never_taken;
  plant_word(receiver, kBelowReceiverWordOffset, &below);
  plant_word(receiver, kAboveReceiverWordOffset, &above);

  begin_run(receiver.bytes, 0u);
  sporepedia_dispatch_owned_slot_FUN_00641e10(receiver.bytes);

  check(g_obs.slot_calls == 1,
        "the pointee planted at 0x20 is the one that is dispatched");
  check(g_obs.poison_calls == 0,
        "a receiver word at 0x18 or 0x24 is never read: 0x20 is the only receiver displacement");
  check(g_obs.pointee_slot_calls == 0,
        "the +0x4 word of the pointee planted at 0x20 is not the slot either");
}

// The displacement pins, restated at run time so the fixture above cannot drift
// away from the listing. A failure here means the constants this test builds its
// words with no longer say what the machine says.
void test_the_displacement_pins() {
  check(sizeof(void *) == 4u,
        "a pointer is one word, so the word the body writes at 0x20 is four bytes");
  check(kReceiverWordOffset == 0x20u,
        "0x20 is the only receiver displacement the machine-derived record enumerates");
  check(kSlotDisplacement == 4u, "the slot's displacement is 4, from MOV EDX,[EAX+0x4]");
  check(kSlotDisplacement == kSlotIndex * sizeof(OpaqueSlotTarget),
        "displacement 4 is the block's second dword, read as index 1");
  check(kFirstArgumentOffset == 4u,
        "0x00641e2c forms receiver+4, and the body never dereferences it");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_sporepedia_slot_release

int main() {
  using namespace openspore::reconstruction::pkg_sporepedia_slot_release;
  test_the_slot_transfer_and_the_order_of_the_clear();
  test_the_zero_word_takes_the_jz_and_still_reaches_the_tail();
  test_the_non_null_path_calls_the_callee_once_with_the_same_pair();
  test_only_the_0x20_receiver_word_is_acted_on();
  test_the_displacement_pins();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
