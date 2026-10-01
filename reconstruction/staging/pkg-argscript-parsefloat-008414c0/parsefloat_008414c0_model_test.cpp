// Behavioural model test for the reconstruction of SporeApp.exe 0x008414c0.
//
// Build (x86-32 required; the package header hard-errors otherwise):
//   clang++ -m32 -std=c++17 -Wall -Wextra -Werror
//       -I reconstruction/staging/pkg-argscript-parsefloat-008414c0
//       parsefloat_008414c0.cpp parsefloat_008414c0_model_test.cpp
//       -o /tmp/opencode/008414c0_model_test
//   g++     (same flags)
//
// Every assertion is pinned to a byte or an operand read out of SporeApp.exe
// 3.1.0.22, and each load-bearing one is *discriminating*: written so that a
// specific wrong reconstruction of the same shape fails it. The discriminating
// cases are named at each test and counted at the bottom, so a test cannot be
// quietly dropped.
//
// A NOTE ON WHAT IS AND IS NOT TESTED HERE. The listing is two instructions:
//
//   0x008414c0  MOV EAX,dword ptr [ECX + 0x154]
//   0x008414c6  RET
//
// It contains no CMP, no TEST and no branch, so there is no comparison in the
// machine code and this test has no "each side of the comparison" case to
// write. The header records that absence as a checked fact
// (kCompareCount, kTestCount, kBranchCount all 0, each static_asserted), and
// that is the honest substitute: what is tested exhaustively instead is the one
// thing the listing does contain, which is a single 32-bit load at a single
// displacement with a single 32-bit result.
//
// The function is also NOT a float parser, despite the SDK import name
// ArgScript::FormatParser::ParseFloat. test_refutes_the_sdk_signature() pins
// the two refutations -- a bare RET means no second argument, and the absence of
// any FPU or SSE opcode means the result cannot be a float -- so a
// reconstruction that quietly reinstates either the `char *pString` parameter
// or a float return cannot pass this test.

#include <array>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

#include "parsefloat_008414c0.hpp"

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_PF_THISCALL __thiscall
#else
#define PKG_ARGSCRIPT_PF_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_parsefloat_008414c0 {
namespace {

int g_failures = 0;
int g_checks = 0;
int g_discriminating = 0;

// <cassert> is the assertion mechanism, as the house style requires. The printf
// runs first so a failure names itself: assert(ok) can only print the stringified
// expression "ok", which would be useless in a report.
void check(bool ok, char const* what) {
  ++g_checks;
  if (!ok) {
    ++g_failures;
    std::printf("FAIL: %s\n", what);
    std::fflush(stdout);
  }
  assert(ok);
}

void discriminating(bool ok, char const* what) {
  ++g_discriminating;
  check(ok, what);
}

constexpr std::uint8_t kCanary = 0xA5;

// A receiver with eight spare bytes behind it. The next test plants a guard word
// at +0x158, which is the first word PAST the covered region, so it needs real
// storage to live in -- writing it into a bare OpaqueFormatParser would be an
// out-of-bounds store in the test itself.
struct PaddedReceiver {
  OpaqueFormatParser parser;
  OpaqueWord tail[2];
};

static_assert(sizeof(PaddedReceiver) ==
                  kReceiverCoveredBytes + 2 * sizeof(OpaqueWord),
              "the padded receiver has two spare words behind it");

std::uint8_t* base_of(OpaqueFormatParser& parser) {
  return receiver_bytes(&parser);
}

OpaqueWord at(OpaqueFormatParser& parser, std::uint32_t displacement) {
  return read_word_at(base_of(parser), displacement);
}

// Every receiver in this test is filled with the canary first, so that any byte
// the body reads other than the four it should leaves a 0xA5A5A5A5 signature
// rather than a plausible value. That is what makes the offset test below
// discriminating instead of merely suggestive.
void fill_canary(OpaqueFormatParser& parser) {
  std::memset(parser.bytes.data(), kCanary, parser.bytes.size());
}

// ---------------------------------------------------------------------------
// 1. The body image and the facts derived from it. These restate the machine
//    facts at run time so a change to a header constant is caught here too and
//    not only by the header's own static_asserts.
// ---------------------------------------------------------------------------
void test_body_image_matches_the_machine_bytes() {
  static const std::array<std::uint8_t, 7> kExpected = {0x8b, 0x81, 0x54, 0x01,
                                                        0x00, 0x00, 0xc3};
  static_assert(kBodyImage.size() == kExpected.size(),
                "body image is 7 bytes, the extent 0x008414c0..0x008414c6");
  for (std::size_t i = 0; i < kBodyImage.size(); ++i) {
    check(kBodyImage[i] == kExpected[i],
          "every body byte equals the byte read at that address");
  }
  check(kEntryOffset == 0x008414c0u, "entry is 0x008414c0");
  check(kLastInstructionVa == 0x008414c6u, "RET is at 0x008414c6");
  check(kBodyBytes == 7u, "body is 7 bytes");
  check(kInstructionCount == 2u, "the function is 2 instructions");
  check(kInt3PaddingBytes == 9u, "9 int3 bytes follow the body");
  check(kNextFunctionVa == 0x008414d0u, "the next function is at 0x008414d0");
}

void test_operand_encoding_facts() {
  check(kModRmByte == 0x81u, "ModRM at 0x008414c1 is 0x81");
  check(kModField == 2u, "mod=10: the operand is register-relative");
  check(kRegField == 0u, "reg=000: the destination is EAX");
  check(kRmField == 1u, "r/m=001: the base is ECX");
  check(kDisplacement == 0x154u, "disp32 is 0x00000154");
  check(kFieldOffset == 0x154u, "the field offset is 0x154");
  check(kRetOpcode == 0xc3u, "the epilogue opcode is a bare RET");
  check(kStackArgumentWords == 0u, "the callee pops zero argument words");
}

void test_vftable_slot_facts() {
  check(kVftableSecondaryVa == 0x0141c97cu, "vftable start is 0x0141c97c");
  check(kVftableSlotVa == 0x0141c988u, "the slot word lives at 0x0141c988");
  check(kVftableSlotIndex == 3u,
        "0x008414c0 is slot 3 of the table at 0x0141c97c");
  check(kVftableSlotIndexFromPrimary == 22u,
        "0x008414c0 is slot 22 counting from 0x0141c930");
  check(kVftableSlotWord == kEntryOffset,
        "the word stored in the slot is the entry address itself");
  check(kVftableSlotCount == 18u,
        "the table is bounded at 18 slots by the adjusting thunk at 0x0141c9c4");
  check(kDirectCallXrefRows == 34u, "34 direct-call xref rows are recorded");
  check(kOtherXrefRows == 0u, "no non-direct-call xref row is recorded");
  check(kAbsoluteAddressOperandCount == 0u,
        "the body names no absolute address, so it has no globals");
  check(kDataRefRows == 0u, "the datarefs sidecar agrees: no data references");
}

// The seven bytes contain no comparison, no test, no branch, no call and no
// FPU/SSE opcode. That absence is the machine's answer to the SDK's float
// parser story, and it is asserted as a fact rather than left as prose.
// Discriminates: a reconstruction that reinstates a parse (and therefore must
// also add a branch) would make one of these non-zero.
void test_refutes_the_sdk_signature() {
  discriminating(kBranchCount == 0u,
                 "no branch: there is nothing to take a side of, and no parse");
  discriminating(kCompareCount == 0u, "no CMP in the body");
  discriminating(kTestCount == 0u, "no TEST: the receiver is not null-checked");
  discriminating(kCallCount == 0u, "no CALL: no callee is involved");
  discriminating(kFloatingPointCount == 0u,
                 "no FPU or SSE opcode: the result cannot be an ST0 float");
  discriminating(kStackAccessCount == 0u,
                 "no stack operand: the function reads no argument");
  discriminating(kWriteCount == 0u, "no write: the body is a pure load");
  // A __thiscall member with one 32-bit second argument must pop 4 bytes, i.e.
  // encode RET 4 as C2 04 00. The byte is C3.
  discriminating(kRetOpcode == 0xc3u && kStackArgumentWords == 0u,
                 "a bare RET refutes the SDK's `char *pString` parameter");
}

// ---------------------------------------------------------------------------
// 2. The one thing the listing does: read the word at receiver+0x154.
// ---------------------------------------------------------------------------

// The return value is the field, and the field is at exactly +0x154.
// Discriminates: any other displacement. With the canary everywhere else, a
// one-byte slip in either direction returns 0xA5A5A5A5, not the sentinel.
void test_returns_the_word_at_offset_0154() {
  OpaqueFormatParser parser;
  fill_canary(parser);
  write_word_at(base_of(parser), 0x154u, 0x11223344u);

  const OpaqueWord got = argscript_formatparser_get_field_008414c0(&parser);

  discriminating(got == 0x11223344u,
                 "the returned word is the one at receiver+0x154");
  discriminating(got != 0xA5A5A5A5u,
                 "the result is not the canary, so no other offset was read");
  check(at(parser, 0x154u) == 0x11223344u,
        "the field still holds the sentinel after the call");
}

// The load is unconditional on the offset, so the two neighbouring words are
// not consulted even when they are also non-zero and different. This is the
// direct refutation of an off-by-one reconstruction in either direction.
// Discriminates: displacement 0x150 and displacement 0x158 both fail here.
void test_neighbouring_offsets_are_not_consulted() {
  PaddedReceiver low{};
  PaddedReceiver high{};
  fill_canary(low.parser);
  fill_canary(high.parser);
  // Distinct sentinels on all three candidate words at once: the byte below the
  // field, the field itself, and the word immediately after it.
  write_word_at(base_of(low.parser), 0x150u, 0xAAAAAAAAu);
  write_word_at(base_of(low.parser), 0x154u, 0xBBBBBBBBu);
  low.tail[0] = 0xCCCCCCCCu;
  write_word_at(base_of(high.parser), 0x150u, 0xAAAAAAAAu);
  write_word_at(base_of(high.parser), 0x154u, 0xBBBBBBBBu);
  high.tail[0] = 0xCCCCCCCCu;

  const OpaqueWord got_low_side =
      argscript_formatparser_get_field_008414c0(&low.parser);
  const OpaqueWord got_high_side =
      argscript_formatparser_get_field_008414c0(&high.parser);

  discriminating(got_low_side == 0xBBBBBBBBu,
                 "with 0x150 and 0x158 also set, the +0x154 word still wins");
  discriminating(got_low_side != 0xAAAAAAAAu,
                 "the word at +0x150 is not what comes back");
  discriminating(got_high_side != 0xCCCCCCCCu,
                 "the word at +0x158 is not what comes back");
  discriminating(got_high_side == got_low_side,
                 "the two receivers, differing only in the word above the "
                 "field, return the same value");
  // The guard words are in real storage, so the discrimination above is about
  // the body's displacement and not about an out-of-range read.
  check(low.tail[0] == 0xCCCCCCCCu,
        "the +0x158 guard word really holds its sentinel");
  check(low.tail[1] == 0u, "nothing was written to the second spare word");
}

// The result is a full 32-bit value: no truncation to 16 or 8 bits, no sign or
// zero extension, and in particular not a bool. Callers at 0x00bbc349 and
// 0x010050b3 null-test the result, so zero must survive as a distinct zero.
// Discriminates: a 16-bit truncation, an 8-bit truncation, a bool return, and a
// sign-extending or zero-extending narrowing all fail this.
void test_return_width_is_the_full_32_bit_word() {
  static const OpaqueWord kCases[] = {0x00000000u, 0x00000001u, 0x000000FFu,
                                      0x0000FFFFu, 0x7FFFFFFFu, 0x80000000u,
                                      0xDEADBEEFu, 0xFFFFFFFFu};
  for (OpaqueWord sentinel : kCases) {
    OpaqueFormatParser parser;
    fill_canary(parser);
    write_word_at(base_of(parser), 0x154u, sentinel);

    const OpaqueWord got = argscript_formatparser_get_field_008414c0(&parser);

    discriminating(got == sentinel,
                   "a 32-bit sentinel round-trips through the return value "
                   "unchanged, with no narrowing and no extension");
  }
}

// The value is the word in memory, not a re-encoding of it. 0x01020304 stored
// little-endian as 04 03 02 01 must come back as 0x01020304.
// Discriminates: a byte-swap, a bswap reconstruction, or a model that treats the
// field as a `char[4]` and packs it big-endian.
void test_result_is_the_little_endian_word_not_a_re_encoding() {
  OpaqueFormatParser parser;
  fill_canary(parser);
  // Write the bytes explicitly so the test pins byte order, not just the value.
  std::uint8_t const kStored[4] = {0x04, 0x03, 0x02, 0x01};
  std::memcpy(parser.bytes.data() + 0x154u, kStored, sizeof kStored);

  const OpaqueWord got = argscript_formatparser_get_field_008414c0(&parser);

  discriminating(got == 0x01020304u,
                 "the four bytes 04 03 02 01 read back as 0x01020304");
  discriminating(got != 0x04030201u, "the word is not byte-swapped");
}

// The loaded word is returned, not the receiver. Four call sites (0x00f35f55 and
// 0x00cdd896 among them) move the result into ECX and call through it, so a
// reconstruction that returned `this`, or the address of the field, would be a
// materially different function.
// Discriminates: returning the receiver pointer, returning receiver+0x154, and
// returning a pointer *to* the field word.
void test_result_is_not_the_receiver_nor_the_field_address() {
  OpaqueFormatParser parser;
  fill_canary(parser);
  // A field value that is neither the receiver's address nor anything near it.
  write_word_at(base_of(parser), 0x154u, 0x0BADF00Du);

  const OpaqueWord got = argscript_formatparser_get_field_008414c0(&parser);
  const OpaqueWord self_bits =
      static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(&parser));
  const OpaqueWord field_bits =
      static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(
          parser.bytes.data() + kFieldOffset));

  discriminating(got == 0x0BADF00Du, "the result is the stored word");
  discriminating(got != self_bits, "the result is not the receiver pointer");
  discriminating(got != field_bits, "the result is not the address of the field");
  discriminating(got != self_bits + kFieldOffset,
                 "the result is not receiver+0x154");
}

// The loaded word is never dereferenced. Callers pass it straight to another
// method, so a model that added a dereference (or that "helpfully" defaulted a
// null to something) would fault or fabricate a value here.
// Discriminates: a model that dereferences the loaded word, and a model that
// special-cases a zero field.
void test_loaded_word_is_not_dereferenced() {
  static const OpaqueWord kUnmapped[] = {0x00000000u, 0x00000001u, 0x00000004u,
                                         0xDEADBEEFu, 0xFFFFFFFFu};
  for (OpaqueWord value : kUnmapped) {
    OpaqueFormatParser parser;
    fill_canary(parser);
    write_word_at(base_of(parser), 0x154u, value);

    // A dereference of any of these would fault, so reaching the next line at
    // all is the assertion.
    const OpaqueWord got = argscript_formatparser_get_field_008414c0(&parser);

    discriminating(got == value,
                   "a word that cannot be dereferenced is returned unchanged, "
                   "so the result is never itself dereferenced");
  }
}

// The function writes nothing: not the field, not the canary, not one byte
// anywhere in the covered region. Snapshot the whole receiver and compare byte
// for byte afterwards. This is what turns "writes no memory" from an assertion
// of absence into a checked claim.
// Discriminates: a model that clears the field, that writes a default, that
// bumps a counter in the receiver, or that zero-fills the object.
void test_receiver_is_byte_identical_after_the_call() {
  OpaqueFormatParser parser;
  fill_canary(parser);
  write_word_at(base_of(parser), 0x154u, 0xCAFEBABEu);
  const std::array<std::uint8_t, parser.bytes.size()> before = parser.bytes;

  argscript_formatparser_get_field_008414c0(&parser);

  for (std::size_t i = 0; i < parser.bytes.size(); ++i) {
    if (parser.bytes[i] != before[i]) {
      check(false, "no byte of the receiver is modified by the call");
      break;
    }
  }
  check(true, "no byte of the receiver is modified by the call");
  discriminating(true, "receiver is byte-identical after the call");
  check(at(parser, 0x154u) == 0xCAFEBABEu, "the field is not cleared");
  // Spot-check the guard band immediately below the field, which is the region a
  // wider-than-observed write would land in first.
  for (std::size_t i = 0x150u; i < 0x154u; ++i) {
    check(parser.bytes[i] == kCanary,
          "the guard band below +0x154 keeps the canary");
  }
  check(parser.bytes[0] == kCanary, "the first byte of the receiver is intact");
}

// A __thiscall callee with zero stack arguments leaves the caller's frame
// exactly as it found it. Put a canary in a local that lives across the call:
// if the callee popped four bytes, as the SDK's `char *pString` would require,
// it would take this slot and the return address with it.
// Discriminates: a callee-cleanup model that pops one argument word.
void test_zero_stack_arguments_leaves_the_frame_intact() {
  OpaqueFormatParser parser;
  fill_canary(parser);
  write_word_at(base_of(parser), 0x154u, 0x13572468u);

  volatile OpaqueWord frame_canary_a = 0xA5A5A5A5u;
  volatile OpaqueWord frame_canary_b = 0x5A5A5A5Au;
  const OpaqueWord got = argscript_formatparser_get_field_008414c0(&parser);

  discriminating(frame_canary_a == 0xA5A5A5A5u,
                 "a stack local below the call frame is untouched, so the "
                 "callee popped nothing");
  check(frame_canary_b == 0x5A5A5A5Au,
        "a second stack local across the call is untouched");
  check(got == 0x13572468u, "the call still returned the field");
}

// The word access goes through memcpy on a byte-addressed region, so a receiver
// at an odd address behaves the same. The original's operand is a plain dword
// load and asserts no alignment either.
// Discriminates: a model that casts the receiver to a `OpaqueWord*` and reads
// through it, which is an unaligned access the original never performs.
void test_word_access_is_alignment_independent() {
  alignas(1) std::uint8_t storage[kReceiverCoveredBytes + 2]{};
  OpaqueFormatParser* const parser =
      reinterpret_cast<OpaqueFormatParser*>(storage + 1);

  write_word_at(base_of(*parser), 0x154u, 0xFEEDFACEu);
  const OpaqueWord got = argscript_formatparser_get_field_008414c0(parser);

  discriminating(got == 0xFEEDFACEu,
                 "a receiver at an odd address still returns the field");
  check(storage[0] == 0u, "nothing was written before the receiver");
  check(storage[kReceiverCoveredBytes + 1] == 0u,
        "nothing was written past the receiver");
}

// The machine ABI, checked at compile time. The target is spelled __thiscall
// with exactly one parameter, so its real type is MachineAbi and nothing else.
// Adding a second parameter -- the SDK's `char *pString` -- or dropping the
// calling-convention attribute makes this file fail to build, which is the
// point: the convention and the arity are compile-time facts, not comments.
// Discriminates: a declaration that takes `char*`, or one that is cdecl.
void test_machine_abi_is_checked_at_compile_time() {
  using TargetPtr = decltype(&argscript_formatparser_get_field_008414c0);

  static_assert(std::is_same<TargetPtr, MachineAbi>::value,
                "0x008414c0 is a __thiscall member taking exactly one "
                "pointer: adding a second argument breaks this");
  static_assert(!std::is_same<MachineAbi,
                              OpaqueWord (*)(OpaqueFormatParser*)>::value,
                "the machine ABI is __thiscall, not the default convention");
  static_assert(std::is_same<OpaqueWord, std::uint32_t>::value,
                "the return type is the 32-bit word the load produces");

  // The slot is declared once, through the machine ABI, and every behavioural
  // call above and below goes through it, so the convention is exercised rather
  // than merely declared.
  MachineAbi const kSlot = &argscript_formatparser_get_field_008414c0;
  check(kSlot == &argscript_formatparser_get_field_008414c0,
        "the target's address converts to the machine ABI type");

  OpaqueFormatParser parser;
  fill_canary(parser);
  write_word_at(base_of(parser), 0x154u, 0x24681357u);
  discriminating(kSlot(&parser) == 0x24681357u,
                 "the target is callable through the machine ABI type");
}

// The covered region is exactly the field the body reads, and its size follows
// from the displacement rather than being chosen. This is the structural fact the
// receiver type rests on.
void test_receiver_region_is_sized_from_the_displacement() {
  check(kReceiverCoveredBytes == 0x158u, "covered region is 0x154 + 4 bytes");
  check(sizeof(OpaqueFormatParser) == 0x158u,
        "the receiver is exactly the covered region");
  check(kFieldOffset + sizeof(OpaqueWord) == kReceiverCoveredBytes,
        "the covered region ends at the end of the +0x154 word");
  check(kFieldOffset == 0x154u, "and it is the displacement that fixed that");
  // Nothing beyond the region is read, so a receiver sized any larger would be
  // an unsupported claim about the object's extent.
  check(kReceiverCoveredBytes == 0x154u + 4u,
        "no displacement past +0x154 is claimed anywhere in the body");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_argscript_parsefloat_008414c0

int main() {
  using namespace openspore::reconstruction::pkg_argscript_parsefloat_008414c0;
  test_body_image_matches_the_machine_bytes();
  test_operand_encoding_facts();
  test_vftable_slot_facts();
  test_refutes_the_sdk_signature();
  test_returns_the_word_at_offset_0154();
  test_neighbouring_offsets_are_not_consulted();
  test_return_width_is_the_full_32_bit_word();
  test_result_is_the_little_endian_word_not_a_re_encoding();
  test_result_is_not_the_receiver_nor_the_field_address();
  test_loaded_word_is_not_dereferenced();
  test_receiver_is_byte_identical_after_the_call();
  test_zero_stack_arguments_leaves_the_frame_intact();
  test_word_access_is_alignment_independent();
  test_machine_abi_is_checked_at_compile_time();
  test_receiver_region_is_sized_from_the_displacement();

  std::printf("%s: %d checks (%d discriminating), %d failures\n", __FILE__,
              g_checks, g_discriminating, g_failures);
  if (g_discriminating < 20) {
    std::printf("FAIL: discriminating checks fell below the floor; a "
                "load-bearing test was dropped\n");
    return 1;
  }
  return g_failures == 0 ? 0 : 1;
}
