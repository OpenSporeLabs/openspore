#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "editor_species_default_wave12.hpp"

// The port is declared in the header under a macro that is undefined at the end
// of it, so the recording stub below restates the same convention explicitly.
#if defined(_MSC_VER)
#define PKG_ESD12_THISCALL __thiscall
#else
#define PKG_ESD12_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_species_default_wave12 {
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
// way.
extern "C" OpaqueWord PKG_ESD12_THISCALL
unresolved_004df550(OpaqueSpeciesLinkRoot *self, const OpaqueSpeciesKey3 *key) {
  ++g_record.calls;
  g_record.receiver = self;
  g_record.key = key;
  return g_record.result;
}

namespace {

// A receiver framed by canaries, so any write outside the proven covered prefix
// is detected rather than assumed absent.
struct alignas(4) FramedRoot {
  OpaqueByte lo_canary[16];
  OpaqueSpeciesLinkRoot root;
  OpaqueByte hi_canary[16];
};

FramedRoot seeded_framed_root() {
  FramedRoot framed{};
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

bool canaries_intact(const FramedRoot &framed) {
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
// model was called with: the body spills ECX and reloads it, so the port sees
// the same pointer, not a copy of the object and not a derived pointer.
void test_receiver_is_forwarded_unchanged() {
  FramedRoot framed = seeded_framed_root();
  reset_record(0x11223344u);

  const OpaqueWord result = editor_species_resolve_fun_004df420(&framed.root);

  check(g_record.calls == 1u);
  check(g_record.receiver == static_cast<const void *>(&framed.root));
  check(g_record.receiver == reinterpret_cast<const void *>(&framed.root));
  check(result == 0x11223344u);
}

// The one argument must be exactly `receiver + 0xa4`, which is what the body
// forms with "MOV EAX,[EBP-0x4]" then "ADD EAX,0xa4" then "PUSH EAX".
void test_argument_is_receiver_plus_0xa4() {
  FramedRoot framed = seeded_framed_root();
  reset_record(0u);

  editor_species_resolve_fun_004df420(&framed.root);

  check(g_record.key == reinterpret_cast<const void *>(&framed.root.key_0a4));
  check(g_record.key ==
        static_cast<const OpaqueByte *>(g_record.receiver) + 0xa4);
  check(g_record.key != reinterpret_cast<const void *>(&framed.root.word_000));
  check(g_record.key != reinterpret_cast<const void *>(&framed.root));
}

// The key argument is a pointer to the receiver's own storage, so the port
// reads the twelve bytes the receiver already holds. That identity is the whole
// observable effect of the +0xa4 displacement and it must hold bit-exactly.
void test_key_argument_reads_the_receiver_key_block() {
  FramedRoot framed = seeded_framed_root();
  reset_record(0u);

  editor_species_resolve_fun_004df420(&framed.root);

  const OpaqueSpeciesKey3 *key =
      reinterpret_cast<const OpaqueSpeciesKey3 *>(g_record.key);
  check(key->word_00 == 0x01020304u);
  check(key->word_04 == 0x05060708u);
  check(key->word_08 == 0x090a0b0cu);
}

// The body ends with a bare RET and never writes EAX after the CALL, so the
// port's dword must reach the caller unchanged. Six observed call sites consume
// it, so this is the observable return, not an incidental register residue.
void test_return_value_is_the_ports_dword() {
  FramedRoot framed = seeded_framed_root();

  const OpaqueWord seeds[] = {0x00000000u, 0x00000001u, 0x7fffffffu,
                              0x80000000u, 0xffffffffu, 0xcafebabeu};
  for (const OpaqueWord seed : seeds) {
    reset_record(seed);
    check(editor_species_resolve_fun_004df420(&framed.root) == seed);
    check(g_record.calls == 1u);
  }
}

// Zero is not a skip. The body has no test of any kind, so an all-zero key
// block and a null key pointer at the call site both still reach the port
// exactly once.
void test_zero_key_block_still_reaches_the_port() {
  FramedRoot framed = seeded_framed_root();
  for (std::size_t index = 0; index < sizeof(framed.root.key_0a4); ++index) {
    reinterpret_cast<OpaqueByte *>(&framed.root.key_0a4)[index] = 0u;
  }
  reset_record(0u);

  const OpaqueWord result = editor_species_resolve_fun_004df420(&framed.root);

  check(g_record.calls == 1u);
  check(g_record.key == reinterpret_cast<const void *>(&framed.root.key_0a4));
  check(result == 0u);
}

// The receiver is forwarded, never dereferenced, so the value of the word at
// receiver +0x00 must not influence the call at all.
void test_receiver_word_zero_does_not_influence_the_call() {
  FramedRoot first = seeded_framed_root();
  FramedRoot second = seeded_framed_root();
  second.root.word_000 = 0x00000000u;

  reset_record(0xdeadbeefu);
  editor_species_resolve_fun_004df420(&first.root);
  const unsigned first_calls = g_record.calls;
  const void *first_receiver = g_record.receiver;
  const void *first_key = g_record.key;

  reset_record(0xdeadbeefu);
  editor_species_resolve_fun_004df420(&second.root);

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
  FramedRoot framed = seeded_framed_root();
  OpaqueByte before[sizeof(FramedRoot)] = {};
  std::memcpy(before, &framed, sizeof(framed));

  reset_record(0x5a5a5a5au);
  editor_species_resolve_fun_004df420(&framed.root);

  check(std::memcmp(before, &framed, sizeof(framed)) == 0);
  check(canaries_intact(framed));
}

// The model must not assume where the receiver lives. A stack receiver, a heap
// receiver and a static receiver all have to produce the same relationship
// between the receiver and the argument.
void test_argument_offset_is_independent_of_receiver_placement() {
  OpaqueSpeciesLinkRoot on_stack{};
  static OpaqueSpeciesLinkRoot in_static{};
  OpaqueSpeciesLinkRoot *in_heap = new OpaqueSpeciesLinkRoot();

  OpaqueSpeciesLinkRoot *const receivers[] = {&on_stack, in_heap, &in_static};
  for (OpaqueSpeciesLinkRoot *receiver : receivers) {
    reset_record(0u);
    editor_species_resolve_fun_004df420(receiver);
    check(g_record.calls == 1u);
    check(g_record.receiver == static_cast<const void *>(receiver));
    check(g_record.key ==
          reinterpret_cast<const OpaqueByte *>(receiver) + 0xa4);
    check(g_record.key ==
          reinterpret_cast<const OpaqueByte *>(receiver) + 0xa4);
  }

  delete in_heap;
}

// The port is entered exactly once per model call, at every receiver placement,
// with no retry and no second dispatch.
void test_exactly_one_dispatch_per_call() {
  FramedRoot framed = seeded_framed_root();
  for (int index = 0; index < 8; ++index) {
    reset_record(static_cast<OpaqueWord>(index));
    const OpaqueWord result = editor_species_resolve_fun_004df420(&framed.root);
    check(g_record.calls == 1u);
    check(result == static_cast<OpaqueWord>(index));
  }
}

// The twelve byte block the port reads is the same block 0x004df550 copies at
// 0x004df5a6/0x004df5ab/0x004df5b1, so the model must present a three word
// block of exactly that width, in that order.
void test_key_block_width_and_order_match_the_callee_copy() {
  FramedRoot framed = seeded_framed_root();
  reset_record(0u);
  editor_species_resolve_fun_004df420(&framed.root);

  const OpaqueByte *key = reinterpret_cast<const OpaqueByte *>(g_record.key);
  const OpaqueByte *root = reinterpret_cast<const OpaqueByte *>(&framed.root);
  check(sizeof(framed.root.key_0a4) == 0x0c);
  for (std::size_t index = 0; index < sizeof(framed.root.key_0a4); ++index) {
    check(key[index] == root[0xa4 + index]);
  }
}

int run_tests() {
  test_receiver_is_forwarded_unchanged();
  test_argument_is_receiver_plus_0xa4();
  test_key_argument_reads_the_receiver_key_block();
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
}  // namespace openspore::reconstruction::pkg_editor_species_default_wave12

int main() {
  return openspore::reconstruction::pkg_editor_species_default_wave12::
      run_tests();
}
