// PKG-SWARM-W1-00EC3BE0 -- VA 0x00ec3be0
// Behavioural model test for FUN_00ec3be0, the Sporepedia-online five-key
// property handler.
//
// The one direct callee -- 0x00642530 -- is defined here as an observer, so the
// test sees every transfer the reconstruction makes, with which arguments, in
// which order, and gets to decide what it does to memory while it is there. That
// is the only way to test the two orderings this body actually has: the call
// happens BEFORE the record is read, and the flag byte is written AFTER it.
//
// WHAT IS ASSERTED is what the 58-instruction listing fixes and nothing more:
//
//   * exactly one direct transfer, to 0x00642530, made on EVERY path -- the
//     hit path, the type-miss path and the no-match path alike;
//   * that call's two arguments: the receiver (in ECX) and a POINTER to the
//     caller's 12-byte record, and that the record is read AFTER the call, so a
//     callee that writes through the pointer changes what this body stores;
//   * that the callee's EAX return is never read;
//   * the five key ids and the one type hash, each against its own arm, and each
//     id's own receiver displacement -- one byte at 0x78, 0x79, 0x7a, 0x7b, 0x7c;
//   * the value test as an EQUALITY against 1, driven with values where "== 1"
//     and "!= 0" and "store the value" all disagree;
//   * the pivot compare as an UNSIGNED above, driven with the three high-bit-set
//     ids and with every id +/- 1, which is the only thing that separates JA from
//     JG here;
//   * that no other key id writes anything, including the pivot's own neighbours
//     and the type hash used as an id;
//   * that a type-hash miss writes nothing, driven with near-miss hashes;
//   * that the store is exactly one BYTE, checked by byte-diffing a receiver
//     whose whole 0x90-byte probe (the modeled object plus a 0x10-byte canary
//     past its end) was pre-filled with a pattern -- so a dword store, a wrong
//     displacement, a stale-field write or a clear-the-block all show up as
//     changed bytes somewhere they must not be;
//   * the ABI, measured rather than asserted: ESP sampled inside a trampoline
//     before the push and after the return, which is equal only if the callee
//     popped its own four bytes.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names the wrong reconstruction it is aimed at:
//
//   A  a key id paired with the wrong receiver displacement (a swapped pair, or
//      a copy-paste of the neighbouring arm);
//   B  the value test read as "!= 0", or the value word stored verbatim instead
//      of a boolean -- driven with 0, 2, 3, 0x100, 0x7fffffff, 0xffffffff;
//   C  the pivot compare read as a SIGNED above, which makes all three high ids
//      unreachable because they have the high bit set;
//   D  a boundary that is off by one in either direction (an id equal to a
//      neighbour of a real one), or an extra match the machine does not have;
//   E  the type-hash guard dropped, or compared with < / <= , or off by one;
//   F  the record read before the callee is given it, or the callee's EAX return
//      used as the value, or the flag written before the call;
//   G  the other four flag bytes cleared instead of left alone;
//   H  the call made conditionally, or made twice, or skipped on the miss path;
//   I  a two-level dereference -- the id read through a pointer, or read out of
//      the receiver instead of out of the record;
//   J  the id read from the record's wrong word;
//   L  a dword store, a displacement outside the five, or a write past the end
//      of the modeled object;
//   M  a cdecl/fastcall reconstruction (the callee does not pop the word, or the
//      receiver does not arrive in ECX);
//   N  a dispatch gated on some receiver word this body never reads.
//
// What is NOT asserted, and why:
//
//   * EAX on return. The declared return type is void and the machine leaves
//     three different incidental values there depending on the path, so there is
//     nothing for the test to say. (The test DOES assert the opposite fact that
//     matters: that the callee's return value is discarded.)
//   * WHICH register carries the SETZ result. The bytes at 0x00ec3c11, 0x00ec3c29,
//     0x00ec3c56, 0x00ec3c6e, 0x00ec3c86 write AL, CL, CL, AL and CL, and that
//     variety is a register-allocation fact with no effect on the stored byte.
//     Nothing here checks it, and the per-arm comments in the .cpp record it
//     because it is what makes the arms matchable to the bytes.
//   * What 0x00642530 does beyond what the listing of 0x00ec3be0 depends on. The
//     observer mutates memory and returns a poison value on purpose; everything
//     it does is a test fixture, not a claim about that body.
//   * The five key ids' preimages, and therefore what the five flag bytes MEAN.
//     No record in this repository maps any of the five hashed ids to a name, so
//     the test asserts the mapping id -> displacement and nothing about meaning.
//   * The object's real size. This body never reads a receiver byte and never
//     writes past 0x7c; 0x00642530 reaches only +0x38, so the modeled 0x80 is
//     this package's lower bound and not a claim about the real layout.

#include "sw1_00ec3be0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_00ec3be0 {
namespace {

// The five receiver displacements, as literals, so a wrong one in the header
// cannot silently agree with a wrong one in the .cpp.
constexpr std::size_t kFlag78 = 0x78u;
constexpr std::size_t kFlag79 = 0x79u;
constexpr std::size_t kFlag7a = 0x7au;
constexpr std::size_t kFlag7b = 0x7bu;
constexpr std::size_t kFlag7c = 0x7cu;

// The modeled object is 0x80 bytes; the probe is that plus a 0x10-byte canary
// past its end, so a store at +0x7d or beyond is visible as a changed byte.
constexpr std::size_t kProbeSize = 0x90u;

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// -- the receiver probe -------------------------------------------------------
struct Receiver {
  std::uint8_t bytes[kProbeSize];
};

// Every byte of the probe gets a distinct, non-boolean pattern, so "this byte
// became 0 or 1" and "this byte became something" are distinguishable and a
// cleared or zeroed region cannot hide behind a pre-zeroed one.
void fill_receiver(Receiver& receiver, std::uint8_t pattern) {
  for (std::size_t index = 0; index < kProbeSize; ++index) {
    receiver.bytes[index] = static_cast<std::uint8_t>(pattern + index);
  }
}

SporepediaOnlineAsset* as_asset(Receiver& receiver) {
  static_assert(sizeof(SporepediaOnlineAsset) <= kProbeSize,
                "the probe must be able to hold the modeled object");
  return reinterpret_cast<SporepediaOnlineAsset*>(&receiver);
}

// How many probe bytes changed, split by whether they are one of the five flag
// bytes. The machine makes exactly one byte write on an arm and no other write at
// all on a miss, so a correct model reports inside == 0 or 1 and outside == 0.
struct Diff {
  int inside = 0;
  int outside = 0;
  std::size_t first_outside = kProbeSize;
  std::size_t first_inside = kProbeSize;
};

Diff diff_receiver(const Receiver& before, const Receiver& after) {
  Diff diff;
  for (std::size_t index = 0; index < kProbeSize; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    if (index >= kFlag78 && index <= kFlag7c) {
      ++diff.inside;
      if (diff.first_inside == kProbeSize) {
        diff.first_inside = index;
      }
    } else {
      ++diff.outside;
      if (diff.first_outside == kProbeSize) {
        diff.first_outside = index;
      }
    }
  }
  return diff;
}

std::uint8_t flag_at(const Receiver& receiver, std::size_t displacement) {
  return receiver.bytes[displacement];
}

std::size_t changed_flags(const Receiver& receiver) {
  std::size_t count = 0;
  for (std::size_t index = kFlag78; index <= kFlag7c; ++index) {
    if (receiver.bytes[index] == 0u || receiver.bytes[index] == 1u) {
      ++count;
    }
  }
  return count;
}

// -- the key record -----------------------------------------------------------
PropertyKeyRecord make_record(Word id, Word type, Word value) {
  PropertyKeyRecord record{};
  record.field_00 = id;
  record.field_04 = type;
  record.field_08 = value;
  return record;
}

// -- the observer for 0x00642530 ---------------------------------------------
enum : int {
  kCalleeDefault = 0,
  kCalleeWriteValue,   // overwrite the record's value word at call time
  kCalleeWriteFlags,   // overwrite all five flag bytes at call time
  kCalleeBoth,
};

struct CalleeRecord {
  int calls = 0;
  SporepediaOnlineAsset* receiver = nullptr;
  const PropertyKeyRecord* key = nullptr;
  // Sampled INSIDE the call, so what the body had already written is observable.
  std::uint8_t flags_seen[5] = {};
  int mode = kCalleeDefault;
  Word poison_return = 0xdeadbeefu;
  // When mode writes the value word, this is what it writes.
  Word value_to_write = 0u;
  // When mode writes the flags, this is what it writes into all five.
  std::uint8_t flag_byte_to_write = 0u;
};

CalleeRecord g_callee;

// The receiver the current case is exercising, so the observer can sample it.
std::uint8_t* g_active_receiver = nullptr;

void configure_callee(int mode, Word value_to_write = 0u, std::uint8_t flag_byte = 0u) {
  g_callee = CalleeRecord();
  g_callee.mode = mode;
  g_callee.value_to_write = value_to_write;
  g_callee.flag_byte_to_write = flag_byte;
}

}  // namespace

// 0x00642530. The real body's 160 bytes show it taking the key pointer at its
// [ESP+0x4], reading the record's +0x00, +0x04 and +0x08, comparing the +0x04
// against 0x2e1a75d and storing the +0x08 into the receiver's +0x28 -- and ending
// `C2 04 00` (RET 0x4), so __thiscall with the receiver in ECX. It is a SIBLING
// handler for the same property vocabulary: none of the seven key ids in its own
// dispatch is one of this body's five, which is why this body calls it and then
// does its own matching.
//
// The observer records what it was handed, samples the receiver's five flag bytes
// at the instant of the call (which is what proves the body writes them AFTER, and
// not before), optionally mutates the record's value word and the receiver's flag
// bytes to model a callee with side effects on the very data this body is about to
// read and write, and returns a poison EAX (0x00ec3bee overwrites it unread).
extern "C" Word SW1_00EC3BE0_THISCALL sporepedia_property_apply_00642530(
    SporepediaOnlineAsset* receiver, const PropertyKeyRecord* key) {
  ++g_callee.calls;
  g_callee.receiver = receiver;
  g_callee.key = key;
  if (g_active_receiver != nullptr) {
    for (std::size_t index = 0; index < 5; ++index) {
      g_callee.flags_seen[index] = g_active_receiver[kFlag78 + index];
    }
  }
  if ((g_callee.mode == kCalleeWriteValue || g_callee.mode == kCalleeBoth) &&
      key != nullptr) {
    // The record is const-qualified in the reconstruction's prototype because
    // THIS body never writes through it. The callee is a different function with
    // its own access, and the machine shows this body's value read happening
    // after the call, so a write here is exactly the interference to test against.
    Word* const value = const_cast<Word*>(word_at(key, 8));
    *value = g_callee.value_to_write;
  }
  if ((g_callee.mode == kCalleeWriteFlags || g_callee.mode == kCalleeBoth) &&
      g_active_receiver != nullptr) {
    for (std::size_t index = 0; index < 5; ++index) {
      g_active_receiver[kFlag78 + index] = g_callee.flag_byte_to_write;
    }
  }
  return g_callee.poison_return;
}

namespace {

// One full call, with the fixture wiring the observer needs.
void drive(Receiver& receiver, const PropertyKeyRecord& record) {
  g_active_receiver = receiver.bytes;
  re_00ec3be0(as_asset(receiver), &record);
  g_active_receiver = nullptr;
}

// The pattern the probe is pre-filled with, so a test can tell "unchanged" from
// "written".
constexpr std::uint8_t kPattern = 0xa5u;

// A. Each of the five key ids writes its OWN flag byte and leaves the other four
// alone. Every id is driven twice, once storing 1 and once storing 0, so a mapping
// that is right for one value cannot be right by accident for the other.
void case_each_id_writes_only_its_own_flag() {
  struct Expectation {
    Word id;
    std::size_t flag;
  };
  const Expectation table[5] = {
      {0x15e8afc8u, kFlag78}, {0x5a3584a7u, kFlag79}, {0xb91fba14u, kFlag7a},
      {0xd22f5e35u, kFlag7b}, {0xdb4675ddu, kFlag7c},
  };

  for (int entry = 0; entry < 5; ++entry) {
    for (int value_index = 0; value_index < 2; ++value_index) {
      const Word value = (value_index == 0) ? 1u : 0u;
      const std::uint8_t expected = (value_index == 0) ? std::uint8_t{1} : std::uint8_t{0};

      Receiver receiver;
      fill_receiver(receiver, kPattern);
      Receiver before = receiver;
      const PropertyKeyRecord record = make_record(table[entry].id, 0x2e1a75du, value);
      configure_callee(kCalleeDefault);
      drive(receiver, record);

      check(g_callee.calls == 1, "A0: exactly one transfer to the callee");
      check(flag_at(receiver, table[entry].flag) == expected,
            "A1: the id's own flag byte holds the boolean");
      // The other four must still hold the pattern. 0xa5 + displacement is never
      // 0 or 1, so this also proves they were not written with a false.
      int other_flags_written = 0;
      for (std::size_t index = kFlag78; index <= kFlag7c; ++index) {
        if (index == table[entry].flag) {
          continue;
        }
        if (receiver.bytes[index] == 0u || receiver.bytes[index] == 1u) {
          ++other_flags_written;
        }
      }
      check(other_flags_written == 0, "A2: the other four flag bytes were not written");
      const Diff diff = diff_receiver(before, receiver);
      check(diff.inside == 1, "A3: exactly one of the five flag bytes changed");
      check(diff.outside == 0, "A4: no byte outside the five flag bytes changed");
    }
  }
}

// B. The value test is an EQUALITY against 1. Every value here is chosen so that
// "== 1", "!= 0" and "store the word" give three different answers.
void case_value_test_is_equality_against_one() {
  struct Value {
    Word value;
    std::uint8_t expected;
  };
  const Value values[8] = {
      {0u, 0u},          {1u, 1u},          {2u, 0u},          {3u, 0u},
      {0x100u, 0u},      {0x7fffffffu, 0u}, {0xffffffffu, 0u}, {0x80000000u, 0u},
  };
  for (int index = 0; index < 8; ++index) {
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    const PropertyKeyRecord record =
        make_record(0x15e8afc8u, 0x2e1a75du, values[index].value);
    configure_callee(kCalleeDefault);
    drive(receiver, record);
    check(flag_at(receiver, kFlag78) == values[index].expected,
          "B1: the stored byte is (value == 1), not (value != 0) and not the value");
    check(changed_flags(receiver) == 1, "B2: still exactly one flag byte written");
  }
}

// C. The pivot compare at 0x00ec3bf5 is an UNSIGNED above. Three of the five ids
// have the high bit set, so a signed compare would send all three into the LOW
// group: two flags unreachable and one arm mis-paired. Driving the three high ids
// is therefore the test of the compare's signedness, and it is a test no other
// case can make.
void case_pivot_compare_is_unsigned() {
  struct High {
    Word id;
    std::size_t flag;
  };
  const High high[3] = {
      {0xb91fba14u, kFlag7a}, {0xd22f5e35u, kFlag7b}, {0xdb4675ddu, kFlag7c},
  };
  for (int entry = 0; entry < 3; ++entry) {
    check(high[entry].id > 0x80000000u,
          "C0: the high-group ids really do have the sign bit set");
    check(high[entry].id > 0x5a3584a7u,
          "C1: and really are above the pivot UNSIGNED");
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    const PropertyKeyRecord record = make_record(high[entry].id, 0x2e1a75du, 1u);
    configure_callee(kCalleeDefault);
    drive(receiver, record);
    check(flag_at(receiver, high[entry].flag) == 1u,
          "C2: a sign-bit-set id still reaches its own high-group arm");
    check(flag_at(receiver, kFlag78) == static_cast<std::uint8_t>(kPattern + kFlag78),
          "C3: and does not fall through into the low group's arm");
  }
}

// D. No other key id writes anything. The list is the neighbourhood of the five
// real ids in both directions, the two ends of the unsigned range, the type hash
// used as an id, and a couple of ordinary values. A boundary that is off by one,
// an extra match the machine does not have, or a compare that is <= instead of ==
// all show up here.
void case_unknown_ids_write_nothing() {
  const Word ids[17] = {
      0u,
      1u,
      0x15e8afc7u,
      0x15e8afc9u,
      0x2e1a75du,  // the type hash, used as an id
      0x5a3584a6u,
      0x5a3584a8u,
      0x7fffffffu,
      0x80000000u,
      0xb91fba13u,
      0xb91fba15u,
      0xd22f5e34u,
      0xd22f5e36u,
      0xdb4675dcu,
      0xdb4675deu,
      0xfffffffeu,
      0xffffffffu,
  };
  for (int index = 0; index < 17; ++index) {
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    Receiver before = receiver;
    const PropertyKeyRecord record = make_record(ids[index], 0x2e1a75du, 1u);
    configure_callee(kCalleeDefault);
    drive(receiver, record);
    const Diff diff = diff_receiver(before, receiver);
    check(diff.inside == 0 && diff.outside == 0,
          "D1: an id the machine does not know writes nothing at all");
    check(g_callee.calls == 1, "D2: and the callee was still handed the record");
  }
}

// E. The type-hash guard, on EVERY arm. All five ids are driven against all five
// type hashes, because a guard dropped on ONE arm is invisible if the type-hash
// case only ever drives one id -- which is exactly the defect a mutation check
// found in an earlier draft of this test. The types are a near miss by one in
// either direction, the type hash 0x00642530's own dispatch uses on its other arm
// (0x2e1a7ff), zero and all ones; only the exact hash may write.
void case_type_hash_must_match_exactly() {
  const Word types[6] = {0u, 0x2e1a75cu, 0x2e1a75eu, 0x2e1a7ffu, 0xffffffffu, 0x2e1a75du};
  const Word ids[5] = {0x15e8afc8u, 0x5a3584a7u, 0xb91fba14u, 0xd22f5e35u, 0xdb4675ddu};
  const std::size_t flags[5] = {kFlag78, kFlag79, kFlag7a, kFlag7b, kFlag7c};
  for (int id_index = 0; id_index < 5; ++id_index) {
    for (int index = 0; index < 6; ++index) {
      Receiver receiver;
      fill_receiver(receiver, kPattern);
      Receiver before = receiver;
      const PropertyKeyRecord record = make_record(ids[id_index], types[index], 1u);
      configure_callee(kCalleeDefault);
      drive(receiver, record);
      const Diff diff = diff_receiver(before, receiver);
      const bool exact = (types[index] == 0x2e1a75du);
      check(exact ? (diff.inside == 1 && diff.outside == 0)
                  : (diff.inside == 0 && diff.outside == 0),
            "E1: only the exact type hash reaches the store, on every arm");
      check(flag_at(receiver, flags[id_index]) ==
                (exact ? std::uint8_t{1} : static_cast<std::uint8_t>(kPattern + flags[id_index])),
            "E2: a type-hash miss leaves this arm's own flag byte untouched");
      check(g_callee.calls == 1, "E3: the callee is called whatever the type hash is");
    }
  }
}

// F. ORDER, on every arm. The body calls 0x00642530 before it reads the record,
// and writes the flag after the call returns. The observer writes a poison value
// into the record's value word at call time: a reconstruction that captured the
// value before delegating stores 1, and the machine -- whose CMP is downstream of
// the call on all five arms -- stores 0. The observer also samples the five flag
// bytes at the instant of the call, which must still be the pre-call pattern.
void case_the_record_is_read_after_the_callee_returns() {
  const Word ids[5] = {0x15e8afc8u, 0x5a3584a7u, 0xb91fba14u, 0xd22f5e35u, 0xdb4675ddu};
  const std::size_t flags[5] = {kFlag78, kFlag79, kFlag7a, kFlag7b, kFlag7c};

  // The ordering itself, on the lowest arm, with the observer sampling the
  // receiver.
  {
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    const PropertyKeyRecord record = make_record(0x15e8afc8u, 0x2e1a75du, 1u);
    configure_callee(kCalleeWriteValue, /*value_to_write=*/2u);
    drive(receiver, record);

    check(g_callee.calls == 1, "F1: the callee ran");
    check(g_callee.receiver == as_asset(receiver),
          "F2: ECX carried the receiver the caller passed");
    check(g_callee.key == &record, "F3: the callee got a POINTER to the caller's record");
    check(flag_at(receiver, kFlag78) == 0u,
          "F4: the value read is the callee's, not the caller's (it wrote 2, so 0 is stored)");
    for (int index = 0; index < 5; ++index) {
      check(g_callee.flags_seen[index] == static_cast<std::uint8_t>(kPattern + kFlag78 + index),
            "F5: no flag byte had been written when the callee was entered");
    }
  }

  // The same ordering on all five arms, so "reads the record before delegating"
  // cannot hide on the four arms the block above does not touch. The caller's
  // value is 1 and the callee's is 0, so a body that captured the value first
  // would store 1 where the machine stores 0.
  for (int id_index = 0; id_index < 5; ++id_index) {
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    PropertyKeyRecord record = make_record(ids[id_index], 0x2e1a75du, 1u);
    configure_callee(kCalleeWriteValue, /*value_to_write=*/0u);
    drive(receiver, record);
    check(g_callee.key == &record, "F6: the callee got this caller's record pointer");
    check(flag_at(receiver, flags[id_index]) == 0u,
          "F7: every arm reads the value after the call, not before");
  }
}

// G. The body writes ONE byte and leaves the other four exactly as the callee left
// them, on every arm. The observer scribbles 0x5a over all five first; only the
// matched arm's byte may change.
void case_the_other_four_flags_are_left_alone() {
  const Word ids[5] = {0x15e8afc8u, 0x5a3584a7u, 0xb91fba14u, 0xd22f5e35u, 0xdb4675ddu};
  const std::size_t flags[5] = {kFlag78, kFlag79, kFlag7a, kFlag7b, kFlag7c};

  for (int id_index = 0; id_index < 5; ++id_index) {
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    const PropertyKeyRecord record = make_record(ids[id_index], 0x2e1a75du, 1u);
    configure_callee(kCalleeWriteFlags, /*value_to_write=*/0u, /*flag_byte=*/0x5au);
    drive(receiver, record);

    check(flag_at(receiver, flags[id_index]) == 1u,
          "G1: the matched arm's byte is overwritten");
    for (int other = 0; other < 5; ++other) {
      if (other == id_index) {
        continue;
      }
      check(flag_at(receiver, flags[other]) == 0x5au,
            "G2: the other four keep the callee's value; the body does not clear them");
    }
  }
}

// H. The call is unconditional: one transfer on the hit path, one on the type-miss
// path, one on the no-match path. Never two, never zero.
void case_the_callee_runs_on_every_path() {
  {
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    const PropertyKeyRecord record = make_record(0x5a3584a7u, 0x2e1a75du, 1u);
    configure_callee(kCalleeDefault);
    drive(receiver, record);
    check(g_callee.calls == 1, "H1: one transfer on the hit path");
  }
  {
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    const PropertyKeyRecord record = make_record(0x5a3584a7u, 0u, 1u);
    configure_callee(kCalleeDefault);
    drive(receiver, record);
    check(g_callee.calls == 1, "H2: one transfer on the type-miss path");
  }
  {
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    const PropertyKeyRecord record = make_record(0x12345678u, 0x2e1a75du, 1u);
    configure_callee(kCalleeDefault);
    drive(receiver, record);
    check(g_callee.calls == 1, "H3: one transfer on the no-match path");
  }
  {
    // The callee's return value is never read: 0x00ec3bee overwrites EAX from
    // memory. A reconstruction that used it as the flag's value would store the
    // poison word's low bit instead of the record's.
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    const PropertyKeyRecord record = make_record(0xb91fba14u, 0x2e1a75du, 1u);
    configure_callee(kCalleeDefault);
    g_callee.poison_return = 0x00000000u;  // low bit clear
    drive(receiver, record);
    check(flag_at(receiver, kFlag7a) == 1u,
          "H4: the stored boolean comes from the record, not from the callee's EAX");
    receiver = Receiver();
    fill_receiver(receiver, kPattern);
    g_callee.poison_return = 0x00000001u;  // low bit set
    drive(receiver, record);
    check(flag_at(receiver, kFlag7a) == 1u,
          "H5: and again with the opposite low bit, still from the record");
  }
}

// I. POINTER LEVEL. The id is the record's own leading word, read as a value; the
// receiver is never read. Two records live side by side in one array and the
// SECOND is driven with a matching id, and the receiver is seeded with copies of
// that id at several displacements. Both would change the answer for a
// reconstruction that dereferenced twice or that read the id out of the receiver.
void case_the_id_is_the_records_own_word() {
  PropertyKeyRecord pair[2];
  pair[0] = make_record(0xdb4675ddu, 0x2e1a75du, 1u);
  pair[1] = make_record(0x15e8afc8u, 0x2e1a75du, 1u);

  Receiver receiver;
  fill_receiver(receiver, kPattern);
  // Decoys in the receiver at the offsets a confused reconstruction might read.
  const std::size_t decoys[4] = {0x00u, 0x04u, 0x08u, 0x70u};
  const Word decoy_id = 0xdb4675ddu;
  for (int index = 0; index < 4; ++index) {
    Word* const slot = word_at(&receiver, decoys[index]);
    *slot = decoy_id;
  }

  configure_callee(kCalleeDefault);
  drive(receiver, pair[1]);

  check(g_callee.key == &pair[1], "I1: the caller's second record is the one used");
  check(flag_at(receiver, kFlag78) == 1u, "I2: its id wrote ITS flag byte");
  check(flag_at(receiver, kFlag7c) == static_cast<std::uint8_t>(kPattern + kFlag7c),
        "I3: the decoy id planted in the receiver selected nothing");
  check(pair[0].field_00 == 0xdb4675ddu && pair[0].field_04 == 0x2e1a75du &&
            pair[0].field_08 == 1u,
        "I4: the neighbouring record is untouched, so nothing was read through it");
}

// J. The id comes from the record's FIRST word. A record whose value word is
// itself a valid key id pins that down: the id arm must follow field_00, and
// field_08 -- also a key id -- must not open an arm of its own.
void case_the_id_is_not_the_value_word() {
  Receiver receiver;
  fill_receiver(receiver, kPattern);
  const PropertyKeyRecord record = make_record(0x15e8afc8u, 0x2e1a75du, 0xb91fba14u);
  configure_callee(kCalleeDefault);
  drive(receiver, record);
  check(flag_at(receiver, kFlag78) == 0u,
        "J1: the value 0xb91fba14 is compared against 1, so the 0x78 flag stores 0");
  check(flag_at(receiver, kFlag7a) == static_cast<std::uint8_t>(kPattern + kFlag7a),
        "J2: and it did not open the 0x7a arm instead");
}

// L. The store is exactly one byte, inside the modeled object, and nothing else in
// the whole probe moves. This is the case that catches a dword store, a
// displacement one off, a write at 0x7d or past the end of the object, and any
// "reset the other flags" behaviour -- in one comparison.
void case_only_one_byte_inside_the_object_ever_changes() {
  struct Expectation {
    Word id;
    std::size_t flag;
  };
  const Expectation table[5] = {
      {0x15e8afc8u, kFlag78}, {0x5a3584a7u, kFlag79}, {0xb91fba14u, kFlag7a},
      {0xd22f5e35u, kFlag7b}, {0xdb4675ddu, kFlag7c},
  };
  for (int entry = 0; entry < 5; ++entry) {
    Receiver receiver;
    fill_receiver(receiver, kPattern);
    Receiver before = receiver;
    const PropertyKeyRecord record = make_record(table[entry].id, 0x2e1a75du, 1u);
    configure_callee(kCalleeDefault);
    drive(receiver, record);
    const Diff diff = diff_receiver(before, receiver);
    check(diff.inside == 1 && diff.first_inside == table[entry].flag,
          "L1: one byte changed, and it is the arm's own displacement");
    check(diff.outside == 0,
          "L2: no other byte of the 0x90-byte probe changed, including the canary "
          "past the modeled object's end");
  }
}

// M. ABI, measured. The terminator is `RET 0x4`, so the callee owns the single
// stack word. ESP is sampled inside a trampoline before the push and after the
// return: the two are equal only if all four bytes were popped. A cdecl
// reconstruction would leave the second sample four bytes lower; a fastcall one
// would additionally not have the record where it expects it.
struct EspSamples {
  std::uint32_t before_push = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_measured(SporepediaOnlineAsset* receiver, const PropertyKeyRecord* key) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&re_00ec3be0));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  // EAX and ECX are in the clobber list, so the compiler cannot have allocated any
  // of the three inputs to them: every "r" operand therefore survives the
  // `movl %[recv], %%ecx` that precedes its use.
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "pushl %[key]\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver), [key] "r"(key)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_push = before;
  samples.after_return = after;
  return samples;
}

void case_the_one_argument_word_is_callee_cleaned() {
  Receiver receiver;
  fill_receiver(receiver, kPattern);
  const PropertyKeyRecord record = make_record(0xdb4675ddu, 0x2e1a75du, 1u);
  configure_callee(kCalleeDefault);

  const EspSamples samples = call_measured(as_asset(receiver), &record);
  check(samples.after_return == samples.before_push,
        "M1: the callee popped its own four bytes (RET 0x4), so ESP is balanced");
  check(g_callee.calls == 1, "M2: the trampoline really reached the body");
  check(flag_at(receiver, kFlag7c) == 1u, "M3: and the body ran to its store");
  check(g_callee.receiver == as_asset(receiver) && g_callee.key == &record,
        "M4: ECX carried the receiver and the stack carried the record pointer");
}

// N. The body never READS the receiver, so its content outside the five bytes it
// writes cannot change what happens. The same key is driven against an all-zero
// receiver and an all-ones one, and against one whose every byte is 1 -- which
// would satisfy any "gate on a receiver flag" reconstruction.
void case_no_receiver_word_gates_the_dispatch() {
  Receiver zeroed;
  std::memset(&zeroed, 0, sizeof zeroed);
  Receiver ones;
  std::memset(&ones, 0xff, sizeof ones);
  Receiver patterned;
  fill_receiver(patterned, kPattern);

  Receiver* const probes[3] = {&zeroed, &ones, &patterned};
  std::uint8_t results[3] = {0xffu, 0xffu, 0xffu};
  for (int index = 0; index < 3; ++index) {
    // Three different ids, one per probe, all with the same value, so the
    // comparison is between three receiver contents and one expected answer each.
    const Word ids[3] = {0x15e8afc8u, 0xd22f5e35u, 0xdb4675ddu};
    const std::size_t flags[3] = {kFlag78, kFlag7b, kFlag7c};
    const PropertyKeyRecord record = make_record(ids[index], 0x2e1a75du, 1u);
    configure_callee(kCalleeDefault);
    drive(*probes[index], record);
    results[index] = flag_at(*probes[index], flags[index]);
  }
  check(results[0] == 1u && results[1] == 1u && results[2] == 1u,
        "N1: an all-zero, an all-one and a patterned receiver all give the same answer");
}

// P. Five calls in a row, one per id: exactly the five bytes move, and the
// receiver ends holding five booleans and nothing else. This is the only case that
// shows the five ids are independent rather than one of them being a duplicate of
// another.
void case_five_calls_move_exactly_five_bytes() {
  Receiver receiver;
  fill_receiver(receiver, kPattern);
  Receiver before = receiver;
  // Driven OUT of flag order on purpose, so a reconstruction that got one arm's
  // destination from its position in the source rather than from the key id fails
  // here even though every other case would pass.
  struct Step {
    Word id;
    Word value;
    std::size_t flag;
    std::uint8_t expected;
  };
  const Step steps[5] = {
      {0xdb4675ddu, 1u, kFlag7c, 1u}, {0x15e8afc8u, 0u, kFlag78, 0u},
      {0x5a3584a7u, 1u, kFlag79, 1u}, {0xd22f5e35u, 1u, kFlag7b, 1u},
      {0xb91fba14u, 0u, kFlag7a, 0u},
  };
  for (int index = 0; index < 5; ++index) {
    const PropertyKeyRecord record =
        make_record(steps[index].id, 0x2e1a75du, steps[index].value);
    configure_callee(kCalleeDefault);
    drive(receiver, record);
    check(g_callee.calls == 1, "P1: one transfer per call, never more");
    check(flag_at(receiver, steps[index].flag) == steps[index].expected,
          "P3: each flag holds the boolean from ITS OWN call");
  }
  const Diff diff = diff_receiver(before, receiver);
  check(diff.inside == 5 && diff.outside == 0, "P2: five bytes changed, all of them flags");
}

// The constants this package states, against the machine's own immediates. Every
// number here is transcribed from the listing quoted at the top of the .cpp, so a
// header that drifted from the bytes is caught without running anything.
void verify_constants() {
  check(kKeyId_15e8afc8 == 0x15e8afc8u, "V1: key id 0x15e8afc8 (CMP at 00ec3bf9)");
  check(kKeyId_5a3584a7 == 0x5a3584a7u, "V2: key id 0x5a3584a7 (CMP at 00ec3bf0)");
  check(kKeyId_b91fba14 == 0xb91fba14u, "V3: key id 0xb91fba14 (CMP at 00ec3c34)");
  check(kKeyId_d22f5e35 == 0xd22f5e35u, "V4: key id 0xd22f5e35 (CMP at 00ec3c3b)");
  check(kKeyId_db4675dd == 0xdb4675ddu, "V5: key id 0xdb4675dd (CMP at 00ec3c42)");
  check(kPivotId_5a3584a7 == 0x5a3584a7u, "V6: the pivot is the same word as key id 2");
  check(kTypeHash == 0x2e1a75du, "V7: the one type hash (CMP at 00ec3c04)");
  check(kFlagDisplacementForId_15e8afc8 == 0x78u, "V8: 0x15e8afc8 -> +0x78");
  check(kFlagDisplacementForId_5a3584a7 == 0x79u, "V9: 0x5a3584a7 -> +0x79");
  check(kFlagDisplacementForId_b91fba14 == 0x7au, "V10: 0xb91fba14 -> +0x7a");
  check(kFlagDisplacementForId_d22f5e35 == 0x7bu, "V11: 0xd22f5e35 -> +0x7b");
  check(kFlagDisplacementForId_db4675dd == 0x7cu, "V12: 0xdb4675dd -> +0x7c");
  check(kRecordIdDisplacement == 0x00u, "V13: the id is the record's word 0");
  check(kRecordTypeDisplacement == 0x04u, "V14: the type hash is the record's word 1");
  check(kRecordValueDisplacement == 0x08u, "V15: the value is the record's word 2");
  check(kFlag78 + 4 == kFlag7c, "V16: the five flags are five CONSECUTIVE bytes");
  check(sizeof(PropertyKeyRecord) == 0x0cu, "V17: the record is three words");
  check(kFlag7c + 1 <= sizeof(SporepediaOnlineAsset),
        "V18: the last byte the body writes is inside the modeled receiver");
}

}  // namespace

}  // namespace openspore::reconstruction::pkg_swarm_w1_00ec3be0

// The cases and their fixtures all live in the package namespace (and its
// anonymous namespace, whose members the directive below reaches too), so that
// the test cannot collide with anything in the reconstruction it is testing.
using namespace openspore::reconstruction::pkg_swarm_w1_00ec3be0;

int main() {
  verify_constants();
  case_each_id_writes_only_its_own_flag();
  case_value_test_is_equality_against_one();
  case_pivot_compare_is_unsigned();
  case_unknown_ids_write_nothing();
  case_type_hash_must_match_exactly();
  case_the_record_is_read_after_the_callee_returns();
  case_the_other_four_flags_are_left_alone();
  case_the_callee_runs_on_every_path();
  case_the_id_is_the_records_own_word();
  case_the_id_is_not_the_value_word();
  case_only_one_byte_inside_the_object_ever_changes();
  case_the_one_argument_word_is_callee_cleaned();
  case_no_receiver_word_gates_the_dispatch();
  case_five_calls_move_exactly_five_bytes();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}


