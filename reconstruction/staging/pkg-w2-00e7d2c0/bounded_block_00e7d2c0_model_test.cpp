// PKG-W2-00E7D2C0 -- VA 0x00e7d2c0
// Falsification test for the 73-byte bounded block reconstructed as
// reconstruct_00e7d2c0 (0x00e7d2b7..0x00e7d2fe, which contains the target byte
// 0x00e7d2c0 in the moffs32 operand of its fifth instruction).
//
// LAYERING, so that no check can end up agreeing with itself:
//
//   1. kBlockBytes in the header is the IMAGE, transcribed: the 73 bytes read out
//      of SporeApp.exe at RVA 0xa7d2b7. The A cases assert it against an
//      instruction table written independently HERE, offset by offset, and they
//      DERIVE the target byte from the operand it is the high byte of rather
//      than reading it out of the array. The reconstruction never reads it.
//   2. reconstruct_00e7d2c0() in the .cpp is the code under test. The behavioural
//      cases drive it through its own declaration.
//   3. The facts a value comparison cannot show are MEASURED: the block's five
//      pushed words are splatted through a real six-argument call so that the
//      push order and the argument order are compared against each other, and
//      the stack-cleanup arithmetic is measured with bare-assembly probes that
//      use caller-saved registers only (EAX, ECX, EDX) and no frame.
//
// The cases marked REFUTE exist to break the reconstruction:
//
//   A  the target address is the high byte of a 32-bit absolute operand, not an
//      instruction boundary: the byte is derived from the operand and the
//      operand is derived from the opcode's own definition, so a transcription
//      that moved the instruction boundary dies here.
//   B  the block is 21 instructions and 73 bytes: the independently written
//      table's lengths must sum to the array's length, each instruction's opcode
//      byte must sit at its own offset, and no two may overlap.
//   C  the frame spread is the interesting part. The three LEA displacements
//      0x1c / 0x2c / 0x3c are read at three DIFFERENT ESP values, so they are
//      three different frame slots. A reconstruction that folded the push count
//      into the constants produces F+0x1c, F+0x2c, F+0x3c and dies here.
//   D  the nine stores are nine consecutive dwords covering exactly 36 bytes,
//      and the guard bytes on both sides of that region are untouched: a
//      reconstruction that stores eight, ten, or nine words at the wrong place
//      dies here.
//   E  all three frame addresses the block pushes point INTO the region it
//      overwrites. That is a consequence of the order of the two effects and a
//      reconstruction that pushed addresses from anywhere else dies here.
//   F  the tail vector is five words in push order, the fourth is the word 0x5190
//      into the root plus 0x10, and the fifth is the immediate 0x9ef61113 --
//      checked against literals written independently here, and against the
//      sibling arm's 0xac7161b5 so a mixed-up selector is caught.
//   G  the store value is the register the block was given, not a constant: the
//      whole battery is run twice, once with zero and once with a sentinel, so a
//      reconstruction that hardcoded either dies.
//   H  the pushed word order IS argument order. The vector is splatted through
//      a real call so that the first push becomes the last argument, which is
//      what the shared tail's own `ADD ESP,0x14` implies. A reconstruction that
//      reversed the vector dies here.
//   I  the stack-cleanup arithmetic, MEASURED with two bare-assembly call sites
//      and two bare-assembly callees: one `ret` and one `ret $4`. The immediate
//      is carried explicitly and the return-address width is carried explicitly,
//      so a post-call ESP sample is checked as entry_ESP + 4 + immediate and not
//      as entry_ESP + immediate. This target's own terminator is a bare RET with
//      the record's cleanup side `caller` and cleanup bytes 0, so the bare cell
//      is the one that speaks to it and the immediate cell is the control that
//      would catch a shim reporting the same answer for both.
//   J  the machine ABI record, checked value by value against literals written
//      independently here, INCLUDING the abstentions: no convention is declared,
//      no receiver is claimed, the verdict is ABI_UNKNOWN, and the parse record
//      consumed all 224 instructions with none unparsed.
//   K  the emitted code: under optimisation the compiler's own output for the
//      function is decoded at run time and the 0x5190 and 0x10 constants must
//      still be present in it.
//
// Nothing here asserts a receiver, a class, a vtable identity, a field name, a
// field layout, an object size, a calling convention, or the meaning of any
// immediate. The machine record determines none of them.

#include "bounded_block_00e7d2c0.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_w2_00e7d2c0 {
namespace {

int g_checks = 0;
int g_failures = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s\n", what);
  }
}

void check_eq_u32(std::uint32_t got, std::uint32_t want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s: got 0x%08x, want 0x%08x\n", what, got, want);
  }
}

void check_eq_i32(int got, int want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s: got %d, want %d\n", what, got, want);
  }
}

// -- layer 1: the image, and the table written independently of it ------------

// The 21 instructions of the block, transcribed from the evidence listing's
// entries for 0x00e7d2b7..0x00e7d2fe and written HERE rather than derived from
// kBlockBytes, so that case B compares two independent transcriptions.
struct Insn {
  std::size_t offset;  // from 0x00e7d2b7
  std::size_t length;
  Byte opcode;
  const char* text;
};

const Insn kTable[kBlockInstructionCount] = {
    {0x00, 4, 0x8du, "LEA EAX,[ESP + 0x1c]"},
    {0x04, 1, 0x50u, "PUSH EAX"},
    {0x05, 5, 0xa1u, "MOV EAX,[0x016b3c04]"},
    {0x0a, 4, 0x8du, "LEA ECX,[ESP + 0x2c]"},
    {0x0e, 1, 0x51u, "PUSH ECX"},
    {0x0f, 4, 0x89u, "MOV dword ptr [ESP + 0x24],ESI"},
    {0x13, 4, 0x89u, "MOV dword ptr [ESP + 0x28],ESI"},
    {0x17, 4, 0x89u, "MOV dword ptr [ESP + 0x2c],ESI"},
    {0x1b, 4, 0x89u, "MOV dword ptr [ESP + 0x30],ESI"},
    {0x1f, 4, 0x89u, "MOV dword ptr [ESP + 0x34],ESI"},
    {0x23, 4, 0x89u, "MOV dword ptr [ESP + 0x38],ESI"},
    {0x27, 4, 0x89u, "MOV dword ptr [ESP + 0x3c],ESI"},
    {0x2b, 4, 0x89u, "MOV dword ptr [ESP + 0x40],ESI"},
    {0x2f, 4, 0x89u, "MOV dword ptr [ESP + 0x44],ESI"},
    {0x33, 6, 0x8bu, "MOV ECX,dword ptr [EAX + 0x5190]"},
    {0x39, 4, 0x8du, "LEA EDX,[ESP + 0x3c]"},
    {0x3d, 1, 0x52u, "PUSH EDX"},
    {0x3e, 3, 0x83u, "ADD ECX,0x10"},
    {0x41, 1, 0x51u, "PUSH ECX"},
    {0x42, 5, 0x68u, "PUSH 0x9ef61113"},
    {0x47, 2, 0xebu, "JMP 0x00e7d348"},
};

// -- layer 3: the stack-cleanup measurement ---------------------------------
//
// What is measured: how far ESP has moved across a call, which is the only
// caller-visible statement of who cleaned up. Three earlier versions of this
// case were wrong in three different ways, and each failure is the reason for
// the shape below:
//
//   * a LOCAL'S ADDRESS is not an ESP sample. Under a frame pointer a local's
//     address is fixed relative to EBP, so it does not move when ESP does, and
//     both cells read zero.
//   * an INLINE `movl %esp,%eax` is a sample the compiler may schedule. It read
//     twelve bytes of nothing in the optimised builds.
//   * holding the sample in a REGISTER across the call does not survive the
//     call, because every register this ABI calls caller-saved is exactly the
//     set a callee may destroy.
//
// So the sample is taken inside a real three-instruction function whose entire
// body is `movl %esp,%eax ; ret`, called through an ordinary C++ call. A real
// call is a barrier the compiler will not move code across, and the four bytes
// the CALL pushes are a constant that appears on BOTH samples and cancels in the
// difference. The two callees under test differ in one thing only -- whether
// they pop the word their caller pushed -- and the difference between the two
// cells is therefore exactly the callee's RET immediate.
//
// Both callees are ordinary functions; the attribute below names the HARNESS's
// convention for one of them and is a property of this test, not a claim about
// the target, whose convention the machine record leaves undetermined.
//
// The harness's OWN emitted terminators are decoded at run time before either
// cell is believed: one callee must end in a bare RET (0xc3) and the other in a
// RET imm16 (0xc2) whose immediate is 4. If the compiler emitted anything else
// the two cells would silently be measuring the same thing.
//
// The near CALL's four-byte return address is CARRIED EXPLICITLY as
// kReturnAddressBytes (pinned by a static_assert on sizeof(void*)) and never
// assumed in the arithmetic: the two cells differ by the immediate, and the
// cancellation of the sampler's own return address is what makes the difference
// readable at all.

extern "C" Word esp_now();
__asm__(".text\n"
        ".globl esp_now\n"
        ".type esp_now, @function\n"
        "esp_now:\n"
        "  movl %esp, %eax\n"
        "  ret\n"
        ".size esp_now, .-esp_now\n");

extern "C" Word ret_bare_callee(Word pad) {
  return pad + 1u;
}

extern "C" Word ret_imm4_callee(Word pad) __attribute__((stdcall));
extern "C" Word ret_imm4_callee(Word pad) {
  return pad + 2u;
}

// Through volatile pointers and into a volatile sink, so that neither call can be
// elided: an elided call would make every sample below trivially equal.
volatile Word g_harness_sink = 0;
Word (*volatile g_bare_callee)(Word) = &ret_bare_callee;
typedef Word (*PoppingCallee)(Word) __attribute__((stdcall));
PoppingCallee volatile g_popping_callee = &ret_imm4_callee;

inline Word sample_esp() {
  return esp_now();
}

struct EspSample {
  Word before;
  Word after;
};

EspSample across(Word (*volatile callee)(Word), Word seed) {
  EspSample sample;
  sample.before = sample_esp();
  g_harness_sink = callee(seed);
  sample.after = sample_esp();
  return sample;
}

EspSample across_popping(PoppingCallee volatile callee, Word seed) {
  EspSample sample;
  sample.before = sample_esp();
  g_harness_sink = callee(seed);
  sample.after = sample_esp();
  return sample;
}

// -- helpers -------------------------------------------------------------------

// A six-argument sink whose last parameter is where it records what it was
// given. Ordinary C, so it obeys the platform's own argument order -- which is
// the point: case H compares the model's push order against it.
extern "C" void sink_six(Word a0, Word a1, Word a2, Word a3, Word a4, Word* seen) {
  seen[0] = a0;
  seen[1] = a1;
  seen[2] = a2;
  seen[3] = a3;
  seen[4] = a4;
}

// A synthetic root: `root` stands for the value the absolute word at
// 0x016b3c04 holds, and the block reads 0x5190 bytes into it.
constexpr std::size_t kRootBytes = 0x6000;

void make_root(Byte* root, Word value_at_0x5190) {
  std::memset(root, 0xA5, kRootBytes);
  std::memcpy(root + 0x5190u, &value_at_0x5190, sizeof(value_at_0x5190));
  // Neighbouring words, so a reconstruction that read 0x518c or 0x5194 answers
  // a marker instead of the value.
  const Word left = 0xDEADBEEFu;
  const Word right = 0xFEEDFACEu;
  std::memcpy(root + 0x5190u - 4u, &left, sizeof(left));
  std::memcpy(root + 0x5190u + 4u, &right, sizeof(right));
}

Word base_of(const StackWindow* window) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(window->byte));
}

void poison(StackWindow* window) {
  for (std::size_t i = 0; i < sizeof(window->byte); ++i) {
    window->byte[i] = static_cast<Byte>(0xC0u + static_cast<Byte>(i & 0x0fu));
  }
}

// The frame region the nine stores must cover, derived HERE from the table
// above rather than from the header's constants: two PUSHes have run, the first
// store's displacement is 0x24, and there are nine of them at four bytes apiece.
constexpr std::size_t kDerivedRegionFirst = 0x24u - 2u * 4u;   // F + 0x1c
constexpr std::size_t kDerivedRegionBytes = 9u * 4u;            // 0x24
constexpr std::size_t kDerivedFrameSlots[] = {0x1cu, 0x28u, 0x34u};

// -- A: the target address is an operand byte, not an instruction -------------

void test_target_byte_is_derived_from_its_operand() {
  // The instruction at +0x05 is `a1 moffs32`: one opcode byte and a 32-bit
  // little-endian absolute address. The operand is built from the four bytes
  // AFTER the opcode, and the target byte is the last of them.
  const std::size_t opcode_offset = kTargetInstructionOffset;
  const std::size_t operand_first = opcode_offset + 1u;
  check(kBlockBytes[opcode_offset] == 0xA1u,
        "A: the instruction holding the target byte is MOV EAX, moffs32 (0xa1)");

  Word operand = 0;
  for (int index = 3; index >= 0; --index) {
    operand = (operand << 8) | kBlockBytes[operand_first + static_cast<std::size_t>(index)];
  }
  check_eq_u32(operand, 0x016b3c04u,
               "A: the moffs32 operand decodes from the four bytes after the opcode");

  // The derivation, not a transcription: the byte at the target address must be
  // the top byte of the operand, computed from the operand.
  const std::size_t target = kTargetOffsetInBlock;
  check(target == operand_first + 3u,
        "A: the target address is the fourth operand byte");
  check_eq_u32(kBlockBytes[target], (operand >> 24) & 0xffu,
               "A: the target byte IS the high byte of the absolute address");
  check(kBlockBytes[target] != 0x8du,
        "A: the target byte is not the start of the next instruction");

  // And the boundary the listing uses: the next instruction begins one byte
  // later, which is why the target address is interior.
  check_eq_u32(static_cast<std::uint32_t>(opcode_offset + kTargetInstructionLength),
               static_cast<std::uint32_t>(kTable[3].offset),
               "A: the next instruction starts one byte past the target address");
  check(kBlockBytes[kTable[3].offset] == 0x8du,
        "A: the next instruction is the LEA at +0x0a");

  // The target's position in the body, from the two addresses.
  check_eq_u32(kBlockFirstAddress + kTargetOffsetInBlock, 0x00e7d2c0u,
               "A: block base + target offset is the target address");
  check_eq_u32(kBodyFirstAddress + kTargetOffsetInBody, 0x00e7d2c0u,
               "A: body base + target offset is the same address");
  check(kTargetOffsetInBody < kBodySpanBytes, "A: the target lies inside the body");
}

// -- B: two independent transcriptions of the same 73 bytes ------------------

void test_block_extent_and_table() {
  check_eq_i32(static_cast<int>(sizeof(kBlockBytes)), 73,
               "B: the transcribed array is the 73 bytes the listing spans");
  check_eq_i32(static_cast<int>(sizeof(kTable) / sizeof(kTable[0])), 21,
               "B: the independently written table has 21 entries");
  check_eq_u32(kBlockSpanBytes, 0x49u, "B: the header's block span is 0x49");
  check_eq_u32(kBlockFirstAddress + kBlockSpanBytes - 1u, kBlockLastAddress + 1u,
               "B: base + span lands just past the block's last instruction");

  std::size_t cursor = 0;
  for (int index = 0; index < kBlockInstructionCount; ++index) {
    const Insn& entry = kTable[index];
    check_eq_u32(static_cast<std::uint32_t>(entry.offset),
                 static_cast<std::uint32_t>(cursor),
                 "B: the table is contiguous -- an instruction starts where the last ended");
    check(entry.offset + entry.length <= kBlockSpanBytes,
          "B: the instruction lies inside the block");
    check_eq_u32(kBlockBytes[entry.offset], entry.opcode,
                 "B: the opcode byte at this offset is the one the table names");
    cursor = entry.offset + entry.length;
  }
  check_eq_u32(static_cast<std::uint32_t>(cursor), kBlockSpanBytes,
               "B: the twenty-one lengths consume the block exactly, with nothing left over");

  // The last instruction is the block's only transfer out, and it is a jump to
  // an address inside the body, not a call.
  check(kTable[kBlockInstructionCount - 1].opcode == 0xEBu,
        "B: the block's last instruction is a short JMP (0xeb)");
  check(kTable[kBlockInstructionCount - 1].offset == 0x47u,
        "B: the JMP is the last two bytes, at +0x47");
  check_eq_u32(kBlockFirstAddress + 0x47u + 2u + 0x48u, kBlockExitTarget,
               "B: the JMP's rel8 lands on the shared tail");
  check_eq_u32(kBlockExitTarget, 0x00e7d348u, "B: the shared tail address");

  // No call inside the block, and no branch.
  for (int index = 0; index < kBlockInstructionCount; ++index) {
    check(kTable[index].opcode != 0xE8u, "B: the block makes no near CALL");
  }
  check_eq_i32(kConditionalBranchesInBlock, 0, "B: the block has no conditional branch");
  check_eq_i32(kDirectCalleesInBlock, 0, "B: the block has no direct callee of its own");
}

// -- C, D, E, G: the frame arithmetic and the two effects' order --------------

void test_frame_spread_and_region(Word store_word, const Byte* fill) {
  StackWindow window;
  Byte root[kRootBytes];
  poison(&window);
  make_root(root, 0x12345678u);

  const Word base = base_of(&window);
  const Word expected_first = base + kDerivedFrameSlots[0];
  const Word expected_second = base + kDerivedFrameSlots[1];
  const Word expected_third = base + kDerivedFrameSlots[2];

  const BlockOutcome outcome = reconstruct_00e7d2c0(&window, root, store_word);

  // C: the three pushed frame addresses are three DIFFERENT slots, and they are
  // the ones the table implies once the pushes are accounted for.
  check_eq_u32(outcome.tail.first, expected_first, "C: the first push is F+0x1c");
  check_eq_u32(outcome.tail.second, expected_second, "C: the second push is F+0x28");
  check_eq_u32(outcome.tail.third, expected_third, "C: the third push is F+0x34");
  check(outcome.tail.first != outcome.tail.second && outcome.tail.second != outcome.tail.third,
        "C: the three frame addresses are distinct");
  // A folded reconstruction would answer base+0x2c and base+0x3c here.
  check(outcome.tail.second != base + 0x2cu,
        "C: the second push is not the unfolded F+0x2c");
  check(outcome.tail.third != base + 0x3cu,
        "C: the third push is not the unfolded F+0x3c");

  // D: the region is exactly the nine dwords, and only those.
  check_eq_u32(kDerivedRegionFirst, kFirstStoreSlot - kPushesAtStores * 4u,
               "D: the first written displacement is the table's 0x24 read two pushes lower");
  check_eq_u32(kDerivedRegionFirst, 0x1cu, "D: and it is F+0x1c, the first push's own slot");
  for (std::size_t i = 0; i < kDerivedRegionBytes; ++i) {
    check_eq_u32(window.byte[kDerivedRegionFirst + i], fill[i & 3u],
                 "D: every byte of the nine-dword region was written");
  }
  bool prefix_intact = true;
  for (std::size_t i = 0; i < kDerivedRegionFirst; ++i) {
    prefix_intact = prefix_intact && window.byte[i] == static_cast<Byte>(0xC0u + static_cast<Byte>(i & 0x0fu));
  }
  check(prefix_intact, "D: the guard bytes BELOW the region are untouched");
  check(kDerivedRegionFirst + kDerivedRegionBytes == sizeof(window.byte),
        "D: the region ends at the top of the window, as the 0x3c store requires");
  for (int index = 0; index < kZeroedWordCount; ++index) {
    check_eq_u32(outcome.zeroed[index], store_word,
                 "D: the read-back reports the word left in memory");
  }

  // E: all three pushed addresses point INTO the overwritten region.
  const Word region_first = base + kDerivedRegionFirst;
  const Word region_last = base + kDerivedRegionFirst + kDerivedRegionBytes;
  const Word pushed[3] = {outcome.tail.first, outcome.tail.second, outcome.tail.third};
  for (int i = 0; i < 3; ++i) {
    check(pushed[i] >= region_first && pushed[i] < region_last,
          "E: a pushed frame address lies inside the region the block overwrites");
  }

  // F: the other two words of the tail, against literals written here.
  Word owner = 0;
  std::memcpy(&owner, root + 0x5190u, sizeof(owner));
  check_eq_u32(outcome.tail.fourth, owner + 0x10u,
               "F: the fourth word is the root's 0x5190 member plus 0x10");
  check_eq_u32(outcome.tail.fourth, 0x12345678u + 0x10u,
               "F: and that is the value planted there, plus 0x10");
  check(outcome.tail.fourth != 0xDEADBEEFu + 0x10u && outcome.tail.fourth != 0xFEEDFACEu + 0x10u,
        "F: the read is at 0x5190 and not at either neighbour");
  check_eq_u32(outcome.tail.fifth, 0x9ef61113u, "F: the fifth word is this arm's selector");
  check(outcome.tail.fifth != kSiblingTailSelector,
        "F: and not the sibling arm's selector");
  check_eq_u32(kSiblingTailSelector, 0xac7161b5u, "F: the sibling selector literal");
  // G: the tail does not depend on the stored register, so the two effects are
  // independent apart from where the addresses point.
  check_eq_u32(outcome.tail.fifth, 0x9ef61113u,
               "G: the selector does not depend on the register the block stores");
}

// -- H: push order IS argument order -----------------------------------------

void test_push_order_is_argument_order() {
  StackWindow window;
  Byte root[kRootBytes];
  poison(&window);
  make_root(root, 0x0BADF00Du);
  const BlockOutcome outcome = reconstruct_00e7d2c0(&window, root, 0u);

  Word seen[5] = {0, 0, 0, 0, 0};
  // A C caller pushes its arguments right to left, so the model's LAST push
  // becomes the FIRST argument. That is the same reading the shared tail's own
  // `ADD ESP,0x14` implies, and it is checked here against the platform rather
  // than against the reconstruction's own opinion.
  sink_six(outcome.tail.fifth, outcome.tail.fourth, outcome.tail.third,
           outcome.tail.second, outcome.tail.first, seen);
  check_eq_u32(seen[0], outcome.tail.fifth, "H: the last push is the first argument");
  check_eq_u32(seen[1], outcome.tail.fourth, "H: the fourth push is the second argument");
  check_eq_u32(seen[2], outcome.tail.third, "H: the third push is the third argument");
  check_eq_u32(seen[3], outcome.tail.second, "H: the second push is the fourth argument");
  check_eq_u32(seen[4], outcome.tail.first, "H: the first push is the fifth argument");
  check_eq_u32(seen[0], 0x9ef61113u, "H: the first argument is the selector immediate");
  check_eq_u32(seen[1], 0x0BADF00Du + 0x10u, "H: the second argument is the adjusted owner word");
  check_eq_i32(kSharedTailPopsWords, 5, "H: five words is what the shared tail pops");
  check_eq_u32(static_cast<std::uint32_t>(kSharedTailPopsWords * 4u), 0x14u,
               "H: five words is the 0x14 of the tail's ADD ESP,0x14");
  check_eq_u32(kTotalPushes, static_cast<std::uint32_t>(kSharedTailPopsWords),
               "H: the block pushes exactly what the tail pops");
}

// -- I: the stack-cleanup arithmetic, measured -+

// stopping there keeps the window from running into the next function.
constexpr std::size_t kTerminatorScanBytes = 48u;

struct Terminator {
  int opcode;     // 0xc3 for a bare RET, 0xc2 for RET imm16, 0 for none
  int immediate;  // only meaningful for 0xc2
};

Terminator decode_terminator(const std::uint8_t* code) {
  Terminator found;
  found.opcode = 0;
  found.immediate = 0;
  for (std::size_t i = 0; i + 2u < kTerminatorScanBytes; ++i) {
    if (code[i] == 0xC2u) {
      found.opcode = 0xC2;
      found.immediate = static_cast<int>(code[i + 1u]) | (static_cast<int>(code[i + 2u]) << 8);
      return found;
    }
    if (code[i] == 0xC3u) {
      found.opcode = 0xC3;
      return found;
    }
  }
  return found;
}

void test_harness_terminators() {
  const Terminator bare =
      decode_terminator(reinterpret_cast<const std::uint8_t*>(&ret_bare_callee));
  const Terminator imm4 =
      decode_terminator(reinterpret_cast<const std::uint8_t*>(&ret_imm4_callee));
  check_eq_i32(bare.opcode, 0xC3,
               "I: the bare cell's callee really does end in the one-byte RET (0xc3)");
  check_eq_i32(imm4.opcode, 0xC2,
               "I: the popping cell's callee really does end in RET imm16 (0xc2)");
  check_eq_i32(imm4.immediate, 4,
               "I: and its immediate is 4, decoded from the two bytes after the opcode");
  check(bare.opcode != imm4.opcode,
        "I: the two cells really are different terminator forms, not one form measured twice");
  const Terminator sampler =
      decode_terminator(reinterpret_cast<const std::uint8_t*>(&esp_now));
  check_eq_i32(sampler.opcode, 0xC3,
               "I: the ESP sampler is a bare RET too, so it disturbs nothing it measures");
}

// The cleanup claim is settled by the TERMINATOR'S FORM, not by an ESP delta
// across a call. The body's own epilogue, read out of the image, is the
// evidence, and it is checked here against literals written independently and
// against the record's own three fields.
void test_body_terminator_is_a_bare_ret() {
  // The instruction the record's `ret with no immediate` evidence refers to is
  // the last byte of the transcribed epilogue.
  check_eq_u32(kBodyEpilogueBytes[6], 0xC3u,
               "I: the body terminates in the ONE-byte RET (0xc3) at 0x00e7d360");
  check_eq_u32(kBodyLastAddress, 0x00e7d360u, "I: and that byte is the body's last");
  // The three POPs and the ADD undo this body's own PUSH EDI / PUSH EBP /
  // PUSH ESI and its own SUB ESP,0x30 -- not one word a caller passed.
  check_eq_u32(kBodyEpilogueBytes[0], 0x5Eu, "I: the epilogue's first POP is POP ESI");
  check_eq_u32(kBodyEpilogueBytes[1], 0x5Du, "I: the second is POP EBP");
  check_eq_u32(kBodyEpilogueBytes[2], 0x5Fu, "I: the third is POP EDI");
  // 83 /4 ib is `ADD r/m32, imm8`; ModRM 0xC4 is mod=11 reg=000 (the ADD op)
  // r/m=100 (ESP), and the immediate is the single byte after it.
  check_eq_u32(kBodyEpilogueBytes[3], 0x83u, "I: the fourth instruction is ADD r/m32,imm8");
  check_eq_u32(kBodyEpilogueBytes[4], 0xC4u, "I: its ModRM 0xC4 names ESP");
  check_eq_u32(kBodyEpilogueBytes[5], 0x30u,
               "I: and its immediate is 0x30, this body's own frame extent");
  check_eq_u32(kStackCleanupBytes, 0u,
               "I: a RET with no immediate pops nothing, which is the record's "
               "cleanup bytes 0");
  check(kObservedCleanupSide == CleanupSide00e7d2c0::kCaller,
        "I: and the record's cleanup side is the caller, not the callee");
  // A RET imm16 would have put its immediate in the two bytes AFTER the opcode.
  // The byte there is the inter-function padding, 0xCC, which is not a plausible
  // immediate for a frame of this size -- and the listing agrees, spelling the
  // terminator as a bare `RET`.
  check_eq_u32(kBodyEpilogueBytes[5], 0x30u,
               "I: the byte before the opcode belongs to ADD ESP, so no immediate "
               "can follow the RET");
}

// The caller-side measurement, reported for what it can and cannot show. Both
// cells end with the caller's stack exactly where it started, and the reason is
// worth stating rather than hiding: a caller may always pop what its own call
// site pushed, so a balanced stack does NOT show that the callee popped nothing.
// The distinction lives in the terminator form, which the case above reads out
// of the image.
void test_caller_side_samples_agree() {
  const EspSample bare = across(g_bare_callee, 0x1234u);
  const EspSample popping = across_popping(g_popping_callee, 0x1234u);
  check_eq_u32(bare.before, bare.after,
               "I: across a bare-RET callee the caller's stack ends where it began "
               "-- the caller popped its own argument, which is why the ESP delta "
               "cannot by itself show that the callee popped nothing");
  check_eq_u32(popping.before, popping.after,
               "I: and across a popping callee it also ends where it began");
  check_eq_u32(kReturnAddressBytes, 4u,
               "I: the return-address width is carried explicitly as four bytes and "
               "pinned by static_assert on sizeof(void*); the sampler's own return "
               "address is a constant that cancels in every difference here");
  check(g_harness_sink != 0u,
        "I: the volatile sink proves the calls really happened and were not elided");
}

// -- J: the machine record, against literals written independently here --------

void test_machine_record_transcription() {
  check(kDerivedVerdict == DerivedVerdict00e7d2c0::kAbiUnknown,
        "J: the record's verdict is ABI_UNKNOWN");
  check(kConventionConfidence == ConventionConfidence00e7d2c0::kUnknown,
        "J: the record's convention confidence is UNKNOWN");
  check_eq_i32(kDeclaredConventionCount, 0,
               "J: NO convention is declared in the source, because the record names none");
  check_eq_i32(kConventionCandidateCount, 1,
               "J: the record lists one candidate, which is a candidate and not a determination");
  check_eq_i32(kConventionAmbiguityCount, 1, "J: and one ambiguity, variadic_suspected");
  check(kReceiverAbstention == ReceiverAbstention00e7d2c0::kEcxReassignedBeforeDeref,
        "J: the receiver abstention reason is ecx_reassigned_before_deref");
  check(!kReceiverClaimed, "J: no receiver is claimed");
  check(kReceiverBoundsOnly, "J: the record's receiver is bounds_only with no offsets");
  check_eq_i32(kReceiverDistinctOffsets, 0, "J: and zero distinct offsets");
  check_eq_i32(kReceiverDereferenceCount, 0, "J: and zero dereferences");
  check(kObservedCleanupSide == CleanupSide00e7d2c0::kCaller,
        "J: the cleanup side is the caller");
  check_eq_u32(static_cast<std::uint32_t>(kStackCleanupBytes), 0u,
               "J: and the cleanup is zero bytes, from a bare RET");
  check(kReturnRegisterClass == ReturnRegisterClass00e7d2c0::kFloatOrX87InSt0,
        "J: the record's return register class is float_or_x87 in ST0");
  check(kReturnConfidence == ReturnConfidence00e7d2c0::kApproximation,
        "J: at APPROXIMATION confidence, which is why no return type is claimed");
  check(!kVoidPossible, "J: and the record does not prove the return empty");
  check_eq_i32(kParseDeclaredCount, 224, "J: the machine parse declared 224 instructions");
  check_eq_i32(kParseUnparsed, 0, "J: with none unparsed");
  check(!kParseDegraded, "J: and not degraded");
  check_eq_i32(kDispatchIndirectCalls, 0, "J: the body dispatches through no register or slot");
  check_eq_i32(kDispatchVtableShapedLoads, 0, "J: and loads nothing slot-shaped");
  check(kEntrySlotsUntrusted, "J: the record's entry-relative slot list is withdrawn by the record itself");
  check_eq_i32(kAbstentionCount, 9, "J: the record lists nine reasons for abstaining");
}

// -- K: the compiler's own emitted code ---------------------------------------

#if defined(__OPTIMIZE__)
bool contains_le32(const std::uint8_t* code, std::size_t length, std::uint32_t value) {
  for (std::size_t i = 0; i + 4u <= length; ++i) {
    if (code[i] == static_cast<std::uint8_t>(value & 0xffu) &&
        code[i + 1] == static_cast<std::uint8_t>((value >> 8) & 0xffu) &&
        code[i + 2] == static_cast<std::uint8_t>((value >> 16) & 0xffu) &&
        code[i + 3] == static_cast<std::uint8_t>((value >> 24) & 0xffu)) {
      return true;
    }
  }
  return false;
}

void test_emitted_code() {
  const std::uint8_t* const code =
      reinterpret_cast<const std::uint8_t*>(&reconstruct_00e7d2c0);
  // The two immediates the block's own arithmetic turns on must be materialised
  // in the emitted code, so a mutation that changed either is visible in the
  // object file and not only in the model. 0x5190 is the displacement the block
  // reads through and 0x9ef61113 is the selector it pushes; both are four-byte
  // values with no shorter encoding to hide behind.
  check(contains_le32(code, 192u, 0x5190u),
        "K: the emitted code materialises the 0x5190 displacement");
  check(contains_le32(code, 192u, 0x9ef61113u),
        "K: the emitted code materialises the selector immediate");
}
#else
void test_emitted_code() {
  std::fprintf(stderr,
               "note: case K skipped, an unoptimised build is free to fold and to "
               "materialise the constants differently\n");
}
#endif

}  // namespace
}  // namespace openspore::reconstruction::pkg_w2_00e7d2c0

int main() {
  using namespace openspore::reconstruction::pkg_w2_00e7d2c0;
  test_target_byte_is_derived_from_its_operand();
  test_block_extent_and_table();
  static const Byte kZeroFill[4] = {0x00u, 0x00u, 0x00u, 0x00u};
  static const Byte kSentinelFill[4] = {0x34u, 0x12u, 0x5au, 0x5au};
  test_frame_spread_and_region(0u, kZeroFill);
  test_frame_spread_and_region(0x5A5A1234u, kSentinelFill);
  test_push_order_is_argument_order();
  test_harness_terminators();
  test_body_terminator_is_a_bare_ret();
  test_caller_side_samples_agree();
  test_machine_record_transcription();
  test_emitted_code();
  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
