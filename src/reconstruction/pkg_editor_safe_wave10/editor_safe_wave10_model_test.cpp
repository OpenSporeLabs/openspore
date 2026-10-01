// Model test for 0x005a2010 (pkg_editor_safe_wave10).
//
// Every assertion below is written to FAIL if the reconstruction is wrong in
// the specific way it could plausibly be wrong, and none of them merely walks
// the happy path.  The body is fourteen instructions:
//
//   CMP byte ptr [ESP + 0x10],0x0 / MOV EAX,[ESP+0x4] / MOV EDX,[ESP+0x8] /
//   PUSH ESI / MOV ESI,[ESP+0x10] / MOV [ECX+0x80],EAX / MOV [ECX+0x84],EDX /
//   MOV [ECX+0x88],ESI / JZ +0x9 / MOV [ECX+0x74],EAX / MOV [ECX+0x78],EDX /
//   MOV [ECX+0x7c],ESI / POP ESI / RET 0x10
//
// The risks this file attacks, in order: mistaking a byte displacement for a
// word index; mistaking the mirrored row for a re-read of the primary row; a
// 32-bit gate test where the machine has a byte test; reading the receiver
// where the machine only writes it; a 5th stack word the body never touches;
// and a callee that does not release its own sixteen bytes.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "editor_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_EDITOR_SAFE_TEST_CDECL __cdecl
#define PKG_EDITOR_SAFE_TEST_THISCALL __thiscall
#else
#define PKG_EDITOR_SAFE_TEST_CDECL __attribute__((cdecl))
#define PKG_EDITOR_SAFE_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_safe_wave10 {
namespace {

using PublishSignature = void(PKG_EDITOR_SAFE_TEST_THISCALL*)(
    RowPublisherExtent*, Real, Real, Real, Word);

// ---------------------------------------------------------------------------
// Constants the test shares with the listing.  These are written in the
// machine's own spelling, and the test compares them BY VALUE (see `check` and
// the bit-pattern cases below), never by how this file happens to spell them.
// ---------------------------------------------------------------------------

constexpr std::size_t kMirrorFirst = 0x74;
constexpr std::size_t kMirrorSecond = 0x78;
constexpr std::size_t kMirrorThird = 0x7c;
constexpr std::size_t kPrimaryFirst = 0x80;
constexpr std::size_t kPrimarySecond = 0x84;
constexpr std::size_t kPrimaryThird = 0x88;
constexpr std::size_t kExtentBytes = 0x8c;

static_assert(std::is_same<decltype(&editor_row_publish_005a2010),
                           PublishSignature>::value,
              "005a2010 takes the receiver in ECX plus four stack words; RET 0x10"
              " releases those four");
static_assert(std::is_same<decltype(std::declval<PublishSignature>()(
                               std::declval<RowPublisherExtent*>(),
                               std::declval<Real>(), std::declval<Real>(),
                               std::declval<Real>(), std::declval<Word>())),
                           void>::value,
              "005a2010 returns nothing: the only value left in EAX is a"
              " caller-saved scratch word it happened to load, and the ABI"
              " record for this target carries no return register to promote"
              " it to a result");
static_assert(sizeof(RowPublisherExtent) == kExtentBytes,
              "the modelled extent is the minimum object the observed stores fit in");
static_assert(kPrimaryThird + sizeof(Real) == kExtentBytes,
              "the largest observed displacement is 0x88 and the word stored"
              " there ends at 0x8c");
static_assert(sizeof(Real) == 4 && sizeof(Word) == 4,
              "each row component and the gate formal occupy one stack word");

void check(bool condition, const char* what) {
  if (condition) {
    return;
  }
  std::fprintf(stderr, "check failed: %s\n", what);
  std::abort();
}

Word bits_of(Real value) {
  Word raw = 0;
  std::memcpy(&raw, &value, sizeof(raw));
  return raw;
}

Real value_of(Word raw) {
  Real value = 0.0f;
  std::memcpy(&value, &raw, sizeof(value));
  return value;
}

// A read of the receiver as BYTES at a byte displacement.  Deliberately not a
// member read: nothing here may depend on a member name, because the machine
// names none.
Word byte_word_at(const RowPublisherExtent* receiver, std::size_t displacement) {
  Word raw = 0;
  std::memcpy(&raw, receiver->bytes + displacement, sizeof(raw));
  return raw;
}

void seed_all(RowPublisherExtent* receiver) {
  std::memset(receiver, 0xcd, sizeof(*receiver));
  const Real fills[6] = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f};
  const std::size_t slots[6] = {kMirrorFirst, kMirrorSecond, kMirrorThird,
                                kPrimaryFirst, kPrimarySecond, kPrimaryThird};
  for (std::size_t index = 0; index < 6u; ++index) {
    std::memcpy(receiver->bytes + slots[index], &fills[index], sizeof(Real));
  }
}

// -- 1. Displacement is an OFFSET, not an index -----------------------------
// If the model had treated the printed displacements as word indices, the first
// primary word would have landed at 0x80*4 = 0x200 -- an address three times
// past the end of even the minimum extent -- and the mirrored row at 0x1d0.
// The test pins all six at their byte displacements and then proves that no
// byte outside the six-word window moved, which an index model cannot do.
void test_displacements_are_byte_offsets() {
  RowPublisherExtent receiver{};
  seed_all(&receiver);
  editor_row_publish_005a2010(&receiver, 1.0f, 2.0f, 3.0f, 1u);
  check(byte_word_at(&receiver, kPrimaryFirst) == bits_of(1.0f),
        "the word at byte offset 0x80 holds the first component");
  check(byte_word_at(&receiver, kPrimarySecond) == bits_of(2.0f),
        "the word at byte offset 0x84 holds the second component");
  check(byte_word_at(&receiver, kPrimaryThird) == bits_of(3.0f),
        "the word at byte offset 0x88 holds the third component");
  check(byte_word_at(&receiver, kMirrorFirst) == bits_of(1.0f),
        "the word at byte offset 0x74 holds the mirrored first component");
  check(byte_word_at(&receiver, kMirrorSecond) == bits_of(2.0f),
        "the word at byte offset 0x78 holds the mirrored second component");
  check(byte_word_at(&receiver, kMirrorThird) == bits_of(3.0f),
        "the word at byte offset 0x7c holds the mirrored third component");

  // The neighbouring bytes must stay distinct: 0x80 and 0x84 are one word
  // apart, 0x08 is inside the opaque prefix the body never reaches, and the
  // bytes immediately below the two six-word windows are not part of either.
  // An implementation that folded the three components into one 12-byte write,
  // that reached below 0x74, or that wrote at 0x08 fails here.
  check(byte_word_at(&receiver, 0x08) == 0xcdcdcdcdu,
        "byte offset 0x08 is untouched, so 0x80 is not an offset from 0x08");
  check(byte_word_at(&receiver, 0x0c) == 0xcdcdcdcdu,
        "byte offset 0x0c is untouched");
  for (std::size_t index = 0x70; index < 0x74u; ++index) {
    check(receiver.bytes[index] == 0xcd,
          "the four bytes below 0x74 keep their fill, so the mirror write did"
          " not start early or run backwards");
  }
  for (std::size_t index = 0x6c; index < 0x70u; ++index) {
    check(receiver.bytes[index] == 0xcd,
          "the word below 0x74 keeps its fill, so a word-indexed 0x74 (which"
          " would be 0x1d0) is not what this body does");
  }
}

// -- 2. The gate is a BYTE of a word, not the word --------------------------
// `CMP byte ptr [ESP + 0x10],0x0` reads one byte.  A 32-bit truth test would
// mirror for 0x00000100 and for 0xff000000; the machine does not, and neither
// may the reconstruction.
void test_gate_is_a_byte_of_the_fourth_formal() {
  const Word word_gate_mirrors[4] = {0x00000001u, 0x000000ffu, 0x00000101u,
                                     0x00000080u};
  const Word word_gate_does_not_mirror[4] = {0x00000000u, 0x00000100u,
                                             0x00ff0000u, 0xff000000u};
  for (const Word gate : word_gate_mirrors) {
    RowPublisherExtent receiver{};
    seed_all(&receiver);
    editor_row_publish_005a2010(&receiver, 8.0f, 9.0f, 10.0f, gate);
    check(byte_word_at(&receiver, kMirrorFirst) == bits_of(8.0f),
          "a nonzero low byte mirrors the row");
    check(byte_word_at(&receiver, kMirrorSecond) == bits_of(9.0f),
          "a nonzero low byte mirrors the second word");
    check(byte_word_at(&receiver, kMirrorThird) == bits_of(10.0f),
          "a nonzero low byte mirrors the third word");
  }
  for (const Word gate : word_gate_does_not_mirror) {
    RowPublisherExtent receiver{};
    seed_all(&receiver);
    editor_row_publish_005a2010(&receiver, 8.0f, 9.0f, 10.0f, gate);
    check(byte_word_at(&receiver, kMirrorFirst) == bits_of(-1.0f),
          "a word whose low byte is zero leaves the mirror alone even when the"
          " rest of the word is nonzero -- a word-wide truth test would fail"
          " this");
    check(byte_word_at(&receiver, kMirrorSecond) == bits_of(-2.0f),
          "a zero low byte leaves the second mirrored word alone");
    check(byte_word_at(&receiver, kMirrorThird) == bits_of(-3.0f),
          "a zero low byte leaves the third mirrored word alone");
    check(byte_word_at(&receiver, kPrimaryFirst) == bits_of(8.0f),
          "the primary row is written unconditionally whatever the gate is");
    check(byte_word_at(&receiver, kPrimarySecond) == bits_of(9.0f),
          "the second primary word is written unconditionally");
    check(byte_word_at(&receiver, kPrimaryThird) == bits_of(10.0f),
          "the third primary word is written unconditionally");
  }
}

// -- 3. The gate is NOT a receiver field ------------------------------------
// The gate is read from the caller's stack at ESP+0x10.  A reconstruction that
// conflated it with a slot in the object would take the mirror decision from
// receiver bytes; the machine never reads the receiver, so no receiver content
// may reach the decision.
void test_gate_is_not_a_receiver_field() {
  RowPublisherExtent zero_gate{};
  RowPublisherExtent loud_receiver{};
  seed_all(&zero_gate);
  std::memset(&loud_receiver, 0xff, sizeof(loud_receiver));
  editor_row_publish_005a2010(&zero_gate, 1.0f, 2.0f, 3.0f, 0u);
  editor_row_publish_005a2010(&loud_receiver, 1.0f, 2.0f, 3.0f, 0u);
  check(byte_word_at(&zero_gate, kMirrorFirst) == bits_of(-1.0f),
        "an all-0xcd receiver with a zero gate keeps the mirror row");
  check(byte_word_at(&loud_receiver, kMirrorFirst) == 0xffffffffu,
        "an all-0xff receiver with a zero gate keeps the mirror row too: no"
        " receiver byte can enable the mirror");
  check(byte_word_at(&zero_gate, kPrimaryFirst) == bits_of(1.0f),
        "the primary row is written even when the receiver is all 0xcd");
  check(byte_word_at(&loud_receiver, kPrimaryFirst) == bits_of(1.0f),
        "the primary row is written even when the receiver is all 0xff");
}

// -- 4. The stores carry the FORMALS, not the receiver's previous content ----
// The body loads the three row words off the argument block and then stores
// them; it never loads the receiver.  A model that read a receiver slot and
// stored that (or that stored the pre-load residue) fails here, because every
// receiver slot is seeded with a distinct sentinel first.
void test_stores_carry_the_formals_not_the_previous_receiver_content() {
  RowPublisherExtent receiver{};
  seed_all(&receiver);
  const Real formals[3] = {11.5f, -22.25f, 33.125f};
  editor_row_publish_005a2010(&receiver, formals[0], formals[1], formals[2], 0u);
  check(byte_word_at(&receiver, kPrimaryFirst) == bits_of(11.5f),
        "+0x80 takes the first formal, not the -4.0f that was resident there");
  check(byte_word_at(&receiver, kPrimarySecond) == bits_of(-22.25f),
        "+0x84 takes the second formal, not the -5.0f that was resident there");
  check(byte_word_at(&receiver, kPrimaryThird) == bits_of(33.125f),
        "+0x88 takes the third formal, not the -6.0f that was resident there");

  // The same four formals against two very different receivers must produce
  // byte-identical results: the output is a pure function of the formals,
  // which is what "the body never reads the receiver" means.
  RowPublisherExtent quiet{};
  RowPublisherExtent loud{};
  std::memset(&quiet, 0x00, sizeof(quiet));
  std::memset(&loud, 0xa5, sizeof(loud));
  editor_row_publish_005a2010(&quiet, 1.0f, 2.0f, 3.0f, 0x00000001u);
  editor_row_publish_005a2010(&loud, 1.0f, 2.0f, 3.0f, 0x00000001u);
  // Compared over the six observed displacements only: the bytes the body
  // never reaches are still the two different fills, and comparing them would
  // be comparing the seed rather than the effect.
  check(std::memcmp(quiet.bytes + kMirrorFirst, loud.bytes + kMirrorFirst,
                    kPrimaryThird + sizeof(Real) - kMirrorFirst) == 0,
        "the result does not depend on any receiver byte");
}

// -- 5. A store is a 4-byte MOVE: the bit pattern arrives intact --------------
// Negative zero, a subnormal and 1.5 are the three values an arithmetic
// implementation (a multiply, an add, a normalisation) would not reproduce
// bit-for-bit.  A 4-byte `MOV` must.
void test_stores_are_bit_exact_moves() {
  const Real negative_zero = value_of(0x80000000u);
  const Real subnormal = value_of(0x00000001u);
  const Real one_and_a_half = value_of(0x3fc00000u);
  RowPublisherExtent receiver{};
  seed_all(&receiver);
  editor_row_publish_005a2010(&receiver, negative_zero, subnormal,
                              one_and_a_half, 0x000000ffu);
  check(byte_word_at(&receiver, kPrimaryFirst) == 0x80000000u,
        "the sign bit of negative zero survives the move to +0x80");
  check(byte_word_at(&receiver, kPrimarySecond) == 0x00000001u,
        "the subnormal payload survives the move to +0x84");
  check(byte_word_at(&receiver, kPrimaryThird) == 0x3fc00000u,
        "1.5 arrives at +0x88 bit for bit");
  check(byte_word_at(&receiver, kMirrorFirst) == 0x80000000u,
        "the mirrored first word keeps the sign bit too");
  check(byte_word_at(&receiver, kMirrorSecond) == 0x00000001u,
        "the mirrored second word keeps the subnormal payload");
  check(byte_word_at(&receiver, kMirrorThird) == 0x3fc00000u,
        "the mirrored third word is unchanged");

  // 0x0c and 0xc are the same constant; the value is what the model acts on.
  const Word gate_spelled_tall = 0x00000101u;
  RowPublisherExtent tall{};
  seed_all(&tall);
  editor_row_publish_005a2010(&tall, 0.25f, 0.5f, 0.75f, gate_spelled_tall);
  check(byte_word_at(&tall, kPrimaryFirst) == 0x3e800000u,
        "0.25f is 0x3e800000 at +0x80 whatever the gate's spelling");
  check(byte_word_at(&tall, kMirrorThird) == 0x3f400000u,
        "0.75f is 0x3f400000 at +0x7c and the 0x1 in 0x101 is a nonzero low"
        " byte, so the mirror runs");
}

// -- 6. Nothing outside the six observed displacements is written ------------
// The listing contains six stores and no others.  This diffs the whole
// modelled extent and requires the changed bytes to be exactly the mirrored
// three when the gate is zero, and the mirrored three plus the primary three
// when it is not.
void test_only_the_observed_displacements_change() {
  const std::size_t six[6] = {kMirrorFirst, kMirrorSecond, kMirrorThird,
                              kPrimaryFirst, kPrimarySecond, kPrimaryThird};
  const Word sets[2] = {0u, 0x00000001u};
  for (const Word gate : sets) {
    RowPublisherExtent before{};
    RowPublisherExtent after{};
    // A uniform 0xcd fill, so every byte a store lands on really does differ
    // and the byte census below measures the effect and not the seed.
    std::memset(&before, 0xcd, sizeof(before));
    std::memcpy(&after, &before, sizeof(after));
    editor_row_publish_005a2010(&after, 7.0f, 8.0f, 9.0f, gate);
    const bool mirror_runs = gate != 0u;

    std::size_t changed = 0;
    std::size_t first_changed = kExtentBytes;
    std::size_t last_changed = 0;
    for (std::size_t index = 0; index < kExtentBytes; ++index) {
      if (before.bytes[index] != after.bytes[index]) {
        changed += 1;
        if (index < first_changed) {
          first_changed = index;
        }
        last_changed = index;
      }
    }
    check(changed == (mirror_runs ? 6u : 3u) * sizeof(Real),
          "only the words the gate selects change, and all four bytes of each");
    check(first_changed == (mirror_runs ? kMirrorFirst : kPrimaryFirst),
          "the first byte the body ever writes is the first byte of the"
          " selected window, so nothing below it is reached");
    check(last_changed == kPrimaryThird + sizeof(Real) - 1u,
          "the last byte the body ever writes is the last byte of the primary"
          " window at 0x88, so the observed extent is 0x8c and not one byte"
          " more");

    // Every changed byte lies inside one of the two four-byte-strided windows
    // the listing prints.  A store at a displacement that is off by one, or a
    // 12-byte write spanning them, changes a byte outside and fails here.
    for (std::size_t index = 0; index < kExtentBytes; ++index) {
      if (before.bytes[index] == after.bytes[index]) {
        continue;
      }
      bool inside = false;
      for (const std::size_t slot : six) {
        if (index >= slot && index < slot + sizeof(Real)) {
          inside = true;
        }
      }
      check(inside, "a changed byte lies outside the six observed"
                    " four-byte windows, so a displacement is wrong");
    }

    for (std::size_t rank = 0; rank < 3u; ++rank) {
      const std::size_t primary = kPrimaryFirst + rank * sizeof(Real);
      check(std::memcmp(before.bytes + primary, after.bytes + primary,
                        sizeof(Real)) != 0,
            "each of the three primary words changed whatever the gate is");
      const std::size_t mirrored = kMirrorFirst + rank * sizeof(Real);
      const bool mirrored_changed =
          std::memcmp(before.bytes + mirrored, after.bytes + mirrored,
                      sizeof(Real)) != 0;
      check(mirrored_changed == mirror_runs,
            "a mirrored word changed exactly when the gate's low byte is"
            " nonzero, so the mirror is not aliased onto the primary row");
    }
  }
}

// -- 7. RET 0x10: the callee releases the four words it was given ------------
// Measured, not asserted.  A cdecl shim allocates a canary below its own
// argument block, calls through the thiscall pointer, and then checks that the
// canary and the two words past the caller's arguments are intact.  A cdecl
// callee (which would not pop) leaves a stale word above the return address
// and shifts nothing here; the strong form of the check is #8, where the
// caller-visible stack image is compared.
std::uint32_t stack_probe_image = 0;
std::uint8_t stack_probe_rows[kExtentBytes] = {};

void PKG_EDITOR_SAFE_TEST_CDECL publish_stack_probe(
    RowPublisherExtent* self, Real row_x, Real row_y, Real row_z,
    Word also_previous, Word fifth_word, Word guard_low, Word guard_high) {
  std::uint32_t* const canary =
      static_cast<std::uint32_t*>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  static_cast<void>(fifth_word);
  const PublishSignature publish = &editor_row_publish_005a2010;
  publish(self, row_x, row_y, row_z, also_previous);
  check(canary[0] == 0xc0dec0deu, "the word below the argument block held");
  check(canary[1] == 0xfeedfaceu, "the second word below the argument block held");
  check(guard_low == 0x11223344u, "the word after the fourth argument held");
  check(guard_high == 0x55667788u, "the word after the fifth argument held");
  stack_probe_image = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
  std::memcpy(stack_probe_rows, self, kExtentBytes);
}

void test_callee_releases_four_words_and_ignores_a_fifth() {
  RowPublisherExtent first{};
  RowPublisherExtent second{};
  seed_all(&first);
  seed_all(&second);
  publish_stack_probe(&first, 1.0f, 2.0f, 3.0f, 0u, 0x00000000u, 0x11223344u,
                      0x55667788u);
  std::uint8_t with_zero_fifth[kExtentBytes];
  std::memcpy(with_zero_fifth, stack_probe_rows, sizeof(with_zero_fifth));
  publish_stack_probe(&second, 1.0f, 2.0f, 3.0f, 0u, 0xffffffffu, 0x11223344u,
                      0x55667788u);
  check(std::memcmp(with_zero_fifth, stack_probe_rows,
                    sizeof(with_zero_fifth)) == 0,
        "a fifth stack word is never read: RET 0x10 releases exactly four"
        " words, so nothing above the fourth argument is in scope");
  check(byte_word_at(&first, kPrimaryFirst) == bits_of(1.0f),
        "the probe's call reached +0x80");
  check(byte_word_at(&first, kMirrorFirst) == bits_of(-1.0f),
        "the probe's call left the mirror alone for a zero gate");
  check(stack_probe_image ==
            (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u),
        "every canary and guard word below and above the arguments survived");
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_editor_safe_wave10;
  test_displacements_are_byte_offsets();
  test_gate_is_a_byte_of_the_fourth_formal();
  test_gate_is_not_a_receiver_field();
  test_stores_carry_the_formals_not_the_previous_receiver_content();
  test_stores_are_bit_exact_moves();
  test_only_the_observed_displacements_change();
  test_callee_releases_four_words_and_ignores_a_fifth();
  return 0;
}

#undef PKG_EDITOR_SAFE_TEST_CDECL
#undef PKG_EDITOR_SAFE_TEST_THISCALL
