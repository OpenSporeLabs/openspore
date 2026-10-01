// PKG-SPOREpedia-DUAL-00fa5040 -- model test for VA 0x00fa5040
//
// What this test is and is not.
//
//   It IS a check of the package against facts derived independently of it:
//   the constants are compared against literals typed out here, the count
//   sequence is compared against C signed division written here, and every
//   behavioural claim is compared against an expected call log typed out here.
//   Nothing in this file reads a constant out of the package header and then
//   compares it with itself; where a package value is checked, the expected
//   value is a literal in THIS file.
//
//   It is NOT a differential test against the original binary. No trace of
//   0x00fa5040 running in SporeApp.exe exists in this repository, so there is
//   no oracle to compare behaviour against, and none is simulated. What is
//   compared here is the reconstruction against a reading of the 297-
//   instruction listing, and that reading is stated in the expectations below
//   with the address it comes from.

#include "sporepedia_dual_00fa5040.hpp"

#include <cstdio>
#include <cstring>
#include <limits>
#include <vector>

namespace {

using namespace openspore::reconstruction::pkg_sporepedia_dual_00fa5040;

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL  %s\n", what);
  }
}

void check_word(Word got, Word want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL  %s: got 0x%08x, want 0x%08x\n", what, got, want);
  }
}

bool check_size(std::size_t got, std::size_t want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL  %s: %zu call(s), want %zu\n", what, got, want);
    return false;
  }
  return true;
}

// -- fixture geometry --------------------------------------------------------
//
// Layout of the synthetic receiver image. Every offset here is either one the
// body reaches, and is therefore in the machine listing, or a fixture address,
// which is not.
//
// 0x00770, 0x00774   the second array's base and end words
// 0x00784, 0x00788   the first array's base and end words
// 0x00218 + k*0x14   sub-table k's own three words
// 0x00218 + k*0x14 + 0x50  the pending vector hanging off sub-table k
const std::size_t kImageBytes = 0x8000;
const std::size_t kArrayOneStore = 0x1000;
const std::size_t kArrayTwoStore = 0x2000;
const std::size_t kSlotStore = 0x3000;
const std::size_t kPendingStore = 0x4000;
const std::size_t kObjectStore = 0x5000;
const std::size_t kTransferStore = 0x6000;

std::vector<std::uint8_t> g_image;

// -- the observer log --------------------------------------------------------
//
// Every call the reconstruction makes is appended here, so an expectation is a
// literal count and a literal list of (callee, argument) pairs.
struct Call {
  int callee;
  std::size_t first;
  std::size_t second;
  std::size_t third;
};

std::vector<Call> g_calls;

enum : int {
  kProbeQuery = 1,    // 0x00fad140
  kProbeNotify = 2,   // 0x00fa29b0
  kProbeRelease = 3,  // 0x00f9f620
  kProbeSecond = 4,   // 0x00fadac0
  kProbeGrow = 5,     // 0x004558a0
  kIndirect = 6       // the body's one indirect transfer
};

int g_query_result = 0;
Real g_query_pattern[4] = {0.0f, 0.0f, 0.0f, 0.0f};

union TransferAddress {
  void (*fn)(void*, Word);
  void* raw;
};

std::size_t calls_to(int callee) {
  std::size_t total = 0;
  for (std::size_t i = 0; i < g_calls.size(); ++i) {
    if (g_calls[i].callee == callee) {
      ++total;
    }
  }
  return total;
}

}  // namespace

extern "C" std::uint8_t probe_00fad140(void* object, Real* query,
                                        Word third) {
  Call call;
  call.callee = kProbeQuery;
  call.first = reinterpret_cast<std::size_t>(object);
  call.second = 0;
  call.third = third;
  g_calls.push_back(call);
  for (std::size_t i = 0; i < 4; ++i) {
    query[i] = g_query_pattern[i];
  }
  return static_cast<std::uint8_t>(g_query_result);
}

extern "C" void probe_00fa29b0(Word packed_index) {
  Call call;
  call.callee = kProbeNotify;
  call.first = packed_index;
  call.second = 0;
  call.third = 0;
  g_calls.push_back(call);
}

extern "C" void probe_00f9f620(void* base, Word cursor) {
  Call call;
  call.callee = kProbeRelease;
  call.first = reinterpret_cast<std::size_t>(base);
  call.second = cursor;
  call.third = 0;
  g_calls.push_back(call);
}

extern "C" void probe_00fadac0(void* object) {
  Call call;
  call.callee = kProbeSecond;
  call.first = reinterpret_cast<std::size_t>(object);
  call.second = 0;
  call.third = 0;
  g_calls.push_back(call);
}

extern "C" void probe_004558a0(void* cursor, const void* value) {
  Call call;
  call.callee = kProbeGrow;
  call.first = reinterpret_cast<std::size_t>(cursor);
  call.second = reinterpret_cast<std::size_t>(value);
  call.third = 0;
  g_calls.push_back(call);
}

namespace {

// The body's one indirect transfer, 0x00fa536a. It is reached only when the
// word at object+0x4 reaches zero, and the machine pushes the immediate 1 and
// passes the object in the first register.
void indirect_entry(void* object, Word argument) {
  Call call;
  call.callee = kIndirect;
  call.first = reinterpret_cast<std::size_t>(object);
  call.second = argument;
  call.third = 0;
  g_calls.push_back(call);
}

// -- the fixture -------------------------------------------------------------

std::size_t pending_store_of(std::size_t group) {
  return kPendingStore + group * 0x40u;
}


void reset_image() {
  g_image.assign(kImageBytes, 0);
  g_calls.clear();
  g_query_result = 0;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 0.0f;
  }
}

std::uint8_t* at(std::size_t offset) { return g_image.data() + offset; }

void poke(std::size_t offset, Word value) {
  std::memcpy(at(offset), &value, sizeof(value));
}

Word peek(std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, at(offset), sizeof(value));
  return value;
}

void poke_word_at(std::size_t offset, Word value) { poke(offset, value); }

void poke_real(std::size_t offset, Real value) {
  std::memcpy(at(offset), &value, sizeof(value));
}

void poke_pointer(std::size_t offset, void* value) {
  std::memcpy(at(offset), &value, sizeof(value));
}

// Give the array `count` elements and write `keys[i]` at element i's key field.
// The end word is placed on the stride grid, which is the only shape the
// tail's EQUALITY-terminated cursor walk terminates on.
void build_array(std::size_t base_offset, std::size_t store,
                 const std::vector<Word>& keys) {
  for (std::size_t i = 0; i < keys.size(); ++i) {
    poke(store + i * kElementStride + kOffElementKey, keys[i]);
  }
  poke(base_offset, static_cast<Word>(store));
  poke(base_offset + 4u,
       static_cast<Word>(store + keys.size() * kElementStride));
}

// The two-element array every behavioural case starts from, with the wanted key
// at index zero. Two elements means the tail's cursor walk runs exactly once:
// the cursor starts one stride past the found element and stops when it EQUALS
// the end word, and with two elements that is one iteration.
void build_two_element_array(std::size_t base_offset, std::size_t store) {
  build_array(base_offset, store, std::vector<Word>{0x2222u, 0x3333u});
}

void build_record(std::size_t store, std::size_t element, std::size_t record,
                  Real a, Real b, Real c, Real d) {
  const std::size_t field = store + element * kElementStride +
                            kOffElementRecord + record * kInnerRecordStride;
  poke_real(field + 0x0u, a);
  poke_real(field + 0x4u, b);
  poke_real(field + 0x8u, c);
  poke_real(field + 0xcu, d);
}

// One sub-table: `count` slot words, all pointing at the same object, whose
// first word is the indirect transfer's table and whose word at +0xb8 carries
// the gate bit. The pending vector starts empty with room for two words.
void build_sub_table(std::size_t group, std::size_t count, Word refcount) {
  const std::size_t table = kOffSubTableGroup + group * kSubTableStride;
  const std::size_t object = kObjectStore + group * 0x40u;
  const std::size_t slot = kSlotStore + group * 0x40u;

  // 0x00fa5361..0x00fa5364 is a TWO-level load: the object's first word is a
  // pointer, and the word at that pointer is the destination. The fixture
  // builds both levels, because a single level would not exercise the shape the
  // listing has.
  TransferAddress address;
  address.fn = &indirect_entry;
  poke_pointer(object + kOffObjectFirstWord, at(kTransferStore + group * 0x40u));
  poke_pointer(kTransferStore + group * 0x40u, address.raw);
  poke(object + kOffRefCount, refcount);
  poke(object + kOffObjectGateWord, 0x8u);

  for (std::size_t i = 0; i < count; ++i) {
    poke_pointer(slot + i * kVectorWordSize, at(object));
  }
  poke(table + kOffVectorBegin, static_cast<Word>(slot));
  poke(table + kOffVectorEnd,
       static_cast<Word>(slot + count * kVectorWordSize));

  // The pending vector's words are real ADDRESSES here, because the body
  // dereferences the end word (MOV [EAX],EDI at 0x00fa53a3). The array words
  // above are offsets, which is legitimate: the body only ever adds a stride to
  // them and never dereferences one directly.
  const std::size_t pending = table + kPendingVectorOffsetFromSubTable;
  const std::size_t store = pending_store_of(group);
  poke_pointer(pending + kOffVectorBegin, at(store));
  poke_pointer(pending + kOffVectorEnd, at(store));
  poke_pointer(pending + kOffVectorCapacity, at(store + 8u));
}

std::size_t sub_table_of(std::size_t group) {
  return kOffSubTableGroup + group * kSubTableStride;
}

std::size_t pending_of(std::size_t group) {
  return sub_table_of(group) + kPendingVectorOffsetFromSubTable;
}

std::size_t object_of(std::size_t group) { return kObjectStore + group * 0x40u; }

std::size_t slot_store_of(std::size_t group) {
  return kSlotStore + group * 0x40u;
}

Receiver* receiver() { return reinterpret_cast<Receiver*>(g_image.data()); }

// == L: the header's constants, against literals written here ===============
void l_constants() {
  check_word(kTargetVa, 0x00fa5040u, "L1 target va");
  check(kInstructionCount == 297, "L2 instruction count");
  check(kBodySpanBytes == 1009, "L3 body span bytes");
  check(kFrameLocalBytes == 28, "L4 frame local bytes");
  check(kSavedRegisterCount == 4, "L5 saved register count");
  check_word(kObservedCalleePoppedBytes, 8, "L6 callee popped bytes");
  check_word(kRetImmediateBytes, 8, "L7 ret immediate bytes");
  check(kOffArrayTwoBase == 0x770u, "L8 second array base");
  check(kOffArrayTwoEnd == 0x774u, "L9 second array end");
  check(kOffArrayOneBase == 0x784u, "L10 first array base");
  check(kOffArrayOneEnd == 0x788u, "L11 first array end");
  check(kElementStride == 0xacu, "L12 element stride");
  check_word(kElementDecrement, 0xffffff54u, "L13 element decrement");
  check(kOffElementKey == 0xa8u, "L14 key displacement");
  check(kOffElementRecord == 0x38u, "L15 record displacement");
  check(kRecordFieldOffsets[0] == 0x38u && kRecordFieldOffsets[1] == 0x3cu &&
            kRecordFieldOffsets[2] == 0x40u && kRecordFieldOffsets[3] == 0x44u,
        "L16 record field displacements");
  check(kQueryFieldOrder[0] == 1u && kQueryFieldOrder[1] == 0u &&
            kQueryFieldOrder[2] == 3u && kQueryFieldOrder[3] == 2u,
        "L17 query-to-record pairing");
  check(kQueryFloatCount == 4, "L18 query float count");
  check(kInnerRecordStride == 0x10u, "L19 inner record stride");
  check(kInnerRecordLimit == 0x60u, "L20 inner record limit");
  check(kInnerRecordCount == 6, "L21 inner record count");
  check(kOffObjectGateWord == 0xb8u, "L22 gate word displacement");
  check(kGateWordShift == 3, "L23 gate word shift");
  check(kGateWordMask == 0x1u, "L24 gate word mask");
  check(kOffSubTableGroup == 0x218u, "L25 sub-table group displacement");
  check(kSubTableStride == 0x14u, "L26 sub-table stride");
  check(kSubTableCount == 4, "L27 sub-table count");
  check(kOffPendingVector == 0x268u, "L28 pending vector displacement");
  check(kPendingVectorOffsetFromSubTable == 0x50u, "L29 pending vector offset");
  check(kOffVectorBegin == 0x0u && kOffVectorEnd == 0x4u &&
            kOffVectorCapacity == 0x8u,
        "L30 vector word displacements");
  check(kVectorWordSize == 4, "L31 vector word size");
  check(kGroupIndexShift == 0x18, "L32 group index shift");
  check(kGroupIndexMask == 0xffffffu, "L33 group index mask");
  check(kOffRefCount == 0x4u, "L34 refcount displacement");
  check_word(kRefCountReset, 1, "L35 refcount reset");
  check(kOffObjectFirstWord == 0x0u, "L36 object first word");
  check(kIndirectEntryIndex == 0, "L37 indirect entry index");
  check_word(kIndirectArgument, 1, "L38 indirect argument");
  check_word(kClearedWord, 0, "L39 cleared word");
  check_word(kProbeThirdArgument, 0, "L40 probe third argument");
  check(kSecondSlotByteMask == 0xffu, "L41 second slot byte mask");
  check(kUnitWord == 1, "L42 unit word");
  check(kFirstStackArgumentOffset == 4, "L43 first stack slot");
  check(kSecondStackArgumentOffset == 8, "L44 second stack slot");
  check(kFrameDisplacementOfFirstSlot == 0x30u, "L45 first slot frame offset");
  check(kFrameDisplacementOfSecondSlot == 0x34u, "L46 second slot frame offset");
  check(kSecondStackArgumentBytesRead == 1, "L47 second slot bytes read");
  check(kDirectCalleeCount == 5, "L48 direct callee count");
  check(kDirectCallSiteCount == 7, "L49 direct call site count");
  check(kIndirectTransferCount == 1, "L50 indirect transfer count");
  check(kConditionalBranchCount == 39, "L51 conditional branch count");
  check(kAbsoluteJumpCount == 3, "L52 absolute jump count");
  check(kDataSegmentReferenceCount == 0, "L53 data references");
  check(kKeyArgumentBytes == 4, "L54 key argument bytes");

  // The record's own four receiver displacements, against the four the evidence
  // pack enumerates. bounds_only is the record's own statement that the
  // enumeration is open, so it is carried as an open bound, not a layout.
  check(kReceiverPresent, "L55 receiver present");
  check(kReceiverBoundsOnly, "L56 receiver bounds only");
  check(kReceiverDisplacementCount == 4, "L57 receiver displacement count");
  check(kReceiverDisplacements[0] == 0x770u &&
            kReceiverDisplacements[1] == 0x774u &&
            kReceiverDisplacements[2] == 0x784u &&
            kReceiverDisplacements[3] == 0x788u,
        "L58 receiver displacements");
  check(kReceiverWrittenThrough == 0, "L59 receiver written-through count");
  check(kDerivedConventionCandidateCount == 4, "L60 convention candidate count");
  check(kDerivedConventionConfidence == ConventionConfidence::kUnknown,
        "L61 convention confidence is UNKNOWN");
  check(kDerivedReceiverRegister == ReceiverRegister::kEcx, "L62 receiver register");
  check(kDerivedAbstentionCount == 3, "L63 abstention count");
  check(std::strcmp(kDerivedAbstentionReasons[0],
                    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: "
                    "EBP is a general register, so every frame-relative "
                    "offset is uncalibrated") == 0,
        "L64 first abstention reason");
  check(kObservedCleanupSide == CleanupSide::kCallee, "L65 cleanup side");
  check(kRecordObservedStackArgumentSlots == 1, "L66 record slot count");
  check(kCalibratedStackArgumentSlots == 2, "L67 calibrated slot count");
  check(!kSecondStackArgumentWidthIsDetermined,
        "L68 second slot width undetermined");
}

// == M: the count sequence, against C division written here =================
//
// The machine never states a divisor. This block does not assume one: it
// compares the package's transcription of the eight-instruction sequence
// against C signed truncated division by 0xac -- the stride the loops that
// consume the count actually step by -- over a wide sample of inputs.
void m_count_sequence() {
  bool same = true;
  for (long value = -4000; value <= 4000 && same; ++value) {
    const Word span = static_cast<Word>(static_cast<std::int32_t>(value));
    const std::int32_t signed_span = static_cast<std::int32_t>(span);
    const std::int32_t magnitude = signed_span < 0 ? -signed_span : signed_span;
    const std::int32_t quotient = magnitude / 172;
    const std::int32_t want = signed_span < 0 ? -quotient : quotient;
    if (static_cast<std::int32_t>(element_count(span)) != want) {
      same = false;
    }
  }
  check(same, "M1 the count sequence equals truncated division by 0xac near zero");

  bool strides = true;
  for (std::size_t elements = 0; elements < 512; ++elements) {
    if (element_count(static_cast<Word>(elements * kElementStride)) !=
        elements) {
      strides = false;
    }
  }
  check(strides, "M2 the count sequence returns the element count for spans");

  // The sweep above only reaches small spans, where the multiply's high half is
  // zero and almost any constant agrees. This one walks the 32-bit input space
  // with a fixed linear congruential sequence, so a magic constant that is off
  // by one is caught rather than tolerated. The expected value is C signed
  // truncated division by the literal 172, written here.
  bool sweep = true;
  std::uint32_t state = 12345u;
  for (std::size_t i = 0; i < 200000u; ++i) {
    state = state * 1103515245u + 12345u;
    const std::int32_t value = static_cast<std::int32_t>(state) - 1073741824;
    const std::int32_t magnitude = value < 0 ? -value : value;
    const std::int32_t quotient = magnitude / 172;
    const std::int32_t want = value < 0 ? -quotient : quotient;
    if (static_cast<std::int32_t>(element_count(static_cast<Word>(value))) !=
        want) {
      sweep = false;
      break;
    }
  }
  check(sweep, "M3 the count sequence matches over a 200000-point 32-bit sweep");

  check_word(word_span_count(0), 0, "M4 word span count of zero");
  check_word(word_span_count(8), 2, "M5 word span count of eight");
  check_word(word_span_count(0xfffffffcu), 0xffffffffu,
             "M6 the word span count shifts the sign");
}

// == N: the argument surface ================================================
//
// The record observed ONE stack slot and abstained on the offsets; this package
// calibrated two from the frame arithmetic. The two facts are kept apart here
// rather than merged, and the divergence is asserted rather than hidden.
void n_argument_surface() {
  const std::size_t frame = kFrameLocalBytes + 4u * kSavedRegisterCount;
  check(0x2cu == frame, "N1 the frame is 0x2c bytes deep");
  check(kFrameDisplacementOfFirstSlot - frame == kFirstStackArgumentOffset,
        "N2 the first slot resolves to entry_ESP+0x4");
  check(kFrameDisplacementOfSecondSlot - frame == kSecondStackArgumentOffset,
        "N3 the second slot resolves to entry_ESP+0x8");
  check(kRecordObservedStackArgumentSlots != kCalibratedStackArgumentSlots,
        "N4 the record's slot count and this package's differ, and that is kept");
  check(kObservedCalleePoppedBytes == 2u * kVectorWordSize,
        "N5 two words are popped");
}

// == B: the behavioural cases ===============================================
//
// Every case below is a two-element array with the wanted key at index zero,
// so the tail's cursor walk -- which stops on an EQUALITY against the end word,
// not a bound -- runs exactly once. That is the machine's own arithmetic: the
// cursor starts one stride past the found element (LEA ESI,[EBP + 0xac] at
// 0x00fa5203), and with two elements the end word is two strides on, so the
// single cursor in between is not equal to it and the loop runs once.

void b_not_found() {
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_two_element_array(kOffArrayTwoBase, kArrayTwoStore);
  const Word end_one = peek(kOffArrayOneEnd);
  const Word end_two = peek(kOffArrayTwoEnd);

  check(!re_00fa5040(receiver(), 0x9999u, 0x1u),
        "B1 a key in neither array returns false");
  check_size(g_calls.size(), 0u, "B2 a key in neither array makes no call");
  check_word(peek(kOffArrayOneEnd), end_one, "B3 the first array's end is unchanged");
  check_word(peek(kOffArrayTwoEnd), end_two, "B4 the second array's end is unchanged");
}

void b_empty_arrays() {
  reset_image();
  build_array(kOffArrayOneBase, kArrayOneStore, std::vector<Word>{});
  build_array(kOffArrayTwoBase, kArrayTwoStore, std::vector<Word>{});
  check(!re_00fa5040(receiver(), 0x1u, 0x1u),
        "B5 two empty arrays return false");
  check_size(g_calls.size(), 0u, "B6 two empty arrays make no call");
}

void b_first_array_flag_zero() {
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_two_element_array(kOffArrayTwoBase, kArrayTwoStore);
  const std::size_t start = kArrayOneStore;

  check(re_00fa5040(receiver(), 0x2222u, 0x0u),
        "B7 a first-array hit returns true");
  // 0x00fa50e3 tests the low byte of the second word; zero skips the four
  // sub-tables, so no query, notify, second-release or grow call may appear.
  if (check_size(g_calls.size(), 1u, "B8 the sub-tables are skipped")) {
    check(g_calls[0].callee == kProbeRelease, "B9 the only call is the release");
    check(g_calls[0].first == start, "B10 the release base is the found element");
    check_word(static_cast<Word>(g_calls[0].second),
               static_cast<Word>(start + kElementStride),
               "B11 the release cursor is one stride on");
  }
  check_word(peek(kOffArrayOneEnd),
             static_cast<Word>(kArrayOneStore + kElementStride),
             "B12 the first array's end is pulled back one stride");
  check_word(peek(kOffArrayTwoEnd),
             static_cast<Word>(kArrayTwoStore + 2u * kElementStride),
             "B13 the second array is untouched");
}

void b_first_array_flag_set_empty_subtables() {
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  for (std::size_t group = 0; group < kSubTableCount; ++group) {
    build_sub_table(group, 0, 1);
  }
  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B14 a first-array hit with four empty sub-tables returns true");
  if (check_size(g_calls.size(), 1u, "B15 only the tail's release runs")) {
    check(g_calls[0].callee == kProbeRelease, "B16 and it is the release");
  }
}

void b_first_array_query_never_matches() {
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  g_query_result = 0;  // 0x00fad140 misses on every record

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B17 a first-array hit whose sub-table never matches still returns true");
  if (check_size(g_calls.size(), 7u, "B18 six queries then one release")) {
    for (std::size_t i = 0; i < 6u; ++i) {
      check(g_calls[i].callee == kProbeQuery, "B19 each inner record queries once");
      check(g_calls[i].first == reinterpret_cast<std::size_t>(at(object_of(0))),
            "B20 the query gets the object");
      check(g_calls[i].third == 0, "B21 the query's third argument is zero");
    }
    check(g_calls[6].callee == kProbeRelease, "B22 the release follows the queries");
  }
  check_size(calls_to(kProbeNotify), 0u, "B23 no notify without a hit");
}

void b_gate_bit_is_bit_three() {
  // SHR 3 then TEST 1 at 0x00fa512c..0x00fa512f opens the object on bit 3 of
  // the word at object+0xb8 and on nothing else.
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  build_record(kArrayOneStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }
  poke(object_of(0) + kOffObjectGateWord, 0x4u);  // bit 2 only

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B24 a closed gate still returns true");
  check_size(calls_to(kProbeQuery), 0u, "B25 bit 2 alone does not open the gate");

  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  build_record(kArrayOneStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }
  poke(object_of(0) + kOffObjectGateWord, 0x9u);  // bits 0 and 3

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B26 an open gate still returns true");
  check_size(calls_to(kProbeQuery), 1u, "B27 bit 3 opens the gate");
}

void b_first_array_hit_notifies() {
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(2, 1, 1);
  // Record 0 does not beat the query; record 1 does, so the walk stops after
  // two probes (0x00fa51a1..0x00fa51a8 step on by 0x10 and stop at 0x60).
  build_record(kArrayOneStore, 0, 0, 5.0f, 5.0f, 5.0f, 5.0f);
  build_record(kArrayOneStore, 0, 1, 1.0f, 1.0f, 1.0f, 1.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 2.0f;
  }

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B28 a first-array hit with a beating record returns true");
  if (check_size(g_calls.size(), 4u, "B29 two queries, a notify, one release")) {
    check(g_calls[2].callee == kProbeNotify, "B30 the notify is the third call");
    // group 2, slot 0: (2 << 0x18) | 0.
    check_word(static_cast<Word>(g_calls[2].first), 0x02000000u,
               "B31 the packed index is group 2, slot 0");
    check(g_calls[3].callee == kProbeRelease, "B32 the release is last");
  }
  // No refcount, no indirect transfer and no pending write on this path.
  check_size(calls_to(kIndirect), 0u, "B33 the first-array path never dispatches");
  check_size(calls_to(kProbeSecond), 0u, "B34 and never makes the second release");
  check_size(calls_to(kProbeGrow), 0u, "B35 and never grows");
}

void b_group_and_slot_order() {
  // The group walk is ascending 0..3 (CMP EAX,0x4 / JL at 0x00fa51de) and the
  // slot walk is descending (SUB EBX,0x1 / JNS at 0x00fa51b2..0x00fa51cc), so
  // the LAST slot of the LAST non-empty group is notified first, with the
  // packed index carrying the group in the high byte.
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  for (std::size_t group = 0; group < kSubTableCount; ++group) {
    build_sub_table(group, group == 3u ? 2u : 0u, 1);
  }
  build_record(kArrayOneStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B36 a hit in the last group still returns true");
  // Both slots hold the same object, so both hit on their first record: the
  // walk is query, notify, query, notify, release -- and the ORDER of the two
  // packed indices is the descending slot walk at 0x00fa51b2..0x00fa51cc.
  if (check_size(g_calls.size(), 5u, "B37 two queries, two notifies, one release")) {
    check_word(static_cast<Word>(g_calls[1].first), 0x03000001u,
               "B38 the first packed index is group 3, slot 1");
    check_word(static_cast<Word>(g_calls[3].first), 0x03000000u,
               "B39 the second packed index is group 3, slot 0");
  }
}

void b_group_walk_is_ascending() {
  // The group walk starts at zero and increments (XOR ESI,ESI at 0x00fa50aa is
  // the second array's, INC ECX at 0x00fa53c7 and the copy at 0x00fa51da are
  // the first's, both against a guard of 4). Two non-empty groups make the
  // ORDER observable through the order of the packed indices.
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(1, 1, 1);
  build_sub_table(3, 1, 1);
  build_record(kArrayOneStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B93 two non-empty groups still return true");
  if (check_size(calls_to(kProbeNotify), 2u, "B94 both groups notified")) {
    check_word(static_cast<Word>(g_calls[1].first), 0x01000000u,
               "B95 the FIRST notify is group 1");
    check_word(static_cast<Word>(g_calls[3].first), 0x03000000u,
               "B96 the SECOND notify is group 3");
  }
}

void b_second_array_group_walk_is_ascending() {
  // The second-array group walk starts at the word saved by MOV [ESP + 0x14],
  //EBX at 0x00fa5251, which is zero, and increments it at 0x00fa53c7 against a
  // guard of 4 -- so it is ascending there exactly as on the first-array path.
  // Two non-empty groups make the order observable through the order of the
  // 0x00fadac0 calls, because each group's object is a distinct address.
  reset_image();
  build_two_element_array(kOffArrayTwoBase, kArrayTwoStore);
  build_sub_table(1, 1, 9);
  build_sub_table(3, 1, 9);
  build_record(kArrayTwoStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B97 two non-empty second-array groups still return true");
  if (check_size(calls_to(kProbeSecond), 2u, "B98 both groups were released")) {
    check(g_calls[1].first == reinterpret_cast<std::size_t>(at(object_of(1))),
          "B99 the FIRST release names group 1's object");
    check(g_calls[3].first == reinterpret_cast<std::size_t>(at(object_of(3))),
          "B100 the SECOND release names group 3's object");
  }
}

void b_query_pairing_is_not_identity() {
  // The listing pairs query[1] with field 0, query[0] with field 1, query[3]
  // with field 2 and query[2] with field 3. The two conditions differ only when
  // the four query floats differ, and this case is built so that the pairing
  // fires and the identity order does not:
  //   pairing  {p0<100, p1<10, p2<100, p3<100} -- p={50,5,50,50} satisfies it
  //   identity {p0<10, p1<100, p2<100, p3<100} -- p0=50 < 10 is false
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  build_record(kArrayOneStore, 0, 0, 50.0f, 5.0f, 50.0f, 50.0f);
  g_query_result = 1;
  g_query_pattern[0] = 10.0f;
  g_query_pattern[1] = 100.0f;
  g_query_pattern[2] = 100.0f;
  g_query_pattern[3] = 100.0f;

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B40 the pairing hit still returns true");
  if (check_size(calls_to(kProbeQuery), 1u, "B41 the pairing stops at record 0")) {
    check_size(calls_to(kProbeNotify), 1u, "B42 the pairing notified");
  }
}

void b_query_pairing_rejects_an_identity_hit() {
  // The mirror: the identity order would fire, the pairing must not.
  //   pairing  {p0<0, p1<0, p2<1000, p3<0} -- p={1,0,0,0} fails on p0 < 0
  //   identity {p0<0, p1<0, p2<0, p3<1000} -- all four hold, so it would fire
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  for (std::size_t record = 0; record < kInnerRecordCount; ++record) {
    build_record(kArrayOneStore, 0, record, 1.0f, 0.0f, 0.0f, 0.0f);
  }
  g_query_result = 1;
  g_query_pattern[0] = 0.0f;
  g_query_pattern[1] = 0.0f;
  g_query_pattern[2] = 0.0f;
  g_query_pattern[3] = 1000.0f;

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B43 the rejected identity hit still returns true");
  check_size(calls_to(kProbeQuery), 6u, "B44 the pairing walked all six records");
  check_size(calls_to(kProbeNotify), 0u, "B45 and never notified");
}

void b_float_comparison_is_strict() {
  // Every COMISS is followed by JBE, so an EQUAL pair takes the skip. A NaN
  // pair does too, because COMISS sets CF and ZF on an unordered compare and
  // JBE takes the skip -- which is what a C++ `>` on a NaN does.
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  for (std::size_t record = 0; record < kInnerRecordCount; ++record) {
    build_record(kArrayOneStore, 0, record, 50.0f, 50.0f, 50.0f, 50.0f);
  }
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 50.0f;
  }
  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B46 an equal pair still returns true from the tail");
  check_size(calls_to(kProbeNotify), 0u, "B47 equality takes the skip");

  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  const Real nan = std::numeric_limits<Real>::quiet_NaN();
  for (std::size_t record = 0; record < kInnerRecordCount; ++record) {
    build_record(kArrayOneStore, 0, record, nan, nan, nan, nan);
  }
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }
  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B48 an unordered pair still returns true from the tail");
  check_size(calls_to(kProbeNotify), 0u, "B55 an unordered compare takes the skip");
}

void b_second_array_second_release_and_grow() {
  reset_image();
  build_two_element_array(kOffArrayTwoBase, kArrayTwoStore);
  build_sub_table(1, 1, 4);
  build_record(kArrayTwoStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }
  // Fill the pending vector so the grow branch is taken: CMP EAX,[ECX + 0x8] /
  // JNC at 0x00fa5394..0x00fa5397 takes the grow when the end word is not below
  // the capacity word.
  poke_word_at(pending_of(1) + kOffVectorEnd, peek(pending_of(1) + kOffVectorCapacity));

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B55 a second-array hit returns true");
  if (check_size(g_calls.size(), 4u, "B56 a query, a second release, a grow, a release")) {
    check(g_calls[0].callee == kProbeQuery, "B57 the query comes first");
    check(g_calls[0].first == reinterpret_cast<std::size_t>(at(object_of(1))),
          "B58 the query gets the object");
    check(g_calls[1].callee == kProbeSecond, "B59 the second release follows");
    check(g_calls[1].first == reinterpret_cast<std::size_t>(at(object_of(1))),
          "B60 and it gets the same object");
    check(g_calls[2].callee == kProbeGrow, "B61 a full pending vector grows");
  }
  check_word(peek(object_of(1) + kOffRefCount), 3,
             "B62 the word at object+0x4 is decremented");
  check_size(calls_to(kIndirect), 0u, "B63 a refcount above zero does not dispatch");
  check_word(peek(kOffArrayTwoEnd),
             static_cast<Word>(kArrayTwoStore + kElementStride),
             "B64 the second array's end is pulled back one stride");
  check_word(peek(kOffArrayOneEnd), 0, "B65 the first array is untouched");
}

void b_second_array_dispatches_when_the_refcount_reaches_zero() {
  reset_image();
  build_two_element_array(kOffArrayTwoBase, kArrayTwoStore);
  build_sub_table(0, 1, 1);
  build_record(kArrayTwoStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B66 a second-array hit that reaches zero returns true");
  check_size(calls_to(kIndirect), 1u, "B67 a refcount reaching zero dispatches");
  for (std::size_t i = 0; i < g_calls.size(); ++i) {
    if (g_calls[i].callee == kIndirect) {
      check_word(static_cast<Word>(g_calls[i].second), 1,
                 "B68 the dispatch's stack word is the immediate 1");
      check(g_calls[i].first == reinterpret_cast<std::size_t>(at(object_of(0))),
            "B69 the dispatch's first word is the object");
    }
  }
  check_word(peek(object_of(0) + kOffRefCount), 1,
             "B70 the word at object+0x4 is reset to one after the dispatch");
}

void b_second_array_appends() {
  reset_image();
  build_two_element_array(kOffArrayTwoBase, kArrayTwoStore);
  build_sub_table(2, 1, 9);
  build_record(kArrayTwoStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B71 an appended pending vector still returns true");
  check_size(calls_to(kProbeGrow), 0u, "B72 room in the vector avoids the grow");
  check_word(peek(pending_of(2) + kOffVectorEnd),
             static_cast<Word>(reinterpret_cast<std::size_t>(
                 at(pending_store_of(2) + kVectorWordSize))),
             "B73 the pending vector's end advances one word");
  check_word(peek(pending_store_of(2)), 0,
             "B74 the slot index is stored through the end word");
}

void b_second_array_null_cursor() {
  // TEST EAX,EAX / JZ at 0x00fa539f..0x00fa53a1: with room to spare and a NULL
  // end word the end word still advances and the store is skipped.
  reset_image();
  build_two_element_array(kOffArrayTwoBase, kArrayTwoStore);
  build_sub_table(0, 1, 9);
  build_record(kArrayTwoStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }
  poke_word_at(pending_of(0) + kOffVectorEnd, 0);
  poke_word_at(pending_of(0) + kOffVectorCapacity, 0x100);

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B75 a null cursor still returns true");
  check_word(peek(pending_of(0) + kOffVectorEnd), kVectorWordSize,
             "B76 the end word still advances by one word");
}

void b_second_array_slot_order_is_descending() {
  // The second-array element walk is descending in exactly the way the
  // first-array one is: the index starts at count-1 and 0x00fa53b2 decrements
  // it. Two slots make the order observable, because 0x00fadac0 fires once per
  // slot and each slot word holds a distinct address.
  // The two slots are made to behave differently so the ORDER is observable:
  // slot 1's object starts at a refcount of one and therefore dispatches, and
  // slot 0's object starts at nine and therefore does not. A descending walk
  // gives release-then-dispatch; an ascending one gives the reverse.
  reset_image();
  build_two_element_array(kOffArrayTwoBase, kArrayTwoStore);
  build_sub_table(0, 2, 1);
  const std::size_t quiet = kObjectStore + 0x200u;
  TransferAddress quiet_address;
  quiet_address.fn = &indirect_entry;
  poke_pointer(quiet + kOffObjectFirstWord, at(kTransferStore + 0x200u));
  poke_pointer(kTransferStore + 0x200u, quiet_address.raw);
  poke(quiet + kOffRefCount, 9);
  poke(quiet + kOffObjectGateWord, 0x8u);
  poke_pointer(slot_store_of(0), at(quiet));
  build_record(kArrayTwoStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }

  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B89 two slots on the second-array path still return true");
  if (check_size(calls_to(kProbeSecond), 2u, "B90 both slots were released")) {
    check_size(calls_to(kIndirect), 1u, "B91 only slot 1's object dispatched");
    // Descending: query, release, dispatch for slot 1, then query, release for
    // slot 0. Ascending would put the dispatch LAST instead.
    check(g_calls[0].callee == kProbeQuery && g_calls[1].callee == kProbeSecond &&
              g_calls[2].callee == kIndirect && g_calls[3].callee == kProbeQuery &&
              g_calls[4].callee == kProbeSecond,
          "B92 the dispatch belongs to the FIRST slot walked, so the walk descends");
  }
}

void b_slot_cleared() {
  // MOV dword ptr [EDX + EDI*0x4],0x0 at 0x00fa5386 clears the taken slot.
  reset_image();
  build_two_element_array(kOffArrayTwoBase, kArrayTwoStore);
  build_sub_table(0, 1, 9);
  build_record(kArrayTwoStore, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f);
  g_query_result = 1;
  for (std::size_t i = 0; i < 4; ++i) {
    g_query_pattern[i] = 1.0f;
  }
  check(re_00fa5040(receiver(), 0x2222u, 0x1u),
        "B77 a cleared slot still returns true");
  check_word(peek(slot_store_of(0)), 0, "B78 the taken slot is cleared to zero");
}

void b_second_stack_word_high_bytes_are_not_read() {
  // CMP byte ptr [ESP + 0x34],BL at 0x00fa50e3 reads ONE byte. Two words that
  // differ only above that byte must behave identically, and a clear low byte
  // must skip the sub-tables whatever the upper bytes hold.
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  g_query_result = 0;

  // Each call pulls the array's end word back by one stride, so the fixture is
  // rebuilt between them: three calls on one image would be three different
  // array lengths, and the comparison would be about that rather than about the
  // stack word.
  const bool first = re_00fa5040(receiver(), 0x2222u, 0x00000101u);
  const std::size_t calls_first = g_calls.size();
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  g_query_result = 0;
  const bool second = re_00fa5040(receiver(), 0x2222u, 0xffffff01u);
  check(first && second, "B79 both words with a set low byte behave the same");
  check_size(g_calls.size(), calls_first, "B80 and make the same number of calls");

  // The sub-table is rebuilt here too: without one, a reconstruction that
  // ignored the flag entirely would walk four empty sub-tables and make no
  // call, and the test would not see the difference.
  reset_image();
  build_two_element_array(kOffArrayOneBase, kArrayOneStore);
  build_sub_table(0, 1, 1);
  g_query_result = 0;
  const bool third = re_00fa5040(receiver(), 0x2222u, 0xfffffe00u);
  check(third, "B81 a clear low byte still returns true");
  check_size(g_calls.size(), 1u, "B82 and only the tail's release runs");
  check_size(calls_to(kProbeQuery), 0u, "B83 a clear low byte never queries");
}

void b_key_is_a_full_word() {
  // CMP dword ptr [ECX],EDI at 0x00fa5080 is a full 32-bit equality against the
  // word the caller left at entry_ESP+0x4.
  reset_image();
  build_array(kOffArrayOneBase, kArrayOneStore,
              std::vector<Word>{0x11110000u, 0x22220000u});
  build_array(kOffArrayTwoBase, kArrayTwoStore, std::vector<Word>{});
  check(!re_00fa5040(receiver(), 0x00001111u, 0x0u),
        "B83 a key differing only in the upper bytes is not found");
  check_size(g_calls.size(), 0u, "B84 and makes no call");
  check(re_00fa5040(receiver(), 0x11110000u, 0x0u),
        "B85 the exact key is found");

  // A reconstruction that compared only the low byte of the key would stop at
  // the first element whose low byte matched. Two elements sharing a low byte
  // and differing above it separate the two, and the release base says which
  // one was taken.
  // Three elements, so the found one is not the last and the tail's walk has
  // somewhere to go. A byte comparison would take element 0 and a word
  // comparison takes element 1, and the release base says which.
  reset_image();
  build_array(kOffArrayOneBase, kArrayOneStore,
              std::vector<Word>{0x00001111u, 0x22221111u, 0x33332222u});
  build_array(kOffArrayTwoBase, kArrayTwoStore, std::vector<Word>{});
  g_calls.clear();
  check(re_00fa5040(receiver(), 0x22221111u, 0x0u),
        "B86 a key sharing its low byte with an earlier element is found");
  if (check_size(g_calls.size(), 1u, "B87 one release follows")) {
    check(g_calls[0].first == kArrayOneStore + kElementStride,
          "B88 and the release base is the SECOND element, not the first");
  }
}

void b_first_array_wins() {
  // The first array is scanned first (0x00fa5074 reads the word at 0x784 and
  // the second scan at 0x00fa50b0 reads the word at 0x770), so a key present in
  // both is taken from the first and the second array is never written.
  reset_image();
  build_array(kOffArrayOneBase, kArrayOneStore,
              std::vector<Word>{0x2222u, 0x3333u});
  build_array(kOffArrayTwoBase, kArrayTwoStore,
              std::vector<Word>{0x2222u, 0x4444u});
  check(re_00fa5040(receiver(), 0x2222u, 0x0u),
        "B86 a key in both arrays returns true");
  check_word(peek(kOffArrayOneEnd),
             static_cast<Word>(kArrayOneStore + kElementStride),
             "B87 the first array is the one pulled back");
  check_word(peek(kOffArrayTwoEnd),
             static_cast<Word>(kArrayTwoStore + 2u * kElementStride),
             "B88 the second array is untouched");
}

}  // namespace

int main() {
  l_constants();
  m_count_sequence();
  n_argument_surface();
  b_not_found();
  b_empty_arrays();
  b_first_array_flag_zero();
  b_first_array_flag_set_empty_subtables();
  b_first_array_query_never_matches();
  b_gate_bit_is_bit_three();
  b_first_array_hit_notifies();
  b_group_and_slot_order();
  b_group_walk_is_ascending();
  b_second_array_group_walk_is_ascending();
  b_query_pairing_is_not_identity();
  b_query_pairing_rejects_an_identity_hit();
  b_float_comparison_is_strict();
  b_second_array_second_release_and_grow();
  b_second_array_dispatches_when_the_refcount_reaches_zero();
  b_second_array_appends();
  b_second_array_null_cursor();
  b_second_array_slot_order_is_descending();
  b_slot_cleared();
  b_second_stack_word_high_bytes_are_not_read();
  b_key_is_a_full_word();
  b_first_array_wins();

  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
