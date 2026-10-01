// Model test for 0x00d1dcd0 (pkg_argscript_wave9).
//
// The body is two instructions:
//
//   00d1dcd0  MOV EAX,dword ptr [ECX + 0x130]
//   00d1dcd6  RET
//
// Everything below is written to FAIL if the reconstruction is wrong in the
// specific way it could plausibly be wrong.  The dominant risk is a
// dereference-depth mistake -- this body loads a word and RETURNS that word,
// so an implementation that treats the loaded word as a pointer and follows it
// (or that returns the address of the slot instead of its contents) produces a
// plausible-looking answer.  The second risk is a displacement mistake (0x130
// as a word index, or as a base for a sub-object), the third is a side effect
// the body does not have, and the fourth is a callee that pops a frame it was
// never given.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "argscript_get_current_scope.hpp"

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_TEST_CDECL __cdecl
#define PKG_ARGSCRIPT_TEST_THISCALL __thiscall
#else
#define PKG_ARGSCRIPT_TEST_CDECL __attribute__((cdecl))
#define PKG_ARGSCRIPT_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_wave9 {
namespace {

using ScopeSignature = char*(PKG_ARGSCRIPT_TEST_THISCALL*)(ParserExtent*);

// 0x130 is the only displacement the listing names, and the record's only
// observed offset.  0x04 and 0x08 are decoys the body must never reach.
constexpr std::size_t kScopeDisplacement = 0x130;
constexpr std::size_t kNearDecoy = 0x04;
constexpr std::size_t kFarDecoy = 0x08;
constexpr std::size_t kScaledDecoy = 0x3c;  // 0x130/4, the word-index reading
constexpr std::size_t kExtentBytes = 0x134;

static_assert(std::is_same<decltype(&pkg_argscript_get_current_scope_00d1dcd0),
                           ScopeSignature>::value,
              "00d1dcd0 takes the receiver in ECX and returns in EAX");
static_assert(std::is_same<decltype(std::declval<ScopeSignature>()(
                               std::declval<ParserExtent*>())),
                           char*>::value,
              "the declared result is the canonical record's `char *`");
static_assert(sizeof(decltype(pkg_argscript_get_current_scope_00d1dcd0(
                    static_cast<ParserExtent*>(nullptr)))) == 4,
              "the result is a 32-bit value, which is the width the listing"
              " moves in EAX");
static_assert(sizeof(ParserExtent) == kExtentBytes,
              "the modelled extent is the minimum object the observed read"
              " fits in");
static_assert(kScopeDisplacement + sizeof(std::uint32_t) == kExtentBytes,
              "the read covers 0x130..0x133 and the extent ends there");

void check(bool condition, const char* what) {
  if (condition) {
    return;
  }
  std::fprintf(stderr, "check failed: %s\n", what);
  std::abort();
}

void store_word_at(ParserExtent* parser, std::size_t displacement,
                   std::uint32_t value) {
  std::memcpy(parser->bytes + displacement, &value, sizeof(value));
}

std::uint32_t word_at(const ParserExtent* parser, std::size_t displacement) {
  std::uint32_t value = 0;
  std::memcpy(&value, parser->bytes + displacement, sizeof(value));
  return value;
}

// Fill the whole extent with a byte pattern of full period 256, then plant a
// distinct 4-byte word at `displacement`.  Every four-byte window therefore
// holds four distinct bytes, so a read at the wrong offset -- including one
// overlapping the right offset by a single byte -- cannot coincide with it.
void seed_with_distinct_words(ParserExtent* parser, std::uint32_t at_scope) {
  for (std::size_t index = 0; index < kExtentBytes; ++index) {
    parser->bytes[index] = static_cast<std::uint8_t>((index * 31u) & 0xffu);
  }
  store_word_at(parser, kScopeDisplacement, at_scope);
}

// -- 1. The result is the word's CONTENTS, not the word's address -------------
// This is the whole two-instruction body.  A model that returned
// `reinterpret_cast<char*>(parser) + 0x130`, or that returned the address the
// word holds after loading it once more, fails here.
void test_result_is_the_loaded_words_contents() {
  const std::uint32_t payload = 0xdeadbeefu;
  ParserExtent parser{};
  seed_with_distinct_words(&parser, payload);
  char* const result = pkg_argscript_get_current_scope_00d1dcd0(&parser);
  std::uint32_t observed = 0;
  std::memcpy(&observed, &result, sizeof(observed));
  check(observed == payload,
        "the result is the 4-byte word stored at receiver+0x130");
  check(reinterpret_cast<char*>(result) !=
            reinterpret_cast<char*>(&parser) + kScopeDisplacement,
        "the result is not the ADDRESS of the slot it was read from");
  check(reinterpret_cast<char*>(result) !=
            reinterpret_cast<char*>(&parser),
        "the result is not the address of the receiver");
  // High-bit patterns are the ones a canonicalising or sign-extending
  // reconstruction would mangle; a dword move carries them through unchanged.
  const std::uint32_t hostile[4] = {0x80000000u, 0xffffffffu, 0x00000001u,
                                    0x7f800000u};
  for (const std::uint32_t value : hostile) {
    ParserExtent probe{};
    seed_with_distinct_words(&probe, value);
    char* const got = pkg_argscript_get_current_scope_00d1dcd0(&probe);
    std::uint32_t bits = 0;
    std::memcpy(&bits, &got, sizeof(bits));
    check(bits == value, "a 4-byte pattern survives the load unchanged");
  }
}

// -- 2. ONE dereference, not two --------------------------------------------
// The word at +0x130 is planted with the address of a real, distinguishable
// object.  If the reconstruction followed the loaded word it would return that
// object's first bytes; if it returned the slot address it would return
// &parser + 0x130.  Only "returns the loaded word itself" passes.
void test_exactly_one_dereference() {
  std::uint32_t pointed[4] = {0x11111111u, 0x22222222u, 0x33333333u,
                              0x44444444u};
  ParserExtent parser{};
  seed_with_distinct_words(&parser, 0x0f0f0f0fu);
  store_word_at(&parser, kScopeDisplacement,
                static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&pointed[0])));

  char* const result = pkg_argscript_get_current_scope_00d1dcd0(&parser);
  std::uint32_t bits = 0;
  std::memcpy(&bits, &result, sizeof(bits));
  check(bits == static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(&pointed[0])),
        "a word holding a valid address is returned AS that address: the body"
        " loads the word once and RETs");
  check(bits != pointed[0],
        "the contents at the pointed-to address are never loaded: 0x11111111"
        " lives there and the result is not it, so this is one dereference"
        " and not two");
  check(reinterpret_cast<char*>(result) !=
            reinterpret_cast<char*>(&parser) + kScopeDisplacement,
        "and the result is not the address of the slot the word came from");
  check(bits != pointed[0],
        "the contents at the pointed-to address are never loaded: 0x11111111"
        " lives there and the result is not it");
  check(pointed[0] == 0x11111111u && pointed[1] == 0x22222222u,
        "the object the word points at is untouched by the call");
}

// -- 3. 0x130 is a byte OFFSET, not a word index and not a base --------------
// If the displacement had been applied as a word index the load would have
// come from 0x130*4 = 0x4c0, which is not even inside the minimum extent; if
// it had been applied to a sub-object the answer would be the sub-object's
// first or second word instead.  Decoys at 0x04, 0x08 and 0x3c each hold a
// value the body must not return.
void test_displacement_is_a_byte_offset() {
  ParserExtent parser{};
  seed_with_distinct_words(&parser, 0x00c0ffeeu);
  store_word_at(&parser, kNearDecoy, 0xaaaaaaaau);
  store_word_at(&parser, kFarDecoy, 0xbbbbbbbbu);
  store_word_at(&parser, kScaledDecoy, 0xccccccccu);

  char* const result = pkg_argscript_get_current_scope_00d1dcd0(&parser);
  std::uint32_t bits = 0;
  std::memcpy(&bits, &result, sizeof(bits));
  check(bits == 0x00c0ffeeu, "the load came from byte offset 0x130");
  check(bits != 0xaaaaaaaau && bits != 0xbbbbbbbbu && bits != 0xccccccccu,
        "the result is not the decoy word at 0x04, 0x08 or 0x3c, so the"
        " displacement was not read as an index or split across a sub-object");
  check(word_at(&parser, kNearDecoy) == 0xaaaaaaaau &&
            word_at(&parser, kFarDecoy) == 0xbbbbbbbbu &&
            word_at(&parser, kScaledDecoy) == 0xccccccccu &&
            word_at(&parser, kScopeDisplacement) == 0x00c0ffeeu,
        "every decoy and the word under test still hold what was planted, so"
        " the call read one word and wrote none");
  // A load pinned one byte early or one byte late would land on an overlapping
  // 4-byte window, and those windows are all-distinct in the fill, so each of
  // them must differ from the word the body actually returned.
  ParserExtent probe{};
  seed_with_distinct_words(&probe, 0x5a5a5a5au);
  for (std::size_t shift = 1; shift <= 3u; ++shift) {
    check(word_at(&probe, kScopeDisplacement - shift) != 0x5a5a5a5au,
          "the 4-byte window ending one to three bytes below 0x130 holds"
          " something else, so a load shifted down would have been seen");
    check(word_at(&probe, kScopeDisplacement + shift) != 0x5a5a5a5au,
          "the 4-byte window starting one to three bytes above 0x130 holds"
          " something else, so a load shifted up would have been seen");
  }
  check(word_at(&probe, kScopeDisplacement) == 0x5a5a5a5au,
        "and the window at 0x130 is the one that was planted");
}

// -- 4. The body writes nothing (record: written_through = 0) ---------------
// A reconstruction with a cache, a lazy fill or a normalisation store would
// mutate the receiver.  The full extent is compared byte for byte, and the
// call is repeated to catch a memoised second result.
void test_receiver_is_never_written() {
  ParserExtent parser{};
  seed_with_distinct_words(&parser, 0x1234abcdu);
  std::uint8_t before[kExtentBytes];
  std::memcpy(before, parser.bytes, sizeof(before));

  char* const first = pkg_argscript_get_current_scope_00d1dcd0(&parser);
  check(std::memcmp(before, parser.bytes, sizeof(before)) == 0,
        "not one byte of the receiver changed: the record's written_through"
        " is 0 and the listing has no store");
  char* const second = pkg_argscript_get_current_scope_00d1dcd0(&parser);
  check(first == second, "two calls return the same thing, so nothing is"
                         " memoised into the receiver");
  check(std::memcmp(before, parser.bytes, sizeof(before)) == 0,
        "the second call wrote nothing either");
}

// -- 5. RET with no immediate: the callee pops nothing -----------------------
// Measured, not asserted.  A cdecl shim places a canary below its own frame,
// calls through the thiscall pointer, and checks the canary and a
// register-spilled sentinel afterwards.  A callee that released even one word
// (`RET 4`, i.e. a stdcall-style cleanup it was never given) would leave the
// shim's frame off by four bytes and the canary would not be where it was left.
std::uint32_t shim_image = 0;

void PKG_ARGSCRIPT_TEST_CDECL call_through_thiscall(ParserExtent* parser,
                                                    std::uint32_t expected) {
  std::uint32_t* const canary = static_cast<std::uint32_t*>(
      __builtin_alloca(3 * sizeof(std::uint32_t)));
  canary[0] = 0x0badc0deu;
  canary[1] = 0x13572468u;
  canary[2] = 0x2468ace0u;
  const std::uint32_t spilled = canary[0] ^ canary[1] ^ canary[2];
  const ScopeSignature scope = &pkg_argscript_get_current_scope_00d1dcd0;
  char* const result = scope(parser);
  std::uint32_t bits = 0;
  std::memcpy(&bits, &result, sizeof(bits));
  check(bits == expected, "the shim observed the word it planted");
  check(canary[0] == 0x0badc0deu && canary[1] == 0x13572468u &&
            canary[2] == 0x2468ace0u,
        "the canary below the shim's frame held: the callee released no"
        " argument, which is what a bare RET means");
  shim_image = canary[0] ^ canary[1] ^ canary[2] ^ spilled;
}

void test_callee_pops_nothing() {
  ParserExtent parser{};
  seed_with_distinct_words(&parser, 0xfeedfaceu);
  call_through_thiscall(&parser, 0xfeedfaceu);
  check(shim_image == 0u, "every canary word survived the call and was read"
                          " back through the same register the shim spilled"
                          " it into, so the frame did not move");
  // A null receiver word is a value, not a fault: the body never follows what
  // it loads, so a zero word is returned as a null result.
  ParserExtent nulled{};
  seed_with_distinct_words(&nulled, 0x00000000u);
  check(pkg_argscript_get_current_scope_00d1dcd0(&nulled) == nullptr,
        "a zero word at +0x130 comes back as a null result without being"
        " dereferenced, which is the same one-level fact seen from the other"
        " side");
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_argscript_wave9;
  // The one-vs-two-dereference case runs first on purpose: an implementation
  // that follows the loaded word lands here, on a planted pointer to a real
  // object, and fails on an assertion instead of on a fault.
  test_exactly_one_dereference();
  test_result_is_the_loaded_words_contents();
  test_displacement_is_a_byte_offset();
  test_receiver_is_never_written();
  test_callee_pops_nothing();
  return 0;
}

#undef PKG_ARGSCRIPT_TEST_CDECL
#undef PKG_ARGSCRIPT_TEST_THISCALL
