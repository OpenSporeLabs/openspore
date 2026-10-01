// PKG-SWARM-W2-00F99980 -- VA 0x00f99980
// Behavioural model test for FUN_00f99980 @ 0x00f99980.
//
// The three direct callees -- 0x0067dd50, 0x00692400 and 0x00690120 -- are defined
// here as observers, and the slot the body dispatches through at 0x00f9999f is
// PLANTED by the test rather than hard-coded: the fake manager's leading word points
// at a fake table whose word at +0x7c is this file's slot observer, and every other
// word of both objects is a distinct decoy slot. So the test sees every transfer the
// reconstruction makes -- which table word, which receiver, which argument, in which
// order -- and can decide what each of them does to memory, including writing the
// receiver behind the model's back.
//
// What is asserted is what the 25-instruction listing fixes and nothing more:
//
//   * the four transfers, once each, and their order;
//   * the two receiver words read (0x894, 0x8a4) and the two written;
//   * that +0x8a4 is cleared UNCONDITIONALLY -- when the sentinel was already there,
//     when the dispatch ran, and when the second guard failed;
//   * that the dispatch runs BEFORE that clear, measured by the slot observer reading
//     the receiver while it is running, and that the notify runs AFTER it;
//   * that the re-read at 0x00f999bc is a real second read, driven in both directions
//     by an observer that clears the field and by one that replaces it;
//   * that the object handed to 0x00690120 is the re-read word and not the zero
//     stored immediately before the transfer;
//   * the notify's ECX receiver and its stack argument 1;
//   * the table displacement 0x7c, the two-level load, and its byte-displacement
//     reading;
//   * that the +0x8a4 word is a pointer passed BY VALUE and never dereferenced;
//   * the exact-equality sentinel test, driven with the words a signed, an unsigned
//     or an off-by-one test would get wrong;
//   * the stack cleanup, measured by sampling ESP inside trampolines;
//   * a byte-level comparison of the whole receiver against a pre-filled pattern.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk it.
// Each names the wrong reconstruction it is aimed at:
//
//   D  the re-read at 0x00f999bc is only a stylistic detail: an observer that clears
//      the field must suppress both the store and the tail transfer;
//   E  ... and one that replaces the field must change what 0x00690120 receives;
//   F  the sentinel test is an exact equality: 0x00000000, 0x7fffffff, 0x80000000
//      and 0xfffffffe must all still dispatch;
//   G  the receiver's words are at 0x894 and 0x8a4 and nowhere else: six decoy words
//      around them must not move, so a one-word slip is visible;
//   H  the +0x8a4 word is a pointer passed by value, not a record that is copied;
//   I  the dispatch is TWO-LEVEL: the manager's leading word is a table pointer, so
//      calling through the manager itself must reach a decoy and be reported;
//   J  0x7c is a BYTE displacement, so an index reading lands four words off and an
//      off-by-one word lands one either side -- all decoys;
//   K  the transfer happens AFTER the clear, and carries the object read before it;
//   L  a second call on the receiver the first call left behind must do nothing;
//   M  the stack cleanup: the body consumes nothing, the notify callee pops its word;
//   T  the arm at 0x00f999c6 / 0x00f999d0 / 0x00f999d1 leaves the stack exactly as it
//      found it and hands the callee the word read before the clear.
//
// What is NOT asserted, and why:
//
//   * EAX. No instruction in the body has EAX as a destination and every call's
//     return word is discarded, so there is no value to assert; the four distinct
//     dead compositions are listed in the .cpp instead.
//   * What 0x0067dd50 reads. Its own body loads a .data word at 0x015fd8c0; this body
//     only ever uses the pointer that comes back, so the test drives that pointer,
//     which is the only channel this body has to the callee.
//   * What 0x00692400 does with its argument, or what 0x00690120 does with the object
//     it is given. Both are outside this body; the observers record what they were
//     handed and, for the notify callee, may write the receiver -- the only side
//     effect of either that this body can observe.
//   * Whether 0x7c is a real slot INDEX in any class. The package models the
//     displacement and nothing more; the test plants the table, so it can only say
//     which displacement the reconstruction read.
//   * Whether the transfer at 0x00f999d1 is emitted as a jump or as a call followed by
//     a return. No C++ spelling forces the jump, and nothing outside the body can tell
//     the two apart, so the test asserts the observable consequences (case T) and the
//     machine's JMP is recorded in the .cpp.

#include "sw2_00f99980_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w2_00f99980 {
namespace {

// The receiver's two machine displacements, and the decoys around them.
constexpr std::size_t kOwnedOffset = 0x894u;
constexpr std::size_t kTargetOffset = 0x8a4u;
constexpr std::size_t kDecoyOwnedMinus8 = 0x88cu;
constexpr std::size_t kDecoyOwnedMinus4 = 0x890u;
constexpr std::size_t kDecoyOwnedPlus4 = 0x898u;
constexpr std::size_t kDecoyOwnedPlus8 = 0x89cu;
constexpr std::size_t kDecoyTargetMinus4 = 0x8a0u;
constexpr std::size_t kDecoyTargetPlus4 = 0x8a8u;
constexpr std::size_t kReceiverBytes = 0x8a8u + 16u;  // a sentinel tail past the modelled run

// The dispatched slot's displacement and the table it is planted in. 512 words is
// enough for the slot (word 31), for an INDEX reading of 0x7c (word 124) and for a
// byte reading one word either side, so all four of those are inside the object and
// every one of the three wrong ones is a decoy.
constexpr std::size_t kSlotOffset = 0x7cu;
constexpr std::size_t kTableWords = 0x200u;

// The poison words the fake pointee objects carry. Nothing the body does may change
// any of them: a byte-level comparison of the whole receiver is asserted in several
// cases, and these are the witnesses for the two objects the body is HANDED.
const Word kTargetPoison = 0x5a5a5a5au;
const Word kOwnedPoison = 0xa5a5a5a5u;
const Word kReplacementPoison = 0xc3c3c3c3u;

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// -- the objects the body is handed -------------------------------------------
// A receiver large enough for every word this body touches, plus a tail, so an
// overrun past 0x8a8 would show up in the byte comparison.
struct ReceiverBytes {
  unsigned char bytes[kReceiverBytes];
};

// The object the +0x8a4 word points at. The body never reads it, so its leading word
// is a poison value: any read the body made of it, and any copy out of it, would
// either move the word or be visible in the slot observer's argument.
struct TargetObject {
  unsigned char bytes[8];
};

struct OwnedObject {
  unsigned char bytes[8];
};

// The fake manager and its table. The manager's LEADING word is the table pointer --
// that is the two-level load 0x00f99997/0x00f99999 performs -- and every other word of
// the manager is a decoy too, so a reconstruction that dispatched through the manager
// instead of through its table is caught rather than merely undefined. The manager is
// 0x88 bytes so that even a table read at the manager's OWN +0x7c is in range and
// lands on a decoy.
struct FakeObjects {
  alignas(4) unsigned char manager[0x88];
  alignas(4) Word table[kTableWords];
  TargetObject target;
  OwnedObject owned;
  OwnedObject owned_replacement;
};

FakeObjects g_objects;

// -- observation --------------------------------------------------------------
enum Call : int {
  kCallManager = 0,
  kCallSlot = 1,
  kCallSlotDecoy = 2,
  kCallNotify = 3,
  kCallRelease = 4,
};

struct Observation {
  int log[16] = {};
  int log_length = 0;

  int manager_calls = 0;
  LightingManager* manager_result = nullptr;

  int slot_calls = 0;
  LightingManager* slot_receiver = nullptr;
  LightingTarget* slot_argument = nullptr;
  // Sampled INSIDE the slot call: the only way to see the ordering of 0x00f9999f (the
  // call) against 0x00f999a7 (the clear).
  Word slot_target_word_seen = 0;
  Word slot_owned_word_seen = 0;
  bool slot_sampled = false;

  int decoy_slot_calls = 0;

  int notify_calls = 0;
  RefCountedObject* notify_receiver = nullptr;
  Word notify_argument = 0;
  Word notify_target_word_seen = 0;
  Word notify_owned_word_seen = 0;
  bool notify_sampled = false;

  int release_calls = 0;
  RefCountedObject* release_receiver = nullptr;
  // The release's OWN return address. For the machine's `POP ESI; JMP 0x00690120`
  // this is the address of THIS BODY'S CALLER, because the transfer is a tail
  // transfer: a call-then-return would leave an address inside the body here.
  const void* release_return_address = nullptr;
  // Sampled INSIDE the release: the only way to see that the clear at 0x00f999c6 runs
  // BEFORE the transfer at 0x00f999d1.
  Word release_owned_word_seen = 0;
  bool release_sampled = false;

  // What the notify observer is told to do to the receiver, if anything.
  int notify_writes = 0;  // 0 = nothing, 1 = clear +0x894, 2 = replace +0x894
  RefCountedObject* notify_replacement = nullptr;

  void reset() { *this = Observation(); }

  void record(Call call) {
    if (log_length < 16) {
      log[log_length] = static_cast<int>(call);
    }
    ++log_length;
  }

  bool log_is(Call a, Call b) const {
    return log_length == 2 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b);
  }
  bool log_is(Call a, Call b, Call c) const {
    return log_length == 3 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b) &&
           log[2] == static_cast<int>(c);
  }
  bool log_is(Call a, Call b, Call c, Call d) const {
    return log_length == 4 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b) &&
           log[2] == static_cast<int>(c) && log[3] == static_cast<int>(d);
  }
};

Observation g_obs;

Word word_of(const void* base, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, static_cast<const unsigned char*>(base) + displacement, sizeof value);
  return value;
}

void store_word(void* base, std::size_t displacement, Word value) {
  std::memcpy(static_cast<unsigned char*>(base) + displacement, &value, sizeof value);
}

void store_pointer(void* base, std::size_t displacement, const void* pointer) {
  std::memcpy(static_cast<unsigned char*>(base) + displacement, &pointer, sizeof pointer);
}

// The receiver the case under test is exercising, so an observer can sample it at a
// moment the caller cannot see.
ReceiverBytes* g_active_receiver = nullptr;

// A pattern no part of the model writes, so a byte-level comparison can say "nothing
// else moved" rather than "the other bytes still hold zero".
ReceiverBytes make_receiver(Word target_word, Word owned_word) {
  ReceiverBytes receiver;
  for (std::size_t index = 0; index < sizeof receiver.bytes; ++index) {
    receiver.bytes[index] = static_cast<unsigned char>(0xa5u ^ (index & 0x3fu));
  }
  store_word(receiver.bytes, kDecoyOwnedMinus8, 0xdeadbe06u);
  store_word(receiver.bytes, kDecoyOwnedMinus4, 0xdeadbe01u);
  store_word(receiver.bytes, kDecoyOwnedPlus4, 0xdeadbe02u);
  store_word(receiver.bytes, kDecoyOwnedPlus8, 0xdeadbe04u);
  store_word(receiver.bytes, kDecoyTargetMinus4, 0xdeadbe03u);
  store_word(receiver.bytes, kDecoyTargetPlus4, 0xdeadbe05u);
  store_word(receiver.bytes, kTargetOffset, target_word);
  store_word(receiver.bytes, kOwnedOffset, owned_word);
  return receiver;
}

// How many bytes of the receiver changed inside each of the two four-byte windows, and
// how many changed outside them. The body has exactly two memory writes to the
// receiver, so every changed byte has to fall inside one of them.
struct ReceiverDiff {
  int owned_window = 0;
  int target_window = 0;
  int outside = 0;
};

ReceiverDiff diff_receiver(const ReceiverBytes& before, const ReceiverBytes& after) {
  ReceiverDiff diff;
  for (std::size_t index = 0; index < sizeof before.bytes; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    if (index >= kOwnedOffset && index < kOwnedOffset + 4) {
      ++diff.owned_window;
    } else if (index >= kTargetOffset && index < kTargetOffset + 4) {
      ++diff.target_window;
    } else {
      ++diff.outside;
    }
  }
  return diff;
}

}  // namespace

// -- the three direct callees, as observers -----------------------------------

// 0x0067dd50 -- the manager. cdecl, no arguments; its own body is a .data load and a
// plain RET. The observer returns whatever the case installed, which is the only
// channel this body has to the manager: the body never dereferences the callee.
extern "C" LightingManager* PKG_SW2_00F99980_CDECL graphics_ilightingmanager_get_0067dd50(
    void) {
  ++g_obs.manager_calls;
  g_obs.record(kCallManager);
  return g_obs.manager_result;
}

// 0x00692400 -- the notify. Receiver in ECX, one stack word read as 0x00692404 does
// and popped by the callee as 0x00692417's RET 0x4 does. The observer records both
// arguments, samples the receiver (which is what shows the clear at 0x00f999a7 had
// already run), and may write the receiver's +0x894 -- the only way a reconstruction
// that ignored the re-read at 0x00f999bc can be caught.
extern "C" void PKG_SW2_00F99980_THISCALL owned_object_notify_00692400(
    RefCountedObject* receiver, Word argument) {
  ++g_obs.notify_calls;
  g_obs.record(kCallNotify);
  g_obs.notify_receiver = receiver;
  g_obs.notify_argument = argument;
  if (g_active_receiver != nullptr) {
    g_obs.notify_target_word_seen = word_of(g_active_receiver->bytes, kTargetOffset);
    g_obs.notify_owned_word_seen = word_of(g_active_receiver->bytes, kOwnedOffset);
    g_obs.notify_sampled = true;
  }
  if (g_active_receiver != nullptr && g_obs.notify_writes == 1) {
    store_word(g_active_receiver->bytes, kOwnedOffset, 0u);
  } else if (g_active_receiver != nullptr && g_obs.notify_writes == 2) {
    store_pointer(g_active_receiver->bytes, kOwnedOffset, g_obs.notify_replacement);
  }
}

// 0x00690120 -- the release, reached only by the tail transfer. Receiver in ECX and no
// stack word, as its own first instruction (TEST ECX,ECX) and its plain RET require.
// The observer records the receiver and samples the receiver's +0x894, which must
// already be the zero stored at 0x00f999c6, while the object it was handed must not
// be that zero.
extern "C" void PKG_SW2_00F99980_THISCALL owned_object_release_00690120(
    RefCountedObject* receiver) {
  ++g_obs.release_calls;
  g_obs.record(kCallRelease);
  g_obs.release_receiver = receiver;
  g_obs.release_return_address = __builtin_return_address(0);
  if (g_active_receiver != nullptr) {
    g_obs.release_owned_word_seen = word_of(g_active_receiver->bytes, kOwnedOffset);
    g_obs.release_sampled = true;
  }
}

// -- the dispatched slot, and the decoys around it ----------------------------

// The slot the reconstruction must reach: 0x7c bytes into the table the manager's
// leading word points at. It records what it was handed and samples the receiver, so
// the ordering of the call against the clear of +0x8a4 is observable.
void PKG_SW2_00F99980_THISCALL slot_observer(LightingManager* receiver,
                                             LightingTarget* target) {
  ++g_obs.slot_calls;
  g_obs.record(kCallSlot);
  g_obs.slot_receiver = receiver;
  g_obs.slot_argument = target;
  if (g_active_receiver != nullptr) {
    g_obs.slot_target_word_seen = word_of(g_active_receiver->bytes, kTargetOffset);
    g_obs.slot_owned_word_seen = word_of(g_active_receiver->bytes, kOwnedOffset);
    g_obs.slot_sampled = true;
  }
}

// One decoy per table word and per non-leading manager word, so any displacement
// other than 0x7c, any reading of 0x7c as an index, and any dispatch through the
// manager instead of through its table lands on a decoy that says so.
void PKG_SW2_00F99980_THISCALL slot_decoy(LightingManager* receiver,
                                          LightingTarget* target) {
  (void)receiver;
  (void)target;
  ++g_obs.decoy_slot_calls;
  g_obs.record(kCallSlotDecoy);
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00f99980

namespace {

using namespace openspore::reconstruction::pkg_swarm_w2_00f99980;

Receiver* as_receiver(ReceiverBytes& bytes) {
  return reinterpret_cast<Receiver*>(bytes.bytes);
}

LightingManager* manager_object() { return reinterpret_cast<LightingManager*>(g_objects.manager); }

LightingTarget* target_object() { return reinterpret_cast<LightingTarget*>(&g_objects.target); }
RefCountedObject* owned_object() { return reinterpret_cast<RefCountedObject*>(&g_objects.owned); }
RefCountedObject* replacement_object() {
  return reinterpret_cast<RefCountedObject*>(&g_objects.owned_replacement);
}

Word target_as_word() {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(target_object()));
}
Word owned_as_word() {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(owned_object()));
}

// Install the fake manager, its table and the three pointee objects, and arm the
// manager pointer the getter observer will hand back.
void install_objects() {
  const Word decoy = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&slot_decoy));
  const Word real = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&slot_observer));
  for (std::size_t index = 0; index < kTableWords; ++index) {
    g_objects.table[index] = decoy;
  }
  g_objects.table[kSlotOffset / sizeof(Word)] = real;
  for (std::size_t index = 4; index < sizeof g_objects.manager; index += 4) {
    store_word(g_objects.manager, index, decoy);
  }
  store_pointer(g_objects.manager, 0, g_objects.table);

  for (std::size_t index = 0; index < sizeof g_objects.target.bytes; ++index) {
    g_objects.target.bytes[index] = static_cast<unsigned char>(0x3cu + index);
  }
  for (std::size_t index = 0; index < sizeof g_objects.owned.bytes; ++index) {
    g_objects.owned.bytes[index] = static_cast<unsigned char>(0x71u + index);
  }
  for (std::size_t index = 0; index < sizeof g_objects.owned_replacement.bytes; ++index) {
    g_objects.owned_replacement.bytes[index] = static_cast<unsigned char>(0x91u + index);
  }
  store_word(target_object(), 0, kTargetPoison);
  store_word(owned_object(), 0, kOwnedPoison);
  store_word(replacement_object(), 0, kReplacementPoison);
}

// Case A -- nothing to do. The sentinel is already in +0x8a4 and +0x894 is null: no
// transfer at all, and not one byte of the receiver changes, because the store at
// 0x00f999a7 rewrites the sentinel with the sentinel.
void case_nothing_to_do() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  ReceiverBytes receiver = make_receiver(0xffffffffu, 0u);
  ReceiverBytes before = receiver;
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  check(g_obs.manager_calls == 0, "A1: the manager is not asked for when the sentinel is present");
  check(g_obs.slot_calls == 0 && g_obs.decoy_slot_calls == 0, "A2: no table word is dispatched");
  check(g_obs.notify_calls == 0, "A3: nothing is notified");
  check(g_obs.release_calls == 0, "A4: nothing is released");
  check(g_obs.log_length == 0, "A5: the body makes no transfer at all");
  const ReceiverDiff diff = diff_receiver(before, receiver);
  check(diff.outside == 0 && diff.owned_window == 0 && diff.target_window == 0,
        "A6: no byte of the receiver changed");
}

// Case B -- the sentinel is absent and the second word is null: the dispatch runs, the
// field is cleared, and nothing else happens.
void case_dispatch_then_clear() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  ReceiverBytes receiver = make_receiver(target_as_word(), 0u);
  ReceiverBytes before = receiver;
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  check(g_obs.manager_calls == 1, "B1: the manager is asked for exactly once");
  check(g_obs.slot_calls == 1, "B2: the table word at +0x7c is dispatched exactly once");
  check(g_obs.decoy_slot_calls == 0, "B3: no other table word was reached");
  check(g_obs.slot_receiver == manager_object(),
        "B4: the slot's receiver is the manager, not the table and not the table word");
  check(g_obs.slot_argument == target_object(), "B5: the slot's argument is +0x8a4's word, by value");
  check(g_obs.slot_sampled, "B6: the slot observer sampled the receiver");
  check(g_obs.slot_target_word_seen == target_as_word(),
        "B7: the dispatch runs BEFORE the clear of +0x8a4 (0x00f9999f before 0x00f999a7)");
  check(g_obs.slot_owned_word_seen == 0u, "B8: the slot call leaves +0x894 alone");
  check(word_of(receiver.bytes, kTargetOffset) == 0xffffffffu, "B9: +0x8a4 is the sentinel afterwards");
  check(word_of(receiver.bytes, kOwnedOffset) == 0u, "B10: +0x894 is untouched");
  check(g_obs.notify_calls == 0, "B11: a null +0x894 is not notified");
  check(g_obs.release_calls == 0, "B12: a null +0x894 is not released");
  check(g_obs.log_is(kCallManager, kCallSlot), "B13: the transfer order is manager then slot");
  check(word_of(target_object(), 0) == kTargetPoison,
        "B14: the object at +0x8a4 was passed over, never read");
  const ReceiverDiff diff = diff_receiver(before, receiver);
  check(diff.outside == 0, "B15: no byte of the receiver outside +0x8a4 changed");
  check(diff.target_window >= 1, "B16: the change is inside +0x8a4's four bytes");
  check(diff.owned_window == 0, "B17: no byte of +0x894 changed");
}

// Case C -- both words are live: the whole body runs, in order.
void case_full_run() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  ReceiverBytes receiver = make_receiver(target_as_word(), owned_as_word());
  ReceiverBytes before = receiver;
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  check(g_obs.log_is(kCallManager, kCallSlot, kCallNotify, kCallRelease),
        "C1: the transfer order is manager, slot, notify, release");
  check(g_obs.notify_receiver == owned_object(), "C2: the notify's ECX receiver is +0x894's word");
  check(g_obs.notify_argument == 1u, "C3: the notify's stack argument is the literal 1");
  check(g_obs.notify_sampled, "C4: the notify observer sampled the receiver");
  check(g_obs.notify_target_word_seen == 0xffffffffu,
        "C5: the clear of +0x8a4 had already run when the notify was called (0x00f999a7 before 0x00f999b7)");
  check(g_obs.notify_owned_word_seen == owned_as_word(),
        "C6: +0x894 is still set when the notify is called (0x00f999c6 has not run)");
  check(g_obs.release_calls == 1, "C7: the transfer ran once");
  check(g_obs.release_receiver == owned_object(), "C8: the release receives the object read at 0x00f999bc");
  check(g_obs.release_receiver != nullptr, "C9: the release receiver is not null");
  check(g_obs.release_sampled, "C10: the release observer sampled the receiver");
  check(g_obs.release_owned_word_seen == 0u,
        "C11: +0x894 is already zero at the transfer (0x00f999c6 before 0x00f999d1)");
  check(g_obs.release_receiver != reinterpret_cast<RefCountedObject*>(receiver.bytes + kOwnedOffset),
        "C12: the release receives the field's VALUE, not the address of the field");
  check(word_of(receiver.bytes, kOwnedOffset) == 0u, "C13: +0x894 is zero afterwards");
  check(word_of(receiver.bytes, kTargetOffset) == 0xffffffffu, "C14: +0x8a4 is the sentinel afterwards");
  check(word_of(owned_object(), 0) == kOwnedPoison,
        "C15: the object at +0x894 was never read or written by the body itself");
  const ReceiverDiff diff = diff_receiver(before, receiver);
  check(diff.outside == 0, "C16: no byte outside the two windows changed");
  check(diff.owned_window == 4 && diff.target_window == 4,
        "C17: all eight changed bytes are the two words the body writes");
}

// -- REFUTATION CASES ---------------------------------------------------------

// D. The re-read at 0x00f999bc is a real second read. An observer that CLEARS +0x894
// must suppress the store at 0x00f999c6 and the transfer at 0x00f999d1: a
// reconstruction that reused the value from 0x00f999a1, or that always released,
// fails both.
void case_notify_can_suppress_the_release() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();
  g_obs.notify_writes = 1;

  ReceiverBytes receiver = make_receiver(target_as_word(), owned_as_word());
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  check(g_obs.notify_calls == 1, "D1: the notify still ran");
  check(g_obs.notify_receiver == owned_object(), "D2: with the pre-call value of +0x894");
  check(g_obs.release_calls == 0, "D3: a +0x894 the notify cleared is NOT released");
  check(g_obs.log_is(kCallManager, kCallSlot, kCallNotify), "D4: the order stops at the notify");
  check(word_of(receiver.bytes, kOwnedOffset) == 0u,
        "D5: +0x894 holds the notify's own zero, so the body never stored it");
  check(word_of(receiver.bytes, kTargetOffset) == 0xffffffffu,
        "D6: +0x8a4 is still cleared -- that store is unconditional (0x00f999a7)");
  const ReceiverDiff diff = diff_receiver(receiver, receiver);
  check(diff.outside == 0 && diff.owned_window == 0 && diff.target_window == 0,
        "D7: (self-comparison, kept so the case's shape matches the others)");
}

// E. ... and an observer that REPLACES +0x894 must change what the release receives. A
// reconstruction that handed 0x00690120 the value read at 0x00f999a1 is refuted.
void case_notify_can_replace_the_released_object() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();
  g_obs.notify_writes = 2;
  g_obs.notify_replacement = replacement_object();

  ReceiverBytes receiver = make_receiver(target_as_word(), owned_as_word());
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  check(g_obs.notify_calls == 1, "E1: the notify ran");
  check(g_obs.notify_receiver == owned_object(), "E2: with the pre-call value of +0x894");
  check(g_obs.release_calls == 1, "E3: the replacement is non-null, so the transfer runs");
  check(g_obs.release_receiver == replacement_object(),
        "E4: the release receives the word read at 0x00f999bc, not the one from 0x00f999a1");
  check(g_obs.release_receiver != owned_object(), "E5: the stale pre-call object is NOT released");
  check(g_obs.release_owned_word_seen == 0u, "E6: the field is zeroed before the transfer");
  check(word_of(receiver.bytes, kOwnedOffset) == 0u, "E7: +0x894 is zero afterwards");
  check(word_of(owned_object(), 0) == kOwnedPoison, "E8: the stale object is untouched");
  check(word_of(replacement_object(), 0) == kReplacementPoison,
        "E9: the replacement object is untouched too");
}

// F. The test at 0x00f99983 is an exact equality against 0xffffffff. A signed `< 0`, an
// unsigned `>= 0xfffffffe`, an off-by-one `-2` sentinel, a `!= 0` test and an
// `unsigned != 0` test each get at least one of these four words wrong, and every one
// of them must still dispatch.
void case_sentinel_test_is_exact() {
  const Word words[] = {0x00000000u, 0x7fffffffu, 0x80000000u, 0xfffffffeu};
  for (std::size_t index = 0; index < sizeof words / sizeof words[0]; ++index) {
    install_objects();
    g_obs.reset();
    g_obs.manager_result = manager_object();

    ReceiverBytes receiver = make_receiver(words[index], 0u);
    g_active_receiver = &receiver;
    re_00f99980(as_receiver(receiver));
    g_active_receiver = nullptr;

    check(g_obs.slot_calls == 1,
          "F1: 0x00000000, 0x7fffffff, 0x80000000 and 0xfffffffe all dispatch");
    check(g_obs.slot_argument == reinterpret_cast<LightingTarget*>(
                                      static_cast<std::uintptr_t>(words[index])),
          "F2: and the word is handed on unchanged");
    check(word_of(receiver.bytes, kTargetOffset) == 0xffffffffu,
          "F3: and it is replaced by the sentinel afterwards");
  }
}

// G. The receiver's words are at 0x894 and 0x8a4 and nowhere else. Six decoy words sit
// around them with visible values, and a reconstruction that read or wrote a
// neighbour moves one of them.
void case_neighbouring_words_are_inert() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  ReceiverBytes receiver = make_receiver(target_as_word(), owned_as_word());
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  check(g_obs.slot_calls == 1, "G1: the dispatch ran once");
  check(g_obs.notify_calls == 1 && g_obs.release_calls == 1, "G2: both trailing calls ran");
  check(word_of(receiver.bytes, kDecoyOwnedMinus8) == 0xdeadbe06u, "G3: +0x88c is untouched");
  check(word_of(receiver.bytes, kDecoyOwnedMinus4) == 0xdeadbe01u, "G4: +0x890 is untouched");
  check(word_of(receiver.bytes, kDecoyOwnedPlus4) == 0xdeadbe02u, "G5: +0x898 is untouched");
  check(word_of(receiver.bytes, kDecoyOwnedPlus8) == 0xdeadbe04u, "G6: +0x89c is untouched");
  check(word_of(receiver.bytes, kDecoyTargetMinus4) == 0xdeadbe03u, "G7: +0x8a0 is untouched");
  check(word_of(receiver.bytes, kDecoyTargetPlus4) == 0xdeadbe05u, "G8: +0x8a8 is untouched");
  check(word_of(receiver.bytes, kTargetOffset) == 0xffffffffu, "G9: only +0x8a4 holds the sentinel");
  check(word_of(receiver.bytes, kOwnedOffset) == 0u, "G10: only +0x894 holds the zero");
}

// H. The +0x8a4 word is a POINTER and it is passed by value. The object it points at
// carries a poison word, and the object the field's NEIGHBOURING word points at
// carries another: a reconstruction that read the pointee, or that followed the
// neighbouring pointer, changes one of them.
void case_target_is_passed_by_value() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  TargetObject decoy_target;
  for (std::size_t index = 0; index < sizeof decoy_target.bytes; ++index) {
    decoy_target.bytes[index] = 0xd7u;
  }
  store_word(&decoy_target, 0, 0xdec0de01u);

  ReceiverBytes receiver = make_receiver(target_as_word(), 0u);
  store_pointer(receiver.bytes, kDecoyTargetMinus4, &decoy_target);
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  const unsigned char* argument =
      reinterpret_cast<const unsigned char*>(g_obs.slot_argument);
  check(g_obs.slot_argument == target_object(),
        "H1: the argument is the field's own value, not the pointee and not &field");
  check(argument >= g_objects.target.bytes && argument < g_objects.target.bytes + 8,
        "H2: the argument lies inside the object the field pointed at");
  check(argument < receiver.bytes || argument >= receiver.bytes + sizeof receiver.bytes,
        "H3: and it is not an address inside the receiver itself");
  check(word_of(target_object(), 0) == kTargetPoison,
        "H4: the pointee's leading word is unchanged -- the body never read through it");
  check(word_of(&decoy_target, 0) == 0xdec0de01u,
        "H5: the object the neighbouring word points at is untouched");
  check(word_of(receiver.bytes, kDecoyTargetMinus4) ==
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_target)),
        "H6: the neighbouring pointer word is untouched");
}

// I and J. The dispatch is a TWO-LEVEL load at a BYTE displacement. Every table word
// other than 0x7c is a decoy, and every word of the manager but its leading one is a
// decoy too, so dispatching through the manager instead of through its table, reading
// one dword either side of 0x7c, and reading 0x7c as a dword INDEX (word 124) are all
// reported rather than merely wrong.
void case_two_level_dispatch_at_a_byte_displacement() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  ReceiverBytes receiver = make_receiver(target_as_word(), 0u);
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  check(g_obs.slot_calls == 1, "I1: the table word at +0x7c is the one that was called");
  check(g_obs.decoy_slot_calls == 0,
        "I2: no other table word and no non-leading word of the manager was called");
  check(g_obs.slot_receiver == manager_object(),
        "I3: the receiver is the manager itself, so the table was reached through its leading word");
  check(sizeof g_objects.manager > kSlotOffset,
        "I4: the manager is larger than the slot displacement, so a table read at the manager's own +0x7c was in range and is therefore covered by a decoy");
  check(g_objects.table[kSlotOffset / sizeof(Word)] ==
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(&slot_observer)),
        "J1: 0x7c divided by the word size is word 31 of the table");
  check(g_objects.table[kSlotOffset] ==
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(&slot_decoy)),
        "J2: an INDEX reading of 0x7c would have called word 124, which is a decoy");
  check(g_objects.table[32] ==
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(&slot_decoy)),
        "J3: an off-by-one-word reading would have called word 32");
  check(g_objects.table[30] ==
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(&slot_decoy)),
        "J4: and so would word 30");
}

// K. The transfer happens AFTER the clear and carries the object read before it. Here
// +0x8a4 is 0, which is not the sentinel, so the dispatch runs with a null argument:
// a reconstruction that treated "absent" as "null" is refuted as well.
void case_release_happens_after_the_clear() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  ReceiverBytes receiver = make_receiver(0u, owned_as_word());
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  check(g_obs.slot_calls == 1, "K1: a zero at +0x8a4 is not the sentinel, so it dispatches");
  check(g_obs.slot_argument == nullptr, "K2: and the argument is that zero, unmodified");
  check(g_obs.notify_calls == 1 && g_obs.release_calls == 1, "K3: both trailing calls ran");
  check(g_obs.release_receiver == owned_object(), "K4: the object is the pre-store value");
  check(g_obs.release_receiver != nullptr, "K5: never the zero that was just stored");
  check(g_obs.release_owned_word_seen == 0u, "K6: the field is already zero at the transfer");
  check(g_obs.log_is(kCallManager, kCallSlot, kCallNotify, kCallRelease),
        "K7: the transfer order is manager, slot, notify, release");
}

// L. A second call on the receiver the first call left behind must do nothing at all:
// the sentinel the first call stored is what the second call's equality test finds.
void case_second_call_is_inert() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  ReceiverBytes receiver = make_receiver(target_as_word(), owned_as_word());
  g_active_receiver = &receiver;
  re_00f99980(as_receiver(receiver));
  ReceiverBytes after_first = receiver;
  const int first_length = g_obs.log_length;
  g_obs.log_length = 0;
  g_obs.manager_calls = 0;
  g_obs.slot_calls = 0;
  g_obs.decoy_slot_calls = 0;
  g_obs.notify_calls = 0;
  g_obs.release_calls = 0;
  re_00f99980(as_receiver(receiver));
  g_active_receiver = nullptr;

  check(first_length == 4, "L1: the first call made all four transfers");
  check(g_obs.manager_calls == 0 && g_obs.slot_calls == 0,
        "L2: the second call does not dispatch -- +0x8a4 is the sentinel it stored");
  check(g_obs.notify_calls == 0 && g_obs.release_calls == 0,
        "L3: the second call does not notify or release -- +0x894 is the zero it stored");
  const ReceiverDiff diff = diff_receiver(after_first, receiver);
  check(diff.outside == 0 && diff.owned_window == 0 && diff.target_window == 0,
        "L4: the second call changed no byte of the receiver");
}

// M. STACK CLEANUP, measured. ESP is sampled inside a trampoline, before the call and
// after the return. The reconstructed function takes no stack argument, so the two
// samples are equal only if it consumed nothing. The notify callee is pushed one word
// and is callee-cleaned (its own bytes end C2 04 00), so its two samples are equal
// only if the callee popped it; a caller-cleaned model would leave the second sample
// four bytes lower.
struct EspSamples {
  std::uint32_t before = 0;
  std::uint32_t after = 0;
};

EspSamples call_no_arguments(Receiver* receiver) {
  const std::uint32_t target =
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&re_00f99980));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  // EAX is in the clobber list, so the compiler cannot have allocated the receiver to
  // it and the `movl ..., %%ecx` before the call really is the receiver.
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before = before;
  samples.after = after;
  return samples;
}

EspSamples call_one_callee_cleaned_argument(RefCountedObject* receiver, Word argument) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&owned_object_notify_00692400));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "pushl %[arg]\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver), [arg] "r"(argument)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before = before;
  samples.after = after;
  return samples;
}

void case_stack_cleanup_is_measured() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  ReceiverBytes receiver = make_receiver(0xffffffffu, 0u);
  const EspSamples body = call_no_arguments(as_receiver(receiver));
  check(body.after == body.before,
        "M1: the reconstructed function consumed no stack word (bare RET, 0x00f999d7)");
  check(g_obs.manager_calls == 0, "M2: the trampoline really reached the body");

  g_obs.reset();
  const EspSamples notify =
      call_one_callee_cleaned_argument(owned_object(), kReleaseNotificationArgument);
  check(notify.after == notify.before,
        "M3: the notify callee owns its one argument word (0x00692417 is C2 04 00)");
  check(g_obs.notify_calls == 1 && g_obs.notify_receiver == owned_object(),
        "M4: ECX carried the receiver the trampoline was given");
  check(g_obs.notify_argument == kReleaseNotificationArgument,
        "M5: and the pushed word arrived as the argument");
}

// N. The two guards are separate tests of two separate READS, and the clear of +0x8a4
// does not depend on either of them.
void case_guards_are_separate() {
  install_objects();

  // The field is set at entry and the notify clears it: the first guard fires, the
  // second suppresses the transfer.
  g_obs.reset();
  g_obs.manager_result = manager_object();
  g_obs.notify_writes = 1;
  {
    ReceiverBytes receiver = make_receiver(0xffffffffu, owned_as_word());
    g_active_receiver = &receiver;
    re_00f99980(as_receiver(receiver));
    g_active_receiver = nullptr;
    check(g_obs.manager_calls == 0, "N1: the sentinel is in place, so nothing dispatches");
    check(g_obs.notify_calls == 1, "N2: the notify still ran");
    check(g_obs.release_calls == 0, "N3: but nothing is released");
    check(word_of(receiver.bytes, kTargetOffset) == 0xffffffffu,
          "N4: and the unconditional clear still ran");
  }

  // The other direction: the field starts null, so the first guard fires and there is
  // no notify at all, whatever the notify observer was told to do.
  g_obs.reset();
  g_obs.manager_result = manager_object();
  g_obs.notify_writes = 2;
  g_obs.notify_replacement = replacement_object();
  {
    ReceiverBytes receiver = make_receiver(0xffffffffu, 0u);
    g_active_receiver = &receiver;
    re_00f99980(as_receiver(receiver));
    g_active_receiver = nullptr;
    check(g_obs.notify_calls == 0, "N5: a null +0x894 skips the notify entirely");
    check(g_obs.release_calls == 0, "N6: and the transfer with it");
    check(word_of(receiver.bytes, kOwnedOffset) == 0u, "N7: +0x894 is still null");
  }
}

// T. The arm at 0x00f999c6 / 0x00f999d0 / 0x00f999d1 leaves nothing behind. The
// machine pops its saved ESI and then jumps out, so the transfer runs on a stack that
// is exactly the entry stack, and the body hands 0x00690120 the word it read before the
// clear. The test drives the model through a trampoline that samples ESP on both sides
// of it, so a reconstruction that pushed a word for the callee, or that failed to pop
// before transferring, shows up as an unbalanced frame.
//
// It is NOT asserted that the transfer is a JUMP rather than a CALL followed by a
// return, and the reason is stated in the .cpp: no C++ spelling forces the compiler to
// emit the jump (this package's own emitted code uses call+ret, because the function
// needs a frame for the position-independent thunk), and nothing outside the body can
// tell the two apart -- the callee's return reaches the body's caller either way and
// no memory of the body is touched after the transfer. What the machine's bytes fix is
// recorded in the .cpp's file header, not asserted here.
__attribute__((noinline)) void tail_trampoline(void* receiver, void* callee) {
  // ECX is in the clobber list, so the receiver cannot be allocated to it and the
  // `movl ..., %%ecx` really is the receiver.
  __asm__ __volatile__("movl %[recv], %%ecx\n\t"
                       "call *%[callee]\n\t"
                       :
                       : [recv] "r"(receiver), [callee] "r"(callee)
                       : "eax", "ecx", "memory");
}

void case_tail_arm_leaves_nothing_behind() {
  install_objects();
  g_obs.reset();
  g_obs.manager_result = manager_object();

  ReceiverBytes receiver = make_receiver(target_as_word(), owned_as_word());
  const void* target = reinterpret_cast<void*>(&re_00f99980);
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  g_active_receiver = &receiver;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [recv] "r"(static_cast<void*>(as_receiver(receiver))), [target] "r"(target)
                       : "eax", "ecx", "memory");
  g_active_receiver = nullptr;

  check(after == before, "T1: the tail arm consumed no stack word of its own");
  check(g_obs.log_is(kCallManager, kCallSlot, kCallNotify, kCallRelease),
        "T2: the tail arm made all four transfers, in order");
  check(g_obs.release_receiver == owned_object(),
        "T3: the object transferred is the one read at 0x00f999bc, not the zero just stored");
  check(g_obs.release_owned_word_seen == 0u, "T4: +0x894 was already zero at the transfer");
  check(word_of(receiver.bytes, kOwnedOffset) == 0u, "T5: +0x894 is zero afterwards");
  check(word_of(receiver.bytes, kTargetOffset) == 0xffffffffu, "T6: +0x8a4 is the sentinel afterwards");
  check(word_of(owned_object(), 0) == kOwnedPoison, "T7: the transferred object was not written");
  tail_trampoline(&g_objects.owned, reinterpret_cast<void*>(&owned_object_release_00690120));
  check(g_obs.release_return_address != nullptr, "T8: the release is callable with no stack word");
}

// The displacements and sizes the reconstruction states, against the listing's bytes.
void verify_machine_constants() {
  check(kLightingTargetDisplacement == 0x8a4u, "V1: the first receiver word is at +0x8a4");
  check(kRefCountedDisplacement == 0x894u, "V2: the second receiver word is at +0x894");
  check(kLightingSlotDisplacement == 0x7cu, "V3: the dispatched table word is at +0x7c");
  check(kLightingSlotDisplacement == 124u, "V4: 0x7c is 124 bytes, 31 whole dwords");
  check(kLightingTargetAbsent == 0xffffffffu, "V5: the sentinel is the unsigned form of -1");
  check(kReleaseNotificationArgument == 1u, "V6: the notify's argument is the literal 1");
  check(kObjectTableWordDisplacement == 0u, "V7: the table word is the manager's leading word");
  check(sizeof(Receiver) == 0x8a8u, "V8: the modelled receiver ends after the +0x8a4 word");
  check(kLightingTargetDisplacement + sizeof(Word) == sizeof(Receiver),
        "V9: 0x8a4 + 4 is the last byte the body writes");
  check(kRefCountedDisplacement != kLightingTargetDisplacement, "V10: the two words are distinct");
  check(kRefCountedDisplacement < kLightingTargetDisplacement,
        "V11: the lower word is the one read first (0x00f999a1 before 0x00f99983's field)");
}

}  // namespace

int main() {
  verify_machine_constants();
  case_nothing_to_do();
  case_dispatch_then_clear();
  case_full_run();
  case_notify_can_suppress_the_release();
  case_notify_can_replace_the_released_object();
  case_sentinel_test_is_exact();
  case_neighbouring_words_are_inert();
  case_target_is_passed_by_value();
  case_two_level_dispatch_at_a_byte_displacement();
  case_release_happens_after_the_clear();
  case_second_call_is_inert();
  case_stack_cleanup_is_measured();
  case_tail_arm_leaves_nothing_behind();
  case_guards_are_separate();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
