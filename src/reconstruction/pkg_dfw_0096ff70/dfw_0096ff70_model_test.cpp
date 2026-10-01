// PKG-DFW-0096FF70 -- VA 0x0096ff70
// Behavioural model test for the two-instruction body at 0x0096ff70.
//
// The one direct transfer the body makes -- the tail jump at 0x0096ff73 to
// 0x0096ffd0 -- is defined here as an observer, so the test sees the transfer
// the reconstruction makes and gets to decide what the tail target does with
// the two things it is handed.
//
// The assertions are the claims the two-instruction listing fixes, and nothing
// more:
//
//   * exactly one transfer leaves the body, and it is the tail target;
//   * the receiver is handed on 12 bytes below where it arrived, from
//     SUB ECX,0x0C at 0x0096ff70;
//   * the single ordinary stack word is forwarded bit for bit, and the low bit
//     of it is not examined in this frame (the TEST that reads it is at
//     0x0096fff3, inside the tail target), so no input selects a path here;
//   * no byte of the receiver is written, and the frame's net stack effect is
//     the removal of the one forwarded word, which is the RET 0x4 at
//     0x00970006 that the machine performs in the tail target's frame;
//   * the two immediates the listing fixes are the ones the model uses, tied to
//     each other by the arithmetic of the jump's rel32 displacement.
//
// Nothing here asserts what the tail target does internally, what the object it
// receives contains, or what class the receiver belongs to. No record for this
// target settles any of those.

#include "dfw_0096ff70_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <type_traits>

namespace openspore::reconstruction::pkg_dfw_0096ff70 {

namespace {

// The adjustment the listing fixes at 0x0096ff70, and the jump displacement it
// fixes at 0x0096ff73, restated here as plain literals so that the header's
// constants are checked against the transcription rather than trusted.
constexpr std::size_t kListedAdjustment = 0x0cu;
constexpr std::size_t kListedRel32 = 0x58u;
constexpr Word kListedTailTarget = 0x0096ffd0u;

// Storage large enough that the receiver can sit at offset 0x0C and still have
// a valid address 12 bytes below itself, which is what SUB ECX,0x0C produces.
// The model reproduces pointer arithmetic the machine performs, and the test
// keeps that arithmetic inside a real allocation so the C++ object model is
// never asked to bless a pointer outside any object.
constexpr std::size_t kStorageBytes = 512u;

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// The receiver as a word-addressed block. Nothing here names a member of it:
// the body performs no load and no store, so there is no displacement to name
// and no layout to assert.
struct Receiver {
  alignas(16) unsigned char bytes[kStorageBytes] = {};
};

struct Observation {
  // How many times the tail target was entered, and the order of the events
  // this frame produced. The body has exactly one transfer, so a correct
  // reconstruction leaves exactly one event here.
  int tail_calls = 0;
  int event_count = 0;
  unsigned char events[8] = {};

  // What the tail target was handed on its two parameters.
  TailTargetObject *object = nullptr;
  Word deleting_flag = 0u;

  // Whether the tail target is asked to plant a word in the receiver it is
  // given, which is how the "this frame writes nothing" check tells its own
  // writes apart from a callee's.
  bool tail_writes_object = false;
};

Observation g_obs;

// The frame's net stack effect is a real claim of this reconstruction: the
// machine removes the one forwarded word with the RET 0x4 at 0x00970006, so
// the caller's stack pointer is exactly where it was when the call began. A
// frame that is balanced under EBP-relative addressing still shows a shifted
// ESP, so C++ cannot observe this on its own and the check below writes the
// call site out by hand. It is a single asm statement, which means no compiler
// scheduling and no outgoing-argument area of the compiler's own can be
// mistaken for an imbalance in the callee -- at -O1 and above a compiler-
// generated call keeps its argument slot allocated across the call, and a
// compiler-generated sample reads that slot rather than the callee's discipline.
// Where GNU-style inline asm is not available the check says it could not be
// measured instead of passing quietly.
#if defined(__GNUC__) || defined(__clang__)
constexpr bool kStackTraceIsMeasurable = true;
#else
constexpr bool kStackTraceIsMeasurable = false;
#endif

// The receiver as the thunk is handed it: a pointer to a block, with no member
// named. The type is distinct from the tail target's on purpose, so a test
// cannot pass the wrong kind of address by accident.
ThunkReceiver *thunk_receiver_address(Receiver &receiver, std::size_t offset) {
  return reinterpret_cast<ThunkReceiver *>(receiver.bytes + offset);
}

const unsigned char *as_bytes(const void *address) {
  return static_cast<const unsigned char *>(address);
}

}  // namespace

// 0x0096ffd0, the tail target, as an observer. Its real listing ends with
// MOV EAX,ESI at 0x00970003, so it hands its receiver back in the return
// register; the observer does the same, and the reconstruction discards the
// word because the persisted ABI record types this body void and the two
// instructions at 0x0096ff70 never write EAX.
extern "C" TailTargetObject *PKG_DFW_0096FF70_CDECL
dfw_tail_deleting_0096ffd0(TailTargetObject *object, Word deleting_flag) {
  ++g_obs.tail_calls;
  ++g_obs.event_count;
  if (g_obs.event_count <= static_cast<int>(sizeof g_obs.events)) {
    g_obs.events[g_obs.event_count - 1] = 'T';
  }
  g_obs.object = object;
  g_obs.deleting_flag = deleting_flag;
  if (g_obs.tail_writes_object) {
    // Stand-in for the four vptr-shaped stores the real tail target performs
    // at 0x0096ffd3, 0x0096ffd9, 0x0096ffe0 and 0x0096ffe7. Which of those
    // writes belong to this frame is exactly what the checks below separate.
    std::memcpy(object, "tail", 4u);
  }
  return object;
}

namespace {

// The declared shape of the reconstruction itself: void, a hidden receiver and
// one ordinary stack word, in the callee-cleaned register-receiver convention
// this package declares. The persisted ABI record types this body void, and the
// runtime stack-balance check below is what backs the cleanup half of the
// convention, since a declaration alone asserts nothing about the epilogue.
//
// The two spellings are the two tools' own: MSVC puts the keyword between the
// parentheses and the pointer's name, GCC and clang only accept it after the
// declarator.
#if defined(_MSC_VER)
typedef void(__thiscall *ThunkSignature)(ThunkReceiver *, Word);
#else
typedef void(*PKG_DFW_0096FF70_THISCALL ThunkSignature)(ThunkReceiver *, Word);
#endif
static_assert(std::is_same<decltype(&dfw_func88h_0096ff70), ThunkSignature>::value,
              "0x0096ff70 is void, thiscall, receiver plus one stack word");

// 0x0096ff73 is the only transfer out of the body, and it reaches the tail
// target and nothing else. The event log is the whole of what this frame did
// observably: one entry, the tail target, on every input.
void test_one_transfer_and_no_other_work() {
  Receiver receiver;
  g_obs = Observation{};

  dfw_func88h_0096ff70(
      thunk_receiver_address(receiver, 0x40u), 0x00000001u);

  check(g_obs.tail_calls == 1,
        "0x0096ff73 reaches the tail target exactly once");
  check(g_obs.event_count == 1,
        "the body produces exactly one observable event");
  check(g_obs.event_count >= 1 && g_obs.events[0] == 'T',
        "the one event is the transfer to the tail target");
}

// 0x0096ff70  SUB ECX,0x0C. The tail target's receiver is 12 bytes below the
// receiver the thunk was handed, for every receiver: the adjustment is
// arithmetic on the pointer, not a property of any one object.
void test_the_receiver_is_reduced_by_twelve_bytes() {
  const std::size_t offsets[] = {0x0cu, 0x40u, 0x0100u};
  for (const std::size_t offset : offsets) {
    Receiver receiver;
    g_obs = Observation{};

    ThunkReceiver *const handed =
        thunk_receiver_address(receiver, offset);
    dfw_func88h_0096ff70(handed, 0u);

    const unsigned char *const expected =
        as_bytes(handed) - kListedAdjustment;
    check(g_obs.object == reinterpret_cast<TailTargetObject *>(
                              const_cast<unsigned char *>(expected)),
          "the tail target's receiver is the thunk's receiver minus 0x0C");
    check(kReceiverAdjustmentBytes == kListedAdjustment,
          "the modelled adjustment is the immediate at 0x0096ff70");
  }
}

// The one ordinary stack word is forwarded untouched. The persisted ABI record
// types it uint32 at ESP+0x08 and names it deleting_flag; this body neither
// reads it nor rewrites it.
void test_the_stack_word_is_forwarded_bit_for_bit() {
  const Word flags[] = {0x00000000u, 0x00000001u, 0x00000002u, 0x00000003u,
                        0x80000000u, 0xffffffffu};
  for (const Word flag : flags) {
    Receiver receiver;
    g_obs = Observation{};

    dfw_func88h_0096ff70(thunk_receiver_address(receiver, 0x40u), flag);

    check(g_obs.deleting_flag == flag,
          "the tail target receives the word the thunk was handed, unchanged");
    check(g_obs.tail_calls == 1,
          "the forward happens once for every value of the word");
  }
}

// There is no branch in this frame. The TEST that reads bit 0 of the forwarded
// word is at 0x0096fff3, inside the tail target, so no value of the word -- and
// no value of the receiver -- can change what this body observably does. The
// only thing that varies with the input is the word that is passed on.
void test_no_input_selects_a_path() {
  for (const Word flag : {0u, 1u, 2u, 4u, 0xffffffffu}) {
    Receiver receiver;
    g_obs = Observation{};

    dfw_func88h_0096ff70(thunk_receiver_address(receiver, 0x40u), flag);

    check(g_obs.tail_calls == 1,
          "every value of the forwarded word takes the same single path");
    check(g_obs.event_count == 1,
          "no value of the forwarded word produces a second event");
  }

  // And the receiver's contents cannot matter either, because no instruction in
  // the body reads memory. The same call against two differently filled
  // receivers is observably identical.
  Receiver filled;
  Receiver empty;
  std::memset(filled.bytes, 0xa5, sizeof filled.bytes);

  g_obs = Observation{};
  dfw_func88h_0096ff70(thunk_receiver_address(filled, 0x40u), 3u);
  const int filled_calls = g_obs.tail_calls;
  const std::ptrdiff_t filled_delta = g_obs.object == nullptr
                                          ? 0
                                          : as_bytes(g_obs.object) -
                                                as_bytes(filled.bytes) - 0x40;

  g_obs = Observation{};
  dfw_func88h_0096ff70(thunk_receiver_address(empty, 0x40u), 3u);
  const int empty_calls = g_obs.tail_calls;
  const std::ptrdiff_t empty_delta = g_obs.object == nullptr
                                         ? 0
                                         : as_bytes(g_obs.object) -
                                               as_bytes(empty.bytes) - 0x40;

  check(filled_calls == 1 && empty_calls == 1,
        "the receiver's contents do not change the number of transfers");
  check(filled_delta == empty_delta &&
            filled_delta == -static_cast<std::ptrdiff_t>(kListedAdjustment),
        "the receiver's contents do not change the adjustment");
}

// No instruction in the body stores to memory, so the receiver must come back
// byte for byte as it went in -- on either value of the forwarded word.
//
// One honest limit, the same one the reference model test states: a store that
// wrote back the value it had just read would leave the bytes identical and so
// would pass here. That store is not observable through this interface and is
// not claimed to be excluded. Every store that changes a byte is excluded.
void test_the_frame_writes_no_memory() {
  unsigned char before[kStorageBytes];

  for (const Word flag : {0u, 1u}) {
    Receiver receiver;
    std::memset(receiver.bytes, 0x5au, sizeof receiver.bytes);
    std::memcpy(before, receiver.bytes, sizeof before);

    g_obs = Observation{};
    dfw_func88h_0096ff70(thunk_receiver_address(receiver, 0x40u), flag);

    check(std::memcmp(before, receiver.bytes, sizeof before) == 0,
          "no byte of the receiver is written by this frame");
  }

  // The converse, so the check is shown to be able to fail: a tail target that
  // does write is still detected, and the write is attributed to the callee
  // rather than to the thunk.
  Receiver receiver;
  std::memset(receiver.bytes, 0x5au, sizeof receiver.bytes);
  std::memcpy(before, receiver.bytes, sizeof before);
  g_obs = Observation{};
  g_obs.tail_writes_object = true;
  dfw_func88h_0096ff70(thunk_receiver_address(receiver, 0x40u), 0u);
  check(std::memcmp(before, receiver.bytes, sizeof before) != 0,
        "the comparison above can see a write, so its pass is not vacuous");
}

// The machine's single RET 0x4, at 0x00970006 inside the tail target, is the
// one that removes the forwarded word. The model attributes that pop to the
// thunk's own callee-cleaned epilogue (see the source-shape note in the .cpp),
// and the consequence is fixed: the caller's stack pointer is exactly where it
// was before the call.
//
// The call site is written out here rather than left to the compiler, because
// this is the one claim a compiler-generated call site cannot be used to check:
// the sequence is exactly the machine's -- push one word, load ECX, call -- and
// the stack-pointer sample brackets only that sequence. A compiler-generated
// call keeps its own outgoing-argument slot allocated across the call, and a
// sample placed next to it reads that slot rather than the callee's discipline;
// at -O1 and above this check read a 12-byte residue from exactly that slot
// before the call site was written out by hand.
//
// The residue is measured inside the one asm statement, and the caller's stack
// pointer is carried across the call *in memory* rather than in a register. A
// register would not do: the asm contains a call, and a call destroys every
// caller-saved register, so a value the asm had written into one before the
// call would be gone by the time the asm ended -- silently, and only at
// register-pressure-heavy optimisation levels.
void test_the_frame_is_stack_neutral() {
  if (!kStackTraceIsMeasurable) {
    std::fprintf(stderr,
                 "note: the stack trace is not available on this compiler, so "
                 "the cleanup claim is unchecked here\n");
    return;
  }

  Receiver receiver;
  g_obs = Observation{};

  ThunkReceiver *const handed = thunk_receiver_address(receiver, 0x40u);
  const Word flag = 0x00000001u;
  std::uintptr_t residue = 1u;

  __asm__ volatile(
      "pushl %%esp\n\t"           /* the caller's stack pointer, into memory */
      "pushl %[flag]\n\t"         /* the one ordinary stack word */
      "movl %[handed], %%ecx\n\t" /* the hidden receiver */
      "calll *%[thunk]\n\t"       /* the transfer the listing fixes */
      "movl (%%esp), %%eax\n\t"   /* the saved stack pointer, into a register */
      "addl $4, %%esp\n\t"        /* the frame is whole again */
      "subl %%esp, %%eax\n\t"     /* zero exactly when the word was popped */
      : [residue] "=&a"(residue)
      : [flag] "r"(flag), [handed] "r"(handed), [thunk] "r"(&dfw_func88h_0096ff70)
      : "ecx", "memory", "cc");

  check(residue == 0u,
        "the call leaves the caller's stack pointer where it was, which is "
        "the one forwarded word being popped exactly once");
  check(g_obs.tail_calls == 1,
        "the stack-neutral call is the one transfer the listing fixes");
  check(g_obs.deleting_flag == flag && g_obs.object != nullptr,
        "the hand-rolled call site still forwards the word and the receiver");
}

// The two immediates the listing fixes, and the arithmetic that relates them:
// a near jump's rel32 displacement is measured from the address after the
// instruction, so 0x0096ff78 + 0x58 is 0x0096ffd0. Checking the transcription
// against itself is what catches a package that changes one constant and leaves
// the other behind.
void test_the_modelled_immediates_are_the_listings() {
  check(kReceiverAdjustmentBytes == 0x0cu,
        "0x0096ff70 models SUB ECX,0x0C");
  check(kTailJumpRel32 == kListedRel32, "0x0096ff73 models JMP with rel32 0x58");
  check(kTailTargetAddress == kListedTailTarget,
        "0x0096ff73 models JMP 0x0096FFD0");
  check(kTailJumpInstructionEnd + kTailJumpRel32 == kTailTargetAddress,
        "the jump's displacement lands on the jump's target");
  check(kBodyStartAddress == 0x0096ff70u, "the body starts at 0x0096ff70");
  check(kBodyEndAddress == 0x0096ff77u, "the body ends at 0x0096ff77");
  check(kBodyEndAddress - kBodyStartAddress + 1u == 8u,
        "the body is the eight bytes the bridge reports");
  check(kInt3PaddingEndAddress == 0x0096ff7fu,
        "the INT3 pad through 0x0096ff7f is recorded, and is not body");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_0096ff70

int main() {
  using namespace openspore::reconstruction::pkg_dfw_0096ff70;
  test_one_transfer_and_no_other_work();
  test_the_receiver_is_reduced_by_twelve_bytes();
  test_the_stack_word_is_forwarded_bit_for_bit();
  test_no_input_selects_a_path();
  test_the_frame_writes_no_memory();
  test_the_frame_is_stack_neutral();
  test_the_modelled_immediates_are_the_listings();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
