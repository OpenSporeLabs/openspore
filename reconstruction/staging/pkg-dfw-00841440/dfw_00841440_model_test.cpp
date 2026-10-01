// PKG-DFW-00841440 -- model test for SporeApp.exe 0x00841440.
//
// Plain int main() with explicit checks. No framework, no gtest, no external
// dependency. Every assertion below is anchored to an instruction of the
// 11-instruction listing at 0x00841440 or of the 5-instruction tail at
// 0x0083c780, and the anchor is named in the check's own label so a failure
// says which instruction it contradicts.
//
// The tail 0x0083c780 is not owned by this package, so it is DEFINED HERE, as
// an observer: it records the three words it was handed, the receiver contents
// as they stood at its entry, and it reproduces the two receiver stores its own
// listing shows. Its return value is machine-faithful by default (EAX at
// 0x0083c78e still holds the first stack word that 0x0083c780 loaded) and can
// be forced to a chosen constant so that verbatim propagation is testable too.

#include "dfw_00841440_types.hpp"

#include <cstdio>

namespace {

// -- the observer's record of one entry -------------------------------------
struct TailObservation {
  unsigned calls;
  const void *receiver;
  const void *pName;
  const void *second;
  openspore::reconstruction::pkg_dfw_00841440::MachineWord word_30_at_entry;
  openspore::reconstruction::pkg_dfw_00841440::MachineWord word_04_at_entry;
  openspore::reconstruction::pkg_dfw_00841440::MachineWord word_0c_at_entry;
};

TailObservation g_tail = {0u, nullptr, nullptr, nullptr, 0u, 0u, 0u};

// -1 = machine-faithful; 0 or 1 = return this chosen value instead, so the test
// can tell "the target returned its own EAX" from "the target returned the
// tail's word".
int g_tail_forced_return = -1;

int g_checks = 0;
int g_failures = 0;

void check(bool ok, const char *what) {
  ++g_checks;
  if (!ok) {
    ++g_failures;
    std::printf("FAIL  %s\n", what);
  }
}

void check_word(unsigned long got, unsigned long want, const char *what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL  %s: got 0x%lx, want 0x%lx\n", what, got, want);
  }
}

void reset_observation() {
  g_tail.calls = 0u;
  g_tail.receiver = nullptr;
  g_tail.pName = nullptr;
  g_tail.second = nullptr;
  g_tail.word_30_at_entry = 0u;
  g_tail.word_04_at_entry = 0u;
  g_tail.word_0c_at_entry = 0u;
  g_tail_forced_return = -1;
}

using namespace openspore::reconstruction::pkg_dfw_00841440;

// 0x34 bytes of a pattern no displacement of this model uses, so any byte that
// moves is a byte some instruction of the listing wrote.
constexpr std::uint8_t kFill = 0xa5u;
// The same fill read back as a whole word, which is how 0x0083c780's loader and
// every load_word in this test see it.
const unsigned long kFillWord = 0xa5a5a5a5ul;

OpaqueFormatParser make_filled_receiver() {
  OpaqueFormatParser receiver;
  for (std::size_t index = 0; index < sizeof receiver.opaque; ++index) {
    receiver.opaque[index] = kFill;
  }
  return receiver;
}

// Chosen non-null argument values. Only the words matter: nothing in the model
// dereferences either, and 0x00003040 is chosen so that the biased word
// 0x0000303c is a distinct value a wrong bias would be caught against.
char *const kNameWord = reinterpret_cast<char *>(static_cast<std::uintptr_t>(0x0000a1b2u));
OpaqueLine *const kLineWord =
    reinterpret_cast<OpaqueLine *>(static_cast<std::uintptr_t>(0x00003040u));

const unsigned long kLineWordValue = 0x00003040ul;
const unsigned long kBiasedLineValue = 0x0000303cul;

}  // namespace

namespace openspore::reconstruction::pkg_dfw_00841440 {

// The observer for the shared tail 0x0083c780, reproduced from its five
// instructions and nothing else:
//
//   0x0083c780  MOV EAX,dword ptr [ESP + 0x4]   first stack word  -> EAX
//   0x0083c784  MOV EDX,dword ptr [ESP + 0x8]   second stack word -> EDX
//   0x0083c788  MOV dword ptr [ECX + 0x4],EAX
//   0x0083c78b  MOV dword ptr [ECX + 0xc],EDX
//   0x0083c78e  RET 0x8                         EAX still the first stack word
//
// The declared return type of the target is bool and the exported decompilation
// models this result as a single byte, so the byte of the first stack word is
// what decides the bool: 0x00000100 is a non-null pointer that yields false.
bool PKG_DFW_00841440_THISCALL dfw_00841440_shared_tail_0083c780(
    OpaqueFormatParser *receiver, char *pName, OpaqueLine *argumentsLine) {
  unsigned char *const base = reinterpret_cast<unsigned char *>(receiver);
  const MachineWord first_word =
      static_cast<MachineWord>(reinterpret_cast<std::uintptr_t>(pName));
  const MachineWord second_word = static_cast<MachineWord>(
      reinterpret_cast<std::uintptr_t>(argumentsLine));

  ++g_tail.calls;
  g_tail.receiver = receiver;
  g_tail.pName = pName;
  g_tail.second = argumentsLine;
  g_tail.word_30_at_entry = load_word(base, kReceiverWord_30);
  g_tail.word_04_at_entry = load_word(base, kReceiverWord_04);
  g_tail.word_0c_at_entry = load_word(base, kReceiverWord_0c);

  // 0x0083c788 / 0x0083c78b: the tail's own two receiver stores. It does not
  // touch displacement 0x30, so whatever 0x00841440 wrote there survives.
  store_word(base, kReceiverWord_04, first_word);
  store_word(base, kReceiverWord_0c, second_word);

  // 0x0083c78e RET 0x8 with EAX untouched since 0x0083c780.
  if (g_tail_forced_return >= 0) {
    return g_tail_forced_return != 0;
  }
  return static_cast<unsigned char>(first_word) != 0u;
}

}  // namespace openspore::reconstruction::pkg_dfw_00841440

namespace {

// One call, from a freshly filled receiver, with the observation reset.
bool call_target(OpaqueFormatParser *receiver, char *pName, OpaqueLine *line) {
  return dfw_00841440_CreateDefinitionSafe(receiver, pName, line);
}

}  // namespace

int main() {
  // -- case 1: non-null second word, non-null first word ---------------------
  // 0x00841446 JZ not taken; 0x00841448 LEA EAX,[EDX-0x4];
  // 0x0084144b store at [ECX+0x30]; 0x00841452 JMP 0x0083c780
  {
    reset_observation();
    OpaqueFormatParser receiver = make_filled_receiver();
    const bool result = call_target(&receiver, kNameWord, kLineWord);

    check_word(g_tail.calls, 1ul,
               "0x00841452: the tail is entered exactly once per call");
    check(g_tail.receiver == &receiver, "0x0083c788: ECX reaches the tail as the receiver");
    check(g_tail.pName == kNameWord, "0x00841440: the first stack word is passed on unchanged");
    check(g_tail.second == kLineWord,
          "0x0084144e/0x0083c784: the [ESP+0x8] rewrite is value-preserving, so the tail "
          "receives the original second word");
    check_word(load_word(&receiver, kReceiverWord_30), kBiasedLineValue,
               "0x00841448/0x0084144b: displacement 0x30 holds second word minus 4");
    check(load_word(&receiver, kReceiverWord_30) != kLineWordValue,
          "0x00841448: the stored word is the biased one, not a copy of the second word");
    check(g_tail.word_30_at_entry == kBiasedLineValue,
          "0x0084144b precedes 0x00841452: the tail observes the store already done");
    check_word(load_word(&receiver, kReceiverWord_30), g_tail.word_30_at_entry,
               "0x00841452: no store happens after the transfer to the tail");
    check_word(g_tail.word_04_at_entry, kFillWord,
               "0x0084144b: before the transfer the body has written no receiver word but 0x30");
    check_word(g_tail.word_0c_at_entry, kFillWord,
               "0x0084144b: before the transfer the body has written no receiver word but 0x30");
    check(result, "0x0083c780/0x0083c78e: a non-null first word returns true");
  }

  // -- case 2: NULL second word, non-null first word -------------------------
  // 0x00841446 JZ taken to 0x00841457; 0x00841459 stores a zero word;
  // 0x0084145c rewrites the slot with zero; 0x00841460 JMP 0x0083c780
  {
    reset_observation();
    OpaqueFormatParser receiver = make_filled_receiver();
    const bool result = call_target(&receiver, kNameWord, nullptr);

    check_word(g_tail.calls, 1ul, "0x00841460: the null arm still enters the tail once");
    check(g_tail.second == nullptr, "0x0084145c: the slot rewrite on the null arm is zero to zero");
    check_word(load_word(&receiver, kReceiverWord_30), 0ul,
               "0x00841457/0x00841459: displacement 0x30 is written with zero");
    check_word(g_tail.word_30_at_entry, 0ul,
               "0x00841459 precedes 0x00841460: the zero store is done before the transfer");
    check(result, "0x0083c780: the null arm still returns the first stack word, so true");
  }

  // -- case 3: NULL first word, NON-NULL second word -------------------------
  // The branch at 0x00841446 tests the second stack word, so a null first word
  // must NOT change which arm runs. This is the check that would fail if the
  // body acted on the first word instead of the second, which is exactly the
  // dispute the exported decompilation's parameter naming would produce.
  {
    reset_observation();
    OpaqueFormatParser receiver = make_filled_receiver();
    const bool result = call_target(&receiver, nullptr, kLineWord);

    check_word(g_tail.calls, 1ul, "0x00841444: the tested word is the second stack word, not the first");
    check_word(load_word(&receiver, kReceiverWord_30), kBiasedLineValue,
               "0x00841448: with a null first word the non-null arm still runs");
    check(result == false,
          "0x0083c780: with a null first word the observed return is false on either arm");
  }

  // -- case 4: both words NULL -----------------------------------------------
  {
    reset_observation();
    OpaqueFormatParser receiver = make_filled_receiver();
    const bool result = call_target(&receiver, nullptr, nullptr);

    check_word(g_tail.calls, 1ul, "0x00841440: every call reaches the tail once");
    check_word(load_word(&receiver, kReceiverWord_30), 0ul, "0x00841459: the null arm stores zero");
    check(result == false, "0x0083c780: a null first word returns false");
  }

  // -- case 5/6: the return word is the FIRST stack word, byte for byte -------
  // 0x0083c780 loads the whole first stack word into EAX and 0x0083c78e returns
  // it, but the declared type is bool, so the byte of that word decides it.
  // 0x00000100 is a non-null pointer whose byte is zero.
  {
    reset_observation();
    OpaqueFormatParser receiver = make_filled_receiver();
    char *const lowByteZero = reinterpret_cast<char *>(static_cast<std::uintptr_t>(0x00000100u));
    char *const lowByteSet = reinterpret_cast<char *>(static_cast<std::uintptr_t>(0x00000101u));

    check(call_target(&receiver, lowByteZero, kLineWord) == false,
          "0x0083c780/RET 0x8: a first word of 0x00000100 is non-null but its byte is zero");
    reset_observation();
    check(call_target(&receiver, lowByteSet, nullptr) == true,
          "0x0083c780/RET 0x8: a first word of 0x00000101 returns true");
    check_word(load_word(&receiver, kReceiverWord_30), 0ul,
               "0x00841459: the first word does not select the arm");
  }

  // -- case 7/8: the returned word is the TAIL's, not this body's -------------
  // The body writes EAX on both arms (the biased word, and zero) and the tail
  // overwrites it. Forcing the tail's return must therefore be visible through
  // the target on both arms, including where the body's own EAX disagrees.
  {
    reset_observation();
    OpaqueFormatParser receiver = make_filled_receiver();
    g_tail_forced_return = 1;
    check(call_target(&receiver, nullptr, nullptr) == true,
          "0x00841460/0x0083c78e: a forced true tail word is returned even where the "
          "body's own EAX was zero");

    reset_observation();
    receiver = make_filled_receiver();
    g_tail_forced_return = 0;
    check(call_target(&receiver, kNameWord, kLineWord) == false,
          "0x00841452/0x0083c78e: a forced false tail word is returned even where the "
          "body's own EAX held the non-zero biased word");
    check_word(load_word(&receiver, kReceiverWord_30), kBiasedLineValue,
               "0x0084144b: the forced return did not disturb the receiver store");
  }

  // -- case 9: write footprint ------------------------------------------------
  // The complete listing stores at exactly three displacements: 0x30 twice from
  // this body, 0x4 and 0xc once each from the tail. Every other byte of the
  // receiver must be untouched.
  {
    reset_observation();
    OpaqueFormatParser receiver = make_filled_receiver();
    call_target(&receiver, kNameWord, kLineWord);

    int moved_bytes = 0;
    for (std::size_t index = 0; index < sizeof receiver.opaque; ++index) {
      const bool written = (index >= 0x04 && index < 0x08) ||
                           (index >= 0x0c && index < 0x10) ||
                           (index >= 0x30 && index < 0x34);
      if (receiver.opaque[index] != kFill) {
        ++moved_bytes;
        check(written, "0x0084144b/0x0083c788/0x0083c78b: a byte outside 0x04, 0x0c and "
                       "0x30 was written");
      }
    }
    check_word(static_cast<unsigned long>(moved_bytes), 12ul,
               "0x0084144b/0x00841459/0x0083c788/0x0083c78b: exactly three words are written");
    check_word(load_word(&receiver, kReceiverWord_04), 0x0000a1b2ul,
               "0x0083c788: the tail stored the first stack word at displacement 0x4");
    check_word(load_word(&receiver, kReceiverWord_0c), kLineWordValue,
               "0x0083c78b: the tail stored the second stack word at displacement 0xc");
  }

  // -- case 10: displacement 0x30 is write-only -------------------------------
  // The body never reads the receiver, so a pre-existing value at 0x30 cannot
  // change the outcome.
  {
    OpaqueFormatParser receiver = make_filled_receiver();
    store_word(&receiver, kReceiverWord_30, 0xa5a5a5a5u);
    reset_observation();
    const bool first = call_target(&receiver, kNameWord, kLineWord);
    const MachineWord after_seeded = load_word(&receiver, kReceiverWord_30);

    receiver = make_filled_receiver();
    store_word(&receiver, kReceiverWord_30, 0x00000000u);
    reset_observation();
    const bool second = call_target(&receiver, kNameWord, kLineWord);
    const MachineWord after_zeroed = load_word(&receiver, kReceiverWord_30);

    check_word(after_seeded, after_zeroed,
               "0x0084144b: the prior contents of displacement 0x30 do not affect the store");
    check(first == second, "0x0084144b: the prior contents of 0x30 do not affect the return");
    check_word(after_seeded, kBiasedLineValue, "0x00841448: the biased word is stored either way");
  }

  // -- case 11: the [ESP+0x8] slot rewrite happens on both arms ---------------
  // 0x0084144e and 0x0084145c are separate stores in the listing, one per arm.
  // Each must hand the tail the value the slot arrived with.
  //
  // Honest limit of these checks, established by mutation rather than asserted:
  // both stores rewrite the slot with the value the slot already holds, so a
  // model that DELETED them entirely would still pass everything here. Their
  // only observable consequence is the content the tail then reads at
  // 0x0083c784, and that content is the same either way. The stores are
  // therefore reproduced in the model as a claim about the listing, and these
  // checks can only confirm that the value reaching the tail is the original
  // one; they cannot confirm that the store instruction is present.
  {
    reset_observation();
    OpaqueFormatParser receiver = make_filled_receiver();
    call_target(&receiver, kNameWord, kLineWord);
    check(g_tail.second == reinterpret_cast<const void *>(kLineWordValue),
          "0x0084144e: the non-null arm leaves the original word in the slot");
    check(g_tail.second != reinterpret_cast<const void *>(kBiasedLineValue),
          "0x0084144e: the biased word is stored to the receiver, not to the slot");

    reset_observation();
    receiver = make_filled_receiver();
    call_target(&receiver, kNameWord, nullptr);
    check(g_tail.second == nullptr, "0x0084145c: the null arm leaves the original word in the slot");
  }

  std::printf("%s  %d checks, %d failures\n", g_failures == 0 ? "PASS" : "FAIL",
              g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
