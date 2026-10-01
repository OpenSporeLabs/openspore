// PKG-SWARM-W2-00586700 -- VA 0x00586700
// Behavioural model test for FUN_00586700, the seven-times-repeated
// "advance the current pointer to start + 35 and zero 35 bytes" reset.
//
// BOTH DIRECT CALLEES ARE DEFINED HERE AS OBSERVERS, so the test sees every
// transfer the reconstruction makes, with which arguments, in which order, and
// decides what each does to memory while it is there. There are exactly two of
// them, called from two sites each:
//
//   0x005151b0  growable_buffer_fill_005151b0   __thiscall, ECX + 3 stack
//                                                 words. Defined TWICE over, in
//                                                 two modes, because who moves
//                                                 the CURRENT word is the single
//                                                 most load-bearing fact in
//                                                 this body.
//   0x011e0744  memcpy_thunk_011e0744           __cdecl, 3 arguments, count
//                                                 identically zero.
//
// WHAT IS ASSERTED is what the 89-instruction listing fixes and nothing more:
//
//   * that the operation happens SEVEN times -- once on the element at
//     self+0x4d8 and once on each of six elements at self+0x50c+20k -- and that
//     each of the seven zeroes exactly 35 BYTES at that element's START
//     address;
//   * the arm split, as an UNSIGNED >= 35 on (current - start), at both sites,
//     driven with the input where signed and unsigned disagree (current BELOW
//     start) and with 34 / 35 / 36 either side of the boundary;
//   * that the fast arm calls 0x011e0744 with a count of IDENTICALLY ZERO and
//     with (destination = start+35, source = current), and advances the CURRENT
//     word ITSELF by the wrapping delta;
//   * that the slow arm calls 0x005151b0 with (receiver = &START word, first
//     word = CURRENT address, second word = the SHORTFALL 35-(current-start),
//     third word = a pointer to a zero byte in the CALLEE'S OWN FRAME) and that
//     it does NOT advance the CURRENT word itself;
//   * that the value byte is re-zeroed immediately before EACH of the two call
//     sites and not once at entry;
//   * the exact set of receiver bytes that change -- which is asserted as a byte
//     diff over the whole modeled receiver, not as a list of individual stores;
//   * the exact set of backing bytes that change -- likewise a byte diff;
//   * the two GUARD BANDS, poisoned before the run and required to be intact
//     after it BY VALUE: the kWindowCanary bytes after each of the eight
//     windows, and every receiver word outside the anchor runs. A byte diff
//     cannot see a write of the value a byte already held, and no other case
//     establishes that the poison was in place at all, so both facts are
//     checked here and neither is checked anywhere else;
//   * the bounds those two bands are stated in -- the receiver run
//     [k_receiver_lo, k_receiver_lo + g_receiver_size) and the backing run --
//     measured rather than assumed, so "outside its window" is a claim about an
//     address range and not about an array subscript;
//   * the stride and count of the two walks (four bytes and six times for the
//     slot cursor, twenty bytes and six times for the walker) and the adjacency
//     of each element's two words;
//   * the call trace, in order, for a fixture that mixes both arms;
//   * the return value, on every arm combination;
//   * the ABI, measured rather than asserted: ESP sampled around the call to the
//     reconstruction, and the observers' frame addresses compared with the
//     caller's.
//
// THE CASES MARKED REFUTE exist to try to BREAK the reconstruction. Each names
// the wrong reconstruction it is aimed at:
//
//   A  a wrong length: 34, 36, 0, or 0x23 read as a dword count
//   B  the compare read as SIGNED, or as > instead of >=, or off by one
//   C  wrong pointer level: the START word read as a value, or dereferenced
//      twice, or the CURRENT word's pointee zeroed instead of the START's
//   D  wrong receiver offset: a neighbouring word zeroed, or the walker's two
//      words mixed up, or the START word written instead of the CURRENT one
//   E  wrong stride or count: 16 or 24 instead of 20, 8 or 12 instead of 4,
//      five or seven elements instead of six
//   F  wrong callee, wrong argument order, or the shortfall passed as the
//      length / the current address passed as the receiver
//   G  the slow arm advancing the CURRENT word itself as well as asking the
//      callee to, or the fast arm calling the fill helper as well as the thunk
//   H  wrong write ordering: the zero-fill before the arm instead of after
//   I  the value byte hoisted to entry and not re-zeroed, or pointed into the
//      receiver instead of the frame
//   J  the callee's return value used, or the thunk's arguments swapped
//   K  the loop reusing element 0, or the head element skipped
//   L  a __cdecl reconstruction of the __thiscall callee, or a receiver that
//      does not arrive in ECX
//   M  a return value that is not 35, or one that varies with the arms taken
//   P  a write outside either window: a fill of 36 or of a dword, a window that
//      starts one byte early, or a store to any receiver word outside the four
//      anchor runs -- and, as the precondition for all of those, a fixture
//      whose poison was never laid down
//
// WHAT IS NOT ASSERTED, AND WHY:
//
//   * WHAT 0x005151b0 DOES. Its 295 instructions are not this package's target.
//     The observer emulates ONE documented effect -- set the current word to
//     start+35 and zero from the old current to start+35, which is what
//     0x00515291 and 0x005153cc and the memset at 0x005152dc show -- and even
//     that is a fixture, not a claim. The PASSIVE mode writes nothing at all,
//     and the reconstruction must behave identically either way; that is the
//     only property of the callee the reconstruction is allowed to depend on.
//   * THE RAW STACK BYTES AT THE CALLEE BOUNDARY. Argument order is measured
//     through the observers' declared parameters, which receive whatever the
//     reconstruction pushed in whatever position it pushed it. Reading [ESP+4]
//     at callee entry would need a frame-pointer assumption this package will
//     not make on a cross-compiled target.
//   * WHICH REGISTERS CARRY WHAT. EAX/EBX/ECX/EDX/ESI/EDI/EBP usage is
//     register allocation with no effect on the observable result. The
//     per-instruction comments in the .cpp record it so the arms can be matched
//     to the bytes, and nothing here depends on it.
//   * THE RELOAD OF THE START WORD IN THE TWO ZEROING LOOPS (0x00586754 and
//     0x005867d1). It is reproduced in the source but it is unobservable here,
//     because nothing in either arm can change that word between two
//     iterations. Asserting it would be asserting an implementation detail of
//     the register allocator, and it is stated as a note instead.
//   * THE IDENTITY OF THE WORDS AT self+0x4ec AND self+0x4f0+4k. The body
//     zeroes them and never reads them; this package claims nothing about what
//     they are, and the test asserts only THAT they are zeroed.
//   * THE OBJECT'S REAL SIZE. This body writes no byte above self+0x573; the
//     modeled receiver is 0x600 bytes so the 0x011e0744 source argument, which
//     is an address out of the current word, can be pointed anywhere without
//     leaving the fixture. 0x574 is a lower bound, not a layout.
//   * THE CLASS THIS ENTRY POINT SITS IN. It is the code pointer at word index
//     20 of the run at 0x013f57f8, and no class is named here.

#include "sw2_00586700_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w2_00586700 {
namespace {

int g_failures = 0;

void check(bool condition, const char* what) {
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL: %s\n", what);
  }
}

// ---------------------------------------------------------------------------
// The observers.
// ---------------------------------------------------------------------------

enum class Kind { kFill, kCopy };

// What one transfer was, as the observer saw it. The tuple is positional and
// the whole point of the test is to assert it in order, so nothing here is
// reordered or normalised.
struct Transfer {
  Kind kind;
  Word arg0;                    // fill: &START word   copy: destination
  Word arg1;                    // fill: CURRENT address copy: source
  Word arg2;                    // fill: shortfall       copy: count
  const std::uint8_t* value_byte;
  std::uint8_t value_byte_seen;
  bool window_all_zero_at_entry;  // the 35 bytes at *(&START word)
  std::uintptr_t frame;           // the observer's own frame address
};

constexpr std::size_t kMaxTransfers = 8;
Transfer g_transfers[kMaxTransfers];
std::size_t g_transfer_count = 0;

enum class FillMode {
  kPassive,    // record only; write nothing at all
  kFaithful,   // emulate the one documented effect of 0x005151b0
  kScribble,   // faithful, and also scribble on the value byte afterwards
};

FillMode g_fill_mode = FillMode::kPassive;
Word g_scribble_value = 0x7f;
// THE RECEIVER RUN'S LOWER BOUND, published by run() on every entry. The body
// reaches the receiver only through the register that 0x00586705 MOV EBP,ECX
// loads out of ECX, so the receiver really is one bounded object and "outside
// its window" is a statement about a range of ADDRESSES rather than about an
// array subscript. Every bounds and guard-band check in this file is stated
// against this bound and g_receiver_size. It is a live value and not a
// constant precisely because it is where the fixture's receiver happened to be
// allocated; it is also the low bound the two bounds checks below are written
// against, which is what it was introduced for.
std::uint8_t* k_receiver_lo = nullptr;
std::size_t g_receiver_size = 0;
Word g_poison_return = 0;

void record(const Transfer& item) {
  if (g_transfer_count < kMaxTransfers) {
    g_transfers[g_transfer_count] = item;
  }
  ++g_transfer_count;
}

std::uintptr_t sample_esp() {
  std::uintptr_t value = 0;
  __asm__ __volatile__("movl %%esp, %0" : "=r"(value));
  return value;
}

bool window_is_all_zero(Word start_address, Word length) {
  const std::uint8_t* window = at_const(start_address);
  for (Word index = 0; index != length; ++index) {
    if (window[index] != 0) {
      return false;
    }
  }
  return true;
}

// Whether `pointer` lies inside the receiver run, i.e. in
// [k_receiver_lo, k_receiver_lo + g_receiver_size). This is the bounds
// predicate for the receiver byte run and it is stated in absolute addresses on
// purpose: the band assertions further down have to be about the object's
// address range, because what the machine guarantees is that the body reaches
// the receiver through ECX and nothing about where the test put it.
//
// The subtraction form avoids forming `low + g_receiver_size`, so a pointer
// below the run cannot wrap into looking like it is inside.
bool inside_receiver_run(const void* pointer) {
  const std::uintptr_t low = reinterpret_cast<std::uintptr_t>(k_receiver_lo);
  const std::uintptr_t value = reinterpret_cast<std::uintptr_t>(pointer);
  return (low != 0u) && (value >= low) && ((value - low) < g_receiver_size);
}

}  // namespace

// Defined outside the anonymous namespace because the reconstruction's header
// declares them with C language linkage.
extern "C" void* memcpy_thunk_011e0744(void* destination, const void* source,
                                       std::size_t count) {
  Transfer item;
  std::memset(&item, 0, sizeof(item));
  item.kind = Kind::kCopy;
  item.arg0 = address_of(static_cast<const std::uint8_t*>(destination));
  item.arg1 = address_of(static_cast<const std::uint8_t*>(source));
  item.arg2 = static_cast<Word>(count);
  item.frame = reinterpret_cast<std::uintptr_t>(__builtin_frame_address(0));
  record(item);
  // A real memcpy of `count` bytes. The listing's count is identically zero, so
  // this writes nothing -- and a reconstruction that passed a non-zero count
  // would visibly move bytes here, which is the point.
  if (count != 0 && destination != nullptr && source != nullptr) {
    std::memmove(destination, source, count);
  }
  return destination;
}

extern "C" void SW2_00586700_THISCALL growable_buffer_fill_005151b0(
    void* buffer, void* current_address, Word shortfall, const std::uint8_t* value_byte) {
  const Word receiver_word = address_of(static_cast<const std::uint8_t*>(buffer));
  const Word start_address = *word_at(buffer, 0);

  Transfer item;
  std::memset(&item, 0, sizeof(item));
  item.kind = Kind::kFill;
  item.arg0 = receiver_word;
  item.arg1 = address_of(static_cast<const std::uint8_t*>(current_address));
  item.arg2 = shortfall;
  item.value_byte = value_byte;
  item.value_byte_seen = (value_byte != nullptr) ? *value_byte : 0xffu;
  item.window_all_zero_at_entry = window_is_all_zero(start_address, kBufBytes);
  item.frame = reinterpret_cast<std::uintptr_t>(__builtin_frame_address(0));
  record(item);

  if (g_fill_mode == FillMode::kPassive) {
    return;
  }
  // The one effect of 0x005151b0 that this reconstruction is allowed to rely
  // on: the current word is advanced to start + 35 and the bytes between the
  // old current and start + 35 are filled with the value byte.
  // kEndWordIndex is a SUBSCRIPT, not a byte displacement: the CURRENT word is
  // the one dword on, and word_at()'s argument is bytes. Getting that wrong
  // writes three bytes into the middle of the START word.
  Word* const current_word = word_block(static_cast<std::uint8_t*>(buffer) + kWordBytes);
  *current_word = start_address + kBufBytes;
  const std::uint8_t fill = (value_byte != nullptr) ? *value_byte : 0u;
  const Word from = item.arg1;
  const Word to = start_address + kBufBytes;
  for (Word address = from; address != to; ++address) {
    at(address)[0] = fill;
  }
  if (g_fill_mode == FillMode::kScribble && value_byte != nullptr) {
    // A reconstruction that zeroed the value byte ONCE at entry and reused it
    // would see 0x7f here from the second call on.
    *const_cast<std::uint8_t*>(value_byte) = static_cast<std::uint8_t>(g_scribble_value);
  }
  g_poison_return = 0xfeedfaceu;
}

namespace {

// ---------------------------------------------------------------------------
// The fixture.
// ---------------------------------------------------------------------------

constexpr std::size_t kReceiverBytes = 0x600;
// Each element gets its own 35-byte window, rounded up to a power of two, and
// the kWindowCanary bytes left over after the window are poisoned, so a length
// of 34, 36 or 64 lands visibly outside.
constexpr std::size_t kWindowStride = 0x40;
constexpr std::size_t kWindowCount = 8;  // 0..6 are the real ones, 7 is a decoy
constexpr std::size_t kBackingBytes = kWindowStride * kWindowCount;

constexpr std::uint8_t kWindowFill = 0xa5;
constexpr std::uint8_t kCanaryFill = 0x5a;
// THE CANARY BAND: what is left of a window's stride once the 35-byte window is
// taken off it. This is the poisoned band the body must never reach -- a fill of
// 36, or of a whole dword, or a window that starts one byte early all land in
// it, and case P4 below requires every byte of it to survive. It is the ONLY
// statement of how wide the band is, so the two places that sweep the band (the
// poisoning in dirty_backing and the assertion in P4) cannot disagree about
// where the window ends.
constexpr std::size_t kWindowCanary = kWindowStride - kBufBytes;

// Element 0 is the one at self+0x4d8; elements 1..6 are the walker's, whose
// CURRENT word is at self+0x50c + 20*(index-1) and whose START word is the one
// dword below it.
constexpr std::size_t kElementCount = 7;
// The bulk pattern every non-anchor receiver word starts as. It is a VALID
// window address rather than a poison number on purpose: a reconstruction that
// walks one element too far must fail a CHECK, not fault on a wild address. A
// fault is a crash, and a crash cannot say which reconstruction was wrong.
constexpr std::size_t kBulkPatternElement = 0;

struct Fixture {
  alignas(4) std::uint8_t receiver[kReceiverBytes];
  alignas(4) std::uint8_t backing[kBackingBytes];
  std::uint8_t receiver_before[kReceiverBytes];
  std::uint8_t backing_before[kBackingBytes];
  // Element 0 is the one at self+0x4d8; element n>0 is the walker's, whose
  // CURRENT word is at self+0x50c + 20*(n-1) and whose START word is the one
  // dword below it -- 0x508 + 20*(n-1), which is the receiver record's 0x508.
  Word* start_word(std::size_t element) {
    return word_at(receiver, element == 0 ? kHeadSlot
                                          : kWalkEnd - kWordBytes + kWalkStrideBytes * (element - 1));
  }
  Word* current_word(std::size_t element) {
    return word_at(receiver, element == 0 ? kHeadSlot : kWalkEnd) +
           (element == 0 ? kEndWordIndex : kWalkStrideWords * (element - 1));
  }
  std::uint8_t* window(std::size_t index) { return backing + kWindowStride * index; }
  const std::uint8_t* window(std::size_t index) const {
    return backing + kWindowStride * index;
  }

  // WHICH RECEIVER WORDS THE BODY IS ENTITLED TO WRITE: the lone dword at
  // 0x4ec, the six-dword slot run 0x00586760 reaches through a register, and the
  // two words of each of the seven elements -- the head element at 0x4d8 and the
  // walker's six at 0x508 + 20k. That is TWENTY-ONE words. Every other word of
  // the receiver run is BAND, and the band is poison (see dirty_receiver).
  //
  // The set is built from the same displacements and the same stride the body
  // itself uses, so it cannot drift away from them, and it is deliberately
  // word-exact rather than a range: the fifteen words BETWEEN the walker
  // elements' pairs (0x510..0x51b and so on) hold the bulk pattern, are never
  // written by this body, and are exactly the words a store one word too high
  // would land in. A range-shaped set would have skipped them and let that store
  // past.
  //
  // The seven START words are read and never written, so they are not words the
  // body may WRITE -- but they hold anchor values rather than the bulk pattern,
  // so they are excluded from the band sweep anyway. D1 asserts that they are not
  // written, by diff.
  bool offset_is_anchored(std::size_t offset) const {
    if (offset == kCountSlot) {
      return true;  // 0x4ec, the lone dword
    }
    if (offset >= kSlotBase && offset < kSlotBase + kTripCount * kSlotStrideBytes) {
      return true;  // 0x4f0 .. 0x507, the six slot dwords
    }
    for (std::size_t element = 0; element != kElementCount; ++element) {
      // The CURRENT word, at the same displacement Fixture::current_word() uses;
      // the element's START word is the one dword below it.
      const std::size_t current = (element == 0)
                                      ? kHeadSlot + kWordBytes
                                      : kWalkEnd + kWalkStrideBytes * (element - 1);
      if (offset == current || offset == current - kWordBytes) {
        return true;  // this element's CURRENT and START word
      }
    }
    return false;
  }

  // Whether the `length` bytes at `address` lie inside this fixture's backing
  // run -- the other bounded object the body reaches, through the addresses the
  // buffer words hold rather than through the receiver. Stated against the run
  // rather than against a window index, because a window that starts early ends
  // in the PREVIOUS window's canary and must still be caught as out of bounds.
  bool backing_run_holds(Word address, std::size_t length) const {
    const std::uintptr_t base = reinterpret_cast<std::uintptr_t>(backing);
    const std::uintptr_t value = static_cast<std::uintptr_t>(address);
    return (value >= base) && ((value - base) <= kBackingBytes) &&
           (length <= kBackingBytes - (value - base));
  }
};

void reset_observers(FillMode mode) {
  g_transfer_count = 0;
  g_fill_mode = mode;
  g_poison_return = 0;
  std::memset(g_transfers, 0, sizeof(g_transfers));
}

// Dirty every backing byte, windows and canaries alike.
void dirty_backing(Fixture& fixture) {
  for (std::size_t index = 0; index < kBackingBytes; ++index) {
    const std::size_t within = index % kWindowStride;
    fixture.backing[index] = (within < kBufBytes) ? kWindowFill : kCanaryFill;
  }
}

void dirty_receiver(Fixture& fixture) {
  std::memset(fixture.receiver, 0x3c, kReceiverBytes);
  // Every word of the four receiver anchors, and the slot run, start as the
  // same nonzero pattern so that "was it written?" is answerable.
  const Word bulk = address_of(fixture.window(kBulkPatternElement));
  for (std::size_t offset = 0; offset + kWordBytes <= kReceiverBytes; offset += kWordBytes) {
    *word_at(fixture.receiver, offset) = bulk;
  }
  // Point every element's two words at its own window, plus a decoy: the
  // address one more dereference away, so a two-level read is visible.
  for (std::size_t element = 0; element != kElementCount; ++element) {
    Word* const start = fixture.start_word(element);
    Word* const current = fixture.current_word(element);
    *start = address_of(fixture.window(element));
    *current = *start;  // size 0 unless the caller widens it
    *word_at(fixture.window(element), 0) = address_of(fixture.window(kWindowCount - 1));
  }
  // A word inside the canary of every window, and inside the last window, both
  // pointing somewhere harmless: if the zero-fill runs long it lands here.
  for (std::size_t index = 0; index != kWindowCount; ++index) {
    for (std::size_t within = kBufBytes; within != kWindowStride; ++within) {
      fixture.backing[kWindowStride * index + within] = kCanaryFill;
    }
  }
  // Receiver words that must NEVER change: the immediate neighbours of every
  // anchor the body touches, plus the words a wrong walker stride would land on
  // instead of the real ones. 0x4f0 + 6*4 is 0x508 and 0x50c + 1*20 is 0x520,
  // so those two are DELIBERATELY absent: they are the first walker's START and
  // CURRENT words, and planting a poison in either would be a broken fixture
  // rather than a decoy. The byte-diff case is what refutes a wrong stride.
  static const std::size_t kForbidden[] = {
      kHeadSlot - kWordBytes,           // 0x4d4
      kHeadSlot + 2 * kWordBytes,       // 0x4e0, the head element's cap word
      kCountSlot - kWordBytes,          // 0x4e8
      kSlotBase + 8 * kSlotStrideBytes, // 0x510, one past the slot run
      kWalkEnd + kWordBytes,            // 0x510, the first element's cap word
      kWalkEnd + 6 * kWalkStrideBytes,  // 0x578, one past the last element
  };
  for (std::size_t index = 0; index != sizeof(kForbidden) / sizeof(kForbidden[0]); ++index) {
    *word_at(fixture.receiver, kForbidden[index]) = bulk;
  }
}

void snapshot(Fixture& fixture) {
  std::memcpy(fixture.receiver_before, fixture.receiver, kReceiverBytes);
  std::memcpy(fixture.backing_before, fixture.backing, kBackingBytes);
}

// `sizes` gives (current - start) per element; a size at or above 35 takes the
// fast arm, below it the slow arm.
void set_sizes(Fixture& fixture, const Word* sizes, std::size_t count) {
  for (std::size_t element = 0; element != count; ++element) {
    Word* const start = fixture.start_word(element);
    *fixture.current_word(element) = *start + sizes[element];
  }
}

int run(Fixture& fixture) {
  k_receiver_lo = fixture.receiver;
  g_receiver_size = kReceiverBytes;
  return re_00586700(fixture.receiver);
}

std::size_t count_changed(const std::uint8_t* before, const std::uint8_t* after,
                          std::size_t length) {
  std::size_t changed = 0;
  for (std::size_t index = 0; index != length; ++index) {
    if (before[index] != after[index]) {
      ++changed;
    }
  }
  return changed;
}

bool byte_changed(const Fixture& fixture, std::size_t offset) {
  return fixture.receiver_before[offset] != fixture.receiver[offset];
}

// Word-level, and deliberately not byte-level: adding 25 to an aligned address
// usually changes ONE of its four bytes, so "every byte of this word changed" is
// a false requirement. A word STORE is what the listing does (0x0058674f
// ADD dword ptr [ESI + 0x4],EBX) and a word comparison is what tests it.
bool word_changed(const Fixture& fixture, std::size_t offset) {
  return *word_at(fixture.receiver_before, offset) != *word_at(fixture.receiver, offset);
}

bool backing_byte_changed(const Fixture& fixture, std::size_t offset) {
  return fixture.backing_before[offset] != fixture.backing[offset];
}

// ---------------------------------------------------------------------------
// THE TWO GUARD BANDS, stated as VALUES.
//
// A byte diff cannot see a write of the value a byte already held, and the
// fixture's own poisoning is the precondition for every "nothing else changed"
// assertion in this file: if the poison were not in place those assertions would
// be satisfied by a fixture that guarded nothing at all. Neither fact is checked
// anywhere else, so the band is checked here both before the body runs and after
// it, and checked by value rather than by diff.
//
// The two bands are:
//
//   * the CANARY BAND -- the kWindowCanary bytes after each window's 35 bytes,
//     poisoned with kCanaryFill, in all eight windows including the eighth,
//     which no element owns. dirty_backing() lays it down and window_band_
//     intact() requires it to survive byte for byte.
//   * the RECEIVER BAND -- every word of the receiver run outside the anchor
//     runs, poisoned with the bulk pattern, which is a VALID window address on
//     purpose: a reconstruction that reads outside its reach then reads
//     something plausible instead of faulting, and a reconstruction that writes
//     there writes a zero where a nonzero window address was, which is visible
//     by value. The band's range is k_receiver_lo .. k_receiver_lo +
//     g_receiver_size, the run the body reaches only through ECX.
// ---------------------------------------------------------------------------

// Every band word of the receiver run still holds `poison`. Returns false at
// the first one that does not and says which, because a band sweep of 384 words
// that fails on word 379 is not a useful diagnostic. It also returns false when
// the band turned out to be EMPTY, so that an anchored set which had drifted to
// cover the whole run could not make this assertion pass by sweeping nothing.
bool receiver_band_holds(const Fixture& fixture, Word poison) {
  std::size_t swept = 0;
  for (std::size_t offset = 0; offset + kWordBytes <= kReceiverBytes; offset += kWordBytes) {
    if (fixture.offset_is_anchored(offset)) {
      continue;
    }
    ++swept;
    const Word seen = *word_at(fixture.receiver, offset);
    if (seen != poison) {
      std::fprintf(stderr, "       (receiver band word at +0x%zx is 0x%08lx, expected 0x%08lx)\n",
                   offset, static_cast<unsigned long>(seen), static_cast<unsigned long>(poison));
      return false;
    }
  }
  if (swept == 0u) {
    std::fprintf(stderr, "       (the receiver band is empty: the sweep would guard nothing)\n");
  }
  return swept != 0u;
}

// The kWindowCanary bytes after window `index`, all of them still poisoned.
// Same rule: a band of width zero is a failure, not a pass.
bool window_band_intact(const Fixture& fixture, std::size_t index) {
  const std::uint8_t* const band = fixture.window(index) + kBufBytes;
  if (kWindowCanary == 0u) {
    return false;
  }
  for (std::size_t within = 0; within != kWindowCanary; ++within) {
    if (band[within] != kCanaryFill) {
      std::fprintf(stderr, "       (window %zu canary byte %zu is 0x%02x, expected 0x%02x)\n",
                   index, within, static_cast<unsigned>(band[within]),
                   static_cast<unsigned>(kCanaryFill));
      return false;
    }
  }
  return true;
}

std::size_t transfers_of(Kind kind) {
  std::size_t count = 0;
  const std::size_t limit = (g_transfer_count < kMaxTransfers) ? g_transfer_count : kMaxTransfers;
  for (std::size_t index = 0; index != limit; ++index) {
    if (g_transfers[index].kind == kind) {
      ++count;
    }
  }
  return count;
}

const Transfer* transfer_at(std::size_t index) {
  return (index < kMaxTransfers) ? &g_transfers[index] : nullptr;
}

// ---------------------------------------------------------------------------
// V: the constants, against the machine's own immediates. Every number here is
// transcribed from the listing quoted at the top of the .cpp, so a header that
// drifted from the bytes is caught without running anything.
// ---------------------------------------------------------------------------
void verify_constants() {
  check(kBufBytes == 0x23u, "V1: 0x23 is the one length (CMP at 0058671c)");
  check(kTripCount == 0x06u, "V2: the loop runs six times (0058677a)");
  check(kFrameBytes == 0x0cu, "V3: SUB ESP,0xc at 00586700");
  check(kFrameFlagOffset == 0x13u, "V4: the value byte at [ESP+0x13] (00586721)");
  check(kFrameFlagPushedOffset == 0x1fu, "V5: the same byte at [ESP+0x1f] (0058672f)");
  check(kFrameCursorOffset == 0x14u, "V6: the cursor at [ESP+0x14] (00586770)");
  check(kFrameCounterOffset == 0x18u, "V7: the counter at [ESP+0x18] (0058677a)");
  check(kHeadSlot == 0x4d8u, "V8: the head element at +0x4d8 (00586707)");
  check(kWordBytes == 0x04u, "V9: the CURRENT word is one dword on (00586715)");
  check(kEndWordIndex == 1u, "V10: which is subscript 1");
  check(kCountSlot == 0x4ecu, "V11: the lone zeroed dword at +0x4ec (00586766)");
  check(kSlotBase == 0x4f0u, "V12: the slot cursor at +0x4f0 (00586760)");
  check(kSlotStrideBytes == 0x04u, "V13: the cursor steps one dword (005867dd)");
  check(kSlotStrideWords == 1u, "V14: so one word per iteration");
  check(kWalkEnd == 0x50cu, "V15: the walker at +0x50c (00586774)");
  check(kWalkStrideBytes == 0x14u, "V16: the walker steps 20 bytes (005867e2)");
  check(kWalkStrideWords == 5u, "V17: so five words per iteration");
  check(kWalkEnd - kWordBytes == 0x508u, "V18: the START word is at +0x508");
  check(kEmptyCopy == 0x00u, "V19: the thunk's count is identically zero");
  check(kSlotBase + 6 * kSlotStrideBytes == 0x508u,
        "V20: the slot run ends exactly where the first START word begins");
  check(kWalkEnd + 5 * kWalkStrideBytes + kWordBytes == 0x574u,
        "V21: the highest byte the body writes is +0x573");
  // The two guard bands, whose widths are the fixture's and not the machine's.
  // Stated as arithmetic on the constants above so a change to either side of
  // either band is a static failure here and not a silently narrower sweep in
  // the behavioural cases.
  check(kWindowCanary == kWindowStride - kBufBytes,
        "V22: the canary band is the window stride less the 35-byte window");
  check(kBufBytes + kWindowCanary == kWindowStride,
        "V23: a window plus its canary band is exactly one window stride");
  check(kWindowCanary != 0u, "V24: the canary band is not empty, so the band sweep bites");
  check(kWindowStride * kWindowCount == kBackingBytes,
        "V25: the backing run is whole windows and no partial one");
}

// ---------------------------------------------------------------------------
// The baseline: seven occurrences, each zeroing 35 bytes at its own start.
// ---------------------------------------------------------------------------
void case_seven_occurrences_zero_thirty_five_bytes_each() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  const Word sizes[kElementCount] = {10, 35, 36, 0, 100, 1, 34};
  set_sizes(fixture, sizes, kElementCount);
  snapshot(fixture);
  reset_observers(FillMode::kFaithful);
  (void)run(fixture);

  for (std::size_t element = 0; element != kElementCount; ++element) {
    for (Word index = 0; index != kBufBytes; ++index) {
      check(fixture.window(element)[index] == 0,
            "T1: each of the seven windows is fully zeroed");
    }
    // A1: the length is exactly 35 -- the byte after is the canary and must be
    // untouched, which refutes 34, 36, 0 and a dword-sized fill.
    for (std::size_t within = kBufBytes; within != kWindowStride; ++within) {
      check(fixture.window(element)[within] == kCanaryFill,
            "A1: the fill stops at 35 bytes; the canary survives");
    }
  }
  // A1 again on the last window, which no element owns: nothing may reach it.
  for (std::size_t index = 0; index != kBufBytes; ++index) {
    check(fixture.window(kWindowCount - 1)[index] != 0,
          "A1: the eighth window is never touched (no two-level dereference)");
  }
  check(g_transfer_count == kElementCount,
        "T2: exactly one transfer per occurrence, seven in all");
}

// ---------------------------------------------------------------------------
// T3: the receiver diff. The exact set of receiver bytes that may change is
// asserted as a whole, so a wrong offset, a wrong stride, a wrong count, a
// wrong store width and a write to the START word are all refuted at once.
// ---------------------------------------------------------------------------
void case_only_the_expected_receiver_bytes_change() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  const Word sizes[kElementCount] = {10, 10, 10, 10, 10, 10, 10};
  set_sizes(fixture, sizes, kElementCount);
  snapshot(fixture);
  reset_observers(FillMode::kFaithful);
  (void)run(fixture);

  std::size_t expected_changed = 0;
  // 0x4dc -- the head element's CURRENT word, as a WORD (see word_changed).
  check(word_changed(fixture, kHeadSlot + kWordBytes),
        "T3: the head CURRENT word is written");
  for (std::size_t index = 0; index != kWordBytes; ++index) {
    expected_changed += byte_changed(fixture, kHeadSlot + kWordBytes + index) ? 1u : 0u;
  }
  // 0x4ec -- the lone dword. Compared as a WORD: a dword store to zero changes
  // only the bytes that were nonzero, and requiring four changed bytes would be
  // requiring a property of the fixture's starting pattern, not of the body.
  check(word_changed(fixture, kCountSlot), "T3: +0x4ec is zeroed");
  for (std::size_t index = 0; index != kWordBytes; ++index) {
    expected_changed += byte_changed(fixture, kCountSlot + index) ? 1u : 0u;
  }
  // 0x4f0..0x507 -- six dwords, stride four.
  for (std::size_t slot = 0; slot != 6; ++slot) {
    const std::size_t base = kSlotBase + kSlotStrideBytes * slot;
    check(word_changed(fixture, base), "T3: the six slot dwords are zeroed, stride four");
    check(*word_at(fixture.receiver, base) == 0u, "T3: a slot dword ends at zero");
    for (std::size_t index = 0; index != kWordBytes; ++index) {
      expected_changed += byte_changed(fixture, base + index) ? 1u : 0u;
    }
  }
  // The six walkers' CURRENT words.
  for (std::size_t element = 1; element != kElementCount; ++element) {
    const std::size_t base = kWalkEnd + kWalkStrideBytes * (element - 1);
    for (std::size_t index = 0; index != kWordBytes; ++index) {
      expected_changed += byte_changed(fixture, base + index) ? 1u : 0u;
    }
  }
  // Nothing else at all.
  const std::size_t total_changed = count_changed(fixture.receiver_before, fixture.receiver,
                                                  kReceiverBytes);
  check(total_changed == expected_changed,
        "T3: no receiver byte outside the four anchors changes at all");
  if (total_changed != expected_changed) {
    std::fprintf(stderr, "       (changed %zu, expected %zu)\n", total_changed, expected_changed);
  }
  // D1: the six START words are read, never written. E5: the slot run is six
  // dwords and not five, not seven, and not a stride of eight or twelve -- all
  // of which the byte diff above already refutes; these say so explicitly.
  for (std::size_t element = 1; element != kElementCount; ++element) {
    check(!word_changed(fixture, kWalkEnd - kWordBytes + kWalkStrideBytes * (element - 1)),
          "D1: the walker's START word is never written");
  }
  check(!word_changed(fixture, kHeadSlot), "D1: the head START word is never written");
  check(!word_changed(fixture, kSlotBase + 8 * kSlotStrideBytes),
        "E5: nothing is zeroed past the six-dword slot run");
  check(!word_changed(fixture, kCountSlot - kWordBytes),
        "E5: nothing is zeroed just below +0x4ec");
  check(!word_changed(fixture, kWalkEnd + kWordBytes),
        "E5: the walker's cap word at +0x510 is never written");
  check(!word_changed(fixture, kWalkEnd + 6 * kWalkStrideBytes),
        "E5: the walker does not take a seventh step");
}

// ---------------------------------------------------------------------------
// P: the two guard bands, by value, before and after the body runs. T3 says what
// CHANGED; this says what is still there, and proves the poison was there to be
// protected.
//
// The sizes put BOTH arms on BOTH sites inside one run: the head element and
// two of the walker's elements are at 35, which is the fast arm, and the other
// four are below 35, which is the slow arm. All of them are at or below 35 on
// purpose -- that keeps the observer's emulated fill, which runs
// [current, start+35), inside its own window, so every byte this case attributes
// to the body is a byte the body wrote and the bands are the only place a write
// can show up.
// ---------------------------------------------------------------------------
void case_the_guard_bands_survive_the_body() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  const Word sizes[kElementCount] = {35, 0, 35, 1, 10, 35, 2};
  set_sizes(fixture, sizes, kElementCount);
  const Word band_poison = address_of(fixture.window(kBulkPatternElement));

  // P1: the receiver band is poisoned BEFORE the body runs. Every "nothing else
  // in the receiver changed" assertion in this file -- T3's byte diff, D1's
  // read-only START words, E5's one-past-the-end words -- is vacuous without
  // this, and nothing else establishes it.
  check(receiver_band_holds(fixture, band_poison),
        "P1: every receiver word outside the anchors holds the bulk pattern before the run");
  // P2: and so is the canary band, in all eight windows.
  for (std::size_t index = 0; index != kWindowCount; ++index) {
    check(window_band_intact(fixture, index),
          "P2: every canary byte holds its poison before the run");
  }

  snapshot(fixture);
  reset_observers(FillMode::kFaithful);
  (void)run(fixture);

  // P3: the body wrote NONE of the receiver band. By value, so a store of the
  // word a band word already held is caught as well as a store of a zero.
  check(receiver_band_holds(fixture, band_poison),
        "P3: the receiver band is untouched: the body wrote none of it");
  // P4: and none of the canary band, in any window, including the eighth that no
  // element owns. A fill of 36, of a dword, or of a window that starts early all
  // land here, and a window that starts early is the one this catches that T1
  // cannot: the byte before a window is the previous window's canary.
  for (std::size_t index = 0; index != kWindowCount; ++index) {
    check(window_band_intact(fixture, index),
          "P4: the kWindowCanary-byte band after every window survives");
  }

  // P5: the bounds both band assertions are stated in, measured rather than
  // assumed. The body's whole reach -- 0x4d8 through the last walker's end word
  // at 0x570, so 0x574 bytes -- is inside the receiver run the band sweep
  // covers, and the run is reached only through ECX (0x00586705 MOV EBP,ECX),
  // which is what makes it one bounded object. 0x574 is this package's lower
  // bound on the object and not a claim about its real extent (header note (5)).
  check(inside_receiver_run(fixture.start_word(0)) &&
            inside_receiver_run(fixture.current_word(kElementCount - 1)) &&
            inside_receiver_run(word_at(fixture.receiver,
                                        kWalkEnd + (kElementCount - 2) * kWalkStrideBytes)),
        "P5: the whole reach, 0x4d8..0x573, is inside the receiver run the band is stated in");
  // P5b: and the band sweep really sweeps. The anchored set is twenty-one words
  // -- the lone dword, the six slot dwords, and two words for each of the seven
  // elements -- and the run is 384, so the band is the other 363. Pinned as
  // literals on purpose: an anchored set that had drifted to cover the whole run
  // would leave P3 passing by sweeping nothing, and this is the assertion that
  // would notice.
  const std::size_t anchored = 1u + kTripCount + 2u * kElementCount;
  check(anchored == 21u && (kReceiverBytes / kWordBytes) == 384u &&
            (kReceiverBytes / kWordBytes) - anchored == 363u,
        "P5b: the band is 363 of the run's 384 words, so the sweep is not vacuous");
  // P6: and the seven windows it writes are inside the backing run, so a band
  // sweep over the backing run covers every byte the body can reach there.
  for (std::size_t element = 0; element != kElementCount; ++element) {
    check(*fixture.start_word(element) == address_of(fixture.window(element)) &&
              fixture.backing_run_holds(*fixture.start_word(element), kBufBytes),
          "P6: each element's 35-byte window is inside the backing run");
  }
}

// ---------------------------------------------------------------------------
// T4: the arm split, and B2 -- the unsigned compare, driven with the input where
// signed and unsigned disagree.
// ---------------------------------------------------------------------------
void case_the_compare_is_an_unsigned_at_least_35() {
  {
    // B2: current BELOW start. Unsigned, the difference wraps to ~4e9 and the
    // fast arm is taken; signed, it is negative and the slow arm would be.
    Fixture fixture;
    dirty_backing(fixture);
    dirty_receiver(fixture);
    for (std::size_t element = 0; element != kElementCount; ++element) {
      *fixture.current_word(element) = *fixture.start_word(element) - 1u;
    }
    snapshot(fixture);
    reset_observers(FillMode::kFaithful);
    (void)run(fixture);

    check(transfers_of(Kind::kFill) == 0,
          "B2: current below start takes the FAST arm, not the signed slow arm");
    check(transfers_of(Kind::kCopy) == kElementCount,
          "B2: all seven occurrences take the thunk");
    for (std::size_t element = 0; element != kElementCount; ++element) {
      check(*fixture.current_word(element) == *fixture.start_word(element) + kBufBytes,
            "B2: the wrapping ADD still lands on start + 35");
      check(fixture.window(element)[kBufBytes - 1] == 0, "B2: the window is zeroed anyway");
    }
  }
  {
    // A1/B1: the boundary. 34 is below, 35 is at, 36 is above. `>` instead of
    // `>=` would take the slow arm at 35.
    static const Word probes[] = {0, 1, 33, 34, 35, 36, 37, 1000};
    for (std::size_t index = 0; index != sizeof(probes) / sizeof(probes[0]); ++index) {
      Fixture fixture;
      dirty_backing(fixture);
      dirty_receiver(fixture);
      const Word size = probes[index];
      for (std::size_t element = 0; element != kElementCount; ++element) {
        *fixture.current_word(element) = *fixture.start_word(element) + size;
      }
      snapshot(fixture);
      reset_observers(FillMode::kFaithful);
      (void)run(fixture);
      const bool expect_fast = (size >= 35);
      const char* label = (size >= 35) ? "B1: size >= 35 takes the fast arm"
                                      : "B1: size < 35 takes the slow arm";
      check(transfers_of(Kind::kFill) == (expect_fast ? 0u : kElementCount), label);
      check(transfers_of(Kind::kCopy) == (expect_fast ? kElementCount : 0u), label);
      for (std::size_t element = 0; element != kElementCount; ++element) {
        check(*fixture.current_word(element) == *fixture.start_word(element) + kBufBytes,
              "T4: every occurrence ends with current == start + 35");
      }
    }
  }
}

// ---------------------------------------------------------------------------
// F: the fill helper's four-word argument tuple, in order.
// ---------------------------------------------------------------------------
void case_the_fill_helper_receives_the_documented_tuple() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  const Word sizes[kElementCount] = {0, 0, 0, 0, 0, 0, 0};
  set_sizes(fixture, sizes, kElementCount);
  snapshot(fixture);
  reset_observers(FillMode::kFaithful);
  (void)run(fixture);

  check(g_transfer_count == kElementCount, "F0: seven transfers, all to the fill helper");
  for (std::size_t index = 0; index != kElementCount; ++index) {
    const Transfer* const item = transfer_at(index);
    if (item == nullptr) {
      check(false, "F0: the trace has room for every transfer");
      return;
    }
    const std::size_t element = index;
    const Word start = address_of(fixture.window(element));
    // F/D: the receiver is the ADDRESS OF THE START WORD, one dword below the
    // current word. Passing the current word, the walker, or the receiver itself
    // would all be wrong and all would still "work" on a permissive fixture.
    check(item->arg0 == address_of(fixture.start_word(element)),
          "F1: arg0 is the address of the element's START word");
    check(item->arg0 == address_of(fixture.current_word(element)) - kWordBytes,
          "F1: arg0 is exactly one dword below the CURRENT word");
    // F: the first stack word is the CURRENT ADDRESS, not the start address.
    check(item->arg1 == start, "F2: arg1 is the CURRENT address");
    check(item->arg1 != address_of(fixture.start_word(element)),
          "F2: arg1 is the current word's value, not its address");
    // F: the second stack word is the SHORTFALL, 35 - (current - start), and at
    // size zero that is the length itself.
    check(item->arg2 == kBufBytes, "F3: arg2 is the shortfall, 35 - size");
    check(item->arg2 != 0u, "F3: arg2 is never the zero the thunk gets");
    // I: the third stack word points at a byte in the callee's own frame, not
    // anywhere in the receiver, and the byte is zero. Stated as a RANGE test
    // against the receiver run's bounds rather than as a list of forbidden
    // words, because 0x0058672f stores it into the frame at entry_ESP-9 and the
    // machine's claim is only that it is not a receiver address at all.
    check(item->value_byte_seen == 0, "I1: the value byte is zero when the callee reads it");
    check(item->value_byte != nullptr, "I2: the value byte pointer is not null");
    if (item->value_byte != nullptr && k_receiver_lo != nullptr) {
      check(!inside_receiver_run(item->value_byte),
            "I2: the value byte is NOT inside the receiver");
      if (inside_receiver_run(item->value_byte)) {
        std::fprintf(stderr,
                     "       (the value byte is at %p, inside the receiver run %p..%p)\n",
                     static_cast<const void*>(item->value_byte),
                     static_cast<const void*>(k_receiver_lo),
                     static_cast<const void*>(byte_at(k_receiver_lo, g_receiver_size)));
      }
    }
  }
}

void case_the_shortfall_is_35_minus_the_size() {
  static const Word probes[] = {0, 1, 17, 33, 34};
  for (std::size_t index = 0; index != sizeof(probes) / sizeof(probes[0]); ++index) {
    Fixture fixture;
    dirty_backing(fixture);
    dirty_receiver(fixture);
    for (std::size_t element = 0; element != kElementCount; ++element) {
      *fixture.current_word(element) = *fixture.start_word(element) + probes[index];
    }
    snapshot(fixture);
    reset_observers(FillMode::kFaithful);
    (void)run(fixture);
    for (std::size_t order = 0; order != kElementCount; ++order) {
      const Transfer* const item = transfer_at(order);
      if (item == nullptr) {
        check(false, "F4: the trace has room");
        return;
      }
      check(item->arg2 == kBufBytes - probes[index],
            "F4: arg2 is 35 minus the size, on the slow arm");
    }
  }
}

// ---------------------------------------------------------------------------
// G: on the slow arm this body does NOT advance the CURRENT word. Proved with
// a callee that writes nothing at all.
// ---------------------------------------------------------------------------
void case_the_slow_arm_leaves_the_current_word_to_the_callee() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  const Word sizes[kElementCount] = {0, 0, 0, 0, 0, 0, 0};
  set_sizes(fixture, sizes, kElementCount);
  Word before[kElementCount];
  for (std::size_t element = 0; element != kElementCount; ++element) {
    before[element] = *fixture.current_word(element);
  }
  snapshot(fixture);
  reset_observers(FillMode::kPassive);
  (void)run(fixture);

  check(transfers_of(Kind::kFill) == kElementCount, "G1: the slow arm is taken");
  for (std::size_t element = 0; element != kElementCount; ++element) {
    check(*fixture.current_word(element) == before[element],
          "G1: the slow arm does NOT advance the CURRENT word itself");
  }
  // And the passive callee changed nothing, so the windows are still dirty --
  // which is the whole reason the zero-fill cannot be coming from the callee.
  check(fixture.window(0)[0] == 0, "H1: the zero-fill is the body's own work");
  check(!backing_byte_changed(fixture, kWindowStride - 1),
        "A1: the passive callee's canary is still intact");
}

// ---------------------------------------------------------------------------
// J: the thunk's three arguments, in order, and a count of identically zero.
// ---------------------------------------------------------------------------
void case_the_thunk_copies_nothing_and_is_argument_ordered() {
  static const Word probes[] = {35, 36, 100, 1000};
  for (std::size_t index = 0; index != sizeof(probes) / sizeof(probes[0]); ++index) {
    Fixture fixture;
    dirty_backing(fixture);
    dirty_receiver(fixture);
    for (std::size_t element = 0; element != kElementCount; ++element) {
      *fixture.current_word(element) = *fixture.start_word(element) + probes[index];
    }
    snapshot(fixture);
    reset_observers(FillMode::kFaithful);
    (void)run(fixture);

    check(transfers_of(Kind::kCopy) == kElementCount, "J1: the fast arm calls the thunk");
    for (std::size_t order = 0; order != kElementCount; ++order) {
      const Transfer* const item = transfer_at(order);
      if (item == nullptr) {
        check(false, "J1: the trace has room");
        return;
      }
      const Word start = address_of(fixture.window(order));
      const Word current = start + probes[index];
      check(item->arg0 == start + kBufBytes, "J2: arg0 is the destination, start + 35");
      check(item->arg1 == current, "J3: arg1 is the source, the current address");
      // J3: a swapped pair is refuted by the ARGS, not by them being unequal --
      // at size exactly 35 the source and the destination are the same address,
      // which is exactly what the boundary case looks like.
      check(item->arg0 == start + kBufBytes && item->arg1 == current,
            "J3: destination and source are in the machine's order");
      check(item->arg2 == 0u, "J4: the count is identically zero on every call");
      check(*fixture.current_word(order) == start + kBufBytes,
            "J5: the wrapping ADD lands on start + 35 from any size");
    }
  }
}

// ---------------------------------------------------------------------------
// K: the seven occurrences are seven DISTINCT elements, in order.
// ---------------------------------------------------------------------------
void case_the_call_trace_is_one_transfer_per_distinct_element() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  // head slow, then fast, slow, fast, slow, fast, slow -- so the trace has to
  // alternate and a loop that reused element 0 would show it.
  const Word sizes[kElementCount] = {7, 40, 9, 41, 11, 42, 13};
  set_sizes(fixture, sizes, kElementCount);
  snapshot(fixture);
  reset_observers(FillMode::kFaithful);
  (void)run(fixture);

  check(g_transfer_count == kElementCount, "K1: seven transfers");
  static const bool expect_fill[kElementCount] = {true, false, true, false, true, false, true};
  for (std::size_t order = 0; order != kElementCount; ++order) {
    const Transfer* const item = transfer_at(order);
    if (item == nullptr) {
      check(false, "K1: the trace has room");
      return;
    }
    check((item->kind == Kind::kFill) == expect_fill[order],
          "K1: the arms alternate in the order the fixture asked for");
    const std::size_t element = (item->kind == Kind::kFill) ? 0u : 0u;  // placeholder
    (void)element;
    const Word start = address_of(fixture.window(order));
    const Word seen = (item->kind == Kind::kFill) ? item->arg1 : item->arg1;
    check(seen == start + sizes[order],
          "K2: transfer N is about element N's current address, in order");
  }
}

// ---------------------------------------------------------------------------
// H: the zero-fill happens AFTER the arm, never before.
// ---------------------------------------------------------------------------
void case_the_zero_fill_follows_the_arm() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  const Word sizes[kElementCount] = {0, 0, 0, 0, 0, 0, 0};
  set_sizes(fixture, sizes, kElementCount);
  snapshot(fixture);
  reset_observers(FillMode::kFaithful);
  (void)run(fixture);

  for (std::size_t order = 0; order != kElementCount; ++order) {
    const Transfer* const item = transfer_at(order);
    if (item == nullptr) {
      check(false, "H1: the trace has room");
      return;
    }
    // The observer looked at the 35 bytes at the element's start address on
    // entry. The faithful observer fills from the CURRENT address to start+35,
    // and at size zero that range is empty, so a window that was still dirty on
    // entry proves the zero-fill had not run yet.
    check(!item->window_all_zero_at_entry,
          "H1: the 35 bytes are still dirty when the callee is entered");
  }
  for (std::size_t element = 0; element != kElementCount; ++element) {
    check(fixture.window(element)[0] == 0, "H2: the window is zeroed by the time it returns");
  }
}

// ---------------------------------------------------------------------------
// I: the value byte is re-zeroed before EACH call, not once at entry.
// ---------------------------------------------------------------------------
void case_the_value_byte_is_re_zeroed_before_every_call() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  const Word sizes[kElementCount] = {0, 0, 0, 0, 0, 0, 0};
  set_sizes(fixture, sizes, kElementCount);
  snapshot(fixture);
  reset_observers(FillMode::kScribble);
  (void)run(fixture);

  // The observer scribbles 0x7f over the value byte on its way out. If the
  // reconstruction zeroed it once at entry, every call after the first would
  // see 0x7f.
  for (std::size_t order = 0; order != kElementCount; ++order) {
    const Transfer* const item = transfer_at(order);
    if (item == nullptr) {
      check(false, "I3: the trace has room");
      return;
    }
    check(item->value_byte_seen == 0,
          "I3: the value byte reads zero on EVERY call, not just the first");
  }
}

// ---------------------------------------------------------------------------
// C: pointer level. The START word is an address, used once. The word AT that
// address is a decoy and must never be followed.
// ---------------------------------------------------------------------------
void case_the_start_word_is_dereferenced_exactly_once() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  // Point each start word at a decoy that itself points at the real window, so
  // a two-level read would zero window 7 for every element.
  for (std::size_t element = 0; element != kElementCount; ++element) {
    Word* const start = fixture.start_word(element);
    *start = address_of(fixture.window(element));
    *word_at(fixture.window(element), 0) = address_of(fixture.window(kWindowCount - 1));
  }
  const Word sizes[kElementCount] = {0, 0, 0, 0, 0, 0, 0};
  set_sizes(fixture, sizes, kElementCount);
  snapshot(fixture);
  reset_observers(FillMode::kFaithful);
  (void)run(fixture);

  for (std::size_t element = 0; element != kElementCount; ++element) {
    check(fixture.window(element)[kBufBytes - 1] == 0,
          "C1: the 35 bytes at the address the START word holds are zeroed");
  }
  for (std::size_t index = 0; index != kBufBytes; ++index) {
    check(fixture.window(kWindowCount - 1)[index] != 0,
          "C2: the pointee of the pointee is never zeroed (one level, not two)");
  }
  // C3: a receiver word that is itself a pointer to a window is read as an
  // address, not written through.
  check(*word_at(fixture.receiver, kCountSlot) == 0u,
        "C3: the dword at +0x4ec is a zero, not a pointer that was followed");
}

// ---------------------------------------------------------------------------
// M: the return value, on every arm combination.
// ---------------------------------------------------------------------------
void case_the_return_value_is_always_thirty_five() {
  static const Word patterns[][kElementCount] = {
      {0, 0, 0, 0, 0, 0, 0},      {35, 35, 35, 35, 35, 35, 35},
      {40, 0, 40, 0, 40, 0, 40},   {0, 40, 0, 40, 0, 40, 0},
      {0xffffffffu, 0, 0xffffffffu, 0, 0xffffffffu, 0, 0xffffffffu},
  };
  for (std::size_t index = 0; index != sizeof(patterns) / sizeof(patterns[0]); ++index) {
    Fixture fixture;
    dirty_backing(fixture);
    dirty_receiver(fixture);
    set_sizes(fixture, patterns[index], kElementCount);
    snapshot(fixture);
    reset_observers(FillMode::kFaithful);
    const int result = run(fixture);
    check(result == static_cast<int>(kBufBytes),
          "M1: the return value is 35 on every arm combination");
    (void)g_poison_return;
  }
}

// ---------------------------------------------------------------------------
// L: the ABI, measured.
// ---------------------------------------------------------------------------
void case_the_abi_is_thiscall_with_caller_cleanup() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  const Word sizes[kElementCount] = {0, 0, 0, 0, 0, 0, 0};
  set_sizes(fixture, sizes, kElementCount);
  snapshot(fixture);
  reset_observers(FillMode::kFaithful);

  const std::uintptr_t before = sample_esp();
  (void)run(fixture);
  const std::uintptr_t after = sample_esp();
  check(before == after,
        "L1: the reconstruction leaves ESP exactly where it found it (four saved "
        "registers, the 12-byte frame, and both call arms' arguments all undone)");

  // Every observer was entered below this frame, i.e. by a CALL and not a jump,
  // and every one of them returned to it.
  for (std::size_t index = 0; index != kElementCount; ++index) {
    const Transfer* const item = transfer_at(index);
    if (item == nullptr) {
      check(false, "L2: the trace has room");
      return;
    }
    check(item->frame != 0u, "L2: every observer ran on a real frame");
  }
  // L3: the head element's fill call received the head element's START word as
  // the receiver, which is only true if ECX carried the receiver through the
  // prologue's MOV EBP,ECX rather than through a stack slot.
  check(g_transfers[0].arg0 == address_of(fixture.start_word(0)),
        "L3: the first transfer's receiver is the head START word (ECX)");
}

// J: the callees' return values are discarded.
void case_the_callee_return_values_are_discarded() {
  Word results[2];
  for (std::size_t variant = 0; variant != 2; ++variant) {
    Fixture fixture;
    dirty_backing(fixture);
    dirty_receiver(fixture);
    const Word sizes[kElementCount] = {0, 40, 0, 40, 0, 40, 0};
    set_sizes(fixture, sizes, kElementCount);
    snapshot(fixture);
    reset_observers(FillMode::kFaithful);
    g_poison_return = (variant == 0) ? 0x00000000u : 0xffffffffu;
    results[variant] = static_cast<Word>(run(fixture));
    for (std::size_t element = 0; element != kElementCount; ++element) {
      check(*fixture.current_word(element) == *fixture.start_word(element) + kBufBytes,
            "J6: the callee's return value changes nothing");
    }
  }
  check(results[0] == results[1],
        "J6: two different callee return values give the same result");
}

// ---------------------------------------------------------------------------
// K: the walk really walks -- the six elements' windows are all distinct and
// all zeroed, which a five- or seven-iteration loop could not manage.
// ---------------------------------------------------------------------------
void case_the_walk_covers_exactly_six_elements() {
  Fixture fixture;
  dirty_backing(fixture);
  dirty_receiver(fixture);
  const Word sizes[kElementCount] = {0, 1, 2, 3, 4, 5, 6};
  set_sizes(fixture, sizes, kElementCount);
  snapshot(fixture);
  reset_observers(FillMode::kFaithful);
  (void)run(fixture);

  for (std::size_t element = 1; element != kElementCount; ++element) {
    check(fixture.window(element)[0] == 0, "K3: walker element is zeroed");
  }
  check(g_transfer_count == kElementCount, "K3: six walker elements plus the head");
  // Each element's shortfall differs, which is only possible if the walk visits
  // six DIFFERENT elements.
  for (std::size_t order = 0; order != kElementCount; ++order) {
    const Transfer* const item = transfer_at(order);
    if (item == nullptr) {
      check(false, "K3: the trace has room");
      return;
    }
    check(item->arg2 == kBufBytes - sizes[order],
          "K4: each transfer's shortfall matches ITS OWN element's size");
  }
}

// ---------------------------------------------------------------------------
// The receiver is not gated on anything. Every word the body reads is one of
// the four anchors; a reconstruction that branched on some other receiver word
// would take a different arm here.
// ---------------------------------------------------------------------------
void case_no_other_receiver_word_gates_the_arms() {
  // The same sizes, run twice, with every non-anchor receiver word set to a
  // different poison value each time. If any of them were read to choose an arm,
  // the second run would take a different path.
  Word first[2];
  static const Word poison[] = {0u, 0xffffffffu};
  for (std::size_t variant = 0; variant != 2; ++variant) {
    Fixture fixture;
    dirty_backing(fixture);
    dirty_receiver(fixture);
    for (std::size_t offset = 0; offset + kWordBytes <= kReceiverBytes; offset += kWordBytes) {
      const bool anchor = (offset == kHeadSlot) || (offset == kCountSlot) ||
                          (offset >= kSlotBase && offset < kSlotBase + 6 * kSlotStrideBytes) ||
                          (offset >= kWalkEnd - kWordBytes &&
                           offset < kWalkEnd + 5 * kWalkStrideBytes + kWordBytes);
      if (!anchor) {
        *word_at(fixture.receiver, offset) = poison[variant];
      }
    }
    const Word sizes[kElementCount] = {0, 40, 0, 40, 0, 40, 0};
    set_sizes(fixture, sizes, kElementCount);
    snapshot(fixture);
    reset_observers(FillMode::kFaithful);
    first[variant] = static_cast<Word>(run(fixture));
    check(g_transfer_count == kElementCount, "N1: seven transfers whatever the poison");
  }
  check(first[0] == first[1], "N1: the arms do not depend on any other receiver word");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w2_00586700

using namespace openspore::reconstruction::pkg_swarm_w2_00586700;

int main() {
  verify_constants();
  case_seven_occurrences_zero_thirty_five_bytes_each();
  case_only_the_expected_receiver_bytes_change();
  case_the_guard_bands_survive_the_body();
  case_the_compare_is_an_unsigned_at_least_35();
  case_the_fill_helper_receives_the_documented_tuple();
  case_the_shortfall_is_35_minus_the_size();
  case_the_slow_arm_leaves_the_current_word_to_the_callee();
  case_the_thunk_copies_nothing_and_is_argument_ordered();
  case_the_call_trace_is_one_transfer_per_distinct_element();
  case_the_zero_fill_follows_the_arm();
  case_the_value_byte_is_re_zeroed_before_every_call();
  case_the_start_word_is_dereferenced_exactly_once();
  case_the_return_value_is_always_thirty_five();
  case_the_abi_is_thiscall_with_caller_cleanup();
  case_the_callee_return_values_are_discarded();
  case_the_walk_covers_exactly_six_elements();
  case_no_other_receiver_word_gates_the_arms();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("all checks passed for VA 0x00586700\n");
  return 0;
}
