// PKG-W2-00F96840 -- VA 0x00f96840
// Model test for the 15-instruction body at 0x00f96840..0x00f96869.
//
// WHAT THIS TEST CAN AND CANNOT PROVE, stated first because this target is an
// unusual one: the body has no return. Its last instruction is a tail jump, so
// the reconstructed entry does not come back to its caller under any harness.
// That is not a limitation worked around; it is the property under test, and
// the harness below is built to observe it rather than to route around it:
//
//   * the three transfers are all register-indirect, so the model never calls
//     out to a named address. Every address it uses it READS OUT of a fixture,
//     which is why the whole body can be exercised against ordinary memory
//     instead of against a wall of unmapped pages.
//
// HARNESS RULES, and why each is here.
//
// 1. The call harness is a bare-assembly block that touches ONLY caller-saved
//    registers -- EAX, ECX, EDX -- plus its own stack frame, addressed off ESP.
//    It never writes ESI, EDI, EBX or EBP. This matters twice over on an
//    i386 System V build: a callee must hand those four back untouched, and on a
//    PIE build EBX holds the GOT base, so a probe that takes EBX over inside the
//    asm invalidates every address the compiler forms around it. Addressing the
//    probe's own frame off ESP rather than EBP keeps the rule absolute: EBP is
//    never written either, not even as a frame pointer.
//
// 2. Nothing reaches the harness through a global. The sample structure is passed
//    by pointer and written through it, so the block's only contact with the
//    fixtures is a pointer it was handed.
//
// 3. The harness CANNOT complete the call, and that is the point. The body's only
//    exit is `JMP EDX` through the table word at the receiver's +0x84, so control
//    never returns to the instruction after the probe's CALL. Two mutually
//    exclusive channels record which one happened:
//      - the probe's post-call code sets `returned_normally`, and is reachable
//        only if the entry RETURNED (i.e. a reconstruction that emitted a
//        terminator instead of the tail jump);
//      - the routine installed at table slot 0x84 records itself and then
//        longjmps straight back to the driver.
//    A reconstruction that got the last instruction wrong would take one of the
//    two and could not take both.
//
// 4. Register state is sampled at the TRANSFER, not after it. The three shims
//    installed in the fixture's table are bare-assembly blocks that push the
//    registers they care about and call a recorder. That is the only way to see
//    ECX and EAX as the body actually hands them over: a C++ function entered
//    normally may have had either clobbered by its own prologue before the first
//    line of its body ran, and a block that returned would have lost the state
//    anyway.
//
// 5. Every assertion compares against something INDEPENDENTLY derived: the
//    binary's own bytes (transcribed from /read_memory) for the byte window, the
//    listing's own displacement for every address claim, and a literal written
//    here in the test for every fact the header states. Nothing compares the
//    header against the header's own pointer, which would survive the very edit
//    it exists to catch.
//
// 6. The stack-discipline samples are taken through the probe's own frame, and
//    the return-address size is carried explicitly rather than inferred. The
//    probe records ESP immediately before the CALL; the shims record ESP on
//    entry. The two are related by the body's own arithmetic -- the return
//    address the CALL pushes (4 bytes) and the single word PUSH ESI holds
//    outstanding while the two calls are made -- and the relation is written out
//    per step in the cases below rather than folded into a constant.

#include "w2_00f96840_types.hpp"

#include <csetjmp>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00f96840 {
namespace {

// -- fixtures ----------------------------------------------------------------

// The receiver must be mappable and must reach 0x817, because the body's only
// write is four bytes at the receiver's +0x814. 0x900 is the smallest size that
// leaves headroom above that for an interior-receiver case, and it is a size and
// not a fact about the original object: the machine record bounds the receiver's
// reach at 0x814 and states bounds_only, and nothing here claims an object size.
constexpr std::size_t kObjectBytes = 0x900u;
// The table read through the receiver's first word. The largest displacement the
// body reads through it is 0x84, so a 0x88-byte window holds every one of them.
constexpr std::size_t kTableBytes = 0x88u;

struct alignas(4) Object {
  std::uint8_t bytes[kObjectBytes];
};
struct alignas(4) Table {
  std::uint8_t bytes[kTableBytes];
};

Object g_object;
Table g_table;

// The fill the whole receiver is set to before every run, so that a single write
// by the body stands out against an unchanging background.
constexpr std::uint8_t kSentinel = 0xa5u;

// Templated rather than taking `const void*`, so a FUNCTION pointer converts as
// readily as an object one: the three shims and the reconstructed entry are all
// `void (*)()`, and a function pointer does not convert to `const void*`
// implicitly on either compiler.
template <typename T>
std::uint32_t address_of(T pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

std::uint32_t word_at(std::uint8_t* base, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, base + offset, sizeof value);
  return value;
}

void store_word(std::uint8_t* base, std::size_t offset, std::uint32_t value) {
  std::memcpy(base + offset, &value, sizeof value);
}

// What the probe hands back. Five fields, and the two that matter most are the
// pair that can only both be set by a body that RETURNS -- which this body does
// not, so both are required to stay zero.
struct Sample {
  std::uint32_t esp_before = 0;
  std::uint32_t receiver = 0;
  std::uint32_t target = 0;
  std::uint32_t returned_normally = 0;
  std::uint32_t esp_after = 0;
};

// -- the recorders the shims call --------------------------------------------

struct Trace {
  unsigned count;                  // how many transfers were observed
  unsigned step[4];                // which step each observation was
  std::uint32_t ecx[4];
  std::uint32_t eax[4];
  std::uint32_t edx[4];
  std::uint32_t esi[4];
  std::uint32_t entry_esp[4];      // ESP as it stood on ENTERING the shim
  std::uint32_t zeroed_word;       // the receiver's 0x814 word, read at step 3
  std::uint32_t zeroed_receiver;   // the receiver step 3 saw in ECX
};

Trace g_trace;

std::jmp_buf g_tail_jump;
std::uint32_t g_target = 0;
std::uint32_t g_receiver = 0;
Sample* g_sample = nullptr;

// `step` is 1 for the table slot 0x70, 2 for slot 0x60 and 3 for slot 0x84. The
// order of the parameters matches the push order the shims use, and `entry_esp`
// is the ESP each shim was ENTERED on, computed inside the shim by a MOV and an
// ADD rather than by pushing the stack pointer -- PUSH ESP does not have one
// portable reading of which value it stores, and a harness that depended on that
// would be testing a manual, not the machine.
extern "C" void record_step(std::uint32_t step, std::uint32_t entry_esp,
                            std::uint32_t esi_at, std::uint32_t ecx_at,
                            std::uint32_t eax_at, std::uint32_t edx_at) {
  const unsigned slot = g_trace.count;
  g_trace.count += 1u;
  if (slot < 4u) {
    g_trace.step[slot] = static_cast<unsigned>(step);
    g_trace.ecx[slot] = ecx_at;
    g_trace.eax[slot] = eax_at;
    g_trace.edx[slot] = edx_at;
    g_trace.esi[slot] = esi_at;
    g_trace.entry_esp[slot] = entry_esp;
  }
  if (step == 3u) {
    // The one store this body makes is visible here or nowhere: by the time
    // control has left the body the only observation left is the memory itself,
    // and reading it at the moment of the transfer is what separates "written
    // before the transfer" from "written after", which cannot happen and would be
    // a different body.
    g_trace.zeroed_receiver = ecx_at;
    g_trace.zeroed_word = word_at(reinterpret_cast<std::uint8_t*>(ecx_at),
                                  kReceiverOffsetZeroed);
    longjmp(g_tail_jump, 1);
  }
}

// The three shims: the observers installed in the fixture's table.
//
// THEY ARE DEFINED IN A TOP-LEVEL ASSEMBLY BLOCK, NOT AS NAKED C++ FUNCTIONS, and
// that is a correctness requirement rather than a style choice. A naked C++ function
// on a position-independent i386 build is handed a ten-byte
// __x86.get_pc_thunk.ax prologue by the compiler, and that prologue CLOBBERS EAX and
// EDX. These shims exist for one reason -- to sample EAX and EDX as the body hands
// them over -- so a compiler-inserted prefix that overwrites both of them would
// silently destroy the only thing they are for. A top-level block gets no
// compiler-generated prologue at all, so what the body sets is what the shim sees.
// The price is that the block is unchecked by the compiler, which is why each shim
// here is small, symmetrical with the others, and read byte for byte in the checks
// that follow.
//
// The two CALL shims are entered by the body's own CALL, so each arrives with a
// return address already on the stack, and each returns through it. The TAIL shim is
// entered by a JMP and therefore has none: it is entered on the caller's own stack.
// That difference is the observation the stack-discipline case is built on, and it
// is why these two shapes must not be unified.
//
// All three push the same six dwords in the same order, so the recorder's parameter
// list is written once. `entry_esp` is not obtained by pushing the stack pointer --
// PUSH ESP does not have one portable reading of which value it stores -- but by a
// MOV and an ADD that undo the four pushes already made, so it is the shim's entry
// ESP by arithmetic rather than by an instruction whose semantics differ between the
// two of us.
extern "C" void shim_first_call(void);
extern "C" void shim_second_call(void);
extern "C" void shim_tail_transfer(void);

#define PKG_W2_SHIM_PUSHES(SYMBOL, STEP, TAIL)                                  \
  ".balign 16\n"                                                              \
  ".globl " SYMBOL "\n"                                                       \
  ".type " SYMBOL ", @function\n"                                             \
  SYMBOL ":\n"                                                                \
  "  pushl %edx\n\t"                                                         \
  "  pushl %eax\n\t"                                                         \
  "  pushl %ecx\n\t"                                                         \
  "  pushl %esi\n\t"                                                         \
  "  movl %esp, %edx\n\t"                                                    \
  "  addl $16, %edx\n\t"                                                     \
  "  pushl %edx\n\t"                                                         \
  "  pushl $" STEP "\n\t"                                                     \
  "  call record_step\n\t"                                                   \
  "  addl $24, %esp\n\t"                                                     \
  TAIL                                                                         \
  ".size " SYMBOL ", .-" SYMBOL "\n"

__asm__(".text\n"
        PKG_W2_SHIM_PUSHES("shim_first_call", "1", "  ret\n\t")
        PKG_W2_SHIM_PUSHES("shim_second_call", "2", "  ret\n\t")
        // The tail shim never returns: record_step longjmps out of it, so the trap
        // after the call is unreachable and exists only to end the block.
        PKG_W2_SHIM_PUSHES("shim_tail_transfer", "3", "  ud2\n\t"));

// The call harness. Three arguments -- target, receiver, out -- are read from the
// incoming frame, copied into the probe's own 16-byte frame, and only then is
// ESP sampled, so the sample is the stack the body will be entered on. ECX is
// loaded with the receiver immediately before the CALL, which is the one register
// input the listing fixes: 0x00f96841 reads ECX and nothing else in the body
// establishes it.
//
// The post-call block is reachable only if the body returned. It records
// returned_normally and the ESP it came back on and then tears its own frame
// down; nothing after the CALL can observe a body that transfers control out
// through its last instruction, which is why the recorder side of this harness
// lives in the shims instead.
extern "C" void probe_enter_tail(std::uint32_t target, std::uint32_t receiver,
                                 Sample* out);

__asm__(".text\n"
        ".balign 16\n"
        ".globl probe_enter_tail\n"
        ".type probe_enter_tail, @function\n"
        "probe_enter_tail:\n"
        "  subl $16, %esp\n"        // the probe's own frame, addressed off ESP
        "  movl 20(%esp), %eax\n"   // target    (return address is at 0(%esp))
        "  movl 24(%esp), %edx\n"   // receiver
        "  movl 28(%esp), %ecx\n"   // out
        "  movl %eax, -8(%esp)\n"
        "  movl %edx, -4(%esp)\n"
        "  movl %ecx, -12(%esp)\n"
        "  movl %esp, 0(%ecx)\n"    // out->esp_before, before any transfer
        "  movl %edx, 4(%ecx)\n"    // out->receiver
        "  movl %eax, 8(%ecx)\n"    // out->target
        "  movl $0, 12(%ecx)\n"     // out->returned_normally
        "  movl $0, 16(%ecx)\n"     // out->esp_after
        "  movl %edx, %ecx\n"       // the receiver, into the one register input
        "  call *-8(%esp)\n"        // 4 bytes of return address land here
        "  movl -12(%esp), %eax\n"  // reachable ONLY if the body returned
        "  movl $1, 12(%eax)\n"     // out->returned_normally = 1
        "  movl %esp, 16(%eax)\n"   // out->esp_after
        "  addl $16, %esp\n"
        "  ret\n"
        ".size probe_enter_tail, .-probe_enter_tail\n");

// The driver. Returns 1 when control came back through the routine at table slot
// 0x84 (the body's actual behaviour) and 0 when the body returned to the probe.
//
// The state it needs across the transfer lives in globals, not in locals, so no
// optimiser-visible local is live across a setjmp. That is not a precaution
// dressed as a rule: a value in a register that the compiler may re-materialise
// after a second return through setjmp is exactly the value that goes stale.
PKG_W2_00F96840_NOINLINE int run_body(std::uint32_t target, std::uint32_t receiver,
                                      Sample* out) {
  g_target = target;
  g_receiver = receiver;
  g_sample = out;
  g_trace.count = 0u;
  for (unsigned index = 0u; index < 4u; ++index) {
    g_trace.step[index] = 0u;
    g_trace.entry_esp[index] = 0u;
  }
  g_trace.zeroed_word = 0xffffffffu;
  g_trace.zeroed_receiver = 0u;
  if (setjmp(g_tail_jump) == 0) {
    probe_enter_tail(g_target, g_receiver, g_sample);
    return 0;
  }
  return 1;
}

// -- the fixture builder -----------------------------------------------------

void fill_sentinels() { std::memset(g_object.bytes, kSentinel, kObjectBytes); }

// Write the three shims into the table itself. Kept separate from the step that
// points the receiver at it, because a case that hands the body an INTERIOR
// receiver must point THAT receiver at the table and must leave the fixture's own
// first word alone -- otherwise the two words and the "nothing else was written"
// comparison below would be measuring the fixture rather than the body.
void build_table(std::uint32_t first, std::uint32_t second, std::uint32_t tail) {
  std::memset(g_table.bytes, 0, kTableBytes);
  store_word(g_table.bytes, kSlotFirstCall, first);
  store_word(g_table.bytes, kSlotSecondCall, second);
  store_word(g_table.bytes, kSlotTailTransfer, tail);
}

// Point the receiver at the table. The table is written through its own byte
// window and the receiver's first word is written last, so a partially built
// fixture is never one the body can see.
void install_table(std::uint32_t first, std::uint32_t second, std::uint32_t tail) {
  build_table(first, second, tail);
  store_word(g_object.bytes, kReceiverOffsetFirstWord, address_of(&g_table));
}

void build_fixture() {
  fill_sentinels();
  install_table(address_of(&shim_first_call), address_of(&shim_second_call),
                address_of(&shim_tail_transfer));
}

// -- a read-only window on the bytes the RECONSTRUCTED ENTRY emits ------------
//
// The entry is a naked function defined in the package's .cpp, and this symbol is
// given the entry's own address by the assembler, so the model test holds the
// very function the validator binds to 0x00f96840 against the binary's own 42
// bytes. It is a window, not a copy: nothing here writes through it.
//
// The anchor allowance is a toolchain artifact, not a relaxation of the claim. A
// position-independent g++ build may prepend a ten-byte __x86.get_pc_thunk.ax PC
// anchor (e8 ?? ?? ?? ?? 05) to a naked function; clang++ emits none. The anchor
// is recognised by that exact opcode pair and the 42 target bytes are then
// required immediately after it, so a toolchain that emitted some other form of
// anchor fails here instead of passing.
extern "C" const unsigned char reconstructed_entry_image[];

__asm__(".text\n"
        ".globl reconstructed_entry_image\n"
        "reconstructed_entry_image = re_00f96840\n");

PKG_W2_00F96840_NOINLINE const unsigned char* entry_body_base() {
  const unsigned char* const image = reconstructed_entry_image;
  const bool anchored = image[0] == 0xe8u && image[5] == 0x05u;
  return image + (anchored ? 10u : 0u);
}

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void check_eq_u32(std::uint32_t actual, std::uint32_t expected, const char* what) {
  if (actual != expected) {
    std::fprintf(stderr, "FAILED: %s -- got 0x%08x, expected 0x%08x\n", what, actual,
                 expected);
    ++g_failures;
  }
}

bool is_divergent_position(std::size_t index) {
  return index == kEcxToEsiFirstByte || index == kEcxToEsiSecondByte ||
         index == kEsiToEcxFirstByte || index == kEsiToEcxSecondByte ||
         index == kEsiToEcxSecondOccurrenceFirstByte ||
         index == kEsiToEcxSecondOccurrenceSecondByte;
}

// W -- the bytes. The reconstructed entry must emit the binary's own 42 bytes.
void case_the_entry_emits_the_target_bytes() {
  const unsigned char* const body = entry_body_base();

  check(address_of(body) != 0u, "W1: the entry has an address");
  check(body[0] != 0u, "W2: and the first target byte was actually read");

  int literal = 0;
  int divergent = 0;
  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    if (is_divergent_position(index)) {
      ++divergent;
      continue;
    }
    ++literal;
    check(body[index] == kTargetBytes[index],
          "W3: byte-for-byte the binary's own encoding");
  }
  check_eq_u32(static_cast<std::uint32_t>(literal),
               static_cast<std::uint32_t>(kLiteralByteCount),
               "W3a: thirty-six of the forty-two positions are compared literally");
  check_eq_u32(static_cast<std::uint32_t>(divergent),
               static_cast<std::uint32_t>(kDivergentByteCount),
               "W3b: and six positions are the three register moves the assembler "
               "spells either way");
  check_eq_u32(literal + divergent, 42u,
               "W3c: the two counts account for all forty-two positions");
  check_eq_u32(static_cast<std::uint32_t>(kBodySpanBytes), 42u,
               "W3d: and the body is forty-two bytes");

  // MOV ESI,ECX: 8b f1 (the binary) or 89 ce (the GNU assembler).
  const bool receiver_copy_binary =
      body[kEcxToEsiFirstByte] == 0x8bu && body[kEcxToEsiSecondByte] == 0xf1u;
  const bool receiver_copy_assembler =
      body[kEcxToEsiFirstByte] == 0x89u && body[kEcxToEsiSecondByte] == 0xceu;
  check(receiver_copy_binary || receiver_copy_assembler,
        "W4: bytes 1..2 are one of the two encodings of MOV ESI,ECX");
  // MOV ECX,ESI: 8b ce (the binary) or 89 f1 (the GNU assembler). It occurs
  // twice, and BOTH occurrences are checked: a body that emitted it once and
  // clobbered ECX for the other would pass a check on the first alone.
  const bool forward_binary =
      body[kEsiToEcxFirstByte] == 0x8bu && body[kEsiToEcxSecondByte] == 0xceu;
  const bool forward_assembler =
      body[kEsiToEcxFirstByte] == 0x89u && body[kEsiToEcxSecondByte] == 0xf1u;
  check(forward_binary || forward_assembler,
        "W5: bytes 15..16 are one of the two encodings of MOV ECX,ESI");
  const bool tail_binary = body[kEsiToEcxSecondOccurrenceFirstByte] == 0x8bu &&
                           body[kEsiToEcxSecondOccurrenceSecondByte] == 0xceu;
  const bool tail_assembler = body[kEsiToEcxSecondOccurrenceFirstByte] == 0x89u &&
                              body[kEsiToEcxSecondOccurrenceSecondByte] == 0xf1u;
  check(tail_binary || tail_assembler,
        "W6: bytes 37..38 are the same instruction, encoded the same way");

  // The positions that carry the interesting facts are pinned individually, so a
  // failure of W3 above is legible rather than just "some byte".
  check(body[0] == 0x56u, "W7: the prologue is PUSH ESI and nothing else");
  check(body[8] == 0xffu && body[9] == 0xd2u,
        "W8: the first transfer is CALL EDX, the register-indirect form");
  check(body[17] == 0xffu && body[18] == 0xd2u,
        "W9: and so is the second");
  check(body[5] == 0x8bu && body[6] == 0x50u && body[7] == 0x70u,
        "W10: the first slot displacement is 0x70, read through the table word");
  check(body[12] == 0x8bu && body[13] == 0x50u && body[14] == 0x60u,
        "W11: the second is 0x60");
  check(body[21] == 0x8bu && body[22] == 0x90u && body[23] == 0x84u &&
            body[24] == 0x00u && body[25] == 0x00u && body[26] == 0x00u,
        "W12: and the third is 0x84, as a six-byte displacement");
  check(body[27] == 0xc7u && body[28] == 0x86u && body[29] == 0x14u &&
            body[30] == 0x08u && body[31] == 0x00u && body[32] == 0x00u &&
            body[33] == 0x00u && body[34] == 0x00u && body[35] == 0x00u &&
            body[36] == 0x00u,
        "W13: the single store is the ten-byte C7 86 form at displacement 0x814 "
        "with a four-byte immediate of zero");
  check(body[39] == 0x5eu, "W14: ESI is restored before the transfer out");
  check(body[40] == 0xffu && body[41] == 0xe2u,
        "W15: the last instruction is JMP EDX, the tail the record abstained on");

  // The header's own byte transcript, anchored on literals written HERE rather
  // than read back from the header, so a corrupted transcript cannot make every
  // comparison in W3 pass for the wrong reason.
  check(kTargetBytes[0] == 0x56u, "W16: the transcript starts with PUSH ESI");
  check(kTargetBytes[40] == 0xffu && kTargetBytes[41] == 0xe2u,
        "W17: and ends with JMP EDX");
  check(kTargetBytes[15] == 0x8bu && kTargetBytes[16] == 0xceu &&
            kTargetBytes[37] == 0x8bu && kTargetBytes[38] == 0xceu,
        "W18: and carries the binary's own 8b ce spelling of MOV ECX,ESI twice");
}

// L -- the machine record travels with the source as DATA, so a package that
// quietly upgraded the abstention into a convention -- or quietly dropped the
// receiver that IS established -- fails here instead of passing.
//
// Every value is compared against a literal SPELLING of what the record states,
// never against the header's own pointer to it. A comparison of a value with the
// header's pointer would still hold after the header had been changed to say
// something else, and the whole point of carrying the determination as data is
// that changing the data is what must be caught.
void case_the_record_travels_as_data() {
  // The convention: NOT determined. Spelled here as __thiscall and nothing else
  // is what this package must NOT be saying.
  check(static_cast<int>(kDerivedConventionVerdict) ==
            static_cast<int>(ConventionVerdict00f96840::kUndetermined),
        "L1: the derived convention is UNDETERMINED");
  check(static_cast<int>(ConventionVerdict00f96840::kUndetermined) == 0,
        "L1a: and the verdict scale spells UNDETERMINED as 0");
  check(kDerivedConventionConfidence == ConventionConfidence::kUnknown,
        "L2: the record's confidence is UNKNOWN, not INFERRED and not OBSERVED");
  check(static_cast<int>(ConventionConfidence::kUnknown) == 0,
        "L2a: and the confidence scale spells UNKNOWN as 0");
  check(static_cast<int>(ConventionConfidence::kInferred) == 1,
        "L2b: and INFERRED as 1, which this determination is not");
  check(static_cast<int>(ConventionConfidence::kObserved) == 2,
        "L2c: and OBSERVED as 2, which it is not either");
  // All four candidates are still open, and this package selects none of them.
  check_eq_u32(static_cast<std::uint32_t>(kCandidateConventionCount), 4u,
               "L3: all four candidates remain");
  check(static_cast<int>(CandidateConvention00f96840::kCdecl) == 0 &&
            static_cast<int>(CandidateConvention00f96840::kStdcall) == 1 &&
            static_cast<int>(CandidateConvention00f96840::kThiscall) == 2 &&
            static_cast<int>(CandidateConvention00f96840::kFastcall) == 3,
        "L3a: the candidate scale spells exactly those four, in that order");
  check(!kEntryDeclaresConvention,
        "L4: and the reconstructed entry declares NO convention token");
  check(std::strstr(kAbstentionReason, "no_terminal_ret") != nullptr,
        "L4a: the record's stated reason is the absent terminator");
  check(std::strstr(kAbstentionReason, "no RET instruction") != nullptr,
        "L4b: quoted in full, terminator and all");

  // The cleanup: UNDETERMINED, with no enumerator member to select. A package
  // that had invented a callee side would have to set this, and dies here.
  check(kObservedCleanupSide == CleanupSide00f96840::kUndetermined,
        "L5: the cleanup side is UNDETERMINED");
  check(!kCleanupSideDetermined, "L6: and the package does not claim it is");
  check_eq_u32(static_cast<std::uint32_t>(kRetImmediateBytes), 0u,
               "L7: no terminator carries an immediate, so there are none");
  check(!kTerminalRetPresent, "L8: and the body contains no RET at all");

  // The receiver: ESTABLISHED. It is present, in ECX, bounds-only, an alias, and
  // it reaches exactly two displacements. The abstention on the convention is not
  // an abstention on the receiver, and a package that lost the second would have
  // understated what the machine proved.
  check(static_cast<int>(kDerivedReceiverRegister) ==
            static_cast<int>(ReceiverRegister00f96840::kEcx),
        "L9: the receiver register is ECX");
  check(static_cast<int>(ReceiverRegister00f96840::kEcx) == 0,
        "L9a: and the register enumerator spells ECX, not a second register");
  check(kReceiverPresent, "L10: a receiver IS present, whatever the convention is");
  check(kReceiverBoundsOnly, "L11: bounds only, so no layout is claimed");
  check(!kReceiverHasType, "L12: and no receiver type is claimed either");
  check(kReceiverShape == ReceiverShape00f96840::kRegisterAlias,
        "L13: the receiver's shape is R-ALIAS, the register the body copies it "
        "into");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDistinctOffsets), 2u,
               "L14: two distinct receiver displacements");
  check(kReceiverOffsetFirstWord == 0x000u,
        "L15: the first is the object's own first word, at +0x0");
  check(kReceiverOffsetZeroed == 0x814u,
        "L16: the second is +0x814, the one word this body writes");
  check(kReceiverOffsetFirstWord == 0u && kReceiverOffsetZeroed == 2068u,
        "L16a: both spelled in decimal as the record's own numbers");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverWrittenThroughCount), 1u,
               "L17: the receiver is written through exactly once");
  check_eq_u32(kZeroedWord, 0u, "L18: and the word written is zero");

  // The return: the record names a register and a class, and NO type. Naming one
  // here would be naming the return type of the routine at table slot 0x84.
  check(kReturnRegisterClass == ReturnRegisterClass00f96840::kPointerLike,
        "L19: the return register's class is pointer_like");
  check(!kReturnTypeClaimed,
        "L20: and no C return type is claimed for this entry");
  check(!kVoidPossibleByMachine,
        "L21: the machine says a void return is not possible, which is why the "
        "entry's `void` is a statement about the entry and not about EAX");
}

// N -- the extent facts, restated from the listing. These are the counts the
// fifteen instructions give, checked against literals written here so a header
// edit cannot move both sides together.
void case_machine_extent_constants() {
  check(kInstructionCount == 15, "N1: the body is fifteen instructions");
  check(kBodySpanBytes == 42u, "N2: and spans forty-two bytes");
  check(kBodyFirstByte == 0x00f96840u && kBodyLastByte == 0x00f96869u &&
            kBodyEndExclusive == 0x00f9686au,
        "N3: the span is 0x00f96840..0x00f96869, exclusive end 0x00f9686a");
  check(kTargetVa == 0x00f96840u, "N4: the target VA is 0x00f96840");
  check(kConditionalBranches == 0, "N5: the body contains no conditional branch");
  check(kBasicBlockCount == 1, "N6: and is a single basic block");
  check(kDirectCalleeCount == 0, "N7: and names no direct callee");
  check_eq_u32(static_cast<std::uint32_t>(kIndirectTransferCount), 3u,
               "N8: and makes three indirect transfers");
  check_eq_u32(static_cast<std::uint32_t>(kTailTransferCount), 1u,
               "N9: the last of them is the tail the record abstained on");
  check_eq_u32(static_cast<std::uint32_t>(kTerminalRetCount), 0u,
               "N10: and there is no terminator to count");
  check(kGlobalReferences == 0, "N11: the body names no global");
  check_eq_u32(static_cast<std::uint32_t>(kStackArgumentSlots), 0u,
               "N12: and pushes no stack argument for any callee");
  check_eq_u32(static_cast<std::uint32_t>(kSavedRegisterCount), 1u,
               "N13: exactly one register is saved, ESI");

  // The three slot displacements, spelled here rather than read from the header.
  check(kSlotFirstCall == 0x70u, "N14: the first transfer reads displacement 0x70");
  check(kSlotSecondCall == 0x60u, "N15: the second reads 0x60");
  check(kSlotTailTransfer == 0x84u, "N16: and the tail reads 0x84");
  check(kSlotFirstCall != kSlotSecondCall && kSlotSecondCall != kSlotTailTransfer &&
            kSlotFirstCall != kSlotTailTransfer,
        "N17: the three are distinct, so the trace can tell them apart");
  check(kTableBytes >= kSlotTailTransfer + 4u,
        "N18: the fixture's table window holds all three words");
  check(kObjectBytes >= kReceiverOffsetZeroed + 4u,
        "N19: and the receiver's window holds the word this body writes");
  check(sizeof(void*) == 4u, "N20: the reconstruction is an x86-32 model");
}

// A -- the baseline. Three transfers, in the order the listing gives, all through
// the table word at the receiver's +0x00, with the receiver in ECX throughout and
// the one store done before the tail.
void case_baseline_three_transfers_in_order() {
  build_fixture();
  Sample sample;
  const int via_tail = run_body(address_of(&re_00f96840), address_of(&g_object), &sample);

  check(via_tail == 1,
        "A1: control left the body through the routine at table slot 0x84, the "
        "tail jump, and never came back to the harness");
  check_eq_u32(sample.returned_normally, 0u,
               "A2: the harness's own post-call code never ran, which is the same "
               "fact measured through the other channel");
  check_eq_u32(static_cast<std::uint32_t>(g_trace.count), 3u,
               "A3: exactly three transfers were observed");
  check(g_trace.step[0] == 1u, "A4: the first went through table slot 0x70");
  check(g_trace.step[1] == 2u, "A5: the second through table slot 0x60");
  check(g_trace.step[2] == 3u, "A6: and the third through table slot 0x84");

  const std::uint32_t table_address = address_of(&g_table);
  for (unsigned index = 0u; index < 3u; ++index) {
    char label[128];
    std::snprintf(label, sizeof label,
                  "A7.%u: ECX held the receiver, unadjusted, at transfer %u", index,
                  index + 1u);
    check(g_trace.ecx[index] == address_of(&g_object), label);
    std::snprintf(label, sizeof label,
                  "A8.%u: EAX held the table word at transfer %u", index, index + 1u);
    check(g_trace.eax[index] == table_address, label);
  }
  // The transfer target really came out of the table, and the tail really went to
  // the routine installed at 0x84 rather than to the entry itself.
  check(g_trace.edx[0] == address_of(&shim_first_call) &&
            g_trace.edx[1] == address_of(&shim_second_call) &&
            g_trace.edx[2] == address_of(&shim_tail_transfer),
        "A9: each transfer's EDX was the word the corresponding slot holds");
  check(g_trace.edx[2] != address_of(&re_00f96840) && g_trace.edx[2] != table_address,
        "A10: and the tail went to neither the entry nor the table itself");

  // The single store: four bytes, at the receiver's +0x814, zero, and nothing
  // else in the whole receiver touched.
  check_eq_u32(g_trace.zeroed_word, 0u,
               "A11: the word at the receiver's +0x814 was already zero when "
               "control left the body, so the store happened BEFORE the transfer");
  check_eq_u32(g_trace.zeroed_receiver, address_of(&g_object),
               "A12: and it was read through the receiver the tail was handed");
  int changed = 0;
  int first_changed = -1;
  for (std::size_t index = 4u; index < kObjectBytes; ++index) {
    // The scan starts at +4, because the receiver's own first word is the table
    // pointer the fixture installed there: it is not a sentinel byte and not
    // something this body wrote.
    const bool expected = (index >= kReceiverOffsetZeroed &&
                           index < kReceiverOffsetZeroed + 4u);
    const std::uint8_t want = expected ? 0u : kSentinel;
    if (g_object.bytes[index] != want) {
      if (first_changed < 0) {
        first_changed = static_cast<int>(index);
      }
      ++changed;
    }
  }
  check_eq_u32(word_at(g_object.bytes, kReceiverOffsetFirstWord), table_address,
               "A12a: the receiver's first word still holds the table pointer the "
               "body read three times");
  check(changed == 0, "A13: after the run the receiver holds the sentinel pattern "
                      "with exactly four zeroed bytes at +0x814 and nothing else");
  check(first_changed < 0 ||
            static_cast<std::size_t>(first_changed) == kReceiverOffsetZeroed,
        "A14: the first word that differs from the sentinel is at +0x814");
}

// B -- the stack discipline. The body pushes one word and pops it, passes no
// argument at all, and pops BEFORE the transfer out, so the routine at slot 0x84
// is entered on the caller's own stack. Each relation below is written out from
// the arithmetic rather than folded into a single constant, and the
// return-address size is carried in each term explicitly: the probe samples ESP
// immediately before its CALL, so the body is entered with a return address
// already on the stack, and it is entered a second time over by the body's own
// CALL for each of the two slots it calls.
constexpr std::uint32_t kReturnAddressBytes = 4u;  // what a CALL pushes
constexpr std::uint32_t kSavedWordBytes = 4u;     // what PUSH ESI pushes

void case_stack_discipline_is_measured() {
  build_fixture();
  Sample sample;
  const int via_tail = run_body(address_of(&re_00f96840), address_of(&g_object), &sample);
  check(via_tail == 1, "B0: the run completed through the tail");

  // ESP sampled immediately before the CALL is the stack the probe calls from, and
  // it is a real one: a zero here would make every relation below pass for the
  // wrong reason.
  check(sample.esp_before != 0u, "B1: a real stack pointer was sampled");

  //   esp_before (the probe's ESP immediately before it called the body)
  //     - 4  the probe's own CALL pushed a return address; the body is entered
  //          with it still on the stack
  //     - 4  the body's PUSH ESI at 00f96840 is still outstanding
  //     - 4  the body's own CALL at 00f96848 pushed a return address
  //   = the ESP the routine at slot 0x70 is entered on
  check_eq_u32(sample.esp_before - g_trace.entry_esp[0],
               kReturnAddressBytes + kSavedWordBytes + kReturnAddressBytes,
               "B2: the first callee was entered below the probe's return address, "
               "below the body's one pushed word and below its own return address");
  // Step 2 is the same shape: the first call has returned, so the only words
  // between the probe's sample and the second callee are the two return
  // addresses and the single PUSH ESI.
  check_eq_u32(sample.esp_before - g_trace.entry_esp[1],
               kReturnAddressBytes + kSavedWordBytes + kReturnAddressBytes,
               "B3: and so was the second, with the first call's frame already gone");
  // Step 3 is entered by a TAIL JUMP: no return address is pushed for it, and
  // POP ESI has already run. So the only word between the probe's sample and the
  // tail target is the probe's own return address.
  check_eq_u32(sample.esp_before - g_trace.entry_esp[2], kReturnAddressBytes,
               "B4: the tail target was entered with only the probe's return "
               "address below it, so no return address was pushed for the tail");
  // The same two facts read relative to the first callee, so the check does not
  // depend on the probe's own frame at all. The tail target sits two words higher
  // than the first callee, and the two words are named: the one PUSH ESI took and
  // popped, and the return address a CALL would have pushed for the tail and a
  // JMP does not. A body that transferred out with ESI still pushed would show a
  // difference of one word here; a body that pushed a return address for the tail
  // would show one word the other way.
  check_eq_u32(g_trace.entry_esp[2] - g_trace.entry_esp[0],
               kSavedWordBytes + kReturnAddressBytes,
               "B5: the tail target is two words higher than the first callee -- the "
               "popped ESI and the return address a tail jump does not push");
  check_eq_u32(static_cast<std::uint32_t>(sizeof(void*)), 4u,
               "B6: the return-address size carried above is this target's");
}

// C -- the three displacements are read where the listing says, not merely in
// some order. Swapping the two CALL slots in the fixture must swap which routine
// is reached at each position, and a body that read both calls through the same
// displacement -- or through the wrong two -- would not follow.
void case_slots_are_read_by_displacement() {
  install_table(address_of(&shim_second_call), address_of(&shim_first_call),
                address_of(&shim_tail_transfer));
  Sample sample;
  const int via_tail = run_body(address_of(&re_00f96840), address_of(&g_object), &sample);
  check(via_tail == 1, "C0: the run completed through the tail");
  check(g_trace.step[0] == 2u,
        "C1: with the two call slots swapped, the FIRST call reaches slot 0x60");
  check(g_trace.step[1] == 1u,
        "C2: and the second reaches slot 0x70, so each is read at its own "
        "displacement and not at a fixed one");
  check(g_trace.step[2] == 3u, "C3: the tail is unaffected by that swap");
  check_eq_u32(g_trace.zeroed_word, 0u,
               "C4: and the single store is still the one the listing fixes");
}

// D -- the receiver is used exactly where it was handed, with no adjustment. The
// receiver here is an INTERIOR pointer of a larger buffer, so a body that added
// or subtracted a constant before reading the table word or before storing would
// be caught, and a body that returned the buffer's head would be caught too.
void case_receiver_is_used_unadjusted() {
  const std::size_t interior[] = {4u, 8u, 16u, 64u};
  const int count = static_cast<int>(sizeof interior / sizeof interior[0]);
  for (int index = 0; index < count; ++index) {
    const std::size_t offset = interior[index];
    std::memset(g_object.bytes, kSentinel, kObjectBytes);
    // The table word goes at the INTERIOR receiver's own +0x0, and nowhere else.
    // That is the whole point of this case: the body reads [ESI] with no
    // displacement, so an interior receiver is usable only if it is the address the
    // table was written for, and a body that adjusted the pointer -- or that read
    // the fixture's head instead -- would read the sentinel pattern and die.
    build_table(address_of(&shim_first_call), address_of(&shim_second_call),
                address_of(&shim_tail_transfer));
    store_word(g_object.bytes, offset, address_of(&g_table));
    Sample sample;
    const int via_tail =
        run_body(address_of(&re_00f96840),
                 address_of(&g_object) + static_cast<std::uint32_t>(offset), &sample);
    char label[160];
    std::snprintf(label, sizeof label, "D0.%d: a receiver at +%u still tails out", index,
                  static_cast<unsigned>(offset));
    check(via_tail == 1, label);
    std::snprintf(label, sizeof label,
                  "D1.%d: a receiver at +%u read the table word at ITS OWN +0x0",
                  index, static_cast<unsigned>(offset));
    check(g_trace.eax[0] == address_of(&g_table), label);
    std::snprintf(label, sizeof label,
                  "D2.%d: a receiver at +%u was the ECX value at every transfer",
                  index, static_cast<unsigned>(offset));
    check(g_trace.ecx[0] == address_of(&g_object) + static_cast<std::uint32_t>(offset) &&
              g_trace.ecx[2] == address_of(&g_object) + static_cast<std::uint32_t>(offset),
          label);
    std::snprintf(label, sizeof label,
                  "D3.%d: a receiver at +%u wrote its OWN +0x814 and nothing else",
                  index, static_cast<unsigned>(offset));
    check(word_at(g_object.bytes, offset + kReceiverOffsetZeroed) == 0u, label);
    std::snprintf(label, sizeof label,
                  "D4.%d: a receiver at +%u left every other byte at the sentinel",
                  index, static_cast<unsigned>(offset));
    bool untouched = true;
    for (std::size_t byte = 0u; byte < kObjectBytes; ++byte) {
      const bool is_table_word = (byte >= offset && byte < offset + 4u);
      // Everything outside the interior receiver and its own table word must still
      // be the sentinel pattern, including the fixture's own first word.
      const bool written = (byte >= offset + kReceiverOffsetZeroed &&
                            byte < offset + kReceiverOffsetZeroed + 4u);
      const std::uint8_t want =
          written ? 0u
                  : (is_table_word
                         ? static_cast<std::uint8_t>((address_of(&g_table) >>
                                                     (8u * (byte - offset))) &
                                                    0xffu)
                         : kSentinel);
      if (g_object.bytes[byte] != want) {
        untouched = false;
      }
    }
    check(untouched, label);
  }
}

// E -- the store writes ZERO, not merely "something". The four bytes are filled
// with a recognisable pattern first, so a body that stored a different constant,
// or left the word alone, or wrote a different width, all fail.
void case_the_store_writes_zero() {
  const std::uint32_t priors[] = {0xffffffffu, 0xa5a5a5a5u, 0x00000001u, 0xdeadbeefu};
  const int count = static_cast<int>(sizeof priors / sizeof priors[0]);
  for (int index = 0; index < count; ++index) {
    build_fixture();
    store_word(g_object.bytes, kReceiverOffsetZeroed, priors[index]);
    Sample sample;
    const int via_tail =
        run_body(address_of(&re_00f96840), address_of(&g_object), &sample);
    char label[160];
    std::snprintf(label, sizeof label,
                  "E0.%d: prior 0x%08x, the run still tails out", index, priors[index]);
    check(via_tail == 1, label);
    std::snprintf(label, sizeof label,
                  "E1.%d: prior 0x%08x, the word is exactly zero afterwards", index,
                  priors[index]);
    check_eq_u32(word_at(g_object.bytes, kReceiverOffsetZeroed), 0u, label);
    std::snprintf(label, sizeof label,
                  "E2.%d: prior 0x%08x, the byte above the word is untouched",
                  index, priors[index]);
    check(g_object.bytes[kReceiverOffsetZeroed + 4u] == kSentinel, label);
    std::snprintf(label, sizeof label,
                  "E3.%d: prior 0x%08x, and the byte below it too", index,
                  priors[index]);
    check(g_object.bytes[kReceiverOffsetZeroed - 1u] == kSentinel, label);
  }
}

// F -- the two channels are exclusive. A body that both tailed out AND returned
// would be a different body from either, and the two observations are read
// through different mechanisms: one is the probe's own post-call code, the other
// is the routine installed at table slot 0x84 calling back. Requiring exactly one
// of them is what makes the pair a witness rather than two restatements.
void case_the_two_channels_agree() {
  build_fixture();
  Sample sample;
  const int via_tail = run_body(address_of(&re_00f96840), address_of(&g_object), &sample);
  check(via_tail == 1, "F1: the tail channel fired");
  check_eq_u32(sample.returned_normally, 0u, "F2: the return channel did not");
  check(g_trace.step[2] == 3u,
        "F3: and the transfer that fired the tail channel is the one the body makes "
        "last");
  check_eq_u32(static_cast<std::uint32_t>(g_trace.count), 3u,
               "F4: no fourth transfer happened, so the tail channel did not fire "
               "twice");
  check_eq_u32(sample.esp_after, 0u,
               "F5: the probe never wrote esp_after, because its post-call code "
               "never ran -- the zero is the probe's own initialisation and is "
               "checked here so the two are not confused");
}

}  // namespace
}  // namespace pkg_w2_00f96840
}  // namespace reconstruction
}  // namespace openspore

int main() {
  using namespace openspore::reconstruction::pkg_w2_00f96840;

  case_the_entry_emits_the_target_bytes();
  case_the_record_travels_as_data();
  case_machine_extent_constants();
  case_baseline_three_transfers_in_order();
  case_stack_discipline_is_measured();
  case_slots_are_read_by_displacement();
  case_receiver_is_used_unadjusted();
  case_the_store_writes_zero();
  case_the_two_channels_agree();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("all checks passed\n");
  return 0;
}
