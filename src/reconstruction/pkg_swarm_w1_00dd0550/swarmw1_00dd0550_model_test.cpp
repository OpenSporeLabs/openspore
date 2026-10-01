// PKG-SWARM-W1-00DD0550 -- VA 0x00dd0550 -- model test
//
// A falsification test for re_00dd0550. Its job is to BREAK the
// reconstruction, not to walk it: every case below is a hypothesis that a
// plausible misreading of the 16-instruction body at 0x00dd0550..0x00dd0573
// would satisfy, and each case is built so that hypothesis produces a
// different observable than the machine's.
//
// The two direct callees are defined here as OBSERVERS, so the test sees every
// transfer, with which argument, in which order, and can decide what each one
// hands back:
//
//   root_slot_00b3d2a0  -- declared with no parameters, because its own two
//     instructions (MOV EAX,[0x0167eae4]; RET) read no register and no stack
//     slot. The observer therefore cannot even be handed a receiver, which is
//     how the model is held to not inventing one.
//   lookup_00ba6dc0     -- __thiscall, ECX receiver plus one callee-popped
//     stack word (its own `RET 0x4`), so the observer samples the receiver and
//     the stack argument separately, at the moment of the call.
//
// WHAT IS ASSERTED, in one line: which of the two branches was taken, whether
// the second call happened at all, WHICH OBJECT reached the second call as its
// receiver, WHICH 32-BIT WORD reached it as its argument, WHEN that word was
// read relative to the first call, and WHAT this body returned. Every one of
// those is fixed by an instruction in the listing.
//
// WHAT IS NOT ASSERTED, and why (stating this is part of the test, not an
// apology for it):
//
//  * Nothing about what the receiver's +0x80 word MEANS. The body only loads it,
//    tests it against zero and pushes it; the "packed index" reading comes from
//    0x00ba6dc0's body, which is a different function. No member name in the
//    model claims it, and the test asserts no semantics for it.
//  * Nothing about the concrete object 0x00b3d2a0 returns, or the global word
//    0x0167eae4 it reads. The test supplies its own pointer and asserts only
//    identity and null-ness.
//  * Nothing about 0x00ba6dc0's internals. It is a black box to this body, so
//    the harness dictates its return value and the test only checks that
//    whatever it dictates is what comes back out.
//  * Nothing about the receiver's bytes at any offset other than 0x80. The
//    harness cannot see a READ of 0x00 (a vtable word this listing never
//    touches), so a spurious read there is undetectable here. Writes ARE
//    detected: the receiver image is compared byte for byte after every case.
//  * Nothing about vtable slot identity or the owning class. The body has zero
//    direct callers and three DATA xrefs, so it is virtually dispatched, but the
//    listing performs no dispatch and the test asserts no slot.
//  * Nothing about register allocation beyond the argument surface. Which
//    scratch register held the key is not observable through this ABI and is
//    not claimed.
//
// MUTATION CHECK actually performed on this test. Each defect was injected into
// a copy of swarmw1_00dd0550.cpp, rebuilt with the same gate, and rerun. All
// fourteen were killed; none survived.
//
//   1  +0x80 read as +0x84                    KILLED  argument mismatch
//   2  +0x80 read as +0x7c                    KILLED  argument mismatch
//   3  second call handed THIS body's receiver KILLED  ECX identity
//   4  second call's argument/receiver swapped KILLED  ECX and argument
//   5  0x00dd055a branch polarity inverted     KILLED  31 checks
//   6  0x00dd0564 branch polarity inverted     KILLED  31 checks
//   7  key tested with signed <= 0, not == 0   KILLED  14 checks
//   8  key read hoisted ABOVE 0x00dd0553      KILLED  "the +0x80 word is read
//                                                       after 0x00dd0553, not
//                                                       before it"
//   9  key dereferenced (two-level read)       KILLED  reported by name, then
//                                                       faulted on a later case
//  10  null guard on the slot removed          KILLED  2 checks
//  11  zero test on the key removed            KILLED  29 checks
//  12  second call elided                      KILLED  29 checks
//  13  return 0 always                         KILLED at compile time (the
//                                                       reconstructed result
//                                                       becomes unused)
//  14  return the key, not the callee's EAX    KILLED at compile time (same)
//
// Cases 13 and 14 are caught by the compiler rather than by an assertion, which
// is worth stating plainly rather than counting as test strength: a model whose
// return value is discarded is rejected outright here, so no runtime check was
// needed to separate it.
//
// KNOWN LIMIT, stated rather than hidden: the "receiver is never written" and
// "the forwarded object is never written" checks are byte-comparisons, so they
// catch a spurious STORE and say nothing about a spurious READ. A model that
// read the receiver's +0x00 (the dispatch word of a virtually dispatched object,
// which this listing never touches) would pass every case here.

#include "swarmw1_00dd0550_types.hpp"

#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_00dd0550 {
namespace {

int g_failures = 0;

// Failures are reported on STDERR and flushed immediately, not on buffered
// stdout. That is not stylistic: a reconstruction that dereferences the key
// faults partway through the run, and a block-buffered stdout would lose every
// diagnosis accumulated before the fault, leaving only a bare SIGSEGV. Reporting
// unbuffered means the FIRST wrong observation survives and names itself.
void report(const char* text) {
  std::fprintf(stderr, "FAIL: %s\n", text);
  std::fflush(stderr);
  ++g_failures;
}

void expect(bool ok, const char* what) {
  if (!ok) {
    report(what);
  }
}

void expect_eq_u32(unsigned long long got, unsigned long long want, const char* what) {
  if (got != want) {
    char line[256];
    std::snprintf(line, sizeof(line), "%s -- got 0x%llx, listing says 0x%llx", what, got,
                  want);
    report(line);
  }
}

void expect_eq_ptr(const void* got, const void* want, const char* what) {
  if (got != want) {
    char line[256];
    std::snprintf(line, sizeof(line), "%s -- got %p, listing says %p", what, got, want);
    report(line);
  }
}

// -- the observable surface of one call ------------------------------------
struct Observation {
  unsigned root_slot_calls;        // 0x00dd0553 CALL 0x00b3d2a0
  unsigned lookup_calls;          // 0x00dd0569 CALL 0x00ba6dc0
  OpaqueStarTable* root_handed;   // what the first callee actually returned
  OpaqueStarTable* lookup_this;   // what arrived in ECX for the second call
  Word lookup_arg;                // what arrived on the stack for the second call
  Word lookup_ret;                // what the second callee returned

  // Test-controlled state.
  OpaqueStarTable* root_to_hand;  // the pointer 0x00b3d2a0 will return
  Word lookup_to_return;          // the value 0x00ba6dc0 will return

  // Ordering probe: armed, the first callee rewrites the receiver's +0x80 word
  // on its way out, so the second call's argument reveals WHEN the body read it.
  bool rewrite_armed;
  SporepediaOnlineReceiver* rewrite_target;
  Word rewrite_value;
};

Observation g_obs;

void reset_observation() { std::memset(&g_obs, 0, sizeof(g_obs)); }

// -- observers -------------------------------------------------------------

extern "C" OpaqueStarTable* PKG_SWARMW1_00DD0550_CDECL root_slot_00b3d2a0() {
  ++g_obs.root_slot_calls;
  g_obs.root_handed = g_obs.root_to_hand;
  if (g_obs.rewrite_armed) {
    g_obs.rewrite_armed = false;
    // The machine reads the receiver's +0x80 at 0x00dd055c, four instructions
    // AFTER this call at 0x00dd0553. Mutating the word here and asserting on
    // what the second call receives is what pins that ordering down.
    std::memcpy(reinterpret_cast<std::uint8_t*>(g_obs.rewrite_target) +
                    kReceiverKeyDisplacement,
                &g_obs.rewrite_value, sizeof(Word));
  }
  return g_obs.root_handed;
}

extern "C" Word PKG_SWARMW1_00DD0550_THISCALL lookup_00ba6dc0(OpaqueStarTable* receiver,
                                                              Word key) {
  ++g_obs.lookup_calls;
  g_obs.lookup_this = receiver;
  g_obs.lookup_arg = key;
  return g_obs.lookup_to_return;
}

// -- fixtures --------------------------------------------------------------
//
// 0x88 bytes: the modelled receiver is 0x84, and the extra four let a decoy sit
// at 0x84 -- the offset immediately AFTER the one the body reads, which is the
// decoy an off-by-one displacement would pick up instead.
struct ReceiverImage {
  std::uint8_t bytes[0x88];
};

struct RootImage {
  std::uint8_t bytes[0x40];
};

void poke(std::uint8_t* image, std::size_t displacement, Word value) {
  std::memcpy(image + displacement, &value, sizeof(value));
}

Word peek(const std::uint8_t* image, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, image + displacement, sizeof(value));
  return value;
}

// A receiver whose +0x80 holds `key` and whose two neighbouring words hold
// poison, so that reading 0x7c or 0x84 (or either half of the right word)
// produces something the assertions reject.
void build_receiver(ReceiverImage* image, Word key) {
  std::memset(image->bytes, 0xa5, sizeof(image->bytes));
  poke(image->bytes, 0x7c, 0xdec07cde);
  poke(image->bytes, 0x80, key);
  poke(image->bytes, 0x84, 0xdec084de);
}

SporepediaOnlineReceiver* as_receiver(ReceiverImage* image) {
  return reinterpret_cast<SporepediaOnlineReceiver*>(image->bytes);
}

OpaqueStarTable* as_root(RootImage* image) {
  return reinterpret_cast<OpaqueStarTable*>(image->bytes);
}

// The two constants planted at 0x7c and 0x84, as the model would see them if it
// read the wrong displacement.
constexpr Word kDecoyBefore = 0xdec07cde;
constexpr Word kDecoyAfter = 0xdec084de;

// A cell that the live cases point the receiver's +0x80 word AT. Those cases
// use a key that is a VALID readable address whose pointee holds a different
// number, which is what makes a two-level dereference of the key a REPORTED
// MISMATCH rather than a fault. The cases that use arbitrary literal keys, and
// would fault instead, all run after those.
Word g_key_cell = 0;

// =========================================================================
// CASE A -- the live path: identity of the receiver, identity of the
// argument, and the forwarded return value, all at once.
//
// The key is the ADDRESS of g_key_cell, whose contents are a different number.
// So one fixture separates three candidate readings of the same instruction:
// the correct one (the address), a two-level one (the cell's contents), and a
// wrong-width one (a halfword or byte of the field).
// =========================================================================
void case_a_live_path() {
  g_key_cell = 0x11223344;
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, reinterpret_cast<Word>(&g_key_cell));
  std::memset(root.bytes, 0x5a, sizeof(root.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);
  g_obs.lookup_to_return = 0xcafef00d;

  const Word result = re_00dd0550(as_receiver(&image));

  // 0x00dd0553 is unconditional, so it runs on every path.
  expect_eq_u32(g_obs.root_slot_calls, 1, "A: 0x00dd0553 runs exactly once");
  // 0x00dd0558 and 0x00dd0562 both pass, so 0x00dd0569 runs.
  expect_eq_u32(g_obs.lookup_calls, 1, "A: 0x00dd0569 runs once on the live path");

  // 0x00dd0567 MOV ECX,EAX -- the second call's `this` is the FIRST call's
  // return value. This is the fact a reconstruction gets wrong most easily,
  // because the decompilation's `FUN_00ba6dc0(*(int *)(param_1 + 0x80))` shape
  // invites passing the receiver.
  expect_eq_ptr(g_obs.lookup_this, as_root(&root),
                "A: 0x00dd0567 passes the FIRST call's return value as ECX");
  expect(reinterpret_cast<const void*>(g_obs.lookup_this) !=
             static_cast<const void*>(as_receiver(&image)),
         "A: the second call's receiver is not this body's receiver");

  // 0x00dd0566 PUSH EDX -- the argument is the receiver's +0x80 word itself,
  // read as a datum, at the displacement 0x00dd055c encodes.
  expect_eq_u32(g_obs.lookup_arg, reinterpret_cast<Word>(&g_key_cell),
                "A: 0x00dd0566 pushes the word at receiver + 0x80");
  expect(g_obs.lookup_arg != kDecoyBefore, "A: not the word at receiver + 0x7c");
  expect(g_obs.lookup_arg != kDecoyAfter, "A: not the word at receiver + 0x84");
  // Width, not just displacement: the field holds the little-endian bytes of
  // &g_key_cell, so a 16-bit read or an 8-bit read would yield the low half of
  // that address instead, and neither equals it.
  expect(g_obs.lookup_arg != 0x11223344,
         "A: the argument is not dereferenced (two-level read)");
  expect(g_obs.lookup_arg != 0x3344 && g_obs.lookup_arg != 0x44,
         "A: the +0x80 word is read at 32-bit width");

  // 0x00dd056e POP ESI / 0x00dd056f RET -- EAX is forwarded untouched.
  expect_eq_u32(result, 0xcafef00d, "A: 0x00ba6dc0's EAX is returned unchanged");
  expect(result != 0x11223344, "A: the return is not the argument");
  expect(result != 0, "A: the live path does not fall through to XOR EAX,EAX");
}

// =========================================================================
// CASE B -- pointer level. The argument is a VALUE, so a model that treats
// receiver + 0x80 as a pointer to dereference lands somewhere else entirely.
// Here the key is the ADDRESS of a word holding a different number, which is
// the decoy: the value that must arrive is the address, not what it points at.
// =========================================================================
void case_b_pointer_level() {
  Word pointee = 0x0badbad0;
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, reinterpret_cast<Word>(&pointee));
  std::memset(root.bytes, 0x5a, sizeof(root.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);
  g_obs.lookup_to_return = 0x11110000;

  const Word result = re_00dd0550(as_receiver(&image));

  expect_eq_ptr(g_obs.lookup_this, as_root(&root), "B: ECX still the first call's result");
  expect_eq_u32(g_obs.lookup_arg, reinterpret_cast<Word>(&pointee),
                "B: the word AT +0x80 is passed, not the word it points to");
  expect(g_obs.lookup_arg != 0x0badbad0, "B: the argument is not dereferenced");
  expect_eq_u32(result, 0x11110000, "B: the callee's return is forwarded");
}

// =========================================================================
// CASE C -- the body must not touch the object it forwards. 0x00dd0567 only
// moves it into ECX; nothing in the listing reads or writes through it. The
// root object's bytes are compared before and after.
// =========================================================================
void case_c_root_is_not_dereferenced() {
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, 0x0f0f0f0f);
  std::memset(root.bytes, 0x33, sizeof(root.bytes));
  std::uint8_t before[sizeof(root.bytes)];
  std::memcpy(before, root.bytes, sizeof(root.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);
  g_obs.lookup_to_return = 0x0000beef;

  const Word result = re_00dd0550(as_receiver(&image));

  expect(std::memcmp(before, root.bytes, sizeof(root.bytes)) == 0,
         "C: the forwarded object is never written through");
  expect_eq_ptr(g_obs.lookup_this, as_root(&root), "C: ECX is the object itself");
  expect_eq_u32(result, 0x0000beef, "C: return forwarded");
}

// =========================================================================
// CASE D -- the receiver is never written. receiver.written_through is 0 in
// the machine record and the listing has no store through ESI.
// =========================================================================
void case_d_receiver_is_not_written() {
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, 0x7a7a7a7a);
  std::memset(root.bytes, 0x5a, sizeof(root.bytes));
  std::uint8_t before[sizeof(image.bytes)];
  std::memcpy(before, image.bytes, sizeof(image.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);
  g_obs.lookup_to_return = 0x01020304;

  (void)re_00dd0550(as_receiver(&image));

  expect(std::memcmp(before, image.bytes, sizeof(image.bytes)) == 0,
         "D: no byte of the receiver is modified, on the live path");
}

// =========================================================================
// CASE E -- branch polarity, arm 1: 0x00dd0558 TEST EAX,EAX / JZ. A null from
// 0x00b3d2a0 must reach 0x00dd0570 and must NOT reach 0x00dd0569, even with a
// perfectly good non-zero key sitting at +0x80. A model with the branch
// inverted, or one that calls the second callee before testing, fails here.
// =========================================================================
void case_e_null_root() {
  ReceiverImage image;
  build_receiver(&image, 0xdeadbeef);

  reset_observation();
  g_obs.root_to_hand = nullptr;      // 0x00b3d2a0 returns 0
  g_obs.lookup_to_return = 0xcafef00d;

  const Word result = re_00dd0550(as_receiver(&image));

  expect_eq_u32(result, 0, "E: 0x00dd0570 returns 0 when the slot is null");
  expect_eq_u32(g_obs.lookup_calls, 0, "E: 0x00dd0569 is not reached when slot is null");
  expect_eq_u32(g_obs.root_slot_calls, 1, "E: the first call still ran");
}

// =========================================================================
// CASE F -- branch polarity, arm 2: 0x00dd0562 TEST EDX,EDX / JZ. A zero key
// must reach 0x00dd0570 with a NON-null slot behind it, so the two arms are
// distinguished by which test fires.
// =========================================================================
void case_f_zero_key() {
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, 0x00000000);
  std::memset(root.bytes, 0x5a, sizeof(root.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);   // slot is NOT null
  g_obs.lookup_to_return = 0xcafef00d;

  const Word result = re_00dd0550(as_receiver(&image));

  expect_eq_u32(result, 0, "F: a zero key returns 0");
  expect_eq_u32(g_obs.lookup_calls, 0, "F: a zero key does not reach 0x00dd0569");
  expect_eq_u32(g_obs.root_slot_calls, 1, "F: the first call still ran");
  // The decoys stay poisoned, proving the zero test is on +0x80 and not on a
  // neighbour: if the test read 0x7c or 0x84 it would have seen a non-zero word
  // and taken the live path.
  expect_eq_u32(peek(image.bytes, 0x7c), kDecoyBefore, "F: +0x7c decoy intact");
  expect_eq_u32(peek(image.bytes, 0x84), kDecoyAfter, "F: +0x84 decoy intact");
}

// =========================================================================
// CASE G -- both tests fail at once: still 0, still no second call.
// =========================================================================
void case_g_both_null() {
  ReceiverImage image;
  build_receiver(&image, 0);

  reset_observation();
  g_obs.root_to_hand = nullptr;
  g_obs.lookup_to_return = 0xcafef00d;

  const Word result = re_00dd0550(as_receiver(&image));

  expect_eq_u32(result, 0, "G: both arms zero give 0");
  expect_eq_u32(g_obs.lookup_calls, 0, "G: no second call");
  expect_eq_u32(g_obs.root_slot_calls, 1, "G: the first call is unconditional");
}

// =========================================================================
// CASE H -- SIGNED vs UNSIGNED. 0x00dd0562 is TEST EDX,EDX with JZ, so only
// ZF is read and a key with the top bit set is NOT "negative". 0xffffffff is
// also the -1 sentinel 0x00ba6dc0 tests for internally, which is precisely the
// value a signed reading would mishandle: a model that guards `key < 0` or
// `(int)key <= 0` would skip the call, and a model that special-cased -1 would
// return 0. The listing does neither.
// =========================================================================
void case_h_signedness_of_the_zero_test() {
  const Word keys[4] = {0xffffffffu, 0x80000000u, 0x80000001u, 0x7fffffffu};
  for (Word key : keys) {
    ReceiverImage image;
    RootImage root;
    build_receiver(&image, key);
    std::memset(root.bytes, 0x5a, sizeof(root.bytes));

    reset_observation();
    g_obs.root_to_hand = as_root(&root);
    g_obs.lookup_to_return = 0x0f0f0f0f;

    const Word result = re_00dd0550(as_receiver(&image));

    char label[96];
    const unsigned long long widened = key;
    std::snprintf(label, sizeof(label),
                  "H: key 0x%08llx is non-zero, so the live path is taken", widened);
    expect_eq_u32(g_obs.lookup_calls, 1, label);
    std::snprintf(label, sizeof(label),
                  "H: key 0x%08llx reaches the call verbatim", widened);
    expect_eq_u32(g_obs.lookup_arg, key, label);
    std::snprintf(label, sizeof(label),
                  "H: key 0x%08llx forwards the callee's EAX", widened);
    expect_eq_u32(result, 0x0f0f0f0f, label);
  }
}

// =========================================================================
// CASE I -- WRITE / READ ORDERING. 0x00dd055c is four instructions after
// 0x00dd0553, so the +0x80 word is read AFTER the first call has run and had
// its chance to change it. The first callee rewrites the word on its way out;
// what the second call receives is the rewritten value. A model that hoisted
// the read above the first call -- a natural thing to do when the two are on
// different branches -- would pass the stale value and fail this.
// =========================================================================
void case_i_read_happens_after_the_first_call() {
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, 0x11110000);          // the value present at entry
  std::memset(root.bytes, 0x5a, sizeof(root.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);
  g_obs.lookup_to_return = 0x22223333;
  g_obs.rewrite_armed = true;
  g_obs.rewrite_target = as_receiver(&image);
  g_obs.rewrite_value = 0x99998888;            // what the first callee leaves

  const Word result = re_00dd0550(as_receiver(&image));

  expect_eq_u32(g_obs.lookup_arg, 0x99998888,
                "I: the +0x80 word is read after 0x00dd0553, not before it");
  expect(g_obs.lookup_arg != 0x11110000,
         "I: the pre-call value is not what the second call receives");
  expect_eq_u32(result, 0x22223333, "I: the callee's EAX is forwarded");
}

// =========================================================================
// CASE J -- the same ordering question from the other side: with nothing
// rewriting the word, the entry value is what arrives. Together with CASE I
// this says the read is late but not arbitrary.
// =========================================================================
void case_j_unrewritten_key_is_the_entry_value() {
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, 0x0a0b0c0d);
  std::memset(root.bytes, 0x5a, sizeof(root.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);
  g_obs.lookup_to_return = 0x44445555;

  (void)re_00dd0550(as_receiver(&image));

  expect_eq_u32(g_obs.lookup_arg, 0x0a0b0c0d,
                "J: with no rewrite the entry value at +0x80 is the argument");
}

// =========================================================================
// CASE K -- CALL COUNT. Both exits converge on 0x00dd0570 and there is no loop
// in the body, so the second call can happen at most once per invocation and the
// first call exactly once. This is what a model that looped, or that called
// 0x00b3d2a0 again to re-test, would break.
// =========================================================================
void case_k_exactly_one_second_call() {
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, 0x0b0b0b0b);
  std::memset(root.bytes, 0x5a, sizeof(root.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);
  g_obs.lookup_to_return = 0x56567777;

  (void)re_00dd0550(as_receiver(&image));

  expect_eq_u32(g_obs.lookup_calls, 1, "K: the second call happens exactly once");
  expect_eq_u32(g_obs.root_slot_calls, 1, "K: the first call happens exactly once");
}

// =========================================================================
// CASE L -- the return is not manufactured. A model that returned 0, or that
// returned the key, or that returned the forwarded pointer, is separated from
// the real one here by making the three candidates three different values.
// =========================================================================
void case_l_return_is_the_callees_value() {
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, 0x13572468);
  std::memset(root.bytes, 0x5a, sizeof(root.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);
  g_obs.lookup_to_return = 0x24681357;   // 0, the key and the pointer all differ

  const Word result = re_00dd0550(as_receiver(&image));

  expect_eq_u32(result, 0x24681357, "L: the return is exactly 0x00ba6dc0's EAX");
  expect(result != 0x13572468, "L: the return is not the key");
  expect(result != 0, "L: the return is not 0 on the live path");
  expect(reinterpret_cast<std::uintptr_t>(g_obs.lookup_this) != result,
         "L: the return is not the forwarded pointer");
}

// =========================================================================
// CASE N -- a key that is emphatically NOT a pointer, and it runs LAST.
//
// 0x11223344 is not a mapped address, so a reconstruction that dereferenced the
// key would fault on it. Later cases (C, D, F, H, I, J, K, L) likewise use
// arbitrary literal keys and would fault too, which is why the two
// DEREFERENCEABLE-key cases -- case_b_pointer_level and case_a_live_path -- are
// the first two the harness runs. By the time any fault is possible, a
// two-level dereference of the key has already been reported by name, and the
// unbuffered stderr reporting above guarantees that report survives the fault
// rather than being lost with the stdout buffer. This case pins the last
// machine fact the earlier ones do not: a key with no pointer interpretation at
// all still travels to 0x00ba6dc0 verbatim.
// =========================================================================
void case_n_non_pointer_key() {
  ReceiverImage image;
  RootImage root;
  build_receiver(&image, 0x11223344);
  std::memset(root.bytes, 0x5a, sizeof(root.bytes));

  reset_observation();
  g_obs.root_to_hand = as_root(&root);
  g_obs.lookup_to_return = 0x0badc0de;

  const Word result = re_00dd0550(as_receiver(&image));

  expect_eq_u32(g_obs.lookup_arg, 0x11223344,
                "N: an arbitrary non-pointer word is forwarded verbatim");
  expect_eq_u32(result, 0x0badc0de, "N: the callee's EAX is forwarded");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w1_00dd0550

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w1_00dd0550;

  // ORDER IS DELIBERATE. case_b_pointer_level runs first because it is the only
  // case whose +0x80 word is a DEREFERENCEABLE address. A reconstruction that
  // treats the key as a pointer and reads through it therefore reports a value
  // mismatch here -- "the word AT +0x80 is passed, not the word it points to" --
  // instead of faulting on the arbitrary key 0x11223344 that the later cases
  // use. Both outcomes fail the test; this ordering makes the failure legible.
  case_b_pointer_level();
  case_a_live_path();
  case_c_root_is_not_dereferenced();
  case_d_receiver_is_not_written();
  case_e_null_root();
  case_f_zero_key();
  case_g_both_null();
  case_h_signedness_of_the_zero_test();
  case_i_read_happens_after_the_first_call();
  case_j_unrewritten_key_is_the_entry_value();
  case_k_exactly_one_second_call();
  case_l_return_is_the_callees_value();
  case_n_non_pointer_key();

  if (g_failures != 0) {
    std::printf("%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("all model checks passed\n");
  return 0;
}
