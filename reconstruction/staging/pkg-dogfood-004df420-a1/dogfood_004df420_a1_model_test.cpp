#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "dogfood_004df420_a1.hpp"

// The port is declared in the header under a macro that is undefined at the end
// of it, so the recording stub below restates the same convention explicitly.
#if defined(_MSC_VER)
#define PKG_DF420_THISCALL __thiscall
#else
#define PKG_DF420_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_dogfood_004df420_a1 {
namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

OpaqueByte g_lo_canary[16];
OpaqueByte g_hi_canary[16];

// Exactly one recording per call is a precondition of the tests below, so the
// recorder resets before every call and the model test asserts the count.
struct PortRecord {
  unsigned calls;
  const void *receiver;
  const void *key;
  OpaqueWord result;
};

PortRecord g_record;

void reset_record(OpaqueWord result) {
  g_record.calls = 0u;
  g_record.receiver = nullptr;
  g_record.key = nullptr;
  g_record.result = result;
}

}  // namespace

// Recording stand-in for 0x004df550. It observes exactly what the model hands
// to the port and returns a chosen dword, so the test can assert the argument
// identity and the return forwarding without a second reconstruction in the
// way. The `const` on the key mirrors the read-only use the callee makes of it.
extern "C" OpaqueWord PKG_DF420_THISCALL
unresolved_004df550(OpaqueSpeciesReceiver *self, const OpaqueKeyTriple *key) {
  ++g_record.calls;
  g_record.receiver = self;
  g_record.key = key;
  return g_record.result;
}

namespace {

// A receiver framed by canaries, so any write outside the proven covered prefix
// is detected rather than assumed absent.
struct alignas(4) FramedReceiver {
  OpaqueByte lo_canary[16];
  OpaqueSpeciesReceiver root;
  OpaqueByte hi_canary[16];
};

FramedReceiver seeded_framed_receiver() {
  FramedReceiver framed{};
  for (std::size_t index = 0; index < sizeof(framed.lo_canary); ++index) {
    framed.lo_canary[index] = 0xa5u;
    g_lo_canary[index] = 0xa5u;
    g_hi_canary[index] = 0xa5u;
    framed.hi_canary[index] = 0xa5u;
  }
  framed.root.word_000 = 0xdeadbeefu;
  for (std::size_t index = 0; index < sizeof(framed.root.opaque_004); ++index) {
    framed.root.opaque_004[index] = static_cast<OpaqueByte>(0x10u + index);
  }
  framed.root.key_0a4.word_00 = 0x01020304u;
  framed.root.key_0a4.word_04 = 0x05060708u;
  framed.root.key_0a4.word_08 = 0x090a0b0cu;
  return framed;
}

bool canaries_intact(const FramedReceiver &framed) {
  for (std::size_t index = 0; index < sizeof(framed.lo_canary); ++index) {
    if (framed.lo_canary[index] != g_lo_canary[index]) {
      return false;
    }
    if (framed.hi_canary[index] != g_hi_canary[index]) {
      return false;
    }
  }
  return true;
}

// The receiver handed to the port must be bit-identical to the receiver the
// model was called with. The body spills ECX and reloads it, so the port sees
// the same pointer, not a copy of the object and not a derived pointer.
void test_receiver_is_forwarded_unchanged() {
  FramedReceiver framed = seeded_framed_receiver();
  reset_record(0x11223344u);

  const OpaqueWord result =
      dogfood_species_key_resolve_fun_004df420(&framed.root);

  check(g_record.calls == 1u);
  check(g_record.receiver == static_cast<const void *>(&framed.root));
  check(g_record.receiver == reinterpret_cast<const void *>(&framed.root));
  check(result == 0x11223344u);
}

// The one argument must be exactly `receiver + 0xa4`, which is what the body
// forms with "MOV EAX,[EBP-0x4]" then "ADD EAX,0xa4" then "PUSH EAX".
void test_argument_is_receiver_plus_0xa4() {
  FramedReceiver framed = seeded_framed_receiver();
  reset_record(0u);

  dogfood_species_key_resolve_fun_004df420(&framed.root);

  check(g_record.key == reinterpret_cast<const void *>(&framed.root.key_0a4));
  check(g_record.key ==
        static_cast<const OpaqueByte *>(g_record.receiver) + 0xa4);
  check(g_record.key != reinterpret_cast<const void *>(&framed.root.word_000));
  check(g_record.key != reinterpret_cast<const void *>(&framed.root));
}

// The argument must point at the receiver's OWN inline storage rather than at a
// copy or at storage reached through an indirection. 0x004df550 reads the block
// through the pointer and copies all twelve bytes, so aliasing the receiver is
// observable and any indirection would change what the callee sees.
void test_argument_aliases_the_receivers_inline_storage() {
  FramedReceiver framed = seeded_framed_receiver();
  reset_record(0u);

  dogfood_species_key_resolve_fun_004df420(&framed.root);

  const OpaqueByte *key = reinterpret_cast<const OpaqueByte *>(g_record.key);
  const OpaqueByte *root = reinterpret_cast<const OpaqueByte *>(&framed.root);
  for (std::size_t index = 0; index < sizeof(framed.root.key_0a4); ++index) {
    check(key + index == root + 0xa4 + index);
  }
}

// The key argument reads the twelve bytes the receiver already holds,
// bit-exactly and in callee order: word zero at +0, word one at +4, word two at
// +8, the same three loads 0x004df550 performs at
// 0x004df5a6/0x004df5ab/0x004df5b1.
void test_key_argument_reads_the_receiver_key_block() {
  FramedReceiver framed = seeded_framed_receiver();
  reset_record(0u);

  dogfood_species_key_resolve_fun_004df420(&framed.root);

  const OpaqueKeyTriple *key =
      reinterpret_cast<const OpaqueKeyTriple *>(g_record.key);
  check(key->word_00 == 0x01020304u);
  check(key->word_04 == 0x05060708u);
  check(key->word_08 == 0x090a0b0cu);
}

// The key's word zero is bit-identical to the receiver's +0xa4 word, because
// the key IS the receiver's +0xa4 block.
//
// This is the algebra behind a static reachability result recorded in the
// header. 0x004df550 gates its key-substitution branch on the key's word zero
// being zero (0x004df5b7/0x004df5bb) and separately tests the receiver's +0xa4
// word on entry (0x004df56d). This target makes those the same dword, so the
// substitution cannot execute on this call path. The model test cannot execute
// the callee, so it asserts the identity that makes the result true instead of
// asserting the result.
void test_key_word_zero_is_the_receivers_a4_word() {
  FramedReceiver framed = seeded_framed_receiver();
  reset_record(0u);

  dogfood_species_key_resolve_fun_004df420(&framed.root);

  const OpaqueKeyTriple *key =
      reinterpret_cast<const OpaqueKeyTriple *>(g_record.key);
  check(key->word_00 == framed.root.key_0a4.word_00);
  check(reinterpret_cast<const OpaqueByte *>(key) ==
        reinterpret_cast<const OpaqueByte *>(&framed.root.key_0a4));

  // The identity must hold for every value of the word, not just the seed,
  // because the callee's two comparisons are exhaustive over that word.
  const OpaqueWord words[] = {0x00000000u, 0x00000001u, 0x7fffffffu,
                              0x80000000u, 0xffffffffu};
  for (const OpaqueWord word : words) {
    framed.root.key_0a4.word_00 = word;
    reset_record(0u);
    dogfood_species_key_resolve_fun_004df420(&framed.root);
    const OpaqueKeyTriple *swept =
        reinterpret_cast<const OpaqueKeyTriple *>(g_record.key);
    check(swept->word_00 == word);
  }
}

// The body ends with a bare RET and never writes EAX after the CALL, so the
// port's dword must reach the caller unchanged. Swept over the whole 32 bit
// space's interesting corners, so this is a bit-exact round trip and not a
// truthiness check. Null is included because every early exit of the callee
// returns null and call sites null-test the result.
void test_return_value_is_the_ports_dword() {
  FramedReceiver framed = seeded_framed_receiver();

  const OpaqueWord seeds[] = {0x00000000u, 0x00000001u, 0x7fffffffu,
                              0x80000000u, 0xffffffffu, 0xcafebabeu};
  for (const OpaqueWord seed : seeds) {
    reset_record(seed);
    check(dogfood_species_key_resolve_fun_004df420(&framed.root) == seed);
    check(g_record.calls == 1u);
  }
}

// Zero is not a skip. The body has no test of any kind, so an all-zero key
// block still reaches the port exactly once, with the same argument address.
void test_zero_key_block_still_reaches_the_port() {
  FramedReceiver framed = seeded_framed_receiver();
  for (std::size_t index = 0; index < sizeof(framed.root.key_0a4); ++index) {
    reinterpret_cast<OpaqueByte *>(&framed.root.key_0a4)[index] = 0u;
  }
  reset_record(0u);

  const OpaqueWord result =
      dogfood_species_key_resolve_fun_004df420(&framed.root);

  check(g_record.calls == 1u);
  check(g_record.key == reinterpret_cast<const void *>(&framed.root.key_0a4));
  check(result == 0u);
}

// The receiver is forwarded, never dereferenced, so the value of the word at
// receiver +0x00 must not influence the call at all.
void test_receiver_word_zero_does_not_influence_the_call() {
  FramedReceiver first = seeded_framed_receiver();
  FramedReceiver second = seeded_framed_receiver();
  second.root.word_000 = 0x00000000u;

  reset_record(0xdeadbeefu);
  dogfood_species_key_resolve_fun_004df420(&first.root);
  const unsigned first_calls = g_record.calls;
  const void *first_receiver = g_record.receiver;
  const void *first_key = g_record.key;

  reset_record(0xdeadbeefu);
  dogfood_species_key_resolve_fun_004df420(&second.root);

  check(first_calls == 1u);
  check(g_record.calls == 1u);
  // Both receivers differ, so the key addresses differ, and that difference is
  // the only thing the displacement produced: nothing about the +0x00 word
  // reached the port.
  check(first_receiver != g_record.receiver);
  check(first_key != g_record.key);
}

// The body writes no memory at all. Every byte of the receiver and both canary
// bands must be bit-identical after the call.
void test_no_memory_is_written() {
  FramedReceiver framed = seeded_framed_receiver();
  OpaqueByte before[sizeof(FramedReceiver)] = {};
  std::memcpy(before, &framed, sizeof(framed));

  reset_record(0x5a5a5a5au);
  dogfood_species_key_resolve_fun_004df420(&framed.root);

  check(std::memcmp(before, &framed, sizeof(framed)) == 0);
  check(canaries_intact(framed));
}

// The model must not assume where the receiver lives. A stack receiver, a heap
// receiver and a static receiver all have to produce the same relationship
// between the receiver and the argument.
void test_argument_offset_is_independent_of_receiver_placement() {
  OpaqueSpeciesReceiver on_stack{};
  static OpaqueSpeciesReceiver in_static{};
  OpaqueSpeciesReceiver *in_heap = new OpaqueSpeciesReceiver();

  OpaqueSpeciesReceiver *const receivers[] = {&on_stack, in_heap, &in_static};
  for (OpaqueSpeciesReceiver *receiver : receivers) {
    reset_record(0u);
    dogfood_species_key_resolve_fun_004df420(receiver);
    check(g_record.calls == 1u);
    check(g_record.receiver == static_cast<const void *>(receiver));
    check(g_record.key ==
          reinterpret_cast<const OpaqueByte *>(receiver) + 0xa4);
    check(g_record.key ==
          reinterpret_cast<const OpaqueByte *>(&receiver->key_0a4));
  }

  delete in_heap;
}

// The port is entered exactly once per model call, at every receiver placement,
// with no retry and no second dispatch.
void test_exactly_one_dispatch_per_call() {
  FramedReceiver framed = seeded_framed_receiver();
  for (int index = 0; index < 8; ++index) {
    reset_record(static_cast<OpaqueWord>(index));
    const OpaqueWord result =
        dogfood_species_key_resolve_fun_004df420(&framed.root);
    check(g_record.calls == 1u);
    check(result == static_cast<OpaqueWord>(index));
  }
}

// The twelve byte block the port reads is the same block 0x004df550 copies at
// 0x004df5a6/0x004df5ab/0x004df5b1, so the model must present a three word
// block of exactly that width, in that order.
void test_key_block_width_and_order_match_the_callee_copy() {
  FramedReceiver framed = seeded_framed_receiver();
  reset_record(0u);
  dogfood_species_key_resolve_fun_004df420(&framed.root);

  const OpaqueByte *key = reinterpret_cast<const OpaqueByte *>(g_record.key);
  const OpaqueByte *root = reinterpret_cast<const OpaqueByte *>(&framed.root);
  check(sizeof(framed.root.key_0a4) == 0x0c);
  check(sizeof(OpaqueKeyTriple) == 0x0c);
  for (std::size_t index = 0; index < sizeof(framed.root.key_0a4); ++index) {
    check(key[index] == root[0xa4 + index]);
  }
}

int run_tests() {
  test_receiver_is_forwarded_unchanged();
  test_argument_is_receiver_plus_0xa4();
  test_argument_aliases_the_receivers_inline_storage();
  test_key_argument_reads_the_receiver_key_block();
  test_key_word_zero_is_the_receivers_a4_word();
  test_return_value_is_the_ports_dword();
  test_zero_key_block_still_reaches_the_port();
  test_receiver_word_zero_does_not_influence_the_call();
  test_no_memory_is_written();
  test_argument_offset_is_independent_of_receiver_placement();
  test_exactly_one_dispatch_per_call();
  test_key_block_width_and_order_match_the_callee_copy();
  return 0;
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dogfood_004df420_a1

int main() {
  return openspore::reconstruction::pkg_dogfood_004df420_a1::run_tests();
}
