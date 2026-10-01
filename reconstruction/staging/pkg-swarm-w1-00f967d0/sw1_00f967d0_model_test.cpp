// PKG-SWARM-W1-00F967D0 -- VA 0x00f967d0
// Behavioural model test for FUN_00f967d0 @ 0x00f967d0.
//
// All three direct callees -- 0x0097ef00, 0x00fb7bb0 and 0x00fb7bc0 -- are
// defined here as observers, so the test sees every transfer the reconstruction
// makes, with which receiver, in which order, and gets to decide what each of them
// returns and what it does to memory.
//
// What is asserted is what the 27-instruction listing fixes, and nothing more:
//
//   * three transfers, once each, in the order 0x0097ef00, 0x00fb7bb0, 0x00fb7bc0;
//   * all three receivers are the SAME object, the word the receiver holds at
//     displacement 0x20c -- and the word is re-loaded before each of them rather
//     than cached;
//   * the three stores through the three out-pointers happen in the order
//     scaled, then +0x5c0, then +0x5c4, each AFTER its own call and each BEFORE
//     the next pointer re-load;
//   * the receiver is never written: the whole arena, plus a sentinel tail, is
//     bit-identical after a call;
//   * the multiplier is the WORD at 0x0140f334, read as memory, not a literal --
//     and the model's word carries the image's own bytes, 00 00 80 42;
//   * the scaling is floor of the product, and NOT truncation, NOT round-to-nearest
//     and NOT a clamp, driven with signed inputs where those four disagree;
//   * the exact x86 conversion edge results: NaN, both infinities, both signs of
//     out-of-range magnitude, the 2^31 boundary and the largest in-range float;
//   * all three callees are entered at the same stack depth, so the body pushes
//     nothing for any of them;
//   * the three argument words are popped by the CALLEE, measured by sampling ESP
//     in a trampoline rather than asserted as a convention.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names the wrong reconstruction it is aimed at:
//
//   C  wrong constant: the multiplier is 64.0f, not 1.0f, 32.0f, 100.0f or
//      0.5f, and it is the word at 0x0140f334 rather than a literal -- planting
//      four different values moves the result each time;
//   D  the neighbouring FLOATS are not the operand: a word at the receiver's +0x08
//      and words at the pointee's +0x00, +0x04 and +0x0c are all poisoned and none
//      of them reaches the result (wrong pointer level, wrong sub-displacement);
//   E  wrong receiver displacement: full decoy pointees at receiver+0x00,
//      +0x204, +0x208 and +0x210, and only the one at +0x20c is ever handed to a
//      callee;
//   F  wrong pointee sub-displacements: distinct words at the pointee's +0x5b8,
//      +0x5bc, +0x5c0, +0x5c4 and +0x5c8, and the two out words come from
//      +0x5c0 and +0x5c4 in that order and not swapped and not from a neighbour;
//   G  wrong rounding: floor, driven against truncate, ceil, round-to-nearest-even
//      and clamp with the specific inputs where each disagrees;
//   H  the x87 conversion edges: NaN -> 0x7fffffff, +infinity -> 0x80000000,
//      negative out-of-range -> 0x7fffffff, positive out-of-range ->
//      0x80000000, -2^31 -> 0x80000000 and 2^31-128 -> 0x7fffff80. A std::floor
//      model, a saturating model and a clamping model all get at least one of
//      these wrong;
//   J  wrong write ordering: the out buffers are sampled by the callees at the
//      moment of each call, which pins the store order and pins that each store
//      follows its own call;
//   K  a cached pointee: the first callee rewrites the receiver's +0x20c, and the
//      second and third calls must see the NEW object while the scaled out word
//      must still carry the OLD object's float. A model that kept the pointer in a
//      local fails on the two word outputs;
//   L  wrong callee pairing: the second out word comes from 0x00fb7bb0's return
//      (+0x5c0) and the third from 0x00fb7bc0's (+0x5c4), checked with the two
//      words distinct and each observer forced to return its own offset's value;
//   M  aliased out-pointers: all three arguments are the same cell, and the trace
//      of that cell at each call pins the store order a second way;
//   N  the ABI: twelve argument bytes, callee-cleaned, measured.
//
// What is NOT asserted, and why:
//
//   * EAX at the terminator, and ST0. The listing shows no outgoing value on any
//     path -- the x87 stack is empty from 0x00f967e8 on -- so the declared return
//     type is void and there is no register state here to test. The
//     machine-derived ABI record disagrees (it reports ST0 as the return register,
//     which is a reading of the FMUL/FSTP pair, not of this function's result);
//     that disagreement is recorded in the sidecar and nothing is asserted from it.
//   * Whether the body pushes stack arguments for the three callees. The listing's
//     own proof is the absence of any PUSH between a CALL and the instruction after
//     it, plus the three callees' bare `C3` terminators; the reconstruction's
//     extern declarations carry no stack parameter, so a pushed word would be
//     ignored rather than observed. The test therefore asserts only the weaker,
//     measurable fact: all three observers run at the same stack depth.
//   * The class that owns vtable 0x01490be8, of which this body is slot 30. No
//     record available for this VA names it, so the receiver is an opaque run and
//     no dispatch slot is modelled. Nothing in this test depends on a class name.
//   * What the three out words MEAN. The listing fixes where each comes from and
//     nothing fixes what any of them is for, so no expected value is derived from
//     a name.
//   * The pointer reload is asserted only in the direction the listing fixes: the
//     machine re-reads the word three times, so a change made between the calls is
//     visible. It is NOT asserted that a conforming C++ compiler must re-read it;
//     it is asserted that this reconstruction does, and the case is labelled as
//     refuting a cached-pointer model rather than as a portability claim.
//
// Two machine details are modelled but deliberately NOT claimed as testable, because
// on this host they are indistinguishable from the alternative and a test for them
// would be a test of the compiler, not of the reconstruction:
//
//   * the strict upper bound in the CVTSS2SI range test. The hardware rule is
//     [-2^31, 2^31) -- 2^31 itself is out of range and 2^31-128 is not -- and the
//     model writes it that way. But 2^31 is the ONLY float in that gap, and both
//     `<` and `<=` there yield the same 0x80000000 on this host, so H6 cannot tell
//     them apart. The listing is the authority for the bound; H6 is a check of the
//     stored value only.
//   * the FSTP at 0x00f967e7, which is what rounds the product to a single. For a
//     product of two float32 operands the exact result needs at most 48 bits, so a
//     double accumulator and a direct single multiply round identically and the
//     model's single `float` product is already equivalent. The FSTP is in the model
//     because the MOVSS at 0x00f967eb reads it back, not because a test can tell
//     that it happened.

#include "sw1_00f967d0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_00f967d0 {
namespace {

// The machine displacements, as literals. 0x20c is the receiver's only word; the
// three inside the pointee are the operands of the three callees, not of this body.
constexpr std::size_t kReceiverWordOffset = 0x20cu;
constexpr std::size_t kPointeeFloatOffset = 0x08u;
constexpr std::size_t kPointeeWord5c0Offset = 0x5c0u;
constexpr std::size_t kPointeeWord5c4Offset = 0x5c4u;

// 0x210 is the last byte the body can reach on the receiver (0x20c + 4). The arena
// is larger than that, and the extra bytes are a sentinel tail so a store past
// +0x20f would show up in the byte comparison instead of being invisible.
constexpr std::size_t kReceiverBytes = 0x210u;
constexpr std::size_t kArenaBytes = kReceiverBytes + 0x20u;

// Large enough to hold the receiver AND a second full decoy pointee inside it, so
// the "wrong receiver displacement" decoys at +0x204 and +0x208 are real objects
// with real contents rather than a pointer to somewhere else.
constexpr std::size_t kBigArenaBytes = 0x1000u;

// A union rather than a cast, so the aliased-out-pointer case reads back what it
// wrote through a different member without a strict-aliasing hole.
union SharedCell {
  std::int32_t as_signed;
  Word as_word;
  std::uint8_t bytes[4];
};

enum Call : int {
  kCallGetFloat = 0,
  kCallGetWord5c0 = 1,
  kCallGetWord5c4 = 2,
  kCallCount = 3,
};

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// The machine's own conversion results, written out by hand from the instruction
// rules rather than computed by a helper, so the expectations are independent of
// the model they check. All three are reachable in one case.
constexpr std::int32_t kIndefinite = static_cast<std::int32_t>(0x80000000u);  // 0x80000000
constexpr std::int32_t kIndefiniteMinusOne = 0x7fffffff;

struct Observation {
  int log[kCallCount] = {};
  int log_length = 0;

  int float_calls = 0;
  int word5c0_calls = 0;
  int word5c4_calls = 0;

  OpaquePointee* float_receiver = nullptr;
  OpaquePointee* word5c0_receiver = nullptr;
  OpaquePointee* word5c4_receiver = nullptr;

  // The pointee's +0x08 as the observer found it, by bit pattern, so the test can
  // prove the value came from that exact word.
  Word float_field08_bits = 0;

  // The out buffers as they were at the moment of each call. Sampled by the
  // callees, so the store order and the store-after-call property are observable.
  const std::int32_t* watched_scaled = nullptr;
  const Word* watched_5c0 = nullptr;
  const Word* watched_5c4 = nullptr;
  std::int32_t seen_scaled[kCallCount] = {};
  Word seen_5c0[kCallCount] = {};
  Word seen_5c4[kCallCount] = {};
  bool seen_valid[kCallCount] = {};

  // When set, the FIRST callee overwrites the receiver's word at +0x20c with this
  // pointer before returning. That is how the test refutes a cached pointee.
  OpaquePointee* swap_receiver_word_to = nullptr;
  OpaqueReceiver* swap_receiver_word_in = nullptr;

  void reset() { *this = Observation(); }

  void record(Call call) {
    if (log_length < kCallCount) {
      log[log_length] = static_cast<int>(call);
    }
    ++log_length;
  }

  void sample_watchers(Call call) {
    const int index = static_cast<int>(call);
    if (watched_scaled != nullptr) {
      seen_scaled[index] = *watched_scaled;
    }
    if (watched_5c0 != nullptr) {
      seen_5c0[index] = *watched_5c0;
    }
    if (watched_5c4 != nullptr) {
      seen_5c4[index] = *watched_5c4;
    }
    seen_valid[index] = true;
  }

  bool log_is(Call a, Call b, Call c) const {
    return log_length == 3 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b) &&
           log[2] == static_cast<int>(c);
  }
};

Observation g_obs;

// Byte-level plant/peek, so a decoy can be placed at any displacement inside a run
// the type models as opaque.
template <typename T>
void plant(void* base, std::size_t displacement, T value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + displacement, &value, sizeof value);
}

template <typename T>
T peek(const void* base, std::size_t displacement) {
  T value = T();
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + displacement, sizeof value);
  return value;
}

OpaqueReceiver* receiver_of(std::uint8_t* arena) {
  return reinterpret_cast<OpaqueReceiver*>(arena);
}

Word bits_of(float value) {
  Word bits = 0;
  std::memcpy(&bits, &value, sizeof bits);
  return bits;
}

float float_of(Word bits) {
  float value = 0.0f;
  std::memcpy(&value, &bits, sizeof value);
  return value;
}

float make_nan() { return float_of(0x7fc00000u); }
float make_positive_infinity() { return float_of(0x7f800000u); }
float make_negative_infinity() { return float_of(0xff800000u); }

// A pointee with its three real fields set and every neighbouring word poisoned, so
// a reconstruction that read the wrong depth or the wrong sub-displacement would
// pick up a value the test can name.
void poison_pointee_neighbours(OpaquePointee* pointee) {
  plant<float>(pointee, 0x00u, 3.0f);
  plant<float>(pointee, 0x04u, 5.0f);
  plant<float>(pointee, 0x0cu, 7.0f);
  plant<Word>(pointee, 0x5b8u, 0x11111111u);
  plant<Word>(pointee, 0x5bcu, 0x22222222u);
  plant<Word>(pointee, 0x5c8u, 0x33333333u);
}

}  // namespace

// 0x00f967dc -- CALL 0x0097ef00. The callee's own body is
// `FLD float ptr [ECX + 0x8]` / `RET`, so the observer reads the float at the
// POINTEE's +0x08 and returns it in ST0. It also samples the watched out buffers
// and, when the test asks for it, rewrites the receiver's word at +0x20c.
extern "C" float PKG_SW1_00F967D0_THISCALL record_get_float_0097ef00(
    OpaquePointee* self) {
  ++g_obs.float_calls;
  g_obs.record(kCallGetFloat);
  g_obs.float_receiver = self;
  g_obs.float_field08_bits = bits_of(peek<float>(self, kPointeeFloatOffset));
  g_obs.sample_watchers(kCallGetFloat);
  if (g_obs.swap_receiver_word_to != nullptr && g_obs.swap_receiver_word_in != nullptr) {
    plant<OpaquePointee*>(reinterpret_cast<std::uint8_t*>(g_obs.swap_receiver_word_in),
                          kReceiverWordOffset, g_obs.swap_receiver_word_to);
  }
  return peek<float>(self, kPointeeFloatOffset);
}

// 0x00f96810 -- CALL 0x00fb7bb0. The callee's own body is
// `MOV EAX,dword ptr [ECX + 0x5c0]` / `RET`: the word at the pointee's +0x5c0.
extern "C" Word PKG_SW1_00F967D0_THISCALL record_get_word_00fb7bb0(OpaquePointee* self) {
  ++g_obs.word5c0_calls;
  g_obs.record(kCallGetWord5c0);
  g_obs.word5c0_receiver = self;
  g_obs.sample_watchers(kCallGetWord5c0);
  return peek<Word>(self, kPointeeWord5c0Offset);
}

// 0x00f96821 -- CALL 0x00fb7bc0. The callee's own body is
// `MOV EAX,dword ptr [ECX + 0x5c4]` / `RET`: the word at the pointee's +0x5c4, ONE
// dword above the previous callee's, and it goes to the THIRD out parameter.
extern "C" Word PKG_SW1_00F967D0_THISCALL record_get_word_00fb7bc0(OpaquePointee* self) {
  ++g_obs.word5c4_calls;
  g_obs.record(kCallGetWord5c4);
  g_obs.word5c4_receiver = self;
  g_obs.sample_watchers(kCallGetWord5c4);
  return peek<Word>(self, kPointeeWord5c4Offset);
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00f967d0

namespace {

using namespace openspore::reconstruction::pkg_swarm_w1_00f967d0;

// A receiver arena with a sentinel tail, and a second arena big enough to hold a
// decoy pointee INSIDE it at a displacement one dword either side of 0x20c.
struct Arena {
  std::uint8_t bytes[kBigArenaBytes];
};

Arena make_arena() {
  Arena arena;
  std::memset(arena.bytes, 0, sizeof arena.bytes);
  return arena;
}

// Puts `pointee` where the receiver's word at +0x20c must name it, and poisons the
// receiver's own first float and its word at +0x00 so that a reconstruction reading
// the receiver instead of the pointee picks up something the test can name.
void install_pointee(Arena& arena, OpaquePointee* pointee) {
  plant<float>(arena.bytes, 0x08u, 9.0f);
  plant<OpaquePointee*>(arena.bytes, 0x00u, nullptr);
  plant<OpaquePointee*>(arena.bytes, kReceiverWordOffset, pointee);
}

int count_changed_bytes(const std::uint8_t* before, const std::uint8_t* after,
                        std::size_t length) {
  int changed = 0;
  for (std::size_t index = 0; index < length; ++index) {
    if (before[index] != after[index]) {
      ++changed;
    }
  }
  return changed;
}

// A point on the floor sequence, with the expected out word derived by hand from
// the four instructions 0x00f967f1, 0x00f967f5, 0x00f967fe and 0x00f96801.
struct ScalingPoint {
  float sampled;              // what 0x0097ef00 returns
  std::int32_t expected;      // what must land in the first out word
  const char* derivation;     // the arithmetic, written out
};

// The multiplier in force for the scaling table. 64.0f is the image's own word at
// 0x0140f334 and it is restored by the caller after the table runs.
constexpr float kImageScale = 64.0f;

void case_transfers_receivers_and_results() {
  static OpaquePointee pointee;
  std::memset(&pointee, 0, sizeof pointee);
  pointee.field_08 = 0.0390625f;  // * 64.0f = 2.5 exactly
  pointee.field_5c0 = 0xa1a1a1a1u;
  pointee.field_5c4 = 0xb2b2b2b2u;

  Arena arena = make_arena();
  install_pointee(arena, &pointee);

  std::int32_t out_scaled = static_cast<std::int32_t>(0x5a5a5a5au);
  Word out_5c0 = 0x6b6b6b6bu;
  Word out_5c4 = 0x7c7c7c7cu;

  g_obs.reset();
  g_obs.watched_scaled = &out_scaled;
  g_obs.watched_5c0 = &out_5c0;
  g_obs.watched_5c4 = &out_5c4;

  re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);

  check(g_obs.log_is(kCallGetFloat, kCallGetWord5c0, kCallGetWord5c4),
        "A1: the three transfers happen once each, in the listing's order");
  check(g_obs.float_calls == 1 && g_obs.word5c0_calls == 1 && g_obs.word5c4_calls == 1,
        "A2: each of the three callees is entered exactly once");
  check(g_obs.float_receiver == &pointee && g_obs.word5c0_receiver == &pointee &&
            g_obs.word5c4_receiver == &pointee,
        "A3: all three callees get the object the receiver holds at +0x20c");
  check(g_obs.float_field08_bits == bits_of(0.0390625f),
        "A4: the float callee read the pointee's own +0x08");
  check(out_scaled == 2, "A5: the scaled word is floor(2.5)");
  check(out_5c0 == 0xa1a1a1a1u, "A6: the second out word is the pointee's +0x5c0");
  check(out_5c4 == 0xb2b2b2b2u, "A7: the third out word is the pointee's +0x5c4");
  // Sampled by the reconstruction at its own three call sites, not inside the
  // callees, so the three values are comparable at any optimisation level.
  const std::uint32_t esp_0 = call_site_esp_00f967d0(0);
  const std::uint32_t esp_1 = call_site_esp_00f967d0(1);
  const std::uint32_t esp_2 = call_site_esp_00f967d0(2);
  check(esp_0 != 0u && esp_0 == esp_1 && esp_1 == esp_2,
        "A8: all three calls leave the same frame depth, so nothing is pushed for any");
  check(call_site_esp_00f967d0(3) == 0u && call_site_esp_00f967d0(-1) == 0u,
        "A9: the instrumentation reports 0 for an ordinal no call site has");
}

// REFUTE C -- wrong constant. The FMUL at 0x00f967e1 is a MEMORY operand on
// 0x0140f334, so the multiplier is a word the body reads, not a literal. Four
// substitutions that a wrong-constant reconstruction would have baked in, each of
// which gives a different answer from 64.0f for a sampled value of 1.0f.
void case_multiplier_is_the_word_at_0x0140f334() {
  static OpaquePointee pointee;
  std::memset(&pointee, 0, sizeof pointee);
  pointee.field_08 = 1.0f;
  // The neighbouring floats must not be reachable either.
  poison_pointee_neighbours(&pointee);

  struct Substitution {
    float scale;
    std::int32_t expected;
    const char* what;
  };
  const Substitution substitutions[] = {
      {1.0f, 1, "1.0f would give 1"},
      {0.5f, 0, "0.5f would give 0"},
      {32.0f, 32, "32.0f would give 32"},
      {100.0f, 100, "100.0f would give 100"},
  };

  for (std::size_t index = 0; index < sizeof substitutions / sizeof substitutions[0]; ++index) {
    Arena arena = make_arena();
    install_pointee(arena, &pointee);
    std::int32_t out_scaled = 0;
    Word out_5c0 = 0u;
    Word out_5c4 = 0u;

    g_obs.reset();
    scale_word_0140f334() = substitutions[index].scale;
    re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);
    scale_word_0140f334() = kImageScale;

    check(out_scaled == substitutions[index].expected, substitutions[index].what);
    // The poisoned neighbours are all far from any of the four answers, so a
    // reconstruction that read one of them instead of +0x08 cannot land here.
    check(out_scaled == 0 || out_scaled == 1 || out_scaled == 32 || out_scaled == 100,
          "C: the answer tracks the scale word and not a neighbouring float");
  }
  check(bits_of(kImageScale) == 0x42800000u,
        "C: the image's own bytes at 0x0140f334 are 00 00 80 42, which is 64.0f");
  check(bits_of(scale_word_0140f334()) == 0x42800000u,
        "C: the model's word was restored after the substitutions");
}

// REFUTE D -- wrong pointer level. The float comes from the pointee's +0x08 and the
// two words from the pointee's +0x5c0 and +0x5c4. The receiver's OWN +0x08 is
// poisoned to 9.0f and the pointee's neighbouring words to 3.0f, 5.0f and 7.0f, so
// reading one level too high, one level too low or one field across is all visible.
void case_two_level_dereference() {
  static OpaquePointee pointee;
  std::memset(&pointee, 0, sizeof pointee);
  pointee.field_08 = 0.25f;  // * 64.0f = 16.0 exactly
  pointee.field_5c0 = 0x44444444u;
  pointee.field_5c4 = 0x55555555u;
  poison_pointee_neighbours(&pointee);

  Arena arena = make_arena();
  install_pointee(arena, &pointee);
  check(peek<float>(arena.bytes, 0x08u) == 9.0f,
        "D0: the receiver's own +0x08 really is poisoned to a different float");

  std::int32_t out_scaled = 0;
  Word out_5c0 = 0u;
  Word out_5c4 = 0u;
  g_obs.reset();
  re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);

  check(out_scaled == 16,
        "D1: the float is the pointee's +0x08 (0.25 * 64 = 16), not the receiver's 9.0f "
        "(9 * 64 = 576) and not the pointee's +0x0c 7.0f (7 * 64 = 448)");
  check(out_5c0 == 0x44444444u, "D2: the second out word is the pointee's +0x5c0");
  check(out_5c4 == 0x55555555u, "D3: the third out word is the pointee's +0x5c4");
  check(out_5c0 != 0x22222222u && out_5c4 != 0x33333333u,
        "D4: neither word came from the +0x5bc or +0x5c8 decoys");
}

// REFUTE E -- wrong receiver displacement. Full decoy pointees at the receiver's
// +0x00, +0x204 and +0x208 (inside the receiver) and +0x210 (past its last byte),
// each with its own values. Only the object at +0x20c may be handed to a callee.
void case_receiver_displacement_is_0x20c() {
  static OpaquePointee real_pointee;
  static OpaquePointee at_204;
  static OpaquePointee at_208;
  static OpaquePointee beyond;
  static OpaquePointee at_zero;
  OpaquePointee* const decoys[] = {&real_pointee, &at_204, &at_208, &beyond, &at_zero};
  for (std::size_t index = 0; index < sizeof decoys / sizeof decoys[0]; ++index) {
    std::memset(decoys[index], 0, sizeof *decoys[index]);
    // Distinct values, so "the wrong pointee" is always visible in the output.
    decoys[index]->field_08 = 1.0f + static_cast<float>(index) * 2.0f;
    decoys[index]->field_5c0 = 0x1000u + static_cast<Word>(index);
    decoys[index]->field_5c4 = 0x2000u + static_cast<Word>(index);
  }
  // index 0 of that array is the real one, so its answers are floor(1.0 * 64) = 64,
  // 0x1000 and 0x2000; the four decoys sit one step above it in both word fields.
  real_pointee.field_08 = 1.0f;
  at_204.field_08 = 3.0f;
  at_208.field_08 = 5.0f;
  beyond.field_08 = 7.0f;
  at_zero.field_08 = 9.0f;

  Arena arena = make_arena();
  plant<OpaquePointee*>(arena.bytes, 0x00u, &at_zero);
  plant<OpaquePointee*>(arena.bytes, 0x204u, &at_204);
  // The decoy at +0x208 is the object ITSELF, occupying +0x208..+0x7cf of the arena.
  plant<OpaquePointee*>(arena.bytes, 0x208u, &at_208);
  plant<OpaquePointee*>(arena.bytes, 0x20cu, &real_pointee);
  plant<OpaquePointee*>(arena.bytes, 0x210u, &beyond);

  std::int32_t out_scaled = 0;
  Word out_5c0 = 0u;
  Word out_5c4 = 0u;
  g_obs.reset();
  re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);

  check(out_scaled == 64, "E1: the scaled word is floor(1.0 * 64), the +0x20c object's");
  check(g_obs.float_receiver == &real_pointee && g_obs.word5c0_receiver == &real_pointee &&
            g_obs.word5c4_receiver == &real_pointee,
        "E2: every callee got the object at +0x20c, not a neighbouring one");
  check(out_5c0 == 0x1000u, "E3: the second out word is the +0x20c object's +0x5c0");
  check(out_5c4 == 0x2000u, "E4: the third out word is the +0x20c object's +0x5c4");
  check(out_scaled != 192 && out_scaled != 320 && out_scaled != 448 && out_scaled != 576,
        "E5: none of the four decoy floats (3.0, 5.0, 7.0, 9.0) reached the result");
}

// REFUTE F -- the two word displacements are +0x5c0 and +0x5c4, in that order, and
// not swapped and not a neighbour. Distinct words are planted on both sides of each.
void case_pointee_word_displacements_and_order() {
  static OpaquePointee pointee;
  std::memset(&pointee, 0, sizeof pointee);
  pointee.field_08 = 0.0f;
  pointee.field_5c0 = 0x0c0c0c0cu;
  pointee.field_5c4 = 0x0d0d0d0du;
  poison_pointee_neighbours(&pointee);
  check(peek<Word>(&pointee, 0x5b8u) == 0x11111111u && peek<Word>(&pointee, 0x5bcu) == 0x22222222u &&
            peek<Word>(&pointee, 0x5c8u) == 0x33333333u,
        "F0: the three neighbouring words are poisoned on both sides");

  Arena arena = make_arena();
  install_pointee(arena, &pointee);
  std::int32_t out_scaled = 0;
  Word out_5c0 = 0u;
  Word out_5c4 = 0u;
  g_obs.reset();
  re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);

  check(out_5c0 == 0x0c0c0c0cu, "F1: out word 2 is the pointee's +0x5c0");
  check(out_5c4 == 0x0d0d0d0du, "F2: out word 3 is the pointee's +0x5c4");
  check(out_5c0 != 0x22222222u, "F3: out word 2 is not the +0x5bc decoy");
  check(out_5c4 != 0x33333333u, "F4: out word 3 is not the +0x5c8 decoy");
  check(out_5c0 != 0x0d0d0d0du && out_5c4 != 0x0c0c0c0cu,
        "F5: the two out words are not swapped with each other");
  check(out_scaled == 0, "F6: a zero float scales to zero and still takes the first store");
}

// REFUTE G -- floor, not truncation, not ceil, not round-to-nearest-even, not a
// clamp. Every sample below is a dyadic rational whose product with 64.0f is EXACT,
// so no expectation here depends on rounding in the test's own arithmetic.
//
//   derivation column, from CVTSS2SI (truncate toward zero) then the
//   UCOMISS/CMOVC pair (subtract one when the product is below its own truncation):
//     +2.5 -> EAX 2, XMM1 2.0, 2.5 < 2.0 false -> 2      (ceil would say 3)
//     +3.5 -> EAX 3, XMM1 3.0, false -> 3                (nearest-even would say 4)
//     -2.5 -> EAX -2, XMM1 -2.0, -2.5 < -2.0 true -> -3  (truncate would say -2)
//     -3.5 -> EAX -3, XMM1 -3.0, true -> -4              (truncate would say -3)
//     +0.5 -> EAX 0, XMM1 0.0, false -> 0
//     -0.5 -> EAX 0, XMM1 0.0, -0.5 < 0.0 true -> -1     (truncate would say 0)
//     +1.0 -> EAX 1, XMM1 1.0, false -> 1
//     +2.0 -> EAX 2, XMM1 2.0, false -> 2
void case_scaling_is_floor() {
  const ScalingPoint points[] = {
      {0.0f, 0, "zero"},
      {5.0f / 128.0f, 2, "2.5 floors to 2, not ceil 3"},
      {7.0f / 128.0f, 3, "3.5 floors to 3, not round-to-nearest-even 4"},
      {-5.0f / 128.0f, -3, "-2.5 floors to -3, not truncate -2"},
      {-7.0f / 128.0f, -4, "-3.5 floors to -4, not truncate -3"},
      {1.0f / 128.0f, 0, "0.5 floors to 0"},
      {-1.0f / 128.0f, -1, "-0.5 floors to -1, not truncate 0"},
      {1.0f / 64.0f, 1, "an exact 1.0 is left alone"},
      {1.0f / 32.0f, 2, "an exact 2.0 is left alone"},
      {1.0f, 64, "64.0f times 64.0f is 4096"},
      {-1.0f, -64, "a whole negative product needs no decrement"},
  };

  static OpaquePointee pointee;
  for (std::size_t index = 0; index < sizeof points / sizeof points[0]; ++index) {
    std::memset(&pointee, 0, sizeof pointee);
    pointee.field_08 = points[index].sampled;
    pointee.field_5c0 = 0u;
    pointee.field_5c4 = 0u;

    Arena arena = make_arena();
    install_pointee(arena, &pointee);
    std::int32_t out_scaled = 0x7ffffffe;
    Word out_5c0 = 0u;
    Word out_5c4 = 0u;
    g_obs.reset();
    re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);
    check(out_scaled == points[index].expected, points[index].derivation);
  }
}

// REFUTE H -- the x87 conversion edges, written out from the four instructions. For
// each row: EAX is what CVTSS2SI produces, XMM1 is what CVTSI2SS then produces from
// it, and the result is EAX or EAX-1 depending on whether UCOMISS raises CF for
// `XMM0 < XMM1` (ordered) or for the unordered case.
//
//   product    CVTSS2SI  XMM1        UCOMISS XMM0,XMM1        stored
//   NaN        0x80000000 -2^31      unordered -> CF=1        0x7fffffff
//   +infinity  0x80000000 -2^31      +inf < -2^31 is false    0x80000000
//   -infinity  0x80000000 -2^31      -inf < -2^31 is true     0x7fffffff
//   +6.4e31    0x80000000 -2^31      +6.4e31 < -2^31 false    0x80000000
//   -6.4e31    0x80000000 -2^31      -6.4e31 < -2^31 true     0x7fffffff
//   +2^31      0x80000000 -2^31      +2^31 < -2^31 false     0x80000000
//   -2^31      -2^31      -2^31      equal, no carry         0x80000000
//   2^31-128   2147483520 same       equal, no carry         0x7fffff80
//
// Note the -2^31 row: CVTSS2SI SUCCEEDS there and produces the same bit pattern the
// indefinite answer has, and the pair must still leave it alone. A model that
// recognised the pattern instead of the range gets this row wrong.
void case_conversion_edges() {
  struct Edge {
    float sampled;
    std::int32_t expected;
    const char* what;
  };
  const Edge edges[] = {
      {make_nan(), 0x7fffffff, "H1: a NaN product stores 0x7fffffff (indefinite minus one)"},
      {make_positive_infinity(), static_cast<std::int32_t>(0x80000000u),
       "H2: +infinity stores 0x80000000: indefinite, and +inf is NOT below -2^31 so "
       "the carry is clear"},
      {make_negative_infinity(), 0x7fffffff,
       "H3: -infinity stores 0x7fffffff: indefinite, and -inf IS below -2^31"},
      {1.0e30f, static_cast<std::int32_t>(0x80000000u),
       "H4: a positive out-of-range magnitude stores 0x80000000"},
      {-1.0e30f, 0x7fffffff,
       "H5: a negative out-of-range magnitude stores 0x7fffffff"},
      {33554432.0f, static_cast<std::int32_t>(0x80000000u),
       "H6: exactly 2^31 is out of range and stores 0x80000000"},
      {-33554432.0f, static_cast<std::int32_t>(0x80000000u),
       "H7: exactly -2^31 is IN range, and it still stores 0x80000000 unchanged"},
      {33554430.0f, 2147483520,
       "H8: the largest in-range product, 2^31-128, stores itself"},
  };

  static OpaquePointee pointee;
  for (std::size_t index = 0; index < sizeof edges / sizeof edges[0]; ++index) {
    std::memset(&pointee, 0, sizeof pointee);
    pointee.field_08 = edges[index].sampled;
    pointee.field_5c0 = 0u;
    pointee.field_5c4 = 0u;

    Arena arena = make_arena();
    install_pointee(arena, &pointee);
    std::int32_t out_scaled = 0;
    Word out_5c0 = 0u;
    Word out_5c4 = 0u;
    g_obs.reset();
    re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);
    check(out_scaled == edges[index].expected, edges[index].what);
  }
}

// REFUTE J -- write ordering. The out buffers are sampled by each callee at the
// moment it is entered, which pins three things at once: each store happens AFTER
// its own call, and the three stores happen in ascending argument order. The
// sentinels are 0x5a5a5a5a / 0x6b6b6b6b / 0x7c7c7c7c, chosen so a store of the
// scaled value into the wrong buffer, or all three stores before the first call,
// would be visible.
void case_store_order_is_observable() {
  static OpaquePointee pointee;
  std::memset(&pointee, 0, sizeof pointee);
  pointee.field_08 = 0.25f;  // 16.0
  pointee.field_5c0 = 0x0a0a0a0au;
  pointee.field_5c4 = 0x0b0b0b0bu;

  Arena arena = make_arena();
  install_pointee(arena, &pointee);

  const std::int32_t scaled_sentinel = static_cast<std::int32_t>(0x5a5a5a5au);
  const Word word_sentinel = 0x6b6b6b6bu;
  const Word word2_sentinel = 0x7c7c7c7cu;
  std::int32_t out_scaled = scaled_sentinel;
  Word out_5c0 = word_sentinel;
  Word out_5c4 = word2_sentinel;

  g_obs.reset();
  g_obs.watched_scaled = &out_scaled;
  g_obs.watched_5c0 = &out_5c0;
  g_obs.watched_5c4 = &out_5c4;
  re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);

  const std::int32_t kSentinel = static_cast<std::int32_t>(0x5a5a5a5au);
  check(g_obs.seen_valid[0] && g_obs.seen_valid[1] && g_obs.seen_valid[2],
        "J1: all three callees sampled the out buffers");
  check(g_obs.seen_scaled[0] == kSentinel && g_obs.seen_5c0[0] == word_sentinel &&
            g_obs.seen_5c4[0] == word2_sentinel,
        "J2: at 0x0097ef00 nothing has been stored yet");
  check(g_obs.seen_scaled[1] == 16, "J3: at 0x00fb7bb0 the scaled word is already stored");
  check(g_obs.seen_5c0[1] == word_sentinel && g_obs.seen_5c4[1] == word2_sentinel,
        "J4: at 0x00fb7bb0 neither word has been stored yet");
  check(g_obs.seen_5c0[2] == 0x0a0a0a0au,
        "J5: at 0x00fb7bc0 the +0x5c0 word is already stored");
  check(g_obs.seen_5c4[2] == word2_sentinel,
        "J6: at 0x00fb7bc0 the +0x5c4 word is still the sentinel");
  check(out_scaled == 16 && out_5c0 == 0x0a0a0a0au && out_5c4 == 0x0b0b0b0bu,
        "J7: and all three land in the end");
}

// REFUTE K -- the pointee is re-loaded, not cached. The first callee rewrites the
// receiver's word at +0x20c before returning. The listing reads that word three
// times (0x00f967d6, 0x00f9680a, 0x00f9681b) and consumes each read immediately,
// so the second and third callees must receive the NEW object while the scaled
// out word must still carry the OLD object's float: the multiply and the first
// store both complete before 0x00f9680a runs.
void case_pointee_is_reloaded_between_calls() {
  static OpaquePointee first_pointee;
  static OpaquePointee second_pointee;
  std::memset(&first_pointee, 0, sizeof first_pointee);
  std::memset(&second_pointee, 0, sizeof second_pointee);
  first_pointee.field_08 = 0.25f;  // 16.0
  first_pointee.field_5c0 = 0xaaaa0001u;
  first_pointee.field_5c4 = 0xaaaa0002u;
  second_pointee.field_08 = 9.0f;  // 576.0, and must NOT be what the first store used
  second_pointee.field_5c0 = 0xbbbb0001u;
  second_pointee.field_5c4 = 0xbbbb0002u;

  Arena arena = make_arena();
  install_pointee(arena, &first_pointee);

  std::int32_t out_scaled = 0;
  Word out_5c0 = 0u;
  Word out_5c4 = 0u;
  g_obs.reset();
  g_obs.swap_receiver_word_to = &second_pointee;
  g_obs.swap_receiver_word_in = receiver_of(arena.bytes);
  re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);

  check(peek<OpaquePointee*>(arena.bytes, kReceiverWordOffset) == &second_pointee,
        "K1: the first callee really did rewrite the receiver's word at +0x20c");
  check(g_obs.float_receiver == &first_pointee,
        "K2: the first callee got the object that was there when it was entered");
  check(g_obs.word5c0_receiver == &second_pointee && g_obs.word5c4_receiver == &second_pointee,
        "K3: the second and third callees got the REPLACED object, so the word is "
        "re-loaded and not cached");
  check(out_scaled == 16,
        "K4: the scaled word still carries the FIRST object's float, because the "
        "multiply and the first store both complete before the re-load");
  check(out_5c0 == 0xbbbb0001u && out_5c4 == 0xbbbb0002u,
        "K5: both word outputs come from the replaced object");
}

// REFUTE L -- the callee/argument pairing. 0x00fb7bb0's own bytes say +0x5c0 and
// 0x00fb7bc0's say +0x5c4, and the listing hands 0x00fb7bb0's EAX to the SECOND out
// parameter and 0x00fb7bc0's to the THIRD. Each observer is forced to return a
// value that is NOT the one the other callee's offset holds, so a swap, or a
// reconstruction that computed both words itself, is caught.
void case_callee_pairing_is_not_swapped() {
  static OpaquePointee pointee;
  std::memset(&pointee, 0, sizeof pointee);
  pointee.field_08 = 0.0f;
  pointee.field_5c0 = 0x0000c0c0u;  // 0x00fb7bb0's offset
  pointee.field_5c4 = 0x0000d0d0u;  // 0x00fb7bc0's offset

  Arena arena = make_arena();
  install_pointee(arena, &pointee);
  std::int32_t out_scaled = 0;
  Word out_5c0 = 0u;
  Word out_5c4 = 0u;
  g_obs.reset();
  re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);

  check(g_obs.word5c0_calls == 1 && g_obs.word5c4_calls == 1,
        "L1: both word callees ran exactly once each");
  check(out_5c0 == 0x0000c0c0u, "L2: out word 2 is 0x00fb7bb0's return, i.e. +0x5c0");
  check(out_5c4 == 0x0000d0d0u, "L3: out word 3 is 0x00fb7bc0's return, i.e. +0x5c4");
  check(peek<Word>(&pointee, 0x5c0u) == 0x0000c0c0u &&
            peek<Word>(&pointee, 0x5c4u) == 0x0000d0d0u,
        "L4: and the two offsets really do hold different values, so L2/L3 discriminate");
}

// REFUTE M -- aliased out-pointers. All three arguments are the same cell, so the
// order the three stores land in is the only thing that decides the final value,
// and the intermediate values are visible to the callees. A reconstruction that
// gathered the three values into locals and stored them at the end, or that stored
// them in descending argument order, produces a different trace.
void case_aliased_out_pointers() {
  static OpaquePointee pointee;
  std::memset(&pointee, 0, sizeof pointee);
  pointee.field_08 = 0.25f;  // 16.0
  pointee.field_5c0 = 0x11111111u;
  pointee.field_5c4 = 0x22222222u;

  Arena arena = make_arena();
  install_pointee(arena, &pointee);

  SharedCell shared;
  shared.as_word = 0xdeadbeefu;

  g_obs.reset();
  g_obs.watched_scaled = reinterpret_cast<const std::int32_t*>(&shared);
  g_obs.watched_5c0 = &shared.as_word;
  g_obs.watched_5c4 = &shared.as_word;
  re_00f967d0(receiver_of(arena.bytes), reinterpret_cast<std::int32_t*>(&shared),
              &shared.as_word, &shared.as_word);

  check(g_obs.seen_scaled[0] == static_cast<std::int32_t>(0xdeadbeefu),
        "M1: at the float call the shared cell is untouched");
  check(shared.as_word == 0x22222222u,
        "M2: the LAST store wins, so the shared cell ends on the +0x5c4 word");
  check(g_obs.seen_scaled[1] == 16,
        "M3: at the +0x5c0 call the shared cell holds the scaled value");
  check(g_obs.seen_5c0[2] == 0x11111111u,
        "M4: at the +0x5c4 call it holds the +0x5c0 word, so the stores ascend");
}

// The body never writes to the receiver. Compared over the whole arena plus the
// sentinel tail, and over the pointee, so "no other byte changed" is asserted rather
// than assumed. The +0x20c word is included: it is read, never written, except in
// case K where the TEST's own observer writes it.
void case_receiver_and_pointee_are_never_written() {
  static OpaquePointee pointee;
  std::memset(&pointee, 0, sizeof pointee);
  pointee.field_08 = 1.0f;
  pointee.field_5c0 = 0x0000c0c0u;
  pointee.field_5c4 = 0x0000d0d0u;
  poison_pointee_neighbours(&pointee);

  Arena arena = make_arena();
  install_pointee(arena, &pointee);
  const Arena before = arena;
  const OpaquePointee pointee_before = pointee;

  std::int32_t out_scaled = 0;
  Word out_5c0 = 0u;
  Word out_5c4 = 0u;
  g_obs.reset();
  re_00f967d0(receiver_of(arena.bytes), &out_scaled, &out_5c0, &out_5c4);

  check(count_changed_bytes(before.bytes, arena.bytes, kArenaBytes) == 0,
        "P1: not one byte of the receiver arena changed, including the sentinel tail "
        "past the last byte the body can reach");
  check(count_changed_bytes(reinterpret_cast<const std::uint8_t*>(&pointee_before),
                            reinterpret_cast<const std::uint8_t*>(&pointee),
                            sizeof pointee) == 0,
        "P2: the pointee is read through, never written through");
}

// REFUTE N -- the ABI. The terminator is `C2 0C 00`, so the callee owns all twelve
// argument bytes. ESP is sampled before the three pushes and after the return: the
// two are equal only when the callee popped all three words. A caller-cleaned
// convention would leave the second sample twelve bytes lower.
struct EspSamples {
  std::uint32_t before_push = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_measured(OpaqueReceiver* receiver, std::int32_t* out_scaled, Word* out_5c0,
                         Word* out_5c4) {
  // Every value the assembly needs lives in ONE stack struct, and the assembly
  // reaches all of it through a register that holds the struct's ADDRESS. That is
  // deliberate: the three pushes move ESP, so any operand GCC resolved as an
  // ESP-relative memory reference (which is what an "m" constraint produces) would
  // be read from the wrong place once the first push had happened, and the call
  // would jump through a displaced word. Going through a base register is immune to
  // that at every optimisation level, and the two ESP samples are written back into
  // the same struct for the same reason.
  struct Trampoline {
    void* target;
    void* recv;
    void* a1;
    void* a2;
    void* a3;
    std::uint32_t before;
    std::uint32_t after;
  };
  // The assembly below spells these offsets as literals, because an "i" constraint
  // would render as an immediate and an immediate is not a memory displacement. The
  // five asserts are what keeps the literals honest.
  static_assert(offsetof(Trampoline, recv) == 4u, "trampoline layout");
  static_assert(offsetof(Trampoline, a1) == 8u, "trampoline layout");
  static_assert(offsetof(Trampoline, a2) == 12u, "trampoline layout");
  static_assert(offsetof(Trampoline, a3) == 16u, "trampoline layout");
  static_assert(offsetof(Trampoline, before) == 20u, "trampoline layout");
  static_assert(offsetof(Trampoline, after) == 24u, "trampoline layout");

  Trampoline frame = {};
  frame.target = reinterpret_cast<void*>(&re_00f967d0);
  frame.recv = receiver;
  frame.a1 = out_scaled;
  frame.a2 = out_5c0;
  frame.a3 = out_5c4;

  __asm__ __volatile__("movl 4(%[frame]), %%ecx\n\t"    // the hidden receiver
                       "movl %%esp, 20(%[frame])\n\t"    // BEFORE the three pushes
                       "pushl 16(%[frame])\n\t"         // third argument
                       "pushl 12(%[frame])\n\t"         // second argument
                       "pushl 8(%[frame])\n\t"          // first argument
                       "call *(%[frame])\n\t"
                       "movl %%esp, 24(%[frame])\n\t"
                       : : [frame] "r"(&frame) : "eax", "ecx", "edx", "memory");

  EspSamples samples;
  samples.before_push = frame.before;
  samples.after_return = frame.after;
  return samples;
}

void case_twelve_argument_bytes_are_callee_cleaned() {
  static OpaquePointee pointee;
  std::memset(&pointee, 0, sizeof pointee);
  pointee.field_08 = 0.5f;  // 32.0
  pointee.field_5c0 = 0x0000c0c0u;
  pointee.field_5c4 = 0x0000d0d0u;

  Arena arena = make_arena();
  install_pointee(arena, &pointee);
  std::int32_t out_scaled = 0;
  Word out_5c0 = 0u;
  Word out_5c4 = 0u;

  g_obs.reset();
  const EspSamples samples = call_measured(receiver_of(arena.bytes), &out_scaled, &out_5c0,
                                           &out_5c4);

  check(samples.after_return == samples.before_push,
        "N1: the callee popped all three argument words (RET 0xc), so ESP is balanced");
  check(g_obs.log_is(kCallGetFloat, kCallGetWord5c0, kCallGetWord5c4),
        "N2: the trampoline really reached the body and ran it to the end");
  check(out_scaled == 32 && out_5c0 == 0x0000c0c0u && out_5c4 == 0x0000d0d0u,
        "N3: and the arguments arrived in the order the listing reads them");
}

// The displacements and the global's address, against the listing's own bytes.
void verify_displacement_constants() {
  check(kImageBase == 0x00400000u, "V1: the package was derived at image base 0x400000");
  check(kScaleConstantAddress == 0x0140f334u, "V2: the only global operand is 0x0140f334");
  check(kReceiverPointeeDisplacement == 0x20cu,
        "V3: the receiver's only word is at +0x20c (0x00f967d6)");
  check(kPointeeFloatDisplacement == 0x08u,
        "V4: 0x0097ef00 reads the float at the pointee's +0x08");
  check(kPointeeWord5c0Displacement == 0x5c0u,
        "V5: 0x00fb7bb0 reads the word at the pointee's +0x5c0");
  check(kPointeeWord5c4Displacement == 0x5c4u,
        "V6: 0x00fb7bc0 reads the word at the pointee's +0x5c4");
  check(offsetof(OpaquePointee, field_08) == 0x08u, "V7: the float member is at +0x08");
  check(offsetof(OpaquePointee, field_5c0) == 0x5c0u, "V8: the first word member is at +0x5c0");
  check(offsetof(OpaquePointee, field_5c4) == 0x5c4u, "V9: the second word member is at +0x5c4");
  check(kPointeeWord5c4Displacement - kPointeeWord5c0Displacement == 4u,
        "V10: the two word operands are one dword apart, as the two callees' listings say");
  check(sizeof(OpaqueReceiver) == 0x210u,
        "V11: the modelled receiver ends after the last byte the body can read");
  check(bits_of(scale_word_0140f334()) == 0x42800000u,
        "V12: the image's bytes at 0x0140f334 are 00 00 80 42 = 64.0f");
}

}  // namespace

int main() {
  verify_displacement_constants();
  case_transfers_receivers_and_results();
  case_multiplier_is_the_word_at_0x0140f334();
  case_two_level_dereference();
  case_receiver_displacement_is_0x20c();
  case_pointee_word_displacements_and_order();
  case_scaling_is_floor();
  case_conversion_edges();
  case_store_order_is_observable();
  case_pointee_is_reloaded_between_calls();
  case_callee_pairing_is_not_swapped();
  case_aliased_out_pointers();
  case_receiver_and_pointee_are_never_written();
  case_twelve_argument_bytes_are_callee_cleaned();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
