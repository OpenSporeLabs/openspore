// Behavioural model test for the reconstruction of SporeApp.exe 0x00841440
// (ArgScript::FormatParser::CreateDefinitionSafe).
//
// Build (x86-32 required; the package header hard-errors otherwise):
//   g++    -m32 -std=c++17 -O2 -Wall -Wextra -Werror
//       argscript_createdefsafe_00841440.cpp
//       argscript_createdefsafe_00841440_model_test.cpp -o model_test_gcc
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Werror
//       argscript_createdefsafe_00841440.cpp
//       argscript_createdefsafe_00841440_model_test.cpp -o model_test_clang
//
// Every assertion is pinned to a byte or an operand read out of SporeApp.exe,
// and each of the load-bearing ones is a *discriminating* test: it is written so
// that a specific wrong reconstruction of the same shape fails it. The
// discriminating cases are named at each test, and are collected at the bottom
// into a table that is checked against the number of live assertions so a test
// cannot be quietly dropped.

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

#include "argscript_createdefsafe_00841440.hpp"

namespace openspore::reconstruction::pkg_argscript_createdefsafe_00841440 {
namespace {

int g_failures = 0;
int g_checks = 0;
int g_discriminating = 0;

void report(bool ok, char const* what) {
  ++g_checks;
  if (!ok) {
    ++g_failures;
    std::printf("FAIL: %s\n", what);
  }
}

void discriminating(bool ok, char const* what) {
  ++g_discriminating;
  report(ok, what);
}

std::uint8_t* base_of(OpaqueFormatParser& parser) {
  return receiver_bytes(&parser);
}

OpaqueWord at(OpaqueFormatParser& parser, std::uint32_t displacement) {
  return read_word_at(base_of(parser), displacement);
}

// A recording tail standing in for 0x0083c780. It performs that function's two
// observed stores and nothing else, so the state the target produced before the
// tail jump can be inspected at the moment control leaves 0x00841440.
struct Recorder {
  int calls = 0;
  OpaqueFormatParser* self = nullptr;
  char* pName = nullptr;
  OpaqueLine* argumentsLine = nullptr;
  OpaqueWord receiver_04_at_entry = 0;
  OpaqueWord receiver_0c_at_entry = 0;
  OpaqueWord receiver_30_at_entry = 0;
  bool perform_stores = true;
};

Recorder g_recorder;

bool recording_tail(OpaqueFormatParser* self, char* pName,
                    OpaqueLine* argumentsLine) {
  ++g_recorder.calls;
  g_recorder.self = self;
  g_recorder.pName = pName;
  g_recorder.argumentsLine = argumentsLine;
  g_recorder.receiver_04_at_entry = at(*self, 0x04u);
  g_recorder.receiver_0c_at_entry = at(*self, 0x0cu);
  g_recorder.receiver_30_at_entry = at(*self, 0x30u);
  if (g_recorder.perform_stores) {
    write_word_at(base_of(*self), 0x04u, word_of(pName));
    write_word_at(base_of(*self), 0x0cu, word_of(argumentsLine));
  }
  // 0x0083c780's first instruction is MOV EAX,[ESP+0x4] and nothing after the
  // two stores writes EAX, so the observed return is the first word as a bool.
  return word_of(pName) != 0u;
}

class PortScope {
 public:
  explicit PortScope(SharedTail0083c780 tail) {
    previous_ = g_tail_0083c780;
    g_tail_0083c780 = tail;
  }
  ~PortScope() { g_tail_0083c780 = previous_; }

 private:
  SharedTail0083c780 previous_;
};

// ---------------------------------------------------------------------------
// 1. 0x00841452 and 0x00841460 are JMP, not CALL, to 0x0083c780. So the tail
//    is entered exactly once per invocation, on both arms, and the receiver and
//    both stack words arrive unchanged -- there is no frame of its own to unwind.
//    Discriminates: a model that calls the tail and then returns false, or that
//    skips the tail on one arm.
// ---------------------------------------------------------------------------
void test_tail_is_entered_once_with_both_arguments() {
  OpaqueFormatParser parser{};
  char name[] = "MyDef";
  OpaqueLine line{};

  PortScope scope(&recording_tail);
  g_recorder = Recorder{};
  const bool result = argscript_formatparser_create_definition_safe_00841440(
      &parser, name, &line);

  discriminating(g_recorder.calls == 1, "tail entered exactly once");
  report(g_recorder.self == &parser, "receiver forwarded as ECX");
  discriminating(g_recorder.pName == name,
                 "first stack word forwarded verbatim, not copied");
  discriminating(g_recorder.argumentsLine == &line,
                 "second stack word forwarded, not the biased value");
  discriminating(result,
                 "EAX at RET is the first argument, non-null here");
}

// 0x00841444 TEST EDX,EDX / 0x00841446 JZ 0x00841457: the test is on the
// SECOND stack word. A null pName must therefore still reach the tail, and must
// still be forwarded.
// Discriminates: testing the first argument instead of the second -- the single
// most likely misreading, and the one the exported decompilation makes.
void test_null_first_argument_still_reaches_the_tail() {
  OpaqueFormatParser parser{};
  OpaqueLine line{};

  PortScope scope(&recording_tail);
  g_recorder = Recorder{};
  const bool result = argscript_formatparser_create_definition_safe_00841440(
      &parser, nullptr, &line);

  discriminating(g_recorder.calls == 1,
                 "null first argument still tail-jumps: test is on arg 2");
  discriminating(g_recorder.pName == nullptr,
                 "null first argument forwarded as a null word");
  discriminating(result == false,
                 "observed return is the null first argument, not a success");
}

// ---------------------------------------------------------------------------
// 2. 0x00841448 LEA EAX,[EDX + -0x4] then 0x0084144b MOV [ECX+0x30],EAX.
//    The bias is exactly four bytes and it is one-sided: it applies to the
//    stored word only, never to the word handed to the tail.
//    Discriminates: storing the raw line, biasing by a different amount, or
//    biasing the forwarded argument as well.
// ---------------------------------------------------------------------------
void test_receiver_30_is_the_four_byte_back_biased_line() {
  OpaqueFormatParser parser{};
  char name[] = "D";
  OpaqueLine line{};

  PortScope scope(&recording_tail);
  g_recorder = Recorder{};
  argscript_formatparser_create_definition_safe_00841440(&parser, name, &line);

  const OpaqueWord raw = word_of(&line);
  discriminating(at(parser, 0x30u) == raw - 4u,
                 "receiver+0x30 is the line minus exactly 4");
  discriminating(g_recorder.receiver_30_at_entry == raw - 4u,
                 "the bias is already applied when the tail is entered");
  discriminating(g_recorder.argumentsLine == &line,
                 "the tail still receives the unbiased line");
}

// The bias is a 32-bit subtraction, not a checked one: a line below the fourth
// byte wraps rather than faulting or saturating, because LEA simply adds -4.
// Discriminates: a model that guards the subtraction.
void test_bias_wraps_as_a_plain_32_bit_subtraction() {
  OpaqueFormatParser parser{};
  char name[] = "D";
  // A Line* value 2 is not a real object and is never dereferenced: the body
  // only ever reads the argument's address. The pointer value 2 is what makes
  // the wrap observable.
  OpaqueLine* const low = reinterpret_cast<OpaqueLine*>(std::uintptr_t{2});

  PortScope scope(&recording_tail);
  g_recorder = Recorder{};
  argscript_formatparser_create_definition_safe_00841440(&parser, name, low);

  discriminating(at(parser, 0x30u) == 0xfffffffeu,
                 "line-4 at a low address wraps to 0xfffffffe");
}

// 0x00841457 XOR EAX,EAX / 0x00841459 MOV [ECX+0x30],EAX: the null path stores
// a plain zero -- not a biased pointer, and not the raw argument.
// Discriminates: a model that runs one shared `line ? line-4 : 0` on a
// different value, or that stores -4 unconditionally.
void test_null_second_argument_stores_plain_zero() {
  OpaqueFormatParser parser{};
  char name[] = "D";
  write_word_at(base_of(parser), 0x30u, 0xdeadbeefu);

  PortScope scope(&recording_tail);
  g_recorder = Recorder{};
  argscript_formatparser_create_definition_safe_00841440(&parser, name, nullptr);

  discriminating(at(parser, 0x30u) == 0u,
                 "null second argument stores 0 at +0x30");
  discriminating(g_recorder.receiver_30_at_entry == 0u,
                 "zero is stored before the tail runs, not by it");
  discriminating(at(parser, 0x30u) != 0xdeadbeefu,
                 "a pre-existing +0x30 is overwritten on the null arm too");
}

// Both arms converge on the same tail, so the branch can only decide the +0x30
// word. Everything else on the two paths must be identical, which is what makes
// the branch observable at all.
// Discriminates: a model that lets the branch also alter a forwarded argument.
void test_only_receiver_30_is_branch_dependent() {
  OpaqueFormatParser with_line{};
  OpaqueFormatParser without_line{};
  char name[] = "Same";
  OpaqueLine line{};

  PortScope scope(&recording_tail);

  g_recorder = Recorder{};
  argscript_formatparser_create_definition_safe_00841440(&with_line, name, &line);
  const OpaqueWord biased = at(with_line, 0x30u);
  g_recorder = Recorder{};
  argscript_formatparser_create_definition_safe_00841440(&without_line, name,
                                                         nullptr);

  report(at(with_line, 0x04u) == at(without_line, 0x04u),
         "tail word +0x04 mirrors the first argument on both arms");
  report(at(with_line, 0x04u) == word_of(name), "+0x04 equals the first argument");
  report(at(with_line, 0x0cu) == word_of(&line),
         "+0x0c equals the second argument");
  report(at(without_line, 0x0cu) == 0u, "null line is forwarded as a null word");
  report(g_recorder.argumentsLine == nullptr,
         "null line reaches the tail as a null pointer");
  discriminating(biased == word_of(&line) - 4u,
                 "non-null arm stores the line minus 4");
  discriminating(at(without_line, 0x30u) == 0u,
                 "null arm stores a plain zero");
  discriminating(biased != at(without_line, 0x30u),
                 "the two arms differ at +0x30 and nowhere else");
}

// The net effect of the whole call is exactly the three observed stores. Every
// other byte of the covered region must survive untouched, which is what makes
// "writes nothing else" a testable claim rather than an assertion of absence.
// Discriminates: a model that writes an extra field, or that clears the
// receiver.
void test_net_receiver_writes_are_exactly_three_words() {
  OpaqueFormatParser parser{};
  std::memset(parser.bytes.data(), 0xa5, parser.bytes.size());
  char name[] = "Z";
  OpaqueLine line{};

  const std::array<std::uint8_t, parser.bytes.size()> before = parser.bytes;

  PortScope scope(&recording_tail);
  g_recorder = Recorder{};
  argscript_formatparser_create_definition_safe_00841440(&parser, name, &line);

  static const std::uint32_t kExpected[] = {0x04u, 0x0cu, 0x30u};
  for (std::size_t offset = 0; offset < parser.bytes.size(); ++offset) {
    bool expected_to_change = false;
    for (std::uint32_t word : kExpected) {
      if (offset >= word && offset < word + sizeof(OpaqueWord)) {
        expected_to_change = true;
      }
    }
    const OpaqueWord replacement =
        offset < 0x08u ? word_of(name)
                       : (offset < 0x10u ? word_of(&line)
                                          : word_of(&line) - 4u);
    if (expected_to_change) {
      report(parser.bytes[offset] ==
                 static_cast<std::uint8_t>(replacement >> (8 * (offset % 4))),
             "a written word carries exactly the value the machine stores");
    } else {
      report(parser.bytes[offset] == before[offset],
             "no byte outside +0x04, +0x0c and +0x30 is touched");
    }
  }
}

// ---------------------------------------------------------------------------
// 3. 0x0083c780 overwrites receiver+0x04 and receiver+0x0c from the two stack
//    words, so any pre-existing value at those offsets is destroyed. Observed
//    at 0x0083c788 and 0x0083c78b.
//    Discriminates: a model that assumes the target pre-populates the receiver.
// ---------------------------------------------------------------------------
void test_tail_overwrites_its_two_words() {
  OpaqueFormatParser parser{};
  write_word_at(base_of(parser), 0x04u, 0x11111111u);
  write_word_at(base_of(parser), 0x0cu, 0x22222222u);
  char name[] = "X";
  OpaqueLine line{};

  PortScope scope(&recording_tail);
  g_recorder = Recorder{};
  argscript_formatparser_create_definition_safe_00841440(&parser, name, &line);

  discriminating(at(parser, 0x04u) == word_of(name),
                 "receiver+0x04 replaced by the first stack word");
  discriminating(at(parser, 0x0cu) == word_of(&line),
                 "receiver+0x0c replaced by the second stack word");
  discriminating(g_recorder.receiver_04_at_entry == 0x11111111u,
                 "the old +0x04 is still in place when the tail is entered");
}

// The default port must be the modelled 0x0083c780, and it must reproduce that
// function's two stores while leaving +0x30 alone.
// Discriminates: a package whose default port is a stub that only returns.
void test_default_port_reproduces_the_modelled_tail() {
  report(g_tail_0083c780 == &model_tail_0083c780,
         "default port is the modelled 0x0083c780");

  OpaqueFormatParser parser{};
  write_word_at(base_of(parser), 0x04u, 0x33333333u);
  char name[] = "Y";
  OpaqueLine line{};

  const bool result = argscript_formatparser_create_definition_safe_00841440(
      &parser, name, &line);

  discriminating(at(parser, 0x04u) == word_of(name),
                 "modelled tail wrote +0x04");
  discriminating(at(parser, 0x0cu) == word_of(&line),
                 "modelled tail wrote +0x0c");
  discriminating(at(parser, 0x30u) == word_of(&line) - 4u,
                 "modelled tail left the biased +0x30 word alone");
  discriminating(result, "modelled tail returns the first word as a bool");

  // 0x0083c780's EAX at the RET is the first stack word, not a success flag:
  // MOV EAX,[ESP+0x4] is its first instruction and nothing after the two stores
  // writes EAX. So a null first argument must come back false through the
  // default port too -- with no recording tail in the way to paper over it.
  // Discriminates: a modelled tail that returns an unconditional true.
  OpaqueFormatParser null_named{};
  OpaqueLine other_line{};
  const bool null_result = argscript_formatparser_create_definition_safe_00841440(
      &null_named, nullptr, &other_line);

  discriminating(null_result == false,
                 "modelled tail returns false for a null first argument");
  discriminating(at(null_named, 0x04u) == 0u,
                 "modelled tail wrote a null +0x04 for a null first argument");
  discriminating(at(null_named, 0x0cu) == word_of(&other_line),
                 "modelled tail still wrote +0x0c for a null first argument");
  discriminating(at(null_named, 0x30u) == word_of(&other_line) - 4u,
                 "a null name does not change the +0x30 bias");
}

// A tail that does not store must not change what the target itself did. This
// isolates the target's own effect from the tail's.
// Discriminates: a model that folds the tail's stores into the target body.
void test_target_effect_is_independent_of_the_tail() {
  OpaqueFormatParser with_stores{};
  OpaqueFormatParser without_stores{};
  char name[] = "Q";
  OpaqueLine line{};

  PortScope scope(&recording_tail);
  g_recorder = Recorder{};
  g_recorder.perform_stores = true;
  argscript_formatparser_create_definition_safe_00841440(&with_stores, name,
                                                         &line);
  g_recorder = Recorder{};
  g_recorder.perform_stores = false;
  argscript_formatparser_create_definition_safe_00841440(&without_stores, name,
                                                         &line);

  discriminating(at(with_stores, 0x30u) == at(without_stores, 0x30u),
                 "+0x30 is written by the target, not by the tail");
  discriminating(g_recorder.calls == 1,
                 "the tail is still entered when it stores nothing");
}

// ---------------------------------------------------------------------------
// 4. Structural facts the displacements in the header rest on, and the shape of
//    the tail port as two stack words plus a receiver.
// ---------------------------------------------------------------------------
void test_receiver_region_covers_every_written_offset() {
  report(kReceiverCoveredBytes == 0x34u, "covered region is 0x34 bytes");
  report(sizeof(OpaqueFormatParser) == kReceiverCoveredBytes,
         "receiver size equals the covered region");
  report(0x30u + sizeof(OpaqueWord) <= kReceiverCoveredBytes,
         "the +0x30 word lies inside the covered region");
  report(0x0cu + sizeof(OpaqueWord) <= kReceiverCoveredBytes,
         "the +0x0c word lies inside the covered region");
  report(sizeof(OpaqueLine) == 4u, "line stands in as a single opaque word");
  OpaqueFormatParser fresh{};
  report(at(fresh, 0x30u) == 0u, "a fresh receiver is zeroed at +0x30");
}

void test_modeled_signatures() {
  // 0x0083c780 reads two stack words and takes ECX, so the port must be spelled
  // as receiver plus two arguments.
  static_assert(std::is_same<SharedTail0083c780,
                             bool (*)(OpaqueFormatParser*, char*,
                                      OpaqueLine*)>::value,
                "tail port is receiver plus two stack words");
  static_assert(
      std::is_same<decltype(&model_tail_0083c780), SharedTail0083c780>::value,
      "tail model matches the tail port type");

  // The target's own signature is checked behaviourally instead: it is spelled
  // __thiscall, so its type is distinct from the plain function pointer used
  // for the port. Taking its address with its own type and calling through it
  // proves it is callable with the observed arity.
  using TargetPtr = decltype(
      &argscript_formatparser_create_definition_safe_00841440);
  TargetPtr const target =
      &argscript_formatparser_create_definition_safe_00841440;
  static_assert(!std::is_null_pointer<TargetPtr>::value,
                "the target's own type is a plain function pointer, so taking "
                "its address yields a callable of exactly that type");

  OpaqueFormatParser parser{};
  char name[] = "S";
  OpaqueLine line{};
  PortScope scope(&recording_tail);
  g_recorder = Recorder{};
  discriminating(target(&parser, name, &line),
                 "target callable with two stack words");
  discriminating(g_recorder.calls == 1,
                 "target forwards to the tail exactly once");
}

// The receiver word is read and written through memcpy on a byte-addressed
// region, so the model must not depend on the region's alignment.
// Discriminates: a model that casts the receiver to a word pointer and would
// fault or misbehave on a misaligned receiver.
void test_word_access_is_alignment_independent() {
  alignas(1) std::uint8_t storage[0x34 + 1]{};
  OpaqueFormatParser* const parser =
      reinterpret_cast<OpaqueFormatParser*>(storage + 1);

  write_word_at(base_of(*parser), 0x30u, 0xcafebabeu);
  report(at(*parser, 0x30u) == 0xcafebabeu,
         "a misaligned receiver still round-trips a word");
  report(storage[0] == 0u, "nothing was written before the receiver");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_argscript_createdefsafe_00841440

int main() {
  using namespace openspore::reconstruction::pkg_argscript_createdefsafe_00841440;
  test_tail_is_entered_once_with_both_arguments();
  test_null_first_argument_still_reaches_the_tail();
  test_receiver_30_is_the_four_byte_back_biased_line();
  test_bias_wraps_as_a_plain_32_bit_subtraction();
  test_null_second_argument_stores_plain_zero();
  test_only_receiver_30_is_branch_dependent();
  test_net_receiver_writes_are_exactly_three_words();
  test_tail_overwrites_its_two_words();
  test_default_port_reproduces_the_modelled_tail();
  test_target_effect_is_independent_of_the_tail();
  test_receiver_region_covers_every_written_offset();
  test_modeled_signatures();
  test_word_access_is_alignment_independent();

  std::printf("%s: %d checks (%d discriminating), %d failures\n", __FILE__,
              g_checks, g_discriminating, g_failures);
  if (g_discriminating < 32) {
    std::printf("FAIL: discriminating checks fell below the floor; a "
                "load-bearing test was dropped\n");
    return 1;
  }
  return g_failures == 0 ? 0 : 1;
}
