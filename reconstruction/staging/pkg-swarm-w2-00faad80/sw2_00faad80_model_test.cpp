// PKG-SWARM-W2-00FAAD80 -- model test for re_00faad80 @ 0x00faad80
//
// A falsification test, not a walk-through. Every direct callee is defined here as an
// observer that records what it was handed, in what order, and what the receiver looked
// like AT THE MOMENT OF THE CALL -- because the three highest-risk classes of mistake in
// this body are an argument order, a write ordering and a pointer depth, and none of
// them is visible in a return value.
//
// WHAT IS ASSERTED, and why each is asserted:
//
//   * the three-way branch on the receiver's +0xa48 word, and that its middle arm is a
//     SIGNED compare (0x00faad93 is JLE, not JBE);
//   * the exact byte set the body changes in the receiver, per case, over a padded
//     buffer so a write outside the listed offsets cannot hide;
//   * the two-level reads: every bounds displacement through the POINTER at +0x2c (with
//     decoy bounds objects planted at +0x28 and +0x30), and every row read through the
//     +0x118 word table (with a decoy either side of the table);
//   * the source row of iteration i of page k, with the page RE-READ on every iteration;
//   * the destination row addresses, expressed through the 0x828 cursor;
//   * the 16-byte frame slot, its entry-ESP-relative offset, and the fact that the bound
//     word and the row words ALIAS;
//   * the argument list and order of all 15 direct callees, measured at the callee;
//   * the ECX receiver of the slot+0x4c and slot+0xd8 calls, and that only their AL is
//     tested (a callee returning 256 must read as "no"/"no substitution");
//   * that the call at 0x00faaf0b receives the indeterminate-ECX sentinel and NOT the
//     receiver, and that it never receives the +0x20c word;
//   * that the two pointer arguments of 0x00f9b8c0 are the SAME address and that reading
//     through either yields the caller's first argument;
//   * that the relay commit sees the value the relay BUILDER left, not the original;
//   * that the three globals are zeroed AFTER the slot+0x10 call, not before;
//   * that the resync compare reports an UNORDERED pair as "the same", which is what the
//     UCOMISS/LAHF/TEST AH,0x44/JP sequence does and what C's != does not;
//   * the float arithmetic of the distance test, in the listing's own order, and the
//     32-bit wrap of the phase byte's address.
//
// WHAT IS DELIBERATELY NOT ASSERTED:
//
//   * EAX, EDX, EBX and the x87 stack at either return. The record's return_semantics is
//     the phrase "float_or_x87_in_ST0"; the machine produces nothing in ST0 on either
//     path (the x87 stack is empty at 0x00faade0 and at 0x00fab0d1) and EAX is dead, so
//     the declared type is void and there is no return value to compare. The sidecar
//     records the disagreement with the record.
//   * What is inside the six row objects at the receiver's +0x118. The body only LOADS
//     each word and passes it as a receiver, so the test plants six distinguishable
//     receiver objects and asserts the right one reached each call, and nothing more.
//   * The conventions of the six callees whose own terminator was not read out of the
//     image. For those, only "receiver in ECX, no stack word" is asserted, which is all
//     the listing fixes at those call sites.
//   * The identity of 0x016c9e8c and of the three words at 0x016c9e7c. The body zeroes
//     the three and passes the fourth by value; the test asserts exactly that.
//   * Whether the resync flag byte at +0x111 alone (with both compares equal) triggers
//     the block. It does per the listing, and case E covers exactly that, but no case
//     claims to know why the flag exists.

#include "sw2_00faad80_types.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <limits>
#include <vector>

namespace pk = openspore::reconstruction::pkg_swarm_w2_00faad80;

using pk::Receiver;
using pk::Row4;
using pk::Word;

namespace {

// ---------------------------------------------------------------------------
// Harness
// ---------------------------------------------------------------------------

int g_failures = 0;
int g_checks = 0;
const char* g_case = "";

void check(bool ok, const char* what, int line) {
  ++g_checks;
  if (!ok) {
    ++g_failures;
    std::printf("FAIL [%s] line %d: %s\n", g_case, line, what);
  }
}

#define CHECK(cond) check((cond), #cond, __LINE__)

void begin_case(const char* name) {
  g_case = name;
  std::printf("case %s\n", name);
}

// ---------------------------------------------------------------------------
// Observer state. Declared before everything that records into it.
// ---------------------------------------------------------------------------

struct Call {
  const char* name;
  std::uintptr_t receiver;
  Word arg0;
  Word arg1;
  Word arg2;
  float farg;
  const void* pointer0;
  const void* pointer1;
};

std::vector<Call> g_calls;
struct SeenRow {
  Row4 first;
  Row4 second;
  Row4 third;
  int hits;
};
SeenRow g_row_seen[6];
const Row4* g_row_pointer[6];

struct SeenQuery {
  float w0;
  float w1;
  float w2;
  float w3;
  std::uintptr_t receiver;
  Word size;
  Word extra_value;
};
std::vector<SeenQuery> g_row_queries;

Word* g_relay_slot_address = nullptr;
void* g_relay_release_receiver = nullptr;
Word g_relay_word_at_release = 0xffffffffu;
void* g_relay_commit_receiver = nullptr;
Word g_relay_builder_stores = 0;

std::uint8_t g_inside_flag_at_commit = 0xff;
std::uint8_t g_phase_dirty_at_resync = 0xff;
Word g_globals_at_phase_call[3] = {0xffffffffu, 0xffffffffu, 0xffffffffu};

Word g_ready_result = 1;
Word g_row_query_result = 0;
void* g_row_query_extra = nullptr;
void (*g_row_hook_first)() = nullptr;
Receiver* g_hook_receiver = nullptr;

void bump_page_index_to_two() { pk::store_word(g_hook_receiver, pk::kOffPageIndex, 2u); }

alignas(4) std::uint8_t g_row_object[6][16];
alignas(4) std::uint8_t g_stage_root_object[8];
alignas(4) std::uint8_t g_stage_object[8];
alignas(4) std::uint8_t g_peer_object[8];
void* g_receiver_table[96];
void* g_stage_root_table[96];
void* g_stage_table[96];

Call& record(const char* name, void* receiver) {
  Call entry{};
  entry.name = name;
  entry.receiver = reinterpret_cast<std::uintptr_t>(receiver);
  entry.pointer0 = nullptr;
  entry.pointer1 = nullptr;
  g_calls.push_back(entry);
  return g_calls.back();
}

int count_of(const char* name) {
  int total = 0;
  for (const Call& entry : g_calls) {
    if (std::strcmp(entry.name, name) == 0) {
      ++total;
    }
  }
  return total;
}

const Call* find_of(const char* name) {
  for (const Call& entry : g_calls) {
    if (std::strcmp(entry.name, name) == 0) {
      return &entry;
    }
  }
  return nullptr;
}

const Call* find_nth(const char* name, int index) {
  int seen = 0;
  for (const Call& entry : g_calls) {
    if (std::strcmp(entry.name, name) == 0) {
      if (seen == index) {
        return &entry;
      }
      ++seen;
    }
  }
  return nullptr;
}

// ---------------------------------------------------------------------------
// The 15 direct callees, as observers
// ---------------------------------------------------------------------------

extern "C" void* PKG_SWARM_W2_00FAAD80_CDECL renderer_global_get_0067dd80() {
  record("0067dd80", nullptr);
  return g_stage_root_object;
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL relay_release_00690120(void* receiver) {
  record("00690120", receiver);
  g_relay_release_receiver = receiver;
  // The ordering claim of 0x00fab030: the word at the relay slot is ALREADY zero.
  g_relay_word_at_release = *g_relay_slot_address;
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL relay_commit_006909b0(void* receiver) {
  record("006909b0", receiver);
  g_relay_commit_receiver = receiver;
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL page_turn_00f96370(void* receiver) {
  record("00f96370", receiver);
  // Faithful to the callee's own 32 bytes at 0x00f96370..0x00f9638f: clear the byte at
  // receiver+0x368+page, then set receiver+0x36c to 1-page. Reproducing it is what makes
  // the loop's per-iteration re-read of +0x36c load-bearing.
  const Word page = pk::load_word(receiver, pk::kOffPageIndex);
  pk::store_byte(receiver, pk::kOffPageIndex - 4u + page, 0u);
  pk::store_word(receiver, pk::kOffPageIndex, 1u - page);
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL row_block_finish_00f96f90(void* receiver) {
  record("00f96f90", receiver);
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL bounds_resync_00f977c0(void* receiver) {
  record("00f977c0", receiver);
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL one_shot_notify_00f9b8c0(
    void* receiver, Word* first_argument_slot, Word* second_argument_slot, Word gate_flag,
    Word zero_argument, float seconds) {
  Call& entry = record("00f9b8c0", receiver);
  entry.pointer0 = first_argument_slot;
  entry.pointer1 = second_argument_slot;
  entry.arg0 = gate_flag;
  entry.arg1 = zero_argument;
  entry.farg = seconds;
  // The value read through the pointer, sampled HERE: the model's frame is gone by the
  // time the assertions run, so reading the slot afterwards would read dead stack.
  entry.arg2 = *first_argument_slot;
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL settle_amount_00fbf570(
    void* unfixed_ecx, Word first_argument, float amount, Word mode) {
  Call& entry = record("00fbf570", unfixed_ecx);
  entry.arg0 = first_argument;
  entry.arg1 = mode;
  entry.farg = amount;
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL row_apply_first_00fb0d20(
    void* row_object, Word index, const Row4* row) {
  Call& entry = record("00fb0d20", row_object);
  entry.arg0 = index;
  entry.pointer0 = row;
  if (index < 6) {
    g_row_seen[index].first = *row;
    g_row_seen[index].hits += 1;
    g_row_pointer[index] = row;
  }
  if (g_row_hook_first != nullptr) {
    g_row_hook_first();
  }
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL row_apply_second_00faf140(
    void* row_object, Word index, const Row4* row) {
  Call& entry = record("00faf140", row_object);
  entry.arg0 = index;
  entry.pointer0 = row;
  if (index < 6) {
    g_row_seen[index].second = *row;
    g_row_seen[index].hits += 1;
    g_row_pointer[index] = row;
  }
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL row_apply_third_00faf400(
    void* row_object, Word index, const Row4* row) {
  Call& entry = record("00faf400", row_object);
  entry.arg0 = index;
  entry.pointer0 = row;
  if (index < 6) {
    g_row_seen[index].third = *row;
    g_row_seen[index].hits += 1;
    g_row_pointer[index] = row;
  }
}

extern "C" void PKG_SWARM_W2_00FAAD80_CDECL relay_build_00faacd0(void* receiver, void* relay_slot) {
  Call& entry = record("00faacd0", receiver);
  entry.pointer0 = relay_slot;
  if (g_relay_builder_stores != 0) {
    *reinterpret_cast<Word*>(relay_slot) = g_relay_builder_stores;
  }
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL frame_commit_00f9ba40(void* receiver,
                                                                    Word first_argument) {
  Call& entry = record("00f9ba40", receiver);
  entry.arg0 = first_argument;
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL inside_flag_commit_00fa5610(
    void* receiver, Word first_argument) {
  Call& entry = record("00fa5610", receiver);
  entry.arg0 = first_argument;
  // The ordering claim of 0x00fab0aa: the flag byte is already stored.
  g_inside_flag_at_commit = pk::load_byte(receiver, pk::kOffInsideFlag);
}

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL peer_notify_00fc7b30(void* peer,
                                                                    Word second_argument) {
  Call& entry = record("00fc7b30", peer);
  entry.arg0 = second_argument;
}

// ---------------------------------------------------------------------------
// The six indirect sites, reached through real two-level tables
// ---------------------------------------------------------------------------

extern "C" void obs_page_entered_0080(void* receiver) { record("slot+0x80", receiver); }

extern "C" void obs_phase_resync_0010(void* receiver) {
  record("slot+0x10", receiver);
  // The three clears come AFTER this call, so all three words are still poisoned.
  for (int i = 0; i < 3; ++i) {
    g_globals_at_phase_call[i] = pk::cleared_word(static_cast<unsigned>(i));
  }
  g_phase_dirty_at_resync = pk::load_byte(receiver, pk::kOffPhaseDirty);
}

extern "C" Word obs_phase_ready_00d8(void* receiver) {
  record("slot+0xd8", receiver);
  return g_ready_result;
}

extern "C" Word obs_row_query_004c(void* receiver, Word size) {
  record("slot+0x4c", receiver);
  SeenQuery seen{};
  seen.receiver = reinterpret_cast<std::uintptr_t>(receiver);
  seen.size = size;
  // All four frame words must be in place when the callee is entered: the first three
  // were written at 0x00faaf71..0x00faaf87 and the FOURTH only at 0x00faafaf, after the
  // PUSH 0x8. A model that writes the fourth earlier still passes this, so the ordering
  // is additionally pinned by the destination-row check below.
  const float* const slot = pk::last_frame();
  seen.w0 = slot[0];
  seen.w1 = slot[1];
  seen.w2 = slot[2];
  seen.w3 = slot[3];
  seen.extra_value = g_row_query_extra != nullptr
                         ? *reinterpret_cast<Word*>(g_row_query_extra)
                         : 0u;
  g_row_queries.push_back(seen);
  return g_row_query_result;
}

extern "C" void* obs_stage_make_001c(void* receiver, Word id) {
  Call& entry = record("slot+0x1c", receiver);
  entry.arg0 = id;
  return g_stage_object;
}

extern "C" void obs_stage_notify_015c(void* receiver, Word zero_argument, Word vector_address,
                                       float value) {
  Call& entry = record("slot+0x15c", receiver);
  entry.arg0 = zero_argument;
  entry.arg1 = vector_address;
  entry.farg = value;
}

void install_tables() {
  for (std::size_t i = 0; i < 96; ++i) {
    g_receiver_table[i] = nullptr;
    g_stage_root_table[i] = nullptr;
    g_stage_table[i] = nullptr;
  }
  g_receiver_table[pk::kSlotPageEntered / 4] = reinterpret_cast<void*>(&obs_page_entered_0080);
  g_receiver_table[pk::kSlotPhaseResync / 4] = reinterpret_cast<void*>(&obs_phase_resync_0010);
  g_receiver_table[pk::kSlotPhaseReady / 4] = reinterpret_cast<void*>(&obs_phase_ready_00d8);
  g_receiver_table[pk::kSlotRowQuery / 4] = reinterpret_cast<void*>(&obs_row_query_004c);
  g_stage_root_table[pk::kSlotStageMake / 4] = reinterpret_cast<void*>(&obs_stage_make_001c);
  g_stage_table[pk::kSlotStageNotify / 4] = reinterpret_cast<void*>(&obs_stage_notify_015c);
  // Through pointer variables, for the reason the Fixture constructor documents: a copy
  // from &array would copy the array's first element, not its address.
  void** root_address = g_stage_root_table;
  void** stage_address = g_stage_table;
  std::memcpy(g_stage_root_object, &root_address, sizeof(root_address));
  std::memcpy(g_stage_object, &stage_address, sizeof(stage_address));
}

// ---------------------------------------------------------------------------
// The fixture
// ---------------------------------------------------------------------------

constexpr std::size_t kPadBefore = 0x40;
constexpr std::size_t kPadAfter = 0x400;
constexpr std::size_t kBoundsSpan = 0x60;
constexpr std::uint8_t kFillByte = 0xa5;
constexpr Word kArg1 = 0x11223344u;
constexpr Word kArg2 = 0x55667788u;

struct Fixture {
  std::vector<std::uint8_t> storage;
  std::vector<std::uint8_t> bounds_primary;
  std::vector<std::uint8_t> bounds_decoy_low;
  std::vector<std::uint8_t> bounds_decoy_high;
  std::vector<std::uint8_t> saved;

  Fixture()
      : storage(kPadBefore + pk::kReceiverSpan + kPadAfter, kFillByte),
        bounds_primary(kBoundsSpan, 0),
        bounds_decoy_low(kBoundsSpan, 0),
        bounds_decoy_high(kBoundsSpan, 0) {
    std::memset(storage.data(), kFillByte, storage.size());
    // The table ADDRESS goes at the receiver's +0x00 -- the one word the body reads to
    // dispatch (0x00faada8, 0x00faaeb9, 0x00faafa6, 0x00faaf2a). It has to go through a
    // pointer VARIABLE: copying from &g_receiver_table would copy the array's first
    // ELEMENT, which is a null slot, not the array's address.
    void** table_address = g_receiver_table;
    std::memcpy(receiver_raw(), &table_address, sizeof(table_address));
  }

  std::uint8_t* raw() { return storage.data(); }
  std::uint8_t* receiver_raw() { return storage.data() + kPadBefore; }
  Receiver* receiver() { return reinterpret_cast<Receiver*>(storage.data() + kPadBefore); }
  void snapshot() { saved = storage; }

  // Every receiver-relative byte offset the last run changed, over the whole padded
  // buffer, so an access outside the listed offsets is reported rather than absorbed.
  std::vector<std::uint32_t> changed() const {
    std::vector<std::uint32_t> out;
    for (std::size_t i = kPadBefore; i < storage.size(); ++i) {
      if (storage[i] != saved[i]) {
        out.push_back(static_cast<std::uint32_t>(i - kPadBefore));
      }
    }
    // Anything the body touched BEFORE the receiver shows up as a negative offset.
    for (std::size_t i = 0; i < kPadBefore; ++i) {
      if (storage[i] != kFillByte) {
        out.push_back(static_cast<std::uint32_t>(
            0x80000000u + static_cast<std::uint32_t>(kPadBefore - i)));
      }
    }
    return out;
  }
};

void put_float(std::uint8_t* base, std::uint32_t offset, float value) {
  std::memcpy(base + offset, &value, sizeof(value));
}
void put_word(std::uint8_t* base, std::uint32_t offset, Word value) {
  std::memcpy(base + offset, &value, sizeof(value));
}

std::vector<std::uint32_t> byte_range(std::uint32_t from, std::uint32_t count) {
  std::vector<std::uint32_t> out;
  for (std::uint32_t i = 0; i < count; ++i) {
    out.push_back(from + i);
  }
  return out;
}

// Bit-exact float comparison. On x86-32 GCC evaluates a float EXPRESSION at full
// precision, so `loaded == 1 + 0.1f` compares a 24-bit loaded value against a 64-bit
// intermediate and is false even when the float the expression denotes is the one that was
// stored. The expectation is therefore rounded through a `volatile float` and the two are
// then compared bit for bit, which is also the right comparison for a body that MOVSS's
// words around: the machine moves bits.
unsigned float_bits(float value) {
  unsigned bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  return bits;
}
bool same_float(float left, float right) {
  volatile float rounded = right;
  return float_bits(left) == float_bits(rounded);
}

void append_all(std::vector<std::uint32_t>& into, const std::vector<std::uint32_t>& more) {
  into.insert(into.end(), more.begin(), more.end());
}

// The weaker form, for the row-destination window: every changed byte must be INSIDE the
// allowed set, and every required offset must be among the changed ones. The exact form
// cannot be used there because a planted float may share a byte with the fill pattern, so
// "which bytes moved" depends on the data while "which bytes were touched" does not.
void expect_changed_within(std::vector<std::uint32_t> got,
                           const std::vector<std::uint32_t>& allowed,
                           const std::vector<std::uint32_t>& required, int line) {
  std::sort(got.begin(), got.end());
  got.erase(std::unique(got.begin(), got.end()), got.end());
  std::vector<std::uint32_t> allow(allowed);
  std::sort(allow.begin(), allow.end());
  allow.erase(std::unique(allow.begin(), allow.end()), allow.end());
  ++g_checks;
  std::vector<std::uint32_t> outside;
  std::set_difference(got.begin(), got.end(), allow.begin(), allow.end(),
                      std::back_inserter(outside));
  if (!outside.empty()) {
    ++g_failures;
    std::printf("FAIL [%s] line %d: %zu changed byte(s) outside the allowed set:",
                g_case, line, outside.size());
    for (std::uint32_t value : outside) {
      std::printf(" 0x%x", value);
    }
    std::printf("\n");
  }
  for (std::uint32_t value : required) {
    CHECK(std::binary_search(got.begin(), got.end(), value));
    if (!std::binary_search(got.begin(), got.end(), value)) {
      std::printf("   (required offset 0x%x did not move)\n", value);
    }
  }
}

void expect_changed(std::vector<std::uint32_t> got, std::vector<std::uint32_t> want,
                    int line) {
  std::sort(got.begin(), got.end());
  std::sort(want.begin(), want.end());
  want.erase(std::unique(want.begin(), want.end()), want.end());
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL [%s] line %d: changed-byte set mismatch\n", g_case, line);
    std::printf("   got :");
    for (std::uint32_t value : got) {
      std::printf(" 0x%x", value);
    }
    std::printf("\n   want:");
    for (std::uint32_t value : want) {
      std::printf(" 0x%x", value);
    }
    std::printf("\n");
  }
}

// A "quiet" receiver: gate clear, live bounds pointer, extents matching the bounds, the
// phase byte clean, the latch already set, no settle target, no peer, counter zero.
void set_quiet(Fixture& fixture) {
  std::uint8_t* const self = fixture.receiver_raw();
  Receiver* const receiver = fixture.receiver();

  // Regions first, so no memset can land on a field planted afterwards. The source-row
  // window and the destination-row window are each filled, and then a decoy ELEMENT is
  // planted on each side of the run the loop actually touches.
  std::memset(self + pk::kOffRowSource - pk::kRowStride * 2u, 0, pk::kRowStride * 40u);
  for (std::uint32_t i = 0; i < 40; ++i) {
    put_float(self, pk::kOffRowSource - pk::kRowStride * 2u + pk::kRowStride * i,
              -1000.0f - static_cast<float>(i));
  }
  std::memset(self + pk::kOffRowDestCursor - pk::kRowStride * 8u, 0, pk::kRowStride * 20u);
  put_float(self, pk::kOffRowDestCursor - pk::kRowStride, -2000.0f);   // element before
  put_float(self, pk::kOffRowDestCursor + pk::kRowStride * 6u, -2001.0f);  // element after

  // Fields.
  put_word(self, pk::kOffPageCounter, 0);
  put_word(self, pk::kOffGate, 0);
  put_word(self, pk::kOffBoundsObject,
           static_cast<Word>(reinterpret_cast<std::uintptr_t>(fixture.bounds_primary.data())));
  put_word(self, pk::kOffPageIndex, 0);
  put_word(self, pk::kOffSettleTarget, 0);
  put_word(self, pk::kOffPeer, 0);
  put_word(self, pk::kOffCallCounter, 0);
  put_word(self, pk::kOffRelaySlot, 0);
  // The relay release runs BEFORE the relay build, so the observer that checks the
  // ordering of the clear cannot learn the slot's address from the build. The test knows
  // it, so it publishes it here.
  g_relay_slot_address = reinterpret_cast<Word*>(self + pk::kOffRelaySlot);
  put_word(self, pk::kOffMode, 0);
  pk::store_byte(receiver, pk::kOffPhaseDirty, 0);
  pk::store_byte(receiver, pk::kOffPhaseDone, 1);
  pk::store_byte(receiver, pk::kOffResyncFlag, 0);
  pk::store_byte(receiver, pk::kOffInsideFlag, 0);
  // The phase byte for page 0 is a BYTE at +0x369; planting a float there would run into
  // the +0x36c word.
  pk::store_byte(receiver, pk::kOffRowPhase, 0);
  // Decoys either side of the +0x36c word. Note 0x36f is the word's own high byte on a
  // little-endian target, so a decoy there is not beside the word -- it is inside it.
  pk::store_byte(receiver, pk::kOffPageIndex - 1u, 0xdd);  // 0x36b
  pk::store_byte(receiver, pk::kOffPageIndex - 4u, 0x11);  // 0x368, which page_turn clears

  // Bounds: near 2, left 3, right 4, far 5, limit 90, second 70. The extents are set to
  // match, so both compares report "the same" and the flag byte is clear too.
  put_float(fixture.bounds_primary.data(), pk::kBoundsNear, 2.0f);
  put_float(fixture.bounds_primary.data(), pk::kBoundsScaleLeft, 3.0f);
  put_float(fixture.bounds_primary.data(), pk::kBoundsScaleRight, 4.0f);
  put_float(fixture.bounds_primary.data(), pk::kBoundsReach, 5.0f);
  put_float(fixture.bounds_primary.data(), pk::kBoundsLimit, 90.0f);
  put_float(fixture.bounds_primary.data(), pk::kBoundsSecondLimit, 70.0f);
  put_float(self, pk::kOffExtentNear, 2.0f);
  put_float(self, pk::kOffExtentSpan, 12.0f);
  // The decoy bounds objects carry the same shape with values that would change the
  // outcome if the body read +0x28 or +0x30 instead of +0x2c. Nothing reads them, and the
  // distance and changed-byte assertions in each case are what prove it.
  for (std::vector<std::uint8_t>* decoy : {&fixture.bounds_decoy_low, &fixture.bounds_decoy_high}) {
    for (std::uint32_t offset = 0; offset + 4 <= kBoundsSpan; offset += 4) {
      put_float(decoy->data(), offset, 7777.0f);
    }
  }
  put_word(self, pk::kOffBoundsObject - 4u,
           static_cast<Word>(reinterpret_cast<std::uintptr_t>(fixture.bounds_decoy_low.data())));
  put_word(self, pk::kOffBoundsObject + 4u,
           static_cast<Word>(reinterpret_cast<std::uintptr_t>(fixture.bounds_decoy_high.data())));
  // Six row objects in the +0x118 table, with a decoy word either side of it.
  for (std::size_t i = 0; i < 6; ++i) {
    put_word(self, pk::kOffRowObject + 4u * static_cast<Word>(i),
             static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_row_object[i])));
  }
  // The six words of the table occupy 0x118..0x12f, and 0x114 is the CALL COUNTER, not a
  // decoy, so the decoys go above the table.
  put_word(self, pk::kOffRowObject + 24u, 0xdeadbeefu);
  put_word(self, pk::kOffRowObject + 28u, 0xdeadbeefu);
  put_word(self, pk::kOffRowObject + 32u, 0xdeadbeefu);
  g_relay_builder_stores = 0;
  g_row_query_extra = nullptr;
  g_row_hook_first = nullptr;
  g_hook_receiver = nullptr;
}

void reset_observers() {
  g_calls.clear();
  g_row_queries.clear();
  g_relay_release_receiver = nullptr;
  g_relay_word_at_release = 0xffffffffu;
  g_relay_commit_receiver = nullptr;
  g_relay_builder_stores = 0;
  g_inside_flag_at_commit = 0xff;
  g_phase_dirty_at_resync = 0xff;
  for (int i = 0; i < 3; ++i) {
    g_globals_at_phase_call[i] = 0xffffffffu;
  }
  g_ready_result = 1;
  g_row_query_result = 0;
  g_row_query_extra = nullptr;
  g_row_hook_first = nullptr;
  for (std::size_t i = 0; i < 6; ++i) {
    g_row_seen[i].hits = 0;
    g_row_pointer[i] = nullptr;
  }
  g_hook_receiver = nullptr;
  // Re-poison the three globals the body zeroes, so the ORDER of the clears relative to
  // the slot+0x10 call is observable in every case and not only the first.
  pk::poison_cleared_words();
}

}  // namespace

int main() {
  std::setvbuf(stdout, nullptr, _IONBF, 0);
  std::printf("pkg-swarm-w2-00faad80 model test: re_00faad80\n");
  install_tables();

  // The model's global triple starts at 1,1,1. Confirm the poisoning is in place before
  // any case runs, so "the clears happened" is a real observation and not a tautology.
  begin_case("preconditions");
  CHECK(pk::cleared_word(0) == 1u);
  CHECK(pk::cleared_word(1) == 1u);
  CHECK(pk::cleared_word(2) == 1u);

  // -----------------------------------------------------------------------
  // A. The minimal steady-state path: no resync, no row block, no settle, no peer.
  // -----------------------------------------------------------------------
  {
    begin_case("A minimal path");
    Fixture fixture;
    set_quiet(fixture);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);

    // Only the slot+0x10 call, the counter, and the two tail callees.
    CHECK(count_of("00f977c0") == 0);
    CHECK(count_of("0067dd80") == 0);
    CHECK(count_of("00f96370") == 0);
    CHECK(count_of("00fb0d20") == 0);
    CHECK(count_of("00f9b8c0") == 0);
    CHECK(count_of("00fbf570") == 0);
    CHECK(count_of("00690120") == 0);
    CHECK(count_of("00fc7b30") == 0);
    CHECK(count_of("00f9ba40") == 1);
    CHECK(count_of("00fa5610") == 1);
    CHECK(count_of("slot+0x10") == 1);
    CHECK(count_of("slot+0xd8") == 0);
    CHECK(count_of("slot+0x4c") == 0);

    // Argument order of the two tail callees, and the receiver of each.
    const Call* const commit = find_of("00f9ba40");
    CHECK(commit != nullptr);
    if (commit != nullptr) {
      CHECK(commit->receiver == reinterpret_cast<std::uintptr_t>(fixture.receiver()));
      CHECK(commit->arg0 == kArg1);
    }
    const Call* const inside = find_of("00fa5610");
    CHECK(inside != nullptr);
    if (inside != nullptr) {
      CHECK(inside->receiver == reinterpret_cast<std::uintptr_t>(fixture.receiver()));
      CHECK(inside->arg0 == kArg1);
    }

    // The ordering claims: the phase byte is already stored when slot+0x10 is entered,
    // and the three globals are still poisoned.
    CHECK(g_phase_dirty_at_resync == 0x00);
    CHECK(g_globals_at_phase_call[0] == 1u);
    CHECK(g_globals_at_phase_call[1] == 1u);
    CHECK(g_globals_at_phase_call[2] == 1u);
    // ... and zeroed afterwards.
    CHECK(pk::cleared_word(0) == 0u);
    CHECK(pk::cleared_word(1) == 0u);
    CHECK(pk::cleared_word(2) == 0u);
    // The inside flag is stored BEFORE its callee is entered.
    CHECK(g_inside_flag_at_commit == 0x01);

    // The counter is incremented exactly once.
    CHECK(pk::load_word(fixture.receiver(), pk::kOffCallCounter) == 1u);
    // The latch and the phase byte are untouched on this path.
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDone) == 1u);
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDirty) == 0x00);

    // EXACT changed-byte set. The listing writes, on this path and no other:
    //   0x110 one byte (0x00fab0aa) and 0x114 four bytes (0x00faaee0).
    // Everything else -- the extent floats, the bounds, the row tables, the decoys, the
    // three globals -- must be bit-identical, which is what makes this a real check of
    // "the body touched nothing else".
    std::vector<std::uint32_t> want;
    // The counter is INC'd as a 32-bit word, but only its low byte MOVES on a 0 -> 1
    // step; the comparison is over bytes, so the upper three must be unchanged.
    append_all(want, byte_range(pk::kOffInsideFlag, 1));
    append_all(want, byte_range(pk::kOffCallCounter, 1));
    expect_changed(fixture.changed(), want, __LINE__);

    // The distance test on the quiet fixture: reach = sqrt(0)-2 = -2, limit = (5+3)*4-1
    // = 31, so the flag is 1. The decoy bounds objects carry 7777 everywhere, so this
    // also pins the two-level read of +0x2c.
    CHECK(g_inside_flag_at_commit == 0x01);
  }

  // -----------------------------------------------------------------------
  // B. The resync arm, both sub-cases of the 0x00faae65 JA, plus the flag byte alone.
  // -----------------------------------------------------------------------
  {
    begin_case("B resync: computed bound is the larger");
    Fixture fixture;
    set_quiet(fixture);
    // extent_near differs from bounds+0x34 (20 vs 2), which is what forces the block, and
    // the stored limit is dropped below the recomputed bound so the computed one wins.
    put_float(fixture.receiver_raw(), pk::kOffExtentNear, 20.0f);
    put_float(fixture.bounds_primary.data(), pk::kBoundsLimit, 5.0f);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);

    CHECK(count_of("00f977c0") == 1);
    CHECK(count_of("0067dd80") == 1);
    CHECK(count_of("slot+0x1c") == 1);
    CHECK(count_of("slot+0x15c") == 1);
    const Call* const resync = find_of("00f977c0");
    CHECK(resync != nullptr && resync->receiver == reinterpret_cast<std::uintptr_t>(fixture.receiver()));
    const Call* const make = find_of("slot+0x1c");
    CHECK(make != nullptr);
    if (make != nullptr) {
      // The slot+0x1c call is made on the getter's return value, and its single argument
      // is the literal 0x03fbae24.
      CHECK(make->receiver == reinterpret_cast<std::uintptr_t>(g_stage_root_object));
      CHECK(make->arg0 == 0x03fbae24u);
    }
    const Call* const notify = find_of("slot+0x15c");
    CHECK(notify != nullptr);
    if (notify != nullptr) {
      CHECK(notify->receiver == reinterpret_cast<std::uintptr_t>(g_stage_object));
      // Argument order: 0 first, the vector ADDRESS second, the float third.
      CHECK(notify->arg0 == 0u);
      CHECK(notify->arg1 == 0x016c9e8cu);
      // The value is the MAXIMUM: near 2 + left 3 * right 4 = 14 against the stored limit
      // 90, and the extent compare forced the block, so the picked word is 14.
      CHECK(same_float(notify->farg, 14.0f));
    }
    // The picked word is the computed bound, which is scratch word 0 (offset 0).
    CHECK(pk::last_picked_word_offset() == 0);
  }
  {
    begin_case("B resync: stored limit is the larger");
    Fixture fixture;
    set_quiet(fixture);
    // The recomputed bound is left at 3*4+2 = 14 and the stored limit is 90, so the
    // stored limit wins and the value handed on is 90 -- the MAXIMUM, not the minimum.
    put_float(fixture.receiver_raw(), pk::kOffExtentNear, 20.0f);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    const Call* const notify = find_of("slot+0x15c");
    CHECK(notify != nullptr);
    if (notify != nullptr) {
      CHECK(same_float(notify->farg, 90.0f));
    }
    // The stored limit is scratch word 1, so the pick offset is 4 -- which is what makes
    // this the refutation of "always word 0".
    CHECK(pk::last_picked_word_offset() == 4);
  }
  {
    begin_case("B resync: the flag byte alone forces the block");
    Fixture fixture;
    set_quiet(fixture);
    // Both compares are equal and the flag byte is set: the third disjunct is the only
    // reason the block runs.
    pk::store_byte(fixture.receiver(), pk::kOffResyncFlag, 1);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(count_of("00f977c0") == 1);
    const Call* const notify = find_of("slot+0x15c");
    CHECK(notify != nullptr);
    if (notify != nullptr) {
      // The recomputed bound is 3*4+2 = 14 against the stored limit 90, so the LIMIT is
      // the maximum and it is the value handed on.
      CHECK(same_float(notify->farg, 90.0f));
    }
    CHECK(pk::last_picked_word_offset() == 4);
  }
  {
    begin_case("B resync: equal operands take the stored limit (JA not taken)");
    Fixture fixture;
    set_quiet(fixture);
    put_float(fixture.receiver_raw(), pk::kOffExtentNear, 20.0f);
    // Make the computed bound exactly equal to the stored limit.
    put_float(fixture.bounds_primary.data(), pk::kBoundsLimit, 14.0f);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(pk::last_picked_word_offset() == 4);
    const Call* const notify = find_of("slot+0x15c");
    CHECK(notify != nullptr);
    if (notify != nullptr) {
      CHECK(same_float(notify->farg, 14.0f));
    }
  }
  {
    // The machine's compare is the UCOMISS/LAHF/TEST AH,0x44/JP sequence, which reports
    // an UNORDERED pair as "the same". C's != reports it as different. This case is the
    // refutation of a reconstruction that writes `!=`: with a NaN extent the block must
    // NOT run unless something else forces it.
    begin_case("B resync: a NaN extent reads as the same");
    Fixture fixture;
    set_quiet(fixture);
    put_float(fixture.receiver_raw(), pk::kOffExtentNear,
              std::numeric_limits<float>::quiet_NaN());
    put_float(fixture.receiver_raw(), pk::kOffExtentSpan,
              std::numeric_limits<float>::quiet_NaN());
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(count_of("00f977c0") == 0);
    CHECK(count_of("slot+0x15c") == 0);
  }
  {
    // A finite extent that differs from the bounds DOES force the block, which is the
    // companion to the NaN case and rules out a model that never resyncs.
    begin_case("B resync: a differing extent does force the block");
    Fixture fixture;
    set_quiet(fixture);
    put_float(fixture.receiver_raw(), pk::kOffExtentSpan, 13.0f);  // 3*4 = 12
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(count_of("00f977c0") == 1);
  }

  // -----------------------------------------------------------------------
  // C. The page counter's three arms.
  // -----------------------------------------------------------------------
  {
    begin_case("C page counter: exactly 1 takes the one-shot arm");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffPageCounter, 1);
    put_word(fixture.receiver_raw(), pk::kOffGate, 1);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);

    CHECK(pk::load_word(fixture.receiver(), pk::kOffPageCounter) == 0u);
    CHECK(count_of("slot+0x80") == 1);
    CHECK(count_of("00f9b8c0") == 1);
    // The one-shot arm returns before the counter increment, so nothing else happened.
    CHECK(pk::load_word(fixture.receiver(), pk::kOffCallCounter) == 0u);
    CHECK(count_of("slot+0x10") == 0);
    CHECK(count_of("00f9ba40") == 0);
    CHECK(pk::cleared_word(0) == 1u);  // still poisoned: the clears are on the other arm

    const Call* const entered = find_of("slot+0x80");
    CHECK(entered != nullptr &&
          entered->receiver == reinterpret_cast<std::uintptr_t>(fixture.receiver()));
    const Call* const notify = find_of("00f9b8c0");
    CHECK(notify != nullptr);
    if (notify != nullptr) {
      CHECK(notify->receiver == reinterpret_cast<std::uintptr_t>(fixture.receiver()));
      // THE decisive claim: the first two arguments are the SAME address, and reading
      // through it yields the caller's first argument.
      CHECK(notify->pointer0 == notify->pointer1);
      CHECK(notify->pointer0 != nullptr);
      // The value, sampled by the callee at call time.
      CHECK(notify->arg2 == kArg1);
      // The gate flag follows the receiver's +0xfc word, zero-extended through SETNZ.
      CHECK(notify->arg0 == 1u);
      CHECK(notify->arg1 == 0u);
      CHECK(same_float(notify->farg, 10.0f));
    }
    // Nothing but the counter changed.
    expect_changed(fixture.changed(), byte_range(pk::kOffPageCounter, 1), __LINE__);
  }
  {
    begin_case("C page counter: 2 decrements and returns");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffPageCounter, 2);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(pk::load_word(fixture.receiver(), pk::kOffPageCounter) == 1u);
    CHECK(g_calls.empty());
    expect_changed(fixture.changed(), byte_range(pk::kOffPageCounter, 1), __LINE__);
  }
  {
    // The branch at 0x00faad93 is JLE, a SIGNED compare. A counter with the top bit set
    // must return without being decremented; an unsigned reading would decrement it.
    begin_case("C page counter: a negative counter returns undecremented");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffPageCounter, 0x80000000u);
    put_word(fixture.receiver_raw(), pk::kOffPageCounter + 4u, 0xccccccccu);  // decoy
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(pk::load_word(fixture.receiver(), pk::kOffPageCounter) == 0x80000000u);
    CHECK(g_calls.empty());
    expect_changed(fixture.changed(), {}, __LINE__);
  }
  {
    begin_case("C page counter: a small negative counter also returns");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffPageCounter, 0xffffffffu);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(pk::load_word(fixture.receiver(), pk::kOffPageCounter) == 0xffffffffu);
    CHECK(g_calls.empty());
  }
  {
    // 0x00faade3/0x00faade9: a non-zero gate word returns before the counter increment.
    begin_case("C gate word: non-zero returns before the counter");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffGate, 0x1234u);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(g_calls.empty());
    CHECK(pk::load_word(fixture.receiver(), pk::kOffCallCounter) == 0u);
    expect_changed(fixture.changed(), {}, __LINE__);
  }

  // -----------------------------------------------------------------------
  // D. The phase byte, including the 32-bit wrap of its address.
  // -----------------------------------------------------------------------
  {
    // 0x00faaea1/0x00faaea7: the byte is at receiver + 0x369 - page. For page 1 that is
    // 0x368 -- one below where a page-0 model would look. The decoy at 0x369 is clean, so
    // only a model that follows the SUB reads the dirty byte.
    begin_case("D phase byte: page 1 reads at 0x368, not 0x369");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffPageIndex, 1);
    // 0x368 is the byte page 1 reads, and its low three bits are set; 0x369 is the byte
    // page 0 would read and is clean. A model that ignored the SUB would read the clean
    // one and miss the resync.
    pk::store_byte(fixture.receiver(), pk::kOffRowPhase - 1u, 0x03);
    pk::store_byte(fixture.receiver(), pk::kOffRowPhase, 0x00);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 1);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    // The flag was set, but the latch was already set, so the block did not run -- and
    // the store at 0x00faaebb is visible as the byte going to 1.
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDirty) == 1u);
    CHECK(g_phase_dirty_at_resync == 1u);
    CHECK(count_of("slot+0xd8") == 0);
  }
  {
    // The wrap: page = 0x36d makes 0x369 - 0x36d = -4 in 32-bit arithmetic, so the
    // machine reads FOUR BYTES BELOW the receiver. The fixture's pad lets that be
    // observed. A model that clamps, or that computes the address in size_t and faults,
    // fails here.
    begin_case("D phase byte: the address wraps below the receiver");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffPageIndex, 0x36du);
    fixture.receiver_raw()[-4] = 3;  // 0x36d - 0x369 == 4, so the byte is at -4
    fixture.receiver_raw()[-5] = 0xee;
    fixture.receiver_raw()[-1] = 0;  // decoy at -1
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 1);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDirty) == 1u);
  }
  {
    // The mask is 0x7 (0x00faaea7), so a byte whose low three bits are clear is NOT
    // dirty however large the rest of it is.
    begin_case("D phase byte: only the low three bits are tested");
    Fixture fixture;
    set_quiet(fixture);
    fixture.receiver_raw()[pk::kOffRowPhase] = 0xf8;  // 0xf8 & 7 == 0
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 1);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDirty) == 0x00u);
  }
  {
    begin_case("D phase byte: bit 2 set is dirty");
    Fixture fixture;
    set_quiet(fixture);
    fixture.receiver_raw()[pk::kOffRowPhase] = 0x04;
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 1);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDirty) == 1u);
  }
  {
    // 0x00faae96/0x00faae9d: when the flag byte is ALREADY set the +0x36c word is not
    // read at all. The wrap case would fault or read out of bounds if it were, so
    // running with the flag set and an absurd page index is the observable form of that
    // short circuit.
    begin_case("D phase byte: an already-set flag short-circuits the +0x36c read");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffPageIndex, 0x7fffffffu);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 1);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDirty) == 1u);
    CHECK(g_calls.size() == 3);  // slot+0x10, 00f9ba40, 00fa5610
  }

  // -----------------------------------------------------------------------
  // E. The six-row block.
  // -----------------------------------------------------------------------
  {
    begin_case("E row block: the whole block, exactly");
    Fixture fixture;
    set_quiet(fixture);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 0);
    put_word(fixture.receiver_raw(), pk::kOffRelaySlot, 0x1234u);
    // Six source rows, each four distinct floats, at page 0.
    for (std::uint32_t i = 0; i < 6; ++i) {
      const std::uint32_t base = pk::kOffRowSource + pk::kRowStride * i;
      put_float(fixture.receiver_raw(), base + 0u, 10.0f * static_cast<float>(i) + 1.0f);
      put_float(fixture.receiver_raw(), base + 4u, 10.0f * static_cast<float>(i) + 2.0f);
      put_float(fixture.receiver_raw(), base + 8u, 10.0f * static_cast<float>(i) + 3.0f);
      put_float(fixture.receiver_raw(), base + 12u, 10.0f * static_cast<float>(i) + 4.0f);
    }
    // The page index is 1, so page_turn -- which sets it to 1-1 = 0 -- leaves the loop
    // reading page 0's rows, and it clears the byte at +0x368+page = 0x369. Planting a
    // non-zero byte there is what makes that write observable: the phase-byte TEST for
    // page 1 reads 0x368, so nothing in the body itself touches 0x369 and only the callee
    // can move it.
    put_word(fixture.receiver_raw(), pk::kOffPageIndex, 1);
    pk::store_byte(fixture.receiver(), pk::kOffRowPhase, 0x05);
    reset_observers();
    g_relay_builder_stores = 0xabcd0001u;
    fixture.snapshot();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);

    CHECK(count_of("00f96370") == 1);
    CHECK(count_of("00f96f90") == 1);
    CHECK(count_of("00fb0d20") == 6);
    CHECK(count_of("00faf140") == 6);
    CHECK(count_of("00faf400") == 6);
    CHECK(count_of("slot+0x4c") == 6);
    CHECK(count_of("slot+0xd8") == 1);

    // The three row callees run in the listing's order within an iteration, and the index
    // is the loop counter, 0..5, in order.
    for (int i = 0; i < 6; ++i) {
      const Call* const first = find_nth("00fb0d20", i);
      const Call* const second = find_nth("00faf140", i);
      const Call* const third = find_nth("00faf400", i);
      CHECK(first != nullptr && second != nullptr && third != nullptr);
      if (first == nullptr || second == nullptr || third == nullptr) {
        continue;
      }
      CHECK(first->arg0 == static_cast<Word>(i));
      CHECK(second->arg0 == static_cast<Word>(i));
      CHECK(third->arg0 == static_cast<Word>(i));
      // The receiver is the i-th word of the +0x118 table -- a distinct object per i.
      CHECK(first->receiver == reinterpret_cast<std::uintptr_t>(g_row_object[i]));
      CHECK(second->receiver == first->receiver);
      CHECK(third->receiver == first->receiver);
      // All three are handed the SAME frame slot, and it is the frame itself.
      CHECK(first->pointer0 == pk::last_frame());
      CHECK(second->pointer0 == first->pointer0);
      CHECK(third->pointer0 == first->pointer0);
    }

    // The frame row each iteration handed over is the source row of that iteration: this
    // is the assertion that the index is (i + 6*page)*0x10 + 0x374 and not 0x374 + i*4.
    for (int i = 0; i < 6; ++i) {
      CHECK(g_row_seen[i].hits == 3);
      CHECK(same_float(g_row_seen[i].first.v0, 10.0f * static_cast<float>(i) + 1.0f));
      CHECK(same_float(g_row_seen[i].first.v1, 10.0f * static_cast<float>(i) + 2.0f));
      CHECK(same_float(g_row_seen[i].first.v2, 10.0f * static_cast<float>(i) + 3.0f));
      CHECK(same_float(g_row_seen[i].first.v3, 10.0f * static_cast<float>(i) + 4.0f));
      CHECK(g_row_seen[i].second.v0 == g_row_seen[i].first.v0);
      CHECK(g_row_seen[i].third.v3 == g_row_seen[i].first.v3);
    }
    // The frame slot's entry-ESP offset, as the listing's ESP arithmetic fixes it.
    CHECK(pk::last_row_slot() == pk::last_frame());
    CHECK(pk::last_row_slot_entry_offset() == -16);

    // The slot+0x4c call is made with the single argument 8, and all four frame words
    // are in place when it is entered -- including the fourth, which the listing writes
    // only after the PUSH.
    CHECK(g_row_queries.size() == 6);
    for (std::size_t i = 0; i < g_row_queries.size(); ++i) {
      CHECK(g_row_queries[i].size == 8u);
      CHECK(g_row_queries[i].receiver == reinterpret_cast<std::uintptr_t>(fixture.receiver()));
      CHECK(g_row_queries[i].w0 == 10.0f * static_cast<float>(i) + 1.0f);
      CHECK(g_row_queries[i].w3 == 10.0f * static_cast<float>(i) + 4.0f);
    }

    // The destination rows, through the 0x828 cursor: element i's four words are at
    // cursor + 0x10*i - 8, -4, +0, +4.
    for (std::uint32_t i = 0; i < 6; ++i) {
      const std::uint32_t dest = pk::kOffRowDestCursor + pk::kRowStride * i;
      CHECK(same_float(pk::load_float(fixture.receiver_raw(), dest - 8u), 10.0f * static_cast<float>(i) + 1.0f));
      CHECK(same_float(pk::load_float(fixture.receiver_raw(), dest - 4u), 10.0f * static_cast<float>(i) + 2.0f));
      CHECK(same_float(pk::load_float(fixture.receiver_raw(), dest), 10.0f * static_cast<float>(i) + 3.0f));
      CHECK(same_float(pk::load_float(fixture.receiver_raw(), dest + 4u), 10.0f * static_cast<float>(i) + 4.0f));
    }
    // And the decoy ELEMENTS either side of the run are untouched: one 0x10-stride
    // element before the first and one after the last. A model with an off-by-one
    // destination stride would land on one of them.
    CHECK(pk::load_float(fixture.receiver_raw(), pk::kOffRowDestCursor - pk::kRowStride) ==
          -2000.0f);
    CHECK(pk::load_float(fixture.receiver_raw(), pk::kOffRowDestCursor + pk::kRowStride * 6u) ==
          -2001.0f);

    // The relay sequence. The word was non-zero, so it was cleared BEFORE the release
    // call and the release call was handed the ORIGINAL value.
    CHECK(count_of("00690120") == 1);
    CHECK(g_relay_release_receiver == reinterpret_cast<void*>(0x1234u));
    CHECK(g_relay_word_at_release == 0u);
    // The builder was handed the ADDRESS of the relay slot and the commit was handed the
    // value the builder left -- not the original and not the zero.
    const Call* const build = find_of("00faacd0");
    CHECK(build != nullptr);
    if (build != nullptr) {
      CHECK(build->receiver == reinterpret_cast<std::uintptr_t>(fixture.receiver()));
      CHECK(build->pointer0 == reinterpret_cast<const void*>(fixture.receiver_raw() + pk::kOffRelaySlot));
    }
    CHECK(g_relay_commit_receiver == reinterpret_cast<void*>(0xabcd0001u));
    // The latch is set and the flag byte is cleared at the end of the block.
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDone) == 1u);
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDirty) == 0u);

    // The changed-byte set for the whole block. The listing writes, on this path and no
    // other: the phase byte (0x00faaebb then 0x00fab04c), the call counter (0x00faaee0),
    // the inside flag (0x00fab0aa), the latch (0x00fab022), the relay slot (0x00fab030
    // and then whatever the builder stored), the +0x36c word and the byte at
    // +0x368+page (both written by 0x00f96370), and the six destination rows. Nothing
    // else -- not the source rows, not the extent floats, not the +0x118 table, not any
    // decoy -- may move.
    //
    // The form is "inside the allowed set" rather than "equal to it" for the destination
    // window alone, because a planted float can share a byte with the fill pattern, so
    // which bytes MOVE there is data-dependent while which bytes were TOUCHED is not. The
    // seven field bytes are required to have moved, which is exact.
    std::vector<std::uint32_t> required;
    append_all(required, byte_range(pk::kOffPhaseDirty, 1));
    append_all(required, byte_range(pk::kOffCallCounter, 1));
    append_all(required, byte_range(pk::kOffInsideFlag, 1));
    append_all(required, byte_range(pk::kOffPhaseDone, 1));
    // The relay slot goes 0x1234 -> 0 -> 0xabcd0001, so all four of its bytes move.
    append_all(required, byte_range(pk::kOffRelaySlot, 4));
    append_all(required, byte_range(pk::kOffPageIndex, 1));
    // The byte 0x00f96370 clears is at +0x368+page, i.e. 0x369 for page 1. 0x368 -- the
    // byte the phase test read -- is NOT written by anything on this path.
    append_all(required, byte_range(pk::kOffRowPhase, 1));
    std::vector<std::uint32_t> allowed(required);
    append_all(allowed, byte_range(pk::kOffRowDestCursor - 8u, 6u * pk::kRowStride));
    expect_changed_within(fixture.changed(), allowed, required, __LINE__);
  }
  {
    // The page index is re-read INSIDE the loop (0x00faaf52), so a model that hoisted
    // the read out would take the wrong rows. Here the FIRST row callee bumps the page
    // index, so iterations 1..5 must read the OTHER page's rows. The run also proves the
    // source index is i + 6*page and not i*4.
    begin_case("E row block: the page index is re-read each iteration");
    Fixture fixture;
    set_quiet(fixture);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 0);
    put_word(fixture.receiver_raw(), pk::kOffPageIndex, 1);
    for (std::uint32_t page = 0; page < 3; ++page) {
      for (std::uint32_t i = 0; i < 6; ++i) {
        const std::uint32_t base = pk::kOffRowSource + pk::kRowStride * (i + 6u * page);
        const float tag = 100.0f * static_cast<float>(page) + static_cast<float>(i);
        put_float(fixture.receiver_raw(), base + 0u, tag);
        put_float(fixture.receiver_raw(), base + 4u, tag + 0.25f);
        put_float(fixture.receiver_raw(), base + 8u, tag + 0.5f);
        put_float(fixture.receiver_raw(), base + 12u, tag + 0.75f);
      }
    }
    // page_turn sets the index to 1-1 = 0, so iteration 0 reads page 0; the hook then
    // sets it to 2, so iterations 1..5 must read page 2.
    g_hook_receiver = fixture.receiver();
    g_row_hook_first = &bump_page_index_to_two;
    reset_observers();
    g_row_hook_first = &bump_page_index_to_two;
    g_hook_receiver = fixture.receiver();
    fixture.snapshot();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(count_of("00fb0d20") == 6);
    CHECK(g_row_seen[0].first.v0 == 0.0f);
    for (int i = 1; i < 6; ++i) {
      CHECK(same_float(g_row_seen[i].first.v0, 200.0f + static_cast<float>(i)));
      CHECK(same_float(g_row_seen[i].first.v3, 200.0f + static_cast<float>(i) + 0.75f));
    }
  }
  {
    // AL-only tests: a callee whose full word is non-zero but whose AL is zero reads as
    // "not ready" (0x00faaf36) and as "no substitution" (0x00faafb7).
    begin_case("E slot+0xd8 returning 256 reads as not ready");
    Fixture fixture;
    set_quiet(fixture);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 0);
    fixture.snapshot();
    reset_observers();
    g_ready_result = 256u;
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    g_ready_result = 1;
    CHECK(count_of("slot+0xd8") == 1);
    CHECK(count_of("00f96370") == 0);
    CHECK(count_of("00fb0d20") == 0);
  }
  {
    begin_case("E slot+0x4c returning 256 does not substitute the identity row");
    Fixture fixture;
    set_quiet(fixture);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 0);
    // page_turn sets the index to 1-page, so page 1 puts the loop on page 0's rows, which
    // are the six this case plants.
    put_word(fixture.receiver_raw(), pk::kOffPageIndex, 1);
    for (std::uint32_t i = 0; i < 6; ++i) {
      const std::uint32_t base = pk::kOffRowSource + pk::kRowStride * i;
      put_float(fixture.receiver_raw(), base + 0u, static_cast<float>(i) + 0.1f);
      put_float(fixture.receiver_raw(), base + 4u, static_cast<float>(i) + 0.2f);
      put_float(fixture.receiver_raw(), base + 8u, static_cast<float>(i) + 0.3f);
      put_float(fixture.receiver_raw(), base + 12u, static_cast<float>(i) + 0.4f);
    }
    fixture.snapshot();
    reset_observers();
    g_row_query_result = 256u;
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    g_row_query_result = 0;
    CHECK(count_of("slot+0x4c") == 6);
    for (int i = 0; i < 6; ++i) {
      CHECK(same_float(g_row_seen[i].first.v0, static_cast<float>(i) + 0.1f));
    }
    // And the destination rows keep the source values.
    for (std::uint32_t i = 0; i < 6; ++i) {
      const std::uint32_t dest = pk::kOffRowDestCursor + pk::kRowStride * i;
      CHECK(same_float(pk::load_float(fixture.receiver_raw(), dest - 8u), static_cast<float>(i) + 0.1f));
    }
  }
  {
    begin_case("E slot+0x4c returning 1 substitutes (0,0,1,1) for the frame row only");
    Fixture fixture;
    set_quiet(fixture);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 0);
    put_word(fixture.receiver_raw(), pk::kOffPageIndex, 1);
    for (std::uint32_t i = 0; i < 6; ++i) {
      const std::uint32_t base = pk::kOffRowSource + pk::kRowStride * i;
      put_float(fixture.receiver_raw(), base + 0u, 5.0f + static_cast<float>(i));
      put_float(fixture.receiver_raw(), base + 4u, 6.0f + static_cast<float>(i));
      put_float(fixture.receiver_raw(), base + 8u, 7.0f + static_cast<float>(i));
      put_float(fixture.receiver_raw(), base + 12u, 8.0f + static_cast<float>(i));
    }
    fixture.snapshot();
    reset_observers();
    g_row_query_result = 1u;
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    g_row_query_result = 0;
    for (int i = 0; i < 6; ++i) {
      // The substitution happens AFTER the query, so the query observer still saw the
      // source values; the three row callees saw the identity row.
      CHECK(same_float(g_row_queries[static_cast<std::size_t>(i)].w0, 5.0f + static_cast<float>(i)));
      CHECK(same_float(g_row_seen[i].first.v0, 0.0f));
      CHECK(same_float(g_row_seen[i].first.v1, 0.0f));
      CHECK(same_float(g_row_seen[i].first.v2, 1.0f));
      CHECK(same_float(g_row_seen[i].first.v3, 1.0f));
      // The receiver's destination row is NOT rewritten by the substitution.
      const std::uint32_t dest = pk::kOffRowDestCursor + pk::kRowStride * static_cast<Word>(i);
      CHECK(same_float(pk::load_float(fixture.receiver_raw(), dest - 8u), 5.0f + static_cast<float>(i)));
      CHECK(same_float(pk::load_float(fixture.receiver_raw(), dest + 4u), 8.0f + static_cast<float>(i)));
    }
  }
  {
    // The latch: 0x00faaf1d/0x00faaf24 skips the whole block when the byte is already 1,
    // even with the flag byte set and the query ready.
    begin_case("E latch already set skips the block");
    Fixture fixture;
    set_quiet(fixture);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 1);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(count_of("slot+0xd8") == 0);
    CHECK(count_of("00f96370") == 0);
    CHECK(pk::load_byte(fixture.receiver(), pk::kOffPhaseDirty) == 1u);
  }

  // -----------------------------------------------------------------------
  // F. The settle call: argument order, the mode reduction, and the ECX receiver.
  // -----------------------------------------------------------------------
  {
    begin_case("F settle: mode 4 becomes 0, the amount is 100, ECX is the sentinel");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffSettleTarget, 0x00c0ffeeu);
    put_word(fixture.receiver_raw(), pk::kOffMode, 4);
    // A decoy beside the mode word.
    put_word(fixture.receiver_raw(), pk::kOffMode + 4u, 0x5a5a5a5au);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    const Call* const settle = find_of("00fbf570");
    CHECK(settle != nullptr);
    if (settle != nullptr) {
      // The receiver is NOT the receiver of this body: the listing never reloads ECX
      // before 0x00faaf0b, so the model passes the indeterminate sentinel and the test
      // asserts exactly that rather than accepting a convenient invention.
      CHECK(settle->receiver == reinterpret_cast<std::uintptr_t>(pk::indeterminate_receiver()));
      CHECK(settle->arg0 == kArg1);
      CHECK(same_float(settle->farg, 100.0f));
      CHECK(settle->arg1 == 0u);
    }
  }
  {
    begin_case("F settle: a mode other than 4 is passed unchanged");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffSettleTarget, 0x00c0ffeeu);
    put_word(fixture.receiver_raw(), pk::kOffMode, 7);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    const Call* const settle = find_of("00fbf570");
    CHECK(settle != nullptr && settle != nullptr && settle->arg1 == 7u);
  }
  {
    begin_case("F settle: mode 0 is passed as 0, not as 4");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffSettleTarget, 0x00c0ffeeu);
    put_word(fixture.receiver_raw(), pk::kOffMode, 0);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    const Call* const settle = find_of("00fbf570");
    CHECK(settle != nullptr && settle != nullptr && settle->arg1 == 0u);
    // The counter is incremented whether or not the settle runs, and the settle target
    // is read BEFORE it -- so a settle target equal to 1 still settles.
    CHECK(pk::load_word(fixture.receiver(), pk::kOffCallCounter) == 1u);
  }
  {
    begin_case("F settle: a null target skips the call");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffSettleTarget, 0);
    put_word(fixture.receiver_raw(), pk::kOffMode, 9);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(count_of("00fbf570") == 0);
    CHECK(pk::load_word(fixture.receiver(), pk::kOffCallCounter) == 1u);
  }

  // -----------------------------------------------------------------------
  // G. The relay slot's three states.
  // -----------------------------------------------------------------------
  {
    begin_case("G relay: a null word skips the release and hands 0 to the commit");
    Fixture fixture;
    set_quiet(fixture);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 0);
    put_word(fixture.receiver_raw(), pk::kOffRelaySlot, 0);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(count_of("00690120") == 0);
    CHECK(count_of("00faacd0") == 1);
    CHECK(count_of("006909b0") == 1);
    CHECK(g_relay_commit_receiver == reinterpret_cast<void*>(0));
  }
  {
    begin_case("G relay: a non-null word is cleared, released, then the builder wins");
    Fixture fixture;
    set_quiet(fixture);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 0);
    put_word(fixture.receiver_raw(), pk::kOffRelaySlot, 0x00ff00ffu);
    fixture.snapshot();
    reset_observers();
    g_relay_builder_stores = 0x00007777u;
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(count_of("00690120") == 1);
    CHECK(g_relay_release_receiver == reinterpret_cast<void*>(0x00ff00ffu));
    CHECK(g_relay_word_at_release == 0u);
    CHECK(g_relay_commit_receiver == reinterpret_cast<void*>(0x00007777u));
  }

  // -----------------------------------------------------------------------
  // H. The distance test and the peer notification.
  // -----------------------------------------------------------------------
  {
    // reach = sqrt(u^2+v^2+w^2) - near; limit = (far + left) * right - 1. With the quiet
    // fixture: sqrt(0) - 2 = -2 against (5+3)*4 - 1 = 31, so the flag is 1.
    begin_case("H distance: inside sets the flag to 1");
    Fixture fixture;
    set_quiet(fixture);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(g_inside_flag_at_commit == 0x01);
  }
  {
    // Push the reach past the limit: u = 100 gives sqrt(10000) - 2 = 98 against 31.
    begin_case("H distance: outside sets the flag to 0");
    Fixture fixture;
    set_quiet(fixture);
    put_float(fixture.receiver_raw(), pk::kOffExtentU, 100.0f);
    put_float(fixture.receiver_raw(), pk::kOffExtentV, 0.0f);
    put_float(fixture.receiver_raw(), pk::kOffExtentW, 0.0f);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(g_inside_flag_at_commit == 0x00);
  }
  {
    // JBE is taken on equality, so an exactly-equal pair gives 0. reach == limit means
    // sqrt(u^2) - 2 == 31, i.e. u = 33.
    begin_case("H distance: exact equality takes JBE and gives 0");
    Fixture fixture;
    set_quiet(fixture);
    put_float(fixture.receiver_raw(), pk::kOffExtentU, 33.0f);
    put_float(fixture.receiver_raw(), pk::kOffExtentV, 0.0f);
    put_float(fixture.receiver_raw(), pk::kOffExtentW, 0.0f);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(g_inside_flag_at_commit == 0x00);
  }
  {
    // Just inside: u = 32.9 gives 30.9 against 31.
    begin_case("H distance: just inside gives 1");
    Fixture fixture;
    set_quiet(fixture);
    put_float(fixture.receiver_raw(), pk::kOffExtentU, 32.9f);
    put_float(fixture.receiver_raw(), pk::kOffExtentV, 0.0f);
    put_float(fixture.receiver_raw(), pk::kOffExtentW, 0.0f);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(g_inside_flag_at_commit == 0x01);
  }
  {
    // The sum is a sum of three squares in the listing's order, and the reach subtracts
    // near AFTER the square root. u = 3, v = 4 gives 5; w = 0. If the model summed the
    // raw extents instead of their squares the answer would be 7 and the flag would
    // still be 1, so drive it to the boundary: near is 2, so reach = 3 and the limit
    // must be made exactly 3 for the comparison to decide.
    begin_case("H distance: the squares are summed, not the extents");
    Fixture fixture;
    set_quiet(fixture);
    put_float(fixture.receiver_raw(), pk::kOffExtentU, 3.0f);
    put_float(fixture.receiver_raw(), pk::kOffExtentV, 4.0f);
    put_float(fixture.receiver_raw(), pk::kOffExtentW, 0.0f);
    // limit = (far + left)*right - 1 == 3  =>  (far + 3)*4 == 4  =>  far = -2.
    put_float(fixture.bounds_primary.data(), pk::kBoundsReach, -2.0f);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    // reach = 5 - 2 = 3, limit = 3, JBE taken, flag 0. A model that summed the extents
    // would get reach = 5 and flag 1.
    CHECK(g_inside_flag_at_commit == 0x00);
  }
  {
    begin_case("H peer: a null peer is not notified");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffPeer, 0);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(count_of("00fc7b30") == 0);
  }
  {
    begin_case("H peer: a live peer is the receiver and gets the SECOND argument");
    Fixture fixture;
    set_quiet(fixture);
    put_word(fixture.receiver_raw(), pk::kOffPeer,
             static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_peer_object)));
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    const Call* const peer = find_of("00fc7b30");
    CHECK(peer != nullptr);
    if (peer != nullptr) {
      CHECK(peer->receiver == reinterpret_cast<std::uintptr_t>(g_peer_object));
      CHECK(peer->receiver != reinterpret_cast<std::uintptr_t>(fixture.receiver()));
      // The SECOND argument, read at 0x00fab0c0 from entry_esp+0x8.
      CHECK(peer->arg0 == kArg2);
      CHECK(peer->arg0 != kArg1);
    }
  }

  // -----------------------------------------------------------------------
  // I. Frame assertions, stated once.
  // -----------------------------------------------------------------------
  {
    begin_case("I frame: the row slot is the frame and sits at entry_esp-0x10");
    Fixture fixture;
    set_quiet(fixture);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDirty, 1);
    pk::store_byte(fixture.receiver(), pk::kOffPhaseDone, 0);
    fixture.snapshot();
    reset_observers();
    pk::re_00faad80(fixture.receiver(), kArg1, kArg2);
    CHECK(pk::last_row_slot() != nullptr);
    CHECK(pk::last_row_slot() == pk::last_frame());
    // The offset the listing's own ESP arithmetic produces: ESP = entry_esp-0x24 at
    // 0x00faaf71, and [ESP+0x14] is the word the callee is handed.
    CHECK(pk::last_row_slot_entry_offset() == -16);
  }

  std::printf("\n%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
