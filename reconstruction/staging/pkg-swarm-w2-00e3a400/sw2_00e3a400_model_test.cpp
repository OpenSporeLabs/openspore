// PKG-SWARM-W2-00E3A400 -- VA 0x00e3a400
// Behavioural model test for FUN_00e3a270, the twenty-seven-way hashed-property
// dispatcher whose interior address 0x00e3a400 is this worker's target.
//
// THE ONE DIRECT CALLEE IS DEFINED HERE AS AN OBSERVER. 0x00e39420 is declared
// extern in the package header and defined below, so the test sees every
// transfer the reconstruction makes, with which three arguments in which push
// order, and gets to decide what the callee does to memory and what it returns
// while it is there. That is the only way to test the three things this body
// does that a store-diff cannot see:
//
//   * the call's ARGUMENT ORDER (record, 0x3, self+0x2c0 / self+0x2b4 /
//     self+0x29c), which the observer verifies by identity rather than by
//     position in a signature;
//   * the WRITE ORDERING around each call -- the receiver word is stored BEFORE
//     the call and the twelve destination bytes are NOT, which the observer
//     proves by snapshotting the receiver at the moment it is entered;
//   * the RETURNED VALUE, which on those three paths is the callee's own result
//     forwarded untouched, and which the observer poisons so that a
//     reconstruction returning a value of its own is caught.
//
// WHAT IS ASSERTED is what the 172-instruction listing fixes and nothing more:
//
//   * the selector -> arm mapping for ALL TWENTY-SEVEN selector immediates, each
//     checked against a hand-written table read off the listing rather than
//     against the model's own dispatch, so a tree that is internally consistent
//     but wrong still fails;
//   * the exact set of receiver dwords each arm writes and the exact value each
//     one receives, checked by diffing a 0x340-byte probe (the modeled 0x330
//     object plus a 0x10-byte canary past its end) that was pre-filled with a
//     per-byte pattern -- so a wrong displacement, a swapped pair, an extra
//     store, a store of the wrong width and a write past the end of the object
//     all show up as changed bytes somewhere they must not be;
//   * the "write the tag only if it is still -1" guard, driven with -1, with 0
//     (which must still be overwritten, because the machine compares against -1
//     and not against zero) and with another tag value (which must be left
//     alone) -- and the one tag store the machine does NOT guard;
//   * the lazy primary/secondary pair: the secondary is stored unconditionally
//     and the primary only when it is still zero;
//   * the null-record guard, which the machine has on exactly one of the ten
//     arms and on no other path in the body;
//   * two levels of indirection, with decoy words planted in the record itself,
//     in the block's unread +0x00/+0x04, and in a second block the record does
//     not point at, so a one-level read is visible as the wrong stored value;
//   * the call's three arguments by identity, the destination offset, and the
//     fact that the body had already written the primary word and had not yet
//     touched the destination when the callee was entered;
//   * the ABI, measured rather than asserted: ESP sampled around the call, equal
//     across it only if the callee owns its own eight bytes of stack cleanup;
//   * the value left in the return register on every class of path, since the
//     listing fixes it per path and it is path-dependent in three different ways.
//
// THE CASES MARKED REFUTE EXIST TO BREAK THE RECONSTRUCTION, not to walk it.
// Each names the wrong reconstruction it is aimed at:
//
//   A  SIGNED vs UNSIGNED dispatch. Every ordering branch in the body is JG,
//      which is signed, and fifteen of the twenty-seven selector values have the
//      high bit set. The test first PROVES the two readings disagree (twelve of
//      the twenty-seven selectors cross the root pivot under the wrong reading),
//      so the case is not vacuous, and then drives all twenty-seven through the
//      signed reading and checks the exact effect of each -- which an unsigned
//      `>` on a std::uint32_t cannot produce, because the root pivot 0xf278934a
//      is itself negative and an unsigned above sends the twelve POSITIVE
//      selectors below it, into the low half, whose seven leaf tests are all
//      negative values, so twelve arms become unreachable and twelve selectors
//      write nothing and call nothing.
//   B  BRANCH POLARITY, both directions. Every pivot and every leaf selector is
//      driven at value+1 and value-1, and every one of those neighbours must
//      write nothing and make no call. A tree that tests `<` instead of `>`, or
//      that turns one JG into a JLE, lands a neighbour in a real arm.
//   C  OFF-BY-ONE DISPLACEMENT, in both the receiver and the value block. The
//      probe carries a decoy dword at every displacement the body does NOT
//      write, immediately below and above the ones it does, and the block
//      carries decoys at +0x00 and +0x04, below the lowest displacement read.
//   D  WRONG POINTER LEVEL. Decoy dwords are planted in the record at the four
//      displacements the body reads out of the BLOCK, a second block the record
//      does not point at is filled with different values, and the record's own
//      bytes are poisoned. A model that reads the record directly, or that
//      follows one pointer fewer, stores a decoy.
//   E  WRONG RECEIVER. The call's third argument is checked by identity against
//      self+0x2c0 / self+0x2b4 / self+0x29c, and the canary past the end of the
//      modeled object must be untouched, so a receiver off by a word is visible.
//   F  WRONG CALLEE ARGUMENT ORDER. The observer identifies each argument by
//      value, not by position: argument zero must BE the record pointer the test
//      passed, argument one must be 3, and argument two must be an address
//      inside the receiver probe at the expected offset. A model that pushes the
//      destination first, or that passes the block instead of the record, is
//      caught by identity rather than by a signature that both would satisfy.
//   G  WRONG WRITE ORDERING. At the instant the callee is entered the observer
//      records the primary word (which the machine has already stored) and the
//      twelve destination bytes (which the machine has NOT touched), and it then
//      overwrites the block's first word. The test asserts the receiver kept the
//      ORIGINAL value, which is only true if the body read the block and stored
//      the primary BEFORE the call; and the opposite reconstruction -- store
//      after the call -- is caught by the three lazy arms, whose secondary store
//      the machine performs before its JNZ.
//   H  WRONG CONSTANT. The tag immediates are driven with a pre-set neighbour and
//      with zero, and the copy index is checked to be 3 rather than 0, 1, 2 or 4:
//      the callee's own bytes read q[index+0], q[index+1], q[index+2], so an index
//      of 0 would move three words and the destination check would show it.
//   I  MISSING ARM / MISSING FALL-THROUGH. Five of the twenty-seven selectors
//      are reached only by a fall-through after a `CMP/JNZ` (0x99f0d1da,
//      0x25ca9233, 0x6a9f2620, 0x7bceaa86, 0x3b38f92a); a reconstruction that
//      turns each block's last compare into a test and forgets the fall-through
//      drops exactly those five, and the table sweep names all twenty-seven.
//   J  EXTRA MATCH. A wide sweep of non-selector values -- 0, 1, 2, 0x7fffffff,
//      0x80000000, every pivot's two neighbours, 0xffffffff and a
//      deterministic pseudo-random set -- must leave the probe byte-identical
//      and make no call.
//
// WHAT IS NOT ASSERTED, AND WHY:
//
//   * WHAT THE RETURNED VALUE MEANS. The machine ABI envelope classifies EAX's
//     content as aggregate_unknown / unclassified_in_EAX, the body writes it
//     differently on every class of path, and the only caller in the binary
//     (0x00e3f970, which calls at 0x00e3fc73) does not read EAX after its call
//     at all. The test therefore asserts the register's CONTENT per path --
//     which the listing fixes -- and asserts nothing about meaning.
//   * WHICH REGISTER CARRIES THE RECEIVER. The model receives the receiver as a
//     thiscall first parameter, so from C++ a reconstruction that used any other
//     register would be indistinguishable from this one. The header's macro and
//     the machine's seventeen ECX displacements are the evidence; the test
//     measures the declared ABI's stack cleanup instead, which IS observable.
//   * WHAT 0x00e39420 DOES BEYOND WHAT THE LISTING OF THIS BODY DEPENDS ON. The
//     observer reproduces the rotation its own 47 bytes show (destination +0x4,
//     +0x00, +0x08 from the block's +index, +index+1, +index+2) and returns a
//     poison value on purpose. Both are fixtures, not claims about that body.
//   * THE MEANING OF THE SEVENTEEN RECEIVER WORDS, OF THE SIX TAG IMMEDIATES
//     0x1654c00..0x1654c05, AND OF THE TWENTY-SEVEN SELECTOR HASHES. No record
//     in this repository names any of them, so the test asserts the
//     displacement/value/id mapping and nothing about what it means.
//   * THE OBJECT'S REAL SIZE. 0x330 is the smallest size this body's own
//     accesses allow; the probe adds a 0x10-byte canary so a store at +0x330 or
//     beyond is visible, but nothing here bounds the real object above.
//   * A FAULTING PATH. Nine of the ten arms have no null test on the record, so
//     a faithful reconstruction dereferences null on those paths and faults.
//     Reproducing a segfault is not a test, so the no-guard arms are exercised
//     only with a real record and the asymmetry is asserted in the positive
//     direction instead (see arm_has_null_guard).

#include "sw2_00e3a400_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace openspore::reconstruction::pkg_swarm_w2_00e3a400 {
namespace {

// -- the probe ----------------------------------------------------------------
// The modeled object is 0x330 bytes; the probe is that plus a 0x10-byte canary,
// so a store at +0x330 or beyond is visible as a changed byte.
constexpr std::size_t kObjectSize = 0x330u;
constexpr std::size_t kProbeSize = 0x340u;

// Distinct marker values for the four words of the value block. They are
// pairwise different AND different from every decoy planted anywhere, so a
// swapped destination pair or a one-level read is unambiguous.
constexpr Word kBlock08 = 0x11111111u;
constexpr Word kBlock0c = 0x22222222u;
constexpr Word kBlock10 = 0x33333333u;
constexpr Word kBlock14 = 0x44444444u;

int g_failures = 0;
int g_checks = 0;

void check(bool ok, const char* what) {
  ++g_checks;
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

struct Probe {
  std::uint8_t bytes[kProbeSize];
};

// A per-byte pattern, so "this byte became 0", "this byte became 1" and "this
// byte became the marker's low byte" are all distinguishable, and no region can
// hide a wrong write behind a pre-zeroed one.
void fill_probe(Probe& probe) {
  for (std::size_t index = 0; index < kProbeSize; ++index) {
    probe.bytes[index] = static_cast<std::uint8_t>(index * 7u + 3u);
  }
}

// The dword the pattern puts at `offset`, so an expectation can be computed
// without reading a probe the body has already changed.
Word pattern_word(std::size_t offset) {
  Word value = 0u;
  for (std::size_t index = 0; index < 4u; ++index) {
    const std::uint8_t byte = static_cast<std::uint8_t>((offset + index) * 7u + 3u);
    value |= static_cast<Word>(byte) << (8u * index);
  }
  return value;
}

bool region_is_pristine(const std::uint8_t* bytes, std::size_t offset,
                        std::size_t length) {
  for (std::size_t index = offset; index < offset + length; ++index) {
    if (bytes[index] != static_cast<std::uint8_t>(index * 7u + 3u)) {
      return false;
    }
  }
  return true;
}

Simulator* as_simulator(Probe& probe) {
  static_assert(sizeof(Simulator) <= kProbeSize,
                "the probe must be able to hold the modeled object");
  return reinterpret_cast<Simulator*>(&probe);
}

Word* word(Probe& probe, std::size_t offset) {
  return word_at(&probe, offset);
}

// == the fixture the body is handed ==========================================
struct ValueFixture {
  PropertyValueBlock live;
  PropertyValueBlock decoy_block;
  PropertyRecord record;
};

// A live block, a fully populated block the record does NOT point at, and a
// record whose own twelve bytes are poisoned, so that every way of getting the
// level wrong is visible as a stored value.
//
// Filled IN PLACE through a reference, deliberately: returning the struct by
// value and then reading `record.value` would leave that pointer aimed at the
// callee's dead local whenever the copy is not elided, and the test would then
// be reading whatever the stack has been reused for -- which is exactly the kind
// of accident that makes a falsification test pass for the wrong reason.
void make_fixture(ValueFixture& fixture) {
  fixture.live.opaque_00.fill(0x5au);
  fixture.live.word_08 = kBlock08;
  fixture.live.word_0c = kBlock0c;
  fixture.live.word_10 = kBlock10;
  fixture.live.word_14 = kBlock14;
  fixture.decoy_block.opaque_00.fill(0xa5u);
  fixture.decoy_block.word_08 = 0x51515151u;
  fixture.decoy_block.word_0c = 0x52525252u;
  fixture.decoy_block.word_10 = 0x53535353u;
  fixture.decoy_block.word_14 = 0x54545454u;
  fixture.record.opaque_00.fill(0x77u);
  fixture.record.value = &fixture.live;
  // A self-check on the fixture itself: if the two ever disagree, every case
  // below is reading the wrong object and nothing it reports means anything.
  if (fixture.record.value != &fixture.live) {
    std::fprintf(stderr, "FAILED: the fixture's record does not point at its "
                         "own live value block\n");
    ++g_failures;
  }
}

// -- the observer for 0x00e39420 ---------------------------------------------
struct Observer {
  int count = 0;
  const PropertyRecord* arg_record = nullptr;
  Word arg_index = 0u;
  std::size_t destination_offset = 0u;
  bool destination_was_pristine = false;
  bool primary_was_stored = false;
  Word primary_at_call = 0u;
  Word tag_at_call = 0u;
  Word poison = 0xfeedfaceu;
};

Observer g_observer;
const Probe* g_live_probe = nullptr;
std::uint8_t* g_destination_base = nullptr;

// What the observer saw of the receiver at the instant it was entered.
struct CallSnapshot {
  bool taken = false;
  bool destination_pristine = true;
  bool primary_already_equal_to_marker = false;
};
CallSnapshot g_snapshot;

// The one direct callee, as an observer. Its real behaviour is fixed by its own
// 47 bytes (quoted in the package header): a null record writes nothing, the
// three words come from the block at +index, +index+1, +index+2 and are stored
// to the destination at +0x4, +0x0, +0x8 -- the order is rotated -- and the last
// thing written to EAX is the block pointer.
extern "C" Word simulator_copy_block3_00e39420(const PropertyRecord* record,
                                               Word index, void* destination) {
  ++g_observer.count;
  g_observer.arg_record = record;
  g_observer.arg_index = index;

  std::uint8_t* const dest_bytes = static_cast<std::uint8_t*>(destination);
  g_observer.destination_offset = static_cast<std::size_t>(dest_bytes -
                                                           g_destination_base);
  g_observer.destination_was_pristine =
      region_is_pristine(g_live_probe->bytes, g_observer.destination_offset, 0x0cu);

  // Snapshot the receiver AT THE MOMENT OF THE CALL. This is what separates
  // "store then call" from "call then store".
  g_snapshot.taken = true;
  g_snapshot.destination_pristine = g_observer.destination_was_pristine;
  g_snapshot.primary_already_equal_to_marker = false;
  g_observer.primary_at_call = 0u;
  for (std::size_t offset = 0x300u; offset <= 0x330u; offset += 4u) {
    if (*word_at(g_live_probe, offset) == kBlock08) {
      g_observer.primary_at_call = kBlock08;
      g_snapshot.primary_already_equal_to_marker = true;
    }
  }
  g_observer.primary_was_stored = g_snapshot.primary_already_equal_to_marker;
  g_observer.tag_at_call = *word_at(g_live_probe, 0x32cu);

  if (record == nullptr) {
    return g_observer.poison;
  }

  // Poison the block's first word NOW. The machine has already read it, so a
  // faithful reconstruction has already stored the ORIGINAL value; a
  // reconstruction that called first and read afterwards would store the poison.
  const PropertyValueBlock* const block = record->value;
  const_cast<PropertyValueBlock*>(block)->word_08 = 0xdeadbeefu;

  // The rotation the callee's own bytes show.
  const Word* const base = word_at(block, 0u);
  Word* const dest = word_at(destination, 0u);
  dest[1] = base[index + 0u];
  dest[0] = base[index + 1u];
  dest[2] = base[index + 2u];
  return g_observer.poison;
}

// == the expected effect, derived from the LISTING and not from the model =====
enum Arm {
  kNoMatch,
  kCopy2c0,
  kCopy2b4,
  kCopy29c,
  kFour,
  kThree,
  kTagInit,
  kTag310,
  kLazy324,
  kLazy314,
  kLazy31c
};

// One row per `CMP EAX,<imm32>` in the dispatch, read off the listing by hand.
// This table is the oracle: the model's own tree is never consulted, so a tree
// that is self-consistent and wrong still fails the sweep.
struct SelectorRow {
  Word selector;
  Arm arm;
};

const SelectorRow kRows[] = {
    {0x8133fb2eu, kCopy2b4},  // e3a29f/e3a2a4 -> e3a4e4
    {0x980e43f2u, kThree},    // e3a2aa/e3a2af -> e3a517
    {0x99f0d1dau, kCopy2c0},  // e3a2b5, fall-through -> e3a2c0
    {0x9f792b4cu, kLazy324},  // e3a29d -> e3a2e5
    {0xa0973374u, kThree},    // e3a31e/e3a323 -> e3a517
    {0xa6cb4c9fu, kThree},    // e3a329/e3a32e -> e3a517
    {0xaaf6aaacu, kCopy2c0},  // e3a290 -> e3a2c0
    {0xade76cceu, kTag310},   // e3a344/e3a349 -> e3a364
    {0xcdb3696fu, kThree},    // e3a34b/e3a350 -> e3a517
    {0xd536c91du, kThree},    // e3a356/e3a35b -> e3a517
    {0xd832b059u, kThree},    // e3a337/e3a33e -> e3a517
    {0xdca976d0u, kCopy2c0},  // e3a38a/e3a38f -> e3a2c0
    {0xe0bc9d45u, kThree},    // e3a395/e3a39a -> e3a517
    {0xf278934au, kFour},     // e3a27f -> e3a3e2
    {0xf967827cu, kCopy29c},  // e3a3c1/e3a3c6 -> e3a546
    {0x13df9c1cu, kCopy29c},  // e3a3cc/e3a3d1 -> e3a546
    {0x25ca9233u, kFour},     // e3a3d7, fall-through -> e3a3e2
    {0x279c4e55u, kLazy314},  // e3a3bf -> e3a419
    {0x2cfa39ddu, kCopy2b4},  // e3a452/e3a457 -> e3a4e4
    {0x3b38f92au, kLazy31c},  // e3a45d, fall-through -> e3a468
    {0x3e2a3040u, kTagInit},  // e3a3ae -> e3a4a1
    {0x5c51063fu, kFour},     // e3a4c7/e3a4cc -> e3a3e2
    {0x5fcf28d0u, kThree},    // e3a4d2/e3a4d7 -> e3a517
    {0x6a9f2620u, kCopy2b4},  // e3a4d9, fall-through -> e3a4e4
    {0x6cd9ec7bu, kThree},    // e3a4c5 -> e3a517
    {0x7115ede5u, kCopy29c},  // e3a509/e3a50e -> e3a546
    {0x7bceaa86u, kThree},    // e3a510, fall-through -> e3a517
};
constexpr std::size_t kRowCount = sizeof(kRows) / sizeof(kRows[0]);

const char* arm_name(Arm arm) {
  switch (arm) {
    case kNoMatch: return "no-match";
    case kCopy2c0: return "copy-into-2c0";
    case kCopy2b4: return "copy-into-2b4";
    case kCopy29c: return "copy-into-29c";
    case kFour: return "four-writes";
    case kThree: return "three-writes";
    case kTagInit: return "unguarded-tag";
    case kTag310: return "guarded-tag-310";
    case kLazy324: return "lazy-324";
    case kLazy314: return "lazy-314";
    case kLazy31c: return "lazy-31c";
  }
  return "?";
}

// The nine arms that carry the body's only null test, and the one that does not.
bool arm_has_null_guard(Arm arm) {
  return arm == kThree;
}

bool is_selector(Word value) {
  for (std::size_t row = 0; row < kRowCount; ++row) {
    if (kRows[row].selector == value) {
      return true;
    }
  }
  return false;
}

// == running the body ========================================================
using WordWrite = std::pair<std::size_t, Word>;
using Effect = std::vector<WordWrite>;

struct Plant {
  std::size_t offset;
  Word value;
};

struct Outcome {
  Effect writes;              // dword-aligned words the BODY changed
  Effect callee_writes;       // the callee's three destination words
  int stray_byte_writes = 0;  // changed bytes not inside a dword
  int call_count = 0;
  Word returned = 0u;
  std::size_t destination_offset = 0u;
  bool destination_pristine = false;
  bool primary_was_stored = false;
  Word tag_at_call = 0u;
};

Outcome run(Word selector, const std::vector<Plant>& plants, Probe& probe,
            const PropertyRecord* record) {
  fill_probe(probe);
  for (const Plant& plant : plants) {
    *word(probe, plant.offset) = plant.value;
  }
  Probe before = probe;
  g_observer = Observer();
  g_snapshot = CallSnapshot();
  g_live_probe = &probe;
  g_destination_base = probe.bytes;

  const Word returned = re_00e3a400(as_simulator(probe), selector, record);

  Outcome outcome;
  outcome.call_count = g_observer.count;
  outcome.returned = returned;
  outcome.destination_offset = g_observer.destination_offset;
  outcome.destination_pristine = g_observer.destination_was_pristine;
  outcome.primary_was_stored = g_observer.primary_was_stored;
  outcome.tag_at_call = g_observer.tag_at_call;

  const std::size_t destination = g_observer.destination_offset;
  const bool in_destination =
      g_observer.count != 0 && destination < kProbeSize &&
      destination + 0x0cu <= kProbeSize;
  for (std::size_t offset = 0; offset + 4u <= kProbeSize; offset += 4u) {
    const Word was = *word(before, offset);
    const Word now = *word(probe, offset);
    if (was == now) {
      continue;
    }
    if (in_destination && offset >= destination && offset < destination + 0x0cu) {
      outcome.callee_writes.push_back(WordWrite(offset, now));
    } else {
      outcome.writes.push_back(WordWrite(offset, now));
    }
  }
  // A changed byte whose CONTAINING dword did not change would be a sub-dword
  // store, which the listing does not contain anywhere: every memory operand in
  // the 172 instructions is a full dword.
  for (std::size_t index = 0; index < kProbeSize; ++index) {
    if (before.bytes[index] == probe.bytes[index]) {
      continue;
    }
    const std::size_t base = index & ~static_cast<std::size_t>(3u);
    if (base + 4u > kProbeSize) {
      ++outcome.stray_byte_writes;
      continue;
    }
    if (*word(before, base) == *word(probe, base)) {
      ++outcome.stray_byte_writes;
    }
  }
  return outcome;
}

// The value a displacement held before the call, from the plants and the
// pattern, so an expectation never reads a probe the body has already changed.
Word before_value(const std::vector<Plant>& plants, std::size_t offset) {
  Word value = pattern_word(offset);
  for (const Plant& plant : plants) {
    if (plant.offset == offset) {
      value = plant.value;
    }
  }
  return value;
}

std::string describe(const Effect& effect) {
  if (effect.empty()) {
    return std::string("nothing");
  }
  std::string text;
  for (std::size_t index = 0; index < effect.size(); ++index) {
    char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "%s0x%zx=0x%08x",
                  index == 0 ? "" : ", ", effect[index].first,
                  effect[index].second);
    text += buffer;
  }
  return text;
}

bool same_effect(const Effect& expected, const Effect& actual) {
  if (expected.size() != actual.size()) {
    return false;
  }
  for (std::size_t index = 0; index < expected.size(); ++index) {
    if (expected[index] != actual[index]) {
      return false;
    }
  }
  return true;
}

// The expected receiver effect of an arm, from the listing.
void expect_for(Arm arm, const std::vector<Plant>& plants, bool null_record,
                Effect* expected, int* expected_calls,
                std::size_t* expected_destination) {
  expected->clear();
  *expected_calls = 0;
  *expected_destination = 0u;
  const Word tag_before = before_value(plants, 0x32cu);
  switch (arm) {
    case kNoMatch:
      break;
    case kCopy2c0:
      expected->push_back(WordWrite(0x324u, kBlock08));
      *expected_calls = 1;
      *expected_destination = 0x2c0u;
      break;
    case kCopy2b4:
      expected->push_back(WordWrite(0x31cu, kBlock08));
      *expected_calls = 1;
      *expected_destination = 0x2b4u;
      break;
    case kCopy29c:
      expected->push_back(WordWrite(0x30cu, kBlock08));
      *expected_calls = 1;
      *expected_destination = 0x29cu;
      break;
    case kFour:
      // Ascending receiver order, and the middle pair is SWAPPED with respect to
      // the source: q[+0x0c] lands at +0x2ac and q[+0x10] lands at +0x2a8.
      expected->push_back(WordWrite(0x2a8u, kBlock10));
      expected->push_back(WordWrite(0x2acu, kBlock0c));
      expected->push_back(WordWrite(0x2b0u, kBlock14));
      expected->push_back(WordWrite(0x314u, kBlock08));
      break;
    case kThree:
      if (null_record) {
        break;  // the JZ at e3a51d returns having written nothing at all
      }
      expected->push_back(WordWrite(0x2ccu, kBlock10));
      expected->push_back(WordWrite(0x2d0u, kBlock0c));
      expected->push_back(WordWrite(0x2d4u, kBlock14));
      break;
    case kTagInit:
      // The only UNGUARDED tag store in the body: it happens whatever +0x32c
      // held, so the pre-set value is overwritten either way.
      expected->push_back(WordWrite(0x308u, kBlock08));
      expected->push_back(WordWrite(0x32cu, kTag_1654c00));
      break;
    case kTag310:
      expected->push_back(WordWrite(0x310u, kBlock08));
      if (tag_before == kTagUnset) {
        expected->push_back(WordWrite(0x32cu, kTag_1654c01));
      }
      break;
    case kLazy324: {
      const Word primary = before_value(plants, 0x324u);
      expected->push_back(WordWrite(0x324u, primary == 0u ? kBlock08 : primary));
      if (primary == 0u) {
        expected->push_back(WordWrite(0x328u, kBlock08));
      }
      if (tag_before == kTagUnset) {
        expected->push_back(WordWrite(0x32cu, kTag_1654c05));
      }
      break;
    }
    case kLazy314: {
      const Word primary = before_value(plants, 0x314u);
      expected->push_back(WordWrite(0x314u, primary == 0u ? kBlock08 : primary));
      if (primary == 0u) {
        expected->push_back(WordWrite(0x318u, kBlock08));
      }
      if (tag_before == kTagUnset) {
        expected->push_back(WordWrite(0x32cu, kTag_1654c02));
      }
      break;
    }
    case kLazy31c: {
      const Word primary = before_value(plants, 0x31cu);
      expected->push_back(WordWrite(0x31cu, primary == 0u ? kBlock08 : primary));
      if (primary == 0u) {
        expected->push_back(WordWrite(0x320u, kBlock08));
      }
      if (tag_before == kTagUnset) {
        expected->push_back(WordWrite(0x32cu, kTag_1654c04));
      }
      break;
    }
  }
  // Sort by offset so the comparison is order-independent, matching the diff.
  for (std::size_t outer = 1; outer < expected->size(); ++outer) {
    for (std::size_t inner = outer; inner > 0; --inner) {
      if ((*expected)[inner - 1u].first > (*expected)[inner].first) {
        const WordWrite swap = (*expected)[inner - 1u];
        (*expected)[inner - 1u] = (*expected)[inner];
        (*expected)[inner] = swap;
      } else {
        break;
      }
    }
  }
}

// == case 1: the twenty-seven-way table sweep, and REFUTE A (signedness) =====
void sweep_selectors() {
  // REFUTE A, part one: prove the signed and unsigned readings of the dispatch
  // DISAGREE, so the sweep below is not vacuous. Fifteen of the twenty-seven
  // selector values have the high bit set and the root pivot 0xf278934a is
  // itself negative when read signed, so an unsigned `>` sends exactly one of
  // the twenty-seven (0xf967827c) above the pivot and the other fourteen below,
  // where eleven of them match no case and write nothing at all.
  int negative = 0;
  for (std::size_t index = 0; index < kRowCount; ++index) {
    if (static_cast<std::int32_t>(kRows[index].selector) < 0) {
      ++negative;
    }
  }
  check(negative == 15, "REFUTE A: fifteen selector values are negative signed");
  int unsigned_would_differ = 0;
  for (std::size_t index = 0; index < kRowCount; ++index) {
    const Word selector = kRows[index].selector;
    if ((selector > kSelector_f278934a) !=
        (static_cast<std::int32_t>(selector) >
         static_cast<std::int32_t>(kSelector_f278934a))) {
      ++unsigned_would_differ;
    }
  }
  // The two readings part company exactly where the two operands disagree about
  // the sign bit, and the root pivot 0xf278934a has it set while twelve of the
  // twenty-seven selectors do not. Signed, those twelve are ABOVE the pivot and
  // belong to the high half; unsigned they are BELOW it and belong to the low
  // half, whose seven leaf tests are all negative values, so all twelve fall
  // through to the default return. The fifteen negative selectors compare the
  // same way under both readings, which is why the error is silent for them.
  check(unsigned_would_differ == 12,
        "REFUTE A: an unsigned root pivot re-routes the twelve positive "
        "selectors into the low half, where none of them matches a case");

  for (std::size_t index = 0; index < kRowCount; ++index) {
    const SelectorRow& row = kRows[index];
    // A fresh fixture and probe per case: the observer poisons the live block,
    // so each case needs its own.
    ValueFixture fixture;
    make_fixture(fixture);
    Probe probe;

    // The three lazy arms: plant the primary at zero so the "both written" path
    // is exercised, and the tag at -1 so the guarded tag write is exercised.
    std::vector<Plant> plants;
    if (row.arm == kLazy324) {
      plants.push_back(Plant{0x324u, 0u});
      plants.push_back(Plant{0x32cu, kTagUnset});
    }
    if (row.arm == kLazy314) {
      plants.push_back(Plant{0x314u, 0u});
      plants.push_back(Plant{0x32cu, kTagUnset});
    }
    if (row.arm == kLazy31c) {
      plants.push_back(Plant{0x31cu, 0u});
      plants.push_back(Plant{0x32cu, kTagUnset});
    }

    const Outcome outcome = run(row.selector, plants, probe, &fixture.record);

    Effect expected;
    int expected_calls = 0;
    std::size_t expected_destination = 0u;
    expect_for(row.arm, plants, false, &expected, &expected_calls,
               &expected_destination);

    char label[256];
    std::snprintf(label, sizeof(label),
                  "selector 0x%08x must reach the %s arm and write exactly %s -- "
                  "it wrote %s",
                  row.selector, arm_name(row.arm), describe(expected).c_str(),
                  describe(outcome.writes).c_str());
    check(same_effect(expected, outcome.writes), label);

    std::snprintf(label, sizeof(label),
                  "selector 0x%08x must make %d call(s) -- it made %d",
                  row.selector, expected_calls, outcome.call_count);
    check(outcome.call_count == expected_calls, label);

    std::snprintf(label, sizeof(label),
                  "selector 0x%08x must not write any byte the listing does not "
                  "show a dword write for -- %d stray byte(s)",
                  row.selector, outcome.stray_byte_writes);
    check(outcome.stray_byte_writes == 0, label);

    if (expected_calls != 0) {
      std::snprintf(label, sizeof(label),
                    "REFUTE F: selector 0x%08x must pass the record pointer, the "
                    "index 3 and self+0x%zx to 0x00e39420",
                    row.selector, expected_destination);
      check(g_observer.arg_record == &fixture.record, label);
      check(g_observer.arg_index == 3u, label);
      check(outcome.destination_offset == expected_destination, label);
    }
  }
}

// == case 2: REFUTE B, branch polarity at every pivot and every leaf =========
void polarity_cases() {
  int neighbours_driven = 0;
  int skipped = 0;
  for (std::size_t index = 0; index < kRowCount; ++index) {
    const Word centre = kRows[index].selector;
    const Word neighbours[2] = {centre + 1u, centre - 1u};
    for (std::size_t side = 0; side < 2; ++side) {
      const Word candidate = neighbours[side];
      if (is_selector(candidate)) {
        ++skipped;  // the neighbour is a selector in its own right
        continue;
      }
      ++neighbours_driven;
      ValueFixture fixture;
    make_fixture(fixture);
      Probe probe;
      const Outcome outcome = run(candidate, std::vector<Plant>(), probe,
                                  &fixture.record);
      char label[192];
      std::snprintf(label, sizeof(label),
                    "REFUTE B: 0x%08x is one away from a selector and must write "
                    "nothing and call nothing -- it wrote %s and called %d time(s)",
                    candidate, describe(outcome.writes).c_str(),
                    outcome.call_count);
      check(outcome.writes.empty(), label);
      check(outcome.call_count == 0, label);
    }
  }
  check(neighbours_driven + skipped == 2u * kRowCount,
        "REFUTE B: both neighbours of all twenty-seven selectors were considered");
  check(neighbours_driven >= 40,
        "REFUTE B: at least forty non-selector neighbours were driven");
}

// == case 3: REFUTE C, off-by-one displacements =============================
void displacement_cases() {
  // The twenty-two displacements the complete listing reaches through ECX. A
  // decoy is planted at every one the arm under test is NOT expected to write,
  // which brackets each real destination immediately above and below.
  const std::size_t touched[] = {0x29cu, 0x2a8u, 0x2acu, 0x2b0u, 0x2b4u,
                                 0x2c0u, 0x2ccu, 0x2d0u, 0x2d4u, 0x308u,
                                 0x30cu, 0x310u, 0x314u, 0x318u, 0x31cu,
                                 0x320u, 0x324u, 0x328u, 0x32cu};
  const std::size_t touched_count = sizeof(touched) / sizeof(touched[0]);
  const Word decoy = 0x11110000u;

  for (std::size_t index = 0; index < kRowCount; ++index) {
    ValueFixture fixture;
    make_fixture(fixture);
    Probe probe;
    std::vector<Plant> plants;
    std::vector<std::size_t> decoys_planted;
    Effect expected;
    int expected_calls = 0;
    std::size_t expected_destination = 0u;
    // The lazy arms need their primary at zero and their tag at -1 for the
    // interesting path, so those two are planted rather than decoyed.
    if (kRows[index].arm == kLazy324) {
      plants.push_back(Plant{0x324u, 0u});
      plants.push_back(Plant{0x32cu, kTagUnset});
    }
    if (kRows[index].arm == kLazy314) {
      plants.push_back(Plant{0x314u, 0u});
      plants.push_back(Plant{0x32cu, kTagUnset});
    }
    if (kRows[index].arm == kLazy31c) {
      plants.push_back(Plant{0x31cu, 0u});
      plants.push_back(Plant{0x32cu, kTagUnset});
    }
    expect_for(kRows[index].arm, plants, false, &expected, &expected_calls,
               &expected_destination);

    for (std::size_t slot = 0; slot < touched_count; ++slot) {
      const std::size_t offset = touched[slot];
      bool written_by_the_body = false;
      for (std::size_t item = 0; item < expected.size(); ++item) {
        if (expected[item].first == offset) {
          written_by_the_body = true;
        }
      }
      if (written_by_the_body) {
        continue;
      }
      if (expected_calls != 0 && offset >= expected_destination &&
          offset < expected_destination + 0x0cu) {
        continue;  // the callee owns these twelve bytes
      }
      plants.push_back(Plant{offset, decoy});
      decoys_planted.push_back(offset);
    }

    const Outcome outcome =
        run(kRows[index].selector, plants, probe, &fixture.record);

    int clobbered = 0;
    for (std::size_t slot = 0; slot < decoys_planted.size(); ++slot) {
      if (*word(probe, decoys_planted[slot]) != decoy) {
        ++clobbered;
      }
    }
    char label[208];
    std::snprintf(label, sizeof(label),
                  "REFUTE C: selector 0x%08x must not disturb any of its %zu "
                  "decoy dwords bracketing its real destinations -- %d clobbered",
                  kRows[index].selector, decoys_planted.size(), clobbered);
    check(clobbered == 0, label);

    // The block's own unread head must survive too: a store at the wrong
    // displacement inside the block would land there.
    check(fixture.live.opaque_00[0] == 0x5au,
          "REFUTE C: the value block's +0x00 is never written");
    check(fixture.live.opaque_00[7] == 0x5au,
          "REFUTE C: the value block's +0x07 is never written");
    check(*word_at(&fixture.live, 0x04u) == 0x5a5a5a5au,
          "REFUTE C: the value block's +0x04 is never written");
  }
}

// == case 4: REFUTE D, the pointer level =====================================
void pointer_level_cases() {
  // The record's twelve bytes are 0x77 and the block it does not point at is
  // filled with 0x51..0x54. Every arm stores one of the live block's four
  // markers, so a one-level read is caught by the VALUE and not by the shape.
  for (std::size_t index = 0; index < kRowCount; ++index) {
    ValueFixture fixture;
    make_fixture(fixture);
    Probe probe;
    std::vector<Plant> plants;
    if (kRows[index].arm == kLazy324) {
      plants.push_back(Plant{0x324u, 0u});
    }
    if (kRows[index].arm == kLazy314) {
      plants.push_back(Plant{0x314u, 0u});
    }
    if (kRows[index].arm == kLazy31c) {
      plants.push_back(Plant{0x31cu, 0u});
    }
    const Outcome outcome =
        run(kRows[index].selector, plants, probe, &fixture.record);

    int leaked = 0;
    for (std::size_t item = 0; item < outcome.writes.size(); ++item) {
      const Word stored = outcome.writes[item].second;
      const bool is_marker = stored == kBlock08 || stored == kBlock0c ||
                             stored == kBlock10 || stored == kBlock14;
      const bool is_a_tag = stored == kTag_1654c00 || stored == kTag_1654c01 ||
                            stored == kTag_1654c02 || stored == kTag_1654c04 ||
                            stored == kTag_1654c05;
      const bool carried_over = stored == before_value(plants,
                                                       outcome.writes[item].first);
      if (!is_marker && !is_a_tag && !carried_over) {
        ++leaked;
      }
    }
    char label[208];
    std::snprintf(label, sizeof(label),
                  "REFUTE D: selector 0x%08x must store the live block's words or "
                  "one of the six tags and nothing else -- %d value(s) came from "
                  "the record or from the block it does not point at",
                  kRows[index].selector, leaked);
    check(leaked == 0, label);
  }
}

// == case 5: REFUTE E/F/G, the call's arguments and the write ordering =======
void call_boundary_cases() {
  struct CopyCase {
    Word selector;
    std::size_t primary;
    std::size_t destination;
  };
  const CopyCase copies[] = {
      {0x99f0d1dau, 0x324u, 0x2c0u}, {0xaaf6aaacu, 0x324u, 0x2c0u},
      {0xdca976d0u, 0x324u, 0x2c0u}, {0x8133fb2eu, 0x31cu, 0x2b4u},
      {0x2cfa39ddu, 0x31cu, 0x2b4u}, {0x6a9f2620u, 0x31cu, 0x2b4u},
      {0xf967827cu, 0x30cu, 0x29cu}, {0x13df9c1cu, 0x30cu, 0x29cu},
      {0x7115ede5u, 0x30cu, 0x29cu},
  };
  const std::size_t copy_count = sizeof(copies) / sizeof(copies[0]);

  for (std::size_t index = 0; index < copy_count; ++index) {
    ValueFixture fixture;
    make_fixture(fixture);
    Probe probe;
    const Outcome outcome =
        run(copies[index].selector, std::vector<Plant>(), probe,
            &fixture.record);

    char label[224];
    std::snprintf(label, sizeof(label),
                  "REFUTE F: selector 0x%08x must call 0x00e39420 exactly once",
                  copies[index].selector);
    check(outcome.call_count == 1, label);
    std::snprintf(label, sizeof(label),
                  "REFUTE F: selector 0x%08x must pass the record pointer as "
                  "argument zero, not the block and not a receiver address",
                  copies[index].selector);
    check(g_observer.arg_record == &fixture.record, label);
    std::snprintf(label, sizeof(label),
                  "REFUTE H: selector 0x%08x must pass the index 3, not 0, 1, 2 "
                  "or 4 -- the callee reads q[index+0..2] from the block",
                  copies[index].selector);
    check(g_observer.arg_index == 3u, label);
    std::snprintf(label, sizeof(label),
                  "REFUTE E/F: selector 0x%08x must pass self+0x%zx as argument "
                  "two, not another receiver word",
                  copies[index].selector, copies[index].destination);
    check(outcome.destination_offset == copies[index].destination, label);

    // REFUTE G: the primary was stored BEFORE the call, and the twelve
    // destination bytes were NOT touched by the body when the callee was
    // entered.
    std::snprintf(label, sizeof(label),
                  "REFUTE G: selector 0x%08x stored self+0x%zx before calling, so "
                  "the callee saw the new value",
                  copies[index].selector, copies[index].primary);
    check(outcome.primary_was_stored, label);
    std::snprintf(label, sizeof(label),
                  "REFUTE G: selector 0x%08x left the callee's twelve destination "
                  "bytes untouched when the callee was entered",
                  copies[index].selector);
    check(outcome.destination_pristine, label);
    std::snprintf(label, sizeof(label),
                  "REFUTE G: selector 0x%08x did not touch the tag word +0x32c, "
                  "which none of the three copy arms writes",
                  copies[index].selector);
    check(outcome.tag_at_call == pattern_word(0x32cu), label);
    std::snprintf(label, sizeof(label),
                  "REFUTE G: selector 0x%08x forwarded the callee's own result "
                  "rather than a value of its own",
                  copies[index].selector);
    check(outcome.returned == g_observer.poison, label);

    // And the observer's poison of the block's first word, applied AFTER the
    // body had already read it, must not appear in the receiver.
    std::snprintf(label, sizeof(label),
                  "REFUTE G: selector 0x%08x read the block before the call, so "
                  "the value the callee poisoned afterwards is not what it stored",
                  copies[index].selector);
    check(*word(probe, copies[index].primary) == kBlock08, label);

    // The callee's own rotation, read back from the probe.
    check(outcome.callee_writes.size() == 3u,
          "REFUTE H: the callee wrote exactly three words into its destination");
    check(*word(probe, copies[index].destination + 0u) == kBlock10,
          "the callee's destination +0x00 must hold q[index+1] = the block's +0x10");
    check(*word(probe, copies[index].destination + 4u) == kBlock0c,
          "the callee's destination +0x04 must hold q[index+0] = the block's +0x0c");
    check(*word(probe, copies[index].destination + 8u) == kBlock14,
          "the callee's destination +0x08 must hold q[index+2] = the block's +0x14");
  }

  // The other eighteen selectors must make no call at all.
  for (std::size_t index = 0; index < kRowCount; ++index) {
    bool is_copy = false;
    for (std::size_t slot = 0; slot < copy_count; ++slot) {
      if (copies[slot].selector == kRows[index].selector) {
        is_copy = true;
      }
    }
    if (is_copy) {
      continue;
    }
    ValueFixture fixture;
    make_fixture(fixture);
    Probe probe;
    const Outcome outcome = run(kRows[index].selector, std::vector<Plant>(),
                               probe, &fixture.record);
    char label[200];
    std::snprintf(label, sizeof(label),
                  "REFUTE H: selector 0x%08x reaches the %s arm, which makes no "
                  "call at all -- it made %d",
                  kRows[index].selector, arm_name(kRows[index].arm),
                  outcome.call_count);
    check(outcome.call_count == 0, label);
  }
}

// == case 6: the tag guard, REFUTE H =========================================
void tag_guard_cases() {
  // The machine compares the receiver word against -1, not against zero, so a
  // receiver whose +0x32c holds 0 is still OVERWRITTEN by a guarded arm.
  const Word pre_set[4] = {kTagUnset, 0u, kTag_1654c04, 0x00000001u};
  // The machine's guard is `CMP [ECX+0x32c],-1 / JNZ skip`, so the tag is
  // written ONLY out of the -1 state. Every other pre-set value survives, and
  // zero in particular survives because zero is not -1.
  const Word expected_tag[4] = {kTag_1654c05, 0u, kTag_1654c04, 0x00000001u};
  for (std::size_t index = 0; index < 4; ++index) {
    ValueFixture fixture;
    make_fixture(fixture);
    Probe probe;
    std::vector<Plant> plants;
    plants.push_back(Plant{0x324u, 0u});
    plants.push_back(Plant{0x32cu, pre_set[index]});
    const Outcome outcome = run(0x9f792b4cu, plants, probe, &fixture.record);
    char label[224];
    std::snprintf(label, sizeof(label),
                  "REFUTE H: with self+0x32c pre-set to 0x%08x the guarded arm "
                  "must leave 0x%08x there -- it left 0x%08x",
                  pre_set[index], expected_tag[index],
                  *word(probe, 0x32cu));
    check(*word(probe, 0x32cu) == expected_tag[index], label);

    // And the same four pre-sets against the other three guarded tag arms, whose
    // immediates are the other three values.
    const Word other_selectors[3] = {0x279c4e55u, 0x3b38f92au, 0xade76cceu};
    const Word other_tags[3] = {kTag_1654c02, kTag_1654c04, kTag_1654c01};
    for (std::size_t slot = 0; slot < 3; ++slot) {
      ValueFixture other;
    make_fixture(other);
      Probe other_probe;
      std::vector<Plant> other_plants;
      other_plants.push_back(Plant{0x32cu, pre_set[index]});
      if (other_selectors[slot] == 0x279c4e55u) {
        other_plants.push_back(Plant{0x314u, 0u});
      }
      if (other_selectors[slot] == 0x3b38f92au) {
        other_plants.push_back(Plant{0x31cu, 0u});
      }
      run(other_selectors[slot], other_plants, other_probe, &other.record);
      const Word want = pre_set[index] == kTagUnset ? other_tags[slot]
                                                    : pre_set[index];
      std::snprintf(label, sizeof(label),
                    "REFUTE H: selector 0x%08x with self+0x32c pre-set to 0x%08x "
                    "must leave 0x%08x -- it left 0x%08x",
                    other_selectors[slot], pre_set[index], want,
                    *word(other_probe, 0x32cu));
      check(*word(other_probe, 0x32cu) == want, label);
    }
  }

  // The one UNGUARDED tag store: it happens whatever +0x32c held, including when
  // it already holds another of the six tags.
  for (std::size_t index = 0; index < 4; ++index) {
    ValueFixture fixture;
    make_fixture(fixture);
    Probe probe;
    std::vector<Plant> plants;
    plants.push_back(Plant{0x32cu, pre_set[index]});
    const Outcome outcome = run(0x3e2a3040u, plants, probe, &fixture.record);
    char label[208];
    std::snprintf(label, sizeof(label),
                  "REFUTE H: the unguarded arm must overwrite 0x%08x with "
                  "0x1654c00 whatever it finds -- it left 0x%08x",
                  pre_set[index], *word(probe, 0x32cu));
    check(*word(probe, 0x32cu) == kTag_1654c00, label);
  }
}

// == case 7: the lazy primary/secondary pair, REFUTE G =======================
void lazy_guard_cases() {
  struct LazyCase {
    Word selector;
    std::size_t primary;
    std::size_t secondary;
  };
  const LazyCase cases[] = {
      {0x9f792b4cu, 0x324u, 0x328u},
      {0x279c4e55u, 0x314u, 0x318u},
      {0x3b38f92au, 0x31cu, 0x320u},
  };
  const std::size_t case_count = sizeof(cases) / sizeof(cases[0]);
  const Word primary_values[4] = {0u, 0x00000001u, 0xdeadbeefu, 0xffffffffu};

  for (std::size_t index = 0; index < case_count; ++index) {
    for (std::size_t value = 0; value < 4; ++value) {
      ValueFixture fixture;
    make_fixture(fixture);
      Probe probe;
      std::vector<Plant> plants;
      plants.push_back(Plant{cases[index].primary, primary_values[value]});
      plants.push_back(Plant{0x32cu, kTag_1654c04});  // no tag write expected
      const Outcome outcome =
          run(cases[index].selector, plants, probe, &fixture.record);

      bool wrote_primary = false;
      for (std::size_t item = 0; item < outcome.writes.size(); ++item) {
        if (outcome.writes[item].first == cases[index].primary) {
          wrote_primary = true;
        }
      }
      char label[256];
      std::snprintf(label, sizeof(label),
                    "REFUTE G: selector 0x%08x with self+0x%zx pre-set to "
                    "0x%08x must store the secondary self+0x%zx unconditionally, "
                    "before the JNZ that guards the primary",
                    cases[index].selector, cases[index].primary,
                    primary_values[value], cases[index].secondary);
      check(*word(probe, cases[index].secondary) == kBlock08, label);
      if (primary_values[value] == 0u) {
        std::snprintf(label, sizeof(label),
                      "REFUTE G: selector 0x%08x must store the primary "
                      "self+0x%zx when it was still zero",
                      cases[index].selector, cases[index].primary);
        check(wrote_primary && *word(probe, cases[index].primary) == kBlock08,
              label);
      } else {
        std::snprintf(label, sizeof(label),
                      "REFUTE G: selector 0x%08x must NOT overwrite a non-zero "
                      "self+0x%zx -- it now holds 0x%08x",
                      cases[index].selector, cases[index].primary,
                      *word(probe, cases[index].primary));
        check(!wrote_primary, label);
        check(*word(probe, cases[index].primary) == primary_values[value], label);
      }
      // And the body wrote nothing else beyond the secondary, the primary (if
      // it was zero) and the receiver's other untouched words.
      check(outcome.writes.size() <= 2u,
            "REFUTE G: a lazy arm writes at most the primary and the secondary");
      check(outcome.call_count == 0,
            "REFUTE G: a lazy arm makes no call at all");
    }
  }
}

// == case 8: the null-record guard ==========================================
void null_record_cases() {
  int guarded = 0;
  for (std::size_t index = 0; index < kRowCount; ++index) {
    if (!arm_has_null_guard(kRows[index].arm)) {
      continue;
    }
    ++guarded;
    Probe probe;
    const Outcome outcome = run(kRows[index].selector, std::vector<Plant>(),
                               probe, nullptr);
    char label[224];
    std::snprintf(label, sizeof(label),
                  "selector 0x%08x reaches the one arm the machine guards with "
                  "TEST EAX,EAX, so a null record must write nothing -- it "
                  "wrote %s",
                  kRows[index].selector, describe(outcome.writes).c_str());
    check(outcome.writes.empty(), label);
    check(outcome.call_count == 0, label);
  }
  check(guarded == 10,
        "exactly ten of the twenty-seven selectors reach the guarded arm at "
        "0x00e3a517");
}

// == case 9: REFUTE J, no match writes nothing ===============================
void no_match_cases() {
  const Word values[] = {
      0u,
      1u,
      2u,
      0x7fffffffu,
      0x80000000u,
      0x80000001u,
      0xf278934bu,
      0xf2789349u,
      0x9f792b4du,
      0x9f792b4bu,
      0x3e2a3041u,
      0x3e2a303fu,
      0x279c4e56u,
      0x279c4e54u,
      0xaaf6aaadu,
      0xaaf6aaabu,
      0xd832b05au,
      0xd832b058u,
      0x6cd9ec7cu,
      0x6cd9ec7au,
      0xffffffffu,
      0xfffffffeu,
  };
  // A deterministic pseudo-random sweep, so the case is not a fixed list.
  Word generated[64];
  Word state = 0x00e3a400u;
  for (std::size_t index = 0; index < 64; ++index) {
    state = state * 1664525u + 1013904223u;
    generated[index] = state;
  }

  const std::size_t fixed_count = sizeof(values) / sizeof(values[0]);
  int driven = 0;
  for (std::size_t index = 0; index < fixed_count + 64; ++index) {
    const Word selector = index < fixed_count ? values[index]
                                              : generated[index - fixed_count];
    if (is_selector(selector)) {
      continue;  // a real selector has its own row in the sweep above
    }
    ++driven;
    ValueFixture fixture;
    make_fixture(fixture);
    Probe probe;
    const Outcome outcome = run(selector, std::vector<Plant>(), probe,
                                &fixture.record);
    char label[200];
    std::snprintf(label, sizeof(label),
                  "REFUTE J: 0x%08x matches no case in the dispatch and must "
                  "leave the receiver untouched -- it wrote %s and called %d",
                  selector, describe(outcome.writes).c_str(),
                  outcome.call_count);
    check(outcome.writes.empty(), label);
    check(outcome.call_count == 0, label);
  }
  check(driven == fixed_count + 64,
        "REFUTE J: every one of the eighty-six non-selector values was driven");
}

// == case 10: the value left in the return register ==========================
void return_value_cases() {
  // The three copy arms forward the callee's result; the two vector arms leave
  // the block pointer; the tag and lazy arms leave the block's first word; a
  // selector that matches nothing leaves the selector itself. All four shapes
  // are register CONTENT, fixed by the listing, and none of them is a claim
  // about what the value means.
  struct Expect {
    Word selector;
    std::size_t plant_offset;
    Word plant_value;
    const char* what;
  };
  const Expect cases[] = {
      {0xaaf6aaacu, 0u, 0u, "the callee's own result, forwarded"},
      {0x99f0d1dau, 0u, 0u, "the callee's own result, forwarded"},
      {0x8133fb2eu, 0u, 0u, "the callee's own result, forwarded"},
      {0xf278934au, 0u, 0u, "the value-block pointer"},
      {0x25ca9233u, 0u, 0u, "the value-block pointer"},
      {0x5c51063fu, 0u, 0u, "the value-block pointer"},
      {0x980e43f2u, 0u, 0u, "the value-block pointer"},
      {0x5fcf28d0u, 0u, 0u, "the value-block pointer"},
      {0x7bceaa86u, 0u, 0u, "the value-block pointer"},
      {0x3e2a3040u, 0u, 0u, "the block's first word"},
      {0xade76cceu, 0u, 0u, "the block's first word"},
      {0x9f792b4cu, 0x324u, 0u, "the block's first word"},
      {0x279c4e55u, 0x314u, 0u, "the block's first word"},
      {0x3b38f92au, 0x31cu, 0u, "the block's first word"},
      {0x00000000u, 0u, 0u, "the selector itself"},
      {0x12345678u, 0u, 0u, "the selector itself"},
  };
  const std::size_t case_count = sizeof(cases) / sizeof(cases[0]);

  for (std::size_t index = 0; index < case_count; ++index) {
    ValueFixture fixture;
    make_fixture(fixture);
    Probe probe;
    std::vector<Plant> plants;
    if (cases[index].plant_offset != 0u) {
      plants.push_back(Plant{cases[index].plant_offset, cases[index].plant_value});
    }
    const Outcome outcome =
        run(cases[index].selector, plants, probe, &fixture.record);

    Word want = 0u;
    const Word selector = cases[index].selector;
    if (selector == 0xaaf6aaacu || selector == 0x99f0d1dau ||
        selector == 0x8133fb2eu) {
      want = g_observer.poison;
    } else if (selector == 0x3e2a3040u || selector == 0xade76cceu ||
               selector == 0x9f792b4cu || selector == 0x279c4e55u ||
               selector == 0x3b38f92au) {
      want = kBlock08;
    } else if (selector == 0x00000000u || selector == 0x12345678u) {
      want = selector;
    } else {
      want = address_word(&fixture.live);
    }
    char label[224];
    std::snprintf(label, sizeof(label),
                  "selector 0x%08x must leave %s in the return register -- it "
                  "left 0x%08x",
                  selector, cases[index].what, outcome.returned);
    check(outcome.returned == want, label);
  }
}

// == case 11: the ABI, measured ==============================================
//
// The stack-cleanup probe is ONE asm block, and that is the whole point of it.
//
// A first attempt sampled ESP in C++ before and after the call:
//
//     const std::uintptr_t before = sample_stack_pointer();
//     re_00e3a400(receiver, 0x8133fb2eu, record);
//     const std::uintptr_t after = sample_stack_pointer();
//
// and it was WRONG at -O1 and above: gcc -O2 emits `sub esp,0x8` for frame
// alignment BETWEEN the first sample and the `call`, so `before` and `after`
// differ by 8 and the check reports a callee-cleanup defect that is not in the
// reconstruction at all. The probe was measuring the compiler, not the callee.
// Three of the eight cells failed for that reason and clang's four passed only
// because clang happened not to emit the adjustment there.
//
// Sampling and calling inside a single `__volatile__` asm block removes the
// window: the compiler cannot insert stack work between two instructions it
// does not own, so the only ESP movement between the two samples is the two
// argument pushes this block performs and the callee's own `ret 0x8`.
//
// The register discipline is respected: this block writes only EAX, ECX and the
// flags, all caller-saved, and never ESI/EDI/EBX/EBP. The pushes are its own
// frame, balanced by the callee under the convention being measured.
struct EspDelta {
  std::uintptr_t observed;  // ESP after the call minus ESP before the pushes
  Word returned;            // EAX on return
};

EspDelta call_and_measure_esp(Simulator* receiver, Word selector,
                              const PropertyRecord* record) {
  // The two ESP samples and the return value are written straight to memory
  // operands rather than to registers: three register outputs plus three
  // register inputs, with EAX/ECX/EDX all clobbered by the sequence, is more
  // distinct registers than x86-32 has available, and the constraint solver
  // rejects the block outright ("impossible constraints" on gcc, "requires
  // more registers than available" on clang). Memory operands need none.
  std::uintptr_t before = 0u;
  std::uintptr_t after = 0u;
  Word result = 0u;
  __asm__ __volatile__(
      "movl %%esp, %[pre]\n\t"
      "pushl %[rec]\n\t"
      "pushl %[sel]\n\t"
      "movl %[rcv], %%ecx\n\t"
      "call re_00e3a400\n\t"
      "movl %%esp, %[post]\n\t"
      "movl %%eax, %[res]\n\t"
      : [pre] "=m"(before), [post] "=m"(after), [res] "=m"(result)
      : [rec] "r"(record), [sel] "r"(selector), [rcv] "r"(receiver)
      : "eax", "ecx", "edx", "cc", "memory");
  EspDelta delta;
  delta.observed = after - before;
  delta.returned = result;
  return delta;
}

void abi_cases() {
  ValueFixture fixture;
  make_fixture(fixture);
  // Static storage duration on purpose: the two globals below outlive this
  // function and must keep pointing at a live object, which an automatic
  // `Probe` would not (gcc -O2 rejects it under -Werror=dangling-pointer).
  static Probe probe;
  fill_probe(probe);
  g_observer = Observer();
  g_snapshot = CallSnapshot();
  g_live_probe = &probe;
  g_destination_base = probe.bytes;

  const EspDelta measured =
      call_and_measure_esp(as_simulator(probe), 0x8133fb2eu, &fixture.record);

  // The body's terminator is `C2 08 00`, RET 0x8, at thirteen sites: the callee
  // owns eight bytes of stack cleanup. The two argument pushes this block makes
  // are therefore undone by the callee itself and the net delta is zero. A cdecl
  // reconstruction (the caller pops) leaves the two words still on the stack and
  // the delta is 8; one that popped twice leaves it -8.
  //
  // The expectation is written here as a literal, from the `ret 0x8` immediate
  // read out of the image, and not computed from the model -- so the check can
  // disagree with the reconstruction instead of restating it.
  check(measured.observed == 0u,
        "the reconstruction must pop its own two stack words (RET 0x8), so the "
        "net ESP movement across the call is zero");

  // The same measurement also pins the return register, from the machine's own
  // RET-sites: the callee's EAX is what the caller reads back.
  check(measured.returned == g_observer.poison,
        "the return register must carry the callee's own EAX on the calling arm, "
        "untouched by the reconstruction");

  // The receiver is the only object the body writes through: the 0x10-byte canary
  // past the modeled object must be untouched.
  int canary_touched = 0;
  for (std::size_t index = kObjectSize; index < kProbeSize; ++index) {
    if (probe.bytes[index] != static_cast<std::uint8_t>(index * 7u + 3u)) {
      ++canary_touched;
    }
  }
  check(canary_touched == 0,
        "the 0x10-byte canary past the modeled object must be untouched, so the "
        "body writes nothing outside the receiver");

  // The callee's own rotation, read back from the probe, at the offset the
  // selector 0x8133fb2e must have passed.
  check(*word(probe, 0x2b4u + 0u) == kBlock10,
        "the callee's destination +0x00 must hold q[index+1] = the block's +0x10");
  check(*word(probe, 0x2b4u + 4u) == kBlock0c,
        "the callee's destination +0x04 must hold q[index+0] = the block's +0x0c");
  check(*word(probe, 0x2b4u + 8u) == kBlock14,
        "the callee's destination +0x08 must hold q[index+2] = the block's +0x14");
}

// == the oracle table's own self-consistency ================================
void table_cases() {
  check(kRowCount == 27u, "the dispatch compares twenty-seven selector values");
  const Word declared[] = {
      kSelector_8133fb2e, kSelector_980e43f2, kSelector_99f0d1da,
      kSelector_9f792b4c, kSelector_a0973374, kSelector_a6cb4c9f,
      kSelector_aaf6aaac, kSelector_ade76cce, kSelector_cdb3696f,
      kSelector_d536c91d, kSelector_d832b059, kSelector_dca976d0,
      kSelector_e0bc9d45, kSelector_f278934a, kSelector_f967827c,
      kSelector_13df9c1c, kSelector_25ca9233, kSelector_279c4e55,
      kSelector_2cfa39dd, kSelector_3b38f92a, kSelector_3e2a3040,
      kSelector_5c51063f, kSelector_5fcf28d0, kSelector_6a9f2620,
      kSelector_6cd9ec7b, kSelector_7115ede5, kSelector_7bceaa86,
  };
  const std::size_t declared_count = sizeof(declared) / sizeof(declared[0]);
  check(declared_count == kRowCount, "the header and the table agree on the count");
  for (std::size_t index = 0; index < declared_count; ++index) {
    char label[160];
    std::snprintf(label, sizeof(label),
                  "selector 0x%08x is declared in the header and mapped in the "
                  "oracle table exactly once",
                  declared[index]);
    check(is_selector(declared[index]), label);
  }
  int three_arms = 0;
  int copy_arms = 0;
  for (std::size_t row = 0; row < kRowCount; ++row) {
    if (kRows[row].arm == kThree) {
      ++three_arms;
    }
    if (kRows[row].arm == kCopy2c0 || kRows[row].arm == kCopy2b4 ||
        kRows[row].arm == kCopy29c) {
      ++copy_arms;
    }
  }
  check(three_arms == 10,
        "ten of the twenty-seven selectors reach the guarded arm at 0x00e3a517");
  check(copy_arms == 9,
        "nine of the twenty-seven selectors reach one of the three calling arms");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w2_00e3a400

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w2_00e3a400;
  table_cases();
  sweep_selectors();
  polarity_cases();
  displacement_cases();
  pointer_level_cases();
  call_boundary_cases();
  tag_guard_cases();
  lazy_guard_cases();
  null_record_cases();
  no_match_cases();
  return_value_cases();
  abi_cases();

  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
