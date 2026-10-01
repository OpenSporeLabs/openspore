// Model test for 0x00c77bf0 (SporeApp.exe 3.1.0.22).
//
// The machine body is thirty-nine instructions, ninety-five bytes:
//
//     0x00c77bf0  83 ec 10              SUB ESP,0x10
//     0x00c77bf3  53 56 57              PUSH EBX / PUSH ESI / PUSH EDI
//     0x00c77bf6  8b 7c 24 20           MOV EDI,dword ptr [ESP+0x20]
//     0x00c77bfa  81 c1 1c 11 00 00     ADD ECX,0x111c
//     0x00c77c00  33 d2                 XOR EDX,EDX
//     0x00c77c02  8b f8                 MOV EAX,EDI
//     0x00c77c04  f7 71 08              DIV dword ptr [ECX+0x8]
//     0x00c77c07  8b 41 04              MOV EAX,dword ptr [ECX+0x4]
//     0x00c77c0a  33 f6                 XOR ESI,ESI
//     0x00c77c0c  8b 14 90              MOV EDX,dword ptr [EAX+EDX*0x4]
//     0x00c77c0f  85 d2 74 0c           TEST EDX,EDX / JZ 0x00c77c1f
//     0x00c77c13  3b 3a 75 01 46        CMP EDI,[EDX] / JNZ / INC ESI
//     0x00c77c18  8b 52 04              MOV EDX,dword ptr [EDX+0x4]
//     0x00c77c1b  85 d2 75 f4           TEST EDX,EDX / JNZ 0x00c77c13
//     0x00c77c1f  85 f6 0f 95 c3        TEST ESI,ESI / SETNZ BL
//     0x00c77c24  84 db 75 1c           TEST BL,BL / JNZ 0x00c77c44
//     0x00c77c28  88 5c 24 20           MOV byte ptr [ESP+0x20],BL
//     0x00c77c2c  8b 54 24 20 52        MOV EDX,[ESP+0x20] / PUSH EDX
//     0x00c77c31  8d 44 24 10 50        LEA EAX,[ESP+0x10] / PUSH EAX
//     0x00c77c36  8d 54 24 18 52        LEA EDX,[ESP+0x18] / PUSH EDX
//     0x00c77c3b  89 7c 24 18           MOV dword ptr [ESP+0x18],EDI
//     0x00c77c3f  e8 ac e1 16 00        CALL 0x00de5df0
//     0x00c77c44  5f 5e 8a c3 5b        POP EDI / POP ESI / MOV AL,BL / POP EBX
//     0x00c77c49  83 c4 10              ADD ESP,0x10
//     0x00c77c4c  c2 04 00              RET 0x4
//
// so the whole of the observable contract is: hash the key with an unsigned
// remainder into one bucket of a chain table held by the receiver, count every
// node of that chain whose key matches, hand the key to 0x00de5df0 exactly when
// the count came out zero, and answer "was it already there" in AL.
//
// LAYERING, because a body this small has little to test and the danger is that
// the test ends up agreeing with itself:
//
//   1. kTargetBytes in the header is the IMAGE, transcribed. The G cases assert
//      it against literals and DECODE the bias, the two displacements, the SIB
//      scale, the node offsets, the store width and the rel32 out of it, so the
//      transcription is under test and the constants cannot drift from the
//      machine. The reconstruction never reads it.
//   2. bucket_membership_insert_00c77bf0() in the .cpp is the code under test.
//      The behavioural cases drive it through its own declaration, so a defect
//      in it cannot be papered over by the transcription.
//   3. What a value comparison cannot show is said so rather than worked around.
//      The stack facts -- that the entry's terminator removes one word of its
//      own, and that the three words pushed in front of the single call come
//      back -- are asserted from the transcribed bytes and from the entry's
//      declared prototype, and the terminator is attacked by mutating those two
//      things. An earlier revision of this file MEASURED the entry's stack
//      effect through a hand-written trampoline with five calibration rungs.
//      That was removed: the measurement needs a stack the caller owns and a
//      callee whose cleanup is the thing under test, and every arrangement of
//      that either trusts what it measures or reintroduces the frame discipline
//      it needs. See the F case for what replaced it and why.
//
// The cases are written to REFUTE a plausible wrong reconstruction rather than
// to walk a right one:
//
//   A  the bucket index is the key's UNSIGNED REMAINDER modulo the dword at
//      +0x1124 -- separated from the quotient, from a power-of-two mask, and
//      from a byte-stride table, with bucket counts deliberately chosen so those
//      three readings disagree somewhere in the set;
//   B  the bucket array is the dword at +0x1120, and the two receiver words are
//      not swapped;
//   C  the chain is walked to its end, following the LINK word at +4 and
//      comparing the KEY word at +0;
//   D  the insert happens on a miss and only on a miss, exactly once;
//   E  the three arguments: the value slot carries the key, the third argument
//      is the key with its low byte cleared (NOT a literal zero -- that is
//      Ghidra's rendering, and it is wrong for every key whose low byte is
//      set), and the two pointers are the two adjacent locals, four bytes apart;
//   F  the entry's stack effect, pinned by the transcribed terminator bytes and
//      by its declared prototype, with the gap that leaves stated;
//   G  the machine facts the whole package rests on;
//   H  the entry writes nothing: every word of the modelled receiver image,
//      including both fields and the guard band above them, keeps its value.
//
// NOT claimed by this test, on purpose: that the walk must continue past the
// first match. Stopping at the first match and counting every match answer
// "was it there at least once" identically, so the two are indistinguishable at
// this boundary and no case pretends otherwise.
//
// The mutants below are bodies that are wrong in exactly one way each. Each is
// driven through the SAME battery the reconstruction is graded by, and each is
// REQUIRED to be refuted: a battery with no power to reject a known-wrong body
// cannot certify the right one.

#if !defined(__i386__) && !defined(_M_IX86)
#error "0x00c77bf0 model test requires an x86-32 target"
#endif

#include "bucket_membership_insert_00c77bf0.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <initializer_list>
#include <type_traits>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace openspore::reconstruction::pkg_00c77bf0_bucket_membership {
namespace model {

using Word = std::uint32_t;

// `std::exit(1)`, not `std::abort()`. The distinction is load-bearing for the
// mutation harness, which reads the exit code to tell the three refutation
// mechanisms apart: exit 1 is the battery rejecting a body on a value, a
// compile failure is a static_assert refusing to build it, and a signal is a
// body that faulted. abort() would report the first two as a fault too, and the
// harness would lose the ability to say which mechanism caught what.
void check(bool condition, const char* what = "assertion") {
  if (!condition) {
    std::fprintf(stderr, "0x00c77bf0: FAILED -- %s\n", what);
    std::fflush(stderr);
    std::exit(1);
  }
}

Word pointer_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The battery is driven through one signature so no mutant is graded by a laxer
// checker than the reconstruction: receiver in ECX, one word on the stack, a
// boolean out.
using Probe = bool(PKG_00C77BF0_CALL*)(BucketTable*, Word);

bool PKG_00C77BF0_CALL real_entry(BucketTable* self, Word key) {
  return bucket_membership_insert_00c77bf0(self, key);
}

// ---------------------------------------------------------------------------
// The call channel.
// ---------------------------------------------------------------------------

// What one probe call yields: the flag it returned, how many times it reached
// 0x00de5df0, and the arguments it handed over on the first of those. Taken
// together AFTER the call rather than read out of the globals directly, so a
// probe that reached the callee more than once, or that recorded something the
// reconstruction never asked for, cannot hide behind a later read of the same
// global.
struct EspSamples {
  bool present;
  std::size_t insert_depth;
  InsertTraceEntry trace;
};

// The one channel every probe is driven through. A plain direct C++ call, so
// there is no hand-written assembly between the battery and the reconstruction
// and no shim whose own stack discipline could be mistaken for the entry's.
//
// What this channel CANNOT show is spelled out rather than worked around: it
// says nothing about how many bytes the entry's terminator removes. A C++
// caller has no way to observe that -- the frame is simply restored -- so the
// `ret 4` fact is pinned where it can be, in the transcribed bytes and in the
// entry's declared prototype, and the terminator is attacked by mutating those
// bytes and that prototype instead of by measuring ESP. See the F case.
EspSamples call_probe(Probe probe, BucketTable* receiver, Word key) {
  EspSamples samples;
  samples.present = probe(receiver, key);
  samples.insert_depth = g_insert_depth;
  if (g_insert_depth == 1u) {
    samples.trace = g_insert_trace[0];
  } else {
    samples.trace.container = 0u;
    samples.trace.value = 0u;
    samples.trace.context = 0u;
    samples.trace.value_at = 0u;
  }
  return samples;
}

// ---------------------------------------------------------------------------
// The modelled image, the bucket array and the node pool.
//
// The bucket array and the node pool are held as RAW WORDS and raw node
// addresses on purpose: the machine loads a bucket as a dword and follows a link
// as a dword, so nothing here may hand the entry a typed container for free.
// ---------------------------------------------------------------------------

constexpr std::size_t kBucketSlots = 8;
Word g_bucket_slots[kBucketSlots];

// A second array, so a case can repoint the receiver's array field at something
// distinguishable that is still a valid input.
Word g_bucket_slots_b[kBucketSlots];

constexpr std::size_t kNodePool = 32;
BucketNode g_node_pool[kNodePool];
std::size_t g_node_used;

BucketTable* receiver_of() {
  return reinterpret_cast<BucketTable*>(&g_bucket_table_image.words[0]);
}

std::uint8_t* image_as_bytes() { return image_bytes(); }

Word node_word(Word link, std::size_t displacement) {
  return word_at(
      reinterpret_cast<const std::uint8_t*>(static_cast<std::uintptr_t>(link)),
      displacement);
}

// Allocates a node whose link word is `next`, and returns its address as the
// raw word the entry will load. Nodes are bump-allocated and never reused
// within a scene, so a stale address can never be mistaken for a fresh one.
Word new_node(Word key, Word next) {
  const std::size_t index = g_node_used++;
  g_node_pool[index].key = key;
  g_node_pool[index].next =
      reinterpret_cast<BucketNode*>(static_cast<std::uintptr_t>(next));
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_node_pool[index]));
}

// Builds a chain in the ORDER GIVEN, head first, and returns the head's raw
// word. So chain({a, b}) is a node carrying a whose link word points at the
// node carrying b -- the order the machine's walk visits them, and the order a
// scene's name means. A zero-length chain yields a null head, which is the
// terminator the entry's `TEST EDX,EDX / JZ` is there to catch.
//
// Prepending would be shorter, and would be wrong here: it would silently
// reverse every chain and turn a "the match is behind another node" scene into
// a "the match is at the head" one, which is a different question. Each scene
// asserts the order it meant, so a reversal cannot pass unnoticed.
Word chain(const std::initializer_list<Word>& keys) {
  Word head = 0u;
  Word tail = 0u;
  for (Word key : keys) {
    const Word node = new_node(key, 0u);
    if (head == 0u) {
      head = node;
    } else {
      g_node_pool[g_node_used - 2u].next =
          reinterpret_cast<BucketNode*>(static_cast<std::uintptr_t>(node));
    }
    tail = node;
    (void)tail;
  }
  return head;
}

void link_bucket(std::size_t slot, Word head) { g_bucket_slots[slot] = head; }

void reset_trace() {
  g_insert_depth = 0;
  for (std::size_t i = 0; i < kMaxInsertDepth; ++i) {
    g_insert_trace[i].container = 0u;
    g_insert_trace[i].value = 0u;
    g_insert_trace[i].context = 0u;
    g_insert_trace[i].value_at = 0u;
  }
}

// ---------------------------------------------------------------------------
// Scenes.
//
// Each arms the image and the chains and states what the machine must answer.
// Bucket counts are 4 and 3, and the 5/3 scenes exist precisely because
// 5 % 3 == 2, 5 / 3 == 1 and 5 & 2 == 0 are three different answers.
// ---------------------------------------------------------------------------

enum SceneId : std::size_t {
  kHitBehindAnotherNode,       // head -> other -> match            => present
  kHitAtHead,                  // head -> match -> other            => present
  kMissOnANonEmptyBucket,      // head -> other -> other2           => insert
  kEmptyBucket,                // no chain at all                   => insert
  kDuplicateKey,               // head -> match -> match            => present
  kMatchInAnotherBucketOnly,   // the key sits in a different slot   => insert
  kKeyZero,                    // key 0, present                    => present
  kKeyAllOnes,                 // key 0xffffffff, present           => present
  kKeyLowByteSet,              // key with its low byte set, absent  => insert
  kRemainderIsNotTheQuotient,  // 5 % 3 == 2, 5 / 3 == 1            => present
  kMaskWouldPickTheWrongSlot,  // 5 & 2 == 0, and 5 is in slot 0    => insert
  kLongChain,                  // four others, then the match       => present
  kSceneSentinel,
};

struct Scene {
  const char* name;
  SceneId id;
  Word bucket_count;
  Word key;
  bool present;
  std::size_t inserts;
};

const Scene kScenes[] = {
    {"hit_behind_another_node", kHitBehindAnotherNode, 4u, 0x00000111u, true, 0u},
    {"hit_at_head", kHitAtHead, 4u, 0x00000111u, true, 0u},
    {"miss_on_a_non_empty_bucket", kMissOnANonEmptyBucket, 4u, 0x00000111u, false,
     1u},
    {"empty_bucket", kEmptyBucket, 4u, 0x00000111u, false, 1u},
    {"duplicate_key", kDuplicateKey, 4u, 0x00000111u, true, 0u},
    {"match_in_another_bucket_only", kMatchInAnotherBucketOnly, 4u, 0x00000111u,
     false, 1u},
    {"key_zero", kKeyZero, 4u, 0x00000000u, true, 0u},
    {"key_all_ones", kKeyAllOnes, 4u, 0xffffffffu, true, 0u},
    {"key_low_byte_set", kKeyLowByteSet, 4u, 0x1234abcdu, false, 1u},
    {"remainder_is_not_the_quotient", kRemainderIsNotTheQuotient, 3u, 0x00000005u,
     true, 0u},
    {"mask_would_pick_the_wrong_slot", kMaskWouldPickTheWrongSlot, 3u, 0x00000005u,
     false, 1u},
    {"long_chain", kLongChain, 4u, 0x00000111u, true, 0u},
};
constexpr std::size_t kSceneCount = sizeof(kScenes) / sizeof(kScenes[0]);

// Reference readers. They exist so a case that claims "it read this field, not
// its neighbour" can actually fail: without them a harness that could not tell
// two addresses apart would report the same answer for all of them and the
// assertion would hold for the wrong reason.
Word reference_table_field() {
  return g_bucket_table_image.words[kBucketArrayDisplacement / sizeof(Word)];
}
Word reference_count_field() {
  return g_bucket_table_image.words[kBucketCountDisplacement / sizeof(Word)];
}
Word reference_word_below_the_pair() {
  return g_bucket_table_image
      .words[(kBucketArrayDisplacement / sizeof(Word)) - 1];
}
Word reference_word_above_the_pair() {
  return g_bucket_table_image
      .words[(kBucketCountDisplacement / sizeof(Word)) + 1];
}

void arm_scene(std::size_t index) {
  const Scene& scene = kScenes[index];

  for (std::size_t i = 0; i < kImageWords; ++i) {
    g_bucket_table_image.words[i] = kGuardCanary;
  }
  for (std::size_t i = 0; i < kBucketSlots; ++i) {
    g_bucket_slots[i] = 0u;
    g_bucket_slots_b[i] = 0u;
  }
  for (std::size_t i = 0; i < kNodePool; ++i) {
    g_node_pool[i].key = 0u;
    g_node_pool[i].next = nullptr;
  }
  g_node_used = 0;
  reset_trace();

  g_bucket_table_image.words[kBucketArrayDisplacement / sizeof(Word)] =
      pointer_word(g_bucket_slots);
  g_bucket_table_image.words[kBucketCountDisplacement / sizeof(Word)] =
      scene.bucket_count;

  // The key's own bucket, computed the machine's way, so a scene can never
  // disagree with the body about where the match belongs.
  const std::size_t bucket =
      static_cast<std::size_t>(scene.key % scene.bucket_count);

  switch (scene.id) {
    case kHitBehindAnotherNode:
      link_bucket(bucket, chain({scene.key + 1u, scene.key}));
      break;
    case kHitAtHead:
      link_bucket(bucket, chain({scene.key, scene.key + 1u}));
      break;
    case kMissOnANonEmptyBucket:
      link_bucket(bucket, chain({scene.key + 1u, scene.key + 2u}));
      break;
    case kEmptyBucket:
      break;
    case kDuplicateKey:
      link_bucket(bucket, chain({scene.key, scene.key}));
      break;
    case kMatchInAnotherBucketOnly: {
      // The key is genuinely in the table, but in a slot the machine must not
      // reach, and the slot it DOES reach is empty. This is the scene that
      // separates "hashed to the right bucket" from "scanned the whole table".
      const std::size_t elsewhere = (bucket + 1u) % scene.bucket_count;
      link_bucket(elsewhere, chain({scene.key}));
      break;
    }
    case kKeyZero:
      link_bucket(bucket, chain({scene.key}));
      break;
    case kKeyAllOnes:
      link_bucket(bucket, chain({scene.key}));
      break;
    case kKeyLowByteSet:
      // A MISS on purpose: the third argument is only observable on the insert
      // path, and this key has to have its low byte set for the claim to be
      // worth testing. So the bucket holds a decoy and the key is absent.
      link_bucket(bucket, chain({scene.key ^ 0x5a5a5a5au}));
      break;
    case kRemainderIsNotTheQuotient:
      // 5 % 3 == 2 and 5 / 3 == 1: the match lives in slot 2 and slots 0 and 1
      // hold decoys, so a body taking the quotient, or masking with count - 1,
      // reads an empty bucket and reports "not there".
      link_bucket(0u, chain({0x00c0ffeeu}));
      link_bucket(1u, chain({0x00c0ffefu}));
      link_bucket(2u, chain({scene.key}));
      break;
    case kMaskWouldPickTheWrongSlot:
      // 5 & 2 == 0 while 5 % 3 == 2: the key is in slot 0, so the machine must
      // say "not there" and a masking body says "there".
      link_bucket(0u, chain({scene.key}));
      link_bucket(2u, chain({scene.key + 7u}));
      break;
    case kLongChain:
      link_bucket(
          bucket, chain({scene.key + 1u, scene.key + 2u, scene.key + 3u,
                         scene.key + 4u, scene.key}));
      break;
    case kSceneSentinel:
      break;
  }
}

// ---------------------------------------------------------------------------
// The battery.
//
// One scene, one probe, and everything the listing fixes.
// ---------------------------------------------------------------------------

// Snapshot of the modelled receiver, so "the entry wrote nothing" is a
// comparison rather than an assumption.
struct ImageSnapshot {
  Word words[kImageWords];
};

bool scene_agrees(Probe probe, std::size_t index) {
  const Scene& scene = kScenes[index];
  arm_scene(index);

  // The scene must be able to TELL the three readings apart, or it proves
  // nothing about the entry.
  if (scene.bucket_count == 0u) {
    return false;  // the machine's DIV would fault; such a scene is not armed
  }
  if (scene.bucket_count > kBucketSlots) {
    return false;  // the modelled table has no such slot
  }
  if (g_bucket_table_image.words[kBucketArrayDisplacement / sizeof(Word)] ==
      g_bucket_table_image.words[kBucketCountDisplacement / sizeof(Word)]) {
    return false;  // the two fields are indistinguishable
  }
  if (scene.id == kRemainderIsNotTheQuotient &&
      (scene.key % scene.bucket_count) == (scene.key / scene.bucket_count)) {
    return false;
  }
  if (scene.id == kRemainderIsNotTheQuotient &&
      (scene.key % scene.bucket_count) == (scene.key & (scene.bucket_count - 1u))) {
    return false;
  }
  if (scene.id == kMaskWouldPickTheWrongSlot &&
      (scene.key % scene.bucket_count) == (scene.key & (scene.bucket_count - 1u))) {
    return false;
  }
  if (scene.id == kKeyLowByteSet &&
      (scene.key & kArgumentSlotLowByteMask) == scene.key) {
    return false;  // the low byte is clear, so this scene cannot separate the
                   // third argument from the key
  }
  if (scene.id == kKeyLowByteSet &&
      (scene.key & kArgumentSlotLowByteMask) == 0u) {
    return false;  // a literal-zero third argument would pass this scene
  }

  ImageSnapshot before;
  for (std::size_t i = 0; i < kImageWords; ++i) {
    before.words[i] = g_bucket_table_image.words[i];
  }
  // The node pool is part of the observable state too: a body that wrote
  // through a node it was only supposed to read would show up here.
  BucketNode nodes_before[kNodePool];
  for (std::size_t i = 0; i < kNodePool; ++i) {
    nodes_before[i] = g_node_pool[i];
  }

  const EspSamples samples = call_probe(probe, receiver_of(), scene.key);

  // 1. the return value. The machine writes only AL (0x00c77c46), so a `bool`
  //    is the whole of the declared contract and nothing wider is judged.
  if (samples.present != scene.present) {
    return false;
  }

  // 2. the insert count, read back out of the same call.
  if (samples.insert_depth != scene.inserts) {
    return false;
  }
  if (g_insert_depth >= kMaxInsertDepth) {
    return false;  // the recorded window is not the whole of what happened
  }

  if (scene.inserts == 1u) {
    const InsertTraceEntry& trace = samples.trace;
    // 4. the second argument points at a slot carrying the key.
    if (trace.value_at != scene.key) {
      return false;
    }
    // 5. the third argument is the key with its low byte cleared. This is the
    //    assertion that separates "the byte store is load-bearing" from
    //    Ghidra's literal zero.
    if (trace.context != (scene.key & kArgumentSlotLowByteMask)) {
      return false;
    }
    // 6. the two pointers are the two ADJACENT locals the two LEAs named: both
    //    four-aligned, distinct, close together, and neither of them any
    //    modelled object.
    //
    //    The distance is bounded rather than pinned to a single value. The
    //    machine puts the twelve-byte container ABOVE the four-byte value slot
    //    (`value - container == -4`), but which way round a C++ compiler lays
    //    two adjacent locals out is its own choice, and the reconstruction
    //    declares them as two separate objects precisely because the machine
    //    only shows two addresses eight bytes apart. What IS claimed, and what a
    //    swapped pair of arguments cannot satisfy, is checked on the next line:
    //    the SECOND argument is the one that points at a slot carrying the key.
    if (trace.container == trace.value) {
      return false;
    }
    const Word gap = (trace.container > trace.value)
                         ? (trace.container - trace.value)
                         : (trace.value - trace.container);
    if (gap > 2u * sizeof(Word) + kContainerLocalBytes) {
      return false;  // they are nowhere near each other: not the machine's pair
    }
    if ((trace.container & 3u) != 0u || (trace.value & 3u) != 0u) {
      return false;
    }
    if (trace.container == trace.value) {
      return false;
    }
    const Word modelled[] = {
        pointer_word(image_as_bytes()), pointer_word(g_bucket_slots),
        pointer_word(g_node_pool),      pointer_word(receiver_of()),
        scene.key,                      scene.bucket_count,
    };
    for (std::size_t i = 0; i < sizeof(modelled) / sizeof(modelled[0]); ++i) {
      if (trace.container == modelled[i] || trace.value == modelled[i]) {
        return false;  // the scene cannot tell them apart, so it proves nothing
      }
    }
  }

  // 7. nothing was written: not the image, not a node.
  for (std::size_t i = 0; i < kImageWords; ++i) {
    if (g_bucket_table_image.words[i] != before.words[i]) {
      return false;
    }
  }
  for (std::size_t i = 0; i < kNodePool; ++i) {
    if (g_node_pool[i].key != nodes_before[i].key ||
        g_node_pool[i].next != nodes_before[i].next) {
      return false;
    }
  }
  return true;
}

bool probe_agrees_on_every_scene(Probe probe) {
  for (std::size_t index = 0; index < kSceneCount; ++index) {
    if (!scene_agrees(probe, index)) {
      std::fprintf(stderr, "0x00c77bf0: battery rejects scene '%s'\n",
                   kScenes[index].name);
      return false;
    }
  }
  return true;
}

// ---------------------------------------------------------------------------
// Mutants: bodies that are wrong in exactly one way each.
//
// Each is driven through the SAME battery, so a mutant that survives means the
// battery has lost the power to tell a correct body from a wrong one.
// ---------------------------------------------------------------------------

// The two receiver words, read the way the entry reads them, so the mutants
// differ from the reconstruction in exactly one named respect.
const Word* table_of(const std::uint8_t* bytes, std::size_t displacement) {
  return reinterpret_cast<const Word*>(word_at(bytes, displacement));
}

// Wrong: the index is the key masked down to a power-of-two bound instead of
// the remainder. On the 5/3 scenes 5 & 2 == 0 while 5 % 3 == 2.
bool PKG_00C77BF0_CALL mutant_masks_instead_of_modulo(BucketTable* self,
                                                      Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(
           buckets, static_cast<std::size_t>(key & (count - 1u)) *
                        kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  }
  return present;
}

// Wrong: the DIV's QUOTIENT is used as the index instead of its remainder.
bool PKG_00C77BF0_CALL mutant_quotient_instead_of_remainder(BucketTable* self,
                                                           Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link =
      bucket_word(buckets, static_cast<std::size_t>(key / count) *
                           kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  }
  return present;
}

// Wrong: the two receiver words are swapped -- the count is read out of the
// pointer slot and the array pointer out of the count slot.
bool PKG_00C77BF0_CALL mutant_table_and_count_swapped(BucketTable* self,
                                                      Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketArrayDisplacement);
  const Word* const buckets = table_of(bytes, kBucketCountDisplacement);
  Word matches = 0u;
  for (Word link =
      bucket_word(buckets, static_cast<std::size_t>(key % count) *
                           kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  }
  return present;
}

// Wrong: the bucket array is read one word too high, out of the divisor's own
// slot. The 0x1120 and 0x1124 pair is exactly the kind of adjacent pair a
// reconstruction gets off by one.
bool PKG_00C77BF0_CALL mutant_table_displacement_off_by_four(BucketTable* self,
                                                           Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketCountDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(buckets, static_cast<std::size_t>(key % count) * kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  }
  return present;
}

// Wrong: the bucket index is used as a BYTE offset into the table, dropping the
// SIB scale of four.
bool PKG_00C77BF0_CALL mutant_bucket_array_indexed_by_bytes(BucketTable* self,
                                                           Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(buckets, static_cast<std::size_t>(key % count));
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  }
  return present;
}

// Wrong: only the HEAD node of the chain is inspected. The walk is gone.
bool PKG_00C77BF0_CALL mutant_inspects_only_the_head_node(BucketTable* self,
                                                         Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  const Word head =
      bucket_word(buckets, static_cast<std::size_t>(key % count) *
                           kBucketSlotBytes);
  const bool present =
      (head != 0u) && (node_word(head, kNodeKeyDisplacement) == key);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  }
  return present;
}

// Wrong: the chain is followed through the KEY word instead of the LINK word.
bool PKG_00C77BF0_CALL mutant_walks_the_chain_backwards(BucketTable* self,
                                                       Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(buckets, static_cast<std::size_t>(key % count) * kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeKeyDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  }
  return present;
}

// Wrong: the miss is detected but nothing is ever handed to 0x00de5df0.
bool PKG_00C77BF0_CALL mutant_never_inserts_on_a_miss(BucketTable* self,
                                                      Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(buckets, static_cast<std::size_t>(key % count) * kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  return matches != 0u;
}

// Wrong: the insert runs unconditionally, on a hit as well as on a miss.
bool PKG_00C77BF0_CALL mutant_inserts_even_on_a_hit(BucketTable* self, Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(buckets, static_cast<std::size_t>(key % count) * kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  alignas(4) std::uint8_t container[kContainerLocalBytes];
  Word value = key;
  FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  return matches != 0u;
}

// Wrong: the third argument is the key itself, i.e. the byte store at 0x00c77c28
// is treated as a no-op.
bool PKG_00C77BF0_CALL mutant_insert_third_argument_is_the_key(
    BucketTable* self, Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(buckets, static_cast<std::size_t>(key % count) * kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, key);
  }
  return present;
}

// Wrong: the third argument is a literal zero -- which is what Ghidra's
// decompilation prints. Kept as a mutant precisely because the decompilation
// says it, so the disagreement between the listing and the decompilation is
// decided by a test rather than by preference.
bool PKG_00C77BF0_CALL mutant_insert_third_argument_is_zero(BucketTable* self,
                                                          Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(buckets, static_cast<std::size_t>(key % count) * kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, 0u);
  }
  return present;
}

// Wrong: the first two arguments are handed over in the wrong order, so the
// callee is given the address of the key slot as the container and the address
// of the twelve-byte local as the value.
bool PKG_00C77BF0_CALL mutant_insert_first_two_arguments_swapped(
    BucketTable* self, Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(buckets, static_cast<std::size_t>(key % count) * kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(&value, reinterpret_cast<const Word*>(container),
                 key & kArgumentSlotLowByteMask);
  }
  return present;
}

// Wrong: the flag is inverted. The count is still right, so this is the mutant
// that proves the battery looks at what the body RETURNS and not only at the
// state it left behind.
bool PKG_00C77BF0_CALL mutant_returns_the_inverted_flag(BucketTable* self,
                                                       Word key) {
  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);
  const Word count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = table_of(bytes, kBucketArrayDisplacement);
  Word matches = 0u;
  for (Word link = bucket_word(buckets, static_cast<std::size_t>(key % count) * kBucketSlotBytes);
       link != 0u; link = node_word(link, kNodeNextDisplacement)) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
  }
  const bool present = (matches != 0u);
  if (!present) {
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  }
  return !present;
}

// Wrong: the terminator pops NOTHING, i.e. a bare RET where the machine has
// `ret 4`. Spelled in asm rather than with a convention attribute on purpose:
// the defect under test is the terminator, and driving it through the padded
// channel keeps the defect from being the shim. 0x00c77c4c is C2 04 00, so a
// bare RET is a real contradiction of the body.
#if defined(_MSC_VER)
__declspec(naked) bool PKG_00C77BF0_CALL mutant_pops_nothing_at_the_terminal(
    BucketTable* self [[maybe_unused]], Word key [[maybe_unused]]) { __asm { ret } }
__declspec(naked) bool PKG_00C77BF0_CALL mutant_pops_eight_at_the_terminal(
    BucketTable* self [[maybe_unused]], Word key [[maybe_unused]]) { __asm { ret 8 } }
__declspec(naked) bool PKG_00C77BF0_CALL mutant_pops_sixteen_at_the_terminal(
    BucketTable* self [[maybe_unused]], Word key [[maybe_unused]]) { __asm { ret 16 } }
#else
__attribute__((naked, thiscall)) bool mutant_pops_nothing_at_the_terminal(
    BucketTable* self [[maybe_unused]], Word key [[maybe_unused]]) {
  __asm__("ret");
}
__attribute__((naked, thiscall)) bool mutant_pops_eight_at_the_terminal(
    BucketTable* self [[maybe_unused]], Word key [[maybe_unused]]) {
  __asm__("ret $8");
}
__attribute__((naked, thiscall)) bool mutant_pops_sixteen_at_the_terminal(
    BucketTable* self [[maybe_unused]], Word key [[maybe_unused]]) {
  __asm__("ret $16");
}
#endif

struct Mutant {
  const char* name;
  Probe entry;
};

const Mutant kMutants[] = {
    {"masks_instead_of_modulo", &mutant_masks_instead_of_modulo},
    {"quotient_instead_of_remainder", &mutant_quotient_instead_of_remainder},
    {"table_and_count_swapped", &mutant_table_and_count_swapped},
    {"table_displacement_off_by_four", &mutant_table_displacement_off_by_four},
    {"bucket_array_indexed_by_bytes", &mutant_bucket_array_indexed_by_bytes},
    {"inspects_only_the_head_node", &mutant_inspects_only_the_head_node},
    {"walks_the_chain_backwards", &mutant_walks_the_chain_backwards},
    {"never_inserts_on_a_miss", &mutant_never_inserts_on_a_miss},
    {"inserts_even_on_a_hit", &mutant_inserts_even_on_a_hit},
    {"insert_third_argument_is_the_key",
     &mutant_insert_third_argument_is_the_key},
    {"insert_third_argument_is_zero", &mutant_insert_third_argument_is_zero},
    {"insert_first_two_arguments_swapped",
     &mutant_insert_first_two_arguments_swapped},
    {"returns_the_inverted_flag", &mutant_returns_the_inverted_flag},
    {"pops_nothing_at_the_terminal", &mutant_pops_nothing_at_the_terminal},
    {"pops_eight_at_the_terminal", &mutant_pops_eight_at_the_terminal},
    {"pops_sixteen_at_the_terminal", &mutant_pops_sixteen_at_the_terminal},
};
constexpr std::size_t kMutantCount = sizeof(kMutants) / sizeof(kMutants[0]);

}  // namespace model
}  // namespace openspore::reconstruction::pkg_00c77bf0_bucket_membership

namespace {

using namespace openspore::reconstruction::pkg_00c77bf0_bucket_membership;
using namespace openspore::reconstruction::pkg_00c77bf0_bucket_membership::model;

// The machine ABI, asserted against the declaration: receiver in ECX, ONE
// ordinary stack argument, the entry removing it itself, and a one-byte result.
// This is the compile-time gate -- change the prototype and this stops building.
static_assert(
    std::is_same<decltype(&bucket_membership_insert_00c77bf0),
                 AbiBucketMembershipInsert00c77bf0>::value,
    "0x00c77bf0 is a __thiscall entry taking the receiver in ECX and one 4-byte "
    "stack argument, removing that argument itself (`ret 4`), and producing a "
    "one-byte flag in AL");
static_assert(sizeof(AbiBucketMembershipInsert00c77bf0) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");
static_assert(sizeof(void*) == 4u,
              "the modelled entry is a 32-bit code pointer, so this is an "
              "x86-32 reconstruction");
static_assert(sizeof(Word) == 4u, "the modelled word is one 32-bit dword");
static_assert(kMutantCount == 16u, "the battery has sixteen known-wrong bodies");
static_assert(kSceneCount == 12u, "there are twelve scenes");

// ---------------------------------------------------------------------------
// Direction A: the whole battery, over every scene.
// ---------------------------------------------------------------------------

void test_the_whole_battery_over_every_scene() {
  check(probe_agrees_on_every_scene(&real_entry),
        "the reconstruction satisfies the battery on every scene");
}

// A. The bucket index is the key's UNSIGNED REMAINDER modulo the dword at
//    +0x1124, and the bucket is a four-byte slot. The reference readers prove
//    the harness can tell the two fields, their neighbours and the bucket array
//    apart, so a wrong index cannot pass for want of a discriminating scene.
void test_index_is_the_remainder_not_the_quotient_or_a_mask() {
  arm_scene(9);  // remainder_is_not_the_quotient: 5 % 3 == 2
  const Word key = kScenes[9].key;
  const Word count = reference_count_field();
  check(count == 3u);
  check(reference_table_field() == pointer_word(g_bucket_slots));
  check(reference_word_below_the_pair() == kGuardCanary);
  check(reference_word_above_the_pair() == kGuardCanary);
  check(key % count == 2u);
  check(key / count == 1u);
  check((key & (count - 1u)) == 0u);

  // Slot 2 holds the match, slots 0 and 1 hold decoys. Only the remainder finds
  // it, so this single call separates all three readings.
  check(g_bucket_slots[0] != 0u);
  check(g_bucket_slots[1] != 0u);
  check(g_bucket_slots[2] != 0u);
  check(node_word(g_bucket_slots[0], kNodeKeyDisplacement) != key);
  check(node_word(g_bucket_slots[1], kNodeKeyDisplacement) != key);
  check(node_word(g_bucket_slots[2], kNodeKeyDisplacement) == key);

  const EspSamples samples = call_probe(&real_entry, receiver_of(), key);
  check(samples.present, "the remainder reaches the match");
  check(g_insert_depth == 0u, "a hit does not insert");

  // And the converse: the same key stored in slot 0, where only the mask looks.
  arm_scene(10);  // mask_would_pick_the_wrong_slot
  check(kScenes[10].key % kScenes[10].bucket_count == 2u);
  check(node_word(g_bucket_slots[0], kNodeKeyDisplacement) == kScenes[10].key);
  const EspSamples other = call_probe(&real_entry, receiver_of(),
                                      kScenes[10].key);
  check(!other.present,
        "a masking body would have said 'present' here");
  check(g_insert_depth == 1u, "a miss inserts exactly once");
}

// B. The bucket array is the dword at +0x1120 and the divisor the dword at
//    +0x1124; the pair is neither swapped nor off by one word, and the key
//    sitting in a DIFFERENT bucket is not found -- which is the difference
//    between hashing and scanning.
void test_the_two_receiver_words_are_not_swapped_or_shifted() {
  const std::size_t table_index = kBucketArrayDisplacement / sizeof(Word);
  const std::size_t count_index = kBucketCountDisplacement / sizeof(Word);
  check(table_index + 1u == count_index);
  check(kBucketArrayDisplacement == 0x1120u);
  check(kBucketCountDisplacement == 0x1124u);
  check(kBucketCountDisplacement - kBucketArrayDisplacement == sizeof(Word));

  arm_scene(5);  // match_in_another_bucket_only
  const Word key = kScenes[5].key;
  const std::size_t bucket = static_cast<std::size_t>(key % kScenes[5].bucket_count);
  check(g_bucket_slots[bucket] == 0u, "the bucket the machine reads is empty");
  check(reference_table_field() == pointer_word(g_bucket_slots));
  check(reference_count_field() == kScenes[5].bucket_count);

  // A body that scanned the whole table would have found the key one slot over.
  bool found_elsewhere = false;
  for (std::size_t slot = 0; slot < kBucketSlots; ++slot) {
    for (Word link = g_bucket_slots[slot]; link != 0u;
         link = node_word(link, kNodeNextDisplacement)) {
      if (node_word(link, kNodeKeyDisplacement) == key) {
        found_elsewhere = true;
      }
    }
  }
  check(found_elsewhere, "the key really is in the table, just not in reach");

  const EspSamples samples = call_probe(&real_entry, receiver_of(), key);
  check(!samples.present);
  check(g_insert_depth == 1u);
}

// C. The chain is walked to its end, following the LINK word at +4 and
//    comparing the KEY word at +0. The long-chain scene puts the match last,
//    behind four others, and the long-chain walk is also the case a
//    head-only reconstruction fails.
void test_walks_the_chain_to_its_end_following_the_link_word() {
  arm_scene(11);  // long_chain
  const Word key = kScenes[11].key;
  const std::size_t bucket = static_cast<std::size_t>(key % kScenes[11].bucket_count);

  std::size_t length = 0u;
  Word last_key = 0u;
  for (Word link = g_bucket_slots[bucket]; link != 0u;
       link = node_word(link, kNodeNextDisplacement)) {
    last_key = node_word(link, kNodeKeyDisplacement);
    ++length;
  }
  check(length == 5u, "the scene really is a five-node chain");
  check(last_key == key, "and the match is the LAST node of it");

  const EspSamples samples = call_probe(&real_entry, receiver_of(), key);
  check(samples.present, "a head-only body would have missed it");
  check(g_insert_depth == 0u);

  // The key word and the link word are different words, and the walk uses both
  // in their own roles: corrupting either one changes the answer.
  arm_scene(0);  // hit_behind_another_node
  const Word head = g_bucket_slots[static_cast<std::size_t>(
      kScenes[0].key % kScenes[0].bucket_count)];
  check(node_word(head, kNodeKeyDisplacement) != kScenes[0].key);
  check(node_word(node_word(head, kNodeNextDisplacement), kNodeKeyDisplacement) ==
        kScenes[0].key);
  const EspSamples behind = call_probe(&real_entry, receiver_of(),
                                       kScenes[0].key);
  check(behind.present);
  check(g_insert_depth == 0u);
}

// D. The insert happens on a miss and ONLY on a miss, exactly once, and the
//    body writes nothing extra into the receiver when it does.
void test_inserts_exactly_once_on_a_miss_and_never_on_a_hit() {
  arm_scene(3);  // empty_bucket
  check(g_bucket_slots[0] == 0u);
  const EspSamples miss = call_probe(&real_entry, receiver_of(),
                                     kScenes[3].key);
  check(!miss.present);
  check(g_insert_depth == 1u, "a miss inserts once");
  check(g_insert_depth < kMaxInsertDepth);

  arm_scene(1);  // hit_at_head
  const EspSamples hit = call_probe(&real_entry, receiver_of(), kScenes[1].key);
  check(hit.present);
  check(g_insert_depth == 0u, "a hit does not insert");

  arm_scene(4);  // duplicate_key: two nodes carry the key
  const EspSamples dup = call_probe(&real_entry, receiver_of(), kScenes[4].key);
  check(dup.present, "a duplicated key is still one hit");
  check(g_insert_depth == 0u);
}

// E. The three arguments to 0x00de5df0.
//
// E1. The second argument points at a slot carrying the key: the store at
//     0x00c77c3b is what makes the pointer worth handing over.
void test_the_value_slot_carries_the_key() {
  arm_scene(2);  // miss_on_a_non_empty_bucket
  const Word key = kScenes[2].key;
  const EspSamples samples = call_probe(&real_entry, receiver_of(), key);
  check(!samples.present);
  check(samples.insert_depth == 1u);
  check(samples.trace.value_at == key);
  check((g_insert_trace[0].value & 3u) == 0u, "the slot is word-aligned");
}

// E2. The third argument is the key with its LOW BYTE CLEARED. This is the
//     substantive claim in the package and the one the decompilation gets
//     wrong: Ghidra prints a literal 0 there, but 0x00c77c28 stores the SETNZ
//     byte into the argument word and 0x00c77c2c reads that word back, so the
//     value the callee sees is `key & 0xffffff00`. The key used here has both
//     its low byte and its high byte set, so "the key", "a literal zero" and
//     "the key with its low byte cleared" are three different numbers.
void test_third_argument_is_the_key_with_its_low_byte_cleared() {
  arm_scene(8);  // key_low_byte_set
  const Word key = kScenes[8].key;
  check((key & 0xffu) != 0u, "the scene key has its low byte set");
  check(key >= 0x100u, "the scene key has more than its low byte set");
  check((key & kArgumentSlotLowByteMask) != 0u);
  check((key & kArgumentSlotLowByteMask) != key);
  check((key & kArgumentSlotLowByteMask) != 0u);
  check(kArgumentSlotStoreWidthBytes == 1u);

  const EspSamples samples = call_probe(&real_entry, receiver_of(), key);
  check(!samples.present);
  check(samples.insert_depth == 1u);
  check(samples.trace.context == (key & kArgumentSlotLowByteMask),
        "the third argument is the key with its low byte cleared");
  check(samples.trace.context != key, "and not the key unchanged");
  check(samples.trace.context != 0u, "and not a literal zero");
}

// E3. The two pointers are the two ADJACENT locals the two LEAs named, four
//     bytes apart -- the container above, the value slot below. A body that
//     swapped them hands the callee the address of the key slot first.
void test_the_two_pointers_are_the_two_adjacent_locals() {
  arm_scene(4 - 1);  // empty_bucket
  const Word key = kScenes[3].key;
  const EspSamples samples = call_probe(&real_entry, receiver_of(), key);
  check(!samples.present);
  check(samples.insert_depth == 1u);
  const InsertTraceEntry& trace = samples.trace;
  const Word gap = (trace.container > trace.value)
                       ? (trace.container - trace.value)
                       : (trace.value - trace.container);
  check(gap <= 2u * sizeof(Word) + kContainerLocalBytes,
        "the two arguments are the two adjacent locals, not two unrelated "
        "addresses");
  check(kContainerLocalBytes == 12u);
  check(trace.container != trace.value);
  check((trace.container & 3u) == 0u);
  check(trace.value_at == key);

  // The pointers are the caller's own frame, so neither of them is any of the
  // modelled objects: the receiver image, the bucket array, the node pool, the
  // receiver itself, and neither numeric field.
  const Word modelled[] = {pointer_word(image_as_bytes()),
                           pointer_word(g_bucket_slots),
                           pointer_word(g_node_pool),
                           pointer_word(receiver_of()),
                           key,
                           kScenes[3].bucket_count};
  for (std::size_t i = 0; i < sizeof(modelled) / sizeof(modelled[0]); ++i) {
    check(trace.container != modelled[i]);
    check(trace.value != modelled[i]);
  }
}

// F. The entry's stack effect, pinned where it can be pinned.
//
// This case does NOT measure ESP, and says so. An earlier revision of this
// harness did: a hand-written trampoline that called each probe and sampled ESP
// either side of the call, calibrated against control callees with five
// different cleanups. It was dropped, for a reason worth recording -- the
// measurement needs a stack the caller owns and a callee whose cleanup is
// whatever is under test, and every arrangement of that either trusts the very
// thing it is measuring or reintroduces the frame discipline it needs to
// measure. The facts themselves are unchanged and are asserted three ways
// instead, each of which a mutation breaks:
//
//   * the transcribed bytes: 0x00c77c4c is C2 04 00, a RET with an immediate of
//     four, so the entry removes one word of its own;
//   * the ABI type: the entry is declared __thiscall taking the receiver and
//     exactly one ordinary stack argument, and the header's static_assert stops
//     the build if either changes;
//   * the callee's shape: three words go in front of the single call and the
//     body removes none of them, which is only coherent if the callee removes
//     all twelve, and that is what the modelled callee's declaration says.
void test_stack_effect_is_pinned_by_the_bytes_and_the_prototype() {
  check(kTargetBytes[92] == 0xc2u, "0x00c77c4c is a RET with an immediate");
  check(kTargetBytes[93] == 0x04u, "whose immediate is four");
  check(kTargetBytes[94] == 0x00u);
  check(kEntryCleanupBytes == 4u);
  check(kEntryCleanupBytes == sizeof(Word));
  check(kOrdinaryStackArgumentSlots == 1u);

  // Three words in front of the call, and the body's own removal of them is
  // zero: the first instruction after the CALL is a POP of a saved register.
  check(kCalleeStackArgumentWords == 3u);
  check(kCalleeCleanupBytes == 12u);
  check(kCalleeCleanupBytes == kCalleeStackArgumentWords * sizeof(Word));
  check(kTargetBytes[79] == 0xe8u, "the body's only call is at 0x00c77c3f");
  check(kTargetBytes[84] == 0x5fu, "and 0x00c77c44, five bytes later, is POP EDI");
  check(kTargetBytes[85] == 0x5eu, "POP ESI");
  check(kTargetBytes[86] == 0x8au, "MOV AL,BL");
  check(kTargetBytes[88] == 0x5bu, "POP EBX");
  check(kCalleeCount == 1u);

  // The insertion block is reached, and reached through the miss, so the three
  // words really were pushed in the run the battery just graded.
  arm_scene(3);
  const EspSamples samples = call_probe(&real_entry, receiver_of(), kScenes[3].key);
  check(samples.insert_depth == 1u,
        "the miss really did reach the call, so the callee's own cleanup of "
        "those three words is what let the entry's epilogue run at all");
  check(!samples.present);
}

// G. The machine facts the whole package rests on, re-checked at run time,
//    including that every constant really is decoded out of the transcribed
//    bytes rather than restated beside them.
void test_machine_facts() {
  check(kEntryVa == 0x00c77bf0u);
  check(kTerminalVa == 0x00c77c4cu);
  check(kBodyBytes == 95u);
  check(kInstructionCount == 39u);
  check(kCalleeCount == 1u);
  check(kConditionalBranches == 4u);
  check(kReceiverBias == 0x111cu);
  check(kBucketArrayDisplacement == 0x1120u);
  check(kBucketCountDisplacement == 0x1124u);
  check(kFrameBytes == 0x10u);
  check(kSavedRegisterPushes == 3u);
  check(kArgumentSlotDisplacement == 0x20u);
  check(kArgumentSlotStoreWidthBytes == 1u);
  check(kArgumentSlotLowByteMask == 0xffffff00u);
  check(kNodeKeyDisplacement == 0u);
  check(kNodeNextDisplacement == 4u);
  check(kBucketIndexIsRemainder == 1u);
  check(kBucketSlotBytes == 4u);
  check(kCalleeVa == 0x00de5df0u);
  check(kContainerLocalBytes == 12u);
  check(kOrdinaryStackArgumentSlots == 1u);
  check(kEntryCleanupBytes == 4u);
  check(kCalleeStackArgumentWords == 3u);
  check(kCalleeCleanupBytes == 12u);
  check(kMaxInsertDepth == 4u);

  // The image, byte for byte.
  check(kTargetBytes[0] == 0x83u && kTargetBytes[1] == 0xecu &&
        kTargetBytes[2] == 0x10u);
  check(kTargetBytes[3] == 0x53u);
  check(kTargetBytes[4] == 0x56u);
  check(kTargetBytes[5] == 0x57u);
  check(kTargetBytes[6] == 0x8bu && kTargetBytes[7] == 0x7cu &&
        kTargetBytes[8] == 0x24u && kTargetBytes[9] == 0x20u);
  check(kTargetBytes[10] == 0x81u && kTargetBytes[11] == 0xc1u &&
        kTargetBytes[12] == 0x1cu && kTargetBytes[13] == 0x11u);
  check(kTargetBytes[16] == 0x33u && kTargetBytes[17] == 0xd2u);
  check(kTargetBytes[20] == 0xf7u && kTargetBytes[21] == 0x71u &&
        kTargetBytes[22] == 0x08u);
  check(kTargetBytes[23] == 0x8bu && kTargetBytes[24] == 0x41u &&
        kTargetBytes[25] == 0x04u);
  check(kTargetBytes[28] == 0x8bu && kTargetBytes[29] == 0x14u &&
        kTargetBytes[30] == 0x90u);
  check(kTargetBytes[31] == 0x85u && kTargetBytes[32] == 0xd2u);
  check(kTargetBytes[33] == 0x74u && kTargetBytes[34] == 0x0cu);
  check(kTargetBytes[35] == 0x3bu && kTargetBytes[36] == 0x3au);
  check(kTargetBytes[37] == 0x75u && kTargetBytes[38] == 0x01u);
  check(kTargetBytes[39] == 0x46u);
  check(kTargetBytes[40] == 0x8bu && kTargetBytes[41] == 0x52u &&
        kTargetBytes[42] == 0x04u);
  check(kTargetBytes[49] == 0x0fu && kTargetBytes[50] == 0x95u &&
        kTargetBytes[51] == 0xc3u);
  check(kTargetBytes[52] == 0x84u && kTargetBytes[53] == 0xdbu);
  check(kTargetBytes[56] == 0x88u && kTargetBytes[57] == 0x5cu &&
        kTargetBytes[58] == 0x24u && kTargetBytes[59] == 0x20u);
  check(kTargetBytes[60] == 0x8bu && kTargetBytes[61] == 0x54u);
  check(kTargetBytes[65] == 0x8du && kTargetBytes[68] == 0x10u);
  check(kTargetBytes[70] == 0x8du && kTargetBytes[73] == 0x18u);
  check(kTargetBytes[75] == 0x89u && kTargetBytes[78] == 0x18u);
  check(kTargetBytes[79] == 0xe8u);
  check(kTargetBytes[84] == 0x5fu && kTargetBytes[85] == 0x5eu);
  check(kTargetBytes[86] == 0x8au && kTargetBytes[87] == 0xc3u);
  check(kTargetBytes[88] == 0x5bu);
  check(kTargetBytes[89] == 0x83u && kTargetBytes[90] == 0xc4u &&
        kTargetBytes[91] == 0x10u);
  check(kTargetBytes[92] == 0xc2u && kTargetBytes[93] == 0x04u &&
        kTargetBytes[94] == 0x00u);

  // The bias, decoded from the four operand bytes rather than restated.
  const Word decoded_bias = static_cast<Word>(
      static_cast<std::uint32_t>(kTargetBytes[12]) |
      (static_cast<std::uint32_t>(kTargetBytes[13]) << 8) |
      (static_cast<std::uint32_t>(kTargetBytes[14]) << 16) |
      (static_cast<std::uint32_t>(kTargetBytes[15]) << 24));
  check(decoded_bias == kReceiverBias);
  check(kReceiverBias == 0x111cu);

  // The SIB scale, decoded rather than restated: byte 0x90 scales by four.
  check(static_cast<std::size_t>(kTargetBytes[30] >> 6) == 2u);
  check((std::size_t(1) << static_cast<std::size_t>(kTargetBytes[30] >> 6)) ==
        kBucketSlotBytes);

  // The store width, decoded from the opcode: 0x88 is the one-byte form.
  check(kTargetBytes[56] == 0x88u);
  check(kTargetBytes[56] != 0x89u, "0x89 would be the four-byte form");

  // The callee's address, decoded from the rel32.
  check(rel32_target(79) == 0x00de5df0u);
  check(kCalleeVa != kEntryVa);
  check(kCalleeVa == 0x00de5df0u);

  // The frame arithmetic that fixes the argument slot.
  check(kEntryVa + kBodyBytes == 0x00c77c4fu);
  check(kTerminalVa - kEntryVa == 92u);
  check(kArgumentSlotDisplacement == 0x20u);
  check(kBucketArrayDisplacement == kReceiverBias + 4u);
  check(kBucketCountDisplacement == kReceiverBias + 8u);

  // The node layout the walk relies on.
  check(offsetof(BucketNode, key) == 0u);
  check(offsetof(BucketNode, next) == 4u);
  check(sizeof(Word) == 4u);

  // The modelled image is big enough to hold both fields plus a guard band
  // above them.
  check(kImageWords == kBucketCountDisplacement / sizeof(Word) + 1 + kGuardWords);
  check(image_as_bytes() ==
        reinterpret_cast<std::uint8_t*>(&g_bucket_table_image.words[0]));
}

// H. The guard band. The body's one store is a single byte into its OWN
//    incoming argument slot, so nothing in the receiver moves: not the two
//    fields, not the words either side of them, not the band above.
//
//    The two fields are dirtied with values that are still VALID INPUTS -- the
//    array pointer is repointed at a second, differently-populated array and the
//    divisor is changed to another legal count -- because a body that dereferences
//    the array pointer cannot be run against a garbage pointer, and a check that
//    only ever sees canaries proves less than one that sees a value it had to
//    preserve. The words either side and above the pair are set to sentinels, so
//    the "nothing moved" claim is not resting on untouched canaries alone.
void test_writes_nothing_into_the_receiver() {
  const std::size_t table_index = kBucketArrayDisplacement / sizeof(Word);
  const std::size_t count_index = kBucketCountDisplacement / sizeof(Word);

  arm_scene(3);  // a miss, so the insert block runs
  const Word key = kScenes[3].key;
  const std::size_t bucket = static_cast<std::size_t>(key % kScenes[3].bucket_count);
  check(g_bucket_table_image.words[table_index - 1] == kGuardCanary);
  check(g_bucket_table_image.words[count_index + 1] == kGuardCanary);

  // Repoint the array at a second array holding a decoy in the bucket the entry
  // will read, and empty the bucket in the first one. The key is then absent
  // either way, so the insert still runs -- but the pointer the entry used is a
  // value the check can insist on afterwards.
  for (std::size_t i = 0; i < kBucketSlots; ++i) {
    g_bucket_slots_b[i] = 0u;
  }
  g_bucket_slots_b[bucket] = chain({key ^ 0x5a5a5a5au});
  g_bucket_slots[bucket] = 0u;
  g_bucket_table_image.words[table_index] = pointer_word(g_bucket_slots_b);
  g_bucket_table_image.words[count_index] = 4u;
  g_bucket_table_image.words[table_index - 1] = 0x11111111u;
  g_bucket_table_image.words[count_index + 1] = 0x22222222u;
  g_bucket_table_image.words[count_index + 2] = 0x33333333u;

  // The harness can tell the two fields and the sentinels apart, which is what
  // stops the checks below passing for the wrong reason.
  check(reference_table_field() == pointer_word(g_bucket_slots_b));
  check(reference_table_field() != pointer_word(g_bucket_slots));
  check(reference_count_field() == 4u);
  check(reference_word_below_the_pair() == 0x11111111u);
  check(reference_word_above_the_pair() == 0x22222222u);

  reset_trace();
  const EspSamples samples = call_probe(&real_entry, receiver_of(), key);
  check(!samples.present, "the key really is absent from the repointed array");
  check(samples.insert_depth == 1u, "so the insert block really did run");

  check(g_bucket_table_image.words[table_index] == pointer_word(g_bucket_slots_b),
        "the array pointer the body read is still the one it was given");
  check(g_bucket_table_image.words[count_index] == 4u,
        "the divisor the body divided by is unchanged");
  check(g_bucket_table_image.words[table_index - 1] == 0x11111111u);
  check(g_bucket_table_image.words[count_index + 1] == 0x22222222u);
  check(g_bucket_table_image.words[count_index + 2] == 0x33333333u);
  for (std::size_t i = 0; i < kImageWords; ++i) {
    const bool is_dirty =
        (i == table_index - 1u) || (i == count_index + 1u) ||
        (i == count_index + 2u) || (i == table_index) || (i == count_index);
    if (is_dirty) {
      continue;
    }
    check(g_bucket_table_image.words[i] == kGuardCanary,
          "every untouched word of the image keeps the canary");
  }

  // The bucket array itself is not written either: the body's insert hands the
  // key to 0x00de5df0 and does not splice a node in itself.
  check(g_bucket_slots[bucket] == 0u, "the entry did not link the key in itself");
  check(node_word(g_bucket_slots_b[bucket], kNodeKeyDisplacement) ==
            (key ^ 0x5a5a5a5au),
        "and did not touch the decoy node it read");
}

// Direction B, the mutation test: every known-wrong body must be rejected. A
// mutant that SURVIVES means the battery has lost its power to tell a correct
// body from a wrong one, so the run fails even though the reconstruction itself
// passed every case above.
//
// Each mutant is driven in a FORKED CHILD, and the reason is mechanical rather
// than decorative. Several of these bodies are wrong in a way that faults
// instead of answering -- reading the array pointer out of the divisor's slot
// dereferences a table address that is really a small integer, and following
// the chain through the key word jumps to whatever the key happens to be. A
// battery that ran them in one process would stop at the first of those and
// never learn whether the other fourteen were caught, so a single crash would
// silently certify the rest. Forking makes each mutant's outcome independent:
//
//   * child exits 0    -> the mutant agreed with the reconstruction on every
//                        scene. That is a HOLE, and the parent fails the run.
//   * child exits 1    -> the battery rejected it cleanly.
//   * child killed by a signal -> it faulted. A body that faults has still
//                        failed to behave like the reconstruction, so it counts
//                        as refuted; the parent prints which signal, so the two
//                        kinds of refutation stay distinguishable.
void test_every_mutant_is_refuted() {
  for (std::size_t index = 0; index < kMutantCount; ++index) {
    std::fflush(nullptr);
    const pid_t pid = fork();
    if (pid < 0) {
      check(false, "fork() failed; the mutation test cannot judge the mutants");
    }
    if (pid == 0) {
      const bool survived = probe_agrees_on_every_scene(kMutants[index].entry);
      std::fprintf(stderr, "  [mutant %2zu/%2zu] %-38s %s\n", index + 1u,
                   kMutantCount, kMutants[index].name,
                   survived ? "SURVIVED -- HOLE IN THE TEST" : "refuted");
      std::fflush(nullptr);
      std::_Exit(survived ? 0 : 1);
    }
    int status = 0;
    if (waitpid(pid, &status, 0) != pid) {
      check(false, "waitpid() failed; the mutation test cannot judge the mutants");
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
      std::fprintf(stderr,
                   "0x00c77bf0: mutant '%s' SURVIVED the battery\n",
                   kMutants[index].name);
      check(false, "a known-wrong body was not refuted");
    }
    if (WIFSIGNALED(status)) {
      std::fprintf(stderr, "  [mutant %2zu/%2zu] %-38s refuted (faulted: %s)\n",
                   index + 1u, kMutantCount, kMutants[index].name,
                   strsignal(WTERMSIG(status)));
    }
  }
}

}  // namespace

int main() {
  test_the_whole_battery_over_every_scene();
  test_index_is_the_remainder_not_the_quotient_or_a_mask();
  test_the_two_receiver_words_are_not_swapped_or_shifted();
  test_walks_the_chain_to_its_end_following_the_link_word();
  test_inserts_exactly_once_on_a_miss_and_never_on_a_hit();
  test_the_value_slot_carries_the_key();
  test_third_argument_is_the_key_with_its_low_byte_cleared();
  test_the_two_pointers_are_the_two_adjacent_locals();
  test_stack_effect_is_pinned_by_the_bytes_and_the_prototype();
  test_machine_facts();
  test_writes_nothing_into_the_receiver();
  test_every_mutant_is_refuted();
  return 0;
}
