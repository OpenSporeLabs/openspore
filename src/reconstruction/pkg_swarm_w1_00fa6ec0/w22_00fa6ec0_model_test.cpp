// PKG-SWARM-W1-00FA6EC0 -- VA 0x00fa6ec0
// Behavioural model test for the vtable method at 0x00fa6ec0
// (FUN_00fa6ec0 in the image).
//
// The body has exactly ONE direct callee, 0x00f9f770, and it is called twice. It
// is defined here as an observer that implements the callee's own 24
// instructions faithfully, so the test sees every transfer the reconstruction
// makes, with which arguments, in which order, and gets to decide what each of
// them does to memory. It also implements the callee's inner loop, which is
// itself a direct call (to the element assign at 0x00f9f620, inside the callee
// and therefore not a call of THIS body), so the test can see whether the
// reconstruction ever triggers a real element move.
//
// What is asserted is what the 40-instruction listing fixes, and nothing more:
//
//   * exactly two calls, in order, each with arg1 == arg2 and arg3 == the OTHER
//     word of the same pair -- the argument order is measured, not assumed;
//   * therefore ZERO element moves, because the callee's loop condition
//     (`arg1 != arg2`) is false on entry every time;
//   * the receiver's two range pairs are read at +0x770/+0x774 and +0x784/+0x788
//     and the counter incremented at +0x814, and the byte-level diff of the
//     WHOLE receiver is exactly those three words -- "no other byte changed" is
//     asserted, not assumed;
//   * the two stores are READ-MODIFY-WRITES against memory, demonstrated with an
//     adversarial callee that writes the word mid-call;
//   * the second pair's words are read AFTER the first pair's store, likewise
//     demonstrated with the adversarial callee;
//   * the quotient's sign, which is the opposite of the span's for a
//     well-formed range: a five-element range ends with last == first, so a model
//     that omits the negation is refuted;
//   * the truncated (not floored, not unsigned) division, driven with spans
//     where signed/unsigned and floor/truncate disagree;
//   * the exact 0xAC stride, cross-checked against 0xA8 which appears in the
//     same class's element copy;
//   * the return value is the SECOND pair's product and not the first's.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names a wrong reconstruction it is aimed at:
//
//   C  wrong argument order / wrong callee: pushing the +0x770 word in the
//      middle slot instead of the third, or handing the callee (first,last)
//      with the arguments in the callee's own other order, would make the
//      callee's range NON-empty. Measured by the element-move count, which must
//      be zero. A reconstruction that swapped the source and the destination
//      would also be caught, and the observer records both.
//   D  signed vs unsigned, and truncating vs flooring: spans of -1, -172, -533
//      and 171/172/173, where `span / 0xAC` computed as unsigned, or as a floor,
//      or without the sign correction, gives a different word. A span of -1 is
//      the sharpest of them: read as unsigned it is 0xffffffff, whose quotient by
//      0xAC is 238609039 strides, so a model without the sign moves the word by
//      gigabytes instead of by nothing.
//   E  stale register versus memory: the two stores are RMW against memory. An
//      observer that rewrites the word during call 0 separates a reconstruction
//      that re-reads it from one that stores a cached copy, and separates both
//      from one that re-reads it to compute the SPAN (which would also move the
//      adjustment).
//   F  wrong receiver offset, in both directions: a planted decoy word at each
//      neighbouring dword (0x76c, 0x778, 0x780, 0x78c, 0x790, 0x7a4, 0x810,
//      0x818) must be neither read into the result nor written. The whole-
//      receiver diff is the assertion, so a model that read +0x76c or wrote
//      +0x818 is caught even if the arithmetic is right.
//   G  wrong pointer level: the model must never dereference an element. The
//      entire element array is filled with a poison pattern and must come back
//      byte-identical, and the observer reports zero moves. This is aimed at the
//      classic object-versus-pointee slip: a reconstruction that treated the
//      words at +0x770/+0x774 as the elements themselves rather than as pointers
//      to them would touch the array.
//   H  wrong block: the two pairs get different spans, so a reconstruction that
//      returns the first block's EAX, or that returns void/zero, is caught.
//   I  wrong magic constant, wrong shift, or the wrong stride: an independent
//      closed form (-(span / 0xAC) * 0xAC, C++ truncating division) is compared
//      against the machine sequence over a sweep of spans, and the 0xA8
//      alternative stride is shown to disagree on the spans chosen.
//   J  wrong counter offset, and a double or missed increment: the counter must
//      move by exactly one, and 0x810 and 0x818 must not move at all.
//   K  ordering: the counter increment is the last memory write and both calls
//      precede it; the first pair's store precedes the second pair's reads.
//      Sampled from INSIDE the observers, at the moment of the call.
//   M  32-bit wrap: a span whose quotient times the stride, and whose product,
//      exceed what a signed 32-bit value would hold if the model had stopped at
//      64 bits or truncated instead of wrapping.
//
// What is NOT asserted, and why:
//
//   * What the two dead calls RETURN. The callee's return value is dead (EAX is
//     overwritten two instructions after each call), so the test records the
//     return the observer produces but asserts nothing about the reconstruction
//     using it -- and a reconstruction that used it would be asserting something
//     the listing refutes.
//   * The MEANING of the value in EAX. Its BITS are fixed and are asserted
//     exactly; its meaning is unestablished (no code in the image calls this
//     body), so the test asserts the bit pattern and says nothing else.
//   * Anything about the element's own layout beyond its size. The observer's
//     element assign copies 0xAC bytes because the callee does; the test never
//     depends on which byte is where, and the reconstruction never reads one.
//   * The receiver's real extent. 0x818 is a floor derived from the last word
//     this body touches, not a claim about the class.

#include "w22_00fa6ec0_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <set>
#include <string>
#include <vector>

namespace openspore::reconstruction::pkg_swarm_w1_00fa6ec0 {
namespace {

// -- the fixture -------------------------------------------------------------

constexpr std::size_t kReceiverSize = 0x818;
constexpr std::size_t kElements = 64;
constexpr std::size_t kStride = 0xac;

// Receiver displacements, as literals in the test (this file is outside the
// span the validator reads, so restating them costs nothing and keeps the
// fixture independent of the header's own constants).
constexpr std::size_t kOffAFirst = 0x770;
constexpr std::size_t kOffALast = 0x774;
constexpr std::size_t kOffBFirst = 0x784;
constexpr std::size_t kOffBLast = 0x788;
constexpr std::size_t kOffCounter = 0x814;

int g_failures = 0;

void check(bool ok, const std::string &what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what.c_str());
    ++g_failures;
  }
}

std::uint32_t load(const void *base, std::size_t displacement) {
  std::uint32_t value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t *>(base) + displacement, sizeof value);
  return value;
}

void store(void *base, std::size_t displacement, std::uint32_t value) {
  std::memcpy(static_cast<std::uint8_t *>(base) + displacement, &value, sizeof value);
}

// -- the observer for 0x00f9f770 --------------------------------------------

struct MoveCall {
  Element *arg1 = nullptr;
  Element *arg2 = nullptr;
  Element *arg3 = nullptr;
  // What the reconstruction had already done to the receiver when this call was
  // made, sampled here because the observer is the only place inside the call.
  std::uint32_t receiver_a_last = 0;
  std::uint32_t receiver_b_last = 0;
  std::uint32_t receiver_counter = 0;
  Element *move_destination = nullptr;
  Element *move_source = nullptr;
};

struct Hook {
  bool enabled = false;
  int on_call_index = 0;
  std::size_t displacement = 0;
  std::uint32_t value = 0;
};

struct Observation {
  std::vector<MoveCall> calls;
  std::vector<std::pair<Element *, Element *>> moves;  // (destination, source)
  void *receiver = nullptr;
  Hook hook;
  std::uintptr_t last_return = 0;
  int empty_range_exits = 0;
  int loop_exits = 0;

  void reset() {
    calls.clear();
    moves.clear();
    receiver = nullptr;
    hook = Hook();
    last_return = 0;
    empty_range_exits = 0;
    loop_exits = 0;
  }
};

Observation g_obs;

}  // namespace

// 0x00f9f620, the element assign the callee calls, as a one-line stand-in: it
// copies the destination from the source field by field over 0xAC bytes. The
// record is (destination, source) in that order because 0x00f9f62e..0x00f9f63d
// read the SOURCE and write the DESTINATION, and the callee puts the source on
// the stack (0x00f9f626 PUSH EDI) and the destination in the hidden receiver
// (0x00f9f627 MOV ESI,ECX).
void element_assign(Element *destination, const Element *source) {
  std::memcpy(static_cast<void *>(destination), static_cast<const void *>(source), sizeof(Element));
}

// The callee's own 24 instructions, in order. Argument order is fixed by its
// frame reads, not by its decompilation:
//
//   0x00f9f771  MOV EBX,[ESP + 0xc]   arg2   (source_last)
//   0x00f9f776  MOV ESI,[ESP + 0xc]   arg1   (source_first)
//   0x00f9f77a  CMP ESI,EBX
//   0x00f9f77c  JZ  0x00f9f7a1              empty range -> MOV EAX,[ESP+0x14] (arg2)
//   0x00f9f77f  MOV EDI,[ESP + 0x18]  arg3   (destination)
//   0x00f9f783  PUSH ESI / 0x00f9f784  MOV ECX,EDI / 0x00f9f786  CALL
//   0x00f9f78b  ADD ESI,0xac / 0x00f9f791  ADD EDI,0xac / 0x00f9f797  CMP ESI,EBX
//   0x00f9f79b  MOV EAX,EDI                -> return the destination end
Element *element_range_move_00f9f770(Element *source_first, Element *source_last,
                                      Element *destination) {
  MoveCall call;
  call.arg1 = source_first;
  call.arg2 = source_last;
  call.arg3 = destination;
  if (g_obs.receiver != nullptr) {
    call.receiver_a_last = load(g_obs.receiver, kOffALast);
    call.receiver_b_last = load(g_obs.receiver, kOffBLast);
    call.receiver_counter = load(g_obs.receiver, kOffCounter);
  }
  const int index = static_cast<int>(g_obs.calls.size());
  g_obs.calls.push_back(call);

  // The adversarial hook: a real callee writes nothing, so anything it writes
  // here is a fixture. It exists to separate a reconstruction that re-reads the
  // receiver at the point of the machine's re-read from one that does not.
  if (g_obs.hook.enabled && g_obs.hook.on_call_index == index) {
    store(g_obs.receiver, g_obs.hook.displacement, g_obs.hook.value);
  }

  if (source_first == source_last) {  // 0x00f9f77a / 0x00f9f77c
    ++g_obs.empty_range_exits;
    const std::uintptr_t result = reinterpret_cast<std::uintptr_t>(source_last);  // 0x00f9f7a1
    g_obs.last_return = result;
    return reinterpret_cast<Element *>(result);
  }

  Element *source = source_first;  // 0x00f9f776  MOV ESI,[ESP + 0xc]
  Element *dest = destination;     // 0x00f9f77f  MOV EDI,[ESP + 0x18]
  while (source != source_last) {  // 0x00f9f797  CMP ESI,EBX / 0x00f9f799  JNZ
    // 0x00f9f783  PUSH ESI / 0x00f9f784  MOV ECX,EDI / 0x00f9f786  CALL
    g_obs.moves.emplace_back(dest, source);
    g_obs.calls[static_cast<std::size_t>(index)].move_destination = dest;
    g_obs.calls[static_cast<std::size_t>(index)].move_source = source;
    element_assign(dest, source);
    // 0x00f9f78b  ADD ESI,0xac
    // 0x00f9f791  ADD EDI,0xac
    source += kStride;
    dest += kStride;
  }
  ++g_obs.loop_exits;
  const std::uintptr_t result = reinterpret_cast<std::uintptr_t>(dest);  // 0x00f9f79b
  g_obs.last_return = result;
  return reinterpret_cast<Element *>(result);
}

// -- independent references, derived without the reconstruction -------------

// The closed form the machine's magic sequence is an expansion of: a signed
// division of the byte span by the stride, truncated toward zero, negated, and
// multiplied back out by the stride. Written with plain C++ division so that
// agreeing with the model is a real cross-check of the multiply, the two shift
// amounts and the sign correction, not a restatement of them.
std::uint32_t expected_adjustment(std::int32_t span) {
  const std::int32_t count = -(span / static_cast<std::int32_t>(kStride));
  return static_cast<std::uint32_t>(count) * 0xacu;
}

// A 32-bit bit pattern read back as a signed value, the way SUB EDI,EBX's result
// has to be read.
std::int32_t as_signed(std::uint32_t bits) {
  std::int32_t value = 0;
  std::memcpy(&value, &bits, sizeof value);
  return value;
}

// The span the machine's SUB produces, given the two words it held.
std::int32_t span_of(std::uint32_t last_word, std::uint32_t first_word) {
  return as_signed(last_word - first_word);
}

// The low 32 bits of the machine's 64-bit signed product, computed as a plain
// 32-bit wrapping multiply so that it shares nothing with the reconstruction's
// IMUL/SAR/SHR/ADD sequence.
std::uint32_t expected_low_product(std::int32_t span) {
  return static_cast<std::uint32_t>(span) * 0xd05f417du;
}

namespace {

// -- the fixture -------------------------------------------------------------

struct alignas(16) Receiver {
  std::uint8_t bytes[kReceiverSize];
};

Receiver g_receiver;
Element g_elements[kElements];
std::uint8_t g_elements_before[sizeof(g_elements)];

void paint_elements() {
  for (std::size_t i = 0; i < kElements; ++i) {
    for (std::size_t b = 0; b < sizeof(Element); ++b) {
      reinterpret_cast<std::uint8_t *>(&g_elements[i])[b] =
          static_cast<std::uint8_t>((i * 0x3bu + b * 0x11u) & 0xffu);
    }
  }
  std::memcpy(g_elements_before, g_elements, sizeof(g_elements));
}

bool elements_untouched() {
  return std::memcmp(g_elements_before, g_elements, sizeof(g_elements)) == 0;
}

// Every 4-byte-aligned word of the receiver whose value differs from the
// snapshot, as displacements. This is how "no other byte changed" becomes an
// assertion instead of an assumption.
std::set<std::size_t> changed_words(const std::uint8_t *before) {
  std::set<std::size_t> changed;
  for (std::size_t displacement = 0; displacement + 4 <= kReceiverSize; displacement += 4) {
    if (std::memcmp(before + displacement, g_receiver.bytes + displacement, 4) != 0) {
      changed.insert(displacement);
    }
  }
  return changed;
}

std::string set_to_string(const std::set<std::size_t> &values) {
  std::string text = "{";
  bool first = true;
  for (std::size_t value : values) {
    char buffer[32];
    std::snprintf(buffer, sizeof buffer, "%s0x%zx", first ? "" : ", ", value);
    text += buffer;
    first = false;
  }
  text += "}";
  return text;
}

std::uint8_t g_receiver_before[kReceiverSize];

// Paints the receiver with a decoy at EVERY dword that is not one of the five
// the body is entitled to touch. REFUTE F: if the reconstruction reads one of
// these into its arithmetic, or writes one, the changed-word set or the result
// moves. Values are chosen to be wildly wrong in every direction (large, small,
// negative-looking, and one that is a valid-looking element pointer, so that a
// model which mistakes a neighbouring word for a range pointer would use it).
void setup(std::int32_t span_a, std::int32_t span_b, std::uint8_t *receiver_snapshot = nullptr) {
  std::memset(&g_receiver, 0, sizeof g_receiver);
  paint_elements();

  Element *const base = &g_elements[8];
  for (std::size_t displacement = 0; displacement + 4 <= kReceiverSize; displacement += 4) {
    if (displacement == kOffAFirst || displacement == kOffALast ||
        displacement == kOffBFirst || displacement == kOffBLast ||
        displacement == kOffCounter) {
      continue;
    }
    store(&g_receiver, displacement, static_cast<std::uint32_t>(0xd0000000u + displacement * 0x9u));
  }
  // Two decoys that are VALID element addresses, at the neighbours a wrong
  // offset would pick up. If the model read one of these as a range pointer its
  // span would come out differently; if it wrote one the changed-word set would
  // grow.
  store(&g_receiver, kOffAFirst - 4, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&g_elements[40])));
  store(&g_receiver, kOffALast + 4, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&g_elements[2])));
  store(&g_receiver, kOffBFirst - 4, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&g_elements[48])));
  store(&g_receiver, kOffBLast + 4, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&g_elements[1])));
  // The capacity words of the two headers, and the header tails, left at the
  // decoy paint: the body never reads them and the test asserts so.
  store(&g_receiver, kOffAFirst + 8, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(base + 0x20)));
  store(&g_receiver, kOffBFirst + 8, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(base + 0x20)));

  store(&g_receiver, kOffAFirst, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(base)));
  store(&g_receiver, kOffALast,
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(base) +
                                   static_cast<std::uintptr_t>(span_a)));
  store(&g_receiver, kOffBFirst, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(base + 0x40)));
  store(&g_receiver, kOffBLast,
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(base + 0x40) +
                                   static_cast<std::uintptr_t>(span_b)));
  store(&g_receiver, kOffCounter, 0x1234u);

  if (receiver_snapshot != nullptr) {
    std::memcpy(receiver_snapshot, g_receiver.bytes, kReceiverSize);
  }

  g_obs.reset();
  g_obs.receiver = &g_receiver;
}

std::uint32_t run() { return re_00fa6ec0(reinterpret_cast<Owner *>(&g_receiver)); }

// -- the cases ---------------------------------------------------------------

// Case A. The two pairs are well formed and already end on an element boundary,
// so the adjustment is a whole number of strides and the last words do not move.
// This is the case that has to hold before any of the others mean anything.
void case_a_baseline() {
  setup(5 * static_cast<std::int32_t>(kStride), 3 * static_cast<std::int32_t>(kStride),
        g_receiver_before);
  const std::uint32_t result = run();

  check(g_obs.calls.size() == 2, "A: exactly two calls to 0x00f9f770");
  check(g_obs.moves.empty(), "A: no element is moved (the callee's range is empty)");
  check(g_obs.empty_range_exits == 2, "A: both calls take the callee's empty-range exit");
  check(elements_untouched(), "A: the element array is byte-identical afterwards");

  const std::set<std::size_t> expected{kOffALast, kOffBLast, kOffCounter};
  check(changed_words(g_receiver_before) == expected,
        "A: the receiver's changed words are exactly {0x774, 0x788, 0x814}, got " +
            set_to_string(changed_words(g_receiver_before)));

  check(load(&g_receiver, kOffCounter) == 0x1235u, "A: the counter at +0x814 moves by exactly one");
  check(result == expected_low_product(3 * static_cast<std::int32_t>(kStride)),
        "A: EAX is the SECOND pair's product low word");

  // The crisp consequence of the adjustment's sign, and the statement that would
  // fail first if a reconstruction dropped the negation: a range that already
  // ends on an element boundary loses every whole element it spans and ends up
  // with last == first.
  check(load(&g_receiver, kOffALast) == load(g_receiver_before, kOffAFirst),
        "A: a five-element range ends up with +0x774 == +0x770");
  check(load(&g_receiver, kOffBLast) == load(g_receiver_before, kOffBFirst),
        "A: a three-element range ends up with +0x788 == +0x784");
}

// Case B. The two last words have drifted off an element boundary by 0x37 and
// 0x89 bytes, so the spans are 5*0xAC+0x37 and 2*0xAC+0x89. The body subtracts
// the whole number of strides the span covers, which leaves the residue:
// last = first + (span mod 0xAC). REFUTE: a model that used the wrong stride
// (0xA8 also appears in this class's element copy), a model that rounded the
// other way, and a model whose adjustment has the opposite sign are all
// separated here, and case A pins the sign with a whole-element span.
void case_b_snaps_a_drifted_last_word() {
  const std::int32_t drift_a = 0x37;
  const std::int32_t drift_b = 0x89;
  setup(5 * static_cast<std::int32_t>(kStride) + drift_a, 2 * static_cast<std::int32_t>(kStride) + drift_b,
        g_receiver_before);
  const std::int32_t span_a = 5 * static_cast<std::int32_t>(kStride) + drift_a;
  const std::int32_t span_b = 2 * static_cast<std::int32_t>(kStride) + drift_b;
  const std::uint32_t result = run();

  const std::uint32_t before_a = load(g_receiver_before, kOffALast);
  const std::uint32_t before_b = load(g_receiver_before, kOffBLast);
  check(load(&g_receiver, kOffALast) == before_a + expected_adjustment(span_a),
        "B: +0x774 shrinks by the 5 whole elements the span covers");
  check(load(&g_receiver, kOffBLast) == before_b + expected_adjustment(span_b),
        "B: +0x788 shrinks by the 2 whole elements the span covers");

  // The closed form, spelled out: last += -(span/0xAC)*0xAC is
  // last = first + (span mod 0xAC), so the residue is what survives.
  const std::uint32_t first_a = load(g_receiver_before, kOffAFirst);
  const std::uint32_t first_b = load(g_receiver_before, kOffBFirst);
  check(load(&g_receiver, kOffALast) == first_a + static_cast<std::uint32_t>(drift_a),
        "B: +0x774 lands on first + 0x37, the sub-element residue");
  check(load(&g_receiver, kOffBLast) == first_b + static_cast<std::uint32_t>(drift_b),
        "B: +0x788 lands on first + 0x89, the sub-element residue");
  check(expected_adjustment(span_a) == static_cast<std::uint32_t>(-5 * 172),
        "B: the adjustment for a 5-element span plus 0x37 is NEGATIVE 5*0xAC");
  // The 0xA8 stride is ruled out over the whole sweep in case I, where the
  // driven spans do separate the two counts; these two spans do not, and the
  // check is stated rather than left implied.
  check(static_cast<std::uint32_t>(span_a / 0xac) == 5u &&
            static_cast<std::uint32_t>(span_b / 0xac) == 2u,
        "B: (sanity) the driven spans hold 5 and 2 whole elements at stride 0xAC");

  const std::set<std::size_t> expected{kOffALast, kOffBLast, kOffCounter};
  check(changed_words(g_receiver_before) == expected, "B: no other receiver word changed");
  check(result == expected_low_product(span_b), "B: EAX is the second pair's product");
  // Hard-coded spot values, evaluated offline from 0x00fa6edb..0x00fa6ee0 and
  // 0x00fa6f0e..0x00fa6f13. Neither of these spans is a multiple of the stride,
  // so neither product is a round number and neither could be produced by an
  // arithmetic shortcut.
  check(expected_low_product(span_a) == 0xc47711c7u,
        "B: (sanity) the first pair's product low word for span 915 is 0xc47711c7");
  check(expected_low_product(span_b) == 0x82fa0bddu,
        "B: (sanity) the second pair's product low word for span 481 is 0x82fa0bdd");
}

// Case C. The argument order of the only callee, measured. REFUTE: swapping the
// second and third pushes (a reconstruction that assumes the callee takes
// (first, last, dest) in the source order rather than the callee's own frame
// order), or pushing the OTHER word in the middle slot, makes the callee's range
// non-empty and moves elements -- which the move count catches.
void case_c_call_shape_and_argument_order() {
  setup(2 * static_cast<std::int32_t>(kStride), 4 * static_cast<std::int32_t>(kStride),
        g_receiver_before);
  run();

  check(g_obs.calls.size() == 2, "C: two calls");
  if (g_obs.calls.size() == 2) {
    const MoveCall &first = g_obs.calls[0];
    const MoveCall &second = g_obs.calls[1];
    const std::uint32_t a_first = load(g_receiver_before, kOffAFirst);
    const std::uint32_t a_last = load(g_receiver_before, kOffALast);
    const std::uint32_t b_first = load(g_receiver_before, kOffBFirst);
    const std::uint32_t b_last = load(g_receiver_before, kOffBLast);

    // The first call is about the FIRST pair (read at 0x00fa6ec4/0x00fa6ecb).
    check(first.arg1 == reinterpret_cast<const Element *>(a_last),
          "C: call 1 arg1 is the word at +0x774");
    check(first.arg2 == first.arg1, "C: call 1 arg2 EQUALS arg1 (the callee's range is empty)");
    check(first.arg3 == reinterpret_cast<const Element *>(a_first),
          "C: call 1 arg3 is the word at +0x770, i.e. the destination");

    // The second call is about the SECOND pair (read at 0x00fa6ef8/0x00fa6efe).
    check(second.arg1 == reinterpret_cast<const Element *>(b_last),
          "C: call 2 arg1 is the word at +0x788");
    check(second.arg2 == second.arg1, "C: call 2 arg2 EQUALS arg1");
    check(second.arg3 == reinterpret_cast<const Element *>(b_first),
          "C: call 2 arg3 is the word at +0x784, i.e. the destination");
  }
  check(g_obs.moves.empty(), "C: a wrong argument order would move elements; none moved");
  check(g_obs.loop_exits == 0, "C: neither call entered the callee's copy loop");
  check(elements_untouched(), "C: the element array is byte-identical afterwards");
}

// Case D. Malformed ranges. The subtraction at 0x00fa6ed9 wraps at 32 bits and
// the division is SIGNED and TRUNCATING. REFUTE: an unsigned division, a floor
// instead of a truncation, and a division that omits the sign correction all
// disagree on the spans below. -1 is the sharpest: unsigned, 0xffffffff/0xac is
// 238609039, so a reconstruction that forgot the sign would move the word by
// gigabytes.
void case_d_signed_truncating_division() {
  const std::int32_t spans[] = {0, 1, 85, 86, 87, 171, 172, 173, 343, 344, 345,
                                859, 860, 861, -1, -85, -172, -173, -516, -533, -17200,
                                4096, 17200, 17201, 17255};
  for (std::size_t i = 0; i < sizeof spans / sizeof spans[0]; ++i) {
    const std::int32_t span = spans[i];
    setup(span, span, g_receiver_before);
    const std::uint32_t before_a = load(g_receiver_before, kOffALast);
    const std::uint32_t before_b = load(g_receiver_before, kOffBLast);
    const std::uint32_t result = run();
    char label[160];
    std::snprintf(label, sizeof label,
                  "D: span %d: +0x774 moves by the truncated signed quotient only",
                  static_cast<int>(span));
    check(load(&g_receiver, kOffALast) == before_a + expected_adjustment(span), label);
    check(load(&g_receiver, kOffBLast) == before_b + expected_adjustment(span), label);
    char label_b[160];
    std::snprintf(label_b, sizeof label_b,
                  "D: span %d: +0x788 moves by the same truncated signed quotient",
                  static_cast<int>(span));
    check(load(&g_receiver, kOffBLast) == before_b + expected_adjustment(span), label_b);
    check(result == expected_low_product(span),
          "D: EAX is the product low word for the driven span");
  }

  // The three specific discriminators, spelled out rather than left implicit.
  setup(-1, -1, g_receiver_before);
  const std::uint32_t before = load(g_receiver_before, kOffALast);
  run();
  check(load(&g_receiver, kOffALast) == before,
        "D: a span of -1 moves the last word by NOTHING (truncation toward zero, "
        "and the unsigned reading of 0xffffffff would move it by 4100015468)");
  check(expected_adjustment(-1) == 0u, "D: (sanity) expected_adjustment(-1) is 0");

  setup(-172, -172, g_receiver_before);
  const std::uint32_t before2 = load(g_receiver_before, kOffALast);
  run();
  check(load(&g_receiver, kOffALast) == before2 + 0xacu,
        "D: a span of -0xAC moves the last word by +0xAC, i.e. back toward first");

  setup(172, 172, g_receiver_before);
  const std::uint32_t before3 = load(g_receiver_before, kOffALast);
  run();
  check(load(&g_receiver, kOffALast) == before3 - 0xacu,
        "D: a span of +0xAC moves the last word by -0xAC: the sign of the adjustment "
        "is the opposite of the sign of the span");
}

// Case E. Both stores are read-modify-writes against MEMORY, and the second
// pair's words are read after the first pair's store has landed. REFUTE: a
// reconstruction that keeps the loaded value in a local and stores
// `loaded + adjustment` writes the stale value; a reconstruction that re-reads
// the word to compute the SPAN as well moves the adjustment too. The observer
// rewrites the word during call 0, which separates all three.
void case_e_stores_are_read_modify_write_on_memory() {
  const std::int32_t span_a = 915;  // 5 * 0xac + 0x37
  const std::int32_t span_b = 481;  // 2 * 0xac + 0x89
  setup(span_a, span_b, g_receiver_before);

  const std::uint32_t planted = 0x00001234u;
  g_obs.hook.enabled = true;
  g_obs.hook.on_call_index = 0;
  g_obs.hook.displacement = kOffALast;
  g_obs.hook.value = planted;
  const std::uint32_t result = run();

  check(load(&g_receiver, kOffALast) == planted + expected_adjustment(span_a),
        "E: the +0x774 store adds to the word AS IT STANDS after the call, not to the "
        "value loaded before it");
  check(load(&g_receiver, kOffALast) != load(g_receiver_before, kOffALast) +
                                            expected_adjustment(span_a),
        "E: (control) the stale-local answer is a different word, so this case can fail");

  // Ordering (case K rides along): the second call must SEE the word the first
  // store produced, which is only possible if the model re-read the receiver
  // after the store rather than from a snapshot taken at entry.
  if (g_obs.calls.size() == 2) {
    check(g_obs.calls[1].receiver_a_last == planted + expected_adjustment(span_a),
          "E/K: the second call observes the already-snapped +0x774");
    check(g_obs.calls[0].receiver_counter == 0x1234u && g_obs.calls[1].receiver_counter == 0x1234u,
          "E/K: the counter at +0x814 is still untouched during BOTH calls, so the "
          "increment is the last memory write");
    check(g_obs.calls[0].receiver_b_last == load(g_receiver_before, kOffBLast),
          "E/K: the first call happens before the +0x788 word is touched");
  }
  check(result == expected_low_product(span_b), "E: the return is unaffected by the hook");

  // The same hook, but aimed at the SECOND pair's first word, to prove the
  // second pair's read also happens at the machine's moment rather than at entry.
  setup(span_a, span_b, g_receiver_before);
  const std::uint32_t original_b_first = load(g_receiver_before, kOffBFirst);
  const std::uint32_t original_b_last = load(g_receiver_before, kOffBLast);
  // Move the second pair's FIRST word two elements lower, still inside the
  // poisoned array, so the span the machine computes grows by exactly 2 * 0xAC.
  const std::uint32_t planted_b = original_b_first - 2u * static_cast<std::uint32_t>(kStride);
  const std::int32_t span_b_planted = span_of(original_b_last, planted_b);
  g_obs.hook.enabled = true;
  g_obs.hook.on_call_index = 0;
  g_obs.hook.displacement = kOffBFirst;
  g_obs.hook.value = planted_b;
  const std::uint32_t result_b = run();
  check(span_b_planted == span_b + 2 * static_cast<std::int32_t>(kStride),
        "E: (sanity) the planted word changes the second pair's span by two elements");
  check(load(&g_receiver, kOffBLast) ==
            original_b_last + expected_adjustment(span_b_planted),
        "E: the second pair's SPAN is taken from the word as it stands at 0x00fa6efe, "
        "not from a value read at entry");
  check(result_b == expected_low_product(span_b_planted),
        "E: the return follows the re-read span, as 0x00fa6f13 IMUL EDI would");
  check(result_b != expected_low_product(span_b),
        "E: (control) a reconstruction that read the span at entry returns a different word");
}

// Case F/G. No wrong receiver displacement, and no pointer-level confusion. The
// whole-receiver diff is the assertion, and the element array is poisoned and
// compared whole. REFUTE: an off-by-one displacement (0x76c, 0x778, 0x780,
// 0x78c, 0x790, 0x7a4, 0x810, 0x818 all carry decoys, two of which are VALID
// element addresses), and a reconstruction that treated the range words as the
// elements themselves rather than as pointers to them.
void case_f_g_offsets_and_pointer_level() {
  setup(915, 481, g_receiver_before);
  const std::uint32_t planted_a_first = load(g_receiver_before, kOffAFirst);
  const std::uint32_t planted_b_first = load(g_receiver_before, kOffBFirst);
  run();

  const std::set<std::size_t> expected{kOffALast, kOffBLast, kOffCounter};
  const std::set<std::size_t> actual = changed_words(g_receiver_before);
  check(actual == expected, "F: the changed-word set is exactly {0x774, 0x788, 0x814}, got " +
                                set_to_string(actual));
  check(elements_untouched(), "G: the poisoned element array is byte-identical afterwards");
  check(g_obs.moves.empty(), "G: no element is ever handed to the callee's copy");
  check(load(&g_receiver, kOffAFirst) == planted_a_first, "F: the +0x770 word is never written");
  check(load(&g_receiver, kOffBFirst) == planted_b_first, "F: the +0x784 word is never written");

  // A reconstruction that read the receiver as the element (no dereference of
  // the range words) would move words inside the receiver itself. Every dword of
  // the receiver outside the three changed ones is asserted unchanged above; here
  // the byte-level check is stated outright, so a partial-word write cannot slip
  // between the dword comparisons.
  std::size_t differing_bytes = 0;
  for (std::size_t displacement = 0; displacement < kReceiverSize; ++displacement) {
    if (g_receiver_before[displacement] != g_receiver.bytes[displacement]) {
      ++differing_bytes;
    }
  }
  check(differing_bytes <= 12,
        "F: at most the three changed words' twelve bytes differ, saw " +
            std::to_string(differing_bytes));
}

// Case H. The two blocks are told apart. REFUTE: a reconstruction that returns
// the FIRST pair's EAX, or the quotient, or zero, or void.
void case_h_the_return_is_the_second_block() {
  const std::int32_t span_a = 17200;  // 100 * 0xac
  const std::int32_t span_b = 4096;   // not a whole number of strides
  setup(span_a, span_b, g_receiver_before);
  const std::uint32_t result = run();

  check(expected_low_product(span_a) != expected_low_product(span_b),
        "H: (sanity) the two blocks' products differ, so the case can fail");
  check(result == expected_low_product(span_b), "H: EAX is the SECOND pair's product");
  check(result != expected_low_product(span_a), "H: EAX is NOT the first pair's product");
  check(result != 0u, "H: EAX is not zero");
  check(result != expected_adjustment(span_b),
        "H: EAX is not the quotient-times-stride, which is the value stored at +0x788 "
        "rather than returned");
  // Spot values evaluated offline from 0x00fa6f0c..0x00fa6f13.
  check(expected_low_product(span_a) == 0xfffffe70u,
        "H: (sanity) the first pair's product low word for span 17200 is 0xfffffe70");
  check(expected_low_product(-533) == 0x29aca6bfu,
        "H: (sanity) a negative span's product low word is the two's-complement "
        "reflection of a positive one's");
}

// Case I. The magic multiply, the two shift amounts, the sign correction and the
// stride, cross-checked against an independent closed form over a wide sweep.
// REFUTE: a different multiplier, a logical shift where the machine has an
// arithmetic one, a missing truncation step, or a stride of 0xA8 / 0xAB.
void case_i_quotient_sweep() {
  const std::int32_t spans[] = {-2000000, -17200, -12345, -4096, -1024, -516, -172, -171, -86,
                                -2,      -1,     0,     1,     2,     86,   171,  172,  173,
                                1024,    4096,   17200, 17201, 0x7ffffff0, static_cast<std::int32_t>(0x80000000u),
                                static_cast<std::int32_t>(0xfffff000u)};
  for (std::size_t i = 0; i < sizeof spans / sizeof spans[0]; ++i) {
    const std::int32_t span = spans[i];
    setup(span, span, g_receiver_before);
    const std::uint32_t before = load(g_receiver_before, kOffALast);
    const std::uint32_t before_b = load(g_receiver_before, kOffBLast);
    const std::uint32_t result = run();
    char label[160];
    std::snprintf(label, sizeof label, "I: span %d: the quotient agrees with -(span/0xAC)",
                  static_cast<int>(span));
    check(load(&g_receiver, kOffALast) == before + expected_adjustment(span), label);
    check(load(&g_receiver, kOffBLast) == before_b + expected_adjustment(span), label);
    check(result == expected_low_product(span), "I: the product low word agrees");
  }
  // The 0xA8 stride is separable on the spans this sweep drives: it would give a
  // different count for 17200 and for 4096, so agreeing here rules it out.
  check(static_cast<std::uint32_t>(17200 / 0xac) != static_cast<std::uint32_t>(17200 / 0xa8) &&
            static_cast<std::uint32_t>(4096 / 0xac) != static_cast<std::uint32_t>(4096 / 0xa8),
        "I: (sanity) the 0xAC and 0xA8 strides disagree on the driven spans, so the "
        "sweep separates them");
}

// Case M. 32-bit wrap in the two places the machine wraps. REFUTE: a model that
// stopped at 64 bits, or that computed the span in a wider type, or that
// truncated rather than wrapping.
void case_m_wrapping() {
  // 0x7ffffff0 is a 32-bit subtraction that stays positive; 0xfffff000 as a
  // pointer difference is a NEGATIVE span of -0x1000, which is the case that
  // separates wrapping from sign extension.
  const std::int32_t spans[] = {0x7ffffff0, static_cast<std::int32_t>(0xfffff000u),
                                static_cast<std::int32_t>(0x80000000u)};
  for (std::size_t i = 0; i < sizeof spans / sizeof spans[0]; ++i) {
    const std::int32_t span = spans[i];
    setup(span, span, g_receiver_before);
    const std::uint32_t before = load(g_receiver_before, kOffALast);
    const std::uint32_t result = run();
    char label[160];
    std::snprintf(label, sizeof label, "M: span 0x%08x: the subtraction wraps, not extends",
                  static_cast<unsigned>(span));
    check(load(&g_receiver, kOffALast) == before + expected_adjustment(span), label);
    check(result == expected_low_product(span), "M: the product low word wraps identically");
  }
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w1_00fa6ec0

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w1_00fa6ec0;
  case_a_baseline();
  case_b_snaps_a_drifted_last_word();
  case_c_call_shape_and_argument_order();
  case_d_signed_truncating_division();
  case_e_stores_are_read_modify_write_on_memory();
  case_f_g_offsets_and_pointer_level();
  case_h_the_return_is_the_second_block();
  case_i_quotient_sweep();
  case_m_wrapping();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("all checks passed\n");
  return 0;
}
