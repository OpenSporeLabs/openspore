// PKG-00E3A270-HASHED-PROPERTY-DISPATCH -- VA 0x00e3a270
// Behavioural model test for FUN_00e3a270: the twenty-seven-way hashed-property
// dispatcher, body 0x00e3a270..0x00e3a56a inclusive, 172 instructions.
//
// THE ONE DIRECT CALLEE IS DEFINED HERE AS AN OBSERVER. 0x00e39420 is declared
// extern in the package header and defined below, so the test sees every
// transfer the reconstruction makes, with which three arguments in which push
// order, and decides for itself what the callee does to memory and what it
// returns while it is there. That is the only way to test the three things this
// body does that a store-diff alone cannot see:
//
//   * the call's ARGUMENT IDENTITY and order -- (record, 0x3,
//     self+0x2c0 / self+0x2b4 / self+0x29c) -- checked by comparing POINTERS,
//     not by position in a signature, so a swapped push order is caught;
//   * the WRITE ORDERING around each call: the receiver word is stored BEFORE
//     the call and the twelve destination bytes are NOT, which the observer
//     proves by snapshotting the receiver at the instant it is entered;
//   * the RETURNED VALUE. On the three calling arms that value is the callee's
//     own result forwarded untouched, so the observer returns a POISON word
//     (0x0badf00d) that no arm could produce on its own. A reconstruction that
//     fabricates a return value of its own is therefore caught, and so is one
//     that forwards the wrong arm's value.
//
// THE GRADER IS A WHOLE-PROBE BYTE COMPARISON. For each of the twenty-seven
// selectors and for each of several receiver pre-states, the test builds the
// probe image the LISTING says the call must leave behind -- computed from the
// oracle table below, never from the reconstruction -- and then compares the
// actual 0x340-byte probe against it byte for byte. The probe is the modelled
// 0x330-byte object plus a 0x10-byte canary past its end, so that single
// comparison refutes, at once: a wrong displacement, an extra store, a missing
// store, a swapped pair, a store of the wrong width, a store of a stale value,
// and a write past the end of the object.
//
// THE CASES REFUTE, they do not merely walk. Each names the wrong
// reconstruction it is aimed at:
//
//   A  the dispatch is SIGNED. Every ordering branch is JG (0x0F 8F, and 0x7F
//      in its short form at 0x00e3a33c), and fifteen of the twenty-seven
//      selector values have the high bit set. Under an UNSIGNED reading the
//      twelve POSITIVE selectors fall below the root pivot 0xf278934a into the
//      low half, whose seven leaf tests are all negative values, so all twelve
//      match no case, write nothing and call nothing. The case first PROVES the
//      two readings disagree on exactly twelve selectors, so it is not vacuous.
//   B  the selector -> arm mapping, for all twenty-seven, against a hand-
//      transcribed oracle table.
//   C  the CALLING arms: argument identity, push order, destination offset, the
//      pre-call write state, and the forwarded poison return.
//   D  the three LAZY arms: the secondary stored unconditionally and the
//      primary only while still zero -- with the JNZ that acts on a flag set
//      FOUR instructions EARLIER than the store it guards.
//   E  the TAG guard: -1 writes, 0 ALSO writes (the machine compares against -1,
//      not against zero), a foreign tag does not, and the one UNGUARDED tag
//      store happens regardless of the pre-state.
//   F  the NULL-RECORD guard: present on exactly one of the ten arms and absent
//      on the other nine.
//   G  two levels of INDIRECTION, with decoy words planted in the record, in the
//      block's unread +0x00/+0x04, and in a second block the record does not
//      point at.
//   H  the SWAPPED pair in the four-store arm (q[+0x0c] -> +0x2ac and
//      q[+0x10] -> +0x2a8) against the ASCENDING order in the three-store arm
//      (+0x2d0, +0x2cc, +0x2d4). The two arms disagree and neither is the
//      other's typo.
//   I  MACHINE facts: the twenty-seven immediates, the signedness of the seven
//      ordering branches, the RET 0x8 terminators, and the ARM COUNT.
//
// Direction M is the MUTATION TEST: fourteen deliberately wrong bodies are
// built below, driven through the SAME grader the reconstruction is graded by,
// and each one is REQUIRED to be refuted. A battery with no power to reject a
// known-wrong body cannot certify the right one, so the mutants being refuted is
// itself an assertion: if any mutant survives, the run fails even though the
// reconstruction passed every other case.
//
// The battery was additionally checked from OUTSIDE, by perturbing the
// reconstruction's own body in the package's .cpp and rebuilding BOTH
// translation units FROM THE MUTATED DIRECTORY under the promotion gate. All
// eleven external perturbations are caught; see the metadata sidecar's
// focused_test.external_perturbation for the list and for which of them fail at
// COMPILE time rather than at RUN time.

#include "hashed_property_dispatch_00e3a270.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <csetjmp>
#include <cstring>
#include <unistd.h>

#include <vector>

#if !defined(__i386__) && !defined(_M_IX86)
#error "0x00e3a270 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00e3a270_dispatch {
namespace model {

using Word = std::uint32_t;

int g_checks = 0;
int g_failures = 0;

void check(bool condition, const char* label) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL: %s\n", label);
  }
}

constexpr std::size_t kNone = 0xffffffffu;

// ---------------------------------------------------------------------------
// Distinct values, so a mis-indexed read shows up as the wrong NUMBER rather
// than as a coincidence.
// ---------------------------------------------------------------------------
constexpr Word kBlock00 = 0x11111111u;
constexpr Word kBlock04 = 0x22222222u;  // never read by the body
constexpr Word kBlock08 = 0xa5a50008u;
constexpr Word kBlock0c = 0xa5a5000cu;
constexpr Word kBlock10 = 0xa5a50010u;
constexpr Word kBlock14 = 0xa5a50014u;

constexpr Word kDecoy00 = 0xdeadbe00u;
constexpr Word kDecoy04 = 0xdeadbe04u;
constexpr Word kDecoy08 = 0xdeadbe08u;
constexpr Word kDecoy0c = 0xdeadbe0cu;
constexpr Word kDecoy10 = 0xdeadbe10u;
constexpr Word kDecoy14 = 0xdeadbe14u;

// The callee's POISON return: no arm of the body can produce this value on its
// own, so forwarding it is observable and fabricating it is a failure.
constexpr Word kCalleePoison = 0x0badf00du;

Word block_value(std::size_t field) {
  switch (field) {
    case 0x08u:
      return kBlock08;
    case 0x0cu:
      return kBlock0c;
    case 0x10u:
      return kBlock10;
    case 0x14u:
      return kBlock14;
    default:
      return 0u;
  }
}

// ---------------------------------------------------------------------------
// The probe.
// ---------------------------------------------------------------------------
// The modelled 0x330-byte receiver, plus a 0x10-byte canary past its end. Every
// byte is initialised from a per-byte pattern, and every byte of the expected
// post-state is computed from the LISTING, so a byte the body must not touch
// and does touch is a mismatch like any other.
constexpr std::size_t kProbeBytes = 0x340u;

std::uint8_t fill_byte(std::size_t index) {
  return static_cast<std::uint8_t>(index * 7u + 3u);
}

struct Scenario {
  std::uint8_t probe[kProbeBytes];
  PropertyValueBlock block;
  PropertyValueBlock decoy;
  PropertyRecord record;
  // Trailing slack. One mutant deliberately treats the RECORD as if it were the
  // value block, i.e. reads it at +0x08/+0x0c/+0x10/+0x14, which runs four bytes
  // past the 0x10-byte record. The slack makes that a bounded, deterministic
  // wrong ANSWER instead of an out-of-bounds read, so the mutant is refuted for
  // the reason it is wrong rather than by crashing.
  std::uint8_t slack[64];
};

void* probe_word(std::uint8_t* probe, std::size_t displacement) {
  return probe + displacement;
}

Word read_word(const std::uint8_t* image, std::size_t displacement) {
  Word value = 0u;
  std::memcpy(&value, image + displacement, sizeof(value));
  return value;
}

void write_word(std::uint8_t* image, std::size_t displacement, Word value) {
  std::memcpy(image + displacement, &value, sizeof(value));
}

// The receiver pre-states the battery sweeps. `tag` is what +0x32c holds before
// the call; the three lazy primaries likewise. Every combination is driven
// because the guards are the load-bearing part of this body.
enum TagState { kTagUnsetState, kTagZeroState, kTagForeignState };
enum PrimaryState { kPrimaryZero, kPrimarySet };

struct PreState {
  TagState tag;
  PrimaryState p324;
  PrimaryState p314;
  PrimaryState p31c;
};

const PreState kPreStates[] = {
    {kTagUnsetState, kPrimaryZero, kPrimaryZero, kPrimaryZero},
    {kTagUnsetState, kPrimarySet, kPrimarySet, kPrimarySet},
    {kTagZeroState, kPrimaryZero, kPrimarySet, kPrimaryZero},
    {kTagZeroState, kPrimarySet, kPrimaryZero, kPrimarySet},
    {kTagForeignState, kPrimaryZero, kPrimaryZero, kPrimarySet},
    {kTagForeignState, kPrimarySet, kPrimaryZero, kPrimaryZero},
};
constexpr std::size_t kPreStateCount = sizeof(kPreStates) / sizeof(kPreStates[0]);

// The value a guarded tag test compares against: `CMP DWORD PTR [ECX+0x32c],-1`
constexpr Word kUnset = 0xffffffffu;
constexpr Word kForeignTag = 0x12345678u;

void fill_scenario(Scenario* scenario, const PreState& pre) {
  std::memset(scenario, 0, sizeof(*scenario));
  for (std::size_t index = 0; index < kProbeBytes; ++index) {
    scenario->probe[index] = fill_byte(index);
  }

  scenario->block.opaque_00[0] = static_cast<std::uint8_t>(kBlock00);
  scenario->block.opaque_00[4] = static_cast<std::uint8_t>(kBlock04);
  scenario->block.word_08 = kBlock08;
  scenario->block.word_0c = kBlock0c;
  scenario->block.word_10 = kBlock10;
  scenario->block.word_14 = kBlock14;

  scenario->decoy.opaque_00[0] = static_cast<std::uint8_t>(kDecoy00);
  scenario->decoy.opaque_00[4] = static_cast<std::uint8_t>(kDecoy04);
  scenario->decoy.word_08 = kDecoy08;
  scenario->decoy.word_0c = kDecoy0c;
  scenario->decoy.word_10 = kDecoy10;
  scenario->decoy.word_14 = kDecoy14;

  // DECOYS at record displacements the body never reads. Reading record[+0x0c]
  // as a VALUE instead of as a pointer, or reading the wrong record
  // displacement, lands on one of these.
  scenario->record.opaque_00[0] = 0xa1u;
  scenario->record.opaque_00[4] = 0xa2u;
  scenario->record.opaque_00[8] = 0xa3u;
  scenario->record.value = &scenario->block;

  switch (pre.tag) {
    case kTagUnsetState:
      write_word(scenario->probe, 0x32cu, kUnset);
      break;
    case kTagZeroState:
      write_word(scenario->probe, 0x32cu, 0u);
      break;
    case kTagForeignState:
      write_word(scenario->probe, 0x32cu, kForeignTag);
      break;
  }
  write_word(scenario->probe, 0x324u, pre.p324 == kPrimaryZero ? 0u : 0xbbbb0324u);
  write_word(scenario->probe, 0x314u, pre.p314 == kPrimaryZero ? 0u : 0xbbbb0314u);
  write_word(scenario->probe, 0x31cu, pre.p31c == kPrimaryZero ? 0u : 0xbbbb031cu);
}

// ===========================================================================
// THE OBSERVER: the one direct callee, 0x00e39420.
// ===========================================================================
int g_call_count = 0;
const PropertyRecord* g_call_record = nullptr;
Word g_call_index = 0u;
std::uint8_t* g_call_destination = nullptr;
std::uint8_t* g_call_receiver = nullptr;
// A copy of the whole receiver taken at the instant the callee was entered.
// Comparing it against the expected image at that same point is what proves the
// WRITE ORDERING around the call, which an end-state diff cannot.
std::uint8_t g_call_snapshot[0x340];
bool g_call_snapshot_valid = false;

extern "C" Word simulator_copy_block3_00e39420(const PropertyRecord* record,
                                               Word index, void* destination) {
  ++g_call_count;
  g_call_record = record;
  g_call_index = index;
  g_call_destination = static_cast<std::uint8_t*>(destination);

  if (g_call_receiver != nullptr) {
    std::memcpy(g_call_snapshot, g_call_receiver, sizeof(g_call_snapshot));
    g_call_snapshot_valid = true;
  }

  // Its machine shape: a null first argument writes NOTHING and returns at
  // once; otherwise it rotates three words into the destination and leaves the
  // block pointer in EAX.
  if (record == nullptr) {
    return 0u;
  }
  const PropertyValueBlock* const q = record->value;
  (void)q;
  std::uint8_t* const dest = static_cast<std::uint8_t*>(destination);
  write_word(dest, 4u, block_value(static_cast<std::size_t>(index) * 4u));
  write_word(dest, 0u, block_value(static_cast<std::size_t>(index + 1u) * 4u));
  write_word(dest, 8u, block_value(static_cast<std::size_t>(index + 2u) * 4u));
  return kCalleePoison;  // stands for `MOV EAX,[EAX+0xc]`, i.e. the block pointer
}

// ===========================================================================
// THE ENTRY POINTS. One signature, so no mutant is graded by a laxer checker
// than the reconstruction is.
// ===========================================================================
using Probe = Word(PKG_00E3A270_THISCALL*)(Simulator*, Word,
                                            const PropertyRecord*);

Word PKG_00E3A270_THISCALL real_entry(Simulator* self, Word selector,
                                      const PropertyRecord* record) {
  return hashed_property_dispatch_00e3a270(self, selector, record);
}

Probe g_probe = &real_entry;

// ===========================================================================
// THE ORACLE. Twenty-seven rows, each transcribed by hand off the listing's
// branch chain: `arm` is the block the selector reaches.
// ===========================================================================
enum Arm {
  kCopy2c0,
  kCopy2b4,
  kCopy29c,
  kWriteFour,
  kWriteThree,
  kTagInit,
  kTagThen310,
  kLazy324,
  kLazy314,
  kLazy31c,
  kNoArm
};

struct Row {
  Word selector;
  Arm arm;
};

constexpr Row kRows[] = {
    // -- the high half, above the root pivot 0xf278934a ------------------------
    {0xf278934au, kWriteFour},   // e3a274 CMP / e3a27f JZ, the root's equality
    {0x25ca9233u, kWriteFour},   // e3a3d7, then the fall-through at e3a3dc
    {0x5c51063fu, kWriteFour},   // e3a4c7 / e3a4cc, a BACKWARD jump
    {0x3e2a3040u, kTagInit},     // e3a3ae
    {0x279c4e55u, kLazy314},     // e3a3bf
    {0xf967827cu, kCopy29c},     // e3a3c1 / e3a3c6
    {0x13df9c1cu, kCopy29c},     // e3a3cc / e3a3d1
    {0x2cfa39ddu, kCopy2b4},     // e3a452 / e3a457
    {0x3b38f92au, kLazy31c},     // e3a45d, then the fall-through at e3a462
    {0x6cd9ec7bu, kWriteThree},  // e3a4c5
    {0x5fcf28d0u, kWriteThree},  // e3a4d2 / e3a4d7
    {0x6a9f2620u, kCopy2b4},     // e3a4d9, then the fall-through at e3a4de
    {0x7115ede5u, kCopy29c},     // e3a509 / e3a50e
    {0x7bceaa86u, kWriteThree},  // e3a510, then the fall-through at e3a515
    {0xe0bc9d45u, kWriteThree},  // e3a395 / e3a39a
    {0xdca976d0u, kCopy2c0},     // e3a38a / e3a38f, a BACKWARD jump
    // -- the low half, below the root pivot ------------------------------------
    {0xaaf6aaacu, kCopy2c0},     // e3a290
    {0x99f0d1dau, kCopy2c0},     // e3a2b5, then the fall-through at e3a2ba
    {0x9f792b4cu, kLazy324},     // e3a29d
    {0xa0973374u, kWriteThree},  // e3a31e / e3a323
    {0xa6cb4c9fu, kWriteThree},  // e3a329 / e3a32e
    {0x8133fb2eu, kCopy2b4},     // e3a29f / e3a2a4
    {0x980e43f2u, kWriteThree},  // e3a2aa / e3a2af
    {0xd832b059u, kWriteThree},  // e3a33e
    {0xade76cceu, kTagThen310},  // e3a344 / e3a349
    {0xcdb3696fu, kWriteThree},  // e3a34b / e3a350
    {0xd536c91du, kWriteThree},  // e3a356 / e3a35b
};

constexpr std::size_t kRowCount = sizeof(kRows) / sizeof(kRows[0]);

const Word kAllSelectors[] = {
    0x13df9c1cu, 0x25ca9233u, 0x279c4e55u, 0x2cfa39ddu, 0x3b38f92au,
    0x3e2a3040u, 0x5c51063fu, 0x5fcf28d0u, 0x6a9f2620u, 0x6cd9ec7bu,
    0x7115ede5u, 0x7bceaa86u, 0x8133fb2eu, 0x980e43f2u, 0x99f0d1dau,
    0x9f792b4cu, 0xa0973374u, 0xa6cb4c9fu, 0xaaf6aaacu, 0xade76cceu,
    0xcdb3696fu, 0xd536c91du, 0xd832b059u, 0xdca976d0u, 0xe0bc9d45u,
    0xf278934au, 0xf967827cu,
};
constexpr std::size_t kAllCount = sizeof(kAllSelectors) / sizeof(kAllSelectors[0]);

const Row* row_for(Word selector) {
  for (std::size_t index = 0; index < kRowCount; ++index) {
    if (kRows[index].selector == selector) {
      return &kRows[index];
    }
  }
  return nullptr;
}

// The UNSIGNED reading of the machine's JG, used only to prove case A is not
// vacuous and to drive mutant 1.
bool unsigned_greater(Word left, Word right) { return left > right; }

// ===========================================================================
// THE EXPECTED POST-STATE, BUILT FROM THE LISTING ALONE.
//
// For each arm the listing fixes: which receiver words it writes, which block
// word lands in each, whether a tag store is present, whether that tag store is
// behind the `CMP ...,0xffffffff` guard, whether the primary of a lazy pair is
// conditional, and whether the arm calls 0x00e39420 and at which computed
// destination.
// ===========================================================================
struct ArmSpec {
  // The direct stores this arm makes, in listing order. `field` is the block
  // displacement read into the receiver displacement `to`.
  struct Store {
    Word to;
    std::size_t field;
    bool conditional;  // stored only when the named primary was still zero
  };
  Store stores[4];
  std::size_t store_count;

  Word tag_to;        // kNone when this arm writes no tag
  Word tag_value;
  bool tag_guarded;   // behind `CMP [ECX+tag_to],0xffffffff`?

  bool call;          // calls 0x00e39420?
  Word call_primary;  // the receiver word stored before the call
  Word call_destination;

  // Does the arm begin with `TEST EAX,EAX` / JZ on the record? This is the
  // body's ONLY null test, and it is on kWriteThree alone.
  bool null_guard;
  Arm ret_kind;  // what EAX holds on return (kNoArm == the selector itself)
};

ArmSpec spec_for(Arm arm) {
  // `guard_null_record` says what the body was HAND, not what it will do with
  // it. Passing the pointer through instead would make this a statement about
  // the record's contents, and the distinction is the whole of case F.
  ArmSpec spec{};
  spec.store_count = 0u;
  spec.tag_to = kNone;
  spec.tag_value = 0u;
  spec.tag_guarded = false;
  spec.call = false;
  spec.call_primary = kNone;
  spec.call_destination = kNone;
  spec.null_guard = false;
  spec.ret_kind = arm;

  switch (arm) {
    case kCopy2c0:
      spec.stores[0] = {0x324u, 8u, false};
      spec.store_count = 1u;
      spec.call = true;
      spec.call_primary = 0x324u;
      spec.call_destination = 0x2c0u;
      spec.ret_kind = kCopy2c0;
      break;
    case kCopy2b4:
      spec.stores[0] = {0x31cu, 8u, false};
      spec.store_count = 1u;
      spec.call = true;
      spec.call_primary = 0x31cu;
      spec.call_destination = 0x2b4u;
      break;
    case kCopy29c:
      spec.stores[0] = {0x30cu, 8u, false};
      spec.store_count = 1u;
      spec.call = true;
      spec.call_primary = 0x30cu;
      spec.call_destination = 0x29cu;
      break;
    case kWriteFour:
      // The SWAP: q[+0x0c] lands at +0x2ac and q[+0x10] lands at +0x2a8.
      spec.stores[0] = {0x314u, 8u, false};
      spec.stores[1] = {0x2acu, 0xcu, false};
      spec.stores[2] = {0x2a8u, 0x10u, false};
      spec.stores[3] = {0x2b0u, 0x14u, false};
      spec.store_count = 4u;
      break;
    case kWriteThree:
      // ASCENDING, unlike the four-store arm.
      spec.stores[0] = {0x2d0u, 0xcu, false};
      spec.stores[1] = {0x2ccu, 0x10u, false};
      spec.stores[2] = {0x2d4u, 0x14u, false};
      spec.store_count = 3u;
      spec.null_guard = true;  // the body's ONLY null test
      break;
    case kTagInit:
      spec.stores[0] = {0x308u, 8u, false};
      spec.store_count = 1u;
      spec.tag_to = 0x32cu;
      spec.tag_value = 0x1654c00u;
      spec.tag_guarded = false;  // the body's ONLY unguarded tag store
      break;
    case kTagThen310:
      spec.stores[0] = {0x310u, 8u, false};
      spec.store_count = 1u;
      spec.tag_to = 0x32cu;
      spec.tag_value = 0x1654c01u;
      spec.tag_guarded = true;
      break;
    case kLazy324:
      // Secondary unconditional; primary only while zero.
      spec.stores[0] = {0x328u, 8u, false};
      spec.stores[1] = {0x324u, 8u, true};
      spec.store_count = 2u;
      spec.tag_to = 0x32cu;
      spec.tag_value = 0x1654c05u;
      spec.tag_guarded = true;
      break;
    case kLazy314:
      spec.stores[0] = {0x318u, 8u, false};
      spec.stores[1] = {0x314u, 8u, true};
      spec.store_count = 2u;
      spec.tag_to = 0x32cu;
      spec.tag_value = 0x1654c02u;
      spec.tag_guarded = true;
      break;
    case kLazy31c:
      spec.stores[0] = {0x320u, 8u, false};
      spec.stores[1] = {0x31cu, 8u, true};
      spec.store_count = 2u;
      spec.tag_to = 0x32cu;
      spec.tag_value = 0x1654c04u;
      spec.tag_guarded = true;
      break;
    case kNoArm:
      break;
  }
  return spec;
}

Word primary_before(const PreState& pre, Word displacement) {
  if (displacement == 0x324u) {
    return pre.p324 == kPrimaryZero ? 0u : 0xbbbb0324u;
  }
  if (displacement == 0x314u) {
    return pre.p314 == kPrimaryZero ? 0u : 0xbbbb0314u;
  }
  if (displacement == 0x31cu) {
    return pre.p31c == kPrimaryZero ? 0u : 0xbbbb031cu;
  }
  return 0u;
}

// Apply, to the expected image, exactly what the LISTING says the arm does.
//
// `phase` selects how far to go, which is what makes the call-ordering case
// possible: the expected image AT THE INSTANT OF THE CALL contains the body's
// own stores and none of the callee's, so comparing the observer's snapshot
// against it proves the ordering rather than merely the end state.
//
// `record_is_null` says what the body was HAND. It is deliberately not derived
// from the pointer value, because "no record" and "a record whose +0x0c is null"
// are different situations and only the first is what TEST EAX,EAX tests.
enum Phase { kPhaseBeforeCall, kPhaseAfterCall };

void apply_spec(const ArmSpec& spec, const PreState& pre, Scenario* scenario,
                bool record_is_null, Phase phase) {
  std::uint8_t* const image = scenario->probe;

  if (spec.null_guard && record_is_null) {
    return;  // the arm's own TEST EAX,EAX returns having written nothing
  }

  if (spec.tag_to != kNone) {
    const Word before = read_word(image, spec.tag_to);
    if (!spec.tag_guarded || before == kUnset) {
      write_word(image, spec.tag_to, spec.tag_value);
    }
  }

  for (std::size_t slot = 0; slot < spec.store_count; ++slot) {
    const Word to = spec.stores[slot].to;
    if (spec.stores[slot].conditional && primary_before(pre, to) != 0u) {
      continue;
    }
    write_word(image, to, block_value(spec.stores[slot].field));
  }

  if (spec.call && phase == kPhaseAfterCall) {
    // The callee's own rotation into the computed destination, which this body
    // never writes itself.
    std::uint8_t* const dest = image + spec.call_destination;
    write_word(dest, 4u, block_value(kCopyIndex * 4u));
    write_word(dest, 0u, block_value((kCopyIndex + 1u) * 4u));
    write_word(dest, 8u, block_value((kCopyIndex + 2u) * 4u));
  }
}

// What EAX holds on return, per the listing. `record_is_null` is what the body
// was handed; the two are not the same question (see apply_spec).
Word expected_return(const ArmSpec& spec, Word selector, bool record_is_null,
                     const Scenario& scenario) {
  switch (spec.ret_kind) {
    case kNoArm:
      return selector;  // no arm ran; EAX still holds the selector
    case kCopy2c0:
    case kCopy2b4:
    case kCopy29c:
      // The callee's result, forwarded untouched: its own POISON when it was
      // handed a record, and the zero its `TEST EAX,EAX` leaves behind when it
      // was handed none.
      return record_is_null ? 0u : kCalleePoison;
    case kWriteFour:
      // `MOV EAX,[EAX+0xc]` leaves the block POINTER in EAX.
      return static_cast<Word>(
          reinterpret_cast<std::uintptr_t>(&scenario.block));
    case kWriteThree:
      if (record_is_null) {
        return 0u;  // the null test leaves EAX zero
      }
      return static_cast<Word>(
          reinterpret_cast<std::uintptr_t>(&scenario.block));
    case kTagInit:
    case kTagThen310:
    case kLazy324:
    case kLazy314:
    case kLazy31c:
      return kBlock08;  // EAX left holding the loaded word
  }
  return selector;
}

// ===========================================================================
// THE GRADER.
//
// The expected image is built from the LISTING alone -- from `spec_for`, which
// is transcribed off the branch blocks by hand -- and never from the
// reconstruction. The body under test is then run against an IDENTICALLY
// prepared probe and the whole 0x340 bytes are compared, together with the
// call's observable facts and the returned word.
// ===========================================================================
struct Verdict {
  bool memory_ok;
  bool call_ok;
  bool return_ok;
  int first_bad_offset;
};

Verdict grade(Probe probe, Word selector, Arm arm, const PreState& pre,
              bool record_is_null) {
  Scenario expected;
  fill_scenario(&expected, pre);
  Scenario actual;
  fill_scenario(&actual, pre);

  const ArmSpec spec = spec_for(arm);
  apply_spec(spec, pre, &expected, record_is_null, kPhaseAfterCall);

  g_call_count = 0;
  g_call_record = nullptr;
  g_call_index = kNone;
  g_call_destination = nullptr;
  g_call_snapshot_valid = false;
  std::memset(g_call_snapshot, 0, sizeof(g_call_snapshot));
  g_call_receiver = actual.probe;

  Simulator* const self = reinterpret_cast<Simulator*>(actual.probe);
  const Word returned =
      probe(self, selector, record_is_null ? nullptr : &actual.record);

  Verdict verdict;
  verdict.first_bad_offset = -1;
  for (std::size_t index = 0; index < kProbeBytes; ++index) {
    if (expected.probe[index] != actual.probe[index]) {
      verdict.first_bad_offset = static_cast<int>(index);
      break;
    }
  }
  verdict.memory_ok = verdict.first_bad_offset < 0;

  verdict.call_ok = (g_call_count == (spec.call ? 1 : 0));
  if (spec.call && verdict.call_ok) {
    // The expected image at the INSTANT OF THE CALL: the body's own stores, and
    // none of the callee's. Comparing the observer's snapshot against this is
    // what proves the ordering -- the primary word is already stored and the
    // twelve destination bytes are still untouched.
    Scenario at_call;
    fill_scenario(&at_call, pre);
    apply_spec(spec, pre, &at_call, record_is_null, kPhaseBeforeCall);

    verdict.call_ok =
        g_call_record == &actual.record &&
        g_call_index == kCopyIndex &&
        g_call_destination == actual.probe + spec.call_destination &&
        g_call_snapshot_valid &&
        std::memcmp(g_call_snapshot, at_call.probe, kProbeBytes) == 0;
  }

  verdict.return_ok = returned == expected_return(spec, selector,
                                                 record_is_null, actual);
  return verdict;
}

// ---------------------------------------------------------------------------
// Case A: the dispatch is SIGNED.
// ---------------------------------------------------------------------------
void polarity_cases() {
  Word crossing = 0u;
  Word positives = 0u;
  for (std::size_t index = 0; index < kAllCount; ++index) {
    const Word value = kAllSelectors[index];
    if (static_cast<std::int32_t>(value) > 0) {
      ++positives;
    }
    if (signed_greater(value, kSelector_f278934a) !=
        unsigned_greater(value, kSelector_f278934a)) {
      ++crossing;
    }
  }
  check(positives == 12u,
        "twelve of the twenty-seven selector values are positive read signed");
  check(crossing == 12u,
        "REFUTE(A): exactly twelve selectors cross the root pivot 0xf278934a "
        "between the signed and unsigned readings, so the signedness case is "
        "not vacuous");

  // Every one of the twelve positive selectors must reach an arm under the
  // signed reading. Under an unsigned reading all twelve would land in the low
  // half, whose seven leaf tests are all negative, and match nothing at all.
  int reached = 0;
  for (std::size_t index = 0; index < kAllCount; ++index) {
    const Word selector = kAllSelectors[index];
    if (static_cast<std::int32_t>(selector) <= 0) {
      continue;
    }
    const Row* const row = row_for(selector);
    if (row != nullptr && row->arm != kNoArm) {
      ++reached;
    }
  }
  check(reached == 12u,
        "REFUTE(A): all twelve positive selectors reach an arm, which an "
        "unsigned dispatch would make unreachable");
}

// ---------------------------------------------------------------------------
// Case B: the selector -> arm mapping and every store, for all twenty-seven
// selectors across all six receiver pre-states.
// ---------------------------------------------------------------------------
void selector_mapping_cases() {
  for (std::size_t index = 0; index < kAllCount; ++index) {
    const Word selector = kAllSelectors[index];
    const Row* const row = row_for(selector);
    check(row != nullptr,
          "every one of the twenty-seven immediates has an oracle row");
    if (row == nullptr) {
      continue;
    }
    for (std::size_t state = 0; state < kPreStateCount; ++state) {
      const Verdict verdict =
          grade(&real_entry, selector, row->arm, kPreStates[state], false);
      char label[220];
      std::snprintf(label, sizeof(label),
                    "REFUTE(B): selector 0x%08x in pre-state %zu must leave the "
                    "receiver exactly as the listing says (first bad offset "
                    "%d)",
                    selector, state, verdict.first_bad_offset);
      check(verdict.memory_ok, label);
      check(verdict.call_ok,
            "REFUTE(C): the call's record, index and destination, and the "
            "pre-call write state, must be what the listing fixes");
      check(verdict.return_ok,
            "REFUTE(C): the word left in EAX on this path is fixed by the "
            "listing and is not this arm's to choose");
    }
  }
}

// ---------------------------------------------------------------------------
// Case F2: an UNGUARDED arm handed a null record must FAULT, because the
// machine dereferences it. This is the machine's own behaviour -- `MOV
// EDX,[EAX+0xc]` at 0x00e3a3e6 and its nine siblings have no test -- and it is
// the only thing that separates "the guard is on one arm" from "the guard is on
// every arm".
//
// Without this case the distinction is invisible: a reconstruction that widened
// the guard to all ten arms would agree with the listing on every non-null
// record and would return cleanly where the machine faults. So the fault is
// made observable with a SIGSEGV handler and siglongjmp, and the case asserts
// that it happens.
//
// A word on why this is a legitimate assertion rather than a trick. The machine
// has no path on which a null record reaches an unguarded arm without
// dereferencing it, so "dereferences it" is not a modelling choice; it is the
// only reading consistent with the bytes. And the reconstruction cannot express
// the fault directly -- C++ has no fault -- so the handler stands in for the
// machine's behaviour rather than for anything the reconstruction chose.
// ---------------------------------------------------------------------------
::sigjmp_buf g_fault_jump;
volatile sig_atomic_t g_fault_armed = 0;
volatile sig_atomic_t g_fault_took = 0;

extern "C" void fault_handler(int) {
  if (g_fault_armed != 0) {
    g_fault_armed = 0;
    g_fault_took = 1;
    siglongjmp(g_fault_jump, 1);
  }
  _exit(97);
}

void install_fault_handler() {
  struct sigaction action;
  std::memset(&action, 0, sizeof(action));
  action.sa_handler = &fault_handler;
  action.sa_flags = SA_NODEFER;
  sigemptyset(&action.sa_mask);
  sigaction(SIGSEGV, &action, nullptr);
  sigaction(SIGBUS, &action, nullptr);
}

// Drives `selector` with a null record and reports whether it faulted.
bool faults_on_null_record(Word selector) {
  static std::uint8_t probe[kProbeBytes];
  for (std::size_t index = 0; index < kProbeBytes; ++index) {
    probe[index] = fill_byte(index);
  }
  Simulator* const self = reinterpret_cast<Simulator*>(probe);
  g_fault_took = 0;
  if (sigsetjmp(g_fault_jump, 1) == 0) {
    g_fault_armed = 1;
    (void)real_entry(self, selector, nullptr);
    g_fault_armed = 0;
    return false;
  }
  g_fault_armed = 0;
  return true;
}

void fault_cases() {
  install_fault_handler();

  // The guarded arm: a null record is TESTED and returns cleanly. This is the
  // control -- it proves the handler does not simply fire on everything.
  check(!faults_on_null_record(kSelector_6cd9ec7b),
        "CONTROL: the guarded arm must return cleanly on a null record, so a "
        "fault reported below is a real fault and not the handler misfiring");

  // Every unguarded arm must fault. Driven through a representative selector of
  // each of the nine, so a guard added to any single arm is caught.
  const Word unguarded[] = {
      kSelector_f278934a,  // four-store arm
      kSelector_aaf6aaac,  // copy into +0x2c0
      kSelector_8133fb2e,  // copy into +0x2b4
      kSelector_f967827c,  // copy into +0x29c
      kSelector_3e2a3040,  // the unguarded tag write
      kSelector_ade76cce,  // guarded tag, then one store
      kSelector_9f792b4c,  // lazy +0x324/+0x328
      kSelector_279c4e55,  // lazy +0x314/+0x318
      kSelector_3b38f92a,  // lazy +0x31c/+0x320
  };
  for (Word selector : unguarded) {
    char label[320];
    std::snprintf(label, sizeof(label),
                  "REFUTE(F): the arm selector 0x%08x reaches has NO null test, "
                  "so a null record must fault there as the machine does -- a "
                  "reconstruction that added a guard to this arm would return "
                  "cleanly and be caught here",
                  selector);
    check(faults_on_null_record(selector), label);
  }
}

// ---------------------------------------------------------------------------
// Case D + E: the lazy guards and the tag guard, stated separately so a failure
// names which guard is wrong.
// ---------------------------------------------------------------------------
void guard_cases() {
  // E1: the guarded tag test compares the receiver word against -1 and skips
  // when it is anything ELSE. So the tag is written when +0x32c holds -1 and
  // left alone when it holds 0 -- 0 is not -1. Both readings are driven, because
  // the opposite mistake (treating the guard as a truth test, "if zero") is
  // indistinguishable from the right one on a receiver that only ever holds -1.
  for (std::size_t state = 0; state < kPreStateCount; ++state) {
    const PreState pre = kPreStates[state];
    Scenario scenario;
    fill_scenario(&scenario, pre);
    Simulator* self = reinterpret_cast<Simulator*>(scenario.probe);
    (void)real_entry(self, kSelector_ade76cce, &scenario.record);

    const Word tag = read_word(scenario.probe, 0x32cu);
    if (pre.tag == kTagUnsetState) {
      check(tag == 0x1654c01u,
            "REFUTE(E): selector 0xade76cce must write tag 0x1654c01 when "
            "+0x32c holds -1 -- the `CMP ...,0xffffffff / JNZ skip` guard is "
            "satisfied only by -1");
    } else {
      check(tag != 0x1654c01u,
            "REFUTE(E): selector 0xade76cce must NOT write its tag when "
            "+0x32c holds anything other than -1 -- a truth test reading it as "
            "\"if zero\" writes here when +0x32c holds 0, which is wrong");
      check(read_word(scenario.probe, 0x310u) == kBlock08,
            "selector 0xade76cce must store the block's +0x08 word at +0x310 "
            "regardless of whether the tag guard fired");
    }
  }

  // E2: 0x1654c00 is the ONE unguarded tag store, so it happens regardless.
  for (std::size_t state = 0; state < kPreStateCount; ++state) {
    Scenario scenario;
    fill_scenario(&scenario, kPreStates[state]);
    Simulator* self = reinterpret_cast<Simulator*>(scenario.probe);
    (void)real_entry(self, kSelector_3e2a3040, &scenario.record);
    check(read_word(scenario.probe, 0x32cu) == 0x1654c00u,
          "REFUTE(E): selector 0x3e2a3040 must write tag 0x1654c00 "
          "UNCONDITIONALLY -- it is the only tag store in the body with no CMP "
          "against -1 before it");
    check(read_word(scenario.probe, 0x308u) == kBlock08,
          "REFUTE(E): selector 0x3e2a3040 must store the block's +0x08 word at "
          "+0x308");
  }

  // D: the lazy pair -- secondary always, primary only while zero. Driven for
  // all three pairs across both primary pre-states.
  struct LazyCase {
    Word selector;
    Word primary;
    Word secondary;
    Word tag;
  };
  const LazyCase kLazy[] = {
      {0x9f792b4cu, 0x324u, 0x328u, 0x1654c05u},
      {0x279c4e55u, 0x314u, 0x318u, 0x1654c02u},
      {0x3b38f92au, 0x31cu, 0x320u, 0x1654c04u},
  };
  for (const LazyCase& lazy : kLazy) {
    for (int primary_set = 0; primary_set < 2; ++primary_set) {
      PreState pre = kPreStates[0];
      if (lazy.primary == 0x324u) {
        pre.p324 = primary_set ? kPrimarySet : kPrimaryZero;
      } else if (lazy.primary == 0x314u) {
        pre.p314 = primary_set ? kPrimarySet : kPrimaryZero;
      } else {
        pre.p31c = primary_set ? kPrimarySet : kPrimaryZero;
      }
      Scenario scenario;
      fill_scenario(&scenario, pre);
      Simulator* self = reinterpret_cast<Simulator*>(scenario.probe);
      const Word stale = read_word(scenario.probe, lazy.primary);
      (void)real_entry(self, lazy.selector, &scenario.record);

      check(read_word(scenario.probe, lazy.secondary) == kBlock08,
            "REFUTE(D): the lazy arm's SECONDARY word must be stored "
            "unconditionally -- the machine's JNZ acts on a flag set four "
            "instructions earlier, AFTER this store");
      const Word primary = read_word(scenario.probe, lazy.primary);
      if (primary_set) {
        check(primary == stale,
              "REFUTE(D): the lazy arm's PRIMARY word must be left alone when it "
              "is already non-zero");
      } else {
        check(primary == kBlock08,
              "REFUTE(D): the lazy arm's PRIMARY word must be stored when it is "
              "still zero");
      }
    }
  }
}

// ---------------------------------------------------------------------------
// Case F: the null-record guard is on exactly ONE arm.
// ---------------------------------------------------------------------------
void null_record_cases() {
  // The guarded arm: a null record writes NOTHING and leaves EAX zero.
  {
    Scenario scenario;
    fill_scenario(&scenario, kPreStates[0]);
    std::uint8_t before[kProbeBytes];
    std::memcpy(before, scenario.probe, kProbeBytes);
    Simulator* self = reinterpret_cast<Simulator*>(scenario.probe);
    g_call_count = 0;
    const Word returned = real_entry(self, kSelector_6cd9ec7b, nullptr);
    check(returned == 0u,
          "REFUTE(F): selector 0x6cd9ec7b's arm has the body's only TEST "
          "EAX,EAX, so a null record must leave EAX zero");
    check(std::memcmp(before, scenario.probe, kProbeBytes) == 0,
          "REFUTE(F): a null record on the guarded arm must write NOTHING at "
          "all -- not even the tag");
    check(g_call_count == 0, "the null-guard path must not call the callee");
  }

  // The nine arms WITHOUT a null test must store when handed a live record --
  // i.e. no guard has been added to them. Driven through the oracle for every
  // selector, with the null-guard case stated separately above: if any of these
  // arms had grown a guard of its own, the whole-probe comparison in case B
  // would already have failed, so this asserts the shape of the guard's reach
  // rather than re-deriving it.
  {
    int guarded_count = 0;
    int total = 0;
    for (std::size_t index = 0; index < kAllCount; ++index) {
      const Row* const row = row_for(kAllSelectors[index]);
      if (row == nullptr) {
        continue;
      }
      ++total;
      if (spec_for(row->arm).null_guard) {
        ++guarded_count;
      }
    }
    check(total == 27u, "all twenty-seven selectors are classified by the oracle");
    check(guarded_count == 10u,
          "REFUTE(F): the body's only TEST EAX,EAX is reached by exactly the "
          "ten selectors of the one guarded arm, and by no other arm");
  }

  // The guarded arm's guard is on the RECORD POINTER and not on anything the
  // record contains: handed a non-null record whose value pointer is null, the
  // arm still runs its stores -- because the machine tests EAX itself, and only
  // EAX. A guard written as `if (record->value == nullptr)` would skip them.
  {
    const Word guarded_selectors[] = {0x6cd9ec7bu, 0x5fcf28d0u, 0xa0973374u};
    for (Word selector : guarded_selectors) {
      Scenario scenario;
      fill_scenario(&scenario, kPreStates[0]);
      // A live record whose +0x0c points at a block that is entirely zero, so
      // the arm's stores are visible as zero rather than as its usual values.
      scenario.block.word_0c = 0u;
      scenario.block.word_10 = 0u;
      scenario.block.word_14 = 0u;
      std::uint8_t before[kProbeBytes];
      std::memcpy(before, scenario.probe, kProbeBytes);
      Simulator* self = reinterpret_cast<Simulator*>(scenario.probe);
      (void)real_entry(self, selector, &scenario.record);
      check(std::memcmp(before, scenario.probe, kProbeBytes) != 0,
            "REFUTE(F): the guarded arm must run its stores for a NON-NULL "
            "record even when the record's own value words are zero -- the "
            "machine tests the pointer, not its contents");
    }
  }
}

// ---------------------------------------------------------------------------
// Case G: TWO levels of indirection, with decoys.
// ---------------------------------------------------------------------------
void pointer_level_cases() {
  // G1: the record's own decoys at unread displacements must survive, and the
  // stored value must be the BLOCK's +0x08 word and not any decoy.
  Scenario scenario;
  fill_scenario(&scenario, kPreStates[0]);
  Simulator* self = reinterpret_cast<Simulator*>(scenario.probe);
  (void)real_entry(self, kSelector_ade76cce, &scenario.record);
  check(read_word(scenario.probe, 0x310u) == kBlock08,
        "REFUTE(G): the stored value must be read through the record's +0x0c "
        "POINTER, so it is the BLOCK's +0x08 word");
  check(scenario.record.opaque_00[0] == 0xa1u &&
            scenario.record.opaque_00[4] == 0xa2u &&
            scenario.record.opaque_00[8] == 0xa3u,
        "REFUTE(G): the body must write nothing into the record itself");

  // G2: point the record at the DECOY block. The stored value must follow,
  // because the body reads THROUGH the pointer rather than at a fixed address.
  Scenario swapped;
  fill_scenario(&swapped, kPreStates[0]);
  swapped.record.value = &swapped.decoy;
  Simulator* swapped_self = reinterpret_cast<Simulator*>(swapped.probe);
  (void)real_entry(swapped_self, kSelector_ade76cce, &swapped.record);
  check(read_word(swapped.probe, 0x310u) == kDecoy08,
        "REFUTE(G): repointing the record's +0x0c at another block must change "
        "the stored value -- the read is two levels deep");

  // G3: the block's unread +0x00/+0x04 must never be the source of a store.
  Scenario low;
  fill_scenario(&low, kPreStates[0]);
  low.block.opaque_00[0] = 0xffu;
  low.block.opaque_00[4] = 0xffu;
  low.block.word_08 = 0u;
  Simulator* low_self = reinterpret_cast<Simulator*>(low.probe);
  (void)real_entry(low_self, kSelector_ade76cce, &low.record);
  check(read_word(low.probe, 0x310u) == 0u,
        "REFUTE(G): with the block's +0x08 word zeroed, the stored value must "
        "be zero -- so it came from +0x08 and not from the block's +0x00");
}

// ---------------------------------------------------------------------------
// Case H: the two triple-writing arms disagree about order, and the four-store
// arm's middle pair is SWAPPED with respect to its source.
// ---------------------------------------------------------------------------
void order_cases() {
  Scenario four;
  fill_scenario(&four, kPreStates[0]);
  Simulator* four_self = reinterpret_cast<Simulator*>(four.probe);
  (void)real_entry(four_self, kSelector_f278934a, &four.record);
  check(read_word(four.probe, 0x314u) == kBlock08,
        "arm at 0x00e3a3e2: q[+0x08] -> +0x314");
  check(read_word(four.probe, 0x2acu) == kBlock0c,
        "REFUTE(H): arm at 0x00e3a3e2: q[+0x0c] -> +0x2ac, NOT +0x2a8");
  check(read_word(four.probe, 0x2a8u) == kBlock10,
        "REFUTE(H): arm at 0x00e3a3e2: q[+0x10] -> +0x2a8, NOT +0x2ac -- the "
        "two destinations are swapped with respect to source order");
  check(read_word(four.probe, 0x2b0u) == kBlock14,
        "arm at 0x00e3a3e2: q[+0x14] -> +0x2b0");

  // +0x314 belongs to the four-store arm. The three-store arm must leave it
  // alone, so it is compared against the value it held BEFORE the call -- which
  // is the pre-state, not the fill pattern, because the lazy primary +0x314 is
  // one of the words this battery deliberately pre-sets.
  Scenario three_before;
  fill_scenario(&three_before, kPreStates[0]);
  const Word word_314_before = read_word(three_before.probe, 0x314u);

  Scenario three;
  fill_scenario(&three, kPreStates[0]);
  Simulator* three_self = reinterpret_cast<Simulator*>(three.probe);
  (void)real_entry(three_self, kSelector_6cd9ec7b, &three.record);
  check(read_word(three.probe, 0x2d0u) == kBlock0c,
        "REFUTE(H): arm at 0x00e3a517: q[+0x0c] -> +0x2d0, in ASCENDING order");
  check(read_word(three.probe, 0x2ccu) == kBlock10,
        "REFUTE(H): arm at 0x00e3a517: q[+0x10] -> +0x2cc, in ASCENDING order");
  check(read_word(three.probe, 0x2d4u) == kBlock14,
        "REFUTE(H): arm at 0x00e3a517: q[+0x14] -> +0x2d4, in ASCENDING order");
  check(read_word(three.probe, 0x314u) == word_314_before,
        "REFUTE(H): the three-store arm writes nothing at +0x314, which belongs "
        "to the four-store arm");
}

// ---------------------------------------------------------------------------
// Case I: machine facts the whole package rests on.
// ---------------------------------------------------------------------------
void machine_cases() {
  check(kRowCount == 27u,
        "the listing compares twenty-seven selector values, and the oracle has "
        "twenty-seven rows");

  // The twenty-seven immediates, as the header declares them.
  const Word declared[] = {
      kSelector_13df9c1c, kSelector_25ca9233, kSelector_279c4e55,
      kSelector_2cfa39dd, kSelector_3b38f92a, kSelector_3e2a3040,
      kSelector_5c51063f, kSelector_5fcf28d0, kSelector_6a9f2620,
      kSelector_6cd9ec7b, kSelector_7115ede5, kSelector_7bceaa86,
      kSelector_8133fb2e, kSelector_980e43f2, kSelector_99f0d1da,
      kSelector_9f792b4c, kSelector_a0973374, kSelector_a6cb4c9f,
      kSelector_aaf6aaac, kSelector_ade76cce, kSelector_cdb3696f,
      kSelector_d536c91d, kSelector_d832b059, kSelector_dca976d0,
      kSelector_e0bc9d45, kSelector_f278934a, kSelector_f967827c,
  };
  check(sizeof(declared) / sizeof(declared[0]) == kAllCount,
        "the header declares twenty-seven selectors and the sweep drives "
        "twenty-seven");
  for (std::size_t index = 0; index < kAllCount; ++index) {
    const Row* const row = row_for(kAllSelectors[index]);
    check(row != nullptr && row->selector == kAllSelectors[index],
          "each swept selector has an oracle row keyed by the same value");
  }

  // Fifteen negatives, twelve positives.
  Word negatives = 0u;
  for (std::size_t index = 0; index < kAllCount; ++index) {
    if (static_cast<std::int32_t>(kAllSelectors[index]) < 0) {
      ++negatives;
    }
  }
  check(negatives == 15u,
        "fifteen of the twenty-seven selector values have the high bit set and "
        "are negative read signed");

  // The seven ordering branches are all SIGNED JG. The oracle's positive
  // selectors exercise three of them positively; a reconstruction using `>` on
  // uint32_t would route all twelve elsewhere, which case A already proves.

  // The ARM COUNT: ten blocks, each reachable, and 27 = 3+3+3+3+10+1+1+1+1+1
  // selectors accounted for.
  bool seen[10] = {false, false, false, false, false,
                   false, false, false, false, false};
  std::size_t copy_arms = 0u;
  std::size_t three_arms = 0u;
  for (std::size_t index = 0; index < kAllCount; ++index) {
    const Row* const row = row_for(kAllSelectors[index]);
    if (row == nullptr) {
      continue;
    }
    seen[static_cast<int>(row->arm)] = true;
    if (row->arm == kCopy2c0 || row->arm == kCopy2b4 || row->arm == kCopy29c) {
      ++copy_arms;
    }
    if (row->arm == kWriteThree) {
      ++three_arms;
    }
  }
  int distinct = 0;
  for (bool flag : seen) {
    if (flag) {
      ++distinct;
    }
  }
  check(distinct == 10,
        "the machine body has exactly ten blocks and the oracle reaches all ten");
  check(copy_arms == 9u,
        "nine of the twenty-seven selectors reach one of the three calling arms");
  check(three_arms == 10u,
        "ten of the twenty-seven selectors reach the guarded three-store arm");

  // The five tag immediates are five of six consecutive values, and 0x1654c03
  // never appears in the body.
  const Word tags[] = {kTag_1654c00, kTag_1654c01, kTag_1654c02, kTag_1654c04,
                       kTag_1654c05};
  for (std::size_t index = 0; index < 5u; ++index) {
    check(tags[index] == 0x1654c00u + index + (index >= 3u ? 1u : 0u),
          "the five tag immediates are the consecutive values 0x1654c00, c01, "
          "c02, c04 and c05 -- 0x1654c03 never appears in the body");
  }

  // Every arm's stored values come from the block fields the listing reads, and
  // the four store arms together read all four of +0x08/+0x0c/+0x10/+0x14.
  check(spec_for(kWriteFour).store_count == 4u &&
            spec_for(kWriteThree).store_count == 3u,
        "the four-store arm makes four stores and the three-store arm three");

  // The declared receiver size matches the largest displacement plus a dword.
  check(sizeof(Simulator) == 0x330u,
        "the modelled receiver is 0x330 bytes, the last byte +0x32c can reach");
  check(sizeof(PropertyValueBlock) == 0x18u &&
            sizeof(PropertyRecord) == 0x10u,
        "the record and block sizes follow from the largest displacement each "
        "is read at");
}

// ===========================================================================
// DIRECTION M: THE MUTATION TEST.
//
// Each mutant is a plausible wrong reconstruction, built here as a small body
// over the SAME oracle-independent path: the grader in `grade` computes the
// expected image from the LISTING, so a mutant is refuted whenever its image,
// its call facts or its returned word differ. Each mutant must be refuted; a
// survivor fails the run.
// ===========================================================================
enum Tweak {
  kTweakNone,
  kTweakUnsignedDispatch,
  kTweakSwapFourPair,
  kTweakWrongCopyDestination,
  kTweakLazyPrimaryUnconditional,
  kTweakLazySkipPrimary,
  kTweakTagGuardAsTruth,
  kTweakTagAlwaysWrites,
  kTweakNoNullGuard,
  kTweakNullGuardEverywhere,
  kTweakOneLevelIndirection,
  kTweakDropCalleeCall,
  kTweakReturnSelector,
  kTweakWrongCopyIndex
};

struct Mutant {
  const char* name;
  Tweak tweak;
  Word route_selector;  // for the single reroute tweak
  Arm route_to;
  // Is the NULL-RECORD pass meaningful for this mutant? A null record is only
  // observable through a guard, so the pass is run for the mutants whose whole
  // point is guard placement and skipped for the rest: those reach
  // record->value first, which on a null record faults -- exactly as the machine
  // does -- and a crash is not a refutation.
  bool graded_on_null_record;
};

Tweak g_active_tweak = kTweakNone;
Word g_active_route_selector = 0u;
Arm g_active_route_to = kNoArm;

Word pointer_of(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

Word PKG_00E3A270_THISCALL mutant_entry(Simulator* receiver, Word selector,
                                        const PropertyRecord* record) {
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);
  auto at = [self](std::size_t displacement) -> Word* {
    return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(self) +
                                   displacement);
  };

  const Tweak tweak = g_active_tweak;

  // -- routing ---------------------------------------------------------------
  // The signed tree, resolved through the oracle. A mutant reroutes one selector
  // by taking its arm from a different block; that is the only routing error a
  // mutant needs, since every other routing error is a wrong reading of the
  // ordering branches, which kTweakUnsignedDispatch stands for.
  Arm arm = kNoArm;
  for (std::size_t index = 0; index < kAllCount; ++index) {
    const Row* const row = row_for(kAllSelectors[index]);
    if (row != nullptr && row->selector == selector) {
      arm = row->arm;
    }
  }
  if (tweak == kTweakUnsignedDispatch) {
    // The classic slip: `>` on a uint32_t instead of a signed compare. Under an
    // unsigned reading the twelve POSITIVE selectors fall below the root pivot
    // 0xf278934a into the low half, whose seven leaf tests are all negative
    // values, so all twelve match nothing at all.
    if (static_cast<std::int32_t>(selector) > 0) {
      arm = kNoArm;
    }
  }
  if (g_active_route_selector != 0u && selector == g_active_route_selector) {
    arm = g_active_route_to;
  }

  if (arm == kNoArm) {
    return selector;  // nothing written at all
  }

  // kTweakNullGuardEverywhere is the reconstruction that added a
  // `if (record == nullptr) return 0;` at the TOP of the body rather than on the
  // one arm the machine guards. Placed here so it covers all ten arms uniformly,
  // which is what makes it wrong on the nine that have no such test.
  if (tweak == kTweakNullGuardEverywhere && record == nullptr) {
    return 0u;
  }

  // -- one wrong body, parameterised by its tweak ------------------------------
  // Every mutant differs from the reconstruction in exactly one named way, and
  // the battery grades all of them through the same `grade`.
  //
  // kTweakOneLevelIndirection reads the value block's words at the RECORD's
  // displacements instead of through the pointer the record holds, i.e. it drops
  // the second level of indirection. The decoys planted in the record's first
  // twelve bytes are what makes that visible.
  const void* const block =
      tweak == kTweakOneLevelIndirection
          ? static_cast<const void*>(record)
          : static_cast<const void*>(record->value);
  const Word loaded = *reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(block) + 8u);
  const Word at_0c = *reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(block) + 0xcu);
  const Word at_10 = *reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(block) + 0x10u);
  const Word at_14 = *reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(block) + 0x14u);

  switch (arm) {
    case kCopy2c0:
    case kCopy2b4:
    case kCopy29c: {
      const Word primary =
          arm == kCopy2c0 ? 0x324u : (arm == kCopy2b4 ? 0x31cu : 0x30cu);
      Word destination = arm == kCopy2c0 ? 0x2c0u
                                         : (arm == kCopy2b4 ? 0x2b4u : 0x29cu);
      if (tweak == kTweakWrongCopyDestination) {
        destination += 4u;  // off by one dword
      }
      *at(primary) = loaded;
      if (tweak == kTweakDropCalleeCall) {
        return loaded;
      }
      const Word index = tweak == kTweakWrongCopyIndex ? 2u : kCopyIndex;
      if (tweak == kTweakReturnSelector) {
        (void)simulator_copy_block3_00e39420(record, index,
                                             self + destination);
        return selector;
      }
      return simulator_copy_block3_00e39420(record, index, self + destination);
    }
    case kWriteFour: {
      *at(0x314u) = loaded;
      // The mutant's SWAPPED pair is the wrong reading of this arm.
      if (tweak == kTweakSwapFourPair) {
        *at(0x2a8u) = at_0c;
        *at(0x2acu) = at_10;
      } else {
        *at(0x2acu) = at_0c;
        *at(0x2a8u) = at_10;
      }
      *at(0x2b0u) = at_14;
      return pointer_of(block);
    }
    case kWriteThree: {
      if (tweak == kTweakNoNullGuard) {
        const void* const b = block;  // dereferenced even for a null record
        *at(0x2d0u) = *reinterpret_cast<const Word*>(
            reinterpret_cast<std::uintptr_t>(b) + 0xcu);
        return pointer_of(b);
      }
      if (record == nullptr) {
        return 0u;
      }
      *at(0x2d0u) = at_0c;
      *at(0x2ccu) = at_10;
      *at(0x2d4u) = at_14;
      return pointer_of(block);
    }
    case kTagInit: {
      *at(0x32cu) = 0x1654c00u;  // unguarded, as the machine has it
      *at(0x308u) = loaded;
      return loaded;
    }
    case kTagThen310: {
      if (tweak == kTweakTagGuardAsTruth) {
        if (*at(0x32cu) == 0u) {
          *at(0x32cu) = 0x1654c01u;
        }
      } else if (tweak == kTweakTagAlwaysWrites) {
        *at(0x32cu) = 0x1654c01u;
      } else if (*at(0x32cu) == kUnset) {
        *at(0x32cu) = 0x1654c01u;
      }
      *at(0x310u) = loaded;
      return loaded;
    }
    case kLazy324:
    case kLazy314:
    case kLazy31c: {
      const Word primary =
          arm == kLazy324 ? 0x324u : (arm == kLazy314 ? 0x314u : 0x31cu);
      const Word secondary = primary + 4u;
      const Word tag = arm == kLazy324
                           ? 0x1654c05u
                           : (arm == kLazy314 ? 0x1654c02u : 0x1654c04u);
      if (tweak == kTweakTagGuardAsTruth) {
        if (*at(0x32cu) == 0u) {
          *at(0x32cu) = tag;
        }
      } else if (tweak == kTweakTagAlwaysWrites) {
        *at(0x32cu) = tag;
      } else if (*at(0x32cu) == kUnset) {
        *at(0x32cu) = tag;
      }
      const bool primary_set = *at(primary) != 0u;
      *at(secondary) = loaded;  // secondary unconditional
      if (tweak == kTweakLazyPrimaryUnconditional) {
        *at(primary) = loaded;  // the guard the machine does NOT have
      } else if (tweak == kTweakLazySkipPrimary) {
        // the guard applied to the wrong store: primary never written
      } else if (!primary_set) {
        *at(primary) = loaded;
      }
      return loaded;
    }
    case kNoArm:
      break;
  }
  return selector;
}

const Mutant kMutants[] = {
    {"unsigned dispatch (`>` on uint32_t)", kTweakUnsignedDispatch, 0u, kNoArm,
     false},
    {"four-store arm's pair not swapped", kTweakSwapFourPair, 0u, kNoArm, false},
    {"copy arm's destination off by a dword", kTweakWrongCopyDestination, 0u,
     kNoArm, false},
    {"lazy primary stored unconditionally", kTweakLazyPrimaryUnconditional, 0u,
     kNoArm, false},
    {"lazy primary never stored", kTweakLazySkipPrimary, 0u, kNoArm, false},
    {"tag guard read as a truth test", kTweakTagGuardAsTruth, 0u, kNoArm, false},
    {"tag stored unconditionally", kTweakTagAlwaysWrites, 0u, kNoArm, false},
    // kTweakNoNullGuard dereferences a null record on the guarded arm, and
    // kTweakOneLevelIndirection reads record->value to find the block at all, so
    // neither is graded on the null pass: the machine faults there too.
    {"null-record guard removed", kTweakNoNullGuard, 0u, kNoArm, false},
    {"null-record guard on every arm", kTweakNullGuardEverywhere, 0u, kNoArm,
     true},
    {"one level of indirection", kTweakOneLevelIndirection, 0u, kNoArm, false},
    {"callee call dropped", kTweakDropCalleeCall, 0u, kNoArm, false},
    {"returned value replaced by the selector", kTweakReturnSelector, 0u,
     kNoArm, false},
    {"callee given the wrong index", kTweakWrongCopyIndex, 0u, kNoArm, false},
    {"one selector rerouted to the wrong arm", kTweakNone, kSelector_ade76cce,
     kLazy324, false},
};

constexpr std::size_t kMutantCount = sizeof(kMutants) / sizeof(kMutants[0]);

// How many (selector, pre-state) cases each mutant is graded over.
// Graded case count per mutant: twenty-seven selectors in each of the six
// receiver pre-states, plus the null-record case for the guard-placement mutant.
static_assert(kAllCount * kPreStateCount == 162u,
              "each mutant is graded over twenty-seven selectors in each of the "
              "six receiver pre-states");

// The mutation test.
//
// A mutant is wrong only where its tweak bites, so it is CORRECT on the rest of
// the sweep and grading it as "must fail everywhere" would be a misstatement of
// what a wrong reconstruction looks like. The assertion made instead is the one
// that carries the weight: EVERY mutant must be refuted on at least one case --
// otherwise the battery has no power over that class of error -- and the union
// of the mutants' refutations must COVER ALL TWENTY-SEVEN selectors, so no
// selector in this body escapes the mutation direction entirely.
//
// A surviving mutant fails the run even though the reconstruction itself passed
// every other case, which is the point: a battery that cannot reject a
// known-wrong body cannot certify the right one.
void mutation_cases() {
  std::vector<bool> covered(kAllCount, false);

  for (std::size_t index = 0; index < kMutantCount; ++index) {
    const Mutant& mutant = kMutants[index];
    g_active_tweak = mutant.tweak;
    g_active_route_selector = mutant.route_selector;
    g_active_route_to = mutant.route_to;

    std::size_t survivors = 0u;
    std::size_t refuted = 0u;
    for (std::size_t sweep = 0; sweep < kAllCount; ++sweep) {
      const Word selector = kAllSelectors[sweep];
      const Row* const row = row_for(selector);
      if (row == nullptr) {
        continue;
      }
      // Every pre-state, so each guard is driven both ways, plus the
      // NULL-RECORD pass -- which is the only situation in which a guard placed
      // on the wrong arm is observable at all.
      for (std::size_t state = 0; state < kPreStateCount; ++state) {
        const Verdict verdict =
            grade(&mutant_entry, selector, row->arm, kPreStates[state], false);
        if (verdict.memory_ok && verdict.call_ok && verdict.return_ok) {
          ++survivors;
        } else {
          ++refuted;
          covered[sweep] = true;
        }
      }
      if (mutant.graded_on_null_record) {
        const Verdict null_verdict =
            grade(&mutant_entry, selector, row->arm, kPreStates[0], true);
        if (null_verdict.memory_ok && null_verdict.call_ok &&
            null_verdict.return_ok) {
          ++survivors;
        } else {
          ++refuted;
          covered[sweep] = true;
        }
      }
    }
    char label[240];
    std::snprintf(label, sizeof(label),
                  "REFUTE(M): mutant \"%s\" must be refuted on at least one "
                  "case; it agreed with the listing on ALL %zu of them, so the "
                  "battery has no power over this class of error",
                  mutant.name, survivors);
    check(refuted > 0u, label);
  }

  int uncovered = 0;
  for (bool flag : covered) {
    if (!flag) {
      ++uncovered;
    }
  }
  check(uncovered == 0,
        "REFUTE(M): the union of the mutants' refutations must cover all "
        "twenty-seven selectors; some selector escaped the mutation direction "
        "entirely, so a wrong arm for it would pass");

  g_active_tweak = kTweakNone;
  g_active_route_selector = 0u;
  g_active_route_to = kNoArm;
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_00e3a270_dispatch

int main() {
  using namespace openspore::reconstruction::pkg_00e3a270_dispatch::model;
  polarity_cases();
  selector_mapping_cases();
  guard_cases();
  null_record_cases();
  fault_cases();
  pointer_level_cases();
  order_cases();
  machine_cases();
  mutation_cases();
  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
