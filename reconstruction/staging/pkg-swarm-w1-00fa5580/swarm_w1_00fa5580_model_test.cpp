// PKG-SWARM-W1-00FA5580 -- VA 0x00fa5580
// Behavioural model test for FUN_00fa5580 @ 0x00fa5580.
//
// The one direct callee, 0x00f9f770, is defined here as an observer, so the test
// sees every transfer the reconstruction makes, with which arguments, in which order,
// and decides what it does to memory. It is implemented with the real callee's
// semantics, read out of 0x00f9f770's and 0x00f9f620's own bytes: the stack word is
// read and the ECX receiver is written, so it copies first_source into
// first_destination while first_source has not reached source_limit, advancing both
// by one 0xac stride, and returns the write cursor one stride past its last use.
//
// What is asserted is what the 46-instruction listing fixes, and nothing more:
//
//   * the single transfer, its three arguments and their order, and the guard that
//     decides whether it happens at all (an UNSIGNED `>=` on two addresses);
//   * the two receiver words read (0x798, 0x79c) and the one written (0x79c, by
//     -0xac) -- checked by comparing the receiver's bytes before and after, so "no
//     other byte changed" is asserted rather than assumed;
//   * the key read at the ELEMENT's own +0xa8, as a full 32-bit compare, two levels
//     down from the receiver;
//   * the signed `count <= 0` guard and the signed loop bound, together fixing the
//     scanned range as indices 0 .. count-1;
//   * the count itself: the six magic-multiply instructions, cross-checked against a
//     second, independently written transliteration of them, and shown to differ from
//     a C division on a negative span;
//   * the return word: AL is the flag, and bits 8..31 are the count, the successor's
//     address or the callee's return word as the path dictates;
//   * the ABI: the receiver in ECX and the callee-popped argument word, MEASURED by
//     sampling ESP inside a trampoline rather than asserted as a convention.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk it.
// Each names a wrong reconstruction it is aimed at:
//
//   A  count == 0 with the key PRESENT in element 0: the guard at 0x00fa55a6 must
//      stop the scan before it reads a single element. A model that scans
//      unconditionally finds the key and shifts.
//   B  argument order: the observer asserts the exact triple
//      (successor, limit, matched). A model that passes (matched, limit, successor),
//      or that swaps the first two, is caught by identity, not by array contents.
//   C  copy direction: with three elements and a match in the middle, the real
//      semantics must leave the element AFTER the match in the matched slot. The
//      inverted direction is what a two-level misreading of 0x00f9f620 produces, and
//      it leaves a visibly different array.
//   D  the unsigned guard: removing the LAST element makes the successor equal the
//      limit, and the call must not run. A `<=` guard calls it.
//   E  the loop bound: a key in the last live element is found; the same key one slot
//      further on is not. A model that scans to the buffer's end, or that uses `<=`
//      on the bound, differs on one side or the other.
//   F  the key offset: a key planted at the element's +0x00 with a decoy at +0xa8 is
//      not found; the same key at +0xa8 with a decoy at +0x00 is.
//   G  the write ordering: the observer reads the receiver's +0x79c at the moment of
//      the call and requires the PRE-decrement value. A model that decrements first
//      hands the callee a limit one stride too low, which also changes the number of
//      moves.
//   H  the decrement: it happens on both arms, by exactly 0xac, including when the
//      shift was skipped, and a neighbouring decoy word is never touched.
//   I  the receiver's two words are two different words: a decoy pair one stride
//      away is not the array.
//   J  the count is the magic and not the division: a negative span, where the two
//      disagree, driven until the published return word separates them.
//   K  the dead return bits: a poisoned callee return word must reach the caller, so a
//      model that computed the high bits from the successor's address instead is
//      caught.
//   L  the argument count: the trampoline shows ESP is restored across the call, so
//      the callee popped the argument word and no slot was dropped.
//
// What is NOT asserted, and why:
//
//   * That the machine's upper 24 bits of EAX hold what the model's dead_return_word
//     publishes. That is a fact about the original's codegen, and a C++ model cannot
//     pin the dead bytes of a return register: the mandated -m32 g++ is free to zero
//     or to preserve them. The trampoline therefore asserts only that the LOW BYTE is
//     the flag, which is the whole of the declared 1-byte return type, and the
//     published dead word is asserted as the model's own instrumentation.
//   * The second reads of the receiver's two words (0x00fa5584/0x00fa55cf and
//     0x00fa558a/0x00fa55a8). Nothing this body calls writes the receiver, so no
//     interleaving can be observed between a first read and a second one, and the
//     model reads each once.
//   * That the search visits elements in ascending order, beyond the fact that it
//     finds the first match: with duplicate keys the first match wins in the machine
//     and in the model, and nothing distinguishes the order beyond that.
//   * Anything about the 0x00f9f770 body beyond the three frame reads, the copy
//     direction, the 0xac stride and the returned write cursor. It is not this
//     package's target; what is used is fixed by its own bytes and cited.

#include "swarm_w1_00fa5580_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

namespace openspore::reconstruction::pkg_swarm_w1_00fa5580 {
namespace {

// Machine displacements, as literals in the harness so that a wrong one is a wrong
// one here and not in the reconstruction. 0x798/0x79c are the receiver's two words;
// 0x794 and 0x7a0 are the decoys either side of them.
constexpr std::size_t kLower = 0x798;
constexpr std::size_t kUpper = 0x79c;
constexpr std::size_t kDecoyBelow = 0x794;
constexpr std::size_t kDecoyAbove = 0x7a0;
constexpr std::size_t kDecoyFar = 0x780;

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void check_eq_word(Word got, Word want, const char* what) {
  if (got != want) {
    std::fprintf(stderr, "FAILED: %s (got 0x%08x, want 0x%08x)\n", what, got, want);
    ++g_failures;
  }
}

void check_eq_int(std::int32_t got, std::int32_t want, const char* what) {
  if (got != want) {
    std::fprintf(stderr, "FAILED: %s (got %d, want %d)\n", what, got, want);
    ++g_failures;
  }
}

// A stored word compared against a pointer, i.e. "is the receiver's +0x79c this
// address". Kept separate from check_eq_ptr so that a mistake in one cannot be
// silently satisfied by the other's conversion.
void check_eq_addr(Word got, const void* want, const char* what) {
  const Word expected = static_cast<Word>(reinterpret_cast<std::uintptr_t>(want));
  if (got != expected) {
    std::fprintf(stderr, "FAILED: %s (got 0x%08x, want 0x%08x)\n", what, got, expected);
    ++g_failures;
  }
}

void check_eq_ptr(const void* got, const void* want, const char* what) {
  if (got != want) {
    std::fprintf(stderr, "FAILED: %s (got %p, want %p)\n", what, got, want);
    ++g_failures;
  }
}

std::uint32_t address_of(const void* p) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(p));
}

// -- the observer for 0x00f9f770 -------------------------------------------------
struct Observation {
  int shift_calls = 0;
  Element* arg_first = nullptr;   // the first word: read cursor
  Element* arg_second = nullptr;  // the second word: the read limit
  Element* arg_third = nullptr;   // the third word: write cursor
  int moves = 0;
  bool guard_holds = false;  // first < second as the machine's JNC requires
  // The receiver's upper word as the callee finds it, i.e. BEFORE the body's
  // decrement. Sampled inside the call on purpose (case G).
  Word upper_at_call = 0;
  Word decoy_below_at_call = 0;
  Word decoy_above_at_call = 0;
  // A fixture, not a claim: when set, the observer returns this instead of the real
  // callee's write cursor, so the test can drive the dead half of the return word.
  bool poison_return = false;
  std::uint32_t poison_return_value = 0;

  void reset() { *this = Observation(); }
};

Observation g_seen;

// The receiver's words as the callee will see them: taken from the arena the test
// built, through the pointers the body handed over.
Receiver* g_probe_receiver = nullptr;

// 0x00f9f770, as its own bytes describe it. See the header for the three frame
// reads and for 0x00f9f620 fixing the copy direction.
extern "C" Element* array_shift_tail_down_00f9f770(Element* first_source,
                                                    Element* source_limit,
                                                    Element* first_destination) {
  ++g_seen.shift_calls;
  g_seen.arg_first = first_source;
  g_seen.arg_second = source_limit;
  g_seen.arg_third = first_destination;
  g_seen.guard_holds =
      address_of(first_source) < address_of(source_limit);
  g_seen.upper_at_call = g_probe_receiver == nullptr
                             ? 0u
                             : *reinterpret_cast<const Word*>(
                                   reinterpret_cast<const std::uint8_t*>(g_probe_receiver) +
                                   kUpper);
  if (g_probe_receiver != nullptr) {
    const std::uint8_t* self =
        reinterpret_cast<const std::uint8_t*>(g_probe_receiver);
    g_seen.decoy_below_at_call = *reinterpret_cast<const Word*>(self + kDecoyBelow);
    g_seen.decoy_above_at_call = *reinterpret_cast<const Word*>(self + kDecoyAbove);
  }

  Element* read_cursor = first_source;
  Element* write_cursor = first_destination;
  int moves = 0;
  while (read_cursor != source_limit) {
    std::memcpy(write_cursor, read_cursor, sizeof(Element));
    read_cursor = reinterpret_cast<Element*>(reinterpret_cast<std::uint8_t*>(read_cursor) +
                                             sizeof(Element));
    write_cursor = reinterpret_cast<Element*>(
        reinterpret_cast<std::uint8_t*>(write_cursor) + sizeof(Element));
    ++moves;
  }
  g_seen.moves = moves;
  if (g_seen.poison_return) {
    return reinterpret_cast<Element*>(static_cast<std::uintptr_t>(
        g_seen.poison_return_value));
  }
  return write_cursor;
}

// -- the ABI trampoline ---------------------------------------------------------
// Sets ECX, pushes the one argument word, calls the reconstruction, and samples ESP
// on both sides of the call plus the whole of EAX afterwards. It exists to MEASURE
// the cleanup (case L) rather than to assert the convention, and to read the returned
// byte out of the return register rather than out of the declared type.
struct AbiProbe {
  std::uint32_t esp_before;
  std::uint32_t esp_after;
  std::uint32_t eax;
};

extern "C" void probe_re_00fa5580(Receiver* receiver, Word key, AbiProbe* probe) {
  // The key is pushed BEFORE ECX is loaded, so this is correct whichever register
  // the compiler picks for either operand. The three outputs are early-clobber so
  // none of them can share a register with an input, which is what keeps the three
  // samples distinct; the runtime assertions would catch it either way.
  __asm__ volatile(
      "pushl  %[key]\n\t"
      "movl   %[rec], %%ecx\n\t"
      "movl   %%esp, %[before]\n\t"
      "call   re_00fa5580\n\t"
      "movl   %%esp, %[after]\n\t"
      "movl   %%eax, %[out]\n\t"
      : [before] "=&r"(probe->esp_before),
        [after] "=&r"(probe->esp_after),
        [out] "=&r"(probe->eax)
      : [rec] "r"(receiver), [key] "r"(key)
      // EBX, ESI and EDI are NOT clobbered, and that is a machine fact about the
      // reconstruction rather than an oversight: 0x00fa5580/0x00fa5581 push EBX and
      // ESI, 0x00fa55a3 pushes EDI, and 0x00fa55cb/0x00fa55c8/0x00fa55fc pop them
      // again, so all three arrive here as the trampoline left them. Listing them
      // would also leave x86-32 with only EAX/ECX/EDX to allocate five operands to.
      : "memory", "cc");
}

// -- the count, twice ------------------------------------------------------------
// The reconstruction uses element_count_from_span() from the header. This is a
// SECOND, independently written transliteration of the same six instructions,
// register by register, and case J checks the two against each other.
std::int32_t count_by_literal_instructions(std::int32_t span) {
  // 0x00fa5590  MOV EAX,0x2fa0be83
  // 0x00fa5595  IMUL EDX            -> EDX:EAX is the 64-bit product
  const std::int64_t product =
      static_cast<std::int64_t>(0x2fa0be83) * static_cast<std::int64_t>(span);
  // 0x00fa5597  SAR EDX,0x5         -> the high word, shifted arithmetically
  std::int32_t edx = static_cast<std::int32_t>(static_cast<std::uint32_t>(product >> 32));
  edx = edx >> 5;
  // 0x00fa559a  MOV EAX,EDX
  // 0x00fa559c  SHR EAX,0x1f        -> 0x00000000 or 0xffffffff (not 0 or 1: the
  //                                      shift is a LOGICAL one, so the negative
  //                                      case yields all ones, which is -1)
  // 0x00fa559f  ADD EAX,EDX
  const std::uint32_t sign_bit = static_cast<std::uint32_t>(static_cast<std::uint32_t>(edx) >> 31);
  const std::uint32_t addend = 0u - sign_bit;  // 0x00000000 or 0xffffffff
  return static_cast<std::int32_t>(static_cast<std::uint32_t>(edx) + addend);
}

// -- the fixture -----------------------------------------------------------------
// The receiver occupies the first 0x7a0 bytes of the arena, which is the whole of
// the modelled receiver, and the element array sits at 0x800 so that a shift can
// never touch a byte the byte-level assertion is watching.
struct alignas(16) Arena {
  std::uint8_t bytes[0x1000];
};

struct Fixture {
  Arena arena{};

  Receiver* receiver() { return reinterpret_cast<Receiver*>(arena.bytes); }
  Element* elements() { return reinterpret_cast<Element*>(arena.bytes + 0x800); }

  Word* word(std::size_t displacement) {
    return reinterpret_cast<Word*>(arena.bytes + displacement);
  }
};

void set_key(Element* e, Word key) { e->field_a8 = key; }

Word key_of(const Element* e) { return e->field_a8; }

// Points the receiver at a two-word array and plants the three decoy words around
// it. `expected_count` is not decoration: it is what the reconstruction's own count
// helper must produce for the span these two words describe, so every case that arms
// a fixture also states what the magic-multiply sequence has to say about it.
void arm(Fixture& f, Element* lower, Element* upper, std::int32_t expected_count) {
  *f.word(kLower) = address_of(lower);
  *f.word(kUpper) = address_of(upper);
  *f.word(kDecoyBelow) = 0xdeadbeefu;
  *f.word(kDecoyAbove) = 0x0badf00du;
  *f.word(kDecoyFar) = 0xfeedfaceu;
  g_probe_receiver = f.receiver();
  g_seen.reset();
  const std::int32_t span = static_cast<std::int32_t>(address_of(upper) - address_of(lower));
  check_eq_int(element_count_from_span(span), expected_count,
               "fixture: the count of the array the fixture just armed");
}

Element* at(Fixture& f, int index) {
  return reinterpret_cast<Element*>(reinterpret_cast<std::uint8_t*>(f.elements()) +
                                   static_cast<std::size_t>(index) * sizeof(Element));
}

// ---------------------------------------------------------------------------
// Case A/B/C: a match in the middle of three elements. The one transfer, its
// arguments in order, and the array the real callee leaves behind.
// ---------------------------------------------------------------------------
static void case_middle_match() {
  Fixture f;
  Element* e0 = at(f, 0);
  Element* e1 = at(f, 1);
  Element* e2 = at(f, 2);
  Element* e3 = at(f, 3);
  for (int i = 0; i < 4; ++i) {
    set_key(at(f, i), 0x1000u + static_cast<Word>(i));
  }
  arm(f, e0, e3, 3);

  const Word key = key_of(e1);
  const std::uint8_t result = re_00fa5580(f.receiver(), key);

  check_eq_int(result, 1, "A/B: a match in the middle returns 1");
  check_eq_int(g_seen.shift_calls, 1, "B: the callee is called exactly once");
  // B: the triple, by identity. (successor, limit, matched).
  check_eq_ptr(g_seen.arg_first, e2, "B: first word is the matched element's successor");
  check_eq_ptr(g_seen.arg_second, e3, "B: second word is the array's limit");
  check_eq_ptr(g_seen.arg_third, e1, "B: third word is the matched element");
  check(g_seen.guard_holds, "B: the unsigned guard held, so the callee's loop terminates");
  check_eq_int(g_seen.moves, 1, "C: exactly one element is copied down, the one after the match");
  // C: the copy direction. e2's old key must now sit in the matched slot e1. The
  // inverted direction would instead have put e1's own key into e2 and left e2's in
  // e3, which is what a misreading of 0x00f9f620's copy direction produces.
  check_eq_word(key_of(e1), 0x1002u, "C: the element AFTER the match lands in the matched slot");
  // e2 is the limit, not an element the callee reads: the loop stops when the read
  // cursor REACHES the limit, so the removed element's own successor keeps its bytes
  // and the new end is that address. A model that read one element too many (an
  // off-by-one on the limit) would put 0x1003 here.
  check_eq_word(key_of(e2), 0x1002u, "C: the element at the limit is never read or written");
  // H: the decrement, by exactly one stride, and the neighbour decoys untouched.
  check_eq_addr(*f.word(kUpper), e2, "H: the upper word moved down by exactly one stride");
  check_eq_word(*f.word(kDecoyBelow), 0xdeadbeefu, "H: the decoy below the pair is untouched");
  check_eq_word(*f.word(kDecoyAbove), 0x0badf00du, "H: the decoy above the pair is untouched");
  check_eq_word(*f.word(kDecoyFar), 0xfeedfaceu, "H: the far decoy is untouched");
  // K: the dead half of the return word is the callee's return, which is the write
  // cursor one stride on: e2 + 0xac == e3.
  check_eq_word(dead_return_word() & kReturnHighBytesMask,
                address_of(e2) & kReturnHighBytesMask,
                "K: the dead high bits are the callee's return word, which here happens "
                "to coincide with the successor; the poisoned case separates them");
  check_eq_word(dead_return_word() & 1u, 1u, "K: bit 0 of the return word is the flag");
}

// ---------------------------------------------------------------------------
// Case D: a match in the LAST live element. successor == limit, so the call must
// not run, and the decrement must still happen.
// ---------------------------------------------------------------------------
static void case_last_match() {
  Fixture f;
  Element* e0 = at(f, 0);
  Element* e1 = at(f, 1);
  Element* e2 = at(f, 2);
  for (int i = 0; i < 3; ++i) {
    set_key(at(f, i), 0x2000u + static_cast<Word>(i));
  }
  arm(f, e0, e2, 2);

  const std::uint8_t result = re_00fa5580(f.receiver(), key_of(e1));

  check_eq_int(result, 1, "D: a match in the last element returns 1");
  check_eq_int(g_seen.shift_calls, 0, "D: the call is skipped when successor == limit");
  check_eq_addr(*f.word(kUpper), e1, "D: the decrement still happens on the skipped arm");
  check_eq_word(key_of(e1), 0x2001u, "D: the removed element's bytes are left in place");
  // The dead high bits are then the successor's own address (0x00fa55dd), not the
  // callee's, because no call ran.
  check_eq_word(dead_return_word() & kReturnHighBytesMask,
                address_of(e2) & kReturnHighBytesMask,
                "D: with no call the dead high bits are the successor's address");
}

// ---------------------------------------------------------------------------
// Case E: the loop bound. The key in the last live element is found; the same key
// one slot beyond the bound is not, and the array is untouched.
// ---------------------------------------------------------------------------
static void case_loop_bound() {
  {
    Fixture f;
    Element* e0 = at(f, 0);
    Element* e1 = at(f, 1);
    Element* e2 = at(f, 2);
    for (int i = 0; i < 3; ++i) {
      set_key(at(f, i), 0x3000u + static_cast<Word>(i));
    }
    arm(f, e0, e2, 2);
    const std::uint8_t result = re_00fa5580(f.receiver(), key_of(e1));
    check_eq_int(result, 1, "E: the last live element (index == count-1) is found");
    check_eq_int(g_seen.shift_calls, 0, "E: and it is the last, so nothing is moved");
  }
  {
    Fixture f;
    Element* e0 = at(f, 0);
    Element* e2 = at(f, 2);
    for (int i = 0; i < 3; ++i) {
      set_key(at(f, i), 0x3000u + static_cast<Word>(i));
    }
    // The key sits in the element at index 2, which is one past the bound the count
    // gives (2 elements live, so indices 0 and 1 are scanned).
    arm(f, e0, e2, 2);
    const std::uint8_t result = re_00fa5580(f.receiver(), key_of(e2));
    check_eq_int(result, 0, "E: the element at index == count is NOT scanned");
    check_eq_int(g_seen.shift_calls, 0, "E: nothing is moved when the key is out of range");
    check_eq_addr(*f.word(kUpper), e2, "E: the array is untouched when nothing matches");
    // The count is 2, and the machine's XOR AL,AL clears the low byte of EAX, so a
    // count below 256 leaves NO dead bits at all. A reconstruction that published
    // the count unshifted (2) or that published the flag byte would differ here; the
    // case where the dead bits are non-zero is case J4, with a count of -258.
    check_eq_word(dead_return_word() & kReturnHighBytesMask, 0u,
                  "E: a count below 256 leaves the dead high bits zero");
  }
}

// ---------------------------------------------------------------------------
// Case A (refutation): count == 0 while the key IS present in element 0. The guard
// at 0x00fa55a6 must stop the scan before it reads anything.
// ---------------------------------------------------------------------------
static void case_empty_guard() {
  {
    Fixture f;
    Element* e0 = at(f, 0);
    Element* e1 = at(f, 1);
    set_key(e0, 0x4444u);
    set_key(e1, 0x5555u);
    // An empty array: begin == end, so the span is 0 and the count is 0.
    arm(f, e0, e0, 0);
    const std::uint8_t result = re_00fa5580(f.receiver(), 0x4444u);
    check_eq_int(result, 0, "A: an empty array never matches, even with the key present");
    check_eq_int(g_seen.shift_calls, 0, "A: and nothing is moved");
    check_eq_word(dead_return_word() & kReturnHighBytesMask, 0u,
                  "A: the dead high bits are a count of 0");
  }
  {
    // A span that is non-zero but short of one stride: the count is 0 again, and
    // this drives the count arithmetic rather than a special case.
    Fixture f;
    Element* e0 = at(f, 0);
    set_key(e0, 0x6666u);
    arm(f, e0, reinterpret_cast<Element*>(reinterpret_cast<std::uint8_t*>(e0) + 1), 0);
    const std::uint8_t result = re_00fa5580(f.receiver(), 0x6666u);
    check_eq_int(result, 0, "A: a sub-stride span gives a count of 0 and no match");
    check_eq_int(g_seen.shift_calls, 0, "A: a sub-stride span moves nothing");
    check_eq_addr(*f.word(kUpper),
                 reinterpret_cast<Element*>(reinterpret_cast<std::uint8_t*>(e0) + 1),
                 "A: a sub-stride span leaves the upper word alone");
  }
}

// ---------------------------------------------------------------------------
// Case F: the key is at the ELEMENT's +0xa8. A key at +0x00 with a decoy at +0xa8
// is not found; the same key at +0xa8 with a decoy at +0x00 is.
// ---------------------------------------------------------------------------
static void case_key_offset() {
  {
    Fixture f;
    Element* e0 = at(f, 0);
    Element* e1 = at(f, 1);
    // The key word is planted at the element's FIRST word, and +0xa8 holds a decoy.
    *reinterpret_cast<Word*>(reinterpret_cast<std::uint8_t*>(e0)) = 0x7777u;
    set_key(e0, 0x9999u);
    set_key(e1, 0xaaaaau);
    arm(f, e0, e1, 1);
    const std::uint8_t result = re_00fa5580(f.receiver(), 0x7777u);
    check_eq_int(result, 0, "F: a key at the element's +0x00 is not the compared word");
    check_eq_int(g_seen.shift_calls, 0, "F: and nothing is moved for it");
    check_eq_addr(*f.word(kUpper), e1, "F: the array is untouched");
  }
  {
    Fixture f;
    Element* e0 = at(f, 0);
    Element* e1 = at(f, 1);
    // The decoy moves to +0x00 and the key to +0xa8: now it must be found.
    *reinterpret_cast<Word*>(reinterpret_cast<std::uint8_t*>(e0)) = 0x9999u;
    set_key(e0, 0x7777u);
    set_key(e1, 0xaaaau);
    arm(f, e0, e1, 1);
    const std::uint8_t result = re_00fa5580(f.receiver(), 0x7777u);
    check_eq_int(result, 1, "F: the same key at the element's +0xa8 IS the compared word");
    check_eq_int(g_seen.shift_calls, 0, "F: the last element is removed without a move");
    check_eq_addr(*f.word(kUpper), e0, "F: and the array shrinks by one stride");
  }
  {
    // A receiver-level decoy: the key word also appears in the receiver's own
    // untouched bytes, which must not be what the search finds.
    Fixture f;
    Element* e0 = at(f, 0);
    Element* e1 = at(f, 1);
    set_key(e0, 0xbbbbu);
    set_key(e1, 0xccccu);
    arm(f, e0, e1, 1);
    *f.word(kDecoyBelow) = 0xbbbbu;  // the key, planted beside the array
    *f.word(kDecoyFar) = 0xbbbbu;
    const std::uint8_t result = re_00fa5580(f.receiver(), 0xbbbbu);
    check_eq_int(result, 1, "F: the key beside the array is not a decoy that changes the arm");
    check_eq_int(g_seen.shift_calls, 0, "F: the match is still the element's own word");
  }
}

// ---------------------------------------------------------------------------
// Case G: write ordering. The callee must be handed the limit as it stood BEFORE
// the decrement, or the number of moves comes out one short.
// ---------------------------------------------------------------------------
static void case_write_ordering() {
  Fixture f;
  Element* e0 = at(f, 0);
  Element* e1 = at(f, 1);
  Element* e2 = at(f, 2);
  Element* e3 = at(f, 3);
  for (int i = 0; i < 4; ++i) {
    set_key(at(f, i), 0x5000u + static_cast<Word>(i));
  }
  arm(f, e0, e3, 3);

  const std::uint8_t result = re_00fa5580(f.receiver(), key_of(e0));

  check_eq_int(result, 1, "G: a match in the first element returns 1");
  check_eq_ptr(g_seen.arg_second, e3, "G: the callee sees the pre-decrement limit");
  check_eq_word(g_seen.upper_at_call, address_of(e3),
                "G: the receiver's +0x79c is still the pre-decrement value inside the call");
  // The read cursor runs from e1 to the limit e3, and the loop stops when it REACHES
  // the limit, so e1 and e2 are read and e3 is not: two moves, and the removed
  // element's own successor is the last one touched. A model that ran the loop one
  // step longer would move three.
  check_eq_int(g_seen.moves, 2, "G: exactly two elements are copied down, not three");
  check_eq_word(key_of(e0), 0x5001u, "G: the second element landed in the first slot");
  check_eq_word(key_of(e1), 0x5002u, "G: the third landed in the second");
  check_eq_word(key_of(e2), 0x5002u, "G: the element at the limit keeps its own bytes");
  check_eq_word(g_seen.decoy_below_at_call, 0xdeadbeefu,
                "G: the decoy below the pair is untouched while the callee runs");
  check_eq_word(g_seen.decoy_above_at_call, 0x0badf00du,
                "G: the decoy above the pair is untouched while the callee runs");
  check_eq_addr(*f.word(kUpper), e2, "G: the decrement happens once, after the call");
  // G: with the match in the FIRST element the callee's return is the new end (e2).
  // The adjacent successor may share its masked high bytes; case K uses a poisoned
  // return to distinguish the callee result from that address without ASLR assumptions.
  check_eq_word(dead_return_word() & kReturnHighBytesMask,
                address_of(e2) & kReturnHighBytesMask,
                "G: the dead high bits are the callee's return (the new end)");
}

// ---------------------------------------------------------------------------
// Case I: the receiver's two words are two different words, and only those two.
// ---------------------------------------------------------------------------
static void case_receiver_pair() {
  Fixture f;
  Element* e0 = at(f, 0);
  Element* e1 = at(f, 1);
  Element* e2 = at(f, 2);
  // A second, decoy pair of words elsewhere in the receiver, holding a plausible
  // array that would match a DIFFERENT key.
  Element* d0 = at(f, 3);
  Element* d1 = at(f, 4);
  set_key(e0, 0x1234u);
  set_key(e1, 0x5678u);
  set_key(d0, 0x9abcu);
  set_key(d1, 0xdef0u);
  arm(f, e0, e2, 2);
  // arm() writes the three decoy words, so the decoy ARRAY is planted after it.
  *f.word(kDecoyFar) = address_of(d0);
  *f.word(kDecoyAbove) = address_of(d1);

  const std::uint8_t result = re_00fa5580(f.receiver(), 0x9abcu);
  check_eq_int(result, 0, "I: a key in a decoy array beside the real one is not found");
  check_eq_int(g_seen.shift_calls, 0, "I: and nothing is moved");
  check_eq_word(*f.word(kDecoyFar), address_of(d0), "I: the decoy pair is untouched");
  check_eq_word(*f.word(kDecoyAbove), address_of(d1), "I: both decoy words are untouched");

  const std::uint8_t second = re_00fa5580(f.receiver(), 0x5678u);
  check_eq_int(second, 1, "I: the real array is still the one that is searched");
}

// ---------------------------------------------------------------------------
// Case J: the count is the six magic instructions, not a C division.
// ---------------------------------------------------------------------------
static void case_count_is_the_magic() {
  // J1: the header's compact form and this file's literal form agree, over a table
  // of spans that includes every interesting boundary.
  static const std::int32_t kSpans[] = {
      0,        1,          0xab,       0xac,        0xad,       0x157,   // 0, 0xac, 2*0xac
      0x158,    0x2a3,      0x2a4,      0x2a5,      -1,         -0xac,   -0x158,
      -0x159,   -0x10000,   -0x2a40000, 0x10000,    0x7fffffff, -0x7fffffff,
  };
  const int kSpanCount = static_cast<int>(sizeof(kSpans) / sizeof(kSpans[0]));
  for (int i = 0; i < kSpanCount; ++i) {
    check_eq_int(element_count_from_span(kSpans[i]), count_by_literal_instructions(kSpans[i]),
                 "J: the two transcriptions of the count agree");
  }
  // J2: for a non-negative span the six instructions ARE the division, so the
  // reconstruction may not differ there.
  for (std::int32_t span = 0; span <= 4096; ++span) {
    check_eq_int(element_count_from_span(span), span / 0xac,
                 "J: a non-negative span counts as span / 0xac");
  }
  // J3: for a NEGATIVE span they are not, and the difference is one. A C division
  // is refuted here, and this is the only channel through which it is observable.
  for (std::int32_t k = 1; k <= 512; ++k) {
    const std::int32_t span = -0xac * k;
    check_eq_int(element_count_from_span(span), -(k + 2),
                 "J: a negative span counts one below the truncating quotient, then one more");
    if (element_count_from_span(span) == (span / 0xac)) {
      std::fprintf(stderr, "FAILED: J: span %d does not separate the magic from the division\n",
                   span);
      ++g_failures;
    }
  }
  // J4: the divergence reaches the caller, through the published return word. The
  // span is -0xac*256 because there the two counts differ in a bit above AL, which
  // is the part of EAX that survives XOR AL,AL.
  {
    Fixture f;
    Element* e0 = at(f, 0);
    // A negative span: the upper word is BELOW the lower word by 256 strides. The
    // two loads are independent, so nothing in the machine stops it.
    Element* const below = reinterpret_cast<Element*>(
        address_of(e0) - 0xac * 256u);
    arm(f, e0, below, -258);
    const std::uint8_t result = re_00fa5580(f.receiver(), 0x1234u);
    check_eq_int(result, 0, "J: a negative span takes the not-found arm");
    check_eq_int(g_seen.shift_calls, 0, "J: a negative span moves nothing");
    check_eq_word(dead_return_word() & kReturnHighBytesMask, 0xfffffe00u,
                  "J: the dead high bits carry the magic count (-258), not the quotient (-256)");
    check(dead_return_word() != (address_of(e0) & kReturnHighBytesMask),
          "J: the negative-span case is distinguishable from the empty case");
  }
}

// ---------------------------------------------------------------------------
// Case K: the callee's return word reaches the caller, so a reconstruction that
// computed the dead half from the successor's address would be caught.
// ---------------------------------------------------------------------------
static void case_dead_bits_follow_the_callee() {
  Fixture f;
  Element* e0 = at(f, 0);
  Element* e1 = at(f, 1);
  Element* e2 = at(f, 2);
  for (int i = 0; i < 3; ++i) {
    set_key(at(f, i), 0x6000u + static_cast<Word>(i));
  }
  arm(f, e0, e2, 2);
  g_seen.poison_return = true;
  g_seen.poison_return_value = 0x00c0ffeeu;
  if ((g_seen.poison_return_value & kReturnHighBytesMask) ==
      (address_of(e1) & kReturnHighBytesMask)) {
    g_seen.poison_return_value ^= 0x01000000u;
  }

  const std::uint8_t result = re_00fa5580(f.receiver(), key_of(e0));

  check_eq_int(result, 1, "K: the match still returns 1 with a poisoned callee return");
  check_eq_int(g_seen.shift_calls, 1, "K: the callee still ran");
  check_eq_word(dead_return_word() & kReturnHighBytesMask,
                g_seen.poison_return_value & kReturnHighBytesMask,
                "K: the dead high bits are whatever the callee returned, with its low byte cleared");
  check(dead_return_word() != ((address_of(e1) & kReturnHighBytesMask) | 1u),
        "K: they are not the successor's address, which is what a reconstruction that "
        "ignored the callee's return would publish");
  g_seen.poison_return = false;
}

// ---------------------------------------------------------------------------
// Case L: the ABI, measured. ECX carries the receiver, the single argument word
// comes over the stack, and the CALLEE pops it.
// ---------------------------------------------------------------------------
static void case_abi_measured() {
  Fixture f;
  Element* e0 = at(f, 0);
  Element* e2 = at(f, 2);
  for (int i = 0; i < 3; ++i) {
    set_key(at(f, i), 0x7000u + static_cast<Word>(i));
  }
  arm(f, e0, e2, 2);

  AbiProbe probe;
  std::memset(&probe, 0xa5, sizeof(probe));
  probe_re_00fa5580(f.receiver(), key_of(e0), &probe);

  // The trampoline samples ESP AFTER pushing the argument word, so a callee that
  // pops it (RET 0x4) leaves ESP four bytes HIGHER than the sample, and a
  // caller-cleaned model would leave the word on the stack and the two samples equal.
  check_eq_int(probe.esp_after - probe.esp_before, 4,
               "L: ESP is four higher after the call, so the CALLEE popped the argument word");
  check_eq_int(static_cast<std::int32_t>(probe.eax & 1u), 1,
               "L: the returned flag arrives in the low byte of the return register");
  check_eq_int(g_seen.shift_calls, 1, "L: the ECX receiver was the receiver, so the match ran");
  check_eq_ptr(g_seen.arg_third, e0, "L: the matched element is the first one");

  // And the miss case, through the same trampoline.
  arm(f, e0, e2, 2);
  std::memset(&probe, 0xa5, sizeof(probe));
  probe_re_00fa5580(f.receiver(), 0x0f0f0f0fu, &probe);
  check_eq_int(probe.esp_after - probe.esp_before, 4,
               "L: the miss path pops the argument word too");
  check_eq_int(static_cast<std::int32_t>(probe.eax & 1u), 0,
               "L: a miss returns 0 in the low byte");
  check_eq_int(g_seen.shift_calls, 0, "L: a miss moves nothing");
}

// ---------------------------------------------------------------------------
// Byte level: nothing on the receiver changes except the four bytes at +0x79c.
// ---------------------------------------------------------------------------
static void case_receiver_bytes() {
  Fixture f;
  Element* e0 = at(f, 0);
  Element* e2 = at(f, 2);
  for (int i = 0; i < 3; ++i) {
    set_key(at(f, i), 0x8000u + static_cast<Word>(i));
  }
  // Fill the whole receiver with a pattern first, so every untouched byte is
  // distinguishable from a zero the model happened to leave.
  for (std::size_t i = 0; i < sizeof(Receiver); ++i) {
    f.arena.bytes[i] = static_cast<std::uint8_t>(0x40u + (i & 0x3fu));
  }
  arm(f, e0, e2, 2);

  std::vector<std::uint8_t> before(f.arena.bytes, f.arena.bytes + sizeof(Receiver));
  const std::uint8_t result = re_00fa5580(f.receiver(), key_of(e0));
  check_eq_int(result, 1, "byte level: the match returns 1");

  int changed = 0;
  for (std::size_t i = 0; i < sizeof(Receiver); ++i) {
    if (f.arena.bytes[i] != before[i]) {
      ++changed;
      if (i < kUpper || i >= kUpper + 4) {
        std::fprintf(stderr, "FAILED: byte level: receiver byte 0x%zx changed outside +0x79c\n", i);
        ++g_failures;
      }
    }
  }
  // The window is four bytes wide, but only the bytes that actually differ are
  // counted: the array moves down by 0xac, so on a typical stack address one or two
  // of them are unchanged. What is asserted is that the change is INSIDE the window,
  // that it is not empty, and (in the cases above) that the word itself took the
  // expected value.
  check(changed >= 1 && changed <= 4,
        "byte level: the change is non-empty and confined to the +0x79c window");
}

// ---------------------------------------------------------------------------
// The count as the body computes it: an independent check that the body and the
// header agree on the span it feeds them, using a receiver whose two words are
// chosen so the span is an exact multiple of the stride.
// ---------------------------------------------------------------------------
static void case_count_matches_the_array() {
  Fixture f;
  Element* e0 = at(f, 0);
  Element* e2 = at(f, 2);
  Element* e3 = at(f, 3);
  for (int i = 0; i < 4; ++i) {
    set_key(at(f, i), 0x9000u + static_cast<Word>(i));
  }
  arm(f, e0, e3, 3);
  // The key is in element 2, the last live one of three.
  const std::uint8_t result = re_00fa5580(f.receiver(), key_of(e2));
  check_eq_int(result, 1, "count: a match at index count-1 is found");
  check_eq_int(g_seen.shift_calls, 0, "count: the last element needs no move");
  check_eq_addr(*f.word(kUpper), e2, "count: and the array shrank by one stride");
  check_eq_word(key_of(e2), 0x9002u, "count: the removed element's bytes stay put");
  check_eq_addr(*f.word(kLower), e0, "count: the lower word never moves");
}

}  // namespace

int model_test_main() {
  case_middle_match();
  case_last_match();
  case_loop_bound();
  case_empty_guard();
  case_key_offset();
  case_write_ordering();
  case_receiver_pair();
  case_count_is_the_magic();
  case_dead_bits_follow_the_callee();
  case_abi_measured();
  case_receiver_bytes();
  case_count_matches_the_array();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("all checks passed\n");
  return 0;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00fa5580

int main() {
  return openspore::reconstruction::pkg_swarm_w1_00fa5580::model_test_main();
}
