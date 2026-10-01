// PKG-SWARM-W2-00A98200 -- model test for VA 0x00a98200
// FUN_00a98200 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// A falsification test, not a walk-through. Its job is to BREAK the
// reconstruction in sw2_00a98200.cpp, and every case below is written as a
// hypothesis the machine can refute.
//
// WHAT THE OBSERVERS ARE. Every transfer the body makes is observed:
//
//   * openspore_acquire_service_00883860 is the body's one DIRECT callee. It is
//     defined here as an observer that counts its own invocations and returns a
//     value the case chooses, including null.
//   * The four INDIRECT sites are observed by installing function words into the
//     table the body reaches through. Each observer records, AT THE MOMENT IT IS
//     ENTERED: which observer fired, the ECX value (the service object), the three
//     stack arguments in the order the callee receives them, the eight dwords
//     visible at the properties address, and -- read back through the receiver --
//     the latch byte, the record pointer the model will use next, its flag word
//     and its call key. Sampling from inside the callee is what makes write
//     ordering, argument order and reload behaviour checkable rather than
//     assumed.
//
// WHAT IS DELIBERATELY PLANTED AS A DECOY:
//
//   * Every slot of the dispatch table other than +0x14 carries a different
//     observer, so a wrong slot displacement, an off-by-one slot or a wrong index
//     fires a named decoy instead of the real one.
//   * The service object carries function words at +0x04, +0x08, +0x0c, +0x14 and
//     +0x18. The body reaches the table through +0x00 and then +0x14 of THAT, so
//     any of these firing means the fetch was one level short, or started at the
//     wrong displacement, or was taken from the wrong base.
//   * The receiver carries distinct decoy words at every offset the body does not
//     name, on both sides of each displacement it does, and the whole 0xa0-byte
//     receiver is compared byte for byte after every run.
//   * The record carries distinct decoy words throughout, so a list slot filled
//     from the wrong record displacement, or from the key displacement, or from a
//     neighbouring one, is visible: all six candidate values are distinct.
//   * The frame's prior content is an explicit poison word, which is how the five
//     list dwords this body never writes are made observable.
//
// WHAT IS NOT ASSERTED, and why. Stated because the contract asks for it, and
// because a test that claimed these would be a worse test:
//
//   * SIGNED-VS-UNSIGNED. This body has no ordering comparison. Its only CMPs are
//     `CMP byte ptr [EDI + 0x10],0x0` and `CMP ESI,EBP`, both equality tests
//     against zero, and every other guard is TEST/SHR against one bit. There is no
//     <, >, <= or >= anywhere in the 110 instructions, so there is no signedness
//     to get wrong and none is exercised. What IS exercised is that both of those
//     equality tests are equalities and not truthiness: a latch of 0x80 and one of
//     0xff must take the active path, and a service word of 0x00000001 must be
//     treated as non-null.
//   * THE MEANING of the two immediate keys, of the flag word's bit assignments,
//     of the two-dword pair or of the eight-dword list. Only their addresses,
//     counts, order, and the dwords this body writes, are asserted.
//   * THAT THE SERVICE'S LEADING WORD IS A VTABLE POINTER. The body performs a
//     two-level table read at displacement 0x14 and nothing here identifies the
//     table. The test installs an ordinary aligned byte run with a function word
//     in one slot, which is what the bytes imply and no more.
//   * THE CALLEE-SAVED REGISTER CONTRACT. EBP is borrowed as the literal-zero
//     third argument (0x00a9821d) and the listing never re-zeroes it, so a callee
//     violating the x86-32 convention would change the original's behaviour. The
//     C++ observers here preserve EBP by that same convention, so the case cannot
//     be driven and is NOT claimed.
//   * THE CALLEES' RETURN VALUES. No instruction between 0x00a9824a and 0x00a9832e
//     reads EAX and the epilogue does not move it, so nothing about a return value
//     is asserted; the observers return void for that reason.
//   * 0x00883860's OWN body beyond its five bytes. It is observed as "was called,
//     with no argument, and its result was used only as a null test"; the test
//     supplies the result and makes no claim about the global it reads.
//
// main() returns 0 only when every case passed.

#include "sw2_00a98200_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace osr = openspore::reconstruction::pkg_swarm_w2_00a98200;

namespace {

using osr::Byte;
using osr::Word;

constexpr std::size_t kObjectBytes = 0x40;

// -- the recorder ------------------------------------------------------------
// One row per indirect call, sampled from inside the callee.
struct CallRecord {
  const char* who;                    // which observer fired
  osr::ServiceObject* service;        // the ECX argument
  Word key;                           // first stack argument
  void* properties;                   // second stack argument
  Word tail;                          // third stack argument
  Word pair[osr::kPairWordCount];     // the first two dwords at `properties`
  Word list[osr::kListWordCount];     // the eight dwords at `properties`, 8 apart
  Byte latch;                         // receiver + 0x10, at the moment of the call
  void* record;                       // the record the model will read next
  Word flag_word;                     // that record's +0x08, at the moment of the call
  Word record_key;                    // that record's +0x0c, at the moment of the call
};

std::vector<CallRecord> g_calls;
int g_acquire_calls = 0;
osr::ServiceObject* g_acquire_result = nullptr;
void* g_receiver_watch = nullptr;

// What the real observer does to the world on its way in. Consumed once, so its
// effect is visible to the NEXT call and never to the one it rides on -- which is
// exactly what makes a stale-cache defect observable.
enum class Hook { kNone, kSwapRecord, kSwapTable, kPokeListSlot0 };
Hook g_hook = Hook::kNone;
void* g_hook_record_replacement = nullptr;
void* g_hook_table_replacement = nullptr;
Word g_hook_poke_value = 0;

void sample(const char* who, osr::ServiceObject* service, Word key, void* properties,
            Word tail) {
  CallRecord row;
  row.who = who;
  row.service = service;
  row.key = key;
  row.properties = properties;
  row.tail = tail;
  for (std::size_t index = 0; index < osr::kPairWordCount; ++index) {
    row.pair[index] = osr::word_at(properties, index * osr::kFrameStride);
  }
  for (std::size_t index = 0; index < osr::kListWordCount; ++index) {
    row.list[index] = osr::word_at(properties, osr::kFrameStride * index);
  }
  row.latch = osr::byte_at(g_receiver_watch, osr::kReceiverLatchOffset);
  row.record =
      reinterpret_cast<void*>(osr::word_at(g_receiver_watch, osr::kReceiverRecordPointerOffset));
  row.flag_word = osr::word_at(row.record, osr::kRecordFlagsOffset);
  row.record_key = osr::word_at(row.record, osr::kRecordCallKeyOffset);

  if (g_hook != Hook::kNone) {
    switch (g_hook) {
      case Hook::kSwapRecord:
        // A callee rewriting the receiver's +0x0c. 0x00a9824c/79/a3 re-read it,
        // so blocks two onward must see the new record.
        osr::mutable_word_at(g_receiver_watch, osr::kReceiverRecordPointerOffset) =
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_hook_record_replacement));
        break;
      case Hook::kSwapTable:
        // A callee rewriting the service's LEADING WORD. 0x00a98230/59/87/1d
        // re-read [ESI] before every fetch, so calls two onward must go to the
        // replacement table.
        osr::mutable_word_at(service, osr::kServiceLeadingWordOffset) =
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_hook_table_replacement));
        break;
      case Hook::kPokeListSlot0:
        // The list's dword 0 sits 0x10 bytes above the pair's base, so the pair
        // pointer the callee holds addresses it. A model that allocated a fresh
        // frame per block would not show this.
        osr::mutable_word_at(properties, osr::kListWord0Offset - osr::kPairBaseOffset) =
            g_hook_poke_value;
        break;
      case Hook::kNone:
        break;
    }
    g_hook = Hook::kNone;
  }
  g_calls.push_back(row);
}

// The real observer and the decoys. Each is a distinct function so a wrong
// dispatch is reported BY NAME rather than as a count.
#define OPENSWORE_SLOT_OBSERVER(tag)                                        \
  extern "C" void PKG_SWARM_W2_00A98200_THISCALL obs_##tag(                 \
      osr::ServiceObject* service, Word key, void* properties, Word tail) { \
    sample(#tag, service, key, properties, tail);                           \
  }

OPENSWORE_SLOT_OBSERVER(main)
OPENSWORE_SLOT_OBSERVER(alt)
OPENSWORE_SLOT_OBSERVER(table_decoy_08)
OPENSWORE_SLOT_OBSERVER(table_decoy_0c)
OPENSWORE_SLOT_OBSERVER(table_decoy_10)
OPENSWORE_SLOT_OBSERVER(table_decoy_18)
OPENSWORE_SLOT_OBSERVER(table_decoy_20)
OPENSWORE_SLOT_OBSERVER(service_decoy_04)
OPENSWORE_SLOT_OBSERVER(service_decoy_08)
OPENSWORE_SLOT_OBSERVER(service_decoy_0c)
OPENSWORE_SLOT_OBSERVER(service_decoy_14)
OPENSWORE_SLOT_OBSERVER(service_decoy_18)

// -- the one direct callee ---------------------------------------------------
// Observed, and parameterless because 0x00883860's own five bytes are
// `MOV EAX,[0x016514cc]` / `RET`: it takes no stack word (nothing is pushed
// before 0x00a98216) and reads no register, so the ECX still holding the receiver
// at the call site is a stale value, not an argument.
extern "C" osr::ServiceObject* PKG_SWARM_W2_00A98200_CDECL
openspore_acquire_service_00883860() {
  ++g_acquire_calls;
  return g_acquire_result;
}

// -- the world ---------------------------------------------------------------
// Over-provisioned on purpose. The body's own extents are 0x54 (receiver), 0x24
// (record) and 0x04 (service); the extra room is where the decoys and the
// byte-for-byte comparison live. Every buffer is 4-aligned, which is what makes
// the displacement-named dword accesses aligned, as the listing's are.
struct ReceiverStore {
  std::vector<Byte> bytes;
  ReceiverStore() : bytes(0xa0, 0) {}
  osr::Receiver* as_receiver() { return reinterpret_cast<osr::Receiver*>(bytes.data()); }
};
struct ObjectStore {
  std::vector<Byte> bytes;
  ObjectStore() : bytes(kObjectBytes, 0) {}
};
struct World {
  ReceiverStore receiver;
  ObjectStore record_a;
  ObjectStore record_b;
  ObjectStore service;
  ObjectStore table_a;
  ObjectStore table_b;
};
World g_world;

// The values planted in the record, each distinct so a list slot filled from the
// wrong displacement cannot coincide with the right one.
constexpr Word kRecordKeyA = 0x11111111u;
constexpr Word kRecordKeyB = 0x99999999u;
constexpr Word kPayload0 = 0xaaaa0001u;
constexpr Word kPayload1 = 0xbbbb0002u;
constexpr Word kPayload2 = 0xcccc0003u;
constexpr Word kPayload3 = 0xdddd0004u;
constexpr Word kPayload4 = 0xeeee0005u;
// The receiver's +0x50 dword and its +0x18 ADDRESS are two different things and
// the model must put each in its own list slot. These two values are chosen so
// neither can be mistaken for the other, nor for a payload.
constexpr Word kReceiverPayloadDecoy = 0x7a7a7a7au;
constexpr Word kReceiverInteriorValueDecoy = 0x5c5c5c5cu;
// The frame's prior content. Never equal to any planted value, so "the callee saw
// the poison" and "the callee saw a payload" are distinguishable.
constexpr Word kPoison = 0x0f0e0d0cu;
constexpr Word kPokeValue = 0xdeadc0deu;

template <typename Fn>
Word func_word(Fn fn) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(fn));
}

void store_word(void* base, std::size_t offset, Word value) {
  osr::mutable_word_at(base, offset) = value;
}
void store_byte(void* base, std::size_t offset, Byte value) {
  osr::mutable_byte_at(base, offset) = value;
}
void store_func_word(ObjectStore& store, std::size_t offset, Word value) {
  store_word(store.bytes.data(), offset, value);
}

// Fill an object with a per-offset pattern, so any dword read out of it is a
// function of its own displacement and nothing else.
void poison_object(ObjectStore& store, Word salt) {
  for (std::size_t offset = 0; offset < store.bytes.size(); offset += sizeof(Word)) {
    store_word(store.bytes.data(), offset, salt + static_cast<Word>(offset * 4u + 0x100u));
  }
}

void build_record(ObjectStore& store, Word flags, Word key, Word salt) {
  poison_object(store, salt);
  store_word(store.bytes.data(), osr::kRecordFlagsOffset, flags);
  store_word(store.bytes.data(), osr::kRecordCallKeyOffset, key);
  store_word(store.bytes.data(), osr::kRecordValue0Offset, kPayload0);
  store_word(store.bytes.data(), osr::kRecordValue1Offset, kPayload1);
  store_word(store.bytes.data(), osr::kRecordValue2Offset, kPayload2);
  store_word(store.bytes.data(), osr::kRecordValue3Offset, kPayload3);
  store_word(store.bytes.data(), osr::kRecordValue4Offset, kPayload4);
}

void build_table(ObjectStore& table, Word main_word) {
  poison_object(table, 0x70000000u);
  store_func_word(table, 0x08, func_word(obs_table_decoy_08));
  store_func_word(table, 0x0c, func_word(obs_table_decoy_0c));
  store_func_word(table, 0x10, func_word(obs_table_decoy_10));
  store_func_word(table, osr::kServiceSlotDisplacement, main_word);
  store_func_word(table, 0x18, func_word(obs_table_decoy_18));
  store_func_word(table, 0x20, func_word(obs_table_decoy_20));
}

void reset(Word flags, Word latch, bool service_available, Word key = kRecordKeyA) {
  g_calls.clear();
  g_acquire_calls = 0;
  g_hook = Hook::kNone;

  // The receiver: decoys everywhere the body names no displacement, then the
  // three words it does, then the latch byte last so nothing overwrites it.
  void* receiver = g_world.receiver.bytes.data();
  for (std::size_t offset = 0; offset < g_world.receiver.bytes.size(); offset += 4) {
    store_word(receiver, offset, 0x01020300u + static_cast<Word>(offset));
  }
  store_byte(receiver, osr::kReceiverLatchOffset + 1, 0x77);  // the byte above the latch
  store_byte(receiver, osr::kReceiverLatchOffset - 1, 0x66);  // the byte below it
  store_word(receiver, osr::kReceiverInteriorOffset, kReceiverInteriorValueDecoy);
  store_word(receiver, osr::kReceiverPayloadOffset, kReceiverPayloadDecoy);
  store_word(receiver, osr::kReceiverRecordPointerOffset,
             static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_world.record_a.bytes.data())));
  store_byte(receiver, osr::kReceiverLatchOffset, static_cast<Byte>(latch));

  build_record(g_world.record_a, flags, key, 0x20000000u);
  // record_b carries bit 4 only, so swapping the record pointer mid-run still
  // reaches the list call, and its key displacement holds a sixth distinct value.
  build_record(g_world.record_b, 0x10u, kRecordKeyB, 0x40000000u);

  // The service: the leading word is the table base, and five function words sit
  // inside the object so a one-level fetch, or a fetch from a neighbouring
  // displacement, fires a named decoy.
  ObjectStore& service = g_world.service;
  poison_object(service, 0x50000000u);
  store_word(service.bytes.data(), 0x00,
             static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_world.table_a.bytes.data())));
  store_func_word(service, 0x04, func_word(obs_service_decoy_04));
  store_func_word(service, 0x08, func_word(obs_service_decoy_08));
  store_func_word(service, 0x0c, func_word(obs_service_decoy_0c));
  store_func_word(service, 0x14, func_word(obs_service_decoy_14));
  store_func_word(service, 0x18, func_word(obs_service_decoy_18));

  build_table(g_world.table_a, func_word(obs_main));
  build_table(g_world.table_b, func_word(obs_alt));

  g_acquire_result =
      service_available ? reinterpret_cast<osr::ServiceObject*>(service.bytes.data()) : nullptr;
  g_receiver_watch = receiver;
  osr::set_frame_poison_word(kPoison);
}

void run(Word unused_stack_word = 0) {
  osr::re_00a98200(g_world.receiver.as_receiver(), unused_stack_word);
}

Word receiver_payload() { return kReceiverPayloadDecoy; }
Word receiver_interior_address() {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_world.receiver.bytes.data() +
                                                            osr::kReceiverInteriorOffset));
}

// -- the check harness -------------------------------------------------------
int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (condition) {
    return;
  }
  ++g_failures;
  std::printf("  FAIL: %s\n", what);
}

void check_word(Word got, Word want, const char* what) {
  ++g_checks;
  if (got == want) {
    return;
  }
  ++g_failures;
  std::printf("  FAIL: %s (got 0x%08x, want 0x%08x)\n", what, got, want);
}

void check_count(std::size_t got, std::size_t want, const char* what) {
  ++g_checks;
  if (got == want) {
    return;
  }
  ++g_failures;
  std::printf("  FAIL: %s (got %zu, want %zu)\n", what, got, want);
}

void check_tag(const char* got, const char* want, const char* what) {
  ++g_checks;
  if (std::string(got) == std::string(want)) {
    return;
  }
  ++g_failures;
  std::printf("  FAIL: %s (observer '%s' fired, only '%s' should have)\n", what, got, want);
}

// Decoys fire only if the dispatch went somewhere it must not have. Reported by
// name, because "a decoy fired" is the signature of a one-level fetch, a wrong
// slot displacement or a wrong base object, and those need different fixes.
void check_no_decoys(const char* what) {
  ++g_checks;
  for (const CallRecord& row : g_calls) {
    if (std::string(row.who) == "main" || std::string(row.who) == "alt") {
      continue;
    }
    ++g_failures;
    std::printf("  FAIL: %s -- decoy dispatch '%s' fired\n", what, row.who);
    return;
  }
}

// -- the byte-identity check -------------------------------------------------
// The body writes exactly one byte of the receiver, at +0x10. Everything else in
// the 0xa0-byte store must come out untouched -- including the decoys at the
// neighbouring offsets, the +0x18 dword, the +0x50 dword and the +0x0c record
// pointer.
std::vector<Byte> g_receiver_before;

void snapshot_receiver() { g_receiver_before = g_world.receiver.bytes; }

void check_receiver_untouched_except_latch(const char* what) {
  ++g_checks;
  std::size_t offenders = 0;
  for (std::size_t offset = 0; offset < g_receiver_before.size(); ++offset) {
    if (offset == osr::kReceiverLatchOffset) {
      continue;
    }
    if (g_receiver_before[offset] == g_world.receiver.bytes[offset]) {
      continue;
    }
    if (offenders == 0) {
      std::printf("  FAIL: %s -- receiver byte at +0x%02zx changed (0x%02x -> 0x%02x)\n", what,
                  offset, g_receiver_before[offset], g_world.receiver.bytes[offset]);
    }
    ++offenders;
  }
  if (offenders == 0) {
    return;
  }
  ++g_failures;
  if (offenders > 1) {
    std::printf("  FAIL: %s -- %zu receiver bytes changed in total\n", what, offenders);
  }
}

// -- the cases ---------------------------------------------------------------
void case_latch_already_zero() {
  std::printf("case: latch byte already zero -> the body transfers control nowhere\n");
  reset(0xffffffffu, 0x00, true);
  snapshot_receiver();
  run();
  check_count(static_cast<std::size_t>(g_acquire_calls), 0u,
              "0x00a9820a jumps to 0x00a98332, which is before the CALL at 00a98216");
  check_count(g_calls.size(), 0u, "no indirect call is reachable from the early exit");
  check_no_decoys("early exit");
  check_receiver_untouched_except_latch(
      "the early exit at 00a98332 must not write the latch, which is already zero");
}

void case_latch_nonzero_service_null() {
  std::printf("case: non-zero latch, null service -> latch cleared, nothing dispatched\n");
  reset(0xffffffffu, 0x01, false);
  snapshot_receiver();
  run();
  check_count(static_cast<std::size_t>(g_acquire_calls), 1u, "0x00a98216 runs exactly once");
  check_count(g_calls.size(), 0u, "0x00a98221 jumps to 0x00a98330 before any dispatch");
  check_word(osr::byte_at(g_world.receiver.bytes.data(), osr::kReceiverLatchOffset), 0u,
             "0x00a98212 clears the latch BEFORE the service lookup, so a null service clears it");
  check_receiver_untouched_except_latch("null service");
}

void case_latch_is_an_equality_not_a_truth() {
  std::printf("case: latch 0x80, 0xff, 0x02 take the active path (CMP against zero, not a bool)\n");
  const Word latches[] = {0x80u, 0xffu, 0x02u};
  for (Word latch : latches) {
    reset(0u, latch, true);
    run();
    check_count(static_cast<std::size_t>(g_acquire_calls), 1u,
                "any non-zero latch byte is != 0 and must reach the CALL at 0x00a98216");
    check_word(osr::byte_at(g_world.receiver.bytes.data(), osr::kReceiverLatchOffset), 0u,
               "0x00a98212 stores the byte zero, not a masked or truncated value");
  }
}

void case_service_word_low_nonzero() {
  std::printf("case: a service word of 1 is non-null (CMP ESI,EBP is a full dword compare)\n");
  reset(0u, 0x01, true);
  store_word(g_world.service.bytes.data(), 0x00, 0x00000001u);
  snapshot_receiver();
  run();
  check_count(static_cast<std::size_t>(g_acquire_calls), 1u, "the service is fetched once");
  check_count(g_calls.size(), 0u, "flag word zero means no guard holds, so no dispatch");
  check_receiver_untouched_except_latch("flag word zero");
}

void case_each_guard_alone() {
  std::printf("case: each of bits 0, 1, 2, 4 alone makes exactly one call, with its own key\n");
  for (Word bit = 0; bit <= 4; ++bit) {
    const Word flags = 1u << bit;
    if (bit == 3u) {
      continue;  // bit 3 has its own case below
    }
    reset(flags, 0x01, true);
    snapshot_receiver();
    run();
    check_count(g_calls.size(), 1u, "one guard bit set makes exactly one indirect call");
    check_no_decoys("single-bit guard");
    if (g_calls.size() != 1) {
      continue;
    }
    const CallRecord& row = g_calls.front();
    check_tag(row.who, "main", "the call lands in the table's +0x14 slot");
    check_word(row.tail, 0u, "the third stack argument is EBP, which 0x00a9821d zeroed");
    check_word(row.latch, 0u, "the latch was already zero when the callee was entered");
    check_word(row.flag_word, flags, "the callee sampled the same flag word the guard read");
    check_receiver_untouched_except_latch("single-bit guard");
    if (bit == 4u) {
      check_word(row.key, kRecordKeyA, "the list call's key is the record's +0x0c (0x00a9831f)");
      // The list's first two dwords are also the pair's first two, since the two
      // frame objects are contiguous and both are read at the same relative
      // addresses. With bits 5 and 6 clear they carry the frame's prior content.
      check_word(row.pair[0], kPoison, "list dword 0 is uninitialised on this run");
      check_word(row.pair[1], kPoison, "list dword 1 is uninitialised on this run");
    } else {
      const Word want_key = (bit == 2u) ? osr::kKeyFlagOffB : osr::kKeyFlagOffA;
      check_word(row.key, want_key, "the first stack argument is the key the listing pushes");
      check_word(row.pair[0], (bit == 1u) ? osr::kPairFlagOn : 0u,
                 "the pair's first dword is 0, except 0x00a9826f's literal 1");
      check_word(row.pair[1], 0u, "the pair's second dword is always EBP, i.e. zero");
    }
  }
}

void case_four_guards_in_listing_order() {
  std::printf("case: all four guards set -> four calls, in the listing's order, not key order\n");
  reset(0x1u | 0x2u | 0x4u | 0x10u, 0x01, true);
  snapshot_receiver();
  run();
  check_count(g_calls.size(), 4u, "four independent guards, four calls, no fallthrough between them");
  check_no_decoys("all four guards");
  if (g_calls.size() != 4) {
    return;
  }
  const Word want_key[4] = {osr::kKeyFlagOffA, osr::kKeyFlagOffA, osr::kKeyFlagOffB, kRecordKeyA};
  const Word want_pair0[4] = {0u, osr::kPairFlagOn, 0u, kPoison};
  for (std::size_t index = 0; index < 4; ++index) {
    check_tag(g_calls[index].who, "main", "every call lands in the +0x14 slot");
    check_word(g_calls[index].key, want_key[index],
               "the calls appear in block order: 0x00a9823b, 0x00a98264, 0x00a98292, then the key");
    check_word(g_calls[index].pair[0], want_pair0[index],
               "only 0x00a9826f stores a non-zero, so the 1 marks the SECOND call");
    check_word(g_calls[index].tail, 0u, "every call's third argument is the zero EBP");
  }
  // The three pair calls share ONE address: the listing hands over the same frame
  // slot every time. A model that allocated a fresh pair per block would differ.
  check(g_calls[0].properties == g_calls[1].properties &&
            g_calls[1].properties == g_calls[2].properties,
        "the three pair calls are handed the SAME frame address (0x00a98236/5f/8d)");
  check(g_calls[3].properties != g_calls[0].properties,
        "the list call is handed a different frame address (0x00a98326)");
  // The two bases are exactly 0x10 apart, which is what fixes the pair's second
  // dword at 0x14 (0x00a98242) and the list's first at 0x1c (0x00a982c3) on one
  // 8-byte stride. A model that swapped the two bases, or that laid them out
  // contiguously, fails here.
  check(reinterpret_cast<std::uintptr_t>(g_calls[3].properties) -
                reinterpret_cast<std::uintptr_t>(g_calls[0].properties) ==
            0x10u,
        "the list base is exactly 0x10 above the pair base in the frame");
}

void case_bit_three_is_never_tested() {
  std::printf("case: bit 3 alone, and every bit except 0/1/2/4, make NO call\n");
  reset(0x8u, 0x01, true);
  run();
  check_count(static_cast<std::size_t>(g_acquire_calls), 1u, "the service is still fetched");
  check_count(g_calls.size(), 0u, "no instruction in the 110 shifts the flag word by 0x3");
  check_no_decoys("bit 3");

  const Word only_unused_bits = 0xffffffffu & ~0x17u;
  reset(only_unused_bits, 0x01, true);
  run();
  check_count(g_calls.size(), 0u, "bits 3 and 5..31 set, none of the four guards set: no call");

  reset(only_unused_bits | 0x10u, 0x01, true);
  run();
  check_count(g_calls.size(), 1u, "bit 4 set with bits 5..9 also set makes exactly one call");
  check_no_decoys("unused bits");
}

void case_list_slot_mapping() {
  std::printf("case: bits 5..9 fill the list's first five dwords, each from its own displacement\n");
  const Word flags = 0x10u | (0x1fu << 5);  // bit 4 plus bits 5, 6, 7, 8, 9
  reset(flags, 0x01, true);
  snapshot_receiver();
  run();
  check_count(g_calls.size(), 1u, "one call");
  check_no_decoys("list fill");
  if (g_calls.size() != 1) {
    return;
  }
  const CallRecord& row = g_calls.front();
  const Word want[osr::kListWordCount] = {kPayload0,
                                         kPayload1,
                                         kPayload2,
                                         kPayload3,
                                         kPayload4,
                                         receiver_interior_address(),
                                         receiver_payload(),
                                         0u};
  for (std::size_t index = 0; index < osr::kListWordCount; ++index) {
    check_word(row.list[index], want[index],
               "list dword N comes from the record displacement the listing pairs with it");
  }
  // All six candidate source words are distinct, so a slot filled one displacement
  // early or late cannot coincide with the right answer.
  const Word candidates[6] = {kRecordKeyA, kPayload0, kPayload1, kPayload2, kPayload3, kPayload4};
  for (std::size_t index = 0; index < 5; ++index) {
    for (std::size_t other = 0; other < 6; ++other) {
      if (other == index + 1) {
        continue;  // the right source
      }
      check(row.list[index] != candidates[other],
            "a list slot must not hold a neighbouring record displacement's value");
    }
  }
  check_receiver_untouched_except_latch("list fill");
}

void case_list_slots_carry_frame_poison() {
  std::printf("case: with bits 5..9 clear the list's first five dwords reach the callee unchanged\n");
  const Word poisons[] = {kPoison, 0xa5a51234u, 0u};
  for (Word poison : poisons) {
    reset(0x10u, 0x01, true);
    osr::set_frame_poison_word(poison);
    run();
    check_count(g_calls.size(), 1u, "bit 4 set, list bits clear: one call");
    check_no_decoys("poison run");
    if (g_calls.size() != 1) {
      continue;
    }
    const CallRecord& row = g_calls.front();
    for (std::size_t index = 0; index < 5; ++index) {
      check_word(row.list[index], poison,
                 "0x00a982c3..0x00a9830b are each inside their own guard, so a clear guard leaves "
                 "the frame's prior content in place -- a zero-filling list fails here");
    }
    check_word(row.list[5], receiver_interior_address(),
               "list dword 5 is written unconditionally and holds the receiver's +0x18 ADDRESS");
    check_word(row.list[6], receiver_payload(), "list dword 6 is written unconditionally");
    check_word(row.list[7], 0u, "list dword 7 is written unconditionally, and is the zero EBP");
  }
}

void case_frame_is_shared_across_calls() {
  std::printf("case: an earlier callee's write into the frame is visible to the list call\n");
  reset(0x1u | 0x10u, 0x01, true);
  g_hook = Hook::kPokeListSlot0;
  g_hook_poke_value = kPokeValue;
  run();
  check_count(g_calls.size(), 2u, "bit 0 then bit 4: two calls");
  if (g_calls.size() != 2) {
    return;
  }
  // The poke went to `properties + (0x1c - 0x0c)`, i.e. the list's dword 0 slot,
  // through the pair pointer the FIRST callee held. The second must see it.
  check_word(g_calls[0].list[2], kPoison,
             "the poking callee sampled list dword 0 before it wrote, so the row is the entry state");
  check_word(g_calls[1].list[0], kPokeValue,
             "the frame is one object for the whole body: the poke survives into the list call");
}

void case_record_pointer_is_re_read() {
  std::printf("case: the record pointer is re-read per block, so a callee's swap takes effect\n");
  reset(0x1u | 0x10u, 0x01, true);
  g_hook = Hook::kSwapRecord;
  g_hook_record_replacement = g_world.record_b.bytes.data();
  run();
  check_count(g_calls.size(), 2u, "two calls");
  if (g_calls.size() != 2) {
    return;
  }
  check_word(g_calls[0].key, osr::kKeyFlagOffA, "the first block read the original record");
  check_word(g_calls[0].record_key, kRecordKeyA, "and sampled the original record's key");
  check(g_calls[1].record == g_world.record_b.bytes.data(),
        "the second block's callee sees the receiver's record pointer as the swap left it");
  check_word(g_calls[1].key, kRecordKeyB,
             "the key is the NEW record's +0x0c (0x00a9831f re-reads the record, it does not cache)");
  for (std::size_t index = 0; index < 5; ++index) {
    check_word(g_calls[1].list[index], kPoison,
               "the new record's bits 5..9 are clear, so the five slots stay stale");
  }
  check_no_decoys("record reload");
}

void case_table_pointer_is_re_read_and_two_levels() {
  std::printf("case: the table base is re-read per call, and the fetch is two levels deep\n");
  reset(0x1u | 0x2u | 0x4u | 0x10u, 0x01, true);
  // Repoint the service's LEADING WORD at table_b after the first call, so calls
  // two through four must dispatch into table_b's +0x14 slot.
  g_hook = Hook::kSwapTable;
  g_hook_table_replacement = g_world.table_b.bytes.data();
  run();
  check_count(g_calls.size(), 4u, "four calls");
  check_no_decoys("table reload");
  if (g_calls.size() != 4) {
    return;
  }
  check_tag(g_calls[0].who, "main", "the first call used the table the service started with");
  for (std::size_t index = 1; index < 4; ++index) {
    check_tag(g_calls[index].who, "alt",
              "every later call re-reads [ESI] (0x00a98230/59/87/1d) instead of reusing the target");
  }
  for (const CallRecord& row : g_calls) {
    check(row.service == reinterpret_cast<osr::ServiceObject*>(g_world.service.bytes.data()),
          "ECX is the service object at every dispatch (0x00a98240/69/97/2c)");
  }
}

void case_key_is_not_validated() {
  std::printf("case: the record's call key is passed through unchecked, including zero\n");
  reset(0x10u, 0x01, true, 0x00000000u);
  run();
  check_count(g_calls.size(), 1u, "a zero key does not suppress the call");
  if (g_calls.size() == 1) {
    check_word(g_calls.front().key, 0u, "the key is the record's +0x0c verbatim (0x00a9831f)");
  }
  reset(0x10u, 0x01, true, osr::kKeyFlagOffA);
  run();
  check_count(g_calls.size(), 1u, "a key equal to one of the immediates is not special-cased");
  if (g_calls.size() == 1) {
    check_word(g_calls.front().key, osr::kKeyFlagOffA, "and it is passed through unchanged");
  }
}

void case_unused_stack_word_is_never_read() {
  std::printf("case: the one stack word RET 0x4 consumes is never read\n");
  const Word words[] = {0u, 0xdeadbeefu, 0xffffffffu};
  std::vector<CallRecord> baseline;
  for (Word word : words) {
    reset(0x1u | 0x2u | 0x4u | 0x10u, 0x01, true);
    std::vector<Byte> before = g_world.receiver.bytes;
    run(word);
    check_count(g_calls.size(), 4u, "the same four calls happen whatever the stack word holds");
    if (baseline.empty()) {
      baseline = g_calls;
    } else {
      check_count(g_calls.size(), baseline.size(), "same call count");
      const std::size_t shared =
          g_calls.size() < baseline.size() ? g_calls.size() : baseline.size();
      for (std::size_t index = 0; index < shared; ++index) {
        check_word(g_calls[index].key, baseline[index].key, "same key");
        check_word(g_calls[index].tail, baseline[index].tail, "same third argument");
        check(g_calls[index].properties == baseline[index].properties,
              "same properties address");
      }
    }
    for (std::size_t offset = 0; offset < before.size(); ++offset) {
      if (offset == osr::kReceiverLatchOffset) {
        continue;
      }
      if (before[offset] == g_world.receiver.bytes[offset]) {
        continue;
      }
      check(false, "the stack word must not reach the receiver");
      break;
    }
  }
}

void case_arguments_reach_the_callee_in_push_order() {
  std::printf("case: the three stack arguments arrive key, properties, zero -- in that order\n");
  reset(0x10u, 0x01, true);
  run();
  check_count(g_calls.size(), 1u, "one call");
  if (g_calls.size() != 1) {
    return;
  }
  // The observers are thiscall functions taking (service, key, properties, tail),
  // so the values they receive ARE the order the pushes produced. A model that
  // pushed the key second would hand the callee the address in the `key` parameter,
  // and a model that pushed the address first would hand it the key.
  const CallRecord& row = g_calls.front();
  check_word(row.key, kRecordKeyA, "arg 1 is the key, pushed last (0x00a9832b)");
  check(row.properties != nullptr, "arg 2 is a real address, pushed second (0x00a9832a)");
  check_word(static_cast<Word>(reinterpret_cast<std::uintptr_t>(row.properties)),
             static_cast<Word>(reinterpret_cast<std::uintptr_t>(row.properties)),
             "arg 2 is an address rather than a value");
  check_word(row.tail, 0u, "arg 3 is the EBP pushed first (0x00a98325)");
  check(row.key != static_cast<Word>(reinterpret_cast<std::uintptr_t>(row.properties)),
        "arg 1 and arg 2 are distinct values, so a swap between them would be visible");
  check(row.service != nullptr &&
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(row.service)) != row.key,
        "the ECX argument is a pointer distinct from both stack arguments");
}

}  // namespace

int main() {
  case_latch_already_zero();
  case_latch_nonzero_service_null();
  case_latch_is_an_equality_not_a_truth();
  case_service_word_low_nonzero();
  case_each_guard_alone();
  case_four_guards_in_listing_order();
  case_bit_three_is_never_tested();
  case_list_slot_mapping();
  case_list_slots_carry_frame_poison();
  case_frame_is_shared_across_calls();
  case_record_pointer_is_re_read();
  case_table_pointer_is_re_read_and_two_levels();
  case_key_is_not_validated();
  case_unused_stack_word_is_never_read();
  case_arguments_reach_the_callee_in_push_order();

  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
