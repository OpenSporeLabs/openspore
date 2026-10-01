// PKG-DFW-009817C0 -- VA 0x009817c0
// Behavioural model test for the body the queue record names
// UTFWin::ScrollbarDrawable::SetImage.
//
// One extern callee is owned by this test: 0x00951240, the target of the JMP at
// 0x009817d6. It is defined below as an observer that records the receiver and
// the key it was handed, and that either returns a chosen word or computes its
// OWN transcribed table, so this test can see the delegation happen, check what
// was delegated, and check the composed result for a key the target does not
// answer itself.
//
// What is asserted here is what the 17-instruction listing fixes, and nothing
// beyond it:
//
//   * which transfers exist -- the JMP at 0x009817d6 is the only one, and the two
//     locally handled keys must NOT reach it;
//   * their order -- the argument is read and compared before the delegate runs,
//     and the delegate runs last;
//   * which base adjustments are formed -- receiver + 4 and receiver + 12, and no
//     others;
//   * which branch each input takes, at each constant and at constant +/- 1;
//   * the return word on every path, including the two null-guard paths and the
//     delegated path;
//   * that the receiver is never written.
//
// What is NOT asserted, because no record for this target supports it: that the
// key is a hash, what any member at +0x04 or +0x0c is, what class owns this
// address, or what the SDK symbol "SetImage" has to do with any of it.
//
// The second-order tests are the differential one: a deliberately flat
// transcription of the same listing, sharing no helper and no control structure
// with the model, driven over the same inputs.

#include "dfw_009817c0_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_dfw_009817c0 {

// The model is only meaningful at the widths the record states: a 4-byte
// pointer (the record's own return type is void*) and a 4-byte key (the record's
// own argument type is uint32_t at entry_ESP+0x4). Asserted here so a host that
// is not the x86-32 target fails at compile time instead of silently modelling
// a different layout.
static_assert(sizeof(void*) == 4, "the record's return type void* presumes a 4-byte pointer");
static_assert(sizeof(Word) == 4, "the record's argument type uint32_t is a 4-byte word");

// 0x009817c0, defined in the package's own translation unit. The header declares
// it, and the declaration is repeated here with the same portable
// calling-convention spelling so this test does not depend on the header alone.
PKG_DFW_009817C0_MODEL_BEGIN
extern "C" void* PKG_DFW_009817C0_THISCALL dfw_009817c0_SetImage(void* receiver, Word key);

namespace {

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// 0x00951240, the one direct transfer out of this body (JMP at 0x009817d6).
// Whether the listing's "direct transfer" or the xref export's "direct-call", the
// two machine sources name the same single target.
struct DelegateObservation {
  int calls = 0;
  void *receiver = nullptr;
  Word key = 0;
  // When true the observer computes the table transcribed from 0x00951240's own
  // listing, so the composed result can be checked. When false it returns
  // `chosen_result` verbatim, which makes the pass-through of the delegate's
  // return word observable and the delegated paths trivially distinguishable
  // from the two local ones.
  bool use_transcribed_table = true;
  void *chosen_result = nullptr;
};

DelegateObservation g_delegate;

// A receiver the model may form receiver + 12 of, and never write through.
// Deliberately not zero-filled, so an invented store to it is visible.
struct Receiver {
  unsigned char bytes[64];
};

void *at_offset(void *base, std::size_t displacement) {
  return static_cast<unsigned char *>(base) + displacement;
}

}  // namespace

// 0x00951240 -- observer for the JMP at 0x009817d6.
//
// The table below is a transcription of that address's live 16-instruction
// listing, not an invention, and it is deliberately not the same shape as the
// model's:
//
//   0x6ec581fd -> the bare receiver, reached with NO null guard at all
//                  (0x0095124c JZ targets the RET at 0x0095126e directly, skipping
//                  every TEST), so a null receiver yields null there by accident
//                  of the value rather than by a decision;
//   0xee3f516e -> receiver + 4, guarded by TEST EAX,EAX (0x00951268);
//   0xeec58382 -> receiver + 4, guarded by TEST EAX,EAX (0x0095125e) -- a key this
//                  package's own target answers before it can ever delegate;
//   anything else -> 0 (XOR EAX,EAX at 0x0095126c).
extern "C" void* PKG_DFW_009817C0_THISCALL dfw_009817c0_resolve_00951240(void*receiver, Word key) {
  ++g_delegate.calls;
  g_delegate.receiver = receiver;
  g_delegate.key = key;

  if (!g_delegate.use_transcribed_table) {
    return g_delegate.chosen_result;
  }
  if (key == 0x6ec581fdu) {
    return receiver;
  }
  if (key == 0xee3f516eu || key == 0xeec58382u) {
    return receiver != nullptr ? at_offset(receiver, 4) : nullptr;
  }
  return nullptr;
}
PKG_DFW_009817C0_MODEL_END

namespace {

// 0x009817c4 / 0x009817c9: the first key, and the arm at 0x009817e5 that leaves
// the comparison chain for it. Non-null receiver -> 0x009817e9 LEA EAX,[ECX+0x4]
// then 0x009817ec RET 0x4.
void test_local_key_returns_receiver_plus_four() {
  Receiver receiver;
  for (std::size_t index = 0; index < sizeof receiver.bytes; ++index) {
    receiver.bytes[index] = static_cast<unsigned char>(0xa0u + index);
  }
  g_delegate = DelegateObservation{};

  void *const got = dfw_009817c0_SetImage(receiver.bytes, kKeyLocalPlus4);

  check(got == at_offset(receiver.bytes, 4),
        "key 0xeec58382 with a live receiver returns the address receiver + 4");
  check(g_delegate.calls == 0,
        "key 0xeec58382 is answered locally and never reaches the JMP at 0x009817d6");
}

// 0x009817cb / 0x009817d0: the second key, the arm at 0x009817db, and
// 0x009817df LEA EAX,[ECX+0xc] then 0x009817e2 RET 0x4.
void test_local_key_returns_receiver_plus_twelve() {
  Receiver receiver;
  for (std::size_t index = 0; index < sizeof receiver.bytes; ++index) {
    receiver.bytes[index] = static_cast<unsigned char>(0x10u + index);
  }
  g_delegate = DelegateObservation{};

  void *const got = dfw_009817c0_SetImage(receiver.bytes, kKeyLocalPlus12);

  check(got == at_offset(receiver.bytes, 12),
        "key 0xeef3af8c with a live receiver returns the address receiver + 12");
  check(g_delegate.calls == 0,
        "key 0xeef3af8c is answered locally and never reaches the JMP at 0x009817d6");
}

// 0x009817e5 / 0x009817e7 and 0x009817db / 0x009817dd: both arms null-guard the
// receiver, and both guards land on the same 0x009817ef XOR EAX,EAX / 0x009817f1
// RET 0x4. Without the guard the +0x04 arm would return 0x00000004 for a null
// receiver, which is the specific thing this test rules out.
void test_null_receiver_is_null_on_both_local_keys() {
  g_delegate = DelegateObservation{};

  void *const plus_four = dfw_009817c0_SetImage(nullptr, kKeyLocalPlus4);
  void *const plus_twelve = dfw_009817c0_SetImage(nullptr, kKeyLocalPlus12);

  check(plus_four == nullptr,
        "a null receiver on the 0xeec58382 arm returns null, not the address 4");
  check(plus_twelve == nullptr,
        "a null receiver on the 0xeef3af8c arm returns null, not the address 12");
  check(g_delegate.calls == 0,
        "a null receiver on a locally handled key still does not delegate");
}

// 0x009817d2 / 0x009817d6: everything else. The delegate must run exactly once,
// must receive the receiver through ECX and the key through the single stack word
// at entry_ESP+0x4, and its return word is what this body returns.
void test_unknown_key_delegates_with_the_same_receiver_and_key() {
  Receiver receiver;
  std::memset(receiver.bytes, 0x5a, sizeof receiver.bytes);
  g_delegate = DelegateObservation{};
  g_delegate.use_transcribed_table = false;
  g_delegate.chosen_result = reinterpret_cast<void *>(static_cast<std::uintptr_t>(0xfeedfaceu));

  void *const got = dfw_009817c0_SetImage(receiver.bytes, 0x12345678u);

  check(g_delegate.calls == 1, "an unhandled key reaches the JMP at 0x009817d6 exactly once");
  check(g_delegate.receiver == receiver.bytes,
        "the delegate receives the receiver unchanged, still in ECX");
  check(g_delegate.key == 0x12345678u,
        "the delegate receives the key unchanged, at its own entry_ESP + 0x4");
  check(got == g_delegate.chosen_result,
        "the delegate's return word is the word this body returns");
}

// The branch boundaries, at each of the two constants and at constant -/+ 1. An
// off-by-one in either CMP immediate would survive a random sweep, so the
// neighbours are checked directly. 0x009817d0's arm is the one that moves from
// 0x009817db to 0x009817df, and 0x009817c9's is the one that moves from 0x009817e5
// to 0x009817e9, so both ends of both comparisons are pinned.
void test_branch_boundaries_at_each_constant() {
  Receiver receiver;
  g_delegate = DelegateObservation{};

  struct Case {
    Word key;
    void *expected;
    const char *what;
  };

  const Case cases[] = {
      {kKeyLocalPlus4 - 1u, nullptr, "0xeec58381 is not the 0xeec58382 arm"},
      {kKeyLocalPlus4, at_offset(receiver.bytes, 4), "0xeec58382 is the 0xeec58382 arm"},
      {kKeyLocalPlus4 + 1u, nullptr, "0xeec58383 is not the 0xeec58382 arm"},
      {kKeyLocalPlus12 - 1u, nullptr, "0xeef3af8b is not the 0xeef3af8c arm"},
      {kKeyLocalPlus12, at_offset(receiver.bytes, 12), "0xeef3af8c is the 0xeef3af8c arm"},
      {kKeyLocalPlus12 + 1u, nullptr, "0xeef3af8d is not the 0xeef3af8c arm"},
      {0u, nullptr, "key 0 is delegated and 0x00951240 answers 0 for it"},
      {0xffffffffu, nullptr, "key 0xffffffff is delegated and 0x00951240 answers 0 for it"},
  };

  for (const Case &entry : cases) {
    g_delegate = DelegateObservation{};
    void *const got = dfw_009817c0_SetImage(receiver.bytes, entry.key);
    check(got == entry.expected, entry.what);
    // Only the two constants may avoid the delegate.
    const bool handled_locally = entry.key == kKeyLocalPlus4 || entry.key == kKeyLocalPlus12;
    check(g_delegate.calls == (handled_locally ? 0 : 1),
          "exactly the two local keys skip the delegate, and no other key does");
  }
}

// 0x00951240's own table, driven through this package's entry point. This is the
// only place the composed behaviour is visible, because 0x6ec581fd and 0xee3f516e
// exist nowhere in the 0x009817c0 body -- they can only be reached by delegation.
//
// The 0x6ec581fd case is the interesting one: 0x0095124c branches straight to its
// RET with no TEST at all, so it returns the receiver verbatim INCLUDING when the
// receiver is null. Every other arm is guarded. The asymmetry is reproduced here
// deliberately, because a model that "helpfully" guarded it would be wrong.
void test_delegated_keys_reach_the_sibling_table() {
  Receiver receiver;
  std::memset(receiver.bytes, 0x33, sizeof receiver.bytes);

  g_delegate = DelegateObservation{};
  void *const bare = dfw_009817c0_SetImage(receiver.bytes, 0x6ec581fdu);
  check(g_delegate.calls == 1, "key 0x6ec581fd is delegated");
  check(bare == receiver.bytes, "0x6ec581fd resolves to the bare receiver, with no offset");

  g_delegate = DelegateObservation{};
  void *const plus_four = dfw_009817c0_SetImage(receiver.bytes, 0xee3f516eu);
  check(plus_four == at_offset(receiver.bytes, 4), "0xee3f516e resolves to the receiver + 4");

  g_delegate = DelegateObservation{};
  void *const null_bare = dfw_009817c0_SetImage(nullptr, 0x6ec581fdu);
  check(null_bare == nullptr,
        "0x6ec581fd with a null receiver returns null -- unguarded, but the value is zero");

  g_delegate = DelegateObservation{};
  void *const null_plus_four = dfw_009817c0_SetImage(nullptr, 0xee3f516eu);
  check(null_plus_four == nullptr, "0xee3f516e with a null receiver returns null by its own guard");

  // 0xeec58382 is in BOTH tables with the same answer. Reached through this
  // entry point it is answered locally, so the delegate must not run -- which is
  // exactly what makes it a test that the local arm precedes the tail call.
  g_delegate = DelegateObservation{};
  void *const local_wins = dfw_009817c0_SetImage(receiver.bytes, kKeyLocalPlus4);
  check(local_wins == at_offset(receiver.bytes, 4) && g_delegate.calls == 0,
        "0xeec58382 agrees in both tables and the local arm is the one that runs");
}

// The body forms two base adjustments and dereferences neither. Across every key
// and both receiver states, the receiver's bytes must be byte-identical
// afterwards. This is the check that fails on an invented store.
//
// Honest limit: a store that wrote back the value it had just read would leave
// the bytes identical and so pass here. The one store in this body,
// MOV dword ptr [ESP + 0x4],EAX at 0x009817d2, is exactly such a store and it
// targets the caller's argument slot rather than the receiver, so it is not
// observable through this interface and is not claimed to be excluded here. Every
// store that changes a byte of the receiver is excluded.
void test_the_receiver_is_never_written() {
  Receiver receiver;
  unsigned char before[sizeof receiver.bytes];

  const Word keys[] = {kKeyLocalPlus4, kKeyLocalPlus12, 0x6ec581fdu, 0xee3f516eu, 0u, 0xffffffffu};

  for (std::size_t index = 0; index < sizeof receiver.bytes; ++index) {
    receiver.bytes[index] = static_cast<unsigned char>(0x70u + index);
  }
  std::memcpy(before, receiver.bytes, sizeof before);
  for (Word key : keys) {
    g_delegate = DelegateObservation{};
    dfw_009817c0_SetImage(receiver.bytes, key);
    check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
          "no byte of the receiver changes on any key, with a live receiver");
  }

  for (Word key : keys) {
    g_delegate = DelegateObservation{};
    dfw_009817c0_SetImage(nullptr, key);
    check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
          "the null-receiver path touches no memory at all");
  }
}

// A second, deliberately flat transcription of the same 17 instructions. It
// shares no helper and no control structure with the model: a switch over the two
// keys, one guarded return, and a single delegation point.
//
// What this does and does not buy, stated plainly: it checks that the MODEL'S
// control structure reproduces the listing -- the two keys, the two null guards,
// the two displacements, the single delegation. It is NOT an independent oracle,
// because it reads the same listing; a misreading of the listing would be made
// twice and this test would not see it.
void *flat_transcription(void *receiver, Word key) {
  void *result = nullptr;
  bool delegate = false;
  switch (key) {
    case 0xeec58382u:
      if (receiver != nullptr) {
        result = at_offset(receiver, 4);
      }
      break;
    case 0xeef3af8cu:
      if (receiver != nullptr) {
        result = at_offset(receiver, 12);
      }
      break;
    default:
      delegate = true;
      break;
  }
  return delegate ? dfw_009817c0_resolve_00951240(receiver, key) : result;
}

void test_differential_against_flat_transcription() {
  Receiver receiver;
  std::memset(receiver.bytes, 0xc3, sizeof receiver.bytes);

  Word keys[64];
  std::size_t count = 0;
  const Word pinned[] = {
      0u,
      1u,
      0x6ec581fcu,
      0x6ec581fdu,
      0x6ec581feu,
      0x009817c0u,
      0xdeadbeefu,
      0xeec58381u,
      kKeyLocalPlus4,
      kKeyLocalPlus4 + 1u,
      0xeef3af8bu,
      kKeyLocalPlus12,
      kKeyLocalPlus12 + 1u,
      0xee3f516du,
      0xee3f516eu,
      0xee3f516fu,
      0x7fffffffu,
      0x80000000u,
      0xfffffffeu,
      0xffffffffu,
  };
  for (Word key : pinned) {
    keys[count++] = key;
  }
  // A fixed odd-stepped sweep, so a difference in any single key is caught and
  // the test is not dependent on a random source.
  Word candidate = 0x00000011u;
  for (std::size_t index = 0; index < 44; ++index) {
    keys[count++] = candidate;
    candidate = candidate * 1664525u + 1013904223u;
  }

  void *const receivers[2] = {receiver.bytes, nullptr};
  void *const sentinels[2] = {
      reinterpret_cast<void *>(static_cast<std::uintptr_t>(0x0badc0deu)),
      reinterpret_cast<void *>(static_cast<std::uintptr_t>(0x0badc0deu)),
  };

  for (int chosen = 0; chosen < 2; ++chosen) {
    for (int which = 0; which < 2; ++which) {
      for (std::size_t index = 0; index < count; ++index) {
        g_delegate = DelegateObservation{};
        g_delegate.use_transcribed_table = (chosen == 0);
        g_delegate.chosen_result = sentinels[which];
        void *const from_model = dfw_009817c0_SetImage(receivers[which], keys[index]);
        const int model_calls = g_delegate.calls;
        void *const model_receiver = g_delegate.receiver;
        const Word model_key = g_delegate.key;

        g_delegate = DelegateObservation{};
        g_delegate.use_transcribed_table = (chosen == 0);
        g_delegate.chosen_result = sentinels[which];
        void *const from_flat = flat_transcription(receivers[which], keys[index]);

        check(from_model == from_flat, "the model and the flat transcription agree on the result");
        check(model_calls == g_delegate.calls,
              "the model and the flat transcription delegate the same number of times");
        check(model_receiver == g_delegate.receiver && model_key == g_delegate.key,
              "the model and the flat transcription delegate the same receiver and key");
      }
    }
  }
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_009817c0

int main() {
  using namespace openspore::reconstruction::pkg_dfw_009817c0;
  test_local_key_returns_receiver_plus_four();
  test_local_key_returns_receiver_plus_twelve();
  test_null_receiver_is_null_on_both_local_keys();
  test_unknown_key_delegates_with_the_same_receiver_and_key();
  test_branch_boundaries_at_each_constant();
  test_delegated_keys_reach_the_sibling_table();
  test_the_receiver_is_never_written();
  test_differential_against_flat_transcription();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
