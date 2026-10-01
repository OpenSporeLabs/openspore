// PKG-SPOREPEDIA-OWNED-SLOT-NOTIFY -- VA 0x00ec3bc0
// Behavioural model test for FUN_00ec3bc0.
//
// The two direct callees -- 0x00641e10 at 0x00ec3bc3 and 0x00eec760 at
// 0x00ec3bd4 -- are defined here as observers, so this test sees the calls the
// reconstruction makes and gets to decide what the receiver's word at
// displacement 0x20 holds at each point.
//
// The assertions are the claims the machine listing makes and nothing more: the
// two transfers, the order they happen in, the single displacement read at
// 0x00ec3bc8, the base adjustment to receiver+0x80 at 0x00ec3bcf, the branch
// that skips the whole block when the word is zero, and the word the body
// leaves in EAX on each of the two paths. Nothing here asserts what either
// callee does internally, or what the word points at.

#include "sporepedia_owned_slot_notify_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_sporepedia_owned_slot_notify {

// 0x00ec3bc0, defined in the package's own translation unit. The header declares
// only the two callees, so the reconstructed body is declared here with the same
// portable calling-convention spelling the package uses.
extern "C" unclassified_in_EAX PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_THISCALL
sporepedia_owned_slot_notify_FUN_00ec3bc0(void *receiver);

namespace {

// Machine displacements, not names: 0x20 is the only receiver word the body
// reads, 0x80 is the base adjustment it adds before handing an address over.
constexpr std::size_t kOwnedWordOffset = 0x20u;
constexpr std::size_t kBoundsBaseAdjustment = 0x80u;

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

struct Observation {
  int release_calls = 0;
  const void *release_receiver = nullptr;
  int fill_calls = 0;
  OpaqueOwnedBlock *fill_object = nullptr;
  BoundsWords *fill_bounds = nullptr;
  // When set, the modelled 0x00641e10 plants a non-null word into the receiver
  // before returning. That is what lets this test tell a read that happens after
  // 0x00ec3bc3 from one that does not.
  bool release_writes_non_null = false;
  unclassified_in_EAX fill_result = 0u;
};

Observation g_obs;

// A receiver large enough for the word at 0x20 and for the three words the
// second callee is handed at +0x80. Zero-filled, so a word nobody plants reads
// as null -- which is the state the listing's JZ at 0x00ec3bcd tests for.
struct Receiver {
  unsigned char bytes[256] = {};
};

// Plants a non-null word at the displacement the body reads.
void plant_owned_word(Receiver &receiver, OpaqueOwnedBlock *value) {
  std::memcpy(receiver.bytes + kOwnedWordOffset, &value, sizeof value);
}

}  // namespace

// 0x00ec3bc3 -- the first direct transfer. Nothing is pushed and the receiver
// arrives in ECX, so the observer records the pointer it was handed.
extern "C" unclassified_in_EAX PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_THISCALL
slot_release_00641e10(void *receiver) {
  ++g_obs.release_calls;
  g_obs.release_receiver = receiver;
  if (g_obs.release_writes_non_null) {
    OpaqueOwnedBlock *const planted = &g_obs;  // any distinguishable non-null word
    std::memcpy(static_cast<unsigned char *>(receiver) + kOwnedWordOffset,
                &planted, sizeof planted);
  }
  return 0u;
}

// 0x00ec3bd4 -- the second direct transfer, taking the pair pushed at
// 0x00ec3bd2/0x00ec3bd3. Its return word is what the body leaves in EAX.
extern "C" unclassified_in_EAX PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_CDECL
sporepedia_bounds_fill_00eec760(OpaqueOwnedBlock *object, BoundsWords *bounds) {
  ++g_obs.fill_calls;
  g_obs.fill_object = object;
  g_obs.fill_bounds = bounds;
  return g_obs.fill_result;
}

namespace {

// The word is zero on entry, so the JZ at 0x00ec3bcd is taken: the whole block
// is skipped, the second transfer never happens, and the body still pops ESI
// and returns with the zero word in EAX.
void test_zero_word_takes_the_early_tail() {
  Receiver receiver;
  g_obs = Observation{};

  const unclassified_in_EAX got =
      sporepedia_owned_slot_notify_FUN_00ec3bc0(receiver.bytes);

  check(g_obs.release_calls == 1, "0x00ec3bc3 runs exactly once");
  check(g_obs.release_receiver == receiver.bytes,
        "0x00ec3bc3 receives the receiver through ECX, with nothing pushed");
  check(g_obs.fill_calls == 0,
        "0x00ec3bd4 is skipped when the word at 0x20 is zero");
  check(got == 0u, "the zero-word path leaves zero in EAX");
}

// A non-null word takes the block: the second transfer runs with the word as
// its first argument and receiver+0x80 as its second, and the EAX word is
// returned.
void test_non_null_word_reaches_the_second_transfer() {
  Receiver receiver;
  g_obs = Observation{};
  g_obs.fill_result = 0x1234u;
  OpaqueOwnedBlock *const owned = &g_obs;
  plant_owned_word(receiver, owned);

  const unclassified_in_EAX got =
      sporepedia_owned_slot_notify_FUN_00ec3bc0(receiver.bytes);

  check(g_obs.fill_calls == 1, "0x00ec3bd4 runs exactly once for a non-null word");
  check(g_obs.fill_object == owned,
        "the first argument at 0x00ec3bd3 is the word read at 0x00ec3bc8");
  check(g_obs.fill_bounds ==
            reinterpret_cast<BoundsWords *>(receiver.bytes + kBoundsBaseAdjustment),
        "the second argument at 0x00ec3bd2 is receiver+0x80, from SUB ESI,-0x80");
  check(got == 0x1234u, "the EAX word of the second transfer is the one returned");
}

// The order the listing fixes: the call at 0x00ec3bc3 precedes the read at
// 0x00ec3bc8. The receiver starts with a zero word and the modelled callee
// plants a non-null one, so a reconstruction that read before the call would
// take the early tail and call nothing.
void test_the_read_follows_the_first_transfer() {
  Receiver receiver;
  g_obs = Observation{};
  g_obs.release_writes_non_null = true;

  sporepedia_owned_slot_notify_FUN_00ec3bc0(receiver.bytes);

  check(g_obs.fill_calls == 1,
        "the word is read after 0x00ec3bc3, so a word the callee plants is seen");
  check(g_obs.fill_object == &g_obs,
        "the planted word, not the original zero, is what the body acts on");
}

// The body reads one receiver word and writes none, so every path must leave
// the receiver's bytes exactly as it found them. This is the check that would
// catch a displacement applied as a write.
//
// One limit worth stating: a store that wrote back the value it had just read
// would leave the bytes identical and so pass here. That store is not
// observable through this interface and is not claimed to be excluded; every
// store that changes a byte is excluded.
void test_the_receiver_is_not_written() {
  Receiver receiver;
  unsigned char before[sizeof receiver.bytes];
  OpaqueOwnedBlock *const owned = &g_obs;

  plant_owned_word(receiver, owned);
  std::memcpy(before, receiver.bytes, sizeof before);

  g_obs = Observation{};
  sporepedia_owned_slot_notify_FUN_00ec3bc0(receiver.bytes);

  check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
        "no byte of the receiver is written on the non-null path");

  // And the zero path, which is the one that would tempt a store of 0.
  Receiver empty;
  std::memcpy(before, empty.bytes, sizeof before);
  g_obs = Observation{};
  sporepedia_owned_slot_notify_FUN_00ec3bc0(empty.bytes);
  check(std::memcmp(before, empty.bytes, sizeof before) == 0,
        "no byte of the receiver is written on the zero path");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_sporepedia_owned_slot_notify

int main() {
  using namespace openspore::reconstruction::pkg_sporepedia_owned_slot_notify;
  test_zero_word_takes_the_early_tail();
  test_non_null_word_reaches_the_second_transfer();
  test_the_read_follows_the_first_transfer();
  test_the_receiver_is_not_written();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
