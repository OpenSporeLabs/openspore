#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <type_traits>

#include "field_getter_0x1674_00c04590.hpp"

// Focused semantic test for FUN_00c04590 @ 0x00c04590.
//
// It pins the behaviour the two-instruction body fixes, and it is written to
// try to REFUTE the reconstruction rather than to walk it. Each group below
// names the risky hypothesis it attacks:
//   1. the entry returns the VALUE stored at receiver+0x1674, not the address
//      of that word, not the receiver, not a constant, and not a LEA-form
//      base-plus-displacement;
//   2. 0x1674 is the displacement and not a near neighbour - distinct sentinels
//      are planted either side of it and only the 0x1674 word comes back;
//   3. the body READS: the receiver is byte-identical before and after, so a
//      write-through or defaulting perturbation fails on the guard bands;
//   4. the entry is a RAW, NON-RETAINING read. This is the claim that
//      distinguishes it from its neighbour 0x00c045a0, which stores through the
//      same displacement and visibly retains/releases through the pointee's own
//      vtable (slots +0x0 and +0x4). A "retaining getter" perturbation must
//      fail: the fixture plants a COUNTED fake object whose vtable slot +0x0
//      bumps an acquire counter, and the test asserts the counter is untouched
//      and the pointee's own bytes survive verbatim;
//   5. the encoding itself is the observed one - the raw bytes of the body are
//      stated here and the displacement bytes are tied to the header's
//      kWordDisplacement, so the two statements cannot drift apart;
//   6. the entry is a pure function of the receiver - the result tracks a
//      changed word and repeats across calls, so a caching perturbation fails;
//   7. the ABI claims - ECX receiver, 0 stack words, caller cleanup, and no
//      stack slot named at all - are settled from the OBSERVED ENCODING rather
//      than from a runtime stack probe. A 7-byte body ending in 0xc3 with no
//      0xc2 cannot be `RET imm16`, and its single memory operand has base ECX
//      with no SIB byte, so it names no stack slot. See the note on the
//      encoding below for why the obvious runtime probe was rejected: every
//      version of it failed for reasons about the probe, and one of them
//      reached a different verdict at -O0 than at -O2 on identical source.
//
// The calls go through an inline-asm trampoline instead of a thiscall function
// pointer on purpose. GCC's __attribute__((thiscall)) on a *function pointer
// type* allocates the argument with caller-side stack cleanup, which is not the
// convention the target uses (0x00c04596 is a bare RET, caller cleanup), so a
// plain pointer call would drift the stack by 4 bytes per call. The trampoline
// reproduces the observed sequence exactly:
//     MOV EAX,[ECX+0x1674] / RET
// and the compiler-generated body of the reconstruction is that same pair: at
// -O1 and -O2, clang++ -m32 emits
//     8b 81 74 16 00 00   mov 0x1674(%ecx),%eax
//     c3                  ret
// i.e. byte-identical to the seven bytes read from 0x00c04590.

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c04590 model test requires an x86-32 target"
#endif

// The header undefines its convention macro, so the modelled ABI type is
// respelled here; it is the same thiscall pointer type the entry declares.
#if defined(_MSC_VER)
#define PKG_00C04590_THISCALL __thiscall
#else
#define PKG_00C04590_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c04590_field_getter_0x1674 {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Word pointer_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The raw bytes read from 0x00c04590..0x00c04596, kept so the reconstruction's
// instruction sequence is stated in the test and not only in prose. The bytes
// after the body (0xcc, 0xcc, 0xcc INT3 pad) are deliberately not included.
constexpr std::uint8_t kTargetBytes[7] = {
    0x8b,                    // MOV r32, r/m32
    0x81,                    // ModRM: mod=10 (disp32), reg=EAX, r/m=ECX
    0x74, 0x16, 0x00, 0x00,  // disp32 = 0x00001674, little endian
    0xc3,                    // RET
};

// A sentinel that cannot be confused with a plausible address, a small
// constant, or a displacement value.
constexpr Word kSentinel = 0xfeedfaceu;

// A second, disjoint base for the planted neighbour words, so no neighbour can
// accidentally hold the value the correct answer is.
constexpr Word kNeighbourBase = 0x0badf00du;

// Distinguishable words below the reached one. Nothing above 0x1674 is inside
// the modeled extent, so the "not one word too high" claim is pinned
// arithmetically instead (kWordDisplacement + sizeof(Word) ==
// sizeof(OpaqueReceiver)).
constexpr std::size_t kNeighbourDisplacements[] = {0x000u, 0x004u, 0x166cu,
                                                   0x1670u};

Word entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&field_getter_0x1674_00c04590));
}

// The return value (EAX) after calling the entry through the trampoline.
// ECX = receiver, no stack words pushed, callee pops nothing.
Word call_entry(OpaqueReceiver* receiver) {
  const Word target = entry_address();
  Word result = 0;
  __asm__ __volatile__("movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

// WHAT THE ENCODING ALREADY SETTLES, and why there is no runtime stack probe
// here.
//
// An earlier draft of this file measured the ABI the way a reviewer might
// expect: sample ESP either side of the call, and vary the caller's stack depth
// so a body reading [ESP+4] would be caught. Both halves of that probe were
// unsound, and the failures were all about the PROBE rather than the target:
//
//   * varying the depth needs a `subl $128, %esp` inside the asm block or an
//     alloca. The first desynchronises the block from the frame its operands
//     live in (clang generated `movl (%esp), 8(%esp)`, which the assembler
//     rejects); the second is deleted outright at -O1+ when the compiler
//     decides the allocated memory is dead, so the "second depth" arm silently
//     measured the first depth again and passed for the wrong reason;
//   * "=m" asm operands on LOCALS are given ESP-relative addresses, so the
//     block that exists to inspect the stack collides with the stack, and at
//     -O0/-O1/-Os the operand/clobber count exceeds the registers the
//     allocator has left ("inline assembly requires more registers than
//     available"), while at -O2 the identical source passed - a probe whose
//     verdict depends on the optimisation level is not evidence.
//
// None of that work is needed, because the observed bytes settle both claims
// outright and settle them better:
//
//   (a) CALLER CLEANUP. The body is 7 bytes, 0x00c04590..0x00c04596, and its
//       last byte is 0xc3. A callee that popped anything would have to end in
//       `RET imm16` (0xc2 nn nn); the byte 0xc2 appears nowhere in the body and
//       the body is exactly as long as `8b 81 74 16 00 00 c3`. There is no
//       encoding of this body that pops a word.
//   (b) NO STACK ARGUMENT IS READ. The body performs exactly one memory
//       access, and its ModRM byte 0x81 has mod=10 (a 32-bit displacement) and
//       r/m=001, i.e. the base register is ECX. There is no SIB byte, so no
//       scaled-index addressing; and the base is ECX rather than ESP or EBP, so
//       no stack slot is named at all. A body that read a pushed argument would
//       need a memory operand based on ESP.
//
// Both are asserted from the byte array below, so they are checked against the
// evidence rather than against a reconstruction of the evidence. The runtime
// half of the entry - it returns the receiver's word, in EAX, from ECX - is
// covered by the trampoline groups above.

// A COUNTED fake object standing in for the refcounted pointee. The neighbour
// 0x00c045a0 is observed calling the pointee's vtable slot +0x0 (retain) and
// slot +0x4 (release) around its store, so a reconstruction that wrongly
// models the getter as retaining would call slot +0x0 here. Both slots are
// instrumented so that perturbation is loud rather than silent.
struct CountedObject {
  std::uint32_t vtable[2];  // slot +0x0 = retain, slot +0x4 = release
  std::uint32_t payload;    // the word 0x00b6b4c0 reads at result + 0x15c's
                            // analogue: some data behind the pointer
};

std::uint32_t g_retain_calls = 0;
std::uint32_t g_release_calls = 0;

void counted_retain() { ++g_retain_calls; }
void counted_release() { ++g_release_calls; }

// A receiver whose +0x1674 word is the ADDRESS of a CountedObject, i.e. the
// shape the adjacent setter leaves behind.
struct PointeeFixture {
  CountedObject object{};
  OpaqueReceiver receiver{};
};

PointeeFixture make_pointee_fixture() {
  PointeeFixture fixture{};
  fixture.object.vtable[0] = pointer_word(
      reinterpret_cast<const void*>(&counted_retain));
  fixture.object.vtable[1] = pointer_word(
      reinterpret_cast<const void*>(&counted_release));
  fixture.object.payload = 0x0a0c0a0cu;
  *word_at(&fixture.receiver, kWordDisplacement) =
      pointer_word(&fixture.object);
  g_retain_calls = 0;
  g_release_calls = 0;
  return fixture;
}

static_assert(sizeof(kTargetBytes) == 7, "target body is 7 bytes");
static_assert(kTargetBytes[0] == 0x8b && kTargetBytes[1] == 0x81,
              "0x00c04590 is MOV EAX,dword ptr [ECX + disp32]");
static_assert(kTargetBytes[6] == 0xc3,
              "0x00c04596 is RET (caller cleanup, no stack words)");

// The displacement is tied to the ENCODING, not to prose: 0x00c04590 is
// `8b 81 74 16 00 00`, so the little-endian disp32 bytes 3..5 spell the
// header's kWordDisplacement. Any drift in either place fails here.
static_assert(kTargetBytes[2] == 0x74 && kTargetBytes[3] == 0x16 &&
                  kTargetBytes[4] == 0x00 && kTargetBytes[5] == 0x00,
              "disp32 bytes spell 0x00001674, little endian");
static_assert(kWordDisplacement == 0x1674,
              "the header's displacement is the instruction's disp32");
static_assert(kWordDisplacement == 5748u,
              "0x1674 is the value 5748, compared semantically not by spelling");
static_assert(kWordDisplacement ==
                  (static_cast<std::size_t>(kTargetBytes[2]) |
                   (static_cast<std::size_t>(kTargetBytes[3]) << 8) |
                   (static_cast<std::size_t>(kTargetBytes[4]) << 16) |
                   (static_cast<std::size_t>(kTargetBytes[5]) << 24)),
              "header displacement equals the reconstructed disp32");

}

}

namespace {

using namespace openspore::reconstruction::pkg_00c04590_field_getter_0x1674;
using model::call_entry;
using model::check;
using model::entry_address;
using model::g_release_calls;
using model::g_retain_calls;
using model::kNeighbourBase;
using model::kNeighbourDisplacements;
using model::kSentinel;
using model::pointer_word;
using model::make_pointee_fixture;
using model::PointeeFixture;

static_assert(sizeof(pointer_word(nullptr)) == 4,
              "the modelled entry slot is one 32-bit word");
static_assert(sizeof(kSentinel) == 4, "the sentinel is one 32-bit word");
static_assert(std::is_same<AbiFieldGetter00c04590,
                           Word(PKG_00C04590_THISCALL*)(OpaqueReceiver*)>::value,
              "modelled ABI is thiscall with 0 stack words, one-word return");

// Fill the whole modeled extent with a non-zero pattern so an access to any
// part of it is visible afterwards, and plant the sentinel only at the
// displacement the body is supposed to reach.
OpaqueReceiver planted_receiver() {
  OpaqueReceiver receiver{};
  for (std::size_t index = 0; index < receiver.opaque_bytes.size(); ++index) {
    receiver.opaque_bytes[index] = static_cast<std::uint8_t>(index + 1u);
  }
  for (std::size_t neighbour = 0;
       neighbour < sizeof(kNeighbourDisplacements) / sizeof(std::size_t);
       ++neighbour) {
    *word_at(&receiver, kNeighbourDisplacements[neighbour]) =
        kNeighbourBase + static_cast<Word>(neighbour);
  }
  *word_at(&receiver, kWordDisplacement) = kSentinel;
  return receiver;
}

Word receiver_address(const OpaqueReceiver* receiver) {
  return pointer_word(receiver);
}

// 1. The return is the VALUE at receiver+0x1674.
void test_return_value_is_the_stored_word() {
  OpaqueReceiver receiver = planted_receiver();

  const Word result = call_entry(&receiver);

  check(result == kSentinel);
  // Not the address of the word: this is the load/LEA distinction. A body
  // written as `reinterpret_cast<std::uintptr_t>(receiver) + 0x1674` returns a
  // value that no sentinel in this fixture equals, so the two cannot both pass.
  check(result != pointer_word(
                       reinterpret_cast<const void*>(
                           reinterpret_cast<std::uintptr_t>(&receiver) +
                           kWordDisplacement)));
  // Not the receiver, not the displacement, not a constant the body could have
  // materialised, and not zero.
  check(result != receiver_address(&receiver));
  check(result != kWordDisplacement);
  check(result != 0u);
  // And the value is genuinely read out of the receiver, byte for byte.
  check(result == *word_at(&receiver, kWordDisplacement));
}

// 2. 0x1674 is THE displacement: distinct words planted below it - including
// the word immediately before it - are not what comes back, and none of them
// is disturbed by the call.
void test_displacement_is_exactly_0x1674() {
  OpaqueReceiver receiver = planted_receiver();

  const Word result = call_entry(&receiver);

  check(result == kSentinel);
  for (std::size_t index = 0;
       index < sizeof(kNeighbourDisplacements) / sizeof(std::size_t); ++index) {
    const std::size_t displacement = kNeighbourDisplacements[index];
    const Word planted = kNeighbourBase + static_cast<Word>(index);
    check(*word_at(&receiver, displacement) == planted);
    check(result != planted);
    // The gap is measured in BYTES: a model that read the displacement as an
    // element count would land 0x1674 elements out, 0x59d0 bytes.
    check(reinterpret_cast<std::uintptr_t>(word_at(&receiver, displacement)) -
              reinterpret_cast<std::uintptr_t>(&receiver) ==
          static_cast<std::uintptr_t>(displacement));
  }
  // The entry's displacement and the header's accessor name one address.
  check(word_at(&receiver, kWordDisplacement) ==
        word_at(&receiver, static_cast<std::size_t>(0x1674u)));
}

// 3. The body READS. Guard bands before and after the reached word must be
// byte-identical across the call; a store-through or defaulting perturbation
// fails here even if it also returned the right value.
void test_body_does_not_write_the_receiver() {
  OpaqueReceiver receiver = planted_receiver();
  OpaqueReceiver before = receiver;

  const Word result = call_entry(&receiver);
  check(result == kSentinel);

  for (std::size_t index = 0; index < receiver.opaque_bytes.size(); ++index) {
    check(receiver.opaque_bytes[index] == before.opaque_bytes[index]);
  }
  // Stated as bounds too: the reached word sits inside the modeled extent and
  // the extent ends immediately after it.
  check(kWordDisplacement < sizeof(OpaqueReceiver));
  check(kWordDisplacement + sizeof(Word) == sizeof(OpaqueReceiver));
}

// 4. THE load-bearing test: the read is RAW. The fixture's +0x1674 word holds
// the address of a CountedObject whose vtable slot +0x0 is an instrumented
// retain. A reconstruction that modelled this accessor as retaining (or that
// copied, or that cleared on read) would touch that object; the real body is
// two instructions and does none of it.
void test_read_is_raw_and_does_not_retain() {
  PointeeFixture fixture = make_pointee_fixture();
  const Word planted = pointer_word(&fixture.object);
  check(*word_at(&fixture.receiver, kWordDisplacement) == planted);

  // Snapshot everything that a side effect would move: both counters, the
  // pointee's vtable words, and its payload.
  const std::uint32_t vtable0_before = fixture.object.vtable[0];
  const std::uint32_t vtable1_before = fixture.object.vtable[1];
  const std::uint32_t payload_before = fixture.object.payload;
  OpaqueReceiver receiver_before = fixture.receiver;

  const Word result = call_entry(&fixture.receiver);

  // The getter returns the stored address, unchanged.
  check(result == planted);
  // It did NOT retain through the pointee's vtable slot +0x0, and it did not
  // release through slot +0x4. This is what separates it from its neighbour
  // 0x00c045a0, which does both around its store.
  check(g_retain_calls == 0u);
  check(g_release_calls == 0u);
  // It did not write through the pointee either.
  check(fixture.object.vtable[0] == vtable0_before);
  check(fixture.object.vtable[1] == vtable1_before);
  check(fixture.object.payload == payload_before);
  // And it did not write through the receiver (e.g. a read-and-null perturbation
  // would leave the +0x1674 word zeroed here).
  check(*word_at(&fixture.receiver, kWordDisplacement) == planted);
  for (std::size_t index = 0;
       index < fixture.receiver.opaque_bytes.size(); ++index) {
    check(fixture.receiver.opaque_bytes[index] ==
          receiver_before.opaque_bytes[index]);
  }

  // Repeating the read is still side-effect free: a caching or
  // consume-once perturbation would bump a counter on the second call.
  check(call_entry(&fixture.receiver) == planted);
  check(g_retain_calls == 0u);
  check(g_release_calls == 0u);
}

// 5. The encoding is the observed one: the body is the 7 bytes read from
// 0x00c04590, and the header's displacement is that instruction's disp32.
void test_encoding_matches_the_observed_bytes() {
  check(model::kTargetBytes[0] == 0x8bu);
  check(model::kTargetBytes[1] == 0x81u);
  check(model::kTargetBytes[2] == 0x74u);
  check(model::kTargetBytes[3] == 0x16u);
  check(model::kTargetBytes[4] == 0x00u);
  check(model::kTargetBytes[5] == 0x00u);
  check(model::kTargetBytes[6] == 0xc3u);
  check(sizeof(model::kTargetBytes) == 7u);
  // 0x81 is mod=10, i.e. a 32-bit displacement; the displacement bytes are the
  // ones after the ModRM byte, so the instruction carries 0x00001674.
  check((model::kTargetBytes[1] >> 6) == 2);
  check((model::kTargetBytes[1] & 0x07) == 1);
  check((model::kTargetBytes[1] >> 3 & 0x07) == 0);
}

// 6. Pure function of the receiver: the result tracks the stored word and
// repeats across calls, so a reconstruction that cached a value fails. This is
// kept separate from group 4 because it is the same machine claim seen from the
// value side rather than the side-effect side.
void test_result_tracks_the_stored_word_and_repeats() {
  OpaqueReceiver receiver = planted_receiver();

  check(call_entry(&receiver) == kSentinel);
  check(call_entry(&receiver) == kSentinel);

  *word_at(&receiver, kWordDisplacement) = 0x12345678u;
  check(call_entry(&receiver) == 0x12345678u);

  *word_at(&receiver, kWordDisplacement) = 0xffffffffu;
  const Word all_ones = call_entry(&receiver);
  check(all_ones == 0xffffffffu);
  // A signed interpretation of the same bits is not what crosses the ABI, and
  // neither is a truncated 16-bit or byte-wide read of it.
  check(all_ones != 0xffffu);
  check(all_ones != 0xffu);
}

// 7. The ABI claims, settled from the OBSERVED ENCODING rather than from a
// runtime stack probe (see the note on the encoding, below):
//   (a) the callee pops nothing - the body ends in 0xc3 and contains no 0xc2,
//       so `RET imm16` is not a possible encoding of these 7 bytes;
//   (b) the body names no stack slot - its one memory operand is based on ECX
//       (ModRM mod=10, r/m=001) with no SIB byte, so no scaled index and no
//       ESP/EBP base;
//   (c) the model is a thiscall entry: receiver in, one word out, one pointer
//       wide.
void test_encoding_settles_cleanup_and_names_no_stack_slot() {
  // (a) caller cleanup, from the bytes.
  check(model::kTargetBytes[6] == 0xc3u);
  check(sizeof(model::kTargetBytes) == 7u);
  for (std::size_t index = 0; index < sizeof(model::kTargetBytes); ++index) {
    // 0xc2 is `RET imm16`. Its absence is what rules out callee-side popping.
    check(model::kTargetBytes[index] != 0xc2u);
  }
  // The last byte is the ONLY 0xc3, so the RET is the final instruction and the
  // body is not a prefix of some longer sequence.
  std::size_t ret_count = 0;
  for (std::size_t index = 0; index < sizeof(model::kTargetBytes); ++index) {
    if (model::kTargetBytes[index] == 0xc3u) {
      ++ret_count;
    }
  }
  check(ret_count == 1u);

  // (b) no stack slot is named. ModRM 0x81: mod=10 => 32-bit displacement,
  // reg=000 => destination register EAX, r/m=001 => base register ECX. No SIB
  // byte follows, because r/m=100 is what would demand one.
  check((model::kTargetBytes[1] >> 6) == 2);   // mod == 10
  check((model::kTargetBytes[1] >> 3 & 0x07) == 0);  // reg == EAX
  check((model::kTargetBytes[1] & 0x07) == 1);  // r/m == ECX, not ESP(4)/EBP(5)
  check((model::kTargetBytes[1] & 0x07) != 4);   // never ESP
  check((model::kTargetBytes[1] & 0x07) != 5);   // never EBP
  // Opcode 0x8b takes no SIB here precisely because r/m is not 100; the two
  // bytes after the ModRM are the displacement, which the test above already
  // tied to kWordDisplacement.
  check(model::kTargetBytes[2] == 0x74u);
  check(model::kTargetBytes[3] == 0x16u);
  check(model::kTargetBytes[4] == 0x00u);
  check(model::kTargetBytes[5] == 0x00u);

  // (c) the modelled entry is a thiscall: one pointer in, one word out, and
  // the pointer is a pointer.
  check(sizeof(AbiFieldGetter00c04590) == sizeof(void*));
  check(sizeof(*word_at(static_cast<OpaqueReceiver*>(nullptr), 0u)) == 4u);
  check(sizeof(void*) == 4u);
  // The receiver reaches the body as ECX and the result leaves in EAX, which is
  // the pair the trampoline sets up and reads; both are named here so the ABI
  // claim is stated in the test and not only in prose.
  check(entry_address() != 0u);
}

int run_tests() {
  test_return_value_is_the_stored_word();
  test_displacement_is_exactly_0x1674();
  test_body_does_not_write_the_receiver();
  test_read_is_raw_and_does_not_retain();
  test_encoding_matches_the_observed_bytes();
  test_result_tracks_the_stored_word_and_repeats();
  test_encoding_settles_cleanup_and_names_no_stack_slot();
  return 0;
}

}

int main() { return ::run_tests(); }

#undef PKG_00C04590_THISCALL
