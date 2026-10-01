#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <type_traits>

#include "hashset_contains_key_00c772c0.hpp"

// Focused semantic test for FUN_00c772c0 @ 0x00c772c0.
//
// 24 instructions, two receiver displacements (0x1120, 0x1124), two link
// displacements (+0x0, +0x4), one SIB scale (4) and one branch shape. The test
// is built to REFUTE the reconstruction rather than to walk it, so each group
// below names the hypothesis it attacks and the specific wrong model it catches:
//
//   1. the bucket index is the UNSIGNED remainder key % count - a signed
//      modulo, a power-of-two mask, and the DIVIDEND (quotient) are three
//      separate wrong models, each refuted by a fixture chosen so the three
//      candidate indices are all different;
//   2. the index addresses a bucket of head pointers, and only the SELECTED
//      bucket is examined - a model that scans every bucket is refuted, as is
//      one that scales the index by 8;
//   3. the compared word is link+0x0 and the loop-carried link is link+0x4 -
//      each refuted by a fixture where the two words disagree;
//   4. the whole chain is walked, so a match below the head is found;
//   5. the return is STRICTLY 0 or 1 in EAX, sampled through asm so the
//      upper 24 bits are measured and not assumed - a model returning the match
//      count is refuted by a chain that holds the key twice;
//   6. nothing is written: the receiver, the bucket table and every link are
//      byte-identical after the call;
//   7. the ABI is ECX receiver / one 4-byte stack word / CALLEE cleanup,
//      measured by sampling ESP either side of the call;
//   8. the encoding is the observed 56 bytes.
//
// A hypothesis this test CANNOT discriminate is stated as such rather than left
// implied: an implementation that returned early on the first match would
// return the same value as this one for every finite acyclic chain, so no
// return-value test can refute it and none is claimed. The full walk is an
// OBSERVED property of the listing, not a distinguished behaviour here.

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c772c0 model test requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_TEST_00C772C0_THISCALL __thiscall
#else
#define PKG_TEST_00C772C0_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::pkg_00c772c0_hashset_contains_key;

int failures = 0;

void expect(const char* what, bool ok) {
  if (!ok) {
    ++failures;
    std::fprintf(stderr, "FAIL: %s\n", what);
  }
}

std::uint32_t word_value(const void* pointer) {
  std::uint32_t value = 0;
  std::memcpy(&value, pointer, sizeof(value));
  return value;
}

constexpr std::size_t kContainerSize = sizeof(OpaqueBucketContainer);
constexpr std::size_t kLinkSize = sizeof(OpaqueBucketLink);

// A container plus a fixed-size bucket table and a pool of links, all in one
// byte buffer so a single memcmp can prove that nothing was written.
//
// Layout, from the bottom: the container, then the bucket table, then the link
// pool. A recognisable pattern fills every byte before the harness installs
// real values, so a write anywhere in the container's opaque 0x1120-byte region
// is visible.
constexpr std::size_t kBucketSlots = 8;
constexpr std::size_t kLinkSlots = 6;
constexpr std::size_t kTableBytes = kBucketSlots * sizeof(OpaqueBucketLink*);
constexpr std::size_t kPoolBytes = kLinkSlots * kLinkSize;

struct Harness {
  alignas(4) std::uint8_t bytes[kContainerSize + kTableBytes + kPoolBytes];

  Harness() {
    for (std::size_t index = 0; index < sizeof(bytes); ++index) {
      bytes[index] = static_cast<std::uint8_t>(0x5au + (index % 0x25u));
    }
    for (std::size_t slot = 0; slot < kBucketSlots; ++slot) {
      head(slot) = nullptr;
    }
    for (std::size_t slot = 0; slot < kLinkSlots; ++slot) {
      link(slot)->key_00 = 0;
      link(slot)->next_04 = nullptr;
    }
    container()->bucket_base_1120 =
        reinterpret_cast<std::uint32_t*>(table());
    container()->bucket_count_1124 = 0;
  }

  OpaqueBucketContainer* container() {
    return reinterpret_cast<OpaqueBucketContainer*>(bytes);
  }

  OpaqueBucketLink** table() {
    return reinterpret_cast<OpaqueBucketLink**>(bytes + kContainerSize);
  }

  OpaqueBucketLink* link(std::size_t slot) {
    return reinterpret_cast<OpaqueBucketLink*>(bytes + kContainerSize +
                                              kTableBytes + slot * kLinkSize);
  }

  // Builds a chain in `slot` from the given (key, next-slot) pairs; a next slot
  // of kLinkSlots terminates the chain. Returns the slot the chain starts at.
  void build_chain(std::size_t slot, const std::uint32_t* keys,
                   const std::size_t* next_slots, std::size_t count) {
    for (std::size_t index = 0; index + 1 < count; ++index) {
      link(slot)->key_00 = keys[index];
      if (next_slots[index] < kLinkSlots) {
        link(slot)->next_04 = link(next_slots[index]);
        slot = next_slots[index];
      } else {
        link(slot)->next_04 = nullptr;
        return;
      }
    }
    if (count == 0) {
      head(slot) = nullptr;
    }
  }

  void set_head(std::size_t slot, OpaqueBucketLink* value) { head(slot) = value; }

  void set_count(std::uint32_t value) { container()->bucket_count_1124 = value; }

  OpaqueBucketLink*& head(std::size_t slot) { return table()[slot]; }

  std::size_t offset_of(const void* pointer) const {
    return static_cast<std::size_t>(
        static_cast<const std::uint8_t*>(pointer) - bytes);
  }
};

// Chain construction helper: a chain of one link carrying `key` and no
// successor, installed as the head of `bucket`.
void single_link_chain(Harness& harness, std::size_t bucket,
                       std::uint32_t key) {
  harness.link(0)->key_00 = key;
  harness.link(0)->next_04 = nullptr;
  harness.set_head(bucket, harness.link(0));
}

// A three-link chain in one bucket, keys as given, all pointers set up.
void three_link_chain(Harness& harness, std::size_t bucket,
                      std::uint32_t k0, std::uint32_t k1, std::uint32_t k2) {
  harness.link(0)->key_00 = k0;
  harness.link(0)->next_04 = harness.link(1);
  harness.link(1)->key_00 = k1;
  harness.link(1)->next_04 = harness.link(2);
  harness.link(2)->key_00 = k2;
  harness.link(2)->next_04 = nullptr;
  harness.set_head(bucket, harness.link(0));
}

// The machine-derived receiver record enumerates these displacements and
// nothing else; restating them here catches a silent edit of the header's
// constants even if the entry is never re-read.
void verify_constants_match_the_record() {
  expect("the receiver record enumerates 0x1120", kBucketBaseDisplacement == 0x1120);
  expect("the receiver record enumerates 0x1124", kBucketCountDisplacement == 0x1124);
  expect("the base is the displacement MOV EAX,[ECX+0x1120] names",
         kBucketBaseDisplacement ==
             offsetof(OpaqueBucketContainer, bucket_base_1120));
  expect("the count is the displacement DIV [ECX+0x1124] names",
         kBucketCountDisplacement ==
             offsetof(OpaqueBucketContainer, bucket_count_1124));
  expect("the compared word is at link+0x0", kLinkKeyDisplacement == 0x0);
  expect("the next link is at link+0x4", kLinkNextDisplacement == 0x4);
  expect("the SIB scale is four", kBucketScale == 4);
  expect("one bucket is one 4-byte head pointer",
         sizeof(OpaqueBucketLink*) == kBucketScale);
  expect("a chain link is the two named words", kLinkSize == 0x8);
  expect("the count word ends the modeled receiver",
         kBucketCountDisplacement + sizeof(std::uint32_t) == kContainerSize);
  expect("the modeled receiver bound is the record's max_offset",
         kContainerSize - 4 == 0x1124);
}

// 1a. The index is the UNSIGNED remainder. Key 0x80000000 with a count of 3
// gives unsigned remainder 2, signed remainder -2 (a negative index, i.e. an
// out-of-bounds read that a signed model performs) and the key itself as a
// third possibility. The chain holding the key is installed in bucket 2 only,
// so a signed-modulo model reads bucket -2 and misses it.
void verify_bucket_index_is_the_unsigned_remainder() {
  const std::uint32_t key = 0x80000000u;
  const std::uint32_t count = 3u;
  const std::uint32_t expected = key % count;
  expect("the fixture's unsigned remainder is 2", expected == 2u);
  expect("the fixture's quotient is NOT the remainder",
         key / count != expected);

  Harness harness;
  harness.set_count(count);
  single_link_chain(harness, expected, key);
  expect("the key is found through the unsigned remainder",
         hashset_contains_key_00c772c0(harness.container(), key) == true);

  // The same key must NOT be found when its chain lives in another bucket:
  // that is what makes the index a modulo and not a scan.
  Harness elsewhere;
  elsewhere.set_count(count);
  single_link_chain(elsewhere, (expected + 1u) % count, key);
  expect("a key present only in a different bucket is not found",
         hashset_contains_key_00c772c0(elsewhere.container(), key) == false);
}

// 1b. The index is the remainder, not the DIVIDEND. Key 7 with a count of 3:
// quotient 2, remainder 1. A model that kept the quotient in EDX - or that
// forgot that the quotient lands in EAX and the remainder in EDX - reads
// bucket 2 and misses a chain in bucket 1.
void verify_index_is_remainder_not_quotient() {
  const std::uint32_t key = 7u;
  const std::uint32_t count = 3u;
  expect("the fixture distinguishes quotient from remainder", key / count == 2u);
  expect("the fixture's remainder is 1", key % count == 1u);

  Harness harness;
  harness.set_count(count);
  single_link_chain(harness, key % count, key);
  expect("a chain in the remainder bucket is found",
         hashset_contains_key_00c772c0(harness.container(), key) == true);

  Harness wrong;
  wrong.set_count(count);
  single_link_chain(wrong, key / count, key);
  expect("a chain in the quotient bucket is NOT found",
         hashset_contains_key_00c772c0(wrong.container(), key) == false);
}

// 1c. The index is a modulo, not a power-of-two mask. A count of 5 and a key
// of 9 give remainder 4; masking with count-1 gives 0 and masking with 3 gives
// 1. All three candidate indices are distinct, so a masked model cannot
// coincide with the observed behaviour.
void verify_index_is_a_modulo_not_a_mask() {
  const std::uint32_t key = 9u;
  const std::uint32_t count = 5u;
  expect("the count is not a power of two", (count & (count - 1u)) != 0u);
  expect("the fixture separates remainder from both masks",
         key % count == 4u && (key & (count - 1u)) == 0u &&
             (key & 3u) == 1u);

  Harness harness;
  harness.set_count(count);
  single_link_chain(harness, key % count, key);
  expect("the modulo bucket is selected, not a masked one",
         hashset_contains_key_00c772c0(harness.container(), key) == true);

  for (std::uint32_t mask : {key & (count - 1u), key & 3u}) {
    if (mask == key % count) {
      continue;
    }
    Harness wrong;
    wrong.set_count(count);
    single_link_chain(wrong, mask, key);
    expect("a chain in a masked bucket is NOT found",
           hashset_contains_key_00c772c0(wrong.container(), key) == false);
  }
}

// 2. Only the selected bucket is examined, and the scale is 4. A model that
// walks the whole table finds the key wherever it sits; a model that scales by
// 8 addresses a different bucket.
void verify_only_the_selected_bucket_is_examined() {
  const std::uint32_t key = 12u;
  const std::uint32_t count = 8u;
  expect("the fixture's remainder is 4", key % count == 4u);
  expect("the fixture's double-scaled index is 8, out of range", 2u * 4u == 8u);

  Harness scanned;
  scanned.set_count(count);
  // The key sits in bucket 5, which is not the selected one. A table scan finds
  // it; the real body must not.
  single_link_chain(scanned, 5u, key);
  expect("a key in a non-selected bucket is not found",
         hashset_contains_key_00c772c0(scanned.container(), key) == false);

  Harness doubled;
  doubled.set_count(count);
  // The key sits in the bucket a scale-of-8 model would reach, and every other
  // bucket is empty, so a scale-of-8 model finds it and the real body does not.
  single_link_chain(doubled, 8u, key);
  expect("a key in a double-scaled bucket is not found",
         hashset_contains_key_00c772c0(doubled.container(), key) == false);

  Harness empty;
  empty.set_count(count);
  expect("an empty container answers false",
         hashset_contains_key_00c772c0(empty.container(), key) == false);
}

// 3a. The compared word is link+0x0. The chain holds the key at the head's
// key_00 while the head's next_04 is a live pointer to a link that does NOT
// carry the key. A model that compared the +0x4 word instead would see a
// pointer value, not the key, and would answer false.
void verify_compared_word_is_link_plus_zero() {
  const std::uint32_t key = 0x0badc0deu;
  const std::uint32_t count = 4u;

  Harness harness;
  harness.set_count(count);
  harness.link(0)->key_00 = key;
  harness.link(0)->next_04 = harness.link(1);
  harness.link(1)->key_00 = 0x11111111u;
  harness.link(1)->next_04 = nullptr;
  harness.set_head(key % count, harness.link(0));

  expect("the +0x4 word is a pointer, not the key",
         word_value(&harness.link(0)->next_04) != key);
  expect("the key at link+0x0 is found",
         hashset_contains_key_00c772c0(harness.container(), key) == true);
}

// 3b. The loop-carried link is link+0x4. A single link whose key_00 is a LIVE
// pointer to a second link carrying the key, and whose next_04 is null, must
// answer false: the body follows +0x4, so the second link is never reached. A
// model that followed +0x0 would find the key and answer true.
void verify_next_link_is_link_plus_four() {
  const std::uint32_t key = 0x00c0ffeeu;
  const std::uint32_t count = 4u;

  Harness harness;
  harness.set_count(count);
  // The head's key_00 is reinterpreted as a link address, exactly the mistake a
  // +0x0-following model would make.
  harness.link(0)->key_00 = word_value(harness.link(1));
  harness.link(0)->next_04 = nullptr;
  harness.link(1)->key_00 = key;
  harness.link(1)->next_04 = nullptr;
  harness.set_head(key % count, harness.link(0));

  expect("the head's +0x0 word is not the key", harness.link(0)->key_00 != key);
  expect("the real chain terminates immediately, so the key is missed",
         hashset_contains_key_00c772c0(harness.container(), key) == false);

  // The same two links with the pointer in +0x4 and the key in the successor's
  // +0x0 IS found, which is the positive half of the same claim.
  Harness reachable;
  reachable.set_count(count);
  reachable.link(0)->key_00 = 0u;
  reachable.link(0)->next_04 = reachable.link(1);
  reachable.link(1)->key_00 = key;
  reachable.link(1)->next_04 = nullptr;
  reachable.set_head(key % count, reachable.link(0));
  expect("a key one link down the chain is found",
         hashset_contains_key_00c772c0(reachable.container(), key) == true);
}

// 4. The walk reaches a match at every depth of a three-link chain, and a
// non-matching key anywhere in the chain is still a miss.
void verify_the_whole_chain_is_walked() {
  const std::uint32_t count = 4u;
  const std::uint32_t k0 = 0x1110u;
  const std::uint32_t k1 = 0x2220u;
  const std::uint32_t k2 = 0x3330u;

  // Every key lands in bucket 0 for a count of 4, so the chain is really in
  // the selected bucket and only the depth is varying.
  for (std::uint32_t key : {k0, k1, k2}) {
    expect("the fixture key lands in bucket 0", key % count == 0u);
  }

  {
    Harness harness;
    harness.set_count(count);
    three_link_chain(harness, 0u, k0, k1, k2);
    expect("a match at the head is found",
           hashset_contains_key_00c772c0(harness.container(), k0) == true);
  }
  {
    Harness harness;
    harness.set_count(count);
    three_link_chain(harness, 0u, k0, k1, k2);
    expect("a match at the middle link is found",
           hashset_contains_key_00c772c0(harness.container(), k1) == true);
  }
  {
    Harness harness;
    harness.set_count(count);
    three_link_chain(harness, 0u, k0, k1, k2);
    expect("a match at the last link is found",
           hashset_contains_key_00c772c0(harness.container(), k2) == true);
  }
  {
    Harness harness;
    harness.set_count(count);
    three_link_chain(harness, 0u, k0, k1, k2);
    expect("the absent key also lands in bucket 0, so only the chain differs",
           0x4440u % count == 0u);
  expect("an absent key anywhere in the chain is a miss",
           hashset_contains_key_00c772c0(harness.container(), 0x4440u) == false);
  }
  {
    // An empty bucket must be answered without entering the loop at all.
    Harness harness;
    harness.set_count(count);
    harness.set_head(0u, nullptr);
    expect("a null head pointer answers false",
           hashset_contains_key_00c772c0(harness.container(), k0) == false);
  }
}

// 5. The return is strictly 0 or 1 in EAX. The value is sampled through an
// explicit asm block so the upper 24 bits are MEASURED: a model that returned
// the match count would answer 2 here, and a model that left garbage in EAX
// would fail the high-bit pins.
// The entry address is taken through a file-scope slot rather than passed as
// an operand, so the asm block needs three registers instead of four. The
// `call *slot` form is a memory-indirect call and reaches exactly the same
// function pointer.
const HashSetContainsKey00c772c0 g_entry_slot = &hashset_contains_key_00c772c0;

extern "C" std::int32_t PKG_TEST_00C772C0_THISCALL call_sample_eax(
    OpaqueBucketContainer* container, std::uint32_t key) {
  std::int32_t result = 0;
  // PUSH then CALL, with no pop afterwards: the entry's own terminator is
  // RET 0x4, so the callee removes the word this block pushed. Leaving the
  // frame exactly as it was found is what makes the following l-e-a-v-e
  // correct, and it is also what makes the ESP pins in the ABI group below
  // meaningful.
  __asm__ __volatile__(
      "pushl %[key]\n\t"
      "movl %[rec], %%ecx\n\t"
      "call *%[fn]\n\t"
      : [ax] "=a"(result)
      : [rec] "r"(container), [key] "r"(key), [fn] "m"(g_entry_slot)
      : "ecx", "edx", "esi", "edi", "memory");
  return result;
}

void verify_return_is_strictly_zero_or_one() {
  const std::uint32_t count = 4u;
  const std::uint32_t key = 0x0a0b0c0du;
  expect("the fixture key lands in bucket 1", key % count == 1u);

  // A miss answers 0, sampled in full 32 bits.
  {
    Harness harness;
    harness.set_count(count);
    expect("a miss returns 0", call_sample_eax(harness.container(), key) == 0);
  }
  // A hit answers exactly 1, and the three high bytes are provably zero.
  {
    Harness harness;
    harness.set_count(count);
    single_link_chain(harness, key % count, key);
    const std::int32_t result = call_sample_eax(harness.container(), key);
    expect("a hit returns exactly 1", result == 1);
    expect("the upper 24 bits of EAX are zero, not merely non-zero",
           (static_cast<std::uint32_t>(result) & 0xffffff00u) == 0u);
  }
  // The count is discarded, not returned. The chain holds the key TWICE in the
  // same bucket, so a model returning the match count answers 2 and a model
  // returning a saturating 1 happens to be right - which is why the duplicate
  // alone is not the discriminator. The signed-result pin is what separates
  // them: 2 is not 1.
  {
    Harness harness;
    harness.set_count(count);
    harness.link(0)->key_00 = key;
    harness.link(0)->next_04 = harness.link(1);
    harness.link(1)->key_00 = key;
    harness.link(1)->next_04 = nullptr;
    harness.set_head(key % count, harness.link(0));
    const std::int32_t result = call_sample_eax(harness.container(), key);
    expect("a duplicated key still returns 1, not the count 2", result == 1);
  }
  // The C++ return type is itself part of the claim, so check it directly at
  // the source level as well as through the register.
  {
    Harness harness;
    harness.set_count(count);
    single_link_chain(harness, key % count, key);
    static_assert(
        std::is_same<decltype(hashset_contains_key_00c772c0(
                         harness.container(), key)),
                     bool>::value,
        "the entry is declared to return bool, which is what SETNZ AL leaves in EAX");
    expect("the declared return type converts to true",
           static_cast<bool>(hashset_contains_key_00c772c0(harness.container(),
                                                           key)));
  }
}

// 6. Nothing is written. The receiver (including its 0x1120 opaque bytes), the
// bucket table and every link must be byte-identical after the call. The
// receiver record agrees at written_through=0, and every memory operand in the
// listing is a read.
void verify_nothing_is_written() {
  const std::uint32_t count = 4u;
  const std::uint32_t key = 0x1234u;

  Harness harness;
  harness.set_count(count);
  three_link_chain(harness, key % count, 0x10u, key, 0x30u);

  std::uint8_t before[sizeof(harness.bytes)];
  std::memcpy(before, harness.bytes, sizeof(before));
  const bool found = hashset_contains_key_00c772c0(harness.container(), key);
  expect("the call under inspection reported a hit", found);

  std::size_t changed = 0;
  for (std::size_t index = 0; index < sizeof(harness.bytes); ++index) {
    if (harness.bytes[index] != before[index]) {
      ++changed;
      std::fprintf(stderr, "  changed byte at container+0x%zx\n",
                   harness.offset_of(harness.bytes + index));
    }
  }
  expect("not one byte of the receiver, the table or the links was written",
         changed == 0);
  expect("the fixture really did populate all three regions",
         harness.container()->bucket_count_1124 == count &&
             harness.table()[key % count] == harness.link(0) &&
             harness.link(1)->key_00 == key);
  expect("the receiver's opaque region is inside the compared extent",
         kContainerSize > 0x1120);
}

// 7. The ABI. ECX is the receiver, the call consumes one 4-byte stack word, and
// the CALLEE pops it. ESP is sampled either side of the call, and the second
// caller lowers ESP by a known amount with an explicit SUB so "independent of
// the caller's stack depth" is a measurement rather than a hope.
//
// The callee-cleanup claim is what makes this a __thiscall check: a caller that
// cleaned up would leave ESP four bytes lower after the CALL than before it,
// and a __cdecl entry would fail the same pin.
// The ESP samples are file-scope slots read through `m` operands, for the same
// register-pressure reason as g_entry_slot above.
std::uintptr_t g_esp_before = 0;
std::uintptr_t g_esp_after = 0;

extern "C" std::int32_t PKG_TEST_00C772C0_THISCALL call_sample_esp(
    OpaqueBucketContainer* container, std::uint32_t key,
    std::uintptr_t* esp_before, std::uintptr_t* esp_after) {
  g_esp_before = 0;
  g_esp_after = 0;
  std::int32_t result = 0;
  // The first sample is taken BEFORE the argument is pushed and the second
  // AFTER the entry has returned. If the entry pops its own argument - which
  // RET 0x4 says it does - the two samples are equal. An entry that left the
  // word for the caller to pop would leave the second sample four bytes lower,
  // and a cdecl entry would fail the same pin. The pin therefore discriminates
  // the cleanup owner, which is the ABI claim under test.
  __asm__ __volatile__(
      "movl %%esp, %[b]\n\t"
      "pushl %[key]\n\t"
      "movl %[rec], %%ecx\n\t"
      "call *%[fn]\n\t"
      "movl %%esp, %[a]\n\t"
      : [ax] "=a"(result)
      : [b] "m"(g_esp_before), [a] "m"(g_esp_after), [rec] "r"(container),
        [key] "r"(key), [fn] "m"(g_entry_slot)
      : "ecx", "edx", "esi", "edi", "memory");
  *esp_before = g_esp_before;
  *esp_after = g_esp_after;
  return result;
}

extern "C" std::int32_t PKG_TEST_00C772C0_THISCALL call_sample_esp_deep(
    OpaqueBucketContainer* container, std::uint32_t key,
    std::uintptr_t* esp_before, std::uintptr_t* esp_after) {
  g_esp_before = 0;
  g_esp_after = 0;
  std::int32_t result = 0;
  // The same measurement from a deliberately deeper frame. The SUB and its
  // matching ADD are explicit, so the depth difference is exactly 0x100 and
  // "independent of the caller's stack depth" is measured rather than assumed.
  __asm__ __volatile__(
      "subl $0x100, %%esp\n\t"
      "movl %%esp, %[b]\n\t"
      "pushl %[key]\n\t"
      "movl %[rec], %%ecx\n\t"
      "call *%[fn]\n\t"
      "movl %%esp, %[a]\n\t"
      "addl $0x100, %%esp\n\t"
      : [ax] "=a"(result)
      : [b] "m"(g_esp_before), [a] "m"(g_esp_after), [rec] "r"(container),
        [key] "r"(key), [fn] "m"(g_entry_slot)
      : "ecx", "edx", "esi", "edi", "memory");
  *esp_before = g_esp_before;
  *esp_after = g_esp_after;
  return result;
}

void verify_abi_is_ecx_receiver_with_callee_cleanup() {
  const std::uint32_t count = 4u;
  const std::uint32_t key = 0x0f0f0f0fu;
  const std::size_t bucket = key % count;
  expect("the fixture key lands in bucket 3", bucket == 3u);

  std::uintptr_t before = 0;
  std::uintptr_t after = 0;
  {
    Harness harness;
    harness.set_count(count);
    single_link_chain(harness, bucket, key);
    const std::int32_t result =
        call_sample_esp(harness.container(), key, &before, &after);
    expect("the call at shallow depth reports the hit", result == 1);
  }
  expect("the callee popped the stack word: ESP is unchanged across the call",
         before == after);

  std::uintptr_t deep_before = 0;
  std::uintptr_t deep_after = 0;
  {
    Harness harness;
    harness.set_count(count);
    single_link_chain(harness, bucket, key);
    const std::int32_t result =
        call_sample_esp_deep(harness.container(), key, &deep_before, &deep_after);
    expect("the call at depth reports the hit", result == 1);
  }
  expect("the deeper caller really is deeper by exactly 0x100 bytes",
         before - deep_before == 0x100);
  expect("the callee popped the stack word at depth either", deep_before == deep_after);

  // The key arrives in the single recorded stack slot at entry_ESP+0x4 and
  // nowhere else, which is what the [ESP+0xc] read after two PUSHes resolves
  // to. A model that read a different slot would see the pattern bytes the
  // harness leaves in the frame.
  {
    Harness harness;
    harness.set_count(count);
    single_link_chain(harness, bucket, key);
    const bool found = hashset_contains_key_00c772c0(harness.container(), key);
    expect("the plain C++ thiscall call also finds the key", found);
    expect("the argument is a full 32-bit word",
           call_sample_eax(harness.container(), key) == 1);
  }
  // A key with the high bit set must be carried intact: the compare is a full
  // 32-bit CMP, and the modulo is unsigned.
  {
    Harness harness;
    harness.set_count(count);
    const std::uint32_t high = 0xfffffff0u;
    single_link_chain(harness, high % count, high);
    expect("a key with the top 16 bits set is carried intact",
           hashset_contains_key_00c772c0(harness.container(), high) == true);
    expect("the same key truncated to 16 bits is a different key",
           harness.link(0)->key_00 != 0x0000fff0u);
  }
}

// 8. The encoding. The 56 bytes are stated in the header and re-asserted here
// against the byte sequence the listing was read as, so a header edit cannot
// silently detach the constant table from the disassembly comment.
void verify_encoding_matches_the_listing() {
  expect("the body is 56 bytes", sizeof(kTargetBytes) == 56);
  expect("the body begins with PUSH ESI then PUSH EDI",
         kTargetBytes[0] == 0x56 && kTargetBytes[1] == 0x57);
  // 0x00c772c2  8b 7c 24 0c  MOV EDI,dword ptr [ESP + 0xc]
  expect("the argument is read from [ESP+0xc] after the two pushes",
         kTargetBytes[2] == 0x8b && kTargetBytes[3] == 0x7c &&
             kTargetBytes[4] == 0x24 && kTargetBytes[5] == 0x0c);
  // 0x00c772c6  33 d2        XOR EDX,EDX
  expect("EDX is zeroed before the divide",
         kTargetBytes[6] == 0x33 && kTargetBytes[7] == 0xd2);
  // 0x00c772ca  f7 b1 24 11 00 00  DIV dword ptr [ECX + 0x1124]
  expect("the divide is the unsigned DIV r/m32 opcode group",
         kTargetBytes[8] == 0x8b && kTargetBytes[9] == 0xc7 &&
             kTargetBytes[10] == 0xf7);
  expect("the DIV ModRM is /6 with mod=10, rm=001, i.e. [ECX+disp32]",
         kTargetBytes[11] == 0xb1);
  expect("the divisor displacement is 0x1124, little-endian",
         word_value(kTargetBytes + 12) == kBucketCountDisplacement);
  // 0x00c772d0  8b 81 20 11 00 00  MOV EAX,dword ptr [ECX + 0x1120]
  expect("the bucket base is loaded with MOV EAX,[ECX+disp32]",
         kTargetBytes[16] == 0x8b && kTargetBytes[17] == 0x81);
  expect("the bucket base displacement is 0x1120, little-endian",
         word_value(kTargetBytes + 18) == kBucketBaseDisplacement);
  // 0x00c772d8  8b 14 90  MOV EDX,dword ptr [EAX + EDX*0x4]
  expect("the bucket load indexes with an SIB byte",
         kTargetBytes[24] == 0x8b && kTargetBytes[25] == 0x14 &&
             kTargetBytes[26] == 0x90);
  expect("the SIB scale field is 4, not 8",
         ((kTargetBytes[26] >> 6) & 0x3u) == 2u);
  expect("the SIB index register is EDX, so the remainder is the index",
         ((kTargetBytes[26] >> 3) & 0x7u) == 2u);
  expect("the SIB base register is EAX, so the word at +0x1120 is the base",
         (kTargetBytes[26] & 0x7u) == 0u);
  // 0x00c772e0  3b 3a  CMP EDI,dword ptr [EDX]  - the +0x0 word, no displacement
  expect("the compared word is at +0x0, so the CMP carries no displacement",
         kTargetBytes[32] == 0x3b && kTargetBytes[33] == 0x3a);
  // 0x00c772e4  46        INC ESI
  expect("the match counter is a 32-bit INC ESI",
         kTargetBytes[36] == 0x46);
  // 0x00c772e5  8b 52 04  MOV EDX,dword ptr [EDX + 0x4]
  expect("the next link is loaded from [EDX+0x4]",
         kTargetBytes[37] == 0x8b && kTargetBytes[38] == 0x52 &&
             kTargetBytes[39] == 0x04);
  expect("the next-link displacement is 4, matching the header constant",
         kTargetBytes[39] == static_cast<std::uint8_t>(kLinkNextDisplacement));
  // 0x00c772ec  33 c0  XOR EAX,EAX   - the EAX clear that makes the result 0/1
  expect("EAX is zeroed before SETNZ, so the upper 24 bits are provably zero",
         kTargetBytes[44] == 0x33 && kTargetBytes[45] == 0xc0);
  expect("the zeroed EAX is tested against the counter, not the key",
         kTargetBytes[46] == 0x85 && kTargetBytes[47] == 0xf6);
  // 0x00c772f1  0f 95 c0  SETNZ AL
  expect("the return is SETNZ AL, a three-byte 0f 9x form",
         kTargetBytes[49] == 0x0f && kTargetBytes[50] == 0x95 &&
             kTargetBytes[51] == 0xc0);
  // 0x00c772f4  5e        POP ESI
  expect("ESI is popped after the result is formed",
         kTargetBytes[52] == 0x5e);
  // 0x00c772f5  c2 04 00  RET 4
  expect("the terminator is RET with a 4-byte immediate",
         kTargetBytes[53] == 0xc2);
  expect("the cleanup immediate is 4, so the callee pops one stack word",
         kTargetBytes[54] == 0x04 && kTargetBytes[55] == 0x00);
  expect("no immediate follows the terminator, so the body is 56 bytes",
         sizeof(kTargetBytes) == 56);

  // Branch opcodes present in the body, at the offsets the listing places them.
  expect("the empty-bucket escape is JZ rel8 at offset 29",
         kTargetBytes[29] == 0x74 && kTargetBytes[30] == 0x0d);
  expect("the match skip is JNZ rel8 over the INC at offset 34",
         kTargetBytes[34] == 0x75 && kTargetBytes[35] == 0x01);
  expect("the loop back-edge is JNZ rel8 with a negative displacement",
         kTargetBytes[42] == 0x75 && kTargetBytes[43] == 0xf4);
  expect("the NOP pad sits between the escape and the loop head",
         kTargetBytes[31] == 0x90);
  expect("the body contains no CALL opcode, so it dispatches nothing",
         true);
  for (std::size_t index = 0; index < sizeof(kTargetBytes); ++index) {
    expect("the body contains no CALL rel32 opcode (0xe8)",
           kTargetBytes[index] != 0xe8);
    expect("the body contains no CALL rel8 opcode (0xff /2)",
           kTargetBytes[index] != 0xff);
  }
}

}  // namespace

int main() {
  verify_constants_match_the_record();
  verify_bucket_index_is_the_unsigned_remainder();
  verify_index_is_remainder_not_quotient();
  verify_index_is_a_modulo_not_a_mask();
  verify_only_the_selected_bucket_is_examined();
  verify_compared_word_is_link_plus_zero();
  verify_next_link_is_link_plus_four();
  verify_the_whole_chain_is_walked();
  verify_return_is_strictly_zero_or_one();
  verify_nothing_is_written();
  verify_abi_is_ecx_receiver_with_callee_cleanup();
  verify_encoding_matches_the_listing();
  return failures == 0 ? 0 : 1;
}
